// Battle camera — follow/frame logic for the challenge-mode viewport.
//
// Confidence convention (see packages/combat/src/constants.ts header + research/decomp/
// behavior-notes.md): DERIVED = confirmed from ROM decomp/binary/live-memory-trace with a
// cited address/evidence source. TUNED = an explicit, reasonable guess. Never silently
// upgrade a TUNED value to DERIVED.
//
// ---------------------------------------------------------------------------------------
// What's real (DERIVED) vs designed-by-us (TUNED) for this camera, and why:
//
// research/decomp/behavior-notes.md was searched in full (no prior "camera" section existed
// before this pass) and the decompiled corpus (research/decomp/ghidra-export/, 11,972
// functions) was grepped for camera-adjacent code. Result:
//
//  - The engine exposes a full HSD camera-OBJECT primitive suite (`HSD_CObjSetEyePosition`
//    0x80247270, `HSD_CObjSetInterest` 0x80247198, `HSD_CObjSetFov`/`GetFov` 0x8024807c/
//    0x80248058, `HSD_CObjSetupViewingMtx` 0x80246ab8, all chunk_0070.c) — this is generic
//    shared HAL/AM2-lineage ("HSD"/Sysdolphin) engine plumbing, the same library used by
//    GameCube-era Melee/Kirby Air Ride. These are primitives ("set the eye position to X"),
//    not policy ("what X should be this frame for a Gotcha Force battle").
//  - No caller of any of those primitives is resolvable anywhere else in the corpus by static
//    address (they're dispatched through a C++ vtable on a `cBaseCamera`-style object, not a
//    direct `bl` Ghidra can attribute) — a direct-address grep across all 80 chunks confirms
//    zero call sites outside their own definitions. `cCameraManager::HasCamera` (0x80008998)
//    and `nlDLRingGetStart<cBaseCamera>` (0x802af478) are the only named C++ camera-manager
//    symbols in the whole 11,972-function index, and both are generic object-manager/ring-
//    buffer boilerplate, not gameplay-specific framing logic.
//  - A dedicated static-code search for a per-frame "camera update" function (reading the
//    6-actor battle table `DAT_803c4e84` across multiple slots, or computing a multi-actor
//    midpoint/spread) found no candidate — every multi-slot reader of that table is AI
//    targeting/separation code, and every midpoint/sqrt-heavy function is HSD skeletal IK,
//    not camera framing. Conclusion: there is no statically-locatable dedicated camera-policy
//    function in this corpus (plausibly because it's dispatched via vtable, or is simpler/
//    more scripted than expected). This mirrors the honest "not found" conclusions already on
//    record for CPU-AI target-selection (behavior-notes.md §q) and dash/jump constants (§s).
//  - research/decomp/ram-trace-analysis.md §3.1 (an EARLIER, already-existing live 2-save-state
//    MEM1 diff, not new work from this pass) independently found a genuine runtime camera
//    object at RAM 0x806A5300: a position with a sliding history buffer (smoothed, not an
//    instant snap) plus an embedded 3x3 look-at matrix at 0x806A53A4, tracking toward the
//    player. Two comparable frames give: constant height offset player+60 units (Y: cam=70.0
//    vs player=10.0 in both samples — the one clean, repeated number here) and a horizontal
//    trailing distance of ~467-505 units (noisy over just 2 samples, DERIVED-but-low-confidence
//    for the exact magnitude, though the fact of "roughly ~470-510" and "smoothed/lagged, not
//    instant" is solid). This is the best real evidence available; it does NOT cover multi-actor
//    framing/zoom (only one borg was on-screen in that trace).
//  - research/asset-inventory/stage-lighting-render-state.md's static `st00_mdl.arc` CObj scan
//    gives an exact DERIVED initial/stage camera setup (eye/interest/fov/near/far baked into the
//    stage file) — already wired via DEFAULT_RENDER_STATE.fov/near/far (43.191872/10/80000) in
//    main.ts; that part predates this pass and needed no change, just this citation.
//  - research/traces/GG4E/dolphin-gdb-trace-results.md's live GDB trace confirms the
//    `C_MTXLookAt` callsite (0x8020b61c) is real and hit 65x in one pass, and later traced two
//    callers (0x8008c93c, 0x8008ca90) — but those captured fixed setup vectors (e.g.
//    eye=[0,0,100], interest=[0,0,-100]), not target-relative gameplay values, and the file's own
//    "Implementation Gate" section explicitly says this "proves camera callsite/capture path,
//    but not enough to replace the browser gameplay follow camera formula yet." Treated here as
//    confirming the mechanism (a real look-at matrix is computed every frame) without supplying
//    portable per-frame numbers.
//
// So: height offset (DERIVED, ~60 units above target) and smoothing behavior (DERIVED,
// lagged/lerped rather than snapped) are ROM-confirmed via live trace. Horizontal follow
// distance is DERIVED-but-approximate (~470-510, 2-sample trace). Multi-actor dynamic framing
// (zooming/widening to keep 2 vs 3+ spread-apart borgs all in view) has NO ROM evidence either
// way and is TUNED here as a standard fighting-game camera practice, clearly separated below so
// nobody mistakes it for a ROM-confirmed algorithm.
// ---------------------------------------------------------------------------------------

