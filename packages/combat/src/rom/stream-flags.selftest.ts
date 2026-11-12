import { createRomActor, type RomActor } from './actor.js';
import { startStream, tickStream } from './stream-vm.js';

function assert(ok: boolean, message: string): void {
  if (!ok) throw new Error(`[stream-flags] ${message}`);
}
function bank(...ops: number[]): Uint8Array {
  // Group0 at2, slot0 at4; terminal wait follows the authored operations.
  return Uint8Array.from([0, 2, 0, 2, ...ops, 0, 0, 255, 255]);
}
export function runStreamFlagsSelfTest(): void {
  let cases = 0;
  for (const initial of [0, 1, 4, 31, 128, 165, 254, 255]) {
    for (const mask of [0, 1, 31, 128, 255]) {
      for (const mode of [0, 1, 2, 255]) {
        const a = createRomActor();
        a.familyStreamBank = bank(0x0b, mode, mask, 0);
        startStream(a, 2, 0, 0);
        a.contactFlags = initial;
        tickStream(a, 2);
        const expected = mode === 0 ? initial & (255 ^ mask) : initial | mask;
        assert(a.contactFlags === expected, `mode${mode}/mask${mask}/initial${initial}`);
        assert(a.parts[1]!.streamPtr === -1, 'opcode advances four bytes to terminal');
        cases++;
      }
    }
  }
  for (let part = 0; part < 4; part++) {
    const a = createRomActor();
    a.familyStreamBank = bank(0x0b, 1, 1, 0);
    startStream(a, 1 << part, 0, 0);
    a.contactFlags = 0x80;
    tickStream(a, 1 << part);
    assert(a.contactFlags === (part === 1 ? 0x81 : 0x80), `part${part} gate`);
    assert(a.parts[part]!.streamPtr === -1, 'unselected opcode still advances');
  }
  for (const available of [false, true]) {
    for (const requested of [0, 1, 2, 15]) {
      for (const permitted of [0, 1, 2, 15]) {
        const a = createRomActor();
        a.familyStreamBank = available ? bank() : null;
        a.weaponPartMask = permitted;
        a.contactFlags = 0xa5;
        startStream(a, requested, 0, 0);
        assert(a.contactFlags === ((requested & permitted & 2) !== 0 ? 0 : 0xa5),
          `effective mask reset requested${requested}/permitted${permitted}/bank${available}`);
      }
    }
  }
  const invalid = createRomActor();
  invalid.familyStreamBank = Uint8Array.from([0x7f, 0xff]);
  invalid.contactFlags = 255;
  startStream(invalid, 2, 0, 0);
  assert(invalid.contactFlags === 0, 'reset precedes failed stream resolution');
  const scheduled = createRomActor() as RomActor & { onStartStream?: () => boolean };
  scheduled.contactFlags = 255;
  scheduled.onStartStream = () => {
    assert(scheduled.contactFlags === 0, 'host startup observes source reset');
    scheduled.contactFlags = 4;
    return true;
  };
  startStream(scheduled, 2, 0, 0);
  assert(scheduled.contactFlags === 4, 'host startup write survives absent-bank scheduling');
  const ordered = createRomActor();
  ordered.familyStreamBank = bank(0x0b, 1, 31, 0, 0x0b, 0, 3, 0, 0x0b, 255, 128, 0);
  startStream(ordered, 15, 0, 0);
  tickStream(ordered, 15);
  assert(ordered.contactFlags === 156, 'multipart walker preserves ordered set/clear writes');
  console.log(`[stream-flags] PASS: ${cases} byte operations, part gates, effective-mask resets and host ordering`);
}
