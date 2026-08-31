#!/usr/bin/env node
// ============================================================================
// hle-call-inventory.mjs — MEASURE the AUDIO and DVD call surfaces this game
// actually has, by the same method scripts/gx-call-inventory.mjs uses for GX.
//
// The HLE host's work is defined by what the ROM calls, not by what the
// GameCube SDK offers. This script walks research/decomp/ghidra-export and
// emits, per family:
//
//   research/decomp/data/<family>-call-inventory.json          (the measurement)
//   packages/rom-runtime/src/<family>/inventory.generated.ts   (the same, as
//                                                               data the
//                                                               runtime imports)
//
// Method — CALL SITES
// -------------------
// Every function body in the export is delimited by a header comment
//     // ==== 8022bce8  gnt4-GXSetProjection-bl ====
// so each call site is attributed to its ENCLOSING function, and classified:
//
//   * "game"         — the caller is ROM game code (FUN_*, zz_*, named
//                      gameplay symbols). These calls cross the SDK seam out
//                      of a composed module.
//   * "sdk-internal" — the caller is itself a gnt4_* SDK/HSD function. Those
//                      calls happen INSIDE the host's own implementation and
//                      never cross the seam; reported for context only.
//
// Each entry also carries a SEAM class, which GX did not need because the
// whole GX API is gnt4_*-prefixed and therefore excluded from porting:
//
//   * "bridged"   — the symbol is gnt4_*-prefixed, so design V2 F2 excludes it
//                   from porting and every call to it is an out-of-window call
//                   that crosses the H2 bridge and must be serviced by a host
//                   adapter.
//   * "in-window" — the symbol is NOT gnt4_*-prefixed, so it is ordinary ROM
//                   code that the port compiles into the module. A call to it
//                   does NOT cross the seam. It appears in this inventory only
//                   because its BODY reaches hardware through MMIO, which is a
//                   seam of a different shape (see below).
//
// Method — MMIO
// -------------
// The audio surface is not a pure call surface. The AI (audio interface), AR
// (ARAM) and DSP libraries are compiled into the ROM window and talk to the
// hardware by loading and storing memory-mapped registers, which the
// decompiler renders as `DAT_ccXXXXXX`. A store to such an address is out of
// bounds in the composed module's linear memory and traps — exactly the
// write-gather-pipe situation docs/gx-hle-host.md §3 describes. So this script
// also counts, per hardware register, how many times the corpus reads it and
// how many times it writes it, and which functions do so.
//
// HONESTY NOTE: every number here is a STATIC count — how many places in the
// ROM do the thing — NOT how often it executes. A per-frame frequency ranking
// needs a Dolphin trace and does not exist. Nothing may read this file as if
// it had one.
//
// Re-run:  node scripts/hle-call-inventory.mjs
// ============================================================================

import fs from "node:fs";
import path from "node:path";
import process from "node:process";
import { fileURLToPath } from "node:url";

const root = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const exportDir = path.join(root, "research", "decomp", "ghidra-export");

