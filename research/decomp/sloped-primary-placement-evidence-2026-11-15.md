# Bounded sloped primary two-bone placement

This activates a one-pass subset of `80047368`, reached through the actual
world traversal and owned correction records. It is not general IK, arbitrary
trigonometry, repeated-frame closure, retail hydration, a completed actor frame,
or a completed port. `27764`, unconditional `0bef4`, and `6d228` remain unchanged.
No new archive/DOL payload selection, raw payload read or extraction was used.

## Inputs and independent arithmetic

The exact witness displacement is binary32 `00000000 3f199999 3f4ccccd`.
It is **target minus parent-transformed captured raw current pose**, not a terrain
normal. The fixtures use zero raw current pose and zero parent translation, so
actual rounded subtraction preserves these words. They do not assume arbitrary
world translations are reversible. The genuine mode0 world rebuild supplies
retained positions `(0,0,0)`, `(0,a,0)`, `(0,a+b,0)` and identity bases, all checked
before the placement. Adjacent raw pose is `(0,a,0)`.

Both retained length pairs `(2,.5)` and `(1,1)` and signed bend bytes
`253,254,255,1,2,3` are covered. Orientation axes remain exactly `(2,1)`.
`actor-primary-sloped-witness.selftest.ts` records all twelve independent current,
adjacent and retained-end matrices, including every zero sign. Expectations were
computed before source activation by exact Fraction/integer nearest-even binary32
and binary64 arithmetic with a fused correction, not by importing production
numeric helpers or calling host sqrt/trig. The derivation includes rounding-tie
and signed-zero controls. Its source evidence is the existing
[primary schedule](primary-terrain-placement-evidence-2026-11-13.md) and
[orientation schedule and finite seeds](terrain-orientation-evidence-2026-11-13.md).

For the displacement above, all incoming column Mag and X/Y/Z normalization
squares are `3f800000`. The first cross is `00000000 bf4ccccd 3f199999`; its
constructor square exceeds `2edbe6fe`. The second cross is
`3f800000 80000000 80000000`. Each SDK refinement uses seed `3f7ff400`, squared
seed `3f7fe801`, half-seed `3efff400`, correction `40000600` and reciprocal
`3f7fffff`. Scale/Concat finishes with this row-major basis:

```
3f7ffffe 00000000 00000000
00000000 3f199997 bf4ccccb
00000000 3f4ccccb 3f199997
```

The post-orientation Mag uses the **saved displacement**, yielding `3f7fffff`.
It does not measure the now-oriented basis. Thus both retained scalar branches
remain exactly their prior admitted cases: folded cosines `+1,-1` and signed
zero sine complements for `(2,.5)`; cosines `3effffff,bf000001`, complements
`3f400000,3f3fffff` and refined sine `3f5db3d7` for `(1,1)`. No scalar estimate
seed was added. Both real RotTrig and paired Concat operations execute. Folded
bend `+3` has adjacent index4 `80000000`, whereas bend `-3` gives `00000000`.

## Admission and source ordering

Primary retains its old flat `(±0,1,±0)` signed-axis lane. A saved displacement
with nonzero X or Z selects a separately named primary-sloped lane. It shares the
already established bounded SDK arithmetic with secondary orientation, but does
not change secondary admission. Every reached Mag/Normalize selects a seed only
from its actual rounded square in `{.25,1,4,16,64}`. There is no input-vector
whitelist, ideal rotation, arbitrary square-root estimate or early preflight.
The retained bone-pair, two positive sine-square, axis and bend limits remain.

Literal binary32 `.6/.8` reaches X-normalization square `3f800002` and refuses,
after current translation stores but before basis writes. The successful
orientation's next incoming squares `3f7ffffc,3f7ffffa,3f7ffffa` remain outside
this finite domain. Axis dispatch, constructor fallback, nonfinite and denormal
inputs retain their source-position refusals. Unsupported scalar domains can
still refuse after completed orientation, not before already-authenticated stores.

All raw pose/retained coordinates are read before length calculations; transformed
current XYZ stores precede target/axis reads. Normalizations complete before
column-major basis stores, then Scale/Concat, original-displacement Mag, scalar
bending and the two final Concats. Adjacent destination is physical current+0x30,
not the topology-selected skipped node. End is read only for retained length at
placement; later genuine ordinary world traversal may overwrite it.

## Ownership, partial writes and reentry

Focused exports are `runActorJointSlopedPrimaryPlacementSelfTests` and
`runActorWorldSlopedPrimaryPlacementSelfTests`; the full joint/world suites call
them as well. Coverage includes all twelve exact two-matrix witnesses; all nine
normalization-store prefixes; all twelve adjacent Concat store prefixes for each
witness; actual mode0 retained geometry, live correction fields and real matrix
handles; physical adjacency versus topology; current raw pose capture versus late
adjacent raw pose and axes/bend reads; callback-driven topology changes; correction
array/record replacement and alias faults; mapping/pose/matrix owner replacement;
world synchronous effects, same-call poisoning and fresh-call retry.

A confirmed pre-existing primary-only caught-reentry gap was fixed. An internal
check is passed through primary descriptor reads, transform, orientation and
Concat stores; after a descriptor observer catches an inner same-runtime refusal,
the outer operation aborts before the next store. Normal operand/store order and
all earlier writes are retained. Other public matrix APIs retain their existing
behavior. Regression observers cover axis0e, both bend reads, a basis-store lane
and the final adjacent store. These inject through the last public descriptor
observer while returning genuine own-data descriptors, not through accessors or
Proxy inputs. Poison lasts only for the active call. A fresh standalone joint or
world call can retry after explicit input repair; no permanent actor-frame closure
is invented where no genuine frame-to-matrix edge exists.

Focused suites and strict compilation are implementation checks. Full aggregate
gates and publication belong to the separately frozen coordinator validation;
this evidence does not claim those have run merely because focused suites passed.
