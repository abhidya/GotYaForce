#!/usr/bin/env node
// run-spine.mjs — boundary_green harness for nonterminating spine functions
// (design v5 AMENDMENT I3, docs/playable-port-design.md). oracle_green's
// per-call replay standard (run-unit.mjs) cannot terminate on a spine like
// run_main_game_loop (0x800527d8, do{...}while(true)) — there is no return to
// compare. boundary_green instead replays the spine's CALLEE BOUNDARY: every
// out-of-unit callee is stubbed to (a) assert the call arrives in the captured
// order with the captured args, (b) apply the callee's captured memory deltas
// to the arena, (c) return the captured return value; the run is cut after K
// captured iterations by the iteration-counting stub (the spine never
// returns), and the spine-owned writes must be byte-exact at every captured
// boundary and at the cut. boundary_green is recorded DISTINCTLY from
// oracle_green (result artifact carries standard:"boundary_green"); it never
// silently upgrades to an oracle_green claim.
//
// ---- capture file schema (spine_schema 1, JSONL — one JSON record per line) ----
// Line 1 — header:
//   {"kind":"header","spine_schema":1,"unit":<name>,
//    "spine":{"export":<wasm export name>,"gc_addr":"0x..","args":[..entry args..]},
//    "wasm":<path relative to the capture file>,   // default; --wasm/ORACLE_WASM override
//    "arena":<path relative to the capture file>,  // DOL-sourced arena JSON ({segments})
//    "iterations":K,                               // loop iterations the capture covers
//    "terminator":{"mode":"call_cap"},             // cut mechanism: after all counts.call
//                                                  // captured calls are serviced, the NEXT
//                                                  // incoming call terminates the run (the
//                                                  // spine looping onward is itself asserted)
//    "owned_regions":[{"addr":"0x..","size":N},..],// spine-owned memory (the spine's own writes)
//    "counts":{"call":N}}                          // integrity: number of call records
// Lines 2..N+1 — calls, in boundary order:
//   {"kind":"call","i":<0-based>,"iter":<0-based iteration>,
//    "callee":<env import name>,"callee_addr":"0x..",   // GC address of the callee
//    "args":[..],              // captured arg values; i32 compared mod 2^32 (>>>0),
//                              // i64 captured as decimal string, floats via Object.is;
//                              // a NON-FINITE float is BOXED bit-exact as
//                              // {"t":"f64"|"f32","bits":"<hex>"} (JSON has no
//                              // NaN/Infinity) and is unboxed before comparison
//    "ret":<value|null>,       // null/absent = void; {"t":"i64","v":"<dec>"} for i64
//    "deltas":[{"addr":"0x..","b64":..},..],  // memory writes attributed to this callee,
//                                             // applied by the stub before returning
//    "owned":[{"addr":"0x..","b64":..},..]}   // OPTIONAL: expected owned-region bytes at
//                                             // this boundary (checked on call arrival,
//                                             // before the deltas apply)
// Last line — end state:
//   {"kind":"end","owned":[{"addr":"0x..","b64":..},..]} // owned-region bytes at the cut;
//                                                        // must cover every owned_region
//                                                        // exactly (byte-exact or fail)
//
// Divergence contract: the FIRST divergent call is named — index, iteration,
// expected vs actual callee/args (or the first mismatching owned byte's
// address). A spine that returns before the cut is a failure. A spine that
// stops calling out entirely cannot be preempted from JS — run under an
// external timeout.
//
// Usage:
//   node run-spine.mjs --capture <file.jsonl> [--wasm <path>]
// Env:
//   ORACLE_WASM         override the wasm path (driver substitutes {wasm})
//   ORACLE_RESULTS_DIR  override the result-artifact directory (as run-unit.mjs)
//
// Exit-code contract mirrors run-unit.mjs: exit 0 iff verdict == "pass" AND the
// result artifact (<unit>.boundary.json) was written; the anchored total line,
// printed ONLY on a clean run, is:
//   SPINE TOTAL calls=<n>/<n> iterations=<k> DIVERGENCE: none VERDICT: BOUNDARY_GREEN
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { loadUnit, importedMemoryLimits } from "./lib/wasm.mjs";
// The value/format/compare machinery below is SHARED with run-transcript.mjs
// (standard transcript_green) so the two callee-boundary standards cannot drift
// apart in what "same callee" or "same argument" means. The divergence wording,
// the verdict token and the result `standard` field stay HERE — nothing shared
// can make boundary_green evidence readable as another standard's.
import {
  sha256, hex, unbox, valueEq, fmtArgs, decodeRet, applyDeltas,
  parseAddr as parseAddrShared, makeBoundaryShimProxy, firstOwnedMismatch,
  fmtByte, readCaptureJsonl, gitRevOf, relPosix,
} from "./lib/boundary.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "..", "..", "..");

