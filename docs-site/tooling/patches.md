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

These files are reviewed inputs for locally cloned tools; they are not vendored
dependencies and are never applied automatically.

## HSDLib patch workflow

Clone the upstream tool under ignored `tools/HSDLib`, pin the revision used by
your evidence record, then check before applying:

```bash
git -C tools/HSDLib apply --check ../../research/patches/hsdlib-modelexporter-texture-fix.patch
git -C tools/HSDLib apply ../../research/patches/hsdlib-modelexporter-texture-fix.patch
```

Rebuild HSDLib using its upstream instructions, run the relevant asset export,
and compare the generated manifest/hashes. If `--check` fails, stop: the patch
and upstream revision are incompatible.

`research/patches/gltf-export-Program.cs` is a reference harness, not a patch
to overwrite blindly. Integrate it into a disposable local clone and record the
clone revision plus output validation in the asset evidence.
