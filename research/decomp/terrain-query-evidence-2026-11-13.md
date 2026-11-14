# Terrain query: fixed archived evidence, 2026-11-13

## Scope and authentication

`research/tools/matching-decomp/read_archived_terrain_query_evidence.py` reads
only four fixed text spans and six fixed constants, after the existing complete
snapshot authentication, schema, Program metadata, empty File Bytes, address
map, text1/data3/data5 mappings, full data5 hash and independent constant guards.
It extends the existing selected-field reader locally with `fdivs`, `fcmpu`
and `cror`; shared readers are unchanged. Output contains derived fields,
hashes, constants and physical traces, never a raw executable range. There is
no arbitrary-address CLI, network operation or archived instruction execution.

Both already-present archive snapshots authenticate:

- db.3.gbf: `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`
- db.4.gbf: `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`

The snapshots have identical selected bytes, derived instructions, constants
and physical traces. All four spans use root21/data36, with obfuscation enabled:

| Start, exclusive end | Bytes | SHA256 | Chain offset | Data offset | Physical offset |
| --- | ---: | --- | ---: | ---: | ---: |
| 8003d6e4–8003d964 | 640 | 3788a13d2282f6b5ae753eb0d7f29c13289f305f35665a0122ce54e8e1fca7b3 | 229636 | 344 | 606558 |
| 8003f320–8003f688 | 872 | 559b34375add13a9156ac4437abc9633cb1f52dcb53817a21c5b95ca3ee4cb1a | 236864 | 7572 | 613786 |
| 8003fa68–8003fb00 | 152 | a8447bcc787bb143584b40bf66dde650f1d635c841eb1948b95fb421f8a57c8a | 238728 | 9436 | 615650 |
| 8003fb00–8003fb58 | 88 | 333885e9781b90d779a3a3056c414854cac154f64352ef15cf25aa8fec76b908 | 238880 | 9588 | 615802 |

There are 158, 216, 38 and 22 selected instructions respectively. Only the two
functions' link-register save/restore instructions are omitted (four total);
all arithmetic, data loads/stores and branches in these spans are decoded.

Constants use root263/data264 with obfuscation enabled. Chain and data offsets
are equal. The recorded r2 basis is 8043ea20 and r13 basis 8043b5a0
(`docs/static-recompilation-spike.md:178–179`); r13-21316 resolves 8043625c,
which holds the runtime terrain-owner pointer.

| Address | Bits | Value | r2 displacement | Chain/data offset | Physical offset |
| --- | --- | ---: | ---: | ---: | ---: |
| 80436f68 | 00000000 | +0 | -31416 | 1352 | 4343118 |
| 80436f88 | 4330000080000000 | 4503601774854144 (f64) | -31384 | 1384 | 4343150 |
| 80436ffc | 43fa0000 | 500 | -31268 | 1500 | 4343266 |
| 80437034 | c5ea6000 | -7500 | -31212 | 1556 | 4343322 |
| 80437038 | 45ea6000 | 7500 | -31208 | 1560 | 4343326 |
| 80436f70 | bf000000 | -0.5 | -31408 | 1360 | 4343126 |

The last constant is authenticated only to describe the **excluded nonempty
+20 ceiling branch**. The runtime terrain owner's +34 and +68 values are not
these constants; they are real runtime reads, called H and L below. No numeric
value for H or L is inferred from archive import metadata.

This is archived ProgramDB evidence, not proof of unchanged original-DOL bytes,
live FPSCR/GQR state or gameplay parity. Interpret the numerical derivations
inside the existing finite binary32, RN=00/NI=0 domain with valid memory and
finite intermediates. Float loads and single arithmetic round as the source
requires. Integer-conversion overflow, NaNs, infinities, unsupported address
wraps and traps are not admitted merely because fields can be decoded.

## Entry, range test and actual owners

C references are `research/decomp/ghidra-export/chunk_0004.c:6993–7047`,
8246–8261, 8288–8296, 8502–8510 and 8520–8526. Instruction evidence takes
precedence over algebraic simplifications in the C export. Addresses in the
following tables omit the common 800 prefix where unambiguous.

