<script setup lang="ts">
import { computed, ref, watch } from 'vue'
import stageData from '../../data/stage-atlas.json'

type StageRow = {
  id: string
  arena: string
  challengeByte: string
  archiveGroup: string
  inChallengePool: boolean
  status: 'verified' | 'observed' | 'likely' | 'unknown' | 'invalid'
  visualPieces: number
  nonEmptyPieces: number
  collisionFiles: number
  completeCollisionTriplet: boolean
  setArcs: number
  jobjCount: number
  pobjCount: number
  materialCount: number
  stageArcBytes: number
  pzzBytes: number
  sourcePath: string
}

const rows = stageData.rows as StageRow[]
const query = ref('')
const status = ref('')
const pool = ref('')
const selectedId = ref(rows[0]?.id ?? '')

const statuses = computed(() => [...new Set(rows.map((row) => row.status))].sort())

const filtered = computed(() => {
  const q = query.value.trim().toLowerCase()
  return rows.filter((row) => {
    if (status.value && row.status !== status.value) return false
    if (pool.value === 'pool' && !row.inChallengePool) return false
    if (pool.value === 'nonpool' && row.inChallengePool) return false
    if (!q) return true
    return [row.id, row.arena, row.archiveGroup, row.challengeByte, row.sourcePath]
      .some((value) => String(value || '').toLowerCase().includes(q))
  })
})

const selected = computed(() => rows.find((row) => row.id === selectedId.value) ?? filtered.value[0] ?? rows[0])

watch(filtered, (next) => {
  if (next.length && !next.some((row) => row.id === selectedId.value)) selectedId.value = next[0].id
})

function fmt(value: number) {
  return Number(value || 0).toLocaleString()
}

function bytes(value: number) {
  if (!value) return 'n/a'
  if (value > 1024 * 1024) return `${(value / 1024 / 1024).toFixed(1)} MB`
  return `${Math.round(value / 1024)} KB`
}
</script>

<template>
  <section class="atlas-shell">
    <div class="atlas-metrics">
      <MetricCard label="Named arenas" :value="fmt(stageData.summary.namedArenas)" hint="Challenge naming decode" accent="blue" />
      <MetricCard label="Stage exports" :value="fmt(stageData.summary.exportStageCount)" hint="ARC/PZZ pairs" accent="green" />
      <MetricCard label="Collision exports" :value="fmt(stageData.summary.collisionStageCount)" hint="Stages with hit files" accent="amber" />
      <MetricCard label="Challenge pool" :value="fmt(stageData.summary.challengePoolCount)" hint="Arena rotation entries" accent="pink" />
    </div>

    <div class="atlas-bar">
      <input v-model="query" type="search" placeholder="Filter stage, arena, archive..." aria-label="Filter stages" />
      <select v-model="status" aria-label="Status filter">
        <option value="">All statuses</option>
        <option v-for="item in statuses" :key="item" :value="item">{{ item }}</option>
      </select>
      <select v-model="pool" aria-label="Challenge pool filter">
        <option value="">All arenas</option>
        <option value="pool">Challenge pool</option>
        <option value="nonpool">Not in pool</option>
      </select>
      <span>{{ filtered.length }} / {{ rows.length }}</span>
    </div>

    <div class="stage-layout">
      <div class="stage-grid">
        <button
          v-for="row in filtered"
          :key="row.id"
          type="button"
          class="stage-card"
          :class="{ active: selected?.id === row.id }"
          @click="selectedId = row.id"
        >
          <header>
            <strong>{{ row.id }}</strong>
            <StatusBadge :status="row.status" />
          </header>
          <h3>{{ row.arena }}</h3>
          <p>{{ row.archiveGroup }}</p>
          <dl>
            <div><dt>DAE</dt><dd>{{ row.visualPieces }}</dd></div>
            <div><dt>Hit</dt><dd>{{ row.collisionFiles }}</dd></div>
            <div><dt>JOBJ</dt><dd>{{ row.jobjCount }}</dd></div>
          </dl>
        </button>
      </div>

      <aside v-if="selected" class="stage-detail">
        <div class="panel-eyebrow">Selected stage</div>
        <h2>{{ selected.arena }}</h2>
        <code>{{ selected.id }} / {{ selected.archiveGroup }}</code>
        <StatusBadge :status="selected.status" />

        <dl class="detail-grid">
          <div><dt>Challenge byte</dt><dd>{{ selected.challengeByte || 'n/a' }}</dd></div>
          <div><dt>Challenge pool</dt><dd>{{ selected.inChallengePool ? 'yes' : 'no' }}</dd></div>
          <div><dt>Visual pieces</dt><dd>{{ selected.visualPieces }} / {{ selected.nonEmptyPieces }} non-empty</dd></div>
          <div><dt>Collision</dt><dd>{{ selected.collisionFiles }} files{{ selected.completeCollisionTriplet ? ', full triplet' : '' }}</dd></div>
          <div><dt>Set arcs</dt><dd>{{ selected.setArcs }}</dd></div>
          <div><dt>Render state</dt><dd>{{ selected.pobjCount }} POBJ, {{ selected.materialCount }} materials</dd></div>
          <div><dt>ARC size</dt><dd>{{ bytes(selected.stageArcBytes) }}</dd></div>
          <div><dt>PZZ size</dt><dd>{{ bytes(selected.pzzBytes) }}</dd></div>
        </dl>

        <p class="source-path">{{ selected.sourcePath }}</p>
      </aside>
    </div>
  </section>
