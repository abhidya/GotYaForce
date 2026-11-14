# Archived actor-frame suffix evidence, 2026-11-14

## Scope and ceiling

This is **static evidence from two existing archived Ghidra ProgramDBs**.
The new fixed reader authenticates all 128 instructions in three complete
suffix functions, two constructor source cells and one scalar. It does not
execute archived instructions, follow pointers, select sound-table payloads,
capture telemetry or establish original-DOL identity, live state, numerical
parity, complete actor frames/actions, integration or browser playability.

The key hydration finding is that Double's constructor source for actual
actor `soundEventTable4e8` is **nonnull `802d3ca0`**, not zero. The function's
null return is real but cannot be substituted for this constructor value.
Four synthetic `auxiliary37 = -1` values likewise do not prove retail sound
hydration. No sound-event payload is selected here.

## Authentication and fixed boundaries

`read_archived_frame_suffix_evidence.py` invokes the unchanged shared
authenticator before selecting new bytes. This checks the actual whole-file
SHA-256 against the two fixed snapshots, exact table schemas, Program name,
Gekko/Broadway language, Ghidra version, executable metadata value and type,
empty File Bytes table, address map, complete data5 hash and known scalar
controls. It then applies existing strict text1/data3/data5 mapping checks,
including image offset, block/subblock identities, lengths, source roots,
offsets, types, bounds, ambiguity and overlapping mappings.

| Snapshot | Whole-file SHA-256 |
| --- | --- |
| `db.3.gbf` | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| `db.4.gbf` | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Stored executable SHA-256 remains import metadata. The empty File Bytes table
does not supply an original executable for independent comparison. Complete
data5 SHA-256 is
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

All new selections are independent literals, never derived from decoded
pointer values. No shared allowlist changes. The CLI accepts only a snapshot
path; address, width, target, follow, raw and execute switches are rejected.
Every instruction operand, including condition-register, record, overflow,
branch-link and branch-hint fields, is explicit. Unsupported instructions,
conditional-return fields, changed span hashes, partial spans and non-call
branches outside their fixed span fail closed before a result is returned.

| Entry | Bytes / instructions | End exclusive | Map size | SHA-256 |
| --- | --- | --- | --- | --- |
| `8006f88c` | 72 / 18 | `8006f8d4` | absent | `680c0ec8c71efb08c8f58d754022ce70e08256402c7a34562baa55330e614ab1` |
| `80055ee4` | 172 / 43 | `80055f90` | `ac` | `f9d106d64326e759fd9b72a619c6bde22a12cc53c0c1a7da4ae9e8f1d40c0ca2` |
| `8005b880` | 268 / 67 | `8005b98c` | `10c` | `4a8f527b8d258953b38ad46c1e5681e3ce20354bc56c7540349d7d2e91660832` |

`55ee4` has adjacent C markers at
`ghidra-export/chunk_0006.c:8129–8167`, independently agreeing with map
row690. `5b880` has adjacent markers at
`ghidra-export/chunk_0007.c:3579–3628`, agreeing with map row717.

`6f88c` has **no exported C body/marker and no map row**. Its start was
independently named as the omitted posthook before this selection. Prior
authenticated prehook `6f7c0` is 204 bytes and ends immediately at `6f88c`.
The next named C marker is `6f8d4` in chunk0009:4121. The new 72-byte span
contains all instructions through terminal `blr` at `6f8d0`, and its direct
branch is internal. This establishes the complete bounded posthook witness;
it is not a claimed map-derived size or newly recovered C export.

## Constructor cells and scalar

The prior independently authenticated constructor `8006f60c/252` supplies
the source-base and copy evidence. Its `6f610/6f618` instructions construct
base `802d3b14`. Loads/stores `6f638/6f63c` copy source+`c` to actual actor
`4c0`; `6f688/6f68c` copy source+`34` to actor `4e8`. Both copies are
regression-checked against both snapshots through the unchanged normal
reader. A constructor producer is not proof of a current live actor.

| Fixed cell | Role | Value | Cell SHA-256 |
| --- | --- | --- | --- |
| `802d3b20` | constructor posthook4c0 | `8006f88c` | `db31181abe0ba833169a9c38254008f88804c913fb1a6376e648cea6661e1229` |
| `802d3b48` | constructor soundEventTable4e8 | `802d3ca0` | `35a3a289b82d0f1c8bec13375bc8f3374fe8355be59fc72bef4277dd84a81e8d` |

