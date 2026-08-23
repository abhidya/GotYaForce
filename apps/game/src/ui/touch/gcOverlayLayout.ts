/**
 * gcOverlayLayout — Dolphin's GameCube on-screen overlay layout, transcribed.
 *
 * SOURCE (copied, not invented): dolphin-emu/dolphin, GPL-2.0-or-later.
 *   Source/Android/app/src/main/java/org/dolphinemu/dolphinemu/overlay/InputOverlay.kt
 *     - gcDefaultOverlay()        -> landscape positions
 *     - gcPortraitDefaultOverlay() -> portrait positions
 *     - initializeOverlayButton()/Dpad()/Joystick() -> per-control scale factors
 *     - resizeBitmap()            -> size is a fraction of the SMALLER screen dimension,
 *                                    which is what keeps buttons identically sized in
 *                                    both orientations.
 *   Source/Android/app/src/main/res/values/integers.xml -> the raw position integers.
 *
 * POSITION UNITS: Dolphin stores each coordinate as a per-mille int (0..1000) and resolves
 * it as `value / 1000 * maxX|maxY`, where landscape uses maxX = the LARGER screen dimension
 * and portrait uses maxX = the SMALLER one. In both cases that resolves to "X against
 * viewport width, Y against viewport height", so this port just multiplies by width/height.
 * The resulting point is the drawable's TOP-LEFT corner, exactly as in Dolphin.
 *
 * SIZE UNITS: Dolphin's resizeBitmap computes
 *     bitmapScale = scale * min(screenW, screenH) / max(bitmapW, bitmapH)
 * and the rendered edge is `bitmapDimension * bitmapScale`. Every gcpad/gcwii drawable in
 * drawable-xxhdpi is a square 384x384, so max(bitmapW, bitmapH) == bitmapDimension and the
 * whole expression collapses to `scale * min(screenW, screenH)`. That identity is why this
 * port can store a bare scale factor instead of carrying the bitmap dimensions around.
 *
 * SCALE BASELINE: Dolphin multiplies every scale by (MAIN_CONTROL_SCALE + 50) / 100.
 * Its default MAIN_CONTROL_SCALE is 50, giving a multiplier of exactly 1.0 — so the raw
 * scale factors below ARE the shipped defaults. `userScale` reintroduces that knob.
 */

/** Which orientation's coordinate set to resolve against. */
export type OverlayOrientation = "landscape" | "portrait";

/**
 * Standard-mapping gamepad button indices this overlay drives.
 *
 * The game already reads a `Gamepad` in two places, so the overlay reports itself AS one
 * rather than adding a third input path (see gcTouchOverlay.ts). These indices are chosen
 * to satisfy the BATTLE mapping in apps/game/src/sim/adapter.ts, which is the mapping that
 * has to be right:
 *   b0=A jump · b1=B attack · b2=X special · b3=Y hyper · b4=Z allyLock
 *   b5/b7=R switchLock · b6=L switchLockPrev · b9=Start · b12..15=D-pad
 * R drives BOTH 5 and 7 because adapter.ts accepts either (`b(5) || b(7)`) while
 * menuInput.ts reads 5 as "switch next" — one source, both consumers satisfied.
 *
 * MENU SIDE-EFFECT, deliberate and harmless: menuInput.ts maps b4 to "switch previous",
 * so GC Z cycles menu selections backwards, and it does not read b6, so GC L is inert in
 * menus. Battle correctness took priority over menu symmetry.
 */
export const PAD_BUTTON = {
  A: [0],
  B: [1],
  X: [2],
  Y: [3],
  Z: [4],
  R: [5, 7],
  L: [6],
  START: [9],
  DPAD_UP: [12],
  DPAD_DOWN: [13],
  DPAD_LEFT: [14],
  DPAD_RIGHT: [15],
} as const;

/** Highest standard-mapping index the overlay touches; sizes the synthetic button array. */
export const PAD_BUTTON_COUNT = 16;

