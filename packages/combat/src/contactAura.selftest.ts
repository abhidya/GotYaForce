import { battleStateForSelfcheck, createBattle } from "./battle.js";
import { applyHit, stepHitStatus } from "./combat.js";
import { damageRecordByIndex, type DamageRecord } from "./gauges.js";
import { buildProfile, type BorgStats } from "./stats.js";
import { actorVelocityScale } from "./timescale.js";
import { emptyInput, type Projectile } from "./types.js";
import borgsData from "../../assets/data/borgs.json" with { type: "json" };

function assert(condition: unknown, message: string): asserts condition {
  if (!condition) throw new Error(`[contactAura.selftest] ${message}`);
}
function close(actual: number, expected: number, message: string): void {
  assert(Math.abs(actual - expected) < 1e-6, `${message}: got ${actual}, expected ${expected}`);
}
const stats = (borgsData as { borgs: BorgStats[] }).borgs;

function record(flagsB: number, magnitude = 3): DamageRecord {
  // Synthetic contact records isolate the decoded aura flags from unrelated HP/reaction
  // behavior. These go through the actual projectile collision + applyHit writer, not a
  // direct slowAuraLevel/hasteAuraLevel assignment or an asserted timescale-only stub.
  return { ...damageRecordByIndex(0), hpDamage: 0, downGaugeDamage: 0,
    balanceGaugeDamage: 0, comboScoreValue: magnitude, hitStrength: 0,
    reactionFlags: 0, flagsA: 0, flagsB };
}
function fixture(reverse = false) {
  const battle = createBattle({ stageId: "st00", bounds: { x: 10000, z: 10000 }, forces: [
    { team: 0, ownerPlayer: "p1", borgIds: ["pl0615"] },
    { team: 1, ownerPlayer: "p2", borgIds: ["pl0008"] },
  ] }, stats);
  const inputs = { p1: emptyInput(), p2: emptyInput() };
  for (let i = 0; i < 100; i++) battle.step(1 / 60, inputs);
  const state = battleStateForSelfcheck(battle);
  const victim = state.borgs.find((b) => b.team === 0)!;
  const attacker = state.borgs.find((b) => b.team === 1)!;
  if (reverse) state.borgs.reverse();
  inputs.p1.moveZ = 1;
  let serial = 0;
  function contact(flagsB: number, magnitude = 3): Projectile {
    const projectile: Projectile = {
      uid: `aura-test-${serial++}`, ownerUid: attacker.uid, team: attacker.team,
      pos: { x: 0, y: 10, z: 0 }, vel: { x: 0, y: 0, z: 0 },
      damage: 0, hitstun: 0, knockback: 0, damageRecord: record(flagsB, magnitude),
      homingTurn: 0, homingTarget: null, life: 2, hitRadius: 100,
      visualKind: "energy",
    };
    state.projectiles.push(projectile);
    return projectile;
  }
  function step(initialSpeed = 2.4): number {
    // Fixed input geometry and initial velocity isolate the per-frame multiplier from
    // acceleration history and applyHit's unrelated velocity write. Measure real movement.
    victim.pos = { x: 0, y: 10, z: 0 };
    victim.vel = { x: 0, y: 0, z: initialSpeed };
    attacker.pos = { x: 0, y: 10, z: 1000 };
    attacker.vel = { x: 0, y: 0, z: 0 };
    victim.invincTimer = 0;
    battle.step(1 / 60, inputs);
    return victim.pos.z;
  }
  return { battle, state, victim, attacker, contact, step };
}

