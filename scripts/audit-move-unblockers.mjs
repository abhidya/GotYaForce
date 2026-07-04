#!/usr/bin/env node
// Read-only audit for the data that unblocks exact move wiring: command context,
// state animation dispatch, per-borg HIT remap slots, and HIT spawner call sites.

import fs from "node:fs";
import path from "node:path";
import process from "node:process";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");

const PATHS = {
  borgs: "packages/assets/data/borgs.json",
  hitInventory: "research/asset-inventory/hit-bin-inventory.json",
  commandMap: "research/decomp/data/command-button-map.json",
  commandMoveTables: "packages/combat/src/data/commandMoveTables.json",
  stateAnimDispatch: "research/decomp/data/state-anim-dispatch-802d3570.json",
  decompDir: "research/decomp/ghidra-export",
};

const ATTACK_REMAP_OFFSET = 0xa20;
const ATTACK_RECORD_OFFSET = 0xaa0;
const ATTACK_REMAP_SLOTS = 32;
const ATTACK_REMAP_STRIDE = 4;
const ATTACK_RECORD_COUNT = 64;
const ATTACK_RECORD_SIZE = 0x50;

const BUTTON_COMMAND_TYPES = {
  "B Shot": { type: 0, context: "B far/default" },
  "B Attack": { type: 1, context: "B close/proximity" },
  X: { type: 2, context: "secondary/X" },
  "B Charge": { type: 3, context: "charged" },
  "X Charge": { type: 5, context: "ranged/target-forced" },
};

function usage() {
  return `usage: node scripts/audit-move-unblockers.mjs [--borg pl0615] [--top 12] [--records 16]

Shows the extracted evidence that unlocks exact move wiring:
- command type/subtype context from the decomp notes
- attack state animation slots from the state dispatch table
- pl####hit.bin attack remap slots and decoded 0x50 hitbox records
- zz_008ac80_(actor, kind) call-site categories that select HIT remap slots`;
}

function parseArgs(argv) {
  const opts = { borg: null, top: 12, records: 16 };
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
      opts.top = parsePositiveInt(argv[i + 1], "--top");
      i += 1;
      continue;
    }
    if (arg === "--records") {
      opts.records = parsePositiveInt(argv[i + 1], "--records");
      i += 1;
      continue;
    }
    fail(`unknown option: ${arg}\n\n${usage()}`, 2);
  }
  return opts;
}

function parsePositiveInt(value, label) {
  const parsed = Number.parseInt(value ?? "", 10);
  if (!Number.isFinite(parsed) || parsed < 0) fail(`${label} requires a non-negative integer`, 2);
  return parsed;
}

function fail(message, code = 1) {
  console.error(`audit-move-unblockers: ${message}`);
  process.exit(code);
}

function abs(relPath) {
  return path.join(repoRoot, relPath);
}

function readJson(relPath) {
  try {
    return JSON.parse(fs.readFileSync(abs(relPath), "utf8"));
  } catch (error) {
    fail(`could not read ${relPath}: ${error instanceof Error ? error.message : String(error)}`);
  }
}

function compact(value) {
  return String(value ?? "").replace(/\s+/g, " ").trim();
}

function bool(value) {
  return value ? "yes" : "no";
}

function short(value, max = 92) {
  const text = compact(value);
  return text.length <= max ? text : `${text.slice(0, max - 3)}...`;
}

function hex(value) {
  return `0x${value.toString(16)}`;
}

function table(rows, columns) {
  if (rows.length === 0) return "(none)";
  const widths = columns.map((column) =>
    Math.max(column.header.length, ...rows.map((row) => compact(column.value(row)).length)),
  );
  const line = (cells) => cells.map((cell, index) => compact(cell).padEnd(widths[index])).join(" | ");
  return [
    line(columns.map((column) => column.header)),
    line(widths.map((width) => "-".repeat(width))),
    ...rows.map((row) => line(columns.map((column) => column.value(row)))),
  ].join("\n");
}

function playerHitInventory(hitInventory) {
  const players = hitInventory?.files?.player;
  if (!Array.isArray(players)) fail(`${PATHS.hitInventory} does not contain files.player`);
  return players;
}

