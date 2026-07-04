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
  are static, not dynamic.
- **Slice 6 title/desk intro LANDED**: TitleIntro.ts mounts the real tl00 scene + G-Red
  playing the recovered desk sequence (anim ids 0,1,6,3,4,7 = g0 slots idle/move/jump_takeoff/
  dash_back/dash_left/jump_land), press-start → menu (set_global_menu_mode(9) model); slot-1
  actor left undecoded per the index note; asset-failure falls back to CSS. UI scenes
  re-exported WITH textures (813 models, 256 textures — the blank-texture fix applied).
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
floor height/spawn placement). Detectors now point at the real path. The true collision gap
is 22/40 stages missing source hit bins, not runtime wiring.

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
6. The `+0x3ec` byte identity: (ak) reads it as level, (be) as size/scale class — reconcile which
   field drives the stat row (the level-row port is validated vs wiki and unaffected either way).
7. The 3 non-normal-schedule borgs (pl0400/pl0507/pl0d01) — per-level HP off the row grid.
8. g4s0 `special_s0`→`down_s0` anim relabel (asset re-bake, separate worktree).

Everything else in the tables below is DONE or an intentional CHECKED_CLOSED. The corpus is otherwise
~97% HAL Sysdolphin / SDK / codec middleware with no game-logic role to assign.

---

## 0. Executive scorecard

