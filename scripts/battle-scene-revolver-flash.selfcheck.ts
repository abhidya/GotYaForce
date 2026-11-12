import * as THREE from "three";
import { readFileSync } from "node:fs";
import { BattleScene } from "../apps/game/src/sim/battleScene.js";
import { battleSceneState } from "../apps/game/src/sim/presentation.js";
import type { Battle, BattleProjectileObservation, RevolverLaunchFlashObservation } from "../packages/combat/src/types.js";

function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`Revolver flash scene: ${message}`);
}
const near = (a: number, b: number) => Math.abs(a - b) < 1e-6;
interface BankVisual { node: THREE.Group; materials: THREE.MeshBasicMaterial[] }
interface FlashActor { node: THREE.Group; layers: Map<92 | 35, BankVisual> }

export async function runBattleSceneRevolverFlashSelfcheck(): Promise<void> {
  const load = THREE.TextureLoader.prototype.load;
  THREE.TextureLoader.prototype.load = function () { return new THREE.Texture(); };
  const root = new THREE.Group();
  let scene: BattleScene;
  try { scene = new BattleScene(root, { loadModel: async () => new THREE.Group(), loadClip: async () => null }); }
  finally { THREE.TextureLoader.prototype.load = load; }
  const internals = scene as unknown as {
    revolverFlashActors: Map<string, FlashActor>; revolverFlashLayers: (modelId: 92 | 35) => unknown;
    projectileActors: Map<string, { node: THREE.Object3D; beam: boolean; bankMaterials?: THREE.Material[] }>;
    poweredFlashActors: Map<string, unknown>; bankFxActors: unknown[]; impactActors: unknown[];
  };
  const s = Math.SQRT1_2;
  const flash: RevolverLaunchFlashObservation = {
    uid: "launch-left", ownerUid: "owner", team: 0, effectId: 5,
    pos: { x: 101, y: 202, z: 303 },
    basis: { right: { x: 1, y: 0, z: 0 }, up: { x: 0, y: s, z: -s }, forward: { x: 0, y: s, z: s } },
    baseScale: 2,
    layers: [
      { modelId: 92, spin: 11 * 256 * Math.PI / 32768, ageFrames: 0, lifeFrames: 2 },
      { modelId: 35, spin: 73 * 256 * Math.PI / 32768, ageFrames: 0, lifeFrames: 7 },
    ],
  };
  const atAge = (ageFrames: number, source = flash): RevolverLaunchFlashObservation => ({
    ...source, layers: source.layers.map((layer) => ({ ...layer, ageFrames })),
  });
  const sync = (flashes: readonly RevolverLaunchFlashObservation[], projectiles: readonly BattleProjectileObservation[] = []) =>
    scene.sync([], projectiles, null, false, [], [], [], [], flashes);
  sync([flash]);
  const actor = internals.revolverFlashActors.get(flash.uid)!;
  const burst = actor.layers.get(92)!;
  const cone = actor.layers.get(35)!;
  assert(actor.node.children.length === 2 && burst.node.children.length === 2 && cone.node.children.length === 2,
    "effect5 has independent global92/global35 definition layers, each with both committed drawable meshes");
  const burstGeometry = (burst.node.children[0] as THREE.Mesh).geometry;
  const coneGeometry = (cone.node.children[0] as THREE.Mesh).geometry;
  assert(burstGeometry !== coneGeometry && burstGeometry.getAttribute("position").count > 0 && coneGeometry.getAttribute("position").count > 0,
    "effect5 reuses two distinct real bank geometries, not a sprite or Powered effect0");
  assert(actor.node.position.equals(new THREE.Vector3(101, 202, 303)) && actor.node.scale.equals(new THREE.Vector3(2, 2, 2)),
    "exact captured launch position and owner scale are applied once");
  assert(burst.node.scale.equals(new THREE.Vector3(1, 1, 1)) && cone.node.scale.equals(new THREE.Vector3(0, 0, 0)),
    "f0 uses source layer92 unit key and layer35 zero key without fabricated minimum size");
  const expectedForward = new THREE.Vector3(0, s, s);
  for (const [index, visual] of [burst, cone].entries()) {
    const phase = flash.layers[index]!.spin;
    // Layer35 begins at zero scale; inspect the parent-composed rotations without
    // decomposing that singular world scale.
    const rotation = actor.node.quaternion.clone().multiply(visual.node.quaternion);
    if (index === 0) assert(visual.node.getWorldQuaternion(new THREE.Quaternion()).angleTo(rotation) < 1e-6,
      "nonzero layer world transform agrees with composed basis");
    assert(new THREE.Vector3(0, 0, 1).applyQuaternion(rotation).distanceTo(expectedForward) < 1e-6,
      "tilted launch forward survives each independent local Z spin");
    assert(new THREE.Vector3(1, 0, 0).applyQuaternion(rotation).distanceTo(new THREE.Vector3(Math.cos(phase), s * Math.sin(phase), -s * Math.sin(phase))) < 1e-6,
      "source phase postmultiplies the captured basis, rather than world Z rotation");
    assert(visual.materials[0]!.color.equals(new THREE.Color(0, 0, 1)) && visual.materials[0]!.opacity === 1 && near(visual.materials[1]!.opacity, .999),
      "both models sample team0 matAnim and preserve unanimated drawable alpha");
  }
  assert(!burst.node.quaternion.equals(cone.node.quaternion), "each definition layer uses its own simulation phase");
  const snapshot = JSON.stringify(flash);
  const initialRotation = actor.node.quaternion.clone();
  scene.update(99); sync([flash, flash]);
  assert(internals.revolverFlashActors.size === 1 && internals.revolverFlashActors.get(flash.uid) === actor && actor.layers.size === 2,
    "repeated sync and duplicate UID do not duplicate either layer");
  assert(JSON.stringify(flash) === snapshot && actor.node.quaternion.equals(initialRotation) && burst.node.scale.x === 1 && cone.node.scale.x === 0,
    "render-only pause neither changes observations nor advances layer age or spin");
  sync([atAge(.5)]);
  assert(burst.node.scale.equals(new THREE.Vector3(.75, .75, .75)) && cone.node.scale.equals(new THREE.Vector3(.5, .5, .5)),
    "fractional source-frame interpolation is independent for each layer");
  sync([atAge(1)]);
  assert(burst.node.scale.equals(new THREE.Vector3(.5, .5, .5)) && cone.node.scale.equals(new THREE.Vector3(1, 1, 1)),
    "f1 uses the two authored keys, not effect0's quarter-size key");
  assert(burst.node.getWorldScale(new THREE.Vector3()).distanceTo(new THREE.Vector3(1, 1, 1)) < 1e-6 &&
    cone.node.getWorldScale(new THREE.Vector3()).distanceTo(new THREE.Vector3(2, 2, 2)) < 1e-6,
  "captured owner scale multiplies each authored key exactly once");
  let burstDisposals = 0, coneDisposals = 0, geometryDisposals = 0;
  for (const material of burst.materials) material.addEventListener("dispose", () => burstDisposals++);
  for (const material of cone.materials) material.addEventListener("dispose", () => coneDisposals++);
  burstGeometry.addEventListener("dispose", () => geometryDisposals++);
  coneGeometry.addEventListener("dispose", () => geometryDisposals++);
  sync([atAge(2)]); sync([atAge(2)]);
  assert(!actor.layers.has(92) && actor.layers.get(35) === cone && !burst.node.parent && burstDisposals === 2 && coneDisposals === 0,
    "f2 retires only the two-frame layer, disposes its materials once, and keeps the seven-frame layer");
  assert(near(cone.node.scale.x, 7 / 6) && cone.materials[0]!.opacity === 1 && near(cone.materials[1]!.opacity, .999),
    "f2 model35 expands with no lifetime-alpha fade");
  sync([atAge(4)]);
  assert(cone.node.scale.equals(new THREE.Vector3(1.5, 1.5, 1.5)) && cone.materials[0]!.opacity === 1,
    "f4 holds authored maximum size and full sampled alpha");
  sync([atAge(6)]);
  assert(near(cone.node.scale.x, .5) && near(cone.node.scale.y, .5) && near(cone.node.scale.z, 19 / 6) && cone.materials[0]!.opacity === 1,
    "last live frame stretches toward source z4 key without inventing a fade");
  sync([atAge(7)]); sync([atAge(700)]);
  assert(!actor.node.parent && internals.revolverFlashActors.size === 0 && coneDisposals === 2 && geometryDisposals === 0,
    "f7 and stale expired observations retire the last layer, never cached geometry");

  const right: RevolverLaunchFlashObservation = { ...flash, uid: "launch-right", team: 1, pos: { x: 501, y: 602, z: 703 } };
  sync([flash, right]);
  const rightActor = internals.revolverFlashActors.get(right.uid)!;
  assert(internals.revolverFlashActors.size === 2 && rightActor.layers.size === 2,
    "two source children produce two effects with four independent definition layers");
  for (const visual of rightActor.layers.values()) {
    assert(visual.materials[0]!.color.equals(new THREE.Color(1, 0, .3984)), "both models use team1 red-pink material selector");
  }
  assert((rightActor.layers.get(92)!.node.children[0] as THREE.Mesh).geometry === burstGeometry &&
    (rightActor.layers.get(35)!.node.children[0] as THREE.Mesh).geometry === coneGeometry,
  "later instances share surviving bank geometry");
  // The renderer only needs the source identity to reject the contradictory global visual;
  // full pending/flight behavior is covered by the combat constructor tests.
  const shell = {
    uid: "shell", ownerUid: "owner", team: 0, pos: { x: 1000, y: 2000, z: 3000 }, vel: { x: 0, y: 0, z: 60 },
    life: 600, hitRadius: 20, visualKind: "energy", flightVisual: { bankTexId: 11, teamTint: true, launchFxId: 5 },
    revolverSource: { kind: "pending" },
  } as unknown as BattleProjectileObservation;
  sync([flash, right], [shell]);
  const shellActor = internals.projectileActors.get(shell.uid)!;
  assert(shellActor.beam && !shellActor.bankMaterials && shellActor.node.children.length === 2,
    "owner-local11 remains explicit generic shell art, never global efct11 even with contradictory flightVisual");
  assert(rightActor.node.position.equals(new THREE.Vector3(501, 602, 703)) &&
    internals.revolverFlashActors.get(flash.uid)!.node.position.equals(new THREE.Vector3(101, 202, 303)),
  "moving shell cannot drag either captured launch transform");
  sync([right]);
  assert(internals.revolverFlashActors.size === 1 && rightActor.node.parent === root,
    "authoritative observation omission retires only the omitted launch");
  assert(internals.poweredFlashActors.size === 0 && internals.bankFxActors.length === 0 && internals.impactActors.length === 0,
    "effect5 never leaks into Powered/render-clock effects or generic impact fallbacks");
  scene.clear(); scene.clear();
  assert(internals.revolverFlashActors.size === 0 && rightActor.layers.size === 0 && geometryDisposals === 0,
    "repeated clear is safe and preserves shared geometry");
  sync([atAge(3)]);
  assert(internals.revolverFlashActors.get(flash.uid)!.layers.size === 1 && !internals.revolverFlashActors.get(flash.uid)!.layers.has(92),
    "first render after a skipped frame does not allocate the already expired layer92");
  scene.clear();

  const availableLayers = internals.revolverFlashLayers;
  const lookups: number[] = [];
  internals.revolverFlashLayers = (modelId) => { lookups.push(modelId); return null; };
  sync([flash]); scene.update(100); sync([flash]);
  const empty = internals.revolverFlashActors.get(flash.uid)!;
  assert([...empty.layers.values()].every((visual) => visual.node.children.length === 0) && lookups.join(",") === "92,35",
    "missing banks leave empty layers without invented art or repeated lookup");
  sync([atAge(2)]); sync([]);
  internals.revolverFlashLayers = (modelId) => modelId === 92 ? null : availableLayers.call(scene, modelId);
  sync([right]);
  const partial = internals.revolverFlashActors.get(right.uid)!;
  assert(partial.layers.get(92)!.node.children.length === 0 && partial.layers.get(35)!.node.children.length === 2,
    "one missing model does not suppress the independent available layer");
  scene.clear();
  internals.revolverFlashLayers = availableLayers;
  sync([flash]);
  assert(internals.revolverFlashActors.get(flash.uid)!.layers.get(92)!.node.children.length === 2,
    "a new launch resolves available models again after omission");
  scene.clear();
  assert(geometryDisposals === 0, "all expiry, omission, and clear paths retain cached geometry");

  const observation = { actors: [], projectiles: [], projectileDespawns: [], diverAuras: [], diverAuraTails: [], poweredLaunchFlashes: [], revolverLaunchFlashes: [flash] };
  const state = battleSceneState({ observe: () => observation } as unknown as Battle, null);
  assert(state.revolverLaunchFlashes === observation.revolverLaunchFlashes, "presentation forwards the exact simulation-owned list");
  const main = readFileSync(new URL("../apps/game/src/main.ts", import.meta.url), "utf8");
  assert(main.includes("initialScene.poweredLaunchFlashes,\n        initialScene.revolverLaunchFlashes,") &&
    main.includes("sceneState.poweredLaunchFlashes,\n    sceneState.revolverLaunchFlashes,"),
  "startup and frame synchronization both wire the dedicated effect5 observation");
  console.log("Revolver flash scene selfcheck passed (two layer meshes/lifetimes, basis/owner scale, independent phases, team alpha, pause, owner-bank fallback, disposal, missing assets, wiring)");
}