function findBorg(borgsData, id) {
  const borgs = borgsData?.borgs;
  if (!Array.isArray(borgs)) fail(`${PATHS.borgs} does not contain a borgs array`);
  return borgs.find((borg) => borg.id?.toLowerCase() === id || borg.name?.toLowerCase() === id) ?? null;
}

function hitInventoryForBorg(hitInventory, id) {
  return playerHitInventory(hitInventory).find((entry) => entry.linkedBorgId?.toLowerCase() === id) ?? null;
}

function readPlayerAttackHit(entry) {
  const summary = inventoryAttackSummary(entry);
  const filePath = entry?.path ? abs(entry.path) : null;
  if (!filePath || !fs.existsSync(filePath)) {
    return {
      source: entry?.path ?? "(missing inventory path)",
      fromFile: false,
      ...summary,
      slots: (entry?.sections?.find((section) => section.name === "attackHitboxes")?.remap?.sampleEntries ?? []).reduce(
        (acc, item) => {
          const slot = acc.find((candidate) => candidate.slot === item.slot);
          if (slot) slot.entries.push({ position: item.position, value: item.value, record: null });
          else acc.push({ slot: item.slot, entries: [{ position: item.position, value: item.value, record: null }] });
          return acc;
        },
        [],
      ),
      records: [],
    };
  }

  const buffer = fs.readFileSync(filePath);
  const slots = [];
  const records = Array.from({ length: ATTACK_RECORD_COUNT }, (_, index) =>
    parseAttackRecord(buffer, ATTACK_RECORD_OFFSET + index * ATTACK_RECORD_SIZE, index),
  );

  for (let slot = 0; slot < ATTACK_REMAP_SLOTS; slot += 1) {
    const entries = [];
    for (let position = 0; position < ATTACK_REMAP_STRIDE; position += 1) {
      const value = buffer.readUInt8(ATTACK_REMAP_OFFSET + slot * ATTACK_REMAP_STRIDE + position);
      if (value === 0xff) break;
      entries.push({ position, value, record: records[value] ?? null });
    }
    if (entries.length > 0) slots.push({ slot, entries });
  }

  const activeRecordIds = new Set(slots.flatMap((slot) => slot.entries.map((entryItem) => entryItem.value)));
  return {
    source: entry.path,
    fromFile: true,
    activeSlots: slots.length,
    activeRemapEntries: slots.reduce((sum, slot) => sum + slot.entries.length, 0),
    uniqueActiveRecords: activeRecordIds.size,
    nonZeroRecords: records.filter((record) => record.nonZero).length,
    maxRecordIndex: Math.max(-1, ...records.filter((record) => record.nonZero).map((record) => record.index)),
    slots,
    records,
  };
}

function inventoryAttackSummary(entry) {
  const attack = entry?.sections?.find((section) => section.name === "attackHitboxes");
  return {
    activeSlots: new Set((attack?.remap?.sampleEntries ?? []).map((sample) => sample.slot)).size,
    activeRemapEntries: attack?.remap?.activeCount ?? 0,
    uniqueActiveRecords: attack?.remap?.uniqueActiveCount ?? 0,
    nonZeroRecords: attack?.records?.nonZeroRecordCount ?? 0,
    maxRecordIndex: attack?.records?.maxNonZeroRecordIndex ?? -1,
  };
}

function parseAttackRecord(buffer, offset, index) {
  const raw = buffer.subarray(offset, offset + ATTACK_RECORD_SIZE);
  const bone = buffer.readUInt8(offset + 0x01);
  return {
    index,
    offset,
    nonZero: raw.some((byte) => byte !== 0),
    shapeKind: buffer.readUInt8(offset + 0x00),
    boneIndex: bone & 0x7f,
    attachToRoot: (bone & 0x80) !== 0,
    collisionFlags: buffer.readUInt16BE(offset + 0x02),
    damageRecordIndex: buffer.readUInt16BE(offset + 0x04),
    activeStart: buffer.readInt16BE(offset + 0x06),
    activeEnd: buffer.readInt16BE(offset + 0x08),
    localOffset: [buffer.readFloatBE(offset + 0x0c), buffer.readFloatBE(offset + 0x10), buffer.readFloatBE(offset + 0x14)],
    halfExtent: [buffer.readFloatBE(offset + 0x18), buffer.readFloatBE(offset + 0x1c), buffer.readFloatBE(offset + 0x20)],
    radius: buffer.readFloatBE(offset + 0x24),
  };
}

