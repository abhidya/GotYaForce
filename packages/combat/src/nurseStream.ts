/** Nurse bank802c2660 g4s2, its contiguous s3 continuation, and s4.
 * Unlike a flattened event schedule, mode3 parks at animation frame6 until
 * zz_004cff4 resumes; mode8 freezes animation for60 source ticks.
 * Descriptor timing is supplied by the source-backed family caller. */
export interface NurseStreamClock {
  stage: 'windup' | 'parked' | 'hit' | 'hold' | 'tail' | 'recover' | 'done';
  frame: number;
  blendElapsed: number;
  blendDuration: number;
  remaining: number;
  recoveryEnd: number;
}
export interface NurseStreamEvent { aux?: number; completed?: boolean }
export function createNurseStreamClock(recoveryEnd: number): NurseStreamClock {
  return { stage: 'windup', frame: 0, blendElapsed: 1, blendDuration: 1,
    remaining: 0, recoveryEnd };
}
function advance(clock: NurseStreamClock, dt: number): void {
  if (clock.blendDuration > 0) {
    clock.blendElapsed += dt;
    if (clock.blendElapsed >= clock.blendDuration) {
      clock.frame += clock.blendElapsed - clock.blendDuration;
      clock.blendDuration = 0;
    }
  } else clock.frame += dt;
}
/** Source004cff4 parses at the saved continuation pointer, retaining animation. */
export function resumeNurseStream(clock: NurseStreamClock, dt: number): void { clock.stage = 'hit'; advance(clock, dt); }
export function recoverNurseStream(clock: NurseStreamClock): void {
  clock.stage = 'recover'; clock.frame = 0; clock.blendElapsed = 1; clock.blendDuration = 7;
}
export function tickNurseStream(clock: NurseStreamClock, dt: number): NurseStreamEvent {
  switch (clock.stage) {
    case 'windup':
      if (clock.blendDuration === 0 && clock.frame >= 6) { clock.stage = 'parked'; return {}; }
      advance(clock, dt); return {};
    case 'parked': return {};
    case 'hit':
      if (clock.blendDuration === 0 && clock.frame >= 10) {
        clock.stage = 'hold'; clock.remaining = 60; advance(clock, dt); return { aux: 6 };
      }
      advance(clock, dt); return {};
    case 'hold':
      clock.remaining -= dt;
      if (clock.remaining <= 0) { clock.stage = 'tail'; advance(clock, dt); return { aux: 8 }; }
      return {};
    case 'tail': advance(clock, dt); return {};
    case 'recover':
      if (clock.blendDuration === 0 && clock.frame >= clock.recoveryEnd) {
        clock.stage = 'done'; return { completed: true };
      }
      advance(clock, dt); return {};
    case 'done': return { completed: true };
  }
}
