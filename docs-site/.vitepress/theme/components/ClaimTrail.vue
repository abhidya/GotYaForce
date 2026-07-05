<script setup lang="ts">
defineProps<{
  steps: Array<{ label: string; value?: string; status?: 'verified' | 'observed' | 'likely' | 'unknown' | 'invalid' }>
}>()
</script>

<template>
  <ol class="gf-trail">
    <li v-for="(s, i) in steps" :key="i" class="gf-trail-step" :class="s.status">
      <span class="gf-trail-dot" />
      <div class="gf-trail-content">
        <span class="gf-trail-label">{{ s.label }}</span>
        <code v-if="s.value" class="gf-addr">{{ s.value }}</code>
      </div>
    </li>
  </ol>
</template>

<style scoped>
.gf-trail {
  list-style: none;
  padding: 0;
  margin: 14px 0;
  position: relative;
}
.gf-trail::before {
  content: '';
  position: absolute;
  left: 8px;
  top: 8px;
  bottom: 8px;
  width: 1px;
  background: var(--gf-border-strong);
}
.gf-trail-step {
  position: relative;
  padding: 4px 0 14px 28px;
}
.gf-trail-step:last-child {
  padding-bottom: 0;
}
.gf-trail-dot {
  position: absolute;
  left: 4px;
  top: 8px;
  width: 9px;
  height: 9px;
  border-radius: 50%;
  background: var(--gf-muted);
  border: 2px solid var(--gf-bg);
  box-shadow: 0 0 0 1px var(--gf-border-strong);
}
.gf-trail-step.verified .gf-trail-dot { background: var(--gf-verified); box-shadow: 0 0 6px var(--gf-verified); }
.gf-trail-step.observed .gf-trail-dot { background: var(--gf-accent-2); box-shadow: 0 0 6px var(--gf-accent-2); }
.gf-trail-step.likely .gf-trail-dot { background: var(--gf-likely); }
.gf-trail-step.invalid .gf-trail-dot { background: var(--gf-invalid); }
.gf-trail-content {
  display: flex;
  flex-direction: column;
  gap: 2px;
}
.gf-trail-label {
  font-family: var(--gf-display);
  font-size: 0.86rem;
  color: var(--gf-text);
}
</style>
