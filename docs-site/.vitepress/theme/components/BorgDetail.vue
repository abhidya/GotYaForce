<script setup lang="ts">
import { computed, onMounted, ref } from 'vue'
import { withBase } from 'vitepress'
import borgsData from '../../data/borg-moves.json'

type Borg = {
  id: string
  name: string
  number: number
  cost: number
  crystals: number
  tribe: string
  type: string
  rarity: string
  alt: boolean
  hp1: string | number
  hp10: string | number
  defense: string | number
  shot: string | number
  attack: string | number
  speed: string | number
  jumpType: string
  levelSchedule: string
  moves: any[]
}

const borgs = borgsData.borgs as Borg[]
const cross = borgsData.crossValidation as Record<string, { match?: number; of?: number; mismatches?: string[] }>

const id = ref<string | null>(null)
const ready = ref(false)
onMounted(() => {
  id.value = new URLSearchParams(window.location.search).get('id')
  ready.value = true
})

const borg = computed<Borg | null>(() => {
  if (!id.value) return null
  return borgs.find((b) => b.id === id.value) ?? null
})

const rarityColor: Record<string, string> = {
  S: 'var(--gf-likely)',
  A: 'var(--gf-accent-2)',
  B: 'var(--gf-muted)',
  C: 'var(--gf-verified)',
  D: 'var(--gf-invalid)'
}

const variants = [
  { key: 'normal', label: 'Normal', color: '#c9ced8' },
  { key: 'alt', label: 'Alt', color: '#ff6fb1' },
  { key: 'gold', label: 'Gold', color: '#d29922' },
  { key: 'silver', label: 'Silver', color: '#a7adb8' },
  { key: 'crystal', label: 'Crystal', color: '#58a6ff' },
  { key: 'black', label: 'Black', color: '#6b7280' }
]

const hp1n = computed(() => Number(String(borg.value?.hp1 ?? 0).replace(/[^0-9]/g, '')) || 0)
const hp10n = computed(() => Number(String(borg.value?.hp10 ?? 0).replace(/[^0-9]/g, '')) || 0)
const growthPct = computed(() => {
  if (!hp10n.value) return 100
  if (!hp1n.value) return 8
  return Math.max(6, Math.min(100, Math.round((hp1n.value / hp10n.value) * 100)))
})

const crossSummary = computed(() => {
  const parts: string[] = []
  for (const [key, v] of Object.entries(cross)) {
    if (typeof v.match === 'number' && typeof v.of === 'number') {
      parts.push(`${key}: ${v.match}/${v.of} match`)
    } else if (typeof v.match === 'number') {
      parts.push(`${key}: ${v.match} match`)
    }
  }
  return parts.join('; ')
})

const atlasLink = computed(() => withBase('/borgs/'))
</script>

