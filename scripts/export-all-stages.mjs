#!/usr/bin/env node
import crypto from "node:crypto";
import fs from "node:fs";
import { mkdir, writeFile } from "node:fs/promises";
import path from "node:path";
import { spawnSync } from "node:child_process";

const REGIONS = new Set(["GG4E", "GG4J", "GG4P"]);
const DEFAULT_REGION = "GG4E";
const DEFAULT_PLAN_JSON = path.join("research", "asset-inventory", "stage-export-plan.json");
const DEFAULT_PLAN_MD = path.join("research", "asset-inventory", "stage-export-plan.md");
const EXPORT_ASSETS_SCRIPT = path.join("scripts", "export-stage-assets.mjs");
const EXPORT_HSD_SCRIPT = path.join("scripts", "export-stage-hsd.mjs");
const VISUAL_EXPORT_SUMMARY = "export-summary.json";

const repoRoot = process.cwd();
const options = parseArgs(process.argv.slice(2));

if (options.help) usage(0);

let plan = buildPlan();
let executedExports = [];

if (options.export) {
  const jobs = selectExportJobs(plan);
  if (jobs.length === 0) {
    console.log("export-all-stages: no safe export jobs matched the filters");
  }
  for (const job of jobs) {
    await runStageExport(job);
    executedExports.push(job.stageId);
  }
  plan = buildPlan({ executedExports });
}

if (options.refreshManifests || executedExports.length > 0) {
  const stageIds = new Set(executedExports);
  if (options.refreshManifests) {
    for (const record of selectManifestRefreshRecords(plan)) {
      stageIds.add(record.id);
    }
  }
  const refreshed = [];
  for (const stageId of stageIds) {
    const record = plan.stages.find((stage) => stage.id === stageId);
    if (!record?.public?.exists) continue;
    await writeVerifiedStageManifest(record);
    refreshed.push(stageId);
  }
  if (refreshed.length > 0) {
    plan = buildPlan({ executedExports, refreshedManifests: refreshed });
  }
}

await writePlanFiles(plan);
printSummary(plan);

function parseArgs(args) {
  const parsed = {
    region: DEFAULT_REGION,
    export: false,
    proof: false,
    forceExisting: false,
    refreshManifests: false,
    stageCodes: new Set(),
    limit: null,
    planJson: DEFAULT_PLAN_JSON,
    planMd: DEFAULT_PLAN_MD,
    help: false,
  };
  const positionals = [];

  for (let i = 0; i < args.length; i++) {
    const arg = args[i];
    if (arg === "--help" || arg === "-h") {
      parsed.help = true;
    } else if (arg === "--dry-run" || arg === "--plan") {
      parsed.export = false;
    } else if (arg === "--export") {
      parsed.export = true;
    } else if (arg === "--proof") {
      parsed.proof = true;
      parsed.limit ??= 1;
    } else if (arg === "--force-existing") {
      parsed.forceExisting = true;
    } else if (arg === "--refresh-manifests") {
      parsed.refreshManifests = true;
    } else if (arg === "--stage") {
      addStageCodes(parsed.stageCodes, requiredValue(args, ++i, arg));
    } else if (arg.startsWith("--stage=")) {
      addStageCodes(parsed.stageCodes, arg.slice("--stage=".length));
    } else if (arg === "--limit") {
      parsed.limit = parsePositiveInt(requiredValue(args, ++i, arg), arg);
    } else if (arg.startsWith("--limit=")) {
      parsed.limit = parsePositiveInt(arg.slice("--limit=".length), "--limit");
    } else if (arg === "--plan-json") {
      parsed.planJson = requiredValue(args, ++i, arg);
    } else if (arg.startsWith("--plan-json=")) {
      parsed.planJson = arg.slice("--plan-json=".length);
    } else if (arg === "--plan-md") {
      parsed.planMd = requiredValue(args, ++i, arg);
    } else if (arg.startsWith("--plan-md=")) {
      parsed.planMd = arg.slice("--plan-md=".length);
    } else if (arg.startsWith("--")) {
      fail(`unknown option "${arg}"`);
    } else {
      positionals.push(arg);
    }
  }

  for (const positional of positionals) {
    const upper = positional.toUpperCase();
    if (REGIONS.has(upper)) {
      parsed.region = upper;
    } else {
      addStageCodes(parsed.stageCodes, positional);
    }
  }

  return parsed;
}

function usage(code) {
  const stream = code === 0 ? process.stdout : process.stderr;
  stream.write(`usage: node scripts/export-all-stages.mjs [GG4E|GG4J|GG4P] [options]

Discovers source st##_mdl.arc/st##.pzz pairs, compares browser public stage
exports, and writes research/asset-inventory/stage-export-plan.{json,md}.

Options:
  --plan, --dry-run          write plan artifacts only (default)
  --export                  run existing single-stage export tools for selected jobs
  --proof                   select one safe missing proof stage
  --stage <id[,id...]>      filter to stage ids or codes, for example st01,02,ff
  --limit <n>               cap selected export jobs
  --force-existing          allow exporters to overwrite an existing stage folder
  --refresh-manifests       write verified manifest.json for public stage folders
  --plan-json <path>        JSON output path
  --plan-md <path>          Markdown output path
`);
  process.exit(code);
}

