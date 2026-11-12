# Arrow Ninja and Shijima X audit

## Original identity and scope

The source constructor `800a2684` is a distinct thrown child, not a request for
an ordinary B projectile. It accepts Arrow Ninja (`pl0002`, row0) and Shijima
(`pl000b`, row1). Qualifying contact creates a separate, fixed-anchor tether.
This work does not introduce a universal same-frame HP suppression gate; see
`collision-hit-gate-audit-2026-11-12.md`.

Source references are `docs-site/public/chunks/chunk_####.c`:

- `0022:639-783`: action2 entry, source position-history carry, airborne recoil,
  stream contact, source weapon-cell2 consumption and constructor dispatch.
- `0015:7346-7568`: constructor, flight, capture eligibility and retirement.
- `0015:7634-7681`, `0016:1-295`: fixed-anchor tether creation, initialization,
  lifetime, target eligibility, constraint and display length.
- `0012:3068-3120`: source aim initialization, retained target conditional on
  inherited owner+d0 mask4.
- `0009:1338-1339,1812-1816`: target range flag, inheritance and status clearing.
- `0012:3354-3392`, `0006:6964-6996`: average simultaneous positional corrections,
  apply after actor update with floor constraint, then clear the accumulator.
- `0008:4865`, `0009:2995-3046`: tether mash value is this frame's relevant input
  rising-edge population count, not the held button count or cumulative presses.
- `0006:6774-6823`: target capture mass is actor-data f32+0x98, scaled below a
  threshold, plus attached/riding actors. Metadata weight is not a substitute.

## Original numeric evidence

Read in place from the user's GG4E08 disc. Header DOL base is `0x1f700`.
DOL section file offset `0x3aec40` maps to RAM `0x80436a20`, length `0x6ae0`.
No executable or asset bytes are included in this change.

- `80438010`: float55, arrow speed.
- `80438014`: float50000, strict capture mass ceiling.
- `80438018`: float100, target-distance release parameter.
- `8043801c`: float3, homing turn parameter, interval literal2.
- `80438020`: float1, base tether duration decrement.
- `80438024`: float1200, tether duration.
- `80438028`: float600, tether allowed separation.
- `80438030`: float0.0010000000474974513, visible-length threshold.
- `80438034`: float0.009999999776482582, hidden zero-length Z scale.
- `80438038`: float140, rendered length divisor.
- `8043803c`: float0.
- `80438040/48/50`: doubles0.5/3/4503601774854144, source math/conversion.
- `80433a30`: model shorts12,12. These are owner-local, not global bank12.
- `802b0cb4`: vector(0,1,0), initial reference up.
- Flight lifetime600 and spin step0xf000 are source literals.

Both borgs' HITkind0 uses shape0, extent(5,0,0), flags1, damage record0.
Their family damage table `8030e1b8` record0 has base HP5, down35, balance35,
combo35, strength1, reactionflags1, reactionvariant5, directionmode2, pitch24.
Final damage still passes through the shared source-derived damage calculation.

Tether model is global effect-bank37, already present in the browser's committed
mesh cache. Its anchor is the victim contact transform at capture, not the owner.
Its second endpoint follows the victim. Original arrow owner-local model12 and
endpoint effects are separate presentation work.

## Verification and remaining limits

Implementation verification and exact final scope are recorded below when complete.
Original articulated target/attachment transforms, global control masks, riding
mass aggregation, attraction fields, and full original-console timing are not
proven by a host unit test. Never label this lane complete game parity.

## Input, stream and eligibility binding

Both original X stat segments are capacity8, refilltype0/count300. Source
cell2 is the second HUD weapon cell, not a third unlimited weapon. Exact ground
command8030e140 uses cue44/action2/variant0; air8030e180 uses cue45/variant4.
Phase0 uses position minus own +5e8 history, not the lock target position.

Group4 streams8030dcd4/8030dd28 encode blend3, start0, waits at animation
frames9/17/21/34, then terminal animation completion. Direct original motion
read gives AOBJEndFrame45 (not exported frameCount46). A satisfied wait parses
its next block; when no new playAnim opcode occurs, the parser advances animation.
A host elapsed-frame list is not equivalent to this wait/animation clock.

Original actor data for both borgs gives enemy and ally tracking range5500
(f32+80/+84) and mass90 (f32+98). The common mass scaling threshold is50000.
Runtime mass data can be derived from the existing committed198-profile
`borg-gauge-init-pldata.json` numeric words, without copying assets.

Shijima duration is independently verified from its own `pl000b.pzz` member3,
not assumed from Arrow. Both clips have20 AOBJs with end45 and flags0.
Direction-mode table `802d0d44[5]` is verified as `800463ac`; tether rendering
transports its previous up basis rather than resetting to world up every frame.

## Implemented host contract and tests

- Both real X input routes now spend the aliased source cell2/HUD X magazine,
  deny late depletion, retain ordinary type0 refill, and sample input while busy.
- Target-independent own-history motion removes the distant-target teleport.
  Ground/air admission and source-clock contact replace the generic event timing.
  Neutral press-inclusive fire is frame26; ground recovery is frame50.
- Dedicated arrow identity, launch speed55, lifetime600, captured target,
  range5500 tracking, turn3 degrees every2 updates, owner invalidation and
  source HITkind0 damage binding replace the generic B fallback.
- Eligible contact creates the fixed anchor, immediately runs its source init
  update (1200 becomes1199 with no mash), and maintains the600-unit constraint.
  Fresh relevant input edges accelerate duration decay. Corrections average
  and are queued for application after the victim's next actor update.
- Tether uses existing global model37, direct team material selection, transported
  basis, exact length scaling and zero-length hiding, with independent materials
  and shared geometry lifetime. No newly extracted asset is published.
- Regression tests cover real ground/air X, eight-charge exhaustion/refill,
  empty/late-denied/interrupted attacks, held/repressed busy input, no teleport,
  authored stream timing, real collision/capture, target changes/loss, source
  flight and lifetime, actual mash input, fixed anchors, mass boundary/scaling,
  owner retirement, immutable observations and other projectile families.

Explicit remaining approximations: animated matrix `ae4` attachment is represented
by a host root/optional attachment seam; original owner-local model12 is absent,
so flying arrows retain an explicitly generic visual. Target collision uses host
root geometry; source aim-scramble6b8, global control masks, some fusion/control
eligibility, mounted mass sums, attraction fields and endpoint particle/audio
presentation are not fully modeled. Degenerate basis handling and trig use host
safeguards rather than PPC floating-point parity. Queued corrections follow the
host frame schedule, not a complete original object-slot scheduler recreation.
No GPU/visual gameplay or original-console side-by-side validation is claimed.

Validation: typecheck, full combat lifecycle (including the new real-input Arrow
suite), Arrow/Beam/Gatling/Revolver/Powered renderer checks, ROM checks, game build,
52 matching-decomp negative controls and oracle81 pass/0 fail/1 expected private
snapshot skip. Local contributor aggregate stops at the same three absent sparse
HUD images; all subsequent aggregate stages were executed separately and passed.
