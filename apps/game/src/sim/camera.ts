// Battle camera — follow/frame logic for the challenge-mode viewport.
//
// Confidence convention (see packages/combat/src/constants.ts header + research/decomp/
// behavior-notes.md): DERIVED = confirmed from ROM decomp/binary/live-memory-trace with a
// cited address/evidence source. TUNED = an explicit, reasonable guess. Never silently
// upgrade a TUNED value to DERIVED.
//
// Evidence (behavior-notes.md §ac + §ad, 2026-07):
// - Per-frame camera update is `zz_000bda4_` @ 0x8000bda4; gameplay cameras run mode 1
//   (`FUN_8000c918` @ 0x8000c918), which dispatches the sub-table at 0x802c3894 by
//   actor+0x3f1. actor+0x3f1 is only ever 0 or 1, so gameplay always lands in
//   `FUN_8000cb8c` @ 0x8000cb8c — a state machine over camera+0x2e6 re-dispatching the same
//   table: state 2 = `FUN_8000cdc0` (no lock-on follow), state 3 = `FUN_8000cf28` (lock-on),
//   state 4 = `FUN_8000d11c` (transition), state 5 = `FUN_8000d318` (actor+0x7c9 special).
// - The PRIMARY follow policy ported here is state 2 (`FUN_8000cdc0` @ 0x8000cdc0 plus the
//   shared interest/distance update `FUN_8000fc2c` @ 0x8000fc2c):
//     1. interest.xz = actor pos (+0x20/+0x28); interest.y = (goalY + prevInterestY) * 0.5
//        (FLOAT_80436ac4) where goalY = actorY + per-borg height terms (+0x6d0, +0x88c).
//     2. trail dir = horizontal (prevGoalEye - interest); if |dir| <= FLOAT_80436ad8 it is
//        rebuilt from a BAM16 heading as (sin, 0, cos) (`FUN_800452e4` @ 0x800452e4).
//     3. distance = horizontal |prevGoalEye - actorPos| clamped to a per-borg [min, max]
//        band (actor +0x894/+0x898 scaled by camera+0x354 — per-borg data, see TUNED note).
//     4. desired = interest + trail * distance; desired.y = interest.y +
//        distance * tan(pitch), pitch fixed at 0x600 BAM (camera+0x70, `zz_004526c_` tan).
//     5. goalEye.xz = (4 * prev + desired) / 5 (FLOAT_80436acc / FLOAT_80436ae8);
//        goalEye.y = (9 * prev + desired) / 10 (FLOAT_80436af0 / FLOAT_80436adc).
//     6. eye = interest + normalize(goalEye - interest) * distance (re-projection), then
//        `FUN_8000c314` @ 0x8000c314 finalizes via C_MTXLookAt(eye, up, interest).
// - The mode-2 approach camera (`FUN_8000c988` @ 0x8000c988, mode table 0x802c38cc[2]) is
//   ported as the battle-entry approach replacing the old instant snap: per frame
//   distance = max(80, distance * 0.9) (FLOAT_80436ae0 / FLOAT_80436ae4), trail dir yawed
//   +0x200 BAM (instruction immediate), tracked eye-Y rises 4/frame (FLOAT_80436acc reused)
//   toward a cap, eye = (4 * prevEye + interest + trail * distance) / 5.
//
// Honest gaps (kept TUNED, marked below):
// - Per-borg camera data is not extracted: min/max follow distances (actor +0x894/+0x898),
//   height offsets (+0x88c/+0x6d0), and the mode-2 height cap (10 * actor+0x668). The port
//   substitutes the ram-trace band/offset (§3.1) for those values.
// - Lock-on states 3/4 (`FUN_8000cf28`/`FUN_8000d11c`) are documented in §ad but not ported;
//   the web port has no lock-on targeting yet.
// - The corrective pitch clamp / distance re-clamp passes (`FUN_800101c8` @ 0x800101c8,
//   `FUN_8000fffc` @ 0x8000fffc) are not ported (secondary safety nets).
// - Multi-actor widen-to-fit and the arena wall-guard are design choices with no ROM
//   evidence (an exhaustive corpus search found none) — both stay TUNED.
// - The ROM's mode-2 exit condition was not located; the approach hands off to the follow
//   policy once its distance decays into the follow band (TUNED exit).

