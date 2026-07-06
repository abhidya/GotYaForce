// SATELLITE family (ctors 0x8018882c pl0d01 / 0x8018890c pl0d05 — both Ghidra-missed,
// raw-disassembled). Covers the two borgs sharing root dispatcher FUN_80188b24:
//   pl0d01 (0x0d01) — X satellite + B pod launcher (action 2)
//   pl0d05 (0x0d05) — X satellite + B burst turret (action 0)
// Source: wav-eng-80188da4.json — 24/24 claims dual-lens CONFIRMED (no refutations).
//
// ARCHITECTURE (CFG-1/WRAP-1/WRAP-2, all confirmed): there is NO per-family wrapper and
// NO r4 config block. Both ctors copy 16-word blocks (0x803625d8 / 0x80362618) whose
// +0x4b4 slot is the SAME root dispatcher FUN_80188b24 @0x80188b24, which dispatches
// `(&PTR_FUN_80362658)[(s8)actor+0x580]` through ONE shared action table @0x80362658:
//   [0] = 0x80188b60 — B burst-turret machine  (phase table @0x80362664, 4 phases)
//   [1] = 0x80188da4 — THE X ENGINE            (phase table @0x80362674, 3 phases)
//   [2] = 0x80188ec4 — B pod-launcher machine  (phase table @0x80362680, 3 phases)
// Per-family divergence is (a) a runtime borg-number fork inside X phase 1
// (`s16 +0x3e8 == 0x0d01 ? variant 0 : variant 1` into zz_00fb220_) and (b) the command
// tables: pl0d01 types 2/5 → action 1, types 0/1/3/4 → action 2 (root @0x803628d8);
// pl0d05 types 2/5 → action 1, types 0/1/3/4 → action 0 (root @0x8037aac0). All 24
// records per table are identical `[cue 0x2d, ctrl 0x01, action, variant 0]` (CFG-3).
// Cue 0x2d → row 45 of the shared cue table 0x803627b8 → full-body state 61 → +0x4b4.
//
// THE X MACHINE (MACH-1..5, engine FUN_80188da4): the first ported family machine with
// ZERO stream-VM dependency — no zz_004beb8_/zz_004cd24_ calls, no contact-flag reads
// (+0x1cef/+0x1cee/+0x1d0f/+0x1d10), no velocity/gravity writes (+0x44..+0x50), no
// +0x560, no +0x694 cooldown. Purely timer-driven: the actor stands and launches; all
// motion lives in the spawned satellite child (SAT_CHILD_RECORD below). These borgs are
// gravity −0.1 floaters on the movement page — the machine adds NO physics of its own.
//
// Exit (MACH-4): zz_006a53c_(actor, 0) — because param 0 is not >0 it does NOT write
// the +0x694 cooldown (contrast ninja X's 4.0+dt); it clears +0x73f, masks +0x5e0 &= ~3
// and dispatches FULL-BODY cue 0x1b → cue-table row 27 = (0x00, 0x21) → idle state 0.

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import type { StreamContext } from "../rom/stream-vm.js";

// ============================================================================
// Constants — every ROM value DERIVED (dol.py reads, dual-lens verified).
// ============================================================================

