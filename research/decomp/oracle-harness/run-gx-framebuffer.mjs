#!/usr/bin/env node
// run-gx-framebuffer.mjs — the GX FRAMEBUFFER-EQUIVALENCE measurement.
//
// WHAT IS AND IS NOT REACHABLE, measured rather than assumed.
//
// A whole-frame comparison of a host-rendered frame against a console frame is
// STRUCTURALLY unreachable today, and not because of tooling: the GX HLE host
// renders the output of ONE gate-lowered ROM function (docs/gx-hle-host.md
// §5.2), while a console frame is the output of the entire game. There is no
// host frame to put beside it. That is a porting-progress fact, not a
// measurement one, and it does not improve by trying harder here.
//
// What IS reachable is a DIFFERENTIAL comparison, and it is a real one:
//
//   control    one console frame with the ROM's fade-overlay draw path OFF
//   treatment  the SAME frame, same savestate, same frame index, with the
//              ROM's own guard word staged so its own draw path runs
//
// The difference between those two console frames is exactly what Flipper did
// with the GX call stream this repo also captured (capture_gx.py), and the host
// can predict that difference from its OWN latched state: its decoded quad
// geometry, its decoded vertex colour, and its interpretation of the blend
// enums. Comparing the prediction against the measured difference tests the
// host against the console over ~300 000 real pixels.
//
// THE CLAIM BAR IS FIXED BY THE DESIGN and is not negotiable here:
// "framebuffer-equivalent, never pixel-identical" (playable-port-design.md V3
// non-fatal note 1). So this harness states a tolerance UP FRONT, reports the
// MEASURED delta distribution whether or not it clears it, and never tunes the
// threshold to make a run pass. The measured numbers are the artifact; the
// verdict is a secondary read on them.
//
// STANDARD: `gx_framebuffer_equivalent`, its own token
// (GX_FRAMEBUFFER_EQUIVALENT), its own filename suffix
// (`.gx-framebuffer.json`). Not a wasm-unit tier, not comparable with one, and
// deliberately a DIFFERENT standard from `gx_callstream_green` — that one
// compares a call stream and explicitly disclaims pixels; this one compares
// pixels over one draw and disclaims everything else in the frame.
//
// Usage:
//   node run-gx-framebuffer.mjs --control <xfb.json> --treatment <xfb.json>
//                               --capture <callstream.jsonl> [--tolerance N]
import fs from "node:fs";
import os from "node:os";
import path from "node:path";
import { createRequire } from "node:module";
import { fileURLToPath, pathToFileURL } from "node:url";
import { sha256, gitRevOf, relPosix } from "./lib/boundary.mjs";

const STANDARD = "gx_framebuffer_equivalent";
const TOKEN = "GX_FRAMEBUFFER_EQUIVALENT";

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "..", "..", "..");
const pkgRoot = path.join(root, "packages", "rom-runtime");

const args = process.argv.slice(2);
const argOf = (n) => { const i = args.indexOf(n); return i >= 0 && i + 1 < args.length ? args[i + 1] : null; };
const die = (m) => { console.error(`GX FRAMEBUFFER ABORT: ${m}`); process.exit(2); };

const controlPath = argOf("--control");
const treatmentPath = argOf("--treatment");
const capturePath = argOf("--capture");
if (!controlPath || !treatmentPath || !capturePath) {
  die("usage: --control <xfb.json> --treatment <xfb.json> --capture <callstream.jsonl>");
}
// The tolerance is DECLARED, not fitted. 4/255 per 8-bit RGB channel is the
// slack a chroma-subsampled YUV round trip plus one 8-bit fixed-point blend
// rounding can produce on its own; it is stated before the numbers are read and
// is not moved afterwards.
const TOLERANCE = Number(argOf("--tolerance") ?? 4);

