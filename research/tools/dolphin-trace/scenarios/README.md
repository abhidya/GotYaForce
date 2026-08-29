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
  "dtm": null,

  "live_families": ["0x800c04c0"],
  "live_families_basis": "how that set was measured, or why it is null"
}
```

`live_families` / `live_families_basis` are OPTIONAL and ADDITIVE. They are
deliberately NOT a `scenario_schema` bump: `capture_oracle.py::load_scenario`
hard-refuses any scenario whose `scenario_schema` is not exactly `1`, and it
ignores keys it does not know, so schema-1 files carry these fields safely.
Only the OGhidra driver's family gate reads them
(`src/port_family_gate.py::scenario_live_families`).

`live_families` lists the borg families whose actors are LOADED AND ACTING in
this game state, named by their constructor address (the
`constructorAddress` in `research/decomp/data/family-state-machine-coverage.json`).
It has three distinct states, and the difference matters:

| value | meaning | effect on `verify-sweep` |
|---|---|---|
| absent, or `null` | **UNKNOWN** — nobody has measured this state's roster | gate OFF for this scenario; selection is exactly what it was before the gate existed |
| `[]` | **MEASURED-EMPTY** — measured, and no borg family is live | every family-gated unit routed here is skipped |
| `["0x...", ...]` | those families are live | units gated by any other family are skipped |

Never write `[]` to mean "we did not check". UNKNOWN must fail OPEN: a wrong
`[]` would silently skip real work, while a wrong UNKNOWN only costs capture
time. `title-attract` is `null` for exactly this reason — the attract loop
plays a demo battle and nobody has measured which families it constructs.

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

## Family-liveness gate on `verify-sweep` (2026-08-29)

Picking the scenario is only half the problem: the sweep also has to stop
SELECTING units the chosen scenario cannot reach. It used to pick by
staleness alone and spend ~15 minutes per unit rediscovering "the function
never fires" — one run burned six consecutive unreachable units and never
touched any of the five reachable ones. `verify-sweep` now gates candidates
on family liveness (`src/port_family_gate.py` in the OGhidra repo).

**How a unit's gating family is derived** — deterministically, from committed
evidence, never from unit-id numbering:

1. `research/decomp/data/family-state-machine-coverage.json` gives one
   `constructorAddress` per borg family (119 of them) plus that family's ROM
   members (`pl0300`, `pl030b`, …).
2. Sorted, those constructors partition the DOL's borg text into contiguous
   per-family blocks: family F owns `[F.constructorAddress, next_constructor)`.
   Validated against the same artifact's own `romEvidence`: all 9024
   `boot.dol:0x…` code addresses cited as evidence for a family fall inside
   that family's block; none fall outside.
3. A unit's exports resolve to addresses through
   `research/decomp/data/oracle-registry.json`, falling back to the address
   Ghidra encoded in its own naming (`FUN_800c05bc` → `0x800c05bc`,
   `zz_00c0d0c_` → `0x800c0d0c`) only when the registry has no entry.
4. The unit's gating family set is the set of blocks its exports land in.

Call-graph reachability from the constructor roots was tried FIRST and does
not work here: family action handlers are entered through per-actor function
POINTER TABLES, so `research/decomp/index/function-evidence-index.json`
records 0 callers for most of them and forward reachability from a
constructor covers exactly one node. Address-block ownership is the only
relation the committed evidence supports. Known bound: the LAST family block
has no next constructor to close it, so addresses at or after the highest
constructor read as UNDETERMINED (gate off) rather than being attributed by
guess. No staged export is in that region today.

**Measured over the 104 staged compile-only greens (2026-08-29):** 103 units
derive a gating family, 1 (`auto-c0002-001`, 8 exports of engine code below
the first constructor) is not family-gated. Against
`battle-2v2-circle`'s live set, 98 units are skipped as `family_not_live` and
6 stay selectable — the 5 known-reachable pl0300 units plus the ungated one.

**Behaviour.** A blocked unit is skipped with the structured reason
`family_not_live: gating borg family 0x…/pl…. is not live in scenario …`,
recorded in the sweep report's `skipped` map and in a structured
`family_gate.blocked` block — never a silent drop. The sweep prints the
blocked inventory as normal output, e.g.

```
family gate: 98 units skipped across 39 absent families -- 0x801301f8/pl0103 x10, 0x801a10e8/pl0906 x10, 0x80079410/pl0900 x9, …
```

**Fail-open everywhere.** A missing coverage artifact, a scenario with no
declared `live_families`, or a unit that mixes family and non-family exports
all leave the unit selectable. `verify-sweep --no-family-gate` restores
un-gated selection outright — use it when a new savestate or DTM makes
families live that the scenario JSON does not declare yet, then update
`live_families` and drop the flag.

## Owner-recorded DTMs slot in as scenarios

The design's coverage plan (playable-port-design.md G4/I3) makes DTM replays
the deterministic capture input, and they are OWNER-SUPPLIED. When the owner
records one, add a scenario with its path in the reserved `dtm` field; the
same capture path applies unchanged once DTM playback is wired into `launch`
(the field is reserved and refused today so nobody mistakes savestate
sampling for a deterministic replay — no DTM exists in the repo yet, and the
bundled Dolphin's CLI movie flag is unverified on this build).
