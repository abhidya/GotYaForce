/**
 * gcTouchOverlay — Dolphin's Android GameCube on-screen controller, ported to the DOM.
 *
 * SOURCE (copied, not invented): dolphin-emu/dolphin, GPL-2.0-or-later,
 *   Source/Android/app/src/main/java/org/dolphinemu/dolphinemu/overlay/
 *     InputOverlay.kt                  -> onTouch() dispatch, D-pad thirds hit test
 *     InputOverlayDrawableButton.kt    -> per-control trackId press/release model
 *     InputOverlayDrawableDpad.kt      -> 9 press states + rotation of the 1-/2-direction art
 *     InputOverlayDrawableJoystick.kt  -> trackEvent(): capture, normalise, recentre
 * Layout constants live in ./gcOverlayLayout.ts with their own provenance notes.
 *
 * WHY IT REPORTS AS A GAMEPAD: this app already reads controllers in two independent
 * places — apps/game/src/sim/adapter.ts inputFromKeys(keys, pad) for battle, and
 * apps/game/src/ui/menuInput.ts pollGamepads() for every menu screen. Rather than add a
 * third input path (and re-derive both mappings, which is where a hand-rolled touch layer
 * would drift), the overlay publishes a synthetic standard-mapping Gamepad. Both existing
 * consumers then work untouched, including every binding they already document.
 *
 * FIDELITY NOTES — the two places this knowingly departs from Dolphin:
 *  1. Stick gate. Dolphin clamps the stick against the real GameCube octagonal gate via
 *     the native InputOverrider.getGateRadiusAtAngle(). That is C++ behind JNI with no web
 *     equivalent, so this clamps to the unit circle instead. Visible only as slightly
 *     shorter throw at the octagon's corners; full range on the cardinals is identical.
 *  2. Rendering. Dolphin draws to a Canvas and calls invalidate(). This uses stacked <img>
 *     layers with opacity toggles so the compositor handles redraw, which avoids running a
 *     second canvas over the WebGL surface. Hit testing is still done against rectangles in
 *     script — NOT via DOM hit testing — so the press/capture semantics stay Dolphin's.
 *
 * PRESS SEMANTICS (Dolphin's, preserved deliberately): a control is captured by the pointer
 * id that pressed it and is released ONLY by that pointer's up/cancel. Dragging off a button
 * does not release it. Multi-touch works because every control tracks its own pointer id.
 */

import {
  GC_BUTTONS,
  GC_DPAD,
  GC_STICK,
  PAD_BUTTON,
  PAD_BUTTON_COUNT,
  orientationOf,
  resolvePosition,
  resolveSize,
  type GcButtonSpec,
  type OverlayOrientation,
} from "./gcOverlayLayout.js";
import { publicUrl } from "../../publicUrl.js";

/**
 * Where the Dolphin drawables were vendored to (apps/game/public/ui/touch).
 * Resolved through publicUrl() at use, because runtime-constructed asset URLs are not
 * rewritten by Vite's `base` and would 404 on the /GotYaForce/game/ Pages subpath.
 */
const ART_BASE = "ui/touch";

/** No pointer owns this control. Dolphin uses -1 for the same purpose. */
const NO_POINTER = -1;

export interface GcTouchOverlayOptions {
  /** Container the overlay mounts into. Defaults to document.body. */
  readonly parent?: HTMLElement;
  /** Multiplies every Dolphin scale; 1 = Dolphin's shipped default. */
  readonly userScale?: number;
  /** 0..1 control opacity. Dolphin's own default setting is 100%. */
  readonly opacity?: number;
  /**
   * Dolphin's MAIN_JOYSTICK_REL_CENTER, whose upstream default is on: pressing anywhere
   * inside the stick ring re-centres the ring under the finger for that gesture.
   */
  readonly relativeStickCenter?: boolean;
  /** Base path for the drawables. Override when the app is served from a subpath. */
  readonly artBase?: string;
}

/** A rectangle in CSS pixels relative to the viewport. */
interface Rect {
  left: number;
  top: number;
  width: number;
  height: number;
}

