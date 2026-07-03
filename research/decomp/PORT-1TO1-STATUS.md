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
| Combat: knockback **magnitude** | DERIVED (found, bc) — port pending | strength-indexed tables DAT_802dd8a0/DAT_802d3664; port needs scale reconcile |
| Combat: B/X contextual resolver | schema only | **trace T1** (command→button map) |
| Combat: ammo/refill | DONE (B cell-0 + X cell-1 wired) | — |
| Combat: projectile penetration | wired OBSERVED_WIKI (borgs/total→persist) | trace T6 confirms engine gate; terrain-penetration + solidity still open |
| Combat: vampire lifesteal | DONE (ported, ay) | — |
| Combat: statuses / hyper / fusion | shells only | traces T3/T8 (nurse heal-write not in corpus) |
| Physics: movement/jump/dash | DERIVED values found (bc), port TUNED | per-borg data.bin values known — scale-reconcile to port, then swap |
| UI: screens | ~9 real screens | 6 modes are dead menu entries |
| UI: HUD | ~90% (charge✓ cursor✓ X-ammo✓ boost✓ jump✓) | burst meter only (fill data is T3-blocked) |
| Challenge flow | PLAYABLE (verified) + ~85% DERIVED | deploy sub-phases (moot, 36f total already correct) |
| Assets: models (static/anim) | 100% / 89% | 23 unanimated borgs |
| Assets: animation playback | ~88% (dispatch mapped+reconciled, ba/bb) | asset re-bake: relabel g4s0 special_s0→down_s0 (worktree); death/deploy slots unresolved |
| Audio: BGM/menu | ~90% | — |
| Audio: combat/voice | ~45% (voice wired az; sound dispatch mapped bc) | combat SE ids need trace at call sites; voice cue-role TUNED |
| Stages: geometry/lighting | ~90% / ~98% | collision on 22/40 stages |
| FX: particles/projectiles | ~70% | PTL/REF decode; 3D weapon meshes |

