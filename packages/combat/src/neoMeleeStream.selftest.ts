/** Independent clock checks, not gameplay or console-output equivalence tests.
 * Source: 487ec/4892c initialize blendElapsed=dt and blendTotal=duration+1;
 * 4a00c/4a0e0 hold/advance during blend, adding only excess on completion;
 * 4b76c observes the old blend mode; 4cd24 tests waits before advancing.
 * Stream25/26/27 operands and raw AOBJ ends are documented in
 * research/decomp/neo-melee-chain-2026-11-12.md. The gate ticks below are
 * hand-derived from those operands, not captured from this implementation.
 * Fractional/large deltas exercise the isolated clock only. Live admission is
 * currently bounded to dt1 and existing playback rate1 (rate byte0 preserves it).
 */
import {
  createNeoMeleeStream,
  tickNeoMeleeStream,
  type NeoMeleeSlot,
  type NeoMeleeStream,
} from './neoMeleeStream.js';

function check(value: unknown, label: string): void {
  if (!value) throw new Error(`[neoMeleeStream] ${label}`);
}

function same(actual: unknown, expected: unknown, label: string): void {
  check(JSON.stringify(actual) === JSON.stringify(expected),
    `${label}: expected ${JSON.stringify(expected)}, got ${JSON.stringify(actual)}`);
}

// [tick, absolute frame operand, contact, signed aux, clearDash]
type Gate = readonly [number, number, number, number, boolean];
interface TraceExpectation {
  slot: NeoMeleeSlot;
  dt: number;
  gates: readonly Gate[];
  endTick: number;
  endFrame: number;
  recoveryTick?: number;
  completeTick: number;
  finalFrame: number;
  finalBlendMode: number;
}

const TRACES: readonly TraceExpectation[] = [
  { slot: 25, dt: 1, gates: [[11, 5, 1, 0, false], [16, 10, -1, -1, true]],
    endTick: 32, endFrame: 27, completeTick: 33, finalFrame: 27, finalBlendMode: 0 },
  { slot: 26, dt: 1, gates: [[7, 5, 1, 0, false], [15, 13, -1, -2, true]],
    endTick: 36, endFrame: 35, completeTick: 37, finalFrame: 35, finalBlendMode: 0 },
  { slot: 27, dt: 1, gates: [[7, 2, 0, 0, false], [14, 9, 0, 1, true], [24, 19, 0, 0, false]],
    endTick: 44, endFrame: 40, recoveryTick: 45, completeTick: 56, finalFrame: 0, finalBlendMode: 0 },
  { slot: 25, dt: .5, gates: [[22, 5, 1, 0, false], [32, 10, -1, -1, true]],
    endTick: 65, endFrame: 27, completeTick: 66, finalFrame: 27, finalBlendMode: 0 },
  { slot: 26, dt: .5, gates: [[12, 5, 1, 0, false], [28, 13, -1, -2, true]],
    endTick: 71, endFrame: 35, completeTick: 72, finalFrame: 35, finalBlendMode: 0 },
  { slot: 27, dt: .5, gates: [[14, 2, 0, 0, false], [28, 9, 0, 1, true], [48, 19, 0, 0, false]],
    endTick: 89, endFrame: 40, recoveryTick: 90, completeTick: 111, finalFrame: 0, finalBlendMode: 1 },
  { slot: 25, dt: .75, gates: [[15, 5, 1, 0, false], [22, 10, -1, -1, true]],
    endTick: 43, endFrame: 27, completeTick: 44, finalFrame: 27, finalBlendMode: 0 },
  { slot: 26, dt: .75, gates: [[9, 5, 1, 0, false], [19, 13, -1, -2, true]],
    endTick: 48, endFrame: 35.5, completeTick: 49, finalFrame: 35.5, finalBlendMode: 0 },
  { slot: 27, dt: .75, gates: [[10, 2, 0, 0, false], [19, 9, 0, 1, true], [32, 19, 0, 0, false]],
    endTick: 59, endFrame: 40, recoveryTick: 60, completeTick: 75, finalFrame: .25, finalBlendMode: 0 },
];

