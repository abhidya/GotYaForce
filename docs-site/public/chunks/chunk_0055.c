// ==== 801c4908  zz_01c4908_ ====

void zz_01c4908_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  char *pcVar8;
  int iVar9;
  double dVar10;
  undefined2 local_28 [10];
  
  fVar1 = FLOAT_8043bc2c;
  if (*(short *)(PTR_DAT_80435a30 + 0x144) < 0) {
    if (*(short *)(PTR_DAT_80435a30 + 0x146) < 0) {
      pcVar8 = (char *)0x0;
    }
    else {
      pcVar8 = (char *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                       *(short *)(PTR_DAT_80435a30 + 0x146) * 0x20 + 0x870);
      if ((-1 < *(short *)(PTR_DAT_80435a30 + 0x50)) &&
         ((*(uint *)(pcVar8 + 0x10) & 1 << (int)(char)PTR_DAT_80435a30[0x40]) != 0)) {
        pcVar8 = (char *)0x0;
      }
    }
  }
  else {
    pcVar8 = (char *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                     *(short *)(PTR_DAT_80435a30 + 0x144) * 0x20 + 0x870);
  }
  if (pcVar8 == (char *)0x0) {
    if ((*(short *)(param_9 + 0x1c) != 0) &&
       (sVar3 = *(short *)(param_9 + 0x1c) + -1, *(short *)(param_9 + 0x1c) = sVar3, sVar3 == 0)) {
      *(undefined4 *)(param_9 + 0xd4) = 0xffffffff;
      *(undefined4 *)(param_9 + 0xd8) = 0xffffffff;
    }
  }
  else {
    *(undefined2 *)(param_9 + 0x1c) = 10;
    dVar10 = (double)*(float *)(PTR_DAT_80435a30 + 0x30);
    iVar4 = ((uint)(*(float *)(PTR_DAT_80435a30 + 0x34) < fVar1) +
            (uint)(byte)(((double)FLOAT_8043bc10 < dVar10) << 1)) * 0xc;
    puVar6 = (undefined4 *)(&DAT_803854f8 + iVar4);
    uVar2 = *(undefined4 *)(&DAT_803854fc + iVar4);
    *(undefined4 *)(param_9 + 0x20) = *puVar6;
    *(undefined4 *)(param_9 + 0x24) = uVar2;
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(&DAT_80385500 + iVar4);
    *(undefined4 *)(param_9 + 0xcc) =
         *(undefined4 *)((&PTR_PTR_803510d8)[*pcVar8] + (uint)(byte)pcVar8[1] * 4);
    local_28[0] = *(undefined2 *)pcVar8;
    iVar4 = zz_0066168_((char *)local_28,(int)pcVar8[2]);
    *(int *)(param_9 + 0xd4) = iVar4;
    iVar9 = 0;
    *(int *)(param_9 + 0xd8) = pcVar8[3] + 1;
    iVar4 = param_9;
    for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
      iVar5 = *(int *)(param_9 + 0x54) + iVar9;
      if (((iVar7 == 1) &&
          (sVar3 = *(short *)(&DAT_80385528 + pcVar8[2] * 2), sVar3 != *(short *)(iVar5 + 0x20))) &&
         (*(short *)(iVar5 + 0x20) = sVar3, -1 < sVar3)) {
        dVar10 = (double)zz_0006fb4_(dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                     DAT_803bb32c,*(int *)(iVar4 + 0xe0),
                                     (int)*(short *)(iVar5 + 0x20),puVar6,in_r7,in_r8,in_r9,in_r10);
      }
      iVar9 = iVar9 + 0x24;
      iVar4 = iVar4 + 4;
    }
  }
  return;
}



// ==== 801c4b10  FUN_801c4b10 ====

void FUN_801c4b10(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float afStack_40 [12];
  
  if (0 < *(short *)(param_9 + 0x1c)) {
    zz_00455fc_((float *)(&DAT_803c7714 + (char)PTR_DAT_80433930[0x28] * 0x3e4),
                (float *)(param_9 + 0x114),(float *)(param_9 + 0x20));
    iVar4 = 0;
    iVar3 = param_9;
    for (iVar2 = 0; iVar2 < *(char *)(param_9 + 0x13); iVar2 = iVar2 + 1) {
      pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar4);
      if (-1 < *(short *)(pfVar1 + 8)) {
        uVar5 = zz_00455fc_((float *)(param_9 + 0x114),afStack_40,pfVar1);
        zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar3 + 0xe0),afStack_40,(undefined *)pfVar1,param_12,param_13,param_14
                    ,param_15,param_16);
        zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
      }
      iVar4 = iVar4 + 0x24;
      iVar3 = iVar3 + 4;
    }
    local_4c = FLOAT_8043bc30;
    local_48 = FLOAT_8043bc34;
    local_44 = FLOAT_8043bc38;
    local_58 = FLOAT_8043bba4;
    local_54 = FLOAT_8043bba4;
    local_50 = FLOAT_8043bba4;
    FUN_801c53dc((double)FLOAT_8043bba4,(double)FLOAT_8043bc3c,(double)FLOAT_8043bc40,
                 (float *)(param_9 + 0x114),&local_4c,&local_58,3,0x22,*(short **)(param_9 + 0xcc));
  }
  return;
}



// ==== 801c4c38  FUN_801c4c38 ====

/* WARNING: Removing unreachable block (ram,0x801c4d78) */
/* WARNING: Removing unreachable block (ram,0x801c4d70) */
/* WARNING: Removing unreachable block (ram,0x801c4d68) */
/* WARNING: Removing unreachable block (ram,0x801c4d60) */
/* WARNING: Removing unreachable block (ram,0x801c4d58) */
/* WARNING: Removing unreachable block (ram,0x801c4c68) */
/* WARNING: Removing unreachable block (ram,0x801c4c60) */
/* WARNING: Removing unreachable block (ram,0x801c4c58) */
/* WARNING: Removing unreachable block (ram,0x801c4c50) */
/* WARNING: Removing unreachable block (ram,0x801c4c48) */

void FUN_801c4c38(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  float *pfVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *extraout_r4;
  uint uVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  
  *(undefined4 *)(param_9 + 0xd4) = 0xffffffff;
  dVar9 = DOUBLE_8043bb98;
  dVar8 = (double)FLOAT_8043bc44;
  uVar5 = (uint)*(byte *)(param_9 + 0x12);
  dVar10 = (double)FLOAT_8043bb80;
  iVar3 = (char)*(byte *)(param_9 + 0x12) * 0xc;
  dVar11 = (double)FLOAT_8043bc48;
  dVar12 = (double)FLOAT_8043bba4;
  puVar4 = (undefined4 *)(&DAT_80385534 + iVar3);
  iVar7 = 0;
  uVar1 = *(undefined4 *)(&DAT_80385538 + iVar3);
  *(undefined4 *)(param_9 + 0x20) = *puVar4;
  *(undefined4 *)(param_9 + 0x24) = uVar1;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(&DAT_8038553c + iVar3);
  iVar3 = param_9;
  for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    pfVar2 = (float *)(*(int *)(param_9 + 0x54) + iVar7);
    uVar5 = 0x22;
    *pfVar2 = (float)(dVar8 * (double)(float)((double)CONCAT44(0x43300000,
                                                               (*(char *)(param_9 + 0x13) + -1) -
                                                               iVar6 ^ 0x80000000) - dVar9));
    pfVar2[1] = (float)dVar10;
    pfVar2[2] = (float)dVar10;
    pfVar2[3] = (float)dVar11;
    pfVar2[4] = (float)dVar11;
    pfVar2[5] = (float)dVar12;
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb32c,*(int *)(iVar3 + 0xe0),0x22,param_12,param_13,param_14,
                          param_15,param_16);
    iVar7 = iVar7 + 0x24;
    iVar3 = iVar3 + 4;
    puVar4 = extraout_r4;
  }
  *(undefined1 *)(param_9 + 0x82) = 4;
  FUN_801c4d94(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,puVar4,uVar5,
               param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801c4d94  FUN_801c4d94 ====

void FUN_801c4d94(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  int iVar2;
  size_t sVar3;
  undefined1 uVar5;
  int iVar4;
  undefined4 extraout_r4;
  float *pfVar6;
  int iVar7;
  undefined8 uVar8;
  char acStack_29 [9];
  undefined4 local_20;
  uint uStack_1c;
  
  iVar2 = 999999;
  if (**(int **)(param_9 + 0xcc) < 999999) {
    iVar2 = **(int **)(param_9 + 0xcc);
  }
  if ((iVar2 != *(int *)(param_9 + 0xd4)) && (*(int *)(param_9 + 0xd4) = iVar2, -1 < iVar2)) {
    pfVar6 = *(float **)(param_9 + 0xd4);
    sprintf(acStack_29 + 1,&DAT_8043bb90);
    sVar3 = strlen(acStack_29 + 1);
    if (sVar3 < 7) {
      sVar3 = strlen(acStack_29 + 1);
      uVar5 = (undefined1)sVar3;
    }
    else {
      uVar5 = 6;
    }
    *(undefined1 *)(param_9 + 0x13) = uVar5;
    iVar2 = param_9;
    for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
      iVar4 = (int)acStack_29[*(char *)(param_9 + 0x13) - iVar7];
      fVar1 = FLOAT_8043bb80;
      if ((0x2f < iVar4) && (iVar4 < 0x3a)) {
        uStack_1c = iVar4 - 0x30U ^ 0x80000000;
        local_20 = 0x43300000;
        fVar1 = (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8043bb98);
      }
      uVar8 = zz_00086b8_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb32c,*(int *)(iVar2 + 0xe0),pfVar6,param_12,param_13,param_14,
                          param_15,param_16);
      zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar2 + 0xe0),extraout_r4,pfVar6,param_12,param_13,param_14,param_15,
                  param_16);
      iVar2 = iVar2 + 4;
    }
  }
  return;
}



// ==== 801c4eb8  FUN_801c4eb8 ====

void FUN_801c4eb8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  
  if (-1 < *(int *)(param_9 + 0xd4)) {
    zz_00455fc_((float *)(*(int *)(param_9 + 0x8c) + 0x114),(float *)(param_9 + 0x114),
                (float *)(param_9 + 0x20));
    iVar4 = 0;
    iVar3 = param_9;
    for (iVar2 = 0; iVar2 < *(char *)(param_9 + 0x13); iVar2 = iVar2 + 1) {
      pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar4);
      zz_00455fc_((float *)(param_9 + 0x114),afStack_48,pfVar1);
      pfVar1 = pfVar1 + 3;
      uVar5 = zz_00456a0_(afStack_48,afStack_48,pfVar1);
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



// ==== 801c4f6c  FUN_801c4f6c ====

/* WARNING: Removing unreachable block (ram,0x801c5084) */
/* WARNING: Removing unreachable block (ram,0x801c4f7c) */

void FUN_801c4f6c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
                 float *param_11,undefined4 param_12,float param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 *extraout_r4;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  
  fVar1 = FLOAT_8043bc54;
  *(float *)(param_9 + 0x38) = FLOAT_8043bc4c;
  puVar5 = &DAT_8038554c;
  iVar6 = 0;
  dVar9 = (double)FLOAT_8043bbcc;
  *(float *)(param_9 + 0x3c) = FLOAT_8043bc50;
  dVar7 = (double)FLOAT_8043bba0;
  *(float *)(param_9 + 0x40) = fVar1;
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(param_9 + 0x38);
  *(undefined4 *)(param_9 + 0x68) = *(undefined4 *)(param_9 + 0x3c);
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(param_9 + 0x40);
  dVar8 = (double)*(float *)(param_9 + 0x68);
  *(float *)(param_9 + 0x68) = (float)(dVar8 + dVar7);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
  *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x3c);
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x40);
  *(undefined2 *)(param_9 + 0x1c) = 0;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    uVar2 = *(undefined4 *)(puVar5 + 4);
    param_10 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar6);
    *param_10 = *(undefined4 *)(puVar5 + 2);
    param_10[1] = uVar2;
    param_10[2] = *(undefined4 *)(puVar5 + 6);
    *(undefined2 *)(param_10 + 8) = *puVar5;
    *(undefined2 *)((int)param_10 + 0x22) = puVar5[1];
    param_10[6] = (float)dVar9;
    param_11 = (float *)(int)*(short *)(param_10 + 8);
    if (-1 < *(short *)(param_10 + 8)) {
      dVar8 = (double)zz_0006fb4_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  DAT_803bb32c,*(int *)(iVar4 + 0xe0),(int)param_11,param_12,
                                  param_13,param_14,param_15,param_16);
      param_10 = extraout_r4;
    }
    iVar6 = iVar6 + 0x24;
    puVar5 = puVar5 + 8;
    iVar4 = iVar4 + 4;
  }
  *(undefined1 *)(param_9 + 0x82) = 5;
  FUN_801c50a0(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801c50a0  FUN_801c50a0 ====

void FUN_801c50a0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,float param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  short sVar3;
  int iVar4;
  undefined4 extraout_r4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  undefined8 uVar10;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  undefined4 local_28;
  undefined4 local_24;
  longlong local_20;
  
  if (PTR_DAT_80435a30[0x149] == '\x03') {
    if (PTR_DAT_80435a30[0x43] == '\0') {
      local_2c = *(float *)(param_9 + 0x38);
      local_28 = *(undefined4 *)(param_9 + 0x3c);
      local_24 = *(undefined4 *)(param_9 + 0x40);
    }
    else {
      local_2c = *(float *)(param_9 + 100);
      local_28 = *(undefined4 *)(param_9 + 0x68);
      local_24 = *(undefined4 *)(param_9 + 0x6c);
    }
    local_38 = local_2c;
    local_34 = local_28;
    local_30 = local_24;
    param_12 = local_28;
    param_13 = local_2c;
    gnt4_PSVECSubtract_bl(&local_38,(float *)(param_9 + 0x20),&local_38);
    dVar9 = gnt4_PSVECMag_bl(&local_38);
    if ((double)FLOAT_8043bc58 < dVar9) {
      gnt4_PSVECNormalize_bl(&local_38,&local_38);
      gnt4_PSQUATScale_bl((double)FLOAT_8043bc58,&local_38,&local_38);
    }
    param_11 = (float *)(param_9 + 0x20);
    gnt4_PSVECAdd_bl(param_11,&local_38,param_11);
  }
  else {
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
    *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x3c);
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x40);
  }
  cVar1 = PTR_DAT_80435a30[0x149];
  if (cVar1 == '\x03') {
    *(float *)(param_9 + 0xd4) = FLOAT_8043bb80;
  }
  else if (cVar1 == '\x01') {
    *(float *)(param_9 + 0xd4) = FLOAT_8043bba4;
  }
  else if (cVar1 == '\x02') {
    *(float *)(param_9 + 0xd4) = FLOAT_8043bc5c;
  }
  else {
    *(float *)(param_9 + 0xd4) = FLOAT_8043bbcc;
  }
  sVar3 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar3;
  if (0x47 < sVar3) {
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  dVar9 = (double)*(float *)(param_9 + 0xd4);
  if ((double)FLOAT_8043bb80 <= dVar9) {
    iVar8 = 0;
    iVar7 = param_9;
    for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
      iVar5 = *(int *)(param_9 + 0x54) + iVar8;
      if (iVar6 == 2) {
        local_20 = (longlong)(int)*(float *)(param_9 + 0xd4);
        sVar3 = *(short *)(&DAT_80435a68 + (int)*(float *)(param_9 + 0xd4) * 2);
        param_11 = (float *)(int)sVar3;
        if (param_11 != (float *)(int)*(short *)(iVar5 + 0x20)) {
          *(float *)(iVar5 + 0x18) = FLOAT_8043bbcc;
          iVar2 = DAT_803bb32c;
          iVar4 = *(int *)(iVar7 + 0xe0);
          *(short *)(iVar5 + 0x20) = sVar3;
          dVar9 = (double)zz_0006fb4_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                      iVar2,iVar4,(int)param_11,param_12,param_13,param_14,param_15,
                                      param_16);
        }
      }
      iVar2 = DAT_803bb32c;
      if (iVar6 < 3) {
        dVar9 = (double)*(float *)(param_9 + 0xd4);
        if (dVar9 != (double)*(float *)(iVar5 + 0x18)) {
          iVar4 = *(int *)(iVar7 + 0xe0);
          *(float *)(iVar5 + 0x18) = *(float *)(param_9 + 0xd4);
          uVar10 = zz_00086b8_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                               iVar4,param_11,param_12,param_13,param_14,param_15,param_16);
          dVar9 = (double)zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,*(int *)(iVar7 + 0xe0),extraout_r4,param_11,param_12,param_13
                                      ,param_14,param_15,param_16);
        }
      }
      iVar8 = iVar8 + 0x24;
      iVar7 = iVar7 + 4;
    }
  }
  return;
}



// ==== 801c52dc  FUN_801c52dc ====

void FUN_801c52dc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  if (FLOAT_8043bb80 <= *(float *)(param_1 + 0xd4)) {
    dVar7 = (double)*(float *)(param_1 + 0x24);
    dVar8 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar7,dVar8,(float *)(param_1 + 0x114));
    iVar5 = 0;
    iVar4 = param_1;
    for (iVar3 = 0; iVar3 < *(char *)(param_1 + 0x13); iVar3 = iVar3 + 1) {
      if (((iVar3 < 5) || (*(short *)(param_1 + 0x1c) < 0x31)) &&
         ((iVar3 != 0 || (FLOAT_8043bb80 != *(float *)(param_1 + 0xd4))))) {
        pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
        pfVar1 = pfVar2;
        uVar6 = zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar2);
        if (iVar3 == 6) {
          pfVar1 = afStack_48;
          param_4 = 0xffff8000;
          uVar6 = zz_00457d4_('z',pfVar1,pfVar1,-0x8000);
        }
        zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),
                    afStack_48,(undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
        zz_00097b4_(*(int *)(iVar4 + 0xe0),(int)*(short *)((int)pfVar2 + 0x22));
      }
      iVar5 = iVar5 + 0x24;
      iVar4 = iVar4 + 4;
    }
  }
  return;
}



// ==== 801c53dc  FUN_801c53dc ====

/* WARNING: Removing unreachable block (ram,0x801c55e4) */
/* WARNING: Removing unreachable block (ram,0x801c55dc) */
/* WARNING: Removing unreachable block (ram,0x801c55d4) */
/* WARNING: Removing unreachable block (ram,0x801c53fc) */
/* WARNING: Removing unreachable block (ram,0x801c53f4) */
/* WARNING: Removing unreachable block (ram,0x801c53ec) */

void FUN_801c53dc(double param_1,double param_2,double param_3,float *param_4,float *param_5,
                 float *param_6,undefined4 param_7,undefined1 param_8,short *param_9)

