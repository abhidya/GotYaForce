---
title: Weapons & Items
---

# Weapons & items

Weapon, projectile, effect, attachment-bone, and attack-clip evidence curated
from the heavy research JSON into a small GitHub Pages atlas.

<WeaponAtlas />

## What's mapped

- Weapon to Borg attachment points
- Projectile spawn params (muzzle position, homing, lifetime)
- Effect IDs cross-referenced with `impact-effect-id` decode
- Owner-liveness despawn rules (`zz_00840b8_`, `chunk_0012.c:3216`)

See [Systems → Combat](../systems/combat) for how weapon params feed the damage
formula.
