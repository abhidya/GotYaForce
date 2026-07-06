# Title-intro residuals decode (2026-07-06)

Closes the two remaining static decode targets from
`title-intro-remaining-decode-2026-07-05.md` (§1 anim-bank ctor binding, §5 widget-table
stride). Both digs were run as parallel corpus/ROM agents and **every claim below survived
independent adversarial re-verification** (P1: 16/16 claims confirmed by BOTH a corpus lens
and a raw-bytes lens; P2: 8/10 confirmed, 2 consumer-attribution claims refuted and corrected
below). Full claim/evidence/verdict JSON: session workflow `wf_9213949b-b42`.

## 1. Family-ctor anim-bank binding (+0x1d80/+0x1d84/+0x1d88/+0x1d8c) — SOLVED

### 1.1 The ctor dispatch table (re-derived, matches commandMoveTables.json byte-exact)

`PTR_PTR_802d3224` @0x802d3224 = 16 family sub-table pointers indexed by the borg-id HIGH
byte (`*(char*)(actor+0x3e8)`); each sub-table indexed by the LOW byte (`+0x3e9`):

- family 0x00 sub-table @0x802d2e98; variants 0x00 (NORMAL NINJA pl0000) and 0x0a
  (SASUKE pl000a) share ctor **0x8006f4f8**
- family 0x06 sub-table @0x802d3008; variants 0x15/0x29/0x2a (G RED/NEO G RED/G BLACK)
  share ctor **0x8018ccfc** = `zz_018ccfc_` (chunk_0046.c)

**0x8006f4f8 is a Ghidra-missed function** (no `_index.tsv` boundary; `FUN_8006f4b8` ends
with `blr` at 0x8006f4f4; the ctor body runs 0x8006f4f8..0x8006f608). Read via raw PPC
disasm. Several stream-op handlers share this missed-boundary fate (op 0x02 @0x8004c424,
op 0x03 @0x8004c488, op 0x07 @0x8004c594, op 0x0b @0x8004c75c).

### 1.2 What each ctor binds

| field | NORMAL NINJA (0x8006f4f8) | G RED (zz_018ccfc_) | role |
|---|---|---|---|
| +0x1d80 | 0x802bde80 | 0x80366220 | family action-stream bank |
| +0x1d84 | 0x802bc080 | 0x802bcc64 | shared stream bank |
| +0x1d88 | 0x802bd780 | 0x80367460 | family anim-METADATA bank |
| +0x1d8c | 0x802bae60 | 0x802bb698 | shared metadata bank |
| +0x27c  | 0x802d4160 | 0x80365ec0 | family damage table |
| +0x4b0  | 0x802d3dc8 (SASUKE override: 0x802d3ee0) | 0x80365ac8 (0x62a override: 0x80365be0) | family descriptor |
| +0x4b4..+0x4f0 | 16-word copy from 0x802d3ad4 | 16-word copy from 0x80365538 | action vtable + tables |
| +0x4b4 | 0x8006facc (root action dispatcher) | 0x8018d24c (`zz_018d24c_`) | actionIndex dispatch |
| +0x4e8 | 0x802d3ca0 | 0x80365878 (0x62a: 0x803659a0) | sound-event table |
| +0x4ec | 0x802d4148 | 0x80365ea8 | (undecoded — open) |
| +0x4f0 | 0x802d3ff8 | 0x80365cf8 | cue→state table |
| +0x4ac | DAT_803c4d94[(s8)actor+0x3e7] | same | runtime per-instance ptr |

SASUKE (pl000a) differs from pl0000 ONLY in the +0x4b0 descriptor → **the whole pl0000
family port covers Sasuke for free**. NN ctor bank addresses match
`packages/combat/src/data/meleeAnimKinds.json` pl0000 byte-exact (independent cross-check).

### 1.3 Bank structure + the metadata layer (the previously-missing hop)

All four banks are two-level big-endian **s16 relative-offset** tables:
`groupTable = bank + s16 bank[group*2]`, `record = groupTable + s16 groupTable[slot*2]`.
Family banks have 7 group entries (group 6 = 0xffff invalid for both borgs); shared banks 4.
Offsets are signed — G RED's shared-bank entry[0] = 0xf424 aliases INTO the adjacent
NN shared bank region (0x802bcc64−0xbdc = 0x802bc088 = 0x802bc080+8).

