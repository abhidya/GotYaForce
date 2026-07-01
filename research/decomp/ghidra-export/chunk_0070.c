// ==== 80240d78  gnt4-TObjInit-bl ====

int gnt4_TObjInit_bl(int param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(DAT_803abc1c + 0x2c))();
  if (-1 < iVar1) {
    iVar1 = 0;
    *(undefined2 *)(param_1 + 0x4a) = 0xffff;
  }
  return iVar1;
}



// ==== 80240dd0  gnt4-TObjRelease-bl ====

void gnt4_TObjRelease_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                        double param_5,double param_6,double param_7,double param_8,int param_9,
                        undefined4 param_10,undefined4 param_11,undefined4 param_12,
                        undefined4 param_13,undefined4 param_14,undefined4 param_15,
                        undefined4 param_16)

{
  undefined4 *puVar1;
  int iVar2;
  undefined8 uVar3;
  
  uVar3 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(undefined4 **)(param_9 + 100),param_10,param_11,param_12,param_13,
                              param_14,param_15,param_16);
  if (*(undefined4 **)(param_9 + 0x5c) != (undefined4 *)0x0) {
    uVar3 = gnt4_hsdFreeMemPiece_bl
                      (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(undefined4 **)(param_9 + 0x5c),0x10,param_11,param_12,param_13,param_14,
                       param_15,param_16);
  }
  if (*(undefined4 **)(param_9 + 0xa8) != (undefined4 *)0x0) {
    uVar3 = gnt4_hsdFreeMemPiece_bl
                      (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(undefined4 **)(param_9 + 0xa8),0x20,param_11,param_12,param_13,param_14,
                       param_15,param_16);
  }
  if (*(int *)(param_9 + 0x6c) != 0) {
    for (iVar2 = 0; puVar1 = *(undefined4 **)(*(int *)(param_9 + 0x6c) + iVar2),
        puVar1 != (undefined4 *)0x0; iVar2 = iVar2 + 4) {
      if (puVar1 != (undefined4 *)0x0) {
        uVar3 = gnt4_hsdFreeMemPiece_bl
                          (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1,0x10
                           ,param_11,param_12,param_13,param_14,param_15,param_16);
      }
    }
    gnt4_HSD_Free_bl();
  }
  (**(code **)(DAT_803abc1c + 0x30))(param_9);
  return;
}



// ==== 80240e8c  gnt4-TObjAmnesia-bl ====

void gnt4_TObjAmnesia_bl(undefined **param_1)

{
  if (param_1 == DAT_804368b0) {
    DAT_804368b0 = (undefined **)0x0;
  }
  if (param_1 == &PTR_gnt4_TObjInfoInit_bl_803abc08) {
    DAT_804368b4 = 0;
  }
  (**(code **)(DAT_803abc1c + 0x38))();
  return;
}



// ==== 80240eec  gnt4-TObjInfoInit-bl ====

void gnt4_TObjInfoInit_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_hsdInitClassInfo_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc543f8,
             &PTR_zz_025acb8__803ad548,s_sysdolphin_base_library_803ac0b0,s_hsd_tobj_803ac0c8,0x4c,
             0xac,in_r9,in_r10);
  DAT_803abc34 = gnt4_TObjInit_bl;
  DAT_803abc38 = gnt4_TObjRelease_bl;
  DAT_803abc40 = gnt4_TObjAmnesia_bl;
  DAT_803abc48 = gnt4_TObjLoad_bl;
  DAT_803abc4c = gnt4_TObjMakeTExp_bl;
  DAT_803abc44 = gnt4_MakeTextureMtx_bl;
  DAT_803abc50 = gnt4_TObjUpdateFunc_bl;
  return;
}



// ==== 80240f90  gnt4-HSD_SetupChannelMode-bl ====

void gnt4_HSD_SetupChannelMode_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined *puVar6;
  undefined4 extraout_r4_01;
  uint uVar7;
  int iVar8;
  uint uVar9;
  undefined8 extraout_f1;
  undefined8 uVar10;
  ulonglong uVar11;
  undefined4 local_38 [14];
  
  uVar11 = gnt4__savegpr_23_bl();
  uVar7 = (uint)(uVar11 >> 0x20);
  uVar5 = (undefined4)uVar11;
  uVar9 = uVar7 & 3;
  bVar2 = false;
  bVar1 = false;
  if ((uVar11 & 0x300000000) == 0) {
    uVar9 = 0;
  }
  uVar7 = uVar7 & 0x6000;
  if ((uVar11 & 0x600000000000) == 0) {
    uVar7 = uVar9 << 0xd;
  }
  uVar10 = extraout_f1;
  if ((uVar11 & 0x800000000) != 0) {
    DAT_803ac0f8 = gnt4_HSD_LObjGetLightMaskSpecular_bl();
    uVar10 = gnt4_HSD_SetupChannel_bl(-0x7fc53f28,&DAT_803ac0d8,param_11,param_12);
    bVar2 = true;
    iVar3 = gnt4_HSD_LObjGetNbActive_bl();
    uVar5 = 0x80400000;
    for (iVar8 = 0; iVar8 < iVar3; iVar8 = iVar8 + 1) {
      iVar4 = gnt4_HSD_LObjGetActiveByIndex_bl(iVar8);
      if (iVar4 != 0) {
        local_38[0] = *(undefined4 *)(iVar4 + 0x10);
        uVar10 = gnt4_HSD_LObjSetup_bl((double)DAT_803f8d00,iVar4,(char *)local_38);
        uVar5 = extraout_r4;
      }
    }
  }
  if ((uVar11 & 0x400000000) == 0) {
    DAT_803ac1b4 = uVar9 >> 1;
    gnt4_HSD_SetupChannel_bl(-0x7fc53e68,uVar5,param_11,param_12);
    DAT_803ac1e4 = uVar7 >> 0xe;
    gnt4_HSD_SetupChannel_bl(-0x7fc53e38,extraout_r4_01,param_11,param_12);
  }
  else {
    iVar3 = gnt4_HSD_LObjGetActiveByID_bl
                      (uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x100,uVar5,
                       param_11,param_12,param_13,param_14,param_15,param_16);
    if ((iVar3 == 0) || ((*(ushort *)(iVar3 + 8) & 4) == 0)) {
      DAT_803ac114 = DAT_80435e20;
    }
    else {
      param_11 = &DAT_803ac114;
      gnt4_HSD_MulColor_bl((byte *)&DAT_803f8cf0,(byte *)(iVar3 + 0x10),(undefined1 *)&DAT_803ac114)
      ;
    }
    DAT_803ac124 = uVar9 >> 1;
    DAT_803ac128 = gnt4_HSD_LObjGetLightMaskDiffuse_bl();
    gnt4_HSD_SetupChannel_bl(-0x7fc53ef8,&DAT_803ac108,param_11,param_12);
    bVar1 = (uVar7 & 0x4000) == 0;
    if (bVar1) {
      DAT_803ac13c = 2;
    }
    else {
      DAT_803ac13c = 3;
      gnt4_HSD_SetupChannel_bl(-0x7fc53e98,extraout_r4_00,param_11,param_12);
    }
    bVar1 = !bVar1;
    DAT_803ac158 = gnt4_HSD_LObjGetLightMaskAlpha_bl();
    puVar6 = &DAT_803ac138;
    if ((iVar3 == 0) || ((*(ushort *)(iVar3 + 8) & 0x10) == 0)) {
      uVar7 = 0;
    }
    else {
      uVar7 = (uint)*(byte *)(iVar3 + 0x13);
    }
    DAT_803ac14c = DAT_803ac158 != 0;
    DAT_803ac14b = (char)uVar7;
    if ((bool)DAT_803ac14c) {
      puVar6 = (undefined *)0x1;
      DAT_803ac14b = 0xff;
      DAT_803ac147 = (char)uVar7;
    }
    gnt4_HSD_SetupChannel_bl(-0x7fc53ec8,puVar6,uVar7,param_12);
  }
  if (bVar2) {
    if (!bVar1) {
      gnt4_HSD_DisableChannelLighting_bl(3);
    }
    gnt4_HSD_StateSetNumChans_bl(2);
  }
  else if (bVar1) {
    gnt4_HSD_DisableChannelLighting_bl(1);
    gnt4_HSD_StateSetNumChans_bl(2);
  }
  else {
    gnt4_HSD_DisableChannelLighting_bl(5);
    gnt4_HSD_StateSetNumChans_bl(1);
  }
  gnt4__restgpr_23_bl();
  return;
}



// ==== 802411cc  gnt4-HSD_SetupRenderModeWithCustomPE-bl ====

void gnt4_HSD_SetupRenderModeWithCustomPE_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,uint param_9,byte *param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  byte *pbVar2;
  undefined4 extraout_r4;
  undefined4 *puVar3;
  uint uVar4;
  uint uVar5;
  undefined8 uVar6;
  undefined1 auStack_88 [4];
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  
  pbVar2 = param_10;
  iVar1 = gnt4_HSD_StateGetNumTevStages();
  if (iVar1 == 0) {
    local_84 = 0;
    local_80 = gnt4_HSD_StateAssignTev_bl
                         (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,pbVar2,
                          param_11,param_12,param_13,param_14,param_15,param_16);
    local_7c = 0xff;
    local_78 = 0xff;
    local_74 = 4;
    local_70 = 4;
    gnt4_HSD_SetupTevStage_bl((int)auStack_88);
  }
  if (param_10 == (byte *)0x0) {
    gnt4_HSD_StateSetColorUpdate_bl(1);
    gnt4_HSD_StateSetAlphaUpdate_bl(0);
    gnt4_HSD_StateSetDstAlpha_bl(0,0);
    gnt4_HSD_StateSetBlendMode_bl(param_9 >> 0x1e & 1,4,5,0xf);
    uVar4 = 3;
    if ((param_9 & 0x8000000) != 0) {
      uVar4 = 7;
    }
    gnt4_HSD_StateSetZMode_bl(1,uVar4,param_9 >> 0x1d & 1 ^ 1);
    if (((param_9 & 0x20000000) == 0) && ((param_9 & 0x40000000) != 0)) {
      gnt4_HSD_StateSetZCompLoc_bl(0);
      puVar3 = (undefined4 *)0x0;
      uVar4 = 4;
      uVar5 = 0;
      gnt4_HSD_StateSetAlphaCompare_bl(4,0,0,4,0);
    }
    else {
      gnt4_HSD_StateSetZCompLoc_bl(1);
      puVar3 = (undefined4 *)0x0;
      uVar4 = 7;
      uVar5 = 0;
      gnt4_HSD_StateSetAlphaCompare_bl(7,0,0,7,0);
    }
    gnt4_HSD_StateSetDither_bl(0);
  }
  else {
    gnt4_HSD_StateSetColorUpdate_bl(*param_10 & 1);
    gnt4_HSD_StateSetAlphaUpdate_bl(*param_10 & 2);
    gnt4_HSD_StateSetDstAlpha_bl(*param_10 & 4,(uint)param_10[3]);
    gnt4_HSD_StateSetBlendMode_bl
              ((uint)param_10[4],(uint)param_10[5],(uint)param_10[6],(uint)param_10[7]);
    gnt4_HSD_StateSetZMode_bl(*param_10 & 0x10,(uint)param_10[8],*param_10 & 0x20);
    gnt4_HSD_StateSetZCompLoc_bl(*param_10 & 8);
    puVar3 = (undefined4 *)(uint)param_10[10];
    uVar4 = (uint)param_10[0xb];
    uVar5 = (uint)param_10[2];
    gnt4_HSD_StateSetAlphaCompare_bl((uint)param_10[9],(uint)param_10[1],(uint)puVar3,uVar4,uVar5);
    gnt4_HSD_StateSetDither_bl(*param_10 & 0x40);
  }
  gnt4_HSD_SetTevRegAll_bl();
  gnt4_HSD_StateSetNumTevStages_bl();
  uVar6 = gnt4_HSD_StateSetNumTexGens_bl();
  gnt4_HSD_SetupChannelMode_bl
            (uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
             puVar3,uVar4,uVar5,param_14,param_15,param_16);
  return;
}



// ==== 8024139c  gnt4-HSD_SetMaterialColor-bl ====

void gnt4_HSD_SetMaterialColor_bl
               (double param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_8043d1d8;
  DAT_803f8cf0 = *param_2;
  DAT_803f8cf4 = *param_3;
  DAT_803f8cf8 = *param_4;
  if ((dVar1 < param_1) && (dVar1 = param_1, (double)FLOAT_8043d1dc <= param_1)) {
    dVar1 = (double)FLOAT_8043d1dc;
  }
  DAT_803f8cfc = (char)(int)((double)FLOAT_8043d1e0 * dVar1);
  return;
}



// ==== 80241410  gnt4-HSD_SetMaterialShininess-bl ====

void gnt4_HSD_SetMaterialShininess_bl(double param_1)

{
  DAT_803f8d00 = (float)param_1;
  return;
}



// ==== 80241420  gnt4-HSD_StateSetCullMode-bl ====

void gnt4_HSD_StateSetCullMode_bl(uint param_1)

{
  if (DAT_804368ec != param_1) {
    gnt4_GXSetCullMode_bl(param_1);
    DAT_804368ec = param_1;
  }
  return;
}



// ==== 8024145c  gnt4-HSD_StateSetBlendMode-bl ====

void gnt4_HSD_StateSetBlendMode_bl(uint param_1,uint param_2,uint param_3,uint param_4)

{
  if ((((DAT_804368e8 != param_1) || (DAT_804368e4 != param_2)) || (DAT_804368e0 != param_3)) ||
     (DAT_804368dc != param_4)) {
    gnt4_GXSetBlendMode_bl(param_1,param_2,param_3,param_4);
    DAT_804368dc = param_4;
    DAT_804368e0 = param_3;
    DAT_804368e4 = param_2;
    DAT_804368e8 = param_1;
  }
  return;
}



// ==== 802414fc  gnt4-HSD_StateSetZMode-bl ====

void gnt4_HSD_StateSetZMode_bl(uint param_1,uint param_2,uint param_3)

{
  uint uVar1;
  uint uVar2;
  
  uVar1 = (-param_1 | param_1) >> 0x1f;
  uVar2 = (-param_3 | param_3) >> 0x1f;
  if (((DAT_804368d8 != uVar1) || (DAT_804368d4 != param_2)) || (DAT_804368d0 != uVar2)) {
    gnt4_GXSetZMode_bl(uVar1,param_2,uVar2);
    DAT_804368d8 = (byte)((-param_1 | param_1) >> 0x1f);
    DAT_804368d0 = (byte)((-param_3 | param_3) >> 0x1f);
    DAT_804368d4 = param_2;
  }
  return;
}



// ==== 8024158c  gnt4-HSD_StateSetAlphaCompare-bl ====

void gnt4_HSD_StateSetAlphaCompare_bl
               (undefined4 param_1,undefined4 param_2,uint param_3,uint param_4,uint param_5)

{
  uint uVar1;
  undefined8 uVar2;
  
  uVar2 = gnt4__savegpr_27_bl();
  uVar1 = (uint)((ulonglong)uVar2 >> 0x20);
  if ((((DAT_804368cc != uVar1) || ((uint)DAT_804368c8 != ((uint)uVar2 & 0xff))) ||
      (DAT_804368c4 != param_3)) ||
     ((DAT_804368c0 != param_4 || ((uint)DAT_804368be != (param_5 & 0xff))))) {
    gnt4_GXSetAlphaCompare_bl(uVar1,(uint)uVar2,param_3,param_4,param_5);
    DAT_804368c8 = (byte)uVar2;
    DAT_804368be = (byte)param_5;
    DAT_804368c0 = param_4;
    DAT_804368c4 = param_3;
    DAT_804368cc = uVar1;
  }
  gnt4__restgpr_27_bl();
  return;
}



// ==== 8024163c  gnt4-HSD_StateSetColorUpdate-bl ====

void gnt4_HSD_StateSetColorUpdate_bl(uint param_1)

{
  uint uVar1;
  
  uVar1 = (-param_1 | param_1) >> 0x1f;
  if (DAT_804368bd != uVar1) {
    gnt4_GXSetColorUpdate_bl(uVar1);
    DAT_804368bd = (byte)((-param_1 | param_1) >> 0x1f);
  }
  return;
}



// ==== 80241684  gnt4-HSD_StateSetAlphaUpdate-bl ====

void gnt4_HSD_StateSetAlphaUpdate_bl(uint param_1)

{
  uint uVar1;
  
  uVar1 = (-param_1 | param_1) >> 0x1f;
  if (DAT_804368bc != uVar1) {
    gnt4_GXSetAlphaUpdate_bl(uVar1);
    DAT_804368bc = (byte)((-param_1 | param_1) >> 0x1f);
  }
  return;
}



// ==== 802416cc  gnt4-HSD_StateSetDstAlpha-bl ====

void gnt4_HSD_StateSetDstAlpha_bl(uint param_1,uint param_2)

{
  uint uVar1;
  
  uVar1 = (-param_1 | param_1) >> 0x1f;
  if ((DAT_804368bb != uVar1) || ((uint)DAT_804368ba != (param_2 & 0xff))) {
    gnt4_GXSetDstAlpha_bl(uVar1,param_2);
    DAT_804368bb = (byte)((-param_1 | param_1) >> 0x1f);
    DAT_804368ba = (byte)param_2;
  }
  return;
}



// ==== 80241738  gnt4-HSD_StateSetZCompLoc-bl ====

void gnt4_HSD_StateSetZCompLoc_bl(uint param_1)

{
  uint uVar1;
  
  uVar1 = (-param_1 | param_1) >> 0x1f;
  if (DAT_804368b9 != uVar1) {
    gnt4_GXSetZCompLoc_bl(uVar1);
    DAT_804368b9 = (byte)((-param_1 | param_1) >> 0x1f);
  }
  return;
}



// ==== 80241780  gnt4-HSD_StateSetDither-bl ====

void gnt4_HSD_StateSetDither_bl(uint param_1)

{
  uint uVar1;
  
  uVar1 = (-param_1 | param_1) >> 0x1f;
  if (DAT_804368b8 != uVar1) {
    gnt4_GXSetDither_bl(uVar1);
    DAT_804368b8 = (byte)((-param_1 | param_1) >> 0x1f);
  }
  return;
}



// ==== 802417c8  gnt4-_HSD_StateInvalidatePrimitive-bl ====

void gnt4__HSD_StateInvalidatePrimitive_bl(void)

{
  DAT_804368f0 = 0;
  DAT_804368ec = 0xffffffff;
  DAT_804368f1 = 0xff;
  return;
}



// ==== 802417e4  gnt4-_HSD_StateInvalidateVtxAttr-bl ====

void gnt4__HSD_StateInvalidateVtxAttr_bl(void)

{
  gnt4_HSD_ClearVtxDesc_bl();
  return;
}



// ==== 80241804  gnt4-_HSD_StateInvalidateRenderMode-bl ====

void gnt4__HSD_StateInvalidateRenderMode_bl(void)

{
  DAT_804368e8 = 0xffffffff;
  DAT_804368e4 = 0xffffffff;
  DAT_804368e0 = 0xffffffff;
  DAT_804368dc = 0xffffffff;
  DAT_804368d8 = 0xff;
  DAT_804368d4 = 0xffffffff;
  DAT_804368d0 = 0xff;
  DAT_804368cc = 0xffffffff;
  DAT_804368c8 = 0;
  DAT_804368c4 = 0xffffffff;
  DAT_804368c0 = 0xffffffff;
  DAT_804368be = 0;
  DAT_804368bd = 0xff;
  DAT_804368bc = 0xff;
  DAT_804368bb = 0xff;
  DAT_804368ba = 0;
  DAT_804368b9 = 0xff;
  DAT_804368b8 = 0xff;
  return;
}



// ==== 8024185c  gnt4-HSD_StateInvalidate-bl ====

void gnt4_HSD_StateInvalidate_bl(uint param_1)

{
  uint *puVar1;
  
  puVar1 = &DAT_803ac1f8;
  while( true ) {
    if (*puVar1 == 0) break;
    if ((param_1 & *puVar1) != 0) {
      (*(code *)puVar1[1])();
    }
    puVar1 = puVar1 + 2;
  }
  return;
}



// ==== 802418bc  gnt4-HSD_RenderInitAllocData-bl ====

void gnt4_HSD_RenderInitAllocData_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar1;
  
  uVar1 = gnt4_HSD_ObjAllocInit_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803f8d08,
                     0x1c,4,in_r6,in_r7,in_r8,in_r9,in_r10);
  uVar1 = gnt4_HSD_ObjAllocInit_bl
                    (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803f8d34,
                     0x14,4,in_r6,in_r7,in_r8,in_r9,in_r10);
  gnt4_HSD_ObjAllocInit_bl
            (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803f8d60,0x30,4,
             in_r6,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 80241918  gnt4-HSD_SetupChannel-bl ====

void gnt4_HSD_SetupChannel_bl(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  uint uVar1;
  uint uVar2;
  undefined4 *puVar3;
  int iVar4;
  uint local_28;
  uint local_24;
  uint local_20;
  uint local_1c [3];
  
  if (param_1 == 0) {
    return;
  }
  uVar2 = *(uint *)(param_1 + 4);
  if (uVar2 == 0xff) {
    return;
  }
  uVar1 = uVar2 & 1;
  if ((*(char *)(param_1 + 0x14) != '\0') && (*(int *)(param_1 + 0x18) == 0)) {
    puVar3 = &DAT_80436908;
    if ((&DAT_80436908)[uVar1] == 0) {
      if ((uVar2 == 4) || (uVar2 == 5)) {
        puVar3 = (undefined4 *)(uVar1 * 0x30);
        if (*(int *)(param_1 + 0xc) != *(int *)(&DAT_803ac274 + (int)puVar3)) {
          *(int *)(&DAT_803ac274 + (int)puVar3) = *(int *)(param_1 + 0xc);
          goto LAB_80241a60;
        }
      }
      else if ((uVar2 == 0) || (uVar2 == 1)) {
        if (((*(uint *)(param_1 + 0xc) ^ *(uint *)(&DAT_803ac274 + uVar1 * 0x30)) & 0xffffff00) != 0
           ) {
          puVar3 = (undefined4 *)
                   (*(uint *)(&DAT_803ac274 + uVar1 * 0x30) & 0xff |
                   *(uint *)(param_1 + 0xc) & 0xffffff00);
          *(undefined4 **)(&DAT_803ac274 + uVar1 * 0x30) = puVar3;
          goto LAB_80241a60;
        }
      }
      else if (*(char *)(param_1 + 0xf) != (&DAT_803ac277)[uVar1 * 0x30]) {
        (&DAT_803ac277)[uVar1 * 0x30] = *(char *)(param_1 + 0xf);
LAB_80241a60:
        local_20 = *(uint *)(param_1 + 0xc);
        gnt4_GXSetChanAmbColor_bl(uVar2,&local_20,puVar3,param_4);
      }
    }
    else {
      (&DAT_80436908)[uVar1] = 0;
      local_1c[0] = *(uint *)(param_1 + 0xc);
      gnt4_GXSetChanAmbColor_bl(uVar1 + 4,local_1c,&DAT_80436908,param_4);
      *(undefined4 *)(&DAT_803ac274 + uVar1 * 0x30) = *(undefined4 *)(param_1 + 0xc);
    }
  }
  if (*(int *)(param_1 + 0x1c) == 0) {
    puVar3 = &DAT_80436900;
    if ((&DAT_80436900)[uVar1] == 0) {
      if ((uVar2 == 4) || (uVar2 == 5)) {
        puVar3 = (undefined4 *)(uVar1 * 0x30);
        if (*(int *)(param_1 + 0x10) == *(int *)(&DAT_803ac278 + (int)puVar3)) goto LAB_80241b84;
        *(int *)(&DAT_803ac278 + (int)puVar3) = *(int *)(param_1 + 0x10);
      }
      else if ((uVar2 == 0) || (uVar2 == 1)) {
        if (((*(uint *)(param_1 + 0x10) ^ *(uint *)(&DAT_803ac278 + uVar1 * 0x30)) & 0xffffff00) ==
            0) goto LAB_80241b84;
        puVar3 = (undefined4 *)
                 (*(uint *)(&DAT_803ac278 + uVar1 * 0x30) & 0xff |
                 *(uint *)(param_1 + 0x10) & 0xffffff00);
        *(undefined4 **)(&DAT_803ac278 + uVar1 * 0x30) = puVar3;
      }
      else {
        if (*(char *)(param_1 + 0x13) == (&DAT_803ac27b)[uVar1 * 0x30]) goto LAB_80241b84;
        (&DAT_803ac27b)[uVar1 * 0x30] = *(char *)(param_1 + 0x13);
      }
      local_28 = *(uint *)(param_1 + 0x10);
      gnt4_GXSetChanMatColor_bl(uVar2,&local_28,puVar3,param_4);
    }
    else {
      (&DAT_80436900)[uVar1] = 0;
      local_24 = *(uint *)(param_1 + 0x10);
      gnt4_GXSetChanMatColor_bl(uVar1 + 4,&local_24,&DAT_80436900,param_4);
      *(undefined4 *)(&DAT_803ac278 + uVar1 * 0x30) = *(undefined4 *)(param_1 + 0x10);
    }
  }
LAB_80241b84:
  iVar4 = (uVar2 & 3) * 0x30;
  if ((((((uint)*(byte *)(param_1 + 0x14) != (uint)(byte)(&DAT_803ac27c)[iVar4]) ||
        (*(int *)(param_1 + 0x18) != *(int *)(&DAT_803ac280 + iVar4))) ||
       (*(int *)(param_1 + 0x1c) != *(int *)(&DAT_803ac284 + iVar4))) ||
      ((*(int *)(param_1 + 0x20) != *(int *)(&DAT_803ac288 + iVar4) ||
       (*(int *)(param_1 + 0x24) != *(int *)(&DAT_803ac28c + iVar4))))) ||
     (*(int *)(param_1 + 0x28) != *(int *)(&DAT_803ac290 + iVar4))) {
    gnt4_GXSetChanCtrl_bl
              (uVar2,(uint)*(byte *)(param_1 + 0x14),*(uint *)(param_1 + 0x18),
               *(uint *)(param_1 + 0x1c),*(uint *)(param_1 + 0x20),*(uint *)(param_1 + 0x24),
               *(int *)(param_1 + 0x28));
    (&DAT_803ac27c)[iVar4] = *(byte *)(param_1 + 0x14);
    *(undefined4 *)(&DAT_803ac280 + iVar4) = *(undefined4 *)(param_1 + 0x18);
    *(undefined4 *)(&DAT_803ac284 + iVar4) = *(undefined4 *)(param_1 + 0x1c);
    *(undefined4 *)(&DAT_803ac288 + iVar4) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(&DAT_803ac28c + iVar4) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(&DAT_803ac290 + iVar4) = *(undefined4 *)(param_1 + 0x28);
    if ((uVar2 == 4) || (uVar2 == 5)) {
      (&DAT_803ac2dc)[iVar4] = *(undefined1 *)(param_1 + 0x14);
      *(undefined4 *)(&DAT_803ac2e0 + iVar4) = *(undefined4 *)(param_1 + 0x18);
      *(undefined4 *)(&DAT_803ac2e4 + iVar4) = *(undefined4 *)(param_1 + 0x1c);
      *(undefined4 *)(&DAT_803ac2e8 + iVar4) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(&DAT_803ac2ec + iVar4) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(&DAT_803ac2f0 + iVar4) = *(undefined4 *)(param_1 + 0x28);
    }
  }
  return;
}



// ==== 80241cbc  gnt4-HSD_DisableChannelLighting-bl ====

void gnt4_HSD_DisableChannelLighting_bl(uint param_1)

{
  int iVar1;
  
  if (((int)param_1 < 6) && (3 < (int)param_1)) {
    iVar1 = (param_1 & 3) * 0x30;
    if (((&DAT_803ac27c)[iVar1] != '\0') || ((&DAT_803ac2dc)[iVar1] != '\0')) {
      (&DAT_803ac2dc)[iVar1] = 0;
      (&DAT_803ac27c)[iVar1] = '\0';
      *(undefined4 *)(&DAT_803ac2e8 + iVar1) = 0;
      *(undefined4 *)(&DAT_803ac288 + iVar1) = 0;
      *(uint *)(&DAT_803ac2e0 + iVar1) = *(uint *)(&DAT_803ac280 + iVar1);
      *(uint *)(&DAT_803ac2e4 + iVar1) = *(uint *)(&DAT_803ac284 + iVar1);
      *(uint *)(&DAT_803ac2ec + iVar1) = *(uint *)(&DAT_803ac28c + iVar1);
      *(int *)(&DAT_803ac2f0 + iVar1) = *(int *)(&DAT_803ac290 + iVar1);
      gnt4_GXSetChanCtrl_bl
                (param_1,0,*(uint *)(&DAT_803ac280 + iVar1),*(uint *)(&DAT_803ac284 + iVar1),0,
                 *(uint *)(&DAT_803ac28c + iVar1),*(int *)(&DAT_803ac290 + iVar1));
    }
  }
  else {
    iVar1 = (param_1 & 3) * 0x30;
    if ((&DAT_803ac27c)[iVar1] != '\0') {
      (&DAT_803ac27c)[iVar1] = '\0';
      *(undefined4 *)(&DAT_803ac288 + iVar1) = 0;
      gnt4_GXSetChanCtrl_bl
                (param_1,0,*(uint *)(&DAT_803ac280 + iVar1),*(uint *)(&DAT_803ac284 + iVar1),0,
                 *(uint *)(&DAT_803ac28c + iVar1),*(int *)(&DAT_803ac290 + iVar1));
    }
  }
  return;
}



// ==== 80241db4  gnt4-HSD_StateSetNumChans-bl ====

void gnt4_HSD_StateSetNumChans_bl(uint param_1)

{
  if (DAT_804368fc != param_1) {
    gnt4_GXSetNumChans_bl(param_1 & 0xff);
    DAT_804368fc = param_1;
  }
  return;
}



// ==== 80241df4  gnt4-HSD_StateRegisterTexGen-bl ====

void gnt4_HSD_StateRegisterTexGen_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = gnt4_HSD_TexCoordID2Num_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                     param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  if (DAT_804368f8 < iVar1) {
    DAT_804368f8 = iVar1;
  }
  return;
}



