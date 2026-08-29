// =============================================================================
// enums.ts — the GX constants the HLE host decodes.
//
// PROVENANCE, stated per group. Two different kinds of authority appear in
// this file and they are NOT interchangeable:
//
//   [CORPUS]  the value is observable in THIS GAME's decompiled SDK
//             (research/decomp/ghidra-export/chunk_0066.c / chunk_0067.c) or
//             at a ROM call site. Grounded in the shipped binary.
//   [SDK]     the value is the documented GameCube SDK constant and could NOT
//             be settled from the corpus — the decompiled bodies mask these
//             fields into packed hardware registers, which hides the
//             numbering. Stated as an ASSUMPTION: a wrong one here produces a
//             wrong frame, not a loud failure.
//
// The distinction is the point. The GX path has no trace verification behind
// it (docs/gx-hle-host.md), so a reader must be able to tell which constants
// are evidence and which are educated defaults.
// =============================================================================

/**
 * Vertex attribute ids (GXAttr). [CORPUS]
 *
 * Read out of gnt4_GXSetVtxDesc_bl's own switch (chunk_0066.c @ 0x80225894),
 * which dispatches on the attribute id into distinct bit fields of the two VCD
 * words: 0 -> PNMTXIDX (1 bit), 1..8 -> TEXnMTXIDX (1 bit each), 9 -> POS
 * (2 bits), 10 -> NRM, 0xb/0xc -> CLR0/CLR1, 0xd..0x14 -> TEX0..TEX7, and
 * 0x19 -> NBT, which shares NRM's field and is mutually exclusive with it.
 * gnt4_GXSetArray's `(char)param_1 - 9` array-slot arithmetic independently
 * confirms 9 is the first array-backed attribute.
 */
export enum GXAttr {
  PNMTXIDX = 0,
  TEX0MTXIDX = 1,
  TEX7MTXIDX = 8,
  POS = 9,
  NRM = 10,
  CLR0 = 11,
  CLR1 = 12,
  TEX0 = 13,
  TEX1 = 14,
  TEX2 = 15,
  TEX3 = 16,
  TEX4 = 17,
  TEX5 = 18,
  TEX6 = 19,
  TEX7 = 20,
  POS_MTX_ARRAY = 21,
  NRM_MTX_ARRAY = 22,
  TEX_MTX_ARRAY = 23,
  LIGHT_ARRAY = 24,
  NBT = 25,
  MAX_ATTR = 26,
  NULL_ATTR = 0xff,
}

/**
 * How an attribute reaches the GPU (GXAttrType). [CORPUS]
 *
 * Settled three independent ways:
 *  - gnt4_GXClearVtxDesc_bl zeroes the descriptor and then forces the POS
 *    field back to 1, so 0 = NONE and 1 = DIRECT;
 *  - zz_0050bf4_ passes 2 alongside GXSetArray and then writes exactly ONE
 *    byte per attribute per vertex, so 2 = INDEX8;
 *  - the display-list interpreter branches
 *    `if (desc == 3) { 16-bit store } else if (desc == 2) { 8-bit store }`
 *    (chunk_0071.c:2281-2290), so 3 = INDEX16.
 */
export enum GXAttrType {
  NONE = 0,
  DIRECT = 1,
  INDEX8 = 2,
  INDEX16 = 3,
}

/**
 * Component counts (GXCompCnt) — meaning depends on the attribute. [CORPUS]
 *
 * POS: zz_0027c34_ uses cnt 0 followed by two 16-bit FIFO stores per vertex,
 * and zz_0050f80_ uses cnt 1 followed by three 32-bit stores; the indexed
 * paths corroborate with GXSetArray strides of 8 (2 x f32) and 0xc (3 x f32).
 * NRM: gnt4_GXSetVtxAttrFmt_bl's NRM case special-cases cnt == 2 (the
 * three-index NBT form) and otherwise stores `cnt & 1`.
 * CLR: every ROM call site uses cnt 1 with a 4-byte colour.
 */
export enum GXCompCnt {
  POS_XY = 0,
  POS_XYZ = 1,
  NRM_XYZ = 0,
  NRM_NBT = 1,
  NRM_NBT3 = 2,
  CLR_RGB = 0,
  CLR_RGBA = 1,
  TEX_S = 0,
  TEX_ST = 1,
}

