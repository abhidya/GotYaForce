#!/usr/bin/env node

import { promises as fs } from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

const paths = {
  weaponAttachmentMap: "research/asset-inventory/weapon-attachment-map.json",
  weaponsEffectsProjectiles: "research/asset-inventory/weapons-effects-projectiles.json",
  particleEffectInventory: "research/asset-inventory/particle-effect-inventory.json",
  borgAssets: "research/asset-inventory/borg-assets.json",
  hitBinInventory: "research/asset-inventory/hit-bin-inventory.json",
  uiHudInventory: "research/asset-inventory/ui-hud-assets.json",
  borgData: "packages/assets/data/borgs.json",
  modelManifest: "apps/game/public/models/library/manifest.json",
  publicFxManifest: "apps/game/public/fx/manifest.json",
  audioManifest: "apps/game/public/audio/manifest.json",
  publicModelRoot: "apps/game/public/models",
  afsRoot: "user-data/GG4E/afs_data/root",
  outputDir: "research/combat-assets",
  outputJson: "research/combat-assets/combat-asset-inventory.json",
  outputMarkdown: "research/combat-assets/combat-asset-inventory.md",
};

const priorityBorgIds = ["pl0615", "pl0109"];

const actions = [
  {
    id: "gunShooting",
    label: "gun shooting",
    families: ["gun", "bulletProjectile", "muzzle"],
    animationLabels: ["attack", "special"],
    sharedFamilies: ["gun", "muzzle"],
    fxTerms: ["muzzle", "flash", "spark", "energy", "dot"],
    sourceNote: "Ranged projectile/gun candidates only; no runtime shot spawn frame is asserted.",
  },
  {
    id: "beamShooting",
    label: "beam shooting",
    families: ["beam", "muzzle", "trailAura"],
    animationLabels: ["attack", "special"],
    sharedFamilies: ["beam", "trail"],
    fxTerms: ["energy", "glow", "aura", "muzzle"],
    sourceNote: "Beam/laser candidates only; beam length, tick rate, and collision are still runtime-trace gaps.",
  },
  {
    id: "swordMelee",
    label: "sword/melee",
    families: ["sword"],
    animationLabels: ["attack_lunge", "attack"],
    sharedFamilies: ["sword"],
    fxTerms: ["spark", "hit"],
    sourceNote: "Melee/action animation and attachment leads only; no fake slash volumes are invented.",
  },
  {
    id: "lockOnTargetReticle",
    label: "lock-on target reticle",
    families: ["reticle"],
    animationLabels: [],
    sharedFamilies: ["reticle"],
    fxTerms: [],
    sourceNote: "Targeting UI candidates come from UI/HUD and filename inventories, not combat behavior code.",
  },
  {
    id: "hits",
    label: "hits",
    families: ["impact"],
    animationLabels: ["hit_react", "guard"],
    sharedFamilies: ["impact"],
    fxTerms: ["hit", "spark", "smoke"],
    sourceNote: "Hit BINs and hit-react animations are structural leads; damage semantics need schema/runtime work.",
  },
  {
    id: "deathExplosion",
    label: "death/explosion",
    families: ["impact", "fire", "trailAura"],
    animationLabels: ["death", "win_or_death", "down"],
    sharedFamilies: ["impact", "fire", "trail"],
    fxTerms: ["flame", "explosion", "smoke", "aura", "atlas"],
    sourceNote: "Death animation plus shared explosion/fire particles; no per-Borg death effect id is confirmed.",
  },
];

const confidenceRank = { High: 3, Medium: 2, Low: 1, Unknown: 0 };

function abs(relPath) {
  return path.join(repoRoot, relPath);
}

function rel(absPath) {
  return path.relative(repoRoot, absPath).replaceAll(path.sep, "/");
}

async function readJson(relPath) {
  return JSON.parse(await fs.readFile(abs(relPath), "utf8"));
}

async function readJsonIfExists(relPath, fallback) {
  try {
    return await readJson(relPath);
  } catch (error) {
    if (error.code === "ENOENT") return fallback;
    throw error;
  }
}

async function exists(relPath) {
  try {
    await fs.access(abs(relPath));
    return true;
  } catch {
    return false;
  }
}

function unique(values) {
  return [...new Set(values.filter((value) => value != null && value !== ""))];
}

function compareConfidence(a, b) {
  return (confidenceRank[b.confidence ?? "Unknown"] ?? 0) - (confidenceRank[a.confidence ?? "Unknown"] ?? 0);
}

