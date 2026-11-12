/** G RED-family ordinary B upper-body airborne action0/v3 and fallback v4.
 * Bounded control-flow port of root18d288, 18d6f0/72c/7e4/8c0 and
 * 18dab4/dafc/dbb4/dcb0, research/decomp/ghidra-export/chunk_0046.c:5240 onward
 * and chunk_0047.c:1–281. Lower locomotion runs BEFORE this root in55568;
 * v3 never integrates physics here. Host terrain, aiming, streams and projectile
 * allocation remain explicit seams, not instruction-level console equivalence.
 */
import type { GRedShotEngineState } from './gredShotEngine.js';

export interface GRedAirShotEngineState extends GRedShotEngineState {
  variant: 1 | 2 | 3 | 4;          // +581; variants1/2 are an explicit scope boundary
  lockYaw5ae: number;
  movementCue5e4: number;
  faceGate1d10: number;
  lowerState5db: number;
  animationGroup1afc: number;
  animationSlot1afd: number;
}

/** Hooks operate on live state. Separate actor adapters must synchronize both
 * ways at each hook boundary. Start defaults preserve source rate/frame/blend
 * overrides -1/-1/-1, and part2 must not overwrite upper-part P0. */
export interface GRedAirShotEngineHooks {
  roll6dee8(state: GRedAirShotEngineState, preserveOutOfCone: 1): number;
  aim6d0dc(state: GRedAirShotEngineState, mode: 0x81, arg: 0): boolean;
  startStream(state: GRedAirShotEngineState, mask: 1 | 2, group: 0 | 2, slot: number,
    startFrame?: number, blend?: number): void;
  tickStream(state: GRedAirShotEngineState, mask: 1 | 15): void;
  primary67310(state: GRedAirShotEngineState, scale: 1, lockYaw: number): void;
  ground677b0(state: GRedAirShotEngineState): void;
  airReturn6a5a4(state: GRedAirShotEngineState): void;
  ammo6dbe0(state: GRedAirShotEngineState, cell: 0, count: 1, debit: boolean): boolean;
  spawnC3be0(state: GRedAirShotEngineState, row: 43 | 101 | 102): void;
  capture6bf80(state: GRedAirShotEngineState): void;
  carryEffectB22f4?(state: GRedAirShotEngineState): void;
  /** Action bits have already been cleared. Argument20 is NOT an attack lockout. */
  idleTransition6a668(state: GRedAirShotEngineState, duration: 20): void;
}

export type GRedAirShotOutcome =
  | { type: 'continue' }
  | { type: 'redispatch'; action: 0; subtype: 0 | 4; direction: 2 }
  | { type: 'cleanup' }
  /** Source-selected locomotion variants and streams outside this bounded port.
   * Report rather than substituting neutral-air or ground scripts. */
  | { type: 'unsupported'; variant: 1 | 2; slot?: number };

const f32 = Math.fround;
const s8 = (value: number): number => (value << 24) >> 24;
const s16 = (value: number): number => (value << 16) >> 16;
const ROOT_DECAY = f32(.96);
const RELEASE = { red: { repeat: 12, row: 43 }, neo: { repeat: 8, row: 101 },
  black: { repeat: 16, row: 102 } } as const;
const CONTINUE = { type: 'continue' } as const;

function redispatch(subtype: 0 | 4): GRedAirShotOutcome {
  return { type: 'redispatch', action: 0, subtype, direction: 2 };
}

function release(s: GRedAirShotEngineState, h: GRedAirShotEngineHooks): void {
  const family = RELEASE[s.family];
  s.timer560 = 20;
  s.streamSlot6ee = 1;
  s.repeatTimer558 = family.repeat;
  if (h.ammo6dbe0(s, 0, 1, true)) {
    h.spawnC3be0(s, family.row);
    s.remaining6ef = s8(s.remaining6ef - 1);
  }
  if (s16(s.ammo774) < 1) s.remaining6ef = 0;
}

function cleanup(s: GRedAirShotEngineState, h: GRedAirShotEngineHooks): GRedAirShotOutcome {
  s.actionFlag6e8 = 0;
  s.actionFlag73f = 0;
  s.controlWord = (s.controlWord & 0xfffffffc) >>> 0;
  // Unlike ground18d534 there is no6a474 ground-idle helper here.
  h.idleTransition6a668(s, 20);
  return { type: 'cleanup' };
}