const HEADER = /^\/\/\s*====\s*([0-9a-fA-F]{8})\s+(\S+)\s*====/;
const CALL = /\b([A-Za-z_][A-Za-z0-9_]*)\s*\(/g;
/** `DAT_cc006c00`, `_DAT_cc005030`, and the sub-field forms Ghidra emits. */
const MMIO = /\b_?DAT_(cc[0-9a-f]{6})\b/g;

/** Index name (`gnt4-DVDOpen-bl`) -> C name (`gnt4_DVDOpen_bl`). */
const toCName = (indexName) => indexName.replace(/-/g, "_");

// ============================================================================
// Families
// ============================================================================

/**
 * A family is defined by (a) which symbols belong to it and (b) which hardware
 * register windows belong to it. Both are stated here rather than discovered,
 * because "which registers are the audio registers" is a fact about the
 * GameCube, not about this ROM — the ROM only tells us which of them it uses.
 */
const FAMILIES = [
  {
    id: "dvd",
    title: "DVD / disc file access",
    tsDir: ["packages", "rom-runtime", "src", "dvd"],
    constPrefix: "DVD",
    /** [SDK] The DVD library's public and internal entry points. */
    symbol: (name) => /^(gnt4_)?_{0,2}(DVD|HSD_DVD)[A-Za-z0-9_]*$/.test(name),
    /** [SDK] DI (disc interface) registers, 0xCC006000..0xCC00603F. */
    mmioWindows: [{ name: "DI", lo: 0xcc006000, hi: 0xcc00603f }],
  },
  {
    id: "audio",
    title: "Audio (AI / AR / ARQ / DSP / OS audio system)",
    tsDir: ["packages", "rom-runtime", "src", "audio"],
    constPrefix: "AUDIO",
    symbol: (name) =>
      // AI / AR / ARQ / DSP library entry points, prefixed or not.
      /^(gnt4_)?_{0,2}(AI|AR|ARQ|DSP)[A-Za-z0-9_]*$/.test(name) ||
      // The OS audio-system and sound-mode calls, which are gnt4_*-prefixed.
      /^gnt4__{0,2}OS(Init|Stop)AudioSystem_bl$/.test(name) ||
      /^gnt4_OS(Get|Set)SoundMode_bl$/.test(name),
    mmioWindows: [
      /** [SDK] DSP interface: mailboxes, CSR, ARAM DMA, AI DMA. */
      { name: "DSP", lo: 0xcc005000, hi: 0xcc00503f },
      /** [SDK] AI interface: AICR, AIVR, AISCNT, AIIT. */
      { name: "AI", lo: 0xcc006c00, hi: 0xcc006c0f },
    ],
  },
];

// ============================================================================
// Measurement
// ============================================================================

function readSymbolAddresses() {
  const byName = new Map();
  const lines = fs.readFileSync(path.join(exportDir, "_index.tsv"), "utf8").split(/\r?\n/);
  for (const line of lines.slice(1)) {
    const [addr, name] = line.split("\t");
    if (!addr || !name) continue;
    byName.set(toCName(name), addr.toLowerCase());
  }
  return byName;
}

/**
 * Is this line a WRITE to `token`? Ghidra renders a register store as the
 * token appearing on the left of a single `=`. Comparisons (`==`, `!=`, `<=`,
 * `>=`) and the token appearing only to the right are reads.
 */
function isWrite(line, token) {
  const idx = line.indexOf(token);
  if (idx < 0) return false;
  // Everything after the token, up to the first `;` — a store looks like
  // `DAT_cc006c00 = expr;` possibly with a `._0_2_`-style field suffix.
  const after = line.slice(idx + token.length);
  const m = /^(\.[_A-Za-z0-9]+)?\s*(=)([^=]|$)/.exec(after);
  return m !== null;
}

function measure(family, addresses) {
  const game = new Map();
  const sdk = new Map();
  const gameCallers = new Map();
  /** hex register address -> { reads, writes, functions:Set } */
  const mmio = new Map();
  const inWindow = (addr) => family.mmioWindows.find((w) => addr >= w.lo && addr <= w.hi) ?? null;

  for (const file of fs.readdirSync(exportDir).sort()) {
    if (!file.endsWith(".c")) continue;
    let enclosing = null;
    let enclosingAddr = null;
    const text = fs.readFileSync(path.join(exportDir, file), "utf8");
    for (const line of text.split(/\r?\n/)) {
      const header = HEADER.exec(line);
      if (header) {
        enclosingAddr = header[1];
        enclosing = header[2];
        continue;
      }

      CALL.lastIndex = 0;
      let match;
      while ((match = CALL.exec(line)) !== null) {
        const symbol = match[1];
        if (!family.symbol(symbol)) continue;
        // A symbol's own definition line is not a call site.
        if (enclosing && toCName(enclosing) === symbol) continue;
        if (enclosing && enclosing.startsWith("gnt4-")) {
          sdk.set(symbol, (sdk.get(symbol) ?? 0) + 1);
        } else {
          game.set(symbol, (game.get(symbol) ?? 0) + 1);
          if (!gameCallers.has(symbol)) gameCallers.set(symbol, new Set());
          gameCallers.get(symbol).add(enclosing ?? "<file scope>");
        }
      }

      MMIO.lastIndex = 0;
      const seenOnLine = new Set();
      while ((match = MMIO.exec(line)) !== null) {
        const addr = Number.parseInt(match[1], 16);
        const window = inWindow(addr);
        if (!window) continue;
        const key = match[1];
        if (!mmio.has(key)) {
          mmio.set(key, { register: `0x${key}`, window: window.name, reads: 0, writes: 0, functions: new Set() });
        }
        const rec = mmio.get(key);
        rec.functions.add(`${enclosingAddr ?? "????????"} ${enclosing ?? "<file scope>"}`);
        // One line may mention the same register twice (`x = DAT; DAT = y;`);
        // classify the line once as write-if-any-write, else read.
        if (!seenOnLine.has(key)) {
          seenOnLine.add(key);
          if (isWrite(line, match[0])) rec.writes += 1;
          else rec.reads += 1;
        }
      }
    }
  }

  const symbols = new Set([...game.keys(), ...sdk.keys()]);
  const entries = [...symbols]
    .map((symbol) => ({
      symbol,
      romAddr: addresses.get(symbol) ?? null,
      seam: symbol.startsWith("gnt4_") ? "bridged" : "in-window",
      gameCalls: game.get(symbol) ?? 0,
      sdkInternalCalls: sdk.get(symbol) ?? 0,
      distinctGameCallers: gameCallers.get(symbol)?.size ?? 0,
    }))
    .sort(
      (a, b) =>
        b.gameCalls - a.gameCalls ||
        b.sdkInternalCalls - a.sdkInternalCalls ||
        a.symbol.localeCompare(b.symbol),
    );

  const registers = [...mmio.values()]
    .map((r) => ({
      register: r.register,
      window: r.window,
      reads: r.reads,
      writes: r.writes,
      total: r.reads + r.writes,
      functions: [...r.functions].sort(),
    }))
    .sort((a, b) => b.total - a.total || a.register.localeCompare(b.register));

  const bridged = entries.filter((e) => e.seam === "bridged");
  const inWindowEntries = entries.filter((e) => e.seam === "in-window");

  return {
    generatedBy: "scripts/hle-call-inventory.mjs",
    family: family.id,
    title: family.title,
    corpus: "research/decomp/ghidra-export",
    method:
      "static call-site counts attributed to the enclosing function; 'game' = caller is ROM game code, " +
      "'sdk-internal' = caller is itself a gnt4_* SDK/HSD function. MMIO counts are static register " +
      "mentions classified read/write by whether the register appears on the left of an assignment. " +
      "NOT a runtime frequency measurement.",
    totals: {
      symbolsInDol: [...addresses.keys()].filter(family.symbol).length,
      symbolsCalledAnywhere: symbols.size,
      symbolsCalledByGameCode: entries.filter((e) => e.gameCalls > 0).length,
      gameCallSites: [...game.values()].reduce((a, b) => a + b, 0),
      sdkInternalCallSites: [...sdk.values()].reduce((a, b) => a + b, 0),
      bridgedSymbolsCalledByGameCode: bridged.filter((e) => e.gameCalls > 0).length,
      bridgedGameCallSites: bridged.reduce((a, b) => a + b.gameCalls, 0),
      inWindowSymbolsCalledByGameCode: inWindowEntries.filter((e) => e.gameCalls > 0).length,
      inWindowGameCallSites: inWindowEntries.reduce((a, b) => a + b.gameCalls, 0),
      mmioRegisters: registers.length,
      mmioReads: registers.reduce((a, b) => a + b.reads, 0),
      mmioWrites: registers.reduce((a, b) => a + b.writes, 0),
    },
    entries,
    registers,
    neverCalled: [...addresses.keys()]
      .filter((s) => family.symbol(s) && !symbols.has(s))
      .sort(),
  };
}

// ============================================================================
// Emit
// ============================================================================

function emitTs(inv, family) {
  const P = family.constPrefix;
  const bridgedRows = inv.entries
    .filter((e) => e.gameCalls > 0)
    .map(
      (e) =>
        `  { symbol: ${JSON.stringify(e.symbol)}, romAddr: ${
          e.romAddr === null ? "null" : `0x${e.romAddr}`
        }, seam: ${JSON.stringify(e.seam)}, gameCalls: ${e.gameCalls}, sdkInternalCalls: ${
          e.sdkInternalCalls
        }, distinctGameCallers: ${e.distinctGameCallers} },`,
    )
    .join("\n");

  const regRows = inv.registers
    .map(
      (r) =>
        `  { register: ${r.register}, window: ${JSON.stringify(r.window)}, reads: ${r.reads}, writes: ${
          r.writes
        }, functions: ${r.functions.length} },`,
    )
    .join("\n");

  return `// =============================================================================
// inventory.generated.ts — GENERATED by scripts/hle-call-inventory.mjs.
// DO NOT EDIT BY HAND; re-run the script instead.
//
// The measured ${inv.title} surface of Gotcha Force: every entry point in this
// family that ROM GAME code calls, ranked by static call-site count, plus every
// hardware register in this family's MMIO windows that the corpus touches.
// This is the ranked list the HLE host's work is prioritized by, and the
// denominator its coverage percentage is computed against — so the coverage
// number is DERIVED from a measurement rather than asserted.
//
// SEAM CLASS matters here in a way it did not for GX:
//   "bridged"   — gnt4_*-prefixed, excluded from porting (design V2 F2), so
//                 every call crosses the H2 bridge and needs a host adapter.
//   "in-window" — ordinary ROM code the port compiles into the module. Calls
//                 to it do NOT cross the seam; it is listed because its body
//                 reaches hardware through the MMIO registers below.
//
// HONESTY NOTE (repeated from the generator): these are STATIC counts — how
// many PLACES in the ROM do the thing, not how often it executes. A per-frame
// frequency ranking requires a Dolphin trace and does not exist yet.
//
// Corpus: ${inv.corpus}
// Symbols in the DOL:            ${inv.totals.symbolsInDol}
// Called by game code:           ${inv.totals.symbolsCalledByGameCode}
// Game call sites:               ${inv.totals.gameCallSites}
//   of which bridged (seam):     ${inv.totals.bridgedGameCallSites}
//   of which in-window (no seam):${inv.totals.inWindowGameCallSites}
// MMIO registers touched:        ${inv.totals.mmioRegisters} (${inv.totals.mmioReads} reads, ${inv.totals.mmioWrites} writes)
// =============================================================================

export interface HleInventoryEntry {
  /** The C symbol as it appears in the corpus (and as a wasm import name). */
  readonly symbol: string;
  /** The entry point's real GameCube address in this game's DOL. */
  readonly romAddr: number | null;
  /** Whether a call to it crosses the SDK seam at all. */
  readonly seam: "bridged" | "in-window";
  /** Static call sites in ROM game code — the ranking key. */
  readonly gameCalls: number;
  /** Static call sites inside other gnt4_* SDK/HSD functions (context only). */
  readonly sdkInternalCalls: number;
  /** Distinct ROM functions that call it. */
  readonly distinctGameCallers: number;
}

export interface HleMmioEntry {
  /** The memory-mapped register address. */
  readonly register: number;
  /** Which hardware block it belongs to. */
  readonly window: string;
  /** Static lines that read it. */
  readonly reads: number;
  /** Static lines that write it. */
  readonly writes: number;
  /** Distinct ROM functions that touch it. */
  readonly functions: number;
}

/** ${inv.title} entry points called by ROM game code, ranked by static call sites. */
export const ${P}_CALL_INVENTORY: readonly HleInventoryEntry[] = [
${bridgedRows}
];

/** Hardware registers in this family's MMIO windows that the corpus touches. */
export const ${P}_MMIO_INVENTORY: readonly HleMmioEntry[] = [
${regRows}
];

/** Total static game-code call sites across the whole ranked surface.
 *  Widened to \`number\` deliberately: a literal type here would make the
 *  divide-by-zero guard below a compile error rather than a guard. */
export const ${P}_GAME_CALL_SITES: number = ${inv.totals.gameCallSites};

/** Static game-code call sites that actually CROSS the seam (gnt4_* callees). */
export const ${P}_BRIDGED_GAME_CALL_SITES: number = ${inv.totals.bridgedGameCallSites};

/** Look one entry point up by symbol. */
export function ${family.id}InventoryEntry(symbol: string): HleInventoryEntry | undefined {
  return ${P}_CALL_INVENTORY.find((e) => e.symbol === symbol);
}

/**
 * Coverage of the ranked surface, by BOTH measures that matter: how many
 * distinct entry points are implemented, and what share of the ROM's static
 * call sites they account for (weighted coverage). Reporting only the first
 * understates a steep distribution; reporting only the second hides a long
 * unimplemented tail. The host reports both, always together.
 */
export function ${family.id}Coverage(implemented: Iterable<string>): {
  implementedSymbols: number;
  totalSymbols: number;
  symbolPct: number;
  coveredCallSites: number;
  totalCallSites: number;
  callSitePct: number;
} {
  const set = new Set(implemented);
  const covered = ${P}_CALL_INVENTORY.filter((e) => set.has(e.symbol));
  const coveredCallSites = covered.reduce((sum, e) => sum + e.gameCalls, 0);
  const totalSymbols = ${P}_CALL_INVENTORY.length;
  return {
    implementedSymbols: covered.length,
    totalSymbols,
    symbolPct: totalSymbols === 0 ? 0 : Math.round((covered.length / totalSymbols) * 1000) / 10,
    coveredCallSites,
    totalCallSites: ${P}_GAME_CALL_SITES,
    callSitePct:
      ${P}_GAME_CALL_SITES === 0 ? 0 : Math.round((coveredCallSites / ${P}_GAME_CALL_SITES) * 1000) / 10,
  };
}
`;
}

// ============================================================================
// Main
// ============================================================================

const addresses = readSymbolAddresses();
const lines = [];
for (const family of FAMILIES) {
  const inv = measure(family, addresses);
  const jsonOut = path.join(root, "research", "decomp", "data", `${family.id}-call-inventory.json`);
  const tsOut = path.join(root, ...family.tsDir, "inventory.generated.ts");
  fs.mkdirSync(path.dirname(jsonOut), { recursive: true });
  fs.writeFileSync(jsonOut, `${JSON.stringify(inv, null, 2)}\n`);
  fs.mkdirSync(path.dirname(tsOut), { recursive: true });
  fs.writeFileSync(tsOut, emitTs(inv, family));
  lines.push(
    `${family.id}: ${inv.totals.symbolsCalledByGameCode} entry points called by game code across ` +
      `${inv.totals.gameCallSites} static call sites ` +
      `(${inv.totals.bridgedGameCallSites} of them across the bridged seam, ` +
      `${inv.totals.inWindowGameCallSites} in-window); ` +
      `${inv.totals.mmioRegisters} MMIO registers touched ` +
      `(${inv.totals.mmioReads}R/${inv.totals.mmioWrites}W).\n` +
      `  -> ${path.relative(root, jsonOut)}\n  -> ${path.relative(root, tsOut)}`,
  );
}
process.stdout.write(`${lines.join("\n")}\n`);
