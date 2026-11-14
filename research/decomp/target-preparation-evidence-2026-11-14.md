# Target preparation: bounded archived instruction evidence

Date: 2026-11-14. Investigation base:
`5871c46f13b5604b056dddf829ea8413aadc1f54`. No commit or push.

The [fixed reader](../tools/matching-decomp/read_archived_target_preparation_evidence.py)
authenticates the complete `8006ae60` body, **1520 bytes / 380 instructions**.
Both existing snapshots agree on all operands, control flow and physical spans.
The [independent fixture and inverse tests](../tools/matching-decomp/test_archived_target_preparation_evidence.py)
represent every instruction, reconstruct the complete selected-body hash, and
pass all **16 tests**. No constant, global payload, pointed-to object, callee
body, or reciprocal-square-root estimator implementation was newly selected.

The immediately usable behavioral boundary is precise: clear six bytes on each
active member of a six-actor contiguous region, reload the first-actor pointer,
then inspect the six actors in order. An active actor with signed status at
least one reaches the first unresolved call, `8006b450` at `8006af80`, before
any distance constant is loaded. The remaining body is fully described static
evidence, not permission to execute unauthenticated callees or substitute
plausible constants. A path with no eligible second-pass actor still reaches
the third pass, whose unconditional `actor+508` load must not be omitted.

This is archived ProgramDB static evidence, not original-DOL identity,
original-code execution, `MATCH`, live dispatch, runtime integration, a completed
frame or playability. The test inverse is synthetic fixture construction,
not source-instruction execution. No estimator code is imported. No shared
authenticator, mapping validator, decoder or existing allowlist changed.

## Frozen scope and exact extent

Before the first selected archive payload read, the scope was frozen in the
local `.tmp/target-preparation-evidence-20261114/scope-frozen.json`, SHA-256
`7c29f4e86636731b5e571dfc12ba5a67126ad40b41e935955c9a0429119de13a`.
It was not expanded.

| Selection | Exact width | Independent readable provenance |
| --- | --- | --- |
| `8006ae60` through `8006b450` exclusive | `0x5f0` / 1520 | `ghidra-export/chunk_0009.c:1223–1437`, `_index.tsv:1391–1392`, `research/symbols/GG4E-CSM-20220412.map:834` exact named size `000005f0` |

The target function closes at C line 1437; the next function marker is line
1441. The next entry is only an extent cross-check, not a selected callee body.
The map size, independently of adjacency, establishes the exact selected
extent. All decoded calls and pointers remain labels; none selects another
read. In particular, constants `80437658/60/68/70/74/78`, the `803c4e84`
pointer payload and every actor or target remain unselected payloads.

## Authentication and reproducibility

Unchanged `read_archived_constants.inspect` authenticates the complete actual
snapshot SHA-256, supported ProgramDB schemas, PowerPC identity, address map,
executable metadata, empty File Bytes table, and existing full-data5/control
checks before any new selection. Unchanged `command.mappings` validates its
text/data mapping identities, bounds, initialization and overlap constraints.
Unchanged `normal.mapping_evidence` then verifies the exact typed text tuple.
Only afterward does the reader request the fixed body, verify its length and
SHA-256, and decode it. These original authentication reads are retained;
"no constants selected" does not conceal or remove the authenticator's existing
full-data5 reads.

| Existing snapshot | Bytes | Complete SHA-256 |
| --- | --- | --- |
| `db.3.gbf` | 57655296 | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| `db.4.gbf` | 58802176 | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

The existing inputs are at
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`.
No input was acquired, changed, newly published, or copied into a raw payload
artifact. Reports contain derived operands, hashes and provenance only.

Both snapshots identify `boot.dol`, created with Ghidra `12.1.2`; File Bytes is
version 0/root −1/count 0; image offset is `80000000`. Executable metadata
SHA-256 `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is import metadata, not independently measured original-DOL identity. The
unchanged data5 authentication hash is
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

