---
title: Source Map
---

# Source map

12,053 decompiled `.c` chunks under `research/decomp/organized/`, sorted into
SDK + game buckets by `scripts/reorg-decomp.mjs`. The function-level index
lives at `research/decomp/organized/_map.tsv` (one row per function).

## Top-level buckets

| Bucket | What's there |
|---|---|
| `sdk/` | GameCube SDK: libc, gx, hsd, os, audio, math |
| `engine/shared/` | Shared engine helpers |
| `classes/` | Named C++ classes (cCameraManager, cPlayer, SaveLoad, etc.) |
| `game/` | Game code, sub-bucketed by system |

## Game sub-buckets

See the [Progress dashboard](./progress) for live per-bucket function counts.
The largest are `game/battle/force-setup`, `game/combat/knockback`, `game/ui`,
`game/modes/challenge`, and `game/physics/movement`.

::: danger 3,946 functions unsorted
The `game/unsorted/` bucket is the largest single bucket. Reducing this to
zero is the next major decomp milestone. See [Progress](./progress).
:::

## Function explorer

11,972 functions indexed in `research/decomp/index/function-evidence-index.json`.
Topic counts:

- `movement-physics` — largest
- `knockback-targeting`
- `force-setup`
- `assets-animation`
- `challenge-menu-flow`
- `battle-initialization`
- `damage`
- `camera`
- `front-end-menu` / `global-menu-mode`
- `audio`
- `stage-load-collision`

Use the [Evidence ledger](./evidence/) to follow claims back to specific
functions.
