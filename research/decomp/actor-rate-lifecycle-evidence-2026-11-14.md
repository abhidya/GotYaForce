# Actor-rate lifecycle: fixed archived evidence

## Result and boundary

The complete `8005a378..8005a580` helper is authenticated from both existing
archived ProgramDB snapshots: **520 bytes, 130 instructions, none omitted**.
The function, three exact float32 constants and four individually selected
float32 table cells agree in both archives. The final multiplication order
**differs from the apparent grouping in the C export**: multiply `1dcc` by
`768` first, then multiply `1dd0` by that single-precision result.

This is offline archived evidence, not execution, original-DOL identity, live
actor ownership, production integration, retail parity or playable-game proof.
The reader does not follow the mode-two actor pointer. Only table indices
**1 and 2** are authenticated for each table; zero skips its source read, and
all other nonzero signed-byte indices remain unsupported. No table extent is
inferred from nearby labels or from an older prose description.

Artifacts:

- [Fixed reader](../tools/matching-decomp/read_archived_actor_rate_evidence.py)
- [Complete operands and fail-closed tests](../tools/matching-decomp/test_archived_actor_rate_evidence.py)
- [Prior readiness evidence](actor-ready-lifecycle-evidence-2026-11-14.md)

No shared allowlist or reader was edited. The CLI accepts one existing snapshot
path, with no address, index, width, raw-output, execution or pointer-following
options. No original instruction execution, new dependencies, installations,
network operations, proprietary binary output or retired port driver is used.

## Extent and authentication

`research/decomp/ghidra-export/chunk_0007.c:2816-2920` supplies the selected
entry and next-entry boundary. The final decoded instruction is `blr` at
`8005a57c`. Neither `8005a378` nor `8005a580` is present as a function entry in
`research/symbols/GG4E-CSM-20220412.map`; this is **not a symbol-size claim**.

The unchanged `read_archived_constants.inspect` verifies the actual full
snapshot SHA-256, exact schemas, executable metadata, Gekko/Broadway big-endian
language, address maps, empty File Bytes, full data5 hash and its existing
controls **before any new fixed read**. The supplied digest alone is not
trusted. Unchanged `read_archived_command_evidence.mappings` then verifies
text1/data3/data5 identities, block/subblock parameters and all-block overlap;
the reader separately checks the exact data5 tuple. Fixed readers reject
wrong roots, noninteger parameters, nonunique allowlist matches, unaligned or
out-of-block ranges, wrong widths and changed selected bits/digests before
decoding. No unsupported instruction is silently omitted.

Existing local snapshots under
`GotchaForce.rep.before_force_create/idata/00/~00000000.db/`:

- `db.3.gbf`: `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`.
- `db.4.gbf`: `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`.

