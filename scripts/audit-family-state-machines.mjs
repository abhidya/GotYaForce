#!/usr/bin/env node

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const PLAYER_COMMAND_TYPES = new Set([0, 1, 2, 3, 5]);
const COMPLETE_STATUSES = new Set(["ported", "inactive", "delegated"]);
const ALL_STATUSES = new Set([...COMPLETE_STATUSES, "partial", "missing"]);
const PORTED_EVIDENCE_FIELDS = [
  "rootDispatch",
  "variantDispatch",
  "phaseTransitions",
  "constants",
  "streamBehavior",
  "bridgeWiring",
  "focusedTests",
];

export function stableStringify(value) {
  return `${JSON.stringify(sortValue(value), null, 2)}\n`;
}

function sortValue(value) {
  if (Array.isArray(value)) return value.map(sortValue);
  if (!value || typeof value !== "object") return value;
  return Object.fromEntries(Object.keys(value).sort().map((key) => [key, sortValue(value[key])]));
}

export function discoverImplementationIds(sources) {
  const ids = new Set();
  const keyPattern = /^\s*(pl[0-9a-f]{4})\s*:/gim;
  const loopPattern = /["'](pl[0-9a-f]{4})["']/gi;
  for (const source of sources) {
    for (const match of source.text.matchAll(keyPattern)) ids.add(match[1].toLowerCase());
    // Registration helper arrays are necessarily string-keyed. Counting these as an
    // implementation reference is conservative: it can only move missing -> partial.
    for (const match of source.text.matchAll(loopPattern)) ids.add(match[1].toLowerCase());
  }
  return ids;
}

export function buildAudit({ commandData, actionData, implementationIds, reviewed = { classifications: [] } }) {
  const errors = [];
  const invalidCompleteKeys = new Set();
  const borgs = commandData?.borgs ?? {};
  const tables = commandData?.tables ?? {};
  const actionBorgs = actionData?.borgs ?? {};
  const rosterIds = new Set(Object.keys(borgs));

  for (const id of implementationIds) {
    if (!rosterIds.has(id)) errors.push(`implementation registration references unknown borg id ${id}`);
  }

  const reviewedByKey = new Map();
  for (const item of reviewed.classifications ?? []) {
    const key = `${String(item.constructorAddress).toLowerCase()}:${item.actionIndex}`;
    if (reviewedByKey.has(key)) errors.push(`duplicate constructor classification ${key}`);
    reviewedByKey.set(key, item);
    if (!ALL_STATUSES.has(item.status)) errors.push(`invalid status ${item.status} for ${key}`);
    if (!Number.isInteger(item.actionIndex) || item.actionIndex < 0 || item.actionIndex > 4) {
      errors.push(`invalid action index ${item.actionIndex} for ${key}`);
    }
    if ((item.status === "ported" || item.status === "delegated") && (!Array.isArray(item.coverage) || item.coverage.length === 0)) {
      errors.push(`${item.status} classification ${key} requires explicit member and live-variant coverage`);
    }
    if (item.status === "inactive" && !(item.evidence?.length > 0)) errors.push(`inactive classification ${key} requires evidence`);
    if (item.status === "delegated" && !item.target) errors.push(`delegated classification ${key} requires target`);
  }

  const grouped = new Map();
  for (const [id, assignment] of Object.entries(borgs)) {
    const ctor = assignment.constructorAddress?.toLowerCase();
    if (!ctor) {
      errors.push(`borg ${id} has no constructorAddress`);
      continue;
    }
    const family = grouped.get(ctor) ?? { constructorAddress: ctor, members: [] };
    family.members.push({ id, assignment });
    grouped.set(ctor, family);
  }

  const families = [...grouped.values()].sort((a, b) => a.constructorAddress.localeCompare(b.constructorAddress)).map((family) => {
    family.members.sort((a, b) => a.id.localeCompare(b.id));
    const slots = new Map();
    const implementedMembers = family.members.filter(({ id }) => implementationIds.has(id)).map(({ id }) => id);

    for (const { id, assignment } of family.members) {
      const rom = actionBorgs[id];
      if (!rom) errors.push(`borg ${id} is absent from family action tables`);
      if (rom?.constructorAddress?.toLowerCase() !== family.constructorAddress) {
        errors.push(`borg ${id} constructor disagrees between command and action tables`);
      }
      for (const [rawIndex, action] of Object.entries(rom?.actions ?? {})) {
        const actionIndex = Number(rawIndex);
        if (!Number.isInteger(actionIndex) || actionIndex < 0 || actionIndex > 4) {
          errors.push(`invalid action index ${rawIndex} in action table for ${id}`);
          continue;
        }
        const slot = ensureSlot(slots, actionIndex);
        slot.rootEvidence.push(`${id}: root ${rom.root}, action table ${rom.actionTable}, handler ${action.handler}`);
        slot.live = true;
        const variants = Object.keys(action.variants ?? {}).map(Number).filter(Number.isInteger);
        noteLiveMember(slot, id, variants);
      }

      const table = tables[assignment.tableId];
      if (!table) {
        errors.push(`borg ${id} references absent command table ${assignment.tableId}`);
        continue;
      }
      for (const type of table.types ?? []) {
        if (!PLAYER_COMMAND_TYPES.has(type.type)) continue;
        for (const record of type.records ?? []) {
          const actionIndex = record.actionIndex;
          if (!Number.isInteger(actionIndex) || actionIndex < 0 || actionIndex > 4) {
            if (!record.disabled) errors.push(`live command ${id} ${record.address} has invalid action index ${actionIndex}`);
            continue;
          }
          const slot = ensureSlot(slots, actionIndex);
          const evidence = `${id}: command ${record.address} (${table.evidence})`;
          if (record.disabled) slot.disabledEvidence.push(evidence);
          else {
            slot.live = true;
            slot.commandEvidence.push(evidence);
            noteLiveMember(slot, id, Number.isInteger(record.variantIndex) ? [record.variantIndex] : []);
          }
        }
      }
    }

    const actions = [...slots.values()].sort((a, b) => a.actionIndex - b.actionIndex).map((slot) => {
      const key = `${family.constructorAddress}:${slot.actionIndex}`;
      const explicit = reviewedByKey.get(key);
      let status;
      let evidence = [];
      let target;
      if (explicit) {
        status = explicit.status;
        evidence = explicit.evidence ?? [];
        target = explicit.target;
        if (!slot.live && ["ported", "partial", "missing", "delegated"].includes(status)) {
          errors.push(`${key} is ROM-inactive but classified ${status}`);
        }
        if (slot.live && status === "inactive") errors.push(`${key} is ROM-live but classified inactive`);
        if (status === "ported" || status === "delegated") {
          const before = errors.length;
          validateCompleteCoverage({ item: explicit, key, slot, implementationIds, errors });
          if (errors.length !== before) invalidCompleteKeys.add(key);
        }
      } else if (!slot.live) {
        status = "inactive";
        evidence = slot.disabledEvidence;
      } else {
        status = implementedMembers.length > 0 ? "partial" : "missing";
      }
      return {
        actionIndex: slot.actionIndex,
        status,
        ...(target ? { target } : {}),
        evidence,
        ...(explicit?.coverage ? { classificationCoverage: explicit.coverage } : {}),
        liveCoverage: [...slot.liveMembers.entries()]
          .sort(([a], [b]) => a.localeCompare(b))
          .map(([member, variants]) => ({ member, variants: [...variants].sort((a, b) => a - b) })),
        romEvidence: [...slot.rootEvidence, ...slot.commandEvidence, ...slot.disabledEvidence].sort(),
      };
    });

    return {
      constructorAddress: family.constructorAddress,
      members: family.members.map(({ id }) => id),
      implementationMembers: implementedMembers,
      actions,
    };
  });

  for (const key of reviewedByKey.keys()) {
    const [ctor, rawIndex] = key.split(":");
    const family = families.find((entry) => entry.constructorAddress === ctor);
    if (!family || !family.actions.some((slot) => slot.actionIndex === Number(rawIndex))) {
      errors.push(`reviewed classification ${key} does not reference a ROM slot`);
    }
  }

  validateDelegations(families, reviewedByKey, invalidCompleteKeys, errors);

  const counts = Object.fromEntries([...ALL_STATUSES].sort().map((status) => [status, 0]));
  for (const family of families) for (const slot of family.actions) counts[slot.status]++;
  return {
    schemaVersion: 2,
    sourceArtifacts: {
      commands: "packages/combat/src/data/commandMoveTables.json",
      actions: "packages/combat/src/data/actionStreamTables.json",
      implementations: "packages/combat/src/bridge.ts and packages/combat/src/families/*.ts",
      reviewedClassifications: "research/decomp/data/family-state-machine-classifications.reviewed.json",
    },
    summary: { borgs: Object.keys(borgs).length, constructorFamilies: families.length, actionSlots: Object.values(counts).reduce((a, b) => a + b, 0), counts },
    structuralErrors: [...new Set(errors)].sort(),
    families,
  };
}

function ensureSlot(slots, actionIndex) {
  if (!slots.has(actionIndex)) slots.set(actionIndex, { actionIndex, live: false, liveMembers: new Map(), rootEvidence: [], commandEvidence: [], disabledEvidence: [] });
  return slots.get(actionIndex);
}

function noteLiveMember(slot, member, variants) {
  const live = slot.liveMembers.get(member) ?? new Set();
  for (const variant of variants) if (Number.isInteger(variant)) live.add(variant);
  slot.liveMembers.set(member, live);
}

function validateCompleteCoverage({ item, key, slot, implementationIds, errors }) {
  if (!Array.isArray(item.coverage) || item.coverage.length === 0) {
    errors.push(`${item.status} classification ${key} requires explicit member and live-variant coverage`);
    return;
  }
  const coverageByMember = new Map();
  for (const coverage of item.coverage) {
    const member = String(coverage.member ?? "").toLowerCase();
    if (coverageByMember.has(member)) errors.push(`${item.status} classification ${key} duplicates member coverage ${member}`);
    coverageByMember.set(member, coverage);
    if (!implementationIds.has(member)) errors.push(`${item.status} classification ${key} references absent implementation for ${member}`);
    if (!Array.isArray(coverage.variants) || coverage.variants.some((variant) => !Number.isInteger(variant) || variant < 0)) {
      errors.push(`${item.status} classification ${key} has invalid variant coverage for ${member}`);
    }
    if (item.status === "ported") {
      for (const field of PORTED_EVIDENCE_FIELDS) {
        if (!(coverage.evidence?.[field]?.length > 0)) errors.push(`ported classification ${key} member ${member} requires ${field} evidence`);
      }
    } else if (!(coverage.romDelegationEvidence?.length > 0)) {
      errors.push(`delegated classification ${key} member ${member} requires ROM delegation evidence`);
    }
  }
  for (const [member, variants] of slot.liveMembers) {
    const coverage = coverageByMember.get(member);
    if (!coverage) {
      errors.push(`${item.status} classification ${key} does not cover live member ${member}`);
      continue;
    }
    const expected = [...variants].sort((a, b) => a - b);
    const actual = [...new Set(coverage.variants ?? [])].sort((a, b) => a - b);
    if (JSON.stringify(expected) !== JSON.stringify(actual)) {
      errors.push(`${item.status} classification ${key} member ${member} variants [${actual}] do not match ROM-live variants [${expected}]`);
    }
  }
  for (const member of coverageByMember.keys()) {
    if (!slot.liveMembers.has(member)) errors.push(`${item.status} classification ${key} covers non-live member ${member}`);
  }
}

function targetKey(target) {
  if (!target || typeof target !== "object") return null;
  if (!Number.isInteger(target.actionIndex)) return null;
  return `${String(target.constructorAddress).toLowerCase()}:${target.actionIndex}`;
}

function validateDelegations(families, reviewedByKey, invalidCompleteKeys, errors) {
  const slots = new Map();
  for (const family of families) for (const action of family.actions) slots.set(`${family.constructorAddress}:${action.actionIndex}`, action);
  const edges = new Map();
  for (const [key, item] of reviewedByKey) {
    if (item.status !== "delegated") continue;
    const target = targetKey(item.target);
    if (!target) {
      errors.push(`delegated classification ${key} has invalid target`);
      continue;
    }
    edges.set(key, target);
    const targetSlot = slots.get(target);
    if (!targetSlot) errors.push(`delegated classification ${key} targets nonexistent audited slot ${target}`);
    else if ((targetSlot.status !== "ported" && targetSlot.status !== "delegated") || invalidCompleteKeys.has(target)) {
      errors.push(`delegated classification ${key} targets incomplete slot ${target} (${targetSlot.status})`);
    }
  }
  const visiting = new Set();
  const visited = new Set();
  function visit(key, chain) {
    if (visiting.has(key)) {
      const start = chain.indexOf(key);
      errors.push(`delegation cycle: ${[...chain.slice(start), key].join(" -> ")}`);
      return;
    }
    if (visited.has(key) || !edges.has(key)) return;
    visiting.add(key);
    visit(edges.get(key), [...chain, key]);
    visiting.delete(key);
    visited.add(key);
  }
  for (const key of edges.keys()) visit(key, []);
}

export function markdownSummary(audit) {
  const c = audit.summary.counts;
  return `# Family state-machine coverage\n\n` +
    `Deterministic audit of the GG4E constructor roster, ROM command/root tables, bridge registrations, and family action tables.\n\n` +
    `- Constructor families: ${audit.summary.constructorFamilies}\n` +
    `- Borg roster entries: ${audit.summary.borgs}\n` +
    `- Action slots: ${audit.summary.actionSlots}\n` +
    `- Ported: ${c.ported}; delegated: ${c.delegated}; inactive: ${c.inactive}; partial: ${c.partial}; missing: ${c.missing}\n` +
    `- Structural errors: ${audit.structuralErrors.length}\n\n` +
    `Default mode checks structural validity. Strict mode additionally fails while partial or missing live slots remain. See \`data/family-state-machine-coverage.json\` for slot evidence.\n`;
}

export function exitCodeForAudit(audit, strict = false) {
  if (audit.structuralErrors.length) return 1;
  if (strict && (audit.summary.counts.partial || audit.summary.counts.missing)) return 1;
  return 0;
}

async function main() {
  const here = path.dirname(fileURLToPath(import.meta.url));
  const root = path.resolve(here, "..");
  const readJson = (relative) => JSON.parse(fs.readFileSync(path.join(root, relative), "utf8"));
  const familyDir = path.join(root, "packages/combat/src/families");
  const sources = [path.join(root, "packages/combat/src/bridge.ts"), ...fs.readdirSync(familyDir).filter((name) => name.endsWith(".ts")).map((name) => path.join(familyDir, name))]
    .map((file) => ({ file, text: fs.readFileSync(file, "utf8") }));
  const audit = buildAudit({
    commandData: readJson("packages/combat/src/data/commandMoveTables.json"),
    actionData: readJson("packages/combat/src/data/actionStreamTables.json"),
    implementationIds: discoverImplementationIds(sources),
    reviewed: readJson("research/decomp/data/family-state-machine-classifications.reviewed.json"),
  });
  fs.writeFileSync(path.join(root, "research/decomp/data/family-state-machine-coverage.json"), stableStringify(audit));
  fs.writeFileSync(path.join(root, "research/decomp/family-state-machine-coverage.md"), markdownSummary(audit));
  console.log(`family-state-machines: ${audit.summary.constructorFamilies} constructors, ${audit.summary.actionSlots} slots; ported=${audit.summary.counts.ported} delegated=${audit.summary.counts.delegated} inactive=${audit.summary.counts.inactive} partial=${audit.summary.counts.partial} missing=${audit.summary.counts.missing}`);
  if (audit.structuralErrors.length) {
    for (const error of audit.structuralErrors) console.error(`ERROR: ${error}`);
    process.exitCode = 1;
  } else if (process.argv.includes("--strict") && exitCodeForAudit(audit, true)) {
    console.error("strict audit failed: partial or missing live action slots remain");
    process.exitCode = 1;
  }
}

if (process.argv[1] && path.resolve(process.argv[1]) === fileURLToPath(import.meta.url)) await main();
