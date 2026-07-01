#!/usr/bin/env node
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const region = process.argv.find((arg) => !arg.startsWith("--")) ?? "GG4E";
const outDir = path.join(repoRoot, "research", "asset-coverage");
const outJson = path.join(outDir, "real-asset-coverage.json");
const outMd = path.join(outDir, "real-asset-coverage.md");

const screenDefs = [
  {
    id: "main-menu",
    runtimeScreen: "menu",
    file: "apps/game/src/ui/screens/MainMenu.ts",
    exportName: "createMainMenu",
    originalMode: "Challenge mode hub",
    expectedSourceArchives: ["tl00_mdl.arc", "optn00_mdl.arc", "staff00_mdl.arc", "titles.tpl", "as_icon.tpl", "font_00.tpl"],
    nextReplacement: "Export/wire the real 3D desk/menu scene instead of CSS ellipse gears and text labels.",
  },
  {
    id: "select-difficulty",
    runtimeScreen: "difficulty",
    file: "apps/game/src/ui/screens/SelectDifficulty.ts",
    exportName: "createSelectDifficulty",
    originalMode: "Challenge",
    expectedSourceArchives: ["vsel00_mdl.arc", "vsel01_mdl.arc", "as_icon.tpl", "font_00.tpl"],
    nextReplacement: "Use the original Challenge select scene textures/models for the three GF-energy pads and cursor.",
  },
  {
    id: "select-players",
    runtimeScreen: "players",
    file: "apps/game/src/ui/screens/SelectPlayers.ts",
    exportName: "createSelectPlayers",
    originalMode: "Challenge",
    expectedSourceArchives: ["vsel00_mdl.arc", "vsel01_mdl.arc", "as_icon.tpl", "font_00.tpl"],
    nextReplacement: "Replace CSS silhouettes/pills/controllers with the real Challenge player-count select scene.",
  },
  {
    id: "load-box-data",
    runtimeScreen: "load-box",
    file: "apps/game/src/ui/screens/LoadBoxData.ts",
    exportName: "createLoadBoxData",
    originalMode: "Challenge",
    expectedSourceArchives: ["box00_mdl.arc", "firstld.pzz", "font_00.tpl"],
    nextReplacement: "Keep the real box DAE, but replace handwritten gold screen copy/rules with original load/box scene assets.",
  },
  {
    id: "select-force",
    runtimeScreen: "select-force",
    file: "apps/game/src/ui/screens/SelectForce.ts",
    exportName: "createSelectForce",
    originalMode: "Challenge",
    expectedSourceArchives: ["entry00_mdl.arc", "box00_mdl.arc", "unitall_mdl.arc", "plcmndata.bin", "allbox.bin", "bn####.tpl", "mn####.tpl", "face####_mdl.arc"],
    nextReplacement: "Replace CSS platform/cost/name layout with the real force-slot/select scene and save/box data.",
  },
  {
    id: "force-builder",
    runtimeScreen: "force",
    file: "apps/game/src/ui/screens/ForceBuilder.ts",
    exportName: "createForceBuilder",
    originalMode: "Challenge edit force",
    expectedSourceArchives: ["unitall_mdl.arc", "plcmndata.bin", "allbox.bin", "gets.pzz", "gets##_mdl.arc", "bn####.tpl", "mn####.tpl"],
    nextReplacement: "Replace the CSS grid/ring/hex slots with original Edit Force layout data and model/collection assets.",
  },
  {
    id: "battle-intro",
    runtimeScreen: "briefing",
    file: "apps/game/src/ui/screens/BattleIntro.ts",
    exportName: "createBattleIntro",
    originalMode: "Challenge briefing/VS",
    expectedSourceArchives: ["brif00_mdl.arc", "entry00_mdl.arc", "vsel00_mdl.arc", "msg*.mdt", "face####_mdl.arc"],
    nextReplacement: "Use the real briefing/entry scene sequencing, not only low-opacity extracted texture sheets over CSS plates.",
  },
  {
    id: "battle-hud",
    runtimeScreen: "battle",
    file: "apps/game/src/ui/hud/BattleHud.ts",
    exportName: "createBattleHud",
    originalMode: "Challenge battle HUD",
    expectedSourceArchives: ["bn####.tpl", "face####_mdl.arc", "font_00.tpl", "as_icon.tpl", "arrow_mdl.arc", "comhit.bin", "comhit2.bin", "cmn_data.bin"],
    nextReplacement: "Map original HUD widgets, lock-on cursor, weapon prompts, and battle data instead of CSS/SVG gauges.",
  },
  {
    id: "results",
    runtimeScreen: "results",
    file: "apps/game/src/ui/screens/Results.ts",
    exportName: "createResults",
    originalMode: "Challenge results",
    expectedSourceArchives: ["rpot20_mdl.arc", "rpot21_mdl.arc", "rpot22_mdl.arc", "rpot23_mdl.arc"],
    nextReplacement: "Export and mount the real result/podium scenes instead of CSS rows and sky backdrop.",
  },
  {
    id: "pause-menu",
    runtimeScreen: "pause",
    file: "apps/game/src/ui/screens/PauseMenu.ts",
    exportName: "createPauseMenu",
    originalMode: "In-battle",
    expectedSourceArchives: ["font_00.tpl", "as_icon.tpl", "cmn_data.bin"],
    nextReplacement: "Find the original pause menu data/assets; current overlay is entirely recreated CSS/text.",
  },
];

