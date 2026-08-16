// Shared-engine GUN-VOLLEY machine (action 0) — 1:1 port of `zz_0177634_`
// @0x80177634 and its phase table `PTR_FUN_80352ae8` @0x80352ae8 =
// [0x80177684, 0x8017776c, 0x80177808, 0x80177900, 0x80177a8c, 0x80177b88,
//  0x80177c48, 0x80177d08]. The engine dispatches on +0x540 exactly like the
// charge-3 engine; the first 4 entries are THIS machine's phases (init / windup /
// fire / reload), while entries 4-7 point into the SAME code pool as the charge-3
// engine's phases 0-3 (PTR_FUN_80352af8) — unreachable here because phase 3 either
// rewinds to phase 1 (+0x540 -= 2) or exits via zz_006a668_. Exhaustive branch scan
// of `b/bl 0x80177634`: exactly two callers (the two family wrappers below).
// @audit-ported pl0619 action=0 variants=0,1,2,3,4
// @audit-ported pl061f action=0 variants=0,1,2,3,4
// @audit-ported pl0625 action=0 variants=0,1,2,3,4
//
// Distinct from the charge-3 machine (shared-charge3.ts): this is bound at ACTION
// INDEX 0 (the B volley), never morphs, its fire path is contact-gated (+0x1cef),
// the reload callback either rewinds to windup (keep firing) or exits, and the
// engine's exit helper is zz_006a668_(..., kind 4, ...) — the same kind-4 exit
// panther-vehicle.ts's exitMachine models.
//
// Families served (exhaustive `b 0x80177634` scan; config ptr loaded into r4 by the
// wrapper's lis/addi before the tail call):
//   Family 1 — ctor 0x80126e00, roster pl0619 TITAN TANK. Wrapper FUN_801271f8
//     (r4 = cfg @0x803303a4) → engine. actionTable @0x80330380, slot [0]
//     dispatcher FUN_801271b0 halves +0x18da (steerYaw) every dispatch, then routes
//     all 5 variants through PTR_FUN_80330390[+0x581] = 0x801271f8.
//   Family 2 — ctor 0x8015b420, roster pl061f + pl0625. Wrapper zz_015b814_
//     (r4 = cfg @0x80345bf8) → engine. actionTable @0x80345be8, slot [0]
//     dispatcher FUN_8015b7dc halves +0x18e0/+0x18e2 (charge meters) every dispatch,
//     then calls the engine wrapper directly.
//
// REGISTRATION NOTE: this file wires the families' actionTable[0] ONLY. Their action
// 3 is the charge-3 machine (separate ported module); the orchestrator composes both
// into one root action table.
//
// Config block layout (proven by the engine's r4-relative loads — lwz 0(r31)
// @0x80177730, lwz 4(r31) @0x80177acc, lwz 8(r31) @0x80177978, lwz c(r31) @0x8017793c,
// lwz 10(r31) @0x80177700/778; the s16 at +0x14 and u16 at +0x16 complete the block —
// verified by the next data block):
//   u32 +0x00 = group-2 stream slot (phase-0 start)
//   u32 +0x04 = group-2 stream slot (phase-3 reload restart)
//   ptr +0x08 = family fire callback (spawns the volley on the phase-2 contact)
//   ptr +0x0c = family reload callback (nonzero → rewind to windup; zero → exit)
//   ptr +0x10 = family aim callback (nonzero → turret aligned; called in every phase)
//   s16 +0x14 = ammo-seed float (loaded into +0x558; the reload timer)
//   u16 +0x16 = volley-count seed (loaded into +0x6ef; fam2 reload gates on it)
//
// FAMILY 1 cfg @0x803303a4 (DOL-read): slot0=0, slot1=0, fire=0x80127220,
//   reload=0x801272b0, aim=0x80127300, s16[+0x14]=16 (0x0010), u16[+0x16]=100
//   (0x0064). Fire callback FUN_80127220 gates on the weapon cell (consume),
//   borg-switches on +0x3e8, spawns zz_00c3be0_ pairs, and resets +0x558 = 16.0.
//   Reload FUN_801272b0: keep firing while B held (+0x5bc & 0x200) AND cell has
//   ammo. Aim FUN_80127300: two turret-pivot seeks; aligned when both pivots settle.
//
// FAMILY 2 cfg @0x80345bf8 (DOL-read): slot0=0, slot1=0, fire=0x8015b83c,
//   reload=0x8015b914, aim=0x8015b970, s16[+0x14]=4 (0x0004), u16[+0x16]=5
//   (0x0005). Fire FUN_8015b83c: borg-switch on +0x3e8 → zz_0082824_ pairs (shot
//   helper, +0x6ea = 4). Reload FUN_8015b914: keep firing while cell has ammo AND
//   +0x6ef >= 1. Aim FUN_8015b970: charge-meter seek + turret-pivot write.

