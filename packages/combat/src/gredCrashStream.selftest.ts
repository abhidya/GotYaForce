/** Independent observer checks for RED g4s0 at8036704c, not console equivalence.
 * Expectations derive from the original packet's absolute frame waits,
 * descriptor803679a2 EndFrame80, recovery803675e2 EndFrame1, playAnim487ec/
 * 4892c, clocks49f10/4a00c, and4cd24/4c050 wait parsing. Mode8 freezes the
 * whole animation update; release parses the next wait before advancing once.
 * Fractional and oversized deltas test this pure clock, not live HIT parity.
 */
import {
  createGRedCrashStream,
  tickGRedCrashStream,
  type GRedCrashStream,
  type GRedCrashStreamEvent,
} from './gredCrashStream.js';

function check(value: unknown, label: string): void {
  if (!value) throw new Error(`[gredCrashStream] ${label}`);
}

function same(actual: unknown, expected: unknown, label: string): void {
  check(JSON.stringify(actual) === JSON.stringify(expected),
    `${label}: expected ${JSON.stringify(expected)}, got ${JSON.stringify(actual)}`);
}

const GATE_EVENTS: readonly GRedCrashStreamEvent[] = [
  { gate: 7, callbacks: [{ callback: 1, arg: 0 }] },
  { gate: 34, strength: 0, faceGate: 1, callbacks: [{ callback: 1, arg: 1 }] },
  { gate: 40, contact: 1, aux: 0, callbacks: [{ callback: 2, arg: 0 }] },
  { gate: 41, callbacks: [{ callback: 1, arg: 4 }] },
  { gate: 52, callbacks: [{ callback: 1, arg: 2 }] },
  { gate: 62 },
  { gate: 64, contact: -1, aux: 0, strength: -1, faceGate: 0 },
  { gate: 68, callbacks: [{ callback: 1, arg: 3 }] },
];

interface TraceExpectation {
  dt: number;
  gateTicks: readonly number[];
  holdEntryTick: number;
  holdReleaseTick: number;
  endTick: number;
  endElapsed: number;
  recoveryTick: number;
  completeTick: number;
  finalBlendMode: number;
}

// dt1: main blend holds2 updates, plus9 frozen countdown updates.
// dt.5: main blend holds5 updates, plus19 frozen countdown updates.
// Gates read the old frame. Recovery starts the update after raw end80;
// completion reads elapsed15 on the update after it first reaches15.
const TRACES: readonly TraceExpectation[] = [
  { dt: 1, gateTicks: [10, 37, 43, 44, 55, 65, 76, 80], holdEntryTick: 65,
    holdReleaseTick: 75, endTick: 91, endElapsed: 82, recoveryTick: 92,
    completeTick: 108, finalBlendMode: 0 },
  { dt: .5, gateTicks: [20, 74, 86, 88, 110, 130, 153, 161], holdEntryTick: 130,
    holdReleaseTick: 150, endTick: 184, endElapsed: 82.5, recoveryTick: 185,
    completeTick: 216, finalBlendMode: 1 },
];

function animationClocks(s: GRedCrashStream): readonly unknown[] {
  return [s.frame, s.elapsed, s.blendMode, s.blendElapsed, s.blendTotal,
    s.endFrame, s.stopped, s.ended];
}