const assetConstants = {
  ASSETS: {
    mainMenuOption: "/ui/hsd/optn00_mdl/texture_000_CI4.png",
    gotchaBoxLens: "/ui/hsd/box00_mdl/texture_000_CMP.png",
    gotchaBoxCross: "/ui/hsd/box00_mdl/texture_001_CMP.png",
    gotchaBoxScrew: "/ui/hsd/box00_mdl/texture_002_CMP.png",
    gotchaBoxButton: "/ui/hsd/box00_mdl/texture_003_CMP.png",
    getStrip: "/ui/hsd/gets00_mdl/texture_000_CI4.png",
    entryControls: "/ui/hsd/entry00_mdl/texture_002_CI8.png",
    unitAllAtlas: "/ui/hsd/unitall_mdl/texture_008_CI8.png",
    briefingVs: "/ui/hsd/brif00_mdl/texture_000_IA4.png",
    briefingNames: "/ui/hsd/brif00_mdl/texture_001_CI4.png",
    vsSelectLabels: "/ui/hsd/vsel00_mdl/texture_004_CI8.png",
    resultsWin: "/ui/hsd/rpot20_mdl/texture_000_RGBA8.png",
    resultsLose: "/ui/hsd/rpot23_mdl/texture_000_RGBA8.png",
    resultsStartPrompt: "/ui/hsd/rpot20_mdl/texture_003_CI8.png",
    resultsGameOver: "/ui/hsd/rpot23_mdl/texture_004_CI8.png",
    faceMarkerRoundel: "/ui/hsd/fmg00_mdl/texture_001_CI8.png",
    fontAscii: "/ui/tpl/ascii/image_00_IA4.png",
    font: "/ui/tpl/font_00/image_00_CI4.png",
  },
  helpers: {
    borgBannerPath: "/ui/tpl/bn<borgUiCode>/image_00_CI4.png",
    borgMiniPath: "/ui/tpl/mn<borgUiCode>/image_00_CI4.png",
    borgFacePath: "/ui/hsd/face<borgUiCode>_mdl/texture_000_CI8.png",
  },
};

const fakeSurfacePatterns = [
  { pattern: "gf-grid-bg", kind: "css-grid-backdrop" },
  { pattern: "linear-gradient", kind: "css-gradient-surface" },
  { pattern: "radial-gradient", kind: "css-gradient-surface" },
  { pattern: "conic-gradient", kind: "css-gear-surface" },
  { pattern: "gf-menu-gear", kind: "css-menu-gear" },
  { pattern: "gf-pad", kind: "css-option-pad" },
  { pattern: "gf-pill", kind: "css-label-pill" },
  { pattern: "personSilhouette", kind: "handcoded-player-silhouette" },
  { pattern: "gf-select-platform", kind: "css-force-platform" },
  { pattern: "gf-force-grid", kind: "handcoded-force-grid" },
  { pattern: "gf-force-ring", kind: "handcoded-force-ring" },
  { pattern: "gf-slot", kind: "handcoded-force-slot" },
  { pattern: "ringGauge", kind: "svg-hud-gauge" },
  { pattern: "gf-reticle", kind: "css-lockon-reticle" },
  { pattern: "gf-results-sky", kind: "css-results-backdrop" },
  { pattern: "gf-result-pill", kind: "css-results-row" },
  { pattern: "gf-pause-box", kind: "css-pause-box" },
  { pattern: "text:", kind: "runtime-text-layout" },
];

function rel(file) {
  return path.relative(repoRoot, file).replaceAll(path.sep, "/");
}

function abs(file) {
  return path.resolve(repoRoot, file);
}

function readText(file) {
  return fs.existsSync(abs(file)) ? fs.readFileSync(abs(file), "utf8") : "";
}

function readJson(file) {
  try {
    return { ok: true, value: JSON.parse(readText(file)), error: null };
  } catch (error) {
    return { ok: false, value: null, error: error.message };
  }
}

function lineOf(text, needle) {
  const index = text.indexOf(needle);
  if (index < 0) return null;
  return text.slice(0, index).split(/\r?\n/).length;
}

function grepHits(text, patterns) {
  const hits = [];
  for (const { pattern, kind } of patterns) {
    const line = lineOf(text, pattern);
    if (line != null) hits.push({ kind, pattern, line });
  }
  return hits;
}

function publicPathExists(publicPath) {
  if (!publicPath.startsWith("/")) return false;
  return fs.existsSync(path.join(repoRoot, "apps", "game", "public", publicPath.slice(1)));
}

function sourceArchiveRecord(name) {
  if (name.includes("#") || name.includes("*")) {
    const regex = new RegExp(`^${name.replaceAll(".", "\\.").replaceAll("####", "[0-9a-f]{4}").replaceAll("##", "[0-9a-f]{2}").replaceAll("*", ".*")}$`, "i");
    const root = abs(`user-data/${region}/afs_data/root`);
    const samples = fs.existsSync(root) ? fs.readdirSync(root).filter((file) => regex.test(file)).sort().slice(0, 8) : [];
    return { pattern: name, exists: samples.length > 0, sampleCount: samples.length, samples: samples.map((file) => `user-data/${region}/afs_data/root/${file}`) };
  }
  const file = `user-data/${region}/afs_data/root/${name}`;
  return { path: file, exists: fs.existsSync(abs(file)) };
}

function assetSourcesUsed(text) {
  const used = [];
  for (const [name, publicPath] of Object.entries(assetConstants.ASSETS)) {
    if (new RegExp(`\\bASSETS\\.${name}\\b`).test(text)) {
      used.push({ kind: "named-texture", symbol: `ASSETS.${name}`, publicPath, exists: publicPathExists(publicPath) });
    }
  }
  for (const [name, publicPathPattern] of Object.entries(assetConstants.helpers)) {
    if (text.includes(`${name}(`)) {
      used.push({ kind: "borg-ui-helper", symbol: name, publicPathPattern, exists: "per-borg" });
    }
  }
  const literalPublicPaths = [...text.matchAll(/["'](\/(?:ui|stages|models)\/[^"']+)["']/g)].map((match) => match[1]);
  for (const publicPath of literalPublicPaths) {
    if (!used.some((asset) => asset.publicPath === publicPath)) {
      used.push({ kind: "literal-public-path", publicPath, exists: publicPathExists(publicPath) });
    }
  }
  const mountedSceneIds = [...text.matchAll(/sceneId:\s*["']([^"']+)["']/g)].map((match) => match[1]);
  for (const sceneId of mountedSceneIds) {
    const publicPath = `/ui/scenes/${sceneId}/model_00.dae`;
    if (!used.some((asset) => asset.publicPath === publicPath)) {
      used.push({ kind: "mounted-ui-scene", publicPath, exists: publicPathExists(publicPath) });
    }
  }
  return used;
}

