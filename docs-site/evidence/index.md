---
title: Evidence Ledger
---

<script setup>
import evidenceData from '../.vitepress/data/evidence.json'
</script>

# Evidence ledger

Every claim on this site traces back to disc offsets, RAM fields, named
functions, and repro steps. This page is the index.

## Verified claims

<AtlasTable
  :rows="evidenceData.evidence"
  :columns="[
    { key: 'claim', label: 'Claim' },
    { key: 'addr', label: 'Address', mono: true },
    { key: 'status', label: 'Status', status: true },
    { key: 'file', label: 'Source', mono: true }
  ]"
  searchable
/>

## Trace validity

<div v-if="evidenceData.invalidTraces" class="gf-panel">
  <div class="gf-panel-header">Dolphin GDB trace results</div>
  <p style="margin: 0 0 8px; font-family: var(--gf-mono); font-size: 0.84rem; color: var(--gf-muted);">
    {{ evidenceData.invalidTraces.source }}
  </p>
  <div class="gf-grid gf-grid-3">
    <MetricCard label="PASS" :value="evidenceData.invalidTraces.counts.pass" accent="green" />
    <MetricCard label="FAIL" :value="evidenceData.invalidTraces.counts.fail" accent="amber" />
    <MetricCard label="INVALID" :value="evidenceData.invalidTraces.counts.invalid" accent="pink" />
  </div>
</div>

::: warning Resident ≠ active
Borg animation strings remain resident in challenge mode memory even after a
borg is no longer in the active slot. UI must warn when reading resident
strings as evidence of active state. Source:
`research/traces/GG4E/challenge-battle1-memory-evidence.md`.
:::

## Sub-pages

- [Function index](./functions) — 11,972 functions cross-referenced by topic
- [Runtime traces](./traces) — Dolphin GDB trace plans and SOPs
- [Save / GCI format](./save-gci) — XOR scramble, keyed digest, CRC
- [Disc / ISO layout](./disc-iso) — FST, AFS TOC, hashes
- [Trace validity ledger](./traces-ledger) — which traces prove which claims
