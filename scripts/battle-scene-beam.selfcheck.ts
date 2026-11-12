import * as THREE from "three";
import { BattleScene } from "../apps/game/src/sim/battleScene.js";
import type { BattleProjectileObservation, Projectile } from "../packages/combat/src/types.js";
function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`Beam scene: ${message}`);
}
const near = (a: number, b: number) => Math.abs(a - b) < 1e-6;
interface Actor {
  node: THREE.Group; material: THREE.Material; beam: boolean; sustainedBeam?: boolean;
  bankMaterials?: THREE.MeshBasicMaterial[]; bankLayerOpacity?: number[];
}
export async function runBattleSceneBeamSelfcheck(): Promise<void> {
  const load = THREE.TextureLoader.prototype.load;
  THREE.TextureLoader.prototype.load = function () { return new THREE.Texture(); };
  const root = new THREE.Group();
  let scene: BattleScene;
  try { scene = new BattleScene(root, { loadModel: async () => new THREE.Group(), loadClip: async () => null }); }
  finally { THREE.TextureLoader.prototype.load = load; }
  const internals = scene as unknown as {
    projectileActors: Map<string, Actor>; sustainedBeamLayers: () => unknown;
    impactActors: unknown[]; bankFxActors: unknown[];
  };
  const source = {
    phase: "init", age: 0, tailAge: 0, scale: 0, ownerScale: 2,
    origin: { x: 10, y: 20, z: 30 }, direction: { x: 0, y: 0, z: 1 },
    drawBasis: { right: { x: 0, y: 1, z: 0 }, up: { x: 0, y: 0, z: 1 }, forward: { x: 1, y: 0, z: 0 } },
    start: { x: 0, y: 0, z: 0 }, end: { x: 0, y: 0, z: 1 },
    tailStartScale: 0, targetUid: null, pulse: false,
  };
  const shot = {
    uid: "beam", ownerUid: "owner", team: 0, pos: { ...source.origin }, vel: { x: 0, y: 0, z: 1 },
    life: 1, damage: 1, hitstun: 0, knockback: 1, homingTurn: 0, homingTarget: null,
    hitRadius: 1, visualKind: "energy", beamSource: source,
    // Contradictory generic metadata must not override the specific source renderer.
    flightVisual: { bankTexId: 35, teamTint: true, launchFxId: null },
  } as unknown as Projectile;
  const sync = (shots: readonly BattleProjectileObservation[]) => scene.sync([], shots);
  sync([shot]);
  const actor = internals.projectileActors.get(shot.uid)!;
  assert(actor.sustainedBeam && !actor.beam && actor.node.children.length === 3,
    "global84 uses all three authored layers without generic crossed planes or secondary effects");
  assert(actor.node.scale.equals(new THREE.Vector3()), "init zero scale");
  const opacity = actor.bankMaterials!.map(m => m.opacity);
  assert(actor.bankMaterials![0]!.color.equals(new THREE.Color(0, .2, .5)) && opacity[0] === .5,
    "team0 samples source material frame0 and authored half-alpha");
  source.phase = "active";
  for (const age of [1, 5, 14, 15, 16, 120]) {
    source.age = age; source.scale = Math.min(age / 15 * 3, 3);
    sync([shot]);
    const z = source.scale * 2, xy = z * ((age & 1) ? Math.fround(1.2) : 1);
    assert(near(actor.node.scale.x, xy) && near(actor.node.scale.y, xy) && near(actor.node.scale.z, z),
      `f${age} source scale, owner scale and parity`);
    assert(actor.bankMaterials!.every((m, i) => m.opacity === opacity[i]), "no generic life fade");
  }
  assert(actor.node.position.equals(new THREE.Vector3(10, 20, 30)), "source origin overrides flight position");
  const actualForward = new THREE.Vector3(0, 0, 1).applyQuaternion(actor.node.quaternion);
  const actualUp = new THREE.Vector3(0, 1, 0).applyQuaternion(actor.node.quaternion);
  assert(actualForward.distanceTo(new THREE.Vector3(1, 0, 0)) < 1e-6 && actualUp.distanceTo(new THREE.Vector3(0, 0, 1)) < 1e-6,
    "full attachment basis preserved, not aim-corrected collision direction or velocity");
  const before = JSON.stringify(shot), matrix = actor.node.quaternion.clone();
  scene.update(100); sync([shot, shot]);
  assert(JSON.stringify(shot) === before && actor.node.quaternion.equals(matrix) && internals.projectileActors.size === 1,
    "pause, repeated sync and duplicate UID do not mutate source or create extra actors");
  source.phase = "tail";
  for (let age = 1; age < 10; age++) {
    source.tailAge = age; source.scale = 3 - age / 10 * 3;
    sync([shot]);
    assert(near(actor.node.scale.z, source.scale * 2) && near(actor.node.scale.x, source.scale * 2),
      "tail follows uniform final draw matrix and frozen active parity");
    assert(actor.bankMaterials!.every((m, i) => m.opacity === opacity[i]), "tail never invents alpha fade");
  }
  let materials = 0, geometry = 0, dummy = 0;
  actor.bankMaterials!.forEach(m => m.addEventListener("dispose", () => materials++));
  actor.node.children.forEach(m => (m as THREE.Mesh).geometry.addEventListener("dispose", () => geometry++));
  actor.material.addEventListener("dispose", () => dummy++);
  const shared = (actor.node.children[0] as THREE.Mesh).geometry;
  sync([]); scene.clear(); scene.clear();
  assert(materials === 3 && dummy === 1 && geometry === 0 && !actor.node.parent,
    "expiry/owner-stop omission and repeated clear dispose per-instance materials once, preserve geometry");
  assert(!internals.impactActors.length && !internals.bankFxActors.length, "omission creates no fake impact");
  shot.team = 1; sync([shot]);
  const enemy = internals.projectileActors.get(shot.uid)!;
  assert((enemy.node.children[0] as THREE.Mesh).geometry === shared, "later lifetime reuses geometry");
  assert(enemy.bankMaterials![0]!.color.equals(new THREE.Color(.5, 0, 0)) && enemy.bankMaterials![0]!.opacity === .5,
    "team1 samples source material frame1 and keeps authored half-alpha");
  scene.clear();
  const available = internals.sustainedBeamLayers; let lookups = 0;
  internals.sustainedBeamLayers = () => { lookups++; return null; };
  sync([shot]); scene.update(100); sync([shot]);
  const missing = internals.projectileActors.get(shot.uid)!;
  assert(missing.sustainedBeam && !missing.beam && missing.node.children.length === 0 && lookups === 1,
    "missing global84 stays empty, no generic fallback or render-time retry");
  scene.clear(); internals.sustainedBeamLayers = available;
  const ordinary = { ...shot, uid: "ordinary", beamSource: undefined, flightVisual: undefined } as unknown as Projectile;
  sync([ordinary]);
  assert(internals.projectileActors.get("ordinary")!.beam, "ordinary energy retains generic renderer");
  sync([{ ...shot, uid: "ordinary" }]);
  assert(internals.projectileActors.get("ordinary")!.sustainedBeam, "same UID source adoption replaces generic actor");
  sync([ordinary]);
  assert(internals.projectileActors.get("ordinary")!.beam, "same UID source removal restores generic actor");
  scene.clear();
  assert(geometry === 0, "all lifetimes preserve cached geometry");
  console.log("Beam scene selfcheck passed (global84, basis, curves, material, pause, tail, owner omission, disposal, missing assets, ordinary regression; CPU scene graph only)");
}
