/** Lower-part mask2 clock for G RED-family fallback v4's authored g0s13.
 * Raw stream: 01000e010a000000 02ff000000000000 0300000000000040 0001ffff.
 * META0/14 -> MOT0/24, raw end1. Opcode01 (48648/4a00c mode1) suppresses
 * parser4c050's same-call animation update. Retained rate1 is the host seam.
 * Opcode02 is mask1-gated, so this mask2-only stream NEVER writes upper P0,
 * upper completion, action flags or equipment. No controller is imported.
 * Original opcode02 handler8004c424 gates writes on mask1; opcode03 handler
 * 8004c488 uses mask2 and (old & 0xfffff00f) | (operand & 0xff0), confirmed
 * by the retained research/decomp/stream-control-reachability-2026-11-12.md audit.
 */
export interface GRedAirShotLowerStream {
  authoredSlot: 13;
  animationGroup: 0;
  animationSlot: 14;
  frame: number;
  elapsed: number;
  blendMode: 0 | 1;
  blendElapsed: number;
  blendTotal: 11;
  endFrame: 1;
  stopped: boolean;
  ended: boolean;
  completed: boolean;
}

export type GRedAirShotLowerStreamEvent =
  | { type: 'play'; group: 0; slot: 14 }
  /** Op03 replaces posture bits4..11: (controlWord & ~0xff0) | controlBits.
   * Op01 also clears71d for mask2. These writes belong to the lower part. */
  | { type: 'movement'; dashStrength: 0; faceGate: 0; controlBits: 0x40; stateMode71d: 0 }
  | { type: 'completed' };

export interface GRedAirShotLowerStreamStart {
  stream: GRedAirShotLowerStream;
  events: GRedAirShotLowerStreamEvent[];
}

const f32 = Math.fround;

export function createGRedAirShotLowerStream(dt = 1): GRedAirShotLowerStreamStart {
  return {
    stream: { authoredSlot: 13, animationGroup: 0, animationSlot: 14,
      frame: 0, elapsed: 0, blendMode: 1, blendElapsed: f32(dt), blendTotal: 11,
      endFrame: 1, stopped: false, ended: false, completed: false },
    events: [{ type: 'play', group: 0, slot: 14 },
      { type: 'movement', dashStrength: 0, faceGate: 0, controlBits: 0x40, stateMode71d: 0 }],
  };
}

export function tickGRedAirShotLowerStream(s: GRedAirShotLowerStream,
  dt: number): GRedAirShotLowerStreamEvent[] {
  if (s.completed) return [];
  // Terminal ended wait reads OLD end state; the completion call never advances.
  if (s.ended) {
    s.completed = true;
    return [{ type: 'completed' }];
  }
  s.elapsed = f32(s.elapsed + dt);
  if (s.blendMode === 1) {
    s.blendElapsed = f32(s.blendElapsed + dt);
    if (s.blendElapsed >= s.blendTotal) {
      s.frame = f32(s.frame + f32(s.blendElapsed - s.blendTotal));
      if (s.frame >= s.endFrame) s.stopped = true;
      // 4a00c runs4a830 before clearing mode1: end marking is suppressed.
      s.blendMode = 0;
    }
  } else {
    if (!s.stopped) s.frame = f32(s.frame + dt);
    if (s.frame >= s.endFrame) { s.stopped = true; s.ended = true; }
  }
  return [];
}
