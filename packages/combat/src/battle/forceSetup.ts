// ROM-faithful 1:1 port of the GG4E force-setup slot/team table WRITERS.
//
// This is the write-side complement to spawnFromSlotTables.ts (the READER). Where the
// reader materializes active borgs FROM the slot tables at battle start, this module
// populates the slot tables from a resolved player force — i.e. it ports the writes that
// `build_challenge_battle_setup` (0x801962c4, chunk_0048.c:234-409) performs against the
// PTR_DAT_80433934 work block. The reader then round-trips the four confirmed offsets
// (0x10/0xa0/0xcb/0x15d9) back into RomActors byte-for-byte.
//
// Sources (decompiled, transcribed exactly):
//   - 0x801962c4 `build_challenge_battle_setup` @ research/decomp/ghidra-export/chunk_0048.c:234.
//     Every slot-table write for the offsets below lives in this one function
//     (confirmed by grep: chunk_0048.c:273-378 are the ONLY writes to 0x10/0x20/0x32/
//     0x3e/0x5a/0xa0/0xcb/0x15d9/0x15da in the corpus; lines 3146+ are READS).
//   - Side-flag table DAT_804356ec (the [slot+0x32] source):
//     research/decomp/data/challenge-battle-tables-8036f360.json `DAT_804356ec_sideValues`.
//   - Spawn-side field map: packages/combat/src/battle/spawnFromSlotTables.ts
//     (SLOT_TABLE_OFFSET + slotTableOffsetFieldMap).
//
// SCOPE: this port covers the byte-layout writes that feed the spawn reader. The ROM
// function also (a) decides team membership from a controller mask (loop 1) and (b)
// auto-fills CPU rosters from pool tables under a budget cap (loop 2 inner). Those
// decisions are already ported in apps/game/src/ui/intro/challengeFlowVm.ts (mode 3) —
// `writeForceToSlotTables` consumes a FORCE ALREADY RESOLVED by that path (or by a
// Versus cfg.forces) and performs the ROM-faithful byte writes. The CPU roster ROLL
// (zz_0196eb8_/zz_0066168_) is intentionally NOT re-implemented here; it is owned by
// the challenge-flow VM + its sink.
//
// FIELD-MAP INVARIANT (mirror of spawnFromSlotTables.ts):
//   PTR_DAT_80433934[slot*2 + 0x10] -> activeBorgId[slot]  (u16)  -> actor.borgNumber (+0x3e8)
//   PTR_DAT_80433934[slot     + 0xa0] -> activeVariant[slot] (byte) -> actor +0x3ec (level)
//   PTR_DAT_80433934[slot     + 0xcb] -> slotTeam[slot]     (byte) -> actor.team (+0x88)
//   PTR_DAT_80433934[0x15d9]          -> activeMask         (u32)  -> spawn-loop driver
//   PTR_DAT_80433934[0x15da]          -> activeCount        (byte) -> informational
//
// This module does NOT edit spawnFromSlotTables.ts, battle.ts, or challengeFlowVm.ts;
// see the integration spec at the bottom.

import type { SlotTableState } from "./spawnFromSlotTables.js";
import { ROM_SLOT_COUNT, SLOT_TEAM } from "./spawnFromSlotTables.js";
import {
  spawnActiveBorgsFromSlotTables,
  getSpawnedLevel3ec,
} from "./spawnFromSlotTables.js";
import type { RomActor } from "../rom/actor.js";

// -------------------------------------------------------------------------------------------------
// ROM-faithful constants from build_challenge_battle_setup.
// -------------------------------------------------------------------------------------------------

/** [slot+0x20] constant written for every slot (chunk_0048.c:365). */
export const SLOT_CONST_0x20 = 0x0e;
/** [slot+0x3e] constant written for every slot (chunk_0048.c:367). */
export const SLOT_CONST_0x3e = 0x03;
/** [slot+0x54] constant written for every slot (chunk_0048.c:376). */
export const SLOT_CONST_0x54 = 0x00;

/**
 * DAT_804356ec — the [slot+0x32] side-flag source (chunk_0048.c:373-375). Indexed as
 * `table[team + difficulty*2]`. Dumped verbatim from
 * research/decomp/data/challenge-battle-tables-8036f360.json `DAT_804356ec_sideValues`:
 *   normal (diff 0): side0=7, side1=4
 *   tuff   (diff 1): side0=7, side1=7
 *   insane (diff 2): side0=7, side1=12
 */
