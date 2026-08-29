// THREE-aware adapters for the source-owned camera. This module is the ONLY
// place the source camera layer pulls in three.js at runtime; the parent
// sourceCamera.ts stays THREE-free so @gf/combat (bootGlobals.ts:10) keeps its
// documented no-three runtime contract. Three-aware hosts — TitleIntro.ts,
// bootGlobals.ts once it owns a renderer — import from here; combat does not.
//
// Two standalone helpers are exposed — mtx34ToThreeMatrix4 (bare Mtx34 -> view
// matrix) and applySourceCameraToThree (SourceCamera -> PerspectiveCamera).

import * as THREE from "three";
import { mtx34ToColumnMajor4x4 } from "./sourceCamera.js";
import type { Mtx34, SourceCamera } from "./sourceCamera.js";

/**
 * Convert a C_MTXLookAt Mtx34 into a THREE.Matrix4 view matrix (world→camera).
 * Delegates to mtx34ToColumnMajor4x4 (the pure-TS rows→columns transpose) and
 * loads the result into a fresh Matrix4 via set. Each Mtx row (right / up /
 * look + its translation term) becomes a THREE matrix column.
 *
 * Direct faithful mapping of the GC view matrix; see mtx34ToColumnMajor4x4 for
 * the layout + the coordinate-system note.
 */
export function mtx34ToThreeMatrix4(mtx: Mtx34): THREE.Matrix4 {
  const cm = mtx34ToColumnMajor4x4(mtx);
  // THREE.Matrix4.set takes row-major arguments but stores column-major; using
  // .elements directly avoids any row/column argument-order confusion. The
  // pure-TS helper already produced the exact column-major layout.
  const m = new THREE.Matrix4();
  for (let i = 0; i < 16; i++) m.elements[i] = cm[i]!;
  return m;
}

/**
 * Apply a source camera's view + projection to a THREE.PerspectiveCamera — the
 * drop-in replacement for `camera.lookAt(target)`. Sets `matrixWorldInverse`
 * directly from the C_MTXLookAt view, `matrixWorld` from its inverse, and
 * decomposes the world matrix into `position`/`quaternion`/`scale` so other
 * three.js code reading those fields stays consistent. Syncs `fov`/`near`/`far`
 * from the CObj state (rebuilding the projection on change). Roll is left to
 * the host — it is a separate CObj channel applied post-lookAt (see the header
 * note in sourceCamera.ts + TitleIntro.ts applyTdcFrame); match the existing
 * host pattern (`camera.rotateZ(roll)`) after this call if roll is in use.
 *
 * Writing matrixWorld/matrixWorldInverse directly (rather than calling
 * updateMatrixWorld) is robust to the host's `matrixWorldAutoUpdate` setting:
 * if true, the renderer's own updateMatrixWorld recomposes matrixWorld from
 * position/quaternion (round-trip identity via the decompose above); if false,
 * the values written here persist untouched.
 */
export function applySourceCameraToThree(source: SourceCamera, camera: THREE.PerspectiveCamera): void {
  const view = mtx34ToThreeMatrix4(source.setupView()); // world→camera
  camera.matrixWorldInverse.copy(view);
  camera.matrixWorld.copy(view).invert(); // camera→world
  camera.matrixWorld.decompose(camera.position, camera.quaternion, camera.scale);
  const { fov, near, far } = source.state;
  if (camera.fov !== fov || camera.near !== near || camera.far !== far) {
    camera.fov = fov;
    camera.near = near;
    camera.far = far;
    camera.updateProjectionMatrix();
  }
}
