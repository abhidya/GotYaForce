---
title: Progress Dashboard
---

<script setup>
import metricsData from './.vitepress/data/metrics.json'
import progressData from './.vitepress/data/progress.json'
</script>

# Progress dashboard

Live status pulled straight from `research/` and the organized decomp map. Last
regenerated {{ metricsData.generatedAt?.slice(0, 10) }} (commit `{{ metricsData.gitSha }}`).

<div class="gf-grid gf-grid-4">
  <MetricCard label="Functions indexed" :value="metricsData.functionsIndexed.toLocaleString()" accent="blue" hint="Ghidra full-corpus" />
  <MetricCard label="Borgs catalogued" :value="metricsData.borgsIndexed" accent="pink" hint="of {{ metricsData.borgsOnDisc }} on disc" />
  <MetricCard label="Stages mapped" :value="metricsData.stagesMapped" accent="green" hint="18 named arenas" />
  <MetricCard label="TUNED remaining" :value="metricsData.tunedRemaining" unit="/ {{ metricsData.tunedTotal }}" accent="amber" hint="{{ metricsData.tunedDerived }} derived · {{ metricsData.tunedFilesWithDebt }} files" />
  <MetricCard label="Decomp organized" :value="metricsData.organizedPct" unit="%" accent="green" hint="{{ (metricsData.totalOrganizedFiles - metricsData.unsortedFiles).toLocaleString() }} / {{ metricsData.totalOrganizedFiles.toLocaleString() }} files bucketed" />
  <MetricCard label="Unsorted functions" :value="metricsData.unsortedFunctions.toLocaleString()" accent="amber" hint="functions not yet bucketed" />
  <MetricCard label="Decoded data tables" :value="progressData.buckets?.length ?? 0" accent="blue" hint="research/decomp/data/" />
  <MetricCard label="Color variants" :value="6" accent="pink" hint="normal / alt / gold / silver / crystal / black" />
</div>

## System coverage

Percentages are the share of all {{ metricsData.functionsIndexed.toLocaleString() }} decompiled
functions tagged with each topic in `function-evidence-index.json`.

<div class="gf-panel">
  <ProgressMatrix :systems="progressData.systems" />
</div>

## Largest decomp buckets

Counts from `research/decomp/organized/_map.tsv` (one row per function).

<AtlasTable
  :rows="progressData.buckets.map(b => ({ ...b, status: b.status }))"
  :columns="[
    { key: 'label', label: 'Bucket', mono: true },
    { key: 'count', label: 'Functions', mono: true },
    { key: 'status', label: 'Status', status: true }
  ]"
/>

## TUNED debt

`{{ metricsData.tunedRemaining }}` markers await ROM/trace evidence; `{{ metricsData.tunedDerived }}`
are already cited. The 1:1 port target is zero TUNED markers. Source:
`research/tuned-burndown.md`.

<EvidenceCard
  claim="Port is 1:1 when TUNED list is empty"
  status="likely"
  file="research/tuned-burndown.md"
  repro="node scripts/report-tuned-constants.mjs"
  note="Generated nightly. Re-run after any constants change."
/>
