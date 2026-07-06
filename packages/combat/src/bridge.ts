// Bridge between the existing @gf/combat `BorgRuntime` (the canonical game state —
// HP, lock-on, ammo, gauges, status, projectiles, results telemetry) and the ROM
// `RomActor` runtime (the 1:1 ported state machine). The existing layer stays
// authoritative for everything EXCEPT the action/motion that a ported ROM family
// owns; the bridge syncs fields both ways each frame.
//
// INTEGRATION (3 lines, minimal surgery on the existing code):
//   battle.ts  before stepMovement/stepAttacks:
//     if (b.romDriver?.tick(b, dt, all, ctx)) continue;   // ROM owned this frame
//   combat.ts  X-special branch, before spawnSpecialProjectiles:
//     if (b.romDriver?.tryStartXSpecial(b, all, ctx)) return { projectiles: out };
//
// BorgRuntime keeps its vec3 `vel` model; RomActor uses the ROM's scalar hSpeed +
// yVel model. The bridge decomposes/recomposes each sync.

import type { BorgRuntime } from "./types.js";
import type { Vec3 } from "@gf/physics";
import type { RomActor } from "./rom/actor.js";
import { createRomActor } from "./rom/actor.js";
import {
  createRomStateTables,
  stepRomActor,
  type StateHandler,
} from "./rom/state-tables.js";
import type { StreamContext } from "./rom/stream-vm.js";
import {
  dispatchCommandRecord,
  dispatchUpperBodyCue,
  dispatchFullBodyCue,
} from "./rom/dispatch.js";
import { configureGRedFamily, type GRedFamilyCtx } from "./families/gred.js";
import { configureNinjaFamily } from "./families/ninja.js";
import { configureStarHeroFamily } from "./families/star-hero.js";
import { configureCyberMachineFamily } from "./families/cyber-machine.js";
import { configureDragonFamily } from "./families/dragon.js";
import { configureWormFamily } from "./families/worm.js";
import { configureWireGunnerFamily } from "./families/wire-gunner.js";
import { configureRobotFamily } from "./families/robot.js";
import { configureSwordKnightFamily } from "./families/sword-knight.js";
import { HERO_X_BUFF } from "./constants.js";
import { applyActorParamTierDelta127 } from "./paramTier.js";
import { createSharedEngineRootAction, DEFAULT_CONFIGS } from "./families/shared-engine.js";
import { spawnRomProjectile } from "./projectiles.js";
import type { Projectile } from "./types.js";
import attackHitTablesData from "./data/attackHitTables.json" with { type: "json" };
import actionStreamTablesData from "./data/actionStreamTables.json" with { type: "json" };
import meleeAnimKindsData from "./data/meleeAnimKinds.json" with { type: "json" };
import familyCueTablesFullData from "./data/familyCueTablesFull.json" with { type: "json" };

const TAU = Math.PI * 2;
const BAM_FULL = 0x10000;

/** An armed hitbox window (from attackHitTables.json, looked up per kind). */
interface ArmedHit {
  activeStart: number;
  activeEnd: number;
  reach: number;
  damageRecordIndex: number;
  /** Uids already struck by this window (one hit per target per window). */
  struck: Set<string>;
}

// Lazy-loaded per-borg hit-table data (attackHitTables.json). Loaded once, cached.
const HIT_TABLES: Record<string, { kinds: Record<string, number[]>; records: Record<string, unknown> }> =
  (attackHitTablesData as { borgs: Record<string, { kinds: Record<string, number[]>; records: Record<string, unknown> }> }).borgs;
function hitTablesFor(borgId: string): { kinds: Record<string, number[]>; records: Record<string, unknown> } | null {
  return HIT_TABLES[borgId] ?? null;
}

// --- Pre-decoded stream events (meleeAnimKinds.json) ---
// The stream banks' bytecode is already decoded into frame-keyed events by
// scripts/gen-melee-anim-kinds.mjs. The bridge plays these back directly, bypassing
// the raw bytecode walker when familyStreamBank is null (which it is for all families
// until the bank-byte extractor lands). This gives every family working anim + hitbox
// arming from the ALREADY-DECODED data.

interface StreamEvent {
  op: string;
  frame?: number;
  kind?: number;
  statusId?: number;
  statusArg?: number;
  group?: number;
  slot?: number;
  mode?: number;
  blend?: boolean;
}

const ACTION_STREAM_BANKS: Record<string, { bank: string; group: number; seedSlot: number } | undefined> = (() => {
  const data = actionStreamTablesData as unknown as { borgs: Record<string, { actions: Record<string, { variants: Record<string, { bank: string; group: number; seedSlot: number } | undefined> }> }> };
  const out: Record<string, { bank: string; group: number; seedSlot: number } | undefined> = {};
  for (const [borgId, b] of Object.entries(data.borgs || {})) {
    const xLeaf = b.actions?.["2"]?.variants?.["0"];
    if (xLeaf) out[borgId] = { bank: xLeaf.bank, group: xLeaf.group, seedSlot: xLeaf.seedSlot ?? 0 };
  }
  return out;
})();

// eslint-disable-next-line @typescript-eslint/no-explicit-any
const MELEE_ANIM_BANKS: Record<string, any> = (meleeAnimKindsData as { banks?: Record<string, unknown> }).banks ?? {};

/** Look up the pre-decoded stream events for a borg's X-special. Returns null when
 *  the borg has no decoded action-stream data (uncommon — 156/208 borgs have it). */
function streamEventsFor(borgId: string): StreamEvent[] | null {
  const meta = ACTION_STREAM_BANKS[borgId];
  if (!meta) return null;
  const bank = MELEE_ANIM_BANKS[meta.bank];
  if (!bank) return null;
  // eslint-disable-next-line @typescript-eslint/no-explicit-any
  const group = bank.groups?.["g" + meta.group] as any;
  const slot = group?.["s" + meta.seedSlot] as { events?: StreamEvent[] } | undefined;
  return slot?.events ?? null;
}

