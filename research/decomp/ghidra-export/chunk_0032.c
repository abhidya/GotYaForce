// ==== 80117ed4  zz_0117ed4_ ====

void zz_0117ed4_(int param_1,undefined4 param_2,int param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,1,
                       (int)*(short *)(&DAT_8032a8a8 + param_3 * 8));
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x17;
    puVar1[0x11] = (char)param_3;
    puVar1[0x12] = (char)*(undefined2 *)(&DAT_8032a8aa + param_3 * 8);
    puVar1[0x13] = (char)*(short *)(&DAT_8032a8a8 + param_3 * 8);
    *(code **)(puVar1 + 0xc) = FUN_80118010;
    *(code **)(puVar1 + 0x10c) = FUN_80118248;
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
    *(undefined **)(puVar1 + 0x54) = (&PTR_DAT_8032a8ac)[param_3 * 2];
    *(undefined4 *)(puVar1 + 0x144) = param_2;
  }
  return;
}



// ==== 80118010  FUN_80118010 ====

void FUN_80118010(int param_1)

{
  (*(code *)(&PTR_FUN_8032a8c0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 8011804c  FUN_8011804c ====

void FUN_8011804c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  undefined8 uVar8;
  
  piVar2 = zz_0006dc8_(*(char *)(param_9 + 0x13) * 0x60);
  *(int **)(param_9 + 0xdc) = piVar2;
  if (piVar2 == (int *)0x0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    fVar1 = FLOAT_80439848;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    uVar3 = 1;
    *(undefined4 *)(param_9 + 0xb4) = *(undefined4 *)(*(int *)(param_9 + 0x8c) + 0xb4);
    *(float *)(param_9 + 0x148) = fVar1;
    puVar6 = *(undefined4 **)(param_9 + 0x144);
    uVar5 = *puVar6;
    uVar4 = puVar6[1];
    *(undefined4 *)(param_9 + 0x20) = uVar5;
    *(undefined4 *)(param_9 + 0x24) = uVar4;
    uVar4 = puVar6[2];
    *(undefined4 *)(param_9 + 0x28) = uVar4;
    *(code **)(param_9 + 0x100) = FUN_801182d4;
    uVar8 = zz_0089100_(param_9,1,1);
    for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
      uVar8 = zz_01183c4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          iVar7,uVar3,uVar4,uVar5,puVar6,in_r9,in_r10);
    }
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 80118130  FUN_80118130 ====

void FUN_80118130(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(*(int *)(param_1 + 0x8c) + 0xb4);
  puVar2 = *(undefined4 **)(param_1 + 0x144);
  uVar1 = puVar2[1];
  *(undefined4 *)(param_1 + 0x20) = *puVar2;
  *(undefined4 *)(param_1 + 0x24) = uVar1;
  *(undefined4 *)(param_1 + 0x28) = puVar2[2];
  if (*(char *)(*(int *)(param_1 + 0x8c) + 0x18) < '\x02') {
    zz_01184f8_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 80118194  FUN_80118194 ====

void FUN_80118194(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80439850;
  fVar1 = FLOAT_8043984c;
  *(float *)(param_1 + 0xb4) = *(float *)(param_1 + 0xb4) * FLOAT_8043984c;
  *(float *)(param_1 + 0x148) = *(float *)(param_1 + 0x148) * fVar1;
  if ((*(float *)(param_1 + 0xb4) < fVar2) || (*(float *)(param_1 + 0x148) < fVar2)) {
    *(undefined1 *)(param_1 + 0x18) = 3;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    zz_01184f8_(param_1);
  }
  return;
}



// ==== 80118200  FUN_80118200 ====

void FUN_80118200(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80118248  FUN_80118248 ====

void FUN_80118248(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = 0;
  iVar3 = 0;
  iVar2 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar1) break;
    if (((int)*(short *)(param_9 + 0x1c) & 1 << iVar1) != 0) {
      zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar2 + 0xe0),(float *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar3)
                  ,param_11,param_12,param_13,param_14,param_15,param_16);
      param_1 = zz_00097b4_(*(int *)(iVar2 + 0xe0),(int)*(char *)(param_9 + 0x12));
    }
    iVar3 = iVar3 + 0x60;
    iVar2 = iVar2 + 4;
    iVar1 = iVar1 + 1;
  }
  return;
}



// ==== 801182d4  FUN_801182d4 ====

void FUN_801182d4(int param_1)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                     (double)*(float *)(param_1 + 0x28),(float *)(param_1 + 0x114));
  iVar2 = 0;
  iVar3 = 0;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar2) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar2) != 0) {
      pfVar1 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar3);
      gnt4_PSMTXCopy_bl((float *)(param_1 + 0x114),pfVar1);
      zz_00457d4_('z',pfVar1,pfVar1,*(short *)(pfVar1 + 0x14));
      zz_00457d4_('y',pfVar1,pfVar1,*(short *)((int)pfVar1 + 0x4e));
      zz_00457d4_('x',pfVar1,pfVar1,*(short *)(pfVar1 + 0x13));
      zz_00456a0_(pfVar1,pfVar1,pfVar1 + 0x10);
    }
    iVar3 = iVar3 + 0x60;
    iVar2 = iVar2 + 1;
  }
  return;
}



// ==== 801183c4  zz_01183c4_ ====

void zz_01183c4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  undefined8 uVar5;
  float local_28 [3];
  
  iVar4 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar4) break;
    if (((int)(short)*(ushort *)(param_9 + 0x1c) & 1 << iVar4) == 0) {
      iVar2 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc);
      psVar3 = (short *)(*(int *)(param_9 + 0x54) + param_10 * 0xc);
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar4);
      iVar2 = iVar2 + iVar4 * 0x60;
      *(int *)(iVar2 + 0x5c) = param_10;
      *(undefined2 *)(iVar2 + 0x58) = 0;
      *(short *)(iVar2 + 0x5a) = psVar3[1];
      uVar1 = zz_00055fc_();
      *(short *)(iVar2 + 0x4c) = (short)(uVar1 << 8);
      uVar1 = zz_00055fc_();
      *(short *)(iVar2 + 0x4e) = (short)(uVar1 << 8);
      *(undefined2 *)(iVar2 + 0x50) = 0;
      *(undefined2 *)(iVar2 + 0x52) = 0x1000;
      *(undefined2 *)(iVar2 + 0x54) = 0x1000;
      zz_0018f88_((int *)(iVar2 + 0x30),*(int *)(psVar3 + 2),(float *)(iVar2 + 0x40));
      gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(iVar2 + 0x40),
                          (float *)(iVar2 + 0x40));
      uVar5 = zz_0019338_((int *)(iVar2 + 0x38),*(int *)(psVar3 + 4),local_28);
      iVar4 = iVar4 * 4 + 0xe0;
      zz_000726c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                  *(int *)(param_9 + iVar4),(float *)(int)*psVar3,(int)*(char *)(param_9 + 0x88),
                  param_13,param_14,param_15,param_16);
      zz_0007cac_((double)(local_28[0] * *(float *)(param_9 + 0x148)),*(int *)(param_9 + iVar4));
      iVar4 = (int)*(char *)(param_9 + 0x13);
    }
    iVar4 = iVar4 + 1;
  }
  return;
}



// ==== 801184f8  zz_01184f8_ ====

int zz_01184f8_(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  float local_28 [5];
  
  iVar3 = 0;
  iVar5 = 0;
  iVar4 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar3) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar3) != 0) {
      iVar2 = *(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar5;
      sVar1 = *(short *)(iVar2 + 0x58) + 1;
      *(short *)(iVar2 + 0x58) = sVar1;
      if (*(short *)(iVar2 + 0x5a) <= sVar1) {
        if (*(int *)(iVar2 + 0x5c) == 0) {
          *(undefined2 *)(iVar2 + 0x58) = 0;
          *(undefined2 *)(iVar2 + 0x34) = 0;
        }
        else {
          *(ushort *)(param_1 + 0x1c) = *(ushort *)(param_1 + 0x1c) & ~(ushort)(1 << iVar3);
        }
      }
      local_28[0] = FLOAT_80439848;
      *(short *)(iVar2 + 0x4c) = *(short *)(iVar2 + 0x4c) + *(short *)(iVar2 + 0x52);
      *(short *)(iVar2 + 0x4e) = *(short *)(iVar2 + 0x4e) + *(short *)(iVar2 + 0x54);
      zz_0018fd8_((int *)(iVar2 + 0x30),(int)*(short *)(iVar2 + 0x58),(float *)(iVar2 + 0x40));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(iVar2 + 0x40),
                          (float *)(iVar2 + 0x40));
      zz_0019370_((int *)(iVar2 + 0x38),(int)*(short *)(iVar2 + 0x58),local_28);
      zz_0007cac_((double)(local_28[0] * *(float *)(param_1 + 0x148)),*(int *)(iVar4 + 0xe0));
    }
    iVar5 = iVar5 + 0x60;
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 1;
  }
  return (int)*(short *)(param_1 + 0x1c);
}



// ==== 80118620  zz_0118620_ ====

void zz_0118620_(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(0xd4);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    zz_00e48cc_(param_1,-0x7fcd4ca0,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}



// ==== 80118698  zz_0118698_ ====

void zz_0118698_(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar2 = *(undefined4 *)(param_1 + 0x20);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(param_1 + 0x28);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
      FUN_800e4a18((double)FLOAT_80439858,param_1,(float *)&DAT_8032b360,5,(float *)(puVar2 + 3),
                   (float *)(puVar2 + 0x12),(float *)(puVar2 + 0x30));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcd4ca0,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}



// ==== 8011872c  zz_011872c_ ====

void zz_011872c_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 80118764  zz_0118764_ ====

void zz_0118764_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcd4ca0,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fcd4ca0,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 80118804  zz_0118804_ ====

void zz_0118804_(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(0xd4);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    zz_00e48cc_(param_1,-0x7fcd4bb0,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}



// ==== 8011887c  zz_011887c_ ====

void zz_011887c_(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar2 = *(undefined4 *)(param_1 + 0x20);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(param_1 + 0x28);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
      FUN_800e4a18((double)FLOAT_8043985c,param_1,(float *)&DAT_8032b450,5,(float *)(puVar2 + 3),
                   (float *)(puVar2 + 0x12),(float *)(puVar2 + 0x30));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcd4bb0,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}



// ==== 80118910  zz_0118910_ ====

void zz_0118910_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 80118948  zz_0118948_ ====

void zz_0118948_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcd4bb0,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fcd4bb0,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 801189e8  zz_01189e8_ ====

/* WARNING: Removing unreachable block (ram,0x80118c94) */
/* WARNING: Removing unreachable block (ram,0x801189f8) */

void zz_01189e8_(int param_1,short *param_2)

{
  float fVar1;
  short sVar2;
  int iVar3;
  short sVar5;
  int iVar4;
  double dVar6;
  double dVar7;
  float local_58;
  float local_54;
  undefined4 local_50;
  float local_4c;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  uint uStack_3c;
  longlong local_38;
  undefined4 local_30;
  uint uStack_2c;
  longlong local_28;
  
  iVar3 = zz_0066580_(param_1);
  dVar6 = DOUBLE_80439868;
  fVar1 = FLOAT_80439860;
  uStack_3c = (int)*param_2 ^ 0x80000000;
  local_40 = 0x43300000;
  sVar5 = (short)iVar3 - *(short *)(param_1 + 0x72);
  local_30 = 0x43300000;
  iVar3 = (int)((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80439868) * FLOAT_80439860);
  local_38 = (longlong)iVar3;
  *param_2 = (short)iVar3;
  uStack_2c = (int)param_2[1] ^ 0x80000000;
  iVar3 = (int)((float)((double)CONCAT44(0x43300000,uStack_2c) - dVar6) * fVar1);
  local_28 = (longlong)iVar3;
  param_2[1] = (short)iVar3;
  if ((*(byte *)(param_1 + 0x6e9) & 1) != 0) {
    sVar2 = sVar5;
    if (0x4000 < sVar5) {
      sVar2 = 0;
    }
    if (sVar2 < -0x4000) {
      sVar2 = 0;
    }
    if (0x2000 < sVar2) {
      sVar2 = 0x2000;
    }
    if (sVar2 < -0x2000) {
      sVar2 = -0x2000;
    }
    sVar2 = sVar2 - *param_2;
    if (sVar2 < 1) {
      if (sVar2 < -0x200) {
        sVar2 = -0x200;
      }
    }
    else if (0x200 < sVar2) {
      sVar2 = 0x200;
    }
    *param_2 = *param_2 + sVar2;
  }
  if ((((*(byte *)(param_1 + 0x6e9) & 0xe) != 0) && (sVar5 < 0x4000)) && (-0x4000 < sVar5)) {
    local_4c = *(float *)(param_1 + 0xb18);
    dVar6 = (double)*(float *)(param_1 + 0xb28);
    local_44 = *(undefined4 *)(param_1 + 0xb38);
    local_48 = FLOAT_80439864;
    dVar7 = gnt4_PSVECMag_bl(&local_4c);
    iVar3 = FUN_800452a0(dVar6,dVar7);
    local_58 = *(float *)(param_1 + 0xb20);
    local_54 = *(float *)(param_1 + 0xb30);
    local_50 = *(undefined4 *)(param_1 + 0xb40);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x50c),&local_58,&local_58);
    dVar7 = (double)local_54;
    local_54 = FLOAT_80439864;
    dVar6 = gnt4_PSVECMag_bl(&local_58);
    iVar4 = FUN_800452a0(dVar7,dVar6);
    if ((*(byte *)(param_1 + 0x6e9) & 4) == 0) {
      if ((*(byte *)(param_1 + 0x6e9) & 8) == 0) {
        sVar5 = 0;
      }
      else {
        sVar5 = 0x1000;
      }
    }
    else {
      sVar5 = -0x1000;
    }
    sVar5 = sVar5 + ((short)iVar3 - (short)iVar4);
    if (sVar5 < 1) {
      if (sVar5 < -0x200) {
        sVar5 = -0x200;
      }
    }
    else if (0x200 < sVar5) {
      sVar5 = 0x200;
    }
    param_2[1] = param_2[1] + sVar5;
    if (0x4000 < param_2[1]) {
      param_2[1] = 0x4000;
    }
    if (param_2[1] < -0x4000) {
      param_2[1] = -0x4000;
    }
  }
  *(short *)(param_1 + 0x190a) = param_2[1] >> 2;
  *(short *)(param_1 + 0x1910) = param_2[1] >> 2;
  *(short *)(param_1 + 0x1916) = param_2[1] >> 2;
  *(short *)(param_1 + 0x191c) = param_2[1];
  *(short *)(param_1 + 0x1920) = -(*param_2 >> 1);
  *(short *)(param_1 + 0x190c) = *param_2 >> 3;
  *(short *)(param_1 + 0x1912) = *param_2 >> 3;
  *(short *)(param_1 + 0x1918) = *param_2 >> 3;
  return;
}



// ==== 80118e20  FUN_80118e20 ====

void FUN_80118e20(int param_1)

{
  undefined1 unaff_r30;
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((sVar1 == 0x501) || (sVar1 == 0x50b)) {
    zz_0118620_(param_1);
  }
  else if ((sVar1 == 0x50d) || (sVar1 == 0x517)) {
    zz_0118804_(param_1);
  }
  switch(*(undefined2 *)(param_1 + 1000)) {
  case 0x501:
    unaff_r30 = 0;
    break;
  case 0x50b:
    unaff_r30 = 1;
    break;
  case 0x50d:
    unaff_r30 = 2;
    break;
  case 0x517:
    unaff_r30 = 3;
  }
  for (sVar1 = 0; sVar1 < 5; sVar1 = sVar1 + 1) {
    zz_0136c40_(param_1,unaff_r30,(char)sVar1);
  }
  return;
}



// ==== 80118efc  FUN_80118efc ====

uint FUN_80118efc(uint param_1)

{
  short sVar1;
  uint uVar2;
  bool bVar3;
  
  sVar1 = *(short *)(param_1 + 1000);
  uVar2 = param_1;
  if ((sVar1 == 0x501) || (sVar1 == 0x50d)) {
    if ((*(uint *)(param_1 + 0x5bc) & 0x400) != 0) {
      if (*(float *)(param_1 + 0x694) <= FLOAT_80439864) {
        uVar2 = zz_006dbe0_(param_1,2,1,0);
        if (uVar2 == 0) {
          uVar2 = zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),2);
        }
        else if (*(char *)(param_1 + 0x14c) == '\0') {
          if (*(short *)(param_1 + 1000) == 0x501) {
            bVar3 = FUN_8011a108(param_1,0);
            uVar2 = (uint)bVar3;
          }
          else if (*(short *)(param_1 + 1000) == 0x50d) {
            bVar3 = FUN_8011a108(param_1,1);
            uVar2 = (uint)bVar3;
          }
        }
        else {
          uVar2 = zz_006dbe0_(param_1,2,1,1);
          if (uVar2 != 0) {
            *(undefined1 *)(param_1 + 0x14c) = 2;
          }
        }
        *(float *)(param_1 + 0x694) = FLOAT_80439870 + *(float *)(param_1 + 0x1dc8);
      }
    }
    if (*(char *)(param_1 + 0x14c) == '\x01') {
      uVar2 = zz_00f0104_(param_1,4,3);
    }
  }
  else if (((sVar1 == 0x50b) || (sVar1 == 0x517)) && ((*(uint *)(param_1 + 0x5bc) & 0x400) != 0)) {
    if (*(float *)(param_1 + 0x694) <= FLOAT_80439864) {
      uVar2 = zz_006dbe0_(param_1,2,1,1);
      if (uVar2 == 0) {
        uVar2 = zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),2);
      }
      else if (*(short *)(param_1 + 1000) == 0x50b) {
        uVar2 = zz_01d4d00_(param_1,1);
      }
      else if (*(short *)(param_1 + 1000) == 0x517) {
        uVar2 = zz_01d4d00_(param_1,3);
      }
      *(float *)(param_1 + 0x694) = FLOAT_80439870 + *(float *)(param_1 + 0x1dc8);
    }
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(undefined2 *)(param_1 + 0x18da) = 0;
  }
  return uVar2;
}



// ==== 801190d0  FUN_801190d0 ====

void FUN_801190d0(int param_1)

{
  zz_0046698_(param_1);
  zz_01189e8_(param_1,(short *)(param_1 + 0x144));
  return;
}



// ==== 80119108  FUN_80119108 ====

void FUN_80119108(int param_1)

{
  short sVar1;
  
  zz_01189e8_(param_1,(short *)(param_1 + 0x144));
  sVar1 = *(short *)(param_1 + 1000);
  if ((sVar1 == 0x501) || (sVar1 == 0x50b)) {
    zz_0118698_(param_1);
  }
  else if ((sVar1 == 0x50d) || (sVar1 == 0x517)) {
    zz_011887c_(param_1);
  }
  return;
}



// ==== 8011917c  FUN_8011917c ====

void FUN_8011917c(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((sVar1 == 0x501) || (sVar1 == 0x50b)) {
    zz_011872c_(param_1);
  }
  else if ((sVar1 == 0x50d) || (sVar1 == 0x517)) {
    zz_0118910_(param_1);
  }
  return;
}



// ==== 801191c8  FUN_801191c8 ====

void FUN_801191c8(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((sVar1 == 0x501) || (sVar1 == 0x50b)) {
    zz_0118764_(param_1);
  }
  else if ((sVar1 == 0x50d) || (sVar1 == 0x517)) {
    zz_0118948_(param_1);
  }
  return;
}



// ==== 80119214  FUN_80119214 ====

void FUN_80119214(int param_1)