export const DAT_804356EC_SIDE_FLAGS: readonly number[] = [
  7, 4, // difficulty 0 (normal): team 0, team 1
  7, 7, // difficulty 1 (tuff):   team 0, team 1
  7, 12, // difficulty 2 (insane):  team 0, team 1
];

/** Difficulty labels for the DAT_804356ec table indices. */
export const SLOT_DIFFICULTY = {
  NORMAL: 0,
  TUFF: 1,
  INSANE: 2,
} as const;

// -------------------------------------------------------------------------------------------------
// Slot-table state. This is the write-side companion to spawnFromSlotTables.SlotTableState:
// it carries the four reader-consumed arrays PLUS the extra ROM-written fields the spawn
// path never reads (0x20/0x32/0x3e/0x5a/0x54/0x15da). A MutableSlotTableState is
// structurally assignable to SlotTableState, so the reader consumes it directly.
// -------------------------------------------------------------------------------------------------

/**
 * Mutable slot-table state. Mirrors the slice of PTR_DAT_80433934 that
 * build_challenge_battle_setup writes. The four fields marked "(reader)" are what
 * spawnActiveBorgsFromSlotTables reads back; the rest are ROM-faithful for completeness.
 */
export interface MutableSlotTableState {
  /** [slot*2 + 0x10] u16 active borg id per slot. (reader) */
  activeBorgId: number[];
  /** [slot + 0xa0] byte active variant/level per slot. (reader) */
  activeVariant: number[];
  /** [slot + 0xcb] byte team per slot (0/1/0xff). (reader) */
  slotTeam: number[];
  /** [0x15d9] active-slot bitmask; bit `slot` set => spawns. (reader) */
  activeMask: number;

  /** [0x15da] active-slot count (derived from the mask; informational). */
  activeCount: number;
  /** [slot + 0x5a] byte roster count per slot (borgs available to that slot). */
  slotRosterCount: number[];
  /** [slot + 0x20] byte constant (0x0e) per slot. */
  slotConst20: number[];
  /** [slot + 0x3e] byte constant (0x03) per slot. */
  slotConst3e: number[];
  /** [slot + 0x32] byte side flag (DAT_804356ec[team + difficulty*2]) per slot. */
  slotFlag32: number[];
  /** [slot + 0x54] byte constant (0x00) per slot. */
  slotConst54: number[];
}

/**
 * Create a blank slot-table state with `slotCount` slots, mirroring the cleared
 * PTR_DAT_80433934 work block at the top of build_challenge_battle_setup (the block is
 * zeroed by init_challenge_flow_state @0x80195fbc; build_challenge_battle_setup clears
 * [0x15d9]/[0x15da] explicitly at chunk_0048.c:275/277). All slots start UNUSED (team
 * 0xff, no active bit), matching the post-clear state.
 */
export function createSlotTableState(slotCount: number = ROM_SLOT_COUNT): MutableSlotTableState {
  const n = slotCount;
  return {
    activeBorgId: new Array<number>(n).fill(0),
    activeVariant: new Array<number>(n).fill(0),
    slotTeam: new Array<number>(n).fill(SLOT_TEAM.UNUSED),
    activeMask: 0, // [0x15d9] = 0 (chunk_0048.c:275)
    activeCount: 0, // [0x15da] = 0 (chunk_0048.c:277)
    slotRosterCount: new Array<number>(n).fill(0),
    slotConst20: new Array<number>(n).fill(0),
    slotConst3e: new Array<number>(n).fill(0),
    slotFlag32: new Array<number>(n).fill(0),
    slotConst54: new Array<number>(n).fill(0),
  };
}

// -------------------------------------------------------------------------------------------------
// Force input shape. One ForceSlotEntry per ROM slot; the caller resolves controller
// masks / CPU auto-fill / Versus cfg.forces into this shape before writing.
// -------------------------------------------------------------------------------------------------

/**
 * One slot's resolved force entry, mirroring the fields build_challenge_battle_setup
 * writes for a staffed slot. A team of 0xff marks the slot UNUSED (no write to the
 * active fields; the spawn reader skips it).
 */
