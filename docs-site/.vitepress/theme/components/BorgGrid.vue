<script setup lang="ts">
import { computed, ref } from 'vue'
import { withBase } from 'vitepress'
import borgsData from '../../data/borg-moves.json'
import BorgCard from './BorgCard.vue'

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
const total = borgsData.count

const tribes = computed(() => Array.from(new Set(borgs.map((b) => b.tribe))).sort())
const types = computed(() => Array.from(new Set(borgs.map((b) => b.type))).sort())
const rarities = computed(() => Array.from(new Set(borgs.map((b) => b.rarity))).sort())

const query = ref('')
const tribe = ref('')
const type = ref('')
const rarity = ref('')
const sortBy = ref<'number' | 'name' | 'cost' | 'hp'>('number')

const filtered = computed(() => {
  const q = query.value.trim().toLowerCase()
  let out = borgs.filter((b) => {
    if (tribe.value && b.tribe !== tribe.value) return false
    if (type.value && b.type !== type.value) return false
    if (rarity.value && b.rarity !== rarity.value) return false
    if (!q) return true
    return (
      b.name.toLowerCase().includes(q) ||
      b.tribe.toLowerCase().includes(q) ||
      b.type.toLowerCase().includes(q) ||
      b.id.toLowerCase().includes(q)
    )
  })
  const hpNum = (v: string | number) => Number(String(v).replace(/[^0-9]/g, '')) || 0
  switch (sortBy.value) {
    case 'name':
      out = out.slice().sort((a, b) => a.name.localeCompare(b.name))
      break
    case 'cost':
      out = out.slice().sort((a, b) => Number(b.cost) - Number(a.cost))
      break
    case 'hp':
      out = out.slice().sort((a, b) => hpNum(b.hp10) - hpNum(a.hp10))
      break
    case 'number':
    default:
      out = out.slice().sort((a, b) => a.number - b.number)
  }
  return out
})

const CAP = 60
const capped = computed(() => filtered.value.length > CAP)
const visible = computed(() => (capped.value ? filtered.value.slice(0, CAP) : filtered.value))

function go(b: Borg) {
  window.location.href = withBase('/borgs/detail.html?id=' + b.id)
}

function resetFilters() {
  query.value = ''
  tribe.value = ''
  type.value = ''
  rarity.value = ''
  sortBy.value = 'number'
}
</script>

<template>
  <div class="bg-wrap">
    <div class="bg-bar">
      <input
        v-model="query"
        type="search"
        class="bg-search"
        placeholder="Filter by name, tribe, type, id…"
        aria-label="Filter borgs"
      />
      <select v-model="tribe" class="bg-select" aria-label="Tribe filter">
        <option value="">All tribes</option>
        <option v-for="t in tribes" :key="t" :value="t">{{ t }}</option>
      </select>
      <select v-model="type" class="bg-select" aria-label="Type filter">
        <option value="">All types</option>
        <option v-for="t in types" :key="t" :value="t">{{ t }}</option>
      </select>
      <select v-model="rarity" class="bg-select" aria-label="Rarity filter">
        <option value="">All rarities</option>
        <option v-for="r in rarities" :key="r" :value="r">{{ r }}</option>
      </select>
      <select v-model="sortBy" class="bg-select" aria-label="Sort">
        <option value="number">Sort: Number</option>
        <option value="name">Sort: Name</option>
        <option value="cost">Sort: Cost ↓</option>
        <option value="hp">Sort: HP ↓</option>
      </select>
      <span class="bg-count">{{ filtered.length }} / {{ total }}</span>
      <button class="bg-reset" type="button" @click="resetFilters">Reset</button>
    </div>

    <p v-if="capped" class="bg-cap-note">
      Showing {{ CAP }} of {{ filtered.length }} — refine filters to see more.
    </p>

    <div v-if="visible.length" class="bg-grid">
      <BorgCard v-for="b in visible" :key="b.id" :borg="b" @click="go(b)" />
    </div>
    <p v-else class="bg-empty">No borgs match the current filters.</p>
  </div>
</template>

<style scoped>
.bg-wrap { margin-top: 14px; }

.bg-bar {
  display: flex;
  flex-wrap: wrap;
  align-items: center;
  gap: 8px;
  padding: 10px;
  background: var(--gf-panel);
  border: 1px solid var(--gf-border);
  border-radius: 10px;
  margin-bottom: 14px;
}
.bg-search {
  flex: 1 1 220px;
  min-width: 160px;
  background: var(--gf-bg);
  border: 1px solid var(--gf-border);
  border-radius: 8px;
  color: var(--gf-text);
  font-family: var(--gf-mono);
  padding: 7px 11px;
  font-size: 0.88rem;
}
.bg-search:focus {
  outline: none;
  border-color: var(--gf-accent-2);
}
.bg-select {
  background: var(--gf-bg);
  border: 1px solid var(--gf-border);
  border-radius: 8px;
  color: var(--gf-text);
  font-family: var(--gf-body);
  font-size: 0.84rem;
  padding: 7px 9px;
  cursor: pointer;
}
.bg-select:focus { outline: none; border-color: var(--gf-accent-2); }

.bg-count {
  font-family: var(--gf-mono);
  font-size: 0.78rem;
  color: var(--gf-muted);
  margin-left: auto;
  white-space: nowrap;
}
.bg-reset {
  background: transparent;
  border: 1px solid var(--gf-border);
  border-radius: 8px;
  color: var(--gf-muted);
  font-family: var(--gf-body);
  font-size: 0.8rem;
  padding: 6px 10px;
  cursor: pointer;
  transition: color 0.14s, border-color 0.14s;
}
.bg-reset:hover { color: var(--gf-accent); border-color: var(--gf-accent); }

.bg-grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(260px, 1fr));
  gap: 14px;
}

.bg-cap-note {
  font-family: var(--gf-mono);
  font-size: 0.78rem;
  color: var(--gf-likely);
  background: color-mix(in srgb, var(--gf-likely) 10%, transparent);
  border: 1px solid color-mix(in srgb, var(--gf-likely) 35%, transparent);
  border-radius: 6px;
  padding: 6px 10px;
  margin: 0 0 12px;
}

.bg-empty {
  text-align: center;
  color: var(--gf-muted);
  font-style: italic;
  padding: 28px 0;
}
</style>
