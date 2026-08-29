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
