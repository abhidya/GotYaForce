// ROM-faithful 1:1 port of the GG4E battle-initialization spawn-from-slot-tables path.
//
// This materializes the active borgs from the force slot tables at battle start. It is the
// path the real game runs after `build_challenge_battle_setup` (0x801962c4,
// challenge_deobfuscated.c / chunk_0048.c:243) has filled the slot/team tables in
// PTR_DAT_80433934, and before the per-frame battle loop begins.
//
// Sources (decompiled, transcribed exactly):
//   - 0x800541ac `FUN_800541ac` `active_borg_spawn_init_from_slot_tables`
//     @ research/decomp/ghidra-export/chunk_0006.c:6999 — the per-active-borg spawn init.
//     The slot-table reads + field copies are at chunk_0006.c:7054-7080.
//   - 0x80057b78 `FUN_80057b78` `active_object_init_from_slot_tables`
//     @ research/decomp/ghidra-export/chunk_0007.c:896 — the sibling per-object init
//     (menu/garage + battle). Its slot-table reads at chunk_0007.c:917-921 are BYTE-FOR-BYTE
//     identical to FUN_800541ac's, confirming the four canonical copies below.
//   - Spawn-loop driver globals: PTR_DAT_80433934[0x15d9] = active-slot bitmask,
//     PTR_DAT_80433934[0x15da] = active count (chunk_0048.c:240,275-301; chunk_0000.c:1061).
//   - Slot-table layout + offset semantics: research/decomp/ghidra-export/challenge_deobfuscated.c
//     (enum ChallengeSlotOffset) and research/decomp/index/challenge-flow-evidence.md
//     ("Required Before Player-Facing Port": offsets 0x10, 0x20, 0x32, 0x3e, 0x5a, 0xa0, 0xcb).
//
// FIELD-MAP INVARIANT (object+0xNNN -> RomActor field, from packages/combat/src/rom/actor.ts):
//   +0x3e4 -> slot            +0x3e7 -> identityVariant   +0x3e8(=1000) -> borgNumber
//   +0x88  -> team            +0x94  -> borgMirror94       +0x96 -> carriedSlot96
//   +0x97  -> carriedVariant97
// (+0x3ec = borg level byte; RomActor has NO sink for it today — HP/gauges/level are owned by
//  BorgRuntime. The copy is still performed and captured in a sidecar; see getSpawnedLevel3ec.)
//
// This module does NOT edit battle.ts or actor.ts; see the integration spec at the bottom.

import { createRomActor } from "../rom/actor.js";
import type { RomActor } from "../rom/actor.js";

// -------------------------------------------------------------------------------------------------
// Slot-table offsets in PTR_DAT_80433934 (challenge_deobfuscated.c enum ChallengeSlotOffset).
// Only the three offsets consumed by the spawn copy are read; the others (0x20/0x32/0x3e/0x5a)
// are table-state writers that the spawn init never copies into the active object.
// -------------------------------------------------------------------------------------------------

/** PTR_DAT_80433934 byte offsets read by FUN_800541ac / FUN_80057b78. */
export const SLOT_TABLE_OFFSET = {
  /** 0x10: uint16[6] active borg id, indexed `slot*2` bytes. Copied into object+0x3e8. */
  ACTIVE_BORG_ID: 0x10,
  /** 0xa0: byte[6] active variant/level, indexed `slot`. Copied into object+0x3ec. */
  ACTIVE_VARIANT: 0xa0,
  /** 0xcb: byte[6] team (0=player/ally, 1=enemy, 0xff=unused), indexed `slot`. -> object+0x88. */
  TEAM: 0xcb,
  /** 0x15d9: bitmask; bit `slot` set = slot is active (spawn-loop driver). */
  ACTIVE_MASK: 0x15d9,
  /** 0x15da: active-slot count (derived from the mask; informational). */
  ACTIVE_COUNT: 0x15da,
} as const;

/** ROM slot count (challenge_deobfuscated.c: slot_team[6], loop 0..5). */
export const ROM_SLOT_COUNT = 6;

/** Team byte values written to PTR_DAT_80433934[slot + 0xcb] (chunk_0048.c:281-327). */
export const SLOT_TEAM = {
  PLAYER_ALLY: 0,
  ENEMY: 1,
  UNUSED: 0xff,
} as const;

