# Actor world-matrix integration audit, 2026-11-13

## Result

The movement consumer's actor+8f0+j*30 is element [1][3] of the game-owned
matrix array beginning actor+8d4. Its producer is **not** HSD_JObjMakeMatrix.
The next integration should implement the game-owned actor matrix builder,
not expose JObj local translations or renderer matrices as movement evidence.

The first pass was a read-only decompiled-source audit. A subsequently authorized
bounded ProgramDB reader and 15 synthetic tests now authenticate the matrix
primitives, their caller and four constants described below. The source audit
and runtime execution checks are separate evidence. Earlier unaudited limitations
below are narrowed only by the explicit authenticated follow-up section.

## Concrete producer and consumer direction

All paths below are relative to research/decomp/ghidra-export.

- chunk_0005.c:2986–3022: 800465fc calls 46754, then 46bd0(actor,0).
  If actor+661 is zero it calls 46e7c and then 46bd0(actor,1), followed by
  additional conditional postprocessing. 80046698 performs only 46754 and
  46bd0(actor,0), gated by actor+4a0 !=2.
- chunk_0005.c:3221–3257: 80046bd0 constructs actor+8d4 from identity,
  translation actor+20/+24/+28, short rotations +70/+72/+74 (with conditional
  +6b8 yaw correction), and scale +58/+5c/+60. Copies root to +114 and +1aa4,
  then adds actor+6d0 to +1ac0. Recurses via 4679c for mode0 or 46914 for mode1.
- chunk_0005.c:3062–3115: 8004679c traverses signed-byte hierarchy at
  actor+1994+joint*4, computes only joints enabled by actor+1d70, and writes
  actor+8d4+joint*30. Entry byte0 selects continuation; byte1 selects recursive
  branch. The recursive branch gets the incoming parent index, and continuation
  subsequently gets the current joint index. Do not impose conventional
  child/sibling meanings without preserving this exact argument flow.
- chunk_0005.c:3290–3310: 80046dd4 builds quaternion matrix from actor+ed4+j*10,
  overwrites translation with actor+12d4+j*c, concatenates parent, applies short
  Euler at +18d4+j*6, then concatenates scale matrix from +15d4+j*c.
- Joint1 is special: 4679c first applies wrappers in z,x,y order using shorts
  +1d68,+1d64,+1d66, then supplies +1d54 instead of ordinary pose translation.
  46754 sets this vector from +12e0 plus +1dbc unless actor+48a &6, in which
  case it writes only its Y component from FLOAT_80437098.
- chunk_0007.c:308–405, FUN_80056aa8: rendering copies actor+8d4+j*30 **into**
  JObj+44, ORs JObj flags with 0x3800000, then invokes dirty propagation.
  This proves the important data-flow direction is actor matrices to JObjs.
- chunk_0006.c:6983 and chunk_0007.c:1229: actor update routes call 465fc /
  46698. Neither warrants placing matrix generation inside movement4d08c.
  Movement can consume previously generated matrices; preserve caller ordering.

## Smallest arithmetic slices and remaining evidence

FUN_80045838 (chunk_0005.c:2440–2475) explicitly copies its input when Z short
is zero, skips Y if zero and skips X if zero. Otherwise it applies Z,Y,X.
Thus a zero-short-Euler slice can avoid trig **at this function**.

But 4679c's joint 1 wrapper 457d4 (chunk_0005.c:2422–2437) always invokes
PSMTXRotRad and concatenates, even for a zero angle. Skipping these calls would
need separately proven arithmetic equivalence including zero signs. Therefore
zero actor/joint Euler is not by itself a trig-free joint 1 implementation.

46dd4 always calls PSMTXQuat (chunk_0064.c:940–1009), including for an identity
quaternion. The decompiler exposes a reciprocal estimate/refinement and mixed
multiply-add operations; ordinary JS reciprocal is not proven equivalent.
PSMTXConcat (chunk_0064.c:288–388) is paired-single arithmetic whose decompiled
expression nesting is insufficient to establish exact rounding/FMA order.
Neither helper should be reduced to guessed identity or generic host math.

Recommended next fixed instruction audit targets:

1. 80046bd0..80046d00 and 80045838..80045918: root control flow and zero-short
   bypass, plus 8004679c..80046914 and 80046dd4..80046e7c for joint inputs/order.
2. 8020aefc Identity, 8020af28 Copy,
   8020af5c Concat through 8020b028, 8020b4ac TransApply,
   8020b4f8 Scale and 8020b578 Quat through 8020b61c.
