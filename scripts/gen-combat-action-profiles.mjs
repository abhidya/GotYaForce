#!/usr/bin/env node
import { promises as fs } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

const paths = {
  borgs: "packages/assets/data/borgs.json",
  weaponMap: "research/asset-inventory/weapon-attachment-map.json",
  actionAssets: "research/animation-actions/borg-action-assets.json",
  // OBSERVED_WIKI per-move catalog (button labels "B Charge"/"X", move names) — community
  // sourced, NOT decomp-derived; used only to select WHO charges / WHOSE special is a
  // projectile. All numeric tuning stays TUNED.
  moveProps: "packages/combat/src/data/borgMoveProperties.json",
  // TUNED per-borg projectile visual family (asset-inventory scan, not a decoded effect id).
  visualFamilies: "packages/combat/src/data/projectileVisualFamilies.json",
  output: "packages/combat/src/data/actionProfiles.json",
};

const schema = "combat-action-profiles.v1";

// G Red hero line, special-cased for the signature charge shot + sword beam (TUNED note,
// verified 2026-07-02): weapon-attachment-map.json gives pl0615 (G RED) / pl0629 (NEO G RED) /
// pl062a (G BLACK) only Low-confidence bulletProjectile/muzzle/impact families — no beam/cannon
// signal — so the family-based `chargeable` heuristic below misses the line entirely, and no
// `sword` family is attributed either despite pl0615 exporting 4 high-confidence attack_lunge
// melee banks (borg-action-assets.json). The chain/charge/sword-beam mechanics themselves are
// well-documented signature moves of this line; only the numeric tuning is invented.
const HERO_CHARGE_IDS = new Set(["pl0615", "pl0629", "pl062a"]);

function abs(relPath) {
  return path.join(repoRoot, relPath);
}

async function readJson(relPath) {
  return JSON.parse(await fs.readFile(abs(relPath), "utf8"));
}

function normalizeId(value) {
  return typeof value === "string" && /^pl[0-9a-f]{4}$/i.test(value) ? value.toLowerCase() : null;
}

function numberOr(value, fallback) {
  return Number.isFinite(value) ? value : fallback;
}

function hasFamily(families, name) {
  return families.includes(name);
}

function bestFrames(actionRecord, action, fallback) {
  const candidate = actionRecord?.actionCandidates?.[action]?.[0];
  return Math.max(1, Math.round(numberOr(candidate?.frames, fallback)));
}

function confidenceFor(families, primary, actionRecord) {
  if (primary === "shot" && (hasFamily(families, "gun") || hasFamily(families, "beam") || hasFamily(families, "fire"))) {
    return "medium";
  }
  if (primary === "melee" && hasFamily(families, "sword")) return "medium";
  if (actionRecord?.exportedAssets?.animIndex) return "low";
  return "fallback";
}

function choosePrimary(borg, families) {
  const shot = numberOr(borg.shot, 0);
  const attack = numberOr(borg.attack, 0);
  const text = `${borg.name ?? ""} ${borg.tribe ?? ""} ${borg.type ?? ""}`.toLowerCase();

  if (shot <= 0 && attack > 0) return "melee";
  if (attack <= 0 && shot > 0) return "shot";

  const rangedFamily =
    hasFamily(families, "gun") ||
    hasFamily(families, "beam") ||
    hasFamily(families, "fire") ||
    hasFamily(families, "muzzle") ||
    hasFamily(families, "bulletProjectile");
  const meleeFamily = hasFamily(families, "sword");

  if (rangedFamily && !meleeFamily) return "shot";
  if (meleeFamily && !rangedFamily) return "melee";
  if (/long range|gun|gunner|cannon|tank|dragon|satellite|bomber|beam/.test(text) && shot >= attack) return "shot";
  if (/short range|sword|knight|samurai|ninja|blade|melee/.test(text) && attack >= shot) return "melee";
  return shot > attack ? "shot" : "melee";
}

function visualKindFor(families) {
  if (hasFamily(families, "fire")) return "flame";
  if (hasFamily(families, "beam") || hasFamily(families, "trailAura")) return "energy";
  return "muzzle";
}

/** OBSERVED_WIKI move lookup, mirroring packages/combat/src/moveProperties.ts moveByButton:
 *  exact button-label match first, then label-prefix fallback (so "X" also reaches an
 *  "X Charge"-only borg). Returns null when the wiki harvest has no record for the borg. */
function wikiMoveByButton(moveProfile, buttonLabel) {
  const moves = moveProfile?.moves ?? [];
  const exact = moves.find((m) => (m.button ?? "") === buttonLabel);
  if (exact) return exact;
  const prefix = buttonLabel.toLowerCase();
  return moves.find((m) => (m.button ?? "").toLowerCase().startsWith(prefix)) ?? null;
}

