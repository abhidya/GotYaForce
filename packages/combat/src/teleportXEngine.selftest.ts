/** Source-order tests for146dcc/146ed8/146f6c/147094, independent of Battle,
 * input admission, actor metadata, fake projectiles and the old family adapter.
 * The normalization fixture is a bounded host implementation, not a PPC SDK
 * reciprocal-square-root oracle. The production engine exposes that seam.
 */
import { tickTeleportXEngine, type TeleportXEngineHooks, type TeleportXEngineState,
  type TeleportXVec3 } from './teleportXEngine.js';

function check(value: unknown, label: string): void {
  if (!value) throw new Error(`[teleportXEngine] ${label}`);
}
function same(actual: unknown, expected: unknown, label: string): void {
  check(JSON.stringify(actual) === JSON.stringify(expected),
    `${label}: expected ${JSON.stringify(expected)}, got ${JSON.stringify(actual)}`);
}
const f32 = Math.fround;
const copy = (v: TeleportXVec3): TeleportXVec3 => ({ ...v });

function fixture() {
  const s: TeleportXEngineState = { phase: 0, dt: 1,
    pos: { x: 10, y: 20, z: 30 }, savedOwnPos5e8: { x: 8, y: 17, z: 34 },
    motion: { x: 91, y: 92, z: 93 }, destination9c: { x: -1, y: -2, z: -3 },
    capturedTargetCc: false, target518: { x: 13, y: 24, z: 30 },
    recentMeleeTimer144: 8, modelScaleB4: .5, controlWord: 0x83,
    airLatch54a: 9, timer558: 99, flags272: 0x8100, visibility82: 0x47,
    movementFlag87: 8, movementCue5e4: 7, actionFlag73f: 1, carriedSlot96: 6,
    hSpeed: 3, yVel: 4, hDecel: 5, gravityCoeff: -2, descriptorGravity6c: -.75 };
  const calls: unknown[][] = [];
  const h: TeleportXEngineHooks = {
    normalize6ebb4: direction => {
      calls.push(['normalize', copy(direction)]);
      const length = Math.hypot(direction.x, direction.y, direction.z);
      if (length > 0) {
        direction.x = f32(direction.x / length);
        direction.y = f32(direction.y / length);
        direction.z = f32(direction.z / length);
      } else { direction.x = 0; direction.y = 1; direction.z = 0; }
    },
    feedback061a8: (_s, code) => {
      calls.push(['feedback', code, s.flags272, s.visibility82, s.phase, s.timer558]);
    },
    ground677b0: () => {
      calls.push(['ground', copy(s.pos), s.phase, s.flags272, s.visibility82, s.timer558]);
    },
    ammo6dbe0: (_s, cell, count, debit) => {
      calls.push(['ammo', cell, count, debit, s.phase, s.timer558, copy(s.pos),
        copy(s.destination9c), copy(s.motion), s.controlWord, s.movementCue5e4,
        s.movementFlag87, s.airLatch54a]);
      return true;
    },
    cueF036c: (_s, code) => { calls.push(['cue', code, s.phase, s.timer558]); },
    startStream: (_s, mask, group, slot, frame, blend, mode) => {
      calls.push(['start', mask, group, slot, frame, blend, mode, s.phase, s.timer558,
        s.visibility82, s.hDecel, s.hSpeed, s.yVel, s.gravityCoeff, s.flags272]);
    },
    tickStream: (_s, mask) => { calls.push(['tick', mask, s.phase, s.timer558, s.flags272]); },
    groundIdle6a474: () => {
      calls.push(['ground-idle', s.controlWord, s.flags272, s.actionFlag73f, s.timer558]);
    },
    airReturn6a5a4: () => {
      calls.push(['air-return', s.controlWord, s.flags272, s.actionFlag73f, s.timer558]);
    },
  };
  return { s, h, calls, tick: () => tickTeleportXEngine(s, h) };
}

