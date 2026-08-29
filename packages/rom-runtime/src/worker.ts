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
  type BridgedImportBinding,
  type MemoryLimits,
  WasmType,
  planBridgedImports,
  readModuleShape,
  wasmTypeName,
} from "./composed.js";
import {
  FRAME_ARGS_OFFSET,
  FRAME_ARG_COUNT_OFFSET,
  FRAME_RET_CLASS_OFFSET,
  FRAME_RET_OFFSET,
  FRAME_SIZE,
  FRAME_SLOT_SIZE,
} from "./frame.js";
import {
  BridgeCallError,
  BridgeState,
  BridgeStatus,
  Ctrl,
  INVOKE_MAX_ARGS,
  type WorkerInitMessage,
  type WorkerReadyMessage,
} from "./protocol.js";

/**
 * Read the module's imported env.memory limits from the binary import
 * section (wasm core spec §5.5.5/§5.5.7: section id 2; limits flags bit 0x1 =
 * has-max, bit 0x2 = shared). Port of the harness's importedMemoryLimits
 * (research/decomp/oracle-harness/lib/wasm.mjs) — kept dependency-free so the
 * worker bundle stays self-contained.
 */
export function importedMemoryLimits(wasmBytes: ArrayBuffer): MemoryLimits | null {
  return readModuleShape(wasmBytes).memory;
}

type WasmFunction = (...args: number[]) => number | void;

/**
 * Per-import bridge trampolines (composed.ts, H2 direct-call edge).
 *
 * Each trampoline has the import's TRUE wasm signature. It claims a dispatch
 * frame from a small depth-indexed region of the shared linear memory, writes
 * the caller's arguments into the frame's 8-byte slots in parameter order,
 * calls the SAME bridge stub the miss import uses, then reads the return out
 * of the frame's authoritative ret slot at its declared wasm type and hands
 * it back to wasm.
 *
 * NOTE the deliberate difference from the bridge's i32 wire result: here the
 * wasm result type is KNOWN, so an i64 return is read as a full i64 from the
 * ret slot rather than through frame.retPpcR3View()'s r3 word. The r3 view
 * exists for the uniform-ABI thunk path, where the true width is not known
 * at the call site; it must not be applied to a typed direct call.
 *
 * Frames nest: while a bridged call is parked, the worker may run an INVOKE
 * that calls another out-of-window symbol. `depth` gives each nesting level
 * its own frame; exhausting the region is a loud error, never reuse.
 */
