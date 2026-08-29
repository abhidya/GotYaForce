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
- `force_navigator.py` — CLI: `inspect` / `survey` / `inventory` / `stage` /
  `cover` / `families`. Makes an ARBITRARY borg family live in the running
  game by rewriting the ROM's own battle roster and re-running its own battle
  load, which is what lifts capture past the one family the single savestate
  provides. `cover` generates a measured scenario per blocked family; the
  mechanism, its evidence, and its two traps are documented in
  `scenarios/README.md` ("Roster-reload scenarios").
- `plans/<unit>.<fn>.json` — per-function capture plans, authored line-by-line
  from the unit's verbatim C (typed read/write sets with address expressions).
- `merge_fixtures.py` — combine the per-export fixtures of one unit into the
  single corpus `run-unit.mjs` loads (`spec.meta.fixture`). Needed by any spec
  covering MORE THAN ONE export, because capture emits one fixture per export
  (one emulator boot each) while the harness loads one file per unit. It
  renumbers `n` across the whole file (the harness keys per-case results by `n`)
  and keeps the original per-export index as `fn_n`.
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
6b. **Dolphin on this rig cannot WRITE a savestate** (measured 2026-08-29, and
   the reason coverage ships as scenarios rather than `.sav` files). Dolphin
   exposes state SAVING only through its hotkey/menu UI — `--save_state` is
   load-only — and the hotkey path needs synthetic keyboard input to reach the
   emulator. It does not: `keybd_event`/`SendInput` produce no key state at all
   from this session (`GetAsyncKeyState` reads 0 during an injected key-down,
   `GetForegroundWindow()` returns 0), i.e. there is no interactive input
   desktop to inject into. `Hotkeys.ini` + `Dolphin.Core.HotkeysRequireFocus`
   were both configured and neither produced a `StateSaves/` file, with or
   without `--batch`. So a derived game state cannot be frozen into a new
   savestate here; it is instead re-derived from the base savestate by a
   scenario `setup` block on every boot (a few seconds), which is also
   versionable text rather than a 20 MB blob.
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

### Capturing a unit whose borg family the savestate does not load

Most staged units are family-gated and the one battle savestate loads one
family, so the recipe above scouts 0 hits for them. Use that family's
roster-reload scenario instead — the `setup` block runs on attach and the rest
is identical:

```sh
# which families block how many staged units, biggest first
python .../force_navigator.py inventory

# generate one measured scenario per blocked family (own Dolphin boot each)
python .../force_navigator.py cover \
  --manifest research/tools/dolphin-trace/scenarios/coverage-manifest.json

# then scout/capture through the generated scenario
python .../capture_oracle.py launch --scenario battle-roster-0x801a10e8 --wait 120
python .../capture_oracle.py scout --unit auto-c0050-000 \
  --scenario battle-roster-0x801a10e8 --seconds 60
```

`--scenario` supplies the savestate, the pad injection, the recorded
`game_state`, AND the roster setup; the setup report is written into the
fixture header (`source.scenario_setup`) so a fixture says which borg family
was live when it was captured.

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

- **auto-c0020-007 (2026-08-29)** — the first MULTI-EXPORT trace spec, and the
  first unit taken from a bare skeleton to a real typed capture end to end.
  All 8 exports got hand-authored plans (typed read/write sets derived
  line-by-line from the verbatim C); 5 of them fire in `battle-2v2-combat` and
  captured **815 cases** (200 / 200 / 200 / 200 / 15). Replay:
  `ORACLE TOTAL functions=5/5 cases=815 UNEXPLAINED: 0 VERDICT: PARTIAL`,
  789/815 byte-exact, 26 within <= 3 ulp on the PSVECNormalize channel, zero
  stray writes, zero sentinel reads. **No divergence: this unit is behaviourally
  consistent with the console over everything the capture can observe.**
  PARTIAL is structural, not a defect — the other 3 exports fire 0 times in the
  repo's one savestate, and two of them are unreplayable anyway
  (`zz_00c4704_`'s stores all target an allocator return value, which capture
  cannot address off entry registers; `FUN_800c4838` ends in a dispatch through
  the ROM function table at `0x80305240`, which staged wasm has no mapping for).
  Live-capture side-findings that the hand derivation predicted and the console
  confirmed: the per-type parameter table is a 0x44-stride array based at
  `0x80303148` (from the `iVar3 + -0x7fcfceb8` expression), and
  `FLOAT_8043ca90/94` — PSVECNormalize's Newton constants — really are 0.5 / 3.0.
  Honesty note recorded in the spec header: on the 141 re-aim cases the ROM's
  `zz_006c440_` (chunk_0009.c:2031) *itself* renormalizes and advances the
  actor, so `a+0x38 / a+0x20 / a+0x180` are the callee's on that path and the
  spec compares only the subset the unit owns; the full write set (float channel
  included) is compared on the 59 non-re-aim cases.

