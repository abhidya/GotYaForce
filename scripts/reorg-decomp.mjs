#!/usr/bin/env node
// Reorganize the flat Ghidra bulk-decompile export (research/decomp/ghidra-export/chunk_*.c)
// into a browsable copied source tree. This is deterministic text processing:
// no LLM involvement, safe to re-run whenever the export/evidence index changes.
//
// Output: research/decomp/organized/
//   classes/<ClassName>/<address>_<method>.c       C++-style mapped methods
//   game/<system>/<topic>/<address>_<name>.c       researched game-code anchors
//   sdk/<subsystem>/<address>_<name>.c             SDK/HSD/libc/GX/etc.
//   engine/shared/<address>_<name>.c               shared engine helpers
//   _map.tsv                                      address/name/path lookup
//   _summary.md                                   route/name-source counts
//   README.md                                     usage notes
//
// File bodies intentionally preserve the original decompiled text. The path,
// filename, and map provide the friendlier browsing names while raw chunk/address
// fidelity remains intact.

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const exportDir = path.join(repoRoot, "research", "decomp", "ghidra-export");
const evidenceFile = path.join(repoRoot, "research", "decomp", "index", "function-evidence-index.json");
const outDir = path.join(repoRoot, "research", "decomp", "organized");

const BUCKET_PATHS = {
  "sdk-hsd": ["sdk", "hsd"],
  "sdk-gx": ["sdk", "gx"],
  "sdk-os": ["sdk", "os"],
  "sdk-audio": ["sdk", "audio"],
  "sdk-math": ["sdk", "math"],
  "sdk-libc": ["sdk", "libc"],
  "engine-shared": ["engine", "shared"],
  "game-combat": ["game", "combat"],
  "game-battle": ["game", "battle"],
  "game-systems": ["game", "systems"],
  "game-modes": ["game", "modes"],
  "game-ui": ["game", "ui"],
  "game-unsorted": ["game", "unsorted"],
};

// name-prefix -> bucket (checked in order, first match wins)
const PREFIX_BUCKETS = [
  [/^HSD_/, "sdk-hsd"],
  [/^(GX|GD)[A-Z_]/, "sdk-gx"],
  [/^(OS|DVD|VI|PAD|SI|EXI|CARD|ARQ?|DSP|IRQ|DB|__OS|SC[A-Z])/, "sdk-os"],
  [/^(AX|AXFX|AI[A-Z_]|Mix|SND|JAX|sndConvert|seqp?_|synth)/i, "sdk-audio"],
  [/^(PSMTX|C_MTX|MTX|PSVEC|VEC|QUAT|C_VEC|MTXQuat)/, "sdk-math"],
  [
    /^(mem(cpy|set|move|cmp)|str[a-z]+|s?printf|vprintf|atoi|atof|ato[lx]|rand|srand|qsort|bsearch|toupper|tolower|is[a-z]+|abs|labs|div|ldiv|calloc|malloc|free|realloc|exit|abort|assert|setjmp|longjmp|errno|_[_a-z])/,
    "sdk-libc",
  ],
  [
    /^(fn_|fabs|sqrtf?|sinf?|cosf?|tanf?|atan2?f?|asinf?|acosf?|powf?|expf?|logf?|floorf?|ceilf?|fmodf?|frexp|ldexp|modff?)/,
    "sdk-libc",
  ],
  [/^gnt4_/, "engine-shared"],
];

// address-band -> bucket for anonymous game code (zz_*/FUN_*). Bands derived from
// systems already confirmed in behavior-notes.md / challenge-flow-evidence.
const ADDRESS_BANDS = [
  [0x80020000, 0x8004a000, "game-combat"],
  [0x8004a000, 0x80060000, "game-battle"],
  [0x80060000, 0x800a0000, "game-systems"],
  [0x80190000, 0x801a0000, "game-modes"],
  [0x801a0000, 0x80230000, "game-ui"],
];

// Evidence topics are stronger navigation hints than broad address bands.
const TOPIC_PATHS = [
  ["front-end-menu", ["game", "ui", "front-end-menu"]],
  ["global-menu-mode", ["game", "modes", "global-menu"]],
  ["challenge-menu-flow", ["game", "modes", "challenge"]],
  ["force-setup", ["game", "battle", "force-setup"]],
  ["battle-initialization", ["game", "battle", "initialization"]],
  ["damage", ["game", "combat", "damage"]],
  ["knockback-targeting", ["game", "combat", "knockback"]],
  ["movement-physics", ["game", "physics", "movement"]],
  ["stage-load-collision", ["game", "stage", "collision"]],
  ["assets-animation", ["game", "assets", "animation"]],
  ["camera", ["game", "camera"]],
  ["audio", ["game", "audio"]],
];

function normalizeAddr(addr) {
  return String(addr).replace(/^0x/i, "").toLowerCase();
}