{
  (*(code *)(&PTR_FUN_8032b5dc)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80119250  FUN_80119250 ====

void FUN_80119250(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8032b5e8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80119298  FUN_80119298 ====

void FUN_80119298(int param_1)

{
  (*(code *)(&PTR_FUN_8032b5fc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801192d4  FUN_801192d4 ====

void FUN_801192d4(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80439874;
  fVar1 = FLOAT_80439864;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc1);
  zz_004beb8_((double)FLOAT_80439878,param_1,0xf,0,1,10,2);
  return;
}



// ==== 8011935c  FUN_8011935c ====

void FUN_8011935c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_80439864;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc1), iVar3 != 0)) {
    dVar4 = (double)FLOAT_80439878;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,2,0,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 801193ec  FUN_801193ec ====

void FUN_801193ec(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    zz_0119848_(param_1);
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 8011946c  FUN_8011946c ====

void FUN_8011946c(int param_1)

{
  (*(code *)(&PTR_FUN_8032b608)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801194a8  FUN_801194a8 ====

void FUN_801194a8(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80439874;
  fVar1 = FLOAT_80439864;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043987c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_80439878,param_1,0xf,0,0xf,10,2);
  return;
}



// ==== 80119568  FUN_80119568 ====

void FUN_80119568(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043987c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_80439864;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc1), iVar3 != 0)) {
    dVar4 = (double)FLOAT_80439878;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,2,1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80119624  FUN_80119624 ====

void FUN_80119624(int param_1)

{
  gnt4_PSQUATScale_bl((double)FLOAT_8043987c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    zz_0119848_(param_1);
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 801196d0  FUN_801196d0 ====

void FUN_801196d0(int param_1)

{
  (*(code *)(&PTR_FUN_80434558)[*(char *)(param_1 + 0x540)])();
  zz_0067458_((double)FLOAT_80439880,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 8011972c  FUN_8011972c ====

void FUN_8011972c(int param_1)

{
  double dVar1;
  
  if (*(char *)(param_1 + 0x5dd) == '\x11') {
    dVar1 = (double)FLOAT_80439878;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x754) = 0;
    zz_004beb8_(dVar1,param_1,1,2,2,0xffffffff,0xffffffff);
    zz_004beb8_((double)FLOAT_80439878,param_1,2,0,0xb,6,2);
  }
  else {
    zz_006a3d0_(param_1,'\0',3,0);
  }
  return;
}



// ==== 801197c4  FUN_801197c4 ====

void FUN_801197c4(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_004cd24_(param_9,0xf);
  if ('\0' < *(char *)(param_9 + 0x1cef)) {
    *(undefined1 *)(param_9 + 0x1cef) = 0;
    zz_0119848_(param_9);
  }
  if (*(char *)(param_9 + 0x1cee) != '\0') {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_9,0x10);
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x14,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80119848  zz_0119848_ ====

uint zz_0119848_(int param_1)

{
  short sVar1;
  uint uVar2;
  bool bVar3;
  
  uVar2 = zz_006dbe0_(param_1,0,1,1);
  if (uVar2 != 0) {
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0x501) {
      bVar3 = zz_013a050_(param_1,0);
      uVar2 = (uint)bVar3;
    }
    else if (sVar1 == 0x50b) {
      uVar2 = zz_01d4d00_(param_1,0);
    }
    else if (sVar1 == 0x50d) {
      bVar3 = zz_013a050_(param_1,1);
      uVar2 = (uint)bVar3;
    }
    else if (sVar1 == 0x517) {
      uVar2 = zz_01d4d00_(param_1,2);
    }
  }
  return uVar2;
}



// ==== 801198e8  FUN_801198e8 ====

void FUN_801198e8(int param_1)

{
  (*(code *)(&PTR_FUN_8032b614)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80119924  FUN_80119924 ====

void FUN_80119924(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032b628)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80119974  FUN_80119974 ====

void FUN_80119974(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439874;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_80439878,param_1,0xf,3,0,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439864;
  return;
}



// ==== 80119a38  FUN_80119a38 ====

void FUN_80119a38(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439864;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80439884;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar2 = FLOAT_80439864;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80439884;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_00b2190_(param_1,0);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80119b30  FUN_80119b30 ====

void FUN_80119b30(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043987c,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar3 = FLOAT_80439864;
  if ((*(short *)(param_1 + 1000) == 0x50d) ||
     (fVar1 = FLOAT_80439888, *(short *)(param_1 + 1000) == 0x517)) {
    fVar1 = FLOAT_8043988c;
  }
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) || (uVar4 = FUN_80066838((double)fVar1,param_1), 0 < (int)uVar4)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80119bf0  FUN_80119bf0 ====

void FUN_80119bf0(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
  }
  if (*(float *)(param_1 + 0x764) <= FLOAT_80439890) {
    *(undefined1 *)(param_1 + 0x1d9b) = 0;
  }
  else {
    zz_006ed8c_((double)FLOAT_8043987c,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80119c94  FUN_80119c94 ====

void FUN_80119c94(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032b638)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80119ce4  FUN_80119ce4 ====

void FUN_80119ce4(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 1;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439874;
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043987c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80439878;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439864;
  zz_0092dcc_(param_1,0);
  return;
}



// ==== 80119e10  FUN_80119e10 ====

void FUN_80119e10(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043987c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_80439864;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80439894;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  return;
}



// ==== 80119ecc  FUN_80119ecc ====

void FUN_80119ecc(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  double dVar5;
  
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439898 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_80439880;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439898 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar3 = FLOAT_80439864;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    *(float *)(param_1 + 0x558) = fVar3;
    fVar2 = FLOAT_8043989c;
    if (*(char *)(param_1 + 0x1b01) != '\0') {
      dVar4 = (double)FLOAT_80439878;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x558) = fVar2;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 80119fd8  FUN_80119fd8 ====

void FUN_80119fd8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80439868) * FLOAT_804398a0);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439880,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_80439864;
  if ((iVar3 == 0) || (*(char *)(param_1 + 0x1cee) == '\0')) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) {
      zz_00b22f4_(param_1);
    }
    else {
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439880 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 8011a108  FUN_8011a108 ====

bool FUN_8011a108(int param_1,int param_2)

{
  undefined1 *puVar1;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0xea4),(float *)(param_2 * 0xc + -0x7fcd44b8),&local_18);
  puVar1 = zz_0088aa0_(param_1,3,8,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = (char)param_2;
    puVar1[0x10] = 0x30;
    *(code **)(puVar1 + 0xc) = FUN_8011a284;
    *(undefined **)(puVar1 + 0x10c) = &DAT_8011a6cc;
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
    *(float *)(puVar1 + 0x20) = local_18;
    *(undefined4 *)(puVar1 + 0x24) = local_14;
    *(undefined4 *)(puVar1 + 0x28) = local_10;
    *(undefined4 *)(puVar1 + 0x144) = *(undefined4 *)(puVar1 + 0x20);
    *(undefined4 *)(puVar1 + 0x148) = *(undefined4 *)(puVar1 + 0x24);
    *(undefined4 *)(puVar1 + 0x14c) = *(undefined4 *)(puVar1 + 0x28);
    *(undefined4 *)(puVar1 + 0x150) = *(undefined4 *)(puVar1 + 0x20);
    *(undefined4 *)(puVar1 + 0x154) = *(undefined4 *)(puVar1 + 0x24);
    *(undefined4 *)(puVar1 + 0x158) = *(undefined4 *)(puVar1 + 0x28);
    *(undefined1 *)(param_1 + 0x14c) = 1;
  }
  return puVar1 != (undefined1 *)0x0;
}



// ==== 8011a284  FUN_8011a284 ====

void FUN_8011a284(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_8032bb60)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8011a2d4  FUN_8011a2d4 ====

void FUN_8011a2d4(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0,1);
  *(undefined1 *)(param_1 + 0x84) = 0xe;
  *(undefined1 *)(param_1 + 0x86) = 0;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar1 + 0xea4),(float *)(*(char *)(param_1 + 0x11) * 0xc + -0x7fcd44b8),
             (float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x144);
  *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x14c);
  *(undefined4 *)(param_1 + 0x168) = *(undefined4 *)(param_1 + 0x150);
  *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(param_1 + 0x154);
  *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_1 + 0x158);
  *(undefined1 *)(param_1 + 0x13) = 0;
  zz_00a2bf8_(iVar1,param_1,(undefined4 *)(param_1 + 0x15c),(undefined4 *)(param_1 + 0x168),
              (int)(char)(&DAT_80434560)[*(char *)(param_1 + 0x11)],0);
  zz_0117ed4_(param_1,(undefined4 *)(param_1 + 0x15c),
              (int)(char)(&DAT_80434564)[*(char *)(param_1 + 0x11)]);
  zz_0117ed4_(param_1,(undefined4 *)(param_1 + 0x168),
              (int)(char)(&DAT_80434564)[*(char *)(param_1 + 0x11)]);
  return;
}



// ==== 8011a448  FUN_8011a448 ====

void FUN_8011a448(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    zz_011a568_(param_1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_011a490_(param_1);
  }
  return;
}



// ==== 8011a490  zz_011a490_ ====

void zz_011a490_(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar2 + 0xea4),(float *)(*(char *)(param_1 + 0x11) * 0xc + -0x7fcd44b8),
             (float *)(param_1 + 0x150));
  if ((*(char *)(iVar2 + 0x14c) == '\x02') && (iVar1 = zz_008ac80_(param_1,5), iVar1 != 0)) {
    *(undefined1 *)(param_1 + 0x19) = 1;
    *(undefined2 *)(param_1 + 0x174) = 300;
    *(undefined2 *)(param_1 + 0x176) = 0;
    *(undefined4 *)(param_1 + 0x178) = 0;
    *(undefined1 *)(param_1 + 0x13) = 1;
    *(undefined1 *)(iVar2 + 0x14c) = 0;
  }
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x144);
  *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x14c);
  *(float *)(param_1 + 0x168) = *(float *)(param_1 + 0x150);
  *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(param_1 + 0x154);
  *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_1 + 0x158);
  return;
}



// ==== 8011a568  zz_011a568_ ====

void zz_011a568_(int param_1)

{
  char cVar1;
  
  if (((*(byte *)(param_1 + 0x1d9) == 0) || ((*(byte *)(param_1 + 0x1d9) & 0x10) == 0)) ||
     (*(short *)(param_1 + 0x176) = *(short *)(param_1 + 0x176) + 1,
     *(short *)(param_1 + 0x176) < 10)) {
    if (*(short *)(param_1 + 0x174) < 1) {
      zz_006de10_(*(int *)(param_1 + 0x90),2);
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
      *(undefined1 *)(param_1 + 0x13) = 0;
    }
    else {
      *(short *)(param_1 + 0x174) = *(short *)(param_1 + 0x174) + -1;
      cVar1 = *(char *)(param_1 + 0x1a);
      if (cVar1 == '\x01') {
        *(undefined1 *)(param_1 + 0x1a) = 0;
        *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x150);
        *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x154);
        *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x158);
      }
      else if ((cVar1 < '\x01') && (-1 < cVar1)) {
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x144);
        *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x148);
        *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x14c);
      }
    }
  }
  else {
    zz_006de10_(*(int *)(param_1 + 0x90),2);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  return;
}



// ==== 8011a678  FUN_8011a678 ====

void FUN_8011a678(int param_1)

{
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 8011a6ac  FUN_8011a6ac ====

void FUN_8011a6ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8011a6d0  zz_011a6d0_ ====

undefined1 * zz_011a6d0_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)0x0;
  if ((*(char *)(param_1 + 0x1dc) == '\0') &&
     (puVar1 = zz_0088aa0_(param_1,3,8,0,1), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x10] = 0x4b;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_8011a7e8;
    *(code **)(puVar1 + 0x10c) = FUN_8011aee8;
    puVar1[0x13] = 4;
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
    *(undefined1 *)(param_1 + 0x150) = 1;
  }
  return puVar1;
}



// ==== 8011a7e8  FUN_8011a7e8 ====

void FUN_8011a7e8(int param_1)

{
  zz_00840b8_(param_1);
  (*(code *)(&PTR_FUN_8032bc90)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8011a838  FUN_8011a838 ====

void FUN_8011a838(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined8 uVar4;
  
  iVar3 = (*(byte *)(param_9 + 0x11) & 0x7f) * 0x18;
  iVar1 = -((int)*(short *)(&DAT_8032bc62 + iVar3) >> 0x1f);
  if (iVar1 == 0) {
    iVar1 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8032bc62 + iVar3));
  }
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(short *)(param_9 + 0x1e) = (short)(char)(&DAT_8032bc74)[iVar3];
    uVar4 = zz_0018f88_((int *)(param_9 + 0x144),-0x7fcd4490,(float *)(param_9 + 0x58));
    piVar2 = zz_0006dc8_(*(char *)(param_9 + 0x13) * 0x68);
    *(int **)(param_9 + 0xdc) = piVar2;
    uVar4 = zz_011b03c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    zz_011b128_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *(code **)(param_9 + 0x100) = FUN_8011ade8;
    zz_0089100_(param_9,1,1);
    *(ushort *)(param_9 + 0x272) = *(ushort *)(param_9 + 0x272) | 1;
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  }
  return;
}



// ==== 8011a93c  FUN_8011a93c ====

void FUN_8011a93c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  double dVar3;
  undefined8 uVar4;
  double dVar5;
  
  uVar4 = (*(code *)(&PTR_FUN_8032bca0)[*(char *)(param_9 + 0x19)])();
  zz_011b274_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
              param_11,param_12,param_13,param_14,param_15,param_16);
  fVar2 = *(float *)(param_9 + 0xd4);
  dVar3 = (double)FLOAT_804398ac;
  fVar1 = (float)((double)fVar2 - (double)FLOAT_804398a8);
  dVar5 = (double)fVar1;
  *(float *)(param_9 + 0xd4) = fVar1;
  if (dVar5 <= dVar3) {
    zz_011b128_(dVar5,(double)fVar2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  return;
}



// ==== 8011a9b4  FUN_8011a9b4 ====

void FUN_8011a9b4(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (*(short *)(param_1 + 0x1e) <= sVar1) {
    *(undefined1 *)(param_1 + 0x19) = 1;
    *(undefined2 *)(param_1 + 0x1e) =
         *(undefined2 *)(&DAT_8032bc70 + (*(byte *)(param_1 + 0x11) & 0x7f) * 0x18);
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xfffe;
  }
  zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x58));
  return;
}



// ==== 8011aa34  FUN_8011aa34 ====

void FUN_8011aa34(int param_1)

{
  int iVar1;
  short sVar2;
  
  iVar1 = (*(byte *)(param_1 + 0x11) & 0x7f) * 0x18;
  if ((*(byte *)(*(int *)(param_1 + 0x90) + 0x7d2) & 3) != 1) {
    if (0x60 < *(short *)(param_1 + 0x1e)) {
      *(undefined2 *)(param_1 + 0x1e) = 0x60;
    }
  }
  sVar2 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar2;
  if (sVar2 < 0) {
    *(undefined1 *)(param_1 + 0x19) = 3;
    zz_008aff0_(param_1);
    *(undefined2 *)(param_1 + 0x1c) = 0;
    *(short *)(param_1 + 0x1e) = (short)(char)(&DAT_8032bc75)[iVar1];
    zz_0018f88_((int *)(param_1 + 0x144),-0x7fcd4450,(float *)(param_1 + 0x58));
  }
  else if (((*(byte *)(param_1 + 0x1d9) != 0) && ((*(byte *)(param_1 + 0x1d9) & 0x10) != 0)) &&
          (*(float *)(*(int *)(param_1 + 0x290) + 0x204) < FLOAT_804398b0)) {
    *(undefined1 *)(param_1 + 0x19) = 2;
    *(undefined2 *)(param_1 + 0x1e) = *(undefined2 *)(&DAT_8032bc72 + iVar1);
    zz_008aff0_(param_1);
    *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x290);
  }
  return;
}



// ==== 8011ab48  FUN_8011ab48 ====

void FUN_8011ab48(int param_1)

{
  byte bVar1;
  float fVar2;
  short sVar4;
  uint uVar3;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  
  bVar1 = *(byte *)(param_1 + 0x11);
  iVar5 = *(int *)(param_1 + 0x14c);
  iVar6 = *(int *)(param_1 + 0x90);
  dVar7 = gnt4_PSVECSquareDistance_bl((float *)(iVar5 + 0x2c),(float *)(iVar5 + 0x5e8));
  if ((double)FLOAT_804398ac < dVar7) {
    dVar8 = 1.0 / SQRT(dVar7);
    dVar8 = DOUBLE_804398b8 * dVar8 * -(dVar7 * dVar8 * dVar8 - DOUBLE_804398c0);
    dVar8 = DOUBLE_804398b8 * dVar8 * -(dVar7 * dVar8 * dVar8 - DOUBLE_804398c0);
    dVar7 = (double)(float)(dVar7 * DOUBLE_804398b8 * dVar8 *
                                    -(dVar7 * dVar8 * dVar8 - DOUBLE_804398c0));
  }
  if ((double)(FLOAT_804398c8 * *(float *)(iVar5 + 0xb4)) < dVar7) {
    *(undefined1 *)(param_1 + 0x151) = 0;
  }
  else {
    *(char *)(param_1 + 0x151) = *(char *)(param_1 + 0x151) + '\x01';
  }
  sVar4 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar4;
  fVar2 = FLOAT_804398ac;
  uVar3 = ((int)sVar4 | 1U - (int)*(char *)(iVar5 + 0x18) | (int)*(char *)(iVar5 + 0x18) - 1U |
          -(int)*(char *)(iVar5 + 0x6cb) | (int)*(char *)(iVar5 + 0x6cb)) >> 0x1f |
          ((int)*(char *)(param_1 + 0x151) >> 0x1f) +
          (uint)(0x2c < (uint)(int)*(char *)(param_1 + 0x151));
  if (uVar3 == 0) {
    uVar3 = 0;
    if ((*(char *)(iVar5 + 0x1db) != '\0') &&
       ((*(byte *)(iVar6 + 0x1dc) & *(byte *)(iVar5 + 0x3e5)) != 0)) {
      uVar3 = 1;
    }
    if (uVar3 != 0) {
      *(float *)(iVar5 + 0x48) = FLOAT_804398ac;
      *(float *)(iVar5 + 0x44) = fVar2;
    }
  }
  if (uVar3 == 0) {
    uVar3 = FUN_8011b390(param_1);
  }
  if (uVar3 != 0) {
    *(undefined1 *)(param_1 + 0x19) = 3;
    zz_008aff0_(param_1);
    *(undefined2 *)(param_1 + 0x1c) = 0;
    *(short *)(param_1 + 0x1e) = (short)(char)(&DAT_8032bc75)[(bVar1 & 0x7f) * 0x18];
    zz_0018f88_((int *)(param_1 + 0x144),-0x7fcd4450,(float *)(param_1 + 0x58));
  }
  return;
}



// ==== 8011ad28  FUN_8011ad28 ====

void FUN_8011ad28(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (*(short *)(param_1 + 0x1e) <= sVar1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
  zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x58));
  return;
}



// ==== 8011ada0  FUN_8011ada0 ====

void FUN_8011ada0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8011ade8  FUN_8011ade8 ====

void FUN_8011ade8(int param_1)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  
  iVar1 = (*(byte *)(param_1 + 0x11) & 0x7f) * 0x18;
  zz_00455fc_((float *)(*(int *)(param_1 + 0x90) + (char)(&DAT_8032bc61)[iVar1] * 0x30 + 0x8d4),
              (float *)(param_1 + 0x114),(float *)(iVar1 + -0x7fcd439c));
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
  if (*(int *)(param_1 + 0xdc) != 0) {
    iVar1 = 0;
    iVar3 = 0;
    while( true ) {
      if (*(char *)(param_1 + 0x13) <= iVar1) break;
      if (((int)*(char *)(param_1 + 0x150) & 1 << iVar1) != 0) {
        pfVar2 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar3);
        zz_00455fc_((float *)(param_1 + 0x114),pfVar2,pfVar2 + 0xc);
        zz_00456a0_(pfVar2,pfVar2,pfVar2 + 0xf);
      }
      iVar3 = iVar3 + 0x68;
      iVar1 = iVar1 + 1;
    }
  }
  return;
}



// ==== 8011aee8  FUN_8011aee8 ====

/* WARNING: Removing unreachable block (ram,0x8011afa8) */

void FUN_8011aee8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar6 = 0;
    iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    iVar5 = 0;
    while (iVar6 < *(char *)(param_9 + 0x13)) {
      if (((int)*(char *)(param_9 + 0x150) & 1 << iVar6) != 0) {
        pfVar4 = (float *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar5);
        if (iVar2 == 0) {
          param_11 = &DAT_804398d4;
          param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,&DAT_804398cc,0x495,&DAT_804398d4,param_12,param_13,param_14,
                                     param_15,param_16);
        }
        if (pfVar4 == (float *)0x0) {
          param_11 = &DAT_804398dc;
          gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_804398cc,0x496,&DAT_804398dc,param_12,param_13,param_14,param_15,
                           param_16);
        }
        param_1 = gnt4_PSMTXCopy_bl(pfVar4,(float *)(iVar2 + 0x44));
        *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
        if (iVar2 != 0) {
          uVar3 = *(uint *)(iVar2 + 0x14);
          bVar1 = false;
          if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
            bVar1 = true;
          }
          if (!bVar1) {
            param_1 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 iVar2,uVar3,param_11,param_12,param_13,param_14,param_15,param_16);
          }
        }
      }
      iVar5 = iVar5 + 0x68;
      iVar6 = iVar6 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
    if (*(char *)(param_9 + 0x150) != '\0') {
      zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
    }
  }
  return;
}



// ==== 8011b03c  zz_011b03c_ ====

void zz_011b03c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar2 = zz_0006f78_(*(int *)(param_9 + 0x90));
    iVar3 = (int)*(char *)(param_9 + 0x13);
    uVar5 = zz_0007198_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                        *(int *)(param_9 + 0xe0),
                        (char *)(int)(char)(&DAT_8032bc60)
                                           [(*(byte *)(param_9 + 0x11) & 0x7f) * 0x18],iVar3,in_r7,
                        in_r8,in_r9,in_r10);
    iVar4 = 0;
    iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    while (iVar4 < *(char *)(param_9 + 0x13)) {
      bVar1 = *(byte *)(param_9 + 0x150);
      *(byte *)(param_9 + 0x150) = bVar1 & ~(byte)(1 << iVar4);
      uVar5 = gnt4_HSD_JObjSetFlagsAll
                        (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,0x10,
                         (undefined *)(uint)bVar1,iVar3,in_r7,in_r8,in_r9,in_r10);
      iVar4 = iVar4 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
  }
  return;
}



// ==== 8011b128  zz_011b128_ ====

void zz_011b128_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    bVar1 = *(byte *)(param_9 + 0x11);
    iVar7 = 0;
    while( true ) {
      if (*(char *)(param_9 + 0x13) <= iVar7) break;
      if (((int)(char)*(byte *)(param_9 + 0x150) & 1 << iVar7) == 0) {
        iVar4 = iVar7 * 0x68;
        iVar5 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc);
        *(byte *)(param_9 + 0x150) = *(byte *)(param_9 + 0x150) | (byte)(1 << iVar7);
        iVar6 = iVar5 + iVar4;
        *(undefined2 *)(iVar6 + 0x4c) = 0;
        *(undefined2 *)(iVar6 + 0x4e) = *(undefined2 *)(&DAT_8032bc76 + (bVar1 & 0x7f) * 0x18);
        zz_0018f88_((int *)(iVar6 + 0x58),-0x7fcd43f0,(float *)(iVar6 + 0x30));
        zz_0018f88_((int *)(iVar6 + 0x50),-0x7fcd4420,(float *)(iVar6 + 0x3c));
        pfVar3 = (float *)(iVar6 + 0x48);
        uVar8 = zz_0019338_((int *)(iVar6 + 0x60),-0x7fcd43c0,pfVar3);
        iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
        if (iVar2 == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(iVar2 + 0x10);
        }
        if (0 < iVar7) {
          do {
            if (iVar2 == 0) {
              iVar2 = 0;
            }
            else {
              iVar2 = *(int *)(iVar2 + 8);
            }
            iVar7 = iVar7 + -1;
          } while (iVar7 != 0);
        }
        gnt4_HSD_JObjClearFlagsAll
                  (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,0x10,
                   (undefined *)pfVar3,iVar4,iVar5,in_r8,in_r9,in_r10);
        zz_00091e4_((double)*(float *)(iVar6 + 0x48),iVar2);
        *(float *)(param_9 + 0xd4) = FLOAT_804398e0;
        iVar7 = (int)*(char *)(param_9 + 0x13);
      }
      iVar7 = iVar7 + 1;
    }
  }
  return;
}



// ==== 8011b274  zz_011b274_ ====

void zz_011b274_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar6 = 0;
    iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    iVar5 = 0;
    while( true ) {
      if (*(char *)(param_9 + 0x13) <= iVar6) break;
      puVar3 = (undefined *)(1 << iVar6);
      if (((int)*(char *)(param_9 + 0x150) & (uint)puVar3) != 0) {
        iVar4 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar5;
        sVar1 = *(short *)(iVar4 + 0x4c) + 1;
        *(short *)(iVar4 + 0x4c) = sVar1;
        if (*(short *)(iVar4 + 0x4e) <= sVar1) {
          *(byte *)(param_9 + 0x150) = *(byte *)(param_9 + 0x150) & ~(byte)puVar3;
          gnt4_HSD_JObjSetFlagsAll
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,0x10,
                     puVar3,param_12,param_13,param_14,param_15,param_16);
        }
        zz_0018fd8_((int *)(iVar4 + 0x58),(int)*(short *)(iVar4 + 0x4c),(float *)(iVar4 + 0x30));
        zz_0018fd8_((int *)(iVar4 + 0x50),(int)*(short *)(iVar4 + 0x4c),(float *)(iVar4 + 0x3c));
        zz_0019370_((int *)(iVar4 + 0x60),(int)*(short *)(iVar4 + 0x4c),(float *)(iVar4 + 0x48));
        param_1 = zz_00091e4_((double)*(float *)(iVar4 + 0x48),iVar2);
      }
      iVar5 = iVar5 + 0x68;
      iVar6 = iVar6 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
  }
  return;
}



// ==== 8011b390  FUN_8011b390 ====

/* WARNING: Removing unreachable block (ram,0x8011b668) */
/* WARNING: Removing unreachable block (ram,0x8011b3a0) */

