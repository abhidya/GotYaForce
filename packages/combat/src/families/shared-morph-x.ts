// Shared-engine MORPH/TRANSFORM X-special machine — 1:1 port of `zz_017a374_`
// @0x8017a374 and its 2-entry phase table @0x804347b0 = [0x8017a3ac, 0x8017a4a8].
// Third shared machine after zz_00ff2bc_ (shared-x-special.ts) and zz_00fed6c_
// (shared-melee-lunge.ts).
//
// This is the Machine-Borg line's TRANSFORM: the borg blinks away from its lock
// target (phase 0), plays the transform stream, and on stream end (phase 1) SWAPS
// ITS BORG NUMBER (+0x3e8) to the config's target form via zz_006a8c0_, wipes the
// line's fifteen gun-state accumulators (zz_017a608_) + re-inits weapon/ammo from
// the new form's descriptor (FUN_800562b8), then exits via upper-body cue 0x1b
// (when morphing into the flight/vehicle form), ground idle, or air-fall.
//
// Dispatch shape (raw disasm 0x8017a374-0x8017a3a8): bare `lbz +0x540 / lwzx /
// bctrl` with NO +0x541 prologue (unlike zz_00ff2bc_); r3=actor and r4=config flow
// into every phase function (Ghidra's decomp dropped both args at the dispatcher/
// wrapper level only — the phase decomps retain param_2).
//
// Config block: 12 bytes, stride 0xc (proven by the back-to-back sibling blocks
// 0x80344878/+0xc/+0x18 and 0x80345c10/+0xc/+0x18):
//   s8  +0x00 = groundSlot      (group-4 stream slot when grounded; lbz @0x8017a44c)
//   s8  +0x01 = airSlot         (lbz @0x8017a484)
//   s16 +0x02 = groundForm      (→ +0x548 pending form when grounded; lha @0x8017a42c)
//   s16 +0x04 = airForm         (→ +0x548 when airborne; lha @0x8017a464)
//   s16 +0x06 = flightExitForm  (lha @0x8017a5b4; 0xffff = -1 never; morph target ==
//                                this → exit via upper-body cue 0x1b)
//   f32 +0x08 = repositionScale (lfs @0x8017a3e8 + @0x8017a544; 0x3f7ae148 = 0.98
//                                in ALL nine ROM blocks)
// Data-only — no callback pointer field (unlike zz_00ff2bc_'s config).
//
// Source: scratchpad wav-eng-8017a374.json — 20/20 claims adversarially verified
// twice (all CONFIRMED). Verifier corrections applied here:
//   * DEAD ARGUMENT: the engine loads r5 = +0x3ec before `bl zz_006a8c0_`
//     (@0x8017a58c) but the callee never reads it — it reloads +0x3ec itself
//     (@0x8006a958). The port's morph therefore takes NO playerSlot parameter.
//   * +0x1cee NAMING CONFLICT: actor.ts:169 documents +0x1cee as `wallContact`
//     (G Crash phase 3), shared-melee-lunge.ts calls the same byte "stream end".
//     This engine gates the morph on +0x1cee as the STREAM-END event byte; both
//     names cover one stream/part event channel — see the phase-1 comment.
//   * CUE-27 NO-FALLBACK: when the morph target equals flightExitForm the ROM
//     calls zz_006a750_(actor, 0x1b) and dispatches NOTHING ELSE — if the family's
//     cue table row 27 is -1 the helper returns 0 and no exit fires at all (the
//     bne skips the idle/air-fall arms). The port preserves that exactly.
//
// NEGATIVE FINDINGS (verified absent from 0x8017a374-0x8017a604): the shared
// engine writes NO timers (+0x558/+0x560), NO +0x694 cooldown, and tests NO
// +0x1cef/+0x1d0f/+0x1d10 — those belong to the pl061a bespoke machine only.
// Phase 0 also does NOT zero the +0x44..+0x50 velocity scalars (unlike zz_00ff2bc_).
//
// Families covered by this module's configs (missing from the registry):
//   TITAN   ctor 0x80125a28 — pl0604 TITAN ROBOT + pl0618 PROTO TITAN → form 0x605
//   EAGLE   ctor 0x80129608 — pl0606 EAGLE ROBOT ONLY → form 0x607 (pl061a PROTO
//           EAGLE takes the != 0x606 branch FUN_8012a50c: a BESPOKE 4-phase gun
//           machine with its own phase table @0x803319ec — EXCLUDED, see caveats)
//   PANTHER ctor 0x8018c2b0 — pl0613 PANTHER ROBOT + pl0627 PROTO PANTHER → 0x614
//   VEHICLE ctor 0x8015b420 — pl0625 VICTORY MACHINE → form 0x626 (pl061f VICTORY
//           TANK has NO branch in FUN_8015bb44 — X dead at this layer, excluded);
//           the runtime forms 0x611/0x622 (morph-back configs 0x80345c10/0x80345c1c)
//           are exported for the day the host can instantiate alt-form actors.
// VICTORY KING (ctor 0x8015a494, pl0610/pl061e/pl0621/pl0623) is already served by
// bridge.ts — not re-registered here.
//
// HOST RESIDUAL: the morph targets (0x605/0x607/0x612/0x614/0x622/0x624/0x626 and
// 0x610/0x611 round-trips) are borg ids with NO borgs.json entries (non-selectable
// vehicle forms), and the renderer does not hot-swap models yet. The port performs
// the ROM-faithful state swap (borg number, form counter, gun-state wipe) and
// surfaces the new form id via `actor.morphFormId` + the optional `onMorph` hook;
// the visual/model swap and the FUN_800562b8 descriptor re-copy are host-side.

