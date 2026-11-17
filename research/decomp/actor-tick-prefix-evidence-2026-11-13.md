# Actor tick prefix and support-contact no-support evidence

## Result and boundary

Both existing authenticated local ProgramDB snapshots agree on all **52**
instructions of `80059068` and the selected **20 + 6** entry/return instructions
of `80067a70`. The fixed reader represents every instruction in those three
spans. It explicitly leaves **166 of 192 instructions** in `80067a70`
unrepresented. This proves archived instruction operands and order, not live
FPSCR, original-DOL identity, runtime ownership, producer freshness, or gameplay
parity. No archived code is executed.

The concrete prefix is:

1. Load actual float760 and B4, divide with `fdivs`, then store760.
2. Load actual float764 and freshly load B4, divide with `fdivs`, then store 764.
3. Call actual `8005bab8`, then actual `80067a70`, on the same actor.
4. The next call is **`80059e58` at `800590ac`**. A runtime that has only the
   first two callees must refuse here, not report a completed tick or skip it.

`8005bab8` is covered separately by
[gauge/scale evidence](actor-gauge-scale-evidence-2026-11-13.md). This reader
authenticates its caller, not that callee's body again. Evidence of later call
sites in the complete `80059068` function is not implementation of those calls.

## Sources and authentication

- Decompiled C: `research/decomp/ghidra-export/chunk_0007.c:2083-2107`
  (`80059068`) and `chunk_0008.c:4094-4171` (`80067a70`). The instructions,
  rather than C statement grouping or host-field names, establish the order.
- Exact function extents: `research/symbols/GG4E-CSM-20220412.map:713,781`:
  `80059068 + d0 = 80059138`, `80067a70 + 300 = 80067d70`.
  The next Ghidra C marker is `8005913c`, not the map's `80059138` end; the
  intervening four bytes are not included or guessed to be part of this function.
- Input directory remains the existing local
  `research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`.

