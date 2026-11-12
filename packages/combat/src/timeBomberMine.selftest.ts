import { createTimeBomberMine, stepTimeBomberMine, type TimeBomberMineContext,
  type TimeBomberMineState, type TimeBomberMineReason } from './timeBomberMine.js';

const assert = (condition: unknown, message: string): void => {
  if (!condition) throw new Error(`[timeBomberMine] ${message}`);
};
const equal = (actual: number, expected: number, message: string): void =>
  assert(Object.is(actual, expected), `${message}: ${actual} !== ${expected}`);
const pos = { x: 10, y: 300, z: 20 };
const direction = { x: 0, y: 0, z: 1 };
function fixture(bytes: number[] = [0, 0]) {
  let draws = 0;
  const ctx: TimeBomberMineContext = {
    rngByte: () => { assert(draws < bytes.length, 'no unexpected RNG draw'); return bytes[draws++]!; },
    // Deliberately simple injected sine: verifies lifecycle without claiming ROM sine parity.
    sinBam: () => .5,
    terrainHeight: () => 0,
  };
  return { ctx, draws: () => draws };
}
function active(ctx: TimeBomberMineContext): TimeBomberMineState {
  return stepTimeBomberMine(createTimeBomberMine(pos, direction), ctx).state;
}

export function runTimeBomberMineSelfTest(): void {
  for (const [byte, life] of [[0, 180], [63, 243], [255, 243], [64, 180]] as const) {
    const f = fixture([byte]);
    const pending = createTimeBomberMine(pos, direction);
    assert(f.draws() === 0 && pending.phase === 'pending', 'constructor does not draw RNG');
    const init = stepTimeBomberMine(pending, f.ctx);
    equal(init.state.life, life, 'masked lifetime endpoint');
    equal(init.state.pos.z, pos.z, 'initializer does not move');
    equal(init.state.speed, 5, 'initializer does not decelerate');
    assert(init.events.length === 0 && f.draws() === 1 && pending.phase === 'pending', 'pure initializer');
  }
  {
    const f = fixture([0, 15]);
    let mine = active(f.ctx);
    let updates = 0;
    let previous = mine;
    while (mine.motion === 'drift') {
      previous = mine;
      mine = stepTimeBomberMine(mine, f.ctx).state;
      updates++;
      assert(updates <= 51, 'deceleration crosses zero');
      if (mine.motion === 'drift') equal(mine.pos.z, Math.fround(previous.pos.z + mine.speed), 'moves at reduced speed');
    }
    equal(updates, 51, 'f32 crossing occurs on update51');
    equal(mine.speed, 0, 'negative speed clamps');
    equal(mine.pos.z, previous.pos.z, 'stop transition does not move');
    equal(mine.pos.y, previous.pos.y, 'stop transition does not bob');
    equal(mine.bobPhase, -4096, 'random phase converts signed16');
    equal(mine.center.y, 280, 'center compensates injected sine');
    equal(mine.floorTarget, 150, 'floor offset');
    equal(f.draws(), 2, 'exactly initializer and stop RNG draws');
    const bob = stepTimeBomberMine(mine, f.ctx).state;
    equal(bob.bobPhase, -4096 + 0x180, 'first bob increments phase');
    equal(bob.pos.y, 300, 'bob uses old center');
    equal(bob.center.y, 279.875, 'center descends after position');
    equal(f.draws(), 2, 'bob has no RNG');
    const wrapped = stepTimeBomberMine({ ...bob, bobPhase: 0x7f80 }, f.ctx).state;
    equal(wrapped.bobPhase, -32512, 'bob signed phase wrap');
    const crossing = stepTimeBomberMine({ ...bob, center: { ...bob.center, y: 150.0625 } }, f.ctx).state;
    equal(crossing.center.y, 149.9375, 'center descent is not clamped');
    equal(stepTimeBomberMine(crossing, f.ctx).state.center.y, 149.9375, 'no descent below target');
    assert(mine.center.y === 280 && mine.bobPhase === -4096, 'steps do not mutate inputs');
  }
  for (const byte of [0, 63]) {
    const f = fixture([byte, 0]);
    let mine = active(f.ctx);
    const initialLife = mine.life;
    for (let update = 1; update < initialLife; update++) {
      mine = stepTimeBomberMine(mine, f.ctx).state;
      assert(mine.phase === 'active', 'both lifetime endpoints survive until final decrement');
    }
    const lastPos = { ...mine.pos };
    const expired = stepTimeBomberMine(mine, f.ctx);
    assert(expired.state.life === 0 && expired.state.reason === 'lifetime', 'both endpoints expire on exact update');
    equal(expired.state.pos.y, lastPos.y, 'final lifetime update does not bob');
    equal(f.draws(), 2, 'full lifetime uses exactly two random draws');
  }
  {
    const f = fixture();
    let poseReads = 0;
    const pending = createTimeBomberMine(pos, direction);
    const initialized = stepTimeBomberMine(pending, { ...f.ctx, initPose: () => {
      poseReads++; return { pos: { x: 100, y: 200, z: 300 }, direction: { x: 1, y: 0, z: 0 } };
    } });
    assert(poseReads === 1 && initialized.state.pos.x === 100 && initialized.state.direction.x === 1,
      'deferred initializer resolves current attachment without flight');
    assert(pending.pos.x === 10, 'init pose leaves allocator input intact');
    const bob = { ...initialized.state, motion: 'bob' as const, center: { x: 1, y: 150.12345, z: 2 } };
    const sine = .123456789;
    const next = stepTimeBomberMine(bob, { ...f.ctx, sinBam: () => sine });
    equal(next.state.pos.y, Math.fround(40 * sine + bob.center.y), 'bob casts once after double product and sum');
  }
  const cases: Array<{ reason: TimeBomberMineReason; explode: boolean; state?: Partial<TimeBomberMineState>; context?: Partial<TimeBomberMineContext> }> = [
    { reason: 'contact', explode: true, context: { contact: true } },
    { reason: 'bounds', explode: false, context: { outsideBounds: () => true } },
    { reason: 'durability', explode: true, state: { durability: 0 } },
    { reason: 'lifetime', explode: true, state: { life: 1 } },
    { reason: 'collision', explode: false, context: { collision83714: () => true } },
    { reason: 'wall', explode: true, context: { wall84170: () => true } },
  ];
  for (const test of cases) {
    const f = fixture();
    const mine = { ...active(f.ctx), ...test.state };
    const retired = stepTimeBomberMine(mine, { ...f.ctx, ...test.context });
    assert(retired.state.phase === 'retiring' && retired.state.reason === test.reason, `${test.reason} retires`);
    assert(retired.events.length === Number(test.explode) &&
      (!test.explode || retired.events[0]?.kind === 'explosion'), `${test.reason} explosion policy and no early refund`);
    const released = stepTimeBomberMine(retired.state, f.ctx);
    assert(released.state.phase === 'released' && !released.state.resourceOwed && released.events[0]?.kind === 'refund', `${test.reason} next-update refund`);
    const freed = stepTimeBomberMine(released.state, f.ctx);
    assert(freed.state.phase === 'freed' && freed.events[0]?.kind === 'free', `${test.reason} following-update free`);
    assert(stepTimeBomberMine(freed.state, f.ctx).events.length === 0, 'freed remains inert');
    equal(f.draws(), 1, 'retirement adds no random draws');
    if (['contact', 'bounds', 'durability', 'lifetime'].includes(test.reason)) equal(retired.state.pos.z, pos.z, 'early retirement does not move');
    if (test.reason === 'lifetime') equal(retired.state.life, 0, 'life1 expires before movement');
  }
  for (const ownerInvalid of ['owner-dead', 'owner-changed'] as const) {
    for (const initialized of [false, true]) {
      const f = fixture();
      const mine = initialized ? active(f.ctx) : createTimeBomberMine(pos, direction);
      const result = stepTimeBomberMine(mine, { ...f.ctx, ownerInvalid, contact: true });
      assert(result.state.phase === 'released' && result.events.length === 1 && result.events[0]?.kind === 'refund', 'owner invalidation refunds immediately without explosion');
      equal(f.draws(), Number(initialized), 'owner invalidation prevents initialization draw');
      assert(stepTimeBomberMine(result.state, { ...f.ctx, ownerInvalid }).events[0]?.kind === 'free', 'owner invalidation does not repeat refund');
    }
  }
  {
    const f = fixture();
    const mine = active(f.ctx);
    assert(stepTimeBomberMine(mine, { ...f.ctx, contact: true, outsideBounds: () => true }).state.reason === 'contact', 'contact precedes bounds');
    assert(stepTimeBomberMine({ ...mine, durability: 0 }, { ...f.ctx, outsideBounds: () => true }).state.reason === 'bounds', 'bounds precedes durability');
    assert(stepTimeBomberMine({ ...mine, life: 1, durability: 0 }, f.ctx).state.reason === 'durability', 'durability precedes lifetime');
    const order: string[] = [];
    const collision = stepTimeBomberMine(mine, { ...f.ctx,
      afterMotion: state => { assert(state.pos.z > pos.z, 'collision update follows movement'); order.push('update'); },
      collision83714: () => { order.push('collision'); return true; },
      wall84170: () => { order.push('wall'); return true; } });
    assert(collision.state.reason === 'collision' && order.join(',') === 'update,collision', '83714 silent termination precedes wall');
    const noToken = stepTimeBomberMine({ ...mine, resourceOwed: false }, { ...f.ctx, ownerInvalid: 'owner-dead' });
    assert(noToken.events.length === 0 && noToken.state.phase === 'released', 'no invented refund without resource token');
  }
}
