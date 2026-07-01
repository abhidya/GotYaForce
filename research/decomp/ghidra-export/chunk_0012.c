// ==== 8007f8b8  zz_007f8b8_ ====

void zz_007f8b8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_9 + 0x90);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  uVar1 = 1;
  if (*(char *)(iVar2 + 0x3ec) == '\x04') {
    uVar1 = 0x44;
  }
  zz_00097b4_(*(int *)(param_9 + 0xe0),uVar1);
  return;
}



// ==== 8007f914  zz_007f914_ ====

void zz_007f914_(void)

{
  if (PTR_DAT_80433930[1] == '\0') {
    PTR_DAT_80433930[1] = 1;
    gnt4_memset(PTR_DAT_80433948,0,0x20);
  }
  (*(code *)(&PTR_zz_007f97c__802d7130)[(char)*PTR_DAT_80433948])();
  return;
}



// ==== 8007f97c  zz_007f97c_ ====

void zz_007f97c_(void)

{
  int iVar1;
  double dVar2;
  
  if (PTR_DAT_80433948[1] == '\0') {
    iVar1 = 0;
    do {
      zz_010d8f8_(iVar1,2);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 4);
    PTR_DAT_80433948[1] = PTR_DAT_80433948[1] + '\x01';
  }
  iVar1 = zz_000a07c_();
  if ((PTR_DAT_80433930[0x2b] & 6) != 0) {
    iVar1 = 0;
  }
  if (iVar1 == 0) {
    dVar2 = (double)FLOAT_80437a18;
    *PTR_DAT_80433948 = *PTR_DAT_80433948 + '\x01';
    PTR_DAT_80433948[1] = 0;
    zz_00e9b60_(dVar2,2,0x1e,2);
    zz_00f07c4_();
    *(undefined2 *)(PTR_DAT_80433948 + 8) = 0x1e;
  }
  zz_008c0b4_(zz_007fcb0_);
  return;
}



// ==== 8007fa48  zz_007fa48_ ====

void zz_007fa48_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  short sVar2;
  undefined *puVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined8 uVar4;
  
  puVar3 = PTR_DAT_80433948;
  sVar2 = *(short *)(PTR_DAT_80433948 + 8);
  *(short *)(PTR_DAT_80433948 + 8) = sVar2 + -1;
  if ((short)(sVar2 + -1) < 1) {
    uVar4 = zz_00e9ac0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,puVar3,
                        param_11,param_12,param_13,param_14,param_15,param_16);
    uVar4 = zz_00e9ac0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,extraout_r4,
                        param_11,param_12,param_13,param_14,param_15,param_16);
    zz_00e9ac0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,extraout_r4_00,
                param_11,param_12,param_13,param_14,param_15,param_16);
    zz_008c098_();
    PTR_DAT_80433930[0x29] = 0;
    zz_008c3a0_(0);
    zz_002a5f4_(0,0,0,0xff);
    zz_007fe60_();
    bVar1 = PTR_DAT_80433930[0x2b];
    gnt4_VISetBlack(1);
    gnt4_VIFlush_bl();
    gnt4_VIWaitForRetrace();
    uVar4 = gnt4_VIWaitForRetrace();
    if ((bVar1 & 4) == 0) {
      if ((bVar1 & 8) == 0) {
        if ((bVar1 & 2) == 0) {
          if ((bVar1 & 1) != 0) {
            *PTR_DAT_80433948 = *PTR_DAT_80433948 + '\x01';
          }
        }
        else {
          zz_02048b8_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0);
        }
      }
      else {
        zz_02048b8_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,0,1);
      }
    }
    else {
      zz_02048b8_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,0,0);
    }
    zz_01b7528_();
  }
  else {
    zz_008c0b4_(zz_007fcb0_);
  }
  return;
}



// ==== 8007fb6c  zz_007fb6c_ ====

void zz_007fb6c_(void)

{
  *PTR_DAT_80433948 = *PTR_DAT_80433948 + '\x01';
  return;
}



// ==== 8007fb80  zz_007fb80_ ====

void zz_007fb80_(void)

{
  int iVar1;
  
  iVar1 = gnt4_PADRecalibrate_bl(0xf0000000);
  if (iVar1 == 1) {
    *PTR_DAT_80433948 = *PTR_DAT_80433948 + '\x01';
  }
  return;
}



// ==== 8007fbbc  zz_007fbbc_ ====

void zz_007fbbc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  *PTR_DAT_80433948 = *PTR_DAT_80433948 + '\x01';
  zz_0009e08_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 8007fbec  zz_007fbec_ ====

void zz_007fbec_(void)

{
  char cVar1;
  
  PTR_DAT_80433930[1] = 0;
  if (PTR_DAT_80433930[0x41] == '\0') {
    cVar1 = PTR_DAT_80433938[0x14];
    *PTR_DAT_80433930 = 0;
    PTR_DAT_80433930[1] = (char)((byte)((uint)-(int)cVar1 >> 0x18) | cVar1 >> 7) >> 7;
    zz_0027e54_();
  }
  else {
    *PTR_DAT_80433930 = 1;
    PTR_DAT_80433930[1] = 0;
  }
  PTR_DAT_80433930[0x2b] = 0;
  zz_00059b8_();
  PTR_DAT_80433930[0x2c] = 0;
  PTR_DAT_80433930[0x2d] = 0;
  PTR_DAT_80433930[0x2e] = 0;
  PTR_DAT_80433930[0x2f] = 0;
  zz_00f0a34_();
  zz_00f0a60_();
  gnt4_VISetBlack(0);
  gnt4_VIFlush_bl();
  gnt4_VIWaitForRetrace();
  gnt4_VIWaitForRetrace();
  return;
}



// ==== 8007fcb0  zz_007fcb0_ ====

void zz_007fcb0_(void)

{
  uint local_18 [2];
  undefined4 local_10;
  uint uStack_c;
  longlong local_8;
  
  DAT_803c1150 = local_18;
  local_10 = 0x43300000;
  uStack_c = 0x1eU - (int)*(short *)(PTR_DAT_80433948 + 8) ^ 0x80000000;
  DAT_803c1140 = &DAT_802d7148;
  DAT_803c1170 = 1;
  DAT_803c1144 = 0;
  DAT_803c1154 = &DAT_804338f8;
  DAT_803c1164 = 7;
  local_18[0] = (uint)(FLOAT_80437a1c *
                      ((float)((double)CONCAT44(0x43300000,uStack_c) - DOUBLE_80437a28) /
                      FLOAT_80437a20));
  local_8 = (longlong)(int)local_18[0];
  local_18[0] = local_18[0] & 0xff;
  FUN_80051998(-0x7fc3eed0);
  return;
}



// ==== 8007fd5c  zz_007fd5c_ ====

void zz_007fd5c_(void)

{
  DAT_804361ac = 0;
  DAT_804361a8 = 0;
  return;
}



// ==== 8007fd6c  zz_007fd6c_ ====

void zz_007fd6c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,int param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  int iVar2;
  byte in_cr1;
  undefined4 local_88;
  int local_84;
  undefined4 local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  char local_28 [4];
  undefined1 *local_24;
  undefined4 *local_20;
  
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_68 = param_1;
    local_60 = param_2;
    local_58 = param_3;
    local_50 = param_4;
    local_48 = param_5;
    local_40 = param_6;
    local_38 = param_7;
    local_30 = param_8;
  }
  local_24 = &stack0x00000008;
  local_20 = &local_88;
  *(undefined4 *)(&DAT_803b2808 + DAT_804361a8 * 4) = param_9;
  *(int *)(&DAT_803b2808 + ((DAT_804361a8 + 1) * 4 & 0xfc)) = param_10;
  local_28[0] = '\x02';
  local_28[1] = '\0';
  local_28[2] = '\0';
  local_28[3] = '\0';
  local_88 = param_9;
  local_84 = param_10;
  local_80 = param_11;
  local_7c = param_12;
  local_78 = param_13;
  local_74 = param_14;
  local_70 = param_15;
  local_6c = param_16;
  DAT_804361a8 = DAT_804361a8 + 1 & 0x3f;
  for (iVar2 = 0; DAT_804361a8 = DAT_804361a8 + 1 & 0x3f, iVar2 < param_10; iVar2 = iVar2 + 1) {
    piVar1 = __va_arg(local_28,1);
    *(int *)(&DAT_803b2808 + DAT_804361a8 * 4) = *piVar1;
  }
  return;
}



// ==== 8007fe60  zz_007fe60_ ====

void zz_007fe60_(void)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  code *pcVar11;
  uint uVar12;
  undefined4 local_28 [8];
  
  while (DAT_804361a8 != DAT_804361ac) {
    pcVar11 = *(code **)(&DAT_803b2808 + DAT_804361ac * 4);
    iVar6 = *(int *)(&DAT_803b2808 + ((DAT_804361ac + 1) * 4 & 0xfc));
    DAT_804361ac = (DAT_804361ac + 1 & 0x3f) + 1 & 0x3f;
    iVar7 = 0;
    if (0 < iVar6) {
      if (8 < iVar6) {
        uVar12 = iVar6 - 1U >> 3;
        puVar5 = local_28;
        if (0 < iVar6 + -8) {
          do {
            uVar2 = (DAT_804361ac + 1 & 0x3f) + 1;
            iVar7 = iVar7 + 8;
            *puVar5 = *(undefined4 *)(&DAT_803b2808 + DAT_804361ac * 4);
            uVar8 = (uVar2 & 0x3f) + 1;
            puVar5[1] = *(undefined4 *)(&DAT_803b2808 + ((DAT_804361ac + 1) * 4 & 0xfc));
            uVar3 = (uVar8 & 0x3f) + 1;
            uVar9 = (uVar3 & 0x3f) + 1;
            puVar5[2] = *(undefined4 *)(&DAT_803b2808 + (uVar2 * 4 & 0xfc));
            uVar2 = (uVar9 & 0x3f) + 1;
            uVar10 = (uVar2 & 0x3f) + 1;
            puVar5[3] = *(undefined4 *)(&DAT_803b2808 + (uVar8 * 4 & 0xfc));
            DAT_804361ac = (uVar10 & 0x3f) + 1 & 0x3f;
            puVar5[4] = *(undefined4 *)(&DAT_803b2808 + (uVar3 * 4 & 0xfc));
            puVar5[5] = *(undefined4 *)(&DAT_803b2808 + (uVar9 * 4 & 0xfc));
            puVar5[6] = *(undefined4 *)(&DAT_803b2808 + (uVar2 * 4 & 0xfc));
            puVar5[7] = *(undefined4 *)(&DAT_803b2808 + (uVar10 * 4 & 0xfc));
            puVar5 = puVar5 + 8;
            uVar12 = uVar12 - 1;
          } while (uVar12 != 0);
        }
      }
      iVar4 = iVar6 - iVar7;
      puVar5 = local_28 + iVar7;
      if (iVar7 < iVar6) {
        do {
          iVar1 = DAT_804361ac * 4;
          DAT_804361ac = DAT_804361ac + 1 & 0x3f;
          iVar7 = iVar7 + 1;
          *puVar5 = *(undefined4 *)(&DAT_803b2808 + iVar1);
          puVar5 = puVar5 + 1;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
    }
    if (pcVar11 != (code *)0x0) {
      switch(iVar6) {
      case 0:
        (*pcVar11)();
        break;
      case 1:
        (*pcVar11)(local_28[0]);
        break;
      case 2:
        (*pcVar11)(local_28[0],local_28[1]);
        break;
      case 3:
        (*pcVar11)(local_28[0],local_28[1],local_28[2],iVar7);
        break;
      case 4:
        (*pcVar11)(local_28[0],local_28[1],local_28[2],local_28[3]);
        break;
      case 5:
        (*pcVar11)(local_28[0],local_28[1],local_28[2],local_28[3],local_28[4]);
        break;
      case 6:
        (*pcVar11)(local_28[0],local_28[1],local_28[2],local_28[3],local_28[4],local_28[5]);
        break;
      case 7:
        (*pcVar11)(local_28[0],local_28[1],local_28[2],local_28[3],local_28[4],local_28[5],
                   local_28[6]);
        break;
      case 8:
        (*pcVar11)(local_28[0],local_28[1],local_28[2],local_28[3],local_28[4],local_28[5],
                   local_28[6],local_28[7]);
      }
    }
  }
  return;
}



// ==== 80080124  zz_0080124_ ====

void zz_0080124_(void)

{
  DAT_804361b8 = DAT_80436238 + 0xab6c00;
  DAT_804361bc = DAT_80436238 + 0xaf6c00;
  zz_020352c_(DAT_804361bc);
  DAT_804361b0 = 0;
  DAT_80433900 = 1;
  DAT_804361b4 = 1;
  return;
}



// ==== 80080170  zz_0080170_ ====

void zz_0080170_(void)

{
  DAT_804361b4 = 0;
  return;
}



// ==== 8008017c  zz_008017c_ ====

undefined4 zz_008017c_(void)

{
  return DAT_804361b4;
}



// ==== 80080184  zz_0080184_ ====

void zz_0080184_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,char *param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  double dVar1;
  int iVar2;
  undefined2 *puVar3;
  byte in_cr1;
  undefined4 local_88;
  undefined4 local_84;
  undefined4 local_80;
  char *local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined8 local_68;
  undefined8 local_60;
  undefined8 local_58;
  undefined8 local_50;
  undefined8 local_48;
  undefined8 local_40;
  undefined8 local_38;
  undefined8 local_30;
  char local_28 [4];
  undefined1 *local_24;
  undefined4 *local_20;
  undefined4 local_18;
  uint uStack_14;
  
  dVar1 = DOUBLE_80437a30;
  if ((bool)(in_cr1 >> 1 & 1)) {
    local_68 = param_1;
    local_60 = param_2;
    local_58 = param_3;
    local_50 = param_4;
    local_48 = param_5;
    local_40 = param_6;
    local_38 = param_7;
    local_30 = param_8;
  }
  if (DAT_804361b0 < 0x10) {
    local_24 = &stack0x00000008;
    local_20 = &local_88;
    local_28[0] = '\x04';
    local_28[1] = '\0';
    local_28[2] = '\0';
    local_28[3] = '\0';
    puVar3 = (undefined2 *)(DAT_804361b8 + DAT_804361b0 * 0x80);
    *puVar3 = (short)param_9;
    puVar3[1] = (short)param_10;
    *(undefined4 *)(puVar3 + 2) = param_11;
    local_18 = 0x43300000;
    uStack_14 = (int)DAT_80433900 ^ 0x80000000;
    *(float *)(puVar3 + 4) = (float)((double)CONCAT44(0x43300000,uStack_14) - dVar1);
    local_88 = param_9;
    local_84 = param_10;
    local_80 = param_11;
    local_7c = param_12;
    local_78 = param_13;
    local_74 = param_14;
    local_70 = param_15;
    local_6c = param_16;
    iVar2 = zz_0236910_((int)(puVar3 + 6),param_12,local_28);
    *(undefined1 *)((int)(puVar3 + 6) + iVar2) = 0;
    DAT_804361b0 = DAT_804361b0 + 1;
  }
  return;
}



// ==== 80080278  zz_0080278_ ====

void zz_0080278_(void)

{
  DAT_804361b0 = 0;
  DAT_80433900 = 1;
  return;
}



// ==== 8008028c  zz_008028c_ ====

void zz_008028c_(double param_1)

{
  DAT_80433900 = (short)(int)param_1;
  return;
}



// ==== 800802a8  zz_00802a8_ ====

void zz_00802a8_(void)

{
  int iVar1;
  int iVar2;
  double dVar3;
  float afStack_88 [12];
  float afStack_58 [16];
  undefined4 local_18;
  uint uStack_14;
  undefined4 local_10;
  uint uStack_c;
  
  if ((DAT_804361b0 != 0) && (DAT_804361b4 != 0)) {
    dVar3 = (double)FLOAT_80437a38;
    uStack_14 = (uint)*(ushort *)(DAT_804362ac + 6);
    uStack_c = (uint)*(ushort *)(DAT_804362ac + 4);
    local_18 = 0x43300000;
    local_10 = 0x43300000;
    gnt4_C_MTXOrtho_bl(dVar3,(double)(float)((double)CONCAT44(0x43300000,uStack_14) -
                                            DOUBLE_80437a40),dVar3,
                       (double)(float)((double)CONCAT44(0x43300000,uStack_c) - DOUBLE_80437a40),
                       dVar3,(double)FLOAT_80437a3c,afStack_58);
    gnt4_GXSetProjection_bl(afStack_58,1);
    gnt4_PSMTXIdentity_bl(afStack_88);
    gnt4_GXLoadPosMtxImm_bl(afStack_88,0);
    gnt4_GXSetCurrentMtx_bl(0);
    gnt4_GXSetZMode_bl(1,7,1);
    gnt4_GXClearVtxDesc_bl();
    gnt4_GXSetVtxDesc_bl(9,1);
    gnt4_GXSetVtxDesc_bl(0xd,1);
    gnt4_GXSetVtxDesc_bl(0xb,1);
    gnt4_GXSetVtxAttrFmt_bl(0,9,1,4,0);
    gnt4_GXSetVtxAttrFmt_bl(0,0xb,1,5,0);
    gnt4_GXSetVtxAttrFmt_bl(0,0xd,1,3,0);
    gnt4_GXSetNumChans_bl(1);
    gnt4_GXSetNumTexGens_bl(1);
    gnt4_GXSetNumTevStages_bl(1);
    gnt4_GXSetChanCtrl_bl(4,0,1,1,0,0,2);
    gnt4_GXSetTevOp_bl(0,0);
    gnt4_GXSetTevOrder_bl(0,0,0,4);
    gnt4_GXSetTexCoordGen2_bl(0,1,4,0x1e,0,0x7d);
    gnt4_GXSetBlendMode_bl(1,4,5,0);
    iVar2 = 0;
    for (iVar1 = 0; iVar1 < DAT_804361b0; iVar1 = iVar1 + 1) {
      FUN_80080494((short *)(DAT_804361b8 + iVar2));
      iVar2 = iVar2 + 0x80;
    }
  }
  return;
}



// ==== 80080494  FUN_80080494 ====

/* WARNING: Removing unreachable block (ram,0x80080584) */
/* WARNING: Removing unreachable block (ram,0x8008057c) */
/* WARNING: Removing unreachable block (ram,0x80080574) */
/* WARNING: Removing unreachable block (ram,0x800804b4) */
/* WARNING: Removing unreachable block (ram,0x800804ac) */
/* WARNING: Removing unreachable block (ram,0x800804a4) */

void FUN_80080494(short *param_1)

{
  byte *pbVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  uint local_68;
  int local_64;
  int local_60;
  uint local_5c [3];
  undefined4 local_50;
  uint uStack_4c;
  
  pbVar1 = (byte *)(param_1 + 6);
  local_5c[2] = (int)*param_1 ^ 0x80000000;
  local_5c[1] = 0x43300000;
  uStack_4c = (int)param_1[1] ^ 0x80000000;
  dVar3 = (double)CONCAT44(0x43300000,local_5c[2]) - DOUBLE_80437a30;
  dVar2 = (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_80437a30);
  dVar4 = DOUBLE_80437a30;
  while( true ) {
    local_50 = 0x43300000;
    dVar3 = (double)(float)dVar3;
    if (*pbVar1 == 0) break;
    pbVar1 = FUN_8020360c(pbVar1,(int *)local_5c,&local_60,&local_64,&local_68);
    FUN_800805a8(local_5c[0]);
    FUN_80080678(dVar3,dVar2,(int)param_1,(short)local_60,(short)local_64);
    uStack_4c = local_68 ^ 0x80000000;
    dVar3 = (double)(float)((double)CONCAT44(0x43300000,uStack_4c) - dVar4) *
            (double)*(float *)(param_1 + 4) + dVar3;
  }
  return;
}



// ==== 800805a8  FUN_800805a8 ====

void FUN_800805a8(uint param_1)

{
  double dVar1;
  uint auStack_68 [8];
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  undefined4 local_10;
  uint uStack_c;
  
  gnt4_GXInitTexObj_bl
            (auStack_68,param_1,(uint)*(ushort *)(DAT_804361bc + 0x1e),
             (uint)*(ushort *)(DAT_804361bc + 0x20),(uint)*(ushort *)(DAT_804361bc + 0x18),0,0,'\0')
  ;
  dVar1 = (double)FLOAT_80437a38;
  gnt4_GXInitTexObjLOD_bl(dVar1,dVar1,dVar1,auStack_68,1,1,0,'\0',0);
  gnt4_GXLoadTexObj_bl(auStack_68,0);
  local_18 = 0x43300000;
  uStack_14 = (uint)*(ushort *)(DAT_804361bc + 0x1e);
  uStack_c = (uint)*(ushort *)(DAT_804361bc + 0x20);
  dVar1 = (double)FLOAT_80437a48;
  local_10 = 0x43300000;
  gnt4_PSMTXScale_bl((double)(float)(dVar1 / (double)(float)((double)CONCAT44(0x43300000,uStack_14)
                                                            - DOUBLE_80437a40)),
                     (double)(float)(dVar1 / (double)(float)((double)CONCAT44(0x43300000,uStack_c) -
                                                            DOUBLE_80437a40)),dVar1,afStack_48);
  gnt4_GXLoadTexMtxImm_bl(afStack_48,0x1e,1);
  return;
}



// ==== 80080678  FUN_80080678 ====

/* WARNING: Removing unreachable block (ram,0x800807c8) */
/* WARNING: Removing unreachable block (ram,0x800807c0) */
/* WARNING: Removing unreachable block (ram,0x800807b8) */
/* WARNING: Removing unreachable block (ram,0x800807b0) */
/* WARNING: Removing unreachable block (ram,0x800806a0) */
/* WARNING: Removing unreachable block (ram,0x80080698) */
/* WARNING: Removing unreachable block (ram,0x80080690) */
/* WARNING: Removing unreachable block (ram,0x80080688) */

void FUN_80080678(double param_1,double param_2,int param_3,short param_4,short param_5)

{
  short sVar1;
  short sVar2;
  double dVar3;
  double dVar4;
  
  sVar2 = param_4 + *(ushort *)(DAT_804361bc + 0x10);
  sVar1 = param_5 + *(ushort *)(DAT_804361bc + 0x12);
  dVar4 = (double)(float)((double)(float)((double)CONCAT44(0x43300000,
                                                           (uint)*(ushort *)(DAT_804361bc + 0x10)) -
                                         DOUBLE_80437a40) * (double)*(float *)(param_3 + 8) +
                         param_1);
  dVar3 = (double)(float)((double)(float)((double)CONCAT44(0x43300000,
                                                           (uint)*(ushort *)(DAT_804361bc + 0x12)) -
                                         DOUBLE_80437a40) * (double)*(float *)(param_3 + 8) +
                         param_2);
  gnt4_GXBegin_bl(0x80,0,4);
  DAT_cc008000 = (float)param_1;
  DAT_cc008000 = (float)param_2;
  DAT_cc008000 = FLOAT_80437a48;
  DAT_cc008000 = *(undefined4 *)(param_3 + 4);
  DAT_cc008000._0_2_ = param_4;
  DAT_cc008000._0_2_ = param_5;
  DAT_cc008000 = (float)dVar4;
  DAT_cc008000 = (float)param_2;
  DAT_cc008000 = FLOAT_80437a48;
  DAT_cc008000 = *(undefined4 *)(param_3 + 4);
  DAT_cc008000._0_2_ = sVar2;
  DAT_cc008000._0_2_ = param_5;
  DAT_cc008000 = (float)dVar4;
  DAT_cc008000 = (float)dVar3;
  DAT_cc008000 = FLOAT_80437a48;
  DAT_cc008000 = *(undefined4 *)(param_3 + 4);
  DAT_cc008000._0_2_ = sVar2;
  DAT_cc008000._0_2_ = sVar1;
  DAT_cc008000 = (float)param_1;
  DAT_cc008000 = (float)dVar3;
  DAT_cc008000 = FLOAT_80437a48;
  DAT_cc008000 = *(undefined4 *)(param_3 + 4);
  DAT_cc008000._0_2_ = param_4;
  DAT_cc008000._0_2_ = sVar1;
  return;
}



// ==== 800807e4  FUN_800807e4 ====

void FUN_800807e4(undefined4 param_1)

{
  undefined1 *puVar1;
  
  if (((PTR_DAT_80433930[0x40] == '\0') && ((char)PTR_DAT_80433934[0x45] < '\x05')) &&
     (puVar1 = zz_008893c_(2,0x38,0,6), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_80080874;
    *(code **)(puVar1 + 0x10c) = FUN_80080a74;
    *(undefined4 *)(puVar1 + 0x90) = param_1;
    *(undefined4 *)(puVar1 + 0x8c) = param_1;
  }
  return;
}



// ==== 80080874  FUN_80080874 ====

void FUN_80080874(int param_1)

{
  (*(code *)(&PTR_FUN_802d7178)[*(char *)(param_1 + 0x18)])(param_1,*(undefined4 *)(param_1 + 0x90))
  ;
  return;
}



// ==== 800808b4  FUN_800808b4 ====

void FUN_800808b4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined8 uVar2;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(code **)(param_9 + 0x100) = FUN_80080f88;
  uVar2 = zz_0089100_(param_9,0x21,1);
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x144) = 0xffff;
  *(undefined1 *)(param_9 + 0x148) = 0xff;
  *(undefined2 *)(param_9 + 0x146) = 0xffff;
  *(undefined1 *)(param_9 + 0x149) = 0xff;
  *(undefined2 *)(param_9 + 0x14a) = 0;
  *(undefined2 *)(param_9 + 0x14c) = 0xffff;
  *(undefined2 *)(param_9 + 0x14e) = 0xffff;
  *(undefined2 *)(param_9 + 0x152) = 0;
  *(undefined1 *)(param_9 + 0x151) = 0;
  *(undefined2 *)(param_9 + 0x154) = 0;
  *(undefined4 *)(param_9 + 0x15c) = 0;
  *(undefined4 *)(param_9 + 0x158) = 0;
  zz_0006fb4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0xe8),0x51,param_12,param_13,param_14,param_15,param_16);
  uVar1 = 0;
  uVar2 = zz_0007cd0_(*(int *)(param_9 + 0xe8),0,0xff,0);
  zz_0006fb4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0xec),0x51,uVar1,param_13,param_14,param_15,param_16);
  uVar1 = 0;
  uVar2 = zz_0007cd0_(*(int *)(param_9 + 0xec),0xff,0,0);
  zz_0006fb4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0xf0),0x32,uVar1,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80080990  FUN_80080990 ====

void FUN_80080990(int param_1)

{
  if (PTR_DAT_80433934[0x45] == '\x04') {
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x400;
    *(short *)(param_1 + 0x14a) = *(short *)(param_1 + 0x14a) + 0x400;
    *(short *)(param_1 + 0x152) = *(short *)(param_1 + 0x152) + 1;
    *(short *)(param_1 + 0x154) = *(short *)(param_1 + 0x154) + 0x1000;
    if (*(short *)(param_1 + 0x154) < 0) {
      *(undefined2 *)(param_1 + 0x154) = 0;
    }
  }
  if (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18)) ||
     ((PTR_DAT_80433934[0x45] == '\x05' && ('\x01' < (char)PTR_DAT_80433934[0x52])))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_0089444_(param_1);
  }
  return;
}



// ==== 80080a54  FUN_80080a54 ====

