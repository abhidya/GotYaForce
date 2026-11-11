# Diver X owner-bound aura child

## Shipped behavior and evidence

`JELLY_DIVER_X.CHILD_SPAWNER_ADDR` now names `0x801213bc`, matching
`zz_01213bc_` (chunk_0033.c:212-249), not the former missing-digit literal.
Battle handles this spawner before ordinary B-shot attribution. The B-shot mode
vote must not replace the X child: each Diver has two kind-0 B call sites versus
one kind-9 X call site in `shotVariantKinds.json`.

The dedicated child reads the three raw 32-byte rows at `0x8032c6a0` from the
existing decoded JSON: mesh 78, bone 12, HIT kind 9, lifetime 1140, zero local
position, init scale 0.01, and fixed material-animation selector Jelly 0 / Jack 2 /
Tar 1. Kind 9 resolves actual family records Jelly 7 / Tar 11 / Jack 12, with slow
levels 1 / 3 / 2, zero HP damage, flagsB 0x480 and rehit interval 1. The hit row has
zero local offset, halfExtent [700,0,0], radius 0, collision flags 0x1003 and an
open-ended active window.

Source creation is `FUN_80116944`, chunk_0031.c:3437-3456. Source child init,
owner-follow update and timer refresh/expiry are `FUN_8012151c`,
`FUN_80121694`, `FUN_80121860`, chunk_0033.c:288-423. One child per owner persists
across actions; further X events refresh it without replacing its UID. Expiry
removes collision. Owner HP-zero/death/removal or combat-form change removes it,
matching the owner-stop intent of `zz_0084000_`, chunk_0012.c:3184-3210.

Contacts run after all actor movement and the global aura clear. They use the
shared contact-only status writer rather than ordinary applyHit: no damage,
knockback, combo credit, hitstop, hitstun or projectile impact puff is manufactured.
There is no extra friendly protection: source flagsB 0x480 lacks the same-team
exemption 0x10 (chunk_0003.c:7538). Slow-aura writes honor Diver exemption, shared
immunity, burst and the explicit carried-role flag (chunk_0003.c:7653-7677).
Haste retains its separate source branch and is not burst-suppressed.

The bridge records host family-child emission as a real X effect, so completing
the first X does not incorrectly latch the generic impotence fallback.

## Explicit approximation boundaries

- **Anchor:** Battle has no owner bone-12 matrix. Child position follows the owner
  root; this is not decoded bone attachment. No invented bone offset is added.
- **Collision:** the browser's existing max-extent spherical abstraction uses
  the decoded 700 extent times owner model scale and target root distance. The
  exact shape-0 volume, target body geometry and complete source collision-mask
  pairing are not reconstructed. This is an approximate boundary, not proof of a
  source-exact 700-radius sphere.
- **Visual/timing:** source active updates copy owner base scale but additionally
  apply an anisotropic pulse. The pulse literals and particle teardown are not
  implemented. The initial 0.01 value is overwritten by active base scale before
  the first observed simulation boundary; source-exact init growth/phase timing
  is not claimed. Refresh and creation are decremented during the same browser
  contact phase. Mesh/material selection is decoded; the complete visual curve
  is not.
- **Ammo:** the original PR26 emitter preserved unbound/infinite source cell 2.
  The subsequent [Diver ammo binding](diver-ammo-binding-2026-11-11.md) connects
  that cell to the browser X/HUD charge and consumes one at the stream cue.
  Normal refill now follows the source timer and cached-rate ordering. The
  additional burst multiplier and live pause/fusion/slow-immunity seams remain
  qualified in that follow-up; full modifier parity is not claimed.
- **Fusion:** `sourceFusionCarried` is a new optional, unpopulated host seam for
  +0x4a0. Existing `fusionState` models +0x4a1 and is not conflated with it. The
  helper's carried-role gate is tested, but live fusion-role integration is not
  claimed.
- **Death visual tail:** source drains child particles before freeing; the browser
  removes the visual with collision instead.

## Verification

`diverAura.selftest.ts`, included in the lifecycle suite, drives actual player X
through Battle for all three variants. It checks real kind-9 status, repeated X
refresh with stable UID, independent observation snapshots, root following,
continuous contact without HP/reaction/combo changes, movement recovery after the
one carried contact frame, expiry, owner death/form change, ally contact and
writer immunity/burst/carried gates. The ammo follow-up replaces the original
unlimited-repeat fixture with source charge, denial and recharge assertions.

A semantic negative control bundles the same test with only Battle's dedicated
spawner dispatch bypassed (imports and fields retained). It fails specifically
`pl0805 actual X did not spawn an aura child`, proving this is not merely a
synthetic status test or a compile-failure control.

## Generic special presentation correction

The scene no longer manufactures a fireball/ring when an actor merely enters the
special animation slot. Diver entry (`FUN_80116854`, chunk_0031.c:3387-3423)
prepares motion/animation; child creation in `FUN_80116944` follows positive stream
contact and successful cell-2 allocation. An unconditional entry explosion falsely
presented a radial attack before that event, including unsuccessful empty X actions.

The port's actual generic radial fallback in `startSpecialAttack` now emits a
sampled-position, monotonic-serial presentation event, after the projectile-special
branch returns. The scene consumes that event once, independent of animation-slot
changes. Its ring diameter follows the fallback mechanic's configured radius and
charge multiplier. This preserves generic AoE readability without adding that
visual to ROM actions or projectile specials. The fallback textures, fireball,
colors and timing remain TUNED; this is not evidence of original effect parity.
Diver mesh attachment, pulse and other approximation boundaries above are unchanged.

The scene selfcheck now renders actual Battle actor views for all three Divers,
including entry before contact, source aura creation, and repeated empty X presses.
Isolated generic-fallback fixtures use real Battle actors, a fixture-local profile
and no ROM driver to check event snapshots, custom/charged radius, repeated sync,
a second attack without a rendered idle transition, and projectile suppression.

A semantic negative-control bundle restores the old special-slot trigger while
keeping all new types and event code. It fails on `pl0805 entry before contact has
no manufactured burst`, rather than an import/compile failure. Focused scene tests,
the scene morph/lifetime/retirement/size aggregate, and root typecheck pass.
