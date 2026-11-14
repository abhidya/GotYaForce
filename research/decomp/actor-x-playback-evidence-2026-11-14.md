# Cue44 control during ordinary X playback: archived evidence

## Result and limits

Both existing authenticated ProgramDB snapshots agree that the **single fixed
cue44 table cell `802d33b0` contains `80059cd0`**. The independently bounded
handler `80059cd0..80059e30` contains 88 instructions. Its previously missing
ground helper `800690a0..80069140` contains 40 instructions. The reader and tests
represent **all 128 instructions and all decoded operands**, including the ABI
save/restore, branches, condition fields, call targets and return instructions.
There are no omitted instructions inside either selected span.

The additional fixed Double constructor cue-table source cell `802d3b50`
contains `802d3ff8`. Exactly two independently preselected bytes at `802d4050`,
that table's cue44 row, are **full-body state 61 and upper-body state 0**. The
new scope is two code spans, two pointer cells and one two-byte row, not a table
dump. In particular the real row is not the historical synthetic `(61,62)`.

`80059cd0` is the cue44 **control/test handler**, not itself the actor animation
stream interpreter or clone spawn callback. It writes actor byte `588 = 1`,
branches on control word `5e0 & 0x40`, and runs an ordered, short-circuiting
callee chain. The next X request must pass the existing lifecycle owners rather
than replace their state or treat this handler as an unconditional return.

`800690a0` returns zero immediately when actor byte `57a & 0x40` is clear. That
path does not read `5d4`, `5b4`, or `5e0`, call the cue setter, or reset attack
state. Its active branch calls cue setter `8006a750` with cue5; on success it
masks and stores `5e0` **before** calling `8005c080`. Only after that call returns
does it reload `5e0`, set bit `0x2000`, store, and return one. A refusal at
`8005c080` must retain earlier real effects and must not execute the suffix.

This is archived static evidence, **not original-DOL identity, live actor
ownership, runtime dispatch capture, matching-decompilation `MATCH`, retail
behavioral parity, clone creation, or playable-game proof**. Passing the reader
does not authenticate any particular runtime actor pointer or implement an
unselected callee.

Artifacts:

- [Fixed reader](../tools/matching-decomp/read_archived_actor_x_playback_evidence.py).
- [All-operand and refusal tests](../tools/matching-decomp/test_archived_actor_x_playback_evidence.py).

## Independent fixed selections

The investigation selected only the already identified cue44 cell first. Its
target and digest were reported before any code payload selection. Named source
markers were then checked separately. The helper expansion was coordinated and
limited to the one missing ground helper. The Double cue row was independently
identified in recorded source data before reading it; the constructor producer
was separately identified from the previously authenticated copy schedule.
No cell or decoded branch target selects a read in the delivered reader.

| Selection | End exclusive | Bytes | Extent basis |
| --- | --- | --- | --- |
| Cue44 cell `802d33b0` | `802d33b4` | 4 | Fixed cell `802d3300 + 44 * 4`; not a table dump |
| Double constructor `4f0` source `802d3b50` | `802d3b54` | 4 | Prior authenticated constructor source base `802d3b14`, load `+3c` at `8006f698`, store actor `4f0` at `8006f69c` |
| Double cue44 row `802d4050` | `802d4052` | 2 | Independently recorded table `802d3ff8`, row44; fixed address `802d3ff8 + 44 * 2` |
| `FUN_80059cd0` | `80059e30` | 352 | `ghidra-export/chunk_0007.c` marker at line 2571, next marker at line 2608; authenticated final `blr` at `80059e2c` |
| `FUN_800690a0` | `80069140` | 160 | `ghidra-export/chunk_0008.c` marker at line 5104, next marker at line 5138; authenticated final `blr` at `8006913c` |

Neither function has an entry in
`research/symbols/GG4E-CSM-20220412.map`. The tests explicitly check that absence
and the independent named C markers; no named map extent is invented. Every
non-call branch in each authenticated span stays within that span. The source
markers provide the planned bounds; the actual return and branch facts confirm
the bounded schedules, rather than silently scanning for more code.

