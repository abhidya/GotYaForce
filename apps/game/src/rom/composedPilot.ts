// =============================================================================
// composedPilot.ts — the COMPOSED-MODULE DISPATCH PILOT.
//
// SCOPE, stated exactly (docs/composed-pilot.md is the long form):
//
//   This is NOT control inversion. Control inversion (design V4 H2 gate (a))
//   requires `run_main_game_loop` (0x800527d8) to be linked INTO the composed
//   window and to drive frames itself. Rung 0 is five units; the ROM's loop is
//   not among them and has no execution model here at all. What this pilot
//   drives is the inverse: the HOST calls into the composed module once per
//   rendered game frame, and every call the module makes back out of its
//   window crosses the H2 bridge.
//
//   What it therefore DOES prove, in the real game, under cross-origin
//   isolation, with the real gate-produced module:
//     - the composed rung-0 module instantiates with 2GB imported SHARED
//       memory and the DOL arena installed at original GC addresses;
//     - its live 40-thunk dispatch table resolves a GC address and runs the
//       ROM's own compiled code (`__gf_dispatch`);
//     - a table MISS routes through `__gf_dispatch_miss` to a bridged host
//       adapter and returns (H3: a miss is a bridge call, never a trap);
//     - a DIRECT call from linked code to an unlinked callee routes through
//       the same bridge via its declared import trampoline (H2's other edge);
//     - adapters own the memory contract (I1): they read GC-pointer arguments
//       out of the shared arena and write side-effects back at original
//       addresses, and the module's own subsequent writes are visible there;
//     - the I2 reentrant case: a bridged adapter invokes a linked export
//       through the worker's dispatch loop and gets the right answer back;
//     - the per-frame bridged-call ledger records every crossing.
//
//   What it does NOT prove: any behavioural claim about these five units.
//   The threads relink SUSPENDS their verification (docs/threads-relink-
//   reverify.md) and none has been re-verified; the adapters are pilot
//   stand-ins with no Dolphin trace behind them; and the arena state the
//   pilot seeds is synthetic, not a DTM. The frame-boundary state check below
//   is against a DECLARED expectation, not against a trace (I1's real state-
//   evidence gate is unmet and stays open).
//
// Driven window (chosen because it exercises every edge in one call):
//
//   zz_01b9b1c_ @ 0x801b9b1c  (rung-0 unit auto-c0053-013, table entry)
//       zz_0085e00_(p, p+0x20, 0);   -> DIRECT out-of-window call (bridged)
//       *(u8*)(p+0x18) = 2;          -> module's own write into the arena
//       zz_008aff0_(p);              -> DIRECT out-of-window call (bridged,
//                                       and the REENTRANT adapter)
//       *(u8*)(p+0x82) = 0;          -> module's own write into the arena
//
//   zz_01b9b68_ @ 0x801b9b68  (same unit, table entry)
//       q = *(int*)(p+0x90);
//       if (*(s16*)(q+1000) == 0x407 && *(s8*)(q+0x150) == 1) {
//           zz_006de10_(q, 2);       -> CONDITIONAL bridged call, gated on
//           *(u8*)(q+0x150) = 0;        arena state the pilot seeds
//       }
//       ... then the same two writes + zz_008aff0_ as above.
//
//   zz_0085e00_ @ 0x80085e00  invoked DIRECTLY as a dispatch address: it is
//       out of window, so it is absent from the 40-entry table and takes the
//       MISS path deliberately.
//
//   zz_01b9be0_ @ 0x801b9be0  (table entry) is the reentrancy target. With
//       *(int*)(q+200) == 0 it takes its early exit, whose result is
//       -(short)(int)(FLOAT_8043ba9c * FLOAT_8043ba5c) — two floats the pilot
//       seeds into GC memory, so the answer is a non-trivial value computed by
//       the ROM's own compiled code rather than a constant that a stub could
//       fake.
// =============================================================================

import {
  DispatchFrame,
  FRAME_SIZE,
  FrameValueClass,
  TraceDeltaAdapter,
  defineAdapter,
  hostFrameAddr,
  type BridgedCalleeAdapter,
  type RomRuntimeHost,
  type TraceDeltaCall,
} from "@gf/rom-runtime";

