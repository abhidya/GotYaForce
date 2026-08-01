// SIRIUS (pl0e00, borgNumber 0xe00) + SIRIUS II (pl0e05, borgNumber 0xe05) family
// (ctor 0x801898b0) — bespoke 3-action dispatch port, ROM-faithful 1:1.
//
// Both borgs share one root action router (FUN_80189cf0 → table @0x80362c98) that
// indexes the actor actionIndex (+0x580) into three action sub-routers. Each
// sub-router dispatches its own phase table (indexed by +0x540):
//
//   action 0 (FUN_80189d2c) table @0x80362ca8 — 3-phase aimed single-shot
//   action 2 (FUN_80189fa8) table @0x80362cd4 — 4-phase aimed beam (cooldown tail)
//   action 3 (FUN_8018a348) table @0x80362d04 — 4-phase dual-weapon barrage
//
// Source: research/decomp/ghidra-export/chunk_0046.c:2913-3292.
// Exit helper zz_006a53c_ @ chunk_0009.c:750 (clear +0x73f, strip +0x5e0 action bits,
// dispatch full-body cue 0x1b; seed +0x694 = param+dt when param > 0).
//
// Float constants (read from boot.dol this session):
//   FLOAT_8043b000 = 10.0  ammo-fail / bail cooldown seed
//   FLOAT_8043b004 = 3.0   action-0 phase-0 main timer seed
//   FLOAT_8043b00c = 0.0   universal drain threshold
//   FLOAT_8043b02c = 20.0  action-0 phase-1 seed / action-2 +0x55c cooldown seed
//   FLOAT_8043b050 = 60.0  action-2 main timer / action-3 phase-0 seed
//   FLOAT_8043b054 = 12.0  action-3 phase-1 exit seed
//   FLOAT_8043b058 = 6.0   action-3 volley sub-timer reset
//   FLOAT_8043b05c = 30.0  action-3 phase-2→3 advance seed
//   FLOAT_8043b060 = 0.2   FUN_8006cc90 stream rate (cosmetic)
//
// Spawners (family-local):
//   zz_01fc1b0_ @0x801fc1b0 — child projectile spawn (action 0 + action-3 weapon-0 volley)
//   FUN_801f2bf8 @0x801f2bf8 — beam child spawn (action 2 + action-3 weapon-2 volley).
//       Borg-gated: only spawns when borgNumber ∈ {0xe00, 0xe05} && type < 0x1e
//       (chunk_0060.c:4843). Both registered members pass the gate.
//
// UNSURFACED HOST DEPS (ported as structure, marked TODO):
//   zz_0066408_(actor,0,aimOrigin518,&vec) — target-relative aim vector used by
//       action-0/2 phase-0 spawn-type classification. The classification indexes
//       byte tables DAT_80362cb4 (action 0) / DAT_80362ce4 (action 2) via a
//       distance/angle ladder (FLOAT_8043b008..b028 / b030..b04c). Without the aim
//       helper + tables the spawn TYPE defaults to 0; the phase machine, ammo gate,
//       timer drains, and spawn ROUTING are all faithful.
//   DAT_80362d14 / DAT_80362d2c — action-3 per-shot type tables (cursor×2 bytes).
//       Default type 0; volley structure (2 shots/cycle, ammo gate per shot, cursor
//       advance, done-latch) is faithful.
//   zz_0011cc4_(slot,weaponIndex) — ammo-fail feedback cue (action 3). No-op TODO.
//   zz_018a6fc_(actor,type,mode) — the SIRIUS multi-port stream tick (8 ports); it
//       decays renderer-owned part offsets (+0x18d4/18d6 stride, 12 sub-parts) then
//       dispatches FUN_8006cc90 (no-op returning 0 without banks). Ported as no-op 0.

