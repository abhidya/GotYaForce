#!/usr/bin/env node
import fs from "node:fs";
import { mkdir, writeFile } from "node:fs/promises";
import path from "node:path";
import { spawnSync } from "node:child_process";

const REGIONS = new Set(["GG4E", "GG4J", "GG4P"]);
const DEFAULT_REGION = "GG4E";
const DEFAULT_PLAN_JSON = path.join("research", "asset-inventory", "borg-animation-export-plan.json");
const DEFAULT_PLAN_MD = path.join("research", "asset-inventory", "borg-animation-export-plan.md");
const EXPORTER_SCRIPT = "scripts/export-borg-animation-hsd.mjs";
const PUBLIC_MODELS_DIR = "apps/game/public/models";
const BANK_COUNT = 6;

const options = parseArgs(process.argv.slice(2));
if (options.help) usage(0);
if (!REGIONS.has(options.region)) fail(`unsupported region "${options.region}"`);

const repoRoot = path.resolve(".");
const rootDir = path.join(repoRoot, "user-data", options.region, "afs_data", "root");
const exporterPath = path.join(repoRoot, EXPORTER_SCRIPT);

mustBeDir(rootDir, "AFS root");
mustBeFile(exporterPath, "single-borg exporter");

let plan = buildPlan();
let exported = [];

if (options.export) {
  const jobs = selectExportJobs(plan);
  if (jobs.length === 0) {
    console.log("export-all-borg-animations: no unconfirmed clips matched the export filters");
  }
  for (const job of jobs) {
    console.log(`export ${job.borgId} ${job.sourceBlobOffset} -> ${job.destinationPath}`);
    const result = spawnSync(process.execPath, job.spawnArgs, {
      cwd: repoRoot,
      shell: false,
      stdio: "inherit",
    });
    if ((result.status ?? 1) !== 0) process.exit(result.status ?? 1);
    exported.push(job);
  }
  plan = buildPlan({ exported });
}

await writePlanFiles(plan);
printSummary(plan, exported);

