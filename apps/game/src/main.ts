// Gotcha Force (web) — entry point.
//
// This wires the three finished systems into a playable CHALLENGE-mode loop:
//   A) @gf/combat   — the deterministic battle sim (createBattle / battle.step).
//   B) @gf/missions — CHALLENGE run/progression (createChallengeRun / computeResults).
//   C) apps/game/src/ui — the framework-free screen + HUD components.
//
// Screen flow:
//   MainMenu -> (challenge) -> SelectDifficulty -> SelectPlayers -> LoadBoxData
//     -> SelectForce -> ForceBuilder/edit -> BattleIntro -> BATTLE
//     -> Results -> next battle / back to menu
//   PauseMenu overlays the battle on Start/Esc.
//
// The existing three.js scene, stage rendering, lighting, camera, the Collada
// model loader, and the baked-clip builder are REUSED. The netcode `ws` hooks are
// preserved (defined but dormant) so multiplayer can be wired next.

import * as THREE from "three";
import { ColladaLoader } from "three/examples/jsm/loaders/ColladaLoader.js";
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js";
import { clone } from "three/examples/jsm/utils/SkeletonUtils.js";

import borgs from "../../../packages/assets/data/borgs.json";

import {
  setBorgStats,
  createBattle,
  DEFAULT_BOUNDS,
  emptyInput,
  type Battle,
  type BorgStats,
  type BorgRuntime,
  type PlayerInput,
  type RectStageBounds,
  type StageCollision,
  type StageCollisionTriangle,
} from "@gf/combat";
import { createAudioManager, type GotchaAudioManager } from "@gf/audio";
import { hitBin } from "@gf/formats";
import {
  createChallengeRun,
  computeResults,
  type ChallengeRun,
  type BattleConfig as MissionBattleConfig,
  type BattleOutcome,
  type BattleResults,
} from "@gf/missions";

import {
  ensureStyles,
  createMainMenu,
  createSelectDifficulty,
  createSelectPlayers,
  createLoadBoxData,
  createSelectForce,
  createForceBuilder,
  createBattleIntro,
  createResults,
  createPauseMenu,
  createBattleHud,
  type ForceBorg,
  type ForceSlot,
  type BattleHudHandle,
} from "./ui/index.js";

import { convertBattleConfig, inputFromKeys, playerIdFor, DEFAULT_ARENA_STAGE, stageIdForArena } from "./sim/adapter.js";
import { BattleScene, type AnimSlot } from "./sim/battleScene.js";

// ------------------------------------------------------------------------------------------
// Data
// ------------------------------------------------------------------------------------------

type BorgEntry = {
  id: string;
  name: string;
  energy: number;
  speed?: number;
  tribe?: string;
  type?: string;
  hp?: string;
  defense?: number;
  shot?: number;
  attack?: number;
  jump?: string;
};

const allBorgs = (borgs as { borgs: BorgEntry[] }).borgs.filter((b) => b.id && b.name);

// Register the per-borg stat table with the sim once.
setBorgStats(allBorgs as unknown as BorgStats[]);

// The force-builder catalog (id, name, energy), grouped by tribe then cost.
const FORCE_CATALOG: ForceBorg[] = [...allBorgs]
  .sort(
    (a, b) =>
      (a.tribe ?? "").localeCompare(b.tribe ?? "") ||
      a.energy - b.energy ||
      a.name.localeCompare(b.name),
  )
  .map((b) => ({ id: b.id, name: b.name, energy: b.energy }));

const DEFAULT_LEAD = "pl0615"; // G Red — fully animated, used as a sensible default.
const FORCE_BY_ID = new Map(FORCE_CATALOG.map((entry) => [entry.id, entry] as const));
const DEFAULT_FORCE_SLOTS: ForceSlot[] = [
  { no: 1, name: "G RED FORCE", borgIds: [DEFAULT_LEAD] },
  { no: 2, name: "DEATH BORG FORCE", borgIds: ["pl0008", "pl000c"] },
  { no: 3, name: "GUN BORG FORCE", borgIds: ["pl0102", "pl0104"] },
];

// Exported ADX->OGG cues from poq_adx_usa.afs. Exact Challenge cue semantics
// still need DOL trace confirmation, so these are conservative asset-backed
// defaults rather than claimed final music IDs.
const AUDIO_CUES = {
  menuBgm: "bgm00",
  battleBgm: "bgm01",
  confirm: "se00_00",
  back: "se00_01",
  edit: "se00_02",
} as const;

function selectedForce(): string[] {
  const valid = selectedForceSlot().borgIds.filter((id) => FORCE_BY_ID.has(id));
  return valid.length > 0 ? valid : [DEFAULT_LEAD];
}

function selectedForceSlot(): ForceSlot {
  return flow.forceSlots[flow.selectedForceSlot] ?? flow.forceSlots[0] ?? DEFAULT_FORCE_SLOTS[0]!;
}

function updateSelectedForceSlot(borgIds: readonly string[]): void {
  const slot = selectedForceSlot();
  const valid = borgIds.filter((id) => FORCE_BY_ID.has(id));
  flow.forceSlots[flow.selectedForceSlot] = {
    ...slot,
    borgIds: valid.length > 0 ? [...valid] : [DEFAULT_LEAD],
  };
}

// Borgs that have a verified Collada model in the library (or the pl0615 special path).
const LIBRARY_IDS = new Set<string>();
// Filled from the manifest at load time.

// ------------------------------------------------------------------------------------------
// three.js scene (preserved from the original app)
// ------------------------------------------------------------------------------------------

const DEFAULT_RENDER_STATE = {
  fogColor: 0xfff6e5,
  fogNear: 900,
  fogFar: 40000,
  fov: 43.191872,
  near: 10,
  far: 80000,
  ambientColor: 0xd8d0c2,
  lightColor: 0xfff0e6,
  lightPosition: new THREE.Vector3(-385.512512, 956.0448, -377.986603),
};

type StageManifest = {
  id: string;
  models?: Array<{ path: string; bytes?: number }>;
  collision?: Array<{ path: string; bytes?: number }>;
  visual?: {
    daeCount?: number;
    expectedDaeIndices?: number[];
  };
};

