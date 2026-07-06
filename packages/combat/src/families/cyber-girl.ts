// CYBER GIRL family (ctor 0x8012f204) — bespoke X-special port.
// Covers the three borgs sharing this ctor:
//   pl0305 CYBER GIRL SUPER  (0x305)
//   pl0309 CYBER GIRL        (0x309)
//   pl030a CYBER GIRL HYPER  (0x30a)
// Source:
//   research/decomp/ghidra-export/chunk_0034.c:4341-4611 (root dispatcher
//   FUN_8012f5bc → action table PTR_FUN_80333a60 → X-special leaf FUN_8012f6f4 →
//   borg-switched engines zz_012f728_ / zz_012fb20_).
//
// The X-special (actionIndex 2) is a BESPOKE borg-switched beam phase machine — the
// engine addresses 0x8012f728 + 0x8012fb20 live in the family code block (0x8012fxxx),
// NOT in the shared-engine ranges (0x80177xxx/0x80178xxx the majority of the roster
// tail-calls). The leaf FUN_8012f6f4 branches on borg number (+0x3e8):
//   pl0309 (0x309)        → zz_012fb20_ → PTR_FUN_804345c0[+0x540]() (2 phases)
//   pl0305/pl030a (else)  → zz_012f728_ → PTR_FUN_80333a80[+0x540]() (3 phases)
// All three fire a beam stream at group 4; the slot is borg/air-switched:
//   pl0305/pl030a ground slot 0 / air slot 2; pl0309 ground slot 4 / air slot 5
//   (actionStreamTables.json confirmation: pl0305 airSeedSlot 2, pl0309 4/5).
//
// The pl0305/pl030a phase-2 contact branch spawns the beam child via zz_013212c_
// @0x8013212c, record-select by borg number (0x305→0..3, 0x30a→6..9 keyed on +0x144
// bit). pl0309's phase machine instead transitions to upper-body cue 7 (zz_006a750_
// (actor, 7)) — its beam child is fired by the stream's op 0x09 (fireChild), so the
// bridge's onFireChild resolver owns the spawn (no explicit family-spawner call).
//
// Float constants (FLOAT_80439e40..e50): values inferred from usage context — the ROM
// uses FLOAT_80439e40 to ZERO the launch scalars (→0.0), FLOAT_80439e44 as the stream
// playback rate (→-1.0, the engine-wide default passed to zz_004beb8_), FLOAT_80439e48
// as the PSQUATScale reposition multiplier (→0.95, the same drag coefficient the
// shared-X engine + ninja big-shuriken use), and FLOAT_80439e4c/_e50 as the post-state
// cooldown seed (→4.0, matching the worm/coyote-style +0x694 = K + dt shape).

import type { RomActor } from "../rom/actor.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romAirKnockoutReturn, romGroundIdleReturn } from "./shared-idle-return.js";

/** Values inferred from the chunk_0034.c usage context (see file header). */
export const CYBER_GIRL_X = {
  ZERO: 0.0,            // FLOAT_80439e40 — zeros launch vel / gravityCoeff (+0x44/48/4c/50)
  STREAM_RATE: -1.0,    // FLOAT_80439e44 — zz_004beb8_ playback rate (engine default)
  REPOS: 0.95,          // FLOAT_80439e48 — PSQUATScale motion multiplier (pull toward target)
  COOLDOWN_305: 4.0,    // FLOAT_80439e4c — pl0305/pl030a +0x694 cooldown seed (K + dt)
  COOLDOWN_309: 4.0,    // FLOAT_80439e50 — pl0309 +0x694 cooldown seed (K + dt)
  /** zz_013212c_ @0x8013212c — the on-contact beam-child spawner (pl0305/pl030a phase 2).
   *  Record-select keyed on borg number AND the polling +0x144 bit (loop 0..3):
   *    0x305 → iVar1      (records 0..3)
   *    0x30a → iVar1 + 6  (records 6..9)
   *  pl0309 does NOT call this spawner (its beam is stream-op-0x09-fired). */
  BEAM_SPAWNER_ADDR: 0x8013212c,
} as const;

