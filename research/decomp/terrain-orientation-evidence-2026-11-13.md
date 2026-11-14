# Secondary terrain orientation: archived evidence, 2026-11-13

## Scope and result

`research/tools/matching-decomp/read_archived_terrain_orientation_evidence.py`
authenticates the smallest selected secondary-correction call chain:
`4784c -> PSMTXMultVec -> 3de80 -> 45918 -> 45ef4 -> 46158`, with the
associated vector magnitude, cross-product and normalization routines. Existing
fixed evidence already covers the caller's correction-entry stores, positive
`46914` scans, grid/ceiling helpers, matrix Scale and matrix Concat.

The chosen positive axis pair is **normal axis 2, reference axis 1**. Its
authenticated selector is 2 and its constructor is `80046158`. The selected
domain requires that constructor's first attempt to succeed. Negative axes,
other constructors, the fallback attempt, primary correction `47368`, general
IK and unrestricted estimator inputs are not covered by this extension.

This is genuine secondary correction, not primary height-placement IK.
`4784c` transforms the current joint's ordinary pose translation using the
incoming parent matrix, stores the resulting translation, queries a normal at
that point and orients the basis. It does **not** read the primary entry's
corrected height or replace translation with that height. For descriptor
joint1, the primary scan key is `signExtend8(1)-2 = -1`, which cannot match an
admitted nonnegative joint; the secondary entry can nevertheless match joint1.
The first scan must actually read and miss before the second scan matches.

## Authentication and exact scope

