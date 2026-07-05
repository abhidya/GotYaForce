/**
 * TitleIntro — the source-shaped TITLE / desk-intro screen, per
 * research/decomp/index/title-main-menu-flow.md ("Desk Intro Script" section).
 *
 * Ghidra shows the real boot path is:
 *   start -> run_main_game_loop -> frontend desk script -> title/menu scene
 * The desk/title intro itself is driven by `FUN_801c795c` (initializes the front-end
 * desk/title sequence, preloads scene assets incl. `tl00_mdl.arc` (archive 0xaa6) and
 * the `tdc00..09.arc` anim banks, installs script pointer `DAT_8038a3ec`) which then
 * runs per-frame via `sndSeqContinue`. The actor descriptor block `DAT_8038a4ec` is a
 * FLAT array of 6 big-endian u16 borg ids (proven chunk_0006.c:7055 /
 * chunk_0046.c:1176-1192): slot 0 = 0x0615 (G RED), slot 1 = 0x000a (Sasuke pl000a —
 * Kakeru's partner borg), slots 2..5 = 0xffff (empty). Opcode `0x0d` (`FUN_801c81a0`)
 * starts actor animations through `zz_0057ff8_((&DAT_803c4e84)[slot], 5, anim_id)` ->
 * `zz_004beb8_(rate, actor, 0xf, action_group, anim_id, -1, -1)`.
 *
 * `scripts/gen-title-intro-script.mjs` dumps that bytecode, opcode lengths, actor
 * descriptors, and widget descriptors directly from `boot.dol`. This component consumes
 * the generated command stream instead of replaying a hand-authored clip list.
 *
 * SINGLE SCENE (2026-07-05): both desk actors are composited INTO the authored tl00
 * scene and rendered through its AUTHORED HSD camera (DERIVED,
 * research/decomp/tl00-scene-camera-2026-07-04.md) — the ROM loads `tl00_mdl.arc` and
 * the actor archives together via `zz_0042a58_`, and opcode `0x0d` allocates actors into
 * the SAME scene context, so the actors stand ON the desk diorama, not in a floating
 * viewport. The exact ROM actor world placement lives in the undecoded `tdc00..09.arc`
 * anim/pose banks; until those are wired, the stage placement below is TUNED (clearly
 * labeled) — the structure (one scene, authored camera, both actors, slot-driven anims)
 * is the source-shaped part.
 */

import * as THREE from "three";
import {
  fallGravityForBorgId,
  groundRunSpeedForBorgId,
  jumpVelocityForBorgId,
} from "@gf/combat";
import { createThreeAssetLoader } from "@gf/render";
import { prepareImportedModel } from "@gf/render";

import {
  TITLE_INTRO_ACTOR_DESCRIPTORS,
  TITLE_INTRO_ACTOR_EVENTS,
  TITLE_INTRO_COMMANDS,
  TITLE_INTRO_SCRIPT_SOURCE,
  TITLE_INTRO_TOTAL_FRAMES,
} from "../titleIntroScript.generated.js";
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

type TitleIntroCommand = (typeof TITLE_INTRO_COMMANDS)[number];
type TitleActorEvent = (typeof TITLE_INTRO_ACTOR_EVENTS)[number];
type PlayableTitleActorEvent = TitleActorEvent & { file: string; label: string };

// DERIVED from DAT_8038a4ec (slot 0 = G RED pl0615, slot 1 = Sasuke pl000a). Slots 2..5
// are 0xffff (empty) and filtered out.
interface ActorSpec {
  slot: number;
  borgId: string;
  events: PlayableTitleActorEvent[];
}

const ACTOR_SPECS: ActorSpec[] = TITLE_INTRO_ACTOR_DESCRIPTORS.flatMap((descriptor) =>
  descriptor.borgId === null
    ? []
    : {
        slot: descriptor.slot,
        borgId: descriptor.borgId,
        events: TITLE_INTRO_ACTOR_EVENTS.filter(
          (event): event is PlayableTitleActorEvent =>
            event.slot === descriptor.slot && event.file !== null && event.label !== null,
        ),
      },
);

/** Native captured title/desk frame (instant paint + fallback if the 3D scene fails). */
const TITLE_CAPTURE_URL = new URL(
  "../../../reference/captures/title-main-menu.png",
  import.meta.url,
).href;