{
  short sVar1;
  short sVar2;
  size_t sVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  double dVar7;
  short local_d8;
  short local_d6;
  short local_d4;
  short local_d2;
  short local_d0;
  short local_ce;
  short local_cc;
  short local_ca;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float afStack_7c [13];
  
  DAT_803c1160 = zz_0098214_();
  DAT_803c113c = afStack_7c;
  local_ac = (float)(-param_2 * (double)FLOAT_8043bbdc);
  local_a8 = (float)(param_2 * (double)FLOAT_8043bbdc);
  DAT_803c1140 = &local_ac;
  DAT_803c1150 = &local_c8;
  DAT_803c115c = &local_d8;
  DAT_803c116a = 4;
  DAT_803c1174 = (float)param_1;
  DAT_803c1170 = 1;
  DAT_803c1172 = 2;
  local_80 = FLOAT_8043bb80;
  local_8c = FLOAT_8043bb80;
  local_98 = FLOAT_8043bb80;
  local_a4 = FLOAT_8043bb80;
  local_bc = 0xffffffff;
  local_c0 = 0xffffffff;
  local_c4 = 0xffffffff;
  local_c8 = 0xffffffff;
  local_b8 = *param_5;
  local_b4 = param_5[1];
  local_b0 = param_5[2];
  DAT_803c1164 = param_7;
  DAT_803c1173 = param_8;
  local_a0 = local_a8;
  local_9c = local_a8;
  local_94 = local_ac;
  local_90 = local_ac;
  local_88 = local_a8;
  local_84 = local_ac;
  sVar3 = strlen((char *)param_9);
  dVar7 = (double)(float)(param_3 * (double)FLOAT_8043bbdc);
  for (iVar6 = 0; iVar6 < (int)(sVar3 >> 1); iVar6 = iVar6 + 1) {
    if (*param_9 != DAT_8043bc60) {
      iVar4 = zz_0097fbc_(*param_9);
      sVar5 = (short)iVar4;
      zz_00455fc_(param_4,afStack_7c,&local_b8);
      zz_00456a0_(afStack_7c,afStack_7c,param_6);
      iVar4 = (int)sVar5 / 10 + ((int)sVar5 >> 0x1f);
      sVar1 = (short)iVar4;
      sVar2 = (short)(iVar4 >> 0x1f);
      local_d8 = (sVar5 + (sVar1 - sVar2) * -10) * 0x18;
      local_d6 = (sVar1 - sVar2) * 0x18;
      local_d4 = local_d8 + 0x18;
      local_ce = local_d6 + 0x18;
      local_d2 = local_d6;
      local_d0 = local_d8;
      local_cc = local_d4;
      local_ca = local_ce;
      zz_0052214_(-0x7fc3eed0);
    }
    param_9 = param_9 + 1;
    local_b8 = (float)(dVar7 * (double)*param_6 + (double)local_b8);
  }
  return;
}



// ==== 801c5600  FUN_801c5600 ====

/* WARNING: Removing unreachable block (ram,0x801c5808) */
/* WARNING: Removing unreachable block (ram,0x801c5800) */
/* WARNING: Removing unreachable block (ram,0x801c57f8) */
/* WARNING: Removing unreachable block (ram,0x801c5620) */
/* WARNING: Removing unreachable block (ram,0x801c5618) */
/* WARNING: Removing unreachable block (ram,0x801c5610) */

void FUN_801c5600(double param_1,double param_2,double param_3,float *param_4,float *param_5,
                 float *param_6,undefined4 param_7,undefined1 param_8,short *param_9)

{
  short sVar1;
  short sVar2;
  size_t sVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  double dVar7;
  short local_d8;
  short local_d6;
  short local_d4;
  short local_d2;
  short local_d0;
  short local_ce;
  short local_cc;
  short local_ca;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  undefined4 local_bc;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float afStack_7c [13];
  
  DAT_803c1160 = zz_0098214_();
  DAT_803c113c = afStack_7c;
  local_ac = (float)(-param_2 * (double)FLOAT_8043bbdc);
  local_a0 = (float)(param_2 * (double)FLOAT_8043bbdc);
  DAT_803c1140 = &local_ac;
  DAT_803c1150 = &local_c8;
  DAT_803c115c = &local_d8;
  DAT_803c116a = 4;
  DAT_803c1174 = (float)param_1;
  DAT_803c1170 = 1;
  DAT_803c1172 = 2;
  local_84 = FLOAT_8043bb80;
  local_90 = FLOAT_8043bb80;
  local_9c = FLOAT_8043bb80;
  local_a8 = FLOAT_8043bb80;
  local_bc = 0xffffffff;
  local_c0 = 0xffffffff;
  local_c4 = 0xffffffff;
  local_c8 = 0xffffffff;
  local_b8 = *param_5;
  local_b4 = param_5[1];
  local_b0 = param_5[2];
  DAT_803c1164 = param_7;
  DAT_803c1173 = param_8;
  local_a4 = local_ac;
  local_98 = local_ac;
  local_94 = local_ac;
  local_8c = local_a0;
  local_88 = local_a0;
  local_80 = local_a0;
  sVar3 = strlen((char *)param_9);
  dVar7 = (double)(float)(param_3 * (double)FLOAT_8043bbdc);
  for (iVar6 = 0; iVar6 < (int)(sVar3 >> 1); iVar6 = iVar6 + 1) {
    if (*param_9 != DAT_8043bc60) {
      iVar4 = zz_0097fbc_(*param_9);
      sVar5 = (short)iVar4;
      zz_00455fc_(param_4,afStack_7c,&local_b8);
      zz_00456a0_(afStack_7c,afStack_7c,param_6);
      iVar4 = (int)sVar5 / 10 + ((int)sVar5 >> 0x1f);
      sVar1 = (short)iVar4;
      sVar2 = (short)(iVar4 >> 0x1f);
      local_d8 = (sVar5 + (sVar1 - sVar2) * -10) * 0x18;
      local_d6 = (sVar1 - sVar2) * 0x18;
      local_d4 = local_d8 + 0x18;
      local_ce = local_d6 + 0x18;
      local_d2 = local_d6;
      local_d0 = local_d8;
      local_cc = local_d4;
      local_ca = local_ce;
      zz_0052214_(-0x7fc3eed0);
    }
    param_9 = param_9 + 1;
    local_b8 = (float)(dVar7 * (double)*param_6 + (double)local_b8);
  }
  return;
}



// ==== 801c5824  zz_01c5824_ ====

void zz_01c5824_(void)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  
  puVar1 = (undefined4 *)&DAT_803855c0;
  iVar3 = 2;
  do {
    iVar2 = zz_01a7538_(0x2b,puVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = FUN_801c58bc;
      *(code **)(iVar2 + 0x10c) = FUN_801c5cd8;
      *(char *)(iVar2 + 0x12) = (char)(iVar3 / 2);
    }
    iVar3 = iVar3 + 1;
    puVar1 = puVar1 + 5;
  } while (iVar3 < 8);
  return;
}



// ==== 801c58bc  FUN_801c58bc ====

void FUN_801c58bc(int param_1)

{
  (*(code *)(&PTR_FUN_80385638)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801c58f8  FUN_801c58f8 ====

void FUN_801c58f8(int param_1)

{
  float fVar1;
  
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(undefined1 *)(param_1 + 0x84) = 0x1f;
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0,1);
  fVar1 = FLOAT_8043bc68;
  *(undefined2 *)(param_1 + 0x74) = 0;
  *(undefined2 *)(param_1 + 0x72) = 0;
  *(undefined2 *)(param_1 + 0x70) = 0;
  *(float *)(param_1 + 0x60) = fVar1;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  fVar1 = FLOAT_8043bc70;
  if (*(char *)(param_1 + 0x12) < '\x02') {
    fVar1 = FLOAT_8043bc6c;
  }
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined4 *)(param_1 + 0x180) = 0xffffffff;
  zz_01c5998_(param_1);
  return;
}



// ==== 801c5998  zz_01c5998_ ====

void zz_01c5998_(int param_1)

{
  (**(code **)(&DAT_80435a70 + *(char *)(param_1 + 0x19) * 4))();
  return;
}



// ==== 801c59d0  FUN_801c59d0 ====

void FUN_801c59d0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  
  iVar3 = DAT_80436354;
  cVar1 = *(char *)(param_9 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(int *)(DAT_80436354 + 0xa28) == 0) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      return;
    }
    iVar2 = (int)*(char *)(DAT_80436354 + *(char *)(param_9 + 0x12) + 0xa0c);
    if (*(int *)(param_9 + 0x180) == iVar2) {
      return;
    }
    uVar4 = 0xffffffff;
    if (iVar2 != 0) {
      uVar4 = 0;
      if ((((*(char *)(DAT_80436354 + 0xa10) != iVar2) &&
           (uVar4 = 1, *(char *)(DAT_80436354 + 0xa11) != iVar2)) &&
          (uVar4 = 2, *(char *)(DAT_80436354 + 0xa12) != iVar2)) &&
         (uVar4 = 3, *(char *)(DAT_80436354 + 0xa13) != iVar2)) {
        uVar4 = 4;
      }
      if (3 < uVar4) {
        return;
      }
    }
    *(int *)(param_9 + 0x180) = iVar2;
    zz_01c5cf8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar4,iVar3,
                param_12,param_13,param_14,param_15,param_16);
    *(char *)(param_9 + 0x1a) = *(char *)(param_9 + 0x1a) + '\x01';
    *(undefined1 *)(param_9 + 0x82) = 4;
    zz_0181fbc_(param_9);
  }
  iVar3 = zz_0181fd0_(param_9,0x10);
  if (iVar3 != 0) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined1 *)(param_9 + 0x1a) = 0;
    if (*(char *)(param_9 + 0x11) == '\0') {
      *(uint *)(DAT_80436354 + 0xa30) =
           *(uint *)(DAT_80436354 + 0xa30) & ~(1 << (int)*(char *)(param_9 + 0x12));
    }
  }
  dVar5 = zz_01820b0_(-(double)*(float *)(param_9 + 0x44),param_9);
  *(float *)(param_9 + 100) =
       (float)((double)(*(float *)(param_9 + 0x148) + *(float *)(param_9 + 0x44)) + dVar5);
  return;
}



// ==== 801c5b5c  FUN_801c5b5c ====

void FUN_801c5b5c(int param_1)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if ((*(int *)(DAT_80436354 + 0xa28) != 0) &&
       ((int)*(char *)(DAT_80436354 + *(char *)(param_1 + 0x12) + 0xa0c) ==
        *(int *)(param_1 + 0x180))) {
      return;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined4 *)(param_1 + 0x180) = 0xffffffff;
    *(undefined2 *)(DAT_80436354 + *(char *)(param_1 + 0x12) * 2 + 0xa14) = 0xffff;
    zz_0181fbc_(param_1);
  }
  iVar2 = zz_0181fd0_(param_1,0x10);
  if (iVar2 == 0) {
    dVar3 = zz_01820b0_((double)*(float *)(param_1 + 0x44),param_1);
    *(float *)(param_1 + 100) = (float)((double)*(float *)(param_1 + 0x148) + dVar3);
  }
  else {
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x82) = 0;
    if (*(char *)(param_1 + 0x11) == '\0') {
      if (*(char *)(DAT_80436354 + *(char *)(param_1 + 0x12) + 0xa0c) < '\0') {
        *(uint *)(DAT_80436354 + 0xa30) =
             *(uint *)(DAT_80436354 + 0xa30) & ~(1 << (int)*(char *)(param_1 + 0x12));
      }
      if (-1 < *(char *)(param_1 + 0x13)) {
        *(undefined1 *)(DAT_80436354 + *(char *)(param_1 + 0x13) + 0xa10) = 0xff;
      }
    }
  }
  return;
}



// ==== 801c5cb8  FUN_801c5cb8 ====

void FUN_801c5cb8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801c5cd8  FUN_801c5cd8 ====

void FUN_801c5cd8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801c5cf8  zz_01c5cf8_ ====

void zz_01c5cf8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  
  *(char *)(param_9 + 0x13) = (char)param_10;
  if (*(char *)(param_9 + 0x12) != '\0') {
    param_11 = 0x803c0000;
    *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(&DAT_803bb394 + param_10 * 8);
  }
  fVar1 = FLOAT_8043bc74;
  if ((*(char *)(param_9 + 0x12) == '\0') && (*(char *)(param_9 + 0x11) != '\0')) {
    *(undefined4 *)(param_9 + 0x174) = 1;
    *(float *)(param_9 + 0x178) = fVar1;
    zz_01a76c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0xff,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  else {
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801c5d78  zz_01c5d78_ ====

void zz_01c5d78_(void)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_80389f08; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(0x2c,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = FUN_801c5df8;
      *(code **)(iVar2 + 0x10c) = FUN_801c6180;
    }
  }
  return;
}



// ==== 801c5df8  FUN_801c5df8 ====

void FUN_801c5df8(int param_1)

{
  (*(code *)(&PTR_FUN_80389f58)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801c5e34  FUN_801c5e34 ====

void FUN_801c5e34(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  uVar2 = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043bc78;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  if (*(char *)(param_9 + 0x11) == '\x02') {
    *(undefined2 *)(param_9 + 0x74) = 0x2000;
  }
  zz_01a7688_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar2,param_12
              ,param_13,param_14,param_15,param_16);
  zz_01c5ecc_(param_9);
  return;
}



// ==== 801c5ecc  zz_01c5ecc_ ====

void zz_01c5ecc_(int param_1)

{
  char cVar1;
  bool bVar2;
  short sVar4;
  int iVar3;
  int iVar5;
  double dVar6;
  undefined4 local_18;
  
  if (*(char *)(param_1 + 0x11) != '\0') {
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + -0x100;
  }
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 != '\x04') {
        if ('\x03' < cVar1) {
          return;
        }
        if ((*(int *)(DAT_80436354 + 0xa28) != 0) && ((*(uint *)(DAT_80436354 + 0x18) & 0x100) == 0)
           ) {
          return;
        }
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(undefined4 *)(param_1 + 0x188) = 0;
        zz_0181fbc_(param_1);
      }
      iVar3 = zz_0181fd0_(param_1,0x10);
      if (iVar3 != 0) {
        *(undefined1 *)(param_1 + 0x1a) = 0;
        *(undefined1 *)(param_1 + 0x82) = 0;
        *(undefined4 *)(DAT_80436354 + 0xa24) = 0xffffffff;
        *(undefined4 *)(DAT_80436354 + 0xa30) = 0;
      }
      dVar6 = zz_01820b0_((double)FLOAT_8043bc80,param_1);
      *(float *)(param_1 + 100) = (float)((double)*(float *)(param_1 + 0x148) + dVar6);
      return;
    }
    if (cVar1 == '\0') {
      if (*(int *)(DAT_80436354 + 0xa28) == 0) {
        *(undefined1 *)(param_1 + 0x18) = 2;
        return;
      }
      if (*(int *)(DAT_80436354 + 0xa24) < 0) {
        return;
      }
      *(undefined1 *)(param_1 + 0x1a) = 1;
      zz_009749c_(0,*(int *)(DAT_80436354 + 0xa24),&local_18,(uint *)0x0);
      bVar2 = false;
      *(undefined1 *)(param_1 + 0x13) = (undefined1)local_18;
      iVar3 = 0;
      iVar5 = 2;
      do {
        if (-1 < *(short *)(DAT_80436354 + iVar3 + 0xa14)) {
          *(undefined2 *)(DAT_80436354 + iVar3 + 0xa14) = 0xffff;
          bVar2 = true;
        }
        if (-1 < *(short *)(DAT_80436354 + iVar3 + 0xa16)) {
          *(undefined2 *)(DAT_80436354 + iVar3 + 0xa16) = 0xffff;
          bVar2 = true;
        }
        if (-1 < *(short *)(DAT_80436354 + iVar3 + 0xa18)) {
          *(undefined2 *)(DAT_80436354 + iVar3 + 0xa18) = 0xffff;
          bVar2 = true;
        }
        if (-1 < *(short *)(DAT_80436354 + iVar3 + 0xa1a)) {
          *(undefined2 *)(DAT_80436354 + iVar3 + 0xa1a) = 0xffff;
          bVar2 = true;
        }
        iVar3 = iVar3 + 8;
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
      if (bVar2) {
        *(undefined2 *)(param_1 + 0x1c) = 0x12;
        return;
      }
    }
    else {
      if (cVar1 < '\0') {
        return;
      }
      sVar4 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar4;
      if (0 < sVar4) {
        return;
      }
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined4 *)(param_1 + 0x188) = 0;
    *(undefined1 *)(param_1 + 0x82) = 4;
    zz_0181fbc_(param_1);
    zz_00f03c0_(0,0x170);
  }
  iVar3 = zz_0181fd0_(param_1,0x10);
  if (iVar3 != 0) {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined4 *)(param_1 + 0x188) = 0xffffffff;
  }
  dVar6 = zz_01820b0_((double)FLOAT_8043bc80,param_1);
  *(float *)(param_1 + 100) =
       (float)((double)(FLOAT_8043bc7c + *(float *)(param_1 + 0x148)) + dVar6);
  return;
}



// ==== 801c6160  FUN_801c6160 ====

void FUN_801c6160(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801c6180  FUN_801c6180 ====

void FUN_801c6180(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  if ((*(int *)(param_9 + 0x188) != 0) && (-1 < *(int *)(DAT_80436354 + 0xa24))) {
    cVar1 = *(char *)(param_9 + 0x13);
    zz_0096d0c_((double)FLOAT_8043bc84);
    zz_0096d14_((double)FLOAT_8043bc88);
    zz_00970b4_((short)((cVar1 * -0xb + 0x280) / 2),0x8c,7,'\0',
                (short)*(undefined4 *)(DAT_80436354 + 0xa24),*(int *)(param_9 + 0x188));
  }
  return;
}



// ==== 801c621c  zz_01c621c_ ====

void zz_01c621c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x106) || (*(short *)(param_1 + 1000) == 0x107)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_801c632c;
    *(code **)(puVar1 + 0x10c) = FUN_801c6628;
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



// ==== 801c632c  FUN_801c632c ====

void FUN_801c632c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80389fb8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801c6380  FUN_801c6380 ====

