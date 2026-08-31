#!/usr/bin/env node
// run-gx-callstream.mjs — the GX CALL-STREAM oracle.
//
// THE CIRCULARITY THIS BREAKS. docs/gx-hle-host.md §1/§6.3: the GX HLE host
// translates 87.1 % of the ROM's static GX call sites and verifies 0 % of them.
// Its pixel assertions are predicted from the same understanding of GX that
// produced the implementation, so they are SELF-CONSISTENCY checks: if the TEV
// selector numbering is wrong, the shader and the prediction are wrong together
// and the check still passes. Only console-derived evidence breaks that.
//
// WHAT THIS HARNESS COMPARES. `research/tools/dolphin-trace/capture_gx.py`
// records, from the real game in Dolphin, the ordered stream one ROM draw
// function emits at the SDK seam — every GX call with its PowerPC-register
// arguments, and every write-gather-pipe store with its width and value. This
// harness runs the ASSEMBLY GATE'S OWN wasm build of that same ROM function
// against the real GX adapters, seeded with the console's own memory, and
// requires the stream the host receives to be IDENTICAL.
//
// WHAT THAT DOES AND DOES NOT ESTABLISH — stated here and again, in
// machine-readable form, in every result artifact's `claim` block:
//
//   VERIFIES   the write-gather-pipe LOWERING (which stores became which
//              imports, at which widths, in which order and carrying which
//              values), the GX call sequence and its ARGUMENT MARSHALLING, the
//              guard the ROM function evaluates, and the GameCube-address ->
//              linear-memory mapping for the pointers it passes.
//   DOES NOT   verify a single pixel. Nothing here reads a framebuffer. It says
//              the host is FED correctly; it says nothing about whether the
//              adapters, the TEV shader generator, the texture decoder or the
//              rasterizer DO the right thing with what they are fed. The
//              [SDK]-assumed enum values in gx/enums.ts are untouched by this
//              standard: an argument value of 7 is compared as the number 7,
//              not as a depth-compare function.
//
// STANDARD AND NAMESPACE. `gx_callstream_green` is its own standard with its
// own verdict token (GX_CALLSTREAM_GREEN), its own result filename suffix
// (`.gx-callstream.json`) and its own `standard` field. It is NOT one of the
// wasm-unit verification tiers, it is not comparable with them, and it must
// never be summed with, quoted as, or promoted into `oracle_green`,
// `boundary_green` or `transcript_green` — those compare a function's write
// set / callee boundary / return value against the console, over a corpus of
// inputs. This compares one function's SEAM EMISSION. See
// docs/verification-status.md §1.
//
// ---- capture schema (gx_stream_schema 1, JSONL) ----
// Line 1 — header:
//   {"kind":"header","gx_stream_schema":1,"name":..,
//    "function":{"export":..,"gc_addr":"0x.."},
//    "wasm":<path relative to the capture file>,
//    "invocations":N,
//    "counts":{"invocation":N,"call":N,"wgpipe":N,"store":N},
//    "binding":{..},"source":{..}}
// Lines 2..N+1 — one per observed invocation:
//   {"kind":"invocation","n":i,"entry_sp":"0x..","exit_sp":"0x..",
//    "staged":[{"addr":..,"was":..,"now":..}]|null,
//    "reads":[{"name":..,"addr":"0x..","size":N,"elem_width":N,"b64":..}|
//             {"name":..,"unresolved":true}],
//    "events":[{"k":"call","callee":..,"args":[..]}|
//              {"k":"wgpipe","import":..,"width":..,"value":..}|
//              {"k":"store","addr":..,"width":..,"value":..}]}
//
// A `{"k":"sp","off":N}` argument is a pointer into the function's own console
// stack frame. Console stack addresses and the wasm module's linear stack are
// different address spaces, so those are compared STRUCTURALLY: the aliasing
// pattern and the pairwise offsets must match, the port value must be a real
// non-zero pointer, and it may not collide with any address the console passed
// as a plain value. That is weaker than value equality and the artifact says so.
//
// Usage:
//   node run-gx-callstream.mjs --capture <file.jsonl> [--wasm <path>]
//                              [--min-invocations N] [--keep-bundle]
// Env:
//   ORACLE_RESULTS_DIR  override the result-artifact directory (as run-unit.mjs)
//
// Exit 0 iff verdict == "pass" AND the artifact was written. The anchored total
// line, printed only on a clean run:
//   GX CALLSTREAM TOTAL invocations=<n>/<n> events=<n>/<n> DIVERGENCE: none VERDICT: GX_CALLSTREAM_GREEN
import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import { createRequire } from "node:module";
import { fileURLToPath, pathToFileURL } from "node:url";
import { importedMemoryLimits } from "./lib/wasm.mjs";
import { sha256, hex, gitRevOf, relPosix } from "./lib/boundary.mjs";

