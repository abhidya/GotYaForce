<script setup lang="ts">
import { ref, computed } from 'vue'
import StatusBadge from './StatusBadge.vue'
import ClaimTrail from './ClaimTrail.vue'

const props = defineProps<{
  claim: string
  status?: 'verified' | 'observed' | 'likely' | 'unknown' | 'invalid'
  steps: Array<{
    label: string
    value?: string
    status?: 'verified' | 'observed' | 'likely' | 'unknown' | 'invalid'
    note?: string
  }>
  repro?: string
  source?: string
}>()

const open = ref(false)
const copied = ref(false)

const preview = computed(() => {
  const s = props.steps?.[0]
  if (!s) return ''
  return s.value ? `${s.label} → ${s.value}` : s.label
})

async function copyRepro() {
  if (!props.repro) return
  try {
    await navigator.clipboard.writeText(props.repro)
    copied.value = true
    setTimeout(() => {
      copied.value = false
    }, 1500)
  } catch {
    /* clipboard unavailable */
  }
}
</script>

<template>
  <div class="gf-et" :class="{ open }">
    <button
      type="button"
      class="gf-et-head"
      :aria-expanded="open"
      @click="open = !open"
    >
      <span class="gf-et-chevron" :class="{ open }" aria-hidden="true">▸</span>
      <div class="gf-et-head-main">
        <div class="gf-et-claim">{{ claim }}</div>
        <div v-if="!open && preview" class="gf-et-preview">
          <span class="gf-et-preview-arrow">→</span> {{ preview }}
        </div>
      </div>
      <StatusBadge v-if="status" :status="status" />
    </button>

    <div class="gf-et-body">
      <div class="gf-et-body-inner">
        <ClaimTrail :steps="steps" />

        <div v-if="repro" class="gf-et-repro">
          <span class="gf-et-repro-label">Reproduce</span>
          <code class="gf-et-repro-cmd">{{ repro }}</code>
          <button
            type="button"
            class="gf-et-copy"
            :class="{ copied }"
            @click="copyRepro"
          >{{ copied ? 'Copied!' : 'Copy' }}</button>
        </div>

        <div v-if="source" class="gf-et-source">
          Source: <code class="gf-addr">{{ source }}</code>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped>
.gf-et {
  background: var(--gf-panel);
  border: 1px solid var(--gf-border);
  border-left: 3px solid var(--gf-accent-2);
  border-radius: 8px;
  margin: 14px 0;
  overflow: hidden;
}
.gf-et-head {
  display: flex;
  align-items: center;
  gap: 12px;
  width: 100%;
  padding: 14px 16px;
  background: transparent;
  border: none;
  text-align: left;
  cursor: pointer;
  font: inherit;
  color: inherit;
}
.gf-et-head:hover {
  background: color-mix(in srgb, var(--gf-accent-2) 6%, transparent);
}
.gf-et-chevron {
  flex-shrink: 0;
  display: inline-flex;
  align-items: center;
  justify-content: center;
  width: 18px;
  height: 18px;
  color: var(--gf-accent-2);
  font-size: 0.8rem;
  transition: transform 0.2s ease;
}
.gf-et-chevron.open {
  transform: rotate(90deg);
}
.gf-et-head-main {
  flex: 1;
  min-width: 0;
  display: flex;
  flex-direction: column;
  gap: 3px;
}
.gf-et-claim {
  font-family: var(--gf-display);
  font-weight: 500;
  font-size: 0.96rem;
  color: var(--gf-text);
  line-height: 1.4;
}
.gf-et-preview {
  font-family: var(--gf-mono);
  font-size: 0.74rem;
  color: var(--gf-text-dim);
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}
.gf-et-preview-arrow {
  color: var(--gf-muted);
}

.gf-et-body {
  display: grid;
  grid-template-rows: 0fr;
  transition: grid-template-rows 0.2s ease;
}
.gf-et.open .gf-et-body {
  grid-template-rows: 1fr;
}
.gf-et-body-inner {
  overflow: hidden;
  min-height: 0;
  padding: 0 16px;
}
.gf-et.open .gf-et-body-inner {
  padding-bottom: 14px;
}

.gf-et-repro {
  display: flex;
  align-items: center;
  gap: 10px;
  margin-top: 12px;
  padding: 10px 12px;
  background: var(--gf-panel-2);
  border: 1px solid var(--gf-border);
  border-radius: 6px;
}
.gf-et-repro-label {
  font-family: var(--gf-display);
  font-size: 0.66rem;
  text-transform: uppercase;
  letter-spacing: 0.08em;
  color: var(--gf-muted);
  flex-shrink: 0;
}
.gf-et-repro-cmd {
  flex: 1;
  min-width: 0;
  font-family: var(--gf-mono);
  font-size: 0.78rem;
  color: var(--gf-text);
  white-space: nowrap;
  overflow: hidden;
  text-overflow: ellipsis;
}
.gf-et-copy {
  flex-shrink: 0;
  appearance: none;
  font-family: var(--gf-mono);
  font-size: 0.72rem;
  padding: 4px 10px;
  border-radius: 5px;
  border: 1px solid var(--gf-border-strong);
  background: var(--gf-panel);
  color: var(--gf-text);
  cursor: pointer;
  transition: all 0.15s;
}
.gf-et-copy:hover {
  border-color: var(--gf-accent-2);
  color: var(--gf-accent-2);
}
.gf-et-copy.copied {
  border-color: var(--gf-verified);
  color: var(--gf-verified);
}

.gf-et-source {
  margin-top: 10px;
  font-family: var(--gf-display);
  font-size: 0.78rem;
  color: var(--gf-muted);
  display: flex;
  align-items: center;
  gap: 8px;
  flex-wrap: wrap;
}
</style>