function buildPlan({ executedExports = [], refreshedManifests = [] } = {}) {
  const sourceRoot = path.resolve(repoRoot, "user-data", options.region, "afs_data", "root");
  const publicRoot = path.resolve(repoRoot, "apps", "game", "public", "stages");
  const sourceStages = discoverSourceStages(sourceRoot);
  const publicStageIds = discoverPublicStageIds(publicRoot);
  const stageIds = [...new Set([...sourceStages.map((stage) => stage.id), ...publicStageIds])].sort(compareStageIds);
  const records = stageIds.map((stageId) => {
    const source = sourceStages.find((stage) => stage.id === stageId) ?? missingSourceRecord(stageId, sourceRoot);
    const publicExport = inspectPublicStage(publicRoot, source);
    return buildStageRecord(source, publicExport);
  });
  const missingExportStages = records.filter((stage) => stage.export.needsExport);
  const safeMissingStages = missingExportStages.filter((stage) => stage.export.safeToRunExistingTools);
  const proofCandidate = chooseProofCandidate(records);
  const selectedForCommand = selectStageRecordsForCommand(records);
  const commandStageIds = selectedForCommand.map((stage) => stage.id);
  const adventureFlow = summarizeAdventureFlow();

  return {
    generatedBy: "scripts/export-all-stages.mjs",
    generatedAt: new Date().toISOString(),
    region: options.region,
    mode: options.export ? "export" : "dry-run",
    scope: "Direct stage ARC/PZZ export coverage only; does not edit browser runtime source or infer arena-name mappings.",
    sources: {
      assetRoot: relRepo(sourceRoot),
      publicStages: relRepo(publicRoot),
      singleStageExporters: [EXPORT_ASSETS_SCRIPT, EXPORT_HSD_SCRIPT],
      batchVisualExporter: "embedded stage-batch-exporter in scripts/export-all-stages.mjs",
      adventureFlow,
    },
    summary: {
      sourceStageArchiveCount: sourceStages.length,
      sourcePairsWithModelAndPzz: sourceStages.filter((stage) => stage.source.hasStageArc && stage.source.hasStagePzz).length,
      publicStageFolderCount: publicStageIds.length,
      publicStageWithAnyDaeCount: records.filter((stage) => stage.public.visual.hasDaePieces).length,
      verifiedVisualStageCount: records.filter((stage) => stage.public.visual.hasCompleteDaeExport).length,
      exportedCollisionHitStageCount: records.filter((stage) => stage.public.collision.hasHitFiles).length,
      sourceCompleteCollisionTripletCount: records.filter((stage) => stage.source.collision.hasCompleteHitTriplet).length,
      sourceAnyCollisionHitCount: records.filter((stage) => stage.source.collision.hasHitFiles).length,
      sourceAnySetArcCount: records.filter((stage) => stage.source.sets.files.length > 0).length,
      missingOrPartialExportCount: missingExportStages.length,
      safeMissingExportCount: safeMissingStages.length,
      proofCandidate: proofCandidate?.id ?? null,
      executedExports,
      refreshedManifests,
    },
    exportPlan: {
      defaultIsDryRun: true,
      selectedStageIds: commandStageIds,
      allMissingOrPartialStageIds: missingExportStages.map((stage) => stage.id),
      safeMissingStageIds: safeMissingStages.map((stage) => stage.id),
      skippedUnsafeExistingStageIds: missingExportStages
        .filter((stage) => !stage.export.safeToRunExistingTools)
        .map((stage) => stage.id),
      proofCommand: proofCandidate ? commandForExportAll([proofCandidate.id], "--proof") : null,
      selectedCommand: commandStageIds.length > 0 ? commandForExportAll(commandStageIds) : null,
      allSafeMissingCommand: safeMissingStages.length > 0 ? commandForExportAll(safeMissingStages.map((stage) => stage.id)) : null,
      exactPerStageCommands: missingExportStages.map((stage) => stage.export.commands),
    },
    stages: records,
    notes: [
      "The legacy visual exporter writes every model texture into one directory; this orchestrator isolates per-model texture writes and publishes a clean model folder from a single run.",
      "Visual coverage means non-empty model_*.dae files exist in apps/game/public/stages/<stage>/model.",
      "Complete visual coverage requires all expected non-null model slots from the current export summary, no exporter failures, and no zero-byte DAE files.",
      "Collision coverage means hit*.bin files are present; hit body records are copied but not decoded here.",
      "Adventure flow currently lists arena names, but the repo does not contain a verified arena-name to st## table.",
    ],
  };
}

function discoverSourceStages(sourceRoot) {
  if (!fs.existsSync(sourceRoot)) fail(`missing source root: ${relRepo(sourceRoot)}`);
  const files = fs.readdirSync(sourceRoot);
  const codes = new Set();
  for (const file of files) {
    const match = file.match(/^st([0-9a-f]{2})(?:_mdl\.arc|\.pzz)$/i);
    if (match) codes.add(match[1].toLowerCase());
  }

  return [...codes].sort(compareStageCodes).map((code) => {
    const id = `st${code}`;
    const stageArcName = `${id}_mdl.arc`;
    const stagePzzName = `${id}.pzz`;
    const hitFiles = files.filter((file) => new RegExp(`^hit${code}[0-9a-f]\\.bin$`, "i").test(file)).sort();
    const setFiles = files.filter((file) => new RegExp(`^set${code}[0-9a-f]{2}\\.arc$`, "i").test(file)).sort();
    const expectedHitFiles = [`hit${code}0.bin`, `hit${code}1.bin`, `hit${code}2.bin`];
    const expectedSetFiles = [`set${code}00.arc`, `set${code}01.arc`, `set${code}02.arc`, `set${code}03.arc`];
    const stageArc = fileInfo(path.join(sourceRoot, stageArcName));
    const stagePzz = fileInfo(path.join(sourceRoot, stagePzzName));

    return {
      id,
      code,
      sourceRoot: relRepo(sourceRoot),
      source: {
        hasStageArc: Boolean(stageArc),
        hasStagePzz: Boolean(stagePzz),
        hasModelAndPzzPair: Boolean(stageArc && stagePzz),
        stageArc,
        stagePzz,
        collision: {
          hasHitFiles: hitFiles.length > 0,
          hasCompleteHitTriplet: expectedHitFiles.every((file) => hitFiles.includes(file)),
          expectedHitFiles,
          files: hitFiles.map((file) => fileInfo(path.join(sourceRoot, file))),
          missingExpectedHitFiles: expectedHitFiles.filter((file) => !hitFiles.includes(file)),
        },
        sets: {
          expectedExporterFiles: expectedSetFiles,
          files: setFiles.map((file) => fileInfo(path.join(sourceRoot, file))),
          filesCopiedByCurrentTool: setFiles.filter((file) => expectedSetFiles.includes(file)),
          filesNotCopiedByCurrentTool: setFiles.filter((file) => !expectedSetFiles.includes(file)),
        },
      },
    };
  });
}