type StageResources = {
  bounds: RectStageBounds | undefined;
  collision: StageCollision | undefined;
};

type StageVector = [number, number, number];
type StageColorRecord = { rgbHex?: string };
type ExtractedStageLight = {
  role?: string;
  color?: StageColorRecord;
  intensity?: number;
  position?: { position?: number[] } | null;
};
type LegacyStageLights = {
  ambient?: { colorRgbHex?: string; intensity?: number };
  directional?: { colorRgbHex?: string; intensity?: number; position?: number[] };
};

type StageRenderState = {
  camera?: { fovDegrees?: number; near?: number; far?: number };
  fog?: { colorRgbHex?: string; color?: StageColorRecord; start?: number; end?: number };
  lights?: ExtractedStageLight[] | LegacyStageLights;
};

type ModelManifestEntry = { id: string; name: string; dae: string };

const uiElement = document.getElementById("ui");
const canvas = document.getElementById("app") as HTMLCanvasElement;
if (!uiElement) throw new Error("Missing #ui");
const ui = uiElement;
ui.style.pointerEvents = "auto"; // the UI component library uses real buttons.

// preserveDrawingBuffer lets us snapshot the canvas via toDataURL for headless
// verification (the preview tab is backgrounded so rAF render is throttled).
const renderer = new THREE.WebGLRenderer({ canvas, antialias: true, preserveDrawingBuffer: true });
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.outputColorSpace = THREE.SRGBColorSpace;

const scene = new THREE.Scene();
scene.background = new THREE.Color(DEFAULT_RENDER_STATE.fogColor);
scene.fog = new THREE.Fog(DEFAULT_RENDER_STATE.fogColor, DEFAULT_RENDER_STATE.fogNear, DEFAULT_RENDER_STATE.fogFar);

const camera = new THREE.PerspectiveCamera(
  DEFAULT_RENDER_STATE.fov,
  window.innerWidth / window.innerHeight,
  DEFAULT_RENDER_STATE.near,
  DEFAULT_RENDER_STATE.far,
);
camera.position.set(950, 520, 1320);

const controls = new OrbitControls(camera, renderer.domElement);
controls.enableDamping = true;
controls.target.set(0, 80, 0);

const stageAmbient = new THREE.AmbientLight(DEFAULT_RENDER_STATE.ambientColor, 1);
scene.add(stageAmbient);
const stageLight = new THREE.DirectionalLight(DEFAULT_RENDER_STATE.lightColor, 1);
stageLight.position.copy(DEFAULT_RENDER_STATE.lightPosition);
scene.add(stageLight);

const stageRoot = new THREE.Group();
scene.add(stageRoot);

// Battle actors (sim-driven borg models) live under their own group.
const battleRoot = new THREE.Group();
scene.add(battleRoot);

let modelManifest: ModelManifestEntry[] = [];

// --- model + clip caches (reused by the BattleScene via the asset hooks) ---
const sourceModels = new Map<string, Promise<THREE.Object3D | null>>();
const clipCache = new Map<string, Promise<THREE.AnimationClip | null>>();

type BakedClip = {
  name?: string;
  frameCount: number;
  fps?: number;
  bones: Array<{ i: number; pos?: number[]; rot?: number[]; scl?: number[] }>;
};

type AnimBank = {
  file: string;
  group: number;
  slot: number;
  label: string;
  frames: number;
};

type AnimIndex = {
  borg: string;
  banks: AnimBank[];
};

function buildClip(json: BakedClip): THREE.AnimationClip {
  const fps = json.fps ?? 60;
  const times = Float32Array.from({ length: json.frameCount }, (_, frame) => frame / fps);
  const tracks: THREE.KeyframeTrack[] = [];
  for (const bone of json.bones) {
    const node = `JOBJ_${bone.i}`;
    if (bone.pos?.length === json.frameCount * 3) {
      tracks.push(new THREE.VectorKeyframeTrack(`${node}.position`, times, Float32Array.from(bone.pos)));
    }
    if (bone.rot?.length === json.frameCount * 4) {
      tracks.push(new THREE.QuaternionKeyframeTrack(`${node}.quaternion`, times, Float32Array.from(bone.rot)));
    }
    if (bone.scl?.length === json.frameCount * 3) {
      tracks.push(new THREE.VectorKeyframeTrack(`${node}.scale`, times, Float32Array.from(bone.scl)));
    }
  }
  return new THREE.AnimationClip(json.name ?? "mot", json.frameCount / fps, tracks);
}

function normalizeModel(model: THREE.Object3D): void {
  model.updateMatrixWorld(true);
  const box = new THREE.Box3().setFromObject(model);
  const center = new THREE.Vector3();
  box.getCenter(center);
  model.position.x -= center.x;
  model.position.z -= center.z;
  model.position.y -= box.min.y;
  model.traverse((object) => {
    if (object instanceof THREE.Mesh || object instanceof THREE.SkinnedMesh) {
      object.frustumCulled = false;
      const materials = Array.isArray(object.material) ? object.material : [object.material];
      for (const material of materials) {
        material.side = THREE.DoubleSide;
        if ("metalness" in material) (material as THREE.MeshStandardMaterial).metalness = 0;
      }
    }
  });
}

/** Resolve the .dae url for a borg id (pl0615 has a special path; others come from the library). */
function modelUrlFor(id: string): string | null {
  if (id === DEFAULT_LEAD) return "/models/pl0615/model_00.dae";
  if (!LIBRARY_IDS.has(id)) return null;
  const entry = modelManifest.find((e) => e.id === id);
  return `/models/library/${id}/${entry?.dae ?? `${id}.dae`}`;
}

/** Load (and cache) a cloneable SOURCE model for a borg id. Returns a fresh clone per call. */
async function loadBorgModel(id: string): Promise<THREE.Object3D | null> {
  let sourceP = sourceModels.get(id);
  if (!sourceP) {
    const url = modelUrlFor(id);
    sourceP = url
      ? new ColladaLoader()
          .loadAsync(url)
          .then((c) => {
            normalizeModel(c.scene);
            return c.scene as THREE.Object3D;
          })
          .catch(() => null)
      : Promise.resolve(null);
    sourceModels.set(id, sourceP);
  }
  const source = await sourceP;
  if (!source) return null;
  return clone(source);
}

