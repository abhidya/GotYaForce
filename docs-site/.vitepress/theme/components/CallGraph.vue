<script setup lang="ts">
import { ref, reactive, onMounted, onBeforeUnmount, shallowRef } from 'vue'
import graphData from '../../data/functions-graph.json'

type RawNode = { id: string; name: string; topic: string; degree: number }
type RawEdge = { from: string; to: string }

type SimNode = RawNode & {
  x: number
  y: number
  vx: number
  vy: number
  r: number
  primary: string
}

const TOPICS = [
  'movement-physics',
  'knockback-targeting',
  'force-setup',
  'assets-animation',
  'challenge-menu-flow',
  'battle-initialization',
  'damage',
  'camera',
  'front-end-menu',
  'global-menu-mode',
  'audio',
  'stage-load-collision',
  'sdk-libc',
  'sdk-os',
  'sdk-gx',
  'sdk-hsd',
  'game-unsorted',
  'unsorted'
]

const topicHue: Record<string, number> = {}
TOPICS.forEach((t, i) => {
  topicHue[t] = Math.round((i * 360) / TOPICS.length)
})

function resolvePrimary(topic: string): string {
  const seg = topic.split('/')[0].trim()
  return TOPICS.includes(seg) ? seg : 'unsorted'
}

function topicColor(primary: string): string {
  const h = topicHue[primary] ?? 0
  return `hsl(${h} 70% 60%)`
}

const visibleTopics = reactive<Record<string, boolean>>({})
TOPICS.forEach((t) => {
  visibleTopics[t] = true
})

const canvasEl = ref<HTMLCanvasElement | null>(null)
const wrapEl = ref<HTMLDivElement | null>(null)
const tooltipEl = ref<HTMLDivElement | null>(null)

const nodeCount = graphData.nodes.length
const edgeCount = graphData.edges.length

const transform = reactive({ scale: 1, x: 0, y: 0 })
const hoverId = ref<string | null>(null)
const hoverInfo = reactive({
  visible: false,
  x: 0,
  y: 0,
  name: '',
  id: '',
  topic: '',
  degree: 0
})

const statusText = ref('initializing')

let ctx: CanvasRenderingContext2D | null = null
let rafId = 0
let tick = 0
let width = 0
let height = 600
const MAX_TICKS = 300
const MAX_VELOCITY = 20
const EDGE_DRAW_CAP = 800

const nodes = shallowRef<SimNode[]>([])
const edges = graphData.edges as RawEdge[]
const idIndex = new Map<string, SimNode>()

function buildNodes(): SimNode[] {
  const arr: SimNode[] = []
  const n = graphData.nodes.length as number
  ;(graphData.nodes as RawNode[]).forEach((raw, i) => {
    const primary = resolvePrimary(raw.topic)
    const angle = (i / n) * Math.PI * 2
    const radius = 200
    arr.push({
      ...raw,
      x: Math.cos(angle) * radius + (Math.random() - 0.5) * 8,
      y: Math.sin(angle) * radius + (Math.random() - 0.5) * 8,
      vx: 0,
      vy: 0,
      r: 3 + Math.min(9, raw.degree / 5),
      primary
    })
  })
  return arr
}

function indexNodes(arr: SimNode[]) {
  idIndex.clear()
  for (const node of arr) idIndex.set(node.id, node)
}

function resetLayout() {
  const arr = buildNodes()
  nodes.value = arr
  indexNodes(arr)
  tick = 0
  transform.scale = 1
  transform.x = 0
  transform.y = 0
  statusText.value = 'running'
  if (!rafId) startSim()
}

const K_REPULSION = 1400
const K_SPRING = 0.02
const REST_LEN = 55
const K_CENTER = 0.0015
const ENERGY_THRESHOLD = 0.5

function step(): boolean {
  const arr = nodes.value
  const n = arr.length
  let energy = 0

  for (let i = 0; i < n; i++) {
    const a = arr[i]
    let fx = 0
    let fy = 0
    for (let j = 0; j < n; j++) {
      if (i === j) continue
      const b = arr[j]
      const dx = a.x - b.x
      const dy = a.y - b.y
      let dist2 = dx * dx + dy * dy
      if (dist2 < 0.01) {
        dist2 = 0.01
      }
      const force = K_REPULSION / dist2
      const dist = Math.sqrt(dist2)
      fx += (dx / dist) * force
      fy += (dy / dist) * force
    }
    a.vx += fx
    a.vy += fy
  }

  for (const e of edges) {
    const a = idIndex.get(e.from)
    const b = idIndex.get(e.to)
    if (!a || !b) continue
    const dx = b.x - a.x
    const dy = b.y - a.y
    const dist = Math.sqrt(dx * dx + dy * dy) || 0.01
    const f = K_SPRING * (dist - REST_LEN)
    const ux = (dx / dist) * f
    const uy = (dy / dist) * f
    a.vx += ux
    a.vy += uy
    b.vx -= ux
    b.vy -= uy
  }

  const cx = width / 2
  const cy = height / 2
  for (let i = 0; i < n; i++) {
    const a = arr[i]
    a.vx += (cx - a.x) * K_CENTER
    a.vy += (cy - a.y) * K_CENTER
    a.vx *= 0.85
    a.vy *= 0.85
    const sp = Math.sqrt(a.vx * a.vx + a.vy * a.vy)
    if (sp > MAX_VELOCITY) {
      a.vx = (a.vx / sp) * MAX_VELOCITY
      a.vy = (a.vy / sp) * MAX_VELOCITY
    }
    a.x += a.vx
    a.y += a.vy
    energy += sp * sp
  }

  return energy < ENERGY_THRESHOLD
}

