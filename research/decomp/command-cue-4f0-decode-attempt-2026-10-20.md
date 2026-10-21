# actor+0x4f0 command-cue → script (group, slot) decode attempt (2026-10-20)

Round-2 wiring pass, item #6 residual: try to decode the mapping that would
resolve combo ladders for the borgs the seed-chain pass leaves unresolved.
**Verdict: the chain is now fully mapped and every link is evidenced — but
the final link's DATA does not exist in the repo for 202 of 208 borgs, and
the alternate data source (mot event tracks / DOL banks ≥ 2) needs the
disc extraction in user-data/, which is absent. No code changed; coverage
is unchanged. The dead ends below are the deliverable — do not re-try them
without new artifacts.**

## Coverage baseline (measured 2026-10-20, current main)

`comboLadderForBorgId` over the 208-borg roster: **91 borgs with a full
3-step ladder, 13 with 2 steps, 4 with 1 step, 100 with no resolved
ladder.** (The "108/208 resolved" figure from earlier passes counts any
borg with ≥ 1 step.) The 100 zero-step borgs include the whole dragon
family (pl0500-pl0516), pl0004, and most of families 01/03/08/09/0c/0d/0e/0f.

## The chain, link by link

1. **BorgRuntime / actor+0x4f0 is an action-descriptor STREAM POINTER, not
   a (group, slot) table.** Writers: family ctors (e.g. `zz_018ccfc_`
   chunk_0046.c:4807-4817) and `FUN_80057b78` (chunk_0007.c:933). The
   command layer copies the current command record's descriptor pointer
   into it: `FUN_8006adb0` (chunk_0009.c:1170,1179-1193,1213-1217). The
   descriptor at +0x00 carries the cue id (`zz_0067980_` reads it,
   chunk_0009.c:1699-1704).
2. **Cue → action request:** descriptor cue ids feed `zz_005f188_`
   (chunk_0007.c:6061-6102), which writes `+0x5e4 = cueId`,
   `+0x590 = 1` — an action REQUEST. The cue byte `+0x5dc` is adjusted per
   phase in `FUN_8005a378` (chunk_0007.c:2887-2898).
3. **Cue → (group, slot):** `FUN_800699d8` / `FUN_80069a50` /
   `FUN_80069ad0` (chunk_0009.c:1303-1547) scan the actor's cue-script
   stream (base `+0x1d80`, stride 0x2c, modes at +0x00, match target at
   +0x28) and resolve the cue through per-family CUE TABLES: 8-byte rows
   (cueId, stateTarget) at `actor+0x4ec + cueId*8 + 4`, stored by family
   ctors (`zz_018ccfc_` chunk_0046.c:4812-4817; ninja `FUN_80072094`
   chunk_0009.c:4091-4092). The resolved (group, slot) then selects the
   action bank — banks at actor+0x1d80/+0x1d84, indexed
   group*0xb4+slot*0x0c (chunk_0006.c:1702, `FUN_8004c21c`).
4. **(group, slot) → HIT kind:** bank op-0x0a events call
   `zz_008ac80_(actor, kind)` — already extracted as `meleeAnimKinds.json`
   hitKinds, but WITHOUT the (group, slot) each kind was armed from.

So the port's framing in `meleeExactData.ts` ("the +0x4f0 state chain is
undecoded") is imprecise: +0x4f0's role is decoded; what's missing is the
per-cue resolution DATA (link 3→4 joined per borg).

## Why the decode cannot land from repo data

- **Cue tables exist for 6 borgs only** (`familyCueTables.json` /
  `familyCueTablesFull.json`: pl0000, pl000a + 4 others). The other 202
  borgs' tables live in the DOL at ctor-written pointers that were never
  dumped; the generator that produced the six needs the disc image.
- **meleeAnimKinds extraction covers banks 0/1 only**
  (`scripts/gen-melee-anim-kinds.mjs` BANK_COUNT = 2). Kinds ≥ 16 in the
  data (e.g. pl0615 arms kinds 16-31) come from literal code sites, not
  from bank arms — so for most borgs the SECOND bank's (group, slot)
  attribution is absent by construction.
- **The ladder resolver doesn't consume (group, slot) anyway:**
  `actionStreamData.ts` `comboLadderForBorgId` walks variant seeds from
  `commandMoveTables.json` and accepts steps via `stepFromKind`, which
  requires a kind with a usable hit window AND a family damage record.
  A cue decode would have to replace the seed-walk's kind ordering — the
  seeds' (group, slot) provenance is exactly what's missing.

## Dead ends tried (do not repeat)

1. Treating +0x4f0 as a (group, slot) table — refuted: it's a stream
   pointer (link 1).
2. Extending the 6 extracted cue tables by family — the tables are stored
   per-ctor with family-specific pointers; the ninja family's other 11
   borgs (incl. pl0005, pl0009 — both unresolved) have NO table in the
   extraction and no corpus site binds one for them.
3. Using kinds ≥ 16 as second-bank ladder rungs — the arms exist
   (pl0615: 14 such kinds) but there is no ordering evidence tying them
   to combo steps; adding them would fabricate ladders.
4. Recovering (group, slot) from `meleeAnimKinds.json` animSounds keys
   (`g<group>s<slot>`) — those keys exist for SOUND events; the generator
   did not emit the same attribution for op-0x0a HIT events. (This is the
   cheapest future fix: re-run the generator emitting (group, slot) per
   hitKind — but the generator reads user-data/ disc files.)

## What would unblock it

Either (a) Manny's disc extract in `user-data/` (same artifact class as
the #9 reaction-clip blocker): re-run `gen-melee-anim-kinds.mjs` with
bank coverage ≥ 2 and (group, slot) attribution, and dump the remaining
families' cue tables from boot.dol ctor pointers via the existing
binding-scan pattern; or (b) a T2 trace logging `+0x5e4` cue ids and
`zz_008ac80_` kinds per B-press for a sample of unresolved borgs (one per
family would generalize furthest). Until one lands, the 100 zero-step
borgs keep the TUNED combo profile by design.