// ---- args ----
const args = process.argv.slice(2);
const argOf = (name) => {
  const i = args.indexOf(name);
  return i >= 0 && i + 1 < args.length ? args[i + 1] : null;
};
const capturePath = argOf("--capture");
if (!capturePath) {
  console.error("usage: node run-spine.mjs --capture <file.jsonl> [--wasm <path>]");
  process.exit(2);
}

const fail = (msg, code = 1) => { console.error(`SPINE HARNESS ERROR: ${msg}`); process.exit(code); };

/** Terminator: thrown by the iteration-counting stub once the capture is exhausted. */
class SpineDone extends Error {}
/** First divergence, with the report already formatted. */
class SpineMismatch extends Error {
  constructor(detail) { super(detail.report); this.detail = detail; }
}

const parseAddr = (s) => parseAddrShared(s, fail);

try {
  await main();
} catch (e) {
  console.error(e.stack ?? String(e));
  process.exit(1);
}

function resultsDir() {
  return process.env.ORACLE_RESULTS_DIR
    ? path.resolve(process.env.ORACLE_RESULTS_DIR)
    : path.join(root, "research", "decomp", "data", "oracle-results");
}

async function main() {
  // ---- capture load + shape validation ----
  const captureAbs = path.resolve(capturePath);
  const { raw: captureRaw, lines } = readCaptureJsonl(captureAbs, fail);
  const header = JSON.parse(lines[0]);
  if (header.kind !== "header" || header.spine_schema !== 1) {
    fail("capture has no valid spine_schema 1 header record — an unbound capture proves nothing");
  }
  if (header.terminator?.mode !== "call_cap") {
    fail(`unsupported terminator mode ${header.terminator?.mode} (spine_schema 1 defines call_cap)`);
  }
  const records = [];
  let endRec = null;
  for (const l of lines.slice(1)) {
    const rec = JSON.parse(l);
    if (rec.kind === "call") {
      if (endRec != null) fail("call record after the end record");
      if (rec.i !== records.length) fail(`call records out of order: expected i=${records.length}, got i=${rec.i}`);
      records.push(rec);
    } else if (rec.kind === "end") {
      if (endRec != null) fail("duplicate end record");
      endRec = rec;
    } else fail(`unknown record kind ${rec.kind}`);
  }
  if (endRec == null) fail("capture has no end record — the cut state is unbound");
  if (records.length !== header.counts?.call) {
    fail(`capture count mismatch: ${records.length} call records != header counts.call ${header.counts?.call}`);
  }
  const ownedRegions = (header.owned_regions ?? []).map((r) => ({ addr: parseAddr(r.addr), size: r.size }));
  // end record must cover every owned region exactly — a spine-owned byte the
  // end state does not bind is a spine-owned write the capture cannot verify.
  const endByAddr = new Map((endRec.owned ?? []).map((o) => [parseAddr(o.addr), Buffer.from(o.b64, "base64")]));
  for (const r of ownedRegions) {
    const b = endByAddr.get(r.addr);
    if (!b || b.length !== r.size) fail(`end record does not cover owned region ${hex(r.addr)}+${r.size}`);
  }

  const captureDir = path.dirname(captureAbs);
  const wasmPath = argOf("--wasm") ?? process.env.ORACLE_WASM ?? path.resolve(captureDir, header.wasm);
  const arenaPath = path.resolve(captureDir, header.arena);

  // ---- boundary stubs ----
  // Every function import dispatches into the sequence checker under its own
  // import name — a Proxy target, so imports the capture never names still get
  // order-checked (arriving out of order IS the divergence, not an unshimmed
  // throw). loadUnit supplies env.memory itself on the threads-target path.
  const state = { i: 0 };
  let shimMem = null; // loadUnit's memCtx — u8 is live for both memory models
  const checkOwned = (owned, atCall) => {
    if (!owned) return;
    const bad = firstOwnedMismatch(shimMem.u8, owned, fail);
    if (bad != null) {
      throw new SpineMismatch({
        i: atCall, kind: "owned_write",
        report: `owned-write divergence at ${atCall === -1 ? "end-of-capture cut" : `call i=${atCall}`}: ` +
          `addr ${hex(bad.addr)} expected ${fmtByte(bad.expected)} got ${fmtByte(bad.got)}`,
      });
    }
  };
  const onBoundaryCall = (name, actualArgs) => {
    if (state.i >= records.length) throw new SpineDone(); // the call-cap terminator
    const rec = records[state.i];
    checkOwned(rec.owned, state.i);
    if (name !== rec.callee) {
      throw new SpineMismatch({
        i: state.i, kind: "callee",
        report: `call divergence at i=${state.i} (iter ${rec.iter}): expected ${rec.callee}@${rec.callee_addr}${fmtArgs(rec.args)}, ` +
          `got ${name}${fmtArgs(actualArgs)}`,
      });
    }
    if (actualArgs.length !== rec.args.length
      || !rec.args.every((e, k) => valueEq(e, actualArgs[k]))) {
      throw new SpineMismatch({
        i: state.i, kind: "args",
        report: `arg divergence at i=${state.i} (iter ${rec.iter}) ${rec.callee}@${rec.callee_addr}: ` +
          `expected ${fmtArgs(rec.args)}, got ${fmtArgs(actualArgs)}`,
      });
    }
    applyDeltas(shimMem.u8, rec.deltas, fail);
    state.i++;
    return decodeRet(rec.ret);
  };
  const makeShims = (ctx) => {
    shimMem = ctx;
    return makeBoundaryShimProxy(onBoundaryCall);
  };

  const { ex, wasmBytes } = await loadUnit({ wasmPath, arenaPath, makeShims });
  const memLim = importedMemoryLimits(wasmBytes);
  const memoryModel = memLim == null ? "exported" : memLim.shared ? "imported_shared" : "imported";
  const spineFn = ex[header.spine.export];
  if (typeof spineFn !== "function") fail(`wasm has no export ${header.spine.export}`);

  // ---- drive the spine to the cut ----
  let divergence = null;
  let cut = false;
  try {
    spineFn(...(header.spine.args ?? []).map(unbox));
    // a spine that returns is not the captured nonterminating spine
    divergence = { i: state.i, kind: "returned",
      report: `spine returned after ${state.i} calls — captured spine never returns` };
  } catch (e) {
    if (e instanceof SpineDone) {
      cut = true;
      try { checkOwned(endRec.owned, -1); } catch (m) {
        if (m instanceof SpineMismatch) divergence = m.detail; else throw m;
      }
    } else if (e instanceof SpineMismatch) {
      divergence = e.detail;
    } else throw e;
  }
  if (divergence == null && state.i !== records.length) {
    divergence = { i: state.i, kind: "short",
      report: `cut arrived after ${state.i} of ${records.length} captured calls` };
  }

  const pass = divergence == null && cut;
  const ownedBytes = ownedRegions.reduce((n, r) => n + r.size, 0);

  // ---- log (divergence first, then the anchored total) ----
  if (divergence != null) console.log(`SPINE DIVERGENCE: ${divergence.report}`);
  if (pass) {
    console.log(`SPINE TOTAL calls=${state.i}/${records.length} iterations=${header.iterations} DIVERGENCE: none VERDICT: BOUNDARY_GREEN`);
  } else {
    console.log(`SPINE TOTAL calls=${state.i}/${records.length} iterations=${header.iterations} DIVERGENCE: ${divergence ? "at call " + divergence.i : "?"} VERDICT: FAIL`);
  }

  // ---- result artifact — standard boundary_green, distinct from oracle_green ----
  const gitRev = gitRevOf(root);
  const result = {
    result_schema: 1,
    standard: "boundary_green",
    unit: header.unit,
    generated_at: new Date().toISOString(),
    harness: {
      entry: "research/decomp/oracle-harness/run-spine.mjs",
      git_rev: gitRev,
      sha256: sha256(fs.readFileSync(path.join(here, "run-spine.mjs"))),
    },
    wasm: { path: wasmPath, sha256: sha256(wasmBytes), memory_model: memoryModel },
    arena: { path: relPosix(root, arenaPath), sha256: sha256(fs.readFileSync(arenaPath)) },
    capture: { file: relPosix(root, captureAbs), sha256: sha256(captureRaw),
      calls: records.length, iterations: header.iterations, terminator: header.terminator.mode },
    spine: { export: header.spine.export, gc_addr: header.spine.gc_addr },
    owned_regions: ownedRegions.map((r) => ({ addr: hex(r.addr), size: r.size })),
    owned_bytes: ownedBytes,
    calls_matched: state.i,
    divergence: divergence == null ? null : { i: divergence.i, kind: divergence.kind, report: divergence.report },
    verdict: pass ? "pass" : "fail",
  };
  const outDir = resultsDir();
  fs.mkdirSync(outDir, { recursive: true });
  fs.writeFileSync(path.join(outDir, `${header.unit}.boundary.json`), JSON.stringify(result, null, 1) + "\n");
  process.exitCode = pass ? 0 : 1;
}