/**
 * The slice of the ROM slot table (PTR_DAT_80433934) consumed by the spawn path. Callers
 * decode the byte-exact ROM layout into these arrays; the spawn copies then read them by
 * slot index, mirroring the pointer arithmetic in FUN_800541ac.
 */
export interface SlotTableState {
  /** [0x10] uint16[N]; the active borg id per slot (high byte = family, low = variant). */
  readonly activeBorgId: readonly number[];
  /** [0xa0] byte[N]; the active variant/level per slot (copied into object+0x3ec). */
  readonly activeVariant: readonly number[];
  /** [0xcb] byte[N]; the team byte per slot (0/1/0xff). */
  readonly slotTeam: readonly number[];
  /** [0x15d9] active-slot bitmask; bit `i` set => slot `i` spawns. */
  readonly activeMask: number;
}

export interface SpawnSlotTablesCtx {
  /** Number of slots to scan (ROM = 6). Defaults to ROM_SLOT_COUNT. */
  readonly slotCount?: number;
  /** Blank-actor factory; defaults to createRomActor. Inject to pre-wire physicsRuntime etc. */
  readonly createActor?: () => RomActor;
}

// -------------------------------------------------------------------------------------------------
// Per-actor sidecar for object+0x3ec (borg level). RomActor (actor.ts) has no +0x3ec field —
// level/HP/gauges are explicitly out-of-scope and owned by BorgRuntime. The copy is still
// performed (FUN_800541ac:7056 / FUN_80057b78:920 both write it), so it is captured here and
// surfaced via getSpawnedLevel3ec for the integration layer to route into BorgRuntime.
// -------------------------------------------------------------------------------------------------

const spawnedLevel3ec = new WeakMap<RomActor, number>();

/** @return the object+0x3ec level byte copied from slot-table offset 0xa0 at spawn time. */
export function getSpawnedLevel3ec(actor: RomActor): number {
  return spawnedLevel3ec.get(actor) ?? 0;
}

function readAt(arr: readonly number[], i: number): number {
  const v = arr[i];
  if (v === undefined) throw new RangeError(`spawnFromSlotTables: slot table index ${i} out of range`);
  return v;
}

// -------------------------------------------------------------------------------------------------
// Per-active-borg spawn init — 1:1 port of the slot-table-read block of FUN_800541ac
// (chunk_0006.c:7015-7080) and the identical block in FUN_80057b78 (chunk_0007.c:909-928).
//
// ROM (param_9 = object pointer, slot = param_9[0x3e4]):
//   7015: iVar4 = zz_00422d8_((int)param_9[0x3e4]);  if (!iVar4) return;   // slot-validity guard
//   ...
//   7054: param_9[999]    = param_9[0x3e4];                              // +0x3e7 = slot
//   7055: *(u16*)(+1000)  = *(u16*)(PTR + param_9[999]*2 + 0x10);        // +0x3e8 = activeBorgId
//   7056: param_9[0x3ec]  = PTR[param_9[999] + 0xa0];                    // +0x3ec = activeVariant
//   7057: param_9[0x88]   = PTR[param_9[0x3e4] + 0xcb];                  // +0x88  = slotTeam
//   ... (FUN_800541ac then sets +0x3ea/+0x3ed mirrors only when +0x490==0; +0x490 is a deploy-
//        mode flag out of scope for the slot-table copy and has no RomActor sink.)
//   7078: *(u16*)(+0x94)  = *(u16*)(+1000);                              // borgMirror94 = borgNumber
//   7079: param_9[0x96]   = param_9[0x3e4];                              // carriedSlot96 = slot
//   7080: param_9[0x97]   = param_9[999];                                // carriedVariant97 = +0x3e7
// -------------------------------------------------------------------------------------------------

/**
 * Apply the slot-table field copies to one actor. Mirrors the body of FUN_800541ac /
 * FUN_80057b78 for a single active slot. `actor.slot` (+0x3e4) is the entry condition and
 * is set first (in ROM it is pre-set by the caller before this function runs).
 */
