import type { BorgRuntime } from "./types.js";

/** zz_00686f0_ slot 2, pl0101data.bin +0x18c. Neutral host timestep only. */
export interface PoweredChargeState {
  warmup: number;
  charge: number;
  ready: boolean;
  releasedReady: boolean;
  held: boolean;
  releaseEdge: boolean;
  pressEdge: boolean;
  pending: boolean;
}
export function stepPoweredCharge(b: BorgRuntime, held: boolean, activeCommand5 = false): PoweredChargeState {
  const s = b.poweredCharge ??= { warmup: 0, charge: 0, ready: false, releasedReady: false, held: false, pressEdge: false, releaseEdge: false, pending: false };
  s.pressEdge = !s.held && held;
  s.releaseEdge = s.held && !held;
  s.held = held;
  s.ready = false;
  s.releasedReady = false;
  if (activeCommand5) {
    s.warmup = s.charge = 0;
  } else if (!held) {
    // Source tests readiness BEFORE decay, including a failed command admission.
    s.releasedReady = s.charge >= 180;
    s.warmup = 0;
    s.charge = Math.max(0, s.charge - 2);
  } else if (s.warmup < 10) {
    s.warmup += 1;
  } else {
    // Host's paired active burst is the bounded mapping to source +0x6fc.
    s.charge = Math.min(180, s.charge + (b.burstActive && b.burstPaired ? 10 : 1));
    s.ready = s.charge >= 180;
  }
  s.pending = true;
  return s;
}
export function commitPoweredCharge(b: BorgRuntime): void {
  if (b.poweredCharge) b.poweredCharge.warmup = b.poweredCharge.charge = 0;
}
