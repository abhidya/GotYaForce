/* gx_selftest.c — threads-target ROM-side draw module for the GX HLE host.
 *
 * WHAT THIS IS, and what it is not.
 *
 * It is a PURPOSE-BUILT ROM-side draw module: each of its three draw functions
 * reproduces, call for call and store for store, one of the ROM's own
 * immediate-mode draw paths as they appear in the decompiled corpus. It exists
 * because the composed rung-0 module cannot issue GX draws yet (see WGPIPE
 * below), so proving the seam end to end requires a module that can.
 *
 * It is NOT ported ROM code and carries no behavioural claim about the game.
 * It is a faithful reproduction of a call SEQUENCE, which is what the seam
 * needs to be exercised against.
 *
 * The three paths, with their originals:
 *
 *  1. gx_draw_fullscreen_quad  <- zz_0027c34_ (chunk_0003.c:3285-3328)
 *     Orthographic screen-space quad. POS = DIRECT, cnt 0 (XY), type 3 (S16);
 *     CLR0 = DIRECT, cnt 1 (RGBA), type 5 (RGBA8). GXBegin(0x80, 0, 4) then
 *     per vertex: two 16-bit FIFO stores + one 32-bit store. The original is
 *     the game's screen fade/flash overlay.
 *
 *  2. gx_draw_strip            <- zz_0050f80_ (chunk_0006.c:4865-4924)
 *     Triangle strip with DIRECT F32 XYZ positions and RGBA8 colours.
 *     GXBegin(0x98, 0, n) then per vertex: four 32-bit stores.
 *
 *  3. gx_draw_indexed          <- zz_0050bf4_ (chunk_0006.c:4760-4797)
 *     INDEX8 positions and colours through GXSetArray, line primitive 0xb0.
 *     GXBegin(0xb0, 0, n) then per vertex: two 8-bit stores.
 *
 *  4. gx_call_unimplemented    — deliberately calls a GX entry point the host
 *     does NOT implement (GXSetFog, 2 static ROM call sites), to prove that an
 *     unimplemented entry point fails loudly instead of no-opping.
 *
 * WGPIPE — the load-bearing difference from the real ROM.
 * On the console the vertex components are STORES to the memory-mapped
 * write-gather pipe at 0xCC008000 (`DAT_cc008000 = ...` in the corpus). A
 * composed wasm module cannot do that: its linear memory is 0x807A0000 bytes
 * and 0xCC008000 is past the end, so the store traps. This fixture therefore
 * calls explicit __gf_gx_wgpipe_* imports instead, which is exactly the
 * lowering the assembly gate will have to emit. Everything downstream of those
 * calls — the byte order, the vertex layout, the decoder — is the console's.
 *
 * Build: see build.sh. The compiled .wasm is COMMITTED so the smoke phase runs
 * on a clean checkout without the toolchain.
 */

typedef unsigned char      u8;
typedef unsigned short     u16;
typedef unsigned int       u32;
typedef signed short       s16;

/* ---- the SDK seam: every GX entry point is a host import ----------------- */
extern void gnt4_GXSetCullMode_bl(u32 mode);
extern void gnt4_GXSetBlendMode_bl(u32 type, u32 src, u32 dst, u32 op);
extern void gnt4_GXSetZMode_bl(u32 compare_enable, u32 func, u32 update_enable);
extern void gnt4_GXSetProjection_bl(float *mtx, int type);
extern void gnt4_GXLoadPosMtxImm_bl(float *mtx, int id);
extern void gnt4_GXSetCurrentMtx_bl(u32 id);
extern void gnt4_GXClearVtxDesc_bl(void);
extern void gnt4_GXSetVtxDesc_bl(u32 attr, u32 type);
extern void gnt4_GXSetVtxAttrFmt_bl(u32 vtxfmt, u32 attr, u32 cnt, u32 type, u32 frac);
extern void gnt4_GXSetArray(u32 attr, void *base, u32 stride);
extern void gnt4_GXSetNumChans_bl(u32 n);
extern void gnt4_GXSetNumTexGens_bl(u32 n);
extern void gnt4_GXSetNumTevStages_bl(u32 n);
extern void gnt4_GXSetChanCtrl_bl(u32 chan, u32 enable, u32 amb_src, u32 mat_src,
                                  u32 light_mask, u32 diff_fn, u32 attn_fn);
extern void gnt4_GXSetTevOrder_bl(u32 stage, u32 coord, u32 map, int color);
extern void gnt4_GXSetTevOp_bl(u32 stage, u32 mode);
extern void gnt4_GXInvalidateVtxCache_bl(void);
extern void gnt4_GXBegin_bl(u32 prim, u32 vtxfmt, u32 nverts);

/* ---- TEV, texture, texgen and lighting entry points ----------------------
 * Argument orders here are the DECOMPILED SDK's, not the published SDK's:
 * gnt4_GXSetTevColorOp_bl takes (stage, op, bias, scale, clamp, out_reg) and
 * gnt4_GXSetTevOrder_bl takes (stage, coord, map, color), both settled from
 * the register packings in research/decomp/ghidra-export/chunk_0067.c. The
 * colour arguments are POINTERS because those bodies dereference them (see
 * readColor in packages/rom-runtime/src/gx/adapters.ts). GXInitTexObjLOD and
 * the GXInitLight* helpers take their floating-point arguments FIRST because
 * PPC passes them in FPRs and Ghidra recovered the signature that way. */