export function initActorFromSlotTables(
  state: SlotTableState,
  slot: number,
  actor: RomActor,
): void {
  // Entry condition: object+0x3e4 is the slot index (set by the spawn-loop driver).
  actor.slot = slot; // +0x3e4

  // 7054: object+0x3e7 (999) = object+0x3e4 (slot).
  actor.identityVariant = slot; // +0x3e7

  // 7055: object+0x3e8 (1000) = PTR_DAT_80433934[slot*2 + 0x10] (uint16 active borg id).
  const borgNumber = readAt(state.activeBorgId, slot); // [0x10], u16
  actor.borgNumber = borgNumber; // +0x3e8

  // 7056: object+0x3ec = PTR_DAT_80433934[slot + 0xa0] (byte active variant/level).
  // No RomActor sink (+0x3ec owned by BorgRuntime); captured in the sidecar, not dropped.
  const level3ec = readAt(state.activeVariant, slot) & 0xff; // [0xa0], byte
  spawnedLevel3ec.set(actor, level3ec); // +0x3ec

  // 7057: object+0x88 = PTR_DAT_80433934[slot + 0xcb] (byte team: 0/1/0xff).
  actor.team = readAt(state.slotTeam, slot) & 0xff; // +0x88

  // 7078-7080: the +0x94/+0x96/+0x97 identity mirrors (FUN_800541ac sets these just before
  // the engine-attach calls; FUN_80057b78 sets the same triple at chunk_0007.c:926-928).
  actor.borgMirror94 = borgNumber; // +0x94 = +0x3e8
  actor.carriedSlot96 = slot; // +0x96 = +0x3e4
  actor.carriedVariant97 = actor.identityVariant; // +0x97 = +0x3e7
}

// -------------------------------------------------------------------------------------------------
// Spawn loop — materialize every active borg. The ROM driver scans the active-slot bitmask
// PTR_DAT_80433934[0x15d9] and runs FUN_800541ac once per active slot (chunk_0000.c:1061,
// chunk_0044.c:102-113, chunk_0048.c:286-333 all populate the mask; chunk_0003.c:4832/6391
// and chunk_0015.c:3797 iterate it the same way). This port scans bit `i` for i in 0..slotCount.
// -------------------------------------------------------------------------------------------------

/**
 * Materialize the active borgs from the slot tables. Returns one RomActor per ACTIVE slot
 * (bit set in `state.activeMask` and team != 0xff), with the exact field copies from
 * FUN_800541ac applied. Actors are returned in ascending slot order.
 */
export function spawnActiveBorgsFromSlotTables(
  state: SlotTableState,
  ctx?: SpawnSlotTablesCtx,
): RomActor[] {
  const slotCount = ctx?.slotCount ?? ROM_SLOT_COUNT;
  const createActor = ctx?.createActor ?? createRomActor;
  const out: RomActor[] = [];
  for (let slot = 0; slot < slotCount; slot++) {
    // Spawn-loop driver: bit `slot` of PTR_DAT_80433934[0x15d9].
    if (((state.activeMask >>> slot) & 1) === 0) continue;
    // zz_00422d8_ slot-validity guard equivalent: a slot whose team byte is 0xff was marked
    // unused by build_challenge_battle_setup (chunk_0048.c:281) and never spawns.
    if ((readAt(state.slotTeam, slot) & 0xff) === SLOT_TEAM.UNUSED) continue;
    const actor = createActor();
    initActorFromSlotTables(state, slot, actor);
    out.push(actor);
  }
  return out;
}

// -------------------------------------------------------------------------------------------------
// Deliverable: the exact slot-table offset -> RomActor-field map (confirmed copies only).
// -------------------------------------------------------------------------------------------------

export interface SlotTableFieldCopy {
  readonly slotTableOffset: number;
  readonly slotIndexing: "slot*2 (u16)" | "slot (byte)";
  readonly objectOffset: number;
  readonly romActorField: keyof RomActor | "(no sink: +0x3ec captured via getSpawnedLevel3ec)";
  readonly source: string;
}

