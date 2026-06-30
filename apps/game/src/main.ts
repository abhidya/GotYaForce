import * as THREE from "three";
import { ColladaLoader } from "three/examples/jsm/loaders/ColladaLoader.js";
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js";
import { clone } from "three/examples/jsm/utils/SkeletonUtils.js";
import { forceEnergy } from "@gf/combat";
import { resolveAdventureStage } from "@gf/missions";
import type { BorgStats } from "@gf/combat";
import type { AdventureBorgData, AdventureStagesData, ResolvedAdventureStage } from "@gf/missions";
import borgs from "../../../packages/assets/data/borgs.json";
import stages from "../../../packages/assets/data/stages.json";

type Screen = "title" | "lobby" | "force" | "arena";
type NetStatus = "offline" | "connecting" | "online";

type BorgEntry = {
  id: string;
  name: string;
  energy: number;
  speed?: number;
  tribe?: string;
  type?: string;
};

type ModelManifestEntry = {
  id: string;
  name: string;
  tribe: string;
  energy: number;
  dae: string;
};

type StageEntry = {
  stage: number | string;
  name: string;
  arena: string;
  enemies: string[];
  boss: string | null;
  confidence: string;
};

type StageManifest = {
  id: string;
  modelCount: number;
  renderStatus?: string;
  models: Array<{ path: string; bytes: number }>;
  collision?: Array<{ path: string; bytes: number }>;
  setArcs?: Array<{ path: string; bytes: number }>;
};

type StageRenderState = {
  camera?: {
    fovDegrees?: number;
    near?: number;
    far?: number;
  };
  fog?: {
    colorRgbHex?: string;
    start?: number;
    end?: number;
  };
  lights?: {
    ambient?: { colorRgbHex?: string; intensity?: number };
    directional?: { colorRgbHex?: string; intensity?: number; position?: [number, number, number] };
  };
};

type NetPlayer = {
  id: string;
  name: string;
  ready: boolean;
  x: number;
  y: number;
  z: number;
  ry: number;
  borg: string;
  anim?: string;
};

type RemoteActor = {
  rig: THREE.Group;
  mixer: THREE.AnimationMixer;
  action: THREE.AnimationAction | null;
  borg: string;
};

type NetStage = {
  id: string;
  name: string;
};

type ServerMessage =
  | { type: "welcome"; playerId: string; roomCode: string; stage?: NetStage; players: NetPlayer[] }
  | { type: "state"; stage?: NetStage; players: NetPlayer[] }
  | { type: "error"; message: string };

type ClientMessage =
  | { type: "create"; name: string; borg: string; stageId: string }
  | { type: "join"; roomCode: string; name: string; borg: string }
  | { type: "ready"; ready: boolean; force: string[]; energy: number }
  | { type: "pose"; x: number; y: number; z: number; ry: number; anim: string };

type BakedClip = {
  name?: string;
  frameCount: number;
  fps?: number;
  bones: Array<{ i: number; pos?: number[]; rot?: number[]; scl?: number[] }>;
};

type ActionName = "idle" | "move" | "boost" | "jump" | "fly" | "attack" | "hit" | "down";
type InputState = { x: number; y: number; turn: number };

const GF_RED = "pl0615";
const DEFAULT_ENERGY = 1000;
const BROWSER_UNITS_PER_SPEED_POINT = 66; // Unit conversion placeholder; relative speed comes from extracted borg stats.
const DEFAULT_STAGE_ID = "st00";
const ACTION_NAMES = new Set<ActionName>(["idle", "move", "boost", "jump", "fly", "attack", "hit", "down"]);
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
const LOOPING_ACTIONS = new Set<ActionName>(["idle", "move"]);
const BORG_ACTION_FILES: Record<string, Partial<Record<ActionName, string>>> = {
  [GF_RED]: {
    idle: "/models/pl0615/anim_b00_idle.json",
    move: "/models/pl0615/anim_b00_move.json",
    boost: "/models/pl0615/anim_b00_boost_forward.json",
    jump: "/models/pl0615/anim_b00_jump_takeoff_candidate.json",
    fly: "/models/pl0615/anim_b00_fly_transition_candidate.json",
    attack: "/models/pl0615/anim_b00_attack_arm_candidate.json",
    hit: "/models/pl0615/anim_b00_hit_flinch_candidate.json",
    down: "/models/pl0615/anim_b00_down_candidate.json",
  },
  pl0109: {
    idle: "/models/pl0109/anim_b00_s00_candidate.json",
  },
};
const ANIMATED_BORGS = new Set(Object.keys(BORG_ACTION_FILES));
const KEY_ACTIONS: Partial<Record<string, ActionName>> = {
  Space: "jump",
  ShiftLeft: "boost",
  ShiftRight: "boost",
  KeyF: "fly",
  KeyJ: "attack",
  KeyH: "hit",
  KeyK: "down",
};
const GAMEPAD_BUTTON_ACTIONS = new Map<number, ActionName>([
  [0, "jump"],
  [1, "boost"],
  [2, "attack"],
  [3, "fly"],
  [4, "hit"],
  [5, "attack"],
  [7, "attack"],
  [8, "down"],
]);

