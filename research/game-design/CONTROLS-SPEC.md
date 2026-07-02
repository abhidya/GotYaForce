# Controls / Mechanics Proof Spec

Purpose: keep the browser controls 1-to-1 with the original where proven, and keep every
unproven mechanic labeled as `UNKNOWN` or `TUNED` until a new proof step upgrades it.

Scope: battle controls, current web bindings, menu actions, lock-on/switch-lock/ally-lock
gaps, jump/fly, dash/step, attack/special, and manual borg switch status.

## Evidence Grades

| Grade | Meaning |
|---|---|
| `CONFIRMED-ASSET` | Visible in an extracted original asset or directly transcribed from one. |
| `CONFIRMED-CODE` | Current browser implementation, not proof of original behavior. |
| `DERIVED` | Mechanism is supported by decompiled C, trace, or generated evidence. |
| `TUNED` | Implemented intentionally, but no original formula/rule is proven. |
| `UNKNOWN` | Not implemented, conflicted, or not proven. Requires next proof step. |

## Evidence Inventory

- Extracted control screen: `apps/game/public/ui/hsd/nwld00_mdl/texture_000_CI8.png`;
  manifest says source `user-data/GG4E/afs_data/root/nwld00_mdl.arc`, 592x400, SHA-1
  `c181852eb9a5dfedd95fc8d550cbab3115569ac2`
  (`apps/game/public/ui/manifest.json:13237-13253`,
  `apps/game/public/ui/provenance.json:20158-20166`). Visual inspection of that texture
  shows Control Stick move, stick-snap step/dodge, A jump, B attack, Y special attack,
  R "lock-on switch", and Z "ally lock-on".
- Existing extracted-note table: `apps/game/UI-FIDELITY-SPEC.md:15-26`. It is useful
  evidence, but it conflicts with the texture for R/Z: the note says R lock-on, Z switch,
  ally lock-on unknown; the texture itself shows R switch-lock and Z ally-lock.
- HUD/UI observations: battle HUD attack/special prompt notes are at
  `apps/game/UI-FIDELITY-SPEC.md:79-84`; the current HUD labels Y special and B attack at
  `apps/game/src/ui/hud/BattleHud.ts:167-187`.
- Current web input adapter: `inputFromKeys()` maps keyboard/gamepad to `PlayerInput`
  in `apps/game/src/sim/adapter.ts:121-170`; `main.ts` captures battle Tab and polls
  pause at `apps/game/src/main.ts:1005-1012` and `apps/game/src/main.ts:1345-1351`.
- Combat API intent shape: `PlayerInput` fields are defined in
  `packages/combat/src/types.ts:11-29`; current comment summary is at
  `packages/combat/src/types.ts:1-4`.
- Battle loop consumption: lock-on/cycle/movement/attacks are wired in
  `packages/combat/src/battle.ts:207-260`; manual switch-borg input is reserved but
  ignored because original proof currently supports death/auto-deploy only.
- Movement mechanics: `stepMovement()` owns lock-relative facing, dash/step, jump,
  air-jump, and fly boost in `packages/combat/src/movement.ts:65-198`.
- Attack mechanics: `acquireLock()`, `cycleLock()`, and `stepAttacks()` live in
  `packages/combat/src/combat.ts:60-121` and `packages/combat/src/combat.ts:311-476`.
- Tuned constants audit: `packages/combat/src/constants.ts:51-82`, `134-174`,
  and `322-335`.
- Decompiled anchors:
  - Borg state dispatch: `zz_005c694_` at `0x8005c694`,
    `research/decomp/ghidra-export/chunk_0007.c:4159-4178`.
  - Transition primitive: `zz_005ec04_` sets `object+0x6fe` and clears local phase
    `+0x544`, `research/decomp/ghidra-export/chunk_0007.c:5529-5538`.
  - Likely active attack handler: `FUN_8005d494` at `0x8005d494` writes
    `object+0x720 = FLOAT_80437448` immediately,
    `research/decomp/ghidra-export/chunk_0007.c:4676-4688`.
  - Target/effect dispatch: `battle_frame_target_action_dispatch` at `0x8002bb14`,
    `research/decomp/ghidra-export/chunk_0003.c:5844-5956`.
  - Hit/effect/damage resolver: `resolve_hitbox_target_effects_and_damage` at
    `0x8002e2a8`, `research/decomp/ghidra-export/chunk_0003.c:7473-7484`.
  - Knockback direction helper: `zz_00300bc_` at `0x800300bc`,
    `research/decomp/ghidra-export/chunk_0003.c:7945` and `:8540-8545`.
  - Swap/death anchors: `cPlayer::ClearSwapControllerTimer(void)` at `0x802807ac`
    and `zz_0281c38_` at `0x80281c38`,
    `research/decomp/index/function-evidence-index.md:56-57`,
    `research/decomp/ghidra-export/chunk_0076.c:3819-3821`,
    `research/decomp/ghidra-export/chunk_0076.c:4844-4897`.