/**
 * Component types for POS/NRM/TEX (GXCompType).
 *
 * S16 (3) and F32 (4) are [CORPUS]: they are the only two the ROM uses and
 * both are confirmed by the FIFO store widths that follow them — two 16-bit
 * stores after `GXSetVtxAttrFmt(0, 9, 0, 3, 0)`, three 32-bit stores after
 * `(0, 9, 1, 4, 0)`. U8/S8/U16 (0/1/2) are [SDK]: no ROM call site exercises
 * them. The FIFO decoder sizes the stream from these values, so a wrong one
 * desynchronizes every following vertex.
 */
export enum GXCompType {
  U8 = 0,
  S8 = 1,
  U16 = 2,
  S16 = 3,
  F32 = 4,
}

/**
 * Component types for CLR0/CLR1 (GXCompType, colour overload). [CORPUS]
 *
 * All six confirmed by the display-list interpreter's per-type byte widths
 * (chunk_0071.c:2292-2325): type 0->2, 1->3, 2->4, 3->2, 4->3, 5->4 bytes,
 * which is exactly RGB565/RGB8/RGBX8/RGBA4/RGBA6/RGBA8. Every ROM game-code
 * call site uses 5 (RGBA8) and writes one 32-bit word per vertex.
 */
export enum GXColorCompType {
  RGB565 = 0,
  RGB8 = 1,
  RGBX8 = 2,
  RGBA4 = 3,
  RGBA6 = 4,
  RGBA8 = 5,
}

/**
 * Primitive types (GXPrimitive).
 *
 *  [CORPUS] 0x80 QUADS         zz_0027c34_ emits the 4 corners of a rectangle
 *  [CORPUS] 0x90 TRIANGLES     chunk_0067.c:2661 emits exactly 3 pos+nrm pairs
 *  [CORPUS] 0x98 TRIANGLESTRIP chunk_0067.c:2801 emits 2 verts per ring step
 *  [CORPUS] 0xa0 TRIANGLEFAN   chunk_0067.c:2891 emits centre + ring + close
 *  [PARTIAL] 0xb0              a LINE primitive by usage (N unpaired vertices,
 *                              zz_0050bf4_); strip-vs-loop is NOT determinable
 *                              from the corpus. LINESTRIP is the SDK's value.
 *  [SDK]    0xa8, 0xb8         absent from the export entirely.
 *
 * gnt4_GXBegin_bl's own packing is [CORPUS]: the display-list interpreter
 * calls `GXBegin(b & 0xf8, b & 7, n)`, so the primitive occupies bits 3-7 and
 * the vertex format bits 0-2 of one command byte.
 */
export enum GXPrimitive {
  QUADS = 0x80,
  TRIANGLES = 0x90,
  TRIANGLESTRIP = 0x98,
  TRIANGLEFAN = 0xa0,
  LINES = 0xa8,
  LINESTRIP = 0xb0,
  POINTS = 0xb8,
}

/**
 * Cull modes (GXCullMode). [CORPUS]
 *
 * gnt4_GXSetCullMode_bl swaps 1 and 2 on the way to the genmode register and
 * passes 0 and 3 through unchanged — a swap that is only meaningful if 1 and 2
 * are FRONT and BACK while 0 and 3 are NONE and ALL. ROM call sites pass 2 for
 * culled 3D geometry and 0 for 2D overlays.
 */
export enum GXCullMode {
  NONE = 0,
  FRONT = 1,
  BACK = 2,
  ALL = 3,
}

/**
 * Depth/alpha compare functions (GXCompare). [SDK — only two values observed]
 *
 * gnt4_GXSetZMode_bl masks the function with 7 and stores it; neither the body
 * nor any call site pins the numbering down. The ROM uses exactly two
 * literals: 7 for always-draw 2D overlays and 3 for depth-tested 3D geometry,
 * consistent with ALWAYS and LEQUAL below but not proof of the other six.
 */
export enum GXCompare {
  NEVER = 0,
  LESS = 1,
  EQUAL = 2,
  LEQUAL = 3,
  GREATER = 4,
  NEQUAL = 5,
  GEQUAL = 6,
  ALWAYS = 7,
}

