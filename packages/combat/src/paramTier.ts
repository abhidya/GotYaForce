import type { ActorParamTier } from "./types.js";

export const PARAM_TIER_RESET = 0x10;
export const PARAM_TIER_TIMER_FRAMES = 900;

export function resetActorParamTier(): ActorParamTier {
  return {
    tier: PARAM_TIER_RESET,
    deltaAccum: 0,
    timerFrames: 0,
  };
}

export function applyActorParamTierDelta127(state: ActorParamTier, signedDelta: number): number {
  const current = state.tier;
  const next = clampSigned(current + Math.trunc(signedDelta), -0x7f, 0x7f);
  state.tier = next;
  return next - current;
}

export function applyActorParamTierDelta63(state: ActorParamTier, signedDelta: number): number {
  const current = state.tier;
  const desired = current + Math.trunc(signedDelta);
  const appliedDelta = clampSigned(desired, -0x3f, 0x3f) - current;
  if (appliedDelta === 0) return 0;

  state.deltaAccum = toSignedByte(state.deltaAccum + appliedDelta);
  if (state.deltaAccum !== 0) state.timerFrames = PARAM_TIER_TIMER_FRAMES;
  applyActorParamTierDelta127(state, appliedDelta);
  return appliedDelta;
}

function clampSigned(n: number, lo: number, hi: number): number {
  return Math.min(hi, Math.max(lo, n));
}

function toSignedByte(n: number): number {
  const byte = ((Math.trunc(n) % 256) + 256) % 256;
  return byte >= 0x80 ? byte - 0x100 : byte;
}
