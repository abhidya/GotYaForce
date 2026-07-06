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

## ★ 2026-07-06 session: title-intro residuals CLOSED + CPU AI brain STATICALLY ISOLATED

Multi-agent verified static dig (every claim independently adversarially re-verified from
corpus + raw DOL bytes before landing; workflow `wf_9213949b-b42`). Three deliverables:

1. **Family-ctor anim-bank binding SOLVED** (`title-intro-residuals-decode-2026-07-06.md` §1,
   behavior-notes (bf)): `PTR_PTR_802d3224`[familyByte][variantByte] → ctor. Normal Ninja ctor
   **0x8006f4f8 is a Ghidra-missed function** (raw-disasm read; serves pl0000 + pl000a — Sasuke
   differs ONLY in descriptor +0x4b0, so one family port covers both). G RED ctor zz_018ccfc_
   (0x615/0x629/0x62a). Full anim chain DERIVED end-to-end incl. the previously-missing
   **+0x1d88/+0x1d8c metadata-bank hop** (playAnim operands are (metaBank, metaAnim), NOT
   (group,slot); resolver zz_004d1f4_, parser zz_004d244_, 0x14-stride records →
   (motionFile, fileAnim, mirror/blend/hand-swap)). **groupSel=5 → the borg's own g0 motion
   file, identity-mapped EXCEPT animId 6 → g0 anim 9** (both intro families). Baked `sNN` index
   PROVEN = g0-file anim index. **TitleIntro.ts ANIM_FILES_BY_ID upgraded TUNED→DERIVED**
   (id 6 → anim_g00_s09; ids 2/5 added; tdc-pose-bank theory falsified). Residuals: id-3 rate
   operand 30 unit unpinned; stream-vm.ts shared-bank fallback + missing metadata hop flagged
   for the ROM-runtime layer (actor.ts fields exist, unpopulated). NN ctor full bindings
   recorded for the family port: root dispatcher 0x8006facc, cue table 0x802d3ff8, sound
   0x802d3ca0, damage 0x802d4160, +0x4ec=0x802d4148 (undecoded).
2. **DAT_80390ad0 widget table CLOSED** (§2, same doc): stride **0x14**, **98 rows**
   {s32 id 0..43, u16 kind 0..20, s16 variant −1..5, f32 X/Y/Z}, sentinel 0xFFFFFFFF; dumped
   to `research/decomp/data/title-widget-table.json` — **byte-verified against an independent
   re-dump (0 mismatches)**. Real per-kind dispatch = PTR_LAB_8039132c (21 entries; kinds 0-3
   handlers are Ghidra decompile gaps). Two of the 2026-07-05 doc's byte samples were misreads
   (purged). Verify pass REFUTED two consumer attributions (PTR_FUN_80391658/DAT_803914d4
   belong to the separate zz_01deb68_ widget family) — corrected in doc + JSON meta.
3. **CPU AI decision brain FOUND STATICALLY** (`cpu-ai-decode-2026-07-06.md`, behavior-notes
   (bg); supersedes index/cpu-ai-evidence.md's "un-isolated" conclusion): root
   **zz_001c9d0_ @0x8001c9d0**, called per-frame from input refresh FUN_80056900 for actors
   with CPU flag +0x3e6 (set from the pad-present mask at FUN_800541ac init). The AI writes
   the actor-embedded **virtual pad** (+0x5b4 buttons/+0x5ca stick) directly — same fields
   the human path fills from the DAT_803c727c mirror. Fully mapped: retarget cadence
   {4,8,10,12,15,30,45,60}f, nearest-enemy 20000u select, **camera-relative** stick
   ((bearing − (camYaw+180°)) × 54 × 0.8 — +0x5b0 writer found by the verify pass), terrain-
   probe jump, 32-slice weighted attack roulette over six per-borg weights (record
   +0xf0..+0x104) → 0x200/0x400 presses through a 3-phase range+LOS-gated executor,
   difficulty idle-cadence tables (lvl0 74-86f → lvl3 34-46f, dumped), level-0 attack block,
   per-borg quirk overlay, fusion 0x800 hold. All range/steering constants DERIVED. §0's
   "CPU AI approach/kite constants tuned for the old 22-speed world" now has a full DERIVED
   replacement spec (port not started); Priority-8 Dolphin pass is now confirmation-only
   (plan in doc §5).

**Session part 2 (same day): NORMAL NINJA family PORTED (2nd family) + shared-X layer +
combo-reconcile root-cause + a real projectile-drop sign bug fixed** (verified workflow
`wf_a6dd44f6-f67`; full record `nn-family-decode-2026-07-06.md` + behavior-notes (bh)/(bi)):

4. **NORMAL NINJA family landed** — Tier D grows to 2/~31 families. The big architecture
   find: pl0000's X-special routes to a **SHARED engine machine** (zz_00ff2bc_ @0x800ff2bc,
   3 phases) parameterized by a per-family config block — ported once as
   `families/shared-x-special.ts`; `families/ninja.ts` adds the family callback (backflip
   10/15/−1 + yaw+180°, shuriken zz_007db5c_ type 0 / SASUKE type 3 via the new
   `StreamContext.onFamilyProjectile` hook — host table-wiring residual). pl000a (SASUKE)
   is covered free (ctor differs only in descriptor). Charge actions are command-disabled
   for BOTH this family's borgs AND (verifier extra) G RED's types 4/5. Cue tables for
   both families upgraded to FULL 48-row DERIVED dumps in bridge.ts (cues 44 AND 45 →
   state 61). +0x4ec identified = command-move root (ctor-decode open question closed).
   Actions 0/1 (B-combo, lunge — incl. a second shared machine zz_00fed6c_) transcribed
   to phase granularity in the doc, not yet ported. `pnpm selfcheck:rom` green with 3 new
   ninja test blocks.
5. **comboHits vs ladder 58-borg disagreement ROOT-CAUSED** (behavior-notes (bi), 11/11
   claims verified): 83% = stale asset inventory + a heuristic-ordering bug (runtime
   already correct via the ladder override — raw-data hygiene only); **3 borgs were a real
   port bug — FIXED**: stepFromKind now accepts −1/−2 open-window sentinel records
   (labeled TUNED active length 8), restoring pl0501→2 / pl0a00→3 / pl0a02→3 (= ROM
   armed-rung = asset counts); 7 borgs honestly UNRESOLVED (ninja whiff-rung + table-end
   shapes — need a live trace; do NOT blanket-fix).
6. **Drive-by REAL BUG fixed**: 31096d1c's ROM projectile-variant wiring fed the ROM's
   NEGATIVE-down drop values into the port's POSITIVE-down `Projectile.drop`
   (`vel.y -= drop`) — ROM-droppy bullets ROSE. Caught by assertChargeShotTiers (the one
   suite 31096d1c didn't run); fixed at the spawnProjectile boundary + assert hardened.
7. **VALIDATED**: `pnpm -r run build` clean; `pnpm selfcheck:rom` all-pass; full combat
   selfcheck PASS; 1P challenge smoke PASS (resolvedFrame 5191→6524, expected — ROM-variant
   bullets now actually fall + the ninja X blink-away changed spacing); 11-stage +
   family-variant smokes PASS; projectile 36/36; xammo 32/32; menu-flow PASS. TitleIntro
   id-6 anim fix verified live in the browser preview (correct s09 files fetched for both
   actors, clean console/network, desk scene renders).

---

## ★ 2026-07-05 session (later): ROM per-family state-machine engine — architecture finding + G RED landed

**Architecture finding (research/decomp/action-vm-and-gcrash-decode-2026-07-05.md): real move
MOTION lives in per-family C state-machine handlers, not shared data tables.** Decoded the last 8
action-script VM opcodes (0x02-0x07/0x0b/0x0c, chunk_0006.c:1996 `zz_004cd24_`, dispatch table
`PTR_FUN_802d0da0`) — every one is a per-part STATE/FLAG/weapon-swap setter (contact latch,
part-target flags, hand/weapon attachment swap); **none writes velocity or position**. Traced G
RED's X-special ("G Crash") end-to-end as a 4-phase family state machine (`FUN_8018e888` chain,
chunk_0047.c:777-970): launch (Y-impulse 4.0, `FLOAT_8043b158`) → air-dash/stream-tick → on-contact
dash (60.0 XZ / 10.0 Y, `FLOAT_8043b148`/`_15c`) → descend/land. **This is why the existing
generic-archetype combat.ts (one shared `projectile`/`aoe`/`melee` `SpecialActionDef` shape for
every borg) cannot fully reproduce real per-borg move feel** — the archetypes model the shared
data (hit windows, damage records, reach) correctly, but the actual phase-by-phase motion driver
is unique C code per family that was never ported.

**Response: started a ROM-faithful actor runtime, `packages/combat/src/rom/*`, composing
alongside (not replacing) the existing BorgRuntime/combat.ts.** Foundation layers all DONE and
unit-tested (`pnpm selfcheck:rom`, 22/22 — `scripts/run-rom-tests.mjs`): actor struct map
(`actor.ts`), physics integrator (`physics.ts`, ports `FUN_80067310`), cue→state→command dispatch
(`dispatch.ts`, `zz_006a6fc_`/`zz_006a750_`/`zz_006a104_`/`FUN_80065dfc`), the full 18-opcode
action-stream VM (`stream-vm.ts`, `zz_004beb8_`+`zz_004cd24_`), and populated state tables
(`state-tables.ts`, 64+64 slots). **First family ported: G RED's X-special** (`families/gred.ts`,
the 4-phase G Crash above) — wired into the live battle sim via `bridge.ts` (BorgRuntime ↔
RomActor field sync, composes with movement.ts/combat.ts rather than replacing them; borgs with no
ported family keep today's generic-archetype behavior unchanged, `romDriver = null`). Cue-table
extractor (`scripts/extract-family-cue-tables.mjs`) resolved 17/30 families' direct
`lis`+`addi`-pattern cue tables automatically; G RED's own table is still hand-transcribed in
`bridge.ts` pending the indirect-load (`lwz`-based) extractor path.

**NOT YET PORTED (see `packages/combat/src/rom/PORTING.md` for the full tracker + per-family
recipe):**
- G RED's OWN other actions — B-melee/dash/B-charge (actionIndex 0/1/3/4 of the same
  `chunk_0047.c` dispatcher) — only the X-special (actionIndex 2) is ported so far.
- **~30 other families' state machines** (Star Hero's X dash, Sword Knight's specials, etc.) —
  each is its own unique 3-4 phase C handler; G RED is the reference template but every other
  family needs its own transcription pass (~0.5-1 session each once the template is proven,
  ~15-25 sessions total for full-roster coverage). Until a family lands, its borgs keep the
  existing generic-archetype `combat.ts` path (safe fallback, not a regression).
- Indirect-load (`lwz`-based) cue-table extraction for the 13/30 families the automatic
  extractor couldn't resolve.

VALIDATED: `pnpm -r run build` clean, `pnpm selfcheck:rom` 22/22 (state-table dispatch, bridge
X-press → ROM launch, physics integration, cue→state→action dispatch, G RED phase-0 launch
impulse) — pushed main @ `31096d1c`.

---

## ★ 2026-07-05 session: combat-feel-gaps wiring (research/decomp/combat-feel-gaps-decode-2026-07-05.md)

Wired all 5 decode targets from the combat-feel-gaps decode pass, in feel-impact order. Every
item's mechanism is DERIVED per the doc's citations; value-level items keep the doc's own honest
UNKNOWNs labeled rather than guessed. Existing selfcheck/test suites stayed green throughout
(see per-item deltas below); combat/missions selfchecks + selfcheck-1p-challenge/
selfcheck-challenge-stages/selfcheck-menu-flow/selfcheck-hud/run-projectile-tests/
run-xammo-tests (plus burst/healing/judge/ammo/status/mash-counter/contact-damage/fusion/
move-properties/level/penetration/attack-schema selftests, checked proactively) all PASS.

