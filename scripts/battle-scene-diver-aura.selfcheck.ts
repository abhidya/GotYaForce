import * as THREE from "three";
import { hsdJointsInTraversalOrder, prepareImportedModel } from "../packages/render/src/index.js";
import { BattleScene } from "../apps/game/src/sim/battleScene.js";
import { createBattle, battleStateForSelfcheck } from "../packages/combat/src/battle.js";
import { emptyInput } from "../packages/combat/src/types.js";
import { stepAttacks, X_CHARGE } from "../packages/combat/src/combat.js";
import { buildProfile } from "../packages/combat/src/stats.js";
import { actionProfileForProfile } from "../packages/combat/src/actionProfiles.js";
import { xChargeMoveForBorgId } from "../packages/combat/src/moveRuntime.js";
import { CHARGE } from "../packages/combat/src/constants.js";
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
    ringTexture: THREE.Texture | null;
    spawnSpecialBurst: (pos: { x: number; y: number; z: number }, radius: number) => void;
    impactActors: Array<{ endScale: THREE.Vector2 }>; bankFxActors: unknown[];
  };
  internals.ringTexture = new THREE.Texture();
  const bursts: Array<{ pos: { x: number; y: number; z: number }; radius: number }> = [];
  const spawnBurst = internals.spawnSpecialBurst.bind(scene);
  internals.spawnSpecialBurst = (pos, radius) => {
    bursts.push({ pos: { ...pos }, radius }); spawnBurst(pos, radius);
  };
  const syncBattle = (battle: ReturnType<typeof createBattle>) => {
    const snapshot = battleSceneState(battle, null);
    scene.sync(snapshot.actors, snapshot.projectiles, null, false, snapshot.projectileDespawns, snapshot.diverAuras);
    return snapshot;
  };
  // Synthetic observation exercises scale propagation, including source init .01.
  // Real X is tested below; its first observable update already uses owner scale.
  const child: DiverAuraChild = {
    uid: "aura", ownerUid: "owner", ownerFormId: "pl0a04", team: 0,
    subtype: 0, pos: { x: 10, y: 20, z: 30 }, remainingFrames: 1140,
    hitRadius: 100, bankTexId: 78, visualVariant: 0, pulsePhaseDegrees: 0, visualScale: { x: .01, y: .01, z: .01 },
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
  const moved = { ...child, pos: { x: -70, y: 40, z: 80 }, visualScale: { x: 1.5, y: 1.25, z: 1.5 }, remainingFrames: 1 };
  sync([moved]); scene.update(3); sync([{ ...moved, remainingFrames: 1140 }]);
  assert(internals.diverAuraActors.get(child.uid) === aura, "refresh keeps one node");
  assert(aura.node.position.equals(new THREE.Vector3(-70, 40, 80)), "owner movement followed");
  assert(aura.node.scale.equals(new THREE.Vector3(1.5, 1.25, 1.5)), "absolute anisotropic scale does not compound or advance with render dt");
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
    syncBattle(battle);
    tick(true);
    syncBattle(battle);
    assert(bursts.length === 0 && battle.observe().diverAuras.length === 0, `${id} entry before contact has no manufactured burst`);
    for (let i = 0; i < 90 && battle.observe().diverAuras.length === 0; i++) { tick(); syncBattle(battle); }
    assert(battle.observe().diverAuras.length === 1, `${id} real X creates child`);
    const snapshot = battleSceneState(battle, null);
    scene.sync(snapshot.actors, snapshot.projectiles, null, false, snapshot.projectileDespawns, snapshot.diverAuras);
    const actual = snapshot.diverAuras[0]!;
    const actualNode = internals.diverAuraActors.get(actual.uid)!.node;
    assert(actualNode.position.equals(new THREE.Vector3(actual.pos.x, actual.pos.y, actual.pos.z)),
      `${id} Battle child reaches scene`);
    const owner = battleStateForSelfcheck(battle).borgs[0]!;
    assert(actual.pulsePhaseDegrees === 3 && actualNode.scale.x > 1 && actualNode.scale.y < 1,
      `${id} first active pulse reaches scene from actual X`);
    const initialScale = actualNode.scale.clone();
    for (const dt of [0, 1 / 240, 1 / 15, 3]) { scene.update(dt); syncBattle(battle); }
    assert(actualNode.scale.equals(initialScale) && battle.observe().diverAuras[0]!.pulsePhaseDegrees === 3,
      `${id} pause/repeated render sync must not advance phase`);
    for (let i = 1; i <= 120; i++) {
      tick(); const frame = syncBattle(battle).diverAuras[0]!;
      assert(frame.pulsePhaseDegrees === (3 + i * 3) % 360, `${id} 120-tick phase wrap`);
      assert(actualNode.scale.equals(new THREE.Vector3(frame.visualScale.x, frame.visualScale.y, frame.visualScale.z)),
        `${id} simulation anisotropy reaches scene on every tick`);
      assert(frame.hitRadius === 700, `${id} pulse must not change collision radius`);
      if (frame.pulsePhaseDegrees === 90) {
        assert(near(actualNode.scale.x, 1.0477) && near(actualNode.scale.y, .8889), `${id} positive quarter pulse`);
      }
      if (frame.pulsePhaseDegrees === 270) {
        assert(near(actualNode.scale.x, .9523) && near(actualNode.scale.y, 1.1111), `${id} signed-short negative quarter pulse`);
      }
    }
    assert(actualNode.scale.equals(initialScale), `${id} full cycle returns same scale`);
    owner.modelSizeScale = 1.5;
    tick(); const scaled = syncBattle(battle).diverAuras[0]!;
    assert(scaled.hitRadius === 700 * owner.modelSizeScale! && owner.modelSizeScale! > 1 &&
      actualNode.scale.x > owner.modelSizeScale! && actualNode.scale.y < owner.modelSizeScale!,
      `${id} owner base scale affects axes once and collision independently`);
    assert(actual.pulsePhaseDegrees === 3 && actual.visualScale.x === initialScale.x,
      `${id} old observation does not alias mutable pulse`);
    owner.pos.x += 100;
    tick();
    const movedSnapshot = battleSceneState(battle, null);
    scene.sync(movedSnapshot.actors, movedSnapshot.projectiles, null, false, movedSnapshot.projectileDespawns, movedSnapshot.diverAuras);
    assert(internals.diverAuraActors.get(actual.uid)!.node === actualNode && actualNode.position.x === owner.pos.x,
      `${id} real child follows updated owner`);
    assert(bursts.length === 0, `${id} authored aura has no generic burst`);
    // Repeated empty presses: keep the real source X cell empty despite refill ticks.
    for (let i = 0; i < 160; i++) {
      owner.weaponCells![1]!.cur = 0;
      tick(i % 40 === 0); syncBattle(battle);
    }
    assert(bursts.length === 0 && !owner.fallbackSpecialBurst, `${id} empty X never emits fallback event`);
    owner.hp = 0; owner.alive = false;
    tick();
    const deadSnapshot = battleSceneState(battle, null);
    scene.sync([], [], null, false, [], deadSnapshot.diverAuras);
    assert(!actualNode.parent, `${id} owner death removes real child visual`);
    scene.clear();
    await Promise.resolve(); await Promise.resolve();
  }
  // Isolate the generic fallback producer using real Battle actors but no ROM driver.
  // The profile belongs only to this fixture; custom radius does not alter catalog data.
  const charged = (borgs.borgs as BorgStats[]).find((b) => xChargeMoveForBorgId(b.id) !== null)!;
  for (const [stats, charge] of [[(borgs.borgs as BorgStats[]).find((b) => b.id === "pl0804")!, false], [charged, true]] as const) {
    const battle = createBattle({ stageId: "st00", forces: [
      { team: 0, ownerPlayer: "p1", borgIds: [stats.id] },
      { team: 1, ownerPlayer: "p2", borgIds: ["pl0804"] },
    ], bounds: { x: 2000, z: 2000 } }, borgs.borgs as BorgStats[]);
    const owner = battleStateForSelfcheck(battle).borgs[0]!;
    owner.romDriver = undefined;
    const profile = buildProfile(stats);
    const action = actionProfileForProfile(profile);
    action.special.archetype = "aoe"; action.special.radius = 173;
    const fire = () => {
      battleStateForSelfcheck(battle);
      owner.state = "idle"; owner.cooldowns = {};
      for (const cell of owner.weaponCells ?? []) cell.cur = cell.max;
      stepAttacks(owner, profile, false, true, [owner], new Map([[owner.uid, profile]]));
      if (charge) {
        owner.cooldowns["xChargeFrames"] = X_CHARGE.TIER2_FRAMES;
        stepAttacks(owner, profile, false, false, [owner], new Map([[owner.uid, profile]]));
      }
    };
    const count = bursts.length;
    fire();
    const event = owner.fallbackSpecialBurst;
    assert(event?.serial === 1, "actual fallback radial branch emits event");
    assert(near(event.radius, 173 * (charge ? CHARGE.TIER2_RADIUS_MULT : 1)), "custom/charged mechanic radius recorded");
    const sampled = { ...event.pos };
    const originalX = sampled.x;
    owner.pos.x += 40; owner.pos.y += 20; owner.pos.z -= 30;
    assert(event.pos.x === sampled.x && event.pos.y === sampled.y && event.pos.z === sampled.z,
      "event position does not alias moving actor on any axis");
    const snapshot = syncBattle(battle);
    assert(bursts.length === count + 1 && bursts.at(-1)!.pos.x === originalX, "Battle snapshot/view reaches scene at sampled origin");
    assert(snapshot.actors[0]!.fallbackSpecialBurst?.pos !== event.pos, "observation clones event position");
    assert(near(internals.impactActors.at(-1)!.endScale.x, event.radius * 2), "rendered ring diameter follows actual custom/charged radius");
    syncBattle(battle);
    assert(bursts.length === count + 1, "repeated sync does not replay event");
    fire(); syncBattle(battle);
    assert(owner.fallbackSpecialBurst?.serial === 2 && bursts.length === count + 2, "second attack renders without intervening rendered idle");
    action.special.archetype = "projectile";
    fire(); syncBattle(battle);
    assert(owner.fallbackSpecialBurst?.serial === 2 && bursts.length === count + 2, "projectile fallback creates no radial event or replay");
    scene.clear(); await Promise.resolve(); await Promise.resolve();
  }
  await checkDiverBoneAttachment();
  console.log("Diver aura Three scene selfcheck: PASS");
}

