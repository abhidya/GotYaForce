import * as THREE from "three";
import { BattleScene, type BorgAssets } from "./battleScene.js";
import type { BattleActorView } from "./battleView.js";
import { cloneDisposableModel } from "./borgPresentationAssets.js";
import type { ThreeAssetLoader } from "@gf/render";

function assert(ok: unknown, message: string): asserts ok {
  if (!ok) throw new Error(`battleScene morph selfcheck: ${message}`);
}

function view(combatFormId?: string, uid = "same-uid", afterimageSerial = 0): BattleActorView {
  return {
    uid, borgId: "pl0604", combatFormId, team: 0, ownerPlayer: "p1",
    alive: true, state: "idle", anim: "idle", pos: { x: 1, y: 2, z: 3 },
    vel: { x: 0, y: 0, z: 0 }, rotY: 0, lockTarget: null, allyLockTarget: null,
    dashActiveFrames: 0, chargeFrames: 0, meleeAnimStream: null, meleeSounds: null,
    lastHitImpactEffectId: undefined, lastHitAttackerTeam: undefined, slowHitTimer: 0, hasteHitTimer: 0,
    romAfterimage: afterimageSerial > 0
      ? { serial: afterimageSerial, pos: { x: 11, y: 12, z: 13 }, effectYaw: 0.25,
          baseScale: 0.5, effectId: 69, lifetimeFrames: 20, renderState: 0x1e }
      : undefined,
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

  scene.sync([view("pl0605", "same-uid", 1), view(undefined, "same-form-peer")]);
  const afterimageInternals = scene as unknown as { bankFxActors: Array<{
    node: THREE.Object3D; materials: THREE.Material[]; layerOpacity: number[]; ttl: number;
    scaleKeys?: ReadonlyArray<readonly number[]>; alphaKeys?: ReadonlyArray<readonly number[]>;
    romTransformFlags?: number;
  }> };
  const effect = afterimageInternals.bankFxActors.find((entry) => entry.ttl === 20 / 60);
  assert(effect, "zz_00b22f4_ presentation edge creates the subtype-1 20-frame bank effect");
  assert(effect.node.position.x === 11 && effect.node.position.y === 12 && effect.node.position.z === 13
    && effect.node.rotation.y === 0.25,
    "afterimage consumes the bridge-owned initialized position and random BAM yaw");
  assert(effect.romTransformFlags === 0x1e && effect.node.scale.x === 0.5,
    "FUN_80047aa4 consumes +0x84=0x1e as Y-rotation plus authored-scale transform flags");
  assert(effect.scaleKeys?.[0]?.join(",") === "0,0.5,0.5,0.5"
    && effect.scaleKeys?.[1]?.join(",") === "20,0.625,1.25,0.625"
    && effect.alphaKeys?.[0]?.join(",") === "0,1" && effect.alphaKeys?.[1]?.join(",") === "20,0",
    "afterimage uses exact 0x802fc588/0x802fc5b8 scale and alpha tracks");
  scene.sync([view("pl0605", "same-uid", 1), view(undefined, "same-form-peer")]);
  assert(afterimageInternals.bankFxActors.filter((entry) => entry.ttl === 20 / 60).length === 1,
    "presentation consumes each monotonic afterimage serial exactly once");
  scene.update(10 / 60);
  assert(Math.abs(effect.node.scale.x - 0.5625) < 1e-6 && Math.abs(effect.node.scale.y - 0.875) < 1e-6
    && effect.materials.every((material, index) =>
      Math.abs(material.opacity - (effect.layerOpacity[index] ?? 1) * 0.5) < 1e-6),
    "afterimage interpolates exact half-life scale/alpha values at frame 10");
  scene.update(10 / 60);
  assert(!afterimageInternals.bankFxActors.includes(effect),
    "afterimage exits and disposes when FUN_800b2b20 reaches frame 20");
}
