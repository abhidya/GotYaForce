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
  shows Control Stick move, stick-snap step/dodge, A jump, B attack, X special attack,
  R "lock-on switch", and Z "ally lock-on".
- Existing extracted-note table: `apps/game/UI-FIDELITY-SPEC.md:15-26`. It is useful
  evidence and now matches the texture for B attack, X special, R switch-lock, and Z ally-lock.
- HUD/UI observations: battle HUD attack/special prompt notes are at
  `apps/game/UI-FIDELITY-SPEC.md:79-84`; the current HUD labels X special and B attack at
  `apps/game/src/ui/hud/BattleHud.ts`.
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
- Ignored Dolphin traces under `user-data/dolphin-trace/traces/` now prove the GDB/PAD
  capture path and the corrected post-PADRead injection path through `zz_010d450_`
  normalization: B -> normalized current/pressed `0x00000200`, X -> `0x00000400`,
  Z -> `0x00000010` (`research/traces/GG4E/dolphin-gdb-trace-results.md`). These
  are `gdb-pad-injection` traces, not physical controller captures.
- Static decomp proves `FUN_80056900` copies normalized `DAT_803c727c[port]` through
  `zz_008bbc0_` into `actor+0x5b4`, then derives `actor+0x5bc` pressed edges. The
  `zz_008bbc0_` mask is `0x00ff1f7f`, so it preserves B `0x00000200`, X
  `0x00000400`, and Z `0x00000010`
  (`research/decomp/ghidra-export/chunk_0007.c:228-270`,
  `research/decomp/ghidra-export/chunk_0013.c:2197-2202`).
- Static decomp also found candidate B/X/Z consumers, but not a complete gameplay rule:
  `FUN_8015b0b4` routes X for borg `0x061e` and B for others, `FUN_800e622c` has an
  X pressed-edge transition path, `FUN_801304b8` has borg-gated B and X pressed-edge
  paths, and `FUN_8005a298` is the only focused-pass exact Z `0x10` consumer found so
  far (`research/traces/GG4E/dolphin-gdb-trace-results.md`).
- Direct `boot.dol` pointer-table reads refine two B/X candidates: `zz_00e6048_`
  dispatches `PTR_FUN_803188e8[actor+0x540]`, whose entry 2 is `FUN_800e622c`;
  `FUN_8015ae1c` dispatches `PTR_FUN_803448b0[actor+0x540]`, whose entry 2 is
  `FUN_8015b0b4`. A raw pointer at `0x80335c84` points to `FUN_801304b8`, but the
  dispatch reference for that table is not identified yet.
- Static C also proves two cue arguments inside the `FUN_801304b8` B pressed-edge
  candidate: borg id `0x0106` calls `zz_00f036c_(actor, 0xeb)` and borg id `0x0107`
  calls `zz_00f036c_(actor, 0xaa)`. `zz_00f036c_` is an SFX request wrapper, but
  those cue IDs are not browser gameplay rules until a live trace ties them to PAD,
  action dispatch, and LR caller.
- The same traces still contain no action-state/param-tier/audio correlation for B/X/Z.
  Fresh action traces from `dolphin/right before hit.sav` either filled on hot
  `audio-seq-continue` or timed out with zero input/action hits. Therefore exact B/X
  action-index mapping, Z charge/power-up side effects, and per-action audio cue IDs
  remain unproven.

## GC Battle Control Checklist

