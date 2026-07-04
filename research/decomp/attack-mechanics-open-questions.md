# Attack-mechanics open questions (ranked)

Companion to `attack-mechanics-findings.md` (Fable 5 audit, 2026-07-03). Ranked by how much
each unblocks 1:1 combat. "Agent type" legend: **grep** = cheap read-only corpus/asset search
agent; **code** = cheap coding agent; **Fable** = needs cross-system synthesis judgment;
**Dolphin** = human-driven (or scripted) live trace against the user's own disc.

---

## Q1. What writes the per-actor command struct (+0x4b0), and which physical button maps to which +0x5d4 bit?

- **Why it matters**: this is the whole B/X contextual-attack resolver. Until the writer and
  the bit mapping are pinned, every command mapping in the port is a guess. Two independent
  corpus reads already produced CONFLICTING guesses for bit 0x200 (B vs Y) — proof that the
  +0x5d4 word is a transformed space that cannot be resolved by reading alone.
- **Evidence searched**: PAD/SI symbols (SDK wrappers only, chunk_0063/0065); all writers of
  actor+0x4b0; stores of small constants near button-bit tests in chunk_0009.c; CPU-AI index
  (`research/decomp/index/cpu-ai-evidence.md`). The decision testers and +0x585/+0x586
  outputs ARE found (chunk_0009.c:220-587); the struct writer is not.
- **Next search/trace**: (a) grep for writers to the memory the +0x4b0 pointers target —
  start from where +0x4b0 itself is initialized (find `0x4b0) =` stores and the allocation
  site); (b) otherwise go straight to Dolphin trace T1: watch commandStruct bytes while
  pressing scripted buttons — 30 minutes of tracing beats another corpus day here.
- **Expected output**: table physical-button -> +0x5d4 bit -> command value, plus the
  writer function address; appended to behavior-notes.md as a new lettered section.
- **Agent type**: grep (one more targeted pass), then **Dolphin** (T1). NOT a coding task.

## Q2. What is the exact melee-vs-ranged contextual rule for B (and X), including the FLOAT_8043762c threshold value?

- **Why it matters**: player feel; wiki claim (A/B) that melee wins at melee range.
- **Evidence searched**: distance gates found only inside subtype selection
  (chunk_0009.c:497-498, 555-556, vs +0x694/+0x6a4); ranged-needs-target gate at :412.
- **Next search/trace**: dump FLOAT_8043762c via `research/decomp/dol.py` (trivial); read
  the tester bodies zz_0069a88_..zz_0069cb0_ fully to map every gate; then T1 distance sweep
  to validate.
- **Expected output**: decision tree with real constants -> unblocks ticket ATK-003.
- **Agent type**: grep + a one-line dol.py read (code-adjacent), then Dolphin T1 validation.

## Q3. What is the per-actor action table at +0x4ec (command,subtype -> action), and what data file populates it?

- **Why it matters**: this is the ROM's own move-capability table — the DERIVED replacement
  for the heuristic `actionProfiles.json` primary/hasMelee/hasShot flags, and likely the
  missing (move -> animation bank -> hitbox remap slot) binding.
- **Evidence searched**: consumption in zz_006a104_ (chunk_0009.c:603-662) found; init not.
- **Next search/trace**: grep writers of `0x4ec) =` and the surrounding init in the actor
  spawn path (chunk_0006/0007 near the stat-row loaders); cross-reference against pl####
  data files already parsed (pl data page +0x4ac is bound nearby).
- **Expected output**: table layout + source file offsets -> unblocks ATK-005 for real.
- **Agent type**: grep, then Fable to bless the format interpretation.

## Q4. Power Burst meter: which field accumulates, what threshold arms activation, and what clears +0x6fc (duration)? — MOSTLY RESOLVED (2026-07-03)

- **Resolved by save-state diff (scripts/diff-actor-block.mjs) + targeted corpus re-read**
  (full detail in attack-mechanics-findings.md §S): meter = per-player struct
  `PTR_DAT_80433934 + i*0x3c + 0x126` (u16), max at +0x124 = 3000, charged flag +0x103
  (the FUN_80069814 arm precondition), burst mode +0x104 (1=Y burst, 2=spawn hyper),
  duration countdown +0x10c/+0x10e = 600 frames (Y) / 1800 frames (spawn). +0x6fc clear:
  zz_005b2b8_ top-of-frame sweep when the player's +0x104 drops to 0.
