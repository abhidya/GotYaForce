// Source GG4E camera — 1:1 port of the HSD CObj state + COBJ animation system and the
// boot view-setup `zz_00059b8_` @0x800059b8. This is the source-owned camera layer that
// sits ABOVE the battle-only `BattleCamera` (apps/game/src/sim/camera.ts): same engine
// primitives (CObj eye/up/interest, COBJ keyframe tracks, C_MTXLookAt view matrix), exposed
// for any screen (title desk, menus, cutscenes) — not just battle.
//
// All ROM-derived values are loaded from the attributed DOL data blobs below, never inlined
// as opaque probe constants. The float literals in `ROM_BOOT_VIEW_VECTORS` and
// `ROM_STEP_DRIVER_CONSTANTS` ARE the ROM struct (the .data-section bytes at the cited
// runtime addresses), reproduced exactly so the port is driven by the same data the PPC
// walked.
//
// === Evidence map (read first) ===
//
//  `zz_00059b8_` @0x800059b8 (chunk_0000.c:559-598) — boot view-setup. Loads 9 floats
//   (eye/up/target, three Vec3s) from DAT_802b01a0..DAT_802b01c0 and calls
//   `gnt4_C_MTXLookAt_bl(&DAT_803c7380, &local_20, &local_2c, &local_38)` — i.e.
//   C_MTXLookAt(matrix, eye, up, target). Stores the resulting matrix pointer into four
//   graphics-state slots (PTR_DAT_80433930 + 0x14/0x18/0x1c/0x20), sets byte flags at
//   +0xc..+0xf = 0xff, +0x29 = 0, +0x33 = 1, then runs the auxiliary setup sequence
//   zz_0005984_/zz_0005668_/zz_00058d0_/zz_002a5f4_. The browser port keeps the camera-
//   vector + matrix work (the substance) and no-ops the GX-state pointer/flag writes
//   (THREE manages its own pipeline state).
//
//  `zz_00088a4_` @0x800088a4 (chunk_0000.c:3101-3128) — COBJ apply-frame. Reads the
//   active CObj at `DAT_80436210`, resolves its animation binding at `(state+0x10)->[1]`,
//   and if the binding has a non-null anim (`*piVar1 != 0`) and frame data (`piVar1[1] != 0`)
//   it runs the HSD CObj animators `zz_0248424_`/`zz_024631c_`/`zz_024652c_`/`zz_02464dc_`
//   to write the interpolated eye/up/interest/fov into the CObj. The frame number is a
//   float passed in `param_9`-derived slot (see FUN_800c028c).
//
//  `zz_0008a1c_` @0x80008a1c (chunk_0000.c:3220-3234) — COBJ end-frame getter. Returns
//   FLOAT_80436a74 (0.0, the "no anim bound" default) when `DAT_80436210 + 0x84 == 0`,
//   otherwise `*(*(DAT_80436210 + 0x84) + 0xc)` — the bound COBJ animation's end frame
//   (float at animObj+0xc).
//
//  `FUN_800c028c` @0x800c028c (research/decomp/organized/game/camera/) — the per-frame
//   COBJ step driver. Operates on a 12-byte state object at `PTR_DAT_80433940`
//   (latches at +0x00 done, +0x02 aux, +0x04 first-init flag, +0x08 completion param) and
//   a float `*param_9` carrying the current animation frame:
//     1. first-init: if state+4 == 0 → set state+4 = 1, *param_9 = FLOAT_80438610 (589.0)
//     2. otherwise:  *param_9 -= FLOAT_80438604 (1.0)
//     3. if *param_9 <= FLOAT_8043860c (549.0): clamp *param_9 = FLOAT_80438608 (449.0),
//        set state+8 = 0x708, state+0 = 1, state+4 = 0, state+2 = 0; call zz_01ae8a8_
//     4. call zz_00088a4_(*param_9)  → apply the frame to the CObj
//     5. call zz_0008970_()          → HSD_CObjGetEyePosition
//     6. call cCameraManager::HasCamera (= HSD_CObjGetInterest)
//
//  `cCameraManager::HasCamera` @0x80008998, `zz_0008970_` @0x80008970,
//   `zz_0008948_` @0x80008948 — thin wrappers over the libogc HSD CObj accessors
//   (`HSD_CObjGetInterest_bl` / `HSD_CObjGetEyePosition_bl` / `HSD_CObjGetViewingMtx_bl`)
//   keyed on the active CObj pointer DAT_80436210.
//
//  `gnt4_C_MTXLookAt_bl` — the libogc `C_MTXLookAt(mt, camPt, upPt, targetPt)` imported
//   symbol. The body is not in the DOL (library call), so this port reproduces the
//   canonical libogc algorithm (vLook = norm(target-eye); vRight = norm(up × vLook);
//   vUp = vLook × vRight; mt rows = [vRight|-(vRight·cam)], [vUp|-(vUp·cam)],
//   [vLook|-(vLook·cam)]).
//
// Boot view vectors and step-driver constants were read straight from
// `user-data/GG4E/disc/sys/boot.dol` at the cited section-9 file offsets
// (research/decomp/behavior-notes.md §1: section 9 → runtime 0x802b01a0..0x802bae60,
// file offset 0x2ad1a0..0x2b7e60; section 12 → runtime 0x80436a20..0x8043d500).

