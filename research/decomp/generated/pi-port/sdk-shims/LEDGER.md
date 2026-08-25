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

Family-wide uncertainty: every `undefined8`-returning shim returns the entry
value of PPC r3 (first pointer arg) zero-extended to 64 bits. The corpus
proves callers consume r3, but which value r3 holds at exit is an assumption
(leaf SDK routines do not normally clobber r3). A disassembly check of the
real SDK routines would settle it.
