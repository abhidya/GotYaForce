// =============================================================================
// host.ts — main-thread side of the composed-module execution runtime.
//
// Owns: the control-block SharedArrayBuffer, the adapter registry, the
// bridged-call ledger, and the servicing pump. The worker owns the module and
// the shared memory (worker.ts); the two meet only through the protocol.ts
// channel.
//
// Main-thread wait discipline (V5 R3, normative): this thread NEVER calls
// Atomics.wait. Top-level waits (invoke delivery, waiting for the park state)
// use Atomics.waitAsync with a setTimeout polling fallback; NESTED waits —
// required while a synchronous adapter is mid-service and cannot yield to the
// event loop — use a bounded busy-wait on Atomics.load. Exceeding the bound
// is the declared servicing error WORKER_STALL, surfaced in the ledger.
//
// Invoke discipline (I2 + V5 verdict): the main thread never calls worker
// exports directly — it publishes invoke-requests that the parked worker runs
// on its own stack. Only a servicing main thread issues NESTED invokes (which
// implies a parked worker); top-level invokes/events queue until the worker
// parks (late invokes queue to the next park).
// =============================================================================

import type { BridgedCallContext, BridgedCalleeAdapter } from "./adapters.js";
import { AdapterRegistry } from "./adapters.js";
import { DispatchFrame, FrameValueClass } from "./frame.js";
import { BridgeLedger } from "./ledger.js";
import { GcMemory, type GcMemoryOptions } from "./memory.js";
import {
  BRIDGE_STATUS_NAMES,
  BridgeCallError,
  BridgeState,
  BridgeStatus,
  CTRL_BYTE_LENGTH,
  Ctrl,
  DEFAULT_BUSY_WAIT_TIMEOUT_MS,
  DEFAULT_NESTING_CAP,
  INVOKE_MAX_ARGS,
  type WorkerInitMessage,
  type WorkerMessage,
} from "./protocol.js";

export interface RomRuntimeHostOptions {
  /** Bound on nested bridged-servicing depth (I2 stated maximum). */
  nestingCap?: number;
  /** Bound (ms) on synchronous busy-waits for worker responses. */
  busyWaitTimeoutMs?: number;
  /** Arena segments the worker installs at GC addresses before ready. */
  arena?: Array<{ addr: number; bytes: Uint8Array }>;
  /** GcMemory options (seam accessor bases; test affordance). */
  memory?: GcMemoryOptions;
}

interface InvokeJob {
  exportName: string;
  args: number[];
  resolve: (value: number) => void;
  reject: (error: Error) => void;
}

const statusName = (code: number): string => BRIDGE_STATUS_NAMES[code] ?? `status_${code}`;

export class RomRuntimeHost {
  readonly adapters = new AdapterRegistry();
  readonly ledger = new BridgeLedger();
  readonly memory: GcMemory;

  #worker: Worker;
  #i32: Int32Array;
  #exportIndex: Map<string, number>;
  #exportNames: string[];
  #nestingCap: number;
  #busyWaitTimeoutMs: number;
  #queue: InvokeJob[] = [];
  #queueSignal: (() => void) | null = null;
  #closed = false;
  #pumpDone: Promise<void>;

  private constructor(
    worker: Worker,
    ctrl: SharedArrayBuffer,
    wasmMemory: WebAssembly.Memory,
    exportNames: string[],
    options: RomRuntimeHostOptions,
  ) {
    this.#worker = worker;
    this.#i32 = new Int32Array(ctrl);
    this.#exportNames = exportNames;
    this.#exportIndex = new Map(exportNames.map((name, index) => [name, index]));
    this.#nestingCap = options.nestingCap ?? DEFAULT_NESTING_CAP;
    this.#busyWaitTimeoutMs = options.busyWaitTimeoutMs ?? DEFAULT_BUSY_WAIT_TIMEOUT_MS;
    this.memory = new GcMemory(wasmMemory, options.memory ?? {});
    this.#pumpDone = this.#pump();
  }