const catalog = (borgs as { borgs: BorgEntry[] }).borgs.filter((borg) => borg.id && borg.name);
const byId = new Map(catalog.map((borg) => [borg.id, borg]));

const uiElement = document.getElementById("ui");
const canvas = document.getElementById("app") as HTMLCanvasElement;
if (!uiElement) throw new Error("Missing #ui");
const ui = uiElement;

let screen: Screen = "arena";
let netStatus: NetStatus = "offline";
let playerName = `Player ${Math.floor(100 + Math.random() * 900)}`;
let roomCode = "";
let playerId = "";
let selectedBudget = DEFAULT_ENERGY;
let selectedForce = [GF_RED];
let selectedStageIndex = 0;
let ws: WebSocket | null = null;
let roster: NetPlayer[] = [];
let errorText = "";
let controllerName = "";
let modelManifest: ModelManifestEntry[] = [];
let roomStage: NetStage | null = null;

const renderer = new THREE.WebGLRenderer({ canvas, antialias: true });
renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
renderer.setSize(window.innerWidth, window.innerHeight);
renderer.outputColorSpace = THREE.SRGBColorSpace;

const scene = new THREE.Scene();
scene.background = new THREE.Color(DEFAULT_RENDER_STATE.fogColor);
scene.fog = new THREE.Fog(DEFAULT_RENDER_STATE.fogColor, DEFAULT_RENDER_STATE.fogNear, DEFAULT_RENDER_STATE.fogFar);

const camera = new THREE.PerspectiveCamera(DEFAULT_RENDER_STATE.fov, window.innerWidth / window.innerHeight, DEFAULT_RENDER_STATE.near, DEFAULT_RENDER_STATE.far);
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

const localRig = new THREE.Group();
scene.add(localRig);

let sourceModel: THREE.Object3D | null = null;
let localModel: THREE.Object3D | null = null;
let localMixer: THREE.AnimationMixer | null = null;
const borgClips = new Map<string, Map<ActionName, THREE.AnimationClip>>();
const sourceModels = new Map<string, THREE.Object3D>();
let currentAction: THREE.AnimationAction | null = null;
let currentActionName: ActionName | null = null;
let queuedAction: ActionName | null = null;
let oneShotAction: ActionName | null = null;
let oneShotTimeRemaining = 0;
let currentBorgId = GF_RED;
const remotes = new Map<string, RemoteActor>();
let loadedStagePieceCount = 0;
let expectedStagePieceCount = 0;
let assetStatus = "Loading extracted stage assets";
let previousGamepadButtons = new Set<number>();

const keys = new Set<string>();
window.addEventListener("keydown", (event) => {
  if (isTextInputTarget(event.target)) return;
  keys.add(event.code);
  if (event.repeat) return;
  const action = KEY_ACTIONS[event.code];
  if (action) {
    event.preventDefault();
    queueAction(action);
  }
});
window.addEventListener("keyup", (event) => keys.delete(event.code));
window.addEventListener("gamepadconnected", (event) => {
  controllerName = event.gamepad.id;
  renderUi();
});
window.addEventListener("gamepaddisconnected", () => {
  controllerName = "";
  renderUi();
});

function energyUsed(): number {
  try {
    return forceEnergy(selectedForce, catalog as BorgStats[]);
  } catch {
    return selectedForce.reduce((sum, id) => sum + (byId.get(id)?.energy ?? 0), 0);
  }
}

function canReady(): boolean {
  return selectedForce.length > 0 && energyUsed() <= selectedBudget && netStatus === "online";
}

