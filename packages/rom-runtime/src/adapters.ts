// =============================================================================
// adapters.ts — the bridged-callee adapter class (design V5 I1).
//
// A bridged call is not serviced by "the TS scaffold" wholesale: it is
// serviced by a PER-SYMBOL host adapter that owns the full memory contract —
// it reads its arguments from GC memory (dereferencing GC-pointer args in the
// shared arena) and writes its results AND side-effects back to GC memory at
// the original addresses, the same observable behavior a linked callee would
// have. The TS scaffold MAY back an adapter's logic, but state moves into and
// out of GC memory at the adapter boundary — never implicitly through TS
// object state.
//
// Adapters are demand-driven from the bridged-call ledger (the work-queue)
// and each cites the evidence it derives from. The TraceDeltaAdapter below is
// the tractability mechanism the V5 verdict relies on: an adapter that
// mechanically applies recorded per-call memory deltas under DTM lockstep —
// auto-generatable from Dolphin trace captures, retired symbol-by-symbol as
// the ladder links.
// =============================================================================

import type { DispatchFrame } from "./frame.js";
import { FrameValueClass } from "./frame.js";
import type { GcMemory } from "./memory.js";

/**
 * How much an adapter's memory contract is actually worth (I1).
 *
 * This is a TYPE-LEVEL distinction on purpose. Before it existed, a pilot
 * stand-in written by hand with no capture behind it was indistinguishable
 * from a trace-backed adapter: both were `BridgedCalleeAdapter`s carrying a
 * free-text `evidence` string that nothing read. The registry now refuses
 * SYNTHETIC adapters unless the host was explicitly opened for them, so a
 * stub cannot drift into a path that services real frames.
 *
 *  - "verified":  derived from an oracle-verified seam contract or a real
 *                 Dolphin trace capture. May service anything.
 *  - "synthetic": DECLARED by hand, no capture. Carries NO behavioural claim
 *                 about its symbol and is admissible only on a host that was
 *                 opened for pilot work (`admitSyntheticAdapters`).
 */
export type AdapterEvidenceClass = "verified" | "synthetic";

/** What an adapter gets to service ONE bridged call. */
export interface BridgedCallContext {
  /** GC address of the bridged callee (the miss/bridge key). */
  gcAddr: number;
  /** Byte address of the caller-written dispatch frame in shared memory. */
  argptr: number;
  /** View over that frame (unmarshal args here, marshal the return here). */
  frame: DispatchFrame;
  /** The shared arena — the adapter's ONLY state channel (I1). */
  mem: GcMemory;
  /**
   * Invoke a linked worker export through the reentrant dispatch loop (I2):
   * the request is published to the parked worker, which runs the export on
   * its OWN stack. Synchronous from the adapter's point of view (bounded
   * busy-wait underneath). Throws BridgeCallError on servicing failure —
   * including NESTING_OVERFLOW when the bounded depth is exceeded.
   */
  invoke(exportName: string, args?: number[]): number;
}

/**
 * One per-symbol bridged-callee adapter. `service` MUST be synchronous
 * (I2: bridged callees are synchronous-only; a returned thenable is the
 * declared servicing error ASYNC_SERVICING).
 *
 * RETURN CONTRACT (companion review, normative): produce the return via the
 * frame's setRet* helpers — the frame's 8-byte ret slot + ret_class are the
 * AUTHORITATIVE return channel. The host derives the bridged call's i32
 * result from the frame (retPpcR3View: i64 returns yield the HIGH word, the
 * PPC r3 read) and NEVER from the number `service` happens to return; that
 * value is a convenience/diagnostic only.
 */
export interface BridgedCalleeAdapter {
  /** GC address this adapter services (the registry key). */
  readonly gcAddr: number;
  /** Symbol name, for the ledger and diagnostics. */
  readonly name: string;
  /** Where this adapter's memory contract comes from (trace file, verified
   *  seam, spec) — I1: an adapter without evidence is not a valid adapter. */
  readonly evidence: string;
  /** Whether that evidence is real. Enforced by AdapterRegistry, not advisory. */
  readonly evidenceClass: AdapterEvidenceClass;
  /** The symbol's DECLARED return class. After servicing, the host compares
   *  the frame's written ret_class against this and surfaces any disagreement
   *  in the ledger (RET_CLASS_MISMATCH — the host-detectable mis-marshal
   *  signal; see protocol.ts). */
  readonly retClass: FrameValueClass;
  service(ctx: BridgedCallContext): number;
}

/**
 * Address-keyed adapter registry — the main-thread service table.
 *
 * Refuses SYNTHETIC adapters unless it was constructed with
 * `admitSynthetic: true`. That flag is the ONLY way a stand-in with no capture
 * behind it can reach a service table, and the composed-module pilot is the
 * only caller that sets it (apps/game/src/rom/composedBoot.ts, behind the
 * opt-in `?composed=` switch).
 */
export class AdapterRegistry {
  #byAddr = new Map<number, BridgedCalleeAdapter>();
  readonly admitSynthetic: boolean;

  constructor(options: { admitSynthetic?: boolean } = {}) {
    this.admitSynthetic = options.admitSynthetic ?? false;
  }