import type { RomActor } from "../rom/actor.js";
import {
  dispatchUpperBodyCue,
  dispatchFullBodyCue,
} from "../rom/dispatch.js";
import { vecSubtract, vecScale, vecAdd } from "../rom/physics.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

/** Machine constants — every value read from boot.dol (wav-eng-8017a374 dig). */
export const SHARED_MORPH_X = {
  /** FLOAT_8043ae04 (0xbf800000) = -1.0 — group-4 stream playback rate
   *  (lfs -0x3c1c(r2), r2=0x8043ea20; zz_004beb8_ param_1). */
  STREAM_RATE: -1.0,
  /** FLOAT_8043ae30 (0x3f666666) = 0.9 — phase-1 per-tick gun-state decay applied
   *  to +0x1d64/+0x1d68 (fctiwz-truncated). DOUBLE_8043ae08 (0x43300000_80000000)
   *  is only the PPC s16→double conversion magic, NOT a gameplay constant. */
  GUNSTATE_DECAY: 0.9,
  /** zz_00f036c_(actor, 0xb2) — SFX id 178 played at the morph windup (li r4,0xb2
   *  @0x8017a408). Routed via ctx.onPlayCue (the zz_00f036c_ port hook). */
  MORPH_SFX: 0xb2,
  /** zz_00660c8_(actor, 0xff) — chain-cancel mask clear (+0x57a/+0x57b &= ~0xff).
   *  Those bytes are not surfaced on RomActor; documented no-op (see phase 0). */
  CHAIN_CANCEL_CLEAR_MASK: 0xff,
  /** Upper-body cue 27 — the flight/vehicle-pose exit (li r4,0x1b @0x8017a5c4).
   *  Fired when the morph target equals cfg.flightExitForm. */
  FLIGHT_EXIT_CUE: 0x1b,
  /** All morph streams are group 4 (zz_004beb8_ r5=4), part mask 0xf. */
  STREAM_GROUP: 4,
  PART_MASK: 0xf,
} as const;

