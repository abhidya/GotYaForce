# Finite non-flat height-plus-normal query, 2026-11-15

## Evidence and bounded production change

The genuine `queryHeightNormal8003e0a8` now accepts finite non-flat source
normals, including nonunit and negative nonzero Y. The sibling `8003d6e4`
height query and `8003de80` normal query retain their flat-normal bounds.
The genuine `800677b0` ground probe is unchanged.

This uses only the already selected, complete instruction evidence recorded in
[ground-query-evidence-2026-11-14.md](ground-query-evidence-2026-11-14.md):
`8003e0a8/844`, 211 instructions, SHA256
`4310809c29ad48750521ad16c4e2f47192b2c69b1d3dc357d613870af21d1708`.
Both existing derived snapshot records agree. No new archive selection, raw
binary/DOL read, retail verifier, asset extraction or hydration is involved.
This is an evidence-backed source-runtime implementation, not a new retail
byte-match or console execution claim.

Only the three flat-normal guards are removed from the plane calculation.
The existing exact finite binary32 helpers implement its unchanged RN=00,
NI=0 sequence:

1. Capture normal X, Z, Y from their owned source words, in that order.
2. Round X times the captured first-vertex X delta to binary32.
3. Round Z times the captured first-vertex Z delta to binary32.
4. Load first-vertex Y, then round the sum of the two products.
5. Round captured normal Y times vertex Y, then separately round its sum
   with the XZ result.
6. Divide by captured normal Y with exact rational nearest-even binary32
   rounding, retaining gradual underflow and signed zero.

There is no FMA, normal normalization, square root, reciprocal estimator or
direct vertex-height shortcut. Every reached operand/intermediate/result must
be finite. A positive or negative zero Y divisor refuses only at the reached
division, after prior products, the vertex-Y load and additions. Overflow also
refuses at its own reached operation. No normal component is reread for output.

The actual actor, position, saved position, history, terrain-global and owned
byte-backed layer/list/triangle records remain the operands. Initial clearance,
ceiling order, fresh current/history reads, signed cell arithmetic and strict
edge/height comparisons are unchanged. Best, minimum and maximum keep separate
normal captures; all equal-height ties retain the later admitted normal.

## Caller-local output ownership

`3e0a8` still writes only a fresh branded caller allocation, never a retained
result, actor field or terrain callback. Its default and selected/fallback
stores keep X/Y/Z order and preserve completed prefixes on failure.

The focused review exposed a pre-existing destination race at the observable
own-property descriptor check: a late accessor/readonly change or adoption
into an actor field could occur after that check, including on final Z.
The height-plus-normal path now reconciles known owner metadata and canonical
position identities before **each** output store. Captured intrinsic
own-property operations perform the final metadata/destination check and data
store, so a stale descriptor cannot invoke a newly installed setter. A second
intrinsic metadata pass also catches changes made during the final observable
position/saved-position checks. These checks inspect no new source scalars,
invoke no owner accessors and do not traverse unread terrain layers.

The siblings' output behavior is untouched. Direct queries still permit a
later independent invocation after failure. No permanent query latch was
introduced. The existing enclosing action/frame guards retain lifecycle
closure when their source operation fails.

## Genuine ground and action composition

`runNonflatDoubleGroundCompositionTests` uses the existing genuine ground,
query, actor/history, action, stream and animation owners with explicit
synthetic byte-backed floors. Direct `677b0` calls prove non-flat no-contact
with unchanged actor values and both positive and negative nonunit normal Y.
Independent synthetic planes bracket the strict `top > height` comparison:
above returns native zero, while equality and below stop at the existing
`8020ba78` contact displacement boundary before normalization/slope handling.

The unchanged pre-action control prefix first calls bounded `3d6e4` at
`(101,300)`. The action composition therefore supplies two explicit triangles
in the same cell/list: a flat triangle includes that prefix point, and a
separate non-flat triangle includes the genuine motion-carried action point.
This preserves the existing actor inputs and completed prefix; it does not
clear a control bit, move an actor, replace a query result or mutate terrain
mid-invocation to manufacture success. Actual phase0 then reaches genuine
`677b0` no-contact and continues into its existing signed slot/configuration
and nonnull stream setup. Contact, zero-denominator and overflow fixtures
preserve phase/yaw/motion/position effects and stop before stream/landing work;
the real enclosing action forbids replay.

No complete frame, landing, source-world hydration, arbitrary terrain,
FPSCR state or retail playability is claimed. Nonzero supporting contacts,
nonempty ceiling triangle bodies, `27764/bef4`, and all other previously
unsupported boundaries remain unsupported.

## Checks

`runActorTerrainNonflatHeightNormalQuerySelfTests` is exported for focused
use and included by `runActorTerrainHeightNormalQuerySelfTests`. It covers
X/Z slopes; negative/nonunit Y; separate-round cancellation; subnormal
products/divisions and ties-even; signed-zero results and normal words;
product/sum/division overflow; zero-divisor timing; normal capture/load order;
no output rereads; independent best/min/max and later ties; malformed/nonfinite
and changed source words; partial output writes; stale-descriptor accessor,
readonly, adoption and canonical-position mutations at every store; caught
reentry and independent reuse. Existing flat/sibling/grid tests remain active.

The implementation-focused regression gate also runs the genuine ground
stream, frame-marker, control40 and phase1 continuation suites. Strict combat
TypeScript checking uses `tsc -p packages/combat/tsconfig.json --noEmit`.
The final publishing gate separately runs the full focused/contributor checks;
focused success alone is not a claim that those aggregate gates passed.
