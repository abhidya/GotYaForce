<script setup lang="ts">
import { computed, onMounted, ref, watch } from 'vue'
import { withBase } from 'vitepress'
import functionsData from '../../data/functions.json'

type Fn = {
  a: string
  n: string
  inf: string | null
  chunk: string
  ls: number
  le: number
  cnt: number
  cc: number
  ce: number
  t: string[]
  src: string | null
}

const allFns: Fn[] = functionsData.functions
const totalCount: number = functionsData.count

const query = ref('')
const topic = ref('all')
const sortMode = ref<'callers' | 'name' | 'addr'>('callers')

const topics = computed(() => {
  const set = new Set<string>()
  for (const f of allFns) for (const t of f.t) set.add(t)
  return [...set].sort()
})

const filtered = computed<Fn[]>(() => {
  const q = query.value.trim().toLowerCase()
  const tSel = topic.value
  let rows = allFns
  if (tSel !== 'all') rows = rows.filter((f) => f.t.includes(tSel))
  if (q) rows = rows.filter((f) => f.n.toLowerCase().includes(q) || f.a.toLowerCase().includes(q))
  const sorted = rows.slice()
  if (sortMode.value === 'callers') sorted.sort((a, b) => b.cc - a.cc || a.a.localeCompare(b.a))
  else if (sortMode.value === 'name') sorted.sort((a, b) => a.n.localeCompare(b.n) || a.a.localeCompare(b.a))
  else sorted.sort((a, b) => a.a.localeCompare(b.a))
  return sorted
})

const MAX_VISIBLE = 200
const visible = computed(() => filtered.value.slice(0, MAX_VISIBLE))

const selectedAddr = ref<string | null>(null)
const selected = computed<Fn | null>(() =>
  selectedAddr.value ? allFns.find((f) => f.a === selectedAddr.value) ?? null : null
)

const chunkCache = new Map<string, string>()
const sourceLines = ref<string[]>([])
const loading = ref(false)
const errorMsg = ref<string | null>(null)
const copied = ref(false)

async function loadSource(fn: Fn) {
  loading.value = true
  errorMsg.value = null
  try {
    let text = chunkCache.get(fn.chunk)
    if (text == null) {
      const res = await fetch(withBase('/chunks/' + fn.chunk))
      if (!res.ok) throw new Error('HTTP ' + res.status + ' on ' + fn.chunk)
      text = await res.text()
      chunkCache.set(fn.chunk, text)
    }
    const lines = text.split('\n')
    const start = Math.max(0, fn.ls - 1)
    const end = Math.min(lines.length, fn.le)
    sourceLines.value = lines.slice(start, end)
  } catch (e: any) {
    errorMsg.value = e && e.message ? String(e.message) : 'Failed to load source'
    sourceLines.value = []
  } finally {
    loading.value = false
  }
}

watch(selected, (fn) => {
  if (fn) loadSource(fn)
  else sourceLines.value = []
})

async function copySource() {
  if (!sourceLines.value.length) return
  try {
    await navigator.clipboard.writeText(sourceLines.value.join('\n'))
    copied.value = true
    setTimeout(() => (copied.value = false), 1200)
  } catch {
    copied.value = false
  }
}

function selectFn(fn: Fn) {
  selectedAddr.value = fn.a
}

function chunkUrl(fn: Fn) {
  return withBase('/chunks/' + fn.chunk)
}

onMounted(() => {
  if (visible.value.length) selectedAddr.value = visible.value[0].a
})
</script>