/** Per-family config for the shared morph machine (the ROM's r4 config block). */
export interface SharedMorphXConfig {
  /** cfg s8 +0x00: group-4 stream slot used when grounded. */
  groundSlot: number;
  /** cfg s8 +0x01: group-4 stream slot used when airborne. */
  airSlot: number;
  /** cfg s16 +0x02: borg id morphed into when the X fires grounded (→ +0x548). */
  groundForm: number;
  /** cfg s16 +0x04: borg id morphed into when the X fires airborne. */
  airForm: number;
  /** cfg s16 +0x06: -1 = never; when the morph target equals this, the exit is
   *  dispatchUpperBodyCue(actor, 0x1b) INSTEAD of ground-idle/air-fall (and if the
   *  cue-table row 27 is -1 the ROM dispatches nothing at all — preserved). */
  flightExitForm: number;
  /** cfg f32 +0x08: blink-away reposition scale (0.98 in all nine ROM blocks). */
  repositionScale: number;
  /** Wrapper-side pre-engine work, run EVERY frame BEFORE the phase dispatch —
   *  only the VEHICLE family (ctor 0x8015b420) has any: its wrappers halve gun-heat
   *  fields before `bl zz_017a374_` (raw disasm 0x8015bba4-0x8015bbb8 etc.). */
  preEngine?: (actor: RomActor) => void;
}

/** Port-side host hooks (beyond StreamContext). The ROM has no config callback —
 *  these exist because the model/descriptor swap lives host-side. */
export interface SharedMorphXHooks {
  /** Fired at the morph transition AFTER the actor-state swap (borg number, form
   *  counter, gun-state wipe). The host should re-skin/re-descriptor the actor —
   *  the zz_0056ce0_ + FUN_800562b8 residual (model swap, weapon/ammo re-init from
   *  the NEW form's descriptor +0x4ac fields, ammo blocks from PTR_DAT_802f2988).
   *  The renderer does not hot-swap models yet, so until then this is where a host
   *  logs/queues the pending visual change. */
  onMorph?: (actor: RomActor, newBorgId: number, previousBorgId: number) => void;
}

/** Port-side scratch fields stamped onto the actor (offsets labeled). */
interface MorphScratch {
  lockTarget?: { x: number; y: number; z: number } | null;
  grounded?: boolean;
  /** +0x548: pending morph-target form id (s16), written by phase 0. */
  morphPendingForm?: number;
  /** +0x3f0: form-change counter (zz_006a8c0_ increments it every morph). */
  morphFormCount?: number;
  /** Labeled surface for the host: the borg id this actor most recently morphed
   *  into (mirrors +0x3e8 after the swap; the PORT-side visual swap is a host
   *  residual — renderer doesn't hot-swap models yet). */
  morphFormId?: number;
  // The pl06xx line's u16 gun-state accumulators (semantics LIKELY heat/spread/
  // recoil-style per GUNSTATE-FIELD-SEMANTICS; the ops on them are DERIVED).
  // +0x18da is actor.steerYaw (reused scratch — see the phase-1 comment).
  gun197a?: number; gun1976?: number;
  gun1d64?: number; gun1d68?: number;
  gun1974?: number; gun1970?: number;
  gun1968?: number; gun1964?: number;
  gun1926?: number; gun1922?: number;
  gun196e?: number; gun1962?: number;
  gun18e0?: number; gun18e2?: number;
}

/** s16 reinterpret (the lha load the ROM uses on every gun-state field). */
function toS16(v: number): number {
  let s = v & 0xffff;
  if (s & 0x8000) s -= 0x10000;
  return s;
}

/** lha / srawi 1 / sth — the ROM's per-field halving primitive. */
function halveS16(v: number): number {
  return toS16(v) >> 1;
}

/** VEHICLE wrapper zz_015bb90_ (borg 0x611) pre-engine work: halve +0x1922 and
 *  +0x1926 (raw disasm 0x8015bba4-0x8015bbb8) before the engine call. Exported for
 *  the day the host can instantiate the 0x611 runtime form. */
export function halveGunHeat1922(actor: RomActor): void {
  const s = actor as RomActor & MorphScratch;
  s.gun1922 = halveS16(s.gun1922 ?? 0);
  s.gun1926 = halveS16(s.gun1926 ?? 0);
}

