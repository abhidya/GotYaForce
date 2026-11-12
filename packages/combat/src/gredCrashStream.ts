/** G RED-family grounded neutral action2/v0 G Crash clocks. Original RED
 * g4s0 at8036704c, NEO g4s1 at8036728c, BLACK g4s4 at80367210.
 * playAnim487ec/4892c, clocks49f10/4a00c and wait interpreter4cd24 supply
 * the clock semantics. Main descriptor803679a2 has raw AOBJ EndFrame80;
 * recovery803675e2 (g0s14, bank0/slot24) has EndFrame1. Neither loops.
 * Rate byte0 retains the caller's rate; this admitted clock assumes rate1.
 * NEO/BLACK both play g4s3 from36 (rawEnd80), with mode1 blends16/6.
 * Initial HIT, part/strength/control and +709 writes belong to the caller.
 */
export type GRedCrashFamily = 'red' | 'neo' | 'black';
export interface GRedCrashStream {
  family: GRedCrashFamily;
  frame: number;
  elapsed: number;
  blendMode: 0 | 1;
  blendElapsed: number;
  blendTotal: number;
  endFrame: number;
  stopped: boolean;
  ended: boolean;
  /** Next absolute mode2 gate, not the number of interpreter invocations. */
  waitIndex: number;
  /** Mode8 countdown. Its positive-wait path freezes every animation clock. */
  waitCount: number;
  recovery: boolean;
  completed: boolean;
}

export interface GRedCrashStreamCallback {
  callback: 1 | 2;
  arg: number;
}

export interface GRedCrashStreamEvent {
  gate?: number;
  contact?: number;
  aux?: number;
  strength?: number;
  faceGate?: number;
  flags6e8?: number;
  /** Preserve original callback identity. Callback2/0 is functional target
   * refresh/range reset. Callback1/4 is presentation, not a HIT registration. */
  callbacks?: readonly GRedCrashStreamCallback[];
  recovery?: boolean;
  completed?: boolean;
}

const RED_GATES = [7, 34, 40, 41, 52, 62, 64, 68] as const;
const OTHER_GATES = [40, 41, 52, 62, 64] as const;

export function createGRedCrashStream(dt = 1, family: GRedCrashFamily = 'red'): GRedCrashStream {
  return {
    family, frame: family==='red'?0:36, elapsed: 0, blendMode: 1,
    blendElapsed: dt, blendTotal: family==='red'?3:family==='neo'?17:7,
    endFrame: 80, stopped: false, ended: false, waitIndex: 0, waitCount: 0,
    recovery: false, completed: false,
  };
}

function advance(s: GRedCrashStream, dt: number): void {
  s.elapsed = Math.fround(s.elapsed + dt);
  if (s.blendMode === 1) {
    s.blendElapsed = Math.fround(s.blendElapsed + dt);
    if (s.blendElapsed >= s.blendTotal) {
      s.frame = Math.fround(s.frame + Math.fround(s.blendElapsed - s.blendTotal));
      if (s.frame >= s.endFrame) s.stopped = true;
      // b76c observes the old nonzero blend mode, so cannot set ended here.
      s.blendMode = 0;
    }
  } else {
    // Preserve the first-crossing overshoot, including STOP set during blend.
    if (!s.stopped) s.frame = Math.fround(s.frame + dt);
    if (s.frame >= s.endFrame) { s.stopped = true; s.ended = true; }
  }
}

/** Tests the old clock before normal animation advance. A satisfied wait parses
 * one following block, stopping at its next wait. Entry into mode8 advances
 * normally; later positive countdowns skip the animation update entirely.
 * Countdown release parses mode2/64, not that gate's following writes.
 */
export function tickGRedCrashStream(s: GRedCrashStream, dt: number): GRedCrashStreamEvent {
  if (s.completed) return { completed: true };
  if (s.recovery) {
    // Terminal0001000f uses elapsed(+8), not current frame(+c) or AOBJ end.
    if (s.elapsed >= 15) { s.completed = true; return { completed: true }; }
    advance(s, dt);
    return {};
  }
  if (s.waitCount > 0) {
    // 4cd24 subtracts dt BEFORE testing, clamps at0, and skips the entire
    // animation update while still positive. Release resumes normal advance.
    s.waitCount = Math.max(0, Math.fround(s.waitCount - dt));
    if (s.waitCount === 0) advance(s, dt);
    return {};
  }

  const red=s.family==='red';
  const gate = (red?RED_GATES:OTHER_GATES)[s.waitIndex];
  let event: GRedCrashStreamEvent = {};
  if (gate !== undefined && s.frame >= gate) {
    s.waitIndex++;
    switch (gate) {
      case 7: event = { gate, callbacks: [{ callback: 1, arg: 0 }] }; break;
      case 34:
        // Opcode03's control wordFFFF preserves the existing control bits.
        event = { gate, strength: 0, faceGate: 1, callbacks: [{ callback: 1, arg: 1 }] };
        break;
      case 40: event = { gate, contact: 1, aux: 0, ...(!red?{flags6e8:2}:{}), callbacks: [{ callback: 2, arg: 0 }] }; break;
      case 41: event = { gate, callbacks: [{ callback: 1, arg: 4 }] }; break;
      case 52: event = { gate, callbacks: red?[{ callback: 1, arg: 2 }]:[{callback:1,arg:0},{callback:1,arg:2}] }; break;
      case 62: s.waitCount = 10; event = { gate }; break;
      case 64: event = { gate, contact: -1, aux: 0, strength: -1, faceGate: 0,
        ...(!red?{flags6e8:3,callbacks:[{callback:1 as const,arg:3}]}:{}) }; break;
      case 68: event = { gate, callbacks: [{ callback: 1, arg: 3 }] }; break;
    }
  } else if (gate === undefined && s.ended) {
    // mode0/-1 resumes at playAnim g0s14: mode1, blend15, start0, rate0.
    // playAnim resets both clocks; this call does not advance them again.
    s.recovery = true; s.frame = 0; s.elapsed = 0;
    s.blendMode = 1; s.blendElapsed = dt; s.blendTotal = 16;
    s.endFrame = 1; s.stopped = false; s.ended = false;
    return red?{ recovery: true }:{recovery:true,contact:-1,aux:0,flags6e8:0};
  }
  advance(s, dt);
  return event;
}