Exact text mapping: `(800055e0,802b0160,1,MAIN_.text1,1,2796416,21)`;
initialized subblock type 2, starting offset 0, source offset 0.

| Body SHA-256 | Root / buffer | Chain offset | Data offset | Physical offset | Bytes |
| --- | --- | --- | --- | --- | --- |
| `6b725b93ac0755d146b4a67fe61ec81127d98afccc77ca5c3fcd990fa199b50a` | 21 / 47 | 415872 | 6422 | 792860 | 1520 |

The selected span is in an obfuscated data buffer. After unchanged authentication,
the **entire additional chain trace** is exactly:

```
(21, 415872, 1520, 2796416)
```

Tests compare the complete traced read list against the authenticator's own
reads followed by this one selection. There is no data selection, pointer
following, arbitrary-address CLI, raw-binary output or original execution.

## First pass: ordered clear of active contiguous actors

The prologue saves LR and r27–r31 in a 48-byte stack frame. At `8006ae78`,
`addis/lwz` loads the first actor pointer from `803c4e84`. This is a pointer-cell
address, not actor storage. The pass visits six actor addresses
`first + i*1e00`, `i=0..5`, not six independently loaded table entries.

At each slot it loads the active byte, sign-extends with record (`extsb.`),
and skips the writes if zero. Any nonzero byte, including `80..ff`, is active.
For an active actor, six one-byte zero stores occur in this exact order:

1. `+58a`
2. `+58b`
3. `+58c`
4. `+58d`
5. `+7d2`
6. `+7d3`

The first four slots use offsets from the initial pointer. At `8006af0c`,
`lbzu r3,+7800(r4)` both loads slot 4's active byte and updates r4; slot 5 is
then addressed at `+1e00` from that updated base. This update does not reload
the global cell. There are no target loads, status guards, calls or floating
loads in this clearing pass. Actor contents are not snapshotted or pre-read.

## Second pass: eligible actor and target-distance preparation

At `8006af5c`, the function **reloads** the first actor pointer from `803c4e84`
into r30 and resets the slot index. Every iteration checks:

- `8006af60`: load active byte, sign-extend, skip if zero.
- `8006af6c`: load `+18`, sign-extend, compare against 1, skip if less.

Thus statuses `01..7f` pass; `00` and `80..ff` do not. On a skipped actor there
is no `+508` load in this pass. The eligible actor is passed in r3 to
`8006b450` at `8006af80`, and then again to `8006b7f4` at `8006af88`. These are
separate sequential calls. The active/status predicates are not rechecked
between or after them. No distance constant has been loaded before either
call. An implementation lacking authenticated callee behavior must stop before
the first call, not assume either call is a no-op.

After the two calls, the body loads `actor+508` into saved r29. Its subsequent
branches are fully covered by the operand fixture but depend on unselected
callees, constants and live memory.

### Primary target present

If saved `+508` is nonzero:

- Load a separate position-provider pointer from `actor+504`. Set r28 to
  `actor+20`, r27 to `provider+64`, then call `8020bc88` with those pointers.
- Compare returned f1 against the binary32 value loaded via `r2−29640`.
  Only ordered GT enters the reciprocal-square-root refinement; other CR
  outcomes skip it. Store the resulting binary32 distance at `actor+758`.
- Load horizontal components in order: actor X, provider X, actor Z,
  provider Z. Compute two single-precision differences, square separately
  with `fmuls`, and add with `fadds`. Apply the analogous conditional
  refinement, then store `actor+75c`.
- Set r3 to actor and r5 to zero, **reload `actor+508` into r4** at `8006b094`,
  then call `8006d228` at `8006b098`. This call uses the fresh field value,
  not saved r29.
- Read/OR/write `actor+7d2` with bit 1. Then load actor team `+88` followed by
  saved-r29 target team `+88`, sign-extend both and compare. A different team
  sets bit 2 through another read/OR/write. The team test deliberately uses
  the earlier saved target pointer, even after the fresh-pointer call.