import type { RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { allocateWeapon, toS16 } from "../rom/helpers.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { armWeaponPartAnimation, refreshTargetVisibility } from "./shared-aimed-shot-x.js";

/** Engine constants — every value read from boot.dol (all lfs r2-relative with
 *  r2=0x8043ea20). */
export const SHARED_GUN_X = {
  /** FLOAT_8043ae00 = 30.0 — phase-0 windup timer seed (+0x560). */
  WINDUP_TIME: 30.0,
  /** FLOAT_8043ae04 = -1.0 — zz_004beb8_ playback rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043ae10 = 0.0 — zero (timer expiry compare + +0x558 reset). */
  ZERO: 0.0,
  /** FLOAT_80439c90 = 16.0 — fam1 fire callback re-seeds +0x558 (the reload timer). */
  FAM1_FIRE_TIMER: 16.0,
  /** Stream group — immediate `li r5,2` @0x80177730 (GROUP 2, same as charge-3). */
  STREAM_GROUP: 2,
  /** Exit kind passed to zz_006a668_ by both phase-2 and phase-3 exits. */
  EXIT_KIND: 4,
  /** +0x5bc B-held status bit gating fam1's reload (the hold-to-fire arm). */
  B_HELD_BIT: 0x200,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
} as const;

/** Per-family config for the shared gun machine (the ROM's r4 config block). */
export interface SharedGunXConfig {
  /** cfg u32[0]: group-2 stream slot for the phase-0 start. */
  slot0: number;
  /** cfg u32[1]: group-2 stream slot for the phase-3 reload restart. */
  slot1: number;
  /** cfg ptr[+8]: family fire callback — spawned on the phase-2 contact, after the
   *  weapon-cell consume gate. */
  onFire: ((actor: RomActor, ctx: StreamContext) => void) | null;
  /** cfg ptr[+0xc]: family reload callback — nonzero keeps firing (rewind to windup
   *  + restart stream); zero exits the machine. */
  onReload: ((actor: RomActor, ctx: StreamContext) => number) | null;
  /** cfg ptr[+0x10]: family aim callback — nonzero means the turret is aligned. The
   *  ROM reads its return as a branch gate in phases 1/3 and discards it in 0/2. */
  onAim: ((actor: RomActor, ctx: StreamContext) => number) | null;
  /** cfg s16[+0x14]: ammo-seed float loaded into +0x558 (the reload timer). */
  ammoSeed: number;
  /** cfg u16[+0x16]: volley-count seed loaded into +0x6ef. */
  volleyCount: number;
}

/** Host-mirrored scratch. The ROM stores these at family-specific offsets; the actor
 *  runs one family at a time so named port-side mirrors suffice (the offsets are
 *  cited for audit). */
interface GunXScratch {
  /** +0x541: one-shot target-invalidate latch (phase 0 sets when the cell is empty). */
  gunLatch541?: number;
  /** +0x543: part mask (1, or 0xf when +0x5db == 1). */
  gunPartMask?: number;
  /** +0x6ef: volley count (decremented per fire; fam2 reload gates on >= 1). */
  gunVolleyCount?: number;
  /** +0x774: weapon-cell ammo-in-hand (host supplies; < 1 → target-invalidate). */
  gunAmmo774?: number;
  /** +0x5bc: live status word; bit 0x200 = B held (fam1 reload gate). */
  statusWord5bc?: number;
  /** +0x5d8: held input word; +0xf0 mask gates the phase-3 no-reload-callback exit. */
  inputHeld5d8?: number;
  /** +0x1cef: contact flag driving the phase-2 fire. */
  contactP0?: number;
  /** +0x1cee: wall/stream-contact flag ending the phase-3 stay. */
  wallContact?: number;
  /** +0x1b03: stream/animation hold byte gating the phase-1 stream tick. */
  streamHold1b03?: number;
  /** +0x1cee/+0x1cef/... host contact fields surfaced above. */
  contactP1?: number;
  /** fam1 +0x18da steerYaw (halved by the action-0 dispatcher every frame). */
  steerYaw?: number;
  /** fam2 +0x18e0/+0x18e2 charge meters (halved by the action-0 dispatcher). */
  chargeMeterA?: number;
  chargeMeterB?: number;
  /** fam1 turret-pivot yaw channels (+0x1962/+0x196e) written by the aim callback. */
  gunPivotL1962?: number;
  gunPivotR196e?: number;
  /** fam2 turret-pivot yaw channels (+0x1968/+0x1974). */
  gunPivotL1968?: number;
  gunPivotR1974?: number;
  /** +0x6ea: stream slot cursor (fam2 fire callback writes 4). */
  streamSlot?: number;
}

function scratchOf(actor: RomActor): GunXScratch {
  return actor as RomActor & GunXScratch;
}

// ============================================================================
// Phase 0 — FUN_80177684 @0x80177684. Init + windup timer + stream start.
// ============================================================================
function gunXPhase0(actor: RomActor, cfg: SharedGunXConfig, ctx: StreamContext): void {
  const s = scratchOf(actor);
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.stateTimer = SHARED_GUN_X.WINDUP_TIME;               // +0x560 = 30.0
  actor.handlerTimer = cfg.ammoSeed;                          // +0x558 = (float)s16 cfg[+0x14]
  s.gunVolleyCount = cfg.volleyCount;                         // +0x6ef = (u16)cfg[+0x16]

  // `if (+0x774 < 1) { +0x541 = 1; +0xcc = 0; }` — empty cell invalidates the target.
  if ((s.gunAmmo774 ?? 1) < 1) {
    s.gunLatch541 = 1;
  }

  if (cfg.onAim) cfg.onAim(actor, ctx); // aim callback (return discarded here)

  // +0x543 = 1 (part mask); +0x5db == 1 → 0xf (full part mask).
  s.gunPartMask = actor.ubState === 1 ? 0xf : 1;
  // zz_004beb8_(rate -1, actor, mask +0x543, GROUP 2, slot cfg[0], -1, -1).
  startStream(actor, s.gunPartMask, SHARED_GUN_X.STREAM_GROUP, cfg.slot0, SHARED_GUN_X.STREAM_RATE);
}

// ============================================================================
// Phase 1 — FUN_8017776c @0x8017776c. Windup countdown; advance on timer/aim.
// ============================================================================
function gunXPhase1(actor: RomActor, cfg: SharedGunXConfig, ctx: StreamContext): void {
  const s = scratchOf(actor);
  // `if (+0x1b03 != 0) zz_004cd24_(actor, +0x543);` — stream tick gated on the hold
  // byte. The port ticks unconditionally (labeled approximation, same class as the
  // charge-3 P1 — the windup timer still bounds the phase).
  tickStream(actor, s.gunPartMask ?? 1, ctx);

  // +0x560 -= dt (FLOAT_8043ae10 = 0.0 expiry compare).
  actor.stateTimer -= actor.dt;

  // Advance when timer expired OR the aim callback returns nonzero (turret aligned).
  if (actor.stateTimer <= SHARED_GUN_X.ZERO || (cfg.onAim !== null && cfg.onAim(actor, ctx) !== 0)) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  }
}

