// =============================================================================
// gxCallstreamHost.ts — the GX host, driveable from node, for the CALL-STREAM
// ORACLE (research/decomp/oracle-harness/run-gx-callstream.mjs).
//
// WHY THIS EXISTS AND WHAT IT IS NOT
//
// docs/gx-hle-host.md §6.3: this host's pixel assertions are predicted from the
// same understanding of GX that produced the implementation, so they cannot
// detect a shared misunderstanding. The only way out is to compare against the
// console. `research/tools/dolphin-trace/capture_gx.py` records, from the real
// game, the ordered stream a ROM draw function emits at the SDK seam — every GX
// call with its PowerPC-register arguments, and every write-gather-pipe store
// with its width and value. This module lets a node harness:
//
//   1. run the SAME ROM function (the assembly gate's gate-lowered wasm unit)
//      against these adapters and record the stream the host RECEIVES, and
//   2. push the CONSOLE's captured stream through the same adapters,
//
// so the two can be compared byte for byte and value for value.
//
// This is a SEAM oracle. It reads no framebuffer and makes no claim about
// pixels. `GX_NO_BEHAVIOURAL_CLAIM` still applies verbatim to every adapter
// here, and every adapter is still `evidenceClass: "synthetic"` — a matching
// call stream says the host is FED correctly, not that it DRAWS correctly.
//
// It deliberately does NOT go through `RomRuntimeHost`. That host is the H2
// Atomics bridge between a worker and the main thread, and its trampoline
// machinery is what the browser leg proves (docs/gx-hle-host.md §5). Bringing
// it into a node harness would make the oracle depend on the bridge's liveness
// rather than on the adapters, and the bridge is not what the console can be
// compared against. Instead this module dispatches straight into the SAME
// `BridgedCalleeAdapter` objects the bridge would land on, through a real
// `DispatchFrame` with the real ABI — the same code path minus the transport.
// =============================================================================

import { AdapterRegistry, type BridgedCallContext, type BridgedCalleeAdapter } from "../../adapters.js";
import { gcAddressForSymbol } from "../../composed.js";
import { DispatchFrame, FRAME_SIZE } from "../../frame.js";
import { GcMemory } from "../../memory.js";
import { GxRecordingBackend } from "../backend.js";
import {
  GxHost,
  GX_NO_BEHAVIOURAL_CLAIM,
  registerGxAdapters,
  registerPsmtxIdentityAdapter,
  registerWgPipeAdapters,
} from "../adapters.js";

/** One event as it arrives at the host, in arrival order. */
export type GxStreamEvent =
  | { k: "call"; callee: string; args: number[] }
  | { k: "wgpipe"; import: string; width: number; value: number };

export interface GxCallstreamHost {
  readonly memory: WebAssembly.Memory;
  readonly mem: GcMemory;
  readonly gx: GxHost;
  readonly backend: GxRecordingBackend;
  /** Everything the host was asked to service, in order. */
  readonly stream: GxStreamEvent[];
  /** Names of adapters registered, for the roster the artifact records. */
  adapterNames(): string[];
  /** Service one call by SYMBOL NAME with i32 arguments, through a real
   *  dispatch frame. Throws exactly what the adapter throws. */
  call(name: string, args: readonly number[]): void;
  /** The import table for a gate-lowered ROM unit: every import name mapped to
   *  a function that records the event and services it. */
  imports(names: readonly string[]): Record<string, (...a: number[]) => void>;
  reset(): void;
}

const WGPIPE_WIDTH: Record<string, number> = {
  __gf_gx_wgpipe_u8: 1,
  __gf_gx_wgpipe_u16: 2,
  __gf_gx_wgpipe_u32: 4,
  __gf_gx_wgpipe_f32: 4,
};

/**
 * Build a host over an existing shared linear memory.
 *
 * `memory` must be the SAME memory the ROM unit is instantiated against: the
 * composed module maps GameCube addresses straight to linear-memory offsets, so
 * a pointer argument the ROM passes is directly an offset here.
 */
export function createGxCallstreamHost(memory: WebAssembly.Memory): GxCallstreamHost {
  const mem = new GcMemory(memory);
  const backend = new GxRecordingBackend();
  const gx = new GxHost(backend, mem);
  const stream: GxStreamEvent[] = [];

  // `admitSynthetic` is REQUIRED and is the honest setting: every GX adapter is
  // a synthetic stand-in, and the registry exists to stop one reaching a host
  // that claims otherwise. An oracle run is pilot work by definition.
  const registry = new AdapterRegistry({ admitSynthetic: true });
  const byName = new Map<string, BridgedCalleeAdapter>();
  const collector = {
    registerAdapter(adapter: BridgedCalleeAdapter): void {
      registry.register(adapter);
      byName.set(adapter.name, adapter);
    },
  };
  registerGxAdapters(collector, gx);
  registerWgPipeAdapters(collector, gx);
  registerPsmtxIdentityAdapter(collector);

  // The dispatch frame lives in its own buffer rather than in the arena: it is
  // the CALLER's scratch in the real bridge, the adapters only ever read
  // arguments out of it, and keeping it outside the arena means an oracle run
  // cannot perturb a GameCube address the ROM function also reads.
  const frameBuf = new ArrayBuffer(FRAME_SIZE);
  const frameView = new DataView(frameBuf);

  const call = (name: string, args: readonly number[]): void => {
    const adapter = byName.get(name);
    if (!adapter) {
      throw new Error(
        `gx call-stream host has no adapter for ${name} — the ROM unit imports a symbol ` +
          `this host does not service, which is a real gap, not a harness detail`,
      );
    }
    const frame = new DispatchFrame(frameView, 0);
    frame.argCount = args.length;
    for (let i = 0; i < args.length; i++) frame.setI32Arg(i, (args[i] ?? 0) | 0);
    const ctx: BridgedCallContext = {
      gcAddr: adapter.gcAddr,
      argptr: 0,
      frame,
      mem,
      invoke(): number {
        throw new Error(
          `${name} tried to re-enter a worker export; the call-stream oracle has no worker ` +
            `(and no GX entry point does this)`,
        );
      },
    };
    adapter.service(ctx);
  };

  return {
    memory,
    mem,
    gx,
    backend,
    stream,
    adapterNames: () => [...byName.keys()].sort(),
    call(name, args) {
      const width = WGPIPE_WIDTH[name];
      stream.push(
        width === undefined
          ? { k: "call", callee: name, args: [...args].map((v) => v >>> 0) }
          : { k: "wgpipe", import: name, width, value: (args[0] ?? 0) >>> 0 },
      );
      call(name, args);
    },
    imports(names) {
      const table: Record<string, (...a: number[]) => void> = {};
      for (const name of names) {
        table[name] = (...a: number[]) => {
          this.call(name, a);
        };
      }
      return table;
    },
    reset() {
      stream.length = 0;
    },
  };
}

export { GX_NO_BEHAVIOURAL_CLAIM, gcAddressForSymbol };