undefined4 FUN_8011b390(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [3];
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  
  iVar4 = *(int *)(param_1 + 0x90);
  iVar3 = *(int *)(param_1 + 0x14c);
  local_40 = FLOAT_804398ac;
  local_3c = FLOAT_804398e4;
  local_38 = FLOAT_804398e8;
  gnt4_PSMTXMultVec_bl((float *)(iVar4 + 0x904),&local_40,&local_40);
  gnt4_PSVECSubtract_bl((float *)(iVar4 + 0x20),(float *)(iVar4 + 0x2c),afStack_4c);
  gnt4_PSVECAdd_bl(afStack_4c,(float *)(iVar4 + 0x1cc),afStack_4c);
  fVar2 = FLOAT_804398ec;
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x01') {
    *(float *)(iVar3 + 0x48) = FLOAT_804398ac;
    local_34 = *(float *)(iVar3 + 0x20);
    local_3c = fVar2 + local_3c;
    local_2c = *(undefined4 *)(iVar3 + 0x28);
    local_30 = *(float *)(iVar3 + 0x24) + *(float *)(iVar3 + 0x6d0);
    if (local_3c <= *(float *)(iVar3 + 0x24) + *(float *)(iVar3 + 0x6d0)) {
      local_3c = local_30;
    }
    gnt4_PSVECSubtract_bl(&local_40,&local_34,&local_58);
    dVar5 = gnt4_PSVECMag_bl(&local_58);
    if (dVar5 <= (double)FLOAT_804398ac) {
      *(undefined1 *)(param_1 + 0x1a) = 2;
    }
    else if ((double)FLOAT_804398e0 < dVar5) {
      *(byte *)(iVar3 + 0x732) = *(byte *)(iVar3 + 0x732) | 4;
      gnt4_PSVECNormalize_bl(&local_58,&local_58);
      if ((double)FLOAT_804398e0 < dVar5) {
        gnt4_PSQUATScale_bl((double)FLOAT_804398e0,&local_58,&local_58);
      }
      else {
        gnt4_PSQUATScale_bl((double)(float)(dVar5 * (double)FLOAT_804398f0),&local_58,&local_58);
      }
      gnt4_PSVECAdd_bl(&local_58,afStack_4c,&local_58);
      zz_0084498_(iVar3,&local_58);
    }
    else {
      *(undefined1 *)(param_1 + 0x1a) = 2;
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      if (*(float *)(iVar3 + 0x24) + *(float *)(iVar3 + 0x6d0) < FLOAT_804398ec + local_3c) {
        local_58 = FLOAT_804398ac;
        local_54 = FLOAT_804398e0;
        local_50 = FLOAT_804398ac;
        *(byte *)(iVar3 + 0x732) = *(byte *)(iVar3 + 0x732) | 4;
        gnt4_PSVECAdd_bl(&local_58,afStack_4c,&local_58);
        zz_0084498_(iVar3,&local_58);
        *(float *)(iVar3 + 0x48) = FLOAT_804398ac;
      }
      else {
        *(undefined1 *)(param_1 + 0x1a) = 1;
      }
    }
  }
  else if (cVar1 < '\x03') {
    local_34 = *(float *)(iVar3 + 0x20);
    local_2c = *(undefined4 *)(iVar3 + 0x28);
    local_30 = *(float *)(iVar3 + 0x24) + *(float *)(iVar3 + 0x6d0);
    gnt4_PSVECSubtract_bl(&local_40,&local_34,&local_58);
    dVar5 = gnt4_PSVECSquareMag_bl(&local_58);
    if (dVar5 <= (double)FLOAT_804398ac) {
      return 1;
    }
    *(float *)(iVar3 + 0x48) = FLOAT_804398f4;
    *(byte *)(iVar3 + 0x732) = *(byte *)(iVar3 + 0x732) | 4;
    gnt4_PSVECNormalize_bl(&local_58,&local_58);
    gnt4_PSQUATScale_bl((double)FLOAT_804398e0,&local_58,&local_58);
    gnt4_PSVECAdd_bl(&local_58,afStack_4c,&local_58);
    zz_0084498_(iVar3,&local_58);
  }
  return 0;
}



// ==== 8011b68c  zz_011b68c_ ====

undefined1 * zz_011b68c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)0x0;
  if ((*(char *)(param_1 + 0x1dc) == '\0') &&
     (puVar1 = zz_0088aa0_(param_1,3,8,0,1), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x10] = 0x4e;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_8011b7a4;
    *(code **)(puVar1 + 0x10c) = FUN_8011bea4;
    puVar1[0x13] = 4;
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
    *(undefined1 *)(param_1 + 0x144) = 1;
  }
  return puVar1;
}



// ==== 8011b7a4  FUN_8011b7a4 ====

void FUN_8011b7a4(int param_1)

{
  zz_00840b8_(param_1);
  (*(code *)(&PTR_FUN_8032bdd0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8011b7f4  FUN_8011b7f4 ====

void FUN_8011b7f4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined8 uVar4;
  
  iVar3 = (*(byte *)(param_9 + 0x11) & 0x7f) * 0x18;
  iVar1 = -((int)*(short *)(&DAT_8032bda2 + iVar3) >> 0x1f);
  if (iVar1 == 0) {
    iVar1 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8032bda2 + iVar3));
  }
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(short *)(param_9 + 0x1e) = (short)(char)(&DAT_8032bdb4)[iVar3];
    uVar4 = zz_0018f88_((int *)(param_9 + 0x144),-0x7fcd4350,(float *)(param_9 + 0x58));
    piVar2 = zz_0006dc8_(*(char *)(param_9 + 0x13) * 0x68);
    *(int **)(param_9 + 0xdc) = piVar2;
    uVar4 = zz_011bff8_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    zz_011c0e4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *(code **)(param_9 + 0x100) = FUN_8011bda4;
    zz_0089100_(param_9,1,1);
    *(ushort *)(param_9 + 0x272) = *(ushort *)(param_9 + 0x272) | 1;
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  }
  return;
}



// ==== 8011b8f8  FUN_8011b8f8 ====

void FUN_8011b8f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  double dVar3;
  undefined8 uVar4;
  double dVar5;
  
  uVar4 = (*(code *)(&PTR_FUN_8032bde0)[*(char *)(param_9 + 0x19)])();
  zz_011c230_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
              param_11,param_12,param_13,param_14,param_15,param_16);
  fVar2 = *(float *)(param_9 + 0xd4);
  dVar3 = (double)FLOAT_804398fc;
  fVar1 = (float)((double)fVar2 - (double)FLOAT_804398f8);
  dVar5 = (double)fVar1;
  *(float *)(param_9 + 0xd4) = fVar1;
  if (dVar5 <= dVar3) {
    zz_011c0e4_(dVar5,(double)fVar2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  return;
}



// ==== 8011b970  FUN_8011b970 ====

void FUN_8011b970(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (*(short *)(param_1 + 0x1e) <= sVar1) {
    *(undefined1 *)(param_1 + 0x19) = 1;
    *(undefined2 *)(param_1 + 0x1e) =
         *(undefined2 *)(&DAT_8032bdb0 + (*(byte *)(param_1 + 0x11) & 0x7f) * 0x18);
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xfffe;
  }
  zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x58));
  return;
}



// ==== 8011b9f0  FUN_8011b9f0 ====

void FUN_8011b9f0(int param_1)

{
  int iVar1;
  short sVar2;
  
  iVar1 = (*(byte *)(param_1 + 0x11) & 0x7f) * 0x18;
  if ((*(byte *)(*(int *)(param_1 + 0x90) + 0x7d2) & 3) != 1) {
    if (0x60 < *(short *)(param_1 + 0x1e)) {
      *(undefined2 *)(param_1 + 0x1e) = 0x60;
    }
  }
  sVar2 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar2;
  if (sVar2 < 0) {
    *(undefined1 *)(param_1 + 0x19) = 3;
    zz_008aff0_(param_1);
    *(undefined2 *)(param_1 + 0x1c) = 0;
    *(short *)(param_1 + 0x1e) = (short)(char)(&DAT_8032bdb5)[iVar1];
    zz_0018f88_((int *)(param_1 + 0x144),-0x7fcd4310,(float *)(param_1 + 0x58));
  }
  else if (((*(byte *)(param_1 + 0x1d9) != 0) && ((*(byte *)(param_1 + 0x1d9) & 0x10) != 0)) &&
          (*(float *)(*(int *)(param_1 + 0x290) + 0x204) < FLOAT_80439900)) {
    *(undefined1 *)(param_1 + 0x19) = 2;
    *(undefined2 *)(param_1 + 0x1e) = *(undefined2 *)(&DAT_8032bdb2 + iVar1);
    zz_008aff0_(param_1);
    *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x290);
  }
  return;
}



// ==== 8011bb04  FUN_8011bb04 ====

void FUN_8011bb04(int param_1)

{
  byte bVar1;
  float fVar2;
  short sVar4;
  uint uVar3;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  
  bVar1 = *(byte *)(param_1 + 0x11);
  iVar5 = *(int *)(param_1 + 0x14c);
  iVar6 = *(int *)(param_1 + 0x90);
  dVar7 = gnt4_PSVECSquareDistance_bl((float *)(iVar5 + 0x2c),(float *)(iVar5 + 0x5e8));
  if ((double)FLOAT_804398fc < dVar7) {
    dVar8 = 1.0 / SQRT(dVar7);
    dVar8 = DOUBLE_80439908 * dVar8 * -(dVar7 * dVar8 * dVar8 - DOUBLE_80439910);
    dVar8 = DOUBLE_80439908 * dVar8 * -(dVar7 * dVar8 * dVar8 - DOUBLE_80439910);
    dVar7 = (double)(float)(dVar7 * DOUBLE_80439908 * dVar8 *
                                    -(dVar7 * dVar8 * dVar8 - DOUBLE_80439910));
  }
  if ((double)(FLOAT_80439918 * *(float *)(iVar5 + 0xb4)) < dVar7) {
    *(undefined1 *)(param_1 + 0x151) = 0;
  }
  else {
    *(char *)(param_1 + 0x151) = *(char *)(param_1 + 0x151) + '\x01';
  }
  sVar4 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar4;
  fVar2 = FLOAT_804398fc;
  uVar3 = ((int)sVar4 | 1U - (int)*(char *)(iVar5 + 0x18) | (int)*(char *)(iVar5 + 0x18) - 1U |
          -(int)*(char *)(iVar5 + 0x6cb) | (int)*(char *)(iVar5 + 0x6cb)) >> 0x1f |
          ((int)*(char *)(param_1 + 0x151) >> 0x1f) +
          (uint)(0x2c < (uint)(int)*(char *)(param_1 + 0x151));
  if (uVar3 == 0) {
    uVar3 = 0;
    if ((*(char *)(iVar5 + 0x1db) != '\0') &&
       ((*(byte *)(iVar6 + 0x1dc) & *(byte *)(iVar5 + 0x3e5)) != 0)) {
      uVar3 = 1;
    }
    if (uVar3 != 0) {
      *(float *)(iVar5 + 0x48) = FLOAT_804398fc;
      *(float *)(iVar5 + 0x44) = fVar2;
    }
  }
  if (uVar3 == 0) {
    uVar3 = FUN_8011c34c(param_1);
  }
  if (uVar3 != 0) {
    *(undefined1 *)(param_1 + 0x19) = 3;
    zz_008aff0_(param_1);
    *(undefined2 *)(param_1 + 0x1c) = 0;
    *(short *)(param_1 + 0x1e) = (short)(char)(&DAT_8032bdb5)[(bVar1 & 0x7f) * 0x18];
    zz_0018f88_((int *)(param_1 + 0x144),-0x7fcd4310,(float *)(param_1 + 0x58));
  }
  return;
}



// ==== 8011bce4  FUN_8011bce4 ====

void FUN_8011bce4(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (*(short *)(param_1 + 0x1e) <= sVar1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
  zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x58));
  return;
}



// ==== 8011bd5c  FUN_8011bd5c ====

void FUN_8011bd5c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8011bda4  FUN_8011bda4 ====

void FUN_8011bda4(int param_1)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  
  iVar1 = (*(byte *)(param_1 + 0x11) & 0x7f) * 0x18;
  zz_00455fc_((float *)(*(int *)(param_1 + 0x90) + (char)(&DAT_8032bda1)[iVar1] * 0x30 + 0x8d4),
              (float *)(param_1 + 0x114),(float *)(iVar1 + -0x7fcd425c));
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
  if (*(int *)(param_1 + 0xdc) != 0) {
    iVar1 = 0;
    iVar3 = 0;
    while( true ) {
      if (*(char *)(param_1 + 0x13) <= iVar1) break;
      if (((int)*(char *)(param_1 + 0x150) & 1 << iVar1) != 0) {
        pfVar2 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar3);
        zz_00455fc_((float *)(param_1 + 0x114),pfVar2,pfVar2 + 0xc);
        zz_00456a0_(pfVar2,pfVar2,pfVar2 + 0xf);
      }
      iVar3 = iVar3 + 0x68;
      iVar1 = iVar1 + 1;
    }
  }
  return;
}



// ==== 8011bea4  FUN_8011bea4 ====

/* WARNING: Removing unreachable block (ram,0x8011bf64) */

void FUN_8011bea4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar6 = 0;
    iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    iVar5 = 0;
    while (iVar6 < *(char *)(param_9 + 0x13)) {
      if (((int)*(char *)(param_9 + 0x150) & 1 << iVar6) != 0) {
        pfVar4 = (float *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar5);
        if (iVar2 == 0) {
          param_11 = &DAT_80439924;
          param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,&DAT_8043991c,0x495,&DAT_80439924,param_12,param_13,param_14,
                                     param_15,param_16);
        }
        if (pfVar4 == (float *)0x0) {
          param_11 = &DAT_8043992c;
          gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_8043991c,0x496,&DAT_8043992c,param_12,param_13,param_14,param_15,
                           param_16);
        }
        param_1 = gnt4_PSMTXCopy_bl(pfVar4,(float *)(iVar2 + 0x44));
        *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
        if (iVar2 != 0) {
          uVar3 = *(uint *)(iVar2 + 0x14);
          bVar1 = false;
          if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
            bVar1 = true;
          }
          if (!bVar1) {
            param_1 = gnt4_HSD_JObjSetMtxDirtySub_bl
                                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 iVar2,uVar3,param_11,param_12,param_13,param_14,param_15,param_16);
          }
        }
      }
      iVar5 = iVar5 + 0x68;
      iVar6 = iVar6 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
    if (*(char *)(param_9 + 0x150) != '\0') {
      zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
    }
  }
  return;
}



// ==== 8011bff8  zz_011bff8_ ====

void zz_011bff8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar2 = zz_0006f78_(*(int *)(param_9 + 0x90));
    iVar3 = (int)*(char *)(param_9 + 0x13);
    uVar5 = zz_0007198_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                        *(int *)(param_9 + 0xe0),
                        (char *)(int)(char)(&DAT_8032bda0)
                                           [(*(byte *)(param_9 + 0x11) & 0x7f) * 0x18],iVar3,in_r7,
                        in_r8,in_r9,in_r10);
    iVar4 = 0;
    iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    while (iVar4 < *(char *)(param_9 + 0x13)) {
      bVar1 = *(byte *)(param_9 + 0x150);
      *(byte *)(param_9 + 0x150) = bVar1 & ~(byte)(1 << iVar4);
      uVar5 = gnt4_HSD_JObjSetFlagsAll
                        (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,0x10,
                         (undefined *)(uint)bVar1,iVar3,in_r7,in_r8,in_r9,in_r10);
      iVar4 = iVar4 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
  }
  return;
}



// ==== 8011c0e4  zz_011c0e4_ ====

void zz_011c0e4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    bVar1 = *(byte *)(param_9 + 0x11);
    iVar7 = 0;
    while( true ) {
      if (*(char *)(param_9 + 0x13) <= iVar7) break;
      if (((int)(char)*(byte *)(param_9 + 0x150) & 1 << iVar7) == 0) {
        iVar4 = iVar7 * 0x68;
        iVar5 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc);
        *(byte *)(param_9 + 0x150) = *(byte *)(param_9 + 0x150) | (byte)(1 << iVar7);
        iVar6 = iVar5 + iVar4;
        *(undefined2 *)(iVar6 + 0x4c) = 0;
        *(undefined2 *)(iVar6 + 0x4e) = *(undefined2 *)(&DAT_8032bdb6 + (bVar1 & 0x7f) * 0x18);
        zz_0018f88_((int *)(iVar6 + 0x58),-0x7fcd42b0,(float *)(iVar6 + 0x30));
        zz_0018f88_((int *)(iVar6 + 0x50),-0x7fcd42e0,(float *)(iVar6 + 0x3c));
        pfVar3 = (float *)(iVar6 + 0x48);
        uVar8 = zz_0019338_((int *)(iVar6 + 0x60),-0x7fcd4280,pfVar3);
        iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
        if (iVar2 == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(iVar2 + 0x10);
        }
        if (0 < iVar7) {
          do {
            if (iVar2 == 0) {
              iVar2 = 0;
            }
            else {
              iVar2 = *(int *)(iVar2 + 8);
            }
            iVar7 = iVar7 + -1;
          } while (iVar7 != 0);
        }
        gnt4_HSD_JObjClearFlagsAll
                  (uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,0x10,
                   (undefined *)pfVar3,iVar4,iVar5,in_r8,in_r9,in_r10);
        zz_00091e4_((double)*(float *)(iVar6 + 0x48),iVar2);
        *(float *)(param_9 + 0xd4) = FLOAT_80439930;
        iVar7 = (int)*(char *)(param_9 + 0x13);
      }
      iVar7 = iVar7 + 1;
    }
  }
  return;
}



// ==== 8011c230  zz_011c230_ ====

void zz_011c230_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar6 = 0;
    iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    iVar5 = 0;
    while( true ) {
      if (*(char *)(param_9 + 0x13) <= iVar6) break;
      puVar3 = (undefined *)(1 << iVar6);
      if (((int)*(char *)(param_9 + 0x150) & (uint)puVar3) != 0) {
        iVar4 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar5;
        sVar1 = *(short *)(iVar4 + 0x4c) + 1;
        *(short *)(iVar4 + 0x4c) = sVar1;
        if (*(short *)(iVar4 + 0x4e) <= sVar1) {
          *(byte *)(param_9 + 0x150) = *(byte *)(param_9 + 0x150) & ~(byte)puVar3;
          gnt4_HSD_JObjSetFlagsAll
                    (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,0x10,
                     puVar3,param_12,param_13,param_14,param_15,param_16);
        }
        zz_0018fd8_((int *)(iVar4 + 0x58),(int)*(short *)(iVar4 + 0x4c),(float *)(iVar4 + 0x30));
        zz_0018fd8_((int *)(iVar4 + 0x50),(int)*(short *)(iVar4 + 0x4c),(float *)(iVar4 + 0x3c));
        zz_0019370_((int *)(iVar4 + 0x60),(int)*(short *)(iVar4 + 0x4c),(float *)(iVar4 + 0x48));
        param_1 = zz_00091e4_((double)*(float *)(iVar4 + 0x48),iVar2);
      }
      iVar5 = iVar5 + 0x68;
      iVar6 = iVar6 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
  }
  return;
}



// ==== 8011c34c  FUN_8011c34c ====

/* WARNING: Removing unreachable block (ram,0x8011c624) */
/* WARNING: Removing unreachable block (ram,0x8011c35c) */

undefined4 FUN_8011c34c(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [3];
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  
  iVar4 = *(int *)(param_1 + 0x90);
  iVar3 = *(int *)(param_1 + 0x14c);
  local_40 = FLOAT_804398fc;
  local_3c = FLOAT_80439934;
  local_38 = FLOAT_80439938;
  gnt4_PSMTXMultVec_bl((float *)(iVar4 + 0x904),&local_40,&local_40);
  gnt4_PSVECSubtract_bl((float *)(iVar4 + 0x20),(float *)(iVar4 + 0x2c),afStack_4c);
  gnt4_PSVECAdd_bl(afStack_4c,(float *)(iVar4 + 0x1cc),afStack_4c);
  fVar2 = FLOAT_8043993c;
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x01') {
    *(float *)(iVar3 + 0x48) = FLOAT_804398fc;
    local_34 = *(float *)(iVar3 + 0x20);
    local_3c = fVar2 + local_3c;
    local_2c = *(undefined4 *)(iVar3 + 0x28);
    local_30 = *(float *)(iVar3 + 0x24) + *(float *)(iVar3 + 0x6d0);
    if (local_3c <= *(float *)(iVar3 + 0x24) + *(float *)(iVar3 + 0x6d0)) {
      local_3c = local_30;
    }
    gnt4_PSVECSubtract_bl(&local_40,&local_34,&local_58);
    dVar5 = gnt4_PSVECMag_bl(&local_58);
    if (dVar5 <= (double)FLOAT_804398fc) {
      *(undefined1 *)(param_1 + 0x1a) = 2;
    }
    else if ((double)FLOAT_80439930 < dVar5) {
      *(byte *)(iVar3 + 0x732) = *(byte *)(iVar3 + 0x732) | 0x20;
      gnt4_PSVECNormalize_bl(&local_58,&local_58);
      if ((double)FLOAT_80439930 < dVar5) {
        gnt4_PSQUATScale_bl((double)FLOAT_80439930,&local_58,&local_58);
      }
      else {
        gnt4_PSQUATScale_bl((double)(float)(dVar5 * (double)FLOAT_80439940),&local_58,&local_58);
      }
      gnt4_PSVECAdd_bl(&local_58,afStack_4c,&local_58);
      zz_0084498_(iVar3,&local_58);
    }
    else {
      *(undefined1 *)(param_1 + 0x1a) = 2;
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      if (*(float *)(iVar3 + 0x24) + *(float *)(iVar3 + 0x6d0) < FLOAT_8043993c + local_3c) {
        local_58 = FLOAT_804398fc;
        local_54 = FLOAT_80439930;
        local_50 = FLOAT_804398fc;
        *(byte *)(iVar3 + 0x732) = *(byte *)(iVar3 + 0x732) | 0x20;
        gnt4_PSVECAdd_bl(&local_58,afStack_4c,&local_58);
        zz_0084498_(iVar3,&local_58);
        *(float *)(iVar3 + 0x48) = FLOAT_804398fc;
      }
      else {
        *(undefined1 *)(param_1 + 0x1a) = 1;
      }
    }
  }
  else if (cVar1 < '\x03') {
    local_34 = *(float *)(iVar3 + 0x20);
    local_2c = *(undefined4 *)(iVar3 + 0x28);
    local_30 = *(float *)(iVar3 + 0x24) + *(float *)(iVar3 + 0x6d0);
    gnt4_PSVECSubtract_bl(&local_40,&local_34,&local_58);
    dVar5 = gnt4_PSVECSquareMag_bl(&local_58);
    if (dVar5 <= (double)FLOAT_804398fc) {
      return 1;
    }
    *(float *)(iVar3 + 0x48) = FLOAT_80439944;
    *(byte *)(iVar3 + 0x732) = *(byte *)(iVar3 + 0x732) | 0x20;
    gnt4_PSVECNormalize_bl(&local_58,&local_58);
    gnt4_PSQUATScale_bl((double)FLOAT_80439930,&local_58,&local_58);
    gnt4_PSVECAdd_bl(&local_58,afStack_4c,&local_58);
    zz_0084498_(iVar3,&local_58);
  }
  return 0;
}



// ==== 8011c648  zz_011c648_ ====

void zz_011c648_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x10,1,(int)(char)(&DAT_8032bdf0)[param_1]);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0;
    puVar1[0x11] = (char)param_1;
    puVar1[0x12] = param_2;
    puVar1[0x13] = (&DAT_8032bdf0)[(char)puVar1[0x11]];
    *(code **)(puVar1 + 0xc) = FUN_8011c6ec;
    *(code **)(puVar1 + 0x10c) = FUN_8011c878;
  }
  return;
}



// ==== 8011c6ec  FUN_8011c6ec ====

void FUN_8011c6ec(int param_1)