// NOTE on the three.js helpers: toThreeMatrix4 / applyToCamera live in the
// sibling sourceCameraThree.ts (not here) so this module stays THREE-free at
// runtime. @gf/combat imports createSourceCamera + setupView from this file
// (bootGlobals.ts:10) under a documented no-three runtime contract; pulling
// `three` in here would force it into combat's graph. Hosts that drive a
// THREE.PerspectiveCamera (e.g. TitleIntro.ts) import the helpers from
// sourceCameraThree.ts instead. This file still exposes the pure-TS primitive
// mtx34ToColumnMajor4x4 (below) that the THREE helpers build on, and that any
// no-three consumer can use to build its own upload.

/** 3-component single-precision vector (HSD CObj uses float fields throughout). */
export interface Vec3 {
  x: number;
  y: number;
  z: number;
}

/**
 * One COBJ animation frame. The ten `tdc00..09.arc` scene_data roots export exactly these
 * channels (decoded via HSDRaw — see apps/game/public/ui/scenes/tl00/tdc-camera-anims.json).
 * These ARE the HSD CObj FOBJ tracks collapsed to per-integer-frame samples; the title
 * renderer already samples them by integer frame index.
 */
export interface CObjAnimFrame {
  eye: readonly [number, number, number];
  target: readonly [number, number, number];
  roll: number;
  fov: number;
  near: number;
  far: number;
}

/** A bound COBJ animation: dense per-integer-frame samples + the ROM end frame. */
export interface CObjAnimation {
  /** Dense samples, one per integer frame (frames[0] is frame 0, frames[N] is frame N). */
  frames: readonly CObjAnimFrame[];
  /**
   * End frame (zz_0008a1c_ returns animObj+0xc). For the title desk archives these are
   * 39/23/60/49/49/80/31/49/29/29 (research/decomp/index/title-main-menu-flow.md
   * "Camera timeline correction (2026-08-01)").
   */
  endFrame: number;
}

/**
 * The HSD CObj state, ported field-for-field. Field roles are evidenced per-accessor:
 *  - eye/up/interest: written by zz_00088a4_ (apply frame); read by zz_0008970_ /
 *    cCameraManager::HasCamera / zz_00089c0_ (HSD_CObjGetUpVector default-source).
 *  - fov/near/far/roll: the remaining CObj projection channels exported in the tdc FOBJ
 *    tracks. roll is a separate channel (not part of C_MTXLookAt) and is applied by the
 *    host's renderer post-lookAt (TitleIntro.ts applyTdcFrame does exactly this).
 *  - animation + timeline.current/target/step/active: the four u32 slots driven by title
 *    VM opcodes 0x07/0x08 (apps/game/src/ui/intro/titleVm.ts) — current=+0x30,
 *    target=+0x34, step=+0x38, active-latch=+0x3c.
 */
