/**
 * TitleIntro — the source-shaped TITLE / desk-intro screen, per
 * research/decomp/index/title-main-menu-flow.md ("Desk Intro Script" section).
 *
 * Ghidra shows the real boot path is:
 *   start -> run_main_game_loop -> frontend desk script -> title/menu scene
 * The desk/title intro itself is driven by `FUN_801c795c` (initializes the front-end
 * desk/title sequence, preloads scene assets incl. `tl00_mdl.arc` (archive 0xaa6), installs
 * script pointer `DAT_8038a3ec`) which then runs per-frame via `sndSeqContinue`. The captured
 * script bytes seed a borg/actor descriptor list from `DAT_8038a4ec` whose first halfword is
 * `0x0615` — G-Red's borg id (DERIVED) — and opcode `0x0d` (`FUN_801c81a0`) starts actor
 * animations through `zz_0057ff8_((&DAT_803c4e84)[slot], 5, anim_id)` ->
 * `zz_004beb8_(rate, actor, 0xf, action_group, anim_id, -1, -1)`.
 *
 * `scripts/gen-title-intro-script.mjs` now dumps that bytecode, opcode lengths, actor
 * descriptors, and widget descriptors directly from `boot.dol`. This component consumes the
 * generated command stream instead of replaying a hand-authored clip list.
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

export interface TitleIntroOptions {
  /** Called on confirm (click or Enter/Space/any key = "press start"). */
  onEnter: () => void;
}

export interface TitleIntroHandle {
  destroy: () => void;
}

const GRED_DESCRIPTOR = TITLE_INTRO_ACTOR_DESCRIPTORS[0];
/** G-Red (pl0615) is the confirmed desk-intro actor (DAT_8038a4ec first halfword = 0x0615). */
const GRED_BORG_ID = GRED_DESCRIPTOR.borgId ?? "pl0615";
const GRED_MODEL_URL = `/models/${GRED_BORG_ID}/model_00.glb`;

/** Native captured title/desk frame (same capture MainMenu's STORY entry binds). */
const TITLE_CAPTURE_URL = new URL(
  "../../../reference/captures/title-main-menu.png",
  import.meta.url,
).href;

type TitleIntroCommand = (typeof TITLE_INTRO_COMMANDS)[number];
type TitleActorEvent = (typeof TITLE_INTRO_ACTOR_EVENTS)[number];
type PlayableTitleActorEvent = TitleActorEvent & { file: string; label: string };

function isPlayableGRedEvent(event: TitleActorEvent): event is PlayableTitleActorEvent {
  return event.slot === 0 && event.file !== null && event.label !== null;
}

const GRED_ACTOR_EVENTS = TITLE_INTRO_ACTOR_EVENTS.filter(isPlayableGRedEvent);

type BakedClip = {
  name?: string;
  frameCount: number;
  fps?: number;
  bones: Array<{ i: number; pos?: number[]; rot?: number[]; scl?: number[] }>;
};

/** Same bake->AnimationClip conversion as sim/borgPresentationAssets.ts. Bone-root X/Z remains
 * stripped because the actor body is now advanced by source movement physics below. */
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

