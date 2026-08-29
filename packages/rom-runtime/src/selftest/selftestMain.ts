// =============================================================================
// selftestMain.ts — browser self-test for the composed-module execution
// runtime (H2 bridge + I2 reentrant dispatch loop + I1 adapters + ledger).
//
// Runs against the committed threads-target fixture
// test/fixtures/bridge-selftest/bridge_selftest.threads.wasm behind the COI
// setup (SharedArrayBuffer + shared wasm memory require crossOriginIsolated).
// Driven headless by scripts/smoke-rom-runtime-phase.mjs, which asserts
// window.__gfRomRuntimeSelfTest and captures screenshots/console evidence.
//
// The four required proofs (task + design gates):
//   1. correct results        — round trip, trace-delta replay, REAL
//                               scaffold-backed damage adapters, i64 r3 rule
//   2. ledger entries         — per-frame {gc_addr, count} records
//   3. reentrant case green   — bridged call whose adapter invokes a linked
//                               export through the dispatch loop (I2 gate)
//   4. nesting overflow loud  — declared servicing error in the ledger
// =============================================================================

import { lookupTypeCategory } from "@gf/combat";
import { TraceDeltaAdapter, defineAdapter, type BridgedCallContext } from "../adapters.js";
import { createApplyHpDamageAdapter, createLookupTypeCategoryAdapter } from "../adapters/damage.js";
import { FrameValueClass } from "../frame.js";
import { BridgeCallError, BridgeStatus } from "../protocol.js";
import { RomRuntimeHost, exposeBridgeLedger } from "../host.js";

interface CheckResult {
  name: string;
  pass: boolean;
  expected: string;
  actual: string;
}

const results: CheckResult[] = [];

function check(name: string, actual: unknown, expected: unknown): void {
  const pass = Object.is(actual, expected) || JSON.stringify(actual) === JSON.stringify(expected);
  results.push({ name, pass, expected: String(expected), actual: String(actual) });
}

async function expectBridgeError(name: string, promise: Promise<number>, status: BridgeStatus): Promise<void> {
  try {
    const value = await promise;
    results.push({ name, pass: false, expected: `BridgeCallError(${status})`, actual: `resolved ${value}` });
  } catch (error) {
    const actual = error instanceof BridgeCallError ? error.status : `non-bridge: ${String(error)}`;
    results.push({
      name,
      pass: actual === status,
      expected: `BridgeCallError(${status})`,
      actual: String(actual),
    });
  }
}

function render(done: boolean, error?: string): void {
  const all = results.every((r) => r.pass) && !error;
  const root = document.getElementById("results");
  if (root) {
    root.innerHTML =
      `<h1 data-status="${done ? (all ? "pass" : "fail") : "running"}">` +
      `rom-runtime bridge self-test: ${done ? (all ? "PASS" : "FAIL") : "running"}</h1>` +
      (error ? `<p class="error">${error}</p>` : "") +
      `<table><tr><th>check</th><th>expected</th><th>actual</th><th></th></tr>` +
      results
        .map(
          (r) =>
            `<tr class="${r.pass ? "pass" : "fail"}"><td>${r.name}</td><td>${r.expected}</td>` +
            `<td>${r.actual}</td><td>${r.pass ? "PASS" : "FAIL"}</td></tr>`,
        )
        .join("") +
      `</table>`;
  }
  (window as unknown as Record<string, unknown>)["__gfRomRuntimeSelfTest"] = {
    done,
    pass: done && all,
    error: error ?? null,
    results,
    crossOriginIsolated: window.crossOriginIsolated,
  };
}