const STANDARD = "gx_callstream_green";
const VERDICT_TOKEN = "GX_CALLSTREAM_GREEN";
const SCHEMA = 1;

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "..", "..", "..");
const pkgRoot = path.join(root, "packages", "rom-runtime");

const args = process.argv.slice(2);
const argOf = (n) => {
  const i = args.indexOf(n);
  return i >= 0 && i + 1 < args.length ? args[i + 1] : null;
};
const capturePath = argOf("--capture");
if (!capturePath) {
  console.error("usage: node run-gx-callstream.mjs --capture <file.jsonl> [--wasm <path>]");
  process.exit(2);
}
const minInvocations = Number(argOf("--min-invocations") ?? 1);
const keepBundle = args.includes("--keep-bundle");

const die = (msg) => {
  console.error(`GX CALLSTREAM ABORT: ${msg}`);
  process.exit(2);
};

// ---- capture ----
const captureAbs = path.resolve(capturePath);
if (!fs.existsSync(captureAbs)) die(`no capture at ${captureAbs}`);
const captureRaw = fs.readFileSync(captureAbs);
const lines = captureRaw.toString("utf8").split(/\r?\n/).filter((l) => l.trim().length);
if (!lines.length) die("capture file is empty");
let records;
try {
  records = lines.map((l) => JSON.parse(l));
} catch (e) {
  die(`capture is not JSONL: ${e.message}`);
}
const header = records[0];
if (header?.kind !== "header") die("first capture line is not a header");
if (header.gx_stream_schema !== SCHEMA) die(`capture is not gx_stream_schema ${SCHEMA}`);
const invocations = records.slice(1).filter((r) => r.kind === "invocation");

// ---- non-vacuity, BEFORE anything is run ----
// A standard that can pass on nothing is not a standard. Each of these has a
// concrete failure it prevents: an emulator boot that never reached the
// function, a guarded draw path that never opened, a capture truncated by a
// dead stub, and a header whose counts drifted from its records.
const vacuity = [];
if (invocations.length < minInvocations) {
  vacuity.push(`${invocations.length} invocation(s) captured, --min-invocations is ${minInvocations}`);
}
if (header.counts?.invocation !== invocations.length) {
  vacuity.push(`header counts.invocation=${header.counts?.invocation} but ${invocations.length} records`);
}
const capCalls = invocations.reduce((n, iv) => n + iv.events.filter((e) => e.k === "call").length, 0);
const capPipes = invocations.reduce((n, iv) => n + iv.events.filter((e) => e.k === "wgpipe").length, 0);
const capPipeBytes = invocations.reduce(
  (n, iv) => n + iv.events.filter((e) => e.k === "wgpipe").reduce((m, e) => m + e.width, 0), 0);
if (header.counts?.call !== capCalls) vacuity.push(`header counts.call=${header.counts?.call} but ${capCalls} call events`);
if (header.counts?.wgpipe !== capPipes) vacuity.push(`header counts.wgpipe=${header.counts?.wgpipe} but ${capPipes} wgpipe events`);
const drawing = invocations.filter(
  (iv) => iv.events.some((e) => e.k === "call") && iv.events.some((e) => e.k === "wgpipe"));
if (!drawing.length) {
  vacuity.push(
    "no captured invocation emitted BOTH a GX call and a write-gather-pipe write — a capture in which "
    + "the ROM function only ever took its guard's false branch proves nothing about the seam");
}
if (capPipeBytes <= 0) vacuity.push("zero write-gather-pipe bytes captured");

// ---- wasm ----
const wasmPath = path.resolve(argOf("--wasm") ?? path.join(path.dirname(captureAbs), header.wasm));
if (!fs.existsSync(wasmPath)) die(`no wasm at ${wasmPath}`);
const wasmBytes = fs.readFileSync(wasmPath);
const limits = importedMemoryLimits(wasmBytes);
if (!limits) die("the ROM unit does not import env.memory — this harness drives the threads shape");

