#!/usr/bin/env node
// Validate exported Borg animation labels against the runtime resolver.
//
// The SLOT_LABELS, SLOT_FALLBACKS, pick order, and bank sort below intentionally
// mirror apps/game/src/main.ts so this reports the app's current behavior rather
// than inventing a second animation label system.

import fs from "node:fs";
import path from "node:path";
import process from "node:process";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const modelsRoot = path.join(repoRoot, "apps", "game", "public", "models");
const reportPath = path.join(repoRoot, "research", "asset-inventory", "borg-animation-action-gaps.md");

const CANONICAL_SLOTS = [
  "idle",
  "move",
  "dash_fwd",
  "dash_back",
  "dash_left",
  "dash_right",
  "jump",
  "fly",
  "shoot",
  "melee",
  "special",
  "hit",
  "death",
];

// Mirrored from apps/game/src/main.ts SLOT_LABELS.
const SLOT_LABELS = {
  idle: [/^idle$/],
  move: [/^move$/, /^move_s\d+$/],
  dash: [/^dash_fwd$/, /^dash_(right|left|back)$/, /^boost$/],
  dash_fwd: [/^dash_fwd$/],
  dash_back: [/^dash_back$/],
  dash_left: [/^dash_left$/],
  dash_right: [/^dash_right$/],
  jump: [/^jump_takeoff$/, /^fly_transition$/, /^boost$/],
  fly: [/^boost$/, /^fly_transition$/, /^move_s\d+$/],
  attack: [/^attack_s\d+$/, /^attack_lunge_s\d+$/],
  melee: [/^attack_lunge_s\d+$/, /^attack_s\d+$/],
  shoot: [/^attack_s\d+$/, /^special_s\d+$/],
  special: [/^special_s\d+$/],
  hit: [/^hit_react_s\d+$/, /^guard_s\d+$/],
  down: [/^hit_react_s\d+$/, /^guard_s\d+$/, /^death$/],
  death: [/^death$/, /^win_or_death$/],
  spawn: [/^pose_short$/, /^idle$/],
  victory: [/^victory$/, /^win_or_death$/],
};

// Mirrored from apps/game/src/main.ts SLOT_FALLBACKS.
const SLOT_FALLBACKS = {
  dash_fwd: ["dash", "move", "idle"],
  dash_back: ["dash", "move", "idle"],
  dash_left: ["dash", "move", "idle"],
  dash_right: ["dash", "move", "idle"],
  dash: ["move", "idle"],
  jump: ["fly", "move", "idle"],
  fly: ["jump", "move", "idle"],
  attack: ["melee", "shoot", "move", "idle"],
  melee: ["attack", "move", "idle"],
  shoot: ["attack", "special", "move", "idle"],
  special: ["attack", "idle"],
  hit: ["down", "idle"],
  down: ["hit", "death", "idle"],
  death: ["down", "idle"],
  spawn: ["idle"],
  victory: ["idle"],
};

const args = new Set(process.argv.slice(2));
const strict = args.has("--strict");

if (args.has("--help") || args.has("-h")) {
  console.log(`usage: node scripts/validate-borg-animation-actions.mjs [--strict]

Scans apps/game/public/models/pl*/anim_index.json and writes:
  research/asset-inventory/borg-animation-action-gaps.md

Default exit code is 0. With --strict, exits 1 when fallbacks, misses, or
parse errors are present.`);
  process.exit(0);
}

for (const arg of args) {
  if (arg !== "--strict") {
    console.error(`unknown option: ${arg}`);
    process.exit(2);
  }
}

function rel(file) {
  return path.relative(repoRoot, file).replaceAll(path.sep, "/");
}

function md(value) {
  return String(value ?? "")
    .replaceAll("|", "\\|")
    .replaceAll("\n", " ");
}

function code(value) {
  return `\`${md(value)}\``;
}

function codeList(values) {
  return values.length > 0 ? values.map(code).join(", ") : "none";
}

function countBy(values, keyFn) {
  const counts = new Map();
  for (const value of values) {
    const key = keyFn(value);
    counts.set(key, (counts.get(key) ?? 0) + 1);
  }
  return counts;
}

