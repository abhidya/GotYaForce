<script setup lang="ts">
import { ref, computed } from 'vue'
import matrixData from '../../data/type-matrix.json'

type Info = { kind: 'neutral' | 'red' | 'green'; pct: number }

const data = matrixData as unknown as {
  source: string
  address: string
  description: string
  labels: string[]
  matrix: number[][]
  indexing: string
}

const labels = data.labels
const matrix = data.matrix
const address = data.address

const summary = (data.description.split(/(?<=\.)\s/)[0] ?? '').trim()

const hoverRow = ref(-1)
const hoverCol = ref(-1)
const hoverVal = ref(1)
const tipX = ref(0)
const tipY = ref(0)

const selection = ref<{ attacker: string; defender: string; multiplier: number; r: number; c: number } | null>(null)

const emit = defineEmits<{
  (e: 'select', payload: { attacker: string; defender: string; multiplier: number }): void
}>()

function colorInfo(val: number): Info {
  if (val === 1) return { kind: 'neutral', pct: 0 }
  if (val < 1) return { kind: 'red', pct: Math.min(60, (1 - val) * 120) }
  return { kind: 'green', pct: Math.min(60, (val - 1) * 60) }
}

function cellStyle(val: number) {
  const info = colorInfo(val)
  if (info.kind === 'neutral') return {}
  const color = info.kind === 'red' ? 'var(--gf-invalid)' : 'var(--gf-verified)'
  return {
    background: `color-mix(in srgb, ${color} ${info.pct}%, transparent)`,
    color: info.pct >= 50 ? '#000' : 'var(--gf-text)'
  }
}

function cellClass(val: number, r: number, c: number) {
  const info = colorInfo(val)
  return {
    'is-neutral': info.kind === 'neutral',
    'is-red': info.kind === 'red',
    'is-green': info.kind === 'green',
    'in-row': hoverRow.value === r,
    'in-col': hoverCol.value === c,
    'is-hover': hoverRow.value === r && hoverCol.value === c,
    'is-selected': !!selection.value && selection.value.r === r && selection.value.c === c
  }
}

function formatVal(v: number) {
  const n = Number(v)
  if (n === 1) return '1.0'
  return n.toFixed(2).replace(/\.?0+$/, '')
}

function onCellEnter(r: number, c: number, val: number) {
  hoverRow.value = r
  hoverCol.value = c
  hoverVal.value = val
}
function onCellMove(e: MouseEvent) {
  const pad = 14
  const w = 300
  const h = 36
  let x = e.clientX + pad
  let y = e.clientY + pad
  if (x + w > window.innerWidth) x = e.clientX - w - pad
  if (y + h > window.innerHeight) y = e.clientY - h - pad
  tipX.value = x
  tipY.value = y
}
function onCellLeave() {
  hoverRow.value = -1
  hoverCol.value = -1
}
function onCellClick(r: number, c: number, val: number) {
  const sel = { attacker: labels[c], defender: labels[r], multiplier: val, r, c }
  selection.value = sel
  emit('select', { attacker: sel.attacker, defender: sel.defender, multiplier: sel.multiplier })
}

const hasHover = computed(() => hoverRow.value >= 0 && hoverCol.value >= 0)
</script>

