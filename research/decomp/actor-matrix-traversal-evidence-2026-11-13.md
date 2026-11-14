# Bounded actor-matrix traversal evidence, 2026-11-13

## Result and boundary

The existing local authenticated ProgramDB snapshots support a bounded actual
`80046698 -> 46754 -> 46bd0(mode0) -> 4679c -> 46dd4` implementation. This includes
joint 1's three mandatory `457d4` wrappers, provided every admitted wrapper short
is zero, effective root/correction shorts are zero, and every enabled joint's
quaternion is exactly the previously audited `(+0,+0,+0,1)`.

Zero wrappers are **not** skipped mathematical identities. The authenticated
zero sin/cos path produces axis matrices containing negative zeros; each wrapper
still concatenates its input with its rotation matrix. This closes the joint-1
zero-angle arithmetic gap identified in `jobj-world-matrix-integration-2026-11-13.md`.

This is the explicit `46698` caller, not a replacement for normal `465fc`, whose
additional mode1/refresh/postprocessing calls remain distinct. Captured pose,
actor fields, hierarchy, enabled mask and matrices must remain explicitly owned.
No renderer/JObj state is substituted for the game-owned matrix producer.

## Authentication and reproducibility

New reader: `research/tools/matching-decomp/read_archived_actor_traversal_evidence.py`.
It reuses the existing full snapshot SHA allowlist, ProgramDB metadata/schema,
data5 digest and address-map checks, and exact MAIN_.text1/data5 mappings before
reading the fixed targets. No arbitrary-address CLI, raw-range output, network,
Ghidra execution, original-asset acquisition or instruction execution is added.

Both existing `db.3.gbf` and `db.4.gbf` under
`research/decomp/GotchaForce.rep.before_force_create/idata/00/~00000000.db/`
pass. All 16 spans, seven constants, decoded facts and physical traces match.

| Start | Bytes | SHA256 |
| --- | ---: | --- |
| 800457d4 | 100 | 5834ba9c6bf11389b74fe25a13eaaf04a90d4aa5e6ba376d7a0ea3004613a2e5 |
| 80045838 | 224 | 90bfcf864297a8889d20a2489af7de1e3441f2b62db6983b4bc0d1f6c904c595 |
| 80046698 | 68 | 61b77c5623de2cd35042a7082b2d50a43304dc672bd99fa2006f59ea41d37a27 |
| 80046754 | 72 | dab21dfac6dedaabc6b1c10ef17f7adb824ffe7e5742e8161fbb1db015a4fdde |
| 8004679c | 376 | 4618782341d1ab5d9a186147c16d4ad9a7a1cdddc894d3a78719e58f34d15b57 |
| 80046bd0 | 304 | 8eb7629551da53d25aedebd78bd1a11804468247065eb4685b79f68cfa013cbd |
| 8020aefc | 44 | 72cc63551ec26fadb4106dfa694a34efe3be38fa7fa97f802d306453f072dfba |
| 8020b4ac | 76 | 282352ff267e0d5e83043d89188bc46363fe127380a6eb5414487ff0da6072f7 |
| 8020ba54 | 36 | c7b35d4075874e063982faa1d7d086e5d5ec4d70aed2b56c619b5e440e18e1ab |
| 8020b238 | 112 | e655ac2abaa9fab3af19ebc0df03b7ec62c2f35b640cfeeff6f6941b6db7d178 |
| 8020b2a8 | 176 | 832e4fbd68ca5d25b4345248b3eadb3421dcade987a190829e0617a61b19a8d7 |
| 8023cc44 | 72 | f6fb91c05f7548feeb7ab6910eddf99de5616a2f69ffb302668e9051badb44b2 |
| 8023c480 | 212 | 7191f0b4d2e319d285c8db0eb3c663aaef119792a2e0a66390ed24c441f18e0f |
| 8023c9e8 | 216 | f5cca675e2bbd4c6f03e357e1551f901741db5fa9354b1a9d3e86b62fb65f2d7 |
| 8023b044 | 244 | e291a438fc827ef22d258b8b22405923970c977efcbfcad6171577ab95b2e6cd |
| 8023bf8c | 160 | 74d1575c2f44b98288faef0858309e3e440520c568d670b0ad1b946df7454f44 |

Seven constants: `80437078=38c90fdb` (short-to-radian factor),
`80437098=41a00000` (20.0), `8043ca68=3f800000` (1),
`8043ca6c=00000000` (+0), `8043d030=3ff0000000000000` (f64 1),
`8043d150=0000000000000000` and `8043d198=0000000000000000` (f64 +0).
SDA2-relative references use the previously recorded r2 basis `8043ea20`
(`docs/static-recompilation-spike.md:178`); this reader does not establish live r2.