function vec(values) {
  return values.map((value) => Number.parseFloat(value.toFixed(2))).join(",");
}

function recordShape(record) {
  if (!record) return "(inventory sample)";
  return `s${record.shapeKind} b${record.attachToRoot ? "root" : record.boneIndex} dmg${record.damageRecordIndex} f${record.activeStart}..${record.activeEnd}`;
}

function recordSize(record) {
  if (!record) return "";
  return `off[${vec(record.localOffset)}] he[${vec(record.halfExtent)}] r${Number.parseFloat(record.radius.toFixed(2))}`;
}

function readHitCallsites() {
  const decompDir = abs(PATHS.decompDir);
  if (!fs.existsSync(decompDir)) return [];
  const files = fs
    .readdirSync(decompDir)
    .filter((name) => /^chunk_\d+\.c$/i.test(name))
    .sort();
  const sites = [];
  for (const fileName of files) {
    const filePath = path.join(decompDir, fileName);
    const lines = fs.readFileSync(filePath, "utf8").split(/\r?\n/);
    lines.forEach((line, index) => {
      if (!line.includes("zz_008ac80_(") || line.trim().startsWith("undefined4 zz_008ac80_")) return;
      const expr = extractSecondArg(line);
      const site = {
        file: `${PATHS.decompDir}/${fileName}`,
        line: index + 1,
        text: compact(line),
        kindExpr: expr,
        category: classifyKindExpr(expr),
      };
      sites.push(site);
    });
  }
  return sites;
}

function extractSecondArg(line) {
  const callStart = line.indexOf("zz_008ac80_(");
  if (callStart < 0) return "(unknown)";
  let depth = 1;
  let comma = -1;
  let end = -1;
  const start = callStart + "zz_008ac80_(".length;
  for (let i = start; i < line.length; i += 1) {
    const ch = line[i];
    if (ch === "(") depth += 1;
    else if (ch === ")") {
      depth -= 1;
      if (depth === 0) {
        end = i;
        break;
      }
    } else if (ch === "," && depth === 1 && comma < 0) {
      comma = i;
    }
  }
  if (comma < 0 || end < 0) return "(unknown)";
  return compact(line.slice(comma + 1, end));
}

function classifyKindExpr(expr) {
  const text = compact(expr);
  const noCast = text.replace(/^\(int\)\s*/, "");
  if (/^(0x[0-9a-f]+|\d+)$/i.test(noCast)) return "literal kind";
  if (/DAT_[0-9a-f]+/i.test(text) && /\*\(short \*\)/.test(text)) return "DOL short table kind";
  if (/DAT_[0-9a-f]+/i.test(text) && /\*\(int \*\)/.test(text)) return "DOL int table kind";
  if (/DAT_[0-9a-f]+/i.test(text) && /\bchar\b/.test(text)) return "DOL byte table kind";
  if (/DAT_[0-9a-f]+/i.test(text)) return "DOL global/data kind";
  if (/\bparam_\d\b/.test(text) || /\biVar\d\b/.test(text) || /\bpsVar\d\b/.test(text) || /\bpuVar\d\b/.test(text)) {
    return "actor/state dynamic kind";
  }
  return "unknown kind";
}

function callsiteSummary(sites) {
  const byCategory = new Map();
  const literalKinds = new Map();
  for (const site of sites) {
    const group = byCategory.get(site.category) ?? [];
    group.push(site);
    byCategory.set(site.category, group);
    if (site.category === "literal kind") {
      const literal = site.kindExpr.replace(/^\(int\)\s*/, "").toLowerCase();
      literalKinds.set(literal, (literalKinds.get(literal) ?? 0) + 1);
    }
  }
  return { byCategory, literalKinds };
}

function commandRows(commandMap) {
  const mappings = Array.isArray(commandMap?.mappings) ? commandMap.mappings : [];
  return mappings.map((mapping) => ({
    input: mapping.inputBit ?? mapping.button ?? "",
    type: mapping.commandType ?? "",
    subtype: mapping.commandSubtype ?? "",
    condition: mapping.condition ?? "",
    fn: mapping.fn ?? "",
  }));
}