/** BorgRuntime.rotY is in radians (atan2(x,z) convention, +Z forward); RomActor.heading
 *  is BAM16 (0..0xFFFF, 0 = +Z forward). */
function radToBam(rad: number): number {
  let bam = Math.round((rad / TAU) * BAM_FULL);
  bam &= 0xffff;
  if (bam >= 0x8000) bam -= 0x10000;
  return bam;
}
function bamToRad(bam: number): number {
  let s = bam & 0xffff;
  if (s & 0x8000) s -= 0x10000;
  return (s / BAM_FULL) * TAU;
}

/** Decompose BorgRuntime.vel (vec3) into RomActor's scalar hSpeed + yVel model. */
function decomposeVel(vel: Vec3): { hSpeed: number; yVel: number } {
  return { hSpeed: Math.hypot(vel.x, vel.z), yVel: vel.y };
}
/** Recompose RomActor's hSpeed (yaw-projected) + yVel back into BorgRuntime.vel. */
function recomposeVel(hSpeed: number, yVel: number, yawBam: number): Vec3 {
  const rad = bamToRad(yawBam);
  // Match physics.ts: pos.x += hSpeed × sin(yaw); pos.z += hSpeed × cos(yaw).
  // The sign of hSpeed carries direction (the ROM allows negative hSpeed for reverse).
  return { x: Math.sin(rad) * hSpeed, y: yVel, z: Math.cos(rad) * hSpeed };
}

/** Per-family registry. Maps borg-id → factory that wires the RomActor + cue table.
 *  Returns null for borgs whose family hasn't been ported yet (they keep the generic
 *  archetype logic). */
export interface FamilyRegistration {
  /** Configure a freshly-created RomActor for this borg-id (sets the family virtual,
   *  stamps the borg-number switch, etc.). */
  configure: (actor: RomActor, ctx: GRedFamilyCtx) => void;
  /** The cue→state table for this family (48 entries × 2 bytes). Extracted from
   *  boot.dol; hardcoded for G RED until the extractor script lands. */
  cueTable: Int8Array;
}

