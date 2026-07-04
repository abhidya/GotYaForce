# Wiki-mined mechanics queue (beyond the Attacks page)

Fable 5 audit follow-up, 2026-07-03. Second mining pass over the fandom wiki (via search
extracts — direct fandom fetch is blocked with HTTP 402) plus StrategyWiki/GameFAQs hits.
All wiki claims below are paraphrased taxonomy, never numeric truth. Each entry lists the
decomp lead and its queue status. Research results land as new lettered sections in
`behavior-notes.md`; port work becomes ATK-tickets in `research/tasks/attack-port/`.

Sources (player-facing taxonomy only):
- https://gotchaforce.fandom.com/wiki/Attacks
- https://gotchaforce.fandom.com/wiki/Power_Burst/Hyper_Mode
- https://gotchaforce.fandom.com/wiki/Gotcha_Force_(Game)
- https://gotchaforce.fandom.com/wiki/Instruction_Manual
- https://strategywiki.org/wiki/Gotcha_Force/Gameplay
- https://gotchaforce.fandom.com/wiki/Borg_List (borg-specific ability notes)

> **Status update (same day):** W1/W3/W4/W5/W6 research returned — results in
> behavior-notes.md sections (aj) fusion, (ak) levels, (al) healing/pull/self-hit.
> New tickets: ATK-018 (fusion pair shell), ATK-019 (healing shell), ATK-020 (level
> plumbing). W2's passthrough claim came back NEGATIVE in code (see (al) — the "0.25
> divisor" read was a misread of the confirmed 2.0 constant); the burst meter remains a
> Dolphin T3 item. W7/W8/W9 remain queued.

## W1. Power Burst fusion / combining borgs — DONE → (aj), ticket ATK-018

- **Wiki claim (paraphrased)**: specific partner borgs fuse into a combined borg when Power
  Burst activates with both on the field (e.g. Machine Red pairs with Machine Blue or with
  Cyber Atlas to form different Cyber Machines; dragon combinations exist); in co-op the
  fused borg's parts are controlled by their respective players.
- **Decomp lead (already confirmed)**: `zz_005b678_` (chunk_0007.c:3500-3553) matches
  actor+0x1000 spawn ids against a pair table at **0x802d352c**; pair-found path sets
  +0x4a1=1/2 and syncs headings. The table dump + post-match spawn path are the open parts.
- **Queued**: research agent dispatched (pair-table dump, fusion spawn/control/end).
  Port ticket to be cut after results (candidate: ATK-018).

## W2. Hyper meter fill + burst ally/self passthrough — CODE-NEGATIVE → (al); meter stays T3

- **Wiki claim (paraphrased)**: the hyper meter fills from attacking enemies; Y activates
  burst; during burst, allied attacks — including your own self-damage (self-damaging
  borgs like the big-missile tank exist) — pass through you harmlessly.
- **Decomp lead**: meter accumulator NOT found in the hit path (findings mechanic S);
  passthrough would be a hit-skip gate on +0x6fc/+0x6fa in the collision validation
  (chunk_0003.c:7085-7091) — research agent dispatched. Meter itself remains a Dolphin
  T3 item.
- **Queued**: passthrough/self-hit research in flight; T3 unchanged for the meter.
  Feeds ATK-012.

## W3. Healing / support specials (Nurse borgs) — DONE → (al), ticket ATK-019

- **Wiki claim (paraphrased)**: Nurse-type borgs heal allies; one heal restores most or all
  HP; the only limit is the move's recharge. Ally lock-on (Z) supports targeting allies.
- **Decomp lead**: the damage formula cannot produce healing (returns 0 for non-positive
  damage), so healing must be a separate HP-increase path — agent is sweeping all +0x1c6
  writers. Recharge is plausibly the weapon-cell ammo system already decoded (ATK-009).
- **Port note**: ally target selection is now source-shaped through `SourceTargetLockState` /
  `sourceSwitchAllyLock`; healing/support consumption of that ally target remains the gap.
- **Queued**: research in flight; ticket after results (candidate: ATK-019).

## W4. Self-damage (owner-hit rules) — DONE (negative) → (al): owner exclusion is unconditional

- **Wiki claim (paraphrased)**: some borgs' explosives hurt the borg itself.
- **Decomp lead**: the port excludes the owner (`o.uid === pr.ownerUid` skip,
  combat.ts:903); the ROM's owner-exclusion check in the collision passes may be gated by
  a record flag — agent is quoting the exact owner check.
- **Queued**: research in flight; affects ATK-008's consumption refactor test vectors.

## W5. Pull / magnet / tether effects — DONE → (al): confirmed forced-move channel

- **Wiki claim (paraphrased)**: a magnet borg attracts every nearby borg toward itself.
- **Decomp lead**: forced-movement family already partially indexed: puVar17[8] effect
  bits, DAT_803b06c0/c4/c8 world-target vectors, `start_forced_move_to_point` @0x8006ab04
  (behavior-notes (q) Lead 3). Agent is characterizing the pull consumer.
