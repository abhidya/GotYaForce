#!/usr/bin/env node
// Read-only audit that joins roster, wiki move, source-stat, action-profile,
// and public animation data to surface per-borg move wiring gaps.

import fs from "node:fs";
import path from "node:path";
import process from "node:process";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

const DATA_PATHS = {
  borgs: "packages/assets/data/borgs.json",
  moveProperties: "packages/combat/src/data/borgMoveProperties.json",
  sourceStats: "packages/combat/src/data/borgSourceStats.json",
  actionProfiles: "packages/combat/src/data/actionProfiles.json",
  commandMoveTables: "packages/combat/src/data/commandMoveTables.json",
  modelManifest: "apps/game/public/models/library/manifest.json",
  runtimeAnimationResolver: "apps/game/src/sim/borgPresentationAssets.ts",
  runtimeCombat: "packages/combat/src/combat.ts",
  runtimeMove: "packages/combat/src/moveRuntime.ts",
};

const BUTTON_ORDER = ["B Shot", "B Attack", "B Charge", "X", "X Charge"];

const BUTTON_WIRING = {
  "B Shot": { action: "shot", weaponSlot: 0, animSlot: "shoot", runtime: "b" },
  "B Attack": { action: "melee", weaponSlot: null, animSlot: "melee", runtime: "b" },
  "B Charge": { action: "shot", weaponSlot: 0, animSlot: "shoot", runtime: "b-charge" },
  X: { action: "special", weaponSlot: 1, animSlot: "special", runtime: "x" },
  "X Charge": { action: "special", weaponSlot: 1, animSlot: "special", runtime: "x-charge" },
};

const BUTTON_COMMAND_TYPES = {
  "B Shot": { type: 0, context: "B far/default" },
  "B Attack": { type: 1, context: "B close/proximity" },
  X: { type: 2, context: "secondary/X" },
  "B Charge": { type: 3, context: "charged" },
  "X Charge": { type: 5, context: "ranged/target-forced" },
};

const SLOT_LABELS = {
  idle: [/^idle$/],
  move: [/^move$/, /^move_s\d+$/],
  attack: [/^attack_s\d+$/, /^attack_lunge_s\d+$/],
  melee: [/^attack_lunge_s\d+$/, /^attack_s\d+$/],
  shoot: [/^attack_s\d+$/, /^special_s\d+$/],
  special: [/^special_s\d+$/],
};

const SLOT_FALLBACKS = {
  shoot: ["attack", "special", "move", "idle"],
  melee: ["attack", "idle"],
  special: ["attack", "idle"],
};

const MIN_ACTION_FRAMES = 5;

function usage() {
  return `usage: node scripts/audit-move-wiring.mjs [--borg pl0615] [--top 15]

Prints a read-only move wiring audit. With --borg, prints per-move detail for
one borg. Without --borg, prints an all-roster summary.`;
}

function parseArgs(argv) {
  const opts = { borg: null, top: 15 };
  for (let i = 0; i < argv.length; i += 1) {
    const arg = argv[i];
    if (arg === "--") continue;
    if (arg === "--help" || arg === "-h") {
      console.log(usage());
      process.exit(0);
    }
    if (arg === "--borg") {
      const value = argv[i + 1];
      if (!value || value.startsWith("--")) fail("--borg requires an id, e.g. --borg pl0615", 2);
      opts.borg = value.toLowerCase();
      i += 1;
      continue;
    }
    if (arg === "--top") {
      const value = Number.parseInt(argv[i + 1] ?? "", 10);
      if (!Number.isFinite(value) || value < 0) fail("--top requires a non-negative integer", 2);
      opts.top = value;
      i += 1;
      continue;
    }
    fail(`unknown option: ${arg}\n\n${usage()}`, 2);
  }
  return opts;
}

function fail(message, code = 1) {
  console.error(`audit-move-wiring: ${message}`);
  process.exit(code);
}

function abs(relPath) {
  return path.join(repoRoot, relPath);
}

function rel(filePath) {
  return path.relative(repoRoot, filePath).replaceAll(path.sep, "/");
}

function readJson(relPath, required = true) {
  const filePath = abs(relPath);
  if (!fs.existsSync(filePath)) {
    if (required) fail(`missing ${relPath}`);
    return null;
  }
  try {
    return JSON.parse(fs.readFileSync(filePath, "utf8"));
  } catch (error) {
    fail(`could not parse ${relPath}: ${error instanceof Error ? error.message : String(error)}`);
  }
}

