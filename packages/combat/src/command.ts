// Attack-command data schema (types + constants only). Mirrors the ROM's command vocabulary
// so the future resolver (ATK-003), AI, and tests share one contract.
//
// SCOPE: this file is schema/types ONLY. It introduces ZERO runtime behavior — nothing in
// the sim constructs, reads, or dispatches on these types yet. Do not assign button meanings
// to command values here (that is ATK-003, blocked on trace T1 — see the evidence below).
//
// Evidence (research/decomp/attack-mechanics-findings.md mechanic A; full detail there):
//   - Command struct actor+0x4b0 (+0/+1 buttons, +4 command) copied to actor+0x660/+0x661/
//     +0x591: `FUN_800562b8` chunk_0007.c:23; `zz_006a8c0_` @0x8006a8c0 chunk_0009.c:978-980.
//   - Command types {1,2,3,5} set at actor+0x585 by decision testers under `FUN_800699d8`
//     @0x800699d8, chunk_0009.c:220+.
//   - Subtype 0-5 at actor+0x586, chunk_0009.c:500-587.
//   - Dispatch families: actor+0x591 == 1/2 -> melee, 4/5/6 -> ranged (`FUN_8005d494`,
//     chunk_0007.c:4750-4782).
//   - Full context: research/decomp/attack-mechanics-findings.md mechanic A;
//     research/decomp/data/attack-profile-port-schema.json#inputBindings.

/**
 * ROM command type byte (actor+0x591 dispatch value; also observed written at actor+0x585
 * by the decision testers under `FUN_800699d8`, chunk_0009.c:220+).
 *
 * Numeric values mirror the ROM byte range 0-7 exactly (do not renumber). UPDATE (behavior-notes
 * (bd)): the decision testers under `FUN_800699d8` write actor+0x585 ∈ {0,1,2,3,5} — value 3 is
 * now DERIVED (the CHARGED type, tester zz_0069bf0_ from input bit 0x400). Types 4 and 6 are NOT
 * tester-written; they arise later at the +0x591 dispatch stage (so the older "testers write
 * 4/5/6" note was imprecise). Values 0 and 7 remain BLOCKED (never observed set).
 */
export enum AttackCommandType {
  /** BLOCKED: never observed written by a decision tester in the corpus read (this audit).
   *  No dispatch-family evidence either. Reserved slot only — do not assign meaning without
   *  a new citation. */
  Unmapped0 = 0,
  /**
   * Melee family. DERIVED_ROM: set at actor+0x585 by decision testers under `FUN_800699d8`
   * @0x800699d8 (chunk_0009.c:220+); consumed as a melee-family value (actor+0x591 == 1) by
   * the attack-active dispatch `FUN_8005d494` (chunk_0007.c:4750-4782).
   */
  Melee1 = 1,
  /**
   * Melee family. DERIVED_ROM: set at actor+0x585 by decision testers under `FUN_800699d8`
   * @0x800699d8 (chunk_0009.c:220+); consumed as a melee-family value (actor+0x591 == 2) by
   * the attack-active dispatch `FUN_8005d494` (chunk_0007.c:4750-4782). Distinct melee family
   * from Melee1 — the two are dispatched identically at the family level but the corpus read
   * did not establish what differentiates them (e.g. combo step vs. a separate melee move).
   */
  Melee2 = 2,
  /** CHARGED command type. DERIVED_ROM (behavior-notes (bd)): written to actor+0x585 by tester
   *  `zz_0069bf0_` from bit 0x400 of the transformed input word actor+0x5d4, and it sets the
   *  charged flag at actor+0x595. So type 3 is the "charged/forced" command variant (kept named
   *  Unmapped3 only to preserve the ROM byte value; its meaning is now known). Its dispatch
   *  family at +0x591 is resolved later at the +0x591 stage rather than by `FUN_8005d494`. */
  Unmapped3 = 3,
  /**
   * Ranged family. DERIVED_ROM: consumed as a ranged-family value (actor+0x591 == 4) by the
   * attack-active dispatch `FUN_8005d494` (chunk_0007.c:4750-4782). Which decision tester
   * writes this exact value under `FUN_800699d8` (chunk_0009.c:220+) is not individually
   * pinned down in the corpus read — see mechanic A unknowns (full button->command mapping
   * is BLOCKED on trace T1).
   */
  Ranged4 = 4,
  /**
   * Ranged family. DERIVED_ROM: set at actor+0x585 by decision testers under `FUN_800699d8`
   * @0x800699d8 — specifically `zz_0069cb0_` (requires a live target: `if (actor+0x4a0 == 0)
   * return 0;` chunk_0009.c:412) and `zz_0069c50_` (bit 0x1000 of the transformed button word
   * actor+0x5d4) both write 5 (chunk_0009.c:220+). Consumed as a ranged-family value
   * (actor+0x591 == 5) by `FUN_8005d494` (chunk_0007.c:4750-4782).
   */
  Ranged5 = 5,
  /**
   * Ranged family. DERIVED_ROM: consumed as a ranged-family value (actor+0x591 == 6) by the
   * attack-active dispatch `FUN_8005d494` (chunk_0007.c:4750-4782). Which decision tester
   * writes this exact value is not individually pinned down in the corpus read (same caveat
   * as Ranged4 — full mapping BLOCKED on trace T1).
   */
  Ranged6 = 6,
  /** BLOCKED: no evidence found in the corpus read — neither a decision-tester writer nor a
   *  dispatch-family branch references command type 7. Reserved slot only. */
  Unmapped7 = 7,
}