/** +0x144 bit-row polling → beam-child record offset within the borg's range. The ROM
 *  loops iVar1 0..3 testing `+0x144 & (1 << iVar1)`; our port approximates by reading
 *  the low nibble of a surfaced `beamRow` scratch field (host-set from the lock-target
 *  row select). Falls back to 0 (the first row) when unset. */
function beamRowFor(actor: RomActor): number {
  const scratch = actor as RomActor & { beamRow?: number };
  return scratch.beamRow ?? 0;
}

/** Borg-id → beam-child record index for zz_013212c_ (FUN_8012f958:4474-4479 switch). */
function beamChildType(borgNumber: number, row: number): number {
  switch (borgNumber) {
    case 0x305: return row;       // 0..3
    case 0x30a: return row + 6;   // 6..9
    default: return row;          // defensive — pl0309 never reaches this spawner
  }
}

export interface CyberGirlFamilyCtx extends StreamContext {}

// ============================================================================
// pl0305/pl030a phase machine — engine zz_012f728_ @ chunk_0034.c:4357, table
// PTR_FUN_80333a80[+0x540]. Three phases:
//   P0 FUN_8012f778 — reposition + start beam stream, then FALL THROUGH to P1
//                    (the ROM tail-calls zz_012f854_ at the end of P0).
//   P1 zz_012f854_ — tick stream, drag motion, on +0x1cee stream-end either return
//                    to idle (ground/air) OR advance to P2 (re-arm).
//   P2 FUN_8012f958 — tick stream, on +0x1cef contact spawn beam child via
//                    zz_013212c_(borg-switched). On +0x1cee return to idle + cooldown.
// ============================================================================

function cyberGirlSuperPhase0(actor: RomActor, ctx: CyberGirlFamilyCtx): void {
  // +0x540++ (FUN_8012f778:4380) — advance to phase 1 for the next tick.
  actor.fbPhaseSlots[0] = 1;
  // +0x5ac = +0x72 when +0xcc == 0 — activeYaw snapshot from heading.
  if ((actor as RomActor & { cc?: number }).cc === 0) {
    actor.activeYaw = actor.heading;
  }
  // Zero the launch scalars (FUN_8012f778:4384-4388).
  actor.gravityCoeff = CYBER_GIRL_X.ZERO;
  actor.yVel = CYBER_GIRL_X.ZERO;
  actor.hDecel = CYBER_GIRL_X.ZERO;
  actor.hSpeed = CYBER_GIRL_X.ZERO;
  // +0x80/+0x7e/+0x7c = 0 (u16 anim offsets; visual — not surfaced).
  // +0x6eb = 4 (stream-state byte; visual).
  // +0x6ea = ground/air slot seed: 0 ground, 2 air (+0x5e0 & 0x40 frozen/air bit).
  const air = (actor.controlWord & 0x40) !== 0;
  const slot = air ? 2 : 0;
  // zz_006d144_(actor, 0xc0) — face the target; the bridge pre-aims so we honor the
  // post-face heading. Motion = pos − target (gnt4_PSVECSubtract).
  const t = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
  if (t) {
    actor.motion.x = (actor.pos.x - t.x) - (actor.pos.x - t.x) * CYBER_GIRL_X.REPOS;
    actor.motion.z = (actor.pos.z - t.z) - (actor.pos.z - t.z) * CYBER_GIRL_X.REPOS;
  }
  // zz_004beb8_(rate, actor, mask 0xf, group 4, slot) — start the beam stream.
  // ROM reads +0x6ea THEN increments it before the call; the incremented value is the
  // FOLLOW-UP slot (phase 1 re-arm uses it). We surface the pre-increment slot here.
  startStream(actor, 0xf, 4, slot, CYBER_GIRL_X.STREAM_RATE);
  // ROM tail-calls zz_012f854_ (phase 1) in the same frame — mirror that inline.
  cyberGirlSuperPhase1(actor, ctx);
}