/** X-machine constants (engine 0x80188da4, phases @0x80362674). */
export const SATELLITE_X = {
  /** FLOAT_8043afac = 0.0 — phase-0 windup seed AND the phase-2 timer floor. */
  ZERO: 0.0,
  /** FLOAT_8043afb0 = 30.0 — phase-1 recovery timer seed (+0x558; counts down by
   *  +0x1dc8 dt in phase 2). */
  RECOVERY: 30.0,
  /** zz_006dbe0_(actor, slot=2, cost=1, consume=1) — the X ammo gate (li r4,2/r5,1/
   *  r6,1 @0x80188e2c). The host (bridge) owns the real ammo count; see the
   *  ammo-gate note on satXPhase1. */
  AMMO_SLOT: 2,
  AMMO_COST: 1,
  /** Exit cue dispatched by zz_006a53c_ → zz_006a6fc_(actor, 0x1b). Cue-table row 27
   *  @0x803627ee = (0x00, 0x21) → full-body idle state 0. NO +0x694 cooldown write
   *  (the zz_006a53c_ param is 0; the write is gated on `0 < (int)param_2`). */
  EXIT_CUE: 0x1b,
  /** Action-mode bits 0..1 of +0x5e0, cleared by zz_006a53c_ (`+0x5e0 &= 0xfffffffc`). */
  ACTION_MODE_BITS: 0x3,
  /** zz_00fb220_ @0x800fb220 — the shared variant-parameterized satellite spawner
   *  (PF-3). Allocates a type-0x4d homing-satellite child via zz_0088aa0_(owner,3,8,
   *  0,1); update FUN_800fb330, draw/collide FUN_800fb7e0; child phase table
   *  @0x8031e930 = [deploy 0x800fb3c8, fly 0x800fb56c, 0x800fb7b4, idle 0x800fb7c0].
   *  The `type` arg passed through onFamilyProjectile is the variant (0=pl0d01,
   *  1=pl0d05 — the phase-1 borg fork). */
  SATELLITE_SPAWNER_ADDR: 0x800fb220,
  /** Borg number the phase-1 fork compares (`lha +0x3e8; cmpwi 0xd01`): equal →
   *  variant 0, else variant 1. */
  VARIANT0_BORG: 0x0d01,
} as const;

/** Satellite child motion record — the PF-4 drift facts, exported as LABELED DATA for
 *  the host's satellite-child implementation (the child itself is not an actor and is
 *  not ported here). Tables: A @0x8031e8c8 (stride 0x18) + B @0x8031e8f8 (stride 0x1c),
 *  indexed by (variant & 0x7f). Variants 0 and 1 are byte-identical except A+0x00
 *  (v0=2, v1=1 — consumed by the zz_0006fb4_ setup call; semantics UNRESOLVED). */
export const SAT_CHILD_RECORD = {
  /** A+0x02 = 1 — owner part matrix used for the muzzle (owner+0x8d4 + bone*0x30). */
  MUZZLE_BONE: 1,
  /** A+0x04 float3 — muzzle offset, PSMTXMultVec against the bone matrix. */
  MUZZLE_OFFSET: { x: 0, y: -80, z: -10 },
  /** FLOAT_80439230 = -0.1 — dir.y forced BEFORE PSVECNormalize (launch down-tilt). */
  LAUNCH_TILT_Y: -0.1,
  /** B+0x10 = 10.0 — launch speed (PSQUATScale of the normalized dir; also child+0x44). */
  LAUNCH_SPEED: 10.0,
  /** B+0x14 = -5.0 — initial y-velocity (child+0x3c). */
  VY0: -5.0,
  /** B+0x18 = -0.1 — per-frame y-acceleration (child+0x50; `+0x3c += +0x50` each
   *  frame). This IS the "satellite drift": data-driven, NOT actor gravity. */
  VY_ACCEL: -0.1,
  /** B+0x08 = 3.0 — FUN_8006c498 homing steer rate toward lockTarget(+0xc8)+0x64. */
  HOMING_RATE: 3.0,
  /** B+0x04 = 4 — re-steer/fire interval frames (child+0x1cb counter). */
  HOMING_INTERVAL: 4,
  /** B+0x02 = 600 — lifetime frames (child+0x1c, -1/frame). */
  LIFE_FRAMES: 600,
  /** B+0x06 = 10 — shot budget (child+0x1c4/+0x1c6/+0x1c8). */
  SHOT_BUDGET: 10,
  /** B+0x0c = 200.0 — FUN_80083874 arg (hover/ground-avoid helper; body unread). */
  HOVER_ARG: 200.0,
  /** B+0x00 = 1 — zz_008ac80_ model index. */
  MODEL_INDEX: 1,
} as const;