- **FILL RULE RESOLVED (2026-07-03 T3 live traces)**: **+50 per hit connection, attacker
  only, flat** — independent of damage dealt:
  - B shot on live G Red: 16 HP damage -> +50 meter (reproduced 3x);
  - Plasma Knuckle melee on live G Red: 25 HP damage -> +50 meter;
  - one penetrating beam through a DEAD borg husk: +150 = 3 hit connections x 50
    (dead borgs still register hits; G Red beam penetration = "borgs");
  - victim side: NONE of the other three players' meters moved on any hit taken —
    taking damage does NOT fill the victim's meter;
  - clamp/flag timing (live): +0x126 clamps at max 3000 while +0x12a keeps accumulating
    (2929 -> 3079 -> 3129); charged flag +0x103 flips to 1 ONE frame after +0x126
    reaches max.
  - Caveat: 50 confirmed for two different G Red moves (shot + melee); a per-move or
    per-record override elsewhere can't be fully excluded. NOTE the damage-record field
    `forceGaugeCurveIndex` is NOT this — that's a damage multiplier keyed to the TEAM
    GF-energy gauge (player struct +0x114 max), a separate gauge from the burst circle
    (+0x124/+0x126). The damage pipeline (chunk_0004.c:6672-6828) never writes +0x126.
- **Remaining (minor)**: live-verify the 600-frame duration + what the +0x12a unclamped
  accumulator feeds (results screen? chunk_0022.c:1671/1737 reads it for min/max across
  players); Q5 speed boost (non-burst baseline captured: 22.0 world-units/frame dash).
- ATK-012 fill rule: **unblocked** — port as `onHitConnect(attacker): meter = min(meter+50,
  3000); unclamped += 50; if (meter == 3000) charged = 1` per player.

## Q5. Where does Power Burst's speed boost live (wiki: "massive speed"), given no +0x6fc-gated speed modifier exists? — RESOLVED AT VALUE LEVEL (2026-07-04)

- **Live-measured (T3-q5-speed-final.jsonl, live paired activation with owner at both pads)**:
  **burst movement speed = x1.5** — median moving delta 33.0 world-units/frame during burst vs
  the proven 22.0 u/f ground-walk baseline ((ac)). Ported as BURST.SPEED_MULTIPLIER.
- **Duration model CORRECTED by the same trace**: the +0x10c/+0x10e=600 timer runs in parallel
  with the METER ITSELF draining -5/frame from 3000 (BURST.DRAIN_PER_FRAME; 343 clean -5
  frames measured; 3000/5 = the 600f ceiling). Burst ends when the meter empties — observed
  437 frames because ACTIONS SPEND EXTRA meter: discrete -45/-50/-60 (dash-shaped) and
  -350/-470 events; the drain ledger sums to exactly 3000. Also confirmed: versus-mode
  activation requires BOTH teammates armed within the 6-frame window (zz_005b2b8_ candidate
  count > 1 unless player flag +0xf5 == 1) — solo Y just arms and expires.
- **Still open (minor)**: the code path carrying the x1.5 (no +0x6fc-gated modifier in the
  read corpus; moveMult1dd4/param-tier fields did NOT change at activation — likely inside
  the movement-physics bucket), and the per-action meter-cost table.

## Q6. Do solid projectiles / projectile-vs-projectile collisions exist in code, and where?

- **Why it matters**: wiki mechanics M/N; affects how stepProjectiles must be restructured.
- **Evidence searched**: generic collision passes (chunk_0003.c:7031-7223) — negative; the
  per-object-type dispatch table PTR_FUN_802da740 (chunk_0013.c:1172) bodies are UNREAD.
- **Next search/trace**: enumerate PTR_FUN_802da740's pointer targets (dol.py raw read, same
  technique as the 35-slot state table) and skim each handler for object-object hit tests;
  in parallel, Dolphin T5 head-on projectile tests.
- **Expected output**: either the solidity flag/field, or a corpus-wide CHECKED_CLOSED.
- **Agent type**: grep + dol.py (table dump), then Dolphin T5.

## Q7. What is actor+0x768 really — ammo refill rate, scale-related float, or both consumers misread?

