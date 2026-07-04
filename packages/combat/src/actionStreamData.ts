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
//
// AIR B / B CHARGE (actionIndex 2 / 3): airBMoveForBorgId / chargeMoveForBorgId below extend
// the same exact-data join to the two OTHER B-family actions (see cue-script-stream-decode-
// 2026-07-04.md hop 3's actionIndex table: a0=dash, a1=ground melee (above), a2=air B,
// a3=B charge). Neither is a combo LADDER — both are single baseline leaves (action 2's air
// row plays once per press; action 3 never re-arms via +0x6ea at all) — so they're exposed as
// ExactMoveLeaf, not ComboStep[]. Air B prefers the leaf's airSeedSlot (the airborne-fork slot)
// over the shared seedSlot when the extraction found a distinct one. B charge leaves often arm
// NO kind (windup-only — the real hit is a spawned projectile child, e.g. G RED's chest beam);
// callers must check `kind !== null` before trusting activeStart/activeEnd/damageRecord, but
// animStreamRef is still valid on a windup-only leaf (the charge-fire anim is real either way).

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
  /** Airborne-fork slot (config's air-config byte, when the extraction found a distinct
   *  branch guarded on actor+0x5e0 & 0x40 — see cue-script-stream-decode-2026-07-04.md's
   *  "airborne" evidence entry). Null when the leaf has no separate air seed (either it's
   *  ground-only, or the ground/air paths share the same slot). */
  airSeedSlot: number | null;
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
  /** playAnim/blendAnim only: group byte 0x80 flag (shared descriptor bank axis). */
  shared?: boolean;
}

interface StreamEntry {
  streamAddress: string;
  events: StreamEvent[];
}

/** One PATH-B per-anim authored sound event (DERIVED — the actor+0x4e8 sound-event table
 *  joined to the anim the stream plays via the anim-descriptor banks +0x1d88/+0x1d8c; see
 *  research/decomp/anim-sound-op-decode-2026-07-04.md and gen-melee-anim-kinds.mjs's
 *  collectAnimSounds). `frame` is the ROM anim-clock frame the sound fires on (0 = anim
 *  start); `id` is the literal soundId (dispatcher zz_00efb3c_, bank = id>>7, sample =
 *  id&0x7f — the se_<hex> manifest key axis); `mode` 0 = plain positional, 1 = anim-rate
 *  variant select (ROM plays id-1/id/id+1 around rate 0.7/2.0 — the port plays the base id,
 *  TUNED simplification), 2|3 = listener-lerped positional; `part` is the anim part the
 *  event rode (deduped across parts by the generator). */
export interface AuthoredSoundEvent {
  frame: number;
  id: number;
  mode: number;
  part: number;
}

interface MeleeAnimKindsFile {
  _meta: Record<string, unknown>;
  banks: Record<string, { groups: Record<string, Record<string, StreamEntry>> }>;
  borgs: Record<string, { animSounds?: Record<string, AuthoredSoundEvent[]> }>;
}

const STREAMS = actionStreamTablesData as unknown as ActionStreamTablesFile;
const KINDS = meleeAnimKindsData as unknown as MeleeAnimKindsFile;

/** B-melee (ground) action index in the family action table (+0x580 == 1, DERIVED — see
 *  cue-script-stream-decode-2026-07-04.md hop 3). */
const GROUND_MELEE_ACTION_INDEX = "1";
/** Air B action index (+0x580 == 2, DERIVED — same hop). */
const AIR_MELEE_ACTION_INDEX = "2";
/** B charge action index (+0x580 == 3, DERIVED — same hop). */
const CHARGE_ACTION_INDEX = "3";
/** Baseline (opener) variant index (+0x581 == 0). */
const BASELINE_VARIANT_INDEX = "0";
/** The action-script group constant for melee strikes (DERIVED — group 3 in every validated
 *  family; group 2 = dash rams, group 4 = charge/air specials). */
const MELEE_GROUP = 3;
/** The action-script group constant for charge/air specials (DERIVED — group 4 in every
 *  validated family; see cue-script-stream-decode-2026-07-04.md hop 3's "rule" paragraph). */
const CHARGE_AIR_GROUP = 4;
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
  /** PATH-B authored sound events of the anim this step plays (DERIVED — see
   *  AuthoredSoundEvent). Empty when the anim carries none. */
  sounds: AuthoredSoundEvent[];
}

const cache = new Map<string, ComboStep[] | null>();

/** Resolve one action-script stream's armed HIT kind (null when the stream is windup-only —
 *  e.g. a charge stream that only fires a projectile child) + playAnim target + the played
 *  anim's PATH-B authored sound events (empty when the anim carries none, or the borg has no
 *  captured sound table). Returns null only when the bank/group/slot itself is missing
 *  (nothing to resolve at all); a windup-only stream still returns its animStreamRef with
 *  kind null so callers can set the anim without fabricating hit data. `streamGroup` is the
 *  meleeAnimKinds.json group axis (3 = melee strikes, 4 = charge/air specials — see
 *  cue-script-stream-decode-2026-07-04.md hop 3). */
