// auto-c0020-007.spec.mjs — Stage-B trace spec (dolphin_trace replay), the
// first MULTI-EXPORT trace spec in this harness.
//
// Reference (design v1 Stage B, playable-port-design.md): the REAL GG4E running
// in the bundled Dolphin 2606-97 is the oracle. Each fixture case is one actual
// call of one of this unit's exports, captured live by
// research/tools/dolphin-trace/capture_oracle.py (GDB-stub breakpoints at entry
// + the caller's return address) against the HAND-AUTHORED capture plans in
// research/tools/dolphin-trace/plans/auto-c0020-007.*.json: entry registers,
// the typed read set derived line-by-line from the unit's verbatim C, and the
// post-return bytes of the derived write set. The per-export fixtures are
// combined into this spec's corpus by
// research/tools/dolphin-trace/merge_fixtures.py.
//
// Replay = rebase captured pointers into fixed scratch regions, byte-swap
// scalars element-wise (BE console RAM -> LE wasm arena, the
// gen_arena_rom_provenance.py rule), call the staged wasm, byte-compare the
// write set. "exact" = every write-set byte identical to the console's, with no
// stray writes anywhere in the scratch regions.
//
// WHAT THIS UNIT IS. auto-c0020-007 is the lifecycle of a homing tracker object
// owned by a borg actor (family 0x800c04c0 / pl0300 is the only family live in
// the repo's one battle savestate, which is why this unit is capturable at all):
//   zz_00c4704_  spawns it and fills 23 fields of the new object
//   FUN_800c4838 is its per-frame state-machine trampoline
//   zz_00c4540_  homing/impact step (normalize+scale velocity, track target,
//                decrement the hit counter, advance position, recompute range)
//   FUN_800c4308 the non-homing integrator (advance, ramp speed, decay scale)
//   FUN_800c42bc the per-frame range/ETA decrement with expiry
//   zz_00c44a8_  orientation update + matrix translation write-back
//   FUN_800c4448 / FUN_800c4468 forwarding thunks into ROM helpers
// The per-type parameter table is a 0x44-stride array based at 0x80303148,
// indexed by the object's type byte at +0x11 (derived from the `iVar3 +
// -0x7fcfceb8` address expression in the verbatim C).
//
// ===================== EXPORT COVERAGE (§3.4) — HONEST ======================
// 5 of 8 exports are covered. The other 3 are uncovered for reasons that are
// properties of the game state and of the tool, not omissions:
//
//   FUN_800c4308  — captured 0 cases. Its plan (typed reads/writes) IS authored
//                   and committed; the non-homing integrator simply never runs
//                   in the one battle savestate this repo has. Needs a new
//                   scenario/DTM, not more capture time.
//   zz_00c4704_   — captured 0 cases, AND its write set is structurally
//                   uncapturable: 22 of its 23 stores target the return value of
//                   the zz_0088aa0_ allocator, and capture_oracle.py evaluates
//                   write addresses over ENTRY registers only.
//   FUN_800c4838  — captured 0 cases, AND it is unreplayable by construction:
//                   it ends in a dispatch through the ROM function table at
//                   0x80305240, and staged wasm units carry no address ->
//                   wasm-table mapping (gnt4_shim.h says so in as many words),
//                   so the wasm traps on the indirect call.
//
// So this spec's best possible verdict is PARTIAL — never PASS, never exit 0,
// never promotable to oracle_green. That is the correct outcome: full coverage
// is blocked on capture coverage the repository does not have.
//
// ===================== CALLEE OWNERSHIP — the honest part ===================
// Two covered exports can call ROM helpers this replay cannot model, and one of
// them MATTERS, so it is handled explicitly rather than hand-waved:
//
//   zz_00c4540_ re-aim branch. When the re-aim counter at a+0x1cb reaches 0 the
//   ROM calls zz_006c440_(rate, actor, aimPoint), whose OWN decompiled body
//   (chunk_0009.c:2031) is: steer the velocity (FUN_8006c1c8), then
//   PSVECNormalize + PSQUATScale + PSVECAdd on a+0x38 / a+0x20 — i.e. the
//   callee re-writes the velocity AND advances the position, and the unit's own
//   PSVECAdd is skipped on that path. So on a re-aim case the console's
//   post-state at a+0x38, a+0x20 and (consequently) a+0x180 belongs to the
//   CALLEE, not to this unit; comparing them would measure a function that is
//   not under test. This spec therefore:
//     * derives, from console evidence alone (a+0xc8 pre/post and the a+0x1cb
//       pre/post/reload bytes), which branch the ROM took;
//     * REQUIRES the wasm to have taken the same branch, and to have called
//       zz_006c440_ / zz_00833a4_ with the derived arguments — a genuine and
//       falsifiable check of the branch logic;
//     * compares the full write set (including the float channel) only on cases
//       where the ROM did NOT re-aim, and on re-aim cases compares the subset
//       the unit provably owns (a+0x150 / a+0x160 / a+0x170, a+0x1cb, a+0xc8);
//     * prints the split, so the partial coverage is visible and not implied.
//   MEASURED on the committed 200-case corpus: 57 null-tracker + 2 cleared = 59
//   full comparisons, 141 re-aim cases with the reduced set.
//
//   FUN_800c42bc expiry branch. Reaching zz_00c42a8_ means the console may have
//   stored into a+0x184 / a+0x60 after the unit did. Such cases are flagged
//   `callee_tainted` in their dump so a divergence can be read against the flag
//   instead of being mistaken for a wrong unit.
//
// A divergence on a case with no callee involvement is a real finding about the
// unit.
//
// ===================== FLOAT CHANNEL ========================================
// The SDK is never ported (design stage 1): gnt4_* arrive as env imports and
// this spec implements them from their OWN decompiled bodies in
// research/decomp/ghidra-export/chunk_0064.c (PSMTXMultVec 1039, PSVECAdd 1249,
// PSVECSubtract 1274, PSQUATScale 1299, PSVECNormalize 1322, PSVECSquareMag
// 1352, PSQUATDotProduct 1390, PSVECSquareDistance 1467). PSVECNormalize's
// decompiled body seeds its Newton step with an EXACT 1.0/sqrt where the
// console's Gekko uses the frsqrte estimate, so normalize-derived f32 results
// can differ from the console by a small number of ulps. Those are classified
// "rounding" (never "exact") with rounding_bound 1.0, so the run REPORTS the
// split instead of hiding it — the same discipline as auto-c0001-005. The two
// Newton constants FLOAT_8043ca90 / FLOAT_8043ca94 are not assumed: they are
// captured from the live console by the zz_00c4540_ plan's `sdk_ca90` read.
import { fileURLToPath } from "node:url";

