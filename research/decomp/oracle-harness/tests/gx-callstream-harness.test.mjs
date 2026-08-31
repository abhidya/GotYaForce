// gx-callstream-harness.test.mjs — the DELIBERATE-RED rehearsal for
// gx_callstream_green, mirroring transcript-harness.test.mjs and
// spine-harness.test.mjs.
//
// A verifier that cannot fail is worse than none. This file drives
// run-gx-callstream.mjs against the committed console capture
// (corpora/gx-rom-unit.zz_0027c34_.gx-callstream.jsonl, recorded from the real
// game in Dolphin) and against MUTANTS OF THAT CAPTURE — one per divergence
// class the standard claims to catch.
//
// WHY THE MUTANT IS THE CAPTURE AND NOT THE WASM. The other harnesses mutate
// the port because the port is the thing under test. Here the comparison is
// between two STREAMS, and a divergence is a difference between them: which
// side moved does not change what the comparator has to notice. Mutating the
// capture also needs no emsdk, so this rehearsal runs on a clean checkout,
// which is the whole reason the console capture is committed.
//
// It also pins the things that keep a GX result from being read as a wasm-unit
// tier: the `standard` field, the verdict token, the filename namespace, and
// the machine-readable claim block that says in words that NO PIXEL is verified.
//
// Run: node research/decomp/oracle-harness/tests/run-oracle-tests.mjs
import test from "node:test";
import assert from "node:assert/strict";
import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import { spawnSync } from "node:child_process";
import { fileURLToPath } from "node:url";

const here = path.dirname(fileURLToPath(import.meta.url));
const harnessDir = path.resolve(here, "..");
const capture = path.join(harnessDir, "corpora", "gx-rom-unit.zz_0027c34_.gx-callstream.jsonl");
const RESULT_NAME = "gx-rom-unit.zz_0027c34_.gx-callstream.json";

const readCapture = () =>
  fs.readFileSync(capture, "utf8").split(/\r?\n/).filter((l) => l.trim()).map((l) => JSON.parse(l));

/** Write a mutated capture into a scratch dir and run the harness on it. */
const runOn = (mutate) => {
  const scratch = fs.mkdtempSync(path.join(process.env.ORACLE_TEST_TMP_ROOT ?? os.tmpdir(), "gx-cs-"));
  let capturePath = capture;
  if (mutate) {
    const recs = readCapture();
    mutate(recs);
    capturePath = path.join(scratch, "mutant.jsonl");
    fs.writeFileSync(capturePath, recs.map((r) => JSON.stringify(r)).join("\n") + "\n");
  }
  const argv = ["run-gx-callstream.mjs", "--capture", capturePath];
  // The header's wasm path is relative to corpora/; a mutant lives elsewhere.
  if (mutate) {
    argv.push("--wasm",
      path.resolve(harnessDir, "..", "..", "..",
        "packages/rom-runtime/test/fixtures/gx-rom-unit/gx_rom_unit.threads.wasm"));
  }
  const res = spawnSync(process.execPath, argv, {
    cwd: harnessDir,
    env: { ...process.env, ORACLE_RESULTS_DIR: scratch },
    encoding: "utf8",
  });
  const log = (res.stdout ?? "") + (res.stderr ?? "");
  const resultPath = path.join(scratch, RESULT_NAME);
  const result = fs.existsSync(resultPath) ? JSON.parse(fs.readFileSync(resultPath, "utf8")) : null;
  return { status: res.status, log, result };
};

const firstDrawing = (recs) => recs.slice(1).find((r) => r.events.some((e) => e.k === "wgpipe"));

