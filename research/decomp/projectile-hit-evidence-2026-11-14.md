# Projectile HIT registration: bounded archive evidence

Date: 2026-11-14. Investigation base: `34e906f6eb5634167c3c6e3da3db3b4d03ffc965`.

The [fixed reader](../tools/matching-decomp/read_archived_projectile_hit_evidence.py)
authenticates complete `8008ac80`: **400 bytes /100 instructions**, plus four
independently justified typed selections totaling10 bytes. Exactly **five
additional reads /410 bytes** follow the unchanged whole-snapshot authenticator.
The [tests](../tools/matching-decomp/test_archived_projectile_hit_evidence.py)
contain manually authored operand fixtures and an independent inverse encoder.

Both existing snapshots agree on every selected instruction, value, hash,
mapping and physical span. This is **static archived ProgramDB evidence**, not
original-DOL identity, execution, `MATCH`, live dispatch, runtime integration,
asset hydration, successful collision or playability. No original code was
executed. No existing authenticator or allowlist was edited. The parent owns
runtime implementation separately.

## Independent selection basis

Before the first archive read:

- `ghidra-export/chunk_0013.c:1349–1415` names `8008ac80`, followed by
  `8008ae10`. `_index.tsv:1982–1983` independently corroborates both identities.
  Community map `research/symbols/GG4E-CSM-20220412.map:1089` assigns
  `8008ac80` size`190`; the next map row starts`8008ae10`. The selected complete
  code interval is exactly `[8008ac80,8008ae10)`. Its terminal return is
  independently authenticated at`8008ae0c`.
- That C body calls `88aa0(savedOwner,4,0x30,0,0)`. The second argument is the
  **pool**, not itself proof of an allocated record's type. `88d98`,
  chunk0012:6517–6540, indexes the unsigned16 size table with the saved signed
  object type: `DAT_802da660 + 2*type`. Type4 independently selects only
  **802da668/2**, not a guessed common object extent.
- `88aa0`, chunk0012:6364 onward, selects classification byte
  `DAT_802da700[group]`. Requested group48 independently selects exactly
  **802da730/1**. This direct group applies when its owner-remap predicate
  does not hold. It is not a substitute for the ordinary actor remap.

A separate second selection was justified before reading it:

- Mode0 constructor `88398`, chunk0012:5996–6072, sets its configuration
  pointer to `802da670 + mode*24`, with eight signed type bytes followed by
  eight u16 capacities. Mode0/pool4 therefore selects exactly **802da674/1**.
  Constructor identity is corroborated by index1945–1946 and map1058–1059.
  The value4 confirms the type4 size selection for this mode/pool. No pool4
  capacity or adjacent configuration field was read. Ordinary battle mode0
  selection has existing C provenance in the separate
  [allocator evidence](object-allocator-evidence-2026-11-14.md).
- For owner83==0, nonnull owner and group48, authenticated allocator `88aa0`
  remaps to **signed owner3e4 +49**. `536b0`, chunk0006:6528–6555, initializes
  actual main-actor slot3e4 starting0 and loops while slot<6. Index1029 and
  map681 corroborate this constructor. These six initialized slots0..5
  independently select only **802da731/6**, classifications for groups49..54.
  This is not a domain claim for arbitrary corrupted/synthetic slot values.

The constructor/slot-initialization bodies are C provenance, not newly
instruction-authenticated here. Returned values never select further reads.
Discovery scripts and their decoded reports are isolated under ignored
`.tmp/projectile-hit-evidence-20261114`; the durable reader uses only literal
addresses, widths, types and hashes. No HIT table source identity was established,
so no remap bytes, HIT row payload, owner3fc contents, callback body or pointed-to
memory is selected. `8008a65c` is a stored callback identity only.

## Authentication, mappings and selected values

| Snapshot | Whole-file SHA-256 |
| --- | --- |
| db.3.gbf | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| db.4.gbf | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Unchanged `read_archived_constants.inspect` verifies the actual complete file
hash, schemas, language/address maps, empty File Bytes and existing data5
identity/controls. Unchanged `command.mappings` verifies text1/data3/data5
identities, subblocks and overlap constraints before all five selections.
File Bytes version0/root−1/count0; image offset80000000; block size16384;
master root1. Executable metadata SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is not an independently measured original-DOL hash.

