// =============================================================================
// adapters.ts — the GX entry points as bridged-callee host adapters.
//
// This is the SDK seam for graphics (design V2 F2 / step 11): the whole gnt4_*
// family is excluded from porting, so every GX call a composed module makes is
// an out-of-window call that crosses the H2 bridge and lands here. Each adapter
// reads its arguments from the dispatch frame (and, for pointer arguments, out
// of the shared GC arena) and writes its effect into the GxState the FIFO
// decoder and the backend read — the I1 contract, applied to graphics.
//
// EVIDENCE CLASS: every adapter here is "synthetic".
// That is not a placeholder pending cleanup; it is the accurate class. These
// adapters are written from the GX API's documented semantics and from the
// decompiled call sites, and NOT ONE of them has been compared against a
// captured frame or a Dolphin trace. The AdapterRegistry therefore refuses
// them unless the host was explicitly opened for pilot work, which is the
// structural expression of "this is scaffolding". When GX trace capture exists
// and an adapter's behaviour is checked against it, that adapter — and only
// that adapter — may be reclassified.
//
// LOUDNESS RULE (task-normative): an entry point this host does not implement
// gets an adapter that THROWS, naming the symbol, its ROM address and its rank
// in the measured inventory. It never returns quietly. A silent no-op in a
// graphics seam produces a frame that renders and is wrong, which is strictly
// worse than a frame that fails.
// =============================================================================

import { defineAdapter, type BridgedCallContext, type BridgedCalleeAdapter } from "../adapters.js";
import { gcAddressForSymbol } from "../composed.js";
import { FrameValueClass } from "../frame.js";
import type { GcMemory } from "../memory.js";
import type { GxBackend } from "./backend.js";
import {
  GXAttr,
  GXAttrType,
  GXColorSrc,
  GXTexFmt,
  GXTlutFmt,
  GX_MAX_TEXMAP,
  GX_TEXMAP_NULL,
  GX_TEX_DISABLE,
  attrName,
} from "./enums.js";
import { GxFifo } from "./fifo.js";
import { GX_CALL_INVENTORY, gxCoverage, gxInventoryEntry } from "./inventory.generated.js";
import { GxState } from "./state.js";
import { tevStageFromOp } from "./tev.js";

/** The evidence string every GX adapter carries. Deliberately one shared,
 *  unflattering sentence: per-adapter prose would let one of them read as if
 *  something had been verified. */
const GX_EVIDENCE =
  "GX API semantics + decompiled ROM call sites (research/decomp/ghidra-export). " +
  "NO trace capture, NO framebuffer comparison — scaffolding, see docs/gx-hle-host.md";

/**
 * The GX host: latched pipeline state, the write-gather-pipe decoder, and the
 * backend the decoded primitives are handed to.
 */
export class GxHost {
  readonly state = new GxState();
  readonly fifo: GxFifo;
  readonly backend: GxBackend;
  /** Entry points that were called but are not implemented, in call order. */
  readonly unimplementedHits: string[] = [];
  /** Every GX call this host serviced, symbol -> count. */
  readonly callCounts = new Map<string, number>();

  constructor(backend: GxBackend, mem: GcMemory | null = null) {
    this.backend = backend;
    this.fifo = new GxFifo(this.state, backend, mem);
  }

  beginFrame(): void {
    this.backend.beginFrame();
  }
  endFrame(): void {
    this.backend.endFrame();
  }

  /**
   * Write a channel colour register the way the ROM's own dispatch does.
   *
   * [CORPUS] gnt4_GXSetChanMatColor_bl @0x8022876c branches on the channel id:
   * 0 and 2 target colour register 0, 1 and 3 target register 1, and 4 and 5
   * target both (they are the combined COLOR0A0 / COLOR1A1 channels). The
   * alpha-only channels write only the alpha byte and the colour-only channels
   * write only the rgb bytes, which is what the body's `& 0xff` / `& 0xffffff00`
   * masking does.
   */
  setChannelColor(bank: Uint8Array[], chan: number, color: Uint8Array): void {
    const rgbOnly = chan === 0 || chan === 1;
    const alphaOnly = chan === 2 || chan === 3;
    const targets = chan === 4 ? [0] : chan === 5 ? [1] : chan === 1 || chan === 3 ? [1] : [0];
    for (const t of targets) {
      const dst = bank[t];
      if (!dst) continue;
      if (!alphaOnly) for (let i = 0; i < 3; i++) dst[i] = color[i] ?? 0;
      if (!rgbOnly) dst[3] = color[3] ?? 255;
    }
  }

  record(symbol: string): void {
    this.callCounts.set(symbol, (this.callCounts.get(symbol) ?? 0) + 1);
  }

  /** Coverage of the measured ranked surface, split by implementation tier. */
  coverage(): ReturnType<typeof gxTieredCoverage> {
    return gxTieredCoverage();
  }

  /** JSON-safe report for window.__gf and the smoke phase. */
  report(): {
    behaviouralClaim: string;
    verified: false;
    coverage: ReturnType<typeof gxTieredCoverage>;
    calls: Array<{ symbol: string; count: number }>;
    unimplementedHits: string[];
    fifo: { primitives: number; droppedBytes: number; pendingBytes: number };
    diagnostics: readonly string[];
  } {
    return {
      behaviouralClaim: GX_NO_BEHAVIOURAL_CLAIM,
      verified: false,
      coverage: this.coverage(),
      calls: [...this.callCounts.entries()].sort((a, b) => b[1] - a[1]).map(([symbol, count]) => ({ symbol, count })),
      unimplementedHits: [...this.unimplementedHits],
      fifo: {
        primitives: this.fifo.primitiveCount,
        droppedBytes: this.fifo.droppedBytes,
        pendingBytes: this.fifo.pendingBytes,
      },
      diagnostics: this.backend.diagnostics,
    };
  }
}

/** Repeated verbatim everywhere this host reports anything. */
export const GX_NO_BEHAVIOURAL_CLAIM =
  "NONE. Every GX adapter is a synthetic stand-in written from API semantics and decompiled call sites; " +
  "no frame produced by this path has ever been compared against a real GameCube frame, and the path has " +
  "no trace verification behind it. The ceiling even once verified is 'framebuffer-equivalent, never " +
  "pixel-identical'. This is scaffolding — see docs/gx-hle-host.md.";

// =============================================================================
// Argument readers
// =============================================================================

/**
 * Read a GC matrix out of the shared arena.
 *
 * ENDIANNESS (settled, not assumed): the arena is byte-swapped to wasm-native
 * LITTLE-endian when it is built from the DOL, so GcMemory's little-endian
 * reads are correct here. Verified rather than inferred:
 * apps/game/public/rom/arena.json holds the 1.0f constant at 0x80436f78 as
 * `00 00 80 3f`. The FIFO byte stream keeps the console's BIG-endian register
 * order instead — see fifo.ts for why the two differ.
 */