- Select threshold `actor+814` for a different team or `actor+818` for the
  same team. Compare threshold against `actor+758` and combine CR GT or EQ
  with `cror`; if true set bit 4. Unordered does not set it.
- Read `actor+5e0` once. Bit `80` selects index 2, otherwise bit `40` selects
  index 1, otherwise index 0. Read scale `actor+b4`, the unselected baseline
  constant via `r2−29616`, and table value `actor+838+4*index`.
- On scale LT baseline, multiply table value by scale. On GT, subtract the
  baseline, load another constant via `r2−29612`, perform the recorded
  single fused multiply-add, then multiply table value. EQ or unordered
  leaves the table value unchanged. Compare that threshold against a fresh
  `actor+758` load, again accepting ordered GT or EQ, to set bit 8.

The exact scalar operations, FPR dependencies, record bits and load/store
sequence are in the 380-row fixture. A mathematical `sqrt` or approximate host
float expression is not claimed equivalent.

### No primary target

At `8006b180`, load the unselected binary32 constant via `r2−29608` and store
`actor+75c` **before** `actor+758`. Load signed heading `actor+72` and call
`80045204`. Reload `actor+75c`, single-multiply by returned f1 and store
`actor+50c`. Load the pointer at `actor+4b0`, then its signed byte `+10`;
compute `48*index+8f0`, perform an indexed **floating** load from the actor,
and a floating store to `actor+510`. This is not a demonstrated integer
bit-copy despite the readable C's `undefined4` wording. Reload heading, call
`80045238`, reload distance, multiply and store `actor+514`.

### Secondary target

At `8006b1d0`, load `actor+cc`. If nonzero, load the position-provider pointer
at `actor+c8`; the source vector is provider `+64` and the actor vector is
`actor+20`. Before the `8020bc88` call at `8006b208`, copy position words in
this exact order: load source X, load source Y, store actor `+518`, store
actor `+51c`, load source Z, store actor `+520`. This is not three preloaded
values and not three interleaved load/store pairs.

The returned three-dimensional distance is stored at `actor+760`, and the
horizontal distance at `actor+764`, using the same recorded arithmetic and
conditional refinement patterns. With a zero `+cc`, the default constant is
stored at `+764` before `+760`; signed heading calls, signed parameter index
and floating vector accesses mirror the no-primary-target path, writing
`+518/+51c/+520`.

Every second-pass iteration increments the slot index and pointer by `1e00`;
`8006b348` branches back while signed index < 6. The global cell is not
reloaded between these six iterations.

## Third pass: association flags and important read order

At `8006b358`, the global first-actor pointer is reloaded again. For every
slot, including an inactive one:

1. `8006b35c`: load actor active byte.
2. `8006b360`: **unconditionally load actor+508** into r5.
3. `8006b364`: sign-extend active with record.
4. `8006b368`: branch away if inactive.

Therefore the `+508` read occurs before the active test, but not before the
active-byte load. Reordering into a conventional short-circuit C expression
would lose this observable read. There is no `actor+18` status guard here.

Further guards, each only after the preceding guard passes:

- `+508` target is nonzero.
- Target `+83` byte, sign-extended, is zero.
- Actor `+7d3` bit 0 is clear.
- Load target team `+88`, then actor team `+88`; sign-extend both and require
  different teams. Actor team is saved in r8 for the inner loop.
- Load actor `+75c`, then actor `+814`; compare distance against threshold.
  `8006b3b0` skips on **GT only**. LT, EQ **and unordered** enter the scan.
  This differs from the readable C's `distance <= threshold` expression.

For an actor passing these guards, `8006b3bc` reloads the global first-actor
pointer for a six-slot contiguous inner scan, not a pointer-table traversal.
For candidate indices 0 through 5:

- Compare candidate index to outer actor index and skip self before reading
  the mask.
- Load target `+58a` anew for that candidate, sign-extend, and test it against
  `1 << candidateIndex` using `slw/and.`.
