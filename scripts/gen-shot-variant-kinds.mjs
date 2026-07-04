#!/usr/bin/env node
// Extract the per-weapon-module SHOT VARIANT tables that map a projectile
// variant byte (shot child +0x11, sometimes +0x12/+0x13/+0x14) to its HIT kind.
//
// Pipeline (evidence: research/decomp/movement-hit-decode-2026-07-04.md section 2):
// 1. Census: every zz_008ac80_(child, kind) call site in research/decomp/ghidra-export
//    whose kind argument is a static DOL table indexed by `variantByte * stride`.
//    Example shapes:
//      chunk_0009.c:3895+3908 (FUN_8006f11c): iVar4 = *(byte*)(p+0x11) * 0x34;
//        zz_008ac80_(p, (int)(char)(&DAT_802d39b3)[iVar4]);       // s8 kind
//      chunk_0015.c:1506 (FUN_8009a12c): (int)*(short*)(&DAT_802f3ddc + iVar4)  // s16 kind
//      chunk_0039.c:2358 (FUN_80150dc8): *(int*)(&DAT_80340f68 + variant*4)     // s32 kind
// 2. Spawner linkage: the consumer init fn is entry N of a PTR_ state-dispatch
//    table; the dispatcher fn (which does `(&PTR_..)[child+0x18]`) is stored at
//    child+0xc by the SPAWNER (fire fn), which also writes child+0x11 = variant.
//    We locate the PTR table by scanning boot.dol data for the init address,
//    match it against dispatch bases referenced in the corpus, then find the
//    fn that stores the dispatcher at +0xc, then grep all of its call sites.
//    Call-site literal args bound the variant space and name the firing borg
//    (callers often compare *(short*)(actor+1000) == borgId).
// 3. Table dump from boot.dol. Row count = next referenced DOL symbol at or
//    beyond rowBase+stride (row-0 field symbols live inside the first row;
//    rows 1+ are only ever reached via indexed access, so the next standalone
//    symbol marks the end of the table), refined by the max literal variant
//    observed at spawner call sites. Never past the containing section.
//
// Output: packages/combat/src/data/shotVariantKinds.json

import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const repoRoot = path.resolve(path.dirname(fileURLToPath(import.meta.url)), "..");
const exportDir = path.join(repoRoot, "research/decomp/ghidra-export");
const bootDolPath = path.join(repoRoot, "user-data/GG4E/disc/sys/boot.dol");
const outPath = path.join(repoRoot, "packages/combat/src/data/shotVariantKinds.json");

function fail(message) {
  console.error(`gen-shot-variant-kinds: ${message}`);
  process.exit(1);
}

if (!fs.existsSync(bootDolPath)) fail(`missing ${path.relative(repoRoot, bootDolPath)}`);
if (!fs.existsSync(exportDir)) fail(`missing ${path.relative(repoRoot, exportDir)}`);

// ---------------------------------------------------------------- DOL mapping
const dol = fs.readFileSync(bootDolPath);
const sectionOffsets = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(i * 4));
const sectionAddresses = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x48 + i * 4));
const sectionSizes = Array.from({ length: 18 }, (_, i) => dol.readUInt32BE(0x90 + i * 4));

function offsetFor(address) {
  for (let i = 0; i < 18; i += 1) {
    if (sectionSizes[i] > 0 && address >= sectionAddresses[i] && address < sectionAddresses[i] + sectionSizes[i]) {
      return sectionOffsets[i] + (address - sectionAddresses[i]);
    }
  }
  return null;
}

function sectionEndFor(address) {
  for (let i = 0; i < 18; i += 1) {
    if (sectionSizes[i] > 0 && address >= sectionAddresses[i] && address < sectionAddresses[i] + sectionSizes[i]) {
      return sectionAddresses[i] + sectionSizes[i];
    }
  }
  return null;
}

function hex(value) {
  return `0x${(value >>> 0).toString(16).padStart(8, "0")}`;
}

// ------------------------------------------------------------- corpus loading
const chunkFiles = fs
  .readdirSync(exportDir)
  .filter((f) => /^chunk_\d+\.c$/.test(f))
  .sort();

const chunks = chunkFiles.map((file) => {
  const text = fs.readFileSync(path.join(exportDir, file), "utf8");
  const lines = text.split(/\r?\n/);
  const markers = [];
  for (let i = 0; i < lines.length; i += 1) {
    const m = lines[i].match(/^\/\/ ==== ([0-9a-f]{8})\s+(\S+) ====/);
    if (m) markers.push({ line: i, addr: parseInt(m[1], 16), name: m[2] });
  }
  return { file, text, lines, markers };
});

const fnByName = new Map();
for (const chunk of chunks) {
  for (let i = 0; i < chunk.markers.length; i += 1) {
    const mk = chunk.markers[i];
    const endLine = i + 1 < chunk.markers.length ? chunk.markers[i + 1].line : chunk.lines.length;
    const fn = {
      name: mk.name,
      addr: mk.addr,
      file: chunk.file,
      startLine: mk.line + 1,
      endLine,
      body: chunk.lines.slice(mk.line, endLine).join("\n"),
    };
    if (!fnByName.has(mk.name)) fnByName.set(mk.name, fn);
  }
}

function fnAt(chunk, lineIdx) {
  let cur = null;
  for (const mk of chunk.markers) {
    if (mk.line <= lineIdx) cur = mk;
    else break;
  }
  return cur;
}