  /**
   * Boot the runtime: hand the worker the module bytes + control block, wait
   * for it to instantiate (shared imported memory), install the arena, and
   * enter its park loop. After `ready`, ALL main->worker traffic is SAB-only —
   * the parked worker's event loop is intentionally blocked.
   */
  static start(worker: Worker, wasmBytes: ArrayBuffer, options: RomRuntimeHostOptions = {}): Promise<RomRuntimeHost> {
    const ctrl = new SharedArrayBuffer(CTRL_BYTE_LENGTH);
    return new Promise<RomRuntimeHost>((resolve, reject) => {
      const onMessage = (event: MessageEvent<WorkerMessage>) => {
        const message = event.data;
        if (message.type === "ready") {
          worker.removeEventListener("message", onMessage);
          resolve(new RomRuntimeHost(worker, ctrl, message.memory, message.exports, options));
        } else if (message.type === "fatal") {
          worker.removeEventListener("message", onMessage);
          reject(new Error(`rom-runtime worker failed to start: ${message.error}`));
        }
      };
      worker.addEventListener("message", onMessage);
      worker.addEventListener("error", (event) => {
        reject(new Error(`rom-runtime worker error: ${event.message}`));
      });
      const init: WorkerInitMessage = {
        type: "init",
        wasmBytes,
        ctrl,
        arena: options.arena ?? [],
      };
      worker.postMessage(init, [wasmBytes]);
    });
  }

  /** Function export names the worker's module offers (invoke targets). */
  get exportNames(): readonly string[] {
    return this.#exportNames;
  }

  registerAdapter(adapter: BridgedCalleeAdapter): void {
    this.adapters.register(adapter);
  }