extern void gnt4_GXSetTevColorIn_bl(u32 stage, u32 a, u32 b, u32 c, u32 d);
extern void gnt4_GXSetTevAlphaIn_bl(u32 stage, u32 a, u32 b, u32 c, u32 d);
extern void gnt4_GXSetTevColorOp_bl(u32 stage, u32 op, u32 bias, u32 scale, u32 clamp, u32 out_reg);
extern void gnt4_GXSetTevAlphaOp_bl(u32 stage, u32 op, u32 bias, u32 scale, u32 clamp, u32 out_reg);
extern void gnt4_GXSetTevKColor_bl(u32 reg, const u8 *color);
extern void gnt4_GXSetTevColor_bl(u32 reg, const u8 *color);
extern void gnt4_GXSetTevKColorSel_bl(u32 stage, u32 sel);
extern void gnt4_GXSetTevKAlphaSel_bl(u32 stage, u32 sel);
extern void gnt4_GXSetTevSwapMode_bl(u32 stage, u32 ras_sel, u32 tex_sel);
extern void gnt4_GXSetTevSwapModeTable_bl(u32 table, u32 r, u32 g, u32 b, u32 a);
extern void gnt4_GXSetAlphaCompare_bl(u32 comp0, u32 ref0, u32 op, u32 comp1, u32 ref1);
extern void gnt4_GXInitTexObj_bl(void *obj, void *image, u32 width, u32 height,
                                 u32 format, u32 wrap_s, u32 wrap_t, char mipmap);
extern void gnt4_GXInitTexObjLOD_bl(double min_lod, double max_lod, double lod_bias, void *obj,
                                    int min_filt, int mag_filt, u32 bias_clamp, char do_edge_lod,
                                    u32 max_aniso);
extern void gnt4_GXLoadTexObj_bl(void *obj, int map);
extern void gnt4_GXSetTexCoordGen2_bl(int dst, int func, int src, u32 mtx, u32 normalize, int postmtx);
extern void gnt4_GXLoadTexMtxImm_bl(float *mtx, int id, int type);
extern void gnt4_GXLoadNrmMtxImm_bl(float *mtx, int id);
extern void gnt4_GXInitLightColor_bl(void *light, const u8 *color);
extern void gnt4_GXInitLightPos_bl(double x, double y, double z, void *light);
extern void gnt4_GXLoadLightObjImm_bl(void *light, u32 light_mask);
extern void gnt4_GXSetChanMatColor_bl(int chan, const u8 *color, u32 pad0, u32 pad1);
extern void gnt4_GXSetChanAmbColor_bl(int chan, const u8 *color, u32 pad0, u32 pad1);

/* An entry point the host deliberately does not implement. */
extern void gnt4_GXSetFog_bl(u32 type, float startz, float endz, float nearz, float farz, u32 color);

/* ---- the write-gather pipe (see WGPIPE above) ---------------------------- */
extern void __gf_gx_wgpipe_u8(u32 value);
extern void __gf_gx_wgpipe_u16(u32 value);
extern void __gf_gx_wgpipe_u32(u32 value);
extern void __gf_gx_wgpipe_f32(float value);

/* ---- projection matrices ------------------------------------------------- */
/* GXSetProjection takes a Mtx44 (16 floats) — settled from the decompiled
 * gnt4_GXSetProjection_bl, which indexes param_1[0], [2]/[3], [5], [6]/[7],
 * [10], [11]. Both matrices below are written in GC row-major order. */
static float ortho_mtx[16];
static float persp_mtx[16];
static float identity_mtx[12];

/* Screen-space orthographic projection over the ROM's own 640x448 frame — the
 * exact extent zz_0027c34_ draws to (its quad corners are 0x280 x 0x1c0). */
static void build_ortho(void)
{
    int i;
    for (i = 0; i < 16; i++) ortho_mtx[i] = 0.0f;
    ortho_mtx[0]  =  2.0f / 640.0f;   /* m[0][0] */
    ortho_mtx[3]  = -1.0f;            /* m[0][3] */
    ortho_mtx[5]  = -2.0f / 448.0f;   /* m[1][1]  (screen y grows downward) */
    ortho_mtx[7]  =  1.0f;            /* m[1][3] */
    ortho_mtx[10] =  1.0f;            /* m[2][2] */
    ortho_mtx[11] = -1.0f;            /* m[2][3] */
    ortho_mtx[15] =  1.0f;
}

/* A plain perspective projection, so the perspective branch of
 * GXSetProjection's coefficient packing is exercised too. */
static void build_persp(void)
{
    int i;
    for (i = 0; i < 16; i++) persp_mtx[i] = 0.0f;
    persp_mtx[0]  =  1.0f;   /* m[0][0] */
    persp_mtx[2]  =  0.0f;   /* m[0][2] */
    persp_mtx[5]  =  1.3333334f;
    persp_mtx[6]  =  0.0f;
    persp_mtx[10] = -1.010101f;
    persp_mtx[11] = -2.020202f;
}