/**
 * Blend modes (GXBlendMode). [CORPUS]
 *
 * gnt4_GXSetBlendMode_bl derives three distinct register bits from the type
 * argument with countLeadingZeros expressions that are set exactly when the
 * type is 1, 2 and 3 respectively — so 0 = none, 1 = blend, 2 = logic,
 * 3 = subtract.
 */
export enum GXBlendMode {
  NONE = 0,
  BLEND = 1,
  LOGIC = 2,
  SUBTRACT = 3,
}

/**
 * Blend factors (GXBlendFactor). [SDK — NOT settled from the corpus]
 *
 * gnt4_GXSetBlendMode_bl only masks the factors with 7 and shifts them into
 * the register, so the numbering is invisible. The ROM's literal pairs are
 * (4, 5) for ordinary alpha blending and (1, 0); the remaining sets come from
 * a 16-byte-stride table at DAT_802d2d44 that is not in the C export. The
 * values below are the documented SDK ones, and a wrong one blends the frame
 * incorrectly with no failure signal at all.
 */
export enum GXBlendFactor {
  ZERO = 0,
  ONE = 1,
  SRCCLR = 2,
  INVSRCCLR = 3,
  SRCALPHA = 4,
  INVSRCALPHA = 5,
  DSTALPHA = 6,
  INVDSTALPHA = 7,
}

/**
 * Projection kind (GXProjectionType). [CORPUS]
 *
 * gnt4_GXSetProjection_bl takes a full Mtx44 and branches on `param_2 == 1` to
 * read m[0][3]/m[1][3] (an orthographic matrix's translation column) versus
 * m[0][2]/m[1][2] (the perspective terms). Corroborated at call sites: the 2D
 * paths pass type 1 and then draw a 640x448 screen-space quad in raw pixel
 * coordinates; the 3D paths pass type 0.
 */
export enum GXProjectionType {
  PERSPECTIVE = 0,
  ORTHOGRAPHIC = 1,
}

/**
 * Texture map slots (GXTexMapID). [CORPUS]
 *
 * gnt4_GXLoadTexObjPreLoaded_bl indexes six parallel byte tables that are 8
 * entries apart using the map id, so the id range is 0..7. The 0xff sentinel
 * and the 0x100 "texture disabled" flag come straight out of
 * gnt4_GXSetTevOrder_bl, which strips 0x100 and treats 0xff as "no texture".
 */
export const GX_TEXMAP_NULL = 0xff;
export const GX_TEX_DISABLE = 0x100;
export const GX_MAX_TEXMAP = 8;

/**
 * Colour channels (GXChannelID). [CORPUS]
 *
 * gnt4_GXSetChanCtrl_bl computes its XF register as `(chan & 3) + 0x100e` and
 * then, for chan 4, ALSO writes 0x1010, and for chan 5 also 0x1011 — i.e. 4
 * and 5 are the combined colour+alpha channels. That is what makes the `4` in
 * the ROM's ubiquitous `GXSetTevOrder(0, 0xff, 0xff, 4)` mean COLOR0A0.
 */
export enum GXChannelID {
  COLOR0 = 0,
  COLOR1 = 1,
  ALPHA0 = 2,
  ALPHA1 = 3,
  COLOR0A0 = 4,
  COLOR1A1 = 5,
  NULL_CHAN = 0xff,
}

/**
 * Channel colour source (GXColorSrc). [CORPUS]
 *
 * gnt4_GXSetChanCtrl_bl stores `amb_src & 1` and `mat_src & 1` as single bits.
 * The ROM's unlit 2D path passes 1 for both while feeding CLR0 through the
 * vertex descriptor; its lit path passes 0 for both and immediately calls
 * GXSetChanAmbColor/GXSetChanMatColor. So 0 = register, 1 = vertex.
 */
export enum GXColorSrc {
  REGISTER = 0,
  VERTEX = 1,
}

/**
 * Position/normal matrix memory ids are ROW indices into matrix memory, three
 * rows apart. [CORPUS]
 *
 * gnt4_GXLoadPosMtxImm_bl emits `id << 2 | 0xb0000` — twelve words to XF
 * address id*4 — so one 3x4 matrix occupies 3 id units. gnt4_GXSetCurrentMtx_bl
 * masks the id with 0x3f, giving the 0..63 row range.
 */