## GC Battle Control Checklist

| Original control | Original action | Current web binding | Current mechanic | Proof grade | Notes / next proof step |
|---|---|---|---|---|---|
| Control Stick | Move | WASD/arrows; gamepad left stick axes 0/1 | `moveX/moveZ` feed `stepMovement()`; while locked, forward/back moves toward/away from target and diagonals circle-strafe | `CONFIRMED-ASSET` input, `CONFIRMED-CODE` web, movement semantics partly `TUNED` | Texture proves "move". Lock-relative movement is current code (`movement.ts:8-11`, `217-244`) and trace notes support default lock-relative play (`research/decomp/behavior-notes.md:1491-1508`). Still trace exact original stick vector handling. |
| Fast stick snap | Step/dodge in pushed direction | ShiftLeft/ShiftRight; gamepad buttons 5 or 7; pure left/right stick while locked auto-dodges | Sets `dashActive`, `dash`, and i-frames; dashes in resolved stick direction | `CONFIRMED-ASSET` input, `TUNED` mechanics | Texture text says to snap/quickly move stick for step/dodge. Current code is `movement.ts:86-104` and pure-lateral auto-dodge is `movement.ts:237-244`. Constants are tuned (`constants.ts:156-174`). Decomp audit found no dash/step/dodge state (`behavior-notes.md:982-991`). Next: trace left/right dodge-dash position and `object+0x6fe`. |
| A | Jump | Space or J; gamepad button 0 | Rising edge sets vertical velocity; air-jumps use `airJumps`; flyer holding jump spends boost fuel and enters fly | `CONFIRMED-ASSET` input, `TUNED` velocity/boost values | Texture proves A jump. Current mapping is `adapter.ts:139` and `:153`; mechanics are `movement.ts:126-198`; constants are `constants.ts:134-153`. Trace notes say tap A = jump and hold A = fly/boost (`behavior-notes.md:1500`). Exact original vertical field/velocity remains unknown (`behavior-notes.md:995-1000`, `1677-1684`). |
| B | Attack | K or X; gamepad button 1 or 2 | B resolves per-borg primary action: melee if melee-primary/available, shot if shot-primary/available; shot consumes ammo/reload and may home to lock target | `CONFIRMED-ASSET` input, action semantics `TUNED` | Texture proves B attack. Current mapping is `adapter.ts:140` and `:154`; attack code is `combat.ts:368-388`, melee start `:439-446`, projectile spawn `:448-476`. Per-borg action profiles are asset-backed but tuned, not decoded hit-bin semantics (`packages/combat/src/data/actionProfiles.json:9`, `packages/combat/src/actionProfiles.ts:103-129`). Next: one close B and one ranged B Dolphin trace. |
| Y | Special attack | L or Y; gamepad button 3 | Starts special if cooldown is clear; current generic implementation is radial/AoE burst with cooldown and action lock | `CONFIRMED-ASSET` input, `TUNED` mechanic | Texture proves Y special. Current mapping is `adapter.ts:141` and `:155`; special path is `combat.ts:333-366`; constants are `constants.ts:245-253`. Current HUD labels special as X (`BattleHud.ts:167-187`) while the control texture labels Y, so HUD prompt vs controls is `UNKNOWN` until an in-battle control prompt capture is checked. |
| R | Lock-on switch (texture label: `ロックオン きりかえ`) | R or Tab; gamepad buttons 5 or 7 stand in for GC R | Human borgs auto-acquire locks; each R PRESS (edge-triggered) cycles to the next enemy by distance — never dead borgs, never self, never allies. The locked enemy is marked with a continuously spinning red ring reticle | Original input `CONFIRMED-ASSET`; current binding + enemy-only spinning reticle `CONFIRMED-CODE`; cycle algorithm `TUNED` | Texture shows R is switch-lock, not generic lock-on. Current code keeps Start/button 9 for pause and binds switch-lock to R-like buttons (`adapter.ts:147-148`, `:163`); the press latch lives in `battle.ts:242-262` and cycling in `combat.ts:142-153`. The reticle renders only over the local human's `lockTarget` and follows borg switches/deaths (`battleScene.ts:283-318`, `:542-`). Decomp search concluded no manual scan-select enemy-lock system exists (`behavior-notes.md:781-856`), so browser lock range/cone are tuned (`constants.ts:322-335`). Next: trace R in original battle to refine cycling order and camera behavior. |
| Z | Ally lock-on (texture label: `みかた ロックオン`) | Z; gamepad left shoulder (button 4) stand-in | Each Z PRESS (edge-triggered) acquires the nearest same-team ally, or cycles allies if one is already locked; records a separate `allyLockTarget`, marked with a GREEN overhead arrow (different shape + color from the red enemy reticle); does not redirect attacks or trigger ally charge/power-up yet | `CONFIRMED-ASSET` input; current binding + distinct ally marker `CONFIRMED-CODE`; target selection `TUNED`; charge behavior `UNKNOWN` | Texture proves Z ally-lock exists as a command label. Current code carries this separately from enemy lock (`adapter.ts:149`, `:165`, `battle.ts:248-267`, `combat.ts:155-183`) so future charge/camera work has state to attach to; the ally marker is the extracted `arrow_mdl` geometry tinted green (`battleScene.ts:649-`). Next: trace Z with ally visible to identify original target choice, camera behavior, and charge/power-up side effects. |
| Start | Pause / advance / skip, depending screen | Battle pause: Escape, Enter, gamepad button 9; Load Box skip currently S | Battle pause opens `PauseMenu`; menus use screen-specific handlers | Original battle binding `UNKNOWN`; current `CONFIRMED-CODE` | UI notes prove Start advances boot/title and Load Box has START=SKIP (`UI-FIDELITY-SPEC.md:59`, `:67-68`). Current pause poll is `main.ts:1345-1351`; Load Box keyboard skip is `LoadBoxData.ts:52-59`. Next: capture original pause/control screen for battle Start semantics. |
| Manual borg switch | Unknown / not on control texture | none | Inactive; active borg changes only through death/auto-deploy | Current `CONFIRMED-CODE`, original manual input `UNKNOWN` | The browser E-key retirement/requeue path was removed because the texture shows no manual switch and decomp has death/swap timer anchors, not a proven manual switch button (`function-evidence-index.md:56-57`, `chunk_0076.c:3819-3821`, `:4844-4897`). Next: trace `0x802807ac`/`0x80281c38` while pressing candidate buttons and while a borg dies. |

