#!/usr/bin/env node
// Build navigation indexes over the copied Ghidra decompile tree:
// - start-rooted static call-flow summary
// - class-like symbol/method map
// - research-doc/data address resolver for function starts, interior labels, and data anchors

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const decompDir = path.join(repoRoot, "research", "decomp");
const indexDir = path.join(decompDir, "index");
const organizedDir = path.join(decompDir, "organized");
const evidenceFile = path.join(indexDir, "function-evidence-index.json");
const organizedMapFile = path.join(organizedDir, "_map.tsv");
const startAddress = "80003154";

const outFiles = {
  startJson: path.join(indexDir, "start-code-flow.json"),
  startMd: path.join(indexDir, "start-code-flow.md"),
  classJson: path.join(indexDir, "class-map.json"),
  classMd: path.join(indexDir, "class-map.md"),
  addressJson: path.join(indexDir, "address-resolution.json"),
  addressMd: path.join(indexDir, "address-resolution.md"),
};

const evidence = readJson(evidenceFile);
const mapRows = parseOrganizedMap(organizedMapFile);
const organizedByAddress = new Map(mapRows.map((row) => [row.address, row]));
const functions = evidence.functions.map((fn) => ({
  ...fn,
  addressKey: strip0x(fn.address),
  organized: organizedByAddress.get(strip0x(fn.address)) ?? null,
}));
const functionByAddress = new Map(functions.map((fn) => [fn.addressKey, fn]));
const callableAliases = buildCallableAliases();
const sortedFunctionAddresses = [...functionByAddress.keys()].sort();
const knownAnchorAddresses = new Set((evidence.knownAnchors ?? []).map((anchor) => strip0x(anchor.address)));

const startFlow = buildStartFlow();
const classMap = buildClassMap(startFlow.parentByAddress);
const addressResolution = buildAddressResolution();

fs.mkdirSync(indexDir, { recursive: true });
writeJson(outFiles.startJson, stripRuntimeMaps(startFlow));
fs.writeFileSync(outFiles.startMd, renderStartFlowMarkdown(startFlow));
writeJson(outFiles.classJson, classMap);
fs.writeFileSync(outFiles.classMd, renderClassMapMarkdown(classMap));
writeJson(outFiles.addressJson, addressResolution);
fs.writeFileSync(outFiles.addressMd, renderAddressResolutionMarkdown(addressResolution));

console.log("decomp navigation indexes");
console.log(`start reachable functions: ${startFlow.summary.reachableFunctions}`);
console.log(`classes: ${classMap.summary.classCount}, methods: ${classMap.summary.methodCount}`);
console.log(`address references resolved: ${addressResolution.summary.totalReferences}`);
for (const file of Object.values(outFiles)) console.log(`wrote ${rel(file)}`);

