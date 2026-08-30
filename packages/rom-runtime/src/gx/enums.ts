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

// =============================================================================
// TEV — the programmable fixed-function fragment combiner.
//
// Everything below was settled against the decompiled SDK bodies in
// research/decomp/ghidra-export/chunk_0067.c, which are unusually generous
// here: they pack their arguments straight into the hardware's BP registers,
// so the FIELD WIDTHS, the FIELD POSITIONS and the ARGUMENT ORDER are all
// directly readable. What the bodies cannot show is what a given field VALUE
// means to the silicon — that part stays [SDK], and it is labelled per enum.
// =============================================================================

/**
 * TEV colour-combiner input selectors (GXTevColorArg).
 * [SDK numbering, CORPUS width, CORPUS-corroborated by usage]
 *
 * WIDTH IS CORPUS: gnt4_GXSetTevColorIn_bl @0x80229c38 packs its four
 * arguments as `d & 0xf | (c & 0xf) << 4 | (b & 0xf) << 8 | (a & 0xf) << 0xc`,
 * so each selector is exactly 4 bits (16 possible values) and the argument
 * order is (stage, a, b, c, d) with `a` in the highest field. Both facts are
 * read off the shipped binary, not assumed.
 *
 * NUMBERING IS SDK, corroborated by the ROM's own 4-stage program in
 * chunk_0003.c: `GXSetTevColorIn(0, 0xf, 8, 0xe, 2)` pairs one-for-one with
 * `GXSetTevAlphaIn(0, 7, 4, 6, 1)` — ZERO/ZERO, TEXC/TEXA, KONST/KONST,
 * C0/A0 — across two enums with DIFFERENT widths (4-bit vs 3-bit). That the
 * documented values line up in all four positions across both enums is strong
 * corroboration, but it is not proof: no captured frame has confirmed it.
 */
export enum GXTevColorArg {
  CPREV = 0,
  APREV = 1,
  C0 = 2,
  A0 = 3,
  C1 = 4,
  A1 = 5,
  C2 = 6,
  A2 = 7,
  TEXC = 8,
  TEXA = 9,
  RASC = 10,
  RASA = 11,
  ONE = 12,
  HALF = 13,
  KONST = 14,
  ZERO = 15,
}

/**
 * TEV alpha-combiner input selectors (GXTevAlphaArg).
 * [SDK numbering, CORPUS width]
 *
 * gnt4_GXSetTevAlphaIn_bl @0x80229c7c packs with `& 7` at shifts 4/7/10/13 —
 * 3-bit fields, argument order (stage, a, b, c, d) with `a` highest, and the
 * low nibble left alone because it holds the swap-mode selectors.
 */
export enum GXTevAlphaArg {
  APREV = 0,
  A0 = 1,
  A1 = 2,
  A2 = 3,
  TEXA = 4,
  RASA = 5,
  KONST = 6,
  ZERO = 7,
}

/**
 * TEV combiner operations (GXTevOp).
 * [CORPUS for ADD/SUB and for the compare-op ENCODING; SDK for which
 *  comparison each compare value names]
 *
 * gnt4_GXSetTevColorOp_bl @0x80229cc0 branches on `op < 2`: values 0 and 1
 * take the ordinary path where bias and scale are the caller's, and the op's
 * low bit becomes the register's subtract bit. So **ADD = 0 and SUB = 1 are
 * corpus-settled**. Values >= 2 force the bias field to 3 (`| 0x30000`) and
 * put `op & 6` into the scale field — which is exactly how the hardware
 * encodes the compare ops, so the compare BLOCK is corpus-settled too. Which
 * of the four comparison widths `op & 6` selects (R8 / GR16 / BGR24 / RGB8)
 * is [SDK]: the field's meaning lives in the silicon, not in this body.
 */
export enum GXTevOp {
  ADD = 0,
  SUB = 1,
  COMP_R8_GT = 2,
  COMP_R8_EQ = 3,
  COMP_GR16_GT = 4,
  COMP_GR16_EQ = 5,
  COMP_BGR24_GT = 6,
  COMP_BGR24_EQ = 7,
  COMP_RGB8_GT = 8,
  COMP_RGB8_EQ = 9,
}
/** Alpha aliases for the two 8-bit compare ops. [SDK] */
export const GX_TEV_COMP_A8_GT = GXTevOp.COMP_RGB8_GT;
export const GX_TEV_COMP_A8_EQ = GXTevOp.COMP_RGB8_EQ;