/** VEHICLE wrappers zz_015bbd0_ (0x622) / zz_015bc10_ (0x625) pre-engine work:
 *  halve +0x18e0 and +0x18e2 before the engine call. */
export function halveGunHeat18e0(actor: RomActor): void {
  const s = actor as RomActor & MorphScratch;
  s.gun18e0 = halveS16(s.gun18e0 ?? 0);
  s.gun18e2 = halveS16(s.gun18e2 ?? 0);
}

/** The lock-target position the phase handlers read at actor+0x5e8 (bridge-synced). */
function lockTargetPos(actor: RomActor): { x: number; y: number; z: number } | null {
  const t = (actor as RomActor & MorphScratch).lockTarget;
  return t ?? null;
}

/** Grounded test — the engine branches on zz_00677b0_'s (ground check/snap) nonzero
 *  return. The bridge mirrors BorgRuntime.grounded onto the actor. */
function isGrounded(actor: RomActor): boolean {
  const grounded = (actor as RomActor & MorphScratch).grounded;
  if (typeof grounded === "boolean") return grounded;
  return (actor.controlWord & 0x40) === 0; // fallback: air control bit clear
}

// ============================================================================
// Phase 0 — 0x8017a3ac. Windup: blink-away + SFX + slot/form select + stream start.
// ============================================================================
function morphXPhase0(actor: RomActor, cfg: SharedMorphXConfig, ctx: StreamContext): void {
  actor.fbPhaseSlots[0] = 1; // +0x540++ (lbz/addi/stb @0x8017a3d8-dc)

  // Blink-away reposition: motion(+0x38) = pos(+0x20) − lockTargetPos(+0x5e8) via
  // PSVECSubtract; motion ×= cfg.repositionScale (lfs 8(r31) @0x8017a3e8 — 0.98,
  // NOT the shared-x machine's 0.95); pos += motion via PSVECAdd. NOTE the negative
  // finding: unlike zz_00ff2bc_, this machine does NOT zero +0x44..+0x50 here.
  // Port approximation: skipped when no lock target is synced (the ROM would use
  // whatever +0x5e8 holds; the bridge only populates it while locked).
  const target = lockTargetPos(actor);
  if (target) {
    vecSubtract(actor.pos, target, actor.motion);
    vecScale(cfg.repositionScale, actor.motion, actor.motion);
    vecAdd(actor.pos, actor.motion, actor.pos);
  }

  // zz_00f036c_(actor, 0xb2) — morph-windup SFX (li r4,0xb2 @0x8017a408).
  ctx.onPlayCue?.(actor, SHARED_MORPH_X.MORPH_SFX);

  // zz_00660c8_(actor, 0xff) — clear both chain-cancel masks (+0x57a/+0x57b &= ~0xff).
  // Those bytes aren't surfaced on RomActor (no ported consumer yet) — documented no-op.

  // zz_00677b0_ ground check (beq @0x8017a428) selects the pending form + stream slot:
  //   GROUNDED: +0x548 = cfg s16@+2, slot = cfg s8@+0, +0x709 = 1
  //   AIRBORNE: +0x548 = cfg s16@+4, slot = cfg s8@+1 (no +0x709 write)
  // +0x709 (contact-slow flag) isn't surfaced on RomActor — documented no-op.
  const grounded = isGrounded(actor);
  const scratch = actor as RomActor & MorphScratch;
  scratch.morphPendingForm = grounded ? cfg.groundForm : cfg.airForm;
  const slot = grounded ? cfg.groundSlot : cfg.airSlot;

  // zz_004beb8_(rate -1.0 [FLOAT_8043ae04], actor, partMask 0xf, group 4, slot, -1, -1)
  startStream(actor, SHARED_MORPH_X.PART_MASK, SHARED_MORPH_X.STREAM_GROUP, slot,
    SHARED_MORPH_X.STREAM_RATE);
  actor.handlerTimer = 0; // port-side stream-end budget (NOT a ROM write — see phase 1)
}

