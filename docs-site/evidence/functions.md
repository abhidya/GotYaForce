---
title: Function Index
---

# Function index

11,972 functions decompiled by Ghidra and indexed by topic in
`research/decomp/index/function-evidence-index.json`.

The full JSON is 18 MB and not copied into the static site (GitHub Pages
limits). Use the source file directly for any deep query.

## Topic counts

<script setup>
import evidenceData from '../.vitepress/data/evidence.json'
</script>

<AtlasTable
  :rows="Object.entries(evidenceData.topicCounts).map(([topic, count]) => ({ topic, count }))"
  :columns="[
    { key: 'topic', label: 'Topic', mono: true },
    { key: 'count', label: 'Functions', mono: true }
  ]"
  searchable
/>

## Source files

- `research/decomp/index/function-evidence-index.json` — 18 MB, the full index
- `research/decomp/index/address-resolution.md` — address → symbol mapping
- `research/decomp/index/class-map.md` — class-grouped function map
- `research/decomp/ghidra-export/_index.tsv` — TSV of all chunks