1. **ANIM-GATED REACTIONS + REAL KNOCKBACK — WIRED.** `applyHit` (combat.ts) now selects
   GROUND (`zz_005ec20_`, gauges.ts `knockbackGroundSpeedForRecord` = idx*7 × scale-ratio) vs
   LAUNCH (`FUN_8005ed38`, existing `knockbackVelocityForRecord` = (idx+1)*8, pitch-split by
   T8 trim) knockback tables, selected by `knockdown || pitchTrimUnits !== 0`. Scale-ratio
   (`knockbackScaleRatio`, gauges.ts) is wired as a real formula call with both sides pinned to
   1.0 (T5's size-scale pipeline doesn't exist on BorgRuntime yet — honestly labeled, not
   hardcoded away). movement.ts integrates the two families separately while
   `state ∈ {hit,down}` and `reactionKind` is set: ground decel = -speed/20
   (`REACTION.GROUND_DECEL_FRAMES=20`, frames-to-stop denominator, not a flat slope), launch
   decel -0.1/frame + gravity -1.2/frame (`REACTION.LAUNCH_DECEL/LAUNCH_GRAVITY`) — replacing
   the generic walk-decel/fall-gravity for the reaction's duration only; the gauge-based
   stagger GATING (down/balance gauges, REACTION_FORCE_STAGGER_MASK) is untouched. Reaction
   RELEASE is now anim-length-gated via `reactionAnimLengthFrames(borgId, kind)` (combat.ts) —
   DEFERRED: no per-borg reaction-clip length is exported anywhere in this port's asset
   pipeline (packages/combat is renderer-agnostic; borgPresentationAssets.ts's clip data never
   reaches it), so this always returns the labeled TUNED fallback
   (`REACTION.GROUND_STAGGER_FALLBACK_FRAMES=14`/`LAUNCH_FALLBACK_FRAMES=30`, anchored to the
   OLD MELEE.HITSTUN/STATE.DOWN_DURATION so today's feel doesn't silently regress) — but every
   call site already goes through the one function, so wiring real per-borg lengths later is a
   one-function change. `enterDown`/`stepActionState`'s "down" case now read
   `cooldowns["downAnimFrames"]` instead of the bare `STATE.DOWN_DURATION` constant.
2. **ANGLE TRIMS — WIRED.** `DamageRecord.knockbackYawTrim`/`knockbackPitchTrim` added to the
   gauges.ts interface (the JSON data already had both fields in damageRecords.json AND
   familyDamageRecords.json — nothing to regenerate). Pitch trim feeds the LAUNCH knockback
   split above (`knockbackPitchTrimRadians`, combat.ts); yaw trim feeds
   `knockbackDirectionFromPositions`'s existing (previously always-0) `trimYaw` parameter via
   `angleTrimByteToBam16` (@gf/physics, already existed, just never called with a real value).
   SIGN: took the doc's own plain-English reading ("positive trim pitches the launch UP") —
   labeled as an assumption in `knockbackPitchTrimRadians`'s doc comment and exercised by
   `assertPitchedKnockbackRisesForTrimmedRecord`; not Confirmed by a live trace.
