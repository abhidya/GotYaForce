# Double prehook and ordinary-X action envelope: archived evidence

Date: 2026-11-14. Baseline: `79c4e84a34ab1afa200e625584dee5132c67578c`.

This is **static evidence from two existing archived Ghidra ProgramDB snapshots**.
It is not an original-DOL identity assertion, an instruction execution, a
matching-decompilation `MATCH`, a dynamic dispatch observation, numerical
parity, complete action playback, production integration or browser acceptance.
No original DOL, live RAM, telemetry, driver, GPU or network was used.

The new [fixed reader](../tools/matching-decomp/read_archived_double_action_evidence.py)
and [tests](../tools/matching-decomp/test_archived_double_action_evidence.py)
represent all **298 instructions and all operands in 14 fixed spans**, with zero
omitted instructions. External calls are retained as boundaries, not claimed
as implementations. Existing readers and their allowlists are unchanged.

## Authentication and selection controls

Before any new selection, the reader invokes the unchanged shared snapshot
inspection. It checks the actual whole-file SHA-256, exact supported schemas,
program language, executable metadata value/type, empty File Bytes table,
address mapping, complete data5 hash and established scalar controls. Stored
executable metadata is not a fresh hash of the original DOL.

| Snapshot | Whole-file SHA-256 |
| --- | --- |
| `db.3.gbf` | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| `db.4.gbf` | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

The exact text1, data3 and data5 mappings use the existing shared checks.
New data4 scalar reads additionally require unique `MAIN_.data4` block6,
encoded start `20000000004335a0`, length11040, initialized subblock6, chain
root262, type2, zero starting/source offsets and no overlapping mapping.
The selected virtual range is `804335a0..804360c0` exclusive. Data4 is **not**
dumped or hashed as a new broad payload selection. Only the two named
halfwords below are read after all mapping controls.

Each code span has a fixed address, width and SHA-256 and must decode every
instruction, end in an unconditional return, and keep every non-call direct
branch inside the selected span. Pointer cells have fixed target/digest checks.
Constants have exact bit checks. Unknown or duplicated selections, invalid
mapping types, bad widths, unsupported forms and malformed snapshots fail
closed. The CLI accepts one snapshot path, with no address, range, raw-output,
execution or pointer-following options. Returned pointers never select reads.

## Independent extents and hashes

Named C markers are from `research/decomp/ghidra-export/`; map sizes are from
`research/symbols/GG4E-CSM-20220412.map`. A missing map row is explicitly absent.

| Entry | Width / instructions | End exclusive | Map size | SHA-256 |
| --- | --- | --- | --- | --- |
| `8006f7c0` | 204 / 51 | `8006f88c` | absent | `e4b751102a00fb7b424274976e8bb1f140fe0807706cd1517078b40dbe3de8dd` |
| `8005f238` | 4 / 1 | `8005f23c` | absent | `f332ea5b5437103cbb6f1508679da89eec9288ad775c96c439a17fccabe3de8e` |
| `80065dfc` | 40 / 10 | `80065e24` | absent | `c594bd68034bba3cc31848d5a87038e876cdfc890c341310c2294b17e0bf21a5` |
| `8006facc` | 60 / 15 | `8006fb08` | absent | `5deeacdae63ecf201429acfbceebbb51b8ef807c1e450b943eec9a6141a564f0` |
| `80071598` | 60 / 15 | `800715d4` | 60 | `4ac9a8f7c2f0b6fbac5305b3c0db122125ccfe4e454ffe8e0924314cd3a7daf9` |
| `800715d4` | 36 / 9 | `800715f8` | 36 | `3cdd2ad074ad5dfab5f9e5817c06a9188420d3d4a0b70c9ce3ce7a8ab0da67ee` |
| `800ff2bc` | 80 / 20 | `800ff30c` | 80 | `6fd537f5d08e83e327f7cf326132bcc5a8e832b48badf8fd0959ceb48ccdea48` |
| `800ff30c` | 268 / 67 | `800ff418` | 268 | `72404d4312c0508eb0b293dcfc9a338bbdbad9f719b1a4fedc7cf217c2904f97` |
| `8006d144` | 100 / 25 | `8006d1a8` | 100 | `9192553250e34d5b4747df230f7eea747fbdeaa373bdf5436c086e45021c8707` |
| `800669d0` | 96 / 24 | `80066a30` | absent | `69f451585b1f653484e6dc9b7daa50eac754d1b0af9c07fb7bbd3e46cb3d63f1` |
| `8020ba78` | 36 / 9 | `8020ba9c` | 36 | `5997a5a32c7df8eb2a03901039345f35a84f00b017545800218ef21bdbfaf81a` |
| `8020ba9c` | 28 / 7 | `8020bab8` | 28 | `e0fbf8bbb6f184d7b21d322b68975adca6dc652510963c83c95b9ceb63e0671d` |
| `8020ba54` | 36 / 9 | `8020ba78` | 36 | `c7b35d4075874e063982faa1d7d086e5d5ec4d70aed2b56c619b5e440e18e1ab` |
| `80066a30` | 144 / 36 | `80066ac0` | absent | `04067a35ffbcd87ad1127ca2d980b63d26e9c05ffb80941604d1a31ddb44a68f` |

