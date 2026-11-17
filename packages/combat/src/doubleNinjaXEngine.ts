/** Double Ninja pl0003 action3, 71750/71858/71938 (chunk_0009.c:5361–5497).
 * Inert source control flow: this arms a displaced double, NOT an actor dash
 * or projectile. Stream clocks, ground probing, matrix X basis and cosine are
 * explicit hooks. No input, renderer, HIT or Battle policy is implied here.
 */
export interface DoubleNinjaVec3 { x: number; y: number; z: number }
export interface DoubleNinjaXEngineState {
  phase: number; dt: number;
  pos: DoubleNinjaVec3; savedOwnPos5e8: DoubleNinjaVec3; motion: DoubleNinjaVec3;
  arm7c8: number; offset7b0: DoubleNinjaVec3; matrixX8d4: DoubleNinjaVec3;
  timer560: number; timer558: number; magnitude55c: number;
  hSpeed: number; yVel: number; hDecel: number; gravityCoeff: number;
  poseAccum80: number; poseAccum7e: number; poseAccum7c: number;
  controlWord: number; streamEnded1cee: number; actionFlag73f: number;
}
export interface DoubleNinjaXEngineHooks {
  ground679d0(state: DoubleNinjaXEngineState): void;
  startStream(state: DoubleNinjaXEngineState, mask: 15, group: 4, slot: 2 | 3,
    startFrameOverride: -1, blendOverride: -1, modeOverride: -1): void;
  tickStream(state: DoubleNinjaXEngineState, mask: 15): void;
  releaseStream4cff4(state: DoubleNinjaXEngineState, mask: 15): void;
  feedback061a8(state: DoubleNinjaXEngineState, code: 5): void;
  /** Source helper45238 takes a signed-short angle, after truncation toward0. */
  cosine45238(angle: number): number;
  groundIdle6a474(state: DoubleNinjaXEngineState): void;
  airReturn6a5a4(state: DoubleNinjaXEngineState): void;
}
export type DoubleNinjaXEngineOutcome = {type:'continue'} |
  {type:'cleanup';exit:'ground'|'air'} | {type:'unsupported';phase:number};
const f = Math.fround;
const s8 = (n: number): number => (n << 24) >> 24;
const axes = ['x', 'y', 'z'] as const;
const CONTINUE = {type:'continue'} as const;
const carry = f(.95), decay = f(.92);
function clearDouble(s: DoubleNinjaXEngineState): void {
  s.arm7c8 = 0;
  for (const axis of axes) s.offset7b0[axis] = 0;
}
function move(s: DoubleNinjaXEngineState, h: DoubleNinjaXEngineHooks): void {
  for (const axis of axes) s.motion[axis] = f(s.motion[axis] * carry);
  for (const axis of axes) s.pos[axis] = f(s.pos[axis] + s.motion[axis]);
  h.ground679d0(s);
}
function setup(s: DoubleNinjaXEngineState, h: DoubleNinjaXEngineHooks): DoubleNinjaXEngineOutcome {
  for (const axis of axes) s.offset7b0[axis] = f(s.offset7b0[axis] * decay);
  move(s, h);
  h.tickStream(s, 15);
  if (s.streamEnded1cee !== 0) {
    if (s.timer560 === 0) {
      s.timer560 = 10;
      h.feedback061a8(s, 5);
    }
    s.timer560 = f(s.timer560 - s.dt);
    if (s.timer560 <= 0) {
      s.phase = s8(s.phase + 1);
      clearDouble(s);
    }
  }
  return CONTINUE;
}
/** One source dispatch. Phase0 also calls phase1; phase2's ramp does NOT tick
 * the stream. The zero crossing releases its hold; arm1 is the NEXT dispatch.
 * Live state is re-read after hooks, matching the original call boundaries. */
export function tickDoubleNinjaXEngine(s: DoubleNinjaXEngineState,
  h: DoubleNinjaXEngineHooks): DoubleNinjaXEngineOutcome {
  switch (s8(s.phase)) {
    case 0: {
      s.phase = s8(s.phase + 1);
      s.timer560 = 0; s.timer558 = 15; s.magnitude55c = 0;
      if (s.arm7c8 === 1) s.arm7c8 = 2;
      else clearDouble(s);
      s.gravityCoeff = s.yVel = s.hDecel = s.hSpeed = 0;
      s.poseAccum80 = s.poseAccum7e = s.poseAccum7c = 0;
      for (const axis of axes) s.motion[axis] = f(s.pos[axis] - s.savedOwnPos5e8[axis]);
      move(s, h);
      h.startStream(s, 15, 4, (s.controlWord & 0x40) !== 0 ? 3 : 2, -1, -1, -1);
      return setup(s, h);
    }
    case 1: return setup(s, h);
    case 2: {
      move(s, h);
      if (s.timer558 <= 0) {
        s.arm7c8 = 1; s.magnitude55c = 150;
        h.tickStream(s, 15);
        if (s.streamEnded1cee !== 0) {
          s.actionFlag73f = 0;
          s.controlWord = (s.controlWord & 0xfffffffc) >>> 0;
          if ((s.controlWord & 0x40) !== 0) {
            h.airReturn6a5a4(s); return {type:'cleanup',exit:'air'};
          }
          h.groundIdle6a474(s); return {type:'cleanup',exit:'ground'};
        }
      } else {
        s.timer558 = f(s.timer558 - s.dt);
        if (s.timer558 <= 0) {
          s.timer558 = 0;
          h.releaseStream4cff4(s, 15);
        }
        s.arm7c8 = 2;
        const angle = (Math.trunc(f(16384 * f(s.timer558 / 15))) << 16) >> 16;
        s.magnitude55c = f(150 * h.cosine45238(angle));
      }
      // Cleanup returns BEFORE this copy, preserving the previous offset.
      for (const axis of axes) s.offset7b0[axis] = f(s.matrixX8d4[axis] * s.magnitude55c);
      return CONTINUE;
    }
    default: return {type:'unsupported',phase:s8(s.phase)};
  }
}