function parseArgs(args) {
  const parsed = {
    region: DEFAULT_REGION,
    export: false,
    proof: false,
    includeConfirmed: false,
    borgs: new Set(),
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
    } else if (arg === "--include-confirmed") {
      parsed.includeConfirmed = true;
    } else if (arg === "--borg") {
      addBorgs(parsed.borgs, requiredValue(args, ++i, arg));
    } else if (arg.startsWith("--borg=")) {
      addBorgs(parsed.borgs, arg.slice("--borg=".length));
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

  if (positionals.length > 1) fail(`unexpected positional args: ${positionals.slice(1).join(" ")}`);
  if (positionals[0]) parsed.region = positionals[0];
  return parsed;
}

function usage(code) {
  const stream = code === 0 ? process.stdout : process.stderr;
  stream.write(`usage: node ${EXPORTER_SCRIPT.replace("export-borg-animation-hsd", "export-all-borg-animations")} [GG4E|GG4J|GG4P] [options]

Builds research/asset-inventory/borg-animation-export-plan.{json,md} from every
borg that has both a primary model arc and a MOT container.

Options:
  --plan, --dry-run          write plan artifacts only (default)
  --export                  run export jobs after planning
  --proof                   filter to one safe non-pl0615 proof export candidate
  --borg <id[,id...]>       filter export jobs to one or more borg ids
  --limit <n>               cap export jobs after filtering
  --include-confirmed       export even when a matching JSON already exists
  --plan-json <path>        JSON output path
  --plan-md <path>          Markdown output path
`);
  process.exit(code);
}

function addBorgs(target, value) {
  for (const raw of value.split(",")) {
    const borgId = raw.trim().toLowerCase();
    if (!borgId) continue;
    if (!/^pl[0-9a-f]{4}[a-z]?$/i.test(borgId)) fail(`invalid borg id "${raw}"`);
    target.add(borgId);
  }
}

function requiredValue(args, index, flag) {
  const value = args[index];
  if (!value || value.startsWith("--")) fail(`${flag} requires a value`);
  return value;
}

function parsePositiveInt(value, flag) {
  const parsed = Number.parseInt(value, 10);
  if (!Number.isInteger(parsed) || parsed <= 0) fail(`${flag} must be a positive integer`);
  return parsed;
}

function buildPlan(extra = {}) {
  const source = discoverSourceBorgs();
  const borgs = source.map((borg) => buildBorgPlan(borg));
  const summary = summarize(borgs);
  return {
    schema: "gotyaforce.borgAnimationExportPlan.v1",
    generatedAt: new Date().toISOString(),
    region: options.region,
    mode: options.export ? "export" : "plan",
    inputs: {
      rootDir: rel(rootDir),
      exporterScript: EXPORTER_SCRIPT,
      motFormatSpec: path.join("research", "format-specs", "mot-animation-format.md"),
    },
    outputs: {
      planJson: normalizeRel(options.planJson),
      planMarkdown: normalizeRel(options.planMd),
      animationRoot: PUBLIC_MODELS_DIR,
    },
    notes: [
      "Generated clip filenames use structural bank/slot candidate labels; this plan does not confirm gameplay semantic labels.",
      "A clip is confirmed-exported only when a matching JSON exists, parses, has a positive frameCount, and records the same source blob offset.",
      "The batch exporter calls scripts/export-borg-animation-hsd.mjs and does not duplicate its HSD conversion logic.",
    ],
    summary,
    proofExportCandidate: findProofExportCandidate(borgs),
    recentExports: (extra.exported ?? []).map((job) => ({
      borgId: job.borgId,
      sourceBlobOffset: job.sourceBlobOffset,
      destinationPath: job.destinationPath,
      command: job.command,
    })),
    borgs,
  };
}

function discoverSourceBorgs() {
  const files = fs.readdirSync(rootDir).sort((a, b) => a.localeCompare(b));
  const models = new Map();
  const mots = new Map();

  for (const file of files) {
    const model = file.match(/^(pl[0-9a-f]{4}[a-z]?)_mdl\.arc$/i);
    if (model) models.set(model[1].toLowerCase(), file);

    const mot = file.match(/^(pl[0-9a-f]{4}[a-z]?)mot\.bin$/i);
    if (mot) mots.set(mot[1].toLowerCase(), file);
  }

  return [...mots.keys()]
    .filter((borgId) => models.has(borgId))
    .sort((a, b) => a.localeCompare(b))
    .map((borgId) => ({
      id: borgId,
      modelPath: path.join(rootDir, models.get(borgId)),
      motPath: path.join(rootDir, mots.get(borgId)),
    }));
}

function buildBorgPlan(borg) {
  const mot = parseMot(borg.motPath);
  const publicModelPaths = findPublicModelPaths(borg.id);
  const existingExports = scanExistingExports(borg.id);
  const existingByOffset = new Map();
  for (const exportRecord of existingExports.filter((record) => record.valid && record.sourceBlobOffset)) {
    pushMap(existingByOffset, exportRecord.sourceBlobOffset, exportRecord);
  }

  const clips = [];
  for (const bank of mot.banks) {
    for (const clip of bank.clips) {
      const outputName = clipFileName(bank.index, clip.slotIndex);
      const destinationPath = path.join(PUBLIC_MODELS_DIR, borg.id, outputName);
      const matchingExports = existingByOffset.get(hex(clip.offset)) ?? [];
      const confirmedExports = matchingExports.map((record) => record.path);
      const exporterSafe = mot.firstBlobOffset === 0x240;
      clips.push({
        bankIndex: bank.index,
        slotIndex: clip.slotIndex,
        clipIndexInBank: clip.clipIndexInBank,
        sourceBlobOffset: hex(clip.offset),
        blobLengthBytes: mot.blobLengths.get(clip.offset) ?? null,
        candidateLabel: `bank${bank.index}_slot${pad2(clip.slotIndex)}`,
        semanticLabelStatus: "candidate-structural-only",
        exporterSafeWithCurrentScript: exporterSafe,
        exporterBlocker: exporterSafe
          ? null
          : `current single-borg exporter assumes the MOT table/blob boundary at 0x240; this MOT starts blobs at ${hex(mot.firstBlobOffset ?? 0)}`,
        destinationPath: normalizeRel(destinationPath),
        status: confirmedExports.length > 0 ? "confirmed-exported" : "planned",
        confirmedExportPaths: confirmedExports,
        command: commandFor(borg.id, clip.offset, outputName),
        shellCommand: commandToString(commandFor(borg.id, clip.offset, outputName)),
      });
    }
  }

  const confirmedExportedClipCount = clips.filter((clip) => clip.status === "confirmed-exported").length;
  return {
    id: borg.id,
    modelPath: rel(borg.modelPath),
    motPath: rel(borg.motPath),
    motBytes: fs.statSync(borg.motPath).size,
    firstBlobOffset: mot.firstBlobOffset == null ? null : hex(mot.firstBlobOffset),
    exporterSafeWithCurrentScript: mot.firstBlobOffset === 0x240,
    publicModelPaths,
    hasPublicModel: publicModelPaths.length > 0,
    banks: mot.banks.map((bank) => ({
      index: bank.index,
      tableOffset: hex(bank.tableOffset),
      slotCount: bank.slotCount,
      emptySlotCount: bank.emptySlotCount,
      clipCount: bank.clips.length,
    })),
    clipCount: clips.length,
    confirmedExportedClipCount,
    plannedClipCount: clips.length - confirmedExportedClipCount,
    existingExports,
    parseIssues: mot.issues,
    clips,
  };
}

function parseMot(motPath) {
  const data = fs.readFileSync(motPath);
  const issues = [];
  const rawBanks = [];

  if (data.length < BANK_COUNT * 4) {
    return {
      banks: [],
      blobLengths: new Map(),
      firstBlobOffset: null,
      issues: ["file is too small for MOT master table"],
    };
  }

  for (let bankIndex = 0; bankIndex < BANK_COUNT; bankIndex++) {
    const tableOffset = data.readUInt32BE(bankIndex * 4);
    const bank = {
      index: bankIndex,
      tableOffset,
      slotCount: 0,
      emptySlotCount: 0,
      clips: [],
    };

    if (tableOffset === 0) {
      rawBanks.push(bank);
      continue;
    }

    if (tableOffset + 4 > data.length) {
      issues.push(`bank ${bankIndex} has invalid table offset ${hex(tableOffset)}`);
      rawBanks.push(bank);
      continue;
    }

    let clipIndexInBank = 0;
    let terminated = false;
    for (let cursor = tableOffset, slotIndex = 0; cursor + 4 <= data.length; cursor += 4, slotIndex++) {
      const value = data.readUInt32BE(cursor);
      if (value === 0xffffffff) {
        bank.slotCount = slotIndex;
        terminated = true;
        break;
      }
      if (value === 0) {
        bank.emptySlotCount += 1;
      } else if (value < data.length) {
        bank.clips.push({ slotIndex, clipIndexInBank, offset: value });
        clipIndexInBank += 1;
      } else {
        issues.push(`bank ${bankIndex} slot ${slotIndex} points outside file: ${hex(value)}`);
      }

      if (slotIndex > 1024) {
        issues.push(`bank ${bankIndex} table scan stopped after 1024 slots without terminator`);
        bank.slotCount = slotIndex + 1;
        break;
      }
    }
    if (!terminated && bank.slotCount === 0) {
      issues.push(`bank ${bankIndex} table has no terminator`);
    }
    rawBanks.push(bank);
  }

  const uniqueOffsets = [...new Set(rawBanks.flatMap((bank) => bank.clips.map((clip) => clip.offset)))].sort(
    (a, b) => a - b,
  );
  const blobLengths = new Map();
  for (let i = 0; i < uniqueOffsets.length; i++) {
    const start = uniqueOffsets[i];
    const end = uniqueOffsets[i + 1] ?? data.length;
    blobLengths.set(start, Math.max(0, end - start));
  }

  return { banks: rawBanks, blobLengths, firstBlobOffset: uniqueOffsets[0] ?? null, issues };
}

function findPublicModelPaths(borgId) {
  const candidates = [
    path.join(repoRoot, PUBLIC_MODELS_DIR, borgId, "model_00.dae"),
    path.join(repoRoot, PUBLIC_MODELS_DIR, borgId, `${borgId}.dae`),
    path.join(repoRoot, PUBLIC_MODELS_DIR, "library", borgId, `${borgId}.dae`),
    path.join(repoRoot, PUBLIC_MODELS_DIR, "library", borgId, "model_00.dae"),
  ];
  return candidates.filter((candidate) => fs.existsSync(candidate)).map(rel);
}

function scanExistingExports(borgId) {
  const dir = path.join(repoRoot, PUBLIC_MODELS_DIR, borgId);
  if (!fs.existsSync(dir) || !fs.statSync(dir).isDirectory()) return [];

  return fs
    .readdirSync(dir)
    .filter((file) => /^anim_.*\.json$/i.test(file))
    .sort((a, b) => a.localeCompare(b))
    .map((file) => readExportRecord(path.join(dir, file)));
}

function readExportRecord(filePath) {
  const record = {
    path: rel(filePath),
    valid: false,
    sourceBlobOffset: null,
    modelIndex: null,
    frameCount: null,
    boneCount: null,
  };

  try {
    const parsed = JSON.parse(fs.readFileSync(filePath, "utf8"));
    const source = String(parsed.name ?? "").match(/_blob([0-9a-f]+)_m([0-9]+)/i);
    record.sourceBlobOffset = source ? hex(Number.parseInt(source[1], 16)) : null;
    record.modelIndex = source ? Number.parseInt(source[2], 10) : null;
    record.frameCount = Number.isFinite(parsed.frameCount) ? parsed.frameCount : null;
    record.boneCount = Array.isArray(parsed.bones) ? parsed.bones.length : null;
    record.valid = Number.isFinite(record.frameCount) && record.frameCount > 0 && record.boneCount > 0;
  } catch (error) {
    record.error = error.message;
  }

  return record;
}

function summarize(borgs) {
  const clipCount = sum(borgs, (borg) => borg.clipCount);
  const confirmedExportedClipCount = sum(borgs, (borg) => borg.confirmedExportedClipCount);
  const publicModelBorgCount = borgs.filter((borg) => borg.hasPublicModel).length;
  const exporterSafeBorgCount = borgs.filter((borg) => borg.exporterSafeWithCurrentScript).length;
  return {
    borgCount: borgs.length,
    publicModelBorgCount,
    exporterSafeBorgCount,
    clipCount,
    confirmedExportedClipCount,
    plannedClipCount: clipCount - confirmedExportedClipCount,
    blockedByCurrentExporterClipCount: sum(borgs, (borg) =>
      borg.exporterSafeWithCurrentScript ? 0 : borg.plannedClipCount,
    ),
    existingExportFileCount: sum(borgs, (borg) => borg.existingExports.length),
    borgsWithParseIssues: borgs.filter((borg) => borg.parseIssues.length > 0).map((borg) => borg.id),
  };
}

function findProofExportCandidate(borgs) {
  for (const borg of borgs) {
    if (borg.id === "pl0615" || !borg.hasPublicModel) continue;
    const clip = borg.clips.find(
      (candidate) => candidate.status !== "confirmed-exported" && candidate.exporterSafeWithCurrentScript,
    );
    if (!clip) continue;
    return {
      borgId: borg.id,
      sourceBlobOffset: clip.sourceBlobOffset,
      destinationPath: clip.destinationPath,
      reason: "first non-pl0615 borg with a discovered model, MOT clip, public DAE, and no confirmed matching export",
      command: clip.command,
      shellCommand: clip.shellCommand,
    };
  }
  return null;
}

function selectExportJobs(plan) {
  if (options.proof) {
    if (!plan.proofExportCandidate) return [];
    const borg = plan.borgs.find((candidate) => candidate.id === plan.proofExportCandidate.borgId);
    const clip = borg?.clips.find(
      (candidate) => candidate.sourceBlobOffset === plan.proofExportCandidate.sourceBlobOffset,
    );
    return clip ? [jobFromClip(borg.id, clip)] : [];
  }

  const jobs = [];
  for (const borg of plan.borgs) {
    if (options.borgs.size > 0 && !options.borgs.has(borg.id)) continue;
    for (const clip of borg.clips) {
      if (!options.includeConfirmed && clip.status === "confirmed-exported") continue;
      if (!clip.exporterSafeWithCurrentScript) continue;
      jobs.push(jobFromClip(borg.id, clip));
      if (options.limit && jobs.length >= options.limit) return jobs;
    }
  }
  return jobs;
}

function jobFromClip(borgId, clip) {
  const outputName = path.basename(clip.destinationPath);
  const sourceBlobOffset = clip.sourceBlobOffset;
  const spawnArgs = [EXPORTER_SCRIPT, options.region, borgId, `${sourceBlobOffset}:${outputName}`];
  return {
    borgId,
    sourceBlobOffset,
    destinationPath: clip.destinationPath,
    command: commandFor(borgId, Number.parseInt(sourceBlobOffset.slice(2), 16), outputName),
    spawnArgs,
  };
}

async function writePlanFiles(plan) {
  const jsonPath = path.resolve(options.planJson);
  const mdPath = path.resolve(options.planMd);
  await mkdir(path.dirname(jsonPath), { recursive: true });
  await mkdir(path.dirname(mdPath), { recursive: true });
  await writeFile(jsonPath, `${JSON.stringify(plan, null, 2)}\n`);
  await writeFile(mdPath, renderMarkdown(plan));
}

function renderMarkdown(plan) {
  const lines = [];
  const summary = plan.summary;
  lines.push("# Borg Animation Export Plan");
  lines.push("");
  lines.push(`Generated: ${plan.generatedAt}`);
  lines.push(`Region: ${plan.region}`);
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push(`- Borgs with model + MOT: ${summary.borgCount}`);
  lines.push(`- Borgs with public DAE/model evidence: ${summary.publicModelBorgCount}`);
  lines.push(`- Borgs safe for current single-borg exporter: ${summary.exporterSafeBorgCount}`);
  lines.push(`- MOT clips discovered: ${summary.clipCount}`);
  lines.push(`- Confirmed exported clips: ${summary.confirmedExportedClipCount}`);
  lines.push(`- Planned clips: ${summary.plannedClipCount}`);
  lines.push(`- Planned clips blocked by current exporter assumption: ${summary.blockedByCurrentExporterClipCount}`);
  lines.push(`- Existing export JSON files parsed: ${summary.existingExportFileCount}`);
  if (summary.borgsWithParseIssues.length > 0) {
    lines.push(`- Borgs with MOT parse issues: ${summary.borgsWithParseIssues.join(", ")}`);
  }
  lines.push("");
  lines.push("## Semantics");
  lines.push("");
  lines.push(
    "Generated names use structural candidate labels (`bankN_slotNN`). This confirms where clips live and how to export them, not gameplay meaning such as walk, attack, or hit reaction.",
  );
  lines.push(
    "Clips are marked exporter-safe only when the MOT's first blob starts at `0x240`, matching the current single-borg exporter's fixed table scan boundary.",
  );
  lines.push("");
  lines.push("## Proof Export Candidate");
  lines.push("");
  if (plan.proofExportCandidate) {
    const proof = plan.proofExportCandidate;
    lines.push(`- Borg: ${proof.borgId}`);
    lines.push(`- Source blob: ${proof.sourceBlobOffset}`);
    lines.push(`- Destination: \`${proof.destinationPath}\``);
    lines.push(`- Command: \`${proof.shellCommand}\``);
    lines.push(`- Reason: ${proof.reason}`);
  } else {
    lines.push("- No non-pl0615 proof candidate found.");
  }
  lines.push("");
  lines.push("## Borg Batch Summary");
  lines.push("");
  lines.push("| Borg | Public model | Exporter-safe | First blob | Clips | Confirmed exported | Planned | First planned command |");
  lines.push("|---|---:|---:|---:|---:|---:|---:|---|");
  for (const borg of plan.borgs) {
    const firstPlanned =
      borg.clips.find((clip) => clip.status !== "confirmed-exported" && clip.exporterSafeWithCurrentScript) ??
      borg.clips[0];
    lines.push(
      `| ${borg.id} | ${borg.hasPublicModel ? "yes" : "no"} | ${borg.exporterSafeWithCurrentScript ? "yes" : "no"} | ${borg.firstBlobOffset ?? ""} | ${borg.clipCount} | ${borg.confirmedExportedClipCount} | ${borg.plannedClipCount} | \`${firstPlanned ? firstPlanned.shellCommand : ""}\` |`,
    );
  }
  lines.push("");
  lines.push("## Confirmed Export Examples");
  lines.push("");
  const confirmed = plan.borgs.flatMap((borg) =>
    borg.clips
      .filter((clip) => clip.status === "confirmed-exported")
      .map((clip) => ({ borgId: borg.id, ...clip })),
  );
  if (confirmed.length === 0) {
    lines.push("- None yet.");
  } else {
    for (const clip of confirmed.slice(0, 12)) {
      lines.push(
        `- ${clip.borgId} ${clip.sourceBlobOffset} -> ${clip.confirmedExportPaths.map((item) => `\`${item}\``).join(", ")}`,
      );
    }
    if (confirmed.length > 12) lines.push(`- ... ${confirmed.length - 12} more in the JSON plan.`);
  }
  lines.push("");
  lines.push("## Recent Exports");
  lines.push("");
  if (plan.recentExports.length === 0) {
    lines.push("- None in this run.");
  } else {
    for (const job of plan.recentExports) {
      lines.push(`- ${job.borgId} ${job.sourceBlobOffset} -> \`${job.destinationPath}\``);
    }
  }
  lines.push("");
  return `${lines.join("\n")}\n`;
}

