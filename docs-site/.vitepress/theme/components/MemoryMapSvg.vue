<script setup lang="ts">
import { ref, computed } from 'vue'
import memData from '../../data/memory.json'

type Region = {
  name: string
  addr?: string
  owner: string
  confidence: string
  notes: string
}
type Field = {
  name: string
  type: string
  offset?: string
  range?: string
  confidence: string
  notes?: string
}
type Struct = {
  name: string
  offset: string
  fields: Field[]
  source: string
}

const regions = memData.regions as Region[]
const structs = memData.structs as Struct[]
const sources = memData.source as string[]

const confidenceColor: Record<string, string> = {
  verified: 'var(--gf-verified)',
  observed: 'var(--gf-accent-2)',
  likely: 'var(--gf-likely)',
  unknown: 'var(--gf-faint)'
}

function confColor(c: string): string {
  return confidenceColor[c] || confidenceColor.unknown
}

function confAlphaBg(c: string): string {
  const color = confColor(c)
  return `color-mix(in srgb, ${color} 15%, transparent)`
}

function structsForRegion(r: Region): Struct[] {
  const key = r.name.toLowerCase()
  if (key.includes('heap') || key.includes('.bss')) {
    return structs
  }
  return []
}

const expanded = ref<Record<string, boolean>>({})
function toggle(name: string) {
  expanded.value[name] = !expanded.value[name]
}

const totalFields = computed(() =>
  structs.reduce((acc, s) => acc + s.fields.length, 0)
)
</script>

<template>
  <div class="gf-mem">
    <div class="gf-mem-stack">
      <div
        v-for="r in regions"
        :key="r.name"
        class="gf-mem-slab-row"
      >
        <div
          class="gf-mem-slab"
          :class="{ 'is-open': expanded[r.name] }"
          :style="{
            '--slab-color': confColor(r.confidence),
            background: confAlphaBg(r.confidence)
          }"
          @click="toggle(r.name)"
        >
          <div class="gf-mem-slab-label">
            <div class="gf-mem-slab-name">{{ r.name }}</div>
            <code v-if="r.addr" class="gf-mem-slab-addr">{{ r.addr }}</code>
            <code v-else class="gf-mem-slab-addr gf-mem-slab-addr-mute">—</code>
          </div>
          <div class="gf-mem-slab-body">
            <div class="gf-mem-slab-top">
              <span class="gf-mem-slab-owner">{{ r.owner }}</span>
              <span
                class="gf-mem-conf"
                :style="{ '--conf-color': confColor(r.confidence) }"
              >
                <span class="gf-mem-conf-dot" />
                {{ r.confidence }}
              </span>
            </div>
            <div class="gf-mem-slab-notes">{{ r.notes }}</div>
            <div class="gf-mem-slab-meta">
              <span v-if="structsForRegion(r).length">
                {{ structsForRegion(r).length }} struct(s) documented
              </span>
              <span v-else class="gf-mem-slab-meta-mute">no structs linked</span>
              <span class="gf-mem-slab-chevron">
                {{ expanded[r.name] ? '▾' : '▸' }}
              </span>
            </div>
          </div>
        </div>

        <div v-if="expanded[r.name]" class="gf-mem-slab-panel">
          <template v-if="structsForRegion(r).length">
            <div
              v-for="s in structsForRegion(r)"
              :key="s.name"
              class="gf-mem-struct-mini"
            >
              <div class="gf-mem-struct-mini-head">
                <span class="gf-mem-struct-mini-name">{{ s.name }}</span>
                <code class="gf-addr">{{ s.offset }}</code>
              </div>
              <div class="gf-mem-struct-fields">
                <div
                  v-for="f in s.fields"
                  :key="f.name"
                  class="gf-mem-struct-field"
                >
                  <span class="gf-mem-fn">{{ f.name }}</span>
                  <code class="gf-mem-ft">{{ f.type }}</code>
                  <span
                    class="gf-mem-conf"
                    :style="{ '--conf-color': confColor(f.confidence) }"
                  >
                    <span class="gf-mem-conf-dot" />
                    {{ f.confidence }}
                  </span>
                </div>
              </div>
              <div class="gf-mem-struct-mini-src">
                source: <code>{{ s.source }}</code>
              </div>
            </div>
          </template>
          <p v-else class="gf-mem-slab-empty">
            No structs linked to this region. See the inspector below for all
            documented structs.
          </p>
        </div>
      </div>
    </div>

    <section class="gf-mem-inspector">
      <div class="gf-mem-inspector-head">
        <h3>Struct inspector</h3>
        <span class="gf-mem-inspector-meta">
          {{ structs.length }} struct(s) · {{ totalFields }} field(s)
        </span>
      </div>

      <div v-for="s in structs" :key="s.name" class="gf-mem-struct-card">
        <div class="gf-mem-struct-card-head">
          <span class="gf-mem-struct-card-name">{{ s.name }}</span>
          <code class="gf-addr">{{ s.offset }}</code>
          <code class="gf-mem-struct-src">{{ s.source }}</code>
        </div>
        <div class="gf-mem-table-scroll">
          <table class="gf-mem-table">
            <thead>
              <tr>
                <th>Name</th>
                <th>Type</th>
                <th>Offset</th>
                <th>Range</th>
                <th>Confidence</th>
                <th>Notes</th>
              </tr>
            </thead>
            <tbody>
              <tr v-for="f in s.fields" :key="f.name">
                <td class="gf-mem-t-name">{{ f.name }}</td>
                <td><code class="gf-mem-ft">{{ f.type }}</code></td>
                <td><code class="gf-addr">{{ f.offset || '—' }}</code></td>
                <td><code class="gf-addr">{{ f.range || '—' }}</code></td>
                <td>
                  <span
                    class="gf-mem-conf"
                    :style="{ '--conf-color': confColor(f.confidence) }"
                  >
                    <span class="gf-mem-conf-dot" />
                    {{ f.confidence }}
                  </span>
                </td>
                <td class="gf-mem-t-notes">{{ f.notes || '—' }}</td>
              </tr>
            </tbody>
          </table>
        </div>
      </div>
    </section>

    <p class="gf-mem-sources">
      Sources:
      <code v-for="(s, i) in sources" :key="i">{{ s }}</code>
    </p>
  </div>
