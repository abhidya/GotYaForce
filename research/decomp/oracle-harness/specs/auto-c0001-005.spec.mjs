// auto-c0001-005.spec.mjs — Stage-B trace pilot spec #2 (dolphin_trace replay,
// float-heavy target with env-import shims).
//
// Reference (design v1 Stage B): the REAL GAME in the bundled Dolphin 2606-97.
// Fixture cases are actual calls of FUN_8000fc2c (0x8000fc2c) captured live by
// research/tools/dolphin-trace/capture_oracle.py under synthesized pad input
// (the borgs' camera moves, so the solver's inputs vary: 189 distinct camera
// vectors, both [view+0x582] table rows in the pilot corpus).
//
// FUN_8000fc2c — camera-distance solver, void(cam, view):
//   cam+0x350  accum  = (vtab[[v+0x582]]*4+0x88c] * cam+0x354 + accum) * F_ac4
//   cam+0x300  <- view+0x20 (x, bit-copy); cam+0x304 <- (v6d0+accum+c310+v24)*F_ac4;
//   cam+0x308 <- view+0x28 (bit-copy)
//   d2 = PSVECSquareMag(cam+0x318 - view+0x20)   [env shims — ROM's own
//        PSVECSubtract/PSVECSquareMag, decompiled at chunk_0064.c:1283/1361]
//   min/max rows from view+0x894.. selected by [view+0x582], scaled by
//   cam+0x354 (and F_ad0 under the [g930+0x29] mode); frsqrte+2xNewton sqrt
//   (D_ab0/D_ab8) clamps cam+0x348; hysteresis byte cam+0x35e.
//
// Float honesty: the decompiled C (and therefore the wasm) does this math in
// doubles where the console used paired-single ops; the sqrt seed is decomp's
// 1.0/SQRT vs the console's frsqrte estimate (both then Newton-refined twice).
// Byte-inexact float write-backs within a small ulp distance are classified
// "rounding" (never "exact"), with rounding_bound 1.0 so the run REPORTS the
// split instead of hiding it — the pilot's job is to measure this channel,
// not to pretend it does not exist. Non-float mismatches are unexplained.
//
// ================= PILOT VERDICT (2026-08-25): REAL DIVERGENCE FOUND ========
// Replaying the 200-case corpus against the staged wasm: 0/200 exact — w348
// diverges structurally, and the root cause was proven against the live ROM:
//
//   The ROM ZEROES THE Y COMPONENT of (cam+0x318 - view+0x20) before
//   PSVECSquareMag — the camera clamps on HORIZONTAL distance. Ghidra's
//   decompilation (chunk_0001.c:2790, `local_1c = FLOAT_80436aa8;`) mis-lifted
//   that store through a stack-aliasing failure: local_1c IS fStack_20.y
//   (verified live: at the 0x8000fd2c fcmpo the stack diff vector reads
//   (-497.009, 0.0, -414.057) while cam+0x318/view+0x20 y-delta is 277.5;
//   f1 = 418461.59 = x²+z² exactly). The staged unit compiled the aliased C
//   faithfully, so the wasm computes 3D distance and takes the wrong clamp
//   branch. Re-simulating all 200 cases with diff.y=0: 196/200 byte-exact,
//   4/200 within 1 ulp on the frsqrte-Newton path (the expected sqrt-seed
//   rounding channel).
//
//   So verdict FAIL here is the trace oracle WORKING: a compile-green staged
//   unit is behaviorally wrong vs the console, caught and root-caused by
//   per-call capture. Fix path: repair the unit.c aliasing (fStack_20.y = 0.0f
//   instead of the dead local_1c), recompile, re-run this same corpus.
// ============================================================================
//
// EXPORT COVERAGE: only FUN_8000fc2c has a trace corpus; the other 7 exports
// are uncovered -> verdict PARTIAL at best (never PASS/exit-0/promotable).
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const here = path.dirname(fileURLToPath(import.meta.url));

const CAM = 0x80600000;   // rebased r3 (camera struct) — scratch, damage-core convention
const VIEW = 0x80604000;  // rebased r4 (view/player struct)
const G930S = 0x80608000; // rebased [0x80433930] battle-mode struct
const G930P = 0x80433930; // PTR_DAT_80433930 cell itself
const CONST = 0x80436aa8; // FLOAT_80436aa8 .. FLOAT_80436b38 window
const CONST_SIZE = 0x94;

