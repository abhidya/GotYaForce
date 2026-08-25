# SDK shim ledger

Status legend: impl = implemented, comp = compiles (pinned emcc -O1
-fno-strict-aliasing -Wall), test = family self-test passes under the emsdk
node (wasm). All code authored by local Qwen (unsloth/Qwen3.8-27B-GGUF)
through pi 0.84.3; UNREVIEWED, not integrated.

## psvec.c (test_psvec.c: PSVEC_TESTS_PASS)

| function | impl | comp | test | notes |
|---|---|---|---|---|
| gnt4_PSVECAdd_bl | y | y | y | undefined8 return = entry r3 (= `a`) zero-extended; PPC leaf-routine assumption, flagged uncertain |
| gnt4_PSVECSubtract_bl | y | y | y | |
| gnt4_PSVECCrossProduct_bl | y | y | y | alias-safe (temps); right-handed |
| gnt4_PSVECMag_bl | y | y | y | float math, sqrtf, widened to double at return |
| gnt4_PSVECNormalize_bl | y | y | y | no zero-guard, mirrors SDK 1/sqrt behavior (inf/nan on zero vector) |
| gnt4_PSVECSquareDistance_bl | y | y | y | |
| gnt4_PSVECSquareMag_bl | y | y | y | |

## psquat.c (test_psquat.c: PSQUAT_TESTS_PASS)

| function | impl | comp | test | notes |
|---|---|---|---|---|
| gnt4_PSQUATDotProduct_bl | y | y | y | float accumulator, widened at return |
| gnt4_PSQUATScale_bl | y | y | y | arg map: s=scale (f1), v=src quat (r3), out=dst (r4); returns entry r3 (= `v`) |

## psmtx.c (test_psmtx.c: PSMTX_TESTS_PASS)

| function | impl | comp | test | notes |
|---|---|---|---|---|
| gnt4_PSMTXIdentity_bl | y | y | y | row-major 3x4 |
| gnt4_PSMTXCopy_bl | y | y | y | returns entry r3 (= `src`) |
| gnt4_PSMTXConcat_bl | y | y | y | ab = a*b with implicit {0,0,0,1} row; alias-safe via temp; returns entry r3 (= `a`) |
| gnt4_PSMTXMultVec_bl | y | y | y | w=1 point transform; alias-safe (loads vec first); returns entry r3 (= `mtx`) |
| gnt4_PSMTXTrans_bl | y | y | y | arg map: x,y,z in f1-f3, matrix in r3; returns entry r3 (= `out`) |
| gnt4_PSMTXScale_bl | y | y | y | arg map: sx,sy,sz in f1-f3, matrix in r3 |
| gnt4_PSMTXRotRad_bl | y | y | y | arg map: angle=f1 rad, `quat_out` is the 3x4 MATRIX (corpus name misleading), axis is char 'x'/'y'/'z' (case-insensitive); unknown axis leaves matrix untouched |

## c_mtx.c (test_c_mtx.c: C_MTX_TESTS_PASS)

| function | impl | comp | test | notes |
|---|---|---|---|---|
| gnt4_C_MTXLookAt_bl | y | y | y | SEMANTICS-UNCERTAINTY: corpus names (eye/center/up) are GL-style but GC SDK positional order is (m, camPos, camUp, target) — implemented positionally per SDK, so `center` is the UP vector and `up` is the look-at TARGET. Adds zero-length normalize guards the real SDK lacks (differs only on degenerate input). |
| gnt4_C_MTXOrtho_bl | y | y | y | arg order t,b,l,r,n,f (SDK order); GC z-range [-1,0] convention: m[2][2]=-1/(f-n), m[2][3]=-f/(f-n) |
| gnt4_C_MTXPerspective_bl | y | y | y | fovY in DEGREES; GC z-range [-1,0]: m[2][2]=-n/(f-n), m[2][3]=-fn/(f-n), m[3][2]=-1, m[3][3]=0; outputs Mtx44 (4x4), not 3x4 |

## os_stubs.c (test_os_stubs.c: OS_STUBS_TESTS_PASS)