</template>

<style scoped>
.gf-mem {
  margin: 18px 0;
}
.gf-mem-stack {
  display: flex;
  flex-direction: column;
  gap: 8px;
}
.gf-mem-slab-row {
  display: flex;
  flex-direction: column;
}
.gf-mem-slab {
  display: flex;
  border: 1px solid var(--gf-border);
  border-left: 2px solid var(--slab-color, var(--gf-faint));
  border-radius: 8px;
  overflow: hidden;
  cursor: pointer;
  transition: border-color 0.15s, transform 0.1s;
  min-height: 70px;
}
.gf-mem-slab:hover {
  border-color: var(--gf-border-strong);
}
.gf-mem-slab.is-open {
  border-bottom-left-radius: 0;
  border-bottom-right-radius: 0;
}
.gf-mem-slab-label {
  flex: 0 0 140px;
  padding: 12px 14px;
  border-right: 1px solid var(--gf-border);
  background: var(--gf-panel-2);
  display: flex;
  flex-direction: column;
  justify-content: center;
  gap: 4px;
}
.gf-mem-slab-name {
  font-family: var(--gf-display);
  font-weight: 600;
  font-size: 0.94rem;
  color: var(--gf-text);
  line-height: 1.15;
}
.gf-mem-slab-addr {
  font-family: var(--gf-mono);
  font-size: 0.74rem;
  color: var(--gf-accent-2);
}
.gf-mem-slab-addr-mute {
  color: var(--gf-faint);
}
.gf-mem-slab-body {
  flex: 1 1 auto;
  padding: 10px 14px;
  display: flex;
  flex-direction: column;
  justify-content: center;
  gap: 4px;
}
.gf-mem-slab-top {
  display: flex;
  align-items: center;
  justify-content: space-between;
  gap: 10px;
}
.gf-mem-slab-owner {
  font-family: var(--gf-display);
  font-size: 0.7rem;
  text-transform: uppercase;
  letter-spacing: 0.08em;
  color: var(--gf-muted);
}
.gf-mem-slab-notes {
  font-size: 0.86rem;
  color: var(--gf-text-dim);
  line-height: 1.4;
}
.gf-mem-slab-meta {
  display: flex;
  justify-content: space-between;
  align-items: center;
  font-family: var(--gf-mono);
  font-size: 0.72rem;
  color: var(--gf-muted);
  margin-top: 2px;
}
.gf-mem-slab-meta-mute {
  color: var(--gf-faint);
}
.gf-mem-slab-chevron {
  font-family: var(--gf-mono);
  color: var(--gf-text-dim);
}
.gf-mem-slab-panel {
  background: var(--gf-panel);
  border: 1px solid var(--gf-border);
  border-top: none;
  border-radius: 0 0 8px 8px;
  padding: 12px 14px;
  display: flex;
  flex-direction: column;
  gap: 12px;
  margin-bottom: 4px;
}
.gf-mem-slab-empty {
  margin: 0;
  font-size: 0.84rem;
  color: var(--gf-muted);
}
.gf-mem-struct-mini {
  background: var(--gf-panel-2);
  border: 1px solid var(--gf-border);
  border-radius: 6px;
  padding: 10px 12px;
}
.gf-mem-struct-mini-head {
  display: flex;
  align-items: center;
  gap: 10px;
  margin-bottom: 8px;
}
.gf-mem-struct-mini-name {
  font-family: var(--gf-display);
  font-weight: 500;
  color: var(--gf-text);
}
.gf-mem-struct-fields {
  display: flex;
  flex-direction: column;
  gap: 4px;
}
.gf-mem-struct-field {
  display: flex;
  align-items: center;
  gap: 10px;
  font-size: 0.82rem;
}
.gf-mem-fn {
  color: var(--gf-text);
  min-width: 140px;
}
.gf-mem-struct-mini-src {
  font-family: var(--gf-mono);
  font-size: 0.72rem;
  color: var(--gf-muted);
  margin-top: 8px;
}

