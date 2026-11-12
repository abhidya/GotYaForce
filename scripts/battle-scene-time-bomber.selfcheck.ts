// Reconstructed renderer regression from the maintained Gatling explosion harness.
// Fresh verification is required; this is not a recovered historical file hash.
import * as THREE from "three";
import { BattleScene } from "../apps/game/src/sim/battleScene.js";
import { createTimeBomberPrimary, createTimeBomberExplosion, stepTimeBomberExplosion } from "../packages/combat/src/timeBomberProjectile.js";
import { createTimeBomberMine } from "../packages/combat/src/timeBomberMine.js";
import type { Projectile, BattleProjectileObservation, ProjectileDespawnObservation } from "../packages/combat/src/types.js";

function assert(value: unknown, message: string): asserts value {
  if (!value) throw new Error(`TimeBomber scene: ${message}`);
}
const near = (a: number, b: number) => Math.abs(a - b) < 1e-6;
interface BankVisual { node: THREE.Group; materials: THREE.MeshBasicMaterial[]; layerOpacity: number[] }
interface ProjectileActor {
  node: THREE.Object3D; material: THREE.Material; beam: boolean;
  bankMaterials?: THREE.MeshBasicMaterial[]; bankLayerOpacity?: number[];
  gatlingModelId?: number; gatlingRing?: BankVisual;
}
function primary(uid = "primary", ownerScale = 2): Projectile {
  const flight = createTimeBomberPrimary( { x: 101, y: 202, z: 303 }, .25, null, ownerScale);
  return {
    uid, ownerUid: "owner", team: 0, pos: { ...flight.pos }, vel: { ...flight.vel },
    life: flight.life, damage: 1, hitstun: 0, knockback: 1, homingTurn: 0,
    homingTarget: null, hitRadius: 24, visualKind: "energy", timeBomberSource: flight,
  };
}
export async function runBattleSceneTimeBomberSelfcheck(): Promise<void> {
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
  // Owner-local mine model3 is not global effect3. This verifies the bounded
  // placeholder, not original animated mine presentation.
  const mine = primary("mine-placeholder");
  mine.life = 180;
  mine.timeBomberSource = { ...createTimeBomberMine(mine.pos, { x: 0, y: 0, z: 1 }),
    kind: "mine", phase: "active", ownerBorgId: "pl0106", ownerScale: 2,
    contactPending: false, hitUids: [], receivedAttackUids: [] };
  mine.flightVisual = { bankTexId: 3, teamTint: true, launchFxId: null };
  sync([mine]);
  const mineVisual = internals.projectileActors.get(mine.uid)!;
  assert(mineVisual.beam && !mineVisual.bankMaterials,
    "mine owner-local model3 never resolves unrelated global effect3");
  const mineSnapshot = JSON.stringify(mine);
  scene.update(100); sync([mine]);
  assert(JSON.stringify(mine) === mineSnapshot && internals.projectileActors.get(mine.uid) === mineVisual,
    "render-only updates do not advance mine lifecycle or duplicate placeholder");
  const mineExplosion = createTimeBomberExplosion(mine);
  sync([mineExplosion]);
  assert(!mineVisual.node.parent && internals.projectileActors.get(mineExplosion.uid)!.gatlingModelId === 22,
    "authoritative mine omission retires placeholder and displays shared source explosion22");
  scene.clear();
  const grenade = primary();
  sync([grenade]);
  const fallback = internals.projectileActors.get(grenade.uid)!;
  assert(fallback.beam && !fallback.bankMaterials && fallback.node.children.length === 2,
    "unresolved owner-local primary model3 retains explicitly generic beam, never global efct3");
  const explosion = createTimeBomberExplosion(grenade);
  const source = explosion.timeBomberSource!;
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
  stepTimeBomberExplosion(source); sync([explosion]);
  assert(ring.node.scale.equals(new THREE.Vector3(4, 2, 4)) && near(ring.materials[0]!.opacity, .999),
    "f1 ring key doubles X/Z only and holds full alpha");
  while (source.ringAge < 9) stepTimeBomberExplosion(source);
  sync([explosion]);
  assert(near(ring.node.scale.x, (2 + .5 * 8 / 9) * 2) && ring.node.scale.y === 2 && near(ring.materials[0]!.opacity, .999 / 9),
    "f9 ring uses exact source piecewise scale and alpha");
  stepTimeBomberExplosion(source); sync([explosion]);
  assert(!body.gatlingRing && !ring.node.parent && ringDisposals === 1 && geometryDisposals === 0,
    "f10 ring retires owned materials once, never cached geometry");
  while (source.phase !== "hold") stepTimeBomberExplosion(source);
  sync([explosion]);
  assert(body.node.scale.equals(new THREE.Vector3(2.5, 2.5, 2.5)), "active expansion clamps at1.25 times owner scale");
  while (source.phase !== "tail") stepTimeBomberExplosion(source);
  sync([explosion]);
  const tail = internals.projectileActors.get(explosion.uid)!;
  assert(tail !== body && tail.gatlingModelId === 23 && tail.node.children.length === 3 && !body.node.parent,
    "same-UID tail switches to all global23 layers and detaches active22");
  assert(bodyDisposals === 3 && dummyDisposals === 1 && geometryDisposals === 0,
    "phase replacement disposes only per-instance materials once");
  assert(tail.node.scale.equals(new THREE.Vector3(2.5, 2.5, 2.5)) && near(tail.bankMaterials![0]!.opacity, .999),
    "tail starts from current expansion scale, not original owner scale");
  while (source.tailAge < 15) stepTimeBomberExplosion(source);
  sync([explosion]);
  assert(near(tail.node.scale.x, 2.5 * 1.125) && near(tail.bankMaterials![0]!.opacity, .999 / 2),
    "tail midpoint source scale/alpha, independent of projectile life");
  while (source.tailAge < 30) stepTimeBomberExplosion(source);
  sync([explosion]);
  assert(near(tail.node.scale.x, 2 * 1.5625) && tail.bankMaterials!.every((m) => m.opacity === 0),
    "tail f30 reaches1.5625 times owner scale and zero alpha");
  let tailDisposals = 0;
  tail.bankMaterials!.forEach((m) => m.addEventListener("dispose", () => tailDisposals++));
  assert(!stepTimeBomberExplosion(source), "source expires after tail f30");
  sync([], [{ uid: explosion.uid, pos: explosion.pos, vel: explosion.vel, team: 0, reason: "expired" }]);
  scene.clear(); scene.clear();
  assert(!tail.node.parent && tailDisposals === 3 && geometryDisposals === 0 && internals.projectileActors.size === 0,
    "authoritative omission and repeated clear retire once and preserve shared geometry");
  assert(internals.impactActors.length === 0 && internals.bankFxActors.length === 0,
    "tail expiry never manufactures generic puff or burst");
  const red = createTimeBomberExplosion(primary("red-primary")); red.team = 1;
  sync([red]);
  const redBody = internals.projectileActors.get(red.uid)!;
  assert(redBody.bankMaterials![0]!.color.equals(new THREE.Color(1, .2969, 0)), "team1 uses the same fixed explosion material selector");
  assert((redBody.node.children[0] as THREE.Mesh).geometry === bodyGeometry, "later explosion reuses surviving cached geometry");
  scene.clear();
  const availableLayers = internals.gatlingLayers;
  const lookups: number[] = [];
  internals.gatlingLayers = (modelId) => { lookups.push(modelId); return null; };
  const missing = createTimeBomberExplosion(primary("missing-primary"));
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
    "observed TimeBomber primary target contact retains exactly one damage-record effect");
  scene.clear();
  sync([], [{ ...terrain, uid: "unseen-target", reason: "hit-target", impactEffectId: 0 }]);
  assert(internals.bankFxActors.length === 1 && internals.impactActors.length === 0,
    "unseen TimeBomber primary target contact also retains its source damage-record effect");
  scene.clear();
  assert(geometryDisposals === 0, "all teardown leaves shared bank geometry intact");
  console.log("TimeBomber scene selfcheck passed (global asset identity, owner-bank fallback, source curves, phase swap, pause, lifecycle, missing assets)");
}
