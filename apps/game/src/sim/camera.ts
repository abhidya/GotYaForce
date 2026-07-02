// Battle camera — follow/frame logic for the challenge-mode viewport.
//
// Confidence convention (see packages/combat/src/constants.ts header + research/decomp/
// behavior-notes.md): DERIVED = confirmed from ROM decomp/binary/live-memory-trace with a
// cited address/evidence source. TUNED = an explicit, reasonable guess. Never silently
// upgrade a TUNED value to DERIVED.
//
// Current evidence (behavior-notes.md §ac, 2026-07-01):
// - Per-frame camera update is `zz_000bda4_` @ 0x8000bda4. It loops 12 static camera objects
//   at `0x803c73b0 + i*0x3e4`; each camera chooses its target actor from the live actor array
//   `(&DAT_803c4e84)[cam+0x2e5]`.
// - Camera object layout is decoded: eye vec3 at +0x2e8, previous eye +0x2f4, interest vec3
//   +0x300, previous interest +0x30c, up +0x330, view matrix +0x394.
// - All four 4P versus cameras were live-confirmed as mode 1. Mode dispatch is through the
//   table at 0x802c38cc; mode 1 is `FUN_8000c918`, which preserves previous eye/interest and
//   dispatches a mode subhandler from 0x802c3894 before finalizing via `FUN_8000c314`.
// - `FUN_8000c314` calls `C_MTXLookAt(cam+0x394, eye=cam+0x2e8, up=cam+0x330,
//   interest=cam+0x300)`.
// - The actor chain is live and replayable in 4P mode: `actor = *(u32*)0x803C4E84`,
//   `pos = actor + 0x20/+0x24/+0x28`, `heading = actor + 0x72`. The same section's golden
//   trace measured G Red ground speed from that chain.
//
// What this port can honestly use now:
// - DERIVED: target/interest comes from actor +0x20/+0x24/+0x28, camera policy is stateful
//   eye/interest smoothing, and the final primitive is a LookAt using separate eye/interest/up.
// - DERIVED: mode-0/init code uses a 0x600 BAM16 pitch value for the eye offset.
// - DERIVED-but-approximate: a prior live RAM camera trace found player+60 vertical offset and
//   horizontal camera distance in the high 400s.
// - DERIVED: mode-1's eye blend constants are read from boot.dol:
//   FLOAT_80436acc=4, FLOAT_80436ae8=5, and FLOAT_80436ac4=0.5. The port uses those exact
//   constants for the previous-eye blend and the target-height half blend.
// - TUNED: multi-actor widen-to-fit behavior. That stays named TUNED until multi-actor traces
//   are captured.

import * as THREE from "three";
import {
  CAMERA_MODE1_EYE_BLEND_DENOMINATOR,
  CAMERA_MODE1_HALF_BLEND,
  CAMERA_MODE1_PREVIOUS_EYE_WEIGHT,
} from "./camera.generated.js";

export interface CameraFollowTarget {
  /** World position to frame (typically the local player's active borg). */
  pos: THREE.Vector3;
  /** Facing yaw (radians), used to bias the trail direction TUNED-behind the borg. */
  rotY: number;
}

export interface StageBoundsLike {
  minX: number;
  maxX: number;
  minZ: number;
  maxZ: number;
}

/** DERIVED: ram-trace-analysis.md §3.1 — camera object 0x806A5300 sat exactly 60 world units
 * above the tracked player (Y=70.0 vs player Y=10.0) in both sampled frames. The §ac decomp
 * then confirmed mode handlers write a separate interest vec3 at camera+0x300 from actor+0x20. */
export const CAMERA_TARGET_Y_OFFSET_DERIVED = 60;

/** DERIVED-but-approximate: ram-trace-analysis.md §3.1 — horizontal camera-to-player distance
 * measured 466.5 and 504.9 world units across the only two sampled frames (mean ~485). Treated
 * as the base trailing distance for a single, un-spread-out target. Only two samples exist, so
 * this is real ROM evidence but not a tightly-bounded constant — do not treat the exact value as
 * more precise than "roughly high-400s". */
export const CAMERA_BASE_DISTANCE_DERIVED = 485;

