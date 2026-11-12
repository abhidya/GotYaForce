# Diver natural-expiry particle tail

## Scope and evidence

This lane implements only the detached natural-expiry tail for Jelly, Tar and Jack
Diver X. Active aura mesh 78, its pulse, bone attachment and collision remain separate.
Death, missing owner and morph still remove the active aura immediately without a tail.
The source owner-stop +0x82 visibility behavior is not sufficiently established to
extend that path. Active selector-79 particles are now covered by the separate
[active-particle lane](diver-active-particles-2026-11-11.md).

Evidence is the read-only rig audit of `chunk_0033.c`, especially lines 762–813 and
894–921, and original PPC checked against DOL SHA-256
`21454a8880c6254616662710d6ec626e43d853999da2cdfad700030960a94836`.
No original assets were copied and no rig files were modified. The repository already
contains the bank geometry used here.

`FUN_80121918` disables collision, hides mesh 78, resets the particle bank and creates
32 particles. `FUN_80121990` advances surviving particles until the mask is zero,
then frees the child. Particle birth is `zz_0121db0_`. The selector table at
`0x804345a0` is `[79, 80]` (DOL offset `0x3ad120`). Teardown selects mesh 80: one
135-triangle alpha-blended mesh, bounds ±40, without vertex colors.

Fixed material animation selection follows child +0xd8: Jelly frame 0, Jack frame 2,
Tar frame 1. The checked PPC ranges are `80121ce8..80121d1c` and
`800074f0..80007510`. The global mode-byte-equals-3 override to frame 0 is not
implemented because the browser has no established equivalent mode state.

## Mathematical translation

Each birth consumes six bytes r0 through r5 from an isolated visual RNG:

- S = 0.5 + r0 / 255.
- R = 760 B - 90 S, where B is the owner base scale copied before lifetime dispatch.
- Seed = R times `(r1 / 127.5 - 1, r2 / 127 - 1, r3 / 127.5 - 1)`.
- If seed magnitude is below `0.00009999999747378752`, replace it with `(0, 1, 0)`.
- Normalize to N. Offset = N R (0.75 + r4 / 1020).
- Velocity = N B (20 + r5 / 51). Initial opacity is 0.25; yaw is zero.

Each subsequent fixed simulation update first adds velocity to offset. If its
magnitude exceeds R, subtract `0.012500000186264515` from opacity. Clamp at zero
and remove that particle when opacity is zero. Dispose the tail after its final
particle disappears. Constants were checked at DOL `0x3b1ce8`, with the fallback
vector at `0x2adcb4`.

These formulas are source-backed, but JS arithmetic and normalization are not a
claim of exact PPC rounding. The local UID-seeded xorshift generator consumes
exactly 192 bytes for 32 births. It intentionally approximates the source global
RNG sequence, rather than sharing the active-particle visual RNG stream. Neither
browser gameplay PRNG is touched. Rendering consumes no random values.

## Browser lifecycle and rendering boundary

`BattleState.diverAuraTails` is independent of active children. A natural expiry
removes active collision immediately and emits one tail; new X can create a fresh
active child while an old tail remains. Tails have no owner-follow or refresh path.
The browser contact phase differs from the source object scheduler: this change
preserves the browser's no-contact-on-expiry rule and does not claim source-wide
update-order parity. New tails retain their birth values until the next sim tick.

`Battle.observe` deep-clones particles, and the presentation adapter carries that
snapshot explicitly. The renderer freezes the last rendered active aura translation
in battle-root coordinates before removing its mesh. If that aura was never seen,
it uses the tail's explicit simulation-root fallback. A loaded animated bone may
therefore determine the frozen anchor, but future movement, morphs, async rig loads
and later auras cannot move it. This is a deliberate rendering boundary, not a
simulation-side bone oracle.

Each particle has translation plus offset, uniform S and zero rotation. No aura
pulse or bone rotation/scale is inherited. Sampled variant color is retained;
particle opacity replaces bank alpha rather than multiplying it. Render dt and
repeated sync cannot move or fade particles. Individual removal and scene clear
dispose only owned materials; shared geometry remains cached.

## Verification

Focused lifecycle tests cover actual X expiry, 32 particles, no expiry contact,
independent new-aura coexistence, immutable nested observations, strict individual
radius boundaries, removal and final freeing, current scale on expiry, deterministic
visual RNG and unchanged gameplay RNGs. Death/morph negative controls emit no tail.
Three scene tests cover actual X for all three variants, mesh-80 topology and bounds,
color and replacement alpha, frozen root and animated-bone anchors, repeated sync,
no render-dt advancement and cleanup. Existing non-Diver projectile/fallback and
bone/morph/async-load controls remain in the same suite.

The full contributor command and all stages after its known sparse-checkout HUD
asset failure are run separately; see the implementation report for exact results.
No rendered pixel or emulator parity claim is made by these structural Three tests.

Validation results: contributor policy, typecheck and browser-gate stages passed.
The aggregate stopped at the existing three missing HUD PNGs (ascii font, face
marker and Borg banner). All later stages were run independently: menu flow,
force builder, game session, pause edge, input focus, title frontend, camera,
challenge flow, render disposal, ROM, combat lifecycle, OGhidra import and game
build passed. No missing assets were manufactured or fetched to mask that limit.

Four deliberate mutation controls were rejected by the focused suites: multiplying
particle alpha by bank alpha, substituting mesh 78, replacing the frozen bone anchor
with the simulation root, and suppressing expiry-tail emission. Each mutation was
restored before final validation. Additional scene checks cover an unseen aura's
root fallback, owner-death survival, active/new-tail coexistence, per-particle
material disposal, final tail disappearance and idempotent scene clear.
