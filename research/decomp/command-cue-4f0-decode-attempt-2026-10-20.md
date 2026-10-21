# actor+0x4f0 command-cue decode attempt (2026-10-20, CORRECTED same day)

Round-2 wiring pass, item #6 residual. **This note was rewritten within the
day: its first merged version relied on an interim census that misidentified
what +0x4f0 holds and where the ladder gap lives. The corrected findings
below are from a full site census plus first-hand spot checks
(`zz_006a750_` at chunk_0009.c:859-880; `familyCueTablesFull.json` family
count = 119).**

**Verdict: the +0x4f0 layer is already fully decoded and fleet-extracted —
and it provably cannot supply the missing (group, slot) data, because the
cue layer carries zero slot information. The ~100 unresolved ladders fail
at three downstream links, none of them +0x4f0. No code changed; coverage
is unchanged.**

## Coverage baseline (measured 2026-10-20, current main)

`comboLadderForBorgId` over the 208-borg roster: **91 borgs with a full
3-step ladder, 17 partial (13×2 steps, 4×1 step), 100 with no resolved
ladder** (108 with any ladder).

## What +0x4f0 actually is (census of all 30 corpus hits; 24 actor-relevant)

- A pointer, bound **only in family ctors** (13 explicit sites, e.g.
  chunk_0046.c:4805 for G RED; most families bind it implicitly via the
  16-word descriptor block copy into actor+0x4b4..+0x4f0), to a static
  **96-byte cue→state-pair table**: 48 entries × 2 bytes
  `[fullBodyState, upperBodyState]`, −1 = no transition.
- Its only runtime readers are `zz_006a6fc_` / `zz_006a750_` /
  `zz_006a7b4_` / `zz_006a7f4_` (chunk_0009.c:840-911), which translate a
  cueId into the actor's current/previous body-state bytes
  (+0x5da/+0x5db, +0x5dc/+0x5dd) and reset the phase bytes. A handful of
  fixed-offset probes read individual cue bytes as capability checks
  ("borg lacks this move" if −1).
- The data is **fully dumped**: `familyCueTablesFull.json` — 119/119
  families, 115 distinct table addresses; attack cues 44 and 45 map to
  [61, 0] in **119/119** families. ⚠️ The older `familyCueTables.json`
  (17 borgs, `scripts/extract-family-cue-tables.mjs`) is **corrupt**
  (wrong addresses, float-bit garbage entries) — do not use it; the Full
  file supersedes it.

## The B-press → script chain (all links DERIVED unless marked)

1. Pad bits → transformed input word +0x5d4 (port: command.ts).
2. Tester priority → command type +0x585 (`FUN_800699d8`, chunk_0009.c).
3. Subtype/direction stage (+0x586/+0x587) via `zz_0069dd0_`.
4. Command record selection in `zz_006a104_`: 4-byte records
   **[cueId, stateMode, actionIndex, variantIndex]** from `actor+0x4ec`
   tables — extraction complete (`commandMoveTables.json`, 208/208).
5. **Cue → state pair via +0x4f0** (`zz_006a6fc_` unconditional;
   `zz_006a750_` when stateMode == 3). Attack cues 44/45 → [61, 0]
   fleet-uniformly. **This is the only link +0x4f0 participates in.**
6. Per-frame state dispatch (`FUN_80055568`): state 61 = `FUN_80065dfc`
   = the +0x4b4 family virtual — the only one of 0x50 state slots that
   calls it.
7. Family dispatch: +0x4b4 root → action table (+0x580) → variant table
   (+0x581) → leaf (117 distinct roots walked by the extractor).
8. Leaf → engine → **config seed (+0x6ea)** → stream call `zz_004beb8_`.
   Combo re-arms auto-increment +0x6ea. **MISSING for 342/2540 leaves
   (85 of them action-1)** — the emulator captured no stream call.
9. Stream resolution in `zz_004beb8_`: group bit7 → shared bank +0x1d84,
   else family bank +0x1d80; stream = bank + group/slot offset words.
