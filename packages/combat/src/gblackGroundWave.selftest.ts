import { G_BLACK_GROUND_WAVE as WAVE, createGBlackGroundWaveParent, stepGBlackGroundWaveParent,
  createGBlackGroundWaveChild, stepGBlackGroundWaveChild, rotateGBlackGroundWaveMotion,
  gblackGroundWaveVisualScale, type GBlackGroundWaveParentState, type GBlackGroundWaveParentContext,
  type GBlackGroundWaveChildContext, type GBlackGroundWaveReason } from './gblackGroundWave.js';

const assert = (condition: unknown, message: string): void => {
  if (!condition) throw new Error(`[gblackGroundWave] ${message}`);
};
const equal = (actual: number, expected: number, message: string): void =>
  assert(Object.is(actual, expected), `${message}: ${actual} !== ${expected}`);
const close = (actual: number, expected: number, message: string, tolerance = 1e-5): void =>
  assert(Math.abs(actual - expected) <= tolerance, `${message}: ${actual} != ${expected}`);
const pos = { x: 10, y: 300, z: 20 };
const facing = { x: 0, y: 0, z: 1 };
const parentContext = (): GBlackGroundWaveParentContext => ({ terrainHeight: () => 0, targetPosition: () => null });
const pending = (modelScale = 1, collisionScale = 1) =>
  createGBlackGroundWaveParent({ pos, facing, modelScale, collisionScale });
const active = (ctx = parentContext()): GBlackGroundWaveParentState => stepGBlackGroundWaveParent(pending(), ctx).state;
const childContext = (): GBlackGroundWaveChildContext => ({ terrainHeight: () => 0, rngByte: () => 0 });
const pendingChild = (modelScale = 1, collisionScale = 1) =>
  createGBlackGroundWaveChild({ pos, modelScale, collisionScale });