function stateRows(stateDispatch) {
  const interesting = new Set([18, 22, 23, 24]);
  return (stateDispatch?.slots ?? [])
    .filter((slot) => interesting.has(slot.slot))
    .map((slot) => ({
      slot: slot.slot,
      handler: slot.name,
      anim: typeof slot.anim === "string" ? slot.anim : `group ${slot.anim?.group} slot ${slot.anim?.slot}`,
      evidence: slot.evidence,
    }));
}

function commandMoveRows(commandMoveTables, id) {
  const assignment = commandMoveTables?.borgs?.[id] ?? null;
  if (!assignment?.tableId) return { assignment, rows: [] };
  const tableEntry = commandMoveTables?.tables?.[assignment.tableId] ?? null;
  if (!tableEntry) return { assignment, rows: [] };
  const rows = Object.entries(BUTTON_COMMAND_TYPES).map(([button, spec]) => {
    const typeEntry = tableEntry.types?.find((entry) => entry.type === spec.type) ?? null;
    const records = (typeEntry?.records ?? []).filter((record) => !record.disabled);
    const sample = records
      .slice(0, 4)
      .map((record) => {
        const dir = record.direction === null ? "" : `/d${record.direction}`;
        return `s${record.subtype}${dir} [${record.bytes.join(",")}]`;
      })
      .join("; ");
    return {
      button,
      context: spec.context,
      type: spec.type,
      mode: typeEntry?.modeName ?? "missing",
      recordCount: records.length,
      actionIndexes: [...new Set(records.map((record) => record.actionIndex))].join(","),
      variants: [...new Set(records.map((record) => record.variantIndex))].join(","),
      sample,
    };
  });
  return { assignment, tableEntry, rows };
}

function renderCommandEvidence(commandMap) {
  console.log("Command Evidence");
  console.log(short(commandMap?.summary, 160));
  console.log(
    table(commandRows(commandMap), [
      { header: "input/context", value: (row) => short(row.input, 40) },
      { header: "type", value: (row) => row.type },
      { header: "subtype", value: (row) => short(row.subtype, 42) },
      { header: "condition", value: (row) => short(row.condition, 74) },
      { header: "fn", value: (row) => row.fn },
    ]),
  );
  const subtype = commandMap?.commandSubtypeResolution;
  if (subtype) {
    console.log(
      `Subtype selectors: melee ${subtype.meleePath?.chunk ?? "?"}; ranged ${subtype.rangedPath?.chunk ?? "?"}; final dispatch ${subtype.finalDispatch?.chunk ?? "?"}`,
    );
    console.log(`Charge gate: ${short(subtype.rangedPath?.note ?? subtype.rangedPath?.subtypeMap, 180)}`);
  }
}

function renderStateEvidence(stateDispatch) {
  console.log("");
  console.log("State Animation Evidence");
  console.log(short(stateDispatch?._meta?.summary, 160));
  console.log(
    table(stateRows(stateDispatch), [
      { header: "state", value: (row) => row.slot },
      { header: "handler", value: (row) => row.handler },
      { header: "anim selector", value: (row) => short(row.anim, 56) },
      { header: "evidence", value: (row) => short(row.evidence, 86) },
    ]),
  );
}

function renderBorgCommandTable(commandMoveTables, borg) {
  console.log("");
  console.log("Borg Command Table Evidence");
  const { assignment, tableEntry, rows } = commandMoveRows(commandMoveTables, borg.id.toLowerCase());
  if (!assignment) {
    console.log("No constructor-table assignment found.");
    return;
  }
  console.log(
    `Constructor ${assignment.constructorAddress}; exact +0x4ec table: ${bool(assignment.exactCommandTable)}${
      assignment.tableId ? ` (${assignment.tableId})` : ""
    }`,
  );
  if (!tableEntry) {
    console.log("No decoded command table for this constructor yet.");
    return;
  }
  console.log(
    `Root ${tableEntry.rootAddress}; command struct ${tableEntry.commandStructAddress}; evidence ${tableEntry.evidence}`,
  );
  console.log(
    table(rows, [
      { header: "button", value: (row) => row.button },
      { header: "context", value: (row) => row.context },
      { header: "type", value: (row) => row.type },
      { header: "mode", value: (row) => row.mode },
      { header: "records", value: (row) => row.recordCount },
      { header: "action", value: (row) => row.actionIndexes || "none" },
      { header: "variant", value: (row) => row.variants || "none" },
      { header: "sample bytes", value: (row) => short(row.sample || "none", 96) },
    ]),
  );
}

