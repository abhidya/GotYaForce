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
  GX_MAX_TEXMAP,
  GX_TEXMAP_NULL,
  GX_TEX_DISABLE,
  attrName,
} from "./enums.js";
import { GxFifo } from "./fifo.js";
import { GX_CALL_INVENTORY, gxCoverage, gxInventoryEntry } from "./inventory.generated.js";
import { GxState } from "./state.js";

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
    tier: "latched",
    retClass: FrameValueClass.VOID,
    effect:
      "stores the 3x3 part of a 3x4 into normal-matrix memory. Latched only: the backend does " +
      "not light, so normals are never transformed",
    service(gx, ctx) {
      gx.state.loadNrmMtx(ctx.frame.i32Arg(1), readMtx3x4(ctx.mem, ctx.frame.u32Arg(0)));
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXLoadTexMtxImm_bl",
    tier: "latched",
    retClass: FrameValueClass.VOID,
    effect:
      "stores a texture matrix (arg2 selects the 3x4 vs 2x4 form). Latched only: texgen is not " +
      "evaluated, so it never reaches a texcoord",
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
      "reads the channel-enable bit and the material colour SOURCE. mat_src decides whether the " +
      "material colour register participates at all, so getting it wrong tints every 2D draw; " +
      "the lighting functions themselves are not evaluated and the backend says so per draw",
    service(gx, ctx) {
      // [CORPUS] GXSetChanCtrl(chan, enable, amb_src, mat_src, light_mask,
      // diff_fn, attn_fn) — gnt4_GXSetChanCtrl_bl @0x80228898.
      gx.state.chanEnabled = (ctx.frame.i32Arg(1) & 1) !== 0;
      gx.state.matSrcVertex = (ctx.frame.i32Arg(3) & 1) === GXColorSrc.VERTEX;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetNumChans_bl",
    tier: "latched",
    retClass: FrameValueClass.VOID,
    effect: "colour-channel count. Latched only: per-vertex lighting is not evaluated",
    service(gx, ctx) {
      gx.state.numChans = ctx.frame.i32Arg(0) & 7;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetNumTexGens_bl",
    tier: "latched",
    retClass: FrameValueClass.VOID,
    effect: "texcoord-generator count. Latched only: texgen is not evaluated",
    service(gx, ctx) {
      gx.state.numTexGens = ctx.frame.i32Arg(0) & 0xf;
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetNumTevStages_bl",
    tier: "latched",
    retClass: FrameValueClass.VOID,
    effect:
      "TEV stage count (1-based). Latched only: the TEV combiner is not translated, and the " +
      "backend reports any draw asking for more than one stage",
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
    tier: "latched",
    retClass: FrameValueClass.VOID,
    effect:
      "records a texture object's geometry/format. Latched only: no GameCube texture format is " +
      "decoded and nothing is uploaded to the GPU",
    service(gx, ctx) {
      const objAddr = ctx.frame.u32Arg(0) >>> 0;
      gx.state.texObjs.set(objAddr, {
        objAddr,
        imageAddr: ctx.frame.u32Arg(1) >>> 0,
        width: ctx.frame.u32Arg(2) & 0xffff,
        height: ctx.frame.u32Arg(3) & 0xffff,
        format: ctx.frame.i32Arg(4),
        wrapS: ctx.frame.i32Arg(5) & 3,
        wrapT: ctx.frame.i32Arg(6) & 3,
        mipmap: ctx.frame.i32Arg(7),
      });
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXLoadTexObj_bl",
    tier: "latched",
    retClass: FrameValueClass.VOID,
    effect:
      "binds a recorded texture object to a GX_TEXMAP slot (0..7). Latched only: sampling is not " +
      "implemented, and the backend reports every draw whose TEV stage selects a texmap",
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
  // TEV wiring — ranks 4, 16
  // ==========================================================================
  {
    symbol: "gnt4_GXSetTevOrder_bl",
    tier: "latched",
    retClass: FrameValueClass.VOID,
    effect:
      "records stage 0's texmap selection so the backend can report the missing sampling. " +
      "Argument order (stage, coord, map, color) is corpus-derived from which field carries the " +
      "0x100 texture-disable flag; GX_TEXMAP_NULL is 0xff",
    service(gx, ctx) {
      if (ctx.frame.i32Arg(0) === 0) {
        const map = ctx.frame.u32Arg(2);
        gx.state.tevTexMap = map === GX_TEXMAP_NULL || (map & GX_TEX_DISABLE) !== 0 ? GX_TEXMAP_NULL : map & 7;
      }
      return ctx.frame.setRetVoid();
    },
  },
  {
    symbol: "gnt4_GXSetTevOp_bl",
    tier: "latched",
    retClass: FrameValueClass.VOID,
    effect: "TEV stage op. Latched only: the combiner is not translated to a shader",
    service(_gx, ctx) {
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
