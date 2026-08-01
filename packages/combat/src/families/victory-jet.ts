// VICTORY JET (pl0620, ctor 0x8015bd74) victory-jet family — bespoke action-3 port.
//
// The ctor wires the root dispatcher FUN_8015c588 (chunk_0041.c:255) → zz_015c5a8_
// (chunk_0041.c:266), which indexes PTR_FUN_80346284[+0x540] (the fbPhaseSlots[0]
// phase cursor). Only actionIndex 3 (B-charge) routes to this 4-phase machine; the
// other action rows fall through to the generic combat layer (null rootAction).
//
//   action 3 table @0x80346284 = [FUN_8015c5e4(47i), FUN_8015c6a0(18i),
//                                 FUN_8015c6e8(67i), FUN_8015c7f4(23i)]
//
// Source: research/decomp/ghidra-export/chunk_0041.c:277-382. The four phases:
//   0 arm   — ammo gate (zz_006dbe0_(actor,2,1,1)): on denial exit via zz_006a53c_(8)
//             + override +0x694 = 16.0; on success advance +0x540, set +0x6ea = 5,
//             +0x558 = 0.0, start stream (zz_004beb8_ mask 0xf group 2 slot 0).
//   1 wait  — tick stream (zz_004cd24_(actor,0xf)); advance when +0x1b03 (streamHold)
//             is 0 (stream completed). Without extracted banks the hold is 0 on entry,
//             so the advance is immediate (the exact ROM behavior with no bank bound).
//   2 spawn — drain +0x558 by dt; when <= 0.0 re-seed 12.0, decrement +0x6ea, and:
//               if +0x6ea < 0 → advance to ph3 + arm cooldown stream (group 0 slot 0);
//               else borg-switched child spawn via zz_00fcd38_(actor, type, 0):
//                 0x612→1, 0x620→3, 0x624→4, 0x626→5; then +0x144 = 1.
//             pl0620 (0x620) is the only registered member → type 3.
//   3 exit  — tick stream; when +0x1b03 == 0 exit via zz_006a53c_(actor, 8).
//
// Float constants (read from boot.dol via v2f, sdata2 base rtoc=0x8043ea20):
//   FLOAT_8043a778 = 0.0    ph0/2 threshold (+0x558 <= this → spawn/advance)
//   FLOAT_8043a77c = -1.0   zz_004beb8_ stream rate (cosmetic)
//   FLOAT_8043a784 = 16.0   ph0 ammo-denied override of +0x694
//   FLOAT_8043a788 = 12.0   ph2 inter-shot +0x558 re-seed
//
// Exit helper zz_006a53c_(actor, param) @ chunk_0009.c:750 (see fighter-craft.ts):
// if param>0 +0x694 = param+dt; +0x73f = 0; +0x5e0 &= ~3; dispatch cue 0x1b.
// ph0's denied branch then overrides +0x694 = 16.0 + dt (the literal post-call store).

import { createRomActor, type RomActor } from "../rom/actor.js";
import { dispatchFullBodyCue } from "../rom/dispatch.js";
import { allocateWeapon } from "../rom/helpers.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";

/** Borg number for VICTORY JET. The phase-2 spawn switch also covers pl0612/pl0624/
 *  pl0626 (sharing this machine in the ROM) but only pl0620 is registered here. */
const VICTORY_JET_BORG_NUMBER = 0x620;

// ----------------------------------------------------------------------------
// Config constants (DOL-read this session; sdata2 @0x8043a7xx).
// ----------------------------------------------------------------------------
const VICTORY_JET = {
  /** FLOAT_8043a778 = 0.0 — ph2 spawn/advance threshold (+0x558 <= this). */
  THRESHOLD: 0.0,
  /** FLOAT_8043a77c = -1.0 — zz_004beb8_ stream rate. */
  STREAM_RATE: -1.0,
  /** FLOAT_8043a784 = 16.0 — ph0 ammo-denied override of +0x694. */
  DENIED_STATE_TIMER_SEED: 16.0,
  /** FLOAT_8043a788 = 12.0 — ph2 inter-shot +0x558 re-seed. */
  SHOT_INTERVAL: 12.0,
  /** ph0 stream-slot seed (+0x6ea = 5 → 6 spawns before ph3). */
  STREAM_SLOT_SEED: 5,
  /** zz_006a53c_ exit param (ph0 denied + ph3 exit). */
  EXIT_PARAM: 8,
  /** zz_006a53c_ full-body exit cue. */
  EXIT_CUE: 0x1b,
  /** +0x5e0 action-mode bits stripped at exit. */
  ACTION_MODE_BITS: 0x3,
  /** Stream mask passed to zz_004beb8_ / zz_004cd24_ (all 4 parts). */
  STREAM_MASK: 0xf,
} as const;

