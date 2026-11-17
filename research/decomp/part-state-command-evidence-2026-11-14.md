# Actual part-state commands and ordinary command prefixes

Date: 2026-11-14. Evidence baseline: `db84380b`.

This checkpoint authenticates both actual opcode02/03 bodies, all46 selected
instructions and operands, and the ordinary ground28/air32 command prefixes
through their first wait. It is static archived ProgramDB evidence, not original
execution, bank-selector hydration, an executed parser, or a playable clone.
The reader and tests do not change any shared reader or allowlist.

## Reproduction and authentication

Reader: `research/tools/matching-decomp/read_archived_part_state_command_evidence.py`.
Tests: `research/tools/matching-decomp/test_archived_part_state_command_evidence.py`.

From `research/tools/matching-decomp`:

```sh
PYTHONDONTWRITEBYTECODE=1 python -m unittest -v test_archived_part_state_command_evidence.py
PYTHONDONTWRITEBYTECODE=1 python read_archived_part_state_command_evidence.py \
  '../../decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
PYTHONDONTWRITEBYTECODE=1 python read_archived_part_state_command_evidence.py \
  '../../decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

Both snapshots independently pass the unchanged base reader's whole-file SHA,
GBF/schema/language/ProgramDB metadata, File Bytes, address-map, complete data5
hash and established constant controls before the six selected reads. The
existing command reader is reused **only for mapping validation**, never its
table or handler reads. Text/data3 mappings are then checked exactly.

| Snapshot | SHA256 |
| --- | --- |
| db.3.gbf | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| db.4.gbf | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Both report boot.dol/Ghidra12.1.2, image base80000000, block size16384,
master root1, and File Bytes version0/root−1/count0. The executable SHA metadata
is `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
The reused whole-data5 hash is
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
Import metadata plus agreeing snapshots do **not** prove unchanged original-DOL
bytes, live dispatch, hardware behavior, or numerical parity.

| Mapping | Start..exclusive end | Block/subblock | Length | Chain root |
| --- | --- | --- | ---: | ---: |
| MAIN_.text1 | 800055e0..802b0160 | 1/1 | 2796416 | 21 |
| MAIN_.data3 | 802bae60..803af120 | 5/5 | 1000128 | 199 |

Each selected mapping uses subblock type2, starting offset0 and source offset0.
Existing base/command checks still validate data5 and reject overlaps, duplicate
block/subblock identities, changed image bases, roots, lengths and offsets.
There are no new data4 selections or checks in this focused reader.

## Independent selection basis

| Literal selection | Bytes | Independent extent/start basis |
| --- | ---: | --- |
| 8004c424..8004c488 | 100 | [Earlier handler inventory](anim-sound-op-decode-2026-07-04.md) names02 atc424 and03 atc488. Exact bounded adjacent-handler interval, not a larger decompiler span. Returns atc434/c474/c47c/c484. No C-body or symbol-map size claim. |
| 8004c488..8004c4dc | 84 | [Earlier control audit](stream-control-reachability-2026-11-12.md) explicitly records84 bytes throughc4d8; earlier handler inventory names04 atc4dc. Returns atc498/c4b4/c4d8. No C-body or symbol-map size claim. |
| 802be5ee..802be602 | 20 | [Double source-X report](double-ninja-source-x-2026-11-12.md) and existing `meleeAnimKinds.json` identify the ordinary ground stream start independently. This initial selection contains01,02 and only the first4 bytes of03. |
| 802be602..802be60a | 8 | Ground start plus three8-byte records and wait4, independently supported by the generator format/size set and the existing Ninja schedule. Finishes03 and selects the first wait. |
| 802be656..802be66a | 20 | Same independent sources identify the ordinary air stream start. Again only the first4 bytes of03 are in the initial20. |
| 802be66a..802be676 | 12 | Same record-size basis plus documented air08/4 before the wait4. Finishes03, then08, then wait. |

`scripts/gen-melee-anim-kinds.mjs:18–25,184` documents the8-byte01/02/03
records and4-byte other records. Its02/03 event extraction uses the same
`partState` label for distinct raw opcodes. Those event names do not establish
two opcode02 calls or4-byte state records. The file is read as an independent
format witness only; the generator is not run and no original executable is
opened.

The already authenticated command-table witness is reused, not reread:
802d0da0/72, SHA256
`fdf7c34d3ce203b91e168f8ea7ce7873e7140b5dbf1a6d5cb1710cbe868d260e`,
from `read_archived_command_evidence.py`. The earlier handler inventory records
02→8004c424 and03→8004c488. No selected address is obtained by following that
table or any newly read pointer.

