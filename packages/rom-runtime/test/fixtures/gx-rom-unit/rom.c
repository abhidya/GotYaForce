#include "gf_gx_wgpipe.h"
#include "gnt4_shim.h"

// ==== 80027c34  zz_0027c34_ ====

void zz_0027c34_(void)

{
  undefined4 uVar1;
  float afStack_38 [14];

  if ((*(int *)(PTR_DAT_80433930 + 0x38) == 0) && (DAT_80436108 != 0)) {
    gnt4_GXSetCullMode_bl(2);
    gnt4_GXSetBlendMode_bl(1,4,5,0);
    gnt4_GXSetZMode_bl(1,7,0);
    gnt4_GXSetProjection_bl((undefined4 *)&DAT_803c0f40,1);
    gnt4_PSMTXIdentity_bl(afStack_38);
    gnt4_GXLoadPosMtxImm_bl(afStack_38,0);
    gnt4_GXSetCurrentMtx_bl(0);
    gnt4_GXClearVtxDesc_bl();
    gnt4_GXSetVtxDesc_bl(9,1);
    gnt4_GXSetVtxDesc_bl(0xb,1);
    gnt4_GXSetVtxAttrFmt_bl(0,9,0,3,0);
    gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
    gnt4_GXSetNumChans_bl(1);
    gnt4_GXSetNumTexGens_bl(0);
    gnt4_GXSetNumTevStages_bl(1);
    gnt4_GXSetChanCtrl_bl(4,0,1,1,0,0,2);
    gnt4_GXSetTevOrder_bl(0,0xff,0xff,4);
    gnt4_GXSetTevOp_bl(0,4);
    gnt4_GXBegin_bl(0x80,0,4);
    uVar1 = *DAT_8043610c;
    GF_WGPIPE_W16((0));
    GF_WGPIPE_W16((0));
    GF_WGPIPE_W32((uVar1));
    GF_WGPIPE_W16((0x280));
    GF_WGPIPE_W16((0));
    GF_WGPIPE_W32((uVar1));
    GF_WGPIPE_W16((0x280));
    GF_WGPIPE_W16((0x1c0));
    GF_WGPIPE_W32((uVar1));
    GF_WGPIPE_W16((0));
    GF_WGPIPE_W16((0x1c0));
    GF_WGPIPE_W32((uVar1));
  }
  return;
}