// ---- bundle the GX host for node ----
// The host is TypeScript in packages/rom-runtime/src/gx/. esbuild is already
// this repo's way of running that source outside a browser (see
// scripts/smoke-gx-host-phase.mjs and the battle-scene selfcheck).
const bundleDir = fs.mkdtempSync(path.join(os.tmpdir(), "gx-callstream-"));
const bundlePath = path.join(bundleDir, "gxCallstreamHost.mjs");
const pkgRequire = createRequire(path.join(pkgRoot, "package.json"));
{
  const esbuild = await import(pathToFileURL(pkgRequire.resolve("esbuild")).href);
  await esbuild.build({
    entryPoints: [path.join(pkgRoot, "src", "gx", "oracle", "gxCallstreamHost.ts")],
    outfile: bundlePath,
    bundle: true,
    format: "esm",
    platform: "node",
    target: "es2022",
    logLevel: "silent",
  });
}
const { createGxCallstreamHost, GX_NO_BEHAVIOURAL_CLAIM } = await import(pathToFileURL(bundlePath).href);

// ---- comparison ----
const isSp = (v) => v !== null && typeof v === "object" && v.k === "sp";
const fmt = (v) => (isSp(v) ? `sp+0x${(v.off >>> 0).toString(16)}` : hex(v));
const fmtArgs = (a) => `(${a.map(fmt).join(", ")})`;

function compareInvocation(expected, actual) {
  // Structural bookkeeping for stack-relative pointer arguments.
  const spSeen = []; // {off, portValue}
  const plainValues = new Set();
  for (const e of expected) {
    if (e.k !== "call") continue;
    for (const a of e.args) if (!isSp(a)) plainValues.add(a >>> 0);
  }
  const n = Math.max(expected.length, actual.length);
  for (let i = 0; i < n; i++) {
    const exp = expected[i];
    const act = actual[i];
    if (!exp) return { i, kind: "extra", report: `port emitted an extra event at index ${i}: ${JSON.stringify(act)}` };
    if (!act) return { i, kind: "missing", report: `port stopped after ${actual.length} events; console had ${JSON.stringify(exp)} at index ${i}` };
    if (exp.k !== act.k) {
      return { i, kind: "kind", report: `event ${i}: console emitted a ${exp.k}, port emitted a ${act.k}` };
    }
    if (exp.k === "wgpipe") {
      if (exp.import !== act.import || exp.width !== act.width) {
        return {
          i, kind: "wgpipe_width",
          report: `event ${i}: console wrote ${exp.width} byte(s) through ${exp.import}, `
            + `port wrote ${act.width} byte(s) through ${act.import} — the write-gather-pipe `
            + `lowering picked a different width, which puts different bytes on the wire`,
        };
      }
      if ((exp.value >>> 0) !== (act.value >>> 0)) {
        return {
          i, kind: "wgpipe_value",
          report: `event ${i} (${exp.import}): console wrote ${hex(exp.value)}, port wrote ${hex(act.value)}`,
        };
      }
      continue;
    }
    if (exp.callee !== act.callee) {
      return { i, kind: "callee", report: `event ${i}: console called ${exp.callee}, port called ${act.callee}` };
    }
    if (exp.args.length !== act.args.length) {
      return {
        i, kind: "arity",
        report: `event ${i} (${exp.callee}): console passed ${exp.args.length} argument(s), `
          + `port passed ${act.args.length} — the wasm import signature and the ROM's own `
          + `call site disagree about this entry point's arity`,
      };
    }
    for (let j = 0; j < exp.args.length; j++) {
      const e = exp.args[j];
      const a = act.args[j] >>> 0;
      if (isSp(e)) {
        if (a === 0) {
          return { i, kind: "sp_null", report: `event ${i} (${exp.callee}) arg ${j}: console passed a stack pointer, port passed 0` };
        }
        if (plainValues.has(a)) {
          return {
            i, kind: "sp_collision",
            report: `event ${i} (${exp.callee}) arg ${j}: port passed ${hex(a)}, which the console `
              + `passed elsewhere as a PLAIN address — a stack local cannot alias a static one`,
          };
        }
        for (const prev of spSeen) {
          if (a - prev.portValue !== e.off - prev.off) {
            return {
              i, kind: "sp_layout",
              report: `event ${i} (${exp.callee}) arg ${j}: console stack offsets differ by `
                + `${e.off - prev.off}, port pointers differ by ${a - prev.portValue} — the port is `
                + `not passing the same buffer the console passed`,
            };
          }
        }
        spSeen.push({ off: e.off, portValue: a });
        continue;
      }
      if ((e >>> 0) !== a) {
        return {
          i, kind: "arg",
          report: `event ${i} (${exp.callee}) arg ${j}: console ${hex(e)}, port ${hex(a)}   `
            + `console ${exp.callee}${fmtArgs(exp.args)} vs port ${act.callee}${fmtArgs(act.args)}`,
        };
      }
    }
  }
  return null;
}