// ==== 80241e24  gnt4-HSD_StateSetNumTexGens-bl ====

void gnt4_HSD_StateSetNumTexGens_bl(void)

{
  gnt4_GXSetNumTexGens_bl(DAT_804368f8 & 0xff);
  DAT_804368f8 = 0;
  return;
}



// ==== 80241e54  gnt4-HSD_StateInitTev ====

void gnt4_HSD_StateInitTev(void)

{
  DAT_80436910 = 0;
  return;
}



// ==== 80241e60  gnt4-HSD_StateGetNumTevStages ====

undefined4 gnt4_HSD_StateGetNumTevStages(void)

{
  return DAT_80436910;
}



// ==== 80241e68  gnt4-HSD_StateAssignTev-bl ====

void gnt4_HSD_StateAssignTev_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = DAT_80436910;
  DAT_80436910 = DAT_80436910 + 1;
  gnt4_HSD_Index2TevStage_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,param_10,param_11
             ,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80241e94  gnt4-HSD_StateSetNumTevStages-bl ====

void gnt4_HSD_StateSetNumTevStages_bl(void)

{
  gnt4_GXSetNumTevStages_bl(DAT_80436910 & 0xff);
  DAT_80436910 = 0;
  return;
}



// ==== 80241ec4  gnt4-HSD_SetupTevStage-bl ====

void gnt4_HSD_SetupTevStage_bl(int param_1)

{
  gnt4_GXSetTevOrder_bl
            (*(uint *)(param_1 + 8),*(uint *)(param_1 + 0xc),*(uint *)(param_1 + 0x10),
             *(int *)(param_1 + 0x14));
  if (*(int *)(param_1 + 4) == 0) {
    gnt4_GXSetTevOp_bl(*(int *)(param_1 + 8),*(int *)(param_1 + 0x18));
    gnt4_GXSetTevSwapMode_bl(*(int *)(param_1 + 8),0,0);
  }
  else {
    gnt4_GXSetTevColorOp_bl
              (*(int *)(param_1 + 8),*(uint *)(param_1 + 0x18),*(uint *)(param_1 + 0x30),
               *(uint *)(param_1 + 0x2c),(uint)*(byte *)(param_1 + 0x34),*(uint *)(param_1 + 0x38));
    gnt4_GXSetTevColorIn_bl
              (*(int *)(param_1 + 8),*(uint *)(param_1 + 0x1c),*(uint *)(param_1 + 0x20),
               *(uint *)(param_1 + 0x24),*(uint *)(param_1 + 0x28));
    gnt4_GXSetTevAlphaOp_bl
              (*(int *)(param_1 + 8),*(uint *)(param_1 + 0x3c),*(uint *)(param_1 + 0x54),
               *(uint *)(param_1 + 0x50),(uint)*(byte *)(param_1 + 0x58),*(uint *)(param_1 + 0x5c));
    gnt4_GXSetTevAlphaIn_bl
              (*(int *)(param_1 + 8),*(uint *)(param_1 + 0x40),*(uint *)(param_1 + 0x44),
               *(uint *)(param_1 + 0x48),*(uint *)(param_1 + 0x4c));
    gnt4_GXSetTevSwapMode_bl
              (*(int *)(param_1 + 8),*(uint *)(param_1 + 100),*(uint *)(param_1 + 0x68));
    gnt4_GXSetTevKColorSel_bl(*(uint *)(param_1 + 8),*(uint *)(param_1 + 0x6c));
    gnt4_GXSetTevKAlphaSel_bl(*(uint *)(param_1 + 8),*(uint *)(param_1 + 0x70));
  }
  return;
}



// ==== 80241fbc  gnt4-HSD_Index2TevStage-bl ====

undefined4
gnt4_HSD_Index2TevStage_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  switch(param_9) {
  case 0:
    uVar1 = 0;
    break;
  case 1:
    uVar1 = 1;
    break;
  case 2:
    uVar1 = 2;
    break;
  case 3:
    uVar1 = 3;
    break;
  case 4:
    uVar1 = 4;
    break;
  case 5:
    uVar1 = 5;
    break;
  case 6:
    uVar1 = 6;
    break;
  case 7:
    uVar1 = 7;
    break;
  case 8:
    uVar1 = 8;
    break;
  case 9:
    uVar1 = 9;
    break;
  case 10:
    uVar1 = 10;
    break;
  case 0xb:
    uVar1 = 0xb;
    break;
  case 0xc:
    uVar1 = 0xc;
    break;
  case 0xd:
    uVar1 = 0xd;
    break;
  case 0xe:
    uVar1 = 0xe;
    break;
  case 0xf:
    uVar1 = 0xf;
    break;
  default:
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e28,
                     0x307,&DAT_80435e30,param_12,param_13,param_14,param_15,param_16);
    uVar1 = 0xf;
  }
  return uVar1;
}



// ==== 8024208c  gnt4-HSD_SetTevRegAll-bl ====

void gnt4_HSD_SetTevRegAll_bl(void)

{
  int iVar1;
  uint uVar2;
  undefined4 *puVar3;
  undefined4 local_18;
  undefined4 local_14;
  
  puVar3 = &DAT_803ac238;
  uVar2 = 0;
  do {
    if (puVar3[2] != 0) {
      local_18 = *puVar3;
      local_14 = puVar3[1];
      if (uVar2 == 2) {
        iVar1 = 3;
      }
      else if ((int)uVar2 < 2) {
        if (uVar2 == 0) {
          iVar1 = 1;
        }
        else {
          if ((int)uVar2 < 0) goto LAB_80242110;
          iVar1 = 2;
        }
      }
      else if ((int)uVar2 < 4) {
        iVar1 = 0;
      }
      else {
LAB_80242110:
        iVar1 = 1;
      }
      gnt4_GXSetTevColorS10_bl(iVar1,(short *)&local_18);
      puVar3[2] = 0;
    }
    uVar2 = uVar2 + 1;
    puVar3 = puVar3 + 3;
    if (3 < uVar2) {
      return;
    }
  } while( true );
}



// ==== 8024214c  gnt4-HSD_TexCoordID2Num-bl ====

undefined4
gnt4_HSD_TexCoordID2Num_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  if (param_9 == 5) {
    return 6;
  }
  if (param_9 < 5) {
    if (param_9 == 2) {
      return 3;
    }
    if (1 < param_9) {
      if (param_9 < 4) {
        return 4;
      }
      return 5;
    }
    if (param_9 == 0) {
      return 1;
    }
    if (-1 < param_9) {
      return 2;
    }
  }
  else {
    if (param_9 == 0xff) {
      return 0;
    }
    if (param_9 < 0xff) {
      if (param_9 == 7) {
        return 8;
      }
      if (param_9 < 7) {
        return 7;
      }
    }
  }
  gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e28,
                   0x434,&DAT_80435e30,param_12,param_13,param_14,param_15,param_16);
  return 0;
}



// ==== 80242214  gnt4-_HSD_StateInvalidateColorChannel-bl ====

void gnt4__HSD_StateInvalidateColorChannel_bl(void)

{
  gnt4_memcpy(&DAT_803ac268,&DAT_803ac368,0xc0);
  DAT_80436908 = 1;
  uRam8043690c = 1;
  DAT_80436900 = 1;
  uRam80436904 = 1;
  DAT_804368fc = 0xffffffff;
  return;
}



// ==== 8024226c  gnt4-_HSD_StateInvalidateTevStage ====

void gnt4__HSD_StateInvalidateTevStage(void)

{
  DAT_80436910 = 0;
  return;
}



// ==== 80242278  gnt4-_HSD_StateInvalidateTevRegister ====

void gnt4__HSD_StateInvalidateTevRegister(void)

{
  DAT_803ac240 = 0;
  DAT_803ac24c = 0;
  DAT_803ac258 = 0;
  DAT_803ac264 = 0;
  return;
}



// ==== 80242298  gnt4-_HSD_StateInvalidateTexCoordGen ====

void gnt4__HSD_StateInvalidateTexCoordGen(void)

{
  DAT_804368f8 = 0;
  return;
}



// ==== 802422a4  gnt4-HSD_MObjSetCurrent-bl ====

void gnt4_HSD_MObjSetCurrent_bl(undefined4 param_1)

{
  DAT_8043691c = param_1;
  return;
}



// ==== 802422ac  gnt4-HSD_MObjSetFlags-bl ====

void gnt4_HSD_MObjSetFlags_bl(int param_1,uint param_2)

{
  if (param_1 == 0) {
    return;
  }
  *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) | param_2;
  return;
}



// ==== 802422c4  zz_02422c4_ ====

void zz_02422c4_(int param_1,uint param_2)

{
  if (param_1 == 0) {
    return;
  }
  *(uint *)(param_1 + 4) = *(uint *)(param_1 + 4) & ~param_2;
  return;
}



// ==== 802422dc  zz_02422dc_ ====

void zz_02422dc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,uint param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint extraout_r4;
  uint uVar1;
  
  if (param_9 != 0) {
    uVar1 = param_10;
    if ((param_10 & 4) != 0) {
      param_1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    *(undefined4 **)(param_9 + 0x14),param_10,param_11,param_12,
                                    param_13,param_14,param_15,param_16);
      *(undefined4 *)(param_9 + 0x14) = 0;
      uVar1 = extraout_r4;
    }
    if ((param_10 & 0x10) != 0) {
      zz_023de9c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 8),uVar1,param_11,param_12,param_13,param_14,param_15,param_16)
      ;
    }
  }
  return;
}



// ==== 8024233c  gnt4-HSD_MObjAddAnim-bl ====

void gnt4_HSD_MObjAddAnim_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,int param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint *puVar1;
  int extraout_r4;
  int iVar2;
  
  if ((param_9 != 0) && (param_10 != 0)) {
    iVar2 = param_10;
    if (*(undefined4 **)(param_9 + 0x14) != (undefined4 *)0x0) {
      param_1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    *(undefined4 **)(param_9 + 0x14),param_10,param_11,param_12,
                                    param_13,param_14,param_15,param_16);
      iVar2 = extraout_r4;
    }
    puVar1 = gnt4_HSD_AObjLoadDesc
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(uint **)(param_10 + 4),iVar2,param_11,param_12,param_13,param_14,param_15,
                        param_16);
    *(uint **)(param_9 + 0x14) = puVar1;
    gnt4_HSD_TObjAddAnim_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(undefined4 *)(param_9 + 8),*(undefined4 *)(param_10 + 8),param_11,param_12,param_13
               ,param_14,param_15,param_16);
  }
  return;
}



// ==== 802423a4  gnt4-HSD_MObjReqAnimByFlags-bl ====

void gnt4_HSD_MObjReqAnimByFlags_bl(double param_1,int param_2,uint param_3)

{
  if (param_2 != 0) {
    if ((param_3 & 4) != 0) {
      gnt4_HSD_AObjReqAnim(param_1,*(uint **)(param_2 + 0x14));
    }
    gnt4_HSD_TObjReqAnimAllByFlags_bl(param_1,*(int *)(param_2 + 8),param_3);
  }
  return;
}



// ==== 80242408  gnt4-MObjUpdateFunc-bl ====

void gnt4_MObjUpdateFunc_bl(int param_1,undefined4 param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  
  if (param_1 != 0) {
    switch(param_2) {
    case 1:
      if (*(undefined1 **)(param_1 + 0xc) != (undefined1 *)0x0) {
        fVar1 = *param_3;
        fVar2 = FLOAT_8043d1e8;
        if ((FLOAT_8043d1e8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ec <= fVar1)) {
          fVar2 = FLOAT_8043d1ec;
        }
        **(undefined1 **)(param_1 + 0xc) = (char)(int)(FLOAT_8043d1f0 * fVar2);
      }
      break;
    case 2:
      if (*(int *)(param_1 + 0xc) != 0) {
        fVar1 = *param_3;
        fVar2 = FLOAT_8043d1e8;
        if ((FLOAT_8043d1e8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ec <= fVar1)) {
          fVar2 = FLOAT_8043d1ec;
        }
        *(char *)(*(int *)(param_1 + 0xc) + 1) = (char)(int)(FLOAT_8043d1f0 * fVar2);
      }
      break;
    case 3:
      if (*(int *)(param_1 + 0xc) != 0) {
        fVar1 = *param_3;
        fVar2 = FLOAT_8043d1e8;
        if ((FLOAT_8043d1e8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ec <= fVar1)) {
          fVar2 = FLOAT_8043d1ec;
        }
        *(char *)(*(int *)(param_1 + 0xc) + 2) = (char)(int)(FLOAT_8043d1f0 * fVar2);
      }
      break;
    case 4:
      if (*(int *)(param_1 + 0xc) != 0) {
        fVar1 = *param_3;
        fVar2 = FLOAT_8043d1e8;
        if ((FLOAT_8043d1e8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ec <= fVar1)) {
          fVar2 = FLOAT_8043d1ec;
        }
        *(char *)(*(int *)(param_1 + 0xc) + 4) = (char)(int)(FLOAT_8043d1f0 * fVar2);
      }
      break;
    case 5:
      if (*(int *)(param_1 + 0xc) != 0) {
        fVar1 = *param_3;
        fVar2 = FLOAT_8043d1e8;
        if ((FLOAT_8043d1e8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ec <= fVar1)) {
          fVar2 = FLOAT_8043d1ec;
        }
        *(char *)(*(int *)(param_1 + 0xc) + 5) = (char)(int)(FLOAT_8043d1f0 * fVar2);
      }
      break;
    case 6:
      if (*(int *)(param_1 + 0xc) != 0) {
        fVar1 = *param_3;
        fVar2 = FLOAT_8043d1e8;
        if ((FLOAT_8043d1e8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ec <= fVar1)) {
          fVar2 = FLOAT_8043d1ec;
        }
        *(char *)(*(int *)(param_1 + 0xc) + 6) = (char)(int)(FLOAT_8043d1f0 * fVar2);
      }
      break;
    case 7:
      if (*(int *)(param_1 + 0xc) != 0) {
        fVar1 = *param_3;
        fVar2 = FLOAT_8043d1e8;
        if ((FLOAT_8043d1e8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ec <= fVar1)) {
          fVar2 = FLOAT_8043d1ec;
        }
        *(char *)(*(int *)(param_1 + 0xc) + 8) = (char)(int)(FLOAT_8043d1f0 * fVar2);
      }
      break;
    case 8:
      if (*(int *)(param_1 + 0xc) != 0) {
        fVar1 = *param_3;
        fVar2 = FLOAT_8043d1e8;
        if ((FLOAT_8043d1e8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ec <= fVar1)) {
          fVar2 = FLOAT_8043d1ec;
        }
        *(char *)(*(int *)(param_1 + 0xc) + 9) = (char)(int)(FLOAT_8043d1f0 * fVar2);
      }
      break;
    case 9:
      if (*(int *)(param_1 + 0xc) != 0) {
        fVar1 = *param_3;
        fVar2 = FLOAT_8043d1e8;
        if ((FLOAT_8043d1e8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ec <= fVar1)) {
          fVar2 = FLOAT_8043d1ec;
        }
        *(char *)(*(int *)(param_1 + 0xc) + 10) = (char)(int)(FLOAT_8043d1f0 * fVar2);
      }
      break;
    case 10:
      if (*(int *)(param_1 + 0xc) != 0) {
        fVar1 = FLOAT_8043d1ec - *param_3;
        fVar2 = FLOAT_8043d1e8;
        if ((FLOAT_8043d1e8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ec <= fVar1)) {
          fVar2 = FLOAT_8043d1ec;
        }
        *(float *)(*(int *)(param_1 + 0xc) + 0xc) = fVar2;
      }
      break;
    case 0xb:
      if (*(int *)(param_1 + 0x10) != 0) {
        fVar1 = *param_3;
        fVar2 = FLOAT_8043d1e8;
        if ((FLOAT_8043d1e8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ec <= fVar1)) {
          fVar2 = FLOAT_8043d1ec;
        }
        *(char *)(*(int *)(param_1 + 0x10) + 1) = (char)(int)(FLOAT_8043d1f0 * fVar2);
      }
      break;
    case 0xc:
      if (*(int *)(param_1 + 0x10) != 0) {
        fVar1 = *param_3;
        fVar2 = FLOAT_8043d1e8;
        if ((FLOAT_8043d1e8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ec <= fVar1)) {
          fVar2 = FLOAT_8043d1ec;
        }
        *(char *)(*(int *)(param_1 + 0x10) + 2) = (char)(int)(FLOAT_8043d1f0 * fVar2);
      }
      break;
    case 0xd:
      if (*(int *)(param_1 + 0x10) != 0) {
        fVar1 = *param_3;
        fVar2 = FLOAT_8043d1e8;
        if ((FLOAT_8043d1e8 < fVar1) && (fVar2 = fVar1, FLOAT_8043d1ec <= fVar1)) {
          fVar2 = FLOAT_8043d1ec;
        }
        *(char *)(*(int *)(param_1 + 0x10) + 3) = (char)(int)(FLOAT_8043d1f0 * fVar2);
      }
    }
  }
  return;
}



// ==== 802428a4  gnt4-HSD_MObjAnim-bl ====

void gnt4_HSD_MObjAnim_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  float *pfVar1;
  undefined8 uVar2;
  
  if (param_9 != (int *)0x0) {
    pfVar1 = *(float **)(*param_9 + 0x4c);
    uVar2 = gnt4_HSD_AObjInterpretAnim
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       (uint *)param_9[5],(uint)param_9,pfVar1,param_12,param_13,param_14,param_15,
                       param_16);
    gnt4_HSD_TObjAnimAll_bl
              (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)param_9[2],
               extraout_r4,pfVar1,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 802428ec  gnt4-MObjLoad-bl ====

undefined4
gnt4_MObjLoad_bl(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int iVar2;
  void *__src;
  undefined4 uVar3;
  
  *(undefined4 *)(param_9 + 4) = *(undefined4 *)(param_10 + 4);
  iVar2 = param_10;
  piVar1 = gnt4_HSD_TObjLoadDesc_bl
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int **)(param_10 + 8),param_10,param_11,param_12,param_13,param_14,param_15,
                      param_16);
  *(int **)(param_9 + 8) = piVar1;
  piVar1 = gnt4_HSD_MaterialAlloc_bl
                     (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar1,iVar2,
                      param_11,param_12,param_13,param_14,param_15,param_16);
  *(int **)(param_9 + 0xc) = piVar1;
  uVar3 = 0x14;
  __src = *(void **)(param_10 + 0xc);
  gnt4_memcpy(*(void **)(param_9 + 0xc),__src,0x14);
  *(uint *)(param_9 + 4) = *(uint *)(param_9 + 4) | 0x1000;
  if (*(int *)(param_10 + 0x14) != 0) {
    piVar1 = gnt4_hsdAllocMemPiece_bl
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0xc,__src,
                        uVar3,param_12,param_13,param_14,param_15,param_16);
    *(int **)(param_9 + 0x10) = piVar1;
    gnt4_memcpy(*(void **)(param_9 + 0x10),*(void **)(param_10 + 0x14),0xc);
  }
  *(undefined4 *)(param_9 + 0x14) = 0;
  return 0;
}



// ==== 8024298c  zz_024298c_ ====

void zz_024298c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 *param_9,undefined4 param_10
                ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if ((param_9 != (undefined4 *)0x0) &&
     (iVar1 = zz_025d150_(param_9,&PTR_gnt4_MObjInfoInit_bl_803ac428), iVar1 == 0)) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e38,
                     0x14e,s_hsdIsDescendantOf_info___hsdMObj_803ac4b4,param_12,param_13,param_14,
                     param_15,param_16);
  }
  DAT_80436918 = param_9;
  return;
}



// ==== 802429e4  zz_02429e4_ ====

undefined ** zz_02429e4_(void)

{
  if (DAT_80436918 != (undefined **)0x0) {
    return DAT_80436918;
  }
  return &PTR_gnt4_MObjInfoInit_bl_803ac428;
}



// ==== 802429fc  gnt4-HSD_MObjLoadDesc-bl ====

int * gnt4_HSD_MObjLoadDesc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 extraout_r4;
  char *pcVar3;
  undefined8 uVar4;
  
  if (param_9 != (int *)0x0) {
    if ((*param_9 == 0) ||
       (puVar1 = (undefined4 *)
                 gnt4_hsdSearchClassInfo_bl
                           (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*param_9
                            ,param_10,param_11,param_12,param_13,param_14,param_15,param_16),
       puVar1 == (undefined4 *)0x0)) {
      piVar2 = gnt4_HSD_MObjAlloc_bl
                         (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    else {
      piVar2 = gnt4_hsdNew_bl(puVar1);
      if (piVar2 == (int *)0x0) {
        gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80435e38,0x175,&DAT_80435e40,param_12,param_13,param_14,param_15,
                         param_16);
      }
    }
    pcVar3 = (char *)*piVar2;
    uVar4 = (**(code **)(pcVar3 + 0x40))(piVar2,param_9);
    gnt4_HSD_MObjCompileTev_bl
              (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,extraout_r4,
               pcVar3,param_12,param_13,param_14,param_15,param_16);
    return piVar2;
  }
  return (int *)0x0;
}



// ==== 80242a9c  gnt4-MObjMakeTExp-bl ====