- Prehook `6f7c0`: `chunk_0009.c:4091`; the next exported marker is `6f8d4`,
  **not** the end of this function. Prior independently named posthook `6f88c`
  is omitted from C. The selected204-byte prehook ends at that address, with
  return `6f888`; it does not combine the separate72-byte posthook.
- UB0 `5f238`: no C marker or map row for the stub itself. Prior derived family
  evidence names its immediate return. The preceding named `5f188` map extent
  is176 bytes, ending exactly at `5f238`; the next C marker is `5f23c`
  (`chunk_0007.c:5843`). The fixed4-byte selection authenticates one complete
  unconditional return at this known entry, not a map-derived function size.
- `65dfc/40`: adjacent `65dfc` and `65e24` C markers in chunk0008:2724.
  `6facc/60`: adjacent `6facc` and `6fb08` in chunk0009:4205.
- `71598/60`, `715d4/36`: adjacent markers in chunk0009:5273 and5284,
  independently agreeing with their map rows.
- `ff2bc/80`, `ff30c/268`: adjacent markers `ff2bc`, `ff30c`, `ff418`
  in chunk0028:1723,1737,1778, independently agreeing with map rows.
- `6d144/100`: chunk0009:2495 to `6d1a8`, with map agreement.
  `669d0/96` and `66a30/144`: chunk0008:3372,3388 to `66ac0`; no map rows.
- Vector subtract `20ba78/36`, scale `20ba9c/28` and add `20ba54/36`:
  chunk0064:1274,1299,1249, with adjacent markers and matching map rows.
  Add/scale hashes agree with unchanged earlier traversal/mode1 evidence.

## Fixed dispatch cells and hidden configuration

The authenticated constructor witness is reused as prior evidence, not reread
by this new reader. Its literal base is `802d3b14`: load/store `6f620/6f624`
copies source+0 to actor4b4; `6f630/6f634` copies source+8 to actor4bc.
The existing constructor regression was rerun against both snapshots. See
[normal lifecycle evidence](actor-normal-lifecycle-evidence-2026-11-14.md).

| Fixed cell | Meaning | Authenticated target | Cell SHA-256 |
| --- | --- | --- | --- |
| `802d3b1c` | constructor-prehook | `8006f7c0` | `154203d03076144a9c4fe908daee41ac69e0c36249556a66cf47e8003ed7801b` |
| `802d37a8` | upper0 | `8005f238` | `8868a8515e4b649802f66057c61600c1899cea349f7d393786d886caaff607a4` |
| `802d379c` | full61 | `80065dfc` | `e6955d35c5cea55d3ab618c25eaaa6ecb58c408b0e21b2f29101334fb56b6201` |
| `802d3b14` | constructor-root | `8006facc` | `b9aebbd587956abb6bd0bb4e5c2099f98afed6fce826f48d5c5a627c966bd045` |
| `802d3b70` | action2 | `80071598` | `749496dd63f8f9fbe6d9574d4cc5109fb6d3d1a2fdd04e42a2f67a1a4f761e55` |
| `802d3c48` | variant0 | `800715d4` | `745d9df22815e0d2ebf0504740b71d230a0bc7f2b73fe3261e01502d8c360dcd` |
| `8031f000` | phase0 | `800ff30c` | `9461c792d0b20cf5b639ffc16b4fab5c53178e78c1ca538faea2a30286033974` |

