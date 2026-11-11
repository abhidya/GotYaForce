import { battleStateForSelfcheck, createBattle } from "./battle.js";
import { emptyInput } from "./types.js";
import { applyHit, stepHitDrain } from "./combat.js";
import { familyDamageRecordForBorg } from "./familyDamageData.js";
import { statusImmunityMasksForBorgId } from "./movementData.js";
import { buildProfile, type BorgStats } from "./stats.js";
import borgsData from "../../assets/data/borgs.json" with { type: "json" };
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[hitDrain] ${message}`);
}
const stats = (borgsData as { borgs: BorgStats[] }).borgs;
export function runHitDrainSelfTest(): void {
  for (const [id, reversed] of [["pl050b", false], ["pl0517", false], ["pl050b", true]] as const) {
    const battle = createBattle({
      stageId: "st00",
      bounds: { x: 10000, z: 10000 },
      forces: [
        { team: 0, ownerPlayer: "p1", borgIds: [id] },
        { team: 1, ownerPlayer: "p2", borgIds: ["pl0615"] },
      ],
    }, stats);
    const inputs = { p1: emptyInput(), p2: emptyInput() };
    const step = () => battle.step(1 / 60, inputs);
    for (let i = 0; i < 100; i++)
      step();
    const state = battleStateForSelfcheck(battle);
    if (reversed) state.borgs.reverse();
    const owner = state.borgs.find(b => b.team === 0)!;
    const target = state.borgs.find(b => b.team === 1)!;
    owner.pos = { x: 0, y: 0, z: 0 };
    target.pos = { x: 25, y: 0, z: 0 };
    target.invincTimer = 0;
    inputs.p1.attack = true;
    for (let i = 0; i < 180 && !target.hitDrainFrames; i++)
      step();
    inputs.p1.attack = false;
    assert(target.hitDrainFrames === 600, `${id} actual B never seeded drain: ${target.hitDrainFrames}, hp=${target.hp}`);
    owner.pos = { x: -5000, y: 0, z: 0 };
    target.pos = { x: 5000, y: 0, z: 0 };
    const hp = target.hp;
    for (let i = 0; i < 29; i++)
      step();
    assert(target.hp === hp, `${id} early drain`);
    step();
    assert(target.hp === hp - 1, `${id} frame 30 did not drain HP`);
    for (let i = 0; i < 570; i++)
      step();
    assert(Number(target.hitDrainFrames) === 0 && target.hp === hp - 20, `${id} expiry mismatch timer=${target.hitDrainFrames} hp=${target.hp} initial=${hp}`);
    for (let i = 0; i < 30; i++)
      step();
    assert(target.hp === hp - 20, `${id} drain continued after expiry`);
    // Refresh replaces remaining duration; paired/fused/immune victims reject the writer.
    const profile = buildProfile(stats.find(b => b.id === target.borgId)!);
    const record = familyDamageRecordForBorg(id, 0)!;
    function connect() {
      target.hp = target.maxHp;
      target.state = "idle";
      target.invincTimer = 0;
      applyHit(target, profile, record.hpDamage, 0, { x: 1, y: 0, z: 0 }, owner.pos, false, record, {
        attacker: owner,
        attackerProfile: buildProfile(stats.find(b => b.id === owner.borgId)!),
      });
    }
    target.hitDrainFrames = 42;
    connect();
    assert(Number(target.hitDrainFrames) === 600, "repeat hit did not refresh 600 frames");
    target.hitDrainFrames = 42;
    target.burstPaired = true;
    connect();
    assert(Number(target.hitDrainFrames) === 42, "paired burst did not block drain");
    target.burstPaired = false;
    for (const role of [1, 2]) {
      target.sourceFusionRole = role;
      connect();
      assert(Number(target.hitDrainFrames) === 42, "carried role did not block drain");
    }
    target.sourceFusionRole = 0;
    const originalId = target.borgId;
    const immune = stats.find(b => (statusImmunityMasksForBorgId(b.id).immunityA & 0x100) !== 0);
    assert(immune, "missing real immune control");
    target.borgId = immune.id;
    connect();
    assert(Number(target.hitDrainFrames) === 42, "immune victim accepted drain");
    target.borgId = originalId;
    target.hitDrainFrames = 1;
    target.hp = 2;
    target.state = "hit";
    stepHitDrain(target);
    assert(target.hp === 1 && Number(target.hitDrainFrames) === 0, "final hit-reaction tick/floor wrong");
    target.hitDrainFrames = 1;
    target.state = "down";
    stepHitDrain(target);
    assert(target.hp === 1, "drain self-killed at floor");
    for (const state of ["spawn", "death"] as const) {
      target.state = state;
      target.hitDrainFrames = 30;
      stepHitDrain(target);
      assert(target.hitDrainFrames === 30, "inactive lifecycle ticked");
    }
    target.state = "idle";
    target.alive = false;
    stepHitDrain(target);
    assert(target.hitDrainFrames === 30, "departed actor ticked");
  }
  for (const id of ["pl0702", "pl070a", "pl0615"]) {
    const battle = createBattle({ stageId: "st00", bounds: { x: 10000, z: 10000 }, forces: [
      { team: 0, ownerPlayer: "p1", borgIds: [id] },
      { team: 1, ownerPlayer: "p2", borgIds: ["pl0615"] },
    ] }, stats);
    const inputs = { p1: emptyInput(), p2: emptyInput() };
    for (let frame = 0; frame < 100; frame++) battle.step(1 / 60, inputs);
    const actor = battleStateForSelfcheck(battle).borgs[0]!;
    const hp = actor.hp;
    for (let frame = 0; frame < 600; frame++) battle.step(1 / 60, inputs);
    assert(actor.hp === hp && !actor.hitDrainFrames, `${id} acquired uninflicted drain`);
  }
}
