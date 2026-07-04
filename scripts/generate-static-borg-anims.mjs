#!/usr/bin/env node
// Generate source-faithful static animation indexes for roster Borgs whose
// extracted PZZ motion-bank member is empty. These are not placeholder guesses:
// the source archive has a zero-byte `*mot.bin`, so a no-op clip is the only
// animation the asset pipeline can honestly provide.

import fs from "node:fs";
import path from "node:path";
import process from "node:process";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const manifestPath = path.join(repoRoot, "research", "asset-inventory", "pzz-member-extraction-manifest.json");
const rosterPath = path.join(repoRoot, "packages", "assets", "data", "borgs.json");
const modelsRoot = path.join(repoRoot, "apps", "game", "public", "models");
const reportPath = path.join(repoRoot, "research", "asset-inventory", "static-borg-animation-indexes.md");

const STATIC_FILE = "anim_static_source_empty_mot.json";
const STATIC_BANKS = [
  { group: 0, slot: 0, label: "idle" },
  { group: 0, slot: 1, label: "move" },
  { group: 0, slot: 2, label: "dash_fwd" },
  { group: 0, slot: 3, label: "dash_back" },
  { group: 0, slot: 4, label: "dash_left" },
  { group: 0, slot: 5, label: "dash_right" },
  { group: 0, slot: 6, label: "jump_takeoff" },
  { group: 0, slot: 7, label: "jump_land" },
  { group: 0, slot: 9, label: "fly_transition" },
  { group: 0, slot: 14, label: "pose_short" },
  { group: 1, slot: 0, label: "attack_s0" },
  { group: 1, slot: 1, label: "attack_lunge_s1" },
  { group: 3, slot: 0, label: "hit_react_s0" },
  { group: 4, slot: 0, label: "down_s0" },
  { group: 4, slot: 1, label: "special_s1" },
  { group: 5, slot: 1, label: "death" },
  { group: 5, slot: 2, label: "victory" },
];

const args = new Set(process.argv.slice(2));
const force = args.has("--force");
const includeNonRoster = args.has("--include-non-roster");

if (args.has("--help") || args.has("-h")) {
  console.log(`usage: node scripts/generate-static-borg-anims.mjs [--force] [--include-non-roster]

Reads:
  research/asset-inventory/pzz-member-extraction-manifest.json
  packages/assets/data/borgs.json

Writes static no-op animation indexes under:
  apps/game/public/models/<borg>/

By default, only roster Borgs are emitted. --include-non-roster also emits
source-empty motion banks that are present in the extraction manifest but not
listed in packages/assets/data/borgs.json.`);
  process.exit(0);
}

for (const arg of args) {
  if (arg !== "--force" && arg !== "--include-non-roster") {
    console.error(`unknown option: ${arg}`);
    process.exit(2);
  }
}

function rel(filePath) {
  return path.relative(repoRoot, filePath).replaceAll(path.sep, "/");
}

function readJson(filePath) {
  return JSON.parse(fs.readFileSync(filePath, "utf8"));
}

function writeJson(filePath, value) {
  fs.writeFileSync(filePath, `${JSON.stringify(value, null, 2)}\n`);
}

function md(value) {
  return String(value ?? "").replaceAll("|", "\\|").replaceAll("\n", " ");
}

function sourceEmptyMotionRecords(manifest) {
  return manifest.records
    .filter(
      (record) =>
        record?.inferredKind === "motion-bank" &&
        typeof record.borgId === "string" &&
        record.inferredName === `${record.borgId.toLowerCase()}mot.bin` &&
        record.payloadBytes === 0 &&
        record.blockCount === 0,
    )
    .map((record) => ({
      ...record,
      borgId: record.borgId.toLowerCase(),
    }))
    .sort((a, b) => a.borgId.localeCompare(b.borgId));
}

function staticClip(id) {
  return {
    name: `${id}_static_source_empty_mot`,
    frameCount: 1,
    fps: 60,
    bones: [],
  };
}

function staticIndex(record) {
  const source = {
    kind: "source-empty-motion-bank",
    archive: record.sourceArchive,
    memberIndex: record.memberIndex,
    inferredName: record.inferredName,
    payloadBytes: record.payloadBytes,
    blockCount: record.blockCount,
    tableWord: record.tableWord,
  };
  return {
    borg: record.borgId,
    bankCount: STATIC_BANKS.length,
    source,
    banks: STATIC_BANKS.map((bank) => ({
      file: STATIC_FILE,
      group: bank.group,
      slot: bank.slot,
      label: bank.label,
      frames: 1,
      animJoints: 0,
      rootSpanX: 0,
      rootSpanY: 0,
      rootSpanZ: 0,
      source: source.kind,
    })),
  };
}