static void build_identity(void)
{
    int i;
    for (i = 0; i < 12; i++) identity_mtx[i] = 0.0f;
    identity_mtx[0] = 1.0f;
    identity_mtx[5] = 1.0f;
    identity_mtx[10] = 1.0f;
}

/* The common state block every one of the ROM's immediate-mode draws sets up
 * before it begins a primitive. Reproduced verbatim from zz_0027c34_. */
static void common_unlit_setup(void)
{
    gnt4_GXSetNumChans_bl(1);
    gnt4_GXSetNumTexGens_bl(0);
    gnt4_GXSetNumTevStages_bl(1);
    /* (COLOR0A0, disabled, amb_src = vertex, mat_src = vertex, ...) */
    gnt4_GXSetChanCtrl_bl(4, 0, 1, 1, 0, 0, 2);
    /* (stage 0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0) */
    gnt4_GXSetTevOrder_bl(0, 0xff, 0xff, 4);
    gnt4_GXSetTevOp_bl(0, 4);
}

/* =========================================================================
 * 1. zz_0027c34_ — orthographic screen-space quad, S16 XY + RGBA8
 * ========================================================================= */
void gx_draw_fullscreen_quad(u32 rgba, u32 x0, u32 y0, u32 x1, u32 y1)
{
    build_ortho();
    build_identity();

    gnt4_GXSetCullMode_bl(2);                 /* GX_CULL_BACK   */
    gnt4_GXSetBlendMode_bl(1, 4, 5, 0);       /* blend, srcalpha/invsrcalpha */
    gnt4_GXSetZMode_bl(1, 7, 0);              /* compare on, ALWAYS, no write */
    gnt4_GXSetProjection_bl(ortho_mtx, 1);    /* orthographic   */
    gnt4_GXLoadPosMtxImm_bl(identity_mtx, 0);
    gnt4_GXSetCurrentMtx_bl(0);
    gnt4_GXClearVtxDesc_bl();
    gnt4_GXSetVtxDesc_bl(9, 1);               /* POS  DIRECT */
    gnt4_GXSetVtxDesc_bl(0xb, 1);             /* CLR0 DIRECT */
    gnt4_GXSetVtxAttrFmt_bl(0, 9, 0, 3, 0);   /* POS  cnt XY,   type S16   */
    gnt4_GXSetVtxAttrFmt_bl(0, 0xb, 1, 5, 0); /* CLR0 cnt RGBA, type RGBA8 */
    common_unlit_setup();

    gnt4_GXBegin_bl(0x80, 0, 4);              /* GX_QUADS, vtxfmt 0, 4 verts */
    __gf_gx_wgpipe_u16(x0); __gf_gx_wgpipe_u16(y0); __gf_gx_wgpipe_u32(rgba);
    __gf_gx_wgpipe_u16(x1); __gf_gx_wgpipe_u16(y0); __gf_gx_wgpipe_u32(rgba);
    __gf_gx_wgpipe_u16(x1); __gf_gx_wgpipe_u16(y1); __gf_gx_wgpipe_u32(rgba);
    __gf_gx_wgpipe_u16(x0); __gf_gx_wgpipe_u16(y1); __gf_gx_wgpipe_u32(rgba);
}

/* =========================================================================
 * 2. zz_0050f80_ — triangle strip, DIRECT F32 XYZ + RGBA8
 * ========================================================================= */
void gx_draw_strip(u32 rgba, u32 x0, u32 y0, u32 x1, u32 y1)
{
    build_ortho();
    build_identity();

    gnt4_GXSetCullMode_bl(0);                 /* GX_CULL_NONE */
    gnt4_GXSetBlendMode_bl(0, 0, 0, 0);       /* GX_BM_NONE   */
    gnt4_GXSetZMode_bl(1, 3, 1);              /* compare on, LEQUAL, write   */
    gnt4_GXSetProjection_bl(ortho_mtx, 1);
    gnt4_GXLoadPosMtxImm_bl(identity_mtx, 0);
    gnt4_GXSetCurrentMtx_bl(0);
    gnt4_GXClearVtxDesc_bl();
    gnt4_GXSetVtxDesc_bl(9, 1);
    gnt4_GXSetVtxDesc_bl(0xb, 1);
    gnt4_GXSetVtxAttrFmt_bl(0, 9, 1, 4, 0);   /* POS  cnt XYZ, type F32   */
    gnt4_GXSetVtxAttrFmt_bl(0, 0xb, 1, 5, 0); /* CLR0 cnt RGBA, type RGBA8 */
    common_unlit_setup();

    /* Strip order: (x0,y0) (x1,y0) (x0,y1) (x1,y1) — two triangles. */
    gnt4_GXBegin_bl(0x98, 0, 4);
    __gf_gx_wgpipe_f32((float)x0); __gf_gx_wgpipe_f32((float)y0); __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_u32(rgba);
    __gf_gx_wgpipe_f32((float)x1); __gf_gx_wgpipe_f32((float)y0); __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_u32(rgba);
    __gf_gx_wgpipe_f32((float)x0); __gf_gx_wgpipe_f32((float)y1); __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_u32(rgba);
    __gf_gx_wgpipe_f32((float)x1); __gf_gx_wgpipe_f32((float)y1); __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_u32(rgba);
}

