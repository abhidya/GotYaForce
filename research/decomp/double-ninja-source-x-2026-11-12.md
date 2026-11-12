# Double Ninja ordinary X: bounded source route

Date: 2026-11-12. Baseline `84491a5a`; isolated charged-engine checkpoint `df9f7791`. Original DOL/PZZ/ARC/HIT reads were read-only numeric inspection. No original binaries or assets were copied or published.

## Scope and visible change

Double Ninja (`pl0003`) fresh ordinary X now enters the verified ground action2/v0 or actual jump-then-X action2/v4 path. A press produces the authored shuriken throw, with no grounded recoil and the airborne backflip. Holding does not repeat it; a short release does not fabricate a charged attack. It uses the existing procedural four-blade shuriken and expanding impact presentation.

Before this lane, actual Battle holds of1/30/90/130 updates left the actor idle with no family callbacks. All releases created the same generic muzzle projectile. The wiki-based charge branch swallowed ordinary X entirely. The old dormant family fallback also backflipped unconditionally and skipped the source ammunition debit.

**Charged clone behavior is not restored.** A genuinely ready charged release retains the prior generic action3 payload and tier2 tuning. The new independent `doubleNinjaXEngine.ts` is an inert, tested transcription of the charged actor phases. It is not called by Battle. The armed second-shuriken row2 is covered only by explicit private fixtures, with no live arming producer. Other Ninja families, Double B attacks, unsupported posture variants, original clone rendering and full animation/collision parity remain outside this lane.

## Shared ordinary actor and exact commands

Source `chunk_0009.c`: Double constructor `6f60c`, shared action2 `71598/715d4`, callback `715f8` at5295–5335. Exact ordinary records:

- Ground `8033b108`: `[44,3,2,0]`.
- Air `8033b148`: `[45,3,2,4]`.

Double shares the original stream bank `802bde80`, config `80433868`, and shared `ff2bc/ff30c/ff418/ff4d4` action with Normal Ninja and Sasuke. The adapter reuses `ninjaX.ts` only for those source-proven ordinary rows. Unsupported Double admission cannot fall through to the inaccurate old family body or a generic ordinary projectile.

Phase0 carries from the actor's own saved position5e8, not toward its target, with source float32 subtract/scale(.95)/add and677b0 probe. Phase1 advances on authored signed P0>0, not a collision. Callback715f8 first conditionally applies the backflip when1d0f is nonzero: lockYaw=heading−0x8000, horizontal10, vertical15, deceleration0, gravity−1. Active yaw is unchanged. It then calls6dbe0(cell2,count1,debit1). Only success allocates row1; a nonzero7c8 additionally allocates row2 **after the same one debit**. Failure still follows conditional recoil but emits neither child.

The live fresh ordinary state is unarmed and emits row1 only. The private action-state `doubleClone` seam defaults to arm0/offset0 and is set only by explicit tests in this lane. It is not a substitute for persistent actor7c8 lifecycle. Armed behavior must not be inferred from these fixtures or the retained generic charged projectile.

Phase2 retains the shared source physics/probe and landing, directional-input or stream-completion exits. Captured target identity does not change when selection changes; its living position refreshes. Ordinary action interruption does not cancel an already independent launched child.

## Source stream and clip evidence

Fresh original AFS488 `pl0003.pzz`:

- Group4 slots0/1 point to exactly the same stream bytes `802be5ee/802be656` already bound for Normal/Sasuke.
- Metadata bank `802bd780`:4/0 and4/1 records `802bdd60/802bdd74` map to MOT4/0 and4/1, flags1.
- Raw AOBJ ends are45 and40. Recovery0/0 ends120, descriptor flags5 loop; metadata0/14 maps MOT0/24, end1, flags1 nonloop. Raw AOBJ flags are0. Descriptor5 is flags, not playback rate.
- Main mode1/blend6, source old-clock gate14; ground recovery mode1/blend4/elapsed4; air recovery mode1/blend8/elapsed8.

These independently verified bytes and AOBJ clocks justify reusing `ninjaXStream.ts` unchanged. At dt1, callback occurs21 dispatches after admission; terminal is57 ground or56 air if landing/input does not exit first. Ground gate14 has dash0; airborne gate14 has dash32. The shared stream has no actor attack-HIT opcode. Support71d/6d0 and layered animation limitations are the same as the earlier Normal/Sasuke route.

## Input and ammunition

Fresh descriptor fields184/188/18c are60/60/120. X uses18c=120. Original686f0 ramps644 for ten held updates without banking on the tenth; then650 gains source rate768 each update. Default1 therefore needs130 held updates. Readiness is checked before release subtracts2×base768. Paired6fc multiplies the already rebuilt1.5 rate by10 while held; release decay does not apply that extra multiplier. Active type5 or58ebit20 clears both clocks. Original6f7c0 sets that bit while7c8 is nonzero; the live clone producer is unbound, and the adapter's explicit input-disable seam supports only source-level fixtures.