function coverageLevel(realAssets, fakeHits) {
  const hasSceneModel = realAssets.some((asset) => asset.publicPath?.endsWith(".dae") && asset.exists === true);
  const hasReal = realAssets.length > 0;
  if (hasSceneModel && fakeHits.length <= 6) return "real-scene-partial-layout";
  if (hasReal && fakeHits.length > 0) return "mixed-real-assets-handcoded-surface";
  if (hasReal) return "real-assets-only";
  return "handcoded-or-unverified";
}

function inspectScreens() {
  return screenDefs.map((def) => {
    const text = readText(def.file);
    const realAssets = assetSourcesUsed(text);
    const fakeHits = grepHits(text, fakeSurfacePatterns);
    const sourceArchives = def.expectedSourceArchives.map(sourceArchiveRecord);
    return {
      ...def,
      fileExists: fs.existsSync(abs(def.file)),
      fileRef: `${def.file}${lineOf(text, `export function ${def.exportName}`) ? `:${lineOf(text, `export function ${def.exportName}`)}` : ""}`,
      coverageLevel: coverageLevel(realAssets, fakeHits),
      realExportedAssetsUsed: realAssets,
      handcodedSurfaceSignals: fakeHits,
      expectedSourceArchives: sourceArchives,
      replacementStatus:
        realAssets.length === 0
          ? "No direct exported UI asset usage observed in this component."
          : "Uses exported asset(s), but audit still treats CSS/SVG/DOM recreations as non-1:1 until original scene/layout is wired.",
    };
  });
}

function inspectStages() {
  const rootManifest = readJson("apps/game/public/stages/manifest.json");
  const plan = readJson("research/asset-inventory/stage-export-plan.json");
  const stageCodeEvidence = readJson("research/asset-inventory/stage-code-evidence.json");
  const adapter = readText("apps/game/src/sim/adapter.ts");
  const main = readText("apps/game/src/main.ts");
  const publicStages = rootManifest.value?.stages ?? [];
  const completeVisual = publicStages.filter((stage) => stage.visualComplete === true);
  const collisionCovered = publicStages.filter((stage) => stage.collisionCount > 0);
  const renderStateCovered = publicStages.filter((stage) =>
    fs.existsSync(abs(`apps/game/public/stages/${stage.id}/render-state.json`)),
  );
  const sourceStageCodes = plan.value?.sources?.adventureFlow?.directStageArchives?.codes ?? plan.value?.stages?.map((stage) => stage.id) ?? [];
  const runtimeLiteralStages = [...new Set([...adapter.matchAll(/st[0-9a-f]{2}|stff/gi)].map((match) => match[0].toLowerCase()))];
  return {
    publicManifest: {
      path: "apps/game/public/stages/manifest.json",
      parses: rootManifest.ok,
      stageCount: publicStages.length,
      completeVisualCount: completeVisual.length,
      collisionCoveredCount: collisionCovered.length,
      renderStateCoveredCount: renderStateCovered.length,
      stageIds: publicStages.map((stage) => stage.id),
    },
    exportPlan: {
      path: "research/asset-inventory/stage-export-plan.json",
      parses: plan.ok,
      sourceStageArchiveCount: plan.value?.summary?.sourceStageArchiveCount ?? null,
      sourcePairsWithModelAndPzz: plan.value?.summary?.sourcePairsWithModelAndPzz ?? null,
      verifiedVisualStageCount: plan.value?.summary?.verifiedVisualStageCount ?? null,
      missingOrPartialExportCount: plan.value?.summary?.missingOrPartialExportCount ?? null,
      sourceStageCodes,
    },
    runtimeUse: {
      defaultStage: runtimeLiteralStages.includes("st00") ? "st00" : null,
      literalStageIdsInAdapter: runtimeLiteralStages,
      acceptsHexStageIds: adapter.includes("^st[0-9a-f]{2}$"),
      adapterRefs: {
        defaultArenaStage: `apps/game/src/sim/adapter.ts:${lineOf(adapter, "DEFAULT_ARENA_STAGE")}`,
        fallback: `apps/game/src/sim/adapter.ts:${lineOf(adapter, "return DEFAULT_ARENA_STAGE")}`,
      },
      mainRefs: {
        loadStage: `apps/game/src/main.ts:${lineOf(main, "async function loadStage(stageId")}`,
        fetchStageManifest: `apps/game/src/main.ts:${lineOf(main, "fetch(`/stages/${stageId}/manifest.json`)")}`,
        loadStageCollision: `apps/game/src/main.ts:${lineOf(main, "async function loadStageCollision")}`,
        parseStageHitGrid: `apps/game/src/main.ts:${lineOf(main, "parseStageHitGrid")}`,
        loadDefaultArena: `apps/game/src/main.ts:${lineOf(main, "loadStage(DEFAULT_ARENA_STAGE)")}`,
        loadConvertedStage: `apps/game/src/main.ts:${lineOf(main, "await loadStage(stageId)")}`,
      },
      collisionBounds: {
        usesStageHitParser: main.includes("hitBin.parseStageHitGrid"),
        passesBoundsToCombat: main.includes("convertBattleConfig(config, stageId, stageBounds"),
        passesTrianglesToCombat: main.includes("stageResources.collision") && main.includes("convertBattleConfig(config, stageId, stageBounds, stageResources.collision)"),
        movementUsesTriangleWalls: readText("packages/combat/src/movement.ts").includes("resolveLateralCollision"),
        movementUsesTriangleCeilings: readText("packages/combat/src/movement.ts").includes("resolveCeilingCollision"),
        parserPackage: main.includes("@gf/formats") ? "@gf/formats" : null,
      },
      assessment:
        publicStages.length > 1
          ? "Exports cover many real stages, but arena-name to st## routing still falls back to st00 unless cfg.arena is already a literal st## id."
          : "Runtime and public export are both effectively st00-only.",
    },
    stageCodeEvidence: {
      path: "research/asset-inventory/stage-code-evidence.json",
      parses: stageCodeEvidence.ok,
      bootDolStageCodeHitCount: stageCodeEvidence.value?.summary?.bootDolStageCodeHitCount ?? null,
      bootDolUniqueStageCodeCount: stageCodeEvidence.value?.summary?.bootDolUniqueStageCodeCount ?? null,
      verifiedArenaNameMappingCount: stageCodeEvidence.value?.summary?.verifiedArenaNameMappingCount ?? null,
      conclusion: stageCodeEvidence.value?.conclusion ?? null,
    },
  };
}