/** GC addresses of the rung-0 table entries the pilot drives. */
export const GC_ZZ_01B9B1C = 0x801b9b1c;
export const GC_ZZ_01B9B68 = 0x801b9b68;
export const GC_ZZ_01B9BE0 = 0x801b9be0;
/** GC addresses of the out-of-window callees the pilot's window reaches. */
export const GC_ZZ_0085E00 = 0x80085e00;
export const GC_ZZ_008AFF0 = 0x8008aff0;
export const GC_ZZ_006DE10 = 0x8006de10;

/**
 * Pilot-owned GC scratch. These are NOT ROM object addresses — the pilot has
 * no live game object to point the ROM code at, so it stands up a synthetic
 * actor/target pair in a region of the GC window that neither the DOL arena
 * (apps/game/public/rom/arena.json) nor any module data segment occupies.
 * `assertRegionClear` proves that emptiness at boot instead of assuming it.
 */
export const PILOT_ACTOR_ADDR = 0x80500000;
export const PILOT_TARGET_ADDR = 0x80501000;
export const PILOT_REGION_BYTES = 0x2000;

/** Float constants the driven early-exit path reads (GC .sdata2 addresses
 *  outside the shipped arena, hence zero until the pilot seeds them). */
const GC_FLOAT_8043BA5C = 0x8043ba5c;
const GC_FLOAT_8043BA9C = 0x8043ba9c;
const PILOT_FLOAT_A = 3;
const PILOT_FLOAT_B = 14;
/** -(short)(int)(14.0f * 3.0f) — what zz_01b9be0_'s early exit must return. */
export const PILOT_REENTRANT_EXPECTED = -(PILOT_FLOAT_A * PILOT_FLOAT_B);

/** Host dispatch-frame slots (composed.ts reserves HOST_FRAME_SLOTS of them). */
const FRAME_SLOT_PRIMARY = 0;
const FRAME_SLOT_SECONDARY = 1;
const FRAME_SLOT_MISS = 2;
/** Reserved for the reentrant invoke issued from INSIDE an adapter, which
 *  must not reuse a frame the outer dispatch is still holding. */
const FRAME_SLOT_REENTRANT = 5;

const NO_TRACE_EVIDENCE =
  "PILOT STUB — no Dolphin capture exists for this symbol. Declared write set only; " +
  "not a valid I1 adapter and carries no behavioural claim (docs/composed-pilot.md).";

export interface PilotFrameResult {
  frame: number;
  /** Bridged crossings the ledger recorded for this frame. */
  bridgedCalls: number;
  /** The reentrant invoke's result, straight out of the composed module. */
  reentrantResult: number;
  /** Declared frame-boundary state checks (NOT a DTM comparison). */
  state: Array<{ name: string; expected: number; actual: number; pass: boolean }>;
  pass: boolean;
}

/** Mutable channel the reentrant adapter reports through. Keeping it explicit
 *  (rather than module-level state) means two hosts can never cross-talk. */
export interface PilotState {
  lastReentrantResult: number;
}

/** One recorded call of the trace-delta fixture, as it ships on disk. */
export interface PilotFixture {
  symbol: string;
  gcAddr: number;
  evidence: string;
  calls: Array<{ writes: Array<{ addr: number; bytes: number[] }> }>;
}

function hex(addr: number): string {
  return `0x${(addr >>> 0).toString(16).padStart(8, "0")}`;
}

/**
 * Build the pilot's adapter set. Registered up front here rather than
 * demand-driven from the ledger because the pilot's driven window is fixed and
 * known; on a real ladder the ledger is the work-queue (I1).
 */