void gnt4_MObjMakeTExp_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               int *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int ****ppppiVar2;
  undefined4 *puVar3;
  int ****ppppiVar4;
  int ***pppiVar5;
  int iVar6;
  int *extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 extraout_r4_05;
  undefined4 extraout_r4_06;
  undefined4 extraout_r4_07;
  undefined4 extraout_r4_08;
  undefined4 extraout_r4_09;
  undefined4 extraout_r4_10;
  undefined4 extraout_r4_11;
  undefined4 extraout_r4_12;
  undefined4 extraout_r4_13;
  int *piVar7;
  int ****ppppiVar8;
  char *pcVar9;
  int ****ppppiVar10;
  undefined4 uVar11;
  int ****ppppiVar12;
  undefined4 uVar13;
  int *piVar14;
  undefined4 uVar15;
  undefined4 *puVar16;
  undefined4 uVar17;
  undefined4 uVar18;
  uint uVar19;
  int *piVar20;
  uint uVar21;
  int *piVar22;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 extraout_f1_01;
  undefined8 extraout_f1_02;
  undefined8 extraout_f1_03;
  undefined8 extraout_f1_04;
  undefined8 extraout_f1_05;
  undefined8 extraout_f1_06;
  undefined8 extraout_f1_07;
  undefined8 uVar23;
  undefined8 uVar24;
  int ***local_30;
  int ***local_2c;
  int ***local_28;
  int ***local_24 [9];
  
  uVar23 = gnt4__savegpr_24_bl();
  iVar6 = (int)((ulonglong)uVar23 >> 0x20);
  piVar20 = (int *)uVar23;
  piVar22 = (int *)0x0;
  piVar14 = piVar20;
  piVar7 = param_11;
  uVar23 = extraout_f1;
  if (param_11 == (int *)0x0) {
    piVar7 = (int *)&DAT_80435e48;
    uVar23 = gnt4___assert_bl(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              &DAT_80435e38,0x18b,&DAT_80435e48,param_12,param_13,param_14,param_15,
                              param_16);
    piVar14 = extraout_r4;
  }
  *param_11 = 0;
  for (piVar1 = piVar20; piVar1 != (int *)0x0; piVar1 = (int *)piVar1[2]) {
    if ((piVar1[0x13] & 0xfU) == 4) {
      piVar22 = piVar1;
    }
  }
  uVar19 = *(uint *)(iVar6 + 4) & 3;
  if (uVar19 == 0) {
    uVar19 = 1;
  }
  uVar21 = *(uint *)(iVar6 + 4) & 0x6000;
  if (uVar21 == 0) {
    uVar21 = uVar19 << 0xd;
  }
  ppppiVar2 = (int ****)
              gnt4_HSD_TExpTev_bl(uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_11,piVar14,(char *)piVar7,param_12,param_13,param_14,
                                  param_15,param_16);
  piVar14 = piVar20;
  local_30 = (int ***)ppppiVar2;
  local_24[0] = (int ***)ppppiVar2;
  if ((*(uint *)(iVar6 + 4) & 4) == 0) {
    if (uVar19 == 2) {
      uVar23 = gnt4_HSD_TExpOrder_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int *)ppppiVar2,(int)piVar22,4,param_12,param_13,param_14,param_15,
                          param_16);
      uVar23 = gnt4_HSD_TExpColorOp_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,0
                          ,0,0,1,param_14,param_15,param_16);
      puVar3 = (undefined4 *)0xfffffffe;
      if (piVar22 != (int *)0x0) {
        puVar3 = (undefined4 *)0xffffffff;
      }
      uVar11 = 7;
      uVar13 = 0;
      uVar15 = 7;
      uVar17 = 0;
      uVar18 = 1;
      uVar23 = gnt4_HSD_TExpColorIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,7
                          ,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,puVar3);
    }
    else if ((uVar19 < 2) && (uVar19 != 0)) {
      puVar3 = (undefined4 *)
               gnt4_HSD_TExpCnst_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar6 + 0xc) + 4,1,(char *)0x0,param_11,param_13,param_14,
                          param_15,param_16);
      uVar23 = gnt4_HSD_TExpColorOp_bl
                         (extraout_f1_03,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          ppppiVar2,0,0,0,1,param_14,param_15,param_16);
      uVar11 = 7;
      uVar13 = 0;
      uVar15 = 7;
      uVar17 = 0;
      uVar18 = 1;
      uVar23 = gnt4_HSD_TExpColorIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,7
                          ,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,puVar3);
    }
    else {
      piVar7 = param_11;
      puVar3 = (undefined4 *)
               gnt4_HSD_TExpCnst_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar6 + 0xc) + 4,1,(char *)0x0,param_11,param_13,param_14,
                          param_15,param_16);
      uVar23 = gnt4_HSD_TExpOrder_bl
                         (extraout_f1_04,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int *)ppppiVar2,(int)piVar22,4,piVar7,param_13,param_14,param_15,param_16
                         );
      uVar23 = gnt4_HSD_TExpColorOp_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,0
                          ,0,0,1,param_14,param_15,param_16);
      puVar16 = (undefined4 *)0xfffffffe;
      if (piVar22 != (int *)0x0) {
        puVar16 = (undefined4 *)0xffffffff;
      }
      uVar11 = 7;
      uVar13 = 0;
      uVar15 = 7;
      uVar17 = 0;
      uVar18 = 1;
      uVar23 = gnt4_HSD_TExpColorIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,1
                          ,puVar16,7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,puVar3);
    }
    if (uVar21 == 0x4000) {
      uVar23 = gnt4_HSD_TExpOrder_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int *)ppppiVar2,(int)piVar22,4,uVar11,uVar13,uVar15,uVar17,uVar18);
      uVar23 = gnt4_HSD_TExpAlphaOp_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,0
                          ,0,0,1,uVar15,uVar17,uVar18);
      ppppiVar8 = (int ****)0x0;
      ppppiVar10 = (int ****)0x7;
      ppppiVar12 = (int ****)0x0;
      piVar7 = (int *)0x7;
      puVar16 = (undefined4 *)0x0;
      uVar13 = 5;
      uVar23 = gnt4_HSD_TExpAlphaIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,7
                          ,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,5,
                          (undefined4 *)0xfffffffe);
      uVar11 = extraout_r4_03;
    }
    else if ((uVar21 < 0x4000) && (uVar21 == 0x2000)) {
      puVar3 = (undefined4 *)
               gnt4_HSD_TExpCnst_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar6 + 0xc) + 0xc,6,(char *)0x3,param_11,uVar13,uVar15,uVar17,
                          uVar18);
      uVar23 = gnt4_HSD_TExpAlphaOp_bl
                         (extraout_f1_05,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          ppppiVar2,0,0,0,1,uVar15,uVar17,uVar18);
      ppppiVar8 = (int ****)0x0;
      ppppiVar10 = (int ****)0x7;
      ppppiVar12 = (int ****)0x0;
      piVar7 = (int *)0x7;
      puVar16 = (undefined4 *)0x0;
      uVar13 = 6;
      uVar23 = gnt4_HSD_TExpAlphaIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,7
                          ,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,6,puVar3);
      uVar11 = extraout_r4_02;
    }
    else {
      piVar7 = param_11;
      puVar16 = (undefined4 *)
                gnt4_HSD_TExpCnst_bl
                          (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(iVar6 + 0xc) + 0xc,6,(char *)0x3,param_11,uVar13,uVar15,uVar17,
                           uVar18);
      uVar23 = gnt4_HSD_TExpOrder_bl
                         (extraout_f1_06,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int *)ppppiVar2,(int)piVar22,4,piVar7,uVar13,uVar15,uVar17,uVar18);
      uVar23 = gnt4_HSD_TExpAlphaOp_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,0
                          ,0,0,1,uVar15,uVar17,uVar18);
      ppppiVar8 = (int ****)0x0;
      ppppiVar10 = (int ****)0x5;
      ppppiVar12 = (int ****)0xfffffffe;
      piVar7 = (int *)0x6;
      uVar13 = 7;
      uVar23 = gnt4_HSD_TExpAlphaIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,7
                          ,(undefined4 *)0x0,5,(undefined4 *)0xfffffffe,6,puVar16,7,
                          (undefined4 *)0x0);
      uVar11 = extraout_r4_04;
    }
  }
  else {
    if (uVar19 == 2) {
      uVar23 = gnt4_HSD_TExpColorOp_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,0
                          ,0,0,1,param_14,param_15,param_16);
      uVar11 = 0;
      uVar13 = 7;
      uVar15 = 0;
      uVar17 = 8;
      uVar23 = gnt4_HSD_TExpColorIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,7
                          ,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,8,
                          (undefined4 *)0x0);
    }
    else {
      puVar3 = (undefined4 *)
               gnt4_HSD_TExpCnst_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar6 + 0xc) + 4,1,(char *)0x0,param_11,param_13,param_14,
                          param_15,param_16);
      uVar23 = gnt4_HSD_TExpColorOp_bl
                         (extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          ppppiVar2,0,0,0,1,param_14,param_15,param_16);
      uVar11 = 0;
      uVar13 = 7;
      uVar15 = 0;
      uVar17 = 1;
      uVar23 = gnt4_HSD_TExpColorIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,7
                          ,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,puVar3);
    }
    if (uVar21 == 0x4000) {
      puVar3 = (undefined4 *)
               gnt4_HSD_TExpCnst_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          &DAT_80435e45,6,(char *)0x0,param_11,uVar11,uVar13,uVar15,uVar17);
      uVar23 = gnt4_HSD_TExpAlphaOp_bl
                         (extraout_f1_01,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          ppppiVar2,0,0,0,1,uVar13,uVar15,uVar17);
      ppppiVar8 = (int ****)0x0;
      ppppiVar10 = (int ****)0x7;
      ppppiVar12 = (int ****)0x0;
      piVar7 = (int *)0x7;
      puVar16 = (undefined4 *)0x0;
      uVar13 = 6;
      uVar23 = gnt4_HSD_TExpAlphaIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,7
                          ,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,6,puVar3);
      uVar11 = extraout_r4_00;
    }
    else {
      puVar3 = (undefined4 *)
               gnt4_HSD_TExpCnst_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar6 + 0xc) + 0xc,6,(char *)0x3,param_11,uVar11,uVar13,uVar15,
                          uVar17);
      uVar23 = gnt4_HSD_TExpAlphaOp_bl
                         (extraout_f1_02,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          ppppiVar2,0,0,0,1,uVar13,uVar15,uVar17);
      ppppiVar8 = (int ****)0x0;
      ppppiVar10 = (int ****)0x7;
      ppppiVar12 = (int ****)0x0;
      piVar7 = (int *)0x7;
      puVar16 = (undefined4 *)0x0;
      uVar13 = 6;
      uVar23 = gnt4_HSD_TExpAlphaIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar2,7
                          ,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,6,puVar3);
      uVar11 = extraout_r4_01;
    }
  }
  for (; piVar14 != (int *)0x0; piVar14 = (int *)piVar14[2]) {
    if (((piVar14[0x13] & 0x50U) != 0) && (piVar14[3] != 0xff)) {
      ppppiVar10 = local_24;
      ppppiVar12 = &local_30;
      ppppiVar8 = (int ****)0x0;
      piVar7 = param_11;
      uVar23 = (**(code **)(*piVar14 + 0x44))(piVar14,0x50);
      uVar11 = extraout_r4_05;
    }
  }
  ppppiVar2 = (int ****)0x50;
  if ((*(uint *)(iVar6 + 4) & 4) != 0) {
    if ((uVar21 & 0x4000) != 0) {
      ppppiVar4 = (int ****)
                  gnt4_HSD_TExpTev_bl(uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,param_11,uVar11,(char *)ppppiVar8,ppppiVar10,ppppiVar12,
                                      piVar7,puVar16,uVar13);
      uVar23 = gnt4_HSD_TExpOrder_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int *)ppppiVar4,0,5,ppppiVar10,ppppiVar12,piVar7,puVar16,uVar13);
      uVar23 = gnt4_HSD_TExpColorOp_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,0
                          ,0,0,1,piVar7,puVar16,uVar13);
      uVar11 = 7;
      uVar13 = 0;
      uVar15 = 1;
      uVar23 = gnt4_HSD_TExpColorIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,7
                          ,(undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,local_24[0]);
      uVar23 = gnt4_HSD_TExpAlphaOp_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,0
                          ,0,0,1,uVar11,uVar13,uVar15);
      ppppiVar10 = (int ****)0x7;
      ppppiVar12 = (int ****)0x0;
      piVar7 = (int *)0x5;
      puVar16 = (undefined4 *)0xfffffffe;
      uVar13 = 7;
      uVar23 = gnt4_HSD_TExpAlphaIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,5
                          ,local_30,7,(undefined4 *)0x0,5,(undefined4 *)0xfffffffe,7,
                          (undefined4 *)0x0);
      uVar11 = extraout_r4_06;
      ppppiVar8 = (int ****)local_30;
      local_30 = (int ***)ppppiVar4;
      local_24[0] = (int ***)ppppiVar4;
    }
    ppppiVar4 = (int ****)
                gnt4_HSD_TExpTev_bl(uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_11,uVar11,(char *)ppppiVar8,ppppiVar10,ppppiVar12,piVar7,
                                    puVar16,uVar13);
    if (piVar22 == (int *)0x0) {
      uVar23 = gnt4_HSD_TExpOrder_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int *)ppppiVar4,0,4,ppppiVar10,ppppiVar12,piVar7,puVar16,uVar13);
      uVar23 = gnt4_HSD_TExpColorOp_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,0
                          ,0,0,1,piVar7,puVar16,uVar13);
      uVar11 = 1;
      uVar13 = 0xfffffffe;
      uVar15 = 7;
      uVar23 = gnt4_HSD_TExpColorIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,7
                          ,(undefined4 *)0x0,1,local_24[0],1,(undefined4 *)0xfffffffe,7,
                          (undefined4 *)0x0);
    }
    else {
      uVar23 = gnt4_HSD_TExpOrder_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          (int *)ppppiVar4,(int)piVar22,4,ppppiVar10,ppppiVar12,piVar7,puVar16,
                          uVar13);
      uVar23 = gnt4_HSD_TExpColorOp_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,0
                          ,0,0,1,piVar7,puVar16,uVar13);
      uVar11 = 1;
      uVar13 = 0xffffffff;
      uVar15 = 7;
      uVar23 = gnt4_HSD_TExpColorIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,7
                          ,(undefined4 *)0x0,1,local_24[0],1,(undefined4 *)0xffffffff,7,
                          (undefined4 *)0x0);
    }
    local_24[0] = (int ***)ppppiVar4;
    if ((uVar21 & 0x4000) == 0) {
      uVar23 = gnt4_HSD_TExpAlphaOp_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,0
                          ,0,0,1,uVar11,uVar13,uVar15);
      ppppiVar10 = (int ****)0x7;
      ppppiVar12 = (int ****)0x0;
      piVar7 = (int *)0x5;
      puVar16 = (undefined4 *)0xfffffffe;
      uVar13 = 7;
      uVar23 = gnt4_HSD_TExpAlphaIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,5
                          ,local_30,7,(undefined4 *)0x0,5,(undefined4 *)0xfffffffe,7,
                          (undefined4 *)0x0);
      uVar11 = extraout_r4_08;
      ppppiVar8 = (int ****)local_30;
      local_30 = (int ***)ppppiVar4;
    }
    else {
      uVar23 = gnt4_HSD_TExpAlphaOp_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,0
                          ,0,0,1,uVar11,uVar13,uVar15);
      ppppiVar8 = (int ****)0x0;
      ppppiVar10 = (int ****)0x5;
      piVar7 = (int *)0x5;
      puVar16 = (undefined4 *)0xfffffffe;
      uVar13 = 7;
      uVar23 = gnt4_HSD_TExpAlphaIn_bl
                         (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,7
                          ,(undefined4 *)0x0,5,local_30,5,(undefined4 *)0xfffffffe,7,
                          (undefined4 *)0x0);
      uVar11 = extraout_r4_07;
      ppppiVar12 = (int ****)local_30;
      local_30 = (int ***)ppppiVar4;
    }
  }
  if ((*(uint *)(iVar6 + 4) & 8) != 0) {
    pcVar9 = (char *)0x0;
    piVar14 = param_11;
    uVar24 = gnt4_HSD_TExpCnst_bl
                       (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar6 + 0xc) + 8,1,(char *)0x0,param_11,ppppiVar12,piVar7,puVar16,
                        uVar13);
    uVar23 = extraout_f1_07;
    pppiVar5 = (int ***)gnt4_HSD_TExpTev_bl(extraout_f1_07,param_2,param_3,param_4,param_5,param_6,
                                            param_7,param_8,param_11,(int)uVar24,pcVar9,piVar14,
                                            ppppiVar12,piVar7,puVar16,uVar13);
    uVar23 = gnt4_HSD_TExpColorOp_bl
                       (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,pppiVar5,0,0,
                        0,1,piVar7,puVar16,uVar13);
    pcVar9 = (char *)0x0;
    ppppiVar8 = (int ****)0x7;
    ppppiVar12 = (int ****)0x0;
    piVar14 = (int *)0x7;
    uVar13 = 0;
    uVar15 = 1;
    uVar23 = gnt4_HSD_TExpColorIn_bl
                       (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,pppiVar5,7,
                        (undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,
                        (undefined4 *)((ulonglong)uVar24 >> 0x20));
    uVar11 = extraout_r4_09;
    local_28 = pppiVar5;
    for (piVar7 = piVar20; piVar7 != (int *)0x0; piVar7 = (int *)piVar7[2]) {
      if (((piVar7[0x13] & 0x20U) != 0) && (piVar7[3] != 0xff)) {
        pcVar9 = (char *)0x50;
        ppppiVar8 = &local_28;
        ppppiVar12 = &local_30;
        piVar14 = param_11;
        uVar23 = (**(code **)(*piVar7 + 0x44))(piVar7,0x20);
        uVar11 = extraout_r4_10;
      }
    }
    ppppiVar2 = (int ****)0x70;
    ppppiVar10 = (int ****)
                 gnt4_HSD_TExpTev_bl(uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                     param_11,uVar11,pcVar9,ppppiVar8,ppppiVar12,piVar14,uVar13,
                                     uVar15);
    uVar23 = gnt4_HSD_TExpOrder_bl
                       (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int *)ppppiVar10,0,5,ppppiVar8,ppppiVar12,piVar14,uVar13,uVar15);
    uVar23 = gnt4_HSD_TExpColorOp_bl
                       (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar10,0,
                        0,0,1,piVar14,uVar13,uVar15);
    pcVar9 = (char *)0x0;
    uVar11 = 1;
    uVar13 = 1;
    uVar15 = 0xfffffffe;
    uVar17 = 7;
    uVar23 = gnt4_HSD_TExpColorIn_bl
                       (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar10,7,
                        (undefined4 *)0x0,1,local_28,1,(undefined4 *)0xfffffffe,7,(undefined4 *)0x0)
    ;
    pppiVar5 = local_28;
    local_28 = (int ***)ppppiVar10;
    ppppiVar4 = (int ****)
                gnt4_HSD_TExpTev_bl(uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    param_11,extraout_r4_11,pcVar9,uVar11,pppiVar5,uVar13,uVar15,
                                    uVar17);
    uVar23 = gnt4_HSD_TExpColorOp_bl
                       (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,0,0
                        ,0,1,uVar13,uVar15,uVar17);
    ppppiVar10 = (int ****)0x7;
    ppppiVar12 = (int ****)0x0;
    piVar7 = (int *)0x7;
    puVar16 = (undefined4 *)0x0;
    uVar13 = 1;
    ppppiVar8 = (int ****)local_28;
    uVar23 = gnt4_HSD_TExpColorIn_bl
                       (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,ppppiVar4,1,
                        local_28,7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,local_24[0]);
    uVar11 = extraout_r4_12;
    local_24[0] = (int ***)ppppiVar4;
  }
  local_2c = local_24[0];
  for (; piVar20 != (int *)0x0; piVar20 = (int *)piVar20[2]) {
    if (((piVar20[0x13] & 0x80U) != 0) && (piVar20[3] != 0xff)) {
      ppppiVar10 = &local_2c;
      ppppiVar12 = &local_30;
      ppppiVar8 = ppppiVar2;
      piVar7 = param_11;
      uVar23 = (**(code **)(*piVar20 + 0x44))(piVar20,0x80);
      uVar11 = extraout_r4_13;
    }
  }
  if (((local_2c != local_30) || (iVar6 = gnt4_HSD_TExpGetType_bl(local_2c), iVar6 != 1)) ||
     (iVar6 = gnt4_HSD_TExpGetType_bl(local_30), iVar6 != 1)) {
    piVar14 = gnt4_HSD_TExpTev_bl(uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  param_11,uVar11,(char *)ppppiVar8,ppppiVar10,ppppiVar12,piVar7,
                                  puVar16,uVar13);
    uVar23 = gnt4_HSD_TExpColorOp_bl
                       (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar14,0,0,0
                        ,1,piVar7,puVar16,uVar13);
    uVar11 = 7;
    uVar13 = 0;
    uVar15 = 1;
    uVar23 = gnt4_HSD_TExpColorIn_bl
                       (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar14,7,
                        (undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,1,local_2c);
    uVar23 = gnt4_HSD_TExpAlphaOp_bl
                       (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar14,0,0,0
                        ,1,uVar11,uVar13,uVar15);
    gnt4_HSD_TExpAlphaIn_bl
              (uVar23,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar14,7,
               (undefined4 *)0x0,7,(undefined4 *)0x0,7,(undefined4 *)0x0,5,local_30);
  }
  gnt4__restgpr_24_bl();
  return;
}



// ==== 80243468  gnt4-HSD_MObjCompileTev-bl ====

void gnt4_HSD_MObjCompileTev_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
               char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  int iVar3;
  int *piVar4;
  undefined8 extraout_f1;
  int local_18;
  
  puVar1 = &stack0xffffffe0;
  piVar4 = (int *)0x0;
  if (param_9 != (int *)0x0) {
    if ((undefined4 *)param_9[6] != (undefined4 *)0x0) {
      param_1 = gnt4_HSD_TExpFreeTevDesc_bl
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           (undefined4 *)param_9[6],param_10,param_11,param_12,param_13,param_14,
                           param_15,param_16);
      param_9[6] = 0;
      param_10 = extraout_r4;
    }
    if ((int *)param_9[7] != (int *)0x0) {
      param_10 = 7;
      param_11 = (char *)0x1;
      gnt4_HSD_TExpFreeList_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)param_9[7],7
                 ,(undefined *)0x1,param_12,param_13,param_14,param_15,param_16);
      param_9[7] = 0;
    }
    local_18 = param_9[2];
    if (((param_9[1] & 0x4000000U) != 0) && (DAT_80436924 != 0)) {
      do {
        piVar4 = (int *)(puVar1 + 8);
        puVar1 = (undefined1 *)*piVar4;
      } while (puVar1 != (undefined1 *)0x0);
      *piVar4 = DAT_80436924;
    }
    if ((((param_9[1] & 0x1000U) != 0) && (DAT_80436920 != 0)) &&
       (*(int *)(DAT_80436920 + 0x58) != 0)) {
      *(int *)(DAT_80436920 + 8) = local_18;
      local_18 = DAT_80436920;
    }
    gnt4_HSD_TObjAssignResources_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_18,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
    iVar3 = *param_9;
    uVar2 = (**(code **)(iVar3 + 0x44))(param_9,local_18,param_9 + 7);
    gnt4_HSD_TExpCompile_bl
              (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar2,param_9 + 6
               ,param_9 + 7,iVar3,param_13,param_14,param_15,param_16);
    if (piVar4 != (int *)0x0) {
      *piVar4 = 0;
    }
  }
  return;
}



// ==== 80243588  gnt4-MObjSetupTev-bl ====

void gnt4_MObjSetupTev_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,int param_10,char *param_11,
               undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
               undefined4 param_16)

{
  char *pcVar1;
  undefined8 uVar2;
  
  pcVar1 = param_11;
  if (*(int *)(param_9 + 0x18) == 0) {
    pcVar1 = s_mobj_>tevdesc_803ac4d8;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80435e38,0x31e,s_mobj_>tevdesc_803ac4d8,param_12,param_13,
                               param_14,param_15,param_16);
  }
  uVar2 = gnt4_HSD_TExpSetupTev_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     *(undefined4 **)(param_9 + 0x18),*(undefined4 *)(param_9 + 0x1c),pcVar1,
                     param_12,param_13,param_14,param_15,param_16);
  gnt4_HSD_TObjSetupVolatileTev_bl
            (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_10,param_11,pcVar1,
             param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80243600  gnt4-HSD_MObjSetup-bl ====

void gnt4_HSD_MObjSetup_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int *param_9)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  uint in_r7;
  uint in_r8;
  uint in_r9;
  uint in_r10;
  int *piVar5;
  uint uVar6;
  undefined8 uVar7;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c [4];
  
  gnt4_HSD_StateInitTev();
  uVar6 = param_9[1];
  local_28 = *(undefined4 *)(param_9[3] + 8);
  pcVar2 = (char *)&local_28;
  local_24 = *(undefined4 *)(param_9[3] + 4);
  local_20 = *(undefined4 *)param_9[3];
  uVar3 = param_9[3];
  uVar7 = gnt4_HSD_SetMaterialColor_bl
                    ((double)*(float *)(uVar3 + 0xc),&local_20,&local_24,(undefined4 *)pcVar2);
  uVar1 = extraout_r4;
  if ((uVar6 & 8) != 0) {
    uVar7 = gnt4_HSD_SetMaterialShininess_bl((double)*(float *)(param_9[3] + 0x10));
    uVar1 = extraout_r4_00;
  }
  piVar5 = (int *)0x0;
  local_1c[0] = param_9[2];
  if ((uVar6 & 0x4000000) != 0) {
    if (DAT_80436924 != 0) {
      piVar5 = local_1c;
      while( true ) {
        if (*piVar5 == 0) break;
        piVar5 = (int *)(*piVar5 + 8);
      }
      *piVar5 = DAT_80436924;
    }
  }
  if ((((uVar6 & 0x1000) != 0) && (DAT_80436920 != 0)) && (*(int *)(DAT_80436920 + 0x58) != 0)) {
    *(int *)(DAT_80436920 + 8) = local_1c[0];
    local_1c[0] = DAT_80436920;
  }
  uVar7 = gnt4_HSD_TObjSetup_bl
                    (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_1c[0],uVar1
                     ,pcVar2,uVar3,in_r7,in_r8,in_r9,in_r10);
  gnt4_HSD_TObjSetupTextureCoordGen_bl
            (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,local_1c[0]);
  iVar4 = *param_9;
  uVar3 = uVar6;
  uVar7 = (**(code **)(iVar4 + 0x48))(param_9,local_1c[0]);
  gnt4_HSD_SetupRenderModeWithCustomPE_bl
            (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar6,(byte *)param_9[4],
             uVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  if (piVar5 != (int *)0x0) {
    *piVar5 = 0;
  }
  return;
}



// ==== 80243744  gnt4-HSD_MObjUnset-bl ====

void gnt4_HSD_MObjUnset_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               char *param_11,uint param_12,uint param_13,uint param_14,uint param_15,uint param_16)

{
  gnt4_HSD_TObjSetup_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,param_10,param_11,
             param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80243768  zz_0243768_ ====

void zz_0243768_(int param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  if (param_1 == 0) {
    return;
  }
  if (*(undefined1 **)(param_1 + 0xc) == (undefined1 *)0x0) {
    return;
  }
  **(undefined1 **)(param_1 + 0xc) = param_2;
  *(undefined1 *)(*(int *)(param_1 + 0xc) + 1) = param_3;
  *(undefined1 *)(*(int *)(param_1 + 0xc) + 2) = param_4;
  return;
}



// ==== 80243798  zz_0243798_ ====

void zz_0243798_(int param_1,undefined1 param_2,undefined1 param_3,undefined1 param_4)

{
  if (param_1 == 0) {
    return;
  }
  if (*(int *)(param_1 + 0xc) == 0) {
    return;
  }
  *(undefined1 *)(*(int *)(param_1 + 0xc) + 4) = param_2;
  *(undefined1 *)(*(int *)(param_1 + 0xc) + 5) = param_3;
  *(undefined1 *)(*(int *)(param_1 + 0xc) + 6) = param_4;
  return;
}



// ==== 802437c8  zz_02437c8_ ====

void zz_02437c8_(double param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  if (*(int *)(param_2 + 0xc) == 0) {
    return;
  }
  *(float *)(*(int *)(param_2 + 0xc) + 0xc) = (float)param_1;
  return;
}



// ==== 802437e8  gnt4-HSD_MObjGetTObj-bl ====

undefined4 gnt4_HSD_MObjGetTObj_bl(int param_1)

{
  if (param_1 == 0) {
    return 0;
  }
  return *(undefined4 *)(param_1 + 8);
}



// ==== 80243800  gnt4-HSD_MObjRemove-bl ====

void gnt4_HSD_MObjRemove_bl(int *param_1)

{
  if (param_1 != (int *)0x0) {
    (**(code **)(*param_1 + 0x30))();
    (**(code **)(*param_1 + 0x34))(param_1);
  }
  return;
}



// ==== 80243850  gnt4-HSD_MObjAlloc-bl ====

int * gnt4_HSD_MObjAlloc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int *piVar1;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined **ppuVar2;
  
  ppuVar2 = DAT_80436918;
  if (DAT_80436918 == (undefined **)0x0) {
    ppuVar2 = &PTR_gnt4_MObjInfoInit_bl_803ac428;
  }
  piVar1 = gnt4_hsdNew_bl(ppuVar2);
  if (piVar1 == (int *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e38,
                     0x44a,&DAT_80435e40,in_r6,in_r7,in_r8,in_r9,in_r10);
  }
  return piVar1;
}



// ==== 802438ac  gnt4-HSD_MaterialAlloc-bl ====

int * gnt4_HSD_MaterialAlloc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int *__s;
  
  __s = gnt4_hsdAllocMemPiece_bl
                  (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x14,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
  if (__s == (int *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e38,
                     0x466,&DAT_80435e50,param_12,param_13,param_14,param_15,param_16);
  }
  gnt4_memset(__s,0,0x14);
  __s[3] = (int)FLOAT_8043d1ec;
  return __s;
}



// ==== 8024390c  gnt4-MObjRelease-bl ====

void gnt4_MObjRelease_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                        double param_5,double param_6,double param_7,double param_8,int param_9,
                        undefined4 param_10,undefined4 param_11,undefined4 param_12,
                        undefined4 param_13,undefined4 param_14,undefined4 param_15,
                        undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  uVar1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(undefined4 **)(param_9 + 0x14),param_10,param_11,param_12,param_13,
                              param_14,param_15,param_16);
  gnt4_hsdFreeMemPiece_bl
            (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
             *(undefined4 **)(param_9 + 0xc),0x14,param_11,param_12,param_13,param_14,param_15,
             param_16);
  uVar1 = gnt4_HSD_TObjRemoveAll_bl(*(int **)(param_9 + 8));
  if (*(undefined4 **)(param_9 + 0x18) != (undefined4 *)0x0) {
    uVar1 = gnt4_HSD_TExpFreeTevDesc_bl
                      (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(undefined4 **)(param_9 + 0x18),extraout_r4,param_11,param_12,param_13,
                       param_14,param_15,param_16);
  }
  if (*(int **)(param_9 + 0x1c) != (int *)0x0) {
    param_11 = 1;
    gnt4_HSD_TExpFreeList_bl
              (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(int **)(param_9 + 0x1c),7,(undefined *)0x1,param_12,param_13,param_14,param_15,
               param_16);
  }
  if (*(undefined4 **)(param_9 + 0x10) != (undefined4 *)0x0) {
    gnt4_hsdFreeMemPiece_bl
              (uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(undefined4 **)(param_9 + 0x10),0xc,param_11,param_12,param_13,param_14,param_15,
               param_16);
  }
  (**(code **)(DAT_803ac43c + 0x30))(param_9);
  return;
}



// ==== 802439a8  gnt4-MObjAmnesia-bl ====

void gnt4_MObjAmnesia_bl(undefined **param_1)

{
  if (param_1 == DAT_80436918) {
    DAT_80436918 = (undefined **)0x0;
  }
  if (param_1 == &PTR_gnt4_MObjInfoInit_bl_803ac428) {
    DAT_80436920 = 0;
    DAT_80436924 = 0;
  }
  (**(code **)(DAT_803ac43c + 0x38))();
  return;
}



// ==== 80243a0c  gnt4-MObjInfoInit-bl ====

void gnt4_MObjInfoInit_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_hsdInitClassInfo_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc53bd8,
             &PTR_gnt4__hsdClassInfoInit_bl_803ad6b0,s_sysdolphin_base_library_803ac570,
             s_hsd_mobj_803ac588,0x54,0x20,in_r9,in_r10);
  DAT_803ac458 = gnt4_MObjRelease_bl;
  DAT_803ac460 = gnt4_MObjAmnesia_bl;
  DAT_803ac464 = gnt4_HSD_MObjSetup_bl;
  DAT_803ac478 = gnt4_HSD_MObjUnset_bl;
  DAT_803ac468 = gnt4_MObjLoad_bl;
  DAT_803ac46c = gnt4_MObjMakeTExp_bl;
  DAT_803ac470 = gnt4_MObjSetupTev_bl;
  DAT_803ac474 = gnt4_MObjUpdateFunc_bl;
  return;
}



// ==== 80243abc  gnt4-HSD_AObjInitAllocData ====

void gnt4_HSD_AObjInitAllocData
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_HSD_ObjAllocInit_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_803f8d90,0x1c,4,
             in_r6,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 80243aec  zz_0243aec_ ====

void zz_0243aec_(uint *param_1,uint param_2)

{
  if (param_1 == (uint *)0x0) {
    return;
  }
  *param_1 = *param_1 | param_2 & 0x30000000;
  return;
}



// ==== 80243b08  zz_0243b08_ ====

void zz_0243b08_(uint *param_1,uint param_2)

{
  if (param_1 == (uint *)0x0) {
    return;
  }
  *param_1 = *param_1 & ~(param_2 & 0x30000000);
  return;
}



// ==== 80243b24  gnt4-HSD_AObjInitEndCallBack ====

void gnt4_HSD_AObjInitEndCallBack(void)

{
  DAT_80436930 = 0;
  DAT_8043692c = 0;
  return;
}



// ==== 80243b34  gnt4-HSD_AObjInvokeCallBacks ====

void gnt4_HSD_AObjInvokeCallBacks(void)

{
  undefined4 *puVar1;
  
  if ((DAT_80436930 != 0) && (puVar1 = DAT_80436928, DAT_8043692c == 0)) {
    for (; puVar1 != (undefined4 *)0x0; puVar1 = (undefined4 *)*puVar1) {
      (*(code *)puVar1[1])();
    }
  }
  return;
}



// ==== 80243b90  gnt4-HSD_AObjReqAnim ====

void gnt4_HSD_AObjReqAnim(double param_1,uint *param_2)

{
  if (param_2 != (uint *)0x0) {
    param_2[1] = (uint)(float)param_1;
    *param_2 = *param_2 & 0xbfffffff | 0x8000000;
    gnt4_HSD_FObjReqAnimAll(param_1,(undefined4 *)param_2[5]);
  }
  return;
}



// ==== 80243bd0  gnt4-HSD_AObjInterpretAnim ====

void gnt4_HSD_AObjInterpretAnim
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,uint *param_9,uint param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  double dVar2;
  
  if (param_9 == (uint *)0x0) {
    return;
  }
  uVar1 = *param_9;
  if ((uVar1 & 0x40000000) != 0) {
    return;
  }
  if ((uVar1 & 0x8000000) == 0) {
    dVar2 = (double)(float)param_9[4];
    param_9[1] = (uint)(float)((double)(float)param_9[1] + dVar2);
  }
  else {
    dVar2 = (double)FLOAT_8043d1f8;
    *param_9 = uVar1 & 0xf7ffffff;
  }
  if ((*param_9 & 0x20000000) != 0) {
    param_2 = (double)(float)param_9[3];
    if (param_2 <= (double)(float)param_9[1]) {
      if (param_2 <= (double)(float)param_9[2]) {
        param_9[1] = param_9[3];
      }
      else {
        gnt4_HSD_FObjStopAnimAll
                  (dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                   (undefined4 *)param_9[5],param_10,param_11,param_12,param_13,param_14,param_15,
                   param_16);
        param_2 = (double)((float)param_9[3] - (float)param_9[2]);
        dVar2 = (double)gnt4_fmod_bl((double)((float)param_9[1] - (float)param_9[2]),param_2);
        param_9[1] = (uint)(float)((double)(float)param_9[2] + dVar2);
        gnt4_HSD_FObjReqAnimAll((double)(float)param_9[1],(undefined4 *)param_9[5]);
      }
      dVar2 = (double)FLOAT_8043d1f8;
      *param_9 = *param_9 | 0x4000000;
      goto LAB_80243cc8;
    }
  }
  *param_9 = *param_9 & 0xfbffffff;
