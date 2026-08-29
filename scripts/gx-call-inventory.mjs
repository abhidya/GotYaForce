#!/usr/bin/env node
// ============================================================================
// gx-call-inventory.mjs — MEASURE the GX call surface this game actually has.
//
// The HLE host's GX work is defined by what the ROM calls, not by what the
// GameCube SDK offers. This script measures that from the decompiled corpus
// (research/decomp/ghidra-export) and emits two artifacts:
//
//   research/decomp/data/gx-call-inventory.json        (the measurement)
//   packages/rom-runtime/src/gx/inventory.generated.ts (the same, as data the
//                                                       runtime imports)
//
// Method
// ------
// Every function body in the export is delimited by a header comment
//     // ==== 8022bce8  gnt4-GXSetProjection-bl ====
// so each call site can be attributed to its ENCLOSING function. A call is
// classified by that enclosing function:
//
//   * "game"         — the caller is ROM game code (FUN_*, zz_*, named
//                      gameplay symbols). These are the calls that will cross
//                      the SDK seam out of a composed module, because the
//                      whole gnt4_* family is excluded from porting by design
//                      (docs/playable-port-design.md V2 F2: 996 sdk_prefix
//                      functions, "never ported").
//   * "sdk-internal" — the caller is itself a gnt4_* SDK/HSD function. Those
//                      calls happen INSIDE the host's own implementation of
//                      the SDK and never cross the seam, so they do not
//                      define host work; they are reported for context only.
//
// The RANKING the host prioritizes by is `gameCalls` — the real ROM->host
// GX boundary. Everything here is a static call-site count: it is a measure
// of how many places in the ROM call an entry point, NOT of how often it
// executes at runtime. Dynamic frequency needs a Dolphin trace and this file
// must never be read as if it had one.
//
// Re-run:  node scripts/gx-call-inventory.mjs
// ============================================================================

import fs from "node:fs";
import path from "node:path";
import process from "node:process";
import { fileURLToPath } from "node:url";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const exportDir = path.join(root, "research", "decomp", "ghidra-export");
const jsonOut = path.join(root, "research", "decomp", "data", "gx-call-inventory.json");
const tsOut = path.join(root, "packages", "rom-runtime", "src", "gx", "inventory.generated.ts");

