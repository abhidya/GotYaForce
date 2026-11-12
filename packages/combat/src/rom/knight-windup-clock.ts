/** Narrow reconstruction of g4s2 at 0x80300c6c, NOT a generic decoded wait VM.
 * See docs/knight-authored-windup.md for the verified operands and rate limit. */
export interface KnightWindupClock {
  localFrame: number;
  blendElapsed: number;
  blending: boolean;
}
export function createKnightWindupClock(advance: number): KnightWindupClock {
  return { localFrame: 0, blendElapsed: advance, blending: true };
}
/** Source order: test terminal flags 3 against local+c, then advance animation.
 * The caller retires the stream on true: bytes after the terminal wait never run. */
export function tickKnightWindupClock(clock: KnightWindupClock, advance: number): boolean {
  if (clock.localFrame >= 30) return true;
  if (clock.blending) {
    clock.blendElapsed += advance;
    if (clock.blendElapsed >= 5) {
      clock.localFrame += clock.blendElapsed - 5;
      clock.blending = false;
    }
  } else {
    clock.localFrame += advance;
  }
  return false;
}
