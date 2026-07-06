// ==== 8020ab98  zz_020ab98_ ====

uint zz_020ab98_(uint param_1)

{
  uint uVar1;
  
  if ((param_1 & 8) != 0) {
    return 8;
  }
  if ((param_1 & 0x47) != 0) {
    return 0x40;
  }
  if ((param_1 & 0xff) != 0) {
    return 0x80;
  }
  if ((param_1 & 0x18000000) != 0) {
    if ((param_1 & 0x18000000) != 0x8000000) {
      return 0x40;
    }
    uVar1 = param_1 & 0xffff0000;
    if (uVar1 == 0x9000000) {
      return uVar1;
    }
    if (((int)uVar1 < 0x9000000) && (uVar1 == 0x8000000)) {
      return uVar1;
    }
    if ((param_1 & 0xffe00000) == 0x8200000) {
      return 0x8200000;
    }
    if (((param_1 & 0x80000000) != 0) && ((param_1 & 0x4000000) == 0)) {
      if ((param_1 & 0x8b100000) == 0x8b100000) {
        return 0x8b100000;
      }
      if ((param_1 & 0x2000000) == 0) {
        return 0x88000000;
      }
    }
    if ((param_1 & 0x9000000) != 0x9000000) {
      return 0x40;
    }
    return 0x9000000;
  }
  uVar1 = param_1 & 0xffff0000;
  if (uVar1 == 0x40000) {
    return uVar1;
  }
  if ((int)uVar1 < 0x40000) {
    if (uVar1 == 0x20000) {
      return uVar1;
    }
    if (((int)uVar1 < 0x20000) && (uVar1 == 0x10000)) {
      return uVar1;
    }
  }
  else {
    if (uVar1 == 0x5000000) {
      return uVar1;
    }
    if (((int)uVar1 < 0x5000000) && (uVar1 == 0x2000000)) {
      return uVar1;
    }
  }
  return 0x40;
}



// ==== 8020ace4  zz_020ace4_ ====

void zz_020ace4_(uint param_1)

{
  uint uVar1;
  
  uVar1 = gnt4_SIGetType(param_1);
  zz_020ab98_(uVar1);
  return;
}



// ==== 8020ad08  zz_020ad08_ ====

void zz_020ad08_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                uint param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  ushort uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined2 *puVar4;
  ulonglong uVar5;
  
  puVar4 = &DAT_803a4dd0;
  if (0xb < param_9) {
    param_9 = 0xb;
  }
  uVar5 = gnt4_OSDisableInterrupts_bl();
  uVar3 = (undefined4)uVar5;
  DAT_804364c8 = param_9;
  iVar2 = gnt4_VIGetTvFormat();
  if (iVar2 == 2) {
LAB_8020ad70:
    puVar4 = &DAT_803a4dd0;
  }
  else {
    if (iVar2 < 2) {
      if (iVar2 == 0) goto LAB_8020ad70;
      if (-1 < iVar2) {
        puVar4 = (undefined2 *)0x803a4e00;
        goto LAB_8020ad94;
      }
    }
    else if (iVar2 == 5) goto LAB_8020ad70;
    gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_SISetSamplingRate__unknown_TV_fo_803a4e30,uVar3,param_11,param_12,param_13,
                     param_14,param_15,param_16);
    param_9 = 0;
  }
LAB_8020ad94:
  uVar1 = DAT_cc00206c;
  if ((uVar1 & 1) == 0) {
    iVar2 = 1;
  }
  else {
    iVar2 = 2;
  }
  zz_020a0fc_(iVar2 * (uint)(ushort)puVar4[param_9 * 2],(uint)*(byte *)(puVar4 + param_9 * 2 + 1));
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 8020adec  zz_020adec_ ====

void zz_020adec_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_020ad08_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804364c8,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8020ae10  zz_020ae10_ ====

void zz_020ae10_(void)

{
  DAT_804364d0 = &DAT_80000040;
  DAT_80000048 = 0x20ae80;
  DAT_804364d4 = 1;
  return;
}



// ==== 8020ae38  FUN_8020ae38 ====

void FUN_8020ae38(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 *puVar1;
  undefined8 uVar2;
  
  puVar1 = (undefined4 *)(iRam000000c0 + -0x80000000);
  uVar2 = gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_DBExceptionDestination_803a4e68,iRam000000c0,param_11,param_12,param_13
                           ,param_14,param_15,param_16);
  gnt4_OSDumpContext_bl
            (uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1,extraout_r4,
             param_11,param_12,param_13,param_14,param_15,param_16);
  gnt4_PPCHalt();
  return;
}



// ==== 8020ae90  gnt4-__DBIsExceptionMarked ====

uint gnt4___DBIsExceptionMarked(uint param_1)

{
  return *(uint *)(DAT_804364d0 + 4) & 1 << (param_1 & 0xff);
}



// ==== 8020aeac  gnt4-DBPrintf ====

void gnt4_DBPrintf(void)

{
  return;
}



// ==== 8020aefc  gnt4-PSMTXIdentity-bl ====

/* WARNING: Removing unreachable block (ram,0x8020af20) */
/* WARNING: Removing unreachable block (ram,0x8020af1c) */
/* WARNING: Removing unreachable block (ram,0x8020af18) */
/* WARNING: Removing unreachable block (ram,0x8020af14) */
/* WARNING: Removing unreachable block (ram,0x8020af0c) */
/* WARNING: Removing unreachable block (ram,0x8020af04) */

void gnt4_PSMTXIdentity_bl(float *param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043ca6c;
  fVar1 = FLOAT_8043ca68;
  param_1[2] = FLOAT_8043ca6c;
  param_1[3] = fVar2;
  param_1[6] = fVar2;
  param_1[7] = fVar2;
  param_1[8] = fVar2;
  param_1[9] = fVar2;
  param_1[4] = fVar2;
  param_1[5] = fVar1;
  *param_1 = fVar1;
  param_1[1] = fVar2;
  param_1[10] = fVar1;
  param_1[0xb] = fVar2;
  return;
}



// ==== 8020af28  gnt4-PSMTXCopy-bl ====

/* WARNING: Removing unreachable block (ram,0x8020af54) */
/* WARNING: Removing unreachable block (ram,0x8020af50) */
/* WARNING: Removing unreachable block (ram,0x8020af4c) */
/* WARNING: Removing unreachable block (ram,0x8020af48) */
/* WARNING: Removing unreachable block (ram,0x8020af44) */
/* WARNING: Removing unreachable block (ram,0x8020af40) */
/* WARNING: Removing unreachable block (ram,0x8020af3c) */
/* WARNING: Removing unreachable block (ram,0x8020af38) */
/* WARNING: Removing unreachable block (ram,0x8020af34) */
/* WARNING: Removing unreachable block (ram,0x8020af30) */
/* WARNING: Removing unreachable block (ram,0x8020af2c) */
/* WARNING: Removing unreachable block (ram,0x8020af28) */

void gnt4_PSMTXCopy_bl(float *param_1,float *param_2)

{
  float fVar1;
  
  fVar1 = param_1[1];
  *param_2 = *param_1;
  param_2[1] = fVar1;
  fVar1 = param_1[3];
  param_2[2] = param_1[2];
  param_2[3] = fVar1;
  fVar1 = param_1[5];
  param_2[4] = param_1[4];
  param_2[5] = fVar1;
  fVar1 = param_1[7];
  param_2[6] = param_1[6];
  param_2[7] = fVar1;
  fVar1 = param_1[9];
  param_2[8] = param_1[8];
  param_2[9] = fVar1;
  fVar1 = param_1[0xb];
  param_2[10] = param_1[10];
  param_2[0xb] = fVar1;
  return;
}



// ==== 8020af5c  gnt4-PSMTXConcat-bl ====

/* WARNING: Removing unreachable block (ram,0x8020b018) */
/* WARNING: Removing unreachable block (ram,0x8020b00c) */
/* WARNING: Removing unreachable block (ram,0x8020b004) */
/* WARNING: Removing unreachable block (ram,0x8020aff0) */
/* WARNING: Removing unreachable block (ram,0x8020afe8) */
/* WARNING: Removing unreachable block (ram,0x8020afd8) */
/* WARNING: Removing unreachable block (ram,0x8020afc4) */
/* WARNING: Removing unreachable block (ram,0x8020afc0) */
/* WARNING: Removing unreachable block (ram,0x8020afb8) */
/* WARNING: Removing unreachable block (ram,0x8020afb0) */
/* WARNING: Removing unreachable block (ram,0x8020afa8) */
/* WARNING: Removing unreachable block (ram,0x8020afa0) */
/* WARNING: Removing unreachable block (ram,0x8020af98) */
/* WARNING: Removing unreachable block (ram,0x8020af90) */
/* WARNING: Removing unreachable block (ram,0x8020af88) */
/* WARNING: Removing unreachable block (ram,0x8020af80) */
/* WARNING: Removing unreachable block (ram,0x8020af70) */
/* WARNING: Removing unreachable block (ram,0x8020af68) */
/* WARNING: Removing unreachable block (ram,0x8020af60) */

void gnt4_PSMTXConcat_bl(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  
  fVar26 = DAT_80435ca4;
  fVar25 = DAT_80435ca0;
  fVar1 = *param_1;
  fVar13 = param_1[1];
  fVar2 = *param_2;
  fVar14 = param_2[1];
  fVar3 = param_2[2];
  fVar15 = param_2[3];
  fVar4 = param_2[4];
  fVar16 = param_2[5];
  fVar5 = param_1[4];
  fVar17 = param_1[5];
  fVar6 = param_2[6];
  fVar18 = param_2[7];
  fVar7 = param_1[2];
  fVar19 = param_1[3];
  fVar8 = param_1[6];
  fVar20 = param_1[7];
  fVar9 = param_2[8];
  fVar21 = param_2[9];
  fVar10 = param_2[10];
  fVar22 = param_2[0xb];
  fVar11 = param_1[8];
  fVar23 = param_1[9];
  fVar12 = param_1[10];
  fVar24 = param_1[0xb];
  *param_3 = fVar9 * fVar7 + fVar4 * fVar13 + fVar2 * fVar1;
  param_3[1] = fVar21 * fVar7 + fVar16 * fVar13 + fVar14 * fVar1;
  param_3[4] = fVar9 * fVar8 + fVar4 * fVar17 + fVar2 * fVar5;
  param_3[5] = fVar21 * fVar8 + fVar16 * fVar17 + fVar14 * fVar5;
  param_3[2] = fVar25 * fVar19 + fVar10 * fVar7 + fVar6 * fVar13 + fVar3 * fVar1;
  param_3[3] = fVar26 * fVar19 + fVar22 * fVar7 + fVar18 * fVar13 + fVar15 * fVar1;
  param_3[6] = fVar25 * fVar20 + fVar10 * fVar8 + fVar6 * fVar17 + fVar3 * fVar5;
  param_3[7] = fVar26 * fVar20 + fVar22 * fVar8 + fVar18 * fVar17 + fVar15 * fVar5;
  param_3[8] = fVar9 * fVar12 + fVar4 * fVar23 + fVar2 * fVar11;
  param_3[9] = fVar21 * fVar12 + fVar16 * fVar23 + fVar14 * fVar11;
  param_3[10] = fVar25 * fVar24 + fVar10 * fVar12 + fVar6 * fVar23 + fVar3 * fVar11;
  param_3[0xb] = fVar26 * fVar24 + fVar22 * fVar12 + fVar18 * fVar23 + fVar15 * fVar11;
  return;
}



// ==== 8020b028  gnt4-PSMTXTranspose-bl ====

/* WARNING: Removing unreachable block (ram,0x8020b06c) */
/* WARNING: Removing unreachable block (ram,0x8020b064) */
/* WARNING: Removing unreachable block (ram,0x8020b05c) */
/* WARNING: Removing unreachable block (ram,0x8020b054) */
/* WARNING: Removing unreachable block (ram,0x8020b04c) */
/* WARNING: Removing unreachable block (ram,0x8020b048) */
/* WARNING: Removing unreachable block (ram,0x8020b044) */
/* WARNING: Removing unreachable block (ram,0x8020b03c) */
/* WARNING: Removing unreachable block (ram,0x8020b034) */
/* WARNING: Removing unreachable block (ram,0x8020b02c) */

void gnt4_PSMTXTranspose_bl(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar6 = FLOAT_8043ca6c;
  fVar1 = *param_1;
  fVar4 = param_1[1];
  param_2[0xb] = FLOAT_8043ca6c;
  fVar2 = param_1[4];
  fVar5 = param_1[5];
  fVar3 = param_1[2];
  *param_2 = fVar1;
  param_2[1] = fVar2;
  fVar1 = param_1[8];
  fVar2 = param_1[9];
  param_2[4] = fVar4;
  param_2[5] = fVar5;
  param_2[8] = fVar3;
  param_2[9] = fVar3;
  param_2[2] = fVar1;
  param_2[3] = fVar6;
  fVar1 = param_1[10];
  param_2[6] = fVar2;
  param_2[7] = fVar6;
  param_2[10] = fVar1;
  return;
}



// ==== 8020b078  gnt4-PSMTXInverse-bl ====

/* WARNING: Removing unreachable block (ram,0x8020b168) */
/* WARNING: Removing unreachable block (ram,0x8020b15c) */
/* WARNING: Removing unreachable block (ram,0x8020b154) */
/* WARNING: Removing unreachable block (ram,0x8020b14c) */
/* WARNING: Removing unreachable block (ram,0x8020b140) */
/* WARNING: Removing unreachable block (ram,0x8020b138) */
/* WARNING: Removing unreachable block (ram,0x8020b12c) */
/* WARNING: Removing unreachable block (ram,0x8020b124) */
/* WARNING: Removing unreachable block (ram,0x8020b094) */
/* WARNING: Removing unreachable block (ram,0x8020b08c) */
/* WARNING: Removing unreachable block (ram,0x8020b088) */
/* WARNING: Removing unreachable block (ram,0x8020b080) */
/* WARNING: Removing unreachable block (ram,0x8020b07c) */
/* WARNING: Removing unreachable block (ram,0x8020b078) */

undefined4 gnt4_PSMTXInverse_bl(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  
  fVar3 = *param_1;
  fVar4 = param_1[1];
  fVar9 = param_1[2];
  fVar5 = param_1[4];
  fVar6 = param_1[5];
  fVar10 = param_1[6];
  fVar7 = param_1[8];
  fVar8 = param_1[9];
  fVar11 = param_1[10];
  fVar14 = fVar4 * fVar10 - fVar6 * fVar9;
  fVar15 = fVar6 * fVar11 - fVar8 * fVar10;
  fVar13 = fVar8 * fVar9 - fVar4 * fVar11;
  fVar1 = fVar7 * fVar14 + fVar5 * fVar13 + fVar3 * fVar15;
  if (fVar1 != fVar9 - fVar9) {
    fVar2 = 1.0 / fVar1;
    fVar17 = -(fVar1 * fVar2 * fVar2 - (fVar2 + fVar2));
    fVar1 = param_1[3];
    fVar15 = fVar15 * fVar17;
    fVar16 = (fVar10 * fVar7 - fVar11 * fVar5) * fVar17;
    fVar2 = param_1[7];
    fVar13 = fVar13 * fVar17;
    fVar12 = (fVar11 * fVar3 - fVar9 * fVar7) * fVar17;
    fVar11 = param_1[0xb];
    fVar14 = fVar14 * fVar17;
    fVar10 = (fVar9 * fVar5 - fVar10 * fVar3) * fVar17;
    fVar9 = (fVar5 * fVar8 - fVar6 * fVar7) * fVar17;
    fVar7 = (fVar4 * fVar7 - fVar3 * fVar8) * fVar17;
    *param_2 = fVar15;
    param_2[1] = fVar13;
    param_2[4] = fVar16;
    param_2[5] = fVar12;
    fVar17 = (fVar3 * fVar6 - fVar4 * fVar5) * fVar17;
    param_2[8] = fVar9;
    param_2[9] = fVar7;
    param_2[10] = fVar17;
    param_2[2] = fVar14;
    param_2[3] = -(fVar14 * fVar11 + fVar13 * fVar2 + fVar15 * fVar1);
    param_2[6] = fVar10;
    param_2[7] = -(fVar10 * fVar11 + fVar12 * fVar2 + fVar16 * fVar1);
    param_2[0xb] = -(fVar17 * fVar11 + fVar7 * fVar2 + fVar9 * fVar1);
    return 1;
  }
  return 0;
}



// ==== 8020b170  gnt4-PSMTXInvXpose-bl ====

/* WARNING: Removing unreachable block (ram,0x8020b230) */
/* WARNING: Removing unreachable block (ram,0x8020b22c) */
/* WARNING: Removing unreachable block (ram,0x8020b220) */
/* WARNING: Removing unreachable block (ram,0x8020b21c) */
/* WARNING: Removing unreachable block (ram,0x8020b210) */
/* WARNING: Removing unreachable block (ram,0x8020b20c) */
/* WARNING: Removing unreachable block (ram,0x8020b1fc) */
/* WARNING: Removing unreachable block (ram,0x8020b1f4) */
/* WARNING: Removing unreachable block (ram,0x8020b1e8) */
/* WARNING: Removing unreachable block (ram,0x8020b18c) */
/* WARNING: Removing unreachable block (ram,0x8020b184) */
/* WARNING: Removing unreachable block (ram,0x8020b180) */
/* WARNING: Removing unreachable block (ram,0x8020b178) */
/* WARNING: Removing unreachable block (ram,0x8020b174) */
/* WARNING: Removing unreachable block (ram,0x8020b170) */

undefined4 gnt4_PSMTXInvXpose_bl(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  
  fVar1 = *param_1;
  fVar2 = param_1[1];
  fVar7 = param_1[2];
  fVar3 = param_1[4];
  fVar4 = param_1[5];
  fVar8 = param_1[6];
  fVar5 = param_1[8];
  fVar6 = param_1[9];
  fVar9 = param_1[10];
  fVar15 = fVar2 * fVar8 - fVar4 * fVar7;
  fVar12 = fVar4 * fVar9 - fVar6 * fVar8;
  fVar11 = fVar6 * fVar7 - fVar2 * fVar9;
  fVar14 = fVar2 - fVar2;
  fVar10 = fVar5 * fVar15 + fVar3 * fVar11 + fVar1 * fVar12;
  if (fVar10 != fVar14) {
    fVar13 = 1.0 / fVar10;
    param_2[3] = fVar14;
    param_2[7] = fVar14;
    fVar10 = -(fVar10 * fVar13 * fVar13 - (fVar13 + fVar13));
    param_2[0xb] = fVar14;
    *param_2 = fVar12 * fVar10;
    param_2[1] = (fVar8 * fVar5 - fVar9 * fVar3) * fVar10;
    param_2[4] = fVar11 * fVar10;
    param_2[5] = (fVar9 * fVar1 - fVar7 * fVar5) * fVar10;
    param_2[8] = fVar15 * fVar10;
    param_2[9] = (fVar7 * fVar3 - fVar8 * fVar1) * fVar10;
    param_2[2] = (fVar3 * fVar6 - fVar4 * fVar5) * fVar10;
    param_2[6] = (fVar2 * fVar5 - fVar1 * fVar6) * fVar10;
    param_2[10] = (fVar1 * fVar4 - fVar2 * fVar3) * fVar10;
    return 1;
  }
  return 0;
}



// ==== 8020b238  gnt4-PSMTXRotRad-bl ====

void gnt4_PSMTXRotRad_bl(double param_1,float *param_2,uint param_3)

{
  double dVar1;
  float fVar2;
  
  fVar2 = gnt4_sinf((float)param_1);
  dVar1 = (double)fVar2;
  fVar2 = gnt4_cosf((float)param_1);
  gnt4_PSMTXRotTrig_bl(dVar1,(double)fVar2,param_2,param_3);
  return;
}



// ==== 8020b2a8  gnt4-PSMTXRotTrig-bl ====

/* WARNING: Removing unreachable block (ram,0x8020b2fc) */
/* WARNING: Removing unreachable block (ram,0x8020b2f8) */
/* WARNING: Removing unreachable block (ram,0x8020b2f4) */
/* WARNING: Removing unreachable block (ram,0x8020b2f0) */
/* WARNING: Removing unreachable block (ram,0x8020b2e8) */
/* WARNING: Removing unreachable block (ram,0x8020b2e0) */
/* WARNING: Removing unreachable block (ram,0x8020b2dc) */
/* WARNING: Removing unreachable block (ram,0x8020b350) */
/* WARNING: Removing unreachable block (ram,0x8020b34c) */
/* WARNING: Removing unreachable block (ram,0x8020b348) */
/* WARNING: Removing unreachable block (ram,0x8020b340) */
/* WARNING: Removing unreachable block (ram,0x8020b33c) */
/* WARNING: Removing unreachable block (ram,0x8020b330) */
/* WARNING: Removing unreachable block (ram,0x8020b328) */
/* WARNING: Removing unreachable block (ram,0x8020b324) */
/* WARNING: Removing unreachable block (ram,0x8020b320) */
/* WARNING: Removing unreachable block (ram,0x8020b31c) */
/* WARNING: Removing unreachable block (ram,0x8020b310) */
/* WARNING: Removing unreachable block (ram,0x8020b30c) */

void gnt4_PSMTXRotTrig_bl(double param_1,double param_2,float *param_3,uint param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  
  fVar4 = FLOAT_8043ca6c;
  fVar3 = FLOAT_8043ca68;
  fVar1 = (float)param_1;
  fVar2 = (float)param_2;
  uVar5 = param_4 | 0x20;
  if (uVar5 == 0x78) {
    *param_3 = FLOAT_8043ca68;
    param_3[1] = fVar4;
    param_3[2] = fVar4;
    param_3[3] = fVar4;
    param_3[4] = fVar4;
    param_3[7] = fVar4;
    param_3[8] = fVar4;
    param_3[0xb] = fVar4;
    param_3[9] = fVar1;
    param_3[10] = fVar2;
    param_3[5] = fVar2;
    param_3[6] = -fVar1;
  }
  else if (uVar5 == 0x79) {
    param_3[6] = FLOAT_8043ca6c;
    param_3[7] = fVar4;
    *param_3 = fVar2;
    param_3[1] = fVar4;
    param_3[10] = fVar2;
    param_3[0xb] = fVar4;
    param_3[4] = fVar4;
    param_3[5] = fVar4;
    param_3[2] = fVar1;
    param_3[3] = fVar1;
    param_3[8] = -fVar1;
    param_3[9] = fVar4;
  }
  else if (uVar5 == 0x7a) {
    param_3[2] = FLOAT_8043ca6c;
    param_3[3] = fVar4;
    param_3[6] = fVar4;
    param_3[7] = fVar4;
    param_3[8] = fVar4;
    param_3[9] = fVar4;
    param_3[4] = fVar1;
    param_3[5] = fVar2;
    *param_3 = fVar2;
    param_3[1] = fVar2;
    param_3[10] = fVar3;
    param_3[0xb] = fVar4;
  }
  return;
}



// ==== 8020b358  gnt4-__PSMTXRotAxisRadInternal-bl ====

/* WARNING: Removing unreachable block (ram,0x8020b400) */
/* WARNING: Removing unreachable block (ram,0x8020b3fc) */
/* WARNING: Removing unreachable block (ram,0x8020b3f4) */
/* WARNING: Removing unreachable block (ram,0x8020b3ec) */
/* WARNING: Removing unreachable block (ram,0x8020b3e4) */
/* WARNING: Removing unreachable block (ram,0x8020b3dc) */
/* WARNING: Removing unreachable block (ram,0x8020b364) */

void gnt4___PSMTXRotAxisRadInternal_bl(double param_1,double param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  fVar1 = (float)param_2;
  fVar4 = *param_4;
  fVar5 = param_4[1];
  fVar2 = (float)param_1;
  fVar3 = param_4[2];
  fVar7 = FLOAT_8043ca70 - FLOAT_8043ca70;
  fVar8 = fVar3 * fVar3 + fVar4 * fVar4 + fVar5 * fVar5;
  fVar9 = (FLOAT_8043ca70 + FLOAT_8043ca70) - fVar1;
  fVar6 = 1.0 / SQRT(fVar8);
  fVar6 = -(fVar6 * fVar6 * fVar8 - FLOAT_8043ca74) * fVar6 * FLOAT_8043ca70;
  fVar4 = fVar4 * fVar6;
  fVar5 = fVar5 * fVar6;
  fVar3 = fVar3 * fVar6;
  fVar8 = fVar4 * fVar9;
  fVar6 = fVar5 * fVar9 * fVar3;
  param_3[2] = fVar8 * fVar3 + fVar5 * fVar2;
  param_3[3] = fVar7;
  *param_3 = fVar8 * fVar4 + fVar1;
  param_3[1] = -(fVar3 * fVar2 - fVar8 * fVar5);
  param_3[4] = fVar3 * fVar2 + fVar8 * fVar5;
  param_3[5] = fVar1 + fVar5 * fVar9 * fVar5;
  param_3[6] = -(fVar4 * fVar2) + fVar6;
  param_3[7] = fVar7;
  param_3[8] = fVar8 * fVar3 + -(fVar5 * fVar2);
  param_3[9] = fVar4 * fVar2 + fVar6;
  param_3[10] = fVar3 * fVar9 * fVar3 + fVar1;
  param_3[0xb] = fVar7;
  return;
}