/** B burst-turret constants (action 0, pl0d05's B command; MACH-7). */
export const SATELLITE_TURRET = {
  /** FLOAT_8043afa4 = 10.0 — phase-1 aim-window timer seed (lfs -0x3a7c(r2)). */
  AIM_WINDOW: 10.0,
  /** FLOAT_8043afa8 = 0.2 — FUN_8006cc90 aim steer rate (×dt). */
  AIM_RATE: 0.2,
  /** DAT_80435678 s16[4] = [0, 0, 0, 0x4000] — aim clamp: yaw [0,0] (no yaw), pitch
   *  [0, 0x4000] (up to +90°). Part 8 aim shorts, stride 6 (+0x18d4 base). */
  PITCH_MIN_BAM: 0,
  PITCH_MAX_BAM: 0x4000,
  /** No-target aim decay factor per frame: FLOAT_804376b0×(FLOAT_80437670 − dt) +
   *  FLOAT_80437694 = 0.04×(1.0 − dt) + 0.96 (FUN_8006cc90, +0xcc==0 branch). */
  DECAY_A: 0.04,   // FLOAT_804376b0
  DECAY_B: 1.0,    // FLOAT_80437670
  DECAY_C: 0.96,   // FLOAT_80437694
  /** u16 +0x14c reload seed — fires when the counter hits 0, then reloads 10 and
   *  decrements on non-fire frames: the true period is 11 frames (verifier nuance). */
  RELOAD: 10,
  /** Burst budget: exit after +0x14e > 9 when the button is held. */
  BURST_SHOTS: 9, // exit condition is shotCount > 9
  /** zz_006dbe0_(actor, slot=0, cost=1, consume=1) — per-shot ammo gate. */
  AMMO_SLOT: 0,
  AMMO_COST: 1,
  /** FLOAT_8043afb0 = 30.0 — phase-2→3 recovery seed (same literal as the X machine). */
  RECOVERY: 30.0,
  /** zz_0082824_ @0x80082824 — generic projectile spawner. Called with rec = 0x10 +
   *  muzzle toggle (+0x149 ^= 1 → alternating left/right pods). Records @DAT_802d7b30
   *  + rec*0x38 (PF-5): scale (0.75,0.75,0.75), speed 15.0, muzzle rec0x10 =
   *  (-15.48, 0, 41.44) vs rec0x11 = (34.43, 0, 57.15) — the only differing bytes. */
  SHOT_SPAWNER_ADDR: 0x80082824,
  SHOT_REC_BASE: 0x10,
  /** +0x5bc bit 0x200 — attack-button-held bit (rlwinm mask; latched into u16 +0x14a). */
  HELD_BIT: 0x200,
} as const;

/** B pod-launcher constants (action 2, pl0d01's B command; MACH-8). */
export const SATELLITE_POD = {
  /** FLOAT_8043afac = 0.0 — phase-0 windup (byte-identical shape to X phase 0). */
  WINDUP: 0.0,
  /** FLOAT_8043afb0 = 30.0 — phase-1 recovery seed. */
  RECOVERY: 30.0,
  /** zz_006dbe0_(actor, slot=0, cost=1, consume=1) — pod ammo gate (li r4,0). */
  AMMO_SLOT: 0,
  AMMO_COST: 1,
  /** zz_00fcd38_ @0x800fcd38 — pod child spawner: child type 0x4c, +0x11=0,
   *  +0x13=side; update FUN_800fce50 → phase table @0x8031eed8 = [0x800fcee8,
   *  0x800fd09c, 0x800fd338, 0x800fd344] (child untranscribed — B-side/port-later).
   *  The `type` arg passed through onFamilyProjectile is the side (0/1). */
  POD_SPAWNER_ADDR: 0x800fcd38,
} as const;

