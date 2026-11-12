import { createArrowStreamClock, tickArrowStream } from './arrowStream.js';

function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[arrowStream.selftest] ${message}`);
}

export function runArrowStreamSelfTest(): void {
  for (const slot of [0, 1] as const) {
    const clock = createArrowStreamClock(slot);
    const gates: Array<[number, number, number]> = [];
    let completed = 0;
    for (let tick = 1; tick <= 49; tick++) {
      const event = tickArrowStream(clock, 1);
      if (event.gate !== undefined) gates.push([tick, event.gate, event.contact!]);
      if (event.completed) completed = tick;
      if (tick < 49) assert(!event.completed, 'terminal wait completed before source AOBJ end');
    }
    assert(JSON.stringify(gates) === JSON.stringify([[13, 9, 0], [21, 17, 0], [25, 21, 1], [38, 34, -1]]),
      `slot${slot} wait-before-advance order or parser advance differs`);
    assert(completed === 49 && clock.frame === 45, `slot${slot} incorrect source end`);
  }
  const frozen = createArrowStreamClock(0);
  for (let i = 0; i < 100; i++) assert(Object.keys(tickArrowStream(frozen, 0)).length === 0, 'zero advance emitted event');
  assert(frozen.frame === 0 && frozen.blendElapsed === 1, 'zero advance moved clock');
  const first = createArrowStreamClock(1);
  for (let i = 0; i < 24; i++) tickArrowStream(first, 1);
  const replacement = createArrowStreamClock(1);
  assert(!tickArrowStream(replacement, 1).contact, 'replacement inherited fire gate');
  assert(tickArrowStream(first, 1).contact === 1, 'replacement mutated independent clock');
}