<template>
  <div class="gf-tm">
    <header class="gf-tm-head">
      <div class="gf-tm-meta">
        <span class="gf-panel-header">Type effectiveness matrix</span>
        <code class="gf-addr">{{ address }}</code>
        <span class="gf-tm-index">{{ data.indexing }}</span>
      </div>
      <p class="gf-tm-summary">{{ summary }}</p>
    </header>

    <div class="gf-tm-frame">
      <div class="gf-tm-frame-top">ATTACKER →</div>
      <div class="gf-tm-frame-left">DEFENDER ↓</div>
      <div class="gf-tm-scroll">
        <div class="gf-tm-grid">
          <div class="gf-tm-corner"></div>
          <div
            v-for="(lbl, c) in labels"
            :key="'ch' + c"
            class="gf-tm-colhead"
            :class="{ active: hoverCol === c }"
            @mouseenter="hoverCol = c"
            @mouseleave="hoverCol = -1"
          >{{ lbl }}</div>

          <template v-for="(row, r) in matrix" :key="'r' + r">
            <div
              class="gf-tm-rowhead"
              :class="{ active: hoverRow === r }"
              @mouseenter="hoverRow = r"
              @mouseleave="hoverRow = -1"
            >{{ labels[r] }}</div>
            <button
              v-for="(val, c) in row"
              :key="'c' + r + '-' + c"
              type="button"
              class="gf-tm-cell"
              :class="cellClass(val, r, c)"
              :style="cellStyle(val)"
              :title="`Attacker: ${labels[c]} · Defender: ${labels[r]} · Multiplier: ${val}`"
              @mouseenter="onCellEnter(r, c, val)"
              @mousemove="onCellMove"
              @mouseleave="onCellLeave"
              @click="onCellClick(r, c, val)"
            >{{ formatVal(val) }}</button>
          </template>
        </div>
      </div>
    </div>

    <Transition name="gf-tm-fade">
      <div v-if="hasHover" class="gf-tm-tooltip" :style="{ left: tipX + 'px', top: tipY + 'px' }">
        Attacker: <strong>{{ labels[hoverCol] }}</strong> · Defender: <strong>{{ labels[hoverRow] }}</strong> · Multiplier: <strong>{{ hoverVal }}</strong>
      </div>
    </Transition>

    <div v-if="selection" class="gf-tm-selected">
      Selected: <strong>{{ selection.attacker }}</strong> vs <strong>{{ selection.defender }}</strong> =
      <code class="gf-addr">{{ selection.multiplier }}×</code> damage
    </div>
    <div v-else class="gf-tm-selected gf-tm-selected-empty">
      Click any cell to inspect the matchup.
    </div>

    <div class="gf-tm-legend">
      <span class="gf-tm-legend-label">0.5× (weaker)</span>
      <div class="gf-tm-legend-bar">
        <span class="gf-tm-legend-mid">1.0× (neutral)</span>
      </div>
      <span class="gf-tm-legend-label">2.0× (stronger)</span>
    </div>
  </div>
</template>

<style scoped>
.gf-tm {
  background: var(--gf-panel);
  border: 1px solid var(--gf-border);
  border-radius: 12px;
  padding: 16px;
  margin: 16px 0;
}
.gf-tm-head {
  margin-bottom: 14px;
}
.gf-tm-meta {
  display: flex;
  align-items: center;
  gap: 10px;
  flex-wrap: wrap;
}
.gf-tm-meta :deep(.gf-panel-header) {
  margin-bottom: 0;
}
.gf-tm-index {
  font-family: var(--gf-mono);
  font-size: 0.7rem;
  color: var(--gf-muted);
}
.gf-tm-summary {
  margin: 8px 0 0;
  font-size: 0.88rem;
  color: var(--gf-text-dim);
  line-height: 1.5;
}

.gf-tm-frame {
  display: grid;
  grid-template-columns: 18px 1fr;
  grid-template-rows: 18px 1fr;
}
.gf-tm-frame-top {
  grid-column: 2;
  grid-row: 1;
  font-family: var(--gf-mono);
  font-size: 0.62rem;
  letter-spacing: 0.12em;
  color: var(--gf-muted);
  text-align: center;
  align-self: end;
  padding-bottom: 2px;
}
.gf-tm-frame-left {
  grid-column: 1;
  grid-row: 2;
  writing-mode: vertical-rl;
  transform: rotate(180deg);
  font-family: var(--gf-mono);
  font-size: 0.62rem;
  letter-spacing: 0.12em;
  color: var(--gf-muted);
  text-align: center;
  align-self: center;
  justify-self: end;
  padding-right: 2px;
}

.gf-tm-scroll {
  grid-column: 2;
  grid-row: 2;
  overflow: auto;
  border: 1px solid var(--gf-border);
  border-radius: 8px;
  background: var(--gf-bg);
}
.gf-tm-grid {
  display: grid;
  grid-template-columns: 96px repeat(20, var(--gf-tm-cell, 36px));
  grid-template-rows: 92px repeat(20, var(--gf-tm-cell, 36px));
  width: max-content;
}

.gf-tm-corner {
  position: sticky;
  left: 0;
  top: 0;
  z-index: 4;
  background: var(--gf-panel);
  border-right: 1px solid var(--gf-border);
  border-bottom: 1px solid var(--gf-border);
}
.gf-tm-colhead {
  position: sticky;
  top: 0;
  z-index: 3;
  background: var(--gf-panel);
  border-bottom: 1px solid var(--gf-border);
  border-left: 1px solid var(--gf-border);
  writing-mode: vertical-rl;
  transform: rotate(180deg);
  font-family: var(--gf-display);
  font-size: 0.72rem;
  color: var(--gf-text);
  display: flex;
  align-items: center;
  justify-content: center;
  padding: 4px 2px;
  transition: background 0.12s, color 0.12s;
}
.gf-tm-colhead.active {
  background: color-mix(in srgb, var(--gf-accent-2) 22%, var(--gf-panel));
  color: var(--gf-text);
}
.gf-tm-rowhead {
  position: sticky;
  left: 0;
  z-index: 3;
  background: var(--gf-panel);
  border-right: 1px solid var(--gf-border);
  border-top: 1px solid var(--gf-border);
  font-family: var(--gf-display);
  font-size: 0.74rem;
  color: var(--gf-text);
  display: flex;
  align-items: center;
  justify-content: flex-end;
  padding: 0 8px;
  text-align: right;
  transition: background 0.12s;
}
.gf-tm-rowhead.active {
  background: color-mix(in srgb, var(--gf-accent-2) 22%, var(--gf-panel));
}

