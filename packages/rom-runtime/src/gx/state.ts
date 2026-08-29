// =============================================================================
// state.ts — the GX pipeline state the HLE host tracks.
//
// The ROM programs the Flipper by calling GX entry points that each latch a
// piece of pipeline state, then submits vertices against whatever is latched.
// A host that only forwards draw calls and ignores the latched state draws the
// wrong thing silently, so this class is the seam's memory: every implemented
// GX entry point writes here, and every draw carries a SNAPSHOT of it.
//
// STATUS: SCAFFOLDING. Nothing in this file has trace verification behind it.
// The claim bar for the whole GX path is "framebuffer-equivalent, never
// pixel-identical" (docs/playable-port-design.md V3 note 1) and today the path
// does not even meet that — it has never been compared against a real frame.
// See docs/gx-hle-host.md.
// =============================================================================

import {
  GXAttr,
  GXAttrType,
  GXBlendFactor,
  GXBlendMode,
  GXCompCnt,
  GXCompType,
  GXCompare,
  GXCullMode,
  GXProjectionType,
  GX_IDENTITY_MTX,
  GX_MAX_TEXMAP,
  GX_TEXMAP_NULL,
} from "./enums.js";

/** One attribute's VAT (vertex attribute table) entry. */
export interface GxVatEntry {
  cnt: number;
  type: number;
  /** Fixed-point fractional bits for integer component types. */
  frac: number;
}

/** One attribute's array binding (GXSetArray) for INDEX8/INDEX16 fetch. */
export interface GxArrayBinding {
  /** Base pointer, as a GC address inside the shared arena. */
  base: number;
  /** Stride in bytes between consecutive entries. */
  stride: number;
}

/** A GX texture object as the host models it (GXInitTexObj). */
export interface GxTexObj {
  /** GC address of the GXTexObj struct the ROM handed us. */
  objAddr: number;
  /** GC address of the image data. */
  imageAddr: number;
  width: number;
  height: number;
  /** GXTexFmt as passed by the ROM. Not decoded — see decodedFormat. */
  format: number;
  wrapS: number;
  wrapT: number;
  mipmap: number;
}

/** Immutable snapshot of everything a draw call depends on. */
export interface GxDrawState {
  projection: Float32Array;
  projectionType: number;
  /** The 3x4 position matrix currently selected by GXSetCurrentMtx. */
  posMtx: Float32Array;
  /** The 3x4 normal matrix for the current matrix id, if one was loaded. */
  nrmMtx: Float32Array | null;
  currentMtxId: number;
  viewport: Float32Array;
  scissor: Int32Array;
  cullMode: number;
  zCompareEnable: boolean;
  zFunc: number;
  zUpdate: boolean;
  blendMode: number;
  blendSrc: number;
  blendDst: number;
  colorUpdate: boolean;
  alphaUpdate: boolean;
  numChans: number;
  numTexGens: number;
  numTevStages: number;
  /** Texture bound to each GX_TEXMAP slot, or null. */
  textures: Array<GxTexObj | null>;
  /** TEV stage 0's texmap selection (GXSetTevOrder) — which map the draw uses. */
  tevTexMap: number;
  /** Material colour for channel 0, RGBA 0-255. Only meaningful when
   *  `matSrcVertex` is false (GXSetChanCtrl mat_src == GX_SRC_REG). */
  matColor: Uint8Array;
  /** Ambient colour for channel 0, RGBA 0-255. */
  ambColor: Uint8Array;
  /** GXSetChanCtrl mat_src == GX_SRC_VTX: the fragment colour comes from the
   *  vertex, and the material colour register must NOT be folded in. The
   *  ROM's 2D paths all take this branch. */
  matSrcVertex: boolean;
  /** GXSetChanCtrl's channel-enable bit (lighting on/off for the channel). */
  chanEnabled: boolean;
}

