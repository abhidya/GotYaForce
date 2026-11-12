/** pl0104 bank803209e0 group4 slots0..2 only, not a generic stream VM.
 * Original wait operands, AOBJ durations and descriptor loop data are recorded in
 * beam-source-x-2026-11-12.md. Wait tests precede animation advancement. */
export interface BeamStreamClock {
  slot: number;
  stage: 'windup' | 'contact' | 'pause' | 'fireBlend' | 'loop' | 'recover' | 'terminal';
  frame: number;
  blendElapsed: number;
  blendDuration: number;
  remaining: number;
}
export interface BeamStreamEvent {
  contact?: number;
  animation?: number;
  completed?: boolean;
}
export function createBeamStreamClock(slot: number): BeamStreamClock {
  return {
    slot,
    stage: slot === 0 ? 'windup' : slot === 1 ? 'loop' : 'recover',
    frame: slot === 1 ? 6 : 0,
    blendElapsed: slot === 1 ? 0 : 1,
    blendDuration: slot === 0 ? 16 : slot === 1 ? 0 : 6,
    remaining: 0,
  };
}
function advanceAnimation(clock: BeamStreamClock, dt: number): void {
  if (clock.blendDuration > 0) {
    clock.blendElapsed += dt;
    if (clock.blendElapsed >= clock.blendDuration) {
      clock.frame += clock.blendElapsed - clock.blendDuration;
      clock.blendDuration = 0;
    }
  } else {
    clock.frame += dt;
  }
}
export function tickBeamStream(clock: BeamStreamClock, dt: number): BeamStreamEvent {
  switch (clock.stage) {
    case 'windup':
      if (clock.blendDuration === 0 && clock.frame >= 9) {
        clock.stage = 'contact';
        clock.remaining = 2;
        return { contact: 1 };
      }
      advanceAnimation(clock, dt);
      return {};
    case 'contact':
      clock.remaining -= dt;
      if (clock.remaining <= 0) {
        clock.stage = 'pause';
        clock.remaining = 30;
        return { contact: 0 };
      }
      return {};
    case 'pause':
      clock.remaining -= dt;
      if (clock.remaining <= 0) {
        clock.stage = 'fireBlend';
        clock.frame = 0;
        clock.blendElapsed = dt;
        clock.blendDuration = 6;
        return { animation: 1 };
      }
      return {};
    case 'fireBlend':
      if (clock.blendDuration === 0 && clock.frame >= 5) return { completed: true };
      advanceAnimation(clock, dt);
      return {};
    case 'loop':
      // Descriptor flags5 loop the motion at9..11. No terminal stream flag.
      clock.frame += dt;
      if (clock.frame >= 11) clock.frame = 9 + ((clock.frame - 9) % 2);
      return {};
    case 'recover':
      if (clock.blendDuration === 0 && clock.frame >= 8) {
        clock.stage = 'terminal';
        return {};
      }
      advanceAnimation(clock, dt);
      return {};
    case 'terminal':
      return { completed: true };
  }
}
