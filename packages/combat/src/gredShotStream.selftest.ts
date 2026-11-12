/** Independent source-derived traces. Call0 is4beb8/4c050 initialization,
 * including0d's extra49e58 update. These clocks never allocate a projectile. */
import { createGRedShotStream, tickGRedShotStream, type GRedShotStream,
  type GRedShotStreamEvent } from './gredShotStream.js';

function check(value: unknown, label: string): void {
  if (!value) throw new Error(`[gredShotStream] ${label}`);
}
function same(actual: unknown, expected: unknown, label: string): void {
  check(JSON.stringify(actual) === JSON.stringify(expected),
    `${label}: expected ${JSON.stringify(expected)}, got ${JSON.stringify(actual)}`);
}
function clocks(s: GRedShotStream): unknown[] {
  return [s.frame, s.elapsed, s.blendMode, s.blendElapsed, s.blendTotal,
    s.endFrame, s.stopped, s.ended];
}
const contact = (value: -1 | 0 | 1): GRedShotStreamEvent => ({ type: 'contact',
  value, aux: 0, group: 1, actionFlag6e8: 1, actionFlag6e9: 0 });
const repeatEvents: GRedShotStreamEvent[] = [{ type: 'play', group: 2, slot: 6 },
  contact(1), { type: 'movement', dashStrength: 0, faceGate: 0 },
  { type: 'equipment', value: [4, 255] }];

function checkInitialization(): void {
  same(createGRedShotStream(0), createGRedShotStream(0, 1), 'default dt1');
  for (const dt of [0, .5, 1]) {
    const { stream: s, events } = createGRedShotStream(0, dt);
    same(events, [{ type: 'play', group: 2, slot: 0 }, contact(0),
      { type: 'movement', dashStrength: 0, faceGate: 0 }], 'source startup play and part writes');
    same(clocks(s), [0, dt, 6, 2 * dt, 6, 11, false, false],
      '0d parser advances once after seeding blendElapsed with dt');
    same([s.stage, s.wait, s.waitRemaining, s.completed], ['startup', 'frame3', 0, false],
      'startup installs absolute frame3 wait');
    const before = JSON.stringify(s);
    for (let i = 0; i < 30; i++) same(tickGRedShotStream(s, 0), [], 'frozen pre-gate emits no events');
    same(JSON.stringify(s), before, 'dt0 never fabricates elapsed/frame/blend advancement');
  }
}

const TRACES = [
  { dt: 1, blendEnd: 4, equipment: 8, end: 15, repeat: 16, terminal: 20, complete: 36,
    endElapsed: 16, terminalFrame: 5 },
  { dt: .5, blendEnd: 10, equipment: 17, end: 32, repeat: 33, terminal: 41, complete: 73,
    endElapsed: 16.5, terminalFrame: 4.5 },
] as const;

