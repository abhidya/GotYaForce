# Gotcha Force borg animation banks — full enumeration

> **Goal:** enumerate EVERY animation in each borg's `pl****mot.bin` (not just
> idle/move) — death, victory, damage-react, knockdown, attacks — and bake them so
> the web recreation has the full move set.
>
> **Status (2026-07-01):** DONE for the priority set. 363 clips baked across 7 borgs.
> Bank counts are **measured** (exact). Index→action labels are **inferred by
> heuristic** (group/slot convention shared across borgs, anchored by a handful of
> human-verified pl0615 clips). The decomp does **not** give a concrete bank table —
> see §"Decomp cross-reference" for what it does and doesn't tell us.

## File format: two-level bank table

`pl****mot.bin` is **not** a flat list. Big-endian throughout:

```
0x00 .. 0x40    MASTER TABLE: 16 × u32 group-table offsets (0 = group absent)
each group table: u32 BLOB offsets, terminated by 0xFFFFFFFF.
                  A 0 entry = "this action slot is empty for this borg" (a hole).
each non-zero blob: a self-contained HSD DAT whose roots are HSD_AnimJoint trees
                    (one root per model sub-part / JOBJDesc, ~20 roots; root 0 =
                    main body, parallel to the model's JOBJ skeleton).
```

So a bank is addressed by **(group, slot)**. The slot index is meaningful and
**consistent across borgs** — it is effectively a shared action-id. Empty slots
(holes) prove the slot axis is an enum, not a packed list. The previous exporter
(`scripts/export-borg-animation-hsd.mjs`) flattened all blobs into one sorted set
and lost the group/slot structure; the new tool
(`user-data/GG4E/borg-anim-allbanks/`) preserves it.

Parser/baker: `user-data/GG4E/borg-anim-allbanks/Program.cs` (HSDRaw, modes
`manifest` and `bake`). Driver: `scripts/bake-all-borg-anims.mjs`. Interpolation is
the proven HSDRaw `FOBJ_Player.GetValue` path (hermite-correct, see
`hsd-animation-semantics.md`) — identical sampler to the original idle/move baker.

## Measured bank counts (EXACT)

| Borg | Name | mot size | banks | groups present (count) |
|------|------|----------|-------|------------------------|
| pl0615 | G RED | 355,264 | **55** | g0(13) g1(23) g2(0) g3(12) g4(5) g5(2) |
| pl0102 | Gatling Gunner | 407,232 | **68** | g0(19) g1(8) g3(23) g4(5) g5(4) g6(9) |
| pl0802 | Gold Hero | 308,864 | **54** | g0(18) g1(13) g2(0) g3(15) g4(5) g5(3) |
| pl0500 | Flame Dragon | 247,392 | **33** | g0(12) g1(5) g3(3) g4(6) g5(1) g6(2) g7(1) g8(3) |
| pl0109 | DEATH BORG BETA | 330,080 | **41** | g0(15) g1(19) g3(3) g4(2) g5(2) |
| pl0008 | DEATH BORG ALPHA | 368,160 | **56** | g0(14) g1(10) g2(3) g3(18) g4(5) g5(6) |
| pl000c | DEATH BORG ALPHA II | 368,160 | **56** | g0(14) g1(10) g2(3) g3(18) g4(5) g5(6) |

(pl0008 DEATH BORG ALPHA and pl000c DEATH BORG ALPHA II do not have standalone
`pl0008mot.bin` / `pl000cmot.bin` siblings in the AFS root, but their MOT members
are present as member 003 inside `pl0008.pzz` / `pl000c.pzz`. Use
`scripts/extract-pzz-members.mjs --borg pl0008,pl000c --member mot` before baking.)

Group 2 is always present in the master table but always empty (0 non-zero slots)
for humanoid borgs — a reserved category.

## Group semantics (inferred)