/** TUNED-visual name heuristic: classify a wiki move NAME into a ProjectileVisualKind, falling
 *  back to the projectileVisualFamilies.json family kind, then the weapon-family kind. Only a
 *  presentation hint — no decoded per-move effect id exists (hit-bin-format.md). */
function visualKindForMoveName(name, familyKind, families) {
  const text = (name ?? "").toLowerCase();
  if (/beam|laser|plasma|buster|ray|spark|thunder|lightning|elec/.test(text)) return "energy";
  if (/flame|fire|breath|burn|heat/.test(text)) return "flame";
  if (/missile|bullet|shot|cannon|vulcan|gatling|gun|bazooka|arrow|shuriken|bomb|rocket/.test(text)) return "muzzle";
  if (familyKind === "energy" || familyKind === "flame" || familyKind === "muzzle") return familyKind;
  return visualKindFor(families);
}

/** Count distinct exported melee/sword animation banks (group:slot pairs) at the given
 *  confidence levels. Real asset evidence for "this borg has N different swings". */
function distinctMeleeBanks(actionRecord, confidences) {
  const candidates = actionRecord?.actionCandidates?.["melee/sword"] ?? [];
  const banks = new Set();
  for (const candidate of candidates) {
    if (!candidate?.exists) continue;
    if (!confidences.includes(candidate.confidence)) continue;
    banks.add(`${candidate.group}:${candidate.slot}`);
  }
  return banks.size;
}

/** Melee combo length derived from how many distinct swing banks the borg actually exports.
 *  High-confidence banks (labeled attack_lunge etc.) are trusted directly; medium-confidence
 *  generic attack_s# banks need a larger count before we grant a chain. Values are capped at 3
 *  (classic s1/s2/s3 lunge chains, e.g. pl0615 G RED). The bank COUNT is real asset evidence;
 *  the hit-chain semantics remain TUNED (hit-bin move records are still undecoded). */
function comboHitsFor(actionRecord) {
  const high = distinctMeleeBanks(actionRecord, ["high"]);
  const broad = distinctMeleeBanks(actionRecord, ["high", "medium"]);
  if (high >= 3) return 3;
  if (high === 2) return 2;
  if (broad >= 6) return 3;
  if (broad >= 3) return 2;
  return 1;
}

/** Sword-beam finisher (TUNED design choice): the LAST hit of a melee combo chain emits a fast,
 *  short-lived projectile with melee-scaled damage. Granted to sword-family melee-primary borgs
 *  and the G Red hero line (whose sword beam is the line's signature move — see HERO_CHARGE_IDS
 *  note). "Combo finisher" was picked over "full-HP melee" as the trigger because it is always
 *  reachable and testable; no ROM evidence distinguishes the two. */
function swordBeamDef(borg, families, primary) {
  const id = normalizeId(borg.id);
  const hero = id !== null && HERO_CHARGE_IDS.has(id);
  const sword = hasFamily(families, "sword");
  if (!hero && !(sword && primary === "melee")) return null;
  return {
    speed: 30,
    lifetime: hero ? 30 : 24,
    hitRadius: 30,
    damageMultiplier: hero ? 1.0 : 0.85,
    homingTurn: 0.02,
    visualKind: "energy",
  };
}

function meleeDef(borg, families, actionRecord, primary) {
  const attack = numberOr(borg.attack, 0);
  if (attack <= 0) return null;

  const clipFrames = bestFrames(actionRecord, "melee/sword", 18);
  const sword = hasFamily(families, "sword");
  const heavy = attack >= 8 || numberOr(borg.energy, 0) >= 900;
  const quick = numberOr(borg.speed, 0) >= 7;
  const startup = quick ? 3 : heavy ? 7 : sword ? 5 : 4;
  const active = heavy ? 9 : sword ? 8 : 6;
  const duration = Math.max(startup + active + 4, Math.min(42, Math.round(clipFrames * 0.62)));

  return {
    startup,
    active,
    duration,
    cooldown: heavy ? 18 : quick ? 8 : sword ? 12 : 10,
    range: heavy ? 78 : sword ? 86 : 64,
    yTolerance: heavy ? 64 : 50,
    damageMultiplier: heavy ? 1.3 : sword ? 1.15 : 1,
    knockbackMultiplier: heavy ? 1.35 : sword ? 1.15 : 1,
    comboHits: comboHitsFor(actionRecord),
    comboWindowFrames: quick ? 26 : 22,
    swordBeam: swordBeamDef(borg, families, primary),
  };
}