// ---- rebased scratch regions (damage-core convention: above all DOL/bss) ----
const ACT = 0x80600000;   // r3 — the tracker object
const TRK = 0x80604000;   // [r3+0xc8] — the tracked target object
const P9 = 0x80608000;    // FUN_800c4468 param_9
const P44 = 0x8060c000;   // FUN_800c4448 param_9
// ---- absolute (compiled-in) addresses: NOT rebasable, the unit derives them ----
const TBL = 0x80303148;   // per-type table base, 0x44 stride, index = [r3+0x11]
const TBL_SIZE = 0x4400;  // 0x100 rows: the type byte is unbounded
const CONST = 0x80438744; // FLOAT_80438744 .. FLOAT_80438764 window
const CONST_SIZE = 0x24;
const SDKC = 0x8043ca90;  // FLOAT_8043ca90 / FLOAT_8043ca94 (PSVECNormalize Newton)

export const meta = {
  unit: "auto-c0020-007",
  reference_kind: "dolphin_trace",
  references: [
    "real GG4E in bundled Dolphin 2606-97 (GDB-stub per-call capture; tool: research/tools/dolphin-trace/capture_oracle.py; plans: research/tools/dolphin-trace/plans/auto-c0020-007.*.json)",
    "corpus merge: research/tools/dolphin-trace/merge_fixtures.py",
    "env shims: the ROM's own SDK bodies per research/decomp/ghidra-export/chunk_0064.c (PSMTXMultVec 1039, PSVECAdd 1249, PSVECSubtract 1274, PSQUATScale 1299, PSVECNormalize 1322, PSVECSquareMag 1352, PSQUATDotProduct 1390, PSVECSquareDistance 1467)",
  ],
  arena: "arena-trace-empty.json",
  wasmDefault: "../port-units-staging/auto-c0020-007/unit.wasm",
  fixture: "corpora/auto-c0020-007.dolphin-trace.jsonl",
  functions: [
    { name: "FUN_800c4468", rounding_bound: 0, min_cases: 150,
      reference: "dolphin_trace 0x800c4468 (entry+LR capture; plan auto-c0020-007.FUN_800c4468.json)",
      note: "forwarding thunk: verified through recording env shims — the [param_9+0xe0] load, the param_9+0x114 interior pointer, argument positions, and the zz_00076d0_ -> zz_00097b4_ call order. Stores nothing, so it has no write set to compare." },
    { name: "zz_00c44a8_", rounding_bound: 0, min_cases: 150,
      reference: "dolphin_trace 0x800c44a8 (entry+LR capture; plan auto-c0020-007.zz_00c44a8_.json)",
      note: "orientation update; only its own three stores (matrix translation column a+0x120/0x130/0x140 <- position words) are declared — the a+0x114 matrix is ROM-callee-owned and deliberately not compared." },
    { name: "zz_00c4540_", rounding_bound: 1.0, min_cases: 150,
      reference: "dolphin_trace 0x800c4540 (entry+LR capture; plan auto-c0020-007.zz_00c4540_.json)",
      note: "homing/impact step; the float-heavy one. normalize-derived f32 write-backs may sit a few ulps off the console's frsqrte path — reported as rounding, bound 1.0 = report, do not hide." },
    { name: "FUN_800c42bc", rounding_bound: 1.0, min_cases: 150,
      reference: "dolphin_trace 0x800c42bc (entry+LR capture; plan auto-c0020-007.FUN_800c42bc.json)",
      note: "range/ETA decrement; cases that reach the zz_00c42a8_ expiry callee are marked callee_tainted." },
    { name: "FUN_800c4448", rounding_bound: 0, min_cases: 10,
      reference: "dolphin_trace 0x800c4448 (entry+LR capture; plan auto-c0020-007.FUN_800c4448.json)",
      note: "pure forwarding thunk with no memory effect; the only replayable property is argument forwarding, checked through a recording shim. The seven double args are FPR-passed and unsampled by the capture tool, so they are supplied as distinct sentinels and only their SLOTS are proven." },
  ],
  uncovered_exports: ["FUN_800c4308", "zz_00c4704_", "FUN_800c4838"],
  regions: [
    { name: "ACT", base: ACT, size: 0x400 },
    { name: "TRK", base: TRK, size: 0x80 },
    { name: "P9", base: P9, size: 0x200 },
    { name: "P44", base: P44, size: 0x40 },
    { name: "TBL", base: TBL, size: TBL_SIZE },
    { name: "CONST", base: CONST, size: CONST_SIZE },
    { name: "SDKC", base: SDKC, size: 8 },
  ],
};