/** Synthetic exporter-shaped rigs exercise attachment, not asset/animation parity. */
async function checkDiverBoneAttachment(): Promise<void> {
  const load = THREE.TextureLoader.prototype.load;
  THREE.TextureLoader.prototype.load = function (): THREE.Texture { return new THREE.Texture(); };
  const parent = new THREE.Group();
  parent.position.set(400, -20, 70); parent.rotation.set(.2, .4, -.1); parent.scale.set(2, 3, 4);
  const root = new THREE.Group();
  root.position.set(-50, 11, 32); root.rotation.y = -.7; parent.add(root);
  const pending: Array<{ id: string; resolve: (model: THREE.Object3D) => void }> = [];
  const scene = new BattleScene(root, {
    loadModel: (id) => new Promise((resolve) => pending.push({ id, resolve })),
    loadClip: async () => null,
  });
  THREE.TextureLoader.prototype.load = load;
  const internals = scene as unknown as {
    actors: Map<string, { model: THREE.Object3D | null; mixer: THREE.AnimationMixer | null }>;
    diverAuraActors: Map<string, { node: THREE.Group }>;
  };
  const battle = createBattle({ stageId: "st00", forces: [
    { team: 0, ownerPlayer: "p1", borgIds: ["pl0805"] },
  ], bounds: { x: 2000, z: 2000 } }, borgs.borgs as BorgStats[]);
  const owner = { ...battleSceneState(battle, null).actors[0]!,
    pos: { x: 10, y: 20, z: 30 }, rotY: Math.PI / 2, modelSizeScale: 1.5 };
  const child: DiverAuraChild = { uid: "bone-aura", ownerUid: owner.uid, ownerFormId: "pl0805", team: 0,
    subtype: 0, pos: { ...owner.pos }, remainingFrames: 1140, hitRadius: 100,
    bankTexId: 78, visualVariant: 0, pulsePhaseDegrees: 0, visualScale: { x: .75, y: .75, z: .75 } };
  const sync = (id = "pl0805") => scene.sync([{ ...owner, combatFormId: id }], [], null, false, [], [child]);
  const flush = async () => { await Promise.resolve(); await Promise.resolve(); };
  const makeRig = () => {
    const model = new THREE.Group(); model.scale.setScalar(.02); model.position.y = 7;
    const joints = Array.from({ length: 23 }, (_, i) => {
      const joint = new THREE.Bone(); joint.name = `JOBJ_${(i + 9) % 23}`; return joint;
    });
    model.add(joints[0]!);
    // Preserved child order, deliberately permuted names. No display meshes needed.
    for (let i = 1; i < joints.length; i++) (i === 2 ? joints[1]! : joints[0]!).add(joints[i]!);
    joints[12]!.position.set(800, 900, 1000);
    joints[14]!.position.set(4, 5, 6);
    joints[14]!.rotation.set(.3, .6, .9); joints[14]!.scale.set(5, 6, 7);
    return { model, bone: joints[14]! };
  };
  const checkPosition = (node: THREE.Object3D, x: number, y: number, z: number, label: string) =>
    assert(near(node.position.x, x) && near(node.position.y, y) && near(node.position.z, z), label);
  sync(); scene.update(.1);
  const aura = internals.diverAuraActors.get(child.uid)!.node;
  checkPosition(aura, 10, 20, 30, "async load uses explicit owner-root fallback");
  const first = makeRig();
  const display = new THREE.Mesh(new THREE.BoxGeometry(), new THREE.MeshBasicMaterial());
  display.name = "Joint_14_Object_0"; display.position.set(3, 8, 2); first.model.add(display);
  const rest = display.getWorldPosition(new THREE.Vector3());
  prepareImportedModel(first.model);
  assert(display.parent === first.bone && display.getWorldPosition(new THREE.Vector3()).distanceTo(rest) < 1e-6,
    "shared DFS reparent preserves mesh rest pose");
  assert(hsdJointsInTraversalOrder(first.model)[14] === first.bone,
    "reparented display nodes do not alter joint traversal");
  pending.shift()!.resolve(first.model); await flush();
  scene.update(0);
  // local (4,5,6) normalized .02, model +7Y, owner scale1.5, yaw90, +owner pos.
  checkPosition(aura, 10.18, 30.65, 29.88, "DFS14 translation includes normalization once and cancels transformed parents");
  assert(aura.scale.equals(new THREE.Vector3(.75, .75, .75)) && aura.quaternion.equals(new THREE.Quaternion()),
    "bone rotation and scale do not leak into aura");
  const mixer = internals.actors.get(owner.uid)!.mixer!;
  mixer.clipAction(new THREE.AnimationClip("anchor-motion", 2, [new THREE.VectorKeyframeTrack(
    `${first.bone.uuid}.position`, [0, 1, 2], [4, 5, 6, 14, 15, 16, 4, 5, 6],
  )])).play();
  scene.update(.5);
  checkPosition(aura, 10.33, 30.8, 29.73, "post-mixer sample moves aura in same rendered frame");
  scene.update(.5);
  checkPosition(aura, 10.48, 30.95, 29.58, "animation continues without a new simulation sync");
  sync("pl080d"); scene.update(0);
  checkPosition(aura, 10, 20, 30, "form swap discards old cached bone immediately");
  child.ownerFormId = "pl080e"; sync("pl080e");
  const stale = makeRig(); pending.shift()!.resolve(stale.model); await flush(); scene.update(0);
  assert(!stale.model.parent, "stale async model is never attached");
  checkPosition(aura, 10, 20, 30, "stale async result cannot reattach old bone");
  const current = makeRig(); pending.shift()!.resolve(current.model); await flush(); scene.update(0);
  checkPosition(aura, 10.18, 30.65, 29.88, "current Tar model resolves new anchor");
  child.ownerFormId = "pl080d"; sync("pl080d");
  pending.shift()!.resolve(makeRig().model); await flush(); scene.update(0);
  checkPosition(aura, 10.18, 30.65, 29.88, "Jack model also resolves source slot12");
  child.ownerFormId = "pl0805"; sync();
  pending.shift()!.resolve(new THREE.Group()); await flush(); scene.update(0);
  checkPosition(aura, 10, 20, 30, "missing skeleton falls back without guessed offset");
  scene.sync([], [], null, false, [], [child]); scene.update(0);
  checkPosition(aura, 10, 20, 30, "retired owner cannot retain a stale anchor");
  scene.clear(); scene.update(.1);
  assert(!aura.parent && internals.diverAuraActors.size === 0, "clear removes attachments permanently");
}
