/**
 * TitleIntro — the source-shaped TITLE / desk-intro screen.
 *
 * Driven by the 1:1 ROM script VM (`./intro/titleVm.ts` — a faithful port of the
 * `zz_01c7de4_` bytecode dispatcher + all 22 opcode handlers). The VM replays the real
 * desk-intro bytecode from `DAT_8038a3ec` and fires engine effects through a
 * `TitleEffectSink`; this component IMPLEMENTS that sink over three.js + DOM so the VM
 * actually drives: desk-archive attach, actor anim/start/reset (G RED slot 0 + Sasuke
 * slot 1), selected COBJ timelines, overlay/light-bar layers, screen-color tint, and
 * widget/audio triggers.
 *
 * Scene: the source initializes stage id 0x11 (`stff`) and loads `tl00_mdl.arc` plus
 * tdc00..09 before opcode 0x0b attaches the scene. The renderer therefore uses tl00's
 * authored camera/lights, the complete tl00 diorama, and the ten stff models created by
 * `zz_01c84a8_`; their movement is ported from 0x801c87dc..0x801c8c54.
 *
 * Per research/decomp/index/title-main-menu-flow.md: `DAT_8038a4ec` is a flat u16[6]
 * borg-id array — slot 0 = 0x0615 (G RED pl0615), slot 1 = 0x000a (Sasuke pl000a).
 */

import * as THREE from "three";
import { createSourceCamera, createThreeAssetLoader, prepareImportedModel } from "@gf/render";
import type { SourceCamera } from "@gf/render";

import { createTitleVm } from "../intro/titleVm.js";
import type { TitleEffectSink, TitleVm } from "../intro/titleVm.js";
import { createTitlePropController } from "../intro/titlePropController.js";
import { createUiSceneHost } from "../sceneModel.js";
import { el } from "../dom.js";
import { bitmapText, setBitmapText } from "../bitmapText.js";
import type { MenuInputTarget } from "../menuInput.js";
import { publicUrl } from "../../publicUrl.js";

/**
 * Source-strict mode: when a VM command cannot be satisfied from source data
 * (missing animation clip, unresolved cue, unexported drawable), the boot must
 * STOP VISIBLY instead of silently degrading to handcrafted choreography. This
 * realizes the fidelity contract: either the original data drives the screen, or
 * the gap is loud. Enabled when <html data-gf-source-strict> is set (dev/audit).
 * In default mode the gap is still surfaced as a console error + DOM flag so it
 * is never silently swallowed. */
const SOURCE_STRICT = document.documentElement.dataset["gfSourceStrict"] !== undefined;
function sourceMissing(reason: string, detail?: unknown): void {
  console.error(`[title][source-missing] ${reason}`, detail ?? "");
  if (SOURCE_STRICT) throw new Error(`[title][source-missing] ${reason}`);
}
export function __titleSourceStrictForTest(): boolean { return SOURCE_STRICT; }

export interface TitleIntroOptions {
  /** Called on confirm (click or Enter/Space/any key = "press start"). */
  onEnter: () => void;
  /** Source sound-id boundary. Opcode 0x15 emits the original u16 id. */
  onSound: (soundId: number) => void;
}

export interface TitleIntroHandle extends MenuInputTarget {
  destroy: () => void;
}

type TdcSceneState = {
  archive: string;
  resourceSlot: number;
  eye: readonly [number, number, number];
  target: readonly [number, number, number];
  fov: number;
  endFrame: number;
  lightProfile: "base" | "character-base" | "character";
  fog: boolean;
};

type TdcCameraFrame = {
  eye: [number, number, number];
  target: [number, number, number];
  roll: number;
  fov: number;
  near: number;
  far: number;
};

type TdcCameraAnimation = {
  archive: string;
  endFrame: number;
  frames: TdcCameraFrame[];
};

/**
 * Exact COBJ state from the ten `tdc00..09.arc` scene_data roots. `zz_0042a58_`
 * installs these at resource slots 12..21; opcode 0x06 selects that resource slot.
 * Values were decoded with HSDRaw directly from the staged GG4E archives.
 */