Focused command:
`python -m unittest discover -s research/tools/matching-decomp -p test_archived_actor_traversal_evidence.py -v`
passes **26 synthetic-only tests**. The two reader CLI runs are separate archive
evidence checks. No aggregate/build/runtime test or live parity is claimed here.

## Identity and translation

`PSMTXIdentity`, export `chunk_0064.c:211–243`, loads +0 and 1, merges the
appropriate paired lanes, and writes in this order:
`[2,3], [6,7], [8,9], [4,5], [0,1], [10,11]` at
`8020af04, af0c, af14, af18, af1c, af20`. All off-diagonals/translations are +0.

`TransApply`, export `chunk_0064.c:791–847`, is not multiplication by a
translation matrix. It preserves all nine linear entries and adds each argument
to its corresponding existing translation using `ps_sum1`. Exact order:

- b4ac loads [0,1]; b4b0 frsp X; b4b4 loads [2,3]; b4b8 frsp Y;
  b4bc loads [6,7]; b4c0 frsp Z; b4c4 loads [10,11].
- b4c8 stores [0,1]; b4cc calculates `[source2, round32(X+source3)]`.
- b4d0 loads [4,5]; b4d4 stores [2,3]; b4d8 calculates Y+source7.
- b4dc loads [8,9]; b4e0 stores [4,5]; b4e4 calculates Z+source11.
- b4e8 stores [6,7]; b4ec stores [8,9]; b4f0 stores [10,11].

Thus exact input/output aliasing is safe. It is not a full input snapshot before
the first store. Finite-f32 inputs make frsp exact; additions still round and
preserve source signed-zero rules rather than overwriting translations.

## 46698, 46754 and root generation

Exports: `chunk_0005.c:3009–3022,3046–3060,3221–3257`.

46698 loads actor+4a0 at466ac and compares to2. Equal jumps directly to return,
without 46754, root writes or traversal. Otherwise calls46754 then46bd0 with mode0.

46754 reads actor+48a, masks6. Nonzero: load constant20 at46770 and store only
actor+1d58 at46774, preserving special-vector X/Z. Zero: call PSVECAdd with
actor+12e0 (joint1 pose translation), actor+1dbc (offset), destination actor+1d54.
PSVECAdd (`chunk_0064.c:1249–1272`) loads both XY pairs atba54/ba58, calculates
`round32(A+B)` using ps_add atba5c, stores XY atba60, then loads both Z singles
atba64/ba68, calculates ps_add atba6c, stores Z atba70. Do not pre-read Z before
the XY write if exposing per-access host validation. The W=1 implicit lanes also
add, but that second lane is not stored and FP status is not emulated here.

Root46bd0 calls Identity into actor+8d4, reads position X/Y/Z and calls TransApply.
It then reads actor+4a1. If nonzero, or if short+6b8 is zero, it reads X/Y/Z
shorts at+70/+72/+74 and calls45838. If +4a1 is zero and +6b8 nonzero:

1. lha +6b8 at46c20, test; lha +72 at46c2c; shift offset left10 at46c30.
2. lha +70 at46c34; add heading and shifted offset at46c3c.
3. lha +74 at46c40; extsh effective Y at46c48; call45838 at46c4c.

Effective Y therefore wraps to signed16. Cancellation/wrapping to zero is an
admissible zero-angle case; raw nonzero +6b8 alone does not require rejection.
The ordinary path's argument load order is X/Y/Z; corrected path is heading,
pitch, roll after the gate/offset reads.

45838 tests signed Z first. Z=0 calls actual PSMTXCopy at45894; then checks Y,
then X and skips their rotations if zero. Caller argument reads are distinct
from these callee branch tests. Nonzero short refusal is a host boundary, not
source behavior. All three zero values yield the real pairwise copy path.

Root next reads scale X/Y/Z, calls Scale then Concat(root,scale,root), copies to
actor+114 then actor+1aa4. At46ca8 it loads copied Y actor+1ac0, at46cb0 loads
actor+6d0, at46cb4 executes fadds(copiedY,offset), at46cb8 stores actor+1ac0.
Only then does mode0 read the first hierarchy byte+1994 and call4679c(parent0).

## Signed-byte traversal and special joint1