/** FUN_801889ec family-init constant: +0x1dc0 = FLOAT_8043afa0 = 70.0 (consumer
 *  unknown — surfaced for completeness; not used by any ported machine). */
export const SATELLITE_INIT_1DC0 = 70.0;

// ============================================================================
// Actor extension fields — the +0x140..+0x14f latch/counter block these machines own.
// Not on RomActor (family-local scratch); stored as extension fields per the
// robot.ts `robotDeployLatch` precedent.
// ============================================================================
interface SatelliteActorExt {
  /** +0x145: X "satellite deployed" latch (set on phase-1 grant; cleared by the
   *  family update when ammo slot 2 refills — FUN_80188a64 branch b). */
  satDeployedLatch?: number;
  /** +0x146/+0x147: per-side pod deployed latches (action 2). */
  satPodLatch?: [number, number];
  /** +0x148: pod side toggle ((side+1)&1 after each launch; read sign-extended —
   *  the ROM does extsb, only values 0/1 occur in normal flow). */
  satPodSide?: number;
  /** +0x149: turret muzzle toggle (^=1 per shot → recs 0x10/0x11). */
  satMuzzleToggle?: number;
  /** +0x14a (u16): turret button-held latch (set-only while +0x5bc & 0x200). */
  satHeldLatch?: number;
  /** +0x14c (u16): turret reload countdown (fire at 0, reload 10). */
  satReload?: number;
  /** +0x14e (u16): turret shot counter — increments BEFORE the ammo gate, so
   *  dry-fires still count toward the exit conditions (verifier nuance). */
  satShotCount?: number;
  /** APPROXIMATION of +0x5bc bit 0x200 (attack-button-held): the raw input word
   *  isn't surfaced on RomActor; the bridge mirrors the live held state here.
   *  Unset ⇒ treated as not held (tap behavior: 1-shot burst). */
  attackHeld?: boolean;
  /** Lock-target position (+0xcc/+0xc8 chain, bridge-synced) — turret aim input. */
  lockTarget?: { x: number; y: number; z: number } | null;
}

function ext(actor: RomActor): RomActor & SatelliteActorExt {
  return actor as RomActor & SatelliteActorExt;
}

export interface SatelliteFamilyCtx extends StreamContext {}

/** Port of zz_006a53c_(actor, 0) — the shared idle exit all three machines use.
 *  Param 0 ⇒ NO +0x694 cooldown write (gated on `0 < (int)param_2` in the ROM);
 *  clears +0x73f (unsurfaced housekeeping byte; no-op here), masks +0x5e0 &= ~3,
 *  then zz_006a6fc_(actor, 0x1b) — full-body cue only (no upper-body dispatch). */
function exitToIdle(actor: RomActor): void {
  actor.controlWord = actor.controlWord & ~SATELLITE_X.ACTION_MODE_BITS;
  dispatchFullBodyCue(actor, SATELLITE_X.EXIT_CUE);
}

// ============================================================================
// X machine — engine FUN_80188da4 @0x80188da4, phase table @0x80362674 =
// [0x80188de0, 0x80188df8, 0x80188e7c]. ZERO stream-VM calls (MACH-5): pure timers
// + payload spawn. The actor never moves during the special.
// ============================================================================

/** Phase 0 @0x80188de0 (Ghidra-missed; raw disasm). One-frame windup:
 *  +0x540++ and +0x558 = FLOAT_8043afac = 0.0. No other writes. */
function satXPhase0(actor: RomActor): void {
  actor.fbPhaseSlots[0] = 1;
  actor.handlerTimer = SATELLITE_X.ZERO;
}

/** Phase 1 @0x80188df8 (FUN_80188df8). +0x540++ (→2); +0x558 = 30.0; ammo-gated
 *  satellite spawn with the runtime borg fork. */