const animIndexCache = new Map<string, Promise<AnimIndex | null>>();

const SLOT_LABELS: Record<AnimSlot, RegExp[]> = {
  idle: [/^idle$/],
  move: [/^move$/, /^move_s\d+$/],
  dash: [/^dash_fwd$/, /^dash_(right|left|back)$/, /^boost$/],
  dash_fwd: [/^dash_fwd$/],
  dash_back: [/^dash_back$/],
  dash_left: [/^dash_left$/],
  dash_right: [/^dash_right$/],
  jump: [/^jump_takeoff$/, /^fly_transition$/, /^boost$/],
  fly: [/^boost$/, /^fly_transition$/, /^move_s\d+$/],
  attack: [/^attack_s\d+$/, /^attack_lunge_s\d+$/],
  melee: [/^attack_lunge_s\d+$/, /^attack_s\d+$/],
  shoot: [/^attack_s\d+$/, /^special_s\d+$/],
  special: [/^special_s\d+$/],
  hit: [/^hit_react_s\d+$/, /^guard_s\d+$/],
  down: [/^hit_react_s\d+$/, /^guard_s\d+$/, /^death$/],
  death: [/^death$/, /^win_or_death$/],
  spawn: [/^pose_short$/, /^idle$/],
  victory: [/^victory$/, /^win_or_death$/],
};

const SLOT_FALLBACKS: Partial<Record<AnimSlot, AnimSlot[]>> = {
  dash_fwd: ["dash", "move", "idle"],
  dash_back: ["dash", "move", "idle"],
  dash_left: ["dash", "move", "idle"],
  dash_right: ["dash", "move", "idle"],
  dash: ["move", "idle"],
  move: ["idle"],
  jump: ["fly", "move", "idle"],
  fly: ["jump", "move", "idle"],
  attack: ["melee", "shoot", "move", "idle"],
  melee: ["attack", "idle"],
  shoot: ["attack", "special", "move", "idle"],
  special: ["attack", "idle"],
  hit: ["idle"],
  down: ["hit", "death", "idle"],
  death: ["idle"],
  spawn: ["idle"],
  victory: ["idle"],
};

const PREFERRED_LABELS: Partial<Record<string, Partial<Record<AnimSlot, string[]>>>> = {
  pl0615: {
    shoot: ["attack_s4"],
    melee: ["attack_lunge_s1"],
    hit: ["hit_react_s0"],
    special: ["special_s0"],
    death: ["death"],
    victory: ["victory"],
  },
  pl0008: {
    melee: ["attack_lunge_s1"],
    hit: ["hit_react_s0"],
    special: ["special_s0"],
    death: ["death", "win_or_death"],
    victory: ["victory"],
  },
  pl000c: {
    melee: ["attack_lunge_s1"],
    hit: ["hit_react_s0"],
    special: ["special_s0"],
    death: ["death", "win_or_death"],
    victory: ["victory"],
  },
  pl0105: {
    melee: ["attack_lunge_s1"],
    hit: ["hit_react_s0"],
    special: ["special_s0"],
    death: ["death", "win_or_death"],
  },
  pl0109: {
    melee: ["attack_lunge_s1"],
    hit: ["guard_s11"],
    special: ["special_s0"],
    death: ["death", "win_or_death"],
  },
};

async function loadAnimIndex(id: string): Promise<AnimIndex | null> {
  let p = animIndexCache.get(id);
  if (!p) {
    p = fetch(`/models/${id}/anim_index.json`)
      .then((r) => (r.ok ? (r.json() as Promise<AnimIndex>) : null))
      .catch(() => null);
    animIndexCache.set(id, p);
  }
  return p;
}

function pickAnimBank(index: AnimIndex, slot: AnimSlot): AnimBank | null {
  const direct = pickAnimBankDirect(index, slot);
  if (direct) return direct;
  for (const fallback of SLOT_FALLBACKS[slot] ?? []) {
    const bank = pickAnimBankDirect(index, fallback);
    if (bank) return bank;
  }
  return null;
}

function pickAnimBankDirect(index: AnimIndex, slot: AnimSlot): AnimBank | null {
  const banks = [...index.banks].sort((a, b) => a.group - b.group || a.slot - b.slot || a.frames - b.frames);
  for (const label of PREFERRED_LABELS[index.borg]?.[slot] ?? []) {
    const match = banks.find((bank) => bank.label === label);
    if (match) return match;
  }
  const patterns = SLOT_LABELS[slot];
  for (const pattern of patterns) {
    const match = banks.find((bank) => pattern.test(bank.label));
    if (match) return match;
  }
  return null;
}

async function loadBorgClip(id: string, slot: AnimSlot): Promise<THREE.AnimationClip | null> {
  const key = `${id}:${slot}`;
  let p = clipCache.get(key);
  if (!p) {
    p = loadAnimIndex(id)
      .then((index) => {
        const bank = index ? pickAnimBank(index, slot) : null;
        return bank ? fetch(`/models/${id}/${bank.file}`) : null;
      })
      .then((r) => (r?.ok ? (r.json() as Promise<BakedClip>) : null))
      .then((json) => (json ? buildClip(json) : null))
      .catch(() => null);
    clipCache.set(key, p);
  }
  return p;
}

const battleScene = new BattleScene(battleRoot, { loadModel: loadBorgModel, loadClip: loadBorgClip });
const cameraFocus = new THREE.Vector3();
const cameraGoal = new THREE.Vector3();
const cameraForward = new THREE.Vector3();
const cameraInward = new THREE.Vector3();
const fallbackStageBounds: RectStageBounds = {
  minX: -DEFAULT_BOUNDS.x,
  maxX: DEFAULT_BOUNDS.x,
  minZ: -DEFAULT_BOUNDS.z,
  maxZ: DEFAULT_BOUNDS.z,
};