function buildStartFlow() {
  const root = functionByAddress.get(startAddress);
  if (!root) throw new Error(`missing start function ${fmt(startAddress)}`);

  const queue = [startAddress];
  const depthByAddress = new Map([[startAddress, 0]]);
  const parentByAddress = new Map([[startAddress, null]]);
  const viaNameByAddress = new Map();

  for (let i = 0; i < queue.length; i += 1) {
    const address = queue[i];
    const fn = functionByAddress.get(address);
    if (!fn) continue;
    const depth = depthByAddress.get(address) ?? 0;
    for (const callee of fn.callees ?? []) {
      const calleeAddress = strip0x(callee.address);
      if (!functionByAddress.has(calleeAddress) || depthByAddress.has(calleeAddress)) continue;
      depthByAddress.set(calleeAddress, depth + 1);
      parentByAddress.set(calleeAddress, address);
      viaNameByAddress.set(calleeAddress, callee.name);
      queue.push(calleeAddress);
    }
  }

  const reachable = [...depthByAddress.keys()].map((address) => functionByAddress.get(address)).filter(Boolean);
  const routeCounts = countBy(reachable, (fn) => dirnameOrBucket(fn.organized));
  const topicCounts = countMany(reachable, (fn) => fn.topics ?? []);
  const nameSourceCounts = countBy(reachable, (fn) => fn.organized?.nameSource ?? "unknown");
  const depthCounts = countBy(reachable, (fn) => String(depthByAddress.get(fn.addressKey)));
  const directCallees = orderedCallees(root).map((callee) => {
    const address = strip0x(callee.address);
    const fn = functionByAddress.get(address);
    const subtree = reachableFrom(address);
    return {
      address: fmt(address),
      callName: callee.name,
      displayName: displayName(fn),
      route: dirnameOrBucket(fn?.organized),
      topics: fn?.topics ?? [],
      reachableFunctionsBelow: subtree.size,
      path: fn?.organized?.path ?? null,
    };
  });
  const mainLoop = buildOrderedFunctionFlow("800527d8", "Main game loop");

  const classMethods = mapRows
    .filter((row) => row.className && depthByAddress.has(row.address))
    .map((row) => ({
      address: fmt(row.address),
      className: row.className,
      method: row.displayName,
      path: row.path,
      shortestPath: shortestPath(row.address, parentByAddress),
    }));

  const knownAnchors = [...knownAnchorAddresses]
    .filter((address) => depthByAddress.has(address))
    .sort()
    .map((address) => {
      const fn = functionByAddress.get(address);
      return {
        address: fmt(address),
        displayName: displayName(fn),
        route: dirnameOrBucket(fn?.organized),
        topics: fn?.topics ?? [],
        path: fn?.organized?.path ?? null,
        shortestPath: shortestPath(address, parentByAddress),
      };
    });

  const indirectCallSites = reachable
    .filter((fn) => hasIndirectCall(fn))
    .slice(0, 200)
    .map((fn) => ({
      address: fn.address,
      displayName: displayName(fn),
      route: dirnameOrBucket(fn.organized),
      sourceRef: fn.sourceRef,
      path: fn.organized?.path ?? null,
    }));

  return {
    generatedAt: new Date().toISOString(),
    generatedBy: rel(fileURLToPath(import.meta.url)),
    root: {
      address: fmt(startAddress),
      displayName: displayName(root),
      sourceRef: root.sourceRef,
      path: root.organized?.path ?? null,
    },
    summary: {
      totalFunctions: functions.length,
      reachableFunctions: reachable.length,
      reachablePct: pct(reachable.length, functions.length),
      directCallees: directCallees.length,
      reachableKnownAnchors: knownAnchors.length,
      reachableClassMethods: classMethods.length,
      indirectCallSitesSampled: indirectCallSites.length,
    },
    directCallees,
    mainLoop,
    routeCounts,
    topicCounts,
    nameSourceCounts,
    depthCounts,
    knownAnchors,
    classMethods,
    indirectCallSites,
    parentByAddress,
  };
}

function buildOrderedFunctionFlow(address, title) {
  const fn = functionByAddress.get(address);
  if (!fn) return null;
  const callees = orderedCallees(fn).map((callee, index) => {
    const calleeAddress = strip0x(callee.address);
    const target = functionByAddress.get(calleeAddress);
    return {
      index: index + 1,
      phase: address === "800527d8" && index < 2 ? "pre-loop init" : "per-frame loop",
      address: fmt(calleeAddress),
      callName: callee.name,
      displayName: displayName(target),
      route: dirnameOrBucket(target?.organized),
      topics: target?.topics ?? [],
      reachableFunctionsBelow: reachableFrom(calleeAddress).size,
      path: target?.organized?.path ?? null,
      note: mainLoopNote(displayName(target)),
    };
  });
  return {
    title,
    address: fmt(address),
    displayName: displayName(fn),
    path: fn.organized?.path ?? null,
    sourceRef: fn.sourceRef,
    callees,
  };
}