// ============================================================================
// Phase 1 — 0x8017a4a8. Gun-state decay + stream tick + morph on stream end + exit.
// ============================================================================
function morphXPhase1(
  actor: RomActor,
  cfg: SharedMorphXConfig,
  ctx: StreamContext,
  hooks: SharedMorphXHooks,
): void {
  const scratch = actor as RomActor & MorphScratch;

  // (a) Gun-state decay every tick:
  //   +0x18da >>= 1 (lha/srawi 1/sth @0x8017a4d8-e4). +0x18da is actor.steerYaw —
  //   actor.ts documents it as G Crash's phase-2 steering yaw; per the verified
  //   GUNSTATE-FIELD-SEMANTICS claim the pl06xx line reuses the same scratch block
  //   as a gun-state accumulator, so this machine just halves it.
  actor.steerYaw = halveS16(actor.steerYaw);
  //   +0x1d64 = truncTowardZero(f32(+0x1d64) × 0.9) and +0x1d68 likewise
  //   (fmuls by FLOAT_8043ae30 = 0.9; fctiwz = truncation toward zero).
  scratch.gun1d64 = Math.trunc(toS16(scratch.gun1d64 ?? 0) * SHARED_MORPH_X.GUNSTATE_DECAY);
  scratch.gun1d68 = Math.trunc(toS16(scratch.gun1d68 ?? 0) * SHARED_MORPH_X.GUNSTATE_DECAY);

  // (b) zz_004cd24_(actor, 0xf) — tick the transform stream.
  tickStream(actor, SHARED_MORPH_X.PART_MASK, ctx);

  // (c) Reposition continuation: motion ×= cfg.repositionScale (lfs 8(r31)
  // @0x8017a544); pos += motion (decaying slide-away).
  vecScale(cfg.repositionScale, actor.motion, actor.motion);
  vecAdd(actor.pos, actor.motion, actor.pos);

  // (d) zz_00677b0_ ground check; if grounded → +0x709 = 1 (flag not surfaced —
  // documented no-op, same as phase 0).
  const grounded = isGrounded(actor);

  // (e) MORPH TRANSITION on s8 +0x1cee != 0 (lbz/extsb. @0x8017a578 — the STREAM-END
  // event byte, NOT the +0x1cef contact byte; the engine never tests +0x1cef).
  // actor.wallContact IS +0x1cee (actor.ts names it for its G Crash wall use; this
  // machine reads the same byte as the stream/part end event. The bridge's decoded
  // stream scheduler raises this exact byte when the authored stream completes.
  const streamEnded = actor.wallContact !== 0;
  if (!streamEnded) return;
  actor.wallContact = 0;
  actor.handlerTimer = 0;

  // --- zz_006a8c0_(actor, +0x548) — the borg-form TRANSFORM. (Verifier correction:
  // the engine also loads r5 = +0x3ec @0x8017a58c but zz_006a8c0_ never reads it —
  // it reloads the slot byte from the actor itself @0x8006a958, so the port takes
  // no playerSlot parameter.) Effects ported:
  //   * new borg id → +0x3e8 (mirrored to +0x94 — host residual, +0x94 unported)
  //   * +0x3f0 form-change counter ++
  //   * +0x8c/+0x90 re-pointed at self; +0x3e4→+0x96, +0x3e7→+0x97 skin/team bytes
  //     carried across the morph — host residuals (fields unported)
  //   * zz_0056ce0_ re-init + the event post zz_01cb750_ — host residuals (the
  //     model/descriptor swap; renderer doesn't hot-swap models yet)
  const previousForm = actor.borgNumber;
  const newForm = scratch.morphPendingForm ?? cfg.groundForm;
  actor.borgNumber = newForm;
  actor.borgMirror94 = newForm;
  actor.carriedSlot96 = actor.slot;
  actor.carriedVariant97 = actor.identityVariant;
  scratch.morphFormCount = (scratch.morphFormCount ?? 0) + 1;
  scratch.morphFormId = newForm; // labeled host surface for the pending visual swap

  // --- zz_017a608_(actor) — gun-state wipe: zero the fifteen u16 accumulators
  // (+0x18da, +0x197a, +0x1976, +0x1d68, +0x1d64, +0x1974, +0x1970, +0x1968,
  // +0x1964, +0x1926, +0x1922, +0x196e, +0x1962, +0x18e2, +0x18e0), then the actor
  // virtual at +0x4b8 if non-null, then FUN_800562b8 (weapon/ammo re-init from the
  // NEW form's descriptor — host residual, delegated to hooks.onMorph).
  wipeMorphGunState(actor);
  actor.upperBody?.(actor); // +0x4b8 virtual (families haven't installed one yet)
  hooks.onMorph?.(actor, newForm, previousForm);

  // +0x73f = 0 (housekeeping byte, unported) ; +0x5e0 &= ~3 (rlwinm @0x8017a5a8).
  actor.housekeeping73f = 0;
  actor.controlWord &= ~0x3;

  // Exit select (lha 6(r31) @0x8017a5b4, cmpw vs +0x548):
  if (newForm === cfg.flightExitForm) {
    // zz_006a750_(actor, 0x1b) — upper-body cue 27 (flight/vehicle pose; semantic
    // LIKELY per CUE-0X1B-EXIT). Faithful no-fallback: if the family cue table has
    // -1 at row 27 this dispatches nothing and NO other exit fires (the ROM's bne
    // skips the idle/air-fall arms).
    dispatchUpperBodyCue(actor, SHARED_MORPH_X.FLIGHT_EXIT_CUE);
  } else if (grounded) {
    // zz_006a474_ — ground idle reset (cues 0/0, same convention as
    // shared-melee-lunge.ts's zz_006a474_ port).
    dispatchUpperBodyCue(actor, 0);
    dispatchFullBodyCue(actor, 0);
  } else {
    // zz_006a5a4_ — air-fall exit. No cue change here; the bridge's completion
    // path transitions the actor out of attack state 61 (same handling as
    // shared-x-special.ts's airborne tail).
  }
  // NEGATIVE FINDING preserved: the shared engine seeds NO +0x694 cooldown and no
  // +0x558/+0x560 timers on exit — stateTimer is intentionally untouched.
}