// ----------------------------------------------------------------------------
// Spawner addresses.
// ----------------------------------------------------------------------------
/** zz_00fcd38_ — dual-port child spawn (the ORANGE FIGHTER hardpoint spawner; shared
 *  by the VICTORY JET phase-2 borg switch). Borg-switched type arg: 0x612→1, 0x620→3,
 *  0x624→4, 0x626→5. */
const DUAL_PORT_SPAWNER = 0x800fcd38;

// ----------------------------------------------------------------------------
// Scratch mirrors for ROM offsets not first-class on RomActor.
// ----------------------------------------------------------------------------
export interface VictoryJetScratch {
  /** +0x144: hardpoint/child ownership latch (set to 1 after each ph2 spawn). */
  victoryJetChildLatch144?: number;
  /** +0x6ea: stream-slot countdown (ph0 seeds 5; ph2 decrements per shot). */
  victoryJetStreamSlot6ea?: number;
  /** +0x1b03: stream/animation hold byte (gates ph1/ph3 advance; 0 without banks). */
  streamHold1b03?: number;
}

type VictoryJetActor = RomActor & VictoryJetScratch;

function scratchOf(actor: RomActor): VictoryJetActor {
  return actor as VictoryJetActor;
}

// ----------------------------------------------------------------------------
// zz_006a53c_(actor, param) — chunk_0009.c:750. Mirrors fighter-craft.ts exitAction.
// ----------------------------------------------------------------------------
function exitAction(actor: RomActor, param: number): void {
  if (param > 0) {
    actor.stateTimer = param + actor.dt;
  }
  actor.housekeeping73f = 0;
  actor.controlWord = actor.controlWord & ~VICTORY_JET.ACTION_MODE_BITS;
  dispatchFullBodyCue(actor, VICTORY_JET.EXIT_CUE);
}

// ----------------------------------------------------------------------------
// Phase 0 — arm. FUN_8015c5e4 @ chunk_0041.c:277 (47 instrs).
// ----------------------------------------------------------------------------
function victoryJetPhase0Arm(actor: VictoryJetActor, ctx: StreamContext): void {
  // zz_006dbe0_(actor, 2, 1, 1) returns 0 when ammo is denied.
  const ammoOk = allocateWeapon(actor, ctx, 2, 1, true);
  if (actor.borgNumber === VICTORY_JET_BORG_NUMBER && !ammoOk) {
    // Denied branch: exit, then override +0x694 = 16.0 + dt.
    exitAction(actor, VICTORY_JET.EXIT_PARAM);
    actor.stateTimer = VICTORY_JET.DENIED_STATE_TIMER_SEED + actor.dt;
    return;
  }
  // Success branch: advance + arm stream.
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  actor.victoryJetStreamSlot6ea = VICTORY_JET.STREAM_SLOT_SEED; // +0x6ea = 5
  actor.handlerTimer = VICTORY_JET.THRESHOLD;                   // +0x558 = 0.0
  // zz_004beb8_(rate, actor, mask=0xf, group=2, slot=0, -1, -1)
  startStream(actor, VICTORY_JET.STREAM_MASK, 2, 0, VICTORY_JET.STREAM_RATE);
}

// ----------------------------------------------------------------------------
// Phase 1 — wait. FUN_8015c6a0 @ chunk_0041.c:305 (18 instrs).
// ----------------------------------------------------------------------------
function victoryJetPhase1Wait(actor: VictoryJetActor, ctx: StreamContext): void {
  // zz_004cd24_(actor, 0xf) — tick all 4 parts' action stream.
  tickStream(actor, VICTORY_JET.STREAM_MASK, ctx);
  if ((actor.streamHold1b03 ?? 0) === 0) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
  }
}