import * as THREE from "three";
import {
  CAMERA_MODE1_DISTANCE_DECAY,
  CAMERA_MODE1_EYE_BLEND_DENOMINATOR,
  CAMERA_MODE1_EYE_Y_BLEND_DENOMINATOR,
  CAMERA_MODE1_HALF_BLEND,
  CAMERA_MODE1_MIN_DISTANCE,
  CAMERA_MODE1_PREVIOUS_EYE_WEIGHT,
  CAMERA_MODE1_PREVIOUS_EYE_Y_WEIGHT,
  CAMERA_MODE1_TRAIL_EPSILON,
  CAMERA_MODE2_EYE_RISE_PER_FRAME,
  CAMERA_MODE2_YAW_STEP_BAM,
} from "./camera.generated.js";

export interface CameraFollowTarget {
  /** World position to frame (typically the local player's active borg). */
  pos: THREE.Vector3;
  /** Facing yaw (radians). DERIVED role: only the degenerate-trail fallback uses it —
   * FUN_800452e4 rebuilds the trail from a BAM16 heading; mode-0 init (FUN_8000c660) seats
   * the camera behind the actor at heading - 0x8000. */
  rotY: number;
}

export interface StageBoundsLike {
  minX: number;
  maxX: number;
  minZ: number;
  maxZ: number;
}

/** DERIVED-but-approximate: ram-trace-analysis.md §3.1 — camera sat 60 world units above the
 * tracked player. In the ROM this is per-borg data (actor +0x6d0 / +0x88c eased into
 * camera+0x350, FUN_8000fc2c); the flat 60 stands in until that data is extracted. */
export const CAMERA_TARGET_Y_OFFSET_DERIVED = 60;

/** DERIVED-but-approximate: ram-trace-analysis.md §3.1 — horizontal camera-to-player distance
 * measured 466.5 and 504.9 world units across the only two sampled frames (mean ~485). The
 * §ad decomp shows the ROM clamps distance to a per-borg [min, max] band (FUN_8000fc2c,
 * actor +0x894/+0x898 × camera+0x354) rather than fixing it; the port uses the two trace
 * samples as the band until per-borg data is extracted. */
export const CAMERA_BASE_DISTANCE_DERIVED = 485;
const CAMERA_FOLLOW_MIN_DISTANCE_TRACE = 466.5;
const CAMERA_FOLLOW_MAX_DISTANCE_TRACE = 504.9;

/** DERIVED: mode init/follow writes camera+0x70 = 0x600 (FUN_8000c660, FUN_8000cdc0). */
export const CAMERA_MODE_INIT_PITCH_BAM_DERIVED = 0x600;
const BAM16_TO_RADIANS = (Math.PI * 2) / 0x10000;
const CAMERA_PITCH_RADIANS_DERIVED = CAMERA_MODE_INIT_PITCH_BAM_DERIVED * BAM16_TO_RADIANS;
/** DERIVED: FUN_8000cdc0 sets the desired eye height via distance * tan(pitch)
 * (zz_004526c_ @ 0x8004526c is tan over BAM16). */
const CAMERA_PITCH_TAN_DERIVED = Math.tan(CAMERA_PITCH_RADIANS_DERIVED);

/** DERIVED: FUN_8000cdc0 XZ blend eye = (prev * 4 + desired) / 5 (0x80436acc / 0x80436ae8). */
const MODE1_EYE_PREV_WEIGHT_DERIVED = CAMERA_MODE1_PREVIOUS_EYE_WEIGHT;
const MODE1_EYE_BLEND_DENOMINATOR_DERIVED = CAMERA_MODE1_EYE_BLEND_DENOMINATOR;
/** DERIVED: FUN_8000cdc0 Y blend eyeY = (prev * 9 + desired) / 10 (0x80436af0 / 0x80436adc). */
const MODE1_EYE_Y_PREV_WEIGHT_DERIVED = CAMERA_MODE1_PREVIOUS_EYE_Y_WEIGHT;
const MODE1_EYE_Y_BLEND_DENOMINATOR_DERIVED = CAMERA_MODE1_EYE_Y_BLEND_DENOMINATOR;
/** DERIVED: FUN_8000fc2c interest-Y half blend (0x80436ac4). */
const MODE1_INTEREST_Y_BLEND_DERIVED = CAMERA_MODE1_HALF_BLEND;
/** DERIVED: FUN_800452e4 degenerate-direction epsilon (0x80436ad8). */
const MODE1_TRAIL_EPSILON_DERIVED = CAMERA_MODE1_TRAIL_EPSILON;

