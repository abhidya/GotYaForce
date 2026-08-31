// =============================================================================
// gxSelftestMain.ts — end-to-end proof for the GX half of the HLE host.
//
// Boots the purpose-built ROM-side draw module
// (test/fixtures/gx-selftest/gx_selftest.threads.wasm) on the real
// composed-module runtime — worker-owned shared memory, Atomics RPC bridge,
// signature-accurate import trampolines — so that the module's GX calls cross
// the H2 bridge exactly as a composed ROM module's would, land in the GX
// adapters, decode through the write-gather-pipe decoder, and rasterize to a
// real WebGL2 framebuffer that this page then reads back with readPixels.
//
// TWO LEGS, and the second one is not a fixture:
//   A. test/fixtures/gx-selftest/ — hand-written ROM-SHAPED call sequences.
//   B. test/fixtures/gx-rom-unit/ — the ASSEMBLY GATE'S OWN OUTPUT for the
//      ROM's own draw function zz_0027c34_, gets its own worker and its own
//      0x807A0000-byte shared memory, and renders into the same backend.
//
// WHAT THIS PROVES
//   1. ROM-shaped GX call sequences reach the adapters through the real bridge
//      and are recorded in the bridged-call ledger at their GX keys.
//   2. The write-gather-pipe decoder assembles the ROM's own vertex layouts —
//      S16 XY + RGBA8 direct, F32 XYZ + RGBA8 direct, and INDEX8 through
//      GXSetArray — into the right primitives.
//   3. Those primitives rasterize: the framebuffer contains the expected
//      colours at the expected pixels.
//   4. An UNIMPLEMENTED GX entry point fails LOUDLY (a declared servicing
//      error in the ledger), instead of no-opping into a wrong frame.
//   5. The TEV combiner produces PREDICTED pixels: a konst-only stage, a
//      two-stage chain through GX_TEVREG0, and an alpha test that DISCARDS.
//      Each one sets the vertex colour to something OTHER than the expected
//      output, so a combiner that fell back to passing the rasterized colour
//      through fails rather than passing by accident.
//   6. A GameCube texture format is decoded out of the arena at the address
//      GXInitTexObj was given, de-tiled, uploaded and sampled.
//   7. Per-vertex lighting is evaluated.
//   8. The ROM's OWN four-stage TEV program latches, argument for argument.
//   9. Gate-lowered REAL ROM CODE drives the whole path to pixels.
//
// WHAT THIS DOES NOT PROVE — stated here because a green page invites the
// opposite reading: nothing about whether these frames match the GameCube.
// Every adapter is a synthetic stand-in, and no output has ever been compared
// against a captured frame. The predicted pixels above were predicted from the
// SAME understanding of GX that produced the implementation, so they are
// self-consistency checks and cannot detect a shared misunderstanding. See
// docs/gx-hle-host.md §6.3.
// =============================================================================

import {
  GxHost,
  GX_NO_BEHAVIOURAL_CLAIM,
  registerGxAdapters,
  registerPsmtxIdentityAdapter,
  registerWgPipeAdapters,
} from "../adapters.js";
import { GxWebglBackend } from "../webgl.js";
import { GXProjectionType } from "../enums.js";
import { RomRuntimeHost, exposeBridgeLedger } from "../../host.js";
import { BridgeCallError, BridgeStatus } from "../../protocol.js";

/** Canvas size: the ROM's own frame extent (zz_0027c34_ draws 0x280 x 0x1c0). */
const WIDTH = 640;
const HEIGHT = 448;

/** Trampoline dispatch frames, placed inside the 16MB fixture memory well
 *  clear of emscripten's static data and stack. */
const TRAMPOLINE_BASE = 0x600000;
const TRAMPOLINE_SLOTS = 32;

/** The gate-lowered ROM unit gets its own 0x807A0000-byte memory, so its
 *  dispatch frames go somewhere the ROM's own arena addresses never reach.
 *  0x80520000 is above the scratch this page pokes and below 0x803c0f40. */
const ROM_UNIT_TRAMPOLINE_BASE = 0x80520000;

/** The colour the page plants where the ROM function reads its own. */
const ROM_QUAD_RGBA = 0x8090a0b0;