function satXPhase1(actor: RomActor, ctx: SatelliteFamilyCtx): void {
  actor.fbPhaseSlots[0] = 2;
  actor.handlerTimer = SATELLITE_X.RECOVERY;

  // zz_006dbe0_(actor, 2, 1, 1) — ammo gate. APPROXIMATION: the ammo counters
  // (+0x774+slot*8) live on the host's BorgRuntime, so the gate is modeled as
  // granted here and the host hook (which owns the real count) decides whether
  // the child actually spawns — same honest-no-op convention as robot.ts. The
  // deployed latch is set on the modeled grant, exactly as the ROM sets +0x145
  // only inside the granted branch.
  ext(actor).satDeployedLatch = 1; // stb +0x145 @0x80188e3c

  // Borg-number fork (lha +0x3e8; cmpwi 0xd01): 0x0d01 → zz_00fb220_(actor, 0),
  // else (0x0d05) → zz_00fb220_(actor, 1). This IS the per-family divergence —
  // the machine has no config block; family identity is read off the actor.
  const variant = actor.borgNumber === SATELLITE_X.VARIANT0_BORG ? 0 : 1;
  ctx.onFamilyProjectile?.(actor, SATELLITE_X.SATELLITE_SPAWNER_ADDR, variant);
}

/** Phase 2 @0x80188e7c (FUN_80188e7c). +0x558 -= dt; on <= 0.0 → zz_006a53c_(actor,0).
 *  Never increments +0x540 — the machine can never run past entry [2] into the
 *  overlapping action-2 table (MACH-4). */
function satXPhase2(actor: RomActor): void {
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= SATELLITE_X.ZERO) {
    exitToIdle(actor);
  }
}

/** X phase table — mirrors PTR @0x80362674 = [0x80188de0, 0x80188df8, 0x80188e7c]. */
const X_PHASE_TABLE: Array<(actor: RomActor, ctx: SatelliteFamilyCtx) => void> = [
  satXPhase0,
  satXPhase1,
  satXPhase2,
];

// ============================================================================
// B burst turret — action 0 (pl0d05), machine FUN_80188b60, phase table @0x80362664 =
// [0x80188b9c, 0x80188bc8, 0x80188c54, 0x80188d5c].
// ============================================================================

/** APPROXIMATION — FUN_8006cc90(rate 0.2, actor, part=8, 1, clamp @0x80435678) aim
 *  step. The ROM steers the part-8 aim shorts (+0x18d4 + 8*6 = +0x1904 yaw /
 *  +0x1906 pitch) toward the lock target: yaw clamped [0,0] (never moves), pitch
 *  clamped [0, 0x4000], stepped by rate×dt; with NO target (+0xcc == 0) it decays
 *  the shorts toward 0 by factor 0.04×(1.0−dt)+0.96 and returns 1 (converged) —
 *  so an unlocked turret advances to the fire phase on its first frame (verifier
 *  nuance). Returns 1 when converged.
 *  Approximated here because (a) per-part aim shorts aren't surfaced on RomActor —
 *  the pitch is carried on actor.steerYaw (the +0x18da-family aim-short surface,
 *  same convention as gred.ts phase 2/3), and (b) FUN_8006cc90's exact per-step
 *  integration formula was not fully transcribed (only rate, clamp, decay factor
 *  and return semantics are DERIVED) — the step below is an exponential approach
 *  by fraction rate×dt with a TUNED convergence epsilon. */
const AIM_CONVERGE_EPSILON_BAM = 0x100; // TUNED (port-side; not a ROM value)

