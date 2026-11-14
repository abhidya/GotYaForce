# Actor cue0 tail: archived source evidence

## Result and scope

The dedicated fixed reader represents **all 159 instructions** in the five
selected cue0-tail helpers and `800694c0`, the predicate actually called by
`800696f4`. Both authenticated local ProgramDB snapshots agree on every
instruction, operand, digest and physical trace. No prologue, epilogue, branch,
early return or other selected instruction is omitted.

Artifacts:

- [Fixed reader](../tools/matching-decomp/read_archived_actor_cue0_tail_evidence.py).
- [Operand and refusal tests](../tools/matching-decomp/test_archived_actor_cue0_tail_evidence.py).
- C cross-reference: `ghidra-export/chunk_0009.c:40-116` for `696f4` and `69814`;
  `ghidra-export/chunk_0008.c:5033-5107` for `68f9c` and `69038`, and
  `chunk_0008.c:5252-5346` for `69354` and `694c0`.
- Symbol map: `research/symbols/GG4E-CSM-20220412.map:804,806`.

**Only `80069038` and `800694c0` have symbol-map rows.** The other four extents
come from the C entry/next-function markers and authenticated final returns,
not invented map rows. The reader lists the five tail helpers in requested
caller order, followed by the direct predicate, but does not independently
authenticate the caller that sequences them. It does not read the intervening
functions or treat the gaps between fixed spans as authenticated coverage.

This is archived source evidence, not unchanged original-DOL identity, live
input, table/pointer/actor ownership, gameplay parity, production integration,
or a complete actor tick. `8006a750` remains an external callee boundary in
this reader. The separate existing reader/integration evidence for that callee
is not upgraded by these six spans. Global pointer and table contents are not
read, and no original or archived instructions are executed.

## Authentication and exact extents

The existing local inputs are
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

The unchanged shared `read_archived_constants.inspect` authenticates the
complete snapshot, exact schemas, executable metadata, big-endian
Gekko/Broadway language, address map, empty File Bytes table, complete data5
hash and existing controls before new reads. Unchanged
`read_archived_command_evidence.mappings` validates exact text1/data3/data5
mappings and all-block nonoverlap. Each new read must match a unique fixed
address/width tuple, root, alignment, bounds, byte count and SHA-256 before
any instruction is decoded. Unselected forms and the checked reserved comparison/sign-extension/SPR fields
fail closed; fixed-span hashes authenticate every remaining operand.

- Executable import-metadata SHA-256:
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  Import metadata alone does not prove unchanged executable bytes.
- File Bytes: version 0, root -1, count 0.
- Block size 16384, master root 1, image offset `80000000`.
- Text1 starts `800055e0`, length 2796416, block/subblock 1, chain root 21.
- All selected text reads use subblock type 2, starting/source offsets 0.
- Data5 digest:
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

| Fixed span | Bytes / instructions | SHA-256 | Map size | Final return |
| --- | --- | --- | --- | --- |
| `80069814..80069860` | 76 / 19 | `6478aa8c8825200e8c8f76a5acf49557a4b072133aff0a5e3c92c420e64aba43` | absent | `8006985c` |
| `800696f4..80069788` | 148 / 37 | `463b8c6883bc8126accbd12fb96d2e5a4315091838f60eea1ff534186ebe061b` | absent | `80069784` |
| `80069038..800690a0` | 104 / 26 | `ae221bab2b247c6b93b71e3d53262eca37909b891ea1706369f34c43b30348b4` | `0x68` | `8006909c` |
| `80069354..800693fc` | 168 / 42 | `85e858e503b2379916a3acf16d04d426d3bdd35ddc46c1e52bb9e945a88414d8` | absent | `800693f8` |
| `80068f9c..80069000` | 100 / 25 | `bb4d4cc7160149270e06ced78a6b825a09a354b65b189a9076c8c980f6664f2d` | absent | `80068ffc` |
| `800694c0..800694e8` | 40 / 10 | `e980d963242e2be1f9873a510c776a99d7a4848dbf56f6541653328f0c7a1194` | `0x28` | `800694e4` |

Physical provenance is identical in both snapshots. Root buffer is 21 and
storage is obfuscated; offsets and lengths below are decimal.

| Entry | Data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| `80069814` | 47 | 410164 | 714 | 787152 | 76 |
| `800696f4` | 47 | 409876 | 426 | 786864 | 148 |
| `80069038` | 46 | 408152 | 15080 | 785134 | 104 |
| `80069354` | 46 | 408948 | 15876 | 785930 | 168 |
| `80068f9c` | 46 | 407996 | 14924 | 784978 | 100 |
| `800694c0` | 46 | 409312 | 16240 | 786294 | 40 |

