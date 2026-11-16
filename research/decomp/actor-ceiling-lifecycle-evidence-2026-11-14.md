# Actor-ceiling lifecycle: fixed archived evidence

## Result and boundary

Both existing archived ProgramDB snapshots authenticate the complete
`80068030..800680d4` ceiling helper (**164 bytes, 41 instructions**), the
complete `8008b290..8008b29c` leaf (**12 bytes, 3 instructions**), and the
exact positive-zero float32 constant at `804375d0`. Every instruction is
represented in order; both snapshots produce identical operands and traces.

Three distinctions matter for a bounded implementation:

- The leaf returns an **unsigned** byte from `PTR_DAT_80433934 + 0xd9`.
  Its `lbz` has no sign extension. The separate actor byte at `1db` is
  sign-extended and tested only after the leaf returns zero.
- The first stage pointer load precedes the single-precision addition, while
  its `+34` float read follows the addition. After storing `48=+0`, the
  pointer and actor `668` are reloaded. The second stage `34` and actor `30`
  are both read before the single-precision subtraction.
- All floating conditional branches test **not GT**, not a synthetic
  less-than-or-equal operation. For finite values the final comparison selects
  actor `30` only when strictly greater; equality selects the rounded
  difference, including that operand's signed-zero identity.

This is offline archived evidence, not original instruction execution,
unchanged original-DOL identity, live ownership, runtime integration, retail
parity or playable-game proof. No global pointer value or pointee is read by
this reader. No NaN payload, exception, denormal or live FPSCR behavior is
established. A bounded implementation must state its supported finite float32
domain and refuse unsupported inputs or arithmetic at the actual source step.

Artifacts:

- [Fixed reader](../tools/matching-decomp/read_archived_actor_ceiling_evidence.py)
- [Complete operand and fail-closed tests](../tools/matching-decomp/test_archived_actor_ceiling_evidence.py)
- [Existing caller evidence](actor-tick-prefix-evidence-2026-11-13.md)
- [Prior actor-rate evidence](actor-rate-lifecycle-evidence-2026-11-14.md)

Only the two named instruction spans and one named float32 are newly selected.
The shared archive readers and allowlists are unchanged. The CLI accepts only
an existing snapshot path; there are no address, width, pointer-following,
index, raw-output or execution options. No proprietary binary is output,
original instructions executed, dependencies installed, content published, or
retired port driver started.

## Extents and authentication

| Function | C entry/next entry | Map size | Final decoded return |
| --- | --- | --- | --- |
| Ceiling helper | `chunk_0008.c:4335`, next `800680d4` | `0xa4` | `800680d0` |
| Match-state leaf | `chunk_0013.c:1674`, next `8008b29c` | `0xc` | `8008b298` |

The entries and widths agree with
`research/symbols/GG4E-CSM-20220412.map:788,1102`. Here the map sizes, C next
entries and final decoded `blr` instructions agree; no padding is included.

The unchanged `read_archived_constants.inspect` authenticates the actual full
snapshot SHA-256, exact schemas, executable metadata, Gekko/Broadway big-endian
language, address maps, empty File Bytes, complete data5 hash and its existing
controls before any new selected read. A supplied digest alone is not trusted.
The unchanged `read_archived_command_evidence.mappings` then checks the exact
text1/data3/data5 identities, block/subblock fields and all-block overlap. The
new reader separately requires the exact data5 tuple. There is no new data3
payload selection.

Fixed reads reject noninteger fields, nonunique allowlist matches, wrong
roots, wrong widths, unaligned/out-of-block selections, changed span digests
and changed constant bits. A span is hashed before decoding; an unrecognized
instruction makes the entire selection fail rather than silently disappearing.
The selected decoder rejects reserved sign-extension, comparison, floating
arithmetic and link-register fields.

Existing snapshots under
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Imported executable SHA-256 metadata is
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
This is metadata from the archived program, not a newly acquired or hashed
original executable. File Bytes is version 0, root -1, count 0. Block size is
16384, master root 1, and image offset `80000000`.

Relevant mappings, with subblock type 2 and starting/source offsets zero:

| Block | Start | Length | Block/subblock key | Chain root |
| --- | --- | --- | --- | --- |
| MAIN_.text1 | `800055e0` | 2796416 | 1 | 21 |
| MAIN_.data5 | `80436a20` | 27360 | 7 | 263 |

Full data5 SHA-256 is
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
The helper span SHA-256 is
`62727691b8e6edb70b8260d660b2d3587900c5309c58a924ab411265b1b797e6`;
the leaf span SHA-256 is
`bed0f0166ee2d2521bf4778199e5f52e29e6c02e88cb20f8e9ad9c4faed7c25e`.

## Constant, bases and physical traces

The previously recorded SDA2 basis `r2=8043ea20` resolves displacement
`-29776` at `8006807c` to `804375d0`. The exact four bytes are `00000000`,
IEEE float32 **positive zero**, with SHA-256
`df3f619804a92fdb4057192dc43dd748ea778adc52bc498ce80524c014b81119`.
Negative zero is not an interchangeable authenticated constant.