/** DERIVED: FUN_8000c988 approach constants — distance floor 80 (0x80436ae0), per-frame decay
 * ×0.9 (0x80436ae4), yaw step 0x200 BAM (instruction immediate), eye-Y rise 4/frame
 * (0x80436acc reused as an addend). */
const MODE2_MIN_DISTANCE_DERIVED = CAMERA_MODE1_MIN_DISTANCE;
const MODE2_DISTANCE_DECAY_DERIVED = CAMERA_MODE1_DISTANCE_DECAY;
const MODE2_YAW_STEP_RADIANS_DERIVED = CAMERA_MODE2_YAW_STEP_BAM * BAM16_TO_RADIANS;
const MODE2_EYE_RISE_PER_FRAME_DERIVED = CAMERA_MODE2_EYE_RISE_PER_FRAME;

/** TUNED: multi-actor dynamic framing. Disabled until a ROM/trace rule is found: the old
 * widen-to-fit overlay let escaped actors drag the camera into a huge gray void. */
const MULTI_ACTOR_ZOOM_TUNED = {
  /** Extra world-unit distance added per unit of spread beyond the base single-target framing. */
  spreadToDistanceGain: 0,
  /** Cap so the camera doesn't zoom out indefinitely on a huge stage. */
  maxExtraDistance: 0,
  /** Extra height gained alongside the zoom-out, so wide shots read from slightly above. */
  spreadToHeightGain: 0,
  maxExtraHeight: 0,
};

const _focus = new THREE.Vector3();
const _goal = new THREE.Vector3();
const _forward = new THREE.Vector3();
const _inward = new THREE.Vector3();
const _center = new THREE.Vector3();
const _trail = new THREE.Vector3();
const _desired = new THREE.Vector3();
const _eye = new THREE.Vector3();
const _eyeGoal = new THREE.Vector3();
const _spreadMin = new THREE.Vector3();
const _spreadMax = new THREE.Vector3();

export interface BattleCameraOptions {
  /** three.js camera being driven. */
  camera: THREE.PerspectiveCamera;
  /** OrbitControls (or any object with a `.target` Vector3) whose target we also drive. */
  controlsTarget: THREE.Vector3;
  /** Explicit fallback: run the pre-§ad heading-locked approximation (fixed distance 485
   * behind the borg's facing) instead of the ported FUN_8000cdc0 goal-eye policy. */
  legacyApproximation?: boolean;
}

/**
 * Per-frame battle camera update.
 *
 * Default policy is the ported ROM mode-1 state-2 follow (FUN_8000cdc0 chain, see module
 * header) seeded through the ported mode-2 approach (FUN_8000c988) when the camera starts far
 * from the target. Multi-actor widen-to-fit and the arena wall-guard remain TUNED overlays on
 * the DERIVED skeleton. Set `legacyApproximation` to fall back to the old heading-locked
 * 2-sample approximation. The default path stays on the recovered single-focus distance band;
 * the old multi-actor widen overlay is kept only inside `legacyApproximation`.
 */
export class BattleCamera {
  private initialized = false;
  /** Persistent goal eye — the ROM's camera+0x318 slot (FUN_8000cdc0 blend state). */
  private readonly goalEye = new THREE.Vector3();
  /** Mode-2 approach state: persistent trail direction (camera+0x33c), decaying distance
   * (camera+0x348) and the rising tracked eye-Y (camera+0x3c). */
  private approachActive = false;
  private readonly approachTrail = new THREE.Vector3();
  private approachDistance = 0;
  private approachEyeY = 0;

  constructor(private readonly opts: BattleCameraOptions) {}

