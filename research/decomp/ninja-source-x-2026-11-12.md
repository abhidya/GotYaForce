# Normal Ninja / Sasuke X: bounded source route

Date: 2026-11-12. Baseline: `3babaa4c` (after the actor-map CI repair). No original assets were copied or published. The source auditor read the original DOL and original PZZ/ARC members read-only; this document records numeric facts, not redistributed binaries.

## Scope and visible change

Only Normal Ninja (`pl0000`) and Sasuke (`pl000a`) fresh ground X action2/v0 and actual jump-then-X action2/v4 enter this route. Neighboring Ninja, Powered, Gatling, G RED and other family actions keep their existing adapters.

Before this lane, both Ninjas used a flattened legacy X schedule with callback on tick16, unconditional backflip and no source cell2 debit. Sasuke's generic row3 fallback had five-frame lifetime and generic gravity3, often disappearing against the floor after two updates. The new route has the authored release gate, ground/air recoil distinction, source X ammo, persistent source shuriken and its independently damaging impact. A procedural four-blade shuriken and expanding impact are visible in the browser representation. They are not original model14/effect meshes.

This is not a full Ninja action, animation, attachment, collision, terrain or numerical parity claim.

## Original actor and commands

Fresh original command bytes:

- `802d40e8` ground directions: `[44,3,2,0]`.
- `802d4128` air directions: `[45,3,2,4]`.
- Variant table `802d3c48` has `715d4` in all five entries. The admitted scope remains v0/v4, rather than broadening host posture selection.
- `715d4` calls shared `ff2bc`, config `80433868`: ground stream0, air stream1, callback `715f8`.

Shared phase0 `ff30c`: phase increment; null-target heading fallback; `6d144(C1)`; zero gravity/y velocity/horizontal deceleration/speed and pose80/7e/7c; unconditional carry from **own** `pos20 - saved5e8`; separately rounded subtract, scale by original `804392d0 = 3f733333` (`0.949999988079071`), and position add; `677b0`; choose slot from control40 and increment stream cursor; start maskF/group4; zero80c. The earlier own-history correction is preserved.

Phase1 `ff418`: tick stream, aim, decay/add carry, probe, then authored signed P0>0 advances phase and invokes callback. Collision acceptance is not the trigger. The `b22f4` afterimage path for motion magnitude>3 is not bound; its presentation/RNG effects remain omitted.

Callback `715f8` reads signed dash/state byte `1d0f`, not face byte `1d10`. If nonzero it first sets lock yaw to heading−0x8000, speed10, deceleration0, upward velocity15 and gravity−1. It does not change active yaw. It then calls `6dbe0(cell2,1,true)`; only success allocates `7db5c` row0 for Normal or row3 for Sasuke. Ground release has dash0, so no backflip. Air release has dash32, so backflip. Even a failed callback ammo check occurs after the conditional backflip.

Phase2 `ff4d4`: tick, `67310(1,lockYaw)`, then `677b0`. A nonzero landing result with control40 and negative P0 has priority: clear73f/action bits, cue7, timer4+dt. Otherwise exit only on negative P0 plus direction bits5d8&f0, or source part0 completion. Air return, ground idle or cue7 follows the original floor/control distinction, then timer4+dt. Held X is not a direction input and never creates an automatic second throw.

## Authored stream and animation clocks

`g4s0 @802be5ee`:

- Play4/0, mode1, blend6, start0. Startup P0=0, auxiliary0, flags0; dash0, face1, control40.
- Frame2 sets6e8=2.
- Frame11 opcode08 sets71d=1.
- Frame14 sets P0=1, flags0, dash0, face0, preserving control.
- Frame31 clears control bits4..11; frame34 sets P0−1.
- Wait for ended; play0/0 mode1/blend4/start0; terminal elapsed4.

`g4s1 @802be656`:

- Play4/1, mode1/blend6/start0; same startup state; opcode08(1) immediately.
- Frame1 sets6e8=2.
- Frame14 P0=1, flags0, dash32, face0, preserving control.
- Wait ended; play0/14 mode1/blend8/start0; P0−1; terminal elapsed8.

