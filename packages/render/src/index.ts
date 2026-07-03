import * as THREE from "three";
import { OrbitControls } from "three/examples/jsm/controls/OrbitControls.js";

export interface ThreeViewportOptions {
  antialias?: boolean;
  preserveDrawingBuffer?: boolean;
  camera?: {
    fov: number;
    near: number;
    far: number;
    position: [number, number, number];
  };
  clearColor?: number;
}

export interface ThreeViewport {
  renderer: THREE.WebGLRenderer;
  scene: THREE.Scene;
  camera: THREE.PerspectiveCamera;
  controls: OrbitControls;
  resize(width?: number, height?: number): void;
  render(): void;
}

export function createThreeViewport(canvas: HTMLCanvasElement, options: ThreeViewportOptions = {}): ThreeViewport {
  const renderer = new THREE.WebGLRenderer({
    canvas,
    antialias: options.antialias ?? true,
    preserveDrawingBuffer: options.preserveDrawingBuffer ?? false,
  });
  renderer.setPixelRatio(Math.min(window.devicePixelRatio, 2));
  renderer.setSize(window.innerWidth, window.innerHeight);
  renderer.outputColorSpace = THREE.SRGBColorSpace;
  renderer.toneMapping = THREE.ACESFilmicToneMapping;
  renderer.toneMappingExposure = 1.0;

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
  };
}