<template>
  <div class="fx">
    <!-- LEFT: function list -->
    <section class="fx-pane fx-list">
      <div class="fx-controls">
        <input
          v-model="query"
          class="fx-search"
          type="search"
          placeholder="filter name or address..."
          aria-label="Filter functions"
        />
        <div class="fx-select-row">
          <select v-model="topic" class="fx-select" aria-label="Topic filter">
            <option value="all">all topics</option>
            <option v-for="t in topics" :key="t" :value="t">{{ t }}</option>
          </select>
          <select v-model="sortMode" class="fx-select" aria-label="Sort mode">
            <option value="callers">sort: callers ↓</option>
            <option value="name">sort: name A→Z</option>
            <option value="addr">sort: address ↑</option>
          </select>
        </div>
        <div class="fx-count">
          <span class="fx-count-num">{{ filtered.length }} / {{ totalCount }}</span>
          <span v-if="filtered.length > MAX_VISIBLE" class="fx-count-cap">
            · capped at {{ MAX_VISIBLE }}
          </span>
        </div>
      </div>

      <div class="fx-rows">
        <button
          v-for="f in visible"
          :key="f.a"
          type="button"
          class="fx-row"
          :class="{ active: f.a === selectedAddr }"
          @click="selectFn(f)"
        >
          <span class="fx-row-addr">{{ f.a }}</span>
          <span class="fx-row-name" :title="f.n">{{ f.n }}</span>
          <span class="fx-row-badges">
            <span class="fx-badge fx-badge-cc" :title="'callers: ' + f.cc">↗{{ f.cc }}</span>
            <span class="fx-badge fx-badge-ce" :title="'callees: ' + f.ce">↘{{ f.ce }}</span>
          </span>
        </button>
        <div v-if="!visible.length" class="fx-empty">No functions match.</div>
      </div>
    </section>

    <!-- MIDDLE: source viewer -->
    <section class="fx-pane fx-viewer">
      <template v-if="selected">
        <header class="fx-vhead">
          <div class="fx-vhead-line">
            <span class="fx-vname">{{ selected.n }}</span>
            <code class="gf-addr">{{ selected.a }}</code>
            <button
              class="fx-copy"
              type="button"
              :disabled="loading || !!errorMsg || !sourceLines.length"
              @click="copySource"
            >
              {{ copied ? 'copied' : 'copy' }}
            </button>
          </div>
          <div class="fx-vhead-meta">
            <span class="fx-lines">{{ selected.cnt }} lines</span>
            <span class="fx-chunk">{{ selected.chunk }}</span>
            <span v-for="t in selected.t" :key="t" class="gf-tag">{{ t }}</span>
          </div>
        </header>

        <div class="fx-src">
          <div v-if="loading" class="fx-state">Loading <code>{{ selected.chunk }}</code>…</div>
          <div v-else-if="errorMsg" class="fx-state fx-state-err">Error: {{ errorMsg }}</div>
          <pre v-else class="fx-pre"><code><span
            v-for="(line, i) in sourceLines"
            :key="i"
            class="fx-line"
          ><span class="fx-ln">{{ selected.ls + i }}</span><span class="fx-code">{{ line.length ? line : ' ' }}</span></span></code></pre>
        </div>
      </template>
      <div v-else class="fx-state">Select a function to view its source.</div>
    </section>

    <!-- RIGHT: evidence rail -->
    <aside class="fx-pane fx-rail">
      <div v-if="selected" class="fx-rail-body">
        <div class="gf-panel-header">Function</div>
        <div class="fx-rail-name">{{ selected.n }}</div>

        <dl class="fx-dl">
          <div class="fx-di">
            <dt>address</dt>
            <dd><code class="gf-addr">{{ selected.a }}</code></dd>
          </div>
          <div class="fx-di">
            <dt>inferred</dt>
            <dd class="fx-mono-small">{{ selected.inf || '—' }}</dd>
          </div>
          <div class="fx-di">
            <dt>chunk</dt>
            <dd class="fx-mono-small">{{ selected.chunk }}</dd>
          </div>
          <div class="fx-di">
            <dt>line range</dt>
            <dd>{{ selected.ls }}–{{ selected.le }} · {{ selected.cnt }} ln</dd>
          </div>
          <div class="fx-di">
            <dt>callers</dt>
            <dd><span class="fx-stat fx-stat-cc">{{ selected.cc }}</span></dd>
          </div>
          <div class="fx-di">
            <dt>callees</dt>
            <dd><span class="fx-stat fx-stat-ce">{{ selected.ce }}</span></dd>
          </div>
          <div v-if="selected.src" class="fx-di">
            <dt>sourceRef</dt>
            <dd class="fx-mono-small fx-ref">{{ selected.src }}</dd>
          </div>
        </dl>

        <div v-if="selected.t.length" class="fx-rail-block">
          <div class="gf-panel-header">Topics</div>
          <div class="fx-tags">
            <span v-for="t in selected.t" :key="t" class="gf-tag">{{ t }}</span>
          </div>
        </div>

        <div class="fx-rail-block">
          <div class="gf-panel-header">Open</div>
          <a class="fx-link" :href="chunkUrl(selected)" target="_blank" rel="noopener">
            view full chunk file →
          </a>
          <p v-if="selected.src" class="fx-ref-note">
            research path (not served): <code>{{ selected.src }}</code>
          </p>
        </div>
      </div>
      <div v-else class="fx-state">No function selected.</div>
    </aside>
  </div>
</template>