- Only on a mask hit load the candidate team `+88`, sign-extend, and compare
  against saved actor team r8. There is no candidate active/status check.
- On the first same-team hit, execute three separate read/OR/write sequences
  in order: actor `+7d3 |= 1`, candidate `+7d3 |= 1`, target `+7d3 |= 2`.
  The later loads observe earlier stores if addresses alias. Then leave the
  inner scan immediately.

A failed candidate advances its pointer by `1e00`; CTR controls six attempts.
The outer index/pointer then advances and repeats until six actors have been
visited. No calls occur in this third pass. The function restores registers,
stack and LR and returns at `8006b44c`.

## Complete callee inventory and estimator boundary

There are 50 control-flow instructions: 33 conditional branches, 7 direct
unlinked branches, 9 linked calls and one return. Every non-call target remains
inside the fixed body. The nine **static call sites**, in address order, are:

| Site | Target | Arguments established at this boundary |
| --- | --- | --- |
| `8006af80` | `8006b450` | r3 = actor |
| `8006af88` | `8006b7f4` | r3 = actor |
| `8006afac` | `8020bc88` | r3 = actor+20; r4 = loaded actor+504 provider+64 |
| `8006b098` | `8006d228` | r3 = actor; r4 = freshly loaded actor+508; r5 = 0 |
| `8006b190` | `80045204` | r3 = freshly loaded signed heading+72 |
| `8006b1c0` | `80045238` | r3 = freshly loaded signed heading+72 |
| `8006b208` | `8020bc88` | r3 = actor+20; r4 = loaded actor+c8 provider+64 |
| `8006b2fc` | `80045204` | r3 = freshly loaded signed heading+72 |
| `8006b32c` | `80045238` | r3 = freshly loaded signed heading+72 |

The four `frsqrte` sites are `8006afbc` (f2←f1), `8006b03c` (f1←f4),
`8006b218` (f2←f1), and `8006b298` (f1←f4). All operands are represented;
record/reserved bits are fixed and mutation-tested. Each site is followed by
the exact double `fmul/fnmsub` refinement sequence, final `frsp`, temporary
single store/reload and final field store. The estimate's implementation,
live FPSCR exception/rounding state and unselected constant values are not
established. No existing estimator was imported or silently substituted.

## Validation and limitations

Run from the repository root:

```
cd research/tools/matching-decomp
python -m unittest -v test_archived_target_preparation_evidence
```

All 16 tests pass with both existing snapshots present. Checks include:

- Complete independent literal operand/address inventory and exact source,
  index and map extent controls.
- Independent inverse bit placement for all 380 instructions, reconstructing
  the exact 1520-byte body SHA-256 without using a reader report at test time.
- All 12,160 single instruction-bit mutations: rejected, or produce different
  operands which re-encode to exactly the changed word. No admitted bit is
  silently discarded.
- All 12,160 selected-payload bit mutations rejected by hash **before decode**.
- All 267 mutable control-flow metadata fields independently corrupted and
  refused; exact nine-call inventory, 50-flow inventory and internal branches.
- Prefix clear offsets/order, signed statuses, per-pass pointer reloads,
  no floating load before the first two calls, third-pass load ordering,
  saved actor team, candidate mask/team order, and sequential alias-sensitive
  read/modify/write flags.
- Four estimator operand sites, six unselected r2-relative constant offsets,
  ordered range tests versus the third pass's unordered-admitting GT guard.
- Invalid/duplicate selections and typed mappings refused before reads;
  missing/short/long inputs and unsupported CLI requests refused.
- Whole-snapshot digest/schema refusal before selection, unchanged complete
  authentication trace, exact physical spans, and no raw-payload output.

The work selects only one complete function body. It does not close any of its
callees, authenticate the distance constants as selected values, read initial
global state, emulate Gekko's reciprocal estimate or execute the original
instructions. Runtime behavior beyond explicitly supported memory and call
boundaries remains partial rather than guessed.
