<script setup lang="ts">
import { ref, provide, readonly } from 'vue'

type View = 'player' | 'research'
const view = ref<View>('research')
const toggle = () => {
  view.value = view.value === 'research' ? 'player' : 'research'
}
provide('gf-view', readonly(view))
provide('gf-toggle', toggle)
</script>

<template>
  <div class="gf-toggle">
    <span class="gf-toggle-label">View</span>
    <div class="gf-toggle-track">
      <button
        :class="{ active: view === 'player' }"
        @click="view = 'player'"
        type="button"
      >Player</button>
      <button
        :class="{ active: view === 'research' }"
        @click="view = 'research'"
        type="button"
      >Research</button>
      <span class="gf-toggle-thumb" :class="{ right: view === 'research' }" />
    </div>
  </div>
</template>

<style scoped>
.gf-toggle {
  display: inline-flex;
  align-items: center;
  gap: 10px;
  margin: 0 0 14px;
}
.gf-toggle-label {
  font-family: var(--gf-display);
  font-size: 0.72rem;
  text-transform: uppercase;
  letter-spacing: 0.08em;
  color: var(--gf-muted);
}
.gf-toggle-track {
  position: relative;
  display: inline-flex;
  background: var(--gf-panel-2);
  border: 1px solid var(--gf-border);
  border-radius: 999px;
  padding: 3px;
}
button {
  position: relative;
  z-index: 2;
  background: transparent;
  border: none;
  color: var(--gf-muted);
  font-family: var(--gf-display);
  font-size: 0.78rem;
  font-weight: 500;
  padding: 4px 14px;
  border-radius: 999px;
  cursor: pointer;
  transition: color 0.2s;
}
button.active {
  color: var(--gf-text);
}
.gf-toggle-thumb {
  position: absolute;
  z-index: 1;
  top: 3px;
  left: 3px;
  width: calc(50% - 3px);
  height: calc(100% - 6px);
  background: var(--gf-panel);
  border: 1px solid var(--gf-border-strong);
  border-radius: 999px;
  transition: transform 0.25s ease;
}
.gf-toggle-thumb.right {
  transform: translateX(100%);
}
</style>
