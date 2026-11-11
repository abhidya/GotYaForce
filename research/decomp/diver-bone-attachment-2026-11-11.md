# Diver aura visual source-bone attachment

## Evidence and bounded implementation

The read-only original model-wrapper trace for pl0805, pl080d and pl080e found
this source-slot assignment in depth-first JOBJ traversal order:

`[0,1,2,3,4,5,6,7,21,8,9,10,11,22,12,20,13,14,15,16,17,18,19]`

Source wrapper-table construction is `zz_0067e18_`, chunk_0008.c:4204–4273,
using each wrapper's offset+8 slot assignment; root selection is `zz_005380c_`,
chunk_0006.c:6589–6607. Therefore the aura row's source bone slot 12 resolves to
**DFS traversal 14**, not DFS12 and not the exported name `JOBJ_12`.
The source aura update copies the transformed position, not the entire bone
transform (`FUN_80121694`, chunk_0033.c; preceding child initialization is
`FUN_8012151c`). See [child evidence](diver-aura-child-2026-11-11.md).

Original model SHA-256 identifiers from the read-only verification:

- pl0805: `7eea4252a2c8b7cb849821b7f7a4ef40fc292f023f3a75310e4c3be2dd9aa125`
- pl080d: `da7e89fc5f8a786bdaed3c0069594d4beaa0fde9c43f7beb8be9643adc1fdfdc`
- pl080e: `921e4d74890de4684a0c73ab8abc40591fb268c055108b0a7a884059b496b05d`

The renderer now shares its existing exporter-tree reconstruction between mesh
reparenting and aura attachment. It follows child order rather than interpreting
JOBJ name suffixes. Only these three known Diver forms with 23 reconstructed
joints enable the mapping. The resolved node belongs to the current loaded
presentation and is cleared with that presentation; asynchronous obsolete loads
cannot replace it.

After each animation-mixer update, the aura copies the joint's world translation
and converts it to battle-root local coordinates. It remains a sibling of the
owner, retaining its independent rotation and observed visual scale. Imported
normalization, owner scale and facing enter the position exactly once through the
normal scene graph. Sync also resolves the current position for callers that have
not yet advanced animation. Missing models/joints, pending loads, form mismatch
and retired owners use the explicit observed root position without a guessed
bone offset. Existing child disappearance still owns visual teardown.

## Approximation boundaries

This improves **visual positioning only**. Combat still uses its existing
root-centered max-extent spherical approximation; a bone-anchored visual is not
proof of source-exact hit geometry. No combat observation or hit behavior changes.
This supersedes only the visual anchor limitation in the earlier child document.
The subsequent [source-backed pulse](diver-source-pulse-2026-11-11.md) uses decoded
constants and signed-short conversion, with explicitly approximate libm behavior.
No complete bone transform is inherited. Existing material animation, timing and particle-tail qualifications
remain. No original model assets were added to the repository or uploaded.

## Verification

The existing Diver scene selfcheck now also uses synthetic exporter-shaped rigs
with deliberately permuted names, branched topology and a distant DFS12 decoy.
It verifies DFS14 selection, normalization once, owner yaw/size, translated and
rotated battle root and nonuniformly scaled ancestor, independent aura
rotation/scale, real AnimationMixer motion without an intervening simulation
sync, pending loads, all three supported forms, stale asynchronous morph results,
missing skeleton, retirement and clear. Shared mesh reparenting retains its rest
pose and does not disturb the joint traversal. Synthetic rigs verify the scene
math/lifecycle, not original-asset visual parity.

Passed: root `pnpm typecheck`, complete `run-battle-scene-morph-selfcheck.mjs`
(morph, animation lifetime, retirement, load failure, size and Diver scene), and
`pnpm test:render-disposal`. Browser rendering with user-disc assets remains a
separate visual check; these CPU scene tests do not claim that check.

Semantic negative controls bundle the same suite with runtime-only mutations.
Selecting DFS12 instead of DFS14 fails the transformed/normalized attachment
assertion. Moving attachment sampling before the animation mixers fails the
same-frame animated-position assertion. Both controls compile and fail on the
intended behavior, rather than missing imports or type errors.

Independent review also parsed all six existing tracked Diver GLBs (library and
model_00 for each form) in memory: each has one root and 23 joints, with DFS14
resolving to JOBJ_14. This checks actual exported topology, while the synthetic
permuted-name test checks that resolution does not depend on the name. The
independent scene/disposal tests and both semantic controls passed as expected.
The game production build also passes; original-asset browser rendering remains
unverified.