function yesNo(value) {
  return value ? "yes" : "no";
}

function compact(value) {
  return String(value ?? "").replace(/\s+/g, " ").trim();
}

function stripJsComments(source) {
  return source.replace(/\/\*[\s\S]*?\*\//g, "").replace(/\/\/.*$/gm, "");
}

function readPreferredLabels() {
  const filePath = abs(DATA_PATHS.runtimeAnimationResolver);
  if (!fs.existsSync(filePath)) return { labels: {}, parsed: false };

  const source = fs.readFileSync(filePath, "utf8");
  const start = source.indexOf("const PREFERRED_LABELS");
  if (start < 0) return { labels: {}, parsed: false };

  const open = source.indexOf("{", start);
  if (open < 0) return { labels: {}, parsed: false };

  let depth = 0;
  let close = -1;
  for (let i = open; i < source.length; i += 1) {
    const ch = source[i];
    if (ch === "{") depth += 1;
    if (ch === "}") {
      depth -= 1;
      if (depth === 0) {
        close = i;
        break;
      }
    }
  }
  if (close < 0) return { labels: {}, parsed: false };

  const body = stripJsComments(source.slice(open + 1, close));
  const labels = {};
  const entryRe = /\b(pl[0-9a-f]{4})\s*:\s*\{([\s\S]*?)\}\s*,?/gi;
  for (const entry of body.matchAll(entryRe)) {
    const id = entry[1].toLowerCase();
    const objectBody = entry[2];
    const slots = {};
    const slotRe = /\b([a-z_]+)\s*:\s*\[([^\]]*)\]/g;
    for (const slotEntry of objectBody.matchAll(slotRe)) {
      const slot = slotEntry[1];
      const values = [...slotEntry[2].matchAll(/"([^"]+)"/g)].map((match) => match[1]);
      if (values.length > 0) slots[slot] = values;
    }
    labels[id] = slots;
  }

  return { labels, parsed: true };
}

function readRuntimeCombatFlags() {
  const combatPath = abs(DATA_PATHS.runtimeCombat);
  const movePath = abs(DATA_PATHS.runtimeMove);
  const source = [
    fs.existsSync(combatPath) ? fs.readFileSync(combatPath, "utf8") : "",
    fs.existsSync(movePath) ? fs.readFileSync(movePath, "utf8") : "",
  ].join("\n");
  return {
    contextualBResolver:
      source.includes("usesContextualBResolver") && source.includes("resolveBActionOrder"),
    runtimeMoveOverlay:
      source.includes("runtimeMoveBindingsForProfile") && source.includes("runtimeShotPenetrationForBorgId"),
  };
}

function readModelManifest() {
  const data = readJson(DATA_PATHS.modelManifest, false);
  if (!Array.isArray(data)) return new Map();
  return new Map(data.filter((record) => record?.id).map((record) => [record.id.toLowerCase(), record]));
}

function readAnimIndex(id) {
  const filePath = abs(path.join("apps/game/public/models", id, "anim_index.json"));
  if (!fs.existsSync(filePath)) return { ok: false, filePath, index: null, error: "missing" };
  try {
    const index = JSON.parse(fs.readFileSync(filePath, "utf8"));
    if (!Array.isArray(index.banks)) return { ok: false, filePath, index: null, error: "no banks array" };
    return { ok: true, filePath, index, error: null };
  } catch (error) {
    return {
      ok: false,
      filePath,
      index: null,
      error: error instanceof Error ? error.message : String(error),
    };
  }
}

function sortedBanks(index) {
  return [...index.banks].sort((a, b) => a.group - b.group || a.slot - b.slot || a.frames - b.frames);
}

function usableBank(bank) {
  return (bank.frames ?? 0) >= MIN_ACTION_FRAMES;
}

function findLabel(index, label) {
  return sortedBanks(index).find((bank) => bank.label === label) ?? null;
}

function findPattern(index, slot) {
  const patterns = SLOT_LABELS[slot] ?? [];
  const matches = sortedBanks(index).filter((bank) => patterns.some((pattern) => pattern.test(bank.label ?? "")));
  const usable = matches.filter(usableBank);
  return usable[0] ?? matches[0] ?? null;
}