3. Exact scalar/table operands including 8043ca68/6c and 80435ca0/a4. Their
   apparent values in decompiled expressions are not newly verified here.
4. For joint 1, 800457d4 and 8020b238 RotRad and its zero-angle
   sin/cos path, or an explicit supported path that truly avoids joint 1.

A root-only 46bd0 slice with zero effective actor shorts and no enabled
recursive joints is the smallest genuine matrix producer. It will **not**
solve normal movement, which unconditionally reads joint 1 Y at actor+920.
An honest intermediate owner can retain root generation and refuse at the
first unsupported joint operation without claiming live movement support.
A meaningful movement slice needs joint 1 special translation/rotations and
all descriptor/list-selected joints, with source-compatible matrix primitives.

## HSD algorithm, separately useful but not the actor movement producer

chunk_0071.c:3431–3580, HSD_JObjMakeMatrix:

- Ensure dirty, non-user-matrix parent through SetupMatrixSub first.
- Flags&8 clear: allocate scale accumulator +74 if absent; copy local scale
  +2c/+30/+34 if parent accumulator absent, else componentwise multiply it.
- Flags&8 set: inherit parent scale accumulator by copy, or free/clear own
  accumulator when no parent accumulator exists.
- Choose MtxSRT or MtxSRTQuat using flag0x20000. Pass **parent** scale
  accumulator (not newly computed own accumulator) as the compensation input.
- Build at +44, then concatenate parent+44 on the left when a parent exists.
- An AObj+18 linked joint overrides translation through PSMTXMultVec after
  ensuring that linked joint's matrix. This cannot be silently omitted.

HSD_MtxSRT at chunk_0071.c:10834–10960 always evaluates sin/cos on all three
Euler components. Its parent-scale compensation is not simple componentwise
SRT: each parent component denominator gets +/- FLOAT_8043d410 based on its
comparison to FLOAT_8043d3d0; cross-axis scale factors use those reciprocals.
Exact constants, FMA order, trig zero behavior and signed zeros remain unaudited.

SetupMatrix_ (5542–5572) invokes SetupMatrixSub only if flag0x40 is set and
0x800000 clear. SetupMatrixSub (7282–7390) calls class method+40, clears0x40,
then handles user matrix return, IK flag0x600000 cases and RObj constraints.
A bounded ordinary path must reject the unsupported constraint/IK cases.
Dirty propagation (7392 onward) sets0x40, skips descent for0x1000, skips
children with0x1000000 and avoids repeating a non-user-matrix already-dirty
subtree. These HSD flags do not replace actor+1d70's separate update mask.

## Limits

Existing actor-movement-followup.ts accepts explicitly owned Y arrays, useful
as a consumer seam but not proof of their producer. Keep fixture matrices
labeled as fixtures until the above actor-owned producer and timing exist.
No renderer/host Math.sin/Math.cos fallback, archived-byte exactness, retail
replay, build or full gameplay result is claimed by this audit.

## Authenticated numeric follow-up

`read_archived_world_matrix_evidence.py` and its 15 synthetic-only tests use the
existing `read_archived_constants.inspect` authentication, exact text mapping,
exact data5 mapping and exact data4/subblock mapping before reading fixed targets.
Both existing db.3.gbf and db.4.gbf pass and yield identical ranges/constants.
Full snapshot provenance/caveats remain those in archived-program-constants.
The reader emits decoded facts, not raw ranges; it has no arbitrary-address CLI.

Fixed authenticated spans:

| Start | Length | SHA256 |
| --- | ---: | --- |
| 8020af5c | 204 | 76d05fd3f0428b0ee7d051458a11fcaddd6de21fb68961b8a19990beefa68637 |
| 8020b578 | 164 | 712544e159855114729c096e3d362ac93149ebd2f3776e517395ba37c6d1970a |

Constants: 8043ca68=3f800000 (1), 8043ca6c=00000000 (+0),
80435ca0=00000000 (+0), 80435ca4=3f800000 (1).
The last two are in MAIN_.data4 start 804335a0, length 11040, block/subblock 6,
initialized BUFFER chain 262. The first two retain the existing data5 chain 263.

### Exact PSMTXConcat arithmetic and store order

For row r and column c, A is first matrix, B second:

1. t = round32(B[0,c] * A[r,0]) by ps_muls0.
2. t = fma32(B[1,c], A[r,1], t) by ps_madds1.
3. t = fma32(B[2,c], A[r,2], t) by ps_madds0.
4. For c=2, t = fma32(+0, A[r,3], t). For c=3,
   t = fma32(1, A[r,3], t). These are ps_madds1, not removable
   mathematical no-ops when signed zero/exceptional values matter.