function buildClassMap(parentByAddress) {
  const classes = new Map();
  for (const row of mapRows) {
    if (!row.className) continue;
    const fn = functionByAddress.get(row.address);
    const classEntry =
      classes.get(row.className) ??
      {
        className: row.className,
        methodCount: 0,
        methods: [],
      };
    classEntry.methods.push({
      address: fmt(row.address),
      originalName: row.originalName,
      displayName: row.displayName,
      path: row.path,
      sourceChunk: row.srcChunk,
      sourceRef: fn?.sourceRef ?? null,
      topics: fn?.topics ?? [],
      callers: (fn?.callers ?? []).slice(0, 20),
      callees: (fn?.callees ?? []).slice(0, 20),
      reachableFromStart: parentByAddress.has(row.address),
      shortestPathFromStart: parentByAddress.has(row.address) ? shortestPath(row.address, parentByAddress) : [],
    });
    classEntry.methodCount = classEntry.methods.length;
    classes.set(row.className, classEntry);
  }

  const classList = [...classes.values()].sort((a, b) => a.className.localeCompare(b.className));
  const reachableMethodCount = classList.flatMap((cls) => cls.methods).filter((method) => method.reachableFromStart).length;
  return {
    generatedAt: new Date().toISOString(),
    generatedBy: rel(fileURLToPath(import.meta.url)),
    summary: {
      classCount: classList.length,
      methodCount: classList.reduce((sum, cls) => sum + cls.methodCount, 0),
      reachableMethodCount,
      note: "This maps C++-style symbols present in the Ghidra/map export. It does not yet recover anonymous C structs or vtables.",
    },
    classes: classList,
  };
}

function buildAddressResolution() {
  const docs = collectResearchFiles();
  const refs = new Map();
  const dataFileAnchors = new Map();

  for (const file of docs) {
    const text = fs.readFileSync(file, "utf8");
    for (const address of extract80xxAddresses(text)) addRef(refs, address, file, "content");
    for (const address of extract80xxAddresses(path.basename(file))) {
      addRef(refs, address, file, "filename");
      if (rel(file).startsWith("research/decomp/data/")) {
        const key = strip0x(address);
        if (!dataFileAnchors.has(key)) dataFileAnchors.set(key, []);
        dataFileAnchors.get(key).push(rel(file));
      }
    }
  }

  const resolutions = [...refs.entries()]
    .sort(([a], [b]) => a.localeCompare(b))
    .map(([address, sources]) => resolveAddress(address, sources, dataFileAnchors.get(address) ?? []));
  const byKind = countBy(resolutions, (item) => item.kind);
  const exactFunctionCount = resolutions.filter((item) => item.kind === "function-start").length;
  const nonFunctionCount = resolutions.length - exactFunctionCount;

  return {
    generatedAt: new Date().toISOString(),
    generatedBy: rel(fileURLToPath(import.meta.url)),
    summary: {
      scannedFiles: docs.length,
      totalReferences: resolutions.length,
      exactFunctionStarts: exactFunctionCount,
      nonFunctionReferences: nonFunctionCount,
      exactFunctionPct: pct(exactFunctionCount, resolutions.length),
      byKind,
    },
    resolutions,
  };
}

function resolveAddress(address, sources, dataFiles) {
  const sourceList = [...sources.values()];
  const exact = functionByAddress.get(address);
  if (exact) {
    return {
      address: fmt(address),
      kind: "function-start",
      displayName: displayName(exact),
      functionAddress: fmt(address),
      functionPath: exact.organized?.path ?? null,
      sourceRef: exact.sourceRef,
      offsetFromFunctionStart: 0,
      dataFiles,
      sources: sourceList,
    };
  }

  const idx = upperBound(sortedFunctionAddresses, address) - 1;
  const prev = idx >= 0 ? sortedFunctionAddresses[idx] : null;
  const next = idx + 1 < sortedFunctionAddresses.length ? sortedFunctionAddresses[idx + 1] : null;
  const numeric = parseInt(address, 16);
  const lastFunction = parseInt(sortedFunctionAddresses.at(-1), 16);

  if (prev && next && numeric < lastFunction) {
    const fn = functionByAddress.get(prev);
    return {
      address: fmt(address),
      kind: "function-interior",
      displayName: displayName(fn),
      functionAddress: fmt(prev),
      functionPath: fn?.organized?.path ?? null,
      sourceRef: fn?.sourceRef ?? null,
      offsetFromFunctionStart: numeric - parseInt(prev, 16),
      nextFunctionAddress: fmt(next),
      dataFiles,
      sources: sourceList,
    };
  }

  const kind = dataFiles.length ? "extracted-data-anchor" : isLikelyDataOrGlobal(address) ? "data-or-global" : "unresolved-nonfunction";
  return {
    address: fmt(address),
    kind,
    displayName: null,
    functionAddress: null,
    functionPath: null,
    sourceRef: null,
    offsetFromFunctionStart: null,
    nextFunctionAddress: null,
    dataFiles,
    sources: sourceList,
  };
}