// ---------------------------------------------------------------- primitives
const f32buf = new Float32Array(1);
const fr = (x) => { f32buf[0] = x; return f32buf[0]; };
const beBytes = (hex) => new Uint8Array(Buffer.from(hex, "hex"));
/** element-wise BE->LE swap at `width` (the arena-provenance rule) */
const swapped = (hex, width) => {
  const b = beBytes(hex);
  const out = new Uint8Array(b.length);
  for (let i = 0; i < b.length; i += width) {
    for (let j = 0; j < width; j++) out[i + j] = b[i + width - 1 - j];
  }
  return out;
};
const beU32 = (hex) => new DataView(beBytes(hex).buffer).getUint32(0, false) >>> 0;
const ulpDist = (aBits, bBits) => {
  const fold = (u) => ((u & 0x80000000) ? (0x80000000 - (u & 0x7fffffff)) : (0x80000000 + u));
  return Math.abs(fold(aBits >>> 0) - fold(bBits >>> 0));
};
const ROUNDING_ULP = 4;

// The seven FPR-passed doubles the capture tool cannot sample. Distinct,
// exactly representable values so a permuted slot is visible.
const DSENT = [1.5, 2.25, 3.125, 4.0625, 5.03125, 6.015625, 7.0078125];

// ------------------------------------------------------------------ env shims
// Every shim records its call; the runner resets the log per case. Anything the
// runner does NOT install stays a loud Proxy throw (lib/wasm.mjs).
const callLog = [];

export function makeShims(memCtx) {
  const gf = (a) => memCtx.dv.getFloat32(a >>> 0, true);
  const sf = (a, v) => memCtx.dv.setFloat32(a >>> 0, v, true);
  const rec = (name, args) => { callLog.push({ name, args }); };

  // --- SDK (chunk_0064.c bodies) ---
  const sdk = {
    // 1249: fVar1=a[1]; fVar2=b[1]; o[0]=a[0]+b[0]; o[1]=fVar1+fVar2; o[2]=a[2]+b[2]
    gnt4_PSVECAdd_bl: (a, b, o) => {
      a >>>= 0; b >>>= 0; o >>>= 0;
      rec("gnt4_PSVECAdd_bl", [a, b, o]);
      const y = fr(gf(a + 4) + gf(b + 4));
      sf(o, fr(gf(a) + gf(b)));
      sf(o + 4, y);
      sf(o + 8, fr(gf(a + 8) + gf(b + 8)));
      return 0n;
    },
    // 1274
    gnt4_PSVECSubtract_bl: (a, b, o) => {
      a >>>= 0; b >>>= 0; o >>>= 0;
      rec("gnt4_PSVECSubtract_bl", [a, b, o]);
      const y = fr(gf(a + 4) - gf(b + 4));
      sf(o, fr(gf(a) - gf(b)));
      sf(o + 4, y);
      sf(o + 8, fr(gf(a + 8) - gf(b + 8)));
    },
    // 1299: o[i] = (float)((double)v[i] * s)
    gnt4_PSQUATScale_bl: (s, v, o) => {
      v >>>= 0; o >>>= 0;
      rec("gnt4_PSQUATScale_bl", [s, v, o]);
      const y = fr(gf(v + 4) * s);
      const z = fr(gf(v + 8) * s);
      sf(o, fr(gf(v) * s));
      sf(o + 4, y);
      sf(o + 8, z);
      return 0n;
    },
    // 1322: float-precision magnitude, 1/sqrt seed, ONE Newton step with the
    // console-captured constants at 0x8043ca90 / 0x8043ca94.
    gnt4_PSVECNormalize_bl: (i, o) => {
      i >>>= 0; o >>>= 0;
      rec("gnt4_PSVECNormalize_bl", [i, o]);
      const half = gf(SDKC);      // FLOAT_8043ca90
      const three = gf(SDKC + 4); // FLOAT_8043ca94
      const x = gf(i), y = gf(i + 4), z = gf(i + 8);
      const mag = fr(fr(fr(z * z) + fr(x * x)) + fr(y * y));
      let k = fr(1.0 / Math.sqrt(mag));
      k = fr(fr(fr(-fr(fr(fr(k * k) * mag) - three)) * k) * half);
      sf(o, fr(x * k));
      sf(o + 4, fr(y * k));
      sf(o + 8, fr(z * k));
    },
    // 1352: (double)z*z + (double)x*x + (double)y*y
    gnt4_PSVECSquareMag_bl: (a) => {
      a >>>= 0;
      rec("gnt4_PSVECSquareMag_bl", [a]);
      const x = gf(a), y = gf(a + 4), z = gf(a + 8);
      return z * z + x * x + y * y;
    },
    // 1390: three-component dot in double (despite the QUAT name)
    gnt4_PSQUATDotProduct_bl: (a, b) => {
      a >>>= 0; b >>>= 0;
      rec("gnt4_PSQUATDotProduct_bl", [a, b]);
      return gf(a) * gf(b) + gf(a + 4) * gf(b + 4) + gf(a + 8) * gf(b + 8);
    },
    // 1467: componentwise difference squared, all in double
    gnt4_PSVECSquareDistance_bl: (a, b) => {
      a >>>= 0; b >>>= 0;
      rec("gnt4_PSVECSquareDistance_bl", [a, b]);
      const dx = gf(a) - gf(b), dy = gf(a + 4) - gf(b + 4), dz = gf(a + 8) - gf(b + 8);
      return dx * dx + dy * dy + dz * dz;
    },
    // 1039: 3x4 matrix times vec3 with an implicit 1.0 translation column
    gnt4_PSMTXMultVec_bl: (m, v, o) => {
      m >>>= 0; v >>>= 0; o >>>= 0;
      rec("gnt4_PSMTXMultVec_bl", [m, v, o]);
      const vx = gf(v), vy = gf(v + 4), vz = gf(v + 8);
      const row = (r) => {
        const a0 = gf(m + r * 16), a1 = gf(m + r * 16 + 4);
        const a2 = gf(m + r * 16 + 8), a3 = gf(m + r * 16 + 12);
        return fr(fr(fr(a2 * vz) + fr(a0 * vx)) + a3 * 1.0 + fr(a1 * vy));
      };
      const y = row(1), z = row(2);
      sf(o, row(0));
      sf(o + 4, y);
      sf(o + 8, z);
      return 0n;
    },
  };

  // --- ROM callees: recorded no-ops. Any of these firing marks the case
  //     callee_tainted (the console's callee may have written memory the
  //     replay's no-op did not). ---
  const romVoid = (name, arity) => (...a) => { rec(name, a.slice(0, arity)); };
  return {
    ...sdk,
    zz_00c42a8_: romVoid("zz_00c42a8_", 1),
    zz_006c440_: romVoid("zz_006c440_", 3),
    zz_00833a4_: romVoid("zz_00833a4_", 1),
    zz_00456a0_: romVoid("zz_00456a0_", 3),
    // returns a bool; the return only decides whether a SECOND zz_0045ef4_ call
    // happens, and neither call touches memory the unit stores to, so a fixed 0
    // cannot change any declared write.
    zz_0045ef4_: (...a) => { rec("zz_0045ef4_", a.slice(0, 4)); return 0; },
    zz_00076d0_: (...a) => { rec("zz_00076d0_", a.slice(0, 16)); },
    zz_00097b4_: romVoid("zz_00097b4_", 2),
    zz_0088e50_: (...a) => { rec("zz_0088e50_", a.slice(0, 9)); },
  };
}