## Authentication and physical provenance

The existing files are under
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256
  `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256
  `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Unchanged `read_archived_constants.inspect` checks the actual whole-file digest,
exact schemas, program `boot.dol`, language `PowerPC:BE:32:Gekko_Broadway`, Ghidra
creation version `12.1.2`, executable hash metadata and property type, empty File
Bytes, address map, whole data5 digest and established controls before any new
cell or code selection. Unchanged `read_archived_command_evidence.mappings`
checks all-block overlap and the exact text1/data3/data5 block and subblock
identities, encoded addresses, lengths, types and offsets. Exact typed text1 and
data3 mapping tuples are derived from those authenticated rows and checked
again before payload reads.

- Executable SHA-256 import metadata is
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  Import metadata is not proof of unchanged original executable bytes.
- File Bytes version 0, root -1, count 0; image offset `80000000`, database
  block size 16384 and master root 1.
- Text1: `800055e0..802b0160`, length 2796416, block/subblock 1, root 21.
- Data3: `802bae60..803af120`, length 1000128, block/subblock 5, root 199.
- Data5: `80436a20..8043d500`, length 27360, block/subblock 7, root 263;
  whole digest
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
- Each selected mapping requires subblock type 2, starting offset 0 and source
  offset 0, with the unchanged all-block mapping guard applied first.

| Fixed selection | SHA-256 |
| --- | --- |
| Cell `802d33b0`, target `80059cd0` | `3444a28cf2b80ab10b57c6aa3d926c09984284298a8ba75776022e6ef19058ff` |
| Cell `802d3b50`, target `802d3ff8` | `27b683898f029efc9c3c6c9e780fbb1e9cfd13387ebdba9e0443e733c076a0d5` |
| Row `802d4050`, states `(61,0)`, 2 bytes | `e7dac261e841e53eb65ac8c2a0e56544df49c46d71e8002d7764f92c66c4c868` |
| Handler `80059cd0`, 352 bytes | `52f4647dff3c3fd9cf6f26f6d9934465f5caad5a1a4487f6add64c6bbce14fea` |
| Helper `800690a0`, 160 bytes | `1a318a9de9150de8569ecb76c144241d23a41c69a7fcd668f4752ff51657587b` |

The two snapshots have identical selected values, operand reports and physical
traces. Offsets and lengths in this table are decimal; all spans are obfuscated.

| Address | Root / data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| `802d33b0` | 199 / 206 | 99664 | 1396 | 3392890 | 4 |
| `802d3b50` | 199 / 206 | 101616 | 3348 | 3394842 | 4 |
| `802d4050` | 199 / 206 | 102896 | 4628 | 3396122 | 2 |
| `80059cd0` | 21 / 43 | 345840 | 1902 | 722804 | 352 |
| `800690a0` | 21 / 46 | 408256 | 15184 | 785238 | 160 |

Each new read requires its literal address and width allowlist, exact mapping
and types, alignment and bounds, returned width, and digest. Each pointer cell
also requires its exact expected u32 target; the row requires its exact two
state values. Code decoding rejects an unsupported
instruction, unexpected reserved fields, a missing terminal return, or a
non-call branch outside the selected span. Output contains derived operands,
hashes and provenance, never raw executable ranges. The CLI accepts one
snapshot pathname and no address, width, target, raw, follow or execute option.
Shared readers and shared allowlists are unchanged.

## Double cue44 producer and row

The previously authenticated `8006f60c` constructor has these source operands
in [normal lifecycle evidence](actor-normal-lifecycle-evidence-2026-11-14.md):

- `8006f610`: `addis r4,0,-32723`; `8006f618`: `addi r4,r4,0x3b14`, forming
  source base `802d3b14`.
- `8006f698`: `lwz r0,0x3c(r4)`, whose fixed source is `802d3b50`.
- `8006f69c`: `stw r0,0x4f0(r3)`, the constructor's cue-table field producer.