There is no actor HIT opcode in either stream. Source opcode08 is not cosmetic: when control40 is set, value1 forces the original support query offset6d0 to zero. The adapter exposes the exact71d/forced-zero shadow. The original animated support query is unavailable in host terrain. Opcode01 recovery clears71d; the no-longer-forced support offset is explicitly unbound rather than retaining stale zero.

Fresh PZZ485 and495 results:

| Metadata | Motion clip | Raw end | Descriptor flags |
|---|---|---:|---:|
|4/0|4/0|45|1 nonloop|
|4/1|4/1|40|1 nonloop|
|0/0|0/0|120|5 loop, rewind0|
|0/14|0/24|1|1 nonloop|

The descriptor byte5 is **flags**, not playback rate5. Original raw AOBJ flags are0. All source clocks advance at ordinary actor dt. Root0 recovery AOBJ is null; original roots1..19 agree on the recovery ends.

Mode1 seeds blendElapsed=dt and total=blend+1, holds frame0 during blend, and adds only overflow on completion. End marking remains suppressed on that completion call. Waits test the old clock before advancing. At dt1, create is call0; release frame14 is interpreted on call21, ground recovery begins52 and completes57, air recovery begins47 and completes56 if the actor does not take its landing exit. Independent dt0.5 traces are tested too. Renderer source samples use the existing per-clip sample-rate/epoch support; frame values are not converted through a guessed universal animation rate.

## Ammo

Fresh original stats rows `802dea74` (Normal) and `802df884` (Sasuke) give X maximum5, refill type0, period300. Original `562b8` maps the second weapon stats segment to runtime cell2, not cell1. Browser cell1/HUD is an alias of that source cell2. Depletion starts a300 source-rate bulk refill; individual shots do not refill early. Entry checks availability but does not add a second debit. The callback consumes exactly one.

## Shuriken7db5c rows0/3

Original table `802d6d68`, stride0x38. Rows0/3 differ in the owning borg identifier, not flight parameters: model14, joint11, HIT1, local offset[55,0,0], speed40, gravity update interval4, initial gravityf32(.3), clamp0..7.5, approachf32(.15), draw multiplier2, impact85e00 row0, no launch effect/trail/proximity child. Constructor captures scale, target identity and saved aim; phase0 recomputes muzzle/current owner yaw but does not recapture the selected target or scales.

Pure source module `ninjaShurikenFlight.ts` preserves:

- Separate allocation and initialization; successful HIT registration initializes lifetime600 and calls active in the **same** dispatch (life599 after initialization).
- Bounds/lifetime checks before contact and motion; contact before movement; spin0x1800 per active update.
- Ballistic startup using the original subtractive root. JS square root, trigonometry and normalization are not a bit-exact PPC oracle. No Powered rationalized-root/finite-gravity substitution is used.
- Target tracking adjusts gravity, not horizontal heading. Target loss does not acquire a new selection.
- Full-vector normalize×speed followed by restoration of vertical velocity.
- Contact and terrain emit row0 impact. Bounds, lifetime, incoming attraction disappearance, owner death/form mismatch and failed registration do not.
- Contact disables HIT immediately; terrain retirement preserves it for that collision pass and disables it on the next retirement dispatch.
- Owner invalidation before active dispatch immediately hides/unregisters and enters released; next dispatch frees. Ordinary action completion/interruption does not destroy an independent launched child.

Source `833a4`, `833ec`, `83610`, `83714` external influences have explicit injectable pure seams but no new gameplay implementation. The production adapter supplies target roots, host bounds and triangle segment terrain. Source target HIT-center/eligibility subtleties and projectile scheduler ordering remain approximations.

### Attachment and HIT

Fresh original Normal ARC member1253 and Sasuke1312 joint11 bind composition is identical. Translation `[61.06508512348328,118.12782997117024,-0.000012228569289618463]`, tiny Z rotation `-0.000008804204806533988`. Applying local[55,0,0] gives `[116.06508512135164,118.12734573990589,-0.000012228569289618463]`. The adapter scales this once and applies host owner yaw. This is a static bind fallback, not animated joint11 or bit-exact HSD matrix composition.

HIT1 in both original banks maps record1: shape0, bone0, flags1, damage1, window0..−1, offset0. Radius is extentX10, not the generic parser's radius payload0. Source c0 controls radius; visual multiplier2 does not. Family damage1 `802d4178`: HP10, down/balance/combo100, strength4, effect1, flagsA/B0, refresh0.