// Lazily built so the cue-table data consts below are initialized first (the
// registrations read cueTableForBorg at construction time).
let FAMILY_REGISTRY_CACHE: Record<string, FamilyRegistration> | null = null;
function familyRegistry(): Record<string, FamilyRegistration> {
  if (!FAMILY_REGISTRY_CACHE) {
    FAMILY_REGISTRY_CACHE = {
      // G RED family (ctor 0x8018ccfc) — cue table @0x80365cf8, full 48-row DOL dump.
      pl0615: makeGRedFamilyRegistration(),
      pl0629: makeGRedFamilyRegistration(),
      pl062a: makeGRedFamilyRegistration(),
      // NORMAL NINJA family (ctor 0x8006f4f8) — cue table @0x802d3ff8. SASUKE (pl000a)
      // shares the entire family: the ctor differs only in the +0x4b0 descriptor.
      pl0000: makeNinjaFamilyRegistration(),
      pl000a: makeNinjaFamilyRegistration(),
      // STAR HERO family (ctor 0x8010f5ac) — cue table @0x80326cf0. PLANET HERO (pl080c)
      // shares the entire family module (status-effects-decode §A verified chain).
      pl0804: makeStarHeroFamilyRegistration(),
      pl080c: makeStarHeroFamilyRegistration(),
      // VICTORY KING family (ctor 0x8015a494) — cue table @0x80344b50. X-special routes
      // through the shared engine zz_017a374_ (phase table 0x804347b0): action-2 handler
      // FUN_8015ad10 delegates all arms to zz_017a374_ (no bespoke family phase machine).
      // X group-4 seed slot per borg (actionStreamTables): pl0610 gnd 0 / air 1,
      // pl0621 slot 0, pl0623 slot 1; pl061e has no action 2.
      pl0610: makeVictoryKingFamilyRegistration(0),
      pl061e: makeVictoryKingFamilyRegistration(null),
      pl0621: makeVictoryKingFamilyRegistration(0),
      pl0623: makeVictoryKingFamilyRegistration(1),
      // SWORD KNIGHT family (ctor 0x80073b70) — cue table @0x802d4b50. NORMAL KNIGHT
      // (pl020a) and DEATH BORG GAMMA II (pl020f) share the entire family module (the
      // ctor block-copies word @0x802d47b8 to all three; only pl0200 wires command
      // records to the X-special actionIndex 2 — cue-script-stream-decode §"Second family").
      pl0200: makeSwordKnightFamilyRegistration(),
      pl020a: makeSwordKnightFamilyRegistration(),
      pl020f: makeSwordKnightFamilyRegistration(),
      // FLAME DRAGON family (ctor 0x80075658) — cue table @0x802d5a58. All 6 members
      // share the bespoke X-special phase machine (3 breath variants); see families/dragon.ts.
      pl0500: makeDragonFamilyRegistration(),
      pl0509: makeDragonFamilyRegistration(),
      pl050a: makeDragonFamilyRegistration(),
      pl050c: makeDragonFamilyRegistration(),
      pl0515: makeDragonFamilyRegistration(),
      pl0516: makeDragonFamilyRegistration(),
      // ALIEN WORM family (ctor 0x80118cb8) — cue table @0x8032b8d8. All 4 members
      // share the bespoke X-special spawn dispatcher (FUN_80118efc); see
      // families/worm.ts. pl0501/pl050d spawn a worm-child via FUN_8011a108;
      // pl050b/pl0517 spawn a venom/poison cloud via zz_01d4d00_.
      pl0501: makeWormFamilyRegistration(),
      pl050b: makeWormFamilyRegistration(),
      pl050d: makeWormFamilyRegistration(),
      pl0517: makeWormFamilyRegistration(),
      // CYBER MACHINE family (ctor 0x800cc454) — cue table @0x8030c3c0. The four
      // beast-god borgs (SEIRYU/SUZAKU/BYAKKO/GENBU) share the entire family module
      // (X-special = ammo-gated shot deploy, FUN_800ce5dc).
      pl0602: makeCyberMachineFamilyRegistration(),
      pl060a: makeCyberMachineFamilyRegistration(),
      pl060c: makeCyberMachineFamilyRegistration(),
      pl060e: makeCyberMachineFamilyRegistration(),
      // MACHINE RED family (ctor 0x800c91bc) — cue table @0x8030a248. The four machine
      // borgs (MACHINE RED/CYBER MARS/PROTO RED/PROTO MARS) share the X-special engine
      // zz_0179d20_ (phaseTable 0x804347a8, group 4 seed slot 0) — the same shared
      // X-special engine used by 12+ other borgs. No bespoke family phase logic, so this
      // is a SHARED registration: cue table + shared-engine X config, no family module.
      pl0600: makeMachineRedFamilyRegistration(),
      pl0608: makeMachineRedFamilyRegistration(),
      pl0616: makeMachineRedFamilyRegistration(),
      pl061c: makeMachineRedFamilyRegistration(),
      // MACHINE BLUE family (ctor 0x800ce730) — cue table @0x8030c9c8. The four
      // machine borgs (MACHINE BLUE/CYBER ATLAS/PROTO BLUE/PROTO ATLAS) share the
      // X-special engine zz_0179fcc_ (phaseTable 0x80352b64, group 4 seed slot 0 /
      // air slot 1) — the same shared group-4 X-special engine family used by 12+
      // other borgs. Action-2 leaf FUN_800cf9cc (chunk_0021.c:4080) is a thin wrapper
      // that halves steerYaw (+0x18da >>= 1) then tail-calls the shared engine; no
      // bespoke family phase logic, so this is a SHARED registration: cue table +
      // shared-engine X config, no family module.
      pl0601: makeMachineBlueFamilyRegistration(),
      pl0609: makeMachineBlueFamilyRegistration(),
      pl0617: makeMachineBlueFamilyRegistration(),
      pl061d: makeMachineBlueFamilyRegistration(),
      // DEMON SAMURAI family (ctor 0x801223c0) — cue table @0x8032d4d8. The X-special
      // routes through the shared engine zz_0149708_ (phase table 0x8033ed3c), shared by
      // 10 borgs across multiple families — no bespoke family module. All 4 members share
      // ctor 0x801223c0 + group-4 seedSlot 0 (actionStreamTables).
      pl0701: makeSamuraiFamilyRegistration(),
      pl0708: makeSamuraiFamilyRegistration(),
      pl070c: makeSamuraiFamilyRegistration(),
      pl070d: makeSamuraiFamilyRegistration(),
      // BUILD ROBOT family (ctor 0x80112b44) — cue table @0x80328148. The three robot
      // borgs (BUILD/MEGATON/ARMY) share the bespoke X-special dive-bomb deploy
      // (FUN_801132f8 → PTR_FUN_80327f98 phase machine); see families/robot.ts. The
      // phase-1 contact spawns a borg-switched child: pl0402/pl0408 via zz_01138c0_
      // (family child-deploy), pl0407 via FUN_801b8b6c (MEGATON heavy deploy, one-shot
      // latched). All 3 members share ctor 0x80112b44 + group-4 seedSlot 0 (air 1).
      pl0402: makeRobotFamilyRegistration(),
      pl0407: makeRobotFamilyRegistration(),
      pl0408: makeRobotFamilyRegistration(),
      // WIRE GUNNER family (ctor 0x801301f8) — cue table @0x80336178. The three gunner
      // borgs share the bespoke X-special phase machine FUN_80131688 → zz_01316e0_
      // (direction-gated aim→fire shot deploy, group 4 slots 2/3/4); see
      // families/wire-gunner.ts.
      pl0103: makeWireGunnerFamilyRegistration(),
      pl0106: makeWireGunnerFamilyRegistration(),
      pl0107: makeWireGunnerFamilyRegistration(),
    };
  }
  return FAMILY_REGISTRY_CACHE;
}

// ---- Fleet-wide DERIVED cue tables (familyCueTablesFull.json, 2026-07-06) ----
// 119/119 family ctors' 48×2 cue→state tables dumped from boot.dol at each ctor's
// +0x4f0 binding, byte-validated against the two hand-verified dumps (family 0 +
// G RED, nn-family-decode-2026-07-06.md §A11). Rows 44 AND 45 → state 61 in ALL 119
// families (the universal root-action trampoline). Three ctors carry per-borg
// memberOverrides (variant sub-families binding a different table).

interface CueTableFamilyEntry {
  cueTable: string;
  members: string[];
  rows: number[][] | null;
  memberOverrides?: Record<string, { cueTable: string; rows: number[][] | null }>;
}
const CUE_TABLE_FAMILIES = (familyCueTablesFullData as unknown as {
  families: Record<string, CueTableFamilyEntry>;
}).families;

/** borgId → family ctor address (actionStreamTables.json). */
const BORG_CTOR: Record<string, string | undefined> = (() => {
  const data = actionStreamTablesData as unknown as { borgs: Record<string, { constructorAddress?: string }> };
  const out: Record<string, string | undefined> = {};
  for (const [borgId, b] of Object.entries(data.borgs || {})) out[borgId] = b.constructorAddress;
  return out;
})();

/** The borg's REAL ROM cue table (per-borg override → family rows), as the Int8Array
 *  shape dispatch.ts consumes. Null when the borg has no extracted family entry. */
export function cueTableForBorg(borgId: string): Int8Array | null {
  const ctor = BORG_CTOR[borgId];
  if (!ctor) return null;
  const fam = CUE_TABLE_FAMILIES[ctor];
  if (!fam) return null;
  const rows = fam.memberOverrides?.[borgId]?.rows ?? fam.rows;
  if (!rows) return null;
  const t = new Int8Array(96);
  for (let i = 0; i < 48 && i < rows.length; i++) {
    t[i * 2] = rows[i]![0]!;
    t[i * 2 + 1] = rows[i]![1]!;
  }
  return t;
}

function makeGRedFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id = actor.borgNumber === 0x629 ? "pl0629" : actor.borgNumber === 0x62a ? "pl062a" : "pl0615";
      configureGRedFamily(actor, id as "pl0615" | "pl0629" | "pl062a", ctx);
    },
    cueTable: cueTableForBorg("pl0615")!,
  };
}

function makeNinjaFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id = actor.borgNumber === 0x00a ? "pl000a" : "pl0000";
      configureNinjaFamily(actor, id as "pl0000" | "pl000a", ctx);
    },
    cueTable: cueTableForBorg("pl0000")!,
  };
}

function makeStarHeroFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id = actor.borgNumber === 0x80c ? "pl080c" : "pl0804";
      configureStarHeroFamily(actor, id as "pl0804" | "pl080c", ctx);
    },
    cueTable: cueTableForBorg("pl0804")!,
  };
}

// VICTORY KING family (ctor 0x8015a494) — cue table @0x80344b50. The X-special ROUTES
// THROUGH THE SHARED ENGINE zz_017a374_ (phase table 0x804347b0, chunk_0044.c:4322):
// action-2 handler FUN_8015ad10 (chunk_0040.c:4103) is a thin borg-switch whose every
// arm (pl0610→zz_015ad5c_, pl0621→zz_015ad84_, pl0623→zz_015adac_) tail-calls
// zz_017a374_ — the same cross-family engine reused by Panther Robot + 2 others. No
// bespoke family phase logic (contrast G RED's family-specific 4-phase G Crash chain),
// so this is a SHARED registration: cue table + shared-engine X config, no family module.
// pl061e (PROTO KING) has NO action 2 (FUN_8015ad10 falls through for 0x61e) → xSpecial
// left null so its rootAction defers entirely to the generic combat layer.
function makeVictoryKingFamilyRegistration(xSeedSlot: number | null): FamilyRegistration {
  return {
    configure: (actor) => {
      actor.borgNumber = 0x610;
      actor.rootAction = createSharedEngineRootAction({
        xSpecial: xSeedSlot === null ? null : DEFAULT_CONFIGS.dashAttack(xSeedSlot),
      });
      actor.defaultGroup = 0;
      actor.streamSlot = 0;
    },
    cueTable: cueTableForBorg("pl0610")!,
  };
}

function makeSwordKnightFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x20a ? "pl020a" :
        actor.borgNumber === 0x20f ? "pl020f" : "pl0200";
      configureSwordKnightFamily(actor, id as "pl0200" | "pl020a" | "pl020f", ctx);
    },
    cueTable: cueTableForBorg("pl0200")!,
  };
}

// MACHINE RED family (ctor 0x800c91bc) — cue table @0x8030a248. The X-special ROUTES
// THROUGH THE SHARED ENGINE zz_0179d20_ (phaseTable 0x804347a8, chunk_0044.c:4086):
// action-2 handler FUN_800cb9d4 (chunk_0021.c:1545) tail-calls zz_0179d20_ — the same
// cross-family group-4 X-special engine reused by 12+ borgs across the roster (per the
// actionStreamTables.json engines header). All 5 action-2 variants route to leaf
// 0x800cba10 with config @0x8030a66c (seedSlot 0), so every member uses the same config.
// No bespoke family phase logic (contrast CYBER MACHINE's ammo-gated shot deploy), so
// this is a SHARED registration: cue table + shared-engine X config, no family module.
function makeMachineRedFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor) => {
      actor.borgNumber = 0x600;
      actor.rootAction = createSharedEngineRootAction({
        xSpecial: DEFAULT_CONFIGS.dashAttack(0),
      });
      actor.defaultGroup = 0;
      actor.streamSlot = 0;
    },
    cueTable: cueTableForBorg("pl0600")!,
  };
}

// MACHINE BLUE family (ctor 0x800ce730) — cue table @0x8030c9c8. The X-special ROUTES
// THROUGH THE SHARED ENGINE zz_0179fcc_ (phaseTable 0x80352b64, chunk_0044.c:4185):
// action-2 handler FUN_800cf990 (chunk_0021.c:4071) dispatches the variant table
// PTR_FUN_8030cef8 — all 5 variants route to leaf 0x800cf9cc, which halves steerYaw
// (+0x18da >>= 1) then tail-calls zz_0179fcc_. The shared engine consumes the config
// block @0x8030cf0c (seedSlot 0 ground / 1 air, group 4). pl0601/pl0609/pl0617/pl061d
// all bind the same config (actionStreamTables.json confirms identical leaf + engine
// + phaseTable across the 4 members). No bespoke family phase logic (contrast CYBER
// MACHINE's ammo-gated shot deploy), so this is a SHARED registration: cue table +
// shared-engine X config, no family module. The borgNumber stamp below is overwritten
// by RomDriverBridge.attach (line `actor.borgNumber = borgIdToNumber(runtime.borgId)`)
// so the per-member number (0x601/0x609/0x617/0x61d) is set correctly post-configure.
function makeMachineBlueFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor) => {
      actor.borgNumber = 0x601;
      actor.rootAction = createSharedEngineRootAction({
        xSpecial: DEFAULT_CONFIGS.dashAttack(0),
      });
      actor.defaultGroup = 0;
      actor.streamSlot = 0;
    },
    cueTable: cueTableForBorg("pl0601")!,
  };
}

function makeCyberMachineFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x60a ? "pl060a" :
        actor.borgNumber === 0x60c ? "pl060c" :
        actor.borgNumber === 0x60e ? "pl060e" : "pl0602";
      configureCyberMachineFamily(actor, id as "pl0602" | "pl060a" | "pl060c" | "pl060e", ctx);
    },
    cueTable: cueTableForBorg("pl0602")!,
  };
}

