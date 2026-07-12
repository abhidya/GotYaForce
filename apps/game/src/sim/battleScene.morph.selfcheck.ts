import * as THREE from "three";
import { BattleScene, type BorgAssets } from "./battleScene.js";
import type { BattleActorView } from "./battleView.js";
import { cloneDisposableModel } from "./borgPresentationAssets.js";
import type { ThreeAssetLoader } from "@gf/render";

function assert(ok: unknown, message: string): asserts ok {
  if (!ok) throw new Error(`battleScene morph selfcheck: ${message}`);
}

function view(combatFormId?: string, uid = "same-uid"): BattleActorView {
  return {
    uid, borgId: "pl0604", combatFormId, team: 0, ownerPlayer: "p1",
    alive: true, state: "idle", anim: "idle", pos: { x: 1, y: 2, z: 3 },
    vel: { x: 0, y: 0, z: 0 }, rotY: 0, lockTarget: null, allyLockTarget: null,
    dashActiveFrames: 0, chargeFrames: 0, meleeAnimStream: null, meleeSounds: null,
    lastHitImpactEffectId: undefined, lastHitAttackerTeam: undefined, slowHitTimer: 0, hasteHitTimer: 0,
  };
}

export async function runBattleSceneMorphSelfcheck(): Promise<void> {
  // Constructor FX texture loads are irrelevant to actor lifecycle and require a browser.
  THREE.TextureLoader.prototype.load = function load(): THREE.Texture { return new THREE.Texture(); };
  const loadedModels: string[] = [];
  const loadedClips: string[] = [];
  let disposedGeometry = 0;
  let disposedMaterial = 0;
  const sourceModels = new Map<string, THREE.Object3D>();
  const returnedModels: THREE.Object3D[] = [];
  const cloneLoader = {
    manager: new THREE.LoadingManager(),
    async loadGlbScene() { throw new Error("unused in selfcheck"); },
    cloneModel(source: THREE.Object3D) { return source.clone(true); },
  } satisfies ThreeAssetLoader;
  const assets: BorgAssets = {
    async loadModel(id) {
      loadedModels.push(id);
      let source = sourceModels.get(id);
      if (!source) {
        source = new THREE.Group(); source.name = `${id}-source`;
        source.add(new THREE.Mesh(new THREE.BoxGeometry(), new THREE.MeshBasicMaterial()));
        sourceModels.set(id, source);
      }
      const model = cloneDisposableModel(cloneLoader, source); model.name = id;
      const mesh = model.children[0] as THREE.Mesh;
      const geometry = mesh.geometry;
      const material = mesh.material as THREE.Material;
      const gd = geometry.dispose.bind(geometry);
      const md = material.dispose.bind(material);
      geometry.dispose = () => { disposedGeometry += 1; gd(); };
      material.dispose = () => { disposedMaterial += 1; md(); };
      returnedModels.push(model);
      return model;
    },
    async loadClip(id, slot) {
      loadedClips.push(`${id}:${slot}`);
      return new THREE.AnimationClip(`${id}:${slot}`, 1, []);
    },
  };
  const root = new THREE.Group();
  const scene = new BattleScene(root, assets);
  scene.sync([view(), view(undefined, "same-form-peer")]);
  await Promise.resolve(); await Promise.resolve();
  scene.sync([view(), view(undefined, "same-form-peer")]);
  await Promise.resolve(); await Promise.resolve();

  const internals = scene as unknown as { actors: Map<string, { group: THREE.Group; mixer: THREE.AnimationMixer | null; actions: Record<string, THREE.AnimationAction>; borgId: string }> };
  const before = internals.actors.get("same-uid");
  assert(before?.borgId === "pl0604" && before.group.children.some((c) => c.name === "pl0604"), "base model attached");
  const oldGroup = before.group;
  const oldMixer = before.mixer;
  const firstMesh = returnedModels[0]!.children[0] as THREE.Mesh;
  const peerMesh = returnedModels[1]!.children[0] as THREE.Mesh;
  assert(firstMesh.geometry !== peerMesh.geometry && firstMesh.material !== peerMesh.material,
    "two same-form actors own distinct disposable geometry/material clones");

  scene.sync([view("pl0605"), view(undefined, "same-form-peer")]);
  assert(internals.actors.get("same-uid") === before && before.group === oldGroup, "same actor/group retained by UID");
  assert(disposedGeometry === 1 && disposedMaterial === 1, "old model geometry/material disposed on form edge");
  assert(peerMesh.geometry.attributes.position !== undefined && peerMesh.material instanceof THREE.Material,
    "morph disposal leaves the same-form peer model resources valid");
  assert(before.mixer !== oldMixer && Object.keys(before.actions).length === 0, "old mixer/clip action cache discarded");
  await Promise.resolve(); await Promise.resolve();
  scene.sync([view("pl0605"), view(undefined, "same-form-peer")]);
  await Promise.resolve(); await Promise.resolve();

  const after = internals.actors.get("same-uid");
  assert(after?.borgId === "pl0605" && after.group.children.some((c) => c.name === "pl0605"), "new internal model attached");
  assert(loadedModels.join(",") === "pl0604,pl0604,pl0605", "model resolver selected two cached-form instances then internal form");
  assert(loadedClips.includes("pl0604:idle"), "base clip resolver ran for both same-form actors");
}