// ==== 8020b408  gnt4-PSMTXRotAxisRad-bl ====

void gnt4_PSMTXRotAxisRad_bl(double param_1,float *param_2,float *param_3)

{
  double dVar1;
  float fVar2;
  
  fVar2 = gnt4_sinf((float)param_1);
  dVar1 = (double)fVar2;
  fVar2 = gnt4_cosf((float)param_1);
  gnt4___PSMTXRotAxisRadInternal_bl(dVar1,(double)fVar2,param_2,param_3);
  return;
}



// ==== 8020b478  gnt4-PSMTXTrans-bl ====

/* WARNING: Removing unreachable block (ram,0x8020b48c) */
/* WARNING: Removing unreachable block (ram,0x8020b488) */

void gnt4_PSMTXTrans_bl(double param_1,double param_2,double param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043ca6c;
  fVar1 = FLOAT_8043ca68;
  param_4[3] = (float)param_1;
  param_4[7] = (float)param_2;
  param_4[1] = fVar2;
  param_4[2] = fVar2;
  param_4[8] = fVar2;
  param_4[9] = fVar2;
  param_4[4] = fVar2;
  param_4[5] = fVar1;
  param_4[6] = fVar2;
  param_4[10] = fVar1;
  param_4[0xb] = (float)param_3;
  *param_4 = fVar1;
  return;
}



// ==== 8020b4ac  zz_020b4ac_ ====

/* WARNING: Removing unreachable block (ram,0x8020b4f0) */
/* WARNING: Removing unreachable block (ram,0x8020b4ec) */
/* WARNING: Removing unreachable block (ram,0x8020b4e8) */
/* WARNING: Removing unreachable block (ram,0x8020b4e0) */
/* WARNING: Removing unreachable block (ram,0x8020b4dc) */
/* WARNING: Removing unreachable block (ram,0x8020b4d4) */
/* WARNING: Removing unreachable block (ram,0x8020b4d0) */
/* WARNING: Removing unreachable block (ram,0x8020b4c8) */
/* WARNING: Removing unreachable block (ram,0x8020b4c4) */
/* WARNING: Removing unreachable block (ram,0x8020b4bc) */
/* WARNING: Removing unreachable block (ram,0x8020b4b4) */
/* WARNING: Removing unreachable block (ram,0x8020b4ac) */

void zz_020b4ac_(double param_1,double param_2,double param_3,float *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  fVar4 = param_4[1];
  fVar1 = param_4[2];
  fVar5 = param_4[3];
  fVar2 = param_4[6];
  fVar6 = param_4[7];
  fVar3 = param_4[10];
  fVar7 = param_4[0xb];
  *param_5 = *param_4;
  param_5[1] = fVar4;
  fVar4 = param_4[4];
  fVar8 = param_4[5];
  param_5[2] = fVar1;
  param_5[3] = (float)param_1 + fVar5;
  fVar1 = param_4[8];
  fVar5 = param_4[9];
  param_5[4] = fVar4;
  param_5[5] = fVar8;
  param_5[6] = fVar2;
  param_5[7] = (float)param_2 + fVar6;
  param_5[8] = fVar1;
  param_5[9] = fVar5;
  param_5[10] = fVar3;
  param_5[0xb] = (float)param_3 + fVar7;
  return;
}



// ==== 8020b4f8  gnt4-PSMTXScale-bl ====

/* WARNING: Removing unreachable block (ram,0x8020b510) */
/* WARNING: Removing unreachable block (ram,0x8020b50c) */
/* WARNING: Removing unreachable block (ram,0x8020b504) */
/* WARNING: Removing unreachable block (ram,0x8020b500) */

void gnt4_PSMTXScale_bl(double param_1,double param_2,double param_3,float *param_4)

{
  float fVar1;
  
  fVar1 = FLOAT_8043ca6c;
  *param_4 = (float)param_1;
  param_4[1] = fVar1;
  param_4[2] = fVar1;
  param_4[3] = fVar1;
  param_4[4] = fVar1;
  param_4[5] = (float)param_2;
  param_4[6] = fVar1;
  param_4[7] = fVar1;
  param_4[8] = fVar1;
  param_4[9] = fVar1;
  param_4[10] = (float)param_3;
  param_4[0xb] = fVar1;
  return;
}



// ==== 8020b520  zz_020b520_ ====

/* WARNING: Removing unreachable block (ram,0x8020b570) */
/* WARNING: Removing unreachable block (ram,0x8020b56c) */
/* WARNING: Removing unreachable block (ram,0x8020b568) */
/* WARNING: Removing unreachable block (ram,0x8020b560) */
/* WARNING: Removing unreachable block (ram,0x8020b558) */
/* WARNING: Removing unreachable block (ram,0x8020b554) */
/* WARNING: Removing unreachable block (ram,0x8020b54c) */
/* WARNING: Removing unreachable block (ram,0x8020b548) */
/* WARNING: Removing unreachable block (ram,0x8020b540) */
/* WARNING: Removing unreachable block (ram,0x8020b538) */
/* WARNING: Removing unreachable block (ram,0x8020b52c) */
/* WARNING: Removing unreachable block (ram,0x8020b524) */

void zz_020b520_(double param_1,double param_2,double param_3,float *param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  
  fVar1 = (float)param_1;
  fVar8 = param_4[1];
  fVar2 = (float)param_2;
  fVar4 = param_4[2];
  fVar9 = param_4[3];
  fVar3 = (float)param_3;
  fVar5 = param_4[4];
  fVar10 = param_4[5];
  fVar6 = param_4[6];
  fVar11 = param_4[7];
  fVar7 = param_4[8];
  fVar12 = param_4[9];
  *param_5 = *param_4 * fVar1;
  param_5[1] = fVar8 * fVar1;
  fVar8 = param_4[10];
  fVar13 = param_4[0xb];
  param_5[2] = fVar4 * fVar1;
  param_5[3] = fVar9 * fVar1;
  param_5[4] = fVar5 * fVar2;
  param_5[5] = fVar10 * fVar2;
  param_5[6] = fVar6 * fVar2;
  param_5[7] = fVar11 * fVar2;
  param_5[8] = fVar7 * fVar3;
  param_5[9] = fVar12 * fVar3;
  param_5[10] = fVar8 * fVar3;
  param_5[0xb] = fVar13 * fVar3;
  return;
}



// ==== 8020b578  gnt4-PSMTXQuat-bl ====

/* WARNING: Removing unreachable block (ram,0x8020b614) */
/* WARNING: Removing unreachable block (ram,0x8020b610) */
/* WARNING: Removing unreachable block (ram,0x8020b604) */
/* WARNING: Removing unreachable block (ram,0x8020b600) */
/* WARNING: Removing unreachable block (ram,0x8020b5f4) */
/* WARNING: Removing unreachable block (ram,0x8020b5e0) */
/* WARNING: Removing unreachable block (ram,0x8020b5d4) */
/* WARNING: Removing unreachable block (ram,0x8020b5c8) */
/* WARNING: Removing unreachable block (ram,0x8020b580) */
/* WARNING: Removing unreachable block (ram,0x8020b57c) */

void gnt4_PSMTXQuat_bl(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  
  fVar12 = FLOAT_8043ca68;
  fVar1 = *param_2;
  fVar3 = param_2[1];
  fVar2 = param_2[2];
  fVar4 = param_2[3];
  fVar5 = FLOAT_8043ca68 - FLOAT_8043ca68;
  fVar6 = FLOAT_8043ca68 + FLOAT_8043ca68;
  fVar8 = fVar3 * fVar3;
  fVar9 = fVar2 * fVar2 + fVar1 * fVar1;
  fVar7 = fVar9 + fVar4 * fVar4 + fVar8;
  fVar10 = 1.0 / fVar7;
  fVar10 = fVar10 * -(fVar7 * fVar10 - fVar6) * fVar6;
  param_1[3] = fVar5;
  param_1[0xb] = fVar5;
  param_1[10] = -((fVar1 * fVar1 + fVar8) * fVar10 - fVar12);
  fVar11 = fVar1 * fVar2 + fVar3 * fVar4;
  fVar7 = fVar3 * fVar2 + fVar1 * fVar4;
  param_1[4] = (fVar1 * fVar3 + fVar2 * fVar4) * fVar10;
  param_1[5] = -(fVar9 * fVar10 - fVar12);
  *param_1 = -((fVar2 * fVar2 + fVar8) * fVar10 - fVar12);
  param_1[1] = (fVar1 * fVar3 - fVar2 * fVar4) * fVar10;
  param_1[2] = fVar11 * fVar10;
  param_1[6] = -(fVar1 * fVar4 * fVar6 - fVar7) * fVar10;
  param_1[7] = fVar5;
  param_1[8] = -(fVar3 * fVar4 * fVar6 - fVar11) * fVar10;
  param_1[9] = fVar7 * fVar10;
  return;
}



// ==== 8020b61c  gnt4-C_MTXLookAt-bl ====

void gnt4_C_MTXLookAt_bl(float *param_1,float *param_2,float *param_3,float *param_4)

{
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  
  local_20 = *param_2 - *param_4;
  local_1c = param_2[1] - param_4[1];
  local_18 = param_2[2] - param_4[2];
  gnt4_PSVECNormalize_bl(&local_20,&local_20);
  gnt4_PSVECCrossProduct_bl(param_3,&local_20,&local_2c);
  gnt4_PSVECNormalize_bl(&local_2c,&local_2c);
  gnt4_PSVECCrossProduct_bl(&local_20,&local_2c,&local_38);
  *param_1 = local_2c;
  param_1[1] = local_28;
  param_1[2] = local_24;
  param_1[3] = -(param_2[2] * local_24 + *param_2 * local_2c + param_2[1] * local_28);
  param_1[4] = local_38;
  param_1[5] = local_34;
  param_1[6] = local_30;
  param_1[7] = -(param_2[2] * local_30 + *param_2 * local_38 + param_2[1] * local_34);
  param_1[8] = local_20;
  param_1[9] = local_1c;
  param_1[10] = local_18;
  param_1[0xb] = -(param_2[2] * local_18 + *param_2 * local_20 + param_2[1] * local_1c);
  return;
}



// ==== 8020b7a8  gnt4-PSMTXMultVec-bl ====

/* WARNING: Removing unreachable block (ram,0x8020b7f4) */
/* WARNING: Removing unreachable block (ram,0x8020b7e8) */
/* WARNING: Removing unreachable block (ram,0x8020b7e0) */
/* WARNING: Removing unreachable block (ram,0x8020b7d8) */
/* WARNING: Removing unreachable block (ram,0x8020b7d0) */
/* WARNING: Removing unreachable block (ram,0x8020b7c8) */
/* WARNING: Removing unreachable block (ram,0x8020b7c0) */
/* WARNING: Removing unreachable block (ram,0x8020b7b8) */
/* WARNING: Removing unreachable block (ram,0x8020b7b0) */
/* WARNING: Removing unreachable block (ram,0x8020b7ac) */
/* WARNING: Removing unreachable block (ram,0x8020b7a8) */

void gnt4_PSMTXMultVec_bl(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  fVar1 = *param_2;
  fVar7 = param_2[1];
  fVar2 = param_2[2];
  fVar3 = param_1[4];
  fVar8 = param_1[5];
  fVar4 = param_1[6];
  fVar9 = param_1[7];
  *param_3 = param_1[2] * fVar2 + *param_1 * fVar1 + param_1[3] * 1.0 + param_1[1] * fVar7;
  fVar5 = param_1[8];
  fVar10 = param_1[9];
  fVar6 = param_1[10];
  fVar11 = param_1[0xb];
  param_3[1] = fVar4 * fVar2 + fVar3 * fVar1 + fVar9 * 1.0 + fVar8 * fVar7;
  param_3[2] = fVar6 * fVar2 + fVar5 * fVar1 + fVar11 * 1.0 + fVar10 * fVar7;
  return;
}



// ==== 8020b7fc  gnt4-PSMTXMultVecSR-bl ====

/* WARNING: Removing unreachable block (ram,0x8020b848) */
/* WARNING: Removing unreachable block (ram,0x8020b840) */
/* WARNING: Removing unreachable block (ram,0x8020b838) */
/* WARNING: Removing unreachable block (ram,0x8020b82c) */
/* WARNING: Removing unreachable block (ram,0x8020b824) */
/* WARNING: Removing unreachable block (ram,0x8020b81c) */
/* WARNING: Removing unreachable block (ram,0x8020b814) */
/* WARNING: Removing unreachable block (ram,0x8020b80c) */
/* WARNING: Removing unreachable block (ram,0x8020b804) */
/* WARNING: Removing unreachable block (ram,0x8020b800) */
/* WARNING: Removing unreachable block (ram,0x8020b7fc) */

void gnt4_PSMTXMultVecSR_bl(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  
  fVar1 = *param_2;
  fVar7 = param_2[1];
  fVar2 = param_1[4];
  fVar8 = param_1[5];
  fVar3 = param_1[8];
  fVar9 = param_1[9];
  fVar4 = param_2[2];
  fVar5 = param_1[6];
  fVar6 = param_1[10];
  *param_3 = param_1[2] * fVar4 + *param_1 * fVar1 + param_1[1] * fVar7;
  param_3[1] = fVar5 * fVar4 + fVar2 * fVar1 + fVar8 * fVar7;
  param_3[2] = fVar6 * fVar4 + fVar3 * fVar1 + fVar9 * fVar7;
  return;
}



// ==== 8020b850  gnt4-C_MTXFrustum-bl ====

void gnt4_C_MTXFrustum_bl
               (double param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,float *param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  double dVar6;
  
  fVar3 = FLOAT_8043ca78;
  dVar6 = (double)FLOAT_8043ca7c;
  fVar1 = FLOAT_8043ca78 / (float)(param_4 - param_3);
  fVar2 = FLOAT_8043ca78 / (float)(param_1 - param_2);
  *param_7 = (float)(dVar6 * param_5) * fVar1;
  fVar4 = FLOAT_8043ca80;
  dVar5 = (double)(fVar3 / (float)(param_6 - param_5));
  param_7[1] = FLOAT_8043ca80;
  param_7[2] = fVar1 * (float)(param_4 + param_3);
  param_7[3] = fVar4;
  param_7[4] = fVar4;
  param_7[5] = (float)(dVar6 * param_5) * fVar2;
  param_7[6] = fVar2 * (float)(param_1 + param_2);
  param_7[7] = fVar4;
  param_7[8] = fVar4;
  param_7[9] = fVar4;
  param_7[10] = (float)(-param_5 * dVar5);
  param_7[0xb] = (float)(dVar5 * -(double)(float)(param_6 * param_5));
  param_7[0xc] = fVar4;
  param_7[0xd] = fVar4;
  param_7[0xe] = FLOAT_8043ca84;
  param_7[0xf] = fVar4;
  return;
}



// ==== 8020b8ec  gnt4-C_MTXPerspective-bl ====

void gnt4_C_MTXPerspective_bl
               (double param_1,double param_2,double param_3,double param_4,float *param_5)

{
  float fVar1;
  float fVar2;
  double dVar3;
  float fVar4;
  
  fVar4 = gnt4_tanf(FLOAT_8043ca8c * (float)((double)FLOAT_8043ca88 * param_1));
  fVar1 = FLOAT_8043ca78;
  fVar4 = FLOAT_8043ca78 / fVar4;
  *param_5 = (float)((double)fVar4 / param_2);
  fVar2 = FLOAT_8043ca80;
  dVar3 = (double)(fVar1 / (float)(param_4 - param_3));
  param_5[1] = FLOAT_8043ca80;
  param_5[2] = fVar2;
  param_5[3] = fVar2;
  param_5[4] = fVar2;
  param_5[5] = fVar4;
  param_5[6] = fVar2;
  param_5[7] = fVar2;
  param_5[8] = fVar2;
  param_5[9] = fVar2;
  param_5[10] = (float)(-param_3 * dVar3);
  param_5[0xb] = (float)(dVar3 * -(double)(float)(param_4 * param_3));
  param_5[0xc] = fVar2;
  param_5[0xd] = fVar2;
  param_5[0xe] = FLOAT_8043ca84;
  param_5[0xf] = fVar2;
  return;
}



// ==== 8020b9bc  gnt4-C_MTXOrtho-bl ====

void gnt4_C_MTXOrtho_bl(double param_1,double param_2,double param_3,double param_4,double param_5,
                       double param_6,float *param_7)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  double dVar6;
  
  fVar4 = FLOAT_8043ca7c;
  fVar3 = FLOAT_8043ca78;
  fVar1 = FLOAT_8043ca78 / (float)(param_4 - param_3);
  fVar2 = FLOAT_8043ca78 / (float)(param_1 - param_2);
  *param_7 = FLOAT_8043ca7c * fVar1;
  fVar5 = FLOAT_8043ca80;
  param_7[1] = FLOAT_8043ca80;
  dVar6 = (double)(fVar3 / (float)(param_6 - param_5));
  param_7[2] = fVar5;
  param_7[3] = fVar1 * -(float)(param_4 + param_3);
  param_7[4] = fVar5;
  param_7[5] = fVar4 * fVar2;
  param_7[6] = fVar5;
  param_7[7] = fVar2 * -(float)(param_1 + param_2);
  param_7[8] = fVar5;
  param_7[9] = fVar5;
  param_7[10] = (float)((double)FLOAT_8043ca84 * dVar6);
  param_7[0xb] = (float)(-param_6 * dVar6);
  param_7[0xc] = fVar5;
  param_7[0xd] = fVar5;
  param_7[0xe] = fVar5;
  param_7[0xf] = fVar3;
  return;
}



// ==== 8020ba54  gnt4-PSVECAdd-bl ====

/* WARNING: Removing unreachable block (ram,0x8020ba70) */
/* WARNING: Removing unreachable block (ram,0x8020ba68) */
/* WARNING: Removing unreachable block (ram,0x8020ba64) */
/* WARNING: Removing unreachable block (ram,0x8020ba60) */
/* WARNING: Removing unreachable block (ram,0x8020ba58) */
/* WARNING: Removing unreachable block (ram,0x8020ba54) */

void gnt4_PSVECAdd_bl(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  
  fVar1 = param_1[1];
  fVar2 = param_2[1];
  *param_3 = *param_1 + *param_2;
  param_3[1] = fVar1 + fVar2;
  param_3[2] = param_1[2] + param_2[2];
  return;
}



// ==== 8020ba78  gnt4-PSVECSubtract-bl ====

/* WARNING: Removing unreachable block (ram,0x8020ba94) */
/* WARNING: Removing unreachable block (ram,0x8020ba8c) */
/* WARNING: Removing unreachable block (ram,0x8020ba88) */
/* WARNING: Removing unreachable block (ram,0x8020ba84) */
/* WARNING: Removing unreachable block (ram,0x8020ba7c) */
/* WARNING: Removing unreachable block (ram,0x8020ba78) */

void gnt4_PSVECSubtract_bl(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  
  fVar1 = param_1[1];
  fVar2 = param_2[1];
  *param_3 = *param_1 - *param_2;
  param_3[1] = fVar1 - fVar2;
  param_3[2] = param_1[2] - param_2[2];
  return;
}



// ==== 8020ba9c  gnt4-PSQUATScale-bl ====

/* WARNING: Removing unreachable block (ram,0x8020bab0) */
/* WARNING: Removing unreachable block (ram,0x8020baa8) */
/* WARNING: Removing unreachable block (ram,0x8020baa0) */
/* WARNING: Removing unreachable block (ram,0x8020ba9c) */

void gnt4_PSQUATScale_bl(double param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  
  fVar2 = param_2[1];
  fVar1 = param_2[2];
  *param_3 = (float)((double)*param_2 * param_1);
  param_3[1] = (float)((double)fVar2 * param_1);
  param_3[2] = (float)((double)fVar1 * param_1);
  return;
}



// ==== 8020bab8  gnt4-PSVECNormalize-bl ====

/* WARNING: Removing unreachable block (ram,0x8020baf4) */
/* WARNING: Removing unreachable block (ram,0x8020baec) */
/* WARNING: Removing unreachable block (ram,0x8020bac8) */
/* WARNING: Removing unreachable block (ram,0x8020bac0) */

void gnt4_PSVECNormalize_bl(float *param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  
  fVar1 = *param_1;
  fVar3 = param_1[1];
  fVar2 = param_1[2];
  fVar5 = fVar2 * fVar2 + fVar1 * fVar1 + fVar3 * fVar3;
  fVar4 = 1.0 / SQRT(fVar5);
  fVar4 = -(fVar4 * fVar4 * fVar5 - FLOAT_8043ca94) * fVar4 * FLOAT_8043ca90;
  *param_2 = fVar1 * fVar4;
  param_2[1] = fVar3 * fVar4;
  param_2[2] = fVar2 * fVar4;
  return;
}



// ==== 8020bafc  gnt4-PSVECSquareMag-bl ====

/* WARNING: Removing unreachable block (ram,0x8020bafc) */

double gnt4_PSVECSquareMag_bl(float *param_1)

{
  return (double)param_1[2] * (double)param_1[2] + (double)*param_1 * (double)*param_1 +
         (double)param_1[1] * (double)param_1[1];
}



// ==== 8020bb14  gnt4-PSVECMag-bl ====

/* WARNING: Removing unreachable block (ram,0x8020bb18) */

double gnt4_PSVECMag_bl(float *param_1)

{
  double dVar1;
  double dVar2;
  double dVar3;
  
  dVar3 = (double)FLOAT_8043ca90;
  dVar2 = (double)param_1[2] * (double)param_1[2] + (double)*param_1 * (double)*param_1 +
          (double)param_1[1] * (double)param_1[1];
  if (dVar2 != (double)(float)(dVar3 - dVar3)) {
    dVar1 = 1.0 / SQRT(dVar2);
    dVar2 = (double)(float)(dVar2 * (double)(-(float)((double)(float)(dVar1 * dVar1) * dVar2 -
                                                     (double)FLOAT_8043ca94) *
                                            (float)(dVar1 * dVar3)));
  }
  return dVar2;
}



// ==== 8020bb58  gnt4-PSQUATDotProduct-bl ====

/* WARNING: Removing unreachable block (ram,0x8020bb68) */
/* WARNING: Removing unreachable block (ram,0x8020bb64) */
/* WARNING: Removing unreachable block (ram,0x8020bb5c) */
/* WARNING: Removing unreachable block (ram,0x8020bb58) */

double gnt4_PSQUATDotProduct_bl(float *param_1,float *param_2)

{
  return (double)*param_1 * (double)*param_2 + (double)param_1[1] * (double)param_2[1] +
         (double)param_1[2] * (double)param_2[2];
}



// ==== 8020bb78  gnt4-PSVECCrossProduct-bl ====

/* WARNING: Removing unreachable block (ram,0x8020bbac) */
/* WARNING: Removing unreachable block (ram,0x8020bba4) */
/* WARNING: Removing unreachable block (ram,0x8020bb80) */
/* WARNING: Removing unreachable block (ram,0x8020bb78) */

void gnt4_PSVECCrossProduct_bl(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  
  fVar3 = *param_2;
  fVar5 = param_2[1];
  fVar1 = param_1[2];
  fVar4 = *param_1;
  fVar6 = param_1[1];
  fVar2 = param_2[2];
  *param_3 = fVar6 * fVar2 - fVar5 * fVar1;
  param_3[1] = -(fVar4 * fVar2 - fVar3 * fVar1);
  param_3[2] = -(fVar6 * fVar3 - fVar5 * fVar4);
  return;
}



// ==== 8020bbb4  zz_020bbb4_ ====

void zz_020bbb4_(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  double dVar2;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  float local_14;
  float local_10;
  
  local_18 = -*param_1;
  local_14 = -param_1[1];
  local_10 = -param_1[2];
  gnt4_PSVECNormalize_bl(&local_18,&local_18);
  gnt4_PSVECNormalize_bl(param_2,&local_24);
  dVar2 = gnt4_PSQUATDotProduct_bl(&local_18,&local_24);
  fVar1 = FLOAT_8043ca98;
  *param_3 = (float)((double)(FLOAT_8043ca98 * local_24) * dVar2) - local_18;
  param_3[1] = (float)((double)(fVar1 * local_20) * dVar2) - local_14;
  param_3[2] = (float)((double)(fVar1 * local_1c) * dVar2) - local_10;
  gnt4_PSVECNormalize_bl(param_3,param_3);
  return;
}



