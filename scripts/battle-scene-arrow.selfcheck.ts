import * as THREE from "three";
import { BattleScene } from "../apps/game/src/sim/battleScene.js";
import type { BattleProjectileObservation, Projectile } from "../packages/combat/src/types.js";
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`Arrow scene: ${message}`);
}
const near = (a: number, b: number) => Math.abs(a - b) < 1e-6;
interface Actor {
  node: THREE.Group; material: THREE.Material; beam: boolean; arrowTether?: boolean;
  bankMaterials?: THREE.MeshBasicMaterial[]; bankLayerOpacity?: number[];
}
export async function runBattleSceneArrowSelfcheck(): Promise<void> {
  const load = THREE.TextureLoader.prototype.load;
  THREE.TextureLoader.prototype.load = function () { return new THREE.Texture(); };
  const root = new THREE.Group();
  let scene: BattleScene;
  try { scene = new BattleScene(root, { loadModel: async () => new THREE.Group(), loadClip: async () => null }); }
  finally { THREE.TextureLoader.prototype.load = load; }
  const internals = scene as unknown as {
    projectileActors: Map<string, Actor>; arrowTetherLayers: () => unknown;
    impactActors: unknown[]; bankFxActors: unknown[];
  };
  const source = {
    kind: "tether", ownerBorgId: 0, targetUid: "victim", life: 1, correction: null,
    anchor: { x: 10, y: 20, z: 30 }, endpoint: { x: 150, y: 20, z: 30 },
    drawBasis: { right: { x: 0, y: 1, z: 0 }, up: { x: 0, y: 0, z: 1 }, forward: { x: 1, y: 0, z: 0 } },
  };
  const shot = {
    uid: "tether", ownerUid: "owner", team: 0, pos: { x: -50, y: -50, z: -50 }, vel: { x: 0, y: 0, z: 1 },
    life: 1, damage: 1, hitstun: 0, knockback: 1, homingTurn: 0, homingTarget: null,
    hitRadius: 1, visualKind: "energy", arrowSource: source, romScale: [2, 3, 4],
    // Contradictory metadata cannot replace the source global37 or local12 distinction.
    flightVisual: { bankTexId: 12, teamTint: true, launchFxId: null },
  } as unknown as Projectile;
  const sync = (shots: readonly BattleProjectileObservation[]) => scene.sync([], shots);
  sync([shot]);
  const actor = internals.projectileActors.get(shot.uid)!;
  assert(actor.arrowTether && !actor.beam && actor.node.children.length === 2,
    "global37 uses both authored layers, no generic beam or extra endpoint effects");
  assert(actor.node.position.equals(new THREE.Vector3(10, 20, 30)), "fixed anchor overrides generic position");
  assert(actor.node.scale.equals(new THREE.Vector3(2, 3, 1)), "own XY scale, length/140 Z (not own Z)");
  assert(actor.bankMaterials![0]!.color.equals(new THREE.Color(0, 0, 1)), "team0 direct selector0");
  const opacity = actor.bankMaterials!.map(m => m.opacity);
  const forward = new THREE.Vector3(0, 0, 1).applyQuaternion(actor.node.quaternion);
  const up = new THREE.Vector3(0, 1, 0).applyQuaternion(actor.node.quaternion);
  assert(forward.distanceTo(new THREE.Vector3(1, 0, 0)) < 1e-6 && up.distanceTo(new THREE.Vector3(0, 0, 1)) < 1e-6,
    "source direction and transported up preserved, not velocity or world-up reconstruction");
  source.endpoint.x = 290; sync([shot]);
  assert(actor.node.scale.equals(new THREE.Vector3(2, 3, 2)) && actor.node.position.x === 10,
    "moving endpoint changes length while anchor stays fixed");
  const before = JSON.stringify(shot), matrix = actor.node.quaternion.clone();
  scene.update(100); sync([shot, shot]);
  assert(JSON.stringify(shot) === before && actor.node.quaternion.equals(matrix) && internals.projectileActors.size === 1,
    "pause, repeated sync and duplicate UID never mutate source or advance basis");
  assert(actor.bankMaterials!.every((m, i) => m.opacity === opacity[i]), "life1 has no invented fade");
  source.anchor = { x: 0, y: 0, z: 0 }; source.endpoint = { ...source.anchor };
  for (const length of [0, 0.0010000000474974513, 0.0010000000474974513 + 1e-9]) {
    source.endpoint.x = length; sync([shot]);
    const visible = length > 0.0010000000474974513;
    assert(actor.node.visible === visible && near(actor.node.scale.z, visible ? length / 140 : Math.fround(.01)),
      "exact source float threshold hides degenerate tether with .01 fallback Z");
  }
  let materials = 0, geometry = 0, dummy = 0;
  actor.bankMaterials!.forEach(m => m.addEventListener("dispose", () => materials++));
  actor.node.children.forEach(m => (m as THREE.Mesh).geometry.addEventListener("dispose", () => geometry++));
  actor.material.addEventListener("dispose", () => dummy++);
  const shared = (actor.node.children[0] as THREE.Mesh).geometry;
  sync([]); scene.clear(); scene.clear();
  assert(materials === 2 && dummy === 1 && geometry === 0 && !actor.node.parent,
    "omission/repeated clear dispose instance materials exactly once, never shared geometry");
  assert(!internals.impactActors.length && !internals.bankFxActors.length, "no fake endpoint/expiry effects");
  shot.team = 1; sync([shot]);
  const enemy = internals.projectileActors.get(shot.uid)!;
  assert((enemy.node.children[0] as THREE.Mesh).geometry === shared, "new lifetime shares geometry");
  assert(enemy.bankMaterials![0]!.color.equals(new THREE.Color(1, 0, .3984)), "team1 direct selector1");
  scene.clear();
  const available = internals.arrowTetherLayers; let lookups = 0;
  internals.arrowTetherLayers = () => { lookups++; return null; };
  sync([shot]); scene.update(100); sync([shot]);
  const missing = internals.projectileActors.get(shot.uid)!;
  assert(missing.arrowTether && !missing.beam && missing.node.children.length === 0 && lookups === 1,
    "missing global37 stays empty, no unrelated fallback or render-time retry");
  scene.clear(); internals.arrowTetherLayers = available;
  const flying = { ...shot, arrowSource: { kind: "arrow" } } as unknown as Projectile;
  sync([flying]);
  assert(internals.projectileActors.get(shot.uid)!.beam, "unexported owner-local12 retains explicit generic flight, not global12");
  sync([shot]); assert(internals.projectileActors.get(shot.uid)!.arrowTether, "same UID replaces generic with tether");
  sync([flying]); assert(internals.projectileActors.get(shot.uid)!.beam, "same UID restores generic after source removal");
  scene.clear();
  assert(geometry === 0, "all cleanup paths preserve cached geometry");
  console.log("Arrow scene selfcheck passed (global37, transported basis, anchor/endpoint, scale/threshold, material, no fade, pause, disposal, missing assets, owner-local12 guard; CPU scene graph only)");
}
