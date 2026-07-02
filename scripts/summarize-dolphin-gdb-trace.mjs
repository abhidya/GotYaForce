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

const PAD_BUTTONS = {
  0x0001: "dLeft",
  0x0002: "dRight",
  0x0004: "dDown",
  0x0008: "dUp",
  0x0010: "Z",
  0x0020: "R",
  0x0040: "L",
  0x0100: "A",
  0x0200: "B",
  0x0400: "X",
  0x0800: "Y",
  0x1000: "Start",
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

function decodePadButtons(raw) {
  if (typeof raw !== "string" || raw.length < 4) return null;
  const button = Number.parseInt(raw.slice(0, 4), 16);
  if (!Number.isInteger(button)) return null;
  const buttons = Object.entries(PAD_BUTTONS)
    .filter(([bit]) => button & Number(bit))
    .map(([, name]) => name);
  return {
    raw: raw.slice(0, 24),
    button,
    buttons: buttons.length > 0 ? buttons : ["none"],
  };
}

function summarizeTrace(file) {
  const data = JSON.parse(fs.readFileSync(file, "utf8"));
  const counts = new Map();
  const groups = new Map();
  const padButtons = new Map();
  let firstNonNeutralPad = null;
  for (const hit of data.hits ?? []) {
    const ids = idsForHit(hit);
    for (const id of ids) counts.set(id, (counts.get(id) ?? 0) + 1);
    const group = hit.breakpoint?.groups?.[0] ?? hit.watchpoint?.groups?.[0] ?? null;
    if (group) groups.set(group, (groups.get(group) ?? 0) + 1);
    if (ids.includes("pad-read")) {
      const decoded = decodePadButtons(hit.pointers?.r3?.bytes?.raw);
      if (!decoded) continue;
      const label = decoded.buttons.join("+");
      padButtons.set(label, (padButtons.get(label) ?? 0) + 1);
      if (!firstNonNeutralPad && label !== "none") {
        firstNonNeutralPad = {
          hit: hit.index ?? null,
          pc: hit.pc ?? null,
          lr: hit.lr ?? null,
          raw: decoded.raw,
          buttons: decoded.buttons,
        };
      }
    }
  }
  const countAny = (ids) => ids.reduce((sum, id) => sum + (counts.get(id) ?? 0), 0);
  const gates = {
    inputObserved: countAny(PROOF_IDS.input) > 0,
    nonNeutralPadObserved: firstNonNeutralPad != null,
    actionStateObserved: countAny(PROOF_IDS.action) > 0,
    paramTierObserved: countAny(PROOF_IDS.paramTier) > 0,
    audioObserved: countAny(PROOF_IDS.audio) > 0,
  };
  return {
    file: path.relative(repoRoot, file),
    hits: data.hits?.length ?? 0,
    errors: data.errors?.length ?? 0,
    groups: Object.fromEntries([...groups.entries()].sort()),
    padButtons: Object.fromEntries([...padButtons.entries()].sort((a, b) => b[1] - a[1])),
    firstNonNeutralPad,
    proofCounts: Object.fromEntries(
      Object.entries(PROOF_IDS).map(([name, ids]) => [
        name,
        Object.fromEntries(ids.map((id) => [id, counts.get(id) ?? 0])),
      ]),
    ),
    gates,
    decisive: {
      bxActionMapping:
        gates.nonNeutralPadObserved && gates.actionStateObserved
          ? "candidate: same trace has input + action-state hits; inspect PAD bytes/registers to map B/X exactly"
          : "missing: needs non-neutral B/X PAD sample + action-state hits in the same labeled B/X capture",
      zPowerUp:
        gates.nonNeutralPadObserved && gates.paramTierObserved
          ? "candidate: same trace has input + param-tier hits; inspect PAD bytes/registers to tie to Z"
          : "missing: needs non-neutral Z-labeled PAD sample + param-tier hits",
      audioCue:
        gates.nonNeutralPadObserved && gates.actionStateObserved && gates.audioObserved
          ? "candidate: same trace has input + action + audio hits; inspect call args/cue handles before assigning cue IDs"
          : "missing: needs non-neutral action-labeled trace with audio hits",
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