/** zz_017a608_'s fifteen-field wipe (decomp 8017a608_zz_017a608.c:6-25, exact
 *  order preserved). +0x18da is actor.steerYaw; the rest are labeled scratch. */
export function wipeMorphGunState(actor: RomActor): void {
  const s = actor as RomActor & MorphScratch;
  actor.steerYaw = 0; // +0x18da
  s.gun197a = 0; s.gun1976 = 0;
  s.gun1d68 = 0; s.gun1d64 = 0;
  s.gun1974 = 0; s.gun1970 = 0;
  s.gun1968 = 0; s.gun1964 = 0;
  s.gun1926 = 0; s.gun1922 = 0;
  s.gun196e = 0; s.gun1962 = 0;
  s.gun18e2 = 0; s.gun18e0 = 0;
}

/**
 * Build the shared morph X-special handler for one family config — the port of the
 * lis/addi-r4 wrapper + `zz_017a374_` dispatch. Wire as actionTable[2] in the
 * family's root action dispatcher. `cfg.preEngine` (VEHICLE gun-heat halving) runs
 * every frame BEFORE the phase dispatch, matching the wrapper instruction order.
 */
export function createSharedMorphXSpecial(
  cfg: SharedMorphXConfig,
  ctx: StreamContext,
  hooks: SharedMorphXHooks = {},
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    cfg.preEngine?.(actor);
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: morphXPhase0(actor, cfg, ctx); break;
      case 1: morphXPhase1(actor, cfg, ctx, hooks); break;
      // Table @0x804347b0 has exactly 2 entries (next word 0x002e0000 ≠ code ptr).
      default: break;
    }
  };
}

// ============================================================================
// Per-family ROM config blocks (all DOL-dumped; every block ends 0x3f7ae148 = 0.98).
// ============================================================================

