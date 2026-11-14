# Terrain matrix handlers: archived evidence, 2026-11-13

## Scope and authentication

The fixed reader `research/tools/matching-decomp/read_archived_terrain_matrix_evidence.py`
reuses whole-snapshot SHA authentication, ProgramDB schema/import metadata checks,
empty File Bytes, address mappings, full data5 authentication and controls. It
checks exact text1/data3/data5 mappings and reads only these two text spans and
three constants. It outputs derived instruction fields and physical traces,
not raw executable ranges; it has no arbitrary-address CLI and executes no
archived instructions. Selected decoding adds xoris, lfsx, fcmpo and fmadds.
The latter names its operands explicitly: fD = round32(fA * fC + fB).

Both existing db.3.gbf and db.4.gbf snapshots agree:

| Start | Bytes | SHA256 |
| --- | ---: | --- |
| 80047164 | 480 | 4568ff72bcbdb8e255eb225282710693120e868fce1afab45dd4de78f8191563 |
| 80047344 | 36 | 79c608b75e1ef0dbe48958d8d395daccb1b445f8cab487d781e0b3b43a52135e |

Both spans use root21/data38. The first has chain offset269188, data offset7140,
physical offset646122; the second has chain269668, data7620, physical646602.

| Constant | Bits | Value | r2 displacement |
| --- | --- | --- | ---: |
| 8043709c | 3f4ccccd | 0.800000011920929 | -31108 |
| 804370a4 | 40000000 | 2.0 | -31100 |
| 804370b8 | 4330000080000000 | 4503601774854144.0 | -31080 |

The recorded r2 basis is 8043ea20 (`docs/static-recompilation-spike.md:178`).
Constants use root263/data264, chain/data offsets1660,1668,1688 respectively.
This is archived ProgramDB evidence, not proof of unchanged original-DOL bytes,
live FPSCR/GQR state, gameplay parity or complete terrain behavior. Existing
finite exact-binary32 RN00/NI0 host bounds continue to apply.

## Dispatcher ownership and distinct selector3 leaf

The prior normal-matrix reader authenticates the indexed table at802d0d60:
selector2 reaches80047164 and selector3 reaches80047344. The caller46e7c clears
actual count1d96 then count1d97 before testing suppression, loading the selected
handler and calling it. Those clears belong to the dispatcher, not either leaf.
The descriptor pointer4b0 is loaded and descriptor+22 formed before entry.

Despite the C export lacking a separate47344 function, the archive contains a
complete distinct leaf. Handler2 ends at47340 with blr. Selector3 starts47344
using actor register r3, not handler2's saved r27, and ends47364 with blr.

| PC | Operation |
| --- | --- |
| 47344 | load actor+1d60 |
| 47348 | load constant8043709c |
| 4734c | fmuls |
| 47350 | store actor+1d60 |
| 47354 | load actor+1d58 |
| 47358 | reload actor+1d60 |
| 4735c | fadds |
| 47360 | store actor+1d58 |
| 47364 | return |

Use controller.field1d60 and actual world.adjusted1d54.y (+1d58), not a new
adjusted-Y shadow. The descriptor is not dereferenced. This leaf does not read
metadata1d99, movement670, position or any matrix. A late adjusted-Y failure
must retain the earlier damping store. Preserve the damping reload, and use
source-rounded addition rather than importing the damping-only46ef4 behavior.

## Handler2 entry arithmetic

The C export is `research/decomp/ghidra-export/chunk_0005.c:3424–3483`.
Instruction evidence refines its load order and fused arithmetic:

1. 47188 loads actor byte1d99; 47190 loads float670 into f31.
2. 47198 extracts the low nibble; 4719c xoris forms its conversion bits.
3. 471a0 loads positionY at actor+24.
4. 471ac loads double804370b8; 471b0 fadds rounds positionY+clearance.
5. 471b4 loads the constructed conversion double from stack.
6. 471bc loads float804370a4 (2); 471c4 fsubs yields exact nibble0–15.
7. 471cc fmadds f30=f3*f1+f0 computes the threshold with one final rounding.

Thus use `fma32(2, nibble, add32(positionY, clearance))`, not a single unrounded
host expression. Threshold construction occurs even when the first descriptor
byte is the sentinel or every entry will be skipped. Reuse actual
metadata.byte1d99, movement.field670 and RomActor.pos.y. Clearance and threshold
are saved for the loop; the skip byte is freshly loaded each iteration.

