#!/usr/bin/env node
import assert from "node:assert/strict";
import { readFileSync } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import ts from "typescript";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const mainSource = readFileSync(path.join(root, "apps/game/src/main.ts"), "utf8");
const initializationSource = readFileSync(path.join(root, "apps/game/src/sim/gotchaBoxBattleInitialization.ts"), "utf8");
const source = readFileSync(path.join(root, "apps/game/src/sim/getStorage.ts"), "utf8")
  .replace(/^import \{[\s\S]*?\} from "@gf\/missions";\s*/m, [
    "const GOTCHA_BOX_STATE_VERSION = 1;",
    "const createGotchaBoxState = () => ({ version: 1, pool: { entries: [] }, collection: [] });",
  ].join("\n"));
const compiled = ts.transpileModule(source, {
  compilerOptions: { module: ts.ModuleKind.ES2022, target: ts.ScriptTarget.ES2022 },
  reportDiagnostics: true,
});
assert.deepEqual(compiled.diagnostics ?? [], []);
const moduleUrl = `data:text/javascript;base64,${Buffer.from(compiled.outputText).toString("base64")}`;
const { createBrowserGotchaBoxPersistence, GOTCHA_BOX_STORAGE_KEY } = await import(moduleUrl);

assert.match(mainSource, /await initializeGotchaBoxBattle\(/, "enterBattle uses the guarded initialization helper");
const initializationCompiled = ts.transpileModule(initializationSource, {
  compilerOptions: { module: ts.ModuleKind.ES2022, target: ts.ScriptTarget.ES2022 },
  reportDiagnostics: true,
});
assert.deepEqual(initializationCompiled.diagnostics ?? [], []);
const initializationUrl = `data:text/javascript;base64,${Buffer.from(initializationCompiled.outputText).toString("base64")}`;
const { initializeGotchaBoxBattle } = await import(initializationUrl);

const bootstrapFailure = new Error("bootstrap failed");
let begins = 0;
let reverts = 0;
await assert.rejects(
  initializeGotchaBoxBattle(
    async () => { throw bootstrapFailure; },
    { begin() { begins += 1; }, revert() { reverts += 1; } },
    () => { throw new Error("must not initialize"); },
  ),
  (error) => error === bootstrapFailure,
);
assert.equal(begins, 0, "bootstrap failure never begins settlement");
assert.equal(reverts, 0, "bootstrap failure has no transaction to revert");

const initializationFailure = new Error("post-begin initialization failed");
await assert.rejects(
  initializeGotchaBoxBattle(
    async () => ({ battle: "ready" }),
    { begin() { begins += 1; }, revert() { reverts += 1; } },
    async () => { await Promise.resolve(); throw initializationFailure; },
  ),
  (error) => error === initializationFailure,
);
assert.equal(begins, 1, "successful bootstrap begins settlement once");
assert.equal(reverts, 1, "post-begin initialization failure reverts settlement once");

class FakeStorage {
  values = new Map();
  writes = [];
  getItem(key) { return this.values.get(key) ?? null; }
  setItem(key, value) { this.values.set(key, value); this.writes.push([key, value]); }
}

const legacy = new FakeStorage();
legacy.values.set("gf-get-pool-v1", JSON.stringify({ entries: [{ borgId: "pl0000", colorVariant: 0, points: 12 }] }));
legacy.values.set("gf-get-collection-v1", JSON.stringify([{ borgId: "pl0001", colorVariant: 1, kind: "unit", partIndex: 0, collectedAt: 7 }]));
const migrated = createBrowserGotchaBoxPersistence(legacy).load();
assert.equal(migrated.pool.entries[0].points, 12);
assert.equal(migrated.collection[0].collectedAt, 7);
assert.equal(legacy.writes.length, 1, "legacy migration writes one combined value");
assert.equal(legacy.writes[0][0], GOTCHA_BOX_STORAGE_KEY);
assert.deepEqual(JSON.parse(legacy.writes[0][1]), migrated);

const onlyPool = new FakeStorage();
onlyPool.values.set("gf-get-pool-v1", JSON.stringify({ entries: [{ borgId: "pl0002", colorVariant: 2, points: 14 }] }));
const migratedPool = createBrowserGotchaBoxPersistence(onlyPool).load();
assert.equal(migratedPool.pool.entries[0].points, 14, "pool-only legacy data migrates");
assert.deepEqual(migratedPool.collection, [], "pool-only migration supplies an empty collection");
assert.equal(onlyPool.writes.length, 1);

const onlyCollection = new FakeStorage();
onlyCollection.values.set("gf-get-collection-v1", JSON.stringify([
  { borgId: "pl0003", colorVariant: 3, kind: "parts", partIndex: 2, partsCount: 3, collectedAt: 11 },
]));
const migratedCollection = createBrowserGotchaBoxPersistence(onlyCollection).load();
assert.deepEqual(migratedCollection.pool.entries, [], "collection-only migration supplies an empty pool");
assert.equal(migratedCollection.collection[0].partIndex, 2, "collection-only legacy data migrates");
assert.equal(onlyCollection.writes.length, 1);

const current = new FakeStorage();
current.values.set(GOTCHA_BOX_STORAGE_KEY, JSON.stringify({ version: 1, pool: { entries: [] }, collection: [] }));
current.values.set("gf-get-pool-v1", JSON.stringify({ entries: [{ borgId: "ignored", colorVariant: 0, points: 1 }] }));
assert.equal(createBrowserGotchaBoxPersistence(current).load().pool.entries.length, 0, "new value takes precedence over legacy");
assert.equal(current.writes.length, 0);

for (const invalid of ["bad json", JSON.stringify({ version: 1, pool: { entries: [{ borgId: "x", colorVariant: 9, points: 1 }] }, collection: [] })]) {
  const fake = new FakeStorage();
  fake.values.set(GOTCHA_BOX_STORAGE_KEY, invalid);
  assert.deepEqual(createBrowserGotchaBoxPersistence(fake).load().pool.entries, [], "invalid state degrades to fresh");
}

const malformedDrops = [
  { borgId: "pl0000", colorVariant: 0, kind: "unit", partIndex: 1, collectedAt: 1 },
  { borgId: "pl0000", colorVariant: 0, kind: "unit", partIndex: 0, partsCount: 2, collectedAt: 1 },
  { borgId: "pl0000", colorVariant: 0, kind: "parts", partIndex: 1, collectedAt: 1 },
  { borgId: "pl0000", colorVariant: 0, kind: "parts", partIndex: 0, partsCount: 2, collectedAt: 1 },
  { borgId: "pl0000", colorVariant: 0, kind: "parts", partIndex: 3, partsCount: 2, collectedAt: 1 },
  { borgId: "pl0000", colorVariant: 0, kind: "parts", partIndex: 1, partsCount: 6, collectedAt: 1 },
  { borgId: "pl0000", colorVariant: 0, kind: "parts", partIndex: 1, partsCount: 999, collectedAt: 1 },
];
for (const malformed of malformedDrops) {
  const invalidCurrent = new FakeStorage();
  invalidCurrent.values.set(GOTCHA_BOX_STORAGE_KEY, JSON.stringify({
    version: 1,
    pool: { entries: [{ borgId: "pl0004", colorVariant: 0, points: 5 }] },
    collection: [malformed],
  }));
  const currentFallback = createBrowserGotchaBoxPersistence(invalidCurrent).load();
  assert.deepEqual(currentFallback, { version: 1, pool: { entries: [] }, collection: [] }, "malformed current drop degrades the whole state to fresh");

  const invalidLegacy = new FakeStorage();
  invalidLegacy.values.set("gf-get-pool-v1", JSON.stringify({ entries: [{ borgId: "pl0004", colorVariant: 0, points: 5 }] }));
  invalidLegacy.values.set("gf-get-collection-v1", JSON.stringify([malformed]));
  const legacyFallback = createBrowserGotchaBoxPersistence(invalidLegacy).load();
  assert.deepEqual(legacyFallback, { version: 1, pool: { entries: [] }, collection: [] }, "malformed legacy drop degrades to fresh");
  assert.equal(invalidLegacy.writes.length, 0, "malformed legacy data is not migrated");
}

const unavailable = { getItem() { throw new Error("disabled"); }, setItem() { throw new Error("disabled"); } };
const fallback = createBrowserGotchaBoxPersistence(unavailable);
assert.doesNotThrow(() => fallback.load());
const state = fallback.load();
state.pool.entries.push({ borgId: "pl0002", colorVariant: 0, points: 3 });
assert.doesNotThrow(() => fallback.save(state));
assert.equal(fallback.load().pool.entries[0].points, 3, "failed storage retains an in-memory session");

const atomic = new FakeStorage();
const adapter = createBrowserGotchaBoxPersistence(atomic);
const combined = adapter.load();
combined.pool.entries.push({ borgId: "pl0003", colorVariant: 0, points: 4 });
combined.collection.push({ borgId: "pl0003", colorVariant: 0, kind: "unit", partIndex: 0, collectedAt: 8 });
adapter.save(combined);
assert.equal(atomic.writes.length, 1, "one commit performs one storage write");
assert.deepEqual(JSON.parse(atomic.writes[0][1]), combined, "the write contains pool and collection together");

console.log("Gotcha-Box browser storage selfcheck PASS: initialization cleanup, strict validation, migration, fallback, atomic write");