function draw() {
  if (!ctx) return
  const dpr = window.devicePixelRatio || 1
  ctx.setTransform(dpr, 0, 0, dpr, 0, 0)
  ctx.clearRect(0, 0, width, height)

  const bg = getComputedStyle(document.documentElement)
    .getPropertyValue('--gf-bg')
    .trim() || '#0b0d12'
  ctx.fillStyle = bg
  ctx.fillRect(0, 0, width, height)

  ctx.save()
  ctx.translate(transform.x, transform.y)
  ctx.scale(transform.scale, transform.scale)

  const arr = nodes.value
  const visible = new Set<string>()
  for (const t of TOPICS) if (visibleTopics[t]) visible.add(t)

  const visibleNodes = arr.filter((nd) => visible.has(nd.primary))

  const edgeColor =
    getComputedStyle(document.documentElement)
      .getPropertyValue('--gf-border-strong')
      .trim() || '#2a2f3a'
  ctx.strokeStyle = edgeColor
  ctx.lineWidth = 1 / transform.scale
  ctx.globalAlpha = 0.15
  ctx.beginPath()
  const edgeLimit = Math.min(edges.length, EDGE_DRAW_CAP)
  for (let i = 0; i < edgeLimit; i++) {
    const e = edges[i]
    const a = idIndex.get(e.from)
    const b = idIndex.get(e.to)
    if (!a || !b) continue
    if (!visible.has(a.primary) || !visible.has(b.primary)) continue
    ctx.moveTo(a.x, a.y)
    ctx.lineTo(b.x, b.y)
  }
  ctx.stroke()
  ctx.globalAlpha = 1

  for (const a of visibleNodes) {
    const hovered = a.id === hoverId.value
    ctx.beginPath()
    ctx.arc(a.x, a.y, a.r, 0, Math.PI * 2)
    ctx.fillStyle = topicColor(a.primary)
    if (hovered) {
      ctx.shadowColor = topicColor(a.primary)
      ctx.shadowBlur = 12
    } else {
      ctx.shadowBlur = 0
    }
    ctx.globalAlpha = hovered ? 1 : 0.85
    ctx.fill()
  }
  ctx.globalAlpha = 1
  ctx.shadowBlur = 0
  ctx.restore()
}

function tickLoop() {
  tick++
  const stable = step()
  draw()
  if (tick >= MAX_TICKS || stable) {
    statusText.value = stable ? 'settled' : 'stopped (tick cap)'
    rafId = 0
    return
  }
  rafId = requestAnimationFrame(tickLoop)
}

function startSim() {
  if (rafId) cancelAnimationFrame(rafId)
  statusText.value = 'running'
  rafId = requestAnimationFrame(tickLoop)
}

function resizeCanvas() {
  const canvas = canvasEl.value
  const wrap = wrapEl.value
  if (!canvas || !wrap) return
  width = wrap.clientWidth
  height = 600
  const dpr = window.devicePixelRatio || 1
  canvas.width = Math.floor(width * dpr)
  canvas.height = Math.floor(height * dpr)
  canvas.style.width = width + 'px'
  canvas.style.height = height + 'px'
  if (ctx) ctx.setTransform(dpr, 0, 0, dpr, 0, 0)
  draw()
}

function screenToWorld(sx: number, sy: number) {
  return {
    x: (sx - transform.x) / transform.scale,
    y: (sy - transform.y) / transform.scale
  }
}

function nodeAt(sx: number, sy: number): SimNode | null {
  const w = screenToWorld(sx, sy)
  const visible = new Set<string>()
  for (const t of TOPICS) if (visibleTopics[t]) visible.add(t)
  let best: SimNode | null = null
  let bestDist = Infinity
  for (const nd of nodes.value) {
    if (!visible.has(nd.primary)) continue
    const dx = nd.x - w.x
    const dy = nd.y - w.y
    const d = Math.sqrt(dx * dx + dy * dy)
    const hit = nd.r + 4 / transform.scale
    if (d < hit && d < bestDist) {
      bestDist = d
      best = nd
    }
  }
  return best
}