const TDC_SCENE_STATES: readonly TdcSceneState[] = [
  { archive: "tdc00.arc", resourceSlot: 12, eye: [8, 364.89, 2595.134], target: [8, 2999.996, -6720.233], fov: 41.539, endFrame: 39, lightProfile: "base", fog: true },
  { archive: "tdc01.arc", resourceSlot: 13, eye: [510.75385, -1446.8043, 4509.2744], target: [1595.9144, -925.9938, -8486.236], fov: 22.029018, endFrame: 23, lightProfile: "base", fog: false },
  { archive: "tdc02.arc", resourceSlot: 14, eye: [-331.3965, -1403.9352, 4802.8525], target: [-1287.339, -1386.3909, 4724.9507], fov: 74.598076, endFrame: 60, lightProfile: "base", fog: false },
  { archive: "tdc03.arc", resourceSlot: 15, eye: [25.054, -1349.234, 5708.005], target: [14.29, -478.701, -8859.972], fov: 43.616, endFrame: 49, lightProfile: "character-base", fog: false },
  { archive: "tdc04.arc", resourceSlot: 16, eye: [555.695, -955.354, 3740.292], target: [587.045, 723.92, -804.43], fov: 41.539, endFrame: 49, lightProfile: "base", fog: false },
  { archive: "tdc05.arc", resourceSlot: 17, eye: [81.82487, 519.5118, 2341.2292], target: [84.95857, 314.86435, 1105.1302], fov: 41.538998, endFrame: 80, lightProfile: "base", fog: true },
  { archive: "tdc06.arc", resourceSlot: 18, eye: [143.903, -1436.151, 4276.268], target: [-300.04, -1429.335, 4313.441], fov: 64.440994, endFrame: 31, lightProfile: "character-base", fog: false },
  { archive: "tdc07.arc", resourceSlot: 19, eye: [-465.22455, -1003.881, 3706.802], target: [-2528.7058, -569.87103, -3034.9438], fov: 22.830599, endFrame: 49, lightProfile: "character-base", fog: true },
  { archive: "tdc08.arc", resourceSlot: 20, eye: [0, -1450, 5005.535], target: [-1800, -1300, 2000], fov: 20, endFrame: 29, lightProfile: "character", fog: false },
  { archive: "tdc09.arc", resourceSlot: 21, eye: [0, -1450, 5000], target: [1800, -1300, 2000], fov: 20, endFrame: 29, lightProfile: "base", fog: false },
] as const;

const TL00_BASE_SCENE_STATE: TdcSceneState = {
  archive: "tl00_mdl.arc",
  resourceSlot: -1,
  eye: [5, 3557.153, -3145.1],
  target: [5, 3557.153, -12625],
  fov: 41.538998,
  endFrame: 1999,
  lightProfile: "base",
  fog: false,
};

const BASE_DIRECTIONS = [
  { color: [128, 128, 128] as const, position: [-2.7812777, 1.9665543, 1.140989] as const },
  { color: [128, 128, 128] as const, position: [0.9624716, 2.0371425, -0.698656] as const },
  { color: [255, 255, 255] as const, position: [1, 1, 1] as const },
  { color: [153, 153, 153] as const, position: [-1, -1, -1] as const },
] as const;
const CHARACTER_DIRECTIONS = [
  { color: [255, 255, 255] as const, position: [0.5, 1, 1] as const },
  { color: [128, 128, 153] as const, position: [-0.5, -1, -1] as const },
] as const;

/**
 * The paired character close-ups encode their subject anchors directly: tdc08 targets
 * (-1800,-1300,2000), tdc09 targets (1800,-1300,2000), and both camera eyes sit on the
 * floor plane at Y=-1450. Keep the actors on that authored floor plane while aiming the
 * cameras 150 units above their roots, exactly matching those two COBJ records.
 */
const INTRO_ACTOR_ANCHORS = [
  [-1800, -1450, 2000],
  [1800, -1450, 2000],
] as const;

const SOURCE_FPS = 60;
const FIXED_FRAME_SECONDS = 1 / SOURCE_FPS;

// ROM script animId -> baked g0-file clip — DERIVED 2026-07-06 (family-ctor-anim-bank
// decode): the VM fires actorPlayAnim(slot, groupSel=5, animId); groupSel 5 indexes the
// actor's +0x1d80 family stream bank's group 5, whose slot-N stream plays metadata-group-5
// anim N, and metadata group 5 identity-maps into MOTION FILE 0 (the borg's own g0 file)
// for N in {0..5,7} — but slot 6's stream plays meta anim 9 (g0 anim 9), for BOTH intro
// families (G RED stream 0x803673f0 / Normal-Ninja-family stream 0x802be8d2 = `01 05 09`).
// The baked anim_g00_sNN index IS the g0-file anim index (proven: pl0000 s14/s23 match the
// ROM battle records (0,0x0e)/(0,0x17)). The old tdc00..09.arc theory is falsified — intro
// anims live in the borg's own g0 motion file. Residual (labeled, not wired): id 3's ROM
// stream carries a playback-rate operand of 30 (s16 at playAnim record+6, substituted
// because the intro caller passes rate=-1.0); its unit (fps vs multiplier) is unpinned, so
// clips still play at their baked rate.
const ANIM_FILES_BY_ID: Record<number, string> = {
  0: "anim_g00_s00_idle.json",
  1: "anim_g00_s01_move.json",
  2: "anim_g00_s02_dash_fwd.json",
  3: "anim_g00_s03_dash_back.json",
  4: "anim_g00_s04_dash_left.json",
  5: "anim_g00_s05_dash_right.json",
  6: "anim_g00_s09_fly_transition.json", // ROM: group-5 slot 6 -> g0 anim 9, NOT anim 6
  7: "anim_g00_s07_jump_land.json",
};