- text1: `[800055e0,802b0160)`, length2796416, block/subblock1, chain root21.
- data3: `[802bae60,803af120)`, length1000128, block/subblock5, chain root199.
- Both mappings are initialized subblock type2 with zero starting/source offset.

| Selection | Width | Typed value | SHA-256 |
| --- | --- | --- | --- |
| 8008ac80 | 400 |100 decoded instructions | `88d16df3bda187ed3cb011269a356a7d0646ca1c946dcd194664a5abf4a317d0` |
| 802da668 | 2 | u16 type4 size448 (`1c0`) | `32444d1ca2314b6449d98ed53575e1d1dca3e826e1d622fee4502e355a21dd85` |
| 802da730 | 1 | i8 group48 classification26 (`1a`) | `58f7b0780592032e4d8602a3e8690fb2c701b2e1dd546e703445aabd6469734d` |
| 802da674 | 1 | i8 mode0/pool4 type4 | `e52d9c508c502347344d8c07ad91cbd6068afc75ff6292f062a09ca381c89e71` |
| 802da731 | 6 | i8 groups49..54:26,26,26,26,26,26 | `e605937264e19250f2777c6c637c32f173428ed770f4f9a2134eb52ef2c21e24` |

Physical provenance below is decimal; each read uses the unchanged obfuscated
ProgramDB chain reader. Both snapshots have identical spans. No selection
crosses a data-buffer boundary.

| Selection | Root /buffer | Chain offset | Data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| 8008ac80 | 21 /55 | 546464 | 5990 | 923500 | 400 |
| 802da668 | 199 /207 | 129032 | 14386 | 3422264 | 2 |
| 802da730 | 199 /207 | 129232 | 14586 | 3422464 | 1 |
| 802da674 | 199 /207 | 129044 | 14398 | 3422276 | 1 |
| 802da731 | 199 /207 | 129233 | 14587 | 3422465 | 6 |

## Exact source order and integer behavior

All PCs and field offsets below are hexadecimal. `child` is original r3;
`kind` is original r4. `hit` is an actual nonnull record returned by`88aa0`,
not a supplied success flag. Address arithmetic, shifts and integer additions
use PPC32 results; stores truncate to their named widths. No host pointer or
array normalization is justified by these instructions.

### Entry and saved identities

1. `ac90/94` retain child and full32-bit kind. `ac98` sets success0. `ac9c`
   loads **child90 once into saved owner r31**. Null owner branches through
   `aca8` (r3=0), `acac -> adfc`, then returns. It performs no27c copy or table
   read and calls no allocator.
2. Nonnull: `acb0` loads owner27c; `acb4` computes `(kind <<2) mod2^32` with
   `rlwinm`. `acb8` sets count0; `acbc` stores child27c. **Only afterward**
   `acc0` loads owner3fc into the asset base register.
3. `acc4` retains `assets+aa0` as HIT-row base r29. `acc8/cc` retain cursor
   `assets+a20+(kind<<2)` in r30, then `acd0` jumps to condition`ade4`.
   These bases and saved owner are not recomputed after any allocation.

### Condition and allocation failures

- `ade4` loads the cursor byte, `ade8` sign-extends it and sets CR. `adec`
  exits when it is negative. **Only then** `adf0` compares signed count with4,
  and `adf4` loops if count<4. Thus count4 still causes a **fifth condition-byte
  read/sign-test** after four attempts, although a fifth allocation cannot run.
  A missing fifth byte is a read boundary before normal function return, not
  permission to reorder the count guard.
- Loop`acd4` passes saved owner, then`acd8/ace4` set args`(4,48,0,0)`.
  `ace8` calls`80088aa0`. No other call or indirect call exists in this body.
- `acec/f0` test the returned pointer; null skips all per-hit stores and goes
  to`addc`. Both success and null outcomes increment cursor at`addc` and count
  at`ade0`, then retry the condition. An allocation failure does not end the
  loop and does not reset an earlier success. Existing allocator effects,
  including failure-side effects, must not be rolled back by this caller.

### Successful hit prefix and late owner/remap reads

1. `acfc` stores hit00=1. `ad04` stores hit0c=`8008a65c`; `ad08` stores
   hit20=child; `ad0c` stores low8(kind) to hit14. The full kind32 selected the
   remap cursor; truncating it before the shift would be wrong.