3. **PAIR-BURST side-wide + ally passthrough — WIRED.** `battle.ts` `activateSideWideBurst`
   sets `burstActive`/`burstPaired` on EVERY living team-mate once ANY presser(s) activate
   (was: only the presser(s)) — `drainPowerBursts` now ends a whole side's burst together when
   the metered presser's own meter empties (CPU/non-metered teammates have no meter of their
   own to drain, per burst.ts's existing documented decision). `combat.ts`
   `burstAllyPassthroughBlocks` (the doc's `zz_002fd7c_` finding) wired into all 3 hit-check
   sites (melee loop, special AoE loop, projectile hit test): a same-team attacker cannot hit a
   bursting ally at all, exempted only by the attacker record's flagsB bit 0x10 (matches the
   doc's 107/1530-record exemption count). The existing 6-frame arm window
   (`BURST.ARM_WINDOW_FRAMES`) and 2-presser requirement already matched the doc's description
   — verified, not changed.
4. **GUARD /40 DATA RULE — WIRED.** `damageFormula.ts`'s `blockDivisorActive` caller flag
   retired; the /40 divide is now gated on `(record.flagsA & 0x1000) && (victimStatusImmunityA &
   0x1000)`, where `victimStatusImmunityA` is `movementData.ts statusImmunityMasksForBorgId(...)
   .immunityA` — VERIFIED the same pldata+0xa8 word already extracted for the status-immunity
   gate (the doc's own "verify" instruction). `combat.ts applyHit` wires it from the victim's
   borgId on every source-context hit. Also wired the /40 rule's two documented side-effects:
   flagsA 0x1000 skips combo-score accrual (chunk_0003.c:7934) and (pre-existing, verified
   unchanged) bypasses the same-team ×0.25 divisor.
5. **CPU FLAG + FORCE-GAUGE — WIRED (7/7 damageFormula.ts discrepancies addressed).**
   `damageFormula.ts`: (1) `attackerForceRatioIndex`/`defenderForceRatioIndex` now wired end to
   end — new `BattleState.energyMax` (snapshotted once at battle creation, round-down-to-10 per
   the doc) + `forceGaugeRatioIndex(energy, energyMax)` helper, fed from `battle.ts` via new
   `DamageRuntimeContext.energyByTeam/energyMaxByTeam`; (2) HP-curve skip-gate documented as an
   accepted equivalence (curve[0]==1.0 always, verified) rather than silently relying on the
   clamp coincidence; (3) CPU-side ×0.5 halvings wired via `heroTableFor(ownerPlayer)` +
   new `attackerIsCpuSide0`/`defenderIsCpuSide0` fields, gated on `cfg.challengeMode !==
   undefined` (`battle.ts isChallengeMode`) so Versus-mode damage stays byte-for-byte
   unchanged — the doc scopes the halving to Challenge modes 0/1 specifically; (4) step-17
   `victim+0x5e0 & 0x4000000` documented as NOT REPRESENTABLE (no port-side +0x5e0 field exists
   at all yet) via a permanently-false `victimSpawnProtection5e0_4000000` field, rather than
   silently doing nothing uncommented; (5) defender post-hit HP index FIXED to use the record's
   raw `hpDamage` instead of the damageScale-multiplied `recordBase` (diverges whenever
   damageScale != 1, e.g. charge tiers); (6) `blockDivisorActive` retired, see item 4 above;
   (7) naming comments added (`pairNerf_80436f9c` = pair-attack BONUS not nerf; `heroTable` =
   CPU-controlled table, not "hero" — `heroTableFor()` documents the T2 correction).
6. **SELFCHECKS added** (packages/combat/src/selfcheck.ts, one per item):
   `assertReactionOutlastsFlatConstantWhenAnimLonger`,
   `assertPitchedKnockbackRisesForTrimmedRecord`, `assertSideWideBurstFlagsBothTeammates`,
   `assertNukeVsFortressIs125` (isolates the /40 ratio rather than asserting the raw headline
   125 unconditionally, since this specific attacker/victim pairing's OTHER formula multipliers
   aren't neutral — see the honest note logged by the assert itself),
   `assertForceGaugeCurveChangesDamageAtLowSideEnergy` (falls back to a direct curve-table
   comparison if the sampled borg/record's curve happens to be flat at the two sampled
   indices). All 5 pass; full combat selfcheck suite (94 asserts + the 1v3 sim) still PASSES.
7. **VALIDATION — all green.** `pnpm typecheck` clean throughout. `pnpm -r run build` clean.
   Smoke deltas (numbers DID change, as expected — reaction lengths/knockback changed):
   `selfcheck-1p-challenge.mjs` resolvedFrame 1732→5191 (win either way) — the battle now takes
   much longer because knockback pushes borgs out of melee/shot range more (real scale-indexed
   magnitude vs the old flat multiplier-only model) and ground reactions decay over 20 frames
   instead of snapping instantly; `selfcheck-challenge-stages.mjs` per-stage frame counts shifted
   similarly (e.g. st00 260→227, st0e 501→364 — direction of change is NOT uniform, since some
   stages resolve FASTER with the new pitched-launch knockback keeping victims airborne/away from
   counterattacks) but all 11 stages + both family-variant stages still PASS. `selfcheck-menu-flow`/
   `selfcheck-hud` unaffected (static checks, no sim). `run-projectile-tests`/`run-xammo-tests`
   unaffected (36/36, 32/32). Proactively also re-ran burst (70/70), healing (47/47), judge
   (16/16), ammo (3097/3097), status (16/16), mash-counter (15/15), contact-damage (4/4), fusion
   (112/112), move-properties (57/57), level (46/46), penetration (11/11), attack-schema (81/81)
   selftests — all green, confirming the reaction/knockback rewrite didn't regress adjacent
   systems.

---

## ★ 2026-07-04 session: projectile flight-visual resolver wired (honest fleet coverage: 0/208 today)

Extended `research/decomp/efct-consumers-decode-2026-07-04.md` §3's shot-init row decode
(FUN_8007dd84's +0x00 texId|flags / +0x34 launch-FX byte) into a runtime resolver and threaded
it to spawned projectiles, using the SAME guarded fire-site attribution machinery
(`borgShotKinds`) the B-shot HIT-kind resolver already uses.

- **`attackHitData.ts` — `shotFlightVisualForBorgId(id)`**: resolves `{ bankTexId, teamTint,
  launchFxId }` from a borg's guarded `borgShotKinds` attribution, restricted to rows whose
  TABLE shares table `0x802d6d68`'s proven byte shape (stride 56 / kindOffset 3 — the ONE shape
  the decode note documents at those offsets). Verified independently (by a second, isolated
  agent) that this shape gate is load-bearing: reading the same nominal offsets in
  differently-shaped tables decodes to texIds far outside the 157-entry efct00 bank (1794,
  3213, 9219, 3596, 3615, 16383 — the census's own `0x802d9758` table's few flag-shaped hits
  are a coincidence, confirmed by inspecting its actual value set). Returns null (keep today's
  visualKind) when unattributed, wrong-shaped, or the row's texId|flags has NEITHER 0x4000 nor
  0x8000 (a per-player weapon-bank row, not efct00 — the dominant case). New
  `shotFlightVisualForTableRow(table, variant)` (direct row decode, bypassing borg attribution)
  and `hasSafeShapeShotAttribution(id)` (coverage telemetry) support the selfcheck.
- **Honest fleet finding, asserted not hidden**: of 208 roster borgs, 42 have a guarded
  attribution landing in the one provably-safe table shape, but **all 42 land on a weapon-bank
  row** — the two real ROM rows that DO carry a bank flag (table `0x802d6d68` variant 6-9,
  texId 125, both flags, the "G RED/BLACK 0x615-family" row the original decode note describes
  in prose; table `0x802d7b10` variant 10, texId 9, 0x4000 only) have **no call-site-guarded
  borg attribution at all** — their firing functions (`FUN_80166fa8`, `zz_0092534_`) carry no
  static actor-id guard the extractor could prove, so no borg's shot legitimately resolves a
  bank flight visual today. **This is not a bug**: `shotFlightVisualForBorgId` is correct and
  conservative; the ROM's own call-site structure just doesn't yet give up which borg fires
  those two rows. 166 borgs are unattributed or attributed to a different-shaped table.
- **`types.ts`**: `Projectile.flightVisual?: { bankTexId, teamTint, launchFxId }` (renderer-
  facing only, no sim-side gameplay effect). **`combat.ts` `spawnProjectile`**: spreads the
  resolved visual onto every spawned projectile (undefined for the honest-null case above —
  every borg's projectile is byte-for-byte unaffected today, including G RED and pl0000, both
  explicitly asserted).
- **`battleScene.ts`**: `syncProjectiles`/`spawnProjectile` (renderer) now check
  `projectile.flightVisual` first and, when present, build a bank-mesh Group via the SAME
  cached `bankFxTemplate`/`sampleBankAnim` machinery `spawnMuzzleFlash`/`spawnHitFx` use —
  team-tint rows sample the entry's matAnim at the shooter's team frame (1/3, same convention
  as the muzzle flash) once at spawn; the mesh tracks the projectile's position and flight-yaw
  every frame and fades via each layer's own rest opacity, same policy as `BankFxActor`. Falls
  back to the existing sprite/beam stand-ins whenever `flightVisual` is absent OR the texId has
  no drawable bank entry. Launch-FX: within the safe-shape table family the only launch-FX id
  ever paired with a bank-flag row is 0 (both real bank rows above), which is already wired
  (the generic muzzle flash, texId 35) — no new launch-FX id needed this pass.
- New selfcheck `assertShotFlightVisualResolution`: (a) direct-row decode of the two real ROM
  bank rows is byte-exact (`shotFlightVisualForTableRow`); (b) a weapon-bank row in the SAME
  safe-shape table decodes to null (proves the flag gate, not just the shape gate); (c) an
  out-of-shape table is never read regardless of its bytes; (d) G RED and pl0000 (the latter
  landing IN the safe-shape table on a weapon-bank row — a stronger negative than "wrong
  shape") both resolve null and pl0000's actually-spawned projectile carries no
  `flightVisual`; logs the fleet split (0 resolved / 42 safe-shape-but-weapon-bank / 166
  other) every run so a future census update that adds a borg guard to those two functions
  will visibly move this number.
- DERIVED vs TUNED: the row shape gate, byte offsets, flag semantics, and the two real ROM
  rows' decoded values are all DERIVED (independently re-verified this session). The
  team-frame sample values (1/3) and "sample once at spawn, not per-frame" policy reuse the
  existing muzzle-flash convention (already DERIVED there); the yaw-from-velocity orientation
  or the bank mesh is the same TUNED stand-in `spawnHitFx`'s directional layers already use for
  the ROM's real attacker->contact/shot-axis basis.
- VALIDATED: `pnpm typecheck`, `packages/combat/dist/selfcheck.js` (full suite incl. the new
  assert), `scripts/selfcheck-1p-challenge.mjs`, `scripts/selfcheck-challenge-stages.mjs`,
  `scripts/run-projectile-tests.mjs` all PASS; challenge/stage smoke numbers UNCHANGED (this
  pass is a strict visual-only no-op for every borg today).

---

## ★ 2026-07-04 session: B-shot HIT kind resolved from guarded fire-site attribution (non-zero kinds wired)

Closed the "General wiring needs each fire-fn's shot id read" gap noted in B6 above.
`shotVariantKinds.json` gained `borgShotKinds`: 130 borgs / 267 call-site-guarded attributions
(all 267 join-verified against the borg's own hit.bin remap, `remapHasKind: true`), each mapping
a borg to the HIT kind(s) its B-shot fire fn actually spawns — as opposed to the port's prior
kind-0-for-everyone heuristic (G RED-only ground truth).

- **`attackHitData.ts` — `shotKindForBorgId(id)`**: new resolver. `borgShotKinds` is keyed by the
  runtime borg-id guard value (`*(short*)(actor+1000)`), a DIFFERENT id space from the `pl####`
  file id used everywhere else in the package — the two are the same digits read in different
  bases (pl0615/G RED ↔ guard `0x615`, pl0629/NEO G RED ↔ guard `0x629`); `borgIdToShotKindKey`
  converts. When a borg has attributions, the resolver picks the MODE (most common) kind among
  them, filtered to `remapHasKind===true` entries, tie-broken by first occurrence in the
  attribution array. **Tie-break rationale**: a "lowest variant id" rule (as originally
  considered) isn't meaningful here because `id` is a row index into a PER-TABLE array scoped to
  one fire fn/call site, not a global ordering across a borg's different fire fns/tables — e.g.
  pl0407 fires two different tables whose row ids are 120/121 and 0/0 respectively, so comparing
  those ids across tables says nothing about which variant is "baseline". Mode-of-attributions is
  the only borg-level aggregate that's actually comparable. Returns `null` when the borg has no
  guarded attribution (or none pass the remap-join filter), and callers keep the kind-0 heuristic.
- **Wired into both consumers**: `shotHitRadiusForBorgId(id)` now resolves
  `shotKindForBorgId(id) ?? 0` and reads that kind's hit-bin records (was hardcoded to kind 0);
  `combat.ts`'s `shotFamilyRecordSpread` does the same for the damage-record join
  (`familyDamageRecordForBorg`). The existing ≤150 plausibility gate on the radius is unchanged
  and applies to non-zero resolved kinds too.
- **G RED (pl0615) is BEHAVIOR-IDENTICAL**: his only attribution is kind 0 (the generator's own
  ground-truth gate), so `shotKindForBorgId("pl0615") === 0` and his hit radius/damage record are
  byte-for-byte what they were before this change (radius pinned at 20).
- **Fleet coverage**: of 208 borgs, **47 now resolve a PROVEN non-zero B-shot HIT kind** (were
  silently using kind 0 before), 70 resolve a proven kind 0 (no behavior change), and 91 have no
  guarded attribution at all (unchanged kind-0 heuristic fallback).
- New selfcheck `assertShotKindResolutionPrefersProvenAttribution`: (a) pins G RED's resolved
  kind/radius unchanged; (b) pl0000 (NORMAL NINJA) resolves guarded kind 1 (hit-bin radius 10,
  vs. kind 0's 5 and the TUNED profile's 35) and an actual spawned projectile carries that exact
  radius; (c) pl0001 (SHURIKEN NINJA) has no attribution and keeps the kind-0 fallback (radius 5)
  exactly; logs the fleet coverage split above.
- VALIDATED: `pnpm typecheck`, `packages/combat/dist/selfcheck.js` (full suite, all asserts
  green), `scripts/selfcheck-1p-challenge.mjs`, `scripts/selfcheck-challenge-stages.mjs` all PASS.
  **Challenge smoke numbers shifted (expected — more accurate/larger shot hitboxes land hits
  sooner for the 47 newly-exact borgs)**: 1P challenge `firstEnergyChangeFrame` 154→117,
  `resolvedFrame` 2613→1732 (same `stage=st00`, `result=win`, `finalEnergy` unchanged); the
  11-stage smoke's per-stage `energyFrame`/`frames` dropped similarly across the board (e.g. st00
  341→142 / 537→260, st0e 623→361 / 979→501) — `result`/triangle counts/stage set unchanged, all
  11 stages still PASS.
- DERIVED vs TUNED: the borg→kind attribution, its hit.bin radius/records, and the mode
  tie-break's underlying data are all DERIVED (call-site-guarded, join-verified against the
  borg's own remap). The mode-selection RULE ITSELF (as opposed to the per-attribution data) is a
  judgment call documented above, not extracted from the ROM — a borg with multiple genuinely
  different fire-fn kinds (e.g. tap vs. a distinct charged-variant fire path) collapses to one
  "the" shot kind for this heuristic's purposes, same limitation the pre-existing kind-0
  heuristic already had.

---

## ★ 2026-07-04 session: asset-pipeline root cause + command dispatch landed

**A. Every shipped runtime GLB had BLANK embedded textures (root cause of "the game looks
broken").** Two pipeline bugs, both fixed and the full fleet re-exported:
1. `tools/HSDLib/HSDRawViewer/IO/ModelExporter.cs` — texture PNGs were named
   `Texture_{count}` PER SUB-MODEL into a shared directory (later sub-models overwrote
   earlier files with different content), and the diffuse/specular map binding always read
   the texture-LIST-HEAD image instead of the current TObj (mis-texturing every
   multi-texture material). Fixed: content-hash texture names (`Texture_{FNV1a:X8}_{fmt}`)
   + per-TObj binding. pl0615's arc has 4 distinct images; the old export shipped 3 with a
   collision.
2. `scripts/convert-runtime-models-to-glb.mjs` — the Node Image polyfill dispatched "load"
   via queueMicrotask, but @napi-rs/canvas decodes images ASYNCHRONOUSLY after `src=`, so
   GLTFExporter drew every texture from an un-decoded image → every GLB embedded 172/364-byte
   solid-black PNGs (stages, borgs, everything). Fixed: dispatch from the native onload.
   Verified: G RED renders fully red in live battle; st0a embeds real 5–52 KB textures.
   Re-exported: 40/40 stages, 208/208 borg model_00.glb (batch harness:
   `user-data/GG4E/gltf-export/Program.cs` BATCH_DIR mode). UI scenes still pending
   (they shipped with no embedded images at all — separate follow-up).
Also render-side: `ACESFilmicToneMapping` removed (GX has no tone mapping — it compressed
every authored HSD color; now `NoToneMapping`), and BLEND-mode stage props get
`alphaTest 0.1` so invisible texels stop punching depth holes (`prepareImportedModel`).

**B. Command dispatch (ATK-003 dispatch stage) is LIVE.** `packages/combat/src/commandDispatch.ts`:
stepAttacks now builds the transformed-input-word from the frame's buttons
(COMMAND_INPUT_BITS), resolves the type via `resolveCommandType()` (ROM tester priority),
refines B into the +0x4ec type-0/type-1 row from live proximity, selects the borg's exact
decoded command record (subtype 4 preferred airborne, 5 on charge releases), and stores the
result on `BorgRuntime.command`. ROM record gating applied ONLY to the contextual-B
melee/shot split (decoded tables whose type-1/type-0 rows are empty gate that side off);
X/charge rows attach records but are never negatively gated (the type-2↔X mapping mismatches
the wiki catalog for 52/208 borgs — do NOT gate X on it). A same-frame B-charge release now
preempts X per tester priority (type 3 > 2). Selftests: commandSchema 53/53 (incl. live
dispatch for pl0615/pl0405/pl0409/pl0900/pl0e01); moveProperties 57/57; 1P challenge smoke
PASS. Remaining ATK-003 work: consuming record identity for animation/HIT selection
(record bytes cueId/stateMode/actionIndex semantics still undecoded).

**B2. Knockback magnitude PORTED (T9 closed).** applyHit now derives its magnitude as
single-base × strength: gauges.ts `knockbackVelocityForRecord` reads the hit record's +0x0d
strength byte into DAT_802d3664[s]=(s+1)*8 (melee 56 > shot 40 > charge/special 24, all
DERIVED), scaled by ONE tuned anchor (constants.ts KNOCKBACK.PORT_SCALE = 5/56, preserving
the old melee base) × the caller's per-move multiplier. The flat MELEE/SHOT/SPECIAL.KNOCKBACK
scalars are retired (kept as historical anchors). No double-counting: call sites now pass
multipliers only. §1's knockback-magnitude row and §7 Tier-B item 3 are DONE.

**B3. Per-borg movement physics adapter LANDED (scale-reconciled).**
`scripts/gen-movement-physics.mjs` dumps all 208 borgs' pl####data.bin movement pages →
`packages/combat/src/data/movementPhysics.json`; `movementData.ts` applies RATIO-ANCHORED
values (anchor = pl0615, the live-traced borg): jumpImpulse(+0x48)/15 scales JUMP.VELOCITY,
|gravityFall(+0x6c)|/1.0 scales JUMP.GRAVITY (pl0d/pl0e satellite families float at -0.1 —
source data). G RED is bit-identical to before; every other borg's relative jump/fall is now
DERIVED. NOT yet mapped: maxHSpeed(+0x2c) — its relation to the +0x50 speed stat (already
the port's profile.speed input) is unresolved (pl0000 has G RED's 12.0 clamp but stat 3), so
ground speed keeps the stat formula; knockdownLaunch+groundAccel exported as data only.

**B4. RAW-SCALE MOVEMENT MIGRATION + speed chain DERIVED (2026-07-04 second pass).** Full
decode in research/decomp/movement-hit-decode-2026-07-04.md: run speed IS page+0x2c (run
start SNAPS actor+0x44 to it), the "speed stat" (+0x50) is only a launch/landing floor, and
worldDelta = +0x44 × statusTimescale(+0x5f4) × tierVelScale(+0x5f8) with both ×1.0 baseline —
so ROM units are 1:1 and the 22.0 trace anchor is RETIRED (unreconcilable; mis-sample).
Port migrated to raw: ground speed = page+0x2c via movementData.ts (G RED 12.0 u/f), jump =
page+0x48 raw (15.0), fall gravity = |page+0x6c| raw, MAX_FALL = 35.0 (FLOAT_804375f0,
DERIVED), KNOCKBACK.PORT_SCALE = 1.0 (table velocities apply raw), DASH/ACCEL/DECEL/BOOST
rescaled as marked TUNED stand-ins. The haste/slow status tables and the param-tier velocity
table (0x802dd5a0; tier+4 self-buff ×2.366 for 1200f = the "acceleration" archetype) are
decoded but their WRITERS (special moves) are not yet wired — that's the Acceleration-Ninja
speed mechanism.

**B5. HIT pipeline decoded end-to-end + first wiring (Slice 3, partial).** zz_008ac80_ fully
read; melee kinds live per-ANIMATION in the mot event stream (FUN_8004c6b4 reads event
byte[1]); shot/special kinds come from per-family DOL variant tables indexed by the command
record's variant byte; 11 literal call sites mapped (generic shot child = kind 0). Extraction
landed: scripts/gen-attack-hit-tables.mjs → data/attackHitTables.json (208/208 borgs, 4434
remap entries, 4258 records: shape/bone/damage-index/frame-window/offset/extent/radius) +
runtime adapter attackHitData.ts. First consumer: B-shot projectiles use the borg's kind-0
hit volume as hitRadius (plausibility-gated ≤150 — kind 0 is also some deployables' slot).
Damage-table bindings SOLVED: every family binds its own 0x18-stride table at actor+0x27c
(112 tables, G RED = 36 records at DAT_80365ec0; DAT_802d46e0 is only family 01's) —
scanners scripts/scan-damage-table-bindings.mjs / scan-damage-table-extents.mjs. REMAINING:
per-borg family damage-record extractor (recipe in the decode note) → per-hit record
selection; mot event-track extraction → melee kind/frame wiring; per-family variant tables →
shot kind selection.

**B6. SLICE 3 COMPLETE + SLICES 6/8/9 (2026-07-04 third pass).**
- **Family damage records EXTRACTED + WIRED**: gen-family-damage-records.mjs resolves all
  208 borgs' +0x27c tables via per-borg ctor emulation (124 distinct tables; family-01
  validates byte-for-byte; pl0806's 1-record table is real ROM packing). Runtime: plain
  B-shots and melee swings now use the borg's EXACT family record (familyDamageData.ts) —
  G RED's shot hits for its real 20 HP (record 0 of DAT_80365ec0), not the generic 10.
- **Melee action-script kinds EXTRACTED + WIRED**: premise corrected — the event scripts are
  DOL action-script banks at actor+0x1d80/+0x1d84 (NOT mot.bin); 18-opcode format decoded
  (op 0x0a = armHit(kind), op 0x00 wait = the frame clock); gen-melee-anim-kinds.mjs dumps
  114 banks / 863 hit-bearing streams / 191/208 borgs (17 bankless boss/special families are
  code-driven, honest). pl0615 validation 27/27 kinds. Runtime (meleeExactData.ts): first
  B-close swing uses the script-armed kind's EXACT active frame window, authored reach
  (offset+extent), and family damage record — per-borg melee identity is now data
  (G RED f10-12/30hp/170u; Sword Knight f17-20/283u; Magnet Robot 50hp). The
  lowest-armed-kind selection is the one TUNED link (cue→script map still undecoded);
  per-combo-step records deferred — **DONE, see the 2026-07-04 per-combo-step entry below.**
- **Shot variant tables EXTRACTED (data only)**: gen-shot-variant-kinds.mjs — 85/85 static
  zz_008ac80_ sites spawner-linked, 81 tables / 662 rows, incl. the two GLOBAL shot
  registries (0x80303138: 123×0x44; 0x802d7b10: 129×0x38). G RED B-shot chain traced
  end-to-end: all 5 variants converge on zz_018dcb0_ → global registry id 0x2b → kind 0 —
  the port's kind-0 heuristic is EXACT for G RED. General wiring needs each fire-fn's shot
  id read (only 277/662 rows are kind 0); doc corrections: chunk_0036:2328 + chunk_0039:2358
  are static, not dynamic. **FIRE-FN SHOT-ID RESOLUTION LANDED (2026-07-04 follow-up)**:
  the generator now constant-folds every spawner call site (literal ids, unique-constant
  local assignments like `uVar4 = 0x27|0x29` unions, single-param affine spawner transforms
  like `+0x11 = param_2 >> 1`) and scopes borg-id guards (`*(short*)(actor+1000) == id`)
  by brace analysis — **417/662 rows now carry proven fire-fn provenance** (188 kind-0 +
  229 non-zero-kind; was 277 heuristic-only), 498 call sites resolved / 41 honestly
  unresolved (reasons: 15 runtime-field ids, 14 non-constant variables, 9 DOL sub-table
  lookups with unproven index, 3 non-affine spawner writes). New JSON sections:
  `fireSiteResolutions`, `unresolvedFireSites`, per-row `firedBy`, and `borgShotKinds` —
  **130 borgs with call-site-guarded borg→kind attributions, all 267 join their own
  hit.bin remap (attackHitTables.json) cleanly (267/267)**. G RED ground truth is a
  hard-fail gate in the script (0x615 → zz_018dcb0_ → id 0x2b → kind 0). Spot-verified
  vs corpus: zz_0070558_ borg-3 guard variants 0/2; zz_0166bbc_ uVar4 union ids 39-42.
  Runtime wiring of non-zero kinds (replace the kind-0-only lookup in attackHitData.ts
  with borgShotKinds) was data-only this pass — **NOW LANDED, see the 2026-07-04 "B-shot HIT
  kind resolved from guarded fire-site attribution" session at the top of this file.**
- **Slice 6 title/desk intro LANDED**: TitleIntro.ts mounts the real tl00 scene with BOTH
  desk actors composited into it through the authored HSD camera (2026-07-05: single scene,
  no floating viewport). `DAT_8038a4ec` is a FLAT array of 6 big-endian u16 borg ids
  (proven chunk_0006.c:7055 / chunk_0046.c:1176-1192): slot 0 = 0x0615 (G RED), slot 1 =
  0x000a (Sasuke pl000a — Kakeru's partner borg), slots 2..5 = 0xffff empty. Both play the
  recovered desk sequence (anim ids 0,1,6,3,4,7 = g0 slots idle/move/jump_takeoff/dash_back/
  dash_left/jump_land); press-start → menu (set_global_menu_mode(9) model). Stage placement
  is TUNED pending the tdc00..09.arc anim/pose-bank decode (those hold the real ROM actor
  world coords); asset-failure falls back to the captured PNG. UI scenes re-exported WITH
  textures (813 models, 256 textures — the blank-texture fix applied).
- **Slice 8 mechanism**: timescale.ts ports the status(+0x5f4)/tier(+0x5f8) velocity system
  with exact DOL tables (gen-param-tier-tables.mjs: tier 16=×1.0 … 20=×2.366; haste
  {1.25,1.5,1.75}/slow {0.7,0.4,0.2}/freeze 0.03; burst ×1.5 = FLOAT_804373d8, upgrading
  BURST.SPEED_MULTIPLIER to DERIVED). ×1.0 for everyone until the special-move tier/status
  WRITERS are attributed (the Acceleration archetype = +4 tiers/1200f awaits its family
  dispatch link).
- **Slice 8 WRITERS + hero X tier-buff DONE (2026-07-04, status-effects-decode-2026-07-04.md)**:
  all hit-inflicted status writers from resolve_hitbox_target_effects_and_damage @0x8002e2a8
  are now wired in combat.ts's `applyHitInflictedStatus` (called from `applyHit` on every melee/
  projectile/special connection): discrete slow/haste-on-hit (flagsB&4/8, 900f, level 2),
  contact slow/haste AURAS (flagsB&0x400/0x800, cleared+re-applied every frame, divers
  pl0805/pl080d/pl080e exempt from receiving the slow aura), hit-inflicted grow/shrink
  (flagsA&4/8, ±63 clamp via the new `sizeTierDelta`/`sizeTierTimer` fields, 900f auto-revert),
  and freeze/hitstop (record.hitStrength, normal-reaction hits only, max-merged on BOTH
  attacker and victim, timescale ×0.03). Per-borg immunity masks (data.bin +0xa8/+0xaa)
  extracted into movementPhysics.json (`statusImmunityA/B`) and gate every write; the "the
  Acceleration archetype" attribution above is now REFUTED — the +4/1200f self-buff belongs to
  **STAR HERO (pl0804) / PLANET HERO (pl080c)**'s X ramming-dash special (zz_011230c_
  chunk_0031.c:576-617), wired in combat.ts's `startSpecialAttack`/`applyHeroXBuff`: a
  connecting dash hit grants +4 param tiers (×2.366 velocity) for 1200f if not already buffed,
  reverted by the new `stepHitStatus` per-frame decay pass (battle.ts). Sanity filter applied
  per the report's honest caveat: records with both flagsA grow+shrink bits set (table-extent
  overshoot rows) skip all status application. selfcheck.ts covers slow/haste/freeze/immunity/
  hero-buff with dedicated asserts.
- **Slice 9**: existing captures re-used headless — T11 jump capture shows takeoff deltas of
  EXACTLY 15.0 u/f, live-validating the raw-scale migration; T1 held-B shows the command
  byte stepping 1→2 (tester-order corroboration). New injection presets remain
  human-in-the-loop (no Dolphin session available headless).
- NOTE: CPU AI kiting/approach constants were tuned for the old 22-speed world — several
  big stages now take >1200f to first hit in the smoke (still PASS). AI retune is a
  follow-up, not a correctness gap.

**C. Stale audit detectors fixed:** `audit-real-asset-coverage.mjs` claimed STIH
bounds/triangles were "not wired" — they moved into packages/assets + battleBootstrap in the
app-flow refactor and ARE fully wired (parse → StageAssets → BattleConfig → walls/ceilings/
floor height/spawn placement). Detectors now point at the real path. The "missing source hit
bins" gap is also closed as of 2026-07-05: the 22 st2x/st4x family variants have no on-disc
hit2XX/hit4XX, but they reuse their base st0x arena's hit0XX.bin triplet byte-identically
(sha1-verified per-stage in manifest.json `collisionDerivation`), so all 40 stages carry real
STIH triangle collision at runtime — zero rect-bounds fallback.

---

## ★ 2026-07-04 session: per-combo-step melee (cue→script chain wired fleet-wide)

**Melee combo chains are DONE (per-step), not just the first swing.** New adapter
`packages/combat/src/actionStreamData.ts` derives the B-melee combo ladder end-to-end from
`data/actionStreamTables.json` (the cue→family-jump-table→config-seed→(bank,group,slot)
extraction, `research/decomp/cue-script-stream-decode-2026-07-04.md` /
`action-stream-extraction-audit.md`) joined against `meleeAnimKinds.json` (armed HIT kind +
playAnim target) and the existing `attackHitTables.json`/`familyDamageRecords.json` chain:

- `comboLadderForBorgId(id)` resolves action index 1 (ground B) baseline variant 0's seed slot,
  then walks the ROM's `(actor+0x6ea)++` re-arm auto-increment (validated generic mechanic,
  FUN_801780e4) for held-B follow-ups, preferring a resolved chain-callback's redirected variant
  (e.g. NEO G RED's v0→v6) for the ladder's final rung when the extraction recorded one. Capped
  at 3 steps (matches `COMBO.STEP_DAMAGE_MULT.length` / the existing comboHits generator cap).
- **Coverage: 103/208 borgs (49.5%) get a fully DERIVED per-step ladder** (93 with 2-3 steps,
  10 single-step openers only — those still benefit from exact reach/record/damage on step 0);
  **105/208 have no resolved ladder** (dash-only/shot-only/code-driven roots, or the emulation's
  "no stream call reached"/"run capped"/"ambiguous" buckets from the extraction audit) and keep
  today's TUNED `COMBO.STEP_STARTUP_SCALE` rescale unchanged.
- Validated exactly against the decode note's ground truth: **pl0200 (SWORD KNIGHT)** → g3
  s0/s1/s2, kinds 1/2/5; **pl0629 (NEO G RED)** → g3 s25/s26 (auto-increment) + chain callback
  → s27, kinds 1/2/8 (the "standing-mash 3rd-hit finisher"). New selfcheck asserts
  (`assertSwordKnightLadderResolvesThreeSteps`, `assertNeoGRedLadderChainsToS27`,
  `assertUnresolvedLadderBorgStillCombosViaTunedPath`) pin both plus the TUNED-fallback path
  (pl0100, a comboHits=3 borg with no resolved ladder).
- `combat.ts`: `startMeleeAttack` and the swing-resolution block (meleeActiveLen/meleeRange/
  meleeRecord) now prefer THIS combo step's own exact window/reach/record
  (`comboLadderForBorgId(id)?.[comboStep]`) over the first-swing-only `meleeExactData.ts`
  fallback, which itself remains the fallback over the TUNED profile. `stepAttacks`' public
  signature is unchanged.
- **Honest cross-check (not acted on this pass, per the task brief)**: comparing ladder length
  against `actionProfiles.json`'s asset-derived `comboHits` finds **58/208 borgs disagree**
  (e.g. many ninja-family borgs resolve a 2-step DOL ladder but comboHits says 3 from exported
  swing-bank counts, and vice versa for a few). `comboLadderStepCountForBorgId(id)` is exported
  for a future pass to reconcile; `comboHits` itself is untouched here.
- **Anim-label bridge (renderer) LANDED**: verified the `playAnim` op's OWN (group, slot) —
  a DIFFERENT numbering axis than the action-script stream slot — is what the exported clip
  label suffix (`_sNN`) actually encodes (checked against pl0615/pl0629's `anim_index.json`:
  stream g3 s27 arms kind 8 and plays `(group 3, slot 18)` → exported `hit_react_s18`, exactly
  the pre-existing `PREFERRED_LABELS.pl0629.charge_shot` precedent, now understood as this
  combo's 3rd hit rather than a charge move). `BorgRuntime.meleeAnimStream` (set by
  `startMeleeAttack` from the resolved step's `animStreamRef`) flows through
  `BattleActorView.meleeAnimStream` to `battleScene.ts`, which — when present — calls a new
  `loadClipByStreamRef(borgId, {group, slot})` (borgPresentationAssets.ts, direct anim_index
  lookup, bypassing the SLOT_LABELS/PREFERRED_LABELS heuristic entirely) instead of the generic
  melee/melee_alt slot pick, falling back to the existing heuristic when the exact bank isn't
  in that borg's baked anim_index (e.g. pl0200's exporter didn't capture g3 s0/s1/s2 at all —
  confirmed by inspecting its anim_index.json, an honest per-borg exporter gap, not a bug in
  this wiring). Every borg keeps its current visual behavior when no ladder resolves or the
  exact bank is missing.
- VALIDATED: `pnpm typecheck`, `packages/combat/dist/selfcheck.js`,
  `scripts/selfcheck-1p-challenge.mjs`, `scripts/selfcheck-challenge-stages.mjs` all pass.

---

## ★ 2026-07-04 session: air B + B charge exact wiring (fleet-wide, same treatment as melee)

Extended `actionStreamData.ts`'s exact-data join (actionStreamTables.json → meleeAnimKinds.json
→ attackHitTables.json → familyDamageData.ts) from ground B melee (actionIndex 1, above) to the
family action table's OTHER two B-family actions per the decode note's hop-3 table: actionIndex 2
(air B) and actionIndex 3 (B charge). Neither re-arms via `+0x6ea` the way the ground ladder does,
so both are exposed as a single `ExactMoveLeaf` (not a `ComboStep[]` ladder):

- **`airBMoveForBorgId(id)`**: resolves action index 2, baseline variant 0's leaf, preferring the
  extraction's `airSeedSlot` (the airborne-fork slot, config's air-config byte guarded on
  `actor+0x5e0 & 0x40`) over the shared `seedSlot` when the extraction captured a distinct one.
  **Coverage: 18/208 borgs** resolve a fully-armed (kind ≠ null, with a windowed hit-bin record)
  air-B leaf. Ground-truth-validated against the decode note's G RED row (bank 0x80366220, g4 s0,
  kind 15, records `[33]`) — the note's own `groundTruth` correction clarifies this row belongs to
  id `0x615` (G RED), not `0x629` (NEO G RED) as first drafted; NEO G RED's OWN air leaf (g4 s1,
  kind 29) is a separate, equally-valid resolution.
- **`chargeMoveForBorgId(id)`**: resolves action index 3, baseline variant 0's leaf (always
  group 4). **Coverage: 2/208 borgs** resolve a fully-armed charge leaf (pl0209 kind 23 with a
  record; pl0203 kind 18 with no windowed record). The roster-wide low coverage is the HONEST
  outcome, not a bug: B charge streams are frequently windup-only (kind null) — G RED's own g4 s2
  charge slot isn't even captured in `meleeAnimKinds.json`'s bank 0x80366220 (only g4 s0/s1/s4
  were captured for that bank), matching the decode note's finding that G RED's charge fire is a
  **spawned projectile child** (`zz_00e19a8_`), not a captured melee-style stream — so
  `chargeMoveForBorgId("pl0615")` correctly returns `null` and the runtime keeps its existing
  fallback exactly (asserted by `assertGRedChargeStreamUnresolvedKeepsFallback`).
