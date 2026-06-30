#!/usr/bin/env node
import { mkdir, readdir, readFile, stat, writeFile } from "node:fs/promises";
import path from "node:path";

const repoRoot = process.cwd();
const outputDir = "research/asset-inventory";
const jsonOut = path.join(outputDir, "adventure-flow-ai.json");
const mdOut = path.join(outputDir, "adventure-flow-ai.md");

const paths = {
  stages: "packages/assets/data/stages.json",
  borgs: "packages/assets/data/borgs.json",
  missions: "packages/missions/src/index.ts",
  ai: "packages/ai/src/index.ts",
  game: "apps/game/src/main.ts",
  afsRoot: "user-data/GG4E/afs_data/root",
  discRoot: "user-data/GG4E/disc",
  bootDol: "user-data/GG4E/disc/sys/boot.dol",
  symbolMap: "research/symbols/GG4E-CSM-20220412.map",
  tracePlaybook: "research/traces/GG4E-dol-trace-playbook.md",
  publicStages: "apps/game/public/stages",
  publicModelsManifest: "apps/game/public/models/library/manifest.json",
};

function rel(file) {
  return file.replaceAll("\\", "/");
}

function abs(file) {
  return path.resolve(repoRoot, file);
}

async function readText(file) {
  return readFile(abs(file), "utf8");
}

async function readJson(file) {
  return JSON.parse(await readText(file));
}

async function statPath(file) {
  try {
    const s = await stat(abs(file));
    return { path: rel(file), exists: true, bytes: s.size };
  } catch {
    return { path: rel(file), exists: false, bytes: null };
  }
}

async function listDir(file) {
  try {
    return await readdir(abs(file));
  } catch {
    return [];
  }
}

async function listRecursive(dir) {
  const root = abs(dir);
  const out = [];

  async function walk(current) {
    let entries = [];
    try {
      entries = await readdir(current, { withFileTypes: true });
    } catch {
      return;
    }

    for (const entry of entries) {
      const full = path.join(current, entry.name);
      if (entry.isDirectory()) {
        await walk(full);
      } else if (entry.isFile()) {
        out.push(rel(path.relative(repoRoot, full)));
      }
    }
  }

  await walk(root);
  return out.sort();
}

function sample(values, limit = 12) {
  return [...values].sort((a, b) => String(a).localeCompare(String(b))).slice(0, limit);
}

function countBy(values, keyFn) {
  const counts = new Map();
  for (const value of values) {
    const key = keyFn(value);
    counts.set(key, (counts.get(key) ?? 0) + 1);
  }
  return Object.fromEntries([...counts.entries()].sort(([a], [b]) => String(a).localeCompare(String(b))));
}

function normalizeName(name) {
  return String(name)
    .normalize("NFKD")
    .replace(/[\u0300-\u036f]/g, "")
    .replace(/[^\p{Letter}\p{Number}]+/gu, " ")
    .trim()
    .replace(/\s+/g, " ")
    .toLocaleLowerCase();
}

function findLine(text, needle) {
  const lines = text.split(/\r?\n/);
  const index = lines.findIndex((line) => line.includes(needle));
  return index === -1 ? null : index + 1;
}

function refWithLine(file, text, needle) {
  const line = findLine(text, needle);
  return line ? `${rel(file)}:${line}` : rel(file);
}

function groupFiles(files, groups) {
  return groups.map((group) => {
    const matches = files.filter((file) => group.pattern.test(file));
    return {
      id: group.id,
      label: group.label,
      pattern: group.pattern.source,
      count: matches.length,
      samples: sample(matches),
      note: group.note,
    };
  });
}

function parseMap(text) {
  return text
    .split(/\r?\n/)
    .map((line, index) => {
      const match = /^([0-9a-f]{8})\s+([0-9a-f]{8})\s+([0-9a-f]{8})\s+\S+\s+(.+)$/i.exec(line.trim());
      if (!match) return null;
      return {
        address: `0x${match[1].toLowerCase()}`,
        addressValue: Number.parseInt(match[1], 16),
        size: `0x${match[2].toLowerCase()}`,
        name: match[4],
        sourceRef: `${rel(paths.symbolMap)}:${index + 1}`,
      };
    })
    .filter(Boolean);
}