function cyberGirlSuperPhase1(actor: RomActor, ctx: CyberGirlFamilyCtx): void {
  // zz_012f854_:4418 — tick the beam stream.
  tickStream(actor, 0xf, ctx);
  // +0x1d10 nonzero → re-face target (zz_006d144_); bridge pre-aims, no-op here.
  // gnt4_PSQUATScale(FLOAT_80439e48, motion, motion) — drag the reposition accumulator.
  actor.motion.x *= CYBER_GIRL_X.REPOS;
  actor.motion.z *= CYBER_GIRL_X.REPOS;
  // gnt4_PSVECAdd(pos, motion, pos) — apply dragged motion.
  actor.pos.x += actor.motion.x;
  actor.pos.z += actor.motion.z;
  // zz_00679d0_(actor) — physics step (no gravity in this phase; gravityCoeff == 0).
  // +0x1cee wall/stream-end contact: the ROM transitions based on (+0x144 & 0xf):
  //   0 → clear action bits + return to idle (zz_006a474_ ground / zz_006a5a4_ air)
  //   else → +0x540++ (advance to phase 2) and re-arm stream at slot (+++0x6ea)
  if (actor.wallContact !== 0) {
    const cmdBits = (actor as RomActor & { cmdBits144?: number }).cmdBits144 ?? 0;
    if ((cmdBits & 0xf) === 0) {
      cyberGirlReturnToIdle(actor, /*air*/ (actor.controlWord & 0x40) !== 0);
      return;
    }
    actor.fbPhaseSlots[0] = 2;
    // Re-arm stream at the incremented slot (the ROM's +0x6ea++ from phase 0).
    const nextSlot = ((actor as RomActor & { slot6ea?: number }).slot6ea ?? 1);
    startStream(actor, 0xf, 4, nextSlot, CYBER_GIRL_X.STREAM_RATE);
  }
}

function cyberGirlSuperPhase2(actor: RomActor, _ctx: CyberGirlFamilyCtx): void {
  // FUN_8012f958:4459-4461 — drag motion + integrate.
  actor.motion.x *= CYBER_GIRL_X.REPOS;
  actor.motion.z *= CYBER_GIRL_X.REPOS;
  actor.pos.x += actor.motion.x;
  actor.pos.z += actor.motion.z;
  // zz_004cd24_(actor, 0xf) — tick stream.
  // zz_00679d0_(actor) — physics (no gravity this phase).
  // +0x1cef > 0 (part-0 contact): spawn the beam child if +0x1b03 == 0.
  if (actor.contactP0 > 0) {
    const b03 = (actor as RomActor & { b03?: number }).b03 ?? 0;
    if (b03 === 0) {
      actor.contactP0 = 0; // ROM clears +0x1cef after consuming.
      // +0x6eb-- (swing counter); zz_013212c_(actor, type, +0x144) — beam spawn.
      const row = beamRowFor(actor) & 3;
      _ctx.onFamilyProjectile?.(actor, CYBER_GIRL_X.BEAM_SPAWNER_ADDR, beamChildType(actor.borgNumber, row));
    }
  }
  // +0x1cee wall/stream-end → clear + return to idle with cooldown.
  if (actor.wallContact !== 0) {
    actor.stateTimer = CYBER_GIRL_X.COOLDOWN_305 + actor.dt; // +0x694 = K + dt
    cyberGirlReturnToIdle(actor, /*air*/ (actor.controlWord & 0x40) !== 0);
  }
}