/** DERIVED: mode init writes camera+0x70 = 0x600 before computing eye from target/heading. */
export const CAMERA_MODE_INIT_PITCH_BAM_DERIVED = 0x600;
const BAM16_TO_RADIANS = (Math.PI * 2) / 0x10000;
const CAMERA_MODE_INIT_PITCH_RADIANS_DERIVED =
  CAMERA_MODE_INIT_PITCH_BAM_DERIVED * BAM16_TO_RADIANS;

/** DERIVED: FUN_8000c988 computes eye = (prevEye * 4 + goalEye) / 5. */
const MODE1_EYE_PREV_WEIGHT_DERIVED = CAMERA_MODE1_PREVIOUS_EYE_WEIGHT;
const MODE1_EYE_BLEND_DENOMINATOR_DERIVED = CAMERA_MODE1_EYE_BLEND_DENOMINATOR;

/** DERIVED shape: mode-1 writes X/Z interest directly from actor+0x20/+0x28 and blends the
 * Y target with FLOAT_80436ac4. The exact actor +0x6d0 / camera +0x350 height terms are not
 * modeled yet, so the current `focus.y` remains the trace-derived actor+60 approximation. */
const MODE1_INTEREST_Y_BLEND_DERIVED = CAMERA_MODE1_HALF_BLEND;

/** TUNED: multi-actor dynamic framing. No ROM evidence (static or live-trace) of a 2-vs-3+
 * spread-apart zoom/framing algorithm was found — behavior-notes.md's camera section documents
 * an exhaustive corpus search that came up empty for this specific mechanic. This is a
 * standard-fighting-game-camera design choice (widen the shot to keep all active combatants in
 * view), not a port of confirmed ROM logic. */
const MULTI_ACTOR_ZOOM_TUNED = {
  /** Extra world-unit distance added per unit of spread beyond the base single-target framing. */
  spreadToDistanceGain: 0.55,
  /** Cap so the camera doesn't zoom out indefinitely on a huge stage. */
  maxExtraDistance: 900,
  /** Extra height gained alongside the zoom-out, so wide shots read from slightly above. */
  spreadToHeightGain: 0.18,
  maxExtraHeight: 260,
};

const _focus = new THREE.Vector3();
const _goal = new THREE.Vector3();
const _forward = new THREE.Vector3();
const _inward = new THREE.Vector3();
const _center = new THREE.Vector3();
const _eyeGoal = new THREE.Vector3();
const _spreadMin = new THREE.Vector3();
const _spreadMax = new THREE.Vector3();

export interface BattleCameraOptions {
  /** three.js camera being driven. */
  camera: THREE.PerspectiveCamera;
  /** OrbitControls (or any object with a `.target` Vector3) whose target we also drive. */
  controlsTarget: THREE.Vector3;
}

/**
 * Per-frame battle camera update. Frames the local player's active borg (DERIVED height offset
 * + base distance + smoothing behavior from ram-trace-analysis.md §3.1), then widens/raises the
 * shot (TUNED) if other live, active borgs are spread far from the primary target so multi-borg
 * fights stay readable instead of clipping teammates/enemies out of frame.
 */
export class BattleCamera {
  private initialized = false;

  constructor(private readonly opts: BattleCameraOptions) {}

