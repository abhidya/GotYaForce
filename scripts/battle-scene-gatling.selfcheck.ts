import * as THREE from "three";
import { BattleScene } from "../apps/game/src/sim/battleScene.js";
import { createPoweredPrimary } from "../packages/combat/src/poweredProjectile.js";
import { createGatlingExplosion, stepGatlingExplosion } from "../packages/combat/src/gatlingProjectile.js";
import type { Projectile, BattleProjectileObservation, ProjectileDespawnObservation } from "../packages/combat/src/types.js";

function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`Gatling scene: ${message}`);
}
const near = (a: number, b: number) => Math.abs(a - b) < 1e-6;
interface BankVisual { node: THREE.Group; materials: THREE.MeshBasicMaterial[]; layerOpacity: number[] }
interface ProjectileActor {
  node: THREE.Object3D; material: THREE.Material; beam: boolean;
  bankMaterials?: THREE.MeshBasicMaterial[]; bankLayerOpacity?: number[];
  gatlingModelId?: number; gatlingRing?: BankVisual;
}
function primary(uid = "primary", ownerScale = 2): Projectile {
  const flight = createPoweredPrimary(4, { x: 101, y: 202, z: 303 }, .25, null, ownerScale);
  return {
    uid, ownerUid: "owner", team: 0, pos: { ...flight.pos }, vel: { ...flight.vel },
    life: flight.life, damage: 1, hitstun: 0, knockback: 1, homingTurn: 0,
    homingTarget: null, hitRadius: 24, visualKind: "energy", gatlingSource: { kind: "primary", flight },
  };
}
export async function runBattleSceneGatlingSelfcheck(): Promise<void> {
  const load = THREE.TextureLoader.prototype.load;
  THREE.TextureLoader.prototype.load = function () { return new THREE.Texture(); };
  const root = new THREE.Group();
  let scene: BattleScene;
  try { scene = new BattleScene(root, { loadModel: async () => new THREE.Group(), loadClip: async () => null }); }
  finally { THREE.TextureLoader.prototype.load = load; }
  const internals = scene as unknown as {
    projectileActors: Map<string, ProjectileActor>; gatlingLayers: (modelId: number) => unknown;
    bankFxActors: unknown[]; impactActors: unknown[];
  };
  const sync = (shots: readonly BattleProjectileObservation[], despawns: readonly ProjectileDespawnObservation[] = []) =>
    scene.sync([], shots, null, false, despawns);
  const grenade = primary();
  sync([grenade]);
  const fallback = internals.projectileActors.get(grenade.uid)!;
  assert(fallback.beam && !fallback.bankMaterials && fallback.node.children.length === 2,
    "unresolved owner-local primary model10 retains explicitly generic beam, never global efct10");
  const explosion = createGatlingExplosion(grenade);
  const source = explosion.gatlingSource!;
  assert(source.kind === "explosion", "explosion fixture");
  // Source state, not a contradictory generic flight visual or near-zero life, selects the asset/fade.
  explosion.flightVisual = { bankTexId: 10, teamTint: true, launchFxId: null };
  explosion.life = 1;
  sync([explosion], [{ uid: grenade.uid, pos: grenade.pos, vel: grenade.vel, team: 0,
    reason: "hit-terrain", suppressTerrainImpactFx: true }]);
  const body = internals.projectileActors.get(explosion.uid)!;
  const ring = body.gatlingRing!;
  assert(body.gatlingModelId === 22 && body.node.children.length === 3 && !body.beam,
    "active explosion uses all three real global22 layers, never the beam or global10");
  assert(body.bankMaterials![0]!.color.equals(new THREE.Color(1, .2969, 0)) && body.bankMaterials![0]!.opacity === 1,
    "fixed matAnim frame0 and source alpha override generic team tint/lifetime fade");
  assert(near(body.node.scale.x, Math.fround(.01) * 2) && body.node.scale.x === body.node.scale.y && body.node.scale.x === body.node.scale.z,
    "initial source expansion is uniformly .01 times owner scale");
  assert(body.node.rotation.y === 0, "explosion does not invent spin from the unused source field");
  assert(ring.node.parent === root && body.node.parent === root && ring.node.children.length === 1,
    "real global18 ring has separate world transform from expanding model22");
  assert(ring.node.position.equals(body.node.position) && ring.node.scale.equals(new THREE.Vector3(2, 2, 2)),
    "ring inherits owner scale once, not primary drawscale2 or expanding body scale");
  assert(near(ring.materials[0]!.opacity, .999), "ring retains authored layer alpha");
  assert(internals.impactActors.length === 0 && internals.bankFxActors.length === 0,
    "source terrain detonation does not also create generic impact or render-clock effects");
  const snapshot = JSON.stringify(explosion);
  const bodyScale = body.node.scale.clone();
  scene.update(100); sync([explosion, explosion]);
  assert(internals.projectileActors.size === 1 && internals.projectileActors.get(explosion.uid) === body && body.gatlingRing === ring,
    "repeated sync and duplicate UID retain one body and one ring");
  assert(JSON.stringify(explosion) === snapshot && body.node.scale.equals(bodyScale) && ring.node.scale.x === 2,
    "render-only/pause does not age source state, source scales, alpha or spin");
  let bodyDisposals = 0, ringDisposals = 0, geometryDisposals = 0, dummyDisposals = 0;
  const bodyGeometry = (body.node.children[0] as THREE.Mesh).geometry;
  bodyGeometry.addEventListener("dispose", () => geometryDisposals++);
  (ring.node.children[0] as THREE.Mesh).geometry.addEventListener("dispose", () => geometryDisposals++);
  body.bankMaterials!.forEach((m) => m.addEventListener("dispose", () => bodyDisposals++));
  ring.materials.forEach((m) => m.addEventListener("dispose", () => ringDisposals++));
  body.material.addEventListener("dispose", () => dummyDisposals++);
  stepGatlingExplosion(source); sync([explosion]);
  assert(ring.node.scale.equals(new THREE.Vector3(4, 2, 4)) && near(ring.materials[0]!.opacity, .999),
    "f1 ring key doubles X/Z only and holds full alpha");
  while (source.ringAge < 9) stepGatlingExplosion(source);
  sync([explosion]);
  assert(near(ring.node.scale.x, (2 + .5 * 8 / 9) * 2) && ring.node.scale.y === 2 && near(ring.materials[0]!.opacity, .999 / 9),
    "f9 ring uses exact source piecewise scale and alpha");
  stepGatlingExplosion(source); sync([explosion]);
  assert(!body.gatlingRing && !ring.node.parent && ringDisposals === 1 && geometryDisposals === 0,
    "f10 ring retires owned materials once, never cached geometry");
  while (source.phase !== "hold") stepGatlingExplosion(source);
  sync([explosion]);
  assert(body.node.scale.equals(new THREE.Vector3(2.5, 2.5, 2.5)), "active expansion clamps at1.25 times owner scale");
  while (source.phase !== "tail") stepGatlingExplosion(source);
  sync([explosion]);
  const tail = internals.projectileActors.get(explosion.uid)!;
  assert(tail !== body && tail.gatlingModelId === 23 && tail.node.children.length === 3 && !body.node.parent,
    "same-UID tail switches to all global23 layers and detaches active22");
  assert(bodyDisposals === 3 && dummyDisposals === 1 && geometryDisposals === 0,
    "phase replacement disposes only per-instance materials once");
  assert(tail.node.scale.equals(new THREE.Vector3(2.5, 2.5, 2.5)) && near(tail.bankMaterials![0]!.opacity, .999),
    "tail starts from current expansion scale, not original owner scale");
  while (source.tailAge < 15) stepGatlingExplosion(source);
  sync([explosion]);
  assert(near(tail.node.scale.x, 2.5 * 1.125) && near(tail.bankMaterials![0]!.opacity, .999 / 2),
    "tail midpoint source scale/alpha, independent of projectile life");
  while (source.tailAge < 30) stepGatlingExplosion(source);
  sync([explosion]);
  assert(near(tail.node.scale.x, 2 * 1.5625) && tail.bankMaterials!.every((m) => m.opacity === 0),
    "tail f30 reaches1.5625 times owner scale and zero alpha");
  let tailDisposals = 0;
  tail.bankMaterials!.forEach((m) => m.addEventListener("dispose", () => tailDisposals++));
  assert(!stepGatlingExplosion(source), "source expires after tail f30");
  sync([], [{ uid: explosion.uid, pos: explosion.pos, vel: explosion.vel, team: 0, reason: "expired" }]);
  scene.clear(); scene.clear();
  assert(!tail.node.parent && tailDisposals === 3 && geometryDisposals === 0 && internals.projectileActors.size === 0,
    "authoritative omission and repeated clear retire once and preserve shared geometry");
  assert(internals.impactActors.length === 0 && internals.bankFxActors.length === 0,
    "tail expiry never manufactures generic puff or burst");
  const red = createGatlingExplosion(primary("red-primary")); red.team = 1;
  sync([red]);
  const redBody = internals.projectileActors.get(red.uid)!;
  assert(redBody.bankMaterials![0]!.color.equals(new THREE.Color(1, .2969, 0)), "team1 uses the same fixed explosion material selector");
  assert((redBody.node.children[0] as THREE.Mesh).geometry === bodyGeometry, "later explosion reuses surviving cached geometry");
  scene.clear();
  const availableLayers = internals.gatlingLayers;
  const lookups: number[] = [];
  internals.gatlingLayers = (modelId) => { lookups.push(modelId); return null; };
  const missing = createGatlingExplosion(primary("missing-primary"));
  sync([missing]); scene.update(100); sync([missing]);
  const empty = internals.projectileActors.get(missing.uid)!;
  assert(empty.node.children.length === 0 && empty.gatlingRing!.node.children.length === 0 && !empty.beam,
    "missing global assets are omitted without wrong-bank or generic substitutes");
  assert(lookups.join(",") === "22,18", "missing static assets are not retried each render");
  sync([]); internals.gatlingLayers = availableLayers; sync([red]);
  assert(internals.projectileActors.get(red.uid)!.node.children.length === 3, "new lifetime resolves available assets again");
  scene.clear();
  // Lifecycle facts also work when the entire primary flight happened between render syncs.
  const terrain: ProjectileDespawnObservation = {
    uid: "unseen-terrain", pos: grenade.pos, vel: grenade.vel, team: 0,
    reason: "hit-terrain", suppressTerrainImpactFx: true,
  };
  sync([], [terrain]);
  assert(internals.impactActors.length === 0 && internals.bankFxActors.length === 0,
    "unseen primary terrain detonation also suppresses only the generic puff");
  sync([], [{ ...terrain, uid: "ordinary-terrain", suppressTerrainImpactFx: false }]);
  assert(internals.impactActors.length === 1, "ordinary terrain impacts retain their puff");
  scene.clear();
  sync([grenade]);
  sync([], [{ ...terrain, uid: grenade.uid, reason: "hit-target", impactEffectId: 0 }]);
  assert(internals.bankFxActors.length === 1 && internals.impactActors.length === 0,
    "observed Gatling primary target contact retains exactly one damage-record effect");
  scene.clear();
  sync([], [{ ...terrain, uid: "unseen-target", reason: "hit-target", impactEffectId: 0 }]);
  assert(internals.bankFxActors.length === 1 && internals.impactActors.length === 0,
    "unseen Gatling primary target contact also retains its source damage-record effect");
  scene.clear();
  assert(geometryDisposals === 0, "all teardown leaves shared bank geometry intact");
  console.log("Gatling scene selfcheck passed (global asset identity, owner-bank fallback, source curves, phase swap, pause, lifecycle, missing assets)");
}