Query 8003d6e4 receives clearance in f1, actor in r3, point in r4. It saves actor
in r29, point in r30 and clearance in f30. At 3d714 it loads actor byte+1db,
then sign-extends with record and branches to 3d740 only for zero. A nonzero
value reaches matrix/contact computation3d724–3d73c and is outside this slice.
Do not replace the byte with an assumed false contact callback.

The zero path calls 8003fb00 on the supplied point. Its finite-input sequence is:

1. 3fb00 loads pointX,3fb04 loads-7500;3fb08 compares X to the lower bound;
   3fb0c combines LT|EQ and3fb10 returns zero if X<=-7500.
2. 3fb14 loads7500;3fb18 compares X to the upper bound;3fb1c combines GT|EQ;
   3fb20 goes to the Z test only if X<7500. Otherwise return zero.
3. 3fb2c loads pointZ;3fb30/34/38 reject Z<=-7500;3fb3c/40/44 reject Z>=7500.
4. 3fb50 returns one. **No pointY read or Y bound occurs in this range test.**

The implementation may require finite XYZ for its numeric domain, but must not
claim the source has a Y-in-(-7500,7500) test. At 3d748–54 an out-of-range result
returns a newly loaded pointY. The runtime admits this early return without demanding terrain fields or history scalars; the integration demonstration below uses the genuine in-range query.

For the admitted in-range path, loads, temporary stores and reloads occur in
this order:

| PC | Operation |
| --- | --- |
| 3d758–770 | Load terrain owner, H=owner+34; compare original clearance>=H using fcmpo and cror(GT,EQ); set r31=1 if true, otherwise0. This flag is saved before any clearance adjustment. |
| 3d774–77c | Load pointX and store localX at stack+14. |
| 3d780–78c | Load pointY, then actor+6d0 current stepHeight; add32 and store localY at stack+18. |
| 3d790–794 | Load pointZ and store localZ at stack+1c. |
| 3d798–7a4 | Load actor+30 savedGroundPos.y, then actor+6d4 previousStepHeight; add32; call8003f320 with this height and the localXYZ pointer. |
| 3d7a8–7b8 | Reload savedGroundPos.y; save returned ceiling in f31; reload previousStepHeight; load actor+24 current pos.y; reload current stepHeight. |
| 3d7bc | add32(savedGroundPos.y, previousStepHeight). |
| 3d7c0–7c8 | Load+0; add32(pos.y,current stepHeight); sub32(previous sum,current sum). |
| 3d7cc–7d4 | Compare0 with delta; only if0<delta, add32(original clearance,delta). |
| 3d7d8–7e0 | Reload original pointY; add32(adjusted clearance,pointY), producing the floor acceptance limit. |
| 3d7e4 | Call8003fa68 on the original point pointer for the +1c floor grid. |
| 3d7e8–7fc | Reload terrain owner; load saved localX; load L=owner+68; load H=owner+34; copy L to max; load saved localZ. |

These are actor-owned fields, not a second shadow history. The first +30/+6d4
sum is an argument to the ceiling query; the sum used in delta is constructed
from fresh loads after that call. Likewise the floor lookup uses the original
point, while triangle deltas use the previously saved localX/localZ. Do not
collapse these distinct reads into one eager snapshot. The source query writes
only stack temporaries on this path, not actor or terrain state.

## Genuine grid lookup and ceiling-empty path

8003f320 first calls 8003fb00 again on localXYZ. For the admitted path, that
range test succeeds. It then visits the actual terrain grid at owner+24 and
**only afterward** owner+20.8003fa68 later visits owner+1c. Each grid consumes:

- signed-int32 originX at grid+10 and originZ at grid+14;
- the dimension/stride word at grid+c, used by `mullw`;
- the cell-pointer-table address at grid+18.

There is no read of grid+0/+4 cell-size words or grid+8 dimension in these
query functions. The cell size comes from authenticated80436ffc=500. An
independent model can validate stored dimensions/storage bounds, but those
checks must not be described as instructions in these spans.

Each signed origin word is XORed with80000000 and placed below high word
43300000. `lfd` loads that constructed double. **`fsubs`, not double `fsub`,**
subtracts4503601774854144 and rounds the resulting signed origin to binary32.
Then the source does:

