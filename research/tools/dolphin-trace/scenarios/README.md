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
