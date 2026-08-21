// auto-c0035-002.spec.mjs — Phase 2 pilot differential spec (staged unit,
// oracle-workstream-plan.md §3.4 / §6 Phase 2).
//
// Reference (I-10): reference_kind "ts_port" — packages/combat/src/families/
// wire-gunner.ts (the WIRE GUNNER X-special phase machine), consumed via the
// seam-spy esbuild bundle refs/wire-gunner-ref.mjs. Both sides are cut at the SAME
// ROM function boundary: zz_004beb8_ <-> startStream, zz_004cd24_ <-> tickStream,
// zz_006a668_ <-> ctx.onFamilyProjectile, so the differential compares the unit's
// decisions (branch selection, mask/slot/kind arguments, struct write-backs), not
// the out-of-unit stream VM. Differential green would mean "agrees with the
// reviewed TS port", not ground truth (F-3).
//
// EXPORT COVERAGE (§3.4 per-function mandate): the registry ranks this unit
// differential_vs_ts on ONE port-grade function (zz_01316e0_ -> wire-gunner.ts:64/73).
// Covered here:
//   zz_01316e0_   port  — the X-special phase machine (wireGunnerXPhase0/Phase1 via
//                         wireGunnerXHandler; wire-gunner.ts:85-149)
//   FUN_80131688  weak  — its wrapper; wireGunnerXHandler (wire-gunner.ts:145-149)
//                         is explicitly labeled its port. Included because the
//                         reference EXISTS in product code; the weak grade is noted
//                         (the wrapper's +0x1900 timer math is NOT modeled by the
//                         TS port — an expected, recorded divergence, not a spec bug).
// Uncovered (no reference implementation in packages/combat/src/ — hand-writing
// one would be reverse-fitting; blocker class: named spec gap):
//   FUN_80131634  none  (timer shr + zz_0161d7c_ tail — unported)
//   FUN_80131664  none  (zz_01618ac_ tail — unported)
//   FUN_80131834  weak  (wire-gunner.ts:165 is a TODO row comment, not a port)
//   FUN_801318a8  none  (secondary dispatcher — unported)
//   FUN_801318f8  none  (X-init: pose/vec setup — unported)
//   FUN_80131a00  none  (X-tick: pull/contact handler — unported)
//
// Read-set (mechanism 2), authored line-by-line from the verbatim C
// (research/decomp/port-units-staging/auto-c0035-002/unit.c):
//   zz_01316e0_ (chunk_0035.c:601-647):
//     reads  ACT+0x540 (phase byte); ACT+0x5e0 u32 (control word; also RMW &~3 in
//            both fire branches); ACT+0x1cef (part-0 contact); ACT+0x5db (ub state,
//            arm branch); ACT+0x1dc8 f32 (dt), ACT+0x1af8 s16 + ACT+0x1ae0 f32
//            (cooldown pair, air branch); ACT+0x1cee (contact, phase-1);
//            +0x543/+0x6ea are write-then-read (call args) — not harness inputs.
//     arena  FLOAT_80439e90 (arm rate), DOUBLE_80439e88 (air int->float magic).
//     writes +0x540=1 (BOTH phase-0 branches); +0x543, +0x6ea (arm);
//            +0x73f=0, +0x5e0&=~3, +0x694 (air / phase-1 contact — +0x694 air only).
//   FUN_80131688 (chunk_0035.c:578-597):
//     reads  ACT+0x1900 s16; arena FLOAT_80439e80, DOUBLE_80439e88.
//     writes +0x1900 = (short)(int)(reconstructed * 0.96); then calls zz_01316e0_
//            internally (same-unit direct call), so all of the above too.
//
// Known-divergence channels, stated UP FRONT (recorded, not massaged — a red
// staged unit is as valuable as a green one):
//   D1. +0x694 air cooldown: ROM computes dt + (s16(+0x1af8) - f32(+0x1ae0));
//       the TS port documents this as "approximated" by stateTimer = dt
//       (wire-gunner.ts:98-102).
//   D2. Fire-branch cues: the TS port dispatches ub/fb idle cues the ROM function
//       does not call at this boundary (wire-gunner.ts:103-105,135-137).
//   D3. +0x540 on air-fire: the ROM advances the phase byte to 1 BEFORE branching;
//       the TS port leaves phase 0 on the air-fire path (wire-gunner.ts:92-107).
//   D4. +0x73f: ROM clears it in both fire branches; the TS port documents the flag
//       as "unsurfaced; no-op" and never writes it.
//   D5. +0x1900 (wrapper): the staged wasm's PPC int->double idiom is mis-lowered
//       (integer CONCAT44 + arithmetic u64->f64 conversion instead of bit
//       reinterpretation, then saturating trunc), so the wasm stores -1 regardless
//       of input where the ROM stores (short)(int)(0.96 * s16). Probed 2026-08-20:
//       input 100 -> ROM 96, wasm -1. This is a STAGED-UNIT defect, not a spec bug.
//
// Corpus (generate mode, I-2): mulberry32-seeded; alternating "phase" (zz_01316e0_
// direct) and "wrap" (FUN_80131688) records; default n=20000 => 10,000 per function
// (Phase 2 gate: N >= 10,000). Domain constraints, each ROM-justified (F-4):
//   phase in {0,1}      — the values this machine itself produces (fresh spawn 0;
//                         arm writes 1). Phase >= 2 is not producible by the
//                         X-special path and the TS table would no-op there.
//   controlWord         — full u32 (the ROM reads the whole word); the decision
//                         bits 0x1/0x2 (action mode), 0x10 (side), 0x20 (air),
//                         0x40 (up) are drawn independently to exercise every
//                         branch; remaining bits uniform.
//   ubState in 0..3     — s8 upper-body state; 1 triggers the full-body arm widen.
//   contactP0/wallContact in {0,1} — contact flags are boolean gates in the C.
//   +0x1af8 full s16, +0x1ae0 f32 [0,8), dt f32 ~1/60, +0x694 f32 [0,4) — the
//   cooldown/timer operands at their ROM widths.
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { createHash } from "node:crypto";
import { fr } from "../lib/wasm.mjs";
import * as REF from "../refs/wire-gunner-ref.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "..", "..", "..", "..");