Edges/bank sample while another action owns the frame, preventing a blocked held press from replaying after interruption. True-ready release retains the generic charged payload; its debt bookkeeping uses the now-shared source cell2, not an isolated HUD decrement. This is a compatibility boundary, not source charged-ammo behavior.

Fresh source stats row `802deeac` level0 fields are `[150,10,10,0,90,5,5,0,300]`. Original562b8 maps the second weapon segment to source cell2. It has max5, bulk refill type0, period300. Browser cell1 aliases cell2. Individual ordinary throws do not refill early; depletion starts the300-rate countdown, then restores the full magazine. Host admission checks availability; source callback715f8 is the verified ammunition debit/gate and spends only one. The original common admission producer is not newly traced;6f7c0 does not itself read ammunition or set58ebit4. The source refill pause bit is cell2's bit4, not HUD alias cell1's bit2.

## Projectile rows1/2, attachment and damage

Source7db5c table `802d6d68`, stride0x38: rows0/1/2/3 are byte-identical in flight data except owning borg at+2e (0/3/3/10), and row2's+2c=1. That row alone adds current owner7b0 at both allocation and phase0, after the muzzle transform; it is a world-space offset. Initialization recomputes the current attachment/offset instead of adding the old offset again. The pure flight API exposes that explicit seam. The adapter uses a private initialization callback for the armed fixture, without serializing actor objects into observations.

Rows1/2 use model14, joint11, HIT1, local[55,0,0], speed40, lifetime600, initial gravityf32(.3), interval4, clamp0..7.5, changef32(.15), draw2, spin0x1800, impact85e00 row0, no launch/proximity child. The source lifecycle/ballistic flight and independent impact are reused from the previously audited Normal/Sasuke modules. They retain their PPC arithmetic, target-root, host swept-geometry and scheduler boundaries.

**Double's static attachment differs.** Fresh original ARC AFS1271 joint11 parent chain is translation-only `[61,118,0.00000251267192652449]`, unit scales/zero rotations. Local[55,0,0] gives `[116,118,0.00000251267192652449]`. `ninjaMuzzle` chooses this bind for Double instead of Normal/Sasuke's116.065/118.127 bind. It remains a static fallback rather than animated joint geometry.

Original AFS969 `pl0003hit.bin` kind1 remap selects record1: shape0, bone0, flags1, damage1, window0..−1, offset0, extentX10. Family damage1 at8033b1b0 is byte-equal to Normal802d4178: HP10 and the same source gauge/reaction data. The independent impact uses the already audited commonHIT3/globaldamage1 HP20 record and its own victim history. Immunity may suppress either accepted hit; a universal30 total damage is not promised.

## Inert charged-engine checkpoint

`doubleNinjaXEngine.ts` transcribes71750/71858/71938 at `chunk_0009.c:5361–5497` with explicit stream, ground, matrix-X and cosine hooks:

1. Entry maps old arm1 to2; otherwise clears arm/offset. It zeros motion scalars/pose fields, applies own-history drift, probes, starts group4 slot2/3, then calls phase1 in the same dispatch.
2. Phase1 decays offset by.92 and motion by.95, carries/probes/ticks. Source part0 completion starts one10-duration feedback5 wait. Expiry enters phase2 and clears arm/offset.
3. Phase2 carries/probes. For positive558 it subtracts dt, releases stream hold exactly at zero, sets arm2 and magnitude150×cos(truncated signed-angle16384×558/15), then sets offset to supplied owner matrix-X basis×magnitude. It does not advance streams during that ramp.
4. The next dispatch after zero sets arm1/magnitude150 and resumes stream ticks. Stream completion clears action flags and returns ground/air before another offset copy.

This is displaced-double arming, not actor dash speed. Separate original6f708 allocates child141a40 once; child141c30 exposes visibility only while owner7c8 is nonzero;141de4 renders the owner's pose at offset7b0 with an arm2 rendering branch. Those lifecycle/render paths and the complete action3 stream bank are not integrated, so the engine remains inert. Its independent tests establish source control flow, not playable clone behavior.

## Verification and remaining limits

Durable tests include the pure charged engine; exact source input warmup/readiness/rate/reset boundaries; rows0–3 flight/row2 offset fixtures; one-debit callback and failed-debit fixtures; and independently authored actual-input `doubleNinjaXBattle.selftest.ts`. Battle tests cover ground/air entry, authored clocks, short hold/release/repress, true-ready legacy fallback, ammo/refill, interrupted/busy input, target capture/loss, natural host actor/terrain contacts, independent primary/impact lifetime, owner death/redeployment and neighboring B/X controls.

Existing source shuriken renderer tests cover procedural blade drawing, spin, independent draw/collision scaling, hidden lifecycle, repeat/pause and disposal. There is no new original clone model, shadow actor or proprietary animation upload.

Focused build/typecheck/lifecycle and final aggregate results are reported separately for the final tested tree. Full original terrain, animated support/muzzle matrices, target eligibility656, incoming shared projectile modifiers, source scheduler ordering, layered pose/afterimage/RNG and instruction-level float/trig parity remain unproven. No actor field-map generation is needed: `rom/actor.ts` is unchanged.
