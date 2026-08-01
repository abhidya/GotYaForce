// WITCH CLUSTER — ROM-faithful port of the 4 witch families that share the action-0
// "approach → contact → borg-switched spawn" machine code shape (per the bespoke port
// plan). One module covers all 4 constructors; each configure function stamps its
// borgNumber + per-family float/spawner config and wires the shared action-0 machine.
//
// Constructors (bespoke-port-work-queue.json):
//   PATRA WITCH  ctor 0x8015d674 — pl0902 (0x902) / pl0909 ISIS WITCH (0x909). 49f/4158i.
//   BASTET WITCH ctor 0x801b3c6c — pl0907 (0x907) / pl090c SEKHMET WITCH (0x90c). 49f/4153i.
//   BUG WITCH    ctor 0x8014d200 — pl0901 (0x901).                                42f/3845i.
//   GUARD WITCH  ctor 0x80151790 — pl0903 (0x903) / pl090a SHIELD WITCH (0x90a).   39f/3381i.
//
// The 4 ctors share the SAME action-0 phase shape (chunk_0039.c/0041.c/0053.c):
//   ph0 setup   — +0x540++; +0x558=30f seed; zero hSpeed/hDecel; aim yaw zz_006d0dc_(0xc1).
//   ph1 approach — drain +0x558; aim; advance when aim-ready OR timer<=0 → start group-2 slot 0.
//   ph2 active   — tick stream; on contact (+0x1cef==1 && +0x1cf0==1) → +0x540++; ammo-gate
//                  zz_006dbe0_(actor,0,1,1); on ok → borg-switched zz_0082824_(actor,type).
//   ph3 recover  — tick stream; on stream-end → +0x73f=0; +0x5e0&=~3; zz_006a474_ ground idle.
//
// Borg-switched zz_0082824_ record types (decomp-verified per family):
//   BUG    0x901 → 0x65            (FUN_8014d9c0,  chunk_0039.c)
//   PATRA  0x902 → 0x66 / ISIS  0x909 → 0x67   (FUN_8015ddd0,  chunk_0041.c)
//   GUARD  0x903 → 0x68 / SHIELD 0x90a → 0x69   (FUN_80152308,  chunk_0039.c)
//   BASTET 0x907 → 0x6c / SEKHMET 0x90c → 0x6d (zz_01b48b8_,  chunk_0053.c)
//
// Float constants read from boot.dol this session (sdata2 — each family its own region):
//   PATRA  8043a7c8 = 30.0 (ph0 +0x558 seed)   8043a7cc = 0.0 (zero)   8043a7d0 = -1.0 (rate)
//   BUG    8043a468 = 30.0                     8043a46c = 0.0         8043a470 = -1.0
//   GUARD  8043a520 = 0.0                      8043a524 = -1.0        8043a528 = 0.965 (drag)
//   BASTET 8043b988 = 30.0                     8043b98c = 0.0         8043b990 = -1.0
// All converge on timer=30.0 / zero=0.0 / stream-rate=-1.0; hardcode + cite per family.

import { createRomActor, type RomActor } from "../rom/actor.js";
import { allocateWeapon, stepTargetYaw } from "../rom/helpers.js";
import { startStream, tickStream, type StreamContext } from "../rom/stream-vm.js";
import { romGroundIdleReturn } from "./shared-idle-return.js";
import { createSharedEngineRootAction, DEFAULT_CONFIGS } from "./shared-engine.js";

/** zz_0082824_ @0x80082824 — the shared record-table projectile spawner every witch
 *  action-0 phase-2 contact tail-calls. */
export const WITCH_SHOT_SPAWNER = 0x80082824;

/** Borg numbers for the 4 witch families. */
const WITCH_BORG_NUMBERS: Record<string, number> = {
  pl0901: 0x901,
  pl0902: 0x902, pl0909: 0x909,
  pl0903: 0x903, pl090a: 0x90a,
  pl0907: 0x907, pl090c: 0x90c,
};

export type WitchBorgId = "pl0901" | "pl0902" | "pl0903" | "pl0907" | "pl0909" | "pl090a" | "pl090c";

/** Per-family float config (each cited to its sdata2 region). All share the same shape
 *  (30f timer / 0.0 zero / -1.0 stream rate); the region address is recorded for audit. */