// F4/F9 staleness binding (same rule as the actor-field-map source hash).
{
  const src = fs.readFileSync(path.join(root, ...REF.__source.split("/"))).toString("utf8").replace(/\r\n/g, "\n");
  const sha = createHash("sha256").update(Buffer.from(src, "utf8")).digest("hex");
  if (sha !== REF.__source_sha256) {
    throw new Error("refs/wire-gunner-ref.mjs is stale: regenerate with gen_wire_gunner_ref.mjs");
  }
}

const ACT = 0x80600000; // scratch actor (free region above all DOL/bss sections)

export const meta = {
  unit: "auto-c0035-002",
  reference_kind: "ts_port",
  references: [
    "packages/combat/src/families/wire-gunner.ts (X-special phase machine via createWireGunnerRootAction, refs/wire-gunner-ref.mjs seam-spy bundle)",
  ],
  arena: "arena-wire-gunner.json",
  wasmDefault: "../port-units-staging/auto-c0035-002/unit.wasm",
  corpus: { mode: "generate", seed: 0x350002, n: 20000 },
  // F-5: rounding_bound 0 for both — state-machine/flag logic; the only float
  // compared (+0x694) is predicted by the reference's own f32 value, so there is
  // no legitimate f32-vs-f64 divergence channel to explain. Any mismatch is a
  // genuine behavioral divergence (see D1-D5 above), never rounding.
  functions: [
    { name: "zz_01316e0_", rounding_bound: 0,
      reference: "wire-gunner.ts:85-149 wireGunnerXPhase0/Phase1 (via wireGunnerXHandler; port-grade citations :64/:73)",
      note: "X-special phase machine; expected divergences D1-D4" },
    { name: "FUN_80131688", rounding_bound: 0,
      reference: "wire-gunner.ts:145-149 wireGunnerXHandler (wrapper; weak-grade citation :144 — the +0x1900 timer math is unmodeled by the port)",
      note: "wrapper; expected divergences D1-D5" },
  ],
  uncovered_exports: [
    "FUN_80131634", "FUN_80131664", "FUN_80131834", "FUN_801318a8", "FUN_801318f8", "FUN_80131a00",
  ],
  regions: [
    { name: "ACT", base: ACT, size: 0x1e00 },
  ],
};