function findRuntimeBank(index, slot) {
  const direct = findPattern(index, slot);
  if (direct) return { status: "generic", slot, bank: direct };
  for (const fallback of SLOT_FALLBACKS[slot] ?? []) {
    const bank = findPattern(index, fallback);
    if (bank) return { status: "fallback", slot: fallback, bank };
  }
  return { status: "missing", slot: null, bank: null };
}

function animCoverage(id, slot, animIndexState, preferredLabels) {
  if (!slot) return { text: "n/a", exact: false, hasIndex: animIndexState.ok, gaps: [] };
  if (!animIndexState.ok) {
    return {
      text: animIndexState.error === "missing" ? "no anim_index" : `bad anim_index: ${animIndexState.error}`,
      exact: false,
      hasIndex: false,
      gaps: ["missing anim_index"],
    };
  }

  const index = animIndexState.index;
  const preferred = preferredLabels[id]?.[slot] ?? [];
  if (preferred.length > 0) {
    for (const label of preferred) {
      const bank = findLabel(index, label);
      if (bank) return { text: `exact ${slot}->${label}`, exact: true, hasIndex: true, gaps: [] };
    }
    const runtime = findRuntimeBank(index, slot);
    return {
      text:
        runtime.bank === null
          ? `exact missing (${preferred.join(",")})`
          : `exact missing; ${runtime.status} ${runtime.slot}->${runtime.bank.label}`,
      exact: false,
      hasIndex: true,
      gaps: [`exact anim label missing (${slot}: ${preferred.join(",")})`],
    };
  }

  const runtime = findRuntimeBank(index, slot);
  if (runtime.bank === null) {
    return {
      text: "missing",
      exact: false,
      hasIndex: true,
      gaps: [`missing ${slot} anim map`],
    };
  }
  return {
    text: `${runtime.status} ${runtime.slot}->${runtime.bank.label}`,
    exact: false,
    hasIndex: true,
    gaps: [`missing exact anim map (${slot})`],
  };
}

function weaponSlot(sourceProfile, slot, rowIndex = null) {
  if (!sourceProfile) return null;
  if (rowIndex !== null) return sourceProfile.rows?.[rowIndex]?.weaponSlots?.[slot] ?? null;
  return sourceProfile.weaponSlots?.[slot] ?? null;
}

function sourceAmmoCoverage(sourceProfile, button) {
  const wiring = BUTTON_WIRING[button];
  if (!sourceProfile) return { text: "missing", hasRows: false, hasSlot: false, values: null, gaps: ["source stats missing"] };
  const rows = Array.isArray(sourceProfile.rows) ? sourceProfile.rows : [];
  if (wiring.weaponSlot === null) {
    return { text: rows.length > 0 ? "rows yes; n/a" : "no rows; n/a", hasRows: rows.length > 0, hasSlot: true, values: null, gaps: [] };
  }

  const slot = wiring.weaponSlot;
  const lv1 = weaponSlot(sourceProfile, slot, 2) ?? weaponSlot(sourceProfile, slot);
  const lv10 = weaponSlot(sourceProfile, slot, 11) ?? rows.at(-1)?.weaponSlots?.[slot] ?? lv1;
  if (!lv1 && !lv10) {
    return {
      text: rows.length > 0 ? `rows yes; w${slot} missing` : `no rows; w${slot} missing`,
      hasRows: rows.length > 0,
      hasSlot: false,
      values: null,
      gaps: [`weapon ${slot} ammo slot missing`],
    };
  }

  const values = {
    lv1: lv1?.ammoCount ?? null,
    lv10: lv10?.ammoCount ?? null,
    refillType: lv1?.chargeType ?? null,
    refillParam: lv1?.chargeCount ?? null,
  };
  return {
    text: `${rows.length > 0 ? "rows yes" : "no rows"}; w${slot} ${values.lv1 ?? "?"}/${values.lv10 ?? "?"}`,
    hasRows: rows.length > 0,
    hasSlot: true,
    values,
    gaps: rows.length > 0 ? [] : ["source level rows missing"],
  };
}

function wikiAmmoText(move) {
  if (!move?.ammo) return null;
  const lv1 = move.ammo.lv1 ?? "?";
  const lv10 = move.ammo.lv10 ?? "?";
  return `${lv1}/${lv10}`;
}

