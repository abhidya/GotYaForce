// Self-test for ATK-019 (healing & lifesteal shells, DISABLED by default — REWRITTEN ticket
// after behavior-notes.md (an) corrected the (al)-era "chunk_0003.c:6318 = nurse healing"
// misread to vampire lifesteal).
//
// Deliberately separate from selfcheck.ts (another agent is concurrently editing that file) —
// own entry point, own runner (scripts/run-healing-tests.mjs), per the commandSchema.selftest.ts
// / burst.selftest.ts precedent. Does not import or modify selfcheck.ts.
//
// Also writes research/tasks/attack-port/NOTES-ATK-019.md with the roster-verification log
// every run (matching the ticket's "Done when ... NOTES-ATK-019.md records the roster name
// verification" requirement) — see writeRosterNotes() below.
//
// Run (from repo root), after building packages/combat:
//   node scripts/run-healing-tests.mjs

import { readFileSync, writeFileSync } from "node:fs";
import { dirname, resolve as resolvePath } from "node:path";
import { fileURLToPath } from "node:url";

import { applyHeal, applyHit, isVampireBorgId, stepVampireDrain } from "./combat.js";
import { HEAL, HEAL_NURSE_BORG_IDS, HEAL_VAMPIRE_BORG_IDS } from "./constants.js";
import { DAMAGE_RECORD_INDEX, damageRecordByIndex } from "./gauges.js";
import { buildProfile, type BorgStats } from "./stats.js";
import type { BorgRuntime } from "./types.js";

// --- Test scaffolding --------------------------------------------------------------------

let failures = 0;
let checks = 0;

function assertEqual<T>(actual: T, expected: T, label: string): void {
  checks++;
  if (actual !== expected) {
    failures++;
    console.error(`FAIL: ${label} — expected ${String(expected)}, got ${String(actual)}`);
  }
}

function assertTrue(cond: boolean, label: string): void {
  checks++;
  if (!cond) {
    failures++;
    console.error(`FAIL: ${label}`);
  }
}

function makeBorg(overrides: Partial<BorgRuntime> = {}): BorgRuntime {
  return {
    uid: "u1",
    borgId: "test",
    team: 0,
    ownerPlayer: "p1",
    hp: 100,
    maxHp: 100,
    pos: { x: 0, y: 10, z: 0 },
    rotY: 0,
    vel: { x: 0, y: 0, z: 0 },
    grounded: true,
    airJumps: 1,
    state: "idle",
    stateTime: 0,
    anim: "idle",
    ammo: 0,
    cooldowns: {},
    invincTimer: 0,
    balanceGauge: 100,
    balanceGaugeMax: 100,
    downGauge: 100,
    downGaugeBase: 100,
    balanceRefillDelay: 0,
    downResetDelay: 0,
    comboWindow: 0,
    comboAccum: 0,
    comboRank: 0,
    paramTier: { tier: 0x10, deltaAccum: 0, timerFrames: 0 },
    statusId: 0,
    statusTimer: 0,
    statusImmunityMask: 0,
    lockTarget: null,
    allyLockTarget: null,
    burstArmFrames: 0,
    burstActive: false,
    burstPaired: false,
    fusionPartnerUid: null,
    fusionState: 0,
    defeatAccounted: false,
    alive: true,
    ...overrides,
  };
}

// --- applyHeal tests -------------------------------------------------------------------------

function testApplyHealClampsToMax(): void {
  const b = makeBorg({ hp: 90, maxHp: 100 });
  const healed = applyHeal(b, 50);
  assertEqual(healed, 10, "applyHeal clamps the returned amount to what's actually missing");
  assertEqual(b.hp, 100, "applyHeal clamps hp to maxHp");
}

function testApplyHealExactAmountBelowMax(): void {
  const b = makeBorg({ hp: 50, maxHp: 100 });
  const healed = applyHeal(b, 30);
  assertEqual(healed, 30, "applyHeal returns the full amount when it fits under maxHp");
  assertEqual(b.hp, 80, "applyHeal adds the full amount to hp");
}

