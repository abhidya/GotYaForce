---
title: Damage Formula & Type Matrix
---

<script setup>
import TypeMatrix from '../.vitepress/theme/components/TypeMatrix.vue'
import EvidenceTrail from '../.vitepress/theme/components/EvidenceTrail.vue'
</script>

# Damage formula & type matrix

The damage pipeline applies a **20×20 type-effectiveness matrix** on top of a base damage formula, then a resistance falloff keyed by combo rank. Click any cell in the matrix below to inspect the matchup.

<TypeMatrix />

## Proof chains

<EvidenceTrail
  claim="Type multiplier matrix is read as matrix[defender*20 + attacker]"
  status="verified"
  :steps="[
    { label: 'ROM address', value: '0x802c5d60', status: 'verified' },
    { label: 'Decoded table', value: 'type-multiplier-matrix-802c5d60.json', status: 'verified' },
    { label: 'Index correction', value: 'behavior-notes.md s4o (2026-07-01)', status: 'verified' },
    { label: 'Indexing rule', value: 'row=defender, col=attacker', status: 'verified' }
  ]"
  repro="node scripts/print-type-matrix.mjs (or inspect research/decomp/data/type-multiplier-matrix-802c5d60.json)"
  source="research/decomp/data/type-multiplier-matrix-802c5d60.json"
/>

<EvidenceTrail
  claim="Damage formula applies base damage × type multiplier × comboRankScale falloff"
  status="verified"
  :steps="[
    { label: 'Formula tables', value: '0x804335e0', status: 'verified' },
    { label: 'Damage records', value: '0x802d46e0', status: 'verified' },
    { label: 'Falloff function', value: 'comboRankScale_802c7ca0', status: 'verified' },
    { label: 'Port', value: 'packages/combat/src/damageFormula.ts:130-132', status: 'verified' }
  ]"
  source="research/decomp/combat-feel-gaps-decode-2026-07-05.md"
/>

## Tables

| Table | Address | Status |
|---|---|---|
| Type multiplier 20×20 matrix | `0x802c5d60` | Verified |
| Damage formula tables | `0x804335e0` | Verified |
| Damage records | `0x802d46e0` | Verified |
| Type category remap | `0x802f2e28` | Verified |

See [Combat & damage](./combat) for the broader system and [Action stream](./action-stream) for combo ladders.