LAB_80243cc8:
  if ((*param_9 & 0x10000000) == 0) {
    gnt4_HSD_FObjInterpretAnimAll
              (dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               (undefined4 *)param_9[5],param_10,param_11,param_12,param_13,param_14,param_15,
               param_16);
  }
  else {
    gnt4_HSD_FObjInterpretAnimAll
              (dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               (undefined4 *)param_9[5],param_10,(float *)0x0,param_12,param_13,param_14,param_15,
               param_16);
  }
  if ((((*param_9 & 0x20000000) == 0) && ((float)param_9[3] <= (float)param_9[1])) &&
     (param_9 != (uint *)0x0)) {
    gnt4_HSD_FObjStopAnimAll
              ((double)(float)param_9[4],param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               (undefined4 *)param_9[5],param_10,param_11,param_12,param_13,param_14,param_15,
               param_16);
    *param_9 = *param_9 | 0x40000000;
  }
  if ((*param_9 & 0x40000000) == 0) {
    DAT_8043692c = DAT_8043692c + 1;
  }
  else {
    DAT_80436930 = DAT_80436930 + 1;
  }
  return;
}



// ==== 80243d88  gnt4-HSD_AObjLoadDesc ====

uint * gnt4_HSD_AObjLoadDesc
                 (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,uint *param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint *puVar1;
  uint uVar2;
  int *piVar3;
  undefined4 extraout_r4;
  uint extraout_r4_00;
  char *pcVar4;
  undefined8 uVar5;
  undefined8 extraout_f1;
  
  if (param_9 == (uint *)0x0) {
    puVar1 = (uint *)0x0;
  }
  else {
    puVar1 = gnt4_HSD_AObjAlloc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_9,param_10,param_11,param_12,param_13,param_14,param_15,
                                param_16);
    if (puVar1 != (uint *)0x0) {
      *puVar1 = *puVar1 | *param_9 & 0x30000000;
    }
    gnt4_HSD_AObjSetRewindFrame((double)FLOAT_8043d1f8,(int)puVar1);
    uVar5 = gnt4_HSD_AObjSetEndFrame((double)(float)param_9[1],(int)puVar1);
    uVar2 = gnt4_HSD_FObjLoadDesc
                      (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9[2],
                       extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
    uVar5 = extraout_f1;
    if (puVar1 != (uint *)0x0) {
      if (puVar1[5] != 0) {
        uVar5 = gnt4_HSD_FObjRemoveAll();
      }
      puVar1[5] = uVar2;
    }
    uVar2 = param_9[3];
    if (uVar2 != 0) {
      pcVar4 = (char *)0x0;
      piVar3 = (int *)gnt4_HSD_IDGetDataFromTable_bl((undefined *)0x0,uVar2,(undefined4 *)0x0);
      if (piVar3 == (int *)0x0) {
        piVar3 = gnt4_HSD_JObjLoadJoint
                           (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int *)param_9[3],uVar2,pcVar4,param_12,param_13,param_14,param_15,
                            param_16);
      }
      else {
        *(short *)(piVar3 + 1) = *(short *)(piVar3 + 1) + 1;
        if (*(short *)(piVar3 + 1) == -1) {
          pcVar4 = s_HSD_OBJ_o__>ref_count____HSD_OBJ_803ac5a4;
          uVar5 = gnt4___assert_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   s_object_h_803ac598,0x5d,
                                   s_HSD_OBJ_o__>ref_count____HSD_OBJ_803ac5a4,param_12,param_13,
                                   param_14,param_15,param_16);
          uVar2 = extraout_r4_00;
        }
      }
      if (puVar1 != (uint *)0x0) {
        if ((int *)puVar1[6] != (int *)0x0) {
          gnt4_HSD_JObjUnref(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             (int *)puVar1[6],uVar2,pcVar4,param_12,param_13,param_14,param_15,
                             param_16);
        }
        puVar1[6] = (uint)piVar3;
      }
    }
  }
  return puVar1;
}



// ==== 80243eb0  gnt4-HSD_AObjRemove ====

void gnt4_HSD_AObjRemove(undefined8 param_1,double param_2,double param_3,double param_4,
                        double param_5,double param_6,double param_7,double param_8,
                        undefined4 *param_9,undefined4 param_10,undefined4 param_11,
                        undefined4 param_12,undefined4 param_13,undefined4 param_14,
                        undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  
  if (param_9 != (undefined4 *)0x0) {
    if (param_9[5] != 0) {
      param_1 = gnt4_HSD_FObjRemoveAll();
      param_10 = extraout_r4;
    }
    param_9[5] = 0;
    if (param_9 != (undefined4 *)0x0) {
      if ((int *)param_9[6] != (int *)0x0) {
        gnt4_HSD_JObjUnref(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           (int *)param_9[6],param_10,param_11,param_12,param_13,param_14,param_15,
                           param_16);
      }
      param_9[6] = 0;
    }
    gnt4_HSD_AObjFree(param_9);
  }
  return;
}



// ==== 80243f20  gnt4-HSD_AObjAlloc ====

undefined4 *
gnt4_HSD_AObjAlloc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                  double param_6,double param_7,double param_8,undefined4 param_9,
                  undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
                  undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 *__s;
  
  __s = gnt4_HSD_ObjAlloc(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          &DAT_803f8d90,param_10,param_11,param_12,param_13,param_14,param_15,
                          param_16);
  if (__s == (undefined4 *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e58,
                     0x1e9,&DAT_80435e60,param_12,param_13,param_14,param_15,param_16);
  }
  gnt4_memset(__s,0,0x1c);
  fVar1 = FLOAT_8043d1fc;
  *__s = 0x40000000;
  __s[4] = fVar1;
  return __s;
}



// ==== 80243f8c  gnt4-HSD_AObjFree ====

void gnt4_HSD_AObjFree(undefined4 *param_1)

{
  if (param_1 != (undefined4 *)0x0) {
    gnt4_HSD_ObjFree(-0x7fc07270,param_1);
  }
  return;
}



// ==== 80243fc0  zz_0243fc0_ ====

void zz_0243fc0_(double param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  *(float *)(param_2 + 0x10) = (float)param_1;
  return;
}



// ==== 80243fd0  gnt4-HSD_AObjSetRewindFrame ====

void gnt4_HSD_AObjSetRewindFrame(double param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  *(float *)(param_2 + 8) = (float)param_1;
  return;
}



// ==== 80243fe0  gnt4-HSD_AObjSetEndFrame ====

void gnt4_HSD_AObjSetEndFrame(double param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  *(float *)(param_2 + 0xc) = (float)param_1;
  return;
}



// ==== 80243ff0  zz_0243ff0_ ====

void zz_0243ff0_(void)

{
  DAT_80436928 = 0;
  return;
}



// ==== 80243ffc  gnt4-HSD_LObjGetLightMaskDiffuse-bl ====

undefined4 gnt4_HSD_LObjGetLightMaskDiffuse_bl(void)

{
  return DAT_80436944;
}



// ==== 80244004  gnt4-HSD_LObjGetLightMaskAlpha-bl ====

undefined4 gnt4_HSD_LObjGetLightMaskAlpha_bl(void)

{
  return DAT_80436950;
}



// ==== 8024400c  gnt4-HSD_LObjGetLightMaskSpecular-bl ====

undefined4 gnt4_HSD_LObjGetLightMaskSpecular_bl(void)

{
  return DAT_80436948;
}



// ==== 80244014  gnt4-HSD_LObjGetNbActive-bl ====

undefined4 gnt4_HSD_LObjGetNbActive_bl(void)

{
  return DAT_80436940;
}



// ==== 8024401c  gnt4-HSD_LObjGetActiveByID-bl ====

undefined4
gnt4_HSD_LObjGetActiveByID_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = gnt4_HSD_LightID2Index_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                     param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  if ((iVar1 < 0) || (8 < iVar1)) {
    uVar2 = 0;
  }
  else {
    uVar2 = (&DAT_803f8dc0)[iVar1];
  }
  return uVar2;
}



// ==== 80244064  gnt4-HSD_LObjGetActiveByIndex-bl ====

undefined4 gnt4_HSD_LObjGetActiveByIndex_bl(int param_1)

{
  if ((-1 < param_1) && (param_1 < 8)) {
    return (&DAT_803f8dc0)[param_1];
  }
  return 0;
}



// ==== 80244090  gnt4-LObjUpdateFunc-bl ====

void gnt4_LObjUpdateFunc_bl(int param_1,undefined4 param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  
  if (param_1 != 0) {
    switch(param_2) {
    case 9:
      fVar1 = *param_3;
      fVar2 = FLOAT_8043d208;
      if ((FLOAT_8043d208 < fVar1) && (fVar2 = fVar1, FLOAT_8043d20c <= fVar1)) {
        fVar2 = FLOAT_8043d20c;
      }
      *(char *)(param_1 + 0x10) = (char)(int)(FLOAT_8043d210 * fVar2);
      break;
    case 10:
      fVar1 = *param_3;
      fVar2 = FLOAT_8043d208;
      if ((FLOAT_8043d208 < fVar1) && (fVar2 = fVar1, FLOAT_8043d20c <= fVar1)) {
        fVar2 = FLOAT_8043d20c;
      }
      *(char *)(param_1 + 0x11) = (char)(int)(FLOAT_8043d210 * fVar2);
      break;
    case 0xb:
      fVar1 = *param_3;
      fVar2 = FLOAT_8043d208;
      if ((FLOAT_8043d208 < fVar1) && (fVar2 = fVar1, FLOAT_8043d20c <= fVar1)) {
        fVar2 = FLOAT_8043d20c;
      }
      *(char *)(param_1 + 0x12) = (char)(int)(FLOAT_8043d210 * fVar2);
      break;
    case 0xc:
      if ((double)*param_3 < DOUBLE_8043d200) {
        *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) | 0x20;
      }
      else {
        *(ushort *)(param_1 + 8) = *(ushort *)(param_1 + 8) & 0xffdf;
      }
      break;
    case 0xd:
    case 0x13:
      if ((*(ushort *)(param_1 + 8) & 0x40) == 0) {
        *(float *)(param_1 + 0x20) = *param_3;
      }
      else {
        *(float *)(param_1 + 0x20) = *param_3;
      }
      break;
    case 0xe:
    case 0x14:
      if ((*(ushort *)(param_1 + 8) & 0x40) == 0) {
        *(float *)(param_1 + 0x2c) = *param_3;
      }
      else {
        *(float *)(param_1 + 0x24) = *param_3;
      }
      break;
    case 0xf:
    case 0x15:
      if ((*(ushort *)(param_1 + 8) & 0x40) == 0) {
        *(float *)(param_1 + 0x28) = *param_3;
      }
      else {
        *(float *)(param_1 + 0x28) = *param_3;
      }
      break;
    case 0x10:
      if ((*(ushort *)(param_1 + 8) & 0x40) != 0) {
        *(float *)(param_1 + 0x2c) = *param_3;
      }
      break;
    case 0x11:
      if ((*(ushort *)(param_1 + 8) & 0x40) != 0) {
        *(float *)(param_1 + 0x30) = *param_3;
      }
      break;
    case 0x12:
      if ((*(ushort *)(param_1 + 8) & 0x40) != 0) {
        *(float *)(param_1 + 0x34) = *param_3;
      }
      break;
    case 0x16:
      fVar1 = *param_3;
      fVar2 = FLOAT_8043d208;
      if ((FLOAT_8043d208 < fVar1) && (fVar2 = fVar1, FLOAT_8043d20c <= fVar1)) {
        fVar2 = FLOAT_8043d20c;
      }
      *(char *)(param_1 + 0x13) = (char)(int)(FLOAT_8043d210 * fVar2);
    }
  }
  return;
}



// ==== 802442dc  gnt4-HSD_LObjGetLightVector-bl ====

void gnt4_HSD_LObjGetLightVector_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,float *param_10)

{
  float fVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  float fVar7;
  undefined4 in_r10;
  undefined *local_28;
  undefined4 local_24;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  puVar4 = &DAT_802b520c;
  local_1c = DAT_802b5200;
  local_18 = DAT_802b5204;
  local_14 = DAT_802b5208;
  local_28 = DAT_802b520c;
  local_24 = DAT_802b5210;
  local_20 = DAT_802b5214;
  if (param_9 != 0) {
    puVar3 = DAT_802b520c;
    uVar5 = DAT_802b5208;
    uVar6 = DAT_802b5204;
    fVar7 = DAT_802b5200;
    gnt4_HSD_LObjGetPosition_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,&local_1c,
               DAT_802b520c,&DAT_802b520c,DAT_802b5208,DAT_802b5204,DAT_802b5200,in_r10);
    gnt4_HSD_LObjGetInterest_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,&local_28,
               puVar3,puVar4,uVar5,uVar6,fVar7,in_r10);
    gnt4_PSVECSubtract_bl((float *)&local_28,&local_1c,param_10);
    if (param_10 == (float *)0x0) {
      iVar2 = -1;
    }
    else if (((DOUBLE_8043d218 < ABS((double)*param_10)) ||
             (DOUBLE_8043d218 < ABS((double)param_10[1]))) ||
            (DOUBLE_8043d218 < ABS((double)param_10[2]))) {
      gnt4_PSVECNormalize_bl(param_10,param_10);
      iVar2 = 0;
    }
    else {
      iVar2 = -1;
    }
    fVar1 = FLOAT_8043d20c;
    fVar7 = FLOAT_8043d208;
    if (iVar2 != 0) {
      *param_10 = FLOAT_8043d208;
      param_10[1] = fVar7;
      param_10[2] = fVar1;
    }
  }
  return;
}



// ==== 80244400  gnt4-HSD_LObjSetup-bl ====

/* WARNING: Removing unreachable block (ram,0x80244544) */
/* WARNING: Removing unreachable block (ram,0x80244410) */

void gnt4_HSD_LObjSetup_bl(double param_1,int param_2,char *param_3)

{
  ushort uVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  undefined4 local_28 [4];
  
  uVar1 = *(ushort *)(param_2 + 8);
  if (((uVar1 & 0x20) == 0) && ((uVar1 & 3) != 0)) {
    if ((uVar1 & 0x14) != 0) {
      if ((((*(char *)(param_2 + 0x14) != *param_3) || (*(char *)(param_2 + 0x15) != param_3[1])) ||
          (*(char *)(param_2 + 0x16) != param_3[2])) || (*(char *)(param_2 + 0x17) != param_3[3])) {
        local_28[0] = *(undefined4 *)param_3;
        gnt4_GXInitLightColor_bl(param_2 + 0x50,local_28);
        *(undefined4 *)(param_2 + 0x14) = *(undefined4 *)param_3;
        *(ushort *)(param_2 + 8) = *(ushort *)(param_2 + 8) | 0x80;
      }
      if ((*(ushort *)(param_2 + 8) & 0x80) != 0) {
        gnt4_GXLoadLightObjImm_bl(param_2 + 0x50,*(undefined4 *)(param_2 + 0x4c));
        *(ushort *)(param_2 + 8) = *(ushort *)(param_2 + 8) & 0xff7f;
      }
    }
    if (*(int *)(param_2 + 0x90) != 0) {
      if ((double)*(float *)(param_2 + 0x38) != param_1) {
        dVar2 = (double)FLOAT_8043d220;
        dVar3 = (double)FLOAT_8043d208;
        dVar4 = (double)FLOAT_8043d20c;
        *(float *)(param_2 + 0x38) = (float)param_1;
        gnt4_GXInitLightAttn_bl
                  (dVar3,dVar3,dVar4,(double)(float)(param_1 * dVar2),dVar3,
                   (double)(float)(dVar4 - (double)(float)(param_1 * dVar2)),param_2 + 0x94);
        *(ushort *)(param_2 + 8) = *(ushort *)(param_2 + 8) | 0x100;
      }
      if ((*(ushort *)(param_2 + 8) & 0x100) != 0) {
        gnt4_GXLoadLightObjImm_bl(param_2 + 0x94,*(undefined4 *)(param_2 + 0x90));
        *(ushort *)(param_2 + 8) = *(ushort *)(param_2 + 8) & 0xfeff;
      }
    }
  }
  return;
}



// ==== 80244564  gnt4-HSD_LObjSetupSpecularInit-bl ====

void gnt4_HSD_LObjSetupSpecularInit_bl
               (undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  ushort uVar4;
  int iVar3;
  int *piVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  
  local_30 = *(float *)(param_9 + 0xc);
  local_2c = *(float *)(param_9 + 0x1c);
  dVar8 = (double)local_2c;
  local_28 = *(float *)(param_9 + 0x2c);
  if (((DOUBLE_8043d218 < ABS((double)local_30)) || (dVar8 = ABS(dVar8), DOUBLE_8043d218 < dVar8))
     || (dVar7 = ABS((double)local_28), DOUBLE_8043d218 < dVar7)) {
    dVar7 = (double)gnt4_PSVECNormalize_bl(&local_30,&local_24);
    iVar2 = 0;
  }
  else {
    iVar2 = -1;
  }
  iVar1 = DAT_80436940;
  if (iVar2 != 0) {
    dVar7 = (double)FLOAT_8043d208;
    local_24 = FLOAT_8043d208;
    local_20 = FLOAT_8043d208;
    local_1c = FLOAT_8043d224;
  }
  piVar5 = &DAT_803f8dc0;
  iVar2 = 0;
  do {
    if (iVar1 <= iVar2) {
      return;
    }
    if ((iVar2 < 0) || (7 < iVar2)) {
      iVar6 = 0;
    }
    else {
      iVar6 = *piVar5;
    }
    if (*(int *)(iVar6 + 0x90) != 0) {
      uVar4 = *(ushort *)(iVar6 + 8) & 3;
      if (uVar4 == 1) {
        gnt4_PSVECAdd_bl((float *)(iVar6 + 0x3c),&local_24,&local_3c);
LAB_80244718:
        if (((DOUBLE_8043d218 < ABS((double)local_3c)) || (DOUBLE_8043d218 < ABS((double)local_38)))
           || (DOUBLE_8043d218 < ABS((double)local_34))) {
          gnt4_PSVECNormalize_bl(&local_3c,&local_3c);
          iVar3 = 0;
        }
        else {
          iVar3 = -1;
        }
        if (iVar3 != 0) {
          local_3c = FLOAT_8043d208;
          local_38 = FLOAT_8043d208;
          local_34 = FLOAT_8043d20c;
        }
      }
      else {
        if (((*(ushort *)(iVar6 + 8) & 3) == 0) || (3 < uVar4)) {
          gnt4___assert_bl(dVar7,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e68
                           ,0x27a,&DAT_80435e70,param_12,param_13,param_14,param_15,param_16);
          goto LAB_80244718;
        }
        gnt4_PSVECSubtract_bl(&local_30,(float *)(iVar6 + 0x3c),&local_48);
        if (((DOUBLE_8043d218 < ABS((double)local_48)) || (DOUBLE_8043d218 < ABS((double)local_44)))
           || (DOUBLE_8043d218 < ABS((double)local_40))) {
          gnt4_PSVECNormalize_bl(&local_48,&local_48);
          iVar3 = 0;
        }
        else {
          iVar3 = -1;
        }
        if (iVar3 == 0) {
          gnt4_PSVECAdd_bl(&local_48,&local_24,&local_3c);
          goto LAB_80244718;
        }
        local_3c = FLOAT_8043d208;
        local_38 = FLOAT_8043d208;
        local_34 = FLOAT_8043d20c;
      }
      dVar8 = (double)local_38;
      param_3 = (double)local_34;
      dVar7 = (double)gnt4_GXInitLightDir_bl((double)local_3c,dVar8,param_3,iVar6 + 0x94);
      *(ushort *)(iVar6 + 8) = *(ushort *)(iVar6 + 8) | 0x100;
    }
    piVar5 = piVar5 + 1;
    iVar2 = iVar2 + 1;
  } while( true );
}



// ==== 802447dc  gnt4-HSD_LObjSetupInit-bl ====

/* WARNING: Removing unreachable block (ram,0x80245378) */
/* WARNING: Removing unreachable block (ram,0x80245370) */
/* WARNING: Removing unreachable block (ram,0x80245368) */
/* WARNING: Removing unreachable block (ram,0x802447fc) */
/* WARNING: Removing unreachable block (ram,0x802447f4) */
/* WARNING: Removing unreachable block (ram,0x802447ec) */
/* WARNING: Removing unreachable block (ram,0x802448e4) */