function stageList(): StageEntry[] {
  return (stages as { stages: StageEntry[] }).stages;
}

function selectedStage(): StageEntry {
  return stageList()[selectedStageIndex] ?? stageList()[0]!;
}

function resolvedSelectedStage(): ResolvedAdventureStage | null {
  return resolveAdventureStage(
    stages as AdventureStagesData,
    borgs as AdventureBorgData,
    selectedStage().stage,
  );
}

function currentBorgStats(): BorgEntry | undefined {
  return byId.get(currentBorgId);
}

function availableForceBorgs(): BorgEntry[] {
  const exportedIds = new Set(modelManifest.map((entry) => entry.id));
  return catalog
    .filter((borg) => exportedIds.has(borg.id) && ANIMATED_BORGS.has(borg.id))
    .sort((a, b) => a.energy - b.energy || a.name.localeCompare(b.name));
}

function send(message: ClientMessage): void {
  if (ws?.readyState === WebSocket.OPEN) ws.send(JSON.stringify(message));
}

function connect(createRoom: boolean): void {
  closeSocket();
  netStatus = "connecting";
  errorText = "";
  renderUi();
  const url = `${location.protocol === "https:" ? "wss" : "ws"}://${location.hostname}:5174`;
  ws = new WebSocket(url);
  ws.addEventListener("open", () => {
    const borg = selectedForce[0] ?? GF_RED;
    send(createRoom ? { type: "create", name: playerName, borg, stageId: String(selectedStage().stage) } : { type: "join", roomCode, name: playerName, borg });
  });
  ws.addEventListener("message", (event) => {
    const msg = JSON.parse(String(event.data)) as ServerMessage;
    if (msg.type === "welcome") {
      playerId = msg.playerId;
      roomCode = msg.roomCode;
      roster = msg.players;
      roomStage = msg.stage ?? null;
      netStatus = "online";
      screen = "force";
    } else if (msg.type === "state") {
      roster = msg.players;
      roomStage = msg.stage ?? roomStage;
      void syncRemotePlayers();
    } else if (msg.type === "error") {
      errorText = msg.message;
    }
    renderUi();
  });
  ws.addEventListener("close", () => {
    netStatus = "offline";
    roster = [];
    renderUi();
  });
  ws.addEventListener("error", () => {
    errorText = "Start the Adventure server on port 5174, then try again.";
    netStatus = "offline";
    renderUi();
  });
}

function closeSocket(): void {
  ws?.close();
  ws = null;
}

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

function setClip(borgId: string, name: ActionName, clip: THREE.AnimationClip): void {
  let clips = borgClips.get(borgId);
  if (!clips) {
    clips = new Map<ActionName, THREE.AnimationClip>();
    borgClips.set(borgId, clips);
  }
  clips.set(name, clip);
}

function getClip(borgId: string, name: ActionName): THREE.AnimationClip | undefined {
  return borgClips.get(borgId)?.get(name);
}

function hasClip(borgId: string, name: ActionName): boolean {
  return Boolean(getClip(borgId, name));
}

function fallbackAction(borgId: string, requested: ActionName): ActionName {
  if (hasClip(borgId, requested)) return requested;
  return hasClip(borgId, "idle") ? "idle" : requested;
}