export function createPilotAdapters(
  host: RomRuntimeHost,
  fixture: PilotFixture,
  pilotState: PilotState,
): BridgedCalleeAdapter[] {
  const reentrantFrame = hostFrameAddr(FRAME_SLOT_REENTRANT, FRAME_SIZE);

  // (a) DIRECT-call edge + GC-pointer argument marshalling. The callee's
  //     second parameter is a pointer INTO the caller's struct; the adapter
  //     dereferences it out of the shared arena and writes there, which is
  //     exactly the memory contract I1 demands of a bridged callee.
  const applyStructInit = defineAdapter({
    gcAddr: GC_ZZ_0085E00,
    name: "zz_0085e00_",
    evidence: NO_TRACE_EVIDENCE,
    retClass: FrameValueClass.VOID,
    service: (ctx) => {
      const structPtr = ctx.frame.u32Arg(1);
      ctx.mem.writeU32(structPtr, 0x5e005e00);
      return ctx.frame.setRetVoid();
    },
  });

  // (b) The I2 REENTRANT case: this adapter, mid-service on the main thread,
  //     asks the PARKED worker to run a linked export on its own stack and
  //     uses the answer. Deadlock-by-construction is what I2 exists to
  //     prevent; a leaf-only adapter set never exercises it.
  const notifyAndReenter = defineAdapter({
    gcAddr: GC_ZZ_008AFF0,
    name: "zz_008aff0_",
    evidence: NO_TRACE_EVIDENCE,
    retClass: FrameValueClass.VOID,
    service: (ctx) => {
      const actor = ctx.frame.u32Arg(0);
      ctx.mem.writeU8(actor + 0x83, 0xaf);
      const inner = new DispatchFrame(ctx.mem.dv, reentrantFrame);
      inner.argCount = 2;
      inner.setI32Arg(0, PILOT_TARGET_ADDR);
      inner.setI32Arg(1, 0);
      const result = ctx.invoke("__gf_dispatch", [GC_ZZ_01B9BE0 | 0, reentrantFrame]);
      pilotState.lastReentrantResult = result;
      ctx.mem.writeI16(actor + 0x84, result);
      return ctx.frame.setRetVoid();
    },
  });

  // (c) The TraceDeltaAdapter mechanism, running against a committed fixture.
  //     The fixture is SYNTHETIC (see its own `evidence` string): it proves
  //     the class works end to end — recorded per-call write sets applied in
  //     call order, exhaustion raising a loud servicing error — not that these
  //     bytes are what the ROM writes.
  const calls: TraceDeltaCall[] = fixture.calls.map((c) => ({ writes: c.writes }));
  const traceDelta = new TraceDeltaAdapter({
    gcAddr: fixture.gcAddr,
    name: fixture.symbol,
    evidence: fixture.evidence,
    calls,
  });

  const adapters = [applyStructInit, notifyAndReenter, traceDelta];
  for (const adapter of adapters) host.registerAdapter(adapter);
  return adapters;
}

/** Fail loudly if the pilot's GC scratch is not actually free. */
export function assertRegionClear(host: RomRuntimeHost, addr: number, length: number, label: string): void {
  const bytes = host.memory.readBytes(addr, length);
  for (let i = 0; i < bytes.length; i++) {
    if (bytes[i] !== 0) {
      throw new Error(`${label} at ${hex(addr)} is not free: byte +0x${i.toString(16)} = ${bytes[i]}`);
    }
  }
}

/** Seed the arena state the driven window reads. Re-applied every frame so
 *  each frame's writes are observable against a known starting point. */
function seedFrameState(host: RomRuntimeHost): void {
  const mem = host.memory;
  const a = PILOT_ACTOR_ADDR;
  const t = PILOT_TARGET_ADDR;
  mem.writeU8(a + 0x18, 0); // module writes 2
  mem.writeU8(a + 0x82, 0xff); // module writes 0
  mem.writeU32(a + 0x20, 0); // zz_0085e00_ adapter writes 0x5e005e00
  mem.writeU8(a + 0x83, 0); // zz_008aff0_ adapter writes 0xaf
  mem.writeI16(a + 0x84, 0); // zz_008aff0_ adapter writes the reentrant result
  mem.writeU32(a + 0x90, t); // the target pointer zz_01b9b68_ follows
  mem.writeU16(t + 1000, 0x407); // gate 1 of the conditional bridged call
  mem.writeU8(t + 0x150, 1); // gate 2; module writes 0 after the call
  mem.writeU8(t + 0x160, 0); // the trace-delta adapter's recorded write
  mem.writeU32(t + 200, 0); // zz_01b9be0_'s early-exit condition
  mem.writeF32(GC_FLOAT_8043BA5C, PILOT_FLOAT_A);
  mem.writeF32(GC_FLOAT_8043BA9C, PILOT_FLOAT_B);
}