function symbolByName(entries, nameNeedle) {
  return entries.find((entry) => entry.name.includes(nameNeedle)) ?? null;
}

function band(entries, start, end, limit = 10) {
  const startValue = Number.parseInt(start.replace(/^0x/i, ""), 16);
  const endValue = Number.parseInt(end.replace(/^0x/i, ""), 16);
  const matches = entries.filter((entry) => entry.addressValue >= startValue && entry.addressValue <= endValue);
  return {
    range: `${start}..${end}`,
    count: matches.length,
    samples: matches.slice(0, limit).map(({ address, size, name, sourceRef }) => ({ address, size, name, sourceRef })),
  };
}

function actorAssetsFor(rootFilesLower, rootFilesByLower, id) {
  const prefix = id.toLowerCase();
  const files = [...rootFilesLower]
    .filter((file) => file.startsWith(prefix))
    .map((file) => rootFilesByLower.get(file))
    .filter(Boolean)
    .sort();
  const has = (suffix) => rootFilesLower.has(`${prefix}${suffix}`);

  return {
    pzz: has(".pzz"),
    model: has("_mdl.arc"),
    modelVariants: files.filter((file) => /^pl[0-9a-f]{4}[bcgks]_mdl\.arc$/i.test(file)),
    data: has("data.bin"),
    hit: has("hit.bin"),
    mot: has("mot.bin"),
    fileCount: files.length,
    samples: sample(files, 10),
  };
}

function makeFlowSteps({ refs, sourceRefs }) {
  return [
    {
      step: "main menu -> Adventure select/load",
      originalEvidence: [
        "titles.tpl, as_icon.tpl, font_00.tpl, icon.bin",
        "vsel00_mdl.arc and vsel01_mdl.arc select-screen model archives",
        "Adventure Flow Trace snapshots requested in the trace playbook",
      ],
      sourceRefs: [
        sourceRefs.titles,
        sourceRefs.asIcon,
        refs.traceAdventureFlow,
        refs.gameOnlyAdventure,
        refs.gameStartsArena,
      ].filter(Boolean),
      currentRepoStatus: "Browser has an Adventure shell but no original menu/load state machine mapping.",
    },
    {
      step: "Adventure select/load -> force/player setup",
      originalEvidence: [
        "unitall_mdl.arc, plcmndata.bin, allbox.bin, gets.pzz, gets##_mdl.arc candidates",
        "cTeam::GetPlayer(int) named symbol and 0x80297538..0x802a5e70 team/player lookup band",
      ],
      sourceRefs: [
        sourceRefs.unitAll,
        sourceRefs.plCommon,
        refs.teamGetPlayer,
        refs.teamBandTrace,
        refs.gameAnimatedBorgs,
      ].filter(Boolean),
      currentRepoStatus: "Force selection is browser-local and only exposes verified animated exported borgs.",
    },
    {
      step: "force/player setup -> mission intro/load",
      originalEvidence: [
        "firstld.pzz, brif00_mdl.arc, entry00_mdl.arc, msg*.mdt and face assets",
        "stages.json mission rows provide names, arenas, enemy names, bosses, and confidence fields",
      ],
      sourceRefs: [
        sourceRefs.firstLoad,
        sourceRefs.briefing,
        sourceRefs.entry,
        refs.stagesFirstRow,
        refs.missionsResolveStage,
      ].filter(Boolean),
      currentRepoStatus: "Mission data resolves text/enemy names, but original intro/load asset sequencing is unmapped.",
    },
    {
      step: "mission intro/load -> battle HUD/gameplay",
      originalEvidence: [
        "st##_mdl.arc, st##.pzz, set####.arc, hit###.bin, comhit*.bin, bn####.tpl, face#### assets",
        "Dense action/state and death/swap DOL bands from trace playbook",
      ],
      sourceRefs: [
        sourceRefs.stage00,
        sourceRefs.set0000,
        sourceRefs.hit000,
        sourceRefs.comhit,
        refs.actionStateTrace,
        refs.deathSwapTrace,
        refs.gameNoCpuActors,
      ].filter(Boolean),
      currentRepoStatus: "Battle scene loads st00 exported DAE pieces and local G Red only; CPU actors, enemy force spawning, HUD semantics, death/swap, and original camera/control remain unmapped.",
    },
  ];
}