**Trace status update (2026-07-03, (bc)):** T9 (knockback magnitude) is **no longer trace-blocked**
— it was found statically in the DOL as strength-indexed tables (DAT_802dd8a0/DAT_802d3664), and
movement physics turned out to be per-borg data-driven (pl####data.bin), not the "unfindable global
constants" §s concluded. The remaining Dolphin-trace unblocks are **T1** command mapping, **T3**
burst meter, **T8** status semantics, and the combat **SE-dispatch** (the menu sound path IS mapped
now, (bc)/menu-cluster: zz_00f0468_ → zz_00efb3c_, id>>7 bank / id&0x7f sample). These need a human
at the controller or TAS-movie injection (see `attack-mechanics-trace-plan.md`).

**Challenge PLAYABILITY verified (2026-07-03):** `scripts/selfcheck-1p-challenge.mjs` (full 1P
battle runs, energy drains, borgs fight), `scripts/selfcheck-challenge-stages.mjs` (all 11
Challenge stages load collision + run 1200f each), and `scripts/run-challenge-tables-crosscheck.mjs`
(battle counts 5/10/15, energy 1500/2000/2500, full stage pool = DOL extract) all PASS. The
"~85%" on Challenge flow is remaining DERIVED-vs-trace FIDELITY (deploy sub-phases), not a
playability gap — a full Challenge run is start-to-finish playable.

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
| Knockback **magnitude** | DERIVED (found, bc) | constants MELEE/SHOT KNOCKBACK (TUNED, port pending) | DAT_802dd8a0[str]=str*7, DAT_802d3664[str]=(str+1)*8, str=actor+0x702 (bc) | port strength-indexed magnitude (scale-reconcile) — T9 NO LONGER trace-blocked |
| B/X contextual resolve | schema (ATK-001) | command.ts | FUN_800699d8 + testers (ai) | **trace T1** — +0x585/+0x586 ↔ button map |
| Melee contexts (5-way) | schema | movementContextOf | subtype +0x586; wiki 5-context (av) | trace T2 |
| Ammo/refill (3 weapon cells) | DONE (values extracted) | ammo.selftest, combat.ts | zz_006dbe0_/006dcc0_/006de10_ (ai/aw) | X-attack→cell-1 (survey UI #2); types 2/3 = dead (ax) |
| Penetration (none/borgs/total) | data (moveProperties) | borgMoveProperties.json | wiki (aw) + rehit chunk_0013 (O) | trace T6 to confirm engine gate |
| Projectile solidity/PvP | data + BLOCKED | moveProperties | shape table 0x802da740 = NOT pvp (at) | trace T5 |
| Hyper / Power Burst | shell (ATK-011) | burst.ts | +0x6fb/+0x6fc, zz_005b2b8_ (aj/S) | **trace T3** — meter+duration |
| Fusion | data + shell (ATK-018) | fusion-pairs JSON | pair table 0x802d352c (aj) | trace T3 (co-op control split) |
| Statuses (id/timer/immunity) | shell (ATK-010) | status.ts | +0x71a/+0x71c/+0x5a0 (Q/aw effects) | trace T8 per-id semantics |
| Vampire lifesteal | **PORTED (aef234f1)** | combat.ts steal+bleed, wired | steal chunk_0003.c:7982/apply 6318/bleed chunk_0006.c:7900 | done: steal=dmg/2 cap@maxHP + 1HP/30f bleed, 47/47 test |
| Nurse heal | **HP-write ABSENT (ay)** | ATK-019 shell | table 0x802d1130 (ax); no +0x1c6 write reachable | Dolphin-trace +0x1c6 on healed ally |
| Mash extra hits | shell (ATK-017) | constants MASH | +0x550 cap 4 (T/ax) | trace consumer |
| Contact damage | scaffold (ATK-006) | disabled | per-borg authored (am/av) | trace T2 stomp |
| Levels | DONE (row=byte+2, ay) | sourceBorgStats.ts | +0x3ec; row=levelByte+2 (av/aw, 200/203) | wire EXP thresholds from saves; 3 non-normal-schedule outliers open |
| Lock-on | CHECKED_CLOSED | combat.ts TUNED heuristic | no ROM system exists (q) | — |

---

## 2. Physics → source

Port: `packages/physics/src/*`, `packages/combat/src/movement.ts`, `constants.ts`.

- Movement anchor: ground speed 22.0 u/f DERIVED_TRACE (behavior-notes §ac). **UPDATE (bc):**
  §s's "not findable" was WRONG — movement is **per-borg DATA-DRIVEN** (pl####data.bin page at
  actor+0x4ac), not global constants. Real DERIVED values now in
  `research/decomp/data/movement-physics-constants.json`: per-borg gravity (+0x6c), jump impulse
  (+0x48), max ground speed (+0x2c), speed stat (+0x50); global max-fall -35.0 (FLOAT_804375f0),
  friction blends (0.98/0.02, 0.90/0.10, 0.80). The port's constants stay TUNED **pending a scale
  reconcile** (the port is ~4× world-rescaled to its 22.0 anchor; raw ROM values ≈4.4× the port's,
  so they can't be swapped 1:1). DASH re-confirmed absent from ROM (port-ism); flight = gravity-
  coeff-0 (no thrust constant), so BOOST_* stays TUNED. Golden-trace fitting still validates scale.
- Knockback direction ported (mode 1); **magnitude now DERIVED (bc)** — strength-indexed tables
  DAT_802dd8a0[str]=str*7 / DAT_802d3664[str]=(str+1)*8 (str=actor+0x702), NO longer trace-blocked
  (see §1). Port change pending scale reconcile.
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
| B ammo | DONE | weapon cell 0 |
| X ammo (separate) | DONE (3b72ee06) | weapon cell 1 + cyan pill/digit readout |
| Charge gauge | DONE (5010cc64) | orange meter above reload pill; flares at full |
| Target reticle color | DONE (5010cc64) | yellow→red at melee range (meleeRange field) |
| **Power Burst meter** | MISSING | BLOCKED trace T3 (damage-fill data not in port) |
| Jump gauge | DONE (32ca8c4a) | multi-level air-jump pips under boost gear |
| Target cursor yellow→red | DONE (5010cc64) | meleeRange field drives reticle tint |

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

Of 11,972 decompiled functions (`_index.tsv`): the research has now assigned a concrete
game-logic **role** to **213** functions — **1.78%** (213 / 11,972) — consolidated into the
machine-readable source map `research/decomp/data/identified-functions.json` (one deduped entry
per address; each traces to a `behavior-notes.md` section, an attack-mechanics findings mechanic,
or a 2026-07-03 corpus-analysis cluster, with a confidence tier DERIVED_ROM / INFERRED /
NAMED_ONLY). This supersedes the earlier ~1.2% / 143 estimate: **205 of the 242 are DERIVED_ROM**
(role read directly from decompiled C or raw ROM data), 21 INFERRED, 16 NAMED_ONLY. The initial
133 covered the load-bearing combat spine (hit resolution, damage formula, HP/ammo/gauge init,
the 35-slot state-handler table, the animation setter, challenge flow + battle judge, camera
policy, command/ammo/burst). The 2026-07-03 expansion added 80 more across three clusters:
**actor update/state-machine/physics-integration** (32 — velocity→position integrator, gravity
ground-snap, param-tier buff system, state-reset/guard/victory handlers), **AI/CPU control**
(15 — the human-vs-CPU input fork FUN_80056900, CPU brain zz_001c9d0_, nearest-enemy targeting,
auto-fusion pairing, difficulty knobs), and **projectile/collision/FX** (33 — the 3 collision
passes, the applyHit ROM equiv zz_003d344_, full projectile lifecycle spawn→fly→despawn, homing,
object pool). The expansion also CORRECTED the collision-pass anchor (real fn 0x8002d7c4, not the
mid-function 0x8002da88). The rest of the corpus is still auto-named (zz_/FUN_) plus ~9%
SDK/middleware (gnt4/HSD/OS/TRK).
Topic-hint buckets in `function-evidence-index.json` (movement-physics 2765, knockback-targeting
2054, force-setup 1566, challenge-menu 569, assets-animation 599) are the unexplored frontier —
movement-physics is the bucket that would retire the most TUNED constants.

**Recommended metric to track:** `identified-functions.json` is the canonical disambiguation
tally; keep it current as new functions get roles (or fold it back into the index as real names)
so "disambiguated %" becomes a tracked burn-down like `tuned-burndown.md`.

---

## 7. Ranked roadmap to 1:1

**Tier A — cheap, DERIVED-safe, no trace needed (do next):**
1. ✅ DONE (commit 5010cc64) — Charge-gauge HUD element + yellow→red target-cursor color
   (charge01 + meleeRange HudState fields; reticle tint plumbed through battleScene.sync).
2. X-attack → weapon-cell-1 ammo consumption + separate X-ammo HUD (ammo model already has
   cell 1; (ao) confirms separate counters).
3. 3-phase deploy timing (20/1/15f, ally cue 8) — values DERIVED in (af); replaces flat 45f.
   NOTE: SPAWN_DURATION is already 36; verify whether the 3-phase split changes observable
   behavior before investing (may be a doc-only refinement).
4. ✅ DONE (commit 3f66777b) — Winner-mask judge: per-side destroyed/equality model (ae) ported
   into battle.ts evaluateResult; BattleState.winnerMask (bit0/bit1/3-mutual/4-timeout) exposed;
   mutual destruction now resolves to 'lose' for the player (was 'draw'), matching FUN_801969a0.
   battleJudge.selftest 16/16.
5. ✅ DONE (commit fcb9c2bc) — level-aware row-index CORRECTED to row = levelByte + 2 (the
   old DAT_804339e8[level] was non-monotonic and wrong; retained for reference only).
   levelRows.selftest rewritten, 42/42. Outliers pl0400/pl0507/pl0d01 remain open.
6. ✅ DONE (commit pending) — 46 voice cues wired: decoded plXX = borg family (az, 208/208
   covered), battleVoiceCues plays cue 00 on deploy / cue 01 on death for the local borg
   (family→group DERIVED, cue-role TUNED). Validation script 8/8 (roster coverage 208/208).

**Tier B — corpus digs (agent-runnable):**
7. ⛔ DEAD-END (ay) — Nurse heal HP-write NOT in corpus. Re-traced table 0x802d1130 + Death
   Borg Theta 0x6a path; no +0x1c6 heal write reachable. Heal amount is inlined/table-indexed
   or truncated. Re-tagged as a Dolphin-trace candidate (watch +0x1c6 on a nurse-healed ally).
8. ✅ DONE + PORTED (commit aef234f1) — Vampire lifesteal decoded (ay) AND wired into combat:
   steal = floor(dmg/2) heal-on-hit capped at maxHP, passive 1 HP / 30-frame bleed floored at 1.
   HEAL.VAMPIRE_ENABLED flipped on; healing.selftest 47/47.
9. ✅ DONE + RECONCILED (commits 4cc03780 (ba) + this (bb)) — state→animation dispatch: anim-setter
   zz_004beb8_ found, 20/34 slots mapped DERIVED_ROM, THEN verified against the port's own extracted
   anim banks: the port's hit=group3 / down=g4s0 are CORRECT (ROM subtable-0 slot 13/14 = port
   group3-slot-13/14 with slot preserved; ROM slot-15 down remapped to g4s0 at load — confirmed by
   the absence of any g00_s15 bank). NO port rewire needed — applying (ba) verbatim would have
   regressed working animation. Surfaced one real asset bug: g4s0 mislabeled special_s0 on some
   borgs (down falls back) — an asset re-bake handled in a separate worktree, not here.
10. Annotate the 150 understood functions into the index (coverage burn-down).

**Also landed this session (beyond the original Tier-A/B list):**
- ✅ Projectile penetration wired (commit 3fea73e8, OBSERVED_WIKI): borgs whose B-shot is
  cataloged 'borgs'/'total' now fire persistent (pass-through) projectiles. The static half of
  T5/T6 — the engine gate is still the trace's to confirm. projectilePenetration.selftest 7/7.

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