function checkTrace(expected: TraceExpectation): void {
  const clock = createNeoMeleeStream(expected.slot, expected.dt);
  const gates: Gate[] = [];
  const label = `slot${expected.slot} dt${expected.dt}`;
  let firstEnd = 0;
  let recovery = 0;
  for (let tick = 1; tick <= expected.completeTick; tick++) {
    const frameBefore = clock.frame;
    const event = tickNeoMeleeStream(clock, expected.dt);
    if (event.gate !== undefined) {
      check(frameBefore >= event.gate, `${label}: wait read the newly advanced frame`);
      gates.push([tick, event.gate, event.contact!, event.aux!, event.clearDash === true]);
      if (expected.slot !== 27) check(event.clearContactFlags === (event.gate === 5 ? undefined : true), `${label}: clear709 only at rearm gate`);
      if (expected.slot === 27) {
        same([event.flags6e8, event.flags6e9, event.control40],
          [2, event.gate === 2 ? 1 : event.gate === 19 ? 2 : 0, event.gate === 9],
          `${label}: source flag writes at gate${event.gate}`);
      }
    }
    if (clock.ended && firstEnd === 0) {
      firstEnd = tick;
      same(clock.frame, expected.endFrame, `${label}: raw end or first-crossing overshoot`);
    }
    if (event.recovery) {
      recovery = tick;
      same([event.contact, event.aux, event.flags6e8, event.flags6e9], [0, 0, 3, 2],
        `${label}: recovery part and flag writes`);
      same([clock.frame, clock.elapsed, clock.blendMode, clock.blendElapsed,
        clock.blendTotal, clock.endFrame, clock.ended, clock.stopped],
      [0, 0, 1, expected.dt, 11, 1, false, false], `${label}: g0s14 resets both clocks`);
    }
    same(event.completed === true, tick === expected.completeTick,
      `${label}: terminal event at tick${tick}`);
  }
  same(gates, expected.gates, `${label}: source gate/write order`);
  same(firstEnd, expected.endTick, `${label}: original motion end tick`);
  same(recovery, expected.recoveryTick ?? 0, `${label}: recovery starts on following wait check`);
  same([clock.frame, clock.blendMode, clock.completed],
    [expected.finalFrame, expected.finalBlendMode, true], `${label}: terminal clock`);
  const terminal = JSON.stringify(clock);
  for (const dt of [0, .5, 1, 4]) {
    same(tickNeoMeleeStream(clock, dt), { completed: true }, `${label}: repeat completion is idempotent`);
    same(JSON.stringify(clock), terminal, `${label}: completed stream advanced`);
  }
}

function checkInitialBlends(): void {
  for (const slot of [25, 26, 27] as const) {
    for (const dt of [0, .5, .75, 1]) {
      const clock = createNeoMeleeStream(slot, dt);
      same([clock.frame, clock.elapsed, clock.blendMode, clock.blendElapsed,
        clock.blendTotal, clock.endFrame, clock.ended, clock.stopped, clock.waitIndex, clock.recovery, clock.completed],
      [0, 0, slot === 26 ? 2 : 1, dt, slot === 25 ? 6 : 5,
        slot === 25 ? 27 : slot === 26 ? 35 : 40, false, false, 0, false, false],
      `slot${slot} dt${dt}: playAnim initialization and raw end`);
      const before = JSON.stringify(clock);
      for (let i = 0; i < 20; i++) same(tickNeoMeleeStream(clock, 0), {}, 'zero delta before first gate');
      same(JSON.stringify(clock), before, 'zero delta changed fresh clock');
    }
  }
  for (const slot of [25, 27] as const) {
    const clock = createNeoMeleeStream(slot, 1);
    const blendTicks = slot === 25 ? 5 : 4;
    for (let tick = 1; tick <= blendTicks; tick++) {
      same(tickNeoMeleeStream(clock, 1), {}, `mode1 slot${slot}: unexpected blend event`);
      same([clock.frame, clock.elapsed, clock.blendElapsed, clock.blendMode],
        [0, tick, tick + 1, tick === blendTicks ? 0 : 1], `mode1 slot${slot}: hold tick${tick}`);
    }
    tickNeoMeleeStream(clock, 1);
    same(clock.frame, 1, `mode1 slot${slot}: normal advance after blend`);
  }
  const mode2 = createNeoMeleeStream(26, 1);
  for (const frame of [1, 2, 3, 3, 4]) {
    same(tickNeoMeleeStream(mode2, 1), {}, 'mode2 emitted early gate');
    same(mode2.frame, frame, 'mode2 advances during blend but completion adds excess only');
  }
}

function checkFractionalBlendOverflow(): void {
  for (const slot of [25, 26, 27] as const) {
    const clock = createNeoMeleeStream(slot, .75);
    const wholeTicks = slot === 25 ? 5 : 4;
    for (let i = 0; i < wholeTicks; i++) tickNeoMeleeStream(clock, 1);
    same([clock.frame, clock.blendMode, clock.blendElapsed],
      [slot === 26 ? 4 : 0, slot === 26 ? 2 : 1, wholeTicks + .75],
      `slot${slot}: pre-overflow blend state`);
    same(tickNeoMeleeStream(clock, .5), {}, `slot${slot}: completion cannot consume a future gate`);
    same([clock.frame, clock.elapsed, clock.blendMode, clock.ended],
      [slot === 26 ? 4.25 : .25, wholeTicks + .5, 0, false],
      `slot${slot}: .25 blend excess, not the full .5 step`);
  }
}