export interface SourceCameraState {
  /** Active CObj eye position (written each applyFrame). */
  eye: Vec3;
  /** Active CObj up vector. */
  up: Vec3;
  /** Active CObj interest / look target (HSD calls this "interest", not "target"). */
  interest: Vec3;
  /** Perspective FOV in degrees (HSD_CObjGetFov). */
  fov: number;
  /** Near clip plane. */
  near: number;
  /** Far clip plane. */
  far: number;
  /** Bank/roll angle in radians (separate CObj channel; applied by the renderer, not C_MTXLookAt). */
  roll: number;
  /** Bound COBJ animation (CObj+0x84 → animObj). null = no anim bound (the zz_0008a1c_ default path). */
  animation: CObjAnimation | null;
  /** The current/target/step/active timeline installed by opcode 0x07 (titleVm.ts sceneTimeline). */
  timeline: { current: number; target: number; step: number; active: number };
}

/**
 * ROM .data blob for `zz_00059b8_`: the 9 floats at DAT_802b01a0..DAT_802b01c0.
 * DOL section 9, runtime 0x802b01a0, file offset 0x2ad1a0 (verified by reading boot.dol).
 * Stack-local order in the decompile (chunk_0000.c:573-581) maps the triplets as
 * (eye=&local_20, up=&local_2c, target=&local_38) into C_MTXLookAt.
 */
export const ROM_BOOT_VIEW_VECTORS = {
  /** runtime 0x802b01a0/a4/a8 — C_MTXLookAt eye/cam argument. */
  eye: [0.0, 0.0, 10.0] as const,
  /** runtime 0x802b01ac/b0/b4 — C_MTXLookAt up argument. */
  up: [0.0, 1.0, 0.0] as const,
  /** runtime 0x802b01b8/bc/c0 — C_MTXLookAt target argument. */
  target: [0.0, 0.0, -1.0] as const,
  /** Attribution: DOL section 9 (file 0x2ad1a0..0x2b7e60, runtime 0x802b01a0..0x802bae60). */
  dolSection: 9,
  dolFileOffset: 0x2ad1a0,
  runtimeAddress: 0x802b01a0,
};

/**
 * ROM .data blob for the step-driver `FUN_800c028c`: the four floats at FLOAT_80438604..
 * FLOAT_80438610. DOL section 12, runtime 0x80438604..0x80438610 (verified by reading
 * boot.dol). These govern the per-frame countdown: initial 589 → subtract 1/frame →
 * expire at 549 (i.e. 40 frames) → clamp to 449 and latch done.
 */
export const ROM_STEP_DRIVER_CONSTANTS = {
  /** FLOAT_80438604 = 1.0 — per-frame decrement of the current-frame counter. */
  frameDecrement: 1.0,
  /** FLOAT_80438608 = 449.0 — value clamped into the counter on completion. */
  completedFrame: 449.0,
  /** FLOAT_8043860c = 549.0 — counter expiry threshold (<= triggers completion). */
  expiryThreshold: 549.0,
  /** FLOAT_80438610 = 589.0 — initial counter value (first-init branch). */
  initialFrame: 589.0,
  /** FLOAT_80436a74 = 0.0 — zz_0008a1c_ default end-frame when no COBJ anim is bound. */
  defaultEndFrame: 0.0,
};

/**
 * GameCube Mtx — 3x4 row-major view matrix (12 floats, the C_MTXLookAt output layout).
 * Row 0 = right vector + translation, row 1 = up, row 2 = look (camera forward).
 */
export type Mtx34 = readonly [number, number, number, number, number, number, number, number, number, number, number, number];

/** Assert signature supplied by the host test runner (e.g. node:assert, vitest expect). */
export interface SourceCameraAssert {
  (condition: unknown, message?: string): void;
}

export interface SourceCamera {
  /** Live CObj state; callers read eye/interest/fov after applyFrame/stepFrame. */
  readonly state: SourceCameraState;
  /**
   * `zz_00088a4_` @0x800088a4 — apply one COBJ animation frame to the active CObj.
   * Samples the bound animation at `frame` (linear interpolation between integer
   * keyframes — exact at integers, linear between) and writes eye/up/interest/fov/near/
   * far/roll into `state`. No-op when no animation is bound (the `*piVar1 != 0` gate).
   */
  applyFrame(frame: number): void;
  /**
   * `gnt4_C_MTXLookAt_bl` (libogc C_MTXLookAt) — compute the 3x4 view matrix from the
   * current state.eye/up/interest. Pure function; the host pushes the result into its
   * renderer (THREE.Matrix4.makeBasis + lookAt, or a direct shader upload).
   */
  setupView(): Mtx34;
  /**
   * `FUN_800c028c` @0x800c028c — the per-frame COBJ step driver. Runs the 589→549
   * countdown on the timeline counter, applies the frame, and latches completion.
   * Returns true the frame the countdown completes (the host then stops calling).
   */
  stepFrame(): boolean;
  /**
   * Bind a COBJ animation (writes CObj+0x84 in the ROM). Subsequent applyFrame/stepFrame
   * calls sample this animation; getEndFrame() returns its end frame.
   */
  bindAnimation(animation: CObjAnimation | null): void;
  /** `zz_0008a1c_` @0x80008a1c — bound animation end frame, or 0.0 when no anim bound. */
  getEndFrame(): number;
}