- **`combat.ts` — air B**: `stepAttacks`' melee call site resolves `airBMoveForBorgId` only when
  `!b.grounded`, and only USES it when armed (`kind !== null`); `startMeleeAttack` takes the
  resolved leaf as a new optional trailing param and lets it override window/anim exactly like a
  combo-ladder step does, and persists a `b.cooldowns["meleeAirSwing"]` 0/1 latch (added to the
  `stepCooldowns` skip-list alongside the other press-latches) so the swing-resolution block —
  which re-reads exact data every active frame from `b.cooldowns["comboStep"]`, independent of the
  call that started the swing — keeps using the air leaf's reach/record for the swing's whole
  duration even if the borg lands mid-swing. Grounded swings and borgs without an armed air leaf
  are byte-for-byte unaffected; `stepAttacks`' public signature is unchanged.
- **`combat.ts` — B charge**: `startShotAttack` resolves `chargeMoveForBorgId` on any tier-1+
  release and sets `BorgRuntime.meleeAnimStream` from its `animStreamRef` (reusing the exact same
  renderer-bridge field the melee ladder sets — generalizing the hardcoded
  `pl0615`/`pl0629`/`pl062a` → `"hit_react_s18"` `PREFERRED_LABELS` precedent in
  `borgPresentationAssets.ts`, which now serves as the fallback for every borg WITHOUT a resolved
  leaf instead of the only path). The charge leaf's damage record replaces the generic
  `CHARGE_OR_SPECIAL` archetype ONLY when gated (`chargeDamageRecordSpread`): the leaf must have an
  armed kind AND a resolved record AND that kind must have real entries in the borg's OWN hit
  remap (`attackHitTableForBorgId(id).kinds`) — otherwise the existing archetype record stands.
  Plain (tier-0) taps are untouched.