// ------------------------------------------------------------------------------------------
// Stage loading (preserved)
// ------------------------------------------------------------------------------------------

function parseHexColor(value: string | undefined, fallback: number): number {
  if (!value || !/^#[0-9a-f]{6}$/i.test(value)) return fallback;
  return Number.parseInt(value.slice(1), 16);
}

function stageVector(value: number[] | undefined): StageVector | undefined {
  if (!value || value.length < 3) return undefined;
  const [x, y, z] = value;
  if (x === undefined || y === undefined || z === undefined) return undefined;
  return Number.isFinite(x) && Number.isFinite(y) && Number.isFinite(z) ? [x, y, z] : undefined;
}

function extractedLights(rs: StageRenderState | null): ExtractedStageLight[] {
  return Array.isArray(rs?.lights) ? rs.lights : [];
}

function legacyLights(rs: StageRenderState | null): LegacyStageLights {
  return rs?.lights && !Array.isArray(rs.lights) ? rs.lights : {};
}

function resolveAmbientLight(rs: StageRenderState | null): { color: string | undefined; intensity: number | undefined } {
  const legacy = legacyLights(rs).ambient;
  const extracted =
    extractedLights(rs).find((light) => /ambient|global/i.test(light.role ?? "")) ??
    extractedLights(rs).find((light) => !stageVector(light.position?.position));
  return {
    color: legacy?.colorRgbHex ?? extracted?.color?.rgbHex,
    intensity: legacy?.intensity ?? extracted?.intensity,
  };
}

function resolveDirectionalLight(
  rs: StageRenderState | null,
): { color: string | undefined; intensity: number | undefined; position: StageVector | undefined } {
  const legacy = legacyLights(rs).directional;
  const extracted =
    extractedLights(rs).find((light) => stageVector(light.position?.position)) ??
    extractedLights(rs).find((light) => /positioned|diffuse|specular/i.test(light.role ?? ""));
  return {
    color: legacy?.colorRgbHex ?? extracted?.color?.rgbHex,
    intensity: legacy?.intensity ?? extracted?.intensity,
    position: stageVector(legacy?.position) ?? stageVector(extracted?.position?.position),
  };
}

function applyStageRenderState(rs: StageRenderState | null): void {
  const fogColor = parseHexColor(rs?.fog?.color?.rgbHex ?? rs?.fog?.colorRgbHex, DEFAULT_RENDER_STATE.fogColor);
  const ambient = resolveAmbientLight(rs);
  const directional = resolveDirectionalLight(rs);
  scene.background = new THREE.Color(fogColor);
  scene.fog = new THREE.Fog(fogColor, rs?.fog?.start ?? DEFAULT_RENDER_STATE.fogNear, rs?.fog?.end ?? DEFAULT_RENDER_STATE.fogFar);
  camera.fov = rs?.camera?.fovDegrees ?? DEFAULT_RENDER_STATE.fov;
  camera.near = rs?.camera?.near ?? DEFAULT_RENDER_STATE.near;
  camera.far = rs?.camera?.far ?? DEFAULT_RENDER_STATE.far;
  camera.updateProjectionMatrix();
  stageAmbient.color.setHex(parseHexColor(ambient.color, DEFAULT_RENDER_STATE.ambientColor));
  stageAmbient.intensity = ambient.intensity ?? 1;
  stageLight.color.setHex(parseHexColor(directional.color, DEFAULT_RENDER_STATE.lightColor));
  stageLight.intensity = directional.intensity ?? 1;
  const lp = directional.position;
  if (lp) stageLight.position.set(lp[0], lp[1], lp[2]);
  else stageLight.position.copy(DEFAULT_RENDER_STATE.lightPosition);
}

let loadedStageId: string | null = null;
let loadedStageResources: StageResources = { bounds: undefined, collision: undefined };
function stageModelPaths(manifest: StageManifest): string[] {
  if (Array.isArray(manifest.models) && manifest.models.length > 0) {
    return manifest.models.map((m) => m.path);
  }

  const indices = manifest.visual?.expectedDaeIndices;
  if (indices && indices.length > 0) {
    return indices.map((i) => `model/model_${String(i).padStart(2, "0")}.dae`);
  }

  const count = manifest.visual?.daeCount ?? 0;
  return Array.from({ length: count }, (_, i) => `model/model_${String(i).padStart(2, "0")}.dae`);
}

async function loadStageCollision(stageId: string, manifest: StageManifest): Promise<StageResources> {
  const collisionFiles = [...(manifest.collision ?? [])].sort((a, b) => a.path.localeCompare(b.path));
  if (collisionFiles.length === 0) return { bounds: undefined, collision: undefined };

  try {
    const parsed = [];
    for (const file of collisionFiles) {
      const response = await fetch(`/stages/${stageId}/${file.path}`);
      if (!response.ok) continue;
      parsed.push({
        path: file.path,
        layerIndex: layerIndexFromCollisionPath(file.path),
        grid: hitBin.parseStageHitGrid(await response.arrayBuffer()),
      });
    }
    const first = parsed[0]?.grid;
    if (!first) return { bounds: undefined, collision: undefined };

    const triangles: StageCollisionTriangle[] = [];
    const mergedCells = Array.from({ length: first.header.gridCells.total }, (_, index) => ({
      index,
      triangleIndices: [] as number[],
    }));
    let canMergeCells = true;

    for (const entry of parsed) {
      const base = triangles.length;
      for (const tri of entry.grid.triangles) {
        triangles.push({
          index: triangles.length,
          layerIndex: entry.layerIndex,
          marker: tri.marker,
          vertices: tri.vertices,
          normal: tri.normal,
          planeD: tri.planeD,
          bounds2d: tri.bounds2d,
        });
      }

      if (!sameHitGridHeader(first, entry.grid)) {
        canMergeCells = false;
        continue;
      }
      for (const cell of entry.grid.cells) {
        const target = mergedCells[cell.index];
        if (!target) continue;
        target.triangleIndices.push(...cell.recordIndices.map((recordIndex) => base + recordIndex));
      }
    }

    return {
      bounds: hitBin.stageBoundsFromHitGrid(first),
      collision: {
        triangles,
        ...(canMergeCells
          ? {
              grid: {
                origin: first.header.origin,
                cellSize: first.header.cellSize,
                gridCells: first.header.gridCells,
                cells: mergedCells,
              },
            }
          : {}),
      },
    };
  } catch (error) {
    console.warn(`Failed to parse stage collision for ${stageId}`, error);
    return { bounds: undefined, collision: undefined };
  }
}

function layerIndexFromCollisionPath(path: string): number | null {
  const match = /hit[0-9a-f]{2}([0-2])\.bin$/i.exec(path);
  return match ? Number(match[1]) : null;
}

function sameHitGridHeader(a: ReturnType<typeof hitBin.parseStageHitGrid>, b: ReturnType<typeof hitBin.parseStageHitGrid>): boolean {
  return (
    a.header.cellSize.x === b.header.cellSize.x &&
    a.header.cellSize.z === b.header.cellSize.z &&
    a.header.gridCells.x === b.header.gridCells.x &&
    a.header.gridCells.z === b.header.gridCells.z &&
    a.header.origin.x === b.header.origin.x &&
    a.header.origin.z === b.header.origin.z
  );
}

async function loadStage(stageId: string): Promise<StageResources> {
  if (loadedStageId === stageId) return loadedStageResources;
  stageRoot.clear();
  const [manifest, renderState] = await Promise.all([
    fetch(`/stages/${stageId}/manifest.json`).then((r) => r.json() as Promise<StageManifest>),
    fetch(`/stages/${stageId}/render-state.json`)
      .then((r) => (r.ok ? (r.json() as Promise<StageRenderState>) : null))
      .catch(() => null),
  ]);
  applyStageRenderState(renderState);
  const resources = await loadStageCollision(stageId, manifest);
  const loader = new ColladaLoader();
  const urls = stageModelPaths(manifest).map((path) => `/stages/${stageId}/${path}`);
  const results = await Promise.allSettled(urls.map((u) => loader.loadAsync(u)));
  let loaded = 0;
  for (const result of results) {
    if (result.status !== "fulfilled") continue;
    const model = result.value.scene;
    model.traverse((object) => {
      if (object instanceof THREE.Mesh || object instanceof THREE.SkinnedMesh) {
        object.frustumCulled = false;
        const materials = Array.isArray(object.material) ? object.material : [object.material];
        for (const material of materials) {
          material.side = THREE.DoubleSide;
          if ("metalness" in material) (material as THREE.MeshStandardMaterial).metalness = 0;
        }
      }
    });
    stageRoot.add(model);
    loaded += 1;
  }
  if (loaded === 0) throw new Error(`No exported stage pieces loaded for ${stageId}`);
  loadedStageId = stageId;
  loadedStageResources = resources;
  return loadedStageResources;
}

async function loadInitialAssets(): Promise<void> {
  const manifest = await fetch("/models/library/manifest.json")
    .then((r) => r.json() as Promise<ModelManifestEntry[]>)
    .catch(() => [] as ModelManifestEntry[]);
  modelManifest = manifest;
  for (const e of manifest) LIBRARY_IDS.add(e.id);
  LIBRARY_IDS.add(DEFAULT_LEAD);
  await loadStage(DEFAULT_ARENA_STAGE);
}

// ------------------------------------------------------------------------------------------
// Netcode hooks (preserved, dormant). Multiplayer is wired next; do not delete.
// ------------------------------------------------------------------------------------------

let ws: WebSocket | null = null;
function closeSocket(): void {
  ws?.close();
  ws = null;
}
void closeSocket; // referenced so the dormant hook isn't tree-shaken/flagged.

// ------------------------------------------------------------------------------------------
// Audio
// ------------------------------------------------------------------------------------------

let audioManagerPromise: Promise<GotchaAudioManager | null> | null = null;
let activeBgmKey: string | null = null;
let pendingBgmKey: string | null = null;

function initAudio(): Promise<GotchaAudioManager | null> {
  if (!audioManagerPromise) {
    audioManagerPromise = createAudioManager().catch(() => null);
  }
  return audioManagerPromise;
}

function queueBgm(key: string): void {
  pendingBgmKey = key;
  void playPendingBgm();
}

async function playPendingBgm(): Promise<void> {
  const key = pendingBgmKey;
  if (!key) return;
  if (key === activeBgmKey) {
    pendingBgmKey = null;
    return;
  }
  const audio = await initAudio();
  if (!audio) return;
  try {
    await audio.playBgm(key);
    activeBgmKey = key;
    if (pendingBgmKey === key) pendingBgmKey = null;
  } catch {
    // Browsers reject autoplay before the first user gesture. Keep pending and
    // retry from the next key/click/touch event.
  }
}

function playSfx(key: string): void {
  void initAudio().then((audio) => {
    if (!audio) return;
    void audio.playSfx(key).catch(() => undefined);
  });
}

function playConfirmSfx(): void {
  playSfx(AUDIO_CUES.confirm);
}

function playBackSfx(): void {
  playSfx(AUDIO_CUES.back);
}

function playEditSfx(): void {
  playSfx(AUDIO_CUES.edit);
}

// ------------------------------------------------------------------------------------------
// Input
// ------------------------------------------------------------------------------------------

const keys = new Set<string>();
window.addEventListener("keydown", (e) => {
  if (isTextInputTarget(e.target)) return;
  void playPendingBgm();
  // Tab would move focus; capture it for switch-lock during battle.
  if (e.code === "Tab" && flow.screen === "battle") e.preventDefault();
  keys.add(e.code);
});
window.addEventListener("keyup", (e) => keys.delete(e.code));
window.addEventListener("pointerdown", () => {
  void playPendingBgm();
});

function isTextInputTarget(target: EventTarget | null): boolean {
  return (
    target instanceof HTMLInputElement ||
    target instanceof HTMLSelectElement ||
    target instanceof HTMLTextAreaElement
  );
}

function activeGamepad(): Gamepad | null {
  return navigator.getGamepads?.().find((g) => g?.connected) ?? null;
}

// ------------------------------------------------------------------------------------------
// Challenge flow state machine
// ------------------------------------------------------------------------------------------

type Screen =
  | "menu"
  | "difficulty"
  | "players"
  | "load-box"
  | "select-force"
  | "force"
  | "briefing"
  | "battle"
  | "results"
  | "loading";

interface Flow {
  screen: Screen;
  budget: number;
  playerCount: number;
  selectedForceSlot: number;
  forceSlots: ForceSlot[];
  run: ChallengeRun | null;
}

const flow: Flow = {
  screen: "loading",
  budget: 2000,
  playerCount: 1,
  selectedForceSlot: 0,
  forceSlots: DEFAULT_FORCE_SLOTS.map((slot) => ({ ...slot, borgIds: [...slot.borgIds] })),
  run: null,
};

// Active screen-component handle (so we can destroy it on transition).
let activeHandle: { destroy(): void } | null = null;

function mountScreen(build: (root: HTMLElement) => { destroy(): void }): void {
  activeHandle?.destroy();
  ui.replaceChildren();
  activeHandle = build(ui);
}

function showMenu(): void {
  flow.screen = "menu";
  queueBgm(AUDIO_CUES.menuBgm);
  mountScreen((root) =>
    createMainMenu(root, {
      initial: "challenge",
      onSelect: (mode) => {
        if (mode === "challenge") {
          playConfirmSfx();
          showDifficulty();
        }
      },
    }),
  );
}

function showDifficulty(): void {
  flow.screen = "difficulty";
  mountScreen((root) =>
    createSelectDifficulty(root, {
      onSelect: (budget) => {
        playConfirmSfx();
        flow.budget = budget;
        showPlayers();
      },
      onBack: () => {
        playBackSfx();
        showMenu();
      },
    }),
  );
}

function showPlayers(): void {
  flow.screen = "players";
  mountScreen((root) =>
    createSelectPlayers(root, {
      maxPlayers: 2,
      onSelect: (count) => {
        playConfirmSfx();
        flow.playerCount = count;
        showLoadBoxData();
      },
      onBack: () => {
        playBackSfx();
        showDifficulty();
      },
    }),
  );
}

function showLoadBoxData(): void {
  flow.screen = "load-box";
  mountScreen((root) =>
    createLoadBoxData(root, {
      onConfirm: () => {
        playConfirmSfx();
        showSelectForce();
      },
      onSkip: () => {
        playConfirmSfx();
        showSelectForce();
      },
      onBack: () => {
        playBackSfx();
        showPlayers();
      },
    }),
  );
}

function showSelectForce(): void {
  flow.screen = "select-force";
  mountScreen((root) =>
    createSelectForce(root, {
      catalog: FORCE_CATALOG,
      slots: flow.forceSlots,
      selectedSlot: flow.selectedForceSlot,
      limit: flow.budget,
      onSelectSlot: (slotIndex) => {
        playSfx(AUDIO_CUES.confirm);
        flow.selectedForceSlot = slotIndex;
      },
      onConfirm: (slot) => {
        playConfirmSfx();
        flow.selectedForceSlot = Math.max(0, flow.forceSlots.findIndex((candidate) => candidate.no === slot.no));
        startRun();
      },
      onEdit: (slot) => {
        playEditSfx();
        flow.selectedForceSlot = Math.max(0, flow.forceSlots.findIndex((candidate) => candidate.no === slot.no));
        showForceBuilder();
      },
      onBack: () => {
        playBackSfx();
        showLoadBoxData();
      },
    }),
  );
}

function showForceBuilder(): void {
  flow.screen = "force";
  mountScreen((root) =>
    createForceBuilder(root, {
      catalog: FORCE_CATALOG,
      limit: flow.budget,
      initialForce: selectedForce(),
      onConfirm: (force) => {
        playConfirmSfx();
        updateSelectedForceSlot(force);
        showSelectForce();
      },
      onQuit: () => {
        playBackSfx();
        showSelectForce();
      },
    }),
  );
}

function startRun(): void {
  const force = selectedForce();
  updateSelectedForceSlot(force);
  flow.run = createChallengeRun({
    budget: flow.budget,
    playerCount: flow.playerCount,
    playerForces: [{ player: 0, borgIds: force }],
    borgs: borgs as unknown as Parameters<typeof createChallengeRun>[0]["borgs"],
  });
  const battle = flow.run.getCurrentBattle();
  if (!battle) {
    showMenu();
    return;
  }
  showBattleIntro(battle);
}

function showBattleIntro(config: MissionBattleConfig): void {
  flow.screen = "briefing";
  queueBgm(AUDIO_CUES.menuBgm);
  mountScreen((root) =>
    createBattleIntro(root, {
      config,
      catalog: FORCE_CATALOG,
      onConfirm: () => {
        playConfirmSfx();
        void enterBattle(config);
      },
      onBack: () => {
        playBackSfx();
        showSelectForce();
      },
    }),
  );
}

// ------------------------------------------------------------------------------------------
// Battle
// ------------------------------------------------------------------------------------------

interface BattleSession {
  battle: Battle;
  config: MissionBattleConfig;
  hud: BattleHudHandle;
  localPlayerId: string;
  stageBounds: RectStageBounds;
  allyMax: number;
  enemyMax: number;
  // outcome telemetry accumulated across the battle
  startEnemyBorgCount: number;
  startPlayerBorgCount: number;
  paused: boolean;
  pauseHandle: { destroy(): void } | null;
  resolved: boolean;
}

let session: BattleSession | null = null;
let simAccumulator = 0;
const SIM_DT = 1 / 60;

async function enterBattle(config: MissionBattleConfig): Promise<void> {
  flow.screen = "loading";
  queueBgm(AUDIO_CUES.battleBgm);
  activeHandle?.destroy();
  activeHandle = null;
  ui.replaceChildren();

  const stageId = stageIdForArena(config.arena);
  const stageResources = await loadStage(stageId);
  const stageBounds = stageResources.bounds ?? fallbackStageBounds;

  const combatCfg = convertBattleConfig(config, stageId, stageBounds, stageResources.collision);
  const battle = createBattle(combatCfg);

  const localPlayerId = playerIdFor(0);

  // Energy maxima for the HUD meters (team 0 = ally, team 1 = enemy).
  const allyMax = battle.state.energy[0] ?? 0;
  const enemyMax = battle.state.energy[1] ?? 0;

  // Mount the HUD.
  const hud = createBattleHud(ui, { showBanner: false });

  // Count starting borgs per side (for results telemetry).
  const startEnemy = combatCfg.forces.filter((f) => f.team === 1).reduce((n, f) => n + f.borgIds.length, 0);
  const startPlayer = combatCfg.forces.filter((f) => f.team === 0).reduce((n, f) => n + f.borgIds.length, 0);

  session = {
    battle,
    config,
    hud,
    localPlayerId,
    stageBounds,
    allyMax,
    enemyMax,
    startEnemyBorgCount: startEnemy,
    startPlayerBorgCount: startPlayer,
    paused: false,
    pauseHandle: null,
    resolved: false,
  };
  simAccumulator = 0;
  battleScene.clear();
  flow.screen = "battle";
  // Prime the scene + HUD on frame 0.
  battleScene.sync(battle.state.borgs, battle.state.projectiles);
  updateHud();
}

function localActiveBorg(): BorgRuntime | null {
  if (!session) return null;
  const uid = session.battle.state.activeUidByPlayer[session.localPlayerId];
  if (!uid) return null;
  return session.battle.state.borgs.find((b) => b.uid === uid) ?? null;
}

function updateHud(): void {
  if (!session) return;
  const st = session.battle.state;
  const active = localActiveBorg();
  const ammoMax = 6;
  session.hud.update({
    allyEnergy: st.energy[0] ?? 0,
    allyMax: session.allyMax,
    enemyEnergy: st.energy[1] ?? 0,
    enemyMax: session.enemyMax,
    hp: active?.hp ?? 0,
    maxHp: active?.maxHp ?? 1,
    ammo: active?.ammo ?? 0,
    reload01: active ? clamp01((active.ammo ?? 0) / ammoMax) : 0,
    cooldown01: active ? (active.cooldowns?.["special"] ? clamp01(1 - active.cooldowns["special"] / 90) : 1) : 1,
    borgId: active?.borgId ?? DEFAULT_LEAD,
    lockOn: Boolean(active?.lockTarget),
    alert: (st.energy[0] ?? 0) > 0 && (st.energy[0] ?? 0) <= session.allyMax * 0.25,
  });
}

function clamp01(v: number): number {
  return v < 0 ? 0 : v > 1 ? 1 : v;
}

// Pause handling (Start/Esc).
let pausePressedLast = false;
function pollPauseToggle(): void {
  if (!session || session.resolved) return;
  const pad = activeGamepad();
  const startPressed = keys.has("Escape") || keys.has("Enter") || (pad?.buttons[9]?.pressed ?? false);
  if (startPressed && !pausePressedLast) {
    if (session.paused) resumeBattle();
    else pauseBattle();
  }
  pausePressedLast = startPressed;
}

function pauseBattle(): void {
  if (!session || session.paused) return;
  session.paused = true;
  session.pauseHandle = createPauseMenu(ui, {
    onResume: resumeBattle,
    onQuit: () => {
      session?.pauseHandle?.destroy();
      if (session) session.paused = false;
      endBattleToMenu();
    },
  });
}

function resumeBattle(): void {
  if (!session) return;
  session.pauseHandle?.destroy();
  session.pauseHandle = null;
  session.paused = false;
}

function endBattleToMenu(): void {
  teardownBattle();
  showMenu();
}

function teardownBattle(): void {
  session?.hud.destroy();
  session?.pauseHandle?.destroy();
  battleScene.clear();
  session = null;
}

// The sim advances on a wall-clock interval (NOT requestAnimationFrame) so a
// battle keeps progressing even when the tab is backgrounded (rAF is throttled
// to ~0 Hz while hidden). dt is clamped so returning from a long background gap
// fast-forwards a bounded number of frames instead of one giant spike.
function stepBattle(dt: number): void {
  if (!session || session.paused || session.resolved) return;
  const { battle } = session;

  simAccumulator += Math.min(dt, 0.25);
  // Fixed 60 Hz; collect local input once and apply for each sub-step.
  const inputs: Record<string, PlayerInput> = {};
  const active = localActiveBorg();
  inputs[session.localPlayerId] = active ? inputFromKeys(keys, activeGamepad()) : emptyInput();

  let steps = 0;
  while (simAccumulator >= SIM_DT && steps < 15) {
    battle.step(SIM_DT, inputs);
    simAccumulator -= SIM_DT;
    steps += 1;
    if (battle.state.result !== "ongoing") break;
  }

  battleScene.sync(battle.state.borgs, battle.state.projectiles);
  updateHud();

  if (battle.state.result !== "ongoing") resolveBattle();
}

function followCamera(): void {
  if (!session) return;
  const active = localActiveBorg();
  const target = active ? battleScene.positionOf(active.uid) : null;
  const focus = target ?? new THREE.Vector3(0, 80, 0);
  cameraFocus.set(focus.x, focus.y + 90, focus.z);
  controls.target.lerp(cameraFocus, 0.08);
  // Trail the camera behind the active borg.
  if (active) {
    cameraForward.set(Math.sin(active.rotY), 0, Math.cos(active.rotY));
    cameraGoal.set(
      focus.x - cameraForward.x * 700,
      focus.y + 420,
      focus.z - cameraForward.z * 700,
    );

    // Until the original gameplay camera collision path is traced, keep the
    // browser camera inside the exported arena shell instead of letting the
    // normal trailing point sit behind a wall/ceiling at spawn.
    const bounds = session.stageBounds;
    const centerX = (bounds.minX + bounds.maxX) * 0.5;
    const centerZ = (bounds.minZ + bounds.maxZ) * 0.5;
    const currentRadius = Math.hypot(focus.x - centerX, focus.z - centerZ);
    const goalRadius = Math.hypot(cameraGoal.x - centerX, cameraGoal.z - centerZ);
    const shellGuardRadius = Math.min(bounds.maxX - bounds.minX, bounds.maxZ - bounds.minZ) * 0.25;
    if (currentRadius > shellGuardRadius && goalRadius > currentRadius + 80) {
      cameraInward.set(centerX - focus.x, 0, centerZ - focus.z);
      if (cameraInward.lengthSq() < 0.0001) cameraInward.copy(cameraForward).multiplyScalar(-1);
      cameraInward.normalize();
      cameraGoal.set(focus.x + cameraInward.x * 1100, focus.y + 560, focus.z + cameraInward.z * 1100);
    }

    camera.position.lerp(cameraGoal, 0.08);
  }
}

function resolveBattle(): void {
  if (!session || session.resolved) return;
  session.resolved = true;
  const st = session.battle.state;
  const win = st.result === "win";

  // Derive results telemetry from the end state (the sim doesn't emit per-shot
  // telemetry, so attack/hit/dodge are estimated from energy deltas).
  const enemyRemaining = st.borgs.filter((b) => b.team === 1 && b.alive).length;
  const playerRemaining = st.borgs.filter((b) => b.team === 0 && b.alive).length;
  const enemyDefeated = Math.max(0, session.startEnemyBorgCount - enemyRemaining);
  const playerDefeated = Math.max(0, session.startPlayerBorgCount - playerRemaining);
  const costWon = session.enemyMax - (st.energy[1] ?? 0);
  const costLost = session.allyMax - (st.energy[0] ?? 0);

  const outcome: BattleOutcome = {
    win,
    attack: Math.round(costWon),
    hits: enemyDefeated,
    attempts: Math.max(1, enemyDefeated + 2),
    dodges: 0,
    incoming: 1,
    enemyBorgsDefeated: enemyDefeated,
    playerBorgsDefeated: playerDefeated,
    allyBorgsDefeated: 0,
    costWon,
    costLost,
  };
  const results = computeResults(outcome);

  showResults(win ? "win" : "lose", {
    attack: results.attack,
    hitRatio: results.hitRatio * 100,
    dodgeRatio: results.dodgeRatio * 100,
    enemyBorgsDefeated: results.enemyBorgsDefeated,
    enemyTotalCost: Math.round(costWon),
    playerBorgsDefeated: results.playerBorgsDefeated,
    playerTotalCost: Math.round(costLost),
    allyBorgsDefeated: results.allyBorgsDefeated,
    grandTotal: results.grandTotal,
  }, results);
}

function showResults(
  result: "win" | "lose",
  stats: Parameters<ReturnType<typeof createResults>["render"]>[1],
  battleResults: BattleResults,
): void {
  // Tear down HUD but keep the battle scene visible behind the results.
  session?.hud.destroy();
  session?.pauseHandle?.destroy();
  flow.screen = "results";

  const handle = createResults(ui, {
    onAdvance: () => {
      handle.destroy();
      advanceRun(battleResults);
    },
  });
  handle.render(result, stats);
  activeHandle = handle;
}

function advanceRun(lastResult: BattleResults): void {
  const run = flow.run;
  battleScene.clear();
  session = null;

  if (!run) {
    showMenu();
    return;
  }
  const progress = run.next(lastResult);
  if (progress.action === "advance" && progress.nextBattle) {
    showBattleIntro(progress.nextBattle);
  } else {
    // "complete" (won the whole run) or "title" (lost) -> back to menu.
    showMenu();
  }
}

// ------------------------------------------------------------------------------------------
// Main loop
// ------------------------------------------------------------------------------------------

// Render loop (requestAnimationFrame): drives animation mixers, the follow
// camera, and the WebGL render. Sim stepping is handled by the interval below.
const renderClock = new THREE.Clock();
function tick(): void {
  const dt = Math.min(renderClock.getDelta(), 0.05);
  if (flow.screen === "battle" || flow.screen === "results") {
    battleScene.update(dt);
    if (flow.screen === "battle") followCamera();
  }
  controls.update();
  renderer.render(scene, camera);
  requestAnimationFrame(tick);
}

// Sim loop (setInterval): fixed-cadence wall-clock stepping, runs even when the
// tab is hidden. ~60 Hz target.
let lastSimTime = performance.now();
setInterval(() => {
  const now = performance.now();
  const dt = (now - lastSimTime) / 1000;
  lastSimTime = now;
  if (flow.screen === "battle") {
    pollPauseToggle();
    stepBattle(dt);
  }
}, 1000 / 60);

window.addEventListener("resize", () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});