Full-body61 `65dfc` loads the **actual actor4b4** at `65e08` and calls through
it at `65e10`. The Double root indexes base `802d3b68` by signed byte580;
action2 indexes `802d3c48` by signed byte581. Only the specified action2 and
variant0 cells are authenticated here; no table extent or other slot is claimed.
All selected dispatchers retain the signed extension, shift, indexed load and
branch-register operands, and contain no bounds checks.

Wrapper `715d4` sets `r4 = r13 - 32056` at `715dc` and directly calls `ff2bc`
at `715e4`. With the previously recorded r13 base `8043b5a0`, this is hidden
configuration address **`80433868`, not a pointer to `ff2bc`**. The shared
wrapper preserves r4, conditionally clears actorcc when signed byte541 is
nonzero, then indexes phase table `8031f000` using signed byte540. Only phase0
cell `8031f000` is selected. No callback pointer at config+4 is read.

| Exact config scalar | Width | Value | SHA-256 |
| --- | --- | --- | --- |
| `80433868` (ground-slot) | 2 | 0 | `96a296d224f285c67bee93c30f8a309157f0daa35dc5b87e410b78630a09cfc7` |
| `8043386a` (air-slot) | 2 | 1 | `b413f47d13ee2fe6c845b2ee141af81de858df4ec549a58b7970bb96645bc8d2` |

The phase0 instructions load these values with **signed `lha`**, then store
only the low byte. The authenticated values0/1 make signedness immaterial for
this fixed config, but the load widths are preserved in the witness.

## Exact instruction-named scalars

The recorded r2 base `8043ea20` and r13 base above are prior documentation,
not freshly authenticated startup or live register values. See the
[earlier family decode](nn-family-decode-2026-07-06.md) for the recorded r13
basis and [mode1 evidence](actor-mode1-envelope-evidence-2026-11-14.md) for r2. The address and
bit checks below are literal; no runtime base determines a reader selection.

| Scalar | Width | Bits | Value / purpose |
| --- | --- | --- | --- |
| `804376f8` | 4 | `43160000` | 150.0 / prehook-scale |
| `804375c8` | 8 | `4330000080000000` | 4503601774854144.0 / signed-integer-conversion-double |
| `804392b4` | 4 | `00000000` | 0.0 / phase0-zero |
| `804392b8` | 4 | `bf800000` | -1.0 / phase0-stream-rate |
| `804392d0` | 4 | `3f733333` | 0.949999988079071 / phase0-carry |

All new selected bytes total1248:1192 code,28 pointer cells,24 float/double
constants and4 config bytes. Both snapshots agree on every derived operand,
scalar, target, mapping and physical chain trace. Exact physical spans are
frozen in the new test's `PHYSICAL` dictionary and included in the JSON output.

## Prehook source order and capture widths

The complete `6f7c0` sequence is:

1. Signed halfword3e8 read at `6f7d4`; store byte582=1 for3, otherwise0.
2. Load control5e0 at `6f7f4`. If bit1 is clear, store halfword1dfc=0 at
   `6f804`, then byte6ee=0 at `6f808`.
3. **Fresh** control5e0 load at `6f80c`. If bit1000 is clear, signed halfword
   272 load at `6f818`, clear bit4 and store halfword272 at `6f820`.
4. Load byte58e at `6f824`, clear20 and store byte58e at `6f82c`.
5. **Fresh** signed halfword3e8 load at `6f830`. Only for3, load byte7c8 at
   `6f83c`, sign-extend and test. Zero returns without vector work.
6. For nonzero7c8, reload58e at `6f848`, set20 and store at `6f858` before
   calling external normalization4538c with source/destination actor7b0.
7. After normalization, load scalar150 at `6f860`, then actor floatb4 at
   `6f868`; single multiply at `6f870`; call selected three-component paired
   scale20ba9c at `6f874`. Return `6f888`.

Equal-value stores still occur. The routine never writes7c8 itself. The
normalization call4538c is not selected/implemented by this evidence, so an
implementation limited to the unarmed path must refuse at that boundary rather than manufacture
armed-clone normalization. The posthook6f88c is not read or implemented here.

## Phase0 and null-target turn-helper schedule

`ff30c` first retains the hidden config in r31 and actor in r30, loads byte540
at `ff328`, increments and stores at `ff330`. It loads actorcc and, only when
zero, captures signed heading72 at `ff340` and stores halfword5ac at `ff344`.
It then calls real `6d144(actor,0xc1)` at `ff350` even for a null target.