export function slotTableOffsetFieldMap(): readonly SlotTableFieldCopy[] {
  return [
    {
      slotTableOffset: SLOT_TABLE_OFFSET.ACTIVE_BORG_ID,
      slotIndexing: "slot*2 (u16)",
      objectOffset: 0x3e8,
      romActorField: "borgNumber",
      source: "chunk_0006.c:7055; chunk_0007.c:918-919",
    },
    {
      slotTableOffset: SLOT_TABLE_OFFSET.ACTIVE_VARIANT,
      slotIndexing: "slot (byte)",
      objectOffset: 0x3ec,
      romActorField: "(no sink: +0x3ec captured via getSpawnedLevel3ec)",
      source: "chunk_0006.c:7056; chunk_0007.c:920",
    },
    {
      slotTableOffset: SLOT_TABLE_OFFSET.TEAM,
      slotIndexing: "slot (byte)",
      objectOffset: 0x88,
      romActorField: "team",
      source: "chunk_0006.c:7057; chunk_0007.c:921",
    },
    // Identity-mirror copies (object-internal, not slot-table reads, but part of the same
    // spawn-init block — listed for completeness so the full +0x94/+0x96/+0x97/+0x3e7 chain
    // is auditable alongside the slot-table reads).
    {
      slotTableOffset: -1,
      slotIndexing: "slot (byte)",
      objectOffset: 0x3e7,
      romActorField: "identityVariant",
      source: "chunk_0006.c:7054 (= +0x3e4); chunk_0007.c:917",
    },
    {
      slotTableOffset: -1,
      slotIndexing: "slot (byte)",
      objectOffset: 0x94,
      romActorField: "borgMirror94",
      source: "chunk_0006.c:7078 (= +0x3e8); chunk_0007.c:926",
    },
    {
      slotTableOffset: -1,
      slotIndexing: "slot (byte)",
      objectOffset: 0x96,
      romActorField: "carriedSlot96",
      source: "chunk_0006.c:7079 (= +0x3e4); chunk_0007.c:927",
    },
    {
      slotTableOffset: -1,
      slotIndexing: "slot (byte)",
      objectOffset: 0x97,
      romActorField: "carriedVariant97",
      source: "chunk_0006.c:7080 (= +0x3e7); chunk_0007.c:928",
    },
  ];
}

// -------------------------------------------------------------------------------------------------
// Self-tests. Caller-supplied assert (matches the runSpawnFromSlotTablesSelfTests(assert)
// contract); a failing assertion throws/flags per the host runner.
// -------------------------------------------------------------------------------------------------

export interface SpawnTestAssert {
  /** Fail the test with a message when `condition` is false. */
  (condition: boolean, message: string): void;
}

/**
 * Build a SlotTableState for a small force. `entries[i] = [borgId, variant, team]` for slot i,
 * active slots derived from the teams given (slots past the list are inactive).
 */
function buildSampleSlotTable(
  entries: ReadonlyArray<readonly [borgId: number, variant: number, team: number]>,
  slotCount = ROM_SLOT_COUNT,
): SlotTableState {
  const activeBorgId = new Array<number>(slotCount).fill(0);
  const activeVariant = new Array<number>(slotCount).fill(0);
  const slotTeam = new Array<number>(slotCount).fill(SLOT_TEAM.UNUSED);
  let activeMask = 0;
  for (let i = 0; i < entries.length; i++) {
    const [borgId, variant, team] = entries[i]!;
    activeBorgId[i] = borgId;
    activeVariant[i] = variant;
    slotTeam[i] = team;
    if (team !== SLOT_TEAM.UNUSED) activeMask |= 1 << i;
  }
  return { activeBorgId, activeVariant, slotTeam, activeMask };
}

/**
 * Self-tests for the spawn-from-slot-tables path. Covers a sample 3-borg force and verifies
 * the confirmed field copies (team/slot/borgNumber/type-category) are exact, the identity
 * mirrors (+0x94/+0x96/+0x97/+0x3e7) are faithful, unused slots are skipped, and the +0x3ec
 * level copy is captured by the sidecar.
 */