function strongestConfidence(items) {
  return items.reduce((best, item) => {
    const current = item.confidence ?? "Unknown";
    return (confidenceRank[current] ?? 0) > (confidenceRank[best] ?? 0) ? current : best;
  }, "Unknown");
}

function normalizeFamilies(families) {
  const out = new Set();
  for (const family of families ?? []) {
    const text =
      typeof family === "string"
        ? family.toLowerCase()
        : String(family.family ?? family.id ?? family.label ?? "").toLowerCase();
    if (text.includes("sword") || text.includes("blade")) out.add("sword");
    if (text.includes("fire") || text.includes("flame")) out.add("fire");
    if (text.includes("gun")) out.add("gun");
    if (text.includes("bullet") || text.includes("projectile") || text.includes("arrow")) out.add("bulletProjectile");
    if (text.includes("beam") || text.includes("laser")) out.add("beam");
    if (text.includes("muzzle")) out.add("muzzle");
    if (text.includes("impact") || text.includes("explosion") || text.includes("hit")) out.add("impact");
    if (text.includes("trail") || text.includes("aura")) out.add("trailAura");
    if (text.includes("reticle") || text.includes("target") || text.includes("lock")) out.add("reticle");
  }
  return [...out];
}

function compactAsset(asset, source = null) {
  if (!asset) return null;
  return {
    path: asset.path,
    name: asset.name ?? path.basename(String(asset.path ?? "")),
    role: asset.role ?? asset.fileType?.role ?? asset.extension ?? asset.fileType?.extension ?? "asset",
    sizeBytes: asset.sizeBytes ?? asset.bytes ?? null,
    confidence: asset.confidence ?? "Unknown",
    families: normalizeFamilies(asset.families ?? asset.familyKeys ?? []),
    source: source ?? asset.source ?? null,
    reason: asset.reason ?? asset.attachmentLead ?? null,
    blocker: asset.blocker ?? null,
    needs: unique(asset.needs ?? []),
  };
}

function animationActionCues(animIndex, action) {
  const rows = [];
  for (const bank of animIndex?.banks ?? []) {
    const label = String(bank.label ?? "");
    if (!action.animationLabels.some((term) => label.includes(term))) continue;
    rows.push({
      file: `${paths.publicModelRoot}/${animIndex.borg}/${bank.file}`,
      group: bank.group,
      slot: bank.slot,
      label,
      frames: bank.frames,
      animJoints: bank.animJoints,
      rootSpan: {
        x: bank.rootSpanX,
        y: bank.rootSpanY,
        z: bank.rootSpanZ,
      },
      confidence: label.includes("death") || label.includes("hit") || label.includes("attack") ? "High" : "Medium",
      note: "exported original MOT clip label; action timing/spawn frame still needs trace",
    });
  }
  return rows.sort((a, b) => a.group - b.group || a.slot - b.slot);
}

function assetsForFamilies(assets, families, limit = 12) {
  return assets
    .filter((asset) => asset.families?.some((family) => families.includes(family)))
    .sort((a, b) => compareConfidence(a, b) || (b.sizeBytes ?? 0) - (a.sizeBytes ?? 0) || a.path.localeCompare(b.path))
    .slice(0, limit);
}

function publicFxCandidates(publicFxManifest, action) {
  return (publicFxManifest.images ?? [])
    .filter((image) => {
      const text = `${image.file} ${image.guessLabel ?? ""}`.toLowerCase();
      return action.fxTerms.some((term) => text.includes(term));
    })
    .map((image) => ({
      path: `apps/game/public/fx/${image.file}`,
      source: image.source,
      dimensions: `${image.w}x${image.h}`,
      format: image.format,
      blend: image.blend,
      labelFromExtractor: image.guessLabel,
      confidence: "Medium",
      caveat: "browser-ready export from original ptcl00/efct texture data; label is visual/extractor guess, not a runtime effect id",
    }));
}

function audioCandidates(audioManifest, action) {
  const sfx = (audioManifest.files ?? [])
    .filter((entry) => entry.type === "sfx")
    .map((entry) => ({
      key: entry.key,
      path: `apps/game/public/${entry.path}`,
      durationSec: entry.durationSec,
      confidence: "Low",
      caveat: "exported SFX sample exists, but shot/hit/death semantic mapping is not identified",
    }));

  if (["gunShooting", "beamShooting", "swordMelee", "hits", "deathExplosion"].includes(action.id)) {
    return sfx;
  }
  return [];
}

