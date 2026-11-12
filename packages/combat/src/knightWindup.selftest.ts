import { RomDriverBridge } from "./bridge.js";
import { createBattle, battleStateForSelfcheck } from "./battle.js";
import { emptyInput } from "./types.js";
import type { BorgStats } from "./stats.js";
import { startStream, tickStream } from "./rom/stream-vm.js";
import { createKnightWindupClock, tickKnightWindupClock } from "./rom/knight-windup-clock.js";
import borgsData from "../../assets/data/borgs.json" with { type: "json" };
const stats = (borgsData as { borgs: BorgStats[] }).borgs;
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[knightWindup.selftest] ${message}`);
}
export function runKnightWindupSelfTest(): void {
  for (const rate of [0.5, 1, 1.5]) {
    const clock = createKnightWindupClock(rate);
    let ticks = 0;
    while (!tickKnightWindupClock(clock, rate)) {
      assert(++ticks < 100, "clock never completed");
    }
    assert(ticks === Math.ceil(35 / rate) - 1, `blend/threshold order at ${rate}`);
  }
  const held = createKnightWindupClock(1);
  for (let i = 0; i < 100; i++) assert(!tickKnightWindupClock(held, 0), "held clock completed");
  assert(held.localFrame === 0 && held.blendElapsed === 1, "held clock moved");
  for (const id of ["pl0208", "pl020e"]) {
    const battle = createBattle({ stageId: "st00", bounds: { x: 10000, z: 10000 }, forces: [
      { team: 0, ownerPlayer: "p1", borgIds: [id] },
      { team: 1, ownerPlayer: "p2", borgIds: ["pl0615"] },
    ] }, stats);
    const inputs = { p1: emptyInput(), p2: emptyInput() };
    for (let i = 0; i < 100; i++) battle.step(1 / 60, inputs);
    const state = battleStateForSelfcheck(battle);
    const owner = state.borgs[0]!;
    const driver = owner.romDriver! as RomDriverBridge;
    const actor = driver.actor;
    const cell = owner.weaponCells![2]!;
    const ownedProjectiles = () => state.projectiles.filter((p) => p.ownerUid === owner.uid).length;
    const initialProjectiles = ownedProjectiles();
    let animations = 0;
    const play = driver.ctx.onPlayAnim!;
    driver.ctx.onPlayAnim = (a, group, slot, blend) => { animations++; play(a, group, slot, blend); };
    let consumes = 0;
    let releases = 0;
    const allocate = driver.ctx.onAllocateResource!;
    driver.ctx.onAllocateResource = (a, type, count, mode) => {
      if (type === 2 && mode) consumes++;
      return allocate(a, type, count, mode);
    };
    const spawn = driver.ctx.onFamilyProjectile!;
    driver.ctx.onFamilyProjectile = (a, addr, kind) => { releases++; spawn(a, addr, kind); };
    // Real bridge entry and family machine, no fabricated completion byte.
    const start = () => {
      owner.command = { actionIndex: 2, variantIndex: 0 } as NonNullable<typeof owner.command>;
      assert(driver.tryStartXSpecial(owner, state.borgs), `${id} X was not owned`);
      assert(actor.fbPhaseSlots[0] === 1, `${id} setup phase missing`);
    };
    const tick = () => driver.tick(owner, 1 / 60, state.borgs);
    start();
    const initial = cell.cur;
    assert(animations === 1, `${id} setup animation not immediate/exactly once`);
    assert(owner.anim === "special" && actor.contactP0 === 0
      && actor.parts[0]!.stateByte === 0 && actor.parts[1]!.stateByte === 0
      && (actor.parts[0] as { c?: number }).c === 0
      && (actor.parts[1] as { c?: number }).c === 1,
      `${id} immediate setup was clobbered by stream reset`);
    for (let i = 1; i <= 34; i++) {
      tick();
      assert(cell.cur === initial && consumes === 0 && releases === 0, `${id} consumed/released early at ${i}`);
      assert(actor.fbPhaseSlots[0] === 1, `${id} released or timed out early at ${i}`);
      assert(ownedProjectiles() === initialProjectiles, `${id} spawned early at ${i}`);
      assert(animations === 1, `${id} repeated setup animation at ${i}`);
    }
    tick();
    assert(consumes === 1 && releases === 1, `${id} did not consume/release exactly once on tick35`);
    assert(cell.cur === (cell.max > 0 ? initial - 1 : initial), `${id} wrong finite/infinite ammo result`);
    assert(ownedProjectiles() === initialProjectiles + 1, `${id} Battle did not receive one projectile`);
    assert(actor.fbPhaseSlots[0] === 2, `${id} did not release on tick35`);
    for (let i = 0; i < 4; i++) tick();
    assert(consumes === 1 && releases === 1, `${id} consumed/released twice`);
    driver.interrupt();
    // New action must not inherit local30, and cancellation must drop completion.
    start();
    for (let i = 0; i < 8; i++) tick();
    assert(consumes === 1 && releases === 1, `${id} repeat inherited local clock`);
    driver.interrupt();
    for (let i = 0; i < 40; i++) tick();
    assert(consumes === 1 && releases === 1, `${id} cancelled wait released`);
    start();
    // A non-overlapping replacement must not revoke part0's pending wait.
    startStream(actor, 2, 4, 1);
    for (let i = 0; i < 34; i++) tickStream(actor, 1);
    assert(actor.wallContact === 0, `${id} mask replacement completed part0 early`);
    tickStream(actor, 1);
    tickStream(actor, 12); // remaining owned parts complete independently of replaced part1
    for (let i = 0; i < 34; i++) tickStream(actor, 12);
    assert(!(driver as unknown as { hasPendingKnightWindup(): boolean }).hasPendingKnightWindup(),
      `${id} revoked part retained pending wait/watchdog exemption`);
    assert(Number(actor.wallContact) === 1, `${id} part0 wait lost to nonoverlapping replacement`);
    driver.interrupt();
    start();
    // Overlapping replacement in the SAME bridge frame revokes old clock ownership.
    startStream(actor, 1, 4, 1);
    for (let i = 0; i < 40; i++) tickStream(actor, 1);
    assert(actor.wallContact === 0, `${id} replaced wait completed newer stream`);
    driver.interrupt();
    start();
    // Same terminal flags/value in g4s0 are deliberately outside this repair.
    startStream(actor, 15, 4, 0);
    tick(); tick();
    assert(actor.wallContact !== 0, `${id} unrelated g4s0 adopted Knight local-clock timing`);
    driver.interrupt();
  }
  console.log("[knightWindup.selftest] PASS: Knight real-bridge windup, blend, threshold, repeat, cancel and masks");
}
