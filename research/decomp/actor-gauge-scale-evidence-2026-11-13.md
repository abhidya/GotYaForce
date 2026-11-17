# Actor gauge resets and scale/tier lifecycle evidence

## Result and boundary

The fixed reader represents **all 23 + 23 + 66 = 112 instructions** in actual
`8003d3e8`, `8003d444` and `8005bab8`, with no omitted or unknown instructions,
from both already existing authenticated local ProgramDB snapshots. The two
snapshots agree on every instruction field, constant, digest and physical
trace. This is archived source evidence, **not** original-DOL byte identity,
live FPSCR/r2 state, runtime ownership, gameplay parity or a complete actor tick.

Only these three fixed spans and four named constants are newly read. The
existing shared authentication/mapping readers and their allowlists are
unchanged. Output is derived operands, values, hashes and physical traces, not
raw executable ranges. The CLI accepts a snapshot path only, not arbitrary
addresses, sizes, raw-output or execution options. No archived code is executed.

Source C cross-references are `ghidra-export/chunk_0004.c:6864-6892` and
`chunk_0007.c:3672-3713`. Exact extents follow link-map entries
`research/symbols/GG4E-CSM-20220412.map:450-451,719`, agreeing with the next
C function markers at `8003d444`, `8003d4a0` and `8005bbc0`. C alone is not the
arithmetic-order proof: its apparent product grouping differs from the
instructions below.

## Authentication and fixed extents