export function runSpawnFromSlotTablesSelfTests(assert: SpawnTestAssert): void {
  // Sample force mirroring the spawn-pool byte packing (behavior-notes.md (n)):
  //   borgId high byte = family, low byte = variant. pl#### ids map to these u16 ids at spawn.
  const state = buildSampleSlotTable([
    [0x0615, 2, SLOT_TEAM.PLAYER_ALLY], // slot 0: G RED family, player/ally
    [0x0629, 0, SLOT_TEAM.PLAYER_ALLY], // slot 1: NEO G RED family, player/ally
    [0x0200, 5, SLOT_TEAM.ENEMY], // slot 2: Sword Knight family, enemy
    // slots 3..5 left UNUSED (team 0xff) — must be skipped.
  ]);

  const actors = spawnActiveBorgsFromSlotTables(state);
  assert(actors.length === 3, `expected 3 active borgs, got ${actors.length}`);

  // --- Slot 0: G RED -----------------------------------------------------------
  const a0 = actors[0]!;
  assert(a0.slot === 0, `slot0 slot=${a0.slot}`);
  assert(a0.team === SLOT_TEAM.PLAYER_ALLY, `slot0 team=${a0.team}`);
  assert(a0.borgNumber === 0x0615, `slot0 borgNumber=0x${a0.borgNumber.toString(16)}`);
  // object+1000 (0x3e8) is the type-category source (challenge-flow-evidence.md:149).
  assert(a0.borgNumber === 0x0615, `slot0 type-category source (borgNumber) mismatch`);
  assert(a0.identityVariant === 0, `slot0 +0x3e7=${a0.identityVariant}`);
  assert(a0.borgMirror94 === 0x0615, `slot0 +0x94=${a0.borgMirror94.toString(16)}`);
  assert(a0.carriedSlot96 === 0, `slot0 +0x96=${a0.carriedSlot96}`);
  assert(a0.carriedVariant97 === 0, `slot0 +0x97=${a0.carriedVariant97}`);
  assert(getSpawnedLevel3ec(a0) === 2, `slot0 +0x3ec level=${getSpawnedLevel3ec(a0)}`);

  // --- Slot 1: NEO G RED -------------------------------------------------------
  const a1 = actors[1]!;
  assert(a1.slot === 1, `slot1 slot=${a1.slot}`);
  assert(a1.team === SLOT_TEAM.PLAYER_ALLY, `slot1 team=${a1.team}`);
  assert(a1.borgNumber === 0x0629, `slot1 borgNumber=0x${a1.borgNumber.toString(16)}`);
  assert(a1.identityVariant === 1, `slot1 +0x3e7=${a1.identityVariant}`);
  assert(a1.borgMirror94 === 0x0629, `slot1 +0x94=${a1.borgMirror94.toString(16)}`);
  assert(a1.carriedSlot96 === 1, `slot1 +0x96=${a1.carriedSlot96}`);
  assert(a1.carriedVariant97 === 1, `slot1 +0x97=${a1.carriedVariant97}`);
  assert(getSpawnedLevel3ec(a1) === 0, `slot1 +0x3ec level=${getSpawnedLevel3ec(a1)}`);

  // --- Slot 2: enemy Sword Knight ---------------------------------------------
  const a2 = actors[2]!;
  assert(a2.slot === 2, `slot2 slot=${a2.slot}`);
  assert(a2.team === SLOT_TEAM.ENEMY, `slot2 team=${a2.team}`);
  assert(a2.borgNumber === 0x0200, `slot2 borgNumber=0x${a2.borgNumber.toString(16)}`);
  assert(a2.identityVariant === 2, `slot2 +0x3e7=${a2.identityVariant}`);
  assert(a2.borgMirror94 === 0x0200, `slot2 +0x94=${a2.borgMirror94.toString(16)}`);
  assert(a2.carriedSlot96 === 2, `slot2 +0x96=${a2.carriedSlot96}`);
  assert(a2.carriedVariant97 === 2, `slot2 +0x97=${a2.carriedVariant97}`);
  assert(getSpawnedLevel3ec(a2) === 5, `slot2 +0x3ec level=${getSpawnedLevel3ec(a2)}`);

  // --- Unused slots are never materialized ------------------------------------
  const noActorsPastSlot2 = actors.every((a) => a.slot < 3);
  assert(noActorsPastSlot2, "unused slots (team 0xff) should not spawn");

  // --- activeMask gating: a cleared bit skips a slot even with a valid team ---
  const partial = buildSampleSlotTable([
    [0x0615, 0, SLOT_TEAM.PLAYER_ALLY],
    [0x0200, 0, SLOT_TEAM.ENEMY],
    [0x0629, 0, SLOT_TEAM.ENEMY],
  ]);
  // Clear slot 1's bit -> only slots 0 and 2 spawn.
  const masked: SlotTableState = { ...partial, activeMask: partial.activeMask & ~(1 << 1) };
  const maskedActors = spawnActiveBorgsFromSlotTables(masked);
  assert(maskedActors.length === 2, `masked force should spawn 2, got ${maskedActors.length}`);
  assert(maskedActors[0]!.slot === 0 && maskedActors[1]!.slot === 2, "masked force skipped wrong slots");

  // --- Field-map deliverable sanity -------------------------------------------
  const map = slotTableOffsetFieldMap();
  const teamCopy = map.find((m) => m.objectOffset === 0x88);
  assert(!!teamCopy && teamCopy.romActorField === "team", "field map missing +0x88 -> team");
  const borgCopy = map.find((m) => m.objectOffset === 0x3e8);
  assert(!!borgCopy && borgCopy.romActorField === "borgNumber", "field map missing +0x3e8 -> borgNumber");
}