export const GX_PNMTX_STRIDE = 3;
export const GX_MAX_PNMTX_ID = 63;

/**
 * Texture matrix memory ids. [CORPUS]
 *
 * gnt4_GXLoadTexMtxImm_bl maps ids below 0x40 to XF address id*4 (the same
 * matrix memory as position matrices) and ids at or above 0x40 to
 * (id - 0x40)*4 + 0x500 (the dual-texture region). Observed ids in the ROM:
 * 0x1e, 0x21, 0x3c, 0x7d. GX_TEXMTX0 == 30 == 0x1e is therefore corpus-
 * corroborated; GX_IDENTITY == 60 == 0x3c is the last 3x4 slot in the 64-row
 * region, which the arithmetic 0x3c*4 + 12 == 256 confirms exactly fills it.
 */
export const GX_TEXMTX0 = 30;
export const GX_IDENTITY_MTX = 60;
/** Ids at or above this land in the dual-texture matrix region. [CORPUS] */
export const GX_DUALMTX_BASE = 0x40;

/** Human name for a primitive byte, for diagnostics and loud errors. */
export function primitiveName(value: number): string {
  return GXPrimitive[value] ?? `GX_PRIM_0x${(value & 0xff).toString(16)}`;
}

/** Human name for an attribute id, for diagnostics and loud errors. */
export function attrName(value: number): string {
  if (value >= GXAttr.TEX0 && value <= GXAttr.TEX7) return `GX_VA_TEX${value - GXAttr.TEX0}`;
  if (value >= GXAttr.TEX0MTXIDX && value <= GXAttr.TEX7MTXIDX) return `GX_VA_TEX${value - GXAttr.TEX0MTXIDX}MTXIDX`;
  return GXAttr[value] ? `GX_VA_${GXAttr[value]}` : `GX_VA_0x${(value & 0xff).toString(16)}`;
}

/**
 * Byte size of one DIRECT component group, given the attribute's VAT entry.
 *
 * Returns null when the combination is one the host does not decode — the
 * caller must then raise a LOUD unimplemented error naming the attribute and
 * must never guess a size, because a wrong size desynchronizes the whole FIFO
 * stream and every subsequent vertex silently becomes garbage.
 */
export function directComponentBytes(attr: number, cnt: number, type: number): number | null {
  const scalarBytes = (t: number): number | null => {
    switch (t) {
      case GXCompType.U8:
      case GXCompType.S8:
        return 1;
      case GXCompType.U16:
      case GXCompType.S16:
        return 2;
      case GXCompType.F32:
        return 4;
      default:
        return null;
    }
  };
  if (attr === GXAttr.POS) {
    const n = cnt === GXCompCnt.POS_XY ? 2 : cnt === GXCompCnt.POS_XYZ ? 3 : null;
    const s = scalarBytes(type);
    return n === null || s === null ? null : n * s;
  }
  if (attr === GXAttr.NRM) {
    const n = cnt === GXCompCnt.NRM_XYZ ? 3 : cnt === GXCompCnt.NRM_NBT ? 9 : null;
    const s = scalarBytes(type);
    return n === null || s === null ? null : n * s;
  }
  if (attr >= GXAttr.TEX0 && attr <= GXAttr.TEX7) {
    const n = cnt === GXCompCnt.TEX_S ? 1 : cnt === GXCompCnt.TEX_ST ? 2 : null;
    const s = scalarBytes(type);
    return n === null || s === null ? null : n * s;
  }
  if (attr === GXAttr.CLR0 || attr === GXAttr.CLR1) {
    switch (type) {
      case GXColorCompType.RGB565:
        return 2;
      case GXColorCompType.RGB8:
        return 3;
      case GXColorCompType.RGBX8:
        return 4;
      case GXColorCompType.RGBA4:
        return 2;
      case GXColorCompType.RGBA6:
        return 3;
      case GXColorCompType.RGBA8:
        return 4;
      default:
        return null;
    }
  }
  if (attr === GXAttr.PNMTXIDX || (attr >= GXAttr.TEX0MTXIDX && attr <= GXAttr.TEX7MTXIDX)) {
    return 1;
  }
  return null;
}
