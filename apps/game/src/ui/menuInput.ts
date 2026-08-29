/**
 * menuInput — a single shared menu-input bus for all non-battle screens.
 *
 * PROBLEM this replaces: every screen (SelectDifficulty, SelectPlayers, LoadBoxData,
 * SelectForce, ForceBuilder, BattleIntro, Results, PauseMenu, MainMenu, TitleIntro)
 * registered its OWN `window.addEventListener("keydown", ...)` with slightly different
 * key sets (some accept Space for confirm, some don't; some accept "s"/"b" letter
 * mnemonics, some don't), and NONE of them read the gamepad — gamepad input only ever
 * worked inside battle (see main.ts inputFromKeys/activeGamepad). A controller-only
 * player could not navigate a single menu screen.
 *
 * FIX: one keydown listener + one polled-gamepad loop translate raw input into a small
 * set of semantic MenuAction values. The app's menu-screen host owns the one gameplay
 * subscription and routes actions to its current screen or top overlay. Screens expose
 * behavior on their handles and know nothing about subscription lifetime. The bus keeps
 * LIFO subscription semantics for isolated consumers/debug tools, but normal gameplay
 * needs only the host subscriber.
 *
 * Gamepad polling: setInterval, NOT requestAnimationFrame. rAF is throttled/paused in
 * background tabs, which silently killed menu gamepad input in testing (a backgrounded
 * tab that regains focus would otherwise "lose" buffered presses, or simply never see
 * them at all while hidden). A plain wall-clock interval keeps polling regardless of
 * tab visibility, matching the sim's own startFixedStepLoop rationale in main.ts.
 */

import { touchGamepad } from "./touch/index.js";

export type MenuAction =
  | "up"
  | "down"
  | "left"
  | "right"
  | "confirm"
  | "back"
  | "edit"
  | "switch"
  | "start";

/** Optional metadata carried alongside some actions. */
export interface MenuActionEvent {
  action: MenuAction;
  /**
   * For "switch" (L/R cycling): -1 = L / previous, 1 = R / next. Screens that only
   * care about "some switch happened" (rare) can ignore this field.
   */
  dir?: -1 | 1;
  /** Input source, for debugging/selfcheck only. */
  source: "keyboard" | "gamepad";
}

export type MenuInputHandler = (event: MenuActionEvent) => void;

/** A mounted menu screen that can receive semantic input from the menu-screen host. */
export interface MenuInputTarget {
  handleMenuInput(event: MenuActionEvent): void;
}

const GAMEPAD_POLL_MS = 16; // ~60Hz; see module doc for why this is setInterval, not rAF.
const STICK_THRESHOLD = 0.5;
const STICK_REPEAT_MS = 220; // suppress repeat-fire while a stick stays pushed past threshold.

// LIFO subscriber stack: only the top entry receives dispatched actions. Normal gameplay
// has one long-lived menu-screen-host subscriber.
const subscribers: MenuInputHandler[] = [];

let gamepadPollHandle: ReturnType<typeof setInterval> | null = null;
let keydownHandler: ((ev: KeyboardEvent) => void) | null = null;

// Gamepad edge-detection state, keyed by pad index. Standard mapping:
//   button0 = confirm (A), button1 = back (B), button2 = edit (X), button9 = start
//   dpad: button12=up, 13=down, 14=left, 15=right
//   left stick: axes[0]/[1], threshold 0.5, with repeat suppression (not per-frame edge)
interface PadEdgeState {
  buttonsPressed: boolean[];
  stickX: 0 | -1 | 1;
  stickY: 0 | -1 | 1;
  lastStickFireAt: number;
}
// Keyed by a STABLE identity, not by array position: the touch overlay is appended after
// the physical pads, so its index shifts when a controller is plugged in. Reusing a
// position-keyed entry across two different pads would carry stale button-edge state and
// swallow the first press after the shift.
type PadKey = number | "touch";
const padStates = new Map<PadKey, PadEdgeState>();

function isTextInputTarget(target: EventTarget | null): boolean {
  return (
    target instanceof HTMLInputElement ||
    target instanceof HTMLSelectElement ||
    target instanceof HTMLTextAreaElement
  );
}

function dispatch(action: MenuAction, source: "keyboard" | "gamepad", dir?: -1 | 1): void {
  const top = subscribers[subscribers.length - 1];
  if (!top) return;
  // exactOptionalPropertyTypes: only include `dir` when a caller actually passed one,
  // rather than assigning `dir: undefined` (which the type explicitly disallows).
  top(dir === undefined ? { action, source } : { action, source, dir });
}

function keyToAction(ev: KeyboardEvent): { action: MenuAction; dir?: -1 | 1 } | null {
  switch (ev.code) {
    case "ArrowUp":
      return { action: "up" };
    case "ArrowDown":
      return { action: "down" };
    case "ArrowLeft":
      return { action: "left" };
    case "ArrowRight":
      return { action: "right" };
    case "Enter":
    case "Space":
    case "KeyA":
      return { action: "confirm" };
    case "Escape":
    case "KeyB":
      return { action: "back" };
    case "KeyX":
      return { action: "edit" };
    case "KeyQ":
    case "BracketLeft":
      return { action: "switch", dir: -1 };
    case "KeyE":
    case "BracketRight":
      return { action: "switch", dir: 1 };
    case "KeyP":
      return { action: "start" };
    default:
      return null;
  }
}

