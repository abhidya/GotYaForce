#!/usr/bin/env node
// run-transcript.mjs — transcript_green harness for ORDINARY (returning)
// functions whose behaviour has NO CAPTURABLE WRITE SET.
//
// ---------------------------------------------------------------------------
// WHY THIS STANDARD EXISTS
// ---------------------------------------------------------------------------
// oracle_green (run-unit.mjs) verifies a function by comparing the MEMORY IT
// WROTE. Measured over the whole ROM (tools/survey_plan_tiers.py), 4455 of
// 10954 functions store nothing a capture could compare, and thousands more
// store only through bases a capture cannot address. For those functions the
// write-comparison standard is not "hard" — it is EMPTY: there is no byte to
// compare, so an oracle_green spec over them would pass vacuously.
//
// But a function with no writes is NOT unobservable. It still has
//   (a) a RETURN VALUE,
//   (b) a CALL SEQUENCE to its out-of-unit callees, with concrete arguments,
//   (c) memory READS, which flow into (a) and (b).
// run-spine.mjs already verifies (b) for the nonterminating spine under the
// boundary_green standard. transcript_green is that same callee-boundary
// machinery generalised to functions that RETURN: the run terminates at the
// function's own return instead of at an iteration cap, and the return value
// joins the claim.
//
// ---------------------------------------------------------------------------
// WHAT transcript_green CLAIMS — AND WHAT IT DOES NOT
// ---------------------------------------------------------------------------
// VERIFIED, over the N captured cases in this corpus and nothing else:
//   * the port calls exactly the captured out-of-unit callees,
//   * in exactly the captured order,
//   * with exactly the captured arguments (i32 mod 2^32, i64 exact, floats by
//     Object.is with non-finite values carried bit-exact),
//   * and returns exactly the captured return value,
//   * and — only where the capture declares owned regions — leaves those bytes
//     byte-exact.
//
// NOT VERIFIED. This standard is STRICTLY WEAKER than oracle_green and the
// artifact says so in a machine-readable `claim` block:
//   * memory writes outside any declared owned region are NOT compared. A port
//     that computes the right transcript while scribbling elsewhere passes.
//   * reads are not independently observed; they are only constrained insofar
//     as a wrong read changes an argument or the return value.
//   * the callees themselves are STUBS replaying captured values. Nothing
//     about the callees' own behaviour is verified here.
//   * a case's live console memory is not reproduced: the port runs against the
//     static DOL arena plus whatever `seed` bytes the capture supplies. Seeded
//     bytes are GIVEN to the port, not derived by it, and are itemised in the
//     artifact.
//   * the claim is bounded by the corpus: "same transcript on N recorded cases",
//     never "same transcript on all inputs".
//
// A transcript_green run therefore NEVER prints `VERDICT: PASS` (run-unit.mjs's
// token) nor `BOUNDARY_GREEN` (run-spine.mjs's token), and NEVER writes a plain
// `<unit>.json` or `<unit>.boundary.json`. Its evidence file is
// `<unit>.<export>.transcript.json` and carries `standard: "transcript_green"`.
//
// ---------------------------------------------------------------------------
// NON-VACUITY GUARDS (the thing that makes a weak standard honest)
// ---------------------------------------------------------------------------
// A weaker standard is only worth having if it cannot pass on nothing:
//   1. a corpus with zero cases can never pass;
//   2. fewer than --min-cases cases can never pass;
//   3. a case that observes NOTHING — no callee calls, no return value, and no
//      owned-region expectation — is VACUOUS. Any vacuous case fails the run.
//      This is the guard that stops transcript_green from being trivially
//      "green" on exactly the do-nothing functions it was built to reach.
//
// ---- capture file schema (transcript_schema 1, JSONL) ----------------------
// Line 1 — header:
//   {"kind":"header","transcript_schema":1,"unit":<name>,
//    "fn":{"export":<wasm export>,"gc_addr":"0x..",
//          "params":["i32",..],"results":["i32"]|[]},
//    "wasm":<path relative to the capture file>,
//    "arena":<path relative to the capture file>,
//    "owned_regions":[{"addr":"0x..","size":N,"cases":K},..],  // ADVISORY: the
//        UNION of the per-case watch windows with a per-address case count. A
//        window is derived from a POINTER ARGUMENT, so cases legitimately watch
//        different addresses; the authoritative per-case addresses live in each
//        case's `owned_end`, and this harness counts only the bytes it actually
//        verified. May be [] — see guard 3
//    "counts":{"case":N,"call":M},
//    "source":{..capture provenance + exclusions..}}
// Lines 2..N+1 — one record per captured CALL of the function:
//   {"kind":"case","n":<0-based>,
//    "args":[..entry args..],
//    "seed":[{"addr":"0x..","b64":..},..],   // OPTIONAL, applied before replay
//    "calls":[{"i":0,"callee":<env import name>,"callee_addr":"0x..",
//              "args":[..],"ret":<value|null>,
//              "deltas":[{"addr":"0x..","b64":..},..],
//              "owned":[{"addr":"0x..","b64":..},..]},..],
//    "ret":<value|null>,                      // null/absent = void
//    "owned_end":[{"addr":"0x..","b64":..},..]}  // OPTIONAL
// Last line — end record (integrity):
//   {"kind":"end","counts":{"case":N,"call":M}}
//
// Divergence contract: the FIRST divergent case is named — case index, call
// index, expected vs actual callee/args/return (or the first mismatching owned
// byte's address). Replay STOPS at the first divergent case.
//
// Usage:
//   node run-transcript.mjs --capture <file.jsonl> [--wasm <path>] [--min-cases N]
// Env:
//   ORACLE_WASM         override the wasm path (driver substitutes {wasm})
//   ORACLE_RESULTS_DIR  override the result-artifact directory (as run-unit.mjs)
//
// Exit-code contract mirrors run-unit.mjs/run-spine.mjs: exit 0 iff verdict ==
// "pass" AND the result artifact was written. The anchored total line, printed
// ONLY on a clean run, is:
//   TRANSCRIPT TOTAL cases=<n>/<n> calls=<m>/<m> rets=<r> DIVERGENCE: none VERDICT: TRANSCRIPT_GREEN
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { loadUnit, importedMemoryLimits, applyArenaSegments } from "./lib/wasm.mjs";
import {
  sha256, hex, unbox, valueEq, fmtArgs, fmtVal, decodeRet, applyDeltas,
  parseAddr as parseAddrShared, makeBoundaryShimProxy, firstOwnedMismatch,
  fmtByte, readCaptureJsonl, gitRevOf, relPosix,
} from "./lib/boundary.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "..", "..", "..");