// FLAME DRAGON family (ctor 0x80075658) — cue table @0x802d5a58. The X-special is a
// BESPOKE 3-variant phase machine (ground/air/charged flame breath) ported in
// families/dragon.ts; engines 0x80075ef0/0x80076088/0x80076244 live in the family code
// block (not shared-engine ranges). All 6 members (pl0500/pl0509/pl050a/pl050c/
// pl0515/pl0516) share one module — the ctor block-copies the same +0x4b4 binding;
// only the borg-number switch inside zz_0076408_ (flame-child record select) differs.
function makeDragonFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x509 ? "pl0509" :
        actor.borgNumber === 0x50a ? "pl050a" :
        actor.borgNumber === 0x50c ? "pl050c" :
        actor.borgNumber === 0x515 ? "pl0515" :
        actor.borgNumber === 0x516 ? "pl0516" : "pl0500";
      configureDragonFamily(actor, id as "pl0500" | "pl0509" | "pl050a" | "pl050c" | "pl0515" | "pl0516", ctx);
    },
    cueTable: cueTableForBorg("pl0500")!,
  };
}

// ALIEN WORM family (ctor 0x80118cb8) — cue table @0x8032b8d8. The X-special is a
// BESPOKE borg-switched spawn dispatcher (FUN_80118efc @ chunk_0032.c:662) ported in
// families/worm.ts. pl0501/pl050d spawn a worm-child via FUN_8011a108 (family code
// block); pl050b/pl0517 spawn a venom/poison cloud via the shared zz_01d4d00_ — the
// routing decision is bespoke even though the cloud spawner is shared. All 4 members
// share the cue table (ctor block-copy of the +0x4f0 binding).
function makeWormFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x50b ? "pl050b" :
        actor.borgNumber === 0x50d ? "pl050d" :
        actor.borgNumber === 0x517 ? "pl0517" : "pl0501";
      configureWormFamily(actor, id as "pl0501" | "pl050b" | "pl050d" | "pl0517", ctx);
    },
    cueTable: cueTableForBorg("pl0501")!,
  };
}

// BUILD ROBOT family (ctor 0x80112b44) — cue table @0x80328148. The X-special is a
// BESPOKE 3-phase dive-bomb deploy (FUN_801132f8 → PTR_FUN_80327f98) ported in
// families/robot.ts; engine 0x801132f8 lives in the family code block (not a shared-
// engine range). The phase-1 contact spawns a borg-switched child: pl0402/pl0408 via
// zz_01138c0_ (family child-deploy @0x801138c0), pl0407 via FUN_801b8b6c (MEGATON
// heavy deploy @0x801b8b6c, one-shot latched at +0x150). All 3 members share the cue
// table (ctor block-copy of the +0x4f0 binding) + group-4 seedSlot 0 (air 1).
function makeRobotFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x407 ? "pl0407" :
        actor.borgNumber === 0x408 ? "pl0408" : "pl0402";
      configureRobotFamily(actor, id as "pl0402" | "pl0407" | "pl0408", ctx);
    },
    cueTable: cueTableForBorg("pl0402")!,
  };
}

// WIRE GUNNER family (ctor 0x801301f8) — cue table @0x80336178. The X-special is a
// BESPOKE 2-phase direction-gated shot deploy (FUN_80131688 → zz_01316e0_) ported in
// families/wire-gunner.ts; engine 0x80131688 lives in the family code block (not a
// shared-engine range). All 3 members (pl0103/pl0106/pl0107) share ctor 0x801301f8 +
// group-4 slots 2/3/4 (direction-switched via +0x5e0 bits 0x10/0x40).
function makeWireGunnerFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x106 ? "pl0106" :
        actor.borgNumber === 0x107 ? "pl0107" : "pl0103";
      configureWireGunnerFamily(actor, id as "pl0103" | "pl0106" | "pl0107", ctx);
    },
    cueTable: cueTableForBorg("pl0103")!,
  };
}

// DEMON SAMURAI family (ctor 0x801223c0) — cue table @0x8032d4d8. The X-special ROUTES
// THROUGH THE SHARED ENGINE zz_0149708_ (phase table 0x8033ed3c, chunk_0038.c:2356):
// action-2 handler FUN_80123390 (chunk_0033.c:1549) dispatches PTR_FUN_8032c800[+0x581]
// whose sole entry is the leaf FUN_801233cc (chunk_0033.c:1558) — a one-line tail-call
// to zz_0149708_. That engine is a GENERIC config-struct-driven lunge shared by 10 borgs
// across multiple families (pl0700-070d, confirmed via actionStreamTables engine audit),
// so this is a SHARED registration: cue table + shared-engine X config, no family module.
// All 4 members (pl0701/pl0708/pl070c/pl070d) share ctor 0x801223c0 + group-4 seedSlot 0.
function makeSamuraiFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor) => {
      actor.rootAction = createSharedEngineRootAction({
        xSpecial: DEFAULT_CONFIGS.dashAttack(0),
      });
      actor.defaultGroup = 0;
      actor.streamSlot = 0;
    },
    cueTable: cueTableForBorg("pl0701")!,
  };
}

/** Returns true if a ROM family driver is registered for this borg-id. With the
 *  shared-engine fallback, borgs with decoded action-stream data also get a driver. */
export function hasRomFamilyDriver(borgId: string): boolean {
  return borgId in familyRegistry() || borgId in ACTION_STREAM_BANKS;
}

function makeDefaultCueTable(): Int8Array {
  const t = new Int8Array(96).fill(-1);
  t[44 * 2] = 61;
  t[44 * 2 + 1] = 0;
  t[7 * 2] = 6;
  t[7 * 2 + 1] = 6;
  return t;
}

/** Host-provided hit resolver — called by the bridge when an armed hitbox's active
 *  window intersects an enemy. The host (battle.ts) implements this using the real
 *  `applyHit` + the profiles map + the damage records + burst/energy context, giving
 *  full damage-formula fidelity without the bridge needing to import the combat stack. */
export type RomHitResolver = (
  attacker: BorgRuntime,
  victim: BorgRuntime,
  damageRecordIndex: number,
  knockbackMult: number,
) => void;