The newly selected producer cell contains `802d3ff8`. Separately,
`packages/combat/src/data/familyCueTablesFull.json` lines 215–220 identify
constructor `8006f60c`, member `pl0003` and table `802d3ff8`; lines 397–400
record cue44 as `[61,0]`. `packages/combat/src/data/actionStreamTables.json`
lines 1668–1677 independently identify the same Double constructor and cue
table. The older [family cue-table research](nn-family-decode-2026-07-06.md)
section 4 records the same row. Those pre-existing records selected the fixed
two-byte row; the new snapshot evidence authenticates its actual values.

This proves the static constructor-source-to-row relationship without following
the returned pointer. It does not execute the constructor, assign ownership to
an unrelated live actor, authenticate the rest of its table, or make the
full-body state61 and upper-body state0 dispatch targets implementation-ready.
The constructor remains separate existing evidence and is not added to this
reader's two code spans.

## Handler schedule: `80059cd0`

The ABI prefix saves LR and r31. `80059cdc` loads r0 with one; `80059ce4` saves
the actor argument r3 in r31; `80059ce8` stores byte r0 at actor `588`.
`80059cec` loads `5e0`; `80059cf0` is `rlwinm. r0,r0,0,25,25`, selecting bit
`0x40`. `80059cf4` branches on equality/zero to the ground chain at `80059da4`.
The byte store therefore happens before either branch's first callee.

### Bit `0x40` clear: ground chain

Each call receives this same actor in r3. Every call except the last has a
following `cmpwi r3,0` and a nonzero branch to epilogue `80059e1c`. The next
callee sees all mutations from earlier calls. The handler does not snapshot
later actor fields in advance.

| Call site | Target | Existing evidence/owner boundary |
| --- | --- | --- |
| `80059da4` | `80068df8` | Existing cue0 terrain helper |
| `80059db4` | `800699d8` | Existing ordered actor input-test chain |
| `80059dc4` | `80069814` | Existing cue0 tail helper |
| `80059dd4` | `800696f4` | Existing cue0 tail helper |
| `80059de4` | `800690a0` | Independently selected in this reader |
| `80059df4` | `80069038` | Existing cue0 tail helper |
| `80059e04` | `80069354` | Existing cue0 tail helper |
| `80059e14` | `80068f9c` | Existing cue0 tail helper |

`80059e18` compares the final return to zero, but both outcomes immediately
reach the epilogue. The final `blr` is `80059e2c`. C calls the handler `void`;
its successful completion is not a new boolean admission result.

Existing evidence is in
[cue0/terrain](actor-cue0-lifecycle-evidence-2026-11-14.md),
[input testers](actor-input-testers-evidence-2026-11-14.md), and
[cue0 tail](actor-cue0-tail-evidence-2026-11-14.md). Those readers own their own
callee body evidence; this reader authenticates the call sites but does not
reselect those bodies. Integration must invoke their real owners rather than
substitute synthetic all-zero results.

### Bit `0x40` set: ordered air boundaries

The encoded fallthrough chain is:

| Call site | Target |
| --- | --- |
| `80059cf8` | `800699d8` |
| `80059d08` | `80069814` |
| `80059d18` | `80069210` |
| `80059d28` | `800693fc` |
| `80059d38` | `800696f4` |
| `80059d48` | `8006965c` |
| `80059d58` | `800695c4` |
| `80059d68` | `8006952c` |
| `80059d78` | `800691d8` |

Every listed call short-circuits to the epilogue on a nonzero return.
Only after all return zero does `80059d84` load actor byte `661`; `80059d88`
compares it to six, and `80059d8c` exits unless equal. Equality reaches
`80059d94 -> 80068f9c`. The last compare/conditional branch and unconditional
branch both lead to the same epilogue.

