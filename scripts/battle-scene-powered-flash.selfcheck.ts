import * as THREE from "three";
import { readFileSync } from "node:fs";
import { BattleScene } from "../apps/game/src/sim/battleScene.js";
import { battleSceneState } from "../apps/game/src/sim/presentation.js";
import type { Battle, PoweredLaunchFlashObservation } from "../packages/combat/src/types.js";

function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`Powered flash scene: ${message}`);
}
const near = (a: number, b: number) => Math.abs(a - b) < 1e-6;
export async function runBattleScenePoweredFlashSelfcheck(): Promise<void> {
  const load = THREE.TextureLoader.prototype.load;
  THREE.TextureLoader.prototype.load = function () { return new THREE.Texture(); };
  const root = new THREE.Group();
  let scene: BattleScene;
  try { scene = new BattleScene(root, { loadModel: async () => new THREE.Group(), loadClip: async () => null }); }
  finally { THREE.TextureLoader.prototype.load = load; }
  type FlashActor = { node: THREE.Group; materials: THREE.MeshBasicMaterial[] };
  const internals = scene as unknown as {
    poweredFlashActors: Map<string, FlashActor>; poweredFlashLayers: () => unknown;
    bankFxActors: unknown[]; impactActors: unknown[];
  };
  const s = Math.SQRT1_2;
  const flash: PoweredLaunchFlashObservation = {
    uid: "launch", ownerUid: "owner", team: 0, cause: "normal", effectId: 0,
    pos: { x: 101, y: 202, z: 303 },
    basis: { right: { x: 1, y: 0, z: 0 }, up: { x: 0, y: s, z: -s }, forward: { x: 0, y: s, z: s } },
    spin: Math.PI / 3, ageFrames: 0, lifeFrames: 4,
  };
  const sync = (flashes: readonly PoweredLaunchFlashObservation[]) => scene.sync([], [], null, false, [], [], [], flashes);
  sync([flash]);
  const actor = internals.poweredFlashActors.get("launch")!;
  assert(actor && actor.node.children.length === 2, "one id0 flash has both authored bank35 drawable layers");
  const mesh = actor.node.children[0] as THREE.Mesh;
  assert(mesh.isMesh && mesh.geometry.getAttribute("position").count > 0, "actual committed geometry, not sprite");
  assert(actor.node.position.equals(new THREE.Vector3(101, 202, 303)), "exact world position without muzzle heuristic offsets");
  assert(new THREE.Vector3(0, 0, 1).applyQuaternion(actor.node.quaternion).distanceTo(new THREE.Vector3(0, s, s)) < 1e-6, "full tilted forward basis survives local Z spin");
  const expectedX = new THREE.Vector3(Math.cos(flash.spin), s * Math.sin(flash.spin), -s * Math.sin(flash.spin));
  assert(new THREE.Vector3(1, 0, 0).applyQuaternion(actor.node.quaternion).distanceTo(expectedX) < 1e-6, "local Z spin is postmultiplied into full basis");
  assert(actor.node.scale.equals(new THREE.Vector3(1, 1, 1)), "source launch unit scale");
  assert(actor.materials[0]!.color.equals(new THREE.Color(0, 0, 1)), "team0 authored matAnim blue");
  assert(near(actor.materials[1]!.opacity, .999), "unanimated layer retains authored opacity");
  const initialQ = actor.node.quaternion.clone();
  scene.update(99); sync([flash, flash]);
  assert(internals.poweredFlashActors.size === 1 && internals.poweredFlashActors.get("launch") === actor, "repeated observation/duplicate uid does not allocate");
  assert(actor.node.quaternion.equals(initialQ) && actor.node.scale.x === 1, "render-only/pause never ages or accumulates spin");
  sync([{ ...flash, ageFrames: 1 }]);
  assert(actor.node.scale.equals(new THREE.Vector3(.25, .25, .25)) && actor.materials[0]!.opacity === 1, "f1 source scale/alpha");
  sync([{ ...flash, ageFrames: 2 }]);
  assert(near(actor.node.scale.x, 1 / 6) && actor.node.scale.z === .25 && near(actor.materials[0]!.opacity, 2 / 3), "f2 exact anisotropic and alpha interpolation");
  sync([{ ...flash, ageFrames: 3 }]);
  assert(near(actor.node.scale.x, 1 / 12) && near(actor.materials[0]!.opacity, 1 / 3), "last live frame source curves");
  let materialDisposals = 0, geometryDisposals = 0;
  for (const m of actor.materials) m.addEventListener("dispose", () => materialDisposals++);
  mesh.geometry.addEventListener("dispose", () => geometryDisposals++);
  sync([{ ...flash, ageFrames: 4 }]); sync([{ ...flash, ageFrames: 40 }]);
  assert(!actor.node.parent && internals.poweredFlashActors.size === 0, "expired/stale records cannot restart nodes");
  assert(materialDisposals === 2 && geometryDisposals === 0, "expiry disposes owned materials once, never bank geometry");
  const red = { ...flash, uid: "red", team: 1, cause: "primary" as const };
  const split = { ...flash, uid: "split", cause: "split" as const };
  sync([red, split]);
  assert(internals.poweredFlashActors.size === 2, "primary and split observations each render exactly one flash");
  const redActor = internals.poweredFlashActors.get("red")!;
  assert(redActor.materials[0]!.color.equals(new THREE.Color(1, 0, .3984)), "team1 authored matAnim red-pink");
  sync([split]);
  assert(!redActor.node.parent, "authoritative list omission immediately retires node");
  assert(internals.bankFxActors.length === 0 && internals.impactActors.length === 0, "no render-clock flashes or generic impact fallbacks");
  scene.clear(); scene.clear();
  assert(internals.poweredFlashActors.size === 0 && geometryDisposals === 0, "repeated clear safe and shared geometry retained");
  const layers = internals.poweredFlashLayers;
  let lookups = 0;
  internals.poweredFlashLayers = () => { lookups++; return null; };
  sync([flash]); scene.update(100); sync([flash]);
  const empty = internals.poweredFlashActors.get("launch")!;
  assert(empty.node.children.length === 0 && lookups === 1, "missing static bank is omitted without invented fallback or repeat retry");
  sync([]); internals.poweredFlashLayers = layers; sync([red]);
  assert(internals.poweredFlashActors.get("red")!.node.children.length === 2, "new launch can resolve available bank again");
  scene.clear();
  const observation = { actors: [], projectiles: [], projectileDespawns: [], diverAuras: [], diverAuraTails: [], poweredLaunchFlashes: [flash] };
  const state = battleSceneState({ observe: () => observation } as unknown as Battle, null);
  assert(state.poweredLaunchFlashes === observation.poweredLaunchFlashes, "presentation forwards exact simulation list");
  const main = readFileSync(new URL("../apps/game/src/main.ts", import.meta.url), "utf8");
  assert(main.includes("initialScene.diverAuraTails,\n        initialScene.poweredLaunchFlashes,") && main.includes("sceneState.diverAuraTails,\n    sceneState.poweredLaunchFlashes,"), "both game startup and frame sync wire flash observation");
  console.log("Powered flash scene selfcheck passed (mesh/basis/spin/team/curves/pause/lifecycle/missing-bank/wiring)");
}
