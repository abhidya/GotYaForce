// =============================================================================
// worker.ts — worker side of the composed-module execution runtime.
//
// The WORKER owns the composed module and its shared WebAssembly.Memory
// (design V4 H2 / step 9): it reads the module's declared env.memory limits
// straight out of the binary import section (the same flag-free technique as
// research/decomp/oracle-harness/lib/wasm.mjs importedMemoryLimits), creates
// the shared memory, instantiates, installs the arena bytes at original GC
// addresses, then enters a BLOCKING dispatch loop on the control block.
//
// This is I2's reentrant dispatch loop, worker half:
//   - The bridge stub (__gf_dispatch_miss — H3: a table miss IS a bridge
//     call) publishes CALL and Atomics.wait's, distinguishing two wake kinds:
//     CALL_DONE (its result) and INVOKE (the main-thread servicer needs a
//     linked export run — executed HERE, on the worker's own stack, then the
//     stub re-waits for its original result).
//   - Between driven frames the worker parks (PARKED) and services INVOKE
//     requests — the delivery point for start/step controls and GC interrupt
//     callbacks (R3: invoke-requests at worker park points).
//
// Once parked, the worker's event loop is intentionally blocked: it can never
// receive another postMessage. ALL post-ready main->worker traffic travels
// through the SharedArrayBuffer (protocol.ts), including shutdown.
// =============================================================================

import {
  BridgeCallError,
  BridgeState,
  BridgeStatus,
  Ctrl,
  INVOKE_MAX_ARGS,
  type WorkerInitMessage,
  type WorkerReadyMessage,
} from "./protocol.js";

interface MemoryLimits {
  initial: number;
  maximum: number | undefined;
  shared: boolean;
}

/**
 * Read the module's imported env.memory limits from the binary import
 * section (wasm core spec §5.5.5/§5.5.7: section id 2; limits flags bit 0x1 =
 * has-max, bit 0x2 = shared). Port of the harness's importedMemoryLimits
 * (research/decomp/oracle-harness/lib/wasm.mjs) — kept dependency-free so the
 * worker bundle stays self-contained.
 */
export function importedMemoryLimits(wasmBytes: ArrayBuffer): MemoryLimits | null {
  const u8 = new Uint8Array(wasmBytes);
  let p = 8; // magic + version
  const leb = (): number => {
    let r = 0;
    let s = 0;
    let b: number;
    do {
      b = u8[p++] ?? 0;
      r |= (b & 0x7f) << s;
      s += 7;
    } while (b & 0x80);
    return r >>> 0;
  };
  const name = (): string => {
    const n = leb();
    const v = new TextDecoder().decode(u8.subarray(p, p + n));
    p += n;
    return v;
  };
  const limits = (): MemoryLimits => {
    const flags = leb();
    const initial = leb();
    const maximum = flags & 0x1 ? leb() : undefined;
    return { initial, maximum, shared: (flags & 0x2) !== 0 };
  };
  while (p < u8.length) {
    const id = u8[p++] ?? 0;
    const size = leb();
    const end = p + size;
    if (id !== 2) {
      p = end;
      continue;
    }
    const count = leb();
    for (let i = 0; i < count; i++) {
      const mod = name();
      const field = name();
      const kind = u8[p++] ?? 0;
      if (kind === 0x00) leb();
      else if (kind === 0x01) {
        p++;
        limits();
      } else if (kind === 0x02) {
        const lim = limits();
        if (mod === "env" && field === "memory") return lim;
      } else if (kind === 0x03) p += 2;
      else throw new Error(`unknown import kind 0x${kind.toString(16)} in wasm import section`);
    }
    return null; // a module has at most one import section
  }
  return null;
}

type WasmFunction = (...args: number[]) => number | void;

class WorkerRuntime {
  #i32: Int32Array;
  #exports: WasmFunction[] = [];
  #exportNames: string[] = [];

  constructor(ctrl: SharedArrayBuffer) {
    this.#i32 = new Int32Array(ctrl);
  }