Import executable SHA-256 metadata is
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`,
not an independently acquired original executable. File Bytes is version 0,
root -1, count 0. Block size is 16384; master root is 1; image offset is
`80000000`. Relevant mappings, each with subblock type 2 and starting/source
offsets zero:

| Block | Start | Length | Block/subblock key | Chain root |
| --- | --- | --- | --- | --- |
| MAIN_.text1 | `800055e0` | 2796416 | 1 | 21 |
| MAIN_.data3 | `802bae60` | 1000128 (`0xf42c0`) | 5 | 199 |
| MAIN_.data5 | `80436a20` | 27360 | 7 | 263 |

Full data5 SHA-256 remains
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.
The full data3 payload is not separately dumped or hashed; snapshot identity,
exact data3 mapping and four exact fixed-cell bit checks establish this narrow
selection. The helper span SHA-256 is
`b6a3dfe9d8bf1b34fb4d470444385f1bbdafe4ba0596786d67699ca9e92ecd2f`.

## Constants and bounded table provenance

Previously recorded SDA2 basis `r2=8043ea20` maps the actual source
displacements to these three constants. This is not a live r2 capture.

| Address | r2 displacement | Bits | Exact float32 value | Source instruction |
| --- | --- | --- | --- | --- |
| `804373c8` | -30296 | `3f800000` | 1 | `5a384`, `5a40c` |
| `804373d8` | -30280 | `3fc00000` | 1.5 | `5a420` |
| `804373dc` | -30276 | `3cf5c28f` | 0.029999999329447746 | `5a528` |

The source constructs `802dd590` (haste) or `802dd580` (slow), sign-extends
the retained byte index, shifts it left two, adds it, then executes `lfs -4`.
Thus the effective addresses are `802dd58c + 4*s8(index)` and
`802dd57c + 4*s8(index)`, respectively. A zero index branches around the
entire multiplication. There is **no source bounds check** that limits an
index to 1 or 2; unsupported values cannot be clamped, defaulted or read by
this reader. The table labels at index zero are not read.

Only these individual cells are selected:

| C base | Index | Effective address | Bits | Exact float32 value |
| --- | --- | --- | --- | --- |
| `802dd57c` | 1 | `802dd580` | `3f333333` | 0.699999988079071 |
| `802dd57c` | 2 | `802dd584` | `3ecccccd` | 0.4000000059604645 |
| `802dd58c` | 1 | `802dd590` | `3fa00000` | 1.25 |
| `802dd58c` | 2 | `802dd594` | `3fc00000` | 1.5 |

Selection rationale is bounded positive cases, not inferred extents. Existing
[status-effect research](status-effects-decode-2026-07-04.md) identifies aura
and hit paths; the actual C writer references are in **chunk_0003.c**, not
chunk_0004.c:

- Line 7683 sets contact-haste byte `70d=1`.
- Line 8105 sets hit-slow byte `70e=2`.
- Line 8143 sets hit-haste byte `70f=2`.
- Line 7676 assigns contact-slow `70c` from record byte +5. This is variable,
  not a proven bound. Index one is a bounded selected input case; authenticating
  that constant does not authenticate the writer's record or its runtime value.

Those C locations justify selecting relevant cells, but their writer function
instructions are **not** added to this reader or claimed authenticated here.
Older research mentions index-three values and index-zero labels; neither is
imported as evidence. All signed indices `-128..-1` and `3..127` remain
unsupported even when they would land near an authenticated cell from the
other table. The base/index pair, not address coincidence, is allowlisted.

### Physical traces

Both snapshots produce identical physical traces. All entries are obfuscated
storage. Offsets and lengths below are decimal.

| Selection | Root/data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| helper `8005a378` | 21 / 43 | 347544 | 3606 | 724508 | 520 |
| constant `804373c8` | 263 / 264 | 2472 | 2472 | 4344238 | 4 |
| constant `804373d8` | 263 / 264 | 2488 | 2488 | 4344254 | 4 |
| constant `804373dc` | 263 / 264 | 2492 | 2492 | 4344258 | 4 |
| slow index 1 | 199 / 208 | 141088 | 10064 | 3434326 | 4 |
| slow index 2 | 199 / 208 | 141092 | 10068 | 3434330 | 4 |
| haste index 1 | 199 / 208 | 141104 | 10080 | 3434342 | 4 |
| haste index 2 | 199 / 208 | 141108 | 10084 | 3434346 | 4 |

## Exact source sequence and C differences

All actor offsets below are hexadecimal. The helper has no calls, stack frame,
LR save or external helper boundary. The pointer path is still an ownership
boundary: decoding its loads does not authorize arbitrary pointer reads.

### Early paths

1. `5a378` reads byte `4a1`, then `extsb.` tests it. If nonzero, only then
   load constant one (`5a384`), store `1dc8`, `5f4`, `768` in that order,
   and return at `5a394`. No `4a0` or timer read occurs. The C's apparent
   leading constant assignment is not an eager source read.
2. Otherwise `5a398` reads byte `4a0`; the comparison with two uses its
   zero-extended `lbz` result. If it equals two, load pointer identity `4a4`
   once, then interleave `lfs`/`stfs` for pointer `768` to actor `768`, pointer
   `5f4` to actor `5f4`, pointer `1dc8` to actor `1dc8`, and return at `5a3c0`.
   These are floating loads/stores, not the integer copies shown as
   `undefined4` in C. An aliasing pointer still requires ordered accesses.

### Timers and retained index bytes

At `5a3c4`, read `710` as signed16. If zero, skip its decrement and flag
write. Otherwise decrement the register, sign-extend its **low16** into CR0,
store the low16 result at `710` (`5a3d8`), and clear byte `70e` only if the
wrapped signed result is nonpositive (`5a3e4`). Repeat the same pattern for
signed16 `712`, clearing byte `70f` at `5a408` if required. The predicate
uses `extsh` before the store, not a reload. In particular, `-32768 - 1`
wraps to `32767` and does not clear its flag.

Only after both timer paths, load one at `5a40c` and store `768` at `5a410`.
Read byte `6fc` at `5a414`; if nonzero after sign extension, load 1.5 and
replace `768` at `5a424`.

Then process signed-byte `70d`, followed by `70f`. Each nonzero case:

- Reads the index byte once, retains its value, and sign-extends that retained
  value again for address arithmetic; there is no second actor-index read.
- Loads current actor `768` **before** reading the selected table cell.
- Loads the exact table cell, executes `fmuls(current768, cell)`, then stores
  the single-precision result at `768` before the next source index is read.

Haste cells are loaded at `5a44c`/`5a47c`; results are stored at
`5a454`/`5a484`. A refusal at a later unsupported cell must preserve earlier
source writes and must not pretend that later fields were reached.

### Lazy slow gates

Read u32 `5e0` at `5a488` and test bit `0x01000000`. If set, skip all slow
work. Only when clear, read **fresh** byte `6fc` at `5a494`; nonzero skips
slow work. Only if that is zero, read **fresh** byte `4a0` at `5a4a0`;
nonzero skips slow work. Earlier reads of either byte are not substitutes.

Only after all three gates pass, process signed-byte `70c`, followed by
`70e`, with the same retained-index, current-rate-before-cell,
`fmuls`-then-store pattern. Slow cell loads are at `5a4d0`/`5a500`, stores
at `5a4d8`/`5a508`. A later failure cannot erase the completed haste writes,
timer updates or base-rate write. A reader must not infer or fetch an
unsupported cell because the effective address overlaps another selected
base's cell.

### Unsigned freeze byte and ordered final multiplication

Read `71c` using `lbz` at `5a50c`, then compare it **unsigned** with zero.
If nonzero, decrement and test the low8 with `rlwinm.`, store that low8 at
`71c` (`5a520`), then branch on the retained condition. If still nonzero,
load constant `3cf5c28f`, store `5f4`, then `1dc8`, and return (`5a534`).
Do not load `1dcc`/`1dd0` on that branch.

If `71c` was zero or just became zero, two duplicate tails execute the same
ordered operations (starting `5a538` or `5a55c`):

1. Load `768`; store it to `5f4`.
2. Load `1dcc` into f1, **reload** `768` into f0, then load `1dd0` into f2.
3. `fmuls f0,f1,f0`: round single-precision `1dcc * reloaded768`.
4. `fmuls f0,f2,f0`: round single-precision `1dd0 * previousResult`.
5. Store `1dc8`; return.

The C export writes `1dd0 * 1dcc * 768`, which suggests left-to-right
`(1dd0 * 1dcc) * 768`. The archived source order is instead
`1dd0 * (1dcc * 768)`, with a single-precision round at each multiply.
This can change even finite normal values. The C also hides the fresh `768`
read and represents `5f4` as an integer copy; neither simplification may
replace the actual instruction stream.

The reader establishes operands and constant bits only. It does not establish
live FPSCR rounding/NI settings, floating exceptions, NaN payload behavior,
denormal handling, owner field availability, pointer validity or any runtime
calculation result. A bounded implementation must state its supported float
domain and stop before unsupported arithmetic or reads.

## Reproduction and focused verification

From repository root, with existing stdlib Python only:

```sh
python research/tools/matching-decomp/read_archived_actor_rate_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
python research/tools/matching-decomp/read_archived_actor_rate_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
PYTHONPATH=research/tools/matching-decomp python -m unittest \
  test_archived_actor_rate_evidence -v