function inspectUiSceneExports() {
  const manifest = readJson("apps/game/public/ui/scenes/manifest.json");
  const assets = manifest.value?.assets ?? [];
  return {
    path: "apps/game/public/ui/scenes/manifest.json",
    parses: manifest.ok,
    counts: manifest.value?.counts ?? null,
    requestedScenes: assets
      .filter((asset) => asset.requested)
      .map((asset) => ({
        id: asset.id,
        status: asset.status,
        sourceArchive: asset.sourceArchive?.sourcePath ?? null,
        modelFiles: asset.modelFiles?.map((file) => file.path) ?? [],
        textureCount: asset.textureCount ?? 0,
        nextCommand:
          asset.status === "exported"
            ? null
            : `Need validated DAE/glTF export for ${asset.sourceArchive?.sourcePath ?? `${asset.id}_mdl.arc`}; current scripts/export-ui-scenes.mjs only copies existing validated exports.`,
      })),
  };
}

function inspectUiTextureExports() {
  const manifest = readJson("apps/game/public/ui/manifest.json");
  return {
    path: "apps/game/public/ui/manifest.json",
    parses: manifest.ok,
    counts: manifest.value?.counts ?? null,
    blockedAssets: (manifest.value?.assets ?? [])
      .filter((asset) => asset.status !== "exported")
      .map((asset) => ({ sourcePath: asset.sourcePath, status: asset.status, categoryLabels: asset.categoryLabels })),
  };
}

function inspectModeNamingRisks() {
  const stages = readJson("packages/assets/data/stages.json");
  const adventure = readJson("research/asset-inventory/adventure-flow-ai.json");
  const metadata = stages.value?.metadata ?? {};
  const runtimeScreenDefs = inspectScreens();
  const challengeScreens = runtimeScreenDefs.filter((screen) => /Challenge/i.test(screen.originalMode)).length;
  return {
    stageDataMode: metadata.mode ?? adventure.value?.data?.stages?.metaMode ?? null,
    stageDataPath: "packages/assets/data/stages.json",
    adventureInventoryScope: adventure.value?.scope ?? null,
    uniqueArenaCount: adventure.value?.data?.stages?.uniqueArenaCount ?? null,
    finding:
      "Runtime screen comments and flow are Challenge-oriented, while packages/assets/data/stages.json declares Story Mode data and adventure-flow inventory discusses Adventure. Do not use Story/Adventure mission rows as a verified Challenge stage/menu mapping.",
    evidence: [
      `packages/assets/data/stages.json:${lineOf(readText("packages/assets/data/stages.json"), "\"mode\"")}`,
      `research/asset-inventory/adventure-flow-ai.json:${lineOf(readText("research/asset-inventory/adventure-flow-ai.json"), "\"metaMode\"")}`,
      `${challengeScreens} audited runtime screens identify themselves as Challenge or in-battle Challenge UI.`,
    ],
  };
}

function inspectCombatFx() {
  const combat = readText("packages/combat/src/combat.ts");
  const types = readText("packages/combat/src/types.ts");
  const battleScene = readText("apps/game/src/sim/battleScene.ts");
  const fxManifest = readJson("apps/game/public/fx/manifest.json");
  const texturePaths = [
    "/fx/energy_dot.png",
    "/fx/flame_core.png",
    "/fx/muzzle_flash.png",
    "/fx/efct00_atlas.png",
    "/fx/hit_spark.png",
  ];
  return {
    projectileVisualKindInState: types.includes("ProjectileVisualKind") && types.includes("visualKind"),
    projectileVisualKindDerivedFromProfile: combat.includes("projectileVisualKindForProfile"),
    rendererUsesExportedProjectileTextures: texturePaths.every((texturePath) => battleScene.includes(texturePath) && publicPathExists(texturePath)),
    fxManifest: {
      path: "apps/game/public/fx/manifest.json",
      parses: fxManifest.ok,
      imageCount: fxManifest.value?.images?.length ?? null,
      projectileTextures: texturePaths.map((texturePath) => ({
        publicPath: texturePath,
        exists: publicPathExists(texturePath),
      })),
    },
  };
}

function inspectHudAssetEvidence() {
  const manifest = readJson("apps/game/public/ui/hud/manifest.json");
  const battleHud = readText("apps/game/src/ui/hud/BattleHud.ts");
  const available = manifest.value?.available ?? {};
  const notAvailableAsSprites = manifest.value?.notAvailableAsSprites ?? {};
  const availableRows = Object.entries(available).map(([key, value]) => ({
    key,
    file: value.file ?? null,
    source: value.source ?? null,
    size: value.w && value.h ? `${value.w}x${value.h}` : "unknown",
    format: value.format ?? null,
    confidence: value.confidence ?? null,
    role: value.role ?? null,
    usedInBattleHud:
      (key === "fontAscii" && battleHud.includes("ASSETS.fontAscii")) ||
      (key === "faceIconRoundel" && battleHud.includes("ASSETS.faceMarkerRoundel")) ||
      (key === "asIcon" && battleHud.includes("as_icon")),
  }));
  return {
    path: "apps/game/public/ui/hud/manifest.json",
    parses: manifest.ok,
    summary: manifest.value?.summary ?? null,
    availableRows,
    gameDrawnRows: Object.entries(notAvailableAsSprites).map(([key, note]) => ({ key, note })),
    asIconPublicPath: "/ui/tpl/as_icon/image_00_CI8.png",
    asIconExists: publicPathExists("/ui/tpl/as_icon/image_00_CI8.png"),
    battleHudUsesFontAscii: battleHud.includes("ASSETS.fontAscii"),
    battleHudUsesFaceRoundel: battleHud.includes("ASSETS.faceMarkerRoundel"),
    battleHudUsesAsIcon: battleHud.includes("as_icon"),
  };
}

