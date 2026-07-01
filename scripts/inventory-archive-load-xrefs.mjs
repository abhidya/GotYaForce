#!/usr/bin/env node
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const indexPath = path.join(repoRoot, "research", "decomp", "index", "function-evidence-index.json");
const outJson = path.join(repoRoot, "research", "decomp", "index", "archive-load-xrefs.json");
const outMd = path.join(repoRoot, "research", "decomp", "index", "archive-load-xrefs.md");

if (!fs.existsSync(indexPath)) {
  throw new Error(`missing function evidence index: ${rel(indexPath)}; run npm run index:decomp first`);
}

const functionIndex = JSON.parse(fs.readFileSync(indexPath, "utf8"));
const functions = new Map(functionIndex.functions.map((fn) => [fn.address.toLowerCase(), fn]));

const roots = [
  {
    id: "dvd-open",
    address: "0x8020d1ec",
    label: "DVDOpen SDK import",
    relevance: "Lowest-level static file-open primitive currently visible in the decomp index.",
  },
  {
    id: "gcci-open",
    address: "0x802754ec",
    label: "gcCiOpen-style DVDOpen wrapper",
    relevance: "Validates filenames and reports DVDOpen failures before reading archives/files.",
  },
  {
    id: "gcci-get-file",
    address: "0x802756fc",
    label: "gcCiGetF-style open/close wrapper",
    relevance: "Opens a file path, checks file length, and closes the DVD handle.",
  },
  {
    id: "hsd-archive-parse",
    address: "0x8025b00c",
    label: "HSD_ArchiveParse SDK import",
    relevance: "Original HSD archive parser used by model/animation/public-symbol data paths.",
  },
  {
    id: "hsd-public-address",
    address: "0x8025b1b0",
    label: "HSD_ArchiveGetPublicAddress SDK import",
    relevance: "Original public-symbol lookup after archive parse.",
  },
  {
    id: "archive-public-wrapper",
    address: "0x80006c88",
    label: "HSD archive parse/public-address wrapper",
    relevance: "Parses an HSD archive and iterates public entries for runtime object data.",
  },
  {
    id: "secondary-archive-wrapper",
    address: "0x8004d548",
    label: "secondary HSD archive parse wrapper",
    relevance: "Allocates/initializes a parsed archive path reached from object setup helpers.",
  },
  {
    id: "active-archive-attach",
    address: "0x800419ec",
    label: "active object archive attach path",
    relevance:
      "Reads DAT_803bb4a0 by object slot/type state and calls the HSD archive wrapper used by spawn/init.",
  },
  {
    id: "active-borg-spawn",
    address: "0x800541ac",
    label: "active borg spawn init",
    relevance: "Challenge/battle spawn path that calls the active archive attach function.",
  },
  {
    id: "active-object-init",
    address: "0x80057b78",
    label: "active object init",
    relevance: "Related active object path that also calls the active archive attach function.",
  },
];

const chains = [
  {
    id: "active-borg-spawn-to-hsd-parse",
    addresses: ["0x800541ac", "0x800419ec", "0x80006c88", "0x8025b00c"],
    proves: "battle spawn init reaches original HSD_ArchiveParse through the active archive attach wrapper",
  },
  {
    id: "active-object-init-to-hsd-parse",
    addresses: ["0x80057b78", "0x800419ec", "0x80006c88", "0x8025b00c"],
    proves: "active object init reaches original HSD_ArchiveParse through the same attach wrapper",
  },
  {
    id: "active-borg-spawn-to-public-address",
    addresses: ["0x800541ac", "0x800419ec", "0x80006c88", "0x8025b1b0"],
    proves: "spawn init reaches HSD public-symbol lookup after archive parse",
  },
  {
    id: "gcci-open-to-dvdopen",
    addresses: ["0x802754ec", "0x8020d1ec"],
    proves: "gcCiOpen-style wrapper directly calls DVDOpen",
  },
  {
    id: "gcci-get-file-to-dvdopen",
    addresses: ["0x802756fc", "0x8020d1ec"],
    proves: "gcCiGetF-style wrapper directly calls DVDOpen",
  },
  {
    id: "secondary-object-path-to-hsd-parse",
    addresses: ["0x8004a754", "0x8004d548", "0x8025b00c"],
    proves: "secondary object setup path reaches original HSD_ArchiveParse",
  },
];