  /**
   * H2 steps 1-3, worker half, with I2's two wake kinds. Called synchronously
   * from inside running wasm (the __gf_dispatch_miss import). Returns the
   * bridged call's i32 result (frame-derived host-side); throws
   * BridgeCallError on any declared servicing error, failing the frame
   * LOUDLY (the error is already in the ledger by the time this throws).
   */
  bridgeCall = (gcAddr: number, argptr: number): number => {
    const i32 = this.#i32;
    const prior = Atomics.load(i32, Ctrl.STATE);
    Atomics.add(i32, Ctrl.SEQ, 1);
    Atomics.store(i32, Ctrl.CALL_GC_ADDR, gcAddr | 0);
    Atomics.store(i32, Ctrl.CALL_ARGPTR, argptr | 0);
    Atomics.store(i32, Ctrl.STATE, BridgeState.CALL);
    Atomics.notify(i32, Ctrl.STATE);
    for (;;) {
      const state = Atomics.load(i32, Ctrl.STATE);
      if (state === BridgeState.CALL_DONE) {
        // Result-wake: consume, restore the pre-call state (rendezvous stack
        // discipline), hand the result (or the declared error) to wasm.
        const status = Atomics.load(i32, Ctrl.CALL_STATUS);
        const result = Atomics.load(i32, Ctrl.CALL_RESULT);
        Atomics.store(i32, Ctrl.STATE, prior);
        Atomics.notify(i32, Ctrl.STATE);
        if (status !== BridgeStatus.OK) {
          throw new BridgeCallError(
            status,
            `bridged call 0x${(gcAddr >>> 0).toString(16).padStart(8, "0")} failed with status ${status}`,
          );
        }
        return result;
      }
      if (state === BridgeState.INVOKE) {
        // Invoke-wake: the main-thread servicer needs a linked export run.
        // Execute it on THIS stack (reentrant dispatch loop), then keep
        // waiting for the original result.
        this.#runInvoke();
        continue;
      }
      // Still pending (CALL), or a transient another party will consume
      // (INVOKE_DONE awaiting main). Block until the state moves.
      Atomics.wait(i32, Ctrl.STATE, state);
    }
  };

  /** Run the published invoke request on the current stack and publish
   *  INVOKE_DONE. Never throws: failures become INV_STATUS codes. */
  #runInvoke(): void {
    const i32 = this.#i32;
    const fnIndex = Atomics.load(i32, Ctrl.INV_FN);
    const argc = Math.min(Atomics.load(i32, Ctrl.INV_ARGC), INVOKE_MAX_ARGS);
    const args: number[] = [];
    for (let i = 0; i < argc; i++) args.push(Atomics.load(i32, Ctrl.INV_ARGS + i));
    let status: number = BridgeStatus.OK;
    let result = 0;
    const fn = this.#exports[fnIndex];
    if (!fn) {
      status = BridgeStatus.UNKNOWN_EXPORT;
    } else {
      try {
        result = (fn(...args) ?? 0) | 0;
      } catch (error) {
        // A BridgeCallError carries the original declared servicing error
        // (e.g. NESTING_OVERFLOW from a deeper bridged call) — propagate its
        // code so the failure surfaces at the invoke originator unrelabeled.
        status = error instanceof BridgeCallError ? error.status : BridgeStatus.EXPORT_THREW;
      }
    }
    Atomics.store(i32, Ctrl.INV_RESULT, result);
    Atomics.store(i32, Ctrl.INV_STATUS, status);
    Atomics.store(i32, Ctrl.STATE, BridgeState.INVOKE_DONE);
    Atomics.notify(i32, Ctrl.STATE);
  }

  setExports(names: string[], fns: WasmFunction[]): void {
    this.#exportNames = names;
    this.#exports = fns;
  }

  get exportNames(): string[] {
    return this.#exportNames;
  }

  /**
   * The park loop — the worker's steady state (R3: GC interrupt callbacks and
   * start/step controls are delivered as invoke-requests at park points).
   * Blocks this worker's event loop FOREVER (until SHUTDOWN through the SAB).
   */
  parkLoop(): void {
    const i32 = this.#i32;
    Atomics.store(i32, Ctrl.STATE, BridgeState.PARKED);
    Atomics.notify(i32, Ctrl.STATE);
    for (;;) {
      const state = Atomics.load(i32, Ctrl.STATE);
      if (state === BridgeState.SHUTDOWN) {
        Atomics.store(i32, Ctrl.STATE, BridgeState.IDLE);
        Atomics.notify(i32, Ctrl.STATE);
        return;
      }
      if (state === BridgeState.INVOKE) {
        this.#runInvoke();
        continue;
      }
      // PARKED (waiting for work) or INVOKE_DONE (main is consuming; it will
      // restore PARKED). Block until the state moves.
      Atomics.wait(i32, Ctrl.STATE, state);
    }
  }
}

