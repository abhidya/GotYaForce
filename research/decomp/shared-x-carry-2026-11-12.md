# Shared X startup own-position carry

## Reproduced failure

Actual X for Normal Ninja, Sasuke and Death Borg Alpha II incorrectly moved a
stationary actor backward by475/950/1900 units when the enemy was500/1000/2000
units away. The second update continued the artificial drift. All nine
character/range combinations reproduce the same shared-handler defect.

Original800ff30c (chunk_0028.c:1737) unconditionally subtracts the actor's OWN
saved5e8 position from current20, scales that motion and adds it back. The target
is not part of this carry. Fresh original804392d0 bytes3f733333 are
f32(0.949999988079071). Per-component subtract, multiply and add store boundaries
are rounded. No-target entry also carries own motion.

## Bounded change

Phase0 clears the four physics scalars and pose7c/7e/80, performs own-history
carry, probes677b0 terrain, selects and starts the configured group4 stream,
then clears80c. The existing host terrain adapter is used; no original terrain
solver is claimed. Later phases, aim behavior, stream schedules, callbacks,
backflip physics and family configuration mapping are left unchanged.

Direct decompiled callers800715d4 and801a0434 support the tested Ninja and Death
Alpha II paths. Host shared helper consumers also include nurse-wizard-idol
and wave-b-catch-all mappings that contain inferred stream configurations or
synthetic callbacks. This shared correction does not establish source accuracy
for those other attacks. A decompiler caller search is not exhaustive binary
cross-reference proof. The earlier nn-family-decode report's target/blink
explanation is corrected rather than retained as provenance.

## Verification and limits

Independent real-input coverage checks all nine stationary cases and continued
short traces, actual preceding movement with target/no-target adjuncts, own
position history, exact f32 arithmetic, pose/80c reset and terrain-probe ordering.
Pure tests cover source ordering and boundaries. Full X timing, payload and
original backflip behavior are not newly verified; this fixes startup motion.
No assets were copied or uploaded, and no publication/deployment occurred.

Final source review approved the bounded change. `verify:contributor` passed
policy, TypeScript, UI/renderer, ROM/full combat lifecycle, importer and production
build (20.30 seconds). Existing large-bundle warning remains. No actual browser
screenshot or original-console replay was performed.