void FUN_801c6380(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  float *pfVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  undefined8 uVar8;
  
  iVar6 = *(byte *)(param_9 + 0x18) + 1;
  *(char *)(param_9 + 0x18) = (char)iVar6;
  iVar7 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar4 = *(char *)(param_9 + 0x11) * 0x14;
  uVar8 = zz_0089100_(param_9,(int)*(char *)(iVar7 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x55;
  fVar1 = FLOAT_8043bc90;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80389f6a + iVar4);
  uVar2 = *(undefined4 *)(&DAT_80389f74 + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80389f70 + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80389f78 + iVar4);
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x72) = *(undefined2 *)(&DAT_80389f6e + iVar4);
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(char *)(param_9 + 0x13) = (char)*(undefined2 *)(&DAT_80389f6c + iVar4);
  iVar7 = zz_0006f98_(iVar7);
  iVar5 = iVar7 + 0xc28;
  pfVar3 = (float *)(int)*(short *)(&DAT_80389f68 + iVar4);
  zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar7 + 0x600),
              *(int *)(param_9 + 0xe0),(int)pfVar3,iVar5,iVar6,in_r8,in_r9,in_r10);
  uVar8 = zz_00086b8_((double)FLOAT_8043bc90,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                      ,*(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe0),pfVar3,iVar5,iVar6,in_r8,
                      in_r9,in_r10);
  uVar8 = zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),extraout_r4,pfVar3,iVar5,iVar6,in_r8,in_r9,in_r10);
  iVar5 = iVar7 + 0xc28;
  pfVar3 = (float *)(int)*(short *)(&DAT_80389f68 + iVar4);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe4),(int)pfVar3,iVar5,iVar6,in_r8
                      ,in_r9,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4_00,pfVar3,iVar5,iVar6,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043bc94,*(int *)(param_9 + 0xe4));
  uVar8 = zz_00086b8_((double)FLOAT_8043bc90,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                      ,*(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe4),pfVar3,iVar5,iVar6,in_r8,
                      in_r9,in_r10);
  uVar8 = zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe4),extraout_r4_01,pfVar3,iVar5,iVar6,in_r8,in_r9,in_r10)
  ;
  *(byte *)(param_9 + 0x82) = *(byte *)(param_9 + 0x96) + 0x41;
  zz_01c64e0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
              (uint)*(byte *)(param_9 + 0x96),pfVar3,iVar5,iVar6,in_r8,in_r9,in_r10);
  return;
}



// ==== 801c64e0  zz_01c64e0_ ====

void zz_01c64e0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  undefined4 extraout_r4;
  int iVar4;
  undefined8 uVar5;
  
  iVar4 = *(int *)(param_9 + 0x90);
  uVar5 = zz_0007c30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),param_10,param_11,param_12,param_13,param_14,param_15
                      ,param_16);
  zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  fVar2 = FLOAT_8043bc9c;
  *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x58) + FLOAT_8043bc98;
  if (fVar2 < *(float *)(param_9 + 0x58)) {
    *(float *)(param_9 + 0x58) = fVar2;
  }
  fVar2 = FLOAT_8043bc90;
  uVar3 = 1 << (int)*(char *)(param_9 + 0x13);
  if (((int)(char)*(byte *)(iVar4 + 0x15b) & uVar3) != 0) {
    *(byte *)(iVar4 + 0x15b) = *(byte *)(iVar4 + 0x15b) & ~(byte)uVar3;
    *(float *)(param_9 + 0x58) = fVar2;
  }
  cVar1 = *(char *)(param_9 + 0x11);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if ((cVar1 < '\x04') && (*(short *)(iVar4 + 0x784) < 1)) {
        *(float *)(param_9 + 0x58) = FLOAT_8043bc90;
      }
      goto LAB_801c65d4;
    }
    if (cVar1 != '\0') {
      if ((-1 < cVar1) && (*(short *)(iVar4 + 0x774) < 2)) {
        *(float *)(param_9 + 0x58) = FLOAT_8043bc90;
      }
      goto LAB_801c65d4;
    }
  }
  if (*(short *)(iVar4 + 0x774) < 1) {
    *(float *)(param_9 + 0x58) = FLOAT_8043bc90;
  }
LAB_801c65d4:
  *(undefined4 *)(param_9 + 0x60) = *(undefined4 *)(param_9 + 0x58);
  *(undefined4 *)(param_9 + 0x5c) = *(undefined4 *)(param_9 + 0x58);
  return;
}



// ==== 801c6608  FUN_801c6608 ====

void FUN_801c6608(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801c6628  FUN_801c6628 ====

void FUN_801c6628(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') &&
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) != '\x04')) {
    iVar1 = *(int *)(param_9 + 0xe0);
    uVar2 = 1;
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
    uVar2 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,uVar2);
  return;
}



// ==== 801c66a0  zz_01c66a0_ ====

void zz_01c66a0_(int param_1,undefined1 param_2,char *param_3)

{
  undefined1 uVar1;
  size_t sVar2;
  
  DAT_80436388 = &DAT_803d5d00;
  gnt4_memset(&DAT_803d5d00,0,0x74);
  DAT_80436388[0x60] = (char)param_1;
  DAT_80436388[0x61] = param_2;
  *(char **)(DAT_80436388 + 0x14) = param_3;
  strcpy(DAT_80436388 + 0x18,param_3);
  sVar2 = strlen(param_3);
  uVar1 = (undefined1)(sVar2 >> 1);
  DAT_80436388[0x6f] = uVar1;
  DAT_80436388[0x70] = uVar1;
  DAT_80436388[0x69] = (&DAT_80435a78)[param_1 * 2];
  DAT_80436388[0x67] = *(undefined1 *)(param_1 * 2 + -0x7fbca587);
  gnt4_memcpy(DAT_80436388 + 0x6a,DAT_80435a7c,2);
  FUN_80181e78();
  return;
}



// ==== 801c677c  zz_01c677c_ ====

int zz_01c677c_(void)

{
  *(undefined4 *)(DAT_80436388 + 8) = (&DAT_803c71fc)[DAT_80436388[0x61] * 8];
  *(undefined4 *)(DAT_80436388 + 0xc) = (&DAT_803c7204)[DAT_80436388[0x61] * 8];
  *(uint *)(DAT_80436388 + 0x10) =
       *(uint *)(DAT_80436388 + 0xc) | (&DAT_803c720c)[DAT_80436388[0x61] * 8];
  (*(code *)(&PTR_FUN_8038a09c)[*DAT_80436388])();
  return (int)DAT_80436388[0x62];
}



// ==== 801c6828  FUN_801c6828 ====

void FUN_801c6828(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  char *pcVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  
  pcVar2 = DAT_80436388;
  cVar1 = DAT_80436388[1];
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      goto LAB_801c68bc;
    }
    if (cVar1 < '\0') {
      return;
    }
    DAT_80436388[1] = cVar1 + '\x01';
    zz_004437c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (int)DAT_80436388[0x60],pcVar2,param_11,param_12,param_13,param_14,param_15,param_16
               );
  }
  iVar4 = zz_000a3c4_();
  if (iVar4 != 0) {
    return;
  }
  zz_01c6ea8_();
  fVar3 = FLOAT_8043bca0;
  DAT_80436388[1] = DAT_80436388[1] + '\x01';
  pcVar2 = DAT_80436388;
  pcVar2[4] = '\0';
  pcVar2[5] = '\0';
  *(float *)(DAT_80436388 + 0x5c) = fVar3;
  DAT_80436388[0x68] = '\0';
LAB_801c68bc:
  iVar4 = zz_0182040_((short *)(DAT_80436388 + 4),(float *)(DAT_80436388 + 0x5c),0x20);
  if (iVar4 != 0) {
    *DAT_80436388 = *DAT_80436388 + '\x01';
    DAT_80436388[1] = '\0';
    DAT_80436388[100] = '\x01';
  }
  dVar5 = zz_01820c4_((double)*(float *)(DAT_80436388 + 0x5c),(double)FLOAT_8043bca8);
  *(float *)(DAT_80436388 + 0x58) = (float)((double)FLOAT_8043bca4 + dVar5);
  DAT_80436388[0x68] = DAT_80436388[0x68] + '\x05';
  return;
}



// ==== 801c6940  FUN_801c6940 ====

void FUN_801c6940(void)

{
  char cVar1;
  char cVar2;
  int iVar3;
  char cVar4;
  char *pcVar5;
  size_t __n;
  uint uVar6;
  char *pcVar7;
  int iVar8;
  
  cVar4 = DAT_80436388[0x71];
  cVar1 = DAT_80436388[0x6d];
  cVar2 = DAT_80436388[0x6e];
  DAT_80436388[0x71] = cVar4 + '\x01';
  if ('\x1e' < (char)(cVar4 + '\x01')) {
    DAT_80436388[0x71] = '\0';
  }
  uVar6 = *(uint *)(DAT_80436388 + 0xc);
  if ((uVar6 & 0x1000) == 0) {
    if ((uVar6 & 0x100) == 0) {
      if ((uVar6 & 0x200) == 0) {
        uVar6 = *(uint *)(DAT_80436388 + 0x10);
        if ((uVar6 & 0x40) == 0) {
          if ((uVar6 & 0x20) == 0) {
            if ((uVar6 & 0x20002) == 0) {
              if ((uVar6 & 0x10001) == 0) {
                if ((uVar6 & 0x40004) == 0) {
                  if ((uVar6 & 0x80008) == 0) goto LAB_801c6cb8;
                  iVar8 = cVar2 + 6;
                  iVar3 = iVar8 / 7 + (iVar8 >> 0x1f);
                  cVar4 = (char)iVar8 + ((char)iVar3 - (char)(iVar3 >> 0x1f)) * -7;
                }
                else {
                  iVar8 = cVar2 + 1;
                  iVar3 = iVar8 / 7 + (iVar8 >> 0x1f);
                  cVar4 = (char)iVar8 + ((char)iVar3 - (char)(iVar3 >> 0x1f)) * -7;
                }
                DAT_80436388[0x71] = '\0';
                DAT_80436388[0x6e] = cVar4;
                zz_01c6e08_();
                goto LAB_801c6cb8;
              }
              iVar8 = cVar1 + 0xe;
              iVar3 = iVar8 / 0xf + (iVar8 >> 0x1f);
              cVar4 = (char)iVar8 + ((char)iVar3 - (char)(iVar3 >> 0x1f)) * -0xf;
            }
            else {
              iVar8 = cVar1 + 1;
              iVar3 = iVar8 / 0xf + (iVar8 >> 0x1f);
              cVar4 = (char)iVar8 + ((char)iVar3 - (char)(iVar3 >> 0x1f)) * -0xf;
            }
            DAT_80436388[0x6d] = cVar4;
            DAT_80436388[0x71] = '\0';
            zz_01c6e08_();
            goto LAB_801c6cb8;
          }
          if ((DAT_80436388[0x69] <= DAT_80436388[0x6f]) ||
             (DAT_80436388[0x6f] <= DAT_80436388[0x70])) goto LAB_801c6cb8;
          DAT_80436388[0x70] = DAT_80436388[0x70] + '\x01';
        }
        else {
          if ((DAT_80436388[0x69] <= DAT_80436388[0x6f]) || (DAT_80436388[0x70] == '\0'))
          goto LAB_801c6cb8;
          DAT_80436388[0x70] = DAT_80436388[0x70] + -1;
        }
        DAT_80436388[0x71] = '\0';
        zz_01c6e08_();
      }
      else if (DAT_80436388[0x70] != '\0') {
        pcVar5 = DAT_80436388 + DAT_80436388[0x70] * 2 + 0x18;
        __n = strlen(pcVar5);
        gnt4_memcpy(pcVar5 + -2,pcVar5,__n);
        DAT_80436388[0x70] = DAT_80436388[0x70] + -1;
        DAT_80436388[0x6f] = DAT_80436388[0x6f] + -1;
        DAT_80436388[0x71] = '\0';
        zz_01c6e58_();
      }
    }
    else if ((int)DAT_80436388[0x6f] < (int)DAT_80436388[0x69]) {
      pcVar5 = DAT_80436388 + DAT_80436388[0x70] * 2 + 0x18;
      for (pcVar7 = DAT_80436388 + DAT_80436388[0x6f] * 2 + 0x18; pcVar5 != pcVar7;
          pcVar7 = pcVar7 + -2) {
        *pcVar7 = pcVar7[-2];
        pcVar7[1] = pcVar7[-1];
      }
      gnt4_memcpy(pcVar5,DAT_80436388 + 0x6a,2);
      DAT_80436388[0x70] = DAT_80436388[0x70] + '\x01';
      DAT_80436388[0x6f] = DAT_80436388[0x6f] + '\x01';
      DAT_80436388[0x71] = '\0';
      zz_01c6e30_();
    }
  }
  else {
    if (DAT_80436388[0x6f] == '\0') {
      zz_01c6e80_();
      return;
    }
    *DAT_80436388 = *DAT_80436388 + '\x01';
    DAT_80436388[0x66] = '\x01';
    DAT_80436388[0x71] = '\x1e';
    DAT_80436388[DAT_80436388[0x6f] * 2 + 0x18] = '\0';
    strcpy(*(char **)(DAT_80436388 + 0x14),DAT_80436388 + 0x18);
    zz_01c6e30_();
  }
LAB_801c6cb8:
  gnt4_memcpy(DAT_80436388 + 0x6a,
              (void *)((&DAT_80435a7c)[DAT_80436388[0x65]] +
                      ((int)DAT_80436388[0x6d] + DAT_80436388[0x6e] * 0xf) * 2),2);
  return;
}



// ==== 801c6d10  FUN_801c6d10 ====

void FUN_801c6d10(void)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  cVar1 = *(char *)(DAT_80436388 + 1);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      zz_00443ec_();
      *(undefined1 *)(DAT_80436388 + 0x62) = 1;
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(char *)(DAT_80436388 + 0x66) == '\x01') {
      return;
    }
    *(char *)(DAT_80436388 + 1) = cVar1 + '\x01';
    fVar2 = FLOAT_8043bca0;
    *(undefined2 *)(DAT_80436388 + 4) = 0;
    *(float *)(DAT_80436388 + 0x5c) = fVar2;
    *(undefined1 *)(DAT_80436388 + 0x68) = 0xa0;
  }
  iVar3 = zz_0182040_((short *)(DAT_80436388 + 4),(float *)(DAT_80436388 + 0x5c),0x20);
  if (iVar3 != 0) {
    *(char *)(DAT_80436388 + 1) = *(char *)(DAT_80436388 + 1) + '\x01';
    *(undefined1 *)(DAT_80436388 + 99) = 0;
  }
  dVar4 = zz_01820c4_((double)*(float *)(DAT_80436388 + 0x5c),(double)FLOAT_8043bca4);
  *(float *)(DAT_80436388 + 0x58) = (float)dVar4;
  *(char *)(DAT_80436388 + 0x68) = *(char *)(DAT_80436388 + 0x68) + -5;
  return;
}



// ==== 801c6e08  zz_01c6e08_ ====

void zz_01c6e08_(void)

{
  zz_00f036c_(0,0x77);
  return;
}



// ==== 801c6e30  zz_01c6e30_ ====

void zz_01c6e30_(void)

{
  zz_00f036c_(0,0x7a);
  return;
}



// ==== 801c6e58  zz_01c6e58_ ====

void zz_01c6e58_(void)

{
  zz_00f036c_(0,0x7b);
  return;
}



// ==== 801c6e80  zz_01c6e80_ ====

void zz_01c6e80_(void)

{
  zz_00f036c_(0,0x7d);
  return;
}



// ==== 801c6ea8  zz_01c6ea8_ ====

void zz_01c6ea8_(void)

{
  int *piVar1;
  
  piVar1 = &DAT_8038a0a8;
  if (*(char *)(DAT_80436388 + 0x60) == '\x01') {
    zz_01c7798_(4);
    piVar1 = &DAT_8038a0a8;
  }
  else {
    zz_01c7798_(3);
  }
  for (; -1 < *piVar1; piVar1 = piVar1 + 5) {
    zz_01c6f24_(piVar1);
  }
  *(undefined1 *)(DAT_80436388 + 99) = 1;
  return;
}



// ==== 801c6f24  zz_01c6f24_ ====

void zz_01c6f24_(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  puVar2 = zz_008893c_(2,(int)*(char *)(DAT_80436388 + 0x67),1,1);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x10] = 0;
    puVar2[0x11] = (char)param_1[1];
    *(code **)(puVar2 + 0xc) = FUN_801c6fdc;
    *(code **)(puVar2 + 0x10c) = FUN_801c7758;
    *(undefined4 *)(puVar2 + 0x144) = *param_1;
    uVar1 = param_1[2];
    *(undefined4 *)(puVar2 + 100) = uVar1;
    *(undefined4 *)(puVar2 + 0x148) = uVar1;
    uVar1 = param_1[3];
    *(undefined4 *)(puVar2 + 0x68) = uVar1;
    *(undefined4 *)(puVar2 + 0x14c) = uVar1;
    uVar1 = param_1[4];
    *(undefined4 *)(puVar2 + 0x6c) = uVar1;
    *(undefined4 *)(puVar2 + 0x150) = uVar1;
    *(undefined4 *)(puVar2 + 0x154) = DAT_803bb33c;
  }
  return;
}



// ==== 801c6fdc  FUN_801c6fdc ====

void FUN_801c6fdc(int param_1)

{
  (*(code *)(&PTR_FUN_8038a2ec)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801c7018  FUN_801c7018 ====

void FUN_801c7018(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  uVar2 = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043bcb0;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  if (*(char *)(DAT_80436388 + 0x60) == '\0') {
    if (*(int *)(param_9 + 0x144) == 3) {
      *(undefined4 *)(param_9 + 0x144) = 0x1b;
    }
    if (*(int *)(param_9 + 0x144) == 4) {
      *(undefined4 *)(param_9 + 0x144) = 0x1c;
    }
  }
  zz_01a7688_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar2,param_12
              ,param_13,param_14,param_15,param_16);
  fVar1 = FLOAT_8043bcb0;
  *(undefined4 *)(param_9 + 0x174) = 1;
  *(float *)(param_9 + 0x178) = fVar1;
  *(undefined1 *)(param_9 + 0x82) = 7;
  zz_01c70ec_(param_9);
  return;
}



// ==== 801c70ec  zz_01c70ec_ ====

void zz_01c70ec_(int param_1)

{
  (*(code *)(&PTR_LAB_8038a2fc)[*(char *)(param_1 + 0x11)])();
  *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x14c) + *(float *)(DAT_80436388 + 0x58);
  if (*(char *)(DAT_80436388 + 99) == '\0') {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801c716c  FUN_801c716c ====

void FUN_801c716c(int param_1)

{
  char cVar1;
  uint uVar2;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    uVar2 = zz_00055fc_();
    *(short *)(param_1 + 0x74) = (short)(uVar2 << 8);
  }
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + -0x100;
  return;
}



// ==== 801c71d4  FUN_801c71d4 ====

void FUN_801c71d4(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      goto LAB_801c7248;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  if (*(char *)(DAT_80436388 + 100) == '\0') {
    return;
  }
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)(param_1 + 0x82) = 7;
LAB_801c7248:
  zz_01c725c_(param_1);
  return;
}



// ==== 801c725c  zz_01c725c_ ====

void zz_01c725c_(int param_1)