// Authored tl00 scene camera (DERIVED, tl00-scene-camera-2026-07-04.md probe), already
// converted through the exporter's 180° Y-rotation (x->-x, z->-z).
const SCENE_CAMERA_EYE = new THREE.Vector3(-5, 3557.153, 3145.1);
const SCENE_CAMERA_TARGET = new THREE.Vector3(-5, 3557.153, 12625);

// TUNED stage placement (pending tdc00..09.arc anim/pose-bank decode for the real ROM
// actor world coords). The authored camera sits at desk-surface height (y = eye.y), so
// the stage surface IS that Y; actors stand on it, in front of the camera along its +Z
// gaze direction, separated in X so both partners are visible side by side.
const STAGE_SURFACE_Y = SCENE_CAMERA_EYE.y;
const STAGE_FORWARD_FROM_CAMERA = 700; // TUNED: actors this many units in front of the camera (in-frustum, visible).
const STAGE_X_SPREAD = 240; // TUNED: per-actor X offset from the camera centerline.

function stageBaseForSlot(slot: number): THREE.Vector3 {
  const xOffset = slot === 0 ? -STAGE_X_SPREAD : STAGE_X_SPREAD;
  return new THREE.Vector3(
    SCENE_CAMERA_EYE.x + xOffset,
    STAGE_SURFACE_Y,
    SCENE_CAMERA_EYE.z + STAGE_FORWARD_FROM_CAMERA,
  );
}

type BakedClip = {
  name?: string;
  frameCount: number;
  fps?: number;
  bones: Array<{ i: number; pos?: number[]; rot?: number[]; scl?: number[] }>;
};

/** Same bake->AnimationClip conversion as sim/borgPresentationAssets.ts. Bone-root X/Z is
 * stripped because the actor body is advanced by source movement physics below. */
