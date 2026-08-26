# dolphin-trace — per-call oracle capture from the real game

Design step 2 ("trace pilot") of docs/playable-port-design.md Stage B: the real
GG4E running in the bundled Dolphin is the byte-exact oracle for staged wasm
units. This tool breaks on a unit function's entry in the live game, records
per call **(args, referenced memory, return, memory writes)**, and emits a
JSONL fixture the EXISTING harness (`research/decomp/oracle-harness/
run-unit.mjs`) replays through a per-unit spec module. Python only (owner
rule); pure stdlib.

## Files

- `rsp_client.py` — GDB-RSP client for Dolphin 2606-97's stub, with every
  stub quirk this rig taught us encoded (see its docstring).
- `capture_oracle.py` — CLI: `launch` / `stop` / `probe` / `scout` /
  `capture`.
- `plans/<unit>.<fn>.json` — per-function capture plans, authored line-by-line
  from the unit's verbatim C (typed read/write sets with address expressions).
- Harness side (not here): `oracle-harness/specs/<unit>.spec.mjs` replays the
  fixture (`reference_kind: "dolphin_trace"`), rebasing captured pointers into
  scratch regions and byte-swapping scalars element-wise (BE console RAM ->
  LE wasm arena, same rule as `gen_arena_rom_provenance.py`).

## Hard-won operational facts (2026-08-25, bundled Dolphin 2606-97)

1. **`--debugger` is load-bearing.** Without it, `Z0` breakpoints install
   (`OK`) but NEVER fire, on every CPU core. With it they fire under **JIT64**
   (`CPUCore=1`) too — use JIT, the game runs near full speed (a frame every
   0.2-0.3 s wall while a breakpoint loop is being serviced).
2. **One stub connection per emulator boot.** The stub never re-listens after
   its single client disconnects. `launch --wait` polls netstat (never
   connects); each attaching command (`probe`/`scout`/`capture`) consumes the
   boot — relaunch Dolphin between them (~15 s with a savestate).
3. **Null video backend works and keeps the GPU free** for the LLM slot (the
   game logic runs headless; savestates load fine). GPU-contention rule from
   the design doc respected by default.
4. **Controllers must be configured** (`SIDevice0..3=6`, launch does it) or
   PADRead reports no-pad and injected input is ignored by the game.
5. **Pad injection** (from `scripts/dolphin-gdb-trace.mjs` prior art): break
   at `0x8010d4d0` (game-side pad normalization, after PADRead), overwrite
   `PADStatus[4]` at fixed `0x803c72fc`. `--inject circle+b` rotates the
   stick + holds B — this is what makes per-actor helpers actually fire in an
   otherwise idle savestate.
6. **Savestate quality decides what fires.** `2v2 gred cotrolled players no
   cpu.sav` (repo root) loads into a LIVE battle (borg array at 0x803c4e84
   populated); the `dolphin/*.sav` damage states did not load into live
   battles on this build. Cold boot runs but nothing gameplay-relevant fires
   for many minutes. **No DTM movie exists in the repo** — the design's I3
   prerequisite (owner-supplied DTM before the trace pilot) is UNMET; capture
   currently rides savestate + synthesized input instead, which is
   non-deterministic across runs (each capture is a fresh sample, not a
   replayable trace). When the owner records a DTM, launch Dolphin with the
   movie and the same capture path applies unchanged.
7. `scout` empirics (90 s, 201 callee-free staged functions, live 2v2 +
   injection): only `FUN_8000fc2c` and `zz_0010980_` fire (4/frame each —
   per-player camera/UI updates). Family-specific actor helpers need their
   borg family present and acting; growing capture coverage is a game-state
   authoring problem (G4 in the design doc), not a tooling problem.

## End-to-end recipe