{
  char cVar1;
  uint uVar2;
  float fVar3;
  int iVar4;
  short sVar5;
  double dVar6;
  double dVar7;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + 1;
      dVar6 = zz_0045238_(*(short *)(param_1 + 0x1e) << 10);
      fVar3 = FLOAT_8043bcb0 - (float)((double)FLOAT_8043bcc0 * -dVar6);
      *(float *)(param_1 + 0x58) = FLOAT_8043bcb0 + (float)((double)FLOAT_8043bcc0 * -dVar6);
      *(float *)(param_1 + 0x5c) = fVar3;
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    *(undefined2 *)(param_1 + 0x1e) = 0;
  }
  uVar2 = (int)*(short *)(param_1 + 0x1e) << 0xe;
  iVar4 = (int)uVar2 / 0x18 + ((int)(uVar2 | (uint)(int)*(short *)(param_1 + 0x1e) >> 0x12) >> 0x1f)
  ;
  dVar7 = zz_0045204_((short)iVar4 - (short)(iVar4 >> 0x1f));
  dVar6 = (double)FLOAT_8043bcbc;
  *(float *)(param_1 + 0x58) = (float)((double)FLOAT_8043bcb8 * dVar7 + (double)FLOAT_8043bcb4);
  *(float *)(param_1 + 0x5c) = (float)(dVar6 * dVar7);
  sVar5 = *(short *)(param_1 + 0x1e) + 1;
  *(short *)(param_1 + 0x1e) = sVar5;
  if (0x17 < sVar5) {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined2 *)(param_1 + 0x1e) = 0;
  }
  return;
}



// ==== 801c7370  FUN_801c7370 ====

void FUN_801c7370(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if (cVar1 < '\x03') {
        sVar2 = *(short *)(param_9 + 0x1e) + -1;
        *(short *)(param_9 + 0x1e) = sVar2;
        if (sVar2 < 1) {
          *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
          *(undefined1 *)(DAT_80436388 + 0x66) = 2;
        }
        *(float *)(param_9 + 0x178) =
             (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1e) ^ 0x80000000) -
                    DOUBLE_8043bcd0) * FLOAT_8043bcc4;
      }
      goto LAB_801c7474;
    }
    if ((cVar1 < '\0') || (*(char *)(DAT_80436388 + 0x66) == '\0')) goto LAB_801c7474;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 0x1e;
  }
  sVar2 = *(short *)(param_9 + 0x1c) + -1;
  *(short *)(param_9 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined2 *)(param_9 + 0x1e) = 0x10;
  }
  uVar3 = 0xffffffff;
  if ((*(ushort *)(param_9 + 0x1c) & 4) != 0) {
    uVar3 = 0x888888ff;
  }
  zz_01a76c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar3,param_11
              ,param_12,param_13,param_14,param_15,param_16);
LAB_801c7474:
  zz_01a7668_(param_9,0x96);
  zz_01a76fc_((double)((float)((double)CONCAT44(0x43300000,*(uint *)(param_9 + 0x170) ^ 0x80000000)
                              - DOUBLE_8043bcd0) / FLOAT_8043bcc8),DOUBLE_8043bcd0,param_3,param_4,
              param_5,param_6,param_7,param_8,param_9,0,param_11,param_12,param_13,param_14,param_15
              ,param_16);
  return;
}



// ==== 801c7550  FUN_801c7550 ====

void FUN_801c7550(int param_1)

{
  zz_01a7668_(param_1,0x3c);
  if ((*(byte *)(param_1 + 0x11) & 1) ==
      ((int)*(uint *)(param_1 + 0x170) >> 0x1f) + (uint)(0x1d < *(uint *)(param_1 + 0x170))) {
    *(undefined1 *)(param_1 + 0x82) = 7;
  }
  else {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801c75d0  FUN_801c75d0 ====

void FUN_801c75d0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801c75f0  zz_01c75f0_ ====

void zz_01c75f0_(void)

{
  void *__src;
  int iVar1;
  short sVar2;
  short sVar3;
  byte abStack_18 [2];
  undefined1 local_16;
  
  if (*(char *)(DAT_80436388 + 0x66) != '\x02') {
    sVar3 = *(short *)(&DAT_8038a37c + *(char *)(DAT_80436388 + 0x6d) * 2);
    sVar2 = *(short *)(&DAT_8038a39c + *(char *)(DAT_80436388 + 0x6e) * 2);
    zz_0096d0c_((double)FLOAT_8043bcd8);
    zz_0097144_(sVar3 + 9,sVar2 + -1,6,(byte *)(DAT_80436388 + 0x6a));
    zz_0096d0c_((double)FLOAT_8043bcdc);
    sVar3 = 0xd1;
    if (*(char *)(DAT_80436388 + 0x60) != '\0') {
      sVar3 = 0x85;
    }
    local_16 = 0;
    __src = (void *)(DAT_80436388 + 0x18);
    iVar1 = 0;
    sVar2 = sVar3;
    while( true ) {
      if (*(char *)(DAT_80436388 + 0x6f) <= iVar1) break;
      gnt4_memcpy(abStack_18,__src,2);
      zz_0097144_(sVar2,0x5a,5,abStack_18);
      __src = (void *)((int)__src + 2);
      sVar2 = sVar2 + 0x13;
      iVar1 = iVar1 + 1;
    }
    if (((int)*(char *)(DAT_80436388 + 0x6f) < (int)*(char *)(DAT_80436388 + 0x69)) &&
       (*(char *)(DAT_80436388 + 0x71) < '\x14')) {
      zz_0097144_(sVar3 + *(char *)(DAT_80436388 + 0x70) * 0x13,0x5a,5,&DAT_8043bce0);
    }
    zz_0096d0c_((double)FLOAT_8043bcb0);
  }
  return;
}



// ==== 801c7758  FUN_801c7758 ====

void FUN_801c7758(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  
  if (*(char *)(param_9 + 0x11) == '\x02') {
    param_1 = zz_01c75f0_();
    param_10 = extraout_r4;
  }
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801c7798  zz_01c7798_ ====

void zz_01c7798_(undefined1 param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x39,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x11] = param_1;
    *(code **)(puVar1 + 0xc) = FUN_801c7800;
    *(code **)(puVar1 + 0x10c) = FUN_801c7840;
  }
  return;
}



// ==== 801c7800  FUN_801c7800 ====

void FUN_801c7800(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(char *)(DAT_80436388 + 99) == '\0') {
    zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  else {
    param_9[0x82] = param_9[0x11] + '\x01';
  }
  return;
}



// ==== 801c7840  FUN_801c7840 ====

void FUN_801c7840(void)

{
  uRam80435a87 = *(undefined1 *)(DAT_80436388 + 0x68);
  DAT_803c1140 = &DAT_8038a3ac;
  DAT_803c1144 = 0;
  DAT_803c1150 = &DAT_80435a84;
  DAT_803c1154 = &DAT_80435a80;
  DAT_803c1164 = 3;
  DAT_803c1168 = 0xf;
  DAT_803c1170 = 1;
  FUN_80051998(-0x7fc3eed0);
  return;
}



// ==== 801c78b0  zz_01c78b0_ ====

void zz_01c78b0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  undefined8 uVar1;
  
  gnt4_memset(&DAT_803d5d78,0,0x6c);
  DAT_803d5d90 = 0;
  DAT_803d5de0 = 0;
  uVar1 = zz_0009f40_();
  zz_0009e08_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  PTR_DAT_80433930[0x32] = 0;
  return;
}



// ==== 801c7908  zz_01c7908_ ====

undefined4 zz_01c7908_(void)

{
  (**(code **)(&DAT_80435a88 + DAT_803d5d78 * 4))();
  PTR_DAT_8043393c[0x14] = DAT_803d5de0;
  return DAT_803d5d90;
}



// ==== 801c795c  FUN_801c795c ====

void FUN_801c795c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,char *param_9)

{
  undefined *puVar1;
  int iVar2;
  undefined1 uVar3;
  byte bVar4;
  undefined4 extraout_r4;
  float *pfVar5;
  float *pfVar6;
  int iVar7;
  undefined2 *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined8 uVar12;
  
  *param_9 = *param_9 + '\x01';
  param_9[1] = '\0';
  zz_01c7dc4_(0);
  zz_002a5f4_(0,0,0,0);
  zz_0027c1c_();
  gnt4_memset(PTR_DAT_80433934,0,0x18b8);
  puVar8 = &DAT_8038a4ec;
  iVar10 = 0;
  iVar9 = 0;
  iVar11 = 3;
  do {
    *(undefined2 *)(PTR_DAT_80433934 + iVar9 + 0x10) = *puVar8;
    uVar3 = 0xff;
    PTR_DAT_80433934[iVar10 + 0xa0] = -(iVar10 - 2U < 0x7ffffffe);
    if (iVar10 < 2) {
      uVar3 = 0;
    }
    PTR_DAT_80433934[iVar10 + 0xcb] = uVar3;
    pfVar6 = (float *)PTR_DAT_80433934;
    iVar7 = (int)(short)puVar8[1];
    *(undefined2 *)(PTR_DAT_80433934 + iVar9 + 0x12) = puVar8[1];
    bVar4 = 0xff;
    PTR_DAT_80433934[iVar10 + 0xa1] = -(iVar10 - 1U < 0x7ffffffe);
    if (iVar10 + 1 < 2) {
      bVar4 = (byte)(iVar10 + 1) & 1;
    }
    iVar2 = iVar10 + 0xcc;
    iVar9 = iVar9 + 4;
    iVar10 = iVar10 + 2;
    PTR_DAT_80433934[iVar2] = bVar4;
    puVar8 = puVar8 + 2;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  zz_0197854_(1);
  pfVar5 = (float *)0x0;
  zz_0088398_(DAT_80436238 + 0xfe800,0xe0000,0);
  zz_00536b0_(DAT_803c71dc);
  PTR_DAT_80433934[0x1c] = 0x11;
  zz_0087718_(DAT_803c71e0);
  zz_000bb70_();
  uVar12 = zz_007fd5c_();
  zz_007fd6c_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_801c7d70,0,pfVar5,
              pfVar6,iVar7,puVar8,iVar9,iVar10);
  zz_00059b8_();
  PTR_DAT_80433934[0x1d] = 0;
  zz_00429ec_();
  uVar12 = zz_0042874_();
  zz_0042878_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  uVar12 = set_global_menu_mode(1);
  puVar1 = PTR_DAT_80433934;
  PTR_DAT_80433934[0x45] = 4;
  zz_00424cc_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1,extraout_r4,
              (undefined *)pfVar5,pfVar6,iVar7,puVar8,iVar9,iVar10);
  zz_0040940_();
  uVar12 = zz_003d4a0_();
  uVar12 = zz_00414ec_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
  uVar12 = zz_00414ec_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1);
  zz_0042a58_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_0197c00_();
  uVar12 = zz_01c84a8_();
  *(undefined **)(param_9 + 0x20) = &DAT_8038a3ec;
  param_9[0x2d] = '\0';
  sndSeqContinue(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,
                 &DAT_8038a3ec,pfVar5,pfVar6,iVar7,puVar8,iVar9,iVar10);
  return;
}



// ==== 801c7b68  sndSeqContinue ====

void sndSeqContinue(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                   double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                   float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
                   undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  uVar1 = zz_01c7de4_(param_9);
  zz_01c7ba0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
              param_11,param_12,param_13,param_14,param_15,param_16);
  zz_01c7cf4_();
  return;
}



// ==== 801c7ba0  zz_01c7ba0_ ====

void zz_01c7ba0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float *pfVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar3;
  undefined4 extraout_r4_02;
  double dVar4;
  
  zz_0089a94_(0x28);
  zz_0089a94_(0x20);
  if (*(char *)(param_9 + 0x3e) != '\0') {
    zz_0057ad0_();
  }
  zz_0087cf0_();
  zz_0089a94_(0);
  zz_0089a94_(0x10);
  zz_0089a94_(8);
  zz_0089a94_(0x18);
  zz_0089554_();
  zz_008972c_();
  zz_0053a94_();
  dVar4 = (double)zz_0040b94_();
  uVar3 = extraout_r4;
  if (*(char *)(param_9 + 0x3c) != '\0') {
    if (*(char *)(param_9 + 0x3c) < '\0') {
      *(undefined1 *)(param_9 + 0x3c) = 1;
    }
    else {
      *(float *)(param_9 + 0x30) = *(float *)(param_9 + 0x30) + *(float *)(param_9 + 0x38);
      if (*(float *)(param_9 + 0x34) <= *(float *)(param_9 + 0x30)) {
        *(float *)(param_9 + 0x30) = *(float *)(param_9 + 0x34);
        *(undefined1 *)(param_9 + 0x3c) = 0;
      }
      dVar4 = (double)zz_00088a4_((double)*(float *)(param_9 + 0x30),param_2,param_3,param_4,param_5
                                  ,param_6,param_7,param_8,*(int *)(param_9 + 0x24),extraout_r4,
                                  param_11,param_12,param_13,param_14,param_15,param_16);
      uVar3 = extraout_r4_00;
    }
  }
  fVar1 = FLOAT_8043bce8;
  if (*(char *)(param_9 + 0x3f) != '\0') {
    dVar4 = (double)FLOAT_8043bce8;
    param_2 = (double)*(float *)(param_9 + 100);
    if (dVar4 != param_2) {
      *(float *)(param_9 + 0x48) = (float)((double)*(float *)(param_9 + 0x48) + param_2);
      param_2 = (double)*(float *)(param_9 + 0x60);
      if ((double)*(float *)(param_9 + 0x48) <= param_2) {
        *(float *)(param_9 + 0x48) = *(float *)(param_9 + 0x60);
        *(float *)(param_9 + 100) = fVar1;
      }
      dVar4 = (double)zz_002b00c_((double)*(float *)(param_9 + 0x48));
      uVar3 = extraout_r4_01;
    }
  }
  if (*(char *)(param_9 + 0x3d) != '\0') {
    pfVar2 = (float *)zz_000598c_(0);
    dVar4 = (double)SidelineExplodableManager__GetNumExplodables_void_();
    *pfVar2 = (float)dVar4;
    uVar3 = extraout_r4_02;
  }
  zz_0008948_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(float *)&DAT_803c7380,
              uVar3,(undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00eff30_();
  return;
}



// ==== 801c7cf4  zz_01c7cf4_ ====

void zz_01c7cf4_(void)

{
  zz_008a16c_();
  zz_0053928_();
  zz_0089cd0_(0x28);
  zz_0089cd0_(0x20);
  zz_0089cd0_(0);
  zz_0089cd0_(0x10);
  zz_0089cd0_(8);
  zz_0089cd0_(0x18);
  zz_0087814_();
  zz_008c0dc_(FUN_80089eb4);
  zz_008c0dc_(FUN_8008a010);
  zz_008c0dc_(FUN_8008a0a8);
  return;
}



// ==== 801c7d70  FUN_801c7d70 ====

void FUN_801c7d70(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined8 uVar1;
  undefined8 extraout_f1;
  
  zz_0008b58_();
  zz_0008cf4_();
  zz_01978d0_();
  uVar1 = zz_0040910_();
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,extraout_r4,
                      param_11,param_12,param_13,param_14,param_15,param_16);
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,extraout_r4_00
                      ,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,extraout_r4_01,
              param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00f07c4_();
  uVar1 = zz_0005984_(0);
  zz_0008924_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14,
              param_15,param_16);
  return;
}



// ==== 801c7dc4  zz_01c7dc4_ ====

void zz_01c7dc4_(undefined4 param_1)

{
  DAT_803d5d94 = param_1;
  return;
}



// ==== 801c7dd4  zz_01c7dd4_ ====

undefined4 zz_01c7dd4_(void)

{
  return DAT_803d5d94;
}



// ==== 801c7de4  zz_01c7de4_ ====

void zz_01c7de4_(int param_1)

{
  byte bVar1;
  int iVar2;
  
  while( true ) {
    bVar1 = **(byte **)(param_1 + 0x20);
    iVar2 = (*(code *)(&PTR_FUN_8038a4f8)[bVar1])(param_1);
    if (iVar2 == 0) break;
    *(int *)(param_1 + 0x20) = (int)(char)(&DAT_8038a3b8)[bVar1] + *(int *)(param_1 + 0x20) + 1;
    *(undefined1 *)(param_1 + 0x2d) = 0;
  }
  return;
}



// ==== 801c7e64  FUN_801c7e64 ====

undefined4 FUN_801c7e64(int param_1)

{
  zz_01c7dc4_((uint)*(byte *)(*(int *)(param_1 + 0x20) + 1));
  if (*(int *)(param_1 + 0x1c) == 0xc) {
    *(undefined1 *)(param_1 + 0x68) = 1;
  }
  *(undefined1 *)(param_1 + 0x2d) = 0;
  return 1;
}



// ==== 801c7eb8  FUN_801c7eb8 ====

undefined4 FUN_801c7eb8(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x20);
  zz_0027aac_((uint)*(byte *)(iVar1 + 4) << 8 |
              (uint)*(byte *)(iVar1 + 2) << 0x18 | (uint)*(byte *)(iVar1 + 3) << 0x10,
              (ushort)*(byte *)(iVar1 + 5),*(undefined1 *)(iVar1 + 1));
  return 1;
}



// ==== 801c7f00  FUN_801c7f00 ====

uint FUN_801c7f00(void)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = zz_0027adc_();
  uVar1 = countLeadingZeros(iVar2);
  return uVar1 >> 5;
}



// ==== 801c7f28  FUN_801c7f28 ====

undefined4 FUN_801c7f28(void)

{
  zz_0027c1c_();
  return 1;
}



// ==== 801c7ffc  FUN_801c7ffc ====

undefined4
FUN_801c7ffc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
            double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
            float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
            undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined8 uVar2;
  double dVar3;
  
  iVar1 = *(int *)(param_9 + 0x20);
  *(undefined4 *)(param_9 + 0x30) = *(undefined4 *)(&DAT_8038a3d0 + (uint)*(byte *)(iVar1 + 1) * 4);
  *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(&DAT_8038a3d0 + (uint)*(byte *)(iVar1 + 3) * 4);
  *(undefined1 *)(param_9 + 0x3c) = 0xff;
  uVar2 = zz_00088a4_((double)*(float *)(param_9 + 0x30),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,*(int *)(param_9 + 0x24),&DAT_8038a3d0,param_11,param_12,
                      param_13,param_14,param_15,param_16);
  if (*(byte *)(iVar1 + 2) == 0xff) {
    dVar3 = zz_0008a1c_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    *(float *)(param_9 + 0x34) = (float)dVar3;
  }
  else {
    *(undefined4 *)(param_9 + 0x34) =
         *(undefined4 *)(&DAT_8038a3d0 + (uint)*(byte *)(iVar1 + 2) * 4);
  }
  return 1;
}



// ==== 801c8100  FUN_801c8100 ====

uint FUN_801c8100(void)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = zz_000a3c4_();
  uVar1 = countLeadingZeros(iVar2);
  return uVar1 >> 5;
}



// ==== 801c8128  FUN_801c8128 ====

undefined4
FUN_801c8128(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
            undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 uVar1;
  
  zz_00412c4_(0,0);
  uVar1 = zz_00412c4_(1,0);
  uVar1 = zz_0042954_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14
                      ,param_15,param_16);
  zz_0042b20_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14,
              param_15,param_16);
  return 1;
}



// ==== 801c8168  FUN_801c8168 ====

undefined4 FUN_801c8168(int param_1)

{
  *(undefined1 *)(param_1 + 0x3d) = *(undefined1 *)(*(int *)(param_1 + 0x20) + 1);
  zz_0005984_((int)*(char *)(param_1 + 0x3d));
  return 1;
}



// ==== 801c81a0  FUN_801c81a0 ====