The previously recorded SDA basis `r13=8043b5a0` resolves:

- `-31852` at `8008b290` to global pointer identity `80433934`.
- `-21316` at `80068064` and `8006808c` to stage pointer identity `8043625c`.

The basis source is `docs/static-recompilation-spike.md:178-180`. These are
recorded bases, not live register captures. Matching C names and decoded
address arithmetic do not authenticate any runtime pointer value, object
ownership, pointee availability or permission to read arbitrary addresses.

Both snapshots yield these identical physical traces. All are obfuscated
storage; offsets and lengths are decimal.

| Selection | Root/data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| Helper `80068030` | 21 / 46 | 404048 | 10976 | 781030 | 164 |
| Leaf `8008b290` | 21 / 55 | 548016 | 7542 | 925052 | 12 |
| Constant `804375d0` | 263 / 264 | 2992 | 2992 | 4344758 | 4 |

## Complete ordered source behavior

All actor and pointee offsets below are hexadecimal. Stack save/restore and
every branch operand are included in the appendix and explicit test fixture.

### Leaf, early gates and first ceiling comparison

1. Save the stack frame, LR and r31; retain the actor in r31. Call `8008b290`
   at `80068044` before reading any actor field.
2. The leaf loads the global pointer identity at `80433934`, reads unsigned
   byte `d9` from that pointee, and returns it. There is no `extsb`, signed
   return conversion or extra global read. The caller compares the full
   zero-extended r3 with zero (`80068048`). Any nonzero byte branches to the
   return-zero path without reading actor `1db` or any floats.
3. Only for leaf zero, read actor byte `1db` (`80068050`), sign-extend it with
   `extsb.` (`80068054`), then branch to return zero if nonzero.
4. Read actor `24` into f1, then actor `668` into f0. Load the stage pointer
   identity at `8043625c` into r3 (`80068064`). Execute single-precision
   `fadds f1,f1,f0` (`80068068`). Only after that arithmetic read stage
   pointee `34` into f0 (`8006806c`). A failed/unsupported addition cannot
   be modeled as having already read the upper-bound float.
5. `fcmpo` compares the rounded sum in f1 against stage `34` in f0.
   `bc BO=4 BI=1` at `80068074` branches to return zero when CR0.GT is clear.
   This source branch is not encoded as an affirmative LT-or-EQ test.
   On supported finite values, only a strictly greater sum reaches step 6.
6. Read actor `48` (`80068078`), then the exact positive-zero constant
   (`8006807c`). Compare actor `48` against that zero, and again branch to
   return zero when CR0.GT is clear. No actor `30`, second stage pointer or
   second `668` read has occurred on either gate-out path.

The C export's compound condition is useful orientation, not a replacement
for this access schedule or the decoded floating predicates. This report does
not claim full behavior for unordered operands: live exception controls,
NaN handling and payloads are outside the authenticated execution domain.

### Successful clamp, reloads, subtraction and tie selection

At `80068088`, store the already loaded exact positive zero into actor `48`.
This write precedes every following pointer access and arithmetic operation.
Then, in source order:

1. Reload the stage pointer identity (`8006808c`), without reusing the first
   pointer identity or assuming it still identifies the same object.
2. Reload actor `668` into f0 (`80068090`), without reusing its earlier value.
3. Read the newly identified stage pointee `34` into f1 (`80068094`).
4. Read actor `30` into f2 (`80068098`). This happens **before subtraction**.
5. Execute `fsubs f0,f1,f0` (`8006809c`), rounding the stage-upper-minus-height
   difference to single precision. The operand order is upper minus height.
6. Compare f2 (actor `30`) against f0 (the rounded difference). The same
   not-GT branch goes to `800680b0`; ordered strict-GT instead falls through
   to `800680a8` and stores f2 into actor `24`.
7. The not-GT path stores f0 into actor `24`. For finite equal operands this
   chooses the **difference**, not actor `30`; keep the selected operand's
   zero sign. A generic maximum function must not change this tie choice.
8. Set r3 to 1, restore the saved registers/stack and return at `800680d0`.
   Earlier gate-outs set r3 to 0 before the same epilogue.

The only actor stores in the complete helper are `48=+0`, then one selected
value into `24`. Thus a later unavailable stage pointer, height, upper value,
saved Y or unsupported subtraction cannot erase the completed `48` store.
Nor may a failed subtraction omit the prior source read of actor `30`.
The two ordered arithmetic operations must remain separate single-precision
steps; no reassociation, eager flattening of all reads, substitute upper value
or clamping of an unsupported input is justified by this evidence.

### Actual caller end: reuse, do not expand