| Group | Meaning (confidence) | Evidence |
|-------|----------------------|----------|
| 0 | **Core locomotion / movement** (idle, walk, dashes, jump, turn) | Longest-looping clip is g0s0; g0 slots 2–5 carry ±300/±200u root translation = directional dashes (verified). |
| 1 | **Attack moveset** | Many 31–56f clips; some carry forward root-Z motion = lunge attacks; pl0615's human-labeled `attack_arm` = g1s21. |
| 2 | reserved / empty | always 0 non-zero slots on humanoids. |
| 3 | **Damage reactions / guard** | short 12–16f, no root motion; pl0615's human-labeled `hit_flinch` = g3s1. Longer g3 (36f) = guard/block. |
| 4 | **Special / long actions** (knockdown, big moves) | 26–81f; pl0615's `down_candidate` (knockdown) = g4s0 (81f). |
| 5 | **Death / victory (finishers)** | the longest non-looping clips in the file (pl0615 g5s1=181f, pl0109 g5s1=161f). |
| 6–8 | extra weapon/flyer-specific groups | only on some borgs (pl0102 gun-mode g6; pl0500 dragon-flyer g6–g8). |

## Slot convention (Group 0, EXACT frame counts)

Consistent slot→action across borgs (frames vary by borg, semantics don't):

| Slot | Action (confidence) | pl0615 | pl0102 | pl0802 | pl0500 | pl0109 |
|------|---------------------|--------|--------|--------|--------|--------|
| 0 | **idle** (longest loop, no root motion) | 61 | 117 | 141 | 256 | 117 |
| 1 | **move / walk** (loop) | 33 | 33 | 33 | 81 | 33 |
| 2 | **dash forward** (root +Z) | 25 | 36 | 39 | 51 | 37 |
| 3 | **dash back** (root −Z) | 25 | 36 | 39 | 70 | 37 |
| 4 | **dash left** (root +X) | 25 | 36 | 39 | 40 | 37 |
| 5 | **dash right** (root −X) | 25 | 36 | 39 | 111 | 37 |
| 6 | jump takeoff (short) | 11 | 11 | 5 | 121 | 12 |
| 7 | jump land (short) | 11 | 11 | 20 | 61 | 12 |
| 8 | turn | 13 | 61 | 35 | 30 | 38 |
| 9 | fly/air transition | 21 | 25 | 16 | 61 | 22 |
| 14/24 | 2-frame pose (T-pose / placeholder) | 2 | 2 | 2 | — | 2 |
| 23 | boost | 37 | 69 | 32 | — | 23 |

The **dash** identification is the strongest non-trivial result: g0 slots 2–5 are
the only group-0 clips with large root translation, and the magnitudes are
±300u (pl0615) scaling to ±600u (pl0109), with Z for fwd/back and X for left/right.
This was independently confirmed by the prior human-labeled `boost_forward`
(=blob 0x3680 = g0s2, +300 Z).

## DEATH and VICTORY banks (the gap this addresses)

These are the win/lose/death animations that were **absent from any RAM snapshot**
and only live in the asset banks. Best-guess per borg (label them as triggers for
the game's win/lose/hit logic):

| Borg | DEATH (bank) | VICTORY (bank) | notes |
|------|--------------|----------------|-------|
| pl0615 G RED | **g5 s1** `anim_g05_s01_death.json` (181f) | **g5 s2** `anim_g05_s02_victory.json` (46f) | death = single longest clip in the file. |
| pl0109 DEATH BORG | **g5 s1** `anim_g05_s01_death.json` (161f) | g5 s0 `win_or_death` (71f) | death = longest clip. |
| pl0102 Gatling | g5 s1 `death` (46f) | g5 s2 `victory` (46f) | also g5 s0 (40f), g5 s3 (58f) finishers. |
| pl0802 Gold Hero | g5 s1 `death` (41f) | **g5 s2** `victory` (95f) | victory is unusually long (hero pose). |
| pl0500 Flame Dragon | (no g5 s1) | g5 s2 `victory` (61f) | flyer; death likely in g4/g8 — **lower confidence**. |

Group 3 = damage/hit reactions (knockback, flinch). Group 4 = knockdown / "down"
and other big special actions. These are the banks the game should trigger on
**hit** (group 3) and **heavy hit / launch** (group 4).

## Decomp cross-reference — honest status

**Update (2026-07-01, behavior-notes.md §4r):** `0x80066ec0`/`0x80066f1c` (+
`0x800670dc`) have now been fully decompiled and are **not** animation-request
helpers at all — they're a heading/turn-rate interpolator (divide a remaining
turn angle by a step count, then apply one step per call). The "Likely an
animation/action request" guess below was wrong; there is no mode→(group,slot)
dispatch table to find in these three functions. This doesn't change any of the
bank-label confidences below, but it does mean nobody should keep chasing these
three addresses looking for the death/victory mode constants — see §4r for the
full correction and what it fixed instead (a real bake-script mislabeling bug:
group-4 slot-0 was tagged as a generic `special_s0` instead of the knockdown
pose, which was already identified as high-confidence `down_candidate` right
below — see "Baked output" section for the fix applied to already-baked
`anim_index.json` files and `apps/game/src/main.ts`'s slot-matching).

The decomp (`research/decomp/behavior-notes.md`) located anim-request helpers
`0x80066ec0` (`(borg, int mode)`, "Likely an animation/action request", observed
mode constants 2/0xf/0x10) and `0x80066f1c` ("apply/advance current action"), and
the central state enum at struct `0x544`. **But it does NOT decode a concrete
mode→(group,slot) table** — the mode constants were not traced to specific banks,
and HP/death wiring is an explicit open gap. So:

- **EXACT / measured:** bank counts, (group,slot) addressing, frame counts,
  animated-joint counts, root-motion spans.
- **Cross-referenced (high confidence):** idle=g0s0, move=g0s1, dash=g0s2–5
  (root-motion-confirmed + matches prior human `boost_forward` anchor), hit=g3,
  knockdown=g4s0 (matches prior human `down_candidate` anchor).
- **Inferred / heuristic (medium confidence):** death=g5s1 (longest non-looping
  clip), victory=g5s2, attack=g1. These follow the Melee/HSD action-bank convention
  (locomotion-first, status/finishers last) but are **not** confirmed against the
  decomp's mode constants.
- **Lower confidence:** flyer/special borgs (pl0500) whose group layout differs;
  per-slot attack labels within group 1.

To upgrade death/victory from inferred→confirmed: trace what writes state `0x544`
on death and which `mode` `0x80066ec0` is called with in that path — that is the
remaining decomp work.

## Baked output

For each priority borg, every non-empty bank is baked to
`apps/game/public/models/<id>/anim_g<GG>_s<SS>_<label>.json` (same schema as the
existing idle/move clips: `frameCount`, `fps:60`, `rotFormat:quat_xyzw`, `bones[]`
with per-frame `pos`/`rot`/`scl`), plus an `anim_index.json` listing every bank's
group/slot/label/frames/animJoints/root-spans.

| Borg | clips baked |
|------|-------------|
| pl0615 | 55 |
| pl0102 | 68 |
| pl0802 | 54 |
| pl0500 | 33 |
| pl0109 | 41 |
| pl0008 | 56 |
| pl000c | 56 |
| **total** | **363** |

Re-bake any borg: `node scripts/bake-all-borg-anims.mjs <plId> GG4E`.
Inspect any mot without baking: `dotnet user-data/GG4E/borg-anim-allbanks/...
manifest <mot.bin> <model.arc> 0x100`.

**Group-4-slot-0 mislabel fixed (2026-07-01, behavior-notes.md §4r):** the bake
script's `label()` tagged every group-4 bank `special_s<slot>`, including slot 0 —
even though this file's own cross-reference table above already lists `g4s0` as
high-confidence **knockdown** (`down_candidate` anchor), not a special move. That
meant `apps/game/src/main.ts`'s `PREFERRED_LABELS` overrides for pl0615/pl0008/
pl000c/pl0105/pl0109 pointed their "special" animation slot at the knockdown pose,
and the `down` combat state had no real match and fell back to a hit/death clip.
Fixed: `scripts/bake-all-borg-anims.mjs`'s `label()` now emits `down_s0` for group
4 slot 0 specifically (all other group-4 slots still `special_s<N>`); all 101
already-baked `apps/game/public/models/*/anim_index.json` files that had a
`special_s0` group-4-slot-0 entry were patched in place to `down_s0` (bone/keyframe
JSON files unchanged — only the semantic label string, so no re-bake was needed);
`main.ts`'s `SLOT_LABELS.down`/`PREFERRED_LABELS` were updated to match. The 5
affected borgs' "special" overrides now point at `special_s1` instead.
