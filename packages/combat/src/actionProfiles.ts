import { AMMO, MELEE, SHOT, SPECIAL } from "./constants.js";
import type { BorgProfile } from "./stats.js";
import type { ProjectileVisualKind, WeaponRefillType } from "./types.js";
import { sourceStatsForBorgId } from "./sourceBorgStats.js";
import actionProfileData from "./data/actionProfiles.json" with { type: "json" };

export type PrimaryAttackKind = "melee" | "shot";

/** Sword-beam finisher projectile (TUNED design: emitted by the LAST hit of a melee combo
 *  chain; HP damage uses the charge/special damage record plus this multiplier bridge). */
export interface SwordBeamDef {
  speed: number;
  lifetime: number;
  hitRadius: number;
  /** Multiplier applied to the melee swing's raw damage. */
  damageMultiplier: number;
  homingTurn: number;
  visualKind: ProjectileVisualKind;
}

export interface MeleeActionDef {
  startup: number;
  active: number;
  duration: number;
  cooldown: number;
  range: number;
  yTolerance: number;
  damageMultiplier: number;
  knockbackMultiplier: number;
  /** Chain length (1 = no combo). Derived in the generator from distinct exported swing banks. */
  comboHits: number;
  /** Frames after a swing's recovery during which the next chain press still connects. TUNED. */
  comboWindowFrames: number;
  /** Combo-finisher projectile, or null for borgs without a sword beam. */
  swordBeam: SwordBeamDef | null;
}

export interface ShotActionDef {
  cooldown: number;
  recovery: number;
  ammoMax: number;
  reloadFrames: number;
  projectileCount: number;
  spreadRadians: number;
  speed: number;
  lifetime: number;
  homingTurn: number;
  hitRadius: number;
  muzzleForwardOffset: number;
  muzzleYOffset: number;
  damageMultiplier: number;
  hitstunMultiplier: number;
  knockbackMultiplier: number;
  visualKind: ProjectileVisualKind;
  /** Hold-B charge shot: hold accumulates charge frames, release fires a scaled projectile. */
  chargeable: boolean;
  /** Held frames needed for charge tier 1 / tier 2 (tier 2 is also the accumulation cap). */
  chargeTier1Frames: number;
  chargeTier2Frames: number;
  chargeTier1DamageMult: number;
  chargeTier2DamageMult: number;
  /** Ballistic drop applied to the projectile's Y velocity each frame (0 = none). TUNED. */
  bulletDrop: number;
  /** Weapon-0 refill type (ATK-009, WeaponRefillType). DERIVED per-borg where the extracted
   *  stat row has data (research/decomp/data/borg-hp-stat-rows-802f2988.json via
   *  sourceBorgStats.json weaponSlots[0].chargeType); TUNED_EXISTING fallback (all-at-once)
   *  for borgs missing a row. */
  refillType: WeaponRefillType;
  /** Weapon-0 refill param (aux +0x792 feed; ROM-units timer seed). DERIVED per-borg where
   *  available (weaponSlots[0].chargeCount); falls back to a value that reproduces
   *  SHOT.RELOAD_FRAMES via AMMO.DEFAULT_ALL_AT_ONCE_TIMER_FRAMES. */
  refillParam: number;
}

export interface SpecialActionDef {
  cooldown: number;
  duration: number;
  radius: number;
  damageMultiplier: number;
  knockbackMultiplier: number;
}

export interface BorgActionProfile {
  primary: PrimaryAttackKind;
  confidence: "medium" | "low" | "fallback";
  melee: MeleeActionDef | null;
  shot: ShotActionDef | null;
  special: SpecialActionDef;
  /** Max mid-air jumps ("Air jump level N"; flyers 3) — mirrors BorgProfile.airJumpLevel, exposed
   *  so the HUD's Jump Gauge (CONFIRMED_MANUAL, behavior-notes (ao)) can show remaining/max. */
  airJumpLevel: number;
  /** Sustained-flight flyer flag (mirrors BorgProfile.flyer). */
  flyer: boolean;
}