let dragging = false
let dragStartX = 0
let dragStartY = 0
let dragOriginX = 0
let dragOriginY = 0
let dragMoved = false

function onMouseMove(ev: MouseEvent) {
  const rect = canvasEl.value?.getBoundingClientRect()
  if (!rect) return
  const mx = ev.clientX - rect.left
  const my = ev.clientY - rect.top
  if (dragging) {
    const dx = ev.clientX - dragStartX
    const dy = ev.clientY - dragStartY
    if (Math.abs(dx) + Math.abs(dy) > 3) dragMoved = true
    transform.x = dragOriginX + dx
    transform.y = dragOriginY + dy
    draw()
    return
  }
  const nd = nodeAt(mx, my)
  if (nd) {
    if (hoverId.value !== nd.id) {
      hoverId.value = nd.id
      draw()
    }
    hoverInfo.visible = true
    hoverInfo.x = ev.clientX
    hoverInfo.y = ev.clientY
    hoverInfo.name = nd.name
    hoverInfo.id = nd.id
    hoverInfo.topic = nd.topic
    hoverInfo.degree = nd.degree
    canvasEl.value!.style.cursor = 'pointer'
  } else {
    if (hoverId.value !== null) {
      hoverId.value = null
      draw()
    }
    hoverInfo.visible = false
    canvasEl.value!.style.cursor = 'grab'
  }
}

function onMouseDown(ev: MouseEvent) {
  dragging = true
  dragMoved = false
  dragStartX = ev.clientX
  dragStartY = ev.clientY
  dragOriginX = transform.x
  dragOriginY = transform.y
  if (canvasEl.value) canvasEl.value.style.cursor = 'grabbing'
}

function onMouseUp(ev: MouseEvent) {
  if (dragging && !dragMoved) {
    const rect = canvasEl.value?.getBoundingClientRect()
    if (rect) {
      const nd = nodeAt(ev.clientX - rect.left, ev.clientY - rect.top)
      if (nd) {
        console.log('[CallGraph] select', nd.id, nd.name)
      }
    }
  }
  dragging = false
  if (canvasEl.value) canvasEl.value.style.cursor = 'grab'
}

function onMouseLeave() {
  hoverId.value = null
  hoverInfo.visible = false
  dragging = false
}

function onWheel(ev: WheelEvent) {
  ev.preventDefault()
  const rect = canvasEl.value?.getBoundingClientRect()
  if (!rect) return
  const mx = ev.clientX - rect.left
  const my = ev.clientY - rect.top
  const factor = ev.deltaY < 0 ? 1.12 : 1 / 1.12
  const newScale = Math.max(0.2, Math.min(4, transform.scale * factor))
  const ratio = newScale / transform.scale
  transform.x = mx - (mx - transform.x) * ratio
  transform.y = my - (my - transform.y) * ratio
  transform.scale = newScale
  draw()
}

function toggleTopic(t: string) {
  visibleTopics[t] = !visibleTopics[t]
  draw()
}

function enableAll(v: boolean) {
  for (const t of TOPICS) visibleTopics[t] = v
  draw()
}

onMounted(() => {
  const canvas = canvasEl.value!
  ctx = canvas.getContext('2d')
  if (!ctx) return
  resizeCanvas()
  const arr = buildNodes()
  nodes.value = arr
  indexNodes(arr)
  transform.x = width / 2
  transform.y = height / 2
  statusText.value = 'running'
  canvas.style.cursor = 'grab'
  rafId = requestAnimationFrame(tickLoop)
  window.addEventListener('resize', resizeCanvas)
})

onBeforeUnmount(() => {
  if (rafId) cancelAnimationFrame(rafId)
  window.removeEventListener('resize', resizeCanvas)
})
</script>