/* WARNING: Removing unreachable block (ram,0x801c81c8) */

undefined4 FUN_801c81a0(int param_1)

{
  byte bVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x20);
  bVar1 = *(byte *)(iVar2 + 1);
  if (bVar1 == 1) {
    zz_0058044_((&DAT_803c4e84)[*(byte *)(iVar2 + 2)]);
  }
  else if (bVar1 == 0) {
    zz_0057ff8_((&DAT_803c4e84)[*(byte *)(iVar2 + 2)],5,(uint)*(byte *)(iVar2 + 3));
  }
  else if (bVar1 < 3) {
    if (*(char *)(iVar2 + 2) == '\x01') {
      *(char *)((&DAT_803c4e84)[*(byte *)(iVar2 + 3)] + 0x82) =
           *(char *)((&DAT_803c4e84)[*(byte *)(iVar2 + 3)] + 0x96) + 'A';
    }
    else {
      *(undefined1 *)((&DAT_803c4e84)[*(byte *)(iVar2 + 3)] + 0x82) = 0;
    }
  }
  return 1;
}



// ==== 801c82b0  FUN_801c82b0 ====

/* WARNING: Removing unreachable block (ram,0x801c82e0) */

undefined4 FUN_801c82b0(int param_1)

{
  char cVar1;
  float fVar2;
  
  cVar1 = *(char *)(*(int *)(param_1 + 0x20) + 1);
  if (cVar1 == '\x01') {
    zz_002aee0_((void *)(param_1 + 0x40));
    fVar2 = FLOAT_8043bce8;
    *(undefined1 *)(param_1 + 0x3f) = 1;
    *(float *)(param_1 + 100) = fVar2;
    *(float *)(param_1 + 0x60) = fVar2;
  }
  else if (cVar1 == '\0') {
    zz_002affc_();
    *(undefined1 *)(param_1 + 0x3f) = 0;
  }
  return 1;
}



// ==== 801c8328  FUN_801c8328 ====

undefined4 FUN_801c8328(int param_1)

{
  gnt4_memcpy((void *)(param_1 + 0x40),&DAT_8038a550,0x20);
  return 1;
}



// ==== 801c835c  FUN_801c835c ====

undefined4 FUN_801c835c(int param_1)

{
  short sVar1;
  double dVar2;
  
  dVar2 = DOUBLE_8043bcf0;
  sVar1 = *(short *)(*(int *)(param_1 + 0x20) + 1);
  *(float *)(param_1 + 0x60) = FLOAT_8043bce8;
  *(float *)(param_1 + 100) =
       (*(float *)(param_1 + 0x60) - *(float *)(param_1 + 0x48)) /
       (float)((double)CONCAT44(0x43300000,(int)sVar1 ^ 0x80000000) - dVar2);
  return 1;
}



// ==== 801c83b8  FUN_801c83b8 ====

undefined4 FUN_801c83b8(void)

{
  zz_0040d64_(0,6);
  return 1;
}



// ==== 801c83e4  FUN_801c83e4 ====

undefined4
FUN_801c83e4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9)

{
  byte *pbVar1;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  pbVar1 = (byte *)(*(int *)(param_9 + 0x20) + 1);
  zz_00e99c8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,
              *(int *)(&DAT_8031a074 + *(short *)pbVar1 * 4),(uint)*pbVar1,*(int *)(param_9 + 0x20),
              in_r8,in_r9,in_r10);
  return 1;
}



// ==== 801c8434  FUN_801c8434 ====

undefined4
FUN_801c8434(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
            undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
            undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_00e9b08_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,1,
              (uint)*(byte *)(*(int *)(param_9 + 0x20) + 1),param_12,param_13,param_14,param_15,
              param_16);
  return 1;
}



// ==== 801c846c  FUN_801c846c ====

undefined4 FUN_801c846c(int param_1)

{
  zz_00f036c_(0,(int)*(short *)(*(int *)(param_1 + 0x20) + 1));
  return 1;
}



// ==== 801c84a8  zz_01c84a8_ ====

void zz_01c84a8_(void)

{
  short *psVar1;
  undefined1 *puVar2;
  char cVar3;
  
  cVar3 = '\0';
  for (psVar1 = &DAT_8038a570; -1 < *psVar1; psVar1 = psVar1 + 3) {
    puVar2 = zz_008893c_(2,0x28,0,2);
    if (puVar2 != (undefined1 *)0x0) {
      *puVar2 = 1;
      puVar2[0x10] = 1;
      *(code **)(puVar2 + 0xc) = FUN_801c8554;
      *(code **)(puVar2 + 0x10c) = FUN_801c867c;
      *(short **)(puVar2 + 0x54) = psVar1;
      puVar2[0x11] = (char)psVar1[1];
      puVar2[0x12] = (char)psVar1[2];
      puVar2[0x13] = cVar3;
    }
    cVar3 = cVar3 + '\x01';
  }
  return;
}



// ==== 801c8554  FUN_801c8554 ====

void FUN_801c8554(int param_1)

{
  (*(code *)(&PTR_FUN_8038a674)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801c8590  FUN_801c8590 ====

void FUN_801c8590(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x82) = 1;
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb470,
              *(int *)(param_9 + 0xe0),(int)**(short **)(param_9 + 0x54),param_12,param_13,param_14,
              param_15,param_16);
  (*(code *)(&PTR_FUN_8038a684)[*(char *)(param_9 + 0x11)])(param_9);
  zz_01c860c_(param_9);
  return;
}



// ==== 801c860c  zz_01c860c_ ====

void zz_01c860c_(int param_1)

{
  (*(code *)(&PTR_FUN_8038a690)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801c865c  FUN_801c865c ====

void FUN_801c865c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801c867c  FUN_801c867c ====

void FUN_801c867c(int param_1)

{
  (*(code *)(&PTR_FUN_8038a69c)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801c86b8  FUN_801c86b8 ====

void FUN_801c86b8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  uVar1 = zz_0008744_((double)FLOAT_8043bcf8,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                      ,DAT_803bb470,*(int *)(param_9 + 0xe0),param_11,param_12,param_13,param_14,
                      param_15,param_16);
  zz_0007c30_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801c8700  FUN_801c8700 ====

void FUN_801c8700(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  
  iVar3 = zz_01c7dd4_();
  cVar1 = *(char *)(param_9 + 0x19);
  bVar2 = false;
  if (cVar1 == '\x01') {
    zz_0007c30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),1,param_11,param_12,param_13,param_14,param_15,param_16);
    if (iVar3 != 2) {
      bVar2 = true;
    }
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) && (1 < iVar3)) {
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
  }
  if ((bVar2) || (*PTR_DAT_80433930 != '\x01')) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801c87b4  FUN_801c87b4 ====

void FUN_801c87b4(int param_1)

{
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x47);
  return;
}



// ==== 801c87dc  FUN_801c87dc ====

void FUN_801c87dc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  int iVar2;
  undefined2 uVar4;
  int iVar3;
  undefined8 uVar5;
  float local_38;
  float local_34;
  float local_30;
  longlong local_28;
  longlong local_20;
  longlong local_18;
  
  uVar5 = zz_0007908_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),(undefined4 *)(param_9 + 100),param_11,param_12,
                      param_13,param_14,param_15,param_16);
  zz_0007a60_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,&local_38,param_11,param_12,param_13,param_14,param_15,param_16);
  fVar1 = FLOAT_8043bcfc;
  local_28 = (longlong)(int)(FLOAT_8043bcfc * local_38);
  uVar4 = (undefined2)(int)(FLOAT_8043bcfc * local_38);
  *(undefined2 *)(param_9 + 0x144) = uVar4;
  *(undefined2 *)(param_9 + 0x70) = uVar4;
  iVar2 = (int)(fVar1 * local_34);
  local_20 = (longlong)iVar2;
  uVar4 = (undefined2)iVar2;
  *(undefined2 *)(param_9 + 0x146) = uVar4;
  *(undefined2 *)(param_9 + 0x72) = uVar4;
  iVar2 = (int)(fVar1 * local_30);
  local_18 = (longlong)iVar2;
  uVar4 = (undefined2)iVar2;
  *(undefined2 *)(param_9 + 0x148) = uVar4;
  *(undefined2 *)(param_9 + 0x74) = uVar4;
  iVar3 = *(char *)(param_9 + 0x12) * 0x18;
  *(undefined2 *)(param_9 + 0x7c) = *(undefined2 *)(&DAT_8038a5ba + iVar3);
  *(undefined1 *)(param_9 + 0x84) = 0xf;
  *(code **)(param_9 + 0x100) = FUN_801c8c54;
  zz_0089100_(param_9,1,1);
  iVar2 = zz_01c7dd4_();
  fVar1 = FLOAT_8043bcf8;
  if ((iVar2 == 0xc) || (*PTR_DAT_80433930 == '\x02')) {
    *(undefined1 *)(param_9 + 0x19) = 3;
    *(float *)(param_9 + 0x38) = fVar1;
  }
  else {
    *(undefined1 *)(*(int *)(param_9 + 0xe0) + 0x10) = 0;
    *(undefined2 *)(param_9 + 0x7e) = *(undefined2 *)(&DAT_8038a5b8 + iVar3);
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8038a5b4 + iVar3);
    *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(&DAT_8038a5bc + iVar3);
    *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(&DAT_8038a5c0 + iVar3);
    *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(&DAT_8038a5c8 + iVar3);
    *(undefined4 *)(param_9 + 0x4c) = *(undefined4 *)(&DAT_8038a5c4 + iVar3);
  }
  return;
}



// ==== 801c892c  FUN_801c892c ====

void FUN_801c892c(int param_1)

{
  char cVar1;
  int iVar2;
  short sVar3;
  bool bVar4;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x02') {
    if (*(char *)(param_1 + 0x12) < '\x04') {
      iVar2 = zz_01c8a84_(param_1);
      if (iVar2 != 0) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      }
    }
    else {
      bVar4 = zz_01c8bd8_(param_1);
      if (bVar4) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      }
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      iVar2 = zz_01c7dd4_();
      if (((8 < iVar2) || (*PTR_DAT_80433930 == '\x02')) &&
         (sVar3 = *(short *)(param_1 + 0x1c) + -1, *(short *)(param_1 + 0x1c) = sVar3, sVar3 < 1)) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        *(undefined1 *)(*(int *)(param_1 + 0xe0) + 0x10) = 1;
      }
    }
    else if (-1 < cVar1) {
      *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) + *(float *)(param_1 + 0x3c);
      *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) + *(float *)(param_1 + 0x4c);
      if (*(float *)(param_1 + 0x38) <= *(float *)(param_1 + 0x40)) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x40);
        if (-1 < *(short *)(&DAT_8038a5b6 + *(char *)(param_1 + 0x12) * 0x18)) {
          zz_00f03c0_(0,(int)*(short *)(&DAT_8038a5b6 + *(char *)(param_1 + 0x12) * 0x18));
        }
      }
    }
  }
  return;
}



// ==== 801c8a84  zz_01c8a84_ ====

undefined4 zz_01c8a84_(int param_1)

{
  char cVar1;
  double dVar2;
  int iVar3;
  short sVar4;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) + *(float *)(param_1 + 0x3c);
    *(short *)(param_1 + 0x7c) = *(short *)(param_1 + 0x7c) - *(short *)(param_1 + 0x7e);
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    if (0 < sVar4) {
      return 0;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined2 *)(param_1 + 0x7c) = 0;
        return 0;
      }
      if (cVar1 < '\0') {
        return 0;
      }
      iVar3 = zz_01c7dd4_();
      if (iVar3 < 10) {
        return 0;
      }
      if (*(char *)(param_1 + 0x12) == '\0') {
        zz_00f03c0_(0,0x17a);
      }
      dVar2 = DOUBLE_8043bd00;
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 0x1e;
      *(float *)(param_1 + 0x3c) =
           -(*(float *)(param_1 + 0x38) /
            (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c) ^ 0x80000000) -
                   dVar2));
      *(short *)(param_1 + 0x7e) = (short)(0x20000 / (int)*(short *)(param_1 + 0x1c));
      return 0;
    }
    if ('\x03' < cVar1) {
      return 0;
    }
  }
  *(float *)(param_1 + 0x38) = FLOAT_8043bcf8;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x72) = 0;
  return 1;
}



// ==== 801c8bd8  zz_01c8bd8_ ====

bool zz_01c8bd8_(int param_1)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return false;
    }
    if (cVar1 < '\0') {
      return false;
    }
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0;
    *(undefined2 *)(param_1 + 0x1e) = 8;
  }
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(&DAT_8038a6a8 + *(short *)(param_1 + 0x1c) * 4);
  sVar2 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar2;
  return *(short *)(param_1 + 0x1e) <= sVar2;
}



// ==== 801c8c54  FUN_801c8c54 ====

void FUN_801c8c54(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_0007908_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(undefined4 *)(param_9 + 100),param_11,param_12,param_13,
              param_14,param_15,param_16);
  *(float *)(param_9 + 0x68) = *(float *)(param_9 + 0x68) + *(float *)(param_9 + 0x38);
  *(short *)(param_9 + 0x72) = *(short *)(param_9 + 0x72) + *(short *)(param_9 + 0x7c);
  FUN_80047aa4(param_9);
  return;
}



// ==== 801c8cb0  FUN_801c8cb0 ====

void FUN_801c8cb0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),1);
  return;
}



// ==== 801c8cf0  FUN_801c8cf0 ====

void FUN_801c8cf0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_8043bd0c;
  dVar2 = (double)FLOAT_8043bd08;
  *(float *)(param_9 + 0xd4) = FLOAT_8043bd08;
  *(float *)(param_9 + 0xd8) = fVar1;
  zz_0007c54_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_0007cac_((double)*(float *)(param_9 + 0xd4),*(int *)(param_9 + 0xe0));
  return;
}



// ==== 801c8d3c  FUN_801c8d3c ====

void FUN_801c8d3c(int param_1)

{
  bool bVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  
  iVar5 = zz_01c7dd4_();
  fVar4 = FLOAT_8043bcf8;
  cVar2 = *(char *)(param_1 + 0x19);
  bVar1 = false;
  if (cVar2 == '\x01') {
    fVar3 = *(float *)(param_1 + 0xd4) - *(float *)(param_1 + 0xd8);
    *(float *)(param_1 + 0xd4) = fVar3;
    bVar1 = fVar3 <= fVar4;
    if (bVar1) {
      *(float *)(param_1 + 0xd4) = fVar4;
    }
    zz_0007cac_((double)*(float *)(param_1 + 0xd4),*(int *)(param_1 + 0xe0));
  }
  else if (((cVar2 < '\x01') && (-1 < cVar2)) && (1 < iVar5)) {
    *(char *)(param_1 + 0x19) = cVar2 + '\x01';
  }
  if ((bVar1) || (*PTR_DAT_80433930 != '\x01')) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801c8e04  FUN_801c8e04 ====

void FUN_801c8e04(int param_1)

{
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
  return;
}



// ==== 801c8e2c  zz_01c8e2c_ ====

void zz_01c8e2c_(void)

{
  int iVar1;
  undefined4 local_18 [6];
  
  local_18[0] = 0x30;
  iVar1 = zz_01a7538_(0x16,local_18);
  if (iVar1 != 0) {
    *(code **)(iVar1 + 0xc) = FUN_801c8e7c;
    *(code **)(iVar1 + 0x10c) = FUN_801c8f7c;
  }
  return;
}



// ==== 801c8e7c  FUN_801c8e7c ====

void FUN_801c8e7c(int param_1)

{
  (*(code *)(&PTR_FUN_8038a6c8)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801c8eb8  FUN_801c8eb8 ====

void FUN_801c8eb8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  uVar2 = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043bd10;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  zz_01a7688_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar2,param_12
              ,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 3;
  zz_01c8f44_();
  return;
}



// ==== 801c8f44  zz_01c8f44_ ====

void zz_01c8f44_(void)

{
  return;
}



// ==== 801c8f5c  FUN_801c8f5c ====

void FUN_801c8f5c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801c8f7c  FUN_801c8f7c ====

void FUN_801c8f7c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char *pcVar1;
  int iVar2;
  undefined8 uVar3;
  float afStack_28 [3];
  float afStack_1c [5];
  
  pcVar1 = DAT_80436354;
  uVar3 = zz_00057f0_((float *)(*(int *)(DAT_80436354 + *(int *)(DAT_80436354 + 0x118) * 4 + 0x984)
                               + 100),afStack_1c);
  iVar2 = *(int *)(param_9 + 0xe0);
  zz_0007834_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,afStack_1c,pcVar1,
              param_12,param_13,param_14,param_15,param_16);
  uVar3 = gnt4_PSQUATScale_bl((double)FLOAT_8043bd14,(float *)(param_9 + 0x58),afStack_28);
  zz_0007ae4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,afStack_28,pcVar1,
              param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar2,0x45);
  return;
}



// ==== 801c9004  zz_01c9004_ ====

void zz_01c9004_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8038a6d8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801c9054  FUN_801c9054 ====

void FUN_801c9054(int param_1,undefined2 *param_2)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043bd18;
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043bd1c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043bd20;
  return;
}



// ==== 801c913c  FUN_801c913c ====

void FUN_801c913c(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043bd20;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    dVar3 = DOUBLE_8043bd28;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,*(uint *)(param_2 + 8) ^ 0x80000000) - dVar3);
    zz_01c94b4_(param_1,param_2);
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 801c9200  FUN_801c9200 ====

void FUN_801c9200(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)*(float *)(param_2 + 0xc),param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  fVar3 = FLOAT_8043bd20;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar3) ||
     (uVar4 = FUN_800668cc((double)*(float *)(param_2 + 4),param_1), uVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if ((*(short *)(param_2 + 2) != 0) && (*(char *)(param_1 + 0x542) == '\0')) {
      dVar5 = (double)FLOAT_8043bd1c;
      *(undefined1 *)(param_1 + 0x542) = 1;
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    }
  }
  zz_01ca8c4_(param_1);
  return;
}



// ==== 801c930c  FUN_801c930c ====

void FUN_801c930c(int param_1,int param_2)

{
  char cVar1;
  double dVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  dVar2 = DOUBLE_8043bd28;
  if (((char)*(byte *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    if (((*(byte *)(param_1 + 0x1cf0) & 1) == 0) && (*(code **)(param_2 + 0x10) != (code *)0x0)) {
      (**(code **)(param_2 + 0x10))(param_1);
      return;
    }
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    dVar3 = (double)FLOAT_8043bd1c;
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(undefined1 *)(param_1 + 0x745) = 0;
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,*(uint *)(param_2 + 8) ^ 0x80000000) - dVar2);
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    zz_01c94b4_(param_1,param_2);
    zz_00b2190_(param_1,0);
    return;
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    zz_01c94b4_(param_1,param_2);
  }
  zz_006ed8c_((double)*(float *)(param_2 + 0xc),param_1);
  if (*(float *)(param_1 + 0x760) < *(float *)(param_2 + 4)) {
    zz_006ed8c_((double)FLOAT_8043bd30,param_1);
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  zz_01ca8c4_(param_1);
  return;
}



// ==== 801c94b4  zz_01c94b4_ ====

void zz_01c94b4_(int param_1,int param_2)

{
  float fVar1;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
  }
  else {
    fVar1 = *(float *)(param_1 + 0x760) *
            (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000) -
                   DOUBLE_8043bd28) * FLOAT_8043bd34;
  }
  if (*(uint *)(param_2 + 8) != 0) {
    *(float *)(param_1 + 0x44) =
         fVar1 / (float)((double)CONCAT44(0x43300000,*(uint *)(param_2 + 8) ^ 0x80000000) -
                        DOUBLE_8043bd28);
  }
  *(undefined1 *)(param_1 + 0x1d0f) = 0;
  return;
}