// ---- replay ----
const memory = new WebAssembly.Memory({
  initial: limits.initial,
  ...(limits.maximum !== undefined ? { maximum: limits.maximum } : {}),
  shared: limits.shared,
});
const u8 = new Uint8Array(memory.buffer);

const portHost = createGxCallstreamHost(memory);
const module = await WebAssembly.compile(wasmBytes);
const importNames = WebAssembly.Module.imports(module)
  .filter((i) => i.kind === "function")
  .map((i) => i.name);
const missing = importNames.filter((n) => !portHost.adapterNames().includes(n));
if (missing.length) die(`the ROM unit imports symbols this host does not service: ${missing.join(", ")}`);

const instance = await WebAssembly.instantiate(module, {
  env: { memory, ...portHost.imports(importNames) },
});
instance.exports._initialize?.();
const entry = instance.exports[header.function.export];
if (typeof entry !== "function") die(`${wasmPath} does not export ${header.function.export}`);

// The console's stream, pushed through a SECOND host. Its purpose is evidence,
// not verdict: it shows what the host's write-gather-pipe decoder makes of the
// console's OWN vertex bytes, which is the first time this decoder has ever
// been fed bytes it did not also generate.
const consoleHost = createGxCallstreamHost(memory);

const results = [];
let divergence = null;
let seededBytes = 0;
let eventsMatched = 0;
let capturedEvents = 0;

for (const iv of invocations) {
  // Seed the console's own memory at the addresses the plan declared. This is
  // the difference between an oracle and the browser self-test, which pokes
  // values a human chose: every byte below was read out of the live console at
  // the moment this invocation started, byte-swapped element-wise to the
  // arena's little-endian order by the capture tool.
  for (const r of iv.reads ?? []) {
    if (!r.b64) continue;
    const bytes = Buffer.from(r.b64, "base64");
    u8.set(bytes, parseInt(r.addr, 16) >>> 0);
    seededBytes += bytes.length;
  }
  portHost.reset();
  let threw = null;
  try {
    entry();
  } catch (e) {
    threw = String(e?.message ?? e);
  }
  const actual = [...portHost.stream];
  const expected = iv.events;
  capturedEvents += expected.length;
  const d = threw
    ? { i: actual.length, kind: "threw", report: `port threw servicing the stream: ${threw}` }
    : compareInvocation(expected, actual);
  if (!d) eventsMatched += expected.length;
  results.push({
    n: iv.n,
    console_events: expected.length,
    port_events: actual.length,
    guard_open: expected.some((e) => e.k === "wgpipe"),
    matched: !d,
    divergence: d,
  });
  if (d && !divergence) divergence = { n: iv.n, ...d };
}

// Feed the console's own captured stream through a clean host, for the record.
let consoleDecode = null;
let consoleDecodeError = null;
try {
  const first = drawing[0];
  if (first) {
    const spScratch = 0x80600000; // scratch region convention, as the trace specs use
    consoleHost.gx.beginFrame();
    for (const e of first.events) {
      if (e.k === "call") {
        consoleHost.call(e.callee, e.args.map((a) => (isSp(a) ? (spScratch + a.off) >>> 0 : a >>> 0)));
      } else if (e.k === "wgpipe") {
        consoleHost.call(e.import, [e.value >>> 0]);
      }
    }
    consoleHost.gx.endFrame();
    consoleDecode = {
      invocation: first.n,
      fifo: {
        primitives: consoleHost.gx.fifo.primitiveCount,
        droppedBytes: consoleHost.gx.fifo.droppedBytes,
        pendingBytes: consoleHost.gx.fifo.pendingBytes,
      },
      records: consoleHost.backend.records.map((r) => ({
        primitive: r.primitive, primitiveByte: r.primitiveByte, vertexCount: r.vertexCount,
        firstVertex: r.firstVertex, firstColor: r.firstColor,
        cullMode: r.cullMode, projectionType: r.projectionType,
      })),
      vertices: consoleHost.backend.primitives.map((p) => ({
        positions: Array.from(p.positions),
        colors: p.colors ? Array.from(p.colors) : null,
      })),
      diagnostics: [...consoleHost.backend.diagnostics],
    };
  }
} catch (e) {
  consoleDecodeError = String(e?.message ?? e);
}