function makeBridgeTrampolines(
  bindings: BridgedImportBinding[],
  memory: WebAssembly.Memory,
  bridgeCall: (gcAddr: number, argptr: number) => number,
  frameBase: number,
  frameSlots: number,
): Record<string, (...args: unknown[]) => unknown> {
  const dv = new DataView(memory.buffer as ArrayBuffer);
  let depth = 0;
  const shims: Record<string, (...args: unknown[]) => unknown> = {};
  for (const binding of bindings) {
    const { gcAddr, symbol, params, results } = binding;
    const resultType = results[0];
    shims[symbol] = (...args: unknown[]): unknown => {
      if (depth >= frameSlots) {
        throw new BridgeCallError(
          BridgeStatus.NESTING_OVERFLOW,
          `bridged import ${symbol}: trampoline frame region exhausted at depth ${depth} (${frameSlots} slots)`,
        );
      }
      const fp = frameBase + depth * FRAME_SIZE;
      depth += 1;
      try {
        dv.setUint32(fp + FRAME_ARG_COUNT_OFFSET, params.length, true);
        dv.setUint32(fp + FRAME_RET_CLASS_OFFSET, 0, true);
        dv.setBigUint64(fp + FRAME_RET_OFFSET, 0n, true);
        for (let i = 0; i < params.length; i++) {
          const at = fp + FRAME_ARGS_OFFSET + i * FRAME_SLOT_SIZE;
          dv.setBigUint64(at, 0n, true);
          switch (params[i]) {
            case WasmType.I32:
              dv.setInt32(at, (args[i] as number) | 0, true);
              break;
            case WasmType.I64:
              dv.setBigInt64(at, (args[i] as bigint) ?? 0n, true);
              break;
            case WasmType.F32:
              dv.setFloat32(at, (args[i] as number) ?? 0, true);
              break;
            case WasmType.F64:
              dv.setFloat64(at, (args[i] as number) ?? 0, true);
              break;
            default:
              throw new Error(`bridged import ${symbol}: unsupported param type ${wasmTypeName(params[i] ?? -1)}`);
          }
        }
        bridgeCall(gcAddr, fp);
        switch (resultType) {
          case undefined:
            return undefined;
          case WasmType.I32:
            return dv.getInt32(fp + FRAME_RET_OFFSET, true);
          case WasmType.I64:
            return dv.getBigInt64(fp + FRAME_RET_OFFSET, true);
          case WasmType.F32:
            return dv.getFloat32(fp + FRAME_RET_OFFSET, true);
          case WasmType.F64:
            return dv.getFloat64(fp + FRAME_RET_OFFSET, true);
          default:
            throw new Error(`bridged import ${symbol}: unsupported result type ${wasmTypeName(resultType)}`);
        }
      } finally {
        depth -= 1;
      }
    };
  }
  return shims;
}

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

    const shape = readModuleShape(init.wasmBytes);
    const limits = shape.memory;
    if (!limits) {
      throw new Error("module does not import env.memory — the composed runtime requires a threads-target (shared imported memory) build");
    }
    if (!limits.shared) {
      throw new Error("module's env.memory import is not shared — rebuild with -sSHARED_MEMORY=1 -sIMPORTED_MEMORY=1");
    }
    // The composed module's memory is the gate's fixed ~2GB flat arena. Time
    // it separately: it dominates boot, and a host that cannot afford it must
    // fail here with a clear cost attached, not somewhere downstream.
    const tMemory = performance.now();
    const memory = new WebAssembly.Memory({
      initial: limits.initial,
      // Shared memories require a maximum; the composed arena is fixed-size.
      maximum: limits.maximum ?? limits.initial,
      shared: true,
    });
    const tCompile = performance.now();

    const module = await WebAssembly.compile(init.wasmBytes);
    const tInstantiate = performance.now();
    const shims: Record<string, unknown> = {
      memory,
      // H3: a table miss is a bridge call, never a trap — bound straight to
      // the Atomics RPC bridge.
      __gf_dispatch_miss: runtime.bridgeCall,
    };

    // H2 direct-call edge (opt-in): bind every OTHER imported function to the
    // same bridge through a signature-accurate trampoline, so a linked
    // function calling an unlinked callee by name crosses the declared bridge
    // instead of hitting the unshimmed-import error below.
    let bridgedImports: WorkerReadyMessage["bridgedImports"] = [];
    if (init.bridgeAllImports) {
      const frameBase = init.trampolineFrameBase;
      const frameSlots = init.trampolineFrameSlots ?? 0;
      if (frameBase === undefined || frameSlots <= 0) {
        throw new Error("bridgeAllImports requires trampolineFrameBase and a positive trampolineFrameSlots");
      }
      const memoryBytes = limits.initial * 65536;
      if (frameBase < 0 || frameBase + frameSlots * FRAME_SIZE > memoryBytes) {
        throw new Error(
          `trampoline frame region 0x${frameBase.toString(16)}+${frameSlots * FRAME_SIZE} lies outside the module's ${memoryBytes}-byte memory`,
        );
      }
      const bindings = planBridgedImports(shape);
      Object.assign(shims, makeBridgeTrampolines(bindings, memory, runtime.bridgeCall, frameBase, frameSlots));
      bridgedImports = bindings.map((b) => ({
        symbol: b.symbol,
        gcAddr: b.gcAddr,
        source: b.source,
        signature: `(${b.params.map(wasmTypeName).join(",")}) -> ${b.results.map(wasmTypeName).join(",") || "void"}`,
      }));
    }
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

    const tArena = performance.now();

    // Reactor-model ctors (emscripten --no-entry exports _initialize): run
    // once, before the arena lands and before any invoke.
    const initialize = instance.exports["_initialize"];
    if (typeof initialize === "function") (initialize as () => void)();

    // Arena at original GC addresses, exactly like the harness/seam path.
    const u8 = new Uint8Array(memory.buffer as unknown as ArrayBuffer);
    for (const segment of init.arena) {
      u8.set(segment.bytes, segment.addr >>> 0);
    }
    const tDone = performance.now();

    const names: string[] = [];
    const fns: WasmFunction[] = [];
    for (const [name, value] of Object.entries(instance.exports)) {
      if (typeof value === "function") {
        names.push(name);
        fns.push(value as WasmFunction);
      }
    }
    runtime.setExports(names, fns);

    const ready: WorkerReadyMessage = {
      type: "ready",
      exports: names,
      memory,
      bridgedImports,
      timings: {
        memoryMs: Math.round(tCompile - tMemory),
        compileMs: Math.round(tInstantiate - tCompile),
        instantiateMs: Math.round(tArena - tInstantiate),
        arenaMs: Math.round(tDone - tArena),
      },
    };
    scope.postMessage(ready);

    // From here the event loop is gone: the park loop owns the thread.
    runtime.parkLoop();
    scope.close();
  } catch (error) {
    scope.postMessage({ type: "fatal", error: error instanceof Error ? `${error.message}` : String(error) });
  }
}