const loadXfb = (p) => {
  const raw = fs.readFileSync(p);
  const j = JSON.parse(raw.toString("utf8"));
  if (j.gx_framebuffer_schema !== 1) die(`${p} is not gx_framebuffer_schema 1`);
  if (!j.frame) die(`${p} captured no frame`);
  return { json: j, raw, bytes: Buffer.from(j.frame.b64, "base64") };
};
const control = loadXfb(controlPath);
const treatment = loadXfb(treatmentPath);
const W = control.json.frame.width, H = control.json.frame.height;
if (treatment.json.frame.width !== W || treatment.json.frame.height !== H) die("frame geometry differs");
if (control.bytes.length !== W * H * 2 || treatment.bytes.length !== W * H * 2) die("frame size is not W*H*2");
if (control.json.frame.vi_hit !== treatment.json.frame.vi_hit) {
  die(`frames are from different frame indices (${control.json.frame.vi_hit} vs ${treatment.json.frame.vi_hit}) — `
    + "the differential is only meaningful between the SAME frame of two identical runs");
}

// ---- the host's own prediction ----
// Everything below comes out of the host, not out of this file: the quad's
// geometry from the FIFO decoder, its colour from the decoded vertices, and the
// blend equation from the host's reading of the blend enums.
const captureAbs = path.resolve(capturePath);
const captureRaw = fs.readFileSync(captureAbs);
const recs = captureRaw.toString("utf8").split(/\r?\n/).filter((l) => l.trim()).map((l) => JSON.parse(l));
const capHeader = recs[0];
const drawing = recs.slice(1).find((r) => r.kind === "invocation" && r.events.some((e) => e.k === "wgpipe"));
if (!drawing) die("the call-stream capture contains no drawing invocation");

const bundleDir = fs.mkdtempSync(path.join(os.tmpdir(), "gx-fb-"));
const bundlePath = path.join(bundleDir, "gxCallstreamHost.mjs");
{
  const req = createRequire(path.join(pkgRoot, "package.json"));
  const esbuild = await import(pathToFileURL(req.resolve("esbuild")).href);
  await esbuild.build({
    entryPoints: [path.join(pkgRoot, "src", "gx", "oracle", "gxCallstreamHost.ts")],
    outfile: bundlePath, bundle: true, format: "esm", platform: "node",
    target: "es2022", logLevel: "silent",
  });
}
const { createGxCallstreamHost, GX_NO_BEHAVIOURAL_CLAIM } = await import(pathToFileURL(bundlePath).href);

// The arena has to be the composed module's size for the same reason the ROM
// unit's does: the shim maps GameCube addresses straight to linear-memory
// offsets, and this stream passes 0x803c0f40 to GXSetProjection. It is then
// SEEDED from the console's own captured read set, so the host reads what the
// console read.
const memory = new WebAssembly.Memory({ initial: 32890, maximum: 32890, shared: true });
const arena = new Uint8Array(memory.buffer);
for (const r of drawing.reads ?? []) {
  if (!r.b64) continue;
  arena.set(Buffer.from(r.b64, "base64"), parseInt(r.addr, 16) >>> 0);
}
const host = createGxCallstreamHost(memory);
const SP_SCRATCH = 0x80600000; // scratch region convention, as the trace specs use
host.gx.beginFrame();
for (const e of drawing.events) {
  if (e.k === "call") {
    host.call(e.callee, e.args.map((a) => (a && typeof a === "object" && a.k === "sp" ? SP_SCRATCH + a.off : a >>> 0)));
  } else if (e.k === "wgpipe") {
    host.call(e.import, [e.value >>> 0]);
  }
}
host.gx.endFrame();
const prim = host.backend.primitives[0];
if (!prim) die("the host decoded no primitive from the console stream");
const st = prim.state;
const colors = prim.colors;
if (!colors) die("the decoded primitive carries no vertex colour");

// The quad's screen extent, from the host's OWN decoded vertices. The ROM's
// projection for this draw is orthographic and its vertices are already in
// screen units (the ROM writes 0/0x280/0x1c0), which is why an extent read
// straight off the decoded positions is the host's prediction and not an
// assumption made here.
let x0 = Infinity, y0 = Infinity, x1 = -Infinity, y1 = -Infinity;
for (let i = 0; i < prim.vertexCount; i++) {
  x0 = Math.min(x0, prim.positions[i * 3]); x1 = Math.max(x1, prim.positions[i * 3]);
  y0 = Math.min(y0, prim.positions[i * 3 + 1]); y1 = Math.max(y1, prim.positions[i * 3 + 1]);
}
const predicted = { x0, y0, x1, y1 };