/* =========================================================================
 * 3. zz_0050bf4_ — INDEX8 arrays through GXSetArray, line primitive 0xb0
 * ========================================================================= */
static float line_positions[4 * 3];
/* RGBA8 array entries are BYTES in R,G,B,A order — NOT a u32.
 *
 * This distinction is load-bearing and was found the hard way. On the console
 * a `u32 = 0xffd040ff` store lays the bytes down big-endian as FF D0 40 FF,
 * which read in memory order IS R,G,B,A. In wasm's little-endian memory the
 * same u32 store lays them down reversed, and the host's indexed fetch — which
 * reads a colour byte-wise, because that is what the hardware does — would see
 * A,B,G,R. Writing the bytes explicitly keeps this array in the console's
 * layout. See docs/gx-hle-host.md: whether the DOL-derived arena preserves
 * console byte order for non-float data is an OPEN question, and this is
 * exactly the class of bug it will produce.
 */
static u8 line_colors[4 * 4];

void gx_draw_indexed(u32 rgba, u32 x0, u32 y0, u32 x1, u32 y1)
{
    int i;
    build_ortho();
    build_identity();

    line_positions[0] = (float)x0; line_positions[1]  = (float)y0; line_positions[2]  = 0.0f;
    line_positions[3] = (float)x1; line_positions[4]  = (float)y0; line_positions[5]  = 0.0f;
    line_positions[6] = (float)x1; line_positions[7]  = (float)y1; line_positions[8]  = 0.0f;
    line_positions[9] = (float)x0; line_positions[10] = (float)y1; line_positions[11] = 0.0f;
    for (i = 0; i < 4; i++) {
        line_colors[i * 4 + 0] = (u8)((rgba >> 24) & 0xff);
        line_colors[i * 4 + 1] = (u8)((rgba >> 16) & 0xff);
        line_colors[i * 4 + 2] = (u8)((rgba >> 8) & 0xff);
        line_colors[i * 4 + 3] = (u8)(rgba & 0xff);
    }

    gnt4_GXSetCullMode_bl(0);
    gnt4_GXSetBlendMode_bl(0, 0, 0, 0);
    gnt4_GXSetZMode_bl(1, 7, 0);
    gnt4_GXSetProjection_bl(ortho_mtx, 1);
    gnt4_GXLoadPosMtxImm_bl(identity_mtx, 0);
    gnt4_GXSetCurrentMtx_bl(0);
    gnt4_GXClearVtxDesc_bl();
    gnt4_GXSetVtxDesc_bl(9, 2);               /* POS  INDEX8 */
    gnt4_GXSetVtxDesc_bl(0xb, 2);             /* CLR0 INDEX8 */
    gnt4_GXSetArray(9, line_positions, 12);   /* stride 12 = 3 x f32 */
    gnt4_GXSetArray(0xb, line_colors, 4);     /* stride 4  = RGBA8   */
    gnt4_GXSetVtxAttrFmt_bl(0, 9, 1, 4, 0);
    gnt4_GXSetVtxAttrFmt_bl(0, 0xb, 1, 5, 0);
    common_unlit_setup();
    gnt4_GXInvalidateVtxCache_bl();

    gnt4_GXBegin_bl(0xb0, 0, 4);
    for (i = 0; i < 4; i++) {
        __gf_gx_wgpipe_u8((u32)i);            /* position index */
        __gf_gx_wgpipe_u8((u32)i);            /* colour index   */
    }
}

/* =========================================================================
 * 4. The loud-unimplemented probe.
 * ========================================================================= */
void gx_call_unimplemented(void)
{
    /* GXSetFog has 2 static ROM call sites and is NOT implemented by the host.
     * The host's adapter for it throws, which surfaces as a declared servicing
     * error in the bridged-call ledger and fails this export. That failure is
     * the point: an unimplemented GX entry point must never quietly no-op. */
    gnt4_GXSetFog_bl(0, 0.0f, 1.0f, 0.0f, 1.0f, 0);
}

/* The perspective projection branch, exercised on its own so the coefficient
 * packing for type 0 is covered as well as type 1. */
void gx_set_perspective(void)
{
    build_persp();
    gnt4_GXSetProjection_bl(persp_mtx, 0);
}

/* =========================================================================
 * 5. The TEV combiner.
 *
 * The draws below exist so the generated fragment shader can be checked
 * against a value the page can PREDICT EXACTLY, rather than against "it drew
 * something". Each one deliberately makes the vertex colour DIFFERENT from
 * the expected output, so a combiner that silently fell back to passing the
 * rasterized colour through would fail rather than pass by accident.
 *
 * As everywhere in this fixture: these are GX call sequences a ROM could
 * make, not ported ROM code, and they carry no behavioural claim.
 * ========================================================================= */

/* Selector values, named so the call sites read as GX rather than as magic.
 * Provenance for every one of these is in
 * packages/rom-runtime/src/gx/enums.ts, labelled [CORPUS] or [SDK]. */