for (const root of roots) mustFunction(root.address);
for (const chain of chains) assertChain(chain);

const report = {
  generatedAt: new Date().toISOString(),
  generatedBy: rel(fileURLToPath(import.meta.url)),
  sourceIndex: rel(indexPath),
  principle:
    "Archive/stage/load behavior must be ported from original file-open, archive-parse, table, and trace evidence. This report does not authorize fake Challenge stage mappings.",
  findings: buildFindings(),
  roots: roots.map((root) => ({ ...root, function: compactFunction(mustFunction(root.address)) })),
  provenChains: chains.map(compactChain),
  supportingArtifacts: artifactRefs([
    "research/decomp/index/challenge-flow-evidence.md",
    "research/asset-inventory/stage-code-evidence.md",
    "research/asset-inventory/stage-geometry-collision.md",
    "research/asset-inventory/stage-lighting-render-state.md",
  ]),
  currentWebEvidence: refsFor([
    ["apps/game/src/sim/battleScene.ts", "load"],
    ["apps/game/src/sim/adapter.ts", "DEFAULT_ARENA_STAGE"],
    ["apps/game/src/main.ts", "async function loadStage"],
    ["packages/formats/src/hsd-anim.ts", "HSD"],
    ["packages/render/src/index.ts", "Stage"],
  ]),
  requiredNextTraceTasks: [
    "Break on 0x802754ec, 0x802756fc, and 0x8020d1ec while entering Challenge battle 1 and record filename strings.",
    "Break on 0x8025b00c and 0x80006c88 during the same run to connect loaded archive bytes to parsed HSD public names.",
    "Watch DAT_803bb4a0 and object+0x3e4 in 0x800419ec to confirm which slot/type selects each object archive pointer.",
    "Do not map human arena names or Challenge stage rotation to st## until the trace records the selected st## archive IDs.",
  ],
};

fs.writeFileSync(outJson, `${JSON.stringify(report, null, 2)}\n`);
fs.writeFileSync(outMd, renderMarkdown(report));

console.log("archive load xrefs");
console.log(`roots: ${report.roots.length}`);
console.log(`chains: ${report.provenChains.length}`);
console.log(`wrote ${rel(outJson)}`);
console.log(`wrote ${rel(outMd)}`);

function buildFindings() {
  const dvdOpen = mustFunction("0x8020d1ec");
  const hsdParse = mustFunction("0x8025b00c");
  const attach = mustFunction("0x800419ec");
  const archiveWrapper = mustFunction("0x80006c88");
  return [
    `DVDOpen has ${dvdOpen.callers.length} static callers in the current index: ${formatCalls(dvdOpen.callers)}.`,
    `HSD_ArchiveParse has ${hsdParse.callers.length} static callers in the current index: ${formatCalls(hsdParse.callers)}.`,
    `0x800419ec reads ${attach.globalReferences.join(", ")} and constants ${attach.constants.slice(0, 8).join(", ")} before calling ${formatCalls(attach.callees.filter((callee) => callee.address === "0x80006c88"))}.`,
    `0x80006c88 calls ${formatCalls(archiveWrapper.callees)}; this is the proven parse/public-address wrapper for active object archive data.`,
    "boot.dol static stage-code scan still has 0 st## hits, so Challenge arena selection still requires runtime archive-open tracing.",
  ];
}

function compactChain(chain) {
  return {
    ...chain,
    path: chain.addresses.map((address) => compactFunction(mustFunction(address))),
    edges: chain.addresses.slice(0, -1).map((address, index) => ({
      from: address,
      to: chain.addresses[index + 1],
      relation: "direct callee",
    })),
  };
}

function compactFunction(fn) {
  return {
    address: fn.address,
    currentFunctionName: fn.currentFunctionName,
    inferredName: fn.inferredName,
    sourceRef: fn.sourceRef,
    callers: fn.callers.slice(0, 24),
    callees: fn.callees.slice(0, 24),
    globalReferences: fn.globalReferences.slice(0, 24),
    globalAccesses: fn.globalAccesses.slice(0, 24),
    constants: fn.constants.slice(0, 32),
    strings: fn.strings.slice(0, 24),
    assets: fn.assets.slice(0, 24),
    topics: fn.topics,
    relatedWebModules: fn.relatedWebModules,
  };
}