| Original control | Original action | Current web binding | Current mechanic | Proof grade | Notes / next proof step |
|---|---|---|---|---|---|
| Control Stick | Move | WASD/arrows; gamepad left stick axes 0/1 | `moveX/moveZ` feed `stepMovement()`; while locked, forward/back moves toward/away from target and diagonals circle-strafe | `CONFIRMED-ASSET` input, `CONFIRMED-CODE` web, movement semantics partly `TUNED` | Texture proves "move". Lock-relative movement is current code (`movement.ts:8-11`, `217-244`) and trace notes support default lock-relative play (`research/decomp/behavior-notes.md:1491-1508`). Still trace exact original stick vector handling. |
| Fast stick snap | Step/dodge in pushed direction | ShiftLeft/ShiftRight; gamepad buttons 5 or 7; pure left/right stick while locked auto-dodges | Sets `dashActive`, `dash`, and i-frames; dashes in resolved stick direction | `CONFIRMED-ASSET` input, `TUNED` mechanics | Texture text says to snap/quickly move stick for step/dodge. Current code is `movement.ts:86-104` and pure-lateral auto-dodge is `movement.ts:237-244`. Constants are tuned (`constants.ts:156-174`). Decomp audit found no dash/step/dodge state (`behavior-notes.md:982-991`). Next: trace left/right dodge-dash position and `object+0x6fe`. |
| A | Jump | Space or J; gamepad button 0 | Rising edge sets vertical velocity; air-jumps use `airJumps`; flyer holding jump spends boost fuel and enters fly | `CONFIRMED-ASSET` input, `TUNED` velocity/boost values | Texture proves A jump. Current mapping is `adapter.ts:139` and `:153`; mechanics are `movement.ts:126-198`; constants are `constants.ts:134-153`. Trace notes say tap A = jump and hold A = fly/boost (`behavior-notes.md:1500`). Exact original vertical field/velocity remains unknown (`behavior-notes.md:995-1000`, `1677-1684`). |
| B | Attack | K or B; gamepad button 1 | B resolves per-borg primary action: melee if melee-primary/available, shot if shot-primary/available; shot consumes ammo/reload and may home to lock target | `CONFIRMED-ASSET` input, B bit bridge `DERIVED`, action semantics `TUNED` | Texture proves B attack. GDB injection plus decomp prove B `0x00000200` reaches normalized PAD and survives the command mask into `actor+0x5b4` when the input bridge runs. Current mapping is `adapter.ts`; attack code is `combat.ts`, melee start, projectile spawn. Per-borg action profiles are asset-backed but tuned, not decoded hit-bin semantics (`packages/combat/src/data/actionProfiles.json`, `packages/combat/src/actionProfiles.ts`). Next: one close B and one ranged B Dolphin trace. |
| X | Special attack | L or X; gamepad button 2 | Starts special if cooldown is clear; current generic implementation is radial/AoE burst with cooldown and action lock | `CONFIRMED-ASSET` input, X bit bridge `DERIVED`, `TUNED` mechanic | Texture and in-battle HUD capture both show X special. GDB injection plus decomp prove X `0x00000400` reaches normalized PAD and survives the command mask into `actor+0x5b4` when the input bridge runs. Current mapping is `adapter.ts`; special path is `combat.ts`; constants are `constants.ts`. |
| L/R | Lock-on switch (texture label: `ロックオン きりかえ`) | Q = previous/L stand-in; R or Tab = next/R stand-in; gamepad left trigger = previous, right shoulder/trigger = next | Human borgs auto-acquire locks; R/request-2 cycles forward through the compact source enemy list, L/request-3 cycles backward, never dead borgs, never self, never allies. The locked enemy is marked with a continuously spinning red ring reticle | Original input `CONFIRMED-ASSET`; request mapping `DERIVED`; current binding + enemy-only spinning reticle `CONFIRMED-CODE` | `FUN_8005a298` maps source input bits to `+0x73c = 2/3`; `zz_006b450_` applies next/previous over the retained target-list index. Browser mapping uses Q because keyboard L is already X/special. The reticle renders only over the local human's `lockTarget` and follows borg switches/deaths. Exact native GC physical mapping still needs live trace. |
| Z | Ally lock-on (texture label: `みかた ロックオン`) | Z; gamepad left shoulder (button 4) stand-in | Hold Z selects a same-team ally using source target-list state; release restores the retained enemy lock. Records a separate `allyLockTarget`, marked with a GREEN overhead arrow; does not redirect attacks or trigger ally charge/power-up yet | `CONFIRMED-ASSET` input; Z request mapping `DERIVED`; current binding + distinct ally marker `CONFIRMED-CODE`; charge behavior `UNKNOWN` | `FUN_8005a298` maps Z hold/release into `+0x73c = 5/4`; `zz_006b450_` saves/restores the enemy target while selecting allies through +0x73e. Future charge/power-up side effects remain trace-pending. |
| Start | Pause / advance / skip, depending screen | Battle pause: Escape, Enter, gamepad button 9; Load Box skip currently S | Battle pause opens `PauseMenu`; menus use screen-specific handlers | Original battle binding `UNKNOWN`; current `CONFIRMED-CODE` | UI notes prove Start advances boot/title and Load Box has START=SKIP (`UI-FIDELITY-SPEC.md:59`, `:67-68`). Current pause poll is `main.ts:1345-1351`; Load Box keyboard skip is `LoadBoxData.ts:52-59`. Next: capture original pause/control screen for battle Start semantics. |
| Manual borg switch | Unknown / not on control texture | none | Inactive; active borg changes only through death/auto-deploy | Current `CONFIRMED-CODE`, original manual input `UNKNOWN` | The browser E-key retirement/requeue path was removed because the texture shows no manual switch and decomp has death/swap timer anchors, not a proven manual switch button (`function-evidence-index.md:56-57`, `chunk_0076.c:3819-3821`, `:4844-4897`). Next: trace `0x802807ac`/`0x80281c38` while pressing candidate buttons and while a borg dies. |

## Current Web Binding Matrix

These are current implementation facts, not claims about the original:

| Intent | Keyboard | Gamepad | Code |
|---|---|---|---|
| Move | WASD or arrows | axes 0/1 | `apps/game/src/sim/adapter.ts:130-138`, `:147-151` |
| Jump | Space or J | button 0 | `adapter.ts:139`, `:153` |
| Attack | K or B | button 1 | `adapter.ts` |
| Special | L or X | button 2 | `adapter.ts` |
| Dash | Shift | none; pure lateral stick while locked auto-dodges | `adapter.ts:142`; `movement.ts:237-244` |
| Lock request | U | none | diagnostic only; players auto-lock in combat core |
| Switch-lock next | R or Tab | buttons 5 or 7 | source request 2; `adapter.ts`, `battle.ts` |
| Switch-lock previous | Q | button 6 | source request 3; `adapter.ts`, `battle.ts` |
| Ally-lock | Z | button 4 stand-in | source hold/release requests 5/4; `adapter.ts`, `battle.ts`, `combat.ts` |
| Switch borg | none | none | `adapter.ts:145`; no battle-core consumer |
| Pause | Escape or Enter | button 9 | `main.ts:1345-1351` |

Known mismatches:

- Current switch-lock physical bindings are browser stand-ins for the GameCube shoulder cluster;
  exact native button-to-request mapping still needs a live trace.
- Current HUD labels special as X (`BattleHud.ts`), matching the control texture and
  the in-battle reference capture.

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

- Current browser lock-on now uses the recovered source-shaped target state: compact filtered
  target-list indices mirror actor +0x73d/+0x73e, active target state mirrors +0x502/+0x503,
  and R/Z write source request-byte families through the combat runtime. Initial null-target
  acquisition uses the source nearest-candidate rule from `FUN_8006b850` / `zz_006b450_`:
  eligible targets are scanned in source-list order, compared by 3D squared distance, and later
  equal-distance entries win.
- Human-controlled borgs keep continuous lock state while active. R/request-2 and L/request-3 are
  edge-triggered switch-lock (+0x73c = 2/3). Z is hold-ally-lock: press/hold requests ally lock
  (+0x73c = 5), release restores the retained enemy lock (+0x73c = 4). The press latches live
  in `cooldowns` (`switchLockHeld` / `allyLockHeld`, skipped by `stepCooldowns`).
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
- Ally-lock target selection now records a separate same-team `allyLockTarget` while Z is held,
  uses the same source-shaped target state as enemy lock, and restores the retained enemy on
  release. Original partner charge/power-up behavior remains untraced. Enemy lock targets remain
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

- Control texture proves B attack and X special. Current web code maps B-like attack to
  K/B and special to L/X (`adapter.ts`).
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
  B/X action mapping to state indices still requires live input correlation.
- New static candidates for the next live trace:
  - `FUN_8015b0b4` chooses X current bit for borg `0x061e`, otherwise B current bit,
    before advancing local action fields. This proves B/X consumers are borg/action
    specific, not one global "B always primary, X always special" table.
  - `FUN_800e622c` has an X pressed-edge branch into an action helper path.
  - `FUN_801304b8` has B and X pressed-edge branches gated by borg id/cooldown.
  These are trace targets, not browser rules yet.
- Static table context: `FUN_800e622c` and `FUN_8015b0b4` are both entry 2 in their
  borg-specific `actor+0x540` dispatch tables. This proves where to break for live
  correlation; it still does not prove which visible move the browser should perform.
- Static sound context: the `FUN_801304b8` B pressed-edge branch has exact
  `zz_00f036c_` cue args `0xeb` and `0xaa` for two borg ids. Treat them as trace
  targets only; browser per-action cue IDs stay `UNKNOWN`.

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
- `FUN_8005a298` is the focused-pass exact Z `0x10` consumer found so far: it tests
  `actor+0x5b4 & 0x10` and writes `actor+0x73c`. That proves a Z command branch exists,
  but not ally target choice, charge, power-up, or camera behavior.
- Its caller path is now identified statically: input bridge callers
  `FUN_80054cbc`/`FUN_80054cf0` call `FUN_80055568`, which calls `zz_0059068_`;
  `zz_0059068_` always calls `FUN_8005a298` near its tail. The fresh Dolphin liveness
  capture still missed this whole actor-update route, so this remains static proof only.
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
4. B/X trace: one close-range B, one ranged B, one X. Correlate PAD bits to `object+0x6fe`,
   `FUN_8005d494`, projectile spawn, cooldown/ammo fields, animation request helper calls, and
   audio trigger wrappers. Do not promote any B/X state mapping or sound cue until this trace
   shows the original action transition and cue path.
5. Manual borg switch trace: press candidate buttons and separately let a borg die while
   watching `0x802807ac` / `0x80281c38` plus active borg slot/player state. Until then,
   manual switch stays inactive in the browser battle core.
6. Power-up/ally-charge trace: trigger ally charge and any power-up pickup while watching
   `0x80068138`, `0x800681e4`, `DAT_8043612c[slot]`, and actor fields `+0x74a/+0x74e/+0x750`.
7. Stage render variants: decode/import the `stc##_mdl.arz` family before claiming visual
   variant rendering is 1:1. The selector count is ported; the rendered variant assets are not.