export function runGblackGroundWaveSelfTest(): void {
  equal(WAVE.spawner, 0x800fc208, 'source allocator address');
  assert(WAVE.type === 5 && WAVE.hitKind === 84 && WAVE.hitRecord === 122 && WAVE.damageRecord === 9,
    'type5 shared HIT selector and damage mapping');
  {
    const original = pending(2, 3), calls: string[] = [];
    assert(original.phase === 'pending' && original.life === 0, 'allocation does not initialize');
    const init = stepGBlackGroundWaveParent(original, { terrainHeight: (point, probe) => {
      calls.push('terrain'); equal(point.y, 300, 'projection receives captured position');
      equal(probe, 100, 'source terrain probe'); return 25;
    }, targetPosition: () => { calls.push('target'); return null; } });
    assert(calls.join(',') === 'terrain', 'no target read without captured target');
    assert(init.state.phase === 'active' && init.state.life === 600 && init.state.retargetCounter === 4,
      'initializer establishes source counters');
    equal(init.state.pos.z, 20, 'initializer does not move');
    equal(init.state.pos.y, 25, 'initializer projects terrain');
    equal(init.state.motion.z, 50, 'initializer builds stored speed50');
    equal(init.state.speedScalar, 50, 'scalar begins50');
    assert(init.children.length === 1, 'initial pulse allocation requested');
    assert(init.children[0]!.pos !== init.state.pos && init.state.lastEmit !== init.state.pos,
      'emission and spacing retain independent snapshots');
    assert(init.children[0]!.modelScale === 2 && init.children[0]!.collisionScale === 3,
      'visual/model and HIT scales are independently inherited');
    equal(original.pos.y, 300, 'input position is immutable');
    equal(original.life, 0, 'input counters are immutable');
  }
  {
    const ctx = parentContext(); let state = active(ctx);
    for (let update = 1; update <= 20; update++) {
      const result = stepGBlackGroundWaveParent(state, ctx); state = result.state;
      equal(state.pos.z, 20 + 50 * update, 'constant motion despite scalar growth');
      equal(state.speedScalar, 50 + update, 'post-motion scalar increments');
      equal(state.motion.z, 50, 'motion is never rebuilt from scalar');
      equal(result.children.length, update % 4 === 0 ? 1 : 0, 'one pulse at each spacing threshold');
      equal(state.retargetCounter, 4, 'counter does not tick without target');
    }
    const capped = stepGBlackGroundWaveParent({ ...state, speedScalar: 150 }, ctx).state;
    equal(capped.speedScalar, 150, 'scalar clamps maximum');
    equal(capped.pos.z - state.pos.z, 50, 'clamped scalar does not accelerate');
    const lower = stepGBlackGroundWaveParent({ ...state, speedScalar: 2 }, ctx).state;
    equal(lower.speedScalar, 50, 'scalar minimum clamp');
    const fast = stepGBlackGroundWaveParent({ ...active(ctx), motion: { x: 0, y: 0, z: 1000 } }, ctx);
    equal(fast.children.length, 1, 'spacing never catches up with multiple allocations');
    equal(fast.state.lastEmit.z, fast.state.pos.z, 'spacing consumed at current point before caller allocation');
  }
  {
    const ctx = parentContext(); let state = stepGBlackGroundWaveParent(pending(2, 7), ctx).state;
    for (let update = 1; update <= 8; update++) {
      const result = stepGBlackGroundWaveParent(state, ctx); state = result.state;
      equal(result.children.length, update === 8 ? 1 : 0, 'spacing follows modelScale, not collisionScale');
    }
    const atRange = { ...state, pos: { ...state.pos, z: state.origin.z + 9950 } };
    const expired = stepGBlackGroundWaveParent(atRange, ctx);
    assert(expired.state.reason === 'distance' && expired.children.length === 0, 'range endpoint is strict5000*modelScale');
  }
  {
    let target = { x: 10, y: 9000, z: 1020 };
    const ctx: GBlackGroundWaveParentContext = { ...parentContext(), targetPosition: () => target };
    let state = stepGBlackGroundWaveParent(createGBlackGroundWaveParent({ pos, facing, modelScale: 1,
      collisionScale: 1, targetUid: 'captured' }), ctx).state;
    equal(state.motion.y, 0, 'targeting flattens target Y at initialization');
    target = { x: 1010, y: -9000, z: 170 };
    for (let update = 1; update <= 3; update++) {
      state = stepGBlackGroundWaveParent(state, ctx).state;
      equal(state.motion.x, 0, 'target direction unchanged before fourth tick');
      equal(state.retargetCounter, 4 - update, 'target countdown');
    }
    const old = state; state = stepGBlackGroundWaveParent(state, ctx).state;
    equal(state.retargetCounter, 4, 'retarget counter resets');
    close(Math.hypot(state.motion.x, state.motion.z), 50, 'steering preserves stored magnitude');
    close(Math.atan2(state.motion.x, state.motion.z), WAVE.turnLimit, 'one-degree turn limit', 1e-8);
    close(state.pos.z - old.pos.z, state.motion.z, 'steering moves exactly once');
    equal(state.motion.y, 0, 'steering ignores target height');
    assert(state.targetUid === 'captured', 'retains captured target, not a new lock');
    const near = stepGBlackGroundWaveParent({ ...old, retargetCounter: 1 }, {
      ...ctx, targetPosition: () => ({ x: old.pos.x, y: 10000, z: old.pos.z + 100 }),
    }).state;
    assert(near.targetUid === null, 'inclusive100 clears target');
    equal(near.pos.z - old.pos.z, 50, 'target clear falls back to exactly one stored-motion step');
    const lost = stepGBlackGroundWaveParent(old, { ...ctx, targetInvalid: (_uid, moving) => {
      assert(moving.pos.z > old.pos.z, '83874 invalidation follows movement'); return true;
    } }).state;
    assert(lost.targetUid === null, 'source validator drops captured target');
  }
  {
    const ctx: GBlackGroundWaveParentContext = { ...parentContext(), targetPosition: () => ({ ...pos, y: -300 }) };
    const state = stepGBlackGroundWaveParent(createGBlackGroundWaveParent({ pos, facing, modelScale: 1,
      collisionScale: 1, targetUid: 'coincident' }), ctx).state;
    equal(Math.hypot(state.motion.x, state.motion.y, state.motion.z), 0, 'coincident initial target does not fall back to facing');
    const tiny = rotateGBlackGroundWaveMotion({ x: 0, y: 7, z: 0 }, { x: 1000, y: 0, z: 0 }, WAVE.turnLimit, facing);
    close(Math.hypot(tiny.x, tiny.z), WAVE.minimumSteeringMagnitude, 'steering-only tiny motion fallback', 1e-10);
    equal(tiny.y, 7, 'source steering restores original vertical component');
    const opposite = rotateGBlackGroundWaveMotion({ x: 0, y: 0, z: 50 }, { x: 0, y: 0, z: -1000 }, WAVE.turnLimit, facing);
    assert(opposite.x > 0, 'antiparallel steering chooses source world+Y fallback axis');
  }
  {
    const order: string[] = [];
    const original = { ...active(), targetUid: 'target', retargetCounter: 1 };
    const result = stepGBlackGroundWaveParent(original, {
      targetPosition: () => { order.push('target'); return { x: 1000, y: 900, z: 1000 }; },
      rotateMotion: (motion, _delta, limit) => { order.push('turn'); equal(limit, WAVE.turnLimit, 'injected source turnlimit'); return { ...motion }; },
      afterSteering: moved => { order.push('refresh'); equal(moved.pos.z, 70, '833a4 after movement'); },
      terrainHeight: () => { order.push('terrain'); return 100; },
      wallSegment: (from, to) => { order.push('wall'); equal(from.z, 20, 'wall from pre-motion'); equal(to.y, 100, 'wall afterprojection'); return true; },
      targetInvalid: (_uid, moved) => { order.push('validate'); equal(moved.speedScalar, 51, 'scalar before targetvalidation'); return true; },
      outsideBounds: () => { order.push('bounds'); return true; },
      attraction83714: moved => { order.push('attraction'); equal(moved.life, 600, 'life decremented after attraction'); return true; },
    });
    assert(order.join(',') === 'target,turn,refresh,terrain,wall,validate,bounds,attraction', 'all probes execute in source order despite failed height/wall');
    assert(result.state.phase === 'retiring' && result.state.reason === 'height-change' && result.children.length === 0,
      'height equality100 fails after all probes, no late pulse');
    equal(result.state.life, 599, 'failed active update still decrements life');
    equal(original.pos.y, 0, 'hooks mutate only copied state');
    let snapshotRead = false;
    stepGBlackGroundWaveParent(active(), { ...parentContext(), previousPosition: { x: -10, y: -20, z: -30 },
      wallSegment: from => { snapshotRead = true; equal(from.z, -30, 'explicit source+2c snapshot reaches wall helper'); return false; },
    });
    assert(snapshotRead, 'scheduler snapshot probe exercised');
  }
  {
    const ctx = parentContext();
    const moved = stepGBlackGroundWaveParent(active(ctx), { ...ctx, attraction83714: state => {
      state.pos.z = 9000; return false;
    } });
    assert(moved.state.phase === 'active' && moved.children.length === 1, 'origin range captured before attraction, spacing measured afterward');
    equal(moved.children[0]!.pos.z, 9000, 'pulse uses post-attraction position');
    equal(moved.state.lastEmit.z, 9000, 'lastEmit updated before allocation');
    assert(stepGBlackGroundWaveParent(moved.state, ctx).state.reason === 'distance', 'next update sees attracted position outside range');
  }
  {
    const cases: Array<{ reason: GBlackGroundWaveReason; state?: Partial<GBlackGroundWaveParentState>; ctx?: Partial<GBlackGroundWaveParentContext> }> = [
      { reason: 'height-change', ctx: { terrainHeight: () => 100 } },
      { reason: 'height-change', ctx: { terrainHeight: () => -100 } },
      { reason: 'wall', ctx: { wallSegment: () => true } },
      { reason: 'distance', state: { pos: { x: pos.x, y: 0, z: pos.z + 4950 } } },
      { reason: 'bounds', ctx: { outsideBounds: () => true } },
      { reason: 'attraction', ctx: { attraction83714: () => true } },
      { reason: 'lifetime', state: { life: 1 } },
    ];
    for (const test of cases) {
      const retired = stepGBlackGroundWaveParent({ ...active(), ...test.state }, { ...parentContext(), ...test.ctx });
      assert(retired.state.phase === 'retiring' && retired.state.reason === test.reason && retired.children.length === 0,
        `${test.reason} failure stages cleanup without a pulse`);
      const released = stepGBlackGroundWaveParent(retired.state, parentContext());
      assert(released.state.phase === 'released' && released.children.length === 0, 'next update releases');
      const freed = stepGBlackGroundWaveParent(released.state, parentContext());
      assert(freed.state.phase === 'freed', 'following update frees');
      assert(stepGBlackGroundWaveParent(freed.state, parentContext()).children.length === 0, 'freed emitter inert');
    }
    assert(stepGBlackGroundWaveParent(active(), { ...parentContext(), terrainHeight: () => 99 }).state.phase === 'active',
      'sub100 terrain height change remains alive');
    let state = { ...active(), motion: { x: 0, y: 0, z: 0 } };
    for (let tick = 1; tick < 600; tick++) {
      state = stepGBlackGroundWaveParent(state, parentContext()).state;
      assert(state.phase === 'active', 'emitter survives until600th active update');
    }
    const final = stepGBlackGroundWaveParent(state, parentContext());
    assert(final.state.reason === 'lifetime' && final.state.life === 0, 'life600 exact endpoint');
  }
  {
    const calls: string[] = [], original = pendingChild(2, 3);
    const ctx: GBlackGroundWaveChildContext = {
      registerHit: () => { calls.push('hit'); return true; },
      rngByte: () => { calls.push('rng'); return 255; },
      terrainHeight: (_point, probe) => { calls.push('terrain'); equal(probe, 100, 'pulse probe100'); return 25; },
    };
    let state = stepGBlackGroundWaveChild(original, ctx).state;
    assert(calls.join(',') === 'hit,rng,terrain', 'HIT registration precedes single RNG draw and terrain');
    assert(state.phase === 'active' && state.hitActive && state.age === 0 && state.life === 30, 'pulse init activates HIT without aging');
    equal(state.yawBam, 0xff00, 'source RNG8 yaw shifted8');
    equal(state.pos.y, 25, 'pulse projects independently at initialization');
    equal(state.visualScale[0], Math.fround(WAVE.horizontalScale * 2), 'visual horizontal model factor');
    equal(state.visualScale[1], 1, 'visual vertical model factor');
    equal(state.collisionScale * WAVE.hitRadius, 450, 'collision scale independent from visual factor');
    for (let age = 1; age <= 29; age++) {
      state = stepGBlackGroundWaveChild(state, ctx).state;
      assert(state.hitActive && state.phase === 'active' && state.age === age, 'pulse remains registered through age29');
      equal(state.pos.y, 25, 'active pulse stays stationary without terrain resample');
      if (age === 3) equal(state.visualScale[1], 5, 't3 vertical peak follows modelScale');
    }
    const last = stepGBlackGroundWaveChild(state, ctx).state;
    assert(last.age === 30 && last.phase === 'retiring' && !last.hitActive && last.life === 0, 'age30 disables HIT before collision');
    equal(last.visualScale[0], 1, 'age30 final horizontal keyframe');
    equal(last.visualScale[1], 0, 'age30 final vertical keyframe still applied');
    assert(calls.join(',') === 'hit,rng,terrain', 'no active-update RNG, HIT reregistration or terrain');
    const released = stepGBlackGroundWaveChild(last, ctx).state;
    const freed = stepGBlackGroundWaveChild(released, ctx).state;
    assert(released.phase === 'released' && freed.phase === 'freed', 'pulse staged cleanup');
    assert(!stepGBlackGroundWaveChild(freed, ctx).state.hitActive, 'freed pulse inert');
    assert(original.phase === 'pending' && !original.hitActive && original.pos.y === 300, 'child initializer immutable');
    assert(state.hitActive && state.age === 29, 'child terminal update immutable');
  }
  {
    const result = stepGBlackGroundWaveChild(pendingChild(), {
      registerHit: () => false,
      rngByte: () => { throw new Error('failed allocation must not draw RNG'); },
      terrainHeight: () => { throw new Error('failed allocation must not project terrain'); },
    }).state;
    assert(result.phase === 'retiring' && result.reason === 'hit-allocation' && !result.hitActive,
      'HIT allocation failure retires without side effects');
    assert(stepGBlackGroundWaveChild(result, childContext()).state.phase === 'released', 'allocation failure cleanup deferred one update');
    for (const byte of [0, 1, 127, 128, 255]) {
      let draws = 0;
      const state = stepGBlackGroundWaveChild(pendingChild(), { ...childContext(), rngByte: () => { draws++; return byte; } }).state;
      assert(state.yawBam === byte << 8 && draws === 1, 'each pulse consumes one independent RNG byte');
    }
    close(gblackGroundWaveVisualScale(1.5, 1)[1], 1.5, 'first keyframe segment linear');
    close(gblackGroundWaveVisualScale(16.5, 1)[1], 1.25, 'second keyframe segment linear');
    close(gblackGroundWaveVisualScale(16.5, 1)[0], .45, 'horizontal second segment linear');
  }
  for (const ownerInvalid of ['owner-dead', 'owner-changed'] as const) {
    for (const initialized of [false, true]) {
      const noParentCalls: GBlackGroundWaveParentContext = {
        ownerInvalid,
        terrainHeight: () => { throw new Error('owner invalidation must precede initialization/motion'); },
        targetPosition: () => { throw new Error('owner invalidation must precede targeting'); },
      };
      const parent = stepGBlackGroundWaveParent(initialized ? active() : pending(), noParentCalls);
      assert(parent.state.phase === 'released' && parent.state.reason === ownerInvalid && parent.children.length === 0,
        'owner invalidation dispatches parent cleanup immediately');
      assert(stepGBlackGroundWaveParent(parent.state, noParentCalls).state.phase === 'freed', 'invalid owner does not trap parent cleanup');
      const noChildCalls: GBlackGroundWaveChildContext = {
        ownerInvalid,
        registerHit: () => { throw new Error('invalid owner cannot register HIT'); },
        rngByte: () => { throw new Error('invalid owner cannot draw RNG'); },
        terrainHeight: () => { throw new Error('invalid owner cannot project terrain'); },
      };
      const child = stepGBlackGroundWaveChild(initialized ? stepGBlackGroundWaveChild(pendingChild(), childContext()).state :
        pendingChild(), noChildCalls).state;
      assert(child.phase === 'released' && !child.hitActive && child.reason === ownerInvalid,
        'owner invalidation disables pulse before immediate cleanup');
      assert(stepGBlackGroundWaveChild(child, noChildCalls).state.phase === 'freed', 'invalid owner does not trap pulse cleanup');
    }
  }
  {
    const init = stepGBlackGroundWaveParent(pending(), parentContext());
    const child = stepGBlackGroundWaveChild(createGBlackGroundWaveChild(init.children[0]!), childContext()).state;
    const parent = stepGBlackGroundWaveParent({ ...init.state, life: 1 }, parentContext()).state;
    assert(parent.phase === 'retiring' && stepGBlackGroundWaveChild(child, childContext()).state.hitActive,
      'normal parent retirement does not invalidate stationary child');
  }
}