2. `ad10` **reloads child90 after allocation and these stores**. If nonnull,
   `ad1c` stores that value to hit24. If null,`ad24` loads child8c and`ad28`
   stores it instead. This late ownership field can differ from the saved
   owner used for allocation and asset selection.
3. `ad2c` **reloads the current cursor byte after allocation**,`ad30`
   sign-extends it,`ad34` multiplies by80 (`50`),`ad38` adds the retained HIT
   base, and`ad3c` stores the resulting row pointer to hit28. The condition's
   earlier byte is not cached. If intervening effects changed it to negative,
   this row computation still uses the newly signed negative value; there is
   no second nonnegative check here.

### Child83 and joint-pointer branches

- `ad40/44` load and sign-test child83. Nonzero takes`ad94/98`, storing
  **child+114** to hit60, then joins at`ad9c`. It performs no row01,
  child1cec/1ced loads and no hit4c store.
- Zero83: `ad4c` loads **unsigned** row01;`ad50` tests bit80. Bitset stores
  **child+1aa4** to hit60 at`ad58/5c`. Bitclear computes unsigned row01×48,
  adds8d4 then child, and stores hit60 at`ad64–70`.
- Both zero83 branches join at`ad74`, which loads **child1cec first**.
  `ad78` loads **child1ced second**. `ad7c/80` sign-extend each;`ad84` shifts
  signed1cec left12 as32-bit arithmetic;`ad88` adds signed1ced;`ad8c` stores
  the low16 result to hit4c. This is not unsigned packing or reversed reads.

### Common success suffix and result

1. `ad9c`: hit5c=self. `ada0/04` prepare1/0;`ada8` sets retained success1.
2. `adac` **reloads child27c**, then`adb0` stores it to hit2c. Do not reuse
   the initial owner27c value across the allocator or intervening stores.
3. `adb4` loads row04 as **u16** (`lhz`);`adb8` stores low8 to hit11.
   `adbc` loads row06 as **i16** (`lha`);`adc0` stores low16 to hit48.
   `adc4` loads row08 as **i16**;`adc8` stores low16 to hit4a.
4. `adcc` stores child86=1, then`add0` stores child1d8=0.
5. `add4` **reloads the cursor byte again**, after those child stores;
   `add8` stores it to hit12. It can differ from the signed row-selection byte
   under aliasing. Then cursor/count advance and condition evaluates again.
6. At normal nonnull-owner completion`adf8` moves retained success to r3;
   the epilogue does not replace it;`ae0c` returns. Result is0 for no successful
   allocation,1 after at least one normal success. The original null-owner
   path returns explicit0 without running`adf8`.

This complete body authenticates ordered accesses, not the mappedness or
identity of any actual HIT payload. If a runtime reaches a missing row/remap
read, it must preserve preceding real effects and report the boundary. It may
not fabricate HIT assets, skip reloads, reorder checks, or treat lack of data
as a successful return. Alias-sensitive reads are precisely why the registers
and load/store schedule are retained in the inverse fixtures.

## Verification and claim ceiling

Completed locally without installs, fetching snapshots, executing original
code or importing disputed estimator code:

```
python -m unittest discover -s research/tools/matching-decomp -p test_archived_projectile_hit_evidence.py -v
python research/tools/matching-decomp/read_archived_projectile_hit_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf
python research/tools/matching-decomp/read_archived_projectile_hit_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf
```

**13 tests pass.** They cover all100 independently inverse-encoded instruction
operands/hashes;3200 one-bit decoder controls;3280 payload-bit refusals; frozen
branch/load/store schedules; exact five-read traces after unchanged
authentication in both archives; physical provenance; schema, hash, mapping,
width, type, duplicate, target and CLI refusal controls. Fixture exports
`EXPECTED`, `BODIES`, `PAYLOADS` are authored independently, not populated by
loading the reader's output. Complete decoded derived reports are
`.tmp/projectile-hit-evidence-20261114/db3.json` and`db4.json`.

Real pool4 type/size and seven reached classifications are now evidenced, but
pool initialization/capacity, HIT source assets, callback8008a65c behavior,
collision/damage and later projectile matrix/flight behavior remain outside
this evidence slice. Synthetic free lists and HIT rows must stay explicitly
synthetic; source metadata is not proof that a live allocation succeeded.