function parseHexColor(value: string | undefined, fallback: number): number {
  if (!value || !/^#[0-9a-f]{6}$/i.test(value)) return fallback;
  return Number.parseInt(value.slice(1), 16);
}

function applyStageRenderState(renderState: StageRenderState | null): void {
  const fogColor = parseHexColor(renderState?.fog?.colorRgbHex, DEFAULT_RENDER_STATE.fogColor);
  const fogNear = renderState?.fog?.start ?? DEFAULT_RENDER_STATE.fogNear;
  const fogFar = renderState?.fog?.end ?? DEFAULT_RENDER_STATE.fogFar;
  scene.background = new THREE.Color(fogColor);
  scene.fog = new THREE.Fog(fogColor, fogNear, fogFar);

  camera.fov = renderState?.camera?.fovDegrees ?? DEFAULT_RENDER_STATE.fov;
  camera.near = renderState?.camera?.near ?? DEFAULT_RENDER_STATE.near;
  camera.far = renderState?.camera?.far ?? DEFAULT_RENDER_STATE.far;
  camera.updateProjectionMatrix();

  stageAmbient.color.setHex(parseHexColor(renderState?.lights?.ambient?.colorRgbHex, DEFAULT_RENDER_STATE.ambientColor));
  stageAmbient.intensity = renderState?.lights?.ambient?.intensity ?? 1;

  stageLight.color.setHex(parseHexColor(renderState?.lights?.directional?.colorRgbHex, DEFAULT_RENDER_STATE.lightColor));
  stageLight.intensity = renderState?.lights?.directional?.intensity ?? 1;
  const lightPosition = renderState?.lights?.directional?.position;
  if (lightPosition) stageLight.position.set(lightPosition[0], lightPosition[1], lightPosition[2]);
  else stageLight.position.copy(DEFAULT_RENDER_STATE.lightPosition);
}

async function loadStageRenderState(stageId: string): Promise<StageRenderState | null> {
  const response = await fetch(`/stages/${stageId}/render-state.json`);
  if (!response.ok) return null;
  return response.json() as Promise<StageRenderState>;
}

async function loadInitialAssets(): Promise<void> {
  const [manifest, actionEntries] = await Promise.all([
    fetch("/models/library/manifest.json").then((r) => r.json() as Promise<ModelManifestEntry[]>),
    Promise.all(
      Object.entries(BORG_ACTION_FILES).flatMap(([borgId, files]) =>
        Object.entries(files).map(async ([name, url]) => {
          const json = await fetch(url).then((r) => r.json() as Promise<BakedClip>);
          return [borgId, name as ActionName, buildClip(json)] as const;
        }),
      ),
    ),
  ]);

  modelManifest = manifest;
  for (const [borgId, name, clip] of actionEntries) setClip(borgId, name, clip);
  await loadStage(DEFAULT_STAGE_ID);
  await mountLocalModel(selectedForce[0] ?? GF_RED);
  renderUi();
}

async function loadStage(stageId: string): Promise<void> {
  stageRoot.clear();
  loadedStagePieceCount = 0;
  expectedStagePieceCount = 0;
  assetStatus = `Loading ${stageId}_mdl.arc export`;
  const [manifest, renderState] = await Promise.all([
    fetch(`/stages/${stageId}/manifest.json`).then((r) => r.json() as Promise<StageManifest>),
    loadStageRenderState(stageId).catch(() => null),
  ]);
  applyStageRenderState(renderState);
  expectedStagePieceCount = manifest.models.length;

  const loader = new ColladaLoader();
  const urls = manifest.models.map((model) => `/stages/${stageId}/${model.path}`);
  const results = await Promise.allSettled(urls.map((url) => loader.loadAsync(url)));

  for (const result of results) {
    if (result.status !== "fulfilled") continue;
    const model = result.value.scene;
    normalizeStagePiece(model);
    stageRoot.add(model);
    loadedStagePieceCount += 1;
  }

  if (loadedStagePieceCount === 0) {
    throw new Error(`No exported stage pieces loaded for ${stageId}`);
  }

  frameStageAndPlayer();
  assetStatus = `${stageId}_mdl.arc loaded from exported DAE pieces`;
}

function normalizeStagePiece(model: THREE.Object3D): void {
  model.traverse((object) => {
    if (object instanceof THREE.Mesh || object instanceof THREE.SkinnedMesh) {
      object.frustumCulled = false;
      const materials = Array.isArray(object.material) ? object.material : [object.material];
      for (const material of materials) {
        material.side = THREE.DoubleSide;
        if ("metalness" in material) material.metalness = 0;
      }
    }
  });
}

function frameStageAndPlayer(): void {
  localRig.position.set(0, 0, 0);
  controls.target.set(0, 90, 0);
  camera.position.set(950, 520, 1320);
  camera.lookAt(controls.target);
  camera.updateProjectionMatrix();
}

async function loadBorgSource(id: string): Promise<THREE.Object3D> {
  const cached = sourceModels.get(id);
  if (cached) return cached;
  const manifestEntry = modelManifest.find((entry) => entry.id === id);
  const url = id === GF_RED ? "/models/pl0615/model_00.dae" : `/models/library/${id}/${manifestEntry?.dae ?? `${id}.dae`}`;
  const collada = await new ColladaLoader().loadAsync(url);
  normalizeModel(collada.scene);
  sourceModels.set(id, collada.scene);
  return collada.scene;
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
        if ("metalness" in material) material.metalness = 0;
      }
    }
  });
}