type RawActionProfile = {
  primary?: PrimaryAttackKind;
  confidence?: "medium" | "low" | "fallback";
  melee?: Partial<MeleeActionDef> | null;
  shot?: Partial<ShotActionDef> | null;
  special?: Partial<SpecialActionDef> | null;
};

const RAW_PROFILES = actionProfileData.profiles as Record<string, RawActionProfile>;

const DEFAULT_MELEE: MeleeActionDef = {
  startup: MELEE.STARTUP,
  active: MELEE.ACTIVE,
  duration: MELEE.DURATION,
  cooldown: MELEE.COOLDOWN,
  range: MELEE.RANGE,
  yTolerance: MELEE.Y_TOLERANCE,
  damageMultiplier: 1,
  knockbackMultiplier: 1,
  comboHits: 1,
  comboWindowFrames: 22,
  swordBeam: null,
};

const DEFAULT_SHOT: ShotActionDef = {
  cooldown: SHOT.FIRE_COOLDOWN,
  recovery: MELEE.DURATION,
  ammoMax: SHOT.AMMO_MAX,
  reloadFrames: SHOT.RELOAD_FRAMES,
  projectileCount: 1,
  spreadRadians: 0,
  speed: SHOT.SPEED,
  lifetime: SHOT.LIFETIME,
  homingTurn: SHOT.HOMING_TURN,
  hitRadius: SHOT.HIT_RADIUS,
  muzzleForwardOffset: 30,
  muzzleYOffset: 20,
  damageMultiplier: 1,
  hitstunMultiplier: 1,
  knockbackMultiplier: 1,
  visualKind: "energy",
  chargeable: false,
  chargeTier1Frames: 30,
  chargeTier2Frames: 90,
  chargeTier1DamageMult: 1.6,
  chargeTier2DamageMult: 2.4,
  bulletDrop: 0,
  // TUNED_EXISTING fallback: all-at-once at the pre-ATK-009 reload feel (see AMMO constants).
  refillType: 0,
  refillParam: AMMO.DEFAULT_ALL_AT_ONCE_TIMER_FRAMES,
};

const DEFAULT_SPECIAL: SpecialActionDef = {
  cooldown: SPECIAL.COOLDOWN,
  duration: SPECIAL.DURATION,
  radius: SPECIAL.RADIUS,
  damageMultiplier: SPECIAL.DMG_MULT,
  knockbackMultiplier: 1,
};

/**
 * Resolve the TUNED asset-backed action profile for a borg.
 *
 * Source: packages/combat/src/data/actionProfiles.json generated by
 * scripts/gen-combat-action-profiles.mjs from weapon-attachment and action-animation
 * inventories. It is intentionally not labeled DERIVED: hit-bin per-move semantics remain
 * undecoded, so missing data falls back to the old generic constants.
 */
const RESOLVED_CACHE = new WeakMap<BorgProfile, BorgActionProfile>();

export function actionProfileForProfile(profile: BorgProfile): BorgActionProfile {
  const cached = RESOLVED_CACHE.get(profile);
  if (cached) return cached;
  const resolved = resolveActionProfile(profile);
  RESOLVED_CACHE.set(profile, resolved);
  return resolved;
}

function resolveActionProfile(profile: BorgProfile): BorgActionProfile {
  const raw = RAW_PROFILES[profile.id];
  const melee = profile.hasMelee ? { ...DEFAULT_MELEE, ...(raw?.melee ?? {}) } : null;
  const shot = profile.hasShot
    ? { ...DEFAULT_SHOT, ...(raw?.shot ?? {}), ...weaponZeroRowOverrides(profile.id, profile.level) }
    : null;

  let primary = raw?.primary ?? chooseFallbackPrimary(profile);
  if (primary === "melee" && melee === null && shot !== null) primary = "shot";
  if (primary === "shot" && shot === null && melee !== null) primary = "melee";

  return {
    primary,
    confidence: raw?.confidence ?? "fallback",
    melee,
    shot,
    special: { ...DEFAULT_SPECIAL, ...(raw?.special ?? {}) },
    airJumpLevel: profile.airJumpLevel,
    flyer: profile.flyer,
  };
}