// ==== 8020bc88  gnt4-PSVECSquareDistance-bl ====

/* WARNING: Removing unreachable block (ram,0x8020bc98) */
/* WARNING: Removing unreachable block (ram,0x8020bc94) */
/* WARNING: Removing unreachable block (ram,0x8020bc8c) */
/* WARNING: Removing unreachable block (ram,0x8020bc88) */

double gnt4_PSVECSquareDistance_bl(float *param_1,float *param_2)

{
  return ((double)*param_1 - (double)*param_2) * ((double)*param_1 - (double)*param_2) +
         ((double)param_1[1] - (double)param_2[1]) * ((double)param_1[1] - (double)param_2[1]) +
         ((double)param_1[2] - (double)param_2[2]) * ((double)param_1[2] - (double)param_2[2]);
}



// ==== 8020bcb0  zz_020bcb0_ ====

void zz_020bcb0_(float *param_1,float *param_2)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_18 [3];
  int local_c [3];
  
  local_c[0] = DAT_802b4488;
  local_c[1] = DAT_802b448c;
  local_c[2] = DAT_802b4490;
  dVar6 = (double)(param_2[10] + *param_2 + param_2[5]);
  if (dVar6 <= (double)FLOAT_8043caa0) {
    uVar2 = (uint)(*param_2 < param_2[5]);
    if (param_2[uVar2 * 5] < param_2[10]) {
      uVar2 = 2;
    }
    iVar3 = local_c[uVar2];
    iVar4 = local_c[iVar3];
    dVar6 = (double)(FLOAT_8043cab8 +
                    (param_2[uVar2 * 5] - (param_2[iVar3 * 5] + param_2[iVar4 * 5])));
    if ((double)FLOAT_8043caa0 < dVar6) {
      dVar5 = 1.0 / SQRT(dVar6);
      dVar5 = DOUBLE_8043caa8 * dVar5 * (DOUBLE_8043cab0 - dVar6 * dVar5 * dVar5);
      dVar5 = DOUBLE_8043caa8 * dVar5 * (DOUBLE_8043cab0 - dVar6 * dVar5 * dVar5);
      dVar6 = (double)(float)(dVar6 * DOUBLE_8043caa8 * dVar5 *
                                      (DOUBLE_8043cab0 - dVar6 * dVar5 * dVar5));
    }
    local_18[uVar2] = (float)((double)FLOAT_8043cabc * dVar6);
    if ((double)FLOAT_8043caa0 != dVar6) {
      dVar6 = (double)(float)((double)FLOAT_8043cabc / dVar6);
    }
    param_1[3] = (float)(dVar6 * (double)(param_2[iVar4 * 4 + iVar3] - param_2[iVar3 * 4 + iVar4]));
    local_18[iVar3] =
         (float)(dVar6 * (double)(param_2[uVar2 * 4 + iVar3] + param_2[iVar3 * 4 + uVar2]));
    local_18[iVar4] =
         (float)(dVar6 * (double)(param_2[uVar2 * 4 + iVar4] + param_2[iVar4 * 4 + uVar2]));
    *param_1 = local_18[0];
    param_1[1] = local_18[1];
    param_1[2] = local_18[2];
  }
  else {
    dVar6 = (double)(float)((double)FLOAT_8043cab8 + dVar6);
    if ((double)FLOAT_8043caa0 < dVar6) {
      dVar5 = 1.0 / SQRT(dVar6);
      dVar5 = DOUBLE_8043caa8 * dVar5 * (DOUBLE_8043cab0 - dVar6 * dVar5 * dVar5);
      dVar5 = DOUBLE_8043caa8 * dVar5 * (DOUBLE_8043cab0 - dVar6 * dVar5 * dVar5);
      dVar6 = (double)(float)(dVar6 * DOUBLE_8043caa8 * dVar5 *
                                      (DOUBLE_8043cab0 - dVar6 * dVar5 * dVar5));
    }
    fVar1 = (float)((double)FLOAT_8043cabc / dVar6);
    param_1[3] = (float)((double)FLOAT_8043cabc * dVar6);
    *param_1 = fVar1 * (param_2[9] - param_2[6]);
    param_1[1] = fVar1 * (param_2[2] - param_2[8]);
    param_1[2] = fVar1 * (param_2[4] - param_2[1]);
  }
  return;
}



// ==== 8020bf08  C_QUATSlerp ====

void C_QUATSlerp(double param_1,float *param_2,float *param_3,float *param_4)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  float fVar5;
  
  dVar3 = (double)FLOAT_8043cab8;
  fVar5 = param_2[3] * param_3[3] +
          param_2[2] * param_3[2] + *param_2 * *param_3 + param_2[1] * param_3[1];
  if (fVar5 < FLOAT_8043caa0) {
    fVar5 = -fVar5;
    dVar3 = -dVar3;
  }
  if (FLOAT_8043cac0 < fVar5) {
    dVar3 = dVar3 * param_1;
    dVar4 = (double)(float)((double)FLOAT_8043cab8 - param_1);
  }
  else {
    fVar5 = tanf(fVar5);
    dVar1 = (double)fVar5;
    fVar5 = gnt4_sinf(fVar5);
    dVar2 = (double)fVar5;
    fVar5 = gnt4_sinf((float)((double)(float)((double)FLOAT_8043cab8 - param_1) * dVar1));
    dVar4 = (double)(float)((double)fVar5 / dVar2);
    fVar5 = gnt4_sinf((float)(param_1 * dVar1));
    dVar3 = dVar3 * (double)(float)((double)fVar5 / dVar2);
  }
  fVar5 = (float)dVar3;
  *param_4 = (float)(dVar4 * (double)*param_2) + fVar5 * *param_3;
  param_4[1] = (float)(dVar4 * (double)param_2[1]) + fVar5 * param_3[1];
  param_4[2] = (float)(dVar4 * (double)param_2[2]) + fVar5 * param_3[2];
  param_4[3] = (float)(dVar4 * (double)param_2[3]) + fVar5 * param_3[3];
  return;
}



// ==== 8020c07c  gnt4-__DVDInitWA-bl ====

void gnt4___DVDInitWA_bl(void)

{
  DAT_8043651c = 0;
  DAT_803d7970 = 0xffffffff;
  gnt4___DVDLowSetWAType_bl(0,0);
  gnt4_OSInitAlarm();
  return;
}



// ==== 8020c0bc  gnt4-__DVDInterruptHandler-bl ====

void gnt4___DVDInterruptHandler_bl(undefined4 param_1,uint param_2)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  code *pcVar9;
  uint uVar10;
  longlong lVar11;
  longlong lVar12;
  undefined1 auStack_2e0 [716];
  
  lVar11 = CONCAT44(DAT_80436508,DAT_8043650c);
  uVar10 = 0;
  if (DAT_80436518 != 0) {
    lVar11 = gnt4___OSGetSystemTime_bl();
    DAT_80435ca8 = 0;
    DAT_803d7a28 = DAT_803d7a34;
    DAT_803d7a2c = DAT_803d7a38;
    DAT_803d7a30 = DAT_803d7a3c;
    if (DAT_804364d8 == 1) {
      uVar10 = 8;
    }
  }
  DAT_80436508 = (undefined4)((ulonglong)lVar11 >> 0x20);
  DAT_8043650c = (undefined4)lVar11;
  DAT_80436518 = 0;
  DAT_804364d8 = 0;
  uVar3 = DAT_cc006000;
  uVar2 = (uVar3 & 0x2a) << 1 & uVar3 & 0x54;
  if ((uVar2 & 0x40) != 0) {
    uVar10 = 8;
  }
  if ((uVar2 & 0x10) != 0) {
    uVar10 = uVar10 | 1;
  }
  if ((uVar2 & 4) != 0) {
    uVar10 = uVar10 | 2;
  }
  if (uVar10 != 0) {
    DAT_804364f0 = 0;
    gnt4_OSCancelAlarm_bl((int *)&DAT_803d79d8);
    lVar11 = CONCAT44(DAT_80436508,DAT_8043650c);
  }
  DAT_80436508 = (undefined4)((ulonglong)lVar11 >> 0x20);
  DAT_8043650c = (undefined4)lVar11;
  DAT_cc006000 = uVar2 | uVar3 & 0x2a;
  if (DAT_804364f0 == 0) {
LAB_8020c238:
    if (DAT_804364f4 == 0) {
      DAT_cc006004 = 0;
    }
    else {
      uVar3 = DAT_cc006004;
      uVar2 = uVar3 & 4 & (uVar3 & 2) << 1;
      if (uVar2 != 0) {
        uVar10 = uVar10 | 4;
      }
      DAT_cc006004 = uVar2 | uVar3 & 2;
      DAT_804364f4 = 0;
    }
  }
  else {
    lVar12 = gnt4___OSGetSystemTime_bl();
    lVar11 = CONCAT44(DAT_80436508,DAT_8043650c);
    if (((uint)lVar12 - DAT_804364ec < (DAT_800000f8 / 4000) * 200) + 0x80000000 <=
        ((int)((ulonglong)lVar12 >> 0x20) - ((uint)((uint)lVar12 < DAT_804364ec) + DAT_804364e8) ^
        0x80000000)) goto LAB_8020c238;
    uVar2 = DAT_cc006004;
    if ((uVar2 & 4 & (uVar2 & 2) << 1) != 0) {
      if (DAT_804364e4 != (code *)0x0) {
        (*DAT_804364e4)(4);
      }
      DAT_804364e4 = (code *)0x0;
    }
    lVar11 = CONCAT44(DAT_80436508,DAT_8043650c);
    uVar4 = DAT_cc006004;
    DAT_cc006004 = uVar4;
  }
  DAT_80436508 = (undefined4)((ulonglong)lVar11 >> 0x20);
  DAT_8043650c = (undefined4)lVar11;
  if (((uVar10 & 8) != 0) && (DAT_804364f8 == 0)) {
    uVar10 = uVar10 & 0xfffffff7;
  }
  if ((uVar10 & 1) == 0) {
    DAT_803d7970 = 0xffffffff;
    DAT_8043651c = 0;
  }
  else {
    if ((&DAT_803d7970)[DAT_8043651c * 5] == 1) {
      iVar5 = DAT_8043651c * 5;
      iVar6 = DAT_8043651c * 5;
      iVar7 = DAT_8043651c * 5;
      iVar8 = DAT_8043651c * 5;
      DAT_8043651c = DAT_8043651c + 1;
      gnt4_Read_bl((&DAT_803d7974)[iVar5],(&DAT_803d7978)[iVar6],(&DAT_803d797c)[iVar7],
                   (&DAT_803d7980)[iVar8]);
      lVar11 = CONCAT44(DAT_80436508,DAT_8043650c);
      bVar1 = true;
    }
    else if ((&DAT_803d7970)[DAT_8043651c * 5] == 2) {
      iVar5 = DAT_8043651c * 5;
      iVar6 = DAT_8043651c * 5;
      DAT_8043651c = DAT_8043651c + 1;
      gnt4_DVDLowSeek_bl((&DAT_803d797c)[iVar5],(&DAT_803d7980)[iVar6]);
      lVar11 = CONCAT44(DAT_80436508,DAT_8043650c);
      bVar1 = true;
    }
    else {
      bVar1 = false;
    }
    if (bVar1) goto LAB_8020c388;
  }
  DAT_80436508 = (undefined4)((ulonglong)lVar11 >> 0x20);
  DAT_8043650c = (undefined4)lVar11;
  gnt4_OSClearContext_bl((int)auStack_2e0);
  gnt4_OSSetCurrentContext_bl((uint)auStack_2e0);
  pcVar9 = DAT_804364e0;
  if (uVar10 != 0) {
    bVar1 = DAT_804364e0 != (code *)0x0;
    DAT_804364e0 = (code *)0x0;
    if (bVar1) {
      (*pcVar9)(uVar10);
    }
    DAT_804364f8 = 0;
  }
  gnt4_OSClearContext_bl((int)auStack_2e0);
  gnt4_OSSetCurrentContext_bl(param_2);
  lVar11 = CONCAT44(DAT_80436508,DAT_8043650c);
LAB_8020c388:
  DAT_80436508 = (undefined4)((ulonglong)lVar11 >> 0x20);
  DAT_8043650c = (undefined4)lVar11;
  return;
}



// ==== 8020c39c  gnt4-AlarmHandler_-bl ====

void gnt4_AlarmHandler__bl(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  if ((&DAT_803d7970)[DAT_8043651c * 5] == 1) {
    iVar1 = DAT_8043651c * 5;
    iVar2 = DAT_8043651c * 5;
    iVar3 = DAT_8043651c * 5;
    iVar4 = DAT_8043651c * 5;
    DAT_8043651c = DAT_8043651c + 1;
    gnt4_Read_bl((&DAT_803d7974)[iVar1],(&DAT_803d7978)[iVar2],(&DAT_803d797c)[iVar3],
                 (&DAT_803d7980)[iVar4]);
  }
  else if ((&DAT_803d7970)[DAT_8043651c * 5] == 2) {
    iVar1 = DAT_8043651c * 5;
    iVar2 = DAT_8043651c * 5;
    DAT_8043651c = DAT_8043651c + 1;
    gnt4_DVDLowSeek_bl((&DAT_803d797c)[iVar1],(&DAT_803d7980)[iVar2]);
  }
  return;
}



// ==== 8020c420  gnt4-AlarmHandlerForTimeout-bl ====

void gnt4_AlarmHandlerForTimeout_bl(undefined4 param_1,uint param_2)

{
  bool bVar1;
  code *pcVar2;
  undefined1 auStack_2d0 [716];
  
  gnt4___OSMaskInterrupts_bl(0x400);
  gnt4_OSClearContext_bl((int)auStack_2d0);
  gnt4_OSSetCurrentContext_bl((uint)auStack_2d0);
  pcVar2 = DAT_804364e0;
  bVar1 = DAT_804364e0 != (code *)0x0;
  DAT_804364e0 = (code *)0x0;
  if (bVar1) {
    (*pcVar2)(0x10);
  }
  gnt4_OSClearContext_bl((int)auStack_2d0);
  gnt4_OSSetCurrentContext_bl(param_2);
  return;
}



// ==== 8020c490  gnt4-Read-bl ====

void gnt4_Read_bl(undefined4 param_1,uint param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  longlong lVar2;
  
  DAT_804364d8 = 0;
  DAT_80436518 = 1;
  DAT_804364e0 = param_4;
  lVar2 = gnt4___OSGetSystemTime_bl();
  DAT_80436510 = (undefined4)((ulonglong)lVar2 >> 0x20);
  DAT_80436514 = (undefined4)lVar2;
  DAT_cc006008 = 0xa8000000;
  DAT_cc00600c = param_3 >> 2;
  DAT_cc006010 = param_2;
  DAT_cc006014 = param_1;
  DAT_cc006018 = param_2;
  DAT_cc00601c = 3;
  DAT_804364dc = param_2;
  if (param_2 < 0xa00001) {
    uVar1 = DAT_800000f8 >> 2;
    gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d79d8);
    gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d79d8,extraout_r4_00,0,uVar1 * 10,
                       gnt4_AlarmHandlerForTimeout_bl);
  }
  else {
    uVar1 = DAT_800000f8 >> 2;
    gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d79d8);
    gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d79d8,extraout_r4,0,uVar1 * 0x14,
                       gnt4_AlarmHandlerForTimeout_bl);
  }
  return;
}



// ==== 8020c5a0  gnt4-SeekTwiceBeforeRead-bl ====

void gnt4_SeekTwiceBeforeRead_bl
               (undefined4 param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  if ((param_3 & 0xffff8000) == 0) {
    DAT_803d797c = 0;
  }
  else {
    DAT_803d797c = (param_3 & 0xffff8000) + DAT_80436500;
  }
  DAT_803d7970 = 2;
  DAT_803d7984 = 1;
  DAT_803d7998 = 0xffffffff;
  DAT_8043651c = 0;
  DAT_803d7980 = param_4;
  DAT_803d7988 = param_1;
  DAT_803d798c = param_2;
  DAT_803d7990 = param_3;
  DAT_803d7994 = param_4;
  gnt4_DVDLowSeek_bl(DAT_803d797c,param_4);
  return;
}



// ==== 8020c620  gnt4-DVDLowRead-bl ====

undefined4 gnt4_DVDLowRead_bl(undefined4 param_1,uint param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  undefined4 extraout_r4;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  longlong lVar7;
  
  DAT_cc006018 = param_2;
  DAT_803d7a34 = param_1;
  DAT_803d7a38 = param_2;
  DAT_803d7a3c = param_3;
  if (DAT_804364fc == 0) {
    DAT_803d7970 = 0xffffffff;
    DAT_8043651c = 0;
    gnt4_Read_bl(param_1,param_2,param_3,param_4);
  }
  else if (DAT_804364fc == 1) {
    if (DAT_80435ca8 == 0) {
      uVar4 = (uint)(DAT_803d7a30 + DAT_803d7a2c + -1) >> 0xf;
      iVar3 = gnt4_DVDGetCurrentDiskID_bl();
      if (*(char *)(iVar3 + 8) == '\0') {
        iVar3 = 0xf;
      }
      else {
        iVar3 = 5;
      }
      if ((uVar4 - 2 < param_3 >> 0xf) || (param_3 >> 0xf < uVar4 + iVar3 + 3)) {
        bVar2 = true;
      }
      else {
        bVar2 = false;
      }
      if (bVar2) {
        uVar4 = (uint)(DAT_803d7a30 + DAT_803d7a2c + -1) >> 0xf;
        if ((uVar4 == DAT_803d7a3c >> 0xf) || (uVar4 + 1 == DAT_803d7a3c >> 0xf)) {
          lVar7 = gnt4___OSGetSystemTime_bl();
          uVar6 = (uint)lVar7 - DAT_8043650c;
          uVar5 = (int)((ulonglong)lVar7 >> 0x20) -
                  ((uint)((uint)lVar7 < DAT_8043650c) + DAT_80436508);
          uVar4 = ((DAT_800000f8 >> 2) / 1000) * 5;
          if ((uint)(uVar4 < uVar6) + (uVar5 ^ 0x80000000) < 0x80000001) {
            DAT_803d7970 = 1;
            DAT_803d7984 = 0xffffffff;
            uVar1 = ((DAT_800000f8 >> 2) / 0x1e848) * 500 >> 3;
            DAT_8043651c = 0;
            DAT_803d7974 = param_1;
            DAT_803d7978 = param_2;
            DAT_803d797c = param_3;
            DAT_803d7980 = param_4;
            gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d79b0);
            gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d79b0,extraout_r4,
                               (uint)CARRY4(uVar4 - uVar6,uVar1) - ((uVar4 < uVar6) + uVar5),
                               (uVar4 - uVar6) + uVar1,gnt4_AlarmHandler__bl);
          }
          else {
            DAT_803d7970 = 0xffffffff;
            DAT_8043651c = 0;
            gnt4_Read_bl(param_1,param_2,param_3,param_4);
          }
        }
        else {
          gnt4_SeekTwiceBeforeRead_bl(param_1,param_2,param_3,param_4);
        }
      }
      else {
        DAT_803d7970 = 0xffffffff;
        DAT_8043651c = 0;
        gnt4_Read_bl(param_1,param_2,param_3,param_4);
      }
    }
    else {
      gnt4_SeekTwiceBeforeRead_bl(param_1,param_2,param_3,param_4);
    }
  }
  return 1;
}



// ==== 8020c8b8  gnt4-DVDLowSeek-bl ====

undefined4 gnt4_DVDLowSeek_bl(uint param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 extraout_r4;
  
  DAT_804364d8 = 0;
  DAT_cc006008 = 0xab000000;
  DAT_cc00600c = param_1 >> 2;
  DAT_cc00601c = 1;
  uVar1 = DAT_800000f8 >> 2;
  DAT_804364e0 = param_2;
  gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d79d8);
  gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d79d8,extraout_r4,0,uVar1 * 10,
                     gnt4_AlarmHandlerForTimeout_bl);
  return 1;
}



// ==== 8020c94c  gnt4-DVDLowWaitCoverClose-bl ====

undefined4 gnt4_DVDLowWaitCoverClose_bl(undefined4 param_1)

{
  DAT_804364e0 = param_1;
  DAT_804364f4 = 1;
  DAT_804364d8 = 0;
  DAT_cc006004 = 2;
  return 1;
}



// ==== 8020c978  gnt4-DVDLowReadDiskID ====

undefined4 gnt4_DVDLowReadDiskID(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 extraout_r4;
  
  DAT_804364d8 = 0;
  DAT_cc006008 = 0xa8000040;
  DAT_cc00600c = 0;
  DAT_cc006010 = 0x20;
  DAT_cc006014 = param_1;
  DAT_cc006018 = 0x20;
  DAT_cc00601c = 3;
  uVar1 = DAT_800000f8 >> 2;
  DAT_804364e0 = param_2;
  gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d79d8);
  gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d79d8,extraout_r4,0,uVar1 * 10,
                     gnt4_AlarmHandlerForTimeout_bl);
  return 1;
}



// ==== 8020ca1c  gnt4-DVDLowStopMotor-bl ====

undefined4 gnt4_DVDLowStopMotor_bl(undefined4 param_1)

{
  uint uVar1;
  undefined4 extraout_r4;
  
  DAT_804364d8 = 0;
  DAT_cc006008 = 0xe3000000;
  DAT_cc00601c = 1;
  uVar1 = DAT_800000f8 >> 2;
  DAT_804364e0 = param_1;
  gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d79d8);
  gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d79d8,extraout_r4,0,uVar1 * 10,
                     gnt4_AlarmHandlerForTimeout_bl);
  return 1;
}



// ==== 8020caa8  gnt4-DVDLowRequestError-bl ====

undefined4 gnt4_DVDLowRequestError_bl(undefined4 param_1)

{
  uint uVar1;
  undefined4 extraout_r4;
  
  DAT_804364d8 = 0;
  DAT_cc006008 = 0xe0000000;
  DAT_cc00601c = 1;
  uVar1 = DAT_800000f8 >> 2;
  DAT_804364e0 = param_1;
  gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d79d8);
  gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d79d8,extraout_r4,0,uVar1 * 10,
                     gnt4_AlarmHandlerForTimeout_bl);
  return 1;
}



// ==== 8020cb34  gnt4-DVDLowInquiry-bl ====

undefined4 gnt4_DVDLowInquiry_bl(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 extraout_r4;
  
  DAT_804364d8 = 0;
  DAT_cc006008 = 0x12000000;
  DAT_cc006010 = 0x20;
  DAT_cc006014 = param_1;
  DAT_cc006018 = 0x20;
  DAT_cc00601c = 3;
  uVar1 = DAT_800000f8 >> 2;
  DAT_804364e0 = param_2;
  gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d79d8);
  gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d79d8,extraout_r4,0,uVar1 * 10,
                     gnt4_AlarmHandlerForTimeout_bl);
  return 1;
}



// ==== 8020cbd0  gnt4-DVDLowAudioStream-bl ====

undefined4
gnt4_DVDLowAudioStream_bl(uint param_1,undefined4 param_2,uint param_3,undefined4 param_4)

{
  uint uVar1;
  undefined4 extraout_r4;
  
  DAT_804364d8 = 0;
  DAT_cc006008 = param_1 | 0xe1000000;
  DAT_cc00600c = param_3 >> 2;
  DAT_cc006010 = param_2;
  DAT_cc00601c = 1;
  uVar1 = DAT_800000f8 >> 2;
  DAT_804364e0 = param_4;
  gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d79d8);
  gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d79d8,extraout_r4,0,uVar1 * 10,
                     gnt4_AlarmHandlerForTimeout_bl);
  return 1;
}



// ==== 8020cc68  gnt4-DVDLowRequestAudioStatus-bl ====

undefined4 gnt4_DVDLowRequestAudioStatus_bl(uint param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 extraout_r4;
  
  DAT_804364d8 = 0;
  DAT_cc006008 = param_1 | 0xe2000000;
  DAT_cc00601c = 1;
  uVar1 = DAT_800000f8 >> 2;
  DAT_804364e0 = param_2;
  gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d79d8);
  gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d79d8,extraout_r4,0,uVar1 * 10,
                     gnt4_AlarmHandlerForTimeout_bl);
  return 1;
}



// ==== 8020ccf4  gnt4-DVDLowAudioBufferConfig-bl ====

