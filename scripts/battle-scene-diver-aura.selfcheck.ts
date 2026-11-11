import * as THREE from "three";
import { BattleScene } from "../apps/game/src/sim/battleScene.js";
import { createBattle, battleStateForSelfcheck } from "../packages/combat/src/battle.js";
import { emptyInput } from "../packages/combat/src/types.js";
import type { BorgStats } from "../packages/combat/src/stats.js";
import borgs from "../packages/assets/data/borgs.json";
import { battleSceneState } from "../apps/game/src/sim/presentation.js";
import type { BattleProjectileObservation, DiverAuraChild } from "../packages/combat/src/types.js";

function assert(ok: unknown, message: string): asserts ok {
  if (!ok) throw new Error(`Diver aura scene: ${message}`);
}
const near = (a: number, b: number) => Math.abs(a - b) < 1e-6;

export async function runBattleSceneDiverAuraSelfcheck(): Promise<void> {
  // TextureLoader is unrelated to the untextured committed mesh78.
  const load = THREE.TextureLoader.prototype.load;
  THREE.TextureLoader.prototype.load = function (): THREE.Texture { return new THREE.Texture(); };
  const root = new THREE.Group();
  const scene = new BattleScene(root, {
    loadModel: async () => new THREE.Group(), loadClip: async () => null,
  });
  THREE.TextureLoader.prototype.load = load;
  const internals = scene as unknown as {
    diverAuraActors: Map<string, { node: THREE.Group; materials: THREE.MeshBasicMaterial[] }>;
    projectileActors: Map<string, { node: THREE.Object3D; beam: boolean }>;
    impactActors: unknown[]; bankFxActors: unknown[];
  };
  // Synthetic observation exercises scale propagation, including source init .01.
  // Real X is tested below; its first observable update already uses owner scale.
  const child: DiverAuraChild = {
    uid: "aura", ownerUid: "owner", ownerFormId: "pl0a04", team: 0,
    subtype: 0, pos: { x: 10, y: 20, z: 30 }, remainingFrames: 1140,
    hitRadius: 100, bankTexId: 78, visualVariant: 0, visualScale: 0.01,
  };
  const sync = (children: DiverAuraChild[], projectiles: BattleProjectileObservation[] = []) =>
    scene.sync([], projectiles, null, false, [], children);
  sync([child]);
  const aura = internals.diverAuraActors.get(child.uid)!;
  assert(aura && aura.node.children.length > 0, "child creates mesh bank node");
  const mesh = aura.node.children[0] as THREE.Mesh;
  assert(mesh.isMesh && mesh.geometry.getAttribute("position").count === 134,
    "committed mesh78 geometry, not sprite/crossed projectile planes");
  mesh.geometry.computeBoundingBox();
  const size = mesh.geometry.boundingBox!.getSize(new THREE.Vector3());
  assert(size.x > 0 && size.y > 0 && size.z > 0, "authored volume has extent on all axes");
  assert(aura.node.position.equals(new THREE.Vector3(10, 20, 30)), "root position copied");
  assert(aura.node.scale.equals(new THREE.Vector3(.01, .01, .01)), "synthetic initial-scale observation copied");
  const material = aura.materials[0]!;
  assert(near(material.color.b, 1) && near(material.opacity, .25), "Jelly selector0 authored blue/alpha");
  assert(material.transparent && !material.depthWrite && material.blending === THREE.NormalBlending,
    "authored translucent surface");
  const moved = { ...child, pos: { x: -70, y: 40, z: 80 }, visualScale: 1.5, remainingFrames: 1 };
  sync([moved]); scene.update(3); sync([{ ...moved, remainingFrames: 1140 }]);
  assert(internals.diverAuraActors.get(child.uid) === aura, "refresh keeps one node");
  assert(aura.node.position.equals(new THREE.Vector3(-70, 40, 80)), "owner movement followed");
  assert(aura.node.scale.equals(new THREE.Vector3(1.5, 1.5, 1.5)), "absolute scale does not compound/pulse");
  assert(near(material.opacity, .25), "lifetime never applies ordinary projectile fade");
  let materialDisposals = 0, geometryDisposals = 0;
  material.addEventListener("dispose", () => { materialDisposals++; });
  mesh.geometry.addEventListener("dispose", () => { geometryDisposals++; });
  sync([]);
  assert(!aura.node.parent && internals.diverAuraActors.size === 0, "expiry/death/form removal detaches child");
  assert(materialDisposals === 1 && geometryDisposals === 0, "dispose own material, retain shared bank geometry");
  assert(internals.impactActors.length === 0 && internals.bankFxActors.length === 0, "removal makes no hit puff");
  for (const [variant, expected] of [[1, [0, 0, .2, .6016]], [2, [.85, 0, .4, .25]]] as const) {
    sync([{ ...child, uid: `variant${variant}`, visualVariant: variant }]);
    const m = internals.diverAuraActors.get(`variant${variant}`)!.materials[0]!;
    assert(near(m.color.r, expected[0]) && near(m.color.g, expected[1]) && near(m.color.b, expected[2]) && near(m.opacity, expected[3]),
      `selector${variant} samples authored material rather than team tint`);
  }
  // Exercise ordinary bolt separately, with a minimal complete-enough render observation.
  const bolt = { uid: "bolt", ownerUid: "shooter", team: 0, pos: { x: 1, y: 2, z: 3 },
    vel: { x: 5, y: 0, z: 10 }, life: 100, hitRadius: 20, visualKind: "energy",
    flightVisual: null, hitConfirmedThisFrame: false } as BattleProjectileObservation;
  sync([child], [bolt]);
  assert(internals.projectileActors.get("bolt")?.beam === true, "ordinary energy bolt still gets beam rig");
  assert(internals.diverAuraActors.get("aura")!.node.children[0] instanceof THREE.Mesh,
    "aura remains separate while normal projectile is live");
  const finalAura = internals.diverAuraActors.get("aura")!;
  let clearDisposals = 0;
  finalAura.materials[0]!.addEventListener("dispose", () => { clearDisposals++; });
  scene.clear(); scene.clear();
  assert(!finalAura.node.parent && internals.diverAuraActors.size === 0 && internals.projectileActors.size === 0,
    "battle clear removes both independent lifecycles");
  assert(clearDisposals === 1 && geometryDisposals === 0, "repeated clear is safe");
  // Real X input reaches Battle's dedicated child, immutable snapshot and app
  // presentation adapter. No injected renderer-only replacement effect.
  for (const id of ["pl0805", "pl080e", "pl080d"]) {
    const battle = createBattle({ stageId: "st00", forces: [
      { team: 0, ownerPlayer: "p1", borgIds: [id] },
      { team: 1, ownerPlayer: "p2", borgIds: ["pl0804"] },
    ], bounds: { x: 2000, z: 2000 } }, borgs.borgs as BorgStats[]);
    const tick = (special = false) => battle.step(1 / 60, {
      p1: { ...emptyInput(), special }, p2: emptyInput(),
    });
    for (let i = 0; i < 40; i++) tick();
    tick(true);
    for (let i = 0; i < 90 && battle.observe().diverAuras.length === 0; i++) tick();
    assert(battle.observe().diverAuras.length === 1, `${id} real X creates child`);
    const snapshot = battleSceneState(battle, null);
    scene.sync([], snapshot.projectiles, null, false, snapshot.projectileDespawns, snapshot.diverAuras);
    const actual = snapshot.diverAuras[0]!;
    const actualNode = internals.diverAuraActors.get(actual.uid)!.node;
    assert(actualNode.position.equals(new THREE.Vector3(actual.pos.x, actual.pos.y, actual.pos.z)),
      `${id} Battle child reaches scene`);
    const owner = battleStateForSelfcheck(battle).borgs[0]!;
    owner.pos.x += 100;
    tick();
    const movedSnapshot = battleSceneState(battle, null);
    scene.sync([], movedSnapshot.projectiles, null, false, movedSnapshot.projectileDespawns, movedSnapshot.diverAuras);
    assert(internals.diverAuraActors.get(actual.uid)!.node === actualNode && actualNode.position.x === owner.pos.x,
      `${id} real child follows updated owner`);
    owner.hp = 0; owner.alive = false;
    tick();
    const deadSnapshot = battleSceneState(battle, null);
    scene.sync([], [], null, false, [], deadSnapshot.diverAuras);
    assert(!actualNode.parent, `${id} owner death removes real child visual`);
    scene.clear();
  }
  console.log("Diver aura Three scene selfcheck: PASS");
}