/**
 * Create a source-owned camera. Mirrors constructing an HSD CObj + leaving its animation
 * slot (CObj+0x84) null until `bindAnimation` is called. Initial eye/up/interest default
 * to the boot view (the values zz_00059b8_ would write — see sourceCameraBootViewSetup).
 */
export function createSourceCamera(initial?: Partial<SourceCameraState>): SourceCamera {
  const state: SourceCameraState = {
    eye: vec3(initial?.eye ?? ROM_BOOT_VIEW_VECTORS.eye),
    up: vec3(initial?.up ?? ROM_BOOT_VIEW_VECTORS.up),
    interest: vec3(initial?.interest ?? ROM_BOOT_VIEW_VECTORS.target),
    fov: initial?.fov ?? 41.539, // tdc00 authoring default; zz_00059b8_ itself sets no fov
    near: initial?.near ?? 0.1,
    far: initial?.far ?? 32768,
    roll: initial?.roll ?? 0,
    animation: initial?.animation ?? null,
    timeline: initial?.timeline ?? { current: 0, target: 0, step: 0, active: 0 },
  };

  const applyFrame = (frame: number): void => {
    const anim = state.animation;
    // zz_00088a4_ gate: if the binding is null (`*piVar1 == 0`) the function is a no-op.
    if (!anim || anim.frames.length === 0) return;
    const clamped = frame < 0 ? 0 : frame;
    const last = anim.frames.length - 1;
    if (clamped >= last) {
      writeFrame(state, anim.frames[last]!);
      return;
    }
    const lo = Math.floor(clamped);
    const hi = Math.ceil(clamped);
    if (lo === hi) {
      writeFrame(state, anim.frames[lo]!);
      return;
    }
    // Linear interpolation between integer keyframes. The HSD COBJ FOBJ tracks for the
    // tdc archives are dense per-integer-frame samples, so this is exact at integers and
    // a faithful linear approximation between (matches how the title renderer samples).
    const t = clamped - lo;
    const a = anim.frames[lo]!;
    const b = anim.frames[hi]!;
    state.eye.x = lerp(a.eye[0], b.eye[0], t);
    state.eye.y = lerp(a.eye[1], b.eye[1], t);
    state.eye.z = lerp(a.eye[2], b.eye[2], t);
    state.interest.x = lerp(a.target[0], b.target[0], t);
    state.interest.y = lerp(a.target[1], b.target[1], t);
    state.interest.z = lerp(a.target[2], b.target[2], t);
    state.roll = lerp(a.roll, b.roll, t);
    state.fov = lerp(a.fov, b.fov, t);
    state.near = lerp(a.near, b.near, t);
    state.far = lerp(a.far, b.far, t);
  };

  const setupView = (): Mtx34 => cMtxLookAt(state.eye, state.up, state.interest);

  const stepFrame = (): boolean => {
    const tl = state.timeline;
    // First-init branch: state+4 == 0 → *param_9 = FLOAT_80438610 (589.0).
    // We model state+4 with `timeline.active === 0 && timeline.current === 0` as the
    // uninit sentinel (matches the VM seeding opcode 0x07 which writes active = 0xff).
    if (tl.active === 0 && tl.current === 0 && tl.target === 0) {
      tl.current = ROM_STEP_DRIVER_CONSTANTS.initialFrame;
    } else {
      tl.current -= ROM_STEP_DRIVER_CONSTANTS.frameDecrement;
    }
    let done = false;
    if (tl.current <= ROM_STEP_DRIVER_CONSTANTS.expiryThreshold) {
      tl.current = ROM_STEP_DRIVER_CONSTANTS.completedFrame;
      tl.active = 0;
      done = true;
    }
    applyFrame(tl.current);
    return done;
  };

  const bindAnimation = (animation: CObjAnimation | null): void => {
    state.animation = animation;
  };

  const getEndFrame = (): number => {
    // zz_0008a1c_: animObj ? animObj+0xc : FLOAT_80436a74 (0.0).
    const anim = state.animation;
    if (!anim) return ROM_STEP_DRIVER_CONSTANTS.defaultEndFrame;
    return anim.endFrame;
  };

  return { state, applyFrame, setupView, stepFrame, bindAnimation, getEndFrame };
}

