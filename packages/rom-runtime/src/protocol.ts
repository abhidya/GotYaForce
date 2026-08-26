// =============================================================================
// protocol.ts — the H2/I2 Atomics RPC channel between the composed-module
// worker and the main-thread bridged-callee servicer.
//
// Design authority: docs/playable-port-design.md V4 H2 (host bridge), V5 I2
// (worker-side reentrant dispatch loop) and V5 verdict R3 (main thread cannot
// Atomics.wait; nested servicing uses the busy-wait / Atomics.waitAsync
// discipline; GC interrupt callbacks are delivered as invoke-requests at
// worker park points).
//
// TOPOLOGY (normative, H2 + I2):
//   - The WORKER owns the composed module and the shared WebAssembly.Memory.
//     It is the only thread that may block in Atomics.wait.
//   - The MAIN thread services bridged calls. It must NEVER call Atomics.wait
//     (agents whose [[CanBlock]] is false throw). Its top-level waits use
//     Atomics.waitAsync; its NESTED waits — issued from inside a synchronous
//     adapter — use a bounded busy-wait on Atomics.load.
//   - The main thread never calls worker exports directly. It publishes
//     INVOKE requests into the control block; the parked worker runs the
//     requested export ON ITS OWN STACK (I2's reentrant dispatch loop).
//
// CHANNEL = one SharedArrayBuffer control block (this file) + dispatch frames
// in the shared module memory (frame.ts, mirroring the wasm-side companion's
// gf_dispatch_frame.h — OGhidra src/port_dispatch_companion.py). The control
// block carries the rendezvous scalars (state, ids, status, i32 results);
// everything wide (arguments, wide returns, GC-pointer payloads) moves through
// dispatch frames in the shared linear memory at the frame ABI's fixed layout.
//
// CONTROL BLOCK LAYOUT — Int32Array over one SharedArrayBuffer:
//
//   idx  name            owner-at-write   meaning
//   ---  --------------  ---------------  -------------------------------------
//    0   STATE           both (see FSM)   the single Atomics rendezvous cell
//    1   SEQ             worker           bridge-call id, monotonically ++
//    2   CALL_GC_ADDR    worker           bridged callee's GC address (u32)
//    3   CALL_ARGPTR     worker           dispatch-frame address in shared mem
//    4   CALL_STATUS     main             BridgeStatus for the answered call
//    5   CALL_RESULT     main             i32 view of the bridged-call return
//    6   INV_FN          main             export-table index to invoke
//    7   INV_ARGC        main             invoke argument count (<= 16, i32s)
//    8   INV_STATUS      worker           BridgeStatus for the answered invoke
//    9   INV_RESULT      worker           i32 view of the invoke's return
//   10   DEPTH           main             current bridged-servicing depth
//   11   FRAME_INDEX     main             ledger frame index (informational)
//   16.. INV_ARGS[16]    main             invoke arguments (i32 each)
//
// STATE MACHINE (strictly nested; the channel is a rendezvous STACK, not a
// queue — each side captures the state it observed before publishing a
// request and RESTORES it after consuming the matching response, so nested
// rendezvous unwind like call frames):
//
//   IDLE(0)         quiescent; worker running plain code or not started.
//   CALL(1)         worker published a bridge call; main must service it.
//   CALL_DONE(2)    main published CALL_STATUS/CALL_RESULT for the innermost
//                   pending call; worker consumes and restores its prior state.
//   INVOKE(3)       main published an invoke request; the non-running worker
//                   (parked, or blocked in a call-wait) must run the export.
//   INVOKE_DONE(4)  worker published INV_STATUS/INV_RESULT; main consumes and
//                   restores its prior state.
//   PARKED(5)       worker is parked at a park point, servicing INVOKEs. This
//                   is the worker's steady state between driven frames; GC
//                   interrupt callbacks (VI retrace, DMA) are delivered here
//                   as ordinary INVOKE requests (R3).
//   SHUTDOWN(6)     main tells the parked worker to exit its dispatch loop.
//
//   Worker→main bridge call (H2 steps 1-3):
//     worker: write SEQ/CALL_GC_ADDR/CALL_ARGPTR, prior := STATE,
//             STATE := CALL, notify; then Atomics.wait loop distinguishing
//             the two wake kinds (I2):
//               CALL_DONE  -> consume result, STATE := prior, notify, return
//               INVOKE     -> run the export on its own stack (reentrant
//                             dispatch loop), publish INVOKE_DONE, re-wait
//     main (inside an await/busy-wait loop): sees CALL, services the adapter
//             synchronously, writes CALL_STATUS/CALL_RESULT,
//             STATE := CALL_DONE, notify.
//
//   Main→worker invoke (I2, R3):
//     main:   write INV_FN/INV_ARGC/INV_ARGS, prior := STATE,
//             STATE := INVOKE, notify; wait for INVOKE_DONE — via
//             Atomics.waitAsync at top level, via bounded busy-wait when
//             issued from inside a synchronous adapter — servicing any nested
//             CALL that appears while waiting; on INVOKE_DONE consume,
//             STATE := prior, notify.
//
// Nesting is bounded: DEPTH counts bridged-servicing levels on the main
// thread; exceeding the configured cap is a DECLARED SERVICING ERROR
// (BridgeStatus.NESTING_OVERFLOW) recorded in the ledger — never a hang.
// Async servicing paths (an adapter returning a thenable) are likewise
// declared errors (ASYNC_SERVICING): bridged callees MUST be synchronous, and
// adapters must preload async resources before servicing (I2).
// =============================================================================