undefined4 gnt4_DVDLowAudioBufferConfig_bl(int param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 extraout_r4;
  
  uVar1 = 0;
  DAT_804364d8 = 0;
  if (param_1 != 0) {
    uVar1 = 0x10000;
  }
  DAT_cc006008 = param_2 | uVar1 | 0xe4000000;
  DAT_cc00601c = 1;
  uVar1 = DAT_800000f8 >> 2;
  DAT_804364e0 = param_3;
  gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d79d8);
  gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d79d8,extraout_r4,0,uVar1 * 10,
                     gnt4_AlarmHandlerForTimeout_bl);
  return 1;
}



// ==== 8020cd90  gnt4-DVDLowReset-bl ====

void gnt4_DVDLowReset_bl(void)

{
  uint uVar1;
  uint uVar2;
  longlong lVar3;
  longlong lVar4;
  
  DAT_cc006004 = 2;
  uVar2 = DAT_cc003024;
  DAT_cc003024 = uVar2 & 0xfffffffb | 1;
  lVar3 = gnt4___OSGetSystemTime_bl();
  uVar1 = DAT_800000f8 / 500000;
  do {
    lVar4 = gnt4___OSGetSystemTime_bl();
  } while (((int)((ulonglong)lVar4 >> 0x20) -
            ((uint)((uint)lVar4 < (uint)lVar3) + (int)((ulonglong)lVar3 >> 0x20)) ^ 0x80000000) <
           ((uint)lVar4 - (uint)lVar3 < uVar1 * 0xc >> 3) + 0x80000000);
  DAT_cc003024 = uVar2 | 5;
  DAT_804364f0 = 1;
  lVar3 = gnt4___OSGetSystemTime_bl();
  DAT_804364ec = (int)lVar3;
  DAT_804364e8 = (int)((ulonglong)lVar3 >> 0x20);
  return;
}



// ==== 8020ce4c  gnt4-DVDLowBreak-bl ====

undefined4 gnt4_DVDLowBreak_bl(void)

{
  DAT_804364d8 = 1;
  DAT_804364f8 = 1;
  return 1;
}



// ==== 8020ce60  gnt4-DVDLowClearCallback-bl ====

undefined4 gnt4_DVDLowClearCallback_bl(void)

{
  undefined4 uVar1;
  
  DAT_cc006004 = 0;
  uVar1 = DAT_804364e0;
  DAT_804364f4 = 0;
  DAT_804364e0 = 0;
  return uVar1;
}



// ==== 8020ce7c  gnt4-__DVDLowSetWAType-bl ====

void gnt4___DVDLowSetWAType_bl(undefined4 param_1,undefined4 param_2)

{
  gnt4_OSDisableInterrupts_bl();
  DAT_804364fc = param_1;
  DAT_80436500 = param_2;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 8020cec0  gnt4-__DVDFSInit-bl ====

void gnt4___DVDFSInit_bl(void)

{
  DAT_80436520 = 0x80000000;
  DAT_80436524 = DAT_80000038;
  if (DAT_80000038 == 0) {
    return;
  }
  DAT_8043652c = *(int *)(DAT_80000038 + 8);
  DAT_80436528 = DAT_80000038 + *(int *)(DAT_80000038 + 8) * 0xc;
  return;
}



// ==== 8020cef8  gnt4-DVDConvertPathToEntrynum-bl ====

uint gnt4_DVDConvertPathToEntrynum_bl
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               char *param_9)

{
  char cVar1;
  char cVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  int iVar6;
  uint *puVar7;
  uint uVar8;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  char *pcVar9;
  char *pcVar10;
  char *pcVar11;
  char *unaff_r24;
  uint uVar12;
  char *pcVar13;
  int iVar14;
  
  pcVar11 = param_9;
  uVar12 = DAT_80436530;
LAB_8020cf1c:
  while( true ) {
    while( true ) {
      cVar1 = *pcVar11;
      if (cVar1 == '\0') {
        return uVar12;
      }
      if (cVar1 != '/') break;
      uVar12 = 0;
      pcVar11 = pcVar11 + 1;
    }
    if (cVar1 != '.') break;
    cVar1 = pcVar11[1];
    if (cVar1 == '.') {
      if (pcVar11[2] != '/') {
        if (pcVar11[2] == '\0') {
          return *(uint *)(DAT_80436524 + uVar12 * 0xc + 4);
        }
        break;
      }
      uVar12 = *(uint *)(DAT_80436524 + uVar12 * 0xc + 4);
      pcVar11 = pcVar11 + 3;
    }
    else {
      if (cVar1 != '/') {
        if (cVar1 == '\0') {
          return uVar12;
        }
        break;
      }
      pcVar11 = pcVar11 + 2;
    }
  }
  pcVar13 = pcVar11;
  if (DAT_80436534 == 0) {
    bVar3 = false;
    bVar4 = false;
LAB_8020d020:
    cVar1 = *pcVar13;
    if ((cVar1 == '\0') || (cVar1 == '/')) goto LAB_8020d038;
    if (cVar1 == '.') {
      if ((8 < (int)pcVar13 - (int)pcVar11) || (bVar3)) {
        bVar4 = true;
LAB_8020d038:
        if ((bVar3) && (3 < (int)pcVar13 - (int)unaff_r24)) {
          bVar4 = true;
        }
        if (bVar4) {
          param_1 = gnt4_OSPanic(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 &DAT_80435cb0,0x17f,s_DVDConvertEntrynumToPath_possibl_803a4e80,
                                 param_9,in_r7,in_r8,in_r9,in_r10);
        }
        goto LAB_8020d098;
      }
      unaff_r24 = pcVar13 + 1;
      bVar3 = true;
    }
    else if (cVar1 == ' ') {
      bVar4 = true;
    }
    pcVar13 = pcVar13 + 1;
    goto LAB_8020d020;
  }
  for (; (*pcVar13 != '\0' && (*pcVar13 != '/')); pcVar13 = pcVar13 + 1) {
  }
LAB_8020d098:
  cVar1 = *pcVar13;
  iVar14 = uVar12 * 0xc;
  uVar12 = uVar12 + 1;
LAB_8020d1a0:
  if (*(uint *)(iVar14 + DAT_80436524 + 8) <= uVar12) {
    return 0xffffffff;
  }
  uVar8 = *(uint *)(DAT_80436524 + uVar12 * 0xc);
  if (((uVar8 & 0xff000000) != 0) || (cVar1 == '\0')) {
    pcVar9 = (char *)(DAT_80436528 + (uVar8 & 0xffffff));
    pcVar10 = pcVar11;
    do {
      if (*pcVar9 == '\0') {
        if ((*pcVar10 == '/') || (*pcVar10 == '\0')) {
          bVar3 = true;
        }
        else {
          bVar3 = false;
        }
        goto LAB_8020d160;
      }
      cVar2 = *pcVar9;
      pcVar9 = pcVar9 + 1;
      iVar5 = gnt4_tolower((int)cVar2);
      cVar2 = *pcVar10;
      pcVar10 = pcVar10 + 1;
      iVar6 = gnt4_tolower((int)cVar2);
    } while (iVar6 == iVar5);
    bVar3 = false;
LAB_8020d160:
    if (bVar3) goto LAB_8020d1bc;
  }
  puVar7 = (uint *)(DAT_80436524 + uVar12 * 0xc);
  if ((*puVar7 & 0xff000000) == 0) {
    uVar12 = uVar12 + 1;
  }
  else {
    uVar12 = puVar7[2];
  }
  goto LAB_8020d1a0;
LAB_8020d1bc:
  if (cVar1 == '\0') {
    return uVar12;
  }
  pcVar11 = pcVar13 + 1;
  goto LAB_8020cf1c;
}



// ==== 8020d1ec  gnt4-DVDOpen-bl ====

undefined4
gnt4_DVDOpen_bl(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               char *param_9,int param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 auStack_88 [128];
  
  uVar1 = gnt4_DVDConvertPathToEntrynum_bl
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  if ((int)uVar1 < 0) {
    gnt4_DVDGetCurrentDir_bl((int)auStack_88,0x80);
    gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                     s_Warning__DVDOpen____file___s__wa_803a4f48,param_9,auStack_88,param_12,
                     param_13,param_14,param_15,param_16);
    uVar2 = 0;
  }
  else {
    iVar3 = uVar1 * 0xc;
    if ((*(uint *)(DAT_80436524 + iVar3) & 0xff000000) == 0) {
      uVar2 = 1;
      *(undefined4 *)(param_10 + 0x30) = *(undefined4 *)(DAT_80436524 + iVar3 + 4);
      *(undefined4 *)(param_10 + 0x34) = *(undefined4 *)(DAT_80436524 + iVar3 + 8);
      *(undefined4 *)(param_10 + 0x38) = 0;
      *(undefined4 *)(param_10 + 0xc) = 0;
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}



// ==== 8020d2b4  gnt4-DVDClose-bl ====

undefined4 gnt4_DVDClose_bl(int *param_1)

{
  gnt4_DVDCancel_bl(param_1);
  return 1;
}



// ==== 8020d2d8  gnt4-entryToPath-bl ====

int gnt4_entryToPath_bl(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  char *pcVar4;
  char *pcVar5;
  
  if (param_1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(DAT_80436524 + 4 + param_1 * 0xc);
    pcVar5 = (char *)(DAT_80436528 + (*(uint *)(DAT_80436524 + param_1 * 0xc) & 0xffffff));
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = iVar1 * 0xc;
      pcVar4 = (char *)(DAT_80436528 + (*(uint *)(DAT_80436524 + iVar1) & 0xffffff));
      iVar1 = gnt4_entryToPath_bl(*(int *)(DAT_80436524 + 4 + iVar1),param_2,param_3);
      if (iVar1 != param_3) {
        iVar2 = iVar1 + 1;
        *(undefined1 *)(param_2 + iVar1) = 0x2f;
        pcVar3 = (char *)(param_2 + iVar2);
        iVar1 = param_3 - iVar2;
        for (; (iVar1 != 0 && (*pcVar4 != '\0')); pcVar4 = pcVar4 + 1) {
          iVar1 = iVar1 + -1;
          *pcVar3 = *pcVar4;
          pcVar3 = pcVar3 + 1;
        }
        iVar1 = iVar2 + ((param_3 - iVar2) - iVar1);
      }
    }
    if (iVar1 != param_3) {
      iVar2 = iVar1 + 1;
      *(undefined1 *)(param_2 + iVar1) = 0x2f;
      pcVar4 = (char *)(param_2 + iVar2);
      iVar1 = param_3 - iVar2;
      for (; (iVar1 != 0 && (*pcVar5 != '\0')); pcVar5 = pcVar5 + 1) {
        iVar1 = iVar1 + -1;
        *pcVar4 = *pcVar5;
        pcVar4 = pcVar4 + 1;
      }
      iVar1 = iVar2 + ((param_3 - iVar2) - iVar1);
    }
  }
  return iVar1;
}



// ==== 8020d438  gnt4-DVDGetCurrentDir-bl ====

undefined4 gnt4_DVDGetCurrentDir_bl(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = DAT_80436530;
  iVar3 = gnt4_entryToPath_bl(DAT_80436530,param_1,param_2);
  if (iVar3 == param_2) {
    uVar2 = 0;
    *(undefined1 *)(param_1 + param_2 + -1) = 0;
  }
  else {
    if ((*(uint *)(DAT_80436524 + iVar1 * 0xc) & 0xff000000) != 0) {
      if (iVar3 == param_2 + -1) {
        *(undefined1 *)(param_1 + iVar3) = 0;
        return 0;
      }
      *(undefined1 *)(param_1 + iVar3) = 0x2f;
      iVar3 = iVar3 + 1;
    }
    *(undefined1 *)(param_1 + iVar3) = 0;
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 8020d4fc  gnt4-DVDReadAsyncPrio-bl ====

undefined4
gnt4_DVDReadAsyncPrio_bl
          (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
          undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
          undefined4 *param_9,undefined4 param_10,int param_11,uint param_12,undefined4 param_13,
          int param_14,undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  
  uVar1 = param_12;
  uVar2 = param_13;
  iVar3 = param_14;
  if (-1 < (int)param_12) {
    if (param_12 < (uint)param_9[0xd]) goto LAB_8020d54c;
  }
  param_1 = gnt4_OSPanic(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80435cb0,0x2ea,s_DVDReadAsync____specified_area_i_803a4f80,param_12,
                         param_13,param_14,param_15,param_16);
LAB_8020d54c:
  if (((int)(param_12 + param_11) < 0) || (param_9[0xd] + 0x20 <= param_12 + param_11)) {
    gnt4_OSPanic(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435cb0,0x2f0
                 ,s_DVDReadAsync____specified_area_i_803a4f80,uVar1,uVar2,iVar3,param_15,param_16);
  }
  param_9[0xe] = param_13;
  gnt4_DVDReadAbsAsyncPrio_bl
            (param_9,param_10,param_11,param_9[0xc] + param_12,gnt4_cbForReadAsync_bl,param_14);
  return 1;
}



// ==== 8020d5bc  gnt4-cbForReadAsync-bl ====

void gnt4_cbForReadAsync_bl(undefined4 param_1,int param_2)

{
  if (*(code **)(param_2 + 0x38) != (code *)0x0) {
    (**(code **)(param_2 + 0x38))();
  }
  return;
}



// ==== 8020d5ec  gnt4-DVDReadPrio-bl ====

undefined4
gnt4_DVDReadPrio_bl(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                   undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                   undefined4 *param_9,undefined4 param_10,int param_11,uint param_12,int param_13,
                   undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar3 = param_12;
  iVar1 = param_13;
  if (-1 < (int)param_12) {
    if (param_12 < (uint)param_9[0xd]) goto LAB_8020d638;
  }
  param_1 = gnt4_OSPanic(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80435cb0,0x330,s_DVDRead____specified_area_is_out_803a4fb4,param_12,
                         param_13,param_14,param_15,param_16);
LAB_8020d638:
  if (((int)(param_12 + param_11) < 0) || (param_9[0xd] + 0x20 <= param_12 + param_11)) {
    gnt4_OSPanic(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435cb0,0x336
                 ,s_DVDRead____specified_area_is_out_803a4fb4,uVar3,iVar1,param_14,param_15,param_16
                );
  }
  iVar1 = gnt4_DVDReadAbsAsyncPrio_bl
                    (param_9,param_10,param_11,param_9[0xc] + param_12,gnt4_cbForReadSync_bl,
                     param_13);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    gnt4_OSDisableInterrupts_bl();
    while (iVar1 = param_9[3], iVar1 != 0) {
      if (iVar1 == -1) {
        uVar2 = 0xffffffff;
        goto LAB_8020d6e4;
      }
      if (iVar1 == 10) {
        uVar2 = 0xfffffffd;
        goto LAB_8020d6e4;
      }
      gnt4_OSSleepThread_bl((int *)&DAT_80436538);
    }
    uVar2 = param_9[8];
LAB_8020d6e4:
    gnt4_OSRestoreInterrupts_bl();
  }
  return uVar2;
}



// ==== 8020d704  gnt4-cbForReadSync-bl ====

void gnt4_cbForReadSync_bl(void)

{
  gnt4_OSWakeupThread_bl((int *)&DAT_80436538);
  return;
}



// ==== 8020d728  zz_020d728_ ====

int zz_020d728_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0xc);
  if (iVar1 == 2) {
    return 0;
  }
  if (iVar1 < 2) {
    if (0 < iVar1) {
      iVar1 = DAT_cc006018;
      return *(int *)(param_1 + 0x20) + (*(int *)(param_1 + 0x1c) - iVar1);
    }
    if (iVar1 < -1) {
      return param_1;
    }
  }
  else if (iVar1 < 10) {
    if (7 < iVar1) {
      return param_1;
    }
  }
  else if (0xb < iVar1) {
    return param_1;
  }
  return *(int *)(param_1 + 0x20);
}



// ==== 8020d794  gnt4-defaultOptionalCommandChecker-bl ====

void gnt4_defaultOptionalCommandChecker_bl(void)

{
  return;
}



// ==== 8020d798  gnt4-DVDInit-bl ====

void gnt4_DVDInit_bl(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                    undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                    undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                    undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  if (DAT_80436580 == 0) {
    gnt4_OSRegisterVersion_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435cb8,param_10
               ,param_11,param_12,param_13,param_14,param_15,param_16);
    DAT_80436580 = 1;
    gnt4___DVDFSInit_bl();
    gnt4___DVDClearWaitingQueue_bl();
    gnt4___DVDInitWA_bl();
    DAT_80436548 = -0x80000000;
    DAT_80436544 = 0x80000000;
    gnt4___OSSetInterruptHandler_bl(0x15,gnt4___DVDInterruptHandler_bl);
    gnt4___OSUnmaskInterrupts_bl(0x400);
    uVar1 = gnt4_OSInitThreadQueue_bl((undefined4 *)&DAT_80436538);
    DAT_cc006000 = 0x2a;
    DAT_cc006004 = 0;
    if (*(int *)(DAT_80436548 + 0x20) == -0x1adf83de) {
      uVar1 = gnt4_OSReport_bl(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s_load_fst_803a5030,extraout_r4,param_11,param_12,param_13,param_14,
                               param_15,param_16);
      gnt4___fstLoad_bl(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    else if (*(int *)(DAT_80436548 + 0x20) != 0xd15ea5e) {
      DAT_8043657c = 1;
    }
  }
  return;
}



// ==== 8020d864  gnt4-stateReadingFST-bl ====

void gnt4_stateReadingFST_bl
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  DAT_80436584 = gnt4_stateReadingFST_bl;
  if (*(uint *)(DAT_80436548 + 0x3c) < DAT_803d7a48) {
    gnt4_OSPanic(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435cc4,0x284
                 ,s_DVDChangeDisk____FST_in_the_new_d_803a503c,in_r6,in_r7,in_r8,in_r9,in_r10);
  }
  gnt4_DVDLowRead_bl(*(undefined4 *)(DAT_80436548 + 0x38),DAT_803d7a48 + 0x1f & 0xffffffe0,
                     DAT_803d7a44,gnt4_cbForStateReadingFST_bl);
  return;
}



// ==== 8020d8f8  gnt4-cbForStateReadingFST-bl ====

void gnt4_cbForStateReadingFST_bl(uint param_1)

{
  undefined *puVar1;
  code *pcVar2;
  
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4_stateTimeout_bl();
  }
  else if ((param_1 & 1) == 0) {
    gnt4_stateGettingError_bl();
  }
  else {
    DAT_80436574 = 0;
    gnt4___DVDFSInit_bl();
    puVar1 = DAT_80436540;
    DAT_80436540 = &DAT_803d7a80;
    *(undefined4 *)(puVar1 + 0xc) = 0;
    pcVar2 = *(code **)(puVar1 + 0x28);
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)(0);
    }
    gnt4_stateReady_bl();
  }
  return;
}



// ==== 8020d984  gnt4-cbForStateError-bl ====

void gnt4_cbForStateError_bl(int param_1)

{
  undefined *puVar1;
  
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4_stateTimeout_bl();
  }
  else {
    gnt4___DVDPrintFatalMessage_bl();
    puVar1 = DAT_80436540;
    DAT_80436540 = &DAT_803d7a80;
    DAT_80436558 = 1;
    if (*(code **)(puVar1 + 0x28) != (code *)0x0) {
      (**(code **)(puVar1 + 0x28))(0xffffffff,puVar1);
    }
    if (DAT_80436560 != 0) {
      DAT_80436560 = 0;
      if (DAT_80436564 != (code *)0x0) {
        (*DAT_80436564)(0,puVar1);
      }
    }
    gnt4_stateReady_bl();
  }
  return;
}



// ==== 8020da30  gnt4-stateTimeout-bl ====

void gnt4_stateTimeout_bl(void)

{
  gnt4___DVDStoreErrorCode_bl(0x1234568);
  gnt4_DVDReset_bl();
  gnt4_cbForStateError_bl(0);
  return;
}



// ==== 8020da64  gnt4-stateGettingError-bl ====

void gnt4_stateGettingError_bl(void)

{
  gnt4_DVDLowRequestError_bl(gnt4_cbForStateGettingError_bl);
  return;
}



// ==== 8020da8c  gnt4-CategorizeError-bl ====

undefined4 gnt4_CategorizeError_bl(uint param_1)

{
  uint uVar1;
  
  if (param_1 == 0x20400) {
    DAT_80436570 = param_1;
    return 1;
  }
  uVar1 = param_1 & 0xffffff;
  if (((uVar1 == 0x62800) || (uVar1 == 0x23a00)) || (uVar1 == 0xb5a01)) {
    return 0;
  }
  DAT_80436574 = DAT_80436574 + 1;
  if (DAT_80436574 == 2) {
    if (uVar1 == DAT_80436570) {
      DAT_80436570 = uVar1;
      return 1;
    }
    DAT_80436570 = uVar1;
    return 2;
  }
  DAT_80436570 = uVar1;
  if ((uVar1 != 0x31100) && (*(int *)(DAT_80436540 + 8) != 5)) {
    return 3;
  }
  return 2;
}



// ==== 8020db40  gnt4-cbForStateGettingError-bl ====

void gnt4_cbForStateGettingError_bl(uint param_1)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  undefined *puVar4;
  int iVar5;
  undefined4 uVar6;
  
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4___DVDStoreErrorCode_bl(0x1234568);
    gnt4_DVDReset_bl();
    gnt4_cbForStateError_bl(0);
  }
  else if ((param_1 & 2) == 0) {
    uVar3 = DAT_cc006020;
    uVar2 = uVar3 & 0xff000000;
    iVar5 = gnt4_CategorizeError_bl(uVar3);
    puVar4 = DAT_80436540;
    if (iVar5 == 1) {
      *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
      gnt4___DVDStoreErrorCode_bl(uVar3);
      gnt4_DVDLowStopMotor_bl(gnt4_cbForStateError_bl);
    }
    else {
      if (iVar5 - 2U < 2) {
        uVar6 = 0;
      }
      else if (uVar2 == 0x1000000) {
        uVar6 = 4;
      }
      else if (uVar2 == 0x2000000) {
        uVar6 = 6;
      }
      else if (uVar2 == 0x3000000) {
        uVar6 = 3;
      }
      else {
        uVar6 = 5;
      }
      if (DAT_80436560 == 0) {
        bVar1 = false;
      }
      else {
        DAT_80436560 = 0;
        DAT_80436540 = &DAT_803d7a80;
        DAT_80436568 = uVar6;
        *(undefined4 *)(puVar4 + 0xc) = 10;
        if (*(code **)(puVar4 + 0x28) != (code *)0x0) {
          (**(code **)(puVar4 + 0x28))(0xfffffffd,puVar4);
        }
        if (DAT_80436564 != (code *)0x0) {
          (*DAT_80436564)(0,puVar4);
        }
        gnt4_stateReady_bl();
        bVar1 = true;
      }
      if (!bVar1) {
        if (iVar5 == 2) {
          gnt4___DVDStoreErrorCode_bl(uVar3);
          gnt4_stateGoToRetry_bl();
        }
        else if (iVar5 == 3) {
          if ((uVar3 & 0xffffff) == 0x31100) {
            gnt4_DVDLowSeek_bl(*(uint *)(DAT_80436540 + 0x10),gnt4_cbForUnrecoveredError_bl);
          }
          else {
            (*DAT_80436584)(DAT_80436540);
          }
        }
        else if (uVar2 == 0x1000000) {
          *(undefined4 *)(DAT_80436540 + 0xc) = 5;
          gnt4_stateMotorStopped_bl();
        }
        else if (uVar2 == 0x2000000) {
          *(undefined4 *)(DAT_80436540 + 0xc) = 3;
          gnt4_stateCoverClosed_bl();
        }
        else if (uVar2 == 0x3000000) {
          *(undefined4 *)(DAT_80436540 + 0xc) = 4;
          gnt4_stateMotorStopped_bl();
        }
        else {
          *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
          gnt4___DVDStoreErrorCode_bl(0x1234567);
          gnt4_DVDLowStopMotor_bl(gnt4_cbForStateError_bl);
        }
      }
    }
  }
  else {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4___DVDStoreErrorCode_bl(0x1234567);
    gnt4_DVDLowStopMotor_bl(gnt4_cbForStateError_bl);
  }
  return;
}



// ==== 8020ddd4  gnt4-cbForUnrecoveredError-bl ====

void gnt4_cbForUnrecoveredError_bl(uint param_1)

{
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4___DVDStoreErrorCode_bl(0x1234568);
    gnt4_DVDReset_bl();
    gnt4_cbForStateError_bl(0);
  }
  else if ((param_1 & 1) == 0) {
    gnt4_DVDLowRequestError_bl(gnt4_cbForUnrecoveredErrorRetry_bl);
  }
  else {
    gnt4_stateGoToRetry_bl();
  }
  return;
}