function makeMarkdown(inventory) {
  const lines = [];
  const add = (line = "") => lines.push(line);

  add("# Adventure Flow And CPU AI Inventory");
  add();
  add(`Generated by \`${inventory.generatedBy}\` on ${inventory.generatedAt}.`);
  add("Scope: Adventure flow only. Story-mode work is intentionally out of scope.");
  add();
  add("## Summary");
  add();
  add(`- Stage data: ${inventory.data.stages.count} rows from \`${inventory.data.stages.path}\`, ${inventory.data.stages.uniqueEnemyNames} unique enemy-name entries, unresolved placeholders: ${inventory.data.stages.unresolvedEnemyNames.join(", ") || "none"}.`);
  add(`- Borg data: ${inventory.data.borgs.count} rows from \`${inventory.data.borgs.path}\`; concrete Adventure enemy actors resolve to ${inventory.enemyForce.uniqueConcreteEnemies} borg ids.`);
  add(`- Extracted stage assets: ${inventory.extractedAssets.stageAssets.directStageArchives.pairsWithModelAndPzz} complete st##_mdl.arc/st##.pzz pairs, ${inventory.extractedAssets.stageAssets.setArchives.count} set####.arc files, ${inventory.extractedAssets.stageAssets.collisionBins.count} hit###.bin files.`);
  add(`- CPU actor files for concrete enemies: ${inventory.enemyForce.assetCoverage.model}/${inventory.enemyForce.uniqueConcreteEnemies} direct models, ${inventory.enemyForce.assetCoverage.pzz}/${inventory.enemyForce.uniqueConcreteEnemies} pzz archives, ${inventory.enemyForce.assetCoverage.mot}/${inventory.enemyForce.uniqueConcreteEnemies} MOT bins.`);
  add(`- Current public runtime export: stages ${inventory.currentRuntime.publicStageExport.stageDirs.join(", ") || "none"}; animated borg gate ${inventory.currentRuntime.browserGates.animatedBorgsRef}.`);
  add();
  add("## Required Flow Map");
  add();
  add("| Flow step | Original evidence | Current repo status | File refs |");
  add("| --- | --- | --- | --- |");
  for (const step of inventory.flow) {
    add(`| ${step.step} | ${step.originalEvidence.join("<br>")} | ${step.currentRepoStatus} | ${step.sourceRefs.map((ref) => `\`${ref}\``).join("<br>")} |`);
  }
  add();
  add("## Extracted Asset Groups");
  add();
  for (const group of inventory.extractedAssets.rootGroups) {
    add(`- ${group.label}: ${group.count} files. Samples: ${group.samples.map((file) => `\`${file}\``).join(", ") || "none"}.`);
  }
  add();
  add("## Enemy Force And CPU Actors");
  add();
  add(`Every concrete enemy name in \`${inventory.data.stages.path}\` resolves through \`${inventory.data.borgs.path}\`; only \`${inventory.data.stages.unresolvedEnemyNames.join("`, `") || "none"}\` is unresolved because it is a randomized placeholder.`);
  add(`Direct model missing for: ${inventory.enemyForce.missingDirectModel.map((actor) => `${actor.id} ${actor.name}`).join(", ") || "none"}.`);
  add(`MOT bins missing for ${inventory.enemyForce.missingMot.count} concrete enemy actors; samples: ${inventory.enemyForce.missingMot.samples.map((actor) => `${actor.id} ${actor.name}`).join(", ") || "none"}.`);
  add();
  add("## Likely DOL Anchors");
  add();
  for (const symbol of inventory.dolCandidates.namedSymbols) {
    add(`- ${symbol.name} at ${symbol.address}, size ${symbol.size}: ${symbol.why} (${symbol.sourceRef}).`);
  }
  for (const trace of inventory.dolCandidates.traceBands) {
    add(`- ${trace.range}: ${trace.use} (${trace.sourceRef}).`);
  }
  add("- Note: symbols named AIInit/AIStartDMA in the map are Audio Interface functions, not CPU player AI; the inventory excludes them from CPU-control candidates.");
  add();
  add("## Implementation Gaps");
  add();
  for (const gap of inventory.implementationGaps) {
    add(`- ${gap.area}: ${gap.finding} Refs: ${gap.fileRefs.map((ref) => `\`${ref}\``).join(", ")}.`);
  }
  add();
  add("## Verification");
  add();
  add("- Script emits this Markdown and `research/asset-inventory/adventure-flow-ai.json` from live repo files.");
  add("- JSON parse verification command: `rtk node -e \"JSON.parse(require('fs').readFileSync('research/asset-inventory/adventure-flow-ai.json','utf8')); console.log('json ok')\"`.");
  add("- Markdown cites repo-local files such as `packages/assets/data/stages.json`, `user-data/GG4E/afs_data/root/st00_mdl.arc`, `packages/ai/src/index.ts`, and `apps/game/src/main.ts`.");
  add();

  return `${lines.join("\n")}\n`;
}