function ammoMismatch(move, ammo) {
  if (!move?.ammo || !ammo.values) return null;
  const wikiLv1 = move.ammo.lv1;
  const wikiLv10 = move.ammo.lv10;
  if (wikiLv1 == null && wikiLv10 == null) return null;
  const lv1Matches = wikiLv1 == null || wikiLv1 === ammo.values.lv1;
  const lv10Matches = wikiLv10 == null || wikiLv10 === ammo.values.lv10;
  if (lv1Matches && lv10Matches) return null;
  return `wiki ammo ${wikiAmmoText(move)} vs source ${ammo.values.lv1 ?? "?"}/${ammo.values.lv10 ?? "?"}`;
}

function actionCoverage(actionProfile, button) {
  if (!actionProfile) return { text: "missing", ok: false, gaps: ["action profile missing"] };
  const action = BUTTON_WIRING[button].action;
  const value = actionProfile[action];
  if (!value) return { text: `${action} missing`, ok: false, gaps: [`${action} action missing`] };
  if (button === "B Charge" && actionProfile.shot?.chargeable !== true) {
    return { text: "shot no-charge", ok: true, gaps: ["B Charge wiki move but shot profile is not chargeable"] };
  }
  return { text: action, ok: true, gaps: [] };
}

function commandCoverage(commandMoveTables, id, button) {
  const spec = BUTTON_COMMAND_TYPES[button];
  if (!spec) return { text: "n/a", exact: false, gaps: [] };

  const assignment = commandMoveTables?.borgs?.[id] ?? null;
  if (!assignment) {
    return { text: "no constructor map", exact: false, assigned: false, gaps: ["exact ROM command table missing"] };
  }
  if (!assignment.tableId) {
    return {
      text: `ctor ${assignment.constructorAddress}; no +0x4ec table`,
      exact: false,
      assigned: false,
      gaps: ["exact ROM command table missing"],
    };
  }

  const tableEntry = commandMoveTables?.tables?.[assignment.tableId] ?? null;
  const typeEntry = tableEntry?.types?.find((entry) => entry.type === spec.type) ?? null;
  if (!tableEntry || !typeEntry) {
    return { text: `t${spec.type} missing`, exact: false, assigned: true, gaps: ["exact ROM command type missing"] };
  }
  const records = (typeEntry.records ?? []).filter((record) => !record.disabled);
  if (records.length === 0) {
    return {
      text: `t${spec.type} ${typeEntry.modeName}; no active records`,
      exact: false,
      assigned: true,
      gaps: [
        typeEntry.modeName === "disabled"
          ? "exact ROM command type disabled"
          : "exact ROM command records inactive",
      ],
    };
  }

  const actionIndexes = [...new Set(records.map((record) => record.actionIndex))].join(",");
  const variants = [...new Set(records.map((record) => record.variantIndex))].join(",");
  return {
    text: `${spec.context}; t${spec.type} ${typeEntry.modeName} ${records.length} recs a[${actionIndexes}] v[${variants}]`,
    exact: true,
    assigned: true,
    gaps: [],
    tableId: assignment.tableId,
    records,
  };
}

function normalizeButton(button) {
  if (!button) return null;
  const exact = BUTTON_ORDER.find((candidate) => candidate.toLowerCase() === button.toLowerCase());
  return exact ?? button;
}

function moveSort(a, b) {
  const ai = BUTTON_ORDER.indexOf(a.button);
  const bi = BUTTON_ORDER.indexOf(b.button);
  return (ai < 0 ? 999 : ai) - (bi < 0 ? 999 : bi) || a.button.localeCompare(b.button);
}

function runtimeExpectedButtons(borg, sourceProfile, actionProfile, wikiButtons) {
  const buttons = new Set(wikiButtons);
  const w0 = weaponSlot(sourceProfile, 0);
  const w1 = weaponSlot(sourceProfile, 1);
  if (actionProfile?.shot || (w0?.ammoCount ?? 0) > 0 || (borg.shot ?? 0) > 0) buttons.add("B Shot");
  if (actionProfile?.melee || (borg.attack ?? 0) > 0) buttons.add("B Attack");
  if (actionProfile?.shot?.chargeable === true) buttons.add("B Charge");
  if ((w1?.ammoCount ?? 0) > 0) buttons.add("X");
  return buttons;
}