async function mountLocalModel(id: string): Promise<void> {
  if (!ANIMATED_BORGS.has(id)) {
    throw new Error(`${id} blocked: model has no verified MOT animation mapping yet`);
  }
  sourceModel = await loadBorgSource(id);
  if (localModel) localRig.remove(localModel);
  localModel = clone(sourceModel);
  localRig.add(localModel);
  localMixer = new THREE.AnimationMixer(localModel);
  currentBorgId = id;
  currentAction = null;
  currentActionName = null;
  oneShotAction = null;
  oneShotTimeRemaining = 0;
  playLocal("idle");
}

function playLocal(name: ActionName): void {
  if (!localMixer) return;
  const actionName = fallbackAction(currentBorgId, name);
  const clip = getClip(currentBorgId, actionName);
  if (!clip) return;
  const next = localMixer.clipAction(clip);
  if (currentAction === next && LOOPING_ACTIONS.has(actionName)) return;
  const looping = LOOPING_ACTIONS.has(actionName);
  next
    .reset()
    .setLoop(looping ? THREE.LoopRepeat : THREE.LoopOnce, looping ? Infinity : 1)
    .play();
  next.clampWhenFinished = !looping;
  if (currentAction && currentAction !== next) currentAction.crossFadeTo(next, 0.18, false);
  currentAction = next;
  currentActionName = actionName;
  oneShotAction = looping ? null : actionName;
  oneShotTimeRemaining = looping ? 0 : clip.duration;
}

async function syncRemotePlayers(): Promise<void> {
  if (!sourceModel) return;
  const liveIds = new Set(roster.filter((p) => p.id !== playerId).map((p) => p.id));
  for (const [id, remote] of remotes) {
    if (!liveIds.has(id)) {
      scene.remove(remote.rig);
      remotes.delete(id);
    }
  }
  for (const player of roster) {
    if (player.id === playerId) continue;
    let remote = remotes.get(player.id);
    if (!remote || remote.borg !== player.borg) {
      if (remote) scene.remove(remote.rig);
      const rig = new THREE.Group();
      const remoteSource = await loadBorgSource(player.borg);
      rig.add(clone(remoteSource));
      scene.add(rig);
      const mixer = new THREE.AnimationMixer(rig);
      const idle = getClip(player.borg, "idle");
      const action = idle ? mixer.clipAction(idle) : null;
      action?.play();
      remote = { rig, mixer, action, borg: player.borg };
      remotes.set(player.id, remote);
    }
    remote.rig.position.set(player.x, player.y, player.z);
    remote.rig.rotation.y = player.ry;
    if (ANIMATED_BORGS.has(player.borg)) playRemote(remote, toActionName(player.anim, "idle"));
  }
}

function playRemote(remote: RemoteActor, name: ActionName): void {
  const actionName = fallbackAction(remote.borg, name);
  const clip = getClip(remote.borg, actionName);
  if (!clip) return;
  const next = remote.mixer.clipAction(clip);
  if (remote.action === next) return;
  const looping = LOOPING_ACTIONS.has(actionName);
  next
    .reset()
    .setLoop(looping ? THREE.LoopRepeat : THREE.LoopOnce, looping ? Infinity : 1)
    .play();
  next.clampWhenFinished = !looping;
  remote.action?.crossFadeTo(next, 0.18, false);
  remote.action = next;
}

function toActionName(value: string | undefined, fallback: ActionName): ActionName {
  return value && ACTION_NAMES.has(value as ActionName) ? (value as ActionName) : fallback;
}

