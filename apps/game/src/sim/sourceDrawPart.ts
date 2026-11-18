import * as THREE from 'three';

/** Attach an independently exported one-root source model to a caller-selected
 * animated joint. The exporter baked the model's original bind transform into
 * mesh vertices, so its inverse must precede the target joint transform.
 * The caller owns joint selection, visibility, asset lifetime, and parity. */
export function attachSourceDrawPart(targetJoint: THREE.Object3D, part: THREE.Object3D): THREE.Group {
  if (part.parent) throw new Error('Source draw part must be detached');
  const joints: THREE.Object3D[] = [];
  part.traverse(node => { if (/^JOBJ_\d+$/.test(node.name)) joints.push(node); });
  if (joints.length !== 1 || joints[0]!.name !== 'JOBJ_0') throw new Error('Expected one JOBJ_0 source root');
  part.updateMatrixWorld(true);
  const bind = joints[0]!.matrixWorld;
  if (!bind.elements.every(Number.isFinite) || !Number.isFinite(bind.determinant()) || bind.determinant() === 0) {
    throw new Error('Source draw part bind transform must be finite and invertible');
  }
  const correction = new THREE.Group();
  correction.name = 'source-draw-part';
  correction.matrixAutoUpdate = false;
  correction.matrix.copy(bind).invert();
  // Keep this independent model out of the actor's JOBJ traversal/clip bindings.
  joints[0]!.name = 'SOURCE_DRAW_ROOT';
  correction.add(part);
  targetJoint.add(correction);
  return correction;
}
