---
title: Memory Map
---

<script setup>
import memData from './.vitepress/data/memory.json'
</script>

# Memory map

GameCube MEM1 / ARAM / disc regions and known runtime structs. Sourced from
`research/decomp/ram-trace-analysis.md` and `research/decomp/borg-struct-offsets.txt`.

<AtlasTable
  :rows="memData.regions"
  :columns="[
    { key: 'name', label: 'Region' },
    { key: 'addr', label: 'Address', mono: true },
    { key: 'owner', label: 'Owner' },
    { key: 'confidence', label: 'Confidence', status: true },
    { key: 'notes', label: 'Notes' }
  ]"
  searchable
/>

## Structs

<div v-for="s in memData.structs" :key="s.name">
  <h3 :id="s.name">{{ s.name }} <code class="gf-addr">{{ s.offset }}</code></h3>
  <AtlasTable
    :rows="s.fields"
    :columns="[
      { key: 'name', label: 'Field' },
      { key: 'type', label: 'Type', mono: true },
      { key: 'offset', label: 'Offset', mono: true },
      { key: 'range', label: 'Range', mono: true },
      { key: 'confidence', label: 'Confidence', status: true },
      { key: 'notes', label: 'Notes' }
    ]"
  />
  <p style="font-size: 0.82rem; color: var(--gf-muted); margin-top: 6px;">
    Source: <code>{{ s.source }}</code>
  </p>
</div>

::: warning Gameplay struct base unpinned
Borg world position is confirmed at the render scene buffer, but the gameplay
struct base + HP field is still unpinned. Treat any HP-related claim as
`observed`, not `verified`, until the base is nailed.
:::
