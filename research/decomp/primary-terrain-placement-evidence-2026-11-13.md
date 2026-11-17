# Primary terrain two-bone placement: archived evidence

Date: 2026-11-13. This is fixed, authenticated local ProgramDB evidence for
`80047368`, its missing vector helpers, and the selected bend-axis lookup.
It is not original-DOL verification, an original execution capture, a generic
inverse-kinematics implementation, or proof of gameplay parity.

## Reader and admission

New files:

- `research/tools/matching-decomp/read_archived_primary_terrain_evidence.py`
- `research/tools/matching-decomp/test_archived_primary_terrain_evidence.py`

The reader accepts only a snapshot path. It has no arbitrary-address argument,
raw executable-range output, instruction execution, network access or external
dependencies. It emits hashes, typed constants, decoded operands in source
order and physical provenance. Unknown selected floating forms fail closed;
unselected instructions are omitted, not inferred. In the primary span, only
the integer multi-register prologue/epilogue instructions are omitted.

Both local files under
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`
were read successfully, with identical selected evidence:

| Snapshot | Complete SHA-256 |
| --- | --- |
| `db.3.gbf` | `7b50dd2d2e17b4bfcc89a64cde27010247d0cbf0f48bd5c059f50275f40458d0` |
| `db.4.gbf` | `1f86813d91ea8e2c4564f96622ec42555e1dba2c78aa81ad654e892140d019f8` |

Before selected reads, `read_archived_constants.inspect` verifies the digest
against the supplied bytes and the complete-snapshot allowlist, schemas,
`boot.dol` program name, Gekko/Broadway language, Ghidra 12.1.2 metadata,
address map, empty File Bytes table, memory block bounds and independent
constant controls. The complete data5 digest is
`989c794b17fc95de6e57810f5c89db23d585c85a15faafc994d9a5bd9a0e61b4`.

The executable metadata digest is
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
This is import metadata, not proof that bytes still match the original DOL.

`command.mappings` additionally admits the exact text1/data3/data5 block and
subblock mappings and rejects all-block overlaps. This reader admits exactly
one data4 block with key6, encoded start `20000000004335a0`, resolved start
`804335a0`, length11040, segment0, and subblock
`[parent6,type2,length11040,offset0,root262,sourceOffset0]`. The data5 tuple is
checked exactly: start `80436a20`, end `8043d500`, block/subblock7,
length27360, root263. No bend table read occurs before those checks.

## Fixed evidence windows

| Subject | Start | Width | SHA-256 |
| --- | --- | ---: | --- |
| Primary placement | `80047368` | 1252 | `64365eb011b470b5c2abddcc606e4fe28fe8ac37b6f9f28be76af21bbde278e2` |
| PSVECSubtract | `8020ba78` | 36 | `5997a5a32c7df8eb2a03901039345f35a84f00b017545800218ef21bdbfaf81a` |
| PSVECSquareDistance | `8020bc88` | 40 | `a5dc9dd558d92f78fdebc97036e9c4e9b250a0f57eed1b449a8515f13c029e74` |
| Selected bend indices1..3 | `804336a9` | 3 | `3608bca1e44ea6c4d268eb6db02260269892c0b42b86bbf1e77a6fa16c3c9282` |

The primary span ends at `8004784c`, the next function. SDK boundaries are
corroborated by `ghidra-export/chunk_0064.c`; primary source is in
`ghidra-export/chunk_0005.c:3487`. The C export helps identify functions but
does not override actual instruction operands or precision.

The reader reuses, without editing or widening, the existing fixed
`PSMTXRotTrig` span in `read_archived_actor_traversal_evidence.py`:
start `8020b2a8`, width176, digest
`832e4fbd68ca5d25b4345248b3eadb3421dcade987a190829e0617a61b19a8d7`.
It also reuses `804370a4` from `read_archived_terrain_matrix_evidence.py`.
Existing readers already cover traversal46914, orientation45918, MultVec,
Mag and Concat; they are not added as new domains here.

Physical traces, identical in both snapshots:

| Window | Root/data buffer | Chain/data offset | Physical offset |
| --- | --- | --- | ---: |
| Primary | 21 / 38 | 269704 / 7656 | 646638 |
| Subtract | 21 / 151 | 2122904 / 10142 | 2500516 |
| SquareDistance | 21 / 151 | 2123432 / 10670 | 2501044 |
| Bend indices1..3 | 262 / 262 | 265 / 265 | 4309267 |

## Constants: types established by loads

The two refinement constants are eight-byte binary64 values. Treating them
as binary32 values or rounding every intermediate to binary32 changes the
source algorithm. Six constants are new to this reader; factor2 is reused.

| Address | Load/type | Width | Bits | Value | Witness PC |
| --- | --- | ---: | --- | --- | --- |
| `804370a0` | lfs / f32 | 4 | `00000000` | +0 | `8004743c` |
| `804370a4` | lfs / f32 | 4 | `40000000` | 2 | `80047588` |
| `804370c0` | lfd / f64 | 8 | `3fe0000000000000` | 0.5 | `8004744c` |
| `804370c8` | lfd / f64 | 8 | `4008000000000000` | 3 | `80047450` |
| `804370d0` | lfs / f32 | 4 | `3f7fbe77` | 0.9990000128746033 | `80047570` |
| `804370d4` | lfs / f32 | 4 | `3f800000` | +1 | `80047590` |
| `804370d8` | lfs / f32 | 4 | `bf800000` | -1 | `800475d0` |

All six new targets use root263/data264. Their chain/data offsets are,
respectively, 1664,1696,1704,1712,1716,1720; physical offsets are
4343430,4343462,4343470,4343478,4343482,4343486. These offsets are provenance,
not a raw byte export.

The documented register bases are r2=`8043ea20` and r13=`8043b5a0`, from
`docs/static-recompilation-spike.md:178-179`. They are recorded documentation,
not newly captured startup state. The bend lookup displacement is -32504,
which resolves r13 to `804336a8`.

## Numerical operation order

Notation below describes instruction order under the explicit execution
domain RN=nearest-even, normal supported values and expected GQR0 float
configuration. It does not establish live FPSCR/GQR or the hardware estimate.
`mul32`, `add32`, `sub32`, `div32` mean the respective single instructions;
`mul64` is `fmul`; `fnmsub64(x,q,three)` is the fused result
`-(x*q-three)`, not a separately rounded multiplication followed by subtract.

### SquareDistance and Subtract

SquareDistance `8020bc88..8020bcac`:

1. Load A.yz and B.yz, subtract both lanes into f2.
2. Load A.xy and B.xy. Square both yz lanes of f2 with `ps_mul`.
3. Subtract xy into f0. `ps_madd f1,f0,f0,f2` computes both lanes:
   `[fma32(dx,dx,mul32(dy,dy)), fma32(dy,dy,mul32(dz,dz))]`.
4. `ps_sum0 f1,f1,f2,f2` produces scalar lane0
   `add32(fma32(dx,dx,mul32(dy,dy)),mul32(dz,dz))`.

The unused paired result is still computed. This is not the decompiler's
binary64 sum-of-squares, and it is not interchangeable with a different
association of the other SDK vector routines.

Subtract `8020ba78..8020ba98` loads both xy pairs, subtracts, stores the xy
pair, and only then loads/subtracts/stores z with W=1. Every paired load and
store uses I=0. Preserve that memory order instead of preloading all inputs
when supporting aliases.

### Primary square-root refinement

For a positive squared length x, first `frsqrte` obtains e. Three binary64
Newton stages follow. Each stage computes in this order:

1. q=`mul64(e,e)`;
2. h=`mul64(0.5,e)`;
3. k=`fnmsub64(x,q,3)`;
4. e=`mul64(h,k)`.

After stage3, compute `mul64(x,e)`, then `frsp`, then `stfs` and `lfs`.
There is no single-precision rounding inside the three stages. The initial
estimate is not replaced with mathematical `1/sqrt(x)` by this evidence.

For the first length, estimate PC=`80047448`; stage starts are
`80047454`, `80047464`, `80047474`; final x multiply=`80047484`,
single round=`80047488`, store/reload=`8004748c/490`. The first two stages
write e to f2; the third product and final multiplication use f0. The second
length has the same operation tree at `800474b4..800474fc`.

Every sine square-root branch uses the same double-refinement tree after a
strict positive comparison. Estimate PCs are `80047628`, `8004768c`,
`80047708`, `8004776c`. A zero complement skips the estimate and all stages.

### Cap, cosine operands and clamps

After SDK Mag, `8004756c` adds the two lengths a,b as binary32, and `80047574`
multiplies that sum by the authenticated cap. A strict ordered less-than
comparison replaces d only if cap<d. There is no minimum-reach distance
clamp in this code.

Cosine calculation preserves these source sites and reuses the squares:

| PC | Operation |
| --- | --- |
| `80047584` | d2=mul32(d,d) |
| `8004758c` | a2=mul32(a,a) |
| `80047594` | b2=mul32(b,b) |
| `80047598` | twoD=mul32(2,d) |
| `8004759c` | sumDA=add32(d2,a2) |
| `800475a0` | sumAB=add32(a2,b2) |
| `800475a4` | twoA=mul32(2,a) |
| `800475a8` | numA=sub32(sumDA,b2) |
| `800475ac` | denA=mul32(twoD,a) |
| `800475b0` | numB=sub32(sumAB,d2) |
| `800475b4` | denB=mul32(twoA,b) |
| `800475b8` | cosA=div32(numA,denA) |
| `800475bc` | negNumB=fneg(numB) |
| `800475c0` | ordered comparison of cosA with +1 |
| `800475c4` | cosB=div32(negNumB,denB) |

Each finite cosine clamps to [-1,+1]. At `475c8/475ec`, BO=4/BI=1 tests
the ordered greater-than flag; at `475d8/475fc`, BO=4/BI=0 tests ordered
less-than. Preserve these source comparisons rather than treating arbitrary
nonfinite values as an admitted generic `min/max` domain.

The sine complement is `fnmsubs`, a fused single negative multiply-subtract:
`-(cos*cos-1)`. The two negative-bend sites are `4761c/47680`; positive-bend
sites are `476fc/47760`. At cosine +/-1, its selected nearest-even result is
negative zero, not a synthesized positive-zero `sqrt` result. The following
ordered comparison skips the estimate when the complement is not positive.

## Signed bend and RotTrig

At `80047608`, descriptor+0f is loaded and sign-extended with Rc=1. A
negative bend takes the negative branch. This branch later reloads the byte
at `476d8`, sign-extends it, computes base-minus-signed-value with `subf`,
then loads the axis byte. The nonnegative branch reloads at `477b8`,
sign-extends and uses `lbzx base+signed-value`. The result is sign-extended
again at `477cc` before passing to RotTrig.

Only absolute indices1..3 are admitted by this lookup evidence. The three
signed-byte values at `804336a9..ab` are 120,121,122, or x,y,z. Index zero,
larger magnitudes and a claimed allocation extent remain excluded.

For negative bend, first sine is unchanged and second sine is negated
(`476e0`). For nonnegative bend, first sine is negated (`47758`) and second
sine is unchanged (`477bc`). The two later descriptor reloads are real memory
accesses; caching the initial sign-test byte is not the source read order.

The reused RotTrig instructions settle its parameter identity:
`8020b2a8` rounds input f1 into f5 (s), `8020b2ac` rounds input f2 into f4
(c), and `8020b2bc` computes paired -s. The actual merges/stores give:

- X: `[1,0,0,0; 0,c,-s,0; 0,s,c,0]`.
- Y: `[c,0,s,0; 0,1,0,0; -s,0,c,0]`.
- Z: `[c,-s,0,0; s,c,0,0; 0,0,1,0]`.

The C export's Y repeated-sine and Z repeated-cosine assignments are
misleading paired-single decompilation, not source behavior. Actual store
order, in destination byte offsets:

- X: 0(W=1),4(pair),12(pair),28(pair),44(W=1),36(pair),20(pair).
- Y: 24(pair),0(pair),40(pair),16(pair),8(pair),32(pair).
- Z: 8(pair),24(pair),32(pair),16(pair),0(pair),40(pair).

Zero signs survive the sine negations and paired merges. Do not erase them
by constructing an abstract identity or a conventional matrix whose zero
signs do not follow these instructions.

## Placement memory and call order

1. Select the current matrix from signed descriptor+0c minus2, with stride
   0x30 at actor+0x8d4. The physically adjacent output matrix pointer is
   current+0x30, established at `800473d4`.
2. Copy input pose0..2 to local storage. Copy input pose3..5 at
   `473d8/473dc/473e0`, before any placement matrix writes. Read translations
   of three consecutive current matrices into local vectors before the
   first SquareDistance call at `47438`.
3. Compute the two lengths. Run MultVec in-place on local pose0..2 at
   `4751c`. Store current matrix XYZ translation at `47530/47538/47540`.
4. Subtract target-minus-local at `47544`. Read and sign-extend descriptor
   axes+0d/+0e after those stores. Call orientation45918 at `47560`, then
   Mag at `47568`; compute cap, cosines, clamps and signed sines.
5. First RotTrig at `477d8` uses f1=sineA/f2=cosineA. First Concat at
   `477e8` aliases current as left input and destination.
6. Second RotTrig at `477fc` uses saved f31=sineB/f30=cosineB. Reload the
   previously copied child pose at `47800/47808/47810`; store those values
   into scratch translation at `47818/4781c/47820`.
7. Second Concat at `47824` writes current+0x30. This is physical adjacency,
   not an independently topology-selected child. Caller traversal must
   admit the corresponding special topology separately.

## Bounded candidate and verification limits

The proposed retained positive lengths2 and0.5, with exact target delta+Y1,
lie inside the minimum reach |2-0.5|. Their unclamped cosine signs put cosA
above+1 and cosB below-1; the clamp therefore selects +1/-1 and both fused
sine complements are zero. This gives a meaningful folded two-matrix
placement domain without exercising nonzero sine estimation. It does not
make the endpoint reach target+Y1, and it does not establish general bending.

This reader verifies instructions, constants and branch/operand identity.
The numeric implementation must separately prove its admitted estimate
seeds, binary64 fused equivalence where used, single rounding, signed-zero
behavior, aliases and special caller topology. No generic `Math.sqrt`,
estimated epsilon identity shortcut, unchecked bend index or general
original-runtime claim follows from this evidence.

Focused validation run:

`python research/tools/matching-decomp/test_archived_primary_terrain_evidence.py -v`

Result: **23 tests passed**, including both actual local snapshot integration
checks (not skipped). Both snapshots give 311 primary,9 Subtract and10
SquareDistance instruction facts. The tests cover exact allowlists, root and
mapping rejection, widths/types/digests, authentication-before-read,
binary64 fused operands, source operation/load/store order, signed lookup,
zero-sine branch guard and reused RotTrig parameter identity. They do not
execute archived instructions. No aggregate runtime checks were run for
this evidence-only change.