function checkOwnHistoryAndSameCall(): void {
  const t = fixture();
  same(t.tick(), { type: 'continue' }, 'setup remains active');
  same(t.calls, [
    ['ammo', 2, 1, true, 1, 4, { x: 10, y: 20, z: 30 },
      { x: 110, y: 170, z: -170 }, { x: 2, y: 3, z: -4 }, 0xc3, 45, 1, 0],
    ['feedback', 9, 0x8100, 0x47, 1, 4],
    ['ground', { x: 12, y: 23, z: 26 }, 1, 0x8102, 0x47, 4],
  ], 'own-history destination is separate from current position until same-call P1');
  same([t.s.phase, t.s.timer558, t.s.airLatch54a], [1, 3, 0], 'setup4 consumes first dt immediately');
  same([t.s.hSpeed, t.s.yVel, t.s.hDecel, t.s.gravityCoeff, t.s.recentMeleeTimer144],
    [3, 4, 5, -2, 8], 'setup does not invent physics zeroing or decrement melee timer144');
  same(t.s.savedOwnPos5e8, { x: 8, y: 17, z: 34 }, 'engine does not update own history');
  for (const recent of [0, -.5]) {
    const expired = fixture(); expired.s.capturedTargetCc = true; expired.s.recentMeleeTimer144 = recent;
    expired.h.normalize6ebb4 = () => { throw new Error('expired144 cannot target'); };
    expired.tick();
    same(expired.s.destination9c, { x: 110, y: 170, z: -170 }, 'expired144 chooses own history despite captured target');
  }
  const stationary = fixture(); stationary.s.savedOwnPos5e8 = copy(stationary.s.pos);
  stationary.tick();
  same([stationary.s.motion, stationary.s.destination9c, stationary.s.pos],
    [{ x: 0, y: 0, z: 0 }, { x: 10, y: 20, z: 30 }, { x: 10, y: 20, z: 30 }],
    'zero own displacement has no arbitrary facing or forward fallback');
}

function checkCapturedTargetAndNormalizeBoundary(): void {
  const t = fixture(); t.s.capturedTargetCc = true;
  t.tick();
  same(t.calls[0], ['normalize', { x: 3, y: 4, z: 0 }], 'target normalization receives captured518 minus current20');
  same(t.s.destination9c, { x: f32(10 + f32(f32(.6) * 400)), y: 340, z: 30 },
    'target destination uses800*modelScale, independent from own motion');
  same([t.s.airLatch54a, t.s.motion, t.s.pos], [0x40, { x: 2, y: 3, z: -4 }, { x: 12, y: 23, z: 26 }],
    'recent-target branch forces air latch without teleporting or replacing motion');
  same(t.calls.map(c => c[0]), ['normalize', 'ammo', 'feedback', 'ground'], 'normalize precedes debit and same-call phase1');
  const zero = fixture(); zero.s.capturedTargetCc = true; zero.s.target518 = copy(zero.s.pos);
  zero.tick();
  same(zero.calls[0], ['normalize', { x: 0, y: 0, z: 0 }], 'zero target vector still calls original normalization boundary');
  same(zero.s.destination9c, { x: 10, y: 420, z: 30 }, 'verified6ebb4 zero policy is positive Y, not facing or no movement');
  const air = fixture(); air.s.controlWord = 0x800000c3;
  air.tick();
  same([air.s.airLatch54a, air.s.controlWord], [0x40, 0x800000c3], 'capture air before66530 and preserve bit80/upper bits');
  const hook = fixture(); hook.s.capturedTargetCc = true;
  hook.h.normalize6ebb4 = direction => { direction.x = -1; direction.y = 0; direction.z = 0; };
  hook.tick();
  same(hook.s.destination9c, { x: -390, y: 20, z: 30 }, 'engine consumes supplied SDK normalization result without re-normalizing');
}

function checkDebitAndSetupTiming(): void {
  const denied = fixture();
  denied.h.ammo6dbe0 = (s, cell, count, debit) => {
    denied.calls.push(['denied', cell, count, debit, s.phase, s.timer558, copy(s.pos)]);
    return false;
  };
  denied.tick();
  same(denied.calls.map(c => c[0]), ['denied', 'feedback', 'ground'], 'failed debit does not cancel source body');
  same([denied.s.phase, denied.s.timer558, denied.s.pos], [1, 3, { x: 12, y: 23, z: 26 }],
    'ignored debit return still runs setup movement');
  const fast = fixture(); fast.s.dt = 100;
  fast.tick();
  same([fast.s.phase, fast.s.timer558, fast.s.visibility82, fast.s.pos],
    [2, 16, 0x47, { x: 12, y: 23, z: 26 }], 'oversized setup dt resets16 without catching up into invisible travel');
  same(fast.calls.at(-1), ['cue', 0xf2, 2, 16], 'crossing setup boundary emits cue after reset');
  const zero = fixture(); zero.s.dt = 0; zero.tick(); zero.tick();
  same([zero.s.phase, zero.s.timer558, zero.s.pos], [1, 4, { x: 14, y: 26, z: 22 }],
    'P1 unscaled motion advances each call, even when dt iszero');
  same(zero.calls.filter(c => c[0] === 'ammo').length, 1, 'P1 never retries debit');
  const fractional = fixture(); fractional.s.phase = 1; fractional.s.timer558 = f32(.2);
  fractional.s.dt = f32(.1); fractional.s.motion = { x: .25, y: -.5, z: 1 };
  fractional.tick();
  same(fractional.s.timer558, f32(f32(.2) - f32(.1)), 'phase1 timer uses source single-precision subtraction');
  same(fractional.s.pos, { x: 10.25, y: 19.5, z: 31 }, 'phase1 motion is not multiplied by dt');
}