| Subsystem | 1:1 coverage | Gating blocker to finish |
|---|---|---|
| Combat: damage formula | ~90% DERIVED | actor level-float init (+0xc4/+0xb4); guard /40 gate |
| Combat: gauges/stagger | ~95% DERIVED | reaction lengths (animation-gated) |
| Combat: knockback direction | DERIVED, ported (mode 1) | modes 0/2/3/4 need sub-object data |
| Combat: knockback **magnitude** | DERIVED (found, bc) — port pending | strength-indexed tables DAT_802dd8a0/DAT_802d3664; port needs scale reconcile |
| Combat: B/X contextual resolver | resolver DERIVED (bd), port upgradeable | fill type/subtype from testers; only pad-bit↔button label needs a dig |
| Combat: ammo/refill | DONE (B cell-0 + X cell-1 wired) | — |
| Combat: projectile penetration | wired OBSERVED_WIKI (borgs/total→persist) | trace T6 confirms engine gate; terrain-penetration + solidity still open |
| Combat: vampire lifesteal | DONE (ported, ay) | — |
| Combat: statuses / hyper / fusion | status framework DERIVED (bd); hyper/fusion shells | status catalog T8-blocked; burst/fusion T3; nurse heal-write not in corpus |
| Physics: movement/jump/dash | DERIVED values found (bc), port TUNED | per-borg data.bin values known — scale-reconcile to port, then swap |
| UI: screens | ~9 real screens | 6 modes are dead menu entries |
| UI: HUD | ~90% (charge✓ cursor✓ X-ammo✓ boost✓ jump✓) | burst meter only (fill data is T3-blocked) |
| Challenge flow | PLAYABLE (verified) + ~85% DERIVED | deploy sub-phases (moot, 36f total already correct) |
| Assets: models (static/anim) | 100% / 89% | 23 unanimated borgs |
| Assets: animation playback | ~88% (dispatch mapped+reconciled, ba/bb) | asset re-bake: relabel g4s0 special_s0→down_s0 (worktree); death/deploy slots unresolved |
| Audio: BGM/menu | ~90% | — |
| Audio: combat/voice | ~85% (voice az; SE ids MAPPED bd, EXTRACTED+WIRED 2026-07-04; **PATH-B per-anim swing audio DECODED+WIRED 2026-07-04**) | real bank samples exported (scripts/export-combat-se.py, 23 files) + wired (shoot/hit/down/dash/jump/spawn/land DERIVED); melee/charge swings now play their ROM-AUTHORED per-anim sounds (actor+0x4e8 sound-event table joined via the anim-descriptor banks — anim-sound-op-decode-2026-07-04.md; 103/103 resolved ladders + 18 air / 2 charge leaves covered, TUNED fallback kept for the rest); death stays TUNED (op-0x0f voice is per-borg table-driven, tables undecoded); voice cue-role TUNED |
| Stages: geometry/lighting | ~90% / ~98% | collision on 22/40 stages |
| FX: particles/projectiles | ~70% | PTL/REF decode; 3D weapon meshes |

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
| Damage formula (18-stage) | DONE (modeled subset) | damageFormula.ts | zz_003cd5c_ @0x8003cd5c (ah) | level floats +0xc4/+0xb4 init (ak); guard /40 (av auto-shield) |
| Type matrix 20×20 | DONE | typeDamage.ts | 802c5d60 + remap 802f2e28 (l/w) | — |
| Combo falloff (resistance) | DONE | damageFormula comboRankScale | DAT_802c7ca0 step 16 (ah) | none — do NOT add a 2nd layer (U) |
| Friendly fire ×0.25 | DONE | damageFormula sameTeam | step 18 (ah/o) | tests only (ATK-014 ✓) |
| Gauge stagger (down/balance) | DONE | gauges.ts + applyHit | (ag)/(ah)/(s) | — |
| Knockback **direction** | DONE (mode 1) | physics/knockback.ts | zz_00300bc_ (p) | modes 0/2/3/4 need muzzle/camera vectors |
| Knockback **magnitude** | DERIVED (found, bc) | constants MELEE/SHOT KNOCKBACK (TUNED, port pending) | DAT_802dd8a0[str]=str*7, DAT_802d3664[str]=(str+1)*8, str=actor+0x702 (bc) | port strength-indexed magnitude (scale-reconcile) — T9 NO LONGER trace-blocked |
| B/X contextual resolve | **type resolver IMPLEMENTED (2a08a35c)** | command.ts resolveCommandType() | tester priority FUN_800699d8:228-238 (bd) | wire into stepAttacks (ATK-003); subtype+pad-button binding still need state/pad-decode |
| Melee contexts (5-way) | schema | movementContextOf | subtype +0x586; wiki 5-context (av) | trace T2 |
| Ammo/refill (3 weapon cells) | DONE (values extracted) | ammo.selftest, combat.ts | zz_006dbe0_/006dcc0_/006de10_ (ai/aw) | X-attack→cell-1 (survey UI #2); types 2/3 = dead (ax) |
| Penetration (none/borgs/total) | data (moveProperties) | borgMoveProperties.json | wiki (aw) + rehit chunk_0013 (O) | trace T6 to confirm engine gate |
| Projectile solidity/PvP | data + BLOCKED | moveProperties | shape table 0x802da740 = NOT pvp (at) | trace T5 |
| Hyper / Power Burst | shell (ATK-011) | burst.ts | +0x6fb/+0x6fc, zz_005b2b8_ (aj/S) | **trace T3** — meter+duration |
| Fusion | data + shell (ATK-018) | fusion-pairs JSON | pair table 0x802d352c (aj) | trace T3 (co-op control split) |
| Statuses (id/timer/immunity) | framework DERIVED (bd), catalog T8-blocked | status.ts | +0x71a=immunity-idx+bone-idx (NOT behavior-selector); tick FUN_8005a378 id-agnostic (bd) | port isImmune/i-frames/hitstun; per-id wiki behaviors genuinely need T8 trace |
| Hit-inflicted status (slow/haste/freeze/grow-shrink) | **DONE (2026-07-04)** | combat.ts applyHitInflictedStatus/stepHitStatus, timescale.ts statusTimescale | resolve_hitbox_target_effects_and_damage @0x8002e2a8 (chunk_0003.c:7621-8157) | — (separate mechanism from the +0x71a statusId shell above) |
| Hero X tier-buff (STAR/PLANET HERO ramming dash) | **DONE (2026-07-04)** | combat.ts applyHeroXBuff/startSpecialAttack | zz_011230c_/FUN_8010f790 (chunk_0031.c:576-617/chunk_0030.c:4004-4026) | — |
| Vampire lifesteal | **PORTED (aef234f1)** | combat.ts steal+bleed, wired | steal chunk_0003.c:7982/apply 6318/bleed chunk_0006.c:7900 | done: steal=dmg/2 cap@maxHP + 1HP/30f bleed, 47/47 test |
| Nurse heal | **HP-write ABSENT (ay)** | ATK-019 shell | table 0x802d1130 (ax); no +0x1c6 write reachable | Dolphin-trace +0x1c6 on healed ally |
| Mash extra hits | shell (ATK-017) | constants MASH | +0x550 cap 4 (T/ax) | trace consumer |
| Contact damage | scaffold (ATK-006) | disabled | per-borg authored (am/av) | trace T2 stomp |
| Levels | DONE (row=byte+2, ay) | sourceBorgStats.ts | row=levelByte+2 (av/aw, 200/203) | NO in-battle EXP system exists (be) — level is save-stored, actor+0x3ec is size/scale class (0-4), CONFLICTS (ak)'s "+0x3ec=level" — reconcile which byte; 3 non-normal outliers open |
| Lock-on target state | PORTED (source-shaped) | combat.ts refresh/sourceSwitch*, battle.ts activeSourceTargetUid | zz_006b450_, FUN_8006b850/FUN_8006ba60, actor +0x502/+0x508/+0x73d/+0x73e | trace still useful for exact 2P initial pairing / ally-support consumers |

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
13. **T9** knockback magnitude (the oldest TUNED debt; not in code).
14. **T5/T6** projectile solidity/penetration engine gate (moveProperties has the taxonomy).
15. **T8** status-id semantics; **T2** melee contexts; SE-dispatch audio trace; golden-trace
    movement-constant fitting.

Tier A is ~6 self-contained tickets a cheap coding agent can execute now; Tier B is 4 corpus
digs; Tier C needs the controller. Each Tier-C trace has a ready preset in
`scripts/trace-attack-mechanics.mjs` and a scenario in `attack-mechanics-trace-plan.md`.