```
originX32 = round32(signedInt32(originXWord))
originZ32 = round32(signedInt32(originZWord))
xFraction = div32(sub32(pointX, originX32), 500)
zFraction = div32(sub32(pointZ, originZ32), 500)
ix = fctiwz(xFraction)  // signed int32 conversion, truncate toward zero
iz = fctiwz(zFraction)
indexWord = low32(iz + low32(ix * strideWord))
byteOffset = low32(indexWord << 2)  // rlwinm SH=2,MB=0,ME=29
listPointer = loadWord(cellPointerTable + byteOffset)
```

Do not use floor for negative fractions, divide in unrounded binary64, or
silently infer a 2-D index from a different grid dimension. The safe bounded
host subset must reject invalid indices or unavailable storage rather than
use source low-word arithmetic to authorize out-of-bounds reads.

The precise lookup scheduling is:

| Stage | Origin/coordinate and quotient sequence | Index/list load |
| --- | --- | --- |
| +24,3f360–3e4 | Read both origin words; load localX; convert originX with fsubs3f390; load localZ; sub32 X3f3a0; convert originZ3f3a8; load H3f3ac; div32 X3f3b4; sub32 Z3f3b8; convert ix3f3bc; div32 Z3f3c0. | Store/reload ix; mullw3f3cc; convert/store/reload iz; add3f3dc; slwi3f3e0; lwzx3f3e4. |
| +20,3f4dc–564 | Load second grid; read both origin words; reload localX3f500; convert originX3f50c; reload localZ3f518; sub32 X3f51c; convert originZ3f528; div32 X3f530; sub32 Z3f538; convert ix3f53c; div32 Z3f540. | Store/reload ix; mullw3f54c; convert/store/reload iz; add3f55c; slwi3f560; lwzx3f564. |
| +1c,3fa7c–af4 | Load floor grid; read both origin words; load original pointX3fa90; convert originX3faa8; load original pointZ3faac; sub32 X3fab8; convert originZ3fac0; div32 X3fac4; sub32 Z3fac8; convert ix3facc; div32 Z3fad0. | Store/reload ix; mullw3fadc; convert/store/reload iz; add3faec; slwi3faf0; lwzx3faf4. |

+24 jumps directly to its first list-entry read3f4cc. It loads an entry,
computes low32(entry+10000), and compares that unsigned value to0000ffff.
Equality is exactly entry=ffffffff, the sentinel. On that sentinel the
triangle body3f3ec–3f4c8 is not executed. +20 uses the same sentinel test at
3f65c–668 and skips body3f56c–658 when empty. The second grid and second list
must really be read; a first empty list does not stand in for both. If both
selected lists are sentinel-empty, the returned f1 is the H loaded at 3f3ac.
Neither grid is a callback or an assumed empty placeholder.

The excluded nonempty ceiling bodies have additional edge/subtraction tests
and plane computation. +20 additionally reads normalY and compares it with
-0.5 at 3f604–618, accepting this condition only when normalY<=-0.5. This is
why 80436f70 is included. Nothing in the empty-path implementation should admit
those bodies on the strength of this note.

## Actual floor-cell triangle scan

The integration demonstration uses a genuinely nonempty +1c cell list. The runtime also admits an actual empty list and executes the source sentinel fallback. Every
entry is an actual triangle pointer/owned triangle identity; the scan advances
one four-byte entry and stops only at the exact ffffffff sentinel. At 3d8f0–8fc
the sentinel is tested before entering the triangle body; it is not a triangle
count, a negative-pointer test or an end inferred from unrelated storage.

Define the actual selected triangle's vertices by record offsets:

- v1=(+4,+8,+c)
- v2=(+10,+14,+18)
- v3=(+1c,+20,+24)
- normal=(+28,+2c,+30)

Only v1Y is read by the plane computation. The floor edge path reads v1X and
subtracts localX; stores dx1 on stack; reads v1Z and subtracts localZ; stores
dz1 on stack; loads v2X,v2Z; computes dx2; loads v3X; computes dz2; loads v3Z;
computes dx3; forms the first products; finally computes dz3. Thus the source
prefix is observable if a bounded reader refuses a later missing field.