/** TITAN family config @0x8032f48c (wrapper zz_01260c8_: lis/addi @0x801260d0/d8,
 *  bl engine @0x801260dc). Bytes `00 00 06 05 06 05 ff ff 3f 7a e1 48`. Both
 *  pl0604 TITAN ROBOT and pl0618 PROTO TITAN morph to alt form 0x605; the handler
 *  FUN_801260a8 has no borg switch (unconditional bl @0x801260b4). */
export const TITAN_MORPH_CONFIG: SharedMorphXConfig = {
  groundSlot: 0,
  airSlot: 0,
  groundForm: 0x605,
  airForm: 0x605,
  flightExitForm: -1, // 0xffff — never; exits are ground-idle/air-fall only
  repositionScale: 0.98,
};

/** EAGLE ROBOT (pl0606) config @0x803319e0 (wrapper FUN_8012a4e4: addi 0x19e0
 *  @0x8012a4f4, bl engine @0x8012a4f8; handler FUN_8012a4b0 routes borg 0x606 here).
 *  Bytes `00 00 06 07 06 07 06 07 3f 7a e1 48` — ground/air/flightExit ALL 0x607,
 *  so the exit compare always matches: EAGLE ROBOT always exits via cue 0x1b.
 *  PROTO EAGLE pl061a takes the != 0x606 branch to a BESPOKE machine — excluded. */
export const EAGLE_MORPH_CONFIG: SharedMorphXConfig = {
  groundSlot: 0,
  airSlot: 0,
  groundForm: 0x607,
  airForm: 0x607,
  flightExitForm: 0x607, // always the cue-0x1b exit
  repositionScale: 0.98,
};

/** PANTHER family config @0x80365510 (wrapper zz_018cb20_: lis -0x7fca @0x8018cb28,
 *  addi 0x5510 @0x8018cb30, bl engine @0x8018cb34; handler FUN_8018cb00 has no borg
 *  switch). Bytes `00 00 06 14 06 14 ff ff 3f 7a e1 48`. pl0613 PANTHER ROBOT +
 *  pl0627 PROTO PANTHER both morph to alt form 0x614. */
export const PANTHER_MORPH_CONFIG: SharedMorphXConfig = {
  groundSlot: 0,
  airSlot: 0,
  groundForm: 0x614,
  airForm: 0x614,
  flightExitForm: -1,
  repositionScale: 0.98,
};

/** VICTORY MACHINE (pl0625) config @0x80345c28 (wrapper zz_015bc10_: pre-halves
 *  +0x18e0/+0x18e2 then addi 0x5c28, bl engine @0x8015bc3c; handler FUN_8015bb44
 *  routes borg 0x625 here). Bytes `01 01 06 26 06 26 06 26 3f 7a e1 48` — slots
 *  1/1, both forms 0x626, flightExit 0x626 = always the cue-0x1b exit. The ONLY
 *  registered config with wrapper-side pre-engine work. */
export const VICTORY_MACHINE_MORPH_CONFIG: SharedMorphXConfig = {
  groundSlot: 1,
  airSlot: 1,
  groundForm: 0x626,
  airForm: 0x626,
  flightExitForm: 0x626,
  repositionScale: 0.98,
  preEngine: halveGunHeat18e0,
};

/** Runtime form 0x611 (VICTORY KING's vehicle form) morph-BACK config @0x80345c10
 *  (wrapper zz_015bb90_: pre-halves +0x1922/+0x1926, addi 0x5c10 @0x8015bba0, bl
 *  @0x8015bbbc). Bytes `00 01 06 10 06 12 06 12 3f 7a e1 48` — grounded morphs BACK
 *  to 0x610 (robot), airborne to the shared flight form 0x612 (= flightExit).
 *  UNREGISTRABLE until the host can instantiate alt-form actors (0x611 has no
 *  borgs.json entry) — exported for the round-trip port. */
export const VEHICLE_FORM_0611_MORPH_CONFIG: SharedMorphXConfig = {
  groundSlot: 0,
  airSlot: 1,
  groundForm: 0x610,
  airForm: 0x612,
  flightExitForm: 0x612,
  repositionScale: 0.98,
  preEngine: halveGunHeat1922,
};