export interface ForceSlotEntry {
  /**
   * u16 borg number (high byte = family, low = variant). Source: the first roster
   * entry at PTR_DAT_80433934[slot*0x348 + 0x1e8] (chunk_0048.c:377). Written to
   * [slot*2 + 0x10] and read back as actor.borgNumber (+0x3e8).
   */
  readonly borgNumber: number;
  /**
   * Byte variant/level. Source: the first roster entry at [slot*0x348 + 0x1ea]
   * (chunk_0048.c:378). Written to [slot + 0xa0] and read back into actor +0x3ec.
   */
  readonly variant: number;
  /**
   * Team byte: 0 = player/ally, 1 = enemy, 0xff = unused. Written to [slot + 0xcb]
   * (chunk_0048.c:281/284/321/327) and read back as actor.team (+0x88).
   */
  readonly team: number;
  /**
   * Optional roster depth for this slot (>= 1 for a staffed slot). Written to
   * [slot + 0x5a] (chunk_0048.c:316/334/360). Defaults to 1 for staffed slots
   * (one active borg); set higher when the caller models a death→swap roster.
   */
  readonly rosterCount?: number;
}

export interface ForceSetupCtx {
  /** Number of slots to write (ROM = 6). Defaults to ROM_SLOT_COUNT. */
  readonly slotCount?: number;
  /** Difficulty 0/1/2 for the [slot+0x32] side-flag lookup. Defaults to NORMAL. */
  readonly difficulty?: number;
  /**
   * Override the DAT_804356ec side-flag table (rarely needed; defaults to the dumped
   * ROM bytes). Indexed as table[team + difficulty*2].
   */
  readonly sideFlagTable?: readonly number[];
}

// -------------------------------------------------------------------------------------------------
// writeForceToSlotTables — 1:1 port of the slot-table write sequence in
// build_challenge_battle_setup (chunk_0048.c:273-378). The ROM iterates 6 slots and,
// per slot, writes team/roster/active fields. Here the team+borgNumber+variant come from
// the resolved `playerForce`; the active mask/count and the constant per-slot writes are
// performed exactly as the ROM does them.
// -------------------------------------------------------------------------------------------------

function sideFlagFor(
  team: number,
  difficulty: number,
  table: readonly number[],
): number {
  // chunk_0048.c:373-375: DAT_804356ec[(int)(char)slotTeam[slot] + difficulty*2].
  // team is 0/1 for staffed slots; 0xff (unused) would read OOB in the ROM — the
  // challengeFlowVm.ts port notes this is harmless (unused slots never spawn). We
  // return 0 for unused slots rather than indexing OOB.
  if (team === SLOT_TEAM.PLAYER_ALLY || team === SLOT_TEAM.ENEMY) {
    const idx = team + difficulty * 2;
    const v = table[idx];
    if (v === undefined) {
      throw new RangeError(`forceSetup: sideFlag table has no index ${idx}`);
    }
    return v & 0xff;
  }
  return 0; // unused slot: ROM reads OOB; we emit 0 (never spawned).
}

/**
 * Populate `state` from `playerForce`, mirroring the slot-table writes of
 * build_challenge_battle_setup. Iterates `slotCount` slots; for each slot `i`:
 *  - reads team/borgNumber/variant from `playerForce[i]` (or marks the slot UNUSED
 *    when the force has no entry / entry.team === 0xff);
 *  - writes the per-slot team ([slot+0xcb]), active borg id ([slot*2+0x10]), active
 *    variant ([slot+0xa0]);
 *  - accumulates the active-slot bitmask ([0x15d9]) and count ([0x15da]);
 *  - writes the per-slot constants ([slot+0x20]=0x0e, [slot+0x3e]=0x03, [slot+0x54]=0),
 *    the side flag ([slot+0x32] from DAT_804356ec), and the roster count ([slot+0x5a]).
 *
 * After this returns, `state` is a valid SlotTableState for
 * spawnActiveBorgsFromSlotTables and will round-trip the staffed slots byte-for-byte.
 */