Rows 0/1 start in f12/f13 and f14/f15; row 2 uses f2/f0.
All 24 A/B matrix elements are loaded before the first store; the final A
pair is loaded at8020afc4. The (+0,1) constant pair is loaded at8020af90.
Output/input aliasing is therefore supported for either complete matrix.

Actual paired-store order is:

- 8020afd8: indices 0,1
- 8020afe8: indices 4,5
- 8020aff0: indices 2,3
- 8020b004: indices 6,7
- 8020b00c: indices 8,9
- 8020b018: indices 10,11

Computations interleave before these stores. A host bounded implementation that
refuses overflow during its chosen pair calculation has a host-admission prefix,
not evidence of original exceptional-value behavior. Finite inputs alone do not
ensure finite intermediates. Also retain rounding-mode, denormal and GQR caveats;
this audit establishes operations and operands, not captured machine state.

### Identity quaternion output, including negative zero

For exactly quaternion(+0,+0,+0,1), the PSMTXQuat instruction path yields:

```
[ 1, +0, +0, +0,
 +0,  1, -0, +0,
 -0, +0,  1, +0 ]
```

This follows the instructions, not a skipped quaternion routine:

- 8020b584 computes f0=1-1 (+0); 8020b588 computes f2=1+1 (2).
- Paired squares/additions compute norm 1; 8020b5a4 executes fres, followed by
  negative fused subtraction at b5ac, multiply at b5b4 and fmuls at b5bc.
  The resulting normalization factor is positive finite. Its exact bits are
  unnecessary for this one input: every affected non-diagonal output multiplies
  zero, while diagonal negative fused subtracts return 1.
- At b5e4, f9 is (+0,+0). At b5ec, ps_nmsub f10,f10,f2,f9 negates
  exact zero differences, yielding (-0,-0). b5fc multiplies by the positive
  normalization factor, preserving both minus signs.
- b608 ps_merge10 f7,f10,f0 gives (-0,+0), stored to indices 6,7 at b610.
- b60c ps_merge01 f11,f10,f9 gives (-0,+0), stored to indices 8,9 at b614.
- Diagonal 1 values are produced by ps_nmsub at b5cc/b5d0. Other stores and
  merges preserve the positive-zero results above.

This identity specialization is not a general reciprocal-estimate emulator and
must reject quaternion -0 components or any value other than this exact domain
unless separately justified. Assumes normal floating execution semantics, not
unverified FPSCR modes. No live retail identity-quaternion capture is claimed.

### Recommended bounded integration boundary

A useful next runtime slice is actual 80046dd4 with an explicitly supplied,
source-owned parent matrix; actual captured bank 0 pose; source scales and exact
zero short Euler; and an owned 3x4 destination. Apply identity-quaternion matrix,
overwrite its translation from captured pose, source Concat, actual zero-short
Euler copy, source Scale matrix and source Concat. Movement then reads Y at
matrix index 7 through its existing source-ordered consumer.

This boundary explicitly does not implement 4679c traversal, joint 1 wrapper,
root generation, caller timing, IK or rendering. Retain parent input and helper
refresh as explicit operations; do not silently regenerate matrices inside
movement or replace older matrices during pose setup. An actual captured pose
can drive the helper without claiming a complete actor-world producer.

### Copy, Scale and 46dd4 caller extension

The same reader now checks three additional fixed spans in both snapshots:

| Start | Length | SHA256 |
| --- | ---: | --- |
| 8020af28 | 52 | 16a1071dcfbc5fc2775a7b929ee6903ac5ab4d946af9119d57f5c8b823f41df1 |
| 8020b4f8 | 40 | e0973dcf5701b4b975a0a3d358a66e9af66353276f25f530500ab1ca52cd3de6 |
| 80046dd4 | 168 | 9522644852d3cf46ccd31a6489318c9c7378d535ac93922ca9785916d495eca5 |

Copy alternates a paired load and paired store, row-major pairs 0/1,2/3,4/5,
6/7,8/9,10/11. It does NOT snapshot all 12 inputs before writing. The first
load/store are af28/af2c; final load/store are af50/af54. An aliased self-copy
can use pairwise validation to retain this boundary for bounded-host refusals.

46dd4 reads/stores translation X at 46e04/46e14, Y at 46e18/46e1c, and Z at
46e20/46e24. The first Concat is called at 46e28. Correction signed shorts load
X,Y,Z at 46e2c,46e34,46e3c before 45838 call46e40. Scale arguments load X,Y,Z
into f1,f2,f3 at 46e44,46e4c,46e50 before Scale call46e54. Second Concat call
is 46e64. These call/load facts are included in reader output.