function readMtx3x4(mem: GcMemory, addr: number): Float32Array {
  const out = new Float32Array(12);
  for (let i = 0; i < 12; i++) out[i] = mem.readF32(addr + i * 4);
  return out;
}

function readMtx4x4(mem: GcMemory, addr: number): Float32Array {
  const out = new Float32Array(16);
  for (let i = 0; i < 16; i++) out[i] = mem.readF32(addr + i * 4);
  return out;
}

/**
 * Read a GXColor out of the arena as four consecutive bytes, r first.
 *
 * WHY A POINTER AND NOT A VALUE — this settles a question docs/gx-hle-host.md
 * left open as "genuinely ambiguous". The SDK declares GXColor as a 4-byte
 * struct passed by value, and a value would arrive in a register. But the
 * decompiled bodies in this build DEREFERENCE: gnt4_GXSetTevKColor_bl
 * @0x80229e88 reads `*param_2`, `param_2[1]`, `param_2[2]`, `param_2[3]` as
 * separate byte loads, and the ROM's own call sites pass `&local_1c`. Ghidra
 * derives both sides from the actual instructions, so an address-of in the
 * caller paired with byte loads in the callee is what the shipped code does.
 * The same shape appears in gnt4_GXSetChanMatColor_bl, gnt4_GXSetChanAmbColor_bl
 * and gnt4_GXInitLightColor_bl, so all four are read the same way here.
 *
 * REMAINING HAZARD, stated rather than hidden: the byte ORDER of that struct
 * in the arena depends on how the region holding it was emitted. The arena
 * builder converts per region by declared type (`swap4` for 4-byte-typed data,
 * `raw` for byte tables — research/decomp/poc/wasm-port-poc/gen_arena.py), and
 * a ported unit that composes a colour as one u32 store lands it in wasm
 * little-endian order. Reading r,g,b,a in ascending address order is what the
 * ROM's own body does, so it is the faithful translation of the callee; a
 * caller that packs a word is the case that would need compensating, and it
 * would show up as swapped red and alpha rather than as a failure.
 */
function readColor(mem: GcMemory, addr: number): Uint8Array {
  return Uint8Array.from(mem.readBytes(addr >>> 0, 4));
}

function colorToFloats(color: Uint8Array, out: Float32Array, base: number): void {
  for (let i = 0; i < 4; i++) out[base + i] = (color[i] ?? 0) / 255;
}

// =============================================================================
// The implemented entry points
// =============================================================================

/**
 * How much an implemented entry point actually DOES. Reported separately in
 * the coverage figures, because collapsing these into one "implemented"
 * number is how a graphics seam talks itself into sounding finished.
 *
 *  - "translated": the call changes what the backend draws.
 *  - "latched":    the call is recorded into GxState and INFLUENCES nothing
 *                  yet. The backend emits a diagnostic at draw time when a
 *                  latched-but-unapplied state is non-default, so the gap is
 *                  loud where it matters rather than at the call.
 *  - "declared-nop": the call correctly has no host-visible effect (cache
 *                  invalidation, pipe synchronization). This is the ONLY
 *                  category where doing nothing is right, and it is named so
 *                  it can never be confused with the other two.
 */
export type GxImplTier = "translated" | "latched" | "declared-nop";

interface GxAdapterSpec {
  /** C symbol — also the wasm import name and the inventory key. */
  symbol: string;
  retClass: FrameValueClass;
  tier: GxImplTier;
  /** Short note on what the host does with it. Shown in the coverage doc. */
  effect: string;
  service(gx: GxHost, ctx: BridgedCallContext): number;
}

