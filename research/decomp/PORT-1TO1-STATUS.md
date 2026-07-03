# Gotcha Force (GG4E) — 1:1 Port Status & Source Map

Authoritative per-subsystem tracker: current port state, ROM/decomp source mapping, and the
ranked next action to reach 1:1. Maintained alongside `behavior-notes.md` (the lab notebook,
sections (a)–(ax)) and `attack-mechanics-findings.md`. Last synthesized 2026-07-03 from two
full subsystem surveys + the session's mechanics mapping.

**Confidence vocabulary** (same as the ledger): `DERIVED_ROM` / `DERIVED_TRACE` /
`CONFIRMED_ASSET` / `OBSERVED_WIKI` / `TUNED` / `BLOCKED` / `CHECKED_CLOSED`.

**How to read the status column:** DONE = ported and faithful to evidence; PARTIAL = works but
diverges from ROM in a known way; MISSING = not ported; STUB = intentional placeholder.

---

## 0. Executive scorecard

| Subsystem | 1:1 coverage | Gating blocker to finish |
|---|---|---|
| Combat: damage formula | ~90% DERIVED | actor level-float init (+0xc4/+0xb4); guard /40 gate |
| Combat: gauges/stagger | ~95% DERIVED | reaction lengths (animation-gated) |
| Combat: knockback direction | DERIVED, ported (mode 1) | modes 0/2/3/4 need sub-object data |
| Combat: knockback **magnitude** | TUNED | **not in code — needs trace T9** |
| Combat: B/X contextual resolver | schema only | **trace T1** (command→button map) |
| Combat: ammo/refill | mechanism DERIVED, values extracted | X-attack→cell-1 wiring |
| Combat: statuses / hyper / fusion | shells only | traces T3/T8 + heal-write dig |
| Physics: movement/jump/dash | TUNED constants | trace-fit from goldens |
| UI: screens | ~9 real screens | 6 modes are dead menu entries |
| UI: HUD | ~60% | X-ammo, charge, burst, jump gauges, cursor color |
| Challenge flow | ~80% DERIVED | winner-mask judge; 3-phase deploy |
| Assets: models (static/anim) | 100% / 89% | 23 unanimated borgs |
| Assets: animation playback | ~85% | state→(group,slot) dispatch trace |
| Audio: BGM/menu | ~90% | — |
| Audio: combat/voice | ~20% | **no ROM table — needs SE-dispatch trace**; 46 voice cues unwired |
| Stages: geometry/lighting | ~90% / ~98% | collision on 22/40 stages |
| FX: particles/projectiles | ~70% | PTL/REF decode; 3D weapon meshes |

**The three highest-value unblocks are all Dolphin traces** (T1 command mapping, T3 burst
meter, T9 knockback magnitude) + the SE-dispatch audio trace. Corpus mapping is largely
exhausted for these; they need a human at the controller or TAS-movie injection (see
`attack-mechanics-trace-plan.md` "Proven launch procedure").

---

## 1. Combat mechanics → source

Port: `packages/combat/src/*`. Full per-mechanic detail: `attack-mechanics-findings.md` (A–X),
`attack-mechanics-ledger.json`. ROM anchors in `behavior-notes.md`.

