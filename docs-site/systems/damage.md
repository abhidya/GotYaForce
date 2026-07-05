---
title: Damage Formula & Type Matrix
---

# Damage formula & type matrix

<script setup>
import tablesData from '../.vitepress/data/data-tables.json'
</script>

The damage pipeline applies a 20×20 type-effectiveness matrix on top of a
base damage formula, then a resistance falloff keyed by combo rank.

## Tables

| Table | Address | Status |
|---|---|---|
| Type multiplier 20×20 matrix | `0x802c5d60` | <StatusBadge status="verified" /> |
| Damage formula tables | `0x804335e0` | <StatusBadge status="verified" /> |
| Damage records | `0x802d46e0` | <StatusBadge status="verified" /> |
| Type category remap | `0x802f2e28` | <StatusBadge status="verified" /> |

## Matrix orientation

Defender's category selects the row (offset = `defenderCat * 0x50` bytes = 20
floats). Attacker's category selects the column (offset = `attackerCat * 0x4`
bytes). Corrected 2026-07-01 in `behavior-notes.md` (s4o).

**Source:** `research/decomp/data/type-multiplier-matrix-802c5d60.json`,
`research/decomp/combat-feel-gaps-decode-2026-07-05.md`