- **Why it matters**: ATK-009's refill model reads +0x768 as the rate; the status search
  read the same offset as a scale-reduction float multiplied by shrink/grow LUTs. Both were
  single-pass corpus reads; at least one is wrong (or the field is genuinely shared, which
  would itself matter).
- **Evidence searched**: zz_006dcc0_ (chunk_0009.c:2923) vs chunk_0007.c:2868-2876.
- **Next search/trace**: re-read both sites carefully (they may be different structs — the
  chunk_0007 site may be on a different object type); confirm the struct identity via the
  surrounding field usage; T7/T8 logging settles it live.
- **Expected output**: one confirmed role per struct; corrects the findings/ledger.
- **Agent type**: grep (careful re-read), then Dolphin if still ambiguous.

## Q8. Which status id (0-63) maps to which player-visible effect, and how is poison implemented (no DoT loop found)?

- **Why it matters**: mechanic Q can only ship as a shell until ids mean something.
- **Evidence searched**: id/timer/immunity plumbing found; per-id consumers beyond
  shrink/grow not isolated; no periodic HP drain anywhere.
- **Next search/trace**: grep readers of victim+0x71a outside the application site (reaction
  selection? per-id branch table?); Dolphin T8 for ground truth.
- **Expected output**: status-id table with effects + durations -> turns ATK-010's shell
  into real behavior tickets.
- **Agent type**: grep first, **Dolphin** (T8) for semantics.

## Q9. What consumes the mash counter +0x550 past the cap-4 comparison — extra hitbox activations, duration extension, or something else?

- **Why it matters**: mechanic T; determines whether mashing adds hits (wiki) or advances
  phases faster.
- **Evidence searched**: increment + cap in FUN_8005d494 (chunk_0007.c:4809-4816); +0x552
  companion flag; no other consumers checked yet.
- **Next search/trace**: grep all readers of +0x550/+0x552 corpus-wide; then T2 mash logging.
- **Expected output**: the downstream effect -> spec for ATK-017's real behavior.
- **Agent type**: grep, then Dolphin.

## Q10. Which real moves set damage-record flagsA bit 0x1000 (friendly-fire exemption / guard interaction) and flagsB bits 0x4000/0x2000?

- **Why it matters**: FF exception (V), penetration gate (O), and combo-falloff exemption (U)
  all key off these bits; per-move values live in hit-bin/comhit data that is extracted but
  not yet swept for flag statistics.
- **Evidence searched**: the 9 borg-family records (all flagsB=0, flagsA in {0,1}); generic
  table DAT_802c4760 extracted to research/decomp/data/damage-records-802d46e0.json but not
  flag-audited; per-move hit-bin records not swept.
- **Next search/trace**: script sweep over user-data hit-bin extractions counting flag bits
  per move/borg (pure local data work, no ROM re-derivation).
- **Expected output**: flag histogram + list of exempt/piercing moves -> feeds ATK-008/014.
- **Agent type**: code (script sweep) — good cheap-agent task.

## Q11. Knockback magnitude and reaction lengths (pre-existing, re-ranked here)

- **Why it matters**: largest feel gap in already-ported systems; blocks MELEE/SHOT/SPECIAL
  KNOCKBACK/HITSTUN TUNED markers (constants.ts).
- **Evidence searched**: exhaustively in behavior-notes (p)/(s)/(u) — direction derived,
  magnitude consumer never found.
- **Next search/trace**: Dolphin T9 (fit launch speed vs record hitStrength 1/4/16).
- **Expected output**: DERIVED magnitude rule.
- **Agent type**: **Dolphin** (T9), then code to port the fit.

## Q12. Does passive contact damage exist at all (stomp/sword-out flight), and if so which records carry it?

- **Why it matters**: mechanic L ships disabled until proven.
- **Evidence searched**: state handlers ((u) full read — no damage side effects); hit-bin
  format allows persistent attack records but none confirmed.
- **Next search/trace**: sweep per-borg hit-bin extractions for attack-region records with
  activeEnd == -1 (persistent attack hitboxes) — pure local data; then a T2 contact script.
- **Expected output**: either candidate records (ASSET_INFERRED -> trace) or a data-backed
  CHECKED_CLOSED.
- **Agent type**: code (script sweep), then Dolphin.