// All DOL symbol addresses referenced anywhere in the corpus (DAT_/FLOAT_/PTR_/
// DOUBLE_/s_ ...). Used as table-extent boundaries.
const symbolAddrs = new Set();
// Dispatch-table bases: `(&PTR_xxx_8yyyyyyy)[...]`
const dispatchBases = new Set();
for (const chunk of chunks) {
  for (const m of chunk.text.matchAll(/_([0-9a-f]{8})\b/g)) symbolAddrs.add(parseInt(m[1], 16));
  for (const m of chunk.text.matchAll(/\(&\w+_([0-9a-f]{8})\)\s*\[/g)) dispatchBases.add(parseInt(m[1], 16));
}
const sortedSymbols = [...symbolAddrs].sort((a, b) => a - b);

function nextSymbolAtOrAfter(address) {
  let lo = 0;
  let hi = sortedSymbols.length;
  while (lo < hi) {
    const mid = (lo + hi) >> 1;
    if (sortedSymbols[mid] < address) lo = mid + 1;
    else hi = mid;
  }
  return lo < sortedSymbols.length ? sortedSymbols[lo] : null;
}

// ------------------------------------------------------------------ census
function extractCallArg(stmt) {
  const start = stmt.indexOf("zz_008ac80_(");
  if (start < 0) return null;
  let i = start + "zz_008ac80_(".length;
  let depth = 1;
  let commaPos = -1;
  for (; i < stmt.length; i += 1) {
    const c = stmt[i];
    if (c === "(") depth += 1;
    else if (c === ")") {
      depth -= 1;
      if (depth === 0) break;
    } else if (c === "," && depth === 1 && commaPos < 0) commaPos = i;
  }
  if (commaPos < 0 || depth !== 0) return null;
  return stmt.slice(commaPos + 1, i).trim().replace(/\s+/g, " ");
}

const VARIANT_LOAD =
  /^\(?(?:\(uint\)|\(char\)|\(int\))?\*\((?:byte|char) \*\)\((\w+) \+ (0x[0-9a-f]+)\)\)?$/;
const VARIANT_LOAD_TIMES =
  /^\(?(?:\(uint\)|\(char\)|\(int\))?\*\((?:byte|char) \*\)\((\w+) \+ (0x[0-9a-f]+)\)\)? \* (0x[0-9a-f]+|\d+)$/;
const VARIANT_MASKED =
  /^\(?\(?(?:\(int\)|\(uint\))?\*\((?:byte|char) \*\)\((\w+) \+ (0x[0-9a-f]+)\)\)? & 0x7fU?\)?$/;
const VARIANT_MASKED_TIMES =
  /^\(\(?(?:\(int\)|\(uint\))?\*\((?:byte|char) \*\)\((\w+) \+ (0x[0-9a-f]+)\)\)? & 0x7fU?\) \* (0x[0-9a-f]+|\d+)$/;
const VARIANT_U32_MASKED_TIMES =
  /^\(\*\(uint \*\)\((\w+) \+ (0x[0-9a-f]+)\) & 0xff\) \* (0x[0-9a-f]+|\d+)$/;

const sites = [];
for (const chunk of chunks) {
  for (let i = 0; i < chunk.lines.length; i += 1) {
    if (!chunk.lines[i].includes("zz_008ac80_(")) continue;
    const mk = fnAt(chunk, i);
    if (!mk || mk.name === "zz_008ac80_") continue;

    let stmt = chunk.lines[i];
    let j = i;
    while (extractCallArg(stmt) === null && j + 1 < chunk.lines.length && j - i < 6) {
      j += 1;
      stmt += " " + chunk.lines[j].trim();
    }
    const arg = extractCallArg(stmt);
    const endLine = chunk.markers[chunk.markers.indexOf(mk) + 1]?.line ?? chunk.lines.length;
    const fnBody = chunk.lines.slice(mk.line, endLine).join("\n");

    const site = {
      fn: mk.name,
      fnAddr: mk.addr,
      chunkLine: `${chunk.file}:${i + 1}`,
      arg,
      shape: "dynamic",
    };

    let m;
    if (arg === null) {
      site.shape = "parse-fail";
    } else if ((m = arg.match(/^(0x[0-9a-f]+|\d+)$/))) {
      site.shape = "literal";
      site.kind = m[1].startsWith("0x") ? parseInt(m[1], 16) : parseInt(m[1], 10);
    } else if ((m = arg.match(/^\(int\)\(char\)\(&DAT_([0-9a-f]{8})\)\[(.+)\]$/))) {
      site.shape = "table";
      site.kindAddr = parseInt(m[1], 16);
      site.idxExpr = m[2];
      site.kindWidth = 1;
    } else if ((m = arg.match(/^\(int\)\*\(short \*\)\(&DAT_([0-9a-f]{8}) \+ (.+)\)$/))) {
      site.shape = "table";
      site.kindAddr = parseInt(m[1], 16);
      site.idxExpr = m[2];
      site.kindWidth = 2;
    } else if ((m = arg.match(/^\*\(int \*\)\(&DAT_([0-9a-f]{8}) \+ (.+)\)$/))) {
      site.shape = "table";
      site.kindAddr = parseInt(m[1], 16);
      site.idxExpr = m[2];
      site.kindWidth = 4;
    }

    if (site.shape === "table") {
      const resolveExpr = (expr, hops) => {
        let mm;
        if ((mm = expr.match(VARIANT_LOAD_TIMES)))
          return { base: mm[1], srcOff: parseInt(mm[2], 16), stride: parseInt(mm[3], 16) };
        if ((mm = expr.match(VARIANT_MASKED_TIMES)))
          return { base: mm[1], srcOff: parseInt(mm[2], 16), srcMask: 0x7f, stride: parseInt(mm[3], 16) };
        if ((mm = expr.match(VARIANT_U32_MASKED_TIMES)))
          return { base: mm[1], srcOff: parseInt(mm[2], 16), srcMask: 0xff, srcWidth: 4, stride: parseInt(mm[3], 16) };
        if ((mm = expr.match(/^(\w+) \* (0x[0-9a-f]+|\d+)$/)) && hops > 0) {
          const inner = resolveVar(mm[1], hops - 1);
          if (inner && inner.stride === undefined) return { ...inner, stride: parseInt(mm[2], 16) };
          return null;
        }
        if ((mm = expr.match(/^(\w+)$/)) && hops > 0) return resolveVar(mm[1], hops - 1);
        return null;
      };
      const resolveVar = (v, hops) => {
        const re = new RegExp(`\\b${v} = ([^;]+);`, "g");
        let mm;
        while ((mm = re.exec(fnBody))) {
          const rhs = mm[1].replace(/\s+/g, " ").trim();
          let r;
          if ((r = rhs.match(VARIANT_LOAD))) return { base: r[1], srcOff: parseInt(r[2], 16) };
          if ((r = rhs.match(VARIANT_MASKED))) return { base: r[1], srcOff: parseInt(r[2], 16), srcMask: 0x7f };
          const solved = resolveExpr(rhs, hops);
          if (solved) return solved;
        }
        return null;
      };
      const res = resolveExpr(site.idxExpr.replace(/\s+/g, " ").trim(), 3);
      if (res && res.stride !== undefined) {
        site.variantOffset = res.srcOff;
        if (res.srcMask) site.variantMask = res.srcMask;
        site.stride = res.stride;
      } else {
        site.shape = "table-unresolved";
      }
    }

    // sibling field accesses driven by the same index variable -> row base
    if (site.shape === "table") {
      const vm = site.idxExpr.match(/^(\w+)$/);
      const addrs = new Set([site.kindAddr]);
      if (vm) {
        const vars = new Set([vm[1]]);
        for (let pass = 0; pass < 2; pass += 1) {
          for (const am of fnBody.matchAll(/\b(\w+) = (\w+);/g)) {
            if (vars.has(am[2])) vars.add(am[1]);
          }
        }
        for (const v of vars) {
          for (const mm of fnBody.matchAll(new RegExp(`&DAT_([0-9a-f]{8})\\)\\[${v}\\]`, "g")))
            addrs.add(parseInt(mm[1], 16));
          for (const mm of fnBody.matchAll(new RegExp(`&DAT_([0-9a-f]{8}) \\+ ${v}\\)`, "g")))
            addrs.add(parseInt(mm[1], 16));
        }
      }
      // keep only plausible row-0 field addresses (within one stride at/below kindAddr)
      const valid = [...addrs].filter((a) => a <= site.kindAddr && site.kindAddr - a < site.stride);
      let rowBase = Math.min(...valid);
      // rows conventionally start 4-aligned; align down while staying within one stride
      const aligned4 = rowBase - (rowBase % 4);
      if (site.kindAddr - aligned4 < site.stride) rowBase = aligned4;
      site.rowBase = rowBase;
      site.kindOffset = site.kindAddr - rowBase;
      site.rowFieldAddrs = valid.map((a) => hex(a));
    }
    sites.push(site);
  }
}

// -------------------------------------------------- spawner linkage per consumer
// Map: code address -> data addresses in the DOL that hold a pointer to it.
// Indexed for every code-range word so dispatcher chains can be walked.
const CODE_LO = 0x80003000;
const CODE_HI = 0x80220000;
const ptrHits = new Map(); // codeAddr -> [dataAddr]
for (let sec = 0; sec < 18; sec += 1) {
  if (sectionSizes[sec] === 0 || sectionAddresses[sec] < 0x80220000) continue; // data sections only
  const base = sectionOffsets[sec];
  const size = sectionSizes[sec] & ~3;
  for (let off = 0; off < size; off += 4) {
    const word = dol.readUInt32BE(base + off);
    if (word >= CODE_LO && word < CODE_HI && (word & 3) === 0) {
      if (!ptrHits.has(word)) ptrHits.set(word, []);
      ptrHits.get(word).push(sectionAddresses[sec] + off);
    }
  }
}

const sortedDispatchBases = [...dispatchBases].sort((a, b) => a - b);
function dispatchBaseFor(addr) {
  // the largest dispatch base <= addr and within 0x40 bytes
  let lo = 0;
  let hi = sortedDispatchBases.length;
  while (lo < hi) {
    const mid = (lo + hi) >> 1;
    if (sortedDispatchBases[mid] <= addr) lo = mid + 1;
    else hi = mid;
  }
  const cand = lo > 0 ? sortedDispatchBases[lo - 1] : null;
  return cand !== null && addr - cand < 0x40 ? cand : null;
}

function fnsReferencing(token) {
  const out = [];
  for (const chunk of chunks) {
    if (!chunk.text.includes(token)) continue;
    for (let i = 0; i < chunk.lines.length; i += 1) {
      if (!chunk.lines[i].includes(token)) continue;
      const mk = fnAt(chunk, i);
      if (mk) out.push({ fn: mk.name, chunkLine: `${chunk.file}:${i + 1}`, lineText: chunk.lines[i] });
    }
  }
  return out;
}

function callSitesOf(fnName) {
  const out = [];
  const needle = `${fnName}(`;
  for (const chunk of chunks) {
    if (!chunk.text.includes(needle)) continue;
    for (let i = 0; i < chunk.lines.length; i += 1) {
      const col = chunk.lines[i].indexOf(needle);
      if (col < 0) continue;
      if (chunk.lines[i].includes(`==== `)) continue; // marker
      // skip the definition line `void fnName(...)`
      if (/^(void|int|uint|undefined\d*|float|double|short|char)\b/.test(chunk.lines[i].trim()) &&
          chunk.markers.some((mk) => mk.name === fnName && Math.abs(mk.line - i) < 4)) {
        continue;
      }
      const mk = fnAt(chunk, i);
      if (!mk || mk.name === fnName) continue;
      // reassemble args
      let stmt = chunk.lines[i];
      let j = i;
      const argOf = (text) => {
        const start = text.indexOf(needle);
        let k = start + needle.length;
        let depth = 1;
        const commas = [];
        for (; k < text.length; k += 1) {
          const c = text[k];
          if (c === "(") depth += 1;
          else if (c === ")") {
            depth -= 1;
            if (depth === 0) break;
          } else if (c === "," && depth === 1) commas.push(k);
        }
        if (depth !== 0) return null;
        const inner = text.slice(start + needle.length, k);
        const parts = [];
        let last = start + needle.length;
        for (const cpos of commas) {
          parts.push(text.slice(last, cpos).trim());
          last = cpos + 1;
        }
        parts.push(text.slice(last, k).trim());
        return inner.length === 0 ? [] : parts;
      };
      while (argOf(stmt) === null && j + 1 < chunk.lines.length && j - i < 6) {
        j += 1;
        stmt += " " + chunk.lines[j].trim();
      }
      const args = argOf(stmt);
      const endLine = chunk.markers[chunk.markers.indexOf(mk) + 1]?.line ?? chunk.lines.length;
      const callerBody = chunk.lines.slice(mk.line, endLine).join("\n");
      const borgIdSet = new Set(
        [...callerBody.matchAll(/\+ 1000\) == (0x[0-9a-f]+|\d+)/g)].map((mm) =>
          mm[1].startsWith("0x") ? parseInt(mm[1], 16) : parseInt(mm[1], 10),
        ),
      );
      // two-step form: sVar1 = *(short *)(actor + 1000); ... if (sVar1 == 0x615)
      for (const vm of callerBody.matchAll(/(\w+) = \*\(short \*\)\(\w+ \+ 1000\);/g)) {
        for (const cm of callerBody.matchAll(new RegExp(`\\b${vm[1]} == (0x[0-9a-f]+|\\d+)`, "g"))) {
          borgIdSet.add(cm[1].startsWith("0x") ? parseInt(cm[1], 16) : parseInt(cm[1], 10));
        }
      }
      const borgIds = [...borgIdSet];
      out.push({
        caller: mk.name,
        chunkLine: `${chunk.file}:${i + 1}`,
        args,
        callerBorgIdCompares: borgIds.map((b) => `0x${b.toString(16)}`),
      });
    }
  }
  return out;
}