function renderUi(): void {
  const roomLabel = roomCode ? `Room ${roomCode}` : "No room";
  const stage = selectedStage();
  const resolvedStage = resolvedSelectedStage();
  const displayStage = roomStage ?? { id: String(stage.stage), name: stage.name };
  const forceBorgs = availableForceBorgs();
  const rosterHtml = roster.length
    ? roster.map((p) => `<li>${escapeHtml(p.name)} <span>${p.ready ? "READY" : "WAIT"}</span></li>`).join("")
    : "<li>Waiting for players</li>";
  const modeRows = [
    ["Adventure", true],
    ["Versus", false],
    ["Training", false],
    ["Collection", false],
    ["Options", false],
  ]
    .map(([label, enabled]) => `<button class="mode ${enabled ? "enabled" : "locked"}" ${enabled ? 'data-action="adventure"' : "disabled"}>${label}</button>`)
    .join("");

  ui.innerHTML = `
    <style>
      #ui { pointer-events: none; }
      .panel { pointer-events: auto; position:absolute; background: linear-gradient(180deg, rgba(5,18,29,.94), rgba(3,8,15,.88)); border:1px solid #4cc7ff; box-shadow:0 0 0 2px #0b2a42, 0 18px 45px rgba(0,0,0,.45); }
      .title { left:5vw; top:8vh; width:min(460px, 90vw); padding:22px; }
      .brand { color:#ffef61; font-size:42px; line-height:.9; font-weight:900; text-transform:uppercase; text-shadow:3px 3px 0 #0d2335, 0 0 16px #1bbcff; }
      .subtitle { color:#9fe5ff; margin-top:9px; font-size:14px; text-transform:uppercase; }
      .modes { display:grid; gap:8px; margin-top:22px; }
      .mode, .primary, .small { border:1px solid #85e8ff; color:#effbff; background:#123c59; padding:10px 12px; text-align:left; cursor:pointer; }
      .mode.enabled:focus, .mode.enabled:hover, .primary:hover { background:#e2372f; color:white; border-color:#ffd95b; }
      .mode.locked { opacity:.38; cursor:not-allowed; }
      .lobby { right:4vw; top:8vh; width:min(390px, 90vw); padding:18px; }
      .field { display:grid; gap:6px; margin:10px 0; color:#bfeeff; font-size:12px; text-transform:uppercase; }
      input, select { background:#06131e; color:#fff; border:1px solid #3c9ac6; padding:9px; }
      .row { display:flex; gap:8px; flex-wrap:wrap; }
      .primary { text-align:center; font-weight:800; }
      .force { left:4vw; bottom:5vh; width:min(620px, 92vw); padding:16px; }
      .borgs { display:grid; grid-template-columns:repeat(auto-fit, minmax(150px,1fr)); gap:8px; margin-top:10px; }
      .borg { border:1px solid #2d7ea9; background:#071827; color:#dff7ff; padding:10px; text-align:left; cursor:pointer; min-height:70px; }
      .borg.selected { border-color:#ffd95b; background:#5f1e26; }
      .hud { position:absolute; left:16px; top:14px; padding:10px 12px; min-width:230px; }
      h2, h3, p, ul { margin:0; }
      ul { list-style:none; padding:0; display:grid; gap:7px; margin-top:10px; }
      li { display:flex; justify-content:space-between; gap:18px; color:#d9f5ff; }
      .fine { color:#9bbbd0; font-size:12px; margin-top:8px; }
      .error { color:#ff8f86; margin-top:10px; min-height:18px; }
      .badge { color:#ffd95b; font-weight:800; }
    </style>
    ${screen === "arena" ? `<div class="panel hud"><b>Adventure ${escapeHtml(displayStage.id)}</b><div>${escapeHtml(displayStage.name)}</div><div>World: ${escapeHtml(assetStatus)} (${loadedStagePieceCount}/${expectedStagePieceCount || loadedStagePieceCount})</div><div>Actor: ${escapeHtml(currentBorgStats()?.name ?? currentBorgId)} · MOT action candidates</div><div>${controllerName ? `Controller: ${escapeHtml(controllerName)}` : "Keyboard active"}</div><div class="fine">No CPU actors spawned until their model, MOT action set, and AI path are verified.</div></div>` : ""}
    ${screen !== "arena" ? `<section class="panel title"><div class="brand">Gotcha Force</div><div class="subtitle">Adventure</div><div class="modes">${modeRows}</div><p class="fine">Only Adventure is enabled in this build.</p></section>` : ""}
    ${screen === "lobby" || screen === "force" ? `
      <section class="panel lobby">
        <h2>${escapeHtml(roomLabel)}</h2>
        <p class="fine">1-4 players. Host creates a room; friends join by code.</p>
        <label class="field">Adventure stage
          <select data-field="stage">${stageList().map((item, index) => `<option value="${index}" ${index === selectedStageIndex ? "selected" : ""}>${escapeHtml(String(item.stage))} - ${escapeHtml(item.name)}</option>`).join("")}</select>
        </label>
        <p class="fine">${escapeHtml(stage.arena)} · ${escapeHtml(stage.boss ?? "enemy force")}</p>
        <p class="fine">Enemy force: ${resolvedStage?.enemyForceEnergy ?? 0} GF · ${resolvedStage?.enemies.map((enemy) => enemy.id ? `${enemy.name} (${enemy.energy ?? "?"})` : `${enemy.name} (?)`).join(", ") ?? "unknown"}</p>
        <label class="field">Name <input data-field="name" value="${escapeAttr(playerName)}" /></label>
        <label class="field">Room code <input data-field="room" value="${escapeAttr(roomCode)}" maxlength="4" /></label>
        <div class="row"><button class="primary" data-action="create">Create room</button><button class="primary" data-action="join">Join room</button></div>
        <ul>${rosterHtml}</ul>
        <div class="error">${escapeHtml(errorText)}</div>
      </section>` : ""}
    ${screen === "force" ? `
      <section class="panel force">
        <h3>Adventure force</h3>
        <label class="field">GF energy <select data-field="budget">${[500, 700, 1000, 1500, 2000, 3000].map((n) => `<option ${n === selectedBudget ? "selected" : ""}>${n}</option>`).join("")}</select></label>
        <div>Used <span class="badge">${energyUsed()}</span> / ${selectedBudget}</div>
        <div class="borgs">${forceBorgs.map((borg) => `<button class="borg ${selectedForce.includes(borg.id) ? "selected" : ""}" data-borg="${borg.id}"><b>${escapeHtml(borg.name)}</b><br>${borg.id} · ${borg.energy} GF</button>`).join("")}</div>
        <div class="row" style="margin-top:12px"><button class="primary" data-action="ready" ${canReady() ? "" : "disabled"}>Ready for Adventure</button><button class="primary" data-action="launch">Enter arena</button></div>
      </section>` : ""}
  `;

  ui.querySelectorAll<HTMLElement>("[data-action]").forEach((element) => {
    element.addEventListener("click", () => handleAction(element.dataset.action ?? ""));
  });
  ui.querySelectorAll<HTMLInputElement | HTMLSelectElement>("[data-field]").forEach((element) => {
    element.addEventListener("input", () => handleField(element));
  });
  ui.querySelectorAll<HTMLButtonElement>("[data-borg]").forEach((button) => {
    button.addEventListener("click", () => toggleBorg(button.dataset.borg ?? ""));
  });
}