With each subtraction and multiplication independently rounded to binary32:

```
dx1=sub32(v1X,localX); dz1=sub32(v1Z,localZ)
dx2=sub32(v2X,localX); dz2=sub32(v2Z,localZ)
dx3=sub32(v3X,localX); dz3=sub32(v3Z,localZ)
```

The three sequential edge tests are:

| PCs | First product | Second product | Branch |
| --- | --- | --- | --- |
| 3d838–848 | mul32(dz1,dx2) | mul32(dx1,dz2) | Skip triangle if first<second. |
| 3d84c–858 | mul32(dz2,dx3) | mul32(dx2,dz3) | Skip triangle if first<second. |
| 3d85c–868 | mul32(dz3,dx1) | mul32(dx3,dz1) | Skip triangle if first<second. |

Equality passes; no epsilon, division, fused cross product or normal load
occurs before all three tests pass. Later edge products are not evaluated if
an earlier test skips the triangle.

For an inside triangle, the actual normal components are loaded with integer
word copies to stack and reloaded as floats in this exact order:

1. 3d86c load normalX word;3d870 load normalZ word;3d874 store normalX.
2. 3d878 load normalY word;3d87c store normalZ.
3. 3d880 reload normalX;3d884 reload normalZ;3d888 store normalY.
4. 3d88c multiply normalX*dx1;3d890 multiply normalZ*dz1.
5. 3d894 load v1Y;3d898 reload normalY.
6. 3d89c add the X and Z products;3d8a0 multiply normalY*v1Y.
7. 3d8a4 add that Y product;3d8a8 divide by normalY.

There is **no FMA in any of the four query spans**. Preserve this mathematical
operation tree even for admitted normal (0,1,0):

```
xProduct = mul32(normalX, dx1)
zProduct = mul32(normalZ, dz1)
xzSum = add32(xProduct, zProduct)
yProduct = mul32(normalY, v1Y)
numerator = add32(xzSum, yProduct)
height = div32(numerator, normalY)
```

The current bounded runtime domain may admit only actual flat normal (0,1,0).
It must verify those actual fields instead of synthesizing them or using
v1Y as a constant floor shortcut. Other normals, overflow/nonfinite arithmetic
and unsupported later paths remain separate work. The instruction evidence
itself does not impose the flat-normal restriction.

## Ordered accumulators and final selector

At 3d7f0–7f8 the registers start as best=L(f0), min=H(f2), max=L(f1).
The limit in f30 is adjustedClearance+reloadedPointY; f31 is the actual ceiling
query result. For each inside triangle, after computing height:

1. 3d8ac compares limit to height;3d8b0 skips the best update unless limit>height.
2. 3d8b4 compares ceiling to height;3d8b8 skips unless ceiling>height.
3. 3d8bc compares best to height;3d8c0 combines LT|EQ;3d8c4 skips unless best<=height.
   Otherwise3d8c8 copies height into best. Both limit/ceiling inequalities are strict.
4. Regardless of whether best changed,3d8cc compares min to height;
   3d8d0 combines GT|EQ;3d8d4/8d8 set min=height when min>=height.
5. 3d8dc compares max to height;3d8e0 combines LT|EQ;3d8e4/8e8 set max=height
   when max<=height.
6. 3d8ec advances the list pointer by4;3d8f0 reads/tests the next entry.

A non-containing triangle updates none of these registers. Source order is
not a sort, average, nearest-distance selection, or a single unconditional
maximum. Even if the admitted runtime geometry often makes all three results
equal, the three independent accumulators and fallback decisions matter.

After the sentinel,3d900–908 tests the flag formed from **original** clearance
and the **entry-time** H. If originalClearance>=entryH, return max. Otherwise:

- 3d90c reloads the terrain owner;3d910 reloads L.
- 3d914 `fcmpu(best,reloadedL)` tests equality. If unequal,3d91c returns best.
- If equal,3d924 reloads H;3d928 `fcmpu(min,reloadedH)` tests equality.
- If min==reloadedH return the reloaded L; otherwise3d934 returns min.

