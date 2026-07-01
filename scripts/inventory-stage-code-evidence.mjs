#!/usr/bin/env node
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const region = process.argv.slice(2).find((arg) => !arg.startsWith("--")) ?? "GG4E";
const outDir = path.join(repoRoot, "research", "asset-inventory");
const outJson = path.join(outDir, "stage-code-evidence.json");
const outMd = path.join(outDir, "stage-code-evidence.md");

const paths = {
  bootDol: path.join(repoRoot, "user-data", region, "disc", "sys", "boot.dol"),
  afsRoot: path.join(repoRoot, "user-data", region, "afs_data", "root"),
  publicStagesManifest: path.join(repoRoot, "apps", "game", "public", "stages", "manifest.json"),
  runtimeAdapter: path.join(repoRoot, "apps", "game", "src", "sim", "adapter.ts"),
  tracePlan: path.join(repoRoot, "research", "traces", region, "breakpoints-watchpoints.json"),
};

for (const required of [paths.bootDol, paths.afsRoot, paths.publicStagesManifest, paths.runtimeAdapter]) {
  if (!fs.existsSync(required)) throw new Error(`missing required input: ${rel(required)}`);
}

const publicManifest = JSON.parse(fs.readFileSync(paths.publicStagesManifest, "utf8"));
const exportedStageIds = publicManifest.stages.map((stage) => stage.id).sort();
const sourceStageIds = fs
  .readdirSync(paths.afsRoot)
  .map((name) => /^st([0-9a-f]{2})_mdl\.arc$/i.exec(name)?.[1]?.toLowerCase())
  .filter(Boolean)
  .map((code) => `st${code}`)
  .sort();

const bootEvidence = scanBinaryForStageCodes(paths.bootDol, exportedStageIds);
const rootEvidence = scanRootStageReferences(exportedStageIds);
const runtimeAdapter = fs.readFileSync(paths.runtimeAdapter, "utf8");
const report = {
  generatedAt: new Date().toISOString(),
  scanner: rel(fileURLToPath(import.meta.url)),
  region,
  purpose:
    "Find direct stage-code evidence from the extracted disc/runtime without inferring arena-name or Challenge-mode mappings.",
  inputs: {
    bootDol: fileInfo(paths.bootDol),
    afsRoot: rel(paths.afsRoot),
    publicStagesManifest: rel(paths.publicStagesManifest),
    runtimeAdapter: rel(paths.runtimeAdapter),
    tracePlan: fs.existsSync(paths.tracePlan) ? rel(paths.tracePlan) : null,
  },
  exportedStageIds,
  sourceStageIds,
  summary: {
    exportedStageCount: exportedStageIds.length,
    sourceStageArchiveCount: sourceStageIds.length,
    bootDolStageCodeHitCount: bootEvidence.hits.length,
    bootDolUniqueStageCodeCount: bootEvidence.uniqueStageIds.length,
    rootStageReferenceFileCount: rootEvidence.filesWithStageRefs.length,
    runtimeFallbacksChallengeToDefault:
      runtimeAdapter.includes('normalized === "challenge"') && runtimeAdapter.includes("DEFAULT_ARENA_STAGE"),
    verifiedArenaNameMappingCount: 0,
  },
  bootDolStageCodeEvidence: bootEvidence,
  rootStageReferenceEvidence: rootEvidence,
  conclusion:
    "This scan proves the exported st## codes are present in disc/runtime artifacts, but it does not prove any human arena-name or Challenge rotation mapping. Keep runtime name mapping on st## literals until Dolphin/DOL control-flow tracing identifies the table that chooses stages.",
  nextTraceTasks: [
    "Trace writes/reads around BattleConfig arena selection and stage archive loads while entering Challenge battle 1.",
    "Break on file/archive open routines with watch strings for st##_mdl.arc and st##.pzz to capture the code path and selected stage id.",
    "Once a Challenge battle loads, record the selected st## literal and add only that proven id to runtime mapping/tests.",
  ],
};

fs.mkdirSync(outDir, { recursive: true });
fs.writeFileSync(outJson, `${JSON.stringify(report, null, 2)}\n`);
fs.writeFileSync(outMd, renderMarkdown(report));

console.log("stage code evidence inventory");
console.log(`exported stages: ${report.summary.exportedStageCount}`);
console.log(`boot.dol stage-code hits: ${report.summary.bootDolStageCodeHitCount}`);
console.log(`root files with stage refs: ${report.summary.rootStageReferenceFileCount}`);
console.log(`wrote ${rel(outJson)}`);
console.log(`wrote ${rel(outMd)}`);