// ==== 8020de3c  gnt4-cbForUnrecoveredErrorRetry-bl ====

void gnt4_cbForUnrecoveredErrorRetry_bl(uint param_1)

{
  uint uVar1;
  
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4___DVDStoreErrorCode_bl(0x1234568);
    gnt4_DVDReset_bl();
    gnt4_cbForStateError_bl(0);
  }
  else {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    if ((param_1 & 2) == 0) {
      uVar1 = DAT_cc006020;
      gnt4___DVDStoreErrorCode_bl(uVar1);
      gnt4_DVDLowStopMotor_bl(gnt4_cbForStateError_bl);
    }
    else {
      gnt4___DVDStoreErrorCode_bl(0x1234567);
      gnt4_DVDLowStopMotor_bl(gnt4_cbForStateError_bl);
    }
  }
  return;
}



// ==== 8020ded4  gnt4-stateGoToRetry-bl ====

void gnt4_stateGoToRetry_bl(void)

{
  gnt4_DVDLowStopMotor_bl(gnt4_cbForStateGoToRetry_bl);
  return;
}



// ==== 8020defc  gnt4-cbForStateGoToRetry-bl ====

void gnt4_cbForStateGoToRetry_bl(uint param_1)

{
  bool bVar1;
  undefined *puVar2;
  
  puVar2 = DAT_80436540;
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4___DVDStoreErrorCode_bl(0x1234568);
    gnt4_DVDReset_bl();
    gnt4_cbForStateError_bl(0);
  }
  else if ((param_1 & 2) == 0) {
    DAT_80436574 = 0;
    if ((((DAT_8043655c == 4) || (DAT_8043655c == 5)) || (DAT_8043655c == 0xd)) ||
       (DAT_8043655c == 0xf)) {
      DAT_80436578 = 1;
    }
    if (DAT_80436560 == 0) {
      bVar1 = false;
    }
    else {
      DAT_80436568 = 2;
      DAT_80436540 = &DAT_803d7a80;
      DAT_80436560 = 0;
      *(undefined4 *)(puVar2 + 0xc) = 10;
      if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
        (**(code **)(puVar2 + 0x28))(0xfffffffd,puVar2);
      }
      if (DAT_80436564 != (code *)0x0) {
        (*DAT_80436564)(0,puVar2);
      }
      gnt4_stateReady_bl();
      bVar1 = true;
    }
    if (!bVar1) {
      *(undefined4 *)(DAT_80436540 + 0xc) = 0xb;
      gnt4_stateMotorStopped_bl();
    }
  }
  else {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4___DVDStoreErrorCode_bl(0x1234567);
    gnt4_DVDLowStopMotor_bl(gnt4_cbForStateError_bl);
  }
  return;
}



// ==== 8020e054  gnt4-stateCheckID-bl ====

void gnt4_stateCheckID_bl(void)

{
  int iVar1;
  
  if (DAT_8043655c == 3) {
    iVar1 = gnt4_DVDCompareDiskID_bl(&DAT_803d7a60,*(char **)(DAT_80436540 + 0x24));
    if (iVar1 == 0) {
      gnt4_DVDLowStopMotor_bl(gnt4_cbForStateCheckID1_bl);
    }
    else {
      gnt4_memcpy(DAT_80436544,&DAT_803d7a60,0x20);
      *(undefined4 *)(DAT_80436540 + 0xc) = 1;
      gnt4_DCInvalidateRange_bl(0x803d7a40,0x20);
      DAT_80436584 = gnt4_stateCheckID2a_bl;
      gnt4_stateCheckID2a_bl();
    }
  }
  else {
    iVar1 = gnt4_memcmp(&DAT_803d7a60,DAT_80436544,0x20);
    if (iVar1 == 0) {
      DAT_80436584 = gnt4_stateCheckID3_bl;
      gnt4_stateCheckID3_bl();
    }
    else {
      gnt4_DVDLowStopMotor_bl(gnt4_cbForStateCheckID1_bl);
    }
  }
  return;
}



// ==== 8020e134  gnt4-stateCheckID3-bl ====

void gnt4_stateCheckID3_bl(void)

{
  gnt4_DVDLowAudioBufferConfig_bl((uint)*(byte *)(DAT_80436544 + 8),10,gnt4_cbForStateCheckID3_bl);
  return;
}



// ==== 8020e168  gnt4-stateCheckID2a-bl ====

void gnt4_stateCheckID2a_bl(void)

{
  gnt4_DVDLowAudioBufferConfig_bl((uint)*(byte *)(DAT_80436544 + 8),10,gnt4_cbForStateCheckID2a_bl);
  return;
}



// ==== 8020e19c  gnt4-cbForStateCheckID2a-bl ====

void gnt4_cbForStateCheckID2a_bl(uint param_1)

{
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4___DVDStoreErrorCode_bl(0x1234568);
    gnt4_DVDReset_bl();
    gnt4_cbForStateError_bl(0);
  }
  else if ((param_1 & 1) == 0) {
    gnt4_DVDLowRequestError_bl(gnt4_cbForStateGettingError_bl);
  }
  else {
    DAT_80436574 = 0;
    gnt4_stateCheckID2_bl();
  }
  return;
}



// ==== 8020e210  gnt4-stateCheckID2-bl ====

void gnt4_stateCheckID2_bl(void)

{
  gnt4_DVDLowRead_bl(&DAT_803d7a40,0x20,0x420,gnt4_cbForStateCheckID2_bl);
  return;
}



// ==== 8020e248  gnt4-cbForStateCheckID1-bl ====

void gnt4_cbForStateCheckID1_bl(uint param_1)

{
  bool bVar1;
  undefined *puVar2;
  
  puVar2 = DAT_80436540;
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4___DVDStoreErrorCode_bl(0x1234568);
    gnt4_DVDReset_bl();
    gnt4_cbForStateError_bl(0);
  }
  else if ((param_1 & 2) == 0) {
    bVar1 = false;
    DAT_80436574 = 0;
    if (DAT_80436560 != 0) {
      DAT_80436568 = 1;
      DAT_80436560 = 0;
      DAT_80436540 = &DAT_803d7a80;
      *(undefined4 *)(puVar2 + 0xc) = 10;
      if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
        (**(code **)(puVar2 + 0x28))(0xfffffffd,puVar2);
      }
      if (DAT_80436564 != (code *)0x0) {
        (*DAT_80436564)(0,puVar2);
      }
      gnt4_stateReady_bl();
      bVar1 = true;
    }
    if (!bVar1) {
      *(undefined4 *)(DAT_80436540 + 0xc) = 6;
      gnt4_stateMotorStopped_bl();
    }
  }
  else {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4___DVDStoreErrorCode_bl(0x1234567);
    gnt4_DVDLowStopMotor_bl(gnt4_cbForStateError_bl);
  }
  return;
}



// ==== 8020e35c  gnt4-cbForStateCheckID2-bl ====

void gnt4_cbForStateCheckID2_bl
               (undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
               uint param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
               undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  if (param_9 == 0x10) {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4___DVDStoreErrorCode_bl(0x1234568);
    gnt4_DVDReset_bl();
    gnt4_cbForStateError_bl(0);
  }
  else if ((param_9 & 1) == 0) {
    gnt4_DVDLowRequestError_bl(gnt4_cbForStateGettingError_bl);
  }
  else {
    DAT_80436584 = gnt4_stateReadingFST_bl;
    DAT_80436574 = 0;
    if (*(uint *)(DAT_80436548 + 0x3c) < DAT_803d7a48) {
      gnt4_OSPanic(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435cc4,
                   0x284,s_DVDChangeDisk____FST_in_the_new_d_803a503c,param_12,param_13,param_14,
                   param_15,param_16);
    }
    gnt4_DVDLowRead_bl(*(undefined4 *)(DAT_80436548 + 0x38),DAT_803d7a48 + 0x1f & 0xffffffe0,
                       DAT_803d7a44,gnt4_cbForStateReadingFST_bl);
  }
  return;
}



// ==== 8020e440  gnt4-cbForStateCheckID3-bl ====

void gnt4_cbForStateCheckID3_bl(uint param_1)

{
  bool bVar1;
  undefined *puVar2;
  
  puVar2 = DAT_80436540;
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4___DVDStoreErrorCode_bl(0x1234568);
    gnt4_DVDReset_bl();
    gnt4_cbForStateError_bl(0);
  }
  else if ((param_1 & 1) == 0) {
    gnt4_DVDLowRequestError_bl(gnt4_cbForStateGettingError_bl);
  }
  else {
    bVar1 = false;
    DAT_80436574 = 0;
    if (DAT_80436560 != 0) {
      DAT_80436568 = 0;
      DAT_80436560 = 0;
      DAT_80436540 = &DAT_803d7a80;
      *(undefined4 *)(puVar2 + 0xc) = 10;
      if (*(code **)(puVar2 + 0x28) != (code *)0x0) {
        (**(code **)(puVar2 + 0x28))(0xfffffffd,puVar2);
      }
      if (DAT_80436564 != (code *)0x0) {
        (*DAT_80436564)(0,puVar2);
      }
      gnt4_stateReady_bl();
      bVar1 = true;
    }
    if (!bVar1) {
      *(undefined4 *)(DAT_80436540 + 0xc) = 1;
      gnt4_stateBusy_bl((int)DAT_80436540);
    }
  }
  return;
}



// ==== 8020e53c  gnt4-AlarmHandler__-bl ====

void gnt4_AlarmHandler___bl(void)

{
  gnt4_DVDReset_bl();
  gnt4_DCInvalidateRange_bl(0x803d7a60,0x20);
  DAT_80436584 = gnt4_stateCoverClosed_CMD_bl;
  gnt4_stateCoverClosed_CMD_bl();
  return;
}



// ==== 8020e580  gnt4-stateCoverClosed-bl ====

void gnt4_stateCoverClosed_bl(void)

{
  undefined *puVar1;
  
  if (DAT_8043655c == 0xd) {
LAB_8020e5c8:
    gnt4___DVDClearWaitingQueue_bl();
    puVar1 = DAT_80436540;
    DAT_80436540 = &DAT_803d7a80;
    if (*(code **)(puVar1 + 0x28) != (code *)0x0) {
      (**(code **)(puVar1 + 0x28))(0xfffffffc);
    }
    gnt4_stateReady_bl();
  }
  else {
    if (DAT_8043655c < 0xd) {
      if ((DAT_8043655c < 6) && (3 < DAT_8043655c)) goto LAB_8020e5c8;
    }
    else if (DAT_8043655c == 0xf) goto LAB_8020e5c8;
    gnt4_DVDReset_bl();
    gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d7ab0);
    gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d7ab0,0x10624dd3,0,(DAT_800000f8 / 4000) * 0x47e,
                       gnt4_AlarmHandler___bl);
  }
  return;
}



// ==== 8020e64c  gnt4-stateCoverClosed_CMD-bl ====

void gnt4_stateCoverClosed_CMD_bl(void)

{
  gnt4_DVDLowReadDiskID(&DAT_803d7a60,gnt4_cbForStateCoverClosed_bl);
  return;
}



// ==== 8020e67c  gnt4-cbForStateCoverClosed-bl ====

void gnt4_cbForStateCoverClosed_bl(uint param_1)

{
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4___DVDStoreErrorCode_bl(0x1234568);
    gnt4_DVDReset_bl();
    gnt4_cbForStateError_bl(0);
  }
  else if ((param_1 & 1) == 0) {
    gnt4_DVDLowRequestError_bl(gnt4_cbForStateGettingError_bl);
  }
  else {
    DAT_80436574 = 0;
    gnt4_stateCheckID_bl();
  }
  return;
}



// ==== 8020e6ec  gnt4-stateMotorStopped-bl ====

void gnt4_stateMotorStopped_bl(void)

{
  gnt4_DVDLowWaitCoverClose_bl(gnt4_cbForStateMotorStopped_bl);
  return;
}



// ==== 8020e714  gnt4-cbForStateMotorStopped-bl ====

void gnt4_cbForStateMotorStopped_bl(void)

{
  undefined *puVar1;
  
  DAT_cc006004 = 0;
  *(undefined4 *)(DAT_80436540 + 0xc) = 3;
  if (DAT_8043655c == 0xd) {
LAB_8020e774:
    gnt4___DVDClearWaitingQueue_bl();
    puVar1 = DAT_80436540;
    DAT_80436540 = &DAT_803d7a80;
    if (*(code **)(puVar1 + 0x28) != (code *)0x0) {
      (**(code **)(puVar1 + 0x28))(0xfffffffc);
    }
    gnt4_stateReady_bl();
  }
  else {
    if (DAT_8043655c < 0xd) {
      if ((DAT_8043655c < 6) && (3 < DAT_8043655c)) goto LAB_8020e774;
    }
    else if (DAT_8043655c == 0xf) goto LAB_8020e774;
    gnt4_DVDReset_bl();
    gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d7ab0);
    gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d7ab0,0x10624dd3,0,(DAT_800000f8 / 4000) * 0x47e,
                       gnt4_AlarmHandler___bl);
  }
  return;
}



// ==== 8020e7f8  gnt4-stateReady-bl ====

void gnt4_stateReady_bl(void)

{
  int *piVar1;
  int iVar2;
  
  iVar2 = gnt4___DVDCheckWaitingQueue_bl();
  if (iVar2 == 0) {
    DAT_80436540 = (int *)0x0;
    return;
  }
  if (DAT_8043654c != 0) {
    DAT_80436540 = (int *)0x0;
    DAT_80436550 = 1;
    return;
  }
  DAT_80436540 = gnt4___DVDPopWaitingQueue_bl();
  if (DAT_80436558 != 0) {
    DAT_80436540[3] = -1;
    piVar1 = DAT_80436540;
    DAT_80436540 = (int *)&DAT_803d7a80;
    if ((code *)piVar1[10] != (code *)0x0) {
      (*(code *)piVar1[10])(0xffffffff);
    }
    gnt4_stateReady_bl();
    return;
  }
  DAT_8043655c = DAT_80436540[2];
  if (DAT_80436568 == 0) {
    DAT_80436540[3] = 1;
    gnt4_stateBusy_bl((int)DAT_80436540);
    return;
  }
  if (DAT_80436568 == 4) {
    DAT_80436540[3] = 5;
    gnt4_DVDLowWaitCoverClose_bl(gnt4_cbForStateMotorStopped_bl);
    DAT_80436568 = 0;
    return;
  }
  if (DAT_80436568 < 4) {
    if (DAT_80436568 == 2) {
      DAT_80436540[3] = 0xb;
      gnt4_DVDLowWaitCoverClose_bl(gnt4_cbForStateMotorStopped_bl);
      DAT_80436568 = 0;
      return;
    }
    if (1 < DAT_80436568) {
      DAT_80436540[3] = 4;
      gnt4_DVDLowWaitCoverClose_bl(gnt4_cbForStateMotorStopped_bl);
      DAT_80436568 = 0;
      return;
    }
    if (DAT_80436568 < 1) {
      DAT_80436568 = 0;
      return;
    }
  }
  else {
    if (7 < DAT_80436568) {
      DAT_80436568 = 0;
      return;
    }
    if (DAT_80436568 < 6) {
      DAT_80436540[3] = -1;
      gnt4___DVDStoreErrorCode_bl(DAT_8043656c);
      gnt4_DVDLowStopMotor_bl(gnt4_cbForStateError_bl);
      DAT_80436568 = 0;
      return;
    }
  }
  DAT_80436540[3] = 3;
  if (DAT_8043655c == 0xd) {
LAB_8020e968:
    gnt4___DVDClearWaitingQueue_bl();
    piVar1 = DAT_80436540;
    DAT_80436540 = (int *)&DAT_803d7a80;
    if ((code *)piVar1[10] != (code *)0x0) {
      (*(code *)piVar1[10])(0xfffffffc);
    }
    gnt4_stateReady_bl();
  }
  else {
    if (DAT_8043655c < 0xd) {
      if ((DAT_8043655c < 6) && (3 < DAT_8043655c)) goto LAB_8020e968;
    }
    else if (DAT_8043655c == 0xf) goto LAB_8020e968;
    gnt4_DVDReset_bl();
    gnt4_OSCreateAlarm_bl((undefined4 *)&DAT_803d7ab0);
    gnt4_OSSetAlarm_bl((undefined4 *)&DAT_803d7ab0,0x10624dd3,0,(DAT_800000f8 / 4000) * 0x47e,
                       gnt4_AlarmHandler___bl);
  }
  DAT_80436568 = 0;
  return;
}



// ==== 8020ea28  gnt4-stateBusy-bl ====

void gnt4_stateBusy_bl(int param_1)

{
  undefined4 uVar1;
  undefined *puVar2;
  uint uVar3;
  code *pcVar4;
  
  puVar2 = DAT_80436540;
  DAT_80436584 = gnt4_stateBusy_bl;
  switch(*(undefined4 *)(param_1 + 8)) {
  default:
    (*DAT_80435cc0)(param_1,gnt4_cbForStateBusy_bl);
    break;
  case 1:
  case 4:
    if (*(int *)(param_1 + 0x14) == 0) {
      DAT_80436540 = &DAT_803d7a80;
      *(undefined4 *)(puVar2 + 0xc) = 0;
      pcVar4 = *(code **)(puVar2 + 0x28);
      if (pcVar4 != (code *)0x0) {
        (*pcVar4)(0);
      }
      gnt4_stateReady_bl();
    }
    else {
      uVar1 = DAT_cc006004;
      DAT_cc006004 = uVar1;
      uVar3 = *(int *)(param_1 + 0x14) - *(int *)(param_1 + 0x20);
      if (0x80000 < uVar3) {
        uVar3 = 0x80000;
      }
      *(uint *)(param_1 + 0x1c) = uVar3;
      gnt4_DVDLowRead_bl(*(int *)(param_1 + 0x18) + *(int *)(param_1 + 0x20),
                         *(uint *)(param_1 + 0x1c),
                         *(int *)(param_1 + 0x10) + *(int *)(param_1 + 0x20),gnt4_cbForStateBusy_bl)
      ;
    }
    break;
  case 2:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    gnt4_DVDLowSeek_bl(*(uint *)(param_1 + 0x10),gnt4_cbForStateBusy_bl);
    break;
  case 3:
    gnt4_DVDLowStopMotor_bl(gnt4_cbForStateBusy_bl);
    break;
  case 5:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    *(undefined4 *)(param_1 + 0x1c) = 0x20;
    gnt4_DVDLowReadDiskID(*(undefined4 *)(param_1 + 0x18),gnt4_cbForStateBusy_bl);
    break;
  case 6:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    if (DAT_80436554 == 0) {
      *(undefined4 *)(DAT_80436540 + 0x1c) = 1;
      gnt4_DVDLowAudioStream_bl
                (0,*(undefined4 *)(param_1 + 0x14),*(uint *)(param_1 + 0x10),gnt4_cbForStateBusy_bl)
      ;
    }
    else {
      *(undefined4 *)(DAT_80436540 + 0x1c) = 0;
      gnt4_DVDLowRequestAudioStatus_bl(0,gnt4_cbForStateBusy_bl);
    }
    break;
  case 7:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    gnt4_DVDLowAudioStream_bl(0x10000,0,0,gnt4_cbForStateBusy_bl);
    break;
  case 8:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    DAT_80436554 = 1;
    gnt4_DVDLowAudioStream_bl(0,0,0,gnt4_cbForStateBusy_bl);
    break;
  case 9:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    gnt4_DVDLowRequestAudioStatus_bl(0,gnt4_cbForStateBusy_bl);
    break;
  case 10:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    gnt4_DVDLowRequestAudioStatus_bl(0x10000,gnt4_cbForStateBusy_bl);
    break;
  case 0xb:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    gnt4_DVDLowRequestAudioStatus_bl(0x20000,gnt4_cbForStateBusy_bl);
    break;
  case 0xc:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    gnt4_DVDLowRequestAudioStatus_bl(0x30000,gnt4_cbForStateBusy_bl);
    break;
  case 0xd:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    gnt4_DVDLowAudioBufferConfig_bl
              (*(int *)(param_1 + 0x10),*(uint *)(param_1 + 0x14),gnt4_cbForStateBusy_bl);
    break;
  case 0xe:
    uVar1 = DAT_cc006004;
    DAT_cc006004 = uVar1;
    *(undefined4 *)(param_1 + 0x1c) = 0x20;
    gnt4_DVDLowInquiry_bl(*(undefined4 *)(param_1 + 0x18),gnt4_cbForStateBusy_bl);
    break;
  case 0xf:
    gnt4_DVDLowStopMotor_bl(gnt4_cbForStateBusy_bl);
  }
  return;
}



// ==== 8020ed48  gnt4-cbForStateBusy-bl ====

void gnt4_cbForStateBusy_bl(uint param_1)