function rectContains(r: Rect, x: number, y: number): boolean {
  return x >= r.left && x < r.left + r.width && y >= r.top && y < r.top + r.height;
}

/** A two-layer image control: released art under pressed art, cross-faded by opacity. */
interface LayeredArt {
  root: HTMLDivElement;
  released: HTMLImageElement;
  pressed: HTMLImageElement;
}

interface ButtonControl {
  spec: GcButtonSpec;
  art: LayeredArt;
  rect: Rect;
  trackId: number;
  isPressed: boolean;
}

interface DpadControl {
  root: HTMLDivElement;
  released: HTMLImageElement;
  oneWay: HTMLImageElement;
  twoWay: HTMLImageElement;
  rect: Rect;
  trackId: number;
  /** [up, down, left, right] — Dolphin's control index order. */
  pressed: [boolean, boolean, boolean, boolean];
}

interface StickControl {
  root: HTMLDivElement;
  range: HTMLImageElement;
  outer: HTMLImageElement;
  inner: HTMLImageElement;
  /** The control's resting bounds; restored on release. */
  origRect: Rect;
  /** The live bounds, which relative-centre mode offsets under the finger. */
  virtRect: Rect;
  innerSize: number;
  trackId: number;
  x: number;
  y: number;
}

function img(src: string): HTMLImageElement {
  const el = document.createElement("img");
  el.src = publicUrl(src);
  el.draggable = false;
  el.alt = "";
  el.setAttribute("aria-hidden", "true");
  el.style.cssText =
    "position:absolute;inset:0;width:100%;height:100%;display:block;" +
    "user-select:none;-webkit-user-drag:none;pointer-events:none;";
  return el;
}

function layer(base: string, releasedArt: string, pressedArt: string): LayeredArt {
  const root = document.createElement("div");
  root.style.cssText = "position:absolute;pointer-events:none;will-change:transform;";
  const released = img(`${base}/${releasedArt}.png`);
  const pressed = img(`${base}/${pressedArt}.png`);
  pressed.style.opacity = "0";
  root.append(released, pressed);
  return { root, released, pressed };
}

/**
 * Position an element from a VIEWPORT-space rect.
 *
 * Rects are kept in viewport space because that is the space pointer events report in, so
 * hit testing needs no conversion. The elements themselves are children of the overlay
 * root, which index.html insets by the safe-area env() values — so placing them requires
 * subtracting the root origin. Script must not subtract the insets itself; CSS owns them.
 */
function place(el: HTMLElement, rect: Rect, originX: number, originY: number): void {
  el.style.left = `${rect.left - originX}px`;
  el.style.top = `${rect.top - originY}px`;
  el.style.width = `${rect.width}px`;
  el.style.height = `${rect.height}px`;
}

/**
 * The live overlay. The synthetic pad is rebuilt on demand so callers always observe
 * current state rather than a stale snapshot.
 */
export interface GcTouchOverlay {
  /** True while the overlay is mounted and visible. */
  readonly visible: boolean;
  /** Show/hide without tearing down. Hiding releases every held control first. */
  setVisible(visible: boolean): void;
  /**
   * A standard-mapping Gamepad snapshot, or null while hidden. Shaped to satisfy the
   * Gamepad interface so adapter.ts and menuInput.ts consume it unmodified.
   */
  getGamepad(): Gamepad | null;
  /** Recompute every control's rect for the current viewport/orientation. */
  layout(): void;
  /** Current orientation bucket, as Dolphin picks it (by which edge is longer). */
  readonly orientation: OverlayOrientation;
  /** Remove listeners and DOM. */
  destroy(): void;
}

