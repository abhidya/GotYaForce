import { battleStateForSelfcheck, createBattle } from "./battle.js";
import { applyHit, stepHitDrain } from "./combat.js";
import { familyDamageRecordForBorg } from "./familyDamageData.js";
import { statusImmunityMasksForBorgId } from "./movementData.js";
import { buildProfile, type BorgStats } from "./stats.js";
import type { DamageRecord } from "./gauges.js";
import borgsData from "../../assets/data/borgs.json" with { type: "json" };

function assert(value: unknown, message: string): void {
  if (!value) throw new Error(`[healingContact] ${message}`);
}
const stats = (borgsData as { borgs: BorgStats[] }).borgs;

/** Resolver contract tests; nurseBattle.selftest covers the actual input/stream/HIT path. */
export function runHealingContactSelfTest(): void {
  for (const [id, index, amount] of [
    ["pl0900", 3, 200], ["pl0900", 4, 200],
    ["pl0908", 7, 400], ["pl0908", 8, 400],
    ["pl090d", 3, 200], ["pl090d", 4, 200],
  ] as const) {
    const battle = createBattle({ stageId: "st00", bounds: { x: 10000, z: 10000 }, forces: [
      { team: 0, ownerPlayer: "p1", borgIds: [id] },
      { team: 1, ownerPlayer: "p2", borgIds: ["pl0615"] },
    ] }, stats);
    const state = battleStateForSelfcheck(battle);
    const telemetry = state.telemetry!;
    const owner = state.borgs.find(b => b.team === 0)!;
    const target = state.borgs.find(b => b.team === 1)!;
    const originalId = target.borgId;
    const ownerProfile = buildProfile(stats.find(b => b.id === id)!);
    const targetProfile = buildProfile(stats.find(b => b.id === originalId)!);
    const record = familyDamageRecordForBorg(id, index)!;
    assert(record.hpDamage === amount && (record.flagsA & 2) !== 0, `${id}/${index} record binding`);
    function reset() {
      owner.alive = target.alive = true;
      owner.state = target.state = "idle";
      owner.invincTimer = target.invincTimer = 0;
      target.borgId = originalId;
      target.team = owner.team;
      target.maxHp = 1000;
      target.hp = 100;
      target.balanceGauge = target.balanceGaugeMax = 500;
      target.downGauge = target.downGaugeBase = 500;
      target.comboAccum = target.comboRank = 0;
      target.freezeFrames = owner.freezeFrames = 0;
      target.balanceRefillDelay = target.downResetDelay = target.comboWindow = 0;
      target.hitDrainFrames = 0;
      target.targetEligibility83 = 0;
    }
    function connect(r: DamageRecord = record) {
      return applyHit(target, targetProfile, 9999, 1, { x: 1, y: 0, z: 0 }, owner.pos, false, r,
        { attacker: owner, attackerProfile: ownerProfile, damageScale: 99 },
        { telemetry: telemetry, burstMeters: state.burstMeterByPlayer, cpuHalvingEnabled: true });
    }
    reset();
    const damageBefore = telemetry.damageByTeam[owner.team] ?? 0;
    const hitsBefore = telemetry.hitsByTeam[owner.team] ?? 0;
    assert(connect() === -amount && target.hp === 100 + amount, `${id}/${index} full allied heal`);
    assert(telemetry.damageByTeam[owner.team] === damageBefore, "healing reduced damage telemetry");
    assert(telemetry.hitsByTeam[owner.team] === hitsBefore + 1, "healing skipped connection telemetry");
    assert(target.balanceRefillDelay === 60 && target.downResetDelay === 60 && target.comboWindow === 60,
      "healing skipped nonlethal gauge windows");
    assert(target.balanceGauge === 500 && target.comboAccum === 0, "wrong Nurse gauge deltas");
    assert(target.state === "down" && target.reactionKind === "launch", "healing omitted forced reaction");
    assert(target.freezeFrames === record.hitStrength && owner.freezeFrames === record.hitStrength,
      "healing skipped contact hitstop");
    reset(); target.team = 1;
    assert(connect() === -amount / 4 && target.hp === 100 + amount / 4, "enemy quarter healing");
    reset(); target.team = 1;
    assert(connect({ ...record, hpDamage: 203 }) === -50 && target.hp === 150, "quarter must truncate toward zero");
    reset(); target.hp = 999;
    connect(); assert(Number(target.hp) === 1000, "healing exceeded max HP");
    reset(); target.hp = 1000;
    connect(); assert(target.hp === 1000 && target.comboWindow === 60, "full HP skipped shared effects");
    reset(); target.hitDrainFrames = 42;
    connect(); assert(Number(target.hitDrainFrames) === 1, "heal must shorten drain to 1, not zero");
    const healed = target.hp; stepHitDrain(target);
    assert(Number(target.hitDrainFrames) === 0 && target.hp === healed - 1, "source final drain tick changed");
    reset(); target.targetEligibility83 = 1; target.hitDrainFrames = 42;
    assert(connect() === 0 && target.hp === 100 && target.hitDrainFrames === 42 && target.comboWindow === 60,
      "non-borg healing target must skip HP/drain branch but retain shared contact");
    reset(); target.invincTimer = 20;
    assert(connect() === 0 && target.hp === 100 && target.comboWindow === 0, "invincible target accepted healing");
    reset(); target.state = "death"; target.alive = false; target.hp = 0;
    assert(connect() === 0 && target.hp === 0 && !target.alive, "healing revived dead target");
    reset(); target.hp = 0;
    connect(); assert(target.hp === 0, "zero HP helper revived target");
    const immune = stats.find(b => (statusImmunityMasksForBorgId(b.id).immunityA & 2) !== 0);
    assert(immune, "no real healing-immune control");
    reset(); target.borgId = immune!.id; target.hitDrainFrames = 42;
    const beforeImmuneHits = telemetry.hitsByTeam[owner.team];
    assert(connect() === 0 && target.hp === 100 && target.hitDrainFrames === 42 &&
      target.comboWindow === 0 && telemetry.hitsByTeam[owner.team] === beforeImmuneHits,
      "healing immunity failed whole-contact gate");
    reset(); target.team = 1;
    const damage = connect({ ...record, flagsA: record.flagsA & ~2 });
    assert(damage > 0 && target.hp < 100, "ordinary damage path changed");
  }
}