```

All **18 focused tests pass**, with both local archive test inputs present and
**no skips**. Tests compare every explicit operand in order, source and return
boundaries, lazy gates, final multiplication association, all seven exact
float32 values, base/index address construction, authentication and map failure
ordering, forbidden CLI options, full signed-index refusal, and mutations of
every selected instruction and every selected data byte in both snapshots.
Synthetic malformed encodings and fixtures test rejected reserved fields;
archived payloads remain only in existing ignored inputs.

A combined run with constants, command, actor-status, control-effect,
cue-reset and ready-lifecycle evidence suites passes **106 tests**, no skips.
Whitespace checks pass for all three new files. These are evidence-reader
checks, not contributor/build, runtime-integration or retail-parity claims.

## Appendix: complete derived operands

All 130 instructions follow in source order. Numbers other than addresses are
decimal. No raw instruction words or executable byte ranges are included.

```text
8005a378 lbz rD=0 rA=3 displacement=1185
8005a37c extsb rS=0 rA=0 Rc=1
8005a380 bc BO=12 BI=2 LK=0 target=8005a398 AA=0
8005a384 lfs fD=0 rA=2 displacement=-30296
8005a388 stfs rA=3 displacement=7624 fS=0
8005a38c stfs rA=3 displacement=1524 fS=0
8005a390 stfs rA=3 displacement=1896 fS=0
8005a394 blr
8005a398 lbz rD=0 rA=3 displacement=1184
8005a39c cmpi BF=0 L=0 rA=0 immediate=2
8005a3a0 bc BO=4 BI=2 LK=0 target=8005a3c4 AA=0
8005a3a4 lwz rD=4 rA=3 displacement=1188
8005a3a8 lfs fD=0 rA=4 displacement=1896
8005a3ac stfs rA=3 displacement=1896 fS=0
8005a3b0 lfs fD=0 rA=4 displacement=1524
8005a3b4 stfs rA=3 displacement=1524 fS=0
8005a3b8 lfs fD=0 rA=4 displacement=7624
8005a3bc stfs rA=3 displacement=7624 fS=0
8005a3c0 blr
8005a3c4 lha rD=4 rA=3 displacement=1808
8005a3c8 cmpi BF=0 L=0 rA=4 immediate=0
8005a3cc bc BO=12 BI=2 LK=0 target=8005a3e8 AA=0
8005a3d0 addi rD=4 rA=4 immediate=-1
8005a3d4 extsh rS=4 rA=0 Rc=1
8005a3d8 sth rA=3 displacement=1808 rS=4
8005a3dc bc BO=12 BI=1 LK=0 target=8005a3e8 AA=0
8005a3e0 addi rD=0 rA=0 immediate=0
8005a3e4 stb rS=0 rA=3 displacement=1806
8005a3e8 lha rD=4 rA=3 displacement=1810
8005a3ec cmpi BF=0 L=0 rA=4 immediate=0
8005a3f0 bc BO=12 BI=2 LK=0 target=8005a40c AA=0
8005a3f4 addi rD=4 rA=4 immediate=-1
8005a3f8 extsh rS=4 rA=0 Rc=1
8005a3fc sth rA=3 displacement=1810 rS=4
8005a400 bc BO=12 BI=1 LK=0 target=8005a40c AA=0
8005a404 addi rD=0 rA=0 immediate=0
8005a408 stb rS=0 rA=3 displacement=1807
8005a40c lfs fD=0 rA=2 displacement=-30296
8005a410 stfs rA=3 displacement=1896 fS=0
8005a414 lbz rD=0 rA=3 displacement=1788
8005a418 extsb rS=0 rA=0 Rc=1
8005a41c bc BO=12 BI=2 LK=0 target=8005a428 AA=0
8005a420 lfs fD=0 rA=2 displacement=-30280
8005a424 stfs rA=3 displacement=1896 fS=0
8005a428 lbz rD=4 rA=3 displacement=1805
8005a42c extsb rS=4 rA=0 Rc=1
8005a430 bc BO=12 BI=2 LK=0 target=8005a458 AA=0
8005a434 extsb rS=4 rA=0 Rc=0
8005a438 addis rD=4 rA=0 immediate=-32722
8005a43c addi rD=4 rA=4 immediate=-10864
8005a440 lfs fD=1 rA=3 displacement=1896
8005a444 rlwinm rS=0 rA=0 SH=2 MB=0 ME=29 Rc=0
8005a448 add rD=4 rA=4 rB=0 Rc=0
8005a44c lfs fD=0 rA=4 displacement=-4
8005a450 fmuls fD=0 fA=1 fC=0
8005a454 stfs rA=3 displacement=1896 fS=0
8005a458 lbz rD=4 rA=3 displacement=1807
8005a45c extsb rS=4 rA=0 Rc=1
8005a460 bc BO=12 BI=2 LK=0 target=8005a488 AA=0
8005a464 extsb rS=4 rA=0 Rc=0
8005a468 addis rD=4 rA=0 immediate=-32722
8005a46c addi rD=4 rA=4 immediate=-10864
8005a470 lfs fD=1 rA=3 displacement=1896
8005a474 rlwinm rS=0 rA=0 SH=2 MB=0 ME=29 Rc=0
8005a478 add rD=4 rA=4 rB=0 Rc=0
8005a47c lfs fD=0 rA=4 displacement=-4
8005a480 fmuls fD=0 fA=1 fC=0
8005a484 stfs rA=3 displacement=1896 fS=0
8005a488 lwz rD=0 rA=3 displacement=1504
8005a48c rlwinm rS=0 rA=0 SH=0 MB=7 ME=7 Rc=1
8005a490 bc BO=4 BI=2 LK=0 target=8005a50c AA=0
8005a494 lbz rD=0 rA=3 displacement=1788
8005a498 extsb rS=0 rA=0 Rc=1
8005a49c bc BO=4 BI=2 LK=0 target=8005a50c AA=0
8005a4a0 lbz rD=0 rA=3 displacement=1184
8005a4a4 extsb rS=0 rA=0 Rc=1
8005a4a8 bc BO=4 BI=2 LK=0 target=8005a50c AA=0
8005a4ac lbz rD=4 rA=3 displacement=1804
8005a4b0 extsb rS=4 rA=0 Rc=1
8005a4b4 bc BO=12 BI=2 LK=0 target=8005a4dc AA=0
8005a4b8 extsb rS=4 rA=0 Rc=0
8005a4bc addis rD=4 rA=0 immediate=-32722
8005a4c0 addi rD=4 rA=4 immediate=-10880
8005a4c4 lfs fD=1 rA=3 displacement=1896
8005a4c8 rlwinm rS=0 rA=0 SH=2 MB=0 ME=29 Rc=0
8005a4cc add rD=4 rA=4 rB=0 Rc=0
8005a4d0 lfs fD=0 rA=4 displacement=-4
8005a4d4 fmuls fD=0 fA=1 fC=0
8005a4d8 stfs rA=3 displacement=1896 fS=0
8005a4dc lbz rD=4 rA=3 displacement=1806
8005a4e0 extsb rS=4 rA=0 Rc=1
8005a4e4 bc BO=12 BI=2 LK=0 target=8005a50c AA=0
8005a4e8 extsb rS=4 rA=0 Rc=0
8005a4ec addis rD=4 rA=0 immediate=-32722
8005a4f0 addi rD=4 rA=4 immediate=-10880
8005a4f4 lfs fD=1 rA=3 displacement=1896
8005a4f8 rlwinm rS=0 rA=0 SH=2 MB=0 ME=29 Rc=0
8005a4fc add rD=4 rA=4 rB=0 Rc=0
8005a500 lfs fD=0 rA=4 displacement=-4
8005a504 fmuls fD=0 fA=1 fC=0
8005a508 stfs rA=3 displacement=1896 fS=0
8005a50c lbz rD=4 rA=3 displacement=1820
8005a510 cmpli BF=0 L=0 rA=4 immediate=0
8005a514 bc BO=12 BI=2 LK=0 target=8005a55c AA=0
8005a518 addi rD=4 rA=4 immediate=-1
8005a51c rlwinm rS=4 rA=0 SH=0 MB=24 ME=31 Rc=1
8005a520 stb rS=4 rA=3 displacement=1820
8005a524 bc BO=12 BI=2 LK=0 target=8005a538 AA=0
8005a528 lfs fD=0 rA=2 displacement=-30276
8005a52c stfs rA=3 displacement=1524 fS=0
8005a530 stfs rA=3 displacement=7624 fS=0
8005a534 blr
8005a538 lfs fD=0 rA=3 displacement=1896
8005a53c stfs rA=3 displacement=1524 fS=0
8005a540 lfs fD=1 rA=3 displacement=7628
8005a544 lfs fD=0 rA=3 displacement=1896
8005a548 lfs fD=2 rA=3 displacement=7632
8005a54c fmuls fD=0 fA=1 fC=0
8005a550 fmuls fD=0 fA=2 fC=0
8005a554 stfs rA=3 displacement=7624 fS=0
8005a558 blr
8005a55c lfs fD=0 rA=3 displacement=1896
8005a560 stfs rA=3 displacement=1524 fS=0
8005a564 lfs fD=1 rA=3 displacement=7628
8005a568 lfs fD=0 rA=3 displacement=1896
8005a56c lfs fD=2 rA=3 displacement=7632
8005a570 fmuls fD=0 fA=1 fC=0
8005a574 fmuls fD=0 fA=2 fC=0
8005a578 stfs rA=3 displacement=7624 fS=0
8005a57c blr
```
