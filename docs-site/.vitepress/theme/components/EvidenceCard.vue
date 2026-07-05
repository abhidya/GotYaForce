<script setup lang="ts">
defineProps<{
  claim: string
  status?: 'verified' | 'observed' | 'likely' | 'unknown' | 'invalid'
  addr?: string
  fn?: string
  file?: string
  repro?: string
  note?: string
}>()
</script>

<template>
  <div class="gf-evidence">
    <div class="gf-evidence-head">
      <div class="gf-evidence-claim">{{ claim }}</div>
      <slot name="status" />
    </div>
    <div class="gf-evidence-grid">
      <div v-if="addr" class="gf-evidence-field">
        <span class="gf-evidence-label">RAM</span>
        <code class="gf-addr">{{ addr }}</code>
      </div>
      <div v-if="fn" class="gf-evidence-field">
        <span class="gf-evidence-label">Function</span>
        <code class="gf-addr">{{ fn }}</code>
      </div>
      <div v-if="file" class="gf-evidence-field">
        <span class="gf-evidence-label">Source</span>
        <code class="gf-addr">{{ file }}</code>
      </div>
      <div v-if="repro" class="gf-evidence-field">
        <span class="gf-evidence-label">Repro</span>
        <code class="gf-addr">{{ repro }}</code>
      </div>
    </div>
    <p v-if="note" class="gf-evidence-note">{{ note }}</p>
    <slot />
  </div>
</template>

<style scoped>
.gf-evidence {
  background: var(--gf-panel);
  border: 1px solid var(--gf-border);
  border-left: 3px solid var(--gf-accent-2);
  border-radius: 8px;
  padding: 14px 16px;
  margin: 14px 0;
}
.gf-evidence-head {
  display: flex;
  align-items: flex-start;
  justify-content: space-between;
  gap: 10px;
  margin-bottom: 10px;
}
.gf-evidence-claim {
  font-family: var(--gf-display);
  font-weight: 500;
  font-size: 0.96rem;
  color: var(--gf-text);
}
.gf-evidence-grid {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(180px, 1fr));
  gap: 8px 14px;
}
.gf-evidence-field {
  display: flex;
  flex-direction: column;
  gap: 2px;
}
.gf-evidence-label {
  font-family: var(--gf-display);
  font-size: 0.66rem;
  text-transform: uppercase;
  letter-spacing: 0.08em;
  color: var(--gf-muted);
}
.gf-evidence-note {
  margin: 8px 0 0;
  font-size: 0.86rem;
  color: var(--gf-text-dim);
}
</style>