function voiceCandidatesForBorg(audioManifest, borgId) {
  const groupKey = `pl${borgId.slice(2, 4)}`;
  return (audioManifest.files ?? [])
    .filter((entry) => entry.type === "voice" && entry.key.startsWith(`${groupKey}_`))
    .map((entry) => ({
      key: entry.key,
      path: `apps/game/public/${entry.path}`,
      durationSec: entry.durationSec,
      confidence: "Low",
      caveat: `${groupKey} voice group is exported, but it is not confirmed as an exact ${borgId} action cue`,
    }));
}

async function readAnimIndex(id) {
  return readJsonIfExists(`${paths.publicModelRoot}/${id}/anim_index.json`, { borg: id, banks: [] });
}

function sourceFilesForBorg(borgAssetRecord) {
  const files = borgAssetRecord?.sourceFiles ?? {};
  return {
    archives: files.archives ?? [],
    modelArcs: files.modelArcs ?? [],
    motBins: files.motBins ?? [],
    dataBins: files.dataBins ?? [],
    hitBins: files.hitBins ?? [],
    other: files.other ?? [],
  };
}

function makeModelExports(id, modelManifest) {
  const manifestEntry = (modelManifest ?? []).find((entry) => String(entry.id).toLowerCase() === id);
  const exports = [];
  if (manifestEntry?.dae) {
    exports.push({
      path: `apps/game/public/models/library/${id}/${manifestEntry.dae}`,
      role: "browser-ready DAE model export",
      confidence: "High",
      meshes: manifestEntry.meshes ?? null,
      bones: manifestEntry.bones ?? null,
      tris: manifestEntry.tris ?? null,
    });
  }
  return exports;
}

function makeActionRecord({ action, borg, animIndex, borgAssets, sharedAssets, publicFxManifest, audioManifest }) {
  const borgAssetsForAction = assetsForFamilies(borg.assetEvidence ?? [], action.families, 16);
  const sharedForAction = assetsForFamilies(sharedAssets, action.sharedFamilies, 12);
  const animationCues = animationActionCues(animIndex, action);
  const modelCandidates = (borg.itemAttachmentCandidates ?? [])
    .map((item) => ({
      path: item.path,
      role: "compressed item/attachment model archive",
      confidence: item.confidence ?? "Unknown",
      families: item.families ?? [],
      blocker: item.blocker,
      caveat: "ARZ decompression required before using as weapon/projectile model",
    }))
    .filter((item) => {
    if (action.id === "swordMelee") return item.families?.includes?.("sword") || item.role.includes("DAE");
    if (["gunShooting", "beamShooting"].includes(action.id)) {
      return item.families?.some?.((family) => action.families.includes(family)) || item.role.includes("DAE");
    }
    return false;
  });

  const dataCandidates = [];
  if (["gunShooting", "beamShooting", "swordMelee"].includes(action.id)) {
    dataCandidates.push(
      ...(borg.dataBinInspection ?? []).map((entry) => ({
        path: entry.path,
        role: "raw pl####data.bin action/weapon table candidate",
        bytes: entry.bytes,
        sha1: entry.sha1,
        parseStatus: entry.parseStatus,
        confidence: "Low",
      })),
    );
  }
  if (["hits", "deathExplosion", "swordMelee"].includes(action.id) && borg.hitBinInspection) {
    dataCandidates.push({
      path: borg.hitBinInspection.path,
      role: "per-Borg hit/collision data",
      valid: borg.hitBinInspection.valid,
      category: borg.hitBinInspection.category,
      parseStatus: borg.hitBinInspection.parseStatus,
      confidence: action.id === "hits" ? "High" : "Medium",
    });
  }

  const candidates = {
    animations: animationCues,
    borgAssets: borgAssetsForAction,
    sharedAssets: sharedForAction,
    models: modelCandidates,
    browserReadyFxTextures: publicFxCandidates(publicFxManifest, action),
    audio: audioCandidates(audioManifest, action),
    data: dataCandidates,
  };

  const actionSpecific = [...candidates.borgAssets, ...candidates.models, ...candidates.data];
  let confidence = strongestConfidence(actionSpecific);
  if (confidence === "Unknown" && animationCues.length > 0) confidence = "Medium";
  if (action.id === "lockOnTargetReticle") confidence = "Unknown";

  return {
    action: action.id,
    label: action.label,
    confidence,
    sourceNote: action.sourceNote,
    candidates,
    gaps: unique([
      animationCues.length > 0 ? "MOT clip exists, but spawn frame/event table is not mapped." : "No exported MOT clip was labelled for this action.",
      ["gunShooting", "beamShooting"].includes(action.id) ? "Projectile/beam entity id and lifetime/path need runtime trace." : null,
      action.id === "swordMelee" ? "Melee hit volume and active frames need hit-bin/runtime correlation." : null,
      action.id === "lockOnTargetReticle" ? "Lock-on state/reticle layout data is not decoded from UI/HUD bins." : null,
      ["hits", "deathExplosion"].includes(action.id) ? "Hit/death effect id and exact particle/PTL record are not mapped." : null,
      candidates.audio.length > 0 ? "Audio cue semantics are not mapped; listed audio is exported source material only." : null,
    ]),
  };
}