## Current Web Binding Matrix

These are current implementation facts, not claims about the original:

| Intent | Keyboard | Gamepad | Code |
|---|---|---|---|
| Move | WASD or arrows | axes 0/1 | `apps/game/src/sim/adapter.ts:130-138`, `:147-151` |
| Jump | Space or J | button 0 | `adapter.ts:139`, `:153` |
| Attack | K or X | buttons 1 or 2 | `adapter.ts:140`, `:154` |
| Special | L or Y | button 3 | `adapter.ts:141`, `:155` |
| Dash | Shift | none; pure lateral stick while locked auto-dodges | `adapter.ts:142`; `movement.ts:237-244` |
| Lock request | U | button 6 | `adapter.ts:147`, `:162` |
| Switch-lock (cycle enemy) | R or Tab | buttons 5 or 7 | `adapter.ts:148`, `:163`; edge-trigger latch `battle.ts:242-262`; Tab focus suppression in battle at `main.ts` |
| Ally-lock | Z | button 4 stand-in | `adapter.ts:149`, `:165`; edge-trigger + target state `battle.ts:248-267`, `combat.ts:155-183` |
| Switch borg | none | none | `adapter.ts:145`; no battle-core consumer |
| Pause | Escape or Enter | button 9 | `main.ts:1345-1351` |