function buildClip(json: BakedClip): THREE.AnimationClip {
  const fps = json.fps ?? 60;
  const times = Float32Array.from({ length: json.frameCount }, (_, frame) => frame / fps);
  const tracks: THREE.KeyframeTrack[] = [];
  for (const bone of json.bones) {
    const node = `JOBJ_${bone.i}`;
    if (bone.pos?.length === json.frameCount * 3) {
      const values = Float32Array.from(bone.pos);
      if (bone.i === 0) {
        // Root-motion strip: zero bone-0 XZ, matching borgPresentationAssets.ts, so the desk
        // intro doesn't slide the actor off its mark during dash/jump clips.
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

async function loadActorClips(spec: ActorSpec): Promise<Map<number, THREE.AnimationClip>> {
  const uniqueEvents = Array.from(new Map(spec.events.map((event) => [event.animId, event])).values());
  const clips = await Promise.all(
    uniqueEvents.map(async (entry) => {
      const res = await fetch(`/models/${spec.borgId}/${entry.file}`);
      if (!res.ok) throw new Error(`Failed to load ${spec.borgId}/${entry.file}: ${res.status}`);
      const json = (await res.json()) as BakedClip;
      return [entry.animId, buildClip(json)] as const;
    }),
  );
  return new Map(clips);
}

function commandPayloadByte(command: TitleIntroCommand, index: number): number | null {
  return command.payload[index] ?? null;
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

const SOURCE_FPS = 60;
const FIXED_FRAME_SECONDS = 1 / SOURCE_FPS;
const LIGHT_BAR_ACTIVE_FRAMES = 90;

// Local-space choreography (TUNED): the anim ids the script drives (0 idle / 1 move /
// 6 jump_takeoff / 3 dash_back / 4 dash_left / 7 jump_land) get a small synthesized
// travel vector so the montage reads on the desk. These are per-actor LOCAL deltas from
// each actor's stage base; both partners use the same choreography, separated by their
// stage X offset.
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
    // The title bytecode proves animation ids 3/4, but not a combat dash state. Use the
    // same source run speed for title-layer translation so the montage stays in frame.
    dashSpeed: runSpeed,
  };
}

function createInitialActorMotion(): ActorMotionState {
  return {
    position: LOCAL_START.clone(),
    velocity: new THREE.Vector3(0, 0, 0),
    grounded: true,
  };
}

function applyPlanarVelocity(target: THREE.Vector3, direction: THREE.Vector3, speed: number): void {
  target.set(direction.x * speed, target.y, direction.z * speed);
}

function applyActorEventMotion(
  event: PlayableTitleActorEvent,
  motion: ActorMotionState,
  physics: SourceActorPhysics,
): void {
  switch (event.animId) {
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

interface ActorRuntime {
  spec: ActorSpec;
  physics: SourceActorPhysics;
  motion: ActorMotionState;
  stageBase: THREE.Vector3;
  group: THREE.Group; // sits at stageBase (TUNED stage placement)
  modelRoot: THREE.Group; // moves inside `group` per the synthesized motion
  mixer: THREE.AnimationMixer;
  clips: Map<number, THREE.AnimationClip>;
  activeAction: THREE.AnimationAction | null;
  activeEvent: PlayableTitleActorEvent | null;
  activeClipEndsAtFrame: number;
  nextEventIndex: number;
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
      "data-gf-intro-source": TITLE_INTRO_SCRIPT_SOURCE.addresses.script,
      "data-gf-intro-step": "0",
      "data-gf-intro-frame": "0",
    },
  });

  // Backdrop layer: the NATIVE captured title/desk frame (instant paint + fallback).
  const backdrop = el("div", { class: "gf-title-intro-backdrop" });
  backdrop.style.backgroundImage = `url(${TITLE_CAPTURE_URL})`;
  root.appendChild(backdrop);

  // SINGLE 3D scene host: the authored tl00 diorama + both desk actors (G RED slot 0,
  // Sasuke slot 1) composited together through the ONE authored HSD camera. Replaces the
  // former separate floating actor viewport ("wrong stage" — actors now stand on the desk).
  const sceneHost = createUiSceneHost("gf-ui-scene gf-title-intro-scene");
  root.appendChild(sceneHost);

  let sceneDisposed = false;
  let sceneFrame = 0;
  const actors: ActorRuntime[] = [];

  void (async () => {
    try {
      const canvas = sceneHost.querySelector<HTMLCanvasElement>(".gf-ui-scene-canvas");
      if (!canvas) return;
      const renderer = new THREE.WebGLRenderer({ canvas, alpha: true, antialias: true });
      renderer.outputColorSpace = THREE.SRGBColorSpace;
      renderer.setClearColor(0x000000, 0);

      const scene3 = new THREE.Scene();
      // AUTHORED scene lights (DERIVED, tl00-scene-camera-2026-07-04.md probe): ambient
      // rgba(152,140,178) — a cool lavender — plus two gray INFINITE diffuse+specular
      // lights whose direction vectors convert through the same 180° Y-rotation as the
      // camera. Authored fog is a linear 1e6..2e6 range — beyond the 32768 far clip, i.e.
      // authored OFF — so no fog is added (DERIVED negative).
      scene3.add(new THREE.AmbientLight(new THREE.Color(152 / 255, 140 / 255, 178 / 255), 1.0));
      const dir1 = new THREE.DirectionalLight(new THREE.Color(0.5, 0.5, 0.5), 1.0);
      dir1.position.set(2.7812777, 1.9665543, -1.140989);
      scene3.add(dir1);
      const dir2 = new THREE.DirectionalLight(new THREE.Color(0.5, 0.5, 0.5), 1.0);
      dir2.position.set(-0.9624716, 2.0371425, 0.698656);
      scene3.add(dir2);

      // Authored CObj, converted through the exporter's 180° Y-rotation.
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

      // Desk actors: load each partner's model + decoded anim clips, place on the stage.
      const actorLoads = await Promise.all(
        ACTOR_SPECS.map(async (spec) => {
          const [model, clips] = await Promise.all([
            loader.loadGlbScene(`/models/${spec.borgId}/model_00.glb`),
            loadActorClips(spec),
          ]);
          return { spec, model, clips };
        }),
      );
      if (sceneDisposed) return;

      for (const { spec, model, clips } of actorLoads) {
        const stageBase = stageBaseForSlot(spec.slot);
        const group = new THREE.Group();
        group.name = `TitleIntro_Actor_${spec.borgId}_Slot${spec.slot}`;
        group.position.copy(stageBase);
        // Stage-facing yaw so the partner faces along the desk, not away from the camera.
        group.rotation.y = ACTOR_YAW;

        const modelRoot = new THREE.Group();
        modelRoot.name = `TitleIntro_${spec.borgId}_MotionRoot`;
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

        actors.push({
          spec,
          physics: sourceActorPhysicsForBorgId(spec.borgId),
          motion: createInitialActorMotion(),
          stageBase,
          group,
          modelRoot,
          mixer: new THREE.AnimationMixer(model),
          clips,
          activeAction: null,
          activeEvent: null,
          activeClipEndsAtFrame: 0,
          nextEventIndex: 0,
        });
      }
      sceneHost.dataset["gfDeskModels"] = String(mountedTl00);
      sceneHost.dataset["gfIntroActors"] = actors.map((a) => a.spec.borgId).join(",");

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
      let lightBarUntilFrame = -1;
      let frameAccumulator = 0;
      let lastNow = performance.now();
      let commandIndex = 0;

      const resetActorMotion = (actor: ActorRuntime): void => {
        actor.motion.position.copy(LOCAL_START);
        actor.motion.velocity.set(0, 0, 0);
        actor.motion.grounded = true;
        actor.modelRoot.position.copy(actor.motion.position);
      };

      const executeScriptCommand = (command: TitleIntroCommand): void => {
        root.dataset["gfIntroFrame"] = String(sourceFrame);
        root.dataset["gfIntroOpcode"] = `${command.opcode}@${command.offset}`;
        switch (command.name) {
          case "setSceneStep": {
            const step = commandPayloadByte(command, 0);
            if (step !== null) root.dataset["gfIntroStep"] = String(step);
            break;
          }
          case "spawnTitleWidget": {
            const slot = commandPayloadByte(command, 0);
            const widget = commandPayloadByte(command, 1);
            if (slot !== null && widget !== null) {
              root.dataset["gfTitleWidget"] = `${slot}:${widget}`;
            }
            break;
          }
          case "selectWidgetOrEffect": {
            const effect = commandPayloadByte(command, 0);
            if (effect !== null) root.dataset["gfIntroEffect"] = String(effect);
            break;
          }
          case "setTitleWidgetMode": {
            const mode = commandPayloadByte(command, 0);
            if (mode !== null) root.dataset["gfTitleWidgetMode"] = String(mode);
            break;
          }
          case "fade": {
            const fadeKind = commandPayloadByte(command, 0);
            const fadeTarget = commandPayloadByte(command, 1);
            const fadeStep = commandPayloadByte(command, 2);
            root.dataset["gfIntroFade"] = `${fadeKind ?? -1}:${fadeTarget ?? -1}:${fadeStep ?? -1}`;
            break;
          }
          case "setFadeTarget": {
            const target = commandPayloadByte(command, 0);
            if (target !== null) root.dataset["gfIntroFadeTarget"] = String(target);
            break;
          }
          case "playSound": {
            const bank = commandPayloadByte(command, 0);
            const sound = commandPayloadByte(command, 1);
            root.dataset["gfIntroSound"] = `${bank ?? -1}:${sound ?? -1}`;
            break;
          }
          case "setAudioCue": {
            const cue = commandPayloadByte(command, 0);
            if (cue !== null) root.dataset["gfIntroAudioCue"] = String(cue);
            break;
          }
          case "actorControl": {
            // Opcode 0x0d: (mode, slot, value). mode 1 = reset that slot's actor.
            const mode = commandPayloadByte(command, 0);
            const slot = commandPayloadByte(command, 1);
            sceneHost.dataset["gfIntroActorCommand"] = `${slot ?? -1}:${mode ?? -1}:${commandPayloadByte(command, 2) ?? -1}`;
            if (mode === 1) {
              const actor = actors.find((a) => a.spec.slot === slot);
              if (actor) {
                actor.mixer.stopAllAction();
                actor.activeAction = null;
                actor.activeEvent = null;
                actor.activeClipEndsAtFrame = sourceFrame;
                resetActorMotion(actor);
              }
            }
            break;
          }
          case "titleLightBar":
            lightBarUntilFrame = sourceFrame + LIGHT_BAR_ACTIVE_FRAMES;
            root.dataset["gfLightbar"] = "active";
            break;
          case "end":
            root.dataset["gfIntroDone"] = "true";
            break;
          default:
            break;
        }
      };

      const executeScriptCommandsThroughFrame = (): void => {
        while (commandIndex < TITLE_INTRO_COMMANDS.length) {
          const command = TITLE_INTRO_COMMANDS[commandIndex];
          if (!command || command.frame > sourceFrame) return;
          executeScriptCommand(command);
          commandIndex += 1;
        }
      };

      const playActorEvent = (actor: ActorRuntime, event: PlayableTitleActorEvent): void => {
        const clip = actor.clips.get(event.animId);
        actor.nextEventIndex += 1;
        if (!clip) {
          sceneHost.dataset[`gfIntroMissingAnim_${actor.spec.slot}`] = String(event.animId);
          return;
        }
        actor.activeAction?.stop();
        const action = actor.mixer.clipAction(clip);
        action.reset().setLoop(THREE.LoopOnce, 1);
        action.clampWhenFinished = true;
        action.play();
        actor.activeAction = action;
        actor.activeEvent = event;
        actor.activeClipEndsAtFrame = sourceFrame + Math.max(1, Math.ceil(clip.duration * SOURCE_FPS));
        applyActorEventMotion(event, actor.motion, actor.physics);
        sceneHost.dataset[`gfIntroAnim_${actor.spec.slot}`] = event.label;
        sceneHost.dataset[`gfIntroAnimId_${actor.spec.slot}`] = String(event.animId);
      };

      const startDueActorEvents = (): void => {
        for (const actor of actors) {
          while (actor.nextEventIndex < actor.spec.events.length) {
            const nextEvent = actor.spec.events[actor.nextEventIndex];
            if (!nextEvent || nextEvent.frame > sourceFrame) break;
            if (
              actor.activeEvent &&
              nextEvent.frame === actor.activeEvent.frame &&
              sourceFrame < actor.activeClipEndsAtFrame
            ) {
              break;
            }
            playActorEvent(actor, nextEvent);
          }
        }
      };

      const stepActorPhysics = (actor: ActorRuntime): void => {
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
        if (sourceFrame < TITLE_INTRO_TOTAL_FRAMES) {
          sourceFrame += 1;
        }
        root.dataset["gfIntroFrame"] = String(sourceFrame);
        executeScriptCommandsThroughFrame();
        startDueActorEvents();
        for (const actor of actors) stepActorPhysics(actor);
        for (const actor of actors) actor.mixer.update(FIXED_FRAME_SECONDS);
        if (lightBarUntilFrame >= 0 && sourceFrame > lightBarUntilFrame) {
          lightBarUntilFrame = -1;
          root.dataset["gfLightbar"] = "idle";
        }
      };

      executeScriptCommandsThroughFrame();

      const render = (now = performance.now()): void => {
        if (sceneDisposed) return;
        const dt = Math.min(0.1, Math.max(0, (now - lastNow) / 1000));
        lastNow = now;
        frameAccumulator += dt;
        while (frameAccumulator >= FIXED_FRAME_SECONDS) {
          stepFixedFrame();
          frameAccumulator -= FIXED_FRAME_SECONDS;
        }
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
      // Asset load failure: the captured PNG backdrop stays as the presentation.
      sceneHost.dataset["gfModelStatus"] = "failed";
      console.warn("[title] tl00 3D desk scene unavailable, keeping capture:", err);
    }
  })();

  const sourceTitle = el("div", { class: "gf-title-intro-source-title", text: "GOTCHA FORCE" });
  root.appendChild(sourceTitle);

  const lightBar = el("div", { class: "gf-title-intro-lightbar" });
  root.appendChild(lightBar);

  const prompt = el("div", { class: "gf-title-intro-prompt", text: "PRESS START" });
  root.appendChild(prompt);

  function enter(): void {
    if (destroyed) return;
    opts.onEnter();
  }

  // TitleIntro is "press ANY key/click to continue" — broader than the shared menu-input
  // bus's mapped common-action key set (the bus deliberately only maps a fixed vocabulary
  // of keys; TitleIntro wants literally any key). This raw window keydown listener is kept
  // as a DOCUMENTED per-screen extra listener for that reason. It is intentionally NOT
  // routed through subscribeMenuInput. Gamepad input, however, only ever reaches screens
  // through the bus (there is no raw "any gamepad button" event to listen for), so this
  // screen ALSO subscribes to the bus purely so a gamepad confirm/start press works here —
  // both paths call the same enter().
  //
  // stopImmediatePropagation is required here: this raw listener and the bus's own window
  // keydown listener are both registered on `window`. Without it, ONE keypress (e.g. Enter)
  // double-advances the flow — this handler fires first and calls enter() -> showMenu(),
  // which mounts MainMenu and subscribes it to the bus SYNCHRONOUSLY, then the bus's own
  // listener (registered after this one, since TitleIntro is the first screen ever mounted)
  // fires for that SAME event and re-dispatches "confirm" to the now-current subscriber
  // (MainMenu), advancing it too. Swallowing the event here after handling it keeps a
  // single keypress to a single action, matching every other screen's behavior.
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
  const unsubscribeMenuInput = subscribeMenuInput(() => enter());

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
