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
  input: ["pad-read", "pad-post-read-normalization", "pad-normalization-complete", "game-pad-normalization-cluster"],
  actorInput: [
    "normalized-pad-slot0-current-read",
    "normalized-pad-slot0-pressed-read",
    "player-input-update-simple",
    "player-input-update-with-69960",
    "player-input-bridge",
    "input-command-mask-helper",
    "post-input-actor-command-update",
    "active-borg-command-current",
    "active-borg-command-pressed",
  ],
  commandConsumer: [
    "z-command-state-candidate",
    "x-table-dispatch-803188e8",
    "x-pressed-action-transition-candidate",
    "bx-pressed-borg-action-candidate",
    "bx-table-dispatch-803448b0",
    "bx-borg-conditional-action-061e",
  ],
  action: [
    "borg-state-dispatch",
    "state-transition-primitive",
    "active-action-handler-invuln",
    "action-helper-cluster",
    "action-handler-table",
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

const COMMAND_CONSUMER_IDS = new Set(PROOF_IDS.commandConsumer);
const AUDIO_IDS = new Set(PROOF_IDS.audio);

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
  return [...new Set([...(bp.ids ?? []), ...(wp.ids ?? []), wp.id].filter(Boolean))];
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

function decodeU32(raw) {
  if (typeof raw !== "string" || raw.length < 8) return null;
  const value = Number.parseInt(raw.slice(0, 8), 16) >>> 0;
  return Number.isInteger(value) ? { raw: raw.slice(0, 8), value, hex: `0x${value.toString(16).padStart(8, "0")}` } : null;
}

function hex(value, digits = 8) {
  return `0x${(value >>> 0).toString(16).padStart(digits, "0")}`;
}

function regHex(hit, name) {
  const value = hit.regs?.[name]?.value;
  return Number.isInteger(value) ? hex(value) : null;
}

function bytesFromStruct(hit) {
  const raw = hit.activeBaseStruct?.bytes?.raw;
  if (typeof raw !== "string" || /[^0-9a-fA-F]/.test(raw)) return null;
  return Buffer.from(raw, "hex");
}

function readU8(bytes, offset) {
  return bytes && offset < bytes.length ? bytes.readUInt8(offset) : null;
}

function readU16(bytes, offset) {
  return bytes && offset + 1 < bytes.length ? bytes.readUInt16BE(offset) : null;
}

function readU32(bytes, offset) {
  return bytes && offset + 3 < bytes.length ? bytes.readUInt32BE(offset) : null;
}

function decodeActorFields(hit) {
  const bytes = bytesFromStruct(hit);
  if (!bytes) return null;
  const u8 = (offset) => readU8(bytes, offset);
  const u16 = (offset) => readU16(bytes, offset);
  const u32 = (offset) => readU32(bytes, offset);
  const actor = hit.activeBaseStruct?.base ?? regHex(hit, "r3");
  return {
    actor,
    borgId: u16(0x3e8) == null ? null : hex(u16(0x3e8), 4),
    actionIndex540: u8(0x540) == null ? null : hex(u8(0x540), 2),
    localPhase544Word: u32(0x544) == null ? null : hex(u32(0x544)),
    actionSelector591: u8(0x591) == null ? null : hex(u8(0x591), 2),
    commandCurrent5b4: u32(0x5b4) == null ? null : hex(u32(0x5b4)),
    commandPrevious5b8: u32(0x5b8) == null ? null : hex(u32(0x5b8)),
    commandPressed5bc: u32(0x5bc) == null ? null : hex(u32(0x5bc)),
    commandReleased5c0: u32(0x5c0) == null ? null : hex(u32(0x5c0)),
    stateFlags5d4: u32(0x5d4) == null ? null : hex(u32(0x5d4)),
    transitionState6fe: u8(0x6fe) == null ? null : hex(u8(0x6fe), 2),
    zState73c: u8(0x73c) == null ? null : hex(u8(0x73c), 2),
    paramTier74a: u8(0x74a) == null ? null : hex(u8(0x74a), 2),
    paramTier74e: u16(0x74e) == null ? null : hex(u16(0x74e), 4),
    paramTimer750: u16(0x750) == null ? null : hex(u16(0x750), 4),
  };
}

function compactRegs(hit, names) {
  return Object.fromEntries(names.map((name) => [name, regHex(hit, name)]));
}

function summarizeTrace(file) {
  const data = JSON.parse(fs.readFileSync(file, "utf8"));
  const counts = new Map();
  const groups = new Map();
  const padButtons = new Map();
  const observedButtons = new Set();
  let firstNonNeutralPad = null;
  let firstNormalizedPad = null;
  let firstCommandCurrent = null;
  let firstCommandPressed = null;
  let firstCommandMask = null;
  let firstCommandConsumer = null;
  let firstAudio = null;
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
      for (const button of decoded.buttons) {
        if (button !== "none") observedButtons.add(button);
      }
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
    if (!firstCommandCurrent && ids.includes("active-borg-command-current")) {
      const decoded = decodeU32(hit.watchpoint?.current?.raw);
      if (decoded) firstCommandCurrent = { hit: hit.index ?? null, pc: hit.pc ?? null, lr: hit.lr ?? null, ...decoded };
    }
    if (!firstNormalizedPad && ids.includes("pad-normalization-complete")) {
      const raw = hit.fixedMemory?.normalizedPad?.bytes?.raw;
      const current = decodeU32(raw);
      const previous = decodeU32(raw?.slice(8));
      const pressed = decodeU32(raw?.slice(16));
      const released = decodeU32(raw?.slice(24));
      if (current || pressed) {
        firstNormalizedPad = {
          hit: hit.index ?? null,
          pc: hit.pc ?? null,
          lr: hit.lr ?? null,
          current,
          previous,
          pressed,
          released,
        };
      }
    }
    if (!firstCommandPressed && ids.includes("active-borg-command-pressed")) {
      const decoded = decodeU32(hit.watchpoint?.current?.raw);
      if (decoded) firstCommandPressed = { hit: hit.index ?? null, pc: hit.pc ?? null, lr: hit.lr ?? null, ...decoded };
    }
    if (!firstCommandMask && ids.includes("input-command-mask-helper")) {
      firstCommandMask = {
        hit: hit.index ?? null,
        pc: hit.pc ?? null,
        lr: hit.lr ?? null,
        regs: compactRegs(hit, ["r3", "r4", "r5", "r6"]),
      };
    }
    if (!firstCommandConsumer && ids.some((id) => COMMAND_CONSUMER_IDS.has(id))) {
      firstCommandConsumer = {
        hit: hit.index ?? null,
        ids,
        pc: hit.pc ?? null,
        lr: hit.lr ?? null,
        regs: compactRegs(hit, ["r3", "r4", "r5", "r6", "r31"]),
        actorFields: decodeActorFields(hit),
      };
    }
    if (!firstAudio && ids.some((id) => AUDIO_IDS.has(id))) {
      firstAudio = {
        hit: hit.index ?? null,
        ids,
        pc: hit.pc ?? null,
        lr: hit.lr ?? null,
        regs: compactRegs(hit, ["r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10"]),
      };
    }
  }
  const countAny = (ids) => ids.reduce((sum, id) => sum + (counts.get(id) ?? 0), 0);
  const hasBOrXPad = observedButtons.has("B") || observedButtons.has("X");
  const hasZPad = observedButtons.has("Z");
  const inputSource = data.padInjection ? "gdb-pad-injection" : "controller-or-keyboard-capture";
  const gates = {
    inputObserved: countAny(PROOF_IDS.input) > 0,
    nonNeutralPadObserved: firstNonNeutralPad != null,
    bOrXPadObserved: hasBOrXPad,
    zPadObserved: hasZPad,
    actorInputObserved: countAny(PROOF_IDS.actorInput) > 0,
    actionStateObserved: countAny(PROOF_IDS.action) > 0,
    paramTierObserved: countAny(PROOF_IDS.paramTier) > 0,
    audioObserved: countAny(PROOF_IDS.audio) > 0,
  };
  return {
    file: path.relative(repoRoot, file),
    hits: data.hits?.length ?? 0,
    errors: data.errors?.length ?? 0,
    inputSource,
    padInjection: data.padInjection
      ? {
          ...data.padInjection,
          writeCount: data.padInjectionWrites?.length ?? 0,
          firstWrite: data.padInjectionWrites?.[0] ?? null,
        }
      : null,
    groups: Object.fromEntries([...groups.entries()].sort()),
    padButtons: Object.fromEntries([...padButtons.entries()].sort((a, b) => b[1] - a[1])),
    observedButtons: [...observedButtons].sort(),
    firstNonNeutralPad,
    firstNormalizedPad,
    firstCommandCurrent,
    firstCommandPressed,
    firstCommandMask,
    firstCommandConsumer,
    firstAudio,
    proofCounts: Object.fromEntries(
      Object.entries(PROOF_IDS).map(([name, ids]) => [
        name,
        Object.fromEntries(ids.map((id) => [id, counts.get(id) ?? 0])),
      ]),
    ),
    gates,
    decisive: {
      bxActionMapping:
        gates.bOrXPadObserved && gates.actionStateObserved
          ? `candidate (${inputSource}): same trace has B/X PAD sample + action-state hits; inspect PAD bytes/registers to map B/X exactly`
          : gates.bOrXPadObserved && countAny(PROOF_IDS.commandConsumer) > 0
            ? `partial (${inputSource}): same trace has B/X PAD sample + command-consumer candidate; inspect actor fields/callsite before promoting action mapping`
          : gates.bOrXPadObserved && gates.actorInputObserved
            ? `partial (${inputSource}): B/X PAD sample reached actor input bridge/command fields; still missing action-state transition/handler hit`
          : "missing: needs non-neutral B or X PAD sample + action-state hits in the same labeled B/X capture",
      zPowerUp:
        gates.zPadObserved && gates.paramTierObserved
          ? `candidate (${inputSource}): same trace has Z PAD sample + param-tier hits; inspect PAD bytes/registers to tie to Z`
          : "missing: needs non-neutral Z-labeled PAD sample + param-tier hits",
      audioCue:
        gates.nonNeutralPadObserved && gates.actionStateObserved && gates.audioObserved
          ? `candidate (${inputSource}): same trace has input + action + audio hits; inspect call args/cue handles before assigning cue IDs`
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
