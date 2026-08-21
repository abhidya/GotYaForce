// auto-c0034-018.spec.mjs — Phase 2 pilot differential spec (staged unit,
// oracle-workstream-plan.md §3.4 / §6 Phase 2).
//
// Reference (I-10): reference_kind "ts_port" — packages/combat/src/families/
// wire-gunner.ts, consumed via the seam-spy esbuild bundle refs/wire-gunner-ref.mjs
// (gen_wire_gunner_ref.mjs; same bundling path as the PoC, plan §1.3). Differential
// green means "agrees with the reviewed TS port", not ground truth (F-3).
//
// EXPORT COVERAGE (the honest pilot result, §3.4 per-function mandate):
// the oracle registry ranks this unit differential_vs_ts on the strength of ONE
// port-grade function (FUN_80130788 -> wire-gunner.ts:152). The other five exported
// functions have NO reference implementation in packages/combat/src/:
//   FUN_80130154  citation_grade none  (wire hit/FX helper — unported)
//   FUN_80130330  citation_grade none  (borg 0x106/0x107/0x103 part handler — unported)
//   FUN_801304b8  citation_grade none  (charge/state handler — unported)
//   FUN_801307c4  citation_grade weak  (wire-gunner.ts:162 is a TODO row comment,
//                                       not a port — actionTable[0] is null)
//   FUN_80130844  citation_grade none  (secondary dispatcher — unported)
// Hand-writing references for them would be reverse-fitting the oracle; they are
// listed in meta.uncovered_exports, which forces verdict PARTIAL at best (the run
// can never print the PASS total line, exit 0, or be promoted). Blocker class:
// named spec gap — "differential spec cannot cover the export set until the
// wire-gunner family port grows real handlers for rows 0/1/3/4".
//
// Read-set (mechanism 2), authored line-by-line from the verbatim C
// (research/decomp/port-units-staging/auto-c0034-018/unit.c):
//   FUN_80130788 (chunk_0034.c:4954-4961):
//     reads  ACT+0x580 (signed char action index);
//            dispatch table cells (&PTR_FUN_80335cb8)[idx] — 4 bytes each.
//     writes nothing; tail-calls the row via call_indirect.
//
// Dispatch-seam instrumentation: the ROM table rows are function POINTERS
// (DOL @0x80335cb8: row0=0x801307c4, row1=0x80131598, row2=0x80131688,
// row3=0x80131834, row4=0x80130844 — matching the TS actionTable's row comments).
// The callees live OUTSIDE this unit (row 2 is in auto-c0035-002), so the table
// window is a declared, codec-tracked scratch region — the call_indirect analogue
// of the zz_* import shims: the case's own cell gets the spy's wasm-table index,
// every other cell gets an out-of-bounds index, so a wrong-cell read traps loudly
// instead of silently dispatching. The spy slot is table index 1 (the unit's
// exported __indirect_function_table has max=2 and cannot grow; slot 1's original
// element is never call_indirect'ed by the covered function).
//
// Corpus (generate mode, I-2): the domain of +0x580 for this family is the TS
// actionTable's five rows (0..4, wire-gunner.ts:161-167; row addresses confirmed
// against boot.dol above). Domain justification: +0x580 is read as a SIGNED char
// and used as a table row; rows beyond 4 belong to the next table
// (PTR_FUN_80335cc8) and are not this dispatcher's domain. Exhaustive per the
// Phase 2 gate's "exhaustive where the domain is smaller" clause: n=5.
import fs from "node:fs";
import path from "node:path";
import { fileURLToPath } from "node:url";
import { createHash } from "node:crypto";
import * as REF from "../refs/wire-gunner-ref.mjs";

const here = path.dirname(fileURLToPath(import.meta.url));
const root = path.resolve(here, "..", "..", "..", "..");

// F4/F9 staleness binding: the seam-spy bundle must describe the wire-gunner.ts
// that exists NOW (LF-normalized, like the actor-field-map binding).
{
  const src = fs.readFileSync(path.join(root, ...REF.__source.split("/"))).toString("utf8").replace(/\r\n/g, "\n");
  const sha = createHash("sha256").update(Buffer.from(src, "utf8")).digest("hex");
  if (sha !== REF.__source_sha256) {
    throw new Error("refs/wire-gunner-ref.mjs is stale: regenerate with gen_wire_gunner_ref.mjs");
  }
}

const ACT = 0x80600000;        // scratch actor (free region above all DOL/bss sections)
const DISP = 0x80335cb8;       // FUN_80130788's dispatch table window (5 rows x 4B)
const ROWS = 5;
const SPY_SLOT = 1;            // wasm table index holding the dispatch spy
const INVALID = 0x7fffffff;    // out-of-bounds table index: wrong-cell reads trap

export const meta = {
  unit: "auto-c0034-018",
  reference_kind: "ts_port",
  references: [
    "packages/combat/src/families/wire-gunner.ts (createWireGunnerRootAction, via refs/wire-gunner-ref.mjs seam-spy bundle)",
  ],
  arena: "arena-wire-gunner.json",
  wasmDefault: "../port-units-staging/auto-c0034-018/unit.wasm",
  // n counts the exhaustive dispatch cases; generateCorpus always appends the two
  // dispatch-control cases (review P3) on top, so the default run is 7 cases.
  corpus: { mode: "generate", seed: 0x340018, n: ROWS },
  // F-5: rounding_bound 0 — pure table dispatch, no float path anywhere in the
  // covered function; there is no legitimate f32-vs-f64 divergence channel.
  // min_cases (review P1): 5 exhaustive rows + 2 controls; fewer proves nothing.
  functions: [
    { name: "FUN_80130788", rounding_bound: 0, min_cases: ROWS + 2,
      reference: "wire-gunner.ts:158-172 createWireGunnerRootAction — dispatch rule actionTable[actor.actionIndex]",
      note: "root action dispatcher; differential = invoked ROM table row == actionIndex; includes negative dispatch control" },
  ],
  uncovered_exports: [
    "FUN_80130154", "FUN_80130330", "FUN_801304b8", "FUN_801307c4", "FUN_80130844",
  ],
  regions: [
    { name: "ACT", base: ACT, size: 0x600 },
    { name: "DISP", base: DISP, size: ROWS * 4 },
  ],
};