<template>
  <div v-if="!ready" class="bd-loading">Loading…</div>

  <div v-else-if="!borg" class="bd-missing">
    <p>Borg not found{{ id ? `: <code>${id}</code>` : '' }}.</p>
    <a :href="atlasLink">← Back to Borg Atlas</a>
  </div>

  <div v-else class="bd-wrap">
    <a class="bd-back" :href="atlasLink">← Borg Atlas</a>

    <header class="bd-head">
      <h1 class="bd-title">{{ borg.name }}</h1>
      <span
        class="bd-rarity"
        :style="{ '--rc': rarityColor[borg.rarity] ?? 'var(--gf-muted)' }"
      >{{ borg.rarity }}</span>
      <div class="bd-meta">
        <span>{{ borg.tribe }}</span>
        <span class="bd-dot">·</span>
        <span>{{ borg.type }}</span>
        <span class="bd-dot">·</span>
        <code class="bd-id">{{ borg.id }}</code>
      </div>
    </header>

    <BorgModelViewer :id="borg.id" :name="borg.name" />

    <div class="bd-cols">
      <section class="bd-stats bd-panel">
        <div class="bd-panel-head">Core stats</div>
        <dl class="bd-grid">
          <div><dt>Cost</dt><dd>{{ borg.cost }}</dd></div>
          <div><dt>Crystals</dt><dd>{{ borg.crystals }}</dd></div>
          <div><dt>HP lvl 1</dt><dd>{{ borg.hp1 }}</dd></div>
          <div><dt>HP lvl 10</dt><dd>{{ borg.hp10 }}</dd></div>
          <div><dt>Defense</dt><dd>{{ borg.defense }}</dd></div>
          <div><dt>Shot</dt><dd>{{ borg.shot }}</dd></div>
          <div><dt>Attack</dt><dd>{{ borg.attack }}</dd></div>
          <div><dt>Speed</dt><dd>{{ borg.speed }}</dd></div>
          <div><dt>Jump type</dt><dd>{{ borg.jumpType }}</dd></div>
          <div><dt>Level-up</dt><dd>{{ borg.levelSchedule }}</dd></div>
        </dl>
      </section>

      <section class="bd-growth bd-panel">
        <div class="bd-panel-head">HP growth</div>
        <div class="bd-growth-row">
          <span class="bd-growth-lbl">L1</span>
          <span class="bd-growth-val">{{ borg.hp1 }}</span>
        </div>
        <div class="bd-bar">
          <div class="bd-bar-fill" :style="{ width: growthPct + '%' }">
            <span class="bd-bar-l1">{{ borg.hp1 }}</span>
            <span class="bd-bar-l10">{{ borg.hp10 }}</span>
          </div>
        </div>
        <div class="bd-growth-row bd-growth-end">
          <span class="bd-growth-lbl">L10</span>
          <span class="bd-growth-val">{{ borg.hp10 }}</span>
        </div>
        <p class="bd-growth-note">
          Bar fills from L1 to L10 HP — the left edge marks level-1 HP relative to level-10.
        </p>
      </section>
    </div>

    <section class="bd-panel bd-variants-panel">
      <div class="bd-panel-head">Color variants</div>
      <ul class="bd-variants">
        <li
          v-for="v in variants"
          :key="v.key"
          :class="{ dim: v.key === 'alt' && !borg.alt }"
        >
          <span class="bd-swatch" :style="{ background: v.color }" />
          <span class="bd-vlabel">{{ v.label }}</span>
          <span v-if="v.key === 'alt' && !borg.alt" class="bd-vnone">none</span>
        </li>
      </ul>
    </section>

    <section class="bd-panel bd-moves-panel">
      <div class="bd-panel-head">Moves ({{ borg.moves.length }})</div>

      <div v-if="borg.moves.length" class="bd-table-scroll">
        <table class="bd-table">
          <thead>
            <tr>
              <th>Name</th>
              <th>Type</th>
              <th>Solidity</th>
              <th>Penetration</th>
              <th>Refill</th>
              <th>Ammo 1/10</th>
              <th>Effect</th>
              <th>Notes</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="(m, i) in borg.moves" :key="i">
              <td class="bd-cell-name">{{ m.name }}</td>
              <td class="mono">{{ m.type ?? '—' }}</td>
              <td class="mono">{{ m.solidity ?? '—' }}</td>
              <td class="mono">{{ m.penetration ?? '—' }}</td>
              <td class="mono">{{ m.refillType ?? '—' }}</td>
              <td class="mono">{{ m.ammoLv1Lv10 ?? '—' }}</td>
              <td>{{ m.effect ?? '—' }}</td>
              <td class="bd-notes">
                <template v-if="m.explodes && m.explodes !== 'No'">
                  <span class="bd-chip bd-chip-warn">{{ m.explodes }}</span>
                </template>
                <template v-if="m.extra && Object.keys(m.extra).length">
                  <code class="bd-extra">{{ JSON.stringify(m.extra) }}</code>
                </template>
                <span v-if="(!m.explodes || m.explodes === 'No') && !(m.extra && Object.keys(m.extra).length)">—</span>
              </td>
            </tr>
          </tbody>
        </table>
      </div>
      <p v-else class="bd-empty">No moves catalogued yet for this borg.</p>
    </section>

    <footer class="bd-source">
      Data: <code>NTSC_Borgs.csv</code> + <code>wiki-borg-moves.json</code> (CC-BY-SA).
      Cross-validation: <span class="bd-cross">{{ crossSummary || 'n/a' }}</span>.
    </footer>
  </div>
</template>

<style scoped>
.bd-wrap { margin-top: 10px; }