// ============================================================================
// Phase 2 — FUN_80177808 @0x80177808. Contact-gated fire + volley spawn.
// ============================================================================
function gunXPhase2(actor: RomActor, cfg: SharedGunXConfig, ctx: StreamContext): void {
  const s = scratchOf(actor);
  tickStream(actor, s.gunPartMask ?? 1, ctx); // zz_004cd24_(actor, +0x543)
  if (cfg.onAim) cfg.onAim(actor, ctx);        // aim callback (return discarded)

  // Fire only on the contact flag +0x1cef (stream-op-0x02-authored). Without
  // byte-loaded banks the flag is host-surfaced; the phase stays in windup->fire
  // until the bridge sets it (the same contact contract charge-3's P2 uses).
  if (s.contactP0 !== undefined && s.contactP0 > 0) {
    // Ammo cost gate: `zz_006dbe0_(actor, 0, 1, 0)` — peek. Fail → exit.
    if (!allocateWeapon(actor, ctx, 0, 1, false)) {
      gunXExit(actor);
      return;
    }
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    actor.handlerTimer = SHARED_GUN_X.ZERO;                    // +0x558 = 0
    s.gunVolleyCount = (s.gunVolleyCount ?? 0) - 1;            // +0x6ef--
    if (cfg.onFire) cfg.onFire(actor, ctx);                    // spawn the volley
    s.gunPartMask = actor.ubState === 1 ? 0xf : 1;             // +0x543 = 1 (or 0xf)
  }
}

// ============================================================================
// Phase 3 — FUN_80177900 @0x80177900. Reload timer; keep firing or exit.
// ============================================================================
function gunXPhase3(actor: RomActor, cfg: SharedGunXConfig, ctx: StreamContext): void {
  const s = scratchOf(actor);
  tickStream(actor, 1, ctx); // zz_004cd24_(actor, 1)

  if (actor.handlerTimer <= SHARED_GUN_X.ZERO) {
    // Reload callback: nonzero → rewind to windup + restart stream (keep firing);
    // zero → exit immediately (ROM `goto LAB_80177a04`, bypassing the stay check).
    if (cfg.onReload !== null) {
      if (cfg.onReload(actor, ctx) !== 0) {
        refreshTargetVisibility(actor); // zz_006bf80_
        actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) - 2; // +0x540 -= 2 → phase 1
        s.gunPartMask = actor.ubState === 1 ? 0xf : 1;            // +0x543 = 1 (or 0xf)
        startStream(actor, s.gunPartMask, SHARED_GUN_X.STREAM_GROUP, cfg.slot1, SHARED_GUN_X.STREAM_RATE);
        return;
      }
      gunXExit(actor);
      return;
    }
    // No reload callback: `if ((+0x5d8 & 0xf0) != 0) exit;` — held direction exits.
    if ((s.inputHeld5d8 ?? 0) & 0xf0) {
      gunXExit(actor);
      return;
    }
  } else {
    actor.handlerTimer -= actor.dt; // +0x558 -= dt
    if (cfg.onAim) cfg.onAim(actor, ctx);
  }

  // Stay while not in a wall/stream-end contact: `((-1 < +0x1cef) || (+0x5db == 1))
  // && (+0x1cee == 0)` → return (keep riding the reload loop); otherwise exit.
  const stay = ((s.contactP0 ?? 0) >= 0 || actor.ubState === 1) && (s.wallContact ?? 0) === 0;
  if (stay) return;
  gunXExit(actor);
}