function plural(count, singular, pluralValue = `${singular}s`) {
  return count === 1 ? singular : pluralValue;
}

function readJson(file) {
  return JSON.parse(fs.readFileSync(file, "utf8"));
}

function discoverAnimIndexes() {
  if (!fs.existsSync(modelsRoot)) return [];
  return fs
    .readdirSync(modelsRoot, { withFileTypes: true })
    .filter((entry) => entry.isDirectory() && /^pl/i.test(entry.name))
    .map((entry) => ({
      borg: entry.name.toLowerCase(),
      file: path.join(modelsRoot, entry.name, "anim_index.json"),
    }))
    .filter((entry) => fs.existsSync(entry.file))
    .sort((a, b) => a.borg.localeCompare(b.borg));
}

function sortedBanks(index) {
  return [...index.banks].sort((a, b) => a.group - b.group || a.slot - b.slot || a.frames - b.frames);
}

function pickAnimBankDirect(index, slot) {
  const patterns = SLOT_LABELS[slot];
  if (!patterns) return null;
  const banks = sortedBanks(index);
  for (const pattern of patterns) {
    const match = banks.find((bank) => typeof bank.label === "string" && pattern.test(bank.label));
    if (match) return match;
  }
  return null;
}

function pickAnimBank(index, slot) {
  const direct = pickAnimBankDirect(index, slot);
  if (direct) return { status: "direct", requestedSlot: slot, resolvedSlot: slot, bank: direct };
  for (const fallback of SLOT_FALLBACKS[slot] ?? []) {
    const bank = pickAnimBankDirect(index, fallback);
    if (bank) return { status: "fallback", requestedSlot: slot, resolvedSlot: fallback, bank };
  }
  return { status: "missing", requestedSlot: slot, resolvedSlot: null, bank: null };
}

function validateAnimIndex(entry) {
  try {
    const index = readJson(entry.file);
    if (!index || !Array.isArray(index.banks)) {
      throw new Error("anim_index.json does not contain a banks array");
    }
    const slotResults = CANONICAL_SLOTS.map((slot) => ({
      borg: entry.borg,
      file: entry.file,
      ...pickAnimBank(index, slot),
    }));
    return {
      ok: true,
      borg: entry.borg,
      file: entry.file,
      bankCount: index.banks.length,
      slotResults,
    };
  } catch (error) {
    return {
      ok: false,
      borg: entry.borg,
      file: entry.file,
      error: error instanceof Error ? error.message : String(error),
    };
  }
}

function groupFallbacks(results) {
  const groups = new Map();
  for (const result of results.filter((item) => item.status === "fallback")) {
    const key = `${result.requestedSlot}\0${result.resolvedSlot}\0${result.bank.label}`;
    const current = groups.get(key) ?? {
      requestedSlot: result.requestedSlot,
      resolvedSlot: result.resolvedSlot,
      label: result.bank.label,
      borgs: [],
    };
    current.borgs.push(result.borg);
    groups.set(key, current);
  }
  return [...groups.values()].sort(
    (a, b) =>
      CANONICAL_SLOTS.indexOf(a.requestedSlot) - CANONICAL_SLOTS.indexOf(b.requestedSlot) ||
      a.resolvedSlot.localeCompare(b.resolvedSlot) ||
      a.label.localeCompare(b.label),
  );
}

function groupMisses(results) {
  const groups = new Map();
  for (const result of results.filter((item) => item.status === "missing")) {
    const current = groups.get(result.requestedSlot) ?? { requestedSlot: result.requestedSlot, borgs: [] };
    current.borgs.push(result.borg);
    groups.set(result.requestedSlot, current);
  }
  return [...groups.values()].sort(
    (a, b) => CANONICAL_SLOTS.indexOf(a.requestedSlot) - CANONICAL_SLOTS.indexOf(b.requestedSlot),
  );
}

function compactFallbackNotes(slotResults) {
  const fallbackResults = slotResults.filter((result) => result.status === "fallback");
  const missingResults = slotResults.filter((result) => result.status === "missing");
  const notes = [];
  if (fallbackResults.length > 0) {
    const byPath = countBy(fallbackResults, (result) => `${result.resolvedSlot} -> ${result.bank.label}`);
    notes.push([...byPath].map(([pathLabel, count]) => `${pathLabel} x${count}`).join("; "));
  }
  if (missingResults.length > 0) notes.push(`missing x${missingResults.length}`);
  return notes.length > 0 ? notes.join("; ") : "none";
}