/**
 * TEV bias (GXTevBias) — 2-bit field at register bits 16-17. [CORPUS width,
 * SDK meaning]
 *
 * gnt4_GXSetTevColorOp_bl writes `(bias & 3) << 0x10`. Value 3 is reserved by
 * the hardware for "this stage is a compare op", which the same body confirms
 * by forcing it (`| 0x30000`) on the compare path — so only 0/1/2 are ever
 * meaningful biases, and that bound IS corpus-settled.
 */
export enum GXTevBias {
  ZERO = 0,
  ADDHALF = 1,
  SUBHALF = 2,
  /** Not a bias: the hardware's compare-op marker. [CORPUS] */
  COMPARE = 3,
}

/**
 * TEV output scale (GXTevScale) — 2-bit field at register bits 20-21.
 * [CORPUS width, SDK meaning]
 */
export enum GXTevScale {
  SCALE_1 = 0,
  SCALE_2 = 1,
  SCALE_4 = 2,
  DIVIDE_2 = 3,
}

/**
 * TEV output registers (GXTevRegID) — 2-bit field at register bits 22-23.
 * [CORPUS width and identity, SDK ordering]
 *
 * gnt4_GXSetTevColorOp_bl writes `(out_reg & 3) << 0x16`, so there are exactly
 * four. gnt4_GXSetTevColor_bl @0x80229d90 addresses them as
 * `(reg * 2 + 0xe0)` / `(reg * 2 + 0xe1)` BP register pairs — two registers
 * per colour, RA then BG — which independently confirms the count and that
 * register 0 is the first of the bank. That register 0 is the one the TEV
 * uses as its running result (GX_TEVPREV) is [SDK].
 */
export enum GXTevRegID {
  TEVPREV = 0,
  TEVREG0 = 1,
  TEVREG1 = 2,
  TEVREG2 = 3,
}

/**
 * The five canned TEV programs GXSetTevOp installs (GXTevMode).
 * [CORPUS count and stage rule; CORPUS-corroborated for MODULATE and PASSCLR;
 *  SDK for DECAL/BLEND/REPLACE]
 *
 * gnt4_GXSetTevOp_bl @0x80229bac indexes two pairs of tables by `mode * 4`,
 * and the two pairs are 0x14 = 20 = 5 entries apart, so **there are exactly 5
 * modes** — corpus-settled. The body also branches on `stage == 0` to pick the
 * first pair, which is the SDK's documented rule that stage 0 combines against
 * the RASTERIZED colour while later stages combine against the previous
 * stage's output; that branch is corpus-settled too.
 *
 * Mode 0 and mode 4 are corroborated by ROM usage: mode 4 appears only
 * alongside `GXSetTevOrder(stage, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, ...)`
 * (7 sites) — a mode that ignores the texture, i.e. PASSCLR — and mode 0 only
 * alongside a real texmap (6 sites), i.e. MODULATE. The table CONTENTS live at
 * DAT_803aad30/0x803aad58 which are not in the C export, so the three
 * remaining modes are expanded from the documented SDK definition.
 */
export enum GXTevMode {
  MODULATE = 0,
  DECAL = 1,
  BLEND = 2,
  REPLACE = 3,
  PASSCLR = 4,
}

/**
 * Konstant-colour selector for a TEV stage (GXTevKColorSel).
 * [CORPUS width, SDK numbering, CORPUS-corroborated by usage]
 *
 * gnt4_GXSetTevKColorSel_bl @0x80229efc writes a 5-bit field (`& 0x1f`) into
 * the KSEL register — bits 4-8 for an even stage, 14-18 for an odd one — so
 * the selector space is 32 wide. The ROM's 4-stage program selects 0xc, 0xd,
 * 0xe, 0xf for stages 0..3 while selecting 0x1c, 0x1d, 0x1e, 0x1f for the
 * same stages' ALPHA konstants, which is exactly the documented
 * "K0..K3 rgb" / "K0..K3 alpha" pair of runs.
 */
export enum GXTevKColorSel {
  CONST_1 = 0x00,
  CONST_7_8 = 0x01,
  CONST_3_4 = 0x02,
  CONST_5_8 = 0x03,
  CONST_1_2 = 0x04,
  CONST_3_8 = 0x05,
  CONST_1_4 = 0x06,
  CONST_1_8 = 0x07,
  K0 = 0x0c,
  K1 = 0x0d,
  K2 = 0x0e,
  K3 = 0x0f,
  K0_R = 0x10,
  K1_R = 0x11,
  K2_R = 0x12,
  K3_R = 0x13,
  K0_G = 0x14,
  K1_G = 0x15,
  K2_G = 0x16,
  K3_G = 0x17,
  K0_B = 0x18,
  K1_B = 0x19,
  K2_B = 0x1a,
  K3_B = 0x1b,
  K0_A = 0x1c,
  K1_A = 0x1d,
  K2_A = 0x1e,
  K3_A = 0x1f,
}