  snapTo(primary: CameraFollowTarget | null): void {
    this.approachActive = false;
    this.approachDistance = 0;
    this.approachEyeY = 0;
    if (!primary) {
      this.initialized = false;
      return;
    }

    const { camera, controlsTarget } = this.opts;
    _focus.set(primary.pos.x, primary.pos.y + CAMERA_TARGET_Y_OFFSET_DERIVED, primary.pos.z);
    _trail.set(-Math.sin(primary.rotY), 0, -Math.cos(primary.rotY));
    if (_trail.lengthSq() <= MODE1_TRAIL_EPSILON_DERIVED * MODE1_TRAIL_EPSILON_DERIVED) {
      _trail.set(0, 0, -1);
    } else {
      _trail.normalize();
    }
    const distance = CAMERA_FOLLOW_MAX_DISTANCE_TRACE;
    controlsTarget.copy(_focus);
    this.goalEye.set(
      _focus.x + _trail.x * distance,
      _focus.y + distance * CAMERA_PITCH_TAN_DERIVED,
      _focus.z + _trail.z * distance,
    );
    camera.position.copy(this.goalEye);
    this.initialized = true;
  }

  update(
    primary: CameraFollowTarget | null,
    allActorPositions: readonly THREE.Vector3[],
    stageBounds: StageBoundsLike,
  ): void {
    if (this.opts.legacyApproximation) {
      this.legacyUpdate(primary, allActorPositions, stageBounds);
      return;
    }
    const { camera, controlsTarget } = this.opts;
    const focusBase = primary?.pos ?? _center.set(0, 80, 0);
    _focus.set(focusBase.x, focusBase.y + CAMERA_TARGET_Y_OFFSET_DERIVED, focusBase.z);

    if (!primary) {
      controlsTarget.copy(mode1InterestTarget(controlsTarget, _focus));
      return;
    }

    const extraHeight = 0;
    // DERIVED structure (FUN_8000fc2c): distance clamps to a [min, max] band. Band values are
    // the two ram-trace samples (per-borg ROM data not extracted).
    const followMin = CAMERA_FOLLOW_MIN_DISTANCE_TRACE;
    const followMax = CAMERA_FOLLOW_MAX_DISTANCE_TRACE;

    if (!this.initialized) {
      this.initialized = true;
      controlsTarget.copy(_focus);
      this.seedFromCurrentEye(camera.position, _focus, primary.rotY, followMax);
      if (!this.approachActive) return;
    }

    // DERIVED (FUN_8000fc2c): interest X/Z track the actor directly; Y half-blends.
    controlsTarget.copy(mode1InterestTarget(controlsTarget, _focus));
    const interest = controlsTarget;

    if (this.approachActive) {
      this.updateApproach(camera.position, interest, extraHeight, followMax);
      return;
    }

    // ---- Ported FUN_8000cdc0 goal-eye follow ----
    // Trail direction: horizontal (prev goal eye - interest); degenerate fallback rebuilds it
    // behind the actor (FUN_800452e4 with the published camera-behind heading, DERIVED).
    _trail.set(this.goalEye.x - interest.x, 0, this.goalEye.z - interest.z);
    if (_trail.lengthSq() <= MODE1_TRAIL_EPSILON_DERIVED * MODE1_TRAIL_EPSILON_DERIVED) {
      _trail.set(-Math.sin(primary.rotY), 0, -Math.cos(primary.rotY));
    } else {
      _trail.normalize();
    }

    // DERIVED structure: distance = horizontal |prev goal eye - actor| clamped to the band.
    const horizontalDist = Math.hypot(this.goalEye.x - focusBase.x, this.goalEye.z - focusBase.z);
    const distance = Math.min(followMax, Math.max(followMin, horizontalDist));

    // DERIVED: desired eye = interest + trail * distance, height = distance * tan(0x600 BAM).
    // TUNED: extraHeight widen overlay.
    _desired.set(
      interest.x + _trail.x * distance,
      interest.y + distance * CAMERA_PITCH_TAN_DERIVED + extraHeight,
      interest.z + _trail.z * distance,
    );

    // TUNED wall-guard: steer the desired eye toward the arena center when the normal trailing
    // point would sit outside the exported arena shell. No ROM camera-collision data has been
    // traced; under the DERIVED re-projection this now only redirects the trail (distance and
    // height stay policy-controlled).
    const centerX = (stageBounds.minX + stageBounds.maxX) * 0.5;
    const centerZ = (stageBounds.minZ + stageBounds.maxZ) * 0.5;
    const currentRadius = Math.hypot(focusBase.x - centerX, focusBase.z - centerZ);
    const desiredRadius = Math.hypot(_desired.x - centerX, _desired.z - centerZ);
    const shellGuardRadius =
      Math.min(stageBounds.maxX - stageBounds.minX, stageBounds.maxZ - stageBounds.minZ) * 0.25;
    if (currentRadius > shellGuardRadius && desiredRadius > currentRadius + 80) {
      _inward.set(centerX - focusBase.x, 0, centerZ - focusBase.z);
      if (_inward.lengthSq() < 0.0001) _inward.set(-Math.sin(primary.rotY), 0, -Math.cos(primary.rotY));
      _inward.normalize();
      _desired.set(
        interest.x + _inward.x * distance,
        interest.y + distance * CAMERA_PITCH_TAN_DERIVED + extraHeight + 120, // TUNED extra lift.
        interest.z + _inward.z * distance,
      );
    }

    // DERIVED: goal-eye blend, XZ (4*prev + desired)/5 and Y (9*prev + desired)/10.
    this.goalEye.set(
      (MODE1_EYE_PREV_WEIGHT_DERIVED * this.goalEye.x + _desired.x) / MODE1_EYE_BLEND_DENOMINATOR_DERIVED,
      (MODE1_EYE_Y_PREV_WEIGHT_DERIVED * this.goalEye.y + _desired.y) / MODE1_EYE_Y_BLEND_DENOMINATOR_DERIVED,
      (MODE1_EYE_PREV_WEIGHT_DERIVED * this.goalEye.z + _desired.z) / MODE1_EYE_BLEND_DENOMINATOR_DERIVED,
    );

    // DERIVED: re-projection — eye = interest + normalize(goalEye - interest) * distance.
    _eye.copy(this.goalEye).sub(interest);
    if (_eye.lengthSq() > MODE1_TRAIL_EPSILON_DERIVED * MODE1_TRAIL_EPSILON_DERIVED) {
      _eye.normalize().multiplyScalar(distance).add(interest);
      camera.position.copy(_eye);
    } else {
      camera.position.copy(this.goalEye);
    }
  }

