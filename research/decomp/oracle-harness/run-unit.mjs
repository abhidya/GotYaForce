#!/usr/bin/env node
// run-unit.mjs — generic differential-oracle harness entry point.
// Oracle workstream Phase 1 (research/tools/OGhidra/docs/oracle-workstream-plan.md
// §3.1/§3.2/§3.3): drives one wasm unit against its TS reference per its spec module,
// replaying a pinned corpus fixture, and writes the machine-readable verdict to
// research/decomp/data/oracle-results/<unit>.json.
//
// Usage:
//   node run-unit.mjs --unit damage-core [--n 20000] [--replay <fixture>]
// Env:
//   ORACLE_WASM             override the unit wasm path (driver substitutes {wasm})
//   ORACLE_RESULTS_DIR      override the result-artifact directory (tests/rehearsals
//                           point this at a scratch dir so the tracked artifact under
//                           research/decomp/data/oracle-results/ is never clobbered
//                           by a non-verification run)
//   ORACLE_FLIP_ARENA_BYTE  hex address whose arena byte is XOR'd 0xff — the
//                           deliberate-red rehearsal knob (gate term 6). A rehearsal
//                           run NEVER passes: the verdict is forced to "fail", the
//                           exit code is nonzero, and the result JSON is stamped
//                           with a `rehearsal` block, so a rehearsal artifact can
//                           never be mistaken for (or committed as) a real verdict —
//                           even if the flipped byte happened to be unread.
//
// Exit-code contract (§3.2, closes F-2): exit 0 iff verdict == "pass" AND the result
// file was written; any exception, malformed spec/fixture, coverage violation, or
// failing function exits nonzero. The final log line, printed ONLY when every
// function passed, is the anchored total (I-5):
//   ORACLE TOTAL functions=<k>/<k> cases=<n> UNEXPLAINED: 0 VERDICT: PASS
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { createHash } from "node:crypto";
import { execSync } from "node:child_process";
import { loadUnit } from "./lib/wasm.mjs";
import { Codec, loadFieldMap, BlockedCodecError } from "./lib/codec.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "..", "..", "..");
const sha256 = (buf) => createHash("sha256").update(buf).digest("hex");

// ---- args ----
const args = process.argv.slice(2);
const argOf = (name) => {
  const i = args.indexOf(name);
  return i >= 0 && i + 1 < args.length ? args[i + 1] : null;
};
const unitName = argOf("--unit");
if (!unitName || !/^[\w-]+$/.test(unitName)) {
  console.error("usage: node run-unit.mjs --unit <name> [--n N] [--replay <fixture>]");
  process.exit(2);
}

const fail = (msg, code = 1) => { console.error(`ORACLE HARNESS ERROR: ${msg}`); process.exit(code); };

try {
  await main();
} catch (e) {
  if (e instanceof BlockedCodecError) {
    console.error(`ORACLE TOTAL VERDICT: BLOCKED_CODEC (${e.message})`);
    writeResultStub("blocked_codec", e.message);
    process.exit(3);
  }
  console.error(e.stack ?? String(e));
  process.exit(1);
}

function resultsDir() {
  return process.env.ORACLE_RESULTS_DIR
    ? path.resolve(process.env.ORACLE_RESULTS_DIR)
    : path.join(root, "research", "decomp", "data", "oracle-results");
}

function writeResultStub(verdict, detail) {
  try {
    const outDir = resultsDir();
    fs.mkdirSync(outDir, { recursive: true });
    fs.writeFileSync(path.join(outDir, `${unitName}.json`),
      JSON.stringify({ result_schema: 1, unit: unitName, generated_at: new Date().toISOString(), verdict, detail }, null, 1) + "\n");
  } catch { /* stub write is best-effort; the nonzero exit already fails the run */ }
}