// child-field writes inside a spawner: `puVar1[0x11] = param_2;` etc.
function stripCasts(expr) {
  return expr.replace(/\((?:char|byte|short|int|uint|undefined[124]?)\)/g, "").trim();
}

function spawnerChildWrites(body) {
  const writes = {};
  for (const mm of body.matchAll(/(\w+)\[(0x1[0-4])\] = ([^;]+);/g)) {
    writes[mm[2]] = stripCasts(mm[3]);
  }
  for (const mm of body.matchAll(/\*\(undefined1 \*\)\((\w+) \+ (0x1[0-4])\) = ([^;]+);/g)) {
    writes[mm[2]] = stripCasts(mm[3]);
  }
  // u32 write covering +0x14..0x17 (consumer reads *(uint*)(+0x14) & 0xff)
  for (const mm of body.matchAll(/\*\(uint \*\)\((\w+) \+ (0x14)\) = ([^;]+);/g)) {
    writes[mm[2]] = stripCasts(mm[3]);
  }
  return writes;
}

function spawnersAssigning(target, via) {
  // fns that store `target` at child+0xc (i.e. fire fns registering the handler)
  const found = [];
  const assignToken = `0xc) = ${target};`;
  for (const chunk of chunks) {
    if (!chunk.text.includes(assignToken)) continue;
    for (let i = 0; i < chunk.lines.length; i += 1) {
      if (!chunk.lines[i].includes(assignToken)) continue;
      const mk = fnAt(chunk, i);
      if (!mk) continue;
      const fn = fnByName.get(mk.name);
      found.push({
        fn: mk.name,
        chunkLine: `${chunk.file}:${i + 1}`,
        dispatcher: via,
        childWrites: fn ? spawnerChildWrites(fn.body) : {},
        callSites: callSitesOf(mk.name),
      });
    }
  }
  return found;
}

