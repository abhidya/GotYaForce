import { applyContactAuraStatus } from "./combat.js";
import { familyDamageRecordForBorg } from "./familyDamageData.js";
import { statusImmunityMasksForBorgId } from "./movementData.js";
import { battleStateForSelfcheck, createBattle } from "./battle.js";
import { emptyInput } from "./types.js";
import { groundSpeed } from "./movement.js";
import { buildProfile, type BorgStats } from "./stats.js";
import { actorVelocityScale } from "./timescale.js";
import borgsData from "../../assets/data/borgs.json" with { type: "json" };

function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[diverAura.selftest] ${message}`);
}
const stats = (borgsData as { borgs: BorgStats[] }).borgs;
function fixture(id: string) {
  const battle = createBattle({ stageId: "st00", bounds: { x: 10000, z: 10000 }, forces: [
    { team: 0, ownerPlayer: "p1", borgIds: [id] },
    { team: 1, ownerPlayer: "p2", borgIds: ["pl0615"] },
  ] }, stats);
  const inputs = { p1: emptyInput(), p2: emptyInput() };
  for (let i = 0; i < 100; i++) battle.step(1 / 60, inputs);
  const state = battleStateForSelfcheck(battle);
  const owner = state.borgs.find((b) => b.team === 0)!;
  const target = state.borgs.find((b) => b.team === 1)!;
  owner.pos = { x: 0, y: 0, z: 0 };
  target.pos = { x: 100, y: 0, z: 0 };
  target.invincTimer = 0;
  function step() { return battle.step(1 / 60, inputs); }
  function pressX() { inputs.p1.special = true; step(); inputs.p1.special = false; }
  return { battle, inputs, state, owner, target, step, pressX };
}

export function runDiverAuraSelfTest(): void {
  for (const [id, level] of [["pl0805", 1], ["pl080d", 3], ["pl080e", 2]] as const) {
    const f = fixture(id);
    const hp = f.target.hp;
    const combo = f.target.comboAccum;
    const xBefore = f.owner.weaponCells![1]!.cur;
    const finiteX = f.owner.weaponCells![1]!.max > 0;
    f.pressX();
    if (finiteX) assert(f.owner.weaponCells![1]!.cur === xBefore, `${id} ROM X unexpectedly changed existing cell-1 ammo policy`);
    for (let i = 0; i < 100 && !f.state.diverAuras?.length; i++) f.step();
    const child = f.state.diverAuras?.[0];
    assert(child, `${id} actual X did not spawn an aura child`);
    assert(f.state.projectiles.length === 0, `${id} X still emitted an ordinary projectile`);
    assert(Number(f.target.slowAuraLevel) === level, `${id} did not use real kind-9 damage record`);
    assert(f.target.hp === hp && f.target.comboAccum === combo, `${id} contact changed HP/combo`);
    assert(f.target.state !== "hit" && f.target.state !== "down", `${id} contact created a hit reaction`);
    assert(f.target.vel.x === 0 && f.target.vel.z === 0, `${id} contact created knockback`);
    if (finiteX) assert(f.owner.weaponCells![1]!.cur === xBefore, `${id} ROM event charged browser cell 1`);
    assert(f.owner.weaponCells![2]!.max === 0, "did not preserve unresolved cell-2 policy");
    assert(child.bankTexId === 78 && child.hitRadius === 700, "decoded extent / approximate boundary or visual missing");
    const uid = child.uid;
    const immutable = f.battle.observe().diverAuras[0]!;
    f.owner.pos.x = 20;
    f.step();
    assert(f.state.diverAuras![0]!.pos.x === f.owner.pos.x, "child did not follow owner");
    assert(immutable.pos.x !== f.state.diverAuras![0]!.pos.x, "observation aliases mutable child");
    // Leave the approximate volume. Previous contact carries one movement frame;
    // after this contact phase the following frame no longer sees an aura.
    const normalSpeed = groundSpeed(buildProfile(stats.find((s) => s.id === f.target.borgId)!));
    f.owner.pos.x = 0; f.owner.pos.z = 1000;
    f.target.pos.x = 0;
    f.target.pos.z = -3000;
    f.target.vel.z = normalSpeed;
    f.inputs.p2.moveZ = 1;
    assert(actorVelocityScale(f.target) < 1, "last contact not carried before leaving");
    f.step();
    const carriedDistance = f.target.pos.z + 3000;
    assert(Number(f.target.slowAuraLevel) === 0 && actorVelocityScale(f.target) === 1, "aura stuck after leaving");
    f.target.pos.z = -3000;
    f.target.vel.z = normalSpeed;
    f.step();
    assert(f.target.pos.z + 3000 > carriedDistance, `real leaving movement did not recover after one carried frame ${id}: carried=${carriedDistance} clear=${f.target.pos.z} state=${f.target.state}`);
    f.inputs.p2.moveZ = 0; f.target.vel.z = 0;
    f.target.pos.x = 100; f.target.pos.z = 1000;
    for (let i = 0; i < 150; i++) f.step();
    const beforeRefresh = f.state.diverAuras![0]!.remainingFrames;
    f.pressX();
    let refreshed = false;
    for (let i = 0; i < 100; i++) {
      f.step();
      if (f.state.diverAuras![0]!.remainingFrames > beforeRefresh) { refreshed = true; break; }
    }
    assert(refreshed, `${id} second real X failed to refresh (impotence latch?)`);
    assert(Number(f.state.diverAuras!.length) === 1 && f.state.diverAuras![0]!.uid === uid, "refresh duplicated/replaced child");
    f.state.diverAuras![0]!.remainingFrames = 1;
    f.step();
    assert(Number(f.state.diverAuras!.length) === 0 && Number(f.target.slowAuraLevel) === 0, "expiry still applied contact");
  }
  {
    const f = fixture("pl080d");
    // The real 0x480 record does not exclude same-team targets. Use the same live
    // population while retaining both force teams so Battle keeps running.
    f.pressX();
    for (let i = 0; i < 100 && !f.state.diverAuras?.length; i++) f.step();
    assert(f.state.diverAuras?.length === 1, "friendly fixture failed to spawn");
    f.target.team = f.owner.team;
    f.target.slowAuraLevel = 0;
    f.step();
    assert(Number(f.target.slowAuraLevel) === 3, "invented friendly protection blocked the real aura");
    const rec = familyDamageRecordForBorg("pl080d", 11)!;
    f.target.slowAuraLevel = 0; f.target.burstActive = true;
    applyContactAuraStatus(f.target, rec);
    assert(Number(f.target.slowAuraLevel) === 0, "burst victim received slow aura write");
    applyContactAuraStatus(f.target, { ...rec, flagsB: 0x800 });
    assert(Number(f.target.hasteAuraLevel) === 1, "burst incorrectly suppressed haste aura");
    f.target.burstActive = false; f.target.sourceFusionCarried = true;
    applyContactAuraStatus(f.target, rec);
    assert(Number(f.target.slowAuraLevel) === 0, "source +0x4a0 carried victim received aura write");
    f.target.sourceFusionCarried = false;
    const immune = stats.find((s) => (statusImmunityMasksForBorgId(s.id).immunityB & 0x400) !== 0);
    assert(immune, "shared immunity fixture missing");
    f.target.borgId = immune.id;
    applyContactAuraStatus(f.target, rec);
    assert(Number(f.target.slowAuraLevel) === 0, "shared immunity ignored");
    f.target.borgId = "pl0805";
    applyContactAuraStatus(f.target, rec);
    assert(Number(f.target.slowAuraLevel) === 0, "Diver exemption ignored");
  }
  for (const reason of ["death", "form"] as const) {
    const f = fixture("pl080d"); f.pressX();
    for (let i = 0; i < 100 && !f.state.diverAuras?.length; i++) f.step();
    assert(f.state.diverAuras?.length === 1, "cleanup fixture failed to spawn");
    if (reason === "death") f.owner.hp = 0;
    else f.owner.combatFormId = "pl0615";
    f.step();
    assert(Number(f.state.diverAuras!.length) === 0, `${reason} left stale child collision`);
  }
  console.log("[diverAura.selftest] PASS: real X create/refresh, records, overlap, expiry and owner cleanup");
}