test("gx_callstream_green: the gate-lowered ROM unit reproduces the console stream", () => {
  const { status, log, result } = runOn(null);
  assert.equal(status, 0, log);
  assert.equal(result.verdict, "pass");
  assert.equal(result.verdict_token, "GX_CALLSTREAM_GREEN");
  assert.equal(result.divergence, null);
  assert.equal(result.invocations_matched, result.capture.invocations);
  assert.ok(result.events_matched > 0);
  assert.equal(result.events_matched, result.events_captured);
  assert.match(log, /VERDICT: GX_CALLSTREAM_GREEN/);
  // the console's own vertex bytes went through the host's FIFO decoder
  assert.equal(result.console_stream_decoded_by_host.fifo.droppedBytes, 0);
  assert.equal(result.console_stream_decoded_by_host.fifo.pendingBytes, 0);
  assert.ok(result.console_stream_decoded_by_host.fifo.primitives > 0);
});

test("the result cannot be read as a wasm-unit verification tier", () => {
  const { result } = runOn(null);
  assert.equal(result.standard, "gx_callstream_green");
  for (const forbidden of ["oracle_green", "boundary_green", "transcript_green", "compile_only"]) {
    assert.notEqual(result.standard, forbidden);
    assert.notEqual(result.verdict_token, forbidden.toUpperCase());
  }
  assert.match(result.standard_note, /NOT one of the wasm-unit verification tiers/);
  // the claim must SAY, in machine-readable form, that no pixel is verified
  assert.ok(result.claim.does_not_verify.some((s) => /ANY PIXEL/.test(s)));
  assert.ok(result.claim.verifies.some((s) => /write-gather-pipe LOWERING/.test(s)));
  assert.equal(typeof result.claim.behavioural_claim_of_the_adapters, "string");
  assert.match(result.claim.behavioural_claim_of_the_adapters, /NONE\./);
});

test("INDUCED RED: a wrong GX argument value diverges", () => {
  const { status, result, log } = runOn((recs) => {
    const iv = firstDrawing(recs);
    const call = iv.events.find((e) => e.k === "call" && e.callee === "gnt4_GXSetZMode_bl");
    call.args[1] = 3; // the ROM passes 7
  });
  assert.equal(status, 1, log);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.kind, "arg");
  assert.match(result.divergence.report, /gnt4_GXSetZMode_bl/);
});

test("INDUCED RED: a wrong write-gather-pipe VALUE diverges", () => {
  const { status, result } = runOn((recs) => {
    const iv = firstDrawing(recs);
    const w = iv.events.find((e) => e.k === "wgpipe" && e.width === 4);
    w.value = (w.value ^ 0xff) >>> 0;
  });
  assert.equal(status, 1);
  assert.equal(result.divergence.kind, "wgpipe_value");
});

test("INDUCED RED: a wrong write-gather-pipe WIDTH diverges", () => {
  // The lowering error that matters most: a 16-bit store lowered as a 32-bit
  // one puts different bytes on the wire for the same number, and the FIFO
  // then mis-frames every following vertex.
  const { status, result } = runOn((recs) => {
    const iv = firstDrawing(recs);
    const w = iv.events.find((e) => e.k === "wgpipe" && e.width === 2);
    w.width = 4;
    w.import = "__gf_gx_wgpipe_u32";
  });
  assert.equal(status, 1);
  assert.equal(result.divergence.kind, "wgpipe_width");
});

test("INDUCED RED: a wrong call ORDER diverges", () => {
  const { status, result } = runOn((recs) => {
    const iv = firstDrawing(recs);
    const i = iv.events.findIndex((e) => e.k === "call");
    const t = iv.events[i];
    iv.events[i] = iv.events[i + 1];
    iv.events[i + 1] = t;
  });
  assert.equal(status, 1);
  assert.ok(["callee", "arg", "arity"].includes(result.divergence.kind), result.divergence.kind);
});

test("INDUCED RED: an extra console event is reported as missing on the port side", () => {
  const { status, result } = runOn((recs) => {
    const iv = firstDrawing(recs);
    iv.events.push({ k: "wgpipe", at: "0xdeadbeef", width: 2, import: "__gf_gx_wgpipe_u16", value: 1 });
    recs[0].counts.wgpipe += 1;
  });
  assert.equal(status, 1);
  assert.equal(result.divergence.kind, "missing");
});