function missingSourceRecord(stageId, sourceRoot) {
  const code = normalizeStageCode(stageId);
  return {
    id: `st${code}`,
    code,
    sourceRoot: relRepo(sourceRoot),
    source: {
      hasStageArc: false,
      hasStagePzz: false,
      hasModelAndPzzPair: false,
      stageArc: null,
      stagePzz: null,
      collision: {
        hasHitFiles: false,
        hasCompleteHitTriplet: false,
        expectedHitFiles: [`hit${code}0.bin`, `hit${code}1.bin`, `hit${code}2.bin`],
        files: [],
        missingExpectedHitFiles: [`hit${code}0.bin`, `hit${code}1.bin`, `hit${code}2.bin`],
      },
      sets: {
        expectedExporterFiles: [`set${code}00.arc`, `set${code}01.arc`, `set${code}02.arc`, `set${code}03.arc`],
        files: [],
        filesCopiedByCurrentTool: [],
        filesNotCopiedByCurrentTool: [],
      },
    },
  };
}

function discoverPublicStageIds(publicRoot) {
  if (!fs.existsSync(publicRoot)) return [];
  return fs
    .readdirSync(publicRoot, { withFileTypes: true })
    .filter((entry) => entry.isDirectory() && /^st[0-9a-f]{2}$/i.test(entry.name))
    .map((entry) => entry.name.toLowerCase())
    .sort(compareStageIds);
}

function inspectPublicStage(publicRoot, sourceRecord) {
  const stageDir = path.join(publicRoot, sourceRecord.id);
  const rawDir = path.join(stageDir, "raw");
  const modelDir = path.join(stageDir, "model");
  const collisionDir = path.join(stageDir, "collision");
  const setDir = path.join(stageDir, "set");
  const rawArc = fileInfo(path.join(rawDir, `${sourceRecord.id}_mdl.arc`));
  const rawPzz = fileInfo(path.join(rawDir, `${sourceRecord.id}.pzz`));
  const daeInfos = listFileInfos(modelDir, (file) => /^model_[0-9]+\.dae$/i.test(file));
  const textureInfos = listFileInfos(modelDir, (file) => /\.(png|tpl)$/i.test(file));
  const hitInfos = listFileInfos(collisionDir, (file) => /^hit[0-9a-f]{3}\.bin$/i.test(file));
  const setInfos = listFileInfos(setDir, (file) => /^set[0-9a-f]{4}\.arc$/i.test(file));
  const manifestPath = path.join(stageDir, "manifest.json");
  const manifest = readJsonIfExists(manifestPath);
  const exportSummaryPath = path.join(modelDir, VISUAL_EXPORT_SUMMARY);
  const exportSummary = readJsonIfExists(exportSummaryPath);
  const sourceHitNames = sourceRecord.source.collision.files.map((file) => path.basename(file.path));
  const publicHitNames = hitInfos.map((file) => path.basename(file.path));
  const modelIndices = daeInfos
    .map((file) => path.basename(file.path).match(/^model_([0-9]+)\.dae$/i))
    .filter(Boolean)
    .map((match) => Number(match[1]))
    .sort((a, b) => a - b);
  const maxModelIndex = modelIndices.length > 0 ? modelIndices.at(-1) : null;
  const missingModelIndices =
    maxModelIndex == null ? [] : range(0, maxModelIndex).filter((index) => !modelIndices.includes(index));
  const zeroByteDaeFiles = daeInfos.filter((file) => file.bytes === 0).map((file) => file.path);
  const expectedDaeIndices = expectedDaeIndicesFromSummary(exportSummary.value, modelIndices);
  const missingExpectedDaeIndices = expectedDaeIndices.filter((index) => !modelIndices.includes(index));
  const unexpectedDaeIndices = modelIndices.filter((index) => expectedDaeIndices.length > 0 && !expectedDaeIndices.includes(index));
  const failedModelIndices = numericArray(exportSummary.value?.failedModelIndices);
  const skippedNullRootJointIndices = numericArray(exportSummary.value?.skippedNullRootJointIndices);
  const hasCompleteDaeExport =
    daeInfos.length > 0 &&
    zeroByteDaeFiles.length === 0 &&
    missingExpectedDaeIndices.length === 0 &&
    unexpectedDaeIndices.length === 0 &&
    exportSummary.ok &&
    exportSummary.value?.complete === true &&
    failedModelIndices.length === 0;

  return {
    exists: fs.existsSync(stageDir),
    directory: relRepo(stageDir),
    manifest: {
      path: relRepo(manifestPath),
      exists: fs.existsSync(manifestPath),
      parses: manifest.ok,
      error: manifest.error,
      status: manifest.value?.status ?? null,
    },
    raw: {
      hasStageArc: Boolean(rawArc),
      hasStagePzz: Boolean(rawPzz),
      stageArc: rawArc,
      stagePzz: rawPzz,
      stageArcMatchesSource: filesMatch(rawArc?.absolutePath, sourceRecord.source.stageArc?.absolutePath),
      stagePzzMatchesSource: filesMatch(rawPzz?.absolutePath, sourceRecord.source.stagePzz?.absolutePath),
    },
    visual: {
      directory: relRepo(modelDir),
      hasDaePieces: daeInfos.length > 0 && zeroByteDaeFiles.length === 0,
      hasContiguousDaeSequence: daeInfos.length > 0 && zeroByteDaeFiles.length === 0 && missingModelIndices.length === 0,
      hasCompleteDaeExport,
      daeCount: daeInfos.length,
      nonEmptyDaeCount: daeInfos.filter((file) => file.bytes > 0).length,
      zeroByteDaeFiles,
      maxModelIndex,
      missingModelIndices,
      expectedDaeIndices,
      missingExpectedDaeIndices,
      unexpectedDaeIndices,
      sampleDaeFiles: daeInfos.slice(0, 8).map((file) => file.path),
      textureCount: textureInfos.length,
      textureFiles: textureInfos.map((file) => file.path),
      exportSummary: {
        path: relRepo(exportSummaryPath),
        exists: fs.existsSync(exportSummaryPath),
        parses: exportSummary.ok,
        error: exportSummary.error,
        exporter: exportSummary.value?.exporter ?? null,
        expectedSlotCount: exportSummary.value?.expectedSlotCount ?? null,
        expectedDaeCount: exportSummary.value?.expectedDaeCount ?? expectedDaeIndices.length,
        exportedModelCount: exportSummary.value?.exportedModelCount ?? null,
        failedModelIndices,
        skippedNullRootJointIndices,
        complete: exportSummary.value?.complete ?? null,
      },
    },
    collision: {
      hasHitFiles: hitInfos.length > 0,
      exportedHitCount: hitInfos.length,
      exportedHitFiles: hitInfos.map((file) => file.path),
      missingSourceHitFiles: sourceHitNames.filter((file) => !publicHitNames.includes(file)),
      extraExportedHitFiles: publicHitNames.filter((file) => !sourceHitNames.includes(file)),
    },
    sets: {
      exportedSetCount: setInfos.length,
      exportedSetFiles: setInfos.map((file) => file.path),
    },
  };
}