const identity3x4 = (): Float32Array =>
  Float32Array.from([1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0]);

/**
 * The latched GX pipeline state.
 *
 * Every field starts at the SDK's documented reset value where one exists.
 * Where the reset value is unknown the field starts at a value that makes an
 * un-programmed draw visibly wrong rather than plausibly right — the host must
 * never make the ROM's omission look like a working frame.
 */
export class GxState {
  /** Vertex descriptor: attribute id -> GXAttrType. */
  readonly vcd = new Map<number, number>();
  /** Vertex attribute tables, 8 formats x attribute id. */
  readonly vat: Array<Map<number, GxVatEntry>> = Array.from({ length: 8 }, () => new Map());
  /** GXSetArray bindings by attribute id. */
  readonly arrays = new Map<number, GxArrayBinding>();

  /** GX projection coefficients: [type, a, b, c, d, e, f] — the SDK's own
   *  7-float form, identical to the repo's gx_stubs.c layout. */
  projection = Float32Array.from([GXProjectionType.PERSPECTIVE, 1, 0, 1, 0, -1, -1]);
  /** viewport: left, top, width, height, nearZ, farZ. */
  viewport = Float32Array.from([0, 0, 640, 480, 0, 1]);
  /** scissor: x, y, w, h. */
  scissor = Int32Array.from([0, 0, 640, 480]);

  /** Position/normal matrix memory, keyed by GX_PNMTX* row id. */
  readonly posMtxMem = new Map<number, Float32Array>();
  readonly nrmMtxMem = new Map<number, Float32Array>();
  readonly texMtxMem = new Map<number, Float32Array>();
  currentMtxId = 0;

  cullMode: number = GXCullMode.BACK;
  zCompareEnable = true;
  zFunc: number = GXCompare.LEQUAL;
  zUpdate = true;
  blendMode: number = GXBlendMode.NONE;
  blendSrc: number = GXBlendFactor.ONE;
  blendDst: number = GXBlendFactor.ZERO;
  colorUpdate = true;
  alphaUpdate = true;

  numChans = 0;
  numTexGens = 0;
  numTevStages = 1;
  tevTexMap: number = GX_TEXMAP_NULL;

  matColor = Uint8Array.from([255, 255, 255, 255]);
  ambColor = Uint8Array.from([0, 0, 0, 255]);
  /** Defaults to VERTEX because that is what every ROM draw path measured in
   *  this corpus selects (`GXSetChanCtrl(4, 0, 1, 1, 0, 0, 2)`), so an
   *  un-programmed draw behaves like the ROM's common case rather than
   *  multiplying in a register colour nothing set. */
  matSrcVertex = true;
  chanEnabled = false;

  /** Texture objects bound to each GX_TEXMAP slot. */
  readonly textures: Array<GxTexObj | null> = Array.from({ length: GX_MAX_TEXMAP }, () => null);
  /** Texture objects the ROM has initialized, keyed by their GXTexObj address. */
  readonly texObjs = new Map<number, GxTexObj>();

  constructor() {
    this.posMtxMem.set(GX_IDENTITY_MTX, identity3x4());
    this.posMtxMem.set(0, identity3x4());
  }

  /** GXClearVtxDesc: every attribute back to GX_NONE. */
  clearVtxDesc(): void {
    this.vcd.clear();
  }

  /** GXSetVtxDesc(attr, type). */
  setVtxDesc(attr: number, type: number): void {
    if (type === GXAttrType.NONE) this.vcd.delete(attr);
    else this.vcd.set(attr, type);
  }

  /** GXSetVtxAttrFmt(vtxfmt, attr, cnt, type, frac). */
  setVtxAttrFmt(vtxfmt: number, attr: number, cnt: number, type: number, frac: number): void {
    const table = this.vat[vtxfmt & 7];
    if (table) table.set(attr, { cnt, type, frac });
  }