function canOverwriteIndex(filePath) {
  if (!fs.existsSync(filePath)) return true;
  if (force) return true;
  try {
    const existing = readJson(filePath);
    return existing?.source?.kind === "source-empty-motion-bank";
  } catch {
    return false;
  }
}

function renderReport({ emitted, skippedNonRoster, protectedExisting }) {
  const lines = [];
  lines.push("# Static Borg Animation Indexes");
  lines.push("");
  lines.push(`Generated: ${new Date().toISOString()}`);
  lines.push("");
  lines.push("These indexes are generated only for Borgs whose original PZZ motion-bank member is present but empty (`payloadBytes: 0`, `blockCount: 0`). The emitted clip is a one-frame no-op so runtime animation references resolve without inventing motion that is absent from the source archive.");
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push("| Metric | Count |");
  lines.push("|---|---:|");
  lines.push(`| Static roster indexes emitted | ${emitted.length} |`);
  lines.push(`| Non-roster source-empty motion banks skipped | ${skippedNonRoster.length} |`);
  lines.push(`| Existing non-static indexes protected | ${protectedExisting.length} |`);
  lines.push("");
  lines.push("## Emitted");
  lines.push("");
  lines.push("| Borg | Source member | Output |");
  lines.push("|---|---|---|");
  for (const item of emitted) {
    lines.push(`| \`${item.id}\` | \`${md(item.sourceMember)}\` | \`${md(rel(item.indexPath))}\` |`);
  }
  if (emitted.length === 0) lines.push("| none |  |  |");
  lines.push("");
  lines.push("## Skipped Non-Roster");
  lines.push("");
  if (skippedNonRoster.length === 0) {
    lines.push("None.");
  } else {
    lines.push(skippedNonRoster.map((record) => `- \`${record.borgId}\` (${record.inferredName})`).join("\n"));
  }
  lines.push("");
  lines.push("## Reproduce");
  lines.push("");
  lines.push("```bash");
  lines.push("rtk node scripts/generate-static-borg-anims.mjs --force");
  lines.push("rtk node scripts/validate-borg-animation-actions.mjs --strict");
  lines.push("```");
  lines.push("");
  return lines.join("\n");
}

if (!fs.existsSync(manifestPath)) {
  console.error(`missing ${rel(manifestPath)}`);
  process.exit(1);
}
if (!fs.existsSync(rosterPath)) {
  console.error(`missing ${rel(rosterPath)}`);
  process.exit(1);
}

const manifest = readJson(manifestPath);
const roster = new Set(readJson(rosterPath).borgs.map((borg) => borg.id.toLowerCase()));
const records = sourceEmptyMotionRecords(manifest);
const selected = includeNonRoster ? records : records.filter((record) => roster.has(record.borgId));
const skippedNonRoster = records.filter((record) => !roster.has(record.borgId));
const emitted = [];
const protectedExisting = [];

for (const record of selected) {
  const outDir = path.join(modelsRoot, record.borgId);
  const indexPath = path.join(outDir, "anim_index.json");
  if (!canOverwriteIndex(indexPath)) {
    protectedExisting.push({ id: record.borgId, indexPath });
    continue;
  }

  fs.mkdirSync(outDir, { recursive: true });
  writeJson(path.join(outDir, STATIC_FILE), staticClip(record.borgId));
  writeJson(indexPath, staticIndex(record));
  emitted.push({
    id: record.borgId,
    sourceMember: record.inferredName,
    indexPath,
  });
}

fs.mkdirSync(path.dirname(reportPath), { recursive: true });
fs.writeFileSync(reportPath, renderReport({ emitted, skippedNonRoster, protectedExisting }));

console.log(
  [
    `source-empty motion banks ${records.length}`,
    `selected ${selected.length}`,
    `emitted ${emitted.length}`,
    `skipped non-roster ${skippedNonRoster.length}`,
    `protected existing ${protectedExisting.length}`,
    `wrote ${rel(reportPath)}`,
  ].join("; "),
);

if (protectedExisting.length > 0) {
  process.exitCode = 1;
}