const spawnerCache = new Map(); // consumer fn name -> linkage
function resolveSpawners(consumer, depth = 0, visited = new Set()) {
  if (depth === 0 && spawnerCache.has(consumer.name)) return spawnerCache.get(consumer.name);
  visited.add(consumer.name);
  const result = { dispatchers: [], spawners: [] };
  const spawnerNames = new Set();
  const addSpawners = (list) => {
    for (const sp of list) {
      if (spawnerNames.has(sp.fn)) continue;
      spawnerNames.add(sp.fn);
      result.spawners.push(sp);
    }
  };

  // direct `+0xc = consumer;` registration
  addSpawners(spawnersAssigning(consumer.name, consumer.name));

  // consumer sits in a PTR_ dispatch table; find the dispatcher fn(s)
  const hits = ptrHits.get(consumer.addr) ?? [];
  const dispatcherNames = new Set();
  for (const dataAddr of hits) {
    const base = dispatchBaseFor(dataAddr);
    if (base === null) continue;
    const token = `_${base.toString(16).padStart(8, "0")})`; // e.g. PTR_FUN_803051e4)
    for (const ref of fnsReferencing(token)) {
      if (!ref.lineText.includes(`(&`) || !ref.lineText.includes(`)[`)) continue;
      if (dispatcherNames.has(ref.fn) || ref.fn === consumer.name) continue;
      dispatcherNames.add(ref.fn);
      result.dispatchers.push({
        fn: ref.fn,
        chunkLine: ref.chunkLine,
        table: hex(base),
        entryIndex: (dataAddr - base) / 4,
      });
    }
  }
  for (const name of dispatcherNames) {
    addSpawners(spawnersAssigning(name, name));
  }

  // dispatcher itself may be another table entry (two-level dispatch), or the
  // consumer may be invoked directly by a fn that is a table entry: recurse.
  if (result.spawners.length === 0 && depth < 3) {
    const nextHops = new Set(dispatcherNames);
    for (const call of callSitesOf(consumer.name)) nextHops.add(call.caller);
    for (const hop of nextHops) {
      if (visited.has(hop)) continue;
      const fn = fnByName.get(hop);
      if (!fn) continue;
      const inner = resolveSpawners({ name: hop, addr: fn.addr }, depth + 1, visited);
      addSpawners(
        inner.spawners.map((sp) => ({ ...sp, dispatcher: `${sp.dispatcher} -> ${hop}` })),
      );
      for (const disp of inner.dispatchers) {
        if (!result.dispatchers.some((d) => d.fn === disp.fn && d.table === disp.table)) {
          result.dispatchers.push({ ...disp, via: hop });
        }
      }
    }
  }

  if (depth === 0) spawnerCache.set(consumer.name, result);
  return result;
}

// ------------------------------------------------------------ table assembly
const tables = new Map(); // rowBase -> table record
const tableSites = sites.filter((s) => s.shape === "table");
for (const site of tableSites) {
  const key = site.rowBase;
  if (!tables.has(key)) {
    tables.set(key, {
      rowBase: key,
      stride: site.stride,
      kindColumns: [],
      consumers: [],
    });
  }
  const table = tables.get(key);
  if (table.stride !== site.stride) {
    console.warn(
      `warning: stride mismatch at ${hex(key)}: ${table.stride} vs ${site.stride} (${site.chunkLine})`,
    );
  }
  if (!table.kindColumns.some((c) => c.kindOffset === site.kindOffset && c.kindWidth === site.kindWidth)) {
    table.kindColumns.push({ kindOffset: site.kindOffset, kindWidth: site.kindWidth });
  }
  const linkage = resolveSpawners({ name: site.fn, addr: site.fnAddr });
  const consumer = {
    fn: site.fn,
    fnAddr: hex(site.fnAddr),
    chunkLine: site.chunkLine,
    kindArg: site.arg,
    kindOffset: site.kindOffset,
    kindWidth: site.kindWidth,
    variantSource: {
      childOffset: `0x${site.variantOffset.toString(16)}`,
      ...(site.variantMask ? { mask: `0x${site.variantMask.toString(16)}` } : {}),
    },
    rowFieldAddrs: site.rowFieldAddrs,
    dispatchers: linkage.dispatchers,
    spawners: linkage.spawners.map((sp) => ({
      fn: sp.fn,
      chunkLine: sp.chunkLine,
      dispatcher: sp.dispatcher,
      childWrites: sp.childWrites,
      callSites: sp.callSites,
    })),
  };
  if (consumer.spawners.length === 0) {
    // init not reached via a +0xc dispatcher we could resolve; fall back to
    // direct callers of the consumer itself as family evidence
    consumer.directCallers = callSitesOf(site.fn);
  }
  table.consumers.push(consumer);
}