// ==== 801c956c  zz_01c956c_ ====

void zz_01c956c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8038a6e8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801c95bc  FUN_801c95bc ====

void FUN_801c95bc(int param_1,int *param_2)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_8043bd18;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(undefined1 *)(param_1 + 0x746) = 0;
  uVar2 = FUN_800668cc((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_004beb8_((double)FLOAT_8043bd1c,param_1,0xf,3,*param_2,0xffffffff,0xffffffff);
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  else {
    zz_006e1ac_(param_1,0xc0,1);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)(float)param_2[3],(float *)(param_1 + 0x38),(float *)(param_1 + 0x38))
  ;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  return;
}



// ==== 801c9710  FUN_801c9710 ====

void FUN_801c9710(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0xc),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  else {
    zz_006e1ac_(param_1,0xc0,1);
  }
  fVar2 = FLOAT_8043bd20;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    dVar3 = DOUBLE_8043bd28;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 8) ^ 0x80000000) - dVar3);
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 801c9820  FUN_801c9820 ====

void FUN_801c9820(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    if (*(char *)(param_1 + 0x1b03) == '\0') goto LAB_801c9860;
  }
  zz_004cd24_(param_1,0xf);
LAB_801c9860:
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  else {
    zz_006e1ac_(param_1,0xc0,1);
    *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x18da);
  }
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_2 + 0x10) * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_8043bd38;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_2 + 0x10) * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043bd20;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) ||
     (uVar3 = FUN_800668cc((double)*(float *)(param_2 + 4),param_1), 0 < (int)uVar3)) {
    dVar4 = DOUBLE_8043bd28;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 10) ^ 0x80000000) - dVar4);
  }
  return;
}



// ==== 801c9964  FUN_801c9964 ====

void FUN_801c9964(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  else {
    zz_006e1ac_(param_1,0xc0,1);
    *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x18da);
  }
  zz_006ed8c_((double)*(float *)(param_2 + 0x14),param_1);
  FUN_80067310((double)FLOAT_8043bd38,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043bd20;
  if ((*(int *)(param_1 + 0xcc) != 0) &&
     (fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x558) = fVar1, fVar2 < fVar1)) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_2 + 0x10);
  dVar3 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar3);
  dVar3 = zz_0045204_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar3);
  return;
}



// ==== 801c9a80  FUN_801c9a80 ====

void FUN_801c9a80(int param_1,int param_2)

{
  int iVar1;
  double dVar2;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043bd28) * FLOAT_8043bd3c);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
    if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
      zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
    }
    else {
      zz_006e1ac_(param_1,0xc0,1);
      *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x18da);
    }
    dVar2 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar2);
    dVar2 = zz_0045204_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar2);
  }
  if ((*(byte *)(param_1 + 0x1d9) & 0x30) != 0) {
    if (*(code **)(param_2 + 0x1c) != (code *)0x0) {
      (**(code **)(param_2 + 0x1c))(param_1);
    }
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  zz_006eddc_((double)*(float *)(param_2 + 0x18),param_1,(float *)(param_1 + 0x38));
  zz_006ed8c_((double)*(float *)(param_2 + 0x18),param_1);
  FUN_80067310((double)FLOAT_8043bd38,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043bd40 + *(float *)(param_1 + 0x1dc8);
    *(undefined2 *)(param_1 + 0x18da) = 0;
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_8043bd40 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 801c9c9c  zz_01c9c9c_ ====

void zz_01c9c9c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8038a6fc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801c9cec  FUN_801c9cec ====

void FUN_801c9cec(int param_1,undefined4 *param_2)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_8043bd20;
  *(float *)(param_1 + 0x558) = FLOAT_8043bd18;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)(float)param_2[1],(float *)(param_1 + 0x38),(float *)(param_1 + 0x38))
  ;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043bd1c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043bd20;
  return;
}



// ==== 801c9e58  FUN_801c9e58 ====

void FUN_801c9e58(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 4),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_8043bd20;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 801c9f18  FUN_801c9f18 ====

void FUN_801c9f18(int param_1,int param_2)

{
  float fVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 4),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  dVar2 = DOUBLE_8043bd28;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar1 = FLOAT_8043bd20;
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 8) ^ 0x80000000) - dVar2);
    *(undefined2 *)(param_1 + 0x54c) = *(undefined2 *)(param_2 + 10);
    *(float *)(param_1 + 0x55c) = fVar1;
    *(float *)(param_1 + 0x38) = fVar1;
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_2 + 0x10);
    dVar2 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar2);
    dVar2 = zz_0045204_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar2);
  }
  return;
}



// ==== 801ca01c  FUN_801ca01c ====

void FUN_801ca01c(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  double dVar6;
  
  uVar5 = zz_006de44_(param_1,0xf0f00);
  dVar6 = DOUBLE_8043bd28;
  if (uVar5 != 0) {
    if ((int)*(short *)(param_1 + 0x54c) < (int)uVar5) {
      uVar5 = (int)*(short *)(param_1 + 0x54c);
    }
    *(short *)(param_1 + 0x54c) = *(short *)(param_1 + 0x54c) - (short)uVar5;
    *(float *)(param_1 + 0x558) =
         *(float *)(param_1 + 0x558) +
         (float)((double)CONCAT44(0x43300000,uVar5 ^ 0x80000000) - dVar6);
  }
  fVar3 = FLOAT_8043bd20;
  fVar2 = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x55c) = fVar2;
  if (fVar2 <= fVar3) {
    *(float *)(param_1 + 0x55c) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 0x14) ^ 0x80000000) -
                DOUBLE_8043bd28);
    zz_00f036c_(param_1,9);
  }
  *(short *)(param_1 + 0x18dc) =
       (short)(int)((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 0x16) ^ 0x80000000
                                            ) - DOUBLE_8043bd28) * *(float *)(param_1 + 0x1dc8) +
                   (float)((double)CONCAT44(0x43300000,
                                            (int)*(short *)(param_1 + 0x18dc) ^ 0x80000000) -
                          DOUBLE_8043bd28));
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x38) =
       *(float *)(param_2 + 0xc) * *(float *)(param_1 + 0x1dc8) + *(float *)(param_1 + 0x38);
  if (*(float *)(param_1 + 0x40) < *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x40);
  }
  dVar6 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar6);
  dVar6 = zz_0045204_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar6);
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) * FLOAT_8043bd30;
  }
  FUN_80067310((double)FLOAT_8043bd38,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar3 = FLOAT_8043bd20;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  fVar4 = FLOAT_8043bd44;
  if (fVar2 <= fVar3) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar4;
    if (*(code **)(param_2 + 0x18) != (code *)0x0) {
      (**(code **)(param_2 + 0x18))(param_1);
    }
    dVar6 = (double)FLOAT_8043bd1c;
    *(undefined2 *)(param_1 + 0x18dc) = 0;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar6,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 801ca280  FUN_801ca280 ====

void FUN_801ca280(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043bd38,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_8043bd20;
  if ((iVar3 == 0) || (*(char *)(param_1 + 0x1cee) == '\0')) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043bd40 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 801ca34c  FUN_801ca34c ====

void FUN_801ca34c(int param_1)

{
  (*(code *)(&PTR_FUN_8038a710)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801ca388  FUN_801ca388 ====

void FUN_801ca388(int param_1,undefined4 *param_2)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  dVar3 = DOUBLE_8043bd28;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(float *)(param_1 + 0x560) =
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 1) ^ 0x80000000) - dVar3);
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)((int)param_2 + 6);
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  fVar2 = FLOAT_8043bd20;
  *(float *)(param_1 + 0x50) = FLOAT_8043bd20;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)(float)param_2[2],(float *)(param_1 + 0x38),(float *)(param_1 + 0x38))
  ;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043bd1c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801ca4d4  FUN_801ca4d4 ====

void FUN_801ca4d4(int param_1,int param_2)

{
  if ((*(uint *)(param_1 + 0x5d4) & 0x80) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  if (*(code **)(param_2 + 0xc) != (code *)0x0) {
    (**(code **)(param_2 + 0xc))(param_1);
  }
  FUN_80067310((double)FLOAT_8043bd38,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 8),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x6f7) = 2;
    if (*(code **)(param_2 + 0x10) != (code *)0x0) {
      (**(code **)(param_2 + 0x10))(param_1);
    }
  }
  return;
}



// ==== 801ca5e0  FUN_801ca5e0 ====

void FUN_801ca5e0(int param_1,int param_2)

{
  double dVar1;
  uint uVar2;
  int iVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x80) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  *(undefined1 *)(param_1 + 0x6f7) = 2;
  uVar2 = zz_006de44_(param_1,0xf0f00);
  dVar1 = DOUBLE_8043bd28;
  if (uVar2 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar2) {
      uVar2 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar2;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - dVar1);
  }
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 8),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_8043bd38,param_1,*(short *)(param_1 + 0x5ae));
  zz_00679d0_(param_1);
  if (*(float *)(param_1 + 0x560) <= FLOAT_8043bd20) {
    zz_004cd24_(param_1,0xf);
    if (((*(char *)(param_1 + 0x1cf0) < '\0') && (*(code **)(param_2 + 0x14) != (code *)0x0)) &&
       (iVar3 = (**(code **)(param_2 + 0x14))(param_1), iVar3 != 0)) {
      return;
    }
    if (*(char *)(param_1 + 0x1cef) < '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x6f7) = 0;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
  }
  else {
    *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 801ca790  FUN_801ca790 ====

void FUN_801ca790(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  dVar3 = (double)FLOAT_8043bd38;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043bd28) * FLOAT_8043bd48);
  FUN_80067310(dVar3,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if (((iVar2 != 0) && ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) &&
     (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043bd40 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043bd20;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    if (iVar2 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = FLOAT_8043bd40 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 801ca8c4  zz_01ca8c4_ ====

void zz_01ca8c4_(int param_1)

{
  double dVar1;
  float afStack_18 [5];
  
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),afStack_18);
  dVar1 = gnt4_PSVECMag_bl(afStack_18);
  if ((double)FLOAT_8043bd4c < dVar1) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 801ca918  zz_01ca918_ ====

void zz_01ca918_(void *param_1)

{
  if (param_1 != (void *)0x0) {
    gnt4_memset(param_1,0,600);
  }
  return;
}



// ==== 801ca948  zz_01ca948_ ====

void zz_01ca948_(undefined2 *param_1)

{
  undefined2 *puVar1;
  int iVar2;
  
  if (param_1 != (undefined2 *)0x0) {
    iVar2 = 0xfa;
    puVar1 = param_1;
    do {
      *puVar1 = 0xffff;
      *(undefined1 *)(puVar1 + 1) = 0;
      *(undefined1 *)((int)puVar1 + 3) = 0;
      *(undefined4 *)(puVar1 + 2) = 0;
      *(undefined4 *)(puVar1 + 4) = 0;
      *(undefined1 *)(puVar1 + 6) = 0;
      *(undefined1 *)((int)puVar1 + 0xd) = 0;
      puVar1[7] = 0;
      puVar1[8] = 0xffff;
      *(undefined1 *)(puVar1 + 9) = 0;
      *(undefined1 *)((int)puVar1 + 0x13) = 0;
      *(undefined4 *)(puVar1 + 10) = 0;
      *(undefined4 *)(puVar1 + 0xc) = 0;
      *(undefined1 *)(puVar1 + 0xe) = 0;
      *(undefined1 *)((int)puVar1 + 0x1d) = 0;
      puVar1[0xf] = 0;
      puVar1[0x10] = 0xffff;
      *(undefined1 *)(puVar1 + 0x11) = 0;
      *(undefined1 *)((int)puVar1 + 0x23) = 0;
      *(undefined4 *)(puVar1 + 0x12) = 0;
      *(undefined4 *)(puVar1 + 0x14) = 0;
      *(undefined1 *)(puVar1 + 0x16) = 0;
      *(undefined1 *)((int)puVar1 + 0x2d) = 0;
      puVar1[0x17] = 0;
      puVar1[0x18] = 0xffff;
      *(undefined1 *)(puVar1 + 0x19) = 0;
      *(undefined1 *)((int)puVar1 + 0x33) = 0;
      *(undefined4 *)(puVar1 + 0x1a) = 0;
      *(undefined4 *)(puVar1 + 0x1c) = 0;
      *(undefined1 *)(puVar1 + 0x1e) = 0;
      *(undefined1 *)((int)puVar1 + 0x3d) = 0;
      puVar1[0x1f] = 0;
      puVar1[0x20] = 0xffff;
      *(undefined1 *)(puVar1 + 0x21) = 0;
      *(undefined1 *)((int)puVar1 + 0x43) = 0;
      *(undefined4 *)(puVar1 + 0x22) = 0;
      *(undefined4 *)(puVar1 + 0x24) = 0;
      *(undefined1 *)(puVar1 + 0x26) = 0;
      *(undefined1 *)((int)puVar1 + 0x4d) = 0;
      puVar1[0x27] = 0;
      puVar1[0x28] = 0xffff;
      *(undefined1 *)(puVar1 + 0x29) = 0;
      *(undefined1 *)((int)puVar1 + 0x53) = 0;
      *(undefined4 *)(puVar1 + 0x2a) = 0;
      *(undefined4 *)(puVar1 + 0x2c) = 0;
      *(undefined1 *)(puVar1 + 0x2e) = 0;
      *(undefined1 *)((int)puVar1 + 0x5d) = 0;
      puVar1[0x2f] = 0;
      puVar1[0x30] = 0xffff;
      *(undefined1 *)(puVar1 + 0x31) = 0;
      *(undefined1 *)((int)puVar1 + 99) = 0;
      *(undefined4 *)(puVar1 + 0x32) = 0;
      *(undefined4 *)(puVar1 + 0x34) = 0;
      *(undefined1 *)(puVar1 + 0x36) = 0;
      *(undefined1 *)((int)puVar1 + 0x6d) = 0;
      puVar1[0x37] = 0;
      puVar1[0x38] = 0xffff;
      *(undefined1 *)(puVar1 + 0x39) = 0;
      *(undefined1 *)((int)puVar1 + 0x73) = 0;
      *(undefined4 *)(puVar1 + 0x3a) = 0;
      *(undefined4 *)(puVar1 + 0x3c) = 0;
      *(undefined1 *)(puVar1 + 0x3e) = 0;
      *(undefined1 *)((int)puVar1 + 0x7d) = 0;
      puVar1[0x3f] = 0;
      puVar1 = puVar1 + 0x40;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    iVar2 = 0x7d;
    puVar1 = param_1;
    do {
      *(undefined4 *)(puVar1 + 16000) = 0xffffffff;
      *(undefined4 *)(puVar1 + 0x3e82) = 0;
      *(undefined1 *)(puVar1 + 0x3e84) = 0;
      *(undefined1 *)((int)puVar1 + 0x7d09) = 0;
      puVar1[0x3e85] = 0;
      *(undefined4 *)(puVar1 + 0x3e86) = 0xffffffff;
      *(undefined4 *)(puVar1 + 0x3e88) = 0;
      *(undefined1 *)(puVar1 + 0x3e8a) = 0;
      *(undefined1 *)((int)puVar1 + 0x7d15) = 0;
      puVar1[0x3e8b] = 0;
      *(undefined4 *)(puVar1 + 0x3e8c) = 0xffffffff;
      *(undefined4 *)(puVar1 + 0x3e8e) = 0;
      *(undefined1 *)(puVar1 + 0x3e90) = 0;
      *(undefined1 *)((int)puVar1 + 0x7d21) = 0;
      puVar1[0x3e91] = 0;
      *(undefined4 *)(puVar1 + 0x3e92) = 0xffffffff;
      *(undefined4 *)(puVar1 + 0x3e94) = 0;
      *(undefined1 *)(puVar1 + 0x3e96) = 0;
      *(undefined1 *)((int)puVar1 + 0x7d2d) = 0;
      puVar1[0x3e97] = 0;
      *(undefined4 *)(puVar1 + 0x3e98) = 0xffffffff;
      *(undefined4 *)(puVar1 + 0x3e9a) = 0;
      *(undefined1 *)(puVar1 + 0x3e9c) = 0;
      *(undefined1 *)((int)puVar1 + 0x7d39) = 0;
      puVar1[0x3e9d] = 0;
      *(undefined4 *)(puVar1 + 0x3e9e) = 0xffffffff;
      *(undefined4 *)(puVar1 + 0x3ea0) = 0;
      *(undefined1 *)(puVar1 + 0x3ea2) = 0;
      *(undefined1 *)((int)puVar1 + 0x7d45) = 0;
      puVar1[0x3ea3] = 0;
      *(undefined4 *)(puVar1 + 0x3ea4) = 0xffffffff;
      *(undefined4 *)(puVar1 + 0x3ea6) = 0;
      *(undefined1 *)(puVar1 + 0x3ea8) = 0;
      *(undefined1 *)((int)puVar1 + 0x7d51) = 0;
      puVar1[0x3ea9] = 0;
      *(undefined4 *)(puVar1 + 0x3eaa) = 0xffffffff;
      *(undefined4 *)(puVar1 + 0x3eac) = 0;
      *(undefined1 *)(puVar1 + 0x3eae) = 0;
      *(undefined1 *)((int)puVar1 + 0x7d5d) = 0;
      puVar1[0x3eaf] = 0;
      puVar1 = puVar1 + 0x30;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
    param_1[22000] = 0;
    param_1[0x55f1] = 0;
    return;
  }
  return;
}



// ==== 801cab54  zz_01cab54_ ====

void zz_01cab54_(void *param_1)

{
  int iVar1;
  void *pvVar2;
  
  if (param_1 != (void *)0x0) {
    iVar1 = 0;
    pvVar2 = param_1;
    do {
      gnt4_memset(pvVar2,0,0x29);
      *(undefined1 *)((int)pvVar2 + 0x29) = 0;
      *(undefined2 *)((int)pvVar2 + 0x2a) = 0;
      *(undefined4 *)((int)pvVar2 + 0x2c) = 0;
      gnt4_memset((void *)((int)pvVar2 + 0x30),-1,0x3c);
      iVar1 = iVar1 + 1;
      pvVar2 = (void *)((int)pvVar2 + 0x6c);
    } while (iVar1 < 0x14);
    iVar1 = 0x19;
    pvVar2 = param_1;
    do {
      *(undefined2 *)((int)pvVar2 + 0x870) = 0xffff;
      *(undefined1 *)((int)pvVar2 + 0x872) = 0;
      *(undefined1 *)((int)pvVar2 + 0x873) = 0;
      *(undefined4 *)((int)pvVar2 + 0x874) = 0;
      *(undefined4 *)((int)pvVar2 + 0x878) = 0;
      *(undefined1 *)((int)pvVar2 + 0x87c) = 0;
      *(undefined1 *)((int)pvVar2 + 0x87d) = 0;
      *(undefined2 *)((int)pvVar2 + 0x87e) = 0;
      *(undefined4 *)((int)pvVar2 + 0x880) = 0;
      *(undefined4 *)((int)pvVar2 + 0x884) = 0;
      *(undefined4 *)((int)pvVar2 + 0x888) = 0;
      *(undefined4 *)((int)pvVar2 + 0x88c) = 0;
      *(undefined2 *)((int)pvVar2 + 0x890) = 0xffff;
      *(undefined1 *)((int)pvVar2 + 0x892) = 0;
      *(undefined1 *)((int)pvVar2 + 0x893) = 0;
      *(undefined4 *)((int)pvVar2 + 0x894) = 0;
      *(undefined4 *)((int)pvVar2 + 0x898) = 0;
      *(undefined1 *)((int)pvVar2 + 0x89c) = 0;
      *(undefined1 *)((int)pvVar2 + 0x89d) = 0;
      *(undefined2 *)((int)pvVar2 + 0x89e) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8a0) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8a4) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8a8) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8ac) = 0;
      *(undefined2 *)((int)pvVar2 + 0x8b0) = 0xffff;
      *(undefined1 *)((int)pvVar2 + 0x8b2) = 0;
      *(undefined1 *)((int)pvVar2 + 0x8b3) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8b4) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8b8) = 0;
      *(undefined1 *)((int)pvVar2 + 0x8bc) = 0;
      *(undefined1 *)((int)pvVar2 + 0x8bd) = 0;
      *(undefined2 *)((int)pvVar2 + 0x8be) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8c0) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8c4) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8c8) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8cc) = 0;
      *(undefined2 *)((int)pvVar2 + 0x8d0) = 0xffff;
      *(undefined1 *)((int)pvVar2 + 0x8d2) = 0;
      *(undefined1 *)((int)pvVar2 + 0x8d3) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8d4) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8d8) = 0;
      *(undefined1 *)((int)pvVar2 + 0x8dc) = 0;
      *(undefined1 *)((int)pvVar2 + 0x8dd) = 0;
      *(undefined2 *)((int)pvVar2 + 0x8de) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8e0) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8e4) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8e8) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8ec) = 0;
      *(undefined2 *)((int)pvVar2 + 0x8f0) = 0xffff;
      *(undefined1 *)((int)pvVar2 + 0x8f2) = 0;
      *(undefined1 *)((int)pvVar2 + 0x8f3) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8f4) = 0;
      *(undefined4 *)((int)pvVar2 + 0x8f8) = 0;
      *(undefined1 *)((int)pvVar2 + 0x8fc) = 0;
      *(undefined1 *)((int)pvVar2 + 0x8fd) = 0;
      *(undefined2 *)((int)pvVar2 + 0x8fe) = 0;
      *(undefined4 *)((int)pvVar2 + 0x900) = 0;
      *(undefined4 *)((int)pvVar2 + 0x904) = 0;
      *(undefined4 *)((int)pvVar2 + 0x908) = 0;
      *(undefined4 *)((int)pvVar2 + 0x90c) = 0;
      *(undefined2 *)((int)pvVar2 + 0x910) = 0xffff;
      *(undefined1 *)((int)pvVar2 + 0x912) = 0;
      *(undefined1 *)((int)pvVar2 + 0x913) = 0;
      *(undefined4 *)((int)pvVar2 + 0x914) = 0;
      *(undefined4 *)((int)pvVar2 + 0x918) = 0;
      *(undefined1 *)((int)pvVar2 + 0x91c) = 0;
      *(undefined1 *)((int)pvVar2 + 0x91d) = 0;
      *(undefined2 *)((int)pvVar2 + 0x91e) = 0;
      *(undefined4 *)((int)pvVar2 + 0x920) = 0;
      *(undefined4 *)((int)pvVar2 + 0x924) = 0;
      *(undefined4 *)((int)pvVar2 + 0x928) = 0;
      *(undefined4 *)((int)pvVar2 + 0x92c) = 0;
      *(undefined2 *)((int)pvVar2 + 0x930) = 0xffff;
      *(undefined1 *)((int)pvVar2 + 0x932) = 0;
      *(undefined1 *)((int)pvVar2 + 0x933) = 0;
      *(undefined4 *)((int)pvVar2 + 0x934) = 0;
      *(undefined4 *)((int)pvVar2 + 0x938) = 0;
      *(undefined1 *)((int)pvVar2 + 0x93c) = 0;
      *(undefined1 *)((int)pvVar2 + 0x93d) = 0;
      *(undefined2 *)((int)pvVar2 + 0x93e) = 0;
      *(undefined4 *)((int)pvVar2 + 0x940) = 0;
      *(undefined4 *)((int)pvVar2 + 0x944) = 0;
      *(undefined4 *)((int)pvVar2 + 0x948) = 0;
      *(undefined4 *)((int)pvVar2 + 0x94c) = 0;
      *(undefined2 *)((int)pvVar2 + 0x950) = 0xffff;
      *(undefined1 *)((int)pvVar2 + 0x952) = 0;
      *(undefined1 *)((int)pvVar2 + 0x953) = 0;
      *(undefined4 *)((int)pvVar2 + 0x954) = 0;
      *(undefined4 *)((int)pvVar2 + 0x958) = 0;
      *(undefined1 *)((int)pvVar2 + 0x95c) = 0;
      *(undefined1 *)((int)pvVar2 + 0x95d) = 0;
      *(undefined2 *)((int)pvVar2 + 0x95e) = 0;
      *(undefined4 *)((int)pvVar2 + 0x960) = 0;
      *(undefined4 *)((int)pvVar2 + 0x964) = 0;
      *(undefined4 *)((int)pvVar2 + 0x968) = 0;
      *(undefined4 *)((int)pvVar2 + 0x96c) = 0;
      pvVar2 = (void *)((int)pvVar2 + 0x100);
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    *(undefined2 *)((int)param_1 + 0x2170) = 0;
    *(undefined2 *)((int)param_1 + 0x2172) = 0;
    gnt4_memset((void *)((int)param_1 + 0x2174),0,0x10);
  }
  return;
}



