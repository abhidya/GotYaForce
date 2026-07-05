---
title: Tooling
---

<script setup>
import toolingData from '../.vitepress/data/tooling.json'
</script>

# Tooling

The reverse-engineering stack. {{ toolingData.scriptsIndexed }} scripts under
repo `scripts/` drive extraction, inventory, and validation.

<AtlasTable
  :rows="toolingData.tools"
  :columns="[
    { key: 'name', label: 'Tool' },
    { key: 'use', label: 'Use' },
    { key: 'status', label: 'Status', status: true }
  ]"
  searchable
/>

## Out-of-tree patches

<AtlasTable
  :rows="toolingData.patches"
  :columns="[
    { key: 'name', label: 'Patch' },
    { key: 'file', label: 'File', mono: true },
    { key: 'use', label: 'Use' },
    { key: 'present', label: 'Present' }
  ]"
/>
