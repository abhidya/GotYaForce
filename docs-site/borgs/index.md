---
title: Borg Atlas
---

<script setup>
import borgsData from '../.vitepress/data/borgs.json'
</script>

# Borg Atlas

{{ borgsData.count }} borgs catalogued, sourced directly from
`{{ borgsData.source }}`. Stats (cost, HP schedule, tribe, type, rarity, jump
type, level-up schedule) are the canonical symbol-map values.

<AtlasTable
  :rows="borgsData.borgs.map(b => ({
    id: b.id,
    name: b.name,
    tribe: b.tribe,
    type: b.type,
    rarity: b.rarity,
    cost: b.cost,
    hp: b.hp1 + '/' + b.hp10,
    speed: b.speed,
    alt: b.alt ? 'Yes' : '-'
  }))"
  :columns="[
    { key: 'id', label: 'ID', mono: true, link: false },
    { key: 'name', label: 'Name' },
    { key: 'tribe', label: 'Tribe' },
    { key: 'type', label: 'Type' },
    { key: 'rarity', label: 'Rarity' },
    { key: 'cost', label: 'Cost', mono: true },
    { key: 'hp', label: 'HP 1/10', mono: true },
    { key: 'speed', label: 'Spd', mono: true },
    { key: 'alt', label: 'Alt' }
  ]"
  searchable
  searchPlaceholder="Filter by name, tribe, type..."
/>

## Source

Each row corresponds to one line in `research/symbols/NTSC_Borgs.csv`. The CSV
columns are:

| CSV column | Maps to |
|---|---|
| `filename` | `id` (pl0000..pl0207) |
| `borgname` | `name` |
| `Cost` / `Data Crystals Required` | summoning cost |
| `Tribe` / `Type` / `Rarity` | classification |
| `Level 1 HP/Level 10 HP` | HP at level bounds |
| `Defense` / `Shot` / `Attack` / `Speed` | stat ratings |
| `Jump Type` | ground / air-jump / double-jump |
| `Level-up Schedule` | progression curve key |