// ============================================================================
// pl0309 phase machine — engine zz_012fb20_ @ chunk_0034.c:4515, table
// PTR_FUN_804345c0[+0x540]. Two phases:
//   P0 FUN_8012fb6c — reposition (PSVECSubtract + PSQUATScale + PSVECAdd), physics,
//                    start beam stream at slot 4 (ground) / 5 (air).
//   P1 FUN_8012fc64 — tick stream, motion, physics; on ground+contact transition to
//                    upper-body cue 7 (zz_006a750_(actor, 7)) with cooldown; on
//                    stream-end clear + return to idle.
// pl0309 does NOT call zz_013212c_ — its beam child is fired by the stream's op 0x09
// (fireChild), resolved by the bridge's onFireChild path.
// ============================================================================

function cyberGirlPhase0(actor: RomActor, _ctx: CyberGirlFamilyCtx): void {
  // FUN_8012fb6c:4538 — +0x540++.
  actor.fbPhaseSlots[0] = 1;
  if ((actor as RomActor & { cc?: number }).cc === 0) {
    actor.activeYaw = actor.heading; // +0x5ac = +0x72
  }
  // +0x6ea = 4 ground / 5 air (FUN_8012fb6c:4542-4545).
  const air = (actor.controlWord & 0x40) !== 0;
  const slot = air ? 5 : 4;
  // Zero the launch scalars (FUN_8012fb6c:4546-4550).
  actor.gravityCoeff = CYBER_GIRL_X.ZERO;
  actor.yVel = CYBER_GIRL_X.ZERO;
  actor.hDecel = CYBER_GIRL_X.ZERO;
  actor.hSpeed = CYBER_GIRL_X.ZERO;
  // zz_006d144_(actor, 0xc0) — face target; reposition motion.
  const t = (actor as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget;
  if (t) {
    // PSVECSubtract(pos, target, motion) then PSQUATScale(0.95, motion, motion).
    actor.motion.x = (actor.pos.x - t.x) * CYBER_GIRL_X.REPOS - (actor.pos.x - t.x);
    actor.motion.z = (actor.pos.z - t.z) * CYBER_GIRL_X.REPOS - (actor.pos.z - t.z);
    // PSVECAdd(pos, motion, pos) — apply the scaled delta toward target.
    actor.pos.x += actor.motion.x;
    actor.pos.z += actor.motion.z;
  }
  // zz_00679d0_ — physics (gravityCoeff == 0, so just XZ integration).
  // +0x6ea++ then zz_004beb8_(rate, actor, 0xf, 4, slot).
  startStream(actor, 0xf, 4, slot, CYBER_GIRL_X.STREAM_RATE);
}

function cyberGirlPhase1(actor: RomActor, ctx: CyberGirlFamilyCtx): void {
  // FUN_8012fc64:4577 — tick stream.
  tickStream(actor, 0xf, ctx);
  // +0x1cf0 < 0 → clear + restore gravityCoeff from descriptor +0x6c (unsurfaced; no-op).
  // +0x1d10 nonzero → re-face (zz_006d144_) — bridge pre-aims.
  // PSQUATScale(0.95, motion, motion) + PSVECAdd(pos, motion, pos).
  actor.motion.x *= CYBER_GIRL_X.REPOS;
  actor.motion.z *= CYBER_GIRL_X.REPOS;
  actor.pos.x += actor.motion.x;
  actor.pos.z += actor.motion.z;
  // zz_00679d0_ — physics.
  // Grounded + air-borne + contact gate: the ROM's fun_8012fc64:4589 compound test
  // (physicsResult != 0 && +0x5e0 & 0x40 && +0x1cef < 0) routes to the
  // zz_006a750_(actor, 7) transition with +0x694 cooldown. Our +0x1cef is surfaced as
  // `contactP0 < 0` (the ROM's "release/edge" sense).
  const air = (actor.controlWord & 0x40) !== 0;
  if (air && actor.contactP0 < 0) {
    actor.stateTimer = CYBER_GIRL_X.COOLDOWN_309 + actor.dt; // +0x694 = K + dt
    actor.contactP0 = 0;
    // zz_006a750_(actor, 7) — upper-body cue 7 (air idle recovery).
    cyberGirlReturnToIdle(actor, /*air*/ true);
    return;
  }
  // +0x1cee wall/stream-end → clear + return to idle.
  if (actor.wallContact !== 0) {
    cyberGirlReturnToIdle(actor, air);
  }
}

// ============================================================================
// Shared helpers + root action dispatcher.
// ============================================================================

/** Mirror of the ROM's zz_006a474_ (ground idle) / zz_006a5a4_ (air idle) tail that
 *  every cyber-girl phase falls into on completion. Clears the action-mode bits and
 *  runs the decomp-verified idle-return helper (shared-idle-return.ts — the old
 *  full-cue-0 + upper-6/7 mapping here was refuted against chunk_0009.c during the
 *  valkrie verify pass). */
function cyberGirlReturnToIdle(actor: RomActor, air: boolean): void {
  // +0x73f = 0, +0x5e0 &= ~0x3 (clear action-mode bits) — ends attack state 61.
  actor.controlWord = actor.controlWord & ~0x3;
  if (air) {
    romAirKnockoutReturn(actor); // zz_006a5a4_ — upper cue 6
  } else {
    romGroundIdleReturn(actor);  // zz_006a474_ — upper cue 0 + velocity zeroing
  }
}

/** Borg-switched X-special dispatch — port of FUN_8012f6f4 @ chunk_0034.c:4343. */
function cyberGirlXSpecial(actor: RomActor, ctx: CyberGirlFamilyCtx): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  if (actor.borgNumber === 0x309) {
    // pl0309 — engine zz_012fb20_, table PTR_FUN_804345c0 (2 phases).
    if (phase === 0) cyberGirlPhase0(actor, ctx);
    else cyberGirlPhase1(actor, ctx);
  } else {
    // pl0305/pl030a — engine zz_012f728_, table PTR_FUN_80333a80 (3 phases).
    if (phase === 0) cyberGirlSuperPhase0(actor, ctx);
    else if (phase === 1) cyberGirlSuperPhase1(actor, ctx);
    else cyberGirlSuperPhase2(actor, ctx);
  }
}

