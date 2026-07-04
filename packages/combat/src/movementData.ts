// Per-borg movement physics adapter — RAW ROM scale (2026-07-04 migration).
//
// Source: data/movementPhysics.json (scripts/gen-movement-physics.mjs), the per-borg
// pl####data.bin parameter page (DERIVED — big-endian floats, loaded to actor+0x4ac).
// Evidence for the runtime formulas: research/decomp/movement-hit-decode-2026-07-04.md —
// the full ground-speed chain is DERIVED:
//   worldDelta/frame = speed(+0x44) × statusTimescale(+0x5f4) × tierVelScale(+0x5f8)
// with BOTH multipliers ×1.0 at baseline, so ROM world units are 1:1 with the port's stage
// geometry and page values apply RAW (the old 22.0 trace anchor and the ratio-anchored v1 of
// this adapter are retired — no code path produces 22.0; the trace was a mis-sample).
//
// Wired fields (RAW):
//   - maxHSpeed (+0x2c): THE ground run speed — run-start states SNAP actor+0x44 to it
//     (zz_005f578_ chunk_0007.c:5973). The guide "speed stat" (+0x50 minTurnSpeed) is only
//     a launch/landing floor, NOT run speed.
//   - jumpImpulse (+0x48): the launch state writes +0x48 = page[+0x48] (chunk_0008.c:329).
//   - gravityFall (+0x6c): the airborne fall gravity slot (pl0d/pl0e satellite families
//     carry -0.1 → genuinely floaty; applied as-is).
// NOT yet wired (exported as data only):
//   - minTurnSpeed launch-floor / 0.5× landing-seed semantics (FLOAT_80437460=0.5);
//   - the +0x74/+0x78/+0x7c accel-clamp triplet (actor+0x678, only active while +0x4c>0);
//   - status timescale (+0x5f4: haste {1.25,1.5,1.75} / slow {0.7,0.4,0.2} / freeze 0.03)
//     and the param-tier velocity table (0x802dd5a0: tier 16=×1.0 … 20=×2.366 — the
//     "acceleration"-style self-buff is +4 tiers for 1200f) — the tier/status WRITERS are
//     special-move wiring, a separate slice; BorgRuntime.paramTier already carries state.
//   - dash page (+0x58/+0x5c/+0x60/+0x64) — WIRED 2026-07-04 via dashPhysicsForBorgId
//     (was mislabeled knockdownLaunch*; the dash states FUN_80061560/FUN_80063230 seed
//     actor speed/accel/v-speed/duration verbatim from these fields).

import movementPhysicsData from "./data/movementPhysics.json" with { type: "json" };
import { JUMP } from "./constants.js";

export interface BorgMovementPhysics {
  /** +0x2c — ground RUN speed (run start snaps actor+0x44 to this; RAW u/f). */
  maxHSpeed: number;
  /** +0x44 — ground-accel magnitude; 0.0 leaves speed wherever the state entry snapped it. */
  groundAccel: number;
  /** +0x48 — jump / vertical impulse (RAW u/f; G RED 15.0). */
  jumpImpulse: number;
  /** +0x50 — min/turn speed = the guide "speed stat"; launch floor + 0.5× landing seed. */
  minTurnSpeed: number;
  /** +0x58 — DASH horizontal speed: the dash states (FUN_80061560 chunk_0007.c:7231-7238,
   *  FUN_80063230 chunk_0008.c:1220-1223/1631-1634) snap actor+0x44 to this on entry.
   *  Previously mislabeled knockdownLaunchHSpeed. */
  dashHSpeed: number;
  /** +0x5c — DASH per-frame accel (negative decay applied via actor+0x4c while dashing). */
  dashAccel: number;
  /** +0x60 — DASH vertical speed seed (actor+0x48; air-dash path FUN_80061560 only). */
  dashVSpeed: number;
  /** +0x64 — DASH duration in frames (actor+0x568 counter, ticked down by the status
   *  timescale +0x5f4 each frame; phase advances when it reaches 0). */
  dashDurationFrames: number;
  /** +0x68 — gravity slot A (ground/turn states). */
  gravityGround: number;
  /** +0x6c — gravity slot B: the true airborne fall gravity (RAW u/f²; G RED -1.0). */
  gravityFall: number;
  /** +0x70 — gravity slot C. */
  gravityC: number;
  /** +0xa8 — status-immunity mask A (u16), checked against a hit record's flagsA. A matching
   *  bit blocks that flagsA status write (grow/shrink). DERIVED, status-effects-decode-
   *  2026-07-04.md §B (chunk_0007.c:24-25). */
  statusImmunityA: number;
  /** +0xaa — status-immunity mask B (u16), checked against a hit record's flagsB. A matching
   *  bit blocks that flagsB status write (slow/haste, discrete or aura). Bit 0x400 is SHARED
   *  by both aura types (contact-slow and contact-haste). */
  statusImmunityB: number;
}

type MovementPhysicsFile = {
  _meta: Record<string, unknown>;
  borgs: Record<string, BorgMovementPhysics>;
};

const DATA = movementPhysicsData as MovementPhysicsFile;

/** Raw DERIVED movement page for a borg, or null for ids without a pl####data.bin. */
export function movementPhysicsForBorgId(id: string): BorgMovementPhysics | null {
  return DATA.borgs[id.toLowerCase()] ?? null;
}

/** DERIVED ground run speed (RAW page+0x2c), or null for ids without a data page —
 *  callers fall back to the MOVE fallback formula for synthetic borgs. */
export function groundRunSpeedForBorgId(id: string): number | null {
  const data = movementPhysicsForBorgId(id);
  return data && data.maxHSpeed > 0 ? data.maxHSpeed : null;
}

/** DERIVED jump takeoff velocity (RAW page+0x48); global fallback for ids without data. */
export function jumpVelocityForBorgId(id: string): number {
  const data = movementPhysicsForBorgId(id);
  return data && data.jumpImpulse > 0 ? data.jumpImpulse : JUMP.VELOCITY;
}

/** DERIVED fall gravity magnitude (RAW |page+0x6c|); global fallback for ids without data. */
export function fallGravityForBorgId(id: string): number {
  const data = movementPhysicsForBorgId(id);
  const mag = data ? Math.abs(data.gravityFall) : 0;
  return mag > 0 ? mag : JUMP.GRAVITY;
}

/** DERIVED per-borg dash physics (RAW page +0x58/+0x5c/+0x60/+0x64 — the dash states seed
 *  actor speed/accel/v-speed/duration verbatim from these; see the field docs above), or
 *  null for ids without a data page (callers fall back to the TUNED DASH block). Pages with
 *  a zero/negative dash speed also return null — those borgs have no authored dash. */
export function dashPhysicsForBorgId(
  id: string,
): { hSpeed: number; accel: number; vSpeed: number; durationFrames: number } | null {
  const data = movementPhysicsForBorgId(id);
  if (!data || !(data.dashHSpeed > 0) || !(data.dashDurationFrames > 0)) return null;
  return {
    hSpeed: data.dashHSpeed,
    accel: data.dashAccel,
    vSpeed: data.dashVSpeed,
    durationFrames: Math.round(data.dashDurationFrames),
  };
}

/** DERIVED per-borg status-immunity masks (RAW page+0xa8/+0xaa u16), or all-zero (no
 *  immunity) for ids without a data page. See status-effects-decode-2026-07-04.md §B. */
export function statusImmunityMasksForBorgId(id: string): { immunityA: number; immunityB: number } {
  const data = movementPhysicsForBorgId(id);
  return { immunityA: data?.statusImmunityA ?? 0, immunityB: data?.statusImmunityB ?? 0 };
}
