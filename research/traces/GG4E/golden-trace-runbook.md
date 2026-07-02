# Golden-trace runbook — calibrating movement constants from live Dolphin captures

The harness for research/game-design/DATA-DRIVEN-REBUILD-PLAN.md workstream 3. One capture
session produces a "golden" (per-frame inputs + borg kinematics); the analyzer fits the real
movement constants from it. Pipeline verified end-to-end by synthetic self-test:
`node scripts/trace-golden-selftest.mjs` (run it after any harness change — must PASS).

## Pieces

| Script | Role |
|---|---|
| `scripts/lib/gdb-remote.mjs` | Shared Dolphin GDB-stub client (protocol proven in dolphin-gdb-trace.mjs) |
| `scripts/trace-golden-record.mjs` | Records per-frame `(pad input, pos, vel, heading, state, invuln)` to JSONL |
| `scripts/trace-golden-analyze.mjs` | Fits gravity / jump velocity / ground speed / accel / dash from a golden |
| `scripts/trace-golden-selftest.mjs` | Synthetic end-to-end proof of the analyzer's math |

Anchors used (already proven in `breakpoints-watchpoints.json` / `behavior-notes.md`):
PADRead `0x8021379c` as the per-frame tick (r3 = PADStatus[4]); borg base resolved live from
the wakeup-timer anchors (`0x8005d4b0` r3 / `0x80055c00` r31); struct offsets `+0x44` pos,
`+0x58` vel, `+0x72` heading, `+0x544` state, `+0x720` invuln.

Timing note baked into the format: at PADRead entry the buffer still holds the *previous*
frame's pads, so each record pairs `input_N` with the state *after* frame N — exactly the
(input → resulting motion) pair the fitter needs.

## Capture session

1. **Launch Dolphin with the GDB stub** (same setup as prior traces — see
   `research/traces/GG4E-dol-trace-playbook.md`; stub on port 5555). Boot the disc, start a
   **Challenge battle** with the borg to calibrate (start with a mid-weight walker, e.g. G Red
   `pl0615`, before flyers — boost thrust contaminates airborne fits).
2. **Record:**
   ```
   node scripts/trace-golden-record.mjs --borg pl0615 --label movement-recipe --frames 1800
   ```
   The script first waits for a wakeup anchor to resolve the borg base (it fires on spawn —
   if you're mid-battle, take a knockdown). Then it records; perform the recipe below.
   If the stub rejects per-frame breakpoints or is too slow, re-run with fewer frames.
3. **Input recipe** (~35s). CONTROL MODEL IS LOCK-ON-RELATIVE (behavior-notes §y): while
   auto-locked, forward = approach+turn-toward-enemy, **back = the only pure translation**,
   left/right = **dodge dash** (not a walk), tap A = jump / hold A = fly. Recipe is built
   around that so each constant is isolated cleanly:
   - stand still 3s (baseline)
   - hold stick full-BACK 5s, release, wait 2s (→ clean ground walk speed + accel, no turn
     coupling). Repeat the back-walk once (second sample).
   - 3 clean jumps: tap A, no stick, let land (→ jump velocity + gravity)
   - 1 fly: tap+HOLD A ~3s, release, fall (→ boost thrust vs gravity)
   - 3 LEFT dodge-dashes then 3 RIGHT, ~1s apart, from standstill (→ dash speed/duration)
   - stand still 3s
   Keep a locked enemy present but do NOT trade hits (damage frames contaminate). The recorder
   also logs the locked enemy position so motion can be read in the lock frame.
4. **Fit:**
   ```
   node scripts/trace-golden-analyze.mjs user-data/dolphin-trace/golden/<file>.jsonl
   ```
   Report lands in `research/traces/GG4E/golden-fit-<file>.md`: each fit with sample count
   (n<10 flagged WEAK), dash clusters, and the `+0x58`-is-velocity validation check.

## Upgrading a constant (the rules still apply)

1. Reproduce the fit on a **second** capture (different battle, same borg).
2. Append a lettered section to `research/decomp/behavior-notes.md` citing both golden files
   and the fitted values.
3. Only then change `packages/combat/src/constants.ts`, relabeling
   `TUNED → DERIVED (trace: <golden files>)`. Never skip to step 3.
4. `node scripts/report-tuned-constants.mjs` — watch the burn-down number drop.

## Known limits (honest scope)

- Per-frame GDB stops cost real time; 1800 frames may take several minutes wall-clock and the
  game runs slow during capture. That's fine — the game's own frame logic is untouched.
- Fits assume a grounded walker recipe. Flyers (boost thrust), knockback frames, and slopes
  need dedicated recipes and analyzer segments — extend `analyzeGolden` then.
- The sim-replay differ (feed recorded inputs through `packages/combat`, diff trajectories)
  is the natural next layer; it needs the workspace built (`pnpm install` + `tsc -b`), which
  this harness deliberately does not require.
