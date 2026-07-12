<script setup lang="ts">
import { computed, onBeforeUnmount, onMounted, ref, watch } from 'vue'
import { withBase } from 'vitepress'
import * as THREE from 'three'
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader.js'
import { OrbitControls } from 'three/examples/jsm/controls/OrbitControls.js'

const props = defineProps<{
  id: string
  name?: string
}>()

type AnimationBank = {
  file: string
  group: number
  slot: number
  label: string
  frames: number
  animJoints?: number
  rootSpanX?: number
  rootSpanY?: number
  rootSpanZ?: number
}

type AnimationIndex = {
  borg: string
  bankCount: number
  banks: AnimationBank[]
}

type BakedClip = {
  name?: string
  frameCount: number
  fps?: number
  bones: Array<{
    i: number
    pos?: number[]
    rot?: number[]
    scl?: number[]
  }>
}

const viewport = ref<HTMLElement | null>(null)
const canvas = ref<HTMLCanvasElement | null>(null)
const status = ref('Preparing viewer')
const error = ref('')
const banks = ref<AnimationBank[]>([])
const selectedBankKey = ref('')
const selectedCategory = ref('core')
const playing = ref(true)
const loop = ref(true)
const autoTurn = ref(false)
const speed = ref(1)
const loadProgress = ref(0)

let renderer: THREE.WebGLRenderer | null = null
let scene: THREE.Scene | null = null
let camera: THREE.PerspectiveCamera | null = null
let controls: OrbitControls | null = null
let mixer: THREE.AnimationMixer | null = null
let currentAction: THREE.AnimationAction | null = null
let activeModel: THREE.Object3D | null = null
let resizeObserver: ResizeObserver | null = null
let animationFrame = 0
let loadToken = 0
const clock = new THREE.Clock()
const clipCache = new Map<string, THREE.AnimationClip>()

const selectedBank = computed(() => banks.value.find((bank) => bankKey(bank) === selectedBankKey.value))

const categories = computed(() => {
  const counts = banks.value.reduce<Record<string, number>>((acc, bank) => {
    const category = categorizeBank(bank)
    acc[category] = (acc[category] ?? 0) + 1
    return acc
  }, {})

  return [
    { id: 'core', label: 'Core', count: counts.core ?? 0 },
    { id: 'attack', label: 'Attack', count: counts.attack ?? 0 },
    { id: 'reaction', label: 'Reaction', count: counts.reaction ?? 0 },
    { id: 'special', label: 'Special', count: counts.special ?? 0 },
    { id: 'other', label: 'Other', count: counts.other ?? 0 },
  ].filter((category) => category.count > 0)
})

const visibleBanks = computed(() => banks.value.filter((bank) => categorizeBank(bank) === selectedCategory.value))

function assetUrl(file: string) {
  return withBase(`/models/${props.id}/${file}`)
}

function bankKey(bank: AnimationBank) {
  return `${bank.group}:${bank.slot}:${bank.file}`
}

function categorizeBank(bank: AnimationBank) {
  const label = bank.label.toLowerCase()

  if (/idle|walk|run|dash|jump|fall|land|turn|move|boost|fly|hover/.test(label)) return 'core'
  if (/attack|shot|shoot|beam|slash|punch|kick|throw|melee|charge/.test(label)) return 'attack'
  if (/hit|damage|guard|block|down|stun|recover|knock/.test(label)) return 'reaction'
  if (/special|super|burst|transform|summon|warp|victory|lose|dead|death/.test(label)) return 'special'
  return 'other'
}

function buildClip(json: BakedClip) {
  const fps = json.fps ?? 60
  const frameCount = Math.max(1, json.frameCount)
  const times = Float32Array.from({ length: frameCount }, (_, frame) => frame / fps)
  const tracks: THREE.KeyframeTrack[] = []

  for (const bone of json.bones) {
    const node = `JOBJ_${bone.i}`

    if (bone.pos?.length === frameCount * 3) {
      const values = Float32Array.from(bone.pos)

      // Strip horizontal root motion so movement clips stay inspectable.
      if (bone.i === 0) {
        for (let i = 0; i < values.length; i += 3) {
          values[i] = 0
          values[i + 2] = 0
        }
      }

      tracks.push(new THREE.VectorKeyframeTrack(`${node}.position`, times, values))
    }

    if (bone.rot?.length === frameCount * 4) {
      tracks.push(new THREE.QuaternionKeyframeTrack(`${node}.quaternion`, times, Float32Array.from(bone.rot)))
    }

    if (bone.scl?.length === frameCount * 3) {
      tracks.push(new THREE.VectorKeyframeTrack(`${node}.scale`, times, Float32Array.from(bone.scl)))
    }
  }

  return new THREE.AnimationClip(json.name ?? 'mot', frameCount / fps, tracks)
}

