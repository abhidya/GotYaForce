---
title: Ghidra Corpus
---

<script setup>
import corpus from './.vitepress/data/ghidra-corpus.json'

const fmt = (value) => Number(value || 0).toLocaleString()
const pct = (value) => `${Number(value || 0).toFixed(1)}%`

const sourceRows = corpus.source.map((path) => ({
  path,
  role:
    path.endsWith('.gpr') ? 'Ghidra project file'
    : path.endsWith('.rep/') ? 'Ghidra project repository'
    : path.includes('ghidra-export') ? 'Bulk decompile export'
    : path.includes('function-evidence-index') ? 'Function evidence index'
    : path.includes('analysis_sessions') ? 'OGhidra session folder'
    : 'Applied findings note'
}))

const sessionRows = corpus.sessions.map((session) => ({
  session: session.id,
  created: session.createdAt ? session.createdAt.slice(0, 19).replace('T', ' ') : 'n/a',
  analyzed: fmt(session.actualAnalyzedFunctions),
  total: session.totalFunctions ? fmt(session.totalFunctions) : 'n/a',
  log: session.analysisLogEntries,
  path: session.path
}))
</script>

# Ghidra corpus

This is the source-of-truth decompilation layer behind the atlas: the checked-in
Ghidra project, the bulk decompiled C export, the searchable function index, and
the OGhidra analysis sessions that were used to turn raw functions into porting
evidence.

The important split: the Ghidra export covers **{{ fmt(corpus.metrics.functionCount) }}**
functions. The OGhidra sessions are AI-assisted analysis passes over that corpus,
currently covering **{{ fmt(corpus.metrics.uniqueAnalyzedFunctions) }}** unique
functions across **{{ fmt(corpus.metrics.sessionCount) }}** saved sessions.

<div class="corpus-metrics">
  <MetricCard
    label="Ghidra functions"
    :value="fmt(corpus.metrics.functionCount)"
    hint="Full boot.dol decompile index"
    accent="blue"
  />
  <MetricCard
    label="Chunk files"
    :value="fmt(corpus.metrics.chunkCount)"
    hint="Served on demand by Function Explorer"
    accent="green"
  />
  <MetricCard
    label="OGhidra sessions"
    :value="fmt(corpus.metrics.sessionCount)"
    :hint="`${fmt(corpus.metrics.sessionFunctionRecords)} session-function records`"
    accent="pink"
  />
  <MetricCard
    label="Unique analyzed"
    :value="fmt(corpus.metrics.uniqueAnalyzedFunctions)"
    :unit="pct(corpus.metrics.uniqueAnalyzedPct)"
    hint="Distinct functions touched by OGhidra sessions"
    accent="amber"
  />
</div>

## Source inventory

<AtlasTable
  :rows="sourceRows"
  :columns="[
    { key: 'role', label: 'Role' },
    { key: 'path', label: 'Source path', mono: true }
  ]"
/>

## How it connects

```text
GotchaForce.gpr / GotchaForce.rep
        |
        v
boot.dol + symbol map in Ghidra
        |
        v
ghidra-export/_index.tsv + chunk_0000.c ... chunk_0079.c
        |
        v
function-evidence-index.json
        |
        +--> Function Explorer, Call Graph, topic dashboards
        |
        +--> OGhidra analysis_sessions/session_*/session.json
                 |
                 v
        applied findings and port dossiers
```

## OGhidra sessions

These rows come from `research/tools/OGhidra/analysis_sessions/*/session.json`.
The counts are per-session analyzed functions; sessions overlap, so the unique
coverage metric above is the number to use for distinct function coverage.

<AtlasTable
  :rows="sessionRows"
  :columns="[
    { key: 'session', label: 'Session', mono: true },
    { key: 'created', label: 'Created', mono: true },
    { key: 'analyzed', label: 'Analyzed', mono: true },
    { key: 'total', label: 'Session total', mono: true },
    { key: 'log', label: 'Logs', mono: true },
    { key: 'path', label: 'Source path', mono: true }
  ]"
  searchable
  search-placeholder="Filter sessions..."
/>

## Function topic coverage

<AtlasTable
  :rows="corpus.topicRows"
  :columns="[
    { key: 'topic', label: 'Topic', mono: true },
    { key: 'functions', label: 'Functions', mono: true },
    { key: 'pct', label: 'Share', mono: true }
  ]"
/>

## High-signal anchors

These are high-caller functions from the indexed decompile corpus. They are good
entry points when tracing system behavior from the browser before opening Ghidra.

<AtlasTable
  :rows="corpus.anchorFunctions"
  :columns="[
    { key: 'address', label: 'Address', mono: true },
    { key: 'name', label: 'Name', mono: true },
    { key: 'topics', label: 'Topics' },
    { key: 'callers', label: 'Callers', mono: true },
    { key: 'callees', label: 'Callees', mono: true },
    { key: 'source', label: 'Source ref', mono: true }
  ]"
/>

## Open it

- Use the [Function Explorer](./functions) to search all
  **{{ fmt(corpus.metrics.functionCount) }}** indexed functions and open C bodies
  from `public/chunks/`.
- Use the [Call Graph](./call-graph) for the top connected functions.
- Use `research/decomp/oghidra-first-pass-port-findings-2026-07-12.md` for the
  first pass of OGhidra findings applied to the 1:1 port.

<style>
.corpus-metrics {
  display: grid;
  grid-template-columns: repeat(4, minmax(0, 1fr));
  gap: 12px;
  margin: 18px 0;
}

@media (max-width: 980px) {
  .corpus-metrics {
    grid-template-columns: repeat(2, minmax(0, 1fr));
  }
}

@media (max-width: 560px) {
  .corpus-metrics {
    grid-template-columns: 1fr;
  }
}
</style>