.gf-mem-conf {
  display: inline-flex;
  align-items: center;
  gap: 5px;
  font-family: var(--gf-mono);
  font-size: 0.72rem;
  color: var(--conf-color, var(--gf-text-dim));
}
.gf-mem-conf-dot {
  width: 8px;
  height: 8px;
  border-radius: 50%;
  background: var(--conf-color, var(--gf-faint));
  display: inline-block;
  box-shadow: 0 0 0 2px color-mix(in srgb, var(--conf-color, var(--gf-faint)) 20%, transparent);
}

.gf-mem-inspector {
  margin-top: 32px;
}
.gf-mem-inspector-head {
  display: flex;
  align-items: baseline;
  justify-content: space-between;
  border-bottom: 1px solid var(--gf-border);
  padding-bottom: 8px;
  margin-bottom: 14px;
}
.gf-mem-inspector-head h3 {
  font-family: var(--gf-display);
  font-size: 1.2rem;
  margin: 0;
  color: var(--gf-text);
}
.gf-mem-inspector-meta {
  font-family: var(--gf-mono);
  font-size: 0.74rem;
  color: var(--gf-muted);
}
.gf-mem-struct-card {
  background: var(--gf-panel);
  border: 1px solid var(--gf-border);
  border-left: 3px solid var(--gf-accent-2);
  border-radius: 8px;
  padding: 14px 16px;
  margin-bottom: 14px;
}
.gf-mem-struct-card-head {
  display: flex;
  align-items: center;
  gap: 12px;
  flex-wrap: wrap;
  margin-bottom: 10px;
}
.gf-mem-struct-card-name {
  font-family: var(--gf-display);
  font-weight: 600;
  font-size: 1rem;
  color: var(--gf-text);
}
.gf-mem-struct-src {
  font-family: var(--gf-mono);
  font-size: 0.72rem;
  color: var(--gf-muted);
  margin-left: auto;
}
.gf-mem-table-scroll {
  overflow-x: auto;
}
.gf-mem-table {
  width: 100%;
  border-collapse: collapse;
  font-size: 0.84rem;
}
.gf-mem-table th {
  text-align: left;
  font-family: var(--gf-display);
  font-size: 0.68rem;
  text-transform: uppercase;
  letter-spacing: 0.08em;
  color: var(--gf-muted);
  padding: 6px 10px;
  border-bottom: 1px solid var(--gf-border);
}
.gf-mem-table td {
  padding: 7px 10px;
  border-bottom: 1px solid var(--gf-border);
  vertical-align: top;
}
.gf-mem-table tr:last-child td {
  border-bottom: none;
}
.gf-mem-t-name {
  color: var(--gf-text);
  font-weight: 500;
}
.gf-mem-ft {
  font-family: var(--gf-mono);
  font-size: 0.78rem;
  color: var(--gf-accent);
}
.gf-mem-t-notes {
  color: var(--gf-text-dim);
  max-width: 320px;
}
.gf-mem-sources {
  margin-top: 16px;
  font-family: var(--gf-mono);
  font-size: 0.74rem;
  color: var(--gf-muted);
}
.gf-mem-sources code {
  margin-left: 6px;
  color: var(--gf-text-dim);
}
</style>