function buildStageRecord(sourceRecord, publicExport) {
  const canExport = sourceRecord.source.hasStageArc && sourceRecord.source.hasStagePzz;
  const needsVisual = !publicExport.visual.hasCompleteDaeExport;
  const needsRaw = !publicExport.raw.hasStageArc || !publicExport.raw.hasStagePzz;
  const needsCollision =
    sourceRecord.source.collision.files.length > 0 && publicExport.collision.missingSourceHitFiles.length > 0;
  const needsExport = canExport && (needsVisual || needsRaw || needsCollision);
  const safeToRunExistingTools = !publicExport.exists || options.forceExisting;
  const commands = makeStageCommands(sourceRecord);

  return {
    id: sourceRecord.id,
    code: sourceRecord.code,
    source: sourceRecord.source,
    public: publicExport,
    export: {
      canExportWithExistingTools: canExport,
      needsExport,
      needsRaw,
      needsVisual,
      needsCollision,
      safeToRunExistingTools,
      unsafeReason:
        needsExport && !safeToRunExistingTools
          ? "public stage folder exists; scripts/export-stage-assets.mjs removes the output folder before copying"
          : null,
      commands,
    },
  };
}

function chooseProofCandidate(records) {
  return (
    records.find(
      (stage) =>
        stage.export.needsExport &&
        stage.export.safeToRunExistingTools &&
        stage.source.hasStageArc &&
        stage.source.hasStagePzz &&
        stage.source.collision.hasCompleteHitTriplet &&
        stage.source.sets.filesCopiedByCurrentTool.length >= 4,
    ) ??
    records.find((stage) => stage.export.needsExport && stage.export.safeToRunExistingTools && stage.source.hasStageArc)
  );
}

function selectStageRecordsForCommand(records) {
  let selected = records.filter((stage) => stage.export.needsExport && stage.export.safeToRunExistingTools);
  if (options.stageCodes.size > 0) {
    selected = selected.filter((stage) => options.stageCodes.has(stage.code));
  }
  if (options.proof) {
    const proof = chooseProofCandidate(selected);
    selected = proof ? [proof] : [];
  }
  if (options.limit != null) {
    selected = selected.slice(0, options.limit);
  }
  return selected;
}

function selectExportJobs(plan) {
  return selectStageRecordsForCommand(plan.stages).map((stage) => ({
    stageId: stage.id,
    code: stage.code,
  }));
}

function selectManifestRefreshRecords(plan) {
  let records = plan.stages.filter((stage) => stage.public.exists);
  if (options.stageCodes.size > 0) {
    records = records.filter((stage) => options.stageCodes.has(stage.code));
  }
  return records;
}

async function runStageExport(job) {
  console.log(`export ${job.stageId}: safe raw/collision/set copy`);
  copyRawStageAssets(job);
  console.log(`export ${job.stageId}: isolated visual DAE export`);
  exportStageVisual(job);
}

function copyRawStageAssets(job) {
  const sourceRoot = path.resolve(repoRoot, "user-data", options.region, "afs_data", "root");
  const publicRoot = path.resolve(repoRoot, "apps", "game", "public", "stages");
  const outDir = path.join(publicRoot, job.stageId);
  if (fs.existsSync(outDir) && !options.forceExisting) {
    fail(`refusing to overwrite existing stage folder without --force-existing: ${relRepo(outDir)}`);
  }
  if (fs.existsSync(outDir)) {
    assertInside(outDir, publicRoot, "stage output folder");
    for (const subdir of ["raw", "collision", "set"]) {
      const target = path.join(outDir, subdir);
      assertInside(target, outDir, "stage asset subfolder");
      fs.rmSync(target, { recursive: true, force: true });
    }
  }

  const copies = [
    { name: `${job.stageId}_mdl.arc`, subdir: "raw" },
    { name: `${job.stageId}.pzz`, subdir: "raw" },
    ...listNames(sourceRoot, (file) => new RegExp(`^hit${job.code}[0-9a-f]\\.bin$`, "i").test(file)).map((name) => ({
      name,
      subdir: "collision",
    })),
    ...listNames(sourceRoot, (file) => new RegExp(`^set${job.code}[0-9a-f]{2}\\.arc$`, "i").test(file)).map((name) => ({
      name,
      subdir: "set",
    })),
  ];

  for (const copy of copies) {
    const source = path.join(sourceRoot, copy.name);
    if (!fs.existsSync(source)) continue;
    const targetDir = path.join(outDir, copy.subdir);
    fs.mkdirSync(targetDir, { recursive: true });
    fs.copyFileSync(source, path.join(targetDir, copy.name));
  }
}

