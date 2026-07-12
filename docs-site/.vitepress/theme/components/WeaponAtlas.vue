<script setup lang="ts">
import { computed, ref } from 'vue'
import weaponData from '../../data/weapon-atlas.json'

type BorgWeaponRow = {
  id: string
  name: string
  tribe: string
  type: string
  rarity: string
  energy: string | number
  families: string[]
  familyList: string
  confidence: string
  evidenceCount: number
  archiveCount: number
  attachmentCandidates: number
  boneCandidates: number
  attackClipCandidates: number
  runtimeTraceNeeded: boolean
  runtimeTraceReasons: string
}

const borgs = weaponData.borgs as BorgWeaponRow[]
const view = ref<'borgs' | 'families' | 'assets' | 'needs'>('borgs')
const query = ref('')
const family = ref('')
const tribe = ref('')
const confidence = ref('')

const families = computed(() => (weaponData.families as any[]).map((row) => row.family).sort())
const tribes = computed(() => [...new Set(borgs.map((row) => row.tribe))].sort())
const confidences = computed(() => [...new Set(borgs.map((row) => row.confidence))].sort())

const filteredBorgs = computed(() => {
  const q = query.value.trim().toLowerCase()
  return borgs.filter((row) => {
    if (family.value && !row.families.includes(family.value)) return false
    if (tribe.value && row.tribe !== tribe.value) return false
    if (confidence.value && row.confidence !== confidence.value) return false
    if (!q) return true
    return [row.id, row.name, row.tribe, row.type, row.familyList]
      .some((value) => String(value || '').toLowerCase().includes(q))
  })
})

const CAP = 72
const visibleBorgs = computed(() => filteredBorgs.value.slice(0, CAP))

function fmt(value: number) {
  return Number(value || 0).toLocaleString()
}
</script>

<template>
  <section class="weapon-atlas">
    <div class="weapon-metrics">
      <MetricCard label="Mapped Borgs" :value="fmt(weaponData.summary.mappedBorgCount)" hint="Borg weapon/effect evidence" accent="blue" />
      <MetricCard label="Shared assets" :value="fmt(weaponData.summary.sharedAssetCount)" hint="Common projectiles/effects" accent="green" />
      <MetricCard label="Candidates" :value="fmt(weaponData.summary.candidateCount)" hint="Weapon/effect/projectile files" accent="amber" />
      <MetricCard label="Trace clips" :value="fmt(weaponData.summary.runtimeTraceAttackClipCount)" hint="Attack clip candidates" accent="pink" />
    </div>

    <div class="weapon-tabs" role="tablist" aria-label="Weapon atlas views">
      <button type="button" :class="{ active: view === 'borgs' }" @click="view = 'borgs'">Borgs</button>
      <button type="button" :class="{ active: view === 'families' }" @click="view = 'families'">Families</button>
      <button type="button" :class="{ active: view === 'assets' }" @click="view = 'assets'">Shared Assets</button>
      <button type="button" :class="{ active: view === 'needs' }" @click="view = 'needs'">Blockers</button>
    </div>

    <div v-if="view === 'borgs'" class="weapon-bar">
      <input v-model="query" type="search" placeholder="Filter Borg, family, tribe..." aria-label="Filter weapon borgs" />
      <select v-model="family" aria-label="Weapon family filter">
        <option value="">All families</option>
        <option v-for="item in families" :key="item" :value="item">{{ item }}</option>
      </select>
      <select v-model="tribe" aria-label="Tribe filter">
        <option value="">All tribes</option>
        <option v-for="item in tribes" :key="item" :value="item">{{ item }}</option>
      </select>
      <select v-model="confidence" aria-label="Confidence filter">
        <option value="">All confidence</option>
        <option v-for="item in confidences" :key="item" :value="item">{{ item }}</option>
      </select>
      <span>{{ filteredBorgs.length }} / {{ borgs.length }}</span>
    </div>

    <p v-if="view === 'borgs' && filteredBorgs.length > CAP" class="cap-note">
      Showing {{ CAP }} of {{ filteredBorgs.length }}. Refine filters for the rest.
    </p>

    <div v-if="view === 'borgs'" class="weapon-grid">
      <article v-for="row in visibleBorgs" :key="row.id" class="weapon-card">
        <header>
          <h3>{{ row.name }}</h3>
          <code>{{ row.id }}</code>
        </header>
        <p>{{ row.tribe }} / {{ row.type }}</p>
        <div class="family-tags">
          <span v-for="item in row.families" :key="item">{{ item }}</span>
        </div>
        <dl>
          <div><dt>Evidence</dt><dd>{{ row.evidenceCount }}</dd></div>
          <div><dt>Archives</dt><dd>{{ row.archiveCount }}</dd></div>
          <div><dt>Bones</dt><dd>{{ row.boneCandidates }}</dd></div>
          <div><dt>Clips</dt><dd>{{ row.attackClipCandidates }}</dd></div>
        </dl>
        <footer>
          <strong :class="row.confidence.toLowerCase()">{{ row.confidence }}</strong>
          <span v-if="row.runtimeTraceNeeded">needs trace</span>
        </footer>
      </article>
    </div>

    <AtlasTable
      v-else-if="view === 'families'"
      :rows="weaponData.families"
      :columns="[
        { key: 'label', label: 'Family' },
        { key: 'family', label: 'Key', mono: true },
        { key: 'borgCount', label: 'Borgs', mono: true },
        { key: 'sharedAssets', label: 'Shared assets', mono: true },
        { key: 'topTribes', label: 'Top tribes' },
        { key: 'sampleBorgs', label: 'Sample Borgs' }
      ]"
      searchable
    />

    <AtlasTable
      v-else-if="view === 'assets'"
      :rows="weaponData.sharedAssets"
      :columns="[
        { key: 'path', label: 'Path', mono: true },
        { key: 'role', label: 'Role' },
        { key: 'families', label: 'Families' },
        { key: 'confidence', label: 'Confidence', mono: true },
        { key: 'sizeBytes', label: 'Bytes', mono: true },
        { key: 'reason', label: 'Reason' }
      ]"
      searchable
    />

    <AtlasTable
      v-else
      :rows="weaponData.needs"
      :columns="[
        { key: 'need', label: 'Need' },
        { key: 'candidateCount', label: 'Candidates', mono: true },
        { key: 'examples', label: 'Examples', mono: true }
      ]"
      searchable
    />
  </section>