const HEADER = /^\/\/\s*====\s*([0-9a-fA-F]{8})\s+(\S+)\s*====/;
// gnt4_GX* and gnt4___GX* (the SDK's internal double-underscore entry points).
const CALL = /\b(gnt4__{0,2}GX[A-Za-z0-9_]*)\s*\(/g;

/** Index name (`gnt4-GXFoo-bl`) -> C name (`gnt4_GXFoo_bl`). */
const toCName = (indexName) => indexName.replace(/-/g, "_");

function readSymbolAddresses() {
  const byName = new Map();
  const lines = fs.readFileSync(path.join(exportDir, "_index.tsv"), "utf8").split(/\r?\n/);
  for (const line of lines.slice(1)) {
    const [addr, name] = line.split("\t");
    if (!addr || !name || !name.includes("GX")) continue;
    byName.set(toCName(name), addr.toLowerCase());
  }
  return byName;
}

function measure() {
  const addresses = readSymbolAddresses();
  const game = new Map();
  const sdk = new Map();
  const gameCallers = new Map();

  for (const file of fs.readdirSync(exportDir).sort()) {
    if (!file.endsWith(".c")) continue;
    let enclosing = null;
    const text = fs.readFileSync(path.join(exportDir, file), "utf8");
    for (const line of text.split(/\r?\n/)) {
      const header = HEADER.exec(line);
      if (header) {
        enclosing = header[2];
        continue;
      }
      CALL.lastIndex = 0;
      let match;
      while ((match = CALL.exec(line)) !== null) {
        const symbol = match[1];
        // The symbol's own definition line is not a call site.
        if (enclosing && toCName(enclosing) === symbol) continue;
        if (enclosing && enclosing.startsWith("gnt4-")) {
          sdk.set(symbol, (sdk.get(symbol) ?? 0) + 1);
        } else {
          game.set(symbol, (game.get(symbol) ?? 0) + 1);
          if (!gameCallers.has(symbol)) gameCallers.set(symbol, new Set());
          gameCallers.get(symbol).add(enclosing ?? "<file scope>");
        }
      }
    }
  }

  const symbols = new Set([...game.keys(), ...sdk.keys()]);
  const entries = [...symbols]
    .map((symbol) => ({
      symbol,
      romAddr: addresses.get(symbol) ?? null,
      gameCalls: game.get(symbol) ?? 0,
      sdkInternalCalls: sdk.get(symbol) ?? 0,
      distinctGameCallers: gameCallers.get(symbol)?.size ?? 0,
    }))
    .sort((a, b) => b.gameCalls - a.gameCalls || b.sdkInternalCalls - a.sdkInternalCalls || a.symbol.localeCompare(b.symbol));

  const called = new Set(symbols);
  const neverCalled = [...addresses.keys()].filter((s) => !called.has(s)).sort();

  return {
    generatedBy: "scripts/gx-call-inventory.mjs",
    corpus: "research/decomp/ghidra-export",
    method:
      "static call-site counts attributed to the enclosing function; 'game' = caller is ROM game code, " +
      "'sdk-internal' = caller is itself a gnt4_* SDK/HSD function. NOT a runtime frequency measurement.",
    totals: {
      gxSymbolsInDol: addresses.size,
      gxSymbolsCalledAnywhere: symbols.size,
      gxSymbolsCalledByGameCode: entries.filter((e) => e.gameCalls > 0).length,
      gameCallSites: [...game.values()].reduce((a, b) => a + b, 0),
      sdkInternalCallSites: [...sdk.values()].reduce((a, b) => a + b, 0),
    },
    entries,
    neverCalled,
  };
}

function emitTs(inventory) {
  const rows = inventory.entries
    .filter((e) => e.gameCalls > 0)
    .map(
      (e) =>
        `  { symbol: ${JSON.stringify(e.symbol)}, romAddr: ${
          e.romAddr === null ? "null" : `0x${e.romAddr}`
        }, gameCalls: ${e.gameCalls}, sdkInternalCalls: ${e.sdkInternalCalls}, distinctGameCallers: ${e.distinctGameCallers} },`,
    )
    .join("\n");

  return `// =============================================================================
// inventory.generated.ts — GENERATED by scripts/gx-call-inventory.mjs.
// DO NOT EDIT BY HAND; re-run the script instead.
//
// The measured GX call surface of Gotcha Force: every GX entry point that ROM
// GAME code calls, ranked by static call-site count. This is the ranked list
// the HLE host's GX work is prioritized by, and the denominator its coverage
// percentage is computed against — so the coverage number is derived from a
// measurement rather than asserted.
//
// HONESTY NOTE (repeated from the generator): these are STATIC call-site
// counts — how many places in the ROM call an entry point, not how often it
// executes. A per-frame frequency ranking requires a Dolphin trace and does
// not exist yet.
//
// Corpus: ${inventory.corpus}
// GX symbols in the DOL: ${inventory.totals.gxSymbolsInDol}
// Called by game code:   ${inventory.totals.gxSymbolsCalledByGameCode}
// Game call sites:       ${inventory.totals.gameCallSites}
// =============================================================================

export interface GxInventoryEntry {
  /** The C symbol as it appears in the corpus (and as a wasm import name). */
  readonly symbol: string;
  /** The entry point's real GameCube address in this game's DOL. */
  readonly romAddr: number | null;
  /** Static call sites in ROM game code — the ranking key. */
  readonly gameCalls: number;
  /** Static call sites inside other gnt4_* SDK/HSD functions (context only). */
  readonly sdkInternalCalls: number;
  /** Distinct ROM functions that call it. */
  readonly distinctGameCallers: number;
}

/** GX entry points called by ROM game code, ranked by static call sites. */
export const GX_CALL_INVENTORY: readonly GxInventoryEntry[] = [
${rows}
];

/** Total static game-code call sites across the whole ranked surface. */
export const GX_GAME_CALL_SITES = ${inventory.totals.gameCallSites};

/** Look one entry point up by symbol. */
export function gxInventoryEntry(symbol: string): GxInventoryEntry | undefined {
  return GX_CALL_INVENTORY.find((e) => e.symbol === symbol);
}

/**
 * Coverage of the ranked surface, by BOTH measures that matter:
 * how many distinct entry points are implemented, and what share of the
 * ROM's static call sites they account for (weighted coverage). The second
 * is the honest headline: implementing the top ten entry points covers far
 * more of the ROM's actual GX usage than 10/76 suggests.
 */
export function gxCoverage(implemented: Iterable<string>): {
  implementedSymbols: number;
  totalSymbols: number;
  symbolPct: number;
  coveredCallSites: number;
  totalCallSites: number;
  callSitePct: number;
} {
  const set = new Set(implemented);
  const covered = GX_CALL_INVENTORY.filter((e) => set.has(e.symbol));
  const coveredCallSites = covered.reduce((sum, e) => sum + e.gameCalls, 0);
  return {
    implementedSymbols: covered.length,
    totalSymbols: GX_CALL_INVENTORY.length,
    symbolPct: Math.round((covered.length / GX_CALL_INVENTORY.length) * 1000) / 10,
    coveredCallSites,
    totalCallSites: GX_GAME_CALL_SITES,
    callSitePct: Math.round((coveredCallSites / GX_GAME_CALL_SITES) * 1000) / 10,
  };
}
`;
}

const inventory = measure();
fs.mkdirSync(path.dirname(jsonOut), { recursive: true });
fs.writeFileSync(jsonOut, `${JSON.stringify(inventory, null, 2)}\n`);
fs.mkdirSync(path.dirname(tsOut), { recursive: true });
fs.writeFileSync(tsOut, emitTs(inventory));

process.stdout.write(
  `GX call inventory: ${inventory.totals.gxSymbolsCalledByGameCode} entry points called by game code across ` +
    `${inventory.totals.gameCallSites} static call sites ` +
    `(${inventory.totals.gxSymbolsInDol} GX symbols in the DOL; ${inventory.totals.sdkInternalCallSites} SDK-internal call sites).\n` +
    `  -> ${path.relative(root, jsonOut)}\n  -> ${path.relative(root, tsOut)}\n`,
);