{
  (*(code *)(&PTR_FUN_8032be04)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 8011c728  FUN_8011c728 ====

void FUN_8011c728(int param_1)

{
  uint uVar1;
  int *piVar2;
  
  uVar1 = *(char *)(param_1 + 0x13) * 0x24;
  if (uVar1 < 0x81) {
    *(int *)(param_1 + 0x54) = param_1 + 0x144;
    *(undefined4 *)(param_1 + 0xdc) = 0;
  }
  else {
    piVar2 = zz_0006dc8_(uVar1);
    *(int **)(param_1 + 0xdc) = piVar2;
    if (piVar2 != (int *)0x0) {
      *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(*(int *)(param_1 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_1 + 0x54) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 1;
    (*(code *)(&PTR_FUN_8032be14)[*(char *)(param_1 + 0x11)])(param_1);
    *(undefined1 *)(param_1 + 0x82) = 5;
  }
  return;
}



// ==== 8011c7e0  FUN_8011c7e0 ====

void FUN_8011c7e0(int param_1)

{
  (*(code *)(&PTR_LAB_8032be64)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 8011c830  FUN_8011c830 ====

void FUN_8011c830(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8011c878  FUN_8011c878 ====

void FUN_8011c878(int param_1)

{
  (*(code *)(&PTR_FUN_8032beb4)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 8011c8b4  FUN_8011c8b4 ====

void FUN_8011c8b4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  
  psVar5 = &DAT_8032bf04;
  iVar6 = 0;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    puVar2 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar6);
    *(short *)(puVar2 + 8) = psVar5[1];
    uVar1 = *(undefined4 *)(psVar5 + 4);
    *puVar2 = *(undefined4 *)(psVar5 + 2);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(psVar5 + 6);
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb384,*(int *)(iVar4 + 0xe0),(int)*psVar5,param_12,param_13,
                          param_14,param_15,param_16);
    iVar6 = iVar6 + 0x24;
    psVar5 = psVar5 + 8;
    iVar4 = iVar4 + 4;
  }
  return;
}



// ==== 8011c958  FUN_8011c958 ====

void FUN_8011c958(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  iVar4 = 0;
  iVar3 = param_1;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
    dVar6 = (double)pfVar1[1];
    dVar7 = (double)pfVar1[2];
    uVar5 = gnt4_PSMTXTrans_bl((double)*pfVar1,dVar6,dVar7,afStack_48);
    zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_48,
                param_3,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(iVar3 + 0xe0),(int)*(short *)(pfVar1 + 8));
    iVar4 = iVar4 + 0x24;
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 8011c9e0  FUN_8011c9e0 ====

/* WARNING: Removing unreachable block (ram,0x8011ca9c) */
/* WARNING: Removing unreachable block (ram,0x8011c9f0) */

void FUN_8011c9e0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  double dVar8;
  
  dVar8 = (double)FLOAT_80439948;
  pbVar6 = &DAT_8032bf34;
  iVar7 = 0;
  iVar5 = param_9;
  for (iVar4 = 0; iVar4 < *(char *)(param_9 + 0x13); iVar4 = iVar4 + 1) {
    puVar3 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar7);
    puVar3[6] = (float)dVar8;
    *(undefined2 *)(puVar3 + 8) = 0;
    *(ushort *)((int)puVar3 + 0x22) = (ushort)*pbVar6;
    bVar1 = pbVar6[1];
    *(short *)((int)puVar3 + 0x1e) = (short)(char)bVar1;
    *(short *)(puVar3 + 7) = (short)(char)bVar1;
    uVar2 = *(undefined4 *)(pbVar6 + 8);
    *puVar3 = *(undefined4 *)(pbVar6 + 4);
    puVar3[1] = uVar2;
    puVar3[2] = *(undefined4 *)(pbVar6 + 0xc);
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb384,*(int *)(iVar5 + 0xe0),(int)*(short *)(pbVar6 + 2),param_12,
                          param_13,param_14,param_15,param_16);
    iVar7 = iVar7 + 0x24;
    pbVar6 = pbVar6 + 0x10;
    iVar5 = iVar5 + 4;
  }
  zz_011cab8_(param_9);
  return;
}



// ==== 8011cab8  zz_011cab8_ ====

/* WARNING: Removing unreachable block (ram,0x8011cc54) */
/* WARNING: Removing unreachable block (ram,0x8011cc4c) */
/* WARNING: Removing unreachable block (ram,0x8011cad0) */
/* WARNING: Removing unreachable block (ram,0x8011cac8) */

void zz_011cab8_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  
  dVar10 = (double)FLOAT_80439948;
  iVar7 = 0;
  iVar6 = param_1;
  for (iVar5 = 0; fVar1 = FLOAT_8043994c, fVar2 = FLOAT_80439948, iVar5 < *(char *)(param_1 + 0x13);
      iVar5 = iVar5 + 1) {
    iVar4 = *(int *)(param_1 + 0x54) + iVar7;
    dVar9 = (double)*(float *)(iVar4 + 0x18);
    if (((ushort)(byte)PTR_DAT_80433944[0x2c] & *(ushort *)(iVar4 + 0x22)) == 0) {
      if (0 < *(short *)(iVar4 + 0x20)) {
        *(short *)(iVar4 + 0x20) = *(short *)(iVar4 + 0x20) + 1;
        fVar3 = FLOAT_80439950;
        fVar1 = *(float *)(iVar4 + 0x18) - fVar1;
        *(float *)(iVar4 + 0x18) = fVar1;
        fVar2 = FLOAT_80439948;
        if (fVar1 <= fVar3) {
          *(undefined2 *)(iVar4 + 0x20) = 0;
          *(float *)(iVar4 + 0x18) = fVar2;
          *(undefined2 *)(iVar4 + 0x1c) = *(undefined2 *)(iVar4 + 0x1e);
        }
      }
    }
    else if (*(short *)(iVar4 + 0x1c) == 0) {
      *(short *)(iVar4 + 0x20) = *(short *)(iVar4 + 0x20) + 1;
      if ((*(float *)(iVar4 + 0x18) < fVar2) &&
         (fVar1 = *(float *)(iVar4 + 0x18) + FLOAT_8043994c, *(float *)(iVar4 + 0x18) = fVar1,
         fVar2 <= fVar1)) {
        *(float *)(iVar4 + 0x18) = fVar2;
      }
    }
    else {
      *(short *)(iVar4 + 0x1c) = *(short *)(iVar4 + 0x1c) + -1;
    }
    while (0x7f < *(short *)(iVar4 + 0x20)) {
      *(short *)(iVar4 + 0x20) = *(short *)(iVar4 + 0x20) + -0x40;
    }
    dVar8 = zz_0045238_((short)((int)*(short *)(iVar4 + 0x20) << 10));
    fVar1 = FLOAT_80439958;
    if (*(short *)(iVar4 + 0x20) < 0x10) {
      fVar1 = FLOAT_80439954;
    }
    *(float *)(iVar4 + 0xc) = (float)(dVar8 * (double)fVar1 + dVar10);
    fVar1 = FLOAT_80439960;
    if (*(short *)(iVar4 + 0x20) < 0x10) {
      fVar1 = FLOAT_8043995c;
    }
    *(float *)(iVar4 + 0x10) = (float)(dVar8 * (double)fVar1 + dVar10);
    *(float *)(iVar4 + 0x14) = (float)dVar10;
    if ((double)*(float *)(iVar4 + 0x18) != dVar9) {
      zz_0007cac_((double)*(float *)(iVar4 + 0x18),*(int *)(iVar6 + 0xe0));
    }
    iVar7 = iVar7 + 0x24;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 8011cc70  FUN_8011cc70 ====

void FUN_8011cc70(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  float afStack_48 [13];
  
  gnt4_PSMTXCopy_bl((float *)(&DAT_803c7714 + (char)PTR_DAT_80433930[0x28] * 0x3e4),
                    (float *)(param_9 + 0x114));
  iVar4 = 0;
  iVar3 = param_9;
  for (iVar2 = 0; iVar2 < *(char *)(param_9 + 0x13); iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar4);
    if ((*(short *)(pfVar1 + 8) != 0) && (FLOAT_80439950 != pfVar1[6])) {
      zz_00455fc_((float *)(param_9 + 0x114),afStack_48,pfVar1);
      pfVar1 = pfVar1 + 3;
      uVar5 = zz_00456a0_(afStack_48,afStack_48,pfVar1);
      zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar3 + 0xe0),afStack_48,(undefined *)pfVar1,param_12,param_13,param_14,
                  param_15,param_16);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
    }
    iVar4 = iVar4 + 0x24;
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 8011cd48  FUN_8011cd48 ====

void FUN_8011cd48(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  short sVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  undefined4 uVar6;
  int iVar7;
  undefined2 *puVar8;
  int iVar9;
  float *pfVar10;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar11;
  int iVar12;
  
  fVar1 = FLOAT_80439964;
  iVar12 = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  iVar7 = *(char *)(param_9 + 0x12) * 0x18;
  puVar8 = (undefined2 *)(&DAT_8032bf74 + iVar7);
  *(undefined2 *)(param_9 + 0x1e) = *puVar8;
  uVar6 = *(undefined4 *)(&DAT_8032bf7c + iVar7);
  *(undefined4 *)(param_9 + 0x9c) = *(undefined4 *)(&DAT_8032bf78 + iVar7);
  *(undefined4 *)(param_9 + 0xa0) = uVar6;
  *(undefined4 *)(param_9 + 0xa4) = *(undefined4 *)(&DAT_8032bf80 + iVar7);
  *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(param_9 + 0x9c);
  *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 0xa0);
  *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_9 + 0xa4);
  *(float *)(param_9 + 0x3c) = *(float *)(param_9 + 0x3c) - fVar1;
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
  *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x3c);
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x40);
  iVar7 = param_9;
  for (iVar11 = 0; fVar1 = FLOAT_80439968, fVar5 = FLOAT_80439950,
      iVar11 < *(char *)(param_9 + 0x13); iVar11 = iVar11 + 1) {
    pfVar10 = (float *)(*(int *)(param_9 + 0x54) + iVar12);
    if (iVar11 == 1) {
      *pfVar10 = FLOAT_8043996c;
      fVar1 = FLOAT_80439970;
      pfVar10[1] = fVar5;
      fVar4 = FLOAT_80439948;
      pfVar10[2] = fVar5;
      pfVar10[3] = fVar1;
      pfVar10[4] = fVar1;
      pfVar10[5] = fVar4;
    }
    else {
      pfVar10[2] = FLOAT_80439950;
      fVar4 = FLOAT_80439948;
      pfVar10[1] = fVar5;
      *pfVar10 = fVar5;
      pfVar10[3] = fVar1;
      pfVar10[4] = fVar1;
      pfVar10[5] = fVar4;
    }
    sVar2 = puVar8[8];
    *(short *)(pfVar10 + 8) = sVar2;
    iVar3 = DAT_803bb384;
    if (-1 < sVar2) {
      iVar9 = *(int *)(iVar7 + 0xe0);
      *(short *)((int)pfVar10 + 0x22) = *(short *)(pfVar10 + 8);
      zz_0006fb4_((double)fVar1,(double)fVar5,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                  iVar9,(int)*(short *)(pfVar10 + 8),pfVar10,in_r7,in_r8,in_r9,in_r10);
    }
    iVar12 = iVar12 + 0x24;
    puVar8 = puVar8 + 1;
    iVar7 = iVar7 + 4;
  }
  return;
}



// ==== 8011ceac  FUN_8011ceac ====

void FUN_8011ceac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
  if (((ushort)(byte)PTR_DAT_80433944[0x2d] & *(ushort *)(param_9 + 0x1e)) == 0) {
    local_1c = *(float *)(param_9 + 0x38);
    local_18 = *(undefined4 *)(param_9 + 0x3c);
    local_14 = *(undefined4 *)(param_9 + 0x40);
  }
  else {
    local_1c = *(float *)(param_9 + 0x9c);
    local_18 = *(undefined4 *)(param_9 + 0xa0);
    local_14 = *(undefined4 *)(param_9 + 0xa4);
  }
  local_28 = local_1c;
  local_24 = local_18;
  local_20 = local_14;
  gnt4_PSVECSubtract_bl(&local_28,(float *)(param_9 + 0x20),&local_28);
  gnt4_PSQUATScale_bl((double)FLOAT_80439974,&local_28,&local_28);
  uVar5 = gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_28,(float *)(param_9 + 0x20));
  iVar1 = DAT_803bb384;
  iVar3 = *(int *)(param_9 + 0x54);
  iVar4 = (int)*(short *)(iVar3 + 0x68);
  if (-1 < iVar4) {
    if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
      iVar4 = iVar4 + 1;
    }
    if (*(short *)(iVar3 + 0x6a) != iVar4) {
      iVar2 = *(int *)(param_9 + 0xe8);
      *(short *)(iVar3 + 0x6a) = (short)iVar4;
      zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,iVar2,
                  (int)(short)iVar4,iVar3,iVar4,in_r8,in_r9,in_r10);
    }
  }
  return;
}



// ==== 8011cfb8  FUN_8011cfb8 ====

void FUN_8011cfb8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  float afStack_48 [13];
  
  uVar1 = (uint)(byte)PTR_DAT_80433930[0x28];
  zz_00455fc_((float *)(&DAT_803c7714 + (char)PTR_DAT_80433930[0x28] * 0x3e4),
              (float *)(param_9 + 0x114),(float *)(param_9 + 0x20));
  iVar5 = 0;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    pfVar2 = (float *)(*(int *)(param_9 + 0x54) + iVar5);
    if (-1 < *(short *)(pfVar2 + 8)) {
      zz_00455fc_((float *)(param_9 + 0x114),afStack_48,pfVar2);
      pfVar2 = pfVar2 + 3;
      uVar6 = zz_00456a0_(afStack_48,afStack_48,pfVar2);
      zz_00076d0_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar4 + 0xe0),afStack_48,(undefined *)pfVar2,uVar1,in_r7,in_r8,in_r9,
                  in_r10);
      zz_00097b4_(*(int *)(iVar4 + 0xe0),0x44);
    }
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
  }
  return;
}



// ==== 8011d084  FUN_8011d084 ====

void FUN_8011d084(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 uVar1;
  
  uVar1 = 0x28;
  *(float *)(param_9 + 0x44) = FLOAT_80439948;
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
              *(int *)(param_9 + 0xe0),0x28,param_12,param_13,param_14,param_15,param_16);
  zz_011d0d4_(param_9,extraout_r4,uVar1,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8011d0d4  zz_011d0d4_ ====

void zz_011d0d4_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined *puVar1;
  undefined4 extraout_r4;
  float *pfVar2;
  double dVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  puVar1 = PTR_DAT_80433944;
  dVar6 = (double)*(float *)(param_1 + 0x44);
  dVar5 = (double)FLOAT_80439948;
  *(float *)(param_1 + 0x44) =
       (float)(dVar5 - (double)((*(float *)(PTR_DAT_80433944 + 0x1c) - FLOAT_80439978) /
                               FLOAT_8043997c));
  dVar3 = (double)*(float *)(param_1 + 0x44);
  if ((dVar3 <= dVar5) && (dVar5 = dVar3, dVar3 < (double)FLOAT_80439950)) {
    dVar5 = (double)FLOAT_80439950;
  }
  *(float *)(param_1 + 0x44) = (float)dVar5;
  dVar3 = (double)*(float *)(param_1 + 0x44);
  if (dVar3 != dVar6) {
    if ((double)FLOAT_80439948 == dVar3) {
      zz_0006fb4_(dVar3,dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb384,
                  *(int *)(param_1 + 0xe0),0x28,param_4,param_5,param_6,param_7,param_8);
    }
    else if ((double)FLOAT_80439948 == dVar6) {
      zz_0007c54_(dVar3,dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),puVar1,
                  param_3,param_4,param_5,param_6,param_7,param_8);
    }
    zz_0007cac_((double)*(float *)(param_1 + 0x44),*(int *)(param_1 + 0xe0));
  }
  pfVar2 = (float *)PTR_DAT_80433944;
  uVar4 = zz_0008744_((double)*(float *)(PTR_DAT_80433944 + 0x1c),dVar5,dVar6,in_f4,in_f5,in_f6,
                      in_f7,in_f8,DAT_803bb384,*(int *)(param_1 + 0xe0),PTR_DAT_80433944,param_4,
                      param_5,param_6,param_7,param_8);
  uVar4 = zz_0007c30_(uVar4,dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
                      extraout_r4,pfVar2,param_4,param_5,param_6,param_7,param_8);
  zz_0007794_(uVar4,dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
              (float *)&DAT_803d4808,(undefined *)pfVar2,param_4,param_5,param_6,param_7,param_8);
  if (FLOAT_80439980 <= *(float *)(PTR_DAT_80433944 + 0x1c)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 8011d1f0  FUN_8011d1f0 ====

void FUN_8011d1f0(int param_1)

{
  if (FLOAT_80439948 == *(float *)(param_1 + 0x44)) {
    zz_00097b4_(*(int *)(param_1 + 0xe0),1);
  }
  else {
    zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
  }
  return;
}



// ==== 8011d238  FUN_8011d238 ====

void FUN_8011d238(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 int param_11,byte *param_12,int param_13,undefined4 param_14,undefined4 param_15,
                 undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  int iVar3;
  int iVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  double dVar8;
  
  fVar2 = FLOAT_80439950;
  fVar1 = FLOAT_80439948;
  dVar8 = (double)FLOAT_80439950;
  iVar7 = 0;
  pbVar6 = &DAT_80434568;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(float *)(param_9 + 0xd4) = fVar2;
  *(float *)(param_9 + 0x44) = fVar1;
  iVar5 = param_9;
  for (iVar4 = 0; iVar4 < *(char *)(param_9 + 0x13); iVar4 = iVar4 + 1) {
    iVar3 = *(int *)(param_9 + 0x54) + iVar7;
    *(ushort *)(iVar3 + 0x20) = (ushort)*pbVar6;
    if (iVar4 == 4) {
      *(short *)(iVar3 + 0x20) = *(short *)(iVar3 + 0x20) + (short)*(char *)(param_9 + 0x12);
    }
    param_11 = (int)*(short *)(iVar3 + 0x20);
    dVar8 = (double)zz_0006fb4_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                DAT_803bb384,*(int *)(iVar5 + 0xe0),param_11,param_12,param_13,
                                param_14,param_15,param_16);
    iVar7 = iVar7 + 0x24;
    pbVar6 = pbVar6 + 1;
    iVar5 = iVar5 + 4;
    param_10 = extraout_r4;
  }
  zz_011d2f4_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8011d2f4  zz_011d2f4_ ====

/* WARNING: Removing unreachable block (ram,0x8011d834) */
/* WARNING: Removing unreachable block (ram,0x8011d304) */

void zz_011d2f4_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,byte *param_12,int param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  short sVar6;
  int iVar5;
  short sVar7;
  uint uVar8;
  uint extraout_r4;
  float *pfVar9;
  int iVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  undefined8 uVar14;
  double dVar15;
  double dVar16;
  float local_68;
  float local_64;
  float local_60;
  float afStack_5c [13];
  
  fVar2 = FLOAT_80439948;
  dVar16 = (double)*(float *)(param_9 + 0x44);
  *(float *)(param_9 + 0x44) =
       FLOAT_80439948 - (*(float *)(PTR_DAT_80433944 + 0x1c) - FLOAT_80439978) / FLOAT_8043997c;
  fVar1 = *(float *)(param_9 + 0x44);
  if ((fVar1 <= fVar2) && (fVar2 = fVar1, fVar1 < FLOAT_80439950)) {
    fVar2 = FLOAT_80439950;
  }
  *(float *)(param_9 + 0x44) = fVar2;
  if (PTR_DAT_80433944[0x1a] == '\0') {
    gnt4_PSVECSubtract_bl
              ((float *)(&DAT_803c73d0 + *(char *)(param_9 + 0x12) * 0xf9),(float *)(param_9 + 0x20)
               ,&local_68);
    dVar13 = gnt4_PSVECMag_bl(&local_68);
    if ((double)FLOAT_80439984 <= dVar13) {
      gnt4_PSVECNormalize_bl(&local_68,&local_68);
      gnt4_PSQUATScale_bl((double)FLOAT_80439984,&local_68,&local_68);
    }
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_68,(float *)(param_9 + 0x20));
    param_12 = (byte *)0x0;
    iVar3 = 3;
    param_13 = param_9;
    do {
      sVar7 = *(short *)(param_12 + *(char *)(param_9 + 0x12) * 0x3e4 + -0x7fc38be0) -
              *(short *)(param_13 + 0x70);
      if (sVar7 < 0x101) {
        sVar6 = -0x100;
        if (-0x101 < sVar7) {
          sVar6 = sVar7;
        }
      }
      else {
        sVar6 = 0x100;
      }
      param_12 = param_12 + 2;
      *(short *)(param_13 + 0x70) = *(short *)(param_13 + 0x70) + sVar6;
      param_13 = param_13 + 2;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  else {
    iVar3 = (int)*(char *)(param_9 + 0x12);
    uVar4 = (&DAT_803c73d4)[iVar3 * 0xf9];
    *(undefined4 *)(param_9 + 0x20) = (&DAT_803c73d0)[iVar3 * 0xf9];
    *(undefined4 *)(param_9 + 0x24) = uVar4;
    *(undefined4 *)(param_9 + 0x28) = (&DAT_803c73d8)[iVar3 * 0xf9];
    *(undefined4 *)(param_9 + 0x70) =
         *(undefined4 *)(&DAT_803c7420 + *(char *)(param_9 + 0x12) * 0x1f2);
    *(undefined2 *)(param_9 + 0x74) = (&DAT_803c7424)[*(char *)(param_9 + 0x12) * 0x1f2];
  }
  fVar1 = FLOAT_80439988;
  pfVar9 = (float *)(int)*(char *)(param_9 + 0x12);
  local_64 = FLOAT_80439988;
  local_68 = *(float *)(&DAT_8032c0ac + (int)pfVar9 * 4);
  if (((uint)(byte)PTR_DAT_80433944[0x18] & 1 << (int)pfVar9) == 0) {
    local_60 = FLOAT_8043998c;
  }
  else if (((uint)(byte)PTR_DAT_80433944[0x14] & 1 << (int)pfVar9) == 0) {
    local_60 = FLOAT_80439990;
  }
  else {
    local_60 = FLOAT_80439994;
  }
  if (PTR_DAT_80433944[0x1a] == '\0') {
    gnt4_PSVECSubtract_bl(&local_68,(float *)(param_9 + 100),&local_68);
    dVar13 = gnt4_PSVECMag_bl(&local_68);
    if ((double)FLOAT_80439984 <= dVar13) {
      gnt4_PSVECNormalize_bl(&local_68,&local_68);
      gnt4_PSQUATScale_bl((double)FLOAT_80439984,&local_68,&local_68);
    }
    pfVar9 = (float *)(param_9 + 100);
    gnt4_PSVECAdd_bl(pfVar9,&local_68,pfVar9);
  }
  else {
    *(float *)(param_9 + 100) = local_68;
    *(float *)(param_9 + 0x68) = fVar1;
    *(float *)(param_9 + 0x6c) = local_60;
  }
  fVar1 = FLOAT_80439948;
  if (FLOAT_80439998 <= *(float *)(PTR_DAT_80433944 + 0x1c)) {
    fVar2 = FLOAT_80439948 + *(float *)(param_9 + 0x44);
    *(float *)(param_9 + 0x5c) = fVar2;
    *(float *)(param_9 + 0x58) = fVar2;
    *(float *)(param_9 + 0x60) = fVar1;
  }
  else {
    if ((((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_9 + 0x12)) == 0) ||
       (*(float *)(param_9 + 0xd4) < FLOAT_80439948)) {
      *(undefined2 *)(param_9 + 0x1c) = 0;
    }
    else {
      sVar7 = *(short *)(param_9 + 0x1c) + 1;
      *(short *)(param_9 + 0x1c) = sVar7;
      if (0x7f < sVar7) {
        *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + -0x40;
      }
    }
    dVar13 = zz_0045238_(*(short *)(param_9 + 0x1c) << 10);
    fVar1 = FLOAT_80439960;
    if (*(short *)(param_9 + 0x1c) < 0x10) {
      fVar1 = FLOAT_8043995c;
    }
    *(float *)(param_9 + 0x58) = (float)(dVar13 * (double)fVar1 + (double)FLOAT_80439948);
    fVar2 = FLOAT_80439948;
    fVar1 = FLOAT_8043999c;
    if (*(short *)(param_9 + 0x1c) < 0x10) {
      fVar1 = FLOAT_80439954;
    }
    *(float *)(param_9 + 0x5c) = (float)(dVar13 * (double)fVar1 + (double)FLOAT_80439948);
    *(float *)(param_9 + 0x60) = fVar2;
  }
  fVar2 = FLOAT_80439950;
  fVar1 = FLOAT_80439948;
  uVar8 = (uint)(char)PTR_DAT_80433930[2];
  if ((uVar8 & 1 << (int)*(char *)(param_9 + 0x12)) == 0) {
    dVar15 = (double)*(float *)(param_9 + 0xd4);
    dVar13 = (double)FLOAT_80439950;
    if ((dVar13 < dVar15) &&
       (dVar12 = (double)FLOAT_8043994c, *(float *)(param_9 + 0xd4) = (float)(dVar15 - dVar12),
       (double)(float)(dVar15 - dVar12) < dVar13)) {
      *(float *)(param_9 + 0xd4) = fVar2;
    }
  }
  else {
    dVar15 = (double)*(float *)(param_9 + 0xd4);
    dVar13 = (double)FLOAT_80439948;
    if ((dVar15 < dVar13) &&
       (dVar12 = (double)FLOAT_8043994c, *(float *)(param_9 + 0xd4) = (float)(dVar15 + dVar12),
       dVar13 < (double)(float)(dVar15 + dVar12))) {
      *(float *)(param_9 + 0xd4) = fVar1;
    }
  }
  fVar1 = FLOAT_80439950;
  *(undefined2 *)(param_9 + 0x1e) = 7;
  if (fVar1 < *(float *)(param_9 + 0xd4)) {
    *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | 8;
  }
  fVar1 = FLOAT_80439998;
  if ((FLOAT_80439948 <= *(float *)(param_9 + 0xd4)) &&
     (*(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | 0x10,
     *(float *)(PTR_DAT_80433944 + 0x1c) < fVar1)) {
    *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | 0x20;
  }
  if ((double)*(float *)(param_9 + 0x44) != dVar16) {
    iVar11 = 0;
    iVar3 = param_9;
    for (iVar10 = 0; iVar10 < *(char *)(param_9 + 0x13); iVar10 = iVar10 + 1) {
      if (iVar10 < 4) {
        dVar13 = (double)FLOAT_80439948;
        iVar5 = *(int *)(param_9 + 0x54);
        if (dVar13 == (double)*(float *)(param_9 + 0x44)) {
          uVar14 = zz_0007794_(dVar13,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,
                               *(int *)(iVar3 + 0xe0),afStack_5c,(undefined *)pfVar9,param_12,
                               param_13,param_14,param_15,param_16);
          pfVar9 = (float *)(int)*(short *)(iVar5 + iVar11 + 0x20);
          uVar14 = zz_0006fb4_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_803bb384,*(int *)(iVar3 + 0xe0),(int)pfVar9,param_12,param_13,
                               param_14,param_15,param_16);
          zz_00076d0_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0xe0),afStack_5c,(undefined *)pfVar9,param_12,param_13,
                      param_14,param_15,param_16);
        }
        else if (dVar13 == dVar16) {
          if (iVar10 == 3) {
            zz_0007c84_(dVar13,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar3 + 0xe0),uVar8,(char *)pfVar9,param_12,param_13,param_14,
                        param_15,param_16);
          }
          else {
            zz_0007c54_(dVar13,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar3 + 0xe0),uVar8,pfVar9,param_12,param_13,param_14,param_15,
                        param_16);
          }
        }
        zz_0007cac_((double)*(float *)(param_9 + 0x44),*(int *)(iVar3 + 0xe0));
        uVar8 = extraout_r4;
      }
      iVar11 = iVar11 + 0x24;
      iVar3 = iVar3 + 4;
    }
  }
  iVar3 = *(int *)(param_9 + 0xec);
  dVar16 = (double)*(float *)(param_9 + 0xd4);
  zz_0008614_(dVar16,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,iVar3,
              pfVar9,param_12,param_13,param_14,param_15,param_16);
  zz_0007c30_(dVar16,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,iVar3,pfVar9,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8011d850  FUN_8011d850 ====

void FUN_8011d850(int param_1)

{
  float fVar1;
  bool bVar2;
  undefined *in_r6;
  int iVar3;
  undefined *in_r7;
  undefined4 *in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  double in_f2;
  double in_f3;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  undefined *puStack_68;
  undefined *puStack_64;
  undefined4 uStack_60;
  float afStack_5c [3];
  undefined *puStack_50;
  undefined *puStack_40;
  undefined4 uStack_30;
  
  if (((uint)(byte)PTR_DAT_80433944[0x18] & 1 << (int)*(char *)(param_1 + 0x12)) != 0) {
    iVar5 = 0;
    iVar8 = 0;
    pbVar6 = &DAT_80434570;
    iVar7 = param_1;
    while( true ) {
      if (*(char *)(param_1 + 0x13) <= iVar5) break;
      if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar5) != 0) {
        if ((*(float *)(PTR_DAT_80433944 + 0x1c) < FLOAT_80439998) ||
           (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_1 + 0x12)) != 0)) {
          pfVar4 = (float *)(*(int *)(param_1 + 0x54) + iVar8);
          if (iVar5 == 0) {
            zz_00455fc_((float *)&DAT_803d4808,afStack_5c,(float *)(param_1 + 0x20));
            zz_00457d4_('y',afStack_5c,afStack_5c,*(short *)(param_1 + 0x72));
            pfVar4 = afStack_5c;
            in_r6 = (undefined *)(int)*(short *)(param_1 + 0x70);
            zz_00457d4_('x',pfVar4,pfVar4,*(short *)(param_1 + 0x70));
            dVar9 = (double)gnt4_PSMTXCopy_bl(afStack_5c,(float *)(param_1 + 0x114));
          }
          else if (iVar5 == 1) {
            pfVar4 = (float *)(param_1 + 100);
            zz_00455fc_((float *)&DAT_803d4808,afStack_5c,pfVar4);
            in_f2 = (double)(float)puStack_50;
            dVar9 = (double)(float)puStack_40;
            *(undefined **)(&DAT_803d47a8 + *(char *)(param_1 + 0x12) * 0xc) = puStack_50;
            *(undefined **)(&DAT_803d47ac + *(char *)(param_1 + 0x12) * 0xc) = puStack_40;
            *(undefined4 *)(&DAT_803d47b0 + *(char *)(param_1 + 0x12) * 0xc) = uStack_30;
          }
          else if (iVar5 < 4) {
            gnt4_PSMTXMultVec_bl
                      ((float *)(param_1 + 0x114),(float *)&DAT_8032c0bc,
                       (float *)(&DAT_803d47d8 + *(char *)(param_1 + 0x12) * 0xc));
            iVar3 = *(char *)(param_1 + 0x12) * 0xc;
            gnt4_PSVECSubtract_bl
                      ((float *)(&DAT_803d47a8 + iVar3),(float *)(&DAT_803d47d8 + iVar3),
                       (float *)&puStack_68);
            fVar1 = FLOAT_80439948;
            pfVar4[4] = FLOAT_80439948;
            pfVar4[3] = fVar1;
            dVar9 = gnt4_PSVECMag_bl((float *)&puStack_68);
            pfVar4[5] = (float)(dVar9 / (double)FLOAT_804399a0);
            bVar2 = zz_0045ef4_(afStack_5c,5,&puStack_68,&DAT_802b0cb4);
            if (bVar2) {
              zz_0045ef4_(afStack_5c,4,&puStack_68,&DAT_802b0ca8);
            }
            pfVar4 = pfVar4 + 3;
            in_r7 = &DAT_803d47d8;
            iVar3 = *(char *)(param_1 + 0x12) * 0xc;
            in_r6 = &DAT_803d47d8 + iVar3;
            puStack_50 = *(undefined **)(&DAT_803d47d8 + iVar3);
            in_f2 = (double)(float)puStack_50;
            puStack_40 = *(undefined **)(&DAT_803d47dc + iVar3);
            uStack_30 = *(undefined4 *)(&DAT_803d47e0 + iVar3);
            dVar9 = (double)zz_00456a0_(afStack_5c,afStack_5c,pfVar4);
          }
          else {
            gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)&DAT_8032c0c8,pfVar4);
            iVar3 = (char)PTR_DAT_80433944[*(char *)(param_1 + 0x12) + 0x28] * 0xc;
            in_r8 = (undefined4 *)(&DAT_8032c0d4 + iVar3);
            in_r7 = (undefined *)*in_r8;
            in_r6 = *(undefined **)(&DAT_8032c0d8 + iVar3);
            uStack_60 = *(undefined4 *)(&DAT_8032c0dc + iVar3);
            puStack_68 = in_r7;
            puStack_64 = in_r6;
            gnt4_PSVECSubtract_bl((float *)&puStack_68,pfVar4,(float *)&puStack_68);
            gnt4_PSQUATScale_bl((double)(FLOAT_80439948 - *(float *)(param_1 + 0x44)),
                                (float *)&puStack_68,(float *)&puStack_68);
            gnt4_PSVECAdd_bl(pfVar4,(float *)&puStack_68,(float *)&puStack_68);
            gnt4_PSMTXTranspose_bl((float *)&DAT_803c1100,afStack_5c);
            in_f2 = (double)(float)puStack_68;
            pfVar4 = (float *)(param_1 + 0x58);
            puStack_50 = puStack_68;
            puStack_40 = puStack_64;
            uStack_30 = uStack_60;
            dVar9 = (double)zz_00456a0_(afStack_5c,afStack_5c,pfVar4);
          }
          zz_00076d0_(dVar9,in_f2,in_f3,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar7 + 0xe0),
                      afStack_5c,(undefined *)pfVar4,in_r6,in_r7,in_r8,in_r9,in_r10);
        }
        if ((iVar5 < 4) || (FLOAT_80439950 != *(float *)(PTR_DAT_80433944 + 0x1c))) {
          if (FLOAT_80439948 == *(float *)(param_1 + 0x44)) {
            zz_00097b4_(*(int *)(iVar7 + 0xe0),(uint)*pbVar6);
          }
          else {
            zz_00097b4_(*(int *)(iVar7 + 0xe0),0x44);
          }
        }
      }
      iVar8 = iVar8 + 0x24;
      iVar7 = iVar7 + 4;
      pbVar6 = pbVar6 + 1;
      iVar5 = iVar5 + 1;
    }
  }
  return;
}