## Exact selected hashes and physical provenance

| Address/width | SHA256 |
| --- | --- |
| 8004c424/100 | `be8ac95c75902d94a0afcbb214ac797ca8f501e0676336d015a424da509cc839` |
| 8004c488/84 | `f0408efcd1b500c334e09862a1a4f0209c4aab0205b2184750565a043cbe6eb3` |
| 802be5ee/20 | `14f850a2bf4697c92ac063e5b35fe68f5b54892c8653dd313e53fe3903ebdff6` |
| 802be602/8 | `8666d68f6b5964c5f8b774f3c4d2046a920342700c737366062abbd4c7841918` |
| 802be656/20 | `6186d688a629f42df51983a88011287bc65c8e74133aa53f5f7f67d32adeadfa` |
| 802be66a/12 | `5053f080e446d14bbd04be06873b151c6dea341ac08b390863cf98ea957bdfad` |

Each selected window lies in one obfuscated chain span; both snapshots produce
the same physical trace. Offsets and lengths below are decimal.

| Address | Root/data buffer | Chain offset | Data offset | Length | Physical offset |
| --- | --- | ---: | ---: | ---: | ---: |
| 8004c424 | 21/39 | 290372 | 11946 | 100 | 667312 |
| 8004c488 | 21/39 | 290472 | 12046 | 84 | 667412 |
| 802be5ee | 199/200 | 14222 | 14222 | 20 | 3307412 |
| 802be602 | 199/200 | 14242 | 14242 | 8 | 3307432 |
| 802be656 | 199/200 | 14326 | 14326 | 20 | 3307516 |
| 802be66a | 199/200 | 14346 | 14346 | 12 | 3307536 |

Only semantic numeric record fields are emitted, including every padding byte,
signed operand and unsigned control halfword, with per-record hashes. No raw
whole-window dump is emitted. Separate20-byte and continuation selections are
retained in the inventory even though pure bounded decoding joins each pair.

## Exact static prefixes

| Ground address | Bytes | Record fields |
| --- | ---: | --- |
| 802be5ee | 8 | 01: group4, slot0, mode1, transition6, byte5=0, signed start0 |
| 802be5f6 | 8 | 02: b1=ff/−1; b2/b3/b4/b5/padding6/padding7 all0 |
| 802be5fe | 8 | 03: state byte1=0, auxiliary byte2=1, unused3/4/5=0, unsigned control halfword0040 |
| 802be606 | 4 | 00: mode2, signed wait2 |

| Air address | Bytes | Record fields |
| --- | ---: | --- |
| 802be656 | 8 | 01: group4, slot1, mode1, transition6, byte5=0, signed start0 |
| 802be65e | 8 | Same02 operands as ground |
| 802be666 | 8 | Same03 operands as ground |
| 802be66e | 4 | 08: bytes1/2=0, signed byte3=1; handler **not** selected/admitted |
| 802be672 | 4 | 00: mode2, signed wait1 |

There is no wait inside either initial20-byte selection. The first wait ends
the selected prefix, not the entire stream. Later continuation bytes and all
family command-bank group/slot offset headers remain unselected. The separate
animation-metadata bank is not a substitute for those command-bank headers.
Any fixture using synthetic selector scaffolding must still label it as such.
Reached uncovered reads must refuse instead of consuming invented zero bytes.

## Opcode02 exact ordered effects

Stackless, no calls. r3 is the actual actor, r4 the caller's part mask, r5 the
parser-local cursor address. The command is8 bytes regardless of the mask.

1. c424 loads the old record pointer into r6; c428 tests numeric mask1.
   c42c/c430 advance and store the cursor by8. c434 returns when mask1 is clear,
   before any operand loads or actor destinations are needed.
2. c438/c43c load unsigned record byte2 and byte-store actor1cef, part0+1b.
   c440/c444 do byte3→1cf0, part0+1c. c448/c44c do byte4→6e8.
   c450/c454 do byte5→6e9.
3. Only then c458 loads byte1 into r4 and c45c sign-extends it for comparisons.
   fe/−2 loads current582, XORs1 and byte-stores582 before returning atc474.
   ff/−1 returns atc47c without reading or writing582.
   Every other byte stores the original unsigned r4 to582 and returns atc484.

The actual prefix therefore writes part0 state0/aux0 and6e8=6e9=0 while
preserving the genuine Double prehook's582. Overwritten582 values need not be
read or validated on the ordinary non-sentinel path. Nothing here writes584.
Part-state stores are authored choreography, not evidence of collision or a hit.

