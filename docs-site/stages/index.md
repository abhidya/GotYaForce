---
title: Stage Atlas
---

<script setup>
import stagesData from '../.vitepress/data/stages.json'
</script>

# Stage Atlas

{{ stagesData.arenas }} named arenas decoded from the challenge-stage-naming
pass. {{ stagesData.challengePoolCount }} of them appear in the challenge
rotation pool. Source: `{{ stagesData.source }}`.

<AtlasTable
  :rows="stagesData.stages"
  :columns="[
    { key: 'id', label: 'Byte', mono: true },
    { key: 'name', label: 'Arena' },
    { key: 'archive', label: 'Archive (sub0/1/2)', mono: true },
    { key: 'inChallengePool', label: 'Challenge pool' },
    { key: 'status', label: 'Status', status: true }
  ]"
  searchable
  searchPlaceholder="Filter by name or byte..."
/>

## Sub-pages

- [Lighting & render state](./lighting) — fog, material, GX state per stage
- [Geometry & collision](./geometry) — bounds, collision mesh port status
- [Export plan](./export) — model/scene export pipeline
- [Readability flags](./readability) — too-dark / too-flat / fog-clip / bounds-mismatch