`6d144` reloads actorcc at `6d160`. Its null path captures signed heading72
**before** signed5ac (`6d174`,`6d178`), subtracts and stores halfword5aa at
`6d180`. Its nonnull path calls external6660c and is not closed by this slice.
Both paths call669d0, preserving that callee's r3 result through the epilogue.

`669d0` uses `2*(mask&15)` to index the existing parameter block at actual4ac.
With maskC1 this selects the signed halfword at block+ae. It loads float1dc8
at `669f4` **before** the signed rate at `669f8`. Signed conversion uses the
fixed double bias; `fsubs` then `fmuls` rounds at each single operation,
`fctiwz` truncates, `stfd`/`lwz` extracts the integer and passes it to66a30.
Nonfinite/out-of-signed32 conversion behavior is not supplied by this evidence.

`66a30` captures signed5aa then signed72 at entry. It compares the absolute
signed remainder to the sign-extended low16 step. For a partial step, it
conditionally negates the step according to the captured remainder, **reloads
5aa** at `66a64`, then stores remainder5aa, conditional lock heading5ae and
conditional heading72 in that order. The heading computation retains the entry
capture72. The completed branch stores5aa=0, then conditional5ae and72.
Mask40 selects5ae and80 selects72. Partial returns0 at `66a90`; complete
returns1 at `66abc`. These returns pass through669d0 and6d144 without r3
being overwritten. Signed16 truncation and low16 stores must remain explicit.

After the real helper returns, phase0 loads one zero float at `ff354` and
stores50,48,4c,44 in that order (`ff364`,`ff36c`,`ff370`,`ff374`), followed
by zero halfwords80,7e,7c. It calls subtract at `ff384` using **own**
position20 minus own saved5e8 into38, scales38 by fixed0.95 at `ff394`, then
adds38 into20 at `ff3a4`. It reaches **real677b0** at `ff3ac`.

The evidence fully represents the later instructions, but a bounded runtime
without genuine677b0 must stop before that call. The existing3d6e4 terrain
query is not an equivalent replacement. Only after677b0 returns does source
load config ground slot into6ea, optionally overwrite from air slot on a fresh
control40 test, capture the resulting byte, increment6ea, start maskF/group4
at rate−1 using the captured signed slot, and finally store80c=0.

## Paired vector schedule and numerical ceiling

Subtract20ba78 and add20ba54 each load sourceA XY, sourceB XY, calculate and
store destination XY **before** loading sourceA Z and sourceB Z. The Z result
is then stored. Scale20ba9c loads both source XY and source Z before its first
multiply/store, then stores XY before calculating/storing the captured Z.
It is a three-component vector scale despite the exported `PSQUATScale` name.

All quantized instructions use GQR0, W0 for XY and W1 for Z. A bounded host
implementation explicitly requires GQR0 load/store type0 and scale0,
FPSCR RN00 and NI0, and finite inputs/results. These are admission assumptions,
not authenticated live values. Every instruction retains its paired lanes,
source/destination registers and record fields. Single arithmetic, paired
arithmetic and the conversion do not become numerical parity claims merely
because their operation ordering is known.

## Reproduction and focused verification

From the repository root, without fetching missing local inputs:

```sh
python -m unittest discover -s research/tools/matching-decomp -p test_archived_double_action_evidence.py -v
python -m unittest discover -s research/tools/matching-decomp -p test_archived_actor_normal_evidence.py -v
python research/tools/matching-decomp/read_archived_double_action_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf' > .tmp/double-action-evidence/db3.json
python research/tools/matching-decomp/read_archived_double_action_evidence.py 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf' > .tmp/double-action-evidence/db4.json
```

The new focused suite passes **19 tests**, including both local archives.
The unchanged normal/constructor regression passes **20 tests**. Synthetic
frozen operand schedules are independently inverse-encoded to every fixed
span hash; actual archives are compared to those schedules and exact physical
traces. Negative tests cover width/digest/type/duplicate errors, unknown
instructions, terminal/branch extents, reserved fields, invalid schemas and
mappings before new reads, scalar values, pointer cells, and forbidden CLI
options. Missing archives skip local cases rather than fetch.

These are focused static-evidence checks, not the contributor/docs aggregate,
not a runtime test of the game and not a browser verification. Required
remaining behavior includes677b0 and its distinct terrain query, nonnull target
facing, reached stream commands and animation progression, later shared-X
phases and callback/resource/projectile behavior, charged-clone normalization,
posthook and full outer-frame completion. No fallback or live enablement is
implied by these witnesses.