function checkWaitBoundaries(): void {
  const clock = createNeoMeleeStream(25, 1);
  for (let tick = 1; tick <= 10; tick++) same(tickNeoMeleeStream(clock, 1), {}, 'frame5 wait fired early');
  same(clock.frame, 5, 'first gate is an absolute frame, not end-relative');
  same(tickNeoMeleeStream(clock, 0), { contact: 1, aux: 0, gate: 5 },
    'ready wait executes at zero dt, before any advance');
  same([clock.frame, clock.elapsed, clock.waitIndex], [5, 10, 1], 'ready zero-delta wait moved clock');
  for (let i = 0; i < 20; i++) same(tickNeoMeleeStream(clock, 0), {}, 'gate repeated while held');

  // Both waits are already ready after this oversized step. The source parses
  // one following block per call, rather than draining every ready wait.
  const overshoot = createNeoMeleeStream(26, 1);
  tickNeoMeleeStream(overshoot, 4); // Exact blend completion, frame remains zero.
  same(tickNeoMeleeStream(overshoot, 35.5), {}, 'overshoot must not consume waits after advancing');
  same([overshoot.frame, overshoot.ended, overshoot.waitIndex], [35.5, true, 0],
    'nonloop first crossing preserves overshoot instead of clamping35');
  same(tickNeoMeleeStream(overshoot, .5), { contact: 1, aux: 0, gate: 5 }, 'first pending wait only');
  same([overshoot.frame, overshoot.elapsed, overshoot.waitIndex], [35.5, 40, 1],
    'ended animation freezes while elapsed clock continues');
  same(tickNeoMeleeStream(overshoot, .5), { contact: -1, aux: -2, clearDash: true, clearContactFlags: true, gate: 13 },
    'second pending wait retains signed FE aux');
  same([overshoot.frame, overshoot.elapsed, overshoot.waitIndex], [35.5, 40.5, 2],
    'held end must not restart or loop');
  same(tickNeoMeleeStream(overshoot, 0), { completed: true }, 'terminal wait completes without another advance');
}

function checkBlendCompletionEndOrdering(): void {
  const clock = createNeoMeleeStream(25, 1);
  same(tickNeoMeleeStream(clock, 40), {}, 'large blend-completion step cannot read future waits');
  same([clock.frame, clock.blendMode, clock.ended, clock.stopped], [35, 0, false, true],
    'b76c sees old nonzero blend mode even after an excess step crosses end27');
  same(tickNeoMeleeStream(clock, 1), { contact: 1, aux: 0, gate: 5 }, 'first wait after blend completion');
  same([clock.frame, clock.ended], [35, true],
    'HSD STOP freezes35 on the next positive-delta call while b76c recognizes end');
  same(tickNeoMeleeStream(clock, 0), { contact: -1, aux: -1, clearDash: true, clearContactFlags: true, gate: 10 },
    'second wait retains signed FF aux before terminal completion');
  same(tickNeoMeleeStream(clock, 0), { completed: true }, 'end wait follows both authored blocks');
}

function checkRecoveryElapsedClock(): void {
  const clock = createNeoMeleeStream(27, 1);
  for (let tick = 1; tick <= 44; tick++) tickNeoMeleeStream(clock, 1);
  same([clock.frame, clock.elapsed, clock.ended, clock.recovery], [40, 44, true, false],
    'finisher mode0/-1 waits for raw end40');
  same(tickNeoMeleeStream(clock, .5), { contact: 0, aux: 0, recovery: true, flags6e8: 3, flags6e9: 2 },
    'recovery playAnim block');
  same([clock.frame, clock.elapsed, clock.blendElapsed, clock.blendTotal, clock.endFrame],
    [0, 0, .5, 11, 1], 'recovery starts at0 and resets elapsed instead of inheriting44');
  for (let tick = 1; tick <= 20; tick++) {
    same(tickNeoMeleeStream(clock, .5), {}, `recovery wait10 fired before check${tick + 1}`);
    same([clock.frame, clock.elapsed, clock.blendMode, clock.ended], [0, tick * .5, 1, false],
      'recovery elapsed advances while animation is held below its raw end1');
  }
  same(tickNeoMeleeStream(clock, 0), { completed: true },
    'terminal mode1/+10 uses elapsed, not frame, blend completion, or ended');
}

function checkIndependentClocks(): void {
  const first = createNeoMeleeStream(25, 1);
  for (let tick = 0; tick < 10; tick++) tickNeoMeleeStream(first, 1);
  const replacement: NeoMeleeStream = createNeoMeleeStream(26, .5);
  tickNeoMeleeStream(replacement, .5);
  same([first.slot, first.frame, first.elapsed, first.waitIndex], [25, 5, 10, 0],
    'replacement mutated earlier stream');
  same(tickNeoMeleeStream(first, 0), { contact: 1, aux: 0, gate: 5 }, 'earlier stream retains pending wait');
  same([replacement.slot, replacement.frame, replacement.elapsed, replacement.waitIndex], [26, .5, .5, 0],
    'new playAnim inherited frame, elapsed, or wait index');
}

export function runNeoMeleeStreamSelfTest(): void {
  checkInitialBlends();
  checkFractionalBlendOverflow();
  checkWaitBoundaries();
  checkBlendCompletionEndOrdering();
  checkRecoveryElapsedClock();
  checkIndependentClocks();
  for (const trace of TRACES) checkTrace(trace);
  console.log('[neoMeleeStream] PASS: source gates, blend clocks, raw ends, overshoot and recovery');
}
