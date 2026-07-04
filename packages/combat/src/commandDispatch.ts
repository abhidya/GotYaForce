// Live command dispatch (ATK-003): the runtime bridge between the port's PlayerInput button
// state and the ROM's command pipeline. Each frame stepAttacks:
//   1. builds the transformed-input-word (actor+0x5d4 model) from the frame's button state
//      via COMMAND_INPUT_BITS (command.ts, DERIVED bits/priority from behavior-notes (bd)),
//   2. resolves the command TYPE with resolveCommandType() (the ROM tester priority under
//      FUN_800699d8: RANGED > CHARGED > SECONDARY > MELEE),
//   3. refines the B command into the +0x4ec table's type-0 (B far/shot) vs type-1
//      (B close/battle-attack) row from the live target-proximity context — the
//      zz_0069a88_/zz_0069b10_ proximity split writes actor+0x585 = 0/1,
//   4. selects the borg's exact ROM command record (data/commandMoveTables.json) for the
//      resolved row where one is decoded, preferring the DERIVED air/elevated subtype 4 row
//      while airborne and the charged-ranged subtype 5 row on charge releases.
//
// The button-bit assignment (which physical pad button produces which +0x5d4 bit) is the one
// TUNED link in the chain — the manual (ao) fixes the button ROLES (B contextual, X secondary,
// Y burst) and the tester bits/priority are DERIVED, but the pad→bit transform itself is
// still un-dug. Everything else here is table-driven from the DOL extraction.
//
// Record capability gating: ONLY the contextual-B melee/shot split is negatively gated by the
// decoded tables (a decoded table whose type-1 row has no active records means the ROM's own
// +0x4ec data says the borg has no B-close battle attack, and vice versa for type-0). X and
// charge rows are attached/marked exact where records exist but never gated off: the type-2↔X
// mapping mismatches the wiki catalog for 52/208 borgs, so treating an empty type-2 row as
// "no X attack" would invent behavior the mismatch does not support.

import {
  AttackCommandType,
  COMMAND_INPUT_BITS,
  resolveCommandType,
} from "./command.js";
import {
  commandMoveRecordsForBorgButton,
  commandMoveTableAssignmentForBorgId,
  type CommandMoveRecord,
  type RuntimeCommandMoveButton,
} from "./commandMoveTables.js";
import type { ResolvedCommandState } from "./types.js";

/** Frame button state feeding the transformed-input-word (see file header for provenance). */
export interface CommandButtonState {
  /** B held this frame. */
  attackHeld: boolean;
  /** X held this frame. */
  specialHeld: boolean;
  /** B released this frame with a banked charge (chargeFrames > 0 on a chargeable shot). */
  chargeRelease: boolean;
  /** X released this frame with a banked X-charge (xChargeFrames > 0). */
  xChargeRelease: boolean;
  /** Y held (Power Burst request) — carried for word completeness; the burst path is
   *  resolved separately in battle.ts stepPowerBurstInputs, never as a +0x585 type. */
  burstHeld?: boolean;
}

/** Actor-state context the input word alone cannot carry (command.ts resolver note). */
export interface CommandActorContext {
  /** Contextual-B target inside the melee engage window (B close → type 1). */
  meleeEngaged: boolean;
  /** Airborne selects the DERIVED air/elevated subtype-4 record row where present. */
  airborne: boolean;
}

/** Build the transformed-input-word (actor+0x5d4 model) for this frame's buttons. */
export function commandInputWord(state: CommandButtonState): number {
  let word = 0;
  if (state.attackHeld) word |= COMMAND_INPUT_BITS.MELEE_A;
  if (state.specialHeld) word |= COMMAND_INPUT_BITS.SECONDARY;
  if (state.chargeRelease) word |= COMMAND_INPUT_BITS.CHARGED;
  if (state.xChargeRelease) word |= COMMAND_INPUT_BITS.RANGED;
  if (state.burstHeld) word |= COMMAND_INPUT_BITS.BURST;
  return word;
}