#define CC_C0     2
#define CC_TEXC   8
#define CC_RASC  10
#define CC_KONST 14
#define CC_ZERO  15
#define CA_A0     1
#define CA_TEXA   4
#define CA_RASA   5
#define CA_KONST  6
#define CA_ZERO   7
#define TEV_ADD   0
#define TB_ZERO   0
#define CS_SCALE_1 0
#define TEVPREV   0
#define TEVREG0   1
#define KCSEL_K0  0x0c
#define KCSEL_K1  0x0d
#define KASEL_K0_A 0x1c
#define KASEL_K1_A 0x1d

static u8 konst0[4];
static u8 konst1[4];

/* A screen-space quad in the same S16 XY + RGBA8 layout as zz_0027c34_'s. */
static void emit_quad(u32 rgba, u32 x0, u32 y0, u32 x1, u32 y1)
{
    gnt4_GXBegin_bl(0x80, 0, 4);
    __gf_gx_wgpipe_u16(x0); __gf_gx_wgpipe_u16(y0); __gf_gx_wgpipe_u32(rgba);
    __gf_gx_wgpipe_u16(x1); __gf_gx_wgpipe_u16(y0); __gf_gx_wgpipe_u32(rgba);
    __gf_gx_wgpipe_u16(x1); __gf_gx_wgpipe_u16(y1); __gf_gx_wgpipe_u32(rgba);
    __gf_gx_wgpipe_u16(x0); __gf_gx_wgpipe_u16(y1); __gf_gx_wgpipe_u32(rgba);
}

static void quad_state_2d(void)
{
    build_ortho();
    build_identity();
    gnt4_GXSetCullMode_bl(0);
    gnt4_GXSetBlendMode_bl(0, 0, 0, 0);
    gnt4_GXSetZMode_bl(1, 7, 0);
    gnt4_GXSetProjection_bl(ortho_mtx, 1);
    gnt4_GXLoadPosMtxImm_bl(identity_mtx, 0);
    gnt4_GXSetCurrentMtx_bl(0);
    gnt4_GXClearVtxDesc_bl();
    gnt4_GXSetVtxDesc_bl(9, 1);
    gnt4_GXSetVtxDesc_bl(0xb, 1);
    gnt4_GXSetVtxAttrFmt_bl(0, 9, 0, 3, 0);
    gnt4_GXSetVtxAttrFmt_bl(0, 0xb, 1, 5, 0);
    gnt4_GXSetNumChans_bl(1);
    gnt4_GXSetNumTexGens_bl(0);
    gnt4_GXSetChanCtrl_bl(4, 0, 1, 1, 0, 0, 2);
}

/* 5a. One stage whose ONLY colour input is the konstant register.
 *     out = d = KONST(K0). The vertex colour is passed in and must NOT win. */
void gx_draw_tev_konst(u32 vertex_rgba, u32 kr, u32 kg, u32 kb, u32 ka)
{
    konst0[0] = (u8)kr; konst0[1] = (u8)kg; konst0[2] = (u8)kb; konst0[3] = (u8)ka;
    quad_state_2d();
    gnt4_GXSetNumTevStages_bl(1);
    gnt4_GXSetTevOrder_bl(0, 0xff, 0xff, 4);
    gnt4_GXSetTevKColor_bl(0, konst0);
    gnt4_GXSetTevKColorSel_bl(0, KCSEL_K0);
    gnt4_GXSetTevKAlphaSel_bl(0, KASEL_K0_A);
    gnt4_GXSetTevColorIn_bl(0, CC_ZERO, CC_ZERO, CC_ZERO, CC_KONST);
    gnt4_GXSetTevAlphaIn_bl(0, CA_ZERO, CA_ZERO, CA_ZERO, CA_KONST);
    gnt4_GXSetTevColorOp_bl(0, TEV_ADD, TB_ZERO, CS_SCALE_1, 1, TEVPREV);
    gnt4_GXSetTevAlphaOp_bl(0, TEV_ADD, TB_ZERO, CS_SCALE_1, 1, TEVPREV);
    emit_quad(vertex_rgba, 0, 0, 640, 448);
}

/* 5b. Two stages that chain THROUGH A REGISTER.
 *     stage 0 writes K1 into GX_TEVREG0 and nothing else;
 *     stage 1 reads it back as GX_CC_C0 and passes it to the framebuffer.
 *     A combiner that ignored out_reg, or that ignored stage 1's inputs,
 *     produces a different pixel. */
