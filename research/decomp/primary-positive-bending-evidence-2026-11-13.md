# Bounded positive two-bone bending

Date: 2026-11-13. This extends the executable primary `80047368` domain from
the retained length pair `(2, 0.5)` to the additional pair `(1, 1)`. It retains
the unit upward target displacement, positive orientation selectors `(2, 1)`,
the previously admitted signed-axis bases and six signed bend indices. It is
not general IK, original execution verification or production activation.

## Source and model provenance

The authenticated instructions, constants, memory order and branch PCs are
unchanged from `primary-terrain-placement-evidence-2026-11-13.md`. That fixed
reader checks both complete local ProgramDB snapshots. No additional game
bytes, captures, executable windows or arbitrary-address reads are required.

The new facts are two finite reciprocal-square-root estimates from the
[pinned canonical Dolphin model](https://github.com/dolphin-emu/dolphin/blob/221d396b3acb9e0d1a815cbf7613a9f7032cc14a/Source/Core/Common/FloatUtils.cpp#L75-L139).
The read returned blob `312d4a88a217e061a8d5f91061272a417b1d484b`. These are
numeric facts derived for two inputs, not an imported estimator implementation
or lookup table. They remain model-backed, not original hardware observations.

| Sine-square f32 bits | Value | Initial estimate f64 bits | Exact estimate |
| --- | --- | --- | --- |
| `3f400000` | 0.75 | `3ff2794000000000` | 18917 / 16384 |
| `3f3fffff` | 0.7499999403953552 | `3ff2794cb8000000` | 38742423 / 33554432 |

The first input selects model bucket8, offset0; the second selects bucket7,
offset2047. Both have binary64 exponent field1022. The second seed has26
significant bits and must not be rounded to binary32 before the source's
double-precision operations. No single-precision estimator specialization or
Force25Bit substitution is made at these double-precision source sites.

The unit bone lengths use the already established seed `3feffe8000000000`
for squared length1. Each actual three-stage length refinement returns1;
the old `(2, 0.5)` behavior remains intact. Other pairings are still refused.

## Reached arithmetic

For unit bones and target displacement `(0, 1, 0)`, SDK Mag returns
`3f7fffff`, not mathematical1. The source cap is `3fffbe77` and does not bind.
The rounded first cosine is `3effffff`; the second is `bf000001`. Their fused
single-precision complements are the two inputs above.

Each positive complement executes the existing source operation tree:

1. `q = RN64(e * e)`.
2. `h = RN64(0.5 * e)`.
3. `k = -RN64_FMA(s, q, -3)`.
4. `e = RN64(h * k)`.

After three iterations, `RN64(s * e)` is rounded once to binary32. Both
admitted complements produce magnitude `3f5db3d7`. The initial sign-test and
late bend-byte reload still select the source sine signs and X/Y/Z rotations.
Zero complements preserve the old signed-zero branch and skip all refinement.

The exact intermediate expectations are:

| Input | Stage | q64 | h64 | k64 | next e64 |
| --- | ---: | --- | --- | --- | --- |
| `3f400000` | 1 | `3ff55466d9000000` | `3fe2794000000000` | `400000596ea00000` | `3ff279a7422e5480` |
| `3f400000` | 2 | `3ff555554d85b177` | `3fe279a7422e5480` | `4000000002eddd73` | `3ff279a74590331b` |
| `3f400000` | 3 | `3ff5555555555552` | `3fe279a74590331b` | `4000000000000001` | `3ff279a74590331c` |
| `3f3fffff` | 1 | `3ff5548437cedc44` | `3fe2794cb8000000` | `4000004e75bcaf82` | `3ff279a74f46ddec` |
| `3f3fffff` | 2 | `3ff555556bc40ba0` | `3fe279a74f46ddec` | `400000000241265a` | `3ff279a751e14d56` |
| `3f3fffff` | 3 | `3ff5555571c71c95` | `3fe279a751e14d56` | `4000000000000001` | `3ff279a751e14d57` |

Final double products are `3febb67ae8584caa` and `3febb67ad5dea55f`.
The first input's second correction is a concrete fusion witness: separately
rounding the product and subtracting3 gives `4000000002eddd74`, not the
required `4000000002eddd73`. The final binary32 sines happen to agree despite
this error, so output-matrix checks alone cannot verify the fused operation.
Direct exact-intermediate tests are required as well.

`actor-primary-float.ts` therefore implements a private, bounded BigInt dyadic
correction. It accepts only these two squares and normal estimate-square
operands in `[1, 2]`, and rounds the exact signed product-plus-addend once to53
bits with ties to even. This does not expand the shared float API, emulate
FPSCR exceptions, or claim arbitrary binary64 behavior. The source sine loop
still performs every separate multiply and its final `frsp`.

## Actual caller and retained consumers

The actual composite keeps raw baseY10, offsetY-2, floor10 and clearance1 from
the folded fixture, but uses adjacent and distal raw translations ofY1 each.
The first pass producesY8/9/10, and the genuine terrain query at the distal
point returns10. `47164` creates primary targetY11. `47368` transforms the raw
base toY10, so the target displacement is the same supported unit vector.

With positive Z bend, the current matrix's diagonal XY values become
`3efffffd`; its off-diagonal magnitudes become `3f5db3d5`. The adjacent matrix
has unequal rounded off-diagonals `bf5db3d5` and `3f5db3d6`, and translation
`(100.86602783203125, 10.5, 100)`. Special traversal skips ordinary evaluation
of that overwritten node and evaluates the distal node from its bent parent.
Its translation is `(100, 11, 100)` in this fixture.

Both X and Z bend signs round to that target in this example. The Y-axis
rotations instead give distal `(100, 12, 100)`, as the original axis choice
requires. No unconditional endpoint snap or general target-attainment claim
is introduced. At a zero world origin, the same finite operations retain
small endpoint residuals rather than idealized geometry.

All actual matrices copy to the linked clone. Later real wait and replacement
setup retain them, and the existing movement consumer uses baseY10 to produce
height3.5. Repeated explicit refresh recreates first-pass geometry before
bending, rather than accumulating changes to previously bent matrices.
Late invalid bend and unsupported mixed length pairs preserve their completed
source prefixes without copying uncompleted output to the clone.

## Remaining boundaries

Other bone-length pairs, nonunit target displacements, broader orientation
selectors and general estimator inputs are still unproved. The caller's
existing topology, aliasing, own-data, synchronous adapter and partial-write
rules remain unchanged. RN00/NI0 and supported GQR assumptions are still host
model bounds, not newly observed original state.

Real spawn resource hydration, complete exclusive lifecycle/contact ownership
before Battle's host sweep, and source-matrix presentation remain unfinished.
The new unit-bone branch is actual local gameplay math integration; it is not
permission to enable an incomplete production route or fall back to host code
after partial source writes.
