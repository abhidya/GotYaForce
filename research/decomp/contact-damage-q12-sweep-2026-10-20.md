# Q12 contact damage — per-borg hit-bin sweep (2026-10-20)

Round-2 wiring pass, item #4. Q12 asked: *"Does passive contact damage exist
at all (stomp/sword-out flight), and if so which records carry it?"* — with the
prescribed next step: *"sweep per-borg hit-bin extractions for attack-region
records with activeEnd == -1 (persistent attack hitboxes)".*

**Verdict: the sweep was run in full. No wireable contact-damage carrier
exists in the per-borg hit-bin data. `stepContactDamage` stays disabled.**
The sweep also produced a DERIVED correction to what `activeEnd == -1/-2`
mean, which the port currently approximates with a TUNED 8-frame window —
recorded below for the next wiring pass. Reproduce with
`scripts/sweep-hit-bin-persistent.mjs`.

## What the sentinel windows actually mean (DERIVED)

From the per-frame hitbox handler `FUN_8008a65c` (chunk_0013.c:1125-1249),
which ticks every spawned hitbox:

- Borg-attached hitboxes compare their window against the owner's ANIMATION
  frame float (`actor+0x1cdc`). The handler's first check despawns the
  hitbox when the owner's anim-ID snapshot changes — **but that check is
  skipped when `activeEnd == -1`** (`*(short *)(param_9 + 0x4a) != -1` is a
  precondition of the despawn branch).
- In the active phase, the end-of-window kill runs only when `-1 < activeEnd`
  (signed). So:
  - `activeEnd == -1` → **persistent**: no frame expiry AND survives
    animation changes. The hitbox lives until its owner/state removes it.
  - `activeEnd == -2` → **open-window**: no frame expiry, but DOES die on
    animation change (active for the rest of the arming animation).
  - `activeEnd >= 0` → ordinary frame window.

## Sweep results (attackHitTables.json = the extracted pl####hit.bin attack region)

- 208 borgs, 4,258 extracted records. `activeEnd == -1`: **1,800 records**
  (42%); `activeEnd == -2`: **259**. Every record in the table is referenced
  by at least one remap kind (the earlier "unreferenced" reading was a
  key-type bug in the first sweep draft — re-run corrected).
- All 1,800 persistent records have `activeStart == 0`; 1,788/1,800 sit on
  bone 0, none attach to root. 1,650 (borg, kind) pairs consist solely of -1
  records — every borg has them, spread over kinds 0-31 with kinds 16-31
  near-uniform (~46-50 refs each). They are a standard part of the kind
  system (shot children, breath weapons, held/special volumes), not a
  contact-specific record class.
- Script-armed kind cross-check (meleeAnimKinds.json, the DOL mot-event
  arms): the guide-claimed borgs' -1 kinds are NOT their melee kinds.
  Dragons (pl0500/pl050c) arm kinds [2,3,4,6] from scripts — the windowed /
  -2 records (bites/tail). Their -1 kinds (0,1,5,7,8,9,10,11) are the
  fire-fn-armed set (kind 0 = shot child; kind 1 resolves to 80 damage =
  breath; kind 8 = a radius-110 projectile record).
- Damage resolution via familyDamageRecords.json for every guide-claimed
  borg (FLAME/BLIZZARD/PLASMA DRAGON "44", other dragons "22", ACCELERATION
  NINJA touch "44"): **no record in any claimed borg resolves to 22 or 44.**
  Dragon records resolve to 5/10/25/40/50/80; pl0004's blade records
  (kinds 10/11, open-window -2, damage index 9/11) resolve to 20. The guide's
  2:1 ratio between the two dragon groups is mirrored in the data (50 vs 25)
  but the absolute guide values appear nowhere.
- Arming paths are exclusively attack contexts: mot op-0x0a events inside
  animations, family fire functions (shots/specials), and 11 literal
  `zz_008ac80_` sites (movement-hit-decode-2026-07-04.md §2). No corpus site
  arms a hit kind from a locomotion state, and behavior-notes (u)'s full
  read of every state handler found no movement-handler damage side effects
  (attack-mechanics-findings.md L).

## Why this is not wired

Contact damage is OBSERVED behavior (behavior-notes (am): speedrunners use
dragon stepping to grant allies hit-invincibility — the hits are real). But
its ROM carrier is not in the per-borg hit bins: there is no record class, kind,
or damage value that distinguishes "contact" from ordinary persistent attack
volumes, and inventing one would fabricate per-borg data for 208 borgs.
Remaining candidate carriers, in order: (1) the shared `comhit.bin` global
table (256 records; layout verified vs zz_008ae60_, hit-bin-inventory.json)
— its records were not part of this sweep because the raw file lives in
user-data/ (absent from this checkout); (2) the unread per-object-type
dispatch (`PTR_FUN_802da740`, findings M caveat). The settling experiment
remains Q12's own: a T2 contact script (walk into / land on an enemy with a
dragon) logging hitbox spawns (`zz_008ac80_`/`zz_008ab30_` calls) and damage
events.

## Port consequence recorded for the next pass

`actionStreamData.ts` / `bridge.ts` currently map BOTH -1 and -2 records to
a TUNED `OPEN_WINDOW_ACTIVE_FRAMES = 8` window. Per the handler read above,
-2 = "rest of the arming animation" (the TUNED 8 is a bounded stand-in) and
-1 = "persistent across animations" (not an 8-frame window at all). The -1
records affected are shot/special arms, so the practical error today is in
special-move durations, not melee. Correcting the -1 handling is a separate
wiring slice that should be driven by per-kind arming context, not by this
note.