/* -------------------------------------------------------------------------------------------------
 * INTEGRATION SPEC (delivered here; battle.ts / main.ts are NOT modified by this task).
 *
 * Today's battle spawn path (packages/combat/src/battle.ts BattleImpl.deployNext, called from
 * the constructor at line 242) builds a BorgRuntime per force directly from cfg.forces[].borgIds
 * — a force-list model, NOT the ROM's slot-table model. apps/game/src/gameSession.ts
 * prepareBattle() (line 357) calls createBattle(combatConfig, borgStats); main.ts enterBattle()
 * (line 805) drives it. To route battle start through this ROM-faithful path:
 *
 * 1. Build a SlotTableState from the battle config, mirroring build_challenge_battle_setup:
 *    - activeBorgId[slot]    = the u16 borg id for that slot (decode from the roster/pl id)
 *    - activeVariant[slot]   = the slot's variant/level byte
 *    - slotTeam[slot]        = 0 (player/ally) | 1 (enemy) | 0xff (unused)
 *    - activeMask            = OR of (1 << slot) for every staffed slot
 *    (For Versus, cfg.forces already carries team + borgIds; map force `i` to slot `i`, set
 *     unused slots to 0xff. For Challenge, the roster builder in packages/missions fills these.)
 *
 * 2. Call spawnActiveBorgsFromSlotTables(state) once at prepareBattle time, BEFORE construct ing
 *    BorgRuntime. This yields RomActor[] with team/slot/borgNumber/type-category set exactly
 *    as the ROM sets them. Then fold each RomActor into the BorgRuntime that deployNext
 *    creates today:
 *      borgRuntime.team    = romActor.team        // +0x88 (replaces force.team)
 *      borgRuntime.borgId  = plIdFor(romActor.borgNumber)  // +0x3e8 -> roster id
 *      level / paramTier   <- getSpawnedLevel3ec(romActor) // +0x3ec, currently dropped
 *    The remaining RomActor identity mirrors (+0x94/+0x96/+0x97/+0x3e7) feed the ROM family
 *    driver (bridge.ts RomDriverBridge.attachToBattle), which already consumes RomActor.
 *
 * 3. Keep deployNext's per-force FIFO queue for death -> auto-deploy: the slot-table path is
 *    the BATTLE-START materialization only (one active borg per slot). Subsequent deploys after
 *    a death re-run initActorFromSlotTables on the next roster id for that slot — the ROM
 *    reuses FUN_800541ac for respawn too (chunk_0006.c:7072 +0x3f0 respawn counter), so the
 *    same field copies apply verbatim.
 *
 * OPEN DEPS (block full integration; cite when wiring):
 *   - pl-id <-> u16 borgNumber table: behavior-notes.md (n) flags the 208-entry roster map as
 *     "still open". Until resolved, borgNumber must be derived per-force (it already is, via
 *     cfg.forces[].borgIds -> the pl id -> the family/variant bytes).
 *   - object+0x3ec (level) has no BorgRuntime sink today; route into paramTier/level when the
 *     level-byte -> damage-formula path (behavior-notes.md (ak)) is ported.
 *   - object+0x3ea/+0x3ed conditional mirrors (FUN_800541ac:7060-7062, gated on +0x490==0) have
 *     no RomActor sink; port when the +0x490 deploy-mode flag is decoded.
 * ------------------------------------------------------------------------------------------------- */
