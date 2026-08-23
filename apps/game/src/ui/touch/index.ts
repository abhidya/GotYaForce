/**
 * touch — mounts the ported GameCube on-screen overlay and keeps it sized to the viewport.
 *
 * The module-level accessor exists because the two things that need the pad are far apart
 * in the app (battle input in main.ts, menu input in ui/menuInput.ts) and menuInput.ts is
 * a standalone bus with no owner to thread an instance through. A single process-wide
 * overlay matches the reality that there is one screen and one pair of thumbs.
 */

import { createGcTouchOverlay, type GcTouchOverlay } from "./gcTouchOverlay.js";
import { isTouchDevice, lockLandscape, watchViewport } from "./orientation.js";

export { isTouchDevice, lockLandscape, unlockOrientation, watchViewport, readViewport } from "./orientation.js";
export type { GcTouchOverlay } from "./gcTouchOverlay.js";

/** Persisted user override of the auto-detected default. */
const STORAGE_KEY = "gf.touchControls.enabled";

let overlay: GcTouchOverlay | null = null;
let stopWatching: (() => void) | null = null;

function readStoredPreference(): boolean | null {
  try {
    const raw = localStorage.getItem(STORAGE_KEY);
    if (raw === "1") return true;
    if (raw === "0") return false;
  } catch {
    // Private-mode / disabled storage: fall back to auto-detection.
  }
  return null;
}

function writeStoredPreference(enabled: boolean): void {
  try {
    localStorage.setItem(STORAGE_KEY, enabled ? "1" : "0");
  } catch {
    // Non-fatal; the setting simply will not survive a reload.
  }
}

export interface TouchControlsHandle {
  readonly overlay: GcTouchOverlay;
  readonly enabled: boolean;
  setEnabled(enabled: boolean): void;
  destroy(): void;
}

/**
 * Mount the overlay. Idempotent — a second call returns the existing handle rather than
 * stacking a second set of controls over the first.
 *
 * Shown by default on touch devices and hidden elsewhere, with an explicit user override
 * taking precedence so a desktop tester can force it on (and a tablet user with a real
 * controller can force it off).
 */
export function initTouchControls(): TouchControlsHandle {
  if (!overlay) {
    overlay = createGcTouchOverlay();
    // Rotation support: re-resolve Dolphin's landscape/portrait coordinate sets whenever
    // the viewport changes. layout() picks the set itself from the new dimensions.
    stopWatching = watchViewport(() => overlay?.layout());
    overlay.setVisible(readStoredPreference() ?? isTouchDevice());
  }

  const live = overlay;
  return {
    overlay: live,
    get enabled() {
      return live.visible;
    },
    setEnabled(enabled: boolean): void {
      live.setVisible(enabled);
      writeStoredPreference(enabled);
    },
    destroy(): void {
      stopWatching?.();
      stopWatching = null;
      live.destroy();
      overlay = null;
    },
  };
}

/**
 * The overlay's synthetic standard-mapping pad, or null when it is absent or hidden.
 * Consumed by apps/game/src/main.ts (battle) and apps/game/src/ui/menuInput.ts (menus).
 */
export function touchGamepad(): Gamepad | null {
  return overlay?.getGamepad() ?? null;
}

/** True when the overlay is mounted and visible. */
export function touchControlsActive(): boolean {
  return overlay?.visible === true;
}

/**
 * Attempt a landscape lock, for callers that want it on a user gesture (the only context
 * where browsers permit it). Never required — the overlay has a real portrait layout.
 */
export async function requestLandscape(): Promise<boolean> {
  return lockLandscape();
}