function auditBorg(borg, data) {
  const id = borg.id.toLowerCase();
  const moveProfile = data.moveProperties.borgs[id] ?? null;
  const sourceProfile = data.sourceStats.profiles[id] ?? null;
  const actionProfile = data.actionProfiles.profiles[id] ?? null;
  const animIndex = readAnimIndex(id);
  const modelManifest = data.modelManifest.get(id) ?? null;
  const wikiMoves = moveProfile?.moves ?? [];
  const wikiByButton = new Map();
  for (const move of wikiMoves) {
    const button = normalizeButton(move.button);
    if (button && !wikiByButton.has(button)) wikiByButton.set(button, move);
  }

  const buttons = runtimeExpectedButtons(borg, sourceProfile, actionProfile, wikiByButton.keys());
  const hasBShot = buttons.has("B Shot");
  const hasBAttack = buttons.has("B Attack");
  const rows = [...buttons]
    .filter((button) => BUTTON_WIRING[button])
    .map((button) => {
      const move = wikiByButton.get(button) ?? null;
      const ammo = sourceAmmoCoverage(sourceProfile, button);
      const action = actionCoverage(actionProfile, button);
      const command = commandCoverage(data.commandMoveTables, id, button);
      const anim = animCoverage(id, BUTTON_WIRING[button].animSlot, animIndex, data.preferredLabels);
      const gaps = [];

      if (!move) gaps.push("wiki move missing");
      gaps.push(...ammo.gaps);
      const mismatch = ammoMismatch(move, ammo);
      if (mismatch) gaps.push(mismatch);
      gaps.push(...action.gaps);
      gaps.push(...command.gaps);
      if (!move || move.penetration == null) gaps.push("penetration missing");
      gaps.push(...anim.gaps);

      if ((button === "B Shot" || button === "B Attack") && hasBShot && hasBAttack && !command.exact) {
        gaps.push(
          data.runtimeFlags.contextualBResolver
            ? command.assigned
              ? "B Shot/B Attack context resolver exists, but this command type has no active ROM records"
              : "B Shot/B Attack context resolver exists, but exact ROM command table is not assigned"
            : `B Shot/B Attack resolver is primary-order only (${actionProfile?.primary ?? "fallback"})`,
        );
      }
      if (button === "B Charge" && !command.exact) {
        gaps.push("B Charge uses shot charge bridge, not an exact move record");
      }
      if (button === "X") {
        gaps.push("X hitbox is generic radius, exact per-move hitbox unmapped");
      }
      if (button === "X Charge") {
        gaps.push("X Charge resolver is not split from X press");
        gaps.push("X hitbox is generic radius, exact per-move hitbox unmapped");
      }

      return {
        id,
        button,
        moveName: move?.name ?? "(runtime slot)",
        wikiMove: !!move,
        sourceAmmo: ammo,
        action,
        command,
        penetration: move?.penetration ?? null,
        anim,
        gaps: [...new Set(gaps)],
      };
    })
    .sort(moveSort);

  const gapCounts = countGapCategories(rows);
  return {
    id,
    name: borg.name,
    borg,
    moveProfile,
    sourceProfile,
    actionProfile,
    animIndex,
    modelManifest,
    rows,
    gapCounts,
    gapTotal: rows.reduce((sum, row) => sum + row.gaps.length, 0),
  };
}

function countGapCategories(rows) {
  const counts = {
    missingWiki: 0,
    missingSource: 0,
    missingAction: 0,
    missingExactCommand: 0,
    missingPenetration: 0,
    missingExactAnimMap: 0,
    missingXHitbox: 0,
    missingXChargeResolver: 0,
    ammoMismatch: 0,
  };
  for (const row of rows) {
    if (!row.wikiMove) counts.missingWiki += 1;
    if (row.gaps.some((gap) => gap.includes("source") || gap.includes("weapon"))) counts.missingSource += 1;
    if (row.gaps.some((gap) => gap.includes("action"))) counts.missingAction += 1;
    if (row.gaps.some((gap) => gap.includes("exact ROM command"))) counts.missingExactCommand += 1;
    if (row.gaps.includes("penetration missing")) counts.missingPenetration += 1;
    if (row.gaps.some((gap) => gap.includes("anim"))) counts.missingExactAnimMap += 1;
    if (row.gaps.some((gap) => gap.includes("X hitbox"))) counts.missingXHitbox += 1;
    if (row.gaps.some((gap) => gap.includes("X Charge resolver"))) counts.missingXChargeResolver += 1;
    if (row.gaps.some((gap) => gap.includes("wiki ammo"))) counts.ammoMismatch += 1;
  }
  return counts;
}

