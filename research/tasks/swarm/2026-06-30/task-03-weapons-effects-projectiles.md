# Task 03 - Weapons, Effects, Projectiles

Purpose: find original sword, fire, gun, beam, projectile, muzzle, impact, and attachment assets. The browser should not fake these.

Own these outputs only:
- `scripts/inventory-effect-assets.mjs`
- `research/asset-inventory/weapons-effects-projectiles.json`
- `research/asset-inventory/weapons-effects-projectiles.md`

Inputs to inspect:
- `user-data/GG4E/afs_data/root/`
- `user-data/GG4E/disc/`
- `research/format-specs/`
- `packages/assets/data/`

Requirements:
- Script must scan extracted file names, archive contents if already unpacked, texture names/sizes, and likely effect/projectile model files.
- Group findings by family: sword/blade, fire/flame, gun/bullet, beam/laser, muzzle, impact/explosion, aura/trail, UI reticle/target.
- For each asset candidate, record path, file type, size, linked borg id if inferable, confidence, and reason.
- Identify which assets need new extraction/conversion scripts.
- Include likely attachment/weapon bone leads if visible from model or MOT naming.
- Do not create placeholder effects.

Verification:
- Run the inventory script.
- Confirm JSON parses and markdown report cites real files.