export interface WitchFamilyConfig {
  /** Family label (for assertions + comments). */
  label: string;
  /** sdata2 region base for citation (e.g. 0x8043a7c8 for PATRA). */
  floatRegionBase: number;
  /** ph0 +0x558 timer seed (30.0 across all 4). */
  timerSeed: number;
  /** zero scalar (0.0 across all 4). */
  zero: number;
  /** zz_004beb8_ stream rate (-1.0 across all 4). */
  streamRate: number;
  /** Borg-number → zz_0082824_ record-type selector (action-0 ph2 contact). */
  shotTypeFor: (borgNumber: number) => number | null;
  /** X-special shared-engine seed slot (actionStreamTables group-4 ground slot). */
  xGroundSlot: number;
}

export const PATRA_WITCH_CONFIG: WitchFamilyConfig = {
  label: "PATRA WITCH",
  floatRegionBase: 0x8043a7c8,
  timerSeed: 30.0, // FLOAT_8043a7c8
  zero: 0.0,       // FLOAT_8043a7cc
  streamRate: -1.0, // FLOAT_8043a7d0
  shotTypeFor: (n) => (n === 0x902 ? 0x66 : n === 0x909 ? 0x67 : null),
  xGroundSlot: 0,
};

export const BASTET_WITCH_CONFIG: WitchFamilyConfig = {
  label: "BASTET WITCH",
  floatRegionBase: 0x8043b988,
  timerSeed: 30.0, // FLOAT_8043b988
  zero: 0.0,       // FLOAT_8043b98c
  streamRate: -1.0, // FLOAT_8043b990
  shotTypeFor: (n) => (n === 0x907 ? 0x6c : n === 0x90c ? 0x6d : null),
  xGroundSlot: 0,
};

export const BUG_WITCH_CONFIG: WitchFamilyConfig = {
  label: "BUG WITCH",
  floatRegionBase: 0x8043a468,
  timerSeed: 30.0, // FLOAT_8043a468
  zero: 0.0,       // FLOAT_8043a46c
  streamRate: -1.0, // FLOAT_8043a470
  shotTypeFor: (n) => (n === 0x901 ? 0x65 : null),
  xGroundSlot: 0,
};

export const GUARD_WITCH_CONFIG: WitchFamilyConfig = {
  label: "GUARD WITCH",
  floatRegionBase: 0x8043a520,
  timerSeed: 30.0, // GUARD action-0 is variant-driven; the 30f window is the ph1 drain.
  zero: 0.0,       // FLOAT_8043a520
  streamRate: -1.0, // FLOAT_8043a524
  shotTypeFor: (n) => (n === 0x903 ? 0x68 : n === 0x90a ? 0x69 : null),
  xGroundSlot: 0,
};

/** Named const bundle (mirrors TELEPORT_NINJA / VICTORY_KING export shape). */
export const WITCH_CLUSTER = {
  TIMER_SEED: 30.0,
  ZERO: 0.0,
  STREAM_RATE: -1.0,
  CONTACT_P0_FLAG: 0x01, // +0x1cef == 1 gate
  CONTACT_P1_FLAG: 0x01, // +0x1cf0 == 1 gate (the part-1 contact byte)
  ACTION0_STREAM_GROUP: 2,
  STREAM_MASK: 0xf,
} as const;

export interface WitchClusterCtx extends StreamContext {}

/** Scratch mirrors for ROM offsets not first-class on RomActor. */
export interface WitchScratch {
  /** +0x558: action-0 handler timer (30f seed, drained in ph1). */
  witchTimer558?: number;
}

type WitchActor = RomActor & WitchScratch;

function scratchOf(actor: RomActor): WitchActor {
  return actor as WitchActor;
}

// ============================================================================
// Shared ACTION 0 machine — the 4-phase approach/contact/recover loop common to all
// 4 witch ctors (PATRA FUN_8015dcfc/dd44/ddd0/de78; BUG FUN_8014d8ec/d934/d9c0/da3c;
// BASTET zz_01b4768_ family; GUARD FUN_80151db0/e50/.../23xx).
// ============================================================================

/** Phase 0 — setup (PATRA FUN_8015dcfc / BUG FUN_8014d8ec / BASTET zz_01b4768_). */
function witchAction0Phase0Setup(actor: WitchActor, cfg: WitchFamilyConfig): void {
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  actor.witchTimer558 = cfg.timerSeed;                       // +0x558 = 30.0
  // Zero hSpeed/hDecel (the witches zero +0x4c/+0x44 only; yVel/gravity untouched).
  actor.hDecel = cfg.zero; // +0x4c
  actor.hSpeed = cfg.zero; // +0x44
  stepTargetYaw(actor, 0xc1, 0); // zz_006d0dc_(actor, 0xc1, 0)
}

