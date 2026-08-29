// Shared app-wide constants and small numeric helpers for the browser app.
//
// Scope: values that more than one module in apps/game needs, plus the unit
// conversions the ROM's own timing/angle units require. Values that belong to a
// single subsystem stay next to it (battle FX sizes in sim/battleScene.ts,
// HUD stage geometry in ui/hud/BattleHud.ts, camera blend weights in
// sim/camera.ts + sim/camera.generated.ts, sim tuning in @gf/combat constants).
//
// Confidence convention (packages/combat/src/constants.ts header): DERIVED =
// confirmed from ROM decomp/binary/trace with a citation; TUNED = an explicit,
// reasonable guess. Never silently promote a TUNED value.

// ------------------------------------------------------------------------------------------
// Source timing
// ------------------------------------------------------------------------------------------

/** DERIVED: the GameCube title runs its simulation and every animation clock at 60 Hz.
 *  Every "frames" quantity in ROM-derived data (anim clocks, cooldowns, effect lifetimes,
 *  battle timers) is in these frames. */
export const SOURCE_FRAME_RATE_HZ = 60;

/** One source frame in seconds — the fixed sim step and the anim-clock unit. */
export const SOURCE_FRAME_SECONDS = 1 / SOURCE_FRAME_RATE_HZ;

/** Convert a count of source (60 Hz) frames to seconds. */
export function framesToSeconds(frames: number): number {
  return frames / SOURCE_FRAME_RATE_HZ;
}

/** Convert a count of source (60 Hz) frames to milliseconds. */
export function framesToMilliseconds(frames: number): number {
  return (frames * 1000) / SOURCE_FRAME_RATE_HZ;
}

// ------------------------------------------------------------------------------------------
// Source angles
// ------------------------------------------------------------------------------------------

/** DERIVED: one GameCube BAM16 turn is 0x10000 units (the s16 angle space the ROM's
 *  rotation/spin/pitch fields live in). */
export const BAM16_UNITS_PER_TURN = 0x10000;

/** BAM16 angle unit -> radians. */
export const BAM16_TO_RADIANS = (Math.PI * 2) / BAM16_UNITS_PER_TURN;

// ------------------------------------------------------------------------------------------
// Shared numeric helpers
// ------------------------------------------------------------------------------------------

/** Clamp to the inclusive [lo, hi] range. */
export function clamp(value: number, lo: number, hi: number): number {
  let clamped = value;
  if (clamped < lo) clamped = lo;
  else if (clamped > hi) clamped = hi;
  return clamped;
}

/** Clamp a 0..1 progress/fraction value. */
export function clamp01(value: number): number {
  return clamp(value, 0, 1);
}

// ------------------------------------------------------------------------------------------
// Browser rendering
// ------------------------------------------------------------------------------------------

/** Cap for window.devicePixelRatio in every app-side WebGL surface (main viewport and the
 *  UI-scene / physical-menu previews). PORT-ISM, TUNED: the GameCube renders one fixed
 *  buffer; rendering a 3x-DPI backbuffer buys no fidelity and costs fill rate. */
export const MAX_DEVICE_PIXEL_RATIO = 2;