{
  bool bVar1;
  uint uVar2;
  undefined *puVar3;
  int iVar4;
  
  puVar3 = DAT_80436540;
  if (param_1 == 0x10) {
    *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
    gnt4___DVDStoreErrorCode_bl(0x1234568);
    gnt4_DVDReset_bl();
    gnt4_cbForStateError_bl(0);
  }
  else {
    if ((DAT_8043655c != 3) && (DAT_8043655c != 0xf)) {
      if ((DAT_8043655c == 1) || ((DAT_8043655c - 4U < 2 || (DAT_8043655c == 0xe)))) {
        bVar1 = true;
      }
      else if (DAT_8043655c == DAT_80435ccc) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      if (bVar1) {
        iVar4 = DAT_cc006018;
        *(int *)(DAT_80436540 + 0x20) =
             *(int *)(DAT_80436540 + 0x20) + (*(int *)(DAT_80436540 + 0x1c) - iVar4);
      }
      puVar3 = DAT_80436540;
      if ((param_1 & 8) != 0) {
        DAT_80436560 = 0;
        DAT_80436540 = &DAT_803d7a80;
        *(undefined4 *)(puVar3 + 0xc) = 10;
        if (*(code **)(puVar3 + 0x28) != (code *)0x0) {
          (**(code **)(puVar3 + 0x28))(0xfffffffd,puVar3);
        }
        if (DAT_80436564 != (code *)0x0) {
          (*DAT_80436564)(0,puVar3);
        }
        gnt4_stateReady_bl();
        return;
      }
      if ((param_1 & 1) == 0) {
        if (DAT_8043655c == 0xe) {
          *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
          gnt4___DVDStoreErrorCode_bl(0x1234567);
          gnt4_DVDLowStopMotor_bl(gnt4_cbForStateError_bl);
          return;
        }
        if (((((DAT_8043655c == 1) || (DAT_8043655c == 4)) || (DAT_8043655c == 5)) ||
            (DAT_8043655c == 0xe)) &&
           (*(int *)(DAT_80436540 + 0x20) == *(int *)(DAT_80436540 + 0x14))) {
          if (DAT_80436560 == 0) {
            bVar1 = false;
          }
          else {
            DAT_80436568 = 0;
            DAT_80436560 = 0;
            DAT_80436540 = &DAT_803d7a80;
            *(undefined4 *)(puVar3 + 0xc) = 10;
            if (*(code **)(puVar3 + 0x28) != (code *)0x0) {
              (**(code **)(puVar3 + 0x28))(0xfffffffd,puVar3);
            }
            if (DAT_80436564 != (code *)0x0) {
              (*DAT_80436564)(0,puVar3);
            }
            gnt4_stateReady_bl();
            bVar1 = true;
          }
          puVar3 = DAT_80436540;
          if (bVar1) {
            return;
          }
          DAT_80436540 = &DAT_803d7a80;
          *(undefined4 *)(puVar3 + 0xc) = 0;
          if (*(code **)(puVar3 + 0x28) != (code *)0x0) {
            (**(code **)(puVar3 + 0x28))(*(undefined4 *)(puVar3 + 0x20));
          }
          gnt4_stateReady_bl();
          return;
        }
        gnt4_DVDLowRequestError_bl(gnt4_cbForStateGettingError_bl);
        return;
      }
      bVar1 = false;
      DAT_80436574 = 0;
      if (DAT_80436560 != 0) {
        DAT_80436568 = 0;
        DAT_80436560 = 0;
        DAT_80436540 = &DAT_803d7a80;
        *(undefined4 *)(puVar3 + 0xc) = 10;
        if (*(code **)(puVar3 + 0x28) != (code *)0x0) {
          (**(code **)(puVar3 + 0x28))(0xfffffffd,puVar3);
        }
        if (DAT_80436564 != (code *)0x0) {
          (*DAT_80436564)(0,puVar3);
        }
        gnt4_stateReady_bl();
        bVar1 = true;
      }
      puVar3 = DAT_80436540;
      if (bVar1) {
        return;
      }
      if (((DAT_8043655c == 1) || (DAT_8043655c - 4U < 2)) || (DAT_8043655c == 0xe)) {
        bVar1 = true;
      }
      else if (DAT_8043655c == DAT_80435ccc) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      if (bVar1) {
        if (*(int *)(DAT_80436540 + 0x20) != *(int *)(DAT_80436540 + 0x14)) {
          gnt4_stateBusy_bl((int)DAT_80436540);
          return;
        }
        DAT_80436540 = &DAT_803d7a80;
        *(undefined4 *)(puVar3 + 0xc) = 0;
        if (*(code **)(puVar3 + 0x28) != (code *)0x0) {
          (**(code **)(puVar3 + 0x28))(*(undefined4 *)(puVar3 + 0x20));
        }
        gnt4_stateReady_bl();
        return;
      }
      if (DAT_8043655c - 9U < 4) {
        bVar1 = true;
      }
      else if (DAT_8043655c == DAT_803a50b0) {
        bVar1 = true;
      }
      else if (DAT_8043655c == DAT_803a50b4) {
        bVar1 = true;
      }
      else if (DAT_8043655c == DAT_803a50b8) {
        bVar1 = true;
      }
      else {
        bVar1 = false;
      }
      if (bVar1) {
        if ((DAT_8043655c == 0xb) || (DAT_8043655c == 10)) {
          iVar4 = DAT_cc006020;
          iVar4 = iVar4 << 2;
        }
        else {
          iVar4 = DAT_cc006020;
        }
        DAT_80436540 = &DAT_803d7a80;
        *(undefined4 *)(puVar3 + 0xc) = 0;
        if (*(code **)(puVar3 + 0x28) != (code *)0x0) {
          (**(code **)(puVar3 + 0x28))(iVar4);
        }
        gnt4_stateReady_bl();
        return;
      }
      if (DAT_8043655c != 6) {
        DAT_80436540 = &DAT_803d7a80;
        *(undefined4 *)(puVar3 + 0xc) = 0;
        if (*(code **)(puVar3 + 0x28) != (code *)0x0) {
          (**(code **)(puVar3 + 0x28))(0);
        }
        gnt4_stateReady_bl();
        return;
      }
      if (*(int *)(DAT_80436540 + 0x1c) == 0) {
        uVar2 = DAT_cc006020;
        if ((uVar2 & 1) != 0) {
          DAT_80436540 = &DAT_803d7a80;
          *(undefined4 *)(puVar3 + 0xc) = 9;
          if (*(code **)(puVar3 + 0x28) != (code *)0x0) {
            (**(code **)(puVar3 + 0x28))(0xfffffffe);
          }
          gnt4_stateReady_bl();
          return;
        }
        DAT_80436554 = 0;
        *(undefined4 *)(DAT_80436540 + 0x1c) = 1;
        gnt4_DVDLowAudioStream_bl
                  (0,*(undefined4 *)(DAT_80436540 + 0x14),*(uint *)(DAT_80436540 + 0x10),
                   gnt4_cbForStateBusy_bl);
        return;
      }
      DAT_80436540 = &DAT_803d7a80;
      *(undefined4 *)(puVar3 + 0xc) = 0;
      if (*(code **)(puVar3 + 0x28) != (code *)0x0) {
        (**(code **)(puVar3 + 0x28))(0);
      }
      gnt4_stateReady_bl();
      return;
    }
    if ((param_1 & 2) == 0) {
      DAT_80436574 = 0;
      if (DAT_8043655c == 0xf) {
        DAT_80436578 = 1;
      }
      if (DAT_80436560 == 0) {
        bVar1 = false;
      }
      else {
        DAT_80436568 = 7;
        DAT_80436560 = 0;
        DAT_80436540 = &DAT_803d7a80;
        *(undefined4 *)(puVar3 + 0xc) = 10;
        if (*(code **)(puVar3 + 0x28) != (code *)0x0) {
          (**(code **)(puVar3 + 0x28))(0xfffffffd,puVar3);
        }
        if (DAT_80436564 != (code *)0x0) {
          (*DAT_80436564)(0,puVar3);
        }
        gnt4_stateReady_bl();
        bVar1 = true;
      }
      if (!bVar1) {
        *(undefined4 *)(DAT_80436540 + 0xc) = 7;
        gnt4_DVDLowWaitCoverClose_bl(gnt4_cbForStateMotorStopped_bl);
      }
    }
    else {
      *(undefined4 *)(DAT_80436540 + 0xc) = 0xffffffff;
      gnt4___DVDStoreErrorCode_bl(0x1234567);
      gnt4_DVDLowStopMotor_bl(gnt4_cbForStateError_bl);
    }
  }
  return;
}



// ==== 8020f380  gnt4-DVDReadAbsAsyncPrio-bl ====

undefined4
gnt4_DVDReadAbsAsyncPrio_bl
          (undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5,int param_6)

{
  int iVar1;
  undefined4 uVar2;
  
  param_1[2] = 1;
  param_1[6] = param_2;
  param_1[5] = param_3;
  param_1[4] = param_4;
  param_1[8] = 0;
  param_1[10] = param_5;
  if ((DAT_80435cbc != 0) &&
     (((iVar1 = param_1[2], iVar1 == 1 || (iVar1 - 4U < 2)) || (iVar1 == 0xe)))) {
    gnt4_DCInvalidateRange_bl(param_1[6],param_1[5]);
  }
  gnt4_OSDisableInterrupts_bl();
  param_1[3] = 2;
  uVar2 = gnt4___DVDPushWaitingQueue_bl(param_6,param_1);
  if ((DAT_80436540 == 0) && (DAT_8043654c == 0)) {
    gnt4_stateReady_bl();
  }
  gnt4_OSRestoreInterrupts_bl();
  return uVar2;
}



// ==== 8020f45c  gnt4-DVDReadAbsAsyncForBS-bl ====

undefined4
gnt4_DVDReadAbsAsyncForBS_bl
          (undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
          undefined4 param_5)

{
  int iVar1;
  undefined4 uVar2;
  
  param_1[2] = 4;
  param_1[6] = param_2;
  param_1[5] = param_3;
  param_1[4] = param_4;
  param_1[8] = 0;
  param_1[10] = param_5;
  if ((DAT_80435cbc != 0) &&
     (((iVar1 = param_1[2], iVar1 == 1 || (iVar1 - 4U < 2)) || (iVar1 == 0xe)))) {
    gnt4_DCInvalidateRange_bl(param_1[6],param_1[5]);
  }
  gnt4_OSDisableInterrupts_bl();
  param_1[3] = 2;
  uVar2 = gnt4___DVDPushWaitingQueue_bl(2,param_1);
  if ((DAT_80436540 == 0) && (DAT_8043654c == 0)) {
    gnt4_stateReady_bl();
  }
  gnt4_OSRestoreInterrupts_bl();
  return uVar2;
}



// ==== 8020f52c  gnt4-DVDReadDiskID-bl ====

undefined4 gnt4_DVDReadDiskID_bl(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  param_1[2] = 5;
  param_1[6] = param_2;
  param_1[5] = 0x20;
  param_1[4] = 0;
  param_1[8] = 0;
  param_1[10] = param_3;
  if ((DAT_80435cbc != 0) &&
     (((iVar1 = param_1[2], iVar1 == 1 || (iVar1 - 4U < 2)) || (iVar1 == 0xe)))) {
    gnt4_DCInvalidateRange_bl(param_1[6],param_1[5]);
  }
  gnt4_OSDisableInterrupts_bl();
  param_1[3] = 2;
  uVar2 = gnt4___DVDPushWaitingQueue_bl(2,param_1);
  if ((DAT_80436540 == 0) && (DAT_8043654c == 0)) {
    gnt4_stateReady_bl();
  }
  gnt4_OSRestoreInterrupts_bl();
  return uVar2;
}



// ==== 8020f600  gnt4-cbForGetStreamErrorStatusSync-bl ====

undefined4 gnt4_cbForGetStreamErrorStatusSync_bl(undefined4 *param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  param_1[2] = 7;
  param_1[10] = param_2;
  if ((DAT_80435cbc != 0) &&
     (((iVar1 = param_1[2], iVar1 == 1 || (iVar1 - 4U < 2)) || (iVar1 == 0xe)))) {
    gnt4_DCInvalidateRange_bl(param_1[6],param_1[5]);
  }
  gnt4_OSDisableInterrupts_bl();
  param_1[3] = 2;
  uVar2 = gnt4___DVDPushWaitingQueue_bl(1,param_1);
  if ((DAT_80436540 == 0) && (DAT_8043654c == 0)) {
    gnt4_stateReady_bl();
  }
  gnt4_OSRestoreInterrupts_bl();
  return uVar2;
}



// ==== 8020f6bc  gnt4-DVDInquiryAsync-bl ====

undefined4 gnt4_DVDInquiryAsync_bl(undefined4 *param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  param_1[2] = 0xe;
  param_1[6] = param_2;
  param_1[5] = 0x20;
  param_1[8] = 0;
  param_1[10] = param_3;
  if ((DAT_80435cbc != 0) &&
     (((iVar1 = param_1[2], iVar1 == 1 || (iVar1 - 4U < 2)) || (iVar1 == 0xe)))) {
    gnt4_DCInvalidateRange_bl(param_1[6],param_1[5]);
  }
  gnt4_OSDisableInterrupts_bl();
  param_1[3] = 2;
  uVar2 = gnt4___DVDPushWaitingQueue_bl(2,param_1);
  if ((DAT_80436540 == 0) && (DAT_8043654c == 0)) {
    gnt4_stateReady_bl();
  }
  gnt4_OSRestoreInterrupts_bl();
  return uVar2;
}



// ==== 8020f78c  gnt4-DVDReset-bl ====

void gnt4_DVDReset_bl(void)

{
  undefined4 uVar1;
  
  gnt4_DVDLowReset_bl();
  DAT_cc006000 = 0x2a;
  uVar1 = DAT_cc006004;
  DAT_cc006004 = uVar1;
  DAT_80436578 = 0;
  DAT_80436568 = 0;
  return;
}



// ==== 8020f7d0  gnt4-DVDGetCommandBlockStatus-bl ====

int gnt4_DVDGetCommandBlockStatus_bl(int param_1)

{
  int iVar1;
  
  gnt4_OSDisableInterrupts_bl();
  iVar1 = *(int *)(param_1 + 0xc);
  if (iVar1 == 3) {
    iVar1 = 1;
  }
  gnt4_OSRestoreInterrupts_bl();
  return iVar1;
}



// ==== 8020f81c  gnt4-DVDGetDriveStatus-bl ====

int gnt4_DVDGetDriveStatus_bl(void)

{
  undefined *puVar1;
  int iVar2;
  
  gnt4_OSDisableInterrupts_bl();
  puVar1 = DAT_80436540;
  if (DAT_80436558 == 0) {
    if (DAT_80436550 == 0) {
      if (DAT_80436540 == (undefined *)0x0) {
        iVar2 = 0;
      }
      else if (DAT_80436540 == &DAT_803d7a80) {
        iVar2 = 0;
      }
      else {
        gnt4_OSDisableInterrupts_bl();
        iVar2 = *(int *)(puVar1 + 0xc);
        if (iVar2 == 3) {
          iVar2 = 1;
        }
        gnt4_OSRestoreInterrupts_bl();
      }
    }
    else {
      iVar2 = 8;
    }
  }
  else {
    iVar2 = -1;
  }
  gnt4_OSRestoreInterrupts_bl();
  return iVar2;
}



// ==== 8020f8c8  gnt4-DVDSetAutoInvalidation ====

undefined4 gnt4_DVDSetAutoInvalidation(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_80435cbc;
  DAT_80435cbc = param_1;
  return uVar1;
}



// ==== 8020f8d8  gnt4-DVDResume-bl ====

void gnt4_DVDResume_bl(void)