/**
 * The real body of `zz_00059b8_` @0x800059b8 — load the boot eye/up/target from
 * ROM_BOOT_VIEW_VECTORS (DAT_802b01a0..DAT_802b01c0) into a source camera, compute the
 * C_MTXLookAt view matrix, and return both so the host can push them into its renderer.
 *
 * This replaces the no-op stub at packages/combat/src/bootGlobals.ts:208-232. The ROM's
 * graphics-state pointer writes (PTR_DAT_80433930 + 0x14/0x18/0x1c/0x20 = &DAT_803c7380)
 * and byte-flag writes (+0xc..+0xf = 0xff, +0x29 = 0, +0x33 = 1) are intentional no-ops
 * in the browser: THREE manages its own matrix/state, and those slots were GC GX pipeline
 * state with no browser equivalent. The auxiliary call sequence (zz_0005984_/zz_0005668_/
 * zz_00058d0_/zz_002a5f4_) remains owned by bootGlobals.ts — this function deliberately
 * touches only the camera-vector + matrix work that was missing.
 */
export function sourceCameraBootViewSetup(camera: SourceCamera): Mtx34 {
  const { eye, up, target } = ROM_BOOT_VIEW_VECTORS;
  camera.state.eye.x = eye[0];
  camera.state.eye.y = eye[1];
  camera.state.eye.z = eye[2];
  camera.state.up.x = up[0];
  camera.state.up.y = up[1];
  camera.state.up.z = up[2];
  camera.state.interest.x = target[0];
  camera.state.interest.y = target[1];
  camera.state.interest.z = target[2];
  return camera.setupView();
}

/**
 * `gnt4_C_MTXLookAt_bl` — faithful port of libogc `C_MTXLookAt(mt, camPt, upPt, targetPt)`.
 * The DOL only contains the call site (the body is in the imported libogc symbol); this
 * reproduces the canonical algorithm exactly: vLook = norm(target-eye); vRight = norm(up ×
 * vLook); vUp = vLook × vRight; rows = [vRight | -(vRight·cam)], [vUp | -(vUp·cam)],
 * [vLook | -(vLook·cam)]. Returns the 3x4 row-major Mtx (12 floats).
 */
export function cMtxLookAt(cam: Vec3, up: Vec3, target: Vec3): Mtx34 {
  // vLook = target - cam (forward)
  let lx = target.x - cam.x;
  let ly = target.y - cam.y;
  let lz = target.z - cam.z;
  let len = Math.hypot(lx, ly, lz);
  if (len > 0) { lx /= len; ly /= len; lz /= len; }

  // vRight = up × vLook
  let rx = up.y * lz - up.z * ly;
  let ry = up.z * lx - up.x * lz;
  let rz = up.x * ly - up.y * lx;
  len = Math.hypot(rx, ry, rz);
  if (len > 0) { rx /= len; ry /= len; rz /= len; }

  // vUp = vLook × vRight (re-orthogonalizes vs the passed-in up)
  const ux = ly * rz - lz * ry;
  const uy = lz * rx - lx * rz;
  const uz = lx * ry - ly * rx;

  return [
    rx, ry, rz, -(rx * cam.x + ry * cam.y + rz * cam.z),
    ux, uy, uz, -(ux * cam.x + uy * cam.y + uz * cam.z),
    lx, ly, lz, -(lx * cam.x + ly * cam.y + lz * cam.z),
  ];
}