function resolveStreamArm(
  borgId: string,
  bankAddress: string,
  streamGroup: number,
  slot: number,
): {
  kind: number | null;
  animStreamRef: { group: number; slot: number } | null;
  sounds: AuthoredSoundEvent[];
} | null {
  const bank = KINDS.banks[bankAddress];
  const group = bank?.groups?.[`g${streamGroup}`];
  const stream = group?.[`s${slot}`];
  if (!stream) return null;
  const armHit = stream.events.find((e) => e.op === "armHit" && typeof e.kind === "number");
  const playAnim = stream.events.find(
    (e) => e.op === "playAnim" && typeof e.group === "number" && typeof e.slot === "number",
  );
  const animStreamRef =
    playAnim && typeof playAnim.group === "number" && typeof playAnim.slot === "number"
      ? { group: playAnim.group, slot: playAnim.slot }
      : null;
  // PATH-B authored sounds for the anim this stream plays (generator key mirrors the
  // playAnim op's shared-bank flag — the same descriptor-bank axis zz_004d1f4_ resolves).
  const soundKey = playAnim ? `${playAnim.shared ? "shared:" : ""}g${playAnim.group}s${playAnim.slot}` : null;
  const sounds = (soundKey ? KINDS.borgs?.[borgId]?.animSounds?.[soundKey] : undefined) ?? [];
  return {
    kind: armHit && typeof armHit.kind === "number" ? armHit.kind : null,
    animStreamRef,
    sounds,
  };
}

/** Build one ComboStep from a resolved (kind, animStreamRef) pair, or null if the kind has no
 *  usable hit-bin window (kept per-step so a partially-decoded ladder still returns its good
 *  steps instead of failing whole). */
