/**
 * LoadBoxData — Challenge flow screen #4, per `challenge-4-load-box-data.png`.
 *
 * The original asks for Memory Card Slot A and lets START skip. The browser port
 * has local extracted roster data already loaded, so A/START advance to the same
 * next Challenge state while preserving the native UX step.
 */

import * as THREE from "three";
import { ColladaLoader } from "three/examples/jsm/loaders/ColladaLoader.js";

import { el, legendItem } from "../dom.js";

export interface LoadBoxDataOptions {
  onConfirm: () => void;
  onBack?: () => void;
  onSkip?: () => void;
}

export interface LoadBoxDataHandle {
  destroy: () => void;
}

export function createLoadBoxData(
  container: HTMLElement,
  opts: LoadBoxDataOptions,
): LoadBoxDataHandle {
  const root = el("div", { class: "gf-screen gf-load-box" });
  root.appendChild(el("div", { class: "gf-grid-bg gf-bg-gold" }));
  root.appendChild(el("h1", { class: "gf-title gf-load-title", text: "LOAD BOX DATA" }));
  root.appendChild(el("div", { class: "gf-load-rule" }));
  root.appendChild(
    el("div", { class: "gf-load-copy" }, [
      el("div", { text: "Insert Memory Card into Slot A" }),
      el("div", {}, ["and press the ", el("span", { class: "gf-inline-a", text: "A" }), " Button."]),
    ]),
  );

  const box = createBoxHost();
  root.appendChild(box);

  const legend = el("div", { class: "gf-legend" }, [
    legendItem("start", "SKIP"),
    legendItem("b", "BACK"),
    legendItem("a", "CONFIRM"),
  ]);
  root.appendChild(legend);

  function confirm(): void {
    opts.onConfirm();
  }

  function onKey(ev: KeyboardEvent): void {
    if (ev.key === "Enter" || ev.key.toLowerCase() === "a") {
      confirm();
      ev.preventDefault();
    } else if (ev.key.toLowerCase() === "s") {
      (opts.onSkip ?? opts.onConfirm)();
      ev.preventDefault();
    } else if (ev.key === "Escape" || ev.key.toLowerCase() === "b") {
      opts.onBack?.();
      ev.preventDefault();
    }
  }

  container.appendChild(root);
  const stopBoxRender = mountGotchaBoxModel(box);
  window.addEventListener("keydown", onKey);
  return {
    destroy: () => {
      window.removeEventListener("keydown", onKey);
      stopBoxRender();
      root.remove();
    },
  };
}

function createBoxHost(): HTMLDivElement {
  return el("div", { class: "gf-box-model", attrs: { "aria-hidden": "true" } }, [
    el("canvas", { class: "gf-box-canvas", attrs: { "aria-hidden": "true" } }),
  ]) as HTMLDivElement;
}

function mountGotchaBoxModel(host: HTMLElement): () => void {
  const canvas = host.querySelector<HTMLCanvasElement>(".gf-box-canvas");
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

  const camera = new THREE.PerspectiveCamera(31, 1, 1, 5000);
  camera.position.set(360, 310, 560);

  const root = new THREE.Group();
  root.rotation.set(-0.28, -0.42, 0.06);
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

  void new ColladaLoader()
    .loadAsync("/ui/scenes/box00/model_00.dae")
    .then((collada) => {
      if (disposed) return;
      prepareModel(collada.scene);
      fitModel(collada.scene, 360);
      root.add(collada.scene);
    })
    .catch(() => {
      host.dataset["gfModelStatus"] = "failed";
    });

  const render = (): void => {
    if (disposed) return;
    camera.lookAt(0, 34, 0);
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
  model.position.y += 28;
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