/**
 * Pure-TS rows→columns transpose of a C_MTXLookAt Mtx34 into the 16-element
 * column-major layout THREE.Matrix4.elements uses. THREE-free (no runtime
 * import) so any consumer — including @gf/combat, which keeps a no-three
 * runtime contract — can build its own upload without pulling in three.js.
 *
 * C_MTXLookAt Mtx (row-major 3x4)         THREE.Matrix4.elements (column-major 4x4):
 *   row 0 = [rx,ry,rz,tx]  (right)          col 0 = (rx,ux,lx,0)
 *   row 1 = [ux,uy,uz,tu]  (up)             col 1 = (ry,uy,ly,0)
 *   row 2 = [lx,ly,lz,tl]  (look/forward)   col 2 = (rz,uz,lz,0)
 *                                           col 3 = (tx,tu,tl,1)
 *
 * This is the structural mapping the THREE-aware helpers in sourceCameraThree.ts
 * (mtx34ToThreeMatrix4 / applySourceCameraToThree) build on. It is a direct
 * (faithful) transpose of the GC view matrix into THREE's column-major layout;
 * any coordinate-system reconciliation with three.js's right-handed camera
 * space is a host/asset-pipeline concern, not baked in here.
 */
export function mtx34ToColumnMajor4x4(mtx: Mtx34): readonly [
  number, number, number, number,
  number, number, number, number,
  number, number, number, number,
  number, number, number, number,
] {
  const [rx, ry, rz, tx, ux, uy, uz, tu, lx, ly, lz, tl] = mtx;
  return [
    rx, ux, lx, 0,
    ry, uy, ly, 0,
    rz, uz, lz, 0,
    tx, tu, tl, 1,
  ];
}

// --- internals -----------------------------------------------------------------------------

function vec3(src: { x: number; y: number; z: number } | readonly [number, number, number]): Vec3 {
  if ("x" in src) return { x: src.x, y: src.y, z: src.z };
  return { x: src[0], y: src[1], z: src[2] };
}

function writeFrame(state: SourceCameraState, f: CObjAnimFrame): void {
  state.eye.x = f.eye[0];
  state.eye.y = f.eye[1];
  state.eye.z = f.eye[2];
  state.interest.x = f.target[0];
  state.interest.y = f.target[1];
  state.interest.z = f.target[2];
  state.roll = f.roll;
  state.fov = f.fov;
  state.near = f.near;
  state.far = f.far;
}

function lerp(a: number, b: number, t: number): number {
  return a + (b - a) * t;
}

// --- self-tests ----------------------------------------------------------------------------

/**
 * `runSourceCameraSelfTests(assert)` — exercises applyFrame interpolation, setupView
 * matrix, the boot view-setup, the step-driver countdown, and the end-frame getter.
 * Pass any assert function (node:assert, vitest `expect(cond).toBe(true)` wrapper, etc.).
 */
