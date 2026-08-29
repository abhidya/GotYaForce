// =============================================================================
// composedBoot.ts — boot the composed ROM module into the live game.
//
// Same shape as sim/romDamageBoot.ts (fetch → gate → install → expose, never
// throw into the game), one level up in ambition: instead of installing a
// single verified function behind a seam, this starts the @gf/rom-runtime
// worker on a REAL assembly-gate module — rung 0 of the composition ladder,
// relinked threads-target — installs the DOL arena at original GC addresses,
// binds every out-of-window callee to the H2 bridge, and drives the
// COMPOSED-MODULE DISPATCH PILOT from the game's own frame loop.
//
// The pilot's exact scope (and the gap to control inversion) is stated in
// composedPilot.ts and docs/composed-pilot.md. In one line: the host calls
// into the module once per rendered frame and every out-of-window call routes
// through the bridge — the ROM's own main loop is NOT driving, because it is
// not in the window.
//
// OFF by default: the module reserves a 2GB shared WebAssembly.Memory and
// blocks a worker thread in Atomics.wait forever, neither of which belongs in
// an ordinary play session. `?composed=1` boots it with the default frame
// budget; `?composed=<n>` drives n frames.
// =============================================================================

import {
  RomRuntimeHost,
  TRAMPOLINE_FRAME_SLOTS,
  exposeBridgeLedger,
  scratchByteLength,
  trampolineFrameBase,
  FRAME_SIZE,
  SCRATCH_BASE,
} from "@gf/rom-runtime";
import { publicUrl } from "../publicUrl";
import {
  PILOT_ACTOR_ADDR,
  PILOT_REGION_BYTES,
  assertPilotFixture,
  assertRegionClear,
  createPilotAdapters,
  drivePilotFrame,
  type PilotFixture,
  type PilotFrameResult,
  type PilotState,
} from "./composedPilot";

/**
 * What this pilot is allowed to claim, stated once and repeated everywhere it
 * reports. Its adapters are synthetic stand-ins, its fixture is hand-declared,
 * and the threads relink suspends every rung-0 unit's verification — so no
 * number this pilot produces is evidence about the ROM's behaviour.
 */
const NO_BEHAVIOURAL_CLAIM =
  "NONE. Synthetic hand-written adapters + a hand-declared fixture, driving units whose " +
  "oracle/boundary verification is SUSPENDED by the threads relink (docs/threads-relink-" +
  "reverify.md). These numbers prove the dispatch/bridge MECHANISM works; they prove nothing " +
  "about what these five units compute. See docs/composed-pilot.md.";

const COMPOSED_WASM_PATH = "/rom/composed-rung0.threads.wasm";
const COMPOSED_PROVENANCE_PATH = "/rom/composed-rung0.provenance.json";
const COMPOSED_FIXTURE_PATH = "/rom/composed-rung0.pilot-fixture.json";
const ARENA_PATH = "/rom/arena.json";

/** Default frames the pilot drives before parking. Small on purpose: the
 *  trace-delta fixture has one recorded call per frame, and running past the
 *  record is a declared servicing error, exactly as it should be. */
export const DEFAULT_PILOT_FRAMES = 8;

interface ArenaFile {
  segments: Array<{ addr: number; b64: string; note?: string }>;
}

interface ProvenanceFile {
  artifact: string;
  ladder: { rung: number; n: number; units: string[]; checked_at: string };
  companion: {
    table_size: number;
    companion_sha256: string;
    dispatch_export: string;
    miss_import: string;
    arity_export: string;
    frame_abi_version: number;
  };
  memory: { initial_pages: number; bytes: number };
  link: { threads_sha256: string; verification_status: string };
}

export interface ComposedBootResult {
  active: boolean;
  detail: string;
  host?: RomRuntimeHost;
}

function decodeBase64(b64: string): Uint8Array {
  const binary = atob(b64);
  const bytes = new Uint8Array(binary.length);
  for (let i = 0; i < binary.length; i++) bytes[i] = binary.charCodeAt(i);
  return bytes;
}

/** State the pilot controls hang off, exposed on window.__gf. */
interface ComposedRuntimeHandle {
  host: RomRuntimeHost;
  provenance: ProvenanceFile;
  pilotState: PilotState;
  fixture: PilotFixture;
  budget: number;
  results: PilotFrameResult[];
  busy: boolean;
  finished: boolean;
  errors: string[];
}

let handle: ComposedRuntimeHandle | null = null;

