/** Admitted G RED0/1/2, NEO G RED25/26/27 and G BLACK13/14/15 clocks.
 * Original streams803666d8/80366768/80366d38, playAnim487ec/4892c,
 * clocks49f10/4a00c/4a0e0 and wait interpreter4cd24. Numeric AOBJ ends
 * NEO ends27/35/40/1 and G BLACK ends35/40/70 are original motion values,
 * never exporter frame counts. BLACK packets live in gblackMeleeConfig.
 */
import { gredMeleeStreamConfig } from './gredMeleeConfig.js';
import { gblackMeleeStreamConfig } from './gblackMeleeConfig.js';
/** Historical API name retained. G BLACK slots are inert until a caller explicitly
 * admits that action and binds the functional groundwave event. */
export type NeoMeleeSlot = 0 | 1 | 2 | 13 | 14 | 15 | 25 | 26 | 27;
export interface NeoMeleeStream {
  slot: NeoMeleeSlot;
  frame: number;
  elapsed: number;
  blendMode: 0 | 1 | 2;
  blendElapsed: number;
  blendTotal: number;
  endFrame: number;
  ended: boolean;
  /** HSD AOBJ STOP can precede the actor end byte during blend completion. */
  stopped: boolean;
  waitIndex: number;
  recovery: boolean;
  completed: boolean;
}
export interface NeoMeleeStreamEvent {
  contact?: number;
  aux?: number;
  clearDash?: boolean;
  recovery?: boolean;
  completed?: boolean;
  gate?: number;
  flags6e8?: number;
  flags6e9?: number;
  control40?: boolean;
  clearContactFlags?: boolean;
  /** Source18d1d8 groundwave emission request. Never silently discard as FX. */
  groundWave?: boolean;
}
export function createNeoMeleeStream(slot: NeoMeleeSlot, dt: number): NeoMeleeStream {
  const red = gredMeleeStreamConfig(slot), scoped = red ?? gblackMeleeStreamConfig(slot);
  return { slot, frame: 0, elapsed: 0, blendMode: red?.blendMode ?? (slot === 26 ? 2 : 1),
    blendElapsed: dt, blendTotal: scoped ? scoped.blendByte + 1 : slot === 25 ? 6 : 5,
    endFrame: scoped?.endFrame ?? (slot === 25 ? 27 : slot === 26 ? 35 : 40),
    ended: false, stopped: false, waitIndex: 0, recovery: false, completed: false };
}
function advance(s: NeoMeleeStream, dt: number): void {
  s.elapsed = Math.fround(s.elapsed + dt);
  if (s.blendMode !== 0) {
    s.blendElapsed = Math.fround(s.blendElapsed + dt);
    if (s.blendElapsed >= s.blendTotal) {
      s.frame = Math.fround(s.frame + Math.fround(s.blendElapsed - s.blendTotal));
      if (s.frame >= s.endFrame) s.stopped = true;
      // b76c observes nonzero blend mode BEFORE this clear, so cannot set end.
      s.blendMode = 0;
    } else if (s.blendMode === 2) s.frame = Math.fround(s.frame + dt);
  } else {
    if (!s.stopped) s.frame = Math.fround(s.frame + dt);
    if (s.frame >= s.endFrame) { s.stopped = true; s.ended = true; }
  }
}
/** Tests the current wait before advancing animation, and parses at most one
 * following block. No-playAnim blocks advance once; a new animation starts at0.
 * Positive mode2 operands are absolute animation frames, not end-relative values. */
export function tickNeoMeleeStream(s: NeoMeleeStream, dt: number): NeoMeleeStreamEvent {
  if (s.completed) return { completed: true };
  const scoped = gredMeleeStreamConfig(s.slot) ?? gblackMeleeStreamConfig(s.slot);
  if (scoped) {
    const gate = scoped.gates[s.waitIndex];
    let event: NeoMeleeStreamEvent = {};
    if (gate && s.frame >= gate.frame) {
      s.waitIndex++;
      const { frame, ...writes } = gate;
      event = { gate: frame, ...writes };
    } else if (!gate && s.ended) {
      s.completed = true; return { completed: true };
    }
    advance(s, dt); return event;
  }
  if (s.recovery) {
    // mode1,+10 uses elapsed animation clock(+8), not animationFrame(+c).
    if (s.elapsed >= 10) { s.completed = true; return { completed: true }; }
    advance(s, dt); return {};
  }
  const waits = s.slot === 25 ? [5, 10] : s.slot === 26 ? [5, 13] : [2, 9, 19];
  const gate = waits[s.waitIndex];
  let event: NeoMeleeStreamEvent = {};
  if (gate !== undefined && s.frame >= gate) {
    s.waitIndex++;
    if (s.slot !== 27) event = gate === 5 ? { contact: 1, aux: 0, gate }
      : { contact: -1, aux: s.slot === 25 ? -1 : -2, clearDash: true, clearContactFlags: true, gate };
    else event = { contact: 0, aux: gate === 9 ? 1 : 0, clearDash: gate === 9, gate,
      flags6e8: 2, flags6e9: gate === 2 ? 1 : gate === 19 ? 2 : 0,
      control40: gate === 9 };
  } else if (gate === undefined && s.ended) {
    if (s.slot !== 27) { s.completed = true; return { completed: true }; }
    // mode0,-1 continues into playAnim g0s14: mode1, blend10, start0.
    s.recovery = true; s.frame = 0; s.elapsed = 0;
    s.blendMode = 1; s.blendElapsed = dt; s.blendTotal = 11;
    s.endFrame = 1; s.ended = false; s.stopped = false;
    return { contact: 0, aux: 0, recovery: true, flags6e8: 3, flags6e9: 2 };
  }
  advance(s, dt);
  return event;
}