/** Byte size of the control block SharedArrayBuffer (64 i32 cells). */
export const CTRL_BYTE_LENGTH = 64 * 4;

/** Control-block cell indices (Int32Array). */
export enum Ctrl {
  STATE = 0,
  SEQ = 1,
  CALL_GC_ADDR = 2,
  CALL_ARGPTR = 3,
  CALL_STATUS = 4,
  CALL_RESULT = 5,
  INV_FN = 6,
  INV_ARGC = 7,
  INV_STATUS = 8,
  INV_RESULT = 9,
  DEPTH = 10,
  FRAME_INDEX = 11,
  INV_ARGS = 16,
}

/** Maximum i32 arguments an invoke request carries in the control block.
 *  Anything wider or wilder travels through a dispatch frame in shared
 *  memory (frame.ts) — the invoke then passes the frame's address. */
export const INVOKE_MAX_ARGS = 16;

/** Rendezvous states (see the FSM above). */
export enum BridgeState {
  IDLE = 0,
  CALL = 1,
  CALL_DONE = 2,
  INVOKE = 3,
  INVOKE_DONE = 4,
  PARKED = 5,
  SHUTDOWN = 6,
}

/** Status codes for answered calls/invokes. Non-OK codes are DECLARED
 *  servicing errors (I2): every one of them is recorded loudly in the
 *  bridged-call ledger, never swallowed. */
export enum BridgeStatus {
  OK = 0,
  /** No adapter registered for the bridged callee's GC address (I1: the
   *  ledger is the adapter work-queue; an unserviced hit is loud). */
  NO_ADAPTER = 1,
  /** The adapter returned a thenable — bridged callees must be synchronous. */
  ASYNC_SERVICING = 2,
  /** Bridged-servicing depth exceeded the configured nesting cap. */
  NESTING_OVERFLOW = 3,
  /** The adapter threw. */
  ADAPTER_THREW = 4,
  /** The invoked worker export threw (non-bridge error). */
  EXPORT_THREW = 5,
  /** Invoke named an export the worker does not have. */
  UNKNOWN_EXPORT = 6,
  /** The other side failed to respond within the busy-wait bound. */
  WORKER_STALL = 7,
  /** Ledger-only signal (never fails the call): the ret_class the servicer
   *  wrote into the frame disagrees with the class declared for the symbol —
   *  the host-detectable mis-marshal signal from the dispatch-companion
   *  adversarial review (a wrong "true signature" mis-marshals silently under
   *  the uniform ABI; ret_class is written on every call precisely so the
   *  host can catch the disagreement). */
  RET_CLASS_MISMATCH = 8,
}

/** Human-readable status names for ledger records and errors. */
export const BRIDGE_STATUS_NAMES: Readonly<Record<number, string>> = {
  [BridgeStatus.OK]: "ok",
  [BridgeStatus.NO_ADAPTER]: "no_adapter",
  [BridgeStatus.ASYNC_SERVICING]: "async_servicing",
  [BridgeStatus.NESTING_OVERFLOW]: "nesting_overflow",
  [BridgeStatus.ADAPTER_THREW]: "adapter_threw",
  [BridgeStatus.EXPORT_THREW]: "export_threw",
  [BridgeStatus.UNKNOWN_EXPORT]: "unknown_export",
  [BridgeStatus.WORKER_STALL]: "worker_stall",
  [BridgeStatus.RET_CLASS_MISMATCH]: "ret_class_mismatch",
};

/** Default bound on nested bridged-servicing depth (I2 "stated maximum
 *  depth"). Small on purpose: legitimate reentrancy in the hybrid period is
 *  shallow (adapter -> linked export -> at most another adapter hop). */
export const DEFAULT_NESTING_CAP = 4;

/** Default bound (ms) on the main thread's synchronous busy-waits. */
export const DEFAULT_BUSY_WAIT_TIMEOUT_MS = 5_000;

/** Error thrown into wasm by the worker-side bridge stub when a bridged call
 *  came back with a non-OK status, and rethrown out of invokes that failed.
 *  Carries the BridgeStatus so nested layers can propagate the ORIGINAL
 *  declared error (e.g. NESTING_OVERFLOW) instead of relabeling it. */
export class BridgeCallError extends Error {
  readonly status: number;
  constructor(status: number, message: string) {
    super(message);
    this.name = "BridgeCallError";
    this.status = status;
  }
}

/** init message: main -> worker, once, before any SAB traffic. */
export interface WorkerInitMessage {
  type: "init";
  /** Threads-target wasm bytes (imported shared env.memory). Transferred. */
  wasmBytes: ArrayBuffer;
  /** The control block SharedArrayBuffer (CTRL_BYTE_LENGTH bytes). */
  ctrl: SharedArrayBuffer;
  /** Arena segments installed at GC addresses AFTER instantiation, BEFORE
   *  ready — the DOL-sourced image (or a synthetic test arena). */
  arena: Array<{ addr: number; bytes: Uint8Array }>;
}

/** ready message: worker -> main after instantiate + arena install. The
 *  worker then enters its blocking park loop and can never receive another
 *  postMessage — ALL further main->worker traffic goes through the SAB. */
export interface WorkerReadyMessage {
  type: "ready";
  /** Function export names, in the index order INV_FN refers to. */
  exports: string[];
  /** The shared WebAssembly.Memory the worker created for the module. */
  memory: WebAssembly.Memory;
}

export interface WorkerFatalMessage {
  type: "fatal";
  error: string;
}

export type WorkerMessage = WorkerReadyMessage | WorkerFatalMessage;
