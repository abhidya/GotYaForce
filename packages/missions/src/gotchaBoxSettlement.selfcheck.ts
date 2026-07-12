import type { BattleDefeat } from "@gf/combat";

import {
  GOTCHA_BOX_STATE_VERSION,
  createGotchaBoxSettlement,
  createMemoryGotchaBoxPersistence,
  type GotchaBoxPersistence,
  type GotchaBoxState,
} from "./gotchaBoxSettlement.js";

function assert(condition: unknown, message: string): asserts condition {
  if (!condition) throw new Error(`Gotcha-Box settlement selfcheck failed: ${message}`);
}

function defeat(overrides: Partial<BattleDefeat> = {}): BattleDefeat {
  return { borgId: "pl0000", colorVariant: 0, victimTeam: 1, killerTeam: 0, ...overrides };
}

function countingPersistence(initial?: GotchaBoxState): GotchaBoxPersistence & { saves: number } {
  const memory = createMemoryGotchaBoxPersistence(initial);
  return {
    saves: 0,
    load: memory.load,
    save(state): void {
      this.saves += 1;
      memory.save(state);
    },
  };
}

const initial: GotchaBoxState = {
  version: GOTCHA_BOX_STATE_VERSION,
  pool: { entries: [
    { borgId: "pl0000", colorVariant: 0, points: 23 },
    { borgId: "pl0000", colorVariant: 1, points: 31 },
  ] },
  collection: [],
};
const winStore = countingPersistence(initial);
let clockCalls = 0;
const settlement = createGotchaBoxSettlement({
  persistence: winStore,
  rng: () => 0,
  clock: () => { clockCalls += 1; return 123456; },
});
assertThrows(() => settlement.win([]), "not active", "settle without begin");
settlement.begin();
assertThrows(() => settlement.begin(), "already active", "double begin");
const drops = settlement.win([
  defeat(),
  defeat({ colorVariant: 1 }),
  defeat({ borgId: "pl0001", victimTeam: 1, killerTeam: 1 }),
  { borgId: "pl0002", colorVariant: 0, victimTeam: 1 },
  defeat({ borgId: "pl0003", victimTeam: 0, killerTeam: 1 }),
]);
assert(drops.length === 2, "only qualifying enemy victims killed by the player team accrue");
assert(clockCalls === 1, "one settlement reads the clock once");
const won = winStore.load();
assert(won.collection.length === 2, "drops append to the collection");
assert(won.collection.every((drop) => drop.collectedAt === 123456), "all drops share one timestamp");
assert(!won.pool.entries.some((entry) => ["pl0001", "pl0002", "pl0003"].includes(entry.borgId)), "nonqualifying defeats are ignored");
assertThrows(() => settlement.win([]), "not active", "repeated settlement");

const customTeamStore = countingPersistence({
  version: GOTCHA_BOX_STATE_VERSION,
  pool: { entries: [{ borgId: "pl0000", colorVariant: 0, points: 23 }] },
  collection: [],
});
const customTeams = createGotchaBoxSettlement({
  persistence: customTeamStore,
  rng: () => 0,
  playerTeam: 4,
  victimTeam: 7,
});
customTeams.begin();
const customDrops = customTeams.win([
  defeat(),
  defeat({ victimTeam: 7, killerTeam: 4 }),
]);
assert(customDrops.length === 1, "injected player/victim teams replace the default team facts");

const noDropStore = countingPersistence();
const noDrop = createGotchaBoxSettlement({ persistence: noDropStore, rng: () => 0 });
noDrop.begin();
assert(noDrop.win([defeat()]).length === 0, "a below-threshold win has no drop");
assert(noDropStore.saves === 1, "a no-drop win still commits pool progress");
assert(noDropStore.load().pool.entries[0]?.points === 1, "a no-drop win preserves accrued points");

for (const outcome of ["loss", "abandon"] as const) {
  const before: GotchaBoxState = {
    version: GOTCHA_BOX_STATE_VERSION,
    pool: { entries: [{ borgId: "pl0004", colorVariant: 2, points: 77 }] },
    collection: [{ borgId: "pl0000", colorVariant: 0, kind: "unit", partIndex: 0, collectedAt: 9 }],
  };
  const store = countingPersistence(before);
  const transaction = createGotchaBoxSettlement({ persistence: store, rng: () => 0 });
  transaction.begin();
  transaction.revert();
  assert(JSON.stringify(store.load()) === JSON.stringify(before), `${outcome} restores the exact pre-battle state`);
  assertThrows(() => transaction.revert(), "not active", `${outcome} cannot repeat settlement`);
}

const isolatedSeed = initial;
const isolated = createMemoryGotchaBoxPersistence(isolatedSeed);
isolatedSeed.pool.entries[0]!.points = 999;
const firstLoad = isolated.load();
assert(firstLoad.pool.entries[0]?.points === 23, "memory adapter isolates its initial value");
firstLoad.pool.entries[0]!.points = 888;
assert(isolated.load().pool.entries[0]?.points === 23, "memory adapter load returns an isolated copy");
isolated.save(firstLoad);
firstLoad.pool.entries[0]!.points = 777;
assert(isolated.load().pool.entries[0]?.points === 888, "memory adapter save copies its input");

console.log("Gotcha-Box settlement selfcheck PASS: lifecycle, default/injected-team filtering, commits/reverts, timestamp, adapter isolation");

function assertThrows(run: () => unknown, fragment: string, label: string): void {
  try {
    run();
  } catch (error) {
    assert(error instanceof Error && error.message.includes(fragment), `${label} reports a defined ordering error`);
    return;
  }
  throw new Error(`Gotcha-Box settlement selfcheck failed: ${label} must throw`);
}