.bd-loading, .bd-missing {
  padding: 32px;
  text-align: center;
  color: var(--gf-muted);
  font-family: var(--gf-mono);
}
.bd-missing code {
  font-family: var(--gf-mono);
  background: var(--gf-panel-2);
  padding: 1px 6px;
  border-radius: 4px;
  border: 1px solid var(--gf-border);
  color: var(--gf-accent);
}
.bd-missing a, .bd-back {
  color: var(--gf-accent-2);
  text-decoration: none;
  border-bottom: 1px dotted var(--gf-accent-2);
}
.bd-missing a:hover, .bd-back:hover { color: var(--gf-accent); border-bottom-color: var(--gf-accent); }
.bd-back {
  display: inline-block;
  font-size: 0.86rem;
  margin-bottom: 10px;
}

.bd-head {
  margin-bottom: 16px;
  display: flex;
  flex-wrap: wrap;
  align-items: center;
  gap: 10px 12px;
}
.bd-title {
  font-family: var(--gf-display);
  font-weight: 700;
  font-size: 1.8rem;
  margin: 0;
  letter-spacing: -0.01em;
}
.bd-rarity {
  font-family: var(--gf-mono);
  font-weight: 700;
  font-size: 1rem;
  width: 30px;
  height: 30px;
  display: inline-flex;
  align-items: center;
  justify-content: center;
  border-radius: 7px;
  color: var(--rc);
  background: color-mix(in srgb, var(--rc) 16%, transparent);
  border: 1px solid color-mix(in srgb, var(--rc) 55%, transparent);
}
.bd-meta {
  display: flex;
  flex-wrap: wrap;
  align-items: center;
  gap: 6px;
  color: var(--gf-muted);
  font-size: 0.86rem;
  width: 100%;
}
.bd-dot { color: var(--gf-faint); }
.bd-id {
  font-family: var(--gf-mono);
  font-size: 0.82rem;
  background: var(--gf-panel-2);
  padding: 1px 6px;
  border-radius: 4px;
  border: 1px solid var(--gf-border);
  color: var(--gf-accent);
}

.bd-panel {
  background: var(--gf-panel);
  border: 1px solid var(--gf-border);
  border-radius: 10px;
  padding: 14px 16px;
}
.bd-panel-head {
  font-family: var(--gf-display);
  font-size: 0.72rem;
  text-transform: uppercase;
  letter-spacing: 0.08em;
  color: var(--gf-muted);
  margin-bottom: 10px;
}

.bd-cols {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 14px;
  margin-bottom: 14px;
}
@media (max-width: 820px) {
  .bd-cols { grid-template-columns: 1fr; }
}

.bd-grid {
  display: grid;
  grid-template-columns: repeat(2, 1fr);
  gap: 6px 12px;
  margin: 0;
}
.bd-grid > div {
  display: flex;
  justify-content: space-between;
  align-items: baseline;
  gap: 8px;
  padding: 4px 8px;
  background: var(--gf-panel-2);
  border: 1px solid var(--gf-border);
  border-radius: 6px;
}
.bd-grid dt {
  font-size: 0.72rem;
  text-transform: uppercase;
  letter-spacing: 0.05em;
  color: var(--gf-muted);
}
.bd-grid dd {
  margin: 0;
  font-family: var(--gf-mono);
  font-size: 0.86rem;
  color: var(--gf-text);
}

.bd-growth-row {
  display: flex;
  align-items: baseline;
  justify-content: space-between;
  margin-bottom: 6px;
}
.bd-growth-end { margin-top: 6px; margin-bottom: 0; }
.bd-growth-lbl {
  font-family: var(--gf-display);
  font-size: 0.72rem;
  text-transform: uppercase;
  letter-spacing: 0.08em;
  color: var(--gf-muted);
}
.bd-growth-val {
  font-family: var(--gf-mono);
  font-size: 1.05rem;
  color: var(--gf-text);
}
.bd-bar {
  position: relative;
  height: 26px;
  background: var(--gf-bg);
  border: 1px solid var(--gf-border);
  border-radius: 6px;
  overflow: hidden;
}
.bd-bar-fill {
  position: relative;
  height: 100%;
  background: linear-gradient(90deg, var(--gf-accent-2), var(--gf-accent));
  border-right: 2px solid var(--gf-text);
  display: flex;
  align-items: center;
  justify-content: flex-start;
  min-width: 8px;
}
.bd-bar-l1 {
  font-family: var(--gf-mono);
  font-size: 0.74rem;
  color: #0a0a0a;
  font-weight: 700;
  padding-left: 6px;
}
.bd-bar-l10 {
  position: absolute;
  right: -52px;
  top: 50%;
  transform: translateY(-50%);
  font-family: var(--gf-mono);
  font-size: 0.74rem;
  color: var(--gf-text-dim);
  white-space: nowrap;
}
.bd-growth-note {
  font-size: 0.76rem;
  color: var(--gf-faint);
  margin: 8px 0 0;
}