New scalar `80437298` has f32 bits `40000000`, exactly 2.0, and SHA-256
`c31425b44a7ed682a3356bf6820141e1584a15c43b6d6793f552e5d4621586f7`.
Its `55f18` load uses recorded r2=`8043ea20` plus displacement -30600.

The sound-loop conversion bias `804373d0` is a reference to the unchanged
actor-rotation evidence, not a new selection: eight bytes
`4330000080000000`, exactly `2^52 + 2^31`. The focused tests reauthenticate
that fixed prior scalar in both snapshots. Its `5b92c` displacement is
-30288 from the same recorded r2. These bases are previously recorded
values, not a fresh startup or live-register capture. Bounded host arithmetic
requires finite values/results and separately stated FPSCR RN=0, NI=0
preconditions; the archived reader does not establish those live settings.

## Complete posthook `8006f88c`

1. Load fresh actor control5e0. `rlwinm` mask MB=ME=6 tests `0x02000000`.
   If set, store byte7c8=0; if clear, skip that store.
2. Load **signed** short3e8 and compare with10. Conditional LR return
   at `6f8a8` has BO=4, BI=2: return when not equal.
3. Load byte6e9, sign-extend with record, then conditional LR return at
   `6f8b4`, BO=4, BI=1: return when signed value is **not greater than0**.
   A negative value is not an admitted increment merely because it is nonzero.
4. Load unsigned byte6ec, add1, and store byte6ec. Reload the stored byte,
   mask its low two bits, and store byte6ec again. These are two ordered
   stores, not an instruction witness for one combined modulo update.
5. Return at `6f8d0`.

No callee or sound payload is reached by this posthook. Its first store may
already have occurred when either conditional return is taken.

## Flags/size suffix `80055ee4`

Order and signedness matter:

1. Read fresh control5e0; rotate/mask extracts bit6 and stores
   attribute.byte87=`(control5e0 >> 6) & 1` before reading the size policy.
2. Read byte8cc and sign-extend. Signed value1 writes byte1eb=0. Signed
   value0 takes the scale test. Every other signed value writes byte1eb=1.
3. Scale-test load order is actor sizeScale7fc, modelScaleb4, scalar2.0.
   One single-precision `fmuls` precedes `fcmpo product, threshold`.
   Ordered product <2 writes1 to byte1eb; product >=2 writes0. This prose
   uses the finite-value precondition, not an invented NaN behavior.
4. **Reload** control5e0 after the byte1eb branch. Mask MB=ME=2 tests
   `0x20000000`; set writes byte276=1, clear writes0.
5. Read byte7c9 and sign-extend with record. If zero, conditional LR
   return at `55f7c`, BO=12, BI=2. Otherwise load signed short272, OR its
   register with65535, and store the resulting low halfword `ffff` to272.
6. Return at `55f8c`.

Fields8cc,1eb,276 require explicit ownership in any composition. Missing
values are not an authorization to default them. The source contains
observable reads even where the resulting store's value is independent of
the old value, such as the signed272 load before OR65535.

## Reused ordinary-frame order `80055568`

The new reader does not select the ordinary frame again. Its prior complete
292-byte actor-mode1 evidence and frozen full-operand witness establish:

- Markers are **2 → 1 → 0 → 2**, with both signed table selectors captured
  before the upper-body call.
- Position words20,24,28 are captured before the prehook call, after the
  earlier frame prefix. They are not transform history or post-action values.
- Following full-body return, set marker2, load actual posthook4c0 and call
  through it at `55630`; call `55ee4` at `55638` next.
- Only then read fresh control5e0. If bit`0x40` is set, skip restore without
  loading byte598. If clear, read signed byte598; zero skips restore.
- The restore uses the earlier captured words, with stores20,24,28 in
  exactly that order. There is no recapture after the action.
- Call `5b880` at `55670`. Genuine return from that call is required before
  the ordinary frame epilogue and return at `55688`.

This schedule alone does not authorize clearing host ownership, epochs or
failure latches. It also does not make later action phases complete.

## Sound gate and loop `8005b880`

The function first loads actual pointer4e8. A zero value branches directly
to its epilogue, without reading row metadata. The authenticated Double
constructor source is nonzero, so that return cannot stand in for actual
Double sound-table hydration.