function makeSharedActionRecord({ action, weaponMap, weaponsInventory, particleInventory, uiHudInventory, publicFxManifest, audioManifest }) {
  const sharedAssets = assetsForFamilies(weaponMap.sharedAssets ?? [], action.sharedFamilies, 20);
  const sourceFamilyAssets = [];
  for (const [family, entries] of Object.entries(weaponsInventory.families ?? {})) {
    const normalized = normalizeFamilies([family]);
    if (!normalized.some((item) => action.sharedFamilies.includes(item))) continue;
    sourceFamilyAssets.push(...entries.slice(0, 20).map((entry) => compactAsset(entry, "weapons-effects-projectiles")));
  }

  const particleAssets = (particleInventory.assets ?? [])
    .map((asset) => compactAsset(asset, "particle-effect-inventory"))
    .filter((asset) => asset.families.some((family) => action.sharedFamilies.includes(family)))
    .slice(0, 20);

  const uiCandidates = [];
  if (action.id === "lockOnTargetReticle") {
    const fromCategories = (uiHudInventory.categories ?? [])
      .filter((category) => category.id === "battle-hud" || category.intent?.toLowerCase().includes("target"))
      .flatMap((category) => category.samples ?? [])
      .filter((name) => /arrow|icon|target|as_icon|battle/i.test(name))
      .map((name) => ({
        path: `${paths.afsRoot}/${name}`,
        role: "battle HUD / targeting source candidate",
        confidence: /arrow|icon/i.test(name) ? "Medium" : "Low",
        reason: "listed by UI/HUD inventory as battle HUD sample",
      }));
    uiCandidates.push(...fromCategories);
  }

  return {
    action: action.id,
    label: action.label,
    sourceNote: action.sourceNote,
    candidates: {
      sharedAssets: uniqueByPath([...sharedAssets, ...sourceFamilyAssets, ...particleAssets]).slice(0, 30),
      browserReadyFxTextures: publicFxCandidates(publicFxManifest, action),
      uiHud: uniqueByPath(uiCandidates).slice(0, 20),
      audio: audioCandidates(audioManifest, action),
    },
  };
}

function uniqueByPath(items) {
  const map = new Map();
  for (const item of items.filter(Boolean)) {
    const key = item.path ?? item.key ?? JSON.stringify(item);
    if (!map.has(key)) map.set(key, item);
  }
  return [...map.values()];
}

function makeBorgMarkdownRow(borg) {
  const actionSummary = borg.actions
    .map((action) => `${action.label}: ${action.confidence}`)
    .join("<br>");
  const topGaps = unique(borg.actions.flatMap((action) => action.gaps)).slice(0, 3).join("<br>");
  return `| ${borg.priority ? "**" : ""}\`${borg.id}\`${borg.priority ? "**" : ""} ${borg.name} | ${borg.tribe} | ${actionSummary} | ${topGaps} |`;
}

