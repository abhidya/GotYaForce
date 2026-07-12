<script setup lang="ts">
import { computed, ref } from 'vue'
import { withBase } from 'vitepress'
import modeData from '../../data/mode-atlas.json'

type ModeRow = {
  id: string
  name: string
  status: 'verified' | 'observed' | 'likely' | 'unknown' | 'invalid'
  route: string
  functions: number
  source: string
  notes: string
}

const modes = modeData.modes as ModeRow[]
const query = ref('')
const status = ref('')

const statuses = computed(() => [...new Set(modes.map((mode) => mode.status))].sort())

const filteredModes = computed(() => {
  const q = query.value.trim().toLowerCase()
  return modes.filter((mode) => {
    if (status.value && mode.status !== status.value) return false
    if (!q) return true
    return [mode.name, mode.id, mode.notes, mode.source]
      .some((value) => String(value || '').toLowerCase().includes(q))
  })
})

function fmt(value: number) {
  return Number(value || 0).toLocaleString()
}
</script>

<template>
  <section class="mode-atlas">
    <div class="mode-metrics">
      <MetricCard label="Top-level modes" :value="fmt(modeData.summary.modes)" hint="Dispatcher-facing rows" accent="blue" />
      <MetricCard label="Verified" :value="fmt(modeData.summary.verified)" hint="Directly decoded flow" accent="green" />
      <MetricCard label="Observed" :value="fmt(modeData.summary.observed)" hint="Traced behavior" accent="amber" />
      <MetricCard label="Related funcs" :value="fmt(modeData.summary.relatedFunctions)" hint="Topic-tag evidence" accent="pink" />
    </div>

    <div class="mode-bar">
      <input v-model="query" type="search" placeholder="Filter mode, note, source..." aria-label="Filter modes" />
      <select v-model="status" aria-label="Mode status filter">
        <option value="">All statuses</option>
        <option v-for="item in statuses" :key="item" :value="item">{{ item }}</option>
      </select>
      <span>{{ filteredModes.length }} / {{ modes.length }}</span>
    </div>

    <div class="mode-grid">
      <article v-for="mode in filteredModes" :key="mode.id" class="mode-card">
        <header>
          <h3>{{ mode.name }}</h3>
          <StatusBadge :status="mode.status" />
        </header>
        <p>{{ mode.notes }}</p>
        <dl>
          <div><dt>Functions</dt><dd>{{ mode.functions }}</dd></div>
          <div><dt>Route</dt><dd><code>{{ mode.route }}</code></dd></div>
        </dl>
        <code class="source">{{ mode.source }}</code>
        <a :href="withBase(mode.route)">Open trace</a>
      </article>
    </div>
  </section>
</template>

<style scoped>
.mode-atlas {
  margin: 16px 0;
}

.mode-metrics {
  display: grid;
  grid-template-columns: repeat(4, minmax(0, 1fr));
  gap: 12px;
  margin-bottom: 14px;
}

.mode-bar {
  display: flex;
  flex-wrap: wrap;
  gap: 8px;
  align-items: center;
  padding: 10px;
  border: 1px solid var(--gf-border);
  border-radius: 8px;
  background: var(--gf-panel);
  margin-bottom: 14px;
}

.mode-bar input,
.mode-bar select {
  min-height: 36px;
  border: 1px solid var(--gf-border);
  border-radius: 6px;
  background: var(--gf-bg);
  color: var(--gf-text);
  padding: 0 10px;
}

.mode-bar input {
  flex: 1 1 260px;
  font-family: var(--gf-mono);
}

.mode-bar span {
  margin-left: auto;
  color: var(--gf-muted);
  font-family: var(--gf-mono);
  font-size: 0.8rem;
}

.mode-grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(270px, 1fr));
  gap: 12px;
}

.mode-card {
  display: grid;
  gap: 9px;
  padding: 12px;
  border: 1px solid var(--gf-border);
  border-radius: 8px;
  background: var(--gf-panel);
}

.mode-card header {
  display: flex;
  gap: 10px;
  justify-content: space-between;
  align-items: start;
}

.mode-card h3 {
  margin: 0;
  font-family: var(--gf-display);
  line-height: 1.15;
}

.mode-card p {
  margin: 0;
  color: var(--gf-text-dim);
  font-size: 0.86rem;
}

.mode-card dl {
  display: grid;
  grid-template-columns: repeat(2, minmax(0, 1fr));
  gap: 6px;
  margin: 0;
}

.mode-card dl div {
  border: 1px solid var(--gf-border);
  border-radius: 6px;
  padding: 6px 8px;
  background: var(--gf-panel-2);
}

.mode-card dt {
  color: var(--gf-muted);
  font-size: 0.66rem;
  text-transform: uppercase;
  letter-spacing: 0.05em;
}

.mode-card dd {
  margin: 0;
  font-family: var(--gf-mono);
  font-size: 0.82rem;
}

.mode-card code,
.source {
  font-family: var(--gf-mono);
}

.source {
  color: var(--gf-faint);
  font-size: 0.76rem;
  overflow-wrap: anywhere;
}

.mode-card a {
  min-height: 36px;
  display: inline-flex;
  width: fit-content;
  align-items: center;
  border: 1px solid var(--gf-accent-2);
  border-radius: 6px;
  padding: 0 10px;
  color: var(--gf-accent-2);
  font-family: var(--gf-mono);
  font-size: 0.78rem;
  text-decoration: none;
}

.mode-card a:hover {
  color: var(--gf-accent);
  border-color: var(--gf-accent);
}

@media (max-width: 980px) {
  .mode-metrics {
    grid-template-columns: repeat(2, minmax(0, 1fr));
  }
}

@media (max-width: 560px) {
  .mode-metrics,
  .mode-card dl {
    grid-template-columns: 1fr;
  }
}
</style>
