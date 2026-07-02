#!/usr/bin/env node
// Summarize Dolphin GDB trace JSON without committing raw captures.
//
// Raw traces stay in ignored user-data/. This prints the proof-relevant hit counts
// for B/X action mapping, Z param-tier side effects, and audio cue tracing.

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const args = process.argv.slice(2);
const inputs = args.length
  ? args
  : [path.join(repoRoot, "user-data", "dolphin-trace", "traces")];

const PROOF_IDS = {
  input: ["pad-read", "game-pad-normalization-cluster"],
  action: [
    "borg-state-dispatch",
    "state-transition-primitive",
    "active-action-handler-invuln",
    "action-helper-cluster",
    "battle-frame-target-action-dispatch",
  ],
  paramTier: [
    "param-tier-reset",
    "param-tier-delta-127",
    "param-tier-delta-63",
    "param-tier-refresh",
    "battle-frame-target-action-dispatch",
  ],
  audio: [
    "audio-sfx-playing",
    "audio-object-callback",
    "audio-seq-continue",
    "audio-thp-stop",
    "audio-sfx-init",
    "audio-sfx-update",
  ],
};

function walkJsonFiles(inputPath) {
  if (!fs.existsSync(inputPath)) return [];
  const stat = fs.statSync(inputPath);
  if (stat.isFile()) return inputPath.endsWith(".json") ? [inputPath] : [];
  if (!stat.isDirectory()) return [];
  const out = [];
  for (const entry of fs.readdirSync(inputPath, { withFileTypes: true })) {
    out.push(...walkJsonFiles(path.join(inputPath, entry.name)));
  }
  return out;
}

function idsForHit(hit) {
  const bp = hit.breakpoint ?? {};
  const wp = hit.watchpoint ?? {};
  return [...(bp.ids ?? []), ...(wp.ids ?? [])].filter(Boolean);
}

function summarizeTrace(file) {
  const data = JSON.parse(fs.readFileSync(file, "utf8"));
  const counts = new Map();
  const groups = new Map();
  for (const hit of data.hits ?? []) {
    for (const id of idsForHit(hit)) counts.set(id, (counts.get(id) ?? 0) + 1);
    const group = hit.breakpoint?.groups?.[0] ?? hit.watchpoint?.groups?.[0] ?? null;
    if (group) groups.set(group, (groups.get(group) ?? 0) + 1);
  }
  const countAny = (ids) => ids.reduce((sum, id) => sum + (counts.get(id) ?? 0), 0);
  const gates = {
    inputObserved: countAny(PROOF_IDS.input) > 0,
    actionStateObserved: countAny(PROOF_IDS.action) > 0,
    paramTierObserved: countAny(PROOF_IDS.paramTier) > 0,
    audioObserved: countAny(PROOF_IDS.audio) > 0,
  };
  return {
    file: path.relative(repoRoot, file),
    hits: data.hits?.length ?? 0,
    errors: data.errors?.length ?? 0,
    groups: Object.fromEntries([...groups.entries()].sort()),
    proofCounts: Object.fromEntries(
      Object.entries(PROOF_IDS).map(([name, ids]) => [
        name,
        Object.fromEntries(ids.map((id) => [id, counts.get(id) ?? 0])),
      ]),
    ),
    gates,
    decisive: {
      bxActionMapping:
        gates.inputObserved && gates.actionStateObserved
          ? "candidate: same trace has input + action-state hits; inspect PAD bytes/registers to map B/X exactly"
          : "missing: needs input + action-state hits in the same labeled B/X capture",
      zPowerUp:
        gates.inputObserved && gates.paramTierObserved
          ? "candidate: same trace has input + param-tier hits; inspect PAD bytes/registers to tie to Z"
          : "missing: needs Z-labeled input + param-tier hits",
      audioCue:
        gates.inputObserved && gates.actionStateObserved && gates.audioObserved
          ? "candidate: same trace has input + action + audio hits; inspect call args/cue handles before assigning cue IDs"
          : "missing: needs action-labeled trace with audio hits",
    },
  };
}

const files = inputs.flatMap((input) => walkJsonFiles(path.resolve(input))).sort();
if (files.length === 0) {
  console.error(`no trace JSON files found under: ${inputs.join(", ")}`);
  process.exit(1);
}

const summaries = files.map(summarizeTrace);
for (const summary of summaries) {
  console.log(JSON.stringify(summary, null, 2));
}
