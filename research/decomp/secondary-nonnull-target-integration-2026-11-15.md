# Secondary nonnull target preparation, 2026-11-15

## Scope and authenticated evidence

Continues the existing `8006ae60` caller only when primary508 is null and the
completed null-primary path reaches nonnull actual+cc (`visibilityTarget`).
Evidence is the existing complete derived instruction/operand record in
`.tmp/target-preparation-evidence-20261114/operands.json`, checked at
`8006b1d0..8006b2e8` (operand JSON SHA-256
`38ba7908f92f03d12a5ab252cfd455360d3d5c731f64189b4166ac7dfea3bb8d`).
No archive selection, raw executable read, asset import,
retail hydration, or replacement source implementation was used.

- `b1d0` compares actual+cc. `b1dc` captures canonical command-admission+c8
  once. The former is opaque branch input, not the OBJECT provider.
- `b1ec` loads integer X at captured OBJECT+64, `b1f4` loads integer Y at +68,
  `b1f8/b1fc` store aim+518/+51c, `b200` loads integer Z at +6c, and `b204`
  stores aim+520. Thus Y is loaded before X is stored; Z is not loaded until
  Y has been stored. Original allocation `readU32` supplies the words, after
  explicit OBJECT-kind admission rejects descriptor or external-pointer storage.
- The existing numeric `getAimPositionOwner` remains the only destination.
  Conversion admits all finite float32 bit patterns, including signed zero,
  subnormals and largest finite values. NaN and infinity patterns stop at the
  corresponding reached store. Their integer load itself does not reject,
  and later operands are not prevalidated. No raw shadow vector is added.
- `b208` calls the existing authenticated `8020bc88` square-distance body with
  actual pos+20 and the captured original OBJECT+64. The caller reuses actual
  world position ownership and root processor/GQR0 admission. Forming an
  inline position address is not a component load: numeric-vector admission
  is deferred until after the three aim stores, at the reached distance call.
- Shared `80437658` must be authenticated positive zero. A positive total
  stops at unsupported `b218 frsqrte`; zero stores actual+760 at `b264`.
- `b268` freshly loads the zero constant; `b26c/b270/b274/b278` freshly load
  position X, OBJECT X, position Z, OBJECT Z. Existing finite source float32
  arithmetic computes the horizontal square. Positive results stop at
  `b298 frsqrte`; zero stores actual+764 at `b2e4`, and `b2e8` rejoins `b33c`.

## Ownership and failure behavior

The original admission binding, data, actual actor, world position, selected
primary vector, and numeric aim owner remain canonical. Existing lifecycle,
reentry, source-storage alias and native terminal destination-descriptor
checks surround the reached operations. The nonnull lane finishes public
metadata observation with a callback-free retained-native check before each
aim and distance store. It rebuilds the current nested owner inventory and
rechecks canonical links, c8/cc/aim/distance aliases, reached position20 aliases,
selected-position aliases/references, and lifecycle/reentry state. No accessor destination is invoked
or recreated, and no copied coordinate or distance store is rolled back by
later failure. Primary position validation was extracted into a shared local
helper; primary pointer504 capture and distance behavior remain unchanged.

## Verification

The new focused `actor-secondary-nonnull.selftest.ts` is wired into the
attached setup aggregate. It uses the existing explicit synthetic six-actor
third-pass graph and original allocation-backed OBJECT bytes, never a fake
successful full frame. Coverage includes exact raw-byte/load/store order,
opaque cc distinct from c8, once-captured c8 despite mutation, finite bit-copy
patterns, nonfinite refusal at each reached store, malformed byte and alias
faults, positive total and horizontal estimator barriers, partial writes,
terminal destination mutation, lifecycle poisoning and reentry.

Validation logs are retained outside the repository in the sibling
`secondary-nonnull-final-validation-20261115` directory. Strict combat
TypeScript and affected primary-distance, primary-stores, null-direction,
secondary-null, nonnull-secondary and third-pass focused suites are the
implementation checks. Final aggregate/contributor validation and publication
are separate gates owned by the coordinating task, not claimed here.

Final production SHA-256 is
`d0844b6d81d56aea98f4c292b30f21b00eb660612a5e3bff7a667daa4440203a`.
`strict-r6` passed (exit 0). `focused-r6` passed the final 105-fixture suite
(exit 0),
including a dynamic last-public-observation baseline and 29 fault replays
across all five stores. Each replay verifies the exact completed prefix,
rather than accepting an eventual error after a store has leaked. These cover
direct/nested c8 owners, numeric c8, selected reference/field50c, and late
field20/numeric32 after position is reached. The final focused result is
recorded in `focused-r6.log` and `focused-r6.exit`.

The earlier affected-suite run (`targeted`, exit 0) passed primary-distance,
primary-stores (310 fixtures), null-direction (318), secondary-null (430),
initial secondary-nonnull (72), and third-pass (31). That build predates the
final nonnull terminal strengthening; it is regression evidence, not a claim
that the final aggregate has run. The coordinating final gate must use the
frozen final source.

## Explicit remaining limits

No positive-distance reciprocal-square-root estimate is implemented. Primary
nonnull direction helper `8006d228` is still a distinct mandatory boundary.
A successful zero secondary lane can finish this target-preparation prefix,
but the outer frame still stops at mandatory `80027764`, whose complete body
is outside the current evidence, then at mandatory `8000bef4`. Neither call
is skipped. There is no full-frame, hardware parity, retail six-actor setup,
console correctness, scheduler authority, rendering, or playability claim.