function checkTrace(expected: TraceExpectation): void {
  const s = createGRedCrashStream(expected.dt);
  const gates: number[] = [];
  const observedCallbacks: number[][] = [];
  let firstEnd = 0;
  let recovery = 0;
  const label = `dt${expected.dt}`;
  for (let tick = 1; tick <= expected.completeTick; tick++) {
    const oldFrame = s.frame;
    const oldClocks = animationClocks(s);
    const event = tickGRedCrashStream(s, expected.dt);
    if (event.gate !== undefined) {
      check(oldFrame >= event.gate, `${label}: wait consumed the newly advanced frame`);
      same(event, GATE_EVENTS[gates.length], `${label}: authored writes at gate${event.gate}`);
      gates.push(tick);
    }
    for (const callback of event.callbacks ?? []) {
      observedCallbacks.push([callback.callback, callback.arg]);
    }
    if (tick === expected.holdEntryTick) {
      same([s.frame, s.waitCount, s.waitIndex], [62 + expected.dt, 10, 6],
        `${label}: mode8 entry advances but does not subtract countdown`);
    } else if (tick > expected.holdEntryTick && tick < expected.holdReleaseTick) {
      same(event, {}, `${label}: frozen countdown emitted an event`);
      same(animationClocks(s), oldClocks, `${label}: countdown advanced an animation clock`);
      same(s.waitCount, 10 - (tick - expected.holdEntryTick) * expected.dt,
        `${label}: subtract before countdown test`);
    } else if (tick === expected.holdReleaseTick) {
      same(event, {}, `${label}: countdown release must only parse next wait64`);
      same([s.frame, s.waitCount, s.waitIndex], [62 + 2 * expected.dt, 0, 6],
        `${label}: release resumes one normal animation update`);
    }
    if (s.ended && firstEnd === 0) {
      firstEnd = tick;
      same([s.frame, s.elapsed, s.stopped], [80, expected.endElapsed, true],
        `${label}: raw end80, not exporter framecount81`);
    }
    if (event.recovery) {
      recovery = tick;
      same(event, { recovery: true }, `${label}: recovery has no invented part or HIT writes`);
      same(animationClocks(s), [0, 0, 1, expected.dt, 16, 1, false, false],
        `${label}: recovery playAnim resets clocks without advancing again`);
    }
    same(s.recovery, tick >= expected.recoveryTick, `${label}: no premature recovery`);
    same(event.completed === true, tick === expected.completeTick,
      `${label}: completion event at tick${tick}`);
  }
  same(gates, expected.gateTicks, `${label}: gate check ticks`);
  same(observedCallbacks, [[1, 0], [1, 1], [2, 0], [1, 4], [1, 2], [1, 3]],
    `${label}: source callback order and once-only functional callback2`);
  same([firstEnd, recovery], [expected.endTick, expected.recoveryTick], `${label}: end and recovery ticks`);
  same([s.frame, s.elapsed, s.blendMode, s.ended, s.completed],
    [0, 15, expected.finalBlendMode, false, true], `${label}: terminal uses elapsed15`);
  const terminal = JSON.stringify(s);
  for (const dt of [0, .5, 1, 100]) {
    same(tickGRedCrashStream(s, dt), { completed: true }, `${label}: stable completion event`);
    same(JSON.stringify(s), terminal, `${label}: completed clock or callback state changed`);
  }
}

function checkInitialBlend(): void {
  same(createGRedCrashStream(), createGRedCrashStream(1), 'default delta is1');
  for (const dt of [0, .5, .75, 1]) {
    const s = createGRedCrashStream(dt);
    same(animationClocks(s), [0, 0, 1, dt, 3, 80, false, false], 'main playAnim initialization');
    same([s.waitIndex, s.waitCount, s.recovery, s.completed], [0, 0, false, false],
      'fresh stream has no inherited wait or terminal state');
    const initial = JSON.stringify(s);
    for (let i = 0; i < 10; i++) same(tickGRedCrashStream(s, 0), {}, 'zero delta before first gate');
    same(JSON.stringify(s), initial, 'zero delta changed fresh stream');
  }
  const s = createGRedCrashStream(1);
  for (let tick = 1; tick <= 2; tick++) {
    same(tickGRedCrashStream(s, 1), {}, 'mode1 holds without events');
    same([s.frame, s.elapsed, s.blendElapsed, s.blendMode], [0, tick, tick + 1, tick === 2 ? 0 : 1],
      `mode1 hold update${tick}`);
  }
  tickGRedCrashStream(s, 1);
  same([s.frame, s.elapsed], [1, 3], 'normal advance after blend completion');

  const fractional = createGRedCrashStream(.75);
  tickGRedCrashStream(fractional, 1);
  tickGRedCrashStream(fractional, 1);
  same([fractional.frame, fractional.blendElapsed, fractional.blendMode], [0, 2.75, 1],
    'fractional blend remains held');
  same(tickGRedCrashStream(fractional, .5), {}, 'blend completion cannot read future gate');
  same([fractional.frame, fractional.elapsed, fractional.blendMode], [.25, 2.5, 0],
    'blend completion adds only excess .25, not whole delta .5');
}

function checkWaitBoundaries(): void {
  const s = createGRedCrashStream(1);
  for (let tick = 1; tick <= 9; tick++) same(tickGRedCrashStream(s, 1), {}, 'gate7 fired early');
  same([s.frame, s.elapsed], [7, 9], 'gate7 is absolute frame7');
  same(tickGRedCrashStream(s, 0), GATE_EVENTS[0], 'ready wait executes before zero-delta advance');
  same([s.frame, s.elapsed, s.waitIndex], [7, 9, 1], 'zero-delta ready wait moved animation');
  for (let i = 0; i < 10; i++) same(tickGRedCrashStream(s, 0), {}, 'callback repeated while held');

  const hold = createGRedCrashStream(1);
  for (let tick = 1; tick <= 65; tick++) tickGRedCrashStream(hold, 1);
  same([hold.frame, hold.elapsed, hold.waitCount], [63, 65, 10], 'mode8 entry baseline');
  const clocks = animationClocks(hold);
  same(tickGRedCrashStream(hold, 0), {}, 'mode8 zero delta emits nothing');
  same(hold.waitCount, 10, 'mode8 zero delta preserves countdown');
  same(tickGRedCrashStream(hold, 9.5), {}, 'positive remaining countdown emits nothing');
  same(animationClocks(hold), clocks, 'positive mode8 freezes elapsed as well as frame');
  same(hold.waitCount, .5, 'countdown subtracts9.5');
  same(tickGRedCrashStream(hold, 1), {}, 'countdown underflow parses wait64 only');
  same([hold.frame, hold.elapsed, hold.waitCount, hold.waitIndex], [64, 66, 0, 6],
    'release clamps countdown0 and applies full normal delta, not excess .5');
  same(tickGRedCrashStream(hold, 0), GATE_EVENTS[6], 'gate64 writes wait until following call');
}