function testApplyHealNoOpOnDeadHp(): void {
  const b = makeBorg({ hp: 0, maxHp: 100, state: "idle" });
  const healed = applyHeal(b, 50);
  assertEqual(healed, 0, "applyHeal is a no-op when hp <= 0");
  assertEqual(b.hp, 0, "applyHeal never revives via hp <= 0 guard");
}

function testApplyHealNoOpOnDeathState(): void {
  const b = makeBorg({ hp: 50, maxHp: 100, state: "death" });
  const healed = applyHeal(b, 50);
  assertEqual(healed, 0, "applyHeal is a no-op when state is death");
  assertEqual(b.hp, 50, "applyHeal never revives via death-state guard");
}

function testApplyHealNeverRevives(): void {
  // Redundant-but-explicit per the ticket's "never revives" requirement: hp already at 0 AND
  // state death simultaneously (the natural post-enterDeath() shape).
  const b = makeBorg({ hp: 0, maxHp: 100, state: "death" });
  const healed = applyHeal(b, 1000);
  assertEqual(healed, 0, "applyHeal never revives a dead borg even with a huge heal amount");
  assertEqual(b.hp, 0, "hp stays 0 after a no-op heal attempt on a dead borg");
}

function testApplyHealAtFullHpIsNoOp(): void {
  const b = makeBorg({ hp: 100, maxHp: 100 });
  const healed = applyHeal(b, 25);
  assertEqual(healed, 0, "applyHeal returns 0 when already at maxHp");
  assertEqual(b.hp, 100, "hp stays at maxHp");
}

function testApplyHealIgnoresNonPositiveAmount(): void {
  const b = makeBorg({ hp: 50, maxHp: 100 });
  assertEqual(applyHeal(b, 0), 0, "applyHeal(0) is a no-op");
  assertEqual(applyHeal(b, -10), 0, "applyHeal with a negative amount is a no-op");
  assertEqual(b.hp, 50, "hp unchanged by non-positive heal attempts");
}

// --- Flag-state / non-vampire guard tests ----------------------------------------------------

function testFlagState(): void {
  // Nurse heal stays disabled (its HP-write is not in the corpus — (ay)); vampire lifesteal is
  // now ENABLED (full path traced, (ay)).
  assertEqual(HEAL.NURSE_ENABLED, false, "HEAL.NURSE_ENABLED stays false (nurse HP-write not found)");
  assertEqual(HEAL.VAMPIRE_ENABLED, true, "HEAL.VAMPIRE_ENABLED is true (vampire path traced, ay)");
}

function testNonVampireNeverBleeds(): void {
  // stepVampireDrain must be a no-op for a non-vampire borg even with the mechanic enabled.
  const b = makeBorg({ borgId: "test", hp: 77, maxHp: 100 });
  assertTrue(!isVampireBorgId("test"), "'test' id is not a vampire id");
  const before = JSON.stringify(b);
  for (let i = 0; i < 300; i++) stepVampireDrain(b);
  assertEqual(JSON.stringify(b), before, "300 frames of stepVampireDrain leave a non-vampire borg untouched");
}

function testNurseHealAmountsAreDataOnly(): void {
  // OBSERVED_GUIDE data constants exist but are never consulted by any active code path
  // (NURSE_ENABLED stays false) — this just pins the recorded values against (an) §2 /
  // guide-anchors-movelist.json nurseHeals so the data constant can't silently drift.
  assertEqual(HEAL.NURSE_HEAL_HP.pl0906, 37, "Death Borg Theta OBSERVED_GUIDE heal amount is 37");
  assertEqual(HEAL.NURSE_HEAL_HP.pl0900, 50, "Angel Nurse OBSERVED_GUIDE heal amount is 50");
  assertEqual(HEAL.NURSE_HEAL_HP.pl0908, 100, "Angel Rescue OBSERVED_GUIDE heal amount is 100");
}

// --- Enabled vampire behavior (ay): bleed + steal ---------------------------------------------