/**
 * Fetch the composed module + arena + fixture, start the worker, install the
 * arena, register the pilot adapters, and expose the controls. Never throws:
 * any failure leaves the game exactly as it was, with the reason logged.
 */
export async function bootComposedModule(frames = DEFAULT_PILOT_FRAMES): Promise<ComposedBootResult> {
  try {
    if (!globalThis.crossOriginIsolated) {
      return {
        active: false,
        detail:
          "not cross-origin isolated — the composed module needs a shared WebAssembly.Memory (design H1)",
      };
    }
    const [wasmRes, arenaRes, provRes, fixtureRes] = await Promise.all([
      fetch(publicUrl(COMPOSED_WASM_PATH)),
      fetch(publicUrl(ARENA_PATH)),
      fetch(publicUrl(COMPOSED_PROVENANCE_PATH)),
      fetch(publicUrl(COMPOSED_FIXTURE_PATH)),
    ]);
    if (!wasmRes.ok || !arenaRes.ok || !provRes.ok || !fixtureRes.ok) {
      return {
        active: false,
        detail: `composed assets unavailable (${wasmRes.status}/${arenaRes.status}/${provRes.status}/${fixtureRes.status})`,
      };
    }
    const wasmBytes = await wasmRes.arrayBuffer();
    const arena = (await arenaRes.json()) as ArenaFile;
    const provenance = (await provRes.json()) as ProvenanceFile;
    const fixture = (await fixtureRes.json()) as PilotFixture;
    assertPilotFixture(fixture);

    const worker = new Worker(new URL("./composedWorker.ts", import.meta.url), {
      type: "module",
      name: "gf-composed-rom",
    });

    const started = performance.now();
    const host = await RomRuntimeHost.start(worker, wasmBytes, {
      arena: arena.segments.map((segment) => ({ addr: segment.addr, bytes: decodeBase64(segment.b64) })),
      // H2's direct-call edge: every unlinked callee the module names becomes a
      // bridge crossing rather than an unshimmed-import failure.
      bridgeAllImports: true,
      trampolineFrameBase: trampolineFrameBase(FRAME_SIZE),
      trampolineFrameSlots: TRAMPOLINE_FRAME_SLOTS,
      // DECLARED pilot work: this host is deliberately opened to the synthetic
      // stand-in adapters in composedPilot.ts. No other host in the app sets
      // this, so a stub cannot service a frame anywhere else — the registry
      // throws instead (packages/rom-runtime AdapterRegistry).
      admitSyntheticAdapters: true,
    });
    const instantiateMs = Math.round(performance.now() - started);

    // The dispatch-frame scratch and the pilot's synthetic actor both live in
    // regions this code ASSUMES are unused. Prove it rather than assume it.
    assertRegionClear(host, SCRATCH_BASE, scratchByteLength(FRAME_SIZE), "dispatch-frame scratch");
    assertRegionClear(host, PILOT_ACTOR_ADDR, PILOT_REGION_BYTES, "pilot GC scratch");

    if (!host.exportNames.includes(provenance.companion.dispatch_export)) {
      await host.shutdown();
      return { active: false, detail: `composed module does not export ${provenance.companion.dispatch_export}` };
    }

    const pilotState: PilotState = { lastReentrantResult: Number.NaN };
    createPilotAdapters(host, fixture, pilotState);
    exposeBridgeLedger(host);

    handle = {
      host,
      provenance,
      pilotState,
      fixture,
      budget: Math.max(0, frames),
      results: [],
      busy: false,
      finished: false,
      errors: [],
    };
    exposeComposedControls();

    // Runtime provenance, published where a human and a script both trip over
    // it, not only in a console line that scrolls away.
    const root = globalThis.document?.documentElement;
    if (root) root.dataset["gfComposedPilot"] = "synthetic-no-behavioural-claim";

    const t = host.bootTimings;
    console.info(
      `[composed-rom] rung ${provenance.ladder.rung} (${provenance.ladder.n} units, ${provenance.companion.table_size}-thunk table) ` +
        `LIVE: ${provenance.memory.initial_pages} shared pages = ${provenance.memory.bytes} B booted in ${instantiateMs} ms ` +
        `(worker: memory ${t.memoryMs} ms, compile ${t.compileMs} ms, instantiate ${t.instantiateMs} ms, arena ${t.arenaMs} ms); ` +
        `${host.bridgedImports.length} out-of-window symbols bound to the bridge. ` +
        `Pilot budget ${handle.budget} frames. NOTE: ${provenance.link.verification_status}`,
    );
    console.warn(`[composed-rom] BEHAVIOURAL CLAIM: ${NO_BEHAVIOURAL_CLAIM}`);
    return { active: true, detail: `rung0 live (${instantiateMs} ms, ${host.bridgedImports.length} bridged imports)`, host };
  } catch (error) {
    console.error("[composed-rom] boot failed — the game is unaffected:", error);
    return { active: false, detail: String(error) };
  }
}

