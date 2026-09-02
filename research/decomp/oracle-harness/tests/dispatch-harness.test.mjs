// dispatch-harness.test.mjs — the DELIBERATE-RED rehearsal for dispatch_green,
// mirroring gx-callstream-harness.test.mjs and transcript-harness.test.mjs.
//
// A verifier that cannot fail is worse than none, and this standard needs the
// rehearsal more than the others do: it observes the port through imports the
// gate itself emitted, so the whole apparatus could agree with itself while
// being wrong. The spec records that risk as second-review finding Y2 —
// "P3b measures the gate's own lowering and is blind to a wrong thunk".
//
// This file drives run-dispatch.mjs against the committed CONSOLE captures
// (recorded from the real game in Dolphin, Null video, CPU only) and against
// MUTANTS of them — one per divergence class the standard claims to catch,
// including the two that exist only because of Y2:
//
//   * WRONG TARGET      — the console resolved somewhere else
//   * WRONG THUNK       — the emitted table maps an address to the wrong
//                         function, which the registry contradicts
//   * WRONG RESOLUTION  — the module claims in-table for a bridged address
//
// WHY THE MUTANT IS THE CAPTURE AND NOT THE WASM. The comparison is between
// two streams; a divergence is a difference between them and which side moved
// does not change what the comparator has to notice. Mutating the capture also
// needs no emsdk, so this rehearsal runs on a clean checkout — which is why
// the console captures and the lowered modules are both committed.
//
// It also pins the things that keep a dispatch result from being read as one
// of the four wasm-unit tiers: the `standard` field, the verdict token, the
// filename namespace, and the machine-readable claim block.
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
const repoRoot = path.resolve(harnessDir, "..", "..", "..");

// The richest of the committed captures: 40 cases, 4 distinct resolved
// targets, one of them in-table, and a direct out-of-unit call interleaved
// with every dispatch — so wrong-target, wrong-order and extra/short all have
// something to bite on.
const CAP_MIXED = path.join(harnessDir, "corpora", "auto-c0011-005.FUN_80079ab8.dispatch.jsonl");
const WASM_MIXED = path.join(repoRoot, "research/decomp/port-units-dispatch/auto-c0011-005/unit.wasm");
const EV_MIXED = path.join(repoRoot, "research/decomp/port-units-dispatch/auto-c0011-005/gate-evidence.json");
const RESULT_MIXED = "auto-c0011-005.FUN_80079ab8.dispatch.json";

// The capture that carries ARGUMENTS through the uniform frame.
const CAP_ARGS = path.join(harnessDir, "corpora", "auto-c0050-003.zz_01a31d8_.dispatch.jsonl");
const WASM_ARGS = path.join(repoRoot, "research/decomp/port-units-dispatch/auto-c0050-003/unit.wasm");
const EV_ARGS = path.join(repoRoot, "research/decomp/port-units-dispatch/auto-c0050-003/gate-evidence.json");
const RESULT_ARGS = "auto-c0050-003.zz_01a31d8_.dispatch.json";

const readJsonl = (p) =>
  fs.readFileSync(p, "utf8").split(/\r?\n/).filter((l) => l.trim()).map((l) => JSON.parse(l));

/**
 * Write a mutated capture (and optionally a mutated gate-evidence file) into a
 * scratch dir and run the harness on it.
 */
