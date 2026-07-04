// Exact per-combo-step melee data: cue -> family action/variant jump tables -> config seed ->
// (bank, group, slot) action-script stream -> armed HIT kind -> hit.bin record -> family damage
// record, per B-melee combo STEP (not just the first swing).
//
// Sources (all DERIVED):
// - data/actionStreamTables.json (scripts/gen-action-stream-tables.mjs): concrete PPC emulation
//   of each family's actor+0x4b4 attack virtual per (borg, actionIndex +0x580, variantIndex
//   +0x581) — resolves actionIndex=1 (ground B melee) variant 0's seed slot into the borg's
//   family action-script bank (actor+0x1d80), plus (when the ROM emulation found one) a chain
//   callback that re-issues the command into a DIFFERENT variant for the finishing hit. See
//   research/decomp/cue-script-stream-decode-2026-07-04.md ("Fleet extraction recipe") and
//   research/decomp/action-stream-extraction-audit.md for the coverage/validation numbers.
// - data/meleeAnimKinds.json: bank -> group -> slot -> ordered stream events (armHit kind,
//   playAnim group/slot, wait/frame-clock) — same source meleeExactData.ts already reads.
// - data/attackHitTables.json / familyDamageRecords.json: kind -> hit record -> family damage
//   record (attackHitData.ts / familyDamageData.ts accessors, reused as-is).
//
// THE LADDER RULE (validated end-to-end against G RED / NEO G RED / Sword Knight in the decode
// note): a held-B combo replays the SAME variant's stream with the ROM's `(actor+0x6ea)++`
// auto-increment cursor on every re-arm (FUN_801780e4) -- i.e. step N's slot is
// `seedSlot + N` -- UNTIL the variant's chain callback (config+0x10/+0x14, e.g. FUN_8018ded0)
// fires and re-issues the command into a DIFFERENT variant, whose OWN seed slot becomes the
// final rung. Validated readings:
//   - pl0629 (NEO G RED): v0 seed 25 -> step1 auto-inc 26 -> chain cb -> v6 seed 27
//     (kinds 1, 2, 8 -- exactly the decode note's "standing-mash 3rd-hit finisher" table).
//   - pl0200 (SWORD KNIGHT): v0 seed 0, no chain callback -> pure auto-increment 0/1/2
//     (kinds 1, 2, 5 -- exactly the audit's validation table).
// SELECTION CAVEAT (honest, not hidden): plain auto-increment past step 1 without a chain-
// callback confirmation is DERIVED-but-unvalidated for that specific borg -- the decode note
// only proves the +0x6ea re-arm mechanic generically (it is part of the shared engine, not
// per-borg script data) and validates the *stopping point* for two borgs specifically. The
// ladder is capped at MAX_LADDER_STEPS (3, matching COMBO.STEP_DAMAGE_MULT.length and the
// existing comboHits generator's own cap) so it never over-walks into unrelated context-variant
// slots (v1..v4 in the same action, which are ALTERNATE commands selected by subtype/context,
// not further chain steps of v0's ladder -- confirmed by their seeds never colliding with
// v0.seedSlot+1/+2 in either validated family).
//
// HANDLED HONESTLY (return null / stop the walk, never fabricate):
//   - No action-1 (ground B) entry, or its variant-0 config doesn't seed a group-3 (melee)
//     script slot (dash-only/shot-only/code-driven borgs, ~44% of the roster per the
//     extraction audit's "no stream call reached" + "run capped" + "ambiguous" buckets).
//   - The seeded bank/slot is missing from meleeAnimKinds.json (pl0402/pl0408's bank
//     0x80327440 known upstream truncation -- gen-melee-anim-kinds.mjs's next-table-bound bug
//     drops that bank's g3 s3+; steps that DO exist (s0-s2) still resolve, the walk just stops
//     honestly at the missing slot instead of guessing further).
//   - A stream exists but arms NO kind (windup-only slot, e.g. charge/dash overlays that
//     share the bank) -- the walk stops there rather than emitting a hitless step.
//   - The armed kind has no valid hit-bin record window -- that step is nulled individually
//     (kept as a shorter ladder) rather than discarding the whole ladder.
// Callers (combat.ts) fall back to the existing TUNED COMBO.STEP_STARTUP_SCALE rescale for any
// borg/step this module returns null for.

