/** Independent opcode01/mode1/end-wait clock expectations. */
import { createGRedAirShotLowerStream, tickGRedAirShotLowerStream,
  type GRedAirShotLowerStream } from './gredAirShotLowerStream.js';

function check(value: unknown, label: string): void {
  if (!value) throw new Error(`[gredAirShotLowerStream] ${label}`);
}
function same(actual: unknown, expected: unknown, label: string): void {
  check(JSON.stringify(actual) === JSON.stringify(expected),
    `${label}: expected ${JSON.stringify(expected)}, got ${JSON.stringify(actual)}`);
}
function clocks(s: GRedAirShotLowerStream): unknown[] {
  return [s.frame, s.elapsed, s.blendMode, s.blendElapsed, s.blendTotal,
    s.endFrame, s.stopped, s.ended, s.completed];
}

function checkInitializationAndPartIsolation(): void {
  same(createGRedAirShotLowerStream(), createGRedAirShotLowerStream(1), 'default host rate/dt1');
  for (const dt of [0, .5, 1, 20]) {
    const { stream: s, events } = createGRedAirShotLowerStream(dt);
    same(clocks(s), [0, 0, 1, dt, 11, 1, false, false, false],
      'opcode01 seeds blend elapsed but NEVER receives same-call animation advance');
    same([s.authoredSlot, s.animationGroup, s.animationSlot], [13, 0, 14],
      'authored g0s13 differs from animation META0/14 and raw MOT0/24');
    same(events, [{ type: 'play', group: 0, slot: 14 },
      { type: 'movement', dashStrength: 0, faceGate: 0, controlBits: 0x40, stateMode71d: 0 }],
    'lower-mask op01/03 writes only; op02 is upper-mask-gated');
    check(!events.some(e => 'contact' in e || 'actionFlag6e8' in e || 'contactP0' in e),
      'lower cannot zero upper release P0 or action bytes');
  }
  const s = createGRedAirShotLowerStream(0).stream;
  const old = JSON.stringify(s);
  for (let tick = 0; tick < 100; tick++) same(tickGRedAirShotLowerStream(s, 0), [], 'zero dt no invented completion');
  same(JSON.stringify(s), old, 'zero dt freezes initial lower blend');
}

function checkExactTraces(): void {
  for (const [dt, clearCall, endedCall, completeCall, endElapsed] of
    [[1, 10, 11, 12, 11], [.5, 21, 23, 24, 11.5]] as const) {
    const s = createGRedAirShotLowerStream(dt).stream;
    for (let call = 1; call <= completeCall; call++) {
      const events = tickGRedAirShotLowerStream(s, dt);
      same(events, call === completeCall ? [{ type: 'completed' }] : [], 'only terminal ended wait emits completion');
      if (call < clearCall) same([s.frame, s.elapsed, s.blendMode, s.blendElapsed],
        [0, call * dt, 1, (call + 1) * dt], 'mode1 holds frame while blend clock advances');
      if (call === clearCall) same([s.frame, s.elapsed, s.blendMode, s.blendElapsed, s.ended],
        [0, call * dt, 0, 11, false], 'blend clear keeps frame0 and suppresses end marking');
      if (call === endedCall) same([s.frame, s.elapsed, s.stopped, s.ended, s.completed],
        [1, endElapsed, true, true, false], 'raw MOT end1 is observed before stream completion');
      if (call === completeCall) same([s.frame, s.elapsed, s.completed],
        [1, endElapsed, true], 'terminal completion performs no extra advance');
    }
    const final = JSON.stringify(s);
    for (const delta of [0, .5, 1, 100]) same(tickGRedAirShotLowerStream(s, delta), [], 'completion emits once');
    same(JSON.stringify(s), final, 'completed lower stream stays frozen');
  }
}

function checkOvershootAndFrozenEnd(): void {
  const s = createGRedAirShotLowerStream(4.25).stream;
  tickGRedAirShotLowerStream(s, 4.25);
  tickGRedAirShotLowerStream(s, 4.25);
  same(clocks(s), [1.75, 8.5, 0, 12.75, 11, 1, true, false, false],
    'mode1 overflow preserves first-crossing HSD overshoot but suppresses ended');
  same(tickGRedAirShotLowerStream(s, 0), [], 'zero dt normal update observes stopped animation end');
  same(clocks(s), [1.75, 8.5, 0, 12.75, 11, 1, true, true, false], 'stopped HSD frame never accumulates extra dt');
  same(tickGRedAirShotLowerStream(s, 0), [{ type: 'completed' }], 'next wait sees old ended even at dt0');

  const initial = createGRedAirShotLowerStream(20).stream;
  tickGRedAirShotLowerStream(initial, 0);
  same([initial.frame, initial.elapsed, initial.blendMode, initial.ended], [9, 0, 0, false],
    'large initial blend seed is applied on first update, not during opcode01 parsing');
  tickGRedAirShotLowerStream(initial, .5);
  same([initial.frame, initial.elapsed, initial.ended], [9, .5, true], 'first-crossing overshoot remains frozen');

  const fractional = createGRedAirShotLowerStream(.1).stream;
  tickGRedAirShotLowerStream(fractional, .1);
  same([fractional.elapsed, fractional.blendElapsed],
    [Math.fround(.1), Math.fround(Math.fround(.1) + .1)], 'each source clock store rounds to f32');
}

export function runGredAirShotLowerStreamSelfTest(): void {
  checkInitializationAndPartIsolation(); checkExactTraces(); checkOvershootAndFrozenEnd();
}