import * as THREE from "three";

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
 * above the tracked player (Y=70.0 vs player Y=10.0) in both sampled frames. */
export const CAMERA_HEIGHT_OFFSET_DERIVED = 60;

/** DERIVED-but-approximate: ram-trace-analysis.md §3.1 — horizontal camera-to-player distance
 * measured 466.5 and 504.9 world units across the only two sampled frames (mean ~485). Treated
 * as the base trailing distance for a single, un-spread-out target. Only two samples exist, so
 * this is real ROM evidence but not a tightly-bounded constant — do not treat the exact value as
 * more precise than "roughly high-400s". */
export const CAMERA_BASE_DISTANCE_DERIVED = 485;

/** TUNED: how strongly the camera trails behind the target's facing direction rather than
 * sitting at a neutral angle. The live trace's yaw-vs-player-heading relationship was not
 * internally consistent enough across only 2 frames to derive a fixed trail angle (see
 * behavior-notes.md camera section), so this stays a designed choice, not a ROM number. */
const TRAIL_BEHIND_WEIGHT_TUNED = 1.0;

/** TUNED: smoothing rate. The live trace confirms the camera is smoothed/lagged (a sliding
 * position-history buffer), not snapped, but the exact filter constant/time-window was not
 * recoverable from 2 samples. This lerp factor is a standard-feel approximation. */
const POSITION_SMOOTHING_TUNED = 0.08;
const TARGET_SMOOTHING_TUNED = 0.1;

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
  constructor(private readonly opts: BattleCameraOptions) {}

  update(
    primary: CameraFollowTarget | null,
    allActorPositions: readonly THREE.Vector3[],
    stageBounds: StageBoundsLike,
  ): void {
    const { camera, controlsTarget } = this.opts;
    const focusBase = primary?.pos ?? _center.set(0, 80, 0);
    _focus.set(focusBase.x, focusBase.y + 90, focusBase.z);
    controlsTarget.lerp(_focus, TARGET_SMOOTHING_TUNED);

    if (!primary) return;

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
    const height = CAMERA_HEIGHT_OFFSET_DERIVED + extraHeight;

    _forward.set(Math.sin(primary.rotY), 0, Math.cos(primary.rotY)).multiplyScalar(
      TRAIL_BEHIND_WEIGHT_TUNED,
    );
    _goal.set(
      focusBase.x - _forward.x * distance,
      focusBase.y + height * 7, // matches the original 700:420-ish trail-height ratio (TUNED feel)
      focusBase.z - _forward.z * distance,
    );

    // Keep the browser camera inside the exported arena shell instead of letting the normal
    // trailing point sit behind a wall/ceiling at spawn. TUNED guard (no ROM collision data
    // for the gameplay camera has been traced yet — see module header).
    const centerX = (stageBounds.minX + stageBounds.maxX) * 0.5;
    const centerZ = (stageBounds.minZ + stageBounds.maxZ) * 0.5;
    const currentRadius = Math.hypot(focusBase.x - centerX, focusBase.z - centerZ);
    const goalRadius = Math.hypot(_goal.x - centerX, _goal.z - centerZ);
    const shellGuardRadius =
      Math.min(stageBounds.maxX - stageBounds.minX, stageBounds.maxZ - stageBounds.minZ) * 0.25;
    if (currentRadius > shellGuardRadius && goalRadius > currentRadius + 80) {
      _inward.set(centerX - focusBase.x, 0, centerZ - focusBase.z);
      if (_inward.lengthSq() < 0.0001) _inward.copy(_forward).multiplyScalar(-1);
      _inward.normalize();
      const pullDistance = distance * 1.57; // preserves original 700->1100 ratio
      const pullHeight = height * 9.33; // preserves original 420->560 -> now scaled off height offset
      _goal.set(
        focusBase.x + _inward.x * pullDistance,
        focusBase.y + pullHeight,
        focusBase.z + _inward.z * pullDistance,
      );
    }

    camera.position.lerp(_goal, POSITION_SMOOTHING_TUNED);
  }
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
