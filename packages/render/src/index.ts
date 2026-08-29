import * as THREE from "three";
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js";
import { GLTFLoader } from "three/examples/jsm/loaders/GLTFLoader.js";
import { clone as cloneSkinnedObject } from "three/examples/jsm/utils/SkeletonUtils.js";

// Source-owned camera layer (1:1 port of HSD CObj + COBJ animation + zz_00059b8_ view-setup).
// sourceCamera.ts stays THREE-free (preserves @gf/combat's no-three runtime contract);
// the THREE-aware adapters (mtx34ToThreeMatrix4 / applySourceCameraToThree) live in the
// sibling sourceCameraThree.ts and are re-exported here for three-aware hosts (TitleIntro).
export * from "./camera/sourceCamera.js";
export * from "./camera/sourceCameraThree.js";

export interface ThreeViewportOptions {
  antialias?: boolean;
  /**
   * Keeps the backbuffer readable for screenshot verification. Leave off during play;
   * it costs memory/bandwidth on several WebGL drivers.
   */
  debugCapture?: boolean;
  pixelRatioLimit?: number;
  /**
   * REQUIRED. The viewport does not invent a camera: fov/near/far are the stage's own
   * exported HSD CObj values (main.ts seeds them from DEFAULT_RENDER_STATE and each stage
   * overwrites them). A built-in default here would silently frame the world with numbers
   * that came from nowhere and look like a rendering bug rather than a missing argument.
   */
  camera: {
    fov: number;
    near: number;
    far: number;
    position: [number, number, number];
  };
  /** REQUIRED, same reason: the clear color is the stage's exported fog color. */
  clearColor: number;
}

export interface RenderDiagnostics {
  backend: "webgl";
  debugCapture: boolean;
  pixelRatio: number;
  viewport: { width: number; height: number };
  render: {
    frame: number;
    calls: number;
    triangles: number;
    lines: number;
    points: number;
  };
  memory: {
    geometries: number;
    textures: number;
  };
  programs: number | null;
}

export interface ThreeViewport {
  backend: "webgl";
  renderer: THREE.WebGLRenderer;
  scene: THREE.Scene;
  camera: THREE.PerspectiveCamera;
  controls: OrbitControls;
  resize(width?: number, height?: number): void;
  render(): void;
  diagnostics(): RenderDiagnostics;
  captureFrame(type?: string, quality?: number): string;
}

/** Cap for window.devicePixelRatio: a 3x-DPI backbuffer costs fill rate without adding
 *  fidelity to GameCube-era art. Callers override with `pixelRatioLimit`. */
const DEFAULT_PIXEL_RATIO_LIMIT = 2;

/** Default orbit pivot: torso height at the arena origin. */
const DEFAULT_TARGET: readonly [number, number, number] = [0, 80, 0];

export function createThreeViewport(canvas: HTMLCanvasElement, options: ThreeViewportOptions): ThreeViewport {
  const debugCapture = options.debugCapture ?? false;
  const renderer = new THREE.WebGLRenderer({
    canvas,
    antialias: options.antialias ?? true,
    preserveDrawingBuffer: debugCapture,
  });
  renderer.setPixelRatio(Math.min(window.devicePixelRatio, options.pixelRatioLimit ?? DEFAULT_PIXEL_RATIO_LIMIT));
  renderer.setSize(window.innerWidth, window.innerHeight);
  renderer.outputColorSpace = THREE.SRGBColorSpace;
  // GX (GameCube) has NO tone mapping: TEV output goes to the framebuffer directly, so the
  // exported HSD light/fog/vertex colors were authored against a linear->sRGB pipeline with no
  // filmic curve. The previous ACESFilmicToneMapping was a port-ism that compressed/darkened
  // every stage and actor material below its authored color (the "dark/flat arena" defect).
  renderer.toneMapping = THREE.NoToneMapping;

  const scene = new THREE.Scene();
  scene.background = new THREE.Color(options.clearColor);

  const cameraOptions = options.camera;
  const camera = new THREE.PerspectiveCamera(
    cameraOptions.fov,
    window.innerWidth / window.innerHeight,
    cameraOptions.near,
    cameraOptions.far,
  );
  camera.position.set(...cameraOptions.position);

  const controls = new OrbitControls(camera, renderer.domElement);
  controls.enableDamping = true;
  controls.target.set(DEFAULT_TARGET[0], DEFAULT_TARGET[1], DEFAULT_TARGET[2]);

  return {
    backend: "webgl",
    renderer,
    scene,
    camera,
    controls,
    resize(width = window.innerWidth, height = window.innerHeight) {
      camera.aspect = width / height;
      camera.updateProjectionMatrix();
      renderer.setSize(width, height);
    },
    render() {
      renderer.render(scene, camera);
    },
    diagnostics() {
      return getRenderDiagnostics(renderer, debugCapture);
    },
    captureFrame(type = "image/png", quality) {
      renderer.render(scene, camera);
      return renderer.domElement.toDataURL(type, quality);
    },
  };
}