function literalVariantMax(table) {
  // Which spawner argument feeds the consumer's variant byte?
  let max = null;
  for (const consumer of table.consumers) {
    const childOff = consumer.variantSource.childOffset;
    const mask = consumer.variantSource.mask ? parseInt(consumer.variantSource.mask, 16) : null;
    for (const spawner of consumer.spawners) {
      const written = spawner.childWrites[childOff];
      if (!written) continue;
      const pm = written.match(/^param_(\d+)$/);
      if (!pm) {
        // literal write inside the spawner itself
        const lm = written.match(/^(0x[0-9a-f]+|\d+)$/);
        if (lm) {
          let v = lm[1].startsWith("0x") ? parseInt(lm[1], 16) : parseInt(lm[1], 10);
          if (mask !== null) v &= mask;
          if (max === null || v > max) max = v;
        }
        continue;
      }
      const argIndex = parseInt(pm[1], 10) - 1; // param_1 == args[0]
      for (const call of spawner.callSites) {
        const raw = call.args?.[argIndex];
        if (raw === undefined) continue;
        const lm = stripCasts(raw).match(/^(0x[0-9a-f]+|\d+)$/);
        if (!lm) continue;
        let v = lm[1].startsWith("0x") ? parseInt(lm[1], 16) : parseInt(lm[1], 10);
        if (mask !== null) v &= mask;
        if (max === null || v > max) max = v;
      }
    }
  }
  return max;
}

const MAX_ROWS = 256;
const outTables = {};
for (const table of [...tables.values()].sort((a, b) => a.rowBase - b.rowBase)) {
  const { rowBase, stride } = table;
  const kindColumns = [...table.kindColumns].sort((a, b) => a.kindOffset - b.kindOffset);
  const { kindOffset, kindWidth } = kindColumns[0];
  const sectionEnd = sectionEndFor(rowBase);
  if (sectionEnd === null) {
    console.warn(`warning: table ${hex(rowBase)} outside mapped DOL sections; skipped`);
    continue;
  }
  const nextSym = nextSymbolAtOrAfter(rowBase + stride);
  let symbolBound = Math.floor(((nextSym ?? sectionEnd) - rowBase) / stride);
  symbolBound = Math.min(symbolBound, Math.floor((sectionEnd - rowBase) / stride));
  const litMax = literalVariantMax(table);
  let rowCount = symbolBound;
  let rowCountSource = `next referenced symbol ${nextSym === null ? "(section end)" : hex(nextSym)}`;
  if (litMax !== null && litMax + 1 > rowCount) {
    rowCount = litMax + 1;
    rowCountSource = `max literal variant ${litMax} at spawner call sites (exceeds symbol bound ${symbolBound})`;
  }
  if (rowCount > MAX_ROWS) {
    rowCount = litMax !== null ? Math.max(litMax + 1, 1) : MAX_ROWS;
    rowCountSource += `; capped to ${rowCount}`;
  }
  rowCount = Math.min(rowCount, Math.floor((sectionEnd - rowBase) / stride));

  const readKind = (rowAddr, column) => {
    const abs = offsetFor(rowAddr + column.kindOffset);
    if (abs === null) return null;
    if (column.kindWidth === 1) return dol.readInt8(abs);
    if (column.kindWidth === 2) return dol.readInt16BE(abs);
    return dol.readInt32BE(abs);
  };

  const rows = [];
  for (let r = 0; r < rowCount; r += 1) {
    const rowAddr = rowBase + r * stride;
    const off = offsetFor(rowAddr);
    if (off === null) break;
    const raw = dol.subarray(off, off + stride);
    const row = {
      variant: r,
      kind: readKind(rowAddr, kindColumns[0]),
      rawBytes: [...raw].map((b) => b.toString(16).padStart(2, "0")).join(""),
    };
    if (kindColumns.length > 1) {
      row.kindsByOffset = Object.fromEntries(
        kindColumns.map((c) => [`0x${c.kindOffset.toString(16)}`, readKind(rowAddr, c)]),
      );
    }
    rows.push(row);
  }

  // HIT kinds index the owner hit.bin remap region bin+0xa20..0xaa0 (32 slots;
  // negative = spawn skipped), so valid kinds are -1..31. Trailing rows with
  // implausible kinds mean the next-symbol bound over-ran into unrelated data
  // (never below max literal variant + 1).
  const plausible = (k) => k >= -1 && k <= 31;
  const keepAtLeast = Math.max(litMax !== null ? litMax + 1 : 1, 1);
  let trimmedCount = rows.length;
  while (trimmedCount > keepAtLeast && !plausible(rows[trimmedCount - 1].kind)) trimmedCount -= 1;
  // implausible kinds ABOVE the max literal variant mean the symbol bound
  // over-ran into unrelated data; cut back to the proven variant range
  if (litMax !== null && rows.slice(litMax + 1, trimmedCount).some((r) => !plausible(r.kind))) {
    trimmedCount = litMax + 1;
  }
  if (trimmedCount < rows.length) {
    rows.length = trimmedCount;
    rowCountSource += `; trimmed to ${trimmedCount} rows (implausible kinds past the proven variant range)`;
  }
  const suspiciousKindRows = rows.filter((r) => !plausible(r.kind)).length;

  outTables[hex(rowBase)] = {
    stride,
    kindOffset,
    kindWidth,
    ...(kindColumns.length > 1 ? { kindColumns } : {}),
    rowCount: rows.length,
    rowCountSource,
    ...(litMax !== null ? { maxLiteralVariantObserved: litMax } : {}),
    ...(suspiciousKindRows > 0 ? { suspiciousKindRows } : {}),
    rows,
    consumers: table.consumers,
  };
}