function onWindowKeydown(ev: KeyboardEvent): void {
  if (isTextInputTarget(ev.target)) return;
  const mapped = keyToAction(ev);
  if (!mapped) return;
  dispatch(mapped.action, "keyboard", mapped.dir);
  ev.preventDefault();
}

function padEdgeStateFor(key: PadKey): PadEdgeState {
  let state = padStates.get(key);
  if (!state) {
    state = { buttonsPressed: [], stickX: 0, stickY: 0, lastStickFireAt: 0 };
    padStates.set(key, state);
  }
  return state;
}

function pollGamepads(): void {
  if (subscribers.length === 0) return; // no screen listening; skip the work
  // The on-screen GameCube overlay (ui/touch) publishes a synthetic standard-mapping pad
  // so menus work under touch with no second code path. It is appended rather than
  // substituted, so a physical pad and the overlay can both be live on a tablet.
  const physical = navigator.getGamepads?.() ?? [];
  const touch = touchGamepad();
  const pads: (Gamepad | null)[] = touch ? [...physical, touch] : [...physical];
  if (!touch) padStates.delete("touch"); // overlay hidden: drop its edge state
  if (pads.length === 0) return;
  const now = performance.now();
  const touchIndex = touch ? pads.length - 1 : -1;
  for (let i = 0; i < pads.length; i += 1) {
    const pad = pads[i];
    const key: PadKey = i === touchIndex ? "touch" : i;
    if (!pad?.connected) {
      padStates.delete(key);
      continue;
    }
    const state = padEdgeStateFor(key);

    // Face/shoulder buttons: fire once per press (rising edge).
    const wasPressed = (idx: number) => state.buttonsPressed[idx] ?? false;
    const isPressed = (idx: number) => pad.buttons[idx]?.pressed ?? false;
    const fireOnPress = (idx: number, action: MenuAction, dir?: -1 | 1): void => {
      const now_ = isPressed(idx);
      if (now_ && !wasPressed(idx)) dispatch(action, "gamepad", dir);
      state.buttonsPressed[idx] = now_;
    };

    fireOnPress(0, "confirm");
    fireOnPress(1, "back");
    fireOnPress(2, "edit");
    fireOnPress(9, "start");
    fireOnPress(12, "up");
    fireOnPress(13, "down");
    fireOnPress(14, "left", -1);
    fireOnPress(15, "right", 1);
    // Shoulder buttons double as "switch" (L/R force cycling), matching main.ts's
    // switchLock/switchLockPrev shoulder mapping.
    fireOnPress(4, "switch", -1);
    fireOnPress(5, "switch", 1);

    // Left stick: threshold + repeat suppression rather than per-frame edge, so
    // holding the stick over doesn't spam actions every 16ms poll.
    const ax = pad.axes[0] ?? 0;
    const ay = pad.axes[1] ?? 0;
    const nextStickX: 0 | -1 | 1 = ax <= -STICK_THRESHOLD ? -1 : ax >= STICK_THRESHOLD ? 1 : 0;
    const nextStickY: 0 | -1 | 1 = ay <= -STICK_THRESHOLD ? -1 : ay >= STICK_THRESHOLD ? 1 : 0;

    if (nextStickX !== 0 && (nextStickX !== state.stickX || now - state.lastStickFireAt >= STICK_REPEAT_MS)) {
      dispatch(nextStickX < 0 ? "left" : "right", "gamepad");
      state.lastStickFireAt = now;
    }
    if (nextStickY !== 0 && (nextStickY !== state.stickY || now - state.lastStickFireAt >= STICK_REPEAT_MS)) {
      dispatch(nextStickY < 0 ? "up" : "down", "gamepad");
      state.lastStickFireAt = now;
    }
    state.stickX = nextStickX;
    state.stickY = nextStickY;
  }
}

function ensureBusStarted(): void {
  if (!keydownHandler) {
    keydownHandler = onWindowKeydown;
    window.addEventListener("keydown", keydownHandler);
  }
  if (!gamepadPollHandle) {
    gamepadPollHandle = setInterval(pollGamepads, GAMEPAD_POLL_MS);
  }
}

/**
 * Subscribe to the shared menu-input bus. The MOST RECENTLY subscribed handler is the
 * only one that receives actions (LIFO). Returns an idempotent unsubscribe function.
 * The menu-screen host owns the gameplay subscription; screen modules must not call this.
 */
export function subscribeMenuInput(handler: MenuInputHandler): () => void {
  ensureBusStarted();
  subscribers.push(handler);
  let unsubscribed = false;
  return () => {
    if (unsubscribed) return;
    unsubscribed = true;
    const idx = subscribers.lastIndexOf(handler);
    if (idx >= 0) subscribers.splice(idx, 1);
  };
}