async function loadAnimationClip(bank: AnimationBank) {
  const key = bankKey(bank)
  const cached = clipCache.get(key)
  if (cached) return cached

  const response = await fetch(assetUrl(bank.file))
  if (!response.ok) throw new Error(`Animation ${bank.file} returned ${response.status}`)
  const clip = buildClip((await response.json()) as BakedClip)
  clipCache.set(key, clip)
  return clip
}

async function playBank(bank: AnimationBank) {
  if (!mixer) return

  selectedBankKey.value = bankKey(bank)
  error.value = ''
  status.value = `Loading ${bank.label}`

  try {
    const clip = await loadAnimationClip(bank)
    const nextAction = mixer.clipAction(clip)
    nextAction.reset()
    nextAction.enabled = true
    nextAction.clampWhenFinished = !loop.value
    nextAction.setLoop(loop.value ? THREE.LoopRepeat : THREE.LoopOnce, loop.value ? Infinity : 1)
    nextAction.play()

    if (currentAction && currentAction !== nextAction) {
      currentAction.fadeOut(0.12)
      nextAction.fadeIn(0.12)
    }

    currentAction = nextAction
    playing.value = true
    status.value = `${bank.label} playing`
  } catch (err) {
    error.value = err instanceof Error ? err.message : String(err)
    status.value = 'Animation unavailable'
  }
}

async function loadIndex() {
  const response = await fetch(assetUrl('anim_index.json'))
  if (!response.ok) throw new Error(`Animation index returned ${response.status}`)
  const index = (await response.json()) as AnimationIndex
  return index.banks ?? []
}

async function loadModel(token: number) {
  if (!scene) return

  disposeModel()
  const manager = new THREE.LoadingManager()
  manager.onProgress = (_url, loaded, total) => {
    loadProgress.value = total > 0 ? Math.round((loaded / total) * 100) : 0
  }

  const loader = new GLTFLoader(manager)
  const gltf = await loader.loadAsync(assetUrl('model_00.glb'))
  if (token !== loadToken) return

  const root = gltf.scene
  prepareModel(root)
  scene.add(root)
  activeModel = root
  mixer = new THREE.AnimationMixer(root)
  resetCamera()
}

function prepareModel(root: THREE.Object3D) {
  root.traverse((node) => {
    if (!(node instanceof THREE.Mesh)) return
    node.frustumCulled = false
    node.castShadow = false
    node.receiveShadow = true

    const materials = Array.isArray(node.material) ? node.material : [node.material]
    for (const material of materials) {
      material.side = THREE.DoubleSide
      material.needsUpdate = true
      if ('metalness' in material) {
        ;(material as THREE.MeshStandardMaterial).metalness = 0
      }
    }
  })

  const box = new THREE.Box3().setFromObject(root)
  const size = new THREE.Vector3()
  const center = new THREE.Vector3()
  box.getSize(size)
  box.getCenter(center)

  const maxSize = Math.max(size.x, size.y, size.z, 0.001)
  root.position.sub(center)
  root.position.y += size.y / 2
  root.scale.setScalar(2.65 / maxSize)
}

async function loadAll() {
  const token = ++loadToken
  error.value = ''
  status.value = `Loading ${props.name ?? props.id}`
  loadProgress.value = 0
  banks.value = []
  selectedBankKey.value = ''
  clipCache.clear()

  try {
    const [nextBanks] = await Promise.all([loadIndex(), loadModel(token)])
    if (token !== loadToken) return

    banks.value = nextBanks
    const initial = chooseInitialBank(nextBanks)
    selectedCategory.value = initial ? categorizeBank(initial) : categories.value[0]?.id ?? 'core'

    if (initial) {
      await playBank(initial)
    } else {
      status.value = 'Model loaded'
    }
  } catch (err) {
    error.value = err instanceof Error ? err.message : String(err)
    status.value = 'Model unavailable'
  }
}