void FUN_80080a54(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80080a74  FUN_80080a74 ====

void FUN_80080a74(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  double dVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  char cVar6;
  uint uVar5;
  float *pfVar7;
  int iVar8;
  float fVar9;
  int iVar10;
  double dVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  undefined4 local_9c;
  undefined4 local_98;
  float local_94;
  float local_90;
  float local_8c;
  float afStack_88 [12];
  float afStack_58 [3];
  float local_4c;
  float local_3c;
  float local_2c;
  undefined4 local_28;
  uint uStack_24;
  
  if (PTR_DAT_80433934[0x45] == '\x04') {
    iVar10 = *(int *)(param_1 + 0x90);
    iVar3 = (int)(char)PTR_DAT_80433930[0x28];
    iVar4 = iVar3 * 0x3e4;
    pfVar7 = (float *)((char)(&DAT_803c7695)[iVar4] * 4);
    fVar9 = pfVar7[-0x1ff0ec5f];
    if (((((*(char *)(iVar10 + 0x88) == *(char *)((int)fVar9 + 0x88)) &&
          (*(int *)(iVar10 + 0x508) != 0)) && (*(char *)(iVar10 + 0x18) == '\x01')) &&
        ((iVar8 = *(int *)(*(int *)(iVar10 + 0x504) + 0x20),
         *(char *)(iVar8 + 0x88) != *(char *)(iVar10 + 0x88) ||
         (*(char *)(iVar10 + 0x3e4) == *(char *)((int)fVar9 + 0x3e4))))) &&
       ((*(short *)(param_1 + 0x146) != 10 ||
        (*(char *)(iVar10 + 0x3e4) == *(char *)((int)fVar9 + 0x3e4))))) {
      local_94 = *(float *)(&DAT_803c771c + iVar4);
      dVar16 = (double)local_94;
      local_90 = *(float *)(&DAT_803c772c + iVar4);
      dVar15 = (double)local_90;
      local_8c = *(float *)(&DAT_803c773c + iVar4);
      dVar14 = (double)local_8c;
      local_a0 = (float)(&DAT_803c7720)[iVar3 * 0xf9];
      local_9c = (&DAT_803c7730)[iVar3 * 0xf9];
      local_98 = (&DAT_803c7740)[iVar3 * 0xf9];
      dVar11 = gnt4_PSVECMag_bl(&local_94);
      if (((double)FLOAT_80437a50 < dVar11) &&
         (dVar11 = gnt4_PSVECMag_bl(&local_a0), (double)FLOAT_80437a50 < dVar11)) {
        pfVar7 = &local_a0;
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar7,pfVar7);
        gnt4_PSVECNormalize_bl(&local_94,&local_94);
        gnt4_PSVECNormalize_bl(&local_a0,&local_a0);
        dVar11 = gnt4_PSQUATDotProduct_bl(&local_a0,&local_94);
        if (dVar11 < (double)FLOAT_80437a50) {
          return;
        }
      }
      zz_00057f0_((float *)(param_1 + 0x20),&local_ac);
      if (*(char *)(iVar10 + 0x3e4) == *(char *)((int)fVar9 + 0x3e4)) {
        iVar3 = (int)*(short *)(param_1 + 0x144);
        bVar2 = true;
        iVar4 = *(int *)(param_1 + 0xe0);
        if ((iVar3 == 2) || (iVar3 == 5)) {
          dVar14 = (double)FLOAT_80437a5c;
          gnt4_PSMTXScale_bl(dVar14,dVar14,dVar14,afStack_58);
          local_28 = 0x43300000;
          uStack_24 = (int)*(short *)(param_1 + 0x74) ^ 0x80000000;
          gnt4_PSMTXRotRad_bl((double)(FLOAT_80437a54 *
                                      (float)((double)CONCAT44(0x43300000,uStack_24) -
                                             DOUBLE_80437a80)),afStack_58,0x7a);
        }
        else if ((iVar3 - 3U & 0xffff) < 2) {
          gnt4_PSMTXIdentity_bl(afStack_58);
        }
        else {
          local_28 = 0x43300000;
          uStack_24 = (int)*(short *)(param_1 + 0x74) ^ 0x80000000;
          gnt4_PSMTXRotRad_bl((double)(FLOAT_80437a54 *
                                      (float)((double)CONCAT44(0x43300000,uStack_24) -
                                             DOUBLE_80437a80)),afStack_58,0x7a);
        }
      }
      else {
        local_28 = 0x43300000;
        uStack_24 = 0x10000U - (int)*(short *)(param_1 + 0x74) ^ 0x80000000;
        iVar4 = *(int *)(param_1 + 0xe4);
        gnt4_PSMTXRotRad_bl((double)(FLOAT_80437a54 *
                                    (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80437a80
                                           )),afStack_58,0x7a);
        bVar2 = false;
        local_a4 = FLOAT_80437a58;
      }
      local_b8 = local_ac;
      local_b4 = local_a8;
      local_b0 = local_a4;
      if ((((bVar2) && (*(char *)(param_1 + 0x150) != '\0')) && (PTR_DAT_80433934[0x1833] == '\0'))
         && (cVar6 = zz_008b290_(), cVar6 == '\0')) {
        if (PTR_DAT_80433930[0x29] == '\x02') {
          dVar13 = (double)FLOAT_80437a60;
          dVar11 = (double)local_b8 + dVar13;
          dVar1 = (double)local_b4 + dVar13;
        }
        else {
          dVar13 = (double)FLOAT_80437a64;
          dVar11 = (double)local_b8 + dVar13;
          dVar1 = (double)local_b4 + dVar13;
        }
        local_b4 = (float)dVar1;
        local_b8 = (float)dVar11;
        uVar12 = zz_0007834_((double)local_b8,dVar13,dVar14,dVar15,dVar16,in_f6,in_f7,in_f8,
                             *(int *)(param_1 + 0xe8),&local_b8,(char *)pfVar7,param_4,param_5,
                             param_6,param_7,param_8);
        zz_0007834_(uVar12,dVar13,dVar14,dVar15,dVar16,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xec),
                    &local_b8,(char *)pfVar7,param_4,param_5,param_6,param_7,param_8);
        zz_0009958_(*(int *)(param_1 + 0xe8),1);
        zz_0009958_(*(int *)(param_1 + 0xec),1);
        if (*(char *)(param_1 + 0x160) != '\0') {
          local_b0 = local_a4;
          local_b8 = FLOAT_80437a70;
          local_b4 = FLOAT_80437a74;
          if (PTR_DAT_80433930[0x29] == '\x02') {
            local_b8 = FLOAT_80437a68;
            local_b4 = FLOAT_80437a6c;
          }
          local_b4 = local_a8 + local_b4;
          local_b8 = local_ac + local_b8;
          zz_0007834_((double)local_a8,(double)local_b8,(double)local_ac,dVar15,dVar16,in_f6,in_f7,
                      in_f8,*(int *)(param_1 + 0xf4),&local_b8,(char *)pfVar7,param_4,param_5,
                      param_6,param_7,param_8);
          zz_0009958_(*(int *)(param_1 + 0xf4),1);
        }
      }
      uVar5 = zz_0010514_((int)(char)(&DAT_803c7695)[(char)PTR_DAT_80433930[0x28] * 0x3e4]);
      if ((uVar5 == 0) || (*(char *)(iVar10 + 0x596) != '\0')) {
        dVar11 = (double)FLOAT_80437a5c;
        zz_020b520_(dVar11,(double)FLOAT_80437a78,dVar11,afStack_58,afStack_58);
        dVar14 = (double)local_ac;
        local_4c = local_ac;
        local_3c = local_a8;
        local_2c = local_a4;
        zz_00076d0_((double)local_a8,dVar14,dVar11,dVar15,dVar16,in_f6,in_f7,in_f8,iVar4,afStack_58,
                    (undefined *)pfVar7,param_4,param_5,param_6,param_7,param_8);
        uVar12 = zz_0009958_(iVar4,1);
        if ((*(char *)(iVar10 + 0x3e4) == *(char *)((int)fVar9 + 0x3e4)) &&
           ((*(char *)(param_1 + 0x151) != '\0' &&
            (*(char *)(iVar8 + 0x88) != *(char *)(iVar10 + 0x88))))) {
          if (*(short *)(param_1 + 0x144) == 9) {
            dVar14 = (double)FLOAT_80437a7c;
            dVar11 = (double)FLOAT_80437a5c;
            gnt4_PSMTXScale_bl(dVar14,dVar14,dVar11,afStack_88);
            pfVar7 = afStack_58;
            uVar12 = gnt4_PSMTXConcat_bl(pfVar7,afStack_88,pfVar7);
          }
          zz_00076d0_(uVar12,dVar14,dVar11,dVar15,dVar16,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xf0),
                      afStack_58,(undefined *)pfVar7,param_4,param_5,param_6,param_7,param_8);
          zz_0009958_(*(int *)(param_1 + 0xf0),1);
        }
      }
    }
  }
  return;
}



// ==== 80080f88  FUN_80080f88 ====

void FUN_80080f88(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  float *pfVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  char cVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  undefined8 uVar11;
  float local_48;
  float local_44;
  float local_40;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  
  iVar9 = *(int *)(param_9 + 0x90);
  pfVar2 = (float *)(int)*(char *)(iVar9 + 0x7d2);
  if ((((uint)pfVar2 & 1) != 0) && (*(char *)(iVar9 + 0x18) == '\x01')) {
    iVar3 = *(int *)(iVar9 + 0x504);
    iVar8 = *(int *)(iVar3 + 0x20);
    if (*(int *)(param_9 + 0x158) != iVar8) {
      *(int *)(param_9 + 0x158) = iVar8;
      *(undefined4 *)(param_9 + 0x15c) = 0;
      *(undefined2 *)(param_9 + 0x14c) = 0xffff;
      *(undefined2 *)(param_9 + 0x14e) = 0xffff;
    }
    uVar1 = *(undefined4 *)(iVar3 + 0x68);
    iVar6 = 0;
    iVar5 = 6;
    cVar4 = '\0';
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(iVar3 + 100);
    *(undefined4 *)(param_9 + 0x24) = uVar1;
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(iVar3 + 0x6c);
    if (((uint)pfVar2 & 2) == 0) {
      iVar6 = 3;
    }
    if (((uint)pfVar2 & 8) == 0) {
      if (((uint)pfVar2 & 4) == 0) {
        iVar5 = 7;
        iVar6 = iVar6 + 1;
      }
    }
    else {
      cVar4 = '\x01';
    }
    uVar7 = 0;
    *(undefined1 *)(param_9 + 0x150) = 0;
    *(undefined1 *)(param_9 + 0x160) = 0;
    local_48 = FLOAT_80437a8c;
    if (*(char *)(iVar8 + 0x83) == '\0') {
      param_1 = (double)*(float *)(iVar8 + 0x720);
      if (((double)FLOAT_80437a58 < param_1) || ((*(ushort *)(iVar8 + 0x272) & 2) != 0)) {
        uVar7 = 1;
      }
    }
    if (*(short *)(iVar8 + 0x1c6) < 1) {
      uVar7 = 1;
      local_40 = FLOAT_80437a5c;
      local_44 = FLOAT_80437a5c;
      if (*(int *)(param_9 + 0x15c) < 10) {
        *(undefined1 *)(param_9 + 0x150) = 1;
        param_2 = DOUBLE_80437a80;
        local_30 = 0x43300000;
        uStack_2c = 10U - *(int *)(param_9 + 0x15c) ^ 0x80000000;
        param_1 = (double)(float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80437a80);
        local_48 = (float)(param_1 / (double)FLOAT_80437a88);
        *(int *)(param_9 + 0x15c) = *(int *)(param_9 + 0x15c) + 1;
      }
      else {
        *(undefined1 *)(param_9 + 0x150) = 0;
      }
      uVar11 = zz_0007ae4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(param_9 + 0xec),&local_48,(char *)pfVar2,iVar3,in_r7,in_r8,in_r9
                           ,in_r10);
      local_48 = FLOAT_80437a8c;
      uVar11 = zz_0007ae4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(param_9 + 0xe8),&local_48,(char *)pfVar2,iVar3,in_r7,in_r8,in_r9
                           ,in_r10);
    }
    else {
      *(undefined1 *)(param_9 + 0x150) = 1;
      param_2 = DOUBLE_80437a80;
      local_38 = 0x43300000;
      local_40 = FLOAT_80437a5c;
      local_44 = FLOAT_80437a5c;
      local_30 = 0x43300000;
      *(undefined2 *)(param_9 + 0x14c) = *(undefined2 *)(iVar8 + 0x1c6);
      *(undefined2 *)(param_9 + 0x14e) = *(undefined2 *)(iVar8 + 0x1c4);
      uStack_34 = (int)*(short *)(param_9 + 0x14c) ^ 0x80000000;
      uStack_2c = (int)*(short *)(param_9 + 0x14e) ^ 0x80000000;
      dVar10 = (double)(float)((double)CONCAT44(0x43300000,uStack_34) - param_2);
      local_48 = (float)(dVar10 / (double)(float)((double)CONCAT44(0x43300000,uStack_2c) - param_2))
      ;
      uVar11 = zz_0007ae4_(dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(param_9 + 0xe8),&local_48,(char *)pfVar2,iVar3,in_r7,in_r8,in_r9
                           ,in_r10);
      local_48 = FLOAT_80437a5c;
      uVar11 = zz_0007ae4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(param_9 + 0xec),&local_48,(char *)pfVar2,iVar3,in_r7,in_r8,in_r9
                           ,in_r10);
    }
    if ((*(char *)(param_9 + 0x150) != '\0') && (*(char *)(iVar8 + 0x83) == '\0')) {
      *(undefined1 *)(param_9 + 0x160) = 1;
      pfVar2 = (float *)(int)*(char *)(iVar8 + 0x96);
      uVar11 = zz_0006fb4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           -0x7fc44bc0,*(int *)(param_9 + 0xf4),(int)pfVar2,iVar3,in_r7,in_r8,in_r9,
                           in_r10);
      local_44 = FLOAT_80437a90;
      local_48 = FLOAT_80437a90;
      uVar11 = zz_0007ae4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(param_9 + 0xf4),&local_48,(char *)pfVar2,iVar3,in_r7,in_r8,in_r9
                           ,in_r10);
    }
    if (((iVar6 == 3) || (iVar6 == 4)) && (*(char *)(iVar9 + 0x589) != '\0')) {
      iVar6 = iVar6 + 6;
    }
    if (*(short *)(param_9 + 0x144) != iVar6) {
      pfVar2 = (float *)(int)*(short *)(iVar6 * 2 + -0x7fd28e78);
      uVar11 = zz_0006fb4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_804361fc,*(int *)(param_9 + 0xe0),(int)pfVar2,iVar3,in_r7,in_r8,in_r9
                           ,in_r10);
      *(short *)(param_9 + 0x144) = (short)iVar6;
      *(undefined1 *)(param_9 + 0x148) = 0xff;
    }
    if ((int)*(char *)(param_9 + 0x148) != uVar7) {
      if (iVar6 - 3U < 2) {
        uVar11 = zz_00086b8_((double)FLOAT_80437a58,param_2,param_3,param_4,param_5,param_6,param_7,
                             param_8,DAT_804361fc,*(int *)(param_9 + 0xe0),pfVar2,iVar3,in_r7,in_r8,
                             in_r9,in_r10);
        uVar11 = zz_0007c30_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             *(int *)(param_9 + 0xe0),extraout_r4_00,pfVar2,iVar3,in_r7,in_r8,in_r9,
                             in_r10);
      }
      else {
        uStack_2c = uVar7 ^ 0x80000000;
        local_30 = 0x43300000;
        uVar11 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_2c) -
                                            DOUBLE_80437a80),param_2,param_3,param_4,param_5,param_6
                             ,param_7,param_8,DAT_804361fc,*(int *)(param_9 + 0xe0),pfVar2,iVar3,
                             in_r7,in_r8,in_r9,in_r10);
        uVar11 = zz_0007c30_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             *(int *)(param_9 + 0xe0),extraout_r4,pfVar2,iVar3,in_r7,in_r8,in_r9,
                             in_r10);
        *(char *)(param_9 + 0x148) = (char)uVar7;
      }
    }
    if (*(char *)(param_9 + 0x151) != cVar4) {
      *(undefined2 *)(param_9 + 0x154) = 0;
    }
    *(char *)(param_9 + 0x151) = cVar4;
    if (cVar4 != '\0') {
      uStack_2c = uVar7 ^ 0x80000000;
      local_30 = 0x43300000;
      uVar11 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80437a80)
                           ,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                           *(int *)(param_9 + 0xf0),pfVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
      zz_0007c30_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xf0),extraout_r4_01,pfVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
      dVar10 = zz_0045238_(*(short *)(param_9 + 0x154));
      uVar11 = zz_0007cac_((double)(float)((double)FLOAT_80437a94 * dVar10 + (double)FLOAT_80437a94)
                           ,*(int *)(param_9 + 0xf0));
    }
    if (*(short *)(param_9 + 0x146) != iVar5) {
      pfVar2 = (float *)(int)*(short *)(iVar5 * 2 + -0x7fd28e78);
      zz_0006fb4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                  *(int *)(param_9 + 0xe4),(int)pfVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
      *(short *)(param_9 + 0x146) = (short)iVar5;
      *(undefined1 *)(param_9 + 0x149) = 0xff;
    }
    if ((int)*(char *)(param_9 + 0x149) != uVar7) {
      uStack_2c = uVar7 ^ 0x80000000;
      local_30 = 0x43300000;
      uVar11 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80437a80)
                           ,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
                           *(int *)(param_9 + 0xe4),pfVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
      zz_0007c30_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xe4),extraout_r4_02,pfVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
      *(char *)(param_9 + 0x149) = (char)uVar7;
    }
    *(undefined1 *)(param_9 + 0x82) = 0x21;
  }
  return;
}



// ==== 800813a8  FUN_800813a8 ====

void FUN_800813a8(undefined4 param_1)

{
  undefined1 *puVar1;
  
  if (((PTR_DAT_80433930[0x40] == '\0') && ((char)PTR_DAT_80433934[0x45] < '\x05')) &&
     (puVar1 = zz_008893c_(2,0x38,0,1), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_80081438;
    *(code **)(puVar1 + 0x10c) = FUN_80081584;
    *(undefined4 *)(puVar1 + 0x90) = param_1;
    *(undefined4 *)(puVar1 + 0x8c) = param_1;
  }
  return;
}



// ==== 80081438  FUN_80081438 ====

void FUN_80081438(int param_1)

{
  (*(code *)(&PTR_FUN_802d71a0)[*(char *)(param_1 + 0x18)])(param_1,*(undefined4 *)(param_1 + 0x90))
  ;
  return;
}



// ==== 80081478  FUN_80081478 ====

void FUN_80081478(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  float *pfVar1;
  undefined8 uVar2;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined **)(param_9 + 0x100) = &DAT_800818cc;
  uVar2 = zz_0089100_(param_9,0x21,1);
  pfVar1 = (float *)0x38;
  zz_0006fb4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,
              *(int *)(param_9 + 0xe0),0x38,param_12,param_13,param_14,param_15,param_16);
  uVar2 = zz_00086b8_((double)FLOAT_80437a98,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                      ,DAT_804361fc,*(int *)(param_9 + 0xe0),pfVar1,param_12,param_13,param_14,
                      param_15,param_16);
  zz_0007c30_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,pfVar1,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800814e8  FUN_800814e8 ====

void FUN_800814e8(int param_1)

{
  if ((*(char *)(*(int *)(param_1 + 0x90) + 0x18) < '\x02') &&
     ((PTR_DAT_80433934[0x45] != '\x05' || ((char)PTR_DAT_80433934[0x52] < '\x02')))) {
    *(undefined1 *)(param_1 + 0x82) = 0x21;
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_0089444_(param_1);
  }
  return;
}



// ==== 80081564  FUN_80081564 ====

void FUN_80081564(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80081584  FUN_80081584 ====

void FUN_80081584(int param_1)

{
  byte bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  float *pfVar5;
  uint uVar6;
  int iVar7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar8;
  uint uVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  float local_24;
  float fStack_20;
  float local_1c;
  float local_18;
  
  if ((char)PTR_DAT_80433934[0x45] < '\x05') {
    uVar9 = *(uint *)(param_1 + 0x90);
    bVar1 = *(byte *)(uVar9 + 0x58b);
    bVar2 = false;
    iVar7 = 0;
    iVar8 = (&DAT_803c4e84)[(char)(&DAT_803c7695)[(char)PTR_DAT_80433930[0x28] * 0x3e4]];
    uVar6 = (uint)bVar1;
    if (bVar1 != 0) {
      iVar7 = 1;
      if ((((bVar1 & 1) == 0) || (uVar6 = DAT_803c4e84, DAT_803c4e84 == uVar9)) ||
         (*(char *)(DAT_803c4e84 + 0x589) == '\0')) {
        if ((((bVar1 & 2) == 0) || (uVar6 = DAT_803c4e88, DAT_803c4e88 == uVar9)) ||
           (*(char *)(DAT_803c4e88 + 0x589) == '\0')) {
          if ((((bVar1 & 4) == 0) || (uVar6 = DAT_803c4e8c, DAT_803c4e8c == uVar9)) ||
             (*(char *)(DAT_803c4e8c + 0x589) == '\0')) {
            if ((((bVar1 & 8) == 0) || (uVar6 = DAT_803c4e90, DAT_803c4e90 == uVar9)) ||
               (*(char *)(DAT_803c4e90 + 0x589) == '\0')) {
              if ((((bVar1 & 0x10) == 0) || (uVar6 = DAT_803c4e94, DAT_803c4e94 == uVar9)) ||
                 (*(char *)(DAT_803c4e94 + 0x589) == '\0')) {
                if ((((bVar1 & 0x20) != 0) && (uVar6 = DAT_803c4e98, DAT_803c4e98 != uVar9)) &&
                   (*(char *)(DAT_803c4e98 + 0x589) != '\0')) {
                  iVar7 = 0;
                }
              }
              else {
                iVar7 = 0;
              }
            }
            else {
              iVar7 = 0;
            }
          }
          else {
            iVar7 = 0;
          }
        }
        else {
          iVar7 = 0;
        }
      }
      else {
        iVar7 = 0;
      }
    }
    if ((((*(char *)(iVar8 + 0x88) == *(char *)(uVar9 + 0x88)) &&
         (*(char *)(iVar8 + 0x3e4) != *(char *)(uVar9 + 0x3e4))) && (iVar7 == 0)) &&
       ((uVar3 = zz_0010514_((int)*(char *)(param_1 + 0x96)), uVar3 == 0 ||
        (*(char *)(iVar8 + 0x596) != '\0')))) {
      *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(uVar9 + 0x8e0);
      *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(uVar9 + 0x8f0);
      *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(uVar9 + 0x900);
      iVar8 = (int)(char)PTR_DAT_80433930[0x28];
      iVar4 = iVar8 * 0x3e4;
      local_2c = *(float *)(&DAT_803c771c + iVar4);
      dVar14 = (double)local_2c;
      local_28 = *(float *)(&DAT_803c772c + iVar4);
      dVar13 = (double)local_28;
      local_24 = *(float *)(&DAT_803c773c + iVar4);
      dVar12 = (double)local_24;
      local_38 = (float)(&DAT_803c7720)[iVar8 * 0xf9];
      dVar11 = (double)local_38;
      local_34 = (&DAT_803c7730)[iVar8 * 0xf9];
      local_30 = (&DAT_803c7740)[iVar8 * 0xf9];
      dVar10 = gnt4_PSVECMag_bl(&local_2c);
      if (((double)FLOAT_80437a9c < dVar10) &&
         (dVar10 = gnt4_PSVECMag_bl(&local_38), (double)FLOAT_80437aa0 < dVar10)) {
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),&local_38,&local_38);
        gnt4_PSVECNormalize_bl(&local_2c,&local_2c);
        gnt4_PSVECNormalize_bl(&local_38,&local_38);
        dVar10 = gnt4_PSQUATDotProduct_bl(&local_38,&local_2c);
        if ((double)FLOAT_80437aa0 < dVar10) {
          bVar2 = true;
        }
      }
      if (bVar2) {
        pfVar5 = &fStack_20;
        zz_0005744_((float *)0x0,(float *)(param_1 + 0x20),pfVar5);
        dVar10 = (double)local_1c;
        local_18 = FLOAT_80437aa4;
        local_1c = (float)-dVar10;
        zz_0007834_(-dVar10,dVar11,dVar12,dVar13,dVar14,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
                    &fStack_20,(char *)pfVar5,uVar6,iVar7,in_r8,in_r9,in_r10);
        zz_0009958_(*(int *)(param_1 + 0xe0),1);
      }
    }
    return;
  }
  return;
}



// ==== 800818d0  zz_00818d0_ ====

void zz_00818d0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  piVar1 = *(int **)(PTR_DAT_80433954 + 0x18);
  if (piVar1 != (int *)0x0) {
    piVar3 = piVar1 + 1;
    for (iVar2 = *piVar1; iVar2 != 0; iVar2 = iVar2 + -1) {
      param_1 = zz_0081980_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (undefined1 *)piVar3);
      piVar3 = piVar3 + 7;
    }
    DAT_803b2908 = 0;
    DAT_803b290c = 0;
    DAT_803b2910 = 0;
    DAT_803b2914 = 0;
    DAT_803b2918 = 0;
    DAT_803b291c = 0;
    DAT_803b2920 = 0;
    DAT_803b2924 = 0;
    DAT_803b2928 = 0;
    DAT_803b292c = 0;
    DAT_803b2930 = 0;
    DAT_803b2934 = 0;
    DAT_803b2938 = 0;
    DAT_803b293c = 0;
    DAT_803b2940 = 0;
    DAT_803b2944 = 0;
  }
  return;
}



// ==== 80081980  zz_0081980_ ====

void zz_0081980_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (param_9[2] == '\0') {
    zz_0081b9c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  else {
    zz_0081d20_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  return;
}



// ==== 800819b4  zz_00819b4_ ====

undefined4
zz_00819b4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
           double param_6,double param_7,double param_8,undefined1 *param_9,undefined1 *param_10)

{
  float fVar1;
  undefined4 uVar2;
  float *pfVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  double dVar7;
  undefined8 uVar8;
  
  uVar5 = 4;
  dVar7 = (double)FLOAT_80437aa8;
  *param_9 = 1;
  param_9[0x10] = 4;
  param_9[0x83] = 0x16;
  *(code **)(param_9 + 0xc) = FUN_80081d98;
  *(code **)(param_9 + 0x10c) = FUN_800820c8;
  param_9[0x88] = 4;
  param_9[0x84] = 0xf;
  uVar2 = *(undefined4 *)(param_10 + 8);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(param_10 + 4);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(param_10 + 0xc);
  *(short *)(param_9 + 0x70) = (short)(int)(dVar7 * (double)*(float *)(param_10 + 0x10));
  *(short *)(param_9 + 0x72) = (short)(int)(dVar7 * (double)*(float *)(param_10 + 0x14));
  *(short *)(param_9 + 0x74) = (short)(int)(dVar7 * (double)*(float *)(param_10 + 0x18));
  param_9[0x11] = *param_10;
  param_9[0x12] = param_10[2];
  param_9[0x13] = param_10[1];
  param_9[0x18b] = param_10[3];
  iVar6 = (&DAT_803bb38c)[(char)param_9[0x18b] * 2];
  if (iVar6 == 0) {
    uVar2 = 0;
  }
  else {
    if (param_9[0x12] == '\0') {
      iVar4 = *(int *)(param_9 + 0xe0) + 0x18;
      uVar8 = zz_0007030_(dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                          *(int *)(param_9 + 0xe0),0,iVar4,4,in_r8,in_r9,in_r10);
      *(undefined4 *)(*(int *)(param_9 + 0xe0) + 0x18) = 0xff;
      zz_0006fb4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                  *(int *)(param_9 + 0xe4),(int)(char)param_9[0x12],iVar4,uVar5,in_r8,in_r9,in_r10);
    }
    else {
      zz_0006fb4_(dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                  *(int *)(param_9 + 0xe0),(int)(char)param_9[0x12],FUN_80081d98,4,in_r8,in_r9,
                  in_r10);
    }
    fVar1 = FLOAT_80437aac;
    *(float *)(param_9 + 0x144) = FLOAT_80437aac;
    iVar6 = 1;
    *(float *)(param_9 + 0x148) = fVar1;
    *(float *)(param_9 + 0x14c) = fVar1;
    *(float *)(param_9 + 0x150) = fVar1;
    *(float *)(param_9 + 0x154) = fVar1;
    *(float *)(param_9 + 0x158) = fVar1;
    *(float *)(param_9 + 0x15c) = fVar1;
    *(float *)(param_9 + 0x160) = fVar1;
    *(float *)(param_9 + 0x164) = fVar1;
    *(float *)(param_9 + 0x168) = fVar1;
    *(float *)(param_9 + 0x16c) = fVar1;
    *(float *)(param_9 + 0x170) = fVar1;
    pfVar3 = (float *)(param_9 + 0x174);
    do {
      *pfVar3 = fVar1;
      pfVar3 = pfVar3 + 1;
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    uVar2 = 1;
    param_9[0x18c] = 0;
  }
  return uVar2;
}