export const meta = {
  unit: "auto-c0001-005",
  reference_kind: "dolphin_trace",
  references: [
    "real GG4E in bundled Dolphin 2606-97 (GDB-stub per-call capture; tool: research/tools/dolphin-trace/capture_oracle.py; plan: research/tools/dolphin-trace/plans/auto-c0001-005.FUN_8000fc2c.json)",
    "env shims: ROM PSVECSubtract/PSVECSquareMag per their decompiled bodies (chunk_0064.c:1283-1292 / 1361-1366)",
  ],
  arena: "arena-trace-empty.json",
  wasmDefault: "../port-units-staging/auto-c0001-005/unit.wasm",
  fixture: "corpora/auto-c0001-005.dolphin-trace.jsonl",
  functions: [
    { name: "FUN_8000fc2c", rounding_bound: 1.0, min_cases: 150,
      reference: "dolphin_trace 0x8000fc2c (entry+LR breakpoint capture, per-call args/reads/writes)",
      note: "camera-distance solver; float-channel divergences reported as rounding (bound 1.0 = report, don't hide); see spec header" },
  ],
  uncovered_exports: [
    "FUN_8000f604", "FUN_8000f72c", "FUN_8000f764", "FUN_8000f7fc",
    "FUN_8000f9e0", "FUN_8000fe60", "FUN_8000fffc",
  ],
  regions: [
    { name: "CAM", base: CAM, size: 0x400 },
    { name: "VIEW", base: VIEW, size: 0x900 },
    { name: "G930P", base: G930P, size: 4 },
    { name: "G930S", base: G930S, size: 0x40 },
    { name: "CONST", base: CONST, size: CONST_SIZE },
  ],
};

const f32buf = new Float32Array(1);
const fr = (x) => { f32buf[0] = x; return f32buf[0]; };

// Env shims: the ROM's own paired-single vector helpers, per their DECOMPILED
// semantics (the same semantics the rest of the unit was compiled from).
export function makeShims(memCtx) {
  const gf = (a) => memCtx.dv.getFloat32(a >>> 0, true);
  const sf = (a, v) => memCtx.dv.setFloat32(a >>> 0, v, true);
  return {
    gnt4_PSVECSubtract_bl: (a, b, o) => {
      a >>>= 0; b >>>= 0; o >>>= 0;
      const y = fr(gf(a + 4) - gf(b + 4));
      sf(o, fr(gf(a) - gf(b)));
      sf(o + 4, y);
      sf(o + 8, fr(gf(a + 8) - gf(b + 8)));
    },
    gnt4_PSVECSquareMag_bl: (a) => {
      a >>>= 0;
      const x = gf(a), y = gf(a + 4), z = gf(a + 8);
      // decompiled order: z*z + x*x + y*y, all in double
      return z * z + x * x + y * y;
    },
  };
}

const beBytes = (hex) => new Uint8Array(Buffer.from(hex, "hex"));
// element-wise BE->LE swap at `width` (the arena-provenance rule)
const swapped = (hex, width) => {
  const b = beBytes(hex);
  const out = new Uint8Array(b.length);
  for (let i = 0; i < b.length; i += width) {
    for (let j = 0; j < width; j++) out[i + j] = b[i + width - 1 - j];
  }
  return out;
};
const f32FromBE = (hex) => {
  const b = beBytes(hex);
  return new DataView(b.buffer).getFloat32(0, false);
};
const bitsFromBE = (hex) => new DataView(beBytes(hex).buffer).getUint32(0, false);

const ulpDist = (aBits, bBits) => {
  // lexicographic-int distance over the float line (sign-folded)
  const fold = (u) => (u & 0x80000000) ? (0x80000000 - (u & 0x7fffffff)) : (0x80000000 + u);
  return Math.abs(fold(aBits >>> 0) - fold(bBits >>> 0));
};
const ROUNDING_ULP = 2;