/** Host-provided ground clamp — called after the ROM physics step to snap the borg
 *  to the stage floor. Without this the ROM integrator (no collision awareness) lets
 *  borgs fall through the ground. */
export type RomGroundClamp = (pos: { x: number; y: number; z: number }, velY: number) => { y: number; velY: number; grounded: boolean };

/** The bridge sidecar attached to BorgRuntime (via the `romDriver` field). Owns the
 *  RomActor + state tables + per-frame sync. Activates when a ported family exists. */
export class RomDriverBridge {
  readonly actor: RomActor;
  private readonly tables: { fullBody: StateHandler[]; upperBody: StateHandler[] };
  /** Armed hitbox records for the current special. */
  private armedHits: ArmedHit[] = [];
  private streamFrame = 0;
  /** Pre-decoded stream events from meleeAnimKinds.json. Played back each tick to
   *  drive anim changes + hitbox arming at the decoded ROM frames. */
  private streamEvents: StreamEvent[] | null = null;
  /** Max frames the special runs before auto-completing (from the decoded stream length). */
  private specialMaxFrames = 30;
  private readonly ctx: StreamContext;
  /** Host-provided hit resolver (battle.ts). When null, hits are recorded but no
   *  damage is applied — the bridge logs the connection for debugging. */
  hitResolver: RomHitResolver | null = null;
  /** Host-provided ground clamp (battle.ts). */
  groundClamp: RomGroundClamp | null = null;
  /** Stage bounds for position clamping during the ROM special (prevents drift
   *  to stage edges since stepMovement's bounds clamp is skipped). */
  bounds: { minX: number; maxX: number; minZ: number; maxZ: number } | null = null;
  /** Off-mesh check: returns false when (x,z) has no collision triangle. The bridge
   *  reverts the borg to its pre-step XZ in that case, preventing wall-through drift. */
  offMeshCheck: ((x: number, z: number) => boolean) | null = null;
  /** Projectiles spawned by the ROM stream's fireChild op (op 0x09) during the
   *  current special. Drained by battle.ts after each tick. */
  private pendingProjectiles: Projectile[] = [];

  /** Drain projectiles spawned by the ROM stream's fireChild op. Called by battle.ts
   *  after each romDriver.tick(). */
  drainProjectiles(): Projectile[] {
    const drained = this.pendingProjectiles;
    this.pendingProjectiles = [];
    return drained;
  }
  /** True while the ROM state machine is mid-special. */
  private specialActive = false;
  private runtime: BorgRuntime | null = null;

  private constructor(actor: RomActor, ctx: StreamContext) {
    this.actor = actor;
    this.tables = createRomStateTables();
    // Wrap the host ctx so we can intercept armHit/playAnim for bridge-level bookkeeping.
    const host = ctx;
    const wrapped: StreamContext = {
      onArmHit: (a, kind, statusId, statusArg) => {
        host.onArmHit?.(a, kind, statusId, statusArg);
        this.onArmHit(kind);
      },
      onPlayAnim: (a, group, slot, blend) => {
        host.onPlayAnim?.(a, group, slot, blend);
        this.onPlayAnim(group, slot);
      },
      onFireChild: (a, variant) => {
        host.onFireChild?.(a, variant);
        this.onFireChild(variant);
      },
      onParamTierDelta: (a, delta) => {
        host.onParamTierDelta?.(a, delta);
        this.onParamTierDelta(delta);
      },
      onPlayCue: (a, cueId) => {
        host.onPlayCue?.(a, cueId);
      },
    };
    if (host.onIndirect) wrapped.onIndirect = host.onIndirect;
    if (host.onFamilyProjectile) wrapped.onFamilyProjectile = host.onFamilyProjectile;
    this.ctx = wrapped;
  }

  /** Attach a bridge to a freshly-spawned BorgRuntime. Returns the bridge, or null if
   *  the borg has no ported family (caller keeps generic archetypes). */
  static attach(runtime: BorgRuntime, hostCtx: StreamContext): RomDriverBridge | null {
    const reg = familyRegistry()[runtime.borgId];
    const actor = createRomActor();
    // Every borg gets its REAL family cue table when extracted (119/119 families);
    // the hand-rolled default remains only as a last-resort fallback.
    actor.cueTable = reg?.cueTable ?? cueTableForBorg(runtime.borgId) ?? makeDefaultCueTable();
    if (reg) {
      reg.configure(actor, hostCtx);
    } else {
      const streamMeta = ACTION_STREAM_BANKS[runtime.borgId];
      if (!streamMeta) return null;
      actor.rootAction = createSharedEngineRootAction({
        xSpecial: DEFAULT_CONFIGS.dashAttack(streamMeta.seedSlot ?? 0),
      });
    }
    const bridge = new RomDriverBridge(actor, hostCtx);
    actor.borgNumber = borgIdToNumber(runtime.borgId);
    actor.team = runtime.team;
    return bridge;
  }

  /** Copy BorgRuntime → RomActor (before the ROM step). During an active special,
   *  velocity is NOT synced — the ROM handler owns it (syncIn would overwrite the
   *  phase machine's impulses with stale BorgRuntime.vel from before the special). */
  syncIn(runtime: BorgRuntime, all: readonly BorgRuntime[]): void {
    const a = this.actor;
    a.pos.x = runtime.pos.x;
    a.pos.y = runtime.pos.y;
    a.pos.z = runtime.pos.z;
    a.heading = radToBam(runtime.rotY);
    // Only sync velocity on the FIRST entry frame (specialActive was just set).
    // Subsequent ticks: ROM handler owns velocity; skip the copy.
    if (!this.specialActive) {
      a.lockYaw = a.heading;
      a.activeYaw = a.heading;
      const { hSpeed, yVel } = decomposeVel(runtime.vel);
      a.hSpeed = hSpeed;
      a.yVel = yVel;
    }
    a.dt = 1;
    a.timescale = 1;
    a.tierScale = 1;
    a.maxFall = -9999;
    (a as RomActor & { grounded?: boolean }).grounded = runtime.grounded;
    const lockUid = runtime.lockTarget;
    if (lockUid) {
      const target = all.find((b) => b.uid === lockUid);
      if (target) {
        (a as RomActor & { lockTarget?: { x: number; y: number; z: number } | null }).lockTarget = {
          x: target.pos.x, y: target.pos.y, z: target.pos.z,
        };
      }
    }
  }

