export interface LoopHandle {
  stop(): void;
}

export interface Destroyable {
  destroy(): void;
}

export interface ScreenHost<THandle extends Destroyable = Destroyable> {
  readonly current: THandle | null;
  mount(build: (root: HTMLElement) => THandle): THandle;
  set(handle: THandle): void;
  clear(): void;
}

export function createScreenHost<THandle extends Destroyable = Destroyable>(root: HTMLElement): ScreenHost<THandle> {
  let current: THandle | null = null;
  return {
    get current() {
      return current;
    },
    mount(build) {
      this.clear();
      current = build(root);
      return current;
    },
    set(handle) {
      current?.destroy();
      current = handle;
    },
    clear() {
      current?.destroy();
      current = null;
      root.replaceChildren();
    },
  };
}

export interface FixedStepLoopOptions {
  step(dtSeconds: number): void;
  intervalMs?: number;
  now?: () => number;
  setInterval?: (handler: () => void, ms: number) => unknown;
  clearInterval?: (handle: unknown) => void;
}

export function startFixedStepLoop(options: FixedStepLoopOptions): LoopHandle {
  const intervalMs = options.intervalMs ?? 1000 / 60;
  const now = options.now ?? (() => performance.now());
  const schedule = options.setInterval ?? ((handler, ms) => globalThis.setInterval(handler, ms));
  const clear = options.clearInterval ?? ((handle) => globalThis.clearInterval(handle as ReturnType<typeof setInterval>));
  let last = now();
  const handle = schedule(() => {
    const current = now();
    const dt = (current - last) / 1000;
    last = current;
    options.step(dt);
  }, intervalMs);
  return {
    stop() {
      clear(handle);
    },
  };
}

export interface RenderLoopOptions {
  frame(): void;
  requestFrame?: (callback: FrameRequestCallback) => number;
  cancelFrame?: (handle: number) => void;
}

export function startRenderLoop(options: RenderLoopOptions): LoopHandle {
  const requestFrame = options.requestFrame ?? globalThis.requestAnimationFrame.bind(globalThis);
  const cancelFrame = options.cancelFrame ?? globalThis.cancelAnimationFrame.bind(globalThis);
  let active = true;
  let handle = 0;

  const tick: FrameRequestCallback = () => {
    if (!active) return;
    options.frame();
    handle = requestFrame(tick);
  };

  handle = requestFrame(tick);
  return {
    stop() {
      active = false;
      cancelFrame(handle);
    },
  };
}