const [
  stagesData,
  borgsData,
  missionsText,
  aiText,
  gameText,
  symbolMapText,
  traceText,
  rootFiles,
  discFiles,
  publicStageFiles,
  publicModelFiles,
] = await Promise.all([
  readJson(paths.stages),
  readJson(paths.borgs),
  readText(paths.missions),
  readText(paths.ai),
  readText(paths.game),
  readText(paths.symbolMap),
  readText(paths.tracePlaybook),
  listDir(paths.afsRoot),
  listRecursive(paths.discRoot),
  listRecursive(paths.publicStages),
  listRecursive("apps/game/public/models"),
]);

const stages = "stages" in stagesData ? stagesData.stages : stagesData;
const borgs = "borgs" in borgsData ? borgsData.borgs : borgsData;
const borgByName = new Map(borgs.map((borg) => [normalizeName(borg.name), borg]));
const rootFilesLower = new Set(rootFiles.map((file) => file.toLowerCase()));
const rootFilesByLower = new Map(rootFiles.map((file) => [file.toLowerCase(), file]));
const mapEntries = parseMap(symbolMapText);

const uniqueEnemyNames = sample(new Set(stages.flatMap((stage) => stage.enemies)), Number.MAX_SAFE_INTEGER);
const enemyRows = uniqueEnemyNames.map((name) => ({ name, borg: borgByName.get(normalizeName(name)) ?? null }));
const concreteEnemyRows = enemyRows.filter((row) => row.borg);
const unresolvedEnemyNames = enemyRows.filter((row) => !row.borg).map((row) => row.name);
const actorRows = concreteEnemyRows.map((row) => ({
  name: row.name,
  id: row.borg.id,
  borgName: row.borg.name,
  energy: row.borg.energy ?? null,
  assets: actorAssetsFor(rootFilesLower, rootFilesByLower, row.borg.id),
}));

const assetCoverage = {
  pzz: actorRows.filter((actor) => actor.assets.pzz).length,
  model: actorRows.filter((actor) => actor.assets.model).length,
  data: actorRows.filter((actor) => actor.assets.data).length,
  hit: actorRows.filter((actor) => actor.assets.hit).length,
  mot: actorRows.filter((actor) => actor.assets.mot).length,
};

const stageArchiveCodes = new Map();
for (const file of rootFiles) {
  const match = /^st([0-9a-f]{2})(?:(_mdl\.arc)|(\.pzz))$/i.exec(file);
  if (!match) continue;
  const code = match[1].toLowerCase();
  const item = stageArchiveCodes.get(code) ?? { code: `st${code}`, model: false, pzz: false };
  if (match[2]) item.model = true;
  if (match[3]) item.pzz = true;
  stageArchiveCodes.set(code, item);
}

const setStages = countBy(
  rootFiles.filter((file) => /^set[0-9a-f]{4}\.arc$/i.test(file)),
  (file) => file.slice(3, 5).toLowerCase(),
);
const hitStages = countBy(
  rootFiles.filter((file) => /^hit[0-9a-f]{3}\.bin$/i.test(file)),
  (file) => file.slice(3, 5).toLowerCase(),
);