export function createGcTouchOverlay(options: GcTouchOverlayOptions = {}): GcTouchOverlay {
  const parent = options.parent ?? document.body;
  const userScale = options.userScale ?? 1;
  const opacity = options.opacity ?? 1;
  const relativeStickCenter = options.relativeStickCenter ?? true;
  const artBase = options.artBase ?? ART_BASE;

  // pointer-events:none on the root so taps that miss a control still reach the page
  // (the audio-unlock pointerdown in main.ts, for one). Hit testing is manual, against
  // the rects below, which is also what keeps Dolphin's capture semantics intact.
  const root = document.createElement("div");
  root.dataset["gcTouchOverlay"] = "";
  // Inset by the safe area so controls clear the notch and home indicator. These are set
  // inline rather than in a stylesheet because an inline `inset:0` would out-specify the
  // stylesheet rule; keeping it here also makes the overlay self-contained. layout() then
  // measures this element's own box, so the insets are applied exactly once.
  root.style.cssText =
    "position:fixed;" +
    "top:env(safe-area-inset-top,0px);right:env(safe-area-inset-right,0px);" +
    "bottom:env(safe-area-inset-bottom,0px);left:env(safe-area-inset-left,0px);" +
    `pointer-events:none;touch-action:none;z-index:40;opacity:${opacity};`;

  const buttons: ButtonControl[] = GC_BUTTONS.map((spec) => {
    const art = layer(artBase, spec.art, `${spec.art}_pressed`);
    root.appendChild(art.root);
    return {
      spec,
      art,
      rect: { left: 0, top: 0, width: 0, height: 0 },
      trackId: NO_POINTER,
      isPressed: false,
    };
  });

  const dpad: DpadControl = (() => {
    const host = document.createElement("div");
    host.style.cssText = "position:absolute;pointer-events:none;";
    const released = img(`${artBase}/${GC_DPAD.art}.png`);
    const oneWay = img(`${artBase}/${GC_DPAD.art}_pressed_one_direction.png`);
    const twoWay = img(`${artBase}/${GC_DPAD.art}_pressed_two_directions.png`);
    oneWay.style.opacity = "0";
    twoWay.style.opacity = "0";
    host.append(released, oneWay, twoWay);
    root.appendChild(host);
    return {
      root: host,
      released,
      oneWay,
      twoWay,
      rect: { left: 0, top: 0, width: 0, height: 0 },
      trackId: NO_POINTER,
      pressed: [false, false, false, false] as [boolean, boolean, boolean, boolean],
    };
  })();

  const stick: StickControl = (() => {
    const host = document.createElement("div");
    host.style.cssText = "position:absolute;pointer-events:none;";
    const range = img(`${artBase}/gcwii_joystick_range.png`);
    const outer = img(`${artBase}/gcwii_joystick.png`);
    const inner = img(`${artBase}/gcwii_joystick_pressed.png`);
    // Dolphin draws the ring plus the knob; the knob is absolutely placed by setInnerBounds.
    outer.style.opacity = "0";
    inner.style.cssText =
      "position:absolute;display:block;user-select:none;-webkit-user-drag:none;pointer-events:none;";
    host.append(range, outer, inner);
    root.appendChild(host);
    const empty: Rect = { left: 0, top: 0, width: 0, height: 0 };
    return {
      root: host,
      range,
      outer,
      inner,
      origRect: { ...empty },
      virtRect: { ...empty },
      innerSize: 0,
      trackId: NO_POINTER,
      x: 0,
      y: 0,
    };
  })();

  let currentOrientation: OverlayOrientation = "landscape";
  let visible = false;

  // ----------------------------------------------------------------------------------
  // Layout — Dolphin's gcDefaultOverlay()/gcPortraitDefaultOverlay() resolved against the
  // live viewport rather than baked once into SharedPreferences.
  // ----------------------------------------------------------------------------------

  function layout(): void {
    // Measure the overlay's own box, not the window: index.html insets this element by the
    // safe-area env() values, so its box IS the region controls may occupy. originX/originY
    // convert between that box and the viewport space pointer events arrive in.
    const box = root.getBoundingClientRect();
    const originX = box.left;
    const originY = box.top;
    const vw = root.clientWidth || window.innerWidth;
    const vh = root.clientHeight || window.innerHeight;
    currentOrientation = orientationOf(vw, vh);

    for (const b of buttons) {
      const size = resolveSize(b.spec.scale, vw, vh, userScale);
      const pos = resolvePosition(
        currentOrientation === "portrait" ? b.spec.portrait : b.spec.landscape,
        vw,
        vh,
      );
      b.rect = { left: originX + pos.left, top: originY + pos.top, width: size, height: size };
      place(b.art.root, b.rect, originX, originY);
    }

    const dpadSize = resolveSize(GC_DPAD.scale, vw, vh, userScale);
    const dpadPos = resolvePosition(
      currentOrientation === "portrait" ? GC_DPAD.portrait : GC_DPAD.landscape,
      vw,
      vh,
    );
    dpad.rect = {
      left: originX + dpadPos.left,
      top: originY + dpadPos.top,
      width: dpadSize,
      height: dpadSize,
    };
    place(dpad.root, dpad.rect, originX, originY);

    const stickSize = resolveSize(GC_STICK.scale, vw, vh, userScale);
    const stickPos = resolvePosition(
      currentOrientation === "portrait" ? GC_STICK.portrait : GC_STICK.landscape,
      vw,
      vh,
    );
    stick.origRect = {
      left: originX + stickPos.left,
      top: originY + stickPos.top,
      width: stickSize,
      height: stickSize,
    };
    // A gesture in flight keeps its offset ring; otherwise snap back to the resting rect.
    if (stick.trackId === NO_POINTER) stick.virtRect = { ...stick.origRect };
    stick.innerSize = stickSize / GC_STICK.innerDivisor;
    place(stick.root, stick.origRect, originX, originY);
    stick.inner.style.width = `${stick.innerSize}px`;
    stick.inner.style.height = `${stick.innerSize}px`;
    updateStickVisual();
  }

  // ----------------------------------------------------------------------------------
  // Visual state
  // ----------------------------------------------------------------------------------

  function setButtonVisual(b: ButtonControl): void {
    b.art.pressed.style.opacity = b.isPressed ? "1" : "0";
    b.art.released.style.opacity = b.isPressed ? "0" : "1";
  }

  /**
   * Transcribed from InputOverlayDrawableDpad.draw(): one shared "one direction" bitmap
   * and one "two directions" bitmap, rotated in 90-degree steps about the control centre.
   * Dolphin does this with canvas.rotate(); a CSS rotate on the same art is equivalent.
   */
  function setDpadVisual(): void {
    const [up, down, left, right] = dpad.pressed;
    let art: HTMLImageElement | null = null;
    let rotation = 0;

    if (up && left) {
      art = dpad.twoWay;
      rotation = 0;
    } else if (up && right) {
      art = dpad.twoWay;
      rotation = 90;
    } else if (down && right) {
      art = dpad.twoWay;
      rotation = 180;
    } else if (down && left) {
      art = dpad.twoWay;
      rotation = 270;
    } else if (up) {
      art = dpad.oneWay;
      rotation = 0;
    } else if (right) {
      art = dpad.oneWay;
      rotation = 90;
    } else if (down) {
      art = dpad.oneWay;
      rotation = 180;
    } else if (left) {
      art = dpad.oneWay;
      rotation = 270;
    }

    dpad.released.style.opacity = art ? "0" : "1";
    dpad.oneWay.style.opacity = art === dpad.oneWay ? "1" : "0";
    dpad.twoWay.style.opacity = art === dpad.twoWay ? "1" : "0";
    if (art) art.style.transform = `rotate(${rotation}deg)`;
  }

  /** Transcribed from InputOverlayDrawableJoystick.setInnerBounds(). */
  function updateStickVisual(): void {
    const half = stick.innerSize / 2;
    // Knob centre = ring centre + normalised offset * half-extent, expressed relative to
    // the control's own box (which stays pinned at origRect even when virtRect is offset).
    const cx = stick.virtRect.left + stick.virtRect.width / 2 - stick.origRect.left;
    const cy = stick.virtRect.top + stick.virtRect.height / 2 - stick.origRect.top;
    const px = cx + stick.x * (stick.virtRect.width / 2);
    const py = cy + stick.y * (stick.virtRect.height / 2);
    stick.inner.style.left = `${px - half}px`;
    stick.inner.style.top = `${py - half}px`;

    const active = stick.trackId !== NO_POINTER;
    // Dolphin hides the resting ring and shows the bounds box while a gesture is live.
    stick.range.style.opacity = active ? "0" : "1";
    stick.outer.style.opacity = active ? "1" : "0";
    if (active) {
      stick.outer.style.inset = "auto";
      stick.outer.style.left = `${stick.virtRect.left - stick.origRect.left}px`;
      stick.outer.style.top = `${stick.virtRect.top - stick.origRect.top}px`;
      stick.outer.style.width = `${stick.virtRect.width}px`;
      stick.outer.style.height = `${stick.virtRect.height}px`;
    }
  }

  // ----------------------------------------------------------------------------------
  // Pointer dispatch — InputOverlay.onTouch(), pointer events instead of MotionEvent.
  // ----------------------------------------------------------------------------------

  function pressButton(b: ButtonControl, pointerId: number): void {
    b.isPressed = true;
    b.trackId = pointerId;
    setButtonVisual(b);
  }

  function releaseButton(b: ButtonControl): void {
    b.isPressed = false;
    b.trackId = NO_POINTER;
    setButtonVisual(b);
  }

  /** InputOverlay.onTouch()'s D-pad block: thirds of the bounds, two directions allowed. */
  function updateDpad(x: number, y: number): void {
    const r = dpad.rect;
    dpad.pressed = [
      r.top + r.height / 3 > y,
      r.top + r.height - r.height / 3 < y,
      r.left + r.width / 3 > x,
      r.left + r.width - r.width / 3 < x,
    ];
    setDpadVisual();
  }

  function releaseDpad(): void {
    dpad.pressed = [false, false, false, false];
    dpad.trackId = NO_POINTER;
    setDpadVisual();
  }

  /** InputOverlayDrawableJoystick.trackEvent()'s normalise + clamp step. */
  function updateStick(x: number, y: number): void {
    const cx = stick.virtRect.left + stick.virtRect.width / 2;
    const cy = stick.virtRect.top + stick.virtRect.height / 2;
    let nx = (x - cx) / (stick.virtRect.width / 2);
    let ny = (y - cy) / (stick.virtRect.height / 2);
    // See FIDELITY NOTES 1: unit-circle clamp stands in for the native octagonal gate.
    const radius = Math.hypot(nx, ny);
    if (radius > 1) {
      nx /= radius;
      ny /= radius;
    }
    stick.x = nx;
    stick.y = ny;
    updateStickVisual();
  }

  function releaseStick(): void {
    stick.trackId = NO_POINTER;
    stick.x = 0;
    stick.y = 0;
    stick.virtRect = { ...stick.origRect };
    stick.outer.style.opacity = "0";
    updateStickVisual();
  }

  function onPointerDown(ev: PointerEvent): void {
    if (!visible) return;
    const x = ev.clientX;
    const y = ev.clientY;
    let hit = false;

    for (const b of buttons) {
      if (b.trackId === NO_POINTER && rectContains(b.rect, x, y)) {
        pressButton(b, ev.pointerId);
        hit = true;
      }
    }

    if (!hit && dpad.trackId === NO_POINTER && rectContains(dpad.rect, x, y)) {
      dpad.trackId = ev.pointerId;
      updateDpad(x, y);
      hit = true;
    }

    if (!hit && stick.trackId === NO_POINTER && rectContains(stick.origRect, x, y)) {
      stick.trackId = ev.pointerId;
      if (relativeStickCenter) {
        // Dolphin offsets virtBounds so the ring centres on the finger for this gesture.
        stick.virtRect = {
          left: x - stick.origRect.width / 2,
          top: y - stick.origRect.height / 2,
          width: stick.origRect.width,
          height: stick.origRect.height,
        };
      }
      updateStick(x, y);
      hit = true;
    }

    // Only swallow the gesture when a control actually took it, so unrelated taps keep
    // reaching the page. preventDefault here is what stops scroll/zoom on the control.
    if (hit) ev.preventDefault();
  }

  function onPointerMove(ev: PointerEvent): void {
    if (!visible) return;
    if (dpad.trackId === ev.pointerId) {
      updateDpad(ev.clientX, ev.clientY);
      ev.preventDefault();
    }
    if (stick.trackId === ev.pointerId) {
      updateStick(ev.clientX, ev.clientY);
      ev.preventDefault();
    }
  }

  function onPointerUp(ev: PointerEvent): void {
    if (!visible) return;
    for (const b of buttons) {
      if (b.trackId === ev.pointerId) releaseButton(b);
    }
    if (dpad.trackId === ev.pointerId) releaseDpad();
    if (stick.trackId === ev.pointerId) releaseStick();
  }

  /** Release everything — used on hide, destroy, and visibility loss. */
  function releaseAll(): void {
    for (const b of buttons) releaseButton(b);
    releaseDpad();
    releaseStick();
  }

  // ----------------------------------------------------------------------------------
  // Synthetic Gamepad
  // ----------------------------------------------------------------------------------

  function getGamepad(): Gamepad | null {
    if (!visible) return null;

    const pressedIndices = new Set<number>();
    for (const b of buttons) {
      if (b.isPressed) for (const idx of b.spec.padButtons) pressedIndices.add(idx);
    }
    const [up, down, left, right] = dpad.pressed;
    if (up) for (const i of PAD_BUTTON.DPAD_UP) pressedIndices.add(i);
    if (down) for (const i of PAD_BUTTON.DPAD_DOWN) pressedIndices.add(i);
    if (left) for (const i of PAD_BUTTON.DPAD_LEFT) pressedIndices.add(i);
    if (right) for (const i of PAD_BUTTON.DPAD_RIGHT) pressedIndices.add(i);

    const padButtons: GamepadButton[] = [];
    for (let i = 0; i < PAD_BUTTON_COUNT; i += 1) {
      const pressed = pressedIndices.has(i);
      padButtons.push({ pressed, touched: pressed, value: pressed ? 1 : 0 });
    }

    // axes[0] = right-positive, axes[1] = down-positive: the standard-mapping convention
    // that adapter.ts already negates into its own +Z-forward sim axes.
    return {
      id: "GameCube touch overlay (standard)",
      index: -1,
      connected: true,
      mapping: "standard",
      timestamp: performance.now(),
      axes: [stick.x, stick.y, 0, 0],
      buttons: padButtons,
      vibrationActuator: null,
    } as unknown as Gamepad;
  }

  // ----------------------------------------------------------------------------------
  // Lifecycle
  // ----------------------------------------------------------------------------------

  function setVisible(next: boolean): void {
    if (next === visible) return;
    if (!next) releaseAll();
    visible = next;
    root.style.display = next ? "block" : "none";
    if (next) layout();
  }

  function onVisibilityChange(): void {
    // A backgrounded tab never delivers pointerup, which would strand a held button on.
    if (document.hidden) releaseAll();
  }

  root.style.display = "none";
  parent.appendChild(root);

  window.addEventListener("pointerdown", onPointerDown, { passive: false });
  window.addEventListener("pointermove", onPointerMove, { passive: false });
  window.addEventListener("pointerup", onPointerUp, { passive: true });
  window.addEventListener("pointercancel", onPointerUp, { passive: true });
  document.addEventListener("visibilitychange", onVisibilityChange);

  layout();

  return {
    get visible() {
      return visible;
    },
    get orientation() {
      return currentOrientation;
    },
    setVisible,
    getGamepad,
    layout,
    destroy(): void {
      releaseAll();
      window.removeEventListener("pointerdown", onPointerDown);
      window.removeEventListener("pointermove", onPointerMove);
      window.removeEventListener("pointerup", onPointerUp);
      window.removeEventListener("pointercancel", onPointerUp);
      document.removeEventListener("visibilitychange", onVisibilityChange);
      root.remove();
    },
  };
}