Scale loads authenticated +0 at b4f8 and stores in this exact order:
X[0] at b4fc; zero pair[1,2] at b500; zero pair[3,4] at b504;
Y[5] at b508; zero pair[6,7] at b50c; zero pair[8,9] at b510;
Z[10] at b514; zero[11] at b518. An internal unobservable host scale array with
already admitted X,Y,Z need not expose each temporary store as a callback.

Final checks: 15 synthetic-only tests pass; all five ranges/four constants
match across authenticated db.3.gbf/db.4.gbf. These are evidence-reader results, distinct from the runtime checks.

### Runtime review

Read-only review of actor-joint-matrix.ts and the movement shared-matrix provider
found the finite admitted arithmetic agrees with the evidence: both Concats use
the audited multiply/FMA order, source zero signs are explicit, parent/output
aliasing snapshots before Concat writes, scale arguments read X,Y,Z and output
records remain stable. Copy was corrected to pairwise reads/stores following
this audit. Movement resolves only selected matrix element 7 at its existing read
sites, checks stable owner record identity, and does not refresh matrices.

The integration remains an explicit 46dd4 callee and actual owned destination,
not a complete traversal/root/correction-wrapper pipeline. Source finite-overflow
behavior and instruction-level exception prefix are not claimed. Runtime-focused
execution checks are reported separately in the integration plan.

### Final execution-state and integrated-test review

Every paired matrix load/store in the five authenticated spans encodes I=0,
selecting GQR0. Interpreting these as raw binary32 array accesses assumes both
GQR0 load and store type fields are 0 (floating point, no integer quantization).
Scale fields do not introduce scaling for that floating type. This reader has
not authenticated a GQR0 initializer, later writes or live invariance. GQR0 raw
float operation is an explicit host-domain precondition alongside RN=00/NI=0;
it is not established merely because the decompiler emits float pointers.
W=0 accesses two values; W=1 accesses a single memory value (loads also supply
the paired implicit lane). Reader output retains each W/I field.

The 46dd4 correction load order is specifically XYZ: `lha r5,0(r29)` at
80046e2c, `lha r6,2(r29)` at 46e34, `lha r7,4(r29)` at 46e3c, then the 45838
call at 46e40. The host zero-correction validation uses that order. Rejection of
an unsupported nonzero component is host admission, not a claim that the source
would skip the remaining argument loads or reject the angle.

Final read-only review of matrixHydratedControlFixture and its integrated tests
confirms explicit 46dd4 scope in the test description. Tests exercise real bank 0
captured pose, supplied parent, separate scale, retained matrices across packed
pose changes and setup replacement, later explicit refresh, bank 1 independence
and first-Concat retention on correction refusal. Shared-matrix movement tests
verify joint 1-before-root reads, captured owner method/receiver, actual mutable
record reads, early-gate avoidance and caught reentry refusal. No new review
finding; execution checks were run separately from this read-only review.

### Explicit-estimate quaternion matrix lane (2026-11-18)

The offline `actor-joint-matrix` owner now admits non-identity finite
quaternions only when its caller supplies the `fres` result for the reached
positive normal squared norm. It follows the archived `8020b578..8020b61c`
paired-single operation schedule and retains the existing identity-only refusal
when no estimate is supplied. The implementation does not substitute host
`1 / norm` for the processor estimate. The estimate is explicit, finite and
positive; GQR0 floating loads and RN00/NI0 remain assumptions. Intermediate
non-finite arithmetic refuses under the host boundary. Synthetic dyadic tests
exercise a quarter turn, a four-component rotation, the estimate input, zero
norm, invalid estimate, and caught reentry. They are not Dolphin traces or
physical-hardware verification, and this offline owner is not connected to the
playable renderer or a complete source pose bank.

An isolated Dolphin JIT64 run of the original GG4E battle on 2026-11-18
captured 18 calls at `8020b578`, the `fres` result at `8020b5a8`, and matrix
stores at `8020b618`. Three non-identity captures with both observed estimates
are now regression cases. With their observed estimates explicitly supplied,
the offline implementation's nonzero matrix values after identity-parent
concatenation match all 27 captured nonzero values bit-for-bit. This is bounded
emulator evidence for the captured inputs, not an exhaustive estimate model,
physical-console proof, source pose-bank integration, or a playable visual
comparison. The separate emulator was stopped; the pre-existing instance was
not touched.

### Controlled `fres` sweep (2026-11-18)

