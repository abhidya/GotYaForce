# Attack-mechanics Dolphin trace plan

Companion to `attack-mechanics-findings.md` (Fable 5 audit, 2026-07-03). Each trace below
resolves a specific BLOCKED item or TUNED marker from the audit. Tooling: extend
`scripts/dolphin-gdb-trace.mjs` (per-frame memory logging against the user's own disc) and
`dolphin-hp-logger.py`. Actor base pointer chain: `*(u32*)0x803C4E84` → slot actors, stride
0x1e00 (behavior-notes.md §z/§aa). All offsets below are actor-relative unless noted.

Priority order matches the audit's blocker ranking.

---

## T1. Command-byte mapping (B/X contextual attack resolution)

- **Resolves:** ledger `contextual_attack_resolution` BLOCKED item — which button/context
  produces command values 1/2 (melee) vs 4/5/6 (ranged) in `actor+0x591`.
- **Scenario:** Versus, 1P human (G RED pl0615 — has both melee and gun) vs 1 idle CPU.
- **Inputs to record:** raw GC pad state per frame (Dolphin input log or TAS movie), plus
  scripted sequence: (a) B at long range, (b) B at point-blank, (c) X at long range,
  (d) X at point-blank, (e) B during ground dash, (f) B in mid-air, (g) B while flying
  (use a flyer borg for a second pass), (h) B directly above the enemy, (i) B on landing
  frame.
- **Memory to log per frame:** `+0x591` (command byte), `+0x6fe`/`+0x540` (state slot),
  `+0x660`/`+0x661` (button bytes), `+0x1d0f` (variant selector), commandStruct bytes
  `+0`..`+7` (pointer at `+0x4b0`), XZ distance to target (positions at `+0x20` vec3 per
  §aa), `+0x544` (local phase).
- **Expected metric:** a table `(button, movement state slot, distance bucket) -> command value`.
- **Pass/fail:** PASS when every scripted press maps deterministically to a command value and
  the melee/ranged distance threshold (if any) is measured to a single world-unit value
  reproduced on 3 repeats. FAIL/iterate if command values change with unlogged context.

## T2. Melee-context variant table (standing/dash/air/landing melee)

- **Resolves:** ledger `contextual_melee_variants` — which animation bank (group,slot) and
  which hit-record remap slot each movement context uses.
- **Scenario:** same as T1, borg with visibly distinct melee contexts (wiki lists Samurai /
  Knight families; G RED works for air vs ground).
- **Inputs:** the 8 wiki contexts as scripted presses (T1's e-i plus standing combo mash).
- **Memory to log:** `+0x591`, `+0x1d0f` (direction/variant), `+0x1cdc` (anim frame),
  current animation bank id if reachable (watch the HSD anim pointer switch; else video),
  `+0x550` (mash counter), object spawns (new entries in the object lists
  `DAT_803c477c`/`DAT_803c417c` — log list counts `DAT_80436250`/`DAT_8043624e`).
- **Expected metric:** per context: (command value, variant byte, anim bank, hitbox remap
  slot index) — the mapping the port's resolver needs.
- **Pass/fail:** PASS when each context reproduces the same tuple 3/3 times.

## T3. Hyper/Power Burst meter + duration

- **Resolves:** ledger `hyper_mode` BLOCKED items — meter accumulation field, activation
  gate (meter full?), duration of `+0x6fc`, movement/attack-speed effects.
- **Scenario:** 2P versus (both human-controlled, per the owned save `2v2 gred cotrolled
  players no cpu.sav`), deal/take damage until the HUD burst gauge visibly fills, press Y.
- **Memory to log per frame:** `+0x6fb` (arm window), `+0x6fc` (burst active), `+0x6fa`
  (paired flag), `+0x5d4` (transformed button word — verify bit 0x200 = Y), and a WATCH
  SWEEP: diff MEM1 actor block (0x400-0x800 range) between "meter empty" and "meter full"
  save states to locate the meter field the corpus search could not find.
- **Expected metric:** meter field address + fill deltas per damage event; frames `+0x6fc`
  stays 1 after activation; ammo refill rate with/without burst (log weapon cell
  `+0x774`/`+0x778`); movement speed with/without burst (per-frame position delta).
- **Pass/fail:** PASS when (a) the meter field is located and its fill rule expressed as
  `fill += f(damage dealt/taken)` fits all logged events, and (b) burst duration is a
  reproducible constant or a measurable meter-drain rate.

## T4. State-slot labels for hit reactions and attacks (confirm §u "Likely" labels)

- **Resolves:** the Likely labels on state slots 18-33 (behavior-notes.md §u table), needed
  before movement-context capture can trust slot->context mapping; also DOWN/DEATH/SPAWN
  durations (TUNED in constants.ts STATE block).
- **Scenario:** 1P versus idle CPU; perform one action at a time (walk, dash, jump, melee,
  shot, get hit lightly, get launched, die, respawn).
- **Memory to log:** `+0x6fe` (and `+0x540`), `+0x544`, `+0x720` (invinc), `+0x684/688/68c`
  windows, `+0x6c2`/`+0x6c6` gauges, frame counter.
- **Expected metric:** slot number per action; frames spent per slot (distribution over 5
  repeats — durations are animation-gated, so record per-borg).
- **Pass/fail:** PASS when each action maps to a stable slot number; label table in §u gets
  Confirmed/corrected annotations.

## T5. Projectile solidity / projectile-vs-projectile

- **Resolves:** ledger `projectile_solidity` + `projectile_vs_projectile` — whether shots
  destroy shots and which object types are "solid" (wiki claim; no generic-code evidence).
- **Scenario:** 2P versus, both fire head-on: (a) machine-gun vs machine-gun (nonsolid vs
  nonsolid per wiki), (b) missile vs machine-gun (solid vs nonsolid), (c) missile vs missile.
  Borg picks per wiki examples (e.g. Machine Robo / Missile Tank families).
- **Memory to log:** object list count `DAT_80436250` and per-object `+0x10` state byte,
  `+0x11` type byte, `+0x58` mode, positions, per frame; video capture as backup.
- **Expected metric:** despawn events at projectile-projectile contact vs pass-through, per
  type pair; the `+0x11` type values involved.
- **Pass/fail:** PASS when each pair reproduces the same outcome 3/3 and outcomes correlate
  with a recorded per-object field (that field becomes the "solidity" source).

## T6. Penetration / consume-on-hit

- **Resolves:** ledger `penetration` — which moves keep flying after a hit; whether
  `rehitIntervalFrames` and the flagsB 0x4000/0x2000 gate explain observed behavior.
- **Scenario:** 1P vs 2 CPUs lined up (use ally-vs-enemy positioning in versus); fire a
  known piercing move (wiki: lasers/explosions penetrate) and a normal bullet through both.
- **Memory to log:** both victims' HP (`+0x1c6`), projectile object `+0x10`/`+0x4e`
  (rehit counter)/`+0x4a`, object list counts.
- **Expected metric:** per move: does one projectile object damage 2 targets? does `+0x4e`
  reload from the record's `+0x16`? does the object despawn on first borg hit?
- **Pass/fail:** PASS when consume-vs-persist is tied to a specific record/object field
  value for at least 2 piercing + 2 non-piercing moves.

## T7. Ammo refill constants per mode

- **Resolves:** ledger `ammo_refill` remaining values — exact per-borg refill rates for
  types 0/1/2/3 and the deployed-return path; validates the extracted stat rows for
  weapon cells 1/2.
- **Scenario:** 1P alone in versus (no timer): fire weapon to empty, stand still, log refill;
  repeat for a gradual-refill borg, an all-at-once borg, and a deploy borg (funnel/bomb).
- **Memory to log:** weapon cells `+0x774/+0x776/+0x778` (and `+0x77c.../+0x784...`),
  `+0x78c-+0x79f` aux cells, `+0x768` (candidate refill-rate float — also resolves the
  +0x768 role conflict, see open-questions Q7), `+0x6fc` (must stay 0).
- **Expected metric:** frames-per-ammo-point (gradual), frames-to-full (all-at-once),
  ammo restore on deployed-object death; confirm `maxAmmo==0 -> infinite`.
- **Pass/fail:** PASS when logged refill matches a formula computable from the extracted
  stat-row values for all three borgs.

## T8. Status effects: id semantics + durations

- **Resolves:** ledger `status_effects` — which status id N corresponds to which player-
  visible effect, and what each does mechanically.
- **Scenario:** get hit by known status moves (wiki: freeze/shock/poison/shrink borgs —
  e.g. Ice/Thunder/Acid family attackers) in versus.
- **Memory to log (victim):** `+0x71a` (status id), `+0x71c` (timer), `+0x70c`/`+0x70e`
  (shrink/grow), `+0x74a/+0x74e/+0x750` (param tier), `+0x768`, model scale field
  (candidate `+0xc0`), HP `+0x1c6` (DoT check), velocity (freeze check), `+0x5e0` word.
- **Expected metric:** table `status id -> observed effect + duration frames + affected fields`.
- **Pass/fail:** PASS per status when the id/timer/effect triple reproduces 2/2.

## T9. Knockback magnitude + hitstun consumer

- **Resolves:** the long-standing TUNED knockback MAGNITUDE / reaction-length markers
  (constants.ts MELEE/SHOT/SPECIAL KNOCKBACK + HITSTUN; behavior-notes §p action item).
- **Scenario:** single clean hit (one melee, one shot, one launcher) on a stationary victim.
- **Memory to log (victim):** position/velocity per frame, `+0x282`/`+0x284` (pitch/yaw BAM),
  `+0x6fe` slot, `+0x544`, damage record index used (attacker object `+0x11`, record fields).
- **Expected metric:** initial launch speed (units/frame) per hitStrength value
  (records show hitStrength 1/4/16) and reaction length in frames per reaction slot.
- **Pass/fail:** PASS when launch speed correlates with a record field (hitStrength or
  another) across ≥3 different records; that correlation becomes the DERIVED magnitude rule.

## T10. Friendly fire + burst passthrough regression capture

- **Resolves:** ledger `friendly_fire` verification vector; gives the TS port a golden test.
- **Scenario:** 2P same-team versus; P1 shoots P2 (normal shot, then a flagsA&0x1000 move if
  one is identified); repeat with P2 in burst (`+0x6fc`=1).
- **Memory to log:** victim HP deltas, attacker/victim `+0x88` team bytes, record flagsA.
- **Expected metric:** damage = formula prediction (x0.25 same-team; x0.5 defender burst).
- **Pass/fail:** PASS when logged HP deltas equal `computeSourceDamage` output for the same
  inputs (this is the direct 1:1 check for the ported formula).

---

## Logging template

For each trace: save-state at scenario start; log at 60 Hz; store JSONL under
`user-data/dolphin-trace/attack-mechanics/T<n>-<slug>.jsonl` with a `meta` line recording
borg ids, scenario, input script, and the Dolphin build. Then add a matching replay case to
`packages/combat/src/selfcheck.ts` (or `scripts/selfcheck-1p-challenge.mjs`) that feeds the
same inputs to the TS sim and diffs the logged metric.

---

## Run commands

Harness: `scripts/trace-attack-mechanics.mjs` (ATK-016). Sanity-check a preset's resolved
watch list with `--dry-run` before starting Dolphin; `--summarize` reads back a captured (or
fixture) JSONL and prints per-field change points (frame, old, new). `--preset T1 --dry-run
--summarize` exercises `--summarize` against the canned fixture at
`scripts/fixtures/attack-mechanics-t1-sample.jsonl` with no Dolphin required — this is the
harness's self-test.

Each real capture needs Dolphin running with the GDB stub (`scripts/launch-dolphin-gdb.mjs`)
and a battle already loaded per the trace's Scenario line; the script resolves the active
borg base itself (slot-table chain, falling back to the single-player fast path) and records
one JSONL row per `PADRead` tick (60 Hz).

```bash
# T1. Command-byte mapping — Versus 1P (G RED pl0615) vs 1 idle CPU; run the scripted
# press sequence (a)-(i) from the trace plan, once per invocation or split into repeats.
node scripts/trace-attack-mechanics.mjs --preset T1 --frames 1800 --borg pl0615 \
  --scenario "B/X contextual resolution script (a)-(i)" --note "repeat 1/3"

# T2. Melee-context variant table — same scenario, mash + the 8 wiki movement contexts.
node scripts/trace-attack-mechanics.mjs --preset T2 --frames 1800 --borg pl0615 \
  --scenario "melee context script: standing/dash/air/landing + mash"

# T3. Hyper/Power Burst meter + duration — 2P versus, both human (2v2 gred controlled
# players no cpu.sav); deal/take damage until the burst gauge fills, press Y.
node scripts/trace-attack-mechanics.mjs --preset T3 --frames 3600 --borg pl0615 \
  --scenario "fill burst gauge via damage, activate with Y"

# T4. State-slot labels — 1P vs idle CPU; one action at a time (walk, dash, jump, melee,
# shot, light hit, launch, death, respawn), 5 repeats per action.
node scripts/trace-attack-mechanics.mjs --preset T4 --frames 3600 --borg pl0615 \
  --scenario "one action at a time x5 repeats"

# T5. Projectile solidity — 2P versus, head-on fire pairs (machine-gun/machine-gun,
# missile/machine-gun, missile/missile).
node scripts/trace-attack-mechanics.mjs --preset T5 --frames 1200 \
  --scenario "head-on projectile pairs: mg/mg, missile/mg, missile/missile"

# T6. Penetration / consume-on-hit — 1P vs 2 lined-up CPUs; one piercing move + one normal
# bullet through both.
node scripts/trace-attack-mechanics.mjs --preset T6 --frames 1200 \
  --scenario "piercing vs normal projectile through 2 lined-up victims"

# T7. Ammo refill constants — 1P alone in versus (no timer); fire to empty, stand still,
# log refill. Repeat per borg (gradual / all-at-once / deploy).
node scripts/trace-attack-mechanics.mjs --preset T7 --frames 3600 --borg pl0615 \
  --scenario "fire to empty, stand still, log refill (gradual-refill borg)"

# T8. Status effects — get hit by known status moves (freeze/shock/poison/shrink family
# attackers) in versus; log the victim.
node scripts/trace-attack-mechanics.mjs --preset T8 --frames 1800 \
  --scenario "status-move hits: freeze/shock/poison/shrink"

# T9. Knockback magnitude + hitstun — single clean hit (melee, shot, launcher) on a
# stationary victim; log the victim.
node scripts/trace-attack-mechanics.mjs --preset T9 --frames 600 \
  --scenario "single clean hit: melee, shot, launcher (3 captures)"

# T10. Friendly fire + burst passthrough — 2P same-team versus; P1 shoots P2, then repeat
# with P2 in burst.
node scripts/trace-attack-mechanics.mjs --preset T10 --frames 1200 \
  --scenario "same-team shot, then same-team shot with defender in burst"
```

Post-capture, read a session back with:

```bash
node scripts/trace-attack-mechanics.mjs --summarize user-data/dolphin-trace/attack-mechanics/T1-command-byte-mapping.jsonl
```

## Standard starting save (added 2026-07-03)

`gotcha_force_100_usa.gci` at the repo root (user-owned, gitignored) is a validated
100%-completion GG4E save — every borg the T1-T10 scenarios need is unlocked (fusion
pairs, status borgs, solid/piercing projectile borgs, all refill-mode archetypes).
Import it into Dolphin's memory card A before any trace session; per-scenario borg
picks in the sections above no longer need availability workarounds. See
behavior-notes (aq); format decode in progress (scripts/inspect-gotcha-save.mjs).
