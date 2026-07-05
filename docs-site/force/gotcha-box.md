---
title: Gotcha-Box Drops
---

# Gotcha-Box drops

Gacha economy driven by a chapter-indexed spawn pool table.

<script setup>
import forceData from '../.vitepress/data/force.json'
</script>

<EvidenceCard
  :claim="`Challenge spawn pool — ${forceData.spawnPools.groupCount} groups`"
  status="verified"
  :addr="forceData.spawnPools.address"
  file="research/decomp/data/spawn-pools-80380804.json"
  :note="forceData.spawnPools.description"
/>

## How drops roll

1. Mission/challenge battle selects a `group` id.
2. `0x80380804[group]` points to a `-1`-terminated array of borg spawn IDs.
3. `zz_0196eb8_` (`0x80196eb8`) does a uniform random pick from the array.
4. Picked ID resolves via `NTSC_Borgs.csv` to a borg + variant.

See the [Borg Atlas](../borgs/) for the canonical name → ID mapping and
[Fusion pairs](./fusion) for how duplicates feed the Power Burst economy.
