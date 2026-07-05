/**
 * TitleIntro — the source-shaped TITLE / desk-intro screen.
 *
 * Driven by the 1:1 ROM script VM (`./intro/titleVm.ts` — a faithful port of the
 * `zz_01c7de4_` bytecode dispatcher + all 22 opcode handlers). The VM replays the real
 * desk-intro bytecode from `DAT_8038a3ec` and fires engine effects through a
 * `TitleEffectSink`; this component IMPLEMENTS that sink over three.js + DOM so the VM
 * actually drives: desk-archive attach, actor anim/start/reset (G RED slot 0 + Sasuke
 * slot 1), fade/overlay/light-bar layers, screen-color tint, widget/audio triggers.
 *
 * Scene: both desk actors are composited INTO the authored tl00 diorama through its ONE
 * authored HSD camera (DERIVED, research/decomp/tl00-scene-camera-2026-07-04.md). The
 * ROM loads `tl00_mdl.arc` + the actor archives together; opcode `0x0b` is the attach
 * cue. Actor world placement is TUNED pending the `tdc00..09.arc` anim/pose-bank decode
 * (those hold the real ROM coords); the structure is source-shaped.
 *
 * Per research/decomp/index/title-main-menu-flow.md: `DAT_8038a4ec` is a flat u16[6]
 * borg-id array — slot 0 = 0x0615 (G RED pl0615), slot 1 = 0x000a (Sasuke pl000a).
 */

import * as THREE from "three";
import {
  fallGravityForBorgId,
  groundRunSpeedForBorgId,
  jumpVelocityForBorgId,
} from "@gf/combat";
import { createThreeAssetLoader } from "@gf/render";
import { prepareImportedModel } from "@gf/render";

import { createTitleVm } from "../intro/titleVm.js";
import type { TitleEffectSink, TitleVm } from "../intro/titleVm.js";
import { createUiSceneHost } from "../sceneModel.js";
import { el } from "../dom.js";
import { subscribeMenuInput } from "../menuInput.js";

export interface TitleIntroOptions {
  /** Called on confirm (click or Enter/Space/any key = "press start"). */
  onEnter: () => void;
}

export interface TitleIntroHandle {
  destroy: () => void;
}

/** Native captured title/desk frame (instant paint + fallback if the 3D scene fails). */
const TITLE_CAPTURE_URL = new URL(
  "../../../reference/captures/title-main-menu.png",
  import.meta.url,
).href;

// Authored tl00 scene camera (DERIVED, tl00-scene-camera-2026-07-04.md probe), already
// converted through the exporter's 180° Y-rotation (x->-x, z->-z).
const SCENE_CAMERA_EYE = new THREE.Vector3(-5, 3557.153, 3145.1);
const SCENE_CAMERA_TARGET = new THREE.Vector3(-5, 3557.153, 12625);

// TUNED stage placement (pending tdc00..09.arc decode for the real ROM actor coords).
// The authored camera sits at desk-surface height, so the stage surface IS that Y; actors
// stand on it, in front of the camera along its +Z gaze, separated in X.
const STAGE_SURFACE_Y = SCENE_CAMERA_EYE.y;
const STAGE_FORWARD_FROM_CAMERA = 700;
const STAGE_X_SPREAD = 240;

function stageBaseForSlot(slot: number): THREE.Vector3 {
  const xOffset = slot === 0 ? -STAGE_X_SPREAD : STAGE_X_SPREAD;
  return new THREE.Vector3(
    SCENE_CAMERA_EYE.x + xOffset,
    STAGE_SURFACE_Y,
    SCENE_CAMERA_EYE.z + STAGE_FORWARD_FROM_CAMERA,
  );
}

const SOURCE_FPS = 60;
const FIXED_FRAME_SECONDS = 1 / SOURCE_FPS;