// ==== 801cada4  zz_01cada4_ ====

void zz_01cada4_(char *param_1,undefined2 *param_2,char *param_3)

{
  zz_01ca918_(param_1);
  zz_01ca948_(param_2);
  zz_01cab54_(param_3);
  zz_01cae04_(param_1,param_3);
  return;
}



// ==== 801cae04  zz_01cae04_ ====

void zz_01cae04_(char *param_1,char *param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  short *psVar4;
  char *pcVar5;
  undefined2 local_28 [2];
  short local_24 [6];
  
  if (param_2 != (char *)0x0) {
    iVar2 = 0;
    psVar4 = *(short **)PTR_PTR_8035b158;
    pcVar3 = param_2;
    pcVar5 = param_2;
    while( true ) {
      if (*psVar4 < 0) break;
      *(short *)(pcVar5 + 0x870) = *psVar4;
      iVar1 = 0;
      pcVar5[0x872] = '\0';
      pcVar5[0x873] = '\0';
      if (param_1 != (char *)0x0) {
        iVar1 = *(int *)(param_1 + 0x50);
        *(int *)(param_1 + 0x50) = iVar1 + 1;
      }
      *(int *)(pcVar5 + 0x874) = iVar1;
      if (*(short *)(pcVar5 + 0x870) != 0x615) {
        pcVar5[0x87c] = '\x01';
      }
      *(short *)(param_2 + 0x2172) = *(short *)(param_2 + 0x2172) + 1;
      local_24[0] = *(short *)(pcVar5 + 0x870);
      zz_01cb368_((int)param_1,local_24,(int)pcVar5[0x872]);
      if (iVar2 == 0) {
        pcVar3[0x30] = '\0';
        pcVar3[0x31] = '\0';
        param_2[0x29] = param_2[0x29] + '\x01';
        local_28[0] = *(undefined2 *)(pcVar5 + 0x870);
        iVar1 = zz_0066168_((char *)local_28,(int)pcVar5[0x872]);
        *(int *)(param_2 + 0x2c) = *(int *)(param_2 + 0x2c) + iVar1;
        *(uint *)(pcVar5 + 0x880) = *(uint *)(pcVar5 + 0x880) | 1;
      }
      pcVar5 = pcVar5 + 0x20;
      psVar4 = psVar4 + 1;
      pcVar3 = pcVar3 + 2;
      iVar2 = iVar2 + 1;
    }
    if (-1 < param_2[0x29]) {
      sprintf(param_2,&DAT_802b3690);
      *(short *)(param_2 + 0x2170) = *(short *)(param_2 + 0x2170) + 1;
    }
    sprintf(param_2 + 0x2174,&DAT_8043bd50);
    if (param_1 != (char *)0x0) {
      strcpy(param_1,param_2 + 0x2174);
      param_1[0x54] = '\0';
      param_1[0x55] = '\0';
      param_1[0x56] = '\0';
      param_1[0x57] = '\x01';
      *(uint *)(param_1 + 0x54) = *(uint *)(param_1 + 0x54) | 0x40;
    }
  }
  return;
}



// ==== 801caf80  zz_01caf80_ ====

void zz_01caf80_(int param_1,short *param_2,int param_3,short *param_4,int param_5)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  short local_28 [2];
  short local_24 [6];
  
  iVar1 = 0;
  if (*(short *)(param_3 + 0x2172) < 200) {
    iVar2 = 0;
    iVar4 = param_3;
    while ((iVar2 < 200 && (iVar1 == 0))) {
      if (*(short *)(iVar4 + 0x870) < 0) {
        local_24[0] = *param_4;
        *(short *)(iVar4 + 0x870) = local_24[0];
        *(char *)(iVar4 + 0x872) = (char)param_5;
        *(undefined1 *)(iVar4 + 0x873) = 0;
        iVar1 = *(int *)(param_1 + 0x50);
        *(int *)(param_1 + 0x50) = iVar1 + 1;
        *(int *)(iVar4 + 0x874) = iVar1;
        *(undefined4 *)(iVar4 + 0x878) = 0;
        *(undefined1 *)(iVar4 + 0x87c) = 1;
        *(undefined4 *)(iVar4 + 0x880) = 0;
        *(short *)(param_3 + 0x2172) = *(short *)(param_3 + 0x2172) + 1;
        zz_01cb368_(param_1,local_24,param_5);
        iVar1 = 1;
      }
      iVar4 = iVar4 + 0x20;
      iVar2 = iVar2 + 1;
    }
  }
  else if (param_2[22000] < 2000) {
    iVar4 = 0;
    psVar3 = param_2;
    while ((iVar4 < 2000 && (iVar1 == 0))) {
      if (*psVar3 < 0) {
        local_28[0] = *param_4;
        *psVar3 = local_28[0];
        *(char *)(psVar3 + 1) = (char)param_5;
        *(undefined1 *)((int)psVar3 + 3) = 0;
        iVar1 = *(int *)(param_1 + 0x50);
        *(int *)(param_1 + 0x50) = iVar1 + 1;
        *(int *)(psVar3 + 2) = iVar1;
        psVar3[4] = 0;
        psVar3[5] = 0;
        *(undefined1 *)(psVar3 + 6) = 1;
        param_2[22000] = param_2[22000] + 1;
        zz_01cb368_(param_1,local_28,param_5);
        iVar1 = 2;
      }
      psVar3 = psVar3 + 8;
      iVar4 = iVar4 + 1;
    }
  }
  return;
}



// ==== 801cb0ec  zz_01cb0ec_ ====

