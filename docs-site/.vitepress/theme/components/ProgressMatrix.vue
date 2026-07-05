<script setup lang="ts">
defineProps<{
  systems: Array<{
    name: string
    href?: string
    pct: number
    status: 'verified' | 'observed' | 'likely' | 'unknown' | 'invalid'
    note?: string
  }>
}>()

const statusColor: Record<string, string> = {
  verified: 'var(--gf-verified)',
  observed: 'var(--gf-accent-2)',
  likely: 'var(--gf-likely)',
  unknown: 'var(--gf-unknown)',
  invalid: 'var(--gf-invalid)'
}
</script>

<template>
  <div class="gf-matrix">
    <div v-for="s in systems" :key="s.name" class="gf-matrix-row">
      <a v-if="s.href" :href="s.href" class="gf-matrix-name">{{ s.name }}</a>
      <span v-else class="gf-matrix-name">{{ s.name }}</span>
      <div class="gf-matrix-bar">
        <div
          class="gf-matrix-fill"
          :style="{ width: `${s.pct}%`, background: statusColor[s.status] }"
        />
      </div>
      <span class="gf-matrix-pct">{{ s.pct }}%</span>
      <span v-if="s.note" class="gf-matrix-note">{{ s.note }}</span>
    </div>
  </div>
</template>

<style scoped>
.gf-matrix {
  display: flex;
  flex-direction: column;
  gap: 8px;
}
.gf-matrix-row {
  display: grid;
  grid-template-columns: 160px 1fr 44px;
  align-items: center;
  gap: 12px;
  padding: 6px 0;
  border-bottom: 1px solid var(--gf-border);
}
.gf-matrix-row:last-child {
  border-bottom: none;
}
.gf-matrix-name {
  font-family: var(--gf-display);
  font-weight: 500;
  font-size: 0.92rem;
  color: var(--gf-text);
  text-decoration: none;
}
a.gf-matrix-name:hover {
  color: var(--gf-accent-2);
}
.gf-matrix-bar {
  height: 8px;
  background: var(--gf-panel-2);
  border-radius: 4px;
  overflow: hidden;
  border: 1px solid var(--gf-border);
}
.gf-matrix-fill {
  height: 100%;
  border-radius: 3px;
  transition: width 0.4s ease;
}
.gf-matrix-pct {
  font-family: var(--gf-mono);
  font-size: 0.84rem;
  color: var(--gf-muted);
  text-align: right;
}
.gf-matrix-note {
  grid-column: 2 / -1;
  font-size: 0.78rem;
  color: var(--gf-muted);
  font-family: var(--gf-mono);
}
@media (max-width: 620px) {
  .gf-matrix-row {
    grid-template-columns: 1fr 44px;
  }
  .gf-matrix-name {
    grid-column: 1 / -1;
  }
}
</style>
