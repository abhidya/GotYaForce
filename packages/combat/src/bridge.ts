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
import { configureDeathBorgFamily } from "./families/death-borg.js";
import { configureClawRobotFamily, configureDeathBorgOmegaFamily } from "./families/shared-aerial-dive-x.js";
import { configureSeries3Family, type Series3BorgId } from "./families/shared-series3-x.js";
import { configureLanceFlightFamily, type LanceFlightBorgId } from "./families/shared-flight-x.js";
import { createFamily1Charge3Action, createFamily2Charge3Action } from "./families/shared-charge3.js";
import {
  createSharedAimedShotX,
  TITAN_ROBOT_X_CONFIG,
  PANTHER_ROBOT_X_CONFIG,
} from "./families/shared-aimed-shot-x.js";
import {
  createSharedMorphXSpecial,
  configureEagleFamily,
  TITAN_MORPH_CONFIG,
  PANTHER_MORPH_CONFIG,
  VICTORY_MACHINE_MORPH_CONFIG,
} from "./families/shared-morph-x.js";
import { configureSatelliteFamily } from "./families/satellite.js";
import { configureStarHeroFamily } from "./families/star-hero.js";
import { configureCyberMachineFamily } from "./families/cyber-machine.js";
import { configureDragonFamily } from "./families/dragon.js";
import { configureCyberDragonFamily } from "./families/cyber-dragon.js";
import { configureWormFamily } from "./families/worm.js";
import { configureCyberGirlFamily } from "./families/cyber-girl.js";
import { configureWireGunnerFamily } from "./families/wire-gunner.js";
import { configureRobotFamily } from "./families/robot.js";
import { configureSwordKnightFamily } from "./families/sword-knight.js";
import { configureJellyDiverFamily } from "./families/jelly-diver.js";
import { configureCopyManFamily } from "./families/copy-man.js";
import { createMeleeGirlStanding } from "./families/melee-girl-standing.js";
import { createMeleeGirlLunge } from "./families/melee-girl-lunge.js";
import { createMeleeRobot } from "./families/melee-robot.js";
import { createMeleeSamurai, SAMURAI_MELEE_DEFAULT_CONFIG } from "./families/melee-samurai.js";
import { configureValkrieFamily } from "./families/valkrie.js";
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
      // DEATH BORG ALPHA family (ctor 0x8019e9a4) — third family on the shared-X
      // machine (config @0x80435750). pl000c ONLY: pl0008's X command is descriptor-
      // disabled in the ROM (+0xba mode 0xff) — it keeps the generic fallback.
      pl000c: makeDeathBorgFamilyRegistration(),
      // ---- Wave-A verified shared-engine families (2026-07-06, wf_1141168b-7b5) ----
      // Aerial dive/leap-shot engine zz_00f41c4_ (shared-aerial-dive-x.ts):
      pl0400: makeSimpleRegistration("pl0400", (a, ctx) => configureClawRobotFamily(a, "pl0400", ctx)),
      pl040a: makeSimpleRegistration("pl040a", (a, ctx) => configureClawRobotFamily(a, "pl040a", ctx)),
      pl0406: makeSimpleRegistration("pl0406", (a, ctx) => configureDeathBorgOmegaFamily(a, "pl0406", ctx)),
      // Series-3 girl-borg engine 0x8010ce60 (shared-series3-x.ts; bonus families slot-3-only):
      ...series3Registrations(),
      // Knight-line lance flight zz_0149708_ (shared-flight-x.ts; family 2 already served
      // by the samurai module):
      ...lanceFlightRegistrations(),
      // Charge-3 release engine zz_0177a3c_ + morph engine zz_017a374_ composites:
      pl0619: makeSimpleRegistration("pl0619", (a, ctx) => {
        a.borgNumber = 0x619;
        a.rootAction = composeActionTable([null, null, null, createFamily1Charge3Action(ctx), null]);
        a.defaultGroup = 0;
        a.streamSlot = 0;
      }),
      pl061f: makeSimpleRegistration("pl061f", (a, ctx) => {
        // VICTORY TANK: charge3 at [3]; its morph branch is a DEAD borg branch (verified) —
        // action 2 keeps the generic fallback.
        a.borgNumber = 0x61f;
        a.rootAction = composeActionTable([null, null, null, createFamily2Charge3Action(ctx), null]);
        a.defaultGroup = 0;
        a.streamSlot = 0;
      }),
      pl0625: makeSimpleRegistration("pl0625", (a, ctx) => {
        // VICTORY MACHINE: morph at [2] + charge3 at [3].
        a.borgNumber = 0x625;
        a.rootAction = composeActionTable([
          null, null,
          createSharedMorphXSpecial(VICTORY_MACHINE_MORPH_CONFIG, ctx, {}),
          createFamily2Charge3Action(ctx),
          null,
        ]);
        a.defaultGroup = 0;
        a.streamSlot = 0;
      }),
      // Titan/Panther robots: morph at [2] + aimed-shot at [3] (two engines composed).
      pl0604: makeMorphAimedComposite("pl0604", 0x604, TITAN_MORPH_CONFIG, TITAN_ROBOT_X_CONFIG),
      pl0618: makeMorphAimedComposite("pl0618", 0x618, TITAN_MORPH_CONFIG, TITAN_ROBOT_X_CONFIG),
      pl0613: makeMorphAimedComposite("pl0613", 0x613, PANTHER_MORPH_CONFIG, PANTHER_ROBOT_X_CONFIG),
      pl0627: makeMorphAimedComposite("pl0627", 0x627, PANTHER_MORPH_CONFIG, PANTHER_ROBOT_X_CONFIG),
      // Eagle robot morph (pl0606 only — pl061a's branch is bespoke, excluded):
      pl0606: makeSimpleRegistration("pl0606", (a, ctx) => configureEagleFamily(a, "pl0606", ctx)),
      // Satellite family (engine 0x80188da4, x-action 1 + B actions):
      pl0d01: makeSimpleRegistration("pl0d01", (a, ctx) => configureSatelliteFamily(a, "pl0d01", ctx)),
      pl0d05: makeSimpleRegistration("pl0d05", (a, ctx) => configureSatelliteFamily(a, "pl0d05", ctx)),
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
      // CYBER DEATH DRAGON family (ctor 0x800b8188) — cue table @0x802fec20. All 6
      // members share the bespoke X-special phase machine (3 breath variants); see
      // families/cyber-dragon.ts. Sister port of FLAME DRAGON (same 3-variant
      // ground/air/charged structure, identical float constants at FLOAT_804384*).
      pl0503: makeCyberDragonFamilyRegistration(),
      pl0506: makeCyberDragonFamilyRegistration(),
      pl0507: makeCyberDragonFamilyRegistration(),
      pl050f: makeCyberDragonFamilyRegistration(),
      pl0512: makeCyberDragonFamilyRegistration(),
      pl0513: makeCyberDragonFamilyRegistration(),
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
      // CYBER GIRL family (ctor 0x8012f204) — cue table @0x80333a60. All 3 members share
      // the bespoke X-special phase machine (borg-switched beam); see families/cyber-girl.ts.
      // pl0305/pl030a route through engine zz_012f728_ (PTR_FUN_80333a80, 3 phases);
      // pl0309 routes through engine zz_012fb20_ (PTR_FUN_804345c0, 2 phases). The leaf
      // FUN_8012f6f4 branches on borg number (0x309 vs others).
      pl0305: makeSimpleRegistration("pl0305", (a, ctx) => configureCyberGirlFamily(a, "pl0305", ctx)),
      pl0309: makeSimpleRegistration("pl0309", (a, ctx) => configureCyberGirlFamily(a, "pl0309", ctx)),
      pl030a: makeSimpleRegistration("pl030a", (a, ctx) => configureCyberGirlFamily(a, "pl030a", ctx)),
      // ---- Wave-B: batch-registered 2-borg families via shared engine (2026-07-06) ----
      // Generated by tmp_gen_regs.mjs: each entry pairs the family's data-driven cue
      // table (cueTableForBorg) with a shared-engine rootAction. Borgs whose X-special
      // stream bank/group/seedSlot has not yet been extracted get the cue table only —
      // rootAction stays null so the generic combat layer owns the X press.
      // REVOLVER GUNMAN / BILLY family (ctor 0x80072048) — both members not yet in registry.
      pl0100: makeSimpleRegistration("pl0100", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl0108: makeSimpleRegistration("pl0108", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // NORMAL TANK / LEOPARD family (ctor 0x8007ca5c) — both members not yet in registry.
      pl0c00: makeSimpleRegistration("pl0c00", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl0c06: makeSimpleRegistration("pl0c06", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // SAPPHIRE KNIGHT / RUBY KNIGHT family (ctor 0x800bb390) — both members not yet in registry.
      pl0208: makeSimpleRegistration("pl0208", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(2) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl020e: makeSimpleRegistration("pl020e", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(15) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // BATTLE GIRL / KEI family (ctor 0x800c04c0) — both members not yet in registry.
      pl0300: makeSimpleRegistration("pl0300", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl030b: makeSimpleRegistration("pl030b", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // ARROW NINJA / SHIJIMA family (ctor 0x800cfe9c) — both members not yet in registry.
      pl0002: makeSimpleRegistration("pl0002", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl000b: makeSimpleRegistration("pl000b", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // AXE KNIGHT / HATCHET KNIGHT family (ctor 0x800d6d10) — both members not yet in registry.
      pl0204: makeSimpleRegistration("pl0204", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl020d: makeSimpleRegistration("pl020d", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // MAGNET ROBOT (+) / MAGNET ROBOT (-) family (ctor 0x800da9fc) — both members not yet in registry.
      pl0405: makeSimpleRegistration("pl0405", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl0409: makeSimpleRegistration("pl0409", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // SPIKE KNIGHT / HAMMER KNIGHT family (ctor 0x800e5288) — both members not yet in registry.
      pl0203: makeSimpleRegistration("pl0203", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl020c: makeSimpleRegistration("pl020c", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // BEAM WING BLUE / BEAM WING RED family (ctor 0x800f9a28) — both members not yet in registry.
      pl0a03: makeSimpleRegistration("pl0a03", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl0a06: makeSimpleRegistration("pl0a06", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(1) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // COSMIC DRAGON / SPACE DRAGON family (ctor 0x80108954) — both members not yet in registry.
      pl0504: makeSimpleRegistration("pl0504", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl0510: makeSimpleRegistration("pl0510", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // ELEMENTAL KNIGHT / GHOST KNIGHT family (ctor 0x80123438) — both members not yet in registry.
      pl0202: makeSimpleRegistration("pl0202", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl020b: makeSimpleRegistration("pl020b", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(2) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // KILLER GIRL / SHADOW GIRL family (ctor 0x80134078) — both members not yet in registry.
      pl0304: makeSimpleRegistration("pl0304", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl0308: makeSimpleRegistration("pl0308", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(2) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // PHOENIX DRAGON / WING DRAGON family (ctor 0x80142674) — both members not yet in registry.
      pl0502: makeSimpleRegistration("pl0502", () => { /* no X-special in ROM; cue table only */ }),
      pl050e: makeSimpleRegistration("pl050e", () => { /* no X-special in ROM; cue table only */ }),
      // TELEPORT NINJA / SWITCHING NINJA family (ctor 0x801456d4) — both members not yet in registry.
      pl0005: makeSimpleRegistration("pl0005", () => { /* X-special stream not yet decoded; cue table only */ }),
      pl0009: makeSimpleRegistration("pl0009", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(4) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // DEMON WING / DEATH WING family (ctor 0x8014bd68) — both members not yet in registry.
      pl0a02: makeSimpleRegistration("pl0a02", () => { /* no X-special in ROM; cue table only */ }),
      pl0a07: makeSimpleRegistration("pl0a07", () => { /* no X-special in ROM; cue table only */ }),
      // GUARD WITCH / SHIELD WITCH family (ctor 0x80151790) — both members not yet in registry.
      pl0903: makeSimpleRegistration("pl0903", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl090a: makeSimpleRegistration("pl090a", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // PATRA WITCH / ISIS WITCH family (ctor 0x8015d674) — both members not yet in registry.
      pl0902: makeSimpleRegistration("pl0902", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl0909: makeSimpleRegistration("pl0909", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // SAMURAI SHOGUN / CHRONO SAMURAI family (ctor 0x80174d88) — both members not yet in registry.
      pl0704: makeSimpleRegistration("pl0704", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl0707: makeSimpleRegistration("pl0707", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(1) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // SIRIUS / DEATH ARC family (ctor 0x801898b0) — both members not yet in registry.
      pl0e00: makeSimpleRegistration("pl0e00", () => { /* X-special stream not yet decoded; cue table only */ }),
      pl0e05: makeSimpleRegistration("pl0e05", () => { /* X-special stream not yet decoded; cue table only */ }),
      // DEATH BORG BETA II / DEATH BORG BETA III family (ctor 0x80198490) — both members not yet in registry.
      pl0105: makeSimpleRegistration("pl0105", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl010a: makeSimpleRegistration("pl010a", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // DEATH BORG SIGMA / DEATH BORG SIGMA II family (ctor 0x8019cfdc) — both members not yet in registry.
      pl0a05: makeSimpleRegistration("pl0a05", () => { /* no X-special in ROM; cue table only */ }),
      pl0a0a: makeSimpleRegistration("pl0a0a", () => { /* no X-special in ROM; cue table only */ }),
      // DEATH BORG LAMBDA / DEATH BORG LAMBDA II family (ctor 0x8019e414) — valkrie-
      // cluster machines (families/valkrie.ts): action 0 = table-A B volley, action 1 =
      // table-B melee / table-C air lunge. NO action 2 in ROM (tables A-C only) — the
      // wave-B "cue table only" registration is composed with the ported rootAction.
      pl0b05: makeSimpleRegistration("pl0b05", (a, ctx) => configureValkrieFamily(a, "pl0b05", ctx)),
      pl0b07: makeSimpleRegistration("pl0b07", (a, ctx) => configureValkrieFamily(a, "pl0b07", ctx)),
      // DEATH BORG THETA / DEATH BORG IOTA family (ctor 0x801a10e8) — both members not yet in registry.
      pl0906: makeSimpleRegistration("pl0906", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl090b: makeSimpleRegistration("pl090b", () => { /* no X-special in ROM; cue table only */ }),
      // DEATH ICBM / DEATH BOMB family (ctor 0x801ae30c) — both members not yet in registry.
      pl0d06: makeSimpleRegistration("pl0d06", () => { /* no X-special in ROM; cue table only */ }),
      pl0d07: makeSimpleRegistration("pl0d07", () => { /* no X-special in ROM; cue table only */ }),
      // BASTET WITCH / SEKHMET WITCH family (ctor 0x801b3c6c) — both members not yet in registry.
      pl0907: makeSimpleRegistration("pl0907", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl090c: makeSimpleRegistration("pl090c", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // DEATH HEAD / MACHINE HEAD family (ctor 0x801e78c0) — both members not yet in registry.
      pl0505: makeSimpleRegistration("pl0505", () => { /* X-special stream not yet decoded; cue table only */ }),
      pl0511: makeSimpleRegistration("pl0511", () => { /* X-special stream not yet decoded; cue table only */ }),
      // ---- Wave-B: batch-register 6 three-borg families (2026-07-06) ----
      // Each family's ctor was searched in the corpus (actionStreamTables.json) to find
      // the X-special engine. Shared-vs-bespoke determination: leaf == engine in family
      // code block (not a cross-family zz_0177dd8_/zz_0179d20_/etc. address) → BESPOKE.
      // BESPOKE families get a families/<name>.ts port; the rest get cue table +
      // shared-engine fallback (cue table + createSharedEngineRootAction).

      // JELLY DIVER family (ctor 0x80114838) — BESPOKE X-special (FUN_80116808 →
      // PTR_FUN_80434550 phase machine, chunk_0031.c). 2-phase ammo-gated borg-switched
      // child deploy (zz_01213bc_); see families/jelly-diver.ts.
      pl0805: makeSimpleRegistration("pl0805", (a, ctx) => configureJellyDiverFamily(a, "pl0805", ctx)),
      pl080d: makeSimpleRegistration("pl080d", (a, ctx) => configureJellyDiverFamily(a, "pl080d", ctx)),
      pl080e: makeSimpleRegistration("pl080e", (a, ctx) => configureJellyDiverFamily(a, "pl080e", ctx)),
      // COPY MAN family (ctor 0x8015613c) — BESPOKE X-special (FUN_80156460 →
      // PTR_FUN_8034267c phase machine, chunk_0040.c). 3-phase borg-switched child deploy
      // (zz_01639c0_ / zz_00c4704_); see families/copy-man.ts.
      pl0806: makeSimpleRegistration("pl0806", (a, ctx) => configureCopyManFamily(a, "pl0806", ctx)),
      pl0809: makeSimpleRegistration("pl0809", (a, ctx) => configureCopyManFamily(a, "pl0809", ctx)),
      pl080f: makeSimpleRegistration("pl080f", (a, ctx) => configureCopyManFamily(a, "pl080f", ctx)),
      // ANGEL NURSE family (ctor 0x80079410) — BESPOKE X-special (FUN_8007bb6c →
      // PTR_FUN_802d6668, chunk_0011.c): 6-phase homing heal/deploy machine. Too complex
      // for batch port; registered with cue table + shared-engine fallback.
      pl0900: makeSimpleRegistration("pl0900", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl0908: makeSimpleRegistration("pl0908", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl090d: makeSimpleRegistration("pl090d", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // DEATH BORG OMEGA II/III/IV family (ctor 0x801d4590) — no action 2 in ROM; X
      // routes via action 0 (dash attack). Registered with cue table + shared-engine.
      pl040b: makeSimpleRegistration("pl040b", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl040c: makeSimpleRegistration("pl040c", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl040d: makeSimpleRegistration("pl040d", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // ANUBIS WING family (ctor 0x800f49a0) — no action 2 in ROM; X routes via action 3
      // (B charge, engine zz_0148384_). Registered with cue table + shared-engine.
      pl0a04: makeSimpleRegistration("pl0a04", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl0a08: makeSimpleRegistration("pl0a08", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl0a09: makeSimpleRegistration("pl0a09", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // DEATH BORG NU family (ctor 0x801b3598) — no action 2 in ROM; X routes via action 0
      // (dash attack, bespoke engine 0x801b372c). Registered with cue table + shared-engine.
      pl0f01: makeSimpleRegistration("pl0f01", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl0f02: makeSimpleRegistration("pl0f02", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      pl0f03: makeSimpleRegistration("pl0f03", (a) => { a.rootAction = createSharedEngineRootAction({ xSpecial: DEFAULT_CONFIGS.dashAttack(0) }); a.defaultGroup = 0; a.streamSlot = 0; }),
      // ---- Valkrie cluster (2026-07-06): 6 valkrie families on the 4 shared phase-table
      // machines ported in families/valkrie.ts (tables @0x8033ed68/ed78/ed88/0x804346b8;
      // engines zz_014a200_/zz_014a8c0_/zz_014ad94_/zz_014b22c_, chunk_0038.c). Action 0 =
      // B ranged volley, action 1 = B melee (v4 = air lunge), action 2 = X special. The
      // per-borg volley config blocks (count/timer/shot record) are DOL-read — see the
      // valkrie.ts header. DEATH BORG LAMBDA (pl0b05/pl0b07) shares tables A-C above.
      pl0b00: makeSimpleRegistration("pl0b00", (a, ctx) => configureValkrieFamily(a, "pl0b00", ctx)),
      pl0b01: makeSimpleRegistration("pl0b01", (a, ctx) => configureValkrieFamily(a, "pl0b01", ctx)),
      pl0b02: makeSimpleRegistration("pl0b02", (a, ctx) => configureValkrieFamily(a, "pl0b02", ctx)),
      pl0b03: makeSimpleRegistration("pl0b03", (a, ctx) => configureValkrieFamily(a, "pl0b03", ctx)),
      pl0b04: makeSimpleRegistration("pl0b04", (a, ctx) => configureValkrieFamily(a, "pl0b04", ctx)),
      pl0b06: makeSimpleRegistration("pl0b06", (a, ctx) => configureValkrieFamily(a, "pl0b06", ctx)),
    };

    // ---- Wave-C: bespoke B-melee engine wiring (2026-07-06, batch 2 — 48 borgs) ----
    // 4 bespoke B-melee dispatchers ported in families/melee-*.ts, each covering 12
    // borgs' action 1 (ground B-melee):
    //   zz_010c220_ (standing) + zz_010b7ac_ (lunge) — 12 girl/delta borgs (2 variants)
    //   zz_00f2374_ (3-phase)                         — 12 robot/omega borgs
    //   zz_0149178_ (config-driven lunge)            — 12 samurai/zeta borgs
    // Each borg's existing registration (X-special/dash/charge wiring) is preserved; the
    // bespoke melee is INJECTED at actionIndex 1 via withBespokeMelee. Borgs not yet in
    // the registry get a cue-table-only base registration first.

    // Girl group: variant <3 → standing (zz_010c220_), >=3 → lunge (zz_010b7ac_).
    const girlMelee = (ctx: GRedFamilyCtx): ((actor: RomActor) => void) => {
      const standing = createMeleeGirlStanding(ctx);
      const lunge = createMeleeGirlLunge(ctx);
      return (actor) => (actor.variantIndex >= 3 ? lunge : standing)(actor);
    };
    for (const id of [
      "pl0300", "pl0301", "pl0302", "pl0304", "pl0305", "pl0307",
      "pl0308", "pl0309", "pl030a", "pl030b", "pl030c", "pl030d",
    ] as const) {
      const base = FAMILY_REGISTRY_CACHE[id] ?? makeSimpleRegistration(id, () => {});
      FAMILY_REGISTRY_CACHE[id] = withBespokeMelee(base, girlMelee);
    }

    // Robot group: zz_00f2374_ (3-phase melee).
    const robotMeleeFactory = (ctx: GRedFamilyCtx) => createMeleeRobot(ctx);
    for (const id of [
      "pl0400", "pl0401", "pl0402", "pl0403", "pl0404", "pl0405",
      "pl0406", "pl0407", "pl0408", "pl0409", "pl040a", "pl040b",
    ] as const) {
      const base = FAMILY_REGISTRY_CACHE[id] ?? makeSimpleRegistration(id, () => {});
      FAMILY_REGISTRY_CACHE[id] = withBespokeMelee(base, robotMeleeFactory);
    }

    // Samurai group: zz_0149178_ (config-driven lunge melee).
    const samuraiMeleeFactory = (ctx: GRedFamilyCtx) =>
      createMeleeSamurai(ctx, SAMURAI_MELEE_DEFAULT_CONFIG);
    for (const id of [
      "pl0700", "pl0701", "pl0702", "pl0703", "pl0705", "pl0706",
      "pl0708", "pl0709", "pl070a", "pl070b", "pl070c", "pl070d",
    ] as const) {
      const base = FAMILY_REGISTRY_CACHE[id] ?? makeSimpleRegistration(id, () => {});
      FAMILY_REGISTRY_CACHE[id] = withBespokeMelee(base, samuraiMeleeFactory);
    }
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

/** Small helper: registration from a configure closure + the borg's data-driven cue table. */
function makeSimpleRegistration(
  borgId: string,
  configure: (actor: RomActor, ctx: GRedFamilyCtx) => void,
): FamilyRegistration {
  return { configure, cueTable: cueTableForBorg(borgId)! };
}

/** Compose a 5-slot actionTable rootAction from per-slot handlers (null = generic fallback). */
function composeActionTable(
  table: Array<((actor: RomActor) => void) | null>,
): (actor: RomActor) => void {
  return (actor: RomActor) => {
    const fn = table[actor.actionIndex];
    if (fn) fn(actor);
  };
}

/** Wrap an existing registration so the bespoke B-melee engine (action 1) is injected
 *  on top of whatever rootAction the base configure closure sets. The base configure
 *  runs first (stamping borgNumber + wiring X-special/dash/charge slots); then this
 *  wraps rootAction to route actionIndex 1 to the bespoke melee, preserving the base
 *  handler for all other action indices. Used by the batch-2 B-melee port to give 48
 *  borgs their real ROM B-melee without touching each family's X-special wiring. */
function withBespokeMelee(
  base: FamilyRegistration,
  melee: (ctx: GRedFamilyCtx) => (actor: RomActor) => void,
): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      base.configure(actor, ctx);
      const meleeHandler = melee(ctx);
      const existing = actor.rootAction;
      if (!existing) {
        actor.rootAction = (a) => {
          if (a.actionIndex === 1) { meleeHandler(a); return; }
        };
      } else {
        actor.rootAction = (a) => {
          if (a.actionIndex === 1) { meleeHandler(a); return; }
          existing(a);
        };
      }
    },
    cueTable: base.cueTable,
  };
}

/** Titan/Panther composite: morph engine at actionTable[2] + aimed-shot engine at [3]
 *  (the ROM's PTR_FUN_8032f41c/PTR_FUN_8036546c wiring, split across two shared modules). */
function makeMorphAimedComposite(
  borgId: string,
  borgNumber: number,
  morphCfg: Parameters<typeof createSharedMorphXSpecial>[0],
  aimedCfg: Parameters<typeof createSharedAimedShotX>[0],
): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      actor.borgNumber = borgNumber;
      actor.rootAction = composeActionTable([
        null,
        null,
        createSharedMorphXSpecial(morphCfg, ctx, {}),
        createSharedAimedShotX(aimedCfg, ctx),
        null,
      ]);
      actor.defaultGroup = 0;
      actor.streamSlot = 0;
    },
    cueTable: cueTableForBorg(borgId)!,
  };
}

function series3Registrations(): Record<string, FamilyRegistration> {
  const ids: Series3BorgId[] = ["pl0301", "pl0302", "pl0303", "pl0306", "pl0307", "pl030d"] as Series3BorgId[];
  const out: Record<string, FamilyRegistration> = {};
  for (const id of ids) {
    out[id] = makeSimpleRegistration(id, (a, ctx) => configureSeries3Family(a, id, ctx));
  }
  return out;
}

function lanceFlightRegistrations(): Record<string, FamilyRegistration> {
  const ids = ["pl0700", "pl0709", "pl0702", "pl070a", "pl0705", "pl070b"] as LanceFlightBorgId[];
  const out: Record<string, FamilyRegistration> = {};
  for (const id of ids) {
    out[id] = makeSimpleRegistration(id, (a, ctx) => configureLanceFlightFamily(a, id, ctx));
  }
  return out;
}

function makeDeathBorgFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => configureDeathBorgFamily(actor, "pl000c", ctx),
    cueTable: cueTableForBorg("pl000c")!,
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

// CYBER DEATH DRAGON family (ctor 0x800b8188) — cue table @0x802fec20. The X-special
// is a BESPOKE 3-variant phase machine (ground/air/charged breath) ported in
// families/cyber-dragon.ts; engines 0x800b96c4/0x800b9888/0x800b9a74 live in the
// family code block (not shared-engine ranges). All 6 members (pl0503/pl0506/pl0507/
// pl050f/pl0512/pl0513) share one module — the ctor block-copies the same +0x4b4
// binding; only FUN_800b866c's borg-id switch (animation record select) differs.
// Sister family to FLAME DRAGON (identical phase structure; no per-frame flame-child
// spawner — the contact calls zz_0098dbc_ instead, a shared kind-6 attack resolver).
function makeCyberDragonFamilyRegistration(): FamilyRegistration {
  return {
    configure: (actor, ctx) => {
      const id =
        actor.borgNumber === 0x506 ? "pl0506" :
        actor.borgNumber === 0x507 ? "pl0507" :
        actor.borgNumber === 0x50f ? "pl050f" :
        actor.borgNumber === 0x512 ? "pl0512" :
        actor.borgNumber === 0x513 ? "pl0513" : "pl0503";
      configureCyberDragonFamily(actor, id as "pl0503" | "pl0506" | "pl0507" | "pl050f" | "pl0512" | "pl0513", ctx);
    },
    cueTable: cueTableForBorg("pl0503")!,
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
  /** True when the ROM phase machine owns the borg's per-frame motion (B-charge's 4-phase
   *  zz_0179814_ machine). When true, tick() calls stepRomActor each frame and returns true
   *  so battle.ts skips stepMovement/stepAttacks. False for X-specials (which compose with
   *  normal movement — tick() returns false and only layers stream events). */
  private romOwnedSpecial = false;
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

  /** Called from combat.ts's B-attack branch (before startShotAttack/startMeleeAttack).
   *  Returns true if the ROM family's B-charge phase machine (zz_0179814_) handled the
   *  press — the caller skips the generic melee/shot path. Only intercepts when the borg's
   *  family explicitly wires a B-charge handler (RomActor.hasBCharge). Subsequent `tick`
   *  calls advance the 4-phase machine each frame (ROM owns motion until recovery). */
  tryStartBAttack(runtime: BorgRuntime, all: readonly BorgRuntime[]): boolean {
    if (this.specialActive) return false;
    if (!this.actor.hasBCharge) return false; // no ROM B-charge handler → generic path
    this.runtime = runtime;
    this.romOwnedSpecial = true;
    this.armedHits = [];
    this.streamFrame = 0;
    // Load pre-decoded stream events for the group-4 charge choreography (anim + fireChild).
    this.streamEvents = streamEventsFor(runtime.borgId);
    this.specialMaxFrames = 90; // generous ceiling; the phase machine's exit clears it sooner
    // Fire frame-0 events immediately (armHit + playAnim).
    this.dispatchEvent(0);
    this.streamFrame = 1;
    runtime.cooldowns["romSpecialActive"] = 1;
    this.specialActive = true;
    // Arm the action-mode bits so the phase-3 exit (controlWord &= ~0x3) can signal
    // completion. The ROM sets these on entering attack state (cue 44 → state 61).
    this.actor.controlWord = (this.actor.controlWord & ~0x3) | 0x1;
    // Run phase 0 immediately (same pattern as tryStartXSpecial): syncIn → dispatch the
    // command record (actionIndex 3 = B-charge) → stepRomActor (runs rootAction → phase 0)
    // → syncOut → bounds/ground clamps.
    const preX = runtime.pos.x;
    const preZ = runtime.pos.z;
    this.syncIn(runtime, all);
    dispatchCommandRecord(this.actor, { cueId: 44, stateMode: 3, actionIndex: 3, variantIndex: 0 });
    stepRomActor(this.actor, this.tables, this.ctx);
    this.syncOut(runtime);
    if (this.bounds) {
      runtime.pos.x = Math.min(this.bounds.maxX, Math.max(this.bounds.minX, runtime.pos.x));
      runtime.pos.z = Math.min(this.bounds.maxZ, Math.max(this.bounds.minZ, runtime.pos.z));
    }
    if (this.offMeshCheck && !this.offMeshCheck(runtime.pos.x, runtime.pos.z)) {
      runtime.pos.x = preX;
      runtime.pos.z = preZ;
    }
    if (this.groundClamp) {
      const clamped = this.groundClamp(runtime.pos, runtime.vel.y);
      if (clamped.y > runtime.pos.y) {
        runtime.pos.y = clamped.y;
        runtime.vel.y = Math.max(0, runtime.vel.y);
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

    // --- ROM-owned multi-frame machine (B-charge zz_0179814_): advance the 4-phase
    //     state machine each tick. Phase 0 armed in tryStartBAttack; phases 1-3 advance
    //     here via stepRomActor → rootAction → phase-table dispatch. Returns true so
    //     battle.ts skips stepMovement/stepAttacks (the ROM owns motion + facing). ---
    if (this.romOwnedSpecial) {
      const preX = runtime.pos.x;
      const preZ = runtime.pos.z;
      this.syncIn(runtime, all);
      // Re-dispatch the command record each frame so rootAction fires under state 61.
      dispatchCommandRecord(this.actor, { cueId: 44, stateMode: 3, actionIndex: 3, variantIndex: 0 });
      stepRomActor(this.actor, this.tables, this.ctx);
      this.syncOut(runtime);
      if (this.bounds) {
        runtime.pos.x = Math.min(this.bounds.maxX, Math.max(this.bounds.minX, runtime.pos.x));
        runtime.pos.z = Math.min(this.bounds.maxZ, Math.max(this.bounds.minZ, runtime.pos.z));
      }
      if (this.offMeshCheck && !this.offMeshCheck(runtime.pos.x, runtime.pos.z)) {
        runtime.pos.x = preX;
        runtime.pos.z = preZ;
      }
      if (this.groundClamp) {
        const clamped = this.groundClamp(runtime.pos, runtime.vel.y);
        if (clamped.y > runtime.pos.y) {
          runtime.pos.y = clamped.y;
          runtime.vel.y = Math.max(0, runtime.vel.y);
        }
      }
      // Stream events (anim + hitbox + fireChild) for this frame.
      this.dispatchEvent(this.streamFrame);
      this.streamFrame++;
      this.resolveHits(runtime, all);
      // Completion: the phase machine's phase-3 exit clears +0x5e0's action bits
      // (controlWord &= ~0x3). Detect that OR the max-frame safety timeout.
      const phaseDone = (this.actor.controlWord & 0x3) === 0 && this.streamFrame > 2;
      if (phaseDone || this.streamFrame >= this.specialMaxFrames) {
        this.specialActive = false;
        this.romOwnedSpecial = false;
        this.armedHits = [];
        this.streamEvents = null;
        runtime.cooldowns["romSpecialActive"] = 0;
      }
      return true; // ROM owns this frame — skip stepMovement/stepAttacks
    }

    // --- X-special path: layer stream events on top of normal movement (tick returns
    //     false → stepMovement + stepAttacks run normally). ---
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
    this.romOwnedSpecial = false;
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