if (!keepBundle) fs.rmSync(bundleDir, { recursive: true, force: true });

// A decode that dropped or stranded FIFO bytes means the host's decoder cannot
// consume the console's OWN byte stream. That is a real failure of this
// standard: the stream comparison would still pass, and the frame would still
// be wrong.
const decodeFaults = [];
if (consoleDecodeError) decodeFaults.push(`decoding the console stream threw: ${consoleDecodeError}`);
if (consoleDecode) {
  if (consoleDecode.fifo.droppedBytes) decodeFaults.push(`${consoleDecode.fifo.droppedBytes} console FIFO byte(s) dropped by the host decoder`);
  if (consoleDecode.fifo.pendingBytes) decodeFaults.push(`${consoleDecode.fifo.pendingBytes} console FIFO byte(s) left unconsumed`);
  if (!consoleDecode.fifo.primitives) decodeFaults.push("the host decoder produced no primitive from the console's vertex bytes");
} else if (!consoleDecodeError) {
  decodeFaults.push("no drawing invocation to decode");
}

const invocationsMatched = results.filter((r) => r.matched).length;
const pass = !vacuity.length && !divergence && !decodeFaults.length
  && invocationsMatched === invocations.length && invocations.length > 0;

const staged = invocations.some((iv) => iv.staged?.length) || Boolean(header.source?.state_staging);