/** Write one dispatch frame's arguments and return its address. */
function writeFrame(host: RomRuntimeHost, slot: number, args: number[]): number {
  const addr = hostFrameAddr(slot, FRAME_SIZE);
  const frame = new DispatchFrame(host.memory.dv, addr);
  frame.argCount = args.length;
  for (let i = 0; i < args.length; i++) frame.setI32Arg(i, args[i] ?? 0);
  return addr;
}

/**
 * Drive ONE pilot frame: advance the ledger boundary, seed the arena, run the
 * three dispatches, and check the frame-boundary state against the declared
 * expectation.
 */
export async function drivePilotFrame(
  host: RomRuntimeHost,
  pilotState: PilotState,
  fixtureWriteAddr: number,
  fixtureWriteByte: number,
): Promise<PilotFrameResult> {
  const frameIndex = host.nextFrame();
  seedFrameState(host);
  pilotState.lastReentrantResult = Number.NaN;

  // 1. table HIT: the module's own compiled code, reaching two bridged callees.
  await host.invokeExport("__gf_dispatch", [GC_ZZ_01B9B1C | 0, writeFrame(host, FRAME_SLOT_PRIMARY, [PILOT_ACTOR_ADDR])]);
  // 2. table HIT with a state-gated bridged call (the trace-delta adapter).
  await host.invokeExport("__gf_dispatch", [GC_ZZ_01B9B68 | 0, writeFrame(host, FRAME_SLOT_SECONDARY, [PILOT_ACTOR_ADDR])]);
  // 3. table MISS: an out-of-window address, routed by __gf_dispatch_miss.
  await host.invokeExport("__gf_dispatch", [
    GC_ZZ_0085E00 | 0,
    writeFrame(host, FRAME_SLOT_MISS, [PILOT_ACTOR_ADDR, PILOT_ACTOR_ADDR + 0x20, 0]),
  ]);

  const mem = host.memory;
  const a = PILOT_ACTOR_ADDR;
  const t = PILOT_TARGET_ADDR;
  const state = [
    { name: "module wrote actor+0x18 = 2", expected: 2, actual: mem.readU8(a + 0x18) },
    { name: "module wrote actor+0x82 = 0", expected: 0, actual: mem.readU8(a + 0x82) },
    { name: "module wrote target+0x150 = 0", expected: 0, actual: mem.readU8(t + 0x150) },
    { name: "adapter wrote *(actor+0x20) via GC-pointer arg", expected: 0x5e005e00, actual: mem.readU32(a + 0x20) },
    { name: "adapter wrote actor+0x83 = 0xaf", expected: 0xaf, actual: mem.readU8(a + 0x83) },
    {
      name: "reentrant invoke result stored at actor+0x84",
      expected: PILOT_REENTRANT_EXPECTED,
      actual: mem.readI16(a + 0x84),
    },
    { name: "trace-delta adapter applied its recorded write", expected: fixtureWriteByte, actual: mem.readU8(fixtureWriteAddr) },
    {
      name: "reentrant invoke returned the module's computed value",
      expected: PILOT_REENTRANT_EXPECTED,
      actual: pilotState.lastReentrantResult,
    },
  ].map((check) => ({ ...check, pass: check.expected === check.actual }));

  const ledgerFrame = host.ledger.snapshot().frames.find((f) => f.frame === frameIndex);
  return {
    frame: frameIndex,
    bridgedCalls: ledgerFrame?.bridgedCallCount ?? 0,
    reentrantResult: pilotState.lastReentrantResult,
    state,
    pass: state.every((c) => c.pass) && (ledgerFrame?.errors.length ?? 0) === 0,
  };
}