/** Action-index table (PTR_FUN_80333a60, 3 entries). Only actionIndex 2 (X-special)
 *  is ported here. Action 0 (B-tap shot) and 1 (B-melee lunge) are command-routed to
 *  the family's shared shot/lunge engines (engine addresses 0x8010a9b4 / 0x8010c220 —
 *  the cross-family shot-combo + melee-lunge blocks, NOT bespoke to this family); the
 *  port falls through to the generic @gf/combat layer for those. 3/4 are null. */
export function createCyberGirlRootAction(
  ctx: CyberGirlFamilyCtx,
): (actor: RomActor) => void {
  const actionTable: Array<((actor: RomActor) => void) | null> = [
    null,                                  // 0: B-tap shot (engine 0x8010a9b4) — generic layer
    null,                                  // 1: B-melee lunge (engine 0x8010c220) — generic layer
    (actor) => cyberGirlXSpecial(actor, ctx), // 2: X-special (bespoke borg-switched beam)
    null,                                  // 3: B charge — TODO identify
    null,                                  // 4: — TODO identify
  ];
  return (actor: RomActor) => {
    const fn = actionTable[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Configure a freshly-spawned CYBER GIRL-family actor (pl0305/pl0309/pl030a).
 *  Stamps the borg-number switch the X-special leaf reads and wires the root action
 *  dispatcher. */
export function configureCyberGirlFamily(
  actor: RomActor,
  borgId: "pl0305" | "pl0309" | "pl030a",
  ctx: CyberGirlFamilyCtx,
): void {
  const numMap: Record<typeof borgId, number> = {
    pl0305: 0x305,
    pl0309: 0x309,
    pl030a: 0x30a,
  };
  actor.borgNumber = numMap[borgId];
  actor.rootAction = createCyberGirlRootAction(ctx);
  // cueTable + familyStreamBank are set by the spawn layer (familyCueTablesFull.json
  // entry "0x8012f204"). Defaults matching power-on state:
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}