function exportStageVisual(job) {
  const sourceRoot = path.resolve(repoRoot, "user-data", options.region, "afs_data", "root");
  const publicRoot = path.resolve(repoRoot, "apps", "game", "public", "stages");
  const stageDir = path.join(publicRoot, job.stageId);
  const arcPath = path.join(sourceRoot, `${job.stageId}_mdl.arc`);
  if (!fs.existsSync(arcPath)) fail(`missing stage model archive: ${relRepo(arcPath)}`);

  const exporterRoot = path.resolve(repoRoot, "user-data", options.region, "stage-batch-exporter");
  const runRoot = path.join(exporterRoot, "runs", `${job.stageId}-${process.pid}`);
  const stagingModelDir = path.join(runRoot, "model");
  const summaryPath = path.join(runRoot, VISUAL_EXPORT_SUMMARY);
  assertInside(runRoot, path.join(exporterRoot, "runs"), "stage visual export workspace");

  fs.rmSync(runRoot, { recursive: true, force: true });
  fs.mkdirSync(stagingModelDir, { recursive: true });
  ensureBatchExporterProject(exporterRoot);

  const csproj = path.join(exporterRoot, "stage-batch-exporter.csproj");
  const result = spawnSync("dotnet", ["run", "--project", csproj, "-c", "Release", "--", arcPath, stagingModelDir, summaryPath], {
    cwd: repoRoot,
    shell: false,
    stdio: "inherit",
  });
  if (result.status !== 0 && !fs.existsSync(summaryPath)) {
    fail(`visual exporter failed before writing a summary for ${job.stageId}`);
  }

  const summary = readJsonIfExists(summaryPath);
  if (!summary.ok) fail(`visual exporter wrote an unreadable summary for ${job.stageId}: ${summary.error}`);
  if ((summary.value.exportedModelCount ?? 0) === 0) {
    fail(`visual exporter produced no models for ${job.stageId}`);
  }

  publishModelDirectory(stageDir, stagingModelDir);
  fs.copyFileSync(summaryPath, path.join(stageDir, "model", VISUAL_EXPORT_SUMMARY));
  fs.rmSync(runRoot, { recursive: true, force: true });

  if (summary.value.complete !== true) {
    console.warn(
      `export ${job.stageId}: partial visual export; failed model indices ${compactNumberList(
        numericArray(summary.value.failedModelIndices),
      )}`,
    );
  }
}

function ensureBatchExporterProject(exporterRoot) {
  fs.mkdirSync(exporterRoot, { recursive: true });
  fs.writeFileSync(path.join(exporterRoot, "Program.cs"), batchExporterSource());
  fs.writeFileSync(
    path.join(exporterRoot, "stage-batch-exporter.csproj"),
    String.raw`<Project Sdk="Microsoft.NET.Sdk">
  <PropertyGroup>
    <OutputType>Exe</OutputType>
    <TargetFramework>net6.0-windows</TargetFramework>
    <Nullable>disable</Nullable>
    <UseWindowsForms>true</UseWindowsForms>
  </PropertyGroup>
  <ItemGroup>
    <ProjectReference Include="..\..\..\tools\HSDLib\HSDRawViewer\HSDRawViewer.csproj" />
  </ItemGroup>
</Project>
`,
  );
}

function batchExporterSource() {
  return String.raw`
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.Json;
using System.Text.RegularExpressions;
using HSDRaw;
using HSDRaw.Common;
using HSDRawViewer.Converters;
using HSDRawViewer.Tools.Animation;

class StageBatchExporter {
  static int Main(string[] args) {
    if (args.Length < 3) throw new Exception("usage: stage-batch-exporter <arc> <outDir> <summaryPath>");
    var arc = args[0];
    var outDir = args[1];
    var summaryPath = args[2];
    var runDir = Path.GetDirectoryName(summaryPath);
    if (runDir == null) throw new Exception("summaryPath must include a directory");
    var isolatedRoot = Path.Combine(runDir, "isolated");

    Directory.CreateDirectory(outDir);
    Directory.CreateDirectory(isolatedRoot);

    var data = File.ReadAllBytes(arc);
    var hsd = new HSDRawFile(data);
    var records = new List<ModelRecord>();
    int model = 0, ok = 0, fail = 0, skippedNull = 0;

    foreach (var root in hsd.Roots) {
      if (root?.Data == null) continue;
      var sobj = new HSD_SOBJ(){ _s = root.Data._s };
      if (sobj.JOBJDescs?.Array == null) continue;
      foreach (var jd in sobj.JOBJDescs.Array) {
        var index = model++;
        if (jd?.RootJoint == null) {
          records.Add(new ModelRecord {
            Index = index,
            Status = "skipped-null-root-joint",
            DaeFile = null,
            TextureFiles = Array.Empty<string>(),
            Error = null
          });
          skippedNull++;
          continue;
        }

        var isolatedModelDir = Path.Combine(isolatedRoot, $"model_{index:D2}");
        Directory.CreateDirectory(isolatedModelDir);
        var isolatedDae = Path.Combine(isolatedModelDir, $"model_{index:D2}.dae");
        try {
          var settings = new ModelExportSettings {
            ExportMesh = true,
            ExportTextures = true,
            ExportBindPose = true,
            Optimize = true
          };
          ModelExporter.ExportFile(isolatedDae, jd.RootJoint, settings, new JointMap());
          var textureFiles = PublishModel(index, isolatedModelDir, isolatedDae, outDir);
          records.Add(new ModelRecord {
            Index = index,
            Status = "exported",
            DaeFile = $"model_{index:D2}.dae",
            TextureFiles = textureFiles,
            Error = null
          });
          Console.WriteLine($"OK model_{index:D2}.dae textures={textureFiles.Length}");
          ok++;
        } catch (Exception e) {
          records.Add(new ModelRecord {
            Index = index,
            Status = "failed",
            DaeFile = null,
            TextureFiles = Array.Empty<string>(),
            Error = e.GetType().Name + ": " + e.Message
          });
          Console.WriteLine($"ERR model_{index:D2}: {e.GetType().Name} {e.Message}");
          fail++;
        }
      }
    }

    var expectedDaeIndices = records.Where(r => r.Status != "skipped-null-root-joint").Select(r => r.Index).ToArray();
    var failedModelIndices = records.Where(r => r.Status == "failed").Select(r => r.Index).ToArray();
    var skippedNullRootJointIndices = records.Where(r => r.Status == "skipped-null-root-joint").Select(r => r.Index).ToArray();
    var exportedModelCount = records.Count(r => r.Status == "exported");
    var summary = new ExportSummary {
      Exporter = "scripts/export-all-stages.mjs stage-batch-exporter",
      ExpectedSlotCount = model,
      ExpectedDaeCount = expectedDaeIndices.Length,
      ExportedModelCount = exportedModelCount,
      FailedModelCount = fail,
      SkippedNullRootJointCount = skippedNull,
      ExpectedDaeIndices = expectedDaeIndices,
      FailedModelIndices = failedModelIndices,
      SkippedNullRootJointIndices = skippedNullRootJointIndices,
      Complete = fail == 0,
      Models = records
    };

    var json = JsonSerializer.Serialize(summary, new JsonSerializerOptions {
      WriteIndented = true,
      PropertyNamingPolicy = JsonNamingPolicy.CamelCase
    });
    File.WriteAllText(summaryPath, json + Environment.NewLine, new UTF8Encoding(false));
    Console.WriteLine($"stage-batch-export expected={expectedDaeIndices.Length} ok={ok} fail={fail} skipped-null={skippedNull}");
    return ok == 0 ? 2 : 0;
  }

  static string[] PublishModel(int modelIndex, string isolatedModelDir, string isolatedDae, string outDir) {
    var dae = File.ReadAllText(isolatedDae);
    dae = Regex.Replace(dae, "<created>.*?</created>", "<created>1970-01-01T00:00:00Z</created>");
    dae = Regex.Replace(dae, "<modified>.*?</modified>", "<modified>1970-01-01T00:00:00Z</modified>");

    var textures = Directory.GetFiles(isolatedModelDir, "*.png").OrderBy(Path.GetFileName).ToArray();
    var renamedTextures = new List<string>();
    var replacements = new Dictionary<string, string>();
    foreach (var texture in textures) {
      var oldBase = Path.GetFileNameWithoutExtension(texture);
      var newBase = $"model_{modelIndex:D2}_{oldBase}";
      replacements[oldBase] = newBase;
    }

    foreach (var pair in replacements.OrderByDescending(p => p.Key.Length)) {
      dae = dae.Replace(pair.Key, pair.Value);
    }

    File.WriteAllText(Path.Combine(outDir, $"model_{modelIndex:D2}.dae"), dae, new UTF8Encoding(false));
    foreach (var texture in textures) {
      var oldBase = Path.GetFileNameWithoutExtension(texture);
      var targetName = replacements[oldBase] + ".png";
      File.Copy(texture, Path.Combine(outDir, targetName), true);
      renamedTextures.Add(targetName);
    }

    return renamedTextures.ToArray();
  }
}

public class ExportSummary {
  public string Exporter { get; set; }
  public int ExpectedSlotCount { get; set; }
  public int ExpectedDaeCount { get; set; }
  public int ExportedModelCount { get; set; }
  public int FailedModelCount { get; set; }
  public int SkippedNullRootJointCount { get; set; }
  public int[] ExpectedDaeIndices { get; set; }
  public int[] FailedModelIndices { get; set; }
  public int[] SkippedNullRootJointIndices { get; set; }
  public bool Complete { get; set; }
  public List<ModelRecord> Models { get; set; }
}

public class ModelRecord {
  public int Index { get; set; }
  public string Status { get; set; }
  public string DaeFile { get; set; }
  public string[] TextureFiles { get; set; }
  public string Error { get; set; }
}
`;
}

