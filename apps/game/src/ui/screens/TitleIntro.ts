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
 * The decoded script plays these actor-slot/anim-id commands in order (title-main-menu-flow.md
 * "Decoded against DAT_8038a3b8..." table): slot0 anim 0, slot1 anim 0, slot0 anim 1, slot1
 * anim 1, slot0 anim 6, slot1 anim 6, slot0 anim 3, slot1 anim 3, slot1 anim 4, slot0 anim 4,
 * slot0 anim 7, slot1 anim 7 — i.e. anim ids 0,1,6,3,4,7 across two actor slots.
 *
 * anim id -> pl0615 exported clip (DERIVED: ids are the script's group-0 slot indices, which
 * line up 1:1 with pl0615's anim_index.json group-0 labels):
 *   0 = idle            (g0s0)
 *   1 = move             (g0s1)
 *   6 = jump_takeoff      (g0s6)
 *   3 = dash_back         (g0s3)
 *   4 = dash_left         (g0s4)
 *   7 = jump_land         (g0s7)
 *
 * Actor slot 0 is rendered here as the G-Red (pl0615) presentation model. Actor slot 1's
 * identity is explicitly UNDECODED in the source map (see the comment below) — we do not
 * spawn a second actor rather than guess who it is.
 *
 * Per-clip hold duration is TUNED (the exact script timing/frame-advance table
 * (`DAT_8038a3b8[opcode]`) is not fully decoded into wall-clock durations yet); each clip
 * plays once at its own baked length before advancing, then the whole sequence loops.
 */

import * as THREE from "three";
import { createThreeAssetLoader } from "@gf/render";
import { prepareImportedModel } from "@gf/render";

import { createUiSceneHost } from "../sceneModel.js";
import { el } from "../dom.js";

export interface TitleIntroOptions {
  /** Called on confirm (click or Enter/Space/any key = "press start"). */
  onEnter: () => void;
}

export interface TitleIntroHandle {
  destroy: () => void;
}

/** G-Red (pl0615) is the confirmed desk-intro actor (DAT_8038a4ec first halfword = 0x0615). */
const GRED_MODEL_URL = "/models/pl0615/model_00.glb";
const GRED_BORG_ID = "pl0615";

/** Native captured title/desk frame (same capture MainMenu's STORY entry binds). */
const TITLE_CAPTURE_URL = new URL(
  "../../../reference/captures/title-main-menu.png",
  import.meta.url,
).href;

/**
 * Desk-intro anim sequence, in script order, DERIVED from the decoded byte-code table in
 * title-main-menu-flow.md. Each entry names the exported pl0615 clip file for that group-0 slot.
 */
const INTRO_ANIM_SEQUENCE: readonly { animId: number; label: string; file: string }[] = [
  { animId: 0, label: "idle", file: "anim_g00_s00_idle.json" },
  { animId: 1, label: "move", file: "anim_g00_s01_move.json" },
  { animId: 6, label: "jump_takeoff", file: "anim_g00_s06_jump_takeoff.json" },
  { animId: 3, label: "dash_back", file: "anim_g00_s03_dash_back.json" },
  { animId: 4, label: "dash_left", file: "anim_g00_s04_dash_left.json" },
  { animId: 7, label: "jump_land", file: "anim_g00_s07_jump_land.json" },
];

type BakedClip = {
  name?: string;
  frameCount: number;
  fps?: number;
  bones: Array<{ i: number; pos?: number[]; rot?: number[]; scl?: number[] }>;
};

/** Same bake->AnimationClip conversion as sim/borgPresentationAssets.ts (kept local/minimal
 *  here since the title intro does not need the full borg-clip cache/fallback machinery). */
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

async function loadIntroClips(): Promise<THREE.AnimationClip[]> {
  const clips = await Promise.all(
    INTRO_ANIM_SEQUENCE.map(async (entry) => {
      const res = await fetch(`/models/${GRED_BORG_ID}/${entry.file}`);
      if (!res.ok) throw new Error(`Failed to load ${entry.file}: ${res.status}`);
      const json = (await res.json()) as BakedClip;
      return buildClip(json);
    }),
  );
  return clips;
}

export function createTitleIntro(container: HTMLElement, opts: TitleIntroOptions): TitleIntroHandle {
  const teardown: Array<() => void> = [];
  let destroyed = false;

  const root = el("div", {
    class: "gf-screen gf-title-intro",
    attrs: { role: "button", tabindex: "0", "aria-label": "Title screen — press start" },
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
  let mixer: THREE.AnimationMixer | null = null;
  let clock: THREE.Clock | null = null;
  let sequenceTimer: ReturnType<typeof setTimeout> | null = null;

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

      prepareImportedModel(model, {
        centerXZ: true,
        groundY: true,
        materialSide: THREE.DoubleSide,
        metalness: 0,
        culling: "skinned-disabled",
      });
      scene3.add(model);

      mixer = new THREE.AnimationMixer(model);
      clock = new THREE.Clock();

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

      // Play the decoded anim-id sequence in order, one clip at a time, then loop the whole
      // sequence — TUNED presentation timing (see file header), DERIVED clip order/ids.
      let seqIndex = 0;
      const playNext = (): void => {
        if (actorDisposed || !mixer) return;
        const entry = INTRO_ANIM_SEQUENCE[seqIndex % INTRO_ANIM_SEQUENCE.length]!;
        const clip = clips[seqIndex % INTRO_ANIM_SEQUENCE.length]!;
        mixer.stopAllAction();
        const action = mixer.clipAction(clip);
        action.reset().setLoop(THREE.LoopOnce, 1);
        action.clampWhenFinished = true;
        action.play();
        seqIndex += 1;
        actorHost.dataset["gfIntroAnim"] = entry.label;
        const durationMs = Math.max(200, (clip.duration || 0.5) * 1000);
        sequenceTimer = setTimeout(playNext, durationMs);
      };
      playNext();
      actorHost.dataset["gfModelStatus"] = "loaded";

      const render = (): void => {
        if (actorDisposed) return;
        const dt = clock?.getDelta() ?? 0;
        mixer?.update(dt);
        camera.lookAt(lookAt);
        renderer.render(scene3, camera);
        actorFrame = requestAnimationFrame(render);
      };
      actorFrame = requestAnimationFrame(render);

      teardown.push(() => {
        actorDisposed = true;
        cancelAnimationFrame(actorFrame);
        if (sequenceTimer !== null) clearTimeout(sequenceTimer);
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
