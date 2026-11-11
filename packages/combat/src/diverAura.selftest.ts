import { applyContactAuraStatus, stepAmmoRefill, useWeaponCell } from "./combat.js";
import { diverAmmoBaseRate, refreshDiverAmmoRate, stepDiverXRefill } from "./diverAmmo.js";
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
    const xCell = f.owner.weaponCells![1]!;
    assert(xBefore === 1 && xCell.max === 1 && xCell.refillParam === 1200, `${id} missing source X row`);
    assert(xCell === f.owner.weaponCells![2], `${id} ROM cell 2 and UI X cell must share one charge`);
    f.pressX();
    assert(xCell.cur === xBefore && xCell.timer === 0, `${id} consumed before stream cue`);
    for (let i = 0; i < 100 && !f.state.diverAuras?.length; i++) f.step();
    const child = f.state.diverAuras?.[0];
    assert(child, `${id} actual X did not spawn an aura child`);
    assert(f.state.projectiles.length === 0, `${id} X still emitted an ordinary projectile`);
    assert(Number(f.target.slowAuraLevel) === level, `${id} did not use real kind-9 damage record`);
    assert(f.target.hp === hp && f.target.comboAccum === combo, `${id} contact changed HP/combo`);
    assert(f.target.state !== "hit" && f.target.state !== "down", `${id} contact created a hit reaction`);
    assert(f.target.vel.x === 0 && f.target.vel.z === 0, `${id} contact created knockback`);
    assert(Number(xCell.cur) === 0 && Number(xCell.timer) === 1200, `${id} cue did not consume exactly one charge`);
    const observed = f.battle.observe().actors.find((b) => b.uid === f.owner.uid)!;
    assert(observed.weaponCells![1]!.cur === 0 && observed.weaponCells![2]!.cur === 0, "HUD snapshot disagrees with source cell");
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
    const beforeDenied = f.state.diverAuras![0]!.remainingFrames;
    f.pressX();
    for (let attempt = 0; attempt < 4; attempt++) {
      f.pressX();
      for (let i = 0; i < 19; i++) f.step();
    }
    assert(f.state.diverAuras![0]!.remainingFrames < beforeDenied && f.state.projectiles.length === 0, "empty X refreshed or emitted generic fallback");
    // The source child lasts 1140 frames, less than baseline refill debt1200.
    // Verified haste allows a genuine overlap/refresh without granting free ammo.
    f.owner.hasteHitLevel = 1; f.owner.hasteHitTimer = 2000;
    for (let i = 0; i < 1200 && xCell.cur < 1; i++) f.step();
    assert(xCell.cur === 1 && f.state.diverAuras!.length === 1, "haste failed to refill before child expiry");
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
    f.pressX();
    for (let i = 0; i < 100 && !f.state.diverAuras?.length; i++) f.step();
    const cell = f.owner.weaponCells![1]!;
    for (let i = 0; i < 1199; i++) f.step();
    assert(cell.cur === 0 && cell.timer === 1, "baseline source refill crossed boundary early/double-ticked alias");
    assert(f.state.diverAuras!.length === 0, "baseline child should expire before charge returns");
    f.inputs.p1.special = true;
    f.step(); // refill precedes input gate, so this exact-boundary press must start X
    f.inputs.p1.special = false;
    assert(Number(cell.cur) === 1 && Number(cell.timer) === 0, "exact-boundary X consumed before cue or failed refill");
    for (let i = 0; i < 100 && !f.state.diverAuras?.length; i++) f.step();
    assert(Number(f.state.diverAuras!.length) === 1 && Number(cell.cur) === 0, "boundary input did not deploy after cue");
  }
  {
    const f = fixture("pl080d");
    f.pressX();
    // Deny the allocation AFTER initiation. This legitimate no-payload completion
    // must not permanently latch the bridge's generic projectile fallback.
    const cell = f.owner.weaponCells![1]!;
    cell.cur = 0; cell.timer = 1200;
    for (let i = 0; i < 120; i++) f.step();
    assert(!f.state.diverAuras?.length && !f.state.projectiles.length, "denied cue spawned a payload");
    cell.cur = 1; cell.timer = 0;
    f.pressX();
    for (let i = 0; i < 100 && !f.state.diverAuras?.length; i++) f.step();
    assert(f.state.diverAuras?.length === 1 && !f.state.projectiles.length, "denied cue latched generic X fallback");
  }
  {
    const f = fixture("pl080d");
    const cell = f.owner.weaponCells![1]!;
    cell.cur = 0; cell.timer = 20;
    f.owner.sourceAmmoRefillRate = 1.25;
    f.owner.hasteHitLevel = 1; f.owner.hasteHitTimer = 1;
    f.step();
    assert(cell.timer === 18.75 && f.owner.sourceAmmoRefillRate === 1,
      "refill did not consume cached pre-expiry rate before rebuilding");
    f.step();
    assert(Number(cell.timer) === 17.75, "expired haste rate carried beyond one cached frame");
    f.owner.hasteAuraLevel = 1;
    f.step();
    assert(Number(cell.timer) === 16.75 && Number(f.owner.sourceAmmoRefillRate) === 1.25,
      "contact snapshot changed refill before source rate rebuild");
    f.step();
    assert(Number(cell.timer) === 15.5 && Number(f.owner.sourceAmmoRefillRate) === 1,
      "contact rate was not retained for exactly its cached frame");
  }
  {
    const f = fixture("pl080d");
    const cell = f.owner.weaponCells![1]!;
    const profile = buildProfile(stats.find((s) => s.id === "pl080d")!);
    assert(useWeaponCell(f.owner, profile, 2, 1, true), "source cell2 allocation failed");
    f.owner.weaponCells = f.owner.weaponCells!.map((c) => ({ ...c }));
    const restored = f.owner.weaponCells[1]!;
    stepAmmoRefill(f.owner, profile);
    assert(restored === f.owner.weaponCells[2] && restored.cur === 0 && restored.timer === 1199,
      "copied cells were not rebound without resetting charge/timer");
    f.owner.weaponCells = [f.owner.weaponCells[0]!, cell, cell];
    f.owner.freezeFrames = 90;
    stepAmmoRefill(f.owner, profile);
    assert(cell.timer === 1199 && cell.cur === 0, "freeze incorrectly slowed ammo or granted fractions");
    f.owner.sourceAmmoRefillPauseMask = 4;
    stepAmmoRefill(f.owner, profile);
    assert(cell.timer === 1199, "source slot2 pause bit ignored");
    f.owner.sourceAmmoRefillPauseMask = 2;
    stepAmmoRefill(f.owner, profile);
    assert(Number(cell.timer) === 1198, "browser slot1 bit incorrectly paused source slot2");
    f.owner.sourceAmmoRefillPauseMask = 0;
    f.owner.hasteHitLevel = 1;
    assert(diverAmmoBaseRate(f.owner) === 1.25, "haste rate missing");
    refreshDiverAmmoRate(f.owner);
    cell.timer = 1.25;
    stepDiverXRefill(cell, f.owner);
    assert(Number(cell.timer) === 0 && Number(cell.cur) === 1, "haste exact boundary wrong");
    f.owner.hasteHitLevel = 0; f.owner.slowHitLevel = 1;
    assert(Math.abs(diverAmmoBaseRate(f.owner) - 0.7) < 0.00001, "slow rate missing");
    f.owner.sourceAmmoSlowImmune = true;
    assert(diverAmmoBaseRate(f.owner) === 1, "source slow-suppression bit ignored");
    f.owner.sourceAmmoSlowImmune = false; f.owner.fusionState = 1;
    assert(diverAmmoBaseRate(f.owner) === 1, "fusion state baseline reset missing");
    f.owner.fusionState = 0; f.owner.sourceFusionCarried = true;
    assert(diverAmmoBaseRate(f.owner) === 1, "coarse carried flag invented role2 inheritance");
    f.owner.sourceFusionRole = 2;
    f.owner.fusionPartnerUid = f.target.uid; f.target.sourceAmmoRefillRate = 1.5;
    assert(diverAmmoBaseRate(f.owner, { all: f.state.borgs, auras: new Map() }) === 1.5, "carried partner rate not inherited");
    const other = fixture("pl0500");
    const otherCell = other.owner.weaponCells![1]!;
    assert(otherCell !== other.owner.weaponCells![2], "global slot remap changed other family");
    const otherProfile = buildProfile(stats.find((s) => s.id === "pl0500")!);
    useWeaponCell(other.owner, otherProfile, 1, 1, true);
    stepAmmoRefill(other.owner, otherProfile);
    assert(otherCell.cur > 0 && otherCell.cur < 1, "non-Diver gradual refill policy changed");
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
  console.log("[diverAura.selftest] PASS: source X charge/cue/refill boundaries, no fallback on denial, HUD, rate frame order, aura lifecycle and non-Diver control");
}