## Exact source schedules

Actor offsets and source PCs below are hexadecimal. All accesses are reached
only after earlier conditions pass; a later boundary does not erase earlier
stores. `lwz` loads a 32-bit word, `lbz` an unsigned byte, `lhz` an unsigned
halfword, and `lha` a signed halfword. `stb` and `sth` retain the low 8 or 16
bits. All equality comparisons use 32-bit `cmpi` (`BF=0,L=0`). All selected
branches have `AA=0`, conditional branches also have `LK=0`; their signed
16-bit displacement differs from the signed 26-bit `b`/`bl` displacement.

### `80069814`: ordered table ownership and always-zero return

1. `69814`: load actor byte `88` into r0.
2. **Before sign extension or multiplication**, `69818` loads a word into r4
   from `r13-31852` (`r13-0x7c6c`). The C export associates this load with
   `PTR_DAT_80433934`. The bounded machine evidence authenticates the
   r13-relative operand, not a live r13 value, global pointer or table owner.
3. `6981c`: sign-extend the retained byte `88`. `69820`: multiply it by `0x3c`.
   `69824`: add that product to the retained pointer. This is a signed-byte
   index, so negative byte values must not be silently interpreted as 128..255
   or clamped to zero. The reader does not follow the calculated address.
4. `69828`: load one byte at calculated base `+103`. `6982c` sign-extends it
   with the record bit. Nonzero branches to `6983c`; zero returns 0 through
   `69834/69838`, without reading actor `5d4`.
5. `6983c`: load word `5d4`. Mask `200` clear returns 0 through
   `69848/6984c`. If set, store byte `6fb=6` at `69854`, then return 0 through
   `69858/6985c`.

There are no calls. All three returns are genuinely zero, including the
store path. Missing global/table ownership is a boundary before the table
byte is known; it must not become a fabricated zero test or skipped call.

### `800696f4`: retained mode byte, predicate, then cue `20`

1. `69708`: load byte `661` once; `6970c` sign-extends it. Compare that same
   retained value with 2 (`69710`) and, if unequal, 5 (`69718`). If neither
   matches, return 0 without reaching `694c0`, `5e0` or `5d4`.
2. `6972c`: call `800694c0` with the retained actor. Zero result returns 0.
   The predicate must happen **before** either input-word read below.
3. `69740`: load word `5e0`; nonzero mask 3 returns 0.
4. `69754`: load word `5d4`; mask `80` clear returns 0.
5. `69764`: set r4 to `20`; `69768`: call `8006a750` and propagate its entire
   returned word unchanged, rather than normalize nonzero to 1.

There are no actor stores in this helper. The apparent repeated `661`
expression in C does not mean a second source load.

### `800694c0`: genuine signed-halfword predicate

1. `694c0`: load byte `7cd`; `694c4` sign-extends it with record bit. Zero
   returns 1 immediately at `694cc/694d0`, without reading `736`.
2. Otherwise `694d4` performs **one** signed halfword load from `736` into r3.
   `694d8` negates it into r0; `694dc` computes r0 AND complement of retained
   r3. `694e0` rotates left 1 and selects bit 31 in PPC MSB-zero numbering,
   extracting the previous sign bit. `694e4` returns that 0/1 value.

This equals `signed16(736) > 0`, not `736 != 0`, `736 >= 0`, or an unsigned
comparison. The synthetic test checks the formula for all 65536 signed
halfword values. The C expression mentions the halfword twice; the source
machine schedule loads it only once. `7cd=0` avoids even this one load.

### `80069038`: store-before-cue `4`

1. `69044`: load word `5e0`; mask 2 set returns 0.
2. `69058`: load word `5d4`; mask 1 clear returns 0.
3. `6906c`: load word `5b4`; mask `100` clear returns 0.
4. `69080`: set r0=0; `69084`: set r4=4; `69088`: store byte `57c=0`.
5. **After that store**, `6908c` calls `8006a750`. Propagate its full word
   return unchanged. If the callee is unavailable, the reached store remains.

A zero already present at `57c` does not erase this separate source store.
There is no `661` or descriptor load in this helper before the cue boundary.

### `80069354`: cue `c`/`25` and two separate success reloads