Known mismatches:

- Existing note says `Space / A` for jump and `J / X` for attack
  (`UI-FIDELITY-SPEC.md:21-22`), but current code maps J to jump and K/X to attack
  (`adapter.ts:139-140`).
- Existing note says R lock-on and Z switch-lock (`UI-FIDELITY-SPEC.md:24-26`), but
  the actual texture shows R switch-lock and Z ally-lock.
- Current switch-lock is still a web stand-in for GC R; exact GameCube trigger semantics
  need a live trace before calling the binding final.
- Current HUD labels special as Y (`BattleHud.ts:186`), matching the control texture.

## Menu Action Checklist

| Menu action | Original evidence | Current keyboard action | Code | Grade |
|---|---|---|---|---|
| Move selection / choose | Stick/D-pad implied by bottom legends and main-menu note | Main menu arrows/WASD; many screens arrows | Main menu `MainMenu.ts:181-196`; select screens `SelectDifficulty.ts:137-153`, `SelectPlayers.ts:127-141` | `CONFIRMED-CODE`; original detailed input `UNKNOWN` |
| Confirm | A on VS/briefing/menu legends | Enter, Space, or A-like key depending screen | Main menu `MainMenu.ts:195-196`; difficulty `SelectDifficulty.ts:150`; players `SelectPlayers.ts:138`; briefing `BattleIntro.ts:75-76`; results `Results.ts:97` | `CONFIRMED-ASSET` for A confirm in captured notes (`UI-FIDELITY-SPEC.md:77`), current `CONFIRMED-CODE` |
| Back | B on VS/briefing legends | Escape or B-like key | difficulty `SelectDifficulty.ts:153`; players `SelectPlayers.ts:141`; load box `LoadBoxData.ts:58-59`; briefing `BattleIntro.ts:78-79`; select force `SelectForce.ts:90-91` | `CONFIRMED-ASSET` for B back in captured notes (`UI-FIDELITY-SPEC.md:77`), current `CONFIRMED-CODE` |
| Edit force | X on Select Force | X | Original note says `X = EDIT FORCE` (`UI-FIDELITY-SPEC.md:60`); current handler `SelectForce.ts:87-88` | `CONFIRMED-ASSET` note, current `CONFIRMED-CODE` |
| Load Box skip | START | Enter or S | Original note says START=SKIP (`UI-FIDELITY-SPEC.md:59`); current handler `LoadBoxData.ts:55-56` | Original `CONFIRMED-ASSET` note, current web stand-in `CONFIRMED-CODE` |
| Pause menu select/resume/quit | Unknown original battle pause layout | Arrows select, Enter/A activate, Escape resume | `PauseMenu.ts:80-92` | `CONFIRMED-CODE`; original `UNKNOWN` |

## Mechanics Proof Notes

### Lock-On, Switch-Lock, Ally-Lock

- Current browser lock-on is intentionally not a ROM-derived formula. `combat.ts` documents
  that the decomp search found no button-triggered scan-and-select enemy-lock mechanic
  (`packages/combat/src/combat.ts:60-75`).
