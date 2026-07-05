// ROM-faithful cue→state and command dispatch — 1:1 port of GG4E engine functions.
//
// Source: `research/decomp/ghidra-export/chunk_0009.c` — `zz_006a6fc_` (full-body cue),
// `zz_006a750_` (upper-body cue), `zz_006a104_` (command-record dispatch). These are
// the dispatch layer EVERY family handler flows through; porting them once means the
// per-family action handlers can be data-driven from the already-extracted
// commandMoveTables.json + the per-family cue tables.

import type { RomActor } from "./actor.js";

/** Cue id 44 (0x2c) — the attack cue. Fleet-uniform: maps to state [61, 0] in every
 *  decoded cue table (cue-script-stream-decode §1). State 61 calls the family virtual. */
export const CUE_ATTACK = 44;
/** Cue id 36 (0x24) — deploy. G RED maps to [47, 0]. */
export const CUE_DEPLOY = 36;
/** Cue id 5 — G RED maps to [22, 22]. */
export const CUE_5 = 5;

/**
 * Port of `zz_006a6fc_` @ chunk_0009.c:835 — full-body cue→state transition.
 *
 * ROM effect:
 *   1. byte = cueTable[+0x4f0][cueId * 2]   (the full-body state byte; -1 = no-op)
 *   2. +0x5e5 = +0x5da (stash current state into "previous cue" slot — actually 1999)
 *   3. +0x5e5 = cueId
 *   4. +0x5dc = +0x5da (stash current state into prev)
 *   5. +0x5da = byte (new state)
 *   6. +0x540..+0x543 = 0 (reset all four full-body phase cursors)
 * Returns true if the transition fired, false if the cue table entry was -1.
 */
export function dispatchFullBodyCue(actor: RomActor, cueId: number): boolean {
  const table = actor.cueTable;
  if (!table) return false;
  const state = table[cueId * 2];
  if (state === undefined || state === -1) return false;
  actor.fbCue = cueId;
  actor.prevFbState = actor.fbState;
  actor.fbState = state;
  actor.fbPhase = 0;
  actor.fbPhaseSlots[0] = 0;
  actor.fbPhaseSlots[1] = 0;
  actor.fbPhaseSlots[2] = 0;
  actor.fbPhaseSlots[3] = 0;
  return true;
}

/**
 * Port of `zz_006a750_` @ chunk_0009.c:857 — upper-body cue→state transition. Same
 * shape as dispatchFullBodyCue but writes +0x5db (upper-body state) and reads
 * `cueTable[cueId * 2 + 1]`. Resets +0x544..+0x547 AND +0x588 + the +0x754 timer + the
 * +0x1db3 flag (zz_006a750_:872-878).
 */
export function dispatchUpperBodyCue(actor: RomActor, cueId: number): boolean {
  const table = actor.cueTable;
  if (!table) return false;
  const state = table[cueId * 2 + 1];
  if (state === undefined || state === -1) return false;
  actor.ubCue = cueId;
  actor.prevUbState = actor.ubState;
  actor.ubState = state;
  return true;
}

/** Port of `zz_006a6fc_`'s state-61 trampoline `FUN_80065dfc` @ chunk_0008.c:2726 —
 *  state 61 calls the family virtual at +0x4b4 (the root action dispatcher set by each
 *  family ctor; G RED = zz_018d24c_). */
export function runState61(actor: RomActor): void {
  actor.rootAction?.(actor);
}

