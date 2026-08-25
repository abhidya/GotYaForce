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

Family-wide uncertainty: every `undefined8`-returning shim returns the entry
value of PPC r3 (first pointer arg) zero-extended to 64 bits. The corpus
proves callers consume r3, but which value r3 holds at exit is an assumption
(leaf SDK routines do not normally clobber r3). A disassembly check of the
real SDK routines would settle it.