function assertChain(chain) {
  for (let index = 0; index < chain.addresses.length - 1; index += 1) {
    const from = mustFunction(chain.addresses[index]);
    const to = chain.addresses[index + 1].toLowerCase();
    if (!from.callees.some((callee) => callee.address.toLowerCase() === to)) {
      throw new Error(`chain ${chain.id} is not proven: ${from.address} does not call ${chain.addresses[index + 1]}`);
    }
  }
}

function mustFunction(address) {
  const fn = functions.get(address.toLowerCase());
  if (!fn) throw new Error(`missing function ${address} in ${rel(indexPath)}`);
  return fn;
}

function refsFor(pairs) {
  return pairs.map(([file, needle]) => {
    const full = path.join(repoRoot, file);
    if (!fs.existsSync(full)) return { file, needle, sourceRef: null, found: false };
    const text = fs.readFileSync(full, "utf8");
    const line = text.split(/\r?\n/).findIndex((candidate) => candidate.includes(needle)) + 1;
    return {
      file,
      needle,
      found: line > 0,
      sourceRef: line > 0 ? `${file}:${line}` : null,
    };
  });
}

function artifactRefs(files) {
  return files.map((file) => ({ path: file, exists: fs.existsSync(path.join(repoRoot, file)) }));
}

function renderMarkdown(report) {
  const lines = [];
  lines.push("# Archive Load Xrefs");
  lines.push("");
  lines.push(`Generated: ${report.generatedAt}`);
  lines.push("");
  lines.push("## Principle");
  lines.push("");
  lines.push(report.principle);
  lines.push("");
  lines.push("## Findings");
  lines.push("");
  for (const finding of report.findings) lines.push(`- ${finding}`);
  lines.push("");
  lines.push("## Proven Call Chains");
  lines.push("");
  lines.push("| Chain | Direct path | Proves |");
  lines.push("| --- | --- | --- |");
  for (const chain of report.provenChains) {
    lines.push(`| ${chain.id} | ${chain.path.map(formatFunction).join(" -> ")} | ${chain.proves} |`);
  }
  lines.push("");
  lines.push("## Root Functions");
  lines.push("");
  lines.push("| Address | Current name | Inferred hint | Callers | Callees | Globals | Strings | Source |");
  lines.push("| --- | --- | --- | ---: | ---: | --- | --- | --- |");
  for (const root of report.roots) {
    const fn = root.function;
    lines.push(
      `| ${fn.address} | \`${fn.currentFunctionName}\` | \`${fn.inferredName ?? ""}\` | ${fn.callers.length} | ${fn.callees.length} | ${fn.globalReferences.slice(0, 4).join(", ") || "none"} | ${fn.strings.slice(0, 3).map((item) => `\`${item}\``).join("<br>") || "none"} | \`${fn.sourceRef}\` |`,
    );
  }
  lines.push("");
  lines.push("## Current Web Evidence");
  lines.push("");
  for (const ref of report.currentWebEvidence) {
    if (ref.found) {
      lines.push(`- \`${ref.sourceRef}\` contains \`${ref.needle}\`.`);
    } else {
      lines.push(`- \`${ref.file}\` does not contain \`${ref.needle}\`; keep this as a porting gap.`);
    }
  }
  lines.push("");
  lines.push("## Supporting Artifacts");
  lines.push("");
  for (const artifact of report.supportingArtifacts) {
    lines.push(`- \`${artifact.path}\`${artifact.exists ? "" : " (missing)"}`);
  }
  lines.push("");
  lines.push("## Required Next Trace Tasks");
  lines.push("");
  for (const task of report.requiredNextTraceTasks) lines.push(`- ${task}`);
  lines.push("");
  return `${lines.join("\n")}\n`;
}

function formatFunction(fn) {
  return `${fn.address} \`${fn.currentFunctionName}\``;
}

function formatCalls(calls) {
  if (!calls.length) return "none";
  return calls.map((call) => `${call.address} ${call.name}`).join(", ");
}

function rel(file) {
  return path.relative(repoRoot, file).replaceAll("\\", "/");
}
