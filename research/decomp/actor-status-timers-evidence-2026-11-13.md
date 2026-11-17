# Actor status/timer and ammo evidence: 8005568c / 8006dcc0

## Result and boundary

The fixed reader represents **all 464 status instructions and all 84 ammo
instructions**, with no omitted or unknown instructions, from both already
existing authenticated local ProgramDB snapshots. It reads only the two fixed
function spans and four named constants after the existing authentication and
mapping guards. No shared reader allowlist was changed. Output consists of
operand fields, constant values, digests and physical traces, not executable
ranges. The CLI accepts only the snapshot path, not addresses, widths, raw
output or execution options.

This establishes archived source evidence, **not** unchanged original-DOL
bytes, live FPSCR state, retail actor values, runtime ownership, gameplay
parity, production activation or a whole ordinary actor tick. The bounded
runtime may legitimately refuse paths whose actual callees or arithmetic are
not implemented. Complete decoding is not a claim that every decoded path is
implemented in that runtime.

The existing C export places `8005568c` immediately after `80055dcc` and before
`80059068` in ordinary `80055568` (`ghidra-export/chunk_0006.c:7786-7789`).
Those surrounding calls are export references, not additional spans covered
by this reader. Bodies are at `chunk_0006.c:7812-8085` and
`chunk_0009.c:2909-2973`. Symbol extents are in
`research/symbols/GG4E-CSM-20220412.map:688,851`.

## Authentication and fixed extents

Inputs remain local under
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`.

| Snapshot | Whole-file SHA-256 |
| --- | --- |
| db.3.gbf | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| db.4.gbf | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Unchanged `read_archived_constants.inspect` authenticates each complete
snapshot, exact schemas, `boot.dol` metadata, big-endian Gekko/Broadway
language, address map, empty File Bytes table, complete data5 digest and
existing controls before the new reads. Unchanged
`read_archived_command_evidence.mappings` then checks exact text1/data3/data5
block and subblock identities and rejects all-block overlap.

- Executable import-metadata SHA-256:
  `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
  This metadata is not independent proof of unchanged executable bytes.