function shotDef(borg, families, actionRecord, bChargeMove, familyKind, bMove) {
  const shot = numberOr(borg.shot, 0);
  if (shot <= 0) return null;

  const clipFrames = bestFrames(actionRecord, "shoot/gun", 20);
  const text = `${borg.name ?? ""} ${borg.tribe ?? ""} ${borg.type ?? ""}`.toLowerCase();
  const beam = hasFamily(families, "beam");
  const flame = hasFamily(families, "fire");
  const gun = hasFamily(families, "gun") || hasFamily(families, "muzzle");
  const heavy = /cannon|tank|icbm|missile|bomb|launcher/.test(text) || shot >= 9;
  const rapid = /gatling|machine|revolver|gunner|gunman/.test(text) && !heavy;

  const baseCooldown = heavy ? 34 : rapid ? 8 : beam ? 16 : flame ? 20 : gun ? 12 : 14;
  const recovery = Math.max(8, Math.min(34, Math.round(clipFrames * (heavy ? 0.58 : 0.42))));
  const visualKind = visualKindFor(families);
  // Charge attack (hold B, release to fire a scaled shot). WHO charges is the union of:
  //   1. OBSERVED_WIKI: the borg has a cataloged "B Charge" move in borgMoveProperties.json
  //      (wiki harvest, behavior-notes (aw)) — the broadest positive evidence available.
  //   2. TUNED family heuristic (beam || heavy): KEPT even where the wiki lists no "B Charge"
  //      move. The wiki harvest covers only 164 of 208 roster borgs and omissions are not
  //      evidence of absence; dropping the heuristic would regress 17 already-working
  //      chargeable shooters (e.g. pl0104 BEAM GUNNER, pl0c00 cannon-class) and the selfcheck
  //      anchors that exercise them. Do NOT narrow this union without re-running selfcheck.
  //   3. HERO_CHARGE_IDS special case (see note above; pl0615 G RED must stay chargeable —
  //      selfcheck assertChargeShotTiers anchor).
  // No ROM per-move charge table is decoded; ALL numeric charge tuning below stays TUNED.
  const id = normalizeId(borg.id);
  const chargeable = beam || heavy || (id !== null && HERO_CHARGE_IDS.has(id)) || bChargeMove !== null;
  // Charged-release visual family (TUNED-visual): tier>=1 releases read as energy beams for
  // Laser/Beam-named "B Charge" moves (e.g. G Buster), flame for breath weapons, etc. Sourced
  // from the OBSERVED_WIKI move name with projectileVisualFamilies.json as fallback; the hero
  // line is forced to energy so pl062a G BLACK (no wiki record) matches its siblings' G Buster
  // beam (HERO_CHARGE_IDS note). Data-only this wave — combat.ts does not consume it yet.
  const hero = id !== null && HERO_CHARGE_IDS.has(id);
  const chargedVisualKind = !chargeable ? null : hero ? "energy" : visualKindForMoveName(bChargeMove?.name, familyKind, families);
  // Bullet drop only for ballistic "bullet" kinds (muzzle visuals): beams/flames fly straight.
  // TUNED magnitude; the muzzle/bulletProjectile family evidence only selects WHO drops.
  const ballistic = visualKind === "muzzle";

  return {
    cooldown: baseCooldown,
    recovery,
    ammoMax: heavy ? 2 : rapid ? 10 : beam ? 4 : 6,
    reloadFrames: heavy ? 86 : rapid ? 70 : 60,
    projectileCount: rapid ? 2 : 1,
    spreadRadians: rapid ? 0.055 : heavy ? 0.025 : 0,
    speed: heavy ? 18 : beam ? 30 : flame ? 18 : gun ? 28 : 22,
    lifetime: heavy ? 54 : beam ? 46 : flame ? 44 : 40,
    // Homing: ZERO for standard B-shots (playtest-confirmed + source-shaped: the ROM aims at
    // the locked target AT FIRE TIME — full 3D muzzle->target direction — and the bullet
    // flies STRAIGHT; the steer mechanism FUN_8006c1c8 exists but only specific weapons use
    // it, and universal per-family homing was a TUNED guess that read wrong in play).
    // In-flight homing survives only where the OBSERVED_WIKI B-move NAME evidences a homing
    // weapon (missile/homing/seeker), at a single TUNED rate.
    homingTurn: /missile|homing|seeker/i.test(bMove?.name ?? "") ? 0.05 : 0,
    hitRadius: heavy ? 58 : flame ? 46 : beam ? 34 : 35,
    // Per-family muzzle origin (TUNED): replaces the old flat 30/20. No decoded per-borg muzzle
    // node exists in the asset inventories (weapon-attachment-map only lists archive-level
    // families), so these stay family-scale offsets, not per-model attachment points.
    muzzleForwardOffset: heavy ? 46 : flame ? 40 : beam ? 38 : gun ? 34 : 30,
    muzzleYOffset: heavy ? 28 : beam ? 24 : 20,
    damageMultiplier: heavy ? 1.75 : beam ? 1.15 : flame ? 1.2 : rapid ? 0.72 : 1,
    hitstunMultiplier: heavy ? 1.45 : 1,
    knockbackMultiplier: heavy ? 1.65 : beam ? 0.9 : rapid ? 0.8 : 1,
    visualKind,
    chargeable,
    chargeTier1Frames: 30,
    chargeTier2Frames: 90,
    chargeTier1DamageMult: 1.6,
    chargeTier2DamageMult: heavy ? 2.6 : 2.4,
    bulletDrop: ballistic ? (heavy ? 0.12 : 0.045) : 0,
    ...(chargedVisualKind !== null ? { chargedVisualKind } : {}),
  };
}