function checkStoppedOvershootAndRecovery(): void {
  const normal = createGRedCrashStream(1);
  tickGRedCrashStream(normal, 2); // Exact blend completion at frame0.
  same(tickGRedCrashStream(normal, 80.25), {}, 'normal crossing reads no newly satisfied wait');
  same([normal.frame, normal.stopped, normal.ended], [80.25, true, true],
    'normal mode0 crossing marks ended immediately without clamping to80');
  same(tickGRedCrashStream(normal, .5), GATE_EVENTS[0], 'normal overshoot leaves authored waits pending');
  same([normal.frame, normal.elapsed], [80.25, 82.75], 'normal STOP freezes overshoot while elapsed advances');

  const s = createGRedCrashStream(1);
  same(tickGRedCrashStream(s, 100), {}, 'oversized blend step reads no future waits');
  same([s.frame, s.elapsed, s.blendMode, s.stopped, s.ended], [98, 100, 0, true, false],
    'blend completion STOP precedes actor ended byte and preserves overshoot98');
  same(tickGRedCrashStream(s, 1), GATE_EVENTS[0], 'first pending block only');
  same([s.frame, s.elapsed, s.stopped, s.ended, s.recovery], [98, 101, true, true, false],
    'next normal update freezes STOP frame98 and marks ended');
  for (let i = 1; i <= 5; i++) {
    same(tickGRedCrashStream(s, 0), GATE_EVENTS[i], `pending block${i} is not skipped for early end`);
    same([s.frame, s.recovery], [98, false], 'pending source blocks precede recovery');
  }
  same(tickGRedCrashStream(s, 11), {}, 'oversized hold release parses only wait64');
  same([s.frame, s.elapsed, s.waitCount, s.waitIndex], [98, 112, 0, 6],
    'released STOP animation remains frozen but elapsed resumes');
  same(tickGRedCrashStream(s, 0), GATE_EVENTS[6], 'preserve signed contact and strengthFF');
  same(tickGRedCrashStream(s, 0), GATE_EVENTS[7], 'last callback is not skipped after end');
  same(tickGRedCrashStream(s, .5), { recovery: true }, 'recovery follows all main blocks and ended');
  same(animationClocks(s), [0, 0, 1, .5, 16, 1, false, false], 'recovery resets stopped overshoot');
  for (let tick = 1; tick <= 30; tick++) {
    same(tickGRedCrashStream(s, .5), {}, `recovery elapsed wait15 fired early at${tick}`);
    same([s.frame, s.elapsed, s.blendMode, s.ended], [0, tick * .5, 1, false],
      'recovery elapsed advances despite mode1 holding below raw end1');
  }
  same(tickGRedCrashStream(s, 0), { completed: true },
    'elapsed15 finishes even with active blend and animation not ended');
}

function checkIndependentClocks(): void {
  const first = createGRedCrashStream(1);
  for (let i = 0; i < 9; i++) tickGRedCrashStream(first, 1);
  const second = createGRedCrashStream(.5);
  tickGRedCrashStream(second, .5);
  same([first.frame, first.elapsed, first.waitIndex], [7, 9, 0], 'new stream cannot mutate old stream');
  same(tickGRedCrashStream(first, 0), GATE_EVENTS[0], 'old stream retains pending callback');
  same([second.frame, second.elapsed, second.waitIndex], [0, .5, 0], 'new stream has independent clocks');
}

export function runGredCrashStreamSelfTest(): void {
  checkInitialBlend();
  checkWaitBoundaries();
  checkStoppedOvershootAndRecovery();
  checkIndependentClocks();
  for (const trace of TRACES) checkTrace(trace);
  console.log('[gredCrashStream] PASS: authored gates/callbacks, mode8 hold, raw ends, STOP and recovery elapsed');
}