const runOn = ({ capture, wasm, evidence, resultName, mutate, mutateEvidence } = {}) => {
  capture ??= CAP_MIXED; wasm ??= WASM_MIXED; evidence ??= EV_MIXED;
  resultName ??= RESULT_MIXED;
  const scratch = fs.mkdtempSync(path.join(process.env.ORACLE_TEST_TMP_ROOT ?? os.tmpdir(), "gf-disp-"));
  let capturePath = capture;
  if (mutate) {
    const recs = readJsonl(capture);
    mutate(recs);
    capturePath = path.join(scratch, "mutant.jsonl");
    fs.writeFileSync(capturePath, recs.map((r) => JSON.stringify(r)).join("\n") + "\n");
  }
  let evidencePath = evidence;
  if (mutateEvidence) {
    const ev = JSON.parse(fs.readFileSync(evidence, "utf8"));
    mutateEvidence(ev);
    evidencePath = path.join(scratch, "gate-evidence.json");
    fs.writeFileSync(evidencePath, JSON.stringify(ev, null, 1));
  }
  const argv = ["run-dispatch.mjs", "--capture", capturePath,
    "--wasm", wasm, "--gate-evidence", evidencePath,
    // a mutant lives in scratch, so the header's capture-relative arena path
    // would not resolve; the real arena is named explicitly instead.
    "--arena", path.join(harnessDir, "arena-trace-empty.json")];
  const res = spawnSync(process.execPath, argv, {
    cwd: harnessDir,
    env: { ...process.env, ORACLE_RESULTS_DIR: scratch },
    encoding: "utf8",
  });
  const log = (res.stdout ?? "") + (res.stderr ?? "");
  const resultPath = path.join(scratch, resultName);
  const result = fs.existsSync(resultPath) ? JSON.parse(fs.readFileSync(resultPath, "utf8")) : null;
  return { status: res.status, log, result };
};

const firstDispatch = (recs) => {
  for (const r of recs.slice(1)) {
    if (r.kind !== "case") continue;
    const e = r.events.find((x) => x.kind === "dispatch");
    if (e) return { rec: r, ev: e };
  }
  throw new Error("no dispatch in capture");
};

const bumpCounts = (recs, dCase = 0, dEvent = 0, dDispatch = 0) => {
  recs[0].counts.case += dCase; recs[0].counts.event += dEvent; recs[0].counts.dispatch += dDispatch;
  const end = recs[recs.length - 1];
  end.counts.case += dCase; end.counts.event += dEvent; end.counts.dispatch += dDispatch;
};

// ---------------------------------------------------------------------------
// the positive controls
// ---------------------------------------------------------------------------

test("dispatch_green: the lowered module reproduces the console's dispatch stream", () => {
  const { status, log, result } = runOn({});
  assert.equal(status, 0, log);
  assert.equal(result.verdict, "pass");
  assert.equal(result.divergence, null);
  assert.match(log, /VERDICT: DISPATCH_GREEN/);
  assert.equal(result.cases_passed, result.capture.cases);
  assert.equal(result.events_matched, result.capture.events);
  assert.equal(result.targets_compared, result.capture.dispatches);
  // the claim rests on target discrimination, so more than one target must
  // actually have been reached — a single-target corpus proves much less.
  assert.ok(result.resolved_targets.length >= 2, JSON.stringify(result.resolved_targets));
});

test("dispatch_green: arguments marshalled into the uniform frame are compared", () => {
  const { status, log, result } = runOn({
    capture: CAP_ARGS, wasm: WASM_ARGS, evidence: EV_ARGS, resultName: RESULT_ARGS,
  });
  assert.equal(status, 0, log);
  assert.equal(result.verdict, "pass");
  assert.ok(result.arg_slots_compared > 0, "no argument slot was compared");
  assert.ok(result.resolved_targets.length >= 2);
});

