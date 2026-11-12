/** Independent observers of18d350/438/534/cb0 control flow and f32 stores.
 * Hook traces are not instruction-level console equivalence or terrain parity. */
import { tickGRedShotEngine, type GRedShotEngineHooks, type GRedShotEngineState,
  type GRedShotFamily } from './gredShotEngine.js';

function check(value: unknown, label: string): void {
  if (!value) throw new Error(`[gredShotEngine] ${label}`);
}
function same(actual: unknown, expected: unknown, label: string): void {
  check(JSON.stringify(actual) === JSON.stringify(expected),
    `${label}: expected ${JSON.stringify(expected)}, got ${JSON.stringify(actual)}`);
}
function fixture(family: GRedShotFamily = 'red') {
  const s: GRedShotEngineState = { family, phase: 0, dt: 1,
    pos: { x: 20, y: 30, z: 40 }, savedGroundPos: { x: 10, y: 10, z: 10 },
    motion: { x: 9, y: 9, z: 9 }, poseAccum7c: { x: 1, y: 2, z: 3 },
    controlWord: 0xffffffff, hSpeed: 4, yVel: 5, hDecel: 6, gravityCoeff: 7,
    rootAngle1900: -101, shift18da: -3, sideBlend1dfc: -5,
    latch745: 1, timer560: 9, repeatTimer558: 0, streamSlot6ee: 0,
    remaining6ef: 3, ammo774: 5, input5d4: 0, input5d8: 0,
    contactP0: 0, completed1cee: 0, actionFlag6e8: 1, actionFlag73f: 1,
    accumulator80c: 99 };
  const calls: unknown[][] = [];
  const h: GRedShotEngineHooks = {
    aim6d0dc: (_s, mode, arg) => { calls.push(['aim', mode, arg, s.dt]); return false; },
    startStream: (_s, mask, group, slot, start, blend) => { calls.push(['start', mask, group, slot, start, blend]); },
    tickStream: (_s, mask) => { calls.push(['tick', mask, s.dt]); },
    ammo6dbe0: (_s, cell, count, debit) => {
      calls.push(['ammo', cell, count, debit, s.timer560, s.repeatTimer558, s.streamSlot6ee]);
      if (debit) s.ammo774 -= count;
      return true;
    },
    spawnC3be0: (_s, row) => { calls.push(['spawn', row, s.remaining6ef]); },
    capture6bf80: () => { calls.push(['capture', s.latch745]); },
    ground679d0: () => { calls.push(['ground', s.accumulator80c]); },
    carryEffectB22f4: () => { calls.push(['effect']); },
    groundIdle6a474: () => { calls.push(['idle', s.actionFlag6e8, s.actionFlag73f, s.controlWord]); },
    idleTransition6a668: (_s, duration) => { calls.push(['transition', duration, s.controlWord & 3]); },
    redispatch6a3d0: (_s, action, variant, phase) => { calls.push(['redispatch', action, variant, phase]); },
  };
  return { s, h, calls, tick: () => tickGRedShotEngine(s, h) };
}

function checkAdmission(): void {
  const { s, calls, tick } = fixture();
  tick();
  same(calls, [['aim', 193, 0, 1], ['start', 15, 2, 0, undefined, undefined], ['ground', 99]],
    'phase0 aim/start/carry order; no stream tick, allocation or carry effect');
  same([s.phase, s.latch745, s.timer560, s.repeatTimer558, s.streamSlot6ee, s.accumulator80c],
    [1, 0, 30, 0, 0, 0], 'phase0 source writes only');
  same([s.controlWord, s.hSpeed, s.yVel, s.hDecel, s.gravityCoeff, s.poseAccum7c],
    [0xffffff4f, 0, 0, 0, 0, { x: 0, y: 0, z: 0 }], 'zero source physics/pose and source control mask');
  same(s.motion, { x: 9.5, y: 19, z: 28.5 }, 'carry uses own5e8 history');
  same(s.pos, { x: 29.5, y: 49, z: 68.5 }, 'carry is added without dt scaling');
  same([s.rootAngle1900, s.shift18da, s.sideBlend1dfc], [-96, -2, -3],
    'three independent signed wrapper channels');
}

