const FRAME_MS = 1000 / 60;
const BANNER_ENTER_FRAMES = 10;
const OPTION_ENTER_FRAMES = 15;
const SELECT_PULSE_FRAMES = 10;

export interface ChallengeMenuMotionItem {
  element: HTMLElement;
  delayFrames?: number;
  fromX?: number;
  fromY?: number;
}

export interface ChallengeMenuMotionHandle {
  isReady: () => boolean;
  pulseSelected: (element: HTMLElement | null) => void;
  finish: () => Promise<void>;
  destroy: () => void;
}

export function mountChallengeMenuMotion(
  root: HTMLElement,
  items: readonly ChallengeMenuMotionItem[],
): ChallengeMenuMotionHandle {
  const reducedMotion = window.matchMedia?.("(prefers-reduced-motion: reduce)")?.matches ?? false;
  let alive = true;
  let ready = reducedMotion;
  let raf = 0;
  let startTime = performance.now();
  let lastFrame = 0;
  let selected: HTMLElement | null = null;
  let pulseStartFrame = -SELECT_PULSE_FRAMES;
  let exiting = false;
  let exitStartTime = 0;
  let exitPromise: Promise<void> | null = null;
  let resolveExit: (() => void) | null = null;

  if (reducedMotion) {
    root.dataset["motionReady"] = "true";
    root.style.setProperty("--gf-title-offset-y", "0%");
    root.style.setProperty("--gf-title-scale", "1");
    root.style.setProperty("--gf-title-opacity", "1");
    root.style.setProperty("--gf-bg-scale", "1");
    for (const item of items) setItemProgress(item, 1);
    return {
      isReady: () => true,
      pulseSelected: () => undefined,
      finish: () => Promise.resolve(),
      destroy: () => undefined,
    };
  }

  function tick(now: number): void {
    if (!alive) return;
    lastFrame = frameAt(now);

    if (exiting) {
      updateExit(now);
      return;
    }

    const bannerT = clamp01(lastFrame / BANNER_ENTER_FRAMES);
    const bannerEase = easeOutCubic(bannerT);
    root.style.setProperty("--gf-title-offset-y", `${(-18 * (1 - bannerEase)).toFixed(3)}%`);
    root.style.setProperty("--gf-title-scale", (0.9 + 0.1 * bannerEase).toFixed(4));
    root.style.setProperty("--gf-title-opacity", bannerEase.toFixed(4));
    root.style.setProperty("--gf-bg-scale", (1.025 - 0.025 * bannerEase).toFixed(4));

    let allEntered = true;
    for (const item of items) {
      const t = clamp01((lastFrame - (item.delayFrames ?? 0)) / OPTION_ENTER_FRAMES);
      setItemProgress(item, easeOutCubic(t));
      if (t < 1) allEntered = false;
    }

    ready = allEntered;
    root.dataset["motionReady"] = String(ready);
    updatePulse();

    const pulseActive = lastFrame - pulseStartFrame < SELECT_PULSE_FRAMES;
    if (!ready || pulseActive) {
      raf = window.requestAnimationFrame(tick);
    } else {
      raf = 0;
    }
  }

  function updateExit(now: number): void {
    const exitFrame = Math.floor((now - exitStartTime) / FRAME_MS);
    const bannerT = clamp01(exitFrame / BANNER_ENTER_FRAMES);
    const optionT = clamp01(exitFrame / OPTION_ENTER_FRAMES);
    const bannerEase = easeInCubic(bannerT);
    const optionEase = easeInCubic(optionT);

    root.style.setProperty("--gf-title-offset-y", `${(-18 * bannerEase).toFixed(3)}%`);
    root.style.setProperty("--gf-title-scale", (1 - 0.1 * bannerEase).toFixed(4));
    root.style.setProperty("--gf-title-opacity", (1 - bannerEase).toFixed(4));
    root.style.setProperty("--gf-bg-scale", (1 + 0.025 * bannerEase).toFixed(4));

    for (const item of items) setItemProgress(item, 1 - optionEase);

    ready = false;
    root.dataset["motionReady"] = "false";

    if (optionT < 1) {
      raf = window.requestAnimationFrame(tick);
      return;
    }

    raf = 0;
    const done = resolveExit;
    resolveExit = null;
    exitPromise = null;
    done?.();
  }

  function updatePulse(): void {
    if (!selected) return;
    const pulseFrame = lastFrame - pulseStartFrame;
    if (pulseFrame < 0 || pulseFrame >= SELECT_PULSE_FRAMES) {
      selected.style.setProperty("--gf-select-scale", "1");
      selected.style.setProperty("--gf-ring-scale", "1");
      selected.style.setProperty("--gf-ring-opacity", "1");
      return;
    }
    const framesRemaining = SELECT_PULSE_FRAMES - pulseFrame;
    const flicker = (framesRemaining & 2) !== 0;
    const settle = 1 - pulseFrame / SELECT_PULSE_FRAMES;
    const scale = 1 + settle * (flicker ? 0.085 : 0.035);
    selected.style.setProperty("--gf-select-scale", scale.toFixed(4));
    selected.style.setProperty("--gf-ring-scale", (1 + settle * (flicker ? 0.11 : 0.03)).toFixed(4));
    selected.style.setProperty("--gf-ring-opacity", (0.86 + settle * (flicker ? 0.14 : 0.04)).toFixed(4));
  }

  function ensureLoop(): void {
    if (!raf && alive) raf = window.requestAnimationFrame(tick);
  }

  function frameAt(time: number): number {
    return Math.floor((time - startTime) / FRAME_MS);
  }

  startTime = performance.now();
  raf = window.requestAnimationFrame(tick);

  return {
    isReady: () => ready,
    pulseSelected: (element) => {
      if (selected && selected !== element) {
        selected.style.removeProperty("--gf-select-scale");
        selected.style.removeProperty("--gf-ring-scale");
        selected.style.removeProperty("--gf-ring-opacity");
      }
      selected = element;
      lastFrame = frameAt(performance.now());
      pulseStartFrame = lastFrame;
      updatePulse();
      ensureLoop();
    },
    finish: () => {
      if (!alive) return Promise.resolve();
      if (exiting) return exitPromise ?? Promise.resolve();
      exiting = true;
      ready = false;
      exitStartTime = performance.now();
      root.dataset["motionReady"] = "false";
      exitPromise = new Promise((resolve) => {
        resolveExit = resolve;
      });
      ensureLoop();
      return exitPromise;
    },
    destroy: () => {
      alive = false;
      if (raf) window.cancelAnimationFrame(raf);
      resolveExit?.();
      resolveExit = null;
      exitPromise = null;
    },
  };
}

function setItemProgress(item: ChallengeMenuMotionItem, easedT: number): void {
  const x = (item.fromX ?? 0) * (1 - easedT);
  const y = (item.fromY ?? 0) * (1 - easedT);
  item.element.style.setProperty("--gf-enter-offset-x", `${x.toFixed(3)}%`);
  item.element.style.setProperty("--gf-enter-offset-y", `${y.toFixed(3)}%`);
  item.element.style.setProperty("--gf-enter-opacity", easedT.toFixed(4));
}

function clamp01(value: number): number {
  if (value <= 0) return 0;
  if (value >= 1) return 1;
  return value;
}

function easeOutCubic(t: number): number {
  return 1 - (1 - t) ** 3;
}

function easeInCubic(t: number): number {
  return t ** 3;
}
