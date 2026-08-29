import * as THREE from "three";
import { createThreeAssetLoader, prepareImportedModel } from "@gf/render";

import {
  PHYSICAL_MENU_CURSOR_MODEL_ID,
  PHYSICAL_MENU_MODEL_TRIPLETS,
} from "../titleIntroScript.generated.js";
import { createMenuWidgetSystem, type MenuWidgetEffectSink } from "./menuWidgetSystem.js";
import { BAM16_TO_RADIANS } from "./titlePropController.js";
import { publicUrl } from "../../publicUrl.js";
import { MAX_DEVICE_PIXEL_RATIO, SOURCE_FRAME_SECONDS } from "../../constants.js";

const FIXED_FRAME_SECONDS = SOURCE_FRAME_SECONDS;
/** Cap on the catch-up a single rendered frame may swallow (see main.ts stepBattle). */
const MAX_CATCHUP_SECONDS = 0.25;
/** stff stage archive model count (stage id 0x11 scene, created by zz_01c84a8_). */
const STFF_ENVIRONMENT_MODEL_COUNT = 35;
// The stff GLBs retain the HSD world space. Keeping the ROM camera unchanged makes
// positive-X OPTION/Edit Force project right and views the authored text fronts.
const CAMERA_EYE = new THREE.Vector3(83.785248, 940.888428, 2788.060059);
const CAMERA_TARGET = new THREE.Vector3(83.785248, -11.72845, -409.605103);

export interface PhysicalMenuProjection {
  readonly menuIndex: number;
  readonly xPercent: number;
  readonly yPercent: number;
}

export interface PhysicalMenuSceneHandle {
  setSelected(menuIndex: number): void;
  destroy(): void;
}

/**
 * GLB plumbing owned by this renderer, keyed by the ROM menu index so the
 * widget-system sink can address each pivot. The BAM arithmetic that drove
 * these pivots previously (manual rotation / visibility / cursor copy) is now
 * the widget system's job; the fields below are pure renderer state.
 */
interface MenuEntryPivots {
  readonly basePivot: THREE.Group;
  readonly selectionPivot: THREE.Group;
  readonly labelPivot: THREE.Group;
}

function modelPath(modelId: number): string {
  return publicUrl(`/stages/stff/model/model_${String(modelId).padStart(2, "0")}.glb`);
}

function prepareModel(model: THREE.Object3D): void {
  prepareImportedModel(model, {
    materialSide: THREE.DoubleSide,
    metalness: 0,
    culling: "disabled",
  });
}

/**
 * Turn an exported authored JOBJ transform into the explicit matrix boundary used by
 * the original menu tasks. The pivot keeps the source translation while the GLB keeps
 * its authored rotation/scale; task-local rotations can then be applied without making
 * the object orbit around world origin.
 */
function createSourcePivot(model: THREE.Object3D): THREE.Group {
  const sourceRoot = model.getObjectByName("JOBJ_0") ?? model.children[0] ?? model;
  const sourcePosition = sourceRoot.position.clone();
  const pivot = new THREE.Group();
  pivot.position.copy(sourcePosition);
  model.position.sub(sourcePosition);
  pivot.add(model);
  return pivot;
}

function disposeObject(object: THREE.Object3D): void {
  object.traverse((child) => {
    if (!(child instanceof THREE.Mesh || child instanceof THREE.SkinnedMesh)) return;
    child.geometry.dispose();
    const materials = Array.isArray(child.material) ? child.material : [child.material];
    for (const material of materials) {
      for (const value of Object.values(material)) {
        if (value instanceof THREE.Texture) value.dispose();
      }
      material.dispose();
    }
  });
}

/**
 * Renderer for the physical main-menu task created by `FUN_801cd90c`.
 *
 * Widget lifecycle ownership is delegated to `createMenuWidgetSystem` — a 1:1 port
 * of the ROM's 15-descriptor widget runtime. This module owns only the WebGL
 * plumbing (scene/camera/renderer + GLB loading) and exposes the effect surface
 * (`MenuWidgetEffectSink`) that the widget system drives. The ROM-side arithmetic
 * — DAT_8038a78c base-spin steps, the 0x400 cursor spin, selection visibility
 * gating, and the entry[selection] cursor follow — all live in the widget system.
 *
 * Source ownership kept here (renderer plumbing only):
 * - stage 0x11 stff scene archive (35 environment GLBs) + camera/lights.
 * - DAT_8038a760 triplet GLB loading per entry (base/selection/label pivots).
 * - kind-1 cursor GLB (model 0x38) pivot.
 * - GL draw itself (three.js renders the bound scene each frame; the ROM
 *   `zz_00097b4_(+0xe0, 0x47)` material-preset draw calls are sink no-ops).
 */