| Snapshot | Whole-file SHA-256 |
| --- | --- |
| db.3.gbf | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| db.4.gbf | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Unchanged `read_archived_constants.inspect` checks whole-snapshot hashes,
schemas, big-endian Gekko/Broadway language, executable metadata, address map,
empty File Bytes table, full data5 hash and existing controls before new reads.
Unchanged `read_archived_command_evidence.mappings` checks exact block/subblock
identities and overlaps. The shared readers and their allowlists are untouched.
Text1 is `800055e0`, length 2796416, root 21. File Bytes is version 0/root -1/count 0.
The recorded executable SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`
is import metadata, not independent proof of unchanged executable bytes.

| Fixed span | Bytes / instructions | SHA-256 |
| --- | --- | --- |
| `[80059068,80059138)` | 208 / 52 | `ea22383e1d48094534b9c882b22400b794423bdea5657be04bcfab050da3716c` |
| `[80067a70,80067ac0)` | 80 / 20 | `9129c95f317a2e7bdabee44f8501fdfcc548e377cfbe72136241d49f0586974c` |
| `[80067d58,80067d70)` | 24 / 6 | `a0c187512d546cf9453e4196cd6494239a580f0fa7262d0c48ec3eceac34c994` |

All selected bytes are digest-checked before decoding. The omitted support
body is `[80067ac0,80067d58)`, 664 bytes/166 instructions. Whole-snapshot
authentication includes its storage, but this reader does not separately
span-check or decode that body and makes no claim about its instruction order.
There are no new constant reads.

Both archives have identical physical traces. Numbers here are decimal; all
three use root 21 and obfuscated ProgramDB storage.

| Span entry | Data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| 80059068 | 42 | 342664 | 15104 | 719622 | 208 |
| 80067a70 | 46 | 402576 | 9504 | 779558 | 80 |
| 80067d58 | 46 | 403320 | 10248 | 780302 | 24 |

## Exact tick prefix

PCs and actor offsets below are hexadecimal. `59078` saves incoming actor r3
in r31. `5907c/59080` load f1 from 760 and f0 from B4; `59084` is
`fdivs f0,f1,f0`; `59088` stores f0 to 760. Only then do `5908c/59090`
load 764 and reload B4, with division at 59094 and store 764 at 59098.
There is no reciprocal multiply, double division or shared denominator load.
The first store precedes the second source load.

`5909c` calls 5bab8. `590a0` restores r3 from r31; `590a4` calls 67a70.
`590a8` again restores r3; `590ac` calls 59e58. Normalization therefore uses
the B4 values read **before** scale/tier interpolation in 5bab8. A scale change
inside 5bab8 does not retroactively change those divisions.

The complete direct-call order is 5bab8, 67a70, 59e58, 685c0, 5a190, then
conditionally 59f5c, 5a144, followed by 5a298, 5a378, 68030. After 5a190, a nonzero
result branches from 590c4 to 5910c. Its zero-result path includes two indirect
calls: signed byte 5e4 indexes the table base 802d3300 for `bctrl` at 590e8;
actor 4c8 supplies the target for `bctrl` at 590f8. Neither those downstream
targets nor the table contents are reconstructed by this evidence.

A bounded host implementation needs actual 760/764 and B4 owners, not copied
normalization sidecars. If it refuses a later operation, prior source-ordered
stores remain part of the reached prefix. Any finite-only division policy or
RN00/NI0 arithmetic model is an explicit runtime domain restriction, not a
fact about live FPSCR established by these archives. C provenance identifying
raw 760/764 producers at 8006ae60/8006bda8 does not authenticate their sqrt,
arithmetic sequence, invocation cadence or the freshness of a runtime value;
those producer functions are outside this reader.

## Support-contact entry and three genuine no-support returns

`67a88` retains actor r3 in r30. The two writes happen unconditionally before
any contact gate:

- `67a8c` loads actual actor flags 5e0. `67a90` is `rlwinm SH0,MB12,ME10`,
  the wraparound mask `ffefffff`, clearing only bit `00100000`.
  `67a94` stores the result to actual 5e0.
- `67a7c` had set r0 to 0; `67a98` byte-stores it to actual 598.

Then the function short-circuits in this exact order:

1. `67a9c` byte-loads actor 1db. `67aa0` sign-extends with Rc 1, setting CR0.
   `67aa4`, BO 12/BI 2, takes the equality branch to 67d58 when 1db is zero.
   This path never loads pointer 1e4 or dereferences a support object.
2. Otherwise `67aa8` loads pointer 1e4 into r31; `67aac` compares it unsigned
   with zero. `67ab0`, BO 12/BI 2, returns via 67d58 if it is null.
3. Otherwise `67ab4` loads byte 0 through that retained pointer. `67ab8`
   sign-extends with Rc 1; `67abc`, BO 12/BI 2, returns via 67d58 if byte 0 is zero.
   A nonzero support byte falls through to the **unrepresented** body 67ac0.

All three selected branches test equality, not positive/nonnegative values.
At 67d58 the six instructions restore LR/r31/r30 from the stack, release the
frame and return at 67d6c. There are no additional actor reads, writes or calls
on these returns. Thus the no-support path is real behavior, including the two
initial stores, not an invented no-op or a stand-in for the support body.

Runtime binding must preserve actual flags 5e0, 598 and 1db. The existing
`SourceCollisionActor.linkedOwner1e4` view must not be shadowed by a new fake
pointer owner. Admitting only the 1db==0 path is a defensible narrower runtime
domain: after the two clears, nonzero 1db can explicitly refuse at the missing
pointer/owner step. An unavailable owner must not be treated as a null pointer.
Similarly, a nonnull pointer needs its real byte 0 owner before the third
predicate can be accepted. These are implementation boundaries, not extra
source branches. Once 67a70 genuinely returns, the tick's next boundary is 59e58.

## Reproduction and controls

```bash
python3 -m unittest discover -s research/tools/matching-decomp -p test_archived_tick_prefix_evidence.py
python3 research/tools/matching-decomp/read_archived_tick_prefix_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
```

The focused suite passes **16 tests**, including both archives. It checks all 78
decoded positions, fixed hashes, physical traces, exact load/divide/store and
call order, source masks, short-circuit predicates, and the complete no-support
epilogue. It verifies the explicit 166-instruction gap and the downstream direct
and indirect call sites without executing them. One-bit mutations at each of 78
instruction positions fail the span hash before decoding. Synthetic controls
cover authentication before parsing, mapping/root/offset/type/overlap/image
failures before reads, fixed-width/hash failures, no silent instruction omission,
reserved/unsupported forms, and rejection of arbitrary-address/raw/execution
CLI options. Archive tests explicitly skip when both private inputs are absent.

Output is derived operands, hashes, coverage and storage traces, never raw
executable ranges. No executable fixture, new acquisition/capture, transfer,
upload, install, network access, rig/process inspection, execution, push or
publication was used for this work.