type BakedClip = {
  name?: string;
  frameCount: number;
  fps?: number;
  bones: Array<{ i: number; pos?: number[]; rot?: number[]; scl?: number[] }>;
};

/** Same bake->AnimationClip conversion as sim/borgPresentationAssets.ts. Root translation
 * is intentionally retained: the recovered g0 animation is the choreography source. */
function buildClip(json: BakedClip): THREE.AnimationClip {
  const fps = json.fps ?? 60;
  const times = Float32Array.from({ length: json.frameCount }, (_, frame) => frame / fps);
  const tracks: THREE.KeyframeTrack[] = [];
  for (const bone of json.bones) {
    const node = `JOBJ_${bone.i}`;
    if (bone.pos?.length === json.frameCount * 3) {
      tracks.push(
        new THREE.VectorKeyframeTrack(`${node}.position`, times, Float32Array.from(bone.pos)),
      );
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

async function loadActorClips(borgId: string): Promise<Map<number, THREE.AnimationClip>> {
  const entries = Object.entries(ANIM_FILES_BY_ID) as Array<[string, string]>;
  const clips = await Promise.all(
    entries.map(async ([idStr, file]) => {
      const res = await fetch(publicUrl(`/models/${borgId}/${file}`));
      if (!res.ok) throw new Error(`Failed to load ${borgId}/${file}: ${res.status}`);
      const json = (await res.json()) as BakedClip;
      return [Number(idStr), buildClip(json)] as const;
    }),
  );
  return new Map(clips);
}

interface ActorRenderState {
  slot: number;
  borgId: string;
  group: THREE.Group;
  modelRoot: THREE.Group;
  mixer: THREE.AnimationMixer;
  clips: Map<number, THREE.AnimationClip>;
  activeAction: THREE.AnimationAction | null;
}

interface PropRenderState {
  index: number;
  group: THREE.Group;
  motionNode: THREE.Object3D;
  baseY: number;
  baseYaw: number;
  lastOpacity: number;
}

function setObjectOpacity(object: THREE.Object3D, opacity: number): void {
  object.traverse((child) => {
    if (!(child instanceof THREE.Mesh || child instanceof THREE.SkinnedMesh)) return;
    const materials = Array.isArray(child.material) ? child.material : [child.material];
    for (const material of materials) {
      material.opacity = opacity;
      material.transparent = opacity < 1;
      material.needsUpdate = true;
    }
  });
}

/**
 * The source-owned HSD CObj instance for the title screen. applyTdcFrame routes every
 * tdc00..09 COBJ animation through this (bindAnimation mirrors writing CObj+0x84;
 * applyFrame is zz_00088a4_ @0x800088a4), reading eye/interest/fov/near/far/roll back
 * out of state each frame to drive the THREE.PerspectiveCamera. The title VM's
 * op_setCameraMode (opcode 0x09) can later route through this instance directly.
 *
 * Distinct from combat's boot CObj (bootGlobals.getBootSourceCamera), which owns the
 * zz_00059b8_ boot view; this instance owns the title desk's bound COBJ animations.
 */
export const titleSourceCamera: SourceCamera = createSourceCamera();

/** Opcode 0x09 camera-mode byte (ROM state[0x3e]). `SourceCameraState` has no mode field,
 *  so the renderer stores it here; the title VM's setCameraMode routes through this. */
export const titleCameraState = { mode: 0 };

export function createTitleIntro(container: HTMLElement, opts: TitleIntroOptions): TitleIntroHandle {
  const teardown: Array<() => void> = [];
  let destroyed = false;

  const root = el("div", {
    class: "gf-screen gf-title-intro",
    attrs: {
      role: "button",
      tabindex: "0",
      "aria-label": "Title screen — press start",
    },
  });

  // 3D scene host: authored tl00 diorama + both desk actors through its authored camera.
  const sceneHost = createUiSceneHost("gf-ui-scene gf-title-intro-scene");
  root.appendChild(sceneHost);

  // Full-screen color is opcode 0x01. Opcodes 0x07/0x08 drive the selected HSD COBJ
  // animation and must never be converted into an invented DOM fade.
  const tintLayer = el("div", { class: "gf-title-intro-tint" });
  tintLayer.style.cssText =
    "position:absolute;inset:0;pointer-events:none;z-index:6;opacity:0;";
  root.appendChild(tintLayer);

  // Full-screen overlay quad (opcodes 0x0f/0x10/0x11). The ROM drives a COBJ overlay
  // layer via zz_002aee0_(state+0x40) (on) / zz_002affc_ (off); opcode 0x11 ramps
  // state[0x48] toward state[0x60] and the VM integrates it each tick (titleVm.ts
  // integrate()). This layer's opacity is read from vm.state.overlay.current EVERY
  // FRAME in syncFxLayers — not a static dataset flag — so the ramp produces a real,
  // visible fade driven by the VM's overlay-integration state.
  const overlayLayer = el("div", { class: "gf-title-intro-overlay" });
  overlayLayer.style.cssText =
    "position:absolute;inset:0;pointer-events:none;z-index:5;background:#000;opacity:0;";
  root.appendChild(overlayLayer);

  // Title logo. Opcode 0x13 spawns this as widget id 27 from the DAT_8031a074 chain.
  // The chain's texture IS exported: titles.tpl -> /ui/tpl/titles/image_00_I4.png
  // (640x448 I4; see public/ui/manifest.json sourcePath titles.tpl). The HSD widget is
  // a screen-space 2D quad, so a DOM layer with the real texture is the faithful render
  // (a world-space Three.js plane would misrepresent it). The placeholder text styling
  // in styles.css is inert here — the element has no text node; the real artwork comes
  // from the texture.
  const titleLogoTextureUrl = publicUrl("/ui/tpl/titles/image_00_I4.png");
  const sourceTitle = el("div", { class: "gf-title-intro-source-title" });
  sourceTitle.hidden = true;
  sourceTitle.dataset["gfSource"] = "titles.tpl:image_00_I4.png";
  sourceTitle.style.backgroundImage = `url("${titleLogoTextureUrl}")`;
  sourceTitle.style.backgroundSize = "contain";
  sourceTitle.style.backgroundRepeat = "no-repeat";
  sourceTitle.style.backgroundPosition = "center";
  sourceTitle.style.width = "min(92vw, 720px)";
  sourceTitle.style.aspectRatio = "640 / 448";
  root.appendChild(sourceTitle);
  const lightBar = el("div", { class: "gf-title-intro-lightbar" });
  root.appendChild(lightBar);
  // PRESS START — rendered with the REAL exported ascii.tpl bitmap font (the
  // game's own font atlas, same one the HUD uses), not a CSS typeface.
  const prompt = bitmapText("gf-title-intro-prompt");
  setBitmapText(prompt as HTMLSpanElement, "PRESS START", { bold: true, scale: 4 });
  (prompt as HTMLElement).hidden = true;
  root.appendChild(prompt as HTMLElement);

  // ---- Renderer state populated by the async loader; the sink mutates it. ----------
  let actors: ActorRenderState[] = [];
  let props: PropRenderState[] = [];
  let archivesReady = false;
  let cameraReady = false;
  let selectedTdcIndex = -1;
  let selectedSceneFrame = 0;
  let applyTdcFrame: ((index: number, frame: number) => void) | null = null;

  // The VM is created UPFRONT and ticks every fixed frame; its sink methods no-op until
  // the async scene load populates `actors` (the script's attachDeskArchives cue fires
  // before the first actorControl opcode, so actors are ready by then).
  const sink: TitleEffectSink = {
    isArchiveReady: () => archivesReady,
    isCameraReady: () => cameraReady,
    attachDeskArchives: () => {
      sceneHost.dataset["gfIntroAttach"] = "1";
    },
    screenColor: (rgba, intensity, screenEffect) => {
      const r = (rgba >>> 16) & 0xff;
      const g = (rgba >>> 8) & 0xff;
      const bl = rgba & 0xff;
      tintLayer.style.background = `rgb(${r},${g},${bl})`;
      tintLayer.style.opacity = String(Math.max(0, Math.min(1, intensity / 0xff)));
      sceneHost.dataset["gfIntroTint"] = `${screenEffect}`;
    },
    selectWidgetOrEffect: (effectIndex) => {
      sceneHost.dataset["gfIntroEffect"] = String(effectIndex);
      // zz_0042a58_ loads tdc00..09 into resource slots 12..21. The script's
      // opcode-0x06 payload is that resource slot, not a synthetic effect id.
      if (effectIndex >= 12 && effectIndex <= 21) {
        selectedTdcIndex = effectIndex - 12;
      } else if (effectIndex === 0xff) {
        selectedTdcIndex = -1;
      }
    },
    getSelectedSceneEndFrame: () =>
      selectedTdcIndex < 0
        ? TL00_BASE_SCENE_STATE.endFrame
        : (TDC_SCENE_STATES[selectedTdcIndex]?.endFrame ?? 0),
    applySelectedSceneFrame: (frame) => {
      selectedSceneFrame = frame;
      sceneHost.dataset["gfIntroSceneFrame"] = String(frame);
      applyTdcFrame?.(selectedTdcIndex, frame);
    },
    setCameraMode: (mode) => {
      // ROM: state[0x3e] = mode. Stored on the title camera (SourceCameraState has no
      // mode field, so it lives in titleCameraState). The mode byte selects which camera
      // behavior the desk runs; the cue->behavior mapping is pending decomp, so for now
      // we log + store and keep the authored tdc COBJ animation driving the view.
      if (mode !== titleCameraState.mode) {
        console.info(`[title] opcode 0x09 setCameraMode: ${mode}`);
        titleCameraState.mode = mode;
      }
      sceneHost.dataset["gfIntroCam"] = String(mode);
    },
    setSceneAuxMode: (mode) => {
      sceneHost.dataset["gfIntroSceneAux"] = String(mode);
    },
    actorPlayAnim: (slot, _groupSel, animId) => {
      const actor = actors.find((a) => a.slot === slot);
      if (!actor) {
        sourceMissing(`opcode 0x0d: actor slot ${slot} not materialized`, { slots: actors.map((a) => a.slot) });
        return;
      }
      const clip = actor.clips.get(animId);
      if (!clip) {
        // ROM: zz_0057ff8_(actor, 5, animId) → zz_004beb8_ resolves the actor's +0x1d80
        // group-5 stream. A missing baked clip means the source animation is not
        // exported for this id — stop visibly rather than inventing motion.
        sourceMissing(`opcode 0x0d: slot ${slot} (${actor.borgId}) anim id ${animId} has no baked clip`, { borgId: actor.borgId, animId });
        sceneHost.dataset[`gfIntroMissingAnim_${slot}`] = String(animId);
        return;
      }
      actor.activeAction?.stop();
      const action = actor.mixer.clipAction(clip);
      action.reset().setLoop(THREE.LoopOnce, 1);
      action.clampWhenFinished = true;
      action.play();
      actor.activeAction = action;
      sceneHost.dataset[`gfIntroAnim_${slot}`] = String(animId);
    },
    actorReset: (slot) => {
      const actor = actors.find((a) => a.slot === slot);
      if (!actor) return;
      actor.mixer.stopAllAction();
      actor.activeAction = null;
      actor.modelRoot.position.set(0, 0, 0);
    },
    actorSetVisible: (slot, visible) => {
      const actor = actors.find((a) => a.slot === slot);
      if (actor) actor.group.visible = visible;
    },
    toggleOverlay: (on) => {
      root.dataset["gfOverlay"] = on ? "on" : "off";
    },
    copyOverlayTransform: () => {
      // ROM: gnt4_memcpy(state+0x40, DAT_8038a550, 0x20) — copies a 32-byte transform
      // seed that positions the overlay quad. The quad is already full-screen here, so
      // placement is cosmetic; logged for traceability, no visible effect required.
      console.info("[title] opcode 0x10 copyOverlayTransform: DAT_8038a550 seed (32 bytes) — overlay placement (cosmetic)");
      sceneHost.dataset["gfIntroCopyXform"] = "1";
    },
    titleLightBar: () => {
      // ROM: zz_0040d64_(0,6) drives a light-bar sweep. styles.css keys a 700ms sweep
      // off [data-gf-lightbar="active"]. To allow re-triggering when the opcode fires
      // again, drop the flag, force a reflow, then re-set it so the CSS animation
      // restarts from 0% rather than sticking on the completed keyframe.
      root.dataset["gfLightbar"] = "idle";
      void root.offsetWidth;
      root.dataset["gfLightbar"] = "active";
    },
    spawnTitleWidget: (id) => {
      sceneHost.dataset["gfIntroWidget"] = String(id);
      root.dataset["gfTitleSpawned"] = String(id);
      // id 27 (title logo): the DAT_8031a074 drawable chain's texture IS exported
      // (titles.tpl -> sourceTitle's background-image), so this is a real render, not
      // HLE. id 29 (PRESS START) renders through the real ascii.tpl bitmap font (see
      // bitmapText above). Any OTHER id is an unhandled source command — surface it.
      if (id === 27) {
        sourceTitle.hidden = false;
      } else if (id === 29) {
        (prompt as HTMLElement).hidden = false;
      } else {
        sourceMissing(`opcode 0x13: spawnTitleWidget id ${id} has no drawable binding`, { id });
      }
    },
    setTitleWidgetMode: (mode) => {
      sceneHost.dataset["gfIntroWidgetMode"] = String(mode);
      root.dataset["gfTitleMode"] = String(mode);
    },
    playSound: (cue) => {
      sceneHost.dataset["gfIntroSound"] = String(cue);
      opts.onSound(cue);
    },
  };

  const vm: TitleVm = createTitleVm(sink);
  const propController = createTitlePropController();

  let sceneDisposed = false;
  let sceneFrame = 0;

  void (async () => {
    try {
      const canvas = sceneHost.querySelector<HTMLCanvasElement>(".gf-ui-scene-canvas");
      if (!canvas) return;
      const renderer = new THREE.WebGLRenderer({ canvas, alpha: true, antialias: true });
      renderer.outputColorSpace = THREE.SRGBColorSpace;
      renderer.setClearColor(0x000000, 0);

      const scene3 = new THREE.Scene();
      const lightRig = new THREE.Group();
      lightRig.name = "TitleIntro_TdcLightRig";
      scene3.add(lightRig);
      const camera = new THREE.PerspectiveCamera(41.539, 1, 0.1, 32768);
      const cameraTarget = new THREE.Vector3();
      let cameraRoll = 0;

      const cameraAnimationsResponse = await fetch(publicUrl("/ui/scenes/tl00/tdc-camera-anims.json"));
      if (!cameraAnimationsResponse.ok) {
        throw new Error(`Failed to load exact TDC camera tracks: ${cameraAnimationsResponse.status}`);
      }
      const cameraAnimations = (await cameraAnimationsResponse.json()) as TdcCameraAnimation[];

      const setTdcLights = (state: TdcSceneState): void => {
        lightRig.clear();
        lightRig.add(
          new THREE.AmbientLight(new THREE.Color(152 / 255, 140 / 255, 178 / 255), 1),
        );
        const directions =
          state.lightProfile === "base"
            ? BASE_DIRECTIONS
            : state.lightProfile === "character"
              ? CHARACTER_DIRECTIONS
              : [...CHARACTER_DIRECTIONS, ...BASE_DIRECTIONS];
        for (const source of directions) {
          const [r, g, b] = source.color;
          const [x, y, z] = source.position;
          const light = new THREE.DirectionalLight(new THREE.Color(r / 255, g / 255, b / 255), 1);
          light.position.set(x, y, z);
          lightRig.add(light);
        }
      };

      applyTdcFrame = (index, frame): void => {
        const state = index < 0 ? TL00_BASE_SCENE_STATE : TDC_SCENE_STATES[index];
        if (!state) return;

        // Inline sampler — the original hand-driven path through tdc-camera-anims.json.
        // Kept as the fallback if the SourceCamera throws, per the wiring contract.
        const applyInlineCamera = (): void => {
          const animation = index < 0 ? undefined : cameraAnimations[index];
          const sampled = index < 0
            ? undefined
            : animation?.frames[Math.max(0, Math.min(Math.round(frame), animation.frames.length - 1))];
          const eye = sampled?.eye ?? state.eye;
          const target = sampled?.target ?? state.target;
          camera.position.set(eye[0], eye[1], eye[2]);
          cameraTarget.set(target[0], target[1], target[2]);
          cameraRoll = sampled?.roll ?? 0;
          camera.fov = sampled?.fov ?? state.fov;
          camera.near = sampled?.near ?? 0.1;
          camera.far = sampled?.far ?? 32768;
          camera.updateProjectionMatrix();
        };

        // Source-owned path: route the COBJ animation through the HSD CObj port. The
        // same tdc-camera-anims.json drives both paths; at integer frames (the only
        // values the title VM emits — sceneFrame maps onto the integer SCENE_FRAME_TABLE)
        // SourceCamera.applyFrame is exact, so the THREE camera receives identical
        // eye/target/fov values. bindAnimation mirrors writing CObj+0x84; applyFrame
        // is zz_00088a4_ @0x800088a4.
        try {
          const tdcAnim = index >= 0 ? cameraAnimations[index] : undefined;
          if (tdcAnim) {
            titleSourceCamera.bindAnimation(tdcAnim);
            titleSourceCamera.applyFrame(frame);
          } else {
            // TL00 base scene (index < 0) has no COBJ animation; seed the CObj state
            // directly from the scene record so the exported SourceCamera stays the
            // single source of truth for a future setCameraMode route.
            titleSourceCamera.bindAnimation(null);
            titleSourceCamera.state.eye.x = state.eye[0];
            titleSourceCamera.state.eye.y = state.eye[1];
            titleSourceCamera.state.eye.z = state.eye[2];
            titleSourceCamera.state.interest.x = state.target[0];
            titleSourceCamera.state.interest.y = state.target[1];
            titleSourceCamera.state.interest.z = state.target[2];
            titleSourceCamera.state.fov = state.fov;
            titleSourceCamera.state.roll = 0;
            titleSourceCamera.state.near = 0.1;
            titleSourceCamera.state.far = 32768;
          }
          const s = titleSourceCamera.state;
          camera.position.set(s.eye.x, s.eye.y, s.eye.z);
          cameraTarget.set(s.interest.x, s.interest.y, s.interest.z);
          cameraRoll = s.roll;
          camera.fov = s.fov;
          camera.near = s.near;
          camera.far = s.far;
          camera.updateProjectionMatrix();
        } catch (err) {
          console.warn("[title] SourceCamera path failed, falling back to inline sampling:", err);
          applyInlineCamera();
        }

        setTdcLights(state);
        sceneHost.dataset["gfIntroTdc"] = state.archive;
        sceneHost.dataset["gfIntroTdcSlot"] = String(state.resourceSlot);
        sceneHost.dataset["gfIntroFog"] = state.fog ? "1" : "0";
      };
      applyTdcFrame(selectedTdcIndex, selectedSceneFrame);

      const loader = createThreeAssetLoader({ enableFileCache: true });

      // tl00 diorama (world-space vertices — mount at identity, no fit/recenter).
      const tl00Models = await Promise.all(
        Array.from({ length: 37 }, (_, i) =>
          loader.loadGlbScene(publicUrl(`/ui/scenes/tl00/model_${String(i).padStart(2, "0")}.glb`)).catch(() => null),
        ),
      );
      let mountedTl00 = 0;
      for (const model of tl00Models) {
        if (!model) continue;
        prepareImportedModel(model, { materialSide: THREE.DoubleSide, metalness: 0 });
        scene3.add(model);
        mountedTl00 += 1;
      }

      // Exact stff objects created by zz_01c84a8_: CAPCOM plate, fade quad, four
      // screws, and four nuts/washers. Their source JOBJ_0 transforms are retained.
      const propModels = await Promise.all(
        propController.frames.map((frame) =>
          loader.loadGlbScene(
            publicUrl(`/stages/stff/model/model_${String(frame.modelId).padStart(2, "0")}.glb`),
          ),
        ),
      );
      props = propModels.map((model, index) => {
        const source = propController.frames[index]!;
        prepareImportedModel(model, {
          materialSide: THREE.DoubleSide,
          metalness: 0,
          culling: "disabled",
        });
        const group = new THREE.Group();
        group.name = `TitleIntro_StffProp_${source.modelId}_Variant${source.variant}`;
        group.add(model);
        group.visible = source.visible;
        scene3.add(group);
        const motionNode = model.getObjectByName("JOBJ_0") ?? model;
        setObjectOpacity(model, source.opacity);
        return {
          index: source.index,
          group,
          motionNode,
          baseY: motionNode.position.y,
          baseYaw: motionNode.rotation.y,
          lastOpacity: source.opacity,
        };
      });

      // Desk actors from the VM's seeded slots (G RED pl0615 + Sasuke pl000a).
      const actorLoads = await Promise.all(
        vm.state.actors.map(async (vmActor) => {
          const [model, clips] = await Promise.all([
            loader.loadGlbScene(publicUrl(`/models/${vmActor.borgId}/model_00.glb`)),
            loadActorClips(vmActor.borgId),
          ]);
          return { vmActor, model, clips };
        }),
      );
      if (sceneDisposed) return;

      actors = actorLoads.map(({ vmActor, model, clips }) => {
        const group = new THREE.Group();
        group.name = `TitleIntro_Actor_${vmActor.borgId}_Slot${vmActor.slot}`;
        const anchor = INTRO_ACTOR_ANCHORS[vmActor.slot];
        if (anchor) group.position.set(anchor[0], anchor[1], anchor[2]);
        group.visible = false; // hidden until the VM's actorControl makes it visible

        const modelRoot = new THREE.Group();
        modelRoot.name = `TitleIntro_${vmActor.borgId}_MotionRoot`;
        prepareImportedModel(model, {
          materialSide: THREE.DoubleSide,
          metalness: 0,
          culling: "skinned-disabled",
        });
        modelRoot.add(model);
        group.add(modelRoot);
        scene3.add(group);

        return {
          slot: vmActor.slot,
          borgId: vmActor.borgId,
          group,
          modelRoot,
          mixer: new THREE.AnimationMixer(model),
          clips,
          activeAction: null,
        };
      });
      sceneHost.dataset["gfDeskModels"] = String(mountedTl00);
      sceneHost.dataset["gfIntroProps"] = props.map((prop) => String(prop.index)).join(",");
      sceneHost.dataset["gfIntroCameraSource"] = "tdc00..09.arc:scene_data.cameras[0]:opcode-0x06";
      sceneHost.dataset["gfIntroActorPlacement"] = "tdc08+tdc09-character-targets";
      sceneHost.dataset["gfIntroActors"] = actors.map((a) => a.borgId).join(",");
      archivesReady = true;
      cameraReady = true;

      const resize = (): void => {
        const rect = sceneHost.getBoundingClientRect();
        const width = Math.max(1, Math.round(rect.width));
        const height = Math.max(1, Math.round(rect.height));
        renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
        renderer.setSize(width, height, false);
        camera.aspect = width / height;
        camera.updateProjectionMatrix();
      };
      const observer = new ResizeObserver(resize);
      observer.observe(sceneHost);
      resize();
      teardown.push(() => observer.disconnect());

      let sourceFrame = -1;
      let frameAccumulator = 0;
      let lastNow = performance.now();

      const stepFixedFrame = (): void => {
        if (vm.state.endRequested === 0) {
          sourceFrame += 1;
        }
        vm.tick(); // run the ROM dispatcher and integrate the selected COBJ/overlay timelines
        const propSounds = propController.tick(vm.state.sceneStep);
        for (const soundId of propSounds) opts.onSound(soundId);
        for (const prop of props) {
          const source = propController.frames[prop.index]!;
          prop.group.visible = source.visible && !source.destroyed;
          prop.motionNode.position.y = prop.baseY + source.yOffset;
          prop.motionNode.rotation.y = prop.baseYaw + source.yawRadians;
          if (prop.lastOpacity !== source.opacity) {
            setObjectOpacity(prop.group, source.opacity);
            prop.lastOpacity = source.opacity;
          }
        }
        for (const actor of actors) actor.mixer.update(FIXED_FRAME_SECONDS);
      };

      const syncFxLayers = (): void => {
        root.dataset["gfIntroFrame"] = String(sourceFrame);
        root.dataset["gfIntroPc"] = String(vm.state.pc);
        root.dataset["gfIntroStep"] = String(vm.state.sceneStep);
        root.dataset["gfIntroEnd"] = String(vm.state.endRequested);
        root.dataset["gfIntroDone"] = String(vm.state.endRequested === 1);
        // Overlay (opcodes 0x0f/0x11): the VM integrates state.overlay.current toward
        // target each tick; mirror it onto the overlay quad's opacity. When toggled off
        // (opcode 0x0f arg 0 -> zz_002affc_ deallocates the quad), snap to 0 — the ROM
        // removes the quad from the render list rather than holding a frozen opacity.
        const overlayOpacity = vm.state.overlay.on !== 0
          ? Math.max(0, Math.min(1, vm.state.overlay.current))
          : 0;
        overlayLayer.style.opacity = String(overlayOpacity);
      };

      const render = (now = performance.now()): void => {
        if (sceneDisposed) return;
        const dt = Math.min(0.1, Math.max(0, (now - lastNow) / 1000));
        lastNow = now;
        frameAccumulator += dt;
        while (frameAccumulator >= FIXED_FRAME_SECONDS) {
          stepFixedFrame();
          frameAccumulator -= FIXED_FRAME_SECONDS;
        }
        syncFxLayers();
        camera.lookAt(cameraTarget);
        camera.rotateZ(cameraRoll);
        renderer.render(scene3, camera);
        sceneFrame = requestAnimationFrame(render);
      };
      sceneFrame = requestAnimationFrame(render);
      teardown.push(() => {
        sceneDisposed = true;
        cancelAnimationFrame(sceneFrame);
        for (const actor of actors) actor.mixer.stopAllAction();
        renderer.dispose();
      });
    } catch (err) {
      sceneHost.dataset["gfModelStatus"] = "failed";
      console.warn("[title] source tl00 3D desk scene unavailable:", err);
    }
  })();

  function enter(): void {
    if (destroyed || vm.state.endRequested === 0) return;
    opts.onEnter();
  }

  // "press ANY key/click to continue" — see the long note in the prior revision; the raw
  // window keydown is kept (broader than the bus's mapped vocabulary), stopImmediatePropagation
  // prevents a double-advance, and the host-routed target covers gamepad confirm/start.
  function onKey(ev: KeyboardEvent): void {
    enter();
    ev.preventDefault();
    ev.stopImmediatePropagation();
  }
  function onClick(): void {
    enter();
  }

  window.addEventListener("keydown", onKey);
  root.addEventListener("click", onClick);
  container.appendChild(root);
  return {
    handleMenuInput: (event) => {
      // Keyboard remains on the raw listener so every key (not just mapped actions)
      // has identical behavior. The semantic target supplies the gamepad path.
      if (event.source !== "gamepad") return;
      enter();
    },
    destroy: () => {
      destroyed = true;
      window.removeEventListener("keydown", onKey);
      root.removeEventListener("click", onClick);
      for (const fn of teardown) fn();
      root.remove();
    },
  };
}
