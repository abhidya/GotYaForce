# Mass and team preparation: bounded archive evidence

Date: 2026-11-14. Investigation base:
`7397cfeb7563f1637bb20bb02b97fafe133d7364` (no commit or push).

The [fixed reader](../tools/matching-decomp/read_archived_mass_preparation_evidence.py)
authenticates the complete `80053b30` body: **1344 bytes /336 instructions**,
plus three independently named four-byte floating constants. Both existing
snapshots agree on every operand, constant, mapping and physical span. The
[independent tests](../tools/matching-decomp/test_archived_mass_preparation_evidence.py)
manually specify every operand and inverse-encode the complete body hash.
All **18 evidence tests** and **17 existing outer-frame regressions** pass.

The concrete next runtime portion is the ordered team-list/count clears, six
contiguous actor mass/team preparations, then six live pointer-table mass
updates when their contact bytes are zero. It stops before mandatory call
`800055fc` at`80053d60`. Full evidence also describes passenger propagation and
the randomized ordering suffix, but does not authenticate that callee or
supply an RNG result. Reaching this boundary is not a completed mass-preparation
function, scheduler callback or frame.

This is archived ProgramDB static evidence, not independently measured original-
DOL identity, original execution, `MATCH`, live dispatch, integration or
playability. No source instructions were executed, no global pointer payloads
or pointed-to memory were read, no raw binary output is published, and no shared
authenticator, mapping validator, decoder or allowlist changed.

## Frozen selection and authentication

Before the first selected archive payload read, the bounded selection was
recorded in ignored `.tmp/mass-preparation-evidence-20261114/scope-frozen.json`,
SHA-256 `2c37e1d18395a34cf1e70b898275b64476f32957e636f02c9318273f64f19219`.
It was never expanded. Independent readable sources establish:

| Selection | Width | Independent provenance |
| --- | --- | --- |
| `80053b30` through `80054070` exclusive | `0x540` /1344 | `ghidra-export/chunk_0006.c:6720–6950`, index1035–1036, `research/symbols/GG4E-CSM-20220412.map:687` exact size`00000540` |
| `80437250` | 4 | Explicit `FLOAT_80437250` uses at C6774/6777 |
| `80437254` | 4 | Explicit `FLOAT_80437254` comparison at C6780 |
| `80437258` | 4 | Explicit `FLOAT_80437258` assignment at C6830; suffix evidence only |

Code/data pointers and decoded calls did not select any new read. `800055fc`,
`803c4e84` table contents, the actors, parameters, passengers, team lists and
count bytes remain unselected. The C identifies source bounds and named
constant locations; the behavior below follows instruction operands, including
places where C wording loses ordering or floating comparison details.

Unchanged `read_archived_constants.inspect` authenticates the actual whole-file
SHA-256, six supported schemas, PowerPC language, image/address map, executable
metadata, empty File Bytes table, and full data5 hash/controls before selection.
Unchanged `command.mappings` validates all text1/data3/data5 blocks and
initialized subblocks, bounds and overlaps. Exact **typed** text1 and data5
mapping tuples are checked again. Width and selected SHA-256 are checked before
code decoding or constant interpretation.

| Snapshot | Bytes | Complete SHA-256 |
| --- | --- | --- |
| `db.3.gbf` | 57655296 | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| `db.4.gbf` | 58802176 | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

