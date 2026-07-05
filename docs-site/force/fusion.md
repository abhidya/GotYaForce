---
title: Fusion Pairs
---

# Power Burst fusion

<script setup>
import forceData from '../.vitepress/data/force.json'
</script>

<EvidenceCard
  :claim="`Fusion pair table — ${forceData.fusion.pairCount} entries across ${forceData.fusion.familyCount} byte families`"
  status="verified"
  :addr="forceData.fusion.address"
  file="research/decomp/data/fusion-pairs-802d352c.json"
  :note="`Non-null families: ${(forceData.fusion.nonNullFamilies || []).join(', ') || 'none'}.`"
/>

::: tip Provenance
{{ forceData.fusion.provenance?.readMethod }}

Citation: {{ forceData.fusion.provenance?.citation }}
:::

## How fusion picks

Each borg carries a family byte. Two borgs in the same family can fuse via
Power Burst. The pair table at `0x802d352c` has 17 entries (families 0–16);
the word at `0x802d3570` belongs to the 35-slot state-handler table, not this
one.