const TRANSCRIPT_SCHEMA = 1;
const STANDARD = "transcript_green";

// ---- args ----
const args = process.argv.slice(2);
const argOf = (name) => {
  const i = args.indexOf(name);
  return i >= 0 && i + 1 < args.length ? args[i + 1] : null;
};
const capturePath = argOf("--capture");
if (!capturePath) {
  console.error("usage: node run-transcript.mjs --capture <file.jsonl> [--wasm <path>] [--min-cases N]");
  process.exit(2);
}
const minCases = argOf("--min-cases") != null ? Number(argOf("--min-cases")) : 1;

const fail = (msg, code = 1) => { console.error(`TRANSCRIPT HARNESS ERROR: ${msg}`); process.exit(code); };
const parseAddr = (s) => parseAddrShared(s, fail);

/** Thrown by a stub when a call arrives that the captured case does not contain. */
class ExtraCall extends Error { constructor(detail) { super(detail.report); this.detail = detail; } }
/** First divergence inside a case, with the report already formatted. */
class TranscriptMismatch extends Error { constructor(detail) { super(detail.report); this.detail = detail; } }

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
  if (header.kind !== "header" || header.transcript_schema !== TRANSCRIPT_SCHEMA) {
    fail("capture has no valid transcript_schema 1 header record — an unbound capture proves nothing");
  }
  if (!header.fn?.export) fail("header.fn.export is required — the capture must name the function under test");

  const cases = [];
  let endRec = null;
  for (const l of lines.slice(1)) {
    const rec = JSON.parse(l);
    if (rec.kind === "case") {
      if (endRec != null) fail("case record after the end record");
      if (rec.n !== cases.length) fail(`case records out of order: expected n=${cases.length}, got n=${rec.n}`);
      if (!Array.isArray(rec.calls)) fail(`case n=${rec.n} has no calls array`);
      rec.calls.forEach((c, k) => {
        if (c.i !== k) fail(`case n=${rec.n} call records out of order: expected i=${k}, got i=${c.i}`);
      });
      cases.push(rec);
    } else if (rec.kind === "end") {
      if (endRec != null) fail("duplicate end record");
      endRec = rec;
    } else fail(`unknown record kind ${rec.kind}`);
  }
  if (endRec == null) fail("capture has no end record — the corpus is unbound");

  // integrity: the header's own counts and the end record's must agree with the body.
  const callTotal = cases.reduce((n, c) => n + c.calls.length, 0);
  for (const [where, counts] of [["header", header.counts], ["end record", endRec.counts]]) {
    if (counts?.case !== cases.length) fail(`capture count mismatch: ${cases.length} case records != ${where} counts.case ${counts?.case}`);
    if (counts?.call !== callTotal) fail(`capture count mismatch: ${callTotal} call records != ${where} counts.call ${counts?.call}`);
  }

  const results = header.fn.results ?? [];
  if (results.length > 1) fail(`fn declares ${results.length} results — transcript_schema 1 models at most one`);
  const isVoid = results.length === 0;

  const ownedRegions = (header.owned_regions ?? []).map((r) => ({ addr: parseAddr(r.addr), size: r.size }));

  // ---- non-vacuity guard 3 (see header): a case that observes nothing ----
  // A capture over a do-nothing function would otherwise "pass" while proving
  // nothing whatsoever — precisely the failure mode this standard exists to
  // avoid, since it targets functions with no write set.
  const vacuous = cases
    .filter((c) => c.calls.length === 0 && (c.ret == null) && !(c.owned_end?.length))
    .map((c) => c.n);

  const captureDir = path.dirname(captureAbs);
  const wasmPath = argOf("--wasm") ?? process.env.ORACLE_WASM ?? path.resolve(captureDir, header.wasm);
  const arenaPath = path.resolve(captureDir, header.arena);

  // ---- boundary stubs (shared with run-spine.mjs via lib/boundary.mjs) ----
  const state = { caseIdx: 0, callIdx: 0, calls: [] };
  let shimMem = null;
  const checkOwned = (owned, where) => {
    if (!owned?.length) return;
    const bad = firstOwnedMismatch(shimMem.u8, owned, fail);
    if (bad != null) {
      throw new TranscriptMismatch({
        n: state.caseIdx, i: state.callIdx, kind: "owned_write",
        report: `owned-write divergence in case n=${state.caseIdx} at ${where}: ` +
          `addr ${hex(bad.addr)} expected ${fmtByte(bad.expected)} got ${fmtByte(bad.got)}`,
      });
    }
  };
  const onBoundaryCall = (name, actualArgs) => {
    if (state.callIdx >= state.calls.length) {
      // A call the console never made at this point in the transcript. This is
      // a DIVERGENCE, not a terminator: unlike a spine, a returning function's
      // capture is complete, so an extra call is extra behaviour.
      throw new ExtraCall({
        n: state.caseIdx, i: state.callIdx, kind: "extra_call",
        report: `extra call in case n=${state.caseIdx} at i=${state.callIdx}: ` +
          `capture ends after ${state.calls.length} calls, port called ${name}${fmtArgs(actualArgs)}`,
      });
    }
    const rec = state.calls[state.callIdx];
    checkOwned(rec.owned, `call i=${state.callIdx}`);
    if (name !== rec.callee) {
      throw new TranscriptMismatch({
        n: state.caseIdx, i: state.callIdx, kind: "callee",
        report: `call divergence in case n=${state.caseIdx} at i=${state.callIdx}: ` +
          `expected ${rec.callee}@${rec.callee_addr}${fmtArgs(rec.args)}, got ${name}${fmtArgs(actualArgs)}`,
      });
    }
    if (actualArgs.length !== rec.args.length || !rec.args.every((e, k) => valueEq(e, actualArgs[k]))) {
      throw new TranscriptMismatch({
        n: state.caseIdx, i: state.callIdx, kind: "args",
        report: `arg divergence in case n=${state.caseIdx} at i=${state.callIdx} ${rec.callee}@${rec.callee_addr}: ` +
          `expected ${fmtArgs(rec.args)}, got ${fmtArgs(actualArgs)}`,
      });
    }
    applyDeltas(shimMem.u8, rec.deltas, fail);
    state.callIdx++;
    return decodeRet(rec.ret);
  };
  const makeShims = (ctx) => { shimMem = ctx; return makeBoundaryShimProxy(onBoundaryCall); };

  const { ex, wasmBytes } = await loadUnit({ wasmPath, arenaPath, makeShims });
  const memLim = importedMemoryLimits(wasmBytes);
  const memoryModel = memLim == null ? "exported" : memLim.shared ? "imported_shared" : "imported";
  const fn = ex[header.fn.export];
  if (typeof fn !== "function") fail(`wasm has no export ${header.fn.export}`);

  // Between cases the arena is RE-APPLIED: each captured case is an independent
  // observation of the console, so case n+1 must not run on case n's residue.
  const arena = JSON.parse(fs.readFileSync(arenaPath, "utf8"));
  const stackSave = typeof ex.emscripten_stack_get_current === "function"
    ? ex.emscripten_stack_get_current() : null;

  // ---- replay, case by case; stop at the first divergent case ----
  let divergence = null;
  let casesPassed = 0, callsMatched = 0, retsChecked = 0, seededBytes = 0;
  // Owned-region coverage is counted from the CASES THAT ACTUALLY PASSED, never
  // from the header: a watch window is derived per case from that case's pointer
  // arguments, so the header's list is a union over the corpus and would
  // overstate what each case verified.
  let ownedBytesChecked = 0;
  const ownedAddrsChecked = new Set();
  for (const c of cases) {
    state.caseIdx = c.n;
    state.callIdx = 0;
    state.calls = c.calls;
    applyArenaSegments(shimMem.u8, arena);
    // Captured live console bytes the static DOL arena cannot supply. These are
    // GIVEN to the port; the artifact itemises every one of them.
    for (const s of c.seed ?? []) {
      const b = Buffer.from(s.b64, "base64");
      shimMem.u8.set(b, parseAddr(s.addr));
      seededBytes += b.length;
    }
    if (stackSave != null && typeof ex._emscripten_stack_restore === "function") {
      ex._emscripten_stack_restore(stackSave);
    }

    let ret;
    try {
      ret = fn(...(c.args ?? []).map(unbox));
    } catch (e) {
      if (e instanceof ExtraCall || e instanceof TranscriptMismatch) { divergence = e.detail; break; }
      divergence = { n: c.n, i: state.callIdx, kind: "trap",
        report: `case n=${c.n} trapped after ${state.callIdx} calls: ${e.message}` };
      break;
    }
    if (state.callIdx !== c.calls.length) {
      divergence = { n: c.n, i: state.callIdx, kind: "short",
        report: `case n=${c.n} returned after ${state.callIdx} of ${c.calls.length} captured calls` };
      break;
    }
    // return value
    if (isVoid) {
      if (ret !== undefined) {
        divergence = { n: c.n, i: state.callIdx, kind: "ret_shape",
          report: `case n=${c.n}: capture declares a void function but the export returned ${fmtVal(ret)}` };
        break;
      }
    } else {
      if (ret === undefined) {
        divergence = { n: c.n, i: state.callIdx, kind: "ret_shape",
          report: `case n=${c.n}: capture declares result ${results[0]} but the export returned nothing` };
        break;
      }
      if (!valueEq(c.ret, ret)) {
        divergence = { n: c.n, i: state.callIdx, kind: "ret",
          report: `return divergence in case n=${c.n}: expected ${fmtVal(c.ret)}, got ${fmtVal(ret)}` };
        break;
      }
      retsChecked++;
    }
    // owned regions at return
    if (c.owned_end?.length) {
      try { checkOwned(c.owned_end, "return"); }
      catch (e) {
        if (e instanceof TranscriptMismatch) { divergence = e.detail; break; }
        throw e;
      }
      for (const o of c.owned_end) {
        ownedBytesChecked += Buffer.from(o.b64, "base64").length;
        ownedAddrsChecked.add(parseAddr(o.addr));
      }
    }
    casesPassed++;
    callsMatched += c.calls.length;
  }

  // ---- verdict ----
  const enoughCases = cases.length >= Math.max(1, minCases);
  const pass = divergence == null && enoughCases && vacuous.length === 0;
  let verdictNote = null;
  if (!enoughCases) verdictNote = `corpus has ${cases.length} cases, below the --min-cases floor of ${minCases}`;
  else if (vacuous.length > 0) {
    verdictNote = `${vacuous.length} VACUOUS case(s) (no calls, no return value, no owned expectation) — ` +
      `first n=${vacuous[0]}; a case that observes nothing cannot support a claim`;
  }

  // ---- log (divergence first, then the anchored total) ----
  if (divergence != null) console.log(`TRANSCRIPT DIVERGENCE: ${divergence.report}`);
  if (verdictNote != null) console.log(`TRANSCRIPT VACUITY: ${verdictNote}`);
  if (pass) {
    console.log(`TRANSCRIPT TOTAL cases=${casesPassed}/${cases.length} calls=${callsMatched}/${callTotal} ` +
      `rets=${retsChecked} DIVERGENCE: none VERDICT: TRANSCRIPT_GREEN`);
  } else {
    console.log(`TRANSCRIPT TOTAL cases=${casesPassed}/${cases.length} calls=${callsMatched}/${callTotal} ` +
      `rets=${retsChecked} DIVERGENCE: ${divergence ? `case ${divergence.n} call ${divergence.i}` : "none"} VERDICT: FAIL`);
  }

  // ---- result artifact ----
  // standard transcript_green, in its OWN filename namespace and carrying an
  // explicit machine-readable statement of what it does and does not claim.
  const result = {
    result_schema: 1,
    standard: STANDARD,
    unit: header.unit,
    fn: header.fn.export,
    generated_at: new Date().toISOString(),
    claim: {
      // Whether this RUN established the claim. A `claim` block on a failed run
      // describes the standard, not an achievement.
      established: pass,
      summary: `same out-of-unit call transcript and return value as the console on ${cases.length} recorded cases`,
      verifies: [
        "the set, order and arguments of every out-of-unit callee call",
        "the function's own return value",
        ownedBytesChecked > 0
          ? `byte-exactness of ${ownedBytesChecked} owned-region bytes at return, `
            + `over ${ownedAddrsChecked.size} distinct address(es), on the cases that passed`
          : ownedRegions.length > 0
            ? `NO owned-region bytes were reached: the corpus declares ${ownedRegions.length} `
              + `watch region(s) but the run stopped before any case completed`
            : "no memory bytes (no case in this corpus carried an owned-region expectation)",
      ],
      does_not_verify: [
        "memory writes outside the declared owned regions",
        "memory reads (constrained only insofar as they change an argument or the return value)",
        "the behaviour of the callees themselves — they are stubs replaying captured values",
        "live console memory: the port runs on the static DOL arena plus the itemised seed bytes",
        "any input outside the recorded corpus",
      ],
      weaker_than: "oracle_green",
      weaker_because: "oracle_green compares the function's memory write set byte-for-byte; "
        + "transcript_green compares only the observable call transcript and return value, "
        + "which is all that exists for a function with no capturable write set. "
        + "A transcript_green result must never be recorded, counted or reported as oracle_green.",
      bounded_by_corpus: { cases: cases.length, calls: callTotal },
    },
    harness: {
      entry: "research/decomp/oracle-harness/run-transcript.mjs",
      git_rev: gitRevOf(root),
      sha256: sha256(fs.readFileSync(path.join(here, "run-transcript.mjs"))),
      min_cases: minCases,
    },
    wasm: { path: wasmPath, sha256: sha256(wasmBytes), memory_model: memoryModel },
    arena: { path: relPosix(root, arenaPath), sha256: sha256(fs.readFileSync(arenaPath)) },
    capture: {
      file: relPosix(root, captureAbs), sha256: sha256(captureRaw),
      cases: cases.length, calls: callTotal,
      source: header.source ?? null,
    },
    function: {
      export: header.fn.export, gc_addr: header.fn.gc_addr ?? null,
      params: header.fn.params ?? null, results,
      void: isVoid,
    },
    // ADVISORY, straight from the capture header: the union of watch windows
    // over the corpus, NOT a set every case checked.
    declared_owned_regions: ownedRegions.map((r) => ({ addr: hex(r.addr), size: r.size })),
    // What this run actually verified.
    owned_bytes_checked: ownedBytesChecked,
    owned_addresses_checked: ownedAddrsChecked.size,
    seeded_bytes: seededBytes,
    cases_passed: casesPassed,
    calls_matched: callsMatched,
    returns_checked: retsChecked,
    vacuous_cases: vacuous,
    divergence: divergence == null ? null
      : { n: divergence.n, i: divergence.i, kind: divergence.kind, report: divergence.report },
    verdict_note: verdictNote,
    verdict: pass ? "pass" : "fail",
  };
  const outDir = resultsDir();
  fs.mkdirSync(outDir, { recursive: true });
  // Distinct filename namespace: never `<unit>.json` (oracle_green) and never
  // `<unit>.boundary.json` (boundary_green). A transcript result cannot
  // overwrite, or be read as, either.
  const safeFn = header.fn.export.replace(/[^\w.-]/g, "_");
  fs.writeFileSync(path.join(outDir, `${header.unit}.${safeFn}.transcript.json`),
    JSON.stringify(result, null, 1) + "\n");
  process.exitCode = pass ? 0 : 1;
}