Export `chunk_0005.c:3062–3115`; authenticated full span8004679c..80046914.
Entry and continuation indices are interpreted as signed bytes; negative stops
before reading the update mask. Each nonnegative iteration freshly loads
actor+1d70 and tests `slw(1,index) & mask`. Disabled joints skip composition but
still traverse both hierarchy links. A bounded host may admit only indices0..31;
that is host policy. PPC slw behavior for larger indices must not be replaced by
JavaScript's modulo32 shift semantics.

For enabled joint1: load short+1d68 and call457d4('z',parent,temp) at46804;
load short+1d64 and call457d4('x',temp,temp) at46818; load short+1d66 and
call457d4('y',temp,temp) at4682c. Only after all three wrappers, call46dd4 with
temporary parent, destination matrix1, special translation+1d54, ordinary joint1
quaternion, correction and scale. Other enabled joints use incoming parent's
matrix and ordinary pose translation, correction, quaternion and scale.

After composition, load topology byte1 at468cc. If its signed value is
nonnegative, recursively call4679c with this branch index and the **incoming
parent**, not current joint. After recursion, set parent=current at468e4, then
load byte0 at468e8 for continuation. This sequence also applies to disabled
joints. Do not impose conventional child/sibling meanings or preload byte0
ahead of recursion. Cycle/capacity guards are host-domain protections, not
authenticated original termination guarantees.

## Zero wrapper proof and corrected RotTrig decoding

Exports: wrapper `chunk_0005.c:2422–2437`; RotRad/RotTrig
`chunk_0064.c:590–695`; sinf/cosf `chunk_0069.c:5564–5590`; sin/cos
`chunk_0069.c:5394–5433,5108–5151`; kernels
`chunk_0069.c:4910–4943,4190–4225`.

457d4 stores the input short at stack+8;457f8 performs `psq_l W=1,I=5`;
45800 loads positive factor80437078;45808 fmuls(factor,loaded-short).
There is **no zero branch**. Under GQR5 signed16/load-scale0, short zero converts
to +0 and multiplication produces +0. RotRad at4580c is mandatory, followed by
Concat(input,temporary rotation,destination) at4581c.

RotRad preserves the angle, calls sinf at8020b260 then cosf atb270, supplies their
results to RotTrig atb288. sinf calls sin at8023cc50 then frsp atcc58; cosf calls
cos atcc74 then frsp atcc7c. For +0, both sin/cos mask the high double word's sign
and compare to0x3fe921fb, selecting their direct kernel calls. Tail arguments
8043d198/8043d150 are authenticated +0 (not needed by the taken early returns).

kernel_sin at8023bf8c compares the absolute high word against0x3e400000.
For +0, it executes fctiwz atbfa8, observes integer0 atbfb4, and branches atbfbc
directly to the epilogue with f1 unchanged. Thus result is +0, with no polynomial.
kernel_cos at8023b044 makes the same threshold/integer-zero tests; b074 loads
authenticated f64 1.0 from8043d030 and b078 branches to return. Thus result is1,
with no polynomial. Subsequent frsp conversions preserve those exact results.

RotTrig uses frsp on sin/cos, loads +0/1 and `ps_neg` on sin at8020b2bc.
Paired merges/stores produce these zero-angle row-major3x4 matrices:

- X: `[1,+0,+0,+0, +0,1,-0,+0, +0,+0,1,+0]`.
- Y: `[1,+0,+0,+0, +0,1,+0,+0, -0,+0,1,+0]`.
- Z: `[1,-0,+0,+0, +0,1,+0,+0, +0,+0,1,+0]`.

The exported C is misleading at its Y[5]/Y[3] and Z[1] assignments because it
loses paired-lane dataflow. The actual Y branch merges (+0,1) atb308, stores it
to[4,5] atb320, and merges(sin,+0) atb318 to store[2,3] atb324. The actual Z
branch merges(cos,-sin) atb338 and stores[0,1] atb34c. Use instruction evidence,
not those decompiler expressions. Preserve all three wrapper Concats and their
previously authenticated multiply/FMA order, including signed-zero effects.

## Remaining limitations

The supported numeric domain assumes normal RN=00/NI=0 execution, GQR0 raw
floating loads/stores, GQR5 signed16/load-scale0, and the recorded SDA2 basis.
Existing wait-reader startup evidence establishes GQR5 initialization to
00070007, not live invariance; no new live register capture is claimed.

No general nonzero trig, general quaternion reciprocal estimate, exceptional
float/overflow semantics, original FP flags, constraints/IK, mode1 traversal,
normal465fc caller replacement, retail replay or complete gameplay parity is
proved. A host refusal may retain an already completed write prefix; it is not
the original machine's exception behavior. Snapshot executable-SHA metadata is
not proof these bytes are unchanged original DOL bytes.
