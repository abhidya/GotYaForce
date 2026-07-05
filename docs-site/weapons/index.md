---
title: Weapons & Items
---

# Weapons & items

90 weapon archives (`it####_mdl.arz`) catalogued in
`research/asset-inventory/weapon-attachment-map.json` (11 MB) and
`research/asset-inventory/weapons-effects-projectiles.json` (4.8 MB).

::: warning Heavy data
The full weapon table is large. The curate script does not yet copy it into
the docs data dir to keep the static site under GitHub Pages limits. The
authoritative source remains the research JSON files above.
:::

## What's mapped

- Weapon → borg attachment points
- Projectile spawn params (muzzle position, homing, lifetime)
- Effect IDs cross-referenced with `impact-effect-id` decode
- Owner-liveness despawn rules (`zz_00840b8_`, `chunk_0012.c:3216`)

See [Systems → Combat](../systems/combat) for how weapon params feed the damage
formula.