// ==== 80081b9c  zz_0081b9c_ ====

void zz_0081b9c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  char cVar1;
  float fVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar5;
  char *pcVar6;
  undefined4 uVar7;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar8;
  
  uVar7 = 2;
  puVar3 = zz_008893c_(3,0x28,0,2);
  if (puVar3 != (undefined1 *)0x0) {
    iVar4 = zz_00819b4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar3,
                        param_9);
    if (iVar4 == 0) {
      puVar3[0x18] = 2;
    }
    else {
      cVar1 = puVar3[0x11];
      *(code **)(puVar3 + 0x100) = FUN_80082060;
      iVar4 = cVar1 * 0x14;
      uVar5 = 1;
      uVar8 = zz_0089100_((int)puVar3,1,1);
      puVar3[0x18a] = 0x47;
      *(undefined4 *)(puVar3 + 0x178) = 0;
      if (puVar3[0x12] == '\0') {
        zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(puVar3 + 0xe4),extraout_r4,uVar5,uVar7,in_r7,in_r8,in_r9,in_r10);
        pcVar6 = (char *)0x0;
        uVar7 = 0;
        uVar8 = zz_0007cd0_(*(int *)(puVar3 + 0xe4),0,0,0);
        zz_0007f38_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(puVar3 + 0xe4),extraout_r4_00,pcVar6,uVar7,in_r7,in_r8,in_r9,in_r10);
        if ((&DAT_802d7994)[iVar4] != '\0') {
          zz_0007d68_(*(int *)(puVar3 + 0xe4),(int)(char)(&DAT_802d7994)[iVar4]);
        }
        fVar2 = FLOAT_80437ab0;
        *(undefined **)(puVar3 + 0x178) = (&PTR_DAT_802d799c)[cVar1 * 5];
        *(undefined4 *)(puVar3 + 0x17c) = *(undefined4 *)(&DAT_802d7998 + iVar4);
        *(float *)(puVar3 + 0x184) = fVar2;
        *(float *)(puVar3 + 0x180) = fVar2;
        *(undefined2 *)(puVar3 + 0x188) = *(undefined2 *)(&DAT_802d79a0 + iVar4);
      }
      *(undefined1 **)(puVar3 + 0x8c) = puVar3;
      fVar2 = FLOAT_80437aac;
      *(undefined4 *)(puVar3 + 0x90) = 0;
      *(float *)(puVar3 + 0xb4) = fVar2;
      *(float *)(puVar3 + 0xb8) = fVar2;
      *(float *)(puVar3 + 0x58) = fVar2;
      *(float *)(puVar3 + 0x5c) = fVar2;
      *(float *)(puVar3 + 0x60) = fVar2;
      *(float *)(puVar3 + 0xc0) = fVar2;
      *(float *)(puVar3 + 0xc4) = fVar2;
      zz_008ae10_((int)puVar3,(byte)*(undefined2 *)(&DAT_802d7992 + iVar4));
      fVar2 = FLOAT_80437ab4;
      puVar3[0x1b] = (char)*(undefined2 *)(&DAT_802d7992 + iVar4);
      *(float *)(puVar3 + 0x204) = fVar2;
      puVar3[0x281] = 1;
      puVar3[0x26f] = 1;
      *(undefined2 *)(puVar3 + 0x1c4) = *(undefined2 *)(&DAT_802d7990 + iVar4);
      *(undefined2 *)(puVar3 + 0x1c6) = *(undefined2 *)(puVar3 + 0x1c4);
      *(undefined2 *)(puVar3 + 0x1c8) = *(undefined2 *)(puVar3 + 0x1c4);
    }
  }
  return;
}



// ==== 80081d20  zz_0081d20_ ====

void zz_0081d20_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  undefined1 *puVar1;
  int iVar2;
  
  puVar1 = zz_008893c_(2,0x28,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    iVar2 = zz_00819b4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1,
                        param_9);
    if (iVar2 == 0) {
      puVar1[0x18] = 2;
    }
    else {
      FUN_80047aa4((int)puVar1);
      puVar1[0x18a] = 0xf;
    }
  }
  return;
}



// ==== 80081d98  FUN_80081d98 ====

void FUN_80081d98(int param_1)

{
  (*(code *)(&PTR_LAB_802d7ad0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80081de4  FUN_80081de4 ====

void FUN_80081de4(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  short sVar6;
  
  fVar3 = FLOAT_80437ab0;
  if (*(char *)(param_1 + 0x12) == '\0') {
    cVar1 = *(char *)(param_1 + 0x19);
    if (cVar1 == '\x01') {
      sVar6 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar6;
      if (sVar6 < 1) {
        *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x1c4);
        *(undefined2 *)(param_1 + 0x1c8) = *(undefined2 *)(param_1 + 0x1c4);
        *(undefined1 *)(param_1 + 0x82) = 1;
        *(undefined1 *)(param_1 + 0x19) = 0;
        zz_008ae10_(param_1,*(byte *)(param_1 + 0x1b));
        fVar3 = FLOAT_80437ab8;
        *(undefined1 *)(param_1 + 0x18c) = 0;
        fVar2 = FLOAT_80437abc;
        *(float *)(param_1 + 0x180) = -(fVar3 + *(float *)(param_1 + 0x17c));
        *(float *)(param_1 + 0x184) = -*(float *)(param_1 + 0x180) / fVar2;
      }
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      if (FLOAT_80437ab0 != *(float *)(param_1 + 0x184)) {
        fVar2 = *(float *)(param_1 + 0x180) + *(float *)(param_1 + 0x184);
        *(float *)(param_1 + 0x180) = fVar2;
        fVar4 = FLOAT_80437ab4;
        if (fVar2 < fVar3) {
          *(undefined1 *)(param_1 + 0x281) = 0;
          *(float *)(param_1 + 0x204) = fVar4;
        }
        else {
          *(float *)(param_1 + 0x184) = fVar3;
          *(float *)(param_1 + 0x204) = FLOAT_80437ab4;
          *(undefined1 *)(param_1 + 0x281) = 1;
          *(float *)(param_1 + 0x184) = fVar3;
          *(float *)(param_1 + 0x180) = fVar3;
          FUN_800827c0(param_1);
        }
      }
      if (*(char *)(param_1 + 0x1da) != '\0') {
        *(undefined1 *)(param_1 + 0x18c) = 4;
      }
      if (*(char *)(param_1 + 0x18c) == '\0') {
        *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0xff;
      }
      else {
        *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0xc0c0c0ff;
        *(char *)(param_1 + 0x18c) = *(char *)(param_1 + 0x18c) + -1;
      }
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_008aff0_(param_1);
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        *(undefined2 *)(param_1 + 0x1c) = 8;
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
        FUN_80082268(param_1);
        *(undefined1 *)(param_1 + 0x82) = 0;
        FUN_8008278c(param_1);
        *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x188);
        if (*(short *)(param_1 + 0x188) < 0) {
          *(undefined1 *)(param_1 + 0x18) = 2;
          *(undefined1 *)(param_1 + 0x82) = 0;
        }
        zz_00f0468_(param_1,0x73,0);
      }
    }
  }
  else {
    uVar5 = FUN_800827f4(param_1);
    if (uVar5 == 0) {
      *(undefined1 *)(param_1 + 0x82) = 1;
    }
    else {
      *(undefined1 *)(param_1 + 0x82) = 0;
    }
  }
  return;
}



// ==== 80081ff8  FUN_80081ff8 ====

void FUN_80081ff8(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  if (*(char *)(param_1 + 0x12) == '\0') {
    zz_008aff0_(param_1);
  }
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80082040  FUN_80082040 ====

void FUN_80082040(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80082060  FUN_80082060 ====

void FUN_80082060(int param_1)

{
  float local_18;
  undefined4 local_14;
  float local_10;
  
  FUN_80047aa4(param_1);
  local_10 = FLOAT_80437ab0;
  local_18 = FLOAT_80437ab0;
  local_14 = *(undefined4 *)(param_1 + 0x180);
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),&local_18,(float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  return;
}



// ==== 800820c8  FUN_800820c8 ====

void FUN_800820c8(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  
  cVar1 = zz_008b290_();
  if (cVar1 == '\0') {
    if ((char)PTR_DAT_80433930[0x28] < '\0') {
      iVar2 = *(int *)(param_9 + 0xe0);
    }
    else {
      if (*(char *)(param_9 + 0x12) == '\0') {
        iVar2 = (int)(char)PTR_DAT_80433930[0x28];
        if (((int)*(short *)(param_9 + 0x270) & 1 << iVar2) == 0) {
          iVar2 = param_9 + iVar2 * 4;
          param_1 = (double)*(float *)(iVar2 + 0x144);
          if (param_1 < (double)FLOAT_80437ac0) {
            *(float *)(iVar2 + 0x144) = (float)(param_1 + (double)FLOAT_80437ac8);
          }
          else {
            *(float *)(iVar2 + 0x144) = FLOAT_80437aac;
          }
        }
        else {
          iVar2 = param_9 + iVar2 * 4;
          param_1 = (double)*(float *)(iVar2 + 0x144);
          if (param_1 <= (double)FLOAT_80437ac0) {
            if ((double)FLOAT_80437ac4 < param_1) {
              *(float *)(iVar2 + 0x144) = (float)(param_1 - (double)FLOAT_80437ac8);
            }
            else {
              *(float *)(iVar2 + 0x144) = FLOAT_80437ac4;
            }
          }
          else {
            *(float *)(iVar2 + 0x144) = FLOAT_80437ac0;
          }
        }
      }
      iVar2 = *(int *)(param_9 + 0xe4);
      if ((iVar2 == 0) ||
         (param_1 = (double)*(float *)(param_9 + (char)PTR_DAT_80433930[0x28] * 4 + 0x144),
         (double)FLOAT_80437aac == param_1)) {
        iVar2 = *(int *)(param_9 + 0xe0);
        if (iVar2 != 0) {
          param_1 = (double)zz_0007cac_((double)*(float *)(param_9 + (char)PTR_DAT_80433930[0x28] *
                                                                     4 + 0x144),iVar2);
        }
      }
      else {
        param_1 = (double)zz_0007cac_(param_1,iVar2);
      }
    }
    if (iVar2 != 0) {
      zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                  (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
      if (PTR_DAT_80433934[0x45] == '\x01') {
        *(undefined1 *)(iVar2 + 0xb) = 1;
      }
      else {
        *(undefined1 *)(iVar2 + 0xb) = 0;
      }
      zz_00097b4_(iVar2,(uint)*(byte *)(param_9 + 0x18a));
    }
  }
  return;
}



// ==== 80082268  FUN_80082268 ====

void FUN_80082268(int param_1)

{
  undefined1 *puVar1;
  char cVar2;
  int *piVar3;
  
  cVar2 = '\0';
  for (piVar3 = *(int **)(param_1 + 0x178); (piVar3 != (int *)0x0 && (-1 < *piVar3));
      piVar3 = piVar3 + 6) {
    puVar1 = zz_008893c_(2,0x28,1,2);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x10] = 4;
      *(code **)(puVar1 + 0xc) = FUN_80082334;
      *(code **)(puVar1 + 0x10c) = FUN_8008270c;
      puVar1[0x88] = 4;
      puVar1[0x84] = 0xf;
      *(int *)(puVar1 + 0x8c) = param_1;
      *(int **)(puVar1 + 0x54) = piVar3;
      puVar1[0x11] = *(undefined1 *)(param_1 + 0x11);
      puVar1[0x12] = *(undefined1 *)(param_1 + 0x18b);
      puVar1[0x13] = cVar2;
    }
    cVar2 = cVar2 + '\x01';
  }
  return;
}



// ==== 80082334  FUN_80082334 ====

void FUN_80082334(int param_1)

{
  (*(code *)(&PTR_FUN_802d7ae0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80082370  FUN_80082370 ====

void FUN_80082370(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined4 uVar2;
  bool bVar4;
  uint uVar3;
  undefined4 extraout_r4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  int *piVar7;
  double dVar8;
  undefined8 uVar9;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar6 = *(int *)(param_9 + 0x8c);
  *(undefined1 *)(param_9 + 0x84) = 0xf;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0,1);
  piVar7 = *(int **)(param_9 + 0x54);
  gnt4_PSMTXMultVec_bl((float *)(iVar6 + 0x114),(float *)(piVar7 + 1),(float *)(param_9 + 100));
  *(short *)(param_9 + 0x70) = *(short *)(iVar6 + 0x70) + *(short *)(piVar7 + 4);
  *(short *)(param_9 + 0x72) = *(short *)(iVar6 + 0x72) + *(short *)((int)piVar7 + 0x12);
  iVar5 = (int)*(short *)(iVar6 + 0x74);
  *(short *)(param_9 + 0x74) = *(short *)(iVar6 + 0x74) + *(short *)(piVar7 + 5);
  gnt4_PSVECSubtract_bl((float *)(param_9 + 100),(float *)(iVar6 + 0x20),(float *)(param_9 + 0x38));
  dVar8 = gnt4_PSVECMag_bl((float *)(param_9 + 0x38));
  uVar1 = DAT_802b0cb8;
  if (dVar8 < DOUBLE_80437ad0) {
    *(undefined4 *)(param_9 + 0x38) = DAT_802b0cb4;
    uVar2 = DAT_802b0cbc;
    *(undefined4 *)(param_9 + 0x3c) = uVar1;
    *(undefined4 *)(param_9 + 0x40) = uVar2;
  }
  bVar4 = zz_004538c_((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  uVar1 = DAT_802b0cb8;
  if (bVar4) {
    *(undefined4 *)(param_9 + 0x38) = DAT_802b0cb4;
    uVar2 = DAT_802b0cbc;
    *(undefined4 *)(param_9 + 0x3c) = uVar1;
    *(undefined4 *)(param_9 + 0x40) = uVar2;
  }
  uVar3 = zz_00055fc_();
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802d7af0 + (uVar3 & 7) * 4),(float *)(param_9 + 0x38),
                      (float *)(param_9 + 0x38));
  *(float *)(param_9 + 0x4c) = (float)(-(double)*(float *)(param_9 + 0x3c) / (double)FLOAT_80437ad8)
  ;
  uVar9 = zz_0006fb4_(-(double)*(float *)(param_9 + 0x3c),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,(&DAT_803bb38c)[*(char *)(param_9 + 0x12) * 2],
                      *(int *)(param_9 + 0xe0),*piVar7,iVar5,in_r7,in_r8,in_r9,in_r10);
  iVar6 = *piVar7;
  uVar9 = zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (&DAT_803bb38c)[*(char *)(param_9 + 0x12) * 2],*(int *)(param_9 + 0xe4),iVar6,
                      iVar5,in_r7,in_r8,in_r9,in_r10);
  zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar6,iVar5,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80437adc,*(int *)(param_9 + 0xe4));
  *(undefined1 *)(param_9 + 0x82) = 1;
  *(undefined2 *)(param_9 + 0x1c) = 500;
  *(undefined2 *)(param_9 + 0x1e) = 0;
  return;
}



// ==== 80082534  FUN_80082534 ====

/* WARNING: Removing unreachable block (ram,0x800826b8) */
/* WARNING: Removing unreachable block (ram,0x80082544) */

void FUN_80082534(int param_1)

{
  char cVar1;
  int iVar2;
  short sVar3;
  double dVar4;
  double dVar5;
  float afStack_38 [3];
  float local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    sVar3 = *(short *)(param_1 + 0x1e) + -1;
    *(short *)(param_1 + 0x1e) = sVar3;
    if (sVar3 < 1) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x82) = 0;
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    gnt4_PSVECAdd_bl((float *)(param_1 + 100),(float *)(param_1 + 0x38),(float *)(param_1 + 100));
    *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) + *(float *)(param_1 + 0x4c);
    if ((*(byte *)(param_1 + 0x13) & 1) == 0) {
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x1000;
    }
    else {
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x1000;
    }
    *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0x400;
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x400;
    iVar2 = zz_003ecb8_((float *)(param_1 + 100),(float *)(param_1 + 0x2c),&local_2c,afStack_38);
    if (iVar2 != 0) {
      dVar5 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
      dVar4 = (double)FLOAT_80437ac0;
      *(float *)(param_1 + 100) = local_2c;
      dVar4 = (double)(float)(dVar5 * dVar4);
      *(undefined4 *)(param_1 + 0x68) = local_28;
      *(undefined4 *)(param_1 + 0x6c) = local_24;
      zz_020bbb4_((float *)(param_1 + 0x38),afStack_38,&local_2c);
      gnt4_PSQUATScale_bl(dVar4,&local_2c,(float *)(param_1 + 0x38));
      if ((iVar2 == 1) &&
         (sVar3 = *(short *)(param_1 + 0x1e) + 1, *(short *)(param_1 + 0x1e) = sVar3, 1 < sVar3)) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        *(undefined2 *)(param_1 + 0x1e) = 0x1e;
      }
    }
  }
  sVar3 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar3;
  if (sVar3 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 800826ec  FUN_800826ec ====

void FUN_800826ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8008270c  FUN_8008270c ====

void FUN_8008270c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined *param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if ((param_9[0x19] == '\0') ||
     (((int)*(short *)(param_9 + 0x1c) &
      1U - ((-(int)(char)PTR_DAT_80433930[0x29] | (int)(char)PTR_DAT_80433930[0x29]) >> 0x1f)) != 0)
     ) {
    iVar1 = *(int *)(param_9 + 0xe0);
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_9,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,0x45);
  return;
}



// ==== 8008278c  FUN_8008278c ====

void FUN_8008278c(int param_1)

{
  (&DAT_803b2908)[*(char *)(param_1 + 0x11)] =
       (&DAT_803b2908)[*(char *)(param_1 + 0x11)] | 1 << (int)*(char *)(param_1 + 0x13);
  return;
}



// ==== 800827c0  FUN_800827c0 ====

void FUN_800827c0(int param_1)

{
  (&DAT_803b2908)[*(char *)(param_1 + 0x11)] =
       (&DAT_803b2908)[*(char *)(param_1 + 0x11)] & ~(1 << (int)*(char *)(param_1 + 0x13));
  return;
}



// ==== 800827f4  FUN_800827f4 ====

uint FUN_800827f4(int param_1)

{
  return 1 << (int)*(char *)(param_1 + 0x13) & (&DAT_803b2908)[*(char *)(param_1 + 0x11)];
}



// ==== 80082824  zz_0082824_ ====

void zz_0082824_(int param_1,uint param_2)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = (param_2 & 0xff) * 0x38;
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0;
    *(uint *)(puVar1 + 0x14) = param_2;
    puVar1[0x12] = 0;
    *(code **)(puVar1 + 0xc) = FUN_80082ab8;
    *(code **)(puVar1 + 0x10c) = FUN_800831dc;
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
    *(float *)(puVar1 + 0x58) = *(float *)(puVar1 + 0xb4) * *(float *)(&DAT_802d7b30 + iVar2);
    *(float *)(puVar1 + 0x5c) = *(float *)(puVar1 + 0xb4) * *(float *)(&DAT_802d7b34 + iVar2);
    *(float *)(puVar1 + 0x60) = *(float *)(puVar1 + 0xb4) * *(float *)(&DAT_802d7b38 + iVar2);
  }
  return;
}



// ==== 8008296c  zz_008296c_ ====

void zz_008296c_(int param_1,uint param_2)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = (param_2 & 0xff) * 0x38;
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0;
    *(uint *)(puVar1 + 0x14) = param_2;
    puVar1[0x12] = 1;
    *(code **)(puVar1 + 0xc) = FUN_80082ab8;
    *(code **)(puVar1 + 0x10c) = FUN_800831dc;
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
    *(float *)(puVar1 + 0x58) = *(float *)(puVar1 + 0xb4) * *(float *)(&DAT_802d7b30 + iVar2);
    *(float *)(puVar1 + 0x5c) = *(float *)(puVar1 + 0xb4) * *(float *)(&DAT_802d7b34 + iVar2);
    *(float *)(puVar1 + 0x60) = *(float *)(puVar1 + 0xb4) * *(float *)(&DAT_802d7b38 + iVar2);
  }
  return;
}



// ==== 80082ab8  FUN_80082ab8 ====

void FUN_80082ab8(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_802d9748)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80082b08  FUN_80082b08 ====

void FUN_80082b08(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  ushort uVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  int iVar7;
  double dVar8;
  undefined8 uVar9;
  float local_28;
  float local_24;
  float local_20;
  
  iVar7 = *(int *)(param_9 + 0x90);
  iVar6 = *(int *)(param_9 + 0x8c);
  iVar5 = (*(uint *)(param_9 + 0x14) & 0xff) * 0x38;
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  *(undefined1 *)(param_9 + 0x98) = 5;
  if (*(char *)(param_9 + 0x12) == '\0') {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar7 + (char)(&DAT_802d7b12)[iVar5] * 0x30 + 0x8d4),
               (float *)(iVar5 + -0x7fd284ec),(float *)(param_9 + 0x20));
    *(undefined4 *)(param_9 + 0x38) =
         *(undefined4 *)
          (iVar7 + (char)(&DAT_802d7b12)[iVar5] * 0x30 + (char)(&DAT_802d7b40)[iVar5] * 4 + 0x8d4);
    *(undefined4 *)(param_9 + 0x3c) =
         *(undefined4 *)
          (iVar7 + (char)(&DAT_802d7b12)[iVar5] * 0x30 + (char)(&DAT_802d7b40)[iVar5] * 4 + 0x8e4);
    *(undefined4 *)(param_9 + 0x40) =
         *(undefined4 *)
          (iVar7 + (char)(&DAT_802d7b12)[iVar5] * 0x30 + (char)(&DAT_802d7b40)[iVar5] * 4 + 0x8f4);
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar6 + 0x114),(float *)(iVar5 + -0x7fd284ec),(float *)(param_9 + 0x20));
    *(undefined4 *)(param_9 + 0x38) =
         *(undefined4 *)(iVar6 + (char)(&DAT_802d7b40)[iVar5] * 4 + 0x114);
    *(undefined4 *)(param_9 + 0x3c) =
         *(undefined4 *)(iVar6 + (char)(&DAT_802d7b40)[iVar5] * 4 + 0x124);
    *(undefined4 *)(param_9 + 0x40) =
         *(undefined4 *)(iVar6 + (char)(&DAT_802d7b40)[iVar5] * 4 + 0x134);
  }
  if ((&DAT_802d7b41)[iVar5] == '\x01') {
    gnt4_PSQUATScale_bl((double)FLOAT_80437ae0,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  }
  bVar3 = true;
  if (*(char *)(param_9 + 0x12) == '\0') {
    if ((*(int *)(iVar7 + 200) != 0) &&
       (iVar4 = FUN_8006c334((double)*(float *)(&DAT_802d7b3c + iVar5),param_9,
                             (float *)(iVar7 + 0x518)), iVar4 != 0)) {
      zz_0083d60_(param_9,iVar7,(int)(char)(&DAT_802d7b12)[iVar5]);
      bVar3 = false;
    }
  }
  else if ((*(int *)(param_9 + 200) != 0) &&
          (iVar4 = FUN_8006c334((double)*(float *)(&DAT_802d7b3c + iVar5),param_9,
                                (float *)(*(int *)(param_9 + 200) + 100)), iVar4 != 0)) {
    zz_0083f5c_(param_9,(float *)(*(int *)(param_9 + 200) + 100));
    bVar3 = false;
  }
  if (bVar3) {
    *(undefined4 *)(param_9 + 200) = 0;
    cVar1 = (&DAT_802d7b43)[iVar5];
    if (cVar1 == '\x02') {
      gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),&local_28);
      local_24 = FLOAT_80437ae4;
      dVar8 = gnt4_PSVECSquareMag_bl(&local_28);
      if ((double)FLOAT_80437ae4 < dVar8) {
        *(float *)(param_9 + 0x38) = local_28;
        *(float *)(param_9 + 0x3c) = local_24;
        *(float *)(param_9 + 0x40) = local_20;
      }
    }
    else if (cVar1 < '\x02') {
      if ((cVar1 != '\0') && (-1 < cVar1)) {
        gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),&local_28);
        local_28 = FLOAT_80437ae4;
        dVar8 = gnt4_PSVECSquareMag_bl(&local_28);
        if ((double)FLOAT_80437ae4 < dVar8) {
          *(float *)(param_9 + 0x38) = local_28;
          *(float *)(param_9 + 0x3c) = local_24;
          *(float *)(param_9 + 0x40) = local_20;
        }
      }
    }
    else if (cVar1 < '\x04') {
      gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),&local_28);
      local_20 = FLOAT_80437ae4;
      dVar8 = gnt4_PSVECSquareMag_bl(&local_28);
      if ((double)FLOAT_80437ae4 < dVar8) {
        *(float *)(param_9 + 0x38) = local_28;
        *(float *)(param_9 + 0x3c) = local_24;
        *(float *)(param_9 + 0x40) = local_20;
      }
    }
  }
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  uVar9 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802d7b20 + iVar5),(float *)(param_9 + 0x38),
                              (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_802d7b20 + iVar5);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined4 *)(&DAT_802d7b24 + iVar5);
  if (*(char *)(param_9 + 0x12) == '\0') {
    *(undefined4 *)(param_9 + 0x9c) =
         *(undefined4 *)(iVar7 + (char)(&DAT_802d7b12)[iVar5] * 0x30 + 0x8d8);
    *(undefined4 *)(param_9 + 0xa0) =
         *(undefined4 *)(iVar7 + (char)(&DAT_802d7b12)[iVar5] * 0x30 + 0x8e8);
    *(undefined4 *)(param_9 + 0xa4) =
         *(undefined4 *)(iVar7 + (char)(&DAT_802d7b12)[iVar5] * 0x30 + 0x8f8);
  }
  else {
    *(undefined4 *)(param_9 + 0x9c) = *(undefined4 *)(iVar6 + 0x118);
    *(undefined4 *)(param_9 + 0xa0) = *(undefined4 *)(iVar6 + 0x128);
    *(undefined4 *)(param_9 + 0xa4) = *(undefined4 *)(iVar6 + 0x138);
  }
  if (-1 < (char)(&DAT_802d7b42)[iVar5]) {
    uVar9 = zz_0048288_(param_9);
    zz_00aedc0_(iVar7,(float *)(param_9 + 0x114),(int)(char)(&DAT_802d7b42)[iVar5],
                *(undefined1 *)(param_9 + 0x88));
  }
  *(undefined2 *)(param_9 + 0x1c) = 300;
  *(undefined2 *)(param_9 + 0x80) = 0x1400;
  iVar4 = zz_008ac80_(param_9,(int)(char)(&DAT_802d7b13)[iVar5]);
  if (iVar4 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    uVar2 = *(ushort *)(&DAT_802d7b10 + iVar5);
    if ((uVar2 & 0x4000) == 0) {
      zz_000726c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                  *(int *)(param_9 + 0xe0),(float *)(uint)uVar2,(int)*(char *)(param_9 + 0x88),in_r7
                  ,in_r8,in_r9,in_r10);
      *(undefined1 *)(param_9 + 0x144) = 0;
      *(undefined1 *)(param_9 + 0x82) = 1;
    }
    else {
      iVar4 = zz_0006f78_(iVar7);
      zz_000726c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                  *(int *)(param_9 + 0xe0),(float *)(uVar2 & 0xffffbfff),
                  (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
      *(undefined1 *)(param_9 + 0x144) = 1;
      *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    }
    if (*(char *)(param_9 + 0x12) == '\0') {
      zz_00f036c_(iVar7,(int)*(short *)(&DAT_802d7b44 + iVar5));
    }
    else {
      zz_00f036c_(iVar6,(int)*(short *)(&DAT_802d7b44 + iVar5));
    }
  }
  return;
}