```sh
# 1. boot our own Dolphin (never the port driver's anything) headless+stub
python research/tools/dolphin-trace/capture_oracle.py launch \
  --save-state "D:/GotYaForce/2v2 gred cotrolled players no cpu.sav" --wait 90

# 2. (each attaching step consumes the boot; relaunch between them)
python .../capture_oracle.py probe                     # prove stub + GG4E
python .../capture_oracle.py scout --unit auto-c0010-009 --inject circle+b \
  --seconds 60                                         # what fires?
python .../capture_oracle.py capture \
  --plan research/tools/dolphin-trace/plans/auto-c0001-007.zz_0010980_.json \
  --n 120 --inject circle+b \
  --game-state "2v2 sav + circle+b injection" \
  --out .../auto-c0001-007.dolphin-trace.jsonl         # ~25 s for 120 cases

# 3. copy fixture into the harness and replay
cp <out> research/decomp/oracle-harness/corpora/<unit>.dolphin-trace.jsonl
node research/decomp/oracle-harness/run-unit.mjs --unit <unit>

# 4. stop the instance
python .../capture_oracle.py stop
```

Authoring a new plan: read the function's verbatim C in
`research/decomp/port-units-staging/<unit>/unit.c`, list every load (typed,
with its address expression over the entry registers — `[e]` is a big-endian
u32 deref) and every store; the spec then rebases pointer-typed roots into
fixed scratch regions (`0x80600000+`, damage-core convention) and compares the
write set byte-for-byte.

## Pilot results (2026-08-25)

- **auto-c0001-007 / `zz_0010980_`** — 120 captured calls, replay
  **120/120 byte-exact** (`ORACLE TOTAL functions=1/1 cases=120 UNEXPLAINED: 0
  VERDICT: PARTIAL` — partial only because the other 7 exports have no corpus
  yet). Honesty note: the game state kept every call on the flag==0 fade path
  with alpha already 0 — mechanism proven, branch coverage thin (spec header
  documents it).
- **auto-c0001-005 / `FUN_8000fc2c`** — 200 captured calls (189 distinct
  camera vectors, both table rows), replay **0/200: REAL DIVERGENCE, root
  cause proven against the live ROM.** The ROM zeroes the Y component of the
  camera-target delta (horizontal-distance clamp); Ghidra mis-lifted that
  store as an unrelated stack local (`local_1c = FLOAT_80436aa8;`,
  chunk_0001.c:2790 — stack aliasing), so the staged wasm measures 3D
  distance and clamps on the wrong branch. Re-simulated with diff.y=0:
  196/200 byte-exact + 4/200 within 1 ulp (frsqrte-seed rounding channel).
  This FAIL is the trace oracle doing its job: a compile-green unit that is
  behaviorally wrong vs the console, caught and root-caused by per-call
  capture. Fix path: repair the aliasing in the unit's C (through the
  driver's sanctioned path), recompile, re-run the same corpus.

Verdicts and evidence artifacts: `research/decomp/data/oracle-results/
auto-c0001-007.json`, `auto-c0001-005.json`.

## Scenarios (coverage authoring)

`scenarios/<name>.json` scripts a capture game state: the savestate `launch`
loads and the default `--inject`/`--game-state` for `scout`/`capture`
(`--scenario <name>` on any of those verbs; explicit flags override). The
library, the unit-family selection heuristic, and the schema live in
`scenarios/README.md`. **Owner-recorded DTMs slot in as scenarios when
provided** (reserved `dtm` field — the design's deterministic capture input,
playable-port-design.md G4/I3); until one exists, captures ride savestate +
synthesized input and are fresh samples, not replayable traces.

## Driver integration (verification at scale)

The port driver's maintenance verbs wrap this tool end-to-end — plan
refresh (typing from `research/decomp/data/oracle-registry.json`) -> capture
(one Dolphin boot per export; Null backend, GPU-free) -> harness replay ->
verdict recorded in the unit's canonical state (`oracle` block; FAIL flags
`oracle_divergent`, never auto-revokes). A FULL-coverage PASS publishes the
unit's `oracle-commands.json` entry and promotes through the existing
reverify path; anything less changes no tier. Operator-run (the rig
supervisor's seam has no stage rotation); both verbs take the driver lock
and refuse to fight a running driver or another Dolphin:

```sh
cd research/tools/OGhidra
.venv/Scripts/python.exe -m src.port_wasm_units verify-unit \
  --unit auto-c0001-007 --repo-root D:/GotYaForce     # one unit end-to-end
.venv/Scripts/python.exe -m src.port_wasm_units verify-sweep \
  --max-units 3 --max-seconds 3600 --repo-root D:/GotYaForce
```

`verify-unit --no-capture` replays the committed corpora only;
`--no-promote` records + publishes the sidecar and leaves promotion to the
driver's own verification lane.