void gnt4_HSD_LObjSetupInit_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,float param_14,
               undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  ushort uVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  undefined4 uVar8;
  undefined4 *puVar9;
  undefined4 *extraout_r4;
  undefined4 *extraout_r4_00;
  undefined4 *extraout_r4_01;
  undefined4 *extraout_r4_02;
  undefined4 *extraout_r4_03;
  undefined4 *extraout_r4_04;
  undefined4 *extraout_r4_05;
  undefined4 *extraout_r4_06;
  undefined4 *extraout_r4_07;
  undefined4 *extraout_r4_08;
  undefined4 *extraout_r4_09;
  undefined4 *extraout_r4_10;
  int iVar10;
  undefined4 *puVar11;
  int iVar12;
  int *piVar13;
  int *piVar14;
  float *pfVar15;
  ushort uVar17;
  int iVar16;
  double dVar18;
  undefined8 extraout_f1;
  undefined8 uVar19;
  double dVar20;
  double dVar21;
  double dVar22;
  double in_f29;
  double dVar23;
  double in_f30;
  double in_f31;
  double in_ps29_1;
  double in_ps30_1;
  double in_ps31_1;
  undefined4 local_e8;
  undefined4 local_e4;
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d8;
  undefined4 local_d4;
  float local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  float local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  float local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  float local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  float local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  float local_94;
  undefined4 local_90;
  undefined4 local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_28;
  float fStack_24;
  float local_18;
  float fStack_14;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  local_18 = (float)in_f30;
  fStack_14 = (float)in_ps30_1;
  local_28 = (float)in_f29;
  fStack_24 = (float)in_ps29_1;
  iVar5 = gnt4__savegpr_24_bl();
  puVar9 = (undefined4 *)0x80400000;
  piVar13 = &DAT_803f8dc0;
  DAT_80436944 = 0;
  pfVar15 = (float *)(iVar5 + 0x54);
  DAT_803f8dc0 = 0;
  iVar5 = 0;
  DAT_803f8dc4 = 0;
  DAT_803f8dc8 = 0;
  DAT_803f8dcc = 0;
  DAT_803f8dd0 = 0;
  DAT_803f8dd4 = 0;
  DAT_803f8dd8 = 0;
  DAT_803f8ddc = 0;
  DAT_803f8de0 = 0;
  DAT_80436948 = 0;
  DAT_8043694c = 0;
  DAT_80436950 = 0;
  DAT_80436940 = 0;
  uVar19 = extraout_f1;
  for (puVar11 = DAT_8043693c; (iVar5 < 8 && (puVar11 != (undefined4 *)0x0));
      puVar11 = (undefined4 *)*puVar11) {
    iVar6 = puVar11[1];
    if ((iVar6 != 0) && (uVar4 = *(ushort *)(iVar6 + 8), (uVar4 & 0x20) == 0)) {
      uVar17 = uVar4 & 3;
      if ((uVar4 & 0x1c) != 0) {
        if ((uVar4 & 3) == 0) {
          iVar5 = 8;
          if (DAT_803f8de0 == 0) goto LAB_802448a8;
        }
        else {
          iVar5 = DAT_80436940;
          DAT_80436940 = DAT_80436940 + 1;
LAB_802448a8:
          puVar9 = &DAT_803f8dc0;
          (&DAT_803f8dc0)[iVar5] = iVar6;
          uVar8 = gnt4_HSD_Index2LightID_bl(iVar5);
          *(undefined4 *)(iVar6 + 0x4c) = uVar8;
        }
        iVar5 = DAT_80436940;
        *(undefined4 *)(iVar6 + 0x90) = 0;
        if (uVar17 == 2) {
          local_d8 = *(undefined4 *)(iVar6 + 0x10);
          uVar19 = gnt4_GXInitLightColor_bl(iVar6 + 0x50,&local_d8);
          *(undefined4 *)(iVar6 + 0x14) = *(undefined4 *)(iVar6 + 0x10);
          gnt4_HSD_LObjGetPosition_bl
                    (uVar19,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,&local_70,
                     (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
          param_11 = &local_70;
          gnt4_PSMTXMultVec_bl(pfVar15,param_11,param_11);
          gnt4_GXInitLightPos_bl((double)local_70,(double)local_6c,(double)local_68,iVar6 + 0x50);
          param_3 = (double)local_68;
          gnt4_GXInitLightPos_bl((double)local_70,(double)local_6c,param_3,iVar6 + 0x94);
          if ((*(ushort *)(iVar6 + 8) & 0x40) == 0) {
            iVar12 = *(int *)(iVar6 + 0x30);
            dVar23 = (double)*(float *)(iVar6 + 0x2c);
            if ((double)*(float *)(iVar6 + 0x2c) < (double)FLOAT_8043d230) {
              dVar23 = (double)FLOAT_8043d230;
            }
            param_2 = (double)*(float *)(iVar6 + 0x28);
            if ((double)*(float *)(iVar6 + 0x28) < (double)FLOAT_8043d230) {
              param_2 = (double)FLOAT_8043d230;
            }
            gnt4_GXInitLightDistAttn_bl(dVar23,param_2,iVar6 + 0x50,iVar12);
            gnt4_GXInitLightSpot_bl((double)FLOAT_8043d208,iVar6 + 0x50,0);
            uVar19 = gnt4_GXInitLightDistAttn_bl(dVar23,param_2,iVar6 + 0x94,iVar12);
            puVar9 = extraout_r4_03;
          }
          else {
            param_2 = (double)FLOAT_8043d208;
            param_4 = (double)*(float *)(iVar6 + 0x2c);
            param_5 = (double)*(float *)(iVar6 + 0x30);
            param_6 = (double)*(float *)(iVar6 + 0x34);
            param_3 = param_2;
            uVar19 = gnt4_GXInitLightAttn_bl
                               ((double)FLOAT_8043d20c,param_2,param_2,param_4,param_5,param_6,
                                iVar6 + 0x50);
            puVar9 = extraout_r4_02;
          }
        }
        else if (uVar17 < 2) {
          if ((uVar4 & 3) == 0) goto LAB_80244f08;
          gnt4_HSD_LObjGetPosition_bl
                    (uVar19,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,&local_64,
                     (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
          param_11 = &local_64;
          param_3 = (double)FLOAT_8043d22c;
          local_64 = (float)((double)local_64 * param_3);
          param_2 = (double)local_64;
          local_60 = (float)((double)local_60 * param_3);
          local_5c = (float)((double)local_5c * param_3);
          uVar19 = gnt4_PSMTXMultVec_bl(pfVar15,param_11,param_11);
          puVar9 = extraout_r4;
          if ((*(ushort *)(iVar6 + 8) & 4) != 0) {
            gnt4_GXInitLightPos_bl((double)local_64,(double)local_60,(double)local_5c,iVar6 + 0x50);
            param_2 = (double)FLOAT_8043d208;
            param_4 = (double)FLOAT_8043d20c;
            param_3 = param_2;
            param_5 = param_2;
            param_6 = param_2;
            uVar19 = gnt4_GXInitLightAttn_bl
                               (param_4,param_2,param_2,param_4,param_2,param_2,iVar6 + 0x50);
            puVar9 = extraout_r4_00;
          }
          if ((*(ushort *)(iVar6 + 8) & 8) != 0) {
            param_2 = (double)local_60;
            param_3 = (double)local_5c;
            uVar19 = gnt4_GXInitLightPos_bl((double)local_64,param_2,param_3,iVar6 + 0x94);
            puVar9 = extraout_r4_01;
          }
        }
        else if (uVar17 < 4) {
          gnt4_HSD_LObjGetPosition_bl
                    (uVar19,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,&local_88,
                     (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
          uVar19 = gnt4_PSMTXMultVec_bl(pfVar15,&local_88,&local_88);
          puVar9 = &DAT_802b520c;
          local_a0 = DAT_802b5200;
          local_9c = DAT_802b5204;
          local_98 = DAT_802b5208;
          local_94 = DAT_802b520c;
          local_90 = DAT_802b5210;
          local_8c = DAT_802b5214;
          param_12 = DAT_802b5208;
          param_13 = DAT_802b5204;
          param_14 = DAT_802b5200;
          if (iVar6 != 0) {
            gnt4_HSD_LObjGetPosition_bl
                      (uVar19,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                       &local_a0,(undefined *)&DAT_802b520c,DAT_802b5208,DAT_802b5204,DAT_802b5200,
                       param_15,param_16);
            gnt4_HSD_LObjGetInterest_bl
                      (uVar19,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                       &local_94,(undefined *)puVar9,param_12,param_13,param_14,param_15,param_16);
            gnt4_PSVECSubtract_bl(&local_94,&local_a0,&local_7c);
            if (((DOUBLE_8043d218 < ABS((double)local_7c)) ||
                (DOUBLE_8043d218 < ABS((double)local_78))) ||
               (DOUBLE_8043d218 < ABS((double)local_74))) {
              gnt4_PSVECNormalize_bl(&local_7c,&local_7c);
              iVar12 = 0;
            }
            else {
              iVar12 = -1;
            }
            if (iVar12 != 0) {
              local_7c = FLOAT_8043d208;
              local_78 = FLOAT_8043d208;
              local_74 = FLOAT_8043d20c;
            }
          }
          param_11 = &local_7c;
          gnt4_PSMTXMultVecSR_bl(pfVar15,param_11,param_11);
          gnt4_PSVECNormalize_bl(&local_7c,&local_7c);
          gnt4_GXInitLightPos_bl((double)local_88,(double)local_84,(double)local_80,iVar6 + 0x50);
          gnt4_GXInitLightPos_bl((double)local_88,(double)local_84,(double)local_80,iVar6 + 0x94);
          param_3 = (double)local_74;
          gnt4_GXInitLightDir_bl((double)local_7c,(double)local_78,param_3,iVar6 + 0x50);
          if ((*(ushort *)(iVar6 + 8) & 0x40) == 0) {
            dVar18 = (double)*(float *)(iVar6 + 0x20);
            uVar8 = *(undefined4 *)(iVar6 + 0x24);
            iVar12 = *(int *)(iVar6 + 0x30);
            dVar23 = (double)*(float *)(iVar6 + 0x2c);
            if ((double)*(float *)(iVar6 + 0x2c) < (double)FLOAT_8043d230) {
              dVar23 = (double)FLOAT_8043d230;
            }
            param_2 = (double)*(float *)(iVar6 + 0x28);
            if ((double)*(float *)(iVar6 + 0x28) < (double)FLOAT_8043d230) {
              param_2 = (double)FLOAT_8043d230;
            }
            gnt4_GXInitLightDistAttn_bl(dVar23,param_2,iVar6 + 0x50,iVar12);
            gnt4_GXInitLightDistAttn_bl(dVar23,param_2,iVar6 + 0x94,iVar12);
            uVar19 = gnt4_GXInitLightSpot_bl(dVar18,iVar6 + 0x50,uVar8);
            puVar9 = extraout_r4_05;
          }
          else {
            param_2 = (double)*(float *)(iVar6 + 0x24);
            param_3 = (double)*(float *)(iVar6 + 0x28);
            param_4 = (double)*(float *)(iVar6 + 0x2c);
            param_5 = (double)*(float *)(iVar6 + 0x30);
            param_6 = (double)*(float *)(iVar6 + 0x34);
            uVar19 = gnt4_GXInitLightAttn_bl
                               ((double)*(float *)(iVar6 + 0x20),param_2,param_3,param_4,param_5,
                                param_6,iVar6 + 0x50);
            puVar9 = extraout_r4_04;
          }
        }
        if ((uVar4 & 0x14) == 0) {
          if ((uVar4 & 8) != 0) {
            uVar7 = *(uint *)(iVar6 + 0x4c);
            *(uint *)(iVar6 + 0x90) = uVar7;
            if (uVar7 != 0) {
              local_e0 = *(undefined4 *)(iVar6 + 0x10);
              gnt4_GXInitLightColor_bl(iVar6 + 0x94,&local_e0);
              param_2 = (double)FLOAT_8043d208;
              *(float *)(iVar6 + 0x38) = FLOAT_8043d228;
              param_3 = (double)FLOAT_8043d20c;
              param_4 = (double)(*(float *)(iVar6 + 0x38) * FLOAT_8043d220);
              param_6 = (double)(float)(param_3 - param_4);
              param_5 = param_2;
              uVar19 = gnt4_GXInitLightAttn_bl
                                 (param_2,param_2,param_3,param_4,param_2,param_6,iVar6 + 0x94);
              uVar4 = *(ushort *)(iVar6 + 8) & 3;
              if (uVar4 == 1) {
                puVar9 = &DAT_802b520c;
                local_b8 = DAT_802b5200;
                local_b4 = DAT_802b5204;
                local_b0 = DAT_802b5208;
                local_ac = DAT_802b520c;
                local_a8 = DAT_802b5210;
                local_a4 = DAT_802b5214;
                param_12 = DAT_802b5208;
                param_13 = DAT_802b5204;
                param_14 = DAT_802b5200;
                if (iVar6 != 0) {
                  gnt4_HSD_LObjGetPosition_bl
                            (uVar19,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                             &local_b8,(undefined *)&DAT_802b520c,DAT_802b5208,DAT_802b5204,
                             DAT_802b5200,param_15,param_16);
                  gnt4_HSD_LObjGetInterest_bl
                            (uVar19,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                             &local_ac,(undefined *)puVar9,param_12,param_13,param_14,param_15,
                             param_16);
                  gnt4_PSVECSubtract_bl(&local_ac,&local_b8,(float *)(iVar6 + 0x3c));
                  if ((iVar6 == -0x3c) || (iVar6 == -0x3c)) {
                    iVar12 = -1;
                  }
                  else if (((DOUBLE_8043d218 < ABS((double)*(float *)(iVar6 + 0x3c))) ||
                           (DOUBLE_8043d218 < ABS((double)*(float *)(iVar6 + 0x40)))) ||
                          (DOUBLE_8043d218 < ABS((double)*(float *)(iVar6 + 0x44)))) {
                    gnt4_PSVECNormalize_bl((float *)(iVar6 + 0x3c),(float *)(iVar6 + 0x3c));
                    iVar12 = 0;
                  }
                  else {
                    iVar12 = -1;
                  }
                  fVar3 = FLOAT_8043d20c;
                  fVar2 = FLOAT_8043d208;
                  if (iVar12 != 0) {
                    *(float *)(iVar6 + 0x3c) = FLOAT_8043d208;
                    *(float *)(iVar6 + 0x40) = fVar2;
                    *(float *)(iVar6 + 0x44) = fVar3;
                  }
                }
                param_11 = (float *)(iVar6 + 0x3c);
                gnt4_PSMTXMultVecSR_bl(pfVar15,param_11,param_11);
                uVar19 = gnt4_PSVECNormalize_bl((float *)(iVar6 + 0x3c),(float *)(iVar6 + 0x3c));
                puVar9 = extraout_r4_09;
              }
              else if (((*(ushort *)(iVar6 + 8) & 3) == 0) || (3 < uVar4)) {
                param_11 = (float *)&DAT_80435e70;
                uVar19 = gnt4___assert_bl(uVar19,param_2,param_3,param_4,param_5,param_6,param_7,
                                          param_8,&DAT_80435e68,0x2c0,&DAT_80435e70,param_12,
                                          param_13,param_14,param_15,param_16);
                puVar9 = extraout_r4_10;
              }
              else {
                gnt4_HSD_LObjGetPosition_bl
                          (uVar19,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                           (undefined4 *)(iVar6 + 0x3c),(undefined *)param_11,param_12,param_13,
                           param_14,param_15,param_16);
                param_11 = (float *)(iVar6 + 0x3c);
                uVar19 = gnt4_PSMTXMultVec_bl(pfVar15,param_11,param_11);
                puVar9 = extraout_r4_08;
              }
              *(ushort *)(iVar6 + 8) = *(ushort *)(iVar6 + 8) | 0x100;
              DAT_80436948 = DAT_80436948 | uVar7;
            }
          }
        }
        else {
          local_dc = *(undefined4 *)(iVar6 + 0x10);
          uVar19 = gnt4_GXInitLightColor_bl(iVar6 + 0x50,&local_dc);
          *(undefined4 *)(iVar6 + 0x14) = *(undefined4 *)(iVar6 + 0x10);
          *(ushort *)(iVar6 + 8) = *(ushort *)(iVar6 + 8) | 0x80;
          uVar4 = *(ushort *)(iVar6 + 8) & 3;
          puVar9 = extraout_r4_06;
          if (uVar4 != 1) {
            if (((*(ushort *)(iVar6 + 8) & 3) == 0) || (3 < uVar4)) {
              param_11 = (float *)&DAT_80435e70;
              uVar19 = gnt4___assert_bl(uVar19,param_2,param_3,param_4,param_5,param_6,param_7,
                                        param_8,&DAT_80435e68,0x298,&DAT_80435e70,param_12,param_13,
                                        param_14,param_15,param_16);
              puVar9 = extraout_r4_07;
            }
            else {
              DAT_8043694c = DAT_8043694c | *(uint *)(iVar6 + 0x4c);
            }
          }
          if ((*(ushort *)(iVar6 + 8) & 4) != 0) {
            DAT_80436944 = DAT_80436944 | *(uint *)(iVar6 + 0x4c);
          }
          if ((*(ushort *)(iVar6 + 8) & 0x10) != 0) {
            DAT_80436950 = DAT_80436950 | *(uint *)(iVar6 + 0x4c);
          }
        }
      }
    }
LAB_80244f08:
  }
  iVar6 = gnt4_HSD_LightID2Index_bl
                    (uVar19,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x100,puVar9,
                     param_11,param_12,param_13,param_14,param_15,param_16);
  if ((iVar6 < 0) || (8 < iVar6)) {
    iVar6 = 0;
  }
  else {
    iVar6 = (&DAT_803f8dc0)[iVar6];
  }
  if (iVar6 == 0) {
    for (; puVar11 != (undefined4 *)0x0; puVar11 = (undefined4 *)*puVar11) {
      iVar6 = puVar11[1];
      if ((((iVar6 != 0) && (uVar4 = *(ushort *)(iVar6 + 8), (uVar4 & 0x20) == 0)) &&
          ((uVar4 & 3) == 0)) && ((uVar4 & 0x14) != 0)) {
        if ((uVar4 & 3) == 0) {
          iVar12 = 8;
          if (DAT_803f8de0 != 0) break;
        }
        else {
          iVar12 = DAT_80436940;
          DAT_80436940 = DAT_80436940 + 1;
        }
        (&DAT_803f8dc0)[iVar12] = iVar6;
        uVar8 = gnt4_HSD_Index2LightID_bl(iVar12);
        *(undefined4 *)(iVar6 + 0x4c) = uVar8;
        break;
      }
    }
  }
  iVar6 = DAT_80436940;
  piVar14 = piVar13;
  for (iVar12 = 0; (iVar5 < 8 && (iVar12 < iVar6)); iVar12 = iVar12 + 1) {
    if ((iVar12 < 0) || (7 < iVar12)) {
      iVar16 = 0;
    }
    else {
      iVar16 = *piVar14;
    }
    iVar10 = iVar5;
    if (((iVar16 != 0) && ((*(ushort *)(iVar16 + 8) & 8) != 0)) &&
       ((*(ushort *)(iVar16 + 8) & 0x14) != 0)) {
      iVar10 = iVar5 + 1;
      uVar7 = gnt4_HSD_Index2LightID_bl(iVar5);
      *(uint *)(iVar16 + 0x90) = uVar7;
      if (uVar7 != 0) {
        local_e4 = *(undefined4 *)(iVar16 + 0x10);
        gnt4_GXInitLightColor_bl(iVar16 + 0x94,&local_e4);
        dVar18 = (double)FLOAT_8043d208;
        *(float *)(iVar16 + 0x38) = FLOAT_8043d228;
        dVar20 = (double)FLOAT_8043d20c;
        dVar21 = (double)(*(float *)(iVar16 + 0x38) * FLOAT_8043d220);
        dVar22 = (double)(float)(dVar20 - dVar21);
        dVar23 = dVar18;
        uVar19 = gnt4_GXInitLightAttn_bl(dVar18,dVar18,dVar20,dVar21,dVar18,dVar22,iVar16 + 0x94);
        uVar4 = *(ushort *)(iVar16 + 8) & 3;
        if (uVar4 == 1) {
          puVar9 = &DAT_802b520c;
          local_d0 = DAT_802b5200;
          local_cc = DAT_802b5204;
          local_c8 = DAT_802b5208;
          local_c4 = DAT_802b520c;
          local_c0 = DAT_802b5210;
          local_bc = DAT_802b5214;
          param_12 = DAT_802b5208;
          param_13 = DAT_802b5204;
          param_14 = DAT_802b5200;
          if (iVar16 != 0) {
            gnt4_HSD_LObjGetPosition_bl
                      (uVar19,dVar18,dVar20,dVar21,dVar23,dVar22,param_7,param_8,iVar16,&local_d0,
                       (undefined *)&DAT_802b520c,DAT_802b5208,DAT_802b5204,DAT_802b5200,param_15,
                       param_16);
            gnt4_HSD_LObjGetInterest_bl
                      (uVar19,dVar18,dVar20,dVar21,dVar23,dVar22,param_7,param_8,iVar16,&local_c4,
                       (undefined *)puVar9,param_12,param_13,param_14,param_15,param_16);
            gnt4_PSVECSubtract_bl(&local_c4,&local_d0,(float *)(iVar16 + 0x3c));
            if ((iVar16 == -0x3c) || (iVar16 == -0x3c)) {
              iVar5 = -1;
            }
            else if (((DOUBLE_8043d218 < ABS((double)*(float *)(iVar16 + 0x3c))) ||
                     (DOUBLE_8043d218 < ABS((double)*(float *)(iVar16 + 0x40)))) ||
                    (DOUBLE_8043d218 < ABS((double)*(float *)(iVar16 + 0x44)))) {
              gnt4_PSVECNormalize_bl((float *)(iVar16 + 0x3c),(float *)(iVar16 + 0x3c));
              iVar5 = 0;
            }
            else {
              iVar5 = -1;
            }
            fVar3 = FLOAT_8043d20c;
            fVar2 = FLOAT_8043d208;
            if (iVar5 != 0) {
              *(float *)(iVar16 + 0x3c) = FLOAT_8043d208;
              *(float *)(iVar16 + 0x40) = fVar2;
              *(float *)(iVar16 + 0x44) = fVar3;
            }
          }
          param_11 = (float *)(iVar16 + 0x3c);
          gnt4_PSMTXMultVecSR_bl(pfVar15,param_11,param_11);
          gnt4_PSVECNormalize_bl((float *)(iVar16 + 0x3c),(float *)(iVar16 + 0x3c));
        }
        else if (((*(ushort *)(iVar16 + 8) & 3) == 0) || (3 < uVar4)) {
          param_11 = (float *)&DAT_80435e70;
          gnt4___assert_bl(uVar19,dVar18,dVar20,dVar21,dVar23,dVar22,param_7,param_8,&DAT_80435e68,
                           0x2c0,&DAT_80435e70,param_12,param_13,param_14,param_15,param_16);
        }
        else {
          gnt4_HSD_LObjGetPosition_bl
                    (uVar19,dVar18,dVar20,dVar21,dVar23,dVar22,param_7,param_8,iVar16,
                     (undefined4 *)(iVar16 + 0x3c),(undefined *)param_11,param_12,param_13,param_14,
                     param_15,param_16);
          param_11 = (float *)(iVar16 + 0x3c);
          gnt4_PSMTXMultVec_bl(pfVar15,param_11,param_11);
        }
        *(ushort *)(iVar16 + 8) = *(ushort *)(iVar16 + 8) | 0x100;
        DAT_80436948 = DAT_80436948 | uVar7;
      }
    }
    piVar14 = piVar14 + 1;
    iVar5 = iVar10;
  }
  for (iVar5 = 0; iVar5 < iVar6; iVar5 = iVar5 + 1) {
    if ((iVar5 < 0) || (7 < iVar5)) {
      iVar12 = 0;
    }
    else {
      iVar12 = *piVar13;
    }
    if (iVar12 != 0) {
      uVar4 = *(ushort *)(iVar12 + 8);
      uVar8 = *(undefined4 *)(iVar12 + 0x10);
      dVar23 = (double)*(float *)(iVar12 + 0x38);
      local_d4 = uVar8;
      if (((uVar4 & 0x20) == 0) && ((uVar4 & 3) != 0)) {
        if ((uVar4 & 0x14) != 0) {
          local_d4._0_1_ = (char)((uint)uVar8 >> 0x18);
          if ((((*(char *)(iVar12 + 0x14) != local_d4._0_1_) ||
               (local_d4._1_1_ = (char)((uint)uVar8 >> 0x10),
               *(char *)(iVar12 + 0x15) != local_d4._1_1_)) ||
              (local_d4._2_1_ = (char)((uint)uVar8 >> 8), *(char *)(iVar12 + 0x16) != local_d4._2_1_
              )) || (local_d4._3_1_ = (char)uVar8,
                    bVar1 = *(char *)(iVar12 + 0x17) != (char)local_d4, bVar1)) {
            local_e8 = uVar8;
            gnt4_GXInitLightColor_bl(iVar12 + 0x50,&local_e8);
            *(undefined4 *)(iVar12 + 0x14) = local_d4;
            *(ushort *)(iVar12 + 8) = *(ushort *)(iVar12 + 8) | 0x80;
          }
          if ((*(ushort *)(iVar12 + 8) & 0x80) != 0) {
            gnt4_GXLoadLightObjImm_bl(iVar12 + 0x50,*(undefined4 *)(iVar12 + 0x4c));
            *(ushort *)(iVar12 + 8) = *(ushort *)(iVar12 + 8) & 0xff7f;
          }
        }
        if (*(int *)(iVar12 + 0x90) != 0) {
          if ((double)*(float *)(iVar12 + 0x38) != dVar23) {
            dVar18 = (double)FLOAT_8043d220;
            dVar20 = (double)FLOAT_8043d208;
            dVar21 = (double)FLOAT_8043d20c;
            *(float *)(iVar12 + 0x38) = (float)dVar23;
            gnt4_GXInitLightAttn_bl
                      (dVar20,dVar20,dVar21,(double)(float)(dVar23 * dVar18),dVar20,
                       (double)(float)(dVar21 - (double)(float)(dVar23 * dVar18)),iVar12 + 0x94);
            *(ushort *)(iVar12 + 8) = *(ushort *)(iVar12 + 8) | 0x100;
          }
          if ((*(ushort *)(iVar12 + 8) & 0x100) != 0) {
            gnt4_GXLoadLightObjImm_bl(iVar12 + 0x94,*(undefined4 *)(iVar12 + 0x90));
            *(ushort *)(iVar12 + 8) = *(ushort *)(iVar12 + 8) & 0xfeff;
          }
        }
      }
    }
    piVar13 = piVar13 + 1;
  }
  gnt4__restgpr_24_bl();
  return;
}



// ==== 80245398  zz_0245398_ ====

void zz_0245398_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
                char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  ushort uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined4 *puVar6;
  int *piVar7;
  undefined8 extraout_f1;
  
  DAT_803f8dc0 = (int *)0x0;
  DAT_803f8dc4 = (int *)0x0;
  DAT_803f8dc8 = (int *)0x0;
  DAT_803f8dcc = (int *)0x0;
  DAT_803f8dd0 = (int *)0x0;
  DAT_803f8dd4 = (int *)0x0;
  DAT_803f8dd8 = (int *)0x0;
  DAT_803f8ddc = (int *)0x0;
  DAT_80436940 = 0;
  DAT_803f8de0 = (int *)0x0;
  for (; DAT_8043693c != (undefined4 *)0x0;
      DAT_8043693c = (undefined4 *)gnt4_HSD_SListRemove_bl(DAT_8043693c)) {
    piVar7 = (int *)DAT_8043693c[1];
    if (piVar7 != (int *)0x0) {
      uVar1 = *(ushort *)(piVar7 + 1);
      uVar2 = countLeadingZeros(0xffff - (uint)uVar1);
      uVar2 = uVar2 >> 5;
      if (uVar2 == 0) {
        uVar2 = countLeadingZeros((uint)uVar1);
        *(ushort *)(piVar7 + 1) = uVar1 - 1;
        uVar2 = uVar2 >> 5;
      }
      if ((uVar2 != 0) && (piVar7 != (int *)0x0)) {
        (**(code **)(*piVar7 + 0x30))(piVar7);
        param_1 = (**(code **)(*piVar7 + 0x34))(piVar7);
      }
    }
  }
LAB_802456b0:
  if (param_9 == (int *)0x0) {
    return;
  }
  puVar4 = DAT_8043693c;
  if (param_9 != (int *)0x0) {
    for (; puVar4 != (undefined4 *)0x0; puVar4 = (undefined4 *)*puVar4) {
      if ((int *)puVar4[1] == param_9) {
        if (param_9 != (int *)0x0) {
          puVar4 = &DAT_8043693c;
          goto LAB_802455e0;
        }
        break;
      }
    }
    goto LAB_802455fc;
  }
  goto LAB_802456ac;
  while ((int *)puVar4[1] != param_9) {
LAB_802455e0:
    puVar6 = puVar4;
    puVar4 = (undefined4 *)*puVar6;
    if (puVar4 == (undefined4 *)0x0) goto LAB_802455fc;
  }
  if (param_9 == DAT_803f8dc0) {
    DAT_803f8dc0 = (int *)0x0;
  }
  if (param_9 == DAT_803f8dc4) {
    DAT_803f8dc4 = (int *)0x0;
  }
  if (param_9 == DAT_803f8dc8) {
    DAT_803f8dc8 = (int *)0x0;
  }
  if (param_9 == DAT_803f8dcc) {
    DAT_803f8dcc = (int *)0x0;
  }
  if (param_9 == DAT_803f8dd0) {
    DAT_803f8dd0 = (int *)0x0;
  }
  if (param_9 == DAT_803f8dd4) {
    DAT_803f8dd4 = (int *)0x0;
  }
  if (param_9 == DAT_803f8dd8) {
    DAT_803f8dd8 = (int *)0x0;
  }
  if (param_9 == DAT_803f8ddc) {
    DAT_803f8ddc = (int *)0x0;
  }
  if (param_9 == DAT_803f8de0) {
    DAT_803f8de0 = (int *)0x0;
  }
  uVar3 = gnt4_HSD_SListRemove_bl((undefined4 *)*puVar6);
  *puVar6 = uVar3;
  if (param_9 != (int *)0x0) {
    uVar1 = *(ushort *)(param_9 + 1);
    uVar2 = countLeadingZeros(0xffff - (uint)uVar1);
    uVar2 = uVar2 >> 5;
    if (uVar2 == 0) {
      uVar2 = countLeadingZeros((uint)uVar1);
      *(ushort *)(param_9 + 1) = uVar1 - 1;
      uVar2 = uVar2 >> 5;
    }
    if ((uVar2 != 0) && (param_9 != (int *)0x0)) {
      (**(code **)(*param_9 + 0x30))(param_9);
      param_1 = (**(code **)(*param_9 + 0x34))(param_9);
    }
  }
LAB_802455fc:
  if ((param_9 != (int *)0x0) &&
     (*(short *)(param_9 + 1) = *(short *)(param_9 + 1) + 1, *(short *)(param_9 + 1) == -1)) {
    param_11 = s_HSD_OBJ_o__>ref_count____HSD_OBJ_803ac658;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_object_h_803ac64c,0x5d,s_HSD_OBJ_o__>ref_count____HSD_OBJ_803ac658,
                               param_12,param_13,param_14,param_15,param_16);
  }
  for (piVar7 = (int *)&DAT_8043693c; *piVar7 != 0; piVar7 = (int *)*piVar7) {
    if (param_9 == (int *)0x0) {
      param_11 = &DAT_80435e7c;
      param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435e74,0x163,&DAT_80435e7c,param_12,param_13,param_14,
                                 param_15,param_16);
    }
    uVar1 = *(ushort *)((int)param_9 + 10);
    iVar5 = *(int *)(*piVar7 + 4);
    if (iVar5 == 0) {
      param_11 = &DAT_80435e7c;
      param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435e74,0x163,&DAT_80435e7c,param_12,param_13,param_14,
                                 param_15,param_16);
    }
    if ((uVar1 & 0xff) < (*(ushort *)(iVar5 + 10) & 0xff)) break;
  }
  iVar5 = gnt4_HSD_SListPrepend_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar7,param_9
                     ,param_11,param_12,param_13,param_14,param_15,param_16);
  *piVar7 = iVar5;
  param_1 = extraout_f1;
LAB_802456ac:
  param_9 = (int *)param_9[3];
  goto LAB_802456b0;
}



// ==== 802456d8  gnt4-HSD_LObjGetCurrentByType-bl ====

int gnt4_HSD_LObjGetCurrentByType_bl(ushort param_1)

{
  undefined4 *puVar1;
  
  puVar1 = DAT_8043693c;
  while( true ) {
    if (puVar1 == (undefined4 *)0x0) {
      return 0;
    }
    if ((param_1 & 3) == (*(ushort *)(puVar1[1] + 8) & 3)) break;
    puVar1 = (undefined4 *)*puVar1;
  }
  return puVar1[1];
}



// ==== 8024570c  gnt4-HSD_LightID2Index-bl ====

undefined4
gnt4_HSD_LightID2Index_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 unaff_r31;
  
  if (param_9 == 0x10) {
    return 4;
  }
  if (param_9 < 0x10) {
    if (param_9 == 4) {
      return 2;
    }
    if (param_9 < 4) {
      if (param_9 == 2) {
        return 1;
      }
      if ((param_9 < 2) && (0 < param_9)) {
        return 0;
      }
    }
    else if (param_9 == 8) {
      return 3;
    }
  }
  else {
    if (param_9 == 0x80) {
      return 7;
    }
    if (param_9 < 0x80) {
      if (param_9 == 0x40) {
        return 6;
      }
      if ((param_9 < 0x40) && (param_9 == 0x20)) {
        return 5;
      }
    }
    else if (param_9 == 0x100) {
      return 8;
    }
  }
  gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e68,
                   0x4a8,&DAT_80435e70,param_12,param_13,param_14,param_15,param_16);
  return unaff_r31;
}



// ==== 802457f8  gnt4-HSD_Index2LightID-bl ====

undefined4 gnt4_HSD_Index2LightID_bl(undefined4 param_1)

{
  switch(param_1) {
  case 0:
    return 1;
  case 1:
    return 2;
  case 2:
    return 4;
  case 3:
    return 8;
  case 4:
    return 0x10;
  case 5:
    return 0x20;
  case 6:
    return 0x40;
  case 7:
    return 0x80;
  case 8:
    return 0x100;
  default:
    return 0;
  }
}



// ==== 80245868  gnt4-HSD_LObjRemoveAll-bl ====

void gnt4_HSD_LObjRemoveAll_bl(int *param_1)

{
  ushort uVar1;
  uint uVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int *piVar6;
  
  do {
    piVar6 = param_1;
    if (piVar6 == (int *)0x0) {
      return;
    }
    param_1 = (int *)piVar6[3];
    if (piVar6 != (int *)0x0) {
      puVar4 = &DAT_8043693c;
      do {
        puVar5 = puVar4;
        puVar4 = (undefined4 *)*puVar5;
        if (puVar4 == (undefined4 *)0x0) goto LAB_802459d8;
      } while ((int *)puVar4[1] != piVar6);
      if (piVar6 == DAT_803f8dc0) {
        DAT_803f8dc0 = (int *)0x0;
      }
      if (piVar6 == DAT_803f8dc4) {
        DAT_803f8dc4 = (int *)0x0;
      }
      if (piVar6 == DAT_803f8dc8) {
        DAT_803f8dc8 = (int *)0x0;
      }
      if (piVar6 == DAT_803f8dcc) {
        DAT_803f8dcc = (int *)0x0;
      }
      if (piVar6 == DAT_803f8dd0) {
        DAT_803f8dd0 = (int *)0x0;
      }
      if (piVar6 == DAT_803f8dd4) {
        DAT_803f8dd4 = (int *)0x0;
      }
      if (piVar6 == DAT_803f8dd8) {
        DAT_803f8dd8 = (int *)0x0;
      }
      if (piVar6 == DAT_803f8ddc) {
        DAT_803f8ddc = (int *)0x0;
      }
      if (piVar6 == DAT_803f8de0) {
        DAT_803f8de0 = (int *)0x0;
      }
      uVar3 = gnt4_HSD_SListRemove_bl((undefined4 *)*puVar5);
      *puVar5 = uVar3;
      if (piVar6 != (int *)0x0) {
        uVar1 = *(ushort *)(piVar6 + 1);
        uVar2 = countLeadingZeros(0xffff - (uint)uVar1);
        uVar2 = uVar2 >> 5;
        if (uVar2 == 0) {
          uVar2 = countLeadingZeros((uint)uVar1);
          *(ushort *)(piVar6 + 1) = uVar1 - 1;
          uVar2 = uVar2 >> 5;
        }
        if ((uVar2 != 0) && (piVar6 != (int *)0x0)) {
          (**(code **)(*piVar6 + 0x30))(piVar6);
          (**(code **)(*piVar6 + 0x34))(piVar6);
        }
      }
    }
LAB_802459d8:
    if (piVar6 != (int *)0x0) {
      uVar1 = *(ushort *)(piVar6 + 1);
      uVar2 = countLeadingZeros(0xffff - (uint)uVar1);
      uVar2 = uVar2 >> 5;
      if (uVar2 == 0) {
        uVar2 = countLeadingZeros((uint)uVar1);
        *(ushort *)(piVar6 + 1) = uVar1 - 1;
        uVar2 = uVar2 >> 5;
      }
      if ((uVar2 != 0) && (piVar6 != (int *)0x0)) {
        (**(code **)(*piVar6 + 0x30))(piVar6);
        (**(code **)(*piVar6 + 0x34))(piVar6);
      }
    }
  } while( true );
}



// ==== 80245a74  gnt4-HSD_LObjSetColor ====

void gnt4_HSD_LObjSetColor(int param_1,undefined4 *param_2)

{
  *(undefined4 *)(param_1 + 0x10) = *param_2;
  return;
}



// ==== 80245a80  zz_0245a80_ ====

void zz_0245a80_(int param_1,undefined4 *param_2)