`zz_004beb8_` selects +0x1d84 when groupSel bit7 set (index = groupSel & 0x7f), else
+0x1d80; groupSel==0 is replaced by the actor default-group byte +0x582 (op 0x02's b1
sets/toggles it: b1=-2 XOR bit0, -1 leave, else store — raw disasm 0x8004c424).

**The playAnim op's operands are NOT (group,slot)**: op 0x01/0x0d (handler `FUN_8004c298`)
reads record bytes b1=metaBank, b2=metaAnim, b3=mode (dispatches the 12-entry
`PTR_FUN_802d0d70` @0x802d0d70 mode-handler table), b4=blend, s16@+6=rate (substituted only
when the caller's rate < 0.0 — `FLOAT_804370f4`=0.0 compare). `zz_0048648_` hard-requires
+0x1d88 AND +0x1d8c non-null, then `zz_004d1f4_(actor, b1, b2)` resolves the metadata
record (identical two-hop s16 math over +0x1d88/+0x1d8c) and `zz_004d244_` parses it:

- 0x14-byte-stride records; per-part sections: part0 @rec[4], part1 @rec[0xc]
  (part2 @rec[0x14] / part3 @rec[0x1c] would exceed the 0x14 stride — these borgs' records
  carry parts 0/1 only; record size is table-derived, not fixed)
- each section: `motionFile byte, animInFile byte, flags (bits0-1 mirror-toggle, bit2)`
- motionFile bit7 selects own motion set (+0x1d78 = DAT_803c4d7c[+0x3e7], runtime .bss)
  vs shared set (+0x1d7c = DAT_80436254); `zz_004d548_` fetches
  `motionSet[fileByte&0x7f][animByte]` with lazy HSD_ArchiveParse caching; motion sets have
  0x10 file slots (`zz_004d63c_`)
- part0 hand-swap bytes rec[9]/rec[10] (negative → descriptor +0xbe/+0xbf fallback);
  op 0x07 (raw disasm 0x8004c594) does the same for +0x1d74/+0x1d75

### 1.4 THE ANSWER: groupSel=5 → the borg's own g0 motion file, EXCEPT slot 6

Family-bank **group 5** is the title-intro group. Its slot streams each play
`playAnim(metaGroup=5, anim=N)` — and metadata group 5 **identity-maps** anim N →
(motionFile 0, fileAnim N)… with one exception, identical for BOTH intro families:

| intro animId (slot) | stream bytes | resolves to |
|---|---|---|
| 0,1,2,3,4,5,7 | `01 05 0N` | **g0-file anim N** (identity) |
| **6** | `01 05 09` (G RED @0x803673f0, NN @0x802be8d2) | **g0-file anim 9** |
| 3 (extra) | `01 05 03 00 00 00 00 1e` | rate operand **30** (applied because the intro caller `zz_0057ff8_` passes rate = FLOAT_8043725c = −1.0) |

Battle group 0 is NOT identity (G RED meta g0: rec2→(0,6), rec3→(0,7), rec4→(0,8),
rec5→(0,9); slots 2/3 and 6/7 alias to shared streams/records) — so g0-file anims 2,3,4,5
are intro-only poses never referenced by battle group-0 streams, and the ROM battle jump
for G RED is g0 anim 8, not 6/7.

**Baked-file indexing PROVEN**: `apps/game/public/models/pl0000/` has `anim_g00_s14` +
`anim_g00_s23`, matching NN battle meta-g0 records (0,0x0e)/(0,0x17) exactly → the baked
`sNN` suffix IS the g0-file anim index (decimal). `anim_g00_s09_fly_transition.json`
exists for pl0615, pl0000, AND pl000a.

Intro-caller corroboration: `zz_0057ff8_`'s ONLY group-5 call site is chunk_0055.c:2669
(actor from the DAT_803c4e84 slot array); all other call sites pass group 0.

### 1.5 Port actions taken / implications

- **TitleIntro.ts `ANIM_FILES_BY_ID` upgraded TUNED→DERIVED** (this session): id 6 →
  `anim_g00_s09_fly_transition.json`; ids 2/5 added (valid ROM intro anims); the old
  "tdc00..09.arc pose banks are the canonical intro anim source" comment was falsified.
  Residual (labeled): id 3's rate operand 30 — unit unpinned, clips play at baked rate.
- **stream-vm.ts fidelity gaps identified** (for the ROM-runtime layer): (a) `tickPart`'s
  `actor.familyStreamBank` fallback mis-resolves shared-bank streams; (b) op 0x01's
  operands are surfaced to `onPlayAnim` as (group,slot) but are really (metaBank,metaAnim)
  — the +0x1d88 metadata hop is unimplemented; `RomActor.familyAnimDescBank/
  sharedAnimDescBank` fields already exist (actor.ts:136-137) but are never populated.
  Porting the metadata layer would replace per-borg hand-tuned anim-label tables.
- **meleeAnimKinds.json caveat**: its "g3/g4" group names are STREAM-bank groups; they map
  to motion files non-trivially via the metadata bank (G RED stream group 3 pulls motion
  FILE 1). Any consumer equating stream group N with motion file gN should be audited.

### 1.6 Open questions

- +0x4ec table (NN 0x802d4148 / G RED 0x80365ea8) — undecoded (in scope for the NN
  family-port dig).
- playAnim rate operand unit (30 = fps? multiplier×100? start frame?).
- Semantics of g0 anims 2,3,4,5,9 (labels are extractor guesses; ROM battle never
  references 2,3,4,5).
- Whether the intro script ever fires animIds 2/5 (both now mapped in the port anyway).

## 2. `DAT_80390ad0` widget table — stride 0x14, 98 rows, dumped

### 2.1 Layout (all DERIVED, byte-verified)

Walk loop `zz_01dd7d4_` @0x801dd7d4 (chunk_0058.c:1870):
`for (piVar1 = &DAT_80390ad0; -1 < *piVar1; piVar1 = piVar1 + 5)` → **stride 0x14**,
continue-while-non-negative; sentinel 0xFFFFFFFF @0x80391278 (+ zero-padded terminator
row). **Exactly 98 rows** (0x80390ad0..0x80391277). Row: `+0x00 s32 id (0..43)`,
`+0x04 u16 kind (0..20)`, `+0x06 s16 variant (−1..5)`, `+0x08/+0x0c/+0x10 f32 X/Y/Z`.
Copied per-row by `zz_01dd820_` into widget +0x144 / byte +0x11 / byte +0x12 /
+0x64..+0x6c (working) AND +0x148..+0x150 (pristine copy — fly-in mutates the working
one). Single corpus reader (grep-verified).

Dump: **`research/decomp/data/title-widget-table.json`** — all 98 rows' raw hex
byte-verified against an independent re-dump by the adversarial pass (0 mismatches).

### 2.2 Consumers (CORRECTED by the adversarial verify pass)

- Per-kind behavior dispatch = **`PTR_LAB_8039132c`** — exactly 21 entries (kind 0..20) at
  0x8039132c..0x8039137c, invoked from `zz_01dd9a4_` chunk_0058.c:1961; kinds 12/13 share
  a handler; kinds 0-3 handlers (0x801dda0c..0x801ddaec) are Ghidra decompile gaps.
- Text overlays: `zz_01de6e8_` switch on kind, cases 3/10/0xf/0x12. Variant is a sub-slot
  (text row Y, state-byte offset), and ALSO a decimal digit position in the number-widget
  path (chunk_0058.c:2606, powers-of-ten table @0x8039128c).
- **REFUTED original attributions** (recorded so nobody re-derives them wrong): the
  `PTR_FUN_80391658` resolver table (10 entries) and the 0x28-stride `DAT_803914d4`
  metadata belong to the SEPARATE `zz_01deb68_` widget family (its +0x11 is a call-site
  literal 1..9 subtype; `FUN_801def80` is unreachable from DAT_80390ad0 widgets). The
  +0xe0 drawable's setter for table widgets is untraced → **row id "model index" remains
  an open hypothesis**, not DERIVED.
- Bonus: `PTR_DAT_803912a4` (immediately after the table + powers-of-ten block) is a
  Shift-JIS string table = the six tribe names ("NINJA BORG"…"DRAGON BORG"), indexed by
  front-end state byte +0x4e.

### 2.3 Prior samples corrected

The 2026-07-05 doc's byte samples were partly bogus: −648.0 / −959.5 / 0x00020002 do not
exist in boot.dol (misaligned/mistranscribed reads); real values: −650.0 (rows 1-4 Y),
−2000.0/−3900.0/−4000.0 confirmed; 0x00010001 was a misaligned read spanning +0x02..+0x05.

### 2.4 Port implication

`spawnTitleWidget`/`setTitleWidgetMode` sinks can consume the JSON as the authoritative
placement manifest (position + kind + variant per row); keep a pristine-position copy per
widget like the ROM does. Rendering the real desk models additionally needs the per-kind
handlers decoded (kind histogram: 10×17, 17×15 dominate).
