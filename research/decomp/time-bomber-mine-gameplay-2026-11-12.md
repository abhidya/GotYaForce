# Time Bomber mine gameplay integration

Local continuation of reconstructed checkpoint `b22f8e0f`. This is not published
and does not claim complete game or console parity. No original assets are added.

## Source-supported scope

- Family 29 post-action callback `801304b8` handles a raw B press independently
  of X ownership. Resource cell 0 has ten units and is returned by children,
  rather than passively refilled. The shared actor `+694` timer is set to `4+dt`
  even on an empty press, decrements only outside action ownership, and is reset
  by action admission. Successful allocation invokes mine type 2/appearance 10.
- Child `800e06c4`/`800e075c` initializes in the later same-frame child pass.
  It begins moving and aging on the next frame. The existing isolated lifecycle
  supplies drift, bob, retirement, delayed resource return, and final free.
- Appearance row 10 transforms its local offset through joint 8 into the child
  physics origin (`80047aa4`). Launch direction separately uses joint 1's +Z.
  The adapter uses the verified static bind-pose offset, not animated matrices.
- HIT 15/remap 8/damage 9 supplies direct HP30 and durability1. Explosion19 has
  an independent attack identity and HP20 record; a direct contact does not
  guarantee an additional twenty damage because host immunity may intervene.
- Original collision lists retain both directions of eligible mine-to-mine contact
  for the current frame even after durability reaches zero. Retirement is deferred
  to the next child update, not used to suppress the other registered attack.
  Evidence: `chunk_0003.c` 7168–7310, 7473 onward, 8210–8225, 8397 onward;
  `chunk_0004.c` 6832–6860.
- Same-owner receiver admission requires known source self-contact eligibility
  on either attacking child or mine, not merely damage flags. Drift is disabled;
  bob is enabled. Unknown projectile eligibility remains conservative.
- Retirement resolves the original owner UID and current resource cell. A
  same-UID form change may receive the returned unit; a replacement UID cannot.

## Explicit limits

The host still approximates collision shapes, swept impacts, terrain queries,
fixed-step ordering, signed-angle sine, RNG ordering, and static attachment pose.
The source `83714` query is not decoded into equivalent geometry. Beam pulses,
tethers, melee and special/status receiving paths are not claimed. Unknown
same-owner attacker markers can reject contacts that the original would admit.
Spawn/death B eligibility is conservatively excluded pending full outer-state
mapping. Allocation failure is injectable; the host has no original pool limit.
The mine mesh/animation remains a generic owner-local placeholder, never an
unrelated global effect with the same numeric model index. Explosion uses the
existing shared effect bank. Browser visual comparison is outstanding.

## Verification

- All ten mine Battle scenario groups pass: press edges/initialization, ten-live
  resource conservation, ground/air/running X coexistence, retirement/identity,
  observation-only pause, contact/bounds, enemy projectile damage, allocation
  failure, wall/shared-timer reset, and collision-order independence.
- The order regression reverses the mine list and also puts a damaging enemy
  projectile before the mine's own registered attack. Both pass. Position and
  lifecycle injections are explicitly fixture setup, not console captures.
- Full `verify:contributor` passes, including typecheck, HUD/frontend, existing X
  lanes, lifecycle, renderer regressions, importer tests, and production build.
- Existing oracle harness: 81 passed, zero failures, one expected skip because
  private MEM1 snapshots are absent. This validates existing harness coverage,
  not an original-console Time Bomber mine replay.
- Renderer regression verifies owner-bank isolation, no render-only aging,
  placeholder retirement, and shared explosion asset identity. It is not a
  screenshot comparison or proof of original animated presentation.
- `git diff --check` passes. The existing large-bundle warning remains.

Final local logs are `mine-contributor-final.log` and `mine-oracle-final.log` in
this reconstruction workspace's parent directory. Earlier intermediate test
failures are superseded; no remote publication or deployment was attempted.