  /**
   * Run one linked export on the worker (start/step control). Queued and
   * delivered as an invoke-request at the worker's next park point. Args are
   * i32s (<= 16); anything wider travels through a dispatch frame in shared
   * memory — write the frame first, pass its address.
   */
  invokeExport(exportName: string, args: number[] = []): Promise<number> {
    if (this.#closed) return Promise.reject(new Error("rom-runtime host is shut down"));
    if (args.length > INVOKE_MAX_ARGS) {
      return Promise.reject(new Error(`invoke ${exportName}: ${args.length} args exceeds ${INVOKE_MAX_ARGS}`));
    }
    if (!this.#exportIndex.has(exportName)) {
      return Promise.reject(
        new BridgeCallError(BridgeStatus.UNKNOWN_EXPORT, `invoke of unknown export ${exportName}`),
      );
    }
    return new Promise<number>((resolve, reject) => {
      this.#queue.push({ exportName, args, resolve, reject });
      this.#queueSignal?.();
    });
  }

  /**
   * Deliver a GC interrupt-style host event (VI retrace, DMA completion) as
   * an invoke-request at the worker's next park point (R3). Identical
   * transport to invokeExport — the distinct name records intent.
   */
  postEvent(exportName: string, args: number[] = []): Promise<number> {
    return this.invokeExport(exportName, args);
  }

  /** Advance the ledger's frame boundary (call once per driven frame). */
  nextFrame(): number {
    const frame = this.ledger.nextFrame();
    Atomics.store(this.#i32, Ctrl.FRAME_INDEX, frame | 0);
    return frame;
  }

  /** Stop the worker's dispatch loop and terminate the worker. */
  async shutdown(): Promise<void> {
    if (this.#closed) return;
    this.#closed = true;
    this.#queueSignal?.();
    await this.#pumpDone;
    // If the worker is parked, release it through the SAB (its event loop is
    // blocked and cannot see postMessage).
    if (Atomics.load(this.#i32, Ctrl.STATE) === BridgeState.PARKED) {
      Atomics.store(this.#i32, Ctrl.STATE, BridgeState.SHUTDOWN);
      Atomics.notify(this.#i32, Ctrl.STATE);
    }
    this.#worker.terminate();
  }

  // ---------------------------------------------------------------------------
  // Waiting primitives
  // ---------------------------------------------------------------------------

  /** Async wait until STATE leaves `observed` (Atomics.waitAsync when the
   *  engine has it, setTimeout polling otherwise). Main thread only ever
   *  waits ASYNC at top level — never Atomics.wait (R3). */
  async #awaitStateChange(observed: number): Promise<void> {
    const waitAsync = (
      Atomics as unknown as {
        waitAsync?: (
          array: Int32Array,
          index: number,
          value: number,
          timeout?: number,
        ) => { async: boolean; value: Promise<string> | string };
      }
    ).waitAsync;
    if (waitAsync) {
      const result = waitAsync(this.#i32, Ctrl.STATE, observed, 250);
      if (result.async) await result.value;
      return;
    }
    await new Promise((r) => setTimeout(r, 1));
  }

  /** Bounded synchronous busy-wait until STATE leaves `observed` — the
   *  nested-servicing discipline (R3): only legal while an adapter is
   *  mid-service (the worker is guaranteed responsive: it is blocked inside
   *  this very rendezvous). */
  #busyWaitStateChange(observed: number): void {
    const deadline = Date.now() + this.#busyWaitTimeoutMs;
    while (Atomics.load(this.#i32, Ctrl.STATE) === observed) {
      if (Date.now() > deadline) {
        this.ledger.recordError(null, BridgeStatus.WORKER_STALL, `worker did not respond within ${this.#busyWaitTimeoutMs}ms (state ${observed})`);
        throw new BridgeCallError(BridgeStatus.WORKER_STALL, "worker stalled during nested servicing");
      }
    }
  }

  // ---------------------------------------------------------------------------
  // Servicing pump (top level, async)
  // ---------------------------------------------------------------------------

  async #pump(): Promise<void> {
    while (!this.#closed) {
      if (this.#queue.length === 0) {
        await new Promise<void>((resolve) => {
          this.#queueSignal = resolve;
        });
        this.#queueSignal = null;
        continue;
      }
      // Deliver only to a PARKED worker (late invokes queue to the next park).
      let state = Atomics.load(this.#i32, Ctrl.STATE);
      while (state !== BridgeState.PARKED && !this.#closed) {
        await this.#awaitStateChange(state);
        state = Atomics.load(this.#i32, Ctrl.STATE);
      }
      if (this.#closed) break;
      const job = this.#queue.shift();
      if (!job) continue;
      try {
        job.resolve(await this.#deliverInvoke(job.exportName, job.args));
      } catch (error) {
        job.reject(error instanceof Error ? error : new Error(String(error)));
      }
    }
    // Drain queued jobs on shutdown.
    for (const job of this.#queue.splice(0)) {
      job.reject(new Error("rom-runtime host shut down before the invoke ran"));
    }
  }

  /** Publish one invoke to the parked worker and await INVOKE_DONE, servicing
   *  any bridged CALLs the running export makes along the way. */
  async #deliverInvoke(exportName: string, args: number[]): Promise<number> {
    const fnIndex = this.#exportIndex.get(exportName);
    if (fnIndex === undefined) {
      throw new BridgeCallError(BridgeStatus.UNKNOWN_EXPORT, `invoke of unknown export ${exportName}`);
    }
    const prior = Atomics.load(this.#i32, Ctrl.STATE); // PARKED
    this.#writeInvoke(fnIndex, args);
    Atomics.store(this.#i32, Ctrl.STATE, BridgeState.INVOKE);
    Atomics.notify(this.#i32, Ctrl.STATE);
    for (;;) {
      const state = Atomics.load(this.#i32, Ctrl.STATE);
      if (state === BridgeState.INVOKE_DONE) {
        return this.#consumeInvokeDone(prior, exportName);
      }
      if (state === BridgeState.CALL) {
        this.#serviceBridgeCall();
        continue;
      }
      await this.#awaitStateChange(state);
    }
  }

  #writeInvoke(fnIndex: number, args: number[]): void {
    Atomics.store(this.#i32, Ctrl.INV_FN, fnIndex | 0);
    Atomics.store(this.#i32, Ctrl.INV_ARGC, args.length | 0);
    for (let i = 0; i < args.length; i++) {
      Atomics.store(this.#i32, Ctrl.INV_ARGS + i, (args[i] ?? 0) | 0);
    }
  }

  #consumeInvokeDone(prior: number, exportName: string): number {
    const status = Atomics.load(this.#i32, Ctrl.INV_STATUS);
    const result = Atomics.load(this.#i32, Ctrl.INV_RESULT);
    Atomics.store(this.#i32, Ctrl.STATE, prior);
    Atomics.notify(this.#i32, Ctrl.STATE);
    if (status !== BridgeStatus.OK) {
      throw new BridgeCallError(status, `invoke ${exportName} failed: ${statusName(status)}`);
    }
    return result;
  }

  /**
   * Nested invoke from INSIDE a synchronous adapter (I2): the worker is
   * parked in its call-wait for the very call being serviced; it will take
   * the INVOKE wake and run the export on its own stack. Fully synchronous
   * here — bounded busy-wait, servicing nested CALLs recursively.
   */
  #syncInvoke(exportName: string, args: number[]): number {
    const fnIndex = this.#exportIndex.get(exportName);
    if (fnIndex === undefined) {
      throw new BridgeCallError(BridgeStatus.UNKNOWN_EXPORT, `invoke of unknown export ${exportName}`);
    }
    if (args.length > INVOKE_MAX_ARGS) {
      throw new BridgeCallError(BridgeStatus.EXPORT_THREW, `invoke ${exportName}: too many args`);
    }
    const prior = Atomics.load(this.#i32, Ctrl.STATE); // CALL (mid-service)
    this.#writeInvoke(fnIndex, args);
    Atomics.store(this.#i32, Ctrl.STATE, BridgeState.INVOKE);
    Atomics.notify(this.#i32, Ctrl.STATE);
    for (;;) {
      const state = Atomics.load(this.#i32, Ctrl.STATE);
      if (state === BridgeState.INVOKE_DONE) {
        return this.#consumeInvokeDone(prior, exportName);
      }
      if (state === BridgeState.CALL) {
        this.#serviceBridgeCall();
        continue;
      }
      this.#busyWaitStateChange(state);
    }
  }

  // ---------------------------------------------------------------------------
  // Bridged-call servicing (synchronous; runs with STATE === CALL)
  // ---------------------------------------------------------------------------

  #serviceBridgeCall(): void {
    const gcAddr = Atomics.load(this.#i32, Ctrl.CALL_GC_ADDR) >>> 0;
    const argptr = Atomics.load(this.#i32, Ctrl.CALL_ARGPTR) >>> 0;
    this.ledger.recordCall(gcAddr);

    const depth = Atomics.load(this.#i32, Ctrl.DEPTH) + 1;
    Atomics.store(this.#i32, Ctrl.DEPTH, depth);
    let status: number = BridgeStatus.OK;
    let result = 0;
    try {
      if (depth > this.#nestingCap) {
        status = BridgeStatus.NESTING_OVERFLOW;
        this.ledger.recordError(
          gcAddr,
          status,
          `bridged-servicing depth ${depth} exceeds the stated cap ${this.#nestingCap}`,
        );
      } else {
        const adapter = this.adapters.get(gcAddr);
        if (!adapter) {
          status = BridgeStatus.NO_ADAPTER;
          this.ledger.recordError(
            gcAddr,
            status,
            `no adapter registered for bridged callee 0x${gcAddr.toString(16).padStart(8, "0")} — ledger is the adapter work-queue (I1)`,
          );
        } else {
          const frame = new DispatchFrame(this.memory.dv, argptr);
          const ctx: BridgedCallContext = {
            gcAddr,
            argptr,
            frame,
            mem: this.memory,
            invoke: (name, invokeArgs = []) => this.#syncInvoke(name, invokeArgs),
          };
          try {
            const returned: unknown = adapter.service(ctx);
            if (returned !== null && (typeof returned === "object" || typeof returned === "function") && typeof (returned as PromiseLike<unknown>).then === "function") {
              // I2: bridged callees MUST be synchronous. The servicing already
              // escaped to an async path — declared error, frame fails loudly.
              status = BridgeStatus.ASYNC_SERVICING;
              this.ledger.recordError(
                gcAddr,
                status,
                `${adapter.name}: adapter returned a thenable — bridged callees are synchronous-only; preload async resources before servicing`,
              );
            } else {
              // Companion-review rule: the result is derived from the frame's
              // authoritative 8-byte ret slot (PPC r3 view — HIGH word for
              // i64), NEVER from the adapter's returned i32.
              result = frame.retPpcR3View();
              if (frame.retClass !== adapter.retClass) {
                this.ledger.recordError(
                  gcAddr,
                  BridgeStatus.RET_CLASS_MISMATCH,
                  `${adapter.name}: frame ret_class ${frame.retClass} disagrees with declared ${adapter.retClass} — possible mis-marshal`,
                );
              }
            }
          } catch (error) {
            if (error instanceof BridgeCallError) {
              // Propagate the ORIGINAL declared error (e.g. a nested
              // NESTING_OVERFLOW) without relabeling or re-recording it.
              status = error.status;
            } else {
              status = BridgeStatus.ADAPTER_THREW;
              this.ledger.recordError(
                gcAddr,
                status,
                `${adapter.name} threw: ${error instanceof Error ? error.message : String(error)}`,
              );
            }
          }
        }
      }
    } finally {
      Atomics.store(this.#i32, Ctrl.DEPTH, depth - 1);
    }

    Atomics.store(this.#i32, Ctrl.CALL_STATUS, status | 0);
    Atomics.store(this.#i32, Ctrl.CALL_RESULT, result | 0);
    Atomics.store(this.#i32, Ctrl.STATE, BridgeState.CALL_DONE);
    Atomics.notify(this.#i32, Ctrl.STATE);
  }
}

/**
 * Expose the ledger on window.__gf.bridgeLedger() (H2's reporting surface),
 * plus the adapter roster for the work-queue view.
 */
export function exposeBridgeLedger(host: RomRuntimeHost): void {
  const w = globalThis as unknown as {
    __gf?: Record<string, unknown>;
  };
  w.__gf = w.__gf ?? {};
  w.__gf["bridgeLedger"] = () => host.ledger.snapshot();
  w.__gf["bridgeAdapters"] = () => host.adapters.list();
}

export { FrameValueClass };