/** zz_006a668_(..., kind 4, ...) — the shared exit helper (same as panther-vehicle's
 *  exitMachine): clear the shot channels, arm the exact weapon-part animation, and
 *  dispatch the current upper-body cue to full body. */
function gunXExit(actor: RomActor): void {
  actor.housekeeping73f = 0; // +0x73f = 0
  actor.controlWord &= ~SHARED_GUN_X.ACTION_MODE_BITS; // +0x5e0 &= ~3
  actor.shotScalar1d9c = 0;
  actor.shotByte1db2 = 0;
  actor.shotByte1db3 = 0;
  armWeaponPartAnimation(actor, SHARED_GUN_X.EXIT_KIND);
  dispatchFullBodyCue(actor, actor.ubCue);
}

/** Build the shared gun-voley handler for one family config — the port of the
 *  stage-2 wrapper + `zz_0177634_` dispatch (phase table PTR_FUN_80352ae8, phases
 *  0-3 only; entries 4-7 alias the charge-3 pool and are unreachable). Wire the
 *  result as actionTable[0] in the family's root action dispatcher. */
export function createSharedGunX(
  cfg: SharedGunXConfig,
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    // zz_0177634_ prologue: `if (+0x541 != 0) +0xcc = 0;` — target-invalidated flag
    // clears the lock pointer. The bridge owns target validity; not modeled here
    // (same treatment as shared-charge3.ts).
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: gunXPhase0(actor, cfg, ctx); break;
      case 1: gunXPhase1(actor, cfg, ctx); break;
      case 2: gunXPhase2(actor, cfg, ctx); break;
      case 3: gunXPhase3(actor, cfg, ctx); break;
      default: break;
    }
  };
}

// ============================================================================
// Aim callback pattern — the FAMILY_GUN cone+decay seek (same class as the
// panther-vehicle zz_006eae0_ approximation). The ROM's exact per-part pivot
// matrix reads (gnt4_PSVECSubtract/FUN_800452a0 yaw at chunk_0033.c:3976-4009 and
// chunk_0040.c:4568-4598) write renderer-side turret channels; the branch-relevant
// return (aligned vs not) is modeled here as "both channels converged within cone".
// ============================================================================

const GUN_AIM_CONE = 0x2000;   // ±0x2000 turret-pivot clamp (both families)
const GUN_AIM_STEP = 0x200;    // per-tick pivot seek step (TUNED; the exact
                                // desc-driven step is host-facing renderer state)

function seekTurretChannel(cur: number, targetYaw: number): number {
  const cone = toS16(targetYaw - cur);
  const delta = Math.max(-GUN_AIM_STEP, Math.min(GUN_AIM_STEP, cone));
  return toS16(cur + delta);
}

/** FAM1 aim FUN_80127300 — two turret-pivot seeks (zz_017a6e0_ + zz_017a884_ on
 *  +0x18e0/+0x18e2 pivots). Aligned when both settle → returns 0x8444. The yaw
 *  targets derive from the lock-target position (host lockTarget). PORT
 *  APPROXIMATION (labeled): the ROM's pivot-write block runs only when +0xcc (the
 *  lock pointer) is set — without a lock the windup timer is the sole advance gate,
 *  matching the branch-structure intent (the exact pivot-matrix reads are
 *  host-facing renderer state). */
export function family1GunXOnAim(actor: RomActor, ctx: StreamContext): number {
  const s = scratchOf(actor);
  const target = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
  if (!target) return 0; // no lock → windup timer governs (labeled approximation)
  const targetYaw = Math.round(
    (Math.atan2(actor.pos.x - target.x, actor.pos.z - target.z) / (Math.PI * 2)) * 0x10000,
  );
  const l = s.gunPivotL1962 ?? actor.heading;
  const r = s.gunPivotR196e ?? actor.heading;
  s.gunPivotL1962 = seekTurretChannel(l, targetYaw);
  s.gunPivotR196e = seekTurretChannel(r, targetYaw);
  void ctx;
  const aligned =
    Math.abs(toS16(s.gunPivotL1962 - targetYaw)) <= GUN_AIM_CONE &&
    Math.abs(toS16(s.gunPivotR196e - targetYaw)) <= GUN_AIM_CONE;
  return aligned ? 0x8444 : 0;
}

