# Hand-off prompt: 1:1 Challenge-mode slice — engine, physics, assets, animations

Paste this whole thing as the opening message of a new session (Claude Code / any agent with
file + shell access to this repo). It supersedes nothing — read `research/decomp/HANDOFF-PROMPT.md`
for combat-formula specifics; this prompt is the umbrella plan for making the Challenge slice
match the real game 1:1.

---

## Context (2 minutes)

This repo (`D:\GotYaForce`) is a from-scratch TypeScript/web port of **Gotcha Force** (GameCube,
GG4E NTSC-U). Playable app: `apps/game` (Vite + three.js). Deterministic sim: `packages/combat`
(pure TS, no DOM). Challenge mode flow: `packages/missions` (`challenge.ts`,
`challenge-reference.ts` — the real ROM battle tables are already ported and cited by address).

Reverse-engineering ground truth, all local:

- `research/decomp/ghidra-export/` — full decompile of `boot.dol`, 11,972 functions.
  `_index.tsv` maps address→name→chunk. **Also reorganized**: run `node scripts/reorg-decomp.mjs`
  to (re)generate `research/decomp/organized/` — one file per function, bucketed by subsystem
  (`sdk-hsd`, `game-combat`, `game-modes`, …) with `_map.tsv` for lookup. Grep this corpus;
  never re-derive by hand in Ghidra unless the decompile failed.
- `research/decomp/index/` — evidence inventories (challenge-flow, cpu-ai, archive-load xrefs,
  function-evidence-index). `research/decomp/data/` — raw ROM tables as JSON (type matrix,
  spawn pools, knockback modes).
- `research/decomp/behavior-notes.md` — the running lab notebook. Append lettered sections with
  address+evidence BEFORE changing TS code.
- `scripts/dolphin-gdb-trace.mjs`, `dolphin-hp-logger.py`, `inventory-challenge-memory-evidence.py`
  — live Dolphin RAM tracing against the user's own disc.
- Raw ROM data is read from `user-data/GG4E/disc/sys/boot.dol` via `research/decomp/dol.py`.

## Ground rules (non-negotiable)

1. **DERIVED vs TUNED** (see `packages/combat/src/constants.ts` header). DERIVED = confirmed
   from ROM decomp, raw data, or live trace, with the address cited. TUNED = labeled guess.
   Never silently upgrade a TUNED value — wrong-but-confident is worse than honest-unknown.
2. **Assets are extracted from the user's own disc, never recreated and never committed.**
   The disc and extracted bytes stay local (`user-data/`, gitignored). 1:1 fidelity comes from
   using the real bytes, not from imitating them.
3. **1:1 is proven by comparison, not by feel.** Every workstream below ends in a check against
   Dolphin (trace diff or screenshot), not "looks right."
4. Matching/byte-identical decompilation is out of scope because it's useless for a TS port —
   don't pursue it; the grep corpus is the source of truth.

## Definition of 1:1 for the Challenge slice

Same battle tables, same damage/knockback/physics numbers, same borg models + skeletal
animations at the same timings, same stage geometry/lighting/camera behavior, same HUD layout
from the real UI atlases, same SFX/BGM from the disc, same CPU behavior where evidenced —
verified frame-against-frame where a harness exists.

## Workstreams, in priority order

