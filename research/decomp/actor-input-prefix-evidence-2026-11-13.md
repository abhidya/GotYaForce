# Actor input prefix: archived source evidence

## Scope and provenance

This is derived instruction evidence from the two existing immutable local
ProgramDB snapshots. It is not execution of archived code, original-DOL
matching, live-oracle evidence, production ownership or playable parity. No new
input, raw executable output, shared-reader allowlist change, external transfer
or rig access is needed.

Inputs under `GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: SHA-256 `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: SHA-256 `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

`read_archived_input_prefix_evidence.py` first reuses the existing snapshot,
schema, executable-metadata, empty File Bytes, mapping, full data5-digest and
control authentication. It then checks each fixed range digest and emits only
decoded instruction operands, spans and authentication metadata. It has no
arbitrary-address, raw-range or execution options. Executable metadata is not
proof of an unchanged original DOL. No constants or direction-table contents
are loaded by this reader.

All four full spans produce identical operands and span metadata in both
snapshots. None of their instructions are silently omitted:

- `800685c0..800686f0`: 304 bytes, 76 instructions, SHA-256
  `ce30ce82c8a3802573cd9741dba970d10c207e00cb2307bc77d7031c1aae4758`.
- `80068980..80068b8c`: 524 bytes, 131 instructions, SHA-256
  `87ed4f07dd32d732c316aa47e87f7a9bab648605637c5bf7ec1299c742bb43ce`.
- `8006de44..8006dee8`: 164 bytes, 41 instructions, SHA-256
  `fd334ecbc181f71a71d64530d934c38e93884362c413354a07cb8a03e4a788f4`.
- `8008b73c..8008b7b0`: 116 bytes, 29 instructions, SHA-256
  `2bd123ab703e075e515d9b70d0029723e523eb86d60ca2cd3553796b59296908`.

The first three extents independently match
`../symbols/GG4E-CSM-20220412.map` entries at lines 799, 801 and 853.
`8008b73c` is **not a named entry in that map**. It starts immediately after
map entry `8008b650` of width `0xec` and ends at the next map entry `8008b7b0`.
Its entry and next entry are in `ghidra-export/chunk_0013.c:1914–1941`.
The other C exports are `chunk_0008.c:4669–4690,4797–4868` and
`chunk_0009.c:2995–3039`. C export is supporting context; all operand claims
below are checked against authenticated instructions, including details that
C simplification could obscure.

All spans use `MAIN_.text1`, block/subblock 1, chain root 21, obfuscated:

- `685c0`: data buffer 46, chain offset 405472, data offset 12400,
  physical offset 782454, length 304.
- `68980`: data buffer 46, chain offset 406432, data offset 13360,
  physical offset 783414, length 524.
- `6de44`: data buffer 48, chain offset 428132, data offset 2304,
  physical offset 805126, length 164.
- `8b73c`: data buffer 55, chain offset 549212, data offset 8738,
  physical offset 926248, length 116.

## Caller and bounded runtime stop

`800685c0` saves its actor pointer in r31, prepares r4 = actor+`0x5fc`,
and calls `80068980` at `800685d8`. Only after that call returns does it
prepare integer zero and store it using **stw** to actor+`0x5d4` at
`800685e4`. This is a raw 32-bit zero store, not an `stfs` or a float
calculation.

Its first following call is at `800685f8`, target `80068b8c`, with r3 actor,
r4 `0x802d38f8`, r5 actor+`0x614`, r6 `0x20`. A bounded runtime may implement
real input preprocessing, perform the actual `5d4` zero store, then refuse
this first unsupported call. It must not fake the call with a callback or
preload later owners before the earlier work completes. Earlier writes remain
real if a later access or call refuses.

For completeness, the authenticated caller has ten `68b8c` calls, with
(table address, actor offset, mask) in this exact order:

1. (`802d38f8`, `614`, `20`).
2. (`802d3904`, `618`, `40`).
3. (`802d3910`, `61c`, `80`).
4. (`802d391c`, `624`, `200`).
5. (`802d3928`, `600`, `1`).
6. (`802d3934`, `604`, `2`).
7. (`802d3940`, `608`, `4`).
8. (`802d394c`, `60c`, `8`).
9. (`802d3958`, `610`, `10`).
10. (`802d3964`, `628`, `2000`).

Numbers in that list are hexadecimal. It then calls `800686f0` at
`800686d8` and returns. Authentication of these operands is not an
implementation or validation of those callees or their tables.

## Direction helper: exact zero domain and first unsupported work

`8008b73c` receives X in r3, Y in r4 and a threshold in r5. Its exact prefix:

1. Save LR and allocate a 16-byte stack frame.
2. Mask low eight X and Y bits, then `extsb` each for the arithmetic.
3. Store original low X byte to stack+8 at `8008b758`.
4. Compute `mullw r3,r0,r0` (signed-byte Y squared) at `8008b75c`.
5. Store original low Y byte to stack+9 at `8008b760`.
6. Compute `mullw r6,r6,r6` (signed-byte X squared) at `8008b764`.
7. Compute `mullw r0,r5,r5` (full register threshold squared) at `8008b768`.
8. Add X squared and Y squared in r3 at `8008b76c`.
9. **Unsigned** `cmpl` r3 against r0 at `8008b770`.
10. `bc BO=12, BI=0` at `8008b774` goes to `8008b79c` only when
    the unsigned sum is **strictly less** than the unsigned threshold product.

The multiplication results are low 32 bits. No threshold byte truncation or
absolute-value operation exists. For the two reached positive thresholds 20
and 52, squares are exactly 400 and 2704, and signed-byte squared sums are
0..32768, so neither sum nor product wraps. Equality is outside the zero
return domain. Negative stick bytes are sign-extended, not treated as large
unsigned magnitudes. If this helper were generalized, threshold-square wrap
would have to remain explicit rather than silently using unbounded numbers.

The complete zero branch sets r3 to 0 at `8008b79c`, reloads LR at
`8008b7a0`, restores it at `8008b7a4`, restores SP at `8008b7a8`, and reaches
`blr` at `8008b7ac`.
There are no actor stores on this path, though the stack saves/stores above
are real source instructions.

Outside the zero domain, the first reached operations are `psq_l f2,8(r1),
W=1,I=4` at `8008b778` then `psq_l f1,9(r1),W=1,I=4` at `8008b77c`.
The first angular call is `bl 800452a0` at `8008b780`. These instructions
establish use of GQR4, **not its runtime configuration**. A bounded
zero-direction implementation must refuse before `8008b778` if it does not
implement and authenticate that conversion, rather than pretending the call
returned zero or inventing an angle callback.

The remaining authenticated angular tail masks the call result to low16,
adds `0x1000`, uses `rlwinm SH=19,MB=29,ME=31` to select an index in 0..7,
then `lbzx` from r13-31864. Neither r13's runtime value, table contents nor
angular result is established. This tail is not executed on the supported
zero branch and must not be represented as implemented.

## Input preprocessing and exact actor fields

`80068980` retains the actor in r30 and its independently supplied four-byte
input pointer p in r31. The caller above makes p=actor+`0x5fc`.
The fields reached are:

- p[0..3], corresponding to actor+`5fc..5ff` in this caller: byte flags and
  three distinct byte timers.
- actor+`5ca`,+`5cb`: byte stick X and Y.
- actor+`5b4`: 32-bit held input word.
- actor+`5b8`: **unsigned halfword** for the release operation.
- actor+`5bc`: 32-bit word used by the actual popcount callee.
- actor+`5d8`: repeatedly loaded/stored unsigned halfword.
- actor+`749`: byte destination for popcount.
- actor+`5d4`: caller's later word-zero destination, not written by `68980`.

A 32-bit big-endian owner beginning at `5b8` does not make the `lhz 5b8`
operation its low16: that halfword is the word's **high16**. Keep the source
width/address mapping explicit. This evidence does not select a JavaScript
owner, establish exclusive binding, or justify duplicate shadow fields.

### First direction gate and second direction gate

Read p[0] and test bit0. If clear, the actual load order is:
`689a8` **X5ca**, `689ac` threshold **20 decimal**, `689b0` **Y5cb**,
then `689b4` call `8b73c`. It is not Y-before-X. Mask the return to a byte
and test zero. A zero result skips all first-direction stores.

For a nonzero direction, the authenticated but unsupported angular-return
branch reloads p[0], ORs bit0 and stores it; loads `5d8`, clears low nibble
and stores; reloads `5d8`, ORs the direction byte and stores; reloads `5d8`
again and tests mask `0x000c`. It stores timer p[1]=3 when that mask is
nonzero, otherwise p[1]=2. These reloads are not interchangeable with a
single retained original halfword.

Next, independently reload p[0] and test bit1. If clear, the load order is
`68a10` **X5ca**, `68a14` threshold **52 decimal**, `68a18` **Y5cb**,
then `68a1c` call `8b73c`. Again, zero skips this direction's stores.

For a nonzero result, reload p[0], OR bit1 and store. Load `5d8`, apply
`rlwinm SH=0,MB=28,ME=23` and store, which clears bits4..7. Reload the
halfword once into H. The next store is low16 of
`H | ((H & directionByte) << 4)`, not merely `H | (directionByte << 4)`.
Then store p[1]=20. This branch is authenticated, not part of a direction0
runtime. Bit0/bit1 already set genuinely skip their corresponding helper call
and stick reads.

### Held acquisition and release

Independently reload p[0] and test bit3. If bit3 is clear:

1. Read actor+`5b4` once and mask `0x000f0000` into U.
2. If U is zero, skip acquisition stores and continue to timers.
3. Otherwise, OR bit3 into the already loaded p[0] value and store p[0].
   The source does not reload p[0] between U's load and this store.
4. Load `5d8`; apply `rlwinm SH=0,MB=24,ME=19` (`&0xf0ff` after
   halfword truncation); store at `80068a8c`.
5. **One** reload of `5d8` at `80068a90` supplies H for both its arithmetic
   shift right4 and its retained OR term. Store
   `H | ((U >>> 8) & (H >> 4))` at `80068aa0`.
6. Store p[3]=20 at `80068aa4`.

If bit3 was set, read `5b4` and mask the same bits. Nonzero skips release.
If zero:

1. Store p[0]=0, not just p[0] with bit3 cleared.
2. Load `5d8`, keep low12, and store at `80068acc`.
3. At `80068ad0`, load **lhz actor+5b8**.
4. At `80068ad4`, **reload `5d8`**.
5. Rotate the loaded `5b8` halfword using SH=12,MB=16,ME=19, which
   supplies `(halfword & 0x000f)<<12`; OR with the reloaded `5d8` and store.
6. Store p[2]=16 at `80068ae4`.

The order of the two halfword loads in steps3/4 matters. Each preceding clear
store and later reload is distinct source work; no all-at-once state snapshot
can substitute for it when reads/writes may fail or their order is observed.

### Timer order and signedness

Timers are processed **p[1], p[3], p[2]**, after the acquisition/release
stores. A freshly assigned timer is decremented in the same call.

For p[1], read a byte and `extsb.` it for the initial nonzero test. If nonzero,
subtract one from the zero-extended loaded byte, `extsb.` that result for CR0,
then store its low byte. Branch `BO=12,BI=1` skips the halfword clear only
if the resulting **signed byte is positive**. Otherwise load `5d8`, mask
`0xff00`, and store. Initial0 is untouched. Thus initial1 becomes0 and
clears; initial0x80 becomes0x7f and does not clear; initial0x81 becomes0x80
and clears; initial0xff becomes0xfe and clears. There is no saturation.

p[3] follows the same signed rule but uses `&0xf0ff` on `5d8` when clearing.
p[2] instead uses an unsigned initial-zero test and a masked-byte equality
check after subtracting one. Its `5d8 &0x0fff` clear happens **only** when
the stored decremented byte is zero. High-bit p[2] values do not cause the
signed-expiry behavior of the other two timers. Every reached clear reloads
`5d8` after the timer store; unchanged timers do not read the halfword.

### Actual masked popcount and final store

After all three timers, `68980` constructs mask `0x000f0f00` in r4,
passes the actor in r3, and calls `8006de44` at `80068b6c`. Only after that
real callee returns does `stb r3,0x749(r30)` at `80068b70` store its result.
It then restores LR/r31/r30/SP and returns.

`8006de44` first loads actor+`5bc`, ANDs the supplied mask, sets count0
and CTR4. The loop has eight explicit low-bit tests with conditional count
increments and an arithmetic right shift by1 after each test. `bdnz` repeats
four times, exactly32 input-bit tests. Arithmetic shifting does not add tests
beyond those32, so the return is the popcount of the masked original word.
An additional r6 register starts0 and increments7 per group; it has no actor
store or role in the returned count. There are no calls or stack writes in
this leaf function. For the reached mask `0x000f0f00`, the result is0..8.
There is no callback, copied held-input value or timer substitute for this
actual `5bc` read.

## Validation and limits

Run from the repository root:

```
python -m unittest discover -s research/tools/matching-decomp -p 'test_archived_input_prefix_evidence.py' -v
```

Result: **11 tests passed, no skips**, with both existing local archives.
Tests assert all277 instruction operands in exact order using explicit
expected source operands, including every store/reload, branch, signed
record form, rotation mask, multiply and paired-load selector. They also
check full coverage, matching snapshots, no raw output fields, strict input
types, selected decoder forms, authentication and mapping failures before
fixed reads, range-width/digest failures before decoding, mutation rejection
at every instruction, and refusal of arbitrary CLI options.

Both standalone reader invocations also completed successfully. These checks
prove archived-source evidence, not the runtime's field ownership, callback
absence, numerical implementation or integration behavior. Those require
separate source-runtime tests. The isolated evidence task did not run
contributor/documentation aggregate checks, commit, push, publish, acquire
inputs, inspect the rig or execute original/archive code.

## Bounded TypeScript runtime and shared owners

`actor-input-prefix.ts` supplies genuine direction-zero preprocessing rather
than a successful callback. Signed-byte stick cells are explicit inputs. Below
20/52 strict integer radii, the actual helper returns zero and does not alter
direction latches. If a required direction call is outside that domain, the
runtime refuses at `8008b778` before paired-load/GQR, angle and table work.
Already-latched direction bits genuinely skip those calls and stick reads.
The supported suffix executes acquisition/release, signed timers and actual
masked popcount, then the caller's5d4 clear and explicit68b8c refusal.

Existing actual RomActor `statusWord5b4`, `statusWord5bc`, `inputEdge5d4` and
`inputHeld5d8` remain the only owners. `statusWord5bc` is promoted from existing
family scratch to an optional declared field with no default or guessed codec
mapping. The old5d8 u32 annotation was incorrect: it is now u16, and generated
map plus codec regression prove that encoding it cannot overwrite adjacent
actual fbState5da/ubState5db. This annotation correction is not a retail input
capture or a complete host input migration.

The exact Borg retained by the existing gauge and tick graph owns its existing
`sourceArrowMash749`. The runtime writes that same field, never a new actor
byte749 shadow. Claiming it permanently excludes the approximate browser
`stepArrowMashInput` producer before any of that producer's reads or writes.
Normal unclaimed Borgs keep their prior behavior. No synthetic edge generation
from `sourceArrowInputButtons`, browser direction quantization or atan2 is used.
Only otherwise missing unsigned halfword5b8, signed stick5ca/5cb and raw bytes
5fc..5ff get sealed explicit binding cells. Halfword5b8 is separately decoded
at that address, not a truncation of a previous u32 input word.

Competing legacy `inputFlags5d4`, `inputFlags5d8`, `inputEdges5bc`, actual749
aliases and duplicate binding properties are refused, including an own property
whose value is undefined. Binding does not delete, migrate or mirror them. Own
data fields, stable synchronous records and non-proxy inputs are host bounds.
Checks are lazy at each reached read/store, so a late failure retains all
previous effects rather than rolling them back or clearing the edge early.

The tick prefix accepts only a genuine input runtime and verifies the same
actual actor/Borg and retained binding. Without it, historical685c0 refusal is
unchanged. With it, genuine stage and optional cue effects precede real input
work; any refusal retains those effects and consumes the raw-distance epoch.
Full59068, ten input machines, charge686f0, raw PAD/CPU capture, active-direction
angles/tables, full lifecycle and exclusive live ownership remain open.

Checked-in tests cover all256 values for each of the three timer bytes, all256
masked popcount combinations, both signed threshold boundaries, missing and
readonly late destinations, aliases, owner identity/reentry and legacy producer
exclusion. Synthetic DAT/setup composition retains the actual stage/cue/input
owners and separate later wait, setup, movement, matrix/linked-copy and history
cadence. No original-game replay or browser-playability claim is made.