import { createRomActor, type RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { allocateWeapon } from "../rom/helpers.js";
import type { StreamContext } from "../rom/stream-vm.js";

const SIRIUS_BORG_NUMBERS: Record<string, number> = {
  pl0e00: 0xe00, // SIRIUS
  pl0e05: 0xe05, // SIRIUS II
};

export type SiriusBorgId = "pl0e00" | "pl0e05";

const SIRIUS = {
  /** FLOAT_8043b000 = 10.0 — ammo-fail / bail cooldown seed. */
  BAIL_COOLDOWN_SEED: 10.0,
  /** FLOAT_8043b004 = 3.0 — action-0 phase-0 main timer seed. */
  A0_MAIN_TIMER_SEED: 3.0,
  /** FLOAT_8043b00c = 0.0 — universal drain threshold. */
  THRESHOLD: 0.0,
  /** FLOAT_8043b02c = 20.0 — action-0 phase-1 seed / action-2 +0x55c cooldown seed. */
  A0_PHASE1_SEED: 20.0,
  /** FLOAT_8043b050 = 60.0 — action-2 main timer / action-3 phase-0 seed. */
  A2_MAIN_TIMER_SEED: 60.0,
  /** FLOAT_8043b054 = 12.0 — action-3 phase-1 exit seed. */
  A3_PHASE1_EXIT_SEED: 12.0,
  /** FLOAT_8043b058 = 6.0 — action-3 volley sub-timer reset. */
  A3_VOLLEY_RESET: 6.0,
  /** FLOAT_8043b05c = 30.0 — action-3 phase-2→3 advance seed. */
  A3_PHASE3_SEED: 30.0,
  /** FLOAT_8043b060 = 0.2 — FUN_8006cc90 stream rate (cosmetic). */
  STREAM_RATE: 0.2,
  /** zz_006a53c_ full-body exit cue. */
  EXIT_CUE: 0x1b,
  /** +0x548 scratch armed by action-0 phase-0 (= 8). */
  A0_SCRATCH548: 8,
  /** Action-3 weapon-0 volley cursor cap (advance done-latch when > 10 → 11 cycles). */
  A3_W0_CURSOR_CAP: 10,
  /** Action-3 weapon-2 volley cursor cap (advance done-latch when >= 10 → 10 cycles). */
  A3_W2_CURSOR_CAP: 10,
} as const;

// ----------------------------------------------------------------------------
// Spawner addresses (family-local projectile/beam child spawners).
// ----------------------------------------------------------------------------
/** zz_01fc1b0_ @0x801fc1b0 — child projectile spawn (no borg gate). */
const SIRIUS_SHOT_SPAWNER = 0x801fc1b0;
/** FUN_801f2bf8 @0x801f2bf8 — beam child spawn (borg-gated 0xe00/0xe05, type < 0x1e). */
const SIRIUS_BEAM_SPAWNER = 0x801f2bf8;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface SiriusScratch {
  /** +0x144: action-0 spawn type (aim-classified) / action-3 weapon-0 shot type. */
  siriusType144?: number;
  /** +0x145: action-2 spawn type / action-3 weapon-2 shot type. */
  siriusType145?: number;
  /** +0x542: action-3 weapon-0 volley done-latch (0→1 when cursor cap reached). */
  siriusVolleyState542?: number;
  /** +0x543: action-3 weapon-2 volley done-latch (0→1 when cursor cap reached). */
  siriusVolleyState543?: number;
  /** +0x54c: action-3 weapon-0 volley cursor (s16, 0..11). */
  siriusVolleyCursor54c?: number;
  /** +0x54e: action-3 weapon-2 volley cursor (s16, 0..10). */
  siriusVolleyCursor54e?: number;
  /** +0x560: action-3 weapon-0 volley sub-timer (float; 0.0 seed, 6.0 reset). */
  siriusVolleyTimer560?: number;
  /** +0x564: action-3 weapon-2 volley sub-timer (float; 0.0 seed, 6.0 reset). */
  siriusVolleyTimer564?: number;
  /** +0x55c: action-2 phase-2/3 cooldown sub-timer (20.0 seed). */
  siriusCooldown55c?: number;
  /** +0x548: action-0 scratch (= 8 on arm). */
  siriusScratch548?: number;
}

type SiriusActor = RomActor & SiriusScratch;

function scratchOf(actor: RomActor): SiriusActor {
  return actor as SiriusActor;
}

// ----------------------------------------------------------------------------
// zz_006a53c_(actor, param) @ chunk_0009.c:750 — common action-exit. With param 0
// (every SIRIUS exit) it clears +0x73f, strips the +0x5e0 action-mode bits, and
// dispatches the full-body cue 0x1b. +0x694 is only seeded when param > 0.
// ----------------------------------------------------------------------------
function exitAction(actor: RomActor, param: number): void {
  if (param > 0) {
    actor.stateTimer = param + actor.dt;
  }
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~0x3;
  dispatchFullBodyCue(actor, SIRIUS.EXIT_CUE);
}

// ----------------------------------------------------------------------------
// zz_018a6fc_ host bridge — the SIRIUS multi-port stream/spawn tick. It decays
// renderer-owned part offsets then dispatches FUN_8006cc90 (the action-stream tick).
// SIRIUS has no extracted stream banks (code-driven), so FUN_8006cc90 returns 0 and
// the tick is an honest no-op — the exact ROM behavior with no bank attached.
// ----------------------------------------------------------------------------
function tickSiriusStream(
  _actor: SiriusActor,
  _type: number,
  _mode: number,
): number {
  return 0;
}

/** +0xcc target-present gate shared by action-0/2 phase-0 (bail to cooldown if null). */
function hasTarget(actor: RomActor): boolean {
  return actor.visibilityTarget !== null;
}

// ----------------------------------------------------------------------------
// Action 0 — aimed single-shot (table @0x80362ca8, 3 phases).
//   ph0 (FUN_80189d6c, 105i): target + ammo gate (weapon 0); on fail bail to ph2
//       (+0x558=10.0), else advance + seed +0x558=3.0, arm +0x548=8, aim-classify
//       spawn type into +0x144 (TODO: zz_0066408_ + DAT_80362cb4 unsurfaced).
//   ph1 (FUN_80189f10, 15i): advance, seed +0x558=20.0, spawn zz_01fc1b0_(+0x144).
//   ph2 (FUN_80189f4c, 23i): drain +0x558; exit (zz_006a53c_(0)) when <= 0.0.
// ----------------------------------------------------------------------------
function action0(actor: SiriusActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: {
      if (!hasTarget(actor) || !allocateWeapon(actor, ctx, 0, 1, true)) {
        // Bail straight to cooldown (phase 2).
        actor.fbPhaseSlots[0] = 2;
        actor.handlerTimer = SIRIUS.BAIL_COOLDOWN_SEED; // +0x558 = 10.0 (FLOAT_8043b000)
        return;
      }
      actor.fbPhaseSlots[0] = 1;
      actor.handlerTimer = SIRIUS.A0_MAIN_TIMER_SEED; // +0x558 = 3.0 (FLOAT_8043b004)
      actor.siriusScratch548 = SIRIUS.A0_SCRATCH548; // +0x548 = 8
      // TODO: zz_0066408_(actor, 0, aimOrigin518, &vec) aim-classify + DAT_80362cb4
      // lookup populate +0x144 with the spawn type. Unsurfaced → default 0.
      actor.siriusType144 = 0;
      return;
    }
    case 1: {
      actor.fbPhaseSlots[0] = 2;
      actor.handlerTimer = SIRIUS.A0_PHASE1_SEED; // +0x558 = 20.0 (FLOAT_8043b02c)
      ctx.onFamilyProjectile?.(actor, SIRIUS_SHOT_SPAWNER, actor.siriusType144 ?? 0); // zz_01fc1b0_
      return;
    }
    case 2: {
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      if (actor.handlerTimer <= SIRIUS.THRESHOLD) {
        exitAction(actor, 0); // zz_006a53c_(actor, 0)
      }
      return;
    }
    default: return;
  }
}