### 1. Model pipeline (`packages/formats/src/mdl-arc.ts` is a deliberate stub) — SOLVED at
parse level, remaining work is coverage
The format research is DONE (2026-06-30): `.arc` files are HSD DAT archives (borg
`pl****_mdl.arc` = 0x100-byte wrapper + DAT); spec in `research/format-specs/arc-hsd-format.md`.
Conversion is OFFLINE via Ploaj/HSDLib `HSDRaw` + the exporter at `user-data/GG4E/gltf-export/`
(C#, build-time only) → Collada DAE with skeleton/skinning/materials/decoded textures, loaded
by three.js. Do NOT write a TypeScript `.arc` parser. (The old "HSD refuted 0-3" note was about
HSD being statically linked in boot.dol / Melee runtime tooling — a different claim; the
corpus's `HSD_ArchiveParse` call chain in `research/decomp/index/archive-load-xrefs.md` is
consistent with all of this.)
What actually remains: wire animation-track export (mot.bin / HSD anim tracks — see
`scripts/export-borg-animation-hsd.mjs`), batch-convert coverage of all 1369 `.arc` files, and
one POBJ "out of struct range" edge case (probe: `user-data/GG4E/hsd-test-csharp/`). Fidelity
check stays the same: render exported borgs side-by-side with Dolphin screenshots.

### 2. Physics + combat numbers (`packages/combat`, `packages/physics`)
- Port the real base-damage formula `zz_003cd5c_` @ `0x8003cd5c` (multi-stage multiplicative:
  base power, HP-ratio scaling, rank table, defender category tables). This is Priority 1 in
  `HANDOFF-PROMPT.md` — read that doc's section before starting; the `object+1000` category
  mapping is the open sub-problem.
- Knockback **direction** is ported (`packages/physics/src/knockback.ts`, DERIVED); knockback
  **magnitude**, hitstun, and movement/gravity/friction constants are still TUNED. Derive them
  from the corpus + Dolphin traces: log position/velocity per frame during a known hit and
  fit against the sim.
- Prefer reading tables straight out of `boot.dol` with `dol.py` (pattern:
  `research/decomp/data/*.json` generators) over transcribing numbers from pseudo-C.

### 3. Animations (`packages/formats/src/hsd-anim.ts` + `scripts/export-all-borg-animations.mjs`)
Pipeline exists. 1:1 gap: verify exported clip frame counts, keyframe timing, and
action→animation mapping against Dolphin (see `research/animation-actions/` and
`scripts/validate-borg-animation-actions.mjs`). Any animation that plays at the wrong speed or
maps to the wrong action is a fidelity bug — file it in behavior-notes with evidence.

### 4. Challenge flow completeness (`packages/missions`)
Tables (battle counts, budgets, group rosters, stage bytes) are DERIVED and ported. Open items:
- Stage selection: static stage-code scan found 0 hits — needs **runtime archive-open tracing**
  (Dolphin) to map stage bytes → actual loaded arena archives.
- CPU AI: `research/decomp/index/cpu-ai-evidence.md` has the leads; the TS AI is a placeholder.
  Port evidenced behavior only; label the rest TUNED.

### 5. Presentation: UI/HUD, camera, lighting, FX, audio
All extraction-driven; pipelines exist — the work is coverage + verification, not invention:
- UI/HUD: `scripts/export-ui-assets.mjs`, `export-ui-scenes.mjs`; HUD glyph atlas already fixed
  (real ascii.tpl). Compare HUD layout to Dolphin screenshots at same resolution.
- Camera: `apps/game/src/sim/camera.ts` is OrbitControls-based — NOT 1:1. Find the battle camera
  logic in the corpus (`game-systems`/`game-ui` buckets; search for camera target/lerp patterns
  near battle loop callers) and port its follow/zoom rules.
- Lighting/render state: `scripts/export-stage-render-state.mjs` + `research/asset-inventory/
  stage-lighting-render-state.md` — wire exported light/fog params into the three.js stages.
- FX: `research/asset-inventory/particle-effect-inventory.json` + weapons-effects-projectiles
  inventories → map each Challenge-relevant move to its real effect assets.
- Audio: `scripts/export-audio-assets.mjs` → wire real SFX/BGM cues to events via `@gf/audio`.

### 6. Verification harness (makes "1:1" measurable — build early, not last)
- Golden traces: extend `scripts/dolphin-gdb-trace.mjs` to record per-frame (inputs, positions,
  velocities, HP) for a scripted Challenge battle; replay identical inputs through the TS sim;
  diff. Every divergence is a ranked TODO pointing at a TUNED constant.
- Keep `scripts/selfcheck-1p-challenge.mjs` green; add trace-diff cases to it as they're derived.
- Visual: side-by-side screenshot checklist (borg render, HUD, stage lighting) per milestone.

## Working style

- Navigate: grep `research/decomp/organized/_map.tsv` (or `_index.tsv`) → open the one small
  per-function file. Don't read whole chunks or whole buckets.
- Every new finding: behavior-notes.md section (address + evidence) → then TS change → then
  a trace/selfcheck that would catch a regression.
- Ask before wiring an unconfirmed mapping into gameplay code; don't ask before grepping,
  tracing, or reading local research material.

## First message to send after reading this

State which workstream you're starting (default: #1 animation-track export + batch coverage —
it gates rendering fidelity the most) and proceed.