function publishModelDirectory(stageDir, stagingModelDir) {
  const publicRoot = path.resolve(repoRoot, "apps", "game", "public", "stages");
  const modelDir = path.join(stageDir, "model");
  assertInside(stageDir, publicRoot, "stage folder");
  assertInside(modelDir, stageDir, "stage model folder");
  fs.mkdirSync(stageDir, { recursive: true });
  fs.rmSync(modelDir, { recursive: true, force: true });
  try {
    fs.renameSync(stagingModelDir, modelDir);
  } catch (error) {
    if (error.code !== "EXDEV") throw error;
    fs.cpSync(stagingModelDir, modelDir, { recursive: true });
    fs.rmSync(stagingModelDir, { recursive: true, force: true });
  }
}

function runNode(args) {
  const result = spawnSync(process.execPath, args, {
    cwd: repoRoot,
    shell: false,
    stdio: "inherit",
  });
  if (result.status !== 0) {
    fail(`command failed: node ${args.join(" ")}`);
  }
}

async function writeVerifiedStageManifest(record) {
  const stageDir = path.resolve(repoRoot, "apps", "game", "public", "stages", record.id);
  const manifestPath = path.join(stageDir, "manifest.json");
  const status = verifiedStatus(record);
  const manifest = {
    region: options.region,
    id: record.id,
    source: record.sourceRoot ?? `user-data/${options.region}/afs_data/root`,
    status,
    verifiedBy: "scripts/export-all-stages.mjs",
    verifiedAt: new Date().toISOString(),
    copied: {
      stageArc: relPublic(record.public.raw.stageArc?.absolutePath),
      stagePzz: relPublic(record.public.raw.stagePzz?.absolutePath),
      hitBins: record.public.collision.exportedHitFiles.map((file) => relPublic(path.resolve(repoRoot, file))),
      setArcs: record.public.sets.exportedSetFiles.map((file) => relPublic(path.resolve(repoRoot, file))),
    },
    visual: {
      hasDaePieces: record.public.visual.hasDaePieces,
      hasContiguousDaeSequence: record.public.visual.hasContiguousDaeSequence,
      hasCompleteDaeExport: record.public.visual.hasCompleteDaeExport,
      daeCount: record.public.visual.daeCount,
      nonEmptyDaeCount: record.public.visual.nonEmptyDaeCount,
      maxModelIndex: record.public.visual.maxModelIndex,
      missingModelIndices: record.public.visual.missingModelIndices,
      expectedDaeIndices: record.public.visual.expectedDaeIndices,
      missingExpectedDaeIndices: record.public.visual.missingExpectedDaeIndices,
      unexpectedDaeIndices: record.public.visual.unexpectedDaeIndices,
      textureCount: record.public.visual.textureCount,
      exportSummary: record.public.visual.exportSummary,
    },
    collision: {
      sourceHitFiles: record.source.collision.files.map((file) => path.basename(file.path)),
      exportedHitCount: record.public.collision.exportedHitCount,
      missingSourceHitFiles: record.public.collision.missingSourceHitFiles,
      hasCompleteSourceHitTriplet: record.source.collision.hasCompleteHitTriplet,
    },
    sets: {
      sourceSetFiles: record.source.sets.files.map((file) => path.basename(file.path)),
      exportedSetCount: record.public.sets.exportedSetCount,
      filesNotCopiedByCurrentTool: record.source.sets.filesNotCopiedByCurrentTool,
    },
    commands: record.export.commands,
    notes: [
      "Verified by comparing source stage assets against the browser public stage folder.",
      "Visual DAE pieces are imported render assets; collision hit*.bin files are copied but not decoded here.",
      ...(record.source.sets.filesNotCopiedByCurrentTool.length > 0
        ? ["Current raw copy tool only copies set##00.arc through set##03.arc for each stage code."]
        : []),
    ],
  };
  await writeFile(manifestPath, `${JSON.stringify(manifest, null, 2)}\n`);
}

