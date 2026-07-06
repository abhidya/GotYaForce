---
title: Memory Map
---

<script setup>
import MemoryMapSvg from './.vitepress/theme/components/MemoryMapSvg.vue'
</script>

# Memory map

GameCube MEM1 / ARAM / disc regions and known runtime structs. Click any region for details. Confidence colors: <span style="color: var(--gf-verified)">green = verified</span>, <span style="color: var(--gf-accent-2)">blue = observed in RAM</span>, <span style="color: var(--gf-likely)">amber = likely</span>, <span style="color: var(--gf-faint)">gray = unknown</span>.

<MemoryMapSvg />

Source: `research/decomp/ram-trace-analysis.md`, `research/decomp/borg-struct-offsets.txt`.