// ----------------------------------------------------------------------------
// Phase 2 — spawn loop. FUN_8015c6e8 @ chunk_0041.c:319 (67 instrs).
// ----------------------------------------------------------------------------
function victoryJetPhase2Spawn(actor: VictoryJetActor, ctx: StreamContext): void {
  if (actor.handlerTimer <= VICTORY_JET.THRESHOLD) {
    actor.handlerTimer = VICTORY_JET.SHOT_INTERVAL; // +0x558 = 12.0
    const slot = (actor.victoryJetStreamSlot6ea ?? 0) - 1;
    actor.victoryJetStreamSlot6ea = slot;           // +0x6ea--
    if (slot < 0) {
      // Done looping → advance to ph3 + arm cooldown stream.
      actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1;
      // zz_004beb8_(-1.0, actor, 0xf, 0, 0, 10, 1)
      startStream(actor, VICTORY_JET.STREAM_MASK, 0, 0, VICTORY_JET.STREAM_RATE);
    } else {
      // zz_006bda8_(actor) — host-only housekeeping (no port-side effect).
      // Borg-switched zz_00fcd38_(actor, type, 0).
      const type = victoryJetChildType(actor.borgNumber);
      ctx.onFamilyProjectile?.(actor, DUAL_PORT_SPAWNER, type);
      actor.victoryJetChildLatch144 = 1; // +0x144 = 1
    }
    return;
  }
  actor.handlerTimer -= actor.dt; // +0x558 -= dt
}

/** Borg-switched type arg for zz_00fcd38_ (chunk_0041.c:342-357). */
function victoryJetChildType(borgNumber: number): number {
  switch (borgNumber) {
    case 0x612: return 1;
    case 0x620: return 3;
    case 0x624: return 4;
    case 0x626: return 5;
    default: return 3; // pl0620 fallback
  }
}

// ----------------------------------------------------------------------------
// Phase 3 — exit. FUN_8015c7f4 @ chunk_0041.c:370 (23 instrs).
// ----------------------------------------------------------------------------
function victoryJetPhase3Exit(actor: VictoryJetActor, ctx: StreamContext): void {
  tickStream(actor, VICTORY_JET.STREAM_MASK, ctx);
  if ((actor.streamHold1b03 ?? 0) === 0) {
    exitAction(actor, VICTORY_JET.EXIT_PARAM);
  }
}

// ----------------------------------------------------------------------------
// Root action dispatcher. Only actionIndex 3 routes to the phase machine; other
// action indices fall through (no-op) so the generic combat layer owns them.
// ----------------------------------------------------------------------------
export function createVictoryJetRootAction(
  ctx: StreamContext,
): (actor: RomActor) => void {
  return (base: RomActor) => {
    if (base.actionIndex !== 3) return;
    const actor = scratchOf(base);
    const phase = actor.fbPhaseSlots[0] ?? 0;
    switch (phase) {
      case 0: victoryJetPhase0Arm(actor, ctx); return;
      case 1: victoryJetPhase1Wait(actor, ctx); return;
      case 2: victoryJetPhase2Spawn(actor, ctx); return;
      case 3: victoryJetPhase3Exit(actor, ctx); return;
      default: return;
    }
  };
}

/** Configure a freshly-spawned VICTORY JET (pl0620). Stamps the borg number and wires
 *  the bespoke action-3 spawn machine. */