test("INDUCED RED: a stack-relative pointer replaced by a static address diverges", () => {
  // The structural check earns its place here: the console passes a pointer
  // into its own frame, the port passes one into the wasm stack, and the only
  // thing comparable is that the port's pointer is a real, distinct, correctly
  // spaced buffer. Claiming the console passed a STATIC address instead must
  // therefore fail.
  const { status, result } = runOn((recs) => {
    const iv = firstDrawing(recs);
    for (const e of iv.events) {
      if (e.k !== "call") continue;
      for (let j = 0; j < e.args.length; j++) {
        if (e.args[j] && typeof e.args[j] === "object") e.args[j] = 0x803c0f40;
      }
    }
  });
  assert.equal(status, 1);
  assert.equal(result.divergence.kind, "arg");
});

test("NON-VACUITY: a capture in which the guard never opened cannot pass", () => {
  const { status, result, log } = runOn((recs) => {
    for (const iv of recs.slice(1)) iv.events = [];
    recs[0].counts.call = 0;
    recs[0].counts.wgpipe = 0;
  });
  assert.equal(status, 1, log);
  assert.equal(result.verdict, "fail");
  assert.ok(result.vacuity_failures.some((v) => /GX call and a write-gather-pipe write/.test(v)),
    JSON.stringify(result.vacuity_failures));
});

test("NON-VACUITY: an empty capture cannot pass", () => {
  const { status, result } = runOn((recs) => {
    recs.length = 1;
    recs[0].counts = { invocation: 0, call: 0, wgpipe: 0, store: 0 };
    recs[0].invocations = 0;
  });
  assert.equal(status, 1);
  // An artifact IS written — a `claim` block on a failed run describes the
  // standard, not an achievement (the transcript_green precedent) — but it can
  // never say `pass`, and it must name why.
  assert.equal(result.verdict, "fail");
  assert.equal(result.verdict_token, "GX_CALLSTREAM_DIVERGENT");
  assert.equal(result.claim.established, false);
  assert.ok(result.vacuity_failures.length > 0);
  assert.ok(result.vacuity_failures.some((v) => /--min-invocations/.test(v)),
    JSON.stringify(result.vacuity_failures));
});

test("NON-VACUITY: header counts that drift from the records cannot pass", () => {
  const { status, result } = runOn((recs) => {
    recs[0].counts.wgpipe += 7;
  });
  assert.equal(status, 1);
  assert.ok(result.vacuity_failures.some((v) => /counts\.wgpipe/.test(v)));
});

// ===========================================================================
// gx_framebuffer_equivalent — the DIFFERENTIAL console-frame measurement.
//
// Same discipline as above: the real committed console frames must produce the
// measured result, and each thing the measurement claims to catch must actually
// make it fail. The mutants here go through the HOST: changing the captured
// GXSetBlendMode arguments changes what the host predicts, which is exactly the
// failure this measurement exists to catch — a wrong [SDK] blend-factor
// reading.
// ===========================================================================

const xfbControl = path.join(harnessDir, "corpora", "gx-rom-unit.zz_0027c34_.xfb-control.json");
const xfbTreatment = path.join(harnessDir, "corpora", "gx-rom-unit.zz_0027c34_.xfb-treatment.json");
const FB_RESULT_NAME = "gx-rom-unit.zz_0027c34_.gx-framebuffer.json";