/** Runtime form 0x622 (VICTORY DUKE's vehicle form) morph-BACK config @0x80345c1c
 *  (wrapper zz_015bbd0_: pre-halves +0x18e0/+0x18e2, r4=0x80345c1c, bl @0x8015bbfc).
 *  Bytes `00 00 06 21 06 21 ff ff 3f 7a e1 48` — morphs back to 0x621. Unregistrable
 *  for the same reason as 0x611. */
export const VEHICLE_FORM_0622_MORPH_CONFIG: SharedMorphXConfig = {
  groundSlot: 0,
  airSlot: 0,
  groundForm: 0x621,
  airForm: 0x621,
  flightExitForm: -1,
  repositionScale: 0.98,
  preEngine: halveGunHeat18e0,
};

// ============================================================================
// Family configure entry points. Each family's ROM root dispatcher places the X
// handler at action-table index 2 (verified: every family's handler pointer sits
// at index 2 of its data-side function table — 0x8032f424 / 0x80331944 /
// 0x80345bf0 / 0x80365474). Other action rows keep the generic fallback.
// ============================================================================

function makeMorphRootAction(
  cfg: SharedMorphXConfig,
  ctx: StreamContext,
  hooks: SharedMorphXHooks,
): (actor: RomActor) => void {
  const xSpecial = createSharedMorphXSpecial(cfg, ctx, hooks);
  const actionTable: Array<((actor: RomActor) => void) | null> = [null, null, xSpecial, null, null];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a TITAN-family actor (ctor 0x80125a28: pl0604 TITAN ROBOT / pl0618
 *  PROTO TITAN). X = shared morph engine with config @0x8032f48c. */
export function configureTitanFamily(
  actor: RomActor,
  borgId: "pl0604" | "pl0618",
  ctx: StreamContext,
  hooks: SharedMorphXHooks = {},
): void {
  actor.borgNumber = borgId === "pl0604" ? 0x604 : 0x618;
  actor.rootAction = makeMorphRootAction(TITAN_MORPH_CONFIG, ctx, hooks);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Configure an EAGLE ROBOT actor (ctor 0x80129608, pl0606 ONLY — pl061a PROTO
 *  EAGLE's != 0x606 branch is a bespoke 4-phase gun machine, NOT this module). */
export function configureEagleFamily(
  actor: RomActor,
  borgId: "pl0606",
  ctx: StreamContext,
  hooks: SharedMorphXHooks = {},
): void {
  actor.borgNumber = 0x606;
  actor.rootAction = makeMorphRootAction(EAGLE_MORPH_CONFIG, ctx, hooks);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  void borgId;
}

/** Configure a PANTHER-family actor (ctor 0x8018c2b0: pl0613 PANTHER ROBOT /
 *  pl0627 PROTO PANTHER). X = shared morph engine with config @0x80365510. */
export function configurePantherFamily(
  actor: RomActor,
  borgId: "pl0613" | "pl0627",
  ctx: StreamContext,
  hooks: SharedMorphXHooks = {},
): void {
  actor.borgNumber = borgId === "pl0613" ? 0x613 : 0x627;
  actor.rootAction = makeMorphRootAction(PANTHER_MORPH_CONFIG, ctx, hooks);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Configure a VICTORY MACHINE actor (ctor 0x8015b420, pl0625 only). pl061f
 *  VICTORY TANK has NO branch in the family X handler FUN_8015bb44 (X dead at
 *  this layer — DEAD-BORG-BRANCHES) and is intentionally not registered. */
export function configureVictoryMachineFamily(
  actor: RomActor,
  borgId: "pl0625",
  ctx: StreamContext,
  hooks: SharedMorphXHooks = {},
): void {
  actor.borgNumber = 0x625;
  actor.rootAction = makeMorphRootAction(VICTORY_MACHINE_MORPH_CONFIG, ctx, hooks);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
  void borgId;
}
