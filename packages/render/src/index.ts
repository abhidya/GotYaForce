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