function handleAction(action: string): void {
  if (action === "adventure") screen = "lobby";
  if (action === "create") connect(true);
  if (action === "join") connect(false);
  if (action === "ready") send({ type: "ready", ready: true, force: selectedForce, energy: selectedBudget });
  if (action === "launch") screen = "arena";
  renderUi();
}

function handleField(element: HTMLInputElement | HTMLSelectElement): void {
  if (element.dataset.field === "name") playerName = element.value.slice(0, 18);
  if (element.dataset.field === "room") roomCode = element.value.toUpperCase().replace(/[^A-Z0-9]/g, "").slice(0, 4);
  if (element.dataset.field === "budget") selectedBudget = Number(element.value);
  if (element.dataset.field === "stage") selectedStageIndex = Number(element.value);
  renderUi();
}

function toggleBorg(id: string): void {
  if (!id) return;
  const previousLead = selectedForce[0] ?? GF_RED;
  selectedForce = selectedForce.includes(id) ? selectedForce.filter((borg) => borg !== id) : [...selectedForce, id];
  const nextLead = selectedForce[0] ?? GF_RED;
  if (nextLead !== previousLead) {
    void mountLocalModel(nextLead).catch((error: unknown) => {
      errorText = error instanceof Error ? error.message : String(error);
      renderUi();
    });
  }
  renderUi();
}

function readInput(): InputState {
  let x = 0;
  let y = 0;
  let turn = 0;
  if (keys.has("KeyA")) x -= 1;
  if (keys.has("KeyD")) x += 1;
  if (keys.has("KeyW")) y += 1;
  if (keys.has("KeyS")) y -= 1;
  if (keys.has("KeyQ")) turn += 1;
  if (keys.has("KeyE")) turn -= 1;

  const pad = navigator.getGamepads().find((gamepad) => gamepad?.connected);
  if (pad) {
    controllerName = pad.id;
    x = chooseAnalog(x, pad.axes[0] ?? 0);
    y = chooseAnalog(y, -(pad.axes[1] ?? 0));
    turn = chooseAnalog(turn, -(pad.axes[2] ?? 0));
    pollGamepadActions(pad);
  }

  return { x: deadzone(x), y: deadzone(y), turn: deadzone(turn) };
}

