# G RED-family ordinary B: own-position carry correction

## Reproduced player-visible defect

For RED (`pl0615`), NEO (`pl0629`) and BLACK (`pl062a`), a real fresh ranged B
press selects exact `80365d58`, action0/variant0. Before this correction, a
stationary shooter at Z0 moved to Z−475/−950/−1900 when the locked enemy was at
Z500/1000/2000 respectively. Subsequent decay kept moving it away. The function
incorrectly treated the enemy's position as the shooter's own movement history.

## Source-supported scope

Original `8018d350`, `research/decomp/ghidra-export/chunk_0046.c:5097` onward,
performs phase advance/latch and aim-timer setup, calls `8006d0dc(C1,0)`, starts
the stream, clears control bitsB0, zeros the four physics scalars and pose7c/7e/80,
then computes:

- motion = f32(pos − own5e8), component-wise;
- motion = f32(motion × f32(.95)); literal `8043b124` is bits`3f733333`;
- pos = f32(pos + motion), component-wise;
- ground/revert helper `800679d0`, then accumulator80c=0.

This carry is unconditional, including no target. It is not enemy spacing or a
backward lunge. The browser bridge already advances `targetCache5e8` from the
older own-position sample exactly once per Battle frame, separately from the
current pre-movement `savedGroundPos`. Admission does not advance that history.

The correction is scoped to ordinary action0/variant0 phase0. It retains the
existing startStream-before-zeroing order and uses the existing `groundSnapRevert`
terrain adapter. A dedicated f32 entry constant avoids changing later phases or
unverified movement variants.

## Verification and limits

`gredShotCarry.selftest.ts` checks three families with null/near/distant targets,
stationary and nonzero history, f32 boundaries, source stream/reset/carry/probe
ordering, and the existing unsupported-floor revert adapter.

`gredRangedCarryBattle.selftest.ts` uses real B input for all nine family/distance
combinations, verifies stationary position traces stay independent of enemy
range, and preserves each family's `800c3be0` shot callback and one-cell ammo
consumption. It also covers preceding real movement, a labeled target-loss
adjunct, a support-rejection fixture, near-stage-bound entry and housekeeping
resets. Nine neighboring charge/melee/air/X suites passed focused regression.

This fixes the target-distance teleport; it is not a full
ordinary-shot port. Legacy normal-shot stream timing, repeat/latch input,
projectile `800c3be0`, later motion decay, aiming and host terrain/clamp behavior
still have separate fidelity limits. Directional/posture B variants remain
unadmitted; stick direction must not be mislabeled as original posture subtype.
No assets were added, and this local change was not published or deployed.

Final local `verify:contributor` passed after source review and test freeze,
including TypeScript, renderer/ROM/full combat lifecycle/importer checks and
production build (21.21 seconds). The existing large-bundle warning remains.