{
  *param_2 = *(undefined4 *)(param_1 + 0x10);
  return;
}



// ==== 80245a8c  gnt4-HSD_LObjGetPosition-bl ====

undefined4
gnt4_HSD_LObjGetPosition_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
          undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  if ((param_9 == 0) || (*(int *)(param_9 + 0x18) == 0)) {
    uVar1 = 0;
  }
  else {
    gnt4_HSD_WObjGetPosition_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(int *)(param_9 + 0x18),param_10,param_11,param_12,param_13,param_14,param_15,
               param_16);
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 80245acc  gnt4-HSD_LObjGetInterest-bl ====

undefined4
gnt4_HSD_LObjGetInterest_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
          undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  
  if ((param_9 == 0) || (*(int *)(param_9 + 0x1c) == 0)) {
    uVar1 = 0;
  }
  else {
    gnt4_HSD_WObjGetPosition_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(int *)(param_9 + 0x1c),param_10,param_11,param_12,param_13,param_14,param_15,
               param_16);
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 80245b0c  gnt4-LObjLoad-bl ====

/* WARNING: Removing unreachable block (ram,0x80245b6c) */

undefined4
gnt4_LObjLoad_bl(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  ushort uVar4;
  ushort uVar8;
  uint uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int *piVar9;
  undefined4 *puVar10;
  int iVar11;
  uint uVar12;
  uint extraout_r4;
  int *piVar13;
  double dVar14;
  
  *(undefined4 *)(param_9 + 0x10) = *(undefined4 *)(param_10 + 0xc);
  if (param_9 != 0) {
    *(ushort *)(param_9 + 8) = *(ushort *)(param_9 + 8) | *(ushort *)(param_10 + 8);
  }
  uVar4 = *(ushort *)(param_10 + 8);
  uVar12 = (uint)uVar4;
  uVar8 = uVar4 & 3;
  if (uVar8 == 2) {
    piVar9 = gnt4_HSD_WObjLoadDesc_bl
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int **)(param_10 + 0x10),uVar12,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    if (param_9 != 0) {
      piVar13 = *(int **)(param_9 + 0x18);
      if (piVar13 != (int *)0x0) {
        uVar4 = *(ushort *)(piVar13 + 1);
        uVar12 = countLeadingZeros(0xffff - (uint)uVar4);
        uVar12 = uVar12 >> 5;
        if (uVar12 == 0) {
          uVar12 = countLeadingZeros((uint)uVar4);
          *(ushort *)(piVar13 + 1) = uVar4 - 1;
          uVar12 = uVar12 >> 5;
        }
        if ((uVar12 != 0) && (piVar13 != (int *)0x0)) {
          (**(code **)(*piVar13 + 0x30))(piVar13);
          (**(code **)(*piVar13 + 0x34))(piVar13);
        }
      }
      *(int **)(param_9 + 0x18) = piVar9;
    }
    if ((*(ushort *)(param_10 + 10) & 1) == 0) {
      puVar10 = *(undefined4 **)(param_10 + 0x18);
      uVar6 = puVar10[2];
      uVar7 = *puVar10;
      if (param_9 != 0) {
        *(undefined4 *)(param_9 + 0x2c) = puVar10[1];
        *(undefined4 *)(param_9 + 0x28) = uVar7;
        *(undefined4 *)(param_9 + 0x30) = uVar6;
      }
    }
    else {
      if (param_9 != 0) {
        *(ushort *)(param_9 + 8) = *(ushort *)(param_9 + 8) | 0x40;
      }
      iVar11 = *(int *)(param_10 + 0x18);
      uVar7 = *(undefined4 *)(iVar11 + 0x14);
      uVar6 = *(undefined4 *)(iVar11 + 0x10);
      if (param_9 != 0) {
        *(undefined4 *)(param_9 + 0x2c) = *(undefined4 *)(iVar11 + 0xc);
        *(undefined4 *)(param_9 + 0x30) = uVar6;
        *(undefined4 *)(param_9 + 0x34) = uVar7;
      }
    }
  }
  else if (uVar8 < 2) {
    if (((uVar4 & 3) != 0) &&
       (piVar9 = gnt4_HSD_WObjLoadDesc_bl
                           (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            *(int **)(param_10 + 0x10),uVar12,param_11,param_12,param_13,param_14,
                            param_15,param_16), param_9 != 0)) {
      piVar13 = *(int **)(param_9 + 0x18);
      if (piVar13 != (int *)0x0) {
        uVar4 = *(ushort *)(piVar13 + 1);
        uVar12 = countLeadingZeros(0xffff - (uint)uVar4);
        uVar12 = uVar12 >> 5;
        if (uVar12 == 0) {
          uVar12 = countLeadingZeros((uint)uVar4);
          *(ushort *)(piVar13 + 1) = uVar4 - 1;
          uVar12 = uVar12 >> 5;
        }
        if ((uVar12 != 0) && (piVar13 != (int *)0x0)) {
          (**(code **)(*piVar13 + 0x30))(piVar13);
          (**(code **)(*piVar13 + 0x34))(piVar13);
        }
      }
      *(int **)(param_9 + 0x18) = piVar9;
    }
  }
  else if (uVar8 < 4) {
    piVar9 = gnt4_HSD_WObjLoadDesc_bl
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int **)(param_10 + 0x10),uVar12,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    if (param_9 != 0) {
      piVar13 = *(int **)(param_9 + 0x18);
      if (piVar13 != (int *)0x0) {
        uVar12 = (uint)*(ushort *)(piVar13 + 1);
        uVar5 = countLeadingZeros(0xffff - uVar12);
        uVar5 = uVar5 >> 5;
        if (uVar5 == 0) {
          uVar5 = countLeadingZeros(uVar12);
          *(ushort *)(piVar13 + 1) = *(ushort *)(piVar13 + 1) - 1;
          uVar5 = uVar5 >> 5;
        }
        if ((uVar5 != 0) && (piVar13 != (int *)0x0)) {
          (**(code **)(*piVar13 + 0x30))(piVar13);
          param_1 = (**(code **)(*piVar13 + 0x34))(piVar13);
          uVar12 = extraout_r4;
        }
      }
      *(int **)(param_9 + 0x18) = piVar9;
    }
    piVar9 = gnt4_HSD_WObjLoadDesc_bl
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int **)(param_10 + 0x14),uVar12,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    if (param_9 != 0) {
      piVar13 = *(int **)(param_9 + 0x1c);
      if (piVar13 != (int *)0x0) {
        uVar4 = *(ushort *)(piVar13 + 1);
        uVar12 = countLeadingZeros(0xffff - (uint)uVar4);
        uVar12 = uVar12 >> 5;
        if (uVar12 == 0) {
          uVar12 = countLeadingZeros((uint)uVar4);
          *(ushort *)(piVar13 + 1) = uVar4 - 1;
          uVar12 = uVar12 >> 5;
        }
        if ((uVar12 != 0) && (piVar13 != (int *)0x0)) {
          (**(code **)(*piVar13 + 0x30))(piVar13);
          (**(code **)(*piVar13 + 0x34))(piVar13);
        }
      }
      *(int **)(param_9 + 0x1c) = piVar9;
    }
    if ((*(ushort *)(param_10 + 10) & 1) == 0) {
      iVar11 = *(int *)(param_10 + 0x18);
      uVar6 = *(undefined4 *)(iVar11 + 0x10);
      uVar7 = *(undefined4 *)(iVar11 + 8);
      if (param_9 != 0) {
        *(undefined4 *)(param_9 + 0x2c) = *(undefined4 *)(iVar11 + 0xc);
        *(undefined4 *)(param_9 + 0x28) = uVar7;
        *(undefined4 *)(param_9 + 0x30) = uVar6;
      }
      uVar7 = (*(undefined4 **)(param_10 + 0x18))[1];
      if (param_9 != 0) {
        *(undefined4 *)(param_9 + 0x20) = **(undefined4 **)(param_10 + 0x18);
        *(undefined4 *)(param_9 + 0x24) = uVar7;
      }
    }
    else {
      if (param_9 != 0) {
        *(ushort *)(param_9 + 8) = *(ushort *)(param_9 + 8) | 0x40;
      }
      puVar10 = *(undefined4 **)(param_10 + 0x18);
      uVar7 = puVar10[5];
      uVar6 = puVar10[4];
      uVar1 = puVar10[3];
      uVar2 = puVar10[2];
      uVar3 = puVar10[1];
      if (param_9 != 0) {
        *(undefined4 *)(param_9 + 0x20) = *puVar10;
        *(undefined4 *)(param_9 + 0x24) = uVar3;
        *(undefined4 *)(param_9 + 0x28) = uVar2;
        *(undefined4 *)(param_9 + 0x2c) = uVar1;
        *(undefined4 *)(param_9 + 0x30) = uVar6;
        *(undefined4 *)(param_9 + 0x34) = uVar7;
      }
    }
  }
  else {
    dVar14 = (double)gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                      param_8,s_unexpected_lightdesc_flags___x__803ac6e8,uVar12,
                                      param_11,param_12,param_13,param_14,param_15,param_16);
    gnt4_HSD_Panic_bl(dVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e68,
                      0x660,&DAT_80435e88,param_12,param_13,param_14,param_15,param_16);
  }
  return 0;
}



// ==== 80245f20  gnt4-HSD_LObjLoadDesc-bl ====

int gnt4_HSD_LObjLoadDesc_bl
              (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
              double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
              int param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
              undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  int *piVar2;
  undefined4 extraout_r4;
  int *piVar4;
  int local_18 [3];
  undefined **ppuVar3;
  
  piVar4 = local_18;
  for (; param_9 != (int *)0x0; param_9 = (int *)param_9[1]) {
    if ((*param_9 == 0) ||
       (puVar1 = (undefined4 *)
                 gnt4_hsdSearchClassInfo_bl
                           (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*param_9
                            ,param_10,param_11,param_12,param_13,param_14,param_15,param_16),
       puVar1 == (undefined4 *)0x0)) {
      ppuVar3 = DAT_80436938;
      if (DAT_80436938 == (undefined **)0x0) {
        ppuVar3 = &PTR_gnt4_LObjInfoInit_bl_803ac5d0;
      }
      piVar2 = gnt4_hsdNew_bl(ppuVar3);
      if (piVar2 == (int *)0x0) {
        gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80435e68,0x5dc,&DAT_80435e84,param_12,param_13,param_14,param_15,
                         param_16);
      }
      *piVar4 = (int)piVar2;
    }
    else {
      piVar2 = gnt4_hsdNew_bl(puVar1);
      *piVar4 = (int)piVar2;
      if (*piVar4 == 0) {
        gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80435e68,0x682,&DAT_80435e8c,param_12,param_13,param_14,param_15,
                         param_16);
      }
    }
    param_11 = *(int *)*piVar4;
    param_1 = (**(code **)(param_11 + 0x3c))((int *)*piVar4,param_9);
    piVar4 = (int *)(*piVar4 + 0xc);
    param_10 = extraout_r4;
  }
  *piVar4 = 0;
  return local_18[0];
}



// ==== 80246010  gnt4-LObjRelease-bl ====

void gnt4_LObjRelease_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                        double param_5,double param_6,double param_7,double param_8,int param_9,
                        undefined4 param_10,undefined4 param_11,undefined4 param_12,
                        undefined4 param_13,undefined4 param_14,undefined4 param_15,
                        undefined4 param_16)

{
  ushort uVar1;
  uint uVar2;
  int *piVar3;
  
  gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(undefined4 **)(param_9 + 0x48),param_10,param_11,param_12,param_13,param_14,
                      param_15,param_16);
  if (param_9 == 0) {
    piVar3 = (int *)0x0;
  }
  else {
    piVar3 = *(int **)(param_9 + 0x18);
  }
  if (piVar3 != (int *)0x0) {
    uVar1 = *(ushort *)(piVar3 + 1);
    uVar2 = countLeadingZeros(0xffff - (uint)uVar1);
    uVar2 = uVar2 >> 5;
    if (uVar2 == 0) {
      uVar2 = countLeadingZeros((uint)uVar1);
      *(ushort *)(piVar3 + 1) = uVar1 - 1;
      uVar2 = uVar2 >> 5;
    }
    if ((uVar2 != 0) && (piVar3 != (int *)0x0)) {
      (**(code **)(*piVar3 + 0x30))(piVar3);
      (**(code **)(*piVar3 + 0x34))(piVar3);
    }
  }
  if (param_9 == 0) {
    piVar3 = (int *)0x0;
  }
  else {
    piVar3 = *(int **)(param_9 + 0x1c);
  }
  if (piVar3 != (int *)0x0) {
    uVar1 = *(ushort *)(piVar3 + 1);
    uVar2 = countLeadingZeros(0xffff - (uint)uVar1);
    uVar2 = uVar2 >> 5;
    if (uVar2 == 0) {
      uVar2 = countLeadingZeros((uint)uVar1);
      *(ushort *)(piVar3 + 1) = uVar1 - 1;
      uVar2 = uVar2 >> 5;
    }
    if ((uVar2 != 0) && (piVar3 != (int *)0x0)) {
      (**(code **)(*piVar3 + 0x30))(piVar3);
      (**(code **)(*piVar3 + 0x34))(piVar3);
    }
  }
  (**(code **)(DAT_803ac5e4 + 0x30))(param_9);
  return;
}



// ==== 80246174  gnt4-LObjAmnesia-bl ====

void gnt4_LObjAmnesia_bl(undefined **param_1)

{
  if (param_1 == DAT_80436938) {
    DAT_80436938 = (undefined **)0x0;
  }
  if (param_1 == &PTR_gnt4_LObjInfoInit_bl_803ac5d0) {
    DAT_8043693c = 0;
  }
  (**(code **)(DAT_803ac5e4 + 0x38))();
  return;
}



// ==== 802461d4  gnt4-LObjInfoInit-bl ====

void gnt4_LObjInfoInit_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined4 in_r9;
  undefined4 in_r10;
  
  gnt4_hsdInitClassInfo_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-0x7fc53a30,
             &PTR_zz_025acb8__803ad548,s_sysdolphin_base_library_803ac70c,s_hsd_lobj_803ac724,0x44,
             0xd4,in_r9,in_r10);
  DAT_803ac600 = gnt4_LObjRelease_bl;
  DAT_803ac608 = gnt4_LObjAmnesia_bl;
  DAT_803ac60c = gnt4_LObjLoad_bl;
  DAT_803ac610 = gnt4_LObjUpdateFunc_bl;
  return;
}



// ==== 80246254  zz_0246254_ ====

void zz_0246254_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  if (param_9 < 1) {
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80435e98,0x2f,s_ref_width_>_0_803ac774,param_12,param_13,
                               param_14,param_15,param_16);
  }
  if (param_10 < 1) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e98,
                     0x30,s_ref_height_>_0_803ac784,param_12,param_13,param_14,param_15,param_16);
  }
  DAT_80435e90 = param_9;
  DAT_80435e94 = param_10;
  return;
}



// ==== 802462c4  zz_02462c4_ ====

void zz_02462c4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  undefined4 extraout_r4_00;
  undefined8 uVar3;
  
  if (param_9 != 0) {
    uVar3 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                *(undefined4 **)(param_9 + 0x84),param_10,param_11,param_12,param_13
                                ,param_14,param_15,param_16);
    *(undefined4 *)(param_9 + 0x84) = 0;
    uVar2 = extraout_r4;
    iVar1 = gnt4_HSD_CObjGetEyePositionWObj_bl
                      (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
    uVar3 = zz_02598f4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,uVar2,
                        param_11,param_12,param_13,param_14,param_15,param_16);
    uVar2 = extraout_r4_00;
    iVar1 = gnt4_HSD_CObjGetInterestWObj_bl
                      (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       extraout_r4_00,param_11,param_12,param_13,param_14,param_15,param_16);
    zz_02598f4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,uVar2,param_11,
                param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8024631c  zz_024631c_ ====

void zz_024631c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint *puVar1;
  int iVar2;
  undefined4 *extraout_r4;
  undefined4 *puVar3;
  undefined4 extraout_r4_00;
  undefined8 uVar4;
  
  if ((param_9 != 0) && (param_10 != (undefined4 *)0x0)) {
    puVar3 = param_10;
    if (*(undefined4 **)(param_9 + 0x84) != (undefined4 *)0x0) {
      param_1 = gnt4_HSD_AObjRemove(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    *(undefined4 **)(param_9 + 0x84),param_10,param_11,param_12,
                                    param_13,param_14,param_15,param_16);
      puVar3 = extraout_r4;
    }
    puVar1 = gnt4_HSD_AObjLoadDesc
                       (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (uint *)*param_10,puVar3,param_11,param_12,param_13,param_14,param_15,
                        param_16);
    *(uint **)(param_9 + 0x84) = puVar1;
    iVar2 = gnt4_HSD_CObjGetEyePositionWObj_bl
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       puVar3,param_11,param_12,param_13,param_14,param_15,param_16);
    uVar4 = gnt4_HSD_WObjAddAnim_bl
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                       (undefined4 *)param_10[1],param_11,param_12,param_13,param_14,param_15,
                       param_16);
    iVar2 = gnt4_HSD_CObjGetInterestWObj_bl
                      (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       extraout_r4_00,param_11,param_12,param_13,param_14,param_15,param_16);
    gnt4_HSD_WObjAddAnim_bl
              (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
               (undefined4 *)param_10[2],param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80246398  gnt4-CObjUpdateFunc-bl ====

void gnt4_CObjUpdateFunc_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined8 uVar2;
  float local_18;
  float local_14;
  float local_10;
  
  if (param_9 != 0) {
    uVar1 = 0x803b0000;
    switch(param_10) {
    case 1:
      uVar2 = gnt4_HSD_CObjGetEyePosition_bl
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         &local_18,(undefined *)0x803b0000,param_12,param_13,param_14,param_15,
                         param_16);
      local_18 = *param_11;
      gnt4_HSD_CObjSetEyePosition_bl
                (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,&local_18,
                 uVar1,param_12,param_13,param_14,param_15,param_16);
      break;
    case 2:
      uVar2 = gnt4_HSD_CObjGetEyePosition_bl
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         &local_18,(undefined *)0x803b0000,param_12,param_13,param_14,param_15,
                         param_16);
      local_14 = *param_11;
      gnt4_HSD_CObjSetEyePosition_bl
                (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,&local_18,
                 uVar1,param_12,param_13,param_14,param_15,param_16);
      break;
    case 3:
      uVar2 = gnt4_HSD_CObjGetEyePosition_bl
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         &local_18,(undefined *)0x803b0000,param_12,param_13,param_14,param_15,
                         param_16);
      local_10 = *param_11;
      gnt4_HSD_CObjSetEyePosition_bl
                (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,&local_18,
                 uVar1,param_12,param_13,param_14,param_15,param_16);
      break;
    case 5:
      uVar2 = gnt4_HSD_CObjGetInterest_bl
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         &local_18,(undefined *)0x803b0000,param_12,param_13,param_14,param_15,
                         param_16);
      local_18 = *param_11;
      gnt4_HSD_CObjSetInterest_bl
                (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,&local_18,
                 uVar1,param_12,param_13,param_14,param_15,param_16);
      break;
    case 6:
      uVar2 = gnt4_HSD_CObjGetInterest_bl
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         &local_18,(undefined *)0x803b0000,param_12,param_13,param_14,param_15,
                         param_16);
      local_18 = *param_11;
      gnt4_HSD_CObjSetInterest_bl
                (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,&local_18,
                 uVar1,param_12,param_13,param_14,param_15,param_16);
      break;
    case 7:
      uVar2 = gnt4_HSD_CObjGetInterest_bl
                        (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         &local_18,(undefined *)0x803b0000,param_12,param_13,param_14,param_15,
                         param_16);
      local_18 = *param_11;
      gnt4_HSD_CObjSetInterest_bl
                (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,&local_18,
                 uVar1,param_12,param_13,param_14,param_15,param_16);
      break;
    case 9:
      gnt4_HSD_CObjSetRoll_bl
                ((double)*param_11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                 &switchD_802463d4::switchdataD_803ac794,(float *)0x803b0000,param_12,param_13,
                 param_14,param_15,param_16);
      break;
    case 10:
      gnt4_HSD_CObjSetFov_bl((double)*param_11,param_9);
      break;
    case 0xb:
      gnt4_HSD_CObjSetNear_bl((double)*param_11,param_9);
      break;
    case 0xc:
      gnt4_HSD_CObjSetFar_bl((double)*param_11,param_9);
    }
  }
  return;
}



// ==== 802464dc  zz_02464dc_ ====

void zz_02464dc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int *param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar1;
  undefined8 uVar2;
  
  if (param_9 != (int *)0x0) {
    pfVar1 = *(float **)(*param_9 + 0x40);
    uVar2 = gnt4_HSD_AObjInterpretAnim
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       (uint *)param_9[0x21],(uint)param_9,pfVar1,param_12,param_13,param_14,
                       param_15,param_16);
    uVar2 = gnt4_HSD_WObjInterpretAnim_bl
                      (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       (int *)param_9[9],extraout_r4,pfVar1,param_12,param_13,param_14,param_15,
                       param_16);
    gnt4_HSD_WObjInterpretAnim_bl
              (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int *)param_9[10],
               extraout_r4_00,pfVar1,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8024652c  zz_024652c_ ====

void zz_024652c_(double param_1,int param_2)

{
  if (param_2 != 0) {
    gnt4_HSD_AObjReqAnim(param_1,*(uint **)(param_2 + 0x84));
    gnt4_HSD_WObjReqAnim_bl(param_1,*(int *)(param_2 + 0x24));
    gnt4_HSD_WObjReqAnim_bl(param_1,*(int *)(param_2 + 0x28));
  }
  return;
}



// ==== 80246588  gnt4-setupTopHalfCamera-bl ====

/* WARNING: Removing unreachable block (ram,0x802467cc) */
/* WARNING: Removing unreachable block (ram,0x802467c4) */
/* WARNING: Removing unreachable block (ram,0x802467bc) */
/* WARNING: Removing unreachable block (ram,0x802465a8) */
/* WARNING: Removing unreachable block (ram,0x802465a0) */
/* WARNING: Removing unreachable block (ram,0x80246598) */

void gnt4_setupTopHalfCamera_bl(void)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int unaff_r27;
  double dVar7;
  double in_f29;
  double dVar8;
  double in_f30;
  double dVar9;
  double in_f31;
  double dVar10;
  double in_ps29_1;
  double in_ps30_1;
  double in_ps31_1;
  float afStack_a8 [16];
  undefined4 local_68;
  uint uStack_64;
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  float local_28;
  float fStack_24;
  float local_18;
  float fStack_14;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  local_18 = (float)in_f30;
  fStack_14 = (float)in_ps30_1;
  local_28 = (float)in_f29;
  fStack_24 = (float)in_ps29_1;
  iVar2 = gnt4__savegpr_26_bl();
  uStack_64 = (uint)DAT_803f8e84._2_2_;
  local_68 = 0x43300000;
  dVar10 = (double)*(float *)(iVar2 + 0x14);
  if (dVar10 < (double)(float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_8043d248)) {
    dVar7 = (double)*(float *)(iVar2 + 0x18);
    local_68 = 0x43300000;
    dVar9 = (double)*(float *)(iVar2 + 0xc);
    dVar8 = (double)*(float *)(iVar2 + 0x10);
    if ((double)(float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_8043d248) <= dVar7) {
      local_60 = 0x43300000;
      dVar7 = (double)(float)((double)CONCAT44(0x43300000,uStack_64) - DOUBLE_8043d248);
      uStack_5c = uStack_64;
    }
    iVar3 = gnt4___cvt_fp2unsigned_bl((double)(float)(dVar7 - dVar10));
    iVar4 = gnt4___cvt_fp2unsigned_bl((double)(float)(dVar8 - dVar9));
    iVar5 = gnt4___cvt_fp2unsigned_bl(dVar10);
    iVar6 = gnt4___cvt_fp2unsigned_bl(dVar9);
    gnt4_GXSetScissor_bl(iVar6,iVar5,iVar4,iVar3);
    uStack_54 = (uint)DAT_803f8e84._2_2_;
    local_58 = 0x43300000;
    dVar8 = (double)*(float *)(iVar2 + 0x18);
    dVar7 = (double)*(float *)(iVar2 + 0x14);
    dVar10 = dVar8;
    if ((double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_8043d248) <= dVar8) {
      local_50 = 0x43300000;
      dVar10 = (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_8043d248);
      uStack_4c = uStack_54;
    }
    dVar8 = (double)(float)((double)(float)(dVar10 - dVar7) / (double)(float)(dVar8 - dVar7));
    gnt4_GXSetViewport_bl
              ((double)*(float *)(iVar2 + 0xc),dVar7,
               (double)(float)((double)*(float *)(iVar2 + 0x10) - (double)*(float *)(iVar2 + 0xc)),
               (double)(float)(dVar10 - dVar7),(double)FLOAT_8043d240,(double)FLOAT_8043d244);
    bVar1 = *(byte *)(iVar2 + 0x50);
    if (bVar1 == 2) {
      dVar10 = (double)*(float *)(iVar2 + 0x40);
      unaff_r27 = 0;
      gnt4_C_MTXFrustum_bl
                (dVar10,-(double)(float)(dVar8 * (double)(float)(dVar10 - (double)*(float *)(iVar2 +
                                                                                            0x44)) -
                                        dVar10),(double)*(float *)(iVar2 + 0x48),
                 (double)*(float *)(iVar2 + 0x4c),(double)*(float *)(iVar2 + 0x38),
                 (double)*(float *)(iVar2 + 0x3c),afStack_a8);
    }
    else if (bVar1 < 2) {
      if (bVar1 != 0) {
        unaff_r27 = 0;
        dVar10 = gnt4_tan_bl((double)(float)(DOUBLE_8043d258 *
                                            DOUBLE_8043d238 * (double)*(float *)(iVar2 + 0x40)));
        dVar10 = (double)(float)((double)*(float *)(iVar2 + 0x38) * (double)(float)dVar10);
        dVar7 = (double)(float)(dVar10 * (double)*(float *)(iVar2 + 0x44));
        gnt4_C_MTXFrustum_bl
                  (dVar10,(double)(float)(dVar10 * -(double)(float)((double)FLOAT_8043d260 * dVar8 -
                                                                   (double)FLOAT_8043d244)),-dVar7,
                   dVar7,(double)*(float *)(iVar2 + 0x38),(double)*(float *)(iVar2 + 0x3c),
                   afStack_a8);
      }
    }
    else if (bVar1 < 4) {
      dVar10 = (double)*(float *)(iVar2 + 0x40);
      unaff_r27 = 1;
      gnt4_C_MTXOrtho_bl(dVar10,-(double)(float)(dVar8 * (double)(float)(dVar10 - (double)*(float *)
                                                  (iVar2 + 0x44)) - dVar10),
                         (double)*(float *)(iVar2 + 0x48),(double)*(float *)(iVar2 + 0x4c),
                         (double)*(float *)(iVar2 + 0x38),(double)*(float *)(iVar2 + 0x3c),
                         afStack_a8);
    }
    gnt4_GXSetProjection_bl(afStack_a8,unaff_r27);
  }
  gnt4__restgpr_26_bl();
  return;
}



// ==== 802467ec  gnt4-setupBottomHalfCamera-bl ====

/* WARNING: Removing unreachable block (ram,0x80246a98) */
/* WARNING: Removing unreachable block (ram,0x80246a90) */
/* WARNING: Removing unreachable block (ram,0x80246a88) */
/* WARNING: Removing unreachable block (ram,0x8024680c) */
/* WARNING: Removing unreachable block (ram,0x80246804) */
/* WARNING: Removing unreachable block (ram,0x802467fc) */