export function createRunner({ ex, dv }) {
  return {
    unit: meta.unit,
    handleRecord(codec, rec) {
      if (rec.kind !== "case") throw new Error(`unknown record kind ${rec.kind}`);
      const byId = {};
      for (const r of rec.reads) byId[r.id] = r;
      const need = (id) => {
        if (!byId[id]) throw new Error(`case ${rec.n} missing read ${id}`);
        return byId[id];
      };
      const w = {};
      for (const x of rec.writes) w[x.id] = x;

      codec.beginCase();
      // camera struct
      codec.wBytes(CAM + 0x350, swapped(need("c350").be_hex, 4));
      codec.wBytes(CAM + 0x354, swapped(need("c354").be_hex, 4));
      codec.wBytes(CAM + 0x310, swapped(need("c310").be_hex, 4));
      codec.wBytes(CAM + 0x318, swapped(need("c318").be_hex, 4)); // vec3: 3x f32
      codec.wBytes(CAM + 0x348, swapped(need("c348_pre").be_hex, 4));
      codec.wBytes(CAM + 0x35e, beBytes(need("c35e_pre").be_hex));
      // view struct
      codec.wBytes(VIEW + 0x582, beBytes(need("v582").be_hex));
      codec.wBytes(VIEW + 0x88c, swapped(need("vtab").be_hex, 4)); // 6x f32
      codec.wBytes(VIEW + 0x20, swapped(need("vpos").be_hex, 4)); // vec3
      codec.wBytes(VIEW + 0x6d0, swapped(need("v6d0").be_hex, 4));
      codec.wBytes(VIEW + 0x7c9, beBytes(need("v7c9").be_hex));
      // battle-mode global: rebase the pointer cell, seed the two bytes read
      codec.wU32(G930P, G930S);
      codec.wBytes(G930S + 0x29, beBytes(need("g930_29").be_hex));
      codec.wBytes(G930S + 0x3d, beBytes(need("g930_3d").be_hex));
      // constants
      codec.wBytes(0x80436ac4, swapped(need("f_ac4").be_hex, 4));
      codec.wBytes(0x80436aa8, swapped(need("f_aa8").be_hex, 4));
      codec.wBytes(0x80436ad0, swapped(need("f_ad0").be_hex, 4));
      codec.wBytes(0x80436ab0, swapped(need("d_ab0").be_hex, 8));
      codec.wBytes(0x80436ab8, swapped(need("d_ab8").be_hex, 8));
      codec.wBytes(0x80436b38, swapped(need("f_b38").be_hex, 4));

      const audit = codec.auditReads({
        mustWrite: [
          [CAM + 0x350, 4], [CAM + 0x354, 4], [CAM + 0x310, 4], [CAM + 0x318, 12],
          [CAM + 0x348, 4], [CAM + 0x35e, 1],
          [VIEW + 0x582, 1], [VIEW + 0x88c, 24], [VIEW + 0x20, 12],
          [VIEW + 0x6d0, 4], [VIEW + 0x7c9, 1],
          [G930P, 4], [G930S + 0x29, 1], [G930S + 0x3d, 1],
          [0x80436ac4, 4], [0x80436aa8, 4], [0x80436ad0, 4],
          [0x80436ab0, 8], [0x80436ab8, 8], [0x80436b38, 4],
        ],
        arenaOk: [],
      });
      codec.snapshotExpected();

      let trap = null;
      try { ex.FUN_8000fc2c(CAM, VIEW); }
      catch (e) { trap = String((e && e.message) || e); }

      // per-field verdicts (bit-exact vs ulp-rounding vs unexplained)
      const fields = [
        { name: "w350", addr: CAM + 0x350, kind: "f32", wantHex: w.w350.be_hex },
        { name: "w300x", addr: CAM + 0x300, kind: "bits", wantHex: w.w300.be_hex.slice(0, 8) },
        { name: "w304", addr: CAM + 0x304, kind: "f32", wantHex: w.w300.be_hex.slice(8, 16) },
        { name: "w308", addr: CAM + 0x308, kind: "bits", wantHex: w.w300.be_hex.slice(16, 24) },
        { name: "w348", addr: CAM + 0x348, kind: "f32", wantHex: w.w348.be_hex },
        { name: "w35e", addr: CAM + 0x35e, kind: "u8", wantHex: w.w35e.be_hex },
      ];
      let worstUlp = 0;
      let cls = trap == null ? "exact" : "unexplained";
      const fieldDump = [];
      if (trap == null) {
        for (const f of fields) {
          if (f.kind === "u8") {
            const got = codec.u8[f.addr];
            const want = beBytes(f.wantHex)[0];
            if (got !== want) { cls = "unexplained"; fieldDump.push({ f: f.name, got, want }); }
            continue;
          }
          const gotBits = dv.getUint32(f.addr, true) >>> 0;
          const wantBits = bitsFromBE(f.wantHex) >>> 0;
          if (gotBits === wantBits) continue;
          if (f.kind === "f32") {
            const d = ulpDist(gotBits, wantBits);
            worstUlp = Math.max(worstUlp, d);
            fieldDump.push({ f: f.name, gotBits: gotBits.toString(16), wantBits: wantBits.toString(16), ulp: d });
            if (d <= ROUNDING_ULP && cls !== "unexplained") { cls = "rounding"; continue; }
          } else {
            fieldDump.push({ f: f.name, gotBits: gotBits.toString(16), wantBits: wantBits.toString(16) });
          }
          cls = "unexplained";
        }
      }

      // stray-write detection: accept the unit's own (already verified or
      // ulp-classified) write-back bytes, flag anything else it touched
      const gotWriteBacks = fields.map((f) => ({
        addr: f.addr,
        bytes: f.kind === "u8"
          ? new Uint8Array([codec.u8[f.addr]])
          : new Uint8Array([codec.u8[f.addr], codec.u8[f.addr + 1], codec.u8[f.addr + 2], codec.u8[f.addr + 3]]),
      }));
      const post = codec.diffPostState(gotWriteBacks);
      if (post.strayWrites.length > 0 && cls === "exact") cls = "unexplained";

      return {
        fn: "FUN_8000fc2c", n: rec.n, cls, audit, post,
        dump: cls === "exact" ? null : {
          n: rec.n, trap, worstUlp, fields: fieldDump,
          stray: post.strayWrites.map((a) => "0x" + a.toString(16)),
        },
      };
    },
  };
}
