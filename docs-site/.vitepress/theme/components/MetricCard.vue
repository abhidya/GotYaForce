<script setup lang="ts">
defineProps<{
  label: string
  value: string | number
  unit?: string
  hint?: string
  trend?: string
  accent?: 'pink' | 'blue' | 'green' | 'amber'
}>()

const accents: Record<string, string> = {
  pink: 'var(--gf-accent)',
  blue: 'var(--gf-accent-2)',
  green: 'var(--gf-verified)',
  amber: 'var(--gf-likely)'
}
</script>

<template>
  <div class="gf-metric">
    <div class="gf-metric-label">{{ label }}</div>
    <div class="gf-metric-row">
      <div
        class="gf-metric-value"
        :style="{ color: accent ? accents[accent] : 'var(--gf-text)' }"
      >
        {{ value }}<span v-if="unit" class="gf-metric-unit">{{ unit }}</span>
      </div>
      <div v-if="trend" class="gf-metric-trend">{{ trend }}</div>
    </div>
    <div v-if="hint" class="gf-metric-hint">{{ hint }}</div>
  </div>
</template>

<style scoped>
.gf-metric {
  background: var(--gf-panel);
  border: 1px solid var(--gf-border);
  border-radius: 10px;
  padding: 14px 16px;
  display: flex;
  flex-direction: column;
  gap: 4px;
  min-height: 92px;
}
.gf-metric-label {
  font-family: var(--gf-display);
  font-size: 0.72rem;
  text-transform: uppercase;
  letter-spacing: 0.08em;
  color: var(--gf-muted);
}
.gf-metric-row {
  display: flex;
  align-items: baseline;
  justify-content: space-between;
  gap: 8px;
}
.gf-metric-value {
  font-family: var(--gf-display);
  font-weight: 700;
  font-size: 1.9rem;
  line-height: 1.1;
  letter-spacing: -0.02em;
}
.gf-metric-unit {
  font-size: 0.9rem;
  color: var(--gf-muted);
  margin-left: 4px;
  font-weight: 500;
}
.gf-metric-trend {
  font-family: var(--gf-mono);
  font-size: 0.7rem;
  color: var(--gf-verified);
  background: rgba(63, 185, 80, 0.1);
  padding: 2px 6px;
  border-radius: 4px;
}
.gf-metric-hint {
  font-size: 0.82rem;
  color: var(--gf-text-dim);
  margin-top: 2px;
}
</style>
