// auto-c0001-007.spec.mjs — Stage-B trace pilot spec (dolphin_trace replay).
//
// Reference (design v1 Stage B, playable-port-design.md): the REAL GAME running
// in the bundled Dolphin 2606-97 is the oracle. Each fixture case is one actual
// call of zz_0010980_ captured live at 0x80010980 by
// research/tools/dolphin-trace/capture_oracle.py (GDB-stub breakpoints at
// entry + the caller's return address): entry registers, every byte the
// function's verbatim C can read (typed, big-endian as captured from GC RAM),
// and the post-return bytes of its write set. Replay = rebase the two captured
// pointers into fixed scratch regions, byte-swap scalars to the harness's
// little-endian arena convention (element-wise, per gen_arena_rom_provenance.py),
// call the staged wasm, byte-compare the write set. "exact" = every write-set
// byte identical to the console's and no stray writes.
//
// Covered function (the ONLY export with a captured corpus so far):
//   zz_0010980_ (0x80010980) — player marker RGBA selector; void(int ui).
//     flag [ui+0x1da]==0 -> fades alpha byte [ui+0x35b] by FLOAT_80436ae4 via
//     the PPC CONCAT44 int->double idiom (DOUBLE_80436b88 = 2^52 magic);
//     else selects RGBA from state bytes [[ui+0x290]+0x10..0x11].
//     Writes ONLY ui+0x358..0x35b.
//
// EXPORT COVERAGE (§3.4): the other 7 exports have no trace corpus yet; they
// are listed in meta.uncovered_exports, forcing verdict PARTIAL at best. A
// partial verdict is the honest pilot statement: "this function replays
// byte-exactly against the real game"; unit-level promotion needs corpora for
// the rest (same tool, more capture plans — several need captured-subcall
// stubs for their env imports, a mechanism this pilot deliberately excludes).
//
// CORPUS HONESTY NOTE: the pilot corpus (auto-c0001-007.dolphin-trace.jsonl)
// was captured in the owner's "2v2 gred controlled players no cpu" savestate
// under synthesized pad input. In that state every observed call took the
// flag==0 fade path with alpha already 0 — the corpus exercises ONE branch
// (fade-at-floor) of the function. That is a real limitation of the capture
// GAME STATE, not of the mechanism; it is stated here so nobody mistakes this
// PARTIAL for behavioral coverage of all branches. min_cases still guards
// corpus presence.
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";

const here = path.dirname(fileURLToPath(import.meta.url));

const ACT = 0x80600000;  // rebased ui struct (scratch above all DOL/bss, damage-core convention)
const SUB = 0x80602000;  // rebased [ui+0x290] state struct
const CONST_D = 0x80436b88; // DOUBLE_80436b88 (2^52 int->double magic)
const CONST_F = 0x80436ae4; // FLOAT_80436ae4 (fade factor)

export const meta = {
  unit: "auto-c0001-007",
  reference_kind: "dolphin_trace",
  references: [
    "real GG4E in bundled Dolphin 2606-97 (GDB-stub per-call capture; tool: research/tools/dolphin-trace/capture_oracle.py; plan: research/tools/dolphin-trace/plans/auto-c0001-007.zz_0010980_.json)",
  ],
  arena: "arena-trace-empty.json",
  wasmDefault: "../port-units-staging/auto-c0001-007/unit.wasm",
  fixture: "corpora/auto-c0001-007.dolphin-trace.jsonl",
  functions: [
    { name: "zz_0010980_", rounding_bound: 0, min_cases: 100,
      reference: "dolphin_trace 0x80010980 (entry+LR breakpoint capture, per-call args/reads/writes)",
      note: "marker RGBA selector; corpus currently exercises the flag==0 fade path only (see CORPUS HONESTY NOTE)" },
  ],
  uncovered_exports: [
    "FUN_800108c8", "FUN_80010924", "zz_00107a0_", "zz_001080c_",
    "zz_0010b50_", "zz_0010b64_", "zz_0010c7c_",
  ],
  regions: [
    { name: "ACT", base: ACT, size: 0x400 },
    { name: "SUB", base: SUB, size: 0x20 },
    { name: "CONST_D", base: CONST_D, size: 8 },
    { name: "CONST_F", base: CONST_F, size: 4 },
  ],
};

// zz_0010980_ calls no env imports; anything else is a loud Proxy throw.
export function makeShims() {
  return {};
}

const beBytes = (hex) => {
  const b = Buffer.from(hex, "hex");
  return new Uint8Array(b);
};
const leBytes = (hex) => beBytes(hex).slice().reverse();

export function createRunner({ ex }) {
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

      codec.beginCase();
      // ui struct (rebased): flag byte + prior RGBA bytes (byte array — no swap)
      const flag = beBytes(need("flag_1da").be_hex)[0];
      codec.wU8(ACT + 0x1da, flag);
      codec.wBytes(ACT + 0x358, beBytes(need("rgba_pre").be_hex));
      // rebase the state pointer; seed the state bytes when captured
      codec.wU32(ACT + 0x290, SUB);
      const mustWrite = [
        [ACT + 0x1da, 1], [ACT + 0x358, 4], [ACT + 0x290, 4],
        [CONST_D, 8], [CONST_F, 4],
      ];
      if (byId.state_1011) {
        codec.wBytes(SUB + 0x10, beBytes(byId.state_1011.be_hex));
        mustWrite.push([SUB + 0x10, 2]);
      }
      // constants: element-wise byte swap BE->LE (f64 and f32 single elements)
      codec.wBytes(CONST_D, leBytes(need("dconst_80436b88").be_hex));
      codec.wBytes(CONST_F, leBytes(need("fconst_80436ae4").be_hex));

      const audit = codec.auditReads({ mustWrite, arenaOk: [] });
      codec.snapshotExpected();

      let trap = null;
      try { ex.zz_0010980_(ACT); }
      catch (e) { trap = String((e && e.message) || e); }

      const wantPost = rec.writes.find((w) => w.id === "rgba_post");
      const post = codec.diffPostState([
        { addr: ACT + 0x358, bytes: beBytes(wantPost.be_hex) },
      ]);
      const ok = trap == null
        && post.writeBackMismatches.length === 0
        && post.strayWrites.length === 0;
      return {
        fn: "zz_0010980_", n: rec.n, cls: ok ? "exact" : "unexplained", audit, post,
        dump: ok ? null : {
          n: rec.n, trap, flag,
          rgba_pre: need("rgba_pre").be_hex, rgba_want: wantPost.be_hex,
          mismatches: post.writeBackMismatches, stray: post.strayWrites.map((a) => "0x" + a.toString(16)),
        },
      };
    },
  };
}