// ----------------------------------------------------------------------------
// Action 2 — aimed beam with cooldown tail (table @0x80362cd4, 4 phases).
//   ph0 (FUN_80189fe8, 121i): target + ammo gate (weapon 2); on fail bail to ph3
//       (+0x558=10.0), else advance + aim-classify type into +0x145 (TODO), seed
//       +0x558=60.0.
//   ph1 (FUN_8018a1cc, 28i): drain +0x558; tick zz_018a6fc_(+0x145,1); advance on
//       stream event OR +0x558 <= 0.0.
//   ph2 (FUN_8018a23c, 29i): advance, seed +0x558=60.0 / +0x55c=20.0, tick stream,
//       spawn FUN_801f2bf8(+0x145) (borg-gated 0xe00/0xe05).
//   ph3 (FUN_8018a2b0, 38i): while +0x55c > 0.0 drain it + tick stream; drain +0x558;
//       exit when +0x558 <= 0.0.
// ----------------------------------------------------------------------------
function action2(actor: SiriusActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: {
      if (!hasTarget(actor) || !allocateWeapon(actor, ctx, 2, 1, true)) {
        actor.fbPhaseSlots[0] = 3; // bail to cooldown (phase 3)
        actor.handlerTimer = SIRIUS.BAIL_COOLDOWN_SEED; // +0x558 = 10.0 (FLOAT_8043b000)
        return;
      }
      actor.fbPhaseSlots[0] = 1;
      // TODO: zz_0066408_ aim-classify + DAT_80362ce4 lookup → +0x145. Unsurfaced → 0.
      actor.siriusType145 = 0;
      actor.handlerTimer = SIRIUS.A2_MAIN_TIMER_SEED; // +0x558 = 60.0 (FLOAT_8043b050)
      return;
    }
    case 1: {
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      const streamEvent = tickSiriusStream(actor, actor.siriusType145 ?? 0, 1); // zz_018a6fc_
      if (streamEvent === 0 && SIRIUS.THRESHOLD < actor.handlerTimer) return;
      actor.fbPhaseSlots[0] = 2;
      return;
    }
    case 2: {
      actor.fbPhaseSlots[0] = 3;
      actor.handlerTimer = SIRIUS.A2_MAIN_TIMER_SEED; // +0x558 = 60.0 (FLOAT_8043b050)
      actor.siriusCooldown55c = SIRIUS.A0_PHASE1_SEED; // +0x55c = 20.0 (FLOAT_8043b02c)
      tickSiriusStream(actor, actor.siriusType145 ?? 0, 1); // zz_018a6fc_
      ctx.onFamilyProjectile?.(actor, SIRIUS_BEAM_SPAWNER, actor.siriusType145 ?? 0); // FUN_801f2bf8
      return;
    }
    case 3: {
      if (SIRIUS.THRESHOLD < (actor.siriusCooldown55c ?? 0)) {
        actor.siriusCooldown55c = (actor.siriusCooldown55c ?? 0) - actor.dt; // +0x55c -= dt
        tickSiriusStream(actor, actor.siriusType145 ?? 0, 1); // zz_018a6fc_
      }
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      if (actor.handlerTimer <= SIRIUS.THRESHOLD) {
        exitAction(actor, 0); // zz_006a53c_(actor, 0)
      }
      return;
    }
    default: return;
  }
}