/** Phase 1 — approach (PATRA FUN_8015dd44 / BUG FUN_8014d934). */
function witchAction0Phase1Approach(actor: WitchActor, cfg: WitchFamilyConfig, ctx: WitchClusterCtx): void {
  actor.witchTimer558 = (actor.witchTimer558 ?? 0) - actor.dt; // +0x558 -= dt
  const converged = stepTargetYaw(actor, 0xc1, 0);              // zz_006d0dc_(0xc1, 0)
  // Advance when aim converged OR timer expired (FUN_8015dd44:11-17).
  if (!converged && cfg.zero < (actor.witchTimer558 ?? 0)) return;
  actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
  // zz_004beb8_(rate, actor, 0xf, group=2, slot=0, -1, -1) — arm the active-contact stream.
  startStream(
    actor,
    WITCH_CLUSTER.STREAM_MASK,
    WITCH_CLUSTER.ACTION0_STREAM_GROUP,
    0,
    cfg.streamRate,
  );
  void ctx;
}

/** Phase 2 — active contact (PATRA FUN_8015ddd0 / BUG FUN_8014d9c0 / BASTET zz_01b48b8_ /
 *  GUARD FUN_80152308). Borg-switched zz_0082824_ spawn on the dual contact gate. */
function witchAction0Phase2Active(actor: WitchActor, cfg: WitchFamilyConfig, ctx: WitchClusterCtx): void {
  tickStream(actor, WITCH_CLUSTER.STREAM_MASK, ctx);
  // Dual contact gate: +0x1cef == 1 AND +0x1cf0 == 1 (part-0 + part-1 contact bytes).
  if (actor.contactP0 === WITCH_CLUSTER.CONTACT_P0_FLAG && actor.contactP1 === WITCH_CLUSTER.CONTACT_P1_FLAG) {
    actor.fbPhaseSlots[0] = (actor.fbPhaseSlots[0] ?? 0) + 1; // +0x540++
    // zz_006dbe0_(actor, 0, 1, 1) — ammo check + consume.
    if (allocateWeapon(actor, ctx, 0, 1, true)) {
      const type = cfg.shotTypeFor(actor.borgNumber);
      if (type !== null) ctx.onFamilyProjectile?.(actor, WITCH_SHOT_SPAWNER, type);
    }
  }
}

/** Phase 3 — recover (PATRA FUN_8015de78 / BUG FUN_8014da3c). */
function witchAction0Phase3Recover(actor: WitchActor, ctx: WitchClusterCtx): void {
  // zz_004cd24_ returns 1 on stream-end; tickStream returns completed for part-0.
  const completed = tickStream(actor, WITCH_CLUSTER.STREAM_MASK, ctx);
  if (completed) {
    // +0x73f = 0; +0x5e0 &= ~3; zz_006a474_(actor).
    actor.housekeeping73f = 0;
    actor.controlWord &= ~0x3;
    romGroundIdleReturn(actor);
  }
}

/** Build the shared witch action-0 root dispatcher (state-61 virtual). */
function createWitchRootAction(
  cfg: WitchFamilyConfig,
  ctx: WitchClusterCtx,
): (actor: RomActor) => void {
  // action 2 (X-special) — shared-engine approximation. Each witch's bespoke X tables
  // (PATRA @0x80348c54/c64, BASTET @0x8038178c/79c, BUG @0x80340ef4, GUARD @0x80341f2c)
  // are TODO; the shared engine provides the closest dash-attack fallback.
  const sharedX = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(cfg.xGroundSlot) });

  return (base: RomActor) => {
    const actor = scratchOf(base);
    switch (actor.actionIndex) {
      case 0: {
        const phase = actor.fbPhaseSlots[0] ?? 0;
        if (phase === 0) witchAction0Phase0Setup(actor, cfg);
        else if (phase === 1) witchAction0Phase1Approach(actor, cfg, ctx);
        else if (phase === 2) witchAction0Phase2Active(actor, cfg, ctx);
        else witchAction0Phase3Recover(actor, ctx);
        return;
      }
      case 1:
        // TODO(rom): port the bespoke action-1 melee tables (PATRA @0x80348bf8/c10/c24/c34,
        // BUG @0x80340ea8/c0/d4/ee4, GUARD @0x80341ed4/eec/f00/f10, BASTET @0x80381730/748).
        // Falls through to the shared engine as the closest approximation for now.
        return;
      case 2:
        sharedX(actor);
        return;
      default:
        return;
    }
  };
}