void zz_01cb0ec_(int param_1,short *param_2,int param_3,short *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  short *psVar4;
  short local_28 [2];
  short local_24 [6];
  
  iVar1 = 0;
  if (*(short *)(param_3 + 0x2172) < 200) {
    iVar2 = 0;
    iVar3 = param_3;
    while ((iVar2 < 200 && (iVar1 == 0))) {
      if (*(short *)(iVar3 + 0x870) < 0) {
        *(short *)(iVar3 + 0x870) = *param_4;
        *(undefined1 *)(iVar3 + 0x872) = *(undefined1 *)(param_4 + 1);
        *(undefined1 *)(iVar3 + 0x873) = *(undefined1 *)((int)param_4 + 3);
        iVar1 = *(int *)(param_1 + 0x50);
        *(int *)(param_1 + 0x50) = iVar1 + 1;
        *(int *)(iVar3 + 0x874) = iVar1;
        *(undefined4 *)(iVar3 + 0x878) = *(undefined4 *)(param_4 + 4);
        *(undefined1 *)(iVar3 + 0x87c) = 1;
        *(undefined4 *)(iVar3 + 0x880) = 0;
        *(short *)(param_3 + 0x2172) = *(short *)(param_3 + 0x2172) + 1;
        local_24[0] = *param_4;
        zz_01cb368_(param_1,local_24,(int)*(char *)(param_4 + 1));
        iVar1 = 1;
      }
      iVar3 = iVar3 + 0x20;
      iVar2 = iVar2 + 1;
    }
  }
  else if (param_2[22000] < 2000) {
    iVar3 = 0;
    psVar4 = param_2;
    while ((iVar3 < 2000 && (iVar1 == 0))) {
      if (*psVar4 < 0) {
        *psVar4 = *param_4;
        *(undefined1 *)(psVar4 + 1) = *(undefined1 *)(param_4 + 1);
        *(undefined1 *)((int)psVar4 + 3) = *(undefined1 *)((int)param_4 + 3);
        iVar1 = *(int *)(param_1 + 0x50);
        *(int *)(param_1 + 0x50) = iVar1 + 1;
        *(int *)(psVar4 + 2) = iVar1;
        *(undefined4 *)(psVar4 + 4) = *(undefined4 *)(param_4 + 4);
        *(undefined1 *)(psVar4 + 6) = 1;
        param_2[22000] = param_2[22000] + 1;
        local_28[0] = *param_4;
        zz_01cb368_(param_1,local_28,(int)*(char *)(param_4 + 1));
        iVar1 = 2;
      }
      psVar4 = psVar4 + 8;
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



// ==== 801cb278  zz_01cb278_ ====

int zz_01cb278_(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  if (*(short *)(param_2 + 0xabe2) < 1000) {
    uVar3 = *param_3;
    iVar4 = 0;
    iVar1 = param_2;
    while ((iVar4 < 1000 && (iVar5 == 0))) {
      if (*(int *)(iVar1 + 32000) < 0) {
        *(undefined4 *)(iVar1 + 32000) = uVar3;
        iVar5 = 1;
        iVar2 = *(int *)(param_1 + 0x50);
        *(int *)(param_1 + 0x50) = iVar2 + 1;
        *(int *)(iVar1 + 0x7d04) = iVar2;
        *(undefined1 *)(iVar1 + 0x7d08) = 1;
        *(short *)(param_2 + 0xabe2) = *(short *)(param_2 + 0xabe2) + 1;
      }
      iVar1 = iVar1 + 0xc;
      iVar4 = iVar4 + 1;
    }
  }
  return iVar5;
}



// ==== 801cb2f0  zz_01cb2f0_ ====

int zz_01cb2f0_(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  if (*(short *)(param_2 + 0xabe2) < 1000) {
    iVar3 = 0;
    iVar1 = param_2;
    while ((iVar3 < 1000 && (iVar4 == 0))) {
      if (*(int *)(iVar1 + 32000) < 0) {
        iVar4 = 1;
        *(undefined4 *)(iVar1 + 32000) = *param_3;
        iVar2 = *(int *)(param_1 + 0x50);
        *(int *)(param_1 + 0x50) = iVar2 + 1;
        *(int *)(iVar1 + 0x7d04) = iVar2;
        *(undefined1 *)(iVar1 + 0x7d08) = 1;
        *(short *)(param_2 + 0xabe2) = *(short *)(param_2 + 0xabe2) + 1;
      }
      iVar1 = iVar1 + 0xc;
      iVar3 = iVar3 + 1;
    }
  }
  return iVar4;
}



// ==== 801cb368  zz_01cb368_ ====

void zz_01cb368_(int param_1,short *param_2,int param_3)

{
  short sVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char local_80 [4];
  char local_7c [4];
  char local_78 [4];
  char local_74 [4];
  char local_70 [4];
  char local_6c [4];
  char local_68 [4];
  char local_64 [4];
  char local_60 [4];
  char local_5c [4];
  char local_58 [4];
  char local_54 [4];
  char local_50 [4];
  char local_4c [4];
  char local_48 [4];
  char local_44 [4];
  char local_40 [4];
  char local_3c [4];
  char local_38 [4];
  char local_34 [4];
  char local_30 [4];
  char local_2c [4];
  char local_28 [4];
  char local_24 [4];
  short local_20 [2];
  undefined2 local_1c;
  undefined2 local_18;
  
  if (param_1 != 0) {
    local_20[0] = *param_2;
    iVar3 = zz_00661d8_((char *)local_20);
    if (-1 < iVar3) {
      iVar5 = param_1 + iVar3;
      bVar2 = (byte)(1 << param_3);
      *(byte *)(iVar5 + 0x58) = *(byte *)(iVar5 + 0x58) | bVar2;
      *(byte *)(iVar5 + 0x158) = *(byte *)(iVar5 + 0x158) | bVar2;
    }
    sVar1 = *param_2;
    if (sVar1 == 0x505) {
      local_18 = 0x506;
      local_1c = 0x503;
      local_28[0] = '\x05';
      local_28[1] = '\x03';
      local_24[0] = '\x05';
      local_24[1] = '\x06';
      iVar5 = zz_00661d8_(local_28);
      iVar4 = zz_00661d8_(local_24);
      zz_01cb7b8_(param_1,iVar3,iVar4,iVar5);
    }
    else if (sVar1 == 0x506) {
      local_30[0] = '\x05';
      local_30[1] = '\x03';
      local_2c[0] = '\x05';
      local_2c[1] = '\x05';
      iVar5 = zz_00661d8_(local_30);
      iVar4 = zz_00661d8_(local_2c);
      zz_01cb7b8_(param_1,iVar4,iVar3,iVar5);
    }
    else if (sVar1 == 0x511) {
      local_38[0] = '\x05';
      local_38[1] = '\x0f';
      local_34[0] = '\x05';
      local_34[1] = '\x12';
      iVar5 = zz_00661d8_(local_38);
      iVar4 = zz_00661d8_(local_34);
      zz_01cb7b8_(param_1,iVar3,iVar4,iVar5);
    }
    else if (sVar1 == 0x512) {
      local_40[0] = '\x05';
      local_40[1] = '\x0f';
      local_3c[0] = '\x05';
      local_3c[1] = '\x11';
      iVar5 = zz_00661d8_(local_40);
      iVar4 = zz_00661d8_(local_3c);
      zz_01cb7b8_(param_1,iVar4,iVar3,iVar5);
    }
    else if (sVar1 == 0x600) {
      local_48[0] = '\x06';
      local_48[1] = '\x02';
      local_44[0] = '\x06';
      local_44[1] = '\x01';
      iVar5 = zz_00661d8_(local_48);
      iVar4 = zz_00661d8_(local_44);
      zz_01cb7b8_(param_1,iVar3,iVar4,iVar5);
      local_50[0] = '\x06';
      local_50[1] = '\f';
      local_4c[0] = '\x06';
      local_4c[1] = '\t';
      iVar5 = zz_00661d8_(local_50);
      iVar4 = zz_00661d8_(local_4c);
      zz_01cb7b8_(param_1,iVar3,iVar4,iVar5);
    }
    else if (sVar1 == 0x601) {
      local_58[0] = '\x06';
      local_58[1] = '\x02';
      local_54[0] = '\x06';
      local_54[1] = '\0';
      iVar5 = zz_00661d8_(local_58);
      iVar4 = zz_00661d8_(local_54);
      zz_01cb7b8_(param_1,iVar4,iVar3,iVar5);
      local_60[0] = '\x06';
      local_60[1] = '\x0e';
      local_5c[0] = '\x06';
      local_5c[1] = '\b';
      iVar5 = zz_00661d8_(local_60);
      iVar4 = zz_00661d8_(local_5c);
      zz_01cb7b8_(param_1,iVar4,iVar3,iVar5);
    }
    else if (sVar1 == 0x608) {
      local_68[0] = '\x06';
      local_68[1] = '\x0e';
      local_64[0] = '\x06';
      local_64[1] = '\x01';
      iVar5 = zz_00661d8_(local_68);
      iVar4 = zz_00661d8_(local_64);
      zz_01cb7b8_(param_1,iVar3,iVar4,iVar5);
      local_70[0] = '\x06';
      local_70[1] = '\n';
      local_6c[0] = '\x06';
      local_6c[1] = '\t';
      iVar5 = zz_00661d8_(local_70);
      iVar4 = zz_00661d8_(local_6c);
      zz_01cb7b8_(param_1,iVar3,iVar4,iVar5);
    }
    else if (sVar1 == 0x609) {
      local_78[0] = '\x06';
      local_78[1] = '\f';
      local_74[0] = '\x06';
      local_74[1] = '\0';
      iVar5 = zz_00661d8_(local_78);
      iVar4 = zz_00661d8_(local_74);
      zz_01cb7b8_(param_1,iVar4,iVar3,iVar5);
      local_80[0] = '\x06';
      local_80[1] = '\n';
      local_7c[0] = '\x06';
      local_7c[1] = '\b';
      iVar5 = zz_00661d8_(local_80);
      iVar4 = zz_00661d8_(local_7c);
      zz_01cb7b8_(param_1,iVar4,iVar3,iVar5);
    }
  }
  return;
}



// ==== 801cb750  zz_01cb750_ ====

void zz_01cb750_(int param_1,undefined2 *param_2,int param_3)

{
  int iVar1;
  undefined2 local_18 [8];
  
  if (param_1 != 0) {
    local_18[0] = *param_2;
    iVar1 = zz_00661d8_((char *)local_18);
    if (-1 < iVar1) {
      *(byte *)(param_1 + iVar1 + 0x158) = *(byte *)(param_1 + iVar1 + 0x158) | (byte)(1 << param_3)
      ;
    }
  }
  return;
}



// ==== 801cb7b8  zz_01cb7b8_ ====

void zz_01cb7b8_(int param_1,int param_2,int param_3,int param_4)

{
  byte bVar1;
  int iVar2;
  
  bVar1 = *(byte *)(param_1 + param_2 + 0x58);
  if (bVar1 == 0) {
    return;
  }
  if (*(char *)(param_1 + param_3 + 0x58) == '\0') {
    return;
  }
  iVar2 = param_1 + param_4;
  *(byte *)(iVar2 + 0x58) = *(byte *)(iVar2 + 0x58) | bVar1;
  *(byte *)(iVar2 + 0x158) = *(byte *)(iVar2 + 0x158) | *(byte *)(param_1 + param_2 + 0x58);
  return;
}



// ==== 801cb7fc  zz_01cb7fc_ ====

byte zz_01cb7fc_(int *param_1,int *param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = (int)*(char *)(param_1 + 4) + (int)*(char *)((int)param_1 + 0x11);
  iVar4 = (int)*(char *)(param_2 + 4) + (int)*(char *)((int)param_2 + 0x11);
  bVar1 = 0x898 < iVar4 + (((int)*(short *)(*param_1 + 0x2172) + (int)*(short *)(param_1[1] + 44000)
                           ) - iVar5);
  if (0x898 < iVar5 + (((int)*(short *)(*param_2 + 0x2172) + (int)*(short *)(param_2[1] + 44000)) -
                      iVar4)) {
    bVar1 = bVar1 | 2;
  }
  iVar3 = (int)*(char *)((int)param_1 + 0x12);
  iVar2 = (int)*(char *)((int)param_2 + 0x12);
  if (1000 < iVar2 + (*(short *)(param_1[1] + 0xabe2) - iVar3)) {
    bVar1 = bVar1 | 4;
  }
  if (1000 < iVar3 + (*(short *)(param_2[1] + 0xabe2) - iVar2)) {
    bVar1 = bVar1 | 8;
  }
  if (7 < iVar3 + iVar5) {
    bVar1 = bVar1 | 0x10;
  }
  if (7 < iVar2 + iVar4) {
    bVar1 = bVar1 | 0x20;
  }
  return bVar1;
}



// ==== 801cb8f0  zz_01cb8f0_ ====

void zz_01cb8f0_(int *param_1,int *param_2)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  
  iVar2 = (int)*(char *)(param_1 + 4) +
          (int)*(char *)((int)param_1 + 0x11) + (int)*(char *)((int)param_1 + 0x12);
  iVar8 = 7;
  if (iVar2 < 7) {
    iVar8 = iVar2;
  }
  iVar2 = 0;
  iVar6 = 0;
  piVar7 = param_1;
  while( true ) {
    if (iVar8 <= iVar2) break;
    sVar1 = *(short *)(piVar7 + 5);
    if (sVar1 == 0) {
      puVar5 = (undefined4 *)(param_1[3] + iVar6);
      puVar4 = (undefined4 *)(*param_1 + *(short *)((int)piVar7 + 0x16) * 0x20 + 0x870);
      uVar3 = puVar4[1];
      *puVar5 = *puVar4;
      puVar5[1] = uVar3;
      uVar3 = puVar4[3];
      puVar5[2] = puVar4[2];
      puVar5[3] = uVar3;
      zz_01cbe54_(*param_1,(int)*(short *)((int)piVar7 + 0x16));
    }
    else if (sVar1 == 1) {
      puVar4 = (undefined4 *)(param_1[1] + *(short *)((int)piVar7 + 0x16) * 0x10);
      puVar5 = (undefined4 *)(param_1[3] + iVar6);
      uVar3 = puVar4[1];
      *puVar5 = *puVar4;
      puVar5[1] = uVar3;
      uVar3 = puVar4[3];
      puVar5[2] = puVar4[2];
      puVar5[3] = uVar3;
      zz_01cbd00_(param_1[1],(int)*(short *)((int)piVar7 + 0x16));
    }
    else if (sVar1 == 2) {
      puVar5 = (undefined4 *)(param_1[3] + iVar6);
      puVar4 = (undefined4 *)(param_1[1] + *(short *)((int)piVar7 + 0x16) * 0xc + 32000);
      uVar3 = puVar4[1];
      *puVar5 = *puVar4;
      puVar5[1] = uVar3;
      puVar5[2] = puVar4[2];
      zz_01cbe14_(param_1[1],(int)*(short *)((int)piVar7 + 0x16));
    }
    piVar7 = piVar7 + 1;
    iVar6 = iVar6 + 0x10;
    iVar2 = iVar2 + 1;
  }
  iVar2 = (int)*(char *)(param_2 + 4) +
          (int)*(char *)((int)param_2 + 0x11) + (int)*(char *)((int)param_2 + 0x12);
  iVar8 = 7;
  if (iVar2 < 7) {
    iVar8 = iVar2;
  }
  iVar2 = 0;
  iVar6 = 0;
  piVar7 = param_2;
  while( true ) {
    if (iVar8 <= iVar2) break;
    sVar1 = *(short *)(piVar7 + 5);
    if (sVar1 == 0) {
      puVar5 = (undefined4 *)(param_2[3] + iVar6);
      puVar4 = (undefined4 *)(*param_2 + *(short *)((int)piVar7 + 0x16) * 0x20 + 0x870);
      uVar3 = puVar4[1];
      *puVar5 = *puVar4;
      puVar5[1] = uVar3;
      uVar3 = puVar4[3];
      puVar5[2] = puVar4[2];
      puVar5[3] = uVar3;
      zz_01cbe54_(*param_2,(int)*(short *)((int)piVar7 + 0x16));
    }
    else if (sVar1 == 1) {
      puVar4 = (undefined4 *)(param_2[1] + *(short *)((int)piVar7 + 0x16) * 0x10);
      puVar5 = (undefined4 *)(param_2[3] + iVar6);
      uVar3 = puVar4[1];
      *puVar5 = *puVar4;
      puVar5[1] = uVar3;
      uVar3 = puVar4[3];
      puVar5[2] = puVar4[2];
      puVar5[3] = uVar3;
      zz_01cbd00_(param_2[1],(int)*(short *)((int)piVar7 + 0x16));
    }
    else if (sVar1 == 2) {
      puVar5 = (undefined4 *)(param_2[3] + iVar6);
      puVar4 = (undefined4 *)(param_2[1] + *(short *)((int)piVar7 + 0x16) * 0xc + 32000);
      uVar3 = puVar4[1];
      *puVar5 = *puVar4;
      puVar5[1] = uVar3;
      puVar5[2] = puVar4[2];
      zz_01cbe14_(param_2[1],(int)*(short *)((int)piVar7 + 0x16));
    }
    piVar7 = piVar7 + 1;
    iVar6 = iVar6 + 0x10;
    iVar2 = iVar2 + 1;
  }
  return;
}



// ==== 801cbba4  zz_01cbba4_ ====

void zz_01cbba4_(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  
  iVar1 = (int)*(char *)(param_2 + 4) +
          (int)*(char *)((int)param_2 + 0x11) + (int)*(char *)((int)param_2 + 0x12);
  iVar4 = 7;
  if (iVar1 < 7) {
    iVar4 = iVar1;
  }
  iVar2 = 0;
  piVar3 = param_2;
  for (iVar1 = 0; iVar1 < iVar4; iVar1 = iVar1 + 1) {
    if (*(short *)(piVar3 + 5) < 2) {
      zz_01cb0ec_(param_1[2],(short *)param_1[1],*param_1,(short *)(param_2[3] + iVar2));
    }
    else if (*(short *)(piVar3 + 5) == 2) {
      zz_01cb2f0_(param_1[2],param_1[1],(undefined4 *)(param_2[3] + iVar2));
    }
    piVar3 = piVar3 + 1;
    iVar2 = iVar2 + 0x10;
  }
  iVar1 = (int)*(char *)(param_1 + 4) +
          (int)*(char *)((int)param_1 + 0x11) + (int)*(char *)((int)param_1 + 0x12);
  iVar4 = 7;
  if (iVar1 < 7) {
    iVar4 = iVar1;
  }
  iVar2 = 0;
  piVar3 = param_1;
  for (iVar1 = 0; iVar1 < iVar4; iVar1 = iVar1 + 1) {
    if (*(short *)(piVar3 + 5) < 2) {
      zz_01cb0ec_(param_2[2],(short *)param_2[1],*param_2,(short *)(param_1[3] + iVar2));
    }
    else if (*(short *)(piVar3 + 5) == 2) {
      zz_01cb2f0_(param_2[2],param_2[1],(undefined4 *)(param_1[3] + iVar2));
    }
    piVar3 = piVar3 + 1;
    iVar2 = iVar2 + 0x10;
  }
  return;
}



// ==== 801cbd00  zz_01cbd00_ ====

void zz_01cbd00_(int param_1,int param_2)

{
  short *psVar1;
  
  psVar1 = (short *)(param_1 + param_2 * 0x10);
  if (*psVar1 < 0) {
    return;
  }
  *psVar1 = -1;
  *(undefined1 *)(psVar1 + 1) = 0;
  *(undefined1 *)((int)psVar1 + 3) = 0;
  psVar1[2] = 0;
  psVar1[3] = 0;
  psVar1[4] = 0;
  psVar1[5] = 0;
  *(undefined1 *)(psVar1 + 6) = 0;
  *(short *)(param_1 + 44000) = *(short *)(param_1 + 44000) + -1;
  return;
}



// ==== 801cbd48  zz_01cbd48_ ====

int zz_01cbd48_(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  
  uVar2 = (int)*(short *)(param_2 + 0x2172) ^ 200;
  iVar1 = -((int)(((int)uVar2 >> 1) - (uVar2 & 200)) >> 0x1f);
  if ((iVar1 != 0) && (psVar5 = (short *)(param_1 + param_3 * 0x10), -1 < *psVar5)) {
    for (iVar6 = 0; iVar6 < 200; iVar6 = iVar6 + 1) {
      iVar4 = param_2 + iVar6 * 0x20;
      if (*(short *)(iVar4 + 0x870) < 0) {
        iVar6 = 200;
        uVar3 = *(undefined4 *)(psVar5 + 2);
        *(undefined4 *)(iVar4 + 0x870) = *(undefined4 *)psVar5;
        *(undefined4 *)(iVar4 + 0x874) = uVar3;
        uVar3 = *(undefined4 *)(psVar5 + 6);
        *(undefined4 *)(iVar4 + 0x878) = *(undefined4 *)(psVar5 + 4);
        *(undefined4 *)(iVar4 + 0x87c) = uVar3;
        *(undefined4 *)(iVar4 + 0x880) = 0;
        *(short *)(param_2 + 0x2172) = *(short *)(param_2 + 0x2172) + 1;
      }
    }
    *psVar5 = -1;
    *(undefined1 *)(psVar5 + 1) = 0;
    *(undefined1 *)((int)psVar5 + 3) = 0;
    psVar5[2] = 0;
    psVar5[3] = 0;
    psVar5[4] = 0;
    psVar5[5] = 0;
    *(undefined1 *)(psVar5 + 6) = 0;
    *(short *)(param_1 + 44000) = *(short *)(param_1 + 44000) + -1;
  }
  return iVar1;
}



// ==== 801cbe14  zz_01cbe14_ ====

void zz_01cbe14_(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + param_2 * 0xc + 32000);
  if (*piVar1 < 0) {
    return;
  }
  *piVar1 = -1;
  piVar1[1] = 0;
  *(undefined1 *)(piVar1 + 2) = 0;
  *(short *)(param_1 + 0xabe2) = *(short *)(param_1 + 0xabe2) + -1;
  return;
}



// ==== 801cbe54  zz_01cbe54_ ====

void zz_01cbe54_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  int iVar4;
  
  psVar3 = (short *)(param_1 + param_2 * 0x20 + 0x870);
  if (-1 < *psVar3) {
    if (*(int *)(psVar3 + 8) != 0) {
      iVar2 = 0;
      iVar4 = param_1;
      do {
        if ((*(uint *)(psVar3 + 8) & 1 << iVar2) != 0) {
          for (iVar1 = 0; iVar1 < 0x1e; iVar1 = iVar1 + 1) {
            if (param_2 == *(short *)(iVar4 + iVar1 * 2 + 0x30)) {
              zz_01ccb94_(param_1,iVar2,iVar1);
              iVar1 = 0x1e;
            }
          }
        }
        iVar2 = iVar2 + 1;
        iVar4 = iVar4 + 0x6c;
      } while (iVar2 < 0x14);
    }
    *psVar3 = -1;
    *(undefined1 *)(psVar3 + 1) = 0;
    *(undefined1 *)((int)psVar3 + 3) = 0;
    psVar3[2] = 0;
    psVar3[3] = 0;
    psVar3[4] = 0;
    psVar3[5] = 0;
    *(undefined1 *)(psVar3 + 6) = 0;
    psVar3[8] = 0;
    psVar3[9] = 0;
    *(short *)(param_1 + 0x2172) = *(short *)(param_1 + 0x2172) + -1;
  }
  return;
}



// ==== 801cbf38  zz_01cbf38_ ====

int zz_01cbf38_(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  undefined4 uVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  int iVar7;
  short *psVar8;
  
  uVar2 = (int)*(short *)(param_1 + 44000) ^ 2000;
  iVar1 = -((int)(((int)uVar2 >> 1) - (uVar2 & 2000)) >> 0x1f);
  if ((iVar1 != 0) && (psVar8 = (short *)(param_2 + param_3 * 0x20 + 0x870), -1 < *psVar8)) {
    if (*(int *)(psVar8 + 8) != 0) {
      iVar6 = 0;
      iVar7 = param_2;
      do {
        if ((*(uint *)(psVar8 + 8) & 1 << iVar6) != 0) {
          for (iVar4 = 0; iVar4 < 0x1e; iVar4 = iVar4 + 1) {
            if (param_3 == *(short *)(iVar7 + iVar4 * 2 + 0x30)) {
              zz_01ccb94_(param_2,iVar6,iVar4);
              iVar4 = 0x1e;
            }
          }
        }
        iVar6 = iVar6 + 1;
        iVar7 = iVar7 + 0x6c;
      } while (iVar6 < 0x14);
    }
    for (iVar7 = 0; iVar7 < 2000; iVar7 = iVar7 + 1) {
      psVar5 = (short *)(param_1 + iVar7 * 0x10);
      if (*psVar5 < 0) {
        iVar7 = 2000;
        uVar3 = *(undefined4 *)(psVar8 + 2);
        *(undefined4 *)psVar5 = *(undefined4 *)psVar8;
        *(undefined4 *)(psVar5 + 2) = uVar3;
        uVar3 = *(undefined4 *)(psVar8 + 6);
        *(undefined4 *)(psVar5 + 4) = *(undefined4 *)(psVar8 + 4);
        *(undefined4 *)(psVar5 + 6) = uVar3;
        *(short *)(param_1 + 44000) = *(short *)(param_1 + 44000) + 1;
      }
    }
    *psVar8 = -1;
    *(undefined1 *)(psVar8 + 1) = 0;
    *(undefined1 *)((int)psVar8 + 3) = 0;
    psVar8[2] = 0;
    psVar8[3] = 0;
    psVar8[4] = 0;
    psVar8[5] = 0;
    *(undefined1 *)(psVar8 + 6) = 0;
    psVar8[8] = 0;
    psVar8[9] = 0;
    *(short *)(param_2 + 0x2172) = *(short *)(param_2 + 0x2172) + -1;
  }
  return iVar1;
}