  /** Copy RomActor → BorgRuntime (after the ROM step). */
  syncOut(runtime: BorgRuntime): void {
    const a = this.actor;
    runtime.pos.x = a.pos.x;
    runtime.pos.y = a.pos.y;
    runtime.pos.z = a.pos.z;
    runtime.rotY = bamToRad(a.heading);
    const vel = recomposeVel(a.hSpeed, a.yVel, a.activeYaw);
    runtime.vel.x = vel.x;
    runtime.vel.y = vel.y;
    runtime.vel.z = vel.z;
  }

  /** Called from combat.ts's X-special branch. Returns true if the ROM family handled
   *  the press (caller skips spawnSpecialProjectiles). Arms the multi-frame phase
   *  machine; subsequent `tick` calls advance it. */
  tryStartXSpecial(runtime: BorgRuntime, all: readonly BorgRuntime[]): boolean {
    if (this.specialActive) return false;
    this.runtime = runtime;
    this.armedHits = [];
    this.streamFrame = 0;
    // Load pre-decoded stream events for the choreography (anim + hitbox arming).
    this.streamEvents = streamEventsFor(runtime.borgId);
    // Determine the special's duration from the decoded stream (default 30 frames).
    this.specialMaxFrames = 30;
    if (this.streamEvents) {
      const maxFrame = this.streamEvents.reduce((m, e) => Math.max(m, e.frame ?? 0), 0);
      this.specialMaxFrames = Math.max(this.specialMaxFrames, maxFrame + 5);
    }
    // Fire frame-0 events immediately (armHit + playAnim).
    this.dispatchEvent(0);
    this.streamFrame = 1;
    // Don't change runtime.state/anim — let stepAttacks/stepMovement handle those.
    // The bridge layers hitbox/anim ON TOP of normal movement, not replacing it.
    runtime.cooldowns["romSpecialActive"] = 1;
    this.specialActive = true;
    // For G RED family (custom handler): also run the ROM physics for the launch arc.
    // The custom handler sets velocities that stepMovement will integrate.
    if (this.actor.rootAction) {
      const preX = runtime.pos.x;
      const preZ = runtime.pos.z;
      this.syncIn(runtime, all);
      dispatchCommandRecord(this.actor, { cueId: 44, stateMode: 3, actionIndex: 2, variantIndex: 0 });
      stepRomActor(this.actor, this.tables, this.ctx);
      this.syncOut(runtime);
      // The shared-X blink-away reposition (phase 0's pos += (pos−target)×0.95) can
      // teleport past the arena walls near stage edges — the ROM's own step runs the
      // ground/wall collide (zz_00677b0_) right after; the port applies the host's
      // bounds clamp + off-mesh revert here (same policy tick() documents).
      if (this.bounds) {
        runtime.pos.x = Math.min(this.bounds.maxX, Math.max(this.bounds.minX, runtime.pos.x));
        runtime.pos.z = Math.min(this.bounds.maxZ, Math.max(this.bounds.minZ, runtime.pos.z));
      }
      if (this.offMeshCheck && !this.offMeshCheck(runtime.pos.x, runtime.pos.z)) {
        runtime.pos.x = preX;
        runtime.pos.z = preZ;
      }
      // Y-guard: a family phase-0 reposition/impulse must never leave the borg BELOW
      // the floor surface (the ROM's own step runs zz_00677b0_ ground collide right
      // after; sword-knight's X dove through the mesh without this).
      if (this.groundClamp) {
        const clamped = this.groundClamp(runtime.pos, runtime.vel.y);
        if (clamped.y > runtime.pos.y) {
          runtime.pos.y = clamped.y;
          runtime.vel.y = Math.max(0, runtime.vel.y);
        }
      }
    }
    return true;
  }

  /** Called from battle.ts before stepMovement/stepAttacks. Returns true ONLY when the
   *  ROM driver needs to exclusively own the borg's motion (G RED's G Crash fly-up
   *  arc). For shared-engine borgs, returns false — stepMovement + stepAttacks run
   *  normally, and the bridge's tick handles ONLY the stream events (anim/hitbox/damage)
   *  on top. This prevents the AI drift caused by skipping navigation during specials. */
  tick(runtime: BorgRuntime, _dt: number, all: readonly BorgRuntime[]): boolean {
    if (!this.specialActive) return false;
    this.runtime = runtime;
    // Play pre-decoded stream events for this frame (anim + hitbox arming).
    this.dispatchEvent(this.streamFrame);
    this.streamFrame++;
    // Resolve armed hitbox windows against nearby enemies (damage).
    this.resolveHits(runtime, all);
    // Drain any fireChild-spawned projectiles.
    // (battle.ts drains via drainProjectiles after tick returns)
    // Check completion: if the special's frame count exceeded the stream length,
    // end the special. The stream length comes from the decoded anim bank (typically
    // 15-81 frames depending on the move).
    if (this.streamFrame >= this.specialMaxFrames) {
      this.specialActive = false;
      this.armedHits = [];
      this.streamEvents = null;
      runtime.cooldowns["romSpecialActive"] = 0;
      runtime.cooldowns["special"] = 90;
    }
    // Return false → stepMovement + stepAttacks run normally. The bridge's
    // hitbox/anim/damage are layered ON TOP of normal movement, not replacing it.
    return false;
  }