// ==== 80082fc4  FUN_80082fc4 ====

void FUN_80082fc4(int param_1)

{
  int iVar1;
  undefined4 auStack_28 [3];
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  if (*(short *)(param_1 + 0x1c) < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    iVar1 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar1 == 0) {
      if (*(char *)(param_1 + 0x1d9) == '\0') {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x80);
        iVar1 = (*(uint *)(param_1 + 0x14) & 0xff) * 0x38;
        FUN_80083874((double)*(float *)(&DAT_802d7b2c + iVar1),param_1);
        FUN_80083ad4((double)*(float *)(&DAT_802d7b28 + iVar1),param_1,
                     (char)*(undefined4 *)(&DAT_802d7b24 + iVar1));
        zz_00833ec_(param_1);
        zz_0083524_(param_1);
        *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0xb4) * *(float *)(&DAT_802d7b30 + iVar1);
        *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0xb4) * *(float *)(&DAT_802d7b34 + iVar1);
        *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0xb4) * *(float *)(&DAT_802d7b38 + iVar1);
        iVar1 = zz_0083714_(param_1);
        if (iVar1 == 0) {
          iVar1 = zz_003ecb8_((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),&local_1c,
                              auStack_28);
          if (iVar1 != 0) {
            *(float *)(param_1 + 0x20) = local_1c;
            *(undefined4 *)(param_1 + 0x24) = local_18;
            *(undefined4 *)(param_1 + 0x28) = local_14;
            FUN_8001b9ac((double)*(float *)(param_1 + 0xb4),&local_1c,auStack_28);
            zz_0019550_(param_1,&local_1c,0);
            *(undefined1 *)(param_1 + 0x18) = 2;
          }
        }
        else {
          *(undefined1 *)(param_1 + 0x18) = 2;
          zz_008aff0_(param_1);
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x18) = 2;
        zz_008aff0_(param_1);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
    }
  }
  return;
}



// ==== 80083180  FUN_80083180 ====

void FUN_80083180(int param_1)

{
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800831bc  FUN_800831bc ====

void FUN_800831bc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800831dc  FUN_800831dc ====

/* WARNING: Removing unreachable block (ram,0x800831f0) */

void FUN_800831dc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  float afStack_38 [13];
  
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437ae8 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x74) *
                                             0x3ff0000000000000)),afStack_38,0x7a);
  pfVar1 = afStack_38;
  uVar2 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 80083244  zz_0083244_ ====

undefined4 zz_0083244_(float *param_1)

{
  if ((((*(float *)(DAT_8043625c + 0x3c) - FLOAT_80437aec <= *param_1) &&
       (*param_1 <= FLOAT_80437aec + *(float *)(DAT_8043625c + 0x38))) &&
      (*(float *)(DAT_8043625c + 0x44) - FLOAT_80437aec <= param_1[2])) &&
     (((param_1[2] <= FLOAT_80437aec + *(float *)(DAT_8043625c + 0x40) &&
       (param_1[1] <= FLOAT_80437aec + *(float *)(DAT_8043625c + 0x34))) &&
      (FLOAT_80437af0 <= param_1[1])))) {
    return 0;
  }
  return 1;
}



// ==== 800832c4  zz_00832c4_ ====

undefined4 zz_00832c4_(float *param_1)

{
  if ((((*(float *)(DAT_8043625c + 0x3c) - FLOAT_80437aec <= *param_1) &&
       (*param_1 <= FLOAT_80437aec + *(float *)(DAT_8043625c + 0x38))) &&
      (*(float *)(DAT_8043625c + 0x44) - FLOAT_80437aec <= param_1[2])) &&
     ((param_1[2] <= FLOAT_80437aec + *(float *)(DAT_8043625c + 0x40) &&
      (FLOAT_80437af4 <= param_1[1])))) {
    return 0;
  }
  return 1;
}



// ==== 80083334  zz_0083334_ ====

undefined4 zz_0083334_(float *param_1)

{
  if ((((*(float *)(DAT_8043625c + 0x3c) - FLOAT_80437af8 <= *param_1) &&
       (*param_1 <= FLOAT_80437af8 + *(float *)(DAT_8043625c + 0x38))) &&
      (*(float *)(DAT_8043625c + 0x44) - FLOAT_80437af8 <= param_1[2])) &&
     ((param_1[2] <= FLOAT_80437af8 + *(float *)(DAT_8043625c + 0x40) &&
      (FLOAT_80437af4 <= param_1[1])))) {
    return 0;
  }
  return 1;
}



// ==== 800833a4  zz_00833a4_ ====

void zz_00833a4_(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 200) != 0) {
    iVar1 = *(int *)(param_1 + 0xcc);
    if ((iVar1 != 0) && (*(char *)(iVar1 + 0x83) == '\0')) {
      zz_006d228_(param_1,iVar1,1);
    }
  }
  return;
}



// ==== 800833ec  zz_00833ec_ ====

void zz_00833ec_(int param_1)

{
  float fVar1;
  
  if (((*(byte *)(param_1 + 0xb1) & 4) == 0) && ((*(byte *)(param_1 + 0xb1) & 8) == 0)) {
    return;
  }
  fVar1 = *(float *)(param_1 + 0xb4);
  if (*(float *)(param_1 + 0xb8) != fVar1) {
    if (*(float *)(param_1 + 0xb8) <= fVar1) {
      *(float *)(param_1 + 0xb4) = fVar1 - FLOAT_80437afc;
      if (*(float *)(param_1 + 0xb4) <= *(float *)(param_1 + 0xb8)) {
        *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0xb8);
      }
    }
    else {
      *(float *)(param_1 + 0xb4) = fVar1 + FLOAT_80437afc;
      if (*(float *)(param_1 + 0xb8) <= *(float *)(param_1 + 0xb4)) {
        *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0xb8);
      }
    }
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0xc4) = *(undefined4 *)(param_1 + 0xb4);
    return;
  }
  *(byte *)(param_1 + 0xb1) = *(byte *)(param_1 + 0xb1) & 0xfb;
  *(byte *)(param_1 + 0xb1) = *(byte *)(param_1 + 0xb1) & 0xf7;
  return;
}



// ==== 800834b0  zz_00834b0_ ====

void zz_00834b0_(int param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  
  if ((*(byte *)(param_1 + 0xb1) & 0xc) == 0) {
    return;
  }
  fVar1 = *param_2;
  fVar2 = *(float *)(param_1 + 0xb8);
  if (fVar1 < fVar2) {
    fVar1 = fVar1 + FLOAT_80437afc;
    *param_2 = fVar1;
    if (fVar1 < fVar2) {
      return;
    }
    *param_2 = *(float *)(param_1 + 0xb8);
    return;
  }
  if (fVar1 <= fVar2) {
    *(byte *)(param_1 + 0xb1) = *(byte *)(param_1 + 0xb1) & 0xf3;
    return;
  }
  fVar1 = fVar1 - FLOAT_80437afc;
  *param_2 = fVar1;
  if (fVar2 < fVar1) {
    return;
  }
  *param_2 = *(float *)(param_1 + 0xb8);
  return;
}



// ==== 80083524  zz_0083524_ ====

void zz_0083524_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80437ae4;
  if ((*(byte *)(param_1 + 0xb1) & 1) != 0) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437b00;
    fVar1 = *(float *)(param_1 + 0x44);
    if (fVar1 < fVar2) {
      if (fVar1 <= *(float *)(param_1 + 0xbc)) {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0xbc);
        *(byte *)(param_1 + 0xb1) = *(byte *)(param_1 + 0xb1) & 0xfe;
      }
    }
    else if (*(float *)(param_1 + 0xbc) <= fVar1) {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0xbc);
      *(byte *)(param_1 + 0xb1) = *(byte *)(param_1 + 0xb1) & 0xfe;
    }
  }
  fVar2 = FLOAT_80437ae4;
  if ((*(byte *)(param_1 + 0xb1) & 2) == 0) {
    return;
  }
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437b04;
  fVar1 = *(float *)(param_1 + 0x44);
  if (fVar1 < fVar2) {
    if (fVar1 < *(float *)(param_1 + 0xbc)) {
      return;
    }
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0xbc);
    *(byte *)(param_1 + 0xb1) = *(byte *)(param_1 + 0xb1) & 0xfd;
    return;
  }
  if (*(float *)(param_1 + 0xbc) < fVar1) {
    return;
  }
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0xbc);
  *(byte *)(param_1 + 0xb1) = *(byte *)(param_1 + 0xb1) & 0xfd;
  return;
}



// ==== 80083610  zz_0083610_ ====

void zz_0083610_(int param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  
  fVar1 = FLOAT_80437b00;
  fVar2 = FLOAT_80437ae4;
  if ((*(byte *)(param_1 + 0xb1) & 1) != 0) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437b00;
    *param_2 = *param_2 * fVar1;
    fVar1 = *(float *)(param_1 + 0x44);
    if (fVar1 < fVar2) {
      if (fVar1 <= *(float *)(param_1 + 0xbc)) {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0xbc);
        *(byte *)(param_1 + 0xb1) = *(byte *)(param_1 + 0xb1) & 0xfe;
      }
    }
    else if (*(float *)(param_1 + 0xbc) <= fVar1) {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0xbc);
      *(byte *)(param_1 + 0xb1) = *(byte *)(param_1 + 0xb1) & 0xfe;
    }
  }
  fVar1 = FLOAT_80437b04;
  fVar2 = FLOAT_80437ae4;
  if ((*(byte *)(param_1 + 0xb1) & 2) == 0) {
    return;
  }
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80437b04;
  *param_2 = *param_2 * fVar1;
  fVar1 = *(float *)(param_1 + 0x44);
  if (fVar1 < fVar2) {
    if (fVar1 < *(float *)(param_1 + 0xbc)) {
      return;
    }
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0xbc);
    *(byte *)(param_1 + 0xb1) = *(byte *)(param_1 + 0xb1) & 0xfd;
    return;
  }
  if (*(float *)(param_1 + 0xbc) < fVar1) {
    return;
  }
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0xbc);
  *(byte *)(param_1 + 0xb1) = *(byte *)(param_1 + 0xb1) & 0xfd;
  return;
}



// ==== 80083714  zz_0083714_ ====

undefined4 zz_0083714_(int param_1)

{
  bool bVar1;
  float fVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  float local_28;
  float local_24;
  float local_20;
  float afStack_1c [3];
  
  iVar6 = 0;
  iVar5 = 0;
  bVar1 = false;
  local_28 = FLOAT_80437ae4;
  local_24 = FLOAT_80437ae4;
  local_20 = FLOAT_80437ae4;
  do {
    if ((PTR_DAT_80433934[iVar5 + 0x60] != '\0') &&
       (((cVar3 = zz_008b480_(), cVar3 == '\0' ||
         (bVar4 = zz_008b480_(), (1 << iVar5 & (uint)bVar4) != 0)) &&
        (*(int *)(PTR_DAT_80433934 + iVar6 + 0x68) != 0)))) {
      gnt4_PSVECSubtract_bl
                ((float *)(*(int *)(PTR_DAT_80433934 + iVar6 + 0x68) + 0x20),
                 (float *)(param_1 + 0x20),afStack_1c);
      dVar7 = gnt4_PSVECMag_bl(afStack_1c);
      fVar2 = FLOAT_80437b10;
      if (dVar7 <= (double)FLOAT_80437b08) {
        return 1;
      }
      if ((!bVar1) &&
         (*(float *)(param_1 + 0x29c) = *(float *)(param_1 + 0x29c) + FLOAT_80437b0c,
         fVar2 <= *(float *)(param_1 + 0x29c))) {
        *(float *)(param_1 + 0x29c) = fVar2;
      }
      bVar1 = true;
      gnt4_PSVECNormalize_bl(afStack_1c,afStack_1c);
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x29c),afStack_1c,afStack_1c);
      gnt4_PSVECAdd_bl(&local_28,afStack_1c,&local_28);
    }
    iVar5 = iVar5 + 1;
    iVar6 = iVar6 + 4;
  } while (iVar5 < 6);
  if (bVar1) {
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),&local_28,(float *)(param_1 + 0x20));
  }
  return 0;
}



// ==== 80083874  FUN_80083874 ====

/* WARNING: Removing unreachable block (ram,0x80083ab4) */
/* WARNING: Removing unreachable block (ram,0x80083aac) */
/* WARNING: Removing unreachable block (ram,0x8008388c) */
/* WARNING: Removing unreachable block (ram,0x80083884) */

uint FUN_80083874(double param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  iVar3 = *(int *)(param_2 + 200);
  if (iVar3 == 0) {
    return 1;
  }
  pcVar2 = *(char **)(param_2 + 0xcc);
  if (((pcVar2 == (char *)0x0) || (*pcVar2 == '\0')) ||
     ((pcVar2[0x83] == '\0' && (pcVar2[0x656] != '\0')))) {
    *(undefined4 *)(param_2 + 200) = 0;
    return 1;
  }
  dVar4 = gnt4_PSVECSquareDistance_bl((float *)(iVar3 + 100),(float *)(param_2 + 0x20));
  if ((double)FLOAT_80437ae4 < dVar4) {
    dVar5 = 1.0 / SQRT(dVar4);
    dVar5 = DOUBLE_80437b18 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80437b20);
    dVar5 = DOUBLE_80437b18 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80437b20);
    dVar4 = (double)(float)(dVar4 * DOUBLE_80437b18 * dVar5 *
                                    -(dVar4 * dVar5 * dVar5 - DOUBLE_80437b20));
  }
  iVar1 = *(int *)(iVar3 + 0x58);
  if (iVar1 == 3) {
    dVar5 = gnt4_PSVECSquareDistance_bl((float *)(iVar3 + 100),(float *)(iVar3 + 0x8c));
    if ((double)FLOAT_80437ae4 < dVar5) {
      dVar6 = 1.0 / SQRT(dVar5);
      dVar6 = DOUBLE_80437b18 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80437b20);
      dVar6 = DOUBLE_80437b18 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80437b20);
      dVar5 = (double)(float)(dVar5 * DOUBLE_80437b18 * dVar6 *
                                      -(dVar5 * dVar6 * dVar6 - DOUBLE_80437b20));
    }
    dVar4 = (double)(float)(dVar4 - dVar5);
    goto LAB_80083a8c;
  }
  if (iVar1 < 3) {
    if (iVar1 == 1) {
      dVar5 = gnt4_PSVECSquareDistance_bl((float *)(iVar3 + 100),(float *)(iVar3 + 0x88));
      if ((double)FLOAT_80437ae4 < dVar5) {
        dVar6 = 1.0 / SQRT(dVar5);
        dVar6 = DOUBLE_80437b18 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80437b20);
        dVar6 = DOUBLE_80437b18 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80437b20);
        dVar5 = (double)(float)(dVar5 * DOUBLE_80437b18 * dVar6 *
                                        -(dVar5 * dVar6 * dVar6 - DOUBLE_80437b20));
      }
      dVar4 = (double)(float)(dVar4 - dVar5);
      goto LAB_80083a8c;
    }
    if (iVar1 < 1) {
      if (-1 < iVar1) {
        dVar4 = (double)(float)(dVar4 - (double)*(float *)(iVar3 + 0x88));
      }
      goto LAB_80083a8c;
    }
  }
  else if (iVar1 != 5) {
    if (iVar1 < 5) {
      dVar4 = (double)(float)(dVar4 - (double)*(float *)(iVar3 + 0xa4));
    }
    goto LAB_80083a8c;
  }
  dVar4 = (double)(float)(dVar4 - (double)*(float *)(iVar3 + 0x88));
LAB_80083a8c:
  if (dVar4 <= param_1) {
    *(undefined4 *)(param_2 + 200) = 0;
  }
  return (uint)(dVar4 <= param_1);
}



// ==== 80083ad4  FUN_80083ad4 ====

/* WARNING: Removing unreachable block (ram,0x80083b84) */
/* WARNING: Removing unreachable block (ram,0x80083ae4) */

void FUN_80083ad4(double param_1,int param_2,undefined1 param_3)

{
  gnt4_PSVECNormalize_bl((float *)(param_2 + 0x38),(float *)(param_2 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x44),(float *)(param_2 + 0x38),
                      (float *)(param_2 + 0x38));
  if (*(int *)(param_2 + 200) == 0) {
    gnt4_PSVECAdd_bl((float *)(param_2 + 0x20),(float *)(param_2 + 0x38),(float *)(param_2 + 0x20));
  }
  else {
    *(char *)(param_2 + 0x1cb) = *(char *)(param_2 + 0x1cb) + -1;
    if (*(char *)(param_2 + 0x1cb) < '\x01') {
      *(undefined1 *)(param_2 + 0x1cb) = param_3;
      zz_006c440_(param_1,param_2,(float *)(*(int *)(param_2 + 200) + 100));
      zz_00833a4_(param_2);
    }
    else {
      gnt4_PSVECAdd_bl((float *)(param_2 + 0x20),(float *)(param_2 + 0x38),(float *)(param_2 + 0x20)
                      );
    }
  }
  return;
}



// ==== 80083ba4  FUN_80083ba4 ====

/* WARNING: Removing unreachable block (ram,0x80083c70) */
/* WARNING: Removing unreachable block (ram,0x80083bb4) */

void FUN_80083ba4(double param_1,int param_2,undefined1 param_3)

{
  int iVar1;
  
  gnt4_PSVECNormalize_bl((float *)(param_2 + 0x38),(float *)(param_2 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x44),(float *)(param_2 + 0x38),
                      (float *)(param_2 + 0x38));
  if (*(int *)(param_2 + 200) == 0) {
    gnt4_PSVECAdd_bl((float *)(param_2 + 0x20),(float *)(param_2 + 0x38),(float *)(param_2 + 0x20));
  }
  else {
    *(char *)(param_2 + 0x1cb) = *(char *)(param_2 + 0x1cb) + -1;
    if (*(char *)(param_2 + 0x1cb) < '\x01') {
      *(undefined1 *)(param_2 + 0x1cb) = param_3;
      iVar1 = *(int *)(param_2 + 200);
      zz_006c440_(param_1,param_2,(float *)(iVar1 + 100));
      if (*(char *)(param_2 + 0x88) != *(char *)(*(int *)(iVar1 + 0x20) + 0x88)) {
        zz_00833a4_(param_2);
      }
    }
    else {
      gnt4_PSVECAdd_bl((float *)(param_2 + 0x20),(float *)(param_2 + 0x38),(float *)(param_2 + 0x20)
                      );
    }
  }
  return;
}



// ==== 80083c90  FUN_80083c90 ====

/* WARNING: Removing unreachable block (ram,0x80083d40) */
/* WARNING: Removing unreachable block (ram,0x80083ca0) */

void FUN_80083c90(double param_1,int param_2,undefined1 param_3)

{
  gnt4_PSVECNormalize_bl((float *)(param_2 + 0x38),(float *)(param_2 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x44),(float *)(param_2 + 0x38),
                      (float *)(param_2 + 0x38));
  if (*(int *)(param_2 + 200) == 0) {
    gnt4_PSVECAdd_bl((float *)(param_2 + 0x20),(float *)(param_2 + 0x38),(float *)(param_2 + 0x20));
  }
  else {
    *(char *)(param_2 + 0x1cb) = *(char *)(param_2 + 0x1cb) + -1;
    if (*(char *)(param_2 + 0x1cb) < '\x01') {
      *(undefined1 *)(param_2 + 0x1cb) = param_3;
      FUN_8006c498(param_1,param_2,(float *)(*(int *)(param_2 + 200) + 100));
      zz_00833a4_(param_2);
    }
    else {
      gnt4_PSVECAdd_bl((float *)(param_2 + 0x20),(float *)(param_2 + 0x38),(float *)(param_2 + 0x20)
                      );
    }
  }
  return;
}



// ==== 80083d60  zz_0083d60_ ====

undefined4 zz_0083d60_(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  double dVar3;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  if (*(int *)(param_2 + 200) == 0) {
    uVar1 = 1;
    iVar2 = param_2 + param_3 * 0x30;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar2 + 0x8dc);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(iVar2 + 0x8ec);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(iVar2 + 0x8fc);
  }
  else {
    gnt4_PSVECSubtract_bl((float *)(param_2 + 0x518),(float *)(param_1 + 0x20),&local_28);
    dVar3 = gnt4_PSVECSquareMag_bl(&local_28);
    if (dVar3 <= (double)FLOAT_80437ae4) {
      uVar1 = 1;
      iVar2 = param_2 + param_3 * 0x30;
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar2 + 0x8dc);
      *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(iVar2 + 0x8ec);
      *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(iVar2 + 0x8fc);
    }
    else {
      *(float *)(param_1 + 0x38) = local_28;
      *(undefined4 *)(param_1 + 0x3c) = local_24;
      *(undefined4 *)(param_1 + 0x40) = local_20;
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      if ((*(byte *)(param_1 + 0xd0) & 4) == 0) {
        *(undefined4 *)(param_1 + 200) = 0;
      }
      uVar1 = 0;
    }
  }
  return uVar1;
}



// ==== 80083e64  zz_0083e64_ ====

void zz_0083e64_(int param_1,float *param_2,float *param_3)

{
  uint uVar1;
  bool bVar2;
  double dVar3;
  float afStack_58 [3];
  float afStack_4c [3];
  undefined4 local_40;
  undefined4 local_30;
  undefined4 local_20;
  
  uVar1 = *(uint *)(param_1 + 200);
  bVar2 = false;
  if ((int)(-uVar1 | uVar1) < 0) {
    gnt4_PSMTXCopy_bl(param_2,afStack_4c);
    local_40 = *(undefined4 *)(uVar1 + 100);
    local_30 = *(undefined4 *)(uVar1 + 0x68);
    local_20 = *(undefined4 *)(uVar1 + 0x6c);
    gnt4_PSMTXMultVec_bl(afStack_4c,param_3,afStack_58);
    gnt4_PSVECSubtract_bl(afStack_58,(float *)(param_1 + 0x20),(float *)(param_1 + 0x38));
    dVar3 = gnt4_PSVECSquareMag_bl((float *)(param_1 + 0x38));
    bVar2 = (double)FLOAT_80437ae4 < dVar3;
  }
  if (!bVar2) {
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0x8dc);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0x8ec);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(*(int *)(param_1 + 0x90) + 0x8fc);
  }
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  if ((*(byte *)(param_1 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_1 + 200) = 0;
  }
  return;
}



// ==== 80083f5c  zz_0083f5c_ ====

bool zz_0083f5c_(int param_1,float *param_2)

{
  bool bVar1;
  double dVar2;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  bVar1 = true;
  if (*(int *)(param_1 + 200) != 0) {
    gnt4_PSVECSubtract_bl(param_2,(float *)(param_1 + 0x20),&local_18);
    dVar2 = gnt4_PSVECSquareMag_bl(&local_18);
    bVar1 = dVar2 <= (double)FLOAT_80437b28;
    if (!bVar1) {
      *(float *)(param_1 + 0x38) = local_18;
      *(undefined4 *)(param_1 + 0x3c) = local_14;
      *(undefined4 *)(param_1 + 0x40) = local_10;
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    }
    if ((*(byte *)(param_1 + 0xd0) & 4) == 0) {
      *(undefined4 *)(param_1 + 200) = 0;
    }
  }
  return bVar1;
}



// ==== 80084000  zz_0084000_ ====

int zz_0084000_(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = (int)*(char *)(param_1 + 0x18) ^ 2;
  iVar2 = 0;
  if ((int)(((int)uVar1 >> 1) - (uVar1 & 2)) < 0) {
    iVar2 = 0;
    if (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18)) ||
       (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))) {
      iVar2 = 1;
    }
    if (iVar2 != 0) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x1b) = 0;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      *(undefined1 *)(param_1 + 0x19) = 0;
      zz_008aff0_(param_1);
      *(undefined1 *)(param_1 + 0x82) = 0;
    }
  }
  return iVar2;
}



// ==== 800840b8  zz_00840b8_ ====

int zz_00840b8_(int param_1)

{
  uint uVar1;
  int iVar2;
  
  uVar1 = (int)*(char *)(param_1 + 0x18) ^ 2;
  iVar2 = 0;
  if ((int)(((int)uVar1 >> 1) - (uVar1 & 2)) < 0) {
    iVar2 = 0;
    if (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18)) ||
       (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))) {
      iVar2 = 1;
    }
    if (iVar2 != 0) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x1b) = 0;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      *(undefined1 *)(param_1 + 0x19) = 0;
      zz_008aff0_(param_1);
      *(undefined1 *)(param_1 + 0x82) = 0;
    }
  }
  return iVar2;
}



// ==== 80084170  zz_0084170_ ====

int zz_0084170_(int param_1)

{
  int iVar1;
  double dVar2;
  float afStack_38 [3];
  float afStack_2c [3];
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  zz_0084230_(afStack_38,(float *)(param_1 + 0x20),(float *)(param_1 + 0x2c));
  zz_0084230_(afStack_2c,(float *)(param_1 + 0x2c),(float *)(param_1 + 0x20));
  dVar2 = gnt4_PSVECSquareDistance_bl(afStack_38,afStack_2c);
  iVar1 = 0;
  if (((double)FLOAT_80437b2c < dVar2) &&
     (iVar1 = zz_003e978_(afStack_2c,afStack_38,&local_20), iVar1 != 0)) {
    *(float *)(param_1 + 0x20) = local_20;
    *(undefined4 *)(param_1 + 0x24) = local_1c;
    *(undefined4 *)(param_1 + 0x28) = local_18;
    zz_0019550_(param_1,(undefined4 *)(param_1 + 0x20),0);
  }
  return iVar1;
}



// ==== 80084230  zz_0084230_ ====