/** FAM2 aim FUN_8015b970 — charge-meter seek (zz_006eae0_(actor, &+0x1922,
 *  &+0x1926, 3)) + turret-pivot write (+0x1968/+0x1974). Aligned when the seek
 *  returns nonzero. PORT APPROXIMATION (labeled): the seek requires a lock target
 *  (+0xcc); without one the windup timer is the sole advance gate. */
export function family2GunXOnAim(actor: RomActor, ctx: StreamContext): number {
  const s = scratchOf(actor);
  const target = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
  if (!target) return 0; // no lock → windup timer governs (labeled approximation)
  const targetYaw = Math.round(
    (Math.atan2(actor.pos.x - target.x, actor.pos.z - target.z) / (Math.PI * 2)) * 0x10000,
  );
  s.chargeMeterA = seekTurretChannel(s.chargeMeterA ?? actor.heading, targetYaw);
  s.chargeMeterB = seekTurretChannel(s.chargeMeterB ?? actor.heading, targetYaw);
  s.gunPivotL1968 = seekTurretChannel(s.gunPivotL1968 ?? actor.heading, targetYaw);
  s.gunPivotR1974 = seekTurretChannel(s.gunPivotR1974 ?? actor.heading, targetYaw);
  void ctx;
  return 0x8444; // seek-complete contract (the windup timer bounds the phase)
}

// ============================================================================
// Family 1 — ctor 0x80126e00 (pl0619 TITAN TANK). Config @0x803303a4.
// ============================================================================

/** Effect spawner zz_00c3be0_ @0x800c3be0 — kind-2 effect child (+0x10 = 2,
 *  +0x11 = type). FAM1 fire FUN_80127220 spawns a pair per borg arm. */
export const FAMILY1_GUN_X = {
  EFFECT_SPAWNER: 0x800c3be0,
  CONFIG_ADDR: 0x803303a4,
  FIRE_CALLBACK_ADDR: 0x80127220,
  RELOAD_CALLBACK_ADDR: 0x801272b0,
  AIM_CALLBACK_ADDR: 0x80127300,
  /** zz_00c3be0_ type pairs by borg (+0x3e8). 0x605 arm is STATICALLY DEAD for this
   *  binding (roster = pl0619 only) — kept for the borg switch's fidelity. */
  VARIANTS: {
    0x605: [0x23, 0x24], // dead arm (unconditional pair)
    0x619: [0x4f, 0x50], // pl0619 — zz_006dbe0_(0,1,1) cost-gated pair
  } as Record<number, readonly [number, number]>,
} as const;

/** FAM1 fire callback FUN_80127220 @0x80127220 (cfg+8): weapon-cell cost gate
 *  (consume), then the borg-switched zz_00c3be0_ pair, then +0x558 = 16.0 (the reload
 *  timer re-seed). PORT APPROXIMATION (labeled): the cost gate is modeled via
 *  allocateWeapon (consume), same as the tank modules. */
export function family1GunXOnFire(actor: RomActor, ctx: StreamContext): void {
  if (!allocateWeapon(actor, ctx, 0, 1, true)) return;
  const pair = FAMILY1_GUN_X.VARIANTS[actor.borgNumber];
  if (pair) {
    ctx.onFamilyProjectile?.(actor, FAMILY1_GUN_X.EFFECT_SPAWNER, pair[0]);
    ctx.onFamilyProjectile?.(actor, FAMILY1_GUN_X.EFFECT_SPAWNER, pair[1]);
  }
  actor.handlerTimer = SHARED_GUN_X.FAM1_FIRE_TIMER; // +0x558 = 16.0
}

/** FAM1 reload callback FUN_801272b0 @0x801272b0 (cfg+0xc): keep firing while B held
 *  (+0x5bc & 0x200) AND the weapon cell has ammo (peek). Returns 0x8444 / 0. */
export function family1GunXOnReload(actor: RomActor, ctx: StreamContext): number {
  const held = ((scratchOf(actor).statusWord5bc ?? 0) & SHARED_GUN_X.B_HELD_BIT) !== 0;
  return held && allocateWeapon(actor, ctx, 0, 1, false) ? 0x8444 : 0;
}

/** Family 1 config @0x803303a4 (DOL-read: slot0=0, slot1=0, fire=0x80127220,
 *  reload=0x801272b0, aim=0x80127300, s16[+0x14]=0x0010=16, u16[+0x16]=0x0064=100). */
export const FAMILY1_GUN_X_CONFIG: SharedGunXConfig = {
  slot0: 0,
  slot1: 0,
  onFire: family1GunXOnFire,
  onReload: family1GunXOnReload,
  onAim: family1GunXOnAim,
  ammoSeed: 16,   // cfg s16[+0x14]
  volleyCount: 100, // cfg u16[+0x16]
};