function printSummary(plan, exported) {
  const summary = plan.summary;
  console.log(`region: ${plan.region}`);
  console.log(`mode: ${plan.mode}`);
  console.log(`borgs: ${summary.borgCount} with model + MOT`);
  console.log(`clips: ${summary.clipCount} discovered`);
  console.log(`confirmed exported clips: ${summary.confirmedExportedClipCount}`);
  console.log(`planned clips: ${summary.plannedClipCount}`);
  console.log(`blocked by current exporter: ${summary.blockedByCurrentExporterClipCount}`);
  console.log(`recent exports: ${exported.length}`);
  console.log(`plan json: ${normalizeRel(options.planJson)}`);
  console.log(`plan md: ${normalizeRel(options.planMd)}`);
  if (plan.proofExportCandidate) {
    console.log(
      `proof candidate: ${plan.proofExportCandidate.borgId} ${plan.proofExportCandidate.sourceBlobOffset}`,
    );
  }
}

function commandFor(borgId, offset, outputName) {
  return ["node", EXPORTER_SCRIPT, options.region, borgId, `${hex(offset)}:${outputName}`];
}

function clipFileName(bankIndex, slotIndex) {
  return `anim_b${pad2(bankIndex)}_s${pad2(slotIndex)}_candidate.json`;
}