const QUAD_RGBA = 0x203050ff; // opaque dark blue, fullscreen
const STRIP_RGBA = 0x30c060ff; // opaque green, centre
const LINE_RGBA = 0xffd040ff; // opaque amber, outline

interface CheckResult {
  name: string;
  pass: boolean;
  expected: string;
  actual: string;
}

const results: CheckResult[] = [];

/** Framebuffer captures kept for the smoke phase's evidence directory: the
 *  fixture frame before the ROM unit redraws over it, and the ROM frame. */
let fixtureFramebufferPng: string | null = null;
let romFramebufferPng: string | null = null;

function check(name: string, actual: unknown, expected: unknown): void {
  const pass = Object.is(actual, expected) || JSON.stringify(actual) === JSON.stringify(expected);
  results.push({ name, pass, expected: String(expected), actual: String(actual) });
}

function checkNear(name: string, actual: number, expected: number, tolerance: number): void {
  const pass = Math.abs(actual - expected) <= tolerance;
  results.push({ name, pass, expected: `${expected} +/-${tolerance}`, actual: String(actual) });
}

function render(done: boolean, report: unknown, error?: string): void {
  const all = results.every((r) => r.pass) && !error;
  const root = document.getElementById("results");
  if (root) {
    root.innerHTML =
      `<h1 data-status="${done ? (all ? "pass" : "fail") : "running"}">` +
      `GX HLE host self-test: ${done ? (all ? "PASS" : "FAIL") : "running"}</h1>` +
      `<p class="claim"><strong>BEHAVIOURAL CLAIM:</strong> ${GX_NO_BEHAVIOURAL_CLAIM}</p>` +
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
  (window as unknown as Record<string, unknown>)["__gfGxSelfTest"] = {
    done,
    pass: done && all,
    // Repeated in the machine-readable payload too: a smoke script reading
    // `pass` must trip over what `pass` does not mean.
    behaviouralClaim: GX_NO_BEHAVIOURAL_CLAIM,
    verified: false,
    error: error ?? null,
    results,
    report,
    fixtureFramebufferPng,
    romFramebufferPng,
    crossOriginIsolated: window.crossOriginIsolated,
  };
}

/** Read one pixel in GL framebuffer coordinates (origin bottom-left). */
function readPixel(gl: WebGL2RenderingContext, x: number, y: number): [number, number, number, number] {
  const px = new Uint8Array(4);
  gl.readPixels(x, y, 1, 1, gl.RGBA, gl.UNSIGNED_BYTE, px);
  return [px[0] as number, px[1] as number, px[2] as number, px[3] as number];
}

async function main(): Promise<void> {
  render(false, null);
  if (!window.crossOriginIsolated) {
    throw new Error("crossOriginIsolated is false — the runtime requires the COI setup (design H1)");
  }

  // --- the browser standing in for the Flipper ------------------------------
  const canvas = document.getElementById("gx-canvas") as HTMLCanvasElement | null;
  if (!canvas) throw new Error("gx-canvas element missing from the page");
  canvas.width = WIDTH;
  canvas.height = HEIGHT;
  const gl = canvas.getContext("webgl2", {
    // Required: the page reads the framebuffer back AFTER the draws, and the
    // headless screenshot is taken later still.
    preserveDrawingBuffer: true,
    antialias: false,
    alpha: false,
  });
  if (!gl) throw new Error("WebGL2 unavailable — the GX host has no rasterizer to prove");

  // The backend needs the arena: texture image data lives at GC addresses and
  // has to be read back out of it. The memory is attached after the host
  // starts, because the WORKER owns it (design H1).
  let backend!: GxWebglBackend;

  // --- the composed-module runtime ------------------------------------------
  const wasmResponse = await fetch("./gx_selftest.threads.wasm");
  if (!wasmResponse.ok) throw new Error(`GX fixture fetch failed: ${wasmResponse.status}`);
  const wasmBytes = await wasmResponse.arrayBuffer();

  const worker = new Worker(new URL("./rom-runtime-worker.js", import.meta.url), { type: "module" });
  // admitSyntheticAdapters: EVERY GX adapter is a synthetic stand-in (see
  // gx/adapters.ts). The registry refuses them by default precisely so this
  // has to be asked for explicitly, and asking for it is the declaration that
  // nothing here carries a behavioural claim.
  const host = await RomRuntimeHost.start(worker, wasmBytes, {
    admitSyntheticAdapters: true,
    // H2's direct-call edge: the fixture's GX imports are ordinary named
    // function imports with true C signatures, bound through per-import
    // trampolines — exactly how a composed module's SDK calls will arrive.
    bridgeAllImports: true,
    trampolineFrameBase: TRAMPOLINE_BASE,
    trampolineFrameSlots: TRAMPOLINE_SLOTS,
  });
  exposeBridgeLedger(host);
  backend = new GxWebglBackend(gl, host.memory);

  const gx = new GxHost(backend, host.memory);
  const registration = registerGxAdapters(host, gx);
  registerWgPipeAdapters(host, gx);

  check("every measured GX entry point has an adapter", registration.implemented + registration.unimplemented, 76);
  check(
    "the fixture's GX imports are all bound to the bridge",
    host.bridgedImports.filter((b) => b.symbol.startsWith("gnt4_GX")).length,
    41,
  );

  // --- one host-driven frame -------------------------------------------------
  gx.beginFrame();
  host.nextFrame();

  // 1. zz_0027c34_'s screen-space quad, full extent.
  await host.invokeExport("gx_draw_fullscreen_quad", [QUAD_RGBA | 0, 0, 0, WIDTH, HEIGHT]);
  // 2. zz_0050f80_'s F32 triangle strip, centre region.
  await host.invokeExport("gx_draw_strip", [STRIP_RGBA | 0, 160, 112, 480, 336]);
  // 3. zz_0050bf4_'s INDEX8 line primitive through GXSetArray.
  await host.invokeExport("gx_draw_indexed", [LINE_RGBA | 0, 40, 40, 600, 408]);

  gx.endFrame();

  // --- proof 2: the FIFO decoded the ROM's own vertex layouts ---------------
  const records = backend.recorder.records;
  check("three primitives assembled", records.length, 3);
  check("primitive 0 is GX_QUADS", records[0]?.primitive, "QUADS");
  check("primitive 0 has 4 vertices", records[0]?.vertexCount, 4);
  check("primitive 0 first vertex is the S16 (0,0) corner", records[0]?.firstVertex, [0, 0, 0]);
  check("primitive 0 first colour is the RGBA8 the ROM wrote", records[0]?.firstColor, [0x20, 0x30, 0x50, 0xff]);
  check("primitive 0 used the orthographic projection", records[0]?.projectionType, GXProjectionType.ORTHOGRAPHIC);
  check("primitive 1 is GX_TRIANGLESTRIP", records[1]?.primitive, "TRIANGLESTRIP");
  check("primitive 1 first vertex is the F32 (160,112,0)", records[1]?.firstVertex, [160, 112, 0]);
  check("primitive 2 is the 0xb0 line primitive", records[2]?.primitive, "LINESTRIP");
  check("primitive 2 resolved its INDEX8 positions from GXSetArray", records[2]?.firstVertex, [40, 40, 0]);
  check("primitive 2 resolved its INDEX8 colours", records[2]?.firstColor, [0xff, 0xd0, 0x40, 0xff]);
  // Nonzero means the host and the ROM disagree about the vertex layout — the
  // failure mode a byte-stream decoder exists to make visible.
  check("the FIFO consumed every byte the ROM wrote", gx.fifo.droppedBytes, 0);
  check("no vertex bytes left buffered between primitives", gx.fifo.pendingBytes, 0);

  // --- proof 3: it actually rasterized --------------------------------------
  const centre = readPixel(gl, WIDTH / 2, HEIGHT / 2);
  const corner = readPixel(gl, 12, 12);
  checkNear("centre pixel R == strip green R", centre[0], 0x30, 2);
  checkNear("centre pixel G == strip green G", centre[1], 0xc0, 2);
  checkNear("centre pixel B == strip green B", centre[2], 0x60, 2);
  checkNear("corner pixel R == fullscreen quad R", corner[0], 0x20, 2);
  checkNear("corner pixel G == fullscreen quad G", corner[1], 0x30, 2);
  checkNear("corner pixel B == fullscreen quad B", corner[2], 0x50, 2);

  // --- projection: the perspective branch of the coefficient packing --------
  await host.invokeExport("gx_set_perspective", []);
  check("GXSetProjection type 0 latched as perspective", gx.state.projection[0], GXProjectionType.PERSPECTIVE);
  checkNear("perspective coefficient m[2][2] latched", gx.state.projection[5] ?? 0, -1.010101, 1e-4);
  checkNear("perspective coefficient m[2][3] latched", gx.state.projection[6] ?? 0, -2.020202, 1e-4);

  // --- proof 4: an unimplemented entry point is LOUD ------------------------
  host.nextFrame();
  let unimplementedStatus: unknown = "resolved without error";
  try {
    await host.invokeExport("gx_call_unimplemented", []);
  } catch (error) {
    unimplementedStatus = error instanceof BridgeCallError ? error.status : `non-bridge: ${String(error)}`;
  }
  check("unimplemented GXSetFog rejects with ADAPTER_THREW", unimplementedStatus, BridgeStatus.ADAPTER_THREW);
  check("the unimplemented hit is named", gx.unimplementedHits, ["gnt4_GXSetFog_bl"]);

  const ledger = host.ledger.snapshot();
  const loudErrors = ledger.frames.flatMap((f) => f.errors).filter((e) => e.status === "adapter_threw");
  check("the loud failure is in the bridged-call ledger", loudErrors.length, 1);
  check(
    "the ledger error names the missing entry point",
    loudErrors[0]?.detail.includes("gnt4_GXSetFog_bl") ?? false,
    true,
  );

  // --- proof 1: ledger entries at the GX keys -------------------------------
  check("GX crossings recorded in the ledger", ledger.totals.bridgedCalls > 60, true);
  check("GXBegin was called three times", gx.callCounts.get("gnt4_GXBegin_bl"), 3);
  check("write-gather-pipe writes reached the decoder", (gx.callCounts.get("__gf_gx_wgpipe_u32") ?? 0) > 0, true);

  // --- the report the smoke phase and a human both read ---------------------
  // --- proof 5: the TEV combiner produces a PREDICTED pixel -----------------
  //
  // Each of these makes the vertex colour deliberately different from the
  // expected output, so a combiner that quietly fell back to passing the
  // rasterized colour through fails instead of passing by accident.
  const drawAndRead = async (
    exportName: string,
    args: number[],
    x: number,
    y: number,
  ): Promise<[number, number, number, number]> => {
    gx.beginFrame();
    host.nextFrame();
    await host.invokeExport(exportName, args);
    gx.endFrame();
    return readPixel(gl, x, y);
  };

  const KONST0: [number, number, number, number] = [0xc0, 0x40, 0x80, 0xff];
  const konstPixel = await drawAndRead("gx_draw_tev_konst", [0x10203040 | 0, ...KONST0], WIDTH / 2, HEIGHT / 2);
  checkNear("TEV konst-only stage: R is GX_KCOLOR0's R, not the vertex colour's", konstPixel[0], KONST0[0], 2);
  checkNear("TEV konst-only stage: G is GX_KCOLOR0's G", konstPixel[1], KONST0[1], 2);
  checkNear("TEV konst-only stage: B is GX_KCOLOR0's B", konstPixel[2], KONST0[2], 2);
  check("the konst pixel is NOT the vertex colour", konstPixel[0] === 0x10 && konstPixel[1] === 0x20, false);
  check("GXSetTevKColor crossed the bridge", (gx.callCounts.get("gnt4_GXSetTevKColor_bl") ?? 0) > 0, true);

  const KONST1: [number, number, number, number] = [0x20, 0xd0, 0x60, 0xff];
  const chainPixel = await drawAndRead("gx_draw_tev_two_stage", [0x10203040 | 0, ...KONST1], WIDTH / 2, HEIGHT / 2);
  checkNear("TEV stage 0 wrote GX_TEVREG0 and stage 1 read it back as GX_CC_C0 (R)", chainPixel[0], KONST1[0], 2);
  checkNear("...and G", chainPixel[1], KONST1[1], 2);
  checkNear("...and B", chainPixel[2], KONST1[2], 2);

  // GXSetAlphaCompare must DISCARD, not merely latch: the quad's alpha (0x40)
  // fails GX_GREATER against 0x80, so the cleared background must survive.
  const discardPixel = await drawAndRead("gx_draw_alpha_compare_discard", [0x40e0f040 | 0], WIDTH / 2, HEIGHT / 2);
  check("GXSetAlphaCompare discarded the failing fragment", [discardPixel[0], discardPixel[1], discardPixel[2]], [0, 0, 0]);

  // --- proof 6: a GameCube texture format is decoded and sampled ------------
  const TEXEL: [number, number, number, number] = [0x30, 0x90, 0xe0, 0xff];
  const texPixel = await drawAndRead("gx_draw_textured", [...TEXEL], WIDTH / 2, HEIGHT / 2);
  checkNear("GX_TF_RGBA8 texel R decoded out of the arena and sampled", texPixel[0], TEXEL[0], 2);
  checkNear("GX_TF_RGBA8 texel G (second 32-byte half of the block)", texPixel[1], TEXEL[1], 2);
  checkNear("GX_TF_RGBA8 texel B (second 32-byte half of the block)", texPixel[2], TEXEL[2], 2);
  check("a texture was actually decoded and uploaded", backend.summary().textures > 0, true);
  check("GXSetTexCoordGen2 crossed the bridge", (gx.callCounts.get("gnt4_GXSetTexCoordGen2_bl") ?? 0) > 0, true);

  // --- proof 7: per-vertex lighting is evaluated ----------------------------
  const LIGHT: [number, number, number] = [0xe0, 0x50, 0x30];
  const litPixel = await drawAndRead("gx_draw_lit", [...LIGHT], WIDTH / 2, HEIGHT / 2);
  checkNear("lit channel R == the light's own R (white material, black ambient)", litPixel[0], LIGHT[0], 3);
  checkNear("lit channel G == the light's own G", litPixel[1], LIGHT[1], 3);
  checkNear("lit channel B == the light's own B", litPixel[2], LIGHT[2], 3);
  check("GXLoadLightObjImm crossed the bridge", (gx.callCounts.get("gnt4_GXLoadLightObjImm_bl") ?? 0) > 0, true);

  // --- proof 8: the ROM's OWN 4-stage program latches ------------------------
  host.nextFrame();
  await host.invokeExport("gx_program_rom_tev", [0, 1]);
  check("the ROM's 4-stage program set the stage count", gx.state.numTevStages, 4);
  check("stage 0's colour inputs are the ROM's own (a,b,c,d)", gx.state.tevStages[0]?.colorIn, [0xf, 8, 0xe, 2]);
  check("stage 0's alpha inputs mirror them", gx.state.tevStages[0]?.alphaIn, [7, 4, 6, 1]);
  check("stage 1 asked for GX_CS_SCALE_2", gx.state.tevStages[1]?.colorOp.scale, 1);
  check("stage 2 selects GX_TEV_KCSEL_K2", gx.state.tevStages[2]?.kColorSel, 0x0e);
  check("stage 2 selects GX_TEV_KASEL_K2_A", gx.state.tevStages[2]?.kAlphaSel, 0x1e);
  check("stage 2's texture swap row is 2", gx.state.tevStages[2]?.texSwap, 2);
  check("stage 3 takes no texture", gx.state.tevStages[3]?.texMap, 0xff);
  check("swap table row 1 is the ROM's (0,3,3,3)", gx.state.swapTable[1], [0, 3, 3, 3]);
  check("swap table row 2 is the ROM's (0,0,3,0)", gx.state.swapTable[2], [0, 0, 3, 0]);

  // GXEnableTexOffsets is a CONDITIONAL declared-nop: inert with the offsets
  // off (all 16 ROM call sites), loud if either is ever enabled.
  await host.invokeExport("gx_call_tex_offsets_disabled", []);
  check("GXEnableTexOffsets with offsets disabled is inert", gx.callCounts.get("gnt4_GXEnableTexOffsets_bl"), 8);

  // Keep the fixture's framebuffer as evidence before the ROM unit redraws it.
  fixtureFramebufferPng = canvas.toDataURL("image/png");

  const report = gx.report();
  const w = window as unknown as { __gf?: Record<string, unknown> };
  w.__gf = w.__gf ?? {};
  w.__gf["gxHost"] = () => report;
  check("coverage is computed from the measured inventory", report.coverage.all.totalSymbols, 76);

  await host.shutdown();

  // --- proof 9: a GATE-LOWERED REAL ROM UNIT drives the whole path ----------
  const romReport = await runGateLoweredRomUnit(gl, backend, canvas);

  render(true, { ...report, romUnit: romReport });
}

/**
 * Drive the assembly gate's own lowering of the ROM's own draw function.
 *
 * THIS IS THE PART THAT IS NOT A FIXTURE. Everything above runs
 * test/fixtures/gx-selftest/, which reproduces the ROM's draw paths but was
 * written by hand. `gx_rom_unit.threads.wasm` is the assembly gate's output for
 * `zz_0027c34_` (0x80027c34) — the verbatim Ghidra decompilation with exactly
 * one class of rewrite applied, each `DAT_cc008000 = ...` store to the
 * write-gather pipe turned into a `__gf_gx_wgpipe_*` import. See
 * test/fixtures/gx-rom-unit/build.sh for the provenance.
 *
 * It gets its own worker, its own 0x807A0000-byte shared memory (the gate's
 * production arena size — the shim maps GameCube addresses straight to linear
 * offsets, so this is not a tuning knob) and its own GxHost, but it renders
 * into the SAME WebGL backend, so the pixels it produces come out of the same
 * rasterizer the fixture proofs just exercised.
 */
async function runGateLoweredRomUnit(
  gl: WebGL2RenderingContext,
  backend: GxWebglBackend,
  canvas: HTMLCanvasElement,
): Promise<unknown> {
  const wasmResponse = await fetch("./gx_rom_unit.threads.wasm");
  if (!wasmResponse.ok) throw new Error(`gate-lowered ROM unit fetch failed: ${wasmResponse.status}`);
  const wasmBytes = await wasmResponse.arrayBuffer();

  const worker = new Worker(new URL("./rom-runtime-worker.js", import.meta.url), { type: "module" });
  const host = await RomRuntimeHost.start(worker, wasmBytes, {
    admitSyntheticAdapters: true,
    bridgeAllImports: true,
    trampolineFrameBase: ROM_UNIT_TRAMPOLINE_BASE,
    trampolineFrameSlots: TRAMPOLINE_SLOTS,
  });
  try {
    const gx = new GxHost(backend, host.memory);
    registerGxAdapters(host, gx);
    registerWgPipeAdapters(host, gx);
    // gnt4_PSMTXIdentity_bl is not a GX entry point — it is the SDK's matrix
    // library, which is equally out-of-window and equally host-provided. The
    // ROM function calls it to build the position matrix it then loads. The
    // adapter itself lives in ../adapters.ts so this page and the GX
    // call-stream oracle drive the SAME definition.
    registerPsmtxIdentityAdapter(host);

    // --- the arena state the ROM function reads -----------------------------
    // Every one of these is a GameCube address the gate's merged shim resolves
    // (test/fixtures/gx-rom-unit/gnt4_shim.h), and the composed module maps GC
    // addresses straight to linear-memory offsets, so they are pokeable here
    // exactly as the arena builder would poke them.
    const mem = host.memory;
    const GUARD_STRUCT = 0x80500000; // scratch: PTR_DAT_80433930 points here
    const COLOUR_SLOT = 0x80500100; // scratch: DAT_8043610c points here
    const PROJECTION = 0x803c0f40; // DAT_803c0f40, the Mtx44 it projects with
    mem.writeU32(0x80433930, GUARD_STRUCT); // the struct pointer it dereferences
    mem.writeU32(GUARD_STRUCT + 0x38, 0); // ... and the == 0 guard it tests
    mem.writeU32(0x80436108, 1); // the != 0 guard it tests
    mem.writeU32(0x8043610c, COLOUR_SLOT); // the colour pointer it dereferences
    mem.writeU32(COLOUR_SLOT, ROM_QUAD_RGBA >>> 0); // ... and the RGBA8 word itself
    // The ROM's own orthographic Mtx44 over its 640x448 frame, GC row-major.
    for (let i = 0; i < 16; i++) mem.writeF32(PROJECTION + i * 4, 0);
    mem.writeF32(PROJECTION + 0 * 4, 2 / 640);
    mem.writeF32(PROJECTION + 3 * 4, -1);
    mem.writeF32(PROJECTION + 5 * 4, -2 / 448);
    mem.writeF32(PROJECTION + 7 * 4, 1);
    mem.writeF32(PROJECTION + 10 * 4, 1);
    mem.writeF32(PROJECTION + 11 * 4, -1);
    mem.writeF32(PROJECTION + 15 * 4, 1);

    gx.beginFrame();
    host.nextFrame();
    await host.invokeExport("zz_0027c34_", []);
    gx.endFrame();

    const records = backend.recorder.records;
    const last = records[records.length - 1];
    check("the gate-lowered ROM unit submitted exactly one primitive", gx.fifo.primitiveCount, 1);
    check("the ROM's own draw is GX_QUADS", last?.primitive, "QUADS");
    check("the ROM's own draw has 4 vertices", last?.vertexCount, 4);
    check("the ROM's own corner vertex decoded", last?.firstVertex, [0, 0, 0]);
    check(
      "the ROM's own RGBA8 colour word reached the framebuffer path",
      last?.firstColor,
      [(ROM_QUAD_RGBA >>> 24) & 0xff, (ROM_QUAD_RGBA >>> 16) & 0xff, (ROM_QUAD_RGBA >>> 8) & 0xff, ROM_QUAD_RGBA & 0xff],
    );
    check("the ROM unit's FIFO consumed every byte it wrote", gx.fifo.droppedBytes, 0);
    check("no ROM-unit vertex bytes left buffered", gx.fifo.pendingBytes, 0);
    // The pixels: this is the first time real ROM geometry has reached this
    // rasterizer through the H2 transport.
    //
    // The EXPECTED value is not the colour word. zz_0027c34_'s own second call
    // is `GXSetBlendMode(1, 4, 5, 0)` — GX_BM_BLEND with SRCALPHA/INVSRCALPHA —
    // and beginFrame cleared to black, so the framebuffer must hold
    // `colour * alpha`. Asserting the blended value rather than the raw one is
    // deliberate: it checks that the ROM's own blend state reached GL as well
    // as that its colour word survived the pipe. A host that ignored
    // GXSetBlendMode would produce the raw colour and fail here.
    const alpha = (ROM_QUAD_RGBA & 0xff) / 255;
    const blended = (shift: number): number => Math.round(((ROM_QUAD_RGBA >>> shift) & 0xff) * alpha);
    const centre = readPixel(gl, WIDTH / 2, HEIGHT / 2);
    checkNear("ROM unit framebuffer centre R (colour * the ROM's own src alpha)", centre[0], blended(24), 2);
    checkNear("ROM unit framebuffer centre G", centre[1], blended(16), 2);
    checkNear("ROM unit framebuffer centre B", centre[2], blended(8), 2);
    check("the ROM's alpha blend actually ran (the raw colour would be brighter)", centre[0] < ((ROM_QUAD_RGBA >>> 24) & 0xff), true);
    const corner = readPixel(gl, 4, 4);
    checkNear("ROM unit framebuffer corner B (the quad covers the whole frame)", corner[2], blended(8), 2);
    check("the ROM unit hit no unimplemented GX entry point", gx.unimplementedHits, []);

    romFramebufferPng = canvas.toDataURL("image/png");
    return {
      source:
        "assembly-gate output for zz_0027c34_ (0x80027c34) with OGHIDRA_PORT_WGPIPE_LOWERING=1 — " +
        "verbatim ROM decompilation, write-gather-pipe stores lowered, NOT hand-written",
      calls: [...gx.callCounts.entries()].sort((a, b) => b[1] - a[1]).map(([symbol, count]) => ({ symbol, count })),
      primitives: gx.fifo.primitiveCount,
      droppedFifoBytes: gx.fifo.droppedBytes,
      verified: false,
      behaviouralClaim: GX_NO_BEHAVIOURAL_CLAIM,
    };
  } finally {
    await host.shutdown();
  }
}

main().catch((error: unknown) => {
  render(true, null, error instanceof Error ? `${error.message}\n${error.stack ?? ""}` : String(error));
});