void gnt4_setupBottomHalfCamera_bl(void)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int unaff_r31;
  double in_f29;
  double dVar11;
  double in_f30;
  double dVar12;
  double in_f31;
  double dVar13;
  double in_ps29_1;
  double in_ps30_1;
  double in_ps31_1;
  float afStack_c8 [16];
  undefined4 local_88;
  uint uStack_84;
  undefined4 local_80;
  uint uStack_7c;
  undefined4 local_78;
  int iStack_74;
  undefined4 local_70;
  int iStack_6c;
  undefined4 local_68;
  uint uStack_64;
  undefined4 local_60;
  uint uStack_5c;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  float local_28;
  float fStack_24;
  float local_18;
  float fStack_14;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  local_18 = (float)in_f30;
  fStack_14 = (float)in_ps30_1;
  local_28 = (float)in_f29;
  fStack_24 = (float)in_ps29_1;
  iVar4 = gnt4__savegpr_26_bl();
  local_88 = 0x43300000;
  uVar10 = DAT_803f8e84._2_2_ - 8;
  uStack_84 = uVar10;
  if ((float)((double)CONCAT44(0x43300000,uVar10) - DOUBLE_8043d248) <= *(float *)(iVar4 + 0x18)) {
    uStack_84 = (uint)*(ushort *)(iVar4 + 0x1c);
    uStack_7c = (uint)*(ushort *)(iVar4 + 0x1e);
    local_88 = 0x43300000;
    dVar12 = (double)(float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_8043d248);
    local_80 = 0x43300000;
    dVar11 = (double)(float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_8043d248);
    uVar9 = uVar10;
    if (uVar10 < *(ushort *)(iVar4 + 0x20)) {
      uVar9 = (uint)*(ushort *)(iVar4 + 0x20);
    }
    iStack_74 = uVar9 - uVar10;
    local_78 = 0x43300000;
    iStack_6c = *(ushort *)(iVar4 + 0x22) - uVar10;
    dVar13 = (double)(float)((double)CONCAT44(0x43300000,iStack_74) - DOUBLE_8043d248);
    local_70 = 0x43300000;
    iVar5 = gnt4___cvt_fp2unsigned_bl
                      ((double)(float)((double)(float)((double)CONCAT44(0x43300000,iStack_6c) -
                                                      DOUBLE_8043d248) - dVar13));
    iVar6 = gnt4___cvt_fp2unsigned_bl((double)(float)(dVar11 - dVar12));
    iVar7 = gnt4___cvt_fp2unsigned_bl(dVar13);
    iVar8 = gnt4___cvt_fp2unsigned_bl(dVar12);
    gnt4_GXSetScissor_bl(iVar8,iVar7,iVar6,iVar5);
    local_68 = 0x43300000;
    fVar2 = *(float *)(iVar4 + 0x14);
    fVar3 = fVar2;
    if (fVar2 <= (float)((double)CONCAT44(0x43300000,uVar10) - DOUBLE_8043d248)) {
      local_60 = 0x43300000;
      fVar3 = (float)((double)CONCAT44(0x43300000,uVar10) - DOUBLE_8043d248);
      uStack_5c = uVar10;
    }
    local_58 = 0x43300000;
    local_50 = 0x43300000;
    dVar11 = (double)(fVar3 - (float)((double)CONCAT44(0x43300000,uVar10) - DOUBLE_8043d248));
    dVar12 = (double)(float)((double)(*(float *)(iVar4 + 0x18) -
                                     (float)((double)CONCAT44(0x43300000,uVar10) - DOUBLE_8043d248))
                            - dVar11);
    dVar13 = (double)(float)(dVar12 / (double)(*(float *)(iVar4 + 0x18) - fVar2));
    uStack_64 = uVar10;
    uStack_54 = uVar10;
    uStack_4c = uVar10;
    gnt4_GXSetViewport_bl
              ((double)*(float *)(iVar4 + 0xc),dVar11,
               (double)(float)((double)*(float *)(iVar4 + 0x10) - (double)*(float *)(iVar4 + 0xc)),
               dVar12,(double)FLOAT_8043d240,(double)FLOAT_8043d244);
    bVar1 = *(byte *)(iVar4 + 0x50);
    if (bVar1 == 2) {
      dVar11 = (double)*(float *)(iVar4 + 0x44);
      unaff_r31 = 0;
      gnt4_C_MTXFrustum_bl
                ((double)(float)(dVar13 * (double)(float)((double)*(float *)(iVar4 + 0x40) - dVar11)
                                + dVar11),dVar11,(double)*(float *)(iVar4 + 0x48),
                 (double)*(float *)(iVar4 + 0x4c),(double)*(float *)(iVar4 + 0x38),
                 (double)*(float *)(iVar4 + 0x3c),afStack_c8);
    }
    else if (bVar1 < 2) {
      if (bVar1 != 0) {
        unaff_r31 = 0;
        dVar11 = gnt4_tan_bl((double)(float)(DOUBLE_8043d258 *
                                            DOUBLE_8043d238 * (double)*(float *)(iVar4 + 0x40)));
        dVar11 = (double)(float)((double)*(float *)(iVar4 + 0x38) * (double)(float)dVar11);
        dVar12 = (double)(float)(dVar11 * (double)*(float *)(iVar4 + 0x44));
        gnt4_C_MTXFrustum_bl
                  ((double)(float)(dVar11 * (double)(float)((double)FLOAT_8043d260 * dVar13 +
                                                           (double)FLOAT_8043d264)),-dVar11,-dVar12,
                   dVar12,(double)*(float *)(iVar4 + 0x38),(double)*(float *)(iVar4 + 0x3c),
                   afStack_c8);
      }
    }
    else if (bVar1 < 4) {
      dVar11 = (double)*(float *)(iVar4 + 0x44);
      unaff_r31 = 1;
      gnt4_C_MTXOrtho_bl((double)(float)(dVar13 * (double)(float)((double)*(float *)(iVar4 + 0x40) -
                                                                 dVar11) + dVar11),dVar11,
                         (double)*(float *)(iVar4 + 0x48),(double)*(float *)(iVar4 + 0x4c),
                         (double)*(float *)(iVar4 + 0x38),(double)*(float *)(iVar4 + 0x3c),
                         afStack_c8);
    }
    gnt4_GXSetProjection_bl(afStack_c8,unaff_r31);
  }
  gnt4__restgpr_26_bl();
  return;
}



// ==== 80246ab8  gnt4-HSD_CObjSetupViewingMtx-bl ====

void gnt4_HSD_CObjSetupViewingMtx_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  float afStack_38 [3];
  float local_2c;
  float local_28;
  float local_24;
  float afStack_20 [7];
  
  if (((*(uint *)(param_9 + 8) & 2) == 0) &&
     (iVar1 = gnt4_HSD_CObjMtxIsDirty_bl(param_9), iVar1 != 0)) {
    dVar2 = (double)gnt4_HSD_CObjGetEyePosition_bl
                              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               param_9,afStack_20,param_11,param_12,param_13,param_14,param_15,
                               param_16);
    iVar1 = gnt4_HSD_CObjGetUpVector_bl
                      (dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       &local_2c,param_11,param_12,param_13,param_14,param_15,param_16);
    if (iVar1 == 0) {
      dVar2 = (double)FLOAT_8043d240;
      local_2c = FLOAT_8043d240;
      local_28 = FLOAT_8043d244;
      local_24 = FLOAT_8043d240;
    }
    gnt4_HSD_CObjGetInterest_bl
              (dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,afStack_38,
               param_11,param_12,param_13,param_14,param_15,param_16);
    gnt4_C_MTXLookAt_bl((float *)(param_9 + 0x54),afStack_20,&local_2c,afStack_38);
    *(uint *)(*(int *)(param_9 + 0x24) + 8) = *(uint *)(*(int *)(param_9 + 0x24) + 8) & 0xfffffffd;
    *(uint *)(*(int *)(param_9 + 0x28) + 8) = *(uint *)(*(int *)(param_9 + 0x28) + 8) & 0xfffffffd;
    gnt4_HSD_CObjClearFlags_bl(param_9,0x40000000);
    gnt4_HSD_CObjSetFlags_bl(param_9,0x80000000);
  }
  return;
}



// ==== 80246b84  gnt4-HSD_CObjSetCurrent-bl ====

/* WARNING: Removing unreachable block (ram,0x80247068) */
/* WARNING: Removing unreachable block (ram,0x80247060) */
/* WARNING: Removing unreachable block (ram,0x80247058) */
/* WARNING: Removing unreachable block (ram,0x80247050) */
/* WARNING: Removing unreachable block (ram,0x80247048) */
/* WARNING: Removing unreachable block (ram,0x80247040) */
/* WARNING: Removing unreachable block (ram,0x80246bbc) */
/* WARNING: Removing unreachable block (ram,0x80246bb4) */
/* WARNING: Removing unreachable block (ram,0x80246bac) */
/* WARNING: Removing unreachable block (ram,0x80246ba4) */
/* WARNING: Removing unreachable block (ram,0x80246b9c) */
/* WARNING: Removing unreachable block (ram,0x80246b94) */

void gnt4_HSD_CObjSetCurrent_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
               undefined *param_11,int param_12,uint param_13,undefined4 *param_14,
               undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  ushort uVar5;
  int iVar4;
  int unaff_r28;
  int unaff_r31;
  double dVar6;
  undefined8 uVar7;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  double in_f26;
  double in_f27;
  double dVar8;
  double in_f28;
  double dVar9;
  double in_f29;
  double in_f30;
  double in_f31;
  double dVar10;
  double in_ps26_1;
  double in_ps27_1;
  double in_ps28_1;
  double in_ps29_1;
  double in_ps30_1;
  double in_ps31_1;
  float afStack_148 [3];
  float local_13c;
  float local_138;
  float local_134;
  float afStack_130 [3];
  float afStack_124 [16];
  float afStack_e4 [17];
  undefined4 local_a0;
  uint uStack_9c;
  undefined4 local_98;
  uint uStack_94;
  undefined4 local_90;
  uint uStack_8c;
  undefined4 local_88;
  uint uStack_84;
  float local_58;
  float fStack_54;
  float local_48;
  float fStack_44;
  float local_38;
  float fStack_34;
  float local_28;
  float fStack_24;
  float local_18;
  float fStack_14;
  float local_8;
  float fStack_4;
  
  local_8 = (float)in_f31;
  fStack_4 = (float)in_ps31_1;
  local_18 = (float)in_f30;
  fStack_14 = (float)in_ps30_1;
  local_28 = (float)in_f29;
  fStack_24 = (float)in_ps29_1;
  local_38 = (float)in_f28;
  fStack_34 = (float)in_ps28_1;
  local_48 = (float)in_f27;
  fStack_44 = (float)in_ps27_1;
  local_58 = (float)in_f26;
  fStack_54 = (float)in_ps26_1;
  iVar2 = gnt4__savegpr_27_bl();
  if (iVar2 == 0) goto LAB_80247040;
  iVar3 = gnt4_HSD_SetCurrentRenderPass_bl();
  dVar6 = (double)gnt4__HSD_ZListClear_bl();
  DAT_8043695c = iVar2;
  if (iVar3 == 2) {
    iVar3 = gnt4_setupBottomHalfCamera_bl();
    uVar7 = extraout_f1_00;
  }
  else if (iVar3 < 2) {
    if (iVar3 == 0) {
      param_14 = &DAT_803f8e80;
      param_13 = (uint)DAT_803f8e84._0_2_;
      uStack_94 = DAT_80435e90 ^ 0x80000000;
      uStack_8c = (uint)DAT_803f8e84._2_2_;
      uStack_84 = DAT_80435e94 ^ 0x80000000;
      local_a0 = 0x43300000;
      local_98 = 0x43300000;
      local_90 = 0x43300000;
      dVar10 = ((double)CONCAT44(0x43300000,param_13) - DOUBLE_8043d248) /
               ((double)CONCAT44(0x43300000,uStack_94) - DOUBLE_8043d250);
      local_88 = 0x43300000;
      dVar9 = (double)(float)((double)*(float *)(iVar2 + 0xc) * dVar10);
      dVar6 = ((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_8043d248) /
              ((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_8043d250);
      dVar8 = (double)(float)((double)*(float *)(iVar2 + 0x14) * dVar6);
      param_3 = (double)(float)((double)(float)((double)*(float *)(iVar2 + 0x10) * dVar10) - dVar9);
      param_4 = (double)(float)((double)(float)((double)*(float *)(iVar2 + 0x18) * dVar6) - dVar8);
      param_7 = DOUBLE_8043d248;
      uStack_9c = param_13;
      if (DAT_803f8e98 == '\0') {
        param_5 = (double)FLOAT_8043d240;
        param_6 = (double)FLOAT_8043d244;
        gnt4_GXSetViewport_bl(dVar9,dVar8,param_3,param_4,param_5,param_6);
      }
      else {
        uVar5 = gnt4_VIGetNextField_bl();
        param_5 = (double)FLOAT_8043d240;
        param_6 = (double)FLOAT_8043d244;
        gnt4_GXSetViewportJitter_bl(dVar9,dVar8,param_3,param_4,param_5,param_6,(uint)uVar5);
      }
      uStack_8c = (uint)*(ushort *)(iVar2 + 0x20);
      uStack_94 = (uint)*(ushort *)(iVar2 + 0x22);
      uStack_84 = (uint)*(ushort *)(iVar2 + 0x1c);
      local_90 = 0x43300000;
      local_98 = 0x43300000;
      local_88 = 0x43300000;
      dVar9 = (double)(float)(((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_8043d248) * dVar6);
      dVar8 = (double)(float)(((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_8043d248) * dVar10);
      param_2 = DOUBLE_8043d248;
      param_12 = gnt4___cvt_fp2unsigned_bl
                           ((double)(float)((double)(float)(((double)CONCAT44(0x43300000,uStack_94)
                                                            - DOUBLE_8043d248) * dVar6) - dVar9));
      uStack_9c = (uint)*(ushort *)(iVar2 + 0x1e);
      local_a0 = 0x43300000;
      param_11 = (undefined *)
                 gnt4___cvt_fp2unsigned_bl
                           ((double)(float)((double)(float)(((double)CONCAT44(0x43300000,uStack_9c)
                                                            - DOUBLE_8043d248) * dVar10) - dVar8));
      iVar3 = gnt4___cvt_fp2unsigned_bl(dVar9);
      iVar4 = gnt4___cvt_fp2unsigned_bl(dVar8);
      gnt4_GXSetScissor_bl(iVar4,iVar3,(int)param_11,param_12);
      bVar1 = *(byte *)(iVar2 + 0x50);
      if (bVar1 == 2) {
        param_2 = (double)*(float *)(iVar2 + 0x44);
        unaff_r31 = 0;
        param_3 = (double)*(float *)(iVar2 + 0x48);
        param_4 = (double)*(float *)(iVar2 + 0x4c);
        param_5 = (double)*(float *)(iVar2 + 0x38);
        param_6 = (double)*(float *)(iVar2 + 0x3c);
        gnt4_C_MTXFrustum_bl
                  ((double)*(float *)(iVar2 + 0x40),param_2,param_3,param_4,param_5,param_6,
                   afStack_124);
      }
      else if (bVar1 < 2) {
        if (bVar1 != 0) {
          param_2 = (double)*(float *)(iVar2 + 0x44);
          unaff_r31 = 0;
          param_3 = (double)*(float *)(iVar2 + 0x38);
          param_4 = (double)*(float *)(iVar2 + 0x3c);
          gnt4_C_MTXPerspective_bl
                    ((double)*(float *)(iVar2 + 0x40),param_2,param_3,param_4,afStack_124);
        }
      }
      else if (bVar1 < 4) {
        param_2 = (double)*(float *)(iVar2 + 0x44);
        unaff_r31 = 1;
        param_3 = (double)*(float *)(iVar2 + 0x48);
        param_4 = (double)*(float *)(iVar2 + 0x4c);
        param_5 = (double)*(float *)(iVar2 + 0x38);
        param_6 = (double)*(float *)(iVar2 + 0x3c);
        gnt4_C_MTXOrtho_bl((double)*(float *)(iVar2 + 0x40),param_2,param_3,param_4,param_5,param_6,
                           afStack_124);
      }
      uVar7 = gnt4_GXSetProjection_bl(afStack_124,unaff_r31);
      iVar3 = 1;
    }
    else {
      if (iVar3 < 0) goto LAB_80246f68;
      iVar3 = gnt4_setupTopHalfCamera_bl();
      uVar7 = extraout_f1;
    }
  }
  else {
    if (3 < iVar3) {
LAB_80246f68:
      gnt4_HSD_Panic_bl(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e98,
                        0x297,s_unkown_type_of_render_pass__803ac7c8,param_12,param_13,param_14,
                        param_15,param_16);
      goto LAB_80247040;
    }
    param_2 = (double)*(float *)(iVar2 + 0x14);
    param_4 = (double)(float)((double)*(float *)(iVar2 + 0x18) - param_2);
    param_5 = (double)FLOAT_8043d240;
    param_3 = (double)(float)((double)*(float *)(iVar2 + 0x10) - (double)*(float *)(iVar2 + 0xc));
    param_6 = (double)FLOAT_8043d244;
    gnt4_GXSetViewport_bl((double)*(float *)(iVar2 + 0xc),param_2,param_3,param_4,param_5,param_6);
    param_12 = (uint)*(ushort *)(iVar2 + 0x22) - (uint)*(ushort *)(iVar2 + 0x20);
    param_11 = (undefined *)((uint)*(ushort *)(iVar2 + 0x1e) - (uint)*(ushort *)(iVar2 + 0x1c));
    gnt4_GXSetScissor_bl
              ((uint)*(ushort *)(iVar2 + 0x1c),(uint)*(ushort *)(iVar2 + 0x20),(int)param_11,
               param_12);
    bVar1 = *(byte *)(iVar2 + 0x50);
    if (bVar1 == 2) {
      param_2 = (double)*(float *)(iVar2 + 0x44);
      unaff_r28 = 0;
      param_3 = (double)*(float *)(iVar2 + 0x48);
      param_4 = (double)*(float *)(iVar2 + 0x4c);
      param_5 = (double)*(float *)(iVar2 + 0x38);
      param_6 = (double)*(float *)(iVar2 + 0x3c);
      gnt4_C_MTXFrustum_bl
                ((double)*(float *)(iVar2 + 0x40),param_2,param_3,param_4,param_5,param_6,afStack_e4
                );
    }
    else if (bVar1 < 2) {
      if (bVar1 != 0) {
        param_2 = (double)*(float *)(iVar2 + 0x44);
        unaff_r28 = 0;
        param_3 = (double)*(float *)(iVar2 + 0x38);
        param_4 = (double)*(float *)(iVar2 + 0x3c);
        gnt4_C_MTXPerspective_bl
                  ((double)*(float *)(iVar2 + 0x40),param_2,param_3,param_4,afStack_e4);
      }
    }
    else if (bVar1 < 4) {
      param_2 = (double)*(float *)(iVar2 + 0x44);
      unaff_r28 = 1;
      param_3 = (double)*(float *)(iVar2 + 0x48);
      param_4 = (double)*(float *)(iVar2 + 0x4c);
      param_5 = (double)*(float *)(iVar2 + 0x38);
      param_6 = (double)*(float *)(iVar2 + 0x3c);
      gnt4_C_MTXOrtho_bl((double)*(float *)(iVar2 + 0x40),param_2,param_3,param_4,param_5,param_6,
                         afStack_e4);
    }
    uVar7 = gnt4_GXSetProjection_bl(afStack_e4,unaff_r28);
    iVar3 = 1;
  }
  if (((iVar3 != 0) && ((*(uint *)(iVar2 + 8) & 2) == 0)) &&
     (iVar3 = gnt4_HSD_CObjMtxIsDirty_bl(iVar2), iVar3 != 0)) {
    dVar6 = (double)gnt4_HSD_CObjGetEyePosition_bl
                              (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                               afStack_148,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar3 = gnt4_HSD_CObjGetUpVector_bl
                      (dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                       &local_13c,param_11,param_12,param_13,param_14,param_15,param_16);
    if (iVar3 == 0) {
      dVar6 = (double)FLOAT_8043d240;
      local_13c = FLOAT_8043d240;
      local_138 = FLOAT_8043d244;
      local_134 = FLOAT_8043d240;
    }
    gnt4_HSD_CObjGetInterest_bl
              (dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,afStack_130,
               param_11,param_12,param_13,param_14,param_15,param_16);
    gnt4_C_MTXLookAt_bl((float *)(iVar2 + 0x54),afStack_148,&local_13c,afStack_130);
    *(uint *)(*(int *)(iVar2 + 0x24) + 8) = *(uint *)(*(int *)(iVar2 + 0x24) + 8) & 0xfffffffd;
    *(uint *)(*(int *)(iVar2 + 0x28) + 8) = *(uint *)(*(int *)(iVar2 + 0x28) + 8) & 0xfffffffd;
    gnt4_HSD_CObjClearFlags_bl(iVar2,0x40000000);
    gnt4_HSD_CObjSetFlags_bl(iVar2,0x80000000);
  }
LAB_80247040:
  gnt4__restgpr_27_bl();
  return;
}



// ==== 80247088  gnt4-HSD_CObjEndCurrent-bl ====

void gnt4_HSD_CObjEndCurrent_bl(void)

{
  gnt4__HSD_ZListSort_bl();
  gnt4__HSD_ZListDisp_bl();
  return;
}



// ==== 802470ac  gnt4-HSD_CObjGetInterestWObj-bl ====

undefined4
gnt4_HSD_CObjGetInterestWObj_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  if (param_9 == 0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e98,
                     700,&DAT_80435ea0,param_12,param_13,param_14,param_15,param_16);
  }
  return *(undefined4 *)(param_9 + 0x28);
}



// ==== 802470ec  gnt4-HSD_CObjGetEyePositionWObj-bl ====

undefined4
gnt4_HSD_CObjGetEyePositionWObj_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  if (param_9 == 0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e98,
                     0x2d4,&DAT_80435ea0,param_12,param_13,param_14,param_15,param_16);
  }
  return *(undefined4 *)(param_9 + 0x24);
}



// ==== 8024712c  gnt4-HSD_CObjGetInterest-bl ====

void gnt4_HSD_CObjGetInterest_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  if (param_9 == 0) {
    uVar1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80435e98,0x2ec,&DAT_80435ea0,param_12,param_13,param_14,param_15,
                             param_16);
    param_11 = &DAT_80435ea0;
    param_1 = gnt4___assert_bl(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80435e98,700,&DAT_80435ea0,param_12,param_13,param_14,param_15,
                               param_16);
  }
  gnt4_HSD_WObjGetPosition_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
             *(int *)(param_9 + 0x28),param_10,param_11,param_12,param_13,param_14,param_15,param_16
            );
  return;
}



// ==== 80247198  gnt4-HSD_CObjSetInterest-bl ====

void gnt4_HSD_CObjSetInterest_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  if (param_9 == 0) {
    uVar1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80435e98,0x2f8,&DAT_80435ea0,param_12,param_13,param_14,param_15,
                             param_16);
    gnt4___assert_bl(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e98,700
                     ,&DAT_80435ea0,param_12,param_13,param_14,param_15,param_16);
  }
  gnt4_HSD_WObjSetPosition_bl(*(int *)(param_9 + 0x28),param_10);
  return;
}



// ==== 80247204  gnt4-HSD_CObjGetEyePosition-bl ====

void gnt4_HSD_CObjGetEyePosition_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  if (param_9 == 0) {
    uVar1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80435e98,0x304,&DAT_80435ea0,param_12,param_13,param_14,param_15,
                             param_16);
    param_11 = &DAT_80435ea0;
    param_1 = gnt4___assert_bl(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80435e98,0x2d4,&DAT_80435ea0,param_12,param_13,param_14,param_15
                               ,param_16);
  }
  gnt4_HSD_WObjGetPosition_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
             *(int *)(param_9 + 0x24),param_10,param_11,param_12,param_13,param_14,param_15,param_16
            );
  return;
}



// ==== 80247270  gnt4-HSD_CObjSetEyePosition-bl ====

void gnt4_HSD_CObjSetEyePosition_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  if (param_9 == 0) {
    uVar1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80435e98,0x310,&DAT_80435ea0,param_12,param_13,param_14,param_15,
                             param_16);
    gnt4___assert_bl(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e98,
                     0x2d4,&DAT_80435ea0,param_12,param_13,param_14,param_15,param_16);
  }
  gnt4_HSD_WObjSetPosition_bl(*(int *)(param_9 + 0x24),param_10);
  return;
}



// ==== 802472dc  gnt4-upvec2roll-bl ====

double gnt4_upvec2roll_bl(undefined8 param_1,double param_2,double param_3,double param_4,
                         double param_5,double param_6,double param_7,double param_8,int param_9,
                         float *param_10,undefined *param_11,undefined4 param_12,undefined4 param_13
                         ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  double dVar4;
  float afStack_68 [3];
  float afStack_5c [3];
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float afStack_38 [12];
  
  if (((param_9 == 0) || (*(int *)(param_9 + 0x24) == 0)) || (*(int *)(param_9 + 0x28) == 0)) {
    uVar1 = 0;
  }
  else {
    if (param_9 == 0) {
      uVar3 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80435e98,0x304,&DAT_80435ea0,param_12,param_13,param_14,param_15
                               ,param_16);
      param_11 = &DAT_80435ea0;
      param_1 = gnt4___assert_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435e98,0x2d4,&DAT_80435ea0,param_12,param_13,param_14,
                                 param_15,param_16);
    }
    uVar3 = gnt4_HSD_WObjGetPosition_bl
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(param_9 + 0x24),afStack_68,param_11,param_12,param_13,param_14,
                       param_15,param_16);
    if (param_9 == 0) {
      uVar3 = gnt4___assert_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80435e98,0x2ec,&DAT_80435ea0,param_12,param_13,param_14,param_15
                               ,param_16);
      param_11 = &DAT_80435ea0;
      uVar3 = gnt4___assert_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80435e98,700,&DAT_80435ea0,param_12,param_13,param_14,param_15,
                               param_16);
    }
    gnt4_HSD_WObjGetPosition_bl
              (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(int *)(param_9 + 0x28),afStack_5c,param_11,param_12,param_13,param_14,param_15,
               param_16);
    gnt4_PSVECSubtract_bl(afStack_5c,afStack_68,&local_50);
    if (((DOUBLE_8043d268 < ABS((double)local_50)) || (DOUBLE_8043d268 < ABS((double)local_4c))) ||
       (DOUBLE_8043d268 < ABS((double)local_48))) {
      gnt4_PSVECNormalize_bl(&local_50,&local_50);
      uVar2 = 0;
    }
    else {
      uVar2 = 0xffffffff;
    }
    uVar1 = countLeadingZeros(uVar2);
    uVar1 = uVar1 >> 5;
  }
  if (uVar1 == 0) {
    dVar4 = (double)FLOAT_8043d240;
  }
  else {
    dVar4 = gnt4_PSQUATDotProduct_bl(param_10,&local_50);
    if (FLOAT_8043d270 <= FLOAT_8043d244 - (float)ABS(dVar4)) {
      gnt4_C_MTXLookAt_bl(afStack_38,(float *)&DAT_803ac808,(float *)&DAT_803ac814,&local_50);
      gnt4_PSMTXMultVecSR_bl(afStack_38,param_10,&local_44);
      if ((double)FLOAT_8043d240 == (double)local_40) {
        if (-(double)local_44 < (double)FLOAT_8043d240) {
          dVar4 = (double)FLOAT_8043d278;
        }
        else {
          dVar4 = (double)FLOAT_8043d274;
        }
      }
      else {
        dVar4 = (double)gnt4_atan2_bl(-(double)local_44,(double)local_40);
        dVar4 = (double)(float)dVar4;
      }
    }
    else {
      dVar4 = (double)FLOAT_8043d240;
    }
  }
  return dVar4;
}



// ==== 802474c4  gnt4-roll2upvec-bl ====

/* WARNING: Removing unreachable block (ram,0x80247788) */
/* WARNING: Removing unreachable block (ram,0x802474d4) */

undefined4
gnt4_roll2upvec_bl(double param_1,double param_2,double param_3,double param_4,double param_5,
                  double param_6,double param_7,double param_8,int param_9,float *param_10,
                  undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                  undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  double dVar4;
  double dVar5;
  float afStack_90 [3];
  float afStack_84 [3];
  float afStack_78 [3];
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float afStack_54 [15];
  
  if (((param_9 == 0) || (*(int *)(param_9 + 0x24) == 0)) || (*(int *)(param_9 + 0x28) == 0)) {
    uVar1 = 0;
  }
  else {
    dVar5 = param_1;
    if (param_9 == 0) {
      uVar3 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80435e98,0x304,&DAT_80435ea0,param_12,param_13,param_14,param_15
                               ,param_16);
      param_11 = &DAT_80435ea0;
      dVar5 = param_1;
      param_1 = (double)gnt4___assert_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,
                                         param_8,&DAT_80435e98,0x2d4,&DAT_80435ea0,param_12,param_13
                                         ,param_14,param_15,param_16);
    }
    uVar3 = gnt4_HSD_WObjGetPosition_bl
                      (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(param_9 + 0x24),afStack_90,param_11,param_12,param_13,param_14,
                       param_15,param_16);
    param_1 = dVar5;
    if (param_9 == 0) {
      uVar3 = gnt4___assert_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80435e98,0x2ec,&DAT_80435ea0,param_12,param_13,param_14,param_15
                               ,param_16);
      param_11 = &DAT_80435ea0;
      uVar3 = gnt4___assert_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80435e98,700,&DAT_80435ea0,param_12,param_13,param_14,param_15,
                               param_16);
      param_1 = dVar5;
    }
    gnt4_HSD_WObjGetPosition_bl
              (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
               *(int *)(param_9 + 0x28),afStack_84,param_11,param_12,param_13,param_14,param_15,
               param_16);
    gnt4_PSVECSubtract_bl(afStack_84,afStack_90,&local_60);
    if (((DOUBLE_8043d268 < ABS((double)local_60)) || (DOUBLE_8043d268 < ABS((double)local_5c))) ||
       (DOUBLE_8043d268 < ABS((double)local_58))) {
      gnt4_PSVECNormalize_bl(&local_60,&local_60);
      uVar2 = 0;
    }
    else {
      uVar2 = 0xffffffff;
    }
    uVar1 = countLeadingZeros(uVar2);
    uVar1 = uVar1 >> 5;
  }
  if (uVar1 == 0) {
    uVar2 = 0;
  }
  else {
    if (DOUBLE_8043d288 <= DOUBLE_8043d280 - (double)ABS(local_5c)) {
      dVar5 = (double)(local_60 * local_60 + local_58 * local_58);
      if ((double)FLOAT_8043d240 < dVar5) {
        dVar4 = 1.0 / SQRT(dVar5);
        dVar4 = DOUBLE_8043d238 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_8043d290);
        dVar4 = DOUBLE_8043d238 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_8043d290);
        dVar5 = (double)(float)(dVar5 * DOUBLE_8043d238 * dVar4 *
                                        -(dVar5 * dVar4 * dVar4 - DOUBLE_8043d290));
      }
      local_68 = (float)dVar5;
      local_64 = -local_5c / (float)dVar5;
      local_6c = local_60 * local_64;
    }
    else {
      dVar5 = (double)(local_5c * local_5c + local_58 * local_58);
      if ((double)FLOAT_8043d240 < dVar5) {
        dVar4 = 1.0 / SQRT(dVar5);
        dVar4 = DOUBLE_8043d238 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_8043d290);
        dVar4 = DOUBLE_8043d238 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_8043d290);
        dVar5 = (double)(float)(dVar5 * DOUBLE_8043d238 * dVar4 *
                                        -(dVar5 * dVar4 * dVar4 - DOUBLE_8043d290));
      }
      local_6c = (float)dVar5;
      local_64 = -local_60 / (float)dVar5;
      local_68 = local_5c * local_64;
    }
    local_64 = local_58 * local_64;
    gnt4_PSMTXRotAxisRad_bl(-param_1,afStack_54,&local_60);
    gnt4_PSMTXMultVecSR_bl(afStack_54,&local_6c,afStack_78);
    gnt4_PSVECNormalize_bl(afStack_78,param_10);
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 802477a8  gnt4-HSD_CObjGetUpVector-bl ====