const TAINTING = new Set(["zz_00c42a8_", "zz_006c440_", "zz_00833a4_"]);

// Coverage honesty: the zz_00c4540_ branch split and the FUN_800c42bc expiry
// count are printed at exit so a reader of the harness log sees how much of the
// corpus got the FULL write-set comparison and how much got the reduced one.
// The harness itself has no per-spec summary hook, hence process.on("exit").
const tally = {
  branch: {}, full_compare: 0, reduced_compare: 0,
  c42bc_expiry: 0, c42bc_total: 0,
};
let tallyPrinted = false;
process.on("exit", () => {
  if (tallyPrinted || tally.full_compare + tally.reduced_compare === 0) return;
  tallyPrinted = true;
  const b = Object.entries(tally.branch).map(([k, v]) => `${k}=${v}`).join(" ");
  // NOTE: the sentinel-probe pass re-runs a sample of cases, so these counts
  // are replay-invocation counts, not distinct-case counts.
  console.log(`[zz_00c4540_] console branch split (incl. sentinel-probe reruns): ${b}`);
  console.log(`[zz_00c4540_] full write-set comparisons=${tally.full_compare} reduced (a+0x38/a+0x20/a+0x180 owned by zz_006c440_)=${tally.reduced_compare}`);
  console.log(`[FUN_800c42bc] expiry-callee cases=${tally.c42bc_expiry}/${tally.c42bc_total}`);
});