  /** Seed the follow/approach state from wherever the renderer left the camera. Mirrors the
   * FUN_8000c988 init branch (trail = eye - interest with epsilon fallback, distance captured
   * from the current eye, tracked eye-Y starts at the current eye height). */
  private seedFromCurrentEye(
    eye: THREE.Vector3,
    interest: THREE.Vector3,
    rotY: number,
    followMax: number,
  ): void {
    _trail.set(eye.x - interest.x, 0, eye.z - interest.z);
    const horizontalDist = _trail.length();
    if (horizontalDist <= MODE1_TRAIL_EPSILON_DERIVED) {
      _trail.set(-Math.sin(rotY), 0, -Math.cos(rotY));
    } else {
      _trail.multiplyScalar(1 / horizontalDist);
    }
    if (horizontalDist > followMax) {
      // Battle-entry approach (ported FUN_8000c988) instead of the old instant snap.
      this.approachActive = true;
      this.approachTrail.copy(_trail);
      this.approachDistance = horizontalDist;
      this.approachEyeY = eye.y;
    } else {
      this.approachActive = false;
      this.goalEye.set(
        interest.x + _trail.x * followMax,
        interest.y + followMax * CAMERA_PITCH_TAN_DERIVED,
        interest.z + _trail.z * followMax,
      );
      eye.copy(this.goalEye);
    }
  }