The existing tick-prefix reader already authenticates the complete
`80059068..80059138` caller: 208 bytes, 52 instructions, SHA-256
`ea22383e1d48094534b9c882b22400b794423bdea5657be04bcfab050da3716c`.
This new reader does not reselect or expand it. The focused tests reuse the
unchanged caller reader's fixed range after snapshot authentication.

At `8005911c` the caller moves its retained actor into r3; `80059120` calls
`80068030`. The only following instructions are LR/r31 loads at `59124` and
`59128`, `mtlr` at `5912c`, SP restoration at `59130`, and `blr` at `59134`.
There is no later call or result test. The exported caller is `void` in
`chunk_0007.c:2083`; it ignores the ceiling helper's 0/1 result.

The caller's map size is `0xd0`, hence end-exclusive `80059138`. Its **next
C entry is `8005913c`**, not `80059138`. The intervening four bytes are
outside the caller selection and are not read or attributed here. A C-next-
entry claim for this caller would be inaccurate even though the two new
helper extents do agree with their next entries.

## Reproduction and focused verification

From repository root, using existing stdlib Python only:

```sh
python research/tools/matching-decomp/read_archived_actor_ceiling_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python research/tools/matching-decomp/read_archived_actor_ceiling_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
PYTHONPATH=research/tools/matching-decomp python -m unittest \
  test_archived_actor_ceiling_evidence -v
```

All **18 focused tests pass**, with both local archive inputs present and no
skips. The tests check every derived operand, full selected coverage, both
map/C/return extents, unsigned leaf and signed actor gate, exact positive zero,
recorded base arithmetic, lazy source accesses, repeated reads, ordered
single-precision operand direction, final tie selection, and the existing
caller's true final call and epilogue. They also test authentication and map
failure ordering, malformed reserved encodings, forbidden CLI options,
refusal of pointer-global data reads, every selected instruction mutation in
both snapshots, and every selected constant-byte mutation.

A combined run with constants, command, actor-status, actor-rate, tick-prefix,
ready-lifecycle, control-effect and cue-reset evidence passes **140 tests**,
with no skips. Both fixed-reader CLI runs succeed. The complete appendix
matches the explicit operand fixture, and all three new files pass whitespace
checks.

These are evidence-reader tests, not contributor/build, runtime integration,
retail parity, full floating environment or gameplay acceptance checks.

## Appendix: complete derived operands

All 44 instructions follow in source order. Numbers other than addresses are
decimal. Raw instruction words and executable byte ranges are not included.

```text
80068030 stwu rA=1 displacement=-16 rS=1
80068034 mflr rD=0
80068038 stw rA=1 displacement=20 rS=0
8006803c stw rA=1 displacement=12 rS=31
80068040 or rS=3 rA=31 rB=3 Rc=0
80068044 bl target=8008b290 AA=0
80068048 cmpi BF=0 L=0 rA=3 immediate=0
8006804c bc BO=4 BI=2 LK=0 target=800680bc AA=0
80068050 lbz rD=0 rA=31 displacement=475
80068054 extsb rS=0 rA=0 Rc=1
80068058 bc BO=4 BI=2 LK=0 target=800680bc AA=0
8006805c lfs fD=1 rA=31 displacement=36
80068060 lfs fD=0 rA=31 displacement=1640
80068064 lwz rD=3 rA=13 displacement=-21316
80068068 fadds fD=1 fA=1 fB=0
8006806c lfs fD=0 rA=3 displacement=52
80068070 fcmpo crD=0 fA=1 fB=0
80068074 bc BO=4 BI=1 LK=0 target=800680bc AA=0
80068078 lfs fD=1 rA=31 displacement=72
8006807c lfs fD=0 rA=2 displacement=-29776
80068080 fcmpo crD=0 fA=1 fB=0
80068084 bc BO=4 BI=1 LK=0 target=800680bc AA=0
80068088 stfs rA=31 displacement=72 fS=0
8006808c lwz rD=3 rA=13 displacement=-21316
80068090 lfs fD=0 rA=31 displacement=1640
80068094 lfs fD=1 rA=3 displacement=52
80068098 lfs fD=2 rA=31 displacement=48
8006809c fsubs fD=0 fA=1 fB=0
800680a0 fcmpo crD=0 fA=2 fB=0
800680a4 bc BO=4 BI=1 LK=0 target=800680b0 AA=0
800680a8 stfs rA=31 displacement=36 fS=2
800680ac b target=800680b4 AA=0
800680b0 stfs rA=31 displacement=36 fS=0
800680b4 addi rD=3 rA=0 immediate=1
800680b8 b target=800680c0 AA=0
800680bc addi rD=3 rA=0 immediate=0
800680c0 lwz rD=0 rA=1 displacement=20
800680c4 lwz rD=31 rA=1 displacement=12
800680c8 mtlr rS=0
800680cc addi rD=1 rA=1 immediate=16
800680d0 blr
8008b290 lwz rD=3 rA=13 displacement=-31852
8008b294 lbz rD=3 rA=3 displacement=217
8008b298 blr
```