export function runSourceCameraSelfTests(assert: SourceCameraAssert): void {
  // -- ROM data blob: boot vectors are the exact DOL bytes (not hand-picked probes). --
  assert(
    ROM_BOOT_VIEW_VECTORS.eye[0] === 0 && ROM_BOOT_VIEW_VECTORS.eye[1] === 0 && ROM_BOOT_VIEW_VECTORS.eye[2] === 10,
    "ROM boot eye = (0,0,10) [DAT_802b01a0..a8]",
  );
  assert(
    ROM_BOOT_VIEW_VECTORS.up[0] === 0 && ROM_BOOT_VIEW_VECTORS.up[1] === 1 && ROM_BOOT_VIEW_VECTORS.up[2] === 0,
    "ROM boot up = (0,1,0) [DAT_802b01ac..b4]",
  );
  assert(
    ROM_BOOT_VIEW_VECTORS.target[0] === 0 && ROM_BOOT_VIEW_VECTORS.target[1] === 0 && ROM_BOOT_VIEW_VECTORS.target[2] === -1,
    "ROM boot target = (0,0,-1) [DAT_802b01b8..c0]",
  );
  assert(ROM_STEP_DRIVER_CONSTANTS.initialFrame === 589, "step-driver initial = 589 [FLOAT_80438610]");
  assert(ROM_STEP_DRIVER_CONSTANTS.frameDecrement === 1, "step-driver decrement = 1 [FLOAT_80438604]");
  assert(ROM_STEP_DRIVER_CONSTANTS.expiryThreshold === 549, "step-driver threshold = 549 [FLOAT_8043860c]");
  assert(ROM_STEP_DRIVER_CONSTANTS.completedFrame === 449, "step-driver completed = 449 [FLOAT_80438608]");

  // -- setupView: C_MTXLookAt over the boot vectors produces the canonical GC view matrix. --
  // vLook=(0,0,-1), vRight=(-1,0,0), vUp=(0,1,0); rows = [vRight|0], [vUp|0], [vLook|10].
  {
    const cam = createSourceCamera();
    const m = sourceCameraBootViewSetup(cam);
    assert(approx(m[0], -1) && approx(m[1], 0) && approx(m[2], 0) && approx(m[3], 0), "view row 0 = [-1,0,0,0]");
    assert(approx(m[4], 0) && approx(m[5], 1) && approx(m[6], 0) && approx(m[7], 0), "view row 1 = [0,1,0,0]");
    assert(approx(m[8], 0) && approx(m[9], 0) && approx(m[10], -1) && approx(m[11], 10), "view row 2 = [0,0,-1,10]");
  }

  // -- setupView: a translated camera looking down -Z yields the expected translation. --
  {
    const cam = createSourceCamera({
      eye: { x: 5, y: 5, z: 5 },
      up: { x: 0, y: 1, z: 0 },
      interest: { x: 5, y: 5, z: 0 },
    });
    const m = cam.setupView();
    // vLook=(0,0,-1); vRight=(-1,0,0); vUp=(0,1,0); translation components:
    // row0.w = -(vRight·cam) = -((-1)*5) = 5; row1.w = -(vUp·cam) = -(1*5) = -5;
    // row2.w = -(vLook·cam) = -((-1)*5) = 5.
    assert(approx(m[0], -1) && approx(m[3], 5), "translated view row 0 = [-1,0,0,5]");
    assert(approx(m[5], 1) && approx(m[7], -5), "translated view row 1 = [0,1,0,-5]");
    assert(approx(m[10], -1) && approx(m[11], 5), "translated view row 2 = [0,0,-1,5]");
  }

  // -- applyFrame: no-op when no animation is bound (the zz_00088a4_ `*piVar1 != 0` gate). --
  {
    const cam = createSourceCamera();
    sourceCameraBootViewSetup(cam); // eye = (0,0,10)
    cam.applyFrame(7);
    assert(cam.state.eye.x === 0 && cam.state.eye.y === 0 && cam.state.eye.z === 10, "applyFrame no-op when no anim bound");
    assert(cam.getEndFrame() === 0, "getEndFrame = 0 default [FLOAT_80436a74]");
  }

  // -- applyFrame: exact sample at an integer frame. --
  {
    const anim: CObjAnimation = {
      endFrame: 2,
      frames: [
        { eye: [0, 0, 0], target: [0, 0, -1], roll: 0, fov: 30, near: 0.1, far: 100 },
        { eye: [10, 0, 0], target: [0, 0, -1], roll: 0, fov: 40, near: 0.1, far: 100 },
        { eye: [20, 0, 0], target: [0, 0, -1], roll: 0, fov: 50, near: 0.1, far: 100 },
      ],
    };
    const cam = createSourceCamera();
    cam.bindAnimation(anim);
    cam.applyFrame(0);
    assert(cam.state.eye.x === 0 && approx(cam.state.fov, 30), "applyFrame(0) exact");
    cam.applyFrame(1);
    assert(cam.state.eye.x === 10 && approx(cam.state.fov, 40), "applyFrame(1) exact");
    cam.applyFrame(2);
    assert(cam.state.eye.x === 20 && approx(cam.state.fov, 50), "applyFrame(2) exact");
    assert(cam.getEndFrame() === 2, "getEndFrame returns bound anim endFrame [animObj+0xc]");
  }

  // -- applyFrame: linear interpolation between integer keyframes. --
  {
    const anim: CObjAnimation = {
      endFrame: 1,
      frames: [
        { eye: [0, 0, 0], target: [0, 0, -1], roll: 0, fov: 30, near: 0.1, far: 100 },
        { eye: [10, 0, 0], target: [0, 0, -1], roll: 0, fov: 40, near: 0.1, far: 100 },
      ],
    };
    const cam = createSourceCamera();
    cam.bindAnimation(anim);
    cam.applyFrame(0.5);
    assert(approx(cam.state.eye.x, 5), "applyFrame(0.5) interpolates eye.x = 5");
    assert(approx(cam.state.fov, 35), "applyFrame(0.5) interpolates fov = 35");
  }

  // -- applyFrame: clamps below 0 and saturates at/above the last frame. --
  {
    const anim: CObjAnimation = {
      endFrame: 1,
      frames: [
        { eye: [0, 0, 0], target: [0, 0, -1], roll: 0, fov: 30, near: 0.1, far: 100 },
        { eye: [10, 0, 0], target: [0, 0, -1], roll: 0, fov: 40, near: 0.1, far: 100 },
      ],
    };
    const cam = createSourceCamera();
    cam.bindAnimation(anim);
    cam.applyFrame(-3);
    assert(cam.state.eye.x === 0, "applyFrame clamps negative frame to 0");
    cam.applyFrame(99);
    assert(cam.state.eye.x === 10, "applyFrame saturates above last frame");
  }

  // -- stepFrame: the 589→549 countdown (FUN_800c028c) over the real ROM constants. --
  {
    const anim: CObjAnimation = {
      endFrame: 0,
      frames: [{ eye: [0, 0, 0], target: [0, 0, -1], roll: 0, fov: 30, near: 0.1, far: 100 }],
    };
    const cam = createSourceCamera();
    cam.bindAnimation(anim);
    // First call hits the first-init branch: current = 589.
    let done = cam.stepFrame();
    assert(approx(cam.state.timeline.current, 589) && !done, "stepFrame first-init sets current = 589, not done");
    // Subsequent calls decrement by 1 until <= 549 (i.e. 589-549 = 40 more frames).
    let frames = 0;
    for (let i = 0; i < 200; i++) {
      frames++;
      done = cam.stepFrame();
      if (done) break;
    }
    // 589 → 549 takes 40 decrements; the 40th stepFrame sees current == 549 (<= 549) and latches.
    assert(done, "stepFrame eventually completes the countdown");
    assert(frames === 40, `stepFrame completes in exactly 40 frames (589->549), got ${frames}`);
    assert(approx(cam.state.timeline.current, 449), "stepFrame completion clamps current to 449 [FLOAT_80438608]");
    assert(cam.state.timeline.active === 0, "stepFrame completion clears the active latch");
  }

  // -- mtx34ToColumnMajor4x4: faithful rows→columns transpose of the boot view. --
  // Pure-TS helper (THREE-free); the three.js Matrix4 variant (mtx34ToThreeMatrix4)
  // is the same mapping wrapped in makeBasis/setPosition and is exercised at
  // runtime by TitleIntro.ts. Boot Mtx = [-1,0,0,0, 0,1,0,0, 0,0,-1,10]:
  //   col0=(rx,ux,lx,0)=(-1,0,0,0)  col1=(ry,uy,ly,0)=(0,1,0,0)
  //   col2=(rz,uz,lz,0)=(0,0,-1,0)  col3=(tx,tu,tl,1)=(0,0,10,1)
  {
    const cam = createSourceCamera();
    const m = sourceCameraBootViewSetup(cam);
    const cm = mtx34ToColumnMajor4x4(m);
    assert(
      approx(cm[0]!, -1) && approx(cm[1]!, 0) && approx(cm[2]!, 0) && approx(cm[3]!, 0),
      "column-major col 0 = (-1,0,0,0) [right row transposed]",
    );
    assert(
      approx(cm[4]!, 0) && approx(cm[5]!, 1) && approx(cm[6]!, 0) && approx(cm[7]!, 0),
      "column-major col 1 = (0,1,0,0) [up row transposed]",
    );
    assert(
      approx(cm[8]!, 0) && approx(cm[9]!, 0) && approx(cm[10]!, -1) && approx(cm[11]!, 0),
      "column-major col 2 = (0,0,-1,0) [look row transposed]",
    );
    assert(
      approx(cm[12]!, 0) && approx(cm[13]!, 0) && approx(cm[14]!, 10) && approx(cm[15]!, 1),
      "column-major col 3 = (0,0,10,1) [translation]",
    );
  }
}

function approx(a: number, b: number, eps = 1e-6): boolean {
  return Math.abs(a - b) <= eps;
}