function testProjectileLifetime(reverse: boolean): void {
  const f = fixture(reverse);
  const baseline = f.step();
  const hit = f.contact(0x400);
  close(f.step(), baseline, "contact does not change movement before it occurs");
  assert(hit.hitConfirmedThisFrame, "slow aura did not contact through the projectile resolver");
  assert(f.victim.slowAuraLevel === 3, "contact did not write slow level 3");
  close(f.step(), 2.4, "prior contact slows the next movement frame to level-3 target");
  close(f.step(), baseline, "no new contact restores movement after the carried frame");

  // Both contact orderings must max-merge, not replace the stronger slow with the last hit.
  for (const levels of [[3, 1], [1, 3]]) {
    const hits = levels.map((level) => f.contact(0x400, level));
    f.step();
    assert(hits.every((p) => p.hitConfirmedThisFrame), "overlapping aura contact missing");
    close(f.step(), 2.4, "strongest overlapping slow wins");
    close(f.step(), baseline, "overlap expires after one carried frame");
  }
  for (let frame = 0; frame < 5; frame++) {
    const repeated = f.contact(0x400);
    close(f.step(), frame === 0 ? baseline : 2.4, "continuous contact preserves carried slow");
    assert(repeated.hitConfirmedThisFrame, "repeated aura contact missing");
  }
  close(f.step(), 2.4, "final continuous contact contributes one last movement frame");
  close(f.step(), baseline, "continuous contact ends after the final carried frame");

  const fastBaseline = f.step(12);
  const haste = f.contact(0x800);
  close(f.step(12), fastBaseline, "haste does not apply early");
  assert(haste.hitConfirmedThisFrame, "haste aura contact missing");
  const fast = f.step(12);
  assert(fast > fastBaseline, "prior haste contact did not increase actual movement");
  close(fast, 14.6, "fixed level-1 haste approaches the 1.25x speed target");
  close(f.step(12), fastBaseline, "haste expires after its carried frame");
}

function testInterleavedContact(reverse: boolean): void {
  const f = fixture(reverse);
  const baseline = f.step();
  const victimProfile = buildProfile(stats.find((b) => b.id === f.victim.borgId)!);
  const attackerProfile = buildProfile(stats.find((b) => b.id === f.attacker.borgId)!);
  assert(f.attacker.romDriver, "missing actor-phase driver fixture");
  let fire = true;
  // A real applyHit writer during an actor callback stresses Battle's interleaved actor
  // phase. A projectile-only test would miss clearing a later actor's new contact early.
  f.attacker.romDriver.tick = () => {
    if (fire) {
      fire = false;
      applyHit(f.victim, victimProfile, 0, 0, { x: 0, y: 0, z: 0 }, f.attacker.pos,
        false, record(0x400), { attacker: f.attacker, attackerProfile });
      // The status phase is under test, not applyHit's knockback write. Restore the same
      // initial velocity in the before-movement ordering so both rosters measure alike.
      f.victim.vel = { x: 0, y: 0, z: 2.4 };
    }
    return false;
  };
  close(f.step(), baseline, "actor-phase contact cannot affect same-frame movement");
  close(f.step(), 2.4, "actor-phase contact survives either roster ordering");
  close(f.step(), baseline, "actor-phase contact expires without a new writer");
}

function testPrecedenceAndStandaloneDecay(): void {
  const { victim } = fixture();
  const aura = { slowAuraLevel: 3, hasteAuraLevel: 0 };
  victim.burstActive = true;
  close(actorVelocityScale(victim, aura), 1, "burst still bypasses the slow multiplier");
  victim.freezeFrames = 3;
  close(actorVelocityScale(victim, aura), 0.03, "freeze still overrides burst/aura speed terms");
  victim.slowAuraLevel = 3;
  victim.hasteAuraLevel = 1;
  stepHitStatus(victim);
  assert(victim.slowAuraLevel === 0 && victim.hasteAuraLevel === 0,
    "standalone stepHitStatus must retain its clear default");
}

export function runContactAuraSelfTest(): void {
  for (const reverse of [false, true]) {
    testProjectileLifetime(reverse);
    testInterleavedContact(reverse);
  }
  testPrecedenceAndStandaloneDecay();
  console.log("[contactAura.selftest] PASS: real contact onset/expiry, overlap, haste, actor order, and precedence");
}