const SPECS: GxAdapterSpec[] = [
  // ==========================================================================
  // Vertex descriptor / attribute format — ranks 1, 2, 5 (45, 45, 18 sites)
  // ==========================================================================
  {
    symbol: "gnt4_GXSetVtxDesc_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "latches attribute -> GXAttrType; drives the FIFO vertex layout",
    service(gx, ctx) {
      gx.state.setVtxDesc(ctx.frame.u32Arg(0), ctx.frame.i32Arg(1));
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXClearVtxDesc_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "clears the vertex descriptor. NOTE: the ROM's own GXClearVtxDesc forces POS back to " +
      "GX_DIRECT afterwards; the host reproduces that so a draw that never re-declares POS " +
      "still has one",
    service(gx, ctx) {
      gx.state.clearVtxDesc();
      // [CORPUS] gnt4_GXClearVtxDesc_bl @0x802261ac zeroes the VCD words and
      // then ORs 0x200 back into the POS field — POS is left DIRECT, not NONE.
      gx.state.setVtxDesc(GXAttr.POS, GXAttrType.DIRECT);
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetVtxAttrFmt_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "latches (cnt, type, frac) for one attribute in one of the 8 VAT slots",
    service(gx, ctx) {
      gx.state.setVtxAttrFmt(
        ctx.frame.i32Arg(0),
        ctx.frame.u32Arg(1),
        ctx.frame.i32Arg(2),
        ctx.frame.i32Arg(3),
        ctx.frame.i32Arg(4),
      );
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetArray",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "binds an attribute's INDEX8/INDEX16 source array (base + stride) in GC memory",
    service(gx, ctx) {
      // [CORPUS] gnt4_GXSetArray computes its CP array slot as `attr - 9` and
      // folds NBT (0x19) onto NRM (10), so the attr id is the raw GXAttr.
      const attr = ctx.frame.u32Arg(0);
      gx.state.arrays.set(attr === GXAttr.NBT ? GXAttr.NRM : attr, {
        base: ctx.frame.u32Arg(1) >>> 0,
        stride: ctx.frame.i32Arg(2),
      });
      return ctx.frame.setRetVoid();
    },
  },

  // ==========================================================================
  // Primitive submission — rank 3 (19 sites)
  // ==========================================================================
  {
    symbol: "gnt4_GXBegin_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "opens a primitive: snapshots pipeline state and plans the FIFO vertex layout",
    service(gx, ctx) {
      gx.fifo.begin(ctx.frame.i32Arg(0), ctx.frame.i32Arg(1), ctx.frame.i32Arg(2));
      return ctx.frame.setRetVoid();
    },
  },

  // ==========================================================================
  // Matrices and projection — ranks 6, 9, 11 (18, 16, 15 sites)
  // ==========================================================================
  {
    symbol: "gnt4_GXSetProjection_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "packs a Mtx44 from GC memory into GX's 6 projection coefficients + type " +
      "(perspective takes m[0][0],m[0][2],m[1][1],m[1][2],m[2][2],m[2][3]; " +
      "orthographic takes m[0][3]/m[1][3] instead of the [0][2]/[1][2] pair)",
    service(gx, ctx) {
      gx.state.setProjection(readMtx4x4(ctx.mem, ctx.frame.u32Arg(0)), ctx.frame.i32Arg(1));
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXGetProjectionv_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "writes the latched projection back into GC memory in the SDK's 7-float packed form",
    service(gx, ctx) {
      const out = ctx.frame.u32Arg(0) >>> 0;
      for (let i = 0; i < 7; i++) ctx.mem.writeF32(out + i * 4, gx.state.projection[i] ?? 0);
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXLoadPosMtxImm_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "stores a 3x4 row-major matrix into position-matrix memory at the given row id",
    service(gx, ctx) {
      gx.state.loadPosMtx(ctx.frame.i32Arg(1), readMtx3x4(ctx.mem, ctx.frame.u32Arg(0)));
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXLoadNrmMtxImm_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "stores a normal matrix. Now applied: the generated vertex shader transforms decoded " +
      "normals through it when a channel has lighting enabled",
    service(gx, ctx) {
      gx.state.loadNrmMtx(ctx.frame.i32Arg(1), readMtx3x4(ctx.mem, ctx.frame.u32Arg(0)));
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXLoadTexMtxImm_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "stores a texture matrix at a 6-bit row id. Now applied: GXSetTexCoordGen2 names one of " +
      "these rows and the generated vertex shader multiplies the texgen source through it",
    service(gx, ctx) {
      gx.state.loadTexMtx(ctx.frame.i32Arg(1), readMtx3x4(ctx.mem, ctx.frame.u32Arg(0)));
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetCurrentMtx_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "selects which position matrix subsequent draws transform through (6-bit row id)",
    service(gx, ctx) {
      gx.state.currentMtxId = ctx.frame.i32Arg(0) & 0x3f;
      return ctx.frame.setRetVoid();
    },
  },

  // ==========================================================================
  // Raster state — ranks 7, 15, 21, 23
  // ==========================================================================
  {
    symbol: "gnt4_GXSetZMode_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "depth test enable / compare function / depth write",
    service(gx, ctx) {
      gx.state.zCompareEnable = ctx.frame.i32Arg(0) !== 0;
      gx.state.zFunc = ctx.frame.i32Arg(1) & 7;
      gx.state.zUpdate = ctx.frame.i32Arg(2) !== 0;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetCullMode_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "face culling",
    service(gx, ctx) {
      gx.state.cullMode = ctx.frame.i32Arg(0) & 3;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetBlendMode_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "blend equation and factors (type is corpus-settled; the FACTOR numbering is not — see " +
      "GXBlendFactor in enums.ts). Logic-op mode is reported unimplemented by the backend",
    service(gx, ctx) {
      gx.state.blendMode = ctx.frame.i32Arg(0);
      gx.state.blendSrc = ctx.frame.i32Arg(1) & 7;
      gx.state.blendDst = ctx.frame.i32Arg(2) & 7;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetColorUpdate_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "colour write mask",
    service(gx, ctx) {
      gx.state.colorUpdate = ctx.frame.i32Arg(0) !== 0;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetAlphaUpdate_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "alpha write mask",
    service(gx, ctx) {
      gx.state.alphaUpdate = ctx.frame.i32Arg(0) !== 0;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetScissor_bl",
    tier: "latched",
    retClass: FrameValueClass.VOID,
    effect: "scissor rectangle. Latched only: the backend does not clip to it yet",
    service(gx, ctx) {
      gx.state.scissor = Int32Array.from([
        ctx.frame.i32Arg(0),
        ctx.frame.i32Arg(1),
        ctx.frame.i32Arg(2),
        ctx.frame.i32Arg(3),
      ]);
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXGetViewportv_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "writes the latched 6-float viewport back into GC memory",
    service(gx, ctx) {
      const out = ctx.frame.u32Arg(0) >>> 0;
      for (let i = 0; i < 6; i++) ctx.mem.writeF32(out + i * 4, gx.state.viewport[i] ?? 0);
      return ctx.frame.setRetVoid();
    },
  },

  // ==========================================================================
  // Lighting channel / TEV counts — ranks 10, 12, 13, 14
  // ==========================================================================
  {
    symbol: "gnt4_GXSetChanCtrl_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "the whole per-channel lighting configuration: enable, ambient/material colour sources, " +
      "the 8-bit light mask, the diffuse function and the attenuation function. All of it now " +
      "reaches the generated vertex shader. The GXAttnFn numbering is corpus-settled from the " +
      "two separate register bits this body derives from one argument (see enums.ts)",
    service(gx, ctx) {
      // [CORPUS] GXSetChanCtrl(chan, enable, amb_src, mat_src, light_mask,
      // diff_fn, attn_fn) — gnt4_GXSetChanCtrl_bl @0x80228898.
      const chan = ctx.frame.u32Arg(0);
      const cfg = {
        enabled: (ctx.frame.i32Arg(1) & 1) !== 0,
        ambSrc: ctx.frame.i32Arg(2) & 1,
        matSrc: ctx.frame.i32Arg(3) & 1,
        lightMask: ctx.frame.u32Arg(4) & 0xff,
        diffFn: ctx.frame.u32Arg(5) & 3,
        attnFn: ctx.frame.i32Arg(6),
      };
      // Channels 4 and 5 are the combined colour+alpha channels: the corpus
      // body writes the SAME register value to both halves for them.
      const targets = chan === 4 ? [0, 2] : chan === 5 ? [1, 3] : [chan & 3];
      for (const t of targets) {
        const slot = gx.state.chanCtrl[t];
        if (slot) Object.assign(slot, cfg);
      }
      gx.state.chanEnabled = cfg.enabled;
      gx.state.matSrcVertex = cfg.matSrc === GXColorSrc.VERTEX;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetNumChans_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "colour-channel count. Now acted on: a channel above the count is not evaluated in the " +
      "generated vertex shader, and a TEV stage that reads one is reported",
    service(gx, ctx) {
      gx.state.numChans = ctx.frame.i32Arg(0) & 7;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetNumTexGens_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "texcoord-generator count — the number of texgen outputs the generated vertex shader " +
      "computes, and the bound a TEV stage's texcoord selection is checked against",
    service(gx, ctx) {
      gx.state.numTexGens = ctx.frame.i32Arg(0) & 0xf;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetNumTevStages_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "TEV stage count (1-based) — how many stages the generated fragment shader chains. The " +
      "4-bit field width is corpus-settled from gnt4_GXSetNumTevStages_bl's `(n-1)*0x400 & 0x3c00`",
    service(gx, ctx) {
      gx.state.numTevStages = ctx.frame.i32Arg(0) & 0xff;
      return ctx.frame.setRetVoid();
    },
  },

  // ==========================================================================
  // Texture binding — ranks 18, 24
  // ==========================================================================
  {
    symbol: "gnt4_GXInitTexObj_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "records a texture object. Now acted on: gx/texture.ts decodes the image out of the arena " +
      "at the GC address the ROM gave, and the backend uploads it. The GXTexFmt numbering is " +
      "corpus-settled from this function's own block-geometry switch (see enums.ts)",
    service(gx, ctx) {
      const objAddr = ctx.frame.u32Arg(0) >>> 0;
      const format = ctx.frame.i32Arg(4);
      const paletted = format === GXTexFmt.C4 || format === GXTexFmt.C8 || format === GXTexFmt.C14X2;
      // A paletted format needs a palette. The ROM loads one through
      // GXLoadTlut, and the SDK's GXInitTexObjCI is what names the TLUT — a
      // function this game never calls. Binding the most recently loaded
      // palette is therefore a GUESS, and it says so at draw time rather than
      // producing a plausible-looking recolour.
      const tlut = paletted ? gx.state.lastLoadedTlut : null;
      gx.state.texObjs.set(objAddr, {
        objAddr,
        imageAddr: ctx.frame.u32Arg(1) >>> 0,
        width: ctx.frame.u32Arg(2) & 0xffff,
        height: ctx.frame.u32Arg(3) & 0xffff,
        format,
        wrapS: ctx.frame.i32Arg(5) & 3,
        wrapT: ctx.frame.i32Arg(6) & 3,
        mipmap: ctx.frame.i32Arg(7),
        minFilter: 1,
        magFilter: 1,
        tlutAddr: tlut ? tlut.imageAddr : null,
        tlutFormat: tlut ? tlut.format : GXTlutFmt.RGB5A3,
        tlutEntries: tlut ? tlut.entries : 0,
      });
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXLoadTexObj_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "binds a texture object to a GX_TEXMAP slot (0..7). The bound texture is decoded, uploaded " +
      "and sampled by any TEV stage whose GXSetTevOrder names that slot",
    service(gx, ctx) {
      const objAddr = ctx.frame.u32Arg(0) >>> 0;
      const map = ctx.frame.i32Arg(1);
      if (map >= 0 && map < GX_MAX_TEXMAP) {
        gx.state.textures[map] = gx.state.texObjs.get(objAddr) ?? null;
      }
      return ctx.frame.setRetVoid();
    },
  },

  // ==========================================================================
  // TEV — the fragment combiner. Ranks 4, 16, 19, 23, 24, 25, 26, 28, 29, 30,
  // 34, 36, 69. Every one of these now reaches the generated fragment shader
  // in webgl.ts; none of them is merely latched any more.
  // ==========================================================================
  {
    symbol: "gnt4_GXSetTevOrder_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "wires a TEV stage's texmap, texcoord and rasterized colour channel. Argument order " +
      "(stage, coord, map, color) is corpus-settled: gnt4_GXSetTevOrder_bl @0x8022a14c strips " +
      "0x100 from the MAP argument and tests the COORD argument against 8, so the two cannot be " +
      "confused. GX_TEXMAP_NULL is 0xff",
    service(gx, ctx) {
      const stage = ctx.frame.i32Arg(0);
      const slot = gx.state.tevStages[stage & 0xf];
      if (!slot) return ctx.frame.setRetVoid();
      const coord = ctx.frame.u32Arg(1);
      const map = ctx.frame.u32Arg(2);
      slot.texCoord = coord < 8 ? coord : 0xff;
      slot.texMap = map === GX_TEXMAP_NULL || (map & GX_TEX_DISABLE) !== 0 ? GX_TEXMAP_NULL : map & 7;
      slot.channel = ctx.frame.i32Arg(3) & 0xff;
      if ((stage & 0xf) === 0) gx.state.tevTexMap = slot.texMap;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTevOp_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "installs one of the five canned combiner programs. The 5-entry bound and the " +
      "stage-0-uses-RASC / later-stages-use-CPREV rule are corpus-settled from the two table " +
      "pairs gnt4_GXSetTevOp_bl indexes; the tuples themselves are the documented SDK expansions",
    service(gx, ctx) {
      const stage = ctx.frame.i32Arg(0) & 0xf;
      const slot = gx.state.tevStages[stage];
      if (slot) gx.state.tevStages[stage] = tevStageFromOp(slot, stage, ctx.frame.i32Arg(1));
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTevColorIn_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "the four colour inputs of one stage. Argument order (stage, a, b, c, d) and the 4-bit " +
      "selector width are corpus-settled from the register packing",
    service(gx, ctx) {
      const slot = gx.state.tevStages[ctx.frame.i32Arg(0) & 0xf];
      if (slot) {
        slot.colorIn = [
          ctx.frame.u32Arg(1) & 0xf,
          ctx.frame.u32Arg(2) & 0xf,
          ctx.frame.u32Arg(3) & 0xf,
          ctx.frame.u32Arg(4) & 0xf,
        ];
      }
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTevAlphaIn_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "the four alpha inputs of one stage; 3-bit selectors, corpus-settled width",
    service(gx, ctx) {
      const slot = gx.state.tevStages[ctx.frame.i32Arg(0) & 0xf];
      if (slot) {
        slot.alphaIn = [
          ctx.frame.u32Arg(1) & 7,
          ctx.frame.u32Arg(2) & 7,
          ctx.frame.u32Arg(3) & 7,
          ctx.frame.u32Arg(4) & 7,
        ];
      }
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTevColorOp_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "op / bias / scale / clamp / output register for one stage's colour. Argument order is " +
      "corpus-settled, and so is the compare-op encoding (bias forced to 3, op>>1 into the scale field)",
    service(gx, ctx) {
      const slot = gx.state.tevStages[ctx.frame.i32Arg(0) & 0xf];
      if (slot) {
        slot.colorOp = {
          op: ctx.frame.u32Arg(1) & 0xf,
          bias: ctx.frame.u32Arg(2) & 3,
          scale: ctx.frame.u32Arg(3) & 3,
          clamp: ctx.frame.i32Arg(4) !== 0,
          outReg: ctx.frame.u32Arg(5) & 3,
        };
      }
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTevAlphaOp_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "op / bias / scale / clamp / output register for one stage's alpha",
    service(gx, ctx) {
      const slot = gx.state.tevStages[ctx.frame.i32Arg(0) & 0xf];
      if (slot) {
        slot.alphaOp = {
          op: ctx.frame.u32Arg(1) & 0xf,
          bias: ctx.frame.u32Arg(2) & 3,
          scale: ctx.frame.u32Arg(3) & 3,
          clamp: ctx.frame.i32Arg(4) !== 0,
          outReg: ctx.frame.u32Arg(5) & 3,
        };
      }
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTevKColor_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "sets one of the four konstant colour registers the stages select from",
    service(gx, ctx) {
      const reg = ctx.frame.i32Arg(0) & 3;
      colorToFloats(readColor(ctx.mem, ctx.frame.u32Arg(1)), gx.state.tevKColors, reg * 4);
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTevColor_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "sets one of the four TEV colour registers (GX_TEVPREV, GX_TEVREG0..2)",
    service(gx, ctx) {
      const reg = ctx.frame.i32Arg(0) & 3;
      colorToFloats(readColor(ctx.mem, ctx.frame.u32Arg(1)), gx.state.tevRegs, reg * 4);
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTevColorS10_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "sets a TEV colour register from four SIGNED 10-bit components. Stored unclamped: the " +
      "whole point of the S10 form is values outside [0,255], and clamping at latch time would " +
      "throw away what the ROM asked for. The corpus body masks each with 0x7ff",
    service(gx, ctx) {
      const reg = ctx.frame.i32Arg(0) & 3;
      const addr = ctx.frame.u32Arg(1) >>> 0;
      for (let i = 0; i < 4; i++) {
        // [CORPUS] gnt4_GXSetTevColorS10_bl reads param_2[0..3] as shorts and
        // pairs [3] with [0] (alpha, red) and [1] with [2] (green, blue).
        gx.state.tevRegs[reg * 4 + i] = ctx.mem.readI16(addr + i * 2) / 255;
      }
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTevKColorSel_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "which konstant a stage's KONST colour input reads. 5-bit selector, corpus-settled width",
    service(gx, ctx) {
      const slot = gx.state.tevStages[ctx.frame.u32Arg(0) & 0xf];
      if (slot) slot.kColorSel = ctx.frame.u32Arg(1) & 0x1f;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTevKAlphaSel_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "which konstant a stage's KONST alpha input reads",
    service(gx, ctx) {
      const slot = gx.state.tevStages[ctx.frame.u32Arg(0) & 0xf];
      if (slot) slot.kAlphaSel = ctx.frame.u32Arg(1) & 0x1f;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTevSwapMode_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "which swap-table row a stage applies to its rasterized colour and to its texture colour",
    service(gx, ctx) {
      const slot = gx.state.tevStages[ctx.frame.i32Arg(0) & 0xf];
      if (slot) {
        slot.rasSwap = ctx.frame.u32Arg(1) & 3;
        slot.texSwap = ctx.frame.u32Arg(2) & 3;
      }
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTevSwapModeTable_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "one row of the 4x4 channel swap table. Argument order (table, r, g, b, a) and the 2-bit " +
      "fields are corpus-settled from the KSEL register pair the body writes",
    service(gx, ctx) {
      const row = ctx.frame.i32Arg(0) & 3;
      gx.state.swapTable[row] = [
        ctx.frame.u32Arg(1) & 3,
        ctx.frame.u32Arg(2) & 3,
        ctx.frame.u32Arg(3) & 3,
        ctx.frame.u32Arg(4) & 3,
      ];
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetAlphaCompare_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "the two-term alpha test, generated into the fragment shader as a discard. Argument order " +
      "(comp0, ref0, op, comp1, ref1) is corpus-settled from the register packing; the COMPARE " +
      "function numbering is not (see GXCompare in enums.ts)",
    service(gx, ctx) {
      gx.state.alphaCompare = {
        comp0: ctx.frame.u32Arg(0) & 7,
        ref0: ctx.frame.u32Arg(1) & 0xff,
        op: ctx.frame.u32Arg(2) & 3,
        comp1: ctx.frame.u32Arg(3) & 7,
        ref1: ctx.frame.u32Arg(4) & 0xff,
      };
      return ctx.frame.setRetVoid();
    },
  },

  // ==========================================================================
  // Texture pipeline — ranks 17, 22, 37, 54, 66
  // ==========================================================================
  {
    symbol: "gnt4_GXInitTexObjLOD_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "min/mag filter for an already-initialized texture object. Ghidra's argument order puts " +
      "the three FP arguments (min_lod, max_lod, lod_bias) first because PPC passes them in " +
      "FPRs; the body's own use pins arg 3 as the object, arg 4 as min_filt (it indexes the " +
      "filter translation table with it) and arg 5 as mag_filt (it tests it against 1). " +
      "LOD/bias/aniso are NOT modelled — the host uploads a single mip level",
    service(gx, ctx) {
      const objAddr = ctx.frame.u32Arg(3) >>> 0;
      const obj = gx.state.texObjs.get(objAddr);
      if (obj) {
        obj.minFilter = ctx.frame.i32Arg(4);
        obj.magFilter = ctx.frame.i32Arg(5);
      }
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXInitTlutObj_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "records a palette: data pointer, GXTlutFmt and entry count. Argument order is " +
      "corpus-settled from gnt4_GXInitTlutObj_bl @0x8022915c, which stores fmt at bits 10-11, " +
      "the data pointer >> 5 and the entry count as a u16",
    service(gx, ctx) {
      const objAddr = ctx.frame.u32Arg(0) >>> 0;
      gx.state.tlutObjs.set(objAddr, {
        objAddr,
        imageAddr: ctx.frame.u32Arg(1) >>> 0,
        format: ctx.frame.i32Arg(2) & 3,
        entries: ctx.frame.u32Arg(3) & 0xffff,
      });
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXLoadTlut_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "loads a palette so paletted textures can sample it. The host keeps palettes as OBJECTS " +
      "keyed by TLUT name rather than emulating texture memory, so the load is a binding, not a copy",
    service(gx, ctx) {
      const obj = gx.state.tlutObjs.get(ctx.frame.u32Arg(0) >>> 0);
      if (obj) {
        gx.state.loadedTluts.set(ctx.frame.i32Arg(1) & 0xff, obj);
        gx.state.lastLoadedTlut = obj;
      }
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTexCoordGen2_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "one texture-coordinate generator: source, function and matrix. Both the GXTexGenType and " +
      "GXTexGenSrc numberings are corpus-settled from gnt4_GXSetTexCoordGen2_bl's own dispatch " +
      "(see enums.ts). Applied in the generated vertex shader",
    service(gx, ctx) {
      const dst = ctx.frame.i32Arg(0) & 7;
      const gen = gx.state.texGens[dst];
      if (gen) {
        gen.type = ctx.frame.i32Arg(1);
        gen.src = ctx.frame.i32Arg(2);
        gen.mtx = ctx.frame.u32Arg(3) & 0x3f ? ctx.frame.i32Arg(3) : ctx.frame.i32Arg(3);
        gen.normalize = (ctx.frame.i32Arg(4) & 1) !== 0;
        gen.postMtx = ctx.frame.i32Arg(5);
      }
      return ctx.frame.setRetVoid();
    },
  },

  // ==========================================================================
  // Lighting — ranks 44, 57, 58, 60, 61, 62
  // ==========================================================================
  {
    symbol: "gnt4_GXInitLightColor_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "writes a light object's colour to object offset 0x0c, exactly as the corpus body does. " +
      "The GXInitLight* family mutates a CALLER-OWNED struct and returns nothing, so the host " +
      "writes GC memory rather than keeping a shadow copy — GXLoadLightObjImm then reads back " +
      "the same bytes the console would have",
    service(_gx, ctx) {
      ctx.mem.writeBytes((ctx.frame.u32Arg(0) + 0x0c) >>> 0, readColor(ctx.mem, ctx.frame.u32Arg(1)));
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXInitLightPos_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "a light object's position (offsets 0x28/0x2c/0x30). The three FP arguments come first " +
      "because PPC passes them in FPRs; arg 3 is the object",
    service(_gx, ctx) {
      const obj = ctx.frame.u32Arg(3) >>> 0;
      ctx.mem.writeF32(obj + 0x28, ctx.frame.f64Arg(0));
      ctx.mem.writeF32(obj + 0x2c, ctx.frame.f64Arg(1));
      ctx.mem.writeF32(obj + 0x30, ctx.frame.f64Arg(2));
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXInitLightDistAttn_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "distance attenuation k0/k1/k2 (offsets 0x1c/0x20/0x24). The corpus body computes the " +
      "polynomial from (ref_distance, ref_brightness, dist_func) and always writes k0 = 1.0; " +
      "that computation is reproduced here rather than the arguments being stored raw",
    service(_gx, ctx) {
      const refDist = ctx.frame.f64Arg(0);
      const refBright = ctx.frame.f64Arg(1);
      const obj = ctx.frame.u32Arg(2) >>> 0;
      let fn = ctx.frame.i32Arg(3);
      // [CORPUS] the body forces GX_DA_OFF when the arguments are degenerate.
      if (refDist < 0 || refBright <= 0 || refBright >= 1) fn = 0;
      let k1 = 0;
      let k2 = 0;
      if (fn === 1) k1 = (1 - refBright) / (refBright * refDist);
      else if (fn === 2) k2 = (1 - refBright) / (refBright * refDist * refDist);
      else if (fn === 3) {
        // [CORPUS] the third branch splits the polynomial across k1 and k2.
        const s = 0.5 * (1 - refBright);
        k1 = s / (refBright * refDist);
        k2 = s / (refBright * refDist * refDist);
      }
      ctx.mem.writeF32(obj + 0x1c, 1);
      ctx.mem.writeF32(obj + 0x20, k1);
      ctx.mem.writeF32(obj + 0x24, k2);
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXInitLightSpot_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "angle attenuation a0/a1/a2 (offsets 0x10/0x14/0x18) from a cutoff angle and a spot " +
      "function. The corpus body's seven-case polynomial fit is reproduced",
    service(_gx, ctx) {
      const cutoff = ctx.frame.f64Arg(0);
      const obj = ctx.frame.u32Arg(1) >>> 0;
      let fn = ctx.frame.i32Arg(2);
      // [CORPUS] out-of-range cutoffs fall back to GX_SP_OFF.
      if (cutoff <= 0 || cutoff > 90) fn = 0;
      const cr = Math.cos((cutoff * Math.PI) / 180);
      let a0 = 0;
      let a1 = 0;
      let a2 = 0;
      switch (fn) {
        case 1: // FLAT
          a0 = -1000 * cr;
          a1 = 1000;
          break;
        case 2: // COS
          a1 = 1 / (1 - cr);
          a0 = -cr * a1;
          break;
        case 3: // COS2
          a2 = 1 / (1 - cr);
          a1 = -cr * a2;
          break;
        case 4: { // SHARP
          const d = (1 - cr) * (1 - cr);
          a0 = (cr * (cr - 2)) / d;
          a1 = 2 / d;
          a2 = -1 / d;
          break;
        }
        case 5: { // RING1
          const d = (1 - cr) * (1 - cr);
          a0 = (-4 * cr) / d;
          a1 = (4 * (1 + cr)) / d;
          a2 = -4 / d;
          break;
        }
        case 6: { // RING2
          const d = (1 - cr) * (1 - cr);
          a0 = 1 - (2 * cr * cr) / d;
          a1 = (4 * cr) / d;
          a2 = -2 / d;
          break;
        }
        default:
          a0 = 1;
          break;
      }
      ctx.mem.writeF32(obj + 0x10, a0);
      ctx.mem.writeF32(obj + 0x14, a1);
      ctx.mem.writeF32(obj + 0x18, a2);
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXLoadLightObjImm_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "binds a light object to one of the 8 hardware lights. The id is a BITMASK, not an index: " +
      "gnt4_GXLoadLightObjImm_bl @0x80228600 derives the XF slot as `31 - clz(id)`, which is " +
      "corpus-settled. The whole object is re-read from GC memory so a ROM that mutates the " +
      "struct between Init and Load is followed",
    service(gx, ctx) {
      const objAddr = ctx.frame.u32Arg(0) >>> 0;
      const mask = ctx.frame.u32Arg(1) >>> 0;
      const slot = mask === 0 ? 0 : 31 - Math.clz32(mask);
      const light = gx.state.lights[slot & 7];
      if (!light) return ctx.frame.setRetVoid();
      const f = (o: number): number => ctx.mem.readF32(objAddr + o);
      // [CORPUS] object layout, from the offsets the body streams to XF.
      light.color = readColor(ctx.mem, objAddr + 0x0c);
      light.angleAttn = Float32Array.from([f(0x10), f(0x14), f(0x18)]);
      light.distAttn = Float32Array.from([f(0x1c), f(0x20), f(0x24)]);
      light.position = Float32Array.from([f(0x28), f(0x2c), f(0x30)]);
      light.negDirection = Float32Array.from([f(0x34), f(0x38), f(0x3c)]);
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetChanMatColor_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "the material colour register for a channel. The signature is settled the same way as " +
      "GXSetTevKColor's — the corpus body dereferences its second argument and the ROM call " +
      "site passes an address (see readColor). Channels 0/2 write colour 0, 1/3 write colour 1, " +
      "4/5 write both, which is the corpus body's own dispatch",
    service(gx, ctx) {
      gx.setChannelColor(gx.state.matColors, ctx.frame.i32Arg(0), readColor(ctx.mem, ctx.frame.u32Arg(1)));
      gx.state.matColor = Uint8Array.from(gx.state.matColors[0] as Uint8Array);
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetChanAmbColor_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect: "the ambient colour register for a channel, dispatched exactly as GXSetChanMatColor",
    service(gx, ctx) {
      gx.setChannelColor(gx.state.ambColors, ctx.frame.i32Arg(0), readColor(ctx.mem, ctx.frame.u32Arg(1)));
      gx.state.ambColor = Uint8Array.from(gx.state.ambColors[0] as Uint8Array);
      return ctx.frame.setRetVoid();
    },
  },

  // ==========================================================================
  // Projection helper — rank 39
  // ==========================================================================
  {
    symbol: "gnt4_GXProject_bl",
    tier: "translated",
    retClass: FrameValueClass.VOID,
    effect:
      "object space -> screen space, ported from the repo's own " +
      "research/decomp/generated/pi-port/sdk-shims/gx_stubs.c rather than rewritten. Uses the " +
      "CALLER's matrices and viewport, not the latched ones, exactly as the SDK does",
    service(_gx, ctx) {
      const x = ctx.frame.f64Arg(0);
      const y = ctx.frame.f64Arg(1);
      const z = ctx.frame.f64Arg(2);
      const model = readMtx3x4(ctx.mem, ctx.frame.u32Arg(3));
      const pm = new Float32Array(7);
      for (let i = 0; i < 7; i++) pm[i] = ctx.mem.readF32(ctx.frame.u32Arg(4) + i * 4);
      const vp = new Float32Array(6);
      for (let i = 0; i < 6; i++) vp[i] = ctx.mem.readF32(ctx.frame.u32Arg(5) + i * 4);
      const m = (i: number): number => model[i] ?? 0;
      const ex = m(0) * x + m(1) * y + m(2) * z + m(3);
      const ey = m(4) * x + m(5) * y + m(6) * z + m(7);
      const ez = m(8) * x + m(9) * y + m(10) * z + m(11);
      const p = (i: number): number => pm[i] ?? 0;
      const v = (i: number): number => vp[i] ?? 0;
      let xc: number;
      let yc: number;
      let wc: number;
      const zc = ez * p(5) + p(6);
      if (p(0) === 0) {
        xc = ex * p(1) + ez * p(2);
        yc = ey * p(3) + ez * p(4);
        wc = 1 / -ez;
      } else {
        xc = ex * p(1) + p(2);
        yc = ey * p(3) + p(4);
        wc = 1;
      }
      ctx.mem.writeF32(ctx.frame.u32Arg(6), v(0) + v(2) / 2 + (wc * xc * v(2)) / 2);
      ctx.mem.writeF32(ctx.frame.u32Arg(7), v(1) + v(3) / 2 - (wc * yc * v(3)) / 2);
      ctx.mem.writeF32(ctx.frame.u32Arg(8), v(5) + wc * zc * (v(5) - v(4)));
      return ctx.frame.setRetVoid();
    },
  },

  // ==========================================================================
  // Sync / cache operations
  //
  // These are DECLARED no-ops, not silent ones. On the console they flush
  // caches and synchronize the command pipe; an HLE host that submits
  // immediately has nothing to flush, so "no host-visible effect" is the
  // CORRECT behaviour here — and it is recorded in the call counts and tiered
  // separately so it can never be mistaken for the other two categories.
  // ==========================================================================
  {
    symbol: "gnt4_GXInvalidateVtxCache_bl",
    tier: "declared-nop",
    retClass: FrameValueClass.VOID,
    effect: "vertex-cache invalidation has no host-visible effect",
    service: (_gx, ctx) => ctx.frame.setRetVoid(),
  },
  {
    symbol: "gnt4_GXInvalidateTexAll_bl",
    tier: "declared-nop",
    retClass: FrameValueClass.VOID,
    effect: "texture-cache invalidation has no host-visible effect",
    service: (_gx, ctx) => ctx.frame.setRetVoid(),
  },
  {
    symbol: "gnt4_GXPixModeSync_bl",
    tier: "declared-nop",
    retClass: FrameValueClass.VOID,
    effect: "pixel-mode sync has no host-visible effect",
    service: (_gx, ctx) => ctx.frame.setRetVoid(),
  },
  {
    symbol: "gnt4___GXFlushTextureState_bl",
    tier: "declared-nop",
    retClass: FrameValueClass.VOID,
    effect: "texture-state flush has no host-visible effect",
    service: (_gx, ctx) => ctx.frame.setRetVoid(),
  },
  {
    symbol: "gnt4_GXInitTlutRegion_bl",
    tier: "declared-nop",
    retClass: FrameValueClass.VOID,
    effect:
      "carves a palette region out of texture memory. The host does not model TMEM at all — it " +
      "keeps palettes as objects and binds them by TLUT name (see GXLoadTlut) — so a TMEM " +
      "allocation has no host-visible effect. This is a nop by MODEL, declared as one, not a gap",
    service: (_gx, ctx) => ctx.frame.setRetVoid(),
  },
  {
    symbol: "gnt4_GXEnableTexOffsets_bl",
    tier: "declared-nop",
    retClass: FrameValueClass.VOID,
    effect:
      "enables the per-texcoord line/point sprite offset generators. CONDITIONAL nop: all 16 ROM " +
      "call sites pass (coord, 0, 0) — both generators DISABLED — and disabled offsets have no " +
      "host-visible effect. If either is ever enabled the adapter THROWS, because that is a " +
      "texgen path this host does not implement and silently ignoring it would misplace sprites",
    service(_gx, ctx) {
      const line = ctx.frame.i32Arg(1);
      const point = ctx.frame.i32Arg(2);
      if (line !== 0 || point !== 0) {
        throw new Error(
          `GXEnableTexOffsets(coord ${ctx.frame.i32Arg(0)}, line=${line}, point=${point}) ENABLES a ` +
            `sprite texcoord offset generator, which the HLE host does not implement. Every ROM call ` +
            `site measured in this corpus passes (n, 0, 0); this one does not. Refusing to no-op.`,
        );
      }
      return ctx.frame.setRetVoid();
    },
  },
];

/** Symbols this host implements — the numerator of the coverage figure. */
export const IMPLEMENTED_SYMBOLS: readonly string[] = SPECS.map((s) => s.symbol);

/** What each implemented entry point actually does, and how much. */
export const IMPLEMENTED_EFFECTS: ReadonlyArray<{ symbol: string; tier: GxImplTier; effect: string }> = SPECS.map(
  (s) => ({ symbol: s.symbol, tier: s.tier, effect: s.effect }),
);

/**
 * Coverage split by tier. The honest headline is `translated`: entry points
 * that actually change the frame. `latched` entry points are accepted without
 * being acted on, and reporting them next to translated ones — rather than
 * merged into a single "implemented" figure — is the difference between a
 * coverage number and a coverage claim.
 */
export function gxTieredCoverage(): {
  translated: ReturnType<typeof gxCoverage>;
  translatedAndLatched: ReturnType<typeof gxCoverage>;
  all: ReturnType<typeof gxCoverage>;
  byTier: Record<GxImplTier, number>;
} {
  const of = (tiers: GxImplTier[]): string[] => SPECS.filter((s) => tiers.includes(s.tier)).map((s) => s.symbol);
  const byTier = { translated: 0, latched: 0, "declared-nop": 0 } as Record<GxImplTier, number>;
  for (const s of SPECS) byTier[s.tier] += 1;
  return {
    translated: gxCoverage(of(["translated"])),
    translatedAndLatched: gxCoverage(of(["translated", "latched"])),
    all: gxCoverage(of(["translated", "latched", "declared-nop"])),
    byTier,
  };
}

// =============================================================================
// Registration
// =============================================================================

function adapterFor(gx: GxHost, spec: GxAdapterSpec, gcAddr: number): BridgedCalleeAdapter {
  const entry = gxInventoryEntry(spec.symbol);
  return defineAdapter({
    gcAddr,
    name: spec.symbol,
    evidence: `${GX_EVIDENCE} [rank by game call sites: ${entry?.gameCalls ?? 0}]`,
    evidenceClass: "synthetic",
    retClass: spec.retClass,
    service(ctx) {
      gx.record(spec.symbol);
      return spec.service(gx, ctx);
    },
  });
}

function unimplementedAdapter(gx: GxHost, symbol: string, gcAddr: number): BridgedCalleeAdapter {
  const entry = gxInventoryEntry(symbol);
  return defineAdapter({
    gcAddr,
    name: `${symbol} [UNIMPLEMENTED]`,
    evidence: `not implemented by the GX HLE host; ${entry?.gameCalls ?? 0} static ROM call sites`,
    evidenceClass: "synthetic",
    retClass: FrameValueClass.VOID,
    service(_ctx) {
      gx.unimplementedHits.push(symbol);
      throw new Error(
        `GX entry point ${symbol} is NOT IMPLEMENTED by the HLE host ` +
          `(ROM address 0x${(entry?.romAddr ?? 0).toString(16)}, ${entry?.gameCalls ?? 0} static ROM call sites, ` +
          `${entry?.distinctGameCallers ?? 0} distinct callers). ` +
          `Refusing to no-op: a silent no-op here renders a frame that looks plausible and is wrong. ` +
          `Implement it in packages/rom-runtime/src/gx/adapters.ts or accept the failed frame.`,
      );
    },
  });
}

/**
 * Register the whole GX surface on a host.
 *
 * EVERY entry point in the measured inventory gets an adapter — implemented
 * ones do their work, the rest throw with their name and rank. Nothing in the
 * GX surface can be hit without the ledger and the console saying so.
 *
 * Each adapter is registered at TWO keys:
 *  - the SYNTHETIC key `gcAddressForSymbol(symbol)` produces, which is what the
 *    direct-import bridge edge uses for an address-less `gnt4_*` symbol
 *    (composed.ts), and
 *  - the symbol's REAL GameCube address from the inventory, which is what a
 *    table-miss edge would carry if the ROM ever dispatched a GX function
 *    through a stored function pointer.
 * Binding both means the seam works whichever edge the call arrives on.
 */
export function registerGxAdapters(
  host: { registerAdapter(adapter: BridgedCalleeAdapter): void },
  gx: GxHost,
): { implemented: number; unimplemented: number; registrations: number } {
  let registrations = 0;
  const bind = (adapter: BridgedCalleeAdapter, symbol: string): void => {
    host.registerAdapter(adapter);
    registrations += 1;
    const romAddr = gxInventoryEntry(symbol)?.romAddr;
    if (romAddr && romAddr !== adapter.gcAddr) {
      // Same adapter object at the ROM address too. AdapterRegistry only
      // rejects a DIFFERENT adapter at an occupied key, so this is safe.
      host.registerAdapter({ ...adapter, gcAddr: romAddr >>> 0 });
      registrations += 1;
    }
  };

  const implemented = new Set(IMPLEMENTED_SYMBOLS);
  for (const spec of SPECS) {
    bind(adapterFor(gx, spec, gcAddressForSymbol(spec.symbol).gcAddr), spec.symbol);
  }
  let unimplemented = 0;
  for (const entry of GX_CALL_INVENTORY) {
    if (implemented.has(entry.symbol)) continue;
    unimplemented += 1;
    bind(unimplementedAdapter(gx, entry.symbol, gcAddressForSymbol(entry.symbol).gcAddr), entry.symbol);
  }
  return { implemented: SPECS.length, unimplemented, registrations };
}

/**
 * Bind the write-gather-pipe imports.
 *
 * These are NOT GX entry points — they are the lowering target for the ROM's
 * `DAT_cc008000` stores (see fifo.ts). The assembly gate does not emit them
 * yet, so today only the purpose-built fixture calls them. They are registered
 * as bridged callees at reserved synthetic addresses so that when the gate DOES
 * lower those stores, the seam is already here.
 */
export const WGPIPE_SYMBOLS = [
  "__gf_gx_wgpipe_u8",
  "__gf_gx_wgpipe_u16",
  "__gf_gx_wgpipe_u32",
  "__gf_gx_wgpipe_f32",
] as const;

export function registerWgPipeAdapters(
  host: { registerAdapter(adapter: BridgedCalleeAdapter): void },
  gx: GxHost,
): void {
  const evidence =
    "write-gather-pipe (0xCC008000) lowering target — the ROM's real vertex submission path; " +
    "the assembly gate does not emit these yet (docs/gx-hle-host.md)";
  const define = (symbol: string, write: (value: number) => void, float: boolean): BridgedCalleeAdapter =>
    defineAdapter({
      gcAddr: gcAddressForSymbol(symbol).gcAddr,
      name: symbol,
      evidence,
      evidenceClass: "synthetic",
      retClass: FrameValueClass.VOID,
      service(ctx) {
        gx.record(symbol);
        write(float ? ctx.frame.f32Arg(0) : ctx.frame.u32Arg(0));
        return ctx.frame.setRetVoid();
      },
    });
  host.registerAdapter(define("__gf_gx_wgpipe_u8", (v) => gx.fifo.writeU8(v), false));
  host.registerAdapter(define("__gf_gx_wgpipe_u16", (v) => gx.fifo.writeU16(v), false));
  host.registerAdapter(define("__gf_gx_wgpipe_u32", (v) => gx.fifo.writeU32(v), false));
  host.registerAdapter(define("__gf_gx_wgpipe_f32", (v) => gx.fifo.writeF32(v), true));
}

export { attrName, gxCoverage, GX_CALL_INVENTORY };