/** Map a resolved command type + proximity context onto the +0x4ec table's button row. */
export function commandButtonForType(
  type: AttackCommandType,
  ctx: CommandActorContext,
): RuntimeCommandMoveButton | null {
  switch (type) {
    case AttackCommandType.Melee1:
      // The B command: zz_0069a88_/zz_0069b10_ write actor+0x585 = 1 with a proximity target
      // (B close, table type 1) and 0 without one (B far, table type 0).
      return ctx.meleeEngaged ? "B Attack" : "B Shot";
    case AttackCommandType.Melee2:
      return "X"; // type 2 — zz_0069b98_, the secondary/X row
    case AttackCommandType.Unmapped3:
      return "B Charge"; // type 3 — zz_0069bf0_, the charged row
    case AttackCommandType.Ranged5:
      return "X Charge"; // type 5 — zz_0069c50_/zz_0069cb0_, the ranged/forced row
    default:
      return null; // types 0/4/6/7: no tester-written mapping — do not invent one
  }
}

/**
 * Select the concrete command record for a button row. DERIVED ordering: the air/elevated
 * subtype 4 (zz_0069ea4_) wins while airborne; the charged-ranged subtype 5 (zz_0069fe0_)
 * wins on charge releases; otherwise the lowest-subtype grounded record with the lowest
 * direction is the base row.
 */
export function selectCommandRecord(
  records: readonly CommandMoveRecord[],
  ctx: CommandActorContext & { charged?: boolean },
): CommandMoveRecord | null {
  if (records.length === 0) return null;
  const bySubtype = (subtype: number) =>
    records
      .filter((record) => record.subtype === subtype)
      .sort((a, b) => (a.direction ?? -1) - (b.direction ?? -1))[0] ?? null;
  if (ctx.airborne) {
    const air = bySubtype(4);
    if (air) return air;
  }
  if (ctx.charged) {
    const charged = bySubtype(5);
    if (charged) return charged;
  }
  const sorted = [...records].sort(
    (a, b) => a.subtype - b.subtype || (a.direction ?? -1) - (b.direction ?? -1),
  );
  return sorted[0] ?? null;
}

/** Contextual-B capability gates from the borg's decoded +0x4ec table.
 *  null = no decoded exact table (callers keep the profile-driven compat behavior). */
export interface ContextualBGates {
  /** Active type-1 (B close / battle attack) records exist. */
  melee: boolean;
  /** Active type-0 (B far / shot) records exist. */
  shot: boolean;
}

const contextualBGatesCache = new Map<string, ContextualBGates | null>();

export function contextualBGatesForBorgId(id: string): ContextualBGates | null {
  const key = id.toLowerCase();
  const cached = contextualBGatesCache.get(key);
  if (cached !== undefined) return cached;
  const assignment = commandMoveTableAssignmentForBorgId(key);
  const gates =
    assignment?.exactCommandTable && assignment.tableId
      ? {
          melee: commandMoveRecordsForBorgButton(key, "B Attack").length > 0,
          shot: commandMoveRecordsForBorgButton(key, "B Shot").length > 0,
        }
      : null;
  contextualBGatesCache.set(key, gates);
  return gates;
}

/** Full live resolution for one frame. Returns null when no attack bit is set. */
export function resolveLiveCommand(
  borgId: string,
  state: CommandButtonState,
  ctx: CommandActorContext,
): ResolvedCommandState | null {
  const word = commandInputWord(state);
  const type = resolveCommandType(word);
  if (type === null) return null;
  const button = commandButtonForType(type, ctx);
  if (button === null) {
    return { word, type, button: null, recordAddress: null, subtype: null, exact: false };
  }
  const records = commandMoveRecordsForBorgButton(borgId, button);
  const record = selectCommandRecord(records, {
    ...ctx,
    charged: state.chargeRelease || state.xChargeRelease,
  });
  return {
    word,
    type,
    button,
    recordAddress: record?.address ?? null,
    subtype: record?.subtype ?? null,
    exact: record !== null,
  };
}