</template>

<style scoped>
.weapon-atlas {
  margin: 16px 0;
}

.weapon-metrics {
  display: grid;
  grid-template-columns: repeat(4, minmax(0, 1fr));
  gap: 12px;
  margin-bottom: 14px;
}

.weapon-tabs,
.weapon-bar {
  display: flex;
  flex-wrap: wrap;
  gap: 8px;
  align-items: center;
  padding: 10px;
  border: 1px solid var(--gf-border);
  border-radius: 8px;
  background: var(--gf-panel);
  margin-bottom: 12px;
}

.weapon-tabs button,
.weapon-bar input,
.weapon-bar select {
  min-height: 36px;
  border: 1px solid var(--gf-border);
  border-radius: 6px;
  background: var(--gf-bg);
  color: var(--gf-text);
  padding: 0 10px;
}

.weapon-tabs button {
  cursor: pointer;
}

.weapon-tabs button.active {
  border-color: var(--gf-accent-2);
  color: var(--gf-accent-2);
}

.weapon-bar input {
  flex: 1 1 260px;
  font-family: var(--gf-mono);
}

.weapon-bar span {
  margin-left: auto;
  color: var(--gf-muted);
  font-family: var(--gf-mono);
  font-size: 0.8rem;
}

.cap-note {
  margin: 0 0 12px;
  padding: 7px 10px;
  color: var(--gf-likely);
  border: 1px solid color-mix(in srgb, var(--gf-likely) 35%, transparent);
  border-radius: 6px;
  background: color-mix(in srgb, var(--gf-likely) 10%, transparent);
  font-family: var(--gf-mono);
  font-size: 0.78rem;
}

.weapon-grid {
  display: grid;
  grid-template-columns: repeat(auto-fill, minmax(260px, 1fr));
  gap: 12px;
}

.weapon-card {
  display: grid;
  gap: 8px;
  padding: 12px;
  border: 1px solid var(--gf-border);
  border-radius: 8px;
  background: var(--gf-panel);
}

.weapon-card header {
  display: flex;
  justify-content: space-between;
  gap: 8px;
  align-items: start;
}

.weapon-card h3 {
  margin: 0;
  font-family: var(--gf-display);
  line-height: 1.15;
}

.weapon-card code,
.weapon-card dd {
  font-family: var(--gf-mono);
}

.weapon-card p {
  margin: 0;
  color: var(--gf-muted);
  font-size: 0.82rem;
}

.family-tags {
  display: flex;
  flex-wrap: wrap;
  gap: 5px;
}

.family-tags span,
.weapon-card footer span,
.weapon-card footer strong {
  border: 1px solid var(--gf-border);
  border-radius: 999px;
  padding: 2px 8px;
  background: var(--gf-panel-2);
  font-family: var(--gf-mono);
  font-size: 0.7rem;
}

.weapon-card dl {
  display: grid;
  grid-template-columns: repeat(4, 1fr);
  gap: 6px;
  margin: 0;
}

.weapon-card dl div {
  border: 1px solid var(--gf-border);
  border-radius: 6px;
  padding: 5px 7px;
  background: var(--gf-panel-2);
}

.weapon-card dt {
  color: var(--gf-muted);
  font-size: 0.64rem;
  text-transform: uppercase;
}

.weapon-card dd {
  margin: 0;
}

.weapon-card footer {
  display: flex;
  flex-wrap: wrap;
  gap: 6px;
  justify-content: space-between;
}

.weapon-card footer .high {
  color: var(--gf-verified);
}

.weapon-card footer .medium {
  color: var(--gf-likely);
}

@media (max-width: 980px) {
  .weapon-metrics {
    grid-template-columns: repeat(2, minmax(0, 1fr));
  }
}

@media (max-width: 560px) {
  .weapon-metrics,
  .weapon-card dl {
    grid-template-columns: 1fr;
  }
}
</style>