- File Bytes table: version 0, root -1, count 0.
- GBF block size 16384, master root 1, image offset `80000000`.
- Text1 starts at `800055e0`, length 2796416, root 21.
- Data5 starts at `80436a20`, length 27360, root 263; full digest
  `989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

| Fixed span | Width / instructions | SHA-256 |
| --- | --- | --- |
| `[8005568c,80055dcc)` | 1856 / 464 | `0f964164be0f7581e45a26f8acd1113b414d13ecdbefeb94be72acde53c156ac` |
| `[8006dcc0,8006de10)` | 336 / 84 | `2d58ff4852a700a526d906055a7d70dcee182783f6f0a3b0d83d3be2fd20de8f` |

Physical traces agree between snapshots (all offsets below are decimal):

| Function | Root / data buffer | Chain offset | Data offset | Physical offset | Length |
| --- | --- | --- | --- | --- | --- |
| 8005568c | 21 / 42 | 327852 | 292 | 704810 | 1856 |
| 8006dcc0 | 21 / 48 | 427744 | 1916 | 804738 | 336 |

All spans are obfuscated ProgramDB storage, decoded by the existing reader.
Each complete function hash is checked before instruction decoding. Constants
are read from the exact authenticated data5 mapping and checked bit-for-bit:

| Address | Bits | Value | Chain/data offset | Physical offset |
| --- | --- | --- | --- | --- |
| 80437250 | `00000000` | positive zero, f32 | 2096 | 4343862 |
| 80437658 | `00000000` | positive zero, f32 | 3128 | 4344894 |
| 804376c8 | `41200000` | 10, f32 | 3240 | 4345006 |
| 804376a0 | `4330000080000000` | 2^52 + 2^31, f64 | 3200 | 4344966 |

Constant traces use root 263, data buffer 264, lengths 4/4/4/8 respectively.

## Ordered source facts

All PCs and field offsets in this section are hexadecimal.

1. **694 timer:** `556a4..556ac` gates on `(control5e0 & 3)==0`.
   `556b0` loads 694 once into f2, compares it to positive zero, then loads
   1dc8 and subtracts from that retained f2. `556c8` stores and `556cc`
   reloads 694. `fcmpo` plus `cror EQ,LT,EQ` gives ordered `<=0` expiry;
   expiry writes positive zero, reloads/masks/stores control and clears73f.
2. **Rate timers:** 690,698,69c,6a0,6a4 occur in that order at
   `556f4,55720,5574c,55778,557a4`. Each positive timer separately loads768,
   subtracts, stores, reloads and clamps only for ordered **strictly <0**.
   These are not five unconditional saturating assignments.
3. **Integer widths:** 6fc arms7de or its nonzero byte decrements. 6b8 is a
   signed `lha`; 4a1 and unsigned71c control its reset/decrement. Bytes
   656,593,594,596 use nonzero tests and low-byte stores. Poison6ba has
   lifecycle18/19 gates, `extsh` before its modulo30 arithmetic and `sth`
   storage, followed by a signed reload and `<=0` clear of8c4 bit2. These
   instructions support wrapping byte/short semantics, not host saturation.
4. **Six counters:** `55908..559f4` has three unrolled entries inside a
   two-count CTR loop. Each selected708 bit separately reloads709, may
   store2, then reloads/decrements a nonzero A8..AD counter. Unselected708
   bits skip that counter entirely. `559f8..55a14` freshly loads709,708,707
   and uses `and`/`andc.` before the conditional real `800f0104` call.
5. **736 refill:** signed661 classes2/3/6 use control80; other classes use
   byte87. Nonzero signed73a decrements through `sth`. Otherwise each branch
   loads4ac, signed736 and signed parameter+8, adds and **stores short736
   before reloading4ac and signed736**, then compares with signed parameter+4
   and caps if greater. Only the non-special branch also clears747 here.
6. **Expiry effects:** control01000000 gates684,688,7d8,68c in that order.
   Each reached positive timer freshly loads1dcc and stores/reloads its
   subtraction before ordered `<=0` expiry. Zeroing precedes the effect:
   684 copies signed6be to6c2; 688 calls8003d3e8; 7d8 calls8003d444; 68c
   clears short6c8 then byte6ca. Timer720 is outside that control gate and
   clears short272 on expiry.
7. **Child list:** eight pointer slots start at440. Child lifecycle18 is
   byte-loaded then sign-extended and compared with2. Removal shifts later
   pointers, zeroes the final slot and decrements byte485. The outer index
   still advances after removal, rather than repeatedly rechecking that slot.
8. **Unconditional ammo:** actual `8006dcc0` is called at `55d08` after the
   child loop. A static branch-graph overapproximation confirms every path
   from5568c entry to its return passes this call. Removing any other call
   leaves a returning path. The exact other calls are `55a28->800f0104`,
   `55b70->8003d3e8`, `55ba8->8003d444`, `55d58->8005c290`.
9. **Final effects:** control80000000 or zero7d4 skips the reaction/refill
   section. Control02000000 chooses the real reaction call and later6b6
   restoration; otherwise signed4ac+4 is stored to738 then736 and747 cleared.
   Byte5da==1 and ordered8c8>=0 adds freshly loaded1dcc via `fadds/stfs`.
   Other5da values store positive zero without reading old8c8.

## Ammo ordering and mode distinction

`6dcc4` loads byte6fc, **then** `6dcc8` loads768 into f3, before testing the
retained byte and optionally multiplying the retained rate by10. That rate
remains in f3 for all three slots. CTR=3 and pointer strides8 establish source
slots0/1/2. Each iteration reloads597 before debt or descriptor loads; a set
pause bit skips both. Nonpositive debt skips the mode load. Mode is signed.

Mode0 subtracts retained f3 from positive debt, stores/reloads debt, then on
ordered `<=0` performs: signed max load, current short store, **second max
load**, mirror short store, positive-zero debt store (`6dd5c..6dd6c`).

Mode1 stores/reloads its subtraction too, but its expiry path refills current
and mirror with separate max loads **without** clamping negative debt. Its
positive-remainder path loads signed parameter, constructs the signed integer
conversion with high word4330, `xoris8000` and the authenticated f64 bias,
loads signed max and signed current, then performs `fsubs`, `fdivs`, `fctiwz`,
integer+1/subtraction and signed comparison. Equality branches around both
stores: it does not repair a stale mirror when current already matches.
Other mode values take actual no-write branches. The fixed function is a leaf.

The reader proves instruction forms and order. RN00/NI0, finite binary32
operands/results and any supported divide domain remain runtime preconditions,
not facts captured from live state. The source evidence does not require the
bounded implementation to enable mode1 division.

## Reproduction and controls

```bash
python3 -m unittest discover -s research/tools/matching-decomp -p test_archived_actor_status_evidence.py
python3 research/tools/matching-decomp/read_archived_actor_status_evidence.py \
  'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
```

The focused suite passes **26 tests**, with both archives present. It checks
complete counts and physical traces, all four constants, operand/condition
fields, signed width and store/reload order, pause/mode gates, final effects
and static mandatory-call dominance. Corruption controls cover whole-snapshot
authentication before parsing, mapping/root/offset/overlap mutations before
new reads, range width/hash failures before decoding, one-bit mutations at
all548 instruction positions, each constant byte, reserved decoder fields,
unknown instructions, and disallowed CLI options. No original executable
fixture or archived-code execution is added. Optional local-archive tests skip
explicitly if the two private snapshots are absent; synthetic controls remain.

No rig/process inspection, new assets or captures, source transfer, upload,
installation, publication, or denied-operation retry was used for this work.
