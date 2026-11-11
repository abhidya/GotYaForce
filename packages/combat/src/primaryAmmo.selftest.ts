import { createBattle, battleStateForSelfcheck } from "./battle.js";
import { emptyInput } from "./types.js";
import { stepAmmoRefill, useWeaponCell } from "./combat.js";
import { diverAmmoBaseRate } from "./diverAmmo.js";
import { buildProfile, type BorgStats } from "./stats.js";
import borgsData from "../../assets/data/borgs.json" with { type: "json" };
const stats = (borgsData as { borgs: BorgStats[] }).borgs;
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[primaryAmmo.selftest] ${message}`);
}
function fixture(id: string) {
  const battle = createBattle({ stageId: "st00", bounds: { x: 10000, z: 10000 }, forces: [
    { team: 0, ownerPlayer: "p1", borgIds: [id] },
    { team: 1, ownerPlayer: "p2", borgIds: ["pl0615"] },
  ] }, stats);
  const inputs = { p1: emptyInput(), p2: emptyInput() };
  const step = () => battle.step(1 / 60, inputs);
  for (let i = 0; i < 100; i++) step();
  const state = battleStateForSelfcheck(battle);
  const owner = state.borgs.find((b) => b.team === 0)!;
  const target = state.borgs.find((b) => b.team === 1)!;
  owner.pos = { x: 0, y: 0, z: 0 };
  target.pos = { x: 2000, y: 0, z: 0 };
  target.invincTimer = 100000;
  const cell = owner.weaponCells![0]!;
  const profile = buildProfile(stats.find((b) => b.id === id)!);
  function shoot() {
    const before = cell.cur;
    for (let i = 0; i < 300; i++) {
      inputs.p1.attack = i % 2 === 0;
      step();
      if (cell.cur < before) { inputs.p1.attack = false; return i + 1; }
    }
    throw new Error(`actual B input did not consume ${id}`);
  }
  return { battle, inputs, state, owner, cell, profile, step, shoot };
}
export function runPrimaryAmmoSelfTest(): void {
  {
    const f = fixture("pl0615");
    assert(f.cell.timer === 0, "full type0 magazine must start with zero timer");
    f.shoot();
    assert(f.cell.cur === 4 && f.cell.timer === 0, "partial magazine armed reload");
    for (let i = 0; i < 200; i++) f.step();
    assert(f.cell.cur === 4 && f.cell.timer === 0, "partial magazine spontaneously refilled");
    for (let i = 0; i < 4; i++) f.shoot();
    assert(Number(f.cell.cur) === 0 && Number(f.cell.timer) === 180, "empty type0 did not arm exact row timer");
    for (let i = 0; i < 179; i++) { f.inputs.p1.attack = i % 2 === 0; f.step(); }
    assert(Number(f.cell.cur) === 0 && Number(f.cell.timer) === 1, "empty B fired/refilled early");
    f.inputs.p1.attack = false; f.step();
    assert(Number(f.cell.cur) === 5 && Number(f.cell.timer) === 0, "type0 180th frame failed");
    f.shoot();
    assert(Number(f.cell.cur) === 4 && Number(f.cell.timer) === 0, "second cycle inherited timer");
  }
  for (const [id, param] of [["pl0104", 60], ["pl0500", 300]] as const) {
    const f = fixture(id);
    f.shoot();
    const remaining = f.cell.max - 1;
    assert(f.cell.cur === remaining && f.cell.timer === param, `${id} did not add exact debt`);
    for (let i = 0; i < param - 1; i++) {
      f.step();
      assert(f.cell.cur === remaining && Number.isInteger(f.cell.cur), `${id} fractional/early grant`);
    }
    assert(Number(f.cell.timer) === 1, `${id} debt boundary drift`);
    f.step();
    assert(f.cell.cur === f.cell.max && Number(f.cell.timer) === 0, `${id} exact refill boundary failed`);
    const hud = f.battle.observe().actors.find((b) => b.uid === f.owner.uid)!;
    assert(hud.weaponCells![0]!.cur === f.cell.max, "HUD primary disagrees");
  }
  {
    const f = fixture("pl0104"); f.shoot();
    for (let i = 0; i < 10; i++) f.step();
    const elapsed = f.shoot();
    assert(f.cell.cur === 3 && f.cell.timer === 110 - elapsed && f.cell.timer > 60,
      "repeated real B reset/omitted existing timer debt");
  }
  {
    const f = fixture("pl0104"); f.shoot();
    for (let i = 0; i < 20; i++) f.step();
    assert(useWeaponCell(f.owner, f.profile, 0, 1, false), "query failed");
    assert(f.cell.timer === 40, "query changed debt");
    assert(useWeaponCell(f.owner, f.profile, 0, 1, true), "second consume failed");
    assert(Number(f.cell.timer) === 100 && f.cell.cur === 3, "repeated consume reset rather than added debt");
    f.owner.sourceAmmoRefillPauseMask = 1;
    for (let i = 0; i < 5; i++) f.step();
    assert(Number(f.cell.timer) === 100, "source pause bit0 ignored");
    f.owner.sourceAmmoRefillPauseMask = 4; f.step();
    assert(Number(f.cell.timer) === 99, "unrelated pause bit2 blocked primary");
    f.owner.sourceAmmoRefillRate = 2; f.owner.freezeFrames = 5;
    f.step(); assert(Number(f.cell.timer) === 97, "cached rate or freeze exclusion failed");
    f.step(); assert(Number(f.cell.timer) === 96, "following frame did not rebuild baseline rate");
    f.owner.sourceAmmoRefillRate = 2; f.cell.timer = 1;
    stepAmmoRefill(f.owner, f.profile);
    assert(Number(f.cell.timer) === -1 && Number(f.cell.cur) === 5, "type1 overshoot lost");
    useWeaponCell(f.owner, f.profile, 0, 1, true);
    assert(Number(f.cell.timer) === 59, "next consume discarded source overshoot");
    f.owner.burstActive = true; f.owner.burstPaired = false;
    assert(diverAmmoBaseRate(f.owner) === 1, "burstActive incorrectly treated as source +6fc");
    f.owner.burstActive = false; f.owner.burstPaired = true;
    f.owner.slowHitLevel = 1;
    assert(diverAmmoBaseRate(f.owner) === 1.5, "paired-only actor lost source base boost/slow exclusion");
    // Cached f32 slow0.4 on paired entry: round product to4 before subtraction,
    // otherwise a JS double product leaves a tiny negative debt and alters next use.
    f.owner.sourceAmmoRefillRate = Math.fround(0.4); f.cell.timer = 4;
    stepAmmoRefill(f.owner, f.profile);
    assert(Number(f.cell.timer) === 0, "paired product was not rounded before subtraction");
    useWeaponCell(f.owner, f.profile, 0, 1, true);
    assert(Number(f.cell.timer) === 60, "paired product error contaminated next consume");
  }
  console.log("[primaryAmmo.selftest] PASS: real B type0/type1 boundaries, repeated debt, pause, cached rate, freeze and paired burst");
}
