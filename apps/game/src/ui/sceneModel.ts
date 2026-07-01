import * as THREE from "three";
import { ColladaLoader } from "three/examples/jsm/loaders/ColladaLoader.js";

type UiSceneManifest = {
  assets?: Array<{
    id?: string;
    modelFiles?: Array<{ publicPath?: string }>;
  }>;
};

export interface UiSceneModelOptions {
  sceneId: string;
  fitSize?: number;
  camera?: { fov?: number; position?: [number, number, number]; lookAt?: [number, number, number] };
  rotation?: [number, number, number];
  maxModels?: number;
}

export function createUiSceneHost(className: string): HTMLDivElement {
  const host = document.createElement("div");
  host.className = className;
  host.setAttribute("aria-hidden", "true");
  const canvas = document.createElement("canvas");
  canvas.className = "gf-ui-scene-canvas";
  canvas.setAttribute("aria-hidden", "true");
  host.appendChild(canvas);
  return host;
}

export function mountUiSceneModels(host: HTMLElement, opts: UiSceneModelOptions): () => void {
  const canvas = host.querySelector<HTMLCanvasElement>(".gf-ui-scene-canvas");
  if (!canvas) return () => undefined;

  const renderer = new THREE.WebGLRenderer({ canvas, alpha: true, antialias: true });
  renderer.outputColorSpace = THREE.SRGBColorSpace;
  renderer.setClearColor(0x000000, 0);

  const scene = new THREE.Scene();
  scene.add(new THREE.AmbientLight(0xf4efe3, 1.2));
  const keyLight = new THREE.DirectionalLight(0xfff1d6, 1.35);
  keyLight.position.set(-260, 520, 420);
  scene.add(keyLight);
  const fillLight = new THREE.DirectionalLight(0x95bfff, 0.35);
  fillLight.position.set(360, 140, -260);
  scene.add(fillLight);

  const camera = new THREE.PerspectiveCamera(opts.camera?.fov ?? 31, 1, 1, 5000);
  camera.position.fromArray(opts.camera?.position ?? [360, 310, 560]);
  const lookAt = new THREE.Vector3().fromArray(opts.camera?.lookAt ?? [0, 34, 0]);

  const root = new THREE.Group();
  root.rotation.fromArray(opts.rotation ?? [-0.28, -0.42, 0.06]);
  scene.add(root);

  let disposed = false;
  let frame = 0;

  const resize = (): void => {
    const rect = host.getBoundingClientRect();
    const width = Math.max(1, Math.round(rect.width));
    const height = Math.max(1, Math.round(rect.height));
    renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
    renderer.setSize(width, height, false);
    camera.aspect = width / height;
    camera.updateProjectionMatrix();
  };

  const observer = new ResizeObserver(resize);
  observer.observe(host);
  resize();

  void loadSceneModelPaths(opts.sceneId, opts.maxModels)
    .then((paths) => Promise.allSettled(paths.map((path) => new ColladaLoader().loadAsync(path))))
    .then((results) => {
      if (disposed) return;
      for (const result of results) {
        if (result.status !== "fulfilled") continue;
        prepareModel(result.value.scene);
        root.add(result.value.scene);
      }
      if (root.children.length > 0) fitModel(root, opts.fitSize ?? 360);
      host.dataset["gfModelStatus"] = root.children.length > 0 ? "loaded" : "empty";
    })
    .catch(() => {
      host.dataset["gfModelStatus"] = "failed";
    });

  const render = (): void => {
    if (disposed) return;
    camera.lookAt(lookAt);
    renderer.render(scene, camera);
    frame = requestAnimationFrame(render);
  };
  frame = requestAnimationFrame(render);

  return () => {
    disposed = true;
    cancelAnimationFrame(frame);
    observer.disconnect();
    disposeObject(root);
    renderer.dispose();
  };
}

async function loadSceneModelPaths(sceneId: string, maxModels: number | undefined): Promise<string[]> {
  const manifest = await fetch("/ui/scenes/manifest.json")
    .then((r) => (r.ok ? (r.json() as Promise<UiSceneManifest>) : null))
    .catch(() => null);
  const paths =
    manifest?.assets
      ?.find((asset) => asset.id === sceneId)
      ?.modelFiles?.map((file) => file.publicPath)
      .filter((path): path is string => Boolean(path)) ?? [];
  const limited = maxModels === undefined ? paths : paths.slice(0, maxModels);
  return limited.length > 0 ? limited : [`/ui/scenes/${sceneId}/model_00.dae`];
}

function prepareModel(model: THREE.Object3D): void {
  model.traverse((object) => {
    if (object instanceof THREE.Mesh || object instanceof THREE.SkinnedMesh) {
      object.frustumCulled = false;
      const materials = Array.isArray(object.material) ? object.material : [object.material];
      for (const material of materials) {
        material.side = THREE.DoubleSide;
        if ("metalness" in material) (material as THREE.MeshStandardMaterial).metalness = 0;
      }
    }
  });
}

function fitModel(model: THREE.Object3D, targetSize: number): void {
  model.updateMatrixWorld(true);
  const bounds = new THREE.Box3().setFromObject(model);
  const center = new THREE.Vector3();
  const size = new THREE.Vector3();
  bounds.getCenter(center);
  bounds.getSize(size);
  const maxDimension = Math.max(size.x, size.y, size.z, 1);
  const scale = targetSize / maxDimension;
  model.position.set(-center.x, -center.y, -center.z);
  model.scale.setScalar(scale);
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