- Human-controlled borgs auto-acquire a target if none is valid; `switchLock` cycles targets.
  R and Z are EDGE-TRIGGERED via 0/1 press latches in `cooldowns` (`switchLockHeld` /
  `allyLockHeld`, same pattern as movement's `jumpHeld`; skipped by `stepCooldowns`), so
  holding the button cycles exactly once per press (`packages/combat/src/battle.ts:242-267`).
- The tuned enemy acquisition heuristic is nearest enemy in range/cone
  (`packages/combat/src/combat.ts:119-153`, `packages/combat/src/constants.ts:322-335`).
- Marker rendering (browser, `apps/game/src/sim/battleScene.ts:283-318`): the enemy reticle —
  a continuously spinning red ring with inward blue triangles, a TUNED canvas stand-in
  transcribed from `apps/game/reference/captures/challenge-8-in-battle-hud.png` (no extracted
  reticle asset exists yet) — renders ONLY over the local HUMAN player's `lockTarget` and only
  when that target is a live enemy (`team !== self.team`, `uid !== self.uid`). The Z ally lock
  renders as a GREEN `arrow_mdl` overhead arrow, a deliberately different shape and color.
  Historical self-marking bug: the old single orange marker trusted the presentation focus uid
  (which falls back to a CPU ally while the player respawns) / "any human-owned borg" with no
  ownership or team guard, so it could read as marking the player's own team.
- Decompiled target globals are hit-reactive bookkeeping, not proof of manual lock:
  `battle_frame_target_action_dispatch` clears `DAT_803b06a8` per frame
  (`chunk_0003.c:5844-5956`), and the damage resolver writes target reaction fields
  (`chunk_0003.c:7473-7484`, `:7718`). Behavior note conclusion is
  `research/decomp/behavior-notes.md:781-856`.
- Ally-lock is still a gameplay gap: the asset says Z is ally-lock, and current code now
  records a separate same-team `allyLockTarget` (edge-triggered acquire-nearest, then cycle
  on repeat presses, `packages/combat/src/combat.ts:155-183`) with a distinct green marker,
  but the original charge/power-up behavior remains untraced. Enemy lock targets remain
  enemy-only.

### Jump/Fly

- Control texture proves A jump; behavior notes corroborate tap A jump and hold A fly/boost
  (`research/decomp/behavior-notes.md:1500`).
- Current code is edge-triggered (`jumpHeld` latch), supports air jumps, and supports flyer
  boost fuel (`packages/combat/src/movement.ts:126-198`).
- `JUMP.VELOCITY`, `GRAVITY`, `BOOST_THRUST`, `BOOST_MAX_RISE`, and fuel are all `TUNED`
  (`packages/combat/src/constants.ts:134-153`). Behavior notes say the vertical field/constant
  remains unresolved (`behavior-notes.md:995-1000`, `:1677-1684`).
- Next proof step: use the jump/fly watch set in
  `research/traces/GG4E/breakpoints-watchpoints.json:427-477` and capture actor vertical
  position/velocity while tapping A and holding A.

### Dash/Step

- Control texture proves stick-snap step/dodge, not Shift. Shift is only a web affordance.
- Current implementation starts dash from explicit `input.dash` or pure lateral lock-relative
  stick (`packages/combat/src/movement.ts:86-104`, `:237-244`).
- All dash numeric values are `TUNED`; no original dash state was found in the corpus pass
  (`packages/combat/src/constants.ts:156-174`, `research/decomp/behavior-notes.md:982-991`).
- Next proof step: trace left/right full-stick samples as dash events, using the golden recipe
  guidance in `research/traces/GG4E/golden-trace-runbook.md:41-57`.

### Attack/Special

- Control texture proves B attack and Y special. Current web code maps B-like attack to
  K/X and special to L/Y (`adapter.ts:139-155`).
- Current B primary action is per-borg and asset-backed but still `TUNED`, not decoded from
  hit-bin move semantics (`packages/combat/src/data/actionProfiles.json:9`,
  `packages/combat/src/actionProfiles.ts:103-129`).
- Current special is a generic cooldown-gated burst (`packages/combat/src/combat.ts:333-366`);
  exact original special-per-borg rule is `UNKNOWN/TUNED`.
- Animation asset labels support visual slots for jump/dash/attack/special, but do not prove
  the gameplay rule by themselves: see `research/animation-actions/borg-action-assets.md:57-62`
  and `research/format-specs/borg-animation-banks.md:66`, `:176-188`.
- Decompiled C proves a real action state machine exists on `object+0x6fe`, not `+0x544`
  (`chunk_0007.c:4159-4178`, `:5529-5538`; summary in
  `research/decomp/behavior-notes.md:1106-1223`). It also proves `FUN_8005d494` re-arms
  invincibility at `object+0x720` each call (`chunk_0007.c:4676-4688`), but the exact
  B/Y action mapping to state indices still requires live input correlation.

### Manual Borg Switch

- Current browser has no active manual switch path (`adapter.ts:145`; no battle-core consumer).
- Original control texture does not show a manual borg-switch button.
- Decompiled swap evidence currently supports death/swap timer flow, not a manual input:
  `cPlayer::ClearSwapControllerTimer(void)` at `0x802807ac` and `zz_0281c38_` at
  `0x80281c38` are indexed (`function-evidence-index.md:56-57`) and chunked
  (`chunk_0076.c:3819-3821`, `:4844-4897`).
- Status: keep manual switch labeled `UNKNOWN` until a trace proves original button behavior.
  The browser now keeps Challenge deploy flow death-driven instead of inventing retirement
  and requeue behavior.

### Power-Up / Ally Charge

- Current browser specials are still generic/tuned, not the original power-up or ally-charge
  system (`packages/combat/src/combat.ts:333-366`).
- No exact C proof currently ties Z ally-lock directly to charge attacks. Z target selection and
  the param-tier power system must stay separate until a trace links them.
- The recovered C proves a tiered actor parameter system, but not enough browser-safe mapping
  yet: `reset_actor_param_tier` at `0x80068138` initializes `actor+0x74a`, `+0x74e`,
  and `+0x750`; `apply_actor_param_tier_delta_63` clamps deltas, accumulates `+0x74e`,
  and sets `actor+0x750 = 900`; `refresh_actor_param_tier_table` writes table-backed
  parameters into `actor+0xb8`, `+0x1dd0`, and `+0x5f8`
  (`research/decomp/ghidra-export/chunk_0008.c:4389-4518`).
- Current browser now carries the proven `actor+0x74a/+0x74e/+0x750` runtime state and helper
  math in `packages/combat/src/paramTier.ts`, initializes it on deploy, and selfchecks reset
  plus `[-0x3f,0x3f]` / `[-0x7f,0x7f]` clamp behavior against the recovered C.
- Status: do not fake ally charge/power-up yet. Remaining import requires identifying which
  target actions call `apply_actor_param_tier_delta_63`, what `DAT_8043612c[slot]` means, how
  the timer decays, and how tier-table values map to browser `BorgProfile`
  attack/defense/speed/shot fields.

### Challenge Stage Variants

- Current browser Challenge stage selection preserves the three selector bytes but still
  draws `stageVariant` from a recovered per-stage variant-count table
  (`packages/missions/src/challenge-reference.ts`).
- The cleaned C sidecar proves the original does not always use hardcoded 4: after selecting
  `stage_id` and `stage_subtable`, `Challenge_SelectStage_80196dac` calls
  `StageVariantCount_Lookup_800825bc(stage_id)`, guards zero to one, then modulo-selects
  `stage_variant` (`research/decomp/ghidra-export/challenge_deobfuscated.c:136-156`).
- Status: selector count is ported. The lookup body returns
  `*(u32*)(&DAT_802da5d0 + stage_id*4)` (`research/decomp/ghidra-export/chunk_0012.c:5777-5782`);
  `packages/missions/src/challenge-reference.ts` carries the extracted table, including
  `st09 = 5`. Official Challenge stage bytes all resolve to count `4`, so this removes the
  literal hardcode without changing those battle picks.

## Next Proof Steps

1. R/Z/ally-lock trace: with two enemies and one ally visible, press R and Z separately.
   Watch PAD state, current actor target fields, camera target, `object+0x6fe`, and the
   target globals around `DAT_803b06a8`. Start from the lock-on watch group at
   `research/traces/GG4E/breakpoints-watchpoints.json:331-394`.
2. Jump/fly trace: tap A, air-jump, then hold A on a flyer. Capture the real vertical field,
   grounded flag, boost/fuel field, and `object+0x6fe`; use
   `research/traces/GG4E/breakpoints-watchpoints.json:427-477`.
3. Dash/step trace: full-stick left/right under lock. Capture position deltas and state index;
   treat left/right as dash events per `research/traces/GG4E/golden-trace-runbook.md:41-57`.
4. B/Y trace: one close-range B, one ranged B, one Y. Correlate PAD bits to `object+0x6fe`,
   `FUN_8005d494`, projectile spawn, cooldown/ammo fields, and animation request helper calls.
5. Manual borg switch trace: press candidate buttons and separately let a borg die while
   watching `0x802807ac` / `0x80281c38` plus active borg slot/player state. Until then,
   manual switch stays inactive in the browser battle core.
6. Power-up/ally-charge trace: trigger ally charge and any power-up pickup while watching
   `0x80068138`, `0x800681e4`, `DAT_8043612c[slot]`, and actor fields `+0x74a/+0x74e/+0x750`.
7. Stage render variants: decode/import the `stc##_mdl.arz` family before claiming visual
   variant rendering is 1:1. The selector count is ported; the rendered variant assets are not.