function explorerVisibleGroups(fallbackGroups, missGroups) {
  const visible = [];
  for (const miss of missGroups) {
    visible.push({
      gap: `${miss.requestedSlot} unresolved`,
      evidence: `${miss.borgs.length} ${plural(miss.borgs.length, "Borg")}: ${codeList(miss.borgs)}`,
    });
  }
  for (const group of fallbackGroups) {
    const slot = group.requestedSlot;
    const directDashGap = slot.startsWith("dash_") && group.resolvedSlot !== slot;
    const nonActionGap =
      ["shoot", "melee", "special", "hit", "death"].includes(slot) && group.resolvedSlot !== slot;
    if (!directDashGap && !nonActionGap) continue;
    visible.push({
      gap: `${slot} uses ${group.resolvedSlot} -> ${group.label}`,
      evidence: `${group.borgs.length} ${plural(group.borgs.length, "Borg")}: ${codeList(group.borgs)}`,
    });
  }
  return visible;
}

function renderReport(records, parseErrors) {
  const parsed = records.filter((record) => record.ok);
  const allResults = parsed.flatMap((record) => record.slotResults);
  const direct = allResults.filter((result) => result.status === "direct");
  const fallbacks = allResults.filter((result) => result.status === "fallback");
  const misses = allResults.filter((result) => result.status === "missing");
  const fallbackGroups = groupFallbacks(allResults);
  const missGroups = groupMisses(allResults);
  const gapBorgs = new Set([...fallbacks, ...misses].map((result) => result.borg));
  const missingBorgs = new Set(misses.map((result) => result.borg));
  const fallbackBorgs = new Set(fallbacks.map((result) => result.borg));
  const bankCount = parsed.reduce((sum, record) => sum + record.bankCount, 0);

  const lines = [];
  lines.push("# Borg Animation Action Gaps");
  lines.push("");
  lines.push(`Generated: ${new Date().toISOString()}`);
  lines.push("");
  lines.push(`Scope: ${code("apps/game/public/models/pl*/anim_index.json")}`);
  lines.push(`Canonical app slots: ${codeList(CANONICAL_SLOTS)}`);
  lines.push(
    "Runtime resolver: mirrors `SLOT_LABELS`, `SLOT_FALLBACKS`, `pickAnimBank`, and `pickAnimBankDirect` from `apps/game/src/main.ts` (runtime label tables and bank sort/pick order). `BattleScene` may still ask for `idle` after `loadClip` returns null, so `missing` below means the main runtime resolver found no canonical clip before that last idle request.",
  );
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push("| Metric | Count |");
  lines.push("|---|---:|");
  lines.push(`| Animation indexes found | ${records.length} |`);
  lines.push(`| Animation indexes parsed | ${parsed.length} |`);
  lines.push(`| Total exported banks in parsed indexes | ${bankCount} |`);
  lines.push(`| Canonical slot checks | ${allResults.length} |`);
  lines.push(`| Direct runtime matches | ${direct.length} |`);
  lines.push(`| Runtime fallbacks | ${fallbacks.length} |`);
  lines.push(`| Missing runtime matches | ${misses.length} |`);
  lines.push(`| Borgs with any fallback | ${fallbackBorgs.size} |`);
  lines.push(`| Borgs with any missing slot | ${missingBorgs.size} |`);
  lines.push(`| Borgs with any gap | ${gapBorgs.size} |`);
  lines.push(`| Parse errors | ${parseErrors.length} |`);
  lines.push("");
  lines.push("## Per-Slot Coverage");
  lines.push("");
  lines.push("| Slot | Direct | Fallback | Missing | Gap notes |");
  lines.push("|---|---:|---:|---:|---|");
  for (const slot of CANONICAL_SLOTS) {
    const slotResults = allResults.filter((result) => result.requestedSlot === slot);
    const slotDirect = slotResults.filter((result) => result.status === "direct").length;
    const slotFallbacks = slotResults.filter((result) => result.status === "fallback").length;
    const slotMisses = slotResults.filter((result) => result.status === "missing").length;
    lines.push(
      `| ${code(slot)} | ${slotDirect} | ${slotFallbacks} | ${slotMisses} | ${md(compactFallbackNotes(slotResults))} |`,
    );
  }
  lines.push("");
  lines.push("## Missing Runtime Matches");
  lines.push("");
  if (missGroups.length === 0) {
    lines.push("No canonical slots are fully missing from the main runtime resolver.");
  } else {
    lines.push("| Requested slot | Count | Borgs |");
    lines.push("|---|---:|---|");
    for (const miss of missGroups) {
      lines.push(`| ${code(miss.requestedSlot)} | ${miss.borgs.length} | ${codeList(miss.borgs)} |`);
    }
  }
  lines.push("");
  lines.push("## Runtime Fallbacks");
  lines.push("");
  if (fallbackGroups.length === 0) {
    lines.push("No canonical slots fall back through `SLOT_FALLBACKS`.");
  } else {
    lines.push("| Requested slot | Runtime fallback used | Count | Borgs |");
    lines.push("|---|---|---:|---|");
    for (const group of fallbackGroups) {
      lines.push(
        `| ${code(group.requestedSlot)} | ${code(`${group.resolvedSlot} -> ${group.label}`)} | ${group.borgs.length} | ${codeList(group.borgs)} |`,
      );
    }
  }
  lines.push("");
  lines.push("## Explorer-Known Gaps Still Present");
  lines.push("");
  const visible = explorerVisibleGroups(fallbackGroups, missGroups);
  if (visible.length === 0) {
    lines.push("No explorer-visible canonical action gaps are still present.");
  } else {
    lines.push("The rows below are generated from the same runtime resolver pass and keep the explorer-visible direct-label gaps in one place.");
    lines.push("");
    lines.push("| Gap | Current evidence |");
    lines.push("|---|---|");
    for (const row of visible) {
      lines.push(`| ${code(row.gap)} | ${md(row.evidence)} |`);
    }
  }
  lines.push("");
  lines.push("## Parse Errors");
  lines.push("");
  if (parseErrors.length === 0) {
    lines.push("None.");
  } else {
    lines.push("| Borg | File | Error |");
    lines.push("|---|---|---|");
    for (const error of parseErrors) {
      lines.push(`| ${code(error.borg)} | ${code(rel(error.file))} | ${md(error.error)} |`);
    }
  }
  lines.push("");
  lines.push("## Reproduce");
  lines.push("");
  lines.push("```bash");
  lines.push("rtk node scripts/validate-borg-animation-actions.mjs");
  lines.push("rtk node scripts/validate-borg-animation-actions.mjs --strict");
  lines.push("```");
  lines.push("");

  return {
    markdown: lines.join("\n"),
    summary: {
      indexes: records.length,
      parsed: parsed.length,
      slotChecks: allResults.length,
      direct: direct.length,
      fallbacks: fallbacks.length,
      missing: misses.length,
      parseErrors: parseErrors.length,
      gapBorgs: gapBorgs.size,
    },
  };
}

const discovered = discoverAnimIndexes();
if (discovered.length === 0) {
  console.error(`no animation indexes found under ${rel(modelsRoot)}`);
  process.exit(1);
}

const records = discovered.map(validateAnimIndex);
const parseErrors = records.filter((record) => !record.ok);
const { markdown, summary } = renderReport(records, parseErrors);

fs.mkdirSync(path.dirname(reportPath), { recursive: true });
fs.writeFileSync(reportPath, markdown);

const gapCount = summary.fallbacks + summary.missing + summary.parseErrors;
console.log(
  [
    `wrote ${rel(reportPath)}`,
    `indexes ${summary.indexes}`,
    `parsed ${summary.parsed}`,
    `slot checks ${summary.slotChecks}`,
    `direct ${summary.direct}`,
    `fallback ${summary.fallbacks}`,
    `missing ${summary.missing}`,
    `parse errors ${summary.parseErrors}`,
    `gap borgs ${summary.gapBorgs}`,
  ].join("; "),
);

if (strict && gapCount > 0) {
  process.exitCode = 1;
}