function checkReadiness(): void {
  const t = fixture();
  t.s.phase = 1;
  t.s.timer560 = 30;
  t.s.dt = .5;
  t.h.aim6d0dc = () => { t.calls.push(['ready', t.s.dt]); return true; };
  t.tick();
  same([t.s.phase, t.s.timer560], [1, 30], 'ready short circuit does not decrement timer and P0zero prevents fire');
  same(t.calls.slice(0, 2), [['tick', 15, .5], ['ready', .5]], 'phase1 tick before aim with ordinary dt');

  t.calls.length = 0;
  t.s.contactP0 = -1;
  t.h.aim6d0dc = () => false;
  t.tick();
  same(t.calls[0], ['tick', 15, 0], 'nonzero P0 freezes stream dt even while aim is unready');
  same([t.s.phase, t.s.timer560, t.s.dt], [1, 29.5, .5], 'restored dt still consumes readiness timer');

  t.s.timer560 = .25;
  t.tick();
  same([t.s.phase, t.s.timer560, t.s.repeatTimer558, t.s.ammo774], [2, 20, 12, 4],
    'timeout releases with negative P0 and original dt');

  const u = fixture();
  u.s.phase = 1;
  u.s.timer560 = -100;
  u.tick();
  check(!u.calls.some(c => c[0] === 'ammo'), 'timeout alone cannot fire without signed P0');
  u.h.tickStream = state => { u.calls.push(['tick', state.dt]); state.contactP0 = 1; };
  u.tick();
  same(u.s.phase, 2, 'same-call stream P0 write gates release');
  same(u.calls.filter(c => c[0] === 'spawn').length, 1, 'release is exactly once');
}

function checkRelease(): void {
  for (const [family, interval, row] of [['red', 12, 43], ['neo', 8, 101], ['black', 16, 102]] as const) {
    const t = fixture(family);
    t.s.phase = 1; t.s.contactP0 = 1; t.s.timer560 = 0;
    t.tick();
    same(t.calls.slice(0, 4), [['tick', 15, 0], ['aim', 193, 0, 1],
      ['ammo', 0, 1, true, 20, interval, 1], ['spawn', row, 3]],
    `${family}: release sets both timers and slot before debit; count decrements after spawn`);
    same([t.s.remaining6ef, t.s.ammo774], [2, 4], `${family}: one debit`);
    same(t.calls.slice(-2).map(c => c[0]), ['ground', 'effect'], 'phase1 still carries after release');
  }
  const exhausted = fixture();
  exhausted.s.phase = 1; exhausted.s.contactP0 = 1; exhausted.s.timer560 = 0; exhausted.s.ammo774 = 1;
  exhausted.tick();
  same([exhausted.s.remaining6ef, exhausted.s.ammo774], [0, 0], 'empty current source cell forces remaining6ef zero');

  const failed = fixture('black');
  failed.s.phase = 1; failed.s.contactP0 = 1; failed.s.timer560 = 0;
  failed.h.ammo6dbe0 = () => false;
  failed.tick();
  same([failed.s.phase, failed.s.timer560, failed.s.repeatTimer558, failed.s.streamSlot6ee,
    failed.s.remaining6ef, failed.s.ammo774], [2, 20, 16, 1, 3, 5], 'failed initial allocation retains source release transition');
  check(!failed.calls.some(c => c[0] === 'spawn' || c[0] === 'idle'), 'failed initial allocation neither spawns nor performs phase2 cleanup');
}

