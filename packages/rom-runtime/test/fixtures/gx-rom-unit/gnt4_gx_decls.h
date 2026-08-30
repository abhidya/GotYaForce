/* gnt4_gx_decls.h -- prototypes for the out-of-window SDK callees this unit
 * calls. NOT gate output: this is the only file in this directory a human
 * wrote, and it deliberately adds NOTHING but declarations.
 *
 * WHY IT IS NEEDED. The assembly gate's merged `gnt4_shim.h` carries the DATA
 * symbols a window touches (PTR_DAT_80433930, DAT_80436108, DAT_8043610c,
 * DAT_803c0f40) and leaves function callees implicitly declared, which C99
 * rejects. Implicit declarations would also be wrong for this fixture in a way
 * that matters: an implicitly declared function returns `int`, so every GX
 * import would link as `(params) -> i32`, while the host's adapters all declare
 * FrameValueClass.VOID. The bridge builds signature-accurate per-import
 * trampolines, so a return-class mismatch is a real ABI disagreement, not a
 * cosmetic one. Declaring them `void` here makes the wasm import types match
 * the adapters exactly -- the same shape ../gx-selftest/gx_selftest.c declares
 * by hand.
 *
 * These signatures are the ones the DECOMPILED SDK bodies carry
 * (research/decomp/ghidra-export/chunk_0066.c / chunk_0067.c), not the
 * published SDK's -- pointer arguments where the corpus dereferences, and the
 * corpus's own argument order. `rom.c` is unedited gate output and calls them
 * exactly as the ROM does.
 */
#ifndef GNT4_GX_DECLS_H
#define GNT4_GX_DECLS_H

void gnt4_GXSetCullMode_bl(int mode);
void gnt4_GXSetBlendMode_bl(int type, int src, int dst, int op);
void gnt4_GXSetZMode_bl(int compare_enable, int func, int update_enable);
void gnt4_GXSetProjection_bl(const void *mtx44, int type);
void gnt4_GXLoadPosMtxImm_bl(const void *mtx3x4, int id);
void gnt4_GXSetCurrentMtx_bl(int id);
void gnt4_GXClearVtxDesc_bl(void);
void gnt4_GXSetVtxDesc_bl(int attr, int type);
void gnt4_GXSetVtxAttrFmt_bl(int vtxfmt, int attr, int cnt, int type, int frac);
void gnt4_GXSetNumChans_bl(int n);
void gnt4_GXSetNumTexGens_bl(int n);
void gnt4_GXSetNumTevStages_bl(int n);
void gnt4_GXSetChanCtrl_bl(int chan, int enable, int amb_src, int mat_src, int light_mask, int diff_fn, int attn_fn);
void gnt4_GXSetTevOrder_bl(int stage, int coord, int map, int color);
void gnt4_GXSetTevOp_bl(int stage, int mode);
void gnt4_GXBegin_bl(int prim, int vtxfmt, int nverts);

/* PSMTX* is the SDK's matrix library, not GX, but it is out-of-window all the
 * same and the host services it as a bridged callee. */
void gnt4_PSMTXIdentity_bl(float *mtx3x4);

#endif /* GNT4_GX_DECLS_H */