function chooseInitialBank(nextBanks: AnimationBank[]) {
  return (
    nextBanks.find((bank) => /idle/i.test(bank.label)) ??
    nextBanks.find((bank) => categorizeBank(bank) === 'core') ??
    nextBanks[0]
  )
}

function initScene() {
  if (!canvas.value || !viewport.value) return

  scene = new THREE.Scene()
  scene.background = new THREE.Color(0x101318)
  scene.fog = new THREE.Fog(0x101318, 7, 15)

  camera = new THREE.PerspectiveCamera(38, 1, 0.01, 100)
  camera.position.set(0, 1.35, 4.2)

  renderer = new THREE.WebGLRenderer({
    canvas: canvas.value,
    antialias: true,
    alpha: false,
    preserveDrawingBuffer: true,
    powerPreference: 'high-performance',
  })
  renderer.outputColorSpace = THREE.SRGBColorSpace
  renderer.setPixelRatio(Math.min(window.devicePixelRatio || 1, 2))
  renderer.setClearColor(0x101318, 1)

  controls = new OrbitControls(camera, renderer.domElement)
  controls.enableDamping = true
  controls.dampingFactor = 0.08
  controls.minDistance = 1.8
  controls.maxDistance = 8
  controls.target.set(0, 1.05, 0)
  controls.update()

  const ambient = new THREE.HemisphereLight(0xcfd8ff, 0x242018, 2.4)
  scene.add(ambient)

  const key = new THREE.DirectionalLight(0xffffff, 2.7)
  key.position.set(3, 4, 4)
  scene.add(key)

  const fill = new THREE.DirectionalLight(0x84c5ff, 1.15)
  fill.position.set(-4, 2.5, -2)
  scene.add(fill)

  const grid = new THREE.GridHelper(4.5, 18, 0x2b3440, 0x1c242c)
  grid.position.y = -0.01
  scene.add(grid)

  resizeObserver = new ResizeObserver(resizeRenderer)
  resizeObserver.observe(viewport.value)
  resizeRenderer()
  renderLoop()
}

function resizeRenderer() {
  if (!renderer || !camera || !viewport.value) return

  const rect = viewport.value.getBoundingClientRect()
  const width = Math.max(1, Math.floor(rect.width))
  const height = Math.max(1, Math.floor(rect.height))
  renderer.setSize(width, height, false)
  camera.aspect = width / height
  camera.updateProjectionMatrix()
}

function renderLoop() {
  const dt = clock.getDelta()

  if (playing.value && mixer) {
    mixer.update(dt * speed.value)
  }

  if (autoTurn.value && activeModel) {
    activeModel.rotation.y += dt * 0.35
  }

  controls?.update()
  if (renderer && scene && camera) renderer.render(scene, camera)
  animationFrame = requestAnimationFrame(renderLoop)
}

function resetCamera() {
  if (!camera || !controls) return
  camera.position.set(0, 1.35, 4.2)
  controls.target.set(0, 1.05, 0)
  controls.update()
}

function togglePlaying() {
  playing.value = !playing.value
  status.value = playing.value && selectedBank.value ? `${selectedBank.value.label} playing` : 'Paused'
}

function toggleLoop() {
  loop.value = !loop.value
  if (!currentAction) return
  currentAction.clampWhenFinished = !loop.value
  currentAction.setLoop(loop.value ? THREE.LoopRepeat : THREE.LoopOnce, loop.value ? Infinity : 1)
}

function disposeModel() {
  if (!scene || !activeModel) return

  scene.remove(activeModel)
  activeModel.traverse((node) => {
    if (!(node instanceof THREE.Mesh)) return
    node.geometry?.dispose()
    const materials = Array.isArray(node.material) ? node.material : [node.material]
    for (const material of materials) material.dispose()
  })

  activeModel = null
  mixer = null
  currentAction = null
}

function disposeScene() {
  cancelAnimationFrame(animationFrame)
  resizeObserver?.disconnect()
  controls?.dispose()
  disposeModel()
  renderer?.dispose()
  scene = null
  camera = null
  controls = null
  renderer = null
}

watch(
  () => props.id,
  () => {
    if (scene) loadAll()
  },
)

onMounted(() => {
  initScene()
  loadAll()
})

onBeforeUnmount(() => {
  disposeScene()
})
</script>