  update(
    primary: CameraFollowTarget | null,
    allActorPositions: readonly THREE.Vector3[],
    stageBounds: StageBoundsLike,
  ): void {
    const { camera, controlsTarget } = this.opts;
    const focusBase = primary?.pos ?? _center.set(0, 80, 0);
    _focus.set(focusBase.x, focusBase.y + CAMERA_TARGET_Y_OFFSET_DERIVED, focusBase.z);

    if (!primary) {
      controlsTarget.copy(mode1InterestTarget(controlsTarget, _focus));
      return;
    }

    // TUNED spread metric: bounding-box diagonal (XZ) across all currently-live actors,
    // including the primary. Two actors close together -> near-zero spread -> base framing.
    const spread = computeSpreadXZ(allActorPositions, primary.pos);

    const extraDistance = Math.min(
      MULTI_ACTOR_ZOOM_TUNED.maxExtraDistance,
      spread * MULTI_ACTOR_ZOOM_TUNED.spreadToDistanceGain,
    );
    const extraHeight = Math.min(
      MULTI_ACTOR_ZOOM_TUNED.maxExtraHeight,
      spread * MULTI_ACTOR_ZOOM_TUNED.spreadToHeightGain,
    );

    const distance = CAMERA_BASE_DISTANCE_DERIVED + extraDistance;
    const pitchSin = Math.sin(CAMERA_MODE_INIT_PITCH_RADIANS_DERIVED);
    const pitchCos = Math.cos(CAMERA_MODE_INIT_PITCH_RADIANS_DERIVED);
    const horizontalDistance = distance * pitchCos;
    const verticalDistance = distance * pitchSin + extraHeight;

    _forward.set(Math.sin(primary.rotY), 0, Math.cos(primary.rotY));
    _eyeGoal.set(
      _focus.x - _forward.x * horizontalDistance,
      _focus.y + verticalDistance,
      _focus.z - _forward.z * horizontalDistance,
    );

    // Keep the browser camera inside the exported arena shell instead of letting the normal
    // trailing point sit behind a wall/ceiling at spawn. TUNED guard (no ROM collision data
    // for the gameplay camera has been traced yet — see module header).
    const centerX = (stageBounds.minX + stageBounds.maxX) * 0.5;
    const centerZ = (stageBounds.minZ + stageBounds.maxZ) * 0.5;
    const currentRadius = Math.hypot(focusBase.x - centerX, focusBase.z - centerZ);
    const goalRadius = Math.hypot(_eyeGoal.x - centerX, _eyeGoal.z - centerZ);
    const shellGuardRadius =
      Math.min(stageBounds.maxX - stageBounds.minX, stageBounds.maxZ - stageBounds.minZ) * 0.25;
    if (currentRadius > shellGuardRadius && goalRadius > currentRadius + 80) {
      _inward.set(centerX - focusBase.x, 0, centerZ - focusBase.z);
      if (_inward.lengthSq() < 0.0001) _inward.copy(_forward).multiplyScalar(-1);
      _inward.normalize();
      const pullDistance = horizontalDistance * 1.57; // TUNED wall-guard distance.
      const pullHeight = verticalDistance + 120; // TUNED extra lift when pulled toward arena center.
      _eyeGoal.set(
        _focus.x + _inward.x * pullDistance,
        _focus.y + pullHeight,
        _focus.z + _inward.z * pullDistance,
      );
    }

    if (!this.initialized) {
      controlsTarget.copy(_focus);
      camera.position.copy(_eyeGoal);
      this.initialized = true;
      return;
    }

    controlsTarget.copy(mode1InterestTarget(controlsTarget, _focus));
    camera.position.copy(mode1BlendEye(camera.position, _eyeGoal));
  }
}

function mode1BlendEye(current: THREE.Vector3, target: THREE.Vector3): THREE.Vector3 {
  return _goal
    .copy(current)
    .multiplyScalar(MODE1_EYE_PREV_WEIGHT_DERIVED)
    .add(target)
    .multiplyScalar(1 / MODE1_EYE_BLEND_DENOMINATOR_DERIVED);
}

function mode1InterestTarget(current: THREE.Vector3, target: THREE.Vector3): THREE.Vector3 {
  return _goal.set(
    target.x,
    (current.y + target.y) * MODE1_INTEREST_Y_BLEND_DERIVED,
    target.z,
  );
}

/** TUNED helper: XZ bounding-box diagonal across all live actors (0 if <=1 actor). */
function computeSpreadXZ(positions: readonly THREE.Vector3[], fallbackCenter: THREE.Vector3): number {
  if (positions.length < 2) return 0;
  _spreadMin.set(Infinity, 0, Infinity);
  _spreadMax.set(-Infinity, 0, -Infinity);
  let any = false;
  for (const p of positions) {
    if (!p) continue;
    any = true;
    if (p.x < _spreadMin.x) _spreadMin.x = p.x;
    if (p.z < _spreadMin.z) _spreadMin.z = p.z;
    if (p.x > _spreadMax.x) _spreadMax.x = p.x;
    if (p.z > _spreadMax.z) _spreadMax.z = p.z;
  }
  if (!any) return 0;
  void fallbackCenter;
  return Math.hypot(_spreadMax.x - _spreadMin.x, _spreadMax.z - _spreadMin.z);
}