- **Queued**: research in flight; folds into the status framework (ATK-010 follow-up).

## W6. Borg level system (HP/ammo/refill/damage growth) — DONE → (ak), ticket ATK-020

- **Wiki claim (paraphrased)**: levels raise HP, ammo capacity, ammo refill speed, and
  more; out-of-range levels borrow other borgs' attribute rows (cheat lore — consistent
  with row-arithmetic indexing).
- **Decomp lead (already strong)**: level byte +0x3ec indexes DAT_804339e8 in the stat-row
  formula (zz_0055f90_, behavior-notes (ag)); damage-formula level floats +0xc4/+0xb4 init
  sites are the #1 formula unknown (behavior-notes (ah)); refill-rate +0x768's initializer
  may be level-derived (would also settle open-questions Q7).
- **Queued**: research agent dispatched (level writers, float inits, +0x768 init,
  DAT_804339e8 dump). Port ticket after results (candidate: ATK-020 — level plumbing into
  damageFormula's existing attackerPower/defenderPower params).

> **(ap) update:** JP Wikipedia states the shield rule precisely — infinite durability,
> no input, auto-blocks frontal hits while NOT attacking. Concrete candidate semantics
> for the /40 divisor gate (flagsA & 0x1000 + victim +0x59c & 0x1000). New items:
> W17 three flight models (winged forward-locked flight / air-class permanent flight /
> boost); level cap 10 with level-up shortening charge/reload (feeds ATK-020 + Q7);
> tribe-affinity spot-check of the ported type matrix (gun<girl, musha>knight,
> angel>demon, tank vs flyers) — cheap validation script against the extracted 20x20.

## W7. Guard / block / barrier — QUEUED (behind status research)

- **Wiki claim (paraphrased)**: a Block effect raises a barrier in front of the targeted
  borg that stops projectiles from the enemy team of whoever produced the effect.
- **Decomp lead**: the /40 block divisor gate (flagsA & 0x1000 + victim +0x59c & 0x1000,
  formula step 18) and state-table slots 5/6/8 (guard-entry shapes, behavior-notes (u));
  barrier-as-object would live in the per-type dispatch (PTR_FUN_802da740 — same unread
  table blocking projectile solidity, open-questions Q6).
- **Queued**: not yet dispatched — bundle with the Q6 per-type dispatch read (one agent
  should enumerate the whole PTR_FUN_802da740 table once).

## W8. Fortress borgs / multi-part bosses — QUEUED

- **Wiki claim (paraphrased)**: fortress-class boss borgs are huge, with destructible
  parts/sub-targets.
- **Decomp lead (already partially confirmed)**: the linked-object HP-mirror mechanic in
  the confirmed HP-subtract function (zz_003d344_, behavior-notes (h)) and the
  linked/partner-object fields (+0x24 wrappers, knockback mode 3, §p) are exactly the
  multi-part plumbing. Gauge init already covers boss-scale values (gaugeInit.json).
- **Queued**: not yet dispatched — needs a scoped agent on linked-object construction
  (who creates child actors with HP mirrors) before a ticket exists. Candidate: ATK-021.

## W9. In-battle borg switching / next-deploy choice — QUEUED (low)

- **Wiki claim (paraphrased)**: the next borg deploys on death; player can influence
  deploy order mid-battle (d-pad selection in some modes).
- **Port note**: `PlayerInput.switchBorg` is reserved and deliberately ignored "until
  original proof exists" (types.ts:38-39). Death/deploy flow is already derived
  (behavior-notes (af)).
- **Queued**: needs a small corpus pass on deploy-order selection input; low priority.

> **Second correction pass (same day, behavior-notes (an)):** the user supplied the
> full GameFAQs guide texts. Decoding the glitch-FAQ borg-ID encoding against the
> roster CORRECTED W3: the (al) HP-increment is VAMPIRE LIFESTEAL (pl0702/pl070a),
> not nurse healing; the :6237 peer check is Demon/Akuma Samurai sword growth. Nurse
> healing is a separate fixed-amount targeted X-heal (37/50/100 anchors). Vampires'
> passive HP drain also revises the "no periodic drain" negative. W4 upgraded:
> suicide borgs detonate on CONTACT (collision-scripted). W10 refined: contact damage
> is authored PER-BORG (dragons 22/44, Accel Ninja 44), not engine-global. Full
> anchor data: research/decomp/data/guide-anchors-movelist.json. ATK-019 rewritten.

## Guide-mined additions (GameFAQs/SDA pass, 2026-07-03 — see behavior-notes (am))

- **W10. Contact damage OBSERVED** — speedrun tech confirms stomp/contact hits exist and
  grant hit-invincibility to victims. Upgrades findings mechanic L from WIKI_TAXONOMY_ONLY
  to observed-behavior; ATK-006's scaffold stays disabled but its evidence section now has
  a concrete borg + scenario for the T2 contact-script trace (a stepping-capable giant).
- **W11. Suicide self-damage** — the ICBM-type borg kills itself as part of its detonation
  move; owner-collision exclusion stays intact ((al)). Research direction: find the
  self-kill in the move handler (grep the deploy/detonate object handlers in
  chunk_0029/0036 for owner HP/kill-event writes). Not yet dispatched.
- **W12. X-as-flight-control overload** — flyer borgs use X to dive (and A to rise), so
  the command resolver's "X = special" assumption is per-borg wrong. Feeds ATK-003's
  decision-tree requirements and trace T1 (add a flyer X-press script line).
- **W13. Burst bonus evaluates at hit time** — projectiles fired pre-burst gain the bonus
  if they land during burst. Already consistent with the formula reading; add as a T3/T10
  pass/fail vector and an ATK-012 test case.
- **Stat-row layout decoded** — see (am): per-weapon (cur,max,refillType,refillParam)
  now readable for weapons 0/1 for the whole roster; feeds ATK-009 directly.

## Manual-mined additions (official NA manual scan, 2026-07-03 — behavior-notes (ao))

- **W14. Air recovery jump** — CONFIRMED_MANUAL: pressing A while blown away jumps out
  of danger. The port has no knockback-escape input at all. Research direction: the
  hit-reaction state handlers (slots 25-30, (u)) re-reading the jump button; then a
  ticket (movement.ts + hit-reaction states). Not yet dispatched.
- **W15. Double-tap evade dash** — CONFIRMED_MANUAL: the evade step is a stick
  double-tap; the port's dodge trigger (pure-lateral-while-locked) is a different
  rule. Verify which is ROM-true in trace T1's input scripts before changing
  movement.ts (the lock-relative trace (y) may have conflated the two).
- **W16. X-attack ammo binding** — CONFIRMED_MANUAL: separate "B Bullets"/"X Bullets"
  HUD counters bind weapon cell 0 = B ammo, cell 1 = X ammo. ATK-009 landed with both
  cells sourced; follow-up ticket needed: specials/X-attacks consume weapon cell 1
  instead of being cooldown-only (small combat.ts change once the special path is
  next touched — fold into ATK-012 or cut ATK-022).
- **Burst gate + simultaneity** — CONFIRMED_MANUAL: Y activates only at full meter;
  simultaneous presses give co-op simultaneous bursts (reads the +0x6fb=6 window as
  the simultaneity tolerance). Feeds ATK-011/012 and T3.

## Player-reported additions (owner gameplay session, 2026-07-03)

- **W17. Force-exhausted player becomes a 1-HP husk borg — IMPLEMENTED (2026-07-03)**:
  in team battles, a player who loses ALL borgs in their force respawns as a tiny 1-HP,
  1-bullet husk while an ally is still alive, and keeps respawning per husk death (owner
  observed live). Identity LIVE-VERIFIED by GDB probe of the owned "meter charged.sav"
  (scripts/probe-actor-slots.mjs): the husk actor's species word actor+0x3e8 = **0xf07 ->
  pl0f07**, the UNNAMED final entry of the Death Borg family (assets exist:
  pl0f07.pzz/_mdl.arc/data.bin/hit.bin/mot.bin; absent from borgs.json/roster) — NOT
  pl0d07 DEATH BOMB as first guessed. hp=1 and weapon cell +0x774/+0x776 = 1/1 confirmed
  on the live actor. The chunk_0006.c:7175 +0x4a0 lead was DISPROVEN by the same probe
  (+0x4a0 = 0 on the husk; that spawn path is a different mechanism). The probe also
  established actor+0x3e8 (u16) as the actor's borg-number field (0x615 on all three
  live G REDs) and actor+0x3e7 as a slot echo, NOT species (confirming behavior-notes
  534). Ported in battle.ts: deployNext falls through to a synthesized pl0f07 entry
  (HUSK_BORG_ID, energy 0, hp/ammo 1/1 live-verified) while allyForceStillFighting();
  husk deaths skip the defeated counters. Selfcheck
  assertHuskDeploysOnForceExhaustion covers deploy/respawn/0-energy/uncounted/loss-on-
  ally-death. Residual unknowns: the husk's real stat bytes (pl0f07data.bin unparsed —
  defense/speed are labeled TUNED placeholders) and whether the ROM counts husk kills
  anywhere (score screens).

## Explicitly NOT queued (already resolved or closed)

- GF Energy cost/budget system — already ported (challenge tables, energy accounting (ae)/(af)).
- Type effectiveness — ported (type matrix, (l)/(w)).
- Hidden resistance/falloff — resolved as comboRankScale_802c7ca0 (findings mechanic U).
- Manual lock-on algorithm — superseded: source target-entry state is ported; ally-support
  consumers still need follow-up ((q)).
- Story-mode transformations on data recovery (e.g. the hero borg's upgraded form) —
  roster/unlock data, not a combat mechanic; out of scope for the attack port.