<template>
  <div ref="wrapEl" class="gf-graph">
    <div class="gf-graph-controls">
      <div class="gf-graph-topics">
        <label
          v-for="t in TOPICS"
          :key="t"
          class="gf-graph-topic"
          :class="{ 'is-off': !visibleTopics[t] }"
        >
          <input type="checkbox" :checked="visibleTopics[t]" @change="toggleTopic(t)" />
          <span class="gf-graph-topic-swatch" :style="{ background: topicColor(t) }" />
          <span class="gf-graph-topic-label">{{ t }}</span>
        </label>
      </div>
      <div class="gf-graph-actions">
        <button class="gf-graph-btn" @click="enableAll(true)">All on</button>
        <button class="gf-graph-btn" @click="enableAll(false)">All off</button>
        <button class="gf-graph-btn gf-graph-btn-primary" @click="resetLayout">
          Reset layout
        </button>
        <span class="gf-graph-count">{{ nodeCount }} nodes / {{ edgeCount }} edges</span>
        <span class="gf-graph-status">{{ statusText }}</span>
      </div>
    </div>

    <div class="gf-graph-canvas-wrap">
      <canvas
        ref="canvasEl"
        @mousemove="onMouseMove"
        @mousedown="onMouseDown"
        @mouseup="onMouseUp"
        @mouseleave="onMouseLeave"
        @wheel.prevent="onWheel"
      />
    </div>

    <div
      v-show="hoverInfo.visible"
      ref="tooltipEl"
      class="gf-graph-tooltip"
      :style="{ left: hoverInfo.x + 'px', top: hoverInfo.y + 'px' }"
    >
      <div class="gf-graph-tooltip-name">{{ hoverInfo.name }}</div>
      <div class="gf-graph-tooltip-row">
        <code>{{ hoverInfo.id }}</code>
        <span class="gf-graph-tooltip-topic">{{ hoverInfo.topic }}</span>
      </div>
      <div class="gf-graph-tooltip-degree">degree {{ hoverInfo.degree }}</div>
    </div>
  </div>
</template>

<style scoped>
.gf-graph {
  position: relative;
  margin: 18px 0;
}
.gf-graph-controls {
  background: var(--gf-panel);
  border: 1px solid var(--gf-border);
  border-radius: 10px 10px 0 0;
  padding: 12px 14px;
  display: flex;
  flex-direction: column;
  gap: 10px;
}
.gf-graph-topics {
  display: flex;
  flex-wrap: wrap;
  gap: 6px 12px;
}
.gf-graph-topic {
  display: inline-flex;
  align-items: center;
  gap: 5px;
  font-family: var(--gf-mono);
  font-size: 0.74rem;
  color: var(--gf-text);
  cursor: pointer;
  user-select: none;
  opacity: 1;
}
.gf-graph-topic.is-off {
  opacity: 0.4;
}
.gf-graph-topic input {
  margin: 0;
  accent-color: var(--gf-accent-2);
}
.gf-graph-topic-swatch {
  width: 10px;
  height: 10px;
  border-radius: 2px;
  display: inline-block;
}
.gf-graph-topic-label {
  color: var(--gf-text-dim);
}
.gf-graph-actions {
  display: flex;
  align-items: center;
  flex-wrap: wrap;
  gap: 8px;
}
.gf-graph-btn {
  font-family: var(--gf-display);
  font-size: 0.8rem;
  padding: 5px 12px;
  border-radius: 6px;
  border: 1px solid var(--gf-border-strong);
  background: var(--gf-panel-2);
  color: var(--gf-text);
  cursor: pointer;
}
.gf-graph-btn:hover {
  border-color: var(--gf-accent-2);
  color: var(--gf-accent-2);
}
.gf-graph-btn-primary {
  background: linear-gradient(135deg, var(--gf-accent), var(--gf-accent-2));
  color: var(--gf-bg);
  border-color: transparent;
  font-weight: 600;
}
.gf-graph-btn-primary:hover {
  color: var(--gf-bg);
  filter: brightness(1.08);
}
.gf-graph-count {
  font-family: var(--gf-mono);
  font-size: 0.74rem;
  color: var(--gf-text-dim);
  margin-left: auto;
}
.gf-graph-status {
  font-family: var(--gf-mono);
  font-size: 0.7rem;
  color: var(--gf-muted);
}
.gf-graph-canvas-wrap {
  border: 1px solid var(--gf-border);
  border-top: none;
  border-radius: 0 0 10px 10px;
  overflow: hidden;
  line-height: 0;
}
.gf-graph-canvas-wrap canvas {
  display: block;
  width: 100%;
  height: 600px;
}
.gf-graph-tooltip {
  position: fixed;
  pointer-events: none;
  transform: translate(12px, 12px);
  background: var(--gf-panel-2);
  border: 1px solid var(--gf-border-strong);
  border-radius: 8px;
  padding: 8px 10px;
  z-index: 50;
  min-width: 160px;
  box-shadow: 0 6px 24px rgba(0, 0, 0, 0.4);
}
.gf-graph-tooltip-name {
  font-family: var(--gf-mono);
  font-size: 0.86rem;
  color: var(--gf-text);
  font-weight: 500;
  margin-bottom: 4px;
  word-break: break-all;
}
.gf-graph-tooltip-row {
  display: flex;
  align-items: center;
  gap: 8px;
  font-size: 0.74rem;
  margin-bottom: 2px;
}
.gf-graph-tooltip-row code {
  font-family: var(--gf-mono);
  color: var(--gf-accent-2);
}
.gf-graph-tooltip-topic {
  color: var(--gf-text-dim);
  font-size: 0.7rem;
}
.gf-graph-tooltip-degree {
  font-family: var(--gf-mono);
  font-size: 0.72rem;
  color: var(--gf-muted);
}
</style>