| Mechanic | Status | Port | ROM source | Next action |
|---|---|---|---|---|
| HP subtract/clamp | DONE | combat.ts applyHit | zz_003d344_ @0x8003d344 (h) | — |
| Damage formula (18-stage) | DONE (modeled subset) | damageFormula.ts | zz_003cd5c_ @0x8003cd5c (ah) | level floats +0xc4/+0xb4 init (ak); guard /40 (av auto-shield) |
| Type matrix 20×20 | DONE | typeDamage.ts | 802c5d60 + remap 802f2e28 (l/w) | — |
| Combo falloff (resistance) | DONE | damageFormula comboRankScale | DAT_802c7ca0 step 16 (ah) | none — do NOT add a 2nd layer (U) |
| Friendly fire ×0.25 | DONE | damageFormula sameTeam | step 18 (ah/o) | tests only (ATK-014 ✓) |
| Gauge stagger (down/balance) | DONE | gauges.ts + applyHit | (ag)/(ah)/(s) | — |
| Knockback **direction** | DONE (mode 1) | physics/knockback.ts | zz_00300bc_ (p) | modes 0/2/3/4 need muzzle/camera vectors |
| Knockback **magnitude** | TUNED, BLOCKED | constants MELEE/SHOT KNOCKBACK | NOT FOUND (p/as/af0f5 hunt) | **trace T9** — seeded at reaction-state entry, not a record field |
| B/X contextual resolve | schema (ATK-001) | command.ts | FUN_800699d8 + testers (ai) | **trace T1** — +0x585/+0x586 ↔ button map |
| Melee contexts (5-way) | schema | movementContextOf | subtype +0x586; wiki 5-context (av) | trace T2 |
| Ammo/refill (3 weapon cells) | DONE (values extracted) | ammo.selftest, combat.ts | zz_006dbe0_/006dcc0_/006de10_ (ai/aw) | X-attack→cell-1 (survey UI #2); types 2/3 = dead (ax) |
| Penetration (none/borgs/total) | data (moveProperties) | borgMoveProperties.json | wiki (aw) + rehit chunk_0013 (O) | trace T6 to confirm engine gate |
| Projectile solidity/PvP | data + BLOCKED | moveProperties | shape table 0x802da740 = NOT pvp (at) | trace T5 |
| Hyper / Power Burst | shell (ATK-011) | burst.ts | +0x6fb/+0x6fc, zz_005b2b8_ (aj/S) | **trace T3** — meter+duration |
| Fusion | data + shell (ATK-018) | fusion-pairs JSON | pair table 0x802d352c (aj) | trace T3 (co-op control split) |
| Statuses (id/timer/immunity) | shell (ATK-010) | status.ts | +0x71a/+0x71c/+0x5a0 (Q/aw effects) | trace T8 per-id semantics |
| Vampire lifesteal | data (ids) | ATK-019 shell | chunk_0003.c:6318 ids 0x702/0x70a (an) | HP-drain loop dig |
| Nurse heal | table located | ATK-019 shell | table 0x802d1130 (ax) | dig zz_0088e50_ for HP-write + amount |
| Mash extra hits | shell (ATK-017) | constants MASH | +0x550 cap 4 (T/ax) | trace consumer |
| Contact damage | scaffold (ATK-006) | disabled | per-borg authored (am/av) | trace T2 stomp |
| Levels | DONE (row select) | sourceBorgStats.ts | +0x3ec, DAT_804339e8 (ak); row=lvl+1 (av) | wire EXP thresholds from saves; fix level-aware row index (see §7) |
| Lock-on | CHECKED_CLOSED | combat.ts TUNED heuristic | no ROM system exists (q) | — |

---

## 2. Physics → source

Port: `packages/physics/src/*`, `packages/combat/src/movement.ts`, `constants.ts`.

- Movement anchor: ground speed 22.0 u/f DERIVED_TRACE (behavior-notes §ac); everything else
  (jump velocity/gravity, dash speed/duration/iframes, accel/decel) is **TUNED** — audited
  §s, not findable in the corpus. **Finish via golden-trace fitting**
  (`scripts/trace-golden-record.mjs` → `trace-golden-analyze.mjs`), a human-driven capture.
- Knockback direction ported (mode 1); magnitude TUNED (see §1).
- Three flight models observed ((ap) W17): winged forward-locked / air-class permanent /
  boost — the port has one FLY_MULT; a fidelity gap for flyer/air borgs.
- Stage collision: triangle mesh from STIH, present on 18/40 stages.

---

## 3. UI / UX → source

Port: `apps/game/src/ui/*`, `apps/game/src/main.ts`. ROM: manual (ao), challenge menu (x).

**Screens (all real components):** MainMenu, SelectDifficulty, SelectPlayers, LoadBoxData,
SelectForce, ForceBuilder, BattleIntro, Results, PauseMenu.
- MISSING: STORY / VERSUS / ACTION / COLLECTION / TRADE / OPTION are dead menu entries
  (only Challenge + Edit-Force actionable). MainMenu backdrop is captured PNGs, not the live
  3D desk-object selection.
- Menu motion (challengeMenuMotion.ts) matches (x) timings (10-frame settle, 15-frame fly-in)
  but only on SelectDifficulty/SelectPlayers; SelectForce/MainMenu use ad-hoc tweens.

**HUD (BattleHud.ts / presentation.ts) vs manual (ao):**
| Element | Status | Note |
|---|---|---|
| GF energy bars, HP, alert roundel | DONE | — |
| Boost gauge | DONE (fixed 2026-07-03) | now driven by boostFuel |
| B ammo | PARTIAL | single pool |
| **X ammo (separate)** | MISSING | X is cooldown-only; needs weapon-cell 1 (survey #2) |
| Charge gauge | MISSING | chargeFrames tracked but no meter — computable now |
| **Power Burst meter** | MISSING | BLOCKED trace T3 |
| Jump gauge | MISSING | multi-level jump readout |
| Target cursor yellow→red | MISSING | no meleeMode field; computable from lock+distance |

**Controls (adapter.ts):** A/B/X/Y/dash/lock all bound. Gaps vs (ao): L-button target-switch
(R only), Z hold-lock (modeled as press-cycle), double-tap evade (Shift stand-in), air recovery
(missing, W14). B/X/Y contextual behavior blocked on traces T1/T3.

---

## 4. Challenge flow → source

Port: `packages/missions/src/challenge*.ts`. ROM: (ae)/(af), challenge-flow-evidence.md.

| Feature | Status | Note |
|---|---|---|
| Stage rotation (zz_0196dac_) | DONE | 11-entry pool, reroll-while-equal (matches (ae)) |
| Team generation (build_challenge_battle_setup) | DONE (structure) | floor(cost*2/3) charge exact; tables now cross-checked vs DOL extract (2026-07-03) |
| Battle counts 5/10/15, energy 1500/2000/2500 | DONE | cross-checked |
| Timer frozen (18000, [0x50]=1) | DONE | — |
| Win/lose/draw judge (zz_00297c8_ mask) | PARTIAL | battle.ts uses "which team has energy" + first-human view, NOT the per-side count/energy/rule-flag + equality mask model (ae:1763-1787) |
| 3-phase deploy (~36f) | PARTIAL/MISSING | port = single spawn + flat 45f TUNED iframes vs ROM 20/1/15f phases + ally cue 8 (af) |
| Kill accounting (zz_002f8dc_) | PARTIAL | energy/count credited; attacker-kill/victim-loss/+100 score counters missing → allyBorgsDefeated hardcoded 0 |
| Results ratios | PARTIAL | HIT/DODGE ratios fabricated from synthetic attempts/dodges (scoring TUNED) |

---

## 5. Assets / Animation / Audio / FX → source

Detail in the asset survey (session 2026-07-03) + `research/format-specs/*`, `research/asset-inventory/*`.

- **Models:** static 208/208 (100%); animated bakes 185/208 (89%). 23 unanimated: pl0d/pl0e/pl0f
  families + pl0505, pl0511 — render frozen. Pipeline is offline HSDRaw→Collada (README); TS
  `.arc` parser intentionally stubbed.
- **Animation:** Hermite interpolation HONORED (hsd-anim.ts full FOBJ evaluator; offline bake is
  dense per-frame) — resolves (ar) lead 3. slot→bank is mostly heuristic (`pickAnimBank` label
  regex + PREFERRED_LABELS), with DERIVED anchors idle=g0s0/move=g0s1/dash=g0s2-5/hit=g3/down=g4s0
  (the g4s0 relabel fixed a real special-plays-knockdown bug, (r)). 33 substitute fallbacks across
  23 borgs (worst: hit→idle on 10 = no flinch). **Finish via state→(group,slot) dispatch trace.**
- **Audio:** BGM (33 tracks) + menu SFX wired and real. Combat SFX = 5 generic `se00_*` samples
  mapped onto 15 events (TUNED); NO ROM per-action table exists (AnimAudioEventLookup is a red
  herring, (v)) — needs a live SE-dispatch trace. **46 per-borg VOICE cues are extracted but
  completely unwired.** No footstep/land audio.
- **Stages/lighting:** geometry 40/40 visual, collision 18/40; lighting/fog fully DERIVED from
  HSD CObj/LObj/FogDesc (all GX_FOG_LIN → exact THREE.Fog).
- **FX:** real extracted textures (ptcl00/efct00), TUNED effect→cell mapping (PTL/REF unparsed);
  projectiles are 2D billboards, not the 3D it####_mdl.arz weapon meshes.

---

## 6. The port's C-code disambiguation coverage

Of 11,972 decompiled functions (`_index.tsv`): ~89.8% still auto-named (zz_/FUN_), ~9% SDK/
middleware (gnt4/HSD/OS/TRK), ~1.2% (143) given game-logic names. The named set covers the
load-bearing combat spine (hit resolution, damage, param tier, challenge flow, menu dispatch).
Topic-hint buckets in `function-evidence-index.json` (movement-physics 2765, knockback-targeting
2054, force-setup 1566, challenge-menu 569, assets-animation 599) are the unexplored frontier —
movement-physics is the bucket that would retire the most TUNED constants.

**Recommended metric to track:** promote the ~150 behavior-notes-understood functions into the
index as real names (or a sidecar annotations file) so "disambiguated %" becomes a tracked burn-
down like `tuned-burndown.md`.

---

## 7. Ranked roadmap to 1:1

**Tier A — cheap, DERIVED-safe, no trace needed (do next):**
1. Charge-gauge HUD element + yellow→red target-cursor color (both computable from tracked
   state: chargeFrames, lock+distance) — closes 2 visible HUD gaps.
2. X-attack → weapon-cell-1 ammo consumption + separate X-ammo HUD (ammo model already has
   cell 1; (ao) confirms separate counters).
3. 3-phase deploy timing (20/1/15f, ally cue 8) — values DERIVED in (af); replaces flat 45f.
4. Winner-mask judge: port the per-side count/energy/rule-flag equality model (ae) into
   battle.ts evaluateResult.
5. Fix the level-aware row-index path in sourceBorgStats.ts: the empirical rule is
   row = displayLevel + 1 (av, 200/203 validated), but rowOffsetForLevel currently returns
   DAT_804339e8[level] which is only part of the index (default level-0 path is correct and is
   all that's used today, so low-risk — but wrong if levels ever drive it).
6. Wire the 46 extracted voice cues to deploy/KO/win events (real assets, currently unused).

**Tier B — corpus digs (agent-runnable):**
7. Nurse heal HP-write + amount (dig zz_0088e50_ behind table 0x802d1130, (ax)).
8. Vampire HP-drain loop (grep with the 0x702/0x70a path as anchor).
9. state→(group,slot) animation dispatch (trace zz_004beb8_ callers / 35-slot table) — converts
   heuristic anim labels to source-proven.
10. Annotate the 150 understood functions into the index (coverage burn-down).

**Tier C — Dolphin traces (human/TAS-in-the-loop; harness proven):**
11. **T1** command→button mapping (unblocks B/X resolver, biggest feel item) — cursor-flip
    calibration available (ao).
12. **T3** burst meter + duration (unblocks Power Burst HUD + effects + fusion control).
13. **T9** knockback magnitude (the oldest TUNED debt; not in code).
14. **T5/T6** projectile solidity/penetration engine gate (moveProperties has the taxonomy).
15. **T8** status-id semantics; **T2** melee contexts; SE-dispatch audio trace; golden-trace
    movement-constant fitting.

Tier A is ~6 self-contained tickets a cheap coding agent can execute now; Tier B is 4 corpus
digs; Tier C needs the controller. Each Tier-C trace has a ready preset in
`scripts/trace-attack-mechanics.mjs` and a scenario in `attack-mechanics-trace-plan.md`.