// ----------------------------------------------------------------------------
// Action 3 — dual-weapon barrage (table @0x80362d04, 4 phases).
//   ph0 (FUN_8018a388, 14i — decoded from PPC, Ghidra did not emit it):
//       advance, seed +0x558=60.0, zero volley state/cursors, seed sub-timers 0.0.
//   ph1 (FUN_8018a3c0, 41i): drain +0x558; tick all 8 ports via zz_018a6fc_(i,0);
//       advance when port-0 fires OR +0x558 <= 0.0; seed +0x558=12.0.
//   ph2 (FUN_8018a464, 143i): drain +0x558 (wait gate); then drain +0x560/+0x564 and
//       run two parallel volley loops (weapon 0 via zz_01fc1b0_, weapon 2 via
//       FUN_801f2bf8), 2 shots/cycle, ammo-gated per shot, until both done-latches
//       set; advance to ph3 with +0x558=30.0.
//   ph3 (FUN_8018a6a0, 23i): drain +0x558; exit when <= 0.0.
// ----------------------------------------------------------------------------
function action3(actor: SiriusActor, ctx: StreamContext): void {
  const phase = actor.fbPhaseSlots[0] ?? 0;
  switch (phase) {
    case 0: {
      // FUN_8018a388 — decoded from boot.dol PPC (r2 base 0x8043ea20).
      actor.fbPhaseSlots[0] = 1; // +0x540 += 1
      actor.handlerTimer = SIRIUS.A2_MAIN_TIMER_SEED; // +0x558 = 60.0 (FLOAT_8043b050)
      actor.siriusVolleyState542 = 0; // +0x542 = 0
      actor.siriusVolleyCursor54c = 0; // +0x54c = 0
      actor.siriusVolleyTimer560 = SIRIUS.THRESHOLD; // +0x560 = 0.0 (FLOAT_8043b00c)
      actor.siriusVolleyState543 = 0; // +0x543 = 0
      actor.siriusVolleyCursor54e = 0; // +0x54e = 0
      actor.siriusVolleyTimer564 = SIRIUS.THRESHOLD; // +0x564 = 0.0 (FLOAT_8043b00c)
      return;
    }
    case 1: {
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      let port0 = 0;
      for (let i = 0; i < 8; i += 1) {
        const r = tickSiriusStream(actor, i, 0); // zz_018a6fc_(actor, i, 0)
        if (i === 0) port0 = r;
      }
      if (port0 === 0 && SIRIUS.THRESHOLD < actor.handlerTimer) return;
      actor.fbPhaseSlots[0] = 2; // +0x540 += 1
      actor.handlerTimer = SIRIUS.A3_PHASE1_EXIT_SEED; // +0x558 = 12.0 (FLOAT_8043b054)
      return;
    }
    case 2: {
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      if (SIRIUS.THRESHOLD < actor.handlerTimer) return; // wait gate
      actor.siriusVolleyTimer560 = (actor.siriusVolleyTimer560 ?? 0) - actor.dt; // +0x560 -= dt
      actor.siriusVolleyTimer564 = (actor.siriusVolleyTimer564 ?? 0) - actor.dt; // +0x564 -= dt
      let advance = 0;
      const s542 = actor.siriusVolleyState542 ?? 0;
      if (s542 === 1) {
        advance = 1; // weapon-0 volley already complete
      } else if (s542 < 1 && s542 >= 0 && (actor.siriusVolleyTimer560 ?? 0) <= SIRIUS.THRESHOLD) {
        // Weapon-0 volley: 2 shots per cycle (FUN_8018a464:3222-3240).
        for (let i = 0; i < 2; i += 1) {
          // TODO: shotType = DAT_80362d14[i + cursor54c*2] (table unsurfaced) → 0.
          const shotType = 0;
          if (shotType >= 0) {
            if (allocateWeapon(actor, ctx, 0, 1, true)) {
              ctx.onFamilyProjectile?.(actor, SIRIUS_SHOT_SPAWNER, shotType); // zz_01fc1b0_
            }
            // else zz_0011cc4_(slot, 0) — TODO: ammo-fail feedback (unsurfaced).
          }
        }
        actor.siriusVolleyTimer560 = SIRIUS.A3_VOLLEY_RESET; // +0x560 = 6.0 (FLOAT_8043b058)
        actor.siriusVolleyCursor54c = (actor.siriusVolleyCursor54c ?? 0) + 1;
        if ((actor.siriusVolleyCursor54c ?? 0) > SIRIUS.A3_W0_CURSOR_CAP) {
          actor.siriusVolleyState542 = (actor.siriusVolleyState542 ?? 0) + 1;
          advance = 1;
        }
      }
      const s543 = actor.siriusVolleyState543 ?? 0;
      if (s543 !== 1) {
        if (s543 !== 0 || SIRIUS.THRESHOLD < (actor.siriusVolleyTimer564 ?? 0)) {
          // not ready for weapon-2 volley this frame — skip (goto LAB_8018a670).
        } else {
          // Weapon-2 volley: 2 shots per cycle (FUN_8018a464:3246-3264).
          for (let i = 0; i < 2; i += 1) {
            // TODO: shotType = DAT_80362d2c[i + cursor54e*2] (table unsurfaced) → 0.
            const shotType = 0;
            if (shotType >= 0) {
              if (allocateWeapon(actor, ctx, 2, 1, true)) {
                ctx.onFamilyProjectile?.(actor, SIRIUS_BEAM_SPAWNER, shotType); // FUN_801f2bf8
              }
              // else zz_0011cc4_(slot, 2) — TODO: ammo-fail feedback (unsurfaced).
            }
          }
          actor.siriusVolleyTimer564 = SIRIUS.A3_VOLLEY_RESET; // +0x564 = 6.0 (FLOAT_8043b058)
          actor.siriusVolleyCursor54e = (actor.siriusVolleyCursor54e ?? 0) + 1;
          if ((actor.siriusVolleyCursor54e ?? 0) < SIRIUS.A3_W2_CURSOR_CAP) {
            // not yet capped — skip the advance contribution (goto LAB_8018a670).
          } else {
            actor.siriusVolleyState543 = (actor.siriusVolleyState543 ?? 0) + 1;
            advance += 1;
          }
        }
      } else {
        advance += 1; // weapon-2 volley already complete
      }
      if (advance === 2) {
        actor.fbPhaseSlots[0] = 3; // +0x540 += 1
        actor.handlerTimer = SIRIUS.A3_PHASE3_SEED; // +0x558 = 30.0 (FLOAT_8043b05c)
      }
      return;
    }
    case 3: {
      actor.handlerTimer -= actor.dt; // +0x558 -= dt
      if (actor.handlerTimer <= SIRIUS.THRESHOLD) {
        exitAction(actor, 0); // zz_006a53c_(actor, 0)
      }
      return;
    }
    default: return;
  }
}