{
  gnt4_OSDisableInterrupts_bl();
  DAT_8043654c = 0;
  if (DAT_80436550 != 0) {
    DAT_80436550 = 0;
    gnt4_stateReady_bl();
  }
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 8020f928  gnt4-DVDCancelAsync-bl ====

undefined4 gnt4_DVDCancelAsync_bl(int *param_1,undefined *param_2)

{
  int iVar1;
  code *pcVar2;
  
  gnt4_OSDisableInterrupts_bl();
  switch(param_1[3]) {
  case 1:
    if (DAT_80436560 != 0) {
      gnt4_OSRestoreInterrupts_bl();
      return 0;
    }
    DAT_80436560 = 1;
    if ((param_1[2] == 4) || (DAT_80436564 = param_2, param_1[2] == 1)) {
      DAT_80436564 = param_2;
      gnt4_DVDLowBreak_bl();
    }
    break;
  case 2:
    gnt4___DVDDequeueWaitingQueue_bl(param_1);
    param_1[3] = 10;
    if ((code *)param_1[10] != (code *)0x0) {
      (*(code *)param_1[10])(0xfffffffd,param_1);
    }
    if (param_2 != (undefined *)0x0) {
      (*(code *)param_2)(0,param_1);
    }
    break;
  case 3:
    iVar1 = param_1[2];
    if (iVar1 == 0xd) {
LAB_8020fa58:
      if (param_2 != (undefined *)0x0) {
        (*(code *)param_2)(0,param_1);
      }
    }
    else {
      if (iVar1 < 0xd) {
        if ((iVar1 < 6) && (3 < iVar1)) goto LAB_8020fa58;
      }
      else if (iVar1 == 0xf) goto LAB_8020fa58;
      if (DAT_80436560 != 0) {
        gnt4_OSRestoreInterrupts_bl();
        return 0;
      }
      DAT_80436560 = 1;
      DAT_80436564 = param_2;
    }
    break;
  case 4:
  case 5:
  case 6:
  case 7:
  case 0xb:
    pcVar2 = (code *)gnt4_DVDLowClearCallback_bl();
    if (pcVar2 != gnt4_cbForStateMotorStopped_bl) {
      gnt4_OSRestoreInterrupts_bl();
      return 0;
    }
    if (param_1[3] == 4) {
      DAT_80436568 = 3;
    }
    if (param_1[3] == 5) {
      DAT_80436568 = 4;
    }
    if (param_1[3] == 6) {
      DAT_80436568 = 1;
    }
    if (param_1[3] == 0xb) {
      DAT_80436568 = 2;
    }
    if (param_1[3] == 7) {
      DAT_80436568 = 7;
    }
    DAT_80436540 = &DAT_803d7a80;
    param_1[3] = 10;
    if ((code *)param_1[10] != (code *)0x0) {
      (*(code *)param_1[10])(0xfffffffd,param_1);
    }
    if (param_2 != (undefined *)0x0) {
      (*(code *)param_2)(0,param_1);
    }
    gnt4_stateReady_bl();
    break;
  case -1:
  case 0:
  case 10:
    if (param_2 != (undefined *)0x0) {
      (*(code *)param_2)(0,param_1);
    }
  }
  gnt4_OSRestoreInterrupts_bl();
  return 1;
}



// ==== 8020fba4  gnt4-DVDCancel-bl ====

undefined4 gnt4_DVDCancel_bl(int *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = gnt4_DVDCancelAsync_bl(param_1,gnt4_cbForCancelSync_bl);
  if (iVar1 == 0) {
    uVar2 = 0xffffffff;
  }
  else {
    gnt4_OSDisableInterrupts_bl();
    while (((iVar1 = param_1[3], 1 < iVar1 + 1U && (iVar1 != 10)) &&
           ((iVar1 != 3 ||
            (((iVar1 = param_1[2], 1 < iVar1 - 4U && (iVar1 != 0xd)) && (iVar1 != 0xf))))))) {
      gnt4_OSSleepThread_bl((int *)&DAT_80436538);
    }
    gnt4_OSRestoreInterrupts_bl();
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 8020fc50  gnt4-cbForCancelSync-bl ====

void gnt4_cbForCancelSync_bl(void)

{
  gnt4_OSWakeupThread_bl((int *)&DAT_80436538);
  return;
}



// ==== 8020fc74  gnt4-DVDGetCurrentDiskID-bl ====

undefined4 gnt4_DVDGetCurrentDiskID_bl(void)

{
  return 0x80000000;
}



// ==== 8020fc7c  gnt4-DVDCheckDisk-bl ====

undefined4 gnt4_DVDCheckDisk_bl(void)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 unaff_r31;
  
  gnt4_OSDisableInterrupts_bl();
  if (DAT_80436558 == 0) {
    if (DAT_80436550 == 0) {
      if (DAT_80436540 == (undefined *)0x0) {
        uVar2 = 0;
      }
      else if (DAT_80436540 == &DAT_803d7a80) {
        uVar2 = 0;
      }
      else {
        uVar2 = *(undefined4 *)(DAT_80436540 + 0xc);
      }
    }
    else {
      uVar2 = 8;
    }
  }
  else {
    uVar2 = 0xffffffff;
  }
  switch(uVar2) {
  case 0:
  case 8:
    uVar1 = DAT_cc006004;
    if (((uVar1 >> 2 & 1) == 0) && ((uVar1 & 1) == 0)) {
      if (DAT_80436568 == 0) {
        unaff_r31 = 1;
      }
      else {
        unaff_r31 = 0;
      }
    }
    else {
      unaff_r31 = 0;
    }
    break;
  case 1:
  case 2:
  case 9:
  case 10:
    unaff_r31 = 1;
    break;
  case 0xffffffff:
  case 3:
  case 4:
  case 5:
  case 6:
  case 7:
  case 0xb:
    unaff_r31 = 0;
  }
  gnt4_OSRestoreInterrupts_bl();
  return unaff_r31;
}



// ==== 8020fd74  gnt4-__DVDPrepareResetAsync-bl ====

void gnt4___DVDPrepareResetAsync_bl(undefined *param_1)

{
  undefined *puVar1;
  int *piVar2;
  
  gnt4_OSDisableInterrupts_bl();
  gnt4___DVDClearWaitingQueue_bl();
  puVar1 = param_1;
  if (DAT_80436560 == 0) {
    if (DAT_80436540 != (int *)0x0) {
      DAT_80436540[10] = 0;
    }
    gnt4_OSDisableInterrupts_bl();
    gnt4_OSDisableInterrupts_bl();
    DAT_8043654c = 1;
    if (DAT_80436540 == (int *)0x0) {
      DAT_80436550 = 1;
    }
    gnt4_OSRestoreInterrupts_bl();
    while (piVar2 = gnt4___DVDPopWaitingQueue_bl(), piVar2 != (int *)0x0) {
      gnt4_DVDCancelAsync_bl(piVar2,(undefined *)0x0);
    }
    if (DAT_80436540 == (int *)0x0) {
      if (param_1 != (undefined *)0x0) {
        (*(code *)param_1)(0,0);
      }
    }
    else {
      gnt4_DVDCancelAsync_bl(DAT_80436540,param_1);
    }
    gnt4_OSDisableInterrupts_bl();
    DAT_8043654c = 0;
    if (DAT_80436550 != 0) {
      DAT_80436550 = 0;
      gnt4_stateReady_bl();
    }
    gnt4_OSRestoreInterrupts_bl();
    gnt4_OSRestoreInterrupts_bl();
    puVar1 = DAT_80436564;
  }
  DAT_80436564 = puVar1;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 8020fe90  gnt4-__DVDClearWaitingQueue-bl ====

void gnt4___DVDClearWaitingQueue_bl(void)

{
  DAT_803d7ad8 = &DAT_803d7ad8;
  DAT_803d7adc = &DAT_803d7ad8;
  DAT_803d7ae0 = &DAT_803d7ae0;
  DAT_803d7ae4 = &DAT_803d7ae0;
  DAT_803d7ae8 = &DAT_803d7ae8;
  DAT_803d7aec = &DAT_803d7ae8;
  DAT_803d7af0 = &DAT_803d7af0;
  DAT_803d7af4 = &DAT_803d7af0;
  return;
}



// ==== 8020fec8  gnt4-__DVDPushWaitingQueue-bl ====

undefined4 gnt4___DVDPushWaitingQueue_bl(int param_1,undefined4 *param_2)

{
  gnt4_OSDisableInterrupts_bl();
  *(undefined4 **)(&DAT_803d7adc)[param_1 * 2] = param_2;
  param_2[1] = (&DAT_803d7adc)[param_1 * 2];
  *param_2 = &DAT_803d7ad8 + param_1 * 2;
  (&DAT_803d7adc)[param_1 * 2] = param_2;
  gnt4_OSRestoreInterrupts_bl();
  return 1;
}



// ==== 8020ff30  gnt4-__DVDPopWaitingQueue-bl ====

int * gnt4___DVDPopWaitingQueue_bl(void)

{
  undefined4 *puVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  gnt4_OSDisableInterrupts_bl();
  iVar5 = 4;
  puVar1 = &DAT_803d7ad8;
  iVar3 = 0;
  do {
    if ((undefined4 *)*puVar1 != puVar1) {
      gnt4_OSRestoreInterrupts_bl();
      gnt4_OSDisableInterrupts_bl();
      piVar2 = &DAT_803d7ad8 + iVar3 * 2;
      piVar4 = (int *)*piVar2;
      *piVar2 = *piVar4;
      *(int **)(*piVar4 + 4) = piVar2;
      gnt4_OSRestoreInterrupts_bl();
      *piVar4 = 0;
      piVar4[1] = 0;
      return piVar4;
    }
    puVar1 = puVar1 + 2;
    iVar3 = iVar3 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  gnt4_OSRestoreInterrupts_bl();
  return (int *)0x0;
}



// ==== 8020ffd0  gnt4-__DVDCheckWaitingQueue-bl ====

undefined4 gnt4___DVDCheckWaitingQueue_bl(void)

{
  undefined4 *puVar1;
  int iVar2;
  
  gnt4_OSDisableInterrupts_bl();
  iVar2 = 4;
  puVar1 = &DAT_803d7ad8;
  do {
    if ((undefined4 *)*puVar1 != puVar1) {
      gnt4_OSRestoreInterrupts_bl();
      return 1;
    }
    puVar1 = puVar1 + 2;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  gnt4_OSRestoreInterrupts_bl();
  return 0;
}



// ==== 80210028  gnt4-__DVDDequeueWaitingQueue-bl ====

undefined4 gnt4___DVDDequeueWaitingQueue_bl(int *param_1)

{
  undefined4 uVar1;
  int *piVar2;
  int iVar3;
  
  gnt4_OSDisableInterrupts_bl();
  piVar2 = (int *)param_1[1];
  iVar3 = *param_1;
  if ((piVar2 == (int *)0x0) || (iVar3 == 0)) {
    gnt4_OSRestoreInterrupts_bl();
    uVar1 = 0;
  }
  else {
    *piVar2 = iVar3;
    *(int **)(iVar3 + 4) = piVar2;
    gnt4_OSRestoreInterrupts_bl();
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 80210088  gnt4-ErrorCode2Num-bl ====

char gnt4_ErrorCode2Num_bl(uint param_1)

{
  uint *puVar1;
  char cVar2;
  int iVar3;
  
  iVar3 = 2;
  puVar1 = &DAT_803a5168;
  cVar2 = '\0';
  while( true ) {
    if (param_1 == *puVar1) {
      return cVar2;
    }
    if (param_1 == puVar1[1]) {
      return cVar2 + '\x01';
    }
    if (param_1 == puVar1[2]) {
      return cVar2 + '\x02';
    }
    if (param_1 == puVar1[3]) {
      return cVar2 + '\x03';
    }
    if (param_1 == puVar1[4]) {
      return cVar2 + '\x04';
    }
    if (param_1 == puVar1[5]) {
      return cVar2 + '\x05';
    }
    if (param_1 == puVar1[6]) {
      return cVar2 + '\x06';
    }
    if (param_1 == puVar1[7]) break;
    if (param_1 == puVar1[8]) {
      return cVar2 + '\b';
    }
    puVar1 = puVar1 + 9;
    cVar2 = cVar2 + '\t';
    iVar3 = iVar3 + -1;
    if (iVar3 == 0) {
      if ((0xfffff < param_1) && (param_1 < 0x100009)) {
        return '\x11';
      }
      return '\x1d';
    }
  }
  return cVar2 + '\a';
}



// ==== 802101a4  gnt4-__DVDStoreErrorCode-bl ====

void gnt4___DVDStoreErrorCode_bl(uint param_1)

{
  char cVar2;
  undefined2 *puVar1;
  char cVar3;
  
  if (param_1 == 0x1234567) {
    cVar2 = -1;
  }
  else if (param_1 == 0x1234568) {
    cVar2 = -2;
  }
  else {
    cVar3 = (char)(param_1 >> 0x18);
    cVar2 = gnt4_ErrorCode2Num_bl(param_1 & 0xffffff);
    if (5 < param_1 >> 0x18) {
      cVar3 = '\x06';
    }
    cVar2 = cVar2 + cVar3 * '\x1e';
  }
  puVar1 = gnt4___OSLockSramEx_bl();
  *(char *)(puVar1 + 0x12) = cVar2;
  gnt4___OSUnlockSramEx_bl(1);
  return;
}



// ==== 80210220  gnt4-DVDCompareDiskID-bl ====

undefined4 gnt4_DVDCompareDiskID_bl(char *param_1,char *param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  if (((*param_1 != '\0') && (*param_2 != '\0')) &&
     (iVar1 = gnt4_strncmp(param_1,param_2,4), iVar1 != 0)) {
    return 0;
  }
  if (((param_1[4] == '\0') || (param_2[4] == '\0')) ||
     (iVar1 = gnt4_strncmp(param_1 + 4,param_2 + 4,2), iVar1 != 0)) {
    uVar2 = 0;
  }
  else if (((param_1[6] == -1) || (param_2[6] == -1)) || (param_1[6] == param_2[6])) {
    if (((param_1[7] == -1) || (param_2[7] == -1)) || (param_1[7] == param_2[7])) {
      uVar2 = 1;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 80210318  zz_0210318_ ====

void zz_0210318_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  ushort uVar2;
  byte bVar3;
  undefined *puVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_4 = DAT_8043cac8;
  local_8 = DAT_8043cacc;
  iVar1 = gnt4_VIGetTvFormat();
  if (iVar1 == 0) {
    uVar2 = zz_0202a60_();
    puVar4 = DAT_80435cd4;
    if (uVar2 == 1) {
      puVar4 = DAT_80435cd0;
    }
  }
  else {
    bVar3 = OSGetLanguage();
    puVar4 = (&PTR_DAT_802b4498)[bVar3];
  }
  local_10 = local_4;
  local_c = local_8;
  zz_0201f78_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&local_c,&local_10,
              puVar4,local_4,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 802103a4  zz_02103a4_ ====

bool zz_02103a4_(int param_1)

{
  bool bVar1;
  
  gnt4_OSDisableInterrupts_bl();
  bVar1 = DAT_80436588 != (code *)0x0;
  if (param_1 == 0) {
    DAT_80436588 = (code *)0x0;
  }
  else {
    DAT_80436588 = zz_0210318_;
  }
  gnt4_OSRestoreInterrupts_bl();
  return bVar1;
}



// ==== 80210414  gnt4-__DVDPrintFatalMessage-bl ====

void gnt4___DVDPrintFatalMessage_bl(void)

{
  if (DAT_80436588 != (code *)0x0) {
    (*DAT_80436588)();
  }
  return;
}



// ==== 80210444  gnt4-cb-bl ====

void gnt4_cb_bl(int param_1,undefined4 *param_2)

{
  if (param_1 < 1) {
    if ((param_1 != -1) && (param_1 == -4)) {
      DAT_80436590 = 0;
      gnt4_DVDReset_bl();
      gnt4_DVDReadDiskID_bl(param_2,DAT_80436598,gnt4_cb_bl);
    }
  }
  else if (DAT_80436590 == 1) {
    DAT_80436590 = 2;
    gnt4_DVDReadAbsAsyncForBS_bl
              (param_2,*(undefined4 *)(DAT_80436594 + 0x10),
               *(int *)(DAT_80436594 + 8) + 0x1fU & 0xffffffe0,*(undefined4 *)(DAT_80436594 + 4),
               gnt4_cb_bl);
  }
  else if ((DAT_80436590 < 1) && (-1 < DAT_80436590)) {
    DAT_80436590 = 1;
    gnt4_DVDReadAbsAsyncForBS_bl(param_2,DAT_80436594,0x20,0x420,gnt4_cb_bl);
  }
  return;
}



// ==== 8021051c  gnt4-__fstLoad-bl ====

void gnt4___fstLoad_bl(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                      undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined1 *puVar2;
  undefined *puVar3;
  undefined4 extraout_r4;
  undefined4 uVar4;
  undefined4 in_r6;
  int iVar5;
  undefined4 in_r7;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar7;
  undefined1 auStack_40 [52];
  
  gnt4_OSGetArenaHi_bl();
  DAT_80436598 = auStack_40;
  DAT_80436594 = &DAT_803d7b00;
  uVar7 = gnt4_DVDReset_bl();
  gnt4_DVDReadDiskID_bl((undefined4 *)&DAT_803d7b38,DAT_80436598,gnt4_cb_bl);
  do {
    iVar1 = gnt4_DVDGetDriveStatus_bl();
  } while (iVar1 != 0);
  DAT_80000038 = *(undefined4 *)(DAT_80436594 + 0x10);
  uVar4 = 0x20;
  DAT_8000003c = *(undefined4 *)(DAT_80436594 + 0xc);
  puVar2 = DAT_80436598;
  gnt4_memcpy(&DAT_80000000,DAT_80436598,0x20);
  uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80435cd8,puVar2,uVar4,in_r6,in_r7,in_r8,in_r9,in_r10);
  iVar5 = (int)DAT_80000002;
  iVar6 = (int)DAT_80000003;
  uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_Game_Name______c_c_c_c_803a55e0,(int)DAT_80000000,(int)DAT_80000001,
                           iVar5,iVar6,in_r8,in_r9,in_r10);
  iVar1 = (int)DAT_80000005;
  uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_Company________c_c_803a55fc,(int)DAT_80000004,iVar1,iVar5,iVar6,in_r8,
                           in_r9,in_r10);
  uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_Disk___________d_803a5614,(uint)DAT_80000006,iVar1,iVar5,iVar6,in_r8,
                           in_r9,in_r10);
  uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_Game_ver_______d_803a5628,(uint)DAT_80000007,iVar1,iVar5,iVar6,in_r8,
                           in_r9,in_r10);
  if (DAT_80000008 == '\0') {
    puVar3 = &DAT_80435cdc;
  }
  else {
    puVar3 = &DAT_80435ce0;
  }
  uVar7 = gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           s_Streaming______s_803a563c,puVar3,iVar1,iVar5,iVar6,in_r8,in_r9,in_r10);
  gnt4_OSReport_bl(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435cd8,
                   extraout_r4,iVar1,iVar5,iVar6,in_r8,in_r9,in_r10);
  gnt4_OSSetArenaHi_bl(*(undefined4 *)(DAT_80436594 + 0x10));
  return;
}



// ==== 80210684  zz_0210684_ ====

void zz_0210684_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,uint param_10)

{
  bool bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined2 *puVar6;
  uint uVar7;
  uint uVar8;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar9;
  undefined8 uVar10;
  ushort local_2e4;
  short local_2e2;
  undefined1 auStack_2e0 [716];
  
  puVar6 = &DAT_cc002030;
  uVar2 = DAT_cc002030;
  uVar7 = (uint)uVar2;
  bVar1 = (uVar2 & 0x8000) != 0;
  if (bVar1) {
    DAT_cc002030 = uVar2 & 0x7fff;
  }
  uVar8 = (uint)bVar1;
  uVar2 = DAT_cc002034;
  if ((uVar2 & 0x8000) != 0) {
    DAT_cc002034 = uVar2 & 0x7fff;
    uVar8 = uVar8 | 2;
  }
  uVar2 = DAT_cc002038;
  if ((uVar2 & 0x8000) != 0) {
    DAT_cc002038 = uVar2 & 0x7fff;
    uVar8 = uVar8 | 4;
  }
  uVar2 = DAT_cc00203c;
  if ((uVar2 & 0x8000) != 0) {
    DAT_cc00203c = uVar2 & 0x7fff;
    uVar8 = uVar8 | 8;
  }
  if (((uVar8 & 4) == 0) && ((uVar8 & 8) == 0)) {
    DAT_804365a4 = DAT_804365a4 + 1;
    gnt4_OSClearContext_bl((int)auStack_2e0);
    uVar9 = gnt4_OSSetCurrentContext_bl((uint)auStack_2e0);
    if (DAT_804365b4 != (code *)0x0) {
      uVar9 = (*DAT_804365b4)(DAT_804365a4);
    }
    if (DAT_804365a8 != 0) {
      if ((DAT_804365d8 == 1) && (iVar4 = zz_02123b0_(), iVar4 == 0)) {
        iVar4 = 0;
        uVar5 = 0;
      }
      else {
        for (; uVar3 = DAT_804365e4, DAT_804365e4 != 0 || DAT_804365e0 != 0;
            DAT_804365e4 = DAT_804365e4 & ~(uint)uVar10) {
          uVar10 = gnt4___shr2u(DAT_804365e0,DAT_804365e4,0x20);
          iVar4 = countLeadingZeros((int)uVar10);
          if (0x1f < iVar4) {
            iVar4 = countLeadingZeros(uVar3);
            iVar4 = iVar4 + 0x20;
          }
          uVar7 = iVar4 * 2;
          (&DAT_cc002000)[iVar4] = *(undefined2 *)(&DAT_803d7be0 + uVar7);
          uVar10 = gnt4___shl2i(0,1,0x3f - iVar4);
          puVar6 = (undefined2 *)~(uint)((ulonglong)uVar10 >> 0x20);
          DAT_804365e0 = DAT_804365e0 & (uint)puVar6;
        }
        DAT_804365d8 = 0;
        iVar4 = 1;
        DAT_804365e8 = DAT_803d7cac;
        DAT_804365ec = DAT_803d7c80;
        DAT_804365f4 = DAT_804365f0;
        uVar5 = DAT_803d7c80;
      }
      if (iVar4 != 0) {
        DAT_804365a8 = 0;
        zz_020adec_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar5,iVar4,puVar6
                    ,uVar7,uVar8,in_r8,in_r9,in_r10);
      }
    }
    if (DAT_804365b8 != (code *)0x0) {
      gnt4_OSClearContext_bl((int)auStack_2e0);
      (*DAT_804365b8)(DAT_804365a4);
    }
    gnt4_OSWakeupThread_bl((int *)&DAT_804365ac);
    gnt4_OSClearContext_bl((int)auStack_2e0);
    gnt4_OSSetCurrentContext_bl(param_10);
  }
  else {
    gnt4_OSClearContext_bl((int)auStack_2e0);
    gnt4_OSSetCurrentContext_bl((uint)auStack_2e0);
    if (DAT_804365bc != (code *)0x0) {
      zz_021280c_(&local_2e2,&local_2e4);
      (*DAT_804365bc)((int)local_2e2,(int)(short)local_2e4);
    }
    gnt4_OSClearContext_bl((int)auStack_2e0);
    gnt4_OSSetCurrentContext_bl(param_10);
  }
  return;
}



// ==== 802108f8  gnt4-VISetPreRetraceCallback ====

undefined4 gnt4_VISetPreRetraceCallback(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_804365b4;
  gnt4_OSDisableInterrupts_bl();
  DAT_804365b4 = param_1;
  gnt4_OSRestoreInterrupts_bl();
  return uVar1;
}



// ==== 8021093c  gnt4-VISetPostRetraceCallback ====

undefined4 gnt4_VISetPostRetraceCallback(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = DAT_804365b8;
  gnt4_OSDisableInterrupts_bl();
  DAT_804365b8 = param_1;
  gnt4_OSRestoreInterrupts_bl();
  return uVar1;
}



// ==== 80210980  gnt4-getTiming ====

undefined * gnt4_getTiming(undefined4 param_1)

{
  switch(param_1) {
  case 0:
    return &DAT_803a5694;
  case 1:
    return &DAT_803a56ba;
  case 2:
    return &DAT_803a5778;
  case 3:
    return &DAT_803a579e;
  case 4:
    return &DAT_803a56e0;
  case 5:
    return &DAT_803a5706;
  default:
    return (undefined *)0x0;
  case 8:
    return &DAT_803a572c;
  case 9:
    return &DAT_803a5752;
  case 0x10:
    return &DAT_803a56e0;
  case 0x11:
    return &DAT_803a5706;
  case 0x14:
    return &DAT_803a5694;
  case 0x15:
    return &DAT_803a56ba;
  case 0x18:
    return &DAT_803a57c4;
  case 0x1a:
    return &DAT_803a57ea;
  }
}



// ==== 80210a20  gnt4-__VIInit ====

void gnt4___VIInit(uint param_1)

{
  uint uVar1;
  byte *pbVar2;
  uint local_14;
  
  uVar1 = param_1 >> 2;
  DAT_800000cc = uVar1;
  pbVar2 = gnt4_getTiming(param_1);
  DAT_cc002002 = 2;
  for (local_14 = 0; local_14 < 1000; local_14 = local_14 + 8) {
  }
  DAT_cc002002 = 0;
  DAT_cc002006 = *(undefined2 *)(pbVar2 + 0x1a);
  DAT_cc002004 = *(undefined2 *)(pbVar2 + 0x1d);
  DAT_cc00200a = (ushort)pbVar2[0x1c] | (ushort)pbVar2[0x1f] << 7;
  DAT_cc002008 = *(short *)(pbVar2 + 0x20) << 1;
  DAT_cc002000 = (ushort)*pbVar2;
  DAT_cc00200e = *(short *)(pbVar2 + 4) + *(short *)(pbVar2 + 2) * 2 + -2;
  DAT_cc00200c = *(short *)(pbVar2 + 8) + 2;
  DAT_cc002012 = *(short *)(pbVar2 + 6) + *(short *)(pbVar2 + 2) * 2 + -2;
  DAT_cc002010 = *(short *)(pbVar2 + 10) + 2;
  DAT_cc002016 = (ushort)pbVar2[0xc] | *(short *)(pbVar2 + 0x10) << 5;
  DAT_cc002014 = (ushort)pbVar2[0xe] | *(short *)(pbVar2 + 0x14) << 5;
  DAT_cc00201a = (ushort)pbVar2[0xd] | *(short *)(pbVar2 + 0x12) << 5;
  DAT_cc002018 = (ushort)pbVar2[0xf] | *(short *)(pbVar2 + 0x16) << 5;
  DAT_cc002048 = 0x2828;
  DAT_cc002036 = 1;
  DAT_cc002034 = 0x1001;
  DAT_cc002032 = *(short *)(pbVar2 + 0x1a) + 1;
  DAT_cc002030 = (short)((int)(uint)*(ushort *)(pbVar2 + 0x18) >> 1) + 1U | 0x1000;
  if (((param_1 == 2) || (param_1 == 3)) || (param_1 == 0x1a)) {
    DAT_cc002002 = (ushort)(uVar1 << 8) | 5;
    DAT_cc00206c = 1;
  }
  else {
    DAT_cc002002 = (ushort)((param_1 & 2) << 2) | 1 | (ushort)(uVar1 << 8);
    DAT_cc00206c = 0;
  }
  return;
}



// ==== 80210c20  gnt4-VIInit-bl ====

void gnt4_VIInit_bl(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                   undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                   undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                   undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  short *psVar1;
  ushort uVar2;
  undefined2 *puVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  short sVar9;
  int iVar8;
  short sVar10;
  
  if (DAT_804365a0 == 0) {
    gnt4_OSRegisterVersion_bl
              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80435ce8,
               0x803a0000,param_11,param_12,param_13,param_14,param_15,param_16);
    DAT_804365a0 = 1;
    DAT_804365c0 = 1;
    uVar2 = DAT_cc002002;
    if ((uVar2 & 1) == 0) {
      gnt4___VIInit(0);
    }
    DAT_804365a4 = 0;
    DAT_804365d4 = 0;
    DAT_804365d0 = 0;
    DAT_804365e4 = 0;
    DAT_804365e0 = 0;
    DAT_804365c8 = 0;
    DAT_804365d8 = 0;
    DAT_804365a8 = 0;
    DAT_cc00204e = DAT_803a5810 | DAT_803a5812 << 10;
    DAT_cc00204c = (ushort)((int)(uint)DAT_803a5812 >> 6) | DAT_803a5814 << 4;
    DAT_cc002052 = DAT_803a5816 | DAT_803a5818 << 10;
    DAT_cc002050 = (ushort)((int)(uint)DAT_803a5818 >> 6) | DAT_803a581a << 4;
    DAT_cc002056 = DAT_803a581c | DAT_803a581e << 10;
    DAT_cc002054 = (ushort)((int)(uint)DAT_803a581e >> 6) | DAT_803a5820 << 4;
    DAT_cc00205a = DAT_803a5822 | DAT_803a5824 << 8;
    DAT_cc002058 = DAT_803a5826 | DAT_803a5828 << 8;
    DAT_cc00205e = DAT_803a582a | DAT_803a582c << 8;
    DAT_cc00205c = DAT_803a582e | DAT_803a5830 << 8;
    DAT_cc002062 = DAT_803a5832 | DAT_803a5834 << 8;
    DAT_cc002060 = DAT_803a5836 | DAT_803a5838 << 8;
    DAT_cc002066 = DAT_803a583a | DAT_803a583c << 8;
    DAT_cc002064 = DAT_803a583e | DAT_803a5840 << 8;
    DAT_cc002070 = 0x280;
    puVar3 = gnt4___OSLockSram_bl();
    DAT_804365c6 = 0;
    DAT_804365c4 = (short)*(char *)(puVar3 + 8);
    gnt4___OSUnlockSram_bl(0);
    uVar2 = DAT_cc002002;
    DAT_803d7c7c = uVar2 >> 2 & 1;
    DAT_803d7c80 = uVar2 >> 8 & 3;
    if ((DAT_800000cc == 1) && ((uVar2 >> 8 & 3) == 0)) {
      DAT_803d7c80 = 5;
    }
    uVar4 = DAT_803d7c80;
    if (DAT_803d7c80 == 3) {
      uVar4 = 0;
    }
    DAT_803d7cac = gnt4_getTiming(uVar4 * 4 + DAT_803d7c7c);
    DAT_804365ec = DAT_803d7c80;
    DAT_803d7c5c = 0x280;
    psVar1 = (short *)(DAT_803d7cac + 2);
    DAT_803d7c5e = *psVar1 * 2;
    DAT_803d7c58 = 0x28;
    DAT_803d7c5a = 0;
    DAT_803d7c60 = 0x50;
    iVar5 = DAT_804365c4 + 0x28;
    if (iVar5 < 0x51) {
      if (iVar5 < 0) {
        iVar5 = 0;
      }
      DAT_803d7c60 = (undefined2)iVar5;
    }
    if (DAT_803d7c78 == 0) {
      iVar5 = 2;
    }
    else {
      iVar5 = 1;
    }
    iVar6 = (int)DAT_804365c6;
    DAT_803d7c62 = 0;
    if (0 < iVar6) {
      DAT_803d7c62 = DAT_804365c6;
    }
    iVar7 = (int)*psVar1;
    if (DAT_803d7c5e + iVar6 + iVar7 * -2 < 1) {
      sVar10 = 0;
    }
    else {
      sVar10 = (short)(DAT_803d7c5e + iVar6) + *psVar1 * -2;
    }
    sVar9 = DAT_804365c6;
    if (-1 < iVar6) {
      sVar9 = 0;
    }
    DAT_803d7c64 = (DAT_803d7c5e + sVar9) - sVar10;
    iVar8 = iVar6;
    if (-1 < iVar6) {
      iVar8 = 0;
    }
    DAT_803d7c66 = DAT_803d7c70 - (short)(iVar8 / iVar5);
    if (DAT_803d7c5e + iVar6 + iVar7 * -2 < 1) {
      iVar7 = 0;
    }
    else {
      iVar7 = DAT_803d7c5e + iVar6 + iVar7 * -2;
    }
    if (-1 < iVar6) {
      iVar6 = 0;
    }
    DAT_803d7c68 = (DAT_803d7c74 + (short)(iVar6 / iVar5)) - (short)(iVar7 / iVar5);
    DAT_803d7c6a = 0x280;
    DAT_803d7c6c = *psVar1 << 1;
    DAT_803d7c6e = 0;
    DAT_803d7c70 = 0;
    DAT_803d7c72 = 0x280;
    DAT_803d7c74 = *psVar1 << 1;
    DAT_803d7c78 = 0;
    DAT_803d7c84 = 0x28;
    DAT_803d7c85 = 0x28;
    DAT_803d7c86 = 0x28;
    DAT_803d7c94 = 0;
    DAT_803d7c98 = 1;
    DAT_803d7c9c = 0;
    DAT_803d7b6a = uVar2;
    DAT_804365e8 = DAT_803d7cac;
    gnt4_OSInitThreadQueue_bl((undefined4 *)&DAT_804365ac);
    uVar2 = DAT_cc002030;
    DAT_cc002030 = uVar2 & 0x7fff;
    uVar2 = DAT_cc002034;
    DAT_cc002034 = uVar2 & 0x7fff;
    DAT_804365b4 = 0;
    DAT_804365b8 = 0;
    gnt4___OSSetInterruptHandler_bl(0x18,zz_0210684_);
    gnt4___OSUnmaskInterrupts_bl(0x80);
  }
  return;
}



// ==== 802110d0  gnt4-VIWaitForRetrace ====

void gnt4_VIWaitForRetrace(void)

{
  int iVar1;
  
  gnt4_OSDisableInterrupts_bl();
  iVar1 = DAT_804365a4;
  do {
    gnt4_OSSleepThread_bl((int *)&DAT_804365ac);
  } while (iVar1 == DAT_804365a4);
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80211124  gnt4-setFbbRegs ====

void gnt4_setFbbRegs(int param_1,uint *param_2,uint *param_3,uint *param_4,uint *param_5)

{
  ushort uVar1;
  int iVar2;
  uint uVar3;
  short sVar4;
  int iVar5;
  
  iVar2 = (uint)*(byte *)(param_1 + 0x2c) * 0x20;
  iVar5 = *(int *)(param_1 + 0x20);
  uVar1 = *(ushort *)(param_1 + 10);
  *param_2 = *(int *)(param_1 + 0x30) +
             (*(ushort *)(param_1 + 0x16) & 0x7ffffff0) * 2 +
             iVar2 * (uint)*(ushort *)(param_1 + 0xe);
  if (iVar5 == 0) {
    uVar3 = *param_2;
  }
  else {
    uVar3 = *param_2 + iVar2;
  }
  *param_3 = uVar3;
  if ((uint)uVar1 + ((int)(uint)uVar1 >> 1) * -2 == 1) {
    uVar3 = *param_2;
    *param_2 = *param_3;
    *param_3 = uVar3;
  }
  *param_2 = *param_2 & 0x3fffffff;
  *param_3 = *param_3 & 0x3fffffff;
  if (*(int *)(param_1 + 0x44) != 0) {
    iVar2 = (uint)*(byte *)(param_1 + 0x2c) * 0x20;
    iVar5 = *(int *)(param_1 + 0x20);
    uVar1 = *(ushort *)(param_1 + 10);
    *param_4 = *(int *)(param_1 + 0x48) +
               (*(ushort *)(param_1 + 0x16) & 0x7ffffff0) * 2 +
               iVar2 * (uint)*(ushort *)(param_1 + 0xe);
    if (iVar5 == 0) {
      uVar3 = *param_4;
    }
    else {
      uVar3 = *param_4 + iVar2;
    }
    *param_5 = uVar3;
    if ((uint)uVar1 + ((int)(uint)uVar1 >> 1) * -2 == 1) {
      uVar3 = *param_4;
      *param_4 = *param_5;
      *param_5 = uVar3;
    }
    *param_4 = *param_4 & 0x3fffffff;
    *param_5 = *param_5 & 0x3fffffff;
  }
  if ((((*param_2 < 0x1000000) && (*param_3 < 0x1000000)) && (*param_4 < 0x1000000)) &&
     (*param_5 < 0x1000000)) {
    sVar4 = 0;
  }
  else {
    sVar4 = 1;
  }
  if (sVar4 != 0) {
    *param_2 = *param_2 >> 5;
    *param_3 = *param_3 >> 5;
    *param_4 = *param_4 >> 5;
    *param_5 = *param_5 >> 5;
  }
  DAT_803d7b86 = (short)*param_2;
  DAT_803d7b84 = sVar4 << 0xc | (ushort)(*param_2 >> 0x10) | (ushort)*(byte *)(param_1 + 0x3c) << 8;
  DAT_803d7b8e = (short)*param_3;
  DAT_803d7b8c = (short)(*param_3 >> 0x10);
  uVar3 = DAT_804365d0 | 0x33000;
  if (*(int *)(param_1 + 0x44) != 0) {
    DAT_803d7b8a = (undefined2)*param_4;
    DAT_803d7b88 = (undefined2)(*param_4 >> 0x10);
    DAT_803d7b92 = (undefined2)*param_5;
    DAT_803d7b90 = (undefined2)(*param_5 >> 0x10);
    uVar3 = DAT_804365d0 | 0x3fc00;
  }
  DAT_804365d0 = uVar3;
  return;
}



// ==== 802113f8  gnt4-setVerticalRegs ====

void gnt4_setVerticalRegs
               (ushort param_1,ushort param_2,ushort param_3,short param_4,short param_5,
               short param_6,short param_7,short param_8,int param_9)

{
  short sVar1;
  uint uVar2;
  short sVar3;
  
  if ((DAT_803d7bd4 & 1) == 0) {
    uVar2 = 2;
    sVar3 = 1;
  }
  else {
    uVar2 = 1;
    sVar3 = 2;
  }
  if ((uint)param_1 == ((int)(uint)param_1 >> 1) * 2) {
    sVar1 = sVar3 * (((short)uVar2 * param_4 - param_2) - param_1);
    DAT_803d7b76 = param_5 + sVar3 * param_1;
    DAT_803d7b74 = param_7 + sVar1;
    DAT_803d7b7a = param_6 + sVar3 * param_1;
    DAT_803d7b78 = param_8 + sVar1;
  }
  else {
    sVar1 = sVar3 * (((short)uVar2 * param_4 - param_2) - param_1);
    DAT_803d7b76 = param_6 + sVar3 * param_1;
    DAT_803d7b74 = param_8 + sVar1;
    DAT_803d7b7a = param_5 + sVar3 * param_1;
    DAT_803d7b78 = param_7 + sVar1;
  }
  uVar2 = param_2 / uVar2;
  if (param_9 != 0) {
    sVar3 = (short)uVar2 * 2 + -2;
    DAT_803d7b76 = DAT_803d7b76 + sVar3;
    DAT_803d7b7a = DAT_803d7b7a + sVar3;
    uVar2 = 0;
    DAT_803d7b74 = DAT_803d7b74 + 2;
    DAT_803d7b78 = DAT_803d7b78 + 2;
  }
  DAT_803d7b68 = param_3 & 0xff | (ushort)(uVar2 << 4);
  DAT_804365d0 = DAT_804365d0 | 0x83c00000;
  return;
}



// ==== 80211598  gnt4-VIConfigure-bl ====

void gnt4_VIConfigure_bl(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4
                        ,undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8
                        ,uint *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                        undefined4 param_13,undefined4 param_14,undefined4 param_15,
                        undefined4 param_16)

{
  int iVar1;
  byte *pbVar2;
  uint uVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  undefined4 extraout_r4_03;
  undefined4 extraout_r4_04;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  ushort uVar9;
  uint uVar8;
  int iVar10;
  short sVar11;
  short sVar12;
  int iVar13;
  undefined8 uVar14;
  
  uVar5 = 0x803a0000;
  gnt4_OSDisableInterrupts_bl();
  uVar3 = DAT_800000cc;
  uVar6 = *param_9 & 3;
  if (DAT_803d7c7c != uVar6) {
    DAT_804365c8 = 1;
    DAT_803d7c7c = uVar6;
  }
  uVar7 = *param_9 >> 2;
  if ((uVar7 == 4) && (DAT_804365fc == 0)) {
    DAT_804365fc = 1;
    uVar14 = gnt4_OSReport_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s__________________________________803a58b0,uVar6,uVar5,param_12,
                              param_13,param_14,param_15,param_16);
    uVar14 = gnt4_OSReport_bl(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_______C_A_U_T_I_O_N_______803a58dc,extraout_r4,uVar5,param_12,
                              param_13,param_14,param_15,param_16);
    uVar14 = gnt4_OSReport_bl(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_This_TV_format__DEBUG_PAL__is_on_803a5908,extraout_r4_00,uVar5,
                              param_12,param_13,param_14,param_15,param_16);
    uVar14 = gnt4_OSReport_bl(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_temporary_solution_until_PAL_DAC_803a5934,extraout_r4_01,uVar5,
                              param_12,param_13,param_14,param_15,param_16);
    uVar14 = gnt4_OSReport_bl(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_is_available__Please_do_NOT_use_t_803a5960,extraout_r4_02,uVar5,
                              param_12,param_13,param_14,param_15,param_16);
    uVar14 = gnt4_OSReport_bl(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              s_mode_in_real_games____803a598c,extraout_r4_03,uVar5,param_12,
                              param_13,param_14,param_15,param_16);
    param_1 = gnt4_OSReport_bl(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               s__________________________________803a58b0,extraout_r4_04,uVar5,
                               param_12,param_13,param_14,param_15,param_16);
  }
  if (uVar3 == 2) {
LAB_802116a0:
    if (((uVar7 == 0) || (uVar7 == 2)) || (uVar7 == 6)) goto LAB_802116e8;
  }
  else if ((int)uVar3 < 2) {
    if (uVar3 == 0) goto LAB_802116a0;
    if (-1 < (int)uVar3) {
LAB_802116bc:
      if ((uVar7 == 1) || (uVar7 == 5)) goto LAB_802116e8;
    }
  }
  else {
    if (uVar3 == 6) goto LAB_802116a0;
    if (((int)uVar3 < 6) && (4 < (int)uVar3)) goto LAB_802116bc;
  }
  gnt4_OSPanic(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80435cec,0x774,
               s_VIConfigure____Tried_to_change_m_803a59b8,uVar3,uVar7,param_14,param_15,param_16);
LAB_802116e8:
  if ((uVar7 == 0) || (DAT_803d7c80 = uVar7, uVar7 == 2)) {
    DAT_803d7c80 = uVar3;
  }
  DAT_803d7c58 = *(short *)((int)param_9 + 10);
  if (DAT_803d7c7c == 1) {
    DAT_803d7c5a = *(short *)(param_9 + 3) << 1;
  }
  else {
    DAT_803d7c5a = *(ushort *)(param_9 + 3);
  }
  DAT_803d7c5c = *(ushort *)((int)param_9 + 0xe);
  DAT_803d7c6a = *(ushort *)(param_9 + 1);
  DAT_803d7c6c = *(short *)(param_9 + 2);
  DAT_803d7c78 = param_9[5];
  DAT_803d7c6e = 0;
  DAT_803d7c70 = 0;
  DAT_803d7c5e = DAT_803d7c6c;
  if (((DAT_803d7c7c != 2) && (DAT_803d7c7c != 3)) && (DAT_803d7c78 == 0)) {
    DAT_803d7c5e = DAT_803d7c6c << 1;
  }
  DAT_803d7c9c = (uint)(DAT_803d7c7c == 3);
  DAT_803d7c72 = DAT_803d7c6a;
  DAT_803d7c74 = DAT_803d7c6c;
  pbVar2 = gnt4_getTiming(DAT_803d7c80 * 4 + DAT_803d7c7c);
  uVar6 = 0x2d0 - DAT_803d7c5c;
  uVar3 = (int)DAT_803d7c58 + (int)DAT_804365c4;
  if (((int)uVar3 <= (int)uVar6) && (uVar6 = uVar3, (int)uVar3 < 0)) {
    uVar6 = 0;
  }
  DAT_803d7c60 = (undefined2)uVar6;
  if (DAT_803d7c78 == 0) {
    iVar4 = 2;
  }
  else {
    iVar4 = 1;
  }
  iVar10 = (int)DAT_804365c6;
  uVar7 = DAT_803d7c5a & 1;
  uVar3 = uVar7;
  if ((int)uVar7 < (short)DAT_803d7c5a + iVar10) {
    uVar3 = (short)DAT_803d7c5a + iVar10;
  }
  DAT_803d7c62 = (ushort)uVar3;
  iVar1 = *(short *)(pbVar2 + 2) * 2 - uVar7;
  iVar13 = (int)(short)DAT_803d7c5a + DAT_803d7c5e + iVar10;
  if (iVar13 - iVar1 < 1) {
    sVar12 = 0;
  }
  else {
    sVar12 = (short)iVar13 - (short)iVar1;
  }
  iVar13 = (short)DAT_803d7c5a + iVar10;
  if ((int)(iVar13 - uVar7) < 0) {
    sVar11 = (short)iVar13 - (short)uVar7;
  }
  else {
    sVar11 = 0;
  }
  DAT_803d7c64 = (DAT_803d7c5e + sVar11) - sVar12;
  if ((int)(((short)DAT_803d7c5a + iVar10) - uVar7) < 0) {
    iVar13 = ((short)DAT_803d7c5a + iVar10) - uVar7;
  }
  else {
    iVar13 = 0;
  }
  DAT_803d7c66 = DAT_803d7c70 - (short)(iVar13 / iVar4);
  iVar13 = (int)(short)DAT_803d7c5a + DAT_803d7c5e + iVar10;
  if (iVar13 - iVar1 < 1) {
    iVar13 = 0;
  }
  else {
    iVar13 = iVar13 - iVar1;
  }
  iVar10 = (short)DAT_803d7c5a + iVar10;
  if ((int)(iVar10 - uVar7) < 0) {
    iVar10 = iVar10 - uVar7;
  }
  else {
    iVar10 = 0;
  }
  DAT_803d7c68 = (DAT_803d7c74 + (short)(iVar10 / iVar4)) - (short)(iVar13 / iVar4);
  if (DAT_804365c0 == 0) {
    DAT_803d7c80 = 3;
  }
  iVar4 = (int)(uint)*(ushort *)(pbVar2 + 0x18) >> 1;
  if (((uint)*(ushort *)(pbVar2 + 0x18) + iVar4 * -2 & 0xffff) == 0) {
    sVar12 = 0;
  }
  else {
    sVar12 = *(short *)(pbVar2 + 0x1a);
  }
  DAT_803d7b9a = sVar12 + 1;
  DAT_803d7b98 = (short)iVar4 + 1U | 0x1000;
  if ((DAT_803d7c7c == 2) || (DAT_803d7c7c == 3)) {
    uVar9 = DAT_803d7b6a & 0xfffb | 4;
  }
  else {
    uVar9 = (ushort)((DAT_803d7c7c & 1) << 2) | DAT_803d7b6a & 0xfffb;
  }
  uVar9 = uVar9 & 0xfff7 | (ushort)(DAT_803d7c9c << 3);
  if ((DAT_803d7c80 == 4) || (DAT_803d7c80 - 5 < 2)) {
    DAT_803d7b6a = uVar9 & 0xfcff;
  }
  else {
    DAT_803d7b6a = uVar9 & 0xfcff | (ushort)(DAT_803d7c80 << 8);
  }
  uVar3 = *param_9;
  if (((uVar3 == 2) || (uVar3 == 3)) || (uVar3 == 0x1a)) {
    DAT_803d7bd4 = DAT_803d7bd4 & 0xfffe | 1;
  }
  else {
    DAT_803d7bd4 = DAT_803d7bd4 & 0xfffe;
  }
  uVar7 = (uint)DAT_803d7c5c;
  uVar8 = (uint)DAT_803d7c72;
  uVar3 = uVar8;
  if (DAT_803d7c9c != 0) {
    uVar3 = uVar8 << 1;
  }
  if ((uVar3 & 0xffff) < uVar7) {
    DAT_803d7bb2 = (ushort)((uVar7 + (uVar3 & 0xffff) * 0x100 + -1) / uVar7) | 0x1000;
    DAT_803d7bd8 = (undefined2)uVar3;
    DAT_804365d4 = DAT_804365d4 | 0x4000280;
  }
  else {
    DAT_803d7bb2 = 0x100;
    DAT_804365d4 = DAT_804365d4 | 0x4000200;
  }
  DAT_803d7b6e = *(undefined2 *)(pbVar2 + 0x1a);
  DAT_803d7b6c = *(undefined2 *)(pbVar2 + 0x1d);
  uVar3 = ((uint)pbVar2[0x1f] + (uVar6 & 0xffff)) - 0x28;
  DAT_803d7b72 = (ushort)pbVar2[0x1c] | (short)uVar3 * 0x80;
  DAT_803d7b70 = (ushort)(uVar3 >> 9) |
                 (short)(((uint)*(ushort *)(pbVar2 + 0x20) + (uVar6 & 0xffff) + 0x28) -
                        (0x2d0 - uVar7)) * 2;
  DAT_803d7b7e = (ushort)pbVar2[0xc] | *(short *)(pbVar2 + 0x10) << 5;
  DAT_803d7b7c = (ushort)pbVar2[0xe] | *(short *)(pbVar2 + 0x14) << 5;
  DAT_803d7b82 = (ushort)pbVar2[0xd] | *(short *)(pbVar2 + 0x12) << 5;
  DAT_803d7b80 = (ushort)pbVar2[0xf] | *(short *)(pbVar2 + 0x16) << 5;
  DAT_804365d0 = DAT_804365d0 | 0x7c3c00c0;
  DAT_803d7c84 = (char)((int)(DAT_803d7c6a + 0xf) >> 4);
  DAT_803d7c85 = DAT_803d7c84;
  if (DAT_803d7c78 != 0) {
    DAT_803d7c85 = DAT_803d7c84 << 1;
  }
  DAT_803d7c94 = (char)DAT_803d7c6e + (char)((int)(uint)DAT_803d7c6e >> 4) * -0x10;
  DAT_803d7c86 = (undefined1)((int)((uint)DAT_803d7c94 + uVar8 + 0xf) >> 4);
  DAT_803d7bb0 = CONCAT11(DAT_803d7c86,DAT_803d7c85);
  DAT_804365d4 = DAT_804365d4 | 0x8000000;
  DAT_803d7cac = pbVar2;
  if (DAT_804365f8 != 0) {
    gnt4_setFbbRegs(-0x7fc283a8,(uint *)&DAT_803d7c8c,(uint *)&DAT_803d7c90,(uint *)&DAT_803d7ca4,
                    (uint *)&DAT_803d7ca8);
  }
  gnt4_setVerticalRegs
            (DAT_803d7c62,DAT_803d7c64,(ushort)*pbVar2,*(short *)(pbVar2 + 2),*(short *)(pbVar2 + 4)
             ,*(short *)(pbVar2 + 6),*(short *)(pbVar2 + 8),*(short *)(pbVar2 + 10),DAT_803d7c98);
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80211dc0  zz_0211dc0_ ====

void zz_0211dc0_(ushort param_1,short param_2,ushort param_3,ushort param_4)

{
  byte *pbVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  short sVar9;
  short sVar10;
  
  gnt4_OSDisableInterrupts_bl();
  pbVar1 = DAT_803d7cac;
  DAT_803d7c5e = param_4;
  if (((DAT_803d7c7c != 2) && (DAT_803d7c7c != 3)) && (DAT_803d7c78 == 0)) {
    DAT_803d7c5e = param_4 << 1;
  }
  iVar2 = 0x2d0 - (uint)DAT_803d7c5c;
  iVar4 = (int)DAT_803d7c58 + (int)DAT_804365c4;
  if ((iVar4 <= iVar2) && (iVar2 = iVar4, iVar4 < 0)) {
    iVar2 = 0;
  }
  DAT_803d7c60 = (undefined2)iVar2;
  if (DAT_803d7c78 == 0) {
    iVar2 = 2;
  }
  else {
    iVar2 = 1;
  }
  iVar4 = (int)DAT_804365c6;
  uVar5 = DAT_803d7c5a & 1;
  uVar3 = uVar5;
  if ((int)uVar5 < (short)DAT_803d7c5a + iVar4) {
    uVar3 = (short)DAT_803d7c5a + iVar4;
  }
  DAT_803d7c62 = (ushort)uVar3;
  iVar7 = *(short *)(DAT_803d7cac + 2) * 2 - uVar5;
  iVar8 = (int)(short)DAT_803d7c5a + (short)DAT_803d7c5e + iVar4;
  if (iVar8 - iVar7 < 1) {
    sVar9 = 0;
  }
  else {
    sVar9 = (short)iVar8 - (short)iVar7;
  }
  iVar8 = (short)DAT_803d7c5a + iVar4;
  if ((int)(iVar8 - uVar5) < 0) {
    sVar10 = (short)iVar8 - (short)uVar5;
  }
  else {
    sVar10 = 0;
  }
  DAT_803d7c64 = (DAT_803d7c5e + sVar10) - sVar9;
  if ((int)(((short)DAT_803d7c5a + iVar4) - uVar5) < 0) {
    iVar8 = ((short)DAT_803d7c5a + iVar4) - uVar5;
  }
  else {
    iVar8 = 0;
  }
  DAT_803d7c66 = param_2 - (short)(iVar8 / iVar2);
  iVar8 = (int)(short)DAT_803d7c5a + (short)DAT_803d7c5e + iVar4;
  if (iVar8 - iVar7 < 1) {
    iVar8 = 0;
  }
  else {
    iVar8 = iVar8 - iVar7;
  }
  iVar4 = (short)DAT_803d7c5a + iVar4;
  if ((int)(iVar4 - uVar5) < 0) {
    iVar4 = iVar4 - uVar5;
  }
  else {
    iVar4 = 0;
  }
  DAT_803d7c68 = (param_4 + (short)(iVar4 / iVar2)) - (short)(iVar8 / iVar2);
  uVar6 = (uint)DAT_803d7c5c;
  uVar5 = (uint)param_3;
  uVar3 = uVar5;
  if (DAT_803d7c9c != 0) {
    uVar3 = uVar5 << 1;
  }
  if ((uVar3 & 0xffff) < uVar6) {
    DAT_803d7bb2 = (ushort)((uVar6 + (uVar3 & 0xffff) * 0x100 + -1) / uVar6) | 0x1000;
    DAT_803d7bd8 = (undefined2)uVar3;
    DAT_804365d4 = DAT_804365d4 | 0x4000080;
  }
  else {
    DAT_803d7bb2 = 0x100;
    DAT_804365d4 = DAT_804365d4 | 0x4000000;
  }
  DAT_803d7c84 = (char)((int)(DAT_803d7c6a + 0xf) >> 4);
  DAT_803d7c85 = DAT_803d7c84;
  if (DAT_803d7c78 != 0) {
    DAT_803d7c85 = DAT_803d7c84 << 1;
  }
  DAT_803d7c94 = (char)param_1 + (char)((int)(uint)param_1 >> 4) * -0x10;
  DAT_803d7c86 = (undefined1)((int)((uint)DAT_803d7c94 + uVar5 + 0xf) >> 4);
  DAT_803d7bb0 = CONCAT11(DAT_803d7c86,DAT_803d7c85);
  DAT_804365d4 = DAT_804365d4 | 0x8000000;
  DAT_803d7c6e = param_1;
  DAT_803d7c70 = param_2;
  DAT_803d7c72 = param_3;
  DAT_803d7c74 = param_4;
  if (DAT_804365f8 != 0) {
    gnt4_setFbbRegs(-0x7fc283a8,(uint *)&DAT_803d7c8c,(uint *)&DAT_803d7c90,(uint *)&DAT_803d7ca4,
                    (uint *)&DAT_803d7ca8);
  }
  gnt4_setVerticalRegs
            (DAT_803d7c62,DAT_803d7c5e,(ushort)*pbVar1,*(short *)(pbVar1 + 2),*(short *)(pbVar1 + 4)
             ,*(short *)(pbVar1 + 6),*(short *)(pbVar1 + 8),*(short *)(pbVar1 + 10),DAT_803d7c98);
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80212154  gnt4-VIFlush-bl ====

void gnt4_VIFlush_bl(void)

{
  uint uVar1;
  int iVar2;
  undefined8 uVar3;
  
  gnt4_OSDisableInterrupts_bl();
  DAT_804365d8 = DAT_804365d8 | DAT_804365c8;
  DAT_804365c8 = 0;
  DAT_804365e0 = DAT_804365e0 | DAT_804365d0;
  DAT_804365e4 = DAT_804365e4 | DAT_804365d4;
  for (; uVar1 = DAT_804365d4, DAT_804365d4 != 0 || DAT_804365d0 != 0;
      DAT_804365d4 = DAT_804365d4 & ~(uint)uVar3) {
    uVar3 = gnt4___shr2u(DAT_804365d0,DAT_804365d4,0x20);
    iVar2 = countLeadingZeros((int)uVar3);
    if (0x1f < iVar2) {
      iVar2 = countLeadingZeros(uVar1);
      iVar2 = iVar2 + 0x20;
    }
    *(undefined2 *)(&DAT_803d7be0 + iVar2 * 2) = (&DAT_803d7b68)[iVar2];
    uVar3 = gnt4___shl2i(0,1,0x3f - iVar2);
    DAT_804365d0 = DAT_804365d0 & ~(uint)((ulonglong)uVar3 >> 0x20);
  }
  DAT_804365a8 = 1;
  DAT_804365f0 = DAT_803d7c88;
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 80212284  gnt4-VISetNextFrameBuffer ====

void gnt4_VISetNextFrameBuffer(undefined4 param_1)

{
  gnt4_OSDisableInterrupts_bl();
  DAT_804365f8 = 1;
  DAT_803d7c88 = param_1;
  gnt4_setFbbRegs(-0x7fc283a8,(uint *)&DAT_803d7c8c,(uint *)&DAT_803d7c90,(uint *)&DAT_803d7ca4,
                  (uint *)&DAT_803d7ca8);
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 802122f0  gnt4-VISetBlack ====

void gnt4_VISetBlack(int param_1)

{
  gnt4_OSDisableInterrupts_bl();
  DAT_803d7c98 = param_1;
  gnt4_setVerticalRegs
            (DAT_803d7c62,DAT_803d7c5e,(ushort)*DAT_803d7cac,*(short *)(DAT_803d7cac + 2),
             *(short *)(DAT_803d7cac + 4),*(short *)(DAT_803d7cac + 6),*(short *)(DAT_803d7cac + 8),
             *(short *)(DAT_803d7cac + 10),param_1);
  gnt4_OSRestoreInterrupts_bl();
  return;
}



// ==== 8021236c  zz_021236c_ ====

undefined4 zz_021236c_(void)

{
  return DAT_804365a4;
}



// ==== 80212374  gnt4-GetCurrentDisplayPosition ====

void gnt4_GetCurrentDisplayPosition(uint *param_1,uint *param_2)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar2 = DAT_cc00202c;
  uVar4 = uVar2 & 0x7ff;
  do {
    uVar2 = DAT_cc00202c;
    uVar3 = DAT_cc00202e;
    uVar5 = uVar2 & 0x7ff;
    bVar1 = uVar4 != uVar5;
    uVar4 = uVar5;
  } while (bVar1);
  *param_1 = uVar3 & 0x7ff;
  *param_2 = uVar5;
  return;
}



// ==== 802123b0  zz_02123b0_ ====

undefined4 zz_02123b0_(void)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  uint uVar4;
  uint uVar5;
  
  uVar2 = DAT_cc00202c;
  uVar4 = uVar2 & 0x7ff;
  do {
    uVar2 = DAT_cc00202c;
    uVar3 = DAT_cc00202e;
    uVar5 = uVar2 & 0x7ff;
    bVar1 = uVar4 != uVar5;
    uVar4 = uVar5;
  } while (bVar1);
  if ((uVar5 - 1) * 2 + ((uVar3 & 0x7ff) - 1) / (uint)*(ushort *)(DAT_804365e8 + 0x1a) <
      (uint)*(ushort *)(DAT_804365e8 + 0x18)) {
    return 1;
  }
  return 0;
}



// ==== 80212418  gnt4-VIGetNextField-bl ====

ushort gnt4_VIGetNextField_bl(void)

{
  ushort uVar1;
  ushort uVar2;
  uint local_18;
  uint local_14 [3];
  
  gnt4_OSDisableInterrupts_bl();
  gnt4_GetCurrentDisplayPosition(&local_18,local_14);
  uVar1 = *(ushort *)(DAT_804365e8 + 0x1a);
  uVar2 = *(ushort *)(DAT_804365e8 + 0x18);
  gnt4_OSRestoreInterrupts_bl();
  return (local_14[0] - 1) * 2 + (local_18 - 1) / (uint)uVar1 < (uint)uVar2 ^ 1 ^ DAT_803d7c62 & 1;
}



// ==== 802124b4  zz_02124b4_ ====

uint zz_02124b4_(void)

{
  bool bVar1;
  ushort uVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  uint uVar6;
  
  iVar4 = DAT_804365e8;
  gnt4_OSDisableInterrupts_bl();
  uVar2 = DAT_cc00202c;
  uVar6 = uVar2 & 0x7ff;
  do {
    uVar2 = DAT_cc00202c;
    uVar3 = DAT_cc00202e;
    uVar5 = uVar2 & 0x7ff;
    bVar1 = uVar6 != uVar5;
    uVar6 = uVar5;
  } while (bVar1);
  uVar6 = (uVar5 - 1) * 2 + ((uVar3 & 0x7ff) - 1) / (uint)*(ushort *)(DAT_804365e8 + 0x1a);
  gnt4_OSRestoreInterrupts_bl();
  if (*(ushort *)(iVar4 + 0x18) <= uVar6) {
    uVar6 = uVar6 - *(ushort *)(iVar4 + 0x18);
  }
  return uVar6 >> 1;
}