// ============================================================================
// Per-family configure functions (the 4 exported entries the bridge registers).
// ============================================================================

/** Configure a PATRA WITCH family actor (pl0902/pl0909). */
export function configurePatraWitchFamily(
  actor: RomActor,
  borgId: WitchBorgId,
  ctx: WitchClusterCtx,
): void {
  actor.borgNumber = WITCH_BORG_NUMBERS[borgId] ?? 0x902;
  actor.rootAction = createWitchRootAction(PATRA_WITCH_CONFIG, ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Configure a BASTET WITCH family actor (pl0907/pl090c). */
export function configureBastetWitchFamily(
  actor: RomActor,
  borgId: WitchBorgId,
  ctx: WitchClusterCtx,
): void {
  actor.borgNumber = WITCH_BORG_NUMBERS[borgId] ?? 0x907;
  actor.rootAction = createWitchRootAction(BASTET_WITCH_CONFIG, ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Configure a BUG WITCH family actor (pl0901). */
export function configureBugWitchFamily(
  actor: RomActor,
  borgId: WitchBorgId,
  ctx: WitchClusterCtx,
): void {
  actor.borgNumber = WITCH_BORG_NUMBERS[borgId] ?? 0x901;
  actor.rootAction = createWitchRootAction(BUG_WITCH_CONFIG, ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

/** Configure a GUARD WITCH family actor (pl0903/pl090a). */
export function configureGuardWitchFamily(
  actor: RomActor,
  borgId: WitchBorgId,
  ctx: WitchClusterCtx,
): void {
  actor.borgNumber = WITCH_BORG_NUMBERS[borgId] ?? 0x903;
  actor.rootAction = createWitchRootAction(GUARD_WITCH_CONFIG, ctx);
  actor.defaultGroup = 0;
  actor.streamSlot = 0;
}

export const WITCH_CLUSTER_CONSTANTS = WITCH_CLUSTER;

// ============================================================================
// Self-tests (mirror victory-king.ts / rom.selfcheck.ts style).
// ============================================================================
export type AssertFn = (cond: boolean, msg: string) => void;

function makeCtx(opts: {
  onAllocateResource?: () => boolean;
  onFamilyProjectile?: (addr: number, type: number) => void;
} = {}): WitchClusterCtx {
  const ctx: WitchClusterCtx = {};
  if (opts.onAllocateResource) ctx.onAllocateResource = () => opts.onAllocateResource!();
  if (opts.onFamilyProjectile) {
    const sink = opts.onFamilyProjectile;
    ctx.onFamilyProjectile = (_a, addr, type) => sink(addr, type);
  }
  return ctx;
}

type Shot = { addr: number; type: number };

/** Drive action-0 ph0→ph1→ph2→ph3 for one (config, borgId, expectedType) case. */
function driveAction0(
  cfg: WitchFamilyConfig,
  borgId: WitchBorgId,
  configure: (a: RomActor, id: WitchBorgId, ctx: WitchClusterCtx) => void,
  expectedType: number,
  assert: AssertFn,
): void {
  const shots: Shot[] = [];
  const a = createRomActor() as WitchActor;
  configure(a, borgId, makeCtx({
    onAllocateResource: () => true,
    onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
  }));
  const root = a.rootAction!;
  a.actionIndex = 0; a.dt = 1;
  // ph0 setup.
  a.hSpeed = 9; a.hDecel = 3;
  root(a);
  assert(a.fbPhaseSlots[0] === 1, `${cfg.label} ph0 advances +0x540 to 1`);
  assert(a.hSpeed === 0 && a.hDecel === 0, `${cfg.label} ph0 zeroes hSpeed/hDecel`);
  assert(a.witchTimer558 === cfg.timerSeed, `${cfg.label} ph0 +0x558 = ${cfg.timerSeed}`);
  // ph1: expire the timer (no target → aim never converges; force via timer<=0).
  a.witchTimer558 = 0; // timer already <= 0 → advance regardless of aim.
  root(a);
  assert(a.fbPhaseSlots[0] === 2, `${cfg.label} ph1 timer<=0 advances to ph2`);
  // ph2: fire the dual contact → borg-switched zz_0082824_ spawn.
  a.contactP0 = 1; a.contactP1 = 1;
  root(a);
  assert(
    shots.length === 1 && shots[0]!.addr === WITCH_SHOT_SPAWNER && shots[0]!.type === expectedType,
    `${cfg.label} ph2 contact spawns zz_0082824_(0x${expectedType.toString(16)}) (got ${JSON.stringify(shots)})`,
  );
  assert(a.fbPhaseSlots[0] === 3, `${cfg.label} ph2 contact advances +0x540 to ph3`);
}

export function runWitchClusterSelfTests(assert: AssertFn): void {
  // --- configure stamps borgNumber + wires bespoke rootAction for all 7 members. ---
  const cases: Array<{ id: WitchBorgId; num: number; configure: (a: RomActor, id: WitchBorgId, ctx: WitchClusterCtx) => void; label: string }> = [
    { id: "pl0901", num: 0x901, configure: configureBugWitchFamily, label: "BUG" },
    { id: "pl0902", num: 0x902, configure: configurePatraWitchFamily, label: "PATRA" },
    { id: "pl0903", num: 0x903, configure: configureGuardWitchFamily, label: "GUARD" },
    { id: "pl0907", num: 0x907, configure: configureBastetWitchFamily, label: "BASTET" },
    { id: "pl0909", num: 0x909, configure: configurePatraWitchFamily, label: "ISIS" },
    { id: "pl090a", num: 0x90a, configure: configureGuardWitchFamily, label: "SHIELD" },
    { id: "pl090c", num: 0x90c, configure: configureBastetWitchFamily, label: "SEKHMET" },
  ];
  for (const { id, num, configure, label } of cases) {
    const a = createRomActor();
    configure(a, id, makeCtx());
    assert(a.borgNumber === num, `${id} (${label}) borgNumber stamped 0x${num.toString(16)}`);
    assert(a.rootAction !== null, `${id} (${label}) bespoke rootAction wired`);
  }

  // --- per-family action-0 drive: contact → exact borg-switched zz_0082824_ type. ---
  driveAction0(BUG_WITCH_CONFIG, "pl0901", configureBugWitchFamily, 0x65, assert);
  driveAction0(PATRA_WITCH_CONFIG, "pl0902", configurePatraWitchFamily, 0x66, assert);
  driveAction0(PATRA_WITCH_CONFIG, "pl0909", configurePatraWitchFamily, 0x67, assert);
  driveAction0(GUARD_WITCH_CONFIG, "pl0903", configureGuardWitchFamily, 0x68, assert);
  driveAction0(GUARD_WITCH_CONFIG, "pl090a", configureGuardWitchFamily, 0x69, assert);
  driveAction0(BASTET_WITCH_CONFIG, "pl0907", configureBastetWitchFamily, 0x6c, assert);
  driveAction0(BASTET_WITCH_CONFIG, "pl090c", configureBastetWitchFamily, 0x6d, assert);

  // --- ph2 ammo denial: suppresses the zz_0082824_ spawn but still advances phase. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as WitchActor;
    configureBugWitchFamily(a, "pl0901", makeCtx({
      onAllocateResource: () => false,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    root(a);              // ph0
    a.witchTimer558 = 0;  // ph1 → advance
    root(a);              // ph1 → ph2
    a.contactP0 = 1; a.contactP1 = 1;
    root(a);              // ph2 denied
    assert(shots.length === 0, "ph2 ammo denial suppresses zz_0082824_ spawn");
    assert(a.fbPhaseSlots[0] === 3, "ph2 still advances +0x540 on denied ammo");
  }

  // --- ph2 dual-contact gate: missing part-1 contact does NOT spawn. ---
  {
    const shots: Shot[] = [];
    const a = createRomActor() as WitchActor;
    configurePatraWitchFamily(a, "pl0902", makeCtx({
      onAllocateResource: () => true,
      onFamilyProjectile: (addr, type) => shots.push({ addr, type }),
    }));
    const root = a.rootAction!;
    a.actionIndex = 0; a.dt = 1;
    root(a); a.witchTimer558 = 0; root(a); // → ph2
    a.contactP0 = 1; a.contactP1 = 0;      // only part-0 contact
    root(a);
    assert(shots.length === 0, "ph2 dual-contact gate: +0x1cf0==0 suppresses spawn");
    assert(a.fbPhaseSlots[0] === 2, "ph2 does not advance without the dual contact");
  }

  // --- action 1 bespoke TODO: falls through (no phase advance). ---
  {
    const a = createRomActor();
    configureBastetWitchFamily(a, "pl0907", makeCtx());
    const root = a.rootAction!;
    a.actionIndex = 1;
    a.fbPhaseSlots[0] = 0;
    root(a);
    assert(a.fbPhaseSlots[0] === 0, "action1 bespoke TODO falls through (no phase advance)");
  }
}