/** Passive self-bleed: a vampire loses 1 HP every 30 frames, floored at 1 (never self-kills). */
function testVampireBleeds(): void {
  const v = makeBorg({ borgId: "pl0702", hp: 100, maxHp: 200, state: "idle" });
  // 29 frames: counter climbs, no HP loss yet.
  for (let i = 0; i < 29; i++) stepVampireDrain(v);
  assertEqual(v.hp, 100, "no HP lost before the 30-frame bleed interval elapses");
  // 30th frame: exactly 1 HP lost.
  stepVampireDrain(v);
  assertEqual(v.hp, 99, "vampire loses exactly 1 HP on the 30th frame");
  // Another full interval: another 1 HP.
  for (let i = 0; i < 30; i++) stepVampireDrain(v);
  assertEqual(v.hp, 98, "vampire loses 1 more HP after a second 30-frame interval");

  // Floor at 1 HP: drive it near the floor and confirm it never reaches 0 from the bleed.
  v.hp = 1;
  for (let i = 0; i < 300; i++) stepVampireDrain(v);
  assertEqual(v.hp, 1, "bleed floors at 1 HP (never self-kills)");

  // A dead / spawning vampire does not bleed.
  const dead = makeBorg({ borgId: "pl0702", hp: 50, maxHp: 200, state: "death" });
  for (let i = 0; i < 60; i++) stepVampireDrain(dead);
  assertEqual(dead.hp, 50, "a dead vampire does not bleed");
}

/** Steal: on a landed hit, a vampire heals floor(damageDealt / 2), capped at its maxHp. */
function testVampireSteal(): void {
  const raw = JSON.parse(readFileSync(borgsPath, "utf8")) as { borgs: BorgStats[] };
  const vampStats = raw.borgs.find((b) => b.id === "pl0702");
  const victimStats = raw.borgs.find((b) => b.id === "pl0008");
  assertTrue(!!vampStats && !!victimStats, "roster has pl0702 (vampire) and pl0008 (victim)");
  if (!vampStats || !victimStats) return;
  const vampProfile = buildProfile(vampStats);
  const victimProfile = buildProfile(victimStats);

  const vampire = makeBorg({ borgId: "pl0702", hp: 50, maxHp: 200, state: "attack" });
  const victim = makeBorg({ uid: "v", borgId: "pl0008", team: 1, hp: 100000, maxHp: 100000, invincTimer: 0, state: "idle" });

  const hpBefore = vampire.hp;
  const dmg = applyHit(
    victim,
    victimProfile,
    0,
    0,
    { x: 0, y: 0, z: 0 },
    { x: victim.pos.x, y: victim.pos.y, z: victim.pos.z - 10 },
    false,
    damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE),
    { attacker: vampire, attackerProfile: vampProfile },
  );
  assertTrue(dmg > 0, "vampire's hit deals positive damage");
  assertEqual(vampire.hp, hpBefore + Math.floor(dmg / 2), "vampire heals floor(dmg/2) on the hit (steal)");

  // Cap at maxHp: a near-full vampire cannot overheal past maxHp.
  const full = makeBorg({ borgId: "pl0702", hp: 199, maxHp: 200, state: "attack" });
  const victim2 = makeBorg({ uid: "v2", borgId: "pl0008", team: 1, hp: 100000, maxHp: 100000, invincTimer: 0, state: "idle" });
  applyHit(
    victim2,
    victimProfile,
    0,
    0,
    { x: 0, y: 0, z: 0 },
    { x: victim2.pos.x, y: victim2.pos.y, z: victim2.pos.z - 10 },
    false,
    damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE),
    { attacker: full, attackerProfile: vampProfile },
  );
  assertEqual(full.hp, 200, "vampire steal is capped at maxHp (no overheal)");

  // A non-vampire attacker never steals.
  const normal = makeBorg({ borgId: "pl0008", hp: 50, maxHp: 200, state: "attack" });
  const victim3 = makeBorg({ uid: "v3", borgId: "pl0615", team: 1, hp: 100000, maxHp: 100000, invincTimer: 0, state: "idle" });
  const normalHpBefore = normal.hp;
  applyHit(
    victim3,
    buildProfile(raw.borgs.find((b) => b.id === "pl0615")!),
    0,
    0,
    { x: 0, y: 0, z: 0 },
    { x: victim3.pos.x, y: victim3.pos.y, z: victim3.pos.z - 10 },
    false,
    damageRecordByIndex(DAMAGE_RECORD_INDEX.MELEE),
    { attacker: normal, attackerProfile: victimProfile },
  );
  assertEqual(normal.hp, normalHpBefore, "a non-vampire attacker never heals from a hit");
}