// ROM script animId -> baked battle-anim clip (TUNED-anim pending the tdc00..09.arc pose
// banks, which are the canonical intro anim source; pl000amot.bin is absent from AFS).
// The VM fires actorPlayAnim(slot, groupSel=5, animId); groupSel 5 is the ROM's +0x1d80
// bank index for the title intro — we map it to the borg's g0 battle bank slot-for-slot.
const ANIM_FILES_BY_ID: Record<number, string> = {
  0: "anim_g00_s00_idle.json",
  1: "anim_g00_s01_move.json",
  3: "anim_g00_s03_dash_back.json",
  4: "anim_g00_s04_dash_left.json",
  6: "anim_g00_s06_jump_takeoff.json",
  7: "anim_g00_s07_jump_land.json",
};

type BakedClip = {
  name?: string;
  frameCount: number;
  fps?: number;
  bones: Array<{ i: number; pos?: number[]; rot?: number[]; scl?: number[] }>;
};

/** Same bake->AnimationClip conversion as sim/borgPresentationAssets.ts. Bone-root X/Z
 * is stripped because the actor body is advanced by source movement physics below. */
function buildClip(json: BakedClip): THREE.AnimationClip {
  const fps = json.fps ?? 60;
  const times = Float32Array.from({ length: json.frameCount }, (_, frame) => frame / fps);
  const tracks: THREE.KeyframeTrack[] = [];
  for (const bone of json.bones) {
    const node = `JOBJ_${bone.i}`;
    if (bone.pos?.length === json.frameCount * 3) {
      const values = Float32Array.from(bone.pos);
      if (bone.i === 0) {
        for (let i = 0; i < values.length; i += 3) {
          values[i] = 0;
          values[i + 2] = 0;
        }
      }
      tracks.push(new THREE.VectorKeyframeTrack(`${node}.position`, times, values));
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
      const res = await fetch(`/models/${borgId}/${file}`);
      if (!res.ok) throw new Error(`Failed to load ${borgId}/${file}: ${res.status}`);
      const json = (await res.json()) as BakedClip;
      return [Number(idStr), buildClip(json)] as const;
    }),
  );
  return new Map(clips);
}

type SourceActorPhysics = {
  runSpeed: number;
  jumpVelocity: number;
  gravity: number;
  dashSpeed: number;
};

type ActorMotionState = {
  position: THREE.Vector3;
  velocity: THREE.Vector3;
  grounded: boolean;
};

// Local-space choreography (TUNED): the anim ids the VM plays get a small synthesized
// travel vector so the montage reads on the desk. Both partners use the same choreography,
// separated by their stage X offset.
const RUN_DIRECTION = new THREE.Vector3(0.45, 0, -0.9).normalize();
const DASH_BACK_DIRECTION = new THREE.Vector3(-0.25, 0, 1).normalize();
const DASH_LEFT_DIRECTION = new THREE.Vector3(-1, 0, 0);
const ACTOR_YAW = -0.24;
const LOCAL_START = new THREE.Vector3(0, 0, 0);

function sourceActorPhysicsForBorgId(borgId: string): SourceActorPhysics {
  const runSpeed = groundRunSpeedForBorgId(borgId) ?? 12;
  return {
    runSpeed,
    jumpVelocity: jumpVelocityForBorgId(borgId),
    gravity: fallGravityForBorgId(borgId),
    dashSpeed: runSpeed,
  };
}

function createInitialActorMotion(): ActorMotionState {
  return { position: LOCAL_START.clone(), velocity: new THREE.Vector3(0, 0, 0), grounded: true };
}

function applyPlanarVelocity(target: THREE.Vector3, direction: THREE.Vector3, speed: number): void {
  target.set(direction.x * speed, target.y, direction.z * speed);
}

