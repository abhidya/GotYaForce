<script setup lang="ts">
defineProps<{
  borg: {
    id: string
    name: string
    tribe: string
    type: string
    rarity: string
    cost: number | string
    hp1: string | number
    hp10: string | number
    defense: string | number
    shot: string | number
    attack: string | number
    speed: string | number
    alt: boolean
    moves?: any[]
  }
}>()

defineEmits<{ (e: 'click', id: string): void }>()

const rarityColor: Record<string, string> = {
  S: 'var(--gf-likely)',
  A: 'var(--gf-accent-2)',
  B: 'var(--gf-muted)',
  C: 'var(--gf-verified)',
  D: 'var(--gf-invalid)'
}

const variants = [
  { key: 'normal', label: 'Normal', color: '#c9ced8' },
  { key: 'alt', label: 'Alt', color: '#ff6fb1' },
  { key: 'gold', label: 'Gold', color: '#d29922' },
  { key: 'silver', label: 'Silver', color: '#a7adb8' },
  { key: 'crystal', label: 'Crystal', color: '#58a6ff' },
  { key: 'black', label: 'Black', color: '#6b7280' }
]
</script>

<template>
  <article class="borg-card" @click="$emit('click', borg.id)">
    <header class="bc-head">
      <h3 class="bc-name">{{ borg.name }}</h3>
      <span
        class="bc-rarity"
        :style="{ '--rc': rarityColor[borg.rarity] ?? 'var(--gf-muted)' }"
        :title="`Rarity ${borg.rarity}`"
      >{{ borg.rarity }}</span>
    </header>

    <div class="bc-sub">
      <span>{{ borg.tribe }}</span>
      <span class="bc-dot">·</span>
      <span>{{ borg.type }}</span>
    </div>

    <dl class="bc-stats">
      <div class="bc-stat"><dt>Cost</dt><dd>{{ borg.cost }}</dd></div>
      <div class="bc-stat"><dt>HP</dt><dd>{{ borg.hp1 }}→{{ borg.hp10 }}</dd></div>
      <div class="bc-stat"><dt>Spd</dt><dd>{{ borg.speed }}</dd></div>
      <div class="bc-stat"><dt>Def</dt><dd>{{ borg.defense }}</dd></div>
      <div class="bc-stat"><dt>Shot</dt><dd>{{ borg.shot }}</dd></div>
      <div class="bc-stat"><dt>Atk</dt><dd>{{ borg.attack }}</dd></div>
    </dl>

    <div class="bc-variants" aria-label="Color variants">
      <span
        v-for="v in variants"
        :key="v.key"
        class="bc-dot-swatch"
        :class="{ dim: v.key === 'alt' && !borg.alt }"
        :style="{ background: v.color }"
        :title="`${v.label}${v.key === 'alt' && !borg.alt ? ' (none)' : ''}`"
      />
    </div>

    <footer v-if="borg.moves && borg.moves.length > 0" class="bc-foot">
      <span class="bc-moves">{{ borg.moves.length }} move{{ borg.moves.length === 1 ? '' : 's' }}</span>
    </footer>
  </article>
</template>

<style scoped>
.borg-card {
  background: var(--gf-panel);
  border: 1px solid var(--gf-border);
  border-radius: 10px;
  padding: 12px 14px 10px;
  cursor: pointer;
  transition: transform 0.14s ease, border-color 0.14s ease, box-shadow 0.14s ease;
  display: flex;
  flex-direction: column;
  gap: 8px;
}
.borg-card:hover {
  transform: translateY(-2px);
  border-color: var(--gf-border-strong);
  box-shadow: 0 6px 18px rgba(0, 0, 0, 0.35);
}

.bc-head {
  display: flex;
  align-items: flex-start;
  justify-content: space-between;
  gap: 8px;
}
.bc-name {
  font-family: var(--gf-display);
  font-weight: 700;
  font-size: 0.96rem;
  line-height: 1.2;
  margin: 0;
  color: var(--gf-text);
}
.bc-rarity {
  flex: none;
  font-family: var(--gf-mono);
  font-weight: 700;
  font-size: 0.74rem;
  width: 22px;
  height: 22px;
  display: inline-flex;
  align-items: center;
  justify-content: center;
  border-radius: 6px;
  color: var(--rc);
  background: color-mix(in srgb, var(--rc) 16%, transparent);
  border: 1px solid color-mix(in srgb, var(--rc) 55%, transparent);
}

.bc-sub {
  font-size: 0.74rem;
  color: var(--gf-muted);
  display: flex;
  flex-wrap: wrap;
  gap: 5px;
}
.bc-dot { color: var(--gf-faint); }

.bc-stats {
  display: grid;
  grid-template-columns: 1fr 1fr;
  gap: 5px 10px;
  margin: 0;
}
.bc-stat {
  display: flex;
  justify-content: space-between;
  align-items: baseline;
  gap: 6px;
  padding: 3px 6px;
  background: var(--gf-panel-2);
  border: 1px solid var(--gf-border);
  border-radius: 5px;
}
.bc-stat dt {
  font-size: 0.66rem;
  text-transform: uppercase;
  letter-spacing: 0.05em;
  color: var(--gf-muted);
}
.bc-stat dd {
  margin: 0;
  font-family: var(--gf-mono);
  font-size: 0.8rem;
  color: var(--gf-text);
}

.bc-variants {
  display: flex;
  gap: 5px;
  align-items: center;
}
.bc-dot-swatch {
  width: 10px;
  height: 10px;
  border-radius: 50%;
  border: 1px solid rgba(0, 0, 0, 0.35);
  box-shadow: 0 0 4px color-mix(in srgb, currentColor 25%, transparent);
}
.bc-dot-swatch.dim {
  opacity: 0.22;
  filter: grayscale(0.6);
}

.bc-foot {
  display: flex;
  justify-content: flex-end;
}
.bc-moves {
  font-family: var(--gf-mono);
  font-size: 0.7rem;
  padding: 2px 8px;
  border-radius: 999px;
  background: color-mix(in srgb, var(--gf-accent) 14%, transparent);
  color: var(--gf-accent);
  border: 1px solid color-mix(in srgb, var(--gf-accent) 40%, transparent);
}
</style>