function pad2(value) {
  return value.toString(10).padStart(2, "0");
}

function hex(value) {
  return `0x${value.toString(16).toUpperCase()}`;
}

function rel(filePath) {
  return normalizeRel(path.relative(repoRoot, filePath));
}

function normalizeRel(filePath) {
  return filePath.split(path.sep).join("/");
}

function commandToString(command) {
  return command.map(quoteArg).join(" ");
}

function quoteArg(arg) {
  return /^[A-Za-z0-9_./:=\\-]+$/.test(arg) ? arg : JSON.stringify(arg);
}

function pushMap(map, key, value) {
  if (!map.has(key)) map.set(key, []);
  map.get(key).push(value);
}

function sum(items, project) {
  return items.reduce((total, item) => total + project(item), 0);
}

function mustBeDir(candidate, label) {
  if (!fs.existsSync(candidate) || !fs.statSync(candidate).isDirectory()) {
    fail(`missing ${label}: ${rel(candidate)}`);
  }
}

function mustBeFile(candidate, label) {
  if (!fs.existsSync(candidate) || !fs.statSync(candidate).isFile()) {
    fail(`missing ${label}: ${rel(candidate)}`);
  }
}

function fail(message) {
  console.error(`export-all-borg-animations: ${message}`);
  process.exit(1);
}