const rootGroups = groupFiles(rootFiles, [
  {
    id: "mainMenuSelect",
    label: "main menu / Adventure select candidates",
    pattern: /^(titles|as_icon|font_00|icon|vsel00_mdl|vsel01_mdl)\.(tpl|bin|arc)$/i,
    note: "Menu/select textures and select-screen models.",
  },
  {
    id: "missionIntroLoad",
    label: "mission intro / load candidates",
    pattern: /^(firstld|brif00_mdl|entry00_mdl|msg00|msg01|mc_msg00|nm_msg|sh_msg|tr_msg)\.(pzz|arc|mdt)$/i,
    note: "Load, briefing, entry, and message archives.",
  },
  {
    id: "hudTextures",
    label: "battle HUD / portrait / banner candidates",
    pattern: /^(bn[0-9a-f]{4}|face[0-9a-f]{4}|as_icon|font_00|arrow_mdl|comhit|comhit2|cmn_data)\.(tpl|arc|bin|pzz)$/i,
    note: "HUD banners, portraits, fonts/icons, targeting arrow, and common battle hit data.",
  },
  {
    id: "battleStages",
    label: "battle stage model/collision/set candidates",
    pattern: /^(st[0-9a-f]{2}(_mdl\.arc|\.pzz)|set[0-9a-f]{4}\.arc|hit[0-9a-f]{3}\.bin)$/i,
    note: "Arena archives, object set archives, and collision bins.",
  },
  {
    id: "stageVariants",
    label: "stage variant ARZ candidates",
    pattern: /^st[cfms][0-9a-f]{2}_mdl\.arz$/i,
    note: "Compressed stage/scene variants that need separate decoding before use.",
  },
  {
    id: "cpuActors",
    label: "CPU actor borg asset candidates",
    pattern: /^pl[0-9a-f]{4}/i,
    note: "Borg pzz/model/data/hit/MOT files used by player and CPU-controlled actors.",
  },
  {
    id: "forceCollection",
    label: "force setup / collection candidates",
    pattern: /^(unitall_mdl|plcmndata|allbox|gets|gets[0-9]{2}_mdl)\.(arc|bin|pzz)$/i,
    note: "Roster, common player data, collection/get assets.",
  },
]);

const sourceRefs = {
  titles: "user-data/GG4E/afs_data/root/titles.tpl",
  asIcon: "user-data/GG4E/afs_data/root/as_icon.tpl",
  unitAll: "user-data/GG4E/afs_data/root/unitall_mdl.arc",
  plCommon: "user-data/GG4E/afs_data/root/plcmndata.bin",
  firstLoad: "user-data/GG4E/afs_data/root/firstld.pzz",
  briefing: "user-data/GG4E/afs_data/root/brif00_mdl.arc",
  entry: "user-data/GG4E/afs_data/root/entry00_mdl.arc",
  stage00: "user-data/GG4E/afs_data/root/st00_mdl.arc",
  set0000: "user-data/GG4E/afs_data/root/set0000.arc",
  hit000: "user-data/GG4E/afs_data/root/hit000.bin",
  comhit: "user-data/GG4E/afs_data/root/comhit.bin",
};

const namedSymbols = [
  {
    needle: "cTeam::GetPlayer(int)",
    why: "team/player lookup anchor for resolving Adventure participants and CPU target ownership",
  },
  {
    needle: "cPlayer::ClearSwapControllerTimer(void)",
    why: "player swap/death-transition anchor needed for ordered-force spawning",
  },
  {
    needle: "SaveLoad::DidGameIDChange(void)",
    why: "save/load boundary candidate for Adventure select/load proof",
  },
  {
    needle: "gnt4-HSD_Randi-bl",
    why: "random/reward helper to trace only around GET or randomized enemy-force selection",
  },
]
  .map((item) => {
    const symbol = symbolByName(mapEntries, item.needle);
    return symbol ? { ...symbol, why: item.why } : null;
  })
  .filter(Boolean)
  .map(({ address, size, name, sourceRef, why }) => ({ address, size, name, sourceRef, why }));