function repeat(s: GRedAirShotEngineState, h: GRedAirShotEngineHooks): GRedAirShotOutcome {
  if ((s.input5d4 & 0x20) !== 0) s.latch745 = 1;
  h.tickStream(s, 1);
  if (s.repeatTimer558 <= 0) {
    if (s8(s.latch745) !== 0) {
      if (!h.ammo6dbe0(s, 0, 1, false)) return cleanup(s, h);
      h.capture6bf80(s);
      s.latch745 = 0;
      s.phase = s8(s.phase - 1);
      let slot: number;
      if ((s.controlWord & 0x40) === 0 && s8(s.movementCue5e4) !== 4) {
        if ((s.controlWord & 0x10) !== 0) {
          s.variant = 1;
          return { type: 'unsupported', variant: 1, slot: 3 };
        }
        if ((s.controlWord & 0x20) !== 0) {
          s.variant = 2;
          slot = s8(s.lowerState5db) === 15 ? 1 : s8(s.faceGate1d10) + 9;
          return { type: 'unsupported', variant: 2, slot };
        }
        return redispatch(0);
      }
      s.variant = 3;
      slot = (s.controlWord & 0x80) !== 0 ? 7 : 5;
      // Preserve the source's literal mixed key, NOT logical script equality.
      const oldAnimation = s8(s.animationSlot1afd) + s8(s.animationGroup1afc) * 0x1000;
      if (s8(s.contactP0) < 0 && slot === oldAnimation) h.startStream(s, 1, 2, slot);
      else h.startStream(s, 1, 2, slot, 4, 1);
      return CONTINUE;
    }
  } else {
    s.repeatTimer558 = f32(s.repeatTimer558 - s.dt);
    h.roll6dee8(s, 1);
  }
  // This shared airborne recovery does NOT exit for fresh A (input5d4 bit1).
  if ((s.input5d8 & 0xf0) !== 0 || s8(s.completed1cee) !== 0) return cleanup(s, h);
  return CONTINUE;
}

/** Exactly one source wrapper update and one phase. No fabricated shared timer
 * tick, catch-up dispatch, physics for v3, or maximum-duration escape hatch. */
export function tickGRedAirShotEngine(s: GRedAirShotEngineState,
  h: GRedAirShotEngineHooks): GRedAirShotOutcome {
  s.rootAngle1900 = s16(Math.trunc(f32(s16(s.rootAngle1900) * ROOT_DECAY)));
  s.shift18da = s16(s.shift18da) >> 1;
  if (s.variant === 1 || s.variant === 2) return { type: 'unsupported', variant: s.variant };
  if (s.variant === 4) s.sideBlend1dfc = s16(s.sideBlend1dfc) >> 1;
  const phase = s8(s.phase);
  if (phase === 2) return repeat(s, h);
  if (s.variant === 3) {
    if (phase === 0) {
      // Known source slot selection, but no stand-in clocks for locomotion1/2.
      // The neutral-air adapter should never admit these lower-state controls.
      if ((s.controlWord & 0x20) !== 0) {
        return { type: 'unsupported', variant: 2,
          slot: (s8(s.lowerState5db) === 15 ? 0 : s8(s.faceGate1d10) + 8) + s8(s.streamSlot6ee) };
      }
      if ((s.controlWord & 0x10) !== 0) {
        return { type: 'unsupported', variant: 1, slot: 2 + s8(s.streamSlot6ee) };
      }
      s.phase = s8(s.phase + 1);
      s.latch745 = 0;
      s.timer560 = 20;
      h.roll6dee8(s, 1);
      h.startStream(s, 1, 2, ((s.controlWord & 0x80) !== 0 ? 6 : 4) + s8(s.streamSlot6ee));
    } else if (phase === 1) {
      const ready = h.roll6dee8(s, 1);
      if (s8(s.contactP0) === 0) h.tickStream(s, 1);
      if (ready < 0) return redispatch((s.controlWord & 0x40) === 0 ? 0 : 4);
      if (ready < 1) {
        s.timer560 = f32(s.timer560 - s.dt);
        if (s.timer560 > 0) return CONTINUE;
      }
      if (s8(s.contactP0) !== 0) {
        s.phase = s8(s.phase + 1);
        release(s, h);
      }
    }
    return CONTINUE;
  }
  if (phase === 0) {
    s.phase = s8(s.phase + 1);
    s.latch745 = 0;
    s.timer560 = 30;
    h.aim6d0dc(s, 0x81, 0);
    h.primary67310(s, 1, s16(s.lockYaw5ae));
    h.ground677b0(s);
    h.startStream(s, 1, 2, 6 + s8(s.streamSlot6ee));
    h.startStream(s, 2, 0, 13);
    s.accumulator80c = 0;
  } else if (phase === 1) {
    const dt = s.dt;
    if (s8(s.contactP0) !== 0) s.dt = 0;
    h.tickStream(s, 15);
    s.dt = dt;
    h.primary67310(s, 1, s16(s.lockYaw5ae));
    h.ground677b0(s);
    s.timer560 = f32(s.timer560 - s.dt);
    // Source v4 tests timeout before aim, unlike ground v0's aim-before-timeout.
    if ((s.timer560 <= 0 || h.aim6d0dc(s, 0x81, 0)) && s8(s.contactP0) !== 0) {
      s.phase = s8(s.phase + 1);
      release(s, h);
      s.controlWord = (s.controlWord & 0xfffffffd) >>> 0;
      h.airReturn6a5a4(s);
    }
    if (s.hSpeed > 3) h.carryEffectB22f4?.(s);
  }
  return CONTINUE;
}