function table(rows, columns) {
  const widths = columns.map((column) =>
    Math.max(
      column.header.length,
      ...rows.map((row) => compact(column.value(row)).length),
    ),
  );
  const line = (cells) => cells.map((cell, index) => compact(cell).padEnd(widths[index])).join(" | ");
  return [line(columns.map((column) => column.header)), line(widths.map((width) => "-".repeat(width))), ...rows.map((row) => line(columns.map((column) => column.value(row))))].join("\n");
}

function renderBorgReport(audit, data) {
  const preferred = data.preferredLabels[audit.id] ?? {};
  const actionBits = [
    audit.actionProfile?.shot ? "shot" : null,
    audit.actionProfile?.melee ? "melee" : null,
    audit.actionProfile?.special ? "special" : null,
  ].filter(Boolean);

  console.log(`Move wiring audit: ${audit.id} ${audit.name}`);
  console.log(`Sources: ${Object.values(DATA_PATHS).join(", ")}`);
  console.log(`Runtime contextual B resolver: ${yesNo(data.runtimeFlags.contextualBResolver)}`);
  console.log(`Runtime move overlay: ${yesNo(data.runtimeFlags.runtimeMoveOverlay)}`);
  console.log(
    `Coverage: wiki=${yesNo(audit.moveProfile)} source=${yesNo(audit.sourceProfile)} action=${actionBits.join("/") || "missing"} modelManifest=${yesNo(audit.modelManifest)} animIndex=${audit.animIndex.ok ? `yes (${audit.animIndex.index.banks.length} banks)` : `no (${audit.animIndex.error})`} preferredSlots=${Object.keys(preferred).join(",") || "none"}`,
  );
  console.log("");

  if (audit.rows.length === 0) {
    console.log("No move rows were inferred for this borg.");
    return;
  }

  console.log(
    table(audit.rows, [
      { header: "button", value: (row) => row.button },
      { header: "move", value: (row) => row.moveName },
      { header: "wiki", value: (row) => yesNo(row.wikiMove) },
      { header: "source ammo", value: (row) => row.sourceAmmo.text },
      { header: "action", value: (row) => row.action.text },
      { header: "cmd", value: (row) => row.command.text },
      { header: "pen", value: (row) => row.penetration ?? "missing" },
      { header: "anim", value: (row) => row.anim.text },
      { header: "gaps", value: (row) => row.gaps.join("; ") || "none" },
    ]),
  );
  console.log("");
  console.log(`Gap rows: ${audit.rows.filter((row) => row.gaps.length > 0).length}/${audit.rows.length}; gap notes: ${audit.gapTotal}`);
}

function sum(audits, selector) {
  return audits.reduce((total, audit) => total + selector(audit), 0);
}