function pollGamepadActions(pad: Gamepad): void {
  const pressed = new Set<number>();
  pad.buttons.forEach((button, index) => {
    if (!button.pressed) return;
    pressed.add(index);
    if (!previousGamepadButtons.has(index)) {
      const action = GAMEPAD_BUTTON_ACTIONS.get(index);
      if (action) queueAction(action);
    }
  });
  previousGamepadButtons = pressed;
}

function queueAction(action: ActionName): void {
  if (screen !== "arena" || !hasClip(currentBorgId, action)) return;
  queuedAction = action;
}

function isTextInputTarget(target: EventTarget | null): boolean {
  return target instanceof HTMLInputElement || target instanceof HTMLSelectElement || target instanceof HTMLTextAreaElement;
}

function chooseAnalog(keyboardValue: number, analogValue: number): number {
  return Math.abs(analogValue) > 0.16 ? analogValue : keyboardValue;
}

function deadzone(value: number): number {
  return Math.abs(value) < 0.16 ? 0 : Math.max(-1, Math.min(1, value));
}

function updateLocal(dt: number, input: InputState): void {
  const turn = 2.7;
  const speed = (currentBorgStats()?.speed ?? 5) * BROWSER_UNITS_PER_SPEED_POINT;
  localRig.rotation.y += input.turn * turn * dt;
  const forward = new THREE.Vector3(Math.sin(localRig.rotation.y), 0, Math.cos(localRig.rotation.y));
  const right = new THREE.Vector3(forward.z, 0, -forward.x);
  const velocity = new THREE.Vector3()
    .addScaledVector(right, input.x)
    .addScaledVector(forward, input.y);
  const moving = velocity.lengthSq() > 0;
  if (moving) localRig.position.add(velocity.normalize().multiplyScalar(speed * dt));
  if (queuedAction) {
    const nextAction = queuedAction;
    queuedAction = null;
    playLocal(nextAction);
  } else if (oneShotAction) {
    oneShotTimeRemaining -= dt;
    if (oneShotTimeRemaining <= 0) playLocal(moving ? "move" : "idle");
  } else if (ANIMATED_BORGS.has(currentBorgId)) {
    playLocal(moving ? "move" : "idle");
  }
  controls.target.lerp(new THREE.Vector3(localRig.position.x, localRig.position.y + 90, localRig.position.z), 0.08);
}

let lastPoseSend = 0;
const clock = new THREE.Clock();
function tick(): void {
  const dt = Math.min(clock.getDelta(), 0.05);
  const input = readInput();
  if (screen === "arena") updateLocal(dt, input);
  localMixer?.update(dt);
  for (const remote of remotes.values()) remote.mixer.update(dt);
  lastPoseSend += dt;
  if (screen === "arena" && lastPoseSend > 1 / 20) {
    lastPoseSend = 0;
    send({
      type: "pose",
      x: localRig.position.x,
      y: localRig.position.y,
      z: localRig.position.z,
      ry: localRig.rotation.y,
      anim: ANIMATED_BORGS.has(currentBorgId) ? currentActionName ?? (input.x || input.y || input.turn ? "move" : "idle") : "idle",
    });
  }
  controls.update();
  renderer.render(scene, camera);
  requestAnimationFrame(tick);
}

function escapeHtml(value: string): string {
  return value.replace(/[&<>"']/g, (char) => ({ "&": "&amp;", "<": "&lt;", ">": "&gt;", '"': "&quot;", "'": "&#39;" })[char] ?? char);
}

function escapeAttr(value: string): string {
  return escapeHtml(value);
}

window.addEventListener("resize", () => {
  camera.aspect = window.innerWidth / window.innerHeight;
  camera.updateProjectionMatrix();
  renderer.setSize(window.innerWidth, window.innerHeight);
});

renderUi();
void loadInitialAssets().catch((error: unknown) => {
  errorText = error instanceof Error ? error.message : String(error);
  renderUi();
});
tick();