export interface ThreeAssetLoaderOptions {
  manager?: THREE.LoadingManager;
  enableFileCache?: boolean;
}

export interface ThreeAssetLoader {
  readonly manager: THREE.LoadingManager;
  loadGlbScene(url: string): Promise<THREE.Object3D>;
  cloneModel(source: THREE.Object3D): THREE.Object3D;
}

export function createThreeAssetLoader(options: ThreeAssetLoaderOptions = {}): ThreeAssetLoader {
  if (options.enableFileCache) THREE.Cache.enabled = true;

  const manager = options.manager ?? new THREE.LoadingManager();
  const gltf = new GLTFLoader(manager);

  return {
    manager,
    async loadGlbScene(url) {
      if (!/\.glb(?:[?#].*)?$/i.test(url)) throw new Error(`Runtime model must be GLB: ${url}`);
      const result = await gltf.loadAsync(url);
      return result.scene;
    },
    cloneModel(source) {
      return cloneSkinnedObject(source);
    },
  };
}

export type MeshCullingPolicy = "auto" | "disabled" | "skinned-disabled";

export interface ImportedModelOptions {
  centerXZ?: boolean;
  groundY?: boolean;
  materialSide?: THREE.Side;
  metalness?: number;
  culling?: MeshCullingPolicy;
  /** Alpha-discard threshold applied to BLEND-mode (transparent) materials only. GLTF BLEND
   *  materials keep depthWrite on by default, so fully-invisible texels of alpha-textured
   *  props (flags/fences/foliage planes) still write depth and cut rectangular holes into
   *  whatever renders behind them. A small alphaTest discards those texels. */
  transparentAlphaTest?: number;
}

export function prepareImportedModel(model: THREE.Object3D, options: ImportedModelOptions = {}): void {
  if (options.centerXZ || options.groundY) {
    model.updateMatrixWorld(true);
    const box = new THREE.Box3().setFromObject(model);
    const center = new THREE.Vector3();
    box.getCenter(center);
    if (options.centerXZ) {
      model.position.x -= center.x;
      model.position.z -= center.z;
    }
    if (options.groundY) model.position.y -= box.min.y;
  }

  // Rebuild the HSD joint table and reparent flattened "Joint_N_Object_*" display
  // objects under their owning JOBJ bone (see reparentMeshesToBones for the mapping).
  reparentMeshesToBones(model);

  model.traverse((object) => {
    if (!(object instanceof THREE.Mesh || object instanceof THREE.SkinnedMesh)) return;
    applyCullingPolicy(object, options.culling ?? "auto");
    if (!object.geometry.boundingSphere) object.geometry.computeBoundingSphere();
    if (!object.geometry.boundingBox) object.geometry.computeBoundingBox();
    const materials = Array.isArray(object.material) ? object.material : [object.material];
    for (const material of materials) {
      if (options.materialSide !== undefined) material.side = options.materialSide;
      if (options.metalness !== undefined && "metalness" in material) {
        (material as THREE.MeshStandardMaterial).metalness = options.metalness;
      }
      if (options.transparentAlphaTest !== undefined && material.transparent) {
        material.alphaTest = options.transparentAlphaTest;
        material.needsUpdate = true;
      }
    }
  });
}

/** Skinned meshes deform past their static bounds, so frustum culling pops them out of the
 *  frame mid-animation; "skinned-disabled" exempts exactly those. */
function applyCullingPolicy(mesh: THREE.Mesh | THREE.SkinnedMesh, policy: MeshCullingPolicy): void {
  let culled = true;
  if (policy === "disabled") culled = false;
  else if (policy === "skinned-disabled") culled = !(mesh instanceof THREE.SkinnedMesh);
  mesh.frustumCulled = culled;
}

function getRenderDiagnostics(renderer: THREE.WebGLRenderer, debugCapture: boolean): RenderDiagnostics {
  const size = new THREE.Vector2();
  renderer.getSize(size);
  const info = renderer.info as THREE.WebGLInfo & { programs?: unknown[] | null };
  return {
    backend: "webgl",
    debugCapture,
    pixelRatio: renderer.getPixelRatio(),
    viewport: { width: size.x, height: size.y },
    render: {
      frame: info.render.frame,
      calls: info.render.calls,
      triangles: info.render.triangles,
      lines: info.render.lines,
      points: info.render.points,
    },
    memory: {
      geometries: info.memory.geometries,
      textures: info.memory.textures,
    },
    programs: info.programs ? info.programs.length : null,
  };
}

/**
 * Reparent flattened HSD mesh nodes under their controlling skeleton bones.
 *
 * The HSD→Collada→GLB export flattens every "Joint_N_Object_M" display object
 * as a sibling of the JOBJ skeleton (a direct child of the scene root) instead
 * of nesting it under its owning bone. With meshes parented to the root, only
 * the root bone's whole-body motion reaches them; per-bone animation (weapon
 * spin, limb swing) is invisible.
 *
 * HSD joints are indexed by a depth-first traversal of the JOBJ tree, and the
 * exporter names each display object "Joint_<dfsIndex>_Object_<k>" for the bone
 * that owns it (and each bone "JOBJ_<dfsIndex>"). We rebuild that joint table at
 * load time by DFS-walking the JOBJ tree in preserved child order and mapping
 * each mesh's Joint_N to the JOBJ at DFS position N. This matches the HSD joint
 * table for every borg model without a per-model lookup and is robust to JOBJ
 * name permutations. The mesh world transform is preserved, so the rest pose is
 * unchanged; once parented, each mesh inherits its bone's relative animation.
 */
/** The JOBJ root is the only bone with no JOBJ ancestor (it sits under the scene root, not
 *  under another bone). */
function findJobjRoot(jobjBones: ReadonlySet<THREE.Object3D>): THREE.Object3D | null {
  let root: THREE.Object3D | null = null;
  for (const bone of jobjBones) {
    let ancestor = bone.parent;
    let nested = false;
    while (ancestor && !nested) {
      nested = jobjBones.has(ancestor);
      ancestor = ancestor.parent;
    }
    if (!nested) {
      root = bone;
      break;
    }
  }
  return root;
}

function reparentMeshesToBones(model: THREE.Object3D): void {
  const jobjBones = new Set<THREE.Object3D>();
  const meshesToReparent: Array<{ node: THREE.Object3D; jointIndex: number }> = [];
  model.traverse((obj) => {
    const name = obj.name ?? "";
    if (/^JOBJ_\d+$/.test(name)) {
      jobjBones.add(obj);
      return;
    }
    const jointMatch = /^Joint_(\d+)_Object/.exec(name);
    if (jointMatch) {
      meshesToReparent.push({ node: obj, jointIndex: parseInt(jointMatch[1]!, 10) });
    }
  });
  if (jobjBones.size === 0 || meshesToReparent.length === 0) return;

  const root = findJobjRoot(jobjBones);
  if (!root) return; // guard clause: no skeleton root, so there is no joint table to rebuild

  // DFS the JOBJ tree in preserved child order → HSD joint index per bone.
  const dfsIndexToBone = new Map<number, THREE.Object3D>();
  const visit = (node: THREE.Object3D, cursor: { n: number }): void => {
    dfsIndexToBone.set(cursor.n, node);
    cursor.n += 1;
    for (const child of node.children) {
      if (jobjBones.has(child)) visit(child, cursor);
    }
  };
  visit(root, { n: 0 });

  const relative = new THREE.Matrix4();
  for (const { node, jointIndex } of meshesToReparent) {
    const targetBone = dfsIndexToBone.get(jointIndex);
    if (!targetBone || targetBone === node.parent) continue;
    node.updateWorldMatrix(true, false);
    targetBone.updateWorldMatrix(true, false);
    relative.copy(targetBone.matrixWorld).invert().multiply(node.matrixWorld);
    node.matrix.copy(relative);
    node.matrix.decompose(node.position, node.quaternion, node.scale);
    targetBone.add(node);
  }
}