These existing private snapshots are in
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`. File Bytes is
version0/root−1/count0; image offset`80000000`; block size16384; master root1.
Executable metadata SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is import metadata, not an independently measured original-DOL hash.
Full data5 SHA-256 is
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

Text1 is `[800055e0,802b0160)`, length2796416, block/subblock1, chain root21.
Data5 is `[80436a20,8043d500)`, length27360, block/subblock7, chain root263.
Both are initialized subblock type2 with starting/source offsets0.

| Selection | SHA-256 | Value |
| --- | --- | --- |
| `80053b30` | `8c5a0b248d9fa0b131b7ff20346ee5af01ea3453ae1c8c9a18012ff8839a6890` | Complete body |
| `80437250` | `df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119` | +0.0, binary32 `00000000` |
| `80437254` | `2b6153d08dad36fbfbc33c125e7c858acc13a4a989168279c710896032141f98` | 50000.0, binary32 `47435000` |
| `80437258` | `de620abd6d3615746360c1d15ce3a56291236d37424124054a49d25e947ffc4d` | 1.0, binary32 `3f800000` |

Physical spans agree in both snapshots; offsets below are decimal. All four
selected spans occupy obfuscated data buffers.

| Address | Root/buffer | Chain offset | Data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| `80053b30` | 21/41 | 320848 | 9666 | 697800 | 1344 |
| `80437250` | 263/264 | 2096 | 2096 | 4343862 | 4 |
| `80437254` | 263/264 | 2100 | 2100 | 4343866 | 4 |
| `80437258` | 263/264 | 2104 | 2104 | 4343870 | 4 |

The complete additional chain trace following unchanged authentication is:

```
(21,320848,1344,2796416)
(263,2096,4,27360)
(263,2100,4,27360)
(263,2104,4,27360)
```

Tests compare the entire trace to the authenticator's own full-data5/control
reads followed by exactly these four selections. This does not omit or disguise
the full data5 reads required by existing authentication.

## Canonical memory and callee boundaries

All source field offsets below are hexadecimal. Absolute `803c...` addresses
are directly assembled with `addis/addi` or `addis/lwz`. The count-byte base is
**r13−21308**, which readable C names `80436264`; the later scheduler count is
r13−21312, named`80436260`. The code does not establish the live r13 value.
Constant loads use **r2−30672/−30668/−30664**, corresponding to the three named
constants above under the source SDA mapping; this does not measure live r2.

| Boundary | Meaning demonstrated by this body |
| --- | --- |
| `803c6dec..803c6e48` inclusive, 24 words | Four six-entry team pointer lists; separate from the scheduler array |
| r13−21308 through +3 | Four team count bytes; separate from the scheduler count |
| `803c4e84` | Address of first actor-pointer table cell, not actor object storage |
| loaded first actor pointer + n×`1e00` | Six contiguous actor objects in first and final passes |
| `803c4e84` + n×4 | Six independently loaded pointer-table entries in propagation and randomized pass |
| actor+0 /+18 /+88 | Active byte, status byte, signed team ID |
| actor+204 /+208 | Accumulated mass and this actor's contribution, binary32 accesses |
| actor+4ac → parameter+98; actor+b4 | Parameter pointer/load and scale read on the LT path |
| current+1db → current+1e4 → passenger+83 | Contact predicate, followed pointer, passenger stop predicate |
| passenger+3e4 | Signed local-counter index, not a team ID |
| `800055fc` at`80053d60`, then`80053d80` | Only two calls in this complete body; both unselected |
| `803c4e6c` and r13−21312 | Later sorted scheduler pointer array/count, not cleared in the prefix |

No callback, dispatcher or SDK call appears in this body. Field labels such as
"mass", "team" and "passenger" are useful descriptions, not proof of a complete
object type or successful integration.

## Ordered clears and captured first-actor pointer

The prologue allocates32 stack bytes, saves LR and r31, initializes r5 to
`803c6dec`, r7 to the team-count base, r4=0, r0=6 and r8=stack+8. The exact
externally relevant order is:

1. `80053b5c`: clear the word at`803c6dec`.
2. **`80053b60`: load the first actor pointer from`803c4e84` into r9.**
3. Clear words`803c6df0..803c6e38` in ascending four-byte order.
4. Clear count byte0; clear word`803c6e3c`; clear byte1; clear word`803c6e40`;
   clear byte2; clear words`803c6e44`, then`803c6e48`; clear byte3.
5. Set CTR=6 and enter the first actor loop.

This is not a bulk zero of an assumed adjacent combined structure. The actor
pointer is captured *between* the first and remaining word clears. A model
allowing aliases must not move this load before or after the complete clear set.
The scheduler array`803c4e6c` and scheduler count are untouched here.

## Six contiguous actor mass/team preparations

Each iteration uses current r9; regardless of active state, the tail advances
r8 by1 and r9 by`1e00`, then decrements CTR. Thus the six objects are firstLoaded
Pointer + n×`1e00`, **not six pointer-table dereferences**. No null, allocation,
array-bound or alignment test is present.

1. Load actor+0, sign-extend with record bit and skip all remaining row work
   if zero. Every nonzero byte, including`80..ff`, is active. An inactive row
   does **not** initialize its local counter or clear either mass field.
2. Load +0.0 into f0; clear the local byte at current r8; store f0 at actor+204.
3. Load actor+18 and sign-extend. For statuses other than1/2, store retained
   f0=+0.0 at actor+208. For1/2, first load pointer actor+4ac, then the50000.0
   threshold, then binary32 parameter+98 into f1.
4. `fcmpo cr0,f1,f0`, followed by `bc BO4/BI0`: when LT is **not set**, store
   unscaled f1 at actor+208. Only the LT path reads actor+b4, performs
   `fmuls f0,f1,f0`, then stores f0 at actor+208. Equality is unscaled.
   The exact predicate is not a JavaScript rewrite of `50000 <= parameter`:
   an unordered comparison also has LT clear if floating exceptions permit
   continuation. Source FPSCR exception behavior and NaN payload propagation
   are not measured here; finite-only host admission must remain explicit.
5. **Reload** actor+18 as an unsigned byte and compare it to1. Only this fresh
   value1 reaches team insertion. It is not the earlier captured status.
6. Load actor+88; sign-extend to team ID. Read unsigned old count from
   countBase+ID; compute ID×24, sign-extend old count for the list index, and
   increment the unsigned loaded count by1. Store the low byte of the increment
   to countBase+ID **before** storing the actor pointer to
   `803c6dec + ID×24 + sign8(oldCount)×4` (32-bit address arithmetic).

There are no original range checks enforcing ID0..3 or count0..5, and no null
parameter guard. A host may refuse unsupported memory safely but must identify
that as host admission, preserve completed prior writes, and avoid treating the
checks as demonstrated original behavior. The first-pass local bytes correspond
to physical actor iteration, not necessarily each actor's later +3e4 index.

## Six live pointer-table mass propagations

Next set r6=`803c4e84`, r4=stack+8, r7=0 and CTR=3. Each CTR iteration has two
halves. The first loads r8 from[r6]; the second uses **`lwzu r8,4(r6)`** and
therefore updates r6. The iteration tail increments r6 by4 again, yielding
six live loads at table offsets0,4,8,12,16,20. A previous store can affect a
later table load when regions alias. These need not be the six objects prepared
by the contiguous pass.

For each loaded original actor r8:

1. Load actor+204 into f1, copy actor pointer to traversal pointer r9, load
   actor+208 into f0, `fadds f0,f1,f0`, then `stfs f0,actor+204`.
   There is **no active or status gate**. Addition is binary32 arithmetic,
   not an unrounded double accumulator.
2. Only after that store, load current r9+1db, sign-extend, and test nonzero.
   Zero advances immediately to the next pointer-table half/iteration.
3. Nonzero follows `lwz r9,current+1e4`, then reads passenger+83. If its signed
   byte is nonzero, stop this original actor's traversal immediately, without
   reading passenger+3e4 or updating its counter/mass.
4. Otherwise read passenger+3e4, then passenger+204, then **original actor+208**.
   Sign-extend +3e4 and read the local byte at stack+8+index. Compute the binary32
   sum of those two mass loads. Increment and store the local byte first,
   then store the sum to passenger+204. Re-test this passenger's+1db and repeat.

The contribution remains the original actor's+208 but is reloaded on every
passenger. There is no null check, visited set, cycle limit, team/status check,
or guaranteed bounded passenger depth. Alias-sensitive loads and stores cannot
be replaced with a prefetched passenger list or one cached mass value. A host
may bound/refuse unsupported traversal; that is not source completion.

The useful **contact-zero runtime subset** needs no passenger pointer or index
read. It still performs each self mass add/store before the contact test. If it
stops on the first nonzero contact byte, it must keep that self mass update and
all previous writes and must not process subsequent slots. Extending through
the passenger+83 early-stop path is separately supported by these operands but
requires the pointer/load admission rules. A whole-function no-op when contact
is unsupported would discard demonstrated prefix effects.

## Mandatory RNG boundary and fully decoded suffix

After all six propagation halves normally finish, execution reaches
**`bl 800055fc` at`80053d60`**. The exact body has no earlier call. The prefix
must stop here and cannot synthesize a return, zero the scheduler count, set
actor+664, or advance to outer-frame callee`8006ae60`.

The remaining instructions are represented and checked but not runtime-admitted
by this evidence alone:

- The first call result is shifted right2, then unsigned high multiplication by
  `aaaaaaab`, shift right2, multiply6 and subtraction compute `(r3 >> 2) % 6`.
  A second `800055fc` call follows. Its bit3 selects traversal step+1 if set,
  otherwise−1.
- Clear scheduler count r13−21312, load constant1.0, then visit six pointer-table
  entries in cyclic order from that starting index. Each visit stores1.0 to
  actor+664 **before** active/4a0 eligibility tests. The next index wraps a
  negative value to5; the nonnegative path uses signed-high multiplication by
  `2aaaaaab`, sign correction, multiplication6 and subtraction for remainder.
- An actor with nonzero active byte and actor+4a0 !=1 is inserted into the
  scheduler array. Initial signed count is captured in r12/r11. A negative
  count skips insertion. Scan at most capturedCount+1 positions. Reaching the
  captured count appends using a fresh count read: count byte is stored before
  the actor pointer.
- Otherwise load the existing pointer, candidate+3e4, existing+3e4, then the
  corresponding local bytes; sign-extend both IDs and both counters. Insert
  before the first existing counter strictly less than the candidate counter.
  Equal counters continue the scan, preserving randomized tie order. The shift
  length uses **captured r12**, not a new count read. Backward pointer copies
  use eight-word chunks followed by the remainder, preserving each load/store
  order. This insertion stores the actor pointer before the incremented count
  byte, unlike append. The count is freshly loaded after shifting.
- Finally reload the first actor pointer from`803c4e84` once, and again walk six
  contiguous objects at stride`1e00`. Active objects with+4a0 ==1 scan the
  scheduler array for a pointer equal to current actor+4a4 (a fresh4a4 load on
  every comparison). The CTR scan permits **count+1 reads**, including the
  entry at logical index count; do not silently repair it to count reads.
- A match shifts the suffix backward, inserts the current actor immediately
  before that entry, then stores the incremented scheduler count. No match
  within that scan causes no insertion. The following contiguous actor begins
  after all insertion writes, so later reads remain live. Finally restore LR,
  r31 and stack, then return. There is no established C return value.

Local counters were initialized only for active first-pass objects. Invalid
indices or aliasing may expose other stack bytes, and the instructions do not
establish how those are initialized. The report does not promote a generic
six-element safe-array sorting implementation or this suffix to verified runtime.

## Verification and limits

All336 manually reviewed semantic fixtures inverse-encode the exact body SHA.
Every one of **10752 instruction-bit mutations** either refuses or decodes to
changed represented operands that inverse-encode the exact changed word.
Every one of **10752 code-payload bit mutations** fails the selected digest
before decode. All **96 constant-bit mutations** fail their selected digest.
All **47 control-flow rows** and **261 metadata mutations** are checked.

Tests also cover whole-file digest corruption, all six schema versions/key
types/field types/names/missing tables, full mapping tampering, exact before/after
chain traces, exact physical spans, complete source extents, typed mapping
refusal, duplicate selections, widths/truncation, nearby/global/callee selection
refusal, reserved instruction fields, arbitrary CLI refusal and no raw output.
Semantic tests explicitly lock clear interleaving, distinct actor traversal
forms, parameter/scale ordering, signed IDs/count indices, store ordering,
self-mass-before-contact, passenger load order and mandatory first RNG call.

The initial run passed every operand/hash/mutation assertion but had an incorrect
expected **count** for metadata mutations (263 versus actual261). Only that
assertion was corrected; no selected hash, operand fixture, source extent or
guard was changed to obtain the final pass. Additional constant type/value
negative controls were included before the final run.

Reproduction (existing snapshots only; no install/fetch):

```
python -m unittest discover -s research/tools/matching-decomp -p test_archived_mass_preparation_evidence.py -v
python -m unittest discover -s research/tools/matching-decomp -p test_archived_outer_frame_evidence.py -v
python research/tools/matching-decomp/read_archived_mass_preparation_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf
python research/tools/matching-decomp/read_archived_mass_preparation_evidence.py research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf
```

This is focused static evidence verification, not contributor/docs aggregate
verification, independent source execution, browser acceptance or runtime
integration. No disputed estimator, ported runtime, proprietary SDK or original
binary execution was used as an oracle. Private discovery and reports remain
in ignored `.tmp/mass-preparation-evidence-20261114/`.

| Derived report | SHA-256 |
| --- | --- |
| `db3.json` | `0d28d5ba36367ef323b08a9e3d5e220fcfc8ee24a11a60b731e8373f2d2fb425` |
| `db4.json` | `69b97aece4b3c6e277d503dd1b4398685f11acfbd8d6e66cdaf1e92dc5e39d80` |

## Complete decoded instruction operands

Every instruction is listed in source order, with no gaps. PCs/branch targets
are hexadecimal; all other operand numbers are decimal. `mflr/mtlr` fix SPR8
and Rc0; `mtctr` fixes SPR9 and Rc0. Register comparisons fix reserved fields;
indexed loads/stores fix Rc0. `blr` fixes XO16 and its reserved fields. Arithmetic
without an explicit record bit fixes Rc0; `andi.` records implicitly. `lwzu`
rejects rA0 and rA=rD. `subf` fixes OE0. Floating arithmetic fixes unused operands
and Rc0; `fcmpo` fixes BF0, reserved bits and Rc0. Every other admitted bit is
represented below. These operands are derived evidence, not raw binary output.

| PC | Complete operands |
| --- | --- |
| `80053b30` | `stwu rS=1, rA=1, displacement=-32` |
| `80053b34` | `mflr rD=0` |
| `80053b38` | `addis rD=4, rA=0, immediate=-32708` |
| `80053b3c` | `addi rD=7, rA=13, immediate=-21308` |
| `80053b40` | `stw rS=0, rA=1, displacement=36` |
| `80053b44` | `addi rD=5, rA=4, immediate=28140` |
| `80053b48` | `addi rD=4, rA=0, immediate=0` |
| `80053b4c` | `addis rD=3, rA=0, immediate=-32708` |
| `80053b50` | `stw rS=31, rA=1, displacement=28` |
| `80053b54` | `addi rD=0, rA=0, immediate=6` |
| `80053b58` | `addi rD=8, rA=1, immediate=8` |
| `80053b5c` | `stw rS=4, rA=5, displacement=0` |
| `80053b60` | `lwz rD=9, rA=3, displacement=20100` |
| `80053b64` | `stw rS=4, rA=5, displacement=4` |
| `80053b68` | `stw rS=4, rA=5, displacement=8` |
| `80053b6c` | `stw rS=4, rA=5, displacement=12` |
| `80053b70` | `stw rS=4, rA=5, displacement=16` |
| `80053b74` | `stw rS=4, rA=5, displacement=20` |
| `80053b78` | `stw rS=4, rA=5, displacement=24` |
| `80053b7c` | `stw rS=4, rA=5, displacement=28` |
| `80053b80` | `stw rS=4, rA=5, displacement=32` |
| `80053b84` | `stw rS=4, rA=5, displacement=36` |
| `80053b88` | `stw rS=4, rA=5, displacement=40` |
| `80053b8c` | `stw rS=4, rA=5, displacement=44` |
| `80053b90` | `stw rS=4, rA=5, displacement=48` |
| `80053b94` | `stw rS=4, rA=5, displacement=52` |
| `80053b98` | `stw rS=4, rA=5, displacement=56` |
| `80053b9c` | `stw rS=4, rA=5, displacement=60` |
| `80053ba0` | `stw rS=4, rA=5, displacement=64` |
| `80053ba4` | `stw rS=4, rA=5, displacement=68` |
| `80053ba8` | `stw rS=4, rA=5, displacement=72` |
| `80053bac` | `stw rS=4, rA=5, displacement=76` |
| `80053bb0` | `stb rS=4, rA=13, displacement=-21308` |
| `80053bb4` | `stw rS=4, rA=5, displacement=80` |
| `80053bb8` | `stb rS=4, rA=7, displacement=1` |
| `80053bbc` | `stw rS=4, rA=5, displacement=84` |
| `80053bc0` | `stb rS=4, rA=7, displacement=2` |
| `80053bc4` | `stw rS=4, rA=5, displacement=88` |
| `80053bc8` | `stw rS=4, rA=5, displacement=92` |
| `80053bcc` | `stb rS=4, rA=7, displacement=3` |
| `80053bd0` | `mtctr rS=0` |
| `80053bd4` | `lbz rD=0, rA=9, displacement=0` |
| `80053bd8` | `extsb rS=0, rA=0, Rc=1` |
| `80053bdc` | `bc BO=12, BI=2, target=80053c78, AA=0, LK=0` |
| `80053be0` | `lfs fD=0, rA=2, displacement=-30672` |
| `80053be4` | `addi rD=0, rA=0, immediate=0` |
| `80053be8` | `stb rS=0, rA=8, displacement=0` |
| `80053bec` | `stfs fS=0, rA=9, displacement=516` |
| `80053bf0` | `lbz rD=0, rA=9, displacement=24` |
| `80053bf4` | `extsb rS=0, rA=0, Rc=0` |
| `80053bf8` | `cmpi BF=0, L=0, rA=0, immediate=1` |
| `80053bfc` | `bc BO=12, BI=2, target=80053c08, AA=0, LK=0` |
| `80053c00` | `cmpi BF=0, L=0, rA=0, immediate=2` |
| `80053c04` | `bc BO=4, BI=2, target=80053c34, AA=0, LK=0` |
| `80053c08` | `lwz rD=3, rA=9, displacement=1196` |
| `80053c0c` | `lfs fD=0, rA=2, displacement=-30668` |
| `80053c10` | `lfs fD=1, rA=3, displacement=152` |
| `80053c14` | `fcmpo BF=0, fA=1, fB=0` |
| `80053c18` | `bc BO=4, BI=0, target=80053c2c, AA=0, LK=0` |
| `80053c1c` | `lfs fD=0, rA=9, displacement=180` |
| `80053c20` | `fmuls fD=0, fA=1, fC=0` |
| `80053c24` | `stfs fS=0, rA=9, displacement=520` |
| `80053c28` | `b target=80053c38, AA=0, LK=0` |
| `80053c2c` | `stfs fS=1, rA=9, displacement=520` |
| `80053c30` | `b target=80053c38, AA=0, LK=0` |
| `80053c34` | `stfs fS=0, rA=9, displacement=520` |
| `80053c38` | `lbz rD=0, rA=9, displacement=24` |
| `80053c3c` | `cmpi BF=0, L=0, rA=0, immediate=1` |
| `80053c40` | `bc BO=4, BI=2, target=80053c78, AA=0, LK=0` |
| `80053c44` | `lbz rD=7, rA=9, displacement=136` |
| `80053c48` | `addis rD=3, rA=0, immediate=-32708` |
| `80053c4c` | `addi rD=4, rA=13, immediate=-21308` |
| `80053c50` | `extsb rS=7, rA=7, Rc=0` |
| `80053c54` | `addi rD=5, rA=3, immediate=28140` |
| `80053c58` | `lbzx rD=3, rA=4, rB=7` |
| `80053c5c` | `mulli rD=6, rA=7, immediate=24` |
| `80053c60` | `extsb rS=3, rA=0, Rc=0` |
| `80053c64` | `addi rD=3, rA=3, immediate=1` |
| `80053c68` | `add rD=5, rA=5, rB=6, Rc=0` |
| `80053c6c` | `rlwinm rS=0, rA=0, SH=2, MB=0, ME=29, Rc=0` |
| `80053c70` | `stbx rS=3, rA=4, rB=7` |
| `80053c74` | `stwx rS=9, rA=5, rB=0` |
| `80053c78` | `addi rD=8, rA=8, immediate=1` |
| `80053c7c` | `addi rD=9, rA=9, immediate=7680` |
| `80053c80` | `bc BO=16, BI=0, target=80053bd4, AA=0, LK=0` |
| `80053c84` | `addis rD=3, rA=0, immediate=-32708` |
| `80053c88` | `addi rD=0, rA=0, immediate=3` |
| `80053c8c` | `addi rD=6, rA=3, immediate=20100` |
| `80053c90` | `addi rD=4, rA=1, immediate=8` |
| `80053c94` | `addi rD=7, rA=0, immediate=0` |
| `80053c98` | `mtctr rS=0` |
| `80053c9c` | `lwz rD=8, rA=6, displacement=0` |
| `80053ca0` | `lfs fD=1, rA=8, displacement=516` |
| `80053ca4` | `or rS=8, rA=9, rB=8, Rc=0` |
| `80053ca8` | `lfs fD=0, rA=8, displacement=520` |
| `80053cac` | `fadds fD=0, fA=1, fB=0` |
| `80053cb0` | `stfs fS=0, rA=8, displacement=516` |
| `80053cb4` | `b target=80053cec, AA=0, LK=0` |
| `80053cb8` | `lwz rD=9, rA=9, displacement=484` |
| `80053cbc` | `lbz rD=0, rA=9, displacement=131` |
| `80053cc0` | `extsb rS=0, rA=0, Rc=1` |
| `80053cc4` | `bc BO=4, BI=2, target=80053cf8, AA=0, LK=0` |
| `80053cc8` | `lbz rD=0, rA=9, displacement=996` |
| `80053ccc` | `lfs fD=1, rA=9, displacement=516` |
| `80053cd0` | `lfs fD=0, rA=8, displacement=520` |
| `80053cd4` | `extsb rS=0, rA=5, Rc=0` |
| `80053cd8` | `lbzx rD=3, rA=4, rB=5` |
| `80053cdc` | `fadds fD=0, fA=1, fB=0` |
| `80053ce0` | `addi rD=0, rA=3, immediate=1` |
| `80053ce4` | `stbx rS=0, rA=4, rB=5` |
| `80053ce8` | `stfs fS=0, rA=9, displacement=516` |
| `80053cec` | `lbz rD=0, rA=9, displacement=475` |
| `80053cf0` | `extsb rS=0, rA=0, Rc=1` |
| `80053cf4` | `bc BO=4, BI=2, target=80053cb8, AA=0, LK=0` |
| `80053cf8` | `lwzu rD=8, rA=6, displacement=4` |
| `80053cfc` | `lfs fD=1, rA=8, displacement=516` |
| `80053d00` | `or rS=8, rA=9, rB=8, Rc=0` |
| `80053d04` | `lfs fD=0, rA=8, displacement=520` |
| `80053d08` | `fadds fD=0, fA=1, fB=0` |
| `80053d0c` | `stfs fS=0, rA=8, displacement=516` |
| `80053d10` | `b target=80053d48, AA=0, LK=0` |
| `80053d14` | `lwz rD=9, rA=9, displacement=484` |
| `80053d18` | `lbz rD=0, rA=9, displacement=131` |
| `80053d1c` | `extsb rS=0, rA=0, Rc=1` |
| `80053d20` | `bc BO=4, BI=2, target=80053d54, AA=0, LK=0` |
| `80053d24` | `lbz rD=0, rA=9, displacement=996` |
| `80053d28` | `lfs fD=1, rA=9, displacement=516` |
| `80053d2c` | `lfs fD=0, rA=8, displacement=520` |
| `80053d30` | `extsb rS=0, rA=5, Rc=0` |
| `80053d34` | `lbzx rD=3, rA=4, rB=5` |
| `80053d38` | `fadds fD=0, fA=1, fB=0` |
| `80053d3c` | `addi rD=0, rA=3, immediate=1` |
| `80053d40` | `stbx rS=0, rA=4, rB=5` |
| `80053d44` | `stfs fS=0, rA=9, displacement=516` |
| `80053d48` | `lbz rD=0, rA=9, displacement=475` |
| `80053d4c` | `extsb rS=0, rA=0, Rc=1` |
| `80053d50` | `bc BO=4, BI=2, target=80053d14, AA=0, LK=0` |
| `80053d54` | `addi rD=6, rA=6, immediate=4` |
| `80053d58` | `addi rD=7, rA=7, immediate=1` |
| `80053d5c` | `bc BO=16, BI=0, target=80053c9c, AA=0, LK=0` |
| `80053d60` | `bl target=800055fc, AA=0, LK=1` |
| `80053d64` | `addis rD=4, rA=0, immediate=-21845` |
| `80053d68` | `rlwinm rS=3, rA=3, SH=30, MB=2, ME=31, Rc=0` |
| `80053d6c` | `addi rD=0, rA=4, immediate=-21845` |
| `80053d70` | `mulhwu rD=0, rA=0, rB=3, Rc=0` |
| `80053d74` | `rlwinm rS=0, rA=0, SH=30, MB=2, ME=31, Rc=0` |
| `80053d78` | `mulli rD=0, rA=0, immediate=6` |
| `80053d7c` | `subf rD=31, rA=0, rB=3, Rc=0` |
| `80053d80` | `bl target=800055fc, AA=0, LK=1` |
| `80053d84` | `rlwinm rS=3, rA=3, SH=0, MB=28, ME=28, Rc=1` |
| `80053d88` | `addi rD=0, rA=0, immediate=-1` |
| `80053d8c` | `bc BO=12, BI=2, target=80053d94, AA=0, LK=0` |
| `80053d90` | `addi rD=0, rA=0, immediate=1` |
| `80053d94` | `addi rD=4, rA=0, immediate=0` |
| `80053d98` | `addis rD=3, rA=0, immediate=-32708` |
| `80053d9c` | `stb rS=4, rA=13, displacement=-21312` |
| `80053da0` | `addi rD=3, rA=3, immediate=20100` |
| `80053da4` | `lfs fD=0, rA=2, displacement=-30664` |
| `80053da8` | `rlwinm rS=31, rA=5, SH=2, MB=0, ME=29, Rc=0` |
| `80053dac` | `add rD=31, rA=31, rB=0, Rc=1` |
| `80053db0` | `lwzx rD=5, rA=3, rB=5` |
| `80053db4` | `stfs fS=0, rA=5, displacement=1636` |
| `80053db8` | `bc BO=4, BI=0, target=80053dc4, AA=0, LK=0` |
| `80053dbc` | `addi rD=31, rA=0, immediate=5` |
| `80053dc0` | `b target=80053de0, AA=0, LK=0` |
| `80053dc4` | `addis rD=6, rA=0, immediate=10923` |
| `80053dc8` | `addi rD=6, rA=6, immediate=-21845` |
| `80053dcc` | `mulhw rD=7, rA=6, rB=31, Rc=0` |
| `80053dd0` | `rlwinm rS=7, rA=6, SH=1, MB=31, ME=31, Rc=0` |
| `80053dd4` | `add rD=6, rA=7, rB=6, Rc=0` |
| `80053dd8` | `mulli rD=6, rA=6, immediate=6` |
| `80053ddc` | `subf rD=31, rA=6, rB=31, Rc=0` |
| `80053de0` | `lbz rD=6, rA=5, displacement=0` |
| `80053de4` | `extsb rS=6, rA=6, Rc=1` |
| `80053de8` | `bc BO=12, BI=2, target=80053f30, AA=0, LK=0` |
| `80053dec` | `lbz rD=6, rA=5, displacement=1184` |
| `80053df0` | `cmpi BF=0, L=0, rA=6, immediate=1` |
| `80053df4` | `bc BO=12, BI=2, target=80053f30, AA=0, LK=0` |
| `80053df8` | `lbz rD=12, rA=13, displacement=-21312` |
| `80053dfc` | `addis rD=6, rA=0, immediate=-32708` |
| `80053e00` | `addi rD=10, rA=6, immediate=20076` |
| `80053e04` | `addi rD=9, rA=1, immediate=8` |
| `80053e08` | `extsb rS=12, rA=11, Rc=1` |
| `80053e0c` | `addi rD=6, rA=0, immediate=0` |
| `80053e10` | `addi rD=7, rA=11, immediate=1` |
| `80053e14` | `mtctr rS=7` |
| `80053e18` | `bc BO=12, BI=0, target=80053f30, AA=0, LK=0` |
| `80053e1c` | `cmp BF=0, L=0, rA=6, rB=11` |
| `80053e20` | `bc BO=4, BI=2, target=80053e48, AA=0, LK=0` |
| `80053e24` | `lbz rD=8, rA=13, displacement=-21312` |
| `80053e28` | `addis rD=6, rA=0, immediate=-32708` |
| `80053e2c` | `addi rD=6, rA=6, immediate=20076` |
| `80053e30` | `extsb rS=8, rA=7, Rc=0` |
| `80053e34` | `addi rD=8, rA=8, immediate=1` |
| `80053e38` | `rlwinm rS=7, rA=7, SH=2, MB=0, ME=29, Rc=0` |
| `80053e3c` | `stb rS=8, rA=13, displacement=-21312` |
| `80053e40` | `stwx rS=5, rA=6, rB=7` |
| `80053e44` | `b target=80053f30, AA=0, LK=0` |
| `80053e48` | `lwz rD=8, rA=10, displacement=0` |
| `80053e4c` | `lbz rD=7, rA=5, displacement=996` |
| `80053e50` | `lbz rD=8, rA=8, displacement=996` |
| `80053e54` | `extsb rS=7, rA=7, Rc=0` |
| `80053e58` | `extsb rS=8, rA=8, Rc=0` |
| `80053e5c` | `lbzx rD=7, rA=9, rB=7` |
| `80053e60` | `lbzx rD=8, rA=9, rB=8` |
| `80053e64` | `extsb rS=7, rA=7, Rc=0` |
| `80053e68` | `extsb rS=8, rA=8, Rc=0` |
| `80053e6c` | `cmp BF=0, L=0, rA=8, rB=7` |
| `80053e70` | `bc BO=4, BI=0, target=80053f24, AA=0, LK=0` |
| `80053e74` | `extsb rS=12, rA=10, Rc=0` |
| `80053e78` | `addis rD=7, rA=0, immediate=-32708` |
| `80053e7c` | `cmp BF=0, L=0, rA=10, rB=6` |
| `80053e80` | `rlwinm rS=10, rA=8, SH=2, MB=0, ME=29, Rc=0` |
| `80053e84` | `addi rD=7, rA=7, immediate=20076` |
| `80053e88` | `add rD=9, rA=7, rB=8, Rc=0` |
| `80053e8c` | `subf rD=8, rA=6, rB=10, Rc=0` |
| `80053e90` | `bc BO=4, BI=1, target=80053f04, AA=0, LK=0` |
| `80053e94` | `rlwinm rS=8, rA=7, SH=29, MB=3, ME=31, Rc=1` |
| `80053e98` | `mtctr rS=7` |
| `80053e9c` | `bc BO=12, BI=2, target=80053ef0, AA=0, LK=0` |
| `80053ea0` | `lwz rD=7, rA=9, displacement=-4` |
| `80053ea4` | `stw rS=7, rA=9, displacement=0` |
| `80053ea8` | `lwz rD=7, rA=9, displacement=-8` |
| `80053eac` | `stw rS=7, rA=9, displacement=-4` |
| `80053eb0` | `lwz rD=7, rA=9, displacement=-12` |
| `80053eb4` | `stw rS=7, rA=9, displacement=-8` |
| `80053eb8` | `lwz rD=7, rA=9, displacement=-16` |
| `80053ebc` | `stw rS=7, rA=9, displacement=-12` |
| `80053ec0` | `lwz rD=7, rA=9, displacement=-20` |
| `80053ec4` | `stw rS=7, rA=9, displacement=-16` |
| `80053ec8` | `lwz rD=7, rA=9, displacement=-24` |
| `80053ecc` | `stw rS=7, rA=9, displacement=-20` |
| `80053ed0` | `lwz rD=7, rA=9, displacement=-28` |
| `80053ed4` | `stw rS=7, rA=9, displacement=-24` |
| `80053ed8` | `lwz rD=7, rA=9, displacement=-32` |
| `80053edc` | `stw rS=7, rA=9, displacement=-28` |
| `80053ee0` | `addi rD=9, rA=9, immediate=-32` |
| `80053ee4` | `bc BO=16, BI=0, target=80053ea0, AA=0, LK=0` |
| `80053ee8` | `andi. rS=8, rA=8, immediate=7` |
| `80053eec` | `bc BO=12, BI=2, target=80053f04, AA=0, LK=0` |
| `80053ef0` | `mtctr rS=8` |
| `80053ef4` | `lwz rD=7, rA=9, displacement=-4` |
| `80053ef8` | `stw rS=7, rA=9, displacement=0` |
| `80053efc` | `addi rD=9, rA=9, immediate=-4` |
| `80053f00` | `bc BO=16, BI=0, target=80053ef4, AA=0, LK=0` |
| `80053f04` | `lbz rD=7, rA=13, displacement=-21312` |
| `80053f08` | `addis rD=8, rA=0, immediate=-32708` |
| `80053f0c` | `rlwinm rS=6, rA=9, SH=2, MB=0, ME=29, Rc=0` |
| `80053f10` | `addi rD=8, rA=8, immediate=20076` |
| `80053f14` | `addi rD=6, rA=7, immediate=1` |
| `80053f18` | `stwx rS=5, rA=8, rB=9` |
| `80053f1c` | `stb rS=6, rA=13, displacement=-21312` |
| `80053f20` | `b target=80053f30, AA=0, LK=0` |
| `80053f24` | `addi rD=10, rA=10, immediate=4` |
| `80053f28` | `addi rD=6, rA=6, immediate=1` |
| `80053f2c` | `bc BO=16, BI=0, target=80053e1c, AA=0, LK=0` |
| `80053f30` | `addi rD=4, rA=4, immediate=1` |
| `80053f34` | `cmpi BF=0, L=0, rA=4, immediate=6` |
| `80053f38` | `bc BO=12, BI=0, target=80053da8, AA=0, LK=0` |
| `80053f3c` | `addis rD=3, rA=0, immediate=-32708` |
| `80053f40` | `addi rD=6, rA=0, immediate=0` |
| `80053f44` | `lwz rD=8, rA=3, displacement=20100` |
| `80053f48` | `lbz rD=0, rA=8, displacement=0` |
| `80053f4c` | `extsb rS=0, rA=0, Rc=1` |
| `80053f50` | `bc BO=12, BI=2, target=8005404c, AA=0, LK=0` |
| `80053f54` | `lbz rD=0, rA=8, displacement=1184` |
| `80053f58` | `cmpi BF=0, L=0, rA=0, immediate=1` |
| `80053f5c` | `bc BO=4, BI=2, target=8005404c, AA=0, LK=0` |
| `80053f60` | `lbz rD=5, rA=13, displacement=-21312` |
| `80053f64` | `addis rD=3, rA=0, immediate=-32708` |
| `80053f68` | `addi rD=4, rA=3, immediate=20076` |
| `80053f6c` | `addi rD=7, rA=0, immediate=0` |
| `80053f70` | `extsb rS=5, rA=3, Rc=1` |
| `80053f74` | `addi rD=0, rA=3, immediate=1` |
| `80053f78` | `mtctr rS=0` |
| `80053f7c` | `bc BO=12, BI=0, target=8005404c, AA=0, LK=0` |
| `80053f80` | `lwz rD=3, rA=4, displacement=0` |
| `80053f84` | `lwz rD=0, rA=8, displacement=1188` |
| `80053f88` | `cmpl BF=0, L=0, rA=3, rB=0` |
| `80053f8c` | `bc BO=4, BI=2, target=80054040, AA=0, LK=0` |
| `80053f90` | `extsb rS=5, rA=5, Rc=0` |
| `80053f94` | `addis rD=3, rA=0, immediate=-32708` |
| `80053f98` | `cmp BF=0, L=0, rA=5, rB=7` |
| `80053f9c` | `rlwinm rS=5, rA=4, SH=2, MB=0, ME=29, Rc=0` |
| `80053fa0` | `addi rD=0, rA=3, immediate=20076` |
| `80053fa4` | `add rD=4, rA=0, rB=4, Rc=0` |
| `80053fa8` | `subf rD=3, rA=7, rB=5, Rc=0` |
| `80053fac` | `bc BO=4, BI=1, target=80054020, AA=0, LK=0` |
| `80053fb0` | `rlwinm rS=3, rA=0, SH=29, MB=3, ME=31, Rc=1` |
| `80053fb4` | `mtctr rS=0` |
| `80053fb8` | `bc BO=12, BI=2, target=8005400c, AA=0, LK=0` |
| `80053fbc` | `lwz rD=0, rA=4, displacement=-4` |
| `80053fc0` | `stw rS=0, rA=4, displacement=0` |
| `80053fc4` | `lwz rD=0, rA=4, displacement=-8` |
| `80053fc8` | `stw rS=0, rA=4, displacement=-4` |
| `80053fcc` | `lwz rD=0, rA=4, displacement=-12` |
| `80053fd0` | `stw rS=0, rA=4, displacement=-8` |
| `80053fd4` | `lwz rD=0, rA=4, displacement=-16` |
| `80053fd8` | `stw rS=0, rA=4, displacement=-12` |
| `80053fdc` | `lwz rD=0, rA=4, displacement=-20` |
| `80053fe0` | `stw rS=0, rA=4, displacement=-16` |
| `80053fe4` | `lwz rD=0, rA=4, displacement=-24` |
| `80053fe8` | `stw rS=0, rA=4, displacement=-20` |
| `80053fec` | `lwz rD=0, rA=4, displacement=-28` |
| `80053ff0` | `stw rS=0, rA=4, displacement=-24` |
| `80053ff4` | `lwz rD=0, rA=4, displacement=-32` |
| `80053ff8` | `stw rS=0, rA=4, displacement=-28` |
| `80053ffc` | `addi rD=4, rA=4, immediate=-32` |
| `80054000` | `bc BO=16, BI=0, target=80053fbc, AA=0, LK=0` |
| `80054004` | `andi. rS=3, rA=3, immediate=7` |
| `80054008` | `bc BO=12, BI=2, target=80054020, AA=0, LK=0` |
| `8005400c` | `mtctr rS=3` |
| `80054010` | `lwz rD=0, rA=4, displacement=-4` |
| `80054014` | `stw rS=0, rA=4, displacement=0` |
| `80054018` | `addi rD=4, rA=4, immediate=-4` |
| `8005401c` | `bc BO=16, BI=0, target=80054010, AA=0, LK=0` |
| `80054020` | `lbz rD=3, rA=13, displacement=-21312` |
| `80054024` | `addis rD=4, rA=0, immediate=-32708` |
| `80054028` | `rlwinm rS=7, rA=5, SH=2, MB=0, ME=29, Rc=0` |
| `8005402c` | `addi rD=4, rA=4, immediate=20076` |
| `80054030` | `addi rD=0, rA=3, immediate=1` |
| `80054034` | `stwx rS=8, rA=4, rB=5` |
| `80054038` | `stb rS=0, rA=13, displacement=-21312` |
| `8005403c` | `b target=8005404c, AA=0, LK=0` |
| `80054040` | `addi rD=4, rA=4, immediate=4` |
| `80054044` | `addi rD=7, rA=7, immediate=1` |
| `80054048` | `bc BO=16, BI=0, target=80053f80, AA=0, LK=0` |
| `8005404c` | `addi rD=6, rA=6, immediate=1` |
| `80054050` | `addi rD=8, rA=8, immediate=7680` |
| `80054054` | `cmpi BF=0, L=0, rA=6, immediate=6` |
| `80054058` | `bc BO=12, BI=0, target=80053f48, AA=0, LK=0` |
| `8005405c` | `lwz rD=0, rA=1, displacement=36` |
| `80054060` | `lwz rD=31, rA=1, displacement=28` |
| `80054064` | `mtlr rS=0` |
| `80054068` | `addi rD=1, rA=1, immediate=32` |
| `8005406c` | `blr BO=20, BI=0, BH=0, LK=0` |