function inspectBorgAnimationCoverage() {
  const reportPath = "research/asset-inventory/borg-animation-action-gaps.md";
  const report = readText(reportPath);
  const metric = (name) => {
    const match = new RegExp(`\\| ${name.replace(/[.*+?^${}()|[\]\\]/g, "\\$&")} \\|\\s*(\\d+) \\|`).exec(report);
    return match ? Number.parseInt(match[1], 10) : null;
  };
  const slotRows = [...report.matchAll(/\| `([^`]+)` \|\s*(\d+) \|\s*(\d+) \|\s*(\d+) \| ([^|]+) \|/g)].map((match) => ({
    slot: match[1],
    direct: Number.parseInt(match[2], 10),
    fallback: Number.parseInt(match[3], 10),
    missing: Number.parseInt(match[4], 10),
    notes: match[5].trim(),
  }));
  const main = readText("apps/game/src/main.ts");
  const battleScene = readText("apps/game/src/sim/battleScene.ts");
  return {
    path: reportPath,
    exists: fs.existsSync(abs(reportPath)),
    indexesFound: metric("Animation indexes found"),
    indexesParsed: metric("Animation indexes parsed"),
    exportedBanks: metric("Total exported banks in parsed indexes"),
    canonicalSlotChecks: metric("Canonical slot checks"),
    directRuntimeMatches: metric("Direct runtime matches"),
    runtimeFallbacks: metric("Runtime fallbacks"),
    missingRuntimeMatches: metric("Missing runtime matches"),
    parseErrors: metric("Parse errors"),
    slotRows,
    runtimeResolverRefs: {
      slotLabels: `apps/game/src/main.ts:${lineOf(main, "const SLOT_LABELS")}`,
      slotFallbacks: `apps/game/src/main.ts:${lineOf(main, "const SLOT_FALLBACKS")}`,
      pickAnimBank: `apps/game/src/main.ts:${lineOf(main, "function pickAnimBank")}`,
      battleSceneSlotMapping: `apps/game/src/sim/battleScene.ts:${lineOf(battleScene, "private slotForBorg")}`,
    },
    boostFlyMapped:
      main.includes("fly: [/^boost$/") &&
      battleScene.includes('if (b.state === "fly") return "fly"'),
  };
}

function inspectPowerupRuntimeGap() {
  const types = readText("packages/combat/src/types.ts");
  const battle = readText("packages/combat/src/battle.ts");
  const particleInventory = readJson("research/asset-inventory/particle-effect-inventory.json");
  const hudInventory = readText("research/asset-inventory/ui-hud-assets.md");
  return {
    battleStateHasItems:
      /(?:items|pickups|powerups|drops)\s*:/.test(types),
    battleRuntimeSpawnsDrops:
      /\b(?:spawnItem|spawnPickup|spawnPowerup|createItem|createPickup|createPowerup)\b/.test(battle),
    evidenceRefs: {
      battleState: `packages/combat/src/types.ts:${lineOf(types, "export interface BattleState")}`,
      deployNextBorg: `packages/combat/src/battle.ts:${lineOf(battle, "private deployNext")}`,
      deathProcessing: `packages/combat/src/battle.ts:${lineOf(battle, "Process any deaths")}`,
      particleInventory: "research/asset-inventory/particle-effect-inventory.json",
      hudInventory: "research/asset-inventory/ui-hud-assets.md",
    },
    assetLeads: {
      itemModelArzCount: particleInventory.value?.summary?.itemModelArzCount ?? particleInventory.value?.itemModelArzCount ?? null,
      asIconDocumented: hudInventory.includes("as_icon.tpl"),
      comhitDocumented: hudInventory.includes("comhit.bin"),
    },
    assessment:
      "Combat state has no item/drop/pickup collection yet. Do not add gameplay powerups until DOL/runtime evidence identifies drop tables and pickup effects; safest next asset work is HUD/icon/comhit inventory.",
  };
}

function inspectAudioRuntime() {
  const main = readText("apps/game/src/main.ts");
  const gamePackage = readJson("apps/game/package.json");
  const manifest = readJson("apps/game/public/audio/manifest.json");
  const files = manifest.value?.files ?? [];
  const cueKeys = ["bgm00", "bgm01", "se00_00", "se00_01", "se00_02"];
  return {
    audioPackageDependency: Boolean(gamePackage.value?.dependencies?.["@gf/audio"]),
    runtimeImportsAudioManager: main.includes("createAudioManager") && main.includes("@gf/audio"),
    runtimeQueuesBgm: main.includes("queueBgm(AUDIO_CUES.menuBgm)") && main.includes("queueBgm(AUDIO_CUES.battleBgm)"),
    runtimePlaysSfx: main.includes("playConfirmSfx") && main.includes("playBackSfx") && main.includes("playEditSfx"),
    manifest: {
      path: "apps/game/public/audio/manifest.json",
      parses: manifest.ok,
      counts: manifest.value?.counts ?? null,
      cueKeys: cueKeys.map((key) => ({
        key,
        exists: files.some((entry) => entry.key === key),
      })),
      notes: manifest.value?.notes ?? null,
    },
  };
}

function buildReport() {
  const screens = inspectScreens();
  const stageCoverage = inspectStages();
  const uiSceneExports = inspectUiSceneExports();
  const uiTextureExports = inspectUiTextureExports();
  const modeNamingRisks = inspectModeNamingRisks();
  const combatFx = inspectCombatFx();
  const hudAssetEvidence = inspectHudAssetEvidence();
  const borgAnimationCoverage = inspectBorgAnimationCoverage();
  const powerupRuntimeGap = inspectPowerupRuntimeGap();
  const audioRuntime = inspectAudioRuntime();
  const summary = {
    screens: screens.length,
    screensUsingAnyRealExportedAsset: screens.filter((screen) => screen.realExportedAssetsUsed.length > 0).length,
    screensWithHandcodedSurfaceSignals: screens.filter((screen) => screen.handcodedSurfaceSignals.length > 0).length,
    screensWithRealSceneModel: screens.filter((screen) => screen.realExportedAssetsUsed.some((asset) => asset.publicPath?.endsWith(".dae"))).length,
    publicUiTextureExportedImages: uiTextureExports.counts?.exportedImages ?? null,
    requestedUiSceneModelsExported: uiSceneExports.counts?.exported ?? null,
    publicStagesCompleteVisual: stageCoverage.publicManifest.completeVisualCount,
    publicStagesTotal: stageCoverage.publicManifest.stageCount,
    publicStagesRenderState: stageCoverage.publicManifest.renderStateCoveredCount,
    runtimeStageFallback: stageCoverage.runtimeUse.defaultStage,
    runtimeAcceptsHexStageIds: stageCoverage.runtimeUse.acceptsHexStageIds,
    runtimeStageCollisionBounds: stageCoverage.runtimeUse.collisionBounds.usesStageHitParser && stageCoverage.runtimeUse.collisionBounds.passesBoundsToCombat,
    runtimeStageTriangleCollision: stageCoverage.runtimeUse.collisionBounds.usesStageHitParser && stageCoverage.runtimeUse.collisionBounds.passesTrianglesToCombat,
    runtimeStageWallCollision: stageCoverage.runtimeUse.collisionBounds.movementUsesTriangleWalls,
    runtimeStageCeilingCollision: stageCoverage.runtimeUse.collisionBounds.movementUsesTriangleCeilings,
    runtimeProjectileFxFromExportedTextures:
      combatFx.projectileVisualKindInState &&
      combatFx.projectileVisualKindDerivedFromProfile &&
      combatFx.rendererUsesExportedProjectileTextures,
    runtimeBattleHudUsesAvailableFontAndRoundel:
      hudAssetEvidence.battleHudUsesFontAscii && hudAssetEvidence.battleHudUsesFaceRoundel,
    runtimeBattleHudUsesAsIcon: hudAssetEvidence.battleHudUsesAsIcon,
    runtimeBorgAnimationDirectMatches: borgAnimationCoverage.directRuntimeMatches,
    runtimeBorgAnimationFallbacks: borgAnimationCoverage.runtimeFallbacks,
    runtimeBorgAnimationMissing: borgAnimationCoverage.missingRuntimeMatches,
    runtimeBoostFlyUsesExportedBoostClip: borgAnimationCoverage.boostFlyMapped,
    runtimeItemsOrPowerupsModeled: powerupRuntimeGap.battleStateHasItems || powerupRuntimeGap.battleRuntimeSpawnsDrops,
    runtimeAudioFromExportedCues:
      audioRuntime.audioPackageDependency &&
      audioRuntime.runtimeImportsAudioManager &&
      audioRuntime.runtimeQueuesBgm &&
      audioRuntime.runtimePlaysSfx &&
      audioRuntime.manifest.cueKeys.every((cue) => cue.exists),
  };
  return {
    generatedBy: "scripts/audit-real-asset-coverage.mjs",
    generatedAt: new Date().toISOString(),
    region,
    scope: "Audit only. Reads exporter scripts/manifests/runtime screens and writes research/asset-coverage outputs. Does not edit runtime files.",
    summary,
    screens,
    stageCoverage,
    uiSceneExports,
    uiTextureExports,
    combatFx,
    hudAssetEvidence,
    borgAnimationCoverage,
    powerupRuntimeGap,
    audioRuntime,
    modeNamingRisks,
    nextMostUsefulReplacements: [
      "Wire stageIdForArena to a traced arena-name -> st## table; public exports now cover 40 visual stages, but runtime fallback still collapses non-st## arenas to st00.",
      "Generalize UI scene model export beyond box00 so tl00/optn00/vsel00/vsel01/brif00/entry00/rpot20-23 can replace CSS scene recreations.",
      "Replace ForceBuilder/SelectForce surfaces with unitall/plcmndata/allbox/gets-driven original layouts; they currently use real borg icons/banners inside handcoded DOM.",
      "Map battle HUD from comhit/cmn_data/as_icon/arrow/font assets and DOL HUD state instead of CSS/SVG gauges.",
      "Resolve remaining borg animation fallbacks/misses from research/asset-inventory/borg-animation-action-gaps.md, especially missing move clips and fallback hit/death labels.",
    ],
  };
}

function mdTable(rows, columns) {
  const header = `| ${columns.map((column) => column.title).join(" | ")} |`;
  const sep = `| ${columns.map(() => "---").join(" | ")} |`;
  const body = rows.map((row) => `| ${columns.map((column) => escapeMd(column.value(row))).join(" | ")} |`);
  return [header, sep, ...body].join("\n");
}

function escapeMd(value) {
  return String(value ?? "").replaceAll("|", "\\|").replaceAll("\n", " ");
}

function renderMarkdown(report) {
  const lines = [];
  const add = (line = "") => lines.push(line);
  add("# Real Asset Coverage Audit");
  add();
  add(`Generated: ${report.generatedAt}`);
  add();
  add("## Summary");
  add();
  add(`- Runtime screens audited: ${report.summary.screens}`);
  add(`- Screens using at least one real exported UI asset: ${report.summary.screensUsingAnyRealExportedAsset}`);
  add(`- Screens with handcoded/CSS/SVG surface signals: ${report.summary.screensWithHandcodedSurfaceSignals}`);
  add(`- Screens mounting a real exported UI scene model: ${report.summary.screensWithRealSceneModel}`);
  add(`- UI texture export: ${report.summary.publicUiTextureExportedImages} images from ${report.uiTextureExports.path}`);
  add(`- Requested UI scene models exported: ${report.summary.requestedUiSceneModelsExported ?? "unknown"} from ${report.uiSceneExports.path}`);
  add(`- Stage exports complete visually: ${report.summary.publicStagesCompleteVisual}/${report.summary.publicStagesTotal}`);
  add(`- Stage render-state exports: ${report.summary.publicStagesRenderState}/${report.summary.publicStagesTotal}`);
  add(`- Runtime stage collision bounds from STIH: ${report.summary.runtimeStageCollisionBounds ? "yes" : "no"}`);
  add(`- Runtime stage triangle collision from STIH: ${report.summary.runtimeStageTriangleCollision ? "yes" : "no"}`);
  add(`- Runtime lateral wall collision from STIH: ${report.summary.runtimeStageWallCollision ? "yes" : "no"}`);
  add(`- Runtime upward ceiling collision from STIH: ${report.summary.runtimeStageCeilingCollision ? "yes" : "no"}`);
  add(`- Runtime projectile FX from exported textures: ${report.summary.runtimeProjectileFxFromExportedTextures ? "yes" : "no"}`);
  add(`- Runtime battle HUD uses exported font/roundel: ${report.summary.runtimeBattleHudUsesAvailableFontAndRoundel ? "yes" : "no"}`);
  add(`- Runtime battle HUD uses as_icon: ${report.summary.runtimeBattleHudUsesAsIcon ? "yes" : "no"} (manifest marks as_icon low-confidence for battle HUD)`);
  add(`- Runtime borg animation direct matches: ${report.summary.runtimeBorgAnimationDirectMatches}/${report.borgAnimationCoverage.canonicalSlotChecks}`);
  add(`- Runtime borg animation fallbacks/missing: ${report.summary.runtimeBorgAnimationFallbacks}/${report.summary.runtimeBorgAnimationMissing}`);
  add(`- Runtime fly uses exported boost clip: ${report.summary.runtimeBoostFlyUsesExportedBoostClip ? "yes" : "no"}`);
  add(`- Runtime items/powerups modeled: ${report.summary.runtimeItemsOrPowerupsModeled ? "yes" : "no"}`);
  add(`- Runtime audio from exported cues: ${report.summary.runtimeAudioFromExportedCues ? "yes" : "no"}`);
  add(`- Runtime stage fallback: ${report.summary.runtimeStageFallback ?? "unknown"}`);
  add(`- Runtime accepts exported hex stage ids: ${report.summary.runtimeAcceptsHexStageIds ? "yes" : "no"}`);
  add();
  add("## Runtime Screens");
  add();
  add(
    mdTable(report.screens, [
      { title: "Screen", value: (row) => row.id },
      { title: "Coverage", value: (row) => row.coverageLevel },
      { title: "Real exported assets used", value: (row) => row.realExportedAssetsUsed.map((asset) => asset.symbol ?? asset.publicPath ?? asset.publicPathPattern).join("<br>") || "none" },
      { title: "Handcoded signals", value: (row) => row.handcodedSurfaceSignals.map((hit) => `${hit.kind}:${hit.line}`).join("<br>") || "none" },
      { title: "Next replacement", value: (row) => row.nextReplacement },
    ]),
  );
  add();
  add("## UI Scene Export Coverage");
  add();
  add(
    mdTable(report.uiSceneExports.requestedScenes, [
      { title: "Scene", value: (row) => row.id },
      { title: "Status", value: (row) => row.status },
      { title: "Source archive", value: (row) => row.sourceArchive },
      { title: "Model files", value: (row) => row.modelFiles.join("<br>") || "none" },
      { title: "Next", value: (row) => row.nextCommand ?? "wired asset available" },
    ]),
  );
  add();
  add("## Stage Coverage");
  add();
  add(`Public stage manifest has ${report.stageCoverage.publicManifest.stageCount} stage folders; ${report.stageCoverage.publicManifest.completeVisualCount} have complete visual DAE exports, ${report.stageCoverage.publicManifest.renderStateCoveredCount} have render-state JSON, and ${report.stageCoverage.publicManifest.collisionCoveredCount} have collision bins.`);
  add();
  add(`Runtime loader refs: ${Object.values(report.stageCoverage.runtimeUse.mainRefs).join(", ")}`);
  add();
  add(`Runtime collision parser: ${report.stageCoverage.runtimeUse.collisionBounds.parserPackage ?? "none"} (bounds ${report.summary.runtimeStageCollisionBounds ? "wired" : "not wired"}, triangles ${report.summary.runtimeStageTriangleCollision ? "wired" : "not wired"}, walls ${report.summary.runtimeStageWallCollision ? "wired" : "not wired"}, ceilings ${report.summary.runtimeStageCeilingCollision ? "wired" : "not wired"})`);
  add();
  add(report.stageCoverage.runtimeUse.assessment);
  if (report.stageCoverage.stageCodeEvidence.parses) {
    add();
    add(`Stage-code evidence: ${report.stageCoverage.stageCodeEvidence.path} (${report.stageCoverage.stageCodeEvidence.bootDolStageCodeHitCount} boot.dol hits, ${report.stageCoverage.stageCodeEvidence.bootDolUniqueStageCodeCount} unique stage codes, ${report.stageCoverage.stageCodeEvidence.verifiedArenaNameMappingCount} verified arena-name mappings).`);
    add();
    add(report.stageCoverage.stageCodeEvidence.conclusion);
  }
  add();
  add("## Combat FX");
  add();
  add(`Projectile visual kind in sim state: ${report.combatFx.projectileVisualKindInState ? "yes" : "no"}`);
  add(`Projectile visual kind derived from borg profile: ${report.combatFx.projectileVisualKindDerivedFromProfile ? "yes" : "no"}`);
  add(`Projectile renderer uses exported FX textures: ${report.combatFx.rendererUsesExportedProjectileTextures ? "yes" : "no"}`);
  add();
  add(
    mdTable(report.combatFx.fxManifest.projectileTextures, [
      { title: "Projectile texture", value: (row) => row.publicPath },
      { title: "Exists", value: (row) => row.exists ? "yes" : "no" },
    ]),
  );
  add();
  add("## Battle HUD Asset Evidence");
  add();
  add(`Manifest: ${report.hudAssetEvidence.path}`);
  add(report.hudAssetEvidence.summary);
  add();
  add(
    mdTable(report.hudAssetEvidence.availableRows, [
      { title: "Asset", value: (row) => row.key },
      { title: "Source", value: (row) => row.source },
      { title: "Size", value: (row) => row.size },
      { title: "Confidence", value: (row) => row.confidence },
      { title: "Used in BattleHud", value: (row) => row.usedInBattleHud ? "yes" : "no" },
      { title: "Role", value: (row) => row.role },
    ]),
  );
  add();
  add(`as_icon public export: ${report.hudAssetEvidence.asIconPublicPath} (${report.hudAssetEvidence.asIconExists ? "exists" : "missing"}). It remains unwired in BattleHud because the HUD manifest classifies its battle-HUD role as low-confidence.`);
  add();
  add("Original HUD elements not available as discrete sprites:");
  add(
    mdTable(report.hudAssetEvidence.gameDrawnRows, [
      { title: "Element", value: (row) => row.key },
      { title: "Evidence", value: (row) => row.note },
    ]),
  );
  add();
  add("## Borg Animation Coverage");
  add();
  add(`Validator report: ${report.borgAnimationCoverage.path}`);
  add(`Runtime resolver refs: ${Object.values(report.borgAnimationCoverage.runtimeResolverRefs).join(", ")}`);
  add(`Animation indexes parsed: ${report.borgAnimationCoverage.indexesParsed}/${report.borgAnimationCoverage.indexesFound}; exported banks: ${report.borgAnimationCoverage.exportedBanks}; canonical slot checks: ${report.borgAnimationCoverage.canonicalSlotChecks}.`);
  add(`Direct matches: ${report.borgAnimationCoverage.directRuntimeMatches}; fallbacks: ${report.borgAnimationCoverage.runtimeFallbacks}; missing: ${report.borgAnimationCoverage.missingRuntimeMatches}; parse errors: ${report.borgAnimationCoverage.parseErrors}.`);
  add(`Fly/boost mapping: ${report.borgAnimationCoverage.boostFlyMapped ? "fly state resolves through exported boost labels" : "fly state is not proven to resolve through exported boost labels"}.`);
  add();
  add(
    mdTable(report.borgAnimationCoverage.slotRows, [
      { title: "Slot", value: (row) => row.slot },
      { title: "Direct", value: (row) => row.direct },
      { title: "Fallback", value: (row) => row.fallback },
      { title: "Missing", value: (row) => row.missing },
      { title: "Notes", value: (row) => row.notes },
    ]),
  );
  add();
  add("## Powerup / Item Runtime Gap");
  add();
  add(`Items/powerups in BattleState: ${report.powerupRuntimeGap.battleStateHasItems ? "yes" : "no"}`);
  add(`Runtime spawns item/drop/pickup entities: ${report.powerupRuntimeGap.battleRuntimeSpawnsDrops ? "yes" : "no"}`);
  add(`Evidence refs: ${Object.values(report.powerupRuntimeGap.evidenceRefs).join(", ")}`);
  add(`Asset leads: item model ARZ count ${report.powerupRuntimeGap.assetLeads.itemModelArzCount ?? "unknown"}, as_icon documented ${report.powerupRuntimeGap.assetLeads.asIconDocumented ? "yes" : "no"}, comhit documented ${report.powerupRuntimeGap.assetLeads.comhitDocumented ? "yes" : "no"}.`);
  add(report.powerupRuntimeGap.assessment);
  add();
  add("## Audio");
  add();
  add(`Audio package dependency: ${report.audioRuntime.audioPackageDependency ? "yes" : "no"}`);
  add(`Runtime imports audio manager: ${report.audioRuntime.runtimeImportsAudioManager ? "yes" : "no"}`);
  add(`Runtime queues menu/battle BGM: ${report.audioRuntime.runtimeQueuesBgm ? "yes" : "no"}`);
  add(`Runtime plays confirm/back/edit SFX: ${report.audioRuntime.runtimePlaysSfx ? "yes" : "no"}`);
  add();
  add(
    mdTable(report.audioRuntime.manifest.cueKeys, [
      { title: "Cue", value: (row) => row.key },
      { title: "Exists", value: (row) => row.exists ? "yes" : "no" },
    ]),
  );
  add();
  add(`Manifest counts: ${JSON.stringify(report.audioRuntime.manifest.counts)}`);
  add();
  add("## Challenge / Adventure / Story Risk");
  add();
  add(report.modeNamingRisks.finding);
  add();
  for (const evidence of report.modeNamingRisks.evidence) add(`- ${evidence}`);
  add();
  add("## Next Replacements");
  add();
  for (const item of report.nextMostUsefulReplacements) add(`- ${item}`);
  add();
  add("## Verification");
  add();
  add("```bash");
  add("rtk node scripts/audit-real-asset-coverage.mjs");
  add("rtk node -e \"JSON.parse(require('fs').readFileSync('research/asset-coverage/real-asset-coverage.json','utf8')); console.log('asset coverage json ok')\"");
  add("```");
  return `${lines.join("\n")}\n`;
}

const report = buildReport();
fs.mkdirSync(outDir, { recursive: true });
fs.writeFileSync(outJson, `${JSON.stringify(report, null, 2)}\n`);
fs.writeFileSync(outMd, renderMarkdown(report));

console.log(`asset coverage audit: screens ${report.summary.screens}, real-ui ${report.summary.screensUsingAnyRealExportedAsset}, handcoded ${report.summary.screensWithHandcodedSurfaceSignals}`);
console.log(`stage exports: ${report.summary.publicStagesCompleteVisual}/${report.summary.publicStagesTotal} complete visual; runtime fallback ${report.summary.runtimeStageFallback ?? "unknown"}`);
console.log(`wrote ${rel(outJson)}`);
console.log(`wrote ${rel(outMd)}`);