<template>
  <section class="borg-model-viewer" aria-label="Borg model and animation viewer">
    <div class="viewer-shell">
      <div ref="viewport" class="viewer-stage">
        <canvas ref="canvas" aria-label="Interactive 3D Borg model"></canvas>
        <div class="viewer-status" :class="{ danger: error }">
          <span>{{ status }}</span>
          <span v-if="loadProgress > 0 && loadProgress < 100">{{ loadProgress }}%</span>
        </div>
      </div>

      <aside class="viewer-controls" aria-label="Animation controls">
        <div class="viewer-title">
          <p>Model</p>
          <h2>{{ name ?? id }}</h2>
          <span>{{ id }}</span>
        </div>

        <div class="transport-row">
          <button class="primary-control" type="button" @click="togglePlaying">
            {{ playing ? 'Pause' : 'Play' }}
          </button>
          <button type="button" :class="{ active: loop }" @click="toggleLoop">Loop</button>
          <button type="button" :class="{ active: autoTurn }" @click="autoTurn = !autoTurn">Turn</button>
          <button type="button" @click="resetCamera">Reset</button>
        </div>

        <label class="speed-control">
          <span>Speed</span>
          <input v-model.number="speed" type="range" min="0.1" max="2" step="0.1" />
          <strong>{{ speed.toFixed(1) }}x</strong>
        </label>

        <div v-if="categories.length" class="category-tabs" role="tablist" aria-label="Animation groups">
          <button
            v-for="category in categories"
            :key="category.id"
            type="button"
            role="tab"
            :aria-selected="selectedCategory === category.id"
            :class="{ active: selectedCategory === category.id }"
            @click="selectedCategory = category.id"
          >
            {{ category.label }}
            <span>{{ category.count }}</span>
          </button>
        </div>

        <div class="animation-list" aria-label="Available animations">
          <button
            v-for="bank in visibleBanks"
            :key="bankKey(bank)"
            type="button"
            :class="{ active: selectedBankKey === bankKey(bank) }"
            @click="playBank(bank)"
          >
            <span>{{ bank.label }}</span>
            <small>g{{ bank.group }} s{{ bank.slot }} - {{ bank.frames }}f</small>
          </button>
        </div>

        <dl v-if="selectedBank" class="animation-meta">
          <div>
            <dt>Clip</dt>
            <dd>{{ selectedBank.file }}</dd>
          </div>
          <div>
            <dt>Joints</dt>
            <dd>{{ selectedBank.animJoints ?? 'n/a' }}</dd>
          </div>
          <div>
            <dt>Root span</dt>
            <dd>
              x{{ selectedBank.rootSpanX?.toFixed(2) ?? '0.00' }}
              y{{ selectedBank.rootSpanY?.toFixed(2) ?? '0.00' }}
              z{{ selectedBank.rootSpanZ?.toFixed(2) ?? '0.00' }}
            </dd>
          </div>
        </dl>

        <p v-if="error" class="viewer-error">{{ error }}</p>
      </aside>
    </div>
  </section>
</template>

<style scoped>
.borg-model-viewer {
  margin: 24px 0 28px;
}

.viewer-shell {
  display: grid;
  grid-template-columns: minmax(0, 1fr) minmax(300px, 360px);
  min-height: 560px;
  border: 1px solid var(--vp-c-divider);
  border-radius: 8px;
  overflow: hidden;
  background:
    linear-gradient(135deg, rgba(48, 96, 128, 0.18), rgba(16, 19, 24, 0.82)),
    var(--vp-c-bg-soft);
}

.viewer-stage {
  position: relative;
  min-height: 560px;
  background: #101318;
}

.viewer-stage canvas {
  display: block;
  width: 100%;
  height: 100%;
}

.viewer-status {
  position: absolute;
  left: 14px;
  bottom: 14px;
  display: inline-flex;
  gap: 10px;
  align-items: center;
  max-width: calc(100% - 28px);
  padding: 7px 10px;
  border: 1px solid rgba(255, 255, 255, 0.12);
  border-radius: 6px;
  color: #dbe7ef;
  background: rgba(10, 14, 18, 0.72);
  font-size: 12px;
  line-height: 1.3;
  backdrop-filter: blur(8px);
}

.viewer-status.danger {
  color: #ffc9bc;
  border-color: rgba(255, 120, 96, 0.45);
}