function checkRepeat(): void {
  for (const p0 of [-1, 0, 1]) {
    const t = fixture();
    t.s.phase = 2; t.s.contactP0 = p0; t.s.controlWord = 3;
    t.s.input5d4 = 0x20; t.s.repeatTimer558 = .5; t.s.dt = .5;
    t.tick();
    same([t.s.phase, t.s.repeatTimer558, t.s.latch745], [2, 0, 1], 'expiry checked before decrement; edge latches');
    check(!t.calls.some(c => c[0] === 'ammo'), 'crossing zero does not check ammo early');
    t.calls.length = 0;
    t.s.input5d4 = 1; t.s.input5d8 = 0xf0; t.s.completed1cee = 1;
    const oldPos = { ...t.s.pos };
    t.tick();
    same(t.calls, [['tick', 15, .5], ['ammo', 0, 1, false, 9, 0, 0], ['capture', 1],
      ['start', 15, 2, 1, p0 < 0 ? undefined : 4, p0 < 0 ? undefined : 1]],
    'repeat checks only, captures, clears latch and starts before cancellation tests');
    same([t.s.phase, t.s.latch745, t.s.ammo774, t.s.pos], [1, 0, 5, oldPos],
      'repeat restarts phase1 without debit, carry or exit');
  }
  const air = fixture();
  air.s.phase = 2; air.s.repeatTimer558 = 0; air.s.latch745 = 1;
  air.tick();
  same(air.calls.map(c => c[0]), ['tick', 'ammo', 'capture', 'redispatch'], 'air handoff returns before stream/carry/exit');
  same(air.calls.at(-1), ['redispatch', 0, 3, 0], 'air source action/variant/phase');
  same([air.s.phase, air.s.latch745, air.s.ammo774], [2, 0, 5], 'air redispatch owns next phase');

  const zero = fixture();
  zero.s.phase = 2; zero.s.repeatTimer558 = 0; zero.s.latch745 = 0;
  zero.tick();
  check(!zero.calls.some(c => c[0] === 'ammo'), 'expiry without fresh latch is not auto-repeat');
}

function checkCleanup(): void {
  for (const reason of ['ammo', 'direction', 'button', 'completion'] as const) {
    const t = fixture();
    t.s.phase = 2; t.s.controlWord = 0x93; t.s.repeatTimer558 = reason === 'ammo' ? 0 : 5;
    t.s.latch745 = reason === 'ammo' ? 1 : 0;
    if (reason === 'ammo') t.h.ammo6dbe0 = () => { t.calls.push(['failed-check']); return false; };
    if (reason === 'direction') t.s.input5d8 = 0x20;
    if (reason === 'button') t.s.input5d4 = 1;
    if (reason === 'completion') t.s.completed1cee = 1;
    const pos = { ...t.s.pos };
    t.tick();
    same(t.calls.slice(-2), [['idle', 0, 0, 0x90], ['transition', 20, 0]],
      `${reason}: clear action bytes and bits before both return hooks`);
    same([t.s.timer560, t.s.pos], [9, pos], `${reason}: no fabricated20 lockout and no carry after exit`);
    check(!t.calls.some(c => ['start', 'spawn', 'capture', 'ground', 'effect'].includes(String(c[0]))),
      `${reason}: immediate cleanup skips other effects`);
  }
}

function checkFloatCarryAndWrappers(): void {
  const t = fixture();
  t.s.phase = 1; t.s.motion = { x: .1, y: -.2, z: .3 }; t.s.dt = 0;
  t.s.pos = { x: 100.25, y: 5.1, z: -.1 };
  const old = { ...t.s.pos }, motion = { ...t.s.motion };
  t.tick();
  for (const axis of ['x', 'y', 'z'] as const) {
    const expected = Math.fround(motion[axis] * Math.fround(.95));
    same(t.s.motion[axis], expected, 'per-component f32 carry multiply');
    same(t.s.pos[axis], Math.fround(old[axis] + expected), 'per-component f32 position add');
  }
  same([t.s.rootAngle1900, t.s.shift18da, t.s.sideBlend1dfc], [-96, -2, -3], 'wrappers run even dt0');
  t.s.phase = 99;
  t.calls.length = 0;
  t.tick();
  same([t.s.rootAngle1900, t.s.shift18da, t.s.sideBlend1dfc], [-92, -1, -2], 'wrapper independent of phase dispatch');
  same(t.calls, [], 'unadmitted phase has no synthetic behavior');

  for (const magnitude of [2.99, 3, 3.01]) {
    const edge = fixture();
    edge.s.phase = 1;
    // The source magnitude check follows679d0, so observe its live result.
    edge.h.ground679d0 = state => { state.motion = { x: magnitude, y: 0, z: 0 }; };
    edge.tick();
    same(edge.calls.some(c => c[0] === 'effect'), magnitude > 3,
      'FLOAT8043b128 cosmetic effect threshold is strictly greater than3');
  }
}

export function runGredShotEngineSelfTest(): void {
  checkAdmission(); checkReadiness(); checkRelease(); checkRepeat(); checkCleanup(); checkFloatCarryAndWrappers();
}