/**
 * TEV swap-table channel selector (GXTevColorChan). [CORPUS width, SDK
 * numbering]
 *
 * gnt4_GXSetTevSwapModeTable_bl @0x80229ffc writes four 2-bit fields across a
 * pair of KSEL registers — (r, g) into `ksel[table*2]` bits 0-1 / 2-3 and
 * (b, a) into `ksel[table*2+1]` — confirming both the 2-bit width and the
 * argument order (table, r, g, b, a).
 */
export enum GXTevColorChan {
  RED = 0,
  GREEN = 1,
  BLUE = 2,
  ALPHA = 3,
}

/**
 * Alpha-compare combine operator (GXAlphaOp). [CORPUS width, SDK numbering]
 *
 * gnt4_GXSetAlphaCompare_bl @0x8022a07c packs
 * `(op & 3) << 0x16 | (comp1 & 7) << 0x13 | (comp0 & 7) << 0x10 |
 *  (ref1 & 0xff) << 8 | ref0 & 0xff`, which settles the ARGUMENT ORDER
 * (comp0, ref0, op, comp1, ref1) from the corpus. The ROM's only two call
 * sites pass `(7, 0, 0, 7, 0)` — both comparisons ALWAYS, which is a no-op
 * filter.
 */
export enum GXAlphaOp {
  AND = 0,
  OR = 1,
  XOR = 2,
  XNOR = 3,
}

// =============================================================================
// Texture pipeline
// =============================================================================

/**
 * Texture formats (GXTexFmt). [CORPUS — settled, not assumed]
 *
 * This is the strongest corpus result in this file. gnt4_GXInitTexObj_bl
 * @0x80228b74 switches on `format & 0xf` and, for each case, writes BOTH the
 * texel-block shift pair AND a bytes-per-texel class byte at offset 0x1e of
 * the texture object:
 *
 *   case 0, 8      -> 8x8 blocks, class 1  => the two 4-bit formats  (I4, C4)
 *   case 1, 2, 9   -> 8x4 blocks, class 2  => the three 8-bit ones (I8, IA4, C8)
 *   case 3,4,5,10  -> 4x4 blocks, class 2  => the four 16-bit ones
 *                                             (IA8, RGB565, RGB5A3, C14X2)
 *   case 6         -> 4x4 blocks, class 3  => the one 32-bit format (RGBA8)
 *   case 0xe       -> 8x8 blocks, class 0  => the one compressed format (CMPR)
 *
 * Block geometry plus bit depth identifies every GameCube texture format
 * uniquely, so each value above is pinned by the shipped binary. The Z
 * formats are pinned separately by gnt4_GXSetZTexture_bl @0x8022a0c0, which
 * maps 0x11 -> 8-bit, 0x13 -> 16-bit and 0x16 -> 24-bit Z. The ROM's own
 * GXInitTexObj call sites use 6 (a 640x224 RGBA8 framebuffer capture), 1 and 3.
 */
export enum GXTexFmt {
  I4 = 0,
  I8 = 1,
  IA4 = 2,
  IA8 = 3,
  RGB565 = 4,
  RGB5A3 = 5,
  RGBA8 = 6,
  C4 = 8,
  C8 = 9,
  C14X2 = 0xa,
  CMPR = 0xe,
  Z8 = 0x11,
  Z16 = 0x13,
  Z24X8 = 0x16,
}

/** Texture wrap modes (GXTexWrapMode). [CORPUS width, SDK numbering]
 *  gnt4_GXInitTexObj_bl stores wrap_s as `& 3` at bits 0-1 and wrap_t at
 *  bits 2-3, which settles the argument order and the 2-bit width. Every ROM
 *  call site passes 0 for both. */
export enum GXTexWrapMode {
  CLAMP = 0,
  REPEAT = 1,
  MIRROR = 2,
}

/** Texture filter modes (GXTexFilter). [SDK]
 *  gnt4_GXInitTexObjLOD_bl indexes a translation table at DAT_80435db8 with
 *  the filter argument, and that table is not in the C export. The ROM passes
 *  0 and 1 only. */
export enum GXTexFilter {
  NEAR = 0,
  LINEAR = 1,
  NEAR_MIP_NEAR = 2,
  LIN_MIP_NEAR = 3,
  NEAR_MIP_LIN = 4,
  LIN_MIP_LIN = 5,
}

/** Texture-lookup-table formats (GXTlutFmt). [SDK]
 *  gnt4_GXInitTlutObj_bl stores `fmt & 3` at bits 10-11; the 2-bit width is
 *  corpus, the meaning is the documented IA8/RGB565/RGB5A3 triple. */