</template>

<style scoped>
.atlas-shell {
  margin: 16px 0;
}

.atlas-metrics {
  display: grid;
  grid-template-columns: repeat(4, minmax(0, 1fr));
  gap: 12px;
  margin-bottom: 14px;
}

.atlas-bar {
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

.atlas-bar input,
.atlas-bar select {
  min-height: 36px;
  border: 1px solid var(--gf-border);
  border-radius: 6px;
  background: var(--gf-bg);
  color: var(--gf-text);
  padding: 0 10px;
}

.atlas-bar input {
  flex: 1 1 260px;
  font-family: var(--gf-mono);
}

.atlas-bar span {
  margin-left: auto;
  color: var(--gf-muted);
  font-family: var(--gf-mono);
  font-size: 0.8rem;
}

.stage-layout {
  display: grid;
  grid-template-columns: minmax(0, 1fr) 340px;
  gap: 14px;
}

.stage-grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(230px, 1fr));
  gap: 12px;
}

.stage-card {
  display: grid;
  gap: 8px;
  min-height: 158px;
  padding: 12px;
  text-align: left;
  border: 1px solid var(--gf-border);
  border-radius: 8px;
  background: var(--gf-panel);
  color: var(--gf-text);
  cursor: pointer;
}

.stage-card:hover,
.stage-card.active {
  border-color: var(--gf-accent-2);
}

.stage-card header {
  display: flex;
  justify-content: space-between;
  gap: 8px;
  align-items: center;
}

.stage-card strong,
.source-path,
.stage-detail code {
  font-family: var(--gf-mono);
}

.stage-card h3,
.stage-detail h2 {
  margin: 0;
  font-family: var(--gf-display);
  line-height: 1.15;
}

.stage-card p {
  margin: 0;
  color: var(--gf-muted);
  font-family: var(--gf-mono);
  font-size: 0.78rem;
}

.stage-card dl,
.detail-grid {
  display: grid;
  gap: 6px;
  margin: 0;
}

.stage-card dl {
  grid-template-columns: repeat(3, 1fr);
}

.stage-card div,
.detail-grid div {
  border: 1px solid var(--gf-border);
  border-radius: 6px;
  background: var(--gf-panel-2);
  padding: 6px 8px;
}

dt {
  color: var(--gf-muted);
  font-size: 0.68rem;
  text-transform: uppercase;
  letter-spacing: 0;
}

dd {
  margin: 0;
  color: var(--gf-text);
  font-family: var(--gf-mono);
  font-size: 0.84rem;
}

.stage-detail {
  display: flex;
  flex-direction: column;
  gap: 10px;
  padding: 14px;
  border: 1px solid var(--gf-border);
  border-radius: 8px;
  background: var(--gf-panel);
}

.panel-eyebrow {
  color: var(--gf-muted);
  font-size: 0.72rem;
  text-transform: uppercase;
  letter-spacing: 0;
}

.detail-grid {
  grid-template-columns: 1fr;
}

.source-path {
  margin: 0;
  color: var(--gf-faint);
  overflow-wrap: anywhere;
  font-size: 0.76rem;
}

@media (max-width: 980px) {
  .atlas-metrics {
    grid-template-columns: repeat(2, minmax(0, 1fr));
  }

  .stage-layout {
    grid-template-columns: 1fr;
  }
}

@media (max-width: 560px) {
  .atlas-metrics {
    grid-template-columns: 1fr;
  }
}
</style>
