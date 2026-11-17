# Finite non-flat terrain siblings, 2026-11-15

## Evidence and scope

The distinct `query8003d6e4` height query and `queryNormal8003de80` normal
query now admit finite non-flat floor normals, including negative and nonunit
nonzero Y. They retain their own implementations. Neither routes through
`queryHeightNormal8003e0a8`; that already-admitted query body is unchanged.

This change uses checked-in detailed derived reports and source only:

- [Terrain query evidence](terrain-query-evidence-2026-11-13.md), selected
  `8003d6e4/640`, SHA256
  `3788a13d2282f6b5ae753eb0d7f29c13289f305f35665a0122ce54e8e1fca7b3`.
  The report records 158 decoded instructions with only the two LR save/restore
  instructions omitted. Its plane and selection sections preserve normal
  X/Z/Y capture, the six separately rounded operations, three accumulators and
  fresh final bounds. No omitted LR operands are invented here.
- [Terrain orientation evidence](terrain-orientation-evidence-2026-11-13.md),
  selected `8003de80/552`, SHA256
  `23cb1653c3d6d0dadb77a3e877433ec7a52365e3175e487699c8db5d3dc29faf`.
  The report records the complete 138-instruction selection as part of its
  larger selected chain, including the different vertex-load schedule and
  preserved X / best-height / Y / Z candidate stores.

The original derived JSON outputs for these two selections were not retained
in this restored checkout. This is reuse of those detailed reports, not a
fresh complete-operand reconstruction or authentication. No archive or DOL was
opened, no evidence reader was rerun to recover missing outputs, and no new
selection, game payload read, extraction or retail verifier was introduced.
The reports explicitly distinguish source evidence from the previous host
flat-only restriction. This remains synthetic offline source-runtime work,
not console execution, original-DOL matching or gameplay parity.

## Arithmetic and distinct query behavior

Only the three flat-normal guards in each sibling's existing plane body are
removed. The existing finite binary32 helpers retain RN=00, NI=0, gradual
underflow and signed zero. Each containing triangle captures normal X, Z and
Y before multiplying. X*dx1 and Z*dz1 are separately rounded; vertex1Y is
loaded; those products are added; Y*vertex1Y is separately rounded and added;
the numerator is divided by captured Y with exact rational nearest-even
binary32 rounding. No FMA, normalization, square root or reciprocal estimate
is substituted. Reached nonfinite operands/intermediates/results refuse.
Positive or negative zero Y refuses at the reached division, after preceding
normal captures, products, vertex-Y load and sums; an earlier failure wins.

`3d6e4` retains its original-clearance/entry-H maximum selector, independent
best/minimum/maximum updates and fresh final L/H comparisons. `3de80` retains
its default-normal stores before bounds, strict height/ceiling thresholds,
best<=height later-tie behavior, no minimum/maximum fallback, and in-range
return1 even when no floor qualified. Both preserve their different vertex
load order and lazy later edge tests. Ceiling+24 and+20 still require separately
read genuine empty lists. Nonzero supporting contact remains unsupported.

## Caller scratch and ordered stores

The normal-only public signature still accepts caller-owned `SourceJointVector`
storage. No new brand, persistent result or actor field is introduced. Before
each default or selected X/Y/Z store, the query checks known actor/history/global
owner metadata and canonical position/saved-position identities. It then uses
captured intrinsic descriptor operations for a final admission pass and the
actual data-property store. A stale observable descriptor cannot invoke a newly
installed setter, conceal readonly/deleted storage or permit adoption into a
known owner, even at final Z. Completed stores remain on any later refusal.
The best-height update still occurs strictly between selected X and Y stores.

These are metadata checks, not source-scalar reads or early traversal of terrain
layers. The existing caller contract still requires stable non-proxy,
non-source-owned scratch. It does not prove arbitrary object-graph separation
or search unread triangle/vertex storage for aliases. Direct queries remain
usable for later independent invocations after a repaired failure. Enclosing
frame/action failure guards retain their existing no-replay behavior.

## One sloped floor through the genuine action

`runAllSlopedDoubleGroundCompositionTests` supplements, rather than replaces,
the previous flat-prefix/non-flat-action regression. One explicit triangle
covers both points, with vertices `(0,4,0)`, `(0,-11.625,1000)` and
`(1000,-3.8125,0)`, and actual normal `(1/64,2,1/32)`.
All bytes and canonical owners are established before the first query.

The unchanged pre-action actor starts at `(101,2,300)`. Real `3d6e4` and
`68e4c` store Y=`-1.4765625`; it is not reset. Genuine Double subtracts its
existing saved target Y=`-2`, scales by the actual binary32 0.95 constant,
and gets motion Y=`0.49726560711860657`. Actual carried position becomes
`(197.89999389648438,-0.9792969226837158,300)`. The same sloped plane at that
point is `-2.2335939407348633`, so genuine `3e0a8/677b0` returns no-contact.
The existing nonnull stream continues through actual DAT/AObj/FObj setup.
Negating all normal components gives the same plane with negative nonunit Y.
An uninterrupted `55568` invocation reaches the same real stream continuation,
then retains its honest missing-`4c0` boundary; it is not a complete frame.

Contact and arithmetic-failure witnesses preserve the exact reached source
prefix and block replay. Zero-Y and early overflow refuse in the prefix before
its height store. Contact is reached after the native height write and genuine
motion, before stream/config/landing work. A second arithmetic witness uses
normal `(2**121,2**125,0)` and vertices `(0,0,0)`, `(0,0,1000)`,
`(500,-31.25,0)`: the real prefix writes finite Y=`-6.3125`, actual motion
carries Y to `-10.409374237060547`, and only the later `3e0a8` X product
overflows. Its completed action effects survive and the same saved selectors
cannot be replayed. No actor reset, cleared control bit,
mid-invocation terrain mutation or fabricated query/ground callback supplies a
successful continuation.

## Honest secondary orientation boundary

`runActorWorldNonflatTerrainBoundarySelfTests` makes genuine `3de80` return a
sloped normal, including negative nonunit Y, and then runs actual secondary
`4784c` through the existing world/matrix owners. It reaches real `45918` and
refuses at its separate flat-normal domain. Earlier matrix translation X/Y/Z
stores survive exactly; basis and later descendant work remain untouched.
Neither `orientTerrainMatrix` nor its estimator/constructor domain is broadened.

## Verification

`runActorTerrainNonflatSiblingQuerySelfTests` is exported and wired into the
existing terrain aggregate. It covers X/Z slopes; signed/nonunit Y; exact
threshold bracketing; separate-round cancellation; subnormal product/division
ties; signed-zero heights and normals; later best/min/max ties; fresh final
bounds; overflow at each plane operation; zero-divisor timing; distinct vertex
loads; lazy edge rejection; captured normals without reread; and default/selected
partial stores against accessor, readonly, deletion, adoption and canonical
vector changes, including the last observable identity-check race.

Implementation-focused checks run the terrain/grid, cue0 lifecycle/tail,
control40, joint-matrix/vector-byte, world, transform-history, Double action,
frame lifecycle, ground/stream, prior nonflat, all-sloped and phase1 regression
suites. Strict combat TypeScript and `git diff --check` are separate checks.
The coordinator independently runs publication/aggregate gates; these focused
checks alone are not a claim those broader gates passed. No landing, general
orientation, complete frame, world hydration or retail playability is claimed.