The first two calls have existing body evidence. The first unsupported air
callee in this bounded integration is `80069210` at `80059d18`. The new reader
does not claim to implement that body, subsequent air bodies, or any inferred
air no-op. The real earlier calls and byte store precede this boundary.

## Ground helper schedule: `800690a0`

The prefix saves LR and r31 and preserves the actor in r31. Three gates are
strictly ordered, with each failed gate returning zero without reading later
fields:

1. `800690b4`: unsigned byte `57a`; `800690b8`: mask `0x40`; `800690bc` branches
   to `800690c8` only when nonzero. Otherwise `800690c0` sets r3 to zero and
   `800690c4` branches directly to epilogue `8006912c`.
2. `800690c8`: word `5d4`; `800690cc`: mask `1`; `800690d0` branches to
   `800690dc` only when nonzero. Failure sets r3 to zero at `800690d4`, then
   branches to the same epilogue.
3. `800690dc`: word `5b4`; `800690e0`: mask `0x100`; `800690e4` branches to
   `800690f0` only when nonzero. Failure sets r3 to zero at `800690e8`, then
   branches to the epilogue.

When all gates pass:

1. `800690f0` loads r4 with five; `800690f4` calls `8006a750(actor,5)`.
2. `800690f8` compares its result to zero. `800690fc` branches to `80069128`
   on failure, where r3 becomes zero before the epilogue. No control mask or
   reset occurs on that path.
3. `80069100` loads actor word `5e0` after the successful cue call.
   `80069104` restores the actor argument to r3. `80069108` masks the loaded
   word to `0x00ff0000`; `8006910c` stores that value to `5e0`.
4. `80069110` calls `8005c080(actor)`. Its body is outside this reader and can
   remain an explicit refusal boundary after the preceding store.
5. Only after return, `80069114` **reloads** `5e0`, `80069118` sets return r3 to
   one, `8006911c` ORs `0x2000` into the newly loaded word, and `80069120`
   stores it. It does not re-use the pre-call masked value.
6. The epilogue restores LR and r31, releases the stack frame, and returns at
   `8006913c`.

The selected helper has no indirect call, pointer dereference through actor
descriptors, arithmetic beyond masks/OR, or hidden float instruction. Its
ordinary failed-gate behavior is demonstrated by the encoded schedule, not a
guess that unsupported attack logic is harmless.

## Explicit omissions and verification ceiling

- No neighboring cue cell or row, runtime/private RAM, actor descriptor, live callback
  pointer, asset record, animation stream or clone payload is selected.
- All handler callees except `800690a0` remain outside this reader, including
  `8006a750` and `8005c080`. Existing readers can establish specific earlier
  owners but do not turn unrelated unresolved bodies into returns.
- Cue44 control completion does not prove `80055568` playback dispatch,
  Double/Ninja attack callbacks, clip progression, clone construction, movement,
  collision, damage, target ownership or expiry.
- No archived/original instructions were executed. No payload was extracted to
  a new executable file. No original runtime, retired driver, installation,
  commit or publication was used.

## Checks

From the repository root:

```sh
python3 -m unittest discover -s research/tools/matching-decomp \
  -p test_archived_actor_x_playback_evidence.py -v
python3 research/tools/matching-decomp/read_archived_actor_x_playback_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python3 research/tools/matching-decomp/read_archived_actor_x_playback_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

Result: **19 tests pass**, including the optional archive tests running against
both real local snapshots, all 128 explicit per-instruction operand witnesses,
exact pointer targets, two row values, hashes and physical traces, independent
recorded row selection, extent markers and absent map rows,
type/bounds/hash/decode/terminal-branch refusals, real schema/mapping failures
before any new selection, authentication ordering, unchanged shared allowlists,
and rejection of arbitrary CLI options. The reader succeeds on both files.
The broader `test_archived_actor*.py` group also passes **271 tests**. All
relative links in this document resolve, and `git diff --check` passes.
Repository-wide build/browser checks belong to the separate integration work;
these focused static-evidence tests do not claim an aggregate product pass.