function collectResearchFiles() {
  const skipDirs = new Set(["ghidra-export", "organized", "GotchaForce.rep", "scratch-verify"]);
  const out = [];
  walk(decompDir);
  return out.sort();

  function walk(dir) {
    for (const entry of fs.readdirSync(dir, { withFileTypes: true })) {
      if (entry.isDirectory() && skipDirs.has(entry.name)) continue;
      const full = path.join(dir, entry.name);
      if (entry.isDirectory()) {
        walk(full);
      } else if (isResearchFile(full)) {
        out.push(full);
      }
    }
  }
}

function isResearchFile(file) {
  const relative = rel(file);
  if (!/\.(md|txt|json|csv|tsv)$/i.test(file)) return false;
  if (relative.includes("function-evidence-index.")) return false;
  if (relative.includes("address-resolution.")) return false;
  if (relative.includes("start-code-flow.")) return false;
  if (relative.includes("class-map.")) return false;
  return true;
}

function reachableFrom(rootAddress) {
  const seen = new Set();
  const queue = [rootAddress];
  for (let i = 0; i < queue.length; i += 1) {
    const address = queue[i];
    if (seen.has(address)) continue;
    seen.add(address);
    const fn = functionByAddress.get(address);
    if (!fn) continue;
    for (const callee of fn.callees ?? []) {
      const calleeAddress = strip0x(callee.address);
      if (functionByAddress.has(calleeAddress) && !seen.has(calleeAddress)) queue.push(calleeAddress);
    }
  }
  return seen;
}

function shortestPath(address, parentByAddress) {
  const out = [];
  let cur = address;
  while (cur) {
    const fn = functionByAddress.get(cur);
    out.push({
      address: fmt(cur),
      displayName: displayName(fn),
      path: fn?.organized?.path ?? null,
    });
    cur = parentByAddress.get(cur);
  }
  return out.reverse();
}