- **Renderer**: `battleScene.ts`'s `playSlot` stream-ref bypass (previously gated to
  `"melee"`/`"melee_alt"`) now also covers `"charge_shot"`, so a charged release's exact anim
  stream flows through `loadClipByStreamRef` the same way melee does, falling back to the
  existing `PREFERRED_LABELS`/pattern heuristic when the exact bank isn't in a borg's baked
  `anim_index.json`.
- New selfcheck asserts: `assertGRedChargeStreamUnresolvedKeepsFallback` (G RED's null charge leaf
  keeps today's behavior), `assertArmedChargeLeafSetsExactAnimAndRecord` (scans the roster for a
  fully-armed charge leaf — currently resolves to pl0209 — and asserts the exact anim stream ref
  AND exact damage record land on release), `assertArmedAirBLeafUsesExactWindow` (scans for an
  armed air-B leaf with a window DIFFERENT from the ground def — resolves to pl0200 Sword Knight,
  5f exact vs 8f ground — and asserts the airborne swing's `meleeActive` length matches exactly),
  `assertUnresolvedAirBAndChargeKeepTodaysBehavior` (pl0100, no resolved leaves either way, plus
  logs the fleet coverage line via `airBChargeCoverage()`).
- VALIDATED: `pnpm typecheck`, `packages/combat/dist/selfcheck.js`,
  `scripts/selfcheck-1p-challenge.mjs`, `scripts/selfcheck-challenge-stages.mjs` all pass.
- DERIVED vs TUNED: every number consumed by the two new resolvers (seed slot, air-seed slot,
  armed kind, hit-bin window, reach, family damage record, playAnim group/slot) is DERIVED
  end-to-end from the same DOL-emulation + hit-bin/damage-table sources as the ground melee ladder
  — nothing new here is TUNED. The `b.cooldowns["meleeAirSwing"]` latch and the
  `chargeDamageRecordSpread` remap gate are port-side bookkeeping/safety checks, not gameplay
  values.

---

## ★ 2026-07-04 session: anim-driven swing SFX decoded + wired (PATH B resolved)

Full decode note: `research/decomp/anim-sound-op-decode-2026-07-04.md`.

- **Stream sound opcode found, then honestly ruled out as the carrier.** The action-script
  handler table @0x802d0da0 was audited handler-by-handler (decomp bodies + raw DOL bl-target
  scans for the non-decompiled ones): op **0x0e** (FUN_8004c97c) IS a playSound op with a
  LITERAL soundId in byte3 (modes: plain / anim-rate id±1 variant / listener-lerped
  positional), and op **0x0f** plays a per-borg table-driven voice/cry (no id in the operand).
  But a full walk of all 114 known action-script banks (12031 slots) finds **zero op 0x0e
  records** — the data never uses it. gen-melee-anim-kinds.mjs still decodes it (future-proof).
- **The REAL swing audio is the PATH-B per-anim sound-event table — now statically extracted**
  (corrects combat-se-ids.json's "requires dumping binary blobs, out of scope" and behavior-
  notes (v)'s "no per-action audio table recoverable"): family ctors bind `actor+0x4e8` (sound
  -event table) and `+0x1d88/+0x1d8c` (anim-descriptor banks). The descriptor record for the
  (group, slot) a stream's playAnim targets carries a per-part sound-list index; records are
  `{u16 frame, u8 windowFlag, u8 mode, u16 soundId, u8 cont}` (consumers zz_005b880_/
  zz_005b98c_, chunk_0007.c:3579/3668). Validated on G RED: every group-3 swing anim plays
  whoosh 0x24 or 0x0b at frames 4-21. Extraction: `gen-melee-anim-kinds.mjs` ctor-emulates the
  three new bindings per borg (incl. the pl062a variant REBIND of +0x4e8) → `meleeAnimKinds.
  json borgs[id].animSounds` (169 borgs, 1325 anim refs, 2984 events, 15 distinct ids;
  hit-bearing slots unchanged at 871, pl0003 still the only validation mismatch).
- **Wired end-to-end**: `actionStreamData.ts` exposes `sounds` on ComboStep/ExactMoveLeaf
  (census over the resolved joins: **103/103 ladders, 281/281 steps, 18/18 air-B leaves, 2/2
  charge leaves carry authored sounds**, 11 distinct ids); `combat.ts` sets
  `BorgRuntime.meleeSounds` per swing/charged release (same bridge as meleeAnimStream);
  `battleScene.ts onSlotEnter` hands it to `main.ts`, which schedules each event at its
  anim-clock frame (60fps) and SKIPS the TUNED slot cue for that swing only (fallback se00_03
  kept for unresolved borgs; the sim-edge melee/charge_release generics are suppressed when
  the local swing is authored so nothing double-plays). 14 new samples exported
  (`export-combat-se.py --ids`, manifest now 23 files: +0x003/005/009/00a/00b/00c/00f/012/020/
  024/067/06a/0ac/0e6).
- DERIVED vs TUNED: soundIds, frames, per-anim binding, and the samples are DERIVED. TUNED
  residue (documented in-code): scheduling hangs off the renderer slot edge + wall clock (not
  the ROM part-anim clock), mode-1 events play the base id (no rate-variant id±1), positional
  modes play flat, and the 150ms per-sample stacking floor is port-side.
- VALIDATED: `pnpm typecheck`, `packages/combat/dist/selfcheck.js`,
  `scripts/selfcheck-1p-challenge.mjs`, `scripts/selfcheck-challenge-stages.mjs` all pass.

---

## ★ 2026-07-04 session: X special (command type 2) exact wiring

Extended the same DERIVED join (actionStreamTables.json → meleeAnimKinds.json →
attackHitTables.json → familyDamageData.ts) to the X button, per
`cue-script-stream-decode-2026-07-04.md`'s finding that a borg's type-2 command records (X
button, `commandMoveTables.ts` `BUTTON_COMMAND_TYPES`) carry the `(actionIndex, variantIndex)`
the ROM dispatch actually runs — unlike ground-B/air-B/B-charge, this is NOT a fixed
`+0x580` value per family (most borgs resolve actionIndex 2, but a real minority resolve
0/1/3/4 instead: 144/96/2291/180/96 active type-2 records across the roster by actionIndex).

- **`actionStreamData.ts` — `xMoveForBorgId(id)`**: reads the borg's baseline command-type-2
  record (`commandMoveTables.ts` `commandMoveRecordsForBorgButton(id, "X")`, subtype 0 preferred
  — same base-row convention as `commandDispatch.ts`'s `selectCommandRecord`), then resolves
  THAT `(actionIndex, variantIndex)` leaf from `actionStreamTables.json` exactly like
  `airBMoveForBorgId`/`chargeMoveForBorgId` do (preferring `airSeedSlot` over the shared
  `seedSlot` when the extraction found a distinct one — the same rationale as air B, since an
  X special is frequently the SAME underlying action/variant as air B, e.g. G RED's pl0615: both
  land on actionIndex 2 variant 0 → bank 0x80366220 g4 s0). Returns `null` when the borg has no
  exact command table or the resolved leaf doesn't join. `xMoveCoverage()` mirrors
  `airBChargeCoverage()`'s roster-scan shape.
  **Coverage: 16/208 borgs (7.7%)** resolve a fully-armed (kind ≠ null, windowed hit-bin record)
  X leaf.
- **Validated against the decode**: `status-effects-decode-2026-07-04.md` §A proved **pl0804
  STAR HERO**'s X (shared hero module with pl080c PLANET HERO) is command type 2 → actionIndex 2
  exclusively, a ramming dash. `xMoveForBorgId("pl0804")` resolves that exact leaf: variant 0 has
  `seedSlot: null, airSeedSlot: 1` (an air-only fork, same shape as several air-B leaves) →
  bank 0x80325c80 g4 s1 → **kind 12**, whose remap records (`[13, 14]`) are real family-damage
  entries — matching the decode's "kind-0xf hitbox live" ramming-dash finding at the mechanism
  level (this pass resolves the exact stream/kind/anim; the buff mechanic itself, `applyHeroXBuff`,
  is untouched TUNED-adjacent logic that already existed).
- **`combat.ts` — `startSpecialAttack`**: both X-fire call sites (plain press-edge and
  X-charge release) now resolve `xMoveForBorgId(b.borgId)` once and pass it through as a new
  optional trailing param. On every fire (any chargeTier), it sets `BorgRuntime.meleeAnimStream`
  / `meleeSounds` from the leaf's `animStreamRef`/`sounds` — same renderer-bridge fields
  `startMeleeAttack`/`startShotAttack`'s charge release already set, so `battleScene.ts`'s
  existing stream-ref bypass picks it up for the `"special"` anim with no renderer change needed.
  The leaf's exact damage record replaces the generic `CHARGE_OR_SPECIAL` archetype ONLY when
  gated (new `xDamageRecordSpread`, copied verbatim from `chargeDamageRecordSpread`'s pattern):
  the leaf needs an armed kind AND a resolved record AND that kind must have real entries in the
  borg's OWN hit remap (`attackHitTableForBorgId(id).kinds`) — otherwise the existing archetype
  record stands. Wired into BOTH special archetypes: the AoE burst loop (`specialRecord` local)
  and the projectile archetype (`spawnSpecialProjectiles` now takes `xLeaf` and spreads
  `xDamageRecordSpread` onto each spawned projectile, same as `spawnProjectile` does for charged
  shots). **No behavior removed**: AoE radius/tier scaling, projectile archetypes/params, and the
  STAR HERO/PLANET HERO ram buff (`applyHeroXBuff`) are all unchanged — this slice only makes the
  record/anim/sounds exact on top of them.
- New selfcheck asserts: `assertStarHeroXResolvesRamActionIndexAndSetsStream` (pl0804 resolves
  actionIndex 2 → kind 12 → a real press sets the exact anim stream, on top of the existing hero
  buff mechanic), `assertArmedXLeafUsesExactDamageRecord` (scans the roster for a fully-armed
  AoE-archetype X leaf whose record is DISTINCT from the generic archetype — currently resolves
  to pl0202 — and asserts both the exact anim stream AND that the actual HP dealt matches
  `computeSourceDamage` run with the exact record, not the generic one), `assertUnresolvedXKeepsTodaysBehavior`
  (pl0100, no resolved X leaf, asserts no stream is set and damage still matches the generic
  `CHARGE_OR_SPECIAL` record exactly, plus logs the `xMoveCoverage()` fleet line).
- VALIDATED: `pnpm typecheck`, `packages/combat/dist/selfcheck.js`,
  `scripts/selfcheck-1p-challenge.mjs`, `scripts/selfcheck-challenge-stages.mjs` all pass.
- DERIVED vs TUNED: the command-record lookup, actionIndex/variantIndex, seed/air-seed slot,
  armed kind, hit-bin window, reach, family damage record, playAnim group/slot, and authored
  sounds are all DERIVED end-to-end from the same DOL-emulation + hit-bin/damage-table sources as
  the ground-melee/air-B/charge resolvers. TUNED residue is unchanged from before this pass: the
  AoE radius/projectile archetype params/tier-scaling constants (wave-1 `SpecialActionDef`,
  OBSERVED_WIKI-selected), and the hero ram-buff velocity/duration constants (already DERIVED
  from the decode, not touched here).

---

## ★ Finish-line handoff (what's left, prioritized) — 2026-07-03

The port is **playable end-to-end** (challenge verified) with every cleanly-derivable mechanic
ported and tested (15 combat suites + 3 challenge selfchecks green). Source map: **300 functions**
role-identified (`identified-functions.json`). What remains splits into exactly three buckets:

**A. Needs a LIVE DOLPHIN SESSION (you drive; I run the presets) — the only true blockers:**
1. **T3 — Power-Burst meter FILL** ("fills as you inflict/receive damage"). The burst state machine,
   arm window, and damage-multiplier EFFECT are mapped (be); only the fill *source* isn't static.
   Trace: watch the burst gauge field vs damage events. Unblocks the burst HUD meter + full burst.
2. **T8 — status per-id CATALOG** (poison/freeze/scramble/swap/transform behaviors). VERIFIED not in
   the static corpus (the status id is an immunity/bone index, not a behavior selector — (bd)).
   Trace: apply each status in-game, watch the actor fields. Unblocks status.ts beyond the framework.
   (Preset scaffolds for both are in `scripts/trace-attack-mechanics.mjs`.)

**B. STATIC but substantial refactors (queued as task chips — dedicated sessions, real risk):**
3. **Knockback magnitude port** — DERIVED data ready (KNOCKBACK_STRENGTH_TABLE + record+0xd). Needs
   the model restructured to single-base × strength across all call sites (naive swap double-counts).
4. **SE-bank extraction** — DONE (2026-07-04). Soundbank format decoded: afs_data.afs
   snd_com01/02/03 (.tsb = LE 128-entry "TSBD" soundId table; .chd = BE Head/Prog/Smpl/Dspi
   chunks, Dspi = u32 dpk offset + standard 96-byte GC DSP-ADPCM header; .dpk = raw ADPCM).
   Bank→slot order proven via the DOL bank table DAT_802d0bec (boot.dol 0x2cdbec → AFS members
   2839..2850; snd_com04 = menu-mode bank). scripts/export-combat-se.py exports the 9 audible
   combat ids to apps/game/public/audio/se/ (id-keyed manifest); main.ts COMBAT_SFX wires
   shoot/hit/down/dash×4/jump/spawn/land as DERIVED. Finding: guard-break ids 0x00/0x80/0x100
   are TSB-muted (volume byte 0) in all three banks — the "layered break stinger" is silent.
5. **Command resolver → stepAttacks** — `resolveCommandType()` implemented + tested; wiring it in is
   the ATK-003 refactor of working attack code.

**C. Open research reconciliations (low-risk, no gameplay impact):**
6. ✅ RESOLVED (2026-07-05, T5 decode `combat-feel-gaps-decode-2026-07-05.md:109`) — The `+0x3ec`
   byte IS the LEVEL byte (ak was right); (be)'s "size/scale class" reading was wrong — the
   size-scale floats are the separate +0xb4/+0xc4 chain driven by the param-tier table, now wired
   via `tierSizeScale()`. Level-row port validated vs wiki and unaffected.
7. The 3 non-normal-schedule borgs (pl0400/pl0507/pl0d01) — per-level HP off the row grid.
8. g4s0 `special_s0`→`down_s0` anim relabel (asset re-bake, separate worktree).

Everything else in the tables below is DONE or an intentional CHECKED_CLOSED. The corpus is otherwise
~97% HAL Sysdolphin / SDK / codec middleware with no game-logic role to assign.

---

## 0. Executive scorecard

| Subsystem | 1:1 coverage | Gating blocker to finish |
|---|---|---|
| Combat: damage formula | ~95% DERIVED (2026-07-05: guard/40 data rule wired, CPU halvings wired, force-gauge ratio wired) | actor level-float init (+0xc4/+0xb4) — level→scale link honestly unfound (T5) |
| Combat: gauges/stagger | ~95% DERIVED; reaction INTEGRATION anim-gated (T6) + per-borg reaction-clip LENGTHS wired (2026-07-05) | residual: 97 ground / 33 launch borgs whose bake lacks the clip keep TUNED fallback (111/208 ground + 175/208 launch DERIVED via `data/reactionAnimLengths.json`) |
| Combat: knockback direction | DONE (mode 1) + yaw trim wired (T8, 2026-07-05) | modes 0/2/3/4 need sub-object data |
| Combat: knockback **magnitude** | **WIRED end-to-end (2026-07-05, T6 + T5)** — ground (idx*7×scaleRatio) vs launch ((idx+1)*8, pitch-split by T8 trim) tables selected per-hit, real per-frame decel/gravity integration in movement.ts; T5 scale-ratio wired via existing `tierSizeScale()` (param-tier table, base uniformly 1.0 at spawn) | no TUNED residue; no per-borg base-scale data needed (decode proves base is uniformly 1.0) |
| Combat: B/X contextual resolver | resolver DERIVED (bd), port upgradeable | fill type/subtype from testers; only pad-bit↔button label needs a dig |
| Combat: per-family move MOTION | **NEW LAYER started 2026-07-05** (`packages/combat/src/rom/*`) — architecture proven: real motion is per-family C state machines, not shared archetype data. 1/~31 families ported (G RED X-special, `pnpm selfcheck:rom` 22/22) | port the remaining ~30 families' state machines (G RED's own B-melee/dash/charge included) — this is now the single biggest lever for "feels like the real game", see `packages/combat/src/rom/PORTING.md` |
| Combat: ammo/refill | DONE (B cell-0 + X cell-1 wired) | — |
| Combat: projectile penetration | wired OBSERVED_WIKI (borgs/total→persist) | trace T6 confirms engine gate; terrain-penetration + solidity still open |
| Combat: vampire lifesteal | DONE (ported, ay) | — |
| Combat: statuses / hyper / fusion | status framework DERIVED (bd); hyper shell now SIDE-WIDE + ally-passthrough (2026-07-05, T3); fusion shell | status catalog T8-blocked; burst-END side-timer clear site still trace-gated (port drives it off the presser's own meter instead); nurse heal-write not in corpus |
| Physics: movement/jump/dash | DERIVED values found (bc), port TUNED | per-borg data.bin values known — scale-reconcile to port, then swap |
| UI: screens | ~9 real screens | 6 modes are dead menu entries |
| UI: HUD | ~90% (charge✓ cursor✓ X-ammo✓ boost✓ jump✓) | burst meter only (fill data is T3-blocked) |
| Challenge flow | PLAYABLE (verified) + ~85% DERIVED | deploy sub-phases (moot, 36f total already correct) |
| Assets: models (static/anim) | 100% / 89% | 23 unanimated borgs |
| Assets: animation playback | ~88% (dispatch mapped+reconciled, ba/bb) | asset re-bake: relabel g4s0 special_s0→down_s0 (worktree); death/deploy slots unresolved |
| Audio: BGM/menu | ~90% | — |
| Audio: combat/voice | ~85% (voice az; SE ids MAPPED bd, EXTRACTED+WIRED 2026-07-04; **PATH-B per-anim swing audio DECODED+WIRED 2026-07-04**) | real bank samples exported (scripts/export-combat-se.py, 23 files) + wired (shoot/hit/down/dash/jump/spawn/land DERIVED); melee/charge swings now play their ROM-AUTHORED per-anim sounds (actor+0x4e8 sound-event table joined via the anim-descriptor banks — anim-sound-op-decode-2026-07-04.md; 103/103 resolved ladders + 18 air / 2 charge leaves covered, TUNED fallback kept for the rest); death stays TUNED (op-0x0f voice is per-borg table-driven, tables undecoded); voice cue-role TUNED |
| Stages: geometry/lighting | ~90% / ~98% | collision 40/40 (18 base + 22 DERIVED-shared-base family variants, sha1-verified 2026-07-05) |
| FX: particles/projectiles | ~85% (hit-impact chain decoded end-to-end 2026-07-04 incl. the texId hop — ptl-format-notes-2026-07-04.md; PLUS muzzle/launch FX family, projectile-row visual fields, slow/haste status FX and the matAnim color tracks decoded+wired — efct-consumers-decode-2026-07-04.md; per-borg flight-visual RESOLVER + renderer wiring landed 2026-07-04, honest fleet coverage 0/208 today — see the top-of-file session entry) | a borg-id guard on FUN_80166fa8/zz_0092534_ (the two real bank-flag rows have no provable per-borg attribution yet) would unlock the first live case; melee hand-flash id 7; DAT_803bb384/470 bank identities; ptcl00.ptl emitter bank loader; 3D weapon meshes |

**Trace status update (2026-07-03, (bc)):** T9 (knockback magnitude) is **no longer trace-blocked**
— it was found statically in the DOL as strength-indexed tables (DAT_802dd8a0/DAT_802d3664), and
movement physics turned out to be per-borg data-driven (pl####data.bin), not the "unfindable global
constants" §s concluded. **Further re-digs (2026-07-03, (bd)) shrank the trace-blocked list again:** **T1** command resolve
is now mostly STATIC — the input-bit→command-type/subtype resolver is DERIVED (only the physical
pad-button↔bit label needs a further static dig, not a trace). **Combat SE ids** are MAPPED (11
events → real ids); wiring is PENDING an SE-bank asset extraction (static, from the AFS), not a
trace. **T8** status per-id semantics is CONFIRMED genuinely trace-blocked (the id is an
immunity/bone index, not a behavior selector — honest negative). So the true remaining
Dolphin-trace unblocks are **T3** (burst meter fill) and **T8** (status catalog); **T2** melee
contexts and knockback-magnitude PORTING are static-but-deferred (scale/strength-source digs).

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
| Damage formula (18-stage) | DONE (2026-07-05: guard/40 data rule, CPU halvings, force-gauge ratio, post-hit-HP-index fix all wired — T1/T2/T4) | damageFormula.ts | zz_003cd5c_ @0x8003cd5c (ah) | level floats +0xc4/+0xb4 init (ak, still honestly unfound); step-17 +0x5e0&0x4000000 documented NOT REPRESENTABLE (no port field for +0x5e0 at all) |
| Type matrix 20×20 | DONE | typeDamage.ts | 802c5d60 + remap 802f2e28 (l/w) | — |
| Combo falloff (resistance) | DONE | damageFormula comboRankScale | DAT_802c7ca0 step 16 (ah) | none — do NOT add a 2nd layer (U) |
| Friendly fire ×0.25 | DONE | damageFormula sameTeam | step 18 (ah/o) | tests only (ATK-014 ✓) |
| Guard/40 data rule | **DONE (2026-07-05, T1)** | damageFormula.ts victimStatusImmunityA gate, combat.ts applyHit | zz_003cd5c_ chunk_0004.c:6814-6817; victim mask = pldata+0xa8 (movementData.ts statusImmunityMasksForBorgId) | — (retired the old blockDivisorActive caller-flag stand-in) |
| Gauge stagger (down/balance) | DONE | gauges.ts + applyHit | (ag)/(ah)/(s) | — |
| Knockback **direction** | DONE (mode 1) + yaw trim (T8, 2026-07-05) | physics/knockback.ts, combat.ts (angleTrimByteToBam16 now fed a real value) | zz_00300bc_ (p); trim bytes +0x14/+0x15 (T8) | modes 0/2/3/4 need muzzle/camera vectors |
| Knockback **magnitude** | **WIRED (2026-07-05, T6)** — ground/launch table selection + real per-frame decel/gravity integration | gauges.ts knockbackGroundSpeedForRecord/knockbackScaleRatio, combat.ts applyHit, movement.ts reaction-integration branch | DAT_802dd8a0[idx]=idx*7 (zz_005ec20_) vs     DAT_802d3664[idx]=(idx+1)*8 (FUN_8005ed38), decel -speed/20 / -0.1, gravity -1.2 (T6) | T5 scale-ratio
    WIRED via `tierSizeScale()` (2026-07-05); per-borg reaction-anim LENGTHS wired fleet-partial
    (111/208 ground + 175/208 launch DERIVED via `data/reactionAnimLengths.json`) |
| Reaction ANIM-GATED release | **MECHANISM WIRED, VALUE TUNED-fallback (2026-07-05, T6)** | combat.ts reactionAnimLengthFrames/enterDown/stepActionState | actor+0x1d0e completion flag (T6) | no per-borg reaction-clip length export exists in this port yet — single-seam fallback, ready for real data |
| B/X contextual resolve | **type resolver IMPLEMENTED (2a08a35c)** | command.ts resolveCommandType() | tester priority FUN_800699d8:228-238 (bd) | wire into stepAttacks (ATK-003); subtype+pad-button binding still need state/pad-decode |
| Melee contexts (5-way) | schema | movementContextOf | subtype +0x586; wiki 5-context (av) | trace T2 |
| Ammo/refill (3 weapon cells) | DONE (values extracted) | ammo.selftest, combat.ts | zz_006dbe0_/006dcc0_/006de10_ (ai/aw) | X-attack→cell-1 (survey UI #2); types 2/3 = dead (ax) |
| Penetration (none/borgs/total) | data (moveProperties) | borgMoveProperties.json | wiki (aw) + rehit chunk_0013 (O) | trace T6 to confirm engine gate |
| Projectile solidity/PvP | data + BLOCKED | moveProperties | shape table 0x802da740 = NOT pvp (at) | trace T5 |
| Hyper / Power Burst | **SIDE-WIDE + ally-passthrough WIRED (2026-07-05, T3)** | burst.ts, battle.ts activateSideWideBurst/drainPowerBursts, combat.ts burstAllyPassthroughBlocks | +0x6fb/+0x6fc, zz_005b2b8_ (aj/S); ally-passthrough zz_002fd7c_ (T3) | burst-END side timer (+0x10c/+0x10e=600) clear site still trace-gated — port ends the whole side together off the metered presser's own meter instead |
| Fusion | data + shell (ATK-018) | fusion-pairs JSON | pair table 0x802d352c (aj) | trace T3 (co-op control split) |
| Statuses (id/timer/immunity) | framework DERIVED (bd), catalog T8-blocked | status.ts | +0x71a=immunity-idx+bone-idx (NOT behavior-selector); tick FUN_8005a378 id-agnostic (bd) | port isImmune/i-frames/hitstun; per-id wiki behaviors genuinely need T8 trace |
| Hit-inflicted status (slow/haste/freeze/grow-shrink) | **DONE (2026-07-04)** | combat.ts applyHitInflictedStatus/stepHitStatus, timescale.ts statusTimescale | resolve_hitbox_target_effects_and_damage @0x8002e2a8 (chunk_0003.c:7621-8157) | — (separate mechanism from the +0x71a statusId shell above) |
| Hit-impact effect selection (record impactEffectId u8+0x09) | **DECODED+WIRED end-to-end incl. texId hop (2026-07-04, impact-effect-id-decode-2026-07-04.md + ptl-format-notes-2026-07-04.md)** | applyHit/stepProjectiles carry the id; battleScene.ts spawnHitFx renders the REAL bank meshes (spawnBankFx + efctBankMeshes.json from scripts/gen-ptl-cell-map.mjs; sprite stand-ins kept only as fallbacks; lifetimes/curves/counts/meshes/colors/blends DERIVED, curve linearization + scatter + yaw heuristic TUNED) | chunk_0003.c:8087-8156 → zz_0019550_ @0x80019550 → table 0x802c7ed0 → variant handlers + keyframe tracks → zz_0006fb4_ @80006fb4: texId = scene_data JOBJDesc index of efct00_mdl.arc (=efct.pzz member1, bank zz_0042954_/zz_0006c88_) | locate subVariant (+0x12) reader (ids 2-7 palette?); matAnim AOBJ color tracks |
| Hero X tier-buff (STAR/PLANET HERO ramming dash) | **DONE (2026-07-04)** | combat.ts applyHeroXBuff/startSpecialAttack | zz_011230c_/FUN_8010f790 (chunk_0031.c:576-617/chunk_0030.c:4004-4026) | — |
| Vampire lifesteal | **PORTED (aef234f1)** | combat.ts steal+bleed, wired | steal chunk_0003.c:7982/apply 6318/bleed chunk_0006.c:7900 | done: steal=dmg/2 cap@maxHP + 1HP/30f bleed, 47/47 test |
| Nurse heal | **HP-write ABSENT (ay)** | ATK-019 shell | table 0x802d1130 (ax); no +0x1c6 write reachable | Dolphin-trace +0x1c6 on healed ally |
| Mash extra hits | shell (ATK-017) | constants MASH | +0x550 cap 4 (T/ax) | trace consumer |
| Contact damage | scaffold (ATK-006) | disabled | per-borg authored (am/av) | trace T2 stomp |
| Levels | DONE (row=byte+2, ay) | sourceBorgStats.ts | row=levelByte+2 (av/aw, 200/203) | NO in-battle EXP system exists (be) — level is save-stored; **T5 decode (2026-07-05) resolves the +0x3ec conflict: it IS the LEVEL byte (HP/ammo row + force cost + UI), NOT a size/scale class — size-scale floats are the +0xb4/+0xc4 chain driven by the param-tier table** (`combat-feel-gaps-decode-2026-07-05.md:109`); 3 non-normal outliers open |
| Lock-on target state | PORTED (source-shaped) | combat.ts refresh/sourceSwitch*, battle.ts activeSourceTargetUid | zz_006b450_, FUN_8006b850/FUN_8006ba60, actor +0x502/+0x508/+0x73d/+0x73e; null-target acquisition uses 3D squared-distance nearest with later equal-distance ties | trace still useful for exact 2P pairing / ally-support consumers |

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
- Stage collision: triangle mesh from STIH, present on 40/40 stages (18 base stages verified `verified-visual-and-collision` from on-disc hit0XX/hit1XX/hitffX bins; 22 st2x/st4x family variants `verified-visual-and-collision-derived` — they reuse their base st0x arena's hit0XX.bin triplet byte-identically, sha1-verified, since no hit2XX/hit4XX exists on disc; research/decomp/challenge-stage-naming-2026-07-05.md §1.2. The STIH cell X-column-major transpose was fixed 2026-07-05 commit 9f7ab8ea). Zero stages on rect-bounds fallback.

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

**as_icon (battle HUD, not used):** `as_icon.tpl` (`user-data/GG4E/afs_data/root/as_icon.tpl`,
64x64, exported at `apps/game/public/ui/tpl/as_icon/image_00_CI8.png`) is a small circular
icon/badge. The HUD asset manifest (`apps/game/public/ui/hud/manifest.json`) marks its
battle-HUD role LOW-CONFIDENCE because it was never actually seen occupying a slot in either
in-battle capture (`challenge-8-in-battle-hud.png` normal state, `challenge-9-battle-critical-hp.png`
critical state) — every HUD element visible in those two frames is already accounted for by
either a real asset (font glyphs, `faceMarkerRoundel`) or measured vector geometry (energy bars,
HP ring, burst gear, X/B discs), leaving no unexplained gap the icon could be filling. Its
strongest attested role is elsewhere: it IS wired as the real memory-card/Slot-A icon on
Load Box Data (`LoadBoxData.ts`), which is a confirmed, capture-backed placement for the same
texture. Forcing it into the battle HUD without a capture showing it there would be exactly the
kind of unverified guess this port tries to avoid — asset reuse across screens is common in the
original game, but reuse is not evidence of reuse *here*. It stays unwired in BattleHud.ts until
a capture (or a decoded `comhit.bin`/layout table — already ruled out as a HUD schema, see
HUD-FIDELITY-PLAN.md's 2026-07-02 addendum) shows it actually on-screen during battle.

**Controls (adapter.ts):** A/B/X/Y/dash/lock all bound. L/R target-switch now maps to the two
source request bytes (+0x73c = 3/2; browser Q=prev, R/Tab=next). Gaps vs (ao): double-tap evade
(Shift stand-in), air recovery (missing, W14). Z target selection is now modeled as source-shaped
hold/release requests (+0x73c = 5/4) that select an ally while held and restore the retained enemy
on release; partner charge/power-up behavior is still untraced. B/X/Y contextual behavior blocked
on traces T1/T3.

---

## 4. Challenge flow → source

Port: `packages/missions/src/challenge*.ts`. ROM: (ae)/(af), challenge-flow-evidence.md.

| Feature | Status | Note |
|---|---|---|
| Stage rotation (zz_0196dac_) | DERIVED (2026-07-05) | 11-entry pool, reroll-while-equal (matches (ae)). `[0x1d]` rand%3 family roll (st0x/st2x/st4x) now fully wired end-to-end: `stageIdForBattleConfig` (combat-config.ts) resolves the family-encoded id from `meta.stageByte`/`stageSubtable` and falls back to the base build when no family exists (st06/st07/st08/st0d/st0f/st10/st11) or the catalog lacks the export; 22 st2x/st4x family folders verified exported with real (non-degenerate) collision, spot-checked st2c+st4c. Authentic arena names (STAGE_ARENA_NAMES, keyed by stage byte, in challenge-reference.ts) added and surfaced in BattleIntro.ts; 18/18 Versus-select names covered, name-id→texture-row binding corroborated 17/17 via story/wiki cross-check but NOT pixel-traced in Dolphin (residual caveat, see challenge-stage-naming-2026-07-05.md §2.6). Selfcheck extended: `packages/missions/src/selfcheck.ts` (name coverage + seeded family-roll distribution hits all 3 families) and `scripts/selfcheck-challenge-stages.mjs` (st2c/st4c load real collision + battle sim). |
| Team generation (build_challenge_battle_setup) | DONE (structure) | floor(cost*2/3) charge exact; tables now cross-checked vs DOL extract (2026-07-03) |
| Battle counts 5/10/15, energy 1500/2000/2500 | DONE | cross-checked |
| Timer frozen (18000, [0x50]=1) | DONE | — |
| Win/lose/draw judge (zz_00297c8_ mask) | **DONE (commit 3f66777b)** | battle.ts evaluateResult ports the per-side destroyed/equality mask model (ae:1763-1787); BattleState.winnerMask (bit0/bit1/3-mutual/4-timeout); mutual destruction resolves 'lose' for the player per FUN_801969a0. battleJudge.selftest 16/16. |
| 3-phase deploy (~36f) | **DONE (2026-07-05, DERIVED)** | constants.ts `DEPLOY` (20/1/15f phases, ally cue 8 from (af)); combat.ts `stepActionState` spawn case tracks phase 0/1/2 by stateTime; `isInvincible` treats spawn state as deploy-lock; smoke 956f→943f (retired 9f post-spawn extra invuln) |
| Kill accounting (zz_002f8dc_) | DONE (2026-07-04) | per-slot kills/costWon credited to the LAST DAMAGER + costLost on the victim's slot (ally cost EXCLUDED — capture-validated); battle.ts accountPendingDefeats. The flat +100/kill feeds only the in-battle team score DAT_80436154, NOT results |
| Results ratios + counters | DERIVED (2026-07-04) | full decode: results-scoring-decode-2026-07-04.md. ATTACK = attack COUNT (+0x404 via zz_008a5d0_), HIT RATIO = +0x408/+0x404, DODGE RATIO = (+0x40c−+0x410)/(+0x40c++0x414). Port telemetry re-keyed to per-player SLOTS (SlotTelemetry, @gf/combat) with ROM increment semantics (aimed-vs-stray split from the attack object's target +0xcc) |
| GRAND TOTAL formula (FUN_800d3260 / zz_00d1d24_) | DERIVED (2026-07-04) | = tier(costWon, DAT_8030e4b8) + tier(costLost, DAT_8030e6a8) + firstStrike×5000 (DAT_80433b58). NO win/lose sign flip. Tables verbatim in scoring.ts (incl. the ROM's 4901→40000 data quirk); WIN-capture validated (6000+1000+0=7000). Run total = Σ grand totals (+0x17e0, can go negative) = accumulateScore |
| Borg GET / Gotcha-Box drop pipeline (zz_018214c_/zz_0182228_) | DERIVED (2026-07-05) | Full decode: items-evidence-inventory-2026-07-05.md. Drop table `DAT_8035b2dc` (197 rows, borgId/partsKind/6 color-variant thresholds) extracted **197/197 byte-exact** vs `research/symbols/eu_borgs_GET_values.csv` by `scripts/extract-borg-get-drop-table.mjs` → `packages/missions/src/data/borgGetDropTable.json` (hard-fails on any mismatch). Pool model + registerKill (+rand 1..16/kill, pl0503 CYBER DEATH DRAGON fusion-credit special case → pl0505+pl0506) + snapshot/restore (lose/abandon revert) + rollDrops (points≥threshold → reset to 0, whole-unit vs random 1..N part) all DERIVED and implemented in `packages/missions/src/getSystem.ts` (seeded-RNG convention, no Math.random). Wired into the Challenge flow only (`apps/game/src/main.ts`): `BattleState.defeats` (additive, `packages/combat/src/types.ts`) exposes victim borgId/colorVariant/killer team+owner per kill from `accountPendingDefeats`; a WON battle registers every enemy kill + rolls drops, a LOSE/abandon reverts to the pre-battle snapshot; pool + collection persisted in `localStorage` (PORT-ISM medium — GCI save-side layout is undocumented, doc §4). `colorVariant` on `BorgRuntime` is a TUNED placeholder (always 0/normal today — the port has no palette-variant spawn pipeline yet). Presentation: minimal GETS overlay (`apps/game/src/ui/screens/Gets.ts`, TUNED/recreated layout — real ascii.tpl font + gets00_mdl backdrop, no per-drop box-open cinematic) shown after Results when drops occurred; skippable via the shared menu-input bus, never blocks the flow. Selfcheck: `packages/missions/src/selfcheck.ts` assertGetSystem (threshold-crossing exact drop, fusion credit, lose-revert byte-exact, points-reset, never-drop borgs pl0503/0507/050f/0513/0615). |

---

## 5. Assets / Animation / Audio / FX → source

Detail in the asset survey (session 2026-07-03) + `research/format-specs/*`, `research/asset-inventory/*`.

- **Models:** static 208/208 (100%); animated bakes 185/208 (89%). 23 unanimated: pl0d/pl0e/pl0f
  families + pl0505, pl0511 — render frozen. Pipeline is offline HSDRaw→Collada (README); TS
  `.arc` parser intentionally stubbed.
- **Animation:** Hermite interpolation HONORED (hsd-anim.ts full FOBJ evaluator; offline bake is
  dense per-frame) — resolves (ar) lead 3. slot→bank is mostly heuristic (`pickAnimBank` label
  regex + PREFERRED_LABELS), with DERIVED anchors idle=g0s0/move=g0s1/dash=g0s2-5/hit=g3/down=g4s0
  (the g4s0 relabel fixed a real special-plays-knockdown bug, (r)). The "33 substitute fallbacks
  across 23 borgs" line is HISTORICAL (pre-override); `borg-animation-action-gaps.md` regenerated
  2026-07-05 shows **0 runtime fallbacks across 208 borgs** — PREFERRED_LABELS overrides are the
  closure, not current loss. State→(group,slot) dispatch table (`zz_004beb8_`): 20 DERIVED_ROM +
  7 INFERRED + 7 UNRESOLVED (4 confirmed-no-anim, 2 matrix-warp blocked, 1 decodable: slot 8 guard).
- **Audio:** BGM (33 tracks) + menu SFX wired and real. Combat SFX = 5 generic `se00_*` samples
  mapped onto 15 events (TUNED); NO ROM per-action table exists (AnimAudioEventLookup is a red
  herring, (v)) — needs a live SE-dispatch trace. **46 per-borg VOICE cues WIRED (commit 4e522cf4):**
  battleVoiceCues plays cue 00 on deploy / cue 01 on death for the local borg (family→group
  DERIVED, cue-role TUNED); validation script 8/8 (roster coverage 208/208). No footstep/land audio.
- **Stages/lighting:** geometry 40/40 visual, collision 40/40 (18 base + 22 DERIVED-shared-base family variants, sha1-verified); lighting/fog fully DERIVED from
  HSD CObj/LObj/FogDesc (all GX_FOG_LIN → exact THREE.Fog).
- **FX:** hit-impact effects are now DERIVED end-to-end (2026-07-04): record impactEffectId
  u8+0x09 → zz_0019550_ → def table 0x802c7ed0 (ids 0..8, 0xff = none) → 4 variant handlers
  with dumped lifetimes + scale/alpha keyframe tracks → texId = efct00_mdl.arc scene_data
  JOBJDesc index (zz_0006fb4_), whose entries are UNTEXTURED vertex-colored GX meshes —
  parsed (scripts/gen-ptl-cell-map.mjs → efctBankMeshes.json, all 157 entries) and rendered
  as real THREE meshes (spawnBankFx), incl. the id-1 burst's real blue/pink per-player rim
  colors (texIds 2/3). Ex-hypothesis "texId→ptcl00.ptl cell" REFUTED
  (ptl-format-notes-2026-07-04.md). NEW (2026-07-04, efct-consumers-decode-2026-07-04.md):
  the OTHER zz_0006fb4_ consumers decoded — launch/muzzle FX family zz_00aedc0_ (9 ids,
  layer table 0x802faef8 + fences 0x802fafd0, all texIds/lifetimes/tracks dumped), the
  projectile-row visual fields of table 0x802d6d68 (+0x00 texId|bank-flags, +0x34 launch-FX
  id; format generalizes to all ~80 shot tables in shotVariantKinds.json), and the
  slow/haste status FX zz_013f300_ (texIds 48/48/49/50 @DAT_80434670 — an animated clock
  with billboard hands + tumbling star ring, pulse 0x222/0x444). The archive's matAnim
  color tracks are now EXTRACTED (89 dobjs; gen-ptl-cell-map.mjs → efctBankMeshes.json
  `anim`) and wired where the ROM consumes them: the muzzle flash is DERIVED (bank texId 35
  + exact id-0 keys + team-frame matAnim tint blue/red) and slow/haste show the DERIVED
  aura for the sim's 900f timers with the pulse-sampled white↔orange / white↔blue matAnim
  colors. Still TUNED: muzzle position/trigger heuristic + remaining sprite-cell effects
  (death/dash/charge/puffs), curve linearization, burst scatter, orientation yaw, aura
  scale (+0x7fc undecoded); projectiles are 2D billboards, not the per-variant bank/weapon
  meshes (texIds documented, not wired).

---

## 6. The port's C-code disambiguation coverage

Of 11,972 decompiled functions (`_index.tsv`): the research has now assigned a concrete
game-logic **role** to **300** functions — **2.51%** (300 / 11,972) — consolidated into the
machine-readable source map `research/decomp/data/identified-functions.json` (one deduped entry
per address; each traces to a `behavior-notes.md` section, an attack-mechanics findings mechanic,
or a 2026-07-03 corpus-analysis cluster, with a confidence tier DERIVED_ROM / INFERRED /
NAMED_ONLY). This supersedes the earlier ~1.2% / 143 estimate: **261 of the 300 are DERIVED_ROM**
(role read directly from decompiled C or raw ROM data), 23 INFERRED, 16 NAMED_ONLY. The 2026-07-03
clusters mapped: actor/AI/FX, menu/sound, physics, SE-dispatch, command resolver, and finally the
fusion pipeline (state machine + co-op sync + pair-table consumer), burst/guard state plumbing,
camera cue→policy, results-stat gathering, and the box/collection acquisition writer. The initial
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
13. ✅ DONE (2026-07-05) — **T9** knockback magnitude PORTED: strength-indexed tables
    DAT_802dd8a0[idx]=idx*7 / DAT_802d3664[idx]=(idx+1)*8, ground-vs-launch selection per hit,
    real per-frame decel/gravity integration in movement.ts. See §0/§1.
14. **T5/T6** projectile solidity/penetration engine gate (moveProperties has the taxonomy).
15. **T8** status-id semantics; **T2** melee contexts; SE-dispatch audio trace; golden-trace
    movement-constant fitting.

Tier A is ~6 self-contained tickets a cheap coding agent can execute now; Tier B is 4 corpus
digs; Tier C needs the controller. Each Tier-C trace has a ready preset in
`scripts/trace-attack-mechanics.mjs` and a scenario in `attack-mechanics-trace-plan.md`.

**Tier D — NEW, added 2026-07-05, now the highest-leverage bucket:** per-family ROM state-machine
porting (`packages/combat/src/rom/*`, tracker in `rom/PORTING.md`). The foundation (actor/physics/
dispatch/stream-vm/state-tables) is done and unit-tested; G RED's X-special is the one family
landed. Remaining: G RED's own B-melee/dash/B-charge actions, then ~30 other families each as a
~0.5-1 session mechanical transcription (read the family's ctor + `FUN_*` phase chain in
`ghidra-export/chunk_*.c`, port per the documented recipe, add a selfcheck). Each family is
independently shippable behind the `romDriver` registry — no risk to borgs not yet ported.