// ==== 8011d858  zz_011d858_ ====

void zz_011d858_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined *param_12,undefined *param_13,undefined4 *param_14,
                undefined4 param_15,undefined4 param_16,undefined *param_17,undefined *param_18,
                undefined4 param_19)

{
  float fVar1;
  bool bVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  byte *pbVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  undefined *in_stack_00000020;
  undefined *in_stack_00000030;
  undefined4 in_stack_00000040;
  
  if (((uint)(byte)PTR_DAT_80433944[0x18] & 1 << (int)*(char *)(param_9 + 0x12)) != 0) {
    iVar5 = 0;
    iVar8 = 0;
    pbVar6 = &DAT_80434570;
    iVar7 = param_9;
    while( true ) {
      if (*(char *)(param_9 + 0x13) <= iVar5) break;
      if (((int)*(short *)(param_9 + 0x1e) & 1 << iVar5) != 0) {
        if ((*(float *)(PTR_DAT_80433944 + 0x1c) < FLOAT_80439998) ||
           (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_9 + 0x12)) != 0)) {
          pfVar4 = (float *)(*(int *)(param_9 + 0x54) + iVar8);
          if (iVar5 == 0) {
            zz_00455fc_((float *)&DAT_803d4808,(float *)&stack0x00000014,(float *)(param_9 + 0x20));
            zz_00457d4_('y',(float *)&stack0x00000014,(float *)&stack0x00000014,
                        *(short *)(param_9 + 0x72));
            pfVar4 = (float *)&stack0x00000014;
            param_12 = (undefined *)(int)*(short *)(param_9 + 0x70);
            zz_00457d4_('x',pfVar4,pfVar4,*(short *)(param_9 + 0x70));
            dVar9 = (double)gnt4_PSMTXCopy_bl((float *)&stack0x00000014,(float *)(param_9 + 0x114));
          }
          else if (iVar5 == 1) {
            pfVar4 = (float *)(param_9 + 100);
            zz_00455fc_((float *)&DAT_803d4808,(float *)&stack0x00000014,pfVar4);
            param_2 = (double)(float)in_stack_00000020;
            dVar9 = (double)(float)in_stack_00000030;
            *(undefined **)(&DAT_803d47a8 + *(char *)(param_9 + 0x12) * 0xc) = in_stack_00000020;
            *(undefined **)(&DAT_803d47ac + *(char *)(param_9 + 0x12) * 0xc) = in_stack_00000030;
            *(undefined4 *)(&DAT_803d47b0 + *(char *)(param_9 + 0x12) * 0xc) = in_stack_00000040;
          }
          else if (iVar5 < 4) {
            gnt4_PSMTXMultVec_bl
                      ((float *)(param_9 + 0x114),(float *)&DAT_8032c0bc,
                       (float *)(&DAT_803d47d8 + *(char *)(param_9 + 0x12) * 0xc));
            iVar3 = *(char *)(param_9 + 0x12) * 0xc;
            gnt4_PSVECSubtract_bl
                      ((float *)(&DAT_803d47a8 + iVar3),(float *)(&DAT_803d47d8 + iVar3),
                       (float *)&param_17);
            fVar1 = FLOAT_80439948;
            pfVar4[4] = FLOAT_80439948;
            pfVar4[3] = fVar1;
            dVar9 = gnt4_PSVECMag_bl((float *)&param_17);
            pfVar4[5] = (float)(dVar9 / (double)FLOAT_804399a0);
            bVar2 = zz_0045ef4_((float *)&stack0x00000014,5,&param_17,&DAT_802b0cb4);
            if (bVar2) {
              zz_0045ef4_((float *)&stack0x00000014,4,&param_17,&DAT_802b0ca8);
            }
            pfVar4 = pfVar4 + 3;
            param_13 = &DAT_803d47d8;
            iVar3 = *(char *)(param_9 + 0x12) * 0xc;
            param_12 = &DAT_803d47d8 + iVar3;
            in_stack_00000020 = *(undefined **)(&DAT_803d47d8 + iVar3);
            param_2 = (double)(float)in_stack_00000020;
            in_stack_00000030 = *(undefined **)(&DAT_803d47dc + iVar3);
            in_stack_00000040 = *(undefined4 *)(&DAT_803d47e0 + iVar3);
            dVar9 = (double)zz_00456a0_((float *)&stack0x00000014,(float *)&stack0x00000014,pfVar4);
          }
          else {
            gnt4_PSMTXMultVec_bl((float *)(param_9 + 0x114),(float *)&DAT_8032c0c8,pfVar4);
            iVar3 = (char)PTR_DAT_80433944[*(char *)(param_9 + 0x12) + 0x28] * 0xc;
            param_14 = (undefined4 *)(&DAT_8032c0d4 + iVar3);
            param_13 = (undefined *)*param_14;
            param_12 = *(undefined **)(&DAT_8032c0d8 + iVar3);
            param_19 = *(undefined4 *)(&DAT_8032c0dc + iVar3);
            param_17 = param_13;
            param_18 = param_12;
            gnt4_PSVECSubtract_bl((float *)&param_17,pfVar4,(float *)&param_17);
            gnt4_PSQUATScale_bl((double)(FLOAT_80439948 - *(float *)(param_9 + 0x44)),
                                (float *)&param_17,(float *)&param_17);
            gnt4_PSVECAdd_bl(pfVar4,(float *)&param_17,(float *)&param_17);
            gnt4_PSMTXTranspose_bl((float *)&DAT_803c1100,(float *)&stack0x00000014);
            param_2 = (double)(float)param_17;
            pfVar4 = (float *)(param_9 + 0x58);
            in_stack_00000020 = param_17;
            in_stack_00000030 = param_18;
            in_stack_00000040 = param_19;
            dVar9 = (double)zz_00456a0_((float *)&stack0x00000014,(float *)&stack0x00000014,pfVar4);
          }
          zz_00076d0_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0xe0),(float *)&stack0x00000014,(undefined *)pfVar4,param_12,
                      param_13,param_14,param_15,param_16);
        }
        if ((iVar5 < 4) || (FLOAT_80439950 != *(float *)(PTR_DAT_80433944 + 0x1c))) {
          if (FLOAT_80439948 == *(float *)(param_9 + 0x44)) {
            zz_00097b4_(*(int *)(iVar7 + 0xe0),(uint)*pbVar6);
          }
          else {
            zz_00097b4_(*(int *)(iVar7 + 0xe0),0x44);
          }
        }
      }
      iVar8 = iVar8 + 0x24;
      iVar7 = iVar7 + 4;
      pbVar6 = pbVar6 + 1;
      iVar5 = iVar5 + 1;
    }
  }
  return;
}



// ==== 8011dbf4  zz_011dbf4_ ====

void zz_011dbf4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  float *pfVar1;
  undefined8 uVar2;
  
  pfVar1 = (float *)0x29;
  *(float *)(param_9 + 0xd4) = FLOAT_80439950;
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
              *(int *)(param_9 + 0xe0),0x29,param_12,param_13,param_14,param_15,param_16);
  zz_00086b8_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,DAT_803bb384,*(int *)(param_9 + 0xe0),pfVar1,param_12,param_13,param_14,
              param_15,param_16);
  uVar2 = zz_0008744_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,DAT_803bb384,*(int *)(param_9 + 0xe0),pfVar1,param_12,param_13
                      ,param_14,param_15,param_16);
  zz_0007c30_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,pfVar1,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8011dc6c  zz_011dc6c_ ====

void zz_011dc6c_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  double dVar3;
  double dVar4;
  undefined8 uVar5;
  double dVar6;
  
  fVar2 = FLOAT_804399a8;
  fVar1 = FLOAT_804399a4;
  if (PTR_DAT_80433944[0x6d] == '\0') {
    dVar6 = (double)*(float *)(param_9 + 0xd4);
    dVar4 = (double)FLOAT_804399a8;
    if (dVar6 < dVar4) {
      dVar3 = (double)FLOAT_80439948;
      *(float *)(param_9 + 0xd4) = (float)(dVar6 + dVar3);
      if (dVar4 <= (double)(float)(dVar6 + dVar3)) {
        *(undefined1 *)(param_9 + 0x18) = 2;
        *(float *)(param_9 + 0xd4) = fVar2;
      }
    }
  }
  else {
    dVar6 = (double)*(float *)(param_9 + 0xd4);
    dVar4 = (double)FLOAT_804399a4;
    if (dVar6 < dVar4) {
      dVar3 = (double)FLOAT_80439948;
      *(float *)(param_9 + 0xd4) = (float)(dVar6 + dVar3);
      if (dVar4 <= (double)(float)(dVar6 + dVar3)) {
        *(float *)(param_9 + 0xd4) = fVar1;
      }
    }
  }
  zz_00086b8_((double)*(float *)(param_9 + 0xd4),dVar6,param_3,param_4,param_5,param_6,param_7,
              param_8,DAT_803bb384,*(int *)(param_9 + 0xe0),param_11,param_12,param_13,param_14,
              param_15,param_16);
  uVar5 = zz_0008744_((double)*(float *)(param_9 + 0xd4),dVar6,param_3,param_4,param_5,param_6,
                      param_7,param_8,DAT_803bb384,*(int *)(param_9 + 0xe0),param_11,param_12,
                      param_13,param_14,param_15,param_16);
  zz_0007c30_(uVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0),
              extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  if (FLOAT_80439980 <= *(float *)(PTR_DAT_80433944 + 0x1c)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 8011dd60  zz_011dd60_ ====

void zz_011dd60_(int param_1)

{
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x45);
  return;
}



// ==== 8011dd88  zz_011dd88_ ====

void zz_011dd88_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                int param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  undefined4 extraout_r4;
  int iVar4;
  int iVar5;
  short *psVar6;
  int iVar7;
  
  fVar1 = FLOAT_80439948;
  iVar7 = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  psVar6 = &DAT_8032c104;
  *(float *)(param_9 + 0x44) = fVar1;
  iVar5 = param_9;
  for (iVar4 = 0; iVar4 < *(char *)(param_9 + 0x13); iVar4 = iVar4 + 1) {
    puVar3 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar7);
    *(short *)(puVar3 + 8) = psVar6[1];
    uVar2 = *(undefined4 *)(psVar6 + 4);
    *puVar3 = *(undefined4 *)(psVar6 + 2);
    puVar3[1] = uVar2;
    puVar3[2] = *(undefined4 *)(psVar6 + 6);
    param_11 = (int)*psVar6;
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb384,*(int *)(iVar5 + 0xe0),param_11,param_12,param_13,param_14,
                          param_15,param_16);
    iVar7 = iVar7 + 0x24;
    psVar6 = psVar6 + 8;
    iVar5 = iVar5 + 4;
    param_10 = extraout_r4;
  }
  zz_011de3c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8011de3c  zz_011de3c_ ====

/* WARNING: Removing unreachable block (ram,0x8011dfd8) */
/* WARNING: Removing unreachable block (ram,0x8011dfd0) */
/* WARNING: Removing unreachable block (ram,0x8011de54) */
/* WARNING: Removing unreachable block (ram,0x8011de4c) */