.gf-tm-cell {
  appearance: none;
  border: none;
  border-top: 1px solid var(--gf-border);
  border-left: 1px solid var(--gf-border);
  font-family: var(--gf-mono);
  font-size: 0.66rem;
  line-height: 1;
  padding: 0;
  cursor: pointer;
  transition: filter 0.1s, outline 0.1s;
  outline-offset: -2px;
  display: flex;
  align-items: center;
  justify-content: center;
  min-height: 0;
  min-width: 0;
}
.gf-tm-cell.is-neutral {
  background: var(--gf-panel-2);
  color: var(--gf-faint);
}
.gf-tm-cell.is-red,
.gf-tm-cell.is-green {
  color: var(--gf-text);
}
.gf-tm-cell.in-row,
.gf-tm-cell.in-col {
  filter: brightness(1.18);
}
.gf-tm-cell.is-hover {
  outline: 2px solid var(--gf-accent);
  filter: brightness(1.32);
  z-index: 2;
}
.gf-tm-cell.is-selected {
  outline: 2px solid var(--gf-accent-2);
  outline-offset: -2px;
  z-index: 2;
  box-shadow: inset 0 0 0 1px var(--gf-bg);
}

.gf-tm-tooltip {
  position: fixed;
  z-index: 50;
  pointer-events: none;
  background: var(--gf-panel);
  border: 1px solid var(--gf-border-strong);
  border-radius: 8px;
  padding: 8px 12px;
  font-family: var(--gf-mono);
  font-size: 0.76rem;
  color: var(--gf-text);
  box-shadow: 0 8px 24px rgba(0, 0, 0, 0.4);
  max-width: 320px;
}
.gf-tm-tooltip strong {
  color: var(--gf-accent-2);
  font-weight: 600;
}

.gf-tm-selected {
  margin-top: 14px;
  padding: 10px 14px;
  background: var(--gf-panel-2);
  border: 1px solid var(--gf-border);
  border-left: 3px solid var(--gf-accent-2);
  border-radius: 6px;
  font-family: var(--gf-display);
  font-size: 0.92rem;
  color: var(--gf-text);
}
.gf-tm-selected strong {
  color: var(--gf-accent);
  font-weight: 600;
}
.gf-tm-selected-empty {
  border-left-color: var(--gf-border-strong);
  color: var(--gf-muted);
  font-style: italic;
}

.gf-tm-legend {
  margin-top: 14px;
  display: flex;
  align-items: center;
  gap: 10px;
}
.gf-tm-legend-label {
  font-family: var(--gf-mono);
  font-size: 0.7rem;
  color: var(--gf-muted);
  white-space: nowrap;
}
.gf-tm-legend-bar {
  position: relative;
  flex: 1;
  height: 12px;
  border-radius: 6px;
  border: 1px solid var(--gf-border);
  background: linear-gradient(
    to right,
    color-mix(in srgb, var(--gf-invalid) 60%, transparent) 0%,
    var(--gf-panel-2) 50%,
    color-mix(in srgb, var(--gf-verified) 60%, transparent) 100%
  );
}
.gf-tm-legend-mid {
  position: absolute;
  left: 50%;
  top: 16px;
  transform: translateX(-50%);
  font-family: var(--gf-mono);
  font-size: 0.66rem;
  color: var(--gf-muted);
  white-space: nowrap;
}

.gf-tm-fade-enter-active,
.gf-tm-fade-leave-active {
  transition: opacity 0.12s ease;
}
.gf-tm-fade-enter-from,
.gf-tm-fade-leave-to {
  opacity: 0;
}

@media (max-width: 768px) {
  .gf-tm-grid {
    grid-template-columns: 72px repeat(20, 26px);
    grid-template-rows: 70px repeat(20, 26px);
  }
  .gf-tm-colhead {
    font-size: 0.62rem;
    padding: 3px 1px;
  }
  .gf-tm-rowhead {
    font-size: 0.64rem;
    padding: 0 5px;
  }
  .gf-tm-cell {
    font-size: 0.54rem;
  }
  .gf-tm-legend {
    flex-wrap: wrap;
  }
  .gf-tm-legend-bar {
    order: 4;
    flex-basis: 100%;
    margin-top: 14px;
  }
}
</style>