undefined4
gnt4_HSD_CObjGetUpVector_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,int param_9,float *param_10,
          undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  
  if ((param_9 != 0) && (param_10 != (float *)0x0)) {
    if ((*(uint *)(param_9 + 8) & 1) != 0) {
      fVar1 = *(float *)(param_9 + 0x30);
      *param_10 = *(float *)(param_9 + 0x2c);
      param_10[1] = fVar1;
      param_10[2] = *(float *)(param_9 + 0x34);
      return 1;
    }
    uVar2 = gnt4_roll2upvec_bl((double)*(float *)(param_9 + 0x2c),param_2,param_3,param_4,param_5,
                               param_6,param_7,param_8,param_9,param_10,param_11,param_12,param_13,
                               param_14,param_15,param_16);
    return uVar2;
  }
  return 0;
}



// ==== 80247810  gnt4-HSD_CObjSetUpVector-bl ====

void gnt4_HSD_CObjSetUpVector_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,float *param_10,
               float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  float *extraout_r4;
  float *extraout_r4_00;
  float *extraout_r4_01;
  float *pfVar4;
  float *extraout_r4_02;
  float *extraout_r4_03;
  undefined8 uVar5;
  double dVar6;
  float afStack_88 [3];
  float afStack_7c [3];
  float local_70;
  float local_6c;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [16];
  
  if ((param_9 != 0) && (param_10 != (float *)0x0)) {
    if ((*(uint *)(param_9 + 8) & 1) == 0) {
      if (((param_9 == 0) || (*(int *)(param_9 + 0x24) == 0)) || (*(int *)(param_9 + 0x28) == 0)) {
        uVar2 = 0;
        pfVar4 = param_10;
      }
      else {
        if (param_9 == 0) {
          uVar5 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_80435e98,0x304,&DAT_80435ea0,param_12,param_13,param_14,
                                   param_15,param_16);
          param_11 = (float *)&DAT_80435ea0;
          param_1 = (double)gnt4___assert_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,
                                             param_8,&DAT_80435e98,0x2d4,&DAT_80435ea0,param_12,
                                             param_13,param_14,param_15,param_16);
        }
        uVar5 = gnt4_HSD_WObjGetPosition_bl
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(param_9 + 0x24),afStack_88,(undefined *)param_11,param_12,
                           param_13,param_14,param_15,param_16);
        if (param_9 == 0) {
          uVar5 = gnt4___assert_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_80435e98,0x2ec,&DAT_80435ea0,param_12,param_13,param_14,
                                   param_15,param_16);
          param_11 = (float *)&DAT_80435ea0;
          uVar5 = gnt4___assert_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_80435e98,700,&DAT_80435ea0,param_12,param_13,param_14,
                                   param_15,param_16);
        }
        gnt4_HSD_WObjGetPosition_bl
                  (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                   *(int *)(param_9 + 0x28),afStack_7c,(undefined *)param_11,param_12,param_13,
                   param_14,param_15,param_16);
        param_11 = &local_64;
        gnt4_PSVECSubtract_bl(afStack_7c,afStack_88,param_11);
        if (((DOUBLE_8043d268 < ABS((double)local_64)) || (DOUBLE_8043d268 < ABS((double)local_60)))
           || (DOUBLE_8043d268 < ABS((double)local_5c))) {
          gnt4_PSVECNormalize_bl(&local_64,&local_64);
          uVar3 = 0;
          pfVar4 = extraout_r4_01;
        }
        else {
          uVar3 = 0xffffffff;
          pfVar4 = extraout_r4_00;
        }
        uVar2 = countLeadingZeros(uVar3);
        uVar2 = uVar2 >> 5;
      }
      if (uVar2 == 0) {
        dVar6 = (double)FLOAT_8043d240;
      }
      else {
        pfVar4 = &local_64;
        dVar6 = gnt4_PSQUATDotProduct_bl(param_10,pfVar4);
        param_2 = (double)FLOAT_8043d244;
        if (FLOAT_8043d270 <= (float)(param_2 - (double)(float)ABS(dVar6))) {
          param_12 = &local_64;
          gnt4_C_MTXLookAt_bl(afStack_4c,(float *)&DAT_803ac808,(float *)&DAT_803ac814,param_12);
          param_11 = &local_70;
          gnt4_PSMTXMultVecSR_bl(afStack_4c,param_10,param_11);
          param_2 = (double)local_6c;
          if ((double)FLOAT_8043d240 == param_2) {
            pfVar4 = extraout_r4_02;
            if (-(double)local_70 < (double)FLOAT_8043d240) {
              dVar6 = (double)FLOAT_8043d278;
            }
            else {
              dVar6 = (double)FLOAT_8043d274;
            }
          }
          else {
            dVar6 = (double)gnt4_atan2_bl(-(double)local_70,param_2);
            dVar6 = (double)(float)dVar6;
            pfVar4 = extraout_r4_03;
          }
        }
        else {
          dVar6 = (double)FLOAT_8043d240;
        }
      }
      gnt4_HSD_CObjSetRoll_bl
                (dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,pfVar4,
                 param_11,param_12,param_13,param_14,param_15,param_16);
    }
    else {
      if (param_10 == (float *)0x0) {
        iVar1 = -1;
      }
      else if (((DOUBLE_8043d268 < ABS((double)*param_10)) ||
               (DOUBLE_8043d268 < ABS((double)param_10[1]))) ||
              (DOUBLE_8043d268 < ABS((double)param_10[2]))) {
        param_1 = (double)gnt4_PSVECNormalize_bl(param_10,&local_58);
        iVar1 = 0;
        param_10 = extraout_r4;
      }
      else {
        iVar1 = -1;
        param_1 = DOUBLE_8043d268;
      }
      if (iVar1 != 0) {
        uVar5 = gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 s_illegal_up_vector__803ac820,param_10,param_11,param_12,param_13,
                                 param_14,param_15,param_16);
        gnt4___assert_bl(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e98
                         ,0x3d0,&DAT_80435ea8,param_12,param_13,param_14,param_15,param_16);
      }
      if (((*(float *)(param_9 + 0x2c) != local_58) || (*(float *)(param_9 + 0x30) != local_54)) ||
         (*(float *)(param_9 + 0x34) != local_50)) {
        gnt4_HSD_CObjSetMtxDirty_bl(param_9);
        *(float *)(param_9 + 0x2c) = local_58;
        *(float *)(param_9 + 0x30) = local_54;
        *(float *)(param_9 + 0x34) = local_50;
      }
    }
  }
  return;
}



// ==== 80247b0c  gnt4-HSD_CObjSetMtxDirty-bl ====

void gnt4_HSD_CObjSetMtxDirty_bl(int param_1)

{
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | 0xc0000000;
  return;
}



// ==== 80247b1c  gnt4-HSD_CObjMtxIsDirty-bl ====

undefined4 gnt4_HSD_CObjMtxIsDirty_bl(int param_1)

{
  if (((*(uint *)(param_1 + 8) & 0x40000000) == 0) &&
     ((*(int *)(param_1 + 0x24) == 0 || ((*(uint *)(*(int *)(param_1 + 0x24) + 8) & 2) == 0)))) {
    if (*(int *)(param_1 + 0x28) == 0) {
      return 0;
    }
    if ((*(uint *)(*(int *)(param_1 + 0x28) + 8) & 2) == 0) {
      return 0;
    }
  }
  return 1;
}



// ==== 80247b68  gnt4-HSD_CObjGetViewingMtx-bl ====

void gnt4_HSD_CObjGetViewingMtx_bl
               (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,float *param_10,
               undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  
  pfVar1 = (float *)gnt4_HSD_CObjGetViewingMtxPtr_bl
                              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               param_9,param_10,param_11,param_12,param_13,param_14,param_15,
                               param_16);
  gnt4_PSMTXCopy_bl(pfVar1,param_10);
  return;
}



// ==== 80247b9c  gnt4-HSD_CObjGetInvViewingMtxPtrDirect-bl ====

undefined4
gnt4_HSD_CObjGetInvViewingMtxPtrDirect_bl
          (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
          double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
          undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
          undefined4 param_15,undefined4 param_16)

{
  undefined4 *puVar1;
  
  if ((*(uint *)(param_9 + 8) & 0x80000000) != 0) {
    if (*(int *)(param_9 + 0x88) == 0) {
      puVar1 = gnt4_HSD_MtxAlloc_bl
                         (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          param_10,param_11,param_12,param_13,param_14,param_15,param_16);
      *(undefined4 **)(param_9 + 0x88) = puVar1;
    }
    gnt4_PSMTXInverse_bl((float *)(param_9 + 0x54),*(float **)(param_9 + 0x88));
    gnt4_HSD_CObjClearFlags_bl(param_9,0x80000000);
  }
  return *(undefined4 *)(param_9 + 0x88);
}



// ==== 80247c00  gnt4-HSD_CObjGetViewingMtxPtr-bl ====

int gnt4_HSD_CObjGetViewingMtxPtr_bl
              (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
              double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
              undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
              undefined4 param_15,undefined4 param_16)

{
  gnt4_HSD_CObjSetupViewingMtx_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
             param_11,param_12,param_13,param_14,param_15,param_16);
  return param_9 + 0x54;
}



// ==== 80247c30  gnt4-HSD_CObjSetRoll-bl ====

/* WARNING: Removing unreachable block (ram,0x8024803c) */
/* WARNING: Removing unreachable block (ram,0x80247c40) */

void gnt4_HSD_CObjSetRoll_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  double dVar1;
  double dVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  undefined4 extraout_r4_05;
  double dVar6;
  double dVar7;
  undefined8 uVar8;
  float afStack_b0 [3];
  float local_a4;
  float local_a0;
  float local_9c;
  float afStack_98 [3];
  float afStack_8c [3];
  float local_80;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float afStack_68 [3];
  float local_5c;
  float local_58;
  float local_54;
  float afStack_50 [15];
  
  if (param_9 != 0) {
    if ((*(uint *)(param_9 + 8) & 1) == 0) {
      if ((double)*(float *)(param_9 + 0x2c) != param_1) {
        *(uint *)(param_9 + 8) = *(uint *)(param_9 + 8) | 0xc0000000;
      }
      *(float *)(param_9 + 0x2c) = (float)param_1;
    }
    else {
      dVar7 = param_1;
      if (((param_9 == 0) || (*(int *)(param_9 + 0x24) == 0)) || (*(int *)(param_9 + 0x28) == 0)) {
        uVar3 = 0;
      }
      else {
        if (param_9 == 0) {
          param_11 = (float *)&DAT_80435ea0;
          param_1 = (double)gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7
                                             ,param_8,&DAT_80435e98,0x304,&DAT_80435ea0,param_12,
                                             param_13,param_14,param_15,param_16);
          param_10 = extraout_r4;
        }
        iVar5 = gnt4_HSD_CObjGetEyePositionWObj_bl
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                           param_10,param_11,param_12,param_13,param_14,param_15,param_16);
        uVar8 = gnt4_HSD_WObjGetPosition_bl
                          (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                           afStack_98,(undefined *)param_11,param_12,param_13,param_14,param_15,
                           param_16);
        uVar4 = extraout_r4_00;
        if (param_9 == 0) {
          param_11 = (float *)&DAT_80435ea0;
          uVar8 = gnt4___assert_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_80435e98,0x2ec,&DAT_80435ea0,param_12,param_13,param_14,
                                   param_15,param_16);
          uVar4 = extraout_r4_01;
        }
        iVar5 = gnt4_HSD_CObjGetInterestWObj_bl
                          (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                           uVar4,param_11,param_12,param_13,param_14,param_15,param_16);
        gnt4_HSD_WObjGetPosition_bl
                  (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,afStack_8c,
                   (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
        param_11 = &local_80;
        gnt4_PSVECSubtract_bl(afStack_8c,afStack_98,param_11);
        param_10 = extraout_r4_02;
        dVar6 = zz_023cc18_((double)local_80);
        if (((DOUBLE_8043d268 < dVar6) ||
            (dVar6 = zz_023cc18_((double)local_7c), DOUBLE_8043d268 < dVar6)) ||
           (param_1 = zz_023cc18_((double)local_78), DOUBLE_8043d268 < param_1)) {
          param_1 = (double)gnt4_PSVECNormalize_bl(&local_80,&local_80);
          uVar4 = 0;
          param_10 = extraout_r4_03;
        }
        else {
          uVar4 = 0xffffffff;
        }
        uVar3 = countLeadingZeros(uVar4);
        uVar3 = uVar3 >> 5;
      }
      if (uVar3 != 0) {
        if (DOUBLE_8043d288 <= DOUBLE_8043d280 - (double)ABS(local_7c)) {
          param_4 = (double)(local_80 * local_80 + local_78 * local_78);
          if ((double)FLOAT_8043d240 < param_4) {
            dVar6 = 1.0 / SQRT(param_4);
            dVar6 = DOUBLE_8043d238 * dVar6 * -(param_4 * dVar6 * dVar6 - DOUBLE_8043d290);
            dVar6 = DOUBLE_8043d238 * dVar6 * -(param_4 * dVar6 * dVar6 - DOUBLE_8043d290);
            param_4 = (double)(float)(param_4 *
                                     DOUBLE_8043d238 * dVar6 *
                                     -(param_4 * dVar6 * dVar6 - DOUBLE_8043d290));
          }
          param_3 = (double)local_80;
          param_2 = (double)(-local_7c / (float)param_4);
          dVar6 = param_3 * param_2;
          dVar1 = (double)local_78 * param_2;
          dVar2 = param_4;
        }
        else {
          param_4 = (double)(local_7c * local_7c + local_78 * local_78);
          if ((double)FLOAT_8043d240 < param_4) {
            dVar6 = 1.0 / SQRT(param_4);
            dVar6 = DOUBLE_8043d238 * dVar6 * -(param_4 * dVar6 * dVar6 - DOUBLE_8043d290);
            dVar6 = DOUBLE_8043d238 * dVar6 * -(param_4 * dVar6 * dVar6 - DOUBLE_8043d290);
            param_4 = (double)(float)(param_4 *
                                     DOUBLE_8043d238 * dVar6 *
                                     -(param_4 * dVar6 * dVar6 - DOUBLE_8043d290));
          }
          param_3 = (double)local_7c;
          param_2 = (double)(-local_80 / (float)param_4);
          dVar1 = (double)local_78 * param_2;
          dVar6 = param_4;
          dVar2 = param_3 * param_2;
        }
        local_6c = (float)dVar1;
        local_70 = (float)dVar2;
        local_74 = (float)dVar6;
        gnt4_PSMTXRotAxisRad_bl(-dVar7,afStack_50,&local_80);
        param_11 = afStack_68;
        gnt4_PSMTXMultVecSR_bl(afStack_50,&local_74,param_11);
        param_1 = (double)gnt4_PSVECNormalize_bl(afStack_68,&local_5c);
        param_10 = extraout_r4_04;
      }
      if (param_9 != 0) {
        if ((*(uint *)(param_9 + 8) & 1) == 0) {
          dVar7 = gnt4_upvec2roll_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,param_9,&local_5c,(undefined *)param_11,param_12,param_13,
                                     param_14,param_15,param_16);
          if (param_9 != 0) {
            if ((*(uint *)(param_9 + 8) & 1) == 0) {
              if ((double)*(float *)(param_9 + 0x2c) != dVar7) {
                gnt4_HSD_CObjSetMtxDirty_bl(param_9);
              }
              *(float *)(param_9 + 0x2c) = (float)dVar7;
            }
            else {
              gnt4_roll2upvec_bl(dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 param_9,afStack_b0,(undefined *)param_11,param_12,param_13,param_14
                                 ,param_15,param_16);
              gnt4_HSD_CObjSetUpVector_bl
                        (dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         afStack_b0,param_11,param_12,param_13,param_14,param_15,param_16);
            }
          }
        }
        else {
          dVar7 = zz_023cc18_((double)local_5c);
          if (((DOUBLE_8043d268 < dVar7) ||
              (dVar7 = zz_023cc18_((double)local_58), DOUBLE_8043d268 < dVar7)) ||
             (dVar7 = zz_023cc18_((double)local_54), DOUBLE_8043d268 < dVar7)) {
            dVar7 = (double)gnt4_PSVECNormalize_bl(&local_5c,&local_a4);
            iVar5 = 0;
            param_10 = extraout_r4_05;
          }
          else {
            iVar5 = -1;
          }
          if (iVar5 != 0) {
            uVar8 = gnt4_OSReport_bl(dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                     s_illegal_up_vector__803ac820,param_10,param_11,param_12,
                                     param_13,param_14,param_15,param_16);
            gnt4___assert_bl(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_80435e98,0x3d0,&DAT_80435ea8,param_12,param_13,param_14,param_15,
                             param_16);
          }
          if (((*(float *)(param_9 + 0x2c) != local_a4) || (*(float *)(param_9 + 0x30) != local_a0))
             || (*(float *)(param_9 + 0x34) != local_9c)) {
            *(uint *)(param_9 + 8) = *(uint *)(param_9 + 8) | 0xc0000000;
            *(float *)(param_9 + 0x2c) = local_a4;
            *(float *)(param_9 + 0x30) = local_a0;
            *(float *)(param_9 + 0x34) = local_9c;
          }
        }
      }
    }
  }
  return;
}



// ==== 80248058  gnt4-HSD_CObjGetFov-bl ====

double gnt4_HSD_CObjGetFov_bl(int param_1)

{
  if ((param_1 != 0) && (*(char *)(param_1 + 0x50) == '\x01')) {
    return (double)*(float *)(param_1 + 0x40);
  }
  return (double)FLOAT_8043d240;
}



// ==== 8024807c  gnt4-HSD_CObjSetFov-bl ====

void gnt4_HSD_CObjSetFov_bl(double param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  if (*(char *)(param_2 + 0x50) != '\x01') {
    return;
  }
  *(float *)(param_2 + 0x40) = (float)param_1;
  return;
}



// ==== 8024809c  gnt4-HSD_CObjGetNear-bl ====

double gnt4_HSD_CObjGetNear_bl(int param_1)

{
  if (param_1 == 0) {
    return (double)FLOAT_8043d240;
  }
  return (double)*(float *)(param_1 + 0x38);
}



// ==== 802480b4  gnt4-HSD_CObjSetNear-bl ====

void gnt4_HSD_CObjSetNear_bl(double param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  *(float *)(param_2 + 0x38) = (float)param_1;
  return;
}



// ==== 802480c4  gnt4-HSD_CObjGetFar-bl ====

double gnt4_HSD_CObjGetFar_bl(int param_1)

{
  if (param_1 == 0) {
    return (double)FLOAT_8043d240;
  }
  return (double)*(float *)(param_1 + 0x3c);
}



// ==== 802480dc  gnt4-HSD_CObjSetFar-bl ====

void gnt4_HSD_CObjSetFar_bl(double param_1,int param_2)

{
  if (param_2 == 0) {
    return;
  }
  *(float *)(param_2 + 0x3c) = (float)param_1;
  return;
}



// ==== 802480ec  gnt4-HSD_CObjSetScissorx4-bl ====

void gnt4_HSD_CObjSetScissorx4_bl
               (int param_1,undefined2 param_2,undefined2 param_3,undefined2 param_4,
               undefined2 param_5)

{
  if (param_1 == 0) {
    return;
  }
  *(undefined2 *)(param_1 + 0x1c) = param_2;
  *(undefined2 *)(param_1 + 0x1e) = param_3;
  *(undefined2 *)(param_1 + 0x20) = param_4;
  *(undefined2 *)(param_1 + 0x22) = param_5;
  return;
}



// ==== 80248108  gnt4-HSD_CObjSetViewportfx4-bl ====

void gnt4_HSD_CObjSetViewportfx4_bl
               (double param_1,double param_2,double param_3,double param_4,int param_5)

{
  if (param_5 == 0) {
    return;
  }
  *(float *)(param_5 + 0xc) = (float)param_1;
  *(float *)(param_5 + 0x10) = (float)param_2;
  *(float *)(param_5 + 0x14) = (float)param_3;
  *(float *)(param_5 + 0x18) = (float)param_4;
  return;
}



// ==== 80248124  gnt4-HSD_CObjSetPerspective-bl ====

void gnt4_HSD_CObjSetPerspective_bl(double param_1,double param_2,int param_3)

{
  if (param_3 == 0) {
    return;
  }
  *(undefined1 *)(param_3 + 0x50) = 1;
  *(float *)(param_3 + 0x40) = (float)param_1;
  *(float *)(param_3 + 0x44) = (float)param_2;
  return;
}



// ==== 80248140  gnt4-HSD_CObjSetOrtho-bl ====

void gnt4_HSD_CObjSetOrtho_bl
               (double param_1,double param_2,double param_3,double param_4,int param_5)

{
  if (param_5 == 0) {
    return;
  }
  *(undefined1 *)(param_5 + 0x50) = 3;
  *(float *)(param_5 + 0x40) = (float)param_1;
  *(float *)(param_5 + 0x44) = (float)param_2;
  *(float *)(param_5 + 0x48) = (float)param_3;
  *(float *)(param_5 + 0x4c) = (float)param_4;
  return;
}



// ==== 80248164  gnt4-HSD_CObjSetFlags-bl ====

void gnt4_HSD_CObjSetFlags_bl(int param_1,uint param_2)

{
  if (param_1 == 0) {
    return;
  }
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) | param_2;
  return;
}



// ==== 8024817c  gnt4-HSD_CObjClearFlags-bl ====

void gnt4_HSD_CObjClearFlags_bl(int param_1,uint param_2)

{
  if (param_1 == 0) {
    return;
  }
  *(uint *)(param_1 + 8) = *(uint *)(param_1 + 8) & ~param_2;
  return;
}



// ==== 80248194  gnt4-HSD_CObjGetCurrent ====

undefined4 gnt4_HSD_CObjGetCurrent(void)

{
  return DAT_8043695c;
}



// ==== 8024819c  gnt4-HSD_CObjAlloc-bl ====

int * gnt4_HSD_CObjAlloc_bl
                (undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int *piVar1;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined **ppuVar2;
  
  ppuVar2 = DAT_80436958;
  if (DAT_80436958 == (undefined **)0x0) {
    ppuVar2 = &PTR_gnt4_CObjInfoInit_bl_803ac730;
  }
  piVar1 = gnt4_hsdNew_bl(ppuVar2);
  if (piVar1 == (int *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e98,
                     0x790,&DAT_80435ea0,in_r6,in_r7,in_r8,in_r9,in_r10);
  }
  return piVar1;
}



// ==== 802481f8  gnt4-CObjLoad-bl ====

undefined4
gnt4_CObjLoad_bl(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  ushort uVar4;
  undefined4 uVar5;
  undefined4 extraout_r4;
  undefined8 uVar6;
  double dVar7;
  
  *(uint *)(param_9 + 8) = (uint)*(ushort *)(param_10 + 4);
  if (param_9 != 0) {
    *(uint *)(param_9 + 8) = *(uint *)(param_9 + 8) & 0xc0000000 | (uint)*(ushort *)(param_10 + 4);
    param_1 = DOUBLE_8043d250;
    *(float *)(param_9 + 0xc) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_10 + 8) ^ 0x80000000) -
                DOUBLE_8043d250);
    *(float *)(param_9 + 0x10) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_10 + 10) ^ 0x80000000) - param_1)
    ;
    *(float *)(param_9 + 0x14) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_10 + 0xc) ^ 0x80000000) - param_1
                );
    *(float *)(param_9 + 0x18) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_10 + 0xe) ^ 0x80000000) - param_1
                );
    uVar5 = *(undefined4 *)(param_10 + 0x14);
    *(undefined4 *)(param_9 + 0x1c) = *(undefined4 *)(param_10 + 0x10);
    *(undefined4 *)(param_9 + 0x20) = uVar5;
  }
  uVar6 = gnt4_HSD_WObjInit_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     *(int *)(param_9 + 0x24),*(int *)(param_10 + 0x18),param_11,param_12,param_13,
                     param_14,param_15,param_16);
  dVar7 = (double)gnt4_HSD_WObjInit_bl
                            (uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             *(int *)(param_9 + 0x28),*(int *)(param_10 + 0x1c),param_11,param_12,
                             param_13,param_14,param_15,param_16);
  if (param_9 != 0) {
    *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(param_10 + 0x28);
  }
  if (param_9 != 0) {
    *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_10 + 0x2c);
  }
  if ((*(ushort *)(param_10 + 4) & 1) == 0) {
    uVar6 = gnt4_HSD_CObjSetRoll_bl
                      ((double)*(float *)(param_10 + 0x20),param_2,param_3,param_4,param_5,param_6,
                       param_7,param_8,param_9,extraout_r4,param_11,param_12,param_13,param_14,
                       param_15,param_16);
  }
  else if (*(float **)(param_10 + 0x24) == (float *)0x0) {
    uVar6 = gnt4_HSD_CObjSetUpVector_bl
                      (dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       (float *)&DAT_803ac858,param_11,param_12,param_13,param_14,param_15,param_16)
    ;
  }
  else {
    uVar6 = gnt4_HSD_CObjSetUpVector_bl
                      (dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                       *(float **)(param_10 + 0x24),param_11,param_12,param_13,param_14,param_15,
                       param_16);
  }
  uVar4 = *(ushort *)(param_10 + 6);
  if (uVar4 == 2) {
    uVar5 = *(undefined4 *)(param_10 + 0x3c);
    uVar1 = *(undefined4 *)(param_10 + 0x38);
    uVar2 = *(undefined4 *)(param_10 + 0x34);
    uVar3 = *(undefined4 *)(param_10 + 0x30);
    if (param_9 != 0) {
      *(undefined1 *)(param_9 + 0x50) = 2;
      *(undefined4 *)(param_9 + 0x40) = uVar3;
      *(undefined4 *)(param_9 + 0x44) = uVar2;
      *(undefined4 *)(param_9 + 0x48) = uVar1;
      *(undefined4 *)(param_9 + 0x4c) = uVar5;
    }
  }
  else {
    if (uVar4 < 2) {
      if (uVar4 != 0) {
        uVar5 = *(undefined4 *)(param_10 + 0x34);
        uVar1 = *(undefined4 *)(param_10 + 0x30);
        if (param_9 == 0) {
          return 0;
        }
        *(undefined1 *)(param_9 + 0x50) = 1;
        *(undefined4 *)(param_9 + 0x40) = uVar1;
        *(undefined4 *)(param_9 + 0x44) = uVar5;
        return 0;
      }
    }
    else if (uVar4 < 4) {
      uVar5 = *(undefined4 *)(param_10 + 0x3c);
      uVar1 = *(undefined4 *)(param_10 + 0x38);
      uVar2 = *(undefined4 *)(param_10 + 0x34);
      uVar3 = *(undefined4 *)(param_10 + 0x30);
      if (param_9 == 0) {
        return 0;
      }
      *(undefined1 *)(param_9 + 0x50) = 3;
      *(undefined4 *)(param_9 + 0x40) = uVar3;
      *(undefined4 *)(param_9 + 0x44) = uVar2;
      *(undefined4 *)(param_9 + 0x48) = uVar1;
      *(undefined4 *)(param_9 + 0x4c) = uVar5;
      return 0;
    }
    gnt4___assert_bl(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435e98,
                     0x7be,&DAT_80435ea8,param_12,param_13,param_14,param_15,param_16);
  }
  return 0;
}



// ==== 80248424  zz_0248424_ ====

void zz_0248424_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  if ((param_9 != 0) && (param_10 != 0)) {
    gnt4_CObjLoad_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                     param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80248458  gnt4-CObjInit-bl ====

int gnt4_CObjInit_bl(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                    double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int *piVar2;
  undefined8 extraout_f1;
  undefined8 uVar3;
  
  iVar1 = (**(code **)(DAT_803ac744 + 0x2c))();
  if (-1 < iVar1) {
    if (param_9 != 0) {
      *(uint *)(param_9 + 8) = *(uint *)(param_9 + 8) | 0xc0000000;
    }
    uVar3 = extraout_f1;
    piVar2 = gnt4_HSD_WObjAlloc_bl
                       (extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    *(int **)(param_9 + 0x24) = piVar2;
    piVar2 = gnt4_HSD_WObjAlloc_bl(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    *(int **)(param_9 + 0x28) = piVar2;
    iVar1 = 0;
  }
  return iVar1;
}



