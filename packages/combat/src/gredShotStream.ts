/** Source-backed, center-clip clocks for G RED-family ordinary B.
 * g2s0 @80366638 falls through its nonterminal ended wait into g2s1 @8036665c.
 * Opcode0d uses48f9c/4a60c (mode6), and unlike opcode01 DOES receive the
 * parser4c050's same-call49e58 update. Retained animation rate is the explicit
 * host rate1 seam. Signed +1dfc side-clip blending/rendering is not reproduced.
 * Authored g2s4/5 alias g2s0/1. Authored g2s6/7 use triples [4,3,5]/[10,9,11]
 * instead of [1,0,2]/[7,6,8]. Center META2/0 -> MOT3/0 End11, META2/6 ->
 * MOT3/11 End35, META2/3 -> MOT3/5 End11, META2/9 -> MOT3/16 End15; no loops.
 * No HIT registration, callback, ammo allocation or projectile event exists.
 */
export interface GRedShotStream {
  /** Authored script slot, distinct from its META center animation slot. */
  authoredSlot: GRedShotStreamSlot;
  /** Even startup slot identifies the alias/clip profile across fallthrough. */
  profile: 0 | 4 | 6;
  animationSlot: 0 | 3 | 6 | 9;
  stage: 'startup' | 'repeat' | 'terminal';
  frame: number;
  elapsed: number;
  blendMode: 0 | 6;
  blendElapsed: number;
  blendTotal: number;
  endFrame: number;
  stopped: boolean;
  ended: boolean;
  completed: boolean;
  /** Only the terminal00090010 uses a countdown. It is not an animation clock. */
  waitRemaining: number;
  /** Source wait already installed by the parser; never poll two waits at once. */
  wait: 'frame3' | 'ended' | 'frame4' | 'terminal';
}

export type GRedShotStreamEvent =
  | { type: 'play'; group: 2; slot: 0 | 3 | 6 | 9 }
  | { type: 'contact'; value: 0 | 1 | -1; aux: 0; group: 1;
      actionFlag6e8: 1; actionFlag6e9: 0 }
  | { type: 'movement'; dashStrength: 0; faceGate: 0 }
  | { type: 'equipment'; value: readonly [4, 255] }
  | { type: 'completed' };

export interface GRedShotStreamOverride { startFrame: number; blend: number }
export interface GRedShotStreamStart { stream: GRedShotStream; events: GRedShotStreamEvent[] }
export type GRedShotStreamSlot = 0 | 1 | 4 | 5 | 6 | 7;
const f32 = Math.fround;

function advance(s: GRedShotStream, dt: number): void {
  s.elapsed = f32(s.elapsed + dt);
  if (s.blendMode === 6) {
    s.blendElapsed = f32(s.blendElapsed + dt);
    if (s.blendElapsed >= s.blendTotal) {
      s.frame = f32(s.frame + f32(s.blendElapsed - s.blendTotal));
      if (s.frame >= s.endFrame) s.stopped = true;
      // 4a60c calls49b98/b76c before clearing mode6. End marking is suppressed.
      s.blendMode = 0;
    }
  } else {
    // Preserve first-crossing overshoot; the nonlooping AOBJ then stays stopped.
    if (!s.stopped) s.frame = f32(s.frame + dt);
    if (s.frame >= s.endFrame) { s.stopped = true; s.ended = true; }
  }
}

function contact(value: 0 | 1 | -1): GRedShotStreamEvent {
  return { type: 'contact', value, aux: 0, group: 1, actionFlag6e8: 1, actionFlag6e9: 0 };
}

function play(s: GRedShotStream, slot: GRedShotStreamSlot, dt: number,
  override?: GRedShotStreamOverride): GRedShotStreamEvent[] {
  const startup = (slot & 1) === 0;
  const blend = override?.blend ?? (startup ? 5 : 0);
  s.authoredSlot = slot;
  s.profile = (slot & ~1) as 0 | 4 | 6;
  s.animationSlot = s.profile === 6 ? (startup ? 3 : 9) : (startup ? 0 : 6);
  s.stage = startup ? 'startup' : 'repeat';
  s.frame = f32(override?.startFrame ?? 0);
  s.elapsed = 0;
  s.blendMode = blend === 0 ? 0 : 6;
  s.blendElapsed = blend === 0 ? 0 : f32(dt);
  s.blendTotal = blend === 0 ? 0 : f32(blend + 1);
  s.endFrame = startup ? 11 : s.profile === 6 ? 15 : 35;
  s.stopped = false;
  s.ended = false;
  s.completed = false;
  s.waitRemaining = 0;
  s.wait = startup ? 'frame3' : 'frame4';
  const events: GRedShotStreamEvent[] = [
    { type: 'play', group: 2, slot: s.animationSlot },
    contact(startup ? 0 : 1),
    { type: 'movement', dashStrength: 0, faceGate: 0 },
  ];
  if (!startup) events.push({ type: 'equipment', value: [4, 255] });
  // 0d does not set4c050's "saw opcode01" flag. Parsing stops at the first
  // wait and advances exactly once, even when that newly installed wait is met.
  advance(s, dt);
  return events;
}

/** Starts the original stream, including the parser's first animation update.
 * Apply the returned initial writes just like events returned from tick.
 * Slot1's only source override is startFrame4/blend1 on an early repeat. */
export function createGRedShotStream(slot: GRedShotStreamSlot, dt = 1,
  override?: GRedShotStreamOverride): GRedShotStreamStart {
  const stream: GRedShotStream = { authoredSlot: slot, profile: 0, animationSlot: 0,
    stage: 'startup', frame: 0, elapsed: 0,
    blendMode: 0, blendElapsed: 0, blendTotal: 0, endFrame: 11, stopped: false,
    ended: false, completed: false, waitRemaining: 0, wait: 'frame3' };
  return { stream, events: play(stream, slot, dt, override) };
}

/** 4cd24 reads the old frame/ended flag. Satisfied nonterminal waits parse ONE
 * following block. Mode9 entry still advances, but subsequent countdown ticks
 * freeze all animation clocks, including the completion tick. */
export function tickGRedShotStream(s: GRedShotStream, dt: number): GRedShotStreamEvent[] {
  if (s.completed) return [];
  if (s.wait === 'terminal') {
    s.waitRemaining = Math.max(0, f32(s.waitRemaining - dt));
    if (s.waitRemaining === 0) {
      s.completed = true;
      return [{ type: 'completed' }];
    }
    return [];
  }
  if (s.wait === 'ended' && s.ended) return play(s, (s.profile + 1) as 1 | 5 | 7, dt);
  let events: GRedShotStreamEvent[] = [];
  if (s.wait === 'frame3' && s.frame >= 3) {
    s.wait = 'ended';
    events = [{ type: 'equipment', value: [4, 255] }];
  } else if (s.wait === 'frame4' && s.frame >= 4) {
    s.stage = 'terminal';
    s.wait = 'terminal';
    s.waitRemaining = 16;
    events = [contact(-1)];
  }
  advance(s, dt);
  return events;
}
