import * as THREE from "three";
import { clone as cloneSkeleton } from "three/examples/jsm/utils/SkeletonUtils.js";

export interface DoubleCloneMirror {
  /** Attach this wrapper to the render scene. Do not reparent or edit its descendants. */
  readonly root: THREE.Group;
  /** Call after the owner's pose AND world matrices have been updated, before rendering. */
  sync(worldOffset: Readonly<THREE.Vector3>): void;
  /** Removes root and frees only resources allocated by this mirror; safe to repeat. */
  dispose(): void;
}

/**
 * Presentation-only approximation: mirrors the already normalized, rendered owner,
 * including its current node/ancestor visibility and morph weights. Materials and
 * geometry are snapshots from creation; later owner material/geometry mutations are
 * NOT mirrored (recreate for those changes). No actor, mixer or asset loading.
 * The source game's precise clone weapon slot/mask and wrapper/joint mapping are not
 * established here. This does not invent either, or an alternate clone material.
 *
 * Requires a stable Object3D child hierarchy, ordinary Mesh/SkinnedMesh nodes and
 * attached-bind skeletons whose bones are all inside source. Replace the mirror when
 * the owner replaces its model/resources. Pairing is by the hierarchy preserved by
 * SkeletonUtils.clone, never by names (which may be duplicated) or ROM joint indices.
 * Source and the destination parent's matrixWorld must already be current. Sync reads
 * source state without advancing its animation or mutating its cached resources.
 */
export function createDoubleCloneMirror(source: THREE.Object3D): DoubleCloneMirror {
  const sourceNodes = new Set<THREE.Object3D>();
  source.traverse((node) => sourceNodes.add(node));
  for (const node of sourceNodes) {
    if (node instanceof THREE.InstancedMesh) throw new Error("Double clone does not support instanced meshes");
    if (!(node instanceof THREE.SkinnedMesh)) continue;
    if (node.bindMode !== "attached" || node.skeleton.bones.some((bone) => !sourceNodes.has(bone))) {
      throw new Error("Double clone requires attached skeleton bones within the source hierarchy");
    }
  }

  const model = cloneSkeleton(source);
  const root = new THREE.Group();
  root.name = "double-clone-mirror";
  root.matrixAutoUpdate = false;
  root.add(model);
  const pairs: Array<{ source: THREE.Object3D; clone: THREE.Object3D; children: THREE.Object3D[] }> = [];
  const geometries = new Set<THREE.BufferGeometry>();
  const materials = new Set<THREE.Material>();
  const skeletons = new Set<THREE.Skeleton>();
  function pair(owner: THREE.Object3D, copy: THREE.Object3D): void {
    if (owner.children.length !== copy.children.length || owner.type !== copy.type) {
      throw new Error("Double clone hierarchy was not preserved by cloning");
    }
    pairs.push({ source: owner, clone: copy, children: [...owner.children] });
    if (owner instanceof THREE.Mesh && copy instanceof THREE.Mesh) {
      copy.geometry = owner.geometry.clone();
      geometries.add(copy.geometry);
      const cloneMaterial = (material: THREE.Material): THREE.Material => {
        const cloned = material.clone(); // Texture references intentionally remain shared.
        materials.add(cloned);
        return cloned;
      };
      copy.material = Array.isArray(owner.material) ? owner.material.map(cloneMaterial) : cloneMaterial(owner.material);
    }
    if (copy instanceof THREE.SkinnedMesh) {
      // Skeleton.clone shares inverse matrices; privatize those as well as the bones.
      copy.skeleton.boneInverses = copy.skeleton.boneInverses.map((matrix) => matrix.clone());
      skeletons.add(copy.skeleton);
    }
    owner.children.forEach((child, index) => pair(child, copy.children[index]!));
  }
  let disposed = false;
  function dispose(): void {
    if (disposed) return;
    disposed = true;
    root.removeFromParent();
    geometries.forEach((geometry) => geometry.dispose());
    materials.forEach((material) => material.dispose());
    // Includes a boneTexture if the renderer allocated one after creation. Never
    // traverse material textures: those belong to the owner/asset cache.
    skeletons.forEach((skeleton) => skeleton.dispose());
    root.clear();
  }
  try {
    pair(source, model);
  } catch (error) {
    dispose();
    throw error;
  }
  const world = new THREE.Matrix4();
  const inverseParent = new THREE.Matrix4();
  function sync(worldOffset: Readonly<THREE.Vector3>): void {
    if (disposed) throw new Error("Cannot sync a disposed double clone");
    if (![worldOffset.x, worldOffset.y, worldOffset.z].every(Number.isFinite)) {
      throw new Error("Double clone offset must be finite");
    }
    // Validate before copying any pose; changed topology needs a fresh mirror.
    for (const entry of pairs) {
      if (entry.source.children.length !== entry.children.length ||
          entry.children.some((child, index) => entry.source.children[index] !== child) ||
          entry.clone.children.length !== entry.children.length) {
        throw new Error("Double clone source hierarchy changed; recreate the mirror");
      }
    }
    world.makeTranslation(worldOffset.x, worldOffset.y, worldOffset.z);
    if (source.parent) world.multiply(source.parent.matrixWorld);
    if (root.parent) {
      if (root.parent.matrixWorld.determinant() === 0) throw new Error("Double clone parent transform is singular");
      inverseParent.copy(root.parent.matrixWorld).invert();
      root.matrix.multiplyMatrices(inverseParent, world);
    } else root.matrix.copy(world);
    root.matrixWorldNeedsUpdate = true;
    root.visible = true;
    for (let ancestor = source.parent; ancestor; ancestor = ancestor.parent) {
      if (!ancestor.visible) root.visible = false;
    }
    for (const { source: owner, clone: copy } of pairs) {
      copy.position.copy(owner.position);
      copy.quaternion.copy(owner.quaternion);
      copy.scale.copy(owner.scale);
      copy.matrixAutoUpdate = false;
      copy.matrixWorldAutoUpdate = true;
      copy.matrix.copy(owner.matrix);
      copy.matrixWorldNeedsUpdate = true;
      copy.visible = owner.visible;
      copy.layers.mask = owner.layers.mask;
      copy.renderOrder = owner.renderOrder;
      if (owner instanceof THREE.Mesh && copy instanceof THREE.Mesh && owner.morphTargetInfluences) {
        copy.morphTargetInfluences = [...owner.morphTargetInfluences];
      }
      if (owner instanceof THREE.SkinnedMesh && copy instanceof THREE.SkinnedMesh) {
        copy.bindMatrix.copy(owner.bindMatrix);
        owner.skeleton.boneInverses.forEach((matrix, index) => copy.skeleton.boneInverses[index]!.copy(matrix));
      }
    }
    root.updateMatrixWorld(true);
    skeletons.forEach((skeleton) => skeleton.update());
    // SkinnedMesh bounds are cached, not invalidated by changed bone matrices or
    // morph weights. A creation-pose sphere can cull the current mirrored pose.
    // Compute from the private pose, without relying on fresh owner bounds.
    for (const { clone: copy } of pairs) {
      if (!(copy instanceof THREE.SkinnedMesh)) continue;
      copy.computeBoundingSphere();
      if (copy.boundingBox !== null) copy.computeBoundingBox();
    }
  }
  return { root, sync, dispose };
}