async function main() {
  const specPath = path.join(here, "specs", `${unitName}.spec.mjs`);
  if (!fs.existsSync(specPath)) fail(`no spec module at ${specPath}`);
  const spec = await import(`./specs/${unitName}.spec.mjs`);
  const meta = spec.meta;

  const wasmPath = process.env.ORACLE_WASM ?? path.resolve(here, meta.wasmDefault);
  const arenaPath = path.resolve(here, meta.arena);
  const fixturePath = argOf("--replay") ?? path.resolve(here, meta.fixture);
  const flipEnv = process.env.ORACLE_FLIP_ARENA_BYTE;
  const flipByte = flipEnv ? Number.parseInt(flipEnv, 16) : null;
  if (flipByte != null) console.log(`DELIBERATE-RED REHEARSAL: arena byte 0x${flipByte.toString(16)} flipped`);

  const { ex, u8, dv, wasmBytes } = await loadUnit({
    wasmPath, arenaPath, makeShims: spec.makeShims, flipByte,
  });
  const arena = JSON.parse(fs.readFileSync(arenaPath, "utf8"));
  const arenaSegments = arena.segments.map((s) => ({ addr: s.addr, size: Buffer.from(s.b64, "base64").length }));

  const fieldMapPath = path.join(here, "actor-field-map.json");
  const fieldMap = loadFieldMap(fieldMapPath);
  // F4: the field map must describe the actor.ts that exists NOW. Hash with
  // normalized line endings (CRLF checkouts must not defeat the binding) and
  // refuse to run against a drifted source.
  const actorTsPath = path.join(root, "packages", "combat", "src", "rom", "actor.ts");
  const actorNormalized = fs.readFileSync(actorTsPath).toString("utf8").replace(/\r\n/g, "\n");
  if (sha256(Buffer.from(actorNormalized, "utf8")) !== fieldMap.raw.source_sha256) {
    fail("actor-field-map.json is stale: source_sha256 does not match packages/combat/src/rom/actor.ts — regenerate with gen_actor_field_map.py");
  }

  // ---- fixture load + integrity binding (§6 Phase 1 / [R2]) ----
  const fixtureRaw = fs.readFileSync(fixturePath);
  const lines = fixtureRaw.toString("utf8").split("\n").filter((l) => l.length > 0);
  const header = JSON.parse(lines[0]);
  if (header.kind !== "header" || header.fixture_schema !== 1) {
    fail("fixture has no valid header record — an unbound corpus file proves nothing");
  }
  if (header.unit !== unitName) fail(`fixture is for unit ${header.unit}, not ${unitName}`);
  const committedLogPath = path.join(root, "research", "decomp", "port-units", unitName, "oracle.log");
  if (!fs.existsSync(committedLogPath) || sha256(fs.readFileSync(committedLogPath)) !== header.oracle_log_sha256) {
    fail("fixture header's oracle_log_sha256 does not match the committed artifact — refusing replay");
  }

  const nArg = argOf("--n");
  if (nArg != null && Number(nArg) !== header.counts.case) {
    fail(`--n ${nArg} != fixture main-corpus count ${header.counts.case} (replay is exact, not resizable)`);
  }

  const makeCodec = (sentinel) => new Codec({
    u8, dv, fieldMap, regions: meta.regions, arenaSegments, sentinel,
  });
  const codec = makeCodec(0xa5);
  const runner = spec.createRunner({ ex, u8, dv });

  // ---- replay ----
  const perFn = new Map();
  for (const f of meta.functions) {
    perFn.set(f.name, { name: f.name, rounding_bound: f.rounding_bound ?? 0,
      cases: 0, exact: 0, rounding_explained: 0, unexplained: 0 });
  }
  const coverage = { offsets_read_unwritten: 0, sentinel_reads_detected: false, stray_writes: [] };
  const unexplainedDumps = [];
  const classByN = new Map(); // main-corpus outcome per case index (for "class" verification)
  const classMismatches = [];
  const probeRecords = []; // records re-run under a different sentinel (F-1 probe)
  const perKindCount = { case: 0, cat: 0, hp: 0, unitb: 0 };

  for (let li = 1; li < lines.length; li++) {
    const rec = JSON.parse(lines[li]);
    if (rec.kind === "class") {
      const got = classByN.get(rec.n);
      if (got !== rec.class) classMismatches.push({ n: rec.n, fixture: rec.class, replay: got ?? "(missing)" });
      continue;
    }
    perKindCount[rec.kind] = (perKindCount[rec.kind] ?? 0) + 1;
    const out = runner.handleRecord(codec, rec);
    const fn = perFn.get(out.fn);
    if (!fn) fail(`spec returned unknown function ${out.fn}`);
    fn.cases++;
    if (out.cls === "exact") fn.exact++;
    else if (out.cls === "rounding") fn.rounding_explained++;
    else { fn.unexplained++; if (unexplainedDumps.length < 8 && out.dump) unexplainedDumps.push({ fn: out.fn, ...out.dump }); }
    if (rec.kind === "case") classByN.set(rec.n, out.cls);
    if (out.audit.missing > 0) {
      coverage.offsets_read_unwritten += out.audit.missing;
      fail(`declared-read offsets unwritten (${out.audit.missing} bytes, first: ${out.audit.missingAddrs.map((a) => "0x" + a.toString(16)).join(",")}) — invalid run`);
    }
    if (out.post.strayWrites.length > 0) {
      for (const a of out.post.strayWrites) if (coverage.stray_writes.length < 16) coverage.stray_writes.push("0x" + a.toString(16));
    }
    if (out.post.writeBackMismatches && out.post.writeBackMismatches.length > 0 && out.cls === "exact") {
      fail(`write-back mismatch escaped classification for ${out.fn} case ${rec.n ?? "?"}`);
    }
    // sentinel-probe sample: first 64 main cases + 16 of each other kind + every non-exact
    const k = perKindCount[rec.kind];
    if ((rec.kind === "case" && k <= 64) || (rec.kind !== "case" && k <= 16) || out.cls !== "exact") {
      probeRecords.push({ rec, cls: out.cls });
    }
  }

  // fixture count integrity
  for (const [kind, want] of Object.entries(header.counts)) {
    if ((perKindCount[kind] ?? 0) !== want) fail(`fixture count mismatch for ${kind}: ${perKindCount[kind] ?? 0} != ${want}`);
  }
  if (classMismatches.length > 0) {
    for (const m of classMismatches.slice(0, 8)) console.log(`  CLASS MISMATCH n=${m.n}: fixture=${m.fixture} replay=${m.replay}`);
  }

  // ---- sentinel probe pass (F-1: detect reads of unwritten scratch) ----
  const probeCodec = makeCodec(0x5a);
  for (const { rec, cls } of probeRecords) {
    const out = runner.handleRecord(probeCodec, rec);
    if (out.cls !== cls) { coverage.sentinel_reads_detected = true; break; }
  }

  // ---- verdicts ----
  let totalCases = 0, totalUnexplained = 0;
  const fnResults = [];
  for (const f of meta.functions) {
    const s = perFn.get(f.name);
    totalCases += s.cases;
    totalUnexplained += s.unexplained;
    const roundingFrac = s.cases > 0 ? s.rounding_explained / s.cases : 0;
    let verdict = "pass";
    if (s.unexplained > 0) verdict = "fail";
    else if (roundingFrac > s.rounding_bound) verdict = "fail_rounding_bound";
    fnResults.push({ name: s.name, cases: s.cases, exact: s.exact,
      rounding_explained: s.rounding_explained, unexplained: s.unexplained,
      reference: f.reference ?? null, verdict });
  }
  const coverageClean = coverage.offsets_read_unwritten === 0
    && !coverage.sentinel_reads_detected && coverage.stray_writes.length === 0;
  // F2: a rehearsal run can NEVER pass — even if the flipped byte was unread.
  const allPass = fnResults.every((f) => f.verdict === "pass") && coverageClean
    && classMismatches.length === 0 && flipByte == null;

  // ---- log (per-function lines + coverage + anchored total, I-5) ----
  for (const f of fnResults) {
    console.log(`[${f.name}] cases=${f.cases} exact=${f.exact} rounding_explained=${f.rounding_explained} unexplained=${f.unexplained} verdict: ${f.verdict}`);
  }
  console.log(`coverage: offsets_read_unwritten=${coverage.offsets_read_unwritten} sentinel_reads=${coverage.sentinel_reads_detected ? "DETECTED" : "none"} stray_writes=${coverage.stray_writes.length} class_mismatches=${classMismatches.length}`);
  const k = fnResults.filter((f) => f.verdict === "pass").length;
  if (allPass) {
    console.log(`ORACLE TOTAL functions=${k}/${fnResults.length} cases=${totalCases} UNEXPLAINED: 0 VERDICT: PASS`);
  } else {
    console.log(`ORACLE TOTAL functions=${k}/${fnResults.length} cases=${totalCases} UNEXPLAINED: ${totalUnexplained} VERDICT: FAIL`);
  }

  // ---- result artifact (§3.2) ----
  let gitRev = "unknown";
  try { gitRev = execSync("git rev-parse HEAD", { cwd: root }).toString().trim(); } catch { /* evidence field only */ }
  const result = {
    result_schema: 1,
    unit: unitName,
    generated_at: new Date().toISOString(),
    harness: { entry: "research/decomp/oracle-harness/run-unit.mjs", git_rev: gitRev },
    wasm: { path: wasmPath, sha256: sha256(wasmBytes) },
    corpus: { mode: "replay", file: path.relative(root, fixturePath).replace(/\\/g, "/"),
              sha256: sha256(fixtureRaw), n: totalCases },
    spec_sha256: sha256(fs.readFileSync(specPath)),
    reference_kind: meta.reference_kind,
    references: meta.references,
    // F5: per-function reference annotation — fnResults carry each function's own
    // reference (see spec meta.functions[].reference), not just the unit-level kind.
    functions: fnResults,
    coverage: {
      offsets_read_unwritten: coverage.offsets_read_unwritten,
      sentinel_reads_detected: coverage.sentinel_reads_detected,
      stray_writes: coverage.stray_writes,
      class_mismatches: classMismatches.slice(0, 8),
    },
    unexplained_cases: unexplainedDumps,
    verdict: allPass ? "pass" : "fail",
  };
  // F2: a rehearsal artifact is stamped as such — never mistakable for a real verdict.
  if (flipByte != null) {
    result.rehearsal = { flip_arena_byte: "0x" + flipByte.toString(16), note: "deliberate-red rehearsal — verdict forced to fail; not a verification run" };
  }
  const outDir = resultsDir();
  fs.mkdirSync(outDir, { recursive: true });
  fs.writeFileSync(path.join(outDir, `${unitName}.json`), JSON.stringify(result, null, 1) + "\n");
  process.exitCode = allPass ? 0 : 1;
}