function makeMarkdown(report) {
  const lines = [];
  lines.push("# Combat Asset/Effect Inventory");
  lines.push("");
  lines.push(`Generated: ${report.generatedAt}`);
  lines.push("");
  lines.push("This is an inventory of original/exported asset evidence. It does not assign fake gameplay mechanics, shot timing, hitboxes, or effect IDs where the source data is still unmapped.");
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push(`- Borgs inventoried: ${report.summary.borgCount}`);
  lines.push(`- Priority Borgs: ${report.priorityBorgIds.map((id) => `\`${id}\``).join(", ")}`);
  lines.push(`- Actions mapped: ${actions.map((action) => action.label).join(", ")}`);
  lines.push(`- Shared/global combat leads: ${report.summary.sharedActionCount} action groups`);
  lines.push("");
  lines.push("## Priority Borgs");
  lines.push("");
  lines.push("| Borg | Tribe | Action evidence | Main gaps |");
  lines.push("|---|---|---|---|");
  for (const id of report.priorityBorgIds) {
    const borg = report.borgs.find((entry) => entry.id === id);
    if (borg) lines.push(makeBorgMarkdownRow(borg));
  }
  lines.push("");
  lines.push("## All Borg Action Coverage");
  lines.push("");
  lines.push("| Borg | Tribe | Action evidence | Main gaps |");
  lines.push("|---|---|---|---|");
  for (const borg of report.borgs.slice(0, 80)) lines.push(makeBorgMarkdownRow(borg));
  if (report.borgs.length > 80) lines.push(`| ... | ... | ... | ${report.borgs.length - 80} more Borgs in JSON |`);

  lines.push("");
  lines.push("## Shared Action Leads");
  for (const shared of report.sharedActions) {
    lines.push("");
    lines.push(`### ${shared.label}`);
    lines.push("");
    lines.push(shared.sourceNote);
    const assets = shared.candidates.sharedAssets ?? [];
    if (assets.length > 0) {
      lines.push("");
      lines.push("Top source assets:");
      for (const asset of assets.slice(0, 8)) {
        lines.push(`- \`${asset.path}\` (${asset.role ?? "asset"}, ${asset.confidence ?? "Unknown"})`);
      }
    }
    const fx = shared.candidates.browserReadyFxTextures ?? [];
    if (fx.length > 0) {
      lines.push("");
      lines.push("Browser-ready original texture exports:");
      for (const image of fx.slice(0, 8)) {
        lines.push(`- \`${image.path}\` from ${image.source}: ${image.labelFromExtractor}`);
      }
    }
    const ui = shared.candidates.uiHud ?? [];
    if (ui.length > 0) {
      lines.push("");
      lines.push("UI/HUD targeting candidates:");
      for (const asset of ui.slice(0, 8)) lines.push(`- \`${asset.path}\` (${asset.confidence})`);
    }
  }

  lines.push("");
  lines.push("## Known Gaps Before 1:1 Runtime Binding");
  lines.push("");
  for (const gap of report.globalGaps) lines.push(`- ${gap}`);
  lines.push("");
  return `${lines.join("\n").trimEnd()}\n`;
}