function hasIndirectCall(fn) {
  const calleeNames = (fn.callees ?? []).map((callee) => callee.name).join(" ");
  const globals = (fn.globalReferences ?? []).join(" ");
  return /\bPTR_FUN_/.test(globals) || /\(\*\*?\(code \*\*\)/.test(calleeNames) || /\bdispatch\b/i.test(displayName(fn));
}

function parseOrganizedMap(file) {
  const [headerLine, ...lines] = fs.readFileSync(file, "utf8").trimEnd().split(/\r?\n/);
  const headers = headerLine.split("\t");
  return lines.map((line) => {
    const parts = line.split("\t");
    const row = Object.fromEntries(headers.map((header, i) => [header, parts[i] ?? ""]));
    return {
      address: row.address.toLowerCase(),
      originalName: row.original_name,
      displayName: row.display_name,
      nameSource: row.name_source,
      className: row.class,
      bucket: row.bucket,
      routeSource: row.route_source,
      path: row.path,
      srcChunk: row.src_chunk,
    };
  });
}

function renderStartFlowMarkdown(flow) {
  const lines = [];
  lines.push("# Start Code Flow");
  lines.push("");
  lines.push(`Generated: ${flow.generatedAt}`);
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push(`- Root: \`${flow.root.address}\` \`${flow.root.displayName}\` at \`${flow.root.path}\``);
  lines.push(`- Static reachable functions: ${flow.summary.reachableFunctions} / ${flow.summary.totalFunctions} (${flow.summary.reachablePct})`);
  lines.push(`- Direct callees from \`start\`: ${flow.summary.directCallees}`);
  lines.push(`- Reachable known anchors: ${flow.summary.reachableKnownAnchors}`);
  lines.push(`- Reachable class methods: ${flow.summary.reachableClassMethods}`);
  lines.push("");
  lines.push("## Boot Flow");
  lines.push("");
  lines.push("| Callee | Route | Static subtree | Notes |");
  lines.push("|---|---|---:|---|");
  for (const callee of flow.directCallees) {
    lines.push(
      `| \`${callee.address}\` \`${callee.displayName}\` | \`${callee.route}\` | ${callee.reachableFunctionsBelow} | ${bootNote(callee.displayName)} |`,
    );
  }
  lines.push("");
  if (flow.mainLoop) {
    lines.push("## Main Loop Body");
    lines.push("");
    lines.push(`Function: \`${flow.mainLoop.address}\` \`${flow.mainLoop.displayName}\` at \`${flow.mainLoop.path}\``);
    lines.push("");
    lines.push("| # | Phase | Callee | Route | Static subtree | Notes |");
    lines.push("|---:|---|---|---|---:|---|");
    for (const callee of flow.mainLoop.callees) {
      lines.push(
        `| ${callee.index} | ${callee.phase} | \`${callee.address}\` \`${callee.displayName}\` | \`${callee.route}\` | ${callee.reachableFunctionsBelow} | ${callee.note} |`,
      );
    }
    lines.push("");
  }
  lines.push("## Route Counts");
  lines.push("");
  lines.push("| Route | Reachable functions |");
  lines.push("|---|---:|");
  for (const [route, count] of sortedEntries(flow.routeCounts).slice(0, 30)) lines.push(`| \`${route}\` | ${count} |`);
  lines.push("");
  lines.push("## Known Anchor Paths");
  lines.push("");
  lines.push("| Anchor | Route | Shortest static path from start |");
  lines.push("|---|---|---|");
  for (const anchor of flow.knownAnchors.slice(0, 30)) {
    lines.push(
      `| \`${anchor.address}\` \`${anchor.displayName}\` | \`${anchor.route}\` | ${anchor.shortestPath.map((node) => `\`${node.displayName}\``).join(" -> ")} |`,
    );
  }
  lines.push("");
  lines.push("## Indirect Dispatch Sites");
  lines.push("");
  lines.push("| Function | Route | Source |");
  lines.push("|---|---|---|");
  for (const site of flow.indirectCallSites.slice(0, 40)) {
    lines.push(`| \`${site.address}\` \`${site.displayName}\` | \`${site.route}\` | \`${site.path}\` |`);
  }
  lines.push("");
  lines.push("## Static Flow Limits");
  lines.push("");
  lines.push("- This is a name-based static call graph from the Ghidra C export.");
  lines.push("- Function-pointer dispatch tables are a known gap; Challenge flow uses dispatch arrays such as `PTR_FUN_*` and will need table decoding.");
  lines.push("- Data/global anchors are resolved separately in `address-resolution.md`.");
  lines.push("");
  return `${lines.join("\n")}\n`;
}

function renderClassMapMarkdown(map) {
  const lines = [];
  lines.push("# Class Map");
  lines.push("");
  lines.push(`Generated: ${map.generatedAt}`);
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push(`- Classes with C++-style symbols: ${map.summary.classCount}`);
  lines.push(`- Methods: ${map.summary.methodCount}`);
  lines.push(`- Methods statically reachable from \`start\`: ${map.summary.reachableMethodCount}`);
  lines.push(`- Note: ${map.summary.note}`);
  lines.push("");
  lines.push("## Classes");
  lines.push("");
  lines.push("| Class | Methods | Reachable from start |");
  lines.push("|---|---:|---:|");
  for (const cls of map.classes) {
    lines.push(`| \`${cls.className}\` | ${cls.methodCount} | ${cls.methods.filter((method) => method.reachableFromStart).length} |`);
  }
  lines.push("");
  lines.push("## Methods");
  lines.push("");
  lines.push("| Method | Source | Callers | Callees |");
  lines.push("|---|---|---:|---:|");
  for (const cls of map.classes) {
    for (const method of cls.methods) {
      lines.push(
        `| \`${method.address}\` \`${method.originalName}\` | \`${method.path}\` | ${method.callers.length} | ${method.callees.length} |`,
      );
    }
  }
  lines.push("");
  return `${lines.join("\n")}\n`;
}