function turretAimStep(actor: RomActor): boolean {
  const target = ext(actor).lockTarget ?? null;
  if (!target) {
    // No-target branch: decay toward 0 by the DERIVED factor, return converged.
    const factor =
      SATELLITE_TURRET.DECAY_A * (SATELLITE_TURRET.DECAY_B - actor.dt) +
      SATELLITE_TURRET.DECAY_C;
    actor.steerYaw = Math.trunc(actor.steerYaw * factor);
    return true;
  }
  // Desired pitch (BAM16, positive = up) toward the target, clamped [0, 0x4000].
  const dx = target.x - actor.pos.x;
  const dz = target.z - actor.pos.z;
  const dy = target.y - actor.pos.y;
  const hDist = Math.sqrt(dx * dx + dz * dz);
  let desired = Math.round((Math.atan2(dy, hDist) / (2 * Math.PI)) * 0x10000);
  if (desired < SATELLITE_TURRET.PITCH_MIN_BAM) desired = SATELLITE_TURRET.PITCH_MIN_BAM;
  if (desired > SATELLITE_TURRET.PITCH_MAX_BAM) desired = SATELLITE_TURRET.PITCH_MAX_BAM;

  const delta = desired - actor.steerYaw;
  const frac = Math.min(1, SATELLITE_TURRET.AIM_RATE * actor.dt);
  actor.steerYaw = Math.trunc(actor.steerYaw + delta * frac);
  return Math.abs(desired - actor.steerYaw) <= AIM_CONVERGE_EPSILON_BAM;
}

/** Held-button read — +0x5bc & 0x200, bridge-synced onto `attackHeld` (see the
 *  SatelliteActorExt doc). The ROM only ever SETS the +0x14a latch. */
function latchHeld(actor: RomActor): void {
  if (ext(actor).attackHeld === true) {
    ext(actor).satHeldLatch = 1;
  }
}

/** Phase 0 @0x80188b9c (Ghidra-missed; raw disasm). +0x540++, +0x558 = 10.0,
 *  zero u16 +0x14a/+0x14c/+0x14e and byte +0x149. */
function turretPhase0(actor: RomActor): void {
  actor.fbPhaseSlots[0] = 1;
  actor.handlerTimer = SATELLITE_TURRET.AIM_WINDOW;
  const a = ext(actor);
  a.satHeldLatch = 0;
  a.satReload = 0;
  a.satShotCount = 0;
  a.satMuzzleToggle = 0;
}

/** Phase 1 @0x80188bc8 (FUN_80188bc8). Held latch + timer + aim; advance when the
 *  aim converged (FUN_8006cc90 returns 1 — incl. the instant no-target path) OR
 *  the 10.0 window expires. */
function turretPhase1(actor: RomActor): void {
  latchHeld(actor); // if (+0x5bc & 0x200) u16 +0x14a = 1
  actor.handlerTimer -= actor.dt;
  const converged = turretAimStep(actor);
  if (converged || actor.handlerTimer <= SATELLITE_X.ZERO) {
    actor.fbPhaseSlots[0] = 2;
  }
}

/** Phase 2 @0x80188c54 (FUN_80188c54). Fire loop: fires when the u16 reload counter
 *  is 0 then reloads 10 (true period 11 frames — verifier nuance; the
 *  check-then-reload structure is reproduced, not a hardcoded modulo). Shot counter
 *  increments BEFORE the ammo gate (dry-fires count toward the exits). Exit to
 *  phase 3 (+0x558 = 30.0) when (+0x14a == 0 && +0x14e > 0) — tap released, ≥1
 *  tick — or +0x14e > 9 — full 10-tick burst. */