function stepFromKind(
  borgId: string,
  slot: number,
  kind: number,
  animStreamRef: { group: number; slot: number } | null,
  sounds: AuthoredSoundEvent[],
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
    sounds,
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
    const arm = resolveStreamArm(borgId, bankAddress, MELEE_GROUP, slot);
    if (!arm || arm.kind === null) return false; // no stream, or windup-only (no armed kind)
    const step = stepFromKind(borgId, slot, arm.kind, arm.animStreamRef, arm.sounds);
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

// ---------------------------------------------------------------------------------------
// Air B (actionIndex 2) and B charge (actionIndex 3) — single baseline leaves, NOT combo
// ladders (neither action re-arms via +0x6ea the way ground B melee does — see
// cue-script-stream-decode-2026-07-04.md's G RED end-to-end table: action 2's air row is a
// one-shot swing, and action 3 never touches the melee-strike group at all). Same DERIVED
// join (actionStreamTables.json leaf -> meleeAnimKinds.json stream -> attackHitTables.json
// record -> familyDamageData.ts), but exposed as a single ExactMoveLeaf per borg instead of a
// stepped array.
// ---------------------------------------------------------------------------------------

export interface ExactMoveLeaf {
  /** The action-script (group, slot) this leaf's stream lives at (the group-4 axis for both
   *  air B and B charge — see CHARGE_AIR_GROUP). */
  slot: number;
  /** The script-armed HIT kind, or null when the stream is windup-only (e.g. G RED's B-charge
   *  stream arms no kind at all — its damage comes from a spawned projectile child, per the
   *  decode note's "no armHit — windup only" row). A null kind still carries a valid
   *  animStreamRef; callers use it to drive the anim without fabricating hit data. */
  kind: number | null;
  /** First active frame of the swing (hit.bin record +0x06), null when kind is null. */
  activeStart: number | null;
  /** Last active frame (inclusive, +0x08), null when kind is null. */
  activeEnd: number | null;
  /** Longest hitbox reach across the kind's records, 0 when kind is null or has no records. */
  reach: number;
  /** The borg family's exact damage record for this leaf, or null (kind null, or the kind has
   *  no windowed hit-bin record, or the family table lookup itself came up empty). */
  damageRecord: DamageRecord | null;
  /** The action-script (group, slot) this leaf's stream plays via its playAnim op — the
   *  anim-label bridge target (see ComboStep.animStreamRef's doc for the numbering-axis
   *  caveat; same rule applies here). */
  animStreamRef: { group: number; slot: number } | null;
  /** PATH-B authored sound events of the anim this leaf plays (DERIVED — see
   *  AuthoredSoundEvent). Empty when the anim carries none. Valid on windup-only leaves too
   *  (a charge-fire anim's whoosh is real even when the damage is a spawned child). */
  sounds: AuthoredSoundEvent[];
}

const airMoveCache = new Map<string, ExactMoveLeaf | null>();
const chargeMoveCache = new Map<string, ExactMoveLeaf | null>();

/** Shared leaf-resolution: given a (bank, group, slot), build an ExactMoveLeaf. Returns null
 *  only when the bank/group/slot is entirely missing from meleeAnimKinds.json (nothing was
 *  captured for this stream at all) — a resolved-but-windup-only stream (kind null) still
 *  returns a leaf so callers can use its animStreamRef. */
function leafFromSlot(borgId: string, bank: string, group: number, slot: number): ExactMoveLeaf | null {
  const arm = resolveStreamArm(borgId, bank, group, slot);
  if (!arm) return null;
  if (arm.kind === null) {
    return {
      slot,
      kind: null,
      activeStart: null,
      activeEnd: null,
      reach: 0,
      damageRecord: null,
      animStreamRef: arm.animStreamRef,
      sounds: arm.sounds,
    };
  }
  const records = attackHitRecordsForKind(borgId, arm.kind);
  const windowed = records.find((record) => record.activeEnd >= record.activeStart && record.activeStart >= 0);
  const reach = attackHitMaxReachForKind(borgId, arm.kind);
  return {
    slot,
    kind: arm.kind,
    activeStart: windowed ? windowed.activeStart : null,
    activeEnd: windowed ? windowed.activeEnd : null,
    reach: reach ?? 0,
    damageRecord: windowed ? familyDamageRecordForBorg(borgId, windowed.damageRecordIndex) : null,
    animStreamRef: arm.animStreamRef,
    sounds: arm.sounds,
  };
}

/**
 * Resolve a borg's exact air-B move (action index 2, baseline variant 0), DERIVED end-to-end
 * from actionStreamTables.json + meleeAnimKinds.json + attackHitTables.json. Prefers the
 * leaf's airSeedSlot (the airborne-fork slot, config's air-config byte guarded on actor+0x5e0
 * & 0x40 — cue-script-stream-decode-2026-07-04.md's "airborne" evidence) when the extraction
 * captured a distinct one; falls back to the shared seedSlot for leaves whose ground/air paths
 * share the same slot (most of the roster — see the G RED row: seedSlot 0 IS the air slot,
 * airSeedSlot null). Returns null when the borg has no action-2 baseline leaf, or its group
 * isn't the charge/air-special axis (CHARGE_AIR_GROUP), or the resolved slot has no captured
 * stream at all. Callers keep today's ground-melee-def-reuse fallback for null. Cached per
 * borg id.
 */
export function airBMoveForBorgId(id: string): ExactMoveLeaf | null {
  const key = id.toLowerCase();
  const cached = airMoveCache.get(key);
  if (cached !== undefined) return cached;

  const result = computeAirMove(key);
  airMoveCache.set(key, result);
  return result;
}

function computeAirMove(borgId: string): ExactMoveLeaf | null {
  const borg = STREAMS.borgs[borgId];
  const action = borg?.actions?.[AIR_MELEE_ACTION_INDEX];
  const baseline = action?.variants?.[BASELINE_VARIANT_INDEX];
  if (!baseline || baseline.group !== CHARGE_AIR_GROUP || !baseline.bank) return null;
  const slot = typeof baseline.airSeedSlot === "number" ? baseline.airSeedSlot : baseline.seedSlot;
  if (typeof slot !== "number") return null;
  return leafFromSlot(borgId, baseline.bank, CHARGE_AIR_GROUP, slot);
}

/**
 * Resolve a borg's exact B-charge move (action index 3, baseline variant 0), DERIVED
 * end-to-end the same way as airBMoveForBorgId. B-charge leaves live on the group-4 axis
 * (charge/air specials) and often arm NO kind at all — the decode note's G RED row: the
 * charge stream is windup-only, and the actual hit comes from a spawned projectile child
 * (zz_00e19a8_ type 0x20). Callers still get the leaf's animStreamRef in that case (the
 * charge-fire anim is real even when the damage isn't a melee-shaped hit), and must gate any
 * damage-record use behind `kind !== null` themselves (this module never fabricates one).
 * Returns null when the borg has no action-3 baseline leaf, its group isn't the charge/air
 * axis, or the seeded slot has no captured stream at all. Cached per borg id.
 */
export function chargeMoveForBorgId(id: string): ExactMoveLeaf | null {
  const key = id.toLowerCase();
  const cached = chargeMoveCache.get(key);
  if (cached !== undefined) return cached;

  const result = computeChargeMove(key);
  chargeMoveCache.set(key, result);
  return result;
}

function computeChargeMove(borgId: string): ExactMoveLeaf | null {
  const borg = STREAMS.borgs[borgId];
  const action = borg?.actions?.[CHARGE_ACTION_INDEX];
  const baseline = action?.variants?.[BASELINE_VARIANT_INDEX];
  if (!baseline || baseline.group !== CHARGE_AIR_GROUP || typeof baseline.seedSlot !== "number" || !baseline.bank) {
    return null;
  }
  return leafFromSlot(borgId, baseline.bank, CHARGE_AIR_GROUP, baseline.seedSlot);
}

/** Fleet coverage counters (roster scan), used by the selfcheck log lines to report how many
 *  borgs resolve an exact air-B / charge leaf. Not cached — cheap one-shot roster walk. */
export function airBChargeCoverage(): { airBResolved: number; chargeResolved: number; rosterSize: number } {
  const ids = Object.keys(STREAMS.borgs);
  let airBResolved = 0;
  let chargeResolved = 0;
  for (const id of ids) {
    if (airBMoveForBorgId(id) !== null) airBResolved += 1;
    if (chargeMoveForBorgId(id) !== null) chargeResolved += 1;
  }
  return { airBResolved, chargeResolved, rosterSize: ids.length };
}