## Opcode03 exact ordered effects

Same r3/r4/r5 convention; stackless, no calls, always8 bytes.

1. c488 loads the old record pointer. c48c tests numeric mask2. c490/c494
   advance/store the cursor by8. c498 returns if mask2 is clear.
2. c49c/c4a0 load byte1 and store actor1d0f, part1+1b; c4a4/c4a8 load byte2
   and store1d10, part1+1c. ff is an ordinary stored byte, not a state sentinel.
3. c4ac reads unsigned BE16 record+6; c4b0/c4b4 compareffff and return if equal.
   This skips only the control update: both earlier state stores remain.
4. c4b8 loads actual5e0; c4bc masks it withfffff00f; c4c0 performs the **first**
   actual controlWord store.
5. c4c4 reloads record+6; c4c8 reloads the now-current actual5e0. c4cc masks the
   reloaded operand with0ff0; c4d0 ORs it into the reloaded owner; c4d4 performs
   the **second** actual controlWord store. c4d8 returns.

The actual prefix writes part1 state0/aux1 and sets the controlled bit range to40.
The historical final-value expression `(old & 0xfffff00f) | (operand & 0xff0)`
does not preserve the observed two-store/read order. A source runtime must allow
the intervening fresh reads and retain the first store if a later reached action
fails; it must not cache both operands and collapse the stores.

All four conditional returns are exact word4d820020, BO12/BI2/BH0/LK0. The three
unconditional returns are4e800020, BO20/BI0/BH0/LK0. Every selected instruction,
including all non-return operands, has an independent frozen test schedule and
inverse encoding that reproduces the complete body hashes.

## Next-frame route and remaining limits

Ground opcode03 sets actual control bit40 after phase0's ground work and slot
selection. In the current otherwise unchanged composed Double fixture, both
cues remain44. On the next full55568 frame, normal59068 runs before the Double
prehook, saved-state capture and action dispatch. Its cue44 path captures40 and,
when genuine699d8 then69814 return0, reaches **80059d18→80069210** before phase1.
The [existing X-playback evidence](actor-x-playback-evidence-2026-11-14.md)
already authenticates that call order. Clearing40, changing the cue, skipping
normal59068 or forcing helper returns would bypass rather than resolve it.
Different demonstrated inputs may short-circuit earlier;69210 is the present
composition's next boundary, not a claim about every possible actor.

Air must refuse at its reached08 until the actual handler is admitted. Its known
8004c5fc/128 interval is not read here. Neither air's later wait nor ground's
first completed command prefix establishes integrated phase1 or clone behavior.

This focused reader promotes six already prepared selections. The scratch-only
`phase-one-entry-preparation-20261114` work separately authenticated ten windows
and93 instructions, including phase1, its dispatch cell, callback pointer and
threshold. Its `REPORT.md` SHA256 was
`718e556e767df0ed3dcf469ea3e1e14f6c8b3b02930da8c3d134f66412576635`.
Its `authenticate_fixed_windows.py`, `db3.json`, `db4.json`, `manifest.json` and
`test_preparation.py` supplied preparation provenance, not dependencies of this
repository reader. This checkpoint does **not** reread or claim to implement
the four omitted selections. The preparation also identified the8020bb14
general-motion magnitude boundary and actual715f8 callback, plus conditional
b22f4 afterimage work. No zero-motion fabrication, null callback replacement,
or numerical approximation is licensed by this prefix evidence.

## Verification

The focused suite passes17 tests, including both real local snapshots with no
skips. It checks all46 instruction operands, every single-bit decoder mutation
for exact rejection or reversible changed fields, all seven return sites,
all60 payload bytes and per-record reconstruction, exact six-window pins,
physical spans, mappings, whole-authentication order and unknown-address CLI
refusals. Every selected byte is individually tampered and rejected. Real
archive SHA spoofing and each selected archive payload mutation also refuse.
Instrumented real reads prove there is no command-table/header/phase1/opcode08
read: beyond the unchanged base data5 controls, exactly two text and four data3
literal reads occur.

The focused suite plus existing constants, command, normal-actor and Double
evidence suites passes77 tests. Both snapshot CLI invocations also succeed and
report46 instructions, prefixes28/32 and `read_here: false` for the reused table
witness. The command-evidence regression uses synthetic fixtures, not a new
archive command-table read.

These are evidence-reader tests, not runtime execution tests. No TypeScript
source, original asset, emulator, live actor, browser state, remote branch or
shared-reader allowlist is changed by this evidence work.