// FUN_80130788 calls no env imports; anything else is a loud Proxy throw.
export function makeShims() {
  return {};
}

// Minimal hand-assembled spy module: import env.hook ()->void, export spy ()->void
// calling it — the only way to observe which table cell the dispatcher read
// (call_indirect requires a real wasm funcref; JS functions are not settable).
function spyModuleBytes() {
  const bytes = [0x00, 0x61, 0x73, 0x6d, 1, 0, 0, 0];
  const sec = (id, body) => { bytes.push(id, body.length, ...body); };
  sec(1, [2, 0x60, 0, 0, 0x60, 0, 0]);                       // types: ()->void x2
  sec(2, [1, 3, 0x65, 0x6e, 0x76, 4, 0x68, 0x6f, 0x6f, 0x6b, 0x00, 0x00]); // env.hook
  sec(3, [1, 1]);                                            // one fn of type 1
  sec(7, [1, 3, 0x73, 0x70, 0x79, 0x00, 1]);                 // export "spy"
  sec(10, [1, 4, 0, 0x10, 0x00, 0x0b]);                      // body: call $hook; end
  return new Uint8Array(bytes);
}

export function generateCorpus({ n }) {
  // Exhaustive over the 5-row action table; deterministic (no PRNG draw needed —
  // the domain is fully enumerated; --n repeats the cycle).
  const recs = [];
  for (let i = 0; i < n; i++) recs.push({ kind: "dispatch", n: i, k: i % ROWS });
  // Dispatch controls (review P3) — committed proof that the spy observable really
  // discriminates rows, i.e. a hit means "the dispatcher read cell k", not "the
  // spy is reachable from anywhere":
  //   negctl: actionIndex=0 with the spy at cell 2 — the dispatcher must NOT reach
  //           the spy; the expected outcome is a trap at cell 0's invalid index.
  //   posctl: actionIndex=2 with the spy at cell 2 — must hit (the aimed twin).
  recs.push({ kind: "dispctl", n: n, k: 0, aim: 2, expect: "trap" });
  recs.push({ kind: "dispctl", n: n + 1, k: 2, aim: 2, expect: "hit" });
  return recs;
}

export function createRunner({ ex }) {
  let spyHits = 0;
  const spy = new WebAssembly.Instance(new WebAssembly.Module(spyModuleBytes()), {
    env: { hook: () => { spyHits++; } },
  });
  ex.__indirect_function_table.set(SPY_SLOT, spy.exports.spy);

  const rootAction = REF.createWireGunnerRootAction({
    onFamilyProjectile: (_a, _addr, kind) => REF.__seamLog.push({ seam: "projectile", kind }),
  });

  return {
    unit: meta.unit,
    handleRecord(codec, rec) {
      if (rec.kind !== "dispatch" && rec.kind !== "dispctl") throw new Error(`unknown record kind ${rec.kind}`);
      const k = rec.k;
      // dispatch: spy at the reference-predicted cell k. dispctl: spy at rec.aim,
      // which for the negative control is NOT the driven index — a spy hit there
      // would mean the observable does not discriminate rows.
      const aimed = rec.kind === "dispctl" ? rec.aim : k;
      codec.beginCase();
      codec.encodeField(ACT, "actionIndex", k); // +0x580 via the extracted field map
      // Instrumented dispatch window: only the aimed row is callable.
      for (let j = 0; j < ROWS; j++) codec.wU32(DISP + 4 * j, j === aimed ? SPY_SLOT : INVALID);
      const audit = codec.auditReads({
        mustWrite: [[ACT + 0x580, 1], [DISP, ROWS * 4]],
        arenaOk: [],
      });
      codec.snapshotExpected();

      // Reference: the TS dispatch rule selects actionTable[actionIndex] — i.e. the
      // predicted ROM row is k itself. Executing the bundled rootAction documents
      // that rule live (row 2 runs the ported X handler; other rows are null TODOs).
      REF.__resetSeams();
      rootAction({
        actionIndex: k, fbPhaseSlots: [0, 0, 0, 0], controlWord: 0,
        ubState: 0, contactP0: 0, wallContact: 0, dt: 1 / 60, stateTimer: 0,
      });
      const refRowRan = REF.__seamLog.length > 0; // informational (row 2 only)

      spyHits = 0;
      let trap = null;
      try { ex.FUN_80130788(ACT); }
      catch (e) { trap = String(e && e.message || e); }
      const post = codec.diffPostState([]); // the dispatcher writes nothing
      const ok = rec.expect === "trap"
        ? trap != null && spyHits === 0   // negctl: wrong-cell read must trap, spy untouched
        : trap == null && spyHits === 1;  // dispatch/posctl: exactly one spy hit
      return {
        fn: "FUN_80130788", n: rec.n, cls: ok ? "exact" : "unexplained", audit, post,
        dump: ok ? null : { n: rec.n, kind: rec.kind, actionIndex: k, aimed, expect: rec.expect ?? "hit", spyHits, trap, refRowRan },
      };
    },
  };
}