void gx_draw_tev_two_stage(u32 vertex_rgba, u32 kr, u32 kg, u32 kb, u32 ka)
{
    konst1[0] = (u8)kr; konst1[1] = (u8)kg; konst1[2] = (u8)kb; konst1[3] = (u8)ka;
    quad_state_2d();
    gnt4_GXSetNumTevStages_bl(2);
    gnt4_GXSetTevKColor_bl(1, konst1);

    gnt4_GXSetTevOrder_bl(0, 0xff, 0xff, 4);
    gnt4_GXSetTevKColorSel_bl(0, KCSEL_K1);
    gnt4_GXSetTevKAlphaSel_bl(0, KASEL_K1_A);
    gnt4_GXSetTevColorIn_bl(0, CC_ZERO, CC_ZERO, CC_ZERO, CC_KONST);
    gnt4_GXSetTevAlphaIn_bl(0, CA_ZERO, CA_ZERO, CA_ZERO, CA_KONST);
    gnt4_GXSetTevColorOp_bl(0, TEV_ADD, TB_ZERO, CS_SCALE_1, 1, TEVREG0);
    gnt4_GXSetTevAlphaOp_bl(0, TEV_ADD, TB_ZERO, CS_SCALE_1, 1, TEVREG0);

    gnt4_GXSetTevOrder_bl(1, 0xff, 0xff, 4);
    gnt4_GXSetTevColorIn_bl(1, CC_ZERO, CC_ZERO, CC_ZERO, CC_C0);
    gnt4_GXSetTevAlphaIn_bl(1, CA_ZERO, CA_ZERO, CA_ZERO, CA_A0);
    gnt4_GXSetTevColorOp_bl(1, TEV_ADD, TB_ZERO, CS_SCALE_1, 1, TEVPREV);
    gnt4_GXSetTevAlphaOp_bl(1, TEV_ADD, TB_ZERO, CS_SCALE_1, 1, TEVPREV);
    emit_quad(vertex_rgba, 0, 0, 640, 448);
}

/* 5c. The alpha test. GX_GREATER against a reference the fragment's alpha
 *     does not clear, so the quad must be DISCARDED and the background must
 *     survive. A host that latched GXSetAlphaCompare without generating the
 *     discard would paint over it. */
void gx_draw_alpha_compare_discard(u32 vertex_rgba)
{
    quad_state_2d();
    gnt4_GXSetNumTevStages_bl(1);
    gnt4_GXSetTevOrder_bl(0, 0xff, 0xff, 4);
    gnt4_GXSetTevOp_bl(0, 4);                       /* GX_PASSCLR */
    /* (GX_GREATER, 0x80, GX_AOP_AND, GX_ALWAYS, 0) */
    gnt4_GXSetAlphaCompare_bl(4, 0x80, 0, 7, 0);
    emit_quad(vertex_rgba, 0, 0, 640, 448);
    gnt4_GXSetAlphaCompare_bl(7, 0, 0, 7, 0);       /* back to always-pass */
}

/* =========================================================================
 * 6. Texture sampling.
 *
 * One 4x4 RGBA8 texel block, built here in the module's own memory so the
 * host has to read it back out of the arena at the address GXInitTexObj was
 * given and de-tile it. RGBA8 is the format whose block layout is least
 * forgiving — 4x4 texels in TWO 32-byte halves, AR pairs then GB pairs — so
 * a decoder that treated the block as linear produces visibly wrong colours
 * rather than nearly-right ones.
 * ========================================================================= */
static u8 tex_rgba8_block[64];
static u32 tex_obj[8];      /* GXTexObj is 32 bytes; the host only reads the
                             * address, but the size is the SDK's. */

static void build_texture(u32 r, u32 g, u32 b, u32 a)
{
    int i;
    for (i = 0; i < 16; i++) {
        tex_rgba8_block[i * 2 + 0]      = (u8)a;   /* first half: A, R */
        tex_rgba8_block[i * 2 + 1]      = (u8)r;
        tex_rgba8_block[32 + i * 2 + 0] = (u8)g;   /* second half: G, B */
        tex_rgba8_block[32 + i * 2 + 1] = (u8)b;
    }
}