// TUNED name heuristic for the X-special "projectile" archetype: wiki X move names that read
// as fired attacks (beams/missiles/thrown weapons/breath). Explosive X moves (explodes: true,
// e.g. pl0300 Missile Launcher) qualify regardless of name. The wiki flair field is null for
// 143/146 X moves, so the NAME is the only usable OBSERVED_WIKI signal; the classification
// itself is TUNED, only the move's existence/name/explodes flag is OBSERVED_WIKI.
const SPECIAL_PROJECTILE_NAME_RE =
  /beam|laser|plasma|buster|ray|shot|missile|cannon|gun|vulcan|gatling|bazooka|arrow|shuriken|bullet|rocket|breath|bomb|launcher|needle|feather|blast/i;

function specialDef(borg, families, primary, xMove, familyKind) {
  const attack = numberOr(borg.attack, 0);
  const shot = numberOr(borg.shot, 0);
  const beam = hasFamily(families, "beam");
  const flame = hasFamily(families, "fire");
  const sword = hasFamily(families, "sword");
  const heavy = numberOr(borg.energy, 0) >= 900 || shot >= 9 || attack >= 9;

  // X-special archetype groundwork (wave 1, data-only): "projectile" flags borgs whose
  // OBSERVED_WIKI X move is a fired attack; everything else stays the existing generic radial
  // "aoe" burst (combat.ts behavior is unchanged this wave — the archetype defaults to "aoe"
  // when absent). The G Red hero line's G Crash is a signature fired special (see
  // HERO_CHARGE_IDS note) but its wiki name/flair carries no ranged keyword, so the hero ids
  // are special-cased exactly like the charge shot. All projectile params below are TUNED.
  const id = normalizeId(borg.id);
  const hero = id !== null && HERO_CHARGE_IDS.has(id);
  const projectile = xMove !== null && (xMove.explodes === true || SPECIAL_PROJECTILE_NAME_RE.test(xMove.name ?? "") || hero);

  return {
    cooldown: heavy ? 120 : 90,
    duration: heavy ? 34 : 26,
    radius: flame ? 150 : beam ? 128 : sword || primary === "melee" ? 96 : 112,
    damageMultiplier: heavy ? 2.35 : flame ? 2.15 : beam ? 2.05 : 2,
    knockbackMultiplier: heavy ? 1.35 : 1,
    ...(xMove !== null
      ? {
          archetype: projectile ? "projectile" : "aoe",
          // OBSERVED_WIKI move name — presentation hook only, never a gameplay input.
          moveName: xMove.name,
        }
      : {}),
    ...(projectile
      ? {
          projectileSpeed: heavy ? 20 : beam ? 28 : 24,
          projectileHitRadius: heavy ? 52 : 38,
          projectileCount: /double|twin/i.test(xMove.name ?? "") ? 2 : 1,
          // Hero line forced to energy (TUNED-visual): G Crash carries no ranged keyword and
          // the line's asset families are Low-confidence muzzle only (HERO_CHARGE_IDS note),
          // but the signature special reads as an energy attack like its charge/sword beams.
          projectileVisualKind: hero ? "energy" : visualKindForMoveName(xMove.name, familyKind, families),
        }
      : {}),
  };
}

