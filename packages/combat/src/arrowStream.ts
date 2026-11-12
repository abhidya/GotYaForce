/** Arrow Ninja/Shijima bank8030d4c0, group4 slots0/1 only.
 * Stream addresses8030dcd4/8030dd28: animation-relative waits9,17,21,34,
 * then terminal animation-end wait. This clock is gameplay-owned, not renderer-owned.
 * zz_004cd24_ tests a wait before advancing animation. For a satisfied wait,
 * zz_004c050_ parses the following block and advances animation when that
 * block has no new playAnim opcode, as at all four Arrow thresholds. */
export interface ArrowStreamClock {
  slot: 0 | 1;
  waitIndex: number;
  frame: number;
  blendElapsed: number;
  blendDuration: number;
  endFrame: number;
  completed: boolean;
}

export interface ArrowStreamEvent {
  contact?: number;
  /** The reached source animation-frame gate, not elapsed battle frames. */
  gate?: number;
  completed?: boolean;
}

const WAITS = [9, 17, 21, 34] as const;
/** GG4E08 pl0002mot and independently unpacked pl000b.pzz motion member3:
 * g4 slots0/1 AOBJ EndFrame, raw42340000, all20 AOBJs in both borgs.
 * Source descriptor bank8030cf40, records8030d494/8030d4a8; flags0, no loop. */
export const ARROW_ANIMATION_END = 45;

/** Both source streams encode blend3 (duration4), start0, animation mode1.
 * End frame must come from the source animation descriptor/AOBJ, never from
 * the last decoded event. */
export function createArrowStreamClock(slot: 0 | 1, endFrame = ARROW_ANIMATION_END): ArrowStreamClock {
  if (!Number.isFinite(endFrame) || endFrame < 34) throw new Error('Invalid Arrow animation end frame');
  return { slot, waitIndex: 0, frame: 0, blendElapsed: 1,
    blendDuration: 4, endFrame, completed: false };
}

export function tickArrowStream(clock: ArrowStreamClock, dt: number): ArrowStreamEvent {
  if (clock.completed) return { completed: true };
  const gate = WAITS[clock.waitIndex];
  let event: ArrowStreamEvent = {};
  if (clock.blendDuration === 0) {
    if (gate !== undefined && clock.frame >= gate) {
      clock.waitIndex++;
      event = { gate, contact: gate === 21 ? 1 : gate === 34 ? -1 : 0 };
    }
    if (gate === undefined && clock.frame >= clock.endFrame) {
      clock.completed = true;
      return { completed: true };
    }
  }
  if (clock.blendDuration > 0) {
    clock.blendElapsed += dt;
    if (clock.blendElapsed >= clock.blendDuration) {
      clock.frame += clock.blendElapsed - clock.blendDuration;
      clock.blendDuration = 0;
    }
  } else {
    clock.frame = Math.min(clock.endFrame, clock.frame + dt);
  }
  return event;
}