const runFb = ({ mutateCapture = null, mutateFrames = null, extra = [] } = {}) => {
  const scratch = fs.mkdtempSync(path.join(process.env.ORACLE_TEST_TMP_ROOT ?? os.tmpdir(), "gx-fb-"));
  let cap = capture, ctl = xfbControl, trt = xfbTreatment;
  if (mutateCapture) {
    const recs = readCapture();
    mutateCapture(recs);
    cap = path.join(scratch, "mutant.jsonl");
    fs.writeFileSync(cap, recs.map((r) => JSON.stringify(r)).join("\n") + "\n");
  }
  if (mutateFrames) {
    const c = JSON.parse(fs.readFileSync(xfbControl, "utf8"));
    const t = JSON.parse(fs.readFileSync(xfbTreatment, "utf8"));
    mutateFrames(c, t);
    ctl = path.join(scratch, "control.json"); trt = path.join(scratch, "treatment.json");
    fs.writeFileSync(ctl, JSON.stringify(c)); fs.writeFileSync(trt, JSON.stringify(t));
  }
  const argv = ["run-gx-framebuffer.mjs", "--control", ctl, "--treatment", trt, "--capture", cap, ...extra];
  const res = spawnSync(process.execPath, argv, {
    cwd: harnessDir, env: { ...process.env, ORACLE_RESULTS_DIR: scratch }, encoding: "utf8",
  });
  const p = path.join(scratch, FB_RESULT_NAME);
  return {
    status: res.status,
    log: (res.stdout ?? "") + (res.stderr ?? ""),
    result: fs.existsSync(p) ? JSON.parse(fs.readFileSync(p, "utf8")) : null,
  };
};

test("gx_framebuffer_equivalent: the console frames match the host's prediction", () => {
  const { status, log, result } = runFb();
  assert.equal(status, 0, log);
  assert.equal(result.verdict, "pass");
  assert.equal(result.verdict_token, "GX_FRAMEBUFFER_EQUIVALENT");
  assert.equal(result.region_matches_host_prediction, true);
  assert.equal(result.pixels_changed_outside_host_prediction, 0);
  assert.ok(result.deltas.channel_samples > 100000, "the measurement must cover a real frame");
  assert.ok(result.deltas.p99 <= result.harness.tolerance_per_channel);
  // the ceiling is restated, in the artifact, in the design's own words
  assert.match(result.claim.ceiling, /framebuffer-equivalent, NEVER pixel-identical/);
  assert.ok(result.claim.does_not_verify.some((s) => /the rest of the frame/.test(s)));
});

test("INDUCED RED: a wrong blend-factor reading blows the measurement apart", () => {
  // GXSetBlendMode(1, 4, 5, 0). Reading the DST factor as SRCALPHA instead of
  // INVSRCALPHA would attenuate the frame to 7/255 of itself. If the
  // measurement could not tell those apart it would not be evidence about the
  // [SDK] blend-factor numbering at all.
  const { status, result } = runFb({
    mutateCapture: (recs) => {
      const iv = firstDrawing(recs);
      iv.events.find((e) => e.k === "call" && e.callee === "gnt4_GXSetBlendMode_bl").args[2] = 4;
    },
  });
  assert.equal(status, 1);
  assert.equal(result.verdict, "fail");
  assert.ok(result.deltas.p50 > 20, `expected a gross delta, got p50=${result.deltas.p50}`);
});

test("INDUCED RED: a wrong decoded quad extent is caught as a region mismatch", () => {
  // Halve the quad's height in the console's own vertex bytes: 0x1c0 -> 0xe0.
  const { status, result } = runFb({
    mutateCapture: (recs) => {
      const iv = firstDrawing(recs);
      for (const e of iv.events) if (e.k === "wgpipe" && e.value === 0x1c0) e.value = 0xe0;
    },
  });
  assert.equal(status, 1);
  assert.equal(result.region_matches_host_prediction, false);
  assert.ok(result.pixels_changed_outside_host_prediction > 0);
});

test("NON-VACUITY: two identical console frames cannot pass", () => {
  const { status, result } = runFb({
    mutateFrames: (c, t) => { t.frame.b64 = c.frame.b64; },
  });
  assert.equal(status, 1);
  assert.ok(result.vacuity_failures.some((v) => /IDENTICAL/.test(v)),
    JSON.stringify(result.vacuity_failures));
});

test("NON-VACUITY: frames from different frame indices are refused outright", () => {
  const { status, result } = runFb({
    mutateFrames: (c, t) => { t.frame.vi_hit = c.frame.vi_hit + 1; },
  });
  assert.equal(status, 2);
  assert.equal(result, null);
});
