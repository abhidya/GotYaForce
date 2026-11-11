# Source primary ammo timers and integer refill

## Evidence and bounded integration

- `docs-site/public/chunks/chunk_0007.c:60-100`, `FUN_800562b8`: the first stat segment initializes source cell 0. A nonzero initial charge initializes timer to zero, including type 0. The field exported as `ammoType` is initial current; `ammoCount` is max.
- `chunk_0009.c:2866-2905`, `zz_006dbe0_`: type 0 seeds timer only when consumption empties current. Type1 adds one parameter to existing float timer debt per consume call. Query-only calls do not mutate.
- `chunk_0009.c:2909-2973`, `zz_006dcc0_`: skip source slot pause bit or nonpositive timer. Type0 subtracts cached rate and restores max at zero, clamping timer to zero. Type1 subtracts rate and derives integer current as `max-(trunc(timer/param)+1)` while positive, restores max otherwise, and preserves negative overshoot.
- `chunk_0009.c:4648-4672`, `zz_0070558_`: ordinary shot emission uses `zz_006dbe0_(actor,0,1,1)` before emitting.
- Rate and update ordering are the same recovered `+0x768` path documented in `diver-ammo-binding-2026-11-11.md`.
- `FUN_8005a378`, `chunk_0007.c:2854-2866`: both known base 1.5 and slow exclusion use `+0x6fc`, represented by `burstPaired`, not the initiator-only `burstActive`. This also corrects the shared Diver rate helper. The additional refill multiplier is gated by the same source byte.

`hasSourcePrimaryAmmo` deliberately includes only exported finite, positive-parameter type 0/1 rows whose initial and maximum charges agree. Synthetic/no-row profiles, empty-start rows, types 2/3 and all existing non-Diver X slot bindings retain their previous policy. No slot remapping is generalized.

Actual generic primary shot consumption now enters `useWeaponCell`, not a separate subtraction that omitted type 1 debt. The live Battle tick uses the existing source refill helper with source slot 0, and rebuilds cached rate in the same post-status phase as Diver. This corrects ammo accounting; it does not claim generic shot animation or emission timing is fully ported.

## Observed regression before fix

Real Battle input for Beam Gunner (`pl0104`) consumed one charge but left timer 0. Ten frames later current was `4.9999999999999964` rather than the source integer 4 with debt 50. G RED (`pl0615`) started full with timer 180; firing only one shot let that partial magazine spontaneously fill later without ever emptying.

## Tests and limitations

`primaryAmmo.selftest.ts` runs in the existing lifecycle suite. It drives actual B input through Battle for G RED type 0 and Beam Gunner 60/Flame Dragon 300 type 1 boundaries, checks immutable HUD output, and covers query/consume debt, pause bit 0 versus bit 2, cached-rate frame order, freeze exclusion, negative timer overshoot, and paired-only versus initiator-only burst flags. Existing Diver, generic ammo and X suites remain regression controls.

Extra burst multiplier `FLOAT_804376c8` is now verified as f32 **10.0**, bits `0x41200000`. With cached paired base 1.5 it gives rate 15; Diver debt 1200 refills in 80 steps. On paired onset with cached baseline 1 the first step subtracts 10, then later steps subtract 15; the live test needs 81 steps and preserves -10 overshoot. Initiator-only `burstActive` applies neither multiplier.

Read-only rig evidence from the GG4E ISO: size 1459978240, embedded DOL base `0x1f700`, DOL span 3888928, DOL SHA256 `21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`. Address `0x804376c8` maps to DOL offset `0x3af8e8`, ISO offset `0x3cefe8`. The four bytes decode big-endian to `41 20 00 00`. Source fusion-role, pause-mask and immunity writers remain limited to already integrated runtime seams; no busy-state pause is invented. Existing level row selection remains empirical, and this patch does not expand its fidelity claim.

Semantic negative controls preserve imports and mutate only the in-memory test bundle: old fractional refill fails the actual Beam boundary, bypassing source consumption fails actual Beam debt, and old type 0 initialization fails the full-magazine zero timer assertion.