/** Synthesize a local travel vector for a played anim id (TUNED choreography). */
function applyActorAnimMotion(animId: number, motion: ActorMotionState, physics: SourceActorPhysics): void {
  switch (animId) {
    case 0:
      motion.velocity.set(0, 0, 0);
      motion.grounded = true;
      motion.position.y = 0;
      break;
    case 1:
      applyPlanarVelocity(motion.velocity, RUN_DIRECTION, physics.runSpeed);
      break;
    case 6:
      applyPlanarVelocity(motion.velocity, RUN_DIRECTION, physics.runSpeed);
      motion.velocity.y = physics.jumpVelocity;
      motion.grounded = false;
      break;
    case 3:
      applyPlanarVelocity(motion.velocity, DASH_BACK_DIRECTION, physics.dashSpeed);
      break;
    case 4:
      applyPlanarVelocity(motion.velocity, DASH_LEFT_DIRECTION, physics.dashSpeed);
      break;
    case 7:
      motion.velocity.x = 0;
      motion.velocity.z = 0;
      if (motion.position.y <= physics.gravity * 3) {
        motion.position.y = 0;
        motion.velocity.y = 0;
        motion.grounded = true;
      }
      break;
    default:
      break;
  }
}

interface ActorRenderState {
  slot: number;
  borgId: string;
  physics: SourceActorPhysics;
  motion: ActorMotionState;
  stageBase: THREE.Vector3;
  group: THREE.Group;
  modelRoot: THREE.Group;
  mixer: THREE.AnimationMixer;
  clips: Map<number, THREE.AnimationClip>;
  activeAction: THREE.AnimationAction | null;
}

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

  // Backdrop: NATIVE captured title/desk frame (instant paint + fallback).
  const backdrop = el("div", { class: "gf-title-intro-backdrop" });
  backdrop.style.backgroundImage = `url(${TITLE_CAPTURE_URL})`;
  root.appendChild(backdrop);

  // 3D scene host: authored tl00 diorama + both desk actors through ONE authored camera.
  const sceneHost = createUiSceneHost("gf-ui-scene gf-title-intro-scene");
  root.appendChild(sceneHost);

  // Full-screen FX layers driven by the VM (fade-to-black, screen-color tint, overlay).
  const fadeLayer = el("div", { class: "gf-title-intro-fade" });
  fadeLayer.style.cssText =
    "position:absolute;inset:0;background:#000;opacity:0;pointer-events:none;z-index:5;";
  root.appendChild(fadeLayer);
  const tintLayer = el("div", { class: "gf-title-intro-tint" });
  tintLayer.style.cssText =
    "position:absolute;inset:0;pointer-events:none;z-index:6;opacity:0;";
  root.appendChild(tintLayer);

  const sourceTitle = el("div", { class: "gf-title-intro-source-title", text: "GOTCHA FORCE" });
  root.appendChild(sourceTitle);
  const lightBar = el("div", { class: "gf-title-intro-lightbar" });
  root.appendChild(lightBar);
  const prompt = el("div", { class: "gf-title-intro-prompt", text: "PRESS START" });
  root.appendChild(prompt);

  // ---- Renderer state populated by the async loader; the sink mutates it. ----------
  let actors: ActorRenderState[] = [];

  // The VM is created UPFRONT and ticks every fixed frame; its sink methods no-op until
  // the async scene load populates `actors` (the script's attachDeskArchives cue fires
  // before the first actorControl opcode, so actors are ready by then).
  const sink: TitleEffectSink = {
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
    },
    setCameraMode: (mode) => {
      sceneHost.dataset["gfIntroCam"] = String(mode);
    },
    setAudioCue: (cue) => {
      sceneHost.dataset["gfIntroAudioCue"] = String(cue);
    },
    actorPlayAnim: (slot, _groupSel, animId) => {
      const actor = actors.find((a) => a.slot === slot);
      if (!actor) return;
      const clip = actor.clips.get(animId);
      if (!clip) {
        sceneHost.dataset[`gfIntroMissingAnim_${slot}`] = String(animId);
        return;
      }
      actor.activeAction?.stop();
      const action = actor.mixer.clipAction(clip);
      action.reset().setLoop(THREE.LoopOnce, 1);
      action.clampWhenFinished = true;
      action.play();
      actor.activeAction = action;
      applyActorAnimMotion(animId, actor.motion, actor.physics);
      sceneHost.dataset[`gfIntroAnim_${slot}`] = String(animId);
    },
    actorReset: (slot) => {
      const actor = actors.find((a) => a.slot === slot);
      if (!actor) return;
      actor.mixer.stopAllAction();
      actor.activeAction = null;
      actor.motion.position.copy(LOCAL_START);
      actor.motion.velocity.set(0, 0, 0);
      actor.motion.grounded = true;
      actor.modelRoot.position.copy(actor.motion.position);
    },
    actorSetVisible: (slot, visible) => {
      const actor = actors.find((a) => a.slot === slot);
      if (actor) actor.group.visible = visible;
    },
    toggleOverlay: (on) => {
      root.dataset["gfOverlay"] = on ? "on" : "off";
    },
    copyOverlayTransform: () => {
      sceneHost.dataset["gfIntroCopyXform"] = "1";
    },
    titleLightBar: () => {
      root.dataset["gfLightbar"] = "active";
    },
    spawnTitleWidget: (id) => {
      sceneHost.dataset["gfIntroWidget"] = String(id);
    },
    setTitleWidgetMode: (mode) => {
      sceneHost.dataset["gfIntroWidgetMode"] = String(mode);
    },
    playSound: (cue) => {
      sceneHost.dataset["gfIntroSound"] = String(cue);
    },
  };

  const vm: TitleVm = createTitleVm(sink);

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
      // AUTHORED scene lights (DERIVED, tl00-scene-camera-2026-07-04.md).
      scene3.add(new THREE.AmbientLight(new THREE.Color(152 / 255, 140 / 255, 178 / 255), 1.0));
      const dir1 = new THREE.DirectionalLight(new THREE.Color(0.5, 0.5, 0.5), 1.0);
      dir1.position.set(2.7812777, 1.9665543, -1.140989);
      scene3.add(dir1);
      const dir2 = new THREE.DirectionalLight(new THREE.Color(0.5, 0.5, 0.5), 1.0);
      dir2.position.set(-0.9624716, 2.0371425, 0.698656);
      scene3.add(dir2);

      const camera = new THREE.PerspectiveCamera(41.538998, 1, 1, 32768);
      camera.position.copy(SCENE_CAMERA_EYE);

      const loader = createThreeAssetLoader({ enableFileCache: true });

      // tl00 diorama (world-space vertices — mount at identity, no fit/recenter).
      const tl00Models = await Promise.all(
        Array.from({ length: 37 }, (_, i) =>
          loader.loadGlbScene(`/ui/scenes/tl00/model_${String(i).padStart(2, "0")}.glb`).catch(() => null),
        ),
      );
      let mountedTl00 = 0;
      for (const model of tl00Models) {
        if (!model) continue;
        prepareImportedModel(model, { materialSide: THREE.DoubleSide, metalness: 0 });
        scene3.add(model);
        mountedTl00 += 1;
      }

      // Desk actors from the VM's seeded slots (G RED pl0615 + Sasuke pl000a).
      const actorLoads = await Promise.all(
        vm.state.actors.map(async (vmActor) => {
          const [model, clips] = await Promise.all([
            loader.loadGlbScene(`/models/${vmActor.borgId}/model_00.glb`),
            loadActorClips(vmActor.borgId),
          ]);
          return { vmActor, model, clips };
        }),
      );
      if (sceneDisposed) return;

      actors = actorLoads.map(({ vmActor, model, clips }) => {
        const stageBase = stageBaseForSlot(vmActor.slot);
        const group = new THREE.Group();
        group.name = `TitleIntro_Actor_${vmActor.borgId}_Slot${vmActor.slot}`;
        group.position.copy(stageBase);
        group.rotation.y = ACTOR_YAW;
        group.visible = false; // hidden until the VM's actorControl makes it visible

        const modelRoot = new THREE.Group();
        modelRoot.name = `TitleIntro_${vmActor.borgId}_MotionRoot`;
        prepareImportedModel(model, {
          centerXZ: true,
          groundY: true,
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
          physics: sourceActorPhysicsForBorgId(vmActor.borgId),
          motion: createInitialActorMotion(),
          stageBase,
          group,
          modelRoot,
          mixer: new THREE.AnimationMixer(model),
          clips,
          activeAction: null,
        };
      });
      sceneHost.dataset["gfDeskModels"] = String(mountedTl00);
      sceneHost.dataset["gfIntroActors"] = actors.map((a) => a.borgId).join(",");

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

      let sourceFrame = 0;
      let frameAccumulator = 0;
      let lastNow = performance.now();

      const stepActorPhysics = (actor: ActorRenderState): void => {
        actor.motion.position.x += actor.motion.velocity.x;
        actor.motion.position.y += actor.motion.velocity.y;
        actor.motion.position.z += actor.motion.velocity.z;
        if (!actor.motion.grounded || actor.motion.velocity.y !== 0) {
          actor.motion.velocity.y -= actor.physics.gravity;
        }
        if (actor.motion.position.y <= 0) {
          actor.motion.position.y = 0;
          actor.motion.velocity.y = 0;
          actor.motion.grounded = true;
        }
        actor.modelRoot.position.copy(actor.motion.position);
      };

      const stepFixedFrame = (): void => {
        if (vm.state.endRequested === 0) {
          sourceFrame += 1;
        }
        vm.tick(); // run the ROM script dispatcher (fires sink methods + integrates fade/overlay)
        for (const actor of actors) stepActorPhysics(actor);
        for (const actor of actors) actor.mixer.update(FIXED_FRAME_SECONDS);
      };

      const syncFxLayers = (): void => {
        // Fade overlay: alpha derived from the VM fade accumulator (current/target ratio).
        // TUNED interpretation pending the zz_00088a4_ consumer decode.
        const fade = vm.state.fade;
        if (fade.target > 0 && fade.current > 0) {
          fadeLayer.style.opacity = String(Math.max(0, Math.min(1, fade.current / fade.target)));
        } else if (fade.current === 0) {
          fadeLayer.style.opacity = "0";
        }
        root.dataset["gfIntroFrame"] = String(sourceFrame);
        root.dataset["gfIntroPc"] = String(vm.state.pc);
        root.dataset["gfIntroEnd"] = String(vm.state.endRequested);
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
        camera.lookAt(SCENE_CAMERA_TARGET);
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
      console.warn("[title] tl00 3D desk scene unavailable, keeping capture:", err);
    }
  })();

  function enter(): void {
    if (destroyed) return;
    opts.onEnter();
  }

  // "press ANY key/click to continue" — see the long note in the prior revision; the raw
  // window keydown is kept (broader than the bus's mapped vocabulary), stopImmediatePropagation
  // prevents a double-advance, and the bus subscription covers gamepad confirm/start.
  function onKey(ev: KeyboardEvent): void {
    vm.notifyInput(); // feed the input edge to the VM (the end opcode tests state[+0x2d])
    enter();
    ev.preventDefault();
    ev.stopImmediatePropagation();
  }
  function onClick(): void {
    vm.notifyInput();
    enter();
  }

  window.addEventListener("keydown", onKey);
  root.addEventListener("click", onClick);
  container.appendChild(root);
  const unsubscribeMenuInput = subscribeMenuInput(() => {
    vm.notifyInput();
    enter();
  });

  return {
    destroy: () => {
      destroyed = true;
      window.removeEventListener("keydown", onKey);
      root.removeEventListener("click", onClick);
      unsubscribeMenuInput();
      for (const fn of teardown) fn();
      root.remove();
    },
  };
}
