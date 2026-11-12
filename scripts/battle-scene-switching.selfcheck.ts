import * as THREE from "three";
import { BattleScene } from "../apps/game/src/sim/battleScene.js";
import { createSwitchingField, stepSwitchingField } from "../packages/combat/src/switchingField.js";
import type { SwitchingFieldContext } from "../packages/combat/src/switchingField.js";
import type { BattleProjectileObservation, Projectile, ProjectileDespawnObservation } from "../packages/combat/src/types.js";

function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`[switchingScene] ${message}`);
}
function near(actual: number, expected: number, message: string): void {
  assert(Math.abs(actual - expected) < 1e-6, `${message}: ${actual} != ${expected}`);
}
interface BankVisual {
  node: THREE.Group;
  materials: THREE.MeshBasicMaterial[];
  layerOpacity: number[];
}
interface ProjectileActor {
  node: THREE.Object3D;
  material: THREE.Material;
  beam: boolean;
  bankMaterials?: THREE.MeshBasicMaterial[];
  switchingField?: { subphase: 0 | 1; inner: BankVisual; outer?: BankVisual };
}
const context: SwitchingFieldContext = { initialPosition: () => ({ x: 101, y: 202, z: 303 }) };
function projectile(uid: string, team: 0 | 1 = 0): Projectile {
  return {
    uid, ownerUid: "owner", team, pos: { x: 900, y: 900, z: 900 }, vel: { x: 1, y: 4000, z: 2 },
    life: 1, damage: 1, hitstun: 0, knockback: 0, homingTurn: 0, homingTarget: null,
    hitRadius: 540, visualKind: "energy", flightVisual: { bankTexId: 10, teamTint: true, launchFxId: null },
    switchingSource: { kind: "field", field: createSwitchingField(3, 2),
      ownerBorgId: "pl0009", ownerFormId: "pl0009", captureFlagsD0: 4, contactPending: false },
  };
}
function tick(projectile: Projectile, overrides: Partial<SwitchingFieldContext> = {}): void {
  const source = projectile.switchingSource!;
  source.field = stepSwitchingField(source.field, { ...context, ...overrides });
}
function activate(projectile: Projectile): void {
  for (let i = 0; i < 63 && projectile.switchingSource!.field.subphase === 0; i++) tick(projectile);
  assert(projectile.switchingSource!.field.subphase === 1, "fixture reaches active field");
}
function geometry(visual: BankVisual): THREE.BufferGeometry {
  return (visual.node.children[0] as THREE.Mesh).geometry;
}