async function main(): Promise<void> {
  render(false);
  if (!window.crossOriginIsolated) {
    throw new Error("crossOriginIsolated is false — the runtime requires the COI setup (H1)");
  }

  const wasmResponse = await fetch("./bridge_selftest.threads.wasm");
  if (!wasmResponse.ok) throw new Error(`fixture fetch failed: ${wasmResponse.status}`);
  const wasmBytes = await wasmResponse.arrayBuffer();

  const worker = new Worker(new URL("./rom-runtime-worker.js", import.meta.url), { type: "module" });
  // admitSyntheticAdapters: this harness's whole point is exercising the bridge
  // mechanism against a synthetic fixture module at made-up test addresses. Its
  // adapters are declared "synthetic" and say nothing about the ROM; only the
  // two damage adapters registered below are evidence-backed.
  const host = await RomRuntimeHost.start(worker, wasmBytes, {
    nestingCap: 4,
    admitSyntheticAdapters: true,
  });
  exposeBridgeLedger(host);

  // --- adapter registrations (the main-thread service registry) --------------
  // Synthetic adapters keyed by test addresses; REAL scaffold-backed damage
  // adapters keyed by their true GC addresses (their pointer args land in the
  // fixture's synthetic arena, which is exactly why they are addr-agnostic).
  host.registerAdapter(
    defineAdapter({
      gcAddr: 0xd0000001,
      name: "rt_double",
      evidence: "self-test synthetic",
      evidenceClass: "synthetic",
      retClass: FrameValueClass.I32,
      service(ctx) {
        ctx.mem.writeI32(0x104000, 7); // side effect into GC memory
        return ctx.frame.setRetI32(ctx.frame.i32Arg(0) * 2);
      },
    }),
  );
  host.registerAdapter(
    defineAdapter({
      gcAddr: 0xd0000002,
      name: "rt_reentrant",
      evidence: "self-test synthetic (I2 reentrant pilot case)",
      evidenceClass: "synthetic",
      retClass: FrameValueClass.I32,
      service(ctx) {
        // The deadlock I2 exists to prevent: this runs ON the main thread
        // while the worker is parked in this very call's Atomics.wait — the
        // invoke goes through the dispatch loop, onto the worker's own stack.
        const sum = ctx.invoke("reentry_target", [ctx.frame.i32Arg(0), ctx.frame.i32Arg(1)]);
        return ctx.frame.setRetI32(sum + 1000);
      },
    }),
  );
  host.registerAdapter(
    defineAdapter({
      gcAddr: 0xd0000003,
      name: "rt_overflow",
      evidence: "self-test synthetic (nesting-cap probe)",
      evidenceClass: "synthetic",
      retClass: FrameValueClass.I32,
      service(ctx) {
        return ctx.frame.setRetI32(ctx.invoke("overflow_probe", [ctx.frame.i32Arg(0)]));
      },
    }),
  );
  host.registerAdapter(
    defineAdapter({
      gcAddr: 0xd0000004,
      name: "rt_async",
      evidence: "self-test synthetic (async-servicing violation)",
      evidenceClass: "synthetic",
      retClass: FrameValueClass.I32,
      // Deliberate violation: bridged callees must be synchronous.
      service: (() => Promise.resolve(1)) as unknown as (ctx: BridgedCallContext) => number,
    }),
  );
  const traceAdapter = new TraceDeltaAdapter({
    gcAddr: 0xd0000005,
    name: "rt_tracedelta",
    evidence: "self-test synthetic capture (hand-authored, spine-synth style)",
    evidenceClass: "synthetic",
    calls: [
      { writes: [{ addr: 0x104010, bytes: [5, 0, 0, 0] }], ret: { class: "i32", value: 11 } },
      { writes: [{ addr: 0x104010, bytes: [9, 0, 0, 0] }], ret: { class: "i32", value: 22 } },
    ],
  });
  host.registerAdapter(traceAdapter);
  host.registerAdapter(
    defineAdapter({
      gcAddr: 0xd0000006,
      name: "rt_i64",
      evidence: "self-test synthetic (PPC r3 high-word rule, companion review)",
      evidenceClass: "synthetic",
      retClass: FrameValueClass.I64,
      service(ctx) {
        return ctx.frame.setRetI64(0x0000_0007_0000_002an);
      },
    }),
  );
  host.registerAdapter(
    defineAdapter({
      gcAddr: 0xd0000007,
      name: "rt_retclass",
      evidence: "self-test synthetic (ret_class mismatch signal)",
      evidenceClass: "synthetic",
      retClass: FrameValueClass.I32, // declared I32 ...
      service(ctx) {
        return ctx.frame.setRetVoid(); // ... but marshals VOID
      },
    }),
  );
  host.registerAdapter(createApplyHpDamageAdapter());
  host.registerAdapter(createLookupTypeCategoryAdapter());

  // --- proof 1a: round trip through a main-thread adapter --------------------
  check("roundtrip(21) == 42+42+7", await host.invokeExport("selftest_roundtrip", [21]), 91);

  // --- proof 3: reentrant case (I2 gate) -------------------------------------
  host.nextFrame();
  check("reentrant(5,7) == 5+7+1000", await host.invokeExport("selftest_reentrant", [5, 7]), 1012);

  // --- proof 4: nesting overflow is a declared, ledgered error ---------------
  host.nextFrame();
  await expectBridgeError(
    "overflow_probe rejects with NESTING_OVERFLOW",
    host.invokeExport("overflow_probe", [0]),
    BridgeStatus.NESTING_OVERFLOW,
  );

  // --- async-servicing violation is declared and ledgered --------------------
  host.nextFrame();
  await expectBridgeError(
    "async adapter rejects with ASYNC_SERVICING",
    host.invokeExport("selftest_async", []),
    BridgeStatus.ASYNC_SERVICING,
  );

  // --- proof 1b: trace-delta adapter (the V5-verdict mechanism) --------------
  host.nextFrame();
  check("tracedelta == 11+22+5+9", await host.invokeExport("selftest_tracedelta", []), 47);
  check("tracedelta cursor consumed", traceAdapter.cursor, 2);

  // --- proof 1c: REAL scaffold-backed adapters (damage path) -----------------
  host.nextFrame();
  check(
    "apply_hp(150,200,60) -> prev=150, clamped=90",
    await host.invokeExport("selftest_apply_hp", [150, 200, 60]),
    (150 << 16) | 90,
  );
  check("apply_hp(0,...) is a no-op (ROM HP==0 guard)", await host.invokeExport("selftest_apply_hp", [0, 200, 60]), 0);
  check("apply_hp heal clamps at maxHp", await host.invokeExport("selftest_apply_hp", [150, 200, -100]), (150 << 16) | 200);
  const expectedCat = lookupTypeCategory(0x0b00);
  check(`lookup_type(0x0b,0x00) == scaffold (${expectedCat})`, await host.invokeExport("selftest_lookup_type", [0x0b, 0x00]), expectedCat);
  const expectedCat2 = lookupTypeCategory(0x0701);
  check(`lookup_type(0x07,0x01) == scaffold (${expectedCat2})`, await host.invokeExport("selftest_lookup_type", [0x07, 0x01]), expectedCat2);

  // --- companion-review rules -------------------------------------------------
  host.nextFrame();
  check("i64 return: r3 is the HIGH word of the ret slot", await host.invokeExport("selftest_i64ret", []), 1);
  check("ret_class mismatch call still succeeds (result 0)", await host.invokeExport("selftest_retclass", []), 0);
  await expectBridgeError(
    "unserviced hit rejects with NO_ADAPTER",
    host.invokeExport("selftest_noadapter", []),
    BridgeStatus.NO_ADAPTER,
  );

  // --- proof 2: ledger structure ---------------------------------------------
  const ledger = host.ledger.snapshot();
  const frame0 = ledger.frames[0];
  check("ledger frame 0 has the roundtrip call", frame0?.calls.some((c) => c.gcAddr === "d0000001" && c.count === 1) ?? false, true);
  check("ledger frame 0 is a dtm-replay frame (R2)", frame0?.mode, "dtm-replay");
  const reentrantFrame = ledger.frames[1];
  check("reentrant frame ledgered", reentrantFrame?.calls.some((c) => c.gcAddr === "d0000002") ?? false, true);
  const overflowErrors = ledger.frames.flatMap((f) => f.errors).filter((e) => e.status === "nesting_overflow");
  check("nesting overflow surfaced in ledger", overflowErrors.length, 1);
  const asyncErrors = ledger.frames.flatMap((f) => f.errors).filter((e) => e.status === "async_servicing");
  check("async servicing violation surfaced in ledger", asyncErrors.length, 1);
  const mismatchErrors = ledger.frames.flatMap((f) => f.errors).filter((e) => e.status === "ret_class_mismatch");
  check("ret_class mismatch surfaced in ledger", mismatchErrors.length, 1);
  const noAdapterErrors = ledger.frames.flatMap((f) => f.errors).filter((e) => e.status === "no_adapter");
  check("no_adapter hit surfaced in ledger", noAdapterErrors.length, 1);
  const damageAddrs = new Set(ledger.totals.byAddr.map((r) => r.gcAddr));
  check("real damage adapters ledgered at their GC addresses", damageAddrs.has("8003d344") && damageAddrs.has("80066298"), true);
  check("window.__gf.bridgeLedger() exposed", typeof (window as unknown as { __gf?: { bridgeLedger?: unknown } }).__gf?.bridgeLedger, "function");

  render(true);
  await host.shutdown();
}

main().catch((error: unknown) => {
  render(true, error instanceof Error ? `${error.message}\n${error.stack ?? ""}` : String(error));
});