export interface GcButtonSpec {
  readonly id: "A" | "B" | "X" | "Y" | "Z" | "L" | "R" | "START";
  /** Fraction of min(viewportW, viewportH); see SIZE UNITS above. */
  readonly scale: number;
  /** Per-mille [x, y] top-left, landscape (integers.xml BUTTON_*_X/Y). */
  readonly landscape: readonly [number, number];
  /** Per-mille [x, y] top-left, portrait (integers.xml BUTTON_*_PORTRAIT_X/Y). */
  readonly portrait: readonly [number, number];
  /** Basename of the released-state drawable, relative to the touch asset dir. */
  readonly art: string;
  /** Standard-mapping button indices this control asserts while held. */
  readonly padButtons: readonly number[];
}

/**
 * The eight GameCube face/shoulder buttons, with Dolphin's own scales and coordinates.
 * The C-stick is intentionally absent: nothing in apps/game/src/sim/adapter.ts reads a
 * second stick, so shipping one would place an inert control over the play area.
 */
export const GC_BUTTONS: readonly GcButtonSpec[] = [
  // scale 0.2   — InputOverlay.kt: ButtonType.BUTTON_A
  { id: "A", scale: 0.2, landscape: [865, 652], portrait: [638, 534], art: "gcpad_a", padButtons: PAD_BUTTON.A },
  // scale 0.125 — InputOverlay.kt `else -> 0.125f` branch
  { id: "B", scale: 0.125, landscape: [785, 524], portrait: [560, 648], art: "gcpad_b", padButtons: PAD_BUTTON.B },
  // scale 0.175 — ButtonType.BUTTON_X / BUTTON_Y
  { id: "X", scale: 0.175, landscape: [896, 388], portrait: [795, 519], art: "gcpad_x", padButtons: PAD_BUTTON.X },
  { id: "Y", scale: 0.175, landscape: [784, 297], portrait: [594, 463], art: "gcpad_y", padButtons: PAD_BUTTON.Y },
  // scale 0.225 — ButtonType.BUTTON_Z / TRIGGER_L / TRIGGER_R
  { id: "Z", scale: 0.225, landscape: [131, 431], portrait: [357, 560], art: "gcpad_z", padButtons: PAD_BUTTON.Z },
  { id: "L", scale: 0.225, landscape: [13, 330], portrait: [76, 582], art: "gcpad_l", padButtons: PAD_BUTTON.L },
  { id: "R", scale: 0.225, landscape: [845, 133], portrait: [739, 629], art: "gcpad_r", padButtons: PAD_BUTTON.R },
  // scale 0.075 — ButtonType.BUTTON_START
  { id: "START", scale: 0.075, landscape: [506, 818], portrait: [472, 789], art: "gcpad_start", padButtons: PAD_BUTTON.START },
];

/** D-pad: scale 0.2375 (InputOverlay.kt ButtonType.BUTTON_UP), art gcwii_dpad. */
export const GC_DPAD = {
  scale: 0.2375,
  landscape: [222, 629] as const,
  portrait: [44, 448] as const,
  art: "gcwii_dpad",
} as const;

/**
 * Main analog stick: outer ring scale 0.275, inner knob = outer / 1.375
 * (InputOverlay.kt initializeOverlayJoystick: `innerScale = 1.375f` for non-C sticks).
 */
export const GC_STICK = {
  scale: 0.275,
  innerDivisor: 1.375,
  landscape: [17, 620] as const,
  portrait: [134, 687] as const,
} as const;

/** Resolve a per-mille [x, y] pair to pixels against the live viewport. */
export function resolvePosition(
  perMille: readonly [number, number],
  viewportWidth: number,
  viewportHeight: number,
): { left: number; top: number } {
  return {
    left: (perMille[0] / 1000) * viewportWidth,
    top: (perMille[1] / 1000) * viewportHeight,
  };
}

/** Resolve a Dolphin scale factor to a pixel edge length. See SIZE UNITS above. */
export function resolveSize(
  scale: number,
  viewportWidth: number,
  viewportHeight: number,
  userScale = 1,
): number {
  return scale * userScale * Math.min(viewportWidth, viewportHeight);
}

/** Pick the coordinate set the way Dolphin does — by which viewport edge is longer. */
export function orientationOf(viewportWidth: number, viewportHeight: number): OverlayOrientation {
  return viewportHeight > viewportWidth ? "portrait" : "landscape";
}