// ---------------------------------------------- fire-fn shot-id resolution
// For every spawner call site (the FIRE FN layer), prove the constant shot
// id/variant it passes, so each table row gains provenance: which fire fn
// (and, where a call-site borg-id guard exists, which borg) fires that row.
// Ground truth chain (G RED): zz_018dcb0_ guards `*(short*)(actor+1000) ==
// 0x615` around `zz_00c3be0_(actor, 0x2b)` -> registry 0x80303138 row 0x2b ->
// kind 0. Conservative: only constants provable from the decompiled corpus
// (literals, unique-constant local assignments, single-param affine spawner
// transforms). Everything else lands in unresolvedFireSites with a reason.

const chunkByFile = new Map(chunks.map((c) => [c.file, c]));

function siteContext(chunkLine) {
  const idx = chunkLine.lastIndexOf(":");
  const file = chunkLine.slice(0, idx);
  const lineIdx = parseInt(chunkLine.slice(idx + 1), 10) - 1;
  const chunk = chunkByFile.get(file);
  if (!chunk) return null;
  const mk = fnAt(chunk, lineIdx);
  if (!mk) return null;
  const mi = chunk.markers.indexOf(mk);
  const endLine = mi + 1 < chunk.markers.length ? chunk.markers[mi + 1].line : chunk.lines.length;
  let offset = 0;
  for (let i = mk.line; i < lineIdx; i += 1) offset += chunk.lines[i].length + 1;
  return { body: chunk.lines.slice(mk.line, endLine).join("\n"), offset, fnName: mk.name };
}

function parseConst(text) {
  const t = text.trim();
  let m;
  if ((m = t.match(/^0x[0-9a-f]+$/i))) return parseInt(t, 16);
  if ((m = t.match(/^\d+$/))) return parseInt(t, 10);
  if ((m = t.match(/^'\\x([0-9a-fA-F]{1,2})'$/))) return parseInt(m[1], 16);
  if ((m = t.match(/^'([ -~])'$/))) return m[1].charCodeAt(0);
  return null;
}

function stripOuterParens(text) {
  let t = text.trim();
  while (t.startsWith("(") && t.endsWith(")")) {
    let depth = 0;
    let wraps = true;
    for (let i = 0; i < t.length; i += 1) {
      if (t[i] === "(") depth += 1;
      else if (t[i] === ")") {
        depth -= 1;
        if (depth === 0 && i < t.length - 1) {
          wraps = false;
          break;
        }
      }
    }
    if (!wraps) break;
    t = t.slice(1, -1).trim();
  }
  return t;
}

const CONST_RHS = /(0x[0-9a-f]+|\d+|'\\x[0-9a-fA-F]{1,2}'|'[ -~]')$/;

// Resolve a call-site argument expression to the set of constant values it can
// provably take. null = not provable.
function resolveArgValues(body, expr, depth = 3) {
  if (depth < 0) return null;
  const e = stripOuterParens(stripCasts(expr));
  const c = parseConst(e);
  if (c !== null) return [c];
  let m;
  if ((m = e.match(new RegExp(`^(.+) (\\+|-|>>|<<|&|\\*) ${CONST_RHS.source}`)))) {
    const inner = resolveArgValues(body, m[1], depth - 1);
    const k = parseConst(m[3]);
    if (inner === null || k === null) return null;
    const apply = { "+": (v) => v + k, "-": (v) => v - k, ">>": (v) => v >> k, "<<": (v) => v << k, "&": (v) => v & k, "*": (v) => v * k }[m[2]];
    return [...new Set(inner.map(apply))];
  }
  if (/^[A-Za-z_]\w*$/.test(e)) {
    // every assignment to the variable must resolve to a constant; the union of
    // those constants is the provable value set (any of them can flow here).
    const values = new Set();
    let any = false;
    for (const am of body.matchAll(new RegExp(`\\b${e} = ([^;]+);`, "g"))) {
      any = true;
      const inner = resolveArgValues(body, am[1], depth - 1);
      if (inner === null) return null;
      for (const v of inner) values.add(v);
    }
    return any ? [...values] : null;
  }
  return null;
}

// Spawner-side transform: how the spawner's variant-byte write maps its own
// parameter to the stored variant. Only single-param affine forms are proven.
function parseSpawnerTransform(writeExpr) {
  if (writeExpr === undefined) return null;
  const e = stripOuterParens(stripCasts(writeExpr));
  const lit = parseConst(e);
  if (lit !== null) return { literal: lit };
  let m;
  if ((m = e.match(/^param_(\d+)$/))) return { paramIndex: parseInt(m[1], 10) - 1, apply: (v) => v };
  if ((m = e.match(new RegExp(`^param_(\\d+) (\\+|-|>>|<<|&|\\*) ${CONST_RHS.source}`)))) {
    const k = parseConst(m[3]);
    if (k === null) return null;
    const op = { "+": (v) => v + k, "-": (v) => v - k, ">>": (v) => v >> k, "<<": (v) => v << k, "&": (v) => v & k, "*": (v) => v * k }[m[2]];
    return { paramIndex: parseInt(m[1], 10) - 1, apply: op };
  }
  return null;
}

// Brace-scope analysis: which borg-id equality guards enclose a char offset.
function computeBlocks(body) {
  const blocks = [];
  const stack = [];
  for (let i = 0; i < body.length; i += 1) {
    if (body[i] === "{") stack.push(i);
    else if (body[i] === "}") {
      const start = stack.pop();
      if (start !== undefined) blocks.push({ start, end: i });
    }
  }
  for (const b of blocks) {
    const from = Math.max(
      body.lastIndexOf(";", b.start),
      body.lastIndexOf("}", b.start - 1),
      body.lastIndexOf("{", b.start - 1),
    );
    b.header = body.slice(from + 1, b.start);
  }
  return blocks;
}