.viewer-controls {
  display: flex;
  flex-direction: column;
  min-width: 0;
  padding: 18px;
  gap: 16px;
  background: color-mix(in srgb, var(--vp-c-bg) 92%, transparent);
  border-left: 1px solid var(--vp-c-divider);
}

.viewer-title {
  display: grid;
  gap: 3px;
}

.viewer-title p,
.viewer-title span {
  margin: 0;
  color: var(--vp-c-text-2);
  font-size: 12px;
  line-height: 1.3;
}

.viewer-title h2 {
  margin: 0;
  color: var(--vp-c-text-1);
  font-size: 22px;
  line-height: 1.15;
}

.transport-row {
  display: grid;
  grid-template-columns: repeat(4, minmax(0, 1fr));
  gap: 8px;
}

.transport-row button,
.category-tabs button,
.animation-list button {
  border: 1px solid var(--vp-c-divider);
  border-radius: 6px;
  color: var(--vp-c-text-1);
  background: var(--vp-c-bg-soft);
  cursor: pointer;
  transition:
    border-color 0.14s ease,
    background 0.14s ease,
    color 0.14s ease;
}

.transport-row button {
  min-height: 38px;
  padding: 0 8px;
  font-size: 13px;
}

.transport-row button:hover,
.category-tabs button:hover,
.animation-list button:hover {
  border-color: var(--vp-c-brand-1);
}

.transport-row button.active,
.transport-row .primary-control,
.category-tabs button.active,
.animation-list button.active {
  border-color: color-mix(in srgb, var(--vp-c-brand-1) 70%, white);
  background: color-mix(in srgb, var(--vp-c-brand-1) 18%, var(--vp-c-bg));
}

.speed-control {
  display: grid;
  grid-template-columns: auto minmax(0, 1fr) 44px;
  gap: 10px;
  align-items: center;
  color: var(--vp-c-text-2);
  font-size: 13px;
}

.speed-control input {
  width: 100%;
}

.speed-control strong {
  color: var(--vp-c-text-1);
  font-weight: 650;
  text-align: right;
}

.category-tabs {
  display: grid;
  grid-template-columns: repeat(5, minmax(0, 1fr));
  gap: 6px;
}

.category-tabs button {
  display: grid;
  min-height: 46px;
  padding: 7px 5px;
  place-items: center;
  font-size: 12px;
  line-height: 1.15;
}

.category-tabs span {
  color: var(--vp-c-text-2);
  font-size: 11px;
}

.animation-list {
  display: grid;
  gap: 7px;
  max-height: 250px;
  padding-right: 4px;
  overflow: auto;
}

.animation-list button {
  display: grid;
  gap: 2px;
  min-height: 48px;
  padding: 8px 10px;
  text-align: left;
}

.animation-list span {
  overflow: hidden;
  color: var(--vp-c-text-1);
  font-size: 13px;
  line-height: 1.2;
  text-overflow: ellipsis;
  white-space: nowrap;
}

.animation-list small {
  color: var(--vp-c-text-2);
  font-size: 11px;
  line-height: 1.2;
}

.animation-meta {
  display: grid;
  gap: 8px;
  margin: 0;
  padding-top: 4px;
}

.animation-meta div {
  display: grid;
  grid-template-columns: 76px minmax(0, 1fr);
  gap: 10px;
  align-items: baseline;
}

.animation-meta dt {
  color: var(--vp-c-text-2);
  font-size: 12px;
}

.animation-meta dd {
  min-width: 0;
  margin: 0;
  overflow-wrap: anywhere;
  color: var(--vp-c-text-1);
  font-family: var(--vp-font-family-mono);
  font-size: 12px;
}

.viewer-error {
  margin: 0;
  color: #d14b32;
  font-size: 13px;
  line-height: 1.45;
}

@media (max-width: 860px) {
  .viewer-shell {
    grid-template-columns: 1fr;
    min-height: 0;
  }

  .viewer-stage {
    min-height: 420px;
    aspect-ratio: 1 / 1;
  }

  .viewer-controls {
    border-top: 1px solid var(--vp-c-divider);
    border-left: 0;
  }
}

@media (max-width: 520px) {
  .viewer-stage {
    min-height: 340px;
  }

  .viewer-controls {
    padding: 14px;
  }

  .transport-row {
    grid-template-columns: repeat(2, minmax(0, 1fr));
  }

  .category-tabs {
    grid-template-columns: repeat(3, minmax(0, 1fr));
  }
}
</style>