function checkTravelArithmeticAndVisibility(): void {
  const t = fixture(); t.s.phase = 2; t.s.timer558 = 16; t.s.dt = f32(.7);
  t.s.pos = { x: f32(.001), y: -30, z: 90 };
  t.s.destination9c = { x: f32(3.8), y: 700, z: -250 };
  const old = copy(t.s.pos), destination = copy(t.s.destination9c);
  const scale = f32(f32(.1) * t.s.dt), remaining = f32(1 - scale);
  const expected = { x: f32(f32(scale * destination.x) + f32(remaining * old.x)),
    y: f32(f32(scale * destination.y) + f32(remaining * old.y)),
    z: f32(f32(scale * destination.z) + f32(remaining * old.z)) };
  t.tick();
  same(t.s.pos, expected, '46588 uses separately rounded products and sum');
  same(t.s.pos.x, 0.2669300138950348, 'rounding-sensitive independent scalar expectation');
  check(t.s.pos.x !== f32(old.x + f32(f32(destination.x - old.x) * scale)),
    'fixture distinguishes source scales/add from delta lerp');
  same(t.calls, [['feedback', 9, 0x8100, 0x47, 2, 16],
    ['ground', expected, 2, 0x8102, 0, 16]], 'feedback precedes flags/hide; probe sees hidden state before decrement');
  same([t.s.phase, t.s.timer558, t.s.visibility82, t.s.flags272],
    [2, f32(16 - f32(.7)), 0, 0x8102], 'travel hides and suppresses defensive HIT registration');
  same(t.s.destination9c, destination, 'travel interpolation never changes frozen destination');
  const unclamped = fixture(); unclamped.s.phase = 2; unclamped.s.timer558 = 100;
  unclamped.s.dt = 20; unclamped.s.destination9c = { x: 20, y: 30, z: 40 };
  unclamped.tick();
  same(unclamped.s.pos, { x: 30, y: 40, z: 50 }, 'source interpolation scale is not clamped toone');
  const zero = fixture(); zero.s.phase = 2; zero.s.timer558 = 16; zero.s.dt = 0;
  zero.tick();
  same([zero.s.pos, zero.s.timer558, zero.s.visibility82], [{ x: 10, y: 20, z: 30 }, 16, 0],
    'dt0 travel still hides and probes without advancing or forcing completion');
}

function checkRecoveryStart(): void {
  for (const [latch, slot] of [[0, 0], [0x40, 13]] as const) {
    const t = fixture(); t.s.phase = 2; t.s.timer558 = .25; t.s.dt = .5;
    t.s.airLatch54a = latch; t.s.controlWord = latch === 0 ? 0x40 : 0;
    t.tick();
    same(t.calls.map(c => c[0]), ['feedback', 'ground', 'start', 'feedback', 'cue'],
      'travel crossing runs recovery start/feedback10/cueF2 after movement and probe');
    same(t.calls.slice(2), [
      ['start', 15, 0, slot, -1, 2, 1, 3, 2, 0x47, 0, 0, 0, -.75, 0x8102],
      ['feedback', 10, 0x8102, 0x47, 3, 2], ['cue', 0xf2, 3, 2],
    ], 'recovery selects captured air latch and exact authored-frame/blend2/mode1 overrides');
    same([t.s.phase, t.s.timer558], [3, 2], 'recovery2 does not consume leftover dt or tick stream samecall');
    same(t.s.controlWord, latch === 0 ? 0x40 : 0, 'engine does not invent recovery posture changes from stream slot');
  }
  const byte = fixture(); byte.s.phase = 2; byte.s.timer558 = 0; byte.s.carriedSlot96 = 0xff;
  byte.tick();
  same(byte.s.visibility82, 0x40, 'restored visibility/equipment byte wraps after carriedSlot plus0x41');
}

function checkRecoveryCleanup(): void {
  for (const [control, expected, exit] of [[0x80000083, 0x80000080, 'ground'], [0xc3, 0xc0, 'air']] as const) {
    const t = fixture(); t.s.phase = 3; t.s.timer558 = 2; t.s.controlWord = control;
    t.tick();
    same(t.calls, [['tick', 15, 3, 2, 0x8102]], 'recovery asserts bit2 before stream tick and decrements afterward');
    same([t.s.timer558, t.s.flags272, t.s.actionFlag73f], [1, 0x8102, 1], 'positive recovery retains suppression and action flag');
    t.calls.length = 0;
    same(t.tick(), { type: 'cleanup', exit }, 'zero timer performs source-selected exit');
    same(t.calls, [['tick', 15, 3, 1, 0x8102],
      [exit === 'ground' ? 'ground-idle' : 'air-return', expected, 0x8100, 0, 0]],
      'cleanup clears only bit2 and control lowtwo/action73f before corresponding return helper');
    same([t.s.phase, t.s.visibility82, t.s.movementCue5e4, t.s.movementFlag87],
      [3, 0x47, 7, 8], 'no invented phase reset, visibility reset or movement-helper reset on exit');
  }
}