10. Hit arming: stream op-0x0a → `zz_008ac80_(actor, kind)` → hit.bin
    remap → family damage records (the join meleeAnimKinds.json +
    attackHitTables.json already encode).

## Why the 100 null ladders are null (partition, sums to 100)

| Bucket | Count | Nature |
|---|---|---|
| No action-1 entry in actionStreamTables | 51 | command records never enumerate (a=1, ·) |
| Action-1 v0 exists but group = null (leaf captured no stream call) | 40 | link-8 extraction gap |
| v0 seed is runtime-conditional (`slotCandidates`) | 3 | pl0205 {0,3}, pl0209 {0,11}, pl0706 {0,6} |
| v0 seed resolves but step-0 stream arms no kind | 6 | windup/code-driven openers |

Reframing that matters: by each borg's base type-1 command record,
(1,0) = 45 borgs, **no type-1 records at all = 36**, (0,0) = 18,
(2,0) = 1. For those 55 borgs there is **no action-1 B-close path in the
ROM's own tables** — their B-close routes to the dash action (0), the
air/charge action (2), or isn't a type-1 command. They should stop
counting as "unresolved melee": no ladder exists to resolve.

## Dead ends — approaches the evidence rules OUT

1. **Decoding (group, slot) from the +0x4f0 cue table.** Information-
   theoretically impossible: cue 44/45 = [61,0] in 119/119 families while
   the 108 resolved borgs exhibit 26 distinct ladders. Zero discriminating
   information past state 61.
2. **Seeding ladders from non-baseline type-1 variants.** Would "improve"
   41 borgs (33 to full 3 steps), but the subtype→variant map in validated
   families (0→0, 1→2, 2→3, 3→1, 4→4, 5→0) shows variants 1-4 are
   context alternates (air/dash/landing), not combo steps. Fabricates data.
3. **Bank-only heuristic (first 3 hit-bearing g3 slots).** Validated
   against the 91 known full ladders: exact match only 66/91 (73%).
4. **Param-fill for bank-less leaves.** The 22 "param" leaves are two
   phase-table DISPATCHER engines (`zz_01613fc_` chunk_0042.c:14-21;
   `zz_010b2f4_` chunk_0030.c:1136-1143), not param-seed engines; the
   extractor's "param" config is an artifact. Fill changed coverage by 0.
5. **`familyCueTables.json`** as a source — corrupt (above).

Also validated-but-zero-gain: replacing the resolver's hardcoded
(action 1, variant 0) with each borg's base type-1 record reproduces
106/106 resolvable ladders and gains 0 nulls — a relabel, not a decode.

## The actual fundable gap (link 8, specific engines)

The two phase-dispatcher engines above cover **17 borgs' v0 leaves**
(pl0100 cluster ×5 via `zz_01613fc_`; pl0300 cluster ×12 via
`zz_010b2f4_`). Their phase-0 seed setters (`FUN_8016144c` /
`FUN_8010b344`) write the seed from an argument whose origin the Ghidra
text export does not show, and their phase-≥1 stream plays
(`zz_004beb8_(…, group 3, +0x6ea++)`) sit behind timer/contact forks the
emulator didn't traverse. Supplying artifacts, either suffices:

1. **boot.dol** (`user-data/GG4E/disc/sys/boot.dol` — absent from this
   workspace): dump the phase tables 0x8034c6a8 / 0x80325a68 and extend
   `gen-action-stream-tables.mjs` to walk phase-table dispatchers and
   the ~21 pointer-config engines with uncaptured v0 leaves. Ceiling:
   ~40 group-null + 3 slotCandidate borgs.
2. **A T2 trace** per attack-mechanics-trace-plan.md §T2: per-frame log
   of +0x540, +0x6ea, and `zz_004beb8_` (group, slot) args during a
   standing B-mash, one representative borg per unresolved engine family.

One cheap code fix independent of both: the `parseBank` sentinel-walk
bug in `gen-melee-anim-kinds.mjs` truncates bank 0x80327440, dropping
pl0402/pl0408 g3 s3..s7 — fixing it addresses part of the 8 "nostream"
partial-ladder stops (the generator still needs user-data/ to re-run).