async function loadIntroClips(): Promise<Map<number, THREE.AnimationClip>> {
  const uniqueEvents = Array.from(new Map(GRED_ACTOR_EVENTS.map((event) => [event.animId, event])).values());
  const clips = await Promise.all(
    uniqueEvents.map(async (entry) => {
      const res = await fetch(`/models/${GRED_BORG_ID}/${entry.file}`);
      if (!res.ok) throw new Error(`Failed to load ${entry.file}: ${res.status}`);
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
const GRED_START_POSITION = new THREE.Vector3(-180, 0, 170);
const GRED_RUN_DIRECTION = new THREE.Vector3(0.45, 0, -0.9).normalize();
const GRED_DASH_BACK_DIRECTION = new THREE.Vector3(-0.25, 0, 1).normalize();
const GRED_DASH_LEFT_DIRECTION = new THREE.Vector3(-1, 0, 0);
const GRED_ACTOR_YAW = -0.24;

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
    position: GRED_START_POSITION.clone(),
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
      applyPlanarVelocity(motion.velocity, GRED_RUN_DIRECTION, physics.runSpeed);
      break;
    case 6:
      applyPlanarVelocity(motion.velocity, GRED_RUN_DIRECTION, physics.runSpeed);
      motion.velocity.y = physics.jumpVelocity;
      motion.grounded = false;
      break;
    case 3:
      applyPlanarVelocity(motion.velocity, GRED_DASH_BACK_DIRECTION, physics.dashSpeed);
      break;
    case 4:
      applyPlanarVelocity(motion.velocity, GRED_DASH_LEFT_DIRECTION, physics.dashSpeed);
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

  // Backdrop layers, back to front:
  //  1. The NATIVE captured title/desk frame (reference/captures/title-main-menu.png) —
  //     instant paint and the fallback if the 3D scene fails to load.
  //  2. The REAL tl00 3D scene rendered through its AUTHORED HSD scene camera (DERIVED,
  //     research/decomp/tl00-scene-camera-2026-07-04.md): the scene_data SOBJ carries one
  //     PERSPECTIVE CObj — fov 41.539°, eye (5, 3557.153, −3145.1), target (5, 3557.153,
  //     −12625), near 0.1 / far 32768. This resolves the old "whole-scene fit frames the
  //     giant room" problem: the placement is authored INTO the scene meshes (world-space
  //     vertices) and the camera frames the desk exactly like hardware. The exporter's
  //     GX→glTF handedness conversion is a 180° Y-rotation, so the camera converts to
  //     eye (−5, 3557.153, 3145.1) → target (−5, 3557.153, 12625) (labeled convention).
  const backdrop = el("div", { class: "gf-title-intro-backdrop" });
  backdrop.style.backgroundImage = `url(${TITLE_CAPTURE_URL})`;
  root.appendChild(backdrop);

  const deskHost = createUiSceneHost("gf-ui-scene gf-title-intro-desk");
  root.appendChild(deskHost);
  let deskDisposed = false;
  let deskFrame = 0;
  void (async () => {
    try {
      const canvas = deskHost.querySelector<HTMLCanvasElement>(".gf-ui-scene-canvas");
      if (!canvas) return;
      const renderer = new THREE.WebGLRenderer({ canvas, alpha: true, antialias: true });
      renderer.outputColorSpace = THREE.SRGBColorSpace;
      renderer.setClearColor(0x000000, 0);

      const scene3 = new THREE.Scene();
      // AUTHORED scene lights (DERIVED, tl00-scene-camera-2026-07-04.md probe): ambient
      // rgba(152,140,178) — a cool lavender — plus two gray INFINITE diffuse+specular
      // lights whose direction vectors convert through the same 180° Y-rotation as the
      // camera. The authored fog is a linear 1e6..2e6 range — beyond the 32768 far clip,
      // i.e. authored OFF — so no fog is added (also DERIVED).
      scene3.add(new THREE.AmbientLight(new THREE.Color(152 / 255, 140 / 255, 178 / 255), 1.0));
      const dir1 = new THREE.DirectionalLight(new THREE.Color(0.5, 0.5, 0.5), 1.0);
      dir1.position.set(2.7812777, 1.9665543, -1.140989);
      scene3.add(dir1);
      const dir2 = new THREE.DirectionalLight(new THREE.Color(0.5, 0.5, 0.5), 1.0);
      dir2.position.set(-0.9624716, 2.0371425, 0.698656);
      scene3.add(dir2);

      // Authored CObj, converted through the exporter's 180° Y-rotation.
      const camera = new THREE.PerspectiveCamera(41.538998, 1, 1, 32768);
      camera.position.set(-5, 3557.153, 3145.1);
      const deskLookAt = new THREE.Vector3(-5, 3557.153, 12625);

      const loader = createThreeAssetLoader({ enableFileCache: true });
      const models = await Promise.all(
        Array.from({ length: 37 }, (_, i) =>
          loader
            .loadGlbScene(`/ui/scenes/tl00/model_${String(i).padStart(2, "0")}.glb`)
            .catch(() => null),
        ),
      );
      if (deskDisposed) return;
      let mounted = 0;
      for (const model of models) {
        if (!model) continue;
        // Authored world-space vertices: mount at identity — no fit, no recenter.
        prepareImportedModel(model, { materialSide: THREE.DoubleSide, metalness: 0 });
        scene3.add(model);
        mounted += 1;
      }
      if (mounted === 0) return; // capture stays as the backdrop
      deskHost.dataset["gfDeskModels"] = String(mounted);

      const resize = (): void => {
        const rect = deskHost.getBoundingClientRect();
        const width = Math.max(1, Math.round(rect.width));
        const height = Math.max(1, Math.round(rect.height));
        renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
        renderer.setSize(width, height, false);
        camera.aspect = width / height;
        camera.updateProjectionMatrix();
      };
      const observer = new ResizeObserver(resize);
      observer.observe(deskHost);
      resize();
      teardown.push(() => observer.disconnect());

      const render = (): void => {
        if (deskDisposed) return;
        camera.lookAt(deskLookAt);
        renderer.render(scene3, camera);
        deskFrame = requestAnimationFrame(render);
      };
      deskFrame = requestAnimationFrame(render);
      teardown.push(() => {
        deskDisposed = true;
        cancelAnimationFrame(deskFrame);
        renderer.dispose();
      });
    } catch (err) {
      console.warn("[title] tl00 3D desk backdrop unavailable, keeping capture:", err);
    }
  })();

  const sourceTitle = el("div", { class: "gf-title-intro-source-title", text: "GOTCHA FORCE" });
  root.appendChild(sourceTitle);

  const lightBar = el("div", { class: "gf-title-intro-lightbar" });
  root.appendChild(lightBar);

  const prompt = el("div", { class: "gf-title-intro-prompt", text: "PRESS START" });
  root.appendChild(prompt);

  // ---- G-Red actor (desk-intro anim sequence) -----------------------------------------
  // Actor slot 0 in the decoded script. Rendered as its own small three.js layer stacked on
  // top of the tl00 backdrop canvas (kept separate from mountUiSceneModels's internal scene
  // so a G-Red load failure can be caught here without tearing down the tl00 backdrop).
  //
  // slot 1 actor: identity undecoded (title-main-menu-flow.md), do not guess. We intentionally
  // do not spawn a second actor for it.
  const actorHost = createUiSceneHost("gf-ui-scene gf-title-intro-actor");
  root.appendChild(actorHost);

  let actorDisposed = false;
  let actorFrame = 0;

  void (async () => {
    try {
      const canvas = actorHost.querySelector<HTMLCanvasElement>(".gf-ui-scene-canvas");
      if (!canvas) return;

      const renderer = new THREE.WebGLRenderer({ canvas, alpha: true, antialias: true });
      renderer.outputColorSpace = THREE.SRGBColorSpace;
      renderer.setClearColor(0x000000, 0);

      const scene3 = new THREE.Scene();
      scene3.add(new THREE.AmbientLight(0xf4efe3, 1.3));
      const key = new THREE.DirectionalLight(0xfff1d6, 1.4);
      key.position.set(-260, 520, 420);
      scene3.add(key);

      // Frame G-Red as a desk figure (~1/3 of screen height, lower half) instead of the
      // old close-up that filled the whole screen. TUNED presentation framing.
      const camera = new THREE.PerspectiveCamera(30, 1, 1, 6000);
      camera.position.set(300, 260, 1250);
      const lookAt = new THREE.Vector3(0, 90, 0);

      const loader = createThreeAssetLoader({ enableFileCache: true });
      const [model, clips] = await Promise.all([loader.loadGlbScene(GRED_MODEL_URL), loadIntroClips()]);
      if (actorDisposed) return;

      const actorRoot = new THREE.Group();
      actorRoot.name = "TitleIntro_GRed_SourcePhysicsRoot";
      actorRoot.rotation.y = GRED_ACTOR_YAW;
      prepareImportedModel(model, {
        centerXZ: true,
        groundY: true,
        materialSide: THREE.DoubleSide,
        metalness: 0,
        culling: "skinned-disabled",
      });
      actorRoot.add(model);
      scene3.add(actorRoot);

      const mixer = new THREE.AnimationMixer(model);
      const physics = sourceActorPhysicsForBorgId(GRED_BORG_ID);
      const motion = createInitialActorMotion();
      let activeAction: THREE.AnimationAction | null = null;
      let activeEvent: PlayableTitleActorEvent | null = null;
      let activeClipEndsAtFrame = 0;
      let nextEventIndex = 0;
      let commandIndex = 0;
      let sourceFrame = 0;
      let lightBarUntilFrame = -1;
      let frameAccumulator = 0;
      let lastNow = performance.now();

      actorRoot.position.copy(motion.position);
      actorHost.dataset["gfModelStatus"] = "loaded";
      actorHost.dataset["gfIntroActor"] = GRED_BORG_ID;
      actorHost.dataset["gfIntroRunSpeed"] = String(physics.runSpeed);
      actorHost.dataset["gfIntroJumpVelocity"] = String(physics.jumpVelocity);
      actorHost.dataset["gfIntroGravity"] = String(physics.gravity);
      actorHost.dataset["gfIntroDashSpeed"] = String(physics.dashSpeed);

      const resetActorMotion = (): void => {
        motion.position.copy(GRED_START_POSITION);
        motion.velocity.set(0, 0, 0);
        motion.grounded = true;
        actorRoot.position.copy(motion.position);
        actorRoot.rotation.y = GRED_ACTOR_YAW;
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
            const mode = commandPayloadByte(command, 0);
            const slot = commandPayloadByte(command, 1);
            const value = commandPayloadByte(command, 2);
            actorHost.dataset["gfIntroActorCommand"] = `${slot ?? -1}:${mode ?? -1}:${value ?? -1}`;
            if (slot === 0 && mode === 1) {
              mixer.stopAllAction();
              activeAction = null;
              activeEvent = null;
              activeClipEndsAtFrame = sourceFrame;
              resetActorMotion();
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

      const playActorEvent = (event: PlayableTitleActorEvent): void => {
        const clip = clips.get(event.animId);
        nextEventIndex += 1;
        if (!clip) {
          actorHost.dataset["gfIntroMissingAnim"] = String(event.animId);
          return;
        }
        activeAction?.stop();
        const action = mixer.clipAction(clip);
        action.reset().setLoop(THREE.LoopOnce, 1);
        action.clampWhenFinished = true;
        action.play();
        activeAction = action;
        activeEvent = event;
        activeClipEndsAtFrame = sourceFrame + Math.max(1, Math.ceil(clip.duration * SOURCE_FPS));
        applyActorEventMotion(event, motion, physics);
        actorHost.dataset["gfIntroAnim"] = event.label;
        actorHost.dataset["gfIntroAnimId"] = String(event.animId);
        actorHost.dataset["gfIntroAnimOffset"] = String(event.offset);
        actorHost.dataset["gfIntroAnimSourceFrame"] = String(event.frame);
      };

      const startDueActorEvents = (): void => {
        while (nextEventIndex < GRED_ACTOR_EVENTS.length) {
          const nextEvent = GRED_ACTOR_EVENTS[nextEventIndex];
          if (!nextEvent || nextEvent.frame > sourceFrame) return;
          if (activeEvent && nextEvent.frame === activeEvent.frame && sourceFrame < activeClipEndsAtFrame) {
            return;
          }
          playActorEvent(nextEvent);
        }
      };

      const stepActorPhysics = (): void => {
        motion.position.x += motion.velocity.x;
        motion.position.y += motion.velocity.y;
        motion.position.z += motion.velocity.z;
        if (!motion.grounded || motion.velocity.y !== 0) {
          motion.velocity.y -= physics.gravity;
        }
        if (motion.position.y <= 0) {
          motion.position.y = 0;
          motion.velocity.y = 0;
          motion.grounded = true;
        }
        actorRoot.position.copy(motion.position);
        actorHost.dataset["gfIntroPosition"] = [
          motion.position.x.toFixed(1),
          motion.position.y.toFixed(1),
          motion.position.z.toFixed(1),
        ].join(",");
      };

      const stepFixedFrame = (): void => {
        if (sourceFrame < TITLE_INTRO_TOTAL_FRAMES) {
          sourceFrame += 1;
        }
        root.dataset["gfIntroFrame"] = String(sourceFrame);
        executeScriptCommandsThroughFrame();
        startDueActorEvents();
        stepActorPhysics();
        mixer.update(FIXED_FRAME_SECONDS);
        if (lightBarUntilFrame >= 0 && sourceFrame > lightBarUntilFrame) {
          lightBarUntilFrame = -1;
          root.dataset["gfLightbar"] = "idle";
        }
      };

      const resize = (): void => {
        const rect = actorHost.getBoundingClientRect();
        const width = Math.max(1, Math.round(rect.width));
        const height = Math.max(1, Math.round(rect.height));
        renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
        renderer.setSize(width, height, false);
        camera.aspect = width / height;
        camera.updateProjectionMatrix();
      };
      const observer = new ResizeObserver(resize);
      observer.observe(actorHost);
      resize();
      teardown.push(() => observer.disconnect());

      executeScriptCommandsThroughFrame();

      const render = (now = performance.now()): void => {
        if (actorDisposed) return;
        const dt = Math.min(0.1, Math.max(0, (now - lastNow) / 1000));
        lastNow = now;
        frameAccumulator += dt;
        while (frameAccumulator >= FIXED_FRAME_SECONDS) {
          stepFixedFrame();
          frameAccumulator -= FIXED_FRAME_SECONDS;
        }
        camera.lookAt(lookAt);
        renderer.render(scene3, camera);
        actorFrame = requestAnimationFrame(render);
      };
      actorFrame = requestAnimationFrame(render);

      teardown.push(() => {
        actorDisposed = true;
        cancelAnimationFrame(actorFrame);
        mixer.stopAllAction();
        renderer.dispose();
      });
    } catch (error) {
      // Asset load failure: leave the tl00 backdrop + CSS prompt as the fallback presentation
      // instead of crashing the title screen.
      actorHost.dataset["gfModelStatus"] = "failed";
      console.warn("[TitleIntro] G-Red actor failed to load; continuing without it.", error);
    }
  })();

  function enter(): void {
    if (destroyed) return;
    opts.onEnter();
  }

  function onKey(ev: KeyboardEvent): void {
    enter();
    ev.preventDefault();
  }
  function onClick(): void {
    enter();
  }

  window.addEventListener("keydown", onKey);
  root.addEventListener("click", onClick);
  container.appendChild(root);

  return {
    destroy: () => {
      destroyed = true;
      window.removeEventListener("keydown", onKey);
      root.removeEventListener("click", onClick);
      for (const fn of teardown) fn();
      root.remove();
    },
  };
}