## Genuine no-query loop paths

472e8 tests index<4 before reading descriptor storage. At472f0 it loads the
byte at descriptor+22+8*i, sign-extends it, and compares exactly -1. Other
negative bytes are not sentinels and must not silently terminate the loop.

471d4 reloads metadata1d99, 471e0 sign-extends it, and 471e4/471e8 test
`signExtend8(byte1d99) & (1 << (i+6))`. Sign extension matters for entries2/3:
byte0xc0 skips all four entries; using an unsigned byte would wrongly reach
bits8/9. Skipped entries perform no matrix loads. Iteration advances both index
and descriptor cursor by one entry (eight bytes), then retests the bound.

An unskipped entry performs these ordered reads:

- 471f0 sign-extends the descriptor byte already cached by the loop condition.
- 471fc lfsx loads X from actor+8e0+48*cachedJoint; 47200 stores it locally.
- 47204 reloads the same descriptor byte and sign-extends it at47208.
- 47214 loads Y from actor+8f0+48*reloadedJoint; 4721c stores it locally.
- 47220 fcmpo compares Y with the saved threshold.
- 47224 loads Z from actor+900+48*reloadedJoint; 47228 stores it locally.
- 4722c skips the query only if Y is strictly greater than threshold.
- 47230–47238 prepare clearance, actor and the local XYZ pointer.
- 4723c calls8003d6e4.

The Z load happens after comparison but before the branch. Above-threshold
paths still require X, Y and Z. For finite admitted inputs, equality reaches
the query and is unsupported by a no-query implementation.

Use actual world matrices8d4 and their existing matrix owner, translation
indices3/7/11. The cached X index and descriptor-reloaded Y/Z index are distinct
source loads even when stable host records usually make them equal. Do not use
movement's optional copied-Y storage, invent a height callback or return a
constant ground result. A world accessor may return the actual owned matrix;
it must not synthesize matrix contents or eagerly read all translation fields.

The existing movement descriptor binding's joint22/joint2a/joint32/joint3a
fields already own the four needed descriptor bytes and share mapping.descriptor4b0.
Reuse that identity and storage. No other descriptor bytes are consumed on
accepted no-query paths. Sentinel/skip paths must not demand unread matrices,
while entry arithmetic still requires its actual fields.

## Completion and refusal boundary

A no-query implementation can accept a first/later sentinel, four skipped
entries, all reached joints above threshold, or mixtures of these paths. It
must stop at the first reached query, preserving the source prefix. At that
point the first matrix traversal and dispatch count clears already happened.
Handler2 itself has written only temporary stack values: no correction entry,
count increment, damping or adjusted-Y write has happened yet. It must not run
the tail, corrected traversal or caller postprocessing after refusal.

On successful loop exit, handler2's separate tail is47300–4731c:
load1d60, load0.8, fmuls, store1d60, load1d58, reload1d60, fadds, store1d58.
Its effects match selector3 but its instruction addresses and actor register
differ. Both count bytes remain the dispatcher's zeros, so the subsequent
corrected traversal genuinely scans no entries and must actually rebuild.

Terrain queries, correction-entry writes, positive-count correction effects,
other handlers and active47904 remain unsupported. No no-op backend or claimed
full terrain implementation follows from this bounded evidence.

## Reproduction and verification

From the repository root:

```sh
PYTHONDONTWRITEBYTECODE=1 python research/tools/matching-decomp/test_archived_terrain_matrix_evidence.py
PYTHONDONTWRITEBYTECODE=1 python research/tools/matching-decomp/read_archived_terrain_matrix_evidence.py \
 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
PYTHONDONTWRITEBYTECODE=1 python research/tools/matching-decomp/read_archived_terrain_matrix_evidence.py \
 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

All 12 synthetic tests passed. Both archived snapshots passed authentication,
span hashes and constants; decoded ranges and physical traces agree. Tests
cover decoder operands, fixed-range admission, hash/width rejection, constant
bits/width, synthetic tail order and authentication failure. They are not
runtime/aggregate or original-machine execution tests. This evidence review
performed no remote operations, new source/asset acquisition, runtime edits
or publication.