Both already-present ProgramDB snapshots under
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`
pass complete snapshot authentication:

- db.3.gbf: `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0`
- db.4.gbf: `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8`

The reader reuses schema, executable-import metadata, empty File Bytes,
address-map, exact text1/data3/data5 mappings, complete data5 hash and constant
controls. The selected ranges, derived instruction fields, constants and
physical traces are identical in both snapshots. All **529 instructions** in
the nine selected text ranges are decoded, including link-register saves and
restores. No archived instruction is executed. Output contains no raw executable
range, and the only CLI argument is an authenticated snapshot path.

| Start | Bytes | SHA256 |
| --- | ---: | --- |
| 8004784c | 184 | fb82e0b8d8e11f40b382a11097e861b4e3256a0a64406b1af1001f80fb77e0c2 |
| 8003de80 | 552 | 23cb1653c3d6d0dadb77a3e877433ec7a52365e3175e487699c8db5d3dc29faf |
| 80045918 | 688 | bfee155c1b91677ec7193fe0c0304ef01fe5a12dd1613b71c6262c5e74f757d1 |
| 80045ef4 | 212 | 9078a77f10df335efefbc86ef7a833d76170b0f604c29d3b7bbc4c5616c565be |
| 80046158 | 200 | 5a3a6bcc3270be7e7cea64413ca39b1647de0da204100a4473baa7db28799201 |
| 8020b7a8 | 84 | 0e86b49668bd9172bfd1256aa2842a4326032efab48cb6b8df58523a63992e78 |
| 8020bab8 | 68 | 0bedb847db29f7910fad9eb0124a664fee124a375a096925888092f01a159310 |
| 8020bb14 | 68 | 492e3d053ee6336c226ad94d8947492f358b1941ca2292029efea8a6d4d382bb |
| 8020bb78 | 60 | 5628e2b0f92b5abb682884c6b2ca18d2286f3036053e283dbc44550998ee11a4 |

All text spans use root21. The actor spans are in data buffer38 except3de80,
which is in36. The SDK spans are in151. The reader reports exact chain,
data-buffer and physical offsets for each span rather than equating virtual
addresses with physical file offsets.

| Fixed data | Bytes | SHA256 or constant bits |
| --- | ---: | --- |
| 802d0d38, positive-axis lookup indices 4..12 | 9 | 93dc572c2e7e9d5b9c7d93c548da5a04d8206f9ce4ea8de59bfab767d11009ee |
| 802d0d4c, dispatch selector2 only | 4 | 33e98d407c753368a5388cc2e512531ff0a8559fde6bd62a40757cc45fd45ada |
| 80436f78, default normalY | 4 | 3f800000 = 1.0 |
| 80437080, basis squared-length threshold | 4 | 2edbe6fe = 9.999999439624929e-11 |
| 8043ca90, refinement half | 4 | 3f000000 = 0.5 |
| 8043ca94, refinement three | 4 | 40400000 = 3.0 |

The lookup's source base is 802d0d34. Positive axes `a,b` in 1..3 address exactly
indices `3*a+b` in4..12, explaining the nine-byte window without claiming a
table allocation extent. The derived selectors are `[0,0,1,2,0,3,4,5,0]`.
For `(a,b)=(2,1)`, index 7 gives 2. The source pointer base802d0d44 plus8 gives
802d0d4c, whose sole selected word is 80046158. The reader authenticates these
facts before reading the selected constructor. It does not read all dispatch
targets or treat equal-axis entries as valid geometry.

Lookup and dispatch bytes use root199/data205; chain offsets89816/89836,
data offsets7926/7946, physical offsets3383036/3383056. Default1 and threshold
use root263/data264; half/three use root263/data265. The recorded r2 basis
8043ea20 is from `docs/static-recompilation-spike.md:178`, not live-state proof.

These are archived ProgramDB facts, not proof of unchanged original-DOL bytes,
live machine state or gameplay parity. Finite binary32 arithmetic, nearest-even
rounding, admitted storage and GQR0 raw-float loads remain host-domain bounds.

## Secondary effect and point transformation

C source: `research/decomp/ghidra-export/chunk_0005.c:3634–3656`.

4784c computes the selected secondary record at actor+1a94+4*entryIndex. It
loads that record's joint byte at47878, sign-extends it at47884 and selects its
actual matrix. The incoming parent matrix and ordinary current-joint pose
translation go to PSMTXMultVec at4789c. It then:

1. Loads transformed localX478a0 and stores matrix translationX478b0.
2. Loads localY478b4 and stores translationY478b8.
3. Loads localZ478bc and stores translationZ478c0.
4. Loads the actor's original clearance+670 at478c4, calls3de80 at478c8 with
   transformed localXYZ and separate normal-output storage.
5. Loads secondary bytes+1 at478cc and+2 at478d4, sign-extends each at478dc/e0,
   then calls45918 at478e4. These are fresh reads after the terrain query.

No return-value test suppresses orientation after3de80. Its out-of-bounds
normal defaults still feed orientation. A later unsupported orientation must
preserve the earlier three matrix translation writes.

PSMTXMultVec source: `chunk_0064.c:1039–1084`; range8020b7a8–b7fc.
With matrix row `(a,b,c,d)`, source arithmetic is
`add32(fma32(c,Z,mul32(a,X)), fma32(d,1,mul32(b,Y)))`, not a left-to-right
sum of four independently rounded products.

The exact schedule is:

- b7a8 load pointXY; b7ac load matrix[0,1]; b7b0 load pointZ with implicit1;
  b7b4 multiply the first pair; b7b8 load matrix[2,3]; b7bc fused paired add.
- b7c0 load matrix[4,5]; b7c4 sum row0 lanes; b7c8 load matrix[6,7]; b7cc
  multiply row1's first pair; b7d0 **store outputX**.
- b7d4 row1 fused paired add; b7d8 load matrix[8,9]; b7dc sum row1 lanes;
  b7e0 load matrix[10,11]; b7e4 multiply row2's first pair; b7e8 **store outputY**.
- b7ec row2 fused paired add; b7f0 sum row2 lanes; b7f4 **store outputZ**.

PointXYZ are all loaded before the first output store. Matrix reads are not
an eager twelve-float snapshot. All output stores use W=1, so unused second
lanes from the sums do not escape into output.

## Actual normal query3de80

C source: `chunk_0004.c:7262–7343`. Existing query evidence is in
`terrain-query-evidence-2026-11-13.md`; its3fb00 bounds,3f320 ceiling and3fa68
floor-grid helpers are reused, not invented callbacks or assumed empty lists.

At3deb0 the function reads actor byte1db, then sign-extends/tests it at3debc.
A nonzero value has its own contact path, before default-normal stores:

- 3dec4 loads actor+1ec rawX;3decc loads+1f0 rawY.
- 3ded0 stores outX;3ded4 stores outY.
- 3ded8 loads+1f4 rawZ;3dedc stores outZ; return1.

This authenticated contact branch is not an instruction to broaden the current
zero-contact runtime domain. A bounded implementation may refuse before those
contact loads, but must not store defaults before the source branch test.

On the zero-contact path,3dee4 loads authenticated+0 from80436f68 and3deec
loads the new authenticated1 from80436f78. It stores output `(0,1,0)` at
3def0/4/8, then calls3fb00 at3defc. A false bounds result returns0, with all
three defaults already written. No terrain-owner or history reads precede this
early return.

For in-range points:

| PCs | Ordered actions |
| --- | --- |
| 3df10–18 | Load pointX, store localX. |
| 3df1c–28 | Load pointY, load actor+6d0, add32, store localY. |
| 3df2c–30 | Load pointZ, store localZ. |
| 3df34–40 | Load savedGroundPos.y(+30), load previousStepHeight(+6d4), add32, call3f320 with localXYZ. |
| 3df44–54 | Reload savedGroundPos.y; save ceiling result; reload previousStepHeight; load current pos.y(+24); load current stepHeight(+6d0). |
| 3df58–64 | add32(previous pair); load+0; add32(current pair); sub32(previous,current). |
| 3df68–70 | If0<delta, add32(original clearance,delta). |
| 3df74–80 | Reload original pointY; add32(adjusted clearance,pointY); call3fa68 on original point. |
| 3df84–88 | Reload terrain owner, load actual+68 as best height. |

3f320 still reads +24 and +20 grid/list owners separately;3fa68 reads+1c.
This query has no original-clearance>=H flag, no independent min/max registers
and no final H/L fallback selector. The default normal remains unless a
triangle qualifies for a best-height update.

The floor loop tests the exactffffffff sentinel before the body, at3e068–74.
Each body performs these accesses and calculations in order:

1. 3df90 loadv1X;3df94 reload localX;3df98 loadv2X;3df9c loadv1Z.
2. 3dfa0 dx1=sub32(v1X,localX);3dfa4 reload localZ;3dfa8 dx2;
   3dfac loadv2Z;3dfb0 dz1;3dfb4 loadv3X;3dfb8 dz2;
   3dfbc loadv3Z;3dfc0 dx3.
3. 3dfc4 mul32(dz1,dx2);3dfc8 mul32(dx1,dz2);3dfcc dz3;
   3dfd0/4 skip if the first product is less than the second.
4. 3dfd8/dc compare mul32(dz2,dx3) to mul32(dx2,dz3), skip if less.
5. 3dfe8/ec compare mul32(dz3,dx1) to mul32(dx3,dz1), skip if less.

Equality passes. The last two product pairs are not computed after an earlier
rejection. Unlike3d6e4, the localX/localZ loads occur inside each triangle's
body; the source vertex/load schedule is also different.

For an inside triangle:

- 3dff8 loads normalX word into r5;3dffc normalZ into r0;3e000 stores stackX.
- 3e004 loads normalY into r4;3e008 stores stackZ;3e00c reloads floatX;
  3e010 reloads floatZ;3e014 stores stackY.
- 3e018 multiplies X*dx1;3e01c multiplies Z*dz1;3e020 loads v1Y;
  3e024 reloads floatY;3e028 adds the X/Z products;3e02c multiplies Y*v1Y;
  3e030 adds that product;3e034 divides by normalY.

All six operations independently round to binary32; there is no FMA in3de80.
Even an admitted actual normal `(0,1,0)` requires this operation tree and the
actual fields, not a constant-height shortcut.

Acceptance is ordered and strict for the two upper bounds:
limit>height at3e038/3c; ceiling>height at3e040/44; best<=height at3e048/4c/50.
On acceptance,3e054 stores outputX from preserved r5,3e058 updates best,
3e05c stores outputY from r4,3e060 stores outputZ from r0. **No triangle-normal
reread** occurs here. The list pointer advances at3e064. At the final sentinel,
3e078 returns1, including when no triangle qualified. Later equal-height
triangles can replace the prior normal because best<=height includes equality.

## Orientation and selected basis constructor

C source: `chunk_0005.c:2477–2590,2719–2752,2807–2830`.

45918 first loads all nine original basis components into three temporary
column vectors. Matrix indices are `0,4,8,1,5,9,2,6,10`; corresponding load PCs
are45954,45968,45970,45978,45980,45988,45990,45998,459a0. Only after all nine
loads does it call PSVECMag for X at459a8, Y at459b4 and Z at459c0.
The magnitudes are saved through subsequent construction and normalization.

The normal copy begins after the magnitudes: rawX459c4, rawY459cc;
store localX459dc, store localY459e4; rawZ459e8, store localZ459ec.
For positive reference axis1, original matrix columnX is freshly reloaded at
45a10/18/20 into the reference vector. Positive axis arguments skip the two
negative-vector scaling calls. The table lookup is45ab8 with sign extension
45abc;45ac0 calls45ef4.

45ef4 loads the selected pointer at45f20 and calls it at45f30. For selector2,
46158 copies the normal vector into temporary Y and reference into temporary X,
then calls Cross(X,Y,Z) at461b8. It checks the resulting Z length as separate
binary32 operations:

- Zx² at461c4, Zy² at461cc, Zz² at461d4.
- add32(Zx²,Zy²) at461d8; add32(Zz²,previous sum) at461dc.
- 461e0/4 require the result **strictly greater** than80437080.

Failure returns1 before a second cross or any actual matrix basis write.
Success calls Cross(Y,Z,X) at461fc, then returns0. The selected closure must
refuse a failed first attempt rather than pretend45918's fallback was covered.

On success45ef4 normalizes temporary X at45f4c, Y at45f58 and Z at45f64.
All three normalizations complete before the first actual matrix basis write.
The nine stores are column-major:

| PCs | Matrix indices |
| --- | --- |
| 45f70,45f78,45f80 | 0,4,8 |
| 45f88,45f90,45f98 | 1,5,9 |
| 45fa0,45fa8,45fb0 | 2,6,10 |

45918 then calls actual Scale using the three saved original magnitudes at
45b7c, followed by actual Concat(matrix,scale,matrix) at45b8c. Neither call is
an optional mathematical identity. Translation is not cleared by the basis
stores. Source Scale/Concat arithmetic and stores retain their existing
authenticated implementation; do not collapse the entire effect into a
replacement diagonal or copied first-pass matrix.

## Exact paired cross-product sequence

Source: `chunk_0064.c:1406–1437`;8020bb78–bbb4. Let inputs be A and B.

- bb78 load BXY into f1;bb7c load AZ into f2;bb80 load AXY into f0;
  bb84 merge10 f6=(By,Bx);bb88 load BZ into f3.
- bb8c ps_mul f4=f1*f2, producing independently rounded(Bx*Az,By*Az).
- bb90 ps_muls0 f7=f1*f0[0], producing independently rounded(Bx*Ax,By*Ax).
- bb94 ps_msub f5=f0*f3-f4: fused(Ax*Bz-f4[0],Ay*Bz-f4[1]).
- bb98 ps_msub f8=f0*f6-f7, whose second lane is fused(Ay*Bx-f7[1]).
- bb9c merge11 f9=(f5[1],f5[1]);bba0 merge01 f10=(f5[0],f8[1]).
- bba4 stores outputX using W=1. bba8 ps_neg negates both f10 lanes.
  bbac stores outputY/Z using W=0.

Thus X is a fused subtraction from a separately rounded product; Y/Z also
have an explicit final negation. Standard unfused cross-product expressions
can change rounding or signed zeros. For axis-aligned inputs, preserve the
same sequence even when many products are zero.

## Magnitude and normalization: code facts

Sources: `chunk_0064.c:1322–1403`. Half 8043ca90 and three 8043ca94 are exact
authenticated binary32 constants 0.5 and 3.0. Both routines construct squared
norm `s = add32(fma32(z,z,mul32(x,x)), mul32(y,y))` using paired operations.
This is not a binary64 sum and is not the decompiler's unfused expression.

Normalize8020bab8:

| PC | Operation |
| --- | --- |
| bab8,babc | Load half into f0, three into f1. |
| bac0 | psq_l XY into f2, W=0,I=0. |
| bac4 | ps_mul f5=f2*f2. |
| bac8 | psq_l Z into f3, W=1,I=0, implicit second lane1. |
| bacc | ps_madd f4=f3*f3+f5. |
| bad0 | ps_sum0 f4: lane0=f4[0]+f5[1], lane1=f3[1]. |
| bad4 | frsqrte f5,f4. This is an estimate, not exact reciprocal square root. |
| bad8 | fmuls f6=f5*f5. |
| badc | fmuls f0=f5*f0, forming estimate*half. |
| bae0 | fnmsubs f6=-(f6*f4-f1), one fused single rounding and negation. |
| bae4 | fmuls f5=f6*f0. |
| bae8,baec | ps_muls0 originalXY by f5[0], then store XY. |
| baf0,baf4 | ps_muls0 originalZ pair by f5[0], then store Z with W=1. |

There is no zero-norm branch in Normalize. XY output is written before the Z
multiply/store. Original XYZ have already been loaded before either store.

Mag8020bb14:

| PC | Operation |
| --- | --- |
| bb14 | Load half into f4. |
| bb18,bb1c | Load XY into f0 and ps_mul f0=f0*f0. |
| bb20 | Load Z into f1. |
| bb24 | fsubs f2=f4-f4, creating+0. |
| bb28 | ps_madd f1=f1*f1+f0. |
| bb2c | ps_sum0 lane0=f1[0]+f0[1]. |
| bb30,bb34 | fcmpu s,+0; equal returns immediately atbb54. |
| bb38 | frsqrte f0,f1. |
| bb3c | Load three into f3. |
| bb40 | fmuls f2=f0*f0. |
| bb44 | fmuls f0=f0*f4. |
| bb48 | fnmsubs f2=-(f2*f1-f3). |
| bb4c | fmuls f0=f2*f0. |
| bb50 | fmuls f1=f1*f0, multiplying squared norm by refined reciprocal. |

The shared refinement therefore has separate rounded estimate-square and
estimate-half multiplies, a **fused negative multiply-subtract**, and a final
rounded multiply. Magnitude adds one more rounded multiplication by s.
The code spans alone do not establish the estimator's numeric seed.

## Numerical evidence boundary

Do not replace frsqrte with `1 / Math.sqrt(s)`, including at s=1.
`research/tools/static-recomp/ppc_recomp.py:485–491` explicitly refuses that
substitution. The old oracle shim
`research/decomp/oracle-harness/specs/auto-c0020-007.spec.mjs:96–104` uses exact
reciprocal square root with a declared rounding-only comparison, not exact
Gekko evidence. Neither is a replacement for estimator semantics.

The separately researched finite estimator proof is model-backed, not a
hardware execution capture. Its pinned reference is Dolphin commit
`221d396b3acb9e0d1a815cbf7613a9f7032cc14a`:

- [FloatUtils.cpp estimator and exponent scaling, lines 75–139](https://github.com/dolphin-emu/dolphin/blob/221d396b3acb9e0d1a815cbf7613a9f7032cc14a/Source/Core/Common/FloatUtils.cpp#L75-L139),
  blob SHA `312d4a88a217e061a8d5f91061272a417b1d484b`.
- [Expected estimate test, lines 69–103](https://github.com/dolphin-emu/dolphin/blob/221d396b3acb9e0d1a815cbf7613a9f7032cc14a/Source/UnitTests/Common/FloatUtilsTest.cpp#L69-L103),
  paired with [input 1.0 at index 6](https://github.com/dolphin-emu/dolphin/blob/221d396b3acb9e0d1a815cbf7613a9f7032cc14a/Source/UnitTests/Core/PowerPC/TestValues.h#L10-L20).
- [fmuls operand treatment, lines 366–386](https://github.com/dolphin-emu/dolphin/blob/221d396b3acb9e0d1a815cbf7613a9f7032cc14a/Source/Core/Core/PowerPC/Interpreter/Interpreter_FloatingPoint.cpp#L366-L386)
  and [Force25Bit, lines 91–124](https://github.com/dolphin-emu/dolphin/blob/221d396b3acb9e0d1a815cbf7613a9f7032cc14a/Source/Core/Core/PowerPC/Interpreter/Interpreter_FPUtils.h#L91-L124).

The explicit unit test pairs 1.0 with estimate binary64 `3feffe8000000000`,
equal to 16381/16384. The test and estimator agree but are not independent
experimental measurements. The separate investigation checked the finite
arithmetic with independently written Fraction arithmetic and explicit
binary32 rounding, without executing downloaded code.

For one nonzero axis component±m with
`m in {0.5,1,2,4,8}`, s=m² is exact. Using the canonical Dolphin estimator
seed `e=(16381/16384)/m`, the authenticated sequence above produces:

```
a = RN32(e*e)
h = RN32(e*0.5)
c = -RN32(a*s-3)       # fused fnmsubs, c has bits40000600
r = RN32(c*h)          # r=(1-2^-24)/m
Mag = RN32(s*r)        # m*(1-2^-24)
Normalize nonzero axis = +/- (1-2^-24), bits3f7fffff orbf7fffff
```

Positive refinement preserves the input zeros' signs during the final
multiplies. The domain uses finite normal operands/results and nearest-even
rounding; seed operands are exactly binary32, so a 25-bit multiplier-operand
rounding step cannot alter them. It does not grant general vector/estimator
support, nor permission to replace source calls by exact unit identities.

| m | s=m² | Estimate bits, binary64 | Refined reciprocal bits, binary32 | Mag bits, binary32 |
| ---: | ---: | --- | --- | --- |
| 0.5 | 0.25 | 3ffffe8000000000 | 3fffffff | 3effffff |
| 1 | 1 | 3feffe8000000000 | 3f7fffff | 3f7fffff |
| 2 | 4 | 3fdffe8000000000 | 3effffff | 3fffffff |
| 4 | 16 | 3fcffe8000000000 | 3e7fffff | 407fffff |
| 8 | 64 | 3fbffe8000000000 | 3dffffff | 40ffffff |

For m=1, the estimate-square is3f7fe801 and estimate-half is3efff400.
The unrounded final product is `1-9*2^-28`, rounding to3f7fffff. If the later
diagonal rescale has just the surviving product of normalized component and
saved magnitude, its result is `m*(1-2^-23)`, with positive bits3efffffe,
3f7ffffe,3ffffffe,407ffffe,40fffffe respectively. This numerical consequence
does not replace proving the source cross signs, zero signs and Concat tree.

The proof does not cover arbitrary magnitudes, an already normalized
`1-2^-24` input, other rounding modes, denormals, NaNs/infinities or FP status
and exception effects. Dolphin's source files are GPL-2.0-or-later. No Dolphin
implementation or estimate table was copied into this repository; only small
numerical facts and the independent bounded derivation are used. A general
implementation/table import would require a separate licensing decision.

## Reproduction and focused verification

From the repository root:

```sh
PYTHONDONTWRITEBYTECODE=1 python3 research/tools/matching-decomp/test_archived_terrain_orientation_evidence.py
PYTHONDONTWRITEBYTECODE=1 python3 research/tools/matching-decomp/read_archived_terrain_orientation_evidence.py \
 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.3.gbf'
