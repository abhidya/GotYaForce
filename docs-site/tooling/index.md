---
title: Tooling
---

<script setup>
import toolingData from '../.vitepress/data/tooling.json'
</script>

# Tooling

This page is the generated inventory, not an installation script. Begin with
the [clean setup](../contributing/setup), then choose a workflow:

- Browser/game changes use the locked Node workspace and
  [verification matrix](../contributing/verification).
- Port artifacts use the [verified-port workflow](../contributing/porting).
- Disc-derived conversion uses the lawful [asset workflow](../contributing/assets).
- Out-of-tree modifications are documented under [Pipeline patches](./patches).

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

## Audited out-of-tree patches

<AtlasTable
  :rows="toolingData.patches"
  :columns="[
    { key: 'name', label: 'Patch' },
    { key: 'file', label: 'File', mono: true },
    { key: 'use', label: 'Use' },
    { key: 'present', label: 'Present' }
  ]"
/>
