---
title: Data Tables
---

<script setup>
import tablesData from '../.vitepress/data/data-tables.json'
</script>

# Decoded data tables

{{ tablesData.count }} game tables decoded from ROM and dumped to
`research/decomp/data/`. Each table is bound to its source address.

<AtlasTable
  :rows="tablesData.tables"
  :columns="[
    { key: 'file', label: 'File', mono: true },
    { key: 'address', label: 'Address', mono: true },
    { key: 'description', label: 'Description' }
  ]"
  searchable
  searchPlaceholder="Filter by address, name, or description..."
/>

## Pipeline

Tables are dumped by scripts under `scripts/` (look for `extract-*` and
`build-*-index` runners) and re-read by `docs-site/scripts/curate-data.mjs` on
every site build. To add a new table, drop the JSON in
`research/decomp/data/` named `<table>_<addr>.json` with `address` and
`description` keys — the curate script will pick it up automatically.