async function main() {
  const [
    weaponMap,
    weaponsInventory,
    particleInventory,
    borgAssetsInventory,
    hitInventory,
    uiHudInventory,
    borgData,
    modelManifest,
    publicFxManifest,
    audioManifest,
  ] = await Promise.all([
    readJson(paths.weaponAttachmentMap),
    readJson(paths.weaponsEffectsProjectiles),
    readJson(paths.particleEffectInventory),
    readJson(paths.borgAssets),
    readJson(paths.hitBinInventory),
    readJsonIfExists(paths.uiHudInventory, {}),
    readJson(paths.borgData),
    readJsonIfExists(paths.modelManifest, []),
    readJsonIfExists(paths.publicFxManifest, { images: [] }),
    readJsonIfExists(paths.audioManifest, { files: [] }),
  ]);

  const borgMeta = new Map((borgData.borgs ?? []).map((borg) => [String(borg.id).toLowerCase(), borg]));
  const borgAssetMap = new Map((borgAssetsInventory.records ?? []).map((record) => [String(record.id).toLowerCase(), record]));
  const weaponMapBorgs = new Map((weaponMap.borgs ?? []).map((borg) => [String(borg.id).toLowerCase(), borg]));
  const hitByBorg = new Map((hitInventory.files?.player ?? []).map((file) => [String(file.linkedBorgId).toLowerCase(), file]));

  const ids = unique([
    ...priorityBorgIds,
    ...(weaponMap.borgs ?? []).map((borg) => borg.id),
  ]).sort((a, b) => {
    const ap = priorityBorgIds.includes(a) ? priorityBorgIds.indexOf(a) : 99;
    const bp = priorityBorgIds.includes(b) ? priorityBorgIds.indexOf(b) : 99;
    return ap - bp || a.localeCompare(b);
  });

  const borgs = [];
  for (const id of ids) {
    const metadata = borgMeta.get(id);
    const mapped = weaponMapBorgs.get(id) ?? {};
    const sourceFiles = sourceFilesForBorg(borgAssetMap.get(id));
    const animIndex = await readAnimIndex(id);
    const hitFromInventory = hitByBorg.get(id);
    const borg = {
      id,
      priority: priorityBorgIds.includes(id),
      name: metadata?.name ?? mapped.name ?? id,
      number: metadata?.number ?? mapped.number ?? null,
      tribe: metadata?.tribe ?? mapped.tribe ?? "Unknown",
      type: metadata?.type ?? mapped.type ?? null,
      stats: mapped.stats ?? {
        hp: metadata?.hp ?? null,
        shot: metadata?.shot ?? null,
        attack: metadata?.attack ?? null,
      },
      sourceFiles,
      sourceAssetEvidenceCount: mapped.assetEvidence?.length ?? 0,
      modelExport: {
        publicDae: makeModelExports(id, modelManifest),
        attachmentBoneCandidates: mapped.attachmentBoneCandidates ?? [],
      },
      voiceCandidates: voiceCandidatesForBorg(audioManifest, id),
      assetEvidence: (mapped.assetEvidence ?? []).map((asset) => compactAsset(asset, asset.source)),
      itemAttachmentCandidates: mapped.itemAttachmentCandidates ?? [],
      dataBinInspection: mapped.dataBinInspection ?? [],
      hitBinInspection: mapped.hitBinInspection ?? (hitFromInventory ? { path: hitFromInventory.path, valid: hitFromInventory.valid } : null),
      actions: [],
    };

    borg.actions = actions.map((action) =>
      makeActionRecord({
        action,
        borg,
        animIndex,
        borgAssets: { modelManifest },
        sharedAssets: weaponMap.sharedAssets ?? [],
        publicFxManifest,
        audioManifest,
      }),
    );
    borgs.push(borg);
  }

  const sharedActions = actions.map((action) =>
    makeSharedActionRecord({
      action,
      weaponMap,
      weaponsInventory,
      particleInventory,
      uiHudInventory,
      publicFxManifest,
      audioManifest,
    }),
  );

  const report = {
    schema: "combat-asset-inventory.v1",
    generatedAt: new Date().toISOString(),
    generatedBy: rel(fileURLToPath(import.meta.url)),
    scope: "Research-only inventory of original/exported combat assets and gaps. Runtime files are intentionally untouched.",
    priorityBorgIds,
    inputs: paths,
    actions: actions.map(({ id, label, sourceNote }) => ({ id, label, sourceNote })),
    summary: {
      borgCount: borgs.length,
      priorityBorgCount: borgs.filter((borg) => borg.priority).length,
      sharedActionCount: sharedActions.length,
      publicFxImageCount: publicFxManifest.images?.length ?? 0,
      exportedSfxCount: (audioManifest.files ?? []).filter((entry) => entry.type === "sfx").length,
      borgsWithHitBin: borgs.filter((borg) => borg.hitBinInspection).length,
      borgsWithDataInspection: borgs.filter((borg) => borg.dataBinInspection.length > 0).length,
      borgsWithAttachmentCandidates: borgs.filter((borg) => borg.modelExport.attachmentBoneCandidates.length > 0).length,
    },
    globalGaps: [
      "MOT animation labels identify candidate actions, but source event tables/spawn frames are not mapped.",
      "Per-Borg data.bin and hit.bin are parsed structurally, not semantically enough to bind damage, active frames, sockets, or projectile ids.",
      "PZZ/ARZ decompression is still needed for efct.pzz members and it####_mdl.arz weapon/projectile models.",
      "PTL/REF/TXG particle records are not correlated to runtime effect IDs.",
      "Audio SFX samples are exported, but combat cue semantics are unresolved.",
      "Lock-on reticle/HUD candidates are source assets only; layout/control BINs are not decoded.",
    ],
    sharedActions,
    borgs,
  };

  await fs.mkdir(abs(paths.outputDir), { recursive: true });
  await fs.writeFile(abs(paths.outputJson), `${JSON.stringify(report, null, 2)}\n`);
  await fs.writeFile(abs(paths.outputMarkdown), makeMarkdown(report));

  console.log(`wrote ${paths.outputJson}`);
  console.log(`wrote ${paths.outputMarkdown}`);
  console.log(`inventoried ${report.summary.borgCount} borgs; priority ${priorityBorgIds.join(", ")}`);
}

main().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