- **Coverage unblock (2026-08-29)** — the first captures from borg families the
  repo's one savestate never loads, via roster-reload scenarios
  (`force_navigator.py`, scenarios/README.md). `force_navigator.py cover`
  attempted all 40 families the 104 staged greens are gated on and brought up
  **39**; each is asserted only on its own constructor breakpoint firing plus
  the ROM reporting live gameplay afterwards. Through the family gate that
  moves selection from **6 of 104 units (46 of 818 exports) to 104 of 104
  (818 of 818)**. Two units carried it end to end:

  | unit | family (was `family_not_live`) | export | cases |
  |---|---|---|---|
  | `auto-c0035-000` | `0x801301f8` / pl0103 | `FUN_80130c5c` | **200 / 200** |
  | `auto-c0050-000` | `0x801a10e8` / pl0906 | `zz_01a1bbc_` | **42** |

  Both had scouted 0 hits in every prior scenario. `auto-c0035-000` also scouts
  7 of its 8 exports firing (186 hits in 60 s) where it previously scored zero.
  `zz_01a1bbc_`'s 42 is a real ceiling, not a stopped battle: it stops firing
  while the battle is still live and raising the roster depth did not change
  the number, so it is called a fixed number of times per deployment rather
  than per frame. Both fixtures are plan SKELETONS (args/ret only — the
  generator's, not hand-authored read/write sets), so they prove reachability
  and per-call sampling, not yet memory behaviour.
  Fixtures: `research/decomp/oracle-harness/corpora/auto-c0035-000.FUN_80130c5c.dolphin-trace.jsonl`,
  `…/auto-c0050-000.zz_01a1bbc_.dolphin-trace.jsonl`; each header's
  `source.scenario_setup` records which borg family was live for it.

Verdicts and evidence artifacts: `research/decomp/data/oracle-results/
auto-c0001-007.json`, `auto-c0001-005.json`, `auto-c0020-007.json`.

### Multi-export specs (2026-08-29)

`run-unit.mjs` loads ONE fixture per unit and dispatches by each case's `fn`, so
a spec covering several exports needs `merge_fixtures.py` run after the capture
sweep. Two consequences worth knowing:

- the merged header deliberately carries no top-level `fn`, so the driver's
  in-place spec-corpus refresh (`port_wasm_units._trace_capture`, which only
  overwrites a corpus whose header `fn` matches the export it just captured)
  cannot silently replace a merged corpus with one export's fixture. It also
  records each source fixture's sha256, so `merge_fixtures.py --unit <u> --check`
  detects the remaining footgun: a `verify-unit` WITH capture rewrites the
  per-export fixtures without re-merging, and the spec would otherwise replay a
  stale corpus while the fresh capture sat unread. Run `--check` after any
  capture sweep for a unit whose spec covers more than one export. Teaching the
  driver to re-merge (or to run `--check`) is the obvious next tooling step and
  is NOT done yet;
- a spec that stands in for ROM callees must say which post-state bytes those
  callees own. `zz_00c4540_` is the worked example: it derives the ROM's branch
  from console evidence, requires the wasm to take the same branch and to call
  the callee with the derived arguments, and only then narrows the byte
  comparison. That keeps a callee-owned byte from being reported as a unit
  defect without quietly dropping the case.

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
