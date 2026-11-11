# Browser tier-size presentation

The browser now carries a simulation-owned live model size through battle observations
to each Three.js actor container. Default size remains one. Setting an absolute parent
scale preserves imported model normalization and current size across deferred loads and
morph replacement; it does not mutate cached source models or advance on render sync.

## Source and scope

- `docs-site/public/chunks/chunk_0008.c:4493–4517`,
  `refresh_actor_param_tier_table`: the tier row writes size target `+0xb8`.
- `chunk_0007.c:3674–3712`, `zz_005bab8_`: expire the size contribution, then
  move live scale `+0xb4` by a fixed additive step toward the target, clamping at
  it. Copy live scale into the uniform transform `+0x58/+0x5c/+0x60`.
- The committed `research/decomp/movement-hit-decode-2026-07-04.md` §1 records
  the step as 0.05/frame. That extraction has not been independently rechecked
  against the retail literal `FLOAT_80437420` here. The code labels that numeric
  value accordingly; the additive/clamped mechanism is directly source-backed.
- The ordinary scale path's `+0x7c9 == 0` gate is not represented in the browser.
  Scripted override scaling, descriptor-specific tier clamps/alternate tables,
  model-scaled collision, live-scale damage calculation, and animation-rate scaling
  are not claimed by this change. Existing target-based physics/damage remain as-is.

The integration test also found that the production bridge's absent optional tier
observer left Hero X's family callback as a no-op. The bridge now commits the tier
writer even without an observer, and still calls an installed observer exactly once.
Previously claiming that the production Hero X already changed its movement/damage
through this callback was incorrect: that was only true of other paths such as the
generic fallback or explicitly supplied callback setups.

## Reproduction

`node scripts/run-battle-scene-size-selfcheck.mjs` exercises both STAR HERO and
PLANET HERO in real battles. Ordinary `PlayerInput.special` reaches ROM ownership,
the authored stream reaches the tier writer, and the resulting observation drives
actor scale to 2.6. A separate fixture injects the family contact seam for exact
writer/expiry tests. This does not establish collision-contact parity: the browser's
stream part-state event is sufficient to trigger that branch.

The tests also cover the default scale, one simulation-owned step, no wall-clock or
repeated-sync advancement, both size directions and expiry, deferred model/morph
installation, normalized child transforms, source/peer isolation, and observer
exactly-once behavior. Hit grow/shrink accumulator state is injected, not claimed as
an end-to-end projectile status test. The suite runs from the existing morph
selfcheck, hence from `verify:contributor`.

`SIZE_TEST_BASE_REF=c8f7889 node scripts/run-battle-scene-size-selfcheck.mjs`
loads the old bridge and presentation code and fails at the missing Hero X runtime
writer. No browser visual acceptance or retail-byte-exact parity is claimed here.