function renderSummary(audits, data, top) {
  const rows = audits.flatMap((audit) => audit.rows);
  const wikiBorgs = audits.filter((audit) => audit.moveProfile).length;
  const sourceBorgs = audits.filter((audit) => audit.sourceProfile).length;
  const actionBorgs = audits.filter((audit) => audit.actionProfile).length;
  const modelBorgs = audits.filter((audit) => audit.modelManifest).length;
  const animBorgs = audits.filter((audit) => audit.animIndex.ok).length;
  const withAnyGap = audits.filter((audit) => audit.gapTotal > 0);

  console.log("Move wiring audit: roster summary");
  console.log(`Sources: ${Object.values(DATA_PATHS).join(", ")}`);
  console.log(`Preferred animation map parsed: ${yesNo(data.preferredLabelsParsed)} (${Object.keys(data.preferredLabels).length} borg entries)`);
  console.log(`Runtime contextual B resolver: ${yesNo(data.runtimeFlags.contextualBResolver)}`);
  console.log(`Runtime move overlay: ${yesNo(data.runtimeFlags.runtimeMoveOverlay)}`);
  if (data.commandMoveTables?._meta?.coverage) {
    const coverage = data.commandMoveTables._meta.coverage;
    console.log(
      `Exact command tables: ${coverage.exactCommandTableBorgs}/${coverage.rosterBorgs} borgs; decoded tables=${coverage.decodedTables}`,
    );
  }
  console.log("");
  console.log(
    table(
      [
        { metric: "borgs", count: audits.length },
        { metric: "move rows audited", count: rows.length },
        { metric: "borgs with wiki moves", count: wikiBorgs },
        { metric: "borgs with source stats", count: sourceBorgs },
        { metric: "borgs with action profile", count: actionBorgs },
        { metric: "borgs with model manifest", count: modelBorgs },
        { metric: "borgs with anim_index", count: animBorgs },
        { metric: "borgs with any gap note", count: withAnyGap.length },
      ],
      [
        { header: "metric", value: (row) => row.metric },
        { header: "count", value: (row) => row.count },
      ],
    ),
  );
  console.log("");

  const categoryRows = [
    { category: "wiki move missing", count: sum(audits, (audit) => audit.gapCounts.missingWiki) },
    { category: "source ammo/stat gap", count: sum(audits, (audit) => audit.gapCounts.missingSource) },
    { category: "action profile gap", count: sum(audits, (audit) => audit.gapCounts.missingAction) },
    { category: "exact command record/type gap", count: sum(audits, (audit) => audit.gapCounts.missingExactCommand) },
    { category: "penetration missing", count: sum(audits, (audit) => audit.gapCounts.missingPenetration) },
    { category: "missing exact anim map", count: sum(audits, (audit) => audit.gapCounts.missingExactAnimMap) },
    { category: "missing X hitbox", count: sum(audits, (audit) => audit.gapCounts.missingXHitbox) },
    { category: "missing X Charge resolver", count: sum(audits, (audit) => audit.gapCounts.missingXChargeResolver) },
    { category: "wiki/source ammo mismatch", count: sum(audits, (audit) => audit.gapCounts.ammoMismatch) },
  ];
  console.log(
    table(categoryRows, [
      { header: "gap category", value: (row) => row.category },
      { header: "move rows", value: (row) => row.count },
    ]),
  );

  const topAudits = [...withAnyGap]
    .sort((a, b) => b.gapTotal - a.gapTotal || a.id.localeCompare(b.id))
    .slice(0, top);
  if (topAudits.length > 0) {
    console.log("");
    console.log(
      table(topAudits, [
        { header: "borg", value: (audit) => audit.id },
        { header: "name", value: (audit) => audit.name },
        { header: "rows", value: (audit) => audit.rows.length },
        { header: "gap notes", value: (audit) => audit.gapTotal },
        {
          header: "top categories",
          value: (audit) =>
            Object.entries(audit.gapCounts)
              .filter(([, count]) => count > 0)
              .sort((a, b) => b[1] - a[1])
              .slice(0, 3)
              .map(([key, count]) => `${topCategoryLabel(key)}:${count}`)
              .join(", "),
        },
      ]),
    );
  }
  console.log("");
  console.log("Use --borg <id> for per-move details, for example: rtk node scripts/audit-move-wiring.mjs --borg pl0615");
}

function topCategoryLabel(key) {
  if (key === "missingExactCommand") return "commandRows";
  if (key === "missingXHitbox") return "xHitbox";
  if (key === "missingExactAnimMap") return "exactAnim";
  if (key === "missingPenetration") return "penetration";
  return key;
}

const opts = parseArgs(process.argv.slice(2));
const borgsData = readJson(DATA_PATHS.borgs);
const moveProperties = readJson(DATA_PATHS.moveProperties);
const sourceStats = readJson(DATA_PATHS.sourceStats);
const actionProfiles = readJson(DATA_PATHS.actionProfiles);
const commandMoveTables = readJson(DATA_PATHS.commandMoveTables);
const modelManifest = readModelManifest();
const preferred = readPreferredLabels();
const runtimeFlags = readRuntimeCombatFlags();

if (!Array.isArray(borgsData.borgs)) fail(`${DATA_PATHS.borgs} does not contain a borgs array`);
if (!moveProperties?.borgs) fail(`${DATA_PATHS.moveProperties} does not contain borgs`);
if (!sourceStats?.profiles) fail(`${DATA_PATHS.sourceStats} does not contain profiles`);
if (!actionProfiles?.profiles) fail(`${DATA_PATHS.actionProfiles} does not contain profiles`);

const data = {
  moveProperties,
  sourceStats,
  actionProfiles,
  commandMoveTables,
  modelManifest,
  preferredLabels: preferred.labels,
  preferredLabelsParsed: preferred.parsed,
  runtimeFlags,
};

const audits = borgsData.borgs.map((borg) => auditBorg(borg, data));

if (opts.borg) {
  const audit = audits.find((item) => item.id === opts.borg);
  if (!audit) fail(`unknown borg id: ${opts.borg}`, 2);
  renderBorgReport(audit, data);
} else {
  renderSummary(audits, data, opts.top);
}