<style scoped>
.fx {
  display: grid;
  grid-template-columns: 30% 45% 25%;
  gap: 1px;
  background: var(--gf-border);
  border: 1px solid var(--gf-border);
  border-radius: 10px;
  overflow: hidden;
  height: 720px;
  margin: 16px 0;
  font-family: var(--gf-body);
}

.fx-pane {
  background: var(--gf-panel);
  display: flex;
  flex-direction: column;
  min-width: 0;
}

/* ---------- LEFT PANE ---------- */
.fx-controls {
  display: flex;
  flex-direction: column;
  gap: 8px;
  padding: 12px;
  border-bottom: 1px solid var(--gf-border);
  background: var(--gf-bg-elev);
}
.fx-search {
  width: 100%;
  background: var(--gf-panel-2);
  border: 1px solid var(--gf-border);
  border-radius: 6px;
  color: var(--gf-text);
  font-family: var(--gf-mono);
  font-size: 0.84rem;
  padding: 7px 10px;
}
.fx-search:focus {
  outline: none;
  border-color: var(--gf-accent-2);
}
.fx-select-row {
  display: flex;
  gap: 8px;
}
.fx-select {
  flex: 1;
  background: var(--gf-panel-2);
  border: 1px solid var(--gf-border);
  border-radius: 6px;
  color: var(--gf-text-dim);
  font-family: var(--gf-mono);
  font-size: 0.74rem;
  padding: 6px 8px;
}
.fx-select:focus {
  outline: none;
  border-color: var(--gf-accent-2);
}
.fx-count {
  font-family: var(--gf-mono);
  font-size: 0.74rem;
  color: var(--gf-muted);
}
.fx-count-num {
  color: var(--gf-accent-2);
}
.fx-count-cap {
  color: var(--gf-faint);
  margin-left: 4px;
}

.fx-rows {
  flex: 1;
  overflow-y: auto;
  scrollbar-width: thin;
}
.fx-row {
  display: grid;
  grid-template-columns: auto 1fr auto;
  align-items: center;
  gap: 8px;
  width: 100%;
  padding: 6px 12px;
  border: 0;
  border-bottom: 1px solid var(--gf-border);
  background: transparent;
  color: var(--gf-text);
  text-align: left;
  cursor: pointer;
  font-family: var(--gf-body);
  font-size: 0.82rem;
}
.fx-row:hover {
  background: var(--gf-panel-2);
}
.fx-row.active {
  background: var(--gf-panel-2);
  box-shadow: inset 2px 0 0 var(--gf-accent);
}
.fx-row-addr {
  font-family: var(--gf-mono);
  font-size: 0.76rem;
  color: var(--gf-accent);
}
.fx-row-name {
  color: var(--gf-text-dim);
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
}
.fx-row.active .fx-row-name {
  color: var(--gf-text);
}
.fx-row-badges {
  display: inline-flex;
  gap: 4px;
  font-family: var(--gf-mono);
  font-size: 0.68rem;
}
.fx-badge {
  padding: 1px 5px;
  border-radius: 4px;
  border: 1px solid var(--gf-border);
  background: var(--gf-bg-elev);
}
.fx-badge-cc {
  color: var(--gf-accent-2);
}
.fx-badge-ce {
  color: var(--gf-likely);
}
.fx-empty {
  padding: 18px;
  text-align: center;
  color: var(--gf-muted);
  font-style: italic;
  font-size: 0.86rem;
}

/* ---------- MIDDLE PANE ---------- */
.fx-viewer {
  background: var(--gf-bg-elev);
}
.fx-vhead {
  padding: 12px 14px;
  border-bottom: 1px solid var(--gf-border);
  background: var(--gf-panel);
}
.fx-vhead-line {
  display: flex;
  align-items: center;
  gap: 10px;
  margin-bottom: 6px;
}
.fx-vname {
  font-family: var(--gf-display);
  font-weight: 600;
  font-size: 0.98rem;
  color: var(--gf-text);
  word-break: break-all;
}
.fx-copy {
  margin-left: auto;
  background: var(--gf-panel-2);
  border: 1px solid var(--gf-border);
  border-radius: 5px;
  color: var(--gf-text-dim);
  font-family: var(--gf-mono);
  font-size: 0.7rem;
  padding: 4px 10px;
  cursor: pointer;
  flex: 0 0 auto;
}
.fx-copy:hover:not(:disabled) {
  border-color: var(--gf-accent-2);
  color: var(--gf-accent-2);
}
.fx-copy:disabled {
  opacity: 0.5;
  cursor: not-allowed;
}
.fx-vhead-meta {
  display: flex;
  align-items: center;
  flex-wrap: wrap;
  gap: 6px;
  font-size: 0.74rem;
}
.fx-lines {
  font-family: var(--gf-mono);
  color: var(--gf-muted);
}
.fx-chunk {
  font-family: var(--gf-mono);
  font-size: 0.72rem;
  color: var(--gf-faint);
  padding: 1px 6px;
  background: var(--gf-panel-2);
  border-radius: 4px;
  border: 1px solid var(--gf-border);
}