void zz_0084230_(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  
  fVar1 = param_2[1];
  *param_1 = *param_2;
  param_1[1] = fVar1;
  param_1[2] = param_2[2];
  fVar1 = *param_1;
  if (*(float *)(DAT_8043625c + 0x3c) <= fVar1) {
    if (*(float *)(DAT_8043625c + 0x38) < fVar1) {
      param_1[2] = param_3[2] +
                   ((*(float *)(DAT_8043625c + 0x38) - *param_3) * (param_1[2] - param_3[2])) /
                   (fVar1 - *param_3);
      param_1[1] = param_3[1] +
                   ((*(float *)(DAT_8043625c + 0x38) - *param_3) * (param_1[1] - param_3[1])) /
                   (*param_1 - *param_3);
      *param_1 = *(float *)(DAT_8043625c + 0x38);
    }
  }
  else {
    param_1[2] = param_3[2] +
                 ((*(float *)(DAT_8043625c + 0x3c) - *param_3) * (param_1[2] - param_3[2])) /
                 (fVar1 - *param_3);
    param_1[1] = param_3[1] +
                 ((*(float *)(DAT_8043625c + 0x3c) - *param_3) * (param_1[1] - param_3[1])) /
                 (*param_1 - *param_3);
    *param_1 = *(float *)(DAT_8043625c + 0x3c);
  }
  fVar1 = param_1[2];
  if (fVar1 < *(float *)(DAT_8043625c + 0x44)) {
    *param_1 = *param_3 +
               ((*(float *)(DAT_8043625c + 0x44) - param_3[2]) * (*param_1 - *param_3)) /
               (fVar1 - param_3[2]);
    param_1[1] = param_3[1] +
                 ((*(float *)(DAT_8043625c + 0x44) - param_3[2]) * (param_1[1] - param_3[1])) /
                 (param_1[2] - param_3[2]);
    param_1[2] = *(float *)(DAT_8043625c + 0x44);
    return;
  }
  if (fVar1 <= *(float *)(DAT_8043625c + 0x40)) {
    return;
  }
  *param_1 = *param_3 +
             ((*(float *)(DAT_8043625c + 0x40) - param_3[2]) * (*param_1 - *param_3)) /
             (fVar1 - param_3[2]);
  param_1[1] = param_3[1] +
               ((*(float *)(DAT_8043625c + 0x40) - param_3[2]) * (param_1[1] - param_3[1])) /
               (param_1[2] - param_3[2]);
  param_1[2] = *(float *)(DAT_8043625c + 0x40);
  return;
}



// ==== 80084434  zz_0084434_ ====

undefined4 zz_0084434_(int param_1,int param_2)

{
  if (*(char *)(param_1 + 0x18) != '\x01') {
    return 1;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x1000) != 0) {
    return 1;
  }
  if (param_2 != 0) {
    return 0;
  }
  if (((*(char *)(param_1 + 0x6fc) == '\0') && (*(char *)(param_1 + 0x4a0) == '\0')) &&
     (*(char *)(param_1 + 0x4a1) == '\0')) {
    return 0;
  }
  return 1;
}



// ==== 80084498  zz_0084498_ ====

void zz_0084498_(int param_1,float *param_2)

{
  float fVar1;
  double dVar2;
  float afStack_28 [4];
  undefined4 local_18;
  uint uStack_14;
  undefined4 local_10;
  uint uStack_c;
  
  dVar2 = gnt4_PSVECSquareMag_bl(param_2);
  if ((double)FLOAT_80437ae4 < dVar2) {
    *(byte *)(param_1 + 0x730) = *(byte *)(param_1 + 0x730) | 1;
    uStack_14 = (uint)*(byte *)(param_1 + 0x731);
    if (uStack_14 == 0) {
      *(undefined1 *)(param_1 + 0x731) = 1;
      fVar1 = param_2[1];
      *(float *)(param_1 + 0x724) = *param_2;
      *(float *)(param_1 + 0x728) = fVar1;
      *(float *)(param_1 + 0x72c) = param_2[2];
    }
    else {
      local_18 = 0x43300000;
      gnt4_PSQUATScale_bl((double)(float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80437b38),
                          (float *)(param_1 + 0x724),afStack_28);
      gnt4_PSVECAdd_bl(param_2,afStack_28,afStack_28);
      dVar2 = DOUBLE_80437b38;
      local_10 = 0x43300000;
      *(char *)(param_1 + 0x731) = *(char *)(param_1 + 0x731) + '\x01';
      uStack_c = (uint)*(byte *)(param_1 + 0x731);
      gnt4_PSQUATScale_bl((double)(FLOAT_80437b30 /
                                  (float)((double)CONCAT44(0x43300000,uStack_c) - dVar2)),afStack_28
                          ,(float *)(param_1 + 0x724));
    }
  }
  return;
}



// ==== 8008458c  zz_008458c_ ====

uint zz_008458c_(float *param_1)

{
  uint uVar1;
  
  uVar1 = 0;
  if (*(float *)(DAT_8043625c + 0x3c) <= *param_1) {
    if (*(float *)(DAT_8043625c + 0x38) < *param_1) {
      *param_1 = *(float *)(DAT_8043625c + 0x38);
      uVar1 = 1;
    }
  }
  else {
    *param_1 = *(float *)(DAT_8043625c + 0x3c);
    uVar1 = 1;
  }
  if (*(float *)(DAT_8043625c + 0x44) <= param_1[2]) {
    if (*(float *)(DAT_8043625c + 0x40) < param_1[2]) {
      param_1[2] = *(float *)(DAT_8043625c + 0x40);
      uVar1 = uVar1 | 2;
    }
  }
  else {
    param_1[2] = *(float *)(DAT_8043625c + 0x44);
    uVar1 = uVar1 | 2;
  }
  return uVar1;
}



// ==== 80084600  zz_0084600_ ====

void zz_0084600_(int param_1,byte param_2)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = (uint)param_2 * 0x50;
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 1;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_80084740;
    *(code **)(puVar1 + 0x10c) = FUN_80085154;
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
    *(float *)(puVar1 + 0x58) = *(float *)(puVar1 + 0xb4) * *(float *)(&DAT_802d9794 + iVar2);
    *(float *)(puVar1 + 0x5c) = *(float *)(puVar1 + 0xb4) * *(float *)(&DAT_802d9798 + iVar2);
    *(float *)(puVar1 + 0x60) = *(float *)(puVar1 + 0xb4) * *(float *)(&DAT_802d979c + iVar2);
  }
  return;
}



// ==== 80084740  FUN_80084740 ====

void FUN_80084740(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_802da018)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80084790  FUN_80084790 ====

/* WARNING: Removing unreachable block (ram,0x8008495c) */
/* WARNING: Removing unreachable block (ram,0x800849b4) */
/* WARNING: Removing unreachable block (ram,0x80084a0c) */

void FUN_80084790(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar5;
  int iVar6;
  undefined8 uVar7;
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar6 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar3 = (uint)*(byte *)(param_9 + 0x11) * 0x50;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar4 = iVar3;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  *(undefined1 *)(param_9 + 0x98) = 5;
  *(undefined2 *)(param_9 + 0x1c) = 600;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8d4),
             (float *)(iVar3 + -0x7fd268a4),(float *)(param_9 + 0x20));
  cVar1 = (&DAT_802d97a0)[iVar3];
  if (cVar1 == '\x03') {
    iVar2 = zz_00853ec_(iVar6,(int)*(char *)(param_9 + 0x11));
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437b40 *
                                       (double)((longlong)(double)(short)iVar2 * 0x3ff0000000000000)
                                       ),&local_44,0x7a);
    gnt4_PSMTXConcat_bl((float *)(iVar6 + 0x8d4),&local_44,&local_44);
    *(float *)(param_9 + 0x38) = local_44;
    *(undefined4 *)(param_9 + 0x3c) = local_34;
    *(undefined4 *)(param_9 + 0x40) = local_24;
  }
  else if (cVar1 < '\x03') {
    if (cVar1 == '\x01') {
      *(undefined4 *)(param_9 + 0x38) =
           *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8d8);
      *(undefined4 *)(param_9 + 0x3c) =
           *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8e8);
      *(undefined4 *)(param_9 + 0x40) =
           *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8f8);
    }
    else if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        *(undefined4 *)(param_9 + 0x38) =
             *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8d4);
        *(undefined4 *)(param_9 + 0x3c) =
             *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8e4);
        *(undefined4 *)(param_9 + 0x40) =
             *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8f4);
      }
    }
    else {
      *(undefined4 *)(param_9 + 0x38) =
           *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8dc);
      *(undefined4 *)(param_9 + 0x3c) =
           *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8ec);
      *(undefined4 *)(param_9 + 0x40) =
           *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8fc);
    }
  }
  else if (cVar1 == '\x05') {
    iVar2 = zz_00853ec_(iVar6,(int)*(char *)(param_9 + 0x11));
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437b40 *
                                       (double)((longlong)(double)(short)iVar2 * 0x3ff0000000000000)
                                       ),&local_44,0x78);
    gnt4_PSMTXConcat_bl((float *)(iVar6 + 0x8d4),&local_44,&local_44);
    *(undefined4 *)(param_9 + 0x38) = local_3c;
    *(undefined4 *)(param_9 + 0x3c) = local_2c;
    *(undefined4 *)(param_9 + 0x40) = local_1c;
  }
  else if (cVar1 < '\x05') {
    iVar2 = zz_00853ec_(iVar6,(int)*(char *)(param_9 + 0x11));
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437b40 *
                                       (double)((longlong)(double)(short)iVar2 * 0x3ff0000000000000)
                                       ),&local_44,0x78);
    gnt4_PSMTXConcat_bl((float *)(iVar6 + 0x8d4),&local_44,&local_44);
    *(undefined4 *)(param_9 + 0x38) = local_40;
    *(undefined4 *)(param_9 + 0x3c) = local_30;
    *(undefined4 *)(param_9 + 0x40) = local_20;
  }
  if ((&DAT_802d97a1)[iVar3] == '\x01') {
    gnt4_PSQUATScale_bl((double)FLOAT_80437b44,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  }
  cVar1 = (&DAT_802d97a2)[iVar3];
  if (cVar1 == '\x01') {
    *(undefined4 *)(param_9 + 0x9c) =
         *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8d8);
    *(undefined4 *)(param_9 + 0xa0) =
         *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8e8);
    *(undefined4 *)(param_9 + 0xa4) =
         *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8f8);
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(undefined4 *)(param_9 + 0x9c) =
           *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8d4);
      *(undefined4 *)(param_9 + 0xa0) =
           *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8e4);
      *(undefined4 *)(param_9 + 0xa4) =
           *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8f4);
    }
  }
  else if (cVar1 < '\x03') {
    *(undefined4 *)(param_9 + 0x9c) =
         *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8dc);
    *(undefined4 *)(param_9 + 0xa0) =
         *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8ec);
    *(undefined4 *)(param_9 + 0xa4) =
         *(undefined4 *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8fc);
  }
  if ((&DAT_802d97a3)[iVar3] == '\x01') {
    gnt4_PSQUATScale_bl((double)FLOAT_80437b44,(float *)(param_9 + 0x9c),(float *)(param_9 + 0x9c));
  }
  gnt4_PSMTXCopy_bl((float *)(iVar6 + (char)(&DAT_802d975a)[iVar3] * 0x30 + 0x8d4),
                    (float *)(param_9 + 0x144));
  if (-1 < (char)(&DAT_802d97a4)[iVar3]) {
    zz_0048288_(param_9);
    zz_00aedc0_(iVar6,(float *)(param_9 + 0x114),(int)(char)(&DAT_802d97a4)[iVar3],
                *(undefined1 *)(param_9 + 0x88));
  }
  iVar2 = zz_008ac80_(param_9,(int)(char)(&DAT_802d975b)[iVar3]);
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    uVar7 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802d9768 + iVar3),(float *)(param_9 + 0x38),
                                (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_802d9768 + iVar3);
    *(short *)(param_9 + 0x1e) = (short)*(undefined4 *)(&DAT_802d9770 + iVar3);
    *(undefined4 *)(param_9 + 0x50) = *(undefined4 *)(&DAT_802d976c + iVar3);
    if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
      uVar7 = zz_0085208_(param_9);
      *(undefined4 *)(param_9 + 200) = 0;
    }
    pfVar5 = (float *)(int)*(short *)(&DAT_802d9758 + iVar3);
    if (((uint)pfVar5 & 0x4000) == 0) {
      zz_000726c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                  *(int *)(param_9 + 0xe0),pfVar5,(int)*(char *)(param_9 + 0x88),iVar4,in_r8,in_r9,
                  in_r10);
      *(undefined1 *)(param_9 + 0x174) = 0;
      *(undefined1 *)(param_9 + 0x82) = 1;
    }
    else {
      iVar6 = zz_0006f78_(iVar6);
      zz_000726c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                  *(int *)(param_9 + 0xe0),(float *)((uint)pfVar5 & 0xffffbfff),
                  (int)*(char *)(param_9 + 0x88),iVar4,in_r8,in_r9,in_r10);
      *(undefined1 *)(param_9 + 0x174) = 1;
      *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    }
    zz_00f036c_(param_9,(uint)(byte)(&DAT_802d97a6)[iVar3]);
  }
  return;
}



// ==== 80084cec  FUN_80084cec ====

/* WARNING: Removing unreachable block (ram,0x800850d4) */
/* WARNING: Removing unreachable block (ram,0x80084cfc) */

void FUN_80084cec(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  float local_74;
  float local_70;
  float local_6c;
  float afStack_68 [3];
  float afStack_5c [3];
  float local_50;
  float local_40;
  float local_30;
  
  iVar4 = (uint)*(byte *)(param_1 + 0x11) * 0x50;
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
  *(undefined1 *)(param_1 + 0x98) = 5;
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  if (*(short *)(param_1 + 0x1c) < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    iVar3 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar3 == 0) {
      if (*(char *)(param_1 + 0x1d9) == '\0') {
        *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x1400;
        FUN_80083874((double)*(float *)(&DAT_802d9784 + iVar4),param_1);
        fVar1 = FLOAT_80437b64;
        if (*(int *)(param_1 + 200) == 0) {
          *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) + *(float *)(param_1 + 0x38);
          *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) + *(float *)(param_1 + 0x40);
          *(float *)(param_1 + 0x24) =
               *(float *)(param_1 + 0x24) +
               -(*(float *)(param_1 + 0x50) * fVar1 - *(float *)(param_1 + 0x3c));
          *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) - *(float *)(param_1 + 0x50);
        }
        else {
          *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
          if (*(short *)(param_1 + 0x1e) < 1) {
            *(short *)(param_1 + 0x1e) = (short)*(undefined4 *)(&DAT_802d9770 + iVar4);
            iVar3 = *(int *)(param_1 + 200);
            gnt4_PSMTXCopy_bl((float *)(param_1 + 0x144),afStack_5c);
            local_74 = local_50;
            local_70 = local_40;
            local_6c = local_30;
            gnt4_PSVECSubtract_bl((float *)(iVar3 + 100),&local_74,&local_74);
            local_50 = local_50 + local_74;
            local_40 = local_40 + local_70;
            local_30 = local_30 + local_6c;
            gnt4_PSMTXMultVec_bl(afStack_5c,(float *)(iVar4 + -0x7fd26878),afStack_68);
            FUN_8006c498((double)*(float *)(&DAT_802d9774 + iVar4),param_1,afStack_68);
            gnt4_PSVECSubtract_bl(afStack_68,(float *)(param_1 + 0x20),&local_74);
            dVar8 = (double)local_70;
            local_70 = FLOAT_80437b48;
            dVar5 = gnt4_PSVECMag_bl(&local_74);
            dVar7 = (double)(*(float *)(param_1 + 0x38) * *(float *)(param_1 + 0x38) +
                            *(float *)(param_1 + 0x40) * *(float *)(param_1 + 0x40));
            if ((double)FLOAT_80437b48 < dVar7) {
              dVar6 = 1.0 / SQRT(dVar7);
              dVar6 = DOUBLE_80437b50 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_80437b58);
              dVar6 = DOUBLE_80437b50 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_80437b58);
              dVar7 = (double)(float)(dVar7 * DOUBLE_80437b50 * dVar6 *
                                              -(dVar7 * dVar6 * dVar6 - DOUBLE_80437b58));
            }
            fVar1 = (float)(dVar5 / dVar7);
            fVar2 = *(float *)(&DAT_802d9778 + iVar4);
            fVar1 = (FLOAT_80437b60 * (float)((double)(fVar1 * *(float *)(param_1 + 0x3c)) - dVar8))
                    / (fVar1 * fVar1);
            if ((fVar2 <= fVar1) && (fVar2 = fVar1, *(float *)(&DAT_802d977c + iVar4) < fVar1)) {
              fVar2 = *(float *)(&DAT_802d977c + iVar4);
            }
            fVar2 = fVar2 - *(float *)(param_1 + 0x50);
            if (*(float *)(&DAT_802d9780 + iVar4) < ABS(fVar2)) {
              fVar2 = *(float *)(&DAT_802d9780 + iVar4) * (ABS(fVar2) / fVar2);
            }
            *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) + fVar2;
          }
          else {
            *(float *)(param_1 + 0x20) = *(float *)(param_1 + 0x20) + *(float *)(param_1 + 0x38);
            *(float *)(param_1 + 0x28) = *(float *)(param_1 + 0x28) + *(float *)(param_1 + 0x40);
          }
          *(float *)(param_1 + 0x24) =
               *(float *)(param_1 + 0x24) +
               (*(float *)(param_1 + 0x3c) - *(float *)(param_1 + 0x50) * FLOAT_80437b64);
          *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) - *(float *)(param_1 + 0x50);
          zz_00833a4_(param_1);
        }
        zz_00833ec_(param_1);
        zz_0083610_(param_1,(float *)(param_1 + 0x50));
        dVar5 = (double)*(float *)(param_1 + 0x3c);
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        *(float *)(param_1 + 0x3c) = (float)dVar5;
        *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0xb4) * *(float *)(&DAT_802d9794 + iVar4);
        *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0xb4) * *(float *)(&DAT_802d9798 + iVar4);
        *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0xb4) * *(float *)(&DAT_802d979c + iVar4);
        iVar4 = zz_0083714_(param_1);
        if (iVar4 == 0) {
          iVar4 = zz_0084170_(param_1);
          if (iVar4 != 0) {
            *(undefined1 *)(param_1 + 0x18) = 2;
          }
        }
        else {
          *(undefined1 *)(param_1 + 0x18) = 2;
          zz_008aff0_(param_1);
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x18) = 2;
        zz_008aff0_(param_1);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
    }
  }
  return;
}



// ==== 800850f8  FUN_800850f8 ====

void FUN_800850f8(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80085134  FUN_80085134 ====

void FUN_80085134(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80085154  FUN_80085154 ====

/* WARNING: Removing unreachable block (ram,0x800851b4) */

void FUN_80085154(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  double dVar2;
  undefined8 uVar3;
  float afStack_38 [13];
  
  if (*(int *)(*(int *)(param_9 + 0xe0) + 0x14) < 0) {
    dVar2 = (double)FLOAT_80437b68;
    gnt4_PSMTXScale_bl(dVar2,dVar2,dVar2,afStack_38);
    gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_38,afStack_38);
    zz_0018824_();
  }
  else {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80437b40 *
                                       (double)((longlong)(double)*(short *)(param_9 + 0x74) *
                                               0x3ff0000000000000)),afStack_38,0x7a);
    pfVar1 = afStack_38;
    uVar3 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
    zz_00076d0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,
                param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe0),0x47);
  }
  return;
}



// ==== 80085208  zz_0085208_ ====

/* WARNING: Removing unreachable block (ram,0x800853c8) */
/* WARNING: Removing unreachable block (ram,0x80085218) */

void zz_0085208_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  float local_74;
  float local_70;
  float local_6c;
  float afStack_68 [3];
  float afStack_5c [3];
  float local_50;
  float local_40;
  float local_30;
  
  iVar4 = *(int *)(param_1 + 200);
  if (iVar4 != 0) {
    iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x50;
    gnt4_PSMTXCopy_bl((float *)(param_1 + 0x144),afStack_5c);
    local_74 = local_50;
    local_70 = local_40;
    local_6c = local_30;
    gnt4_PSVECSubtract_bl((float *)(iVar4 + 100),&local_74,&local_74);
    local_50 = local_50 + local_74;
    local_40 = local_40 + local_70;
    local_30 = local_30 + local_6c;
    gnt4_PSMTXMultVec_bl(afStack_5c,(float *)(iVar3 + -0x7fd26878),afStack_68);
    gnt4_PSVECSubtract_bl(afStack_68,(float *)(param_1 + 0x20),&local_74);
    dVar8 = (double)local_70;
    local_70 = FLOAT_80437b48;
    dVar5 = gnt4_PSVECMag_bl(&local_74);
    dVar7 = (double)(*(float *)(param_1 + 0x38) * *(float *)(param_1 + 0x38) +
                    *(float *)(param_1 + 0x40) * *(float *)(param_1 + 0x40));
    if ((double)FLOAT_80437b48 < dVar7) {
      dVar6 = 1.0 / SQRT(dVar7);
      dVar6 = DOUBLE_80437b50 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_80437b58);
      dVar6 = DOUBLE_80437b50 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_80437b58);
      dVar7 = (double)(float)(dVar7 * DOUBLE_80437b50 * dVar6 *
                                      -(dVar7 * dVar6 * dVar6 - DOUBLE_80437b58));
    }
    dVar5 = (double)(float)(dVar5 / dVar7);
    fVar1 = *(float *)(&DAT_802d9778 + iVar3);
    fVar2 = (FLOAT_80437b60 * (float)(dVar5 * (double)*(float *)(param_1 + 0x3c) - dVar8)) /
            (float)(dVar5 * dVar5);
    if ((fVar1 <= fVar2) && (fVar1 = fVar2, *(float *)(&DAT_802d977c + iVar3) < fVar2)) {
      fVar1 = *(float *)(&DAT_802d977c + iVar3);
    }
    fVar1 = fVar1 - *(float *)(param_1 + 0x50);
    if (*(float *)(&DAT_802d9780 + iVar3) < ABS(fVar1)) {
      fVar1 = *(float *)(&DAT_802d9780 + iVar3) * (ABS(fVar1) / fVar1);
    }
    *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) + fVar1;
  }
  return;
}



// ==== 800853ec  zz_00853ec_ ====

int zz_00853ec_(int param_1,uint param_2)

{
  float fVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_30;
  float local_2c;
  float local_28;
  float afStack_24 [6];
  
  iVar3 = *(int *)(param_1 + 200);
  fVar1 = FLOAT_80437b48;
  if (iVar3 != 0) {
    iVar2 = (param_2 & 0xff) * 0x50;
    if ((&DAT_802d975a)[iVar2] == '\0') {
      gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)(iVar2 + -0x7fd268a4),afStack_24);
    }
    else {
      gnt4_PSMTXMultVec_bl
                ((float *)(param_1 + (char)(&DAT_802d975a)[iVar2] * 0x30 + 0x8d4),
                 (float *)(iVar2 + -0x7fd268a4),afStack_24);
    }
    local_30 = *(float *)(iVar3 + 100);
    local_2c = *(float *)(iVar3 + 0x68);
    local_28 = *(float *)(iVar3 + 0x6c);
    gnt4_PSVECSubtract_bl(&local_30,afStack_24,&local_30);
    dVar5 = (double)(local_30 * local_30 + local_28 * local_28);
    if ((double)FLOAT_80437b48 < dVar5) {
      dVar4 = 1.0 / SQRT(dVar5);
      dVar4 = DOUBLE_80437b50 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_80437b58);
      dVar4 = DOUBLE_80437b50 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_80437b58);
      dVar5 = (double)(float)(dVar5 * DOUBLE_80437b50 * dVar4 *
                                      -(dVar5 * dVar4 * dVar4 - DOUBLE_80437b58));
    }
    local_30 = (float)dVar5;
    if (dVar5 < (double)FLOAT_80437b6c) {
      local_30 = FLOAT_80437b6c;
    }
    fVar1 = (*(float *)(&DAT_802d976c + iVar2) * local_30 * local_30) /
            (FLOAT_80437b60 * *(float *)(&DAT_802d9768 + iVar2) * *(float *)(&DAT_802d9768 + iVar2))
    ;
    dVar5 = (double)(local_30 * local_30 - FLOAT_80437b70 * fVar1 * (fVar1 + local_2c));
    if (dVar5 < (double)FLOAT_80437b48) {
      dVar5 = (double)FLOAT_80437b48;
    }
    if ((double)FLOAT_80437b48 < dVar5) {
      dVar4 = 1.0 / SQRT(dVar5);
      dVar4 = DOUBLE_80437b50 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_80437b58);
      dVar4 = DOUBLE_80437b50 * dVar4 * -(dVar5 * dVar4 * dVar4 - DOUBLE_80437b58);
      dVar5 = (double)(float)(dVar5 * DOUBLE_80437b50 * dVar4 *
                                      -(dVar5 * dVar4 * dVar4 - DOUBLE_80437b58));
    }
    dVar5 = gnt4_atan((double)((float)((double)local_30 - dVar5) / (FLOAT_80437b60 * fVar1)));
    fVar1 = (float)dVar5;
    if (FLOAT_80437b74 <= fVar1) {
      fVar1 = FLOAT_80437b74;
    }
  }
  return (int)(short)(-*(short *)(param_1 + 0x1d64) - (short)(int)(FLOAT_80437b78 * fVar1));
}



// ==== 80085638  zz_0085638_ ====

void zz_0085638_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 3;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_80085798;
    *(code **)(puVar1 + 0x10c) = FUN_80085dc0;
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
    *(undefined4 *)(puVar1 + 0x148) = *(undefined4 *)(puVar1 + 0xb4);
    *(undefined4 *)(puVar1 + 200) = 0;
    if ('\x03' < *(char *)(param_1 + 0x485)) {
      *(undefined1 *)(*(int *)(param_1 + 0x440) + 0x18) = 2;
      *(undefined4 *)(param_1 + 0x440) = *(undefined4 *)(param_1 + 0x444);
      *(undefined4 *)(param_1 + 0x444) = *(undefined4 *)(param_1 + 0x448);
      *(undefined4 *)(param_1 + 0x448) = *(undefined4 *)(param_1 + 0x44c);
      *(undefined1 *)(param_1 + 0x485) = 3;
    }
    *(undefined1 **)(param_1 + *(char *)(param_1 + 0x485) * 4 + 0x440) = puVar1;
    *(char *)(param_1 + 0x485) = *(char *)(param_1 + 0x485) + '\x01';
  }
  return;
}



// ==== 80085798  FUN_80085798 ====

void FUN_80085798(int param_1)

