---
title: Pipeline Patches
---

# Pipeline patches

Out-of-tree patches to the RE tooling stack.

<script setup>
import toolingData from '../.vitepress/data/tooling.json'
</script>

<AtlasTable
  :rows="toolingData.patches"
  :columns="[
    { key: 'name', label: 'Patch' },
    { key: 'file', label: 'File', mono: true },
    { key: 'use', label: 'Use' },
    { key: 'present', label: 'Present in repo' }
  ]"
/>

Apply these on top of upstream HSDLib / gltf-export when running the asset
pipeline locally.