// ------------------------------------------------------------------------------------------
// Boot
// ------------------------------------------------------------------------------------------

ensureStyles();
showLoadingMessage("Loading extracted stage + model assets…");

void loadInitialAssets()
  .then(() => {
    showMenu();
  })
  .catch((error: unknown) => {
    showLoadingMessage(`Asset load failed: ${error instanceof Error ? error.message : String(error)}`);
  });

tick();

function showLoadingMessage(text: string): void {
  flow.screen = "loading";
  activeHandle?.destroy();
  activeHandle = null;
  ui.replaceChildren();
  const box = document.createElement("div");
  box.style.cssText =
    "position:absolute;left:50%;top:50%;transform:translate(-50%,-50%);color:#bfeeff;font:600 16px 'Trebuchet MS',system-ui,sans-serif;text-align:center;text-shadow:0 1px 3px #000;";
  box.textContent = text;
  ui.appendChild(box);
}

// Expose a tiny debug handle for live verification in the preview.
(window as unknown as { __gf: unknown }).__gf = {
  flow,
  keys,
  get input() {
    return inputFromKeys(keys, activeGamepad());
  },
  get session() {
    return session;
  },
  startChallenge: () => showDifficulty(),
  renderNow: () => {
    renderer.render(scene, camera);
    return canvas.toDataURL("image/png");
  },
  forceBattle: (force: string[] = [DEFAULT_LEAD]) => {
    flow.budget = 2000;
    flow.playerCount = 1;
    updateSelectedForceSlot(force);
    startRun();
  },
};