/**
 * Human-readable dispatch family for each {@link AttackCommandType}, keyed by the ROM's
 * numeric command-type byte. DERIVED_ROM for 1/2 (melee) and 4/5/6 (ranged) — see
 * `FUN_8005d494` (chunk_0007.c:4750-4782). Types 0/3/7 are `"unmapped"` — BLOCKED, no dispatch
 * evidence found; do not infer a family for them.
 */
export const COMMAND_FAMILY: Readonly<Record<AttackCommandType, "melee" | "ranged" | "unmapped">> = {
  [AttackCommandType.Unmapped0]: "unmapped",
  [AttackCommandType.Melee1]: "melee",
  [AttackCommandType.Melee2]: "melee",
  [AttackCommandType.Unmapped3]: "unmapped",
  [AttackCommandType.Ranged4]: "ranged",
  [AttackCommandType.Ranged5]: "ranged",
  [AttackCommandType.Ranged6]: "ranged",
  [AttackCommandType.Unmapped7]: "unmapped",
};

/**
 * ROM command subtype byte (actor+0x586), range 0-5. Set by `zz_0069ea4_`
 * (chunk_0009.c:500-534) and `zz_0069fe0_` (chunk_0009.c:554-587) from additional button bits
 * and state. Only value 4 (air/elevated) has a DERIVED_ROM meaning from the corpus read; the
 * rest are BLOCKED — documented per mechanic A/D-K, do not invent meanings for them.
 */
export enum AttackCommandSubtype {
  /** BLOCKED: subtype byte observed in range 0-5 (chunk_0009.c:500-587) but no specific
   *  meaning for 0 was isolated in the corpus read. */
  Unmapped0 = 0,
  /** BLOCKED: see Unmapped0 — no specific meaning for 1 was isolated in the corpus read. */
  Unmapped1 = 1,
  /** BLOCKED: see Unmapped0 — no specific meaning for 2 was isolated in the corpus read. */
  Unmapped2 = 2,
  /** BLOCKED: see Unmapped0 — no specific meaning for 3 was isolated in the corpus read. */
  Unmapped3 = 3,
  /**
   * Air / elevated. DERIVED_ROM: value 4 is set at actor+0x586 under an air/elevated gate in
   * `zz_0069ea4_` (chunk_0009.c:500-534). This is the one subtype value with a confirmed
   * citation from the ticket evidence — cited, not invented.
   */
  AirElevated4 = 4,
  /** CHARGED-RANGED subtype. DERIVED_ROM (behavior-notes (bd)): subtype 5 is set at actor+0x586
   *  by `zz_0069fe0_` (ranged path) when the charge timer is positive (`0.0 < actor+0x6a4`),
   *  confirming the charged-ranged meaning the earlier read only SUSPECTED. CORRECTION (bd): the
   *  gate constant `FLOAT_8043762c` = 0.0 (DOL-read, anchor-validated) — it is a positive-timer
   *  gate (`0.0 < timer`), NOT a distance/melee threshold. (Named Unmapped5 only to preserve the
   *  ROM byte value.) */
  Unmapped5 = 5,
}

/** A single resolved attack command: (type, subtype) pair, mirroring the ROM's
 *  actor+0x591/+0x586 command state. Schema only — nothing in the sim constructs one of
 *  these yet (that is ATK-003, blocked on trace T1). */
export interface AttackCommand {
  type: AttackCommandType;
  subtype: AttackCommandSubtype;
}
