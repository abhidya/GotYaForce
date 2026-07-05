---
title: Color Variants
---

# Color variants

<script setup>
import forceData from '../.vitepress/data/force.json'
</script>

Six color variants per borg, stored as flags in the save roster section.

<AtlasTable
  :rows="forceData.colorVariants.map((v, i) => ({ i, variant: v }))"
  :columns="[
    { key: 'i', label: '#', mono: true },
    { key: 'variant', label: 'Variant', mono: true }
  ]"
/>

**Source:** `research/format-specs/save-gci-format.md:230`,
`research/decomp/items-evidence-inventory-2026-07-05.md` §2d.