void gx_draw_textured(u32 tr, u32 tg, u32 tb, u32 ta)
{
    build_texture(tr, tg, tb, ta);
    build_ortho();
    build_identity();

    gnt4_GXInitTexObj_bl(tex_obj, tex_rgba8_block, 4, 4, 6 /* GX_TF_RGBA8 */, 0, 0, 0);
    gnt4_GXInitTexObjLOD_bl(0.0, 0.0, 0.0, tex_obj, 0 /* GX_NEAR */, 0 /* GX_NEAR */, 0, 0, 0);
    gnt4_GXLoadTexObj_bl(tex_obj, 0 /* GX_TEXMAP0 */);

    gnt4_GXSetCullMode_bl(0);
    gnt4_GXSetBlendMode_bl(0, 0, 0, 0);
    gnt4_GXSetZMode_bl(1, 7, 0);
    gnt4_GXSetProjection_bl(ortho_mtx, 1);
    gnt4_GXLoadPosMtxImm_bl(identity_mtx, 0);
    gnt4_GXSetCurrentMtx_bl(0);
    gnt4_GXLoadTexMtxImm_bl(identity_mtx, 0x3c /* GX_IDENTITY */, 0);

    gnt4_GXClearVtxDesc_bl();
    gnt4_GXSetVtxDesc_bl(9, 1);      /* POS  DIRECT */
    gnt4_GXSetVtxDesc_bl(0xb, 1);    /* CLR0 DIRECT */
    gnt4_GXSetVtxDesc_bl(0xd, 1);    /* TEX0 DIRECT */
    gnt4_GXSetVtxAttrFmt_bl(0, 9, 0, 3, 0);      /* POS  XY  S16   */
    gnt4_GXSetVtxAttrFmt_bl(0, 0xb, 1, 5, 0);    /* CLR0 RGBA8     */
    gnt4_GXSetVtxAttrFmt_bl(0, 0xd, 1, 4, 0);    /* TEX0 ST  F32   */

    gnt4_GXSetNumChans_bl(1);
    gnt4_GXSetChanCtrl_bl(4, 0, 1, 1, 0, 0, 2);
    gnt4_GXSetNumTexGens_bl(1);
    /* (GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, no normalize,
     *  GX_PTIDENTITY) — the exact shape of the ROM's own 6 call sites, which
     *  differ only in naming GX_TEXMTX0 instead of GX_IDENTITY. */
    gnt4_GXSetTexCoordGen2_bl(0, 1, 4, 0x3c, 0, 0x7d);
    gnt4_GXSetNumTevStages_bl(1);
    /* (stage 0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0) then GX_MODULATE —
     *  the ROM's own textured pairing. White vertices make the product the
     *  texel, so the readback checks the DECODE, not the multiply. */
    gnt4_GXSetTevOrder_bl(0, 0, 0, 4);
    gnt4_GXSetTevOp_bl(0, 0);

    gnt4_GXBegin_bl(0x80, 0, 4);
    __gf_gx_wgpipe_u16(0);   __gf_gx_wgpipe_u16(0);   __gf_gx_wgpipe_u32(0xffffffffu);
    __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_f32(0.0f);
    __gf_gx_wgpipe_u16(640); __gf_gx_wgpipe_u16(0);   __gf_gx_wgpipe_u32(0xffffffffu);
    __gf_gx_wgpipe_f32(1.0f); __gf_gx_wgpipe_f32(0.0f);
    __gf_gx_wgpipe_u16(640); __gf_gx_wgpipe_u16(448); __gf_gx_wgpipe_u32(0xffffffffu);
    __gf_gx_wgpipe_f32(1.0f); __gf_gx_wgpipe_f32(1.0f);
    __gf_gx_wgpipe_u16(0);   __gf_gx_wgpipe_u16(448); __gf_gx_wgpipe_u32(0xffffffffu);
    __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_f32(1.0f);
}

/* =========================================================================
 * 7. Lighting.
 *
 * One directional-ish point light placed straight in front of a screen-space
 * quad whose normals face it, so the diffuse term is exactly 1 and the lit
 * colour is the light's own colour. Material white, ambient black, so nothing
 * else can contribute.
 * ========================================================================= */
static u32 light_obj[16];   /* GXLightObj is 0x40 bytes (corpus-settled). */
static u8 light_rgba[4];
static u8 white_rgba[4];
static u8 black_rgba[4];

void gx_draw_lit(u32 lr, u32 lg, u32 lb)
{
    light_rgba[0] = (u8)lr; light_rgba[1] = (u8)lg; light_rgba[2] = (u8)lb; light_rgba[3] = 255;
    white_rgba[0] = 255; white_rgba[1] = 255; white_rgba[2] = 255; white_rgba[3] = 255;
    black_rgba[0] = 0; black_rgba[1] = 0; black_rgba[2] = 0; black_rgba[3] = 255;

    build_ortho();
    build_identity();

    gnt4_GXInitLightColor_bl(light_obj, light_rgba);
    /* Screen space: the quad sits on z = 0 with normals pointing at +z, so a
     * light far out along +z is head-on. GX lights PER VERTEX and the raster
     * interpolates, so the distance is deliberately large: it makes cos(theta)
     * ~= 1 at all four corners, which makes the expected pixel exactly the
     * light colour instead of a corner-dependent fraction the page would have
     * to approximate. */
    gnt4_GXInitLightPos_bl(320.0, 224.0, 100000.0, light_obj);
    gnt4_GXLoadLightObjImm_bl(light_obj, 1 /* GX_LIGHT0 — a MASK, not an index */);

    gnt4_GXSetCullMode_bl(0);
    gnt4_GXSetBlendMode_bl(0, 0, 0, 0);
    gnt4_GXSetZMode_bl(1, 7, 0);
    gnt4_GXSetProjection_bl(ortho_mtx, 1);
    gnt4_GXLoadPosMtxImm_bl(identity_mtx, 0);
    gnt4_GXLoadNrmMtxImm_bl(identity_mtx, 0);
    gnt4_GXSetCurrentMtx_bl(0);

    gnt4_GXClearVtxDesc_bl();
    gnt4_GXSetVtxDesc_bl(9, 1);      /* POS DIRECT */
    gnt4_GXSetVtxDesc_bl(10, 1);     /* NRM DIRECT */
    gnt4_GXSetVtxAttrFmt_bl(0, 9, 0, 3, 0);      /* POS XY  S16 */
    gnt4_GXSetVtxAttrFmt_bl(0, 10, 0, 4, 0);     /* NRM XYZ F32 */

    gnt4_GXSetNumChans_bl(1);
    gnt4_GXSetChanMatColor_bl(4, white_rgba, 0, 0);
    gnt4_GXSetChanAmbColor_bl(4, black_rgba, 0, 0);
    /* (GX_COLOR0A0, lighting ON, amb from REG, mat from REG, light 0,
     *  GX_DF_CLAMP, GX_AF_NONE) */
    gnt4_GXSetChanCtrl_bl(4, 1, 0, 0, 1, 2, 2);
    gnt4_GXSetNumTexGens_bl(0);
    gnt4_GXSetNumTevStages_bl(1);
    gnt4_GXSetTevOrder_bl(0, 0xff, 0xff, 4);
    gnt4_GXSetTevOp_bl(0, 4);        /* GX_PASSCLR */

    gnt4_GXBegin_bl(0x80, 0, 4);
    __gf_gx_wgpipe_u16(0);   __gf_gx_wgpipe_u16(0);
    __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_f32(1.0f);
    __gf_gx_wgpipe_u16(640); __gf_gx_wgpipe_u16(0);
    __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_f32(1.0f);
    __gf_gx_wgpipe_u16(640); __gf_gx_wgpipe_u16(448);
    __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_f32(1.0f);
    __gf_gx_wgpipe_u16(0);   __gf_gx_wgpipe_u16(448);
    __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_f32(0.0f); __gf_gx_wgpipe_f32(1.0f);
}