function renderCallsites(sites) {
  const summary = callsiteSummary(sites);
  console.log("");
  console.log("HIT Spawner Call Sites");
  const rows = [...summary.byCategory.entries()]
    .sort((a, b) => b[1].length - a[1].length || a[0].localeCompare(b[0]))
    .map(([category, group]) => ({
      category,
      count: group.length,
      examples: group
        .slice(0, 3)
        .map((site) => `${path.basename(site.file)}:${site.line} ${site.kindExpr}`)
        .join("; "),
    }));
  console.log(
    table(rows, [
      { header: "category", value: (row) => row.category },
      { header: "calls", value: (row) => row.count },
      { header: "examples", value: (row) => short(row.examples, 116) },
    ]),
  );
  const literalRows = [...summary.literalKinds.entries()]
    .sort((a, b) => Number.parseInt(a[0]) - Number.parseInt(b[0]))
    .map(([kind, count]) => ({ kind, count }));
  console.log(
    `Literal kinds now pluggable: ${
      literalRows.length === 0 ? "none" : literalRows.map((row) => `${row.kind}=${row.count}`).join(", ")
    }`,
  );
}

function renderRosterSummary(borgsData, hitInventory, commandMoveTables, sites, opts) {
  const players = playerHitInventory(hitInventory);
  const summaries = players
    .map((entry) => ({ entry, summary: inventoryAttackSummary(entry) }))
    .sort((a, b) => b.summary.activeRemapEntries - a.summary.activeRemapEntries || a.entry.linkedBorgId.localeCompare(b.entry.linkedBorgId));
  const totals = summaries.reduce(
    (acc, item) => {
      acc.activeRemapEntries += item.summary.activeRemapEntries;
      acc.uniqueActiveRecords += item.summary.uniqueActiveRecords;
      acc.nonZeroRecords += item.summary.nonZeroRecords;
      if (item.summary.activeRemapEntries > 0) acc.withAttackRemaps += 1;
      return acc;
    },
    { activeRemapEntries: 0, uniqueActiveRecords: 0, nonZeroRecords: 0, withAttackRemaps: 0 },
  );

  console.log("Move Unblocker Audit: roster");
  console.log(`Borgs: ${(borgsData.borgs ?? []).length}; player HIT tables: ${players.length}`);
  const commandCoverage = commandMoveTables?._meta?.coverage;
  console.log(
    table(
      [
        commandCoverage
          ? {
              metric: "borgs with exact +0x4ec command tables",
              count: `${commandCoverage.exactCommandTableBorgs}/${commandCoverage.rosterBorgs}`,
            }
          : null,
        commandCoverage ? { metric: "decoded +0x4ec command tables", count: commandCoverage.decodedTables } : null,
        { metric: "borgs with attack remaps", count: totals.withAttackRemaps },
        { metric: "active attack remap entries", count: totals.activeRemapEntries },
        { metric: "unique active attack records", count: totals.uniqueActiveRecords },
        { metric: "nonzero attack records", count: totals.nonZeroRecords },
        { metric: "zz_008ac80 call sites", count: sites.length },
      ].filter(Boolean),
      [
        { header: "metric", value: (row) => row.metric },
        { header: "count", value: (row) => row.count },
      ],
    ),
  );
  console.log("");
  console.log(
    table(summaries.slice(0, opts.top), [
      { header: "borg", value: (row) => row.entry.linkedBorgId },
      { header: "name", value: (row) => row.entry.linkedBorgName },
      { header: "remap entries", value: (row) => row.summary.activeRemapEntries },
      { header: "unique records", value: (row) => row.summary.uniqueActiveRecords },
      { header: "nonzero records", value: (row) => row.summary.nonZeroRecords },
      { header: "max record", value: (row) => row.summary.maxRecordIndex },
    ]),
  );
}