{
  (*(code *)(&PTR_FUN_802da094)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800857d4  FUN_800857d4 ====

void FUN_800857d4(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  uint uVar2;
  undefined4 extraout_r4;
  float *pfVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  double dVar8;
  undefined8 uVar9;
  double dVar10;
  
  puVar4 = &DAT_802da028;
  iVar7 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x24;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar6 = iVar5;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar7 + (char)(&DAT_802da02a)[iVar5] * 0x30 + 0x8d4),
             (float *)(iVar5 + -0x7fd25fd4),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)
        (iVar7 + (char)(&DAT_802da02a)[iVar5] * 0x30 + *(short *)(&DAT_802da048 + iVar5) * 4 + 0x8d4
        );
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)
        (iVar7 + (char)(&DAT_802da02a)[iVar5] * 0x30 + *(short *)(&DAT_802da048 + iVar5) * 4 + 0x8e4
        );
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)
        (iVar7 + (char)(&DAT_802da02a)[iVar5] * 0x30 + *(short *)(&DAT_802da048 + iVar5) * 4 + 0x8f4
        );
  if (*(short *)(&DAT_802da04a + iVar5) == 1) {
    gnt4_PSQUATScale_bl((double)FLOAT_80437b80,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  }
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_802da038 + iVar5),(float *)(param_9 + 0x38),
                      (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_802da038 + iVar5);
  *(undefined4 *)(param_9 + 0x4c) = *(undefined4 *)(&DAT_802da03c + iVar5);
  *(float *)(param_9 + 0xb4) = *(float *)(param_9 + 0x148) * *(float *)(&DAT_802da040 + iVar5);
  *(undefined4 *)(param_9 + 0xc0) = *(undefined4 *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0x58) = *(undefined4 *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0x5c) = *(undefined4 *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0x60) = *(undefined4 *)(param_9 + 0xb4);
  uVar2 = zz_00055fc_();
  *(short *)(param_9 + 0x72) = (short)(uVar2 << 8);
  *(undefined2 *)(param_9 + 0x7e) = 0x888;
  *(undefined2 *)(param_9 + 0x272) = 0xffff;
  iVar7 = zz_008ae3c_(iVar7,param_9,(&DAT_802da02b)[iVar5]);
  if (iVar7 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined4 *)(param_9 + 0x144) = 0;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined2 *)(param_9 + 0x1e) = 0;
    *(undefined4 *)(param_9 + 0xd8) =
         *(undefined4 *)(&DAT_802da0a4 + (char)(&DAT_802da029)[iVar5] * 4);
    dVar8 = zz_0045204_(*(short *)(param_9 + 0x1e));
    dVar10 = (double)FLOAT_80437b84;
    *(float *)(param_9 + 0xd4) = (float)(dVar8 * dVar10);
    dVar8 = (double)*(float *)(param_9 + 0xd4);
    if ((dVar8 <= dVar10) && (dVar10 = dVar8, dVar8 < (double)FLOAT_80437b88)) {
      dVar10 = (double)FLOAT_80437b88;
    }
    *(float *)(param_9 + 0xd4) = (float)dVar10;
    fVar1 = *(float *)(param_9 + 0xd4);
    *(float *)(param_9 + 0xd4) = (float)((double)fVar1 + (double)*(float *)(param_9 + 0xd8));
    pfVar3 = (float *)(int)(char)(&DAT_802da028)[iVar5];
    zz_0006fb4_((double)fVar1,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(int)pfVar3,puVar4,iVar6,in_r8,in_r9,in_r10);
    uVar9 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),dVar10,param_3,param_4,param_5,param_6,
                        param_7,param_8,DAT_803bb374,*(int *)(param_9 + 0xe0),pfVar3,puVar4,iVar6,
                        in_r8,in_r9,in_r10);
    zz_0007c30_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4,pfVar3,puVar4,iVar6,in_r8,in_r9,in_r10);
    *(undefined1 *)(param_9 + 0x82) = 1;
    zz_00f036c_(param_9,3);
  }
  return;
}



// ==== 80085a60  FUN_80085a60 ====

void FUN_80085a60(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar5;
  double dVar6;
  undefined8 uVar7;
  double dVar8;
  
  iVar4 = zz_0083244_((float *)(param_9 + 0x20));
  if (iVar4 == 0) {
    if (FLOAT_80437b8c <= *(float *)(param_9 + 0xd8)) {
      *(short *)(param_9 + 0x1e) = *(short *)(param_9 + 0x1e) + 0x400;
      dVar6 = zz_0045204_(*(short *)(param_9 + 0x1e));
      dVar8 = (double)FLOAT_80437b84;
      *(float *)(param_9 + 0xd4) = (float)(dVar6 * dVar8);
      dVar6 = (double)*(float *)(param_9 + 0xd4);
      if ((dVar6 <= dVar8) && (dVar8 = dVar6, dVar6 < (double)FLOAT_80437b88)) {
        dVar8 = (double)FLOAT_80437b88;
      }
      *(float *)(param_9 + 0xd4) = (float)dVar8;
      *(float *)(param_9 + 0xd4) = *(float *)(param_9 + 0xd4) + *(float *)(param_9 + 0xd8);
      uVar7 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),dVar8,param_3,param_4,param_5,param_6,
                          param_7,param_8,DAT_803bb374,*(int *)(param_9 + 0xe0),param_11,param_12,
                          param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar7,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,param_15,
                  param_16);
    }
    *(short *)(param_9 + 0x72) = *(short *)(param_9 + 0x72) + *(short *)(param_9 + 0x7e);
    fVar3 = FLOAT_80437ba4;
    fVar2 = FLOAT_80437b90;
    cVar1 = *(char *)(param_9 + 0x19);
    if (cVar1 == '\x01') {
      if (*(char *)(param_9 + 0x1da) != '\0') {
        *(int *)(param_9 + 0x144) = *(int *)(param_9 + 0x144) + 1;
      }
      if (*(int *)(param_9 + 0x144) < 8) {
        *(float *)(param_9 + 0xb4) = *(float *)(param_9 + 0xb4) * FLOAT_80437ba0;
        fVar2 = *(float *)(param_9 + 0x148) *
                *(float *)(&DAT_802da044 + (uint)*(byte *)(param_9 + 0x11) * 0x24);
        if (fVar2 <= *(float *)(param_9 + 0xb4)) {
          *(float *)(param_9 + 0xb4) = fVar2;
        }
      }
      else {
        *(undefined1 *)(param_9 + 0x19) = 2;
        zz_008aff0_(param_9);
        dVar6 = (double)FLOAT_80437b98;
        *(float *)(param_9 + 0x14c) = FLOAT_80437b94;
        pfVar5 = (float *)0x42;
        dVar8 = (double)(float)(dVar6 * (double)*(float *)(param_9 + 0xb4));
        *(float *)(param_9 + 0x150) = (float)(dVar8 / (double)FLOAT_80437b9c);
        zz_0006fb4_(dVar8,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                    *(int *)(param_9 + 0xe0),0x42,param_12,param_13,param_14,param_15,param_16);
        uVar7 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),dVar6,param_3,param_4,param_5,param_6
                            ,param_7,param_8,DAT_803bb374,*(int *)(param_9 + 0xe0),pfVar5,param_12,
                            param_13,param_14,param_15,param_16);
        zz_0007c30_(uVar7,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 0xe0),extraout_r4_00,pfVar5,param_12,param_13,param_14,
                    param_15,param_16);
      }
      *(undefined4 *)(param_9 + 0xc0) = *(undefined4 *)(param_9 + 0xb4);
      *(undefined4 *)(param_9 + 0x58) = *(undefined4 *)(param_9 + 0xb4);
      *(undefined4 *)(param_9 + 0x5c) = *(undefined4 *)(param_9 + 0xb4);
      *(undefined4 *)(param_9 + 0x60) = *(undefined4 *)(param_9 + 0xb4);
    }
    else if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        *(float *)(param_9 + 0x44) = *(float *)(param_9 + 0x44) + *(float *)(param_9 + 0x4c);
        if (fVar2 < *(float *)(param_9 + 0x44)) {
          gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
          gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x44),(float *)(param_9 + 0x38),
                              (float *)(param_9 + 0x38));
          gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),
                           (float *)(param_9 + 0x20));
        }
        else {
          *(undefined1 *)(param_9 + 0x19) = 1;
          *(undefined2 *)(param_9 + 0x272) = 0;
        }
      }
    }
    else if (cVar1 < '\x03') {
      *(float *)(param_9 + 0xb4) = *(float *)(param_9 + 0xb4) + *(float *)(param_9 + 0x150);
      *(float *)(param_9 + 0x14c) = *(float *)(param_9 + 0x14c) - fVar3;
      if (*(float *)(param_9 + 0x14c) <= fVar2) {
        *(float *)(param_9 + 0x14c) = fVar2;
        *(undefined1 *)(param_9 + 0x18) = 2;
        *(undefined1 *)(param_9 + 0x19) = 0;
      }
      zz_0007cac_((double)*(float *)(param_9 + 0x14c),*(int *)(param_9 + 0xe0));
      *(undefined4 *)(param_9 + 0x58) = *(undefined4 *)(param_9 + 0xb4);
      *(undefined4 *)(param_9 + 0x5c) = *(undefined4 *)(param_9 + 0xb4);
      *(undefined4 *)(param_9 + 0x60) = *(undefined4 *)(param_9 + 0xb4);
    }
    iVar4 = zz_0084170_(param_9);
    if (iVar4 != 0) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      zz_008aff0_(param_9);
    }
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
  }
  return;
}



// ==== 80085d64  FUN_80085d64 ====

void FUN_80085d64(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80085da0  FUN_80085da0 ====

void FUN_80085da0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80085dc0  FUN_80085dc0 ====

void FUN_80085dc0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 80085e00  zz_0085e00_ ====

void zz_0085e00_(int param_1,undefined4 *param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,1,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 5;
    puVar1[0x11] = param_3;
    uVar2 = param_2[1];
    *(undefined4 *)(puVar1 + 0x20) = *param_2;
    *(undefined4 *)(puVar1 + 0x24) = uVar2;
    *(undefined4 *)(puVar1 + 0x28) = param_2[2];
    puVar1[0x12] = 0;
    *(code **)(puVar1 + 0xc) = FUN_80086048;
    *(code **)(puVar1 + 0x10c) = FUN_80086504;
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
  }
  return;
}



// ==== 80085f28  zz_0085f28_ ====

void zz_0085f28_(int param_1,undefined4 *param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  puVar1 = zz_008893c_(3,8,1,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 5;
    puVar1[0x11] = param_3;
    uVar2 = param_2[1];
    *(undefined4 *)(puVar1 + 0x20) = *param_2;
    *(undefined4 *)(puVar1 + 0x24) = uVar2;
    *(undefined4 *)(puVar1 + 0x28) = param_2[2];
    puVar1[0x12] = 1;
    *(code **)(puVar1 + 0xc) = FUN_80086048;
    *(code **)(puVar1 + 0x10c) = FUN_80086504;
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
  }
  return;
}



// ==== 80086048  FUN_80086048 ====

void FUN_80086048(int param_1)

{
  (*(code *)(&PTR_FUN_802da544)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80086084  FUN_80086084 ====

void FUN_80086084(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  byte bVar5;
  float *pfVar4;
  undefined8 uVar6;
  
  iVar3 = (uint)*(byte *)(param_9 + 0x11) * 0x24;
  uVar2 = countLeadingZeros(0xff - *(short *)(&DAT_802da0ba + iVar3));
  uVar2 = uVar2 >> 5;
  if (uVar2 == 0) {
    bVar5 = (byte)*(short *)(&DAT_802da0ba + iVar3);
    if (*(char *)(param_9 + 0x12) == '\0') {
      uVar2 = zz_008ae3c_(*(int *)(param_9 + 0x90),param_9,bVar5);
    }
    else {
      uVar2 = zz_008ae10_(param_9,bVar5);
    }
  }
  if (uVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(param_9 + 0xb4);
    *(float *)(param_9 + 0x148) = *(float *)(&DAT_802da0c0 + iVar3) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x14c) = *(float *)(&DAT_802da0c4 + iVar3) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x150) = *(float *)(&DAT_802da0c8 + iVar3) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x154) = *(float *)(&DAT_802da0cc + iVar3) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x158) = *(float *)(&DAT_802da0d0 + iVar3) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x15c) = *(float *)(&DAT_802da0d4 + iVar3) * *(float *)(param_9 + 0x144);
    *(int *)(param_9 + 0x160) = (int)*(short *)(&DAT_802da0bc + iVar3);
    uVar2 = zz_00055fc_();
    *(short *)(param_9 + 0x72) = (short)(uVar2 << 8);
    *(undefined2 *)(param_9 + 0x7e) = 0x800;
    uVar1 = *(undefined4 *)(param_9 + 0x148);
    *(undefined4 *)(param_9 + 0x60) = uVar1;
    *(undefined4 *)(param_9 + 0x5c) = uVar1;
    *(undefined4 *)(param_9 + 0x58) = uVar1;
    *(undefined4 *)(param_9 + 0xb4) = uVar1;
    *(undefined4 *)(param_9 + 0xc0) = uVar1;
    *(code **)(param_9 + 0x100) = FUN_8008658c;
    uVar6 = zz_0089100_(param_9,1,1);
    uVar6 = zz_00865ec_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    pfVar4 = (float *)(int)*(short *)(&DAT_802da0b8 + iVar3);
    zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(int)pfVar4,param_12,param_13,param_14,param_15,param_16);
    uVar6 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                         (int)*(short *)(&DAT_802da0be + iVar3) ^
                                                         0x80000000) - DOUBLE_80437ba8),param_2,
                        param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                        *(int *)(param_9 + 0xe0),pfVar4,param_12,param_13,param_14,param_15,param_16
                       );
    uVar6 = zz_0007c30_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0xe0),extraout_r4,pfVar4,param_12,param_13,param_14,
                        param_15,param_16);
    zz_0007d40_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4_00,pfVar4,param_12,param_13,param_14,param_15,
                param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
    if (-1 < (int)*(uint *)(&DAT_802da0d8 + iVar3)) {
      zz_00f036c_(param_9,*(uint *)(&DAT_802da0d8 + iVar3));
    }
  }
  return;
}



// ==== 80086268  FUN_80086268 ====

void FUN_80086268(int param_1)

{
  (*(code *)(&PTR_LAB_802da554)[*(char *)(param_1 + 0x19)])();
  zz_0086698_(param_1);
  return;
}



// ==== 80086350  FUN_80086350 ====

void FUN_80086350(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  float local_18 [4];
  
  iVar2 = *(int *)(param_9 + 0x160) + -1;
  *(int *)(param_9 + 0x160) = iVar2;
  if (iVar2 < 1) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x13) = 0;
    *(undefined2 *)(param_9 + 0x180) = 0;
    *(undefined2 *)(param_9 + 0x182) = DAT_802da53a;
    zz_0018f88_((int *)(param_9 + 0x164),(int)PTR_DAT_802da53c,(float *)(param_9 + 0x58));
    gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x148),(float *)(param_9 + 0x58),
                        (float *)(param_9 + 0x58));
    uVar3 = zz_0019338_((int *)(param_9 + 0x16c),(int)PTR_DAT_802da540,local_18);
    zz_0006fb4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(int)DAT_802da538,param_12,param_13,param_14,param_15,
                param_16);
    zz_0007cac_((double)local_18[0],*(int *)(param_9 + 0xe0));
  }
  else {
    *(short *)(param_9 + 0x72) = *(short *)(param_9 + 0x72) + *(short *)(param_9 + 0x7e);
    uVar1 = *(undefined4 *)(param_9 + 0x148);
    *(undefined4 *)(param_9 + 0x60) = uVar1;
    *(undefined4 *)(param_9 + 0x5c) = uVar1;
    *(undefined4 *)(param_9 + 0x58) = uVar1;
    *(undefined4 *)(param_9 + 0xb4) = uVar1;
    *(undefined4 *)(param_9 + 0xc0) = uVar1;
  }
  return;
}



// ==== 8008643c  FUN_8008643c ====

void FUN_8008643c(int param_1)

{
  short sVar1;
  float local_18 [5];
  
  sVar1 = *(short *)(param_1 + 0x180) + 1;
  *(short *)(param_1 + 0x180) = sVar1;
  if (*(short *)(param_1 + 0x182) < sVar1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
  else {
    zz_0018fd8_((int *)(param_1 + 0x164),(int)*(short *)(param_1 + 0x180),(float *)(param_1 + 0x58))
    ;
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x148),(float *)(param_1 + 0x58),
                        (float *)(param_1 + 0x58));
    zz_0019370_((int *)(param_1 + 0x16c),(int)*(short *)(param_1 + 0x180),local_18);
    zz_0007cac_((double)local_18[0],*(int *)(param_1 + 0xe0));
  }
  return;
}



// ==== 800864e4  FUN_800864e4 ====

void FUN_800864e4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80086504  FUN_80086504 ====

void FUN_80086504(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  double dVar3;
  double dVar4;
  float afStack_38 [13];
  
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  if (*(char *)(param_9 + 0x13) != '\0') {
    dVar3 = (double)*(float *)(param_9 + 0x24);
    dVar4 = (double)*(float *)(param_9 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_9 + 0x20),dVar3,dVar4,afStack_38);
    pfVar1 = (float *)(param_9 + 0x174);
    uVar2 = zz_00456a0_(afStack_38,afStack_38,pfVar1);
    zz_00076d0_(uVar2,dVar3,dVar4,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4),
                afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe4),0x44);
  }
  return;
}



// ==== 8008658c  FUN_8008658c ====

void FUN_8008658c(int param_1)

{
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                     (double)*(float *)(param_1 + 0x28),(float *)(param_1 + 0x114));
  zz_00457d4_('y',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x70));
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  return;
}



// ==== 800865ec  zz_00865ec_ ====

void zz_00865ec_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar1;
  float local_18 [5];
  
  *(undefined1 *)(param_9 + 0x13) = 1;
  *(undefined2 *)(param_9 + 0x180) = 0;
  *(undefined2 *)(param_9 + 0x182) = DAT_802da52e;
  zz_0018f88_((int *)(param_9 + 0x164),(int)PTR_DAT_802da530,(float *)(param_9 + 0x174));
  gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x144),(float *)(param_9 + 0x174),
                      (float *)(param_9 + 0x174));
  uVar1 = zz_0019338_((int *)(param_9 + 0x16c),(int)PTR_DAT_802da534,local_18);
  zz_0006fb4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe4),(int)DAT_802da52c,&DAT_803bb32c,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)local_18[0],*(int *)(param_9 + 0xe4));
  return;
}



// ==== 80086698  zz_0086698_ ====

void zz_0086698_(int param_1)

{
  short sVar1;
  float local_18 [5];
  
  if (*(char *)(param_1 + 0x13) != '\0') {
    sVar1 = *(short *)(param_1 + 0x180) + 1;
    *(short *)(param_1 + 0x180) = sVar1;
    if (*(short *)(param_1 + 0x182) < sVar1) {
      *(undefined1 *)(param_1 + 0x13) = 0;
    }
    zz_0018fd8_((int *)(param_1 + 0x164),(int)*(short *)(param_1 + 0x180),(float *)(param_1 + 0x174)
               );
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x144),(float *)(param_1 + 0x174),
                        (float *)(param_1 + 0x174));
    zz_0019370_((int *)(param_1 + 0x16c),(int)*(short *)(param_1 + 0x180),local_18);
    zz_0007cac_((double)local_18[0],*(int *)(param_1 + 0xe4));
  }
  return;
}



// ==== 8008672c  zz_008672c_ ====

void zz_008672c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 7;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_8008683c;
    *(code **)(puVar1 + 0x10c) = FUN_80087068;
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
    puVar1[0x13] = 100;
    puVar1[0x12] = *(undefined1 *)(param_1 + 0x3e4);
    *(undefined4 *)(puVar1 + 200) = 0;
  }
  return;
}



// ==== 8008683c  FUN_8008683c ====

void FUN_8008683c(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_802da5b0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8008688c  FUN_8008688c ====

void FUN_8008688c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  undefined8 uVar9;
  
  iVar7 = *(int *)(param_9 + 0x8c);
  iVar6 = (uint)*(byte *)(param_9 + 0x11) * 0x28;
  iVar2 = -((int)*(short *)(&DAT_802da564 + iVar6) >> 0x1f);
  if (iVar2 == 0) {
    iVar2 = zz_008ac80_(param_9,(int)*(short *)(&DAT_802da564 + iVar6));
  }
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined2 *)(param_9 + 0x272) = 0xffff;
    piVar3 = zz_0006dc8_(*(char *)(param_9 + 0x13) * 0x38);
    *(int **)(param_9 + 0xdc) = piVar3;
    zz_00455fc_((float *)(iVar7 + (char)(&DAT_802da561)[iVar6] * 0x30 + 0x8d4),
                (float *)(param_9 + 0x114),(float *)(iVar6 + -0x7fd25a98));
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x120);
    *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x130);
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x140);
    *(undefined4 *)(param_9 + 0x38) =
         *(undefined4 *)(param_9 + (char)(&DAT_802da562)[iVar6] * 4 + 0x114);
    *(undefined4 *)(param_9 + 0x3c) =
         *(undefined4 *)(param_9 + (char)(&DAT_802da562)[iVar6] * 4 + 0x124);
    *(undefined4 *)(param_9 + 0x40) =
         *(undefined4 *)(param_9 + (char)(&DAT_802da562)[iVar6] * 4 + 0x134);
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(param_9 + 0x20);
    *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(param_9 + 0x24);
    *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(param_9 + 0x28);
    *(float *)(param_9 + 0x44) = *(float *)(&DAT_802da574 + iVar6) * *(float *)(iVar7 + 0xb4);
    *(float *)(param_9 + 0x48) = *(float *)(&DAT_802da578 + iVar6) * *(float *)(iVar7 + 0xb4);
    *(float *)(param_9 + 0xb4) = *(float *)(&DAT_802da57c + iVar6) * *(float *)(iVar7 + 0xb4);
    *(float *)(param_9 + 0x150) = *(float *)(&DAT_802da580 + iVar6) * *(float *)(iVar7 + 0xb4);
    dVar8 = (double)*(float *)(&DAT_802da584 + iVar6);
    *(float *)(param_9 + 0x154) = (float)(dVar8 * (double)*(float *)(iVar7 + 0xb4));
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_802da566 + iVar6);
    uVar1 = *(undefined4 *)(param_9 + 0xb4);
    *(undefined4 *)(param_9 + 0xc0) = uVar1;
    *(undefined4 *)(param_9 + 0x60) = uVar1;
    *(undefined4 *)(param_9 + 0x5c) = uVar1;
    *(undefined4 *)(param_9 + 0x58) = uVar1;
    uVar4 = zz_00055fc_();
    *(short *)(param_9 + 0x74) = (short)(uVar4 << 8);
    zz_0087214_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    if (-1 < (char)(&DAT_802da563)[iVar6]) {
      bVar5 = zz_0045ef4_((float *)(param_9 + 0x114),5,param_9 + 0x38,&DAT_802b0cb4);
      if (bVar5) {
        zz_0045ef4_((float *)(param_9 + 0x114),4,param_9 + 0x38,&DAT_802b0ca8);
      }
      *(undefined4 *)(param_9 + 0x120) = *(undefined4 *)(param_9 + 0x20);
      *(undefined4 *)(param_9 + 0x130) = *(undefined4 *)(param_9 + 0x24);
      *(undefined4 *)(param_9 + 0x140) = *(undefined4 *)(param_9 + 0x28);
      param_12 = (int)*(char *)(param_9 + 0x88);
      zz_00aedc0_(iVar7,(float *)(param_9 + 0x114),(int)(char)(&DAT_802da563)[iVar6],
                  *(char *)(param_9 + 0x88));
    }
    *(code **)(param_9 + 0x100) = FUN_80086f50;
    uVar9 = zz_0089100_(param_9,1,1);
    zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(uint)(byte)(&DAT_802da560)[iVar6],param_12,param_13,
                param_14,param_15,param_16);
    dVar8 = (double)FLOAT_80437bb0;
    *(undefined1 *)(param_9 + 0x82) = 1;
    zz_00f061c_(dVar8,iVar7,5);
  }
  return;
}



// ==== 80086b18  FUN_80086b18 ====

void FUN_80086b18(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined8 uVar2;
  
  zz_00f0104_(param_9,0x1f,3);
  iVar1 = zz_0083244_((float *)(param_9 + 0x20));
  if (iVar1 != 0) {
    *(undefined1 *)(param_9 + 0x19) = 3;
  }
  *(short *)(param_9 + 0x74) = *(short *)(param_9 + 0x74) + 0x924;
  uVar2 = (*(code *)(&PTR_FUN_802da5c0)[*(char *)(param_9 + 0x19)])(param_9);
  zz_00875ec_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  if ('\0' < *(char *)(param_9 + 0x19)) {
    zz_0087318_(param_9);
  }
  return;
}



// ==== 80086bb0  FUN_80086bb0 ====

void FUN_80086bb0(int param_1)

{
  int iVar1;
  double dVar2;
  double dVar3;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  float afStack_18 [4];
  
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),afStack_18);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),afStack_18,(float *)(param_1 + 0x20));
  iVar1 = zz_003e978_((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),&local_24);
  if (iVar1 != 0) {
    *(float *)(param_1 + 0x20) = local_24;
    *(undefined4 *)(param_1 + 0x24) = local_20;
    *(undefined4 *)(param_1 + 0x28) = local_1c;
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x272) = 0;
  }
  dVar2 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x144));
  if ((double)FLOAT_80437bb4 < dVar2) {
    dVar3 = 1.0 / SQRT(dVar2);
    dVar3 = DOUBLE_80437bb8 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80437bc0);
    dVar3 = DOUBLE_80437bb8 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80437bc0);
    dVar2 = (double)(float)(dVar2 * DOUBLE_80437bb8 * dVar3 *
                                    -(dVar2 * dVar3 * dVar3 - DOUBLE_80437bc0));
  }
  if ((double)*(float *)(param_1 + 0x48) <= dVar2) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x272) = 0;
  }
  return;
}



// ==== 80086d4c  FUN_80086d4c ====

void FUN_80086d4c(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if ((sVar1 == 0) || (*(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x12) * 4 + 0x68) != param_1)
     ) {
    zz_0086da0_(param_1);
  }
  return;
}



// ==== 80086da0  zz_0086da0_ ====

void zz_0086da0_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x19) = 0;
  if (*(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x12) * 4 + 0x68) != param_1) {
    return;
  }
  PTR_DAT_80433934[*(char *)(param_1 + 0x12) + 0x60] = 0;
  *(undefined4 *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x12) * 4 + 0x68) = 0;
  return;
}



// ==== 80086df4  FUN_80086df4 ====

void FUN_80086df4(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  undefined8 uVar1;
  
  *(short *)(param_9 + 0x74) = *(short *)(param_9 + 0x74) + 0x924;
  uVar1 = (**(code **)(&DAT_80433908 + *(char *)(param_9 + 0x19) * 4))();
  zz_00875ec_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80086e4c  FUN_80086e4c ====

void FUN_80086e4c(int param_1)

{
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  if (*(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x12) * 4 + 0x68) == param_1) {
    PTR_DAT_80433934[*(char *)(param_1 + 0x12) + 0x60] = 0;
    *(undefined4 *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x12) * 4 + 0x68) = 0;
  }
  zz_0086ebc_(param_1);
  return;
}



// ==== 80086ebc  zz_0086ebc_ ====

void zz_0086ebc_(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  float fVar3;
  
  fVar3 = FLOAT_80437bd0;
  fVar1 = (float)((double)*(float *)(param_1 + 0xb4) * DOUBLE_80437bc8);
  *(float *)(param_1 + 0xb4) = fVar1;
  if (fVar1 <= fVar3) {
    *(undefined1 *)(param_1 + 0x18) = 3;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  uVar2 = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0xc0) = uVar2;
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  *(undefined4 *)(param_1 + 0x5c) = uVar2;
  *(undefined4 *)(param_1 + 0x58) = uVar2;
  return;
}



// ==== 80086f08  FUN_80086f08 ====

void FUN_80086f08(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80086f50  FUN_80086f50 ====

void FUN_80086f50(int param_1)

{
  float *pfVar1;
  uint uVar2;
  int iVar3;
  float afStack_48 [2];
  float local_40;
  float local_30;
  float local_20;
  
  if (*(int *)(param_1 + 0xdc) != 0) {
    uVar2 = 0;
    iVar3 = 0;
    while( true ) {
      if ((int)*(char *)(param_1 + 0x13) <= (int)uVar2) break;
      if ((*(uint *)(param_1 + ((int)uVar2 >> 5) * 4 + 0x158) & 1 << (uVar2 & 0x1f)) != 0) {
        pfVar1 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar3);
        gnt4_PSMTXIdentity_bl(afStack_48);
        zz_00457d4_('y',afStack_48,afStack_48,*(short *)((int)pfVar1 + 0x26));
        zz_00457d4_('x',afStack_48,afStack_48,*(short *)(pfVar1 + 9));
        *pfVar1 = local_40;
        pfVar1[1] = local_30;
        pfVar1[2] = local_20;
        gnt4_PSQUATScale_bl((double)pfVar1[0xd],pfVar1,pfVar1);
        gnt4_PSVECAdd_bl(pfVar1,(float *)(param_1 + 0x20),pfVar1);
      }
      iVar3 = iVar3 + 0x38;
      uVar2 = uVar2 + 1;
    }
  }
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                     (double)*(float *)(param_1 + 0x28),(float *)(param_1 + 0x114));
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  return;
}