// ----------------------------------------------------------------------------
// Root dispatcher — FUN_80189cf0 indexes PTR_FUN_80362c98[+0x580] (actionIndex).
// SIRIUS routes actions 0/2/3 to their phase tables; other indices fall through.
// ----------------------------------------------------------------------------
export function createSiriusRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: action0(actor, ctx); return;
      case 2: action2(actor, ctx); return;
      case 3: action3(actor, ctx); return;
      default: return;
    }
  };
}

export function configureSiriusFamily(
  actor: RomActor,
  borgId: SiriusBorgId,
  ctx: StreamContext,
): void {
  actor.borgNumber = SIRIUS_BORG_NUMBERS[borgId] ?? 0;
  actor.rootAction = createSiriusRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

// ============================================================================
// Self-tests — mirrors rom.selfcheck.ts style. Covers each action's phase
// transitions, the ammo-gate bail, and the borg-gated beam spawn routing.
// ============================================================================
export function runSiriusSelfTests(assert: (cond: boolean, msg: string) => void): void {
  type Shot = { addr: number; type: number };
  const target = { eligibility83: 0, controlWord: 0, visibilityMask5e6: 0 };

  // --- pl0e00 action 0: 3-phase aimed single-shot. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActorSirius());
    configureSiriusFamily(a, "pl0e00", sctx);
    assert(a.borgNumber === 0xe00, "pl0e00 borgNumber stamped 0xe00");
    assert(a.rootAction !== null, "sirius bespoke rootAction wired");
    const root = a.rootAction!;
    a.visibilityTarget = target;
    a.actionIndex = 0;
    a.dt = 1;
    root(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1 && a.handlerTimer === SIRIUS.A0_MAIN_TIMER_SEED,
      "action 0 ph0 seeds +0x558=3.0 and advances (target + ammo OK)");
    assert(a.siriusScratch548 === SIRIUS.A0_SCRATCH548, "action 0 ph0 arms +0x548=8");
    root(a); // ph1 spawn
    assert(a.fbPhaseSlots[0] === 2 && a.handlerTimer === SIRIUS.A0_PHASE1_SEED,
      "action 0 ph1 advances and seeds +0x558=20.0");
    assert(shots.length === 1 && shots[0]!.addr === SIRIUS_SHOT_SPAWNER,
      `action 0 ph1 spawns zz_01fc1b0_ (got ${JSON.stringify(shots)})`);
    // ph2 cooldown drain → exit (zz_006a53c_(0) dispatches cue 0x1b which resets
    // +0x540..+0x543; verify the exit cleared the action-mode bits + housekeeping).
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 20; i += 1) root(a);
    assert(a.housekeeping73f === 0 && a.controlWord === 0,
      "action 0 ph2 exits (clears +0x73f, strips +0x5e0) when +0x558 <= 0.0");
  }

  // --- pl0e00 action 0 ammo-fail bail: jumps straight to phase 2 (cooldown). ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => false,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActorSirius());
    configureSiriusFamily(a, "pl0e00", sctx);
    a.visibilityTarget = target;
    a.actionIndex = 0;
    a.dt = 1;
    a.rootAction!(a); // ph0 ammo-fail bail
    assert(a.fbPhaseSlots[0] === 2 && a.handlerTimer === SIRIUS.BAIL_COOLDOWN_SEED,
      "action 0 ph0 ammo-fail bails to phase 2 with +0x558=10.0");
    assert(shots.length === 0, "action 0 ammo-fail suppresses spawn");
  }

  // --- pl0e00 action 0 no-target bail: jumps straight to phase 2. ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true, onFamilyProjectile: () => {} };
    const a = scratchOf(createRomActorSirius());
    configureSiriusFamily(a, "pl0e00", sctx);
    a.visibilityTarget = null; // +0xcc == 0
    a.actionIndex = 0;
    a.rootAction!(a);
    assert(a.fbPhaseSlots[0] === 2 && a.handlerTimer === SIRIUS.BAIL_COOLDOWN_SEED,
      "action 0 ph0 no-target (+0xcc==0) bails to phase 2 with +0x558=10.0");
  }

  // --- pl0e05 action 2: 4-phase aimed beam. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActorSirius());
    configureSiriusFamily(a, "pl0e05", sctx);
    assert(a.borgNumber === 0xe05, "pl0e05 borgNumber stamped 0xe05");
    const root = a.rootAction!;
    a.visibilityTarget = target;
    a.actionIndex = 2;
    a.dt = 1;
    root(a); // ph0 setup
    assert(a.fbPhaseSlots[0] === 1 && a.handlerTimer === SIRIUS.A2_MAIN_TIMER_SEED,
      "action 2 ph0 seeds +0x558=60.0 and advances");
    for (let i = 0; i < 60; i += 1) root(a); // ph1 drain (stream no-op → timer gate)
    assert(a.fbPhaseSlots[0] === 2, "action 2 ph1 advances when +0x558 <= 0.0");
    root(a); // ph2 spawn
    assert(a.fbPhaseSlots[0] === 3 && a.handlerTimer === SIRIUS.A2_MAIN_TIMER_SEED
      && a.siriusCooldown55c === SIRIUS.A0_PHASE1_SEED,
      "action 2 ph2 advances, seeds +0x558=60.0 / +0x55c=20.0");
    assert(shots.length === 1 && shots[0]!.addr === SIRIUS_BEAM_SPAWNER,
      `action 2 ph2 spawns FUN_801f2bf8 (borg-gated 0xe00/0xe05) (got ${JSON.stringify(shots)})`);
    // ph3: drain +0x55c (20f) then +0x558 (60f total) → exit.
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 60; i += 1) root(a);
    assert(a.housekeeping73f === 0 && a.controlWord === 0,
      "action 2 ph3 exits when +0x558 <= 0.0 (clears +0x73f, strips +0x5e0)");
  }

  // --- pl0e05 action 2 ammo-fail bail: jumps to phase 3 (cooldown). ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => false,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActorSirius());
    configureSiriusFamily(a, "pl0e05", sctx);
    a.visibilityTarget = target;
    a.actionIndex = 2;
    a.rootAction!(a); // ph0 ammo-fail bail
    assert(a.fbPhaseSlots[0] === 3 && a.handlerTimer === SIRIUS.BAIL_COOLDOWN_SEED,
      "action 2 ph0 ammo-fail bails to phase 3 with +0x558=10.0");
    assert(shots.length === 0, "action 2 ammo-fail suppresses beam spawn");
  }

  // --- pl0e00 action 3: 4-phase dual-weapon barrage (phase 0 decoded stub). ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = scratchOf(createRomActorSirius());
    configureSiriusFamily(a, "pl0e00", sctx);
    const root = a.rootAction!;
    a.visibilityTarget = target;
    a.actionIndex = 3;
    a.dt = 1;
    root(a); // ph0 setup (FUN_8018a388 decoded stub)
    assert(a.fbPhaseSlots[0] === 1 && a.handlerTimer === SIRIUS.A2_MAIN_TIMER_SEED,
      "action 3 ph0 seeds +0x558=60.0 and advances");
    assert(a.siriusVolleyState542 === 0 && a.siriusVolleyState543 === 0,
      "action 3 ph0 zeros volley done-latches +0x542/+0x543");
    assert(a.siriusVolleyCursor54c === 0 && a.siriusVolleyCursor54e === 0,
      "action 3 ph0 zeros volley cursors +0x54c/+0x54e");
    assert(a.siriusVolleyTimer560 === SIRIUS.THRESHOLD && a.siriusVolleyTimer564 === SIRIUS.THRESHOLD,
      "action 3 ph0 seeds volley sub-timers +0x560/+0x564 = 0.0");
    for (let i = 0; i < 60; i += 1) root(a); // ph1 drain (8-port stream no-op → timer gate)
    assert(a.fbPhaseSlots[0] === 2 && a.handlerTimer === SIRIUS.A3_PHASE1_EXIT_SEED,
      "action 3 ph1 advances when +0x558 <= 0.0 and seeds +0x558=12.0");
    // ph2: 12-frame wait gate, then volley. Drive enough frames to complete both weapons.
    let prevShots = 0;
    let sawShot = false;
    let sawBeam = false;
    for (let i = 0; i < 200 && a.fbPhaseSlots[0] === 2; i += 1) {
      root(a);
      for (const s of shots.slice(prevShots)) {
        if (s.addr === SIRIUS_SHOT_SPAWNER) sawShot = true;
        if (s.addr === SIRIUS_BEAM_SPAWNER) sawBeam = true;
      }
      prevShots = shots.length;
    }
    assert(sawShot && sawBeam, "action 3 ph2 fires both zz_01fc1b0_ (weapon 0) and FUN_801f2bf8 (weapon 2)");
    assert(a.fbPhaseSlots[0] === 3 && a.handlerTimer === SIRIUS.A3_PHASE3_SEED,
      "action 3 ph2 advances to phase 3 with +0x558=30.0 when both volleys complete");
    // ph3 cooldown drain → exit.
    a.controlWord = 0x3; a.housekeeping73f = 1;
    for (let i = 0; i < 30; i += 1) root(a);
    assert(a.housekeeping73f === 0 && a.controlWord === 0,
      "action 3 ph3 exits when +0x558 <= 0.0");
  }

  // --- pl0e05 borg-gate confirmation: action 2 routes FUN_801f2bf8 for both members. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    for (const id of ["pl0e00", "pl0e05"] as const) {
      shots.length = 0;
      const a = scratchOf(createRomActorSirius());
      configureSiriusFamily(a, id, sctx);
      a.visibilityTarget = target;
      a.actionIndex = 2;
      a.dt = 1;
      // ph0 (1 call) + ph1 drain (60 calls) + ph2 spawn (1 call) = 62 calls.
      for (let i = 0; i < 62; i += 1) a.rootAction!(a);
      assert(shots.some((s) => s.addr === SIRIUS_BEAM_SPAWNER),
        `${id} action 2 routes FUN_801f2bf8 (borg-gated 0xe00/0xe05 pass)`);
    }
  }
}

/** Test helper — create a blank actor with a Sirus cue table attached. */
function createRomActorSirius(): RomActor {
  const a = createRomActor();
  a.cueTable = new Int8Array(96).fill(-1);
  a.cueTable[SIRIUS.EXIT_CUE * 2] = 61; // cue 0x1b → state 61 (stays in attack)
  return a;
}

// ----------------------------------------------------------------------------
// Named const exports for spawner addresses + floats (audit surface).
// ----------------------------------------------------------------------------
export const SIRIUS_CONSTANTS = SIRIUS;
export const SIRIUS_SHOT_SPAWNER_ADDR = SIRIUS_SHOT_SPAWNER;
export const SIRIUS_BEAM_SPAWNER_ADDR = SIRIUS_BEAM_SPAWNER;