function scanBinaryForStageCodes(file, allowedIds) {
  const allowed = new Set(allowedIds);
  const buffer = fs.readFileSync(file);
  const hits = [];
  const seenByOffset = new Set();
  for (let i = 0; i <= buffer.length - 4; i += 1) {
    if (buffer[i] !== 0x73 || buffer[i + 1] !== 0x74) continue;
    const code = buffer.toString("latin1", i, i + 4).toLowerCase();
    if (!/^st[0-9a-f]{2}$/.test(code) || !allowed.has(code)) continue;
    if (seenByOffset.has(i)) continue;
    seenByOffset.add(i);
    hits.push({
      stageId: code,
      fileOffset: hex(i),
      nearbyAscii: nearbyAscii(buffer, i, 56),
    });
  }
  return {
    path: rel(file),
    hits,
    uniqueStageIds: [...new Set(hits.map((hit) => hit.stageId))].sort(),
  };
}

function scanRootStageReferences(stageIds) {
  const wanted = new Set(stageIds);
  const files = fs.readdirSync(paths.afsRoot).sort();
  const filesWithStageRefs = [];
  for (const name of files) {
    const full = path.join(paths.afsRoot, name);
    if (!fs.statSync(full).isFile()) continue;
    const matches = new Set();
    for (const id of stageIds) {
      if (name.toLowerCase().includes(id)) matches.add(id);
    }
    if (!matches.size) continue;
    filesWithStageRefs.push({
      path: rel(full),
      name,
      bytes: fs.statSync(full).size,
      stageIds: [...matches].filter((id) => wanted.has(id)).sort(),
    });
  }
  return {
    afsRoot: rel(paths.afsRoot),
    filesWithStageRefs,
  };
}

function nearbyAscii(buffer, offset, radius) {
  const start = Math.max(0, offset - radius);
  const end = Math.min(buffer.length, offset + 4 + radius);
  let text = "";
  for (let i = start; i < end; i += 1) {
    const value = buffer[i];
    text += value >= 0x20 && value <= 0x7e ? String.fromCharCode(value) : ".";
  }
  return text.replace(/\.+/g, ".").slice(0, 140);
}

function renderMarkdown(report) {
  const lines = [];
  lines.push("# Stage Code Evidence");
  lines.push("");
  lines.push(`Generated: ${report.generatedAt}`);
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push(`- Exported stage folders: ${report.summary.exportedStageCount}`);
  lines.push(`- Source stage archives: ${report.summary.sourceStageArchiveCount}`);
  lines.push(`- boot.dol stage-code hits: ${report.summary.bootDolStageCodeHitCount}`);
  lines.push(`- boot.dol unique stage codes: ${report.summary.bootDolUniqueStageCodeCount}`);
  lines.push(`- Root files with stage refs: ${report.summary.rootStageReferenceFileCount}`);
  lines.push(`- Verified arena-name mappings found: ${report.summary.verifiedArenaNameMappingCount}`);
  lines.push("");
  lines.push("## boot.dol Stage-Code Hits");
  lines.push("");
  lines.push("| Stage | Offset | Nearby ASCII |");
  lines.push("| --- | ---: | --- |");
  for (const hit of report.bootDolStageCodeEvidence.hits.slice(0, 80)) {
    lines.push(`| ${hit.stageId} | ${hit.fileOffset} | \`${escapeMd(hit.nearbyAscii)}\` |`);
  }
  if (report.bootDolStageCodeEvidence.hits.length > 80) {
    lines.push(`| ... | ... | ${report.bootDolStageCodeEvidence.hits.length - 80} more hits in JSON |`);
  }
  lines.push("");
  lines.push("## Root Stage Files");
  lines.push("");
  lines.push("| File | Stage ids | Bytes |");
  lines.push("| --- | --- | ---: |");
  for (const file of report.rootStageReferenceEvidence.filesWithStageRefs) {
    lines.push(`| ${file.path} | ${file.stageIds.join(", ")} | ${file.bytes} |`);
  }
  lines.push("");
  lines.push("## Conclusion");
  lines.push("");
  lines.push(report.conclusion);
  lines.push("");
  lines.push("## Next Trace Tasks");
  lines.push("");
  for (const task of report.nextTraceTasks) lines.push(`- ${task}`);
  lines.push("");
  return `${lines.join("\n")}\n`;
}

function fileInfo(file) {
  const info = fs.statSync(file);
  return { path: rel(file), bytes: info.size };
}

function rel(file) {
  return path.relative(repoRoot, file).replaceAll("\\", "/");
}

function hex(value) {
  return `0x${value.toString(16).padStart(8, "0")}`;
}

function escapeMd(value) {
  return String(value).replaceAll("|", "\\|").replaceAll("`", "'");
}