test("the result cannot be read as a wasm-unit verification tier", () => {
  const { result } = runOn({});
  assert.equal(result.standard, "dispatch_green");
  for (const forbidden of ["oracle_green", "boundary_green", "transcript_green", "compile_only"]) {
    assert.notEqual(result.standard, forbidden);
  }
  assert.match(JSON.stringify(result.claim.orthogonal_to), /oracle_green/);
  assert.ok(result.claim.not_a_ladder.length > 0);
  // the artifact must say, in machine-readable form, that no write set is compared
  assert.ok(result.claim.does_not_verify.some((s) => /memory write set/i.test(s)));
  // and that the table's CONTENTS were given to the port
  assert.ok(result.claim.does_not_verify.some((s) => /CONTENTS of the ROM's function-pointer table/i.test(s)));
});

test("the artifact records all three wrong-thunk defences", () => {
  const { result } = runOn({});
  const d = result.claim.wrong_thunk_defence;
  assert.equal(d.console_resolved_target, true);
  assert.equal(d.table_audited_against_registry, true);
  assert.equal(d.resolution_class_checked, true);
  assert.equal(result.table_audit.status, "pass");
  assert.ok(result.table_audit.cross_checked > 0);
});

// ---------------------------------------------------------------------------
// the mutants — each must go RED
// ---------------------------------------------------------------------------

test("MUTANT wrong target: a dispatch to a different GC address FAILS", () => {
  const { status, log, result } = runOn({
    mutate: (recs) => {
      const { ev } = firstDispatch(recs);
      const v = parseInt(ev.resolved_target, 16) + 4;
      ev.resolved_target = "0x" + v.toString(16).padStart(8, "0");
    },
  });
  assert.notEqual(status, 0);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.kind, "target");
  assert.match(log, /DISPATCH TARGET divergence/);
});

test("MUTANT wrong target, plausible sibling: swapping two REAL targets FAILS", () => {
  // The sharper version: not a nonsense address, but another address this very
  // corpus dispatches to. A port that dispatched consistently but selected the
  // wrong table entry would look exactly like this.
  const { status, result } = runOn({
    mutate: (recs) => {
      const seen = [];
      for (const r of recs.slice(1)) {
        if (r.kind !== "case") continue;
        for (const e of r.events) if (e.kind === "dispatch" && !seen.includes(e.resolved_target)) seen.push(e.resolved_target);
      }
      assert.ok(seen.length >= 2, "corpus needs two targets for this mutant");
      const { ev } = firstDispatch(recs);
      ev.resolved_target = seen.find((t) => t !== ev.resolved_target);
    },
  });
  assert.notEqual(status, 0);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.kind, "target");
});

test("MUTANT wrong argument: a changed argument register FAILS", () => {
  const { status, log, result } = runOn({
    capture: CAP_ARGS, wasm: WASM_ARGS, evidence: EV_ARGS, resultName: RESULT_ARGS,
    mutate: (recs) => {
      const { ev } = firstDispatch(recs);
      ev.arg_regs.r3 = (ev.arg_regs.r3 ^ 0x10) >>> 0;
    },
  });
  assert.notEqual(status, 0);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.kind, "args");
  assert.match(log, /dispatch-argument divergence/);
});

test("MUTANT wrong result across an in-table dispatch: changed bytes FAIL", () => {
  // Only an IN-TABLE dispatch produces a result the port computed; a bridged
  // one is supplied by the harness. So the mutant targets the in-table
  // dispatch's watch window — the bytes the port's own dispatched code wrote.
  const { status, result } = runOn({
    mutate: (recs) => {
      let touched = false;
      for (const r of recs.slice(1)) {
        if (r.kind !== "case") continue;
        for (const e of r.events) {
          if (e.kind !== "dispatch") continue;
          // in-table target for auto-c0011-005 is FUN_80079b08, and its
          // watch-window bytes are what the port itself produced.
          if (e.resolved_target === "0x80079b08" && e.deltas?.length) {
            const b = Buffer.from(e.deltas[0].b64, "base64");
            b[0] = b[0] ^ 0xff;
            e.deltas[0].b64 = b.toString("base64");
            touched = true;
            break;
          }
        }
        if (touched) break;
      }
      assert.ok(touched, "no in-table dispatch with a watch-window delta to mutate");
    },
  });
  assert.notEqual(status, 0);
  assert.equal(result.verdict, "fail");
  // Compared AT the dispatch when nothing inside it was stubbed, and otherwise
  // replayed and caught at the function's own return. Both are the standard
  // noticing the same wrong bytes; which one fires depends on whether that
  // particular dispatch had to service a nested call.
  assert.ok(["dispatch_owned_write", "owned_write"].includes(result.divergence.kind),
    result.divergence.kind);
});