The final sentinel comparisons therefore use fresh terrain-bound reads, not
only the initialization values. For finite stable owners this is equivalent
to the compact rule `clearance>=H ? max : best!=L ? best : min!=H ? min : L`,
but that expression is not permission to elide the source loads.

## Caller no-correction continuation

The preexisting fixed terrain-handler reader authenticates 80047164 onward;
its evidence is `terrain-matrix-handlers-evidence-2026-11-13.md`. That reader
was rerun locally to verify the boundary after the new query:

- 47240 performs add32(the caller's original saved clearance,returnedHeight).
- 47244 reloads the caller-local jointY, not the query's temporary localY.
- 47248 compares jointY to the sum.
- 4724c branches to 472e0 only when jointY is **strictly greater**.
- Otherwise 47250 first replaces stackY; 47268 is the first persistent correction
  position store, followed by 4726c and later correction metadata/count work.

The bounded continuation may accept only the genuine strict-GT branch. Equal
or lower jointY must refuse before 47250 and before correction-entry stores;
no fabricated no-op correction result is supported. This refusal retains the
already executed outer traversal, dispatch clears, reads and stack-only query
work. The caller uses its original clearance; the query's delta-adjusted
clearance must not leak into 47240. Subsequent accepted-loop behavior remains
owned by the existing handler, not by a new terrain callback.

## Worked mathematical trace, not original execution

This example is a synthetic finite-input derivation, not an archive replay or
an authenticated claim about runtime H/L values. Let original point=(100,10,100),
clearance=5, savedGroundPos.y=20, previousStepHeight=2, pos.y=10, current
stepHeight=1, H=1000 and L=-1000. Each of the three actual grid headers has
origin (0,0), stride 2 and valid storage for the selected cell. Both ceiling
cell lists are `[-1]`. The floor cell list is `[triangle,-1]`, with actual
vertices (0,4,0),(0,4,400),(400,4,0) and actual normal (0,1,0).

1. Bounds accept X/Z. Clearance 5 < H records the small-clearance selector.
2. Local point=(100,11,100); ceiling argument=add32(20,2)=22.
3. Each grid quotient is div32(100,500), approximately 0.20000000298023224;
   fctiwz gives 0, index=0*2+0=0. The +24 and +20 cell sentinels are separately
   read, so the ceiling query returns its real H=1000.
4. Reloaded delta=sub32(add32(20,2),add32(10,1))=11. Adjusted clearance 16;
   floor limit=add32(16,10)=26. The real +1c cell returns the triangle.
5. Deltas are (-100,-100),(-100,300),(300,-100). Edge product pairs are
   (10000,-30000),(90000,10000),(10000,-30000), all passing.
6. Plane products are -0,-0, then sum -0, Y product 4, numerator 4 and quotient 4.
   The operation tree is retained; no constant-ground shortcut is used.
7. 4<26,4<1000 and -1000 <= 4 give best 4; min and max separately become 4.
   Final small-clearance selection returns best 4 after rereading L.
8. Caller sum=add32(5,4)=9; reloaded jointY 10 > 9 follows the no-correction branch.
   If the returned height were 5, the sum would be 10 and equality would require
   refusal before correction work, not acceptance.

## Reproduction and focused verification

From the repository root:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 research/tools/matching-decomp/test_archived_terrain_query_evidence.py
PYTHONDONTWRITEBYTECODE=1 python3 research/tools/matching-decomp/read_archived_terrain_query_evidence.py \
 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
PYTHONDONTWRITEBYTECODE=1 python3 research/tools/matching-decomp/read_archived_terrain_query_evidence.py \
 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

All 16 synthetic tests pass. They cover the new decoder forms and invalid
encodings, fixed spans/root/width/bounds/hash rejection, derived-only output,
synthetic origin-conversion order, separate plane operations, CR branch order,
low-word index/sentinel fields, constant bits/widths and authentication before
any query-span read (including forged allowlisted digest rejection). Both
archive reads pass with identical range/constant/trace results. The existing
terrain-handler reader also passed on db.3 for the caller boundary above.
These are focused evidence checks, not runtime or aggregate checks. The evidence extraction
itself made no runtime edits, remote requests, asset acquisition, source
transfer, rig actions, commit or publication.