  /**
   * The VAT entry the FIFO decoder should use for `attr` in format `vtxfmt`.
   * Returns null when the ROM never programmed one — the decoder then raises a
   * loud error instead of assuming a default, because assuming here means
   * mis-sizing the stream and silently drawing garbage.
   */
  vatEntry(vtxfmt: number, attr: number): GxVatEntry | null {
    return this.vat[vtxfmt & 7]?.get(attr) ?? null;
  }

  /** GXSetProjection(mtx, type) — the SDK's own coefficient packing. */
  setProjection(mtx: Float32Array | number[], type: number): void {
    const m = mtx;
    const p = this.projection;
    p[0] = type;
    if (type === GXProjectionType.ORTHOGRAPHIC) {
      p[1] = m[0] as number;
      p[2] = m[3] as number;
      p[3] = m[5] as number;
      p[4] = m[7] as number;
      p[5] = m[10] as number;
      p[6] = m[11] as number;
    } else {
      p[1] = m[0] as number;
      p[2] = m[2] as number;
      p[3] = m[5] as number;
      p[4] = m[6] as number;
      p[5] = m[10] as number;
      p[6] = m[11] as number;
    }
  }

  /** GXLoadPosMtxImm(mtx, id). */
  loadPosMtx(id: number, mtx: Float32Array): void {
    this.posMtxMem.set(id, mtx);
  }
  /** GXLoadNrmMtxImm(mtx, id). */
  loadNrmMtx(id: number, mtx: Float32Array): void {
    this.nrmMtxMem.set(id, mtx);
  }
  /** GXLoadTexMtxImm(mtx, id, type). */
  loadTexMtx(id: number, mtx: Float32Array): void {
    this.texMtxMem.set(id, mtx);
  }

  /** The position matrix a draw will transform through. */
  currentPosMtx(): Float32Array {
    return this.posMtxMem.get(this.currentMtxId) ?? this.posMtxMem.get(GX_IDENTITY_MTX) ?? identity3x4();
  }

  /** Freeze everything a draw call depends on. */
  snapshot(): GxDrawState {
    return {
      projection: Float32Array.from(this.projection),
      projectionType: this.projection[0] ?? GXProjectionType.PERSPECTIVE,
      posMtx: Float32Array.from(this.currentPosMtx()),
      nrmMtx: this.nrmMtxMem.has(this.currentMtxId)
        ? Float32Array.from(this.nrmMtxMem.get(this.currentMtxId) as Float32Array)
        : null,
      currentMtxId: this.currentMtxId,
      viewport: Float32Array.from(this.viewport),
      scissor: Int32Array.from(this.scissor),
      cullMode: this.cullMode,
      zCompareEnable: this.zCompareEnable,
      zFunc: this.zFunc,
      zUpdate: this.zUpdate,
      blendMode: this.blendMode,
      blendSrc: this.blendSrc,
      blendDst: this.blendDst,
      colorUpdate: this.colorUpdate,
      alphaUpdate: this.alphaUpdate,
      numChans: this.numChans,
      numTexGens: this.numTexGens,
      numTevStages: this.numTevStages,
      textures: this.textures.slice(),
      tevTexMap: this.tevTexMap,
      matColor: Uint8Array.from(this.matColor),
      ambColor: Uint8Array.from(this.ambColor),
      matSrcVertex: this.matSrcVertex,
      chanEnabled: this.chanEnabled,
    };
  }

  /**
   * The set of attributes a vertex carries, in the FIFO's fixed submission
   * order (GXAttr id order — the hardware's order, not the ROM's call order).
   */
  activeAttributes(): Array<{ attr: number; type: number }> {
    return [...this.vcd.entries()]
      .filter(([, type]) => type !== GXAttrType.NONE)
      .sort((a, b) => a[0] - b[0])
      .map(([attr, type]) => ({ attr, type }));
  }
}

export { GXAttr, GXAttrType, GXCompCnt, GXCompType };
