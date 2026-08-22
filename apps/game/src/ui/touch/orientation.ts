/**
 * orientation — screen-rotation support for the browser app.
 *
 * Three separate problems, none of which the app handled before:
 *
 * 1. WHEN DOES THE VIEWPORT ACTUALLY CHANGE. A single "resize" listener is not enough on
 *    mobile. iOS Safari fires resize BEFORE the rotation animation settles, so measuring
 *    in that handler yields the pre-rotation size; Android Chrome fires resize and
 *    orientationchange in either order. The fix used here is the conventional one: listen
 *    to every signal, coalesce them through rAF so a burst becomes one relayout, and add
 *    one deferred re-measure so a late-settling viewport is caught. Measuring twice is
 *    cheap; measuring once and being wrong is a broken layout until the next rotation.
 *
 * 2. VISUAL VIEWPORT vs LAYOUT VIEWPORT. Mobile browser chrome (URL bar) shrinks and grows
 *    the visual viewport without a layout resize, which is the classic "100vh is taller
 *    than the screen" bug. visualViewport events are included so the overlay tracks the
 *    space the player can actually touch.
 *
 * 3. LOCKING. screen.orientation.lock() is only permitted from fullscreen on the browsers
 *    that implement it at all (it is absent on iOS Safari entirely). It is therefore
 *    offered as a best-effort call that resolves to whether it worked — never awaited as
 *    though it were guaranteed, and never required for the app to function, because the
 *    overlay already carries Dolphin's portrait coordinate set as a real fallback.
 */

/** A viewport measurement plus the orientation bucket it implies. */
export interface ViewportState {
  readonly width: number;
  readonly height: number;
  readonly orientation: "landscape" | "portrait";
}

export type ViewportListener = (state: ViewportState) => void;

/** How long after a rotation signal to re-measure, for viewports that settle late. */
const SETTLE_DELAY_MS = 250;

export function readViewport(): ViewportState {
  // visualViewport is the space actually visible to the user; fall back to the layout
  // viewport where it is unavailable.
  const vv = window.visualViewport;
  const width = Math.round(vv?.width ?? window.innerWidth);
  const height = Math.round(vv?.height ?? window.innerHeight);
  return { width, height, orientation: height > width ? "portrait" : "landscape" };
}

/**
 * Call `listener` whenever the viewport meaningfully changes (rotation, browser-chrome
 * show/hide, window resize). Returns an unsubscribe function.
 */
export function watchViewport(listener: ViewportListener): () => void {
  // Coalescing uses a timer, NOT requestAnimationFrame. rAF is paused outright while the
  // document is hidden, so an rAF-coalesced relayout is silently dropped for any rotation
  // that happens in a background tab — the overlay then stays at the old orientation's
  // coordinates when the player comes back. menuInput.ts avoids rAF for the same reason
  // (its gamepad poll uses setInterval); this follows that precedent.
  let coalesceHandle: ReturnType<typeof setTimeout> | null = null;
  let settleHandle: ReturnType<typeof setTimeout> | null = null;
  let last: ViewportState | null = null;

  const emit = (): void => {
    coalesceHandle = null;
    const next = readViewport();
    // Suppress no-op churn: visualViewport fires continuously during URL-bar scroll.
    if (
      last &&
      last.width === next.width &&
      last.height === next.height &&
      last.orientation === next.orientation
    ) {
      return;
    }
    last = next;
    listener(next);
  };

  const schedule = (): void => {
    if (coalesceHandle === null) coalesceHandle = setTimeout(emit, 0);
  };

  const scheduleWithSettle = (): void => {
    schedule();
    // See note 1: one deferred re-measure catches viewports that settle after the event.
    if (settleHandle !== null) clearTimeout(settleHandle);
    settleHandle = setTimeout(() => {
      settleHandle = null;
      schedule();
    }, SETTLE_DELAY_MS);
  };

  window.addEventListener("resize", scheduleWithSettle);
  window.addEventListener("orientationchange", scheduleWithSettle);
  window.visualViewport?.addEventListener("resize", schedule);
  window.visualViewport?.addEventListener("scroll", schedule);
  // Some browsers expose the modern event and not the legacy one, and vice versa.
  screen.orientation?.addEventListener?.("change", scheduleWithSettle);
  // Re-measure on return to the foreground. Some engines suppress resize entirely while
  // hidden, so a rotation performed in a background tab may produce no event at all.
  document.addEventListener("visibilitychange", schedule);

  return () => {
    if (coalesceHandle !== null) clearTimeout(coalesceHandle);
    if (settleHandle !== null) clearTimeout(settleHandle);
    window.removeEventListener("resize", scheduleWithSettle);
    window.removeEventListener("orientationchange", scheduleWithSettle);
    window.visualViewport?.removeEventListener("resize", schedule);
    window.visualViewport?.removeEventListener("scroll", schedule);
    screen.orientation?.removeEventListener?.("change", scheduleWithSettle);
    document.removeEventListener("visibilitychange", schedule);
  };
}

/** True when the device reports touch input, which is what gates showing the overlay. */
export function isTouchDevice(): boolean {
  return (
    navigator.maxTouchPoints > 0 ||
    // Coarse pointer covers touch-primary devices that under-report maxTouchPoints.
    window.matchMedia?.("(pointer: coarse)").matches === true
  );
}

/**
 * Best-effort landscape lock. Resolves true only if the lock was actually applied.
 *
 * Locking requires fullscreen on every engine that supports it, and iOS Safari does not
 * implement screen.orientation.lock at all — so a false result is an expected outcome,
 * not an error. Callers must stay functional in portrait regardless.
 */
export async function lockLandscape(element: Element = document.documentElement): Promise<boolean> {
  const orientation = screen.orientation as (ScreenOrientation & {
    lock?: (o: string) => Promise<void>;
  }) | undefined;
  if (!orientation?.lock) return false;

  try {
    if (!document.fullscreenElement && element.requestFullscreen) {
      await element.requestFullscreen({ navigationUI: "hide" });
    }
    await orientation.lock("landscape");
    return true;
  } catch {
    // Rejected locks are routine: no fullscreen, no user gesture, or unsupported.
    return false;
  }
}

/** Release a landscape lock taken by lockLandscape. Safe to call unconditionally. */
export function unlockOrientation(): void {
  try {
    screen.orientation?.unlock?.();
  } catch {
    // Unsupported; nothing to release.
  }
}