/** Action-0 handler for pl0619 — the port of the action-0 dispatcher FUN_801271b0
 *  (per-tick +0x18da >>= 1) + the stage-2 wrapper FUN_801271f8 (cfg bind) + engine.
 *  Wire as actionTable[0] of the family root dispatcher FUN_80127174 (table
 *  @0x80330380; slot [3] is the charge-3 machine, ported separately). */
export function createFamily1GunXAction(ctx: StreamContext): (actor: RomActor) => void {
  const engine = createSharedGunX(FAMILY1_GUN_X_CONFIG, ctx);
  return (actor: RomActor) => {
    const s = scratchOf(actor);
    s.steerYaw = toS16(s.steerYaw ?? 0) >> 1; // FUN_801271b0: +0x18da >>= 1 (every frame)
    engine(actor);
  };
}

// ============================================================================
// Family 2 — ctor 0x8015b420 (pl061f + pl0625). Config @0x80345bf8.
// ============================================================================

/** Shot helper zz_0082824_ @0x80082824 — the family shot spawner (same helper the
 *  gatling/beam/icbm tanks use). FAM2 fire FUN_8015b83c spawns a pair per borg arm. */
export const FAMILY2_GUN_X = {
  SHOT_HELPER: 0x80082824,
  CONFIG_ADDR: 0x80345bf8,
  FIRE_CALLBACK_ADDR: 0x8015b83c,
  RELOAD_CALLBACK_ADDR: 0x8015b914,
  AIM_CALLBACK_ADDR: 0x8015b970,
  /** zz_0082824_ kindIdx pairs by borg (+0x3e8). 0x611 and 0x622 arms are STATICALLY
   *  DEAD for this binding (roster = pl061f + pl0625 only) — kept for the borg
   *  switch's fidelity. */
  VARIANTS: {
    0x611: [0x30, 0x31], // dead arm (unconditional pair)
    0x61f: [0x57, 0x58], // pl061f — zz_006dbe0_(0,1,1) cost-gated pair
    0x622: [0x59, 0x5a], // dead arm (unconditional pair)
    0x625: [0x5b, 0x5c], // pl0625 — zz_006dbe0_(0,1,1) cost-gated pair
  } as Record<number, readonly [number, number]>,
} as const;

/** FAM2 fire callback FUN_8015b83c @0x8015b83c (cfg+8): weapon-cell cost gate
 *  (consume), then the borg-switched zz_0082824_ pair, then +0x6ea = 4. PORT
 *  APPROXIMATION (labeled): the cost gate is modeled via allocateWeapon. */
export function family2GunXOnFire(actor: RomActor, ctx: StreamContext): void {
  if (!allocateWeapon(actor, ctx, 0, 1, true)) return;
  const pair = FAMILY2_GUN_X.VARIANTS[actor.borgNumber];
  if (pair) {
    ctx.onFamilyProjectile?.(actor, FAMILY2_GUN_X.SHOT_HELPER, pair[0]);
    ctx.onFamilyProjectile?.(actor, FAMILY2_GUN_X.SHOT_HELPER, pair[1]);
  }
  scratchOf(actor).streamSlot = 4; // +0x6ea = 4
}

/** FAM2 reload callback FUN_8015b914 @0x8015b914 (cfg+0xc): keep firing while the
 *  weapon cell has ammo (peek) AND the +0x6ef volley count remains. Returns 0x8444. */
export function family2GunXOnReload(actor: RomActor, ctx: StreamContext): number {
  const volley = (scratchOf(actor).gunVolleyCount ?? 0) >= 1;
  return volley && allocateWeapon(actor, ctx, 0, 1, false) ? 0x8444 : 0;
}

/** Family 2 config @0x80345bf8 (DOL-read: slot0=0, slot1=0, fire=0x8015b83c,
 *  reload=0x8015b914, aim=0x8015b970, s16[+0x14]=0x0004=4, u16[+0x16]=0x0005=5). */
export const FAMILY2_GUN_X_CONFIG: SharedGunXConfig = {
  slot0: 0,
  slot1: 0,
  onFire: family2GunXOnFire,
  onReload: family2GunXOnReload,
  onAim: family2GunXOnAim,
  ammoSeed: 4,  // cfg s16[+0x14]
  volleyCount: 5, // cfg u16[+0x16]
};

/** Action-0 handler for pl061f/pl0625 — the port of the action-0 dispatcher
 *  FUN_8015b7dc (per-tick +0x18e0/+0x18e2 >>= 1) + the stage-2 wrapper zz_015b814_
 *  (cfg bind) + engine. Wire as actionTable[0] of the family root dispatcher
 *  FUN_8015b7a0 (table @0x80345be8; slot [3] is the charge-3 machine, ported
 *  separately). */