const result = {
  result_schema: 1,
  standard: STANDARD,
  // Spelled out so no reader and no grep can mistake this for a wasm-unit tier.
  standard_note:
    "gx_callstream_green is the GX SDK-seam standard. It is NOT one of the wasm-unit verification "
    + "tiers (compile_only / oracle_green / boundary_green / transcript_green), is not comparable "
    + "with them, and must never be summed with or reported as any of them.",
  name: header.name,
  fn: header.function.export,
  generated_at: new Date().toISOString(),
  claim: {
    established: pass,
    summary:
      `the gate-lowered wasm build of ${header.function.export} emits the SAME SDK-seam stream as the `
      + `console — same GX calls in the same order with the same arguments, and the same `
      + `write-gather-pipe writes at the same widths with the same values — over `
      + `${invocations.length} recorded invocation(s)`,
    verifies: [
      "the write-gather-pipe LOWERING: which stores became which __gf_gx_wgpipe_* import, "
        + `at which width, in which order, carrying which value (${capPipes} write(s), ${capPipeBytes} byte(s))`,
      `the GX call sequence and its ARGUMENT MARSHALLING (${capCalls} call(s) compared value-for-value)`,
      "the guard the ROM function evaluates, replayed against the console's own memory",
      "the GameCube-address to linear-memory mapping for every static pointer the function passes",
      "that the host's FIFO decoder consumes the console's OWN vertex byte stream completely "
        + "(no dropped bytes, no bytes left buffered) and assembles a primitive from it",
    ],
    does_not_verify: [
      "ANY PIXEL. No framebuffer is read on either side. A matching call stream means the host is "
        + "FED correctly; it says nothing about what the adapters, the TEV shader generator, the "
        + "texture decoder or the WebGL rasterizer DO with what they are fed.",
      "the MEANING of any argument value: a 7 is compared as the number 7, not as a depth-compare "
        + "function. Every [SDK]-labelled enum value in gx/enums.ts is untouched by this standard.",
      "the behaviour of the GX entry points themselves — what the console's SDK did with these "
        + "arguments is outside the capture",
      "any ROM function other than this one, and any game state other than the one captured",
      staged
        ? "an UNSTAGED observation: this capture staged game state to open the function's guard "
          + "(source.state_staging). The executed code, its call stream and its pipe bytes are the "
          + "ROM's own; the guard's value was not."
        : "coverage outside the recorded invocations",
    ],
    relationship_to_other_standards:
      "orthogonal, not weaker or stronger. oracle_green / boundary_green / transcript_green compare a "
      + "ported function's write set, callee boundary or return value against the console. This "
      + "compares one function's GRAPHICS SEAM EMISSION, which none of them can see, because a "
      + "write-gather-pipe store is neither a call nor a MEM1 write.",
    bounded_by_corpus: {
      invocations: invocations.length,
      calls: capCalls,
      wgpipe_writes: capPipes,
      wgpipe_bytes: capPipeBytes,
      drawing_invocations: drawing.length,
    },
    behavioural_claim_of_the_adapters: GX_NO_BEHAVIOURAL_CLAIM,
  },
  harness: {
    entry: "research/decomp/oracle-harness/run-gx-callstream.mjs",
    git_rev: gitRevOf(root),
    sha256: sha256(fs.readFileSync(path.join(here, "run-gx-callstream.mjs"))),
    gx_host_entry: "packages/rom-runtime/src/gx/oracle/gxCallstreamHost.ts",
    gx_host_sha256: sha256(fs.readFileSync(path.join(pkgRoot, "src", "gx", "oracle", "gxCallstreamHost.ts"))),
    min_invocations: minInvocations,
  },
  wasm: {
    path: relPosix(root, wasmPath),
    sha256: sha256(wasmBytes),
    memory_pages: limits,
  },
  capture: {
    file: relPosix(root, captureAbs),
    sha256: sha256(captureRaw),
    invocations: invocations.length,
    counts: header.counts,
    binding: header.binding,
    source: header.source ?? null,
  },
  state_staging: header.source?.state_staging ?? null,
  seeded_bytes: seededBytes,
  invocations_matched: invocationsMatched,
  events_matched: eventsMatched,
  events_captured: capturedEvents,
  per_invocation: results,
  // Evidence, not verdict input beyond the fault list: what the host's decoder
  // makes of the console's own vertex bytes.
  console_stream_decoded_by_host: consoleDecode,
  decode_faults: decodeFaults,
  vacuity_failures: vacuity,
  divergence,
  verdict: pass ? "pass" : "fail",
  verdict_token: pass ? VERDICT_TOKEN : "GX_CALLSTREAM_DIVERGENT",
};

const outDir = process.env.ORACLE_RESULTS_DIR
  ? path.resolve(process.env.ORACLE_RESULTS_DIR)
  : path.join(root, "research", "decomp", "data", "oracle-results");
fs.mkdirSync(outDir, { recursive: true });
// Distinct filename namespace: never `<unit>.json` (oracle_green), never
// `<unit>.boundary.json` (boundary_green), never `<unit>.<fn>.transcript.json`
// (transcript_green). A GX result cannot overwrite, or be read as, any of them.
const safe = String(header.name).replace(/[^\w.-]/g, "_");
const safeFn = String(header.function.export).replace(/[^\w.-]/g, "_");
const outFile = path.join(outDir, `${safe}.${safeFn}.gx-callstream.json`);
fs.writeFileSync(outFile, JSON.stringify(result, null, 1) + "\n");

for (const v of vacuity) console.error(`GX CALLSTREAM VACUOUS: ${v}`);
for (const f of decodeFaults) console.error(`GX CALLSTREAM DECODE FAULT: ${f}`);
if (divergence) {
  console.error(`GX CALLSTREAM DIVERGENCE invocation=${divergence.n} kind=${divergence.kind}`);
  console.error(`  ${divergence.report}`);
}
console.log(`artifact: ${relPosix(root, outFile)}`);
if (consoleDecode) {
  console.log(
    `console stream decoded by the host: ${consoleDecode.fifo.primitives} primitive(s), `
    + `${consoleDecode.fifo.droppedBytes} dropped, ${consoleDecode.fifo.pendingBytes} pending; `
    + `${JSON.stringify(consoleDecode.records)}`);
}
if (pass) {
  console.log(
    `GX CALLSTREAM TOTAL invocations=${invocationsMatched}/${invocations.length} `
    + `events=${eventsMatched}/${capturedEvents} DIVERGENCE: none VERDICT: ${VERDICT_TOKEN}`);
}
process.exitCode = pass ? 0 : 1;
