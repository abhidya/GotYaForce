import assert from "node:assert/strict";
import fs from "node:fs";
import path from "node:path";
import vm from "node:vm";
import test from "node:test";
import { execFileSync } from "node:child_process";
import { fileURLToPath } from "node:url";
import ts from "typescript";
import * as THREE from "three";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const filename = "apps/game/src/sim/borgPresentationAssets.ts";
const source = process.env.ANIMATION_TEST_BASE_REF
  ? execFileSync("git", ["show", `${process.env.ANIMATION_TEST_BASE_REF}:${filename}`], { cwd: root, encoding: "utf8" })
  : fs.readFileSync(path.join(root, filename), "utf8");
const tree = ts.createSourceFile(filename, source, ts.ScriptTarget.Latest, true);
// Execute the complete production module, removing only imports. Three.js is real;
// only fetch and the unrelated model loader/public URL environment are boundaries.
const code = ts.transpileModule(tree.statements.filter(n => !ts.isImportDeclaration(n))
  .map(n => n.getText(tree)).join("\n"), {
  compilerOptions: { target: ts.ScriptTarget.ES2022, module: ts.ModuleKind.CommonJS },
}).outputText;
const index = { borg: "pl0615", banks: [{ file: "idle.json", group: 0, slot: 0, label: "idle", frames: 6 }] };
const clip = { name: "idle", frameCount: 6, bones: [] };
const ok = json => ({ ok: true, status: 200, json: async () => json });
const absent = () => ({ ok: false, status: 404 });
function harness() {
  const calls = [];
  let respond = url => ok(url.endsWith("anim_index.json") ? index : clip);
  const context = vm.createContext({ exports: {}, THREE, SOURCE_FRAME_RATE_HZ: 60,
    publicUrl: value => value, fetch: async url => { calls.push(url); return respond(url); } });
  vm.runInContext(code, context);
  const assets = context.exports.createBorgPresentationAssets({ assetLoader: {}, defaultLeadId: "pl0615" });
  return { calls, assets, respond: fn => { respond = fn; },
    load: mode => mode === "label" ? assets.loadClip("pl0615", "idle")
      : assets.loadClipByStreamRef("pl0615", { group: 0, slot: 0 }) };
}
const failures = {
  "HTTP 503": () => ({ ok: false, status: 503 }),
  "HTTP 429": () => ({ ok: false, status: 429 }),
  "HTTP 403": () => ({ ok: false, status: 403 }),
  network: () => { throw new TypeError("Network unavailable"); },
  JSON: () => ({ ok: true, status: 200, json: async () => { throw new SyntaxError("Incomplete JSON"); } }),
};
for (const mode of ["label", "exact"]) {
  for (const boundary of ["index", "bank"]) {
    for (const [reason, failure] of Object.entries(failures)) {
      test(`${mode}: ${boundary} ${reason} recovers on next request`, async () => {
        const h = harness();
        let healthy = false;
        h.respond(url => !healthy && (url.endsWith("anim_index.json") === (boundary === "index"))
          ? failure() : ok(url.endsWith("anim_index.json") ? index : clip));
        assert.equal(await h.load(mode), null);
        healthy = true;
        const recovered = await h.load(mode);
        assert.ok(recovered instanceof THREE.AnimationClip);
        assert.equal(recovered.name, "idle");
        assert.equal(h.calls.length, 3);
        assert.equal(await h.load(mode), recovered);
        assert.equal(h.calls.length, 3, "successful clip remains cached");
      });
    }
    test(`${mode}: ${boundary} 404 stays cached`, async () => {
      const h = harness();
      h.respond(url => url.endsWith("anim_index.json") === (boundary === "index")
        ? absent() : ok(index));
      assert.equal(await h.load(mode), null);
      assert.equal(await h.load(mode), null);
      assert.equal(h.calls.length, boundary === "index" ? 1 : 2);
    });
  }
  test(`${mode}: missing bank stays cached without a clip fetch`, async () => {
    const h = harness(); h.respond(() => ok({ ...index, banks: [] }));
    assert.equal(await h.load(mode), null); assert.equal(await h.load(mode), null);
    assert.equal(h.calls.length, 1);
  });
  test(`${mode}: concurrent requests share pending and successful loads`, async () => {
    const h = harness(); let release;
    const gate = new Promise(resolve => { release = resolve; });
    h.respond(async url => { await gate; return ok(url.endsWith("anim_index.json") ? index : clip); });
    const pending = Array.from({ length: 12 }, () => h.load(mode));
    release(); const results = await Promise.all(pending);
    assert.equal(h.calls.length, 2);
    assert.ok(results.every(result => result === results[0]));
    assert.equal(await h.load(mode), results[0]); assert.equal(h.calls.length, 2);
  });
}

test("failed shared index evicts all dependent label and exact entries", async () => {
  const h = harness(); let release;
  const gate = new Promise(resolve => { release = resolve; });
  h.respond(async () => { await gate; throw new TypeError("offline"); });
  const first = [h.load("label"), h.load("exact"), h.assets.loadClip("pl0615", "move")];
  release(); assert.deepEqual(await Promise.all(first), [null, null, null]);
  assert.equal(h.calls.length, 1);
  h.respond(url => ok(url.endsWith("anim_index.json") ? index : clip));
  const recovered = await Promise.all([h.load("label"), h.load("exact"), h.assets.loadClip("pl0615", "move")]);
  assert.ok(recovered.every(value => value instanceof THREE.AnimationClip));
  assert.equal(h.calls.filter(url => url.endsWith("anim_index.json")).length, 2);
  assert.equal(h.calls.length, 5);
});

test("concurrent failed bank requests deduplicate and can retry", async () => {
  const h = harness(); h.respond(url => url.endsWith("anim_index.json") ? ok(index) : failures.network());
  assert.deepEqual(await Promise.all([h.load("label"), h.load("label")]), [null, null]);
  assert.equal(h.calls.length, 2);
  h.respond(() => ok(clip));
  const recovered = await Promise.all([h.load("label"), h.load("label")]);
  assert.ok(recovered[0] instanceof THREE.AnimationClip);
  assert.equal(recovered[0], recovered[1]); assert.equal(h.calls.length, 3);
});

test("internal form index retains the group-2 filter", async () => {
  const h = harness(); h.respond(url => ok(url.endsWith("anim_index.json") ? {
    borg: "pl0604", banks: [...index.banks, { ...index.banks[0], group: 2 }],
  } : clip));
  assert.equal(await h.assets.loadClipByStreamRef("pl0605", { group: 0, slot: 0 }), null);
  assert.ok(await h.assets.loadClipByStreamRef("pl0605", { group: 2, slot: 0 }) instanceof THREE.AnimationClip);
  assert.equal(h.calls.length, 2);
  assert.ok(h.calls.every(url => url.includes("/pl0604/")));
});

for (const mode of ["label", "exact"]) {
  test(`${mode}: parseable index without a banks array can recover`, async () => {
    const h = harness(); h.respond(() => ok({ borg: "pl0615" }));
    assert.equal(await h.load(mode), null);
    h.respond(url => ok(url.endsWith("anim_index.json") ? index : clip));
    assert.ok(await h.load(mode) instanceof THREE.AnimationClip);
    assert.equal(h.calls.length, 3);
  });
}