export async function runBattleSceneSwitchingSelfcheck(): Promise<void> {
  const load = THREE.TextureLoader.prototype.load;
  THREE.TextureLoader.prototype.load = function () { return new THREE.Texture(); };
  const root = new THREE.Group();
  let scene: BattleScene;
  try { scene = new BattleScene(root, { loadModel: async () => new THREE.Group(), loadClip: async () => null }); }
  finally { THREE.TextureLoader.prototype.load = load; }
  const internals = scene as unknown as {
    projectileActors: Map<string, ProjectileActor>;
    switchingFieldLayers: (modelId: number) => unknown;
    impactActors: unknown[];
    bankFxActors: unknown[];
  };
  const sync = (shots: readonly BattleProjectileObservation[], despawns: readonly ProjectileDespawnObservation[] = []) =>
    scene.sync([], shots, null, false, despawns);
  const get = (uid: string) => {
    const actor = internals.projectileActors.get(uid);
    assert(actor, `actor ${uid} exists`);
    return actor;
  };
  const materialDisposals = new Map<THREE.Material, number>();
  let geometryDisposals = 0;
  const watch = (actor: ProjectileActor) => {
    const owned = [actor.material, ...(actor.switchingField?.inner.materials ?? []),
      ...(actor.switchingField?.outer?.materials ?? [])];
    for (const material of owned) {
      assert(!materialDisposals.has(material), "each field instance owns fresh materials");
      materialDisposals.set(material, 0);
      material.addEventListener("dispose", () => materialDisposals.set(material, materialDisposals.get(material)! + 1));
    }
    actor.node.traverse(node => {
      if (node instanceof THREE.Mesh) node.geometry.addEventListener("dispose", () => geometryDisposals++);
    });
  };
  const retired = (actor: ProjectileActor, message: string) => {
    const owned = [actor.material, ...(actor.switchingField?.inner.materials ?? []),
      ...(actor.switchingField?.outer?.materials ?? [])];
    assert(!actor.node.parent && owned.every(material => materialDisposals.get(material) === 1), message);
  };

  const first = projectile("first");
  sync([first]);
  const warning = get(first.uid);
  watch(warning);
  assert(!warning.node.visible && warning.switchingField?.subphase === 0 && !warning.beam && !warning.bankMaterials,
    "pending field is hidden and never resolves contradictory global10 or flying beam");
  tick(first); sync([first]);
  assert(get(first.uid) === warning && warning.node.visible && warning.switchingField.inner.node.children.length === 1,
    "INIT exposes global150 warning without replacing its actor");
  assert(warning.switchingField.inner.node.name.endsWith(":model150"), "warning uses source model150");
  assert(warning.node.position.equals(new THREE.Vector3(101, 202, 303)), "field position overrides generic projectile pose");
  assert(warning.node.scale.equals(new THREE.Vector3(1, 1, 1)), "INIT resets draw scale, independent of owner model3 and collision2");
  const warningGeometry = geometry(warning.switchingField.inner);
  assert(warningGeometry.getAttribute("position").count === 32, "source warning geometry has32 vertices");
  assert(warning.switchingField.inner.materials[0]!.color.equals(new THREE.Color(0, .3984, 1)),
    "team0 samples direct material frame0, not generic frame1");
  for (let i = 0; i < 60; i++) tick(first);
  sync([first]);
  assert(first.switchingSource!.field.timer === 0 && first.switchingSource!.field.subphase === 0 && get(first.uid) === warning,
    "all60 warning updates retain the warning, even with generic life1");
  near(warning.node.rotation.y, first.switchingSource!.field.yaw * Math.PI * 2 / 65536, "warning yaw uses BAM16");
  near(warning.node.scale.x, first.switchingSource!.field.visualScale.x, "warning X pulse follows source");
  assert(warning.node.rotation.x === 0 && warning.node.rotation.z === 0 && warning.node.scale.y === 1,
    "animated pitch is not tilt and pulse is transverse only");
  tick(first, { registerHit: () => false }); sync([first]);
  assert(get(first.uid) === warning && first.switchingSource!.field.timer === 0,
    "failed HIT registration retains visible warning rather than guessing activation");
  const warningSnapshot = JSON.stringify(first), warningPose = {
    position: warning.node.position.clone(), rotation: warning.node.rotation.clone(), scale: warning.node.scale.clone(),
  };
  scene.update(100); sync([first, first]);
  assert(JSON.stringify(first) === warningSnapshot && warning.node.position.equals(warningPose.position)
    && warning.node.rotation.equals(warningPose.rotation) && warning.node.scale.equals(warningPose.scale)
    && internals.projectileActors.size === 1,
    "paused/render-only repeated sync does not advance warning, state or actor count");

  tick(first); sync([first]);
  const active = get(first.uid);
  watch(active);
  const layers = active.switchingField!;
  assert(active !== warning && layers.subphase === 1 && layers.inner.node.children.length === 2 && layers.outer?.node.children.length === 1,
    "registration replaces warning with both151 layers and outer152");
  retired(warning, "phase replacement disposes warning private materials once");
  assert(layers.inner.node.name.endsWith(":model151") && layers.outer.node.name.endsWith(":model152"), "active source asset identity");
  assert(active.node.scale.equals(new THREE.Vector3(1, 1, 1)) && layers.inner.node.scale.x === 1 && layers.outer.node.scale.x === 1,
    "activation resets source scales without generic velocity stretch or HIT enlargement");
  assert([...layers.inner.materials, ...layers.outer.materials].every(material =>
    material.transparent && !material.depthWrite && material.blending === THREE.AdditiveBlending),
    "source columns use additive transparent materials, never opaque collision capsules");
  const innerGeometry = geometry(layers.inner), outerGeometry = geometry(layers.outer);
  tick(first); sync([first]);
  near(layers.inner.node.scale.x, first.switchingSource!.field.innerScale, "inner source shrink");
  assert(layers.inner.node.scale.x === layers.inner.node.scale.y && layers.inner.node.scale.y === layers.inner.node.scale.z,
    "inner scale is uniform, including vertical silhouette");
  assert(first.switchingSource!.field.outerScale > 1 && layers.outer.node.scale.equals(new THREE.Vector3(1, 1, 1)),
    "outerScale scratch matrix is unused by source outer draw");
  near(layers.outer.materials[0]!.opacity, first.switchingSource!.field.outerAlpha, "outer source alpha");
  first.hitConfirmedThisFrame = true;
  const activeSnapshot = JSON.stringify(first);
  const pose = { position: active.node.position.clone(), rotation: active.node.rotation.clone(),
    scale: layers.inner.node.scale.clone(), alpha: layers.outer.materials[0]!.opacity };
  scene.update(100); sync([first, first]);
  assert(JSON.stringify(first) === activeSnapshot && active.node.position.equals(pose.position) && active.node.rotation.equals(pose.rotation)
    && layers.inner.node.scale.equals(pose.scale) && layers.outer.materials[0]!.opacity === pose.alpha,
    "active state, transforms and alpha remain frozen under render-only updates");
  assert(internals.impactActors.length === 0 && internals.bankFxActors.length === 0,
    "field contacts do not manufacture generic hit or render-clock effects");

  const second = projectile("second", 1);
  tick(second, { initialPosition: () => ({ x: -500, y: 30, z: 700 }) });
  sync([first, second]);
  const secondWarning = get(second.uid);
  watch(secondWarning);
  assert(geometry(secondWarning.switchingField!.inner) === warningGeometry, "later field reuses cached warning geometry");
  assert(secondWarning.switchingField!.inner.materials[0]!.color.equals(new THREE.Color(1, 0, .3984)),
    "team1 samples direct material frame1");
  assert(secondWarning.node.position.equals(new THREE.Vector3(-500, 30, 700)), "independent field position");
  const secondSnapshot = JSON.stringify(second), secondScale = secondWarning.node.scale.clone();
  tick(first); sync([first, second]);
  assert(JSON.stringify(second) === secondSnapshot && secondWarning.node.scale.equals(secondScale) && secondWarning.node.visible,
    "advancing first field cannot age or modify second warning");
  activate(second); sync([first, second]);
  const secondActive = get(second.uid);
  watch(secondActive);
  retired(secondWarning, "second phase replacement disposes its own warning once");
  assert(geometry(secondActive.switchingField!.inner) === innerGeometry && geometry(secondActive.switchingField!.outer!) === outerGeometry,
    "independent active fields share only static geometry");
  assert(secondActive.switchingField!.outer!.materials[0] !== layers.outer.materials[0]
    && secondActive.switchingField!.outer!.materials[0]!.opacity === 1 && layers.outer.materials[0]!.opacity < 1,
    "each active field owns independent source alpha and materials");

  while (first.switchingSource!.field.timer > 1) tick(first);
  sync([first, second]);
  assert(active.node.visible && first.switchingSource!.field.hitActive, "last active sample remains visible");
  assert(layers.outer.materials[0]!.opacity === 0 && layers.inner.node.visible,
    "outer fade ends before source inner lifetime, without destroying the other layer");
  tick(first); sync([first, second]);
  assert(!active.node.visible && secondActive.node.visible && first.switchingSource!.field.phase === "retiring",
    "expiry hides field immediately while retaining other field");
  tick(first); sync([first, second]);
  assert(!active.node.visible && first.switchingSource!.field.phase === "released", "released phase stays hidden");
  tick(first); sync([first, second]);
  assert(!active.node.visible && first.switchingSource!.field.phase === "freed", "freed sample cannot resurrect field");
  sync([second], [{ uid: first.uid, pos: first.pos, vel: first.vel, team: 0, reason: "expired" }]);
  retired(active, "authoritative omission disposes active materials once");
  assert(get(second.uid) === secondActive && secondActive.node.visible, "omitting one field leaves the other intact");

  const ordinary = { ...second };
  delete ordinary.switchingSource;
  delete ordinary.flightVisual;
  sync([ordinary]);
  const generic = get(second.uid);
  watch(generic);
  assert(generic !== secondActive && generic.beam && !generic.switchingField, "same UID returning to ordinary projectile restores generic presentation");
  retired(secondActive, "source removal disposes only that field's private materials");
  sync([second]);
  retired(generic, "same UID returning to source field retires generic actor");
  const resumed = get(second.uid);
  watch(resumed);
  assert(resumed.switchingField?.subphase === 1 && resumed.node.visible, "late first active sample does not invent a warning");
  tick(second, { ownerInvalid: "owner-changed" }); sync([second]);
  assert(!resumed.node.visible, "owner form change hides source field before omission");
  sync([], [{ uid: second.uid, pos: second.pos, vel: second.vel, team: 1, reason: "hit-target", impactEffectId: 0 }]);
  retired(resumed, "owner omission retires source field without generic hit effects");
  assert(internals.impactActors.length === 0 && internals.bankFxActors.length === 0, "field removal stays effect-free");

  const dying = projectile("dying"); tick(dying); sync([dying]);
  const dyingActor = get(dying.uid); watch(dyingActor);
  tick(dying, { ownerInvalid: "owner-dead" }); sync([dying]);
  assert(!dyingActor.node.visible, "owner death hides warning immediately");
  scene.clear(); scene.clear(); sync([]);
  retired(dyingActor, "repeated clear disposes hidden field exactly once");
  assert([...materialDisposals.values()].every(count => count === 1) && geometryDisposals === 0,
    "every private material retires exactly once and static cached geometry survives");

  const availableLayers = internals.switchingFieldLayers;
  const lookups: number[] = [];
  internals.switchingFieldLayers = modelId => { lookups.push(modelId); return null; };
  const missing = projectile("missing"); tick(missing); sync([missing]);
  const emptyWarning = get(missing.uid);
  assert(emptyWarning.switchingField!.inner.node.children.length === 0 && !emptyWarning.beam,
    "missing warning export remains empty, without an unrelated bank or invented beam");
  scene.update(100); sync([missing]);
  activate(missing); sync([missing]);
  const emptyActive = get(missing.uid);
  scene.update(100); sync([missing]);
  assert(emptyActive.switchingField!.inner.node.children.length === 0 && emptyActive.switchingField!.outer!.node.children.length === 0,
    "missing active exports also remain empty");
  assert(lookups.join(",") === "150,151,152", "asset lookups occur once per source phase, never every render");
  sync([]); internals.switchingFieldLayers = availableLayers;
  const fresh = projectile("fresh"); activate(fresh); sync([fresh]);
  assert(get(fresh.uid).switchingField!.inner.node.children.length === 2, "new lifetime resolves restored static assets");
  scene.clear();
  assert(internals.projectileActors.size === 0 && geometryDisposals === 0, "final cleanup retains shared geometry");
  console.log("[switchingScene] PASS: source bank150/151/152, warning/active clocks, yaw-only transforms, source alpha, independent fields, pause, hidden phases, replacement, missing assets and disposal");
}