const refs = {
  stagesFirstRow: `${rel(paths.stages)}:${findLine(await readText(paths.stages), '"stage": 1') ?? 1}`,
  missionsResolveStage: refWithLine(paths.missions, missionsText, "export function resolveAdventureStage"),
  missionsEnemyEnergy: refWithLine(paths.missions, missionsText, "enemyForceEnergy: enemies.reduce"),
  aiExportEmpty: refWithLine(paths.ai, aiText, "export {};"),
  gameStartsArena: refWithLine(paths.game, gameText, 'let screen: Screen = "arena"'),
  gameDefaultStage: refWithLine(paths.game, gameText, "const DEFAULT_STAGE_ID"),
  gameStageModelCount: refWithLine(paths.game, gameText, "const DEFAULT_STAGE_MODEL_COUNT"),
  gameAnimatedBorgs: refWithLine(paths.game, gameText, "const ANIMATED_BORGS"),
  gameLoadStage: refWithLine(paths.game, gameText, "async function loadStage"),
  gameNoCpuActors: refWithLine(paths.game, gameText, "No CPU actors spawned"),
  gameEnemyForceTextOnly: refWithLine(paths.game, gameText, "Enemy force:"),
  gameOnlyAdventure: refWithLine(paths.game, gameText, "Only Adventure is enabled"),
  traceAdventureFlow: refWithLine(paths.tracePlaybook, traceText, "## Adventure Flow Trace"),
  actionStateTrace: refWithLine(paths.tracePlaybook, traceText, "0x8005ec04..0x800660b8"),
  deathSwapTrace: refWithLine(paths.tracePlaybook, traceText, "0x80281c38..0x80281e60"),
  teamBandTrace: refWithLine(paths.tracePlaybook, traceText, "0x80297538..0x802a5e70"),
  teamGetPlayer: namedSymbols.find((symbol) => symbol.name.includes("cTeam::GetPlayer"))?.sourceRef,
};