export function writeForceToSlotTables(
  state: MutableSlotTableState,
  playerForce: readonly ForceSlotEntry[],
  ctx?: ForceSetupCtx,
): void {
  const slotCount = ctx?.slotCount ?? ROM_SLOT_COUNT;
  const difficulty = ctx?.difficulty ?? SLOT_DIFFICULTY.NORMAL;
  const sideFlagTable = ctx?.sideFlagTable ?? DAT_804356EC_SIDE_FLAGS;

  if (slotCount < 0 || slotCount > 32) {
    throw new RangeError(`forceSetup: slotCount ${slotCount} out of range (0..32)`);
  }
  if (state.activeBorgId.length < slotCount ||
      state.activeVariant.length < slotCount ||
      state.slotTeam.length < slotCount ||
      state.slotRosterCount.length < slotCount ||
      state.slotConst20.length < slotCount ||
      state.slotConst3e.length < slotCount ||
      state.slotFlag32.length < slotCount ||
      state.slotConst54.length < slotCount) {
    throw new RangeError("forceSetup: state arrays shorter than slotCount");
  }

  // --- Init block (chunk_0048.c:275/277): clear active mask + count. ---
  state.activeMask = 0;
  state.activeCount = 0;

  // --- Per-slot writes (chunk_0048.c:278-378, loops 1+2 collapsed). ---
  // The ROM derives team from a controller mask (loop 1) then auto-fills CPU slots
  // (loop 2). Here the team is already resolved in playerForce[i]; we apply it
  // directly and perform the common per-slot writes uniformly.
  for (let slot = 0; slot < slotCount; slot++) {
    const entry = slot < playerForce.length ? playerForce[slot] : undefined;
    const team = entry ? (entry.team & 0xff) : SLOT_TEAM.UNUSED;
    const isStaffed = team !== SLOT_TEAM.UNUSED;

    // [slot + 0xcb] team byte (chunk_0048.c:281/284/291/294/321/327).
    state.slotTeam[slot] = team;

    if (isStaffed) {
      // [slot*2 + 0x10] u16 active borg id = first roster entry's borg id
      // (chunk_0048.c:377: *(u16*)(PTR + slot*2 + 0x10) = *(u16*)(PTR + slot*0x348 + 0x1e8)).
      const borgNumber = entry!.borgNumber & 0xffff;
      state.activeBorgId[slot] = borgNumber;

      // [slot + 0xa0] byte active variant = first roster entry's variant byte
      // (chunk_0048.c:378: PTR[slot + 0xa0] = PTR[slot*0x348 + 0x1ea]).
      state.activeVariant[slot] = entry!.variant & 0xff;

      // [0x15d9] |= (1 << slot) and [0x15da] += 1
      // (chunk_0048.c:286-287 loop1, 296-297 loop1, 331-333 loop2).
      state.activeMask |= 1 << slot;
      state.activeCount += 1;

      // [slot + 0x5a] roster count (chunk_0048.c:316 reset, 360 ++ per rolled borg).
      // For a staffed player slot the ROM has >= 1 roster entry (the active borg);
      // the caller may override via entry.rosterCount to model a death→swap roster.
      const roster = entry!.rosterCount ?? 1;
      state.slotRosterCount[slot] = roster & 0xff;
    } else {
      // Unused slot: zero the active fields. (The ROM leaves [slot+0x5a]=0 for
      // unused slots and the active-mask bit clear; [0x10]/[0xa0] are stale from
      // the cleared block, but the spawn reader skips unused slots via team 0xff.)
      state.activeBorgId[slot] = 0;
      state.activeVariant[slot] = 0;
      state.slotRosterCount[slot] = 0;
    }

    // --- Common per-slot writes (chunk_0048.c:365-376): run for EVERY slot. ---
    // [slot + 0x20] = 0x0e (chunk_0048.c:365).
    state.slotConst20[slot] = SLOT_CONST_0x20;
    // [slot + 0x3e] = 0x03 (chunk_0048.c:367).
    state.slotConst3e[slot] = SLOT_CONST_0x3e;
    // [slot + 0x32] = DAT_804356ec[team + difficulty*2] (chunk_0048.c:373-375).
    state.slotFlag32[slot] = sideFlagFor(team, difficulty, sideFlagTable);
    // [slot + 0x54] = 0 (chunk_0048.c:376).
    state.slotConst54[slot] = SLOT_CONST_0x54;
  }
}

// -------------------------------------------------------------------------------------------------
// Deliverable: the slot-table write sequence (offset <- source), with evidence.
// -------------------------------------------------------------------------------------------------

export interface SlotTableWriteEntry {
  /** PTR_DAT_80433934 byte offset (or u16 stride note). */
  readonly slotTableOffset: string;
  readonly slotIndexing: "slot*2 (u16)" | "slot (byte)" | "global";
  /** Source the writer copies from. */
  readonly source: string;
  readonly evidence: string;
  /** Whether the spawn reader (spawnFromSlotTables) consumes this offset. */
  readonly readBySpawn: boolean;
}

/**
 * The exact slot-table write sequence performed by build_challenge_battle_setup, in the
 * order the ROM performs it. Confirmed offsets (0x10/0xa0/0xcb/0x15d9) are tagged
 * `readBySpawn: true`; the rest are ROM-faithful writes the spawn path never reads.
 */
