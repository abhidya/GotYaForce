<script setup lang="ts">
defineProps<{
  status: 'verified' | 'observed' | 'likely' | 'unknown' | 'invalid'
  label?: string
}>()

const map: Record<string, { color: string; bg: string; text: string }> = {
  verified: { color: 'var(--gf-verified)', bg: 'rgba(63,185,80,0.12)', text: 'Verified' },
  observed: { color: 'var(--gf-observed)', bg: 'rgba(88,166,255,0.12)', text: 'In RAM' },
  likely: { color: 'var(--gf-likely)', bg: 'rgba(210,153,34,0.12)', text: 'Likely' },
  unknown: { color: 'var(--gf-unknown)', bg: 'rgba(110,118,129,0.14)', text: 'Unknown' },
  invalid: { color: 'var(--gf-invalid)', bg: 'rgba(248,81,73,0.12)', text: 'Invalid' }
}
</script>

<template>
  <span
    class="gf-status"
    :style="{
      '--c': map[status]?.color ?? map.unknown.color,
      background: map[status]?.bg ?? map.unknown.bg,
      color: map[status]?.color ?? map.unknown.color
    }"
  >
    <span class="gf-status-dot" />
    <slot>{{ label ?? map[status]?.text ?? 'Unknown' }}</slot>
  </span>
</template>

<style scoped>
.gf-status {
  display: inline-flex;
  align-items: center;
  gap: 6px;
  font-family: var(--gf-mono);
  font-size: 0.72rem;
  font-weight: 500;
  padding: 2px 9px;
  border-radius: 999px;
  border: 1px solid color-mix(in srgb, var(--c) 40%, transparent);
  white-space: nowrap;
  line-height: 1.4;
}
.gf-status-dot {
  width: 6px;
  height: 6px;
  border-radius: 50%;
  background: var(--c);
  box-shadow: 0 0 6px var(--c);
}
</style>