export enum GXTlutFmt {
  IA8 = 0,
  RGB565 = 1,
  RGB5A3 = 2,
}

// =============================================================================
// Texture coordinate generation
// =============================================================================

/**
 * Texgen functions (GXTexGenType). [CORPUS]
 *
 * gnt4_GXSetTexCoordGen2_bl @0x80226aec dispatches on the function argument:
 *  - 0 sets the register's "3 output components" bit (`| 2`), 1 does not, so
 *    0 = MTX3x4 and 1 = MTX2x4;
 *  - 2..9 take the bump-map path, writing `(func - 2)` into the bump light
 *    field and `(src - 0xc)` into the bump source-texcoord field, so
 *    BUMP0..BUMP7 = 2..9 and GX_TG_TEXCOORD0 = 0xc;
 *  - 10 takes the colour-strgbc path, so SRTG = 10.
 * The ROM uses 0 and 1 only.
 */
export enum GXTexGenType {
  MTX3x4 = 0,
  MTX2x4 = 1,
  BUMP0 = 2,
  BUMP7 = 9,
  SRTG = 10,
}

/**
 * Texgen sources (GXTexGenSrc). [CORPUS]
 *
 * Read straight out of gnt4_GXSetTexCoordGen2_bl's source switch, which maps
 * the caller's value to the hardware's input-row index:
 *   0 -> row 0 (position, 3-component input form)
 *   1 -> row 1 (normal, 3-component)
 *   2 -> row 3, 3 -> row 4 (binormal / tangent, 3-component)
 *   4..0xb -> rows 5..0xc (the eight texcoord inputs, 2-component)
 *   0x13, 0x14 -> row 2 (the two colour channels)
 * The bump branch's `src - 0xc` arithmetic pins GX_TG_TEXCOORD0 at 0xc.
 * The ROM uses 4 (GX_TG_TEX0) at every game-code call site.
 */
export enum GXTexGenSrc {
  POS = 0,
  NRM = 1,
  BINRM = 2,
  TANGENT = 3,
  TEX0 = 4,
  TEX7 = 11,
  TEXCOORD0 = 12,
  COLOR0 = 0x13,
  COLOR1 = 0x14,
}

/** Post-transform texture matrices start at 0x40 and GX_PTIDENTITY is the last
 *  slot. [CORPUS] gnt4_GXSetTexCoordGen2_bl writes `postmtx - 0x40 & 0x3f`,
 *  and every ROM call site passes 0x7d — the identity slot, 0x7d - 0x40 = 0x3d. */
export const GX_PTTEXMTX_BASE = 0x40;
export const GX_PTIDENTITY = 0x7d;

// =============================================================================
// Lighting
// =============================================================================

/**
 * Diffuse lighting functions (GXDiffuseFn). [CORPUS width, SDK numbering]
 *
 * gnt4_GXSetChanCtrl_bl @0x80228898 writes `(diff_fn & 3) << 7`. The ROM's
 * unlit paths pass 0 and its one lit path passes 2.
 */
export enum GXDiffuseFn {
  NONE = 0,
  SIGN = 1,
  CLAMP = 2,
}

/**
 * Light attenuation functions (GXAttnFn). [CORPUS]
 *
 * gnt4_GXSetChanCtrl_bl derives two separate register bits from this one
 * argument: an ENABLE bit that is set for values 1 and 2 and clear for 0, and
 * a SELECT bit that is set for 0 and 1 and clear for 2. It also opens with
 * `if (attn_fn == 0) diff_fn = 0`. Only one assignment satisfies all three:
 * 0 = SPEC (specular attenuation, which the hardware requires be paired with
 * no diffuse function), 1 = SPOT, 2 = NONE. Every ROM call site passes 2.
 */
export enum GXAttnFn {
  SPEC = 0,
  SPOT = 1,
  NONE = 2,
}

/** Bytes in a GXLightObj as the SDK lays it out. [CORPUS]
 *  gnt4_GXLoadLightObjImm_bl @0x80228600 streams offsets 0x0c through 0x3c
 *  inclusive to the XF light region, and gnt4_GXInitLightDir_bl writes the
 *  NEGATED direction to 0x34/0x38/0x3c, so the object is 0x40 bytes with
 *  colour at 0x0c, distance attenuation at 0x10-0x18, angle attenuation at
 *  0x1c-0x24, position at 0x28-0x30 and negated direction at 0x34-0x3c. */
export const GX_LIGHT_OBJ_BYTES = 0x40;
export const GX_MAX_LIGHT = 8;