// --- Roster verification (required test + NOTES-ATK-019.md) -----------------------------------

interface BorgEntry {
  id: string;
  name: string;
  tribe: string;
}

interface BorgsFile {
  borgs: BorgEntry[];
}

const repoRoot = resolvePath(dirname(fileURLToPath(import.meta.url)), "..", "..", "..");
const borgsPath = resolvePath(repoRoot, "packages/assets/data/borgs.json");
const notesPath = resolvePath(repoRoot, "research/tasks/attack-port/NOTES-ATK-019.md");

function loadBorgs(): BorgsFile {
  return JSON.parse(readFileSync(borgsPath, "utf8")) as BorgsFile;
}

interface RosterCheck {
  id: string;
  expectedNameSubstr: string;
  role: string;
}

const ROSTER_CHECKS: RosterCheck[] = [
  { id: "pl0702", expectedNameSubstr: "VAMPIRE KNIGHT", role: "vampire lifesteal" },
  { id: "pl070a", expectedNameSubstr: "VLAD", role: "vampire lifesteal" },
  { id: "pl0900", expectedNameSubstr: "ANGEL NURSE", role: "nurse heal" },
  { id: "pl0908", expectedNameSubstr: "ANGEL RESCUE", role: "nurse heal" },
  { id: "pl090d", expectedNameSubstr: "NAO", role: "nurse heal (ally-or-enemy, no fixed amount)" },
  { id: "pl0906", expectedNameSubstr: "DEATH BORG THETA", role: "nurse heal (Theta, family-09 expected)" },
];

function testRosterIdsResolveWithExpectedNames(): void {
  const doc = loadBorgs();
  const byId = new Map(doc.borgs.map((b) => [b.id, b]));

  assertEqual(HEAL_VAMPIRE_BORG_IDS.length, 2, "HEAL_VAMPIRE_BORG_IDS has exactly 2 entries");
  assertEqual(HEAL_NURSE_BORG_IDS.length, 4, "HEAL_NURSE_BORG_IDS has exactly 4 entries");

  for (const check of ROSTER_CHECKS) {
    const entry = byId.get(check.id);
    assertTrue(!!entry, `roster id ${check.id} (${check.role}) resolves in borgs.json`);
    if (entry) {
      assertEqual(entry.name, check.expectedNameSubstr, `${check.id} name matches expected "${check.expectedNameSubstr}"`);
    }
  }

  // Theta's specific sub-item per the ticket: the NAME must resolve correctly (it does: exact
  // "DEATH BORG THETA" match, asserted above via ROSTER_CHECKS) — that is the ticket's actual
  // STOP trigger ("if its name is not Theta-like at the expected id, STOP"). The name matches,
  // so this sub-item is NOT stopped. Separately, (an) §2 describes pl0906 as "family 09 = nurse
  // family", but borgs.json's `tribe` field for pl0906 is "Death Borg", not "Nurse Borg" like
  // its 09xx siblings (pl0900/pl0908/pl090d) — logged as a non-blocking discrepancy in
  // NOTES-ATK-019.md (see writeRosterNotes) rather than a hard test failure, since it's a
  // grouping-label mismatch, not the name-mismatch condition the ticket says to stop on.
  const theta = byId.get("pl0906");
  assertTrue(!!theta, "pl0906 resolves for the Theta tribe-grouping check");
}