const publicStagesPrefix = `${rel(paths.publicStages)}/`;
const publicStageDirs = [
  ...new Set(
    publicStageFiles
      .filter((file) => file.startsWith(publicStagesPrefix))
      .map((file) => file.slice(publicStagesPrefix.length).split("/")[0])
      .filter(Boolean),
  ),
].sort();
const inventory = {
  generatedBy: rel("scripts/inventory-adventure-flow.mjs"),
  generatedAt: new Date().toISOString(),
  scope: "Adventure flow and CPU AI mapping only; no story-mode proposal or fake UI work.",
  sources: {
    data: await Promise.all([statPath(paths.stages), statPath(paths.borgs), statPath(paths.missions)]),
    extracted: await Promise.all([statPath(paths.afsRoot), statPath(paths.discRoot), statPath(paths.bootDol)]),
    reverseEngineering: await Promise.all([statPath(paths.symbolMap), statPath(paths.tracePlaybook)]),
    currentRuntime: await Promise.all([statPath(paths.ai), statPath(paths.game), statPath(paths.publicStages), statPath(paths.publicModelsManifest)]),
  },
  data: {
    stages: {
      path: rel(paths.stages),
      metaMode: stagesData.meta?.mode ?? null,
      metaSource: stagesData.meta?.source ?? null,
      count: stages.length,
      first: stages[0],
      last: stages.at(-1),
      confidenceCounts: countBy(stages, (stage) => stage.confidence ?? "unknown"),
      uniqueArenaCount: new Set(stages.map((stage) => stage.arena)).size,
      uniqueArenas: sample(new Set(stages.map((stage) => stage.arena)), 20),
      uniqueEnemyNames: uniqueEnemyNames.length,
      unresolvedEnemyNames,
    },
    borgs: {
      path: rel(paths.borgs),
      count: borgs.length,
      hasModelCount: borgs.filter((borg) => borg.hasModel === true || Boolean(borg.model)).length,
      hasAnimCount: borgs.filter((borg) => borg.hasAnim === true || Boolean(borg.anim)).length,
    },
    missionsPackage: {
      path: rel(paths.missions),
      resolvesEnemyNames: refs.missionsResolveStage,
      enemyForceEnergySum: refs.missionsEnemyEnergy,
      limitation: "Resolves guide/data rows to borg stats; it does not map original Adventure menus, load sequencing, CPU controller ownership, or battle runtime state.",
    },
  },
  extractedAssets: {
    root: {
      path: rel(paths.afsRoot),
      fileCount: rootFiles.length,
    },
    rootGroups,
    stageAssets: {
      directStageArchives: {
        count: [...stageArchiveCodes.values()].length,
        pairsWithModelAndPzz: [...stageArchiveCodes.values()].filter((item) => item.model && item.pzz).length,
        codes: sample([...stageArchiveCodes.values()].map((item) => item.code), 80),
      },
      setArchives: {
        count: rootFiles.filter((file) => /^set[0-9a-f]{4}\.arc$/i.test(file)).length,
        byStageCode: setStages,
      },
      collisionBins: {
        count: rootFiles.filter((file) => /^hit[0-9a-f]{3}\.bin$/i.test(file)).length,
        byStageCode: hitStages,
      },
      stageVariantArz: {
        count: rootFiles.filter((file) => /^st[cfms][0-9a-f]{2}_mdl\.arz$/i.test(file)).length,
        samples: sample(rootFiles.filter((file) => /^st[cfms][0-9a-f]{2}_mdl\.arz$/i.test(file))),
      },
    },
    introLoadHud: {
      mainMenuSelect: rootGroups.find((group) => group.id === "mainMenuSelect"),
      missionIntroLoad: rootGroups.find((group) => group.id === "missionIntroLoad"),
      hudTextures: rootGroups.find((group) => group.id === "hudTextures"),
      forceCollection: rootGroups.find((group) => group.id === "forceCollection"),
    },
    disc: {
      path: rel(paths.discRoot),
      fileCount: discFiles.length,
      bootDol: await statPath(paths.bootDol),
      samples: sample(discFiles),
    },
  },
  enemyForce: {
    sourceStageData: rel(paths.stages),
    sourceBorgData: rel(paths.borgs),
    uniqueEnemyNames: uniqueEnemyNames.length,
    uniqueConcreteEnemies: actorRows.length,
    unresolvedEnemyNames,
    assetCoverage,
    missingDirectModel: actorRows
      .filter((actor) => !actor.assets.model)
      .map(({ id, name, assets }) => ({ id, name, hasPzz: assets.pzz, samples: assets.samples })),
    missingMot: {
      count: actorRows.filter((actor) => !actor.assets.mot).length,
      samples: actorRows
        .filter((actor) => !actor.assets.mot)
        .slice(0, 20)
        .map(({ id, name }) => ({ id, name })),
    },
    actorSamples: actorRows.slice(0, 20),
  },
  dolCandidates: {
    symbolMap: rel(paths.symbolMap),
    tracePlaybook: rel(paths.tracePlaybook),
    namedSymbols,
    traceBands: [
      {
        range: "0x8005ec04..0x800660b8",
        use: "dense action/state handlers touching active borg state byte +0x544; likely CPU/player action-control proof point",
        sourceRef: refs.actionStateTrace,
      },
      {
        range: "0x800660b8..0x80068004",
        use: "action/helper cluster adjacent to dense state handlers",
        sourceRef: refWithLine(paths.tracePlaybook, traceText, "0x800660b8..0x80068004"),
      },
      {
        range: "0x80281c38..0x80281e60",
        use: "death/swap lead; calls cPlayer::ClearSwapControllerTimer and should anchor ordered-force replacement",
        sourceRef: refs.deathSwapTrace,
      },
      {
        range: "0x80297538..0x802a5e70",
        use: "team/player lookup band with cTeam::GetPlayer callers; likely CPU target/team ownership path",
        sourceRef: refs.teamBandTrace,
      },
    ],
    mapBands: {
      actionStateHandlers: band(mapEntries, "0x8005ec04", "0x800660b8"),
      deathSwap: band(mapEntries, "0x80281c38", "0x80281e60"),
      teamPlayerLookup: band(mapEntries, "0x80297538", "0x802a5e70"),
    },
    excludedAmbiguousSymbols: [
      {
        pattern: "AIInit/AIStartDMA/AISetStream*",
        reason: "GameCube Audio Interface symbols, not CPU player AI.",
      },
    ],
  },
  currentRuntime: {
    aiPackage: {
      path: rel(paths.ai),
      emptyExportRef: refs.aiExportEmpty,
    },
    browserGates: {
      path: rel(paths.game),
      screenStartsArenaRef: refs.gameStartsArena,
      defaultStageRef: refs.gameDefaultStage,
      stageModelCountRef: refs.gameStageModelCount,
      animatedBorgsRef: refs.gameAnimatedBorgs,
      noCpuActorsRef: refs.gameNoCpuActors,
      enemyForceTextOnlyRef: refs.gameEnemyForceTextOnly,
    },
    publicStageExport: {
      path: rel(paths.publicStages),
      stageDirs: publicStageDirs.filter((dir) => /^st/i.test(dir)),
      fileCount: publicStageFiles.length,
      daeCount: publicStageFiles.filter((file) => /\.dae$/i.test(file)).length,
      collisionBinCount: publicStageFiles.filter((file) => /\/collision\/.*\.bin$/i.test(file)).length,
      setArcCount: publicStageFiles.filter((file) => /\/set\/.*\.arc$/i.test(file)).length,
    },
    publicModelExport: {
      fileCount: publicModelFiles.length,
      manifest: await statPath(paths.publicModelsManifest),
    },
  },
  flow: makeFlowSteps({ refs, sourceRefs }),
  implementationGaps: [
    {
      area: "Adventure menu/load flow",
      finding: "The browser starts in arena and offers a local Adventure shell; original main-menu to Adventure select/load state transitions are not mapped.",
      fileRefs: [refs.gameStartsArena, refs.gameOnlyAdventure, refs.traceAdventureFlow].filter(Boolean),
    },
    {
      area: "Stage selection to arena asset mapping",
      finding: "Runtime hard-codes st00 and 40 DAE pieces; extracted root has many st##_mdl.arc/st##.pzz pairs but no verified arena-name to stage-code table in source.",
      fileRefs: [refs.gameDefaultStage, refs.gameStageModelCount, sourceRefs.stage00, rel(paths.stages)].filter(Boolean),
    },
    {
      area: "Enemy force spawning",
      finding: "Mission package computes enemy names and energy, while the browser renders enemy force as text only and does not spawn ordered enemy borgs.",
      fileRefs: [refs.missionsResolveStage, refs.missionsEnemyEnergy, refs.gameEnemyForceTextOnly].filter(Boolean),
    },
    {
      area: "CPU AI behavior",
      finding: "@gf/ai is an empty export and the browser explicitly avoids CPU actors until model, MOT, and AI path are verified.",
      fileRefs: [refs.aiExportEmpty, refs.gameNoCpuActors, refs.actionStateTrace, refs.teamBandTrace].filter(Boolean),
    },
    {
      area: "Force/player ownership and death/swap",
      finding: "Original team/player lookup and player swap/death anchors are identified, but not connected to runtime force order, respawn, or CPU ownership.",
      fileRefs: [refs.teamGetPlayer, refs.deathSwapTrace, refs.gameAnimatedBorgs].filter(Boolean),
    },
    {
      area: "Mission intro/load and HUD semantics",
      finding: "Extracted briefing/load/HUD candidate assets exist, but current HUD is handwritten status text rather than mapped original Adventure intro/load/HUD assets.",
      fileRefs: [sourceRefs.firstLoad, sourceRefs.briefing, sourceRefs.comhit, refs.gameNoCpuActors].filter(Boolean),
    },
  ],
};

await mkdir(abs(outputDir), { recursive: true });
await writeFile(abs(jsonOut), `${JSON.stringify(inventory, null, 2)}\n`);
await writeFile(abs(mdOut), makeMarkdown(inventory));

console.log(`wrote ${rel(jsonOut)}`);
console.log(`wrote ${rel(mdOut)}`);
console.log(`Adventure stages: ${inventory.data.stages.count}`);
console.log(`Concrete enemy actors: ${inventory.enemyForce.uniqueConcreteEnemies}`);
console.log(`Direct enemy models: ${inventory.enemyForce.assetCoverage.model}/${inventory.enemyForce.uniqueConcreteEnemies}`);
console.log(`Enemy MOT bins: ${inventory.enemyForce.assetCoverage.mot}/${inventory.enemyForce.uniqueConcreteEnemies}`);