.fx-src {
  flex: 1;
  overflow: auto;
  scrollbar-width: thin;
}
.fx-pre {
  margin: 0;
  padding: 10px 0;
  font-family: var(--gf-mono);
  font-size: 0.8rem;
  line-height: 1.5;
  color: var(--gf-text);
}
.fx-pre code {
  display: block;
  white-space: normal;
}
.fx-line {
  display: flex;
  align-items: flex-start;
}
.fx-ln {
  flex: 0 0 auto;
  width: 4em;
  padding-right: 12px;
  text-align: right;
  color: var(--gf-faint);
  user-select: none;
}
.fx-code {
  flex: 1 1 auto;
  white-space: pre;
  overflow-x: visible;
  word-break: normal;
}

.fx-state {
  padding: 24px;
  font-family: var(--gf-mono);
  font-size: 0.84rem;
  color: var(--gf-muted);
}
.fx-state code {
  font-family: var(--gf-mono);
  color: var(--gf-accent-2);
}
.fx-state-err {
  color: var(--gf-invalid);
}

/* ---------- RIGHT PANE ---------- */
.fx-rail {
  background: var(--gf-panel);
}
.fx-rail-body {
  padding: 14px;
  overflow-y: auto;
  flex: 1;
  scrollbar-width: thin;
}
.fx-rail-name {
  font-family: var(--gf-display);
  font-weight: 600;
  font-size: 0.96rem;
  color: var(--gf-text);
  word-break: break-all;
  margin-bottom: 14px;
  line-height: 1.3;
}
.fx-dl {
  margin: 0 0 14px;
  display: grid;
  gap: 7px;
}
.fx-di {
  display: grid;
  grid-template-columns: 80px 1fr;
  gap: 8px;
  align-items: baseline;
}
.fx-di dt {
  font-family: var(--gf-display);
  font-size: 0.66rem;
  text-transform: uppercase;
  letter-spacing: 0.06em;
  color: var(--gf-faint);
}
.fx-di dd {
  margin: 0;
  font-size: 0.82rem;
  color: var(--gf-text-dim);
  word-break: break-all;
}
.fx-mono-small {
  font-family: var(--gf-mono);
  font-size: 0.76rem;
  color: var(--gf-text-dim);
}
.fx-stat {
  display: inline-block;
  font-family: var(--gf-mono);
  font-size: 0.86rem;
  font-weight: 600;
  padding: 1px 8px;
  border-radius: 4px;
  border: 1px solid var(--gf-border);
  background: var(--gf-panel-2);
}
.fx-stat-cc {
  color: var(--gf-accent-2);
}
.fx-stat-ce {
  color: var(--gf-likely);
}
.fx-ref {
  color: var(--gf-faint);
}

.fx-rail-block {
  margin-top: 14px;
  padding-top: 12px;
  border-top: 1px solid var(--gf-border);
}
.fx-tags {
  display: flex;
  flex-wrap: wrap;
  gap: 6px;
}
.fx-link {
  display: inline-block;
  color: var(--gf-accent-2);
  text-decoration: none;
  font-family: var(--gf-mono);
  font-size: 0.8rem;
  border-bottom: 1px dotted var(--gf-accent-2);
  padding-bottom: 1px;
}
.fx-link:hover {
  color: var(--gf-accent);
  border-bottom-color: var(--gf-accent);
}
.fx-ref-note {
  margin: 8px 0 0;
  font-size: 0.74rem;
  color: var(--gf-muted);
}
.fx-ref-note code {
  font-family: var(--gf-mono);
  font-size: 0.72rem;
  color: var(--gf-faint);
  word-break: break-all;
}

/* ---------- responsive ---------- */
@media (max-width: 1100px) {
  .fx {
    grid-template-columns: 1fr;
    height: auto;
  }
  .fx-list,
  .fx-viewer,
  .fx-rail {
    min-height: 0;
  }
  .fx-rows {
    max-height: 360px;
  }
  .fx-src {
    max-height: 540px;
  }
  .fx-rail-body {
    max-height: none;
  }
}
</style>
