---
title: Trace Validity Ledger
---

# Trace validity ledger

Which Dolphin traces prove which claims. Many traces prove PAD normalization
but not action semantics — those must be marked `invalid` for action claims.

**Source:** `research/traces/GG4E/dolphin-gdb-trace-results.md`

<script setup>
import evidenceData from '../.vitepress/data/evidence.json'
</script>

<div v-if="evidenceData.invalidTraces" class="gf-panel">
  <div class="gf-panel-header">Aggregate counts</div>
  <div class="gf-grid gf-grid-3">
    <MetricCard label="PASS" :value="evidenceData.invalidTraces.counts.pass" accent="green" />
    <MetricCard label="FAIL" :value="evidenceData.invalidTraces.counts.fail" accent="amber" />
    <MetricCard label="INVALID" :value="evidenceData.invalidTraces.counts.invalid" accent="pink" />
  </div>
</div>

## Rules

- PAD-only trace → cannot prove B/X/Z action semantics. Mark `invalid` for
  action claims.
- Watchpoint on RAM field + matching frame capture → `verified`.
- Resident memory read ≠ active slot. Mark `observed`, not `verified`.

See [Memory map → Structs](../memory-map) for which fields are still unpinned.