test("LIMIT a BRIDGED dispatch's return is an INPUT, and the artifact says so", () => {
  // The counterpart of the mutant above, and the reason it has to exist. This
  // harness SUPPLIES a bridged callee's return from the console's r3, so
  // mutating that field cannot red — it changes what the port is given, not
  // what the port produced. A standard that quietly counted it as verified
  // would be claiming its own input back. The test pins both halves: the
  // mutation does not fail the run, AND the claim block declares the limit.
  const { status, result } = runOn({
    mutate: (recs) => {
      let touched = false;
      for (const r of recs.slice(1)) {
        if (r.kind !== "case" || touched) continue;
        for (const e of r.events) {
          if (e.kind === "dispatch" && e.resolved_target !== "0x80079b08" && e.ret_regs) {
            e.ret_regs.r3 = (e.ret_regs.r3 ^ 0x5a5a5a5a) >>> 0;
            touched = true;
            break;
          }
        }
      }
      assert.ok(touched, "no bridged dispatch to mutate");
    },
  });
  assert.equal(status, 0);
  assert.equal(result.verdict, "pass");
  assert.ok(result.claim.does_not_verify.some((s) => /BRIDGED dispatch's return value/.test(s)));
});

test("MUTANT wrong function return: a changed entry return value FAILS", () => {
  const { status, result } = runOn({
    capture: CAP_ARGS, wasm: WASM_ARGS, evidence: EV_ARGS, resultName: RESULT_ARGS,
    mutate: (recs) => {
      // this corpus's function is void; force a non-void expectation and the
      // shape check must catch it rather than quietly ignoring the field.
      recs[0].fn.results = ["i32"];
      for (const r of recs.slice(1)) if (r.kind === "case") r.ret = 1;
    },
  });
  assert.notEqual(status, 0);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.kind, "ret_shape");
});

test("MUTANT wrong order: swapping a dispatch and its neighbouring call FAILS", () => {
  const { status, result } = runOn({
    mutate: (recs) => {
      const r = recs.slice(1).find((x) => x.kind === "case" && x.events.length >= 2);
      assert.ok(r, "need a case with two events");
      const [a, b] = [r.events[0], r.events[1]];
      assert.notEqual(a.kind, b.kind, "the two events must differ in kind for this mutant");
      r.events[0] = { ...b, i: 0 };
      r.events[1] = { ...a, i: 1 };
    },
  });
  assert.notEqual(status, 0);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.kind, "event_kind");
});

test("MUTANT extra event: a dispatch the console never made FAILS", () => {
  const { status, result } = runOn({
    mutate: (recs) => {
      const r = recs.slice(1).find((x) => x.kind === "case");
      r.events.pop();
      r.events.forEach((e, i) => { e.i = i; });
      bumpCounts(recs, 0, -1, 0);
      // the removed event was the direct call, so dispatch count is unchanged
      if (recs[0].counts.dispatch !== recs[recs.length - 1].counts.dispatch) throw new Error("count drift");
    },
  });
  assert.notEqual(status, 0);
  assert.equal(result.verdict, "fail");
  assert.ok(["extra_event", "event_kind"].includes(result.divergence.kind), result.divergence.kind);
});

test("MUTANT wrong PORT: a module that selects the wrong table entry FAILS", () => {
  // The one control that mutates the PORT rather than the capture, and the
  // answer to the standing objection that a thunk-level transcript observes
  // the gate's own lowering and could therefore agree with itself.
  //
  // fixtures/dispatch-wrong-index/unit.wasm is auto-c0011-005 rebuilt from a
  // unit.c in which FUN_80079ab8 reads its vtable index from `param_1 + 0x541`
  // instead of `+ 0x540`. One character. The lowering, the companion, the
  // thunk table and the emcc flags are identical, the emitted table is
  // CORRECT, and the module is entirely self-consistent — so nothing inside
  // the module can notice. The console's own `bctrl` target does.
  const dir = path.join(here, "fixtures", "dispatch-wrong-index");
  const { status, log, result } = runOn({
    wasm: path.join(dir, "unit.wasm"),
    evidence: path.join(dir, "gate-evidence.json"),
  });
  assert.notEqual(status, 0);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.kind, "target");
  // the table itself is fine — this is not the audit firing
  assert.equal(result.table_audit.status, "pass");
  assert.match(log, /the port dispatched to/);
});