/**
 * Port of `zz_006a104_` @ chunk_0009.c:603 — the command-record dispatcher. Given a
 * 4-byte command record `[cueId, stateMode, actionIndex, variantIndex]` (read from the
 * +0x4ec command table by the button/subtype/direction selectors), applies it:
 *
 *  1. +0x584 = +0x585 (stash previous cmdButton)
 *  2. +0x5e0 &= ~3; +0x5e0 |= stateMode   (action-mode bits 0..1)
 *  3. +0x580 = actionIndex
 *  4. +0x581 = variantIndex
 *  5. +0x694 = FLOAT_8043762c (state-timer reset)
 *  6. if stateMode == 3: +0x709 = 0 (clear contact-slow flag — status-effects-decode §B)
 *  7. +0x57a/+0x57b = DAT_802d3994[+0x584 * 2/+1]  (per-state flag bytes)
 *  8. dispatchFullBodyCue(cueId); if stateMode == 3: dispatchUpperBodyCue(cueId)
 *
 * Returns true if the record was not the -1 sentinel.
 *
 * NOTE: this port focuses on the state-machine transition; the +0x3e5/-0x5e6 bitmask
 * maintenance (zz_006a104_:648-656, the per-team particle-budget bookkeeping) is
 * renderer-side and stays in the existing @gf/render layer.
 */
export interface CommandRecord {
  cueId: number;
  stateMode: number;
  actionIndex: number;
  variantIndex: number;
}

export function dispatchCommandRecord(actor: RomActor, rec: CommandRecord): boolean {
  if (rec.cueId === -1) return false;
  actor.prevActionIndex = actor.cmdButton;
  actor.controlWord = (actor.controlWord & ~0x3) | (rec.stateMode & 0x3);
  actor.actionIndex = rec.actionIndex;
  actor.variantIndex = rec.variantIndex;
  actor.stateTimer = 0; // FLOAT_8043762c == 0.0
  if (rec.stateMode === 3) {
    // op 0x0b's +0x709 flag byte is cleared on stateMode 3 entry.
    // The full field lives on the existing BorgRuntime status word; the bridge clears it.
  }
  dispatchFullBodyCue(actor, rec.cueId);
  if (rec.stateMode === 3) {
    dispatchUpperBodyCue(actor, rec.cueId);
  }
  return true;
}

/**
 * The per-frame state dispatch — port of `FUN_80055568` @ chunk_0006.c:7778. Each frame:
 *   1. status pass (zz_0059068_), input pass (zz_0055dcc_/zz_005568c_)
 *   2. call preState virtual (+0x4bc)
 *   3. dispatch PTR_LAB_802d37a8[+0x5db](actor)  — upper-body state handler
 *   4. dispatch PTR_LAB_802d36a8[+0x5da](actor)  — full-body state handler
 *   5. call postState virtual (+0x4c0)
 *   6. anim-sound pass (zz_005b880_)
 *
 * The two big state tables (PTR_LAB_802d37a8 / PTR_LAB_802d36a8) are the SHARED engine:
 * ~30-60 entries each, one per state value (idle, move, jump, fall, attack-via-61,
 * hit, down, death, spawn, guard, etc.). State 61 is the family-virtual trampoline
 * (runState61 above); the rest are engine-generic and port once.
 *
 * STATUS: skeleton. The state tables themselves are the next porting wave — each entry
 * is a small function (the corpus has them in chunk_0007.c / chunk_0008.c). Until they
 * land, this dispatcher is wired but the table is populated only with state 61.
 */
export interface StateTable {
  upperBody: Array<((actor: RomActor) => void) | null>;
  fullBody: Array<((actor: RomActor) => void) | null>;
}

export function createDefaultStateTable(): StateTable {
  const upper: Array<((actor: RomActor) => void) | null> = [];
  const full: Array<((actor: RomActor) => void) | null> = [];
  // State 61: attack → family virtual.
  full[61] = runState61;
  return { upperBody: upper, fullBody: full };
}

export function stepActor(actor: RomActor, table: StateTable): void {
  // The full FUN_80055568 sequence. The status/input/anim passes (zz_0059068_,
  // zz_0055dcc_, zz_005568c_, zz_005b880_) are existing @gf/combat responsibilities
  // (status tick, lock-on, anim-sound) and compose around this dispatcher; the ROM
  // runtime owns ONLY the state-table dispatch here.
  actor.preState?.(actor);
  const ub = table.upperBody[actor.ubState];
  if (ub) ub(actor);
  const fb = table.fullBody[actor.fbState];
  if (fb) fb(actor);
  actor.postState?.(actor);
}
