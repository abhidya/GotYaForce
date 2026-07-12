<script setup lang="ts">
import { computed, ref } from 'vue'
import forceData from '../../data/force.json'

const view = ref<'spawn' | 'fusion' | 'variants'>('spawn')
const query = ref('')

const spawnRows = computed(() => {
  const q = query.value.trim().toLowerCase()
  const rows = forceData.spawnRows as any[]
  if (!q) return rows
  return rows.filter((row) =>
    [row.group, row.ptr, row.families, row.borgs, row.ids].some((value) =>
      String(value || '').toLowerCase().includes(q)
    )
  )
})

const fusionRows = computed(() => {
  const q = query.value.trim().toLowerCase()
  const rows = forceData.fusionRows as any[]
  if (!q) return rows
  return rows.filter((row) =>
    [row.base, row.partner, row.result, row.ptr, row.family].some((value) =>
      String(value || '').toLowerCase().includes(q)
    )
  )
})

function fmt(value: number) {
  return Number(value || 0).toLocaleString()
}
</script>

<template>
  <section class="force-atlas">
    <div class="force-metrics">
      <MetricCard label="Spawn groups" :value="fmt(forceData.spawnPools.groupCount)" :hint="forceData.spawnPools.address" accent="blue" />
      <MetricCard label="Fusion pairs" :value="fmt(forceData.fusion.pairCount)" :hint="forceData.fusion.address" accent="green" />
      <MetricCard label="Fusion families" :value="fmt(forceData.fusion.familyCount)" :hint="`${forceData.fusion.nonNullFamilies.length} active`" accent="amber" />
      <MetricCard label="Color variants" :value="fmt(forceData.colorVariants.length)" hint="Normal, alt, trophy colors" accent="pink" />
    </div>

    <div class="force-tabs">
      <button type="button" :class="{ active: view === 'spawn' }" @click="view = 'spawn'">Spawn Pools</button>
      <button type="button" :class="{ active: view === 'fusion' }" @click="view = 'fusion'">Fusion</button>
      <button type="button" :class="{ active: view === 'variants' }" @click="view = 'variants'">Variants</button>
      <input v-if="view !== 'variants'" v-model="query" type="search" placeholder="Filter current view..." aria-label="Filter force atlas" />
    </div>

    <div v-if="view === 'spawn'" class="spawn-grid">
      <article v-for="row in spawnRows" :key="row.group" class="force-card">
        <header>
          <h3>Group {{ row.group }}</h3>
          <code>{{ row.ptr }}</code>
        </header>
        <dl>
          <div><dt>Borgs</dt><dd>{{ row.count }}</dd></div>
          <div><dt>Families</dt><dd>{{ row.families }}</dd></div>
        </dl>
        <p>{{ row.borgs }}</p>
      </article>
    </div>

    <div v-else-if="view === 'fusion'" class="fusion-wrap">
      <AtlasTable
        :rows="forceData.fusionFamilyRows"
        :columns="[
          { key: 'family', label: 'Family', mono: true },
          { key: 'listPtr', label: 'List ptr', mono: true },
          { key: 'variants', label: 'Variants', mono: true },
          { key: 'pairs', label: 'Pairs', mono: true },
          { key: 'listWords', label: 'Words', mono: true }
        ]"
      />

      <div class="fusion-grid">
        <article v-for="row in fusionRows" :key="`${row.family}-${row.variant}-${row.partner}-${row.result}`" class="force-card">
          <header>
            <h3>Family {{ row.family }} / variant {{ row.variant }}</h3>
            <code>{{ row.ptr }}</code>
          </header>
          <p><strong>Base:</strong> {{ row.base }}</p>
          <p><strong>Partner:</strong> {{ row.partner }}</p>
          <p><strong>Result:</strong> {{ row.result }}</p>
        </article>
      </div>
    </div>

    <div v-else class="variant-grid">
      <article v-for="(variant, index) in forceData.colorVariants" :key="variant" class="variant-card">
        <span class="swatch" :class="variant" />
        <h3>{{ variant }}</h3>
        <code>slot {{ index }}</code>
      </article>
    </div>
  </section>
</template>

<style scoped>
.force-atlas {
  margin: 16px 0;
}

.force-metrics {
  display: grid;
  grid-template-columns: repeat(4, minmax(0, 1fr));
  gap: 12px;
  margin-bottom: 14px;
}

.force-tabs {
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

.force-tabs button,
.force-tabs input {
  min-height: 36px;
  border: 1px solid var(--gf-border);
  border-radius: 6px;
  background: var(--gf-bg);
  color: var(--gf-text);
  padding: 0 10px;
}

.force-tabs button {
  cursor: pointer;
}

.force-tabs button.active {
  border-color: var(--gf-accent-2);
  color: var(--gf-accent-2);
}

.force-tabs input {
  flex: 1 1 260px;
  font-family: var(--gf-mono);
}

.spawn-grid,
.fusion-grid,
.variant-grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(260px, 1fr));
  gap: 12px;
}

.fusion-grid {
  margin-top: 14px;
}

.force-card,
.variant-card {
  display: grid;
  gap: 8px;
  padding: 12px;
  border: 1px solid var(--gf-border);
  border-radius: 8px;
  background: var(--gf-panel);
}

.force-card header {
  display: flex;
  justify-content: space-between;
  gap: 8px;
  align-items: start;
}

.force-card h3,
.variant-card h3 {
  margin: 0;
  font-family: var(--gf-display);
  line-height: 1.15;
}

.force-card code,
.force-card dd,
.variant-card code {
  font-family: var(--gf-mono);
}

.force-card dl {
  display: grid;
  grid-template-columns: 90px 1fr;
  gap: 6px;
  margin: 0;
}

.force-card dl div {
  border: 1px solid var(--gf-border);
  border-radius: 6px;
  padding: 5px 7px;
  background: var(--gf-panel-2);
}

.force-card dt {
  color: var(--gf-muted);
  font-size: 0.64rem;
  text-transform: uppercase;
}

.force-card dd,
.force-card p {
  margin: 0;
}

.force-card p {
  color: var(--gf-text-dim);
  font-size: 0.82rem;
  overflow-wrap: anywhere;
}

.variant-card {
  grid-template-columns: auto 1fr auto;
  align-items: center;
}

.swatch {
  width: 28px;
  height: 28px;
  border-radius: 50%;
  border: 1px solid var(--gf-border);
}

.swatch.normal { background: #c9ced8; }
.swatch.alt { background: #ff6fb1; }
.swatch.gold { background: #d29922; }
.swatch.silver { background: #a7adb8; }
.swatch.crystal { background: #58a6ff; }
.swatch.black { background: #111827; }

@media (max-width: 980px) {
  .force-metrics {
    grid-template-columns: repeat(2, minmax(0, 1fr));
  }
}

@media (max-width: 560px) {
  .force-metrics,
  .force-card dl,
  .variant-card {
    grid-template-columns: 1fr;
  }
}
</style>
