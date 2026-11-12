# Diver active aura particles

The active mesh-79 lane follows `FUN_80121694`, `zz_0121db0_` and
`zz_0122208_` in chunk_0033.c (phase/cadence near 388, birth 700–760,
update 875–891). It uses the existing efct bank geometry, not newly copied assets.
Read-only original DOL provenance and decoded constants are in
[expiry-tail evidence](diver-expiry-tail-2026-11-11.md).

## Source behavior implemented

The signed countdown starts at zero. Each active simulation update decrements it;
at <=0 it resets to 30 and attempts one birth in the first free slot of 32.
A full pool consumes no random bytes. Refresh preserves the pool, countdown and
visual RNG state. Expiry discards the active pool and starts the existing detached
32-particle mesh-80 tail. Owner death/morph still uses immediate safe cleanup;
source owner-stop visibility remains outside this lane.

Each successful birth consumes six local visual RNG bytes r0…r5:
- S = 1 + r0/255; R = 760 B - 90 S.
- Position = R * (r1/127.5 - 1, r2/510 - 1, r3/127.5 - 1).
- If magnitude exceeds R, scale position to R.
- Rise per tick = 4 + r4/127.5.
- Initial yaw is signed16(r5 << 9). Yaw step is +1024 when bit0x80 is set,
  otherwise -1024. Opacity is 0.25, replacing bank alpha (0.1).

Birth precedes update, so the new particle rises/spins immediately. Each update
adds rise to Y, advances signed16 yaw, then removes the particle if its magnitude
is >= 760 B - 90 S. B is the current owner base scale, not a saved birth radius.
The source constants were read from the same original DOL SHA256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.

## Presentation and limits

Mesh79 has 75 triangles, authored vertex colors, white rest material, additive
blending and no material animation. Particle translation follows the active aura's
bone/root anchor. Offsets, uniform scale and Y rotation are independent of the
main aura's anisotropic pulse. Renderer time neither births nor ages particles.
Per-particle materials are owned/disposed; shared geometry stays cached.

The persistent UID-seeded visual RNG does not reproduce the original global RNG
sequence and never touches either browser gameplay RNG. Tail births retain their
separate deterministic stream. Mathematical motion and JS rotation are not a claim
of PPC floating-point or original sine-matrix bit parity. Existing initialization
scheduler, last-rendered anchor, collision geometry and owner-stop limitations
remain. No GPU pixel or original-game side-by-side acceptance is claimed.

## Validation

Actual X tests for all three Divers verify the first active birth and real scene
mesh79 topology/material, translation-only parent, render-dt independence,
immutable snapshots and active-pool disposal/reset at expiry. Lifecycle tests
cover exact 30-step cadence, six draws on successful birth, no draws for a full
pool, first-free-slot reuse, inclusive boundary removal, current-scale changes,
signed yaw wrap, refresh preservation and unchanged gameplay RNGs. Existing tail,
normal projectile, fallback, morph and cleanup controls remain enabled.

Final restored-source typecheck, all contributor stages after HUD, lifecycle,
scene aggregate and game build pass. The aggregate command stops only at the
three known missing sparse-checkout HUD PNGs. No assets were manufactured to
hide that limitation. Deliberate mutations (31-step cadence, wrong Y divisor,
and ignored rendered particle scale) fail the intended behavioral assertions.
