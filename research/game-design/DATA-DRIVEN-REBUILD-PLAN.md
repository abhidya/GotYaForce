# Building it correctly: from hand-rolled behaviors to data-driven runtimes

Written 2026-07-01 after a playtest surfaced: screenshot-CSS UI, poor borg animation, generic
attacks (no per-borg moves/items), shooting that doesn't match, and flaky camera/lock/movement.
A code audit confirmed every symptom and located the exact gaps. This doc is the plan.

## Root cause

The port was built **behavior-first** (write TS that imitates what the game looks like) instead
of **data-first** (write small runtimes that execute the game's own extracted data). The result
is one generic borg wearing 108 different models. The fix is not "tune harder" — it's wiring
the already-extracted data through interpreters, and decoding the two formats still missing.

Three distinct gap types (they need different work):

1. **Wiring gaps** — data extracted + parser exists, runtime ignores it (cheapest, biggest wins).
2. **Decoder gaps** — data extracted, per-record semantics not decoded (hit-bin move records,
   MOT action timing). Needs decomp reading + trace validation.
3. **Research gaps** — no ROM evidence found yet (movement constants, lock-on mechanic,
   camera magnitudes). Needs Dolphin runtime tracing, not more static grep.

## Audit facts the plan builds on (file-verified 2026-07-01)

- `packages/combat/src/combat.ts:310-436` — ONE attack routine for all borgs: flat melee arc,
  one projectile template, one AoE special. Per-borg variation = 4 visual families
  (`projectileVisualFamilies.json`) affecting tint only. Muzzle/melee origins are flat offsets.
- `research/asset-inventory/hit-bin-inventory.json` — 210 per-borg hit-bin files scanned;
  `packages/formats/src/hit-bin.ts` parser exists; **zero runtime imports**. Per-move record
  semantics partially decoded (behavior-notes §4j/4o/4p) — this is THE decoder gap for combat.
- `research/asset-inventory/weapon-attachment-map.json` — 206/211 borgs have skeletal (JOBJ)
  attachment-point candidates for weapons/muzzles; unused.
- `research/animation-actions/borg-action-assets.json` — 4,894 clips across 219 borgs;
  runtime collapses to ~16 generic slots via per-borg `anim_index.json`.
- Camera (`apps/game/src/sim/camera.ts`) is a custom follow cam, partially trace-DERIVED
  (height +60 confirmed; trail ~470-510 low-confidence; framing TUNED). Lock-on
  (`combat.ts:92-123`) is an honest TUNED heuristic — corpus search found no scan-select
  mechanic, so the real one must be found by runtime tracing.
- Movement/jump/dash constants audited TUNED (constants.ts §s4s) — no trace harness ever fit them.
- UI: `styles.generated.ts` is 1000+ lines of hand CSS from reference captures. Real extracted
  UI exists and is partially used: 831 textures in `public/ui`, six exported 3D UI scenes
  (box00/brif00/entry00/vsel00/vsel01/tl00) mounted as **backdrops only**; all layout and
  interaction is hand-DOM. The exported scene DAEs contain the game's actual layout transforms —
  currently ignored.
- FX: 4 hand-extracted sprite PNGs hardcoded in `battleScene.ts:84-89`; `ptcl00.txg` (the real
  particle sheet) is skipped by the UI exporter's classifier; no per-move effect-ID mapping
  exists yet (blocked on hit-bin decode).

## Workstreams (dependency order)

### 1. Per-borg action system — fixes "attacks/items not plugged in, shooting doesn't match"
The core architectural change: replace the generic `stepAttacks()` branch with an **action
interpreter** over per-borg data.
- a. Decode hit-bin per-move records: find the ROM reader for hit-bin data in the corpus
     (start from behavior-notes §4j/4o/4p leads + `game-combat` bucket; the code that indexes
     records by move ID defines the schema). Validate decoded fields against Dolphin traces
     (known move → observed damage/hitstun/knockback).
- b. Define `ActionDef` (per borg, per move): startup/active/recovery frames, hit record ref,
     projectile def (speed/lifetime/homing/count), attachment node, effect IDs when known.
     Generate `apps/game/public/actions/pl*.json` from decoded hit-bins at export time.
- c. Interpreter in `packages/combat`: `stepAttacks()` executes the loaded ActionDefs;
     keep today's generic path as an explicit labeled fallback for undecoded borgs.
- d. Wire `weapon-attachment-map.json` JOBJ nodes as real muzzle/melee origins (replaces the
     flat offsets at combat.ts:426/456). Pure wiring, can start immediately.

### 2. Animation binding — fixes "borgs are not animated well"
- Replace the 16-slot resolver with per-borg action→clip binding generated from
  `borg-action-assets.json` (the inventory already maps actions to banks; today a script
  hand-condenses it into anim_index.json).
- Sync combat state timing to clip timing: active frames should come from the action data
  (workstream 1b), so animation and hitbox agree like the real game.

### 3. Trace calibration — fixes "movement lacks the feeling"
- Build the golden-trace harness (extend `scripts/dolphin-gdb-trace.mjs`): scripted pad inputs
  in Dolphin, log per-frame position/velocity/state for one borg; replay identical inputs in
  the TS sim; diff. Fit GRAVITY / JUMP / DASH / accel / turn-rate until the diff is flat;
  relabel DERIVED-by-trace with the capture cited.
- Same harness answers lock-on: engage lock in-game while tracing which code paths/fields
  change (static grep already failed here — runtime evidence is the only route).

### 4. Camera port — fixes "camera view and locking flakey"
- Extend the §3.1 RAM traces (more samples: zoom during dash, multi-actor fights, wall
  proximity) and read the 74 `camera`-topic candidates in
  `research/decomp/index/function-evidence-index.md` to port the real follow/zoom/framing rules
  into `camera.ts`, replacing the TUNED framing heuristics.

### 5. UI runtime — fixes "screenshot CSS"
- Short term (cheap, high visual payoff): derive screen layout from the exported UI scene DAEs'
  node transforms instead of eyeballed CSS — generate layout constants from the scene files the
  way `styles.generated.ts` is generated today. DOM remains the input layer.
- Real fix: a small **UI scene player** — parse the exported scenes (quads, textures, anim
  tracks) and render them on the existing canvas layer; DOM shrinks to invisible hit-areas.
  Fix the exporter classifier so `arrow_mdl.arc` and `ptcl00.txg` stop being skipped.

### 6. FX wiring — depends on 1a
- Export the real particle sheets (`ptcl00.txg`), then map per-move effect IDs from decoded
  hit-bin/action data to sprites via `particle-effect-inventory.json`. Until then FX stays the
  4 generic sheets, honestly labeled.

## Rules (same as everywhere in this repo)
- Every decoded field: behavior-notes.md entry with address/trace evidence BEFORE TS changes.
- Fallbacks stay explicitly labeled (a borg without decoded actions uses the generic path and
  says so) — never fake per-borg data.
- Each workstream ends in a comparison artifact: trace diff (1,3,4), side-by-side capture (2,5,6).

## What NOT to do
- Don't tune constants by feel anymore — every "feel" complaint above traces to exactly that.
- Don't hand-write more per-borg special cases in combat.ts; that path is capped at "generic".
- Don't rebuild UI layouts in CSS from screenshots; the real layout data is already on disk.
