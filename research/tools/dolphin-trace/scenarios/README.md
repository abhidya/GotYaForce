# Capture scenarios — scripted game states for coverage authoring

A scenario is a small JSON file that tells `capture_oracle.py` HOW to put the
real game into a state where a unit family's functions actually fire:
which savestate to load (`launch --scenario X`) and which synthesized pad
input to drive each frame (`capture`/`scout` `--scenario X` defaults for
`--inject` and `--game-state`). Explicit CLI flags always override scenario
defaults.

## Schema (scenario_schema 1)

```json
{
  "scenario_schema": 1,
  "name": "<file basename>",
  "description": "why/when this state fires which code",
  "save_state": "<path relative to the MAIN checkout root, or null for cold boot>",
  "inject": "<--inject spec: 'circle+b', 'hold:sx,sy+a', or null>",
  "game_state": "<human note recorded into every fixture header>",
  "dtm": null
}
```

## Library

| scenario | state | proven coverage |
|---|---|---|
| `battle-2v2-circle` | owner's live 2v2 savestate + circling/shooting P1 | per-frame camera/UI/actor helpers (pilot: 120/120 byte-exact on `zz_0010980_`; the `FUN_8000fc2c` mis-lift catch) |
| `title-attract` | cold boot, title/attract loop | title/menu/attract families (untested breadth; menus need input scripting to leave the title) |
| `battle-2v2-combat` | same 2v2 savestate, circling stick + B/X/A press/release edges | MEASURED 2026-08-29: ~2.7-2.9x the per-frame hit rate of `circle+b` on the live family's hot exports; unlocked NO export `circle+b` could not already reach. Density/branch-coverage aid, not a coverage unlock. |

## Held masks vs press edges (2026-08-29)

`circle` and `hold` write the SAME button mask on every injected frame, so the
game only ever observes a button that is already down — never a fresh press
(verified: 0 rising edges in 64 frames under `circle+b`, constant mask 0x200).
`combat:<buttons>` cycles the named buttons through press/release edges
(6 frames down, 10 up, round-robin) so edge-triggered code can be entered.

**What that did and did not buy, measured the same day.** A/B over the 46
exports of six units that had captured 0 cases: `combat:b,x,a` scored 0 hits,
exactly like `circle+b`. A second A/B over the five staged exports that DO fire
in this savestate: `combat` roughly tripled the per-frame hit rate
(`FUN_800c4468` 2.02 hits/frame vs 0.75) but reached nothing new.

So the held-mask defect is real, and fixing it makes captures denser and more
branch-varied — but it is NOT the reason family exports score zero. **The
binding constraint is which borg family is loaded.** In this savestate only
family `0x800c04c0` (pl0300/pl030b) is live, which is why exactly 5 of 104
staged units (38 of 818 exports) are capturable here and the other 99 are not.
Growing coverage means new savestates/DTMs for the other 39 families, exactly
as the design doc's G4 says — not more capture time or cleverer input in this
state.

## Unit-family -> scenario heuristic (v1)

Selection is implemented in `src/port_trace_verify.py::select_scenario`
(OGhidra repo) and used by the driver's `verify-unit`/`verify-sweep` verbs
when `--scenario` is not given:

- `auto-c0013-*` (the title/main-menu chunk,
  research/decomp/index/title-main-menu-flow.md) -> `title-attract`
- everything else -> `battle-2v2-circle` (the only state measured to fire
  per-frame helpers; design doc G4: growing coverage beyond it is a
  game-state authoring problem, not a tooling problem)

The heuristic is deliberately coarse: family-specific actor helpers need
their borg family present and acting, which no current scenario guarantees.
When a capture scouts 0 hits, the fix is a NEW scenario (a savestate or DTM
that reaches the code), then extending this table — not more capture time in
the wrong state.

## Owner-recorded DTMs slot in as scenarios

The design's coverage plan (playable-port-design.md G4/I3) makes DTM replays
the deterministic capture input, and they are OWNER-SUPPLIED. When the owner
records one, add a scenario with its path in the reserved `dtm` field; the
same capture path applies unchanged once DTM playback is wired into `launch`
(the field is reserved and refused today so nobody mistakes savestate
sampling for a deterministic replay — no DTM exists in the repo yet, and the
bundled Dolphin's CLI movie flag is unverified on this build).