// Wasm-side seam shims: the three ROM functions the covered code calls, logged in
// the same normalized shape as the TS spy. Everything else stays unshimmed (loud
// Proxy throw). PSVEC/PSQUAT are imported by the module but never reached by the
// covered functions.
const wasmSeams = [];
export function makeShims() {
  return {
    zz_004beb8_: (rate, _actor, mask, group, slot, _a6, _a7) => {
      wasmSeams.push(["stream_arm", mask | 0, group | 0, slot | 0, rate]);
      return 0;
    },
    zz_004cd24_: (_actor, mask) => {
      wasmSeams.push(["stream_tick", mask | 0]);
      return 0;
    },
    zz_006a668_: (...a) => {
      wasmSeams.push(["projectile", a[9] | 0]); // 10th arg = shot kind (4 / 0x1e)
      return 0;
    },
  };
}

// mulberry32 (PoC PRNG lineage, I-2).
function mulberry32(seed) {
  let a = seed >>> 0;
  return function () {
    a |= 0; a = (a + 0x6d2b79f5) | 0;
    let t = Math.imul(a ^ (a >>> 15), 1 | a);
    t = (t + Math.imul(t ^ (t >>> 7), 61 | t)) ^ t;
    return ((t ^ (t >>> 14)) >>> 0) / 4294967296;
  };
}

export function generateCorpus({ seed, n }) {
  const r = mulberry32(seed);
  const bit = (p) => (r() < p ? 1 : 0);
  const recs = [];
  for (let i = 0; i < n; i++) {
    const cw = ((bit(0.5) * 0x1) | (bit(0.5) * 0x2) | (bit(0.5) * 0x10)
      | (bit(0.5) * 0x20) | (bit(0.5) * 0x40)
      | ((r() * 0x100000000) & ~0x73) >>> 0) >>> 0;
    const c = {
      kind: i % 2 === 0 ? "phase" : "wrap",
      n: i,
      phase: bit(0.5),
      cw,
      ubState: Math.floor(r() * 4),
      contactP0: bit(0.5),
      wallContact: bit(0.5),
      t1af8: (Math.floor(r() * 0x10000) << 16) >> 16,
      f1ae0: fr(r() * 8),
      dt: fr((0.5 + r()) / 60),
      timer694: fr(r() * 4),
    };
    if (c.kind === "wrap") c.t1900 = (Math.floor(r() * 0x10000) << 16) >> 16;
    recs.push(c);
  }
  return recs;
}