// ==== 80087068  FUN_80087068 ====

/* WARNING: Removing unreachable block (ram,0x80087140) */

void FUN_80087068(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  uint uVar5;
  int iVar6;
  undefined8 uVar7;
  float afStack_48 [12];
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar2 = *(int *)(*(int *)(param_9 + 0xe4) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    uVar5 = 0;
    iVar6 = 0;
    while ((int)uVar5 < (int)*(char *)(param_9 + 0x13)) {
      if ((*(uint *)(param_9 + ((int)uVar5 >> 5) * 4 + 0x158) & 1 << (uVar5 & 0x1f)) != 0) {
        pfVar4 = (float *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar6);
        zz_004844c_(afStack_48,pfVar4,5);
        pfVar4 = pfVar4 + 6;
        uVar7 = zz_00456a0_(afStack_48,afStack_48,pfVar4);
        if (iVar2 == 0) {
          pfVar4 = (float *)&DAT_80437bdc;
          gnt4___assert_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80437bd4,0x495,&DAT_80437bdc,param_12,param_13,param_14,param_15,
                           param_16);
        }
        uVar7 = gnt4_PSMTXCopy_bl(afStack_48,(float *)(iVar2 + 0x44));
        *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
        if (iVar2 != 0) {
          uVar3 = *(uint *)(iVar2 + 0x14);
          bVar1 = false;
          if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
            bVar1 = true;
          }
          if (!bVar1) {
            gnt4_HSD_JObjSetMtxDirtySub_bl
                      (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,uVar3,
                       (undefined *)pfVar4,param_12,param_13,param_14,param_15,param_16);
          }
        }
      }
      iVar6 = iVar6 + 0x38;
      uVar5 = uVar5 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
    zz_00097b4_(*(int *)(param_9 + 0xe4),0x44);
  }
  zz_004844c_(afStack_48,(float *)(param_9 + 0x20),5);
  iVar2 = (int)*(short *)(param_9 + 0x74);
  zz_00457d4_('z',afStack_48,afStack_48,*(short *)(param_9 + 0x74));
  pfVar4 = (float *)(param_9 + 0x58);
  uVar7 = zz_00456a0_(afStack_48,afStack_48,pfVar4);
  zz_00076d0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_48,(undefined *)pfVar4,iVar2,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 80087214  zz_0087214_ ====

void zz_0087214_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar4;
  undefined8 uVar5;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar1 = 0;
    if ((int)(3U - (int)(char)PTR_DAT_80433934[0x51] | (int)(char)PTR_DAT_80433934[0x51] - 3U) < 0)
    {
      iVar1 = (int)*(char *)(param_9 + 0x88);
    }
    uVar5 = zz_0007198_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374
                        ,*(int *)(param_9 + 0xe4),(char *)(int)*(short *)(&DAT_80433910 + iVar1 * 2)
                        ,(int)*(char *)(param_9 + 0x13),in_r7,in_r8,in_r9,in_r10);
    uVar4 = 0;
    iVar1 = *(int *)(*(int *)(param_9 + 0xe4) + 0xc);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(iVar1 + 0x10);
    }
    while ((int)uVar4 < (int)*(char *)(param_9 + 0x13)) {
      iVar3 = ((int)uVar4 >> 5) * 4 + 0x14;
      puVar2 = *(undefined **)(param_9 + 0x144 + iVar3);
      *(uint *)(param_9 + 0x144 + iVar3) = (uint)puVar2 & ~(1 << (uVar4 & 0x1f));
      uVar5 = gnt4_HSD_JObjSetFlagsAll
                        (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,0x10,
                         puVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
      uVar4 = uVar4 + 1;
      if (iVar1 == 0) {
        iVar1 = 0;
      }
      else {
        iVar1 = *(int *)(iVar1 + 8);
      }
    }
  }
  return;
}



// ==== 80087318  zz_0087318_ ====

void zz_0087318_(int param_1)

{
  float fVar1;
  short sVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  uint uVar7;
  float *pfVar8;
  int iVar9;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_74 [13];
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  
  if (*(int *)(param_1 + 0xdc) != 0) {
    iVar13 = param_1 + 0x144;
    iVar11 = 0;
    do {
      uVar12 = 0;
      while( true ) {
        if ((int)*(char *)(param_1 + 0x13) <= (int)uVar12) break;
        iVar9 = ((int)uVar12 >> 5) * 4 + 0x14;
        uVar7 = 1 << (uVar12 & 0x1f);
        if ((*(uint *)(iVar13 + iVar9) & uVar7) == 0) {
          iVar4 = *(int *)(*(int *)(param_1 + 0xe4) + 0xc);
          if (iVar4 == 0) {
            iVar4 = 0;
          }
          else {
            iVar4 = *(int *)(iVar4 + 0x10);
          }
          iVar6 = *(int *)(*(int *)(param_1 + 0xdc) + 0xc);
          *(uint *)(iVar13 + iVar9) = *(uint *)(iVar13 + iVar9) | uVar7;
          pfVar10 = (float *)(iVar6 + uVar12 * 0x38);
          uStack_3c = zz_00055fc_();
          fVar3 = FLOAT_80437be8;
          uStack_3c = uStack_3c & 0xff;
          local_40 = 0x43300000;
          dVar17 = (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80437c00);
          fVar1 = *(float *)(param_1 + 0x150) *
                  FLOAT_80437be4 * (float)(dVar17 * (double)FLOAT_80437bec + (double)FLOAT_80437be8)
          ;
          pfVar10[7] = fVar1;
          pfVar10[6] = fVar1;
          pfVar10[8] = fVar3;
          uVar7 = zz_00055fc_();
          sVar2 = (short)(uVar7 << 8);
          iVar6 = (int)sVar2;
          uVar7 = zz_00055fc_();
          uVar5 = zz_00055fc_();
          fVar1 = FLOAT_80437bf0;
          pfVar10[10] = FLOAT_80437bb4;
          pfVar10[0xb] = fVar1 * *(float *)(param_1 + 0x150);
          uStack_34 = zz_00055fc_();
          uStack_34 = uStack_34 & 0xff;
          local_38 = 0x43300000;
          dVar16 = (double)(float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80437c00);
          fVar1 = FLOAT_80437bf4 * *(float *)(param_1 + 0x150) +
                  (float)((double)FLOAT_80437bf8 * dVar16);
          pfVar10[0xc] = fVar1;
          pfVar10[0xd] = fVar1;
          gnt4_PSMTXIdentity_bl(afStack_74);
          zz_00457d4_('z',afStack_74,afStack_74,(short)(uVar5 << 8));
          zz_00457d4_('y',afStack_74,afStack_74,(short)(uVar7 << 8));
          zz_00457d4_('x',afStack_74,afStack_74,sVar2);
          pfVar8 = pfVar10;
          gnt4_PSMTXMultVec_bl(afStack_74,(float *)&DAT_802b0cc0,pfVar10);
          gnt4_PSQUATScale_bl((double)pfVar10[0xd],pfVar10,pfVar10);
          pfVar10[1] = pfVar10[1] / FLOAT_80437bfc;
          dVar14 = gnt4_PSVECMag_bl(pfVar10);
          pfVar10[0xd] = (float)dVar14;
          iVar9 = FUN_800452a0((double)*pfVar10,(double)pfVar10[2]);
          *(short *)((int)pfVar10 + 0x26) = (short)iVar9;
          dVar14 = (double)(*pfVar10 * *pfVar10 + pfVar10[2] * pfVar10[2]);
          if ((double)FLOAT_80437bb4 < dVar14) {
            dVar16 = 1.0 / SQRT(dVar14);
            dVar16 = DOUBLE_80437bb8 * dVar16 * -(dVar14 * dVar16 * dVar16 - DOUBLE_80437bc0);
            dVar16 = DOUBLE_80437bb8 * dVar16 * -(dVar14 * dVar16 * dVar16 - DOUBLE_80437bc0);
            dVar14 = (double)(float)(dVar14 * DOUBLE_80437bb8 * dVar16 *
                                              -(dVar14 * dVar16 * dVar16 - DOUBLE_80437bc0));
            dVar16 = DOUBLE_80437bc0;
            dVar17 = DOUBLE_80437bb8;
          }
          dVar15 = -(double)pfVar10[1];
          iVar9 = FUN_800452a0(dVar15,dVar14);
          *(short *)(pfVar10 + 9) = (short)iVar9;
          if (0 < (int)uVar12) {
            do {
              if (iVar4 == 0) {
                iVar4 = 0;
              }
              else {
                iVar4 = *(int *)(iVar4 + 8);
              }
              uVar12 = uVar12 - 1;
            } while (uVar12 != 0);
          }
          gnt4_HSD_JObjClearFlagsAll
                    (dVar15,dVar14,dVar16,dVar17,in_f5,in_f6,in_f7,in_f8,iVar4,0x10,
                     (undefined *)pfVar8,iVar6,in_r7,in_r8,in_r9,in_r10);
          zz_00091e4_((double)pfVar10[10],iVar4);
          uVar12 = (uint)*(char *)(param_1 + 0x13);
        }
        uVar12 = uVar12 + 1;
      }
      iVar11 = iVar11 + 1;
    } while (iVar11 < 3);
  }
  return;
}



// ==== 800875ec  zz_00875ec_ ====

void zz_00875ec_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined *puVar4;
  uint uVar5;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  double dVar11;
  double dVar12;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar3 = *(int *)(*(int *)(param_9 + 0xe4) + 0xc);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *(int *)(iVar3 + 0x10);
    }
    iVar10 = param_9 + 0x144;
    uVar9 = 0;
    iVar8 = 0;
    while( true ) {
      fVar2 = FLOAT_80437be8;
      if ((int)*(char *)(param_9 + 0x13) <= (int)uVar9) break;
      iVar6 = ((int)uVar9 >> 5) * 4 + 0x14;
      uVar5 = 1 << (uVar9 & 0x1f);
      if ((*(uint *)(iVar10 + iVar6) & uVar5) != 0) {
        dVar11 = (double)FLOAT_80437be8;
        iVar7 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar8;
        if ((double)*(float *)(iVar7 + 0x28) < dVar11) {
          fVar1 = (float)((double)*(float *)(iVar7 + 0x28) + DOUBLE_80437c08);
          *(float *)(iVar7 + 0x28) = fVar1;
          if (dVar11 <= (double)fVar1) {
            *(float *)(iVar7 + 0x28) = fVar2;
          }
        }
        fVar1 = *(float *)(iVar7 + 0x34);
        dVar11 = (double)FLOAT_80437be8;
        fVar2 = (float)((double)fVar1 - (double)*(float *)(iVar7 + 0x2c));
        dVar12 = (double)fVar2;
        *(float *)(iVar7 + 0x34) = fVar2;
        if (dVar12 < dVar11) {
          puVar4 = *(undefined **)(iVar10 + iVar6);
          *(uint *)(iVar10 + iVar6) = (uint)puVar4 & ~uVar5;
          gnt4_HSD_JObjSetFlagsAll
                    (dVar12,(double)fVar1,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,0x10
                     ,puVar4,uVar5,iVar6,in_r8,in_r9,in_r10);
        }
        zz_00091e4_((double)*(float *)(iVar7 + 0x28),iVar3);
      }
      iVar8 = iVar8 + 0x38;
      uVar9 = uVar9 + 1;
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(iVar3 + 8);
      }
    }
  }
  return;
}



// ==== 80087718  zz_0087718_ ====

void zz_0087718_(void *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  
  DAT_8043625c = param_1;
  gnt4_memset(param_1,0,0x100);
  fVar2 = FLOAT_80437c14;
  fVar1 = FLOAT_80437c10;
  *(float *)((int)DAT_8043625c + 0x10) = FLOAT_80437c10;
  fVar4 = FLOAT_80437c1c;
  fVar3 = FLOAT_80437c18;
  *(float *)((int)DAT_8043625c + 0x14) = fVar1;
  *(float *)((int)DAT_8043625c + 0x18) = fVar1;
  *(undefined4 *)((int)DAT_8043625c + 0x34) =
       *(undefined4 *)(&DAT_802dace8 + (char)PTR_DAT_80433934[0x1c] * 4);
  *(undefined4 *)((int)DAT_8043625c + 0x68) =
       *(undefined4 *)(&DAT_802dad30 + (char)PTR_DAT_80433934[0x1c] * 4);
  *(float *)((int)DAT_8043625c + 0x38) = fVar2;
  *(float *)((int)DAT_8043625c + 0x3c) = fVar3;
  *(float *)((int)DAT_8043625c + 0x40) = fVar2;
  *(float *)((int)DAT_8043625c + 0x44) = fVar3;
  *(float *)((int)DAT_8043625c + 0x48) = *(float *)((int)DAT_8043625c + 0x38) - fVar4;
  *(float *)((int)DAT_8043625c + 0x4c) = fVar4 + *(float *)((int)DAT_8043625c + 0x3c);
  *(float *)((int)DAT_8043625c + 0x50) = *(float *)((int)DAT_8043625c + 0x40) - fVar4;
  *(float *)((int)DAT_8043625c + 0x54) = fVar4 + *(float *)((int)DAT_8043625c + 0x44);
  return;
}



// ==== 80087814  zz_0087814_ ====

void zz_0087814_(void)

{
  if (*(char *)(DAT_8043625c + 8) != '\0') {
    zz_008c0dc_(FUN_80087f38);
  }
  return;
}



// ==== 8008784c  zz_008784c_ ====

void zz_008784c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9,undefined1 param_10
                ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  int iVar2;
  undefined8 uVar3;
  float local_38;
  float local_34;
  float local_30;
  longlong local_28;
  longlong local_20;
  longlong local_18;
  
  *param_9 = 1;
  *(undefined1 **)(param_9 + 0xc) = &LAB_80087b58;
  param_9[0x88] = 4;
  param_9[0x13] = param_10;
  iVar2 = (int)(char)param_9[0x13];
  uVar3 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb470,
                      *(int *)(param_9 + 0xe0),iVar2,param_12,param_13,param_14,param_15,param_16);
  uVar3 = zz_0007908_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),(undefined4 *)(param_9 + 0x20),iVar2,param_12,
                      param_13,param_14,param_15,param_16);
  zz_0007a60_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,&local_38,iVar2,param_12,param_13,param_14,param_15,param_16);
  fVar1 = FLOAT_80437c20;
  local_28 = (longlong)(int)(FLOAT_80437c20 * local_38);
  *(short *)(param_9 + 0x70) = (short)(int)(FLOAT_80437c20 * local_38);
  iVar2 = (int)(fVar1 * local_34);
  local_20 = (longlong)iVar2;
  *(short *)(param_9 + 0x72) = (short)iVar2;
  iVar2 = (int)(fVar1 * local_30);
  local_18 = (longlong)iVar2;
  *(short *)(param_9 + 0x74) = (short)iVar2;
  param_9[0x84] = 0xe;
  FUN_80047aa4((int)param_9);
  return;
}



// ==== 80087924  zz_0087924_ ====

/* WARNING: Removing unreachable block (ram,0x80087b3c) */
/* WARNING: Removing unreachable block (ram,0x80087b34) */
/* WARNING: Removing unreachable block (ram,0x8008793c) */
/* WARNING: Removing unreachable block (ram,0x80087934) */

void zz_0087924_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  byte *pbVar1;
  byte bVar2;
  int iVar3;
  int *piVar4;
  undefined1 *puVar5;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int iVar6;
  char *pcVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  uint uVar10;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int *piVar11;
  byte *pbVar12;
  int iVar13;
  undefined1 *unaff_r31;
  undefined8 uVar14;
  double dVar15;
  double dVar16;
  
  bVar2 = PTR_DAT_80433934[0x1c];
  uVar10 = (uint)bVar2;
  dVar15 = (double)FLOAT_80437c28;
  iVar3 = (char)bVar2 * 4;
  dVar16 = (double)FLOAT_80437c2c;
  pbVar12 = (&PTR_DAT_802daca0)[(char)bVar2] + 6;
  for (iVar13 = (int)(char)(&DAT_802da898)[iVar3];
      (-1 < iVar13 && (iVar13 <= (char)(&DAT_802da899)[iVar3])); iVar13 = iVar13 + 1) {
    uVar8 = 0;
    uVar9 = 2;
    unaff_r31 = zz_008893c_(3,0x28,0,2);
    if (unaff_r31 == (undefined1 *)0x0) break;
    unaff_r31[0x11] = 0;
    uVar14 = zz_008784c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,unaff_r31,
                         (char)iVar13,uVar8,uVar9,uVar10,in_r8,in_r9,in_r10);
    *(code **)(unaff_r31 + 0x10c) = FUN_80087b64;
    iVar6 = (int)(char)unaff_r31[0x13];
    uVar14 = zz_0006fb4_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb470
                         ,*(int *)(unaff_r31 + 0xe4),iVar6,uVar9,uVar10,in_r8,in_r9,in_r10);
    uVar8 = extraout_r4;
    if (*(int *)(*(int *)(unaff_r31 + 0xe4) + 0xc) == 0) {
      piVar4 = (int *)0x0;
    }
    else {
      piVar4 = *(int **)(*(int *)(*(int *)(unaff_r31 + 0xe4) + 0xc) + 0x10);
    }
    while (piVar4 != (int *)0x0) {
      if (piVar4 == (int *)0x0) {
        piVar11 = (int *)0x0;
      }
      else {
        piVar11 = (int *)piVar4[2];
      }
      uVar14 = gnt4_HSD_JObjUnref(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  piVar4,uVar8,iVar6,uVar9,uVar10,in_r8,in_r9,in_r10);
      piVar4 = piVar11;
      uVar8 = extraout_r4_00;
    }
    zz_0007c54_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(unaff_r31 + 0xe4),uVar8,iVar6,uVar9,uVar10,in_r8,in_r9,in_r10);
    pcVar7 = (char *)0x0;
    uVar8 = 0;
    zz_0007cd0_(*(int *)(unaff_r31 + 0xe4),0,0,0);
    uVar14 = zz_0007cac_((double)FLOAT_80437c24,*(int *)(unaff_r31 + 0xe4));
    param_1 = zz_0007f38_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(unaff_r31 + 0xe4),extraout_r4_01,pcVar7,uVar8,uVar10,in_r8,in_r9,
                          in_r10);
    *(undefined1 **)(unaff_r31 + 0x8c) = unaff_r31;
    *(undefined4 *)(unaff_r31 + 0x90) = 0;
    *(float *)(unaff_r31 + 0xb4) = (float)dVar15;
    *(float *)(unaff_r31 + 0xb8) = (float)dVar15;
    *(float *)(unaff_r31 + 0x58) = (float)dVar15;
    *(float *)(unaff_r31 + 0x5c) = (float)dVar15;
    *(float *)(unaff_r31 + 0x60) = (float)dVar15;
    *(float *)(unaff_r31 + 0xc0) = (float)dVar15;
    *(float *)(unaff_r31 + 0xc4) = (float)dVar15;
    if (*pbVar12 != 0xff) {
      param_1 = zz_008ae10_((int)unaff_r31,*pbVar12);
    }
    pbVar1 = pbVar12 + 1;
    pbVar12 = pbVar12 + 2;
    if (*pbVar1 != 0xff) {
      param_1 = zz_008ae10_((int)unaff_r31,*pbVar1);
    }
    unaff_r31[0x26f] = 1;
    unaff_r31[0x281] = 1;
    *(float *)(unaff_r31 + 0x204) = (float)dVar16;
  }
  for (iVar13 = (int)(char)(&DAT_802da89a)[iVar3];
      (-1 < iVar13 && (iVar13 <= (char)(&DAT_802da89b)[iVar3])); iVar13 = iVar13 + 1) {
    uVar8 = 0;
    uVar9 = 1;
    puVar5 = zz_008893c_(2,0x28,0,1);
    if (puVar5 == (undefined1 *)0x0) {
      return;
    }
    unaff_r31[0x11] = 1;
    param_1 = zz_008784c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar5,
                          (char)iVar13,uVar8,uVar9,uVar10,in_r8,in_r9,in_r10);
    *(code **)(puVar5 + 0x10c) = FUN_80087c84;
  }
  return;
}



// ==== 80087b64  FUN_80087b64 ====

void FUN_80087b64(int param_1)

{
  char cVar2;
  uint uVar1;
  
  cVar2 = zz_008b290_();
  if (cVar2 == '\0') {
    if ((-1 < (char)PTR_DAT_80433930[0x28]) &&
       (uVar1 = 1 << (int)(char)PTR_DAT_80433930[0x28],
       ((int)*(short *)(param_1 + 0x270) & uVar1) != 0)) {
      if (((int)*(short *)(param_1 + 0x286) & uVar1) == 0) {
        zz_0007d68_(*(int *)(param_1 + 0xe4),0);
      }
      else {
        zz_0007d68_(*(int *)(param_1 + 0xe4),1);
      }
      if (PTR_DAT_80433934[0x45] == '\x01') {
        *(undefined1 *)(*(int *)(param_1 + 0xe4) + 0xb) = 1;
      }
      else {
        *(undefined1 *)(*(int *)(param_1 + 0xe4) + 0xb) = 0;
      }
      zz_00097b4_(*(int *)(param_1 + 0xe4),0x47);
      return;
    }
    if (PTR_DAT_80433934[0x45] == '\x01') {
      *(undefined1 *)(*(int *)(param_1 + 0xe0) + 0xb) = 1;
    }
    else {
      *(undefined1 *)(*(int *)(param_1 + 0xe0) + 0xb) = 0;
    }
    zz_00097b4_(*(int *)(param_1 + 0xe0),0x17);
  }
  return;
}



// ==== 80087c84  FUN_80087c84 ====

void FUN_80087c84(int param_1)

{
  char cVar1;
  
  cVar1 = zz_008b290_();
  if (cVar1 == '\0') {
    if (PTR_DAT_80433934[0x45] == '\x01') {
      *(undefined1 *)(*(int *)(param_1 + 0xe0) + 0xb) = 1;
    }
    else {
      *(undefined1 *)(*(int *)(param_1 + 0xe0) + 0xb) = 0;
    }
    zz_00097b4_(*(int *)(param_1 + 0xe0),0x14);
  }
  return;
}



// ==== 80087cf0  zz_0087cf0_ ====

void zz_0087cf0_(void)

{
  (**(code **)(&DAT_80433918 + *DAT_8043625c * 4))();
  return;
}



// ==== 80087d2c  FUN_80087d2c ====

void FUN_80087d2c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar3;
  char *pcVar4;
  undefined4 *puVar5;
  char *pcVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int *piVar7;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 uVar8;
  double dVar9;
  undefined8 extraout_f1_01;
  undefined8 extraout_f1_02;
  undefined4 uStack_18;
  float local_14;
  
  *DAT_8043625c = *DAT_8043625c + '\x01';
  DAT_8043625c[8] = '\x01';
  if (*(int *)(&DAT_802da5d0 + (char)PTR_DAT_80433934[0x1c] * 4) != 0) {
    param_1 = zz_00818d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  zz_0087924_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar1 = zz_0006d4c_();
  pcVar6 = DAT_8043625c;
  *(undefined4 *)(DAT_8043625c + 0x58) = uVar1;
  zz_0006fb4_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb470,
              *(int *)(DAT_8043625c + 0x58),0,&DAT_803bb470,pcVar6,in_r8,in_r9,in_r10);
  uVar1 = zz_0006d4c_();
  pcVar6 = DAT_8043625c;
  puVar5 = &DAT_803bb470;
  uVar3 = 0;
  *(undefined4 *)(DAT_8043625c + 0x5c) = uVar1;
  uVar8 = zz_0006fb4_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      DAT_803bb470,*(int *)(DAT_8043625c + 0x5c),0,&DAT_803bb470,pcVar6,in_r8,in_r9,
                      in_r10);
  uVar1 = extraout_r4;
  if (*(int *)(*(int *)(DAT_8043625c + 0x5c) + 0xc) == 0) {
    piVar2 = (int *)0x0;
  }
  else {
    piVar2 = *(int **)(*(int *)(*(int *)(DAT_8043625c + 0x5c) + 0xc) + 0x10);
  }
  while (piVar2 != (int *)0x0) {
    if (piVar2 == (int *)0x0) {
      piVar7 = (int *)0x0;
    }
    else {
      piVar7 = (int *)piVar2[2];
    }
    uVar8 = gnt4_HSD_JObjUnref(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,piVar2,
                               uVar1,uVar3,puVar5,pcVar6,in_r8,in_r9,in_r10);
    piVar2 = piVar7;
    uVar1 = extraout_r4_00;
  }
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(DAT_8043625c + 0x5c),uVar1,uVar3,puVar5,pcVar6,in_r8,in_r9,in_r10);
  pcVar4 = (char *)0x0;
  uVar1 = 0;
  zz_0007cd0_(*(int *)(DAT_8043625c + 0x5c),0,0,0);
  uVar8 = zz_0007cac_((double)FLOAT_80437c24,*(int *)(DAT_8043625c + 0x5c));
  zz_0007f38_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(DAT_8043625c + 0x5c),extraout_r4_01,pcVar4,uVar1,pcVar6,in_r8,in_r9,in_r10);
  uVar8 = zz_0007d68_(*(int *)(DAT_8043625c + 0x5c),-1);
  zz_0007908_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(DAT_8043625c + 0x5c),&uStack_18,pcVar4,uVar1,pcVar6,in_r8,in_r9,in_r10);
  dVar9 = (double)local_14;
  local_14 = (float)(dVar9 - (double)FLOAT_80437c28);
  zz_0007834_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(DAT_8043625c + 0x5c),&uStack_18,pcVar4,uVar1,pcVar6,in_r8,in_r9,in_r10);
  uVar1 = zz_0006d4c_();
  *(undefined4 *)(DAT_8043625c + 0x60) = uVar1;
  zz_00070e4_(extraout_f1_01,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb470,
              *(int *)(DAT_8043625c + 0x60),1,*(int *)(DAT_8043625c + 0x60) + 0x18,pcVar6,in_r8,
              in_r9,in_r10);
  zz_0009c28_(*(int *)(DAT_8043625c + 0x60),0xff);
  zz_0009c30_(*(int *)(DAT_8043625c + 0x60),0xffffffff);
  uVar1 = zz_0006d4c_();
  pcVar6 = DAT_8043625c;
  *(undefined4 *)(DAT_8043625c + 100) = uVar1;
  zz_0006fb4_(extraout_f1_02,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb470,
              *(int *)(DAT_8043625c + 100),2,&DAT_803bb470,pcVar6,in_r8,in_r9,in_r10);
  return;
}



// ==== 80087f24  LooseBallAnims::GetDesperationInfo(unsigned ====

undefined4 LooseBallAnims__GetDesperationInfo_unsigned(int param_1)

{
  return *(undefined4 *)(&DAT_802da5d0 + param_1 * 4);
}



// ==== 80087f38  FUN_80087f38 ====