// The blend, from the host's latched state and its enum reading.
const GX_BM_BLEND = 1, GX_BL_SRCALPHA = 4, GX_BL_INVSRCALPHA = 5;
const srcRGBA = [colors[0], colors[1], colors[2], colors[3]];
const blend = { mode: st.blendMode, src: st.blendSrc, dst: st.blendDst };
const factor = (f, sa) => (f === 0 ? 0 : f === 1 ? 1 : f === GX_BL_SRCALPHA ? sa : f === GX_BL_INVSRCALPHA ? 1 - sa : null);
const sa = srcRGBA[3] / 255;
const fs_ = blend.mode === GX_BM_BLEND ? factor(blend.src, sa) : 1;
const fd_ = blend.mode === GX_BM_BLEND ? factor(blend.dst, sa) : 0;
const blendable = fs_ !== null && fd_ !== null;

// ---- YUY2 -> RGB (BT.601 studio swing, the VI's own encoding) ----
const clamp8 = (v) => (v < 0 ? 0 : v > 255 ? 255 : v);
function toRgb(buf, out) {
  for (let p = 0, o = 0; p < buf.length; p += 4, o += 6) {
    const y0v = buf[p], cb = buf[p + 1] - 128, y1v = buf[p + 2], cr = buf[p + 3] - 128;
    for (const [k, yv] of [[0, y0v], [3, y1v]]) {
      const y = 1.164 * (yv - 16);
      out[o + k] = clamp8(Math.round(y + 1.596 * cr));
      out[o + k + 1] = clamp8(Math.round(y - 0.813 * cr - 0.391 * cb));
      out[o + k + 2] = clamp8(Math.round(y + 2.018 * cb));
    }
  }
}
const rgbC = new Uint8Array(W * H * 3), rgbT = new Uint8Array(W * H * 3);
toRgb(control.bytes, rgbC);
toRgb(treatment.bytes, rgbT);

// ---- measured change region (the console's own answer) ----
let mx0 = Infinity, my0 = Infinity, mx1 = -Infinity, my1 = -Infinity, changed = 0;
const rowChanged = new Uint8Array(H);
for (let y = 0; y < H; y++) {
  for (let x = 0; x < W; x++) {
    const i = (y * W + x) * 2;
    // compare in the RAW YUY2 bytes: a chroma pair covers two pixels, so a
    // change is attributed to both, which is the encoding's own granularity
    const j = i - (i % 4);
    if (control.bytes[j] !== treatment.bytes[j] || control.bytes[j + 1] !== treatment.bytes[j + 1]
      || control.bytes[j + 2] !== treatment.bytes[j + 2] || control.bytes[j + 3] !== treatment.bytes[j + 3]) {
      changed++; rowChanged[y] = 1;
      if (x < mx0) mx0 = x; if (x > mx1) mx1 = x;
      if (y < my0) my0 = y; if (y > my1) my1 = y;
    }
  }
}
const measured = { x0: mx0, y0: my0, x1: mx1 + 1, y1: my1 + 1, changedPixels: changed };

// ---- per-channel delta: host prediction vs console ----
const hist = new Array(256).fill(0);
let inside = 0, outside = 0, outsideChanged = 0, sumAbs = 0, maxAbs = 0, within = 0, samples = 0;
for (let y = 0; y < H; y++) {
  for (let x = 0; x < W; x++) {
    const o = (y * W + x) * 3;
    const isInside = x >= predicted.x0 && x < predicted.x1 && y >= predicted.y0 && y < predicted.y1;
    if (!isInside) {
      outside++;
      if (rgbC[o] !== rgbT[o] || rgbC[o + 1] !== rgbT[o + 1] || rgbC[o + 2] !== rgbT[o + 2]) outsideChanged++;
      continue;
    }
    inside++;
    for (let c = 0; c < 3; c++) {
      const dst = rgbC[o + c];
      const pred = blendable ? clamp8(Math.round(srcRGBA[c] * fs_ + dst * fd_)) : dst;
      const d = Math.abs(pred - rgbT[o + c]);
      hist[d]++; sumAbs += d; samples++;
      if (d > maxAbs) maxAbs = d;
      if (d <= TOLERANCE) within++;
    }
  }
}
const pct = (p) => {
  let seen = 0; const target = p * samples;
  for (let d = 0; d < 256; d++) { seen += hist[d]; if (seen >= target) return d; }
  return 255;
};
const deltas = {
  channel_samples: samples,
  mean_abs: Number((sumAbs / Math.max(1, samples)).toFixed(4)),
  p50: pct(0.5), p90: pct(0.9), p95: pct(0.95), p99: pct(0.99), max: maxAbs,
  within_tolerance: within,
  within_tolerance_pct: Number(((100 * within) / Math.max(1, samples)).toFixed(4)),
  histogram_0_to_15: hist.slice(0, 16),
};