The host uses a previous/current sphere sweep against body/root geometry and preserves one victim history per child. It does not turn the drawing blades into additional HIT geometry. Primary accepted contact is consumed by the next source child dispatch. The Time Bomber receiver path uses the same identity and deferred mine retirement.

## Independent damaging impact

Fresh `85e00` row0 at `802da0b8` differs from previously audited row13 only in HIT3 versus107. Original commonHIT3 maps record4: sphere radius310×dynamicc0, flags1, window0..−1, global damage1. Global `802c4778` bytes are equal to audited global damage20: HP20, flagsA0x20, flagsB0, reaction2, animation4, knockback mode1, pitch trim56, refresh0.

Reuse of the existing85e00 expansion/hold/tail engine is therefore supported: initialization does not advance;13 expansion updates reach1.25; three subsequent hold passes remain active; the fourth hold update disables HIT; tail through30 then free. Each impact has a new UID and empty victim history. It survives owner death because86048 only dispatches its own phases. Immunity can suppress either hit, so the move does not promise a universal30 total damage. Cosmetic yaw RNG and exact effect model/ring presentation remain existing omissions.

## Production bindings and limits

Both standalone bridge `spawnFamilyProjectile` and production Battle `addRomProjectile` route the admitted rows before generic fallback. Generic source collision/motion is bypassed for these children. Actor cancellation clears source clock/sample; existing renderer epochs prevent a delayed clip load from resurrecting the action. Input edges are sampled even while busy, so a blocked held press is not buffered into another move.

Remaining explicit boundaries:

- Fresh host ground/air posture maps to the exact observed rows; this does not establish all original directional/posture admission.
- Shared aim helper rounding and host movement/terrain are not original variable-dt/geometry parity. Actor clocks are tested at1/.5; this does not prove every physics helper at those rates.
- Static joint11, root target sample, swept sphere/body receiver and terrain intersections replace animated source shapes/matrices.
- Source support6d0 consumer, afterimage FX/RNG and incoming projectile modifiers remain unbound.
- New impact allocation/collision uses the host projectile pass, not a proof of original scheduler slot timing. Initial aim uses retained child-target validity instead of independently reading current owner+c8, so a target change/loss exactly between allocation and initialization is an explicit capture seam.
- Production tracking considers a living target valid. The original `(cc83==0 && cc656!=0)` tracking-loss branch is unbound because the host does not expose656; the pure engine accepts a distinct validity input.
- Shared85e00 numerical/presentation approximations are retained; procedural shuriken/impact drawing does not imply original asset fidelity or exact blending.
- Host post-action cooldown and240-update safety ceiling are retained safeguards, not newly claimed source parameters.

## Verification

Durable tests:

- `ninjaXStream.selftest.ts`: raw gate sequence, dt1/.5 timing, blend/end ordering, recovery flags and elapsed terminals.
- `ninjaX.selftest.ts`: own-history phase0, authored callback, conditional recoil/ammo ordering, support shadow reset and cleanup.
- `ninjaShurikenFlight.selftest.ts`: source phase/probe ordering, gravity/target behavior, negative impact cases, immutability and external seams.
- `ninjaProjectile.selftest.ts`: static attachment, allocation snapshots, scale separation, independent impact history, lifetime and owner isolation.
- Independently authored `ninjaXBattle.selftest.ts`: actual ground/jump X, source commands/release/recovery, five shots/depletion/refill, held/fresh/busy controls, captured-target movement/R change/loss, natural target/wall contacts, owner interruption/death/replacement and neighbor attacks.
- `battle-scene-ninja.selfcheck.ts`: visible procedural blades, source yaw/spin/scale, impact opacity, hidden states, render pause, duplicate UID, kind replacement and disposal.
- Existing source-animation selfcheck adds both Ninja main/recovery clip families with source-owned paused sample clocks.

Focused suites and combat/game typechecks pass as reported in the parent work log. Full contributor and matching/oracle results must be recorded after their final runs; this document does not preclaim them. `rom/actor.ts` was not changed, so this lane does not regenerate the actor-field map.