async function main() {
  const [borgsJson, weaponMap, actionAssets, movePropsJson, visualFamiliesJson] = await Promise.all([
    readJson(paths.borgs),
    readJson(paths.weaponMap),
    readJson(paths.actionAssets),
    readJson(paths.moveProps),
    readJson(paths.visualFamilies),
  ]);

  const weaponById = new Map((weaponMap.borgs ?? []).map((borg) => [normalizeId(borg.id), borg]).filter(([id]) => id));
  const actionById = new Map((actionAssets.records ?? []).map((record) => [normalizeId(record.id), record]).filter(([id]) => id));
  const moveProfilesById = movePropsJson.borgs ?? {};
  const familyKindById = visualFamiliesJson.kinds ?? {};
  const profiles = {};

  for (const borg of borgsJson.borgs ?? []) {
    const id = normalizeId(borg.id);
    if (!id) continue;
    const weaponRecord = weaponById.get(id);
    const actionRecord = actionById.get(id);
    const moveProfile = moveProfilesById[id] ?? null;
    const familyKind = familyKindById[id] ?? null;
    const bChargeMove = wikiMoveByButton(moveProfile, "B Charge");
    // EXACT "B" button match only (no prefix fallback — that would match "B Charge" too):
    // the homing-evidence test reads the plain B-shot's wiki name.
    const bMove = (moveProfile?.moves ?? []).find((m) => (m.button ?? "") === "B") ?? null;
    const xMove = wikiMoveByButton(moveProfile, "X");
    const families = Object.keys(weaponRecord?.families ?? {}).sort();
    const primary = choosePrimary(borg, families);
    const melee = meleeDef(borg, families, actionRecord, primary);
    const shot = shotDef(borg, families, actionRecord, bChargeMove, familyKind, bMove);
    const special = specialDef(borg, families, primary, xMove, familyKind);

    const noteParts = [
      "TUNED asset-backed profile: primary attack family comes from weapon/effect/animation asset inventories, not decoded hit-bin move semantics.",
    ];
    if (shot?.chargeable) {
      noteParts.push(
        bChargeMove !== null
          ? `Chargeable per OBSERVED_WIKI "B Charge" move ${JSON.stringify(bChargeMove.name)} (borgMoveProperties.json wiki harvest; numeric charge tuning TUNED).`
          : "Chargeable per TUNED beam/heavy family heuristic (or hero-line special case); the wiki harvest lists no B Charge move for this borg.",
      );
    }
    if (special.archetype !== undefined) {
      noteParts.push(
        `Special archetype "${special.archetype}" classified from OBSERVED_WIKI X move ${JSON.stringify(special.moveName)} (borgMoveProperties.json; classification heuristic and all projectile params TUNED).`,
      );
    }

    profiles[id] = {
      primary,
      confidence: confidenceFor(families, primary, actionRecord),
      families,
      evidence: {
        weaponAttachmentMap: weaponRecord ? "research/asset-inventory/weapon-attachment-map.json" : null,
        actionAssetInventory: actionRecord ? "research/animation-actions/borg-action-assets.json" : null,
        exportedAnimIndex: actionRecord?.exportedAssets?.animIndex?.path ?? null,
        moveProperties: moveProfile ? paths.moveProps : null,
        projectileVisualFamilies: familyKind !== null ? paths.visualFamilies : null,
        note: noteParts.join(" "),
      },
      melee,
      shot,
      special,
    };
  }

  const output = {
    schema,
    generatedBy: "scripts/gen-combat-action-profiles.mjs",
    generatedFrom: [paths.borgs, paths.weaponMap, paths.actionAssets, paths.moveProps, paths.visualFamilies],
    note:
      "TUNED, not DERIVED: per-borg attack primary/timing/projectile traits are generated from weapon-attachment and animation asset evidence. Hit-bin move records remain structurally parsed but semantically undecoded, so combat.ts keeps a generic fallback for missing profile fields. Combo chain length (melee.comboHits) counts real exported swing banks; charge shots (shot.chargeable) are the UNION of the OBSERVED_WIKI 'B Charge' move catalog (borgMoveProperties.json) with the retained TUNED beam/heavy family heuristic + the G Red hero line; shot.chargedVisualKind and the special.archetype/'projectile' params are TUNED-visual groundwork keyed off OBSERVED_WIKI move names + projectileVisualFamilies.json (data-only until the runtime waves consume them); sword-beam finishers (melee.swordBeam) key off sword-family melee-primary borgs + the hero line. All numeric values for those mechanics are TUNED.",
    count: Object.keys(profiles).length,
    profiles,
  };

  await fs.mkdir(path.dirname(abs(paths.output)), { recursive: true });
  await fs.writeFile(abs(paths.output), `${JSON.stringify(output, null, 2)}\n`);
  console.log(`wrote ${paths.output}`);
  console.log(`profiles: ${output.count}`);
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