// A pure structural fit of the multiplier, independent of the host: solve
// (t - base) / (c - base) in YUV space over well-separated samples. This is
// what the CONSOLE did, expressed as one number, and it is reported next to the
// host's own srcAlpha so the two can be read against each other.
const ks = [];
for (let p = 0; p < control.bytes.length; p += 4) {
  const row = Math.floor(p / (W * 2));
  if (!rowChanged[row]) continue;
  for (const [k, base] of [[0, 16], [1, 128], [2, 16], [3, 128]]) {
    const a = control.bytes[p + k] - base;
    if (Math.abs(a) >= 32) ks.push((treatment.bytes[p + k] - base) / a);
  }
}
ks.sort((a, b) => a - b);
const fittedK = ks.length
  ? {
    samples: ks.length,
    median: Number(ks[ks.length >> 1].toFixed(6)),
    p05: Number(ks[Math.floor(ks.length * 0.05)].toFixed(6)),
    p95: Number(ks[Math.floor(ks.length * 0.95)].toFixed(6)),
  }
  : null;
const hostK = Number(fd_ === null ? NaN : fd_.toFixed(6));

fs.rmSync(bundleDir, { recursive: true, force: true });

// ---- non-vacuity ----
const vacuity = [];
if (changed === 0) vacuity.push("the two console frames are IDENTICAL — the staged draw path never ran, so there is nothing to compare");
if (inside === 0) vacuity.push("the host predicted an empty region");
if (samples === 0) vacuity.push("no channel samples");
if (!blendable) vacuity.push(`the host's blend factors (${blend.src}, ${blend.dst}) are outside the alpha/one/zero set this measurement can evaluate`);
if (changed < 0.05 * W * H) vacuity.push(`only ${changed} pixel(s) changed — too small a footprint to measure equivalence over`);

const regionMatches = measured.x0 === predicted.x0 && measured.y0 === predicted.y0
  && measured.x1 === predicted.x1 && measured.y1 === predicted.y1;
const pass = !vacuity.length && regionMatches && outsideChanged === 0
  && deltas.p99 <= TOLERANCE;