void zz_011de3c_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  short sVar3;
  undefined *puVar4;
  undefined *extraout_r4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  
  fVar2 = FLOAT_80439948;
  puVar4 = PTR_DAT_80433944;
  dVar9 = (double)*(float *)(param_9 + 0x44);
  *(float *)(param_9 + 0x44) =
       FLOAT_80439948 - (*(float *)(PTR_DAT_80433944 + 0x1c) - FLOAT_80439978) / FLOAT_8043997c;
  fVar1 = *(float *)(param_9 + 0x44);
  if ((fVar1 <= fVar2) && (fVar2 = fVar1, fVar1 < FLOAT_80439950)) {
    fVar2 = FLOAT_80439950;
  }
  *(float *)(param_9 + 0x44) = fVar2;
  if (*(float *)(PTR_DAT_80433944 + 0x1c) < FLOAT_804399ac) {
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  else {
    sVar3 = *(short *)(param_9 + 0x1c) + 1;
    *(short *)(param_9 + 0x1c) = sVar3;
    if (0x7f < sVar3) {
      *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + -0x40;
    }
  }
  dVar7 = zz_0045238_(*(short *)(param_9 + 0x1c) << 10);
  fVar1 = FLOAT_8043999c;
  if (*(short *)(param_9 + 0x1c) < 0x10) {
    fVar1 = FLOAT_80439954;
  }
  dVar8 = (double)fVar1;
  *(float *)(param_9 + 0x58) = (float)(dVar7 * dVar8 + (double)FLOAT_80439948);
  fVar2 = FLOAT_80439948;
  fVar1 = FLOAT_80439960;
  if (*(short *)(param_9 + 0x1c) < 0x10) {
    fVar1 = FLOAT_8043995c;
  }
  dVar10 = (double)FLOAT_80439948;
  *(float *)(param_9 + 0x5c) = (float)(dVar7 * (double)fVar1 + dVar10);
  *(float *)(param_9 + 0x60) = fVar2;
  if ((double)*(float *)(param_9 + 0x44) != dVar9) {
    iVar6 = param_9;
    for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
      if ((iVar5 == 0) && (dVar10 == dVar9)) {
        zz_0007c54_(dVar7,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar6 + 0xe0),puVar4,param_11,param_12,param_13,param_14,param_15,
                    param_16);
      }
      dVar7 = (double)zz_0007cac_((double)*(float *)(param_9 + 0x44),*(int *)(iVar6 + 0xe0));
      iVar6 = iVar6 + 4;
      puVar4 = extraout_r4;
    }
  }
  if (FLOAT_80439980 <= *(float *)(PTR_DAT_80433944 + 0x1c)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 8011dffc  FUN_8011dffc ====

/* WARNING: Removing unreachable block (ram,0x8011e0b0) */
/* WARNING: Removing unreachable block (ram,0x8011e00c) */

void FUN_8011dffc(int param_1,undefined4 param_2,float *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar8;
  float afStack_58 [13];
  
  dVar8 = (double)FLOAT_80439948;
  iVar4 = 0;
  iVar3 = param_1;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
    dVar6 = (double)pfVar1[1];
    dVar7 = (double)pfVar1[2];
    uVar5 = gnt4_PSMTXTrans_bl((double)*pfVar1,dVar6,dVar7,afStack_58);
    if (iVar2 == 3) {
      param_3 = (float *)(param_1 + 0x58);
      uVar5 = zz_00456a0_(afStack_58,afStack_58,param_3);
    }
    zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_58,
                (undefined *)param_3,param_4,param_5,param_6,param_7,param_8);
    if (dVar8 == (double)*(float *)(param_1 + 0x44)) {
      zz_00097b4_(*(int *)(iVar3 + 0xe0),(int)*(short *)(pfVar1 + 8));
    }
    else {
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
    }
    iVar4 = iVar4 + 0x24;
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 8011e0cc  FUN_8011e0cc ====

/* WARNING: Removing unreachable block (ram,0x8011e22c) */
/* WARNING: Removing unreachable block (ram,0x8011e0dc) */

void FUN_8011e0cc(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar7;
  int iVar8;
  undefined2 *puVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  
  fVar3 = FLOAT_804399b0;
  fVar2 = FLOAT_80439950;
  dVar11 = (double)FLOAT_80439950;
  iVar6 = 0;
  *(float *)(param_9 + 0x20) = FLOAT_80439950;
  fVar4 = FLOAT_804399b4;
  iVar5 = 4;
  dVar10 = (double)FLOAT_804399b4;
  *(float *)(param_9 + 0x24) = fVar3;
  fVar3 = FLOAT_804399b8;
  *(float *)(param_9 + 0x28) = fVar4;
  *(float *)(param_9 + 0xd4) = fVar2;
  *(float *)(param_9 + 0xd8) = fVar3;
  *(undefined2 *)(param_9 + 0x1e) = 0;
  do {
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar6) != 0) {
      *(ushort *)(param_9 + 0x1e) =
           *(ushort *)(param_9 + 0x1e) | (ushort)(1 << (int)(char)PTR_DAT_80433944[iVar6 + 0x24]);
    }
    iVar6 = iVar6 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  dVar12 = (double)FLOAT_804399bc;
  iVar8 = 0;
  puVar9 = (undefined2 *)&DAT_80434578;
  iVar5 = param_9;
  for (uVar7 = 0; (int)uVar7 < (int)*(char *)(param_9 + 0x13); uVar7 = uVar7 + 1) {
    *(undefined2 *)(*(int *)(param_9 + 0x54) + iVar8 + 0x20) = *puVar9;
    zz_0006fb4_(dVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                *(int *)(iVar5 + 0xe0),0xd,iVar6,in_r7,in_r8,in_r9,in_r10);
    uVar1 = uVar7 & 1;
    dVar11 = (double)(longlong)(int)(dVar12 * (double)(float)(&DAT_8032c144)[uVar1 * 3]);
    iVar6 = (int)(dVar12 * (double)(float)(&DAT_8032c14c)[uVar1 * 3]);
    dVar10 = (double)zz_0007cd0_(*(int *)(iVar5 + 0xe0),
                                 (int)(dVar12 * (double)(float)(&DAT_8032c144)[uVar1 * 3]),
                                 (int)(dVar12 * (double)(float)(&DAT_8032c148)[uVar1 * 3]),iVar6);
    puVar9 = puVar9 + 1;
    iVar8 = iVar8 + 0x24;
    iVar5 = iVar5 + 4;
  }
  zz_011e248_(param_9);
  return;
}



// ==== 8011e248  zz_011e248_ ====

void zz_011e248_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  
  fVar1 = *(float *)(param_1 + 0xd4) + FLOAT_80439948;
  *(float *)(param_1 + 0xd4) = fVar1;
  fVar2 = FLOAT_804399b8;
  if (*(float *)(param_1 + 0xd8) < fVar1) {
    if ((PTR_DAT_80433944[0x2e] & 4) == 0) {
      iVar4 = 0;
      iVar3 = 4;
      *(float *)(param_1 + 0xd4) = FLOAT_80439950;
      *(float *)(param_1 + 0xd8) = fVar2;
      *(undefined2 *)(param_1 + 0x1e) = 0;
      do {
        if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar4) != 0) {
          *(ushort *)(param_1 + 0x1e) =
               *(ushort *)(param_1 + 0x1e) |
               (ushort)(1 << (int)(char)PTR_DAT_80433944[iVar4 + 0x24]);
        }
        iVar4 = iVar4 + 1;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    else {
      *(float *)(param_1 + 0xd4) = FLOAT_804399c0 * *(float *)(param_1 + 0xd8);
    }
  }
  fVar2 = FLOAT_80439980;
  fVar1 = FLOAT_804399c4 +
          (FLOAT_804399c8 * *(float *)(param_1 + 0xd4)) / *(float *)(param_1 + 0xd8);
  *(float *)(param_1 + 0x60) = fVar1;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  if (fVar2 <= *(float *)(PTR_DAT_80433944 + 0x1c)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    return;
  }
  return;
}



// ==== 8011e340  FUN_8011e340 ====

void FUN_8011e340(int param_1)

{
  short sVar1;
  float *pfVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  if (*(float *)(param_1 + 0xd4) < FLOAT_804399c0 * *(float *)(param_1 + 0xd8)) {
    dVar8 = (double)*(float *)(param_1 + 0x24);
    dVar9 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar8,dVar9,(float *)(param_1 + 0x114));
    zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
    iVar4 = 0;
    iVar6 = 0;
    iVar5 = param_1;
    while( true ) {
      if (*(char *)(param_1 + 0x13) <= iVar4) break;
      if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar4) != 0) {
        pfVar2 = afStack_48;
        sVar1 = *(short *)(*(int *)(param_1 + 0x54) + iVar6 + 0x20);
        iVar3 = (int)sVar1;
        uVar7 = zz_00457d4_('z',(float *)(param_1 + 0x114),pfVar2,sVar1);
        zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),
                    afStack_48,(undefined *)pfVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
        zz_00097b4_(*(int *)(iVar5 + 0xe0),0x44);
      }
      iVar6 = iVar6 + 0x24;
      iVar5 = iVar5 + 4;
      iVar4 = iVar4 + 1;
    }
  }
  return;
}



// ==== 8011e418  FUN_8011e418 ====

void FUN_8011e418(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  fVar1 = FLOAT_80439948;
  iVar3 = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(float *)(param_9 + 0x44) = fVar1;
  for (iVar4 = 0; iVar4 < *(char *)(param_9 + 0x13); iVar4 = iVar4 + 1) {
    iVar2 = iVar3 + 0x20;
    iVar3 = iVar3 + 0x24;
    *(undefined2 *)(*(int *)(param_9 + 0x54) + iVar2) = 0xffff;
  }
  zz_011e478_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8011e478  zz_011e478_ ====

/* WARNING: Removing unreachable block (ram,0x8011e754) */
/* WARNING: Removing unreachable block (ram,0x8011e74c) */
/* WARNING: Removing unreachable block (ram,0x8011e744) */
/* WARNING: Removing unreachable block (ram,0x8011e73c) */
/* WARNING: Removing unreachable block (ram,0x8011e4a0) */
/* WARNING: Removing unreachable block (ram,0x8011e498) */
/* WARNING: Removing unreachable block (ram,0x8011e490) */
/* WARNING: Removing unreachable block (ram,0x8011e488) */

void zz_011e478_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  float local_98;
  float local_94;
  float local_90;
  double local_88;
  longlong local_80;
  longlong local_78;
  
  dVar14 = (double)*(float *)(param_9 + 0x44);
  if ((PTR_DAT_80433944[0x2e] & 4) == 0) {
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  else {
    *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
  }
  dVar11 = (double)FLOAT_80439948;
  *(float *)(param_9 + 0x44) =
       (float)(dVar11 - (double)((*(float *)(PTR_DAT_80433944 + 0x1c) - FLOAT_804399cc) /
                                FLOAT_804399d0));
  dVar9 = (double)*(float *)(param_9 + 0x44);
  if ((dVar9 <= dVar11) && (dVar11 = dVar9, dVar9 < (double)FLOAT_80439950)) {
    dVar11 = (double)FLOAT_80439950;
  }
  *(float *)(param_9 + 0x44) = (float)dVar11;
  dVar9 = (double)FLOAT_804399d4;
  dVar12 = (double)FLOAT_80439978;
  dVar13 = (double)FLOAT_804399bc;
  iVar8 = 0;
  pbVar7 = &DAT_80434580;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    pfVar4 = (float *)(*(int *)(param_9 + 0x54) + iVar8);
    local_90 = (float)dVar9;
    local_98 = *(float *)(&DAT_8032c15c + (char)PTR_DAT_80433944[iVar5 + 0x28] * 8);
    dVar10 = (double)local_98;
    local_94 = *(float *)(&DAT_8032c160 + (char)PTR_DAT_80433944[iVar5 + 0x28] * 8);
    if (dVar12 <= (double)*(float *)(PTR_DAT_80433944 + 0x1c)) {
      gnt4_PSVECSubtract_bl(&local_98,pfVar4,&local_98);
      dVar10 = gnt4_PSVECMag_bl(&local_98);
      if ((double)FLOAT_804399d8 <= dVar10) {
        gnt4_PSVECNormalize_bl(&local_98,&local_98);
        gnt4_PSQUATScale_bl((double)FLOAT_804399d8,&local_98,&local_98);
      }
      dVar10 = (double)gnt4_PSVECAdd_bl(pfVar4,&local_98,pfVar4);
    }
    else {
      *pfVar4 = local_98;
      pfVar4[1] = local_94;
      pfVar4[2] = local_90;
    }
    iVar1 = DAT_803bb384;
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar5) == 0) {
      if ((PTR_DAT_80433944[(char)PTR_DAT_80433944[iVar5 + 0x28] + 0x20] & 0x40) == 0) {
        uVar3 = 0x23;
      }
      else {
        uVar3 = 0x24;
      }
    }
    else {
      uVar3 = (uint)*pbVar7;
    }
    if ((int)*(short *)(pfVar4 + 8) != uVar3) {
      iVar2 = *(int *)(iVar6 + 0xe0);
      *(short *)(pfVar4 + 8) = (short)uVar3;
      zz_0006fb4_(dVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,iVar2,
                  (int)(short)uVar3,uVar3,in_r7,in_r8,in_r9,in_r10);
    }
    if ((double)*(float *)(param_9 + 0x44) != dVar14) {
      zz_0007cac_((double)*(float *)(param_9 + 0x44),*(int *)(iVar6 + 0xe0));
    }
    iVar1 = (((byte)PTR_DAT_80433944[iVar5 + 0x28] & 1) + 1) *
            ((uint)(int)*(short *)(param_9 + 0x1c) >> 2 & 1) * 0xc;
    dVar11 = (double)(longlong)(int)(dVar13 * (double)*(float *)(&DAT_8032c17c + iVar1));
    local_80 = (longlong)(int)(dVar13 * (double)*(float *)(&DAT_8032c180 + iVar1));
    local_78 = (longlong)(int)(dVar13 * (double)*(float *)(&DAT_8032c184 + iVar1));
    local_88 = dVar11;
    zz_0007cd0_(*(int *)(iVar6 + 0xe0),(int)(dVar13 * (double)*(float *)(&DAT_8032c17c + iVar1)),
                (int)(dVar13 * (double)*(float *)(&DAT_8032c180 + iVar1)),
                (int)(dVar13 * (double)*(float *)(&DAT_8032c184 + iVar1)));
    iVar8 = iVar8 + 0x24;
    pbVar7 = pbVar7 + 1;
    iVar6 = iVar6 + 4;
  }
  if (FLOAT_80439980 <= *(float *)(PTR_DAT_80433944 + 0x1c)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 8011e770  FUN_8011e770 ====

void FUN_8011e770(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [14];
  
  if (FLOAT_80439998 <= *(float *)(PTR_DAT_80433944 + 0x1c)) {
    iVar4 = 0;
    iVar3 = param_1;
    for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
      pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
      dVar6 = (double)pfVar1[1];
      dVar7 = (double)pfVar1[2];
      uVar5 = gnt4_PSMTXTrans_bl((double)*pfVar1,dVar6,dVar7,afStack_48);
      zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_48,
                  param_3,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
      iVar4 = iVar4 + 0x24;
      iVar3 = iVar3 + 4;
    }
  }
  return;
}



// ==== 8011e828  FUN_8011e828 ====

void FUN_8011e828(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  
  fVar1 = FLOAT_80439950;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(float *)(param_9 + 0xd4) = fVar1;
  fVar1 = FLOAT_804399c4;
  if ((*(byte *)(param_9 + 0x12) & 0xc) != 0) {
    fVar1 = FLOAT_8043994c;
  }
  *(float *)(param_9 + 0xd8) = fVar1;
  *(byte *)(param_9 + 0x12) = *(byte *)(param_9 + 0x12) & 3;
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
              *(int *)(param_9 + 0xe0),0x2f,param_12,param_13,param_14,param_15,param_16);
  zz_011e8a8_(param_9);
  return;
}



// ==== 8011e8a8  zz_011e8a8_ ====

/* WARNING: Removing unreachable block (ram,0x8011ea0c) */
/* WARNING: Removing unreachable block (ram,0x8011e8b8) */

void zz_011e8a8_(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  double dVar6;
  
  uVar4 = zz_00055fc_();
  fVar1 = FLOAT_80439948;
  dVar6 = (double)((float)((double)CONCAT44(0x43300000,uVar4 & 0xff) - DOUBLE_804399e8) /
                  FLOAT_804399dc);
  if (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_1 + 0x12)) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    fVar3 = *(float *)(param_1 + 0xd4) + *(float *)(param_1 + 0xd8);
    *(float *)(param_1 + 0xd4) = fVar3;
    if (fVar1 <= fVar3) {
      *(undefined1 *)(param_1 + 0x18) = 2;
    }
  }
  iVar5 = *(char *)(param_1 + 0x12) * 0xc;
  gnt4_PSVECSubtract_bl
            ((float *)(&DAT_803d47a8 + iVar5),(float *)(&DAT_803d47d8 + iVar5),
             (float *)(param_1 + 0x20));
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xd4),(float *)(param_1 + 0x20),
                      (float *)(param_1 + 0x20));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),
                   (float *)(&DAT_803d47d8 + *(char *)(param_1 + 0x12) * 0xc),
                   (float *)(param_1 + 0x20));
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  fVar1 = FLOAT_804399e4;
  if ((*(ushort *)(param_1 + 0x1c) & 1) != 0) {
    fVar1 = FLOAT_804399e0;
  }
  *(float *)(param_1 + 0xb4) = (float)(dVar6 + (double)fVar1);
  uVar2 = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  *(undefined4 *)(param_1 + 0x5c) = uVar2;
  *(undefined4 *)(param_1 + 0x58) = uVar2;
  uVar4 = zz_00055fc_();
  *(short *)(param_1 + 0x70) = (short)(uVar4 << 8);
  uVar4 = zz_00055fc_();
  *(short *)(param_1 + 0x72) = (short)(uVar4 << 8);
  uVar4 = zz_00055fc_();
  *(short *)(param_1 + 0x74) = (short)(uVar4 << 8);
  return;
}



// ==== 8011ea28  FUN_8011ea28 ====

void FUN_8011ea28(int param_1)

{
  float *pfVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar3;
  double dVar4;
  double dVar5;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  dVar4 = (double)*(float *)(param_1 + 0x24);
  dVar5 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar4,dVar5,(float *)(param_1 + 0x114));
  zz_00457d4_('z',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x74));
  zz_00457d4_('y',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x72));
  iVar2 = (int)*(short *)(param_1 + 0x70);
  zz_00457d4_('x',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x70));
  pfVar1 = (float *)(param_1 + 0x58);
  uVar3 = zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),pfVar1);
  zz_00076d0_(uVar3,dVar4,dVar5,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
              (float *)(param_1 + 0x114),(undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x45);
  return;
}



// ==== 8011eac8  FUN_8011eac8 ====

/* WARNING: Removing unreachable block (ram,0x8011ec04) */
/* WARNING: Removing unreachable block (ram,0x8011ead8) */

void FUN_8011eac8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int iVar4;
  undefined4 *puVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  double dVar10;
  
  fVar1 = FLOAT_80439950;
  *(float *)(param_9 + 0x44) = FLOAT_80439950;
  dVar10 = DOUBLE_804399f0;
  iVar4 = *(char *)(param_9 + 0x12) * 0x14;
  puVar5 = (undefined4 *)(&DAT_8032c1a0 + iVar4);
  iVar8 = 0;
  *(short *)(param_9 + 0x1c) = (short)(char)PTR_DAT_80433944[0x6c];
  *(float *)(param_9 + 0xd4) = fVar1;
  *(float *)(param_9 + 0xd8) = fVar1;
  *(short *)(param_9 + 0x1e) = (short)*puVar5;
  uVar2 = *(undefined4 *)(&DAT_8032c1ac + iVar4);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(&DAT_8032c1a8 + iVar4);
  *(undefined4 *)(param_9 + 0x24) = uVar2;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(&DAT_8032c1b0 + iVar4);
  iVar4 = param_9;
  for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
    iVar3 = *(int *)(param_9 + 0x54);
    pfVar6 = (float *)(int)*(short *)(puVar5 + 1);
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                *(int *)(iVar4 + 0xe0),(int)pfVar6,param_12,param_13,param_14,param_15,param_16);
    uVar9 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                         (int)*(short *)(param_9 + 0x1c) ^
                                                         0x80000000) - dVar10),param_2,param_3,
                        param_4,param_5,param_6,param_7,param_8,DAT_803bb384,*(int *)(iVar4 + 0xe0),
                        pfVar6,param_12,param_13,param_14,param_15,param_16);
    uVar9 = zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar4 + 0xe0),extraout_r4,pfVar6,param_12,param_13,param_14,
                        param_15,param_16);
    zz_0007d40_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar4 + 0xe0)
                ,extraout_r4_00,pfVar6,param_12,param_13,param_14,param_15,param_16);
    uVar9 = zz_0008744_((double)(*(float *)(param_9 + 0xd4) + *(float *)(param_9 + 0xd8)),param_2,
                        param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                        *(int *)(iVar4 + 0xe0),pfVar6,param_12,param_13,param_14,param_15,param_16);
    uVar9 = zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar4 + 0xe0),extraout_r4_01,pfVar6,param_12,param_13,param_14,
                        param_15,param_16);
    zz_0007bb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar4 + 0xe0)
                ,(undefined4 *)(iVar3 + iVar8 + 0xc),pfVar6,param_12,param_13,param_14,param_15,
                param_16);
    param_1 = zz_0007cac_((double)*(float *)(param_9 + 0x44),*(int *)(iVar4 + 0xe0));
    iVar8 = iVar8 + 0x24;
    puVar5 = (undefined4 *)((int)puVar5 + 2);
    iVar4 = iVar4 + 4;
  }
  return;
}



// ==== 8011ec20  FUN_8011ec20 ====

/* WARNING: Removing unreachable block (ram,0x8011ee64) */
/* WARNING: Removing unreachable block (ram,0x8011ee5c) */
/* WARNING: Removing unreachable block (ram,0x8011ec38) */
/* WARNING: Removing unreachable block (ram,0x8011ec30) */

void FUN_8011ec20(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int iVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  
  fVar3 = FLOAT_804399f8;
  fVar2 = FLOAT_80439950;
  dVar11 = (double)*(float *)(param_9 + 0xd4);
  dVar13 = (double)(float)(dVar11 - (double)*(float *)(param_9 + 0xd8));
  sVar1 = *(short *)(param_9 + 0x1c);
  dVar12 = (double)*(float *)(param_9 + 0x44);
  if (((ushort)(byte)PTR_DAT_80433944[0x2d] & *(ushort *)(param_9 + 0x1e)) == 0) {
    dVar9 = (double)FLOAT_8043994c;
    *(float *)(param_9 + 0x44) = (float)(dVar12 - dVar9);
    if ((float)(dVar12 - dVar9) <= fVar2) {
      *(float *)(param_9 + 0x44) = fVar2;
      *(float *)(param_9 + 0xd4) = fVar2;
    }
  }
  else {
    dVar9 = (double)FLOAT_804399f8;
    if ((dVar11 < dVar9) &&
       (dVar8 = (double)FLOAT_80439948, *(float *)(param_9 + 0xd4) = (float)(dVar11 + dVar8),
       dVar9 <= (double)(float)(dVar11 + dVar8))) {
      *(float *)(param_9 + 0xd4) = fVar3;
    }
    *(float *)(param_9 + 0x44) = FLOAT_80439948;
  }
  if (*(char *)(param_9 + 0x12) == '\0') {
    if ((FLOAT_804399fc == *(float *)(param_9 + 0xd8)) &&
       ((int)(char)PTR_DAT_80433944[0x6c] != (int)*(short *)(param_9 + 0x1c))) {
      *(short *)(param_9 + 0x1c) = (short)(char)PTR_DAT_80433944[0x6c];
    }
    fVar3 = FLOAT_804399fc;
    fVar2 = FLOAT_80439950;
    if ((PTR_DAT_80433944[0x6d] == '\0') && (PTR_DAT_80433944[0x6f] == '\0')) {
      dVar11 = (double)*(float *)(param_9 + 0xd8);
      dVar9 = (double)FLOAT_80439950;
      if ((dVar9 < dVar11) &&
         (dVar8 = (double)FLOAT_80439948, *(float *)(param_9 + 0xd8) = (float)(dVar11 - dVar8),
         (double)(float)(dVar11 - dVar8) <= dVar9)) {
        *(float *)(param_9 + 0xd8) = fVar2;
      }
    }
    else {
      dVar11 = (double)*(float *)(param_9 + 0xd8);
      dVar9 = (double)FLOAT_804399fc;
      if ((dVar11 < dVar9) &&
         (dVar8 = (double)FLOAT_80439948, *(float *)(param_9 + 0xd8) = (float)(dVar11 + dVar8),
         dVar9 <= (double)(float)(dVar11 + dVar8))) {
        *(float *)(param_9 + 0xd8) = fVar3;
      }
    }
  }
  iVar7 = 0;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    iVar4 = *(int *)(param_9 + 0x54);
    if ((int)*(short *)(param_9 + 0x1c) != (int)sVar1) {
      uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                            (int)*(short *)(param_9 + 0x1c) ^
                                                            0x80000000) - DOUBLE_804399f0),dVar11,
                           param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                           *(int *)(iVar6 + 0xe0),param_11,param_12,param_13,param_14,param_15,
                           param_16);
      uVar10 = zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(iVar6 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                           param_15,param_16);
      zz_0007d40_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar6 + 0xe0),extraout_r4_00,param_11,param_12,param_13,param_14,param_15
                  ,param_16);
    }
    dVar9 = (double)(*(float *)(param_9 + 0xd4) + *(float *)(param_9 + 0xd8));
    if (dVar13 != dVar9) {
      uVar10 = zz_0008744_(dVar9,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384
                           ,*(int *)(iVar6 + 0xe0),param_11,param_12,param_13,param_14,param_15,
                           param_16);
      uVar10 = zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(iVar6 + 0xe0),extraout_r4_01,param_11,param_12,param_13,param_14
                           ,param_15,param_16);
      zz_0007bb4_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar6 + 0xe0),(undefined4 *)(iVar4 + iVar7 + 0xc),param_11,param_12,
                  param_13,param_14,param_15,param_16);
    }
    if ((double)*(float *)(param_9 + 0x44) != dVar12) {
      zz_0007cac_((double)*(float *)(param_9 + 0x44),*(int *)(iVar6 + 0xe0));
    }
    iVar7 = iVar7 + 0x24;
    iVar6 = iVar6 + 4;
  }
  if (FLOAT_80439980 <= *(float *)(PTR_DAT_80433944 + 0x1c)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 8011ee80  FUN_8011ee80 ====

void FUN_8011ee80(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  float afStack_48 [14];
  
  if ((FLOAT_80439950 < *(float *)(param_9 + 0xd4)) && (FLOAT_80439950 < *(float *)(param_9 + 0x44))
     ) {
    zz_00455fc_((float *)(&DAT_803c7714 + (char)PTR_DAT_80433930[0x28] * 0x3e4),
                (float *)(param_9 + 0x114),(float *)(param_9 + 0x20));
    iVar4 = 0;
    iVar3 = param_9;
    for (iVar2 = 0; iVar2 < *(char *)(param_9 + 0x13); iVar2 = iVar2 + 1) {
      pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar4 + 0xc);
      uVar5 = zz_00456a0_((float *)(param_9 + 0x114),afStack_48,pfVar1);
      zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar3 + 0xe0),afStack_48,(undefined *)pfVar1,param_12,param_13,param_14,
                  param_15,param_16);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
      iVar4 = iVar4 + 0x24;
      iVar3 = iVar3 + 4;
    }
  }
  return;
}