| function | impl | comp | test | notes |
|---|---|---|---|---|
| gnt4___OSCacheInit_bl | y | y | y | documented no-op (no cache in portable target) |
| gnt4___OSFPRInit_bl | y | y | y | documented no-op |
| gnt4___OSPSInit_bl | y | y | y | documented no-op (no paired-single mode) |
| gnt4___init_hardware_bl | y | y | y | documented no-op |
| gnt4___init_user_bl | y | y | y | no-op, returns 0; real MSL __init_user return value unverified |
| gnt4___cvt_fp2unsigned_bl | y | y | y | PPC saturating double->u32: NaN/<=0 -> 0, >=2^32-1 -> 0xFFFFFFFF, else truncate |

## libc_math.c (test_libc_math.c: LIBC_MATH_TESTS_PASS)

| function | impl | comp | test | notes |
|---|---|---|---|---|
| gnt4_memcpy | y | y | y | delegates to host memcpy |
| gnt4_memset | y | y | y | delegates to host memset |
| gnt4_acos_bl | y | y | y | host libm; MSL bit-exactness not verified (last-ulp differences possible vs GC libm) |
| gnt4_atan | y | y | y | host libm; same caveat |
| gnt4_atan2_bl | y | y | y | host libm; same caveat |
| gnt4_pow_bl | y | y | y | host libm; same caveat |
| gnt4_sin_bl | y | y | y | host libm; same caveat |

## gx_stubs.c (test_gx_stubs.c: GX_TESTS_PASS)

| function | impl | comp | test | notes |
|---|---|---|---|---|
| gnt4_GXSetProjection_bl | y | y | y | records SDK 7-float projection vector (type + 6 coefficients) into static state |
| gnt4_GXGetProjectionv_bl | y | y | y | reads recorded state |
| gnt4_GXSetViewport_bl | y | y | y | records 6-float viewport |
| gnt4_GXGetViewportv_bl | y | y | y | reads recorded state |
| gnt4_GXSetScissor_bl | y | y | y | records only; no getter exists in the seam |
| gnt4_GXProject_bl | y | y | y | real math per SDK GXProject: model transform + perspective/ortho projection vector + viewport mapping; args map to (model 3x4, pm[7], vp[6]) |
| gnt4_GXInitLightColor_bl | y | y | y | TODO no-op: corpus prototype does not carry SDK (GXLightObj*, GXColor) shape; semantics deferred |
| gnt4_GXInitLightDistAttn_bl | y | y | y | TODO no-op, same reason |
| gnt4_GXInitLightSpot_bl | y | y | y | TODO no-op, same reason |

GX caveat: Set*/Get* record into process-local static state, not real GX
hardware registers; sufficient for callers that round-trip through the seam,
not a rendering implementation.

## hsd_stubs.c (test_hsd_stubs.c: HSD_TESTS_PASS)

All 27 declared HSD_* seam functions are documented TODO no-op stubs (empty
body, or 0/NULL matching the declared return type). Real semantics operate on
sysdolphin scene-graph objects that do not exist in the portable harness;
implementing them is out of scope for this lane and marked deferred. All 27:
impl=y(stub) comp=y test=y(smoke: callable, returns 0/NULL, no crash).

Per the seed header, two symbols are additionally present with deliberately
EMPTY-PAREN signatures and no semantics, because their parameter types are
still contested between corpus units and must not be guessed:

| function | status |
|---|---|
| gnt4_HSD_JObjSetMtxDirtySub_bl | stub-with-TODO, signature unsettled (void* vs int*), not declared in header |
| gnt4___assert_bl | stub-with-TODO, signature unsettled (char* vs float*), not declared in header |

Stub caveats: gnt4_HSD_JObjLoadJoint returns NULL — callers that dereference
the joint will fault; that is intentional surfacing, not correctness.
gnt4_HSD_JObjClearFlags/SetFlags return 0 rather than an entry-register
value because their first GPR pair is packed into an undefined8 and the
r3-at-exit assumption is not meaningful there.

Harness note: one mechanical fix was applied by the harness (not the model):
test_hsd_stubs.c printed its pass marker without a trailing newline, which
emscripten's line-buffered stdout drops; a `\n` was added. No logic changed.

Family-wide uncertainty: every `undefined8`-returning shim returns the entry
value of PPC r3 (first pointer arg) zero-extended to 64 bits. The corpus
proves callers consume r3, but which value r3 holds at exit is an assumption
(leaf SDK routines do not normally clobber r3). A disassembly check of the
real SDK routines would settle it.