const result = {
  result_schema: 1,
  standard: STANDARD,
  standard_note:
    "gx_framebuffer_equivalent measures ONE draw's contribution to a real console frame against the "
    + "GX host's prediction. It is NOT a wasm-unit verification tier and is NOT gx_callstream_green.",
  name: capHeader.name,
  fn: capHeader.function.export,
  generated_at: new Date().toISOString(),
  claim: {
    established: pass,
    summary:
      `the difference between two console frames that differ only in whether ${capHeader.function.export}'s `
      + `draw path ran is FRAMEBUFFER-EQUIVALENT to what the GX host predicts from its own decoded geometry, `
      + `decoded vertex colour and blend-enum reading, within ${TOLERANCE}/255 per 8-bit RGB channel`,
    ceiling:
      "framebuffer-equivalent, NEVER pixel-identical (docs/playable-port-design.md V3 non-fatal note 1). "
      + "WebGL rasterization cannot match Flipper; this measurement does not raise that ceiling and no "
      + "result here may be quoted as bit-exactness.",
    verifies: [
      "the RASTERIZED COVERAGE of the ROM's own quad against the console: which pixels of a real console "
        + "frame this draw touched, compared with the extent the host's FIFO decoder derives from the "
        + "console's own vertex bytes",
      "that the draw touched NOTHING outside that extent on the console",
      "the host's BLEND-ENUM READING against the console: the measured per-pixel attenuation is compared "
        + "with the host's own interpretation of GXSetBlendMode's factor arguments, which "
        + "packages/rom-runtime/src/gx/enums.ts still labels [SDK — NOT settled from the corpus]",
      "the decoded vertex COLOUR and its alpha, since both enter the prediction",
    ],
    does_not_verify: [
      "the rest of the frame. Everything the console drew that the port has not ported is CONTROLLED FOR "
        + "by the differential, not reproduced by the host.",
      "the WebGL backend. The prediction is evaluated from the host's latched state and decoded primitive; "
        + "no GL context is created here, so shader generation, texture sampling and depth handling are "
        + "untouched by this measurement.",
      "any draw with a texture, a TEV program beyond GX_PASSCLR, lighting, or depth interaction — this "
        + "draw has none of those.",
      "determinism beyond what was observed: control and treatment are two runs of one savestate at the "
        + "same frame index, and the measurement itself reports whether anything outside the draw's extent "
        + "moved between them.",
    ],
    behavioural_claim_of_the_adapters: GX_NO_BEHAVIOURAL_CLAIM,
  },
  harness: {
    entry: "research/decomp/oracle-harness/run-gx-framebuffer.mjs",
    git_rev: gitRevOf(root),
    sha256: sha256(fs.readFileSync(path.join(here, "run-gx-framebuffer.mjs"))),
    tolerance_per_channel: TOLERANCE,
    tolerance_note:
      "DECLARED BEFORE THE MEASUREMENT and not moved afterwards. It is the slack a chroma-subsampled "
      + "YUV 4:2:2 round trip plus one 8-bit fixed-point blend rounding can produce on their own.",
    colour_space: "XFB is YUY2 4:2:2, BT.601 studio swing; both frames are converted with the same "
      + "coefficients, so the conversion error is common-mode",
  },
  frames: {
    control: { file: relPosix(root, path.resolve(controlPath)), sha256: sha256(control.raw), source: control.json.source },
    treatment: { file: relPosix(root, path.resolve(treatmentPath)), sha256: sha256(treatment.raw), source: treatment.json.source },
    width: W, height: H, xfb_addr: control.json.frame.addr, vi_hit: control.json.frame.vi_hit,
  },
  capture: { file: relPosix(root, captureAbs), sha256: sha256(captureRaw), invocation: drawing.n },
  host_prediction: {
    primitive: host.backend.records[0],
    quad_extent: predicted,
    vertex_colour_rgba: srcRGBA,
    blend: { ...blend, srcFactorValue: fs_, dstFactorValue: fd_ },
    diagnostics: [...host.backend.diagnostics],
  },
  measured_change_region: measured,
  region_matches_host_prediction: regionMatches,
  pixels_changed_outside_host_prediction: outsideChanged,
  deltas,
  console_fitted_attenuation: fittedK,
  host_predicted_attenuation: hostK,
  vacuity_failures: vacuity,
  verdict: pass ? "pass" : "fail",
  verdict_token: pass ? TOKEN : "GX_FRAMEBUFFER_DIVERGENT",
};

const outDir = process.env.ORACLE_RESULTS_DIR
  ? path.resolve(process.env.ORACLE_RESULTS_DIR)
  : path.join(root, "research", "decomp", "data", "oracle-results");
fs.mkdirSync(outDir, { recursive: true });
const safe = String(capHeader.name).replace(/[^\w.-]/g, "_");
const safeFn = String(capHeader.function.export).replace(/[^\w.-]/g, "_");
const outFile = path.join(outDir, `${safe}.${safeFn}.gx-framebuffer.json`);
fs.writeFileSync(outFile, JSON.stringify(result, null, 1) + "\n");

for (const v of vacuity) console.error(`GX FRAMEBUFFER VACUOUS: ${v}`);
console.log(`artifact: ${relPosix(root, outFile)}`);
console.log(`host predicted region ${JSON.stringify(predicted)}; console changed ${JSON.stringify(measured)}`);
console.log(`console fitted attenuation ${JSON.stringify(fittedK)} vs host ${hostK}`);
console.log(`per-channel |delta|: mean ${deltas.mean_abs} p50 ${deltas.p50} p95 ${deltas.p95} `
  + `p99 ${deltas.p99} max ${deltas.max}; within ${TOLERANCE}/255: ${deltas.within_tolerance_pct}%`);
console.log(`GX FRAMEBUFFER TOTAL pixels=${inside} channels=${samples} `
  + `region=${regionMatches ? "match" : "MISMATCH"} outside_changed=${outsideChanged} `
  + `VERDICT: ${result.verdict_token}`);
process.exitCode = pass ? 0 : 1;