import actionStreamTablesData from "./data/actionStreamTables.json" with { type: "json" };
import meleeAnimKindsData from "./data/meleeAnimKinds.json" with { type: "json" };
import { attackHitRecordsForKind, attackHitMaxReachForKind } from "./attackHitData.js";
import { familyDamageRecordForBorg } from "./familyDamageData.js";
import type { DamageRecord } from "./gauges.js";

// --- data/actionStreamTables.json shape (only the fields this module reads) --------------
interface ChainCallback {
  configOffset: string;
  address: string;
  setsVariant: number | null;
  setsAction: number | null;
  reissuesCommand: [number, number, number] | null;
}

interface ActionVariant {
  bank: string | null;
  group: number | null;
  seedSlot: number | null;
  chainCallback: ChainCallback | null;
}

interface ActionEntry {
  variants: Record<string, ActionVariant>;
}

interface BorgActionStreams {
  actions: Record<string, ActionEntry>;
}

type ActionStreamTablesFile = {
  _meta: Record<string, unknown>;
  borgs: Record<string, BorgActionStreams>;
};

// --- data/meleeAnimKinds.json shape (only the fields this module reads) ------------------
interface StreamEvent {
  op: string;
  kind?: number;
  group?: number;
  slot?: number;
}

interface StreamEntry {
  streamAddress: string;
  events: StreamEvent[];
}

interface MeleeAnimKindsFile {
  _meta: Record<string, unknown>;
  banks: Record<string, { groups: Record<string, Record<string, StreamEntry>> }>;
}

const STREAMS = actionStreamTablesData as unknown as ActionStreamTablesFile;
const KINDS = meleeAnimKindsData as unknown as MeleeAnimKindsFile;

/** B-melee (ground) action index in the family action table (+0x580 == 1, DERIVED — see
 *  cue-script-stream-decode-2026-07-04.md hop 3). */
const GROUND_MELEE_ACTION_INDEX = "1";
/** Baseline (opener) variant index (+0x581 == 0). */
const BASELINE_VARIANT_INDEX = "0";
/** The action-script group constant for melee strikes (DERIVED — group 3 in every validated
 *  family; group 2 = dash rams, group 4 = charge/air specials). */
const MELEE_GROUP = 3;
/** Cap on ladder length: matches COMBO.STEP_DAMAGE_MULT.length / the existing comboHits
 *  generator's own cap. See header caveat on why plain auto-increment isn't walked further. */
const MAX_LADDER_STEPS = 3;

export interface ComboStep {
  /** Which slot in the family bank's group-3 table this step plays (seedSlot + N, or the
   *  chain callback's redirected variant seed for the final rung). */
  slot: number;
  /** The script-armed HIT kind for this step. */
  kind: number;
  /** First active frame of the swing (hit.bin record +0x06, vs the anim frame clock). */
  activeStart: number;
  /** Last active frame (inclusive, +0x08). */
  activeEnd: number;
  /** Longest hitbox reach across the kind's records (|offset| + max extent/radius). */
  reach: number;
  /** The borg family's exact damage record for this step, or null if unresolved. */
  damageRecord: DamageRecord | null;
  /** The action-script (group, slot) this step's stream plays via its playAnim op, when the
   *  stream data captured one — the anim-label bridge (borgPresentationAssets.ts) resolves
   *  this to an exported clip suffix (playAnim slot -> clip _sNN), NOT this step's own
   *  action-script slot (those are two different numbering axes — see actionStreamData.ts's
   *  header and the pl0615 charge_shot precedent in borgPresentationAssets.ts). */
  animStreamRef: { group: number; slot: number } | null;
}

const cache = new Map<string, ComboStep[] | null>();

/** Resolve one action-script stream's armed HIT kind + playAnim target, or null if the bank/
 *  slot is missing or the stream arms no kind (windup-only). */
function resolveStreamArm(
  bankAddress: string,
  slot: number,
): { kind: number; animStreamRef: { group: number; slot: number } | null } | null {
  const bank = KINDS.banks[bankAddress];
  const group = bank?.groups?.[`g${MELEE_GROUP}`];
  const stream = group?.[`s${slot}`];
  if (!stream) return null;
  const armHit = stream.events.find((e) => e.op === "armHit" && typeof e.kind === "number");
  if (!armHit || typeof armHit.kind !== "number") return null;
  const playAnim = stream.events.find(
    (e) => e.op === "playAnim" && typeof e.group === "number" && typeof e.slot === "number",
  );
  const animStreamRef =
    playAnim && typeof playAnim.group === "number" && typeof playAnim.slot === "number"
      ? { group: playAnim.group, slot: playAnim.slot }
      : null;
  return { kind: armHit.kind, animStreamRef };
}