test("MUTANT wrong thunk: a table entry the registry contradicts FAILS BEFORE replay", () => {
  // THE Y2 MUTANT. The capture is untouched and the module is untouched; only
  // the emitted table claims a different GC address for a symbol. A transcript
  // taken through such a table would be self-consistent and wrong, so the
  // audit must catch it without needing a divergence at all.
  const { status, log, result } = runOn({
    mutateEvidence: (ev) => {
      ev.dispatch.table[0].gc_address = "deadbeef";
    },
  });
  assert.notEqual(status, 0);
  assert.equal(result.verdict, "fail");
  assert.equal(result.table_audit.status, "fail");
  assert.equal(result.claim.wrong_thunk_defence.table_audited_against_registry, false);
  assert.match(log, /DISPATCH TABLE AUDIT/);
});

test("MUTANT wrong resolution class: an address the table does not hold FAILS", () => {
  // The module reports IN-TABLE for the address it found; delete that address
  // from the audited table and the two must disagree.
  const { status, result } = runOn({
    mutateEvidence: (ev) => {
      ev.dispatch.table = ev.dispatch.table.filter((r) => r.gc_address !== "80079b08");
    },
  });
  assert.notEqual(status, 0);
  assert.equal(result.verdict, "fail");
  assert.equal(result.divergence.kind, "resolution_class");
});

// ---------------------------------------------------------------------------
// non-vacuity — a weak standard is only worth having if it cannot pass on nothing
// ---------------------------------------------------------------------------

test("GUARD an empty capture cannot pass", () => {
  const { status, result } = runOn({
    mutate: (recs) => {
      const header = recs[0], end = recs[recs.length - 1];
      header.counts = { case: 0, event: 0, dispatch: 0 };
      end.counts = { case: 0, event: 0, dispatch: 0 };
      recs.length = 0;
      recs.push(header, end);
    },
  });
  assert.notEqual(status, 0);
  assert.equal(result.verdict, "fail");
  assert.ok(/below the --min-cases floor|no resolved target/.test(result.verdict_note));
});

test("GUARD a case that observed NO dispatch cannot pass", () => {
  const { status, log, result } = runOn({
    mutate: (recs) => {
      const r = recs.slice(1).find((x) => x.kind === "case");
      const removed = r.events.filter((e) => e.kind === "dispatch").length;
      r.events = r.events.filter((e) => e.kind !== "dispatch");
      r.events.forEach((e, i) => { e.i = i; });
      bumpCounts(recs, 0, -removed, -removed);
    },
  });
  assert.notEqual(status, 0);
  assert.equal(result.verdict, "fail");
  assert.match(log, /DISPATCH VACUITY/);
  assert.ok(result.vacuous_cases.length > 0);
});

test("GUARD header counts that drift from the body cannot pass", () => {
  const { status, log } = runOn({
    mutate: (recs) => { recs[0].counts.dispatch += 1; },
  });
  assert.notEqual(status, 0);
  assert.match(log, /capture count mismatch/);
});

test("GUARD a capture with no end record cannot pass", () => {
  const { status, log } = runOn({ mutate: (recs) => { recs.pop(); } });
  assert.notEqual(status, 0);
  assert.match(log, /no end record/);
});

test("GUARD a module without the lowering is refused, not silently passed", () => {
  // The staged unit.wasm is the SAME unit built the ordinary way: its indirect
  // calls are still `call_indirect` on emcc's own table and nothing observes
  // them. Replaying a dispatch capture against it must be an error.
  const staged = path.join(repoRoot, "research/decomp/port-units-staging/auto-c0011-005/unit.wasm");
  const { status, log } = runOn({ wasm: staged });
  assert.notEqual(status, 0);
  assert.match(log, /__gf_dispatch_at/);
});
