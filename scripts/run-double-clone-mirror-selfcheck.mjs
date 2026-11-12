#!/usr/bin/env node
import assert from "node:assert/strict";
import { createRequire } from "node:module";
import { fileURLToPath, pathToFileURL } from "node:url";
import path from "node:path";
import * as THREE from "three";

const root = fileURLToPath(new URL("../", import.meta.url));
const gameRequire = createRequire(new URL("../apps/game/package.json", import.meta.url));
const { build } = createRequire(gameRequire.resolve("vite"))("esbuild");
const outfile = path.join(root, ".tmp/double-clone-mirror-selfcheck.mjs");
await build({
  absWorkingDir: root,
  entryPoints: ["apps/game/src/sim/doubleCloneMirror.ts"],
  bundle: true, platform: "node", format: "esm", packages: "external", outfile,
});
const { createDoubleCloneMirror } = await import(pathToFileURL(outfile).href);
const scene = new THREE.Group();
scene.position.set(3, 2, 1);
scene.rotation.y = 0.7;
scene.scale.set(1.1, 1.3, 0.8);
const owner = new THREE.Group();
owner.position.set(5, 4, -2);
owner.rotation.y = -1.2;
owner.scale.set(0.5, 2, 3);
scene.add(owner);
const geometry = new THREE.BufferGeometry();
geometry.setAttribute("position", new THREE.Float32BufferAttribute([1, 0, 0, 0, 1, 0, 0, 0, 1], 3));
geometry.setAttribute("skinIndex", new THREE.Uint16BufferAttribute([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0], 4));
geometry.setAttribute("skinWeight", new THREE.Float32BufferAttribute([1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0], 4));
geometry.morphAttributes.position = [new THREE.Float32BufferAttribute([2, 0, 0, 0, 2, 0, 0, 0, 2], 3)];
const texture = new THREE.Texture();
const material = new THREE.MeshBasicMaterial({ map: texture });
const skin = new THREE.SkinnedMesh(geometry, [material, material]);
const bone = new THREE.Bone();
bone.name = "duplicate";
skin.add(bone);
owner.add(skin);
scene.updateMatrixWorld(true);
skin.bind(new THREE.Skeleton([bone]));
const weapon = new THREE.Mesh(geometry, material);
weapon.name = "duplicate";
weapon.matrixAutoUpdate = false;
weapon.matrix.makeTranslation(4, 5, 6);
owner.add(weapon);
const destination = new THREE.Group();
destination.position.set(-9, 8, 7);
destination.rotation.y = 2;
destination.scale.set(0.7, 2, 1.5);
scene.add(destination);
scene.updateMatrixWorld(true);
const mirror = createDoubleCloneMirror(owner);
destination.add(mirror.root);
const clonedOwner = mirror.root.children[0];
const clonedSkin = clonedOwner.children[0];
const clonedWeapon = clonedOwner.children[1];
assert.notEqual(clonedSkin.geometry, geometry);
assert.notEqual(clonedSkin.material[0], material);
assert.equal(clonedSkin.material[0].map, texture);
assert.notEqual(clonedSkin.skeleton, skin.skeleton);
assert.notEqual(clonedSkin.skeleton.bones[0], bone);
assert.notEqual(clonedSkin.skeleton.boneInverses[0], skin.skeleton.boneInverses[0]);
assert.notEqual(clonedSkin.geometry.morphAttributes.position[0], geometry.morphAttributes.position[0]);
assert.notEqual(clonedSkin.morphTargetInfluences, skin.morphTargetInfluences);
const matrixNear = (actual, expected) => actual.elements.forEach((value, index) => {
  assert.ok(Math.abs(value - expected.elements[index]) < 1e-9, `${index}: ${value} != ${expected.elements[index]}`);
});
const offset = new THREE.Vector3(12, -3, 7);
for (let frame = 0; frame < 3; frame++) {
  owner.rotation.y += 0.3;
  bone.rotation.z += 0.2;
  bone.position.y += 0.5;
  skin.morphTargetInfluences[0] = frame * 0.4;
  weapon.visible = frame !== 1;
  scene.updateMatrixWorld(true);
  const originalMatrices = [];
  owner.traverse((node) => originalMatrices.push(node.matrixWorld.clone()));
  const inverse = skin.skeleton.boneInverses[0].clone();
  mirror.sync(offset);
  const translation = new THREE.Matrix4().makeTranslation(offset.x, offset.y, offset.z);
  const sourceNodes = []; const cloneNodes = [];
  owner.traverse((node) => sourceNodes.push(node));
  clonedOwner.traverse((node) => cloneNodes.push(node));
  sourceNodes.forEach((node, index) => {
    matrixNear(cloneNodes[index].matrixWorld, translation.clone().multiply(node.matrixWorld));
    matrixNear(node.matrixWorld, originalMatrices[index]);
    assert.equal(cloneNodes[index].visible, node.visible);
  });
  assert.deepEqual(clonedSkin.morphTargetInfluences, skin.morphTargetInfluences);
  assert.equal(clonedWeapon.visible, weapon.visible);
  matrixNear(skin.skeleton.boneInverses[0], inverse);
  // Check actual skinned + morphed world-space vertex, not merely joint matrices.
  const ownerVertex = new THREE.Vector3(); const cloneVertex = new THREE.Vector3();
  skin.getVertexPosition(0, ownerVertex); ownerVertex.applyMatrix4(skin.matrixWorld).add(offset);
  clonedSkin.getVertexPosition(0, cloneVertex); cloneVertex.applyMatrix4(clonedSkin.matrixWorld);
  assert.ok(ownerVertex.distanceTo(cloneVertex) < 1e-9);
}
// Hidden owner wrappers must hide the mirror even if the model itself is visible.
scene.visible = false;
mirror.sync(offset);
assert.equal(mirror.root.visible, false);
scene.visible = true;
mirror.sync(offset);
assert.equal(mirror.root.visible, true);
// Materials are deliberately snapshots, while texture identity is shared.
const originalColor = material.color.clone();
clonedSkin.material[0].color.set(0xff0000);
assert.ok(material.color.equals(originalColor));
clonedSkin.geometry.attributes.position.setX(0, 99);
assert.equal(geometry.attributes.position.getX(0), 1);
clonedSkin.skeleton.boneInverses[0].elements[12] += 99;
assert.notEqual(clonedSkin.skeleton.boneInverses[0].elements[12], skin.skeleton.boneInverses[0].elements[12]);
mirror.sync(offset);
assert.throws(() => mirror.sync(new THREE.Vector3(NaN, 0, 0)), /finite/);
// Render-time skeleton texture ownership, and material texture non-ownership.
skin.skeleton.computeBoneTexture();
clonedSkin.skeleton.computeBoneTexture();
let sourceDisposed = 0; let textureDisposed = 0; let boneTextureDisposed = 0;
geometry.addEventListener("dispose", () => sourceDisposed++);
material.addEventListener("dispose", () => sourceDisposed++);
skin.skeleton.boneTexture.addEventListener("dispose", () => sourceDisposed++);
texture.addEventListener("dispose", () => textureDisposed++);
clonedSkin.skeleton.boneTexture.addEventListener("dispose", () => boneTextureDisposed++);
const resourceCounts = new Map();
clonedOwner.traverse((node) => {
  if (!node.isMesh) return;
  for (const resource of [node.geometry, ...[].concat(node.material)]) {
    resourceCounts.set(resource, 0);
    resource.addEventListener("dispose", () => resourceCounts.set(resource, resourceCounts.get(resource) + 1));
  }
});
owner.add(new THREE.Group());
assert.throws(() => mirror.sync(offset), /hierarchy changed/);
owner.remove(owner.children.at(-1));
mirror.dispose(); mirror.dispose();
assert.equal(mirror.root.parent, null);
assert.equal(mirror.root.children.length, 0);
assert.equal(sourceDisposed, 0);
assert.equal(textureDisposed, 0);
assert.equal(boneTextureDisposed, 1);
assert.ok([...resourceCounts.values()].every((count) => count === 1));
assert.throws(() => mirror.sync(offset), /disposed/);
skin.bindMode = "detached";
assert.throws(() => createDoubleCloneMirror(owner), /attached skeleton/);
skin.bindMode = "attached";
skin.skeleton.bones[0] = new THREE.Bone();
assert.throws(() => createDoubleCloneMirror(owner), /within the source hierarchy/);
console.log("double clone mirror selfcheck: PASS");