// ==== 8011ef64  FUN_8011ef64 ====

/* WARNING: Removing unreachable block (ram,0x8011f0b4) */
/* WARNING: Removing unreachable block (ram,0x8011f0ac) */
/* WARNING: Removing unreachable block (ram,0x8011f0a4) */
/* WARNING: Removing unreachable block (ram,0x8011f09c) */
/* WARNING: Removing unreachable block (ram,0x8011f094) */
/* WARNING: Removing unreachable block (ram,0x8011ef94) */
/* WARNING: Removing unreachable block (ram,0x8011ef8c) */
/* WARNING: Removing unreachable block (ram,0x8011ef84) */
/* WARNING: Removing unreachable block (ram,0x8011ef7c) */
/* WARNING: Removing unreachable block (ram,0x8011ef74) */

void FUN_8011ef64(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float *pfVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar3;
  uint uVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  undefined8 uVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  
  *(float *)(param_9 + 0xd4) = FLOAT_80439950;
  pfVar6 = (float *)&DAT_8032c1c8;
  dVar9 = (double)FLOAT_80439a00;
  dVar10 = (double)FLOAT_80439a04;
  dVar11 = (double)FLOAT_80439a08;
  dVar12 = (double)FLOAT_80439a0c;
  iVar7 = 0;
  iVar5 = param_9;
  dVar13 = DOUBLE_804399f0;
  for (uVar4 = 0; (int)uVar4 < (int)*(char *)(param_9 + 0x13); uVar4 = uVar4 + 1) {
    pfVar3 = (float *)0x2a;
    pfVar2 = (float *)(*(int *)(param_9 + 0x54) + iVar7);
    *(short *)(pfVar2 + 8) = (short)(int)(dVar9 * (double)*pfVar6);
    fVar1 = pfVar6[2];
    *pfVar2 = pfVar6[1];
    pfVar2[1] = fVar1;
    pfVar2[2] = pfVar6[3];
    pfVar2[3] = pfVar2[1];
    pfVar2[4] = (float)dVar10;
    pfVar2[5] = (float)dVar11;
    pfVar2[1] = (float)((double)pfVar2[1] + dVar12);
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                *(int *)(iVar5 + 0xe0),0x2a,param_12,param_13,param_14,param_15,param_16);
    uVar8 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - dVar13),
                        param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                        *(int *)(iVar5 + 0xe0),pfVar3,param_12,param_13,param_14,param_15,param_16);
    uVar8 = zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar5 + 0xe0),extraout_r4,pfVar3,param_12,param_13,param_14,
                        param_15,param_16);
    param_1 = zz_0007d40_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar5 + 0xe0),extraout_r4_00,pfVar3,param_12,param_13,param_14,
                          param_15,param_16);
    iVar7 = iVar7 + 0x24;
    pfVar6 = pfVar6 + 4;
    iVar5 = iVar5 + 4;
  }
  return;
}



// ==== 8011f0d0  FUN_8011f0d0 ====

void FUN_8011f0d0(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  undefined4 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  undefined8 uVar8;
  double dVar9;
  
  fVar1 = FLOAT_80439a10;
  dVar7 = (double)FLOAT_80439970;
  dVar9 = (double)*(float *)(param_9 + 0xd4);
  *(float *)(param_9 + 0xd4) = (float)(dVar9 + dVar7);
  if (fVar1 <= (float)(dVar9 + dVar7)) {
    *(float *)(param_9 + 0xd4) = *(float *)(param_9 + 0xd4) - fVar1;
  }
  iVar4 = 0;
  iVar6 = 0;
  iVar5 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar4) break;
    if (((uint)(byte)PTR_DAT_80433944[0x91] & 1 << iVar4) != 0) {
      puVar3 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar6);
      if ((float)puVar3[1] != (float)puVar3[3]) {
        fVar1 = (float)puVar3[1] + (float)puVar3[4];
        puVar3[1] = fVar1;
        if ((float)puVar3[3] < fVar1) {
          puVar3[4] = (float)puVar3[4] + (float)puVar3[5];
        }
        else {
          puVar3[1] = puVar3[3];
          param_11 = (float *)*puVar3;
          uVar2 = puVar3[1];
          *(float **)(param_9 + 0x20) = param_11;
          *(undefined4 *)(param_9 + 0x24) = uVar2;
          *(undefined4 *)(param_9 + 0x28) = puVar3[2];
          zz_00f03c0_(param_9,0x12);
        }
      }
      uVar8 = zz_0008744_((double)(float)((double)CONCAT44(0x43300000,
                                                           (int)*(float *)(param_9 + 0xd4) ^
                                                           0x80000000) - DOUBLE_804399f0),dVar9,
                          param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                          *(int *)(iVar5 + 0xe0),param_11,puVar3,param_13,param_14,param_15,param_16
                         );
      zz_0007c30_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar5 + 0xe0)
                  ,extraout_r4,param_11,puVar3,param_13,param_14,param_15,param_16);
    }
    iVar6 = iVar6 + 0x24;
    iVar5 = iVar5 + 4;
    iVar4 = iVar4 + 1;
  }
  if (FLOAT_80439980 <= *(float *)(PTR_DAT_80433944 + 0x1c)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 8011f240  FUN_8011f240 ====

void FUN_8011f240(int param_1)

{
  float *pfVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  iVar4 = 0;
  iVar6 = 0;
  iVar5 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar4) break;
    if (((uint)(byte)PTR_DAT_80433944[0x91] & 1 << iVar4) != 0) {
      pfVar3 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
      dVar8 = (double)pfVar3[1];
      dVar9 = (double)pfVar3[2];
      gnt4_PSMTXTrans_bl((double)*pfVar3,dVar8,dVar9,afStack_48);
      pfVar1 = afStack_48;
      iVar2 = (int)*(short *)(pfVar3 + 8);
      uVar7 = zz_00457d4_('y',pfVar1,pfVar1,*(short *)(pfVar3 + 8));
      zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),afStack_48,
                  (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
      zz_00097b4_(*(int *)(iVar5 + 0xe0),1);
    }
    iVar6 = iVar6 + 0x24;
    iVar5 = iVar5 + 4;
    iVar4 = iVar4 + 1;
  }
  return;
}



// ==== 8011f2f4  FUN_8011f2f4 ====

/* WARNING: Removing unreachable block (ram,0x8011f3c8) */
/* WARNING: Removing unreachable block (ram,0x8011f304) */

void FUN_8011f2f4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 extraout_r4;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  
  fVar1 = FLOAT_80439950;
  dVar9 = (double)FLOAT_80439950;
  uVar3 = 0x80330000;
  *(float *)(param_9 + 0xb4) = FLOAT_80439950;
  fVar2 = FLOAT_80439a14;
  puVar7 = &DAT_8032c248;
  *(float *)(param_9 + 0xd4) = fVar1;
  dVar10 = (double)FLOAT_80439948;
  *(float *)(param_9 + 0x20) = fVar1;
  iVar8 = 0;
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x28) = fVar2;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    puVar4 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar8);
    puVar4[5] = (float)dVar10;
    puVar4[4] = (float)dVar10;
    puVar4[3] = (float)dVar10;
    *(undefined2 *)(puVar4 + 8) = 0;
    uVar3 = *puVar7;
    *(short *)((int)puVar4 + 0x1a) = (short)uVar3;
    *(short *)(puVar4 + 6) = (short)uVar3;
    uVar3 = puVar7[2];
    *puVar4 = puVar7[1];
    puVar4[1] = uVar3;
    puVar4[2] = puVar7[3];
    param_11 = (float *)(int)*(short *)(puVar4 + 6);
    dVar9 = (double)zz_0006fb4_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                DAT_803bb384,*(int *)(iVar6 + 0xe0),(int)param_11,param_12,param_13,
                                param_14,param_15,param_16);
    iVar8 = iVar8 + 0x24;
    puVar7 = puVar7 + 4;
    iVar6 = iVar6 + 4;
    uVar3 = extraout_r4;
  }
  zz_011f3e4_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar3,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8011f3e4  zz_011f3e4_ ====

/* WARNING: Removing unreachable block (ram,0x8011f640) */
/* WARNING: Removing unreachable block (ram,0x8011f3f4) */

void zz_011f3e4_(double param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,int param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  int iVar2;
  float fVar3;
  uint uVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  
  fVar3 = FLOAT_80439a18;
  fVar1 = FLOAT_80439950;
  dVar13 = (double)*(float *)(param_9 + 0xd4);
  dVar14 = dVar13;
  if ((PTR_DAT_80433944[0x2c] & 8) == 0) {
    param_3 = (double)FLOAT_80439950;
    if (param_3 != dVar13) {
      dVar14 = (double)*(float *)(param_9 + 0x24);
      param_1 = (double)FLOAT_80439a1c;
      if ((dVar14 < param_1) &&
         (dVar11 = (double)FLOAT_804399d0, *(float *)(param_9 + 0x24) = (float)(dVar14 + dVar11),
         param_1 <= (double)(float)(dVar14 + dVar11))) {
        *(float *)(param_9 + 0xd4) = fVar1;
        *(float *)(param_9 + 0xb4) = fVar1;
        *(float *)(param_9 + 0x24) = fVar1;
      }
    }
  }
  else {
    dVar11 = (double)FLOAT_80439a18;
    if ((dVar13 < dVar11) &&
       (dVar10 = (double)FLOAT_80439948, *(float *)(param_9 + 0xd4) = (float)(dVar13 + dVar10),
       dVar11 <= (double)(float)(dVar13 + dVar10))) {
      *(float *)(param_9 + 0xd4) = fVar3;
    }
    fVar1 = FLOAT_80439948;
    param_1 = (double)FLOAT_80439a18;
    if (param_1 == (double)*(float *)(param_9 + 0xd4)) {
      dVar14 = (double)*(float *)(param_9 + 0xb4);
      param_1 = (double)FLOAT_80439948;
      if ((dVar14 < param_1) &&
         (dVar11 = (double)FLOAT_80439958, *(float *)(param_9 + 0xb4) = (float)(dVar14 + dVar11),
         param_1 <= (double)(float)(dVar14 + dVar11))) {
        *(float *)(param_9 + 0xb4) = fVar1;
      }
    }
  }
  iVar9 = 0;
  iVar8 = param_9;
  for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
    pfVar6 = (float *)(*(int *)(param_9 + 0x54) + iVar9);
    if (iVar7 == 0) {
      param_1 = (double)*(float *)(param_9 + 0xd4);
      if (param_1 != dVar13) {
        uVar12 = zz_0008744_(param_1,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                             DAT_803bb384,*(int *)(param_9 + 0xe0),param_11,param_12,param_13,
                             param_14,param_15,param_16);
        uVar12 = zz_0007c30_(uVar12,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                             *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,
                             param_14,param_15,param_16);
        param_1 = (double)zz_0007bb4_(uVar12,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                                      *(int *)(param_9 + 0xe0),pfVar6 + 3,param_11,param_12,param_13
                                      ,param_14,param_15,param_16);
      }
    }
    else {
      pfVar6[4] = *(float *)(param_9 + 0xb4);
      if (iVar7 < 5) {
        fVar1 = FLOAT_80439950;
        if (((iVar7 != 1) || ('\x01' < (char)PTR_DAT_80433944[0x83])) &&
           ((iVar7 < 2 || (iVar7 != (char)PTR_DAT_80433944[0x83] + 2)))) {
          fVar1 = FLOAT_804399e4;
        }
        dVar13 = (double)fVar1;
        uVar12 = zz_00086b8_(dVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                             DAT_803bb384,*(int *)(iVar8 + 0xe0),param_11,param_12,param_13,param_14
                             ,param_15,param_16);
        param_1 = (double)zz_0007c30_(uVar12,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                                      *(int *)(iVar8 + 0xe0),extraout_r4_00,param_11,param_12,
                                      param_13,param_14,param_15,param_16);
      }
      else {
        pfVar6[1] = *(float *)(&DAT_8032c2c8 + (char)PTR_DAT_80433944[0x83] * 4);
        if (iVar7 == 5) {
          *(short *)(pfVar6 + 8) = *(short *)(pfVar6 + 8) + -0x200;
        }
        else if (iVar7 == 7) {
          param_11 = (float *)(int)*(short *)((int)pfVar6 + 0x1a);
          uVar4 = countLeadingZeros(2 - (char)PTR_DAT_80433944[0x83]);
          param_12 = (int)param_11 + (uVar4 >> 5);
          if (param_12 != *(short *)(pfVar6 + 6)) {
            if ((char)PTR_DAT_80433944[0x83] == 2) {
              *pfVar6 = FLOAT_80439a24;
            }
            else {
              *pfVar6 = FLOAT_80439a20;
            }
            iVar2 = DAT_803bb384;
            param_11 = (float *)(int)(short)param_12;
            iVar5 = *(int *)(iVar8 + 0xe0);
            *(short *)(pfVar6 + 6) = (short)param_12;
            param_1 = (double)zz_0006fb4_(param_1,dVar14,param_3,param_4,param_5,param_6,param_7,
                                          param_8,iVar2,iVar5,(int)param_11,param_12,param_13,
                                          param_14,param_15,param_16);
          }
        }
      }
    }
    iVar9 = iVar9 + 0x24;
    iVar8 = iVar8 + 4;
  }
  return;
}



// ==== 8011f65c  FUN_8011f65c ====

void FUN_8011f65c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  float afStack_48 [13];
  
  if (FLOAT_80439950 != *(float *)(param_9 + 0xd4)) {
    zz_00455fc_((float *)(&DAT_803c7714 + (char)PTR_DAT_80433930[0x28] * 0x3e4),
                (float *)(param_9 + 0x114),(float *)(param_9 + 0x20));
    iVar5 = 0;
    iVar4 = param_9;
    for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
      pfVar2 = (float *)(*(int *)(param_9 + 0x54) + iVar5);
      zz_00455fc_((float *)(param_9 + 0x114),afStack_48,pfVar2);
      iVar1 = (int)*(short *)(pfVar2 + 8);
      zz_00457d4_('z',afStack_48,afStack_48,*(short *)(pfVar2 + 8));
      pfVar2 = pfVar2 + 3;
      uVar6 = zz_00456a0_(afStack_48,afStack_48,pfVar2);
      zz_00076d0_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar4 + 0xe0),afStack_48,(undefined *)pfVar2,iVar1,in_r7,in_r8,in_r9,
                  in_r10);
      zz_00097b4_(*(int *)(iVar4 + 0xe0),0x44);
      iVar5 = iVar5 + 0x24;
      iVar4 = iVar4 + 4;
    }
  }
  return;
}



// ==== 8011f740  FUN_8011f740 ====

void FUN_8011f740(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  float *pfVar6;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  double dVar11;
  
  fVar4 = FLOAT_80439a14;
  fVar2 = FLOAT_80439950;
  dVar11 = (double)FLOAT_80439950;
  uVar5 = 0x80330000;
  iVar10 = 0;
  *(float *)(param_9 + 0xb4) = FLOAT_80439950;
  iVar1 = *(char *)(param_9 + 0x12) * 0x10;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(float *)(param_9 + 0xd4) = fVar2;
  *(float *)(param_9 + 0x20) = fVar2;
  *(float *)(param_9 + 0x24) = fVar2;
  *(float *)(param_9 + 0x28) = fVar4;
  iVar7 = iVar1;
  iVar9 = param_9;
  for (iVar8 = 0; fVar3 = FLOAT_804399d0, fVar4 = FLOAT_80439968, fVar2 = FLOAT_80439948,
      iVar8 < *(char *)(param_9 + 0x13); iVar8 = iVar8 + 1) {
    pfVar6 = (float *)(*(int *)(param_9 + 0x54) + iVar10);
    if (iVar8 == 0) {
      fVar4 = *(float *)(&DAT_8032c2dc + iVar1);
      *pfVar6 = *(float *)(&DAT_8032c2d8 + iVar1);
      pfVar6[1] = fVar4;
      pfVar6[2] = *(float *)(&DAT_8032c2e0 + iVar1);
      pfVar6[5] = fVar2;
      pfVar6[4] = fVar2;
      pfVar6[3] = fVar2;
      iVar7 = (int)*(short *)(&DAT_8032c2d4 + iVar1);
      dVar11 = (double)zz_0006fb4_(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   DAT_803bb384,*(int *)(iVar9 + 0xe0),iVar7,param_12,param_13,
                                   param_14,param_15,param_16);
      uVar5 = extraout_r4;
    }
    else if ((*(char *)(param_9 + 0x12) == '\x02') && (iVar8 == 4)) {
      fVar4 = *(float *)(&DAT_8032c2ec + iVar1);
      *pfVar6 = *(float *)(&DAT_8032c2e8 + iVar1);
      pfVar6[1] = fVar4;
      pfVar6[2] = *(float *)(&DAT_8032c2f0 + iVar1);
      pfVar6[5] = fVar2;
      pfVar6[4] = fVar2;
      pfVar6[3] = fVar2;
      iVar7 = (int)*(short *)(&DAT_8032c2e4 + iVar1);
      dVar11 = (double)zz_0006fb4_(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   DAT_803bb384,*(int *)(iVar9 + 0xe0),iVar7,param_12,param_13,
                                   param_14,param_15,param_16);
      uVar5 = extraout_r4_00;
    }
    else {
      if (*(char *)(param_9 + 0x12) == '\x02') {
        *pfVar6 = FLOAT_80439968 *
                  (FLOAT_804399d0 *
                   (float)((double)CONCAT44(0x43300000,iVar8 - 1U ^ 0x80000000) - DOUBLE_804399f0) -
                  FLOAT_80439a2c);
      }
      else {
        *pfVar6 = FLOAT_80439968 *
                  (FLOAT_804399d0 *
                   (float)((double)CONCAT44(0x43300000,iVar8 - 1U ^ 0x80000000) - DOUBLE_804399f0) +
                  FLOAT_80439a28);
      }
      fVar2 = FLOAT_804399e4;
      param_3 = (double)fVar3;
      param_2 = (double)fVar4;
      iVar7 = 8;
      pfVar6[1] = *(float *)(&DAT_8032c2dc + iVar1);
      fVar4 = FLOAT_80439968;
      dVar11 = (double)FLOAT_80439968;
      pfVar6[2] = fVar2;
      fVar2 = FLOAT_80439948;
      pfVar6[3] = fVar4;
      pfVar6[4] = fVar4;
      pfVar6[5] = fVar2;
      dVar11 = (double)zz_0006fb4_(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   DAT_803bb384,*(int *)(iVar9 + 0xe0),8,param_12,param_13,param_14,
                                   param_15,param_16);
      uVar5 = extraout_r4_01;
    }
    iVar10 = iVar10 + 0x24;
    iVar9 = iVar9 + 4;
  }
  zz_011f92c_(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar5,iVar7,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8011f92c  zz_011f92c_ ====

void zz_011f92c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  size_t sVar4;
  int iVar5;
  undefined4 extraout_r4;
  float *pfVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  double dVar10;
  double dVar11;
  undefined8 uVar12;
  char local_39 [9];
  undefined4 local_30;
  uint uStack_2c;
  
  fVar2 = FLOAT_80439a18;
  fVar1 = FLOAT_80439950;
  if ((PTR_DAT_80433944[0x2c] & 8) == 0) {
    param_3 = (double)FLOAT_80439950;
    if (param_3 != (double)*(float *)(param_9 + 0xd4)) {
      param_2 = (double)*(float *)(param_9 + 0x24);
      dVar11 = (double)FLOAT_80439a1c;
      if ((param_2 < dVar11) &&
         (dVar10 = (double)FLOAT_804399d0, *(float *)(param_9 + 0x24) = (float)(param_2 + dVar10),
         dVar11 <= (double)(float)(param_2 + dVar10))) {
        *(float *)(param_9 + 0xd4) = fVar1;
        *(float *)(param_9 + 0xb4) = fVar1;
        *(float *)(param_9 + 0x24) = fVar1;
      }
    }
  }
  else {
    param_2 = (double)*(float *)(param_9 + 0xd4);
    dVar11 = (double)FLOAT_80439a18;
    if ((param_2 < dVar11) &&
       (dVar10 = (double)FLOAT_80439948, *(float *)(param_9 + 0xd4) = (float)(param_2 + dVar10),
       dVar11 <= (double)(float)(param_2 + dVar10))) {
      *(float *)(param_9 + 0xd4) = fVar2;
    }
    fVar1 = FLOAT_80439948;
    if (FLOAT_80439a18 == *(float *)(param_9 + 0xd4)) {
      param_2 = (double)*(float *)(param_9 + 0xb4);
      dVar11 = (double)FLOAT_80439948;
      if ((param_2 < dVar11) &&
         (dVar10 = (double)FLOAT_80439958, *(float *)(param_9 + 0xb4) = (float)(param_2 + dVar10),
         dVar11 <= (double)(float)(param_2 + dVar10))) {
        *(float *)(param_9 + 0xb4) = fVar1;
      }
    }
  }
  pfVar6 = (float *)(int)*(char *)(param_9 + 0x12);
  iVar3 = -((int)(2U - (int)pfVar6 | (int)pfVar6 - 2U) >> 0x1f);
  if (iVar3 == 0) {
    iVar3 = (int)(char)PTR_DAT_80433944[0x82];
    if (iVar3 != 0) {
      pfVar6 = (float *)0x3e7;
      if (*(short *)(&DAT_80434788 + iVar3 * 2) < 999) {
        pfVar6 = (float *)(int)*(short *)(&DAT_80434788 + iVar3 * 2);
      }
      sprintf(local_39 + 1,&DAT_80439a34);
    }
  }
  else {
    iVar8 = (int)pfVar6 * 4;
    pfVar6 = (float *)0xf423f;
    if ((int)*(float **)(PTR_DAT_80433944 + iVar8 + 0x70) < 999999) {
      pfVar6 = *(float **)(PTR_DAT_80433944 + iVar8 + 0x70);
    }
    sprintf(local_39 + 1,&DAT_80439a30);
  }
  *(undefined2 *)(param_9 + 0x1c) = 0;
  sVar4 = strlen(local_39 + 1);
  pcVar9 = local_39;
  iVar8 = param_9;
  for (iVar7 = 0; dVar11 = DOUBLE_804399f0, pcVar9 = pcVar9 + 1, iVar7 < *(char *)(param_9 + 0x13);
      iVar7 = iVar7 + 1) {
    if (iVar7 == 0) {
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | 1;
    }
    else if ((iVar3 == 0) || ((int)(sVar4 + 1) <= iVar7)) {
      if ((iVar3 == 0) && ((*(char *)(param_9 + 0x12) == '\x02' && (iVar7 == 4)))) {
        *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | 0x10;
      }
    }
    else {
      iVar5 = (int)pcVar9[-1];
      if ((0x2f < iVar5) && (iVar5 < 0x3a)) {
        uStack_2c = iVar5 - 0x30U ^ 0x80000000;
        local_30 = 0x43300000;
        *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar7);
        uVar12 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_2c) - dVar11),
                             param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                             *(int *)(iVar8 + 0xe0),pfVar6,param_12,param_13,param_14,param_15,
                             param_16);
        zz_0007c30_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar8 + 0xe0),extraout_r4,pfVar6,param_12,param_13,param_14,param_15,
                    param_16);
      }
    }
    iVar8 = iVar8 + 4;
  }
  return;
}