function renderBorgHitReport(borg, entry, opts) {
  if (!entry) {
    console.log(`No player HIT table inventory entry found for ${borg.id} ${borg.name}.`);
    return;
  }
  const hit = readPlayerAttackHit(entry);
  console.log("");
  console.log(`Borg HIT Evidence: ${borg.id} ${borg.name}`);
  console.log(`Source: ${hit.source} (${hit.fromFile ? "decoded from file" : "inventory fallback"})`);
  console.log(
    `Attack remap slots: ${hit.activeSlots}; entries: ${hit.activeRemapEntries}; unique records: ${hit.uniqueActiveRecords}; nonzero records: ${hit.nonZeroRecords}; max record: ${hit.maxRecordIndex}`,
  );
  console.log("Rule: zz_008ac80_(actor, kind) selects attack remap slot <kind>, then each entry points to a 0x50 hitbox record.");
  const rows = hit.slots.slice(0, opts.records).map((slot) => ({
    slot: slot.slot,
    ids: slot.entries.map((item) => item.value).join(","),
    shapes: slot.entries.map((item) => recordShape(item.record)).join(" / "),
    sizes: slot.entries.map((item) => recordSize(item.record)).filter(Boolean).join(" / "),
  }));
  console.log(
    table(rows, [
      { header: "kind", value: (row) => row.slot },
      { header: "record ids", value: (row) => row.ids },
      { header: "shape/frame/damage", value: (row) => short(row.shapes, 92) },
      { header: "offset/extent/radius", value: (row) => short(row.sizes, 92) },
    ]),
  );
  if (hit.slots.length > opts.records) {
    console.log(`... ${hit.slots.length - opts.records} more active remap slots. Use --records ${hit.slots.length} to show all.`);
  }
}

function renderNextUnlocks(sites) {
  const summary = callsiteSummary(sites);
  const literalCount = summary.byCategory.get("literal kind")?.length ?? 0;
  const tableCount =
    (summary.byCategory.get("DOL byte table kind")?.length ?? 0) +
    (summary.byCategory.get("DOL short table kind")?.length ?? 0) +
    (summary.byCategory.get("DOL int table kind")?.length ?? 0);
  const dynamicCount =
    (summary.byCategory.get("actor/state dynamic kind")?.length ?? 0) +
    (summary.byCategory.get("unknown kind")?.length ?? 0);
  console.log("");
  console.log("Next Unlocks");
  console.log(`1. Plug literal HIT kinds first (${literalCount} calls): fixed kind values already point straight at remap slots.`);
  console.log(`2. Extract DAT_* kind arrays (${tableCount} calls): these should become static kind->slot tables.`);
  console.log(`3. Trace actor/state dynamic kinds only after static tables (${dynamicCount} calls): these are the real remaining runtime bridge.`);
}

const opts = parseArgs(process.argv.slice(2));
const borgsData = readJson(PATHS.borgs);
const hitInventory = readJson(PATHS.hitInventory);
const commandMap = readJson(PATHS.commandMap);
const commandMoveTables = readJson(PATHS.commandMoveTables);
const stateDispatch = readJson(PATHS.stateAnimDispatch);
const sites = readHitCallsites();

if (opts.borg) {
  const borg = findBorg(borgsData, opts.borg);
  if (!borg) fail(`unknown borg id/name: ${opts.borg}`, 2);
  console.log(`Move Unblocker Audit: ${borg.id} ${borg.name}`);
  renderCommandEvidence(commandMap);
  renderStateEvidence(stateDispatch);
  renderBorgCommandTable(commandMoveTables, borg);
  renderBorgHitReport(borg, hitInventoryForBorg(hitInventory, borg.id.toLowerCase()), opts);
  renderCallsites(sites);
  renderNextUnlocks(sites);
} else {
  renderRosterSummary(borgsData, hitInventory, commandMoveTables, sites, opts);
  renderCommandEvidence(commandMap);
  renderStateEvidence(stateDispatch);
  renderCallsites(sites);
  renderNextUnlocks(sites);
  console.log("");
  console.log("Use --borg <id> for decoded per-borg HIT remap slots, for example: rtk pnpm audit:move-unblockers -- --borg pl0615");
}
