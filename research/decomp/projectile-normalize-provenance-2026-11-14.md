# Normalize: why the accuracy bound is not an exact implementation

The mandatory projectile Normalize call at8007e074 remains unsupported. Even
for the reached direction (+0,+0,1), an estimator accuracy bound does not
uniquely determine the final stored result after the SDK refinement.

## Independent arithmetic counterexample

For squared norm1, the authenticated SDK schedule is:

- q = RN32(e × e)
- h = RN32(e × 0.5)
- c = −RN32(q − 3), using the genuine fused negative multiply-subtract
- r = RN32(c × h)

Take two hypothetical seeds, **not claimed hardware or emulator outputs**:

| Hypothetical seed | Relative error | Final r bits |
| --- | --- | --- |
| 1 | 0 | 3f800000 |
| 1 − 2^-12 | 1/4096 | 3f7fffff |

Both seeds and all intermediates are finite normal values. The seeds are
binary32-exact, so the single instruction's 25-bit multiplier reduction cannot
remove this difference. The independent rational test reproduces every rounding
step: `research/tools/matching-decomp/test_projectile_normalize_error_bound.py`.
It contains no estimator implementation, external source or lookup table.

IBM's [public generic PowerPC instruction reference](https://www.ibm.com/docs/en/aix/7.1.0?topic=set-frsqrte-floating-reciprocal-square-root-estimate-instruction)
provides an accuracy guarantee and permits variation, not an exact unit-input
result. It is not a Gekko-specific numeric specification. The Gekko manual
already cited elsewhere in this repository gives the stronger1/4096 bound but
also permits variation. Granting that stronger bound still leaves the two
results above. The [available mirror](https://fenixfox-studios.com/manual/powerpc/IBMGekkoManual.pdf#page=419)
identifies its manual as unpublished and confidential on its opening pages;
public accessibility is not evidence of authorized publication or redistribution.

## Existing model evidence is a different claim

The existing finite-axis implementation in `actor-joint-matrix.ts` uses an
independently derived arithmetic specialization with a pinned numeric seed fact.
Its provenance remains the [Dolphin unit-test expectation](https://github.com/dolphin-emu/dolphin/blob/221d396b3acb9e0d1a815cbf7613a9f7032cc14a/Source/UnitTests/Common/FloatUtilsTest.cpp#L69-L99)
and the corresponding [input1.0](https://github.com/dolphin-emu/dolphin/blob/221d396b3acb9e0d1a815cbf7613a9f7032cc14a/Source/UnitTests/Core/PowerPC/TestValues.h#L10-L20),
not an independently authenticated physical Gekko observation. The project uses
per-file licenses as described in its [COPYING file](https://github.com/dolphin-emu/dolphin/blob/221d396b3acb9e0d1a815cbf7613a9f7032cc14a/COPYING).

Technically, a byte-backed consumer could reuse that existing finite kernel
without adding estimator data or third-party implementation source. Such reuse
would remain model-backed and would not cure any unresolved provenance or
licensing concern. It must not be described as a new clean-room derivation,
architecture-only proof or hardware capture. This checkpoint does not extend
or execute that kernel for projectile normalization.

A stronger exact claim would need an authenticated physical Gekko capture of
frsqrte's full64-bit result for input1.0, with processor identity, test harness,
build digest and floating-point context, or an authorized exact numeric
specification. Software-emulator or other-processor results must remain labeled
as such. Broader inputs need broader evidence, not extrapolation from one seed.

The independent target-displacement continuation proceeds without resolving
this estimator question. It retains explicit boundaries rather than substituting
an exact reciprocal square root or skipping normalization for unit length.