// ==== 8011fbbc  FUN_8011fbbc ====

void FUN_8011fbbc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float *pfVar1;
  float fVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [15];
  
  if ((FLOAT_80439950 != *(float *)(param_9 + 0xd4)) && (*(short *)(param_9 + 0x1c) != 0)) {
    zz_00455fc_((float *)(&DAT_803c7714 + (char)PTR_DAT_80433930[0x28] * 0x3e4),
                (float *)(param_9 + 0x114),(float *)(param_9 + 0x20));
    iVar3 = *(char *)(param_9 + 0x13) + -1;
    iVar5 = iVar3 * 0x24;
    iVar4 = param_9 + iVar3 * 4;
    while( true ) {
      if (iVar3 < 0) break;
      if (((int)*(short *)(param_9 + 0x1c) & 1 << iVar3) != 0) {
        pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar5);
        fVar2 = pfVar1[3];
        local_50 = pfVar1[5];
        local_54 = pfVar1[4] * *(float *)(param_9 + 0xb4);
        local_58 = fVar2;
        zz_00455fc_((float *)(param_9 + 0x114),afStack_4c,pfVar1);
        pfVar1 = &local_58;
        uVar6 = zz_00456a0_(afStack_4c,afStack_4c,pfVar1);
        zz_00076d0_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar4 + 0xe0),afStack_4c,(undefined *)pfVar1,fVar2,in_r7,in_r8,in_r9,
                    in_r10);
        zz_00097b4_(*(int *)(iVar4 + 0xe0),0x44);
      }
      iVar5 = iVar5 + -0x24;
      iVar4 = iVar4 + -4;
      iVar3 = iVar3 + -1;
    }
  }
  return;
}



// ==== 8011fcec  FUN_8011fcec ====

void FUN_8011fcec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  float *pfVar3;
  double dVar4;
  undefined8 uVar5;
  
  fVar2 = FLOAT_80439a38;
  fVar1 = FLOAT_80439950;
  dVar4 = (double)FLOAT_80439950;
  pfVar3 = (float *)0x67;
  *(float *)(param_9 + 0xd4) = FLOAT_80439950;
  *(float *)(param_9 + 0x20) = fVar1;
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x28) = fVar2;
  zz_0006fb4_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
              *(int *)(param_9 + 0xe0),0x67,param_12,param_13,param_14,param_15,param_16);
  uVar5 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,DAT_803bb384,*(int *)(param_9 + 0xe0),pfVar3,param_12,param_13
                      ,param_14,param_15,param_16);
  zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,pfVar3,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8011fd64  FUN_8011fd64 ====

void FUN_8011fd64(int param_1,undefined4 param_2,float *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  bool bVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  dVar6 = (double)*(float *)(param_1 + 0xd4);
  if ((PTR_DAT_80433944[0x2c] & 8) == 0) {
    if (PTR_DAT_80433944[0x6f] != '\0') {
      *(float *)(param_1 + 0x28) = FLOAT_80439a3c;
    }
  }
  else {
    *(float *)(param_1 + 0x28) = FLOAT_80439a38;
  }
  fVar2 = FLOAT_80439950;
  fVar1 = FLOAT_80439948;
  if (((PTR_DAT_80433944[0x2c] & 8) == 0) && (PTR_DAT_80433944[0x6f] == '\0')) {
    dVar5 = (double)*(float *)(param_1 + 0xd4);
    bVar3 = (float)(dVar5 - (double)FLOAT_804399c4) < FLOAT_80439950;
    *(float *)(param_1 + 0xd4) = (float)(dVar5 - (double)FLOAT_804399c4);
    if (bVar3) {
      *(float *)(param_1 + 0xd4) = fVar2;
    }
  }
  else {
    dVar5 = (double)*(float *)(param_1 + 0xd4);
    bVar3 = FLOAT_80439948 < (float)(dVar5 + (double)FLOAT_804399c4);
    *(float *)(param_1 + 0xd4) = (float)(dVar5 + (double)FLOAT_804399c4);
    if (bVar3) {
      *(float *)(param_1 + 0xd4) = fVar1;
    }
  }
  if ((double)*(float *)(param_1 + 0xd4) != dVar6) {
    uVar4 = zz_00086b8_((double)*(float *)(param_1 + 0xd4),dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8
                        ,DAT_803bb384,*(int *)(param_1 + 0xe0),param_3,param_4,param_5,param_6,
                        param_7,param_8);
    zz_0007c30_(uVar4,dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),extraout_r4
                ,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return;
}



// ==== 8011fe48  FUN_8011fe48 ====

void FUN_8011fe48(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  
  if (FLOAT_80439950 < *(float *)(param_9 + 0xd4)) {
    gnt4_PSMTXCopy_bl((float *)(&DAT_803c7714 + (char)PTR_DAT_80433930[0x28] * 0x3e4),
                      (float *)(param_9 + 0x114));
    pfVar1 = (float *)(param_9 + 0x20);
    uVar2 = zz_00455fc_((float *)(param_9 + 0x114),(float *)(param_9 + 0x114),pfVar1);
    zz_00076d0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),(undefined *)pfVar1,param_12,
                param_13,param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  }
  return;
}



// ==== 8011fed0  FUN_8011fed0 ====

void FUN_8011fed0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  *(float *)(param_9 + 0x44) = FLOAT_8043995c;
  iVar2 = param_9;
  for (iVar1 = 0; iVar1 < *(char *)(param_9 + 0x13); iVar1 = iVar1 + 1) {
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb384,*(int *)(iVar2 + 0xe0),0x30,param_12,param_13,param_14,
                          param_15,param_16);
    iVar2 = iVar2 + 4;
  }
  zz_011ff5c_(param_9);
  return;
}



// ==== 8011ff5c  zz_011ff5c_ ====

/* WARNING: Removing unreachable block (ram,0x80120088) */
/* WARNING: Removing unreachable block (ram,0x8011ff6c) */

void zz_011ff5c_(int param_1)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  
  fVar2 = FLOAT_80439948;
  dVar9 = (double)*(float *)(param_1 + 0x44);
  *(float *)(param_1 + 0x44) =
       (*(float *)(PTR_DAT_80433944 + 0x1c) - FLOAT_80439978) / FLOAT_8043997c;
  fVar1 = *(float *)(param_1 + 0x44);
  if ((fVar1 <= fVar2) && (fVar2 = fVar1, fVar1 < FLOAT_80439950)) {
    fVar2 = FLOAT_80439950;
  }
  *(float *)(param_1 + 0x44) = fVar2;
  iVar8 = 0;
  *(undefined2 *)(param_1 + 0x1c) = 0;
  iVar7 = param_1;
  for (iVar6 = 0; iVar6 < *(char *)(param_1 + 0x13); iVar6 = iVar6 + 1) {
    if ((PTR_DAT_80433944[(char)PTR_DAT_80433944[iVar6 + 0x28] + 0x20] & 0xc0) == 0x80) {
      *(ushort *)(param_1 + 0x1c) = *(ushort *)(param_1 + 0x1c) | (ushort)(1 << iVar6);
      puVar5 = (undefined4 *)(*(int *)(param_1 + 0x54) + iVar8);
      iVar4 = (char)PTR_DAT_80433944[iVar6 + 0x28] * 0xc;
      uVar3 = *(undefined4 *)(&DAT_8032c318 + iVar4);
      *puVar5 = *(undefined4 *)(&DAT_8032c314 + iVar4);
      puVar5[1] = uVar3;
      puVar5[2] = *(undefined4 *)(&DAT_8032c31c + iVar4);
    }
    if ((double)*(float *)(param_1 + 0x44) != dVar9) {
      zz_0007cac_((double)*(float *)(param_1 + 0x44),*(int *)(iVar7 + 0xe0));
    }
    iVar8 = iVar8 + 0x24;
    iVar7 = iVar7 + 4;
  }
  return;
}



// ==== 801200b0  FUN_801200b0 ====

void FUN_801200b0(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  iVar2 = 0;
  iVar4 = 0;
  iVar3 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar2) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar2) != 0) {
      pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
      dVar6 = (double)pfVar1[1];
      dVar7 = (double)pfVar1[2];
      uVar5 = gnt4_PSMTXTrans_bl((double)*pfVar1,dVar6,dVar7,afStack_48);
      zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_48,
                  param_3,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
    }
    iVar4 = iVar4 + 0x24;
    iVar3 = iVar3 + 4;
    iVar2 = iVar2 + 1;
  }
  return;
}



// ==== 8012014c  FUN_8012014c ====

/* WARNING: Removing unreachable block (ram,0x8012022c) */
/* WARNING: Removing unreachable block (ram,0x80120224) */
/* WARNING: Removing unreachable block (ram,0x80120164) */
/* WARNING: Removing unreachable block (ram,0x8012015c) */

void FUN_8012014c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  
  dVar7 = (double)FLOAT_80439950;
  *(float *)(param_9 + 0xd4) = FLOAT_80439950;
  fVar1 = FLOAT_80439a40;
  iVar6 = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  dVar8 = (double)FLOAT_80439948;
  psVar5 = (short *)&DAT_80434584;
  *(short *)(param_9 + 0x1e) =
       (short)(char)PTR_DAT_80433944[*(char *)(param_9 + 0x12) * 0x80 + 0x164];
  *(float *)(param_9 + 0x28) = fVar1;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    pfVar2 = (float *)(*(int *)(param_9 + 0x54) + iVar6);
    *(undefined2 *)(pfVar2 + 8) = 0;
    pfVar2[2] = (float)dVar7;
    pfVar2[1] = (float)dVar7;
    *pfVar2 = (float)dVar7;
    pfVar2[5] = (float)dVar8;
    pfVar2[4] = (float)dVar8;
    pfVar2[3] = (float)dVar8;
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb384,*(int *)(iVar4 + 0xe0),(int)*psVar5,param_12,param_13,
                          param_14,param_15,param_16);
    iVar6 = iVar6 + 0x24;
    psVar5 = psVar5 + 1;
    iVar4 = iVar4 + 4;
  }
  zz_0120248_(param_9);
  return;
}



// ==== 80120248  zz_0120248_ ====

void zz_0120248_(int param_1)

{
  char cVar1;
  int iVar2;
  float fVar3;
  float fVar4;
  undefined *puVar5;
  
  fVar4 = FLOAT_80439950;
  puVar5 = PTR_DAT_80433944 + *(char *)(param_1 + 0x12) * 0x80 + 0x100;
  if ((int)*(short *)(param_1 + 0x1e) != (int)(char)puVar5[100]) {
    if (FLOAT_80439950 < *(float *)(param_1 + 0xd4)) {
      fVar3 = *(float *)(param_1 + 0xd4) - FLOAT_80439948;
      *(float *)(param_1 + 0xd4) = fVar3;
      if (fVar3 <= fVar4) {
        *(float *)(param_1 + 0xd4) = fVar4;
        *(short *)(param_1 + 0x1e) = (short)(char)puVar5[100];
      }
    }
    else {
      *(float *)(param_1 + 0xd4) = FLOAT_80439a44;
    }
  }
  fVar3 = FLOAT_8043999c;
  fVar4 = FLOAT_80439948;
  cVar1 = puVar5[100];
  iVar2 = *(short *)(param_1 + 0x1e) * 8;
  *(float *)(param_1 + 0x20) =
       -(*(float *)(param_1 + 0xd4) * FLOAT_8043999c - FLOAT_80439948) *
       (*(float *)(&DAT_8032c350 + cVar1 * 8) - *(float *)(&DAT_8032c350 + iVar2)) +
       *(float *)(&DAT_8032c350 + iVar2);
  *(float *)(param_1 + 0x24) =
       -(*(float *)(param_1 + 0xd4) * fVar3 - fVar4) *
       (*(float *)(&DAT_8032c354 + cVar1 * 8) - *(float *)(&DAT_8032c354 + iVar2)) +
       *(float *)(&DAT_8032c354 + iVar2);
  (*(code *)(&PTR_LAB_8032c344)[*(char *)(param_1 + 0x19)])(param_1,puVar5);
  if ((puVar5[0x3d] & 0x10) == 0) {
    *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  }
  return;
}



// ==== 80120510  FUN_80120510 ====

void FUN_80120510(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_80439950;
  if (*(float *)(param_1 + 0xd8) <= FLOAT_80439950) {
    if ((*(byte *)(param_2 + 0x3f) & 0x10) == 0) {
      dVar3 = (double)FLOAT_80439948;
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + -1;
      *(float *)(param_1 + 0xd8) = fVar2;
      zz_0007cac_(dVar3,*(int *)(param_1 + 0xe0));
    }
  }
  else {
    fVar1 = *(float *)(param_1 + 0xd8) - FLOAT_80439948;
    *(float *)(param_1 + 0xd8) = fVar1;
    if (fVar1 <= fVar2) {
      *(float *)(param_1 + 0xd8) = fVar2;
      zz_0007cac_((double)FLOAT_80439970,*(int *)(param_1 + 0xe0));
    }
    if (((int)*(float *)(param_1 + 0xd8) & 1U) == 0) {
      *(undefined2 *)(param_1 + 0x1c) = 1;
    }
    else {
      *(undefined2 *)(param_1 + 0x1c) = 0;
    }
  }
  return;
}



// ==== 801205c8  FUN_801205c8 ====

void FUN_801205c8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  float afStack_48 [13];
  
  zz_00455fc_((float *)(&DAT_803c7714 + (char)PTR_DAT_80433930[0x28] * 0x3e4),
              (float *)(param_9 + 0x114),(float *)(param_9 + 0x20));
  iVar3 = 0;
  iVar5 = 0;
  iVar4 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar3) break;
    if (((int)*(short *)(param_9 + 0x1c) & 1 << iVar3) != 0) {
      pfVar2 = (float *)(*(int *)(param_9 + 0x54) + iVar5);
      zz_00455fc_((float *)(param_9 + 0x114),afStack_48,pfVar2);
      iVar1 = (int)*(short *)(pfVar2 + 8);
      zz_00457d4_('z',afStack_48,afStack_48,*(short *)(pfVar2 + 8));
      pfVar2 = pfVar2 + 3;
      uVar6 = zz_00456a0_(afStack_48,afStack_48,pfVar2);
      zz_00076d0_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar4 + 0xe0),afStack_48,(undefined *)pfVar2,iVar1,in_r7,in_r8,in_r9,
                  in_r10);
      zz_00097b4_(*(int *)(iVar4 + 0xe0),0x44);
    }
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 1;
  }
  return;
}



// ==== 801206b0  FUN_801206b0 ====

void FUN_801206b0(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int *piVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  double dVar10;
  undefined8 uVar11;
  double dVar12;
  
  fVar3 = FLOAT_80439a48;
  fVar2 = FLOAT_80439a18;
  fVar1 = FLOAT_80439950;
  dVar12 = (double)FLOAT_80439950;
  dVar10 = (double)FLOAT_80439a48;
  iVar9 = 0;
  *(undefined1 *)(param_9 + 0x19) = 0;
  piVar8 = &DAT_8032c3fc;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0x20) = fVar1;
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x28) = fVar3;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(float *)(param_9 + 0xd4) = fVar1;
  *(float *)(param_9 + 0xd8) = fVar2;
  iVar7 = param_9;
  for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    piVar5 = (int *)(*(int *)(param_9 + 0x54) + iVar9);
    *(undefined2 *)(piVar5 + 8) = 0;
    iVar4 = piVar8[2];
    *piVar5 = piVar8[1];
    piVar5[1] = iVar4;
    piVar5[2] = piVar8[3];
    piVar5[3] = *piVar5;
    piVar5[4] = piVar5[1];
    piVar5[5] = piVar5[2];
    param_11 = (float *)*piVar8;
    dVar10 = (double)zz_0006fb4_(dVar10,dVar12,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_803bb384,*(int *)(iVar7 + 0xe0),(int)param_11,param_12,param_13
                                 ,param_14,param_15,param_16);
    param_10 = extraout_r4;
    if (iVar6 == 0) {
      uVar11 = zz_0008744_((double)*(float *)(param_9 + 0xd4),dVar12,param_3,param_4,param_5,param_6
                           ,param_7,param_8,DAT_803bb384,*(int *)(iVar7 + 0xe0),param_11,param_12,
                           param_13,param_14,param_15,param_16);
      uVar11 = zz_0007c30_(uVar11,dVar12,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(iVar7 + 0xe0),extraout_r4_00,param_11,param_12,param_13,param_14
                           ,param_15,param_16);
      dVar10 = (double)zz_0007bb4_(uVar11,dVar12,param_3,param_4,param_5,param_6,param_7,param_8,
                                   *(int *)(iVar7 + 0xe0),piVar5 + 3,param_11,param_12,param_13,
                                   param_14,param_15,param_16);
      param_10 = extraout_r4_01;
    }
    iVar9 = iVar9 + 0x24;
    piVar8 = piVar8 + 4;
    iVar7 = iVar7 + 4;
  }
  zz_01207c8_(dVar10,dVar12,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801207c8  zz_01207c8_ ====

void zz_01207c8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  short sVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  undefined8 uVar10;
  
  fVar2 = FLOAT_80439a4c;
  fVar1 = FLOAT_80439950;
  if (*(char *)(param_9 + 0x19) == '\0') {
    if (PTR_DAT_80433944[0x6f] == '\0') {
      *(undefined1 *)(param_9 + 0x19) = 1;
      *(float *)(param_9 + 0xd4) = fVar2;
    }
    else {
      param_2 = (double)*(float *)(param_9 + 0xd8);
      if (((double)*(float *)(param_9 + 0xd4) < param_2) &&
         (fVar1 = (float)((double)*(float *)(param_9 + 0xd4) + (double)FLOAT_80439948),
         *(float *)(param_9 + 0xd4) = fVar1, param_2 < (double)fVar1)) {
        *(undefined4 *)(param_9 + 0xd4) = *(undefined4 *)(param_9 + 0xd8);
      }
    }
    fVar1 = FLOAT_80439948;
    if (FLOAT_80439a4c <= *(float *)(param_9 + 0xd4)) {
      param_2 = (double)*(float *)(param_9 + 0xb4);
      dVar9 = (double)FLOAT_80439948;
      if (param_2 < dVar9) {
        dVar8 = (double)FLOAT_80439958;
        *(float *)(param_9 + 0xb4) = (float)(param_2 + dVar8);
        if (dVar9 <= (double)(float)(param_2 + dVar8)) {
          *(float *)(param_9 + 0xb4) = fVar1;
        }
      }
    }
  }
  else {
    if (FLOAT_80439950 < *(float *)(param_9 + 0xb4)) {
      fVar2 = *(float *)(param_9 + 0xb4) - FLOAT_80439958;
      *(float *)(param_9 + 0xb4) = fVar2;
      if (fVar2 <= fVar1) {
        *(float *)(param_9 + 0xb4) = fVar1;
      }
    }
    fVar1 = FLOAT_80439950;
    param_2 = (double)*(float *)(param_9 + 0xd4);
    dVar9 = (double)FLOAT_80439948;
    *(float *)(param_9 + 0xd4) = (float)(param_2 - dVar9);
    if ((float)(param_2 - dVar9) <= fVar1) {
      *(float *)(param_9 + 0xd4) = fVar1;
      *(undefined1 *)(param_9 + 0x18) = 2;
    }
  }
  iVar7 = 0;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    pfVar4 = (float *)(*(int *)(param_9 + 0x54) + iVar7);
    if (iVar5 == 0) {
      uVar10 = zz_0008744_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,
                           param_6,param_7,param_8,DAT_803bb384,*(int *)(iVar6 + 0xe0),param_11,
                           param_12,param_13,param_14,param_15,param_16);
      uVar10 = zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(iVar6 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                           param_15,param_16);
      zz_0007bb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar6 + 0xe0),pfVar4 + 3,param_11,param_12,param_13,param_14,param_15,
                  param_16);
    }
    else if (iVar5 < 3) {
      if (iVar5 == 1) {
        if (FLOAT_80439948 <= *(float *)(param_9 + 0xb4)) {
          sVar3 = *(short *)(pfVar4 + 8) + -0x100;
        }
        else {
          sVar3 = 0;
        }
        *(short *)(pfVar4 + 8) = sVar3;
      }
      param_2 = DOUBLE_804399f0;
      param_3 = (double)FLOAT_80439a50;
      *pfVar4 = (float)(param_3 * (double)(float)((double)CONCAT44(0x43300000,
                                                                   (int)(char)PTR_DAT_80433944[0x83]
                                                                   ^ 0x80000000) - DOUBLE_804399f0)
                       + (double)pfVar4[3]);
    }
    else if (3 < iVar5) {
      if (iVar5 + -4 == (int)(char)PTR_DAT_80433944[0x83]) {
        if ((PTR_DAT_80433944[0x6f] == '\x02') && ((*(ushort *)(PTR_DAT_80433944 + 8) & 4) != 0)) {
          dVar9 = (double)FLOAT_80439948;
        }
        else {
          dVar9 = (double)FLOAT_80439950;
        }
      }
      else {
        dVar9 = (double)FLOAT_804399e4;
      }
      uVar10 = zz_00086b8_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_803bb384,*(int *)(iVar6 + 0xe0),param_11,param_12,param_13,param_14,
                           param_15,param_16);
      zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar6 + 0xe0),extraout_r4_00,param_11,param_12,param_13,param_14,param_15
                  ,param_16);
    }
    iVar7 = iVar7 + 0x24;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 80120a24  FUN_80120a24 ====

void FUN_80120a24(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  float local_58;
  undefined4 local_54;
  float local_50;
  float afStack_4c [14];
  
  zz_00455fc_((float *)(&DAT_803c7714 + (char)PTR_DAT_80433930[0x28] * 0x3e4),
              (float *)(param_9 + 0x114),(float *)(param_9 + 0x20));
  iVar5 = 0;
  local_58 = FLOAT_80439948;
  local_54 = *(undefined4 *)(param_9 + 0xb4);
  local_50 = FLOAT_80439948;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    if ((iVar3 == 0) || (FLOAT_80439950 < *(float *)(param_9 + 0xb4))) {
      pfVar2 = (float *)(*(int *)(param_9 + 0x54) + iVar5);
      zz_00455fc_((float *)(param_9 + 0x114),afStack_4c,pfVar2);
      iVar1 = (int)*(short *)(pfVar2 + 8);
      zz_00457d4_('z',afStack_4c,afStack_4c,*(short *)(pfVar2 + 8));
      if (iVar3 == 0) {
        pfVar2 = pfVar2 + 3;
        uVar6 = zz_00456a0_(afStack_4c,afStack_4c,pfVar2);
      }
      else {
        pfVar2 = &local_58;
        uVar6 = zz_00456a0_(afStack_4c,afStack_4c,pfVar2);
      }
      zz_00076d0_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar4 + 0xe0),afStack_4c,(undefined *)pfVar2,iVar1,in_r7,in_r8,in_r9,
                  in_r10);
      zz_00097b4_(*(int *)(iVar4 + 0xe0),0x44);
    }
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
  }
  return;
}



// ==== 80120b58  zz_0120b58_ ====

void zz_0120b58_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((((sVar1 == 0x803) || (sVar1 == 0x80a)) || (sVar1 == 0x80b)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_80120c70;
    *(code **)(puVar2 + 0x10c) = FUN_801212d0;
    *(int *)(puVar2 + 0x8c) = param_1;
    *(undefined4 *)(puVar2 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar2 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar2[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar2[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar2[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar2 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar2 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar2 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar2 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar2 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar2[0xd0] = *(undefined1 *)(param_1 + 0xd0);
  }
  return;
}