export function slotTableWriteSequence(): readonly SlotTableWriteEntry[] {
  return [
    {
      slotTableOffset: "0x15d9",
      slotIndexing: "global",
      source: "cleared to 0 (init), then ORed with (1 << slot) per staffed slot",
      evidence: "chunk_0048.c:275,286,296,331",
      readBySpawn: true,
    },
    {
      slotTableOffset: "0x15da",
      slotIndexing: "global",
      source: "cleared to 0 (init), then incremented per staffed slot",
      evidence: "chunk_0048.c:277,287,297,333",
      readBySpawn: false,
    },
    {
      slotTableOffset: "0xcb",
      slotIndexing: "slot (byte)",
      source: "team byte: 0 (player/ally) | 1 (enemy) | 0xff (unused). Loop 1 derives "
            + "player teams from controllerMask; loop 2 auto-fills CPU ally/enemy teams.",
      evidence: "chunk_0048.c:281,284,291,294,321,327",
      readBySpawn: true,
    },
    {
      slotTableOffset: "0x5a",
      slotIndexing: "slot (byte)",
      source: "per-slot roster count (reset to 0, ++ per rolled roster borg)",
      evidence: "chunk_0048.c:316,334,360",
      readBySpawn: false,
    },
    {
      slotTableOffset: "0x10",
      slotIndexing: "slot*2 (u16)",
      source: "active borg id = first roster entry's u16 borg id at [slot*0x348 + 0x1e8]",
      evidence: "chunk_0048.c:377 (iVar2 = slot*2 + 0x10; iVar6 = slot*0x348 + 0x1e8)",
      readBySpawn: true,
    },
    {
      slotTableOffset: "0xa0",
      slotIndexing: "slot (byte)",
      source: "active variant byte = first roster entry's variant at [slot*0x348 + 0x1ea]",
      evidence: "chunk_0048.c:378 (iVar5 = slot*0x348 + 0x1ea)",
      readBySpawn: true,
    },
    {
      slotTableOffset: "0x20",
      slotIndexing: "slot (byte)",
      source: "constant 0x0e (14)",
      evidence: "chunk_0048.c:365",
      readBySpawn: false,
    },
    {
      slotTableOffset: "0x3e",
      slotIndexing: "slot (byte)",
      source: "constant 0x03 (3)",
      evidence: "chunk_0048.c:367",
      readBySpawn: false,
    },
    {
      slotTableOffset: "0x32",
      slotIndexing: "slot (byte)",
      source: "DAT_804356ec[team + difficulty*2] side flag",
      evidence: "chunk_0048.c:373-375; data/challenge-battle-tables-8036f360.json",
      readBySpawn: false,
    },
    {
      slotTableOffset: "0x54",
      slotIndexing: "slot (byte)",
      source: "constant 0x00",
      evidence: "chunk_0048.c:376",
      readBySpawn: false,
    },
  ];
}

// -------------------------------------------------------------------------------------------------
// Self-tests. The centerpiece is a write -> read ROUND-TRIP: writeForceToSlotTables feeds
// spawnActiveBorgsFromSlotTables and the spawned RomActors must match the input force.
// -------------------------------------------------------------------------------------------------

export interface ForceSetupTestAssert {
  /** Fail the test with a message when `condition` is false. */
  (condition: boolean, message: string): void;
}

/**
 * Self-tests for the force-setup writer. Covers:
 *  - the confirmed-offset writes (0x10/0xa0/0xcb/0x15d9) for a 3-borg force;
 *  - the constant writes (0x20/0x3e/0x54) and side-flag writes (0x32);
 *  - the activeMask/activeCount derivation;
 *  - a full write -> spawnActiveBorgsFromSlotTables ROUND-TRIP verifying the reader
 *    reproduces the same RomActors (borgNumber/team/slot/variant);
 *  - unused-slot handling (0xff team, no active bit);
 *  - difficulty -> [slot+0x32] side-flag table fidelity.
 */
