# Bounded positive nonunit flat primary placement

This checkpoint extends only primary placement's positive, nonunit, flat
source displacement to the existing rounded-norm arithmetic lane. Unit-flat
and nonpositive-flat inputs retain the original axis lane. Sloped primary and
standalone secondary admission are unchanged. There are no new estimate seeds,
retained-length pairs, sine inputs, fallback constructors or general trig APIs.

## Independent arithmetic evidence

The independent Fraction/integer RN32/RN64 proof in
`/workspace/shared/flat-half-primary-feasibility/reference.py`, `results.json`,
`outputs.txt` and `REPORT.md` models each reached arithmetic operation without
production imports or host sqrt/trig. Test-only literal words in
`actor-primary-flat-half-witness.selftest.ts` are transcribed from that proof.
Original instruction ordering is established by
`terrain-orientation-evidence-2026-11-13.md` (210 onward),
`primary-terrain-placement-evidence-2026-11-13.md` (153–196), and
`actor-matrix-traversal-evidence-2026-11-13.md` (127–140).

The explicit owned fixture has actor position (10,20,30), raw bank-zero joint1
translation (0,10,0), joint2 (0,2,0), joint3 (0,.5,0), exact identity quaternions,
unit root scale, zero corrections and pre-rotations, flags48a&6 clear and
 offset1dbc=(0,-2,0). Adjusted1d54 is (0,8,0). Owned joint1 scales15d4=(2,1,1)
is applied by actual mode0 composition, yielding bases diag(2,1,1) and retained
translations (10,28,30), (10,30,30), (10,30.5,30). Tests run real mode0 followed
by real mode1 with no matrix reseeding.

Owned primary joint0c=3 selects physical matrices1/2/3. Unchanged parent root
transforms the **raw** current pose to (10,30,30), not adjusted1d54. Target
(10,30.5,30) subtracts to exact (0,.5,0). Retained lengths refine to (2,.5).
Incoming squared norms are 4,1,1; Normalize operands are .25,.25,1; saved
 displacement Mag uses .25 and produces 3effffff. Actual norms select existing
seeds, never ideal lengths or an up-front fixture-bit whitelist.

Raw scalar cosines 40000001/c0000000 clamp to +1/-1. Both fused sine
complements are negative zero and skip estimates. All six signed bends
±1,±2,±3 yield current diag(3ffffffe,3f7ffffe,3f7ffffe), translation
(41200000,41f00000,41f00000). Adjacent translation rounds exactly to
(41200000,42000000,41f00000), i.e. (10,32,30). Its diagonal has signs
(+,-,-), (-,+,-), or (-,-,+) for bend magnitudes1/2/3. Full exact words,
including zeros, are literal independent expectations in both joint/world tests.
End is unchanged only at the placement boundary; ordinary world continuation
then really rebuilds it. This is not a whole-mode1 preservation assertion.

## Refusal boundaries and coverage

- Identity/+Y.5 refuses at second-cross Normalize square .0625 after current
  translation but before any basis writes. Scalar .25 support cannot admit it.
- X2/+Y2 finishes orientation, then refuses first sine complement 3d7c0000.
  No next-matrix Concat or world continuation occurs. Existing identity/+Y2
  negatives also remain refusals, with their corrected late sine boundary.
- Repeated output norms 407ffffc/3f7ffffc are still unsupported. Explicit input
  repair, or a fresh genuine mode0 rebuild, supports a later standalone retry;
  same-call reentry poison is not a permanent actor-frame closure.
- Zero/negative flat displacements retain refusal. Axes/bend are fresh late
  reads. Invalid axes, bend, accessors, aliases, unknown/replaced owners and
  non-writable output slots preserve their actually completed prefixes.
- New focused tests check all six complete matrix witnesses, all normalized
  basis store stops, all twelve adjacent Concat stops for each bend, translation
  stops, late descriptor observers and caught same-call reentry, fresh retry,
  raw/adjusted distinction, physical adjacency independent of topology, owned
  mode0 scale production, live correction/topology fields and world continuation.

Exports: `runActorJointFlatHalfPrimaryPlacementSelfTests` and
`runActorWorldFlatHalfPrimaryPlacementSelfTests`; both run within their existing
joint/world aggregate exports. The runtime relies on actual reached finite-norm
and sine guards: this is not a claim that arbitrary positive flat inputs succeed.
The concrete success witness is the fixture above under stable records/bends,
finite normal arithmetic, RN=00 and existing GQR assumptions.

No archive/DOL selections, raw payload reads or extraction were used. No
completed-frame, retail hydration, repeated-frame closure, general estimator,
general trig, clone/gameplay or target-reaching claim is made. Missing27764,
unconditional0bef4 and6d228 remain unchanged.