/** Build one ComboStep from a resolved (kind, animStreamRef) pair, or null if the kind has no
 *  usable hit-bin window (kept per-step so a partially-decoded ladder still returns its good
 *  steps instead of failing whole). */
function stepFromKind(
  borgId: string,
  slot: number,
  kind: number,
  animStreamRef: { group: number; slot: number } | null,
): ComboStep | null {
  const records = attackHitRecordsForKind(borgId, kind);
  const windowed = records.find((record) => record.activeEnd >= record.activeStart && record.activeStart >= 0);
  if (!windowed) return null;
  const reach = attackHitMaxReachForKind(borgId, kind);
  return {
    slot,
    kind,
    activeStart: windowed.activeStart,
    activeEnd: windowed.activeEnd,
    reach: reach ?? 0,
    damageRecord: familyDamageRecordForBorg(borgId, windowed.damageRecordIndex),
    animStreamRef,
  };
}

/**
 * Resolve a borg's exact B-melee combo ladder (ground, action index 1, baseline variant 0),
 * DERIVED end-to-end from actionStreamTables.json + meleeAnimKinds.json + attackHitTables.json.
 * Returns null when the borg has no resolved ladder at all (callers keep today's
 * meleeExactData.ts single-swing behavior + the TUNED COMBO.STEP_STARTUP_SCALE rescale for
 * chain steps). Cached per borg id.
 */
export function comboLadderForBorgId(id: string): ComboStep[] | null {
  const key = id.toLowerCase();
  const cached = cache.get(key);
  if (cached !== undefined) return cached;

  const result = computeLadder(key);
  cache.set(key, result);
  return result;
}

function computeLadder(borgId: string): ComboStep[] | null {
  const borg = STREAMS.borgs[borgId];
  const action = borg?.actions?.[GROUND_MELEE_ACTION_INDEX];
  const baseline = action?.variants?.[BASELINE_VARIANT_INDEX];
  if (!baseline || baseline.group !== MELEE_GROUP || typeof baseline.seedSlot !== "number" || !baseline.bank) {
    return null;
  }
  const bankAddress = baseline.bank;

  const steps: ComboStep[] = [];
  let cursor = baseline.seedSlot;

  const tryPushSlot = (slot: number): boolean => {
    const arm = resolveStreamArm(bankAddress, slot);
    if (!arm) return false;
    const step = stepFromKind(borgId, slot, arm.kind, arm.animStreamRef);
    if (!step) return false; // stream arms a kind, but no usable hit-bin window for it
    steps.push(step);
    return true;
  };

  if (!tryPushSlot(cursor)) return null; // opener itself doesn't resolve — nothing to expose

  const chainTargetVariant =
    baseline.chainCallback && typeof baseline.chainCallback.setsVariant === "number"
      ? action?.variants?.[String(baseline.chainCallback.setsVariant)]
      : null;
  const chainTargetSeed =
    chainTargetVariant && chainTargetVariant.group === MELEE_GROUP && typeof chainTargetVariant.seedSlot === "number"
      ? chainTargetVariant.seedSlot
      : null;

  while (steps.length < MAX_LADDER_STEPS) {
    // Final rung: prefer the chain-callback's redirected variant when the extraction recorded
    // one (validated pattern — pl0629's mash finisher is v6, not a further auto-increment).
    if (steps.length === MAX_LADDER_STEPS - 1 && chainTargetSeed !== null) {
      if (tryPushSlot(chainTargetSeed)) break;
    }
    cursor += 1;
    if (!tryPushSlot(cursor)) break;
  }

  return steps.length > 0 ? steps : null;
}

/** Number of steps in the borg's resolved ladder (0 when unresolved). Exposed so
 *  actionProfiles.json's comboHits (asset-derived, independent source) can be cross-checked
 *  against the exact DOL-derived ladder length without this pass changing comboHits itself. */
export function comboLadderStepCountForBorgId(id: string): number {
  return comboLadderForBorgId(id)?.length ?? 0;
}