export function configureVictoryJetFamily(actor: RomActor, ctx: StreamContext): void {
  actor.borgNumber = VICTORY_JET_BORG_NUMBER;
  actor.rootAction = createVictoryJetRootAction(ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

export const VICTORY_JET_CONSTANTS = VICTORY_JET;
export const VICTORY_JET_DUAL_PORT_SPAWNER = DUAL_PORT_SPAWNER;

// ============================================================================
// Self-tests. Mirror the rom.selfcheck.ts MU/ROACH style: createRomActor + ctx with
// onAllocateResource:true + onFamilyProjectile collector; drive the rootAction;
// assert phase transitions + spawn types.
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

export function runVictoryJetSelfTests(assert: AssertFn): void {
  type Shot = { addr: number; type: number };

  // --- pl0620 ph0: success arm (ammo available) → ph1, +0x6ea=5, +0x558=0.0. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as RomActor & VictoryJetScratch;
    configureVictoryJetFamily(a, sctx);
    assert(a.borgNumber === 0x620, "pl0620 borgNumber stamped 0x620");
    assert(a.rootAction !== null, "victory-jet bespoke rootAction wired");
    const root = a.rootAction!;
    a.actionIndex = 3;
    a.dt = 1;
    root(a); // ph0 arm (ammo ok)
    assert(a.fbPhaseSlots[0] === 1, "VJ ph0 advances to ph1 on ammo success");
    assert(a.victoryJetStreamSlot6ea === 5, "VJ ph0 seeds +0x6ea = 5");
    assert(a.handlerTimer === 0.0, "VJ ph0 seeds +0x558 = 0.0 (FLOAT_8043a778)");
    assert(shots.length === 0, "VJ ph0 does not spawn");
  }

  // --- pl0620 ph0: ammo-denied exit (zz_006a53c_(8) + override +0x694 = 16+dt). ---
  {
    const sctx: StreamContext = {
      onAllocateResource: () => false, // ammo denied
    };
    const a = createRomActor() as RomActor & VictoryJetScratch;
    configureVictoryJetFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 3;
    a.dt = 1;
    a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a); // ph0 arm (denied)
    assert(a.fbPhaseSlots[0] === 0, "VJ ph0 denied does NOT advance +0x540");
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "VJ ph0 denied clears +0x73f and strips +0x5e0 action bits");
    assert(a.stateTimer === 16.0 + 1, "VJ ph0 denied overrides +0x694 = 16.0 + dt (FLOAT_8043a784)");
  }

  // --- pl0620 ph1 → ph2 → ph2 spawn loop (6 shots of zz_00fcd38_(3)) → ph3 → exit. ---
  {
    const shots: Shot[] = [];
    const sctx: StreamContext = {
      onAllocateResource: () => true,
      onFamilyProjectile: (_a, addr, type) => shots.push({ addr, type }),
    };
    const a = createRomActor() as RomActor & VictoryJetScratch;
    configureVictoryJetFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 3; a.dt = 1;
    root(a); // ph0 → ph1
    assert(a.fbPhaseSlots[0] === 1, "VJ ph0 → ph1");
    // ph1: streamHold==0 (no banks) → advance immediately.
    root(a); // ph1 → ph2
    assert(a.fbPhaseSlots[0] === 2, "VJ ph1 advances to ph2 when streamHold == 0");

    // ph2 first tick: +0x558 (0.0) <= 0.0 → re-seed 12.0, slot 5→4, spawn type 3.
    root(a);
    assert(shots.length === 1 && shots[0]!.addr === VICTORY_JET_DUAL_PORT_SPAWNER && shots[0]!.type === 3,
      `VJ ph2 first spawn zz_00fcd38_(3) (got ${JSON.stringify(shots)})`);
    assert(a.victoryJetStreamSlot6ea === 4 && a.handlerTimer === 12.0,
      "VJ ph2 re-seeds +0x558=12.0 and decrements +0x6ea to 4");
    assert(a.victoryJetChildLatch144 === 1, "VJ ph2 sets +0x144 = 1 after spawn");

    // Each subsequent spawn needs 13 ticks: 12 drains (12.0→0.0) + 1 spawn tick.
    // Shots #2..#5 fire while slot walks 3→2→1→0 (>= 0 branch).
    for (let shotIdx = 2; shotIdx <= 5; shotIdx += 1) {
      for (let f = 0; f < 13; f += 1) root(a);
      assert(shots.length === shotIdx, `VJ ph2 fires shot ${shotIdx} (slot ${5 - shotIdx})`);
      assert(a.fbPhaseSlots[0] === 2, `VJ ph2 stays in ph2 after shot ${shotIdx}`);
    }
    // 6th spawn tick: slot 0 → -1 (< 0 branch) → advance to ph3, NO spawn.
    for (let f = 0; f < 13; f += 1) root(a);
    assert(shots.length === 5, `VJ ph2 fires 5 total shots (got ${shots.length})`);
    assert(a.fbPhaseSlots[0] === 3, "VJ ph2 advances to ph3 when +0x6ea < 0");

    // ph3: streamHold==0 → exit via zz_006a53c_(8).
    a.controlWord = 0x3; a.housekeeping73f = 1;
    root(a);
    assert(a.housekeeping73f === 0 && (a.controlWord & 0x3) === 0,
      "VJ ph3 exit clears +0x73f and strips +0x5e0 action bits");
    assert(a.stateTimer === 8 + 1, "VJ ph3 exit seeds +0x694 = 8 + dt (zz_006a53c_(8))");
  }

  // --- Non-action-3 indices fall through (no-op). ---
  {
    const sctx: StreamContext = { onAllocateResource: () => true };
    const a = createRomActor() as RomActor & VictoryJetScratch;
    configureVictoryJetFamily(a, sctx);
    const root = a.rootAction!;
    a.actionIndex = 0; // not 3
    a.fbPhaseSlots[0] = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "VJ rootAction no-ops for actionIndex != 3");
  }
}