/* =========================================================================
 * 8. The ROM's OWN four-stage TEV program, reproduced call for call.
 *
 * Transcribed from research/decomp/ghidra-export/chunk_0003.c:5670-5720 — the
 * game's most elaborate combiner program, four stages with per-stage konstant
 * selection, per-stage swap modes and a three-row swap table. It sets state
 * only and draws nothing: without the two textures its stages 0-2 name, a draw
 * would prove nothing about pixels. What it DOES prove is that the whole
 * multi-stage entry-point surface accepts the ROM's real argument values and
 * lands them where the shader generator reads them.
 * ========================================================================= */
void gx_program_rom_tev(u32 map_a, u32 map_b)
{
    gnt4_GXSetNumTevStages_bl(4);

    gnt4_GXSetTevOrder_bl(0, 0, map_b, 0xff);
    gnt4_GXSetTevColorIn_bl(0, 0xf, 8, 0xe, 2);
    gnt4_GXSetTevColorOp_bl(0, 0, 0, 0, 0, 0);
    gnt4_GXSetTevAlphaIn_bl(0, 7, 4, 6, 1);
    gnt4_GXSetTevAlphaOp_bl(0, 1, 0, 0, 0, 0);
    gnt4_GXSetTevKColorSel_bl(0, 0xc);
    gnt4_GXSetTevKAlphaSel_bl(0, 0x1c);
    gnt4_GXSetTevSwapMode_bl(0, 0, 1);

    gnt4_GXSetTevOrder_bl(1, 1, map_a, 0xff);
    gnt4_GXSetTevColorIn_bl(1, 0xf, 8, 0xe, 0);
    gnt4_GXSetTevColorOp_bl(1, 0, 0, 1, 0, 0);
    gnt4_GXSetTevAlphaIn_bl(1, 7, 4, 6, 0);
    gnt4_GXSetTevAlphaOp_bl(1, 0, 0, 1, 0, 0);
    gnt4_GXSetTevKColorSel_bl(1, 0xd);
    gnt4_GXSetTevKAlphaSel_bl(1, 0x1d);
    gnt4_GXSetTevSwapMode_bl(1, 0, 0);

    gnt4_GXSetTevOrder_bl(2, 0, map_b, 0xff);
    gnt4_GXSetTevColorIn_bl(2, 0xf, 8, 0xe, 0);
    gnt4_GXSetTevColorOp_bl(2, 0, 0, 0, 1, 0);
    gnt4_GXSetTevAlphaIn_bl(2, 7, 4, 6, 0);
    gnt4_GXSetTevAlphaOp_bl(2, 1, 0, 0, 1, 0);
    gnt4_GXSetTevKColorSel_bl(2, 0xe);
    gnt4_GXSetTevKAlphaSel_bl(2, 0x1e);
    gnt4_GXSetTevSwapMode_bl(2, 0, 2);

    gnt4_GXSetTevOrder_bl(3, 0xff, 0xff, 0xff);
    gnt4_GXSetTevColorIn_bl(3, 0, 1, 0xe, 0xf);
    gnt4_GXSetTevColorOp_bl(3, 0, 0, 0, 1, 0);
    gnt4_GXSetTevAlphaIn_bl(3, 7, 7, 7, 7);
    gnt4_GXSetTevAlphaOp_bl(3, 0, 0, 0, 1, 0);
    gnt4_GXSetTevSwapMode_bl(3, 0, 0);
    gnt4_GXSetTevKColorSel_bl(3, 0xf);

    gnt4_GXSetTevSwapModeTable_bl(0, 0, 1, 2, 3);
    gnt4_GXSetTevSwapModeTable_bl(1, 0, 3, 3, 3);
    gnt4_GXSetTevSwapModeTable_bl(2, 0, 0, 3, 0);
}

/* A GXEnableTexOffsets call with the offsets DISABLED, exactly as all 16 of
 * the ROM's own call sites pass them. The host declares this a nop only in
 * that case and throws when either generator is enabled, so this proves the
 * common path rather than the refusal. */
extern void gnt4_GXEnableTexOffsets_bl(u32 coord, u32 line_offset, u32 point_offset);
void gx_call_tex_offsets_disabled(void)
{
    u32 i;
    for (i = 0; i < 8; i++) gnt4_GXEnableTexOffsets_bl(i, 0, 0);
}