  /** Ported FUN_8000c988 body (mode-2 approach): decay distance toward the 80-unit floor while
   * yawing the trail 0x200 BAM/frame and raising the tracked eye-Y 4/frame, then blend the eye
   * (4*prev + interest + trail*distance)/5. Exit-to-follow at the band edge is TUNED (the ROM
   * trigger that leaves mode 2 was not located). */
  private updateApproach(
    eyeOut: THREE.Vector3,
    interest: THREE.Vector3,
    extraHeight: number,
    followMax: number,
  ): void {
    // DERIVED: distance floor/decay (0x80436ae0 / 0x80436ae4).
    this.approachDistance =
      this.approachDistance <= MODE2_MIN_DISTANCE_DERIVED
        ? MODE2_MIN_DISTANCE_DERIVED
        : this.approachDistance * MODE2_DISTANCE_DECAY_DERIVED;
    // DERIVED: yaw the trail direction by 0x200 BAM around Y (zz_00453fc_).
    const cos = Math.cos(MODE2_YAW_STEP_RADIANS_DERIVED);
    const sin = Math.sin(MODE2_YAW_STEP_RADIANS_DERIVED);
    this.approachTrail.set(
      this.approachTrail.x * cos + this.approachTrail.z * sin,
      0,
      this.approachTrail.z * cos - this.approachTrail.x * sin,
    );
    this.approachTrail.normalize();
    // DERIVED shape: tracked eye-Y rises 4/frame until its cap; the ROM cap is per-borg
    // (10 * actor+0x668, unavailable) — TUNED cap: the follow policy's own eye height.
    const eyeYCap = interest.y + this.approachDistance * CAMERA_PITCH_TAN_DERIVED + extraHeight;
    if (this.approachEyeY - eyeYCap <= 0) {
      this.approachEyeY = Math.min(this.approachEyeY + MODE2_EYE_RISE_PER_FRAME_DERIVED, eyeYCap);
    } else {
      this.approachEyeY = eyeYCap;
    }
    // DERIVED: eye = (4*prevEye + interest + trail*distance)/5; Y uses the tracked eye-Y.
    _desired.set(
      interest.x + this.approachTrail.x * this.approachDistance,
      this.approachEyeY,
      interest.z + this.approachTrail.z * this.approachDistance,
    );
    eyeOut.set(
      (MODE1_EYE_PREV_WEIGHT_DERIVED * eyeOut.x + _desired.x) / MODE1_EYE_BLEND_DENOMINATOR_DERIVED,
      (MODE1_EYE_PREV_WEIGHT_DERIVED * eyeOut.y + _desired.y) / MODE1_EYE_BLEND_DENOMINATOR_DERIVED,
      (MODE1_EYE_PREV_WEIGHT_DERIVED * eyeOut.z + _desired.z) / MODE1_EYE_BLEND_DENOMINATOR_DERIVED,
    );
    // TUNED exit: hand off to the follow policy once inside the follow band.
    if (this.approachDistance <= followMax) {
      this.approachActive = false;
      this.goalEye.copy(eyeOut);
    }
  }

  /** Pre-§ad approximation (explicit fallback): fixed base distance 485 behind the borg's
   * facing with sin/cos pitch split, TUNED widen and wall-guard, 4/5 whole-eye blend. Kept
   * verbatim so the old behavior stays reachable via `legacyApproximation`. */
  private legacyUpdate(
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
    const pitchSin = Math.sin(CAMERA_PITCH_RADIANS_DERIVED);
    const pitchCos = Math.cos(CAMERA_PITCH_RADIANS_DERIVED);
    const horizontalDistance = distance * pitchCos;
    const verticalDistance = distance * pitchSin + extraHeight;

    _forward.set(Math.sin(primary.rotY), 0, Math.cos(primary.rotY));
    _eyeGoal.set(
      _focus.x - _forward.x * horizontalDistance,
      _focus.y + verticalDistance,
      _focus.z - _forward.z * horizontalDistance,
    );

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
    camera.position.copy(legacyBlendEye(camera.position, _eyeGoal));
  }
}

/** DERIVED: FUN_8000fc2c interest — X/Z track the target, Y half-blends (FLOAT_80436ac4). */
function mode1InterestTarget(current: THREE.Vector3, target: THREE.Vector3): THREE.Vector3 {
  return _goal.set(
    target.x,
    (current.y + target.y) * MODE1_INTEREST_Y_BLEND_DERIVED,
    target.z,
  );
}

/** Legacy whole-eye 4/5 blend (pre-§ad shape: applied the XZ weights to Y as well). */
function legacyBlendEye(current: THREE.Vector3, target: THREE.Vector3): THREE.Vector3 {
  return _goal
    .copy(current)
    .multiplyScalar(MODE1_EYE_PREV_WEIGHT_DERIVED)
    .add(target)
    .multiplyScalar(1 / MODE1_EYE_BLEND_DENOMINATOR_DERIVED);
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
