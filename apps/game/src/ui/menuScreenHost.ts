import { createScreenHost } from "@gf/core";
import { subscribeMenuInput, type MenuInputHandler, type MenuInputTarget } from "./menuInput.js";

export interface MenuScreenHandle extends MenuInputTarget {
  destroy(): void;
}

export interface MenuInputSource {
  subscribe(handler: MenuInputHandler): () => void;
}

export interface MenuScreenHost {
  readonly current: MenuScreenHandle | null;
  mount<THandle extends MenuScreenHandle>(build: (root: HTMLElement) => THandle): THandle;
  set(handle: MenuScreenHandle): void;
  clear(): void;
  mountOverlay<THandle extends MenuScreenHandle>(build: (root: HTMLElement) => THandle): THandle;
  closeOverlay(handle: MenuScreenHandle): void;
  destroy(): void;
}

interface ManagedHandle {
  readonly target: MenuScreenHandle;
  destroy(): void;
}

const browserMenuInput: MenuInputSource = { subscribe: subscribeMenuInput };

/**
 * Owns DOM screen lifetime and the single subscription to the shared menu-input bus.
 * Overlays are routed first without replacing the root's underlying HUD/content.
 */
export function createMenuScreenHost(
  root: HTMLElement,
  input: MenuInputSource = browserMenuInput,
): MenuScreenHost {
  const screens = createScreenHost<ManagedHandle>(root);
  const overlays: ManagedHandle[] = [];
  let destroyed = false;

  function manage(target: MenuScreenHandle): ManagedHandle {
    let released = false;
    return {
      target,
      destroy() {
        if (released) return;
        released = true;
        target.destroy();
      },
    };
  }

  function closeAllOverlays(): void {
    while (overlays.length > 0) overlays.pop()!.destroy();
  }

  const unsubscribe = input.subscribe((event) => {
    if (destroyed) return;
    const target = overlays[overlays.length - 1]?.target ?? screens.current?.target;
    target?.handleMenuInput(event);
  });

  return {
    get current() {
      return screens.current?.target ?? null;
    },
    mount<THandle extends MenuScreenHandle>(build: (root: HTMLElement) => THandle): THandle {
      if (destroyed) throw new Error("Cannot mount on a destroyed menu-screen host");
      closeAllOverlays();
      let target: THandle | null = null;
      screens.mount((container) => {
        target = build(container);
        return manage(target);
      });
      return target!;
    },
    set(handle) {
      if (destroyed) throw new Error("Cannot set a screen on a destroyed menu-screen host");
      closeAllOverlays();
      screens.set(manage(handle));
    },
    clear() {
      closeAllOverlays();
      screens.clear();
    },
    mountOverlay<THandle extends MenuScreenHandle>(build: (root: HTMLElement) => THandle): THandle {
      if (destroyed) throw new Error("Cannot mount an overlay on a destroyed menu-screen host");
      const target = build(root);
      const managed = manage(target);
      overlays.push(managed);
      return target;
    },
    closeOverlay(handle) {
      let index = overlays.length - 1;
      while (index >= 0 && overlays[index]?.target !== handle) index -= 1;
      if (index < 0) return;
      const [managed] = overlays.splice(index, 1);
      managed!.destroy();
    },
    destroy() {
      if (destroyed) return;
      destroyed = true;
      unsubscribe();
      closeAllOverlays();
      screens.clear();
    },
  };
}