void FUN_80087f38(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  int iVar1;
  double dVar2;
  char cVar4;
  int iVar3;
  char *pcVar5;
  int in_r6;
  undefined4 in_r7;
  uint in_r8;
  undefined4 in_r9;
  uint in_r10;
  int iVar6;
  undefined8 uVar7;
  
  if (PTR_DAT_80433930[0x34] == '\0') {
    cVar4 = zz_008b290_();
    if (cVar4 == '\0') {
      if (((char)PTR_DAT_80433930[0x28] < '\0') ||
         ((&DAT_803c7697)[(char)PTR_DAT_80433930[0x28] * 0x3e4] == '\0')) {
        iVar3 = *(int *)(DAT_8043625c + 0x58);
      }
      else {
        iVar3 = *(int *)(DAT_8043625c + 0x5c);
      }
      if (PTR_DAT_80433934[0x45] == '\x01') {
        *(undefined1 *)(iVar3 + 0xb) = 1;
      }
      else {
        *(undefined1 *)(iVar3 + 0xb) = 0;
      }
      zz_00097b4_(iVar3,0xf);
      if (PTR_DAT_80433934[0x45] != '\x01') {
        iVar6 = *(int *)(DAT_8043625c + 0x60);
        iVar3 = (char)PTR_DAT_80433930[0x34] * 0x68;
        if ((&DAT_803bb18c)[iVar3] == '\0') {
          uVar7 = zz_0009c30_(iVar6,0xffffffff);
        }
        else {
          in_r10 = (uint)(byte)(&DAT_803bb1d8)[iVar3];
          in_r9 = 0x43300000;
          in_r8 = (uint)DAT_803bb16c;
          in_r7 = 0xff;
          param_5 = (double)FLOAT_80437c30;
          param_3 = (double)(float)((double)CONCAT44(0x43300000,(uint)(byte)(&DAT_803bb1d9)[iVar3])
                                   - DOUBLE_80437c38);
          iVar1 = (int)(param_5 *
                       (double)((float)((double)CONCAT44(0x43300000,in_r10) - DOUBLE_80437c38) /
                               (float)((double)CONCAT44(0x43300000,in_r8) - DOUBLE_80437c38)));
          param_4 = (double)(longlong)iVar1;
          dVar2 = param_5 * (double)(float)(param_3 /
                                           (double)(float)((double)CONCAT44(0x43300000,
                                                                            (uint)DAT_803bb16d) -
                                                          DOUBLE_80437c38));
          param_2 = (double)(float)dVar2;
          in_r6 = (int)(param_5 *
                       (double)((float)((double)CONCAT44(0x43300000,
                                                         (uint)(byte)(&DAT_803bb1da)[iVar3]) -
                                       DOUBLE_80437c38) /
                               (float)((double)CONCAT44(0x43300000,(uint)DAT_803bb16e) -
                                      DOUBLE_80437c38)));
          param_6 = DOUBLE_80437c38;
          uVar7 = zz_0009c38_(iVar6,(char)iVar1,(char)(int)dVar2,(char)in_r6,0xff);
        }
        *(undefined1 *)(iVar6 + 0xb) = 1;
        if ((-1 < (char)PTR_DAT_80433930[0x28]) && (PTR_DAT_80433934[0x1c] != '\x11')) {
          pcVar5 = (char *)((char)PTR_DAT_80433930[0x28] * 0x3e4);
          zz_0007834_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                      (undefined4 *)(pcVar5 + -0x7fc38968),pcVar5,in_r6,in_r7,in_r8,in_r9,in_r10);
        }
        zz_00097b4_(iVar6,1);
      }
      iVar3 = *(int *)(DAT_8043625c + 100);
      if (PTR_DAT_80433934[0x45] == '\x01') {
        *(undefined1 *)(iVar3 + 0xb) = 1;
      }
      else {
        *(undefined1 *)(iVar3 + 0xb) = 0;
      }
      zz_00097b4_(iVar3,0xf);
    }
  }
  return;
}



// ==== 80088190  zz_0088190_ ====

undefined4
zz_0088190_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
           undefined4 param_9,undefined4 param_10,undefined4 param_11,uint *param_12,
           undefined4 *param_13,uint param_14,int param_15,uint param_16)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 extraout_r4;
  undefined8 uVar4;
  undefined8 extraout_f1;
  
  if (DAT_804361c8 != 2) {
    if (1 < DAT_804361c8) {
      if (DAT_804361c8 != 4) {
        if (3 < DAT_804361c8) {
          return 0;
        }
        DAT_804361c8 = DAT_804361c8 + 1;
        puVar1 = &DAT_802da630;
        iVar2 = 0;
        do {
          uVar3 = zz_002a860_(puVar1[3]);
          iVar2 = iVar2 + 1;
          puVar1[2] = uVar3;
          puVar1 = puVar1 + 4;
        } while (iVar2 < 3);
        zz_00882d8_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
        DAT_804361c0 = 0;
        DAT_804361c4 = 1;
      }
      return 1;
    }
    if (DAT_804361c8 == 0) {
      DAT_804361c8 = 1;
      uVar4 = zz_01b729c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      param_1 = zz_0270dec_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            &DAT_800882d4,0,param_11,param_12,param_13,param_14,param_15,param_16);
      DAT_804361cc = 0;
    }
    else if (DAT_804361c8 < 0) {
      return 0;
    }
    DAT_804361c8 = DAT_804361c8 + 1;
    param_11 = 0;
    param_12 = (uint *)(&PTR_DAT_802da61c)[DAT_804361cc * 3];
    param_1 = zz_0273b2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_804361cc,(int)(&PTR_s_poq_adx_usa_afs_802da618)[DAT_804361cc * 3],0,
                          param_12);
    param_10 = extraout_r4;
  }
  iVar2 = zz_0273868_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361cc,
                      param_10,param_11,(uint)param_12,param_13,param_14,param_15,param_16);
  if (iVar2 == 3) {
    DAT_804361cc = DAT_804361cc + 1;
    if (DAT_804361cc < 2) {
      DAT_804361c8 = 1;
    }
    else {
      DAT_804361c8 = DAT_804361c8 + 1;
    }
  }
  return 0;
}



// ==== 800882d8  zz_00882d8_ ====

void zz_00882d8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int *piVar1;
  char *pcVar2;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  
  piVar1 = &DAT_802da630;
  iVar3 = 0;
  do {
    pcVar2 = zz_026f5a0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar1,
                         piVar1[2],piVar1[3],in_r6,in_r7,in_r8,in_r9,in_r10);
    *(char **)piVar1[1] = pcVar2;
    if (pcVar2 != (char *)0x0) {
      param_1 = zz_026e700_(*(int *)piVar1[1],1);
    }
    iVar3 = iVar3 + 1;
    piVar1 = piVar1 + 4;
  } while (iVar3 < 3);
  return;
}



// ==== 80088354  zz_0088354_ ====

undefined4 zz_0088354_(void)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  DAT_80436238 = zz_002a860_(0xd00000);
  if (DAT_80436238 != 0) {
    uVar1 = 0xd00000;
  }
  return uVar1;
}



// ==== 80088398  zz_0088398_ ====

uint zz_0088398_(int param_1,uint param_2,int param_3)

{
  char *pcVar1;
  ushort *puVar2;
  char cVar3;
  ushort uVar4;
  ushort uVar5;
  char *pcVar6;
  uint *puVar7;
  char *pcVar8;
  ushort *puVar9;
  char *pcVar10;
  ushort *puVar11;
  uint uVar12;
  int iVar13;
  
  pcVar6 = &DAT_802da670 + param_3 * 0x18;
  DAT_804362a0 = param_1 + 0x1fU & 0xffffffe0;
  puVar11 = &DAT_803c71cc;
  puVar7 = &DAT_803c71dc;
  puVar9 = &DAT_803c71bc;
  pcVar8 = &DAT_80436298;
  iVar13 = 4;
  pcVar10 = pcVar6;
  DAT_804362a4 = DAT_804362a0;
  do {
    cVar3 = *pcVar6;
    *puVar7 = 0;
    *pcVar8 = -1;
    *puVar9 = 0;
    if ((cVar3 != -1) && (uVar4 = *(ushort *)(pcVar10 + 8), uVar4 != 0)) {
      *pcVar8 = cVar3;
      cVar3 = *pcVar8;
      *puVar9 = uVar4;
      uVar4 = *puVar9;
      uVar5 = *(ushort *)(&DAT_802da660 + cVar3 * 2);
      *puVar7 = DAT_804362a0;
      *puVar11 = uVar5;
      DAT_804362a0 = DAT_804362a0 + (uint)uVar4 * (uint)*puVar11 + 0x1f & 0xffffffe0;
    }
    cVar3 = pcVar6[1];
    puVar7[1] = 0;
    pcVar1 = pcVar8 + 1;
    *pcVar1 = -1;
    puVar2 = puVar9 + 1;
    *puVar2 = 0;
    if ((cVar3 != -1) && (uVar4 = *(ushort *)(pcVar10 + 10), uVar4 != 0)) {
      *pcVar1 = cVar3;
      cVar3 = *pcVar1;
      *puVar2 = uVar4;
      uVar4 = *puVar2;
      uVar5 = *(ushort *)(&DAT_802da660 + cVar3 * 2);
      puVar7[1] = DAT_804362a0;
      puVar11[1] = uVar5;
      DAT_804362a0 = DAT_804362a0 + (uint)uVar4 * (uint)puVar11[1] + 0x1f & 0xffffffe0;
    }
    puVar7 = puVar7 + 2;
    pcVar8 = pcVar8 + 2;
    puVar9 = puVar9 + 2;
    pcVar10 = pcVar10 + 4;
    puVar11 = puVar11 + 2;
    pcVar6 = pcVar6 + 2;
    iVar13 = iVar13 + -1;
  } while (iVar13 != 0);
  uVar12 = DAT_804362a0 - DAT_804362a4;
  if (param_2 < uVar12) {
    uVar12 = 0;
  }
  else {
    zz_008853c_();
  }
  return uVar12;
}



// ==== 8008853c  zz_008853c_ ====

void zz_008853c_(void)

{
  undefined1 uVar1;
  ushort uVar2;
  ushort uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  void *__s;
  void *pvVar7;
  undefined *puVar8;
  ushort *puVar9;
  ushort *puVar10;
  int *piVar11;
  ushort *puVar12;
  int *piVar13;
  int iVar14;
  
  puVar5 = &DAT_803c6f6c;
  puVar4 = &DAT_803c706c;
  iVar14 = 4;
  do {
    *puVar5 = 0;
    *puVar4 = 0;
    puVar5[1] = 0;
    puVar4[1] = 0;
    puVar5[2] = 0;
    puVar4[2] = 0;
    puVar5[3] = 0;
    puVar4[3] = 0;
    puVar5[4] = 0;
    puVar4[4] = 0;
    puVar5[5] = 0;
    puVar4[5] = 0;
    puVar5[6] = 0;
    puVar4[6] = 0;
    puVar5[7] = 0;
    puVar4[7] = 0;
    puVar5[8] = 0;
    puVar4[8] = 0;
    puVar5[9] = 0;
    puVar4[9] = 0;
    puVar5[10] = 0;
    puVar4[10] = 0;
    puVar5[0xb] = 0;
    puVar4[0xb] = 0;
    puVar5[0xc] = 0;
    puVar4[0xc] = 0;
    puVar5[0xd] = 0;
    puVar4[0xd] = 0;
    puVar5[0xe] = 0;
    puVar4[0xe] = 0;
    puVar5[0xf] = 0;
    puVar5 = puVar5 + 0x10;
    puVar4[0xf] = 0;
    puVar4 = puVar4 + 0x10;
    iVar14 = iVar14 + -1;
  } while (iVar14 != 0);
  iVar14 = 0;
  DAT_80436288 = 0;
  DAT_80436290 = 0;
  DAT_80436278 = 0;
  DAT_80436280 = 0;
  DAT_80436268 = 0;
  DAT_80436270 = 0;
  uRam8043628c = 0;
  uRam80436294 = 0;
  uRam8043627c = 0;
  uRam80436284 = 0;
  uRam8043626c = 0;
  uRam80436274 = 0;
  DAT_803c6f3c = 0;
  DAT_803c6f54 = 0;
  DAT_803c6f40 = 0;
  DAT_803c6f58 = 0;
  DAT_803c6f44 = 0;
  DAT_803c6f5c = 0;
  DAT_803c6f48 = 0;
  DAT_803c6f60 = 0;
  DAT_803c6f4c = 0;
  DAT_803c6f64 = 0;
  DAT_803c6f50 = 0;
  DAT_803c6f68 = 0;
  DAT_803c6efc = 0;
  DAT_803c6f1c = 0;
  DAT_803c6f00 = 0;
  DAT_803c6f20 = 0;
  DAT_803c6f04 = 0;
  DAT_803c6f24 = 0;
  DAT_803c6f08 = 0;
  DAT_803c6f28 = 0;
  DAT_803c6f0c = 0;
  DAT_803c6f2c = 0;
  DAT_803c6f10 = 0;
  DAT_803c6f30 = 0;
  DAT_803c6f14 = 0;
  DAT_803c6f34 = 0;
  DAT_803c6f18 = 0;
  DAT_803c6f38 = 0;
  DAT_803c6eac = 0;
  DAT_803c6ec0 = 0;
  DAT_803c6ed4 = 0;
  DAT_803c6ee8 = 0;
  DAT_803c6eb0 = 0;
  DAT_803c6ec4 = 0;
  DAT_803c6ed8 = 0;
  DAT_803c6eec = 0;
  DAT_803c6eb4 = 0;
  DAT_803c6ec8 = 0;
  DAT_803c6edc = 0;
  DAT_803c6ef0 = 0;
  DAT_803c6eb8 = 0;
  DAT_803c6ecc = 0;
  DAT_803c6ee0 = 0;
  DAT_803c6ef4 = 0;
  DAT_803c6ebc = 0;
  DAT_803c6ed0 = 0;
  DAT_803c6ee4 = 0;
  DAT_803c6ef8 = 0;
  DAT_803c6e4c = 0;
  DAT_803c6e64 = 0;
  DAT_803c6e7c = 0;
  DAT_803c6e94 = 0;
  DAT_803c6e50 = 0;
  DAT_803c6e68 = 0;
  DAT_803c6e80 = 0;
  DAT_803c6e98 = 0;
  DAT_803c6e54 = 0;
  piVar13 = &DAT_803c716c;
  puVar4 = &DAT_803c718c;
  puVar12 = &DAT_803c71ac;
  DAT_803c6e6c = 0;
  piVar11 = &DAT_803c71dc;
  puVar10 = &DAT_803c71cc;
  puVar9 = &DAT_803c71bc;
  DAT_803c6e84 = 0;
  puVar8 = &DAT_80436298;
  DAT_803c6e9c = 0;
  DAT_803c6e58 = 0;
  DAT_803c6e70 = 0;
  DAT_803c6e88 = 0;
  DAT_803c6ea0 = 0;
  DAT_803c6e5c = 0;
  DAT_803c6e74 = 0;
  DAT_803c6e8c = 0;
  DAT_803c6ea4 = 0;
  DAT_803c6e60 = 0;
  DAT_803c6e78 = 0;
  DAT_803c6e90 = 0;
  DAT_803c6ea8 = 0;
  do {
    __s = (void *)*piVar11;
    *piVar13 = 0;
    *puVar4 = 0;
    *puVar12 = 0;
    if (__s != (void *)0x0) {
      uVar2 = *puVar9;
      uVar3 = *puVar10;
      *piVar13 = (int)__s;
      uVar1 = *puVar8;
      for (iVar6 = 0; iVar6 < (int)(uint)uVar2; iVar6 = iVar6 + 1) {
        gnt4_memset(__s,0,(uint)uVar3);
        *(undefined1 *)((int)__s + 2) = uVar1;
        pvVar7 = (void *)((int)__s + (uint)uVar3);
        *(char *)((int)__s + 3) = (char)iVar14;
        if (iVar6 < (int)(uVar2 - 1)) {
          *(void **)((int)__s + 4) = pvVar7;
        }
        else {
          *puVar4 = __s;
        }
        __s = pvVar7;
      }
      *puVar12 = uVar2;
    }
    iVar14 = iVar14 + 1;
    puVar4 = puVar4 + 1;
    puVar12 = puVar12 + 1;
    piVar11 = piVar11 + 1;
    puVar8 = puVar8 + 1;
    puVar10 = puVar10 + 1;
    puVar9 = puVar9 + 1;
    piVar13 = piVar13 + 1;
  } while (iVar14 < 8);
  DAT_80436250 = 0;
  DAT_8043624e = 0;
  DAT_8043624c = 0;
  DAT_8043624a = 0;
  DAT_80436248 = 0;
  DAT_80436246 = 0;
  DAT_80436244 = 0;
  DAT_80436242 = 0;
  DAT_80436240 = 0;
  DAT_8043623e = 0;
  PTR_DAT_80433934[0xd1] = 0;
  PTR_DAT_80433934[0xd2] = 0;
  PTR_DAT_80433934[0xd3] = 0;
  PTR_DAT_80433934[0xd4] = 0;
  *(undefined2 *)(PTR_DAT_80433934 + 0xd6) = 0;
  PTR_DAT_80433934[0xd9] = 0;
  PTR_DAT_80433934[0xd8] = 0;
  PTR_DAT_80433934[0xda] = 0;
  PTR_DAT_80433934[0xdb] = 0;
  PTR_DAT_80433934[0xeb] = 0;
  *(undefined2 *)(PTR_DAT_80433934 + 0xe8) = 0;
  return;
}



// ==== 8008893c  zz_008893c_ ====

void * zz_008893c_(int param_1,int param_2,int param_3,int param_4)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  void *pvVar4;
  
  if (param_4 < 9) {
    iVar2 = zz_0197bec_(0);
    if (iVar2 < param_4) {
      pvVar1 = (void *)0x0;
    }
    else {
      pvVar1 = zz_0088d98_(param_1);
      if (pvVar1 != (void *)0x0) {
        *(char *)((int)pvVar1 + 1) = (char)param_2;
        *(undefined1 *)((int)pvVar1 + 0x85) = 0xff;
        if (param_2 != -1) {
          *(undefined *)((int)pvVar1 + 0x83) = (&DAT_802da700)[param_2];
          if (param_3 == 0) {
            iVar2 = (&DAT_803c706c)[param_2];
            (&DAT_803c706c)[param_2] = pvVar1;
            *(undefined4 *)((int)pvVar1 + 4) = 0;
            if (iVar2 == 0) {
              (&DAT_803c6f6c)[param_2] = pvVar1;
              *(undefined4 *)((int)pvVar1 + 8) = 0;
            }
            else {
              *(int *)((int)pvVar1 + 8) = iVar2;
              *(void **)(iVar2 + 4) = pvVar1;
            }
          }
          else {
            iVar2 = (&DAT_803c6f6c)[param_2];
            (&DAT_803c6f6c)[param_2] = pvVar1;
            *(undefined4 *)((int)pvVar1 + 8) = 0;
            if (iVar2 == 0) {
              (&DAT_803c706c)[param_2] = pvVar1;
              *(undefined4 *)((int)pvVar1 + 4) = 0;
            }
            else {
              *(int *)((int)pvVar1 + 4) = iVar2;
              *(void **)(iVar2 + 8) = pvVar1;
            }
          }
          if (*(char *)((int)pvVar1 + 2) != '\x04') {
            iVar2 = 0;
            pvVar4 = pvVar1;
            do {
              if (iVar2 < param_4) {
                uVar3 = zz_0006d4c_();
                *(undefined4 *)((int)pvVar4 + 0xe0) = uVar3;
              }
              else {
                *(undefined4 *)((int)pvVar4 + 0xe0) = 0;
              }
              iVar2 = iVar2 + 1;
              pvVar4 = (void *)((int)pvVar4 + 4);
            } while (iVar2 < 8);
            *(char *)((int)pvVar1 + 0x99) = (char)param_4;
          }
        }
      }
    }
  }
  else {
    pvVar1 = (void *)0x0;
  }
  return pvVar1;
}



// ==== 80088aa0  zz_0088aa0_ ====

void * zz_0088aa0_(int param_1,int param_2,uint param_3,int param_4,int param_5)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  void *pvVar4;
  
  if (param_5 < 9) {
    iVar2 = zz_0197bec_(0);
    if (iVar2 < param_5) {
      pvVar1 = (void *)0x0;
    }
    else {
      pvVar1 = zz_0088d98_(param_2);
      if (pvVar1 != (void *)0x0) {
        *(char *)((int)pvVar1 + 1) = (char)param_3;
        *(undefined1 *)((int)pvVar1 + 0x85) = 0xff;
        if (param_3 != 0xffffffff) {
          if (((((int)param_3 < 0x38) && (param_1 != 0)) && (*(char *)(param_1 + 0x83) == '\0')) &&
             ((param_3 & 7) == 0)) {
            param_3 = (int)*(char *)(param_1 + 0x3e4) + param_3 + 1;
          }
          *(char *)((int)pvVar1 + 1) = (char)param_3;
          *(undefined *)((int)pvVar1 + 0x83) = (&DAT_802da700)[param_3];
          if (param_4 == 0) {
            iVar2 = (&DAT_803c706c)[param_3];
            (&DAT_803c706c)[param_3] = pvVar1;
            *(undefined4 *)((int)pvVar1 + 4) = 0;
            if (iVar2 == 0) {
              (&DAT_803c6f6c)[param_3] = pvVar1;
              *(undefined4 *)((int)pvVar1 + 8) = 0;
            }
            else {
              *(int *)((int)pvVar1 + 8) = iVar2;
              *(void **)(iVar2 + 4) = pvVar1;
            }
          }
          else {
            iVar2 = (&DAT_803c6f6c)[param_3];
            (&DAT_803c6f6c)[param_3] = pvVar1;
            *(undefined4 *)((int)pvVar1 + 8) = 0;
            if (iVar2 == 0) {
              (&DAT_803c706c)[param_3] = pvVar1;
              *(undefined4 *)((int)pvVar1 + 4) = 0;
            }
            else {
              *(int *)((int)pvVar1 + 4) = iVar2;
              *(void **)(iVar2 + 8) = pvVar1;
            }
          }
          if (*(char *)((int)pvVar1 + 2) != '\x04') {
            iVar2 = 0;
            pvVar4 = pvVar1;
            do {
              if (iVar2 < param_5) {
                uVar3 = zz_0006d4c_();
                *(undefined4 *)((int)pvVar4 + 0xe0) = uVar3;
              }
              else {
                *(undefined4 *)((int)pvVar4 + 0xe0) = 0;
              }
              iVar2 = iVar2 + 1;
              pvVar4 = (void *)((int)pvVar4 + 4);
            } while (iVar2 < 8);
            *(char *)((int)pvVar1 + 0x99) = (char)param_5;
          }
        }
      }
    }
  }
  else {
    pvVar1 = (void *)0x0;
  }
  return pvVar1;
}



// ==== 80088c40  zz_0088c40_ ====

void * zz_0088c40_(int param_1,int param_2,int param_3,int param_4)

{
  void *pvVar1;
  int iVar2;
  undefined4 uVar3;
  void *pvVar4;
  
  if (param_4 < 9) {
    iVar2 = zz_0197bec_(0);
    if (iVar2 < param_4) {
      pvVar1 = (void *)0x0;
    }
    else {
      pvVar1 = zz_0088d98_(param_1);
      if (pvVar1 != (void *)0x0) {
        *(undefined1 *)((int)pvVar1 + 1) = *(undefined1 *)(param_2 + 1);
        *(undefined1 *)((int)pvVar1 + 0x85) = 0xff;
        *(undefined *)((int)pvVar1 + 0x83) = (&DAT_802da700)[*(char *)((int)pvVar1 + 1)];
        if (param_3 == 0) {
          iVar2 = *(int *)(param_2 + 4);
          *(void **)(param_2 + 4) = pvVar1;
          *(int *)((int)pvVar1 + 4) = iVar2;
          *(int *)((int)pvVar1 + 8) = param_2;
          if (iVar2 == 0) {
            (&DAT_803c706c)[*(char *)(param_2 + 1)] = pvVar1;
          }
          else {
            *(void **)(iVar2 + 8) = pvVar1;
          }
        }
        else {
          iVar2 = *(int *)(param_2 + 8);
          *(void **)(param_2 + 8) = pvVar1;
          *(int *)((int)pvVar1 + 4) = param_2;
          *(int *)((int)pvVar1 + 8) = iVar2;
          if (iVar2 == 0) {
            (&DAT_803c6f6c)[*(char *)(param_2 + 1)] = pvVar1;
          }
          else {
            *(void **)(iVar2 + 4) = pvVar1;
          }
        }
        if (*(char *)((int)pvVar1 + 2) != '\x04') {
          iVar2 = 0;
          pvVar4 = pvVar1;
          do {
            if (iVar2 < param_4) {
              uVar3 = zz_0006d4c_();
              *(undefined4 *)((int)pvVar4 + 0xe0) = uVar3;
            }
            else {
              *(undefined4 *)((int)pvVar4 + 0xe0) = 0;
            }
            iVar2 = iVar2 + 1;
            pvVar4 = (void *)((int)pvVar4 + 4);
          } while (iVar2 < 8);
          *(char *)((int)pvVar1 + 0x99) = (char)param_4;
        }
      }
    }
  }
  else {
    pvVar1 = (void *)0x0;
  }
  return pvVar1;
}



// ==== 80088d98  zz_0088d98_ ====

void * zz_0088d98_(int param_1)

{
  char cVar1;
  int iVar2;
  void *__s;
  
  __s = (void *)(&DAT_803c716c)[param_1];
  if (__s != (void *)0x0) {
    (&DAT_803c71ac)[param_1] = (&DAT_803c71ac)[param_1] + -1;
    iVar2 = *(int *)((int)__s + 4);
    (&DAT_803c716c)[param_1] = iVar2;
    if (iVar2 == 0) {
      (&DAT_803c718c)[param_1] = 0;
    }
    cVar1 = *(char *)((int)__s + 2);
    gnt4_memset(__s,0,(uint)*(ushort *)(&DAT_802da660 + cVar1 * 2));
    *(char *)((int)__s + 2) = cVar1;
    *(char *)((int)__s + 3) = (char)param_1;
  }
  return __s;
}



// ==== 80088e50  zz_0088e50_ ====

void zz_0088e50_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  char cVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined1 *puVar6;
  undefined8 uVar7;
  
  cVar1 = param_9[1];
  if (cVar1 != -1) {
    iVar3 = *(int *)(param_9 + 4);
    iVar4 = *(int *)(param_9 + 8);
    if ((iVar3 == 0) && (iVar4 == 0)) {
      iVar3 = 0;
      (&DAT_803c706c)[cVar1] = 0;
      (&DAT_803c6f6c)[(char)param_9[1]] = 0;
    }
    else if ((iVar3 == 0) && (iVar4 != 0)) {
      (&DAT_803c706c)[cVar1] = iVar4;
      *(undefined4 *)(iVar4 + 4) = 0;
    }
    else if ((iVar3 == 0) || (iVar4 != 0)) {
      *(int *)(iVar3 + 8) = iVar4;
      *(int *)(iVar4 + 4) = iVar3;
    }
    else {
      (&DAT_803c6f6c)[cVar1] = iVar3;
      *(undefined4 *)(iVar3 + 8) = 0;
    }
    if (param_9[2] != '\x04') {
      uVar7 = zz_0089444_((int)param_9);
      uVar2 = extraout_r4;
      puVar6 = param_9;
      for (iVar5 = 0; iVar5 < (char)param_9[0x99]; iVar5 = iVar5 + 1) {
        if (*(int **)(puVar6 + 0xe0) != (int *)0x0) {
          uVar7 = zz_0006d80_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int **)(puVar6 + 0xe0),uVar2,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
          uVar2 = extraout_r4_00;
        }
        puVar6 = puVar6 + 4;
      }
    }
  }
  zz_0089814_(param_9);
  return;
}