.bd-variants-panel { margin-bottom: 14px; }
.bd-variants {
  list-style: none;
  padding: 0;
  margin: 0;
  display: flex;
  flex-wrap: wrap;
  gap: 10px;
}
.bd-variants li {
  display: inline-flex;
  align-items: center;
  gap: 6px;
  padding: 5px 10px;
  background: var(--gf-panel-2);
  border: 1px solid var(--gf-border);
  border-radius: 999px;
  font-size: 0.8rem;
  color: var(--gf-text-dim);
}
.bd-variants li.dim { opacity: 0.4; }
.bd-swatch {
  width: 12px;
  height: 12px;
  border-radius: 50%;
  border: 1px solid rgba(0, 0, 0, 0.4);
}
.bd-vnone {
  font-family: var(--gf-mono);
  font-size: 0.68rem;
  color: var(--gf-faint);
}

.bd-moves-panel { margin-bottom: 14px; }
.bd-table-scroll { overflow-x: auto; border: 1px solid var(--gf-border); border-radius: 8px; }
.bd-table {
  width: 100%;
  border-collapse: collapse;
  font-size: 0.86rem;
  min-width: 720px;
}
.bd-table thead { background: var(--gf-panel-2); }
.bd-table th {
  font-family: var(--gf-display);
  font-weight: 600;
  text-align: left;
  padding: 8px 11px;
  font-size: 0.72rem;
  text-transform: uppercase;
  letter-spacing: 0.06em;
  color: var(--gf-muted);
  border-bottom: 1px solid var(--gf-border);
  white-space: nowrap;
}
.bd-table td {
  padding: 8px 11px;
  border-bottom: 1px solid var(--gf-border);
  color: var(--gf-text);
  vertical-align: middle;
}
.bd-table tr:last-child td { border-bottom: none; }
.bd-table tr:nth-child(even) td { background: var(--gf-bg-elev); }
.bd-table .mono {
  font-family: var(--gf-mono);
  font-size: 0.8rem;
}
.bd-cell-name { font-weight: 600; color: var(--gf-text); }
.bd-notes { display: flex; flex-wrap: wrap; gap: 4px; align-items: center; }
.bd-chip {
  font-family: var(--gf-mono);
  font-size: 0.7rem;
  padding: 1px 7px;
  border-radius: 999px;
  border: 1px solid;
}
.bd-chip-warn {
  color: var(--gf-invalid);
  border-color: color-mix(in srgb, var(--gf-invalid) 45%, transparent);
  background: color-mix(in srgb, var(--gf-invalid) 12%, transparent);
}
.bd-extra {
  font-family: var(--gf-mono);
  font-size: 0.7rem;
  background: var(--gf-panel-2);
  padding: 1px 5px;
  border-radius: 4px;
  border: 1px solid var(--gf-border);
  color: var(--gf-accent);
}

.bd-empty {
  color: var(--gf-muted);
  font-style: italic;
  margin: 0;
  padding: 10px 0;
}

.bd-source {
  font-size: 0.78rem;
  color: var(--gf-muted);
  border-top: 1px solid var(--gf-border);
  padding-top: 12px;
}
.bd-source code {
  font-family: var(--gf-mono);
  background: var(--gf-panel-2);
  padding: 1px 5px;
  border-radius: 4px;
  border: 1px solid var(--gf-border);
  color: var(--gf-accent);
}
.bd-cross {
  color: var(--gf-text-dim);
}
</style>
