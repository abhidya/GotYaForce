#!/usr/bin/env node
import { promises as fs } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

const paths = {
  borgs: "packages/assets/data/borgs.json",
  weaponMap: "research/asset-inventory/weapon-attachment-map.json",
  actionAssets: "research/animation-actions/borg-action-assets.json",
  output: "packages/combat/src/data/actionProfiles.json",
};

const schema = "combat-action-profiles.v1";

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

function meleeDef(borg, families, actionRecord) {
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
  };
}

function shotDef(borg, families, actionRecord) {
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

  return {
    cooldown: baseCooldown,
    recovery,
    ammoMax: heavy ? 2 : rapid ? 10 : beam ? 4 : 6,
    reloadFrames: heavy ? 86 : rapid ? 70 : 60,
    projectileCount: rapid ? 2 : 1,
    spreadRadians: rapid ? 0.055 : heavy ? 0.025 : 0,
    speed: heavy ? 18 : beam ? 30 : flame ? 18 : gun ? 28 : 22,
    lifetime: heavy ? 54 : beam ? 46 : flame ? 44 : 40,
    homingTurn: beam ? 0.045 : flame ? 0.03 : heavy ? 0.02 : 0.08,
    hitRadius: heavy ? 58 : flame ? 46 : beam ? 34 : 35,
    muzzleForwardOffset: heavy ? 46 : 30,
    muzzleYOffset: heavy ? 28 : 20,
    damageMultiplier: heavy ? 1.75 : beam ? 1.15 : flame ? 1.2 : rapid ? 0.72 : 1,
    hitstunMultiplier: heavy ? 1.45 : 1,
    knockbackMultiplier: heavy ? 1.65 : beam ? 0.9 : rapid ? 0.8 : 1,
    visualKind: visualKindFor(families),
  };
}

function specialDef(borg, families, primary) {
  const attack = numberOr(borg.attack, 0);
  const shot = numberOr(borg.shot, 0);
  const beam = hasFamily(families, "beam");
  const flame = hasFamily(families, "fire");
  const sword = hasFamily(families, "sword");
  const heavy = numberOr(borg.energy, 0) >= 900 || shot >= 9 || attack >= 9;

  return {
    cooldown: heavy ? 120 : 90,
    duration: heavy ? 34 : 26,
    radius: flame ? 150 : beam ? 128 : sword || primary === "melee" ? 96 : 112,
    damageMultiplier: heavy ? 2.35 : flame ? 2.15 : beam ? 2.05 : 2,
    knockbackMultiplier: heavy ? 1.35 : 1,
  };
}

async function main() {
  const [borgsJson, weaponMap, actionAssets] = await Promise.all([
    readJson(paths.borgs),
    readJson(paths.weaponMap),
    readJson(paths.actionAssets),
  ]);

  const weaponById = new Map((weaponMap.borgs ?? []).map((borg) => [normalizeId(borg.id), borg]).filter(([id]) => id));
  const actionById = new Map((actionAssets.records ?? []).map((record) => [normalizeId(record.id), record]).filter(([id]) => id));
  const profiles = {};

  for (const borg of borgsJson.borgs ?? []) {
    const id = normalizeId(borg.id);
    if (!id) continue;
    const weaponRecord = weaponById.get(id);
    const actionRecord = actionById.get(id);
    const families = Object.keys(weaponRecord?.families ?? {}).sort();
    const primary = choosePrimary(borg, families);
    const melee = meleeDef(borg, families, actionRecord);
    const shot = shotDef(borg, families, actionRecord);

    profiles[id] = {
      primary,
      confidence: confidenceFor(families, primary, actionRecord),
      families,
      evidence: {
        weaponAttachmentMap: weaponRecord ? "research/asset-inventory/weapon-attachment-map.json" : null,
        actionAssetInventory: actionRecord ? "research/animation-actions/borg-action-assets.json" : null,
        exportedAnimIndex: actionRecord?.exportedAssets?.animIndex?.path ?? null,
        note:
          "TUNED asset-backed profile: primary attack family comes from weapon/effect/animation asset inventories, not decoded hit-bin move semantics.",
      },
      melee,
      shot,
      special: specialDef(borg, families, primary),
    };
  }

  const output = {
    schema,
    generatedBy: "scripts/gen-combat-action-profiles.mjs",
    generatedFrom: [paths.borgs, paths.weaponMap, paths.actionAssets],
    note:
      "TUNED, not DERIVED: per-borg attack primary/timing/projectile traits are generated from weapon-attachment and animation asset evidence. Hit-bin move records remain structurally parsed but semantically undecoded, so combat.ts keeps a generic fallback for missing profile fields.",
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