// ------------------------------------------------------------------- runner
export function createRunner({ ex, dv }) {
  const readsById = (rec) => {
    const by = {};
    for (const r of rec.reads) by[r.id] = r;
    return by;
  };
  const writesById = (rec) => {
    const by = {};
    for (const w of rec.writes) by[w.id] = w;
    return by;
  };

  /** Compare declared write-backs; returns {cls, fieldDump, gotBacks}. */
  const compare = (codec, fields) => {
    let cls = "exact";
    const fieldDump = [];
    const gotBacks = [];
    for (const f of fields) {
      const n = f.kind === "u8" ? 1 : 4;
      const got = new Uint8Array(n);
      for (let i = 0; i < n; i++) got[i] = codec.u8[f.addr + i];
      gotBacks.push({ addr: f.addr, bytes: got });
      const want = f.kind === "u8" ? beBytes(f.wantHex) : swapped(f.wantHex, 4);
      let same = true;
      for (let i = 0; i < n; i++) if (got[i] !== want[i]) { same = false; break; }
      if (same) continue;
      if (f.kind === "f32") {
        const gotBits = dv.getUint32(f.addr, true) >>> 0;
        const wantBits = new DataView(want.buffer).getUint32(0, true) >>> 0;
        const d = ulpDist(gotBits, wantBits);
        fieldDump.push({ f: f.name, got: gotBits.toString(16), want: wantBits.toString(16), ulp: d });
        if (d <= ROUNDING_ULP && cls !== "unexplained") { cls = "rounding"; continue; }
      } else {
        fieldDump.push({
          f: f.name,
          got: Buffer.from(got).toString("hex"),
          want: Buffer.from(want).toString("hex"),
        });
      }
      cls = "unexplained";
    }
    return { cls, fieldDump, gotBacks };
  };

  const finish = (fn, rec, cls, audit, post, extra, tainted) => {
    if (post.strayWrites.length > 0 && cls === "exact") cls = "unexplained";
    return {
      fn, n: rec.n, cls, audit, post,
      dump: cls === "exact" ? null : {
        n: rec.n, fn_n: rec.fn_n, callee_tainted: tainted,
        calls: callLog.map((c) => c.name),
        ...extra,
        stray: post.strayWrites.map((a) => "0x" + a.toString(16)),
      },
    };
  };

  // ---------------------------------------------------------- FUN_800c42bc
  const runC42bc = (codec, rec) => {
    const R = readsById(rec), W = writesById(rec);
    const need = (id) => { if (!R[id]) throw new Error(`case ${rec.n} missing read ${id}`); return R[id]; };
    codec.beginCase();
    codec.wBytes(ACT + 0x184, swapped(need("a184_pre").be_hex, 4));
    codec.wBytes(ACT + 0x44, swapped(need("a44").be_hex, 4));
    codec.wBytes(0x80438744, swapped(need("f_8744").be_hex, 4));
    codec.wBytes(0x8043875c, swapped(need("f_875c").be_hex, 4));
    const audit = codec.auditReads({
      mustWrite: [[ACT + 0x184, 4], [ACT + 0x44, 4], [0x80438744, 4], [0x8043875c, 4]],
      arenaOk: [],
    });
    codec.snapshotExpected();
    callLog.length = 0;
    let trap = null;
    try { ex.FUN_800c42bc(ACT); } catch (e) { trap = String((e && e.message) || e); }
    const tainted = callLog.some((c) => TAINTING.has(c.name));
    tally.c42bc_total++;
    if (tainted) tally.c42bc_expiry++;
    const { cls, fieldDump, gotBacks } = trap ? { cls: "unexplained", fieldDump: [], gotBacks: [] }
      : compare(codec, [
        { name: "w184", addr: ACT + 0x184, kind: "f32", wantHex: W.w184.be_hex },
        { name: "w60", addr: ACT + 0x60, kind: "f32", wantHex: W.w60.be_hex },
      ]);
    const post = codec.diffPostState(gotBacks);
    return finish("FUN_800c42bc", rec, cls, audit, post, { trap, fields: fieldDump }, tainted);
  };

  // ---------------------------------------------------------- FUN_800c4448
  const runC4448 = (codec, rec) => {
    codec.beginCase();
    const hi = Number.parseInt(rec.args[0], 16) >>> 0;
    const lo = Number.parseInt(rec.args[1], 16) >>> 0;
    // wasm i64 args surface in JS as SIGNED BigInts, so compare against the
    // signed reading of the captured r3:r4 pair.
    const p1 = (BigInt(hi) << 32n) | BigInt(lo);
    const p1s = BigInt.asIntN(64, p1);
    const audit = codec.auditReads({ mustWrite: [], arenaOk: [] });
    codec.snapshotExpected();
    callLog.length = 0;
    let trap = null;
    try { ex.FUN_800c4448(p1, ...DSENT, P44); } catch (e) { trap = String((e && e.message) || e); }
    const problems = [];
    if (trap) problems.push({ trap });
    const forwarded = callLog.filter((c) => c.name === "zz_0088e50_");
    if (callLog.length !== 1 || forwarded.length !== 1) {
      problems.push({ calls: callLog.map((c) => c.name) });
    } else {
      const a = forwarded[0].args;
      if (BigInt.asIntN(64, a[0]) !== p1s) problems.push({ arg: "param_1", got: String(a[0]), want: String(p1s) });
      for (let i = 0; i < 7; i++) {
        if (a[1 + i] !== DSENT[i]) problems.push({ arg: `param_${2 + i}`, got: a[1 + i], want: DSENT[i] });
      }
      if ((a[8] >>> 0) !== P44) problems.push({ arg: "param_9", got: (a[8] >>> 0).toString(16), want: P44.toString(16) });
    }
    const post = codec.diffPostState([]);
    const cls = problems.length === 0 ? "exact" : "unexplained";
    return finish("FUN_800c4448", rec, cls, audit, post, { problems }, false);
  };

  // ---------------------------------------------------------- FUN_800c4468
  const runC4468 = (codec, rec) => {
    const R = readsById(rec);
    const need = (id) => { if (!R[id]) throw new Error(`case ${rec.n} missing read ${id}`); return R[id]; };
    codec.beginCase();
    const hi = Number.parseInt(rec.args[0], 16) >>> 0;
    const lo = Number.parseInt(rec.args[1], 16) >>> 0;
    const p1 = (BigInt(hi) << 32n) | BigInt(lo);
    const p1s = BigInt.asIntN(64, p1);
    const p10 = Number.parseInt(rec.args[3], 16) | 0;
    const p11 = Number.parseInt(rec.args[4], 16) | 0;
    const p12 = Number.parseInt(rec.args[5], 16) | 0;
    const p13 = Number.parseInt(rec.args[6], 16) | 0;
    const p14 = Number.parseInt(rec.args[7], 16) | 0;
    const e0 = beU32(need("p9_e0").be_hex);
    codec.wBytes(P9 + 0xe0, swapped(need("p9_e0").be_hex, 4));
    const audit = codec.auditReads({ mustWrite: [[P9 + 0xe0, 4]], arenaOk: [] });
    codec.snapshotExpected();
    callLog.length = 0;
    let trap = null;
    try {
      ex.FUN_800c4468(p1, ...DSENT, P9, p10, p11, p12, p13, p14, 0, 0);
    } catch (e) { trap = String((e && e.message) || e); }
    const problems = [];
    if (trap) problems.push({ trap });
    const names = callLog.map((c) => c.name);
    if (names.length !== 2 || names[0] !== "zz_00076d0_" || names[1] !== "zz_00097b4_") {
      problems.push({ calls: names });
    } else {
      const a = callLog[0].args, b = callLog[1].args;
      if (BigInt.asIntN(64, a[0]) !== p1s) problems.push({ arg: "fwd.param_1", got: String(a[0]), want: String(p1s) });
      for (let i = 0; i < 7; i++) {
        if (a[1 + i] !== DSENT[i]) problems.push({ arg: `fwd.param_${2 + i}`, got: a[1 + i], want: DSENT[i] });
      }
      if ((a[8] | 0) !== (e0 | 0)) problems.push({ arg: "fwd.[p9+0xe0]", got: (a[8] >>> 0).toString(16), want: e0.toString(16) });
      if ((a[9] >>> 0) !== (P9 + 0x114)) problems.push({ arg: "fwd.p9+0x114", got: (a[9] >>> 0).toString(16), want: (P9 + 0x114).toString(16) });
      if ((a[10] | 0) !== p11) problems.push({ arg: "fwd.param_11", got: a[10], want: p11 });
      if ((a[11] | 0) !== p12) problems.push({ arg: "fwd.param_12", got: a[11], want: p12 });
      if ((a[12] | 0) !== p13) problems.push({ arg: "fwd.param_13", got: a[12], want: p13 });
      if ((a[13] | 0) !== p14) problems.push({ arg: "fwd.param_14", got: a[13], want: p14 });
      if ((b[0] | 0) !== (e0 | 0)) problems.push({ arg: "notify.[p9+0xe0]", got: (b[0] >>> 0).toString(16), want: e0.toString(16) });
      if ((b[1] | 0) !== 0x44) problems.push({ arg: "notify.literal", got: b[1], want: 0x44 });
    }
    const post = codec.diffPostState([]);
    const cls = problems.length === 0 ? "exact" : "unexplained";
    return finish("FUN_800c4468", rec, cls, audit, post, { problems }, false);
  };

  // ---------------------------------------------------------- zz_00c44a8_
  const runC44a8 = (codec, rec) => {
    const R = readsById(rec), W = writesById(rec);
    const need = (id) => { if (!R[id]) throw new Error(`case ${rec.n} missing read ${id}`); return R[id]; };
    codec.beginCase();
    codec.wBytes(ACT + 0x20, swapped(need("a20_pos").be_hex, 4));
    codec.wBytes(ACT + 0x174, swapped(need("a174_target").be_hex, 4));
    const audit = codec.auditReads({
      mustWrite: [[ACT + 0x20, 12], [ACT + 0x174, 12]], arenaOk: [],
    });
    codec.snapshotExpected();
    callLog.length = 0;
    let trap = null;
    try { ex.zz_00c44a8_(ACT); } catch (e) { trap = String((e && e.message) || e); }
    const problems = [];
    // the two ROM helpers must see the matrix, the rate, and the two DAT_ tables
    const ef4 = callLog.filter((c) => c.name === "zz_0045ef4_");
    if (ef4.length >= 1) {
      if ((ef4[0].args[0] >>> 0) !== (ACT + 0x114)) problems.push({ arg: "ef4.mtx", got: (ef4[0].args[0] >>> 0).toString(16) });
      if (ef4[0].args[1] !== 5) problems.push({ arg: "ef4.axis", got: ef4[0].args[1], want: 5 });
      if ((ef4[0].args[3] >>> 0) !== 0x802b0cb4) problems.push({ arg: "ef4.tbl", got: (ef4[0].args[3] >>> 0).toString(16), want: "802b0cb4" });
    } else problems.push({ calls: callLog.map((c) => c.name) });
    const a56a0 = callLog.filter((c) => c.name === "zz_00456a0_");
    if (a56a0.length !== 1 || (a56a0[0].args[2] >>> 0) !== (ACT + 0x58)) {
      problems.push({ arg: "456a0", got: a56a0.map((c) => (c.args[2] >>> 0).toString(16)) });
    }
    const { cls: cmpCls, fieldDump, gotBacks } = trap
      ? { cls: "unexplained", fieldDump: [], gotBacks: [] }
      : compare(codec, [
        { name: "w120", addr: ACT + 0x120, kind: "bits", wantHex: W.w120.be_hex },
        { name: "w130", addr: ACT + 0x130, kind: "bits", wantHex: W.w130.be_hex },
        { name: "w140", addr: ACT + 0x140, kind: "bits", wantHex: W.w140.be_hex },
      ]);
    const post = codec.diffPostState(gotBacks);
    const cls = (problems.length || trap) ? "unexplained" : cmpCls;
    return finish("zz_00c44a8_", rec, cls, audit, post, { trap, fields: fieldDump, problems }, false);
  };

  // ---------------------------------------------------------- zz_00c4540_
  const runC4540 = (codec, rec) => {
    const R = readsById(rec), W = writesById(rec);
    const need = (id) => { if (!R[id]) throw new Error(`case ${rec.n} missing read ${id}`); return R[id]; };
    codec.beginCase();
    const typeByte = beBytes(need("a11_type").be_hex)[0];
    const idx = typeByte * 0x44;
    const trackPre = beU32(need("ac8_track").be_hex);
    const mustWrite = [];
    const put = (addr, bytes) => { codec.wBytes(addr, bytes); mustWrite.push([addr, bytes.length]); };

    codec.wU8(ACT + 0x11, typeByte); mustWrite.push([ACT + 0x11, 1]);
    put(ACT + 0x20, swapped(need("a20_pos").be_hex, 4));
    put(ACT + 0x38, swapped(need("a38_vel").be_hex, 4));
    put(ACT + 0x44, swapped(need("a44_speed").be_hex, 4));
    put(ACT + 0x144, swapped(need("a144_mtx").be_hex, 4));
    put(ACT + 0x174, swapped(need("a174_target").be_hex, 4));
    codec.wU8(ACT + 0x1cb, beBytes(need("a1cb_pre").be_hex)[0]); mustWrite.push([ACT + 0x1cb, 1]);
    // rebase the tracked-object pointer (0 stays 0 — the branch key)
    codec.wU32(ACT + 0xc8, trackPre === 0 ? 0 : TRK); mustWrite.push([ACT + 0xc8, 4]);
    if (trackPre !== 0) {
      if (!R.track_64) throw new Error(`case ${rec.n}: non-null tracker but no track_64 read`);
      put(TRK + 0x64, swapped(R.track_64.be_hex, 4));
    }
    // per-type table row, at its real (compiled-in) addresses
    put(TBL + idx, swapped(need("row_vec").be_hex, 4));
    codec.wU8(0x80303157 + idx, beBytes(need("row_157").be_hex)[0]);
    mustWrite.push([0x80303157 + idx, 1]);
    put(0x80303158 + idx, swapped(need("row_158").be_hex, 4));
    put(0x80303160 + idx, swapped(need("row_160").be_hex, 4));
    // constants
    put(0x80438744, swapped(need("f_8744").be_hex, 4));
    put(0x80438748, swapped(need("d_8748").be_hex, 8));
    put(0x80438750, swapped(need("d_8750").be_hex, 8));
    put(SDKC, swapped(need("sdk_ca90").be_hex, 4)); // two f32s, element width 4

    const audit = codec.auditReads({ mustWrite, arenaOk: [] });
    codec.snapshotExpected();
    callLog.length = 0;
    let trap = null;
    try { ex.zz_00c4540_(ACT); } catch (e) { trap = String((e && e.message) || e); }
    const tainted = callLog.some((c) => TAINTING.has(c.name));

    // ---- derive the branch the CONSOLE took, from console evidence only ----
    const trackPost = beU32(W.wc8.be_hex);
    const cPre = beBytes(need("a1cb_pre").be_hex)[0];
    const cPost = beBytes(W.w1cb.be_hex)[0];
    const reload = beBytes(need("row_157").be_hex)[0];
    const decremented = (cPre - 1) & 0xff;
    let branch;
    if (trackPre === 0) branch = "null_tracker";
    else if (trackPost === 0) branch = "cleared";
    else if (cPost === reload && cPost !== decremented) branch = "reaim";
    else if (cPost === decremented) branch = "decrement";
    else branch = "ambiguous";
    tally.branch[branch] = (tally.branch[branch] ?? 0) + 1;

    const problems = [];
    if (branch === "ambiguous") {
      problems.push({ branch: "console evidence does not identify a branch", trackPre: trackPre.toString(16), trackPost: trackPost.toString(16), cPre, cPost, reload });
    }
    // ---- require the wasm to have taken the SAME branch ----
    const reaimCalls = callLog.filter((c) => c.name === "zz_006c440_");
    const notifyCalls = callLog.filter((c) => c.name === "zz_00833a4_");
    const wasmReaim = reaimCalls.length > 0;
    if (!trap) {
      if ((branch === "reaim") !== wasmReaim) {
        problems.push({ branch, wasm_reaim: wasmReaim, detail: "wasm branch disagrees with the console" });
      }
      if (branch === "reaim") {
        if (notifyCalls.length !== 1) problems.push({ arg: "zz_00833a4_ calls", got: notifyCalls.length });
        else if ((notifyCalls[0].args[0] >>> 0) !== ACT) problems.push({ arg: "zz_00833a4_.actor", got: (notifyCalls[0].args[0] >>> 0).toString(16) });
        if (reaimCalls.length !== 1) problems.push({ arg: "zz_006c440_ calls", got: reaimCalls.length });
        else {
          const rate = new DataView(swapped(need("row_158").be_hex, 4).buffer).getFloat32(0, true);
          if (reaimCalls[0].args[0] !== rate) problems.push({ arg: "zz_006c440_.rate", got: reaimCalls[0].args[0], want: rate });
          if ((reaimCalls[0].args[1] >>> 0) !== ACT) problems.push({ arg: "zz_006c440_.actor", got: (reaimCalls[0].args[1] >>> 0).toString(16) });
        }
      }
      const gotC8raw = dv.getUint32(ACT + 0xc8, true) >>> 0;
      if ((branch === "cleared") !== (trackPre !== 0 && gotC8raw === 0)) {
        problems.push({ branch, wasm_cleared: gotC8raw === 0, detail: "wasm clear-of-a+0xc8 disagrees with the console" });
      }
    }

    // a+0xc8 write-back: the console keeps its own pointer or clears it to 0;
    // the replay keeps the rebased TRK or clears it to 0.
    let expectC8;
    if (trackPost === 0) expectC8 = 0;
    else if (trackPost === trackPre) expectC8 = TRK;
    else { expectC8 = null; problems.push({ wc8: "console stored a pointer that is neither the entry value nor 0", pre: trackPre.toString(16), post: trackPost.toString(16) }); }

    // On a re-aim case zz_006c440_ owns a+0x38 / a+0x20 (steer, renormalize,
    // rescale, advance) and therefore a+0x180 too — comparing them would test
    // the callee, not this unit. Compare only what the unit provably owns.
    const calleeOwned = branch === "reaim";
    const fields = [
      { name: "w150", addr: ACT + 0x150, kind: "bits", wantHex: W.w150.be_hex },
      { name: "w160", addr: ACT + 0x160, kind: "bits", wantHex: W.w160.be_hex },
      { name: "w170", addr: ACT + 0x170, kind: "bits", wantHex: W.w170.be_hex },
      { name: "w1cb", addr: ACT + 0x1cb, kind: "u8", wantHex: W.w1cb.be_hex },
    ];
    if (!calleeOwned) {
      fields.unshift(
        { name: "w38x", addr: ACT + 0x38, kind: "f32", wantHex: W.w38.be_hex.slice(0, 8) },
        { name: "w38y", addr: ACT + 0x3c, kind: "f32", wantHex: W.w38.be_hex.slice(8, 16) },
        { name: "w38z", addr: ACT + 0x40, kind: "f32", wantHex: W.w38.be_hex.slice(16, 24) },
        { name: "w20x", addr: ACT + 0x20, kind: "f32", wantHex: W.w20.be_hex.slice(0, 8) },
        { name: "w20y", addr: ACT + 0x24, kind: "f32", wantHex: W.w20.be_hex.slice(8, 16) },
        { name: "w20z", addr: ACT + 0x28, kind: "f32", wantHex: W.w20.be_hex.slice(16, 24) },
        { name: "w180", addr: ACT + 0x180, kind: "f32", wantHex: W.w180.be_hex },
      );
      tally.full_compare++;
    } else {
      tally.reduced_compare++;
    }
    const { cls: cmpCls, fieldDump, gotBacks } = trap
      ? { cls: "unexplained", fieldDump: [], gotBacks: [] }
      : compare(codec, fields);
    let cls = cmpCls;
    if (!trap && calleeOwned) {
      // The wasm DID write these; accept its own bytes so the stray-write
      // detector does not double-report a region the console does not define.
      for (const [addr, len] of [[ACT + 0x38, 12], [ACT + 0x20, 12], [ACT + 0x180, 4]]) {
        const b = new Uint8Array(len);
        for (let i = 0; i < len; i++) b[i] = codec.u8[addr + i];
        gotBacks.push({ addr, bytes: b });
      }
    }
    if (!trap && expectC8 !== null) {
      const gotC8 = dv.getUint32(ACT + 0xc8, true) >>> 0;
      gotBacks.push({ addr: ACT + 0xc8, bytes: new Uint8Array([codec.u8[ACT + 0xc8], codec.u8[ACT + 0xc9], codec.u8[ACT + 0xca], codec.u8[ACT + 0xcb]]) });
      if (gotC8 !== (expectC8 >>> 0)) {
        fieldDump.push({ f: "wc8", got: gotC8.toString(16), want: (expectC8 >>> 0).toString(16) });
        cls = "unexplained";
      }
    }
    if (trap || problems.length) cls = "unexplained";
    const post = codec.diffPostState(gotBacks);
    return finish("zz_00c4540_", rec, cls, audit, post,
      { trap, type_byte: typeByte, branch, callee_owned_fields: calleeOwned ? ["w38", "w20", "w180"] : [], fields: fieldDump, problems },
      tainted || calleeOwned);
  };

  const table = {
    FUN_800c42bc: runC42bc,
    FUN_800c4448: runC4448,
    FUN_800c4468: runC4468,
    zz_00c44a8_: runC44a8,
    zz_00c4540_: runC4540,
  };

  return {
    unit: meta.unit,
    handleRecord(codec, rec) {
      if (rec.kind !== "case") throw new Error(`unknown record kind ${rec.kind}`);
      const run = table[rec.fn];
      if (!run) throw new Error(`case ${rec.n}: no runner for ${rec.fn}`);
      return run(codec, rec);
    },
  };
}

export const __specPath = fileURLToPath(import.meta.url);
