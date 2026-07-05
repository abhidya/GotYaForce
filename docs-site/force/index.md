---
title: Force — Gacha + Fusion + Variants
---

<script setup>
import forceData from '../.vitepress/data/force.json'
</script>

# Force

The gacha economy (Gotcha-Box drops), Power Burst fusion, and the six color
variants. All values straight from decoded ROM tables.

## Gotcha-Box spawns

<EvidenceCard
  :claim="`Challenge spawn pool — ${forceData.spawnPools.groupCount} groups`"
  status="verified"
  :addr="forceData.spawnPools.address"
  file="research/decomp/data/spawn-pools-80380804.json"
  :note="forceData.spawnPools.description"
/>

## Power Burst fusion

<EvidenceCard
  :claim="`Fusion pair table — ${forceData.fusion.pairCount} entries across ${forceData.fusion.familyCount} byte families`"
  status="verified"
  :addr="forceData.fusion.address"
  file="research/decomp/data/fusion-pairs-802d352c.json"
  :note="`Non-null families: ${(forceData.fusion.nonNullFamilies || []).join(', ') || 'none'}.`"
/>

## Color variants

<AtlasTable
  :rows="forceData.colorVariants.map((v, i) => ({ i, variant: v }))"
  :columns="[
    { key: 'i', label: '#', mono: true },
    { key: 'variant', label: 'Variant', mono: true }
  ]"
/>

::: tip Provenance
Fusion extraction method: {{ forceData.fusion.provenance?.readMethod }}.
Citation: {{ forceData.fusion.provenance?.citation }}.
:::