export function runForceSetupSelfTests(assert: ForceSetupTestAssert): void {
  // --- 3-borg force (mirrors spawnFromSlotTables self-test sample) -----------------
  const playerForce: ForceSlotEntry[] = [
    { borgNumber: 0x0615, variant: 2, team: SLOT_TEAM.PLAYER_ALLY }, // slot 0: G RED
    { borgNumber: 0x0629, variant: 0, team: SLOT_TEAM.PLAYER_ALLY }, // slot 1: NEO G RED
    { borgNumber: 0x0200, variant: 5, team: SLOT_TEAM.ENEMY }, // slot 2: Sword Knight
    // slots 3..5 left unused (no entry -> team 0xff).
  ];

  // --- Write + verify the confirmed offsets ---------------------------------------
  const state = createSlotTableState(ROM_SLOT_COUNT);
  writeForceToSlotTables(state, playerForce);

  // [0xcb] team bytes.
  assert(state.slotTeam[0] === SLOT_TEAM.PLAYER_ALLY, `slot0 team=${state.slotTeam[0]}`);
  assert(state.slotTeam[1] === SLOT_TEAM.PLAYER_ALLY, `slot1 team=${state.slotTeam[1]}`);
  assert(state.slotTeam[2] === SLOT_TEAM.ENEMY, `slot2 team=${state.slotTeam[2]}`);
  assert(state.slotTeam[3] === SLOT_TEAM.UNUSED, `slot3 team=${state.slotTeam[3]} (unused)`);
  assert(state.slotTeam[5] === SLOT_TEAM.UNUSED, `slot5 team=${state.slotTeam[5]} (unused)`);

  // [0x10] u16 active borg ids.
  assert(state.activeBorgId[0] === 0x0615, `slot0 borgId=0x${(state.activeBorgId[0] ?? 0).toString(16)}`);
  assert(state.activeBorgId[1] === 0x0629, `slot1 borgId=0x${(state.activeBorgId[1] ?? 0).toString(16)}`);
  assert(state.activeBorgId[2] === 0x0200, `slot2 borgId=0x${(state.activeBorgId[2] ?? 0).toString(16)}`);
  assert(state.activeBorgId[3] === 0, `slot3 borgId=${state.activeBorgId[3] ?? 0} (unused)`);

  // [0xa0] variant bytes.
  assert(state.activeVariant[0] === 2, `slot0 variant=${state.activeVariant[0]}`);
  assert(state.activeVariant[1] === 0, `slot1 variant=${state.activeVariant[1]}`);
  assert(state.activeVariant[2] === 5, `slot2 variant=${state.activeVariant[2]}`);

  // [0x15d9] active mask: bits 0,1,2 set => 0b111 = 7.
  assert(state.activeMask === 0b111, `activeMask=0b${state.activeMask.toString(2)} (expect 111)`);
  // [0x15da] active count.
  assert(state.activeCount === 3, `activeCount=${state.activeCount} (expect 3)`);

  // --- ROM-faithful constant + side-flag writes -----------------------------------
  // [0x20]=0x0e, [0x3e]=0x03, [0x54]=0x00 for EVERY slot (incl. unused).
  for (let i = 0; i < ROM_SLOT_COUNT; i++) {
    assert(state.slotConst20[i] === SLOT_CONST_0x20, `slot${i} [0x20]=${state.slotConst20[i]}`);
    assert(state.slotConst3e[i] === SLOT_CONST_0x3e, `slot${i} [0x3e]=${state.slotConst3e[i]}`);
    assert(state.slotConst54[i] === SLOT_CONST_0x54, `slot${i} [0x54]=${state.slotConst54[i]}`);
  }
  // [0x32] = DAT_804356ec[team + difficulty*2]; default difficulty NORMAL(0):
  //   team0 -> 7, team1 -> 4, unused -> 0 (we emit 0 in lieu of ROM's OOB read).
  assert(state.slotFlag32[0] === 7, `slot0 [0x32]=${state.slotFlag32[0]} (team0 normal=7)`);
  assert(state.slotFlag32[2] === 4, `slot2 [0x32]=${state.slotFlag32[2]} (team1 normal=4)`);
  assert(state.slotFlag32[3] === 0, `slot3 [0x32]=${state.slotFlag32[3]} (unused->0)`);

  // [0x5a] roster count defaults to 1 for staffed, 0 for unused.
  assert(state.slotRosterCount[0] === 1, `slot0 roster=${state.slotRosterCount[0]}`);
  assert(state.slotRosterCount[3] === 0, `slot3 roster=${state.slotRosterCount[3]} (unused)`);

  // --- ROUND-TRIP: spawnActiveBorgsFromSlotTables reads the state back --------------
  // The reader must reproduce one RomActor per staffed slot, with borgNumber/team/slot
  // matching the input force, and the +0x3ec level byte (from [0xa0]) matching variant.
  const actors = spawnActiveBorgsFromSlotTables(state as Readonly<SlotTableState> as SlotTableState);
  assert(actors.length === 3, `round-trip spawned ${actors.length} actors (expect 3)`);

  const a0 = actors[0]!;
  assert(a0.slot === 0, `round-trip slot0.slot=${a0.slot}`);
  assert(a0.team === SLOT_TEAM.PLAYER_ALLY, `round-trip slot0.team=${a0.team}`);
  assert(a0.borgNumber === 0x0615, `round-trip slot0.borgNumber=0x${a0.borgNumber.toString(16)}`);
  assert(getSpawnedLevel3ec(a0) === 2, `round-trip slot0 +0x3ec=${getSpawnedLevel3ec(a0)}`);

  const a1 = actors[1]!;
  assert(a1.slot === 1, `round-trip slot1.slot=${a1.slot}`);
  assert(a1.team === SLOT_TEAM.PLAYER_ALLY, `round-trip slot1.team=${a1.team}`);
  assert(a1.borgNumber === 0x0629, `round-trip slot1.borgNumber=0x${a1.borgNumber.toString(16)}`);
  assert(getSpawnedLevel3ec(a1) === 0, `round-trip slot1 +0x3ec=${getSpawnedLevel3ec(a1)}`);

  const a2 = actors[2]!;
  assert(a2.slot === 2, `round-trip slot2.slot=${a2.slot}`);
  assert(a2.team === SLOT_TEAM.ENEMY, `round-trip slot2.team=${a2.team}`);
  assert(a2.borgNumber === 0x0200, `round-trip slot2.borgNumber=0x${a2.borgNumber.toString(16)}`);
  assert(getSpawnedLevel3ec(a2) === 5, `round-trip slot2 +0x3ec=${getSpawnedLevel3ec(a2)}`);

  // --- Difficulty -> [0x32] side-flag table fidelity -------------------------------
  // INSANE: team0 -> 7, team1 -> 12 (challenge-battle-tables-8036f360.json).
  const insaneState = createSlotTableState(ROM_SLOT_COUNT);
  writeForceToSlotTables(
    insaneState,
    [
      { borgNumber: 0x0001, variant: 0, team: SLOT_TEAM.PLAYER_ALLY },
      { borgNumber: 0x0002, variant: 0, team: SLOT_TEAM.ENEMY },
    ],
    { difficulty: SLOT_DIFFICULTY.INSANE },
  );
  assert(insaneState.slotFlag32[0] === 7, `insane team0 [0x32]=${insaneState.slotFlag32[0]} (expect 7)`);
  assert(insaneState.slotFlag32[1] === 12, `insane team1 [0x32]=${insaneState.slotFlag32[1]} (expect 12)`);

  // --- Full 6-slot force round-trip (no unused slots) ------------------------------
  const fullForce: ForceSlotEntry[] = [
    { borgNumber: 0x0100, variant: 1, team: SLOT_TEAM.PLAYER_ALLY },
    { borgNumber: 0x0200, variant: 2, team: SLOT_TEAM.PLAYER_ALLY },
    { borgNumber: 0x0300, variant: 3, team: SLOT_TEAM.ENEMY },
    { borgNumber: 0x0400, variant: 4, team: SLOT_TEAM.ENEMY },
    { borgNumber: 0x0500, variant: 5, team: SLOT_TEAM.ENEMY },
    { borgNumber: 0x0600, variant: 6, team: SLOT_TEAM.ENEMY },
  ];
  const fullState = createSlotTableState(ROM_SLOT_COUNT);
  writeForceToSlotTables(fullState, fullForce);
  assert(fullState.activeMask === 0b111111, `full activeMask=0b${fullState.activeMask.toString(2)}`);
  assert(fullState.activeCount === 6, `full activeCount=${fullState.activeCount}`);
  const fullActors = spawnActiveBorgsFromSlotTables(fullState as Readonly<SlotTableState> as SlotTableState);
  assert(fullActors.length === 6, `full round-trip spawned ${fullActors.length} (expect 6)`);
  // Verify every actor round-trips its borgNumber + team.
  const allMatch = fullActors.every((a: RomActor, i: number) =>
    a.borgNumber === fullForce[i]!.borgNumber &&
    a.team === fullForce[i]!.team &&
    a.slot === i,
  );
  assert(allMatch, "full round-trip: every actor matches its force entry");

  // --- Write-sequence deliverable sanity ------------------------------------------
  const seq = slotTableWriteSequence();
  const confirmedRead = seq.filter((e) => e.readBySpawn).map((e) => e.slotTableOffset);
  assert(
    confirmedRead.join(",") === "0x15d9,0xcb,0x10,0xa0",
    `read-by-spawn offsets = ${confirmedRead.join(",")}`,
  );
  const offset10 = seq.find((e) => e.slotTableOffset === "0x10");
  assert(!!offset10 && offset10.slotIndexing === "slot*2 (u16)", "0x10 indexing = slot*2 (u16)");
  const offsetCb = seq.find((e) => e.slotTableOffset === "0xcb");
  assert(!!offsetCb && offsetCb.slotIndexing === "slot (byte)", "0xcb indexing = slot (byte)");
}