export function createFamily2GunXAction(ctx: StreamContext): (actor: RomActor) => void {
  const engine = createSharedGunX(FAMILY2_GUN_X_CONFIG, ctx);
  return (actor: RomActor) => {
    const s = scratchOf(actor);
    s.chargeMeterA = toS16(s.chargeMeterA ?? 0) >> 1; // FUN_8015b7dc: +0x18e0 >>= 1
    s.chargeMeterB = toS16(s.chargeMeterB ?? 0) >> 1; // FUN_8015b7dc: +0x18e2 >>= 1
    engine(actor);
  };
}

// ============================================================================
// Self-tests — mirror the panther-vehicle / beam-tank style.
// ============================================================================

function makeTestActor(): RomActor & GunXScratch & { lockTarget?: { x: number; y: number; z: number } | null } {
  return {
    borgNumber: 0,
    fbPhaseSlots: [0, 0, 0, 0],
    actionIndex: 0,
    variantIndex: 0,
    controlWord: 0x3,
    stateTimer: 0,
    handlerTimer: 0,
    dt: 1,
    ubState: 0,
    housekeeping73f: 0,
    shotScalar1d9c: 0,
    shotByte1db2: 0,
    shotByte1db3: 0,
    heading: 0,
    lockYaw: 0,
    activeYaw: 0,
    steerYaw: 0,
    pos: { x: 0, y: 0, z: 0 },
    motion: { x: 0, y: 0, z: 0 },
    parts: [
      { streamPtr: -1, frameClock: 0, prevTarget: 0, curTarget: 0, animTime: 0, active: 0, stateByte: 0 },
      { streamPtr: -1, frameClock: 0, prevTarget: 0, curTarget: 0, animTime: 0, active: 0, stateByte: 0 },
      { streamPtr: -1, frameClock: 0, prevTarget: 0, curTarget: 0, animTime: 0, active: 0, stateByte: 0 },
      { streamPtr: -1, frameClock: 0, prevTarget: 0, curTarget: 0, animTime: 0, active: 0, stateByte: 0 },
    ],
    ubCue: 0,
    fbCue: 0,
    visibilityBit: 0,
    visibilityRoster: [],
    visibilityTarget: null,
  } as unknown as RomActor & GunXScratch & { lockTarget?: { x: number; y: number; z: number } | null };
}

type AssertFn = (cond: boolean, msg: string) => void;

