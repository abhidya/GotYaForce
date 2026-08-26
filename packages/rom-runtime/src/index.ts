// @gf/rom-runtime — the composed-module execution runtime (design steps
// H2/I1/I2): worker-owned composed module + shared memory, Atomics ring-
// buffer RPC bridge, worker-side reentrant dispatch loop, per-symbol
// bridged-callee adapters, and the per-frame bridged-call ledger.
//
// Authority: docs/playable-port-design.md V4 H2/H3, V5 I1/I2 and verdict
// R1-R3. Wasm-side counterpart: the assembly gate's dispatch companion
// (OGhidra src/port_dispatch_companion.py — frame ABI v1, __gf_dispatch_miss).

export {
  CTRL_BYTE_LENGTH,
  Ctrl,
  BridgeState,
  BridgeStatus,
  BRIDGE_STATUS_NAMES,
  BridgeCallError,
  DEFAULT_NESTING_CAP,
  DEFAULT_BUSY_WAIT_TIMEOUT_MS,
  INVOKE_MAX_ARGS,
  type WorkerInitMessage,
  type WorkerReadyMessage,
  type WorkerFatalMessage,
  type WorkerMessage,
} from "./protocol.js";

export {
  FRAME_ABI_VERSION,
  FRAME_MAX_ARGS,
  FRAME_SLOT_SIZE,
  FRAME_SIZE,
  FRAME_ARG_COUNT_OFFSET,
  FRAME_RET_CLASS_OFFSET,
  FRAME_RET_OFFSET,
  FRAME_ARGS_OFFSET,
  FrameValueClass,
  DispatchFrame,
} from "./frame.js";

export { GcMemory, GC_HP_MIRROR_ADDR, GC_ENERGY_ADDR, type GcMemoryOptions } from "./memory.js";

export {
  BridgeLedger,
  type LedgerSnapshot,
  type LedgerFrameSnapshot,
  type LedgerErrorRecord,
} from "./ledger.js";

export {
  AdapterRegistry,
  TraceDeltaAdapter,
  defineAdapter,
  type BridgedCalleeAdapter,
  type BridgedCallContext,
  type TraceDeltaCall,
} from "./adapters.js";

export {
  createApplyHpDamageAdapter,
  createLookupTypeCategoryAdapter,
  GC_APPLY_HP_DAMAGE_ADDR,
  GC_LOOKUP_TYPE_CATEGORY_ADDR,
} from "./adapters/damage.js";

export { RomRuntimeHost, exposeBridgeLedger, type RomRuntimeHostOptions } from "./host.js";
export { installRomRuntimeWorker, importedMemoryLimits } from "./worker.js";
