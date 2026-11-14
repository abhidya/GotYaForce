# Live target squared distance and nearest-candidate loop

This source-only checkpoint continues genuine `8006b850` from the first
`8020bc88` call at `8006b968` through the nearest-candidate loop and the selected
OBJECT's `+20` pointer load at `8006b9b8`. It stops before sibling descriptor
selection (`8006b9c4`) or, for a null selected actor pointer, before target commit
(`8006ba18`). It does not write target state or complete a battle frame.

## Previously authenticated inputs

- [Target dispatch evidence](target-dispatch-evidence-2026-11-14.md): the existing
  C/index-bounded, not named-map-size-proven, 528-byte `8006b850..8006ba60`
  span has SHA-256
  `8a01e4c3f1a21269d2b9fb98b2d6c71ab2d46859d9670049069db7c6eafabb51`.
- [Primary terrain evidence](primary-terrain-placement-evidence-2026-11-13.md):
  the existing 40-byte `8020bc88..8020bcb0` PSVECSquareDistance span has SHA-256
  `a5dc9dd558d92f78fdebc97036e9c4e9b250a0f57eed1b449a8515f13c029e74`.
- [Projection integration](target-projection-integration-2026-11-14.md) supplies
  the actual descriptor-selected joint translation and caller-local stack.

No evidence reader selection is widened. No original executable is run, and
no reciprocal-square-root estimator or disputed implementation is imported.
SquareDistance does not contain an estimator or square root.

## Live arguments and operations

A is the retained caller-local projection stack. B is the **captured original
OBJECT pointer plus64**, backed by the same allocator's registered big-endian
bytes. Neither the pointed actor's position nor a copied target snapshot is
substituted. Scratch entry0 is not reloaded at the call.

The actual helper performs, in this order:

1. Paired A.y/A.z, then B.y/B.z loads (`OBJECT+68/+6c`).
2. Binary32 subtraction, retaining these old dy/dz values.
3. Fresh paired A.x/A.y, then B.x/B.y loads (`OBJECT+64/+68`).
4. Square the old dy/dz, after both fresh XY loads.
5. Subtract the freshly loaded XY values.
6. Compute both single-round FMA lanes: `dx*dx + oldDySquared` and
   `newDy*newDy + oldDzSquared`. The latter still executes even though unused.
7. Add oldDzSquared to the first FMA lane for the scalar return.

Subtraction, FMA and final addition use the existing independently tested exact
binary32 arithmetic. A product of two binary32 operands fits exactly in binary64
before the one binary32 multiplication rounding. The host domain is finite,
exact binary32 operands/intermediates with gradual underflow and nearest-even
rounding. Overflow and NaN are refused, not emulated as source exceptions.
Signed zero is preserved. RN00/NI0, paired-single enablement and configuration
invariance are model assumptions, not authenticated live processor state.

The paired profile comes from the genuine root's existing `processor` record,
not a new GQR owner. An identity-only getter retains it lazily; each reached
paired load validates the same identity and live `gqr0`. The full-word zero
requirement matches the existing conservative host domain, although the hardware
helper itself uses only GQR0 float loads. Missing profile preserves the old
`8006b968` boundary after all projection stores. Accessors are never called.
The profile cannot alias canonical byte/vector/stack owners or helper storage.

## Nearest loop and safe stop

The first distance initializes the local best value and the captured first
OBJECT initializes the local winner. Index1 begins the loop. The scratch count
is freshly reloaded before **every** continuation decision and compared as a
signed32 integer. Each reached candidate pointer and both vector arguments are
live. No active/team/lifecycle filter is repeated in this loop.

Only a strictly greater distance skips replacement; a later equal candidate
wins. The source unordered case would also replace, but NaN is outside the
finite host domain. Index4096 is a lazy host limit at the reached scratch load,
not a source limit or eager count rejection. Shrinking, growing and negative
raw signed counts therefore preserve the source decision order within that
bound. Scratch entries, unused tails, globals and vector bytes are not rewritten
by distance selection.

After the final count comparison, the same allocator reads the winner's `+20`
pointer once. Null selects the `8006ba18` boundary; nonnull selects `8006b9c4`.
This live read demonstrates which OBJECT won without exposing a synthetic
nearest-target callback or result. The `+28` sibling descriptor, flags and all
`502/504/508/50c/510/514` commits remain unsupported. Earlier scan/projection
writes survive failures; caller/candidate completeness and caught-reentry
checks remain in force. A metadata-only set retains every actor accepted during
the scan: later null or rejected list entries cannot remove a previously
accepted actor from completeness checks. This closes an independently observed
failure gap without adding source pointer or lifecycle reads. No scheduler capability or successful-frame token is
created.

## Claim ceiling and next work

This is bounded synthetic offline integration of the genuine lifecycle graph,
not hardware parity, `MATCH`, full source hydration, or browser playability.
The next lane is the selected object's canonical sibling descriptor flags and
redirect scan, followed by ordered target commits. Real candidate-list
production, remaining outer-frame predecessors, full six-actor hydration,
projectile flight/collision/damage and production activation remain open.