/**
 * Install the runtime on a dedicated worker scope: handles the single init
 * message, instantiates the threads-target module with a worker-owned shared
 * memory, installs the arena, replies ready, and parks.
 */
export function installRomRuntimeWorker(scope: DedicatedWorkerGlobalScope): void {
  scope.addEventListener("message", (event: MessageEvent) => {
    const message = event.data as WorkerInitMessage;
    if (message?.type !== "init") return;
    void bootWorker(scope, message);
  });
}

async function bootWorker(scope: DedicatedWorkerGlobalScope, init: WorkerInitMessage): Promise<void> {
  try {
    const runtime = new WorkerRuntime(init.ctrl);

    const limits = importedMemoryLimits(init.wasmBytes);
    if (!limits) {
      throw new Error("module does not import env.memory — the composed runtime requires a threads-target (shared imported memory) build");
    }
    if (!limits.shared) {
      throw new Error("module's env.memory import is not shared — rebuild with -sSHARED_MEMORY=1 -sIMPORTED_MEMORY=1");
    }
    const memory = new WebAssembly.Memory({
      initial: limits.initial,
      // Shared memories require a maximum; the composed arena is fixed-size.
      maximum: limits.maximum ?? limits.initial,
      shared: true,
    });

    const module = await WebAssembly.compile(init.wasmBytes);
    const shims: Record<string, unknown> = {
      memory,
      // H3: a table miss is a bridge call, never a trap — bound straight to
      // the Atomics RPC bridge.
      __gf_dispatch_miss: runtime.bridgeCall,
    };
    const instance = await WebAssembly.instantiate(module, {
      env: new Proxy(shims, {
        get: (t, k) =>
          t[k as string] ??
          (() => {
            // Loud by design: an import that is neither the memory nor the
            // declared bridge hook is a composition error, not a silent no-op.
            throw new Error(`rom-runtime worker: unshimmed import env.${String(k)}`);
          }),
      }) as WebAssembly.ModuleImports,
    });

    // Reactor-model ctors (emscripten --no-entry exports _initialize): run
    // once, before the arena lands and before any invoke.
    const initialize = instance.exports["_initialize"];
    if (typeof initialize === "function") (initialize as () => void)();

    // Arena at original GC addresses, exactly like the harness/seam path.
    const u8 = new Uint8Array(memory.buffer as unknown as ArrayBuffer);
    for (const segment of init.arena) {
      u8.set(segment.bytes, segment.addr >>> 0);
    }

    const names: string[] = [];
    const fns: WasmFunction[] = [];
    for (const [name, value] of Object.entries(instance.exports)) {
      if (typeof value === "function") {
        names.push(name);
        fns.push(value as WasmFunction);
      }
    }
    runtime.setExports(names, fns);

    const ready: WorkerReadyMessage = { type: "ready", exports: names, memory };
    scope.postMessage(ready);

    // From here the event loop is gone: the park loop owns the thread.
    runtime.parkLoop();
    scope.close();
  } catch (error) {
    scope.postMessage({ type: "fatal", error: error instanceof Error ? `${error.message}` : String(error) });
  }
}
