# Target descriptor and matrix projection

This checkpoint continues the surviving-candidate path in genuine `8006b850`
from descriptor `4b0` at `8006b924` to the call at `8006b968`. The source caller
copies the selected joint's world translation into its own stack vector. It
does not refresh matrices, transform a point, select a nearest target, or
complete a battle frame.

## Already authenticated evidence

The exact instructions are in the previously selected 528-byte
`8006b850..8006ba60` span, SHA-256
`8a01e4c3f1a21269d2b9fb98b2d6c71ab2d46859d9670049069db7c6eafabb51`.
See [target dispatch evidence](target-dispatch-evidence-2026-11-14.md).
The span remains C/index-bounded, not named-map-size-proven. This checkpoint
selects no new archive payload and executes no original code.

A provenance correction matters for the next lane: `8020bc88` is already
authenticated as **PSVECSquareDistance**, not an unauthenticated function.
The [primary terrain evidence](primary-terrain-placement-evidence-2026-11-13.md)
and its fixed reader select `8020bc88..8020bcb0` exclusive, 40 bytes, SHA-256
`a5dc9dd558d92f78fdebc97036e9c4e9b250a0f57eed1b449a8515f13c029e74`.
It contains no reciprocal-square-root estimator. The current target lane
stops before invoking it because its live canonical vector-call integration
is not implemented. The private primaryLength routine is not a substitute:
it uses preloaded vectors, restricts lengths, then performs estimator
refinements for the separate primary-terrain caller.

## Canonical storage and exact order

- Actor `4b0` remains the genuine admission/world mapping header's
  `descriptor4b0`. No copied descriptor pointer or RomActor shadow is added.
- Descriptor `+10` remains the attributes-owned `byte10` extension. The new
  admission metadata getter factors the same retained descriptor identity and
  alias checks already used by `8006bda8`. The joint mapping's numeric
  descriptor array represents `jointMap8c`, not scalar descriptor bytes.
- The selected matrix is the existing world owner's twelve-lane matrix.
  Lanes `3,7,11` correspond to actor `8e0,8f0,900` plus signed index times48.
  `partAimAnchors`, local pose translation, actor position, and a second matrix
  owner are not substitutes.
- New optional `projectionStack` explicitly supplies the caller-local
  stack `+8/+c/+10` cells as `x/y/z`. It is not a second actor vector.

The reached source order is:

1. `8006b924`: capture mapping descriptor pointer once.
2. `8006b934`: capture descriptor byte10 once.
3. `8006b938`: freshly load the first scratch object pointer.
4. Sign-extend the captured byte, multiply by48, and form source addresses.
5. `8006b950/954`: load matrix lane3, then store stack.x.
6. `8006b958/95c`: load matrix lane7, then store stack.y.
7. `8006b960/964`: load matrix lane11, then store stack.z.
8. Stop before the actual `8020bc88` call at `8006b968`.

There is no descriptor or initial scratch-pointer null guard in this source
prefix. A null descriptor refuses when its byte would be dereferenced. The
scratch pointer is not dereferenced before the call, so a null or unknown
symbolic pointer still permits the three stack stores. Invalid host pointer
representations are refused at their load. Matrix index bounds are existing
host bounds, checked only after the scratch word load; negative signed indices
are not mapped to a fallback joint. Descriptor pointer, selector and matrix
identity are captured, while the three matrix values remain separately live.

## Admission, faults and limits

Absent optional projectionStack preserves the historical `8006b924` refusal.
If the property exists, its value, own-data record, ownership and destination
writability are checked when the first stack store is reached, after X has
been loaded. Later destinations are checked individually. Prior candidate
count/list stores and completed stack stores survive a later failure.

Only finite exact binary32 inputs are admitted. Scalar loads/stores preserve
signed zero and need no GQR profile. No source floating-point computation is
replaced by an idealized distance calculation.

Stack storage is distinct from source tables, globals, lists, descriptor
metadata, actor vectors and matrices. A metadata-only inventory of all bound
world matrix records also prevents candidate input/scratch lists from aliasing
these matrices before projection. Bound world matrices use shared canonical
record reservations, rejecting late helper-to-world ownership reversal. Arrays, typed arrays and promises are
not stack records; null-prototype own-data records are allowed. The shared
helper registry prevents cross-helper reuse. Projectile-root's declared
stack/profile identities and immediate nested displacement are now included
in its metadata-only alias inventory; getters are never invoked. Reached
projectile stack owners use the same shared claims, preventing late reverse
aliasing after a target projection has retained its stack.

Caller/candidate completeness and caught-reentry checks continue across every
new read, metadata call and store. This gives no scheduler authority and does
not recover an incomplete actor or frame. The unchanged optional route still
uses the same genuine outer target-preparation composition.

The next bounded work is live source PSVECSquareDistance arguments and its
paired load/arithmetic schedule, then the authenticated nearest-candidate loop
and final target stores. Other target-dispatch entries, real list production,
full six-actor hydration, mandatory outer predecessors, complete projectile
flight/collision/damage and production browser activation remain open. This
is synthetic offline integration, not `MATCH`, hardware parity or playability.