function isGeneratedName(name) {
  return /^zz_[0-9a-f]+_$/.test(name) || /^FUN_[0-9a-f]+$/i.test(name);
}

function sanitize(name) {
  return String(name)
    .replace(/::/g, "__")
    .replace(/[<>{}[\](),*&\s]+/g, "_")
    .replace(/[^A-Za-z0-9_.-]/g, "_")
    .replace(/_+/g, "_")
    .replace(/^_+|_+$/g, "")
    .slice(0, 100);
}

function parseClassSymbol(name) {
  // Some Ghidra/map names are truncated at the first tab/comma and keep only an
  // opening paren, e.g. `cCameraManager::HasCamera(cBaseCamera`. Treat those as
  // class symbols too; the address in the filename still guarantees uniqueness.
  const m = /^([^:()\s]+)::([^(]+)(?:\((.*)\)?)?$/.exec(name);
  if (!m) return null;
  return {
    className: sanitize(m[1]),
    methodName: sanitize(m[2].trim()) || "method",
    params: m[3] ?? "",
  };
}

function methodStem(classInfo) {
  const params = classInfo.params.trim();
  if (!params || params === "void") return classInfo.methodName;
  return `${classInfo.methodName}__${sanitize(params)}`;
}

function bucketFor(name, addr) {
  // The community map wraps borrowed GNT4/SDK symbols as `gnt4-<RealSymbol>-suffix`;
  // unwrap so the real symbol prefix drives classification.
  let sym = name;
  if (sym.startsWith("gnt4-")) sym = sym.slice(5).split("-")[0];
  if (/^(HSD_|_HSD|JObj|cbF)/.test(sym)) return "sdk-hsd";
  if (/^(PPC|__PPC)/.test(sym)) return "sdk-os";
  for (const [re, bucket] of PREFIX_BUCKETS) if (re.test(sym)) return bucket;
  if (sym !== name) return "engine-shared";
  if (/^TRK/.test(sym)) return "sdk-os";
  for (const [lo, hi, bucket] of ADDRESS_BANDS) if (addr >= lo && addr < hi) return bucket;
  return "game-unsorted";
}

function loadEvidenceByAddress() {
  if (!fs.existsSync(evidenceFile)) return new Map();
  const data = JSON.parse(fs.readFileSync(evidenceFile, "utf8"));
  const byAddr = new Map();
  for (const fn of data.functions ?? []) {
    byAddr.set(normalizeAddr(fn.address), fn);
  }
  for (const anchor of data.knownAnchors ?? []) {
    const addr = normalizeAddr(anchor.address);
    byAddr.set(addr, { ...(byAddr.get(addr) ?? {}), ...anchor, knownAnchor: true });
  }
  return byAddr;
}

function gfAliasFrom(body) {
  return /GF_ALIAS:\s*([A-Za-z0-9_]+)/.exec(body)?.[1] ?? "";
}

function displayNameFor(rec, evidence, gfAlias) {
  const inferred = evidence?.inferredName;
  if (gfAlias) return { displayName: gfAlias, source: "GF_ALIAS" };
  if (inferred && !isGeneratedName(inferred) && inferred !== rec.name) {
    return { displayName: inferred, source: evidence?.knownAnchor ? "known-anchor" : "evidence-index" };
  }
  if (!isGeneratedName(rec.name)) return { displayName: rec.name, source: "symbol" };
  if (inferred && !isGeneratedName(inferred)) return { displayName: inferred, source: "evidence-index" };
  return { displayName: rec.name, source: "generated" };
}

function routeFor(rec, evidence) {
  const classInfo = parseClassSymbol(rec.name);
  if (classInfo) {
    return {
      bucket: "class-method",
      pathParts: ["classes", classInfo.className],
      classInfo,
      routeSource: "class-symbol",
    };
  }

  const topics = evidence?.topics ?? [];
  for (const [topic, pathParts] of TOPIC_PATHS) {
    if (topics.includes(topic)) {
      return {
        bucket: topic,
        pathParts,
        classInfo: null,
        routeSource: "evidence-topic",
      };
    }
  }

  const bucket = bucketFor(rec.name, parseInt(rec.addr, 16));
  return {
    bucket,
    pathParts: BUCKET_PATHS[bucket] ?? ["game", "unsorted"],
    classInfo: null,
    routeSource: "symbol-or-address",
  };
}

function parseRecords() {
  const headerRe = /^\/\/ ==== ([0-9a-f]{8})  (.+?) ====\s*$/;
  const records = [];
  for (const file of fs.readdirSync(exportDir).filter((f) => /^chunk_\d+\.c$/.test(f)).sort()) {
    const lines = fs.readFileSync(path.join(exportDir, file), "utf8").split(/\r?\n/);
    let cur = null;
    for (const line of lines) {
      const m = headerRe.exec(line);
      if (m) {
        if (cur) records.push(cur);
        cur = { addr: m[1], name: m[2].trim(), lines: [line], srcChunk: file };
      } else if (cur) {
        cur.lines.push(line);
      }
    }
    if (cur) records.push(cur);
  }
  return records;
}

const evidenceByAddr = loadEvidenceByAddress();
const records = parseRecords();

fs.rmSync(outDir, { recursive: true, force: true });
fs.mkdirSync(outDir, { recursive: true });

const mapRows = [
  [
    "address",
    "original_name",
    "display_name",
    "name_source",
    "class",
    "bucket",
    "route_source",
    "path",
    "src_chunk",
  ].join("\t"),
];
const routeCounts = new Map();
const nameSourceCounts = new Map();
const classCounts = new Map();

for (const rec of records) {
  const body = rec.lines.join("\n").replace(/\n+$/, "") + "\n";
  const evidence = evidenceByAddr.get(normalizeAddr(rec.addr));
  const gfAlias = gfAliasFrom(body);
  const { displayName, source: nameSource } = displayNameFor(rec, evidence, gfAlias);
  const route = routeFor(rec, evidence);
  const stem = route.classInfo ? methodStem(route.classInfo) : displayName;
  const fileName = `${rec.addr}_${sanitize(stem) || "function"}.c`;
  const dir = path.join(outDir, ...route.pathParts);
  fs.mkdirSync(dir, { recursive: true });
  fs.writeFileSync(path.join(dir, fileName), body);

  const relPath = path.join(...route.pathParts, fileName).replaceAll(path.sep, "/");
  const className = route.classInfo?.className ?? "";
  mapRows.push(
    [
      rec.addr,
      rec.name,
      displayName,
      nameSource,
      className,
      route.bucket,
      route.routeSource,
      relPath,
      rec.srcChunk,
    ].join("\t"),
  );

  const routeKey = route.pathParts.join("/");
  routeCounts.set(routeKey, (routeCounts.get(routeKey) ?? 0) + 1);
  nameSourceCounts.set(nameSource, (nameSourceCounts.get(nameSource) ?? 0) + 1);
  if (className) classCounts.set(className, (classCounts.get(className) ?? 0) + 1);
}

fs.writeFileSync(path.join(outDir, "_map.tsv"), mapRows.join("\n") + "\n");

const summary = [
  "# Organized decomp tree",
  "",
  `Generated by \`scripts/reorg-decomp.mjs\` from ${records.length} functions in \`research/decomp/ghidra-export/\`.`,
  "This is copied, derived browsing output. Re-run the script after any Ghidra re-export or evidence-index rebuild; do not hand-edit files here.",
  "Function bodies preserve the raw decompiler text. Friendlier names live in paths, filenames, and `_map.tsv`.",
  "",
  "## Route counts",
  "",
  "| route | functions |",
  "|---|---:|",
  ...[...routeCounts.entries()].sort((a, b) => b[1] - a[1]).map(([route, n]) => `| ${route} | ${n} |`),
  "",
  "## Name sources",
  "",
  "| source | functions |",
  "|---|---:|",
  ...[...nameSourceCounts.entries()].sort((a, b) => b[1] - a[1]).map(([source, n]) => `| ${source} | ${n} |`),
  "",
  "## Classes",
  "",
  "| class | methods |",
  "|---|---:|",
  ...[...classCounts.entries()].sort((a, b) => a[0].localeCompare(b[0])).map(([cls, n]) => `| ${cls} | ${n} |`),
  "",
].join("\n");
fs.writeFileSync(path.join(outDir, "_summary.md"), summary);

const readme = [
  "# Organized Ghidra Decompile Copy",
  "",
  "This directory is generated from `research/decomp/ghidra-export/` by `scripts/reorg-decomp.mjs`.",
  "",
  "- Raw chunks remain the source of truth.",
  "- Each `.c` file here is one copied decompiled function body.",
  "- Paths and filenames use the best available reviewed name: `GF_ALIAS`, evidence-index inferred name, class symbol, symbol-map name, then generated Ghidra name.",
  "- `_map.tsv` links every organized file back to its address, raw chunk, original symbol, display name, and route.",
  "- `classes/<ClassName>/` groups C++-style symbols such as `cTeam::GetPlayer(int)`.",
  "",
  "Regenerate with:",
  "",
  "```bash",
  "node scripts/reorg-decomp.mjs",
  "```",
  "",
].join("\n");
fs.writeFileSync(path.join(outDir, "README.md"), readme);

console.log(`wrote ${records.length} functions into ${routeCounts.size} routes under research/decomp/organized/`);
for (const [route, n] of [...routeCounts.entries()].sort((a, b) => b[1] - a[1])) {
  console.log(`  ${route}: ${n}`);
}
