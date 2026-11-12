# Teleport Ninja ordinary X: bounded source route

Date: 2026-11-12. Baseline `eb434441`, matching the live PR51 tree. Original DOL/PZZ reads were numeric-only and read-only. No original asset files were copied or published.

## Scope and visible change

Only `pl0005` fresh ordinary X, exact ground action2/v0 and actual jump-then-X action2/v4, uses this route. Switching Ninja, Double Ninja, other posture variants and the legacy charged payload remain separate.

Before this lane, the browser's generic X-charge branch swallowed the ordinary press. Real ground/jump X, held for1/30/90 updates, never called the family driver. Even a one-update release became a generic type5 special; Teleport Ninja did not teleport at all. The dormant family transcription also had three source errors: it immediately moved the actor to the computed destination, treated actor phase1 `146ed8` as a spawned child, and interpolated toward the motion vector instead of destination9c.

The admitted route now preserves a separate destination, carries the actor during setup, hides it during travel, restores it for recovery and protects its defensive shape for the authored action. A stationary ordinary X has no invented movement toward a distant enemy. Movement supplies the source own-history displacement. There is no damaging actor HIT or projectile child. Short release does not fabricate a charged payload.

This is not full Teleport Ninja, charged-special, original terrain, target geometry, animation layering or instruction-level numerical parity.

## Original action and arithmetic

Source `ghidra-export/chunk_0038.c:754–883`: action2 dispatcher `146d5c`, pl0005 phase table `8033e584`, functions `146dcc`, `146ed8`, `146f6c`, `147094`. Actual input resolves ground record `8033e9b8` action2/v0, air record `8033e9c8` action2/v4. Their ordinary press is source command type2.

Fresh source numeric constants: setup4, travel16, recovery2, fallback50, aimed distance800×modelScale, interpolationf32(.1). `66530(45)` sets movement cue5e4=45, flag87=1 and control40.

1. Phase0 sets timer4 and saves control40 in airLatch54a. It computes motion=position−own saved5e8. If recent-melee timer144 is not positive or captured targetcc is null, destination9c=position+50×motion. Otherwise destination=position+normalize(target518−position)×(800×modelScale), and airLatch40 is forced. Position is not changed by destination calculation. It calls66530, debits cell2 once and ignores that body's return, then calls phase1 **in the same dispatch**.
2. Phase1 emits feedback9, sets272bit2, adds the unscaled own motion, probes677b0 and subtracts dt. At zero it enters phase2 with timer16 and cueF2. Thus normal admission leaves setup timer3.
3. Phase2 emits feedback9, sets272bit2, writes82=0 and interpolates toward9c, then probes and subtracts dt. `46588` uses separately rounded products: f32(f32(scale×destination)+f32(f32(1−scale)×current)), with scale=f32(f32(.1)×dt). It is not a fused current+(destination−current) formula. At zero it enters recovery timer2, zeroes horizontal speed/deceleration and vertical velocity, restores descriptor gravity, writes82=carriedSlot96+0x41, starts recovery, emits feedback10 and cueF2.
4. Phase3 keeps272bit2, ticks the recovery stream and subtracts dt. At zero it clears only272bit2,73f and action bits, then chooses ground idle or air return from control40. There is no new20-frame action lockout.

The SDK normalizer6ebb4 returns[0,1,0] for zero magnitude. The pure engine accepts an explicit in-place normalization hook; production uses f32-rounded Math.hypot normalization. SDK reciprocal-square-root rounding is not claimed.

## Recovery bytes and source samples

Original family bank `8033d5c0`, descriptor bank `8033de20`:

- g0s0 at8033d68e: `010000020a000000 02ff000000000000 0300000000000000 0000ffff`.
- g0s13 at8033d786: `01000e010a000000 02ff000000000000 0300000000000040 0001ffff`.

The final2/1 arguments to4beb8 override **blend2/mode1**, not start2/rate1. Float−1 retains authored start0. Recovery play seeds blendElapsed=entrydt and total=f32(2+entrydt). Both streams reset P0/aux/6e8/6e9, dash/face and71d; ground posture becomes0, air posture40. Opcode01's original support query remains a host boundary.

Metadata0/0 at8033deb6 maps MOT0/0 with loop flag; fresh original AOBJ end140. Metadata0/14 at8033dfb2 maps MOT0/24 nonloop, end1. Both normal dt1 and dt.5 recovery actors leave after two duration units while frame0 is still held. The implementation binds that bounded recovery sample and does not claim an independently reusable complete looping stream interpreter. Source animation epochs use the existing renderer playhead mechanism, so asynchronous clip loading cannot free-run the recovery pose. The hidden interval comes from82, not an animation or visibility opcode.

## Input and ammunition