/**
 * Weapon-0 ammoMax/refillType/refillParam sourced from the ROM's per-borg stat row (ATK-009,
 * findings.md mechanic P; row source `research/decomp/data/borg-hp-stat-rows-802f2988.json`,
 * resolved per-borg-id via `sourceBorgStats.json`'s already-verified extraction).
 *
 * Row layout CONFIRMED by re-reading the init code (chunk_0007.c:60-94) against an
 * independent player-guide cross-check (behavior-notes.md section (am), 4 exact anchors:
 * G RED/pl0615, FLAME DRAGON/pl0500, CYBER DEATH DRAGON/pl0503, DEATH HEAD/pl0505):
 *   row = [hp, w0cur, w0max, w0refillType, w0refillParam, w1cur, w1max, w1refillType, w1refillParam]
 * `sourceBorgStats.json`'s `weaponSlots[N].ammoType`/`ammoCount` are that weapon's
 * row cur/max u16s (always equal at spawn — a fresh cell starts full); `chargeType`/
 * `chargeCount` are that weapon's row refillType/refillParam u16s. Live-verified anchor:
 * G RED (pl0615) -> weapon-0 ammoCount 5, matching the captured HUD value (behavior-notes.md
 * ag). refillParam's frames interpretation (180/300 ~= 3s/5s) is strong-but-unverified per
 * (am) — AMMO.REFILL_RATE_PER_FRAME / AMMO.DEFAULT_ALL_AT_ONCE_TIMER_FRAMES remain the
 * labeled-TUNED conversion knobs for borgs without a usable row value.
 *
 * Only overrides fields the row actually has data for (ammoMax > 0); borgs missing a row, or
 * with a 0 weapon-0 ammo feed (melee-only borgs — DEFAULT_SHOT/raw profile still apply for
 * borgs that HAVE a shot action per profile.hasShot), keep the actionProfiles.json/DEFAULT_SHOT
 * fallback untouched (labeled TUNED_EXISTING there).
 */
function weaponZeroRowOverrides(borgId: string, level?: number): Partial<ShotActionDef> {
  const weapon0 = sourceStatsForBorgId(borgId, level)?.weaponSlots[0];
  if (!weapon0 || weapon0.ammoCount <= 0) return {};
  return {
    ammoMax: weapon0.ammoCount,
    refillType: weapon0.chargeType,
    refillParam: weapon0.chargeCount > 0 ? weapon0.chargeCount : AMMO.DEFAULT_ALL_AT_ONCE_TIMER_FRAMES,
  };
}

/**
 * Weapon-1 cell source (ATK-009 follow-up per behavior-notes.md (am)): same row/field
 * semantics as weapon 0 (see weaponZeroRowOverrides), just `weaponSlots[1]`. Weapon 1 is
 * structurally modeled (combat.ts weapon-cell array index 1) but STILL UNUSED gameplay-wise
 * — no per-weapon command resolver dispatches to it yet (ATK-009 "Required behavior") — this
 * only sources its DATA so the cell is ROM-accurate once something does wire it up. Returns
 * null when the borg has no row or a 0 weapon-1 ammo feed (melee-only weapon-1, or borgs
 * without an extracted row).
 */
export interface WeaponOneCellSource {
  max: number;
  refillType: number;
  refillParam: number;
}

export function weaponOneCellSourceForBorgId(borgId: string, level?: number): WeaponOneCellSource | null {
  const weapon1 = sourceStatsForBorgId(borgId, level)?.weaponSlots[1];
  if (!weapon1 || weapon1.ammoCount <= 0) return null;
  return {
    max: weapon1.ammoCount,
    refillType: weapon1.chargeType,
    refillParam: weapon1.chargeCount > 0 ? weapon1.chargeCount : AMMO.DEFAULT_ALL_AT_ONCE_TIMER_FRAMES,
  };
}

export function startingAmmoForProfile(profile: BorgProfile): number {
  return actionProfileForProfile(profile).shot?.ammoMax ?? 0;
}

function chooseFallbackPrimary(profile: BorgProfile): PrimaryAttackKind {
  if (profile.hasShot && !profile.hasMelee) return "shot";
  if (profile.hasMelee && !profile.hasShot) return "melee";
  if (profile.rangePref === "ranged" && profile.hasShot) return "shot";
  return "melee";
}
