import * as THREE from "three";
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js";
import { GLTFLoader } from "three/examples/jsm/loaders/GLTFLoader.js";
import { clone as cloneSkinnedObject } from "three/examples/jsm/utils/SkeletonUtils.js";

export interface ThreeViewportOptions {
  backend?: "webgl";
  antialias?: boolean;
  /**
   * Keeps the backbuffer readable for screenshot verification. Leave off during play;
   * it costs memory/bandwidth on several WebGL drivers.
   */
  debugCapture?: boolean;
  /** @deprecated Use debugCapture. */
  preserveDrawingBuffer?: boolean;
  pixelRatioLimit?: number;
  camera?: {
    fov: number;
    near: number;
    far: number;
    position: [number, number, number];
  };
  clearColor?: number;
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

export function createThreeViewport(canvas: HTMLCanvasElement, options: ThreeViewportOptions = {}): ThreeViewport {
  const backend = options.backend ?? "webgl";
  if (backend !== "webgl") throw new Error(`Unsupported render backend: ${backend}`);
  const debugCapture = options.debugCapture ?? options.preserveDrawingBuffer ?? false;
  const renderer = new THREE.WebGLRenderer({
    canvas,
    antialias: options.antialias ?? true,
    preserveDrawingBuffer: debugCapture,
  });
  renderer.setPixelRatio(Math.min(window.devicePixelRatio, options.pixelRatioLimit ?? 2));
  renderer.setSize(window.innerWidth, window.innerHeight);
  renderer.outputColorSpace = THREE.SRGBColorSpace;
  // GX (GameCube) has NO tone mapping: TEV output goes to the framebuffer directly, so the
  // exported HSD light/fog/vertex colors were authored against a linear->sRGB pipeline with no
  // filmic curve. The previous ACESFilmicToneMapping was a port-ism that compressed/darkened
  // every stage and actor material below its authored color (the "dark/flat arena" defect).
  renderer.toneMapping = THREE.NoToneMapping;

  const scene = new THREE.Scene();
  scene.background = new THREE.Color(options.clearColor ?? 0x101820);

  const cameraOptions = options.camera ?? {
    fov: 45,
    near: 0.1,
    far: 100000,
    position: [0, 900, 1800],
  };
  const camera = new THREE.PerspectiveCamera(
    cameraOptions.fov,
    window.innerWidth / window.innerHeight,
    cameraOptions.near,
    cameraOptions.far,
  );
  camera.position.set(...cameraOptions.position);

  const controls = new OrbitControls(camera, renderer.domElement);
  controls.enableDamping = true;
  controls.target.set(0, 80, 0);

  return {
    backend,
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

function applyCullingPolicy(mesh: THREE.Mesh | THREE.SkinnedMesh, policy: MeshCullingPolicy): void {
  if (policy === "disabled") {
    mesh.frustumCulled = false;
  } else if (policy === "skinned-disabled") {
    mesh.frustumCulled = !(mesh instanceof THREE.SkinnedMesh);
  } else {
    mesh.frustumCulled = true;
  }
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

  // The JOBJ root is the only bone with no JOBJ ancestor (it sits under the scene
  // root, not under another bone).
  let root: THREE.Object3D | null = null;
  for (const bone of jobjBones) {
    let ancestor = bone.parent;
    let nested = false;
    while (ancestor) {
      if (jobjBones.has(ancestor)) {
        nested = true;
        break;
      }
      ancestor = ancestor.parent;
    }
    if (!nested) {
      root = bone;
      break;
    }
  }
  if (!root) return;

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
