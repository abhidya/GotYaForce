# Corpus-correction loop — divergence to re-verified rebuild

First executed 2026-08-26 on `auto-c0001-005` / `FUN_8000fc2c` (camera-distance solver).
This is the sanctioned, repeatable path for every future case where a staged unit is
proven behaviorally wrong against the console because Ghidra mis-lifted the ROM.

The invariant that makes this loop work: **unit.c is regenerated output, the chunk is the
source of truth.** `materialize_unit_c` (OGhidra `src/port_wasm_units.py`) re-extracts the
queue's pinned line ranges from `research/decomp/ghidra-export/chunk_NNNN.c` on every build
and records fresh per-block sha256s into the unit's `provenance.json`. Fix the chunk, revoke
the verdict, and the driver's natural loop rebuilds the unit from the corrected source — no
driver code changes, no hand-edited artifacts, no hand-edited state.

## The loop

### 1. Divergence found (trace oracle)

A `research/decomp/data/oracle-results/<unit>.json` with a `fail` verdict against a
`dolphin_trace` reference (captured per `research/tools/dolphin-trace/README.md`). Root-cause
it to a specific mis-lifted line in the chunk — the divergence artifact plus live
register/stack evidence must pin down *what the ROM actually does* before anything is edited.

Case study: 200/200 live captures diverged on `w348`; live capture at the `0x8000fd2c`
`fcmpo` showed the stack diff-vector as `(x, 0.0, z)` while the true camera y-delta was
nonzero — the ROM zeroes the Y component before `PSVECSquareMag` (horizontal distance).
Ghidra had lifted that store as a dead stack local (`local_1c = FLOAT_80436aa8;` — stack
aliasing: `local_1c` IS `fStack_20.y`), so the compiled wasm measured 3D distance.

### 2. Corpus correction with provenance

Edit the chunk per the convention in `research/decomp/ghidra-export/README.md`
("Manual corpus corrections"): **same-line replacement** (extraction ranges are line-pinned),
inline `/* CORPUS CORRECTION YYYY-MM-DD: ... */` comment citing the evidence, minimal
semantic delta.

Verify before touching live state:

- line count of the chunk unchanged; re-extract every queue range that touches the chunk and
  confirm only the corrected unit's block sha changes;
- preflight-build the corrected unit with the driver's exact emcc invocation
  (`emcc_build_unit` in `src/port_wasm_units.py` — copy the staged `gnt4_shim.h`, same flags,
  same export list) and replay the committed corpus:

  ```
  ORACLE_WASM=<preflight unit.wasm> ORACLE_RESULTS_DIR=<scratch> \
    node research/decomp/oracle-harness/run-unit.mjs --unit <unit>
  ```

  `ORACLE_RESULTS_DIR` MUST point at a scratch dir so the tracked verdict artifact is not
  clobbered by a rehearsal run. Expect the corrected split before proceeding.

Commit the chunk fix (plus docs) as a plain commit — no attribution trailers.

### 3. Revoke the stale verdict (journal path)

The unit's green is a settled verdict; hand-editing `wasm-units-state.json` is forbidden
(settle-through-journal rule, design §2.9 [V4-9]). The sanctioned mechanism:

```
cd research/tools/OGhidra
.venv\Scripts\python.exe -m src.port_wasm_units revoke-unit \
  --unit <unit> \
  --reason "<divergence proof: oracle-results file + root cause + chunk line corrected>"
```

Operational discipline (same as the orphan repair):

- run it **only between driver units** — after a terminal unit event in
  `research/decomp/generated/finish-game-port/events.jsonl` and before the next
  `wasm_unit_started`. The command takes the driver lock and refuses while a driver is alive;
  do not fight it — wait for the boundary (or pause the manual gate per AGENTS.md).
- it computes every required binding itself (deterministic `transition_id`,
  `previous_record_sha256`, `previous_commit`), backs up the state file, emits the journal
  checkpoint + `verdict_revoked` event, pushes only the `port-progress` journal, and requeues
  the unit as `pending`. The stale staged artifact stays on disk as audit evidence and is
  replaced only through the recorded revocation (revoked-preimage binding in
  `revoked_lifecycle_is_eligible`).
- rerunning the exact same command after a crash completes the same transition (idempotent);
  a second run reports `already_requeued`.

### 4. Natural rebuild

Make sure the corrected chunk is present in the checkout the driver reads
(`find_gotyaforce_root` — the live `D:\GotYaForce` working tree), landed at a driver
boundary. The requeued `pending` unit is picked up by the driver's normal rotation;
its build re-extracts the corrected chunk text, and the new `provenance.json` records the
corrected block sha — the export chain stays honest without any manual artifact writes.

### 5. Re-verify

When the unit re-lands (watch `events.jsonl` for its terminal event), replay the same
committed corpus against the rebuilt staged wasm:

```
node research/decomp/oracle-harness/run-unit.mjs --unit <unit>
```

(default wasm path is the staged artifact; use a scratch `ORACLE_RESULTS_DIR` unless this run
is meant to update the tracked verdict artifact). Compare against the preflight split and the
spec header's documented expectation.

Case-study outcome (preflight, corrected source, production emcc flags, 200-case committed
corpus): `exact=196 rounding_explained=4 unexplained=0` — the 4 are the documented 1-ulp
frsqrte-seed/Newton sqrt rounding channel (spec `rounding_bound 1.0` reports, never hides).
Overall verdict stays PARTIAL for this unit because the spec covers 1 of 8 exports — that is
the export-coverage mandate working, not a failure of the loop.

## What this loop never does

- edit `unit.c`, `unit.wasm`, `provenance.json`, or `wasm-units-state.json` by hand;
- restructure chunk code beyond the proven mis-lift;
- insert/delete lines in a chunk (line-pinned extractions);
- push product refs (revoke-unit pushes only the journal; the rebuild's own commit path
  publishes the corrected artifact);
- run while the driver is mid-unit.