function turretPhase2(actor: RomActor, ctx: SatelliteFamilyCtx): void {
  latchHeld(actor); // re-latch each frame
  const a = ext(actor);
  if ((a.satReload ?? 0) === 0) {
    // Fire tick: +0x14e++ FIRST (pre-ammo-gate), then zz_006dbe0_(actor,0,1,1) →
    // zz_0082824_(actor, 0x10 + +0x149), +0x149 ^= 1, +0x14c = 10.
    a.satShotCount = (a.satShotCount ?? 0) + 1;
    // Ammo gate is host-owned (see satXPhase1 note); the hook decides the spawn.
    const rec = SATELLITE_TURRET.SHOT_REC_BASE + (a.satMuzzleToggle ?? 0);
    ctx.onFamilyProjectile?.(actor, SATELLITE_TURRET.SHOT_SPAWNER_ADDR, rec);
    a.satMuzzleToggle = (a.satMuzzleToggle ?? 0) ^ 1;
    a.satReload = SATELLITE_TURRET.RELOAD;
  } else {
    a.satReload = (a.satReload ?? 0) - 1;
  }

  const shots = a.satShotCount ?? 0;
  const tapExit = (a.satHeldLatch ?? 0) === 0 && shots > 0;
  const burstExit = shots > SATELLITE_TURRET.BURST_SHOTS;
  if (tapExit || burstExit) {
    actor.fbPhaseSlots[0] = 3;
    actor.handlerTimer = SATELLITE_TURRET.RECOVERY;
  }
}

/** Phase 3 @0x80188d5c (FUN_80188d5c). Countdown → zz_006a53c_(actor, 0) idle exit. */
function turretPhase3(actor: RomActor): void {
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= SATELLITE_X.ZERO) {
    exitToIdle(actor);
  }
}

/** Turret phase table — mirrors PTR @0x80362664 = [0x80188b9c, 0x80188bc8,
 *  0x80188c54, 0x80188d5c]. */
const TURRET_PHASE_TABLE: Array<(actor: RomActor, ctx: SatelliteFamilyCtx) => void> = [
  turretPhase0,
  turretPhase1,
  turretPhase2,
  turretPhase3,
];

// ============================================================================
// B pod launcher — action 2 (pl0d01), machine FUN_80188ec4, phase table @0x80362680 =
// [0x80188f00, 0x80188f18, 0x80188fac] (entry [3] is NULL @0x8036268c).
// ============================================================================

/** Phase 0 @0x80188f00 (Ghidra-missed; byte-identical shape to X phase 0):
 *  +0x540++, +0x558 = 0.0. */
function podPhase0(actor: RomActor): void {
  actor.fbPhaseSlots[0] = 1;
  actor.handlerTimer = SATELLITE_POD.WINDUP;
}

/** Phase 1 @0x80188f18 (FUN_80188f18). +0x540++ (→2); +0x558 = 30.0; ammo
 *  zz_006dbe0_(actor, 0, 1, 1); on grant: per-side latch byte at +0x146+(s8)+0x148
 *  = 1, zz_00fcd38_(actor, 0, side) pod spawn, then side = (side+1)&1. */
function podPhase1(actor: RomActor, ctx: SatelliteFamilyCtx): void {
  actor.fbPhaseSlots[0] = 2;
  actor.handlerTimer = SATELLITE_POD.RECOVERY;

  // Ammo gate host-owned (see satXPhase1 note) — modeled as granted.
  const a = ext(actor);
  const side = (a.satPodSide ?? 0) & 1; // extsb +0x148 (0/1 in normal flow)
  const latches = a.satPodLatch ?? [0, 0];
  latches[side] = 1; // stb 1 → +0x146+side
  a.satPodLatch = latches;
  ctx.onFamilyProjectile?.(actor, SATELLITE_POD.POD_SPAWNER_ADDR, side);
  a.satPodSide = (side + 1) & 1; // addi/stb + clrlwi (&1) toggle
}

/** Phase 2 @0x80188fac (FUN_80188fac). Countdown → zz_006a53c_(actor, 0) idle exit. */
function podPhase2(actor: RomActor): void {
  actor.handlerTimer -= actor.dt;
  if (actor.handlerTimer <= SATELLITE_X.ZERO) {
    exitToIdle(actor);
  }
}

/** Pod-launcher phase table — mirrors PTR @0x80362680 = [0x80188f00, 0x80188f18,
 *  0x80188fac, NULL]. */
const POD_PHASE_TABLE: Array<(actor: RomActor, ctx: SatelliteFamilyCtx) => void> = [
  podPhase0,
  podPhase1,
  podPhase2,
];

