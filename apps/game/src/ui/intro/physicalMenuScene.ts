import * as THREE from "three";
import { createThreeAssetLoader, prepareImportedModel } from "@gf/render";

import {
  PHYSICAL_MENU_ANGULAR_STEPS,
  PHYSICAL_MENU_CURSOR_MODEL_ID,
  PHYSICAL_MENU_MODEL_TRIPLETS,
} from "../titleIntroScript.generated.js";
import { BAM16_TO_RADIANS } from "./titlePropController.js";

const SOURCE_FPS = 60;
const FIXED_FRAME_SECONDS = 1 / SOURCE_FPS;
const CURSOR_BAM_STEP = 0x400;
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

interface MenuDrawable {
  readonly menuIndex: number;
  readonly basePivot: THREE.Group;
  readonly selectionPivot: THREE.Group;
  readonly labelPivot: THREE.Group;
  bamAngle: number;
}

function wrapI16(value: number): number {
  return (value << 16) >> 16;
}

function modelPath(modelId: number): string {
  return `/stages/stff/model/model_${String(modelId).padStart(2, "0")}.glb`;
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
 * Renderer for the physical main-menu task created by FUN_801cd90c.
 *
 * Source ownership:
 * - DAT_8038a720 creates seven kind-0 objects, one kind-1 cursor, and seven kind-2 labels.
 * - DAT_8038a760 supplies each entry's base/selection/label stff model ids.
 * - kind 1 uses literal model 0x38 and copies the selected kind-0 source position.
 * - DAT_8038a78c supplies each base model's per-frame BAM rotation step.
 * - the camera and lights come from stage 0x11's stff scene archive.
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

  let selectedIndex = initialIndex;
  let cursorPivot: THREE.Group | null = null;
  let cursorBamAngle = 0;
  let drawables: MenuDrawable[] = [];
  let disposed = false;
  let animationFrame = 0;
  let accumulatedSeconds = 0;
  let previousTime = performance.now();

  function assertIndex(menuIndex: number): void {
    if (!Number.isInteger(menuIndex) || menuIndex < 0 || menuIndex >= PHYSICAL_MENU_MODEL_TRIPLETS.length) {
      throw new RangeError(`physical menu scene index ${menuIndex} is outside the source table`);
    }
  }

  function applySelection(): void {
    for (const drawable of drawables) {
      drawable.selectionPivot.visible = drawable.menuIndex === selectedIndex;
    }
    const selected = drawables[selectedIndex];
    if (cursorPivot && selected) cursorPivot.position.copy(selected.basePivot.position);
  }

  function emitProjections(): void {
    if (!onProjection) return;
    for (const drawable of drawables) {
      const point = drawable.basePivot.position.clone().project(camera);
      onProjection({
        menuIndex: drawable.menuIndex,
        xPercent: (point.x * 0.5 + 0.5) * 100,
        yPercent: (-point.y * 0.5 + 0.5) * 100,
      });
    }
  }

  const resize = (): void => {
    const rect = host.getBoundingClientRect();
    const width = Math.max(1, Math.round(rect.width));
    const height = Math.max(1, Math.round(rect.height));
    renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
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
        Array.from({ length: 35 }, (_, modelId) =>
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
      drawables = tripletModels.map(({ triplet, base, selection, label }) => {
        prepareModel(base);
        prepareModel(selection);
        prepareModel(label);
        const basePivot = createSourcePivot(base);
        const selectionPivot = createSourcePivot(selection);
        const labelPivot = createSourcePivot(label);
        sceneRoot.add(basePivot, selectionPivot, labelPivot);
        return {
          menuIndex: triplet.menuIndex,
          basePivot,
          selectionPivot,
          labelPivot,
          bamAngle: 0,
        };
      });

      prepareModel(cursorModel);
      cursorPivot = createSourcePivot(cursorModel);
      sceneRoot.add(cursorPivot);
      applySelection();
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
    for (const drawable of drawables) {
      const step = PHYSICAL_MENU_ANGULAR_STEPS[drawable.menuIndex]?.bamStep ?? 0;
      drawable.bamAngle = wrapI16(drawable.bamAngle + step);
      drawable.basePivot.rotation.y = drawable.bamAngle * BAM16_TO_RADIANS;
    }
    cursorBamAngle = wrapI16(cursorBamAngle + CURSOR_BAM_STEP);
    if (cursorPivot) cursorPivot.rotation.z = cursorBamAngle * BAM16_TO_RADIANS;
  }

  const render = (time: number): void => {
    if (disposed) return;
    accumulatedSeconds += Math.min((time - previousTime) / 1000, 0.25);
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
      selectedIndex = menuIndex;
      applySelection();
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