function verifiedStatus(record) {
  if (!record.public.visual.hasDaePieces) return "missing-visual-dae";
  if (record.public.visual.zeroByteDaeFiles.length > 0) return "partial-visual-zero-byte-dae";
  if (!record.public.visual.exportSummary.exists) return "partial-visual-export-unverified";
  if (record.public.visual.exportSummary.exists && record.public.visual.exportSummary.failedModelIndices.length > 0) {
    return "partial-visual-export-failed";
  }
  if (!record.public.visual.hasCompleteDaeExport) return "partial-visual-dae-missing-slots";
  if (!record.public.raw.stageArcMatchesSource || !record.public.raw.stagePzzMatchesSource) return "visual-exported-raw-mismatch";
  if (record.source.collision.hasHitFiles && record.public.collision.missingSourceHitFiles.length > 0) {
    return "visual-exported-missing-hit-files";
  }
  if (!record.source.collision.hasHitFiles) return "visual-exported-no-source-hit-files";
  return "verified-visual-and-collision";
}

async function writePlanFiles(plan) {
  const jsonPath = path.resolve(repoRoot, options.planJson);
  const mdPath = path.resolve(repoRoot, options.planMd);
  await mkdir(path.dirname(jsonPath), { recursive: true });
  await mkdir(path.dirname(mdPath), { recursive: true });
  await writeFile(jsonPath, `${JSON.stringify(plan, null, 2)}\n`);
  await writeFile(mdPath, renderMarkdown(plan));
}

function renderMarkdown(plan) {
  const missing = plan.stages.filter((stage) => stage.export.needsExport);
  const visual = plan.stages.filter((stage) => stage.public.visual.hasDaePieces);
  const completeVisual = plan.stages.filter((stage) => stage.public.visual.hasCompleteDaeExport);
  const collision = plan.stages.filter((stage) => stage.source.collision.hasHitFiles);
  const rows = plan.stages
    .map((stage) => {
      const source = stage.source.hasModelAndPzzPair ? "ARC+PZZ" : stage.source.hasStageArc ? "ARC only" : "missing";
      const publicState = stage.public.visual.hasDaePieces
        ? stage.public.visual.hasCompleteDaeExport
          ? `${stage.public.visual.daeCount} DAE complete`
          : `${stage.public.visual.daeCount} DAE, missing ${compactNumberList(stage.public.visual.missingExpectedDaeIndices)}`
        : stage.public.exists
          ? "public folder, no DAE"
          : "not exported";
      const hitState = stage.source.collision.hasHitFiles
        ? `${stage.source.collision.files.length} source / ${stage.public.collision.exportedHitCount} public`
        : "no source hit";
      const setState = `${stage.source.sets.files.length} source / ${stage.public.sets.exportedSetCount} public`;
      const action = stage.export.needsExport
        ? stage.export.safeToRunExistingTools
          ? `\`${stage.export.commands.orchestrated}\``
          : "manual or --force-existing"
        : "covered";
      return `| ${stage.id} | ${source} | ${publicState} | ${hitState} | ${setState} | ${action} |`;
    })
    .join("\n");

  const exactCommands = missing
    .map(
      (stage) => `### ${stage.id}
\`\`\`bash
${stage.export.commands.orchestrated}
# equivalent single-stage raw copy tool, which also rewrites apps/game/public/stages/manifest.json:
${stage.export.commands.singleStageRawCopy}
# legacy visual exporter; retained for comparison, not used by the batch orchestrator:
${stage.export.commands.legacyVisualExport}
${stage.export.commands.visualExport}
\`\`\`
`,
    )
    .join("\n");

  return `# Stage Export Plan

Generated: ${plan.generatedAt}

## Summary

- Region: ${plan.region}
- Source direct stage pairs: ${plan.summary.sourcePairsWithModelAndPzz}/${plan.summary.sourceStageArchiveCount}
- Browser public stage folders: ${plan.summary.publicStageFolderCount}
- Browser stages with visual DAE pieces: ${visual.length}
- Browser stages with complete DAE sequences: ${completeVisual.length}
- Source stages with any hit collision bins: ${collision.length}
- Missing or partial exports: ${plan.summary.missingOrPartialExportCount}
- Safe missing exports with current tools: ${plan.summary.safeMissingExportCount}
- Proof candidate: ${plan.summary.proofCandidate ?? "none"}

Adventure-flow note: ${plan.sources.adventureFlow.stageSelectionFinding}

## Commands

Dry run:

\`\`\`bash
rtk node scripts/export-all-stages.mjs ${plan.region} --dry-run
\`\`\`

One proof export:

\`\`\`bash
${plan.exportPlan.proofCommand ?? "# no safe proof candidate"}
\`\`\`

All safe missing exports:

\`\`\`bash
${plan.exportPlan.allSafeMissingCommand ?? "# no safe missing exports"}
\`\`\`

## Coverage Table

| Stage | Source | Browser visual | Hit bins | Set ARCs | Action |
| --- | --- | --- | --- | --- | --- |
${rows}

## Exact Per-Stage Commands

${exactCommands || "No missing or partial stage exports remain.\n"}
`;
}

function summarizeAdventureFlow() {
  const file = path.resolve(repoRoot, "research", "asset-inventory", "adventure-flow-ai.json");
  const fallback = {
    path: relRepo(file),
    exists: false,
    directStageArchives: null,
    uniqueArenaCount: null,
    uniqueArenas: [],
    stageSelectionFinding: "adventure-flow-ai.json was not available for comparison.",
  };
  if (!fs.existsSync(file)) return fallback;
  const parsed = readJsonIfExists(file);
  if (!parsed.ok) {
    return {
      ...fallback,
      exists: true,
      error: parsed.error,
      stageSelectionFinding: "adventure-flow-ai.json could not be parsed.",
    };
  }
  const data = parsed.value;
  const finding = data.implementationGaps?.find((gap) => gap.area === "Stage selection to arena asset mapping")?.finding;
  return {
    path: relRepo(file),
    exists: true,
    directStageArchives: data.extractedAssets?.stageAssets?.directStageArchives ?? null,
    uniqueArenaCount: data.data?.stages?.uniqueArenaCount ?? null,
    uniqueArenas: data.data?.stages?.uniqueArenas ?? [],
    publicStageExport: data.currentRuntime?.publicStageExport ?? null,
    stageSelectionFinding:
      finding ?? "No verified arena-name to st## mapping was found in adventure-flow-ai.json.",
  };
}

