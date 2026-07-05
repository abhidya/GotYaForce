<script setup lang="ts">
import { computed, ref } from 'vue'

const props = defineProps<{
  rows: Array<Record<string, any>>
  columns: Array<{ key: string; label?: string; mono?: boolean; status?: boolean; link?: boolean }>
  searchable?: boolean
  searchPlaceholder?: string
  emptyText?: string
}>()

const query = ref('')
const filtered = computed(() => {
  if (!query.value.trim()) return props.rows
  const q = query.value.toLowerCase()
  return props.rows.filter((r) =>
    props.columns.some((c) => String(r[c.key] ?? '').toLowerCase().includes(q))
  )
})
</script>

<template>
  <div class="gf-atlas">
    <div v-if="searchable" class="gf-atlas-search">
      <input
        v-model="query"
        type="search"
        :placeholder="searchPlaceholder ?? 'Filter...'"
        aria-label="Filter rows"
      />
      <span class="gf-atlas-count">{{ filtered.length }} / {{ rows.length }}</span>
    </div>
    <div class="gf-atlas-scroll">
      <table>
        <thead>
          <tr>
            <th v-for="c in columns" :key="c.key">{{ c.label ?? c.key }}</th>
          </tr>
        </thead>
        <tbody>
          <tr v-for="(row, i) in filtered" :key="i">
            <td v-for="c in columns" :key="c.key" :class="{ mono: c.mono }">
              <StatusBadge
                v-if="c.status"
                :status="String(row[c.key]) as any"
              />
              <a
                v-else-if="c.link && row.href"
                :href="row.href"
              >{{ row[c.key] }}</a>
              <span v-else>{{ row[c.key] }}</span>
            </td>
          </tr>
          <tr v-if="filtered.length === 0">
            <td :colspan="columns.length" class="gf-atlas-empty">
              {{ emptyText ?? 'No rows match.' }}
            </td>
          </tr>
        </tbody>
      </table>
    </div>
  </div>
</template>

<style scoped>
.gf-atlas {
  margin: 14px 0;
}
.gf-atlas-search {
  display: flex;
  align-items: center;
  gap: 12px;
  margin-bottom: 10px;
}
.gf-atlas-search input {
  flex: 1;
  background: var(--gf-panel);
  border: 1px solid var(--gf-border);
  border-radius: 8px;
  color: var(--gf-text);
  font-family: var(--gf-mono);
  padding: 8px 12px;
  font-size: 0.9rem;
}
.gf-atlas-search input:focus {
  outline: none;
  border-color: var(--gf-accent-2);
}
.gf-atlas-count {
  font-family: var(--gf-mono);
  font-size: 0.74rem;
  color: var(--gf-muted);
  white-space: nowrap;
}
.gf-atlas-scroll {
  overflow-x: auto;
  border: 1px solid var(--gf-border);
  border-radius: 8px;
}
table {
  width: 100%;
  border-collapse: collapse;
  font-size: 0.88rem;
}
thead {
  background: var(--gf-panel);
}
th {
  font-family: var(--gf-display);
  font-weight: 600;
  text-align: left;
  padding: 8px 12px;
  font-size: 0.74rem;
  text-transform: uppercase;
  letter-spacing: 0.06em;
  color: var(--gf-muted);
  border-bottom: 1px solid var(--gf-border);
  white-space: nowrap;
}
td {
  padding: 8px 12px;
  border-bottom: 1px solid var(--gf-border);
  color: var(--gf-text);
  vertical-align: middle;
}
tr:last-child td {
  border-bottom: none;
}
tr:nth-child(even) td {
  background: var(--gf-bg-elev);
}
td.mono,
.mono {
  font-family: var(--gf-mono);
  font-size: 0.82rem;
}
td a {
  color: var(--gf-accent-2);
  text-decoration: none;
}
td a:hover {
  color: var(--gf-accent);
}
.gf-atlas-empty {
  text-align: center;
  color: var(--gf-muted);
  padding: 20px !important;
  font-style: italic;
}
</style>