Original X descriptor802d3910 words `[1,0,0,1,0400,0]` maps a raw X press to one update of5d4bit80 and69b98 type2. Source686f0's X bank650 has threshold descriptor18c=120. Ramp644 increases by1/update until10, without adding bank on update10; subsequent held updates add source float at **offset768**, not literal768. Default rate1 reaches full bank after130 held updates. Paired6fc multiplies the already1.5 source rate by10, giving15. Release checks readiness before subtracting2×base768; active type5 and58ebit20 clear bank/ramp. The existing audited sourceAmmoRefillRate supplies5a378 status/burst rate, separate from animation dt. Global input suspension, arbitrary family descriptor changes and every command-state modifier are not newly modeled.

Fresh ordinary input is not deferred into a later move when held through interruption. A genuinely ready type5 release retains the previous generic action3 payload and tuning; that payload is explicitly not restored source charged teleport. Only its input qualification is source-backed here. The retained fallback still spends one X unit; its pl0005-only bookkeeping now uses the same cell2 debt helper so a bare decrement is not undone by the next refill update. This preserves the generic policy, not a source charged-ammo claim. Other X-charge families keep their existing behavior.

Original pl0005 stats802df17c: X maximum/current2, refill type1, period180. Source562b8 maps the second weapon stats segment to cell2; browser cell1/HUD aliases it. Original family preupdate145864–90 clears58ebit4 and sets it when signed current cell2<=0;69b98 rejects type2 when that bit is set. The production ordinary gate therefore rejects empty ammunition. The later146dcc consuming call intentionally ignores failure, as tested by a pure denial fixture. Each successful debit adds180 to source refill debt; the existing incremental source refill derives integer ammunition from debt, without double-ticking the alias.

## Runtime boundaries

- `teleportXEngine.ts` is an independent four-phase engine. `teleportX.ts` binds actor fields and scoped input without changing `rom/actor.ts` or replacing other family engines.
- Captured target UID is fixed at admission, with the same living target's position refreshed; R selection does not replace it mid-action. Original target HIT centers and visibility subtleties remain the existing host approximation.
- Source144 is a recent-melee timer: initialized0, set8 by146560 after1d9&0x10, decremented while positive by the family update. The new adapter exposes/decrements its explicit runtime seam. The existing host melee producer is not newly mapped to that contact bit; aimed destination tests therefore label their positive-timer fixture rather than claiming an actual combo unlock.
- `sourceDefenseDisabled` represents272bit2 defensive registration exclusion. Dedicated and generic live hit paths skip it before accepted contacts/history, and the audit collision body list excludes it. It is not an arbitrary invincibility timer or a change to unrelated death flags. Cleanup/interruption/form change removes the owned exposure.
- `sourceHidden` represents82==0. The renderer hides the actor group even while its model loads, restores on recovery/interruption, and lets death presentation own visibility. There is no guessed original teleport particle/model asset. Feedback9/10 are observable counters; their original presentation/RNG is unbound. CueF2 uses the existing cue hook.
- Setup/travel use the existing host677b0 motion/ground probe, followed by bridge bounds/off-mesh guards. Original geometry, support anchors, exact wall behavior and pose matrices are not restored. The source engine is tested independently of those approximations.
- Recovery is center-clip presentation, not original layered pose/blending fidelity. The host90-update ceiling is a safety guard, not an original timer. Other unadmitted legacy Teleport-family paths remain unchanged and are not a source-parity reference.

## Verification

Durable tests:

- `teleportXEngine.selftest.ts`: same-call phase1, exact4/16/2 order, ignored body debit result, own-history versus aimed destination, f32 interpolation, visibility/defense phases, recovery overrides and live hooks.
- `teleportX.selftest.ts`: ten-update ramp,120 bank threshold,768 and paired-rate behavior, release-before-decay, reset gates, explicit aimed/zero-vector fixture and owned cleanup.
- Independently authored `teleportXBattle.selftest.ts`: real press/jump/movement/hold/release/repress, source records, source phase timing, ammo/depletion/incremental refill, true-charge fallback separation, real input-created mine rejection without history consumption then accepted post-cleanup damage, captured lifecycle, interruption/death and neighboring families.
- `romCollision.selftest.ts`: updates only the obsolete direct pl0005 admission fixture to real input and observes its source677b0 host-probe boundary; Switching's old route remains isolated.
- `battle-scene-teleport.selfcheck.ts`: hidden placeholder and late model, render pause, recovery/interruption/death restore and repeated cleanup.

Focused actual-input, pure, renderer and typechecks pass at the reported checkpoint. Full contributor/matching/oracle checks are reported separately after running against the final tree. No actor-field map regeneration is needed because `rom/actor.ts` is unchanged.