  register(adapter: BridgedCalleeAdapter): void {
    const key = adapter.gcAddr >>> 0;
    if (adapter.evidenceClass === "synthetic" && !this.admitSynthetic) {
      throw new Error(
        `refusing SYNTHETIC adapter ${adapter.name} at 0x${key.toString(16)}: it has no capture behind it ` +
          `and carries no behavioural claim, so it may not service frames on this host. Open the host with ` +
          `admitSyntheticAdapters:true if this really is pilot work (${adapter.evidence})`,
      );
    }
    const existing = this.#byAddr.get(key);
    if (existing && existing !== adapter) {
      throw new Error(
        `adapter collision at 0x${key.toString(16)}: ${existing.name} already registered, refusing ${adapter.name}`,
      );
    }
    this.#byAddr.set(key, adapter);
  }

  get(gcAddr: number): BridgedCalleeAdapter | undefined {
    return this.#byAddr.get(gcAddr >>> 0);
  }

  /** True once any registered adapter is a synthetic stand-in — i.e. this
   *  host's results carry no behavioural claim. */
  get hasSyntheticAdapters(): boolean {
    return [...this.#byAddr.values()].some((a) => a.evidenceClass === "synthetic");
  }

  list(): Array<{ gcAddr: string; name: string; evidenceClass: AdapterEvidenceClass; evidence: string }> {
    return [...this.#byAddr.entries()]
      .sort((a, b) => a[0] - b[0])
      .map(([addr, a]) => ({
        gcAddr: (addr >>> 0).toString(16).padStart(8, "0"),
        name: a.name,
        evidenceClass: a.evidenceClass,
        evidence: a.evidence,
      }));
  }
}

// =============================================================================
// TraceDeltaAdapter — recorded per-call memory deltas, applied mechanically.
// =============================================================================

/** One recorded call of the traced symbol: the byte writes it performed and
 *  the return it produced, captured at its Stage-B breakpoints. */
export interface TraceDeltaCall {
  /** Byte writes at ABSOLUTE GC addresses, applied in order. */
  writes: Array<{ addr: number; bytes: number[] }>;
  /** The recorded return (omitted => void). */
  ret?:
    | { class: "i32"; value: number }
    | { class: "i64"; value: bigint }
    | { class: "f32"; value: number }
    | { class: "f64"; value: number };
}

/**
 * Applies its symbol's recorded per-call write set in call order — call N of
 * the replay consumes record N. Only valid under DTM lockstep (R2: adapter-
 * serviced frames are REPLAY frames); running past the recorded calls is a
 * servicing error (the adapter throws, surfacing ADAPTER_THREW in the
 * ledger), because an unrecorded call means the replay has diverged.
 */
export class TraceDeltaAdapter implements BridgedCalleeAdapter {
  readonly gcAddr: number;
  readonly name: string;
  readonly evidence: string;
  readonly evidenceClass: AdapterEvidenceClass;
  readonly retClass: FrameValueClass;
  #calls: TraceDeltaCall[];
  #cursor = 0;

  constructor(options: {
    gcAddr: number;
    name: string;
    /** Trace provenance (capture file / DTM id) — required by I1. */
    evidence: string;
    /** "verified" only for records that came out of a real capture. A fixture
     *  whose write set was hand-declared is "synthetic" — the class mechanism
     *  works either way, but only one of the two says anything about the ROM. */
    evidenceClass: AdapterEvidenceClass;
    calls: TraceDeltaCall[];
  }) {
    this.gcAddr = options.gcAddr >>> 0;
    this.name = options.name;
    this.evidence = options.evidence;
    this.evidenceClass = options.evidenceClass;
    this.#calls = options.calls;
    const classes = new Set(
      options.calls.map((c) =>
        c.ret === undefined
          ? FrameValueClass.VOID
          : { i32: FrameValueClass.I32, i64: FrameValueClass.I64, f32: FrameValueClass.F32, f64: FrameValueClass.F64 }[c.ret.class],
      ),
    );
    if (classes.size > 1) {
      throw new Error(`${options.name}: trace records disagree on return class — invalid capture`);
    }
    this.retClass = classes.values().next().value ?? FrameValueClass.VOID;
  }

  /** How many recorded calls have been consumed. */
  get cursor(): number {
    return this.#cursor;
  }

  /** Rewind for a fresh replay of the same DTM. */
  reset(): void {
    this.#cursor = 0;
  }

  service(ctx: BridgedCallContext): number {
    const record = this.#calls[this.#cursor];
    if (!record) {
      throw new Error(
        `${this.name}: trace exhausted after ${this.#calls.length} recorded call(s) — ` +
          `replay diverged from the DTM this adapter was derived from (${this.evidence})`,
      );
    }
    this.#cursor += 1;
    for (const write of record.writes) {
      ctx.mem.writeBytes(write.addr, Uint8Array.from(write.bytes));
    }
    const ret = record.ret;
    if (!ret) return ctx.frame.setRetVoid();
    switch (ret.class) {
      case "i32":
        return ctx.frame.setRetI32(ret.value);
      case "i64":
        return ctx.frame.setRetI64(ret.value);
      case "f32":
        return ctx.frame.setRetF32(ret.value);
      case "f64":
        return ctx.frame.setRetF64(ret.value);
    }
  }
}

/** Small helper for hand-written adapters. `evidenceClass` is required: an
 *  adapter author has to state, at the definition site, whether anything is
 *  actually behind the contract they just wrote. */
export function defineAdapter(options: {
  gcAddr: number;
  name: string;
  evidence: string;
  evidenceClass: AdapterEvidenceClass;
  retClass: FrameValueClass;
  service: (ctx: BridgedCallContext) => number;
}): BridgedCalleeAdapter {
  return {
    gcAddr: options.gcAddr >>> 0,
    name: options.name,
    evidence: options.evidence,
    evidenceClass: options.evidenceClass,
    retClass: options.retClass,
    service: options.service,
  };
}

export { FrameValueClass };