function makeStageCommands(sourceRecord) {
  return {
    stage: sourceRecord.id,
    orchestrated: commandForExportAll([sourceRecord.id]),
    singleStageRawCopy: `rtk node ${slash(EXPORT_ASSETS_SCRIPT)} ${options.region} ${sourceRecord.code}`,
    visualExport: commandForExportAll([sourceRecord.id]),
    legacyVisualExport: `rtk node ${slash(EXPORT_HSD_SCRIPT)} ${options.region} ${sourceRecord.code}`,
  };
}

function commandForExportAll(stageIds, extra = "") {
  const parts = ["rtk", "node", slash("scripts/export-all-stages.mjs"), options.region, "--export"];
  if (extra) parts.push(extra);
  if (stageIds.length > 0 && extra !== "--proof") {
    parts.push("--stage", stageIds.join(","));
  }
  return parts.join(" ");
}

function fileInfo(file) {
  try {
    const stat = fs.statSync(file);
    if (!stat.isFile()) return null;
    return {
      path: relRepo(file),
      absolutePath: file,
      bytes: stat.size,
    };
  } catch {
    return null;
  }
}

function listFileInfos(dir, predicate) {
  try {
    return fs
      .readdirSync(dir)
      .filter(predicate)
      .sort()
      .map((file) => fileInfo(path.join(dir, file)))
      .filter(Boolean);
  } catch {
    return [];
  }
}

function listNames(dir, predicate) {
  try {
    return fs.readdirSync(dir).filter(predicate).sort();
  } catch {
    return [];
  }
}

function filesMatch(left, right) {
  if (!left || !right) return false;
  try {
    const leftStat = fs.statSync(left);
    const rightStat = fs.statSync(right);
    return leftStat.size === rightStat.size && sha1(left) === sha1(right);
  } catch {
    return false;
  }
}

function sha1(file) {
  return crypto.createHash("sha1").update(fs.readFileSync(file)).digest("hex");
}

function readJsonIfExists(file) {
  try {
    return { ok: true, value: JSON.parse(fs.readFileSync(file, "utf8")), error: null };
  } catch (error) {
    if (error.code === "ENOENT") return { ok: false, value: null, error: "missing" };
    return { ok: false, value: null, error: error.message };
  }
}

function expectedDaeIndicesFromSummary(summary, modelIndices) {
  const expected = numericArray(summary?.expectedDaeIndices);
  if (expected.length > 0) return expected;
  const maxModelIndex = modelIndices.length > 0 ? modelIndices.at(-1) : null;
  return maxModelIndex == null ? [] : range(0, maxModelIndex);
}

function numericArray(value) {
  return Array.isArray(value)
    ? value.filter((item) => Number.isInteger(item) && item >= 0).sort((left, right) => left - right)
    : [];
}

function addStageCodes(target, value) {
  for (const part of value.split(",")) {
    if (!part.trim()) continue;
    target.add(normalizeStageCode(part));
  }
}

function normalizeStageCode(value) {
  const normalized = value.trim().toLowerCase().replace(/^st/, "");
  if (!/^[0-9a-f]{2}$/.test(normalized)) fail(`invalid stage code "${value}"`);
  return normalized;
}

function requiredValue(args, index, flag) {
  const value = args[index];
  if (!value || value.startsWith("--")) fail(`${flag} requires a value`);
  return value;
}

function parsePositiveInt(value, flag) {
  const parsed = Number.parseInt(value, 10);
  if (!Number.isInteger(parsed) || parsed < 1) fail(`${flag} must be a positive integer`);
  return parsed;
}

function compareStageIds(left, right) {
  return compareStageCodes(normalizeStageCode(left), normalizeStageCode(right));
}

function compareStageCodes(left, right) {
  return Number.parseInt(left, 16) - Number.parseInt(right, 16);
}

function range(start, endInclusive) {
  return Array.from({ length: endInclusive - start + 1 }, (_, index) => start + index);
}

function compactNumberList(values) {
  if (values.length === 0) return "none";
  const ranges = [];
  let start = values[0];
  let previous = values[0];
  for (const value of values.slice(1)) {
    if (value === previous + 1) {
      previous = value;
      continue;
    }
    ranges.push(start === previous ? `${start}` : `${start}-${previous}`);
    start = value;
    previous = value;
  }
  ranges.push(start === previous ? `${start}` : `${start}-${previous}`);
  return ranges.join(",");
}

function assertInside(child, parent, label) {
  const resolvedChild = path.resolve(child);
  const resolvedParent = path.resolve(parent);
  if (resolvedChild !== resolvedParent && !resolvedChild.startsWith(`${resolvedParent}${path.sep}`)) {
    fail(`refusing to use ${label} outside ${relRepo(resolvedParent)}: ${relRepo(resolvedChild)}`);
  }
}

function relRepo(file) {
  return slash(path.relative(repoRoot, file));
}

function relPublic(file) {
  if (!file) return null;
  const publicRoot = path.resolve(repoRoot, "apps", "game", "public", "stages");
  return slash(path.relative(publicRoot, file));
}

function slash(value) {
  return value.replaceAll("\\", "/");
}

function fail(message) {
  console.error(`export-all-stages: ${message}`);
  process.exit(1);
}

function printSummary(plan) {
  console.log(
    [
      `export-all-stages: ${plan.mode}`,
      `source pairs ${plan.summary.sourcePairsWithModelAndPzz}/${plan.summary.sourceStageArchiveCount}`,
      `visual public ${plan.summary.verifiedVisualStageCount}`,
      `missing/partial ${plan.summary.missingOrPartialExportCount}`,
      `safe ${plan.summary.safeMissingExportCount}`,
      `proof ${plan.summary.proofCandidate ?? "none"}`,
      `plan ${options.planJson}`,
    ].join("; "),
  );
}