export function mountPhysicalMenuScene(
  host: HTMLElement,
  initialIndex: number,
  onProjection?: (projection: PhysicalMenuProjection) => void,
): PhysicalMenuSceneHandle {
  const canvas = host.querySelector<HTMLCanvasElement>(".gf-ui-scene-canvas");
  if (!canvas) {
    return { setSelected: () => undefined, destroy: () => undefined };
  }

  const renderer = new THREE.WebGLRenderer({ canvas, alpha: false, antialias: true });
  renderer.outputColorSpace = THREE.SRGBColorSpace;
  renderer.setClearColor(new THREE.Color(42 / 255, 196 / 255, 188 / 255), 1);

  const scene = new THREE.Scene();
  scene.add(new THREE.AmbientLight(new THREE.Color(152 / 255, 140 / 255, 178 / 255), 1));
  const light0 = new THREE.DirectionalLight(new THREE.Color(0.5, 0.5, 0.5), 1);
  light0.position.set(-2.7812777, 1.9665543, 1.140989);
  scene.add(light0);
  const light1 = new THREE.DirectionalLight(new THREE.Color(0.5, 0.5, 0.5), 1);
  light1.position.set(0.9624716, 2.0371425, -0.698656);
  scene.add(light1);

  const camera = new THREE.PerspectiveCamera(41.538998, 4 / 3, 0.1, 32768);
  camera.position.copy(CAMERA_EYE);
  camera.lookAt(CAMERA_TARGET);

  const loader = createThreeAssetLoader({ enableFileCache: true });
  const sceneRoot = new THREE.Group();
  scene.add(sceneRoot);

  // ROM widget-owned GLB pivots, addressed by the sink closures below.
  const entries = new Map<number, MenuEntryPivots>();
  let cursorPivot: THREE.Group | null = null;

  let disposed = false;
  let animationFrame = 0;
  let accumulatedSeconds = 0;
  let previousTime = performance.now();

  function assertIndex(menuIndex: number): void {
    if (!Number.isInteger(menuIndex) || menuIndex < 0 || menuIndex >= PHYSICAL_MENU_MODEL_TRIPLETS.length) {
      throw new RangeError(`physical menu scene index ${menuIndex} is outside the source table`);
    }
  }

  // =========================================================================
  // MenuWidgetEffectSink — ROM widget system -> three.js object application.
  // Every ROM effect (FUN_801cdaec / zz_01cdf08_ / FUN_801cde10 / ...) routes
  // here. The system computes every argument; this sink only applies it.
  // =========================================================================
  const sink: MenuWidgetEffectSink = {
    // FUN_801cdaec (init kind 0): models already loaded + pivots built by the
    // async loader; attach base+selection and report the base translation that
    // the cursor follows (entry+0x144..14c).
    initEntry(menuIndex) {
      const entry = entries.get(menuIndex);
      if (!entry) return { x: 0, y: 0, z: 0 };
      sceneRoot.add(entry.basePivot, entry.selectionPivot);
      const p = entry.basePivot.position;
      return { x: p.x, y: p.y, z: p.z };
    },
    // FUN_801cde60 (init kind 1): attach the cursor pivot.
    initCursor() {
      if (cursorPivot) sceneRoot.add(cursorPivot);
    },
    // FUN_801ce01c (init kind 2): attach the label pivot.
    initLabel(menuIndex) {
      const entry = entries.get(menuIndex);
      if (entry) sceneRoot.add(entry.labelPivot);
    },
    // FUN_801cdbe0 (update kind 0): base Y-spin (axis 0x79) + selection-model
    // visibility (entry+0xe4 -> +0x10, gated by selection + triggerActive).
    updateEntry(menuIndex, rotationBam, selectionVisible) {
      const entry = entries.get(menuIndex);
      if (!entry) return;
      entry.basePivot.rotation.y = rotationBam * BAM16_TO_RADIANS;
      entry.selectionPivot.visible = selectionVisible;
    },
    // zz_01cdf08_ (update kind 1): cursor follows entry[selection].basePosition
    // into +0x20..28, applies the Z-spin (axis 0x7a), and respects the ROM
    // globalState<2 && triggerActive visibility gate.
    updateCursor(position, rotationBam, cursorVisible) {
      if (!cursorPivot) return;
      cursorPivot.position.set(position.x, position.y, position.z);
      cursorPivot.rotation.z = rotationBam * BAM16_TO_RADIANS;
      cursorPivot.visible = cursorVisible;
    },
    // FUN_801ce084 (update kind 2): [body not yet dumped] only the +0x82 flag is
    // modelled in-system; no three.js effect to apply yet.
    updateLabel(_menuIndex) {
      // intentional no-op until FUN_801ce084 is dumped.
    },
    // FUN_801cde10 / FUN_801cdf84 / FUN_801ce0dc (draw-by-kind): the ROM issues
    // zz_00097b4_(+0xe0, 0x47) per draw to set a material preset. three.js
    // renders the bound GLB materials directly each frame, so these are no-ops;
    // GL draw is renderer-owned (kept here, not in the widget system).
    drawEntry() {
      /* renderer-owned */
    },
    drawCursor() {
      /* renderer-owned */
    },
    drawLabel() {
      /* renderer-owned */
    },
  };

  const widgetSystem = createMenuWidgetSystem(sink);
  // PTR_DAT_80433930[0x32] seed; init() reads it when the cursor first resolves.
  widgetSystem.setSelected(initialIndex);

  function emitProjections(): void {
    if (!onProjection) return;
    for (const [menuIndex, entry] of entries) {
      const point = entry.basePivot.position.clone().project(camera);
      onProjection({
        menuIndex,
        xPercent: (point.x * 0.5 + 0.5) * 100,
        yPercent: (-point.y * 0.5 + 0.5) * 100,
      });
    }
  }

  const resize = (): void => {
    const rect = host.getBoundingClientRect();
    const width = Math.max(1, Math.round(rect.width));
    const height = Math.max(1, Math.round(rect.height));
    renderer.setPixelRatio(Math.min(window.devicePixelRatio, MAX_DEVICE_PIXEL_RATIO));
    renderer.setSize(width, height, false);
    camera.aspect = width / height;
    camera.updateProjectionMatrix();
    emitProjections();
  };
  const observer = new ResizeObserver(resize);
  observer.observe(host);
  resize();

  void (async () => {
    try {
      const stffEnvironment = await Promise.all(
        Array.from({ length: STFF_ENVIRONMENT_MODEL_COUNT }, (_, modelId) =>
          loader.loadGlbScene(modelPath(modelId)),
        ),
      );
      const tripletModels = await Promise.all(
        PHYSICAL_MENU_MODEL_TRIPLETS.map(async (triplet) => ({
          triplet,
          base: await loader.loadGlbScene(modelPath(triplet.baseModelId)),
          selection: await loader.loadGlbScene(modelPath(triplet.selectionModelId)),
          label: await loader.loadGlbScene(modelPath(triplet.labelModelId)),
        })),
      );
      const cursorModel = await loader.loadGlbScene(modelPath(PHYSICAL_MENU_CURSOR_MODEL_ID));
      if (disposed) return;

      for (const model of stffEnvironment) {
        prepareModel(model);
        sceneRoot.add(model);
      }
      for (const { triplet, base, selection, label } of tripletModels) {
        prepareModel(base);
        prepareModel(selection);
        prepareModel(label);
        entries.set(triplet.menuIndex, {
          basePivot: createSourcePivot(base),
          selectionPivot: createSourcePivot(selection),
          labelPivot: createSourcePivot(label),
        });
      }

      prepareModel(cursorModel);
      cursorPivot = createSourcePivot(cursorModel);

      // ROM widget system owns the lifecycle from here: init() walks all 15
      // DAT_8038a720 descriptors, binding models via the sink + seeding BAM
      // accumulators + running one trailing update-by-kind per widget (so the
      // scene is positioned correctly on the first rendered frame).
      widgetSystem.init();
      emitProjections();
      host.dataset["gfModelStatus"] = "loaded";
      host.dataset["gfPhysicalMenuModels"] = PHYSICAL_MENU_MODEL_TRIPLETS
        .flatMap((entry) => [entry.baseModelId, entry.selectionModelId, entry.labelModelId])
        .join(",");
    } catch (error) {
      host.dataset["gfModelStatus"] = "failed";
      console.warn("[physicalMenuScene] source menu models failed to load", error);
    }
  })();

  function tickSourceFrame(): void {
    // zz_01cda40_ steady-state think: update-by-kind[kind] for every widget,
    // routed through the sink. Replaces the hand-rolled BAM math + cursor copy.
    widgetSystem.update();
  }

  const render = (time: number): void => {
    if (disposed) return;
    accumulatedSeconds += Math.min((time - previousTime) / 1000, MAX_CATCHUP_SECONDS);
    previousTime = time;
    while (accumulatedSeconds >= FIXED_FRAME_SECONDS) {
      tickSourceFrame();
      accumulatedSeconds -= FIXED_FRAME_SECONDS;
    }
    renderer.render(scene, camera);
    animationFrame = requestAnimationFrame(render);
  };
  animationFrame = requestAnimationFrame(render);

  return {
    setSelected(menuIndex) {
      assertIndex(menuIndex);
      // PTR_DAT_80433930[0x32] write. The ROM applies this on the next think
      // tick (cursor follow + entry visibility), so we mirror that: no
      // synchronous update here, the fixed-step loop picks it up within one
      // SOURCE_FPS frame.
      widgetSystem.setSelected(menuIndex);
    },
    destroy() {
      disposed = true;
      cancelAnimationFrame(animationFrame);
      observer.disconnect();
      disposeObject(sceneRoot);
      renderer.dispose();
    },
  };
}