// ============================================================================
// Family update — port of FUN_80188a64 (+0x4bc per-frame virtual), branches (a)+(b).
// Branch (c) — the (+0x7d2 bits)-gated type-0x4e conditional summon via zz_011b68c_ —
// is EXCLUDED (child untranscribed; +0x7d2 semantics unresolved — see caveats).
// ============================================================================

/** The ammo counters (+0x774+slot*8 cur / +0x78e+slot*8 max) live on the host's
 *  BorgRuntime, so the bridge computes the refill predicates and calls this each
 *  frame. Re-deploy gating is ammo-regen-driven, NOT timer-driven:
 *  (a) borg 0x0d01 only: slot-0 refilled (cur >= max) → clear the pod latches
 *      +0x146/+0x147 and the side toggle +0x148;
 *  (b) both borgs: slot-2 refilled → clear the X deployed latch +0x145 — the
 *      satellite becomes re-summonable exactly when slot-2 ammo regenerates. */
export function satelliteFamilyUpdate(
  actor: RomActor,
  slot0Refilled: boolean,
  slot2Refilled: boolean,
): void {
  const a = ext(actor);
  if (actor.borgNumber === SATELLITE_X.VARIANT0_BORG && slot0Refilled) {
    a.satPodLatch = [0, 0];
    a.satPodSide = 0;
  }
  if (slot2Refilled) {
    a.satDeployedLatch = 0;
  }
}

// ============================================================================
// Root action dispatcher — port of FUN_80188b24 @0x80188b24 (the +0x4b4 virtual,
// invoked by full-body state 61): `(&PTR_FUN_80362658)[(s8)actor+0x580]`. ONE shared
// table for BOTH families (CFG-1) — exactly as the ROM shares the instruction bytes.
// (The ROM sign-extends the index byte; negative values are unreachable in normal
// flow and the array lookup below simply misses, matching a no-op.)
// ============================================================================

export function createSatelliteRootAction(
  ctx: SatelliteFamilyCtx,
): (actor: RomActor) => void {
  const dispatch = (
    table: Array<(actor: RomActor, ctx: SatelliteFamilyCtx) => void>,
  ) => (actor: RomActor) => {
    const fn = table[actor.fbPhaseSlots[0] ?? 0];
    if (fn) fn(actor, ctx);
  };
  // @0x80362658: [0]=0x80188b60 turret, [1]=0x80188da4 X engine, [2]=0x80188ec4 pods.
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    dispatch(TURRET_PHASE_TABLE), // 0: B burst turret  (routed only by pl0d05's types 0/1/3/4)
    dispatch(X_PHASE_TABLE),      // 1: X satellite deploy (BOTH families' types 2 AND 5)
    dispatch(POD_PHASE_TABLE),    // 2: B pod launcher  (routed only by pl0d01's types 0/1/3/4)
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned SATELLITE-family actor (pl0d01/pl0d05). Stamps the
 *  borg number the X phase-1 fork reads and wires the shared root dispatcher.
 *  Family init FUN_801889ec's cosmetic-child spawns (zz_00f846c_/zz_00f889c_) and
 *  the type-0x0e attachment (zz_00c74ec_(actor, 0x35)) are renderer-side and not
 *  ported; its latch clears (+0x145/+0x146/+0x147) are reproduced here. */
export function configureSatelliteFamily(
  actor: RomActor,
  borgId: "pl0d01" | "pl0d05",
  ctx: SatelliteFamilyCtx,
): void {
  actor.borgNumber = borgId === "pl0d01" ? 0x0d01 : 0x0d05;
  actor.rootAction = createSatelliteRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  // FUN_801889ec latch clears.
  const a = ext(actor);
  a.satDeployedLatch = 0;
  a.satPodLatch = [0, 0];
  a.satPodSide = 0;
}