export function createRunner({ ex, dv }) {
  const rootAction = REF.createWireGunnerRootAction({
    onFamilyProjectile: (_a, _addr, kind) => REF.__seamLog.push({ seam: "projectile", kind }),
  });

  function encodeCase(codec, c) {
    codec.beginCase();
    codec.encodeField(ACT, "fbPhase", c.phase);        // +0x540 via field map
    codec.encodeField(ACT, "controlWord", c.cw);       // +0x5e0
    codec.encodeField(ACT, "ubState", c.ubState);      // +0x5db
    codec.encodeField(ACT, "contactP0", c.contactP0);  // +0x1cef
    codec.encodeField(ACT, "wallContact", c.wallContact); // +0x1cee
    codec.encodeField(ACT, "dt", c.dt);                // +0x1dc8
    codec.encodeField(ACT, "stateTimer", c.timer694);  // +0x694
    // Non-RomActor-mapped operands (per-unit encoder rule, plan §3.3): the air
    // cooldown pair — offsets from the verbatim C, values TS-domain.
    codec.wI16(ACT + 0x1af8, c.t1af8);
    codec.wF32(ACT + 0x1ae0, c.f1ae0);
    if (c.kind === "wrap") codec.wI16(ACT + 0x1900, c.t1900);
  }

  function caseReadSet(c) {
    const mustWrite = [
      [ACT + 0x540, 1], [ACT + 0x5db, 1], [ACT + 0x5e0, 4],
      [ACT + 0x1cee, 1], [ACT + 0x1cef, 1],
      [ACT + 0x1ae0, 4], [ACT + 0x1af8, 2], [ACT + 0x1dc8, 4], [ACT + 0x694, 4],
    ];
    if (c.kind === "wrap") mustWrite.push([ACT + 0x1900, 2]);
    const arenaOk = [
      [0x80439e80, 4],  // FLOAT_80439e80 (wrapper timer scale, 0.96)
      [0x80439e88, 8],  // DOUBLE_80439e88 (int->float magic, 2^52+2^31)
      [0x80439e90, 4],  // FLOAT_80439e90 (stream arm rate, -1.0)
    ];
    return { mustWrite, arenaOk };
  }

  // Run the TS reference on a mirror actor; returns {refActor, refSeams}.
  function runReference(c) {
    const refActor = {
      actionIndex: 2, // the X row — this unit IS the row-2 code block
      fbPhaseSlots: [c.phase, 0, 0, 0],
      controlWord: c.cw >>> 0,
      ubState: c.ubState,
      contactP0: c.contactP0,
      wallContact: c.wallContact,
      dt: c.dt,
      stateTimer: c.timer694,
      streamSlot: null, // null = "not written" marker; the port writes numbers
    };
    REF.__resetSeams();
    rootAction(refActor);
    const refSeams = REF.__seamLog.map((e) =>
      e.seam === "stream_arm" ? ["stream_arm", e.mask, e.group, e.slot, e.rate]
      : e.seam === "stream_tick" ? ["stream_tick", e.mask]
      : e.seam === "projectile" ? ["projectile", e.kind]
      : [e.seam, e.cue]);
    return { refActor, refSeams };
  }

  // Declared write-backs (mechanism 4): every offset in the C write-set, with the
  // reference-predicted bytes — or the snapshot bytes where the reference predicts
  // no write (so an unpredicted ROM write classifies as a per-case mismatch, while
  // truly unmodeled offsets stay loud coverage failures).
  function writeBacks(codec, c, refActor, refSeams) {
    const snap = codec.expected.get("ACT");
    const snapBytes = (off, len) => Array.from(snap.slice(off, off + len));
    const f32Bytes = (v) => { const b = Buffer.alloc(4); b.writeFloatLE(fr(v)); return Array.from(b); };
    const u32Bytes = (v) => { const b = Buffer.alloc(4); b.writeUInt32LE(v >>> 0); return Array.from(b); };
    const wb = [];
    wb.push({ addr: ACT + 0x540, bytes: [refActor.fbPhaseSlots[0] & 0xff] });
    const arm = refSeams.find((e) => e[0] === "stream_arm");
    wb.push({ addr: ACT + 0x543, bytes: arm ? [arm[1] & 0xff] : snapBytes(0x543, 1) });
    wb.push({ addr: ACT + 0x6ea, bytes: refActor.streamSlot != null ? [refActor.streamSlot & 0xff] : snapBytes(0x6ea, 1) });
    wb.push({ addr: ACT + 0x5e0, bytes: u32Bytes(refActor.controlWord) });
    wb.push({ addr: ACT + 0x73f, bytes: snapBytes(0x73f, 1) }); // D4: port never writes it
    wb.push({ addr: ACT + 0x694, bytes: f32Bytes(refActor.stateTimer) });
    if (c.kind === "wrap") wb.push({ addr: ACT + 0x1900, bytes: snapBytes(0x1900, 2) }); // D5
    return wb;
  }

  return {
    unit: meta.unit,
    handleRecord(codec, c) {
      if (c.kind !== "phase" && c.kind !== "wrap") throw new Error(`unknown record kind ${c.kind}`);
      encodeCase(codec, c);
      const audit = codec.auditReads(caseReadSet(c));
      codec.snapshotExpected();

      const { refActor, refSeams } = runReference(c);
      wasmSeams.length = 0;
      let trap = null;
      try {
        if (c.kind === "phase") ex.zz_01316e0_(0, 0, 0, 0, 0, 0, 0, 0, ACT, 0, 0, 0, 0, 0, 0, 0);
        else ex.FUN_80131688(0n, 0n, 0, 0, 0, 0, 0, 0, ACT, 0, 0, 0, 0, 0, 0, 0);
      } catch (e) { trap = String(e && e.message || e); }

      const post = codec.diffPostState(writeBacks(codec, c, refActor, refSeams));
      const seamsEqual = JSON.stringify(wasmSeams) === JSON.stringify(refSeams);
      const ok = trap == null && seamsEqual && post.writeBackMismatches.length === 0;
      const fn = c.kind === "phase" ? "zz_01316e0_" : "FUN_80131688";
      return {
        fn, n: c.n, cls: ok ? "exact" : "unexplained", audit, post,
        dump: ok ? null : {
          n: c.n, case: { ...c }, trap,
          wasmSeams: [...wasmSeams], refSeams,
          writeBackMismatches: post.writeBackMismatches.map((m) => ({
            offset: "0x" + (m.addr - ACT).toString(16), got: m.got, want: m.want,
          })),
        },
      };
    },
  };
}