1. `69368`: load word `5e0`; mask 1 set returns 0.
2. `6937c`: load **unsigned halfword** `5d8`; mask `f0` clear returns 0.
3. `69390`: load byte `661` once; `69394` compares its zero-extended value
   with 6. No `extsb` is present here; equality with 6 is unaffected by that
   signedness distinction. Equal selects r4=`25` (`693b4`) and calls
   `8006a750` at `693b8`. Unequal selects r4=`c` (`6939c`) and calls at `693a0`.
4. Either call's zero result returns 0 **before** any success reload/store.
   Any nonzero result reaches `693cc`; it is normalized to return value 1.
5. `693cc`: **reload** unsigned halfword `5d8`, after the call. `693d0` sets
   return r3=1. `693d4` rotates retained value left 28 and masks its low nibble,
   equivalent to `(value >> 4) & f`. `693d8` stores that byte to `58f`.
6. `693dc`: **load `5d8` again, after the `58f` store**. `693e0` applies the
   wraparound PPC mask `MB=28,ME=23` (`ffffff0f`). `693e4` stores its low
   halfword to `5d8`, clearing only `f0` from that fresh halfword.

Do not reuse the pre-call halfword for either success action, or reuse the
first success reload for the second. The call or a source-backed memory
adapter may make the distinction observable. Do not perform either success
store when the cue returns zero or has not completed.

### `80068f9c`: cue `1`/`1d`

1. `68fa8`: load word `5e0`; mask 2 set returns 0.
2. `68fbc`: load word `5b4`; mask `f0000` clear returns 0.
3. `68fd0`: load byte `661` once, zero-extended; `68fd4` compares to 6.
   Equal selects r4=`1d` (`68fe8`) and calls `8006a750` at `68fec`.
   Unequal selects r4=1 (`68fdc`) and calls at `68fe0`.
4. Propagate the full returned word unchanged. There are no actor stores.

This helper does not share or reuse the earlier helper's `661` read. The
source call sequence must decide whether this helper is reached at all.

## PPC mask audit

`rlwinm` uses MSB-zero bit numbering; masks are not conventional LSB indices.
All selected `Rc=1` masks feed CR0 zero/nonzero tests. `BO=12,BI=2` branches
on equality/zero and `BO=4,BI=2` on inequality/nonzero.

| PC | SH / MB / ME / Rc | Mathematical mask or selected result |
| --- | --- | --- |
| `69840` | 0 / 22 / 22 / 1 | `200` |
| `69744` | 0 / 30 / 31 / 1 | `3` |
| `69758` | 0 / 24 / 24 / 1 | `80` |
| `69048`, `68fac` | 0 / 30 / 30 / 1 | `2` |
| `6905c`, `6936c` | 0 / 31 / 31 / 1 | `1` |
| `69070` | 0 / 23 / 23 / 1 | `100` |
| `69380` | 0 / 24 / 27 / 1 | `f0` |
| `693d4` | 28 / 28 / 31 / 0 | `(unsigned16 >> 4) & f` |
| `693e0` | 0 / 28 / 23 / 0 | wraparound `ffffff0f`, stored halfword `ff0f` |
| `68fc0` | 0 / 12 / 15 / 1 | `f0000` |
| `694e0` | 1 / 31 / 31 / 0 | extract prior bit 31, the numeric sign bit |

The final row names numeric bit 31 for the pre-rotate sign bit; the mask's
`ME=31` names PPC bit 31, the numeric low bit after rotation. These conventions
must not be conflated.

## Verification and refusal coverage

Executed against both local archives, with no skips:

```text
python -m unittest discover -s research/tools/matching-decomp \
  -p test_archived_actor_cue0_tail_evidence.py -v
Ran 17 tests ... OK

python -m unittest discover -s research/tools/matching-decomp \
  -p 'test_archived_actor_*evidence.py'
Ran 236 tests ... OK

git diff --check
# clean
```

The explicit expected operand listing contains every one of the 159
instructions, including stack accesses, register assignments, branch targets,
CR fields, record bits and all early returns. Separate tests check physical
traces, actual map absence/presence, C marker extents, nonstack memory order,
cue arguments, signed predicates, retained values and wrapping masks.

Negative tests reject modified/truncated/extended ranges before decode,
wrong or duplicate tuples, arbitrary pointers, non-integer fields, wrong
roots, unselected opcodes, reserved fields and unselected SPR forms. Whole
snapshot/schema and exact mapping failures occur before any new read. Tests
also cover absent arbitrary address/width/raw/execution CLI flags and the
unchanged shared allowlists. Output contains derived operands and provenance,
never raw executable bytes.

No installs, commits, publication, original execution, runtime pointer
following or private telemetry access were performed for this evidence.