/* -------------------------------------------------------------------------------------------------
 * INTEGRATION SPEC (delivered here; spawnFromSlotTables.ts / battle.ts / challengeFlowVm.ts
 * are NOT modified by this task).
 *
 * This writer is the bridge between a resolved force and the ROM spawn path. Today the
 * spawn-side integration spec in spawnFromSlotTables.ts (bottom of file) describes wiring
 * spawnActiveBorgsFromSlotTables into prepareBattle; this writer completes the path:
 *
 * 1. Force resolution (host-owned): the host resolves a force into ForceSlotEntry[].
 *    - Versus: cfg.forces already carries team + borgIds. Map force `i` to slot `i`,
 *      decode each borgId to its u16 borgNumber (behavior-notes.md (n) roster map; until
 *      that lands, derive from the pl id's family/variant bytes), set variant/level from
 *      the roster, and set team = force.team (0 player / 1 enemy). Pad unused slots to
 *      team 0xff (or omit them; the writer treats missing entries as unused).
 *    - Challenge: the challengeFlowVm mode-3 build (challengeFlowVm.ts:363-485) already
 *      resolves slots[].side + roster[] (CPU rolls). Fold its output into ForceSlotEntry[]:
 *        entry.borgNumber = slot.roster[0].borgId   // first roster entry = active borg
 *        entry.variant    = 0                        // ROM hardcodes variant byte to 0
 *                                                   // (chunk_0048.c:358: PTR[..+0x1ea]=0)
 *        entry.team       = slot.side                // 0 ally / 1 enemy / 0xff unused
 *        entry.rosterCount = slot.roster.length      // [slot+0x5a] death→swap depth
 *      The human player's own force fills the controller-mask slots (team 0) from the
 *      save-block force list (PTR_DAT_80433944), not from the CPU pool roll.
 *
 * 2. Write + spawn (replace battle.ts BattleImpl.deployNext's force-list materialization):
 *      const state = createSlotTableState();
 *      writeForceToSlotTables(state, forceEntries, { difficulty });
 *      const actors = spawnActiveBorgsFromSlotTables(state);
 *    Each RomActor now carries slot/team/borgNumber exactly as the ROM sets them. Fold
 *    each into the BorgRuntime deployNext creates today (see spawnFromSlotTables.ts
 *    integration spec step 2 for the per-field routing, including getSpawnedLevel3ec).
 *
 * 3. Death → auto-deploy: bump the dying slot's active borg to the next roster entry
 *    (state.slotRosterCount[slot] tracks depth), then re-run initActorFromSlotTables on
 *    the new actor for that slot. The ROM reuses FUN_800541ac for respawn
 *    (chunk_0006.c:7072 +0x3f0 respawn counter), so no second writer is needed.
 *
 * OPEN DEPS (block full integration; cite when wiring):
 *   - pl-id <-> u16 borgNumber table: behavior-notes.md (n) flags the 208-entry roster
 *     map as "still open". Until resolved, borgNumber is derived per-force.
 *   - The ROM's CPU roster roll (loop 2 inner, chunk_0048.c:335-361) lives in
 *     challengeFlowVm.ts mode 3 + its sink (drawBorgFromPool / borgCost). This writer
 *     does NOT roll rosters; it only writes a resolved force. Wire the VM's slots[]
 *     output into ForceSlotEntry[] as described above.
 *   - object+0x3ec (level) has no BorgRuntime sink today; route getSpawnedLevel3ec into
 *     paramTier/level when the level-byte -> damage-formula path is ported.
 *   - Versus mode (non-Challenge) uses a sibling writer not traced here; the offset
 *     writes are expected to match (the spawn reader is mode-agnostic), but the team
 *     derivation differs (cfg.forces[].team instead of controllerMask). TODO: trace the
 *     Versus force-setup fn and confirm offset parity.
 * ------------------------------------------------------------------------------------------------- */