  /** Called by the stream VM when a playAnim op fires. Sets the BorgRuntime's anim
   *  label + meleeAnimStream ref so the renderer (borgPresentationAssets) plays the
   *  decoded (group, slot) clip. For G RED's G Crash this is (4, 0) = g04_s00. */
  private onPlayAnim(group: number, slot: number): void {
    if (this.runtime) {
      this.runtime.anim = "special";
      this.runtime.meleeAnimStream = { group, slot };
    }
  }

  /** Called by the stream VM when an armHit op fires. Looks up the kind's hit records
   *  from attackHitTables.json and arms them — each record carries its active window
   *  (frame range), reach, and damage record. The bridge checks them each tick. */
  private onArmHit(kind: number): void {
    if (!this.runtime) return;
    const tables = hitTablesFor(this.runtime.borgId);
    if (!tables) return;
    const recordIndices = tables.kinds[String(kind)];
    if (!recordIndices) return;
    this.armedHits = recordIndices.map((idx) => {
      const rec = tables.records[String(idx)] as {
        activeStart: number; activeEnd: number; halfExtent: number[]; damageRecordIndex: number;
      } | undefined;
      if (!rec) return null;
      return {
        activeStart: rec.activeStart,
        activeEnd: rec.activeEnd,
        reach: rec.halfExtent?.[0] ?? 50,
        damageRecordIndex: rec.damageRecordIndex,
        struck: new Set<string>(),
      } satisfies ArmedHit;
    }).filter((h): h is ArmedHit => h !== null);
    this.streamFrame = 0;
  }

  /** Called by the stream VM when a fireChild op (0x09) fires. Spawns a ROM-data-driven
   *  projectile using the decoded variant table (DAT_802f3dda). The projectile gets
   *  real speed/drop/lifetime from the variant, replacing the TUNED spawnSpecialProjectiles
   *  path. Collected in pendingProjectiles; battle.ts drains them after tick. */
  private onFireChild(variant: number): void {
    if (!this.runtime) return;
    const yawRad = (this.actor.activeYaw / 0x10000) * Math.PI * 2;
    const proj = spawnRomProjectile(this.runtime, variant, yawRad);
    if (proj) this.pendingProjectiles.push(proj);
  }

  /** Called by family handlers (STAR HERO / PLANET HERO X-special) when they apply a
   *  param-tier delta via `apply_actor_param_tier_delta_127`. Routes to BorgRuntime's
   *  authoritative paramTier and keeps heroTierBuffFrames in sync so the existing
   *  stepHitStatus revert path owns expiry (ROM postState only ticks during specials). */
  private onParamTierDelta(signedDelta: number): void {
    if (!this.runtime) return;
    applyActorParamTierDelta127(this.runtime.paramTier, signedDelta);
    if (signedDelta > 0) {
      // Buff application: arm the heroTierBuffFrames timer (stepHitStatus reverts at 0).
      this.runtime.heroTierBuffFrames = HERO_X_BUFF.DURATION_FRAMES;
    } else if (signedDelta < 0) {
      // Revert (ROM-driven): clear the timer so stepHitStatus doesn't double-revert.
      this.runtime.heroTierBuffFrames = 0;
    }
  }

  /** Fire any stream events scheduled for the given frame (from meleeAnimKinds.json).
   *  This drives the anim + hitbox arming at the exact ROM frame numbers, bypassing
   *  the raw bytecode walker when the bank bytes aren't loaded. */
  private dispatchEvent(frame: number): void {
    if (!this.streamEvents) return;
    for (const ev of this.streamEvents) {
      const evFrame = ev.frame ?? 0;
      if (evFrame !== frame) continue;
      switch (ev.op) {
        case "armHit":
          if (ev.kind !== undefined && ev.kind > 0) {
            this.ctx.onArmHit?.(this.actor, ev.kind, ev.statusId ?? 0, ev.statusArg ?? 255);
          }
          break;
        case "playAnim":
        case "blendAnim":
          if (ev.group !== undefined && ev.slot !== undefined) {
            this.ctx.onPlayAnim?.(this.actor, ev.group, ev.slot, ev.op === "blendAnim");
          }
          break;
      }
    }
  }

  /** Per-frame hit check: if any armed hitbox's active window is live this frame,
   *  resolve hits against nearby enemies via the host's applyHit callback. */
  private resolveHits(runtime: BorgRuntime, all: readonly BorgRuntime[]): void {
    if (this.armedHits.length === 0) return;
    this.streamFrame += 1;
    for (const hit of this.armedHits) {
      if (this.streamFrame < hit.activeStart || this.streamFrame > hit.activeEnd) continue;
      for (const target of all) {
        if (!target.alive || target.team === runtime.team) continue;
        if (hit.struck.has(target.uid)) continue;
        const dx = target.pos.x - runtime.pos.x;
        const dz = target.pos.z - runtime.pos.z;
        const dist = Math.hypot(dx, dz);
        if (dist <= hit.reach) {
          hit.struck.add(target.uid);
          // Route through the host's full applyHit path for damage-formula fidelity.
          if (this.hitResolver) {
            this.hitResolver(runtime, target, hit.damageRecordIndex, 1.0);
          } else {
            // Fallback (no resolver wired): direct HP subtraction so hits are still visible.
            target.hp = Math.max(0, target.hp - 20);
            target.lastHitAttackerTeam = runtime.team;
            target.lastHitAttackerOwner = runtime.ownerPlayer;
          }
        }
      }
    }
  }

  /** Force-clear (e.g. on hit-interrupt). The existing hit reaction will set state to
   *  "hit"/"down" which overrides whatever the ROM driver was doing. */
  interrupt(): void {
    this.specialActive = false;
    this.armedHits = [];
    if (this.actor.fbState === 61) {
      dispatchFullBodyCue(this.actor, 0);
      dispatchUpperBodyCue(this.actor, 6);
    }
  }
}

/** Convert a pl#### borg id to the ROM's internal borg number (the +0x3e8 u16). */
function borgIdToNumber(borgId: string): number {
  const m = /^pl([0-9a-f]{4})$/i.exec(borgId);
  return m ? parseInt(m[1]!, 16) : 0;
}