For a nonnull table, rows start at actor+`1ad4`, advance by`40`, and are
visited in order0,1,2,3. Each row's byte37 is sign-extended and compared
with -1. Exactly -1 skips the event loop. Other negative values are not
treated as sentinels or bounds-checked by this witness.

For an admitted row, the function **reloads actual table4e8**, shifts the
signed index left3 and adds it to the table base. This selects an eight-byte
event record at runtime. The archived reader does not follow it.

- Event byte2 equal0: load row elapsed08, then previous10, and call
  `8005b98c(actor, record, elapsed, previous)` at `5b8ec`.
- Event byte2 nonzero: load frame0c and previous14. `fcmpo` followed by
  `cror EQ,GT,EQ` sends ordered frame>=previous directly to `5b98c` at
  `5b910` with those values.
- Otherwise, under finite preconditions, frame<previous: load **signed**
  duration24; build the integer-conversion double using `xoris 8000` and
  high word43300000; load bias804373d0. Conversion uses **single-precision
  `fsubs`**, then **single-precision `fadds`** with frame0c, and calls
  `5b98c` at `5b944` with wrapped frame and unchanged previous14.
- After the callee returns, read event byte6, increment the event pointer
  by8, sign-extend byte6 and compare with -1. Exactly -1 ends this row;
  any other value continues at the next sequential record. Byte6 is a
  sentinel check, not a next-record index.
- Increment row counter and row pointer; loop while counter<4. Then
  execute the genuine epilogue/return at `5b988`.

The function writes only stack bookkeeping, not actor or row fields. A
nonnull no-event return is possible only if all four actual reached signed
auxiliary37 values are -1. No such initial retail row values are authenticated
here. Any reached event retains `5b98c` and its eventual audio behavior as
an external boundary. The reader authenticates the complete dispatch-loop
schedule, not sound playback, event-table extent or payload ownership.

## Exact physical provenance

Both snapshots agree on all derived instructions, cells, scalars, mappings
and physical chain spans. New selection total is **524 bytes**:512 code,
8 constructor cells and4 scalar. Whole-source authentication uses the
existing shared data5 verification and is separate from this new total.

| Address | Root / data buffer | Chain offset | Data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| `8006f88c` | 21 / 48 | 434860 | 9032 | 811854 | 72 |
| `80055ee4` | 21 / 42 | 329988 | 2428 | 706946 | 172 |
| `8005b880` | 21 / 43 | 352928 | 8990 | 729892 | 268 |
| `802d3b20` | 199 / 206 | 101568 | 3300 | 3394794 | 4 |
| `802d3b48` | 199 / 206 | 101608 | 3340 | 3394834 | 4 |
| `80437298` | 263 / 264 | 2168 | 2168 | 4343934 | 4 |

Every listed span uses the archived obfuscated chain form, authenticated by
the unchanged parser. Tests freeze these spans rather than printing a broad
binary dump.

## Reproduction and checks

```sh
python research/tools/matching-decomp/read_archived_frame_suffix_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf' > .tmp/frame-suffix-evidence/db3.json
python research/tools/matching-decomp/read_archived_frame_suffix_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf' > .tmp/frame-suffix-evidence/db4.json
python -m unittest discover -s research/tools/matching-decomp -p test_archived_frame_suffix_evidence.py -v
```

The focused suite passes22 tests, including both existing local snapshots.
Frozen complete operand schedules independently inverse-encode all three
exact hashes. Refusal tests cover unknown/duplicate/non-integer selections,
fixed mapping identity, widths, digests, incomplete decoding, external
non-call branches, conditional LR-return reserved fields, wrong pointer
targets, changed scalar bits, whole-file authentication before parsing,
schema and mapping controls before selections, forbidden CLI switches and
no pointer following. Semantic assertions protect signed gates, source
store/read order, actual constructor copies, frame capture/restore order,
single-precision conversion, four-row traversal and event sentinel timing.
Missing local archives skip local cases rather than fetching them.

The complete existing archived-evidence regression selection also passes
841 tests, including these22, and the shared constant/parser suite passes
16 additional tests. `git diff --check` passes. These are static-reader
checks, not application integration or original-game execution tests.

This evidence permits bounded source-informed implementation and tests.
It does not by itself promote any implementation to retail execution,
complete frame/action coverage, production routing or playability.