function checkLiveHookBoundaries(): void {
  const debit = fixture();
  debit.h.ammo6dbe0 = s => { s.pos.x = 100; s.motion.x = -5; s.dt = .5; return false; };
  debit.tick();
  same([debit.s.pos.x, debit.s.timer558], [95, 3.5], 'same-callP1 sees live post-debit state');
  const ground = fixture(); ground.s.phase = 2; ground.s.timer558 = 8;
  ground.h.ground677b0 = s => {
    same([s.visibility82, s.flags272, s.timer558], [0, 0x8102, 8], 'probe boundary sees hide/defense before timer update');
    s.pos.y = 321; s.timer558 = .5; s.dt = 1; s.descriptorGravity6c = -.125; s.carriedSlot96 = 2;
  };
  ground.tick();
  same([ground.s.pos.y, ground.s.phase, ground.s.gravityCoeff, ground.s.visibility82],
    [321, 3, -.125, 0x43], 'ground correction and later source reads consume live state');
  const stream = fixture(); stream.s.phase = 3; stream.s.timer558 = 9; stream.s.controlWord = 0xc3;
  stream.h.tickStream = s => {
    s.timer558 = .25; s.dt = .5; s.controlWord &= ~0x40; s.flags272 |= 0x20;
  };
  same(stream.tick(), { type: 'cleanup', exit: 'ground' }, 'exit selection uses post-stream control, not captured latch');
  same(stream.calls.at(-1), ['ground-idle', 0x80, 0x8120, 0, -.25], 'post-stream unrelated flags survive cleanup');
  const stop = fixture(); stop.s.phase = 3; stop.s.timer558 = 2;
  const interruption = new Error('host interrupted stream');
  stop.h.tickStream = () => { throw interruption; };
  let thrown: unknown;
  try { stop.tick(); } catch (error) { thrown = error; }
  check(thrown === interruption, 'host exception propagates rather than inventing action recovery');
  same([stop.s.phase, stop.s.timer558, stop.s.flags272, stop.s.actionFlag73f, stop.calls],
    [3, 2, 0x8102, 1, []], 'interrupted hook has no synthesized decrement/cleanup/exit after boundary');
  const unknown = fixture(); unknown.s.phase = 0xff;
  const before = JSON.stringify(unknown.s);
  same(unknown.tick(), { type: 'unsupported', phase: -1 }, 'unknown signed phase is explicit inert boundary');
  same(JSON.stringify(unknown.s), before, 'unknown phase does not invent timeout or state mutations');
  same(unknown.calls, [], 'unknown phase calls no host hook');
}

function checkFullPhaseSchedule(): void {
  const t = fixture();
  for (let update = 1; update <= 22; update++) {
    const outcome = t.tick();
    const expectedPhase = update < 4 ? 1 : update < 20 ? 2 : 3;
    same(t.s.phase, expectedPhase, `dt1 source phase after update${update}`);
    same(t.s.visibility82, update >= 5 && update < 20 ? 0 : 0x47,
      `source visibility interval after update${update}`);
    same((t.s.flags272 & 2) !== 0, update < 22, `defensive registration suppression after update${update}`);
    same(outcome.type, update === 22 ? 'cleanup' : 'continue', `source outcome after update${update}`);
  }
  same(t.calls.filter(c => c[0] === 'ammo').length, 1, 'full body debits exactlyonce');
  same(t.calls.filter(c => c[0] === 'ground').length, 20, 'four setup drifts and16 travel probes');
  same(t.calls.filter(c => c[0] === 'tick').length, 2, 'two recovery stream ticks');
  same(t.calls.filter(c => c[0] === 'cue').length, 2, 'two F2 transition cues, no projectile cue');
  same(t.calls.filter(c => c[0] === 'start').length, 1, 'one recovery start only');
}

export function runTeleportXEngineSelfTest(): void {
  checkOwnHistoryAndSameCall();
  checkCapturedTargetAndNormalizeBoundary();
  checkDebitAndSetupTiming();
  checkTravelArithmeticAndVisibility();
  checkRecoveryStart();
  checkRecoveryCleanup();
  checkLiveHookBoundaries();
  checkFullPhaseSchedule();
}