function borgGuardsAt(body, blocks, offset) {
  const borgVars = new Set();
  for (const m of body.matchAll(/(\w+) = \*\(short \*\)\(\w+ \+ 1000\);/g)) borgVars.add(m[1]);
  const ids = new Set();
  for (const b of blocks) {
    if (!(b.start < offset && offset < b.end)) continue;
    if (!/\bif\s*\(/.test(b.header)) continue;
    for (const m of b.header.matchAll(/(\*\(short \*\)\(\w+ \+ 1000\)|[A-Za-z_]\w*) == (0x[0-9a-f]+|\d+)/g)) {
      const lhs = m[1];
      if (lhs.includes("+ 1000)") || borgVars.has(lhs)) {
        ids.add(m[2].startsWith("0x") ? parseInt(m[2], 16) : parseInt(m[2], 10));
      }
    }
  }
  return [...ids];
}

const guardCache = new Map(); // fnName -> {body, blocks}
function callerAnalysis(chunkLine) {
  const ctx = siteContext(chunkLine);
  if (!ctx) return null;
  if (!guardCache.has(ctx.fnName)) {
    guardCache.set(ctx.fnName, { body: ctx.body, blocks: computeBlocks(ctx.body) });
  }
  const cached = guardCache.get(ctx.fnName);
  return { ...cached, offset: ctx.offset, fnName: ctx.fnName };
}

function classifyUnresolved(arg) {
  if (arg === undefined || arg === null) return "call-site argument unavailable (parse fail)";
  if (/&DAT_[0-9a-f]{8}/.test(arg)) return "shot id from DOL sub-table lookup (index not proven)";
  if (/\*\(/.test(arg)) return "shot id from runtime field";
  return "variable without provable constant assignment chain";
}

const fireSiteResolutions = [];
const unresolvedFireSites = [];
const seenResolutions = new Set();
const seenUnresolved = new Set();

for (const [tableAddr, table] of Object.entries(outTables)) {
  for (const consumer of table.consumers) {
    const childOff = consumer.variantSource.childOffset;
    const mask = consumer.variantSource.mask ? parseInt(consumer.variantSource.mask, 16) : null;
    for (const spawner of consumer.spawners) {
      const transform = parseSpawnerTransform(spawner.childWrites[childOff]);
      if (transform === null) {
        const key = `${tableAddr}|${spawner.fn}|no-transform`;
        if (!seenUnresolved.has(key)) {
          seenUnresolved.add(key);
          unresolvedFireSites.push({
            table: tableAddr,
            spawner: spawner.fn,
            chunkLine: spawner.chunkLine,
            reason: `spawner variant write at ${childOff} not a provable single-param form: ${spawner.childWrites[childOff] ?? "(missing)"}`,
            callSites: spawner.callSites.length,
          });
        }
        continue;
      }
      for (const call of spawner.callSites) {
        const siteKey = `${tableAddr}|${call.caller}|${call.chunkLine}`;
        let values = null;
        let rawArg;
        if (transform.literal !== undefined) {
          values = [transform.literal];
        } else {
          rawArg = call.args?.[transform.paramIndex];
          const analysis = callerAnalysis(call.chunkLine);
          const argValues =
            rawArg !== undefined && analysis ? resolveArgValues(analysis.body, rawArg) : null;
          if (argValues !== null) values = argValues.map((v) => transform.apply(v));
        }
        if (values === null) {
          if (!seenUnresolved.has(siteKey)) {
            seenUnresolved.add(siteKey);
            unresolvedFireSites.push({
              table: tableAddr,
              fireFn: call.caller,
              chunkLine: call.chunkLine,
              spawner: spawner.fn,
              arg: rawArg ?? null,
              reason: classifyUnresolved(rawArg),
            });
          }
          continue;
        }
        const analysis = callerAnalysis(call.chunkLine);
        const guards = analysis ? borgGuardsAt(analysis.body, analysis.blocks, analysis.offset) : [];
        for (const rawValue of values) {
          const variant = mask !== null ? rawValue & mask : rawValue;
          const resKey = `${tableAddr}|${variant}|${call.caller}|${call.chunkLine}`;
          if (seenResolutions.has(resKey)) continue;
          seenResolutions.add(resKey);
          const row = variant >= 0 && variant < table.rows.length ? table.rows[variant] : null;
          const resolution = {
            table: tableAddr,
            variant,
            kind: row ? row.kind : null,
            inExtractedRows: row !== null,
            fireFn: call.caller,
            chunkLine: call.chunkLine,
            viaSpawner: spawner.fn,
            ...(transform.literal !== undefined
              ? { evidence: `spawner writes literal variant ${transform.literal}` }
              : { evidence: `arg ${JSON.stringify(rawArg)} -> ${rawValue}` }),
            borgIds: guards.map((b) => `0x${b.toString(16)}`),
            borgEvidence:
              guards.length > 0
                ? "call-site borg-id guard"
                : call.callerBorgIdCompares.length > 0
                  ? "caller-wide borg-id compares (unscoped)"
                  : "none",
            ...(guards.length === 0 && call.callerBorgIdCompares.length > 0
              ? { callerBorgIdCompares: call.callerBorgIdCompares }
              : {}),
          };
          fireSiteResolutions.push(resolution);
          if (row) {
            if (!row.firedBy) row.firedBy = [];
            if (!row.firedBy.some((f) => f.fn === resolution.fireFn && f.chunkLine === resolution.chunkLine)) {
              row.firedBy.push({
                fn: resolution.fireFn,
                chunkLine: resolution.chunkLine,
                ...(resolution.borgIds.length > 0 ? { borgIds: resolution.borgIds } : {}),
              });
            }
          }
        }
      }
    }
  }
}

// Guarded borg -> shot kind map (only call-site-scoped guards are attributed;
// caller-wide compares stay evidence-only). Joined against the borg's own
// hit.bin remap (attackHitTables.json) to confirm the kind actually exists.
const attackHitTablesPath = path.join(repoRoot, "packages/combat/src/data/attackHitTables.json");
const attackHitTables = fs.existsSync(attackHitTablesPath)
  ? JSON.parse(fs.readFileSync(attackHitTablesPath, "utf8"))
  : null;

const borgShotKinds = {};
for (const res of fireSiteResolutions) {
  if (res.borgEvidence !== "call-site borg-id guard" || res.kind === null) continue;
  for (const borgHex of res.borgIds) {
    const plId = `pl${parseInt(borgHex, 16).toString(16).padStart(4, "0")}`;
    const remapKinds = attackHitTables?.borgs?.[plId]?.kinds ?? null;
    const entry = {
      kind: res.kind,
      table: res.table,
      id: res.variant,
      fireFn: res.fireFn,
      chunkLine: res.chunkLine,
      ...(remapKinds !== null
        ? { remapHasKind: res.kind >= 0 && Object.prototype.hasOwnProperty.call(remapKinds, String(res.kind)) }
        : {}),
    };
    if (!borgShotKinds[borgHex]) borgShotKinds[borgHex] = [];
    if (!borgShotKinds[borgHex].some((e) => e.table === entry.table && e.id === entry.id && e.fireFn === entry.fireFn)) {
      borgShotKinds[borgHex].push(entry);
    }
  }
}

const rowsTotal = Object.values(outTables).reduce((n, t) => n + t.rows.length, 0);
const rowsWithProvenance = Object.values(outTables).reduce(
  (n, t) => n + t.rows.filter((r) => r.firedBy && r.firedBy.length > 0).length,
  0,
);
const rowsWithProvenanceKind0 = Object.values(outTables).reduce(
  (n, t) => n + t.rows.filter((r) => r.firedBy && r.firedBy.length > 0 && r.kind === 0).length,
  0,
);
const kind0Rows = Object.values(outTables).reduce(
  (n, t) => n + t.rows.filter((r) => r.kind === 0).length,
  0,
);
const joinChecked = Object.values(borgShotKinds).flat().filter((e) => e.remapHasKind !== undefined);
const joinOk = joinChecked.filter((e) => e.remapHasKind).length;

// ---------------------------------------------------- G RED ground truth gate
// The proven end-to-end chain must survive every regeneration: G RED (0x615)
// fire fn zz_018dcb0_ -> registry 0x80303138 id 0x2b -> kind 0 (all 5 of his
// shot variants converge on zz_018dcb0_ — movement-hit-decode-2026-07-04.md §2).
{
  const registry = outTables["0x80303138"];
  if (!registry) fail("G RED gate: global shot registry table 0x80303138 missing");
  const row = registry.rows[0x2b];
  if (!row || row.kind !== 0) {
    fail(`G RED gate: registry row 0x2b kind must be 0, got ${row ? row.kind : "missing"}`);
  }
  const gred = fireSiteResolutions.find(
    (r) =>
      r.table === "0x80303138" &&
      r.variant === 0x2b &&
      r.fireFn === "zz_018dcb0_" &&
      r.borgIds.includes("0x615") &&
      r.borgEvidence === "call-site borg-id guard",
  );
  if (!gred) fail("G RED gate: zz_018dcb0_ must resolve id 0x2b under a 0x615 call-site guard");
  const mapped = (borgShotKinds["0x615"] ?? []).find((e) => e.id === 0x2b && e.kind === 0);
  if (!mapped) fail("G RED gate: borgShotKinds[0x615] must include id 0x2b -> kind 0");
}

// ------------------------------------------------------- excluded site report
const excluded = sites
  .filter((s) => s.shape !== "table")
  .map((s) => ({
    fn: s.fn,
    chunkLine: s.chunkLine,
    shape: s.shape,
    kindArg: s.arg,
    ...(s.kind !== undefined ? { literalKind: s.kind } : {}),
  }));

const consumersTotal = Object.values(outTables).reduce((n, t) => n + t.consumers.length, 0);
const spawnersResolved = Object.values(outTables).reduce(
  (n, t) => n + t.consumers.filter((c) => c.spawners.length > 0).length,
  0,
);

const output = {
  _meta: {
    generatedBy: "scripts/gen-shot-variant-kinds.mjs",
    source: "user-data/GG4E/disc/sys/boot.dol + research/decomp/ghidra-export",
    evidence: "research/decomp/movement-hit-decode-2026-07-04.md section 2 (shot variant -> HIT kind tables)",
    pipeline: {
      consumer:
        "shot-child init fn reads kind from static DOL table: zz_008ac80_(child, table[child[variantOffset] * stride + kindOffset])",
      spawnerLinkage:
        "init fn addr found in a PTR_ state-dispatch table in the DOL; dispatcher fn (indexes it by child+0x18) is stored at child+0xc by the spawner (fire fn), which writes the variant byte; call sites of the spawner name the firing borg module",
      rowCount:
        "bounded by next corpus-referenced DOL symbol at/after rowBase+stride (row-0 field symbols live inside the first row), refined by max literal variant at spawner call sites; kind semantics: negative kind = no hitbox (spawn skipped)",
      fireFnResolution:
        "each spawner call site (fire fn) is constant-folded to the shot id/variant it passes (literals, unique-constant local assignments, single-param affine spawner transforms only); rows gain firedBy provenance; a call-site borg-id guard (`*(short*)(actor+1000) == id` scoped by brace analysis) attributes the row's kind to a borg in borgShotKinds, joined vs the borg's hit.bin remap (attackHitTables.json). Ground truth gate: G RED 0x615 -> zz_018dcb0_ -> registry 0x80303138 id 0x2b -> kind 0 (script hard-fails if broken). Non-provable sites are listed in unresolvedFireSites with reasons.",
    },
    counts: {
      totalCallSites: sites.length,
      staticTableSites: tableSites.length,
      distinctTables: Object.keys(outTables).length,
      consumersWithResolvedSpawner: spawnersResolved,
      consumersTotal,
      excludedSites: excluded.length,
      rowsTotal,
      kind0Rows,
      rowsWithFireFnProvenance: rowsWithProvenance,
      rowsWithFireFnProvenanceKind0: rowsWithProvenanceKind0,
      rowsWithFireFnProvenanceNonZeroKind: rowsWithProvenance - rowsWithProvenanceKind0,
      fireSitesResolved: fireSiteResolutions.length,
      fireSitesUnresolved: unresolvedFireSites.length,
      borgsWithGuardedShotKinds: Object.keys(borgShotKinds).length,
      guardedShotKindsJoinOk: joinOk,
      guardedShotKindsJoinChecked: joinChecked.length,
    },
  },
  tables: outTables,
  borgShotKinds,
  fireSiteResolutions,
  unresolvedFireSites,
  excludedSites: excluded,
};

fs.mkdirSync(path.dirname(outPath), { recursive: true });
fs.writeFileSync(outPath, `${JSON.stringify(output, null, 2)}\n`);
console.log(
  `wrote ${path.relative(repoRoot, outPath)} (${Object.keys(outTables).length} tables, ` +
    `${tableSites.length} static sites, ${spawnersResolved}/${consumersTotal} spawner-linked, ` +
    `${excluded.length} excluded)`,
);
console.log(
  `fire-fn provenance: ${rowsWithProvenance}/${rowsTotal} rows resolved ` +
    `(${rowsWithProvenanceKind0} kind-0, ${rowsWithProvenance - rowsWithProvenanceKind0} non-zero; ` +
    `kind-0 rows total ${kind0Rows}); ${fireSiteResolutions.length} sites resolved, ` +
    `${unresolvedFireSites.length} unresolved; borgShotKinds: ${Object.keys(borgShotKinds).length} borgs ` +
    `(remap join ${joinOk}/${joinChecked.length}); G RED 0x615 -> id 0x2b -> kind 0 gate PASSED`,
);