function renderAddressResolutionMarkdown(resolution) {
  const lines = [];
  lines.push("# Address Resolution");
  lines.push("");
  lines.push(`Generated: ${resolution.generatedAt}`);
  lines.push("");
  lines.push("## Summary");
  lines.push("");
  lines.push(`- Research files scanned: ${resolution.summary.scannedFiles}`);
  lines.push(`- Unique 80xx addresses referenced: ${resolution.summary.totalReferences}`);
  lines.push(`- Exact function starts: ${resolution.summary.exactFunctionStarts} (${resolution.summary.exactFunctionPct})`);
  lines.push(`- Non-function references: ${resolution.summary.nonFunctionReferences}`);
  lines.push("");
  lines.push("| Kind | Count |");
  lines.push("|---|---:|");
  for (const [kind, count] of sortedEntries(resolution.summary.byKind)) lines.push(`| ${kind} | ${count} |`);
  lines.push("");
  lines.push("## Non-Function Anchors");
  lines.push("");
  lines.push("| Address | Kind | Containing function / data file | Sources |");
  lines.push("|---|---|---|---|");
  for (const item of resolution.resolutions.filter((entry) => entry.kind !== "function-start").slice(0, 80)) {
    const target =
      item.functionPath ??
      item.dataFiles.slice(0, 2).map((file) => `\`${file}\``).join("<br>") ??
      "";
    lines.push(
      `| \`${item.address}\` | ${item.kind} | ${target || ""} | ${item.sources.slice(0, 3).map((source) => `\`${source.path}\``).join("<br>")} |`,
    );
  }
  lines.push("");
  lines.push("## Function Starts Referenced By Research");
  lines.push("");
  lines.push("| Address | Function | Organized path | Sources |");
  lines.push("|---|---|---|---|");
  for (const item of resolution.resolutions.filter((entry) => entry.kind === "function-start").slice(0, 80)) {
    lines.push(
      `| \`${item.address}\` | \`${item.displayName}\` | \`${item.functionPath}\` | ${item.sources.slice(0, 3).map((source) => `\`${source.path}\``).join("<br>")} |`,
    );
  }
  lines.push("");
  lines.push("## Usage");
  lines.push("");
  lines.push("- `function-interior` means the address is inside the previous function-start range in the sorted decompile index.");
  lines.push("- `extracted-data-anchor` means the address is represented by a file under `research/decomp/data/`, not by a C function.");
  lines.push("- `data-or-global` means the address appears to be a data/global/table address that still needs a first-class schema or cross-reference entry.");
  lines.push("");
  return `${lines.join("\n")}\n`;
}

function bootNote(name) {
  if (/__init_registers/.test(name)) return "CPU/register bootstrap stub.";
  if (/hardware/.test(name)) return "OS/FPU/cache hardware init.";
  if (/zz_0003340/.test(name)) return "Copies initialized sections and clears BSS-style regions.";
  if (/TRK|debug|pad/i.test(name)) return "Debug / MetroTRK / boot-mode handling.";
  if (/init_user/.test(name)) return "User runtime initialization before game handoff.";
  if (/run_main_game_loop|zz_00527d8/.test(name)) return "Application handoff into the infinite main loop.";
  if (/FUN_802331c4/.test(name)) return "Terminal/runtime tail after user handoff.";
  return "";
}

function mainLoopNote(name) {
  if (/dispatch_pending_io_request/.test(name)) return "Dispatches current pending I/O/load request via `PTR_FUN_802c3818`.";
  if (/dispatch_global_menu_mode/.test(name)) return "Dispatches current menu/game mode via `PTR_FUN_802da780`.";
  if (/zz_002a3e4/.test(name)) return "Pre-loop system initialization.";
  if (/zz_002a638/.test(name)) return "Pre-loop follow-up initialization.";
  if (/zz_002a4b0|zz_002a4d4/.test(name)) return "Frame boundary / render-system handoff candidate.";
  return "";
}

function orderedCallees(fn) {
  const body = readOrganizedBody(fn);
  if (!body) return fn.callees ?? [];
  const out = [];
  const seen = new Set();
  const re = /\b([A-Za-z_][A-Za-z0-9_]*)\s*\(/g;
  let match;
  while ((match = re.exec(body))) {
    const name = match[1];
    const address = callableAliases.get(name);
    if (!address || address === fn.addressKey || seen.has(address)) continue;
    seen.add(address);
    out.push({ address: fmt(address), name });
  }
  return out.length ? out : fn.callees ?? [];
}

function readOrganizedBody(fn) {
  if (!fn?.organized?.path) return "";
  const full = path.join(organizedDir, ...fn.organized.path.split("/"));
  return fs.existsSync(full) ? fs.readFileSync(full, "utf8") : "";
}

function buildCallableAliases() {
  const aliases = new Map();
  for (const fn of functions) {
    for (const name of [
      fn.currentFunctionName,
      fn.symbolMapName,
      fn.inferredName,
      fn.organized?.displayName,
      fn.organized?.originalName,
    ]) {
      addCallableAlias(aliases, name, fn.addressKey);
    }
  }
  return aliases;
}

function addCallableAlias(aliases, name, address) {
  if (typeof name !== "string" || !name) return;
  const candidates = [
    name,
    name.replace(/::/g, "__").replace(/[^A-Za-z0-9_]+/g, "_").replace(/^_+|_+$/g, ""),
  ];
  for (const candidate of candidates) {
    if (/^[A-Za-z_][A-Za-z0-9_]*$/.test(candidate) && !aliases.has(candidate)) aliases.set(candidate, address);
  }
}

function dirnameOrBucket(row) {
  if (!row) return "unknown";
  const slash = row.path.lastIndexOf("/");
  return slash > 0 ? row.path.slice(0, slash) : row.bucket;
}

function displayName(fn) {
  return fn?.organized?.displayName ?? fn?.inferredName ?? fn?.currentFunctionName ?? "(unknown)";
}

function sortedEntries(obj) {
  return Object.entries(obj).sort((a, b) => b[1] - a[1] || a[0].localeCompare(b[0]));
}

function countBy(values, keyFn) {
  const out = {};
  for (const value of values) {
    const key = keyFn(value) || "unknown";
    out[key] = (out[key] ?? 0) + 1;
  }
  return Object.fromEntries(sortedEntries(out));
}

function countMany(values, keyFn) {
  const out = {};
  for (const value of values) {
    for (const key of keyFn(value)) out[key] = (out[key] ?? 0) + 1;
  }
  return Object.fromEntries(sortedEntries(out));
}

function upperBound(sorted, target) {
  let lo = 0;
  let hi = sorted.length;
  while (lo < hi) {
    const mid = (lo + hi) >> 1;
    if (sorted[mid] <= target) lo = mid + 1;
    else hi = mid;
  }
  return lo;
}

function extract80xxAddresses(text) {
  const out = [];
  const re = /(?:0x)?\b(80[0-9a-fA-F]{6})\b/g;
  let match;
  while ((match = re.exec(text))) out.push(match[1].toLowerCase());
  return out;
}

function addRef(refs, address, file, sourceKind) {
  const key = strip0x(address);
  if (!refs.has(key)) refs.set(key, new Map());
  const sourcePath = rel(file);
  const existing = refs.get(key).get(sourcePath) ?? { path: sourcePath, sourceKinds: [] };
  if (!existing.sourceKinds.includes(sourceKind)) existing.sourceKinds.push(sourceKind);
  refs.get(key).set(sourcePath, existing);
}

function isLikelyDataOrGlobal(address) {
  const numeric = parseInt(address, 16);
  return numeric >= 0x802b0040 || numeric >= 0x80300000 || numeric >= 0x80400000;
}

function stripRuntimeMaps(flow) {
  const { parentByAddress: _parentByAddress, ...rest } = flow;
  return rest;
}

function readJson(file) {
  return JSON.parse(fs.readFileSync(file, "utf8"));
}

function writeJson(file, value) {
  fs.writeFileSync(file, `${JSON.stringify(value, null, 2)}\n`);
}

function strip0x(address) {
  return String(address).replace(/^0x/i, "").toLowerCase();
}

function fmt(address) {
  return `0x${strip0x(address)}`;
}

function pct(part, whole) {
  return whole ? `${((part * 100) / whole).toFixed(2)}%` : "0.00%";
}

function rel(file) {
  return path.relative(repoRoot, file).replaceAll("\\", "/");
}