/**
 * Called once per rendered game frame. Non-blocking: it starts at most one
 * pilot frame at a time and returns immediately, so the render loop never
 * waits on the worker.
 */
export function onGameFrame(): void {
  const h = handle;
  if (!h || h.busy || h.finished || h.results.length >= h.budget) {
    if (h && !h.finished && h.results.length >= h.budget) h.finished = true;
    return;
  }
  h.busy = true;
  // TraceDeltaAdapter runs in LOCKSTEP: the k-th driven frame consumes the
  // k-th recorded call, so the byte the pilot expects to find comes from that
  // record — a wrong cursor shows up as a state mismatch, not as a silent pass.
  const record = h.fixture.calls[h.results.length]?.writes[0];
  void drivePilotFrame(h.host, h.pilotState, record?.addr ?? 0, record?.bytes[0] ?? 0)
    .then((result) => {
      h.results.push(result);
      if (!result.declaredChecksPass) {
        console.error(`[composed-rom] pilot frame ${result.frame} FAILED`, result.state.filter((c) => !c.pass));
      }
      if (h.results.length >= h.budget) {
        h.finished = true;
        const passed = h.results.filter((r) => r.declaredChecksPass).length;
        console.info(
          `[composed-rom] dispatch pilot done: ${passed}/${h.results.length} frames pass, ` +
            `${h.host.ledger.snapshot().totals.bridgedCalls} bridged crossings recorded ` +
            `(window.__gf.bridgeLedger()).`,
        );
      }
    })
    .catch((error: unknown) => {
      h.errors.push(String(error));
      h.finished = true;
      console.error("[composed-rom] pilot frame threw:", error);
    })
    .finally(() => {
      h.busy = false;
    });
}

/** Extend the pilot's frame budget (the manual control surface). */
export function runComposedFrames(count: number): number {
  if (!handle) return 0;
  handle.budget += Math.max(0, Math.floor(count));
  handle.finished = false;
  return handle.budget;
}

function exposeComposedControls(): void {
  const w = globalThis as unknown as { __gf?: Record<string, unknown> };
  w.__gf = w.__gf ?? {};
  w.__gf["composedPilot"] = () => {
    const h = handle;
    if (!h) return null;
    return {
      gate: "composed-module dispatch pilot",
      // First two fields on purpose: anything reading this object sees what it
      // is NOT allowed to conclude before it sees a single number.
      behaviouralClaim: NO_BEHAVIOURAL_CLAIM,
      verified: false,
      scope:
        "host-driven dispatch into the composed module from the game frame loop; " +
        "NOT control inversion (run_main_game_loop is not in the window)",
      adapters: h.host.adapters.list(),
      module: {
        artifact: h.provenance.artifact,
        sha256: h.provenance.link.threads_sha256,
        rung: h.provenance.ladder.rung,
        units: h.provenance.ladder.units,
        tableSize: h.provenance.companion.table_size,
        frameAbiVersion: h.provenance.companion.frame_abi_version,
        sharedMemoryBytes: h.provenance.memory.bytes,
        verificationStatus: h.provenance.link.verification_status,
      },
      bootTimings: h.host.bootTimings,
      bridgedImports: h.host.bridgedImports.length,
      budget: h.budget,
      framesDriven: h.results.length,
      finished: h.finished,
      frames: h.results,
      errors: h.errors,
      // NOT `pass`. This says the pilot's own DECLARED expectations held — a
      // mechanism check. `pass` invited exactly the misreading ("the composed
      // module passed") that this pilot can never support.
      declaredChecksPass:
        h.results.length > 0 && h.results.every((r) => r.declaredChecksPass) && h.errors.length === 0,
    };
  };
  w.__gf["composedRun"] = (count: number) => runComposedFrames(count);
  w.__gf["composedShutdown"] = async () => {
    const h = handle;
    handle = null;
    if (h) await h.host.shutdown();
  };
}