PYTHONDONTWRITEBYTECODE=1 python3 research/tools/matching-decomp/read_archived_terrain_orientation_evidence.py \
 'research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/db.4.gbf'
```

All 20 synthetic tests pass. They check new instruction forms and operand order,
single/fused refinement scheduling, distinct XY/Z stores, paired norm inputs,
integer absolute-value/index operations, fixed range/table admission, root,
width, alignment, bounds and digest rejection, independent selector/target
checks, exact constants, derived-only output, normal stores and authentication
before selected reads (including a forged allowlisted digest). Both archive
reads independently pass and all selected fields/traces agree.

These checks are evidence-reader tests, not runtime, aggregate, original-machine
execution or gameplay tests. This evidence work changed only its new reader,
test and note; it performed no remote operation, source acquisition, rig action,
commit or publication.
## Runtime and independent checks

The runtime extension writes genuine caller correction entries, scans the
actual positive lists, performs the selected secondary correction and copies
the resulting shared matrices to the linked clone. The composite tests then
retain those matrices across a real wait and consume them during replacement
setup and movement. They also check fresh descriptor/count reads, independent
list cursors, byte wrap, partial stores, primary-match refusal and an actual
out-of-bounds normal return whose status the caller intentionally ignores.

Four independent private mutation suites reject all 128 meaningful variants:
32 normal-query, 30 correction-entry, 27 traversal and 39 arithmetic controls.
All baselines pass, with no surviving control, build failure or ambiguous
anchor. Thirteen initially surviving controls exposed regression-test gaps;
the tests were strengthened without changing the runtime. Four other proposed
controls were excluded as observationally equivalent within the admitted
stable-data or finite numerical domain, with the initial outcomes and proofs
preserved. They are not counted as kills.

A separate integer-dyadic reference checks 4,096 actual composite contexts and
8,192 explicit refreshes, including 6,144 genuine height queries and 4,096
secondary normal/orientation passes. Its expectations use BigInt rational
arithmetic with explicit nearest-even binary32 rounding, not runtime arithmetic
helpers. It checks 5,333,780 ordered rounded operations, all five admitted
magnitudes, eight column-sign combinations, four flat-normal signed-zero
combinations, history, masks, repeated refresh and 1,024 retained consumers.
The reference varies signed diagonal bases; it does not claim independent
coverage of every signed-axis permutation or unrestricted estimator inputs.

The baseline translation is `(134,47,448)` and diagonal bits are
`(3ffffffe,3ffffffe,407ffffe)`. A later real setup consumes retained matrix Y47
and produces height `9.449999809265137`. No original game execution, new hardware
capture, full primary IK, arbitrary terrain normal or production activation is
inferred from these checks.