function checkTraces(): void {
  for (const trace of TRACES) {
    const { stream: s } = createGRedShotStream(0, trace.dt);
    let frozen: unknown[] = [];
    const observed: [number, GRedShotStreamEvent[]][] = [];
    for (let tick = 1; tick <= trace.complete; tick++) {
      const oldFrame = s.frame;
      const events = tickGRedShotStream(s, trace.dt);
      if (events.length) observed.push([tick, events]);
      if (tick === trace.blendEnd) same([s.frame, s.elapsed, s.blendMode, s.blendElapsed],
        [0, trace.dt * (tick + 1), 0, 6], 'mode6 holds frame until blend total6');
      if (tick === trace.equipment) {
        same(oldFrame, 3, 'frame3 gate reads old source frame');
        same(s.wait, 'ended', 'equipment parser installs nonterminal ended wait');
      }
      if (tick === trace.end) same([s.frame, s.elapsed, s.ended, s.completed, s.stage],
        [11, trace.endElapsed, true, false, 'startup'], 'raw AOBJEnd11 is not stream completion');
      if (tick === trace.repeat) same(clocks(s), [trace.dt, trace.dt, 0, 0, 0, 35, false, false],
        'ended wait falls through to contiguous s1 and advances new unblended clock once');
      if (tick === trace.terminal) {
        same(oldFrame, 4, 'frame4 gate reads old source frame');
        same([s.stage, s.wait, s.waitRemaining, s.completed], ['terminal', 'terminal', 16, false],
          'mode9 entry stores16 without subtracting yet');
        same([s.frame, s.elapsed], [trace.terminalFrame, trace.terminalFrame],
          'mode9 entry receives one final parser advance');
        frozen = clocks(s);
      }
      if (tick > trace.terminal) {
        same(clocks(s), frozen, 'mode9 countdown and completion freeze every animation clock');
        same(s.waitRemaining, Math.max(0, 16 - trace.dt * (tick - trace.terminal)),
          'mode9 subtracts before testing');
        same(s.completed, tick === trace.complete, 'terminal completion boundary');
      }
    }
    same(observed, [[trace.equipment, [{ type: 'equipment', value: [4, 255] }]],
      [trace.repeat, repeatEvents], [trace.terminal, [contact(-1)]],
      [trace.complete, [{ type: 'completed' }]]], `dt${trace.dt} exact event trace; no callbacks/HIT/fire`);
    const final = JSON.stringify(s);
    for (const dt of [0, .5, 1, 100]) {
      same(tickGRedShotStream(s, dt), [], 'completion is a once-only event');
      same(JSON.stringify(s), final, 'completed stream remains unchanged');
    }
  }
}

function checkRepeatsAndZeroDt(): void {
  const late = createGRedShotStream(1, 1);
  same(late.events, repeatEvents, 'default late repeat source writes');
  same(clocks(late.stream), [1, 1, 0, 0, 0, 35, false, false], 'late repeat starts0/blend0 then advances');
  same(tickGRedShotStream(late.stream, 0), [], 'phase1 dt0 freezes late-repeat positive contact');
  same([late.stream.frame, late.stream.elapsed], [1, 1], 'late-repeat clock does not advance on frozen aim tick');

  const early = createGRedShotStream(1, 1, { startFrame: 4, blend: 1 });
  same(early.events, repeatEvents, 'early repeat has identical source writes');
  same(clocks(early.stream), [4, 1, 0, 2, 2, 35, false, false],
    'start4/blend1 completes mode6 on the same parser call');
  same(tickGRedShotStream(early.stream, 0), [contact(-1)],
    'oldframe4 still permits gate/control work with dt0');
  same([early.stream.stage, early.stream.frame, early.stream.elapsed, early.stream.waitRemaining],
    ['terminal', 4, 1, 16], 'gate4 dt0 does not fabricate time or consume countdown');
  for (let i = 0; i < 10; i++) same(tickGRedShotStream(early.stream, 0), [], 'zero terminal delta freezes countdown');
  same(early.stream.waitRemaining, 16, 'zero terminal delta does not finish action');

  const fractional = createGRedShotStream(1, .5, { startFrame: 4, blend: 1 }).stream;
  same(clocks(fractional), [4, .5, 6, 1, 2, 35, false, false], 'fractional early repeat retains live mode6');
  same(tickGRedShotStream(fractional, 0), [contact(-1)], 'frame gate does not require blend completion');
  const frozen = clocks(fractional);
  for (let tick = 1; tick <= 32; tick++) tickGRedShotStream(fractional, .5);
  same(clocks(fractional), frozen, 'mode9 can freeze the incomplete mode6 until terminal completion');
  same([fractional.completed, fractional.waitRemaining], [true, 0], 'fractional terminal finishes after32 countdown ticks');
}