A second isolated Dolphin JIT64 run used the same original battle savestate.
At each of 65 calls to `8020b578`, the quaternion was temporarily changed to
`(1 + i/64, 0, 0, 0)` for i=0..64, and restored before returning to the game.
At `8020b5a8`, `f3` and `f11` yielded the norm `(1+i/64)^2` and the estimate
below, respectively. The norm values are exactly representable in float32.
The test instance was stopped afterward; the pre-existing instance was not
changed. These are Dolphin observations, not independent hardware captures.

```text
0.9998779296875 0.96938157081604 0.9402303695678711 0.9123992919921875 0.8857917785644531
0.8603301048278809 0.8359642028808594 0.8125839233398438 0.7901763916015625 0.768665075302124
0.7479887008666992 0.7281584739685059 0.7091255187988281 0.6908767223358154 0.6732778549194336
0.6563115119934082 0.639984130859375 0.6243031024932861 0.6091957092285156 0.594597339630127
0.5805854797363281 0.5669605731964111 0.5537919998168945 0.5412299633026123 0.528961181640625
0.5170607566833496 0.5057468414306641 0.4946712851524353 0.48391056060791016 0.47360044717788696
0.4636037349700928 0.4538688659667969 0.44439697265625 0.43534356355667114 0.42651891708374023
0.4179399013519287 0.409576416015625 0.40152549743652344 0.39371705055236816 0.38611119985580444
0.3787040710449219 0.37150895595550537 0.36454153060913086 0.35777270793914795 0.3511781692504883
0.34477347135543823 0.33852362632751465 0.3324357271194458 0.326507568359375 0.3207676410675049
0.31519055366516113 0.3097265362739563 0.3044166564941406 0.29924023151397705 0.29418110847473145
0.2892792820930481 0.2844429016113281 0.2798030972480774 0.27517199516296387 0.2707764506340027
0.26636314392089844 0.26217782497406006 0.2579631805419922 0.25398218631744385 0.249969482421875
```

This sparse sweep is not enough to infer every interpolation interval or to
replace the explicit estimate dependency. At norm 1 the observed estimate is
`0.9998779296875`, not the result of host division. No table or implementation
was copied from Dolphin source.

### Interval grid

A further isolated Dolphin JIT64 run sampled four interior values in each of
32 equal intervals spanning norms `[1,2)`. For each point, a float32 quaternion
`(sqrt(target),0,0,0)` was temporarily injected and restored on return. The
actual rounded norm and resulting `fres` estimate, as IEEE-754 binary32 hex
pairs, are in `fres-dolphin-grid-2026-11-18.json`. The target fractions within
intervals were 0.1, 0.35, 0.65 and 0.9; the file records actual reached norms,
not those ideal targets. All 128 samples were captured; the separate test
instance was stopped and the existing Dolphin instance was left untouched.
These points alone do not establish interpolation boundaries or behavior outside
this interval, and no estimate implementation is inferred from them yet.

A separate 128-point fine sweep, in `fres-dolphin-fine-2026-11-18.json`,
sampled actual rounded norms near 1 after temporary quaternion injection and
restoration in another isolated Dolphin JIT64 run. Independently fitting the
interval-grid samples produced a 32-segment candidate with a step of 256 float32 bit patterns.
The opt-in `sourceReciprocalEstimateBounded` admits only float32 `[1,4]`; it
matches all 128 grid, 128 fine and 65 earlier sweep observations. The 65-point
sweep provides an independent check of the candidate across the second exponent.
These finite samples do not prove unobserved boundaries, physical hardware,
exceptional values or `[0.5,1)`, and the candidate is not enabled in gameplay.

A separate isolated Dolphin run sampled four interior points in each of 32
intervals for norms in `(0.5,1)`; actual float32 norm/estimate bit pairs are in
`fres-dolphin-half-2026-11-18.json`. All 128 agree with the candidate's
exponent scaling. The candidate now admits `(0.5,4]`; exactly 0.5 remains
excluded because this sweep did not measure that endpoint. Using the candidate
instead of injected observed estimates also matches the 27 nonzero output
values in the three captured rotations, including the two norms below 1.
This is still a bounded experimental emulator model, not full hardware or
playable-game parity. The isolated instance was stopped and the unrelated
existing emulator was left untouched.

A separate isolated Dolphin run sampled four points immediately around each
of the 32 normalized interval boundaries. Actual rounded norm and estimate
bits are saved in `fres-dolphin-edge-2026-11-18.json`. All 128 match the
bounded candidate, including values straddling 1. Inputs were restored, the
isolated instance stopped, and the existing Dolphin process left untouched.
This is still finite emulator evidence, not physical-console validation.