export function runSharedGunXSelfTests(assert: AssertFn): void {
  console.log("\n[shared-gun-x.selfcheck] pl0619 TITAN TANK action 0 — gun volley:");

  {
    // Phase 0 init → phase 1; windup 30.0; no target → aim converges to heading.
    const shots: Array<{ addr: number; type: number }> = [];
    const ctx: StreamContext = {
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
      onAllocateResource: () => true,
    };
    const a = makeTestActor();
    a.borgNumber = 0x619;
    const root = createFamily1GunXAction(ctx);
    root(a);
    assert(a.fbPhaseSlots[0] === 1, "phase 0 advances to phase 1");
    assert(a.stateTimer === 30.0, "phase 0 seeds windup timer 30.0");
    assert(a.handlerTimer === 16, "phase 0 seeds +0x558 = ammoSeed 16");
    assert(shots.length === 0, "no fire before contact");

    // Windup: with no target, the aim callback returns 0 (no lock) so the 30.0
    // windup timer is the sole gate.
    for (let i = 0; i < 29; i += 1) root(a);
    assert(a.fbPhaseSlots[0] === 1, "windup holds before timer expiry");
    root(a); // 30th tick → timer <= 0 → phase 2
    assert(a.fbPhaseSlots[0] === 2, "windup advances to fire on timer expiry");

    // Fire: contact not set → no volley, stays in phase 2.
    root(a);
    assert(shots.length === 0, "fire waits for contact flag");
    assert(a.fbPhaseSlots[0] === 2, "fire holds without contact");

    // Fire: contact set → ammo gate passes → volley spawns (0x4f/0x50), +0x6ef--,
    // +0x558 = 16.0 (fire-callback re-seed), advance to phase 3.
    a.contactP0 = 1;
    root(a);
    assert(a.fbPhaseSlots[0] === 3, "fire advances to reload on contact");
    assert(shots.length === 2, "fam1 fire spawns the 0x4f/0x50 pair");
    assert(shots[0]!.addr === FAMILY1_GUN_X.EFFECT_SPAWNER && shots[0]!.type === 0x4f,
      "fam1 volley[0] = EFFECT_SPAWNER type 0x4f");
    assert(shots[1]!.addr === FAMILY1_GUN_X.EFFECT_SPAWNER && shots[1]!.type === 0x50,
      "fam1 volley[1] = EFFECT_SPAWNER type 0x50");
    assert(a.gunVolleyCount === 99, "fire decrements +0x6ef");
    assert(a.handlerTimer === 16.0, "fam1 fire re-seeds +0x558 = 16.0");

    // Reload: B held → after +0x558 drains (16 ticks from the 16.0 re-seed) the
    // reload callback rewinds to phase 1 (keep firing). The windup timer is NOT
    // re-seeded on rewind (the ROM only seeds +0x560 in phase 0), so the next
    // windup advances immediately.
    a.statusWord5bc = 0x200;
    for (let i = 0; i < 16; i += 1) root(a); // +0x558 16 → 0, still phase 3
    assert(a.fbPhaseSlots[0] === 3, "reload drains +0x558 in phase 3");
    root(a); // +0x558 == 0 → reload callback (B held) → rewind to phase 1
    assert(a.fbPhaseSlots[0] === 1, "fam1 reload with B held rewinds to windup");
    // Windup re-entry: stateTimer already drained → immediate advance to fire.
    root(a);
    assert(a.fbPhaseSlots[0] === 2, "second windup (drained timer) advances to fire");
    root(a); // fire again (contact set) → 2 more shots
    assert(shots.length === 4, "second volley spawns 2 more shots");

    // Release B → reload callback returns 0 → immediate exit (kind-4 control bits
    // stripped; does NOT re-ride the stay check).
    a.statusWord5bc = 0;
    for (let i = 0; i < 16; i += 1) root(a); // +0x558 16 → 0
    root(a); // +0x558 == 0 → reload callback (0) → exit
    assert((a.controlWord & SHARED_GUN_X.ACTION_MODE_BITS) === 0, "reload-denied exit strips action bits");
  }

  console.log("\n[shared-gun-x.selfcheck] pl061f/pl0625 action 0 — gun volley:");

  {
    const shots: Array<{ addr: number; type: number }> = [];
    const ctx: StreamContext = {
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
      onAllocateResource: () => true,
    };
    const a = makeTestActor();
    a.borgNumber = 0x61f;
    const root = createFamily2GunXAction(ctx);
    root(a);
    assert(a.fbPhaseSlots[0] === 1 && a.stateTimer === 30.0, "fam2 phase 0 init");
    assert(a.handlerTimer === 4, "fam2 +0x558 = ammoSeed 4");

    for (let i = 0; i < 30; i += 1) root(a);
    assert(a.fbPhaseSlots[0] === 2, "fam2 windup reaches fire");
    a.contactP0 = 1;
    root(a);
    assert(shots.length === 2, "fam2 fire spawns the 0x57/0x58 pair");
    assert(shots[0]!.addr === FAMILY2_GUN_X.SHOT_HELPER && shots[0]!.type === 0x57,
      "fam2 volley[0] = SHOT_HELPER kind 0x57");
    assert(a.streamSlot === 4, "fam2 fire sets +0x6ea = 4");
    assert(a.gunVolleyCount === 4, "fam2 fire decrements +0x6ef");
    // fam2's fire callback does NOT re-seed +0x558 (it stays 0) → the reload callback
    // is consulted on the very next tick.
    root(a); // +0x558 == 0 → onReload (volley 4 >= 1) → rewind to windup
    assert(a.fbPhaseSlots[0] === 1, "fam2 reload with volley rewinds to windup");
    assert(a.handlerTimer === 0, "fam2 +0x558 stays 0 across the reload rewind");

    // Drain the volley count. The rewind enters phase 1 with the windup timer already
    // drained, so each further cycle is: windup (1 tick) → fire → reload-rewind.
    // Volley goes 4 → 0 across 4 more fires; the LAST reload (volley 0) exits.
    for (let cycle = 0; cycle < 3; cycle += 1) {
      root(a); // windup re-entry (drained timer) → advance to fire
      assert(a.fbPhaseSlots[0] === 2, "fam2 windup advances to fire (cycle " + cycle + ")");
      root(a); // fire → +0x6ef-- → phase 3
      assert(a.fbPhaseSlots[0] === 3, "fam2 fire reaches reload (cycle " + cycle + ")");
      root(a); // +0x558 == 0 → onReload → rewind
      assert(a.fbPhaseSlots[0] === 1, "fam2 reload rewinds (cycle " + cycle + ")");
    }
    assert((a.gunVolleyCount ?? 0) === 1, "fam2 +0x6ef = 1 before the final fire");
    // Final fire: volley 1 → 0; the reload then denies → exit.
    root(a); // windup (drained timer) → fire
    assert(a.fbPhaseSlots[0] === 2, "fam2 final windup advances to fire");
    root(a); // fire → volley 0 → phase 3
    assert((a.gunVolleyCount ?? 0) === 0, "fam2 volley exhausted at phase 3");
    root(a); // +0x558 == 0 → onReload (volley 0) → exit
    assert((a.controlWord & SHARED_GUN_X.ACTION_MODE_BITS) === 0, "fam2 volley-exhausted exit strips action bits");
  }
}