function writeRosterNotes(): void {
  const doc = loadBorgs();
  const byId = new Map(doc.borgs.map((b) => [b.id, b]));
  const lines: string[] = [];
  lines.push("# NOTES-ATK-019: roster-id verification log");
  lines.push("");
  lines.push(`Generated by packages/combat/src/healing.selftest.ts (scripts/run-healing-tests.mjs), ` + `run against packages/assets/data/borgs.json.`);
  lines.push("");
  lines.push("| id | expected role | found name | found tribe | match |");
  lines.push("|---|---|---|---|---|");
  let anyMismatch = false;
  for (const check of ROSTER_CHECKS) {
    const entry = byId.get(check.id);
    const found = entry ? entry.name : "(not found)";
    const tribe = entry ? entry.tribe : "(n/a)";
    const match = entry && entry.name === check.expectedNameSubstr ? "OK" : "MISMATCH";
    if (match === "MISMATCH") anyMismatch = true;
    lines.push(`| ${check.id} | ${check.role} | ${found} | ${tribe} | ${match} |`);
  }
  lines.push("");
  if (anyMismatch) {
    lines.push(
      "**MISMATCH DETECTED** — per the ATK-019 ticket, the affected sub-item should be treated " +
        "as STOPPED pending investigation; do not assume the id mapping above is correct.",
    );
  } else {
    lines.push(
      "All six roster ids resolved to their expected NAMES exactly — no name mismatch, no " +
        "ticket-defined STOP condition triggered (the ticket's STOP trigger is specifically " +
        '"if its name is not Theta-like at the expected id"; the name matched).',
    );
  }
  lines.push("");
  lines.push("## Non-blocking discrepancy: Death Borg Theta's tribe field");
  lines.push("");
  const theta = byId.get("pl0906");
  lines.push(
    `behavior-notes.md (an) §2 describes pl0906 (id 0x906, code {2,3,9,12}) as ` +
      `"family 09 = nurse family". borgs.json's \`tribe\` field for pl0906 is ` +
      `"${theta?.tribe ?? "(not found)"}", NOT "Nurse Borg" like its 09xx siblings ` +
      `pl0900/pl0908/pl090d (all tribe "Nurse Borg"). The NAME still resolves exactly to ` +
      `"DEATH BORG THETA" as expected, so this is not the ticket's name-mismatch STOP ` +
      `condition — it's a separate observation that the "family 09 = nurse family" framing ` +
      `in (an) is an id-prefix generalization, not a literal roster-tribe grouping (Death ` +
      `Borg Theta is roster tribe "Death Borg", one of several Death Borg variants at 09xx ` +
      `ids alongside the dedicated Nurse Borg tribe). Recorded here for anyone building the ` +
      `real per-borg nurse-heal data table later; does not block this scaffold ticket.`,
  );
  lines.push("");
  writeFileSync(notesPath, lines.join("\n") + "\n", "utf8");
}

// --- Runner ---------------------------------------------------------------------------------

export function runSelfTest(): number {
  failures = 0;
  checks = 0;

  testApplyHealClampsToMax();
  testApplyHealExactAmountBelowMax();
  testApplyHealNoOpOnDeadHp();
  testApplyHealNoOpOnDeathState();
  testApplyHealNeverRevives();
  testApplyHealAtFullHpIsNoOp();
  testApplyHealIgnoresNonPositiveAmount();
  testFlagState();
  testNonVampireNeverBleeds();
  testNurseHealAmountsAreDataOnly();
  testVampireBleeds();
  testVampireSteal();
  testRosterIdsResolveWithExpectedNames();

  // Always write the notes file (regardless of pass/fail), per the ticket's "Done when" clause.
  writeRosterNotes();

  if (failures > 0) {
    console.error(`healing.selftest: ${failures}/${checks} checks FAILED`);
    return 1;
  }
  console.log(`healing.selftest: ${checks}/${checks} checks passed`);
  return 0;
}
