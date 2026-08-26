// =============================================================================
// ledger.ts — the per-frame bridged-call ledger (design V4 H2, V5 I1/I2).
//
// One record per (frame, gc_addr): how many times that symbol crossed the
// worker->main boundary during the frame. The ledger is:
//   - the SHRINK METRIC: as the composition ladder links more symbols, the
//     per-frame bridged-call count falls monotonically (H2 gate (b));
//   - the ADAPTER WORK-QUEUE: adapters are written only for symbols the
//     ledger proves are actually hit (I1);
//   - the SERVICING-ERROR channel: every declared servicing error — async
//     path reached during servicing, nesting-depth overflow, unserviced hit,
//     adapter throw — lands here LOUDLY (I2), never as a silent hang.
//
// R2 discipline: any frame containing an adapter-serviced bridged call is a
// REPLAY frame (mode "dtm-replay") — the hybrid-period gates pin such frames
// to a recorded DTM; they are never interactive play. A frame whose calls
// were all serviced by linked code (i.e. no bridge crossings at all) stays
// "linked-only".
// =============================================================================

import { BRIDGE_STATUS_NAMES } from "./protocol.js";

export interface LedgerErrorRecord {
  /** GC address (8-hex string) of the bridged callee involved, if any. */
  gcAddr: string | null;
  /** BridgeStatus numeric code. */
  code: number;
  /** Human-readable status name (BRIDGE_STATUS_NAMES). */
  status: string;
  detail: string;
}

export interface LedgerFrameSnapshot {
  frame: number;
  /** "dtm-replay" once any adapter serviced a bridged call this frame (R2);
   *  "linked-only" while no bridge crossing has occurred. */
  mode: "dtm-replay" | "linked-only";
  calls: Array<{ gcAddr: string; count: number }>;
  errors: LedgerErrorRecord[];
  bridgedCallCount: number;
}

export interface LedgerSnapshot {
  currentFrame: number;
  frames: LedgerFrameSnapshot[];
  totals: {
    bridgedCalls: number;
    servicingErrors: number;
    byAddr: Array<{ gcAddr: string; count: number }>;
  };
}

const hex = (addr: number): string => (addr >>> 0).toString(16).padStart(8, "0");

interface FrameRecord {
  frame: number;
  mode: "dtm-replay" | "linked-only";
  calls: Map<number, number>;
  errors: LedgerErrorRecord[];
}

export class BridgeLedger {
  #frames: FrameRecord[] = [];
  #current: FrameRecord;
  #totalsByAddr = new Map<number, number>();
  #totalCalls = 0;
  #totalErrors = 0;

  constructor() {
    this.#current = { frame: 0, mode: "linked-only", calls: new Map(), errors: [] };
    this.#frames.push(this.#current);
  }

  get currentFrame(): number {
    return this.#current.frame;
  }

  /** Advance the frame boundary. Called once per driven frame by the host. */
  nextFrame(): number {
    this.#current = {
      frame: this.#current.frame + 1,
      mode: "linked-only",
      calls: new Map(),
      errors: [],
    };
    this.#frames.push(this.#current);
    return this.#current.frame;
  }

  /** Record one bridged call crossing the boundary this frame. */
  recordCall(gcAddr: number): void {
    const key = gcAddr >>> 0;
    this.#current.calls.set(key, (this.#current.calls.get(key) ?? 0) + 1);
    this.#totalsByAddr.set(key, (this.#totalsByAddr.get(key) ?? 0) + 1);
    this.#totalCalls += 1;
    // R2: a bridge crossing means this frame is adapter-serviced territory.
    this.#current.mode = "dtm-replay";
  }

  /** Record one DECLARED servicing error (loud channel, I2). */
  recordError(gcAddr: number | null, code: number, detail: string): void {
    this.#current.errors.push({
      gcAddr: gcAddr === null ? null : hex(gcAddr),
      code,
      status: BRIDGE_STATUS_NAMES[code] ?? `status_${code}`,
      detail,
    });
    this.#totalErrors += 1;
  }

  get servicingErrorCount(): number {
    return this.#totalErrors;
  }

  /** JSON-safe snapshot — the window.__gf.bridgeLedger() payload. */
  snapshot(): LedgerSnapshot {
    return {
      currentFrame: this.#current.frame,
      frames: this.#frames.map((f) => ({
        frame: f.frame,
        mode: f.mode,
        calls: [...f.calls.entries()]
          .sort((a, b) => a[0] - b[0])
          .map(([addr, count]) => ({ gcAddr: hex(addr), count })),
        errors: [...f.errors],
        bridgedCallCount: [...f.calls.values()].reduce((a, b) => a + b, 0),
      })),
      totals: {
        bridgedCalls: this.#totalCalls,
        servicingErrors: this.#totalErrors,
        byAddr: [...this.#totalsByAddr.entries()]
          .sort((a, b) => a[0] - b[0])
          .map(([addr, count]) => ({ gcAddr: hex(addr), count })),
      },
    };
  }
}