function checkWaitAndEndBoundaries(): void {
  const s = createGRedShotStream(0, 0).stream;
  s.frame = 11; s.ended = true; s.stopped = true; s.blendMode = 0;
  same(tickGRedShotStream(s, 0), [{ type: 'equipment', value: [4, 255] }],
    'one satisfied frame3 wait cannot also consume following ended wait');
  same(s.stage, 'startup', 'newly installed ended wait waits until next call');
  same(tickGRedShotStream(s, 0), repeatEvents, 'next call follows ended into s1');
  same([s.stage, s.frame, s.elapsed, s.completed], ['repeat', 0, 0, false],
    'dt0 fallthrough resets but does not advance new clocks');

  // Artificially close to the clip end to isolate4a60c/b76c mode-ordering.
  const end = createGRedShotStream(0, 0).stream;
  end.wait = 'ended'; end.frame = 11; end.blendElapsed = 5; end.blendTotal = 6;
  same(tickGRedShotStream(end, 1), [], 'blend completion does not trigger ended wait');
  same([end.blendMode, end.stopped, end.ended], [0, true, false], 'end marking suppressed while old mode6 is live');
  same(tickGRedShotStream(end, 0), [], 'normal zero-dt clock can observe AOBJ ended without time advancement');
  same(end.ended, true, 'end marker set on following normal mode0 update');
  same(tickGRedShotStream(end, 0), repeatEvents, 'ended marker used only on next interpreter call');
}

function checkAirAliasesAndProfiles(): void {
  for (const dt of [0, .5, 1, 2.75]) {
    for (const slot of [0, 1] as const) {
      const ground = createGRedShotStream(slot, dt);
      const air = createGRedShotStream(slot === 0 ? 4 : 5, dt);
      const bank6 = createGRedShotStream(slot === 0 ? 6 : 7, dt);
      same(air.events, ground.events, 'g2s4/5 exact aliases of g2s0/1');
      same([air.stream.authoredSlot, air.stream.profile, air.stream.animationSlot],
        [slot + 4, 4, slot === 0 ? 0 : 6], 'air alias retains authored identity distinct from META center');
      same([bank6.stream.authoredSlot, bank6.stream.profile, bank6.stream.animationSlot, bank6.stream.endFrame],
        [slot + 6, 6, slot === 0 ? 3 : 9, slot === 0 ? 11 : 15], 'g2s6/7 original center and raw end metadata');
      same(bank6.events, ground.events.map(e => e.type === 'play' ?
        { ...e, slot: e.slot === 0 ? 3 : 9 } : e), 'bank6 changes only center play, not state/event writes');
      for (let call = 0; call < 90; call++) {
        const groundEvents = tickGRedShotStream(ground.stream, dt);
        same(tickGRedShotStream(air.stream, dt), groundEvents, 'alias exact event trace including startup fallthrough');
        same(clocks(air.stream), clocks(ground.stream), 'alias exact blend/frame/end trace');
        same([air.stream.stage, air.stream.waitRemaining, air.stream.completed],
          [ground.stream.stage, ground.stream.waitRemaining, ground.stream.completed], 'alias terminal countdown trace');
        tickGRedShotStream(bank6.stream, dt);
      }
      same(air.stream.profile, 4, 'fallthrough preserves authored alias profile');
      if (dt > 0) {
        same([air.stream.authoredSlot, bank6.stream.authoredSlot], [5, 7], 'fallthrough uses matching adjacent authored repeat');
        same([air.stream.completed, bank6.stream.completed], [true, true], 'both air profiles complete source mode9 countdown');
      }
    }
  }
  for (const slot of [5, 7] as const) {
    const s = createGRedShotStream(slot, .5, { startFrame: 4, blend: 1 }).stream;
    same([s.frame, s.blendMode, s.blendElapsed, s.endFrame], [4, 6, 1, slot === 5 ? 35 : 15],
      'air early repeat uses source override and profile-specific MOT end');
    same(tickGRedShotStream(s, 0), [contact(-1)], 'air early repeat gate4 can run with frozen dt');
    const old = clocks(s);
    for (let call = 0; call < 32; call++) tickGRedShotStream(s, .5);
    same(clocks(s), old, 'air terminal wait freezes incomplete mode6 too');
    same(s.completed, true, 'air early-repeat countdown completes exactly');
  }
}

export function runGredShotStreamSelfTest(): void {
  checkInitialization(); checkTraces(); checkRepeatsAndZeroDt(); checkWaitAndEndBoundaries();
  checkAirAliasesAndProfiles();
}
