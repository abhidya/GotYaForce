---
title: Stage Export Plan
---

# Stage export plan

Pipeline for exporting stages from disc archives to runtime models.

**Source:** `research/asset-inventory/stage-export-plan.md`

## Pipeline

```text
st_*_dat.arz ──► HSD DAT ──► JOBJ scene ──► glTF / GLB ──► runtime
```

Blocks: animation export (`.mot` banks) and stage-lighting render-state
mapping. See [Tooling → Pipeline patches](../tooling/patches) for HSDLib
texture fix and glTF export harness.