Inputs stay under the existing local directory
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`.

| Snapshot | Whole-file SHA-256 |
| --- | --- |
| db.3.gbf | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| db.4.gbf | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Unchanged `read_archived_constants.inspect` authenticates the complete
snapshot, exact schemas, `boot.dol` metadata, big-endian Gekko/Broadway language,
address map, empty File Bytes table, full data5 digest and existing controls
before new reads. Unchanged `read_archived_command_evidence.mappings` checks
exact text1/data3/data5 block/subblock identities and all-block overlap.

- Executable import-metadata SHA-256:
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  This is metadata, not independent proof of unchanged executable bytes.
- File Bytes table: version 0, root -1, count 0.
- GBF block size 16384, master root 1, image offset `80000000`.
- Text1 start `800055e0`, length 2796416, root 21.
- Data5 start `80436a20`, length 27360, root 263; full digest
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

| Fixed span | Width / instructions | SHA-256 |
| --- | --- | --- |
| `[8003d3e8,8003d444)` | 92 / 23 | `029c02b480e2afb11381d7ff2f595f03c46dabff6c4a410a249d2b4eb53ef1af` |
| `[8003d444,8003d4a0)` | 92 / 23 | `38e165f8b714575694c3f29ce4efea45dd1b1f16c3b10e3900e39fe2fb2b8902` |
| `[8005bab8,8005bbc0)` | 264 / 66 | `d857580767ae7b19893084b31d12b3a0c9a606a7891ae5e4f3cbaa7672c0ee46` |

Physical traces are identical in both snapshots. Offsets below are decimal;
all text traces use root21 and obfuscated ProgramDB storage.

| Function | Data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| 8003d3e8 | 35 | 228872 | 15958 | 605788 | 92 |
| 8003d444 | 35 | 228964 | 16050 | 605880 | 92 |
| 8005bab8 | 43 | 353496 | 9558 | 730460 | 264 |

Each complete function hash is checked before instruction decoding. Constants
are exact data5 reads, checked bit-for-bit:

| Address | Bits | Value | r2 displacement | Chain/data offset | Physical offset |
| --- | --- | --- | --- | --- | --- |
| 80436f88 | `4330000080000000` | f64, 2^52 + 2^31 | -31384 | 1384 | 4343150 |
| 80436f7c | `3f000000` | f32, 0.5 | -31396 | 1372 | 4343138 |
| 80436f78 | `3f800000` | f32, 1 | -31400 | 1368 | 4343134 |
| 80437420 | `3d4ccccd` | f32, 0.05000000074505806 | -30208 | 2560 | 4344326 |

Constant traces use root263/data buffer264 and lengths8/4/4/4 respectively.
SDA2 displacements use the previously recorded `r2=8043ea20` basis
(`docs/static-recompilation-spike.md:178`), not a new live-register capture.

## Gauge reset arithmetic and storage

The two leaf functions are instruction-identical except for their signed base
and short destination offsets: `6c4 -> 6c6` and `7d6 -> 7dc`. PCs and offsets
in this section are hexadecimal.

At `3d3f4` the first helper loads signed short base6c4 into **retained r5**,
then `3d3f8` loads actual modelScaleB4 once. It does not reload either source.
The corresponding second-helper PCs are these PCs plus5c.

The decisive sequence is:

1. `3d404`: `fsubs f0,f1,f0` computes **single-rounded B4 minus 1**.
2. `3d418`: `fmuls f0,f1,f0` computes **single-rounded 0.5 times that delta**.
3. The signed base conversion uses `lha`, `xoris8000`, stack high word4330,
   `lfd` and the authenticated bias. `3d41c` is **fsubs**, not double fsub:
   constructed double minus the bias yields the exact signed16 base as f32.
4. `3d420`: `fmuls f0,f1,f0` computes **single-rounded base times the factor**.
5. `3d424`: `fctiwz` converts the product toward zero; `stfd` and `lwz` retrieve
   its integer low word. `3d430` sign-extends that word's **low16 bits**.
6. `3d434` adds retained signed base r5 to that signed16 correction, then
   `3d438` performs a **short store** to6c6. The other helper stores7dc at3d494.

There are two separate `fmuls` instructions and no fused multiply-add, double
product, division, or saturating/clamping operation. The supported finite
RN00/NI0 interpretation is conceptually
`i16(base + i16(trunc(f32(base * f32(0.5 * f32(scale - 1))))))`.
The source's base conversion appears between the two products, as listed.
Do not regroup the product as `f32(f32(base * 0.5) * delta)` or retain extra
precision between single instructions. The final two short-width operations
wrap; they are not host saturation.

This reader proves instruction forms and order, not live rounding mode or
exception state. A bounded runtime should explicitly delimit supported finite
single operands/results and valid signed32 `fctiwz` conversions. For a finite
binary32 product, `[-2147483648,2147483648)` is the valid signed32 conversion
interval. These snapshots do not justify substituting host behavior for NaN,
infinity, out-of-range conversion or unknown FPSCR behavior.

The existing authenticated status reader establishes the conditional calls
`55b70 -> 3d3e8` after688 expiry and `55ba8 -> 3d444` after7d8 expiry. Those
caller instructions are covered by that earlier reader, not added to this
one. Source ownership must retain actual BorgRuntime downGaugeBase/downGauge,
actual modelScaleB4, and explicit owners for7d6/7dc; these archive reads alone
do not establish runtime wiring.

## 5bab8 tier prefix and scale ordering

### Tier timer before scale

- `5bacc` signed-loads750 into r4. Only signed `>0` enters the decrement.
- `5bad8` subtracts1; `5badc` executes `extsh.` into r0 for its signed condition;
  `5bae0` stores r4's low16 to750 **before** the expiry branch.
- If the decremented signed value is still positive, branch to5bb04.
  Otherwise `5bae8/5baec` load and sign-extend byte74e, and `5baf0` negates it
  into the second call argument. `5baf4` calls actual `8006817c`.
- **Only after that call returns**, `5bafc` clears short750 and `5bb00` clears
  byte74e. Then scale processing begins.

No6817c body is included in this fixed reader. Existing source C
`chunk_0008.c:4410-4437` shows both a global gate and a table refresh around the
tier operation, so a convenient host clamp is not evidence of that callee.
A bounded refusal at the reached call must retain the already-decremented750,
leave74e uncleared and not perform the later scale stage. Use the existing
actual ActorParamTier object for750/74e/74a rather than a copied sidecar.

### Scale gates and direction

`5bb04` loads **targetB8 before currentB4** (`5bb08`). `5bb0c` is `fcmpu`:
only equality returns immediately. Next, byte7c9 is loaded/sign-extended with
a record bit; nonzero returns. Neither early-return path writes scale copies
or calls the gauge reset.

`5bb20` compares the retained target and current using `fcmpo`.
Ordered target>current takes the increasing path. The not-GT branch selects
the decreasing path, including the unordered comparison case; do not mistake
it for an ordered target<=current instruction predicate. A finite-only runtime
can explicitly refuse NaNs without claiming the archive excluded them.

### Increasing and decreasing paths

- Increasing (`5bb28..5bb50`): load step, `fadds` retained current+step, storeB4,
  **reloadB8 then reloadB4**, compare target/new current. `cror EQ,LT,EQ` makes
  the clamp condition ordered target<=new current. If true, store the newly
  loaded target toB4 **before** calling3d3e8 at5bb50.
- Decreasing (`5bb58..5bb80`): load step, `fsubs` retained current-step, storeB4,
  **reloadB8 then reloadB4**, compare target/new current. `cror EQ,GT,EQ` makes
  the clamp condition ordered target>=new current. If true, store that loaded
  target toB4 **before** calling3d3e8 at5bb80.
- Both compare/clamp paths reject unordered results from the clamp. A reached
  reset failure occurs after the interpolation store and target clamp, not
  before those stores. Do not run later copies after a reset refusal.

After either interpolation path, `5bb84..5bba8` performs five distinct
`lfs B4; stfs destination` pairs to **58,5c,60,c0,c4, in that order**. Every
pair freshly loadsB4. Although Ghidra C shows undefined4 copies, the actual
instructions are floating loads/stores, not integer word copies. Existing
world-binding scale58 and explicit actual c0/c4 owners are required; absence
of collisionScaleC0 does not authorize fallback to modelScaleB4.

The complete call set in this helper is precisely
`5baf4 -> 6817c`, `5bb50 -> 3d3e8`, `5bb80 -> 3d3e8`. It does not call3d444.
This narrow helper does not close the subsequent calls or whole `80059068`,
ordinary `80055568`, enclosing traversal or production host routing.

## Reproduction and controls

```bash
python3 -m unittest discover -s research/tools/matching-decomp -p test_archived_gauge_scale_evidence.py
python3 research/tools/matching-decomp/read_archived_gauge_scale_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
```

The focused suite passes **16 tests**, with both snapshots present. It checks
all112 decoded positions, digests, counts and physical traces; all constants;
representative strong operand/order anchors for reset arithmetic, signed
conversion and wrapping, tier expiry, scale gates, compare conditions,
store/reload/call order and all five final copies. Synthetic controls cover
whole-snapshot authentication before parsing, mapping/root/offset/overlap
mutations before new reads, fixed-width/hash failures before decoding,
reserved/unsupported forms, unknown instructions, fixed constant bounds/bits,
and forbidden CLI options. One-bit changes at each of112 instruction positions
and each constant byte fail before decoding/acceptance. Archive-specific tests
skip explicitly if both private snapshots are not present; synthetic controls
remain runnable. No original executable fixture is stored.

No rig/process inspection, new input/capture/assets, source transfer/upload,
installation, publication/push, denied-operation retry, or commit was used.
