// ==== 80167760  zz_0167760_ ====

void zz_0167760_(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  byte bVar1;
  byte bVar2;
  float fVar3;
  undefined4 extraout_r4;
  float *pfVar4;
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
  
  bVar1 = *(byte *)(param_1 + 0x12);
  pfVar4 = (float *)(uint)bVar1;
  dVar8 = (double)*(float *)(param_1 + 0xd4);
  if (bVar1 == 2) {
    dVar9 = (double)FLOAT_8043aa14;
  }
  else {
    bVar2 = *(byte *)(param_2 + 0x3d);
    if ((bVar2 & 1) == 0) {
      if ((bVar2 & 0x1e) == 0) {
        if ((bVar2 & 0x20) == 0) {
          if ((bVar2 & 0x80) == 0) {
            if (bVar1 == 1) {
              dVar9 = (double)FLOAT_8043aa10;
            }
            else {
              dVar9 = (double)FLOAT_8043aa24;
            }
          }
          else {
            dVar9 = (double)FLOAT_8043aa24;
          }
        }
        else {
          dVar9 = (double)FLOAT_8043aa20;
        }
      }
      else {
        dVar9 = (double)FLOAT_8043aa1c;
      }
    }
    else {
      dVar9 = (double)FLOAT_8043aa18;
    }
  }
  fVar3 = FLOAT_8043aa2c;
  if (bVar1 == 0) {
    fVar3 = FLOAT_8043aa28;
  }
  if ((double)FLOAT_8043aa14 <= dVar9) {
    if (dVar9 <= dVar8) {
      if ((dVar9 < dVar8) &&
         (fVar3 = *(float *)(param_1 + 0xd4) - fVar3, *(float *)(param_1 + 0xd4) = fVar3,
         (double)fVar3 < dVar9)) {
        *(float *)(param_1 + 0xd4) = (float)dVar9;
      }
    }
    else {
      fVar3 = *(float *)(param_1 + 0xd4) + fVar3;
      *(float *)(param_1 + 0xd4) = fVar3;
      if (dVar9 < (double)fVar3) {
        *(float *)(param_1 + 0xd4) = (float)dVar9;
      }
    }
    if ((double)*(float *)(param_1 + 0xd4) != dVar8) {
      iVar6 = param_1;
      for (iVar5 = 0; iVar5 < *(char *)(param_1 + 0x13); iVar5 = iVar5 + 1) {
        uVar7 = zz_00086b8_((double)*(float *)(param_1 + 0xd4),dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,
                            in_f8,DAT_803bb384,*(int *)(iVar6 + 0xe0),pfVar4,param_4,param_5,param_6
                            ,param_7,param_8);
        zz_0007c30_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar6 + 0xe0),
                    extraout_r4,pfVar4,param_4,param_5,param_6,param_7,param_8);
        iVar6 = iVar6 + 4;
      }
    }
  }
  return;
}



// ==== 801678c8  FUN_801678c8 ====

void FUN_801678c8(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
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
  return;
}



// ==== 80167968  FUN_80167968 ====

/* WARNING: Removing unreachable block (ram,0x80167a1c) */
/* WARNING: Removing unreachable block (ram,0x80167978) */

void FUN_80167968(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined2 *puVar5;
  int iVar6;
  double dVar7;
  
  dVar7 = (double)FLOAT_8043aa10;
  puVar5 = &DAT_8034fe44;
  iVar6 = 0;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    puVar2 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar6);
    puVar2[6] = (float)dVar7;
    *(undefined2 *)(puVar2 + 8) = 0;
    *(undefined2 *)((int)puVar2 + 0x22) = *puVar5;
    uVar1 = *(undefined4 *)(puVar5 + 4);
    *puVar2 = *(undefined4 *)(puVar5 + 2);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(puVar5 + 6);
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb384,*(int *)(iVar4 + 0xe0),(int)(short)puVar5[1],param_12,
                          param_13,param_14,param_15,param_16);
    iVar6 = iVar6 + 0x24;
    puVar5 = puVar5 + 8;
    iVar4 = iVar4 + 4;
  }
  FUN_80167a38(param_9,param_10);
  return;
}



// ==== 80167a38  FUN_80167a38 ====

/* WARNING: Removing unreachable block (ram,0x80167bac) */
/* WARNING: Removing unreachable block (ram,0x80167a48) */

void FUN_80167a38(int param_1,int param_2)

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
  
  dVar9 = (double)FLOAT_8043aa10;
  iVar7 = 0;
  iVar6 = param_1;
  for (iVar5 = 0; iVar5 < *(char *)(param_1 + 0x13); iVar5 = iVar5 + 1) {
    iVar4 = *(int *)(param_1 + 0x54) + iVar7;
    *(undefined4 *)(iVar4 + 0x1c) = *(undefined4 *)(iVar4 + 0x18);
    fVar1 = FLOAT_8043aa2c;
    fVar2 = FLOAT_8043aa10;
    if (((ushort)*(byte *)(param_2 + 0x3d) & *(ushort *)(iVar4 + 0x22)) == 0) {
      if (0 < *(short *)(iVar4 + 0x20)) {
        *(short *)(iVar4 + 0x20) = *(short *)(iVar4 + 0x20) + 1;
        fVar3 = FLOAT_8043aa14;
        fVar1 = *(float *)(iVar4 + 0x18) - fVar1;
        *(float *)(iVar4 + 0x18) = fVar1;
        fVar2 = FLOAT_8043aa10;
        if (fVar1 <= fVar3) {
          *(undefined2 *)(iVar4 + 0x20) = 0;
          *(float *)(iVar4 + 0x18) = fVar2;
        }
      }
    }
    else {
      *(short *)(iVar4 + 0x20) = *(short *)(iVar4 + 0x20) + 1;
      if ((*(float *)(iVar4 + 0x18) < fVar2) &&
         (fVar1 = *(float *)(iVar4 + 0x18) + FLOAT_8043aa2c, *(float *)(iVar4 + 0x18) = fVar1,
         fVar2 <= fVar1)) {
        *(float *)(iVar4 + 0x18) = fVar2;
      }
    }
    while (0x7f < *(short *)(iVar4 + 0x20)) {
      *(short *)(iVar4 + 0x20) = *(short *)(iVar4 + 0x20) + -0x40;
    }
    dVar8 = zz_0045238_((short)((int)*(short *)(iVar4 + 0x20) << 10));
    fVar1 = FLOAT_8043aa34;
    if (*(short *)(iVar4 + 0x20) < 0x10) {
      fVar1 = FLOAT_8043aa30;
    }
    *(float *)(iVar4 + 0xc) = (float)(dVar8 * (double)fVar1 + dVar9);
    fVar1 = FLOAT_8043aa38;
    if (*(short *)(iVar4 + 0x20) < 0x10) {
      fVar1 = FLOAT_8043aa24;
    }
    *(float *)(iVar4 + 0x10) = (float)(dVar8 * (double)fVar1 + dVar9);
    *(float *)(iVar4 + 0x14) = (float)dVar9;
    if ((double)*(float *)(iVar4 + 0x18) != (double)*(float *)(iVar4 + 0x1c)) {
      zz_0007cac_((double)*(float *)(iVar4 + 0x18),*(int *)(iVar6 + 0xe0));
    }
    iVar7 = iVar7 + 0x24;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 80167bc8  FUN_80167bc8 ====

void FUN_80167bc8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
    if ((*(short *)(pfVar1 + 8) != 0) && (FLOAT_8043aa14 != pfVar1[6])) {
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



// ==== 80167ca0  FUN_80167ca0 ====

void FUN_80167ca0(int param_1)

{
  float fVar1;
  short sVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  undefined2 *puVar6;
  int iVar7;
  float *pfVar8;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  int iVar10;
  int iVar11;
  double dVar12;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  fVar4 = FLOAT_8043aa44;
  fVar5 = FLOAT_8043aa40;
  fVar1 = FLOAT_8043aa3c;
  iVar11 = 0;
  *(undefined2 *)(param_1 + 0x1c) = 0;
  iVar10 = *(char *)(param_1 + 0x12) * 0x10;
  puVar6 = (undefined2 *)(&DAT_8034fe94 + iVar10);
  *(undefined2 *)(param_1 + 0x1e) = *puVar6;
  dVar12 = (double)*(float *)(&DAT_8034fe98 + iVar10);
  *(float *)(param_1 + 0x38) = *(float *)(&DAT_8034fe98 + iVar10);
  *(float *)(param_1 + 0x3c) = fVar1;
  *(float *)(param_1 + 0x40) = fVar5;
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_8034fe98 + iVar10);
  *(float *)(param_1 + 0x68) = fVar4;
  *(float *)(param_1 + 0x6c) = fVar5;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x40);
  iVar10 = param_1;
  for (iVar9 = 0; fVar1 = FLOAT_8043aa48, fVar5 = FLOAT_8043aa14, iVar9 < *(char *)(param_1 + 0x13);
      iVar9 = iVar9 + 1) {
    pfVar8 = (float *)(*(int *)(param_1 + 0x54) + iVar11);
    if (iVar9 == 1) {
      *pfVar8 = FLOAT_8043aa4c;
      fVar1 = FLOAT_8043aa50;
      pfVar8[1] = fVar5;
      fVar4 = FLOAT_8043aa10;
      pfVar8[2] = fVar5;
      pfVar8[3] = fVar1;
      pfVar8[4] = fVar1;
      pfVar8[5] = fVar4;
    }
    else {
      pfVar8[2] = FLOAT_8043aa14;
      fVar4 = FLOAT_8043aa10;
      pfVar8[1] = fVar5;
      *pfVar8 = fVar5;
      pfVar8[3] = fVar1;
      pfVar8[4] = fVar1;
      pfVar8[5] = fVar4;
    }
    sVar2 = puVar6[4];
    *(short *)(pfVar8 + 8) = sVar2;
    iVar3 = DAT_803bb384;
    if (-1 < sVar2) {
      iVar7 = *(int *)(iVar10 + 0xe0);
      *(short *)((int)pfVar8 + 0x22) = *(short *)(pfVar8 + 8);
      zz_0006fb4_((double)fVar1,(double)fVar5,dVar12,in_f4,in_f5,in_f6,in_f7,in_f8,iVar3,iVar7,
                  (int)*(short *)(pfVar8 + 8),pfVar8,in_r7,in_r8,in_r9,in_r10);
    }
    iVar11 = iVar11 + 0x24;
    puVar6 = puVar6 + 1;
    iVar10 = iVar10 + 4;
  }
  return;
}



// ==== 80167df0  FUN_80167df0 ====

void FUN_80167df0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10)

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
  if (((ushort)*(byte *)(param_10 + 0x3e) & *(ushort *)(param_9 + 0x1e)) == 0) {
    local_1c = *(float *)(param_9 + 0x38);
    local_18 = *(undefined4 *)(param_9 + 0x3c);
    local_14 = *(undefined4 *)(param_9 + 0x40);
  }
  else {
    local_1c = *(float *)(param_9 + 100);
    local_18 = *(undefined4 *)(param_9 + 0x68);
    local_14 = *(undefined4 *)(param_9 + 0x6c);
  }
  local_28 = local_1c;
  local_24 = local_18;
  local_20 = local_14;
  gnt4_PSVECSubtract_bl(&local_28,(float *)(param_9 + 0x20),&local_28);
  gnt4_PSQUATScale_bl((double)FLOAT_8043aa34,&local_28,&local_28);
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



// ==== 80167ef8  FUN_80167ef8 ====

void FUN_80167ef8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
    if (-1 < *(short *)((int)pfVar2 + 0x22)) {
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



// ==== 80167fc4  FUN_80167fc4 ====

void FUN_80167fc4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10)

{
  undefined4 *puVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar9;
  undefined8 uVar10;
  
  fVar3 = FLOAT_8043aa54;
  fVar2 = FLOAT_8043aa14;
  dVar9 = (double)FLOAT_8043aa14;
  iVar7 = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0xffff;
  puVar6 = &DAT_8034ff04;
  *(float *)(param_9 + 0x38) = fVar2;
  *(float *)(param_9 + 0x3c) = fVar3;
  *(float *)(param_9 + 0x40) = fVar2;
  *(float *)(param_9 + 100) = fVar2;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar2;
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
  *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x3c);
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x40);
  for (iVar8 = 0; iVar8 < *(char *)(param_9 + 0x13); iVar8 = iVar8 + 1) {
    puVar5 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar7);
    uVar4 = puVar6[1];
    iVar7 = iVar7 + 0x24;
    *puVar5 = *puVar6;
    puVar5[1] = uVar4;
    puVar1 = puVar6 + 2;
    puVar6 = puVar6 + 3;
    puVar5[2] = *puVar1;
  }
  uVar10 = zz_0006fb4_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                       *(int *)(param_9 + 0xe0),99,iVar7,iVar8,in_r8,in_r9,in_r10);
  zz_01680ac_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10);
  return;
}



// ==== 801680ac  zz_01680ac_ ====

void zz_01680ac_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  float fVar4;
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
  
  sVar1 = *(short *)(&DAT_80434768 + ((*(char *)(param_10 + 0x3b) + 1) % 3) * 2);
  if ((*(byte *)(param_10 + 0x3d) & 1) == 0) {
    local_1c = *(float *)(param_9 + 0x38);
    local_18 = *(undefined4 *)(param_9 + 0x3c);
    local_14 = *(undefined4 *)(param_9 + 0x40);
  }
  else {
    local_1c = *(float *)(param_9 + 100);
    local_18 = *(undefined4 *)(param_9 + 0x68);
    local_14 = *(undefined4 *)(param_9 + 0x6c);
  }
  local_28 = local_1c;
  local_24 = local_18;
  local_20 = local_14;
  uVar3 = local_18;
  fVar4 = local_1c;
  gnt4_PSVECSubtract_bl(&local_28,(float *)(param_9 + 0x20),&local_28);
  gnt4_PSQUATScale_bl((double)FLOAT_8043aa34,&local_28,&local_28);
  uVar5 = gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_28,(float *)(param_9 + 0x20));
  iVar2 = DAT_803bb384;
  if ((int)sVar1 != (int)*(short *)(param_9 + 0x1c)) {
    *(short *)(param_9 + 0x1c) = sVar1;
    zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                *(int *)(param_9 + 0xe4),(int)sVar1,uVar3,fVar4,in_r8,in_r9,in_r10);
  }
  return;
}



// ==== 801681c0  FUN_801681c0 ====

void FUN_801681c0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
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
  
  dVar6 = (double)*(float *)(param_1 + 0x24);
  dVar7 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar6,dVar7,(float *)(param_1 + 0x114));
  iVar4 = 0;
  iVar3 = param_1;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
    uVar5 = zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar1);
    zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_48,
                (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
    iVar4 = iVar4 + 0x24;
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 8016826c  FUN_8016826c ====

void FUN_8016826c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,int param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  double dVar10;
  double dVar11;
  
  fVar3 = FLOAT_8043aa5c;
  fVar1 = FLOAT_8043aa14;
  puVar5 = &DAT_80350000;
  dVar11 = (double)FLOAT_8043aa14;
  dVar10 = (double)FLOAT_8043aa5c;
  puVar9 = &DAT_8034ff1c;
  iVar8 = 0;
  *(float *)(param_9 + 0x44) = FLOAT_8043aa10;
  fVar2 = FLOAT_8043aa58;
  *(float *)(param_9 + 0xd4) = fVar1;
  *(float *)(param_9 + 0x38) = fVar2;
  fVar2 = FLOAT_8043aa60;
  *(float *)(param_9 + 0x3c) = fVar1;
  *(float *)(param_9 + 0x40) = fVar1;
  *(float *)(param_9 + 100) = fVar1;
  *(float *)(param_9 + 0x68) = fVar1;
  *(float *)(param_9 + 0x6c) = fVar1;
  *(float *)(param_9 + 0x9c) = fVar3;
  *(float *)(param_9 + 0xa0) = fVar2;
  *(float *)(param_9 + 0xa4) = fVar1;
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
  *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x3c);
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x40);
  iVar7 = param_9;
  for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    uVar4 = puVar9[2];
    puVar5 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar8);
    *puVar5 = puVar9[1];
    puVar5[1] = uVar4;
    puVar5[2] = puVar9[3];
    puVar5 = (undefined4 *)*puVar9;
    dVar10 = (double)zz_0006fb4_(dVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_803bb384,*(int *)(iVar7 + 0xe0),(int)puVar5,param_12,param_13,
                                 param_14,param_15,param_16);
    puVar9 = puVar9 + 4;
    iVar8 = iVar8 + 0x24;
    iVar7 = iVar7 + 4;
  }
  zz_016836c_(dVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,puVar5,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8016836c  zz_016836c_ ====

/* WARNING: Removing unreachable block (ram,0x80168504) */
/* WARNING: Removing unreachable block (ram,0x8016837c) */

void zz_016836c_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float *pfVar3;
  undefined4 extraout_r4;
  undefined8 uVar4;
  double dVar5;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  dVar5 = (double)*(float *)(param_9 + 0x44);
  if ((*(byte *)(param_10 + 0x3d) & 1) == 0) {
    if ((*(byte *)(param_10 + 0x3f) & 1) == 0) {
      local_28 = *(float *)(param_9 + 0x38);
      local_24 = *(undefined4 *)(param_9 + 0x3c);
      local_20 = *(undefined4 *)(param_9 + 0x40);
    }
    else {
      local_28 = *(float *)(param_9 + 0x9c);
      local_24 = *(undefined4 *)(param_9 + 0xa0);
      local_20 = *(undefined4 *)(param_9 + 0xa4);
    }
  }
  else {
    local_28 = *(float *)(param_9 + 100);
    local_24 = *(undefined4 *)(param_9 + 0x68);
    local_20 = *(undefined4 *)(param_9 + 0x6c);
  }
  gnt4_PSVECSubtract_bl(&local_28,(float *)(param_9 + 0x20),&local_28);
  gnt4_PSQUATScale_bl((double)FLOAT_8043aa34,&local_28,&local_28);
  pfVar3 = (float *)(param_9 + 0x20);
  gnt4_PSVECAdd_bl(pfVar3,&local_28,pfVar3);
  fVar2 = FLOAT_8043aa10;
  if ((*(byte *)(param_10 + 0x3f) & 1) != 0) {
    fVar2 = FLOAT_8043aa14;
  }
  fVar1 = *(float *)(param_9 + 0x44);
  if (fVar2 <= fVar1) {
    if ((fVar2 < fVar1) &&
       (fVar1 = fVar1 - FLOAT_8043aa2c, *(float *)(param_9 + 0x44) = fVar1, fVar1 <= fVar2)) {
      *(float *)(param_9 + 0x44) = fVar2;
    }
  }
  else {
    fVar1 = fVar1 + FLOAT_8043aa2c;
    *(float *)(param_9 + 0x44) = fVar1;
    if (fVar2 <= fVar1) {
      *(float *)(param_9 + 0x44) = fVar2;
    }
  }
  if ((double)*(float *)(param_9 + 0x44) != dVar5) {
    zz_0007cac_((double)*(float *)(param_9 + 0x44),*(int *)(param_9 + 0xe4));
  }
  if (FLOAT_8043aa14 != *(float *)(param_9 + 0x44)) {
    dVar5 = (double)FLOAT_8043aa68;
    *(float *)(param_9 + 0xd4) = *(float *)(param_9 + 0xd4) + FLOAT_8043aa64;
    while (dVar5 <= (double)*(float *)(param_9 + 0xd4)) {
      *(float *)(param_9 + 0xd4) = (float)((double)*(float *)(param_9 + 0xd4) - dVar5);
    }
    uVar4 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),dVar5,param_3,param_4,param_5,param_6,
                        param_7,param_8,DAT_803bb384,*(int *)(param_9 + 0xe4),pfVar3,param_12,
                        param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
                ,extraout_r4,pfVar3,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80168524  FUN_80168524 ====

void FUN_80168524(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

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
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float afStack_50 [12];
  undefined4 local_20;
  uint uStack_1c;
  
  dVar6 = (double)*(float *)(param_1 + 0x24);
  dVar7 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar6,dVar7,(float *)(param_1 + 0x114));
  iVar2 = 0;
  iVar4 = 0;
  iVar3 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar2) break;
    pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
    uVar5 = zz_00455fc_((float *)(param_1 + 0x114),afStack_50,pfVar1);
    zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_50,
                (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
    iVar4 = iVar4 + 0x24;
    iVar3 = iVar3 + 4;
    iVar2 = iVar2 + 1;
  }
  local_68 = FLOAT_8043aa6c;
  local_64 = FLOAT_8043aa70;
  local_60 = FLOAT_8043aa10;
  local_5c = FLOAT_8043aa74 * *(float *)(param_1 + 0x20);
  local_58 = FLOAT_8043aa78 * *(float *)(param_1 + 0x24);
  local_54 = FLOAT_8043aa14;
  FUN_8016c5f4((double)FLOAT_8043aa10,(double)FLOAT_8043aa7c,(double)FLOAT_8043aa80,&local_68,
               &local_5c,3,0xff,(short *)(param_2 + 0x20));
  if ((*(byte *)(param_2 + 0x3e) & 1) != 0) {
    if (((int)*(char *)(param_2 + 0x39) <= (int)*(char *)(param_2 + 0x3a)) &&
       ((*(ushort *)(PTR_DAT_80433944 + 8) & 0x20) != 0)) {
      uStack_1c = (int)*(char *)(param_2 + 0x3a) ^ 0x80000000;
      local_20 = 0x43300000;
      local_68 = (float)((double)FLOAT_8043aa80 *
                        (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8043aa90)) *
                 FLOAT_8043aa84 + local_68;
      FUN_8016c5f4((double)FLOAT_8043aa10,(double)FLOAT_8043aa7c,(double)FLOAT_8043aa80,&local_68,
                   &local_5c,3,0xff,(short *)&DAT_8043aa88);
    }
  }
  return;
}



// ==== 80168730  FUN_80168730 ====

void FUN_80168730(int param_1,int param_2)

{
  char cVar1;
  short sVar2;
  short sVar3;
  float fVar4;
  short sVar6;
  int iVar5;
  short sVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  uint uVar11;
  undefined3 *puVar12;
  undefined2 local_c8;
  undefined2 local_c6;
  short local_c4;
  short local_c2;
  short local_c0;
  short local_be;
  undefined2 local_bc;
  undefined2 local_ba;
  undefined2 local_b8;
  undefined2 local_b6;
  undefined4 local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  undefined4 local_a8;
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
  float local_7c;
  float local_78;
  float afStack_74 [13];
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  longlong local_30;
  
  if (FLOAT_8043aa14 != *(float *)(param_1 + 0x44)) {
    cVar1 = *(char *)(param_2 + 0x3b);
    iVar5 = cVar1 * 8;
    DAT_803c1160 = zz_0098214_();
    DAT_803c113c = afStack_74;
    DAT_803c1140 = &local_a4;
    DAT_803c1150 = &local_b4;
    DAT_803c115c = &local_c4;
    DAT_803c1154 = &local_c8;
    DAT_803c116a = 4;
    DAT_803c1174 = *(undefined4 *)(param_1 + 0x44);
    DAT_803c1172 = 0;
    DAT_803c1164 = 3;
    DAT_803c1144 = 0;
    DAT_803c1168 = 0xf;
    DAT_803c1170 = 1;
    DAT_803c1173 = 0xff;
    local_90 = FLOAT_8043aa10;
    local_9c = FLOAT_8043aa10;
    local_c8 = 0x2c;
    local_c6 = 0x28;
    *(float *)(param_1 + 0x28) = FLOAT_8043aa14;
    iVar10 = *(char *)(param_2 + 100) + -7;
    for (uVar11 = 0xffffffd3; (int)uVar11 < 0x280; uVar11 = uVar11 + 0x31) {
      iVar8 = (int)*(short *)(&DAT_8035160e + iVar5);
      iVar10 = (iVar10 + iVar8) - ((iVar10 + iVar8) / iVar8) * iVar8;
      puVar12 = (undefined3 *)&DAT_8034ff3c;
      for (uVar9 = 0; (int)uVar9 < (int)*(short *)(&DAT_8035160c + iVar5); uVar9 = uVar9 + 1) {
        sVar2 = *(short *)((&PTR_DAT_80351610)[cVar1 * 2] +
                          (iVar10 + uVar9 * (int)*(short *)(&DAT_8035160e + iVar5)) * 2);
        if (sVar2 != DAT_8043aa98) {
          uStack_34 = uVar9 ^ 0x80000000;
          uStack_3c = uVar11 ^ 0x80000000;
          local_38 = 0x43300000;
          local_40 = 0x43300000;
          local_a0 = FLOAT_8043aaa0 *
                     (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_8043aa90) +
                     FLOAT_8043aa9c;
          local_a4 = (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_8043aa90);
          iVar8 = (int)(FLOAT_8043aaa4 * *(float *)(param_1 + 0x44));
          local_30 = (longlong)iVar8;
          local_b4 = CONCAT31(*puVar12,(char)iVar8);
          FUN_80051998(-0x7fc3eed0);
          local_a4 = local_a4 + FLOAT_8043aaa8;
          local_a0 = local_a0 - FLOAT_8043aa18;
          local_98 = FLOAT_8043aa7c + local_a4;
          local_94 = FLOAT_8043aaac + local_a0;
          if (sVar2 != DAT_8043aab0) {
            iVar8 = zz_0097fbc_(sVar2);
            sVar6 = (short)iVar8;
            iVar8 = (int)sVar6 / 10 + ((int)sVar6 >> 0x1f);
            sVar3 = (short)iVar8;
            sVar7 = (short)(iVar8 >> 0x1f);
            local_c2 = (sVar3 - sVar7) * 0x18;
            local_c4 = (sVar6 + (sVar3 - sVar7) * -10) * 0x18;
            local_be = local_c2 + 0x18;
            local_c0 = local_c4 + 0x18;
            iVar8 = (int)(FLOAT_8043aaa4 * *(float *)(param_1 + 0x44));
            local_30 = (longlong)iVar8;
            local_b4 = CONCAT31(0xffffff,(char)iVar8);
            FUN_80051ef4(-0x7fc3eed0);
          }
          fVar4 = FLOAT_8043aab8;
          if ((iVar10 == *(char *)(param_2 + 100)) && (uVar9 == (int)*(char *)(param_2 + 0x65) + 1U)
             ) {
            *(float *)(param_1 + 0x20) = ((local_a4 + local_98) - FLOAT_8043aab4) * FLOAT_8043aab8;
            *(float *)(param_1 + 0x24) = (local_a0 + local_94) * fVar4;
            *(short *)(param_1 + 0x1c) = sVar2;
          }
        }
        puVar12 = puVar12 + 1;
      }
      iVar10 = iVar10 + 1;
    }
    local_98 = FLOAT_8043aabc;
    local_a4 = FLOAT_8043aabc;
    local_80 = FLOAT_8043aac0;
    local_8c = FLOAT_8043aac0;
    local_88 = FLOAT_8043aabc;
    local_a0 = FLOAT_8043aabc;
    local_7c = FLOAT_8043aac0;
    local_94 = FLOAT_8043aac0;
    local_78 = FLOAT_8043aa10;
    local_84 = FLOAT_8043aa10;
    local_ba = 0;
    local_c2 = 0;
    local_c0 = 0;
    local_c4 = 0;
    local_b6 = 0x28;
    local_be = 0x28;
    local_b8 = 0x28;
    local_bc = 0x28;
    local_a8 = 0xffffffff;
    local_ac = 0xffffffff;
    local_b0 = 0xffffffff;
    local_b4 = 0xffffffff;
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                       (double)*(float *)(param_1 + 0x28),afStack_74);
    zz_00457d4_('z',afStack_74,afStack_74,*(short *)(param_1 + 0x74));
    DAT_803c1173 = 0xff;
    DAT_803c1160 = (undefined4 *)&DAT_803c0170;
    zz_00524d4_(-0x7fc3eed0);
    if (*(short *)(param_1 + 0x1c) != DAT_8043aab0) {
      iVar5 = zz_0097fbc_(*(short *)(param_1 + 0x1c));
      sVar7 = (short)iVar5;
      local_a4 = *(float *)(param_1 + 0x20) - FLOAT_8043aac4;
      iVar5 = (int)sVar7 / 10 + ((int)sVar7 >> 0x1f);
      local_98 = FLOAT_8043aac8 + *(float *)(param_1 + 0x20);
      sVar2 = (short)iVar5;
      sVar3 = (short)(iVar5 >> 0x1f);
      local_c4 = (sVar7 + (sVar2 - sVar3) * -10) * 0x18;
      local_a0 = *(float *)(param_1 + 0x24) - FLOAT_8043aacc;
      local_c2 = (sVar2 - sVar3) * 0x18;
      local_94 = FLOAT_8043aacc + *(float *)(param_1 + 0x24);
      local_c0 = local_c4 + 0x18;
      local_be = local_c2 + 0x18;
      iVar5 = (int)(FLOAT_8043aaa4 * *(float *)(param_1 + 0x44));
      local_30 = (longlong)iVar5;
      local_b4 = CONCAT31(0xffffff,(char)iVar5);
      DAT_803c1160 = zz_0098214_();
      FUN_80051ef4(-0x7fc3eed0);
    }
  }
  return;
}



// ==== 80168bf4  FUN_80168bf4 ====

void FUN_80168bf4(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float *pfVar5;
  uint uVar6;
  int iVar7;
  uint in_r8;
  int in_r9;
  int in_r10;
  double dVar8;
  double dVar9;
  double dVar10;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  fVar2 = FLOAT_8043aad4;
  uVar6 = 0;
  dVar10 = (double)FLOAT_8043aad4;
  *(float *)(param_1 + 0x38) = FLOAT_8043aad0;
  fVar3 = FLOAT_8043aad8;
  dVar9 = (double)FLOAT_8043aad8;
  *(float *)(param_1 + 0x3c) = fVar2;
  fVar1 = FLOAT_8043aa14;
  dVar8 = (double)FLOAT_8043aa14;
  *(float *)(param_1 + 0x40) = fVar3;
  fVar4 = FLOAT_8043aadc;
  *(float *)(param_1 + 100) = fVar1;
  *(float *)(param_1 + 0x68) = fVar2;
  *(float *)(param_1 + 0x6c) = fVar3;
  *(float *)(param_1 + 0x9c) = fVar1;
  *(float *)(param_1 + 0xa0) = fVar4;
  *(float *)(param_1 + 0xa4) = fVar3;
  pfVar5 = *(float **)(param_1 + 0x38);
  *(float **)(param_1 + 0x20) = pfVar5;
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x40);
  for (iVar7 = 0; iVar7 < *(char *)(param_1 + 0x13); iVar7 = iVar7 + 1) {
    pfVar5 = (float *)(*(int *)(param_1 + 0x54) + uVar6);
    *(undefined2 *)(pfVar5 + 8) = 0xffff;
    *(short *)((int)pfVar5 + 0x22) = (short)iVar7 + *(char *)(param_1 + 0x12) * 8;
    fVar2 = FLOAT_8043aa14;
    fVar1 = FLOAT_8043aa10;
    if (*(short *)((int)pfVar5 + 0x22) < 0x1e) {
      pfVar5[5] = FLOAT_8043aa10;
      pfVar5[4] = fVar1;
      pfVar5[3] = fVar1;
    }
    else if (*(short *)((int)pfVar5 + 0x22) == 0x1e) {
      dVar8 = (double)FLOAT_8043aa14;
      pfVar5[2] = FLOAT_8043aa14;
      pfVar5[1] = fVar2;
      *pfVar5 = fVar2;
      pfVar5[5] = fVar1;
      pfVar5[4] = fVar1;
      pfVar5[3] = fVar1;
    }
    uVar6 = uVar6 + 0x24;
  }
  zz_0168cf0_(dVar8,dVar9,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,param_1,param_2,pfVar5,uVar6,iVar7,
              in_r8,in_r9,in_r10);
  return;
}



// ==== 80168cf0  zz_0168cf0_ ====

void zz_0168cf0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,uint param_12,int param_13,uint param_14,int param_15,
                int param_16)

{
  byte bVar1;
  undefined2 uVar2;
  float fVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  short sVar10;
  int iVar11;
  float *pfVar12;
  int unaff_r21;
  int iVar13;
  uint uVar14;
  int iVar15;
  double dVar16;
  double dVar17;
  undefined8 uVar18;
  char local_68;
  byte bStack_67;
  float local_64;
  undefined4 local_60;
  undefined4 local_5c;
  double local_58;
  undefined4 local_50;
  uint uStack_4c;
  double local_48;
  undefined4 local_40;
  uint uStack_3c;
  
  if (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_9 + 0x96)) == 0) {
    bVar1 = *(byte *)(param_10 + 0x3d) | *(byte *)(param_10 + 0x3f);
  }
  else {
    bVar1 = *(byte *)(param_10 + 0x3d);
  }
  if ((bVar1 & 4) == 0) {
    if (*(float *)(param_9 + 0x20) == *(float *)(param_9 + 0x38)) {
      local_64 = *(float *)(param_9 + 0x38);
      local_60 = *(undefined4 *)(param_9 + 0x3c);
      local_5c = *(undefined4 *)(param_9 + 0x40);
    }
    else {
      local_64 = *(float *)(param_9 + 0x9c);
      local_60 = *(undefined4 *)(param_9 + 0xa0);
      local_5c = *(undefined4 *)(param_9 + 0xa4);
    }
  }
  else {
    local_64 = *(float *)(param_9 + 100);
    local_60 = *(undefined4 *)(param_9 + 0x68);
    local_5c = *(undefined4 *)(param_9 + 0x6c);
  }
  gnt4_PSVECSubtract_bl(&local_64,(float *)(param_9 + 0x20),&local_64);
  gnt4_PSQUATScale_bl((double)FLOAT_8043aa34,&local_64,&local_64);
  gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_64,(float *)(param_9 + 0x20));
  dVar17 = gnt4_PSVECSquareDistance_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x9c));
  if (dVar17 < (double)FLOAT_8043aae0) {
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
    *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x3c);
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x40);
  }
  iVar6 = *(int *)(param_10 + 0x40);
  if ((iVar6 == 0) || (*(char *)(param_10 + 0x61) < '\0')) {
    iVar13 = 0;
    iVar11 = 3;
  }
  else {
    iVar7 = (int)*(char *)(param_10 + *(char *)(param_10 + 0x61) + 0x4c);
    param_14 = 0;
    iVar13 = iVar6 + iVar7 * 0x6c;
    uVar9 = (uint)*(char *)(iVar13 + 0x29);
    param_15 = (int)uVar9 >> 0x1f;
    param_16 = param_15 + (uint)(0xf < uVar9);
    param_13 = uVar9 - 0x18;
    param_12 = (uint)((byte)PTR_DAT_80433944
                            [(int)(char)PTR_DAT_80433944[*(char *)(param_9 + 0x96) + 0x28] + 0x20]
                     >> 7);
    iVar11 = param_16 + param_15 + (uint)(0x17 < uVar9);
    unaff_r21 = zz_01cce38_(iVar6,iVar7,
                            *(int *)(PTR_DAT_80433934 +
                                    ((int)(char)PTR_DAT_80433944[*(char *)(param_9 + 0x96) + 0x28] &
                                    1U) * 0x3c + 0x120),param_12);
  }
  *(undefined2 *)(param_9 + 0x70) = *(undefined2 *)(&DAT_80434778 + iVar11 * 2);
  iVar15 = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  iVar6 = param_9;
  for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
    pfVar12 = (float *)(*(int *)(param_9 + 0x54) + iVar15);
    if ((iVar13 == 0) || (0x1d < *(short *)((int)pfVar12 + 0x22))) {
      if (*(short *)((int)pfVar12 + 0x22) == 0x1e) {
        *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar7);
        iVar4 = DAT_803bb384;
        sVar10 = *(short *)(&DAT_80434770 + iVar11 * 2);
        if ((int)*(short *)(pfVar12 + 8) != (int)sVar10) {
          iVar8 = *(int *)(iVar6 + 0xe0);
          *(short *)(pfVar12 + 8) = sVar10;
          dVar17 = (double)zz_0006fb4_(dVar17,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,iVar4,iVar8,(int)sVar10,param_12,param_13,param_14,
                                       param_15,param_16);
        }
      }
    }
    else {
      iVar4 = (int)*(short *)(iVar13 + *(short *)((int)pfVar12 + 0x22) * 2 + 0x30);
      if (-1 < iVar4) {
        uVar2 = *(undefined2 *)(*(int *)(param_10 + 0x40) + iVar4 * 0x20 + 0x870);
        *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar7);
        if (*(char *)(iVar13 + 0x29) < 9) {
          local_58 = (double)(CONCAT44(0x43300000,(int)*(short *)((int)pfVar12 + 0x22)) ^ 0x80000000
                             );
          iVar4 = *(char *)(iVar13 + 0x29) * 8;
          uVar14 = 0;
          *pfVar12 = *(float *)(&DAT_8034ff4c + iVar4) * (float)(local_58 - DOUBLE_8043aa90) +
                     *(float *)(&DAT_8034ff48 + iVar4);
          fVar3 = FLOAT_8043aaec;
          if (((*(byte *)(iVar13 + 0x29) & 0xc) != 0) &&
             (fVar3 = FLOAT_8043aae8, (*(ushort *)((int)pfVar12 + 0x22) & 1) != 0)) {
            fVar3 = FLOAT_8043aae4;
          }
          pfVar12[2] = fVar3;
          param_2 = DOUBLE_8043aa90;
          param_3 = (double)FLOAT_8043aa2c;
          dVar17 = (double)FLOAT_8043aaf0;
          uStack_4c = 8U - (int)*(char *)(iVar13 + 0x29) ^ 0x80000000;
          param_4 = (double)FLOAT_8043aaf4;
          pfVar12[3] = (float)(param_3 * (double)(float)((double)CONCAT44(0x43300000,uStack_4c) -
                                                        DOUBLE_8043aa90) + dVar17);
          dVar16 = (double)pfVar12[3];
          if ((dVar16 <= param_4) && (param_4 = dVar16, dVar16 < dVar17)) {
            param_4 = dVar17;
          }
          pfVar12[3] = (float)param_4;
          pfVar12[5] = pfVar12[3];
          pfVar12[4] = pfVar12[3];
        }
        else {
          uVar9 = (uint)*(short *)((int)pfVar12 + 0x22);
          param_12 = (int)uVar9 >> 0x1f;
          param_15 = param_12 + (0x16 < uVar9);
          param_13 = param_12 + (7 < uVar9);
          uVar14 = param_13 + param_12 + (0xe < uVar9) + param_15;
          uStack_4c = uVar14 ^ 0x80000000;
          iVar4 = (int)(FLOAT_8043aafc *
                        (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8043aa90) +
                       FLOAT_8043aab8);
          local_58 = (double)(longlong)iVar4;
          local_48 = (double)(CONCAT44(0x43300000,uVar9 - iVar4) ^ 0x80000000);
          fVar3 = FLOAT_8043ab04;
          if ((uVar14 & 1) == 0) {
            fVar3 = FLOAT_8043ab00;
          }
          uStack_3c = uVar14 ^ 0x80000000;
          fVar3 = FLOAT_8043aaf8 * (float)(local_48 - DOUBLE_8043aa90) - fVar3;
          param_4 = (double)fVar3;
          local_40 = 0x43300000;
          param_3 = (double)FLOAT_8043aac0;
          dVar17 = (double)FLOAT_8043ab08;
          param_2 = (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_8043aa90);
          *pfVar12 = fVar3;
          fVar3 = FLOAT_8043aa10;
          dVar17 = -(double)(float)(param_3 * param_2 - dVar17);
          pfVar12[2] = (float)dVar17;
          pfVar12[5] = fVar3;
          pfVar12[4] = fVar3;
          pfVar12[3] = fVar3;
          param_14 = param_12;
        }
        local_50 = 0x43300000;
        local_68 = (char)((ushort)uVar2 >> 8);
        pfVar12[1] = FLOAT_8043aab8;
        bStack_67 = (byte)uVar2;
        iVar4 = *(int *)((&PTR_DAT_80350d0c)[local_68] + (uint)bStack_67 * 4);
        if (*(short *)(pfVar12 + 8) != iVar4) {
          uVar18 = zz_0006fb4_(dVar17,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_803bb384,*(int *)(iVar6 + 0xe0),0x6e,param_12,param_13,param_14,
                               param_15,param_16);
          iVar8 = DAT_803bb334;
          sVar10 = (short)iVar4;
          iVar4 = *(int *)(iVar6 + 0xe0);
          param_12 = 0;
          *(short *)(pfVar12 + 8) = sVar10;
          zz_000761c_(uVar18,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar8,iVar4,
                      (char *)(int)sVar10,0,param_13,param_14,param_15,param_16);
          zz_0007d8c_(*(int *)(iVar6 + 0xe0),7);
        }
        if (*(short *)((int)pfVar12 + 0x22) < unaff_r21) {
          uStack_3c = uVar14 ^ 0x80000000;
          local_40 = 0x43300000;
          param_3 = (double)FLOAT_8043ab0c;
          iVar4 = (int)(param_3 *
                       (double)(float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_8043aa90));
          local_48 = (double)(longlong)iVar4;
          cVar5 = -1 - (char)iVar4;
          param_2 = DOUBLE_8043aa90;
          fVar3 = FLOAT_8043aa10;
        }
        else {
          cVar5 = '\0';
          fVar3 = FLOAT_8043aa84;
        }
        *(char *)(*(int *)(iVar6 + 0xe0) + 0x1e) = cVar5;
        *(char *)(*(int *)(iVar6 + 0xe0) + 0x1d) = cVar5;
        *(char *)(*(int *)(iVar6 + 0xe0) + 0x1c) = cVar5;
        dVar17 = (double)zz_0007cac_((double)fVar3,*(int *)(iVar6 + 0xe0));
      }
    }
    iVar15 = iVar15 + 0x24;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 80169280  FUN_80169280 ====

/* WARNING: Removing unreachable block (ram,0x801693c0) */

void FUN_80169280(int param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  if (*(short *)(param_1 + 0x1c) != 0) {
    dVar11 = (double)*(float *)(param_1 + 0x24);
    dVar12 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar11,dVar12,(float *)(param_1 + 0x114));
    iVar5 = (int)*(short *)(param_1 + 0x70);
    zz_00457d4_('x',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x70)
               );
    iVar9 = 0;
    iVar8 = param_1;
    for (iVar7 = 0; iVar7 < *(char *)(param_1 + 0x13); iVar7 = iVar7 + 1) {
      if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar7) != 0) {
        pfVar6 = (float *)(*(int *)(param_1 + 0x54) + iVar9);
        zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar6);
        pfVar4 = pfVar6 + 3;
        uVar10 = zz_00456a0_(afStack_48,afStack_48,pfVar4);
        zz_00076d0_(uVar10,dVar11,dVar12,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar8 + 0xe0),
                    afStack_48,(undefined *)pfVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
        if (*(short *)((int)pfVar6 + 0x22) < 0x1e) {
          iVar2 = *(int *)(*(int *)(iVar8 + 0xe0) + 0xc);
          if (iVar2 == 0) {
            iVar2 = 0;
          }
          else {
            iVar2 = *(int *)(iVar2 + 0x10);
          }
          if (iVar2 != 0) {
            dVar11 = (double)FLOAT_8043aab8;
            dVar12 = (double)FLOAT_8043ab10;
            FUN_800455b0((double)FLOAT_8043aa14,dVar11,dVar12,afStack_48,afStack_48);
            pfVar4 = afStack_48;
            iVar5 = (int)-*(short *)(param_1 + 0x70);
            uVar10 = zz_00457d4_('x',pfVar4,pfVar4,-*(short *)(param_1 + 0x70));
            if (iVar2 == 0) {
              pfVar4 = (float *)&DAT_8043ab1c;
              gnt4___assert_bl(uVar10,dVar11,dVar12,in_f4,in_f5,in_f6,in_f7,in_f8,&DAT_8043ab14,
                               0x495,&DAT_8043ab1c,iVar5,in_r7,in_r8,in_r9,in_r10);
            }
            uVar10 = gnt4_PSMTXCopy_bl(afStack_48,(float *)(iVar2 + 0x44));
            *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
            if (iVar2 != 0) {
              uVar3 = *(uint *)(iVar2 + 0x14);
              bVar1 = false;
              if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
                bVar1 = true;
              }
              if (!bVar1) {
                gnt4_HSD_JObjSetMtxDirtySub_bl
                          (uVar10,dVar11,dVar12,in_f4,in_f5,in_f6,in_f7,in_f8,iVar2,uVar3,
                           (undefined *)pfVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
              }
            }
          }
          zz_00097b4_(*(int *)(iVar8 + 0xe0),0x45);
        }
        else if (*(short *)(pfVar6 + 8) == 0x91) {
          zz_00097b4_(*(int *)(iVar8 + 0xe0),0x44);
        }
        else {
          zz_00097b4_(*(int *)(iVar8 + 0xe0),1);
        }
      }
      iVar9 = iVar9 + 0x24;
      iVar8 = iVar8 + 4;
    }
  }
  return;
}



// ==== 80169464  FUN_80169464 ====

void FUN_80169464(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,int param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 *puVar9;
  double dVar10;
  double dVar11;
  
  fVar2 = FLOAT_8043ab2c;
  fVar1 = FLOAT_8043ab28;
  puVar5 = &DAT_80350000;
  dVar11 = (double)FLOAT_8043ab28;
  dVar10 = (double)FLOAT_8043ab2c;
  puVar9 = &DAT_8034ff90;
  iVar8 = 0;
  *(float *)(param_9 + 0x44) = FLOAT_8043aa14;
  *(float *)(param_9 + 0x38) = FLOAT_8043ab24;
  fVar3 = FLOAT_8043ab30;
  *(float *)(param_9 + 0x3c) = fVar1;
  *(float *)(param_9 + 0x40) = fVar2;
  *(float *)(param_9 + 100) = fVar3;
  *(float *)(param_9 + 0x68) = fVar1;
  *(float *)(param_9 + 0x6c) = fVar2;
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
  *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x3c);
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x40);
  iVar7 = param_9;
  for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    uVar4 = puVar9[2];
    puVar5 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar8);
    *puVar5 = puVar9[1];
    puVar5[1] = uVar4;
    puVar5[2] = puVar9[3];
    puVar5 = (undefined4 *)*puVar9;
    dVar10 = (double)zz_0006fb4_(dVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_803bb384,*(int *)(iVar7 + 0xe0),(int)puVar5,param_12,param_13,
                                 param_14,param_15,param_16);
    puVar9 = puVar9 + 4;
    iVar8 = iVar8 + 0x24;
    iVar7 = iVar7 + 4;
  }
  zz_0169554_(dVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,puVar5,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80169554  zz_0169554_ ====

/* WARNING: Removing unreachable block (ram,0x801697a8) */
/* WARNING: Removing unreachable block (ram,0x80169564) */

void zz_0169554_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  float fVar2;
  float *pfVar3;
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
  double dVar13;
  char local_48 [4];
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  uint uStack_34;
  
  fVar2 = FLOAT_8043aa14;
  if (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_9 + 0x96)) == 0) {
    bVar1 = *(byte *)(param_10 + 0x3d) | *(byte *)(param_10 + 0x3f);
  }
  else {
    bVar1 = *(byte *)(param_10 + 0x3d);
  }
  dVar13 = (double)*(float *)(param_9 + 0x44);
  if ((bVar1 & 4) == 0) {
    dVar11 = (double)FLOAT_8043aa14;
    if (dVar13 <= dVar11) {
      local_44 = *(float *)(param_9 + 0x38);
      local_40 = *(undefined4 *)(param_9 + 0x3c);
      local_3c = *(undefined4 *)(param_9 + 0x40);
      *(float *)(param_9 + 0x20) = local_44;
      *(undefined4 *)(param_9 + 0x24) = local_40;
      *(undefined4 *)(param_9 + 0x28) = local_3c;
    }
    else {
      dVar10 = (double)FLOAT_8043aa2c;
      *(float *)(param_9 + 0x44) = (float)(dVar13 - dVar10);
      if ((double)(float)(dVar13 - dVar10) < dVar11) {
        *(float *)(param_9 + 0x44) = fVar2;
      }
      local_44 = *(float *)(param_9 + 100);
      local_40 = *(undefined4 *)(param_9 + 0x68);
      local_3c = *(undefined4 *)(param_9 + 0x6c);
    }
  }
  else {
    *(float *)(param_9 + 0x44) = FLOAT_8043aa10;
    local_44 = *(float *)(param_9 + 100);
    local_40 = *(undefined4 *)(param_9 + 0x68);
    local_3c = *(undefined4 *)(param_9 + 0x6c);
  }
  gnt4_PSVECSubtract_bl(&local_44,(float *)(param_9 + 0x20),&local_44);
  gnt4_PSQUATScale_bl((double)FLOAT_8043aa34,&local_44,&local_44);
  gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_44,(float *)(param_9 + 0x20));
  if ((double)*(float *)(param_9 + 0x44) != dVar13) {
    iVar8 = param_9;
    for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
      fVar2 = FLOAT_8043aa10;
      if (iVar7 == 0) {
        fVar2 = FLOAT_8043ab34;
      }
      zz_0007cac_((double)(*(float *)(param_9 + 0x44) * fVar2),*(int *)(iVar8 + 0xe0));
      iVar8 = iVar8 + 4;
    }
  }
  if ((FLOAT_8043aa14 < *(float *)(param_9 + 0x44)) && (-1 < *(char *)(param_10 + 0x61))) {
    pfVar3 = (float *)(*(char *)(param_10 + *(char *)(param_10 + 0x61) + 0x4c) + 1);
    pfVar6 = (float *)0x14;
    if ((int)pfVar3 < 0x14) {
      pfVar6 = pfVar3;
    }
    sprintf(local_48,&DAT_8043ab38);
    sVar4 = strlen(local_48);
    *(short *)(param_9 + 0x1c) = (short)sVar4;
    pcVar9 = local_48;
    iVar8 = param_9;
    for (iVar7 = 0; iVar7 < *(short *)(param_9 + 0x1c); iVar7 = iVar7 + 1) {
      iVar5 = (int)*pcVar9;
      fVar2 = FLOAT_8043aa14;
      if ((0x2f < iVar5) && (iVar5 < 0x3a)) {
        uStack_34 = iVar5 - 0x30U ^ 0x80000000;
        local_38 = 0x43300000;
        fVar2 = (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_8043aa90);
      }
      uVar12 = zz_00086b8_((double)fVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_803bb384,*(int *)(iVar8 + 0xe8),pfVar6,param_12,param_13,param_14,
                           param_15,param_16);
      zz_0007c30_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar8 + 0xe8),extraout_r4,pfVar6,param_12,param_13,param_14,param_15,
                  param_16);
      pcVar9 = pcVar9 + 1;
      iVar8 = iVar8 + 4;
    }
  }
  return;
}



// ==== 801697c4  FUN_801697c4 ====

void FUN_801697c4(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
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
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float afStack_50 [14];
  
  if (FLOAT_8043aa14 < *(float *)(param_1 + 0x44)) {
    dVar7 = (double)*(float *)(param_1 + 0x24);
    dVar8 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar7,dVar8,(float *)(param_1 + 0x114));
    if (*(char *)(param_2 + 0x61) < '\0') {
      iVar2 = 1;
    }
    else {
      iVar2 = (int)*(char *)(param_1 + 0x13) + (int)*(short *)(param_1 + 0x1c) + -2;
    }
    iVar5 = 0;
    iVar4 = param_1;
    for (iVar3 = 0; iVar3 < iVar2; iVar3 = iVar3 + 1) {
      pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
      uVar6 = zz_00455fc_((float *)(param_1 + 0x114),afStack_50,pfVar1);
      zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),afStack_50,
                  (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar4 + 0xe0),0x44);
      iVar5 = iVar5 + 0x24;
      iVar4 = iVar4 + 4;
    }
    if ((*(int *)(param_2 + 0x40) == 0) || (*(char *)(param_2 + 0x61) < '\0')) {
      sprintf(&DAT_803d5eb8,&DAT_802b1e70);
    }
    else {
      strcpy(&DAT_803d5eb8,
             (char *)(*(int *)(param_2 + 0x40) +
                     *(char *)(param_2 + *(char *)(param_2 + 0x61) + 0x4c) * 0x6c));
    }
    local_5c = FLOAT_8043ab3c;
    local_58 = FLOAT_8043ab40;
    local_54 = FLOAT_8043aab8;
    local_60 = FLOAT_8043aa10;
    local_64 = FLOAT_8043aa10;
    local_68 = FLOAT_8043aa10;
    FUN_801c53dc((double)*(float *)(param_1 + 0x44),(double)FLOAT_8043ab44,(double)FLOAT_8043ab0c,
                 (float *)(param_1 + 0x114),&local_5c,&local_68,3,0x1e,(short *)&DAT_803d5eb8);
  }
  return;
}



// ==== 80169938  FUN_80169938 ====

void FUN_80169938(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 *puVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  fVar3 = FLOAT_8043ab50;
  fVar2 = FLOAT_8043ab4c;
  fVar1 = FLOAT_8043ab48;
  iVar8 = -0x7fc40000;
  dVar14 = (double)FLOAT_8043ab48;
  dVar13 = (double)FLOAT_8043ab4c;
  dVar12 = (double)FLOAT_8043ab50;
  iVar11 = 0;
  *(float *)(param_1 + 0x44) = FLOAT_8043aa14;
  fVar4 = FLOAT_8043ab54;
  *(float *)(param_1 + 0x38) = fVar1;
  *(float *)(param_1 + 0x3c) = fVar2;
  *(float *)(param_1 + 0x40) = fVar3;
  *(float *)(param_1 + 100) = fVar1;
  *(float *)(param_1 + 0x68) = fVar2;
  *(float *)(param_1 + 0x6c) = fVar4;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x40);
  *(undefined2 *)(param_1 + 0x74) = 0x9f4;
  iVar10 = param_1;
  for (uVar9 = 0; (int)uVar9 < (int)*(char *)(param_1 + 0x13); uVar9 = uVar9 + 1) {
    uVar6 = (-uVar9 | uVar9) >> 0x1b & 0x10;
    puVar7 = (undefined4 *)(*(int *)(param_1 + 0x54) + iVar11);
    uVar5 = *(undefined4 *)((int)&DAT_8034ffd8 + uVar6);
    *puVar7 = *(undefined4 *)((int)&DAT_8034ffd4 + uVar6);
    puVar7[1] = uVar5;
    puVar7[2] = *(undefined4 *)((int)&DAT_8034ffdc + uVar6);
    iVar8 = *(int *)((int)&DAT_8034ffd0 + uVar6);
    dVar12 = (double)zz_0006fb4_(dVar12,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb384,
                                 *(int *)(iVar10 + 0xe0),iVar8,param_4,param_5,param_6,param_7,
                                 param_8);
    iVar11 = iVar11 + 0x24;
    iVar10 = iVar10 + 4;
  }
  zz_0169a3c_(dVar12,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,param_1,param_2,iVar8,param_4,
              param_5,param_6,param_7,param_8);
  return;
}



// ==== 80169a3c  zz_0169a3c_ ====

/* WARNING: Removing unreachable block (ram,0x80169d18) */
/* WARNING: Removing unreachable block (ram,0x80169d10) */
/* WARNING: Removing unreachable block (ram,0x80169d08) */
/* WARNING: Removing unreachable block (ram,0x80169a5c) */
/* WARNING: Removing unreachable block (ram,0x80169a54) */
/* WARNING: Removing unreachable block (ram,0x80169a4c) */

void zz_0169a3c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  float fVar2;
  int iVar3;
  size_t sVar4;
  int iVar5;
  undefined4 extraout_r4;
  float *pfVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  double dVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  char local_78 [8];
  float local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_60;
  uint uStack_5c;
  
  fVar2 = FLOAT_8043aa14;
  if (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_9 + 0x96)) == 0) {
    bVar1 = *(byte *)(param_10 + 0x3d) | *(byte *)(param_10 + 0x3f);
  }
  else {
    bVar1 = *(byte *)(param_10 + 0x3d);
  }
  dVar13 = (double)*(float *)(param_9 + 0x44);
  if ((bVar1 & 4) == 0) {
    dVar14 = (double)FLOAT_8043aa14;
    if (dVar13 <= dVar14) {
      local_70 = *(float *)(param_9 + 0x38);
      local_6c = *(undefined4 *)(param_9 + 0x3c);
      local_68 = *(undefined4 *)(param_9 + 0x40);
      *(float *)(param_9 + 0x20) = local_70;
      *(undefined4 *)(param_9 + 0x24) = local_6c;
      *(undefined4 *)(param_9 + 0x28) = local_68;
    }
    else {
      dVar15 = (double)FLOAT_8043aa2c;
      *(float *)(param_9 + 0x44) = (float)(dVar13 - dVar15);
      if ((double)(float)(dVar13 - dVar15) < dVar14) {
        *(float *)(param_9 + 0x44) = fVar2;
      }
      local_70 = *(float *)(param_9 + 100);
      local_6c = *(undefined4 *)(param_9 + 0x68);
      local_68 = *(undefined4 *)(param_9 + 0x6c);
    }
  }
  else {
    *(float *)(param_9 + 0x44) = FLOAT_8043aa10;
    local_70 = *(float *)(param_9 + 100);
    local_6c = *(undefined4 *)(param_9 + 0x68);
    local_68 = *(undefined4 *)(param_9 + 0x6c);
  }
  gnt4_PSVECSubtract_bl(&local_70,(float *)(param_9 + 0x20),&local_70);
  gnt4_PSQUATScale_bl((double)FLOAT_8043aa34,&local_70,&local_70);
  gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_70,(float *)(param_9 + 0x20));
  if ((double)*(float *)(param_9 + 0x44) != dVar13) {
    iVar3 = param_9;
    for (iVar8 = 0; iVar8 < *(char *)(param_9 + 0x13); iVar8 = iVar8 + 1) {
      zz_0007cac_((double)*(float *)(param_9 + 0x44),*(int *)(iVar3 + 0xe0));
      iVar3 = iVar3 + 4;
    }
  }
  if (FLOAT_8043aa14 < *(float *)(param_9 + 0x44)) {
    if (*(char *)(param_10 + 0x61) < '\0') {
      sprintf(local_78,&DAT_8043ab58);
    }
    else {
      iVar3 = 999999;
      iVar8 = *(int *)(*(int *)(param_10 + 0x40) +
                       *(char *)(param_10 + *(char *)(param_10 + 0x61) + 0x4c) * 0x6c + 0x2c);
      if (iVar8 < 999999) {
        iVar3 = iVar8;
      }
      sprintf(local_78,&DAT_8043ab38,iVar3);
    }
    sVar4 = strlen(local_78);
    *(short *)(param_9 + 0x1c) = (short)sVar4;
    dVar14 = (double)FLOAT_8043ab60;
    pcVar10 = local_78;
    dVar15 = (double)FLOAT_8043aab8;
    iVar9 = 1;
    iVar3 = param_9;
    dVar13 = DOUBLE_8043aa90;
    for (iVar8 = 0; iVar7 = (int)*(short *)(param_9 + 0x1c), iVar8 < iVar7; iVar8 = iVar8 + 1) {
      pfVar6 = *(float **)(param_9 + 0x54);
      iVar5 = (int)*pcVar10;
      if ((iVar5 < 0x30) || (0x39 < iVar5)) {
        if (iVar5 == 0x3f) {
          dVar11 = (double)FLOAT_8043aaa8;
        }
        else {
          dVar11 = (double)FLOAT_8043aa14;
        }
      }
      else {
        dVar11 = (double)(float)((double)CONCAT44(0x43300000,iVar5 - 0x30U ^ 0x80000000) -
                                DOUBLE_8043aa90);
      }
      local_60 = 0x43300000;
      uStack_5c = iVar9 - iVar7 ^ 0x80000000;
      pfVar6[(iVar8 + 1) * 9] =
           (float)((double)(float)(dVar14 * (double)(float)((double)CONCAT44(0x43300000,uStack_5c) -
                                                           dVar13)) * dVar15);
      uVar12 = zz_00086b8_(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_803bb384,*(int *)(iVar3 + 0xe4),pfVar6,iVar7,param_13,param_14,
                           param_15,param_16);
      zz_0007c30_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar3 + 0xe4),extraout_r4,pfVar6,iVar7,param_13,param_14,param_15,
                  param_16);
      pcVar10 = pcVar10 + 1;
      iVar9 = iVar9 + 2;
      iVar3 = iVar3 + 4;
    }
  }
  return;
}



// ==== 80169d34  FUN_80169d34 ====

void FUN_80169d34(int param_1)

{
  float *pfVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
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
  float afStack_48 [14];
  
  if (FLOAT_8043aa14 < *(float *)(param_1 + 0x44)) {
    dVar7 = (double)*(float *)(param_1 + 0x24);
    dVar8 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar7,dVar8,(float *)(param_1 + 0x114));
    iVar2 = (int)*(short *)(param_1 + 0x74);
    zz_00457d4_('z',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x74)
               );
    iVar3 = (int)*(char *)(param_1 + 0x13) + (int)*(short *)(param_1 + 0x1c) + -7;
    iVar5 = iVar3 * 0x24;
    iVar4 = param_1 + iVar3 * 4;
    for (; -1 < iVar3; iVar3 = iVar3 + -1) {
      pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
      uVar6 = zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar1);
      zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),afStack_48,
                  (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
      zz_00097b4_(*(int *)(iVar4 + 0xe0),0x44);
      iVar5 = iVar5 + -0x24;
      iVar4 = iVar4 + -4;
    }
  }
  return;
}



// ==== 80169e10  FUN_80169e10 ====

void FUN_80169e10(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  
  iVar5 = 0;
  *(undefined1 *)(param_9 + 0x1b) = 0x26;
  *(undefined2 *)(param_9 + 0x1c) = 0x1f;
  piVar6 = &DAT_8034fff0;
  *(undefined2 *)(param_9 + 0x1e) = 0;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    iVar1 = piVar6[2];
    piVar2 = (int *)(*(int *)(param_9 + 0x54) + iVar5);
    *piVar2 = piVar6[1];
    piVar2[1] = iVar1;
    piVar2[2] = piVar6[3];
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb384,*(int *)(iVar4 + 0xe0),*piVar6,param_12,param_13,param_14,
                          param_15,param_16);
    piVar6 = piVar6 + 4;
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
  }
  zz_0169ecc_(param_9,param_10);
  return;
}



// ==== 80169ecc  zz_0169ecc_ ====

void zz_0169ecc_(int param_1,int param_2)

{
  byte bVar1;
  
  bVar1 = *(byte *)(param_1 + 0x1b);
  if ((bVar1 & (*(byte *)(param_2 + 0x3e) | *(byte *)(param_2 + 0x3d) & *(byte *)(param_2 + 0x3f)))
      != 0) {
    if ((*(byte *)(param_2 + 0x3e) & bVar1) == 0) {
      if ((*(byte *)(param_2 + 0x3f) & bVar1) != 0) {
        *(undefined2 *)(param_1 + 0x1e) = 2;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x1e) = 0x20;
    }
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
    return;
  }
  *(undefined2 *)(param_1 + 0x1c) = 0x1f;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  return;
}



// ==== 80169f38  FUN_80169f38 ====

void FUN_80169f38(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
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
  
  if ((*(ushort *)(param_1 + 0x1c) & *(ushort *)(param_1 + 0x1e)) != 0) {
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



// ==== 80169fe8  FUN_80169fe8 ====

void FUN_80169fe8(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar10;
  int iVar11;
  int *piVar12;
  int iVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  fVar3 = FLOAT_8043ab68;
  dVar16 = DOUBLE_8043aa90;
  dVar17 = (double)FLOAT_8043ab64;
  *(float *)(param_1 + 100) = FLOAT_8043aa14;
  fVar2 = FLOAT_8043aa24;
  fVar1 = (float)(dVar17 * (double)(float)((double)CONCAT44(0x43300000,
                                                            2U - (int)*(char *)(param_1 + 0x12) ^
                                                            0x80000000) - dVar16));
  dVar15 = (double)fVar1;
  *(float *)(param_1 + 0x68) = fVar1;
  *(float *)(param_1 + 0x6c) = fVar3;
  uVar9 = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x20) = uVar9;
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x6c);
  *(undefined1 *)(param_1 + 0x1a) = 0xff;
  uVar8 = (uint)*(byte *)(param_2 + 0x65);
  iVar7 = uVar8 + (*(byte *)(param_1 + 0x12) - 2);
  *(char *)(param_1 + 0x1b) = (char)iVar7;
  *(float *)(param_1 + 0xd4) = fVar2;
  *(undefined2 *)(param_1 + 0x74) = 0;
  zz_01673e4_(param_1,0,param_1 + 0x1c);
  iVar6 = param_1 + 0x1e;
  dVar14 = (double)zz_01673e4_(param_1,1,iVar6);
  piVar12 = &DAT_80350000;
  iVar13 = 0;
  iVar11 = param_1;
  for (iVar10 = 0; iVar10 < *(char *)(param_1 + 0x13); iVar10 = iVar10 + 1) {
    iVar4 = piVar12[2];
    piVar5 = (int *)(*(int *)(param_1 + 0x54) + iVar13);
    *piVar5 = piVar12[1];
    piVar5[1] = iVar4;
    piVar5[2] = piVar12[3];
    *(undefined2 *)(piVar5 + 8) = *(undefined2 *)(param_1 + 0x74);
    fVar2 = FLOAT_8043ab6c;
    fVar1 = FLOAT_8043aa10;
    if (iVar10 < 3) {
      piVar5[5] = (int)FLOAT_8043aa10;
      piVar5[4] = (int)fVar1;
      piVar5[3] = (int)fVar1;
      iVar6 = *piVar12;
      dVar14 = (double)zz_0006fb4_(dVar14,dVar15,dVar16,dVar17,in_f5,in_f6,in_f7,in_f8,DAT_803bb384,
                                   *(int *)(iVar11 + 0xe0),iVar6,iVar7,uVar8,uVar9,in_r9,in_r10);
    }
    else {
      dVar14 = (double)FLOAT_8043ab6c;
      piVar5[3] = (int)FLOAT_8043ab6c;
      piVar5[4] = (int)fVar2;
      piVar5[5] = (int)fVar1;
    }
    iVar13 = iVar13 + 0x24;
    piVar12 = piVar12 + 4;
    iVar11 = iVar11 + 4;
  }
  zz_016a16c_(dVar14,dVar15,dVar16,dVar17,in_f5,in_f6,in_f7,in_f8,param_1,param_2,iVar6,iVar7,uVar8,
              uVar9,in_r9,in_r10);
  return;
}



// ==== 8016a16c  zz_016a16c_ ====

void zz_016a16c_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  bool bVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  undefined8 uVar11;
  double dVar12;
  undefined2 local_38 [4];
  undefined4 local_30;
  uint uStack_2c;
  
  fVar1 = *(float *)(param_9 + 0x68);
  iVar5 = (int)*(char *)(param_10 + 0x65) + *(char *)(param_9 + 0x12) + -2;
  iVar3 = (int)*(char *)(param_9 + 0x1b);
  pfVar4 = (float *)(*(int *)(param_10 + 0x40) +
                    *(char *)(param_10 + *(char *)(param_10 + 0x61) + 0x4c) * 0x6c);
  if (iVar3 != iVar5) {
    param_3 = (double)(*(float *)(param_9 + 0x24) - fVar1);
    dVar12 = param_3;
    if (param_3 < (double)FLOAT_8043aa14) {
      dVar12 = -param_3;
    }
    if ((double)FLOAT_8043ab70 <= dVar12) {
      if (param_3 <= (double)FLOAT_8043aa14) {
        if (param_3 < (double)FLOAT_8043aa14) {
          *(float *)(param_9 + 0x24) = *(float *)(param_9 + 0x24) + FLOAT_8043ab64;
        }
      }
      else {
        *(float *)(param_9 + 0x24) = *(float *)(param_9 + 0x24) - FLOAT_8043ab64;
      }
      *(char *)(param_9 + 0x1b) = (char)iVar5;
    }
    else if (iVar5 < iVar3) {
      fVar1 = fVar1 - FLOAT_8043ab64;
    }
    else if (iVar3 < iVar5) {
      fVar1 = fVar1 + FLOAT_8043ab64;
    }
  }
  dVar12 = (double)(fVar1 - *(float *)(param_9 + 0x24));
  fVar1 = FLOAT_8043aa20;
  if ((*(byte *)(param_10 + 0x3e) & 8) != 0) {
    fVar1 = FLOAT_8043ab74;
  }
  dVar10 = (double)(FLOAT_8043ab64 / fVar1);
  dVar9 = dVar12;
  if (dVar12 < (double)FLOAT_8043aa14) {
    dVar9 = -dVar12;
  }
  if (dVar10 < dVar9) {
    dVar10 = (double)(float)(dVar10 * dVar12);
    if (dVar12 < (double)FLOAT_8043aa14) {
      dVar12 = -dVar12;
    }
    dVar12 = (double)(float)(dVar10 / dVar12);
  }
  bVar2 = false;
  *(float *)(param_9 + 0x24) = (float)((double)*(float *)(param_9 + 0x24) + dVar12);
  *(short *)(param_9 + 0x74) = *(short *)(param_9 + 0x74) + -0x200;
  if ((-1 < *(char *)(param_9 + 0x1b)) &&
     (*(char *)(param_9 + 0x1b) < *(char *)((int)pfVar4 + 0x29))) {
    bVar2 = true;
  }
  *(bool *)(param_9 + 0x87) = bVar2;
  if (bVar2) {
    iVar3 = (int)*(short *)((int)pfVar4 + *(char *)(param_9 + 0x1b) * 2 + 0x30);
    if (iVar3 < 0) {
      pcVar6 = (char *)0x0;
    }
    else {
      pcVar6 = (char *)(*(int *)(param_10 + 0x40) + iVar3 * 0x20 + 0x870);
      *(short *)(param_9 + 0x1c) = pcVar6[3] + 1;
      local_38[0] = *(undefined2 *)pcVar6;
      iVar3 = zz_0066168_((char *)local_38,(int)pcVar6[2]);
      *(short *)(param_9 + 0x1e) = (short)iVar3;
    }
    *(char **)(param_9 + 0xcc) = pcVar6;
    iVar8 = 0;
    iVar3 = param_9;
    for (iVar7 = 0; dVar9 = DOUBLE_8043aa90, iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
      if (iVar7 != 0) {
        if (iVar7 == 1) {
          local_30 = 0x43300000;
          *(undefined2 *)(*(int *)(param_9 + 0x54) + iVar8 + 0x20) = *(undefined2 *)(param_9 + 0x74)
          ;
          uStack_2c = (int)(char)PTR_DAT_80433944[*(char *)(param_10 + 0x66) + 0x88] ^ 0x80000000;
          pfVar4 = (float *)PTR_DAT_80433944;
          uVar11 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_2c) - dVar9),
                               dVar12,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                               *(int *)(iVar3 + 0xe0),PTR_DAT_80433944,iVar5,param_13,param_14,
                               param_15,param_16);
          dVar10 = (double)zz_0007c30_(uVar11,dVar12,param_3,param_4,param_5,param_6,param_7,param_8
                                       ,*(int *)(iVar3 + 0xe0),extraout_r4,pfVar4,iVar5,param_13,
                                       param_14,param_15,param_16);
        }
        else if (pcVar6 != (char *)0x0) {
          if (iVar7 == 2) {
            local_30 = 0x43300000;
            uStack_2c = (int)pcVar6[2] ^ 0x80000000;
            uVar11 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_2c) -
                                                DOUBLE_8043aa90),dVar12,param_3,param_4,param_5,
                                 param_6,param_7,param_8,DAT_803bb384,*(int *)(iVar3 + 0xe0),pfVar4,
                                 iVar5,param_13,param_14,param_15,param_16);
            dVar10 = (double)zz_0007c30_(uVar11,dVar12,param_3,param_4,param_5,param_6,param_7,
                                         param_8,*(int *)(iVar3 + 0xe0),extraout_r4_00,pfVar4,iVar5,
                                         param_13,param_14,param_15,param_16);
          }
          else if (*(char *)(param_9 + 0x1a) != *(char *)(param_9 + 0x1b)) {
            *(char *)(param_9 + 0x1a) = *(char *)(param_9 + 0x1b);
            pfVar4 = *(float **)((&PTR_DAT_80350d0c)[*pcVar6] + (uint)(byte)pcVar6[1] * 4);
            dVar10 = (double)zz_0006fb4_(dVar10,dVar12,param_3,param_4,param_5,param_6,param_7,
                                         param_8,DAT_803bb334,*(int *)(iVar3 + 0xe0),(int)pfVar4,
                                         iVar5,param_13,param_14,param_15,param_16);
          }
        }
      }
      iVar8 = iVar8 + 0x24;
      iVar3 = iVar3 + 4;
    }
  }
  if (((*(byte *)(param_10 + 0x3d) & 8) == 0) &&
     ((int)*(short *)(param_10 + 6) <= (int)*(char *)(param_9 + 0x1b))) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 8016a4e4  FUN_8016a4e4 ====

void FUN_8016a4e4(int param_1)

{
  int iVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  char *pcVar2;
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
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float afStack_50 [15];
  
  if (*(char *)(param_1 + 0x87) != '\0') {
    dVar8 = (double)*(float *)(param_1 + 0x24);
    dVar9 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar8,dVar9,(float *)(param_1 + 0x114));
    iVar6 = 0;
    iVar5 = param_1;
    for (iVar4 = 0; iVar4 < *(char *)(param_1 + 0x13); iVar4 = iVar4 + 1) {
      if ((iVar4 < 2) || (*(int *)(param_1 + 0xcc) != 0)) {
        pfVar3 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
        zz_00455fc_((float *)(param_1 + 0x114),afStack_50,pfVar3);
        iVar1 = (int)*(short *)(pfVar3 + 8);
        zz_00457d4_('z',afStack_50,afStack_50,*(short *)(pfVar3 + 8));
        pfVar3 = pfVar3 + 3;
        uVar7 = zz_00456a0_(afStack_50,afStack_50,pfVar3);
        zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),
                    afStack_50,(undefined *)pfVar3,iVar1,in_r7,in_r8,in_r9,in_r10);
        zz_00097b4_(*(int *)(iVar5 + 0xe0),0x44);
      }
      iVar6 = iVar6 + 0x24;
      iVar5 = iVar5 + 4;
    }
    pcVar2 = *(char **)(param_1 + 0xcc);
    if (pcVar2 != (char *)0x0) {
      local_5c = FLOAT_8043ab78;
      local_58 = FLOAT_8043ab7c;
      local_54 = FLOAT_8043ab80;
      local_60 = FLOAT_8043aa10;
      local_64 = FLOAT_8043aa10;
      local_68 = FLOAT_8043aa10;
      FUN_801c53dc((double)FLOAT_8043aa10,(double)FLOAT_8043ab84,(double)FLOAT_8043ab88,
                   (float *)(param_1 + 0x114),&local_5c,&local_68,3,0xff,
                   *(short **)((&PTR_PTR_803510d8)[*pcVar2] + (uint)(byte)pcVar2[1] * 4));
    }
  }
  return;
}



// ==== 8016a638  FUN_8016a638 ====

/* WARNING: Removing unreachable block (ram,0x8016a770) */
/* WARNING: Removing unreachable block (ram,0x8016a768) */
/* WARNING: Removing unreachable block (ram,0x8016a760) */
/* WARNING: Removing unreachable block (ram,0x8016a758) */
/* WARNING: Removing unreachable block (ram,0x8016a750) */
/* WARNING: Removing unreachable block (ram,0x8016a668) */
/* WARNING: Removing unreachable block (ram,0x8016a660) */
/* WARNING: Removing unreachable block (ram,0x8016a658) */
/* WARNING: Removing unreachable block (ram,0x8016a650) */
/* WARNING: Removing unreachable block (ram,0x8016a648) */

void FUN_8016a638(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  float *pfVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  uint uVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  
  *(undefined2 *)(param_9 + 0x1c) = 0xffff;
  dVar9 = DOUBLE_8043aa90;
  puVar4 = &DAT_80350000;
  dVar8 = (double)FLOAT_8043ab8c;
  uVar5 = (uint)*(byte *)(param_9 + 0x12);
  dVar10 = (double)FLOAT_8043aa14;
  iVar3 = (char)*(byte *)(param_9 + 0x12) * 0xc;
  dVar11 = (double)FLOAT_8043ab90;
  dVar12 = (double)FLOAT_8043aa10;
  uVar1 = *(undefined4 *)(&DAT_80350044 + iVar3);
  iVar7 = 0;
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(&DAT_80350040 + iVar3);
  *(undefined4 *)(param_9 + 0x24) = uVar1;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(&DAT_80350048 + iVar3);
  iVar3 = param_9;
  for (uVar6 = 0; (int)uVar6 < (int)*(char *)(param_9 + 0x13); uVar6 = uVar6 + 1) {
    puVar4 = (undefined4 *)0x8;
    pfVar2 = (float *)(*(int *)(param_9 + 0x54) + iVar7);
    *pfVar2 = (float)(dVar8 * (double)(float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) -
                                             dVar9));
    pfVar2[1] = (float)dVar10;
    pfVar2[2] = (float)dVar10;
    pfVar2[3] = (float)dVar11;
    pfVar2[4] = (float)dVar11;
    pfVar2[5] = (float)dVar12;
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb384,*(int *)(iVar3 + 0xe0),8,uVar5,param_13,param_14,param_15,
                          param_16);
    iVar7 = iVar7 + 0x24;
    iVar3 = iVar3 + 4;
  }
  zz_016a78c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              puVar4,uVar5,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8016a78c  zz_016a78c_ ====

void zz_016a78c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  size_t sVar2;
  undefined1 uVar4;
  int iVar3;
  short sVar5;
  undefined4 extraout_r4;
  float *pfVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  undefined8 uVar11;
  char local_28 [8];
  undefined4 local_20;
  uint uStack_1c;
  
  iVar10 = *(int *)(param_9 + 0x8c);
  sVar5 = 30000;
  if (**(short **)(param_9 + 0xcc) < 30000) {
    sVar5 = **(short **)(param_9 + 0xcc);
  }
  if (*(short *)(param_9 + 0x1c) != sVar5) {
    *(short *)(param_9 + 0x1c) = sVar5;
    pfVar6 = (float *)(int)sVar5;
    sprintf(local_28,&DAT_8043ab38);
    sVar2 = strlen(local_28);
    if (sVar2 < 6) {
      sVar2 = strlen(local_28);
      uVar4 = (undefined1)sVar2;
    }
    else {
      uVar4 = 5;
    }
    *(undefined1 *)(param_9 + 0x13) = uVar4;
    pcVar9 = local_28;
    iVar8 = param_9;
    for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
      iVar3 = (int)*pcVar9;
      fVar1 = FLOAT_8043aa14;
      if ((0x2f < iVar3) && (iVar3 < 0x3a)) {
        uStack_1c = iVar3 - 0x30U ^ 0x80000000;
        local_20 = 0x43300000;
        fVar1 = (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8043aa90);
      }
      uVar11 = zz_00086b8_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_803bb384,*(int *)(iVar8 + 0xe0),pfVar6,param_12,param_13,param_14,
                           param_15,param_16);
      zz_0007c30_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar8 + 0xe0),extraout_r4,pfVar6,param_12,param_13,param_14,param_15,
                  param_16);
      pcVar9 = pcVar9 + 1;
      iVar8 = iVar8 + 4;
    }
  }
  if ('\x01' < *(char *)(iVar10 + 0x18)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 8016a8b8  FUN_8016a8b8 ====

void FUN_8016a8b8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  float afStack_48 [13];
  
  iVar1 = *(int *)(param_9 + 0x8c);
  if ((*(char *)(iVar1 + 0x87) != '\0') && (*(int *)(iVar1 + 0xcc) != 0)) {
    zz_00455fc_((float *)(iVar1 + 0x114),(float *)(param_9 + 0x114),(float *)(param_9 + 0x20));
    iVar1 = *(char *)(param_9 + 0x13) + -1;
    iVar4 = iVar1 * 0x24;
    iVar3 = param_9 + iVar1 * 4;
    for (; -1 < iVar1; iVar1 = iVar1 + -1) {
      pfVar2 = (float *)(*(int *)(param_9 + 0x54) + iVar4);
      zz_00455fc_((float *)(param_9 + 0x114),afStack_48,pfVar2);
      pfVar2 = pfVar2 + 3;
      uVar5 = zz_00456a0_(afStack_48,afStack_48,pfVar2);
      zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar3 + 0xe0),afStack_48,(undefined *)pfVar2,param_12,param_13,param_14,
                  param_15,param_16);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
      iVar4 = iVar4 + -0x24;
      iVar3 = iVar3 + -4;
    }
  }
  return;
}



// ==== 8016a97c  FUN_8016a97c ====

void FUN_8016a97c(int param_1,int param_2,float *param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int iVar7;
  int iVar8;
  short *psVar9;
  int iVar10;
  double dVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double local_28;
  
  fVar3 = FLOAT_8043ab9c;
  fVar2 = FLOAT_8043ab98;
  fVar1 = FLOAT_8043aa14;
  dVar14 = (double)FLOAT_8043ab98;
  dVar13 = (double)FLOAT_8043ab9c;
  psVar9 = &DAT_80350058;
  dVar11 = (double)FLOAT_8043aa14;
  iVar10 = 0;
  *(float *)(param_1 + 0x38) = FLOAT_8043ab94;
  fVar4 = FLOAT_8043aba0;
  *(float *)(param_1 + 0x3c) = fVar2;
  *(float *)(param_1 + 0x40) = fVar3;
  *(float *)(param_1 + 100) = fVar1;
  *(float *)(param_1 + 0x68) = fVar2;
  *(float *)(param_1 + 0x6c) = fVar3;
  *(float *)(param_1 + 0x9c) = fVar4;
  *(float *)(param_1 + 0xa0) = fVar2;
  *(float *)(param_1 + 0xa4) = fVar3;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x40);
  *(undefined2 *)(param_1 + 0x1c) = 0;
  *(short *)(param_1 + 0x1e) = (short)*(char *)(param_2 + 0x66);
  *(float *)(param_1 + 0xd4) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  iVar8 = param_1;
  for (iVar7 = 0; iVar7 < *(char *)(param_1 + 0x13); iVar7 = iVar7 + 1) {
    puVar6 = (undefined4 *)(*(int *)(param_1 + 0x54) + iVar10);
    fVar1 = FLOAT_8043aa14;
    if (iVar7 == 0) {
      fVar1 = FLOAT_8043aba4;
    }
    *(short *)(puVar6 + 8) = (short)(int)fVar1;
    *(undefined2 *)((int)puVar6 + 0x22) = 0;
    uVar5 = *(undefined4 *)(psVar9 + 6);
    *puVar6 = *(undefined4 *)(psVar9 + 4);
    puVar6[1] = uVar5;
    puVar6[2] = *(undefined4 *)(psVar9 + 8);
    uVar5 = *(undefined4 *)(psVar9 + 2);
    puVar6[5] = uVar5;
    puVar6[4] = uVar5;
    puVar6[3] = uVar5;
    param_3 = (float *)(int)*psVar9;
    dVar11 = (double)zz_0006fb4_(dVar11,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb384,
                                 *(int *)(iVar8 + 0xe0),(int)param_3,param_4,param_5,param_6,param_7
                                 ,param_8);
    if (iVar7 == 0) {
      uVar12 = zz_00086b8_((double)FLOAT_8043aa10,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,
                           DAT_803bb384,*(int *)(iVar8 + 0xe0),param_3,param_4,param_5,param_6,
                           param_7,param_8);
      dVar11 = (double)zz_0007c30_(uVar12,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,
                                   *(int *)(iVar8 + 0xe0),extraout_r4,param_3,param_4,param_5,
                                   param_6,param_7,param_8);
    }
    else if (iVar7 == 1) {
      local_28 = (double)(CONCAT44(0x43300000,
                                   (int)(char)PTR_DAT_80433944[*(short *)(param_1 + 0x1e) + 0x88]) ^
                         0x80000000);
      uVar12 = zz_00086b8_((double)(float)(local_28 - DOUBLE_8043aa90),dVar13,dVar14,in_f4,in_f5,
                           in_f6,in_f7,in_f8,DAT_803bb384,*(int *)(iVar8 + 0xe0),param_3,param_4,
                           param_5,param_6,param_7,param_8);
      uVar12 = zz_0007c30_(uVar12,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar8 + 0xe0)
                           ,extraout_r4_00,param_3,param_4,param_5,param_6,param_7,param_8);
      dVar11 = (double)zz_0007d40_(uVar12,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,
                                   *(int *)(iVar8 + 0xe0),extraout_r4_01,param_3,param_4,param_5,
                                   param_6,param_7,param_8);
    }
    iVar10 = iVar10 + 0x24;
    psVar9 = psVar9 + 10;
    iVar8 = iVar8 + 4;
  }
  zz_016ab40_(dVar11,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,param_1,param_2,param_3,param_4,
              param_5,param_6,param_7,param_8);
  return;
}



// ==== 8016ab40  zz_016ab40_ ====

void zz_016ab40_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  short sVar2;
  float fVar3;
  int iVar4;
  float *pfVar5;
  float *pfVar6;
  char cVar7;
  int iVar8;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  int iVar9;
  char *pcVar10;
  int iVar11;
  double dVar12;
  undefined8 uVar13;
  double dVar14;
  char local_4b [7];
  char acStack_44 [4];
  float local_40;
  undefined4 local_3c;
  undefined4 local_38;
  double local_30;
  undefined4 local_28;
  uint uStack_24;
  
  if ((*(byte *)(param_10 + 0x3d) & 2) == 0) {
    if ((*(byte *)(param_10 + 0x3f) & 2) == 0) {
      local_40 = *(float *)(param_9 + 0x38);
      local_3c = *(undefined4 *)(param_9 + 0x3c);
      local_38 = *(undefined4 *)(param_9 + 0x40);
    }
    else {
      local_40 = *(float *)(param_9 + 0x9c);
      local_3c = *(undefined4 *)(param_9 + 0xa0);
      local_38 = *(undefined4 *)(param_9 + 0xa4);
    }
  }
  else {
    local_40 = *(float *)(param_9 + 100);
    local_3c = *(undefined4 *)(param_9 + 0x68);
    local_38 = *(undefined4 *)(param_9 + 0x6c);
  }
  gnt4_PSVECSubtract_bl(&local_40,(float *)(param_9 + 0x20),&local_40);
  gnt4_PSQUATScale_bl((double)FLOAT_8043aa34,&local_40,&local_40);
  pfVar6 = (float *)(param_9 + 0x20);
  gnt4_PSVECAdd_bl(pfVar6,&local_40,pfVar6);
  fVar3 = FLOAT_8043aba8;
  fVar1 = *(float *)(param_9 + 0xd4) + FLOAT_8043aab8;
  *(float *)(param_9 + 0xd4) = fVar1;
  if (fVar3 <= fVar1) {
    *(float *)(param_9 + 0xd4) = *(float *)(param_9 + 0xd4) - fVar3;
  }
  sVar2 = *(short *)(param_9 + 0x1e);
  local_40 = FLOAT_8043aa14;
  if ((int)sVar2 != (int)*(char *)(param_10 + 0x66)) {
    fVar1 = *(float *)(param_9 + 0x58);
    fVar3 = fVar1;
    if (fVar1 < FLOAT_8043aa14) {
      fVar3 = -fVar1;
    }
    if (FLOAT_8043abac <= fVar3) {
      if (fVar1 < FLOAT_8043abac) {
        if (fVar1 <= FLOAT_8043abb8) {
          *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x58) + FLOAT_8043abb0;
        }
      }
      else {
        *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x58) - FLOAT_8043abb0;
      }
      *(short *)(param_9 + 0x1e) = (short)*(char *)(param_10 + 0x66);
    }
    else if ((*(byte *)(param_10 + 0x67) & 1) == 0) {
      if ((*(byte *)(param_10 + 0x67) & 2) != 0) {
        local_40 = FLOAT_8043abb4;
      }
    }
    else {
      local_40 = FLOAT_8043abb0;
    }
  }
  local_40 = local_40 - *(float *)(param_9 + 0x58);
  dVar14 = (double)local_40;
  dVar12 = dVar14;
  if (dVar14 < (double)FLOAT_8043aa14) {
    dVar12 = -dVar14;
  }
  if ((double)FLOAT_8043ab08 < dVar12) {
    dVar12 = dVar14;
    if (dVar14 < (double)FLOAT_8043aa14) {
      dVar12 = -dVar14;
    }
    local_40 = (float)((double)(float)((double)FLOAT_8043ab08 * dVar12) / dVar14);
  }
  *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x58) + local_40;
  if (*(short *)(param_9 + 0x1e) < 0) {
    sprintf(local_4b + 3,&DAT_8043abc4);
    sprintf(acStack_44,&DAT_8043abc8);
  }
  else {
    iVar9 = (&DAT_803bfe00)[(char)PTR_DAT_80433944[*(short *)(param_9 + 0x1e) + 0x88]];
    iVar4 = (int)*(short *)(iVar9 + 0x2172);
    iVar11 = 200;
    if (iVar4 < 200) {
      iVar11 = iVar4;
    }
    sprintf(local_4b + 3,&DAT_8043abbc,iVar11);
    pfVar5 = (float *)(int)*(short *)(iVar9 + 0x2170);
    pfVar6 = (float *)0x14;
    if ((int)pfVar5 < 0x14) {
      pfVar6 = pfVar5;
    }
    sprintf(acStack_44,&DAT_8043abc0);
  }
  iVar9 = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  pcVar10 = local_4b + 3;
  iVar11 = param_9;
  for (iVar4 = 0; dVar12 = DOUBLE_8043aa90, iVar4 < *(char *)(param_9 + 0x13); iVar4 = iVar4 + 1) {
    iVar8 = *(int *)(param_9 + 0x54) + iVar9;
    if (iVar4 < 3) {
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar4);
      if (iVar4 == 1) {
        *(short *)(iVar8 + 0x22) = *(short *)(iVar8 + 0x22) + -0x100;
        if ((int)*(short *)(param_9 + 0x1e) != (int)sVar2) {
          local_30 = (double)(CONCAT44(0x43300000,
                                       (int)(char)PTR_DAT_80433944
                                                  [*(short *)(param_9 + 0x1e) + 0x88]) ^ 0x80000000)
          ;
          uVar13 = zz_00086b8_((double)(float)(local_30 - DOUBLE_8043aa90),dVar14,param_3,param_4,
                               param_5,param_6,param_7,param_8,DAT_803bb384,*(int *)(iVar11 + 0xe0),
                               pfVar6,param_12,param_13,param_14,param_15,param_16);
          uVar13 = zz_0007c30_(uVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                               *(int *)(iVar11 + 0xe0),extraout_r4,pfVar6,param_12,param_13,param_14
                               ,param_15,param_16);
          zz_0007d40_(uVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar11 + 0xe0),extraout_r4_00,pfVar6,param_12,param_13,param_14,
                      param_15,param_16);
        }
        local_28 = 0x43300000;
        local_30 = (double)(longlong)(int)*(float *)(param_9 + 0xd4);
        uStack_24 = (int)*(float *)(param_9 + 0xd4) ^ 0x80000000;
        uVar13 = zz_0008744_((double)(float)((double)CONCAT44(0x43300000,uStack_24) -
                                            DOUBLE_8043aa90),dVar14,param_3,param_4,param_5,param_6,
                             param_7,param_8,DAT_803bb384,*(int *)(iVar11 + 0xe0),pfVar6,param_12,
                             param_13,param_14,param_15,param_16);
        zz_0007c30_(uVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar11 + 0xe0),extraout_r4_01,pfVar6,param_12,param_13,param_14,
                    param_15,param_16);
      }
    }
    else {
      if (iVar4 < 6) {
        cVar7 = pcVar10[-3];
      }
      else {
        cVar7 = pcVar10[-2];
      }
      iVar8 = (int)cVar7;
      if ((0x2f < iVar8) && (iVar8 < 0x3a)) {
        uStack_24 = iVar8 - 0x30U ^ 0x80000000;
        local_28 = 0x43300000;
        *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar4);
        uVar13 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_24) - dVar12),dVar14
                             ,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                             *(int *)(iVar11 + 0xe0),pfVar6,param_12,param_13,param_14,param_15,
                             param_16);
        zz_0007c30_(uVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar11 + 0xe0),extraout_r4_02,pfVar6,param_12,param_13,param_14,
                    param_15,param_16);
      }
    }
    iVar9 = iVar9 + 0x24;
    iVar11 = iVar11 + 4;
    pcVar10 = pcVar10 + 1;
  }
  return;
}



// ==== 8016af70  FUN_8016af70 ====

void FUN_8016af70(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
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
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float afStack_50 [14];
  
  if (*(short *)(param_1 + 0x1c) != 0) {
    dVar7 = (double)*(float *)(param_1 + 0x24);
    dVar8 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar7,dVar8,(float *)(param_1 + 0x114));
    iVar3 = *(char *)(param_1 + 0x13) + -1;
    iVar5 = iVar3 * 0x24;
    iVar4 = param_1 + iVar3 * 4;
    while( true ) {
      if (iVar3 < 0) break;
      if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar3) != 0) {
        pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
        zz_00455fc_((float *)(param_1 + 0x114),afStack_50,pfVar2);
        if (((*(byte *)(param_2 + 0x3d) & 2) != 0) && (0 < iVar3)) {
          zz_00455fc_(afStack_50,afStack_50,(float *)(param_1 + 0x58));
        }
        zz_00457d4_('y',afStack_50,afStack_50,*(short *)((int)pfVar2 + 0x22));
        iVar1 = (int)*(short *)(pfVar2 + 8);
        zz_00457d4_('x',afStack_50,afStack_50,*(short *)(pfVar2 + 8));
        pfVar2 = pfVar2 + 3;
        uVar6 = zz_00456a0_(afStack_50,afStack_50,pfVar2);
        zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),
                    afStack_50,(undefined *)pfVar2,iVar1,param_5,param_6,param_7,param_8);
        if (iVar3 == 1) {
          zz_00097b4_(*(int *)(iVar4 + 0xe0),1);
        }
        else {
          zz_00097b4_(*(int *)(iVar4 + 0xe0),0x44);
        }
      }
      iVar5 = iVar5 + -0x24;
      iVar4 = iVar4 + -4;
      iVar3 = iVar3 + -1;
    }
    if (((*(ushort *)(param_1 + 0x1c) & 4) != 0) && (-1 < *(short *)(param_1 + 0x1e))) {
      local_5c = FLOAT_8043abcc;
      local_58 = FLOAT_8043aa14;
      iVar3 = (&DAT_803bfe00)[(char)PTR_DAT_80433944[*(short *)(param_1 + 0x1e) + 0x88]];
      local_54 = FLOAT_8043aa84;
      gnt4_PSVECAdd_bl(&local_5c,(float *)(param_1 + 0x58),&local_5c);
      local_60 = FLOAT_8043aa10;
      local_64 = FLOAT_8043aa10;
      local_68 = FLOAT_8043aa10;
      FUN_801c53dc((double)FLOAT_8043aa10,(double)FLOAT_8043abd0,(double)FLOAT_8043abd4,
                   (float *)(param_1 + 0x114),&local_5c,&local_68,3,0x1e,(short *)(iVar3 + 0x2174));
    }
  }
  return;
}



// ==== 8016b138  FUN_8016b138 ====

void FUN_8016b138(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  undefined2 *puVar7;
  int iVar8;
  double dVar9;
  
  fVar1 = FLOAT_8043aa14;
  dVar9 = (double)FLOAT_8043aa14;
  puVar7 = &DAT_803500f8;
  iVar8 = 0;
  *(float *)(param_9 + 0x38) = FLOAT_8043abd8;
  fVar2 = FLOAT_8043abdc;
  *(float *)(param_9 + 0x3c) = fVar1;
  *(float *)(param_9 + 0x40) = fVar1;
  *(float *)(param_9 + 100) = fVar1;
  *(float *)(param_9 + 0x68) = fVar1;
  *(float *)(param_9 + 0x6c) = fVar1;
  *(float *)(param_9 + 0x9c) = fVar2;
  *(float *)(param_9 + 0xa0) = fVar1;
  *(float *)(param_9 + 0xa4) = fVar1;
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
  *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x3c);
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x40);
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(undefined2 *)(param_9 + 0x1c) = 0xffff;
  *(short *)(param_9 + 0x1e) = (short)*(char *)(param_10 + 0x62);
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    uVar3 = *(undefined4 *)(puVar7 + 4);
    puVar4 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar8);
    *puVar4 = *(undefined4 *)(puVar7 + 2);
    puVar4[1] = uVar3;
    puVar4[2] = *(undefined4 *)(puVar7 + 6);
    *(undefined2 *)(puVar4 + 8) = puVar7[1];
    *(undefined2 *)((int)puVar4 + 0x22) = *puVar7;
    if (2 < iVar5) {
      dVar9 = (double)zz_0006fb4_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  DAT_803bb384,*(int *)(iVar6 + 0xe0),
                                  (int)*(short *)((int)puVar4 + 0x22),param_12,param_13,param_14,
                                  param_15,param_16);
    }
    iVar8 = iVar8 + 0x24;
    puVar7 = puVar7 + 8;
    iVar6 = iVar6 + 4;
  }
  zz_016b260_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10);
  return;
}



// ==== 8016b260  zz_016b260_ ====

void zz_016b260_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  float *pfVar5;
  undefined1 *puVar6;
  undefined *puVar7;
  int iVar8;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  double dVar10;
  undefined8 uVar11;
  float local_38;
  float local_34;
  float local_30;
  undefined4 local_28;
  uint uStack_24;
  
  if ((*(byte *)(param_10 + 0x3d) & 0x20) == 0) {
    if ((*(byte *)(param_10 + 0x3f) & 0x20) == 0) {
      local_38 = *(float *)(param_9 + 0x38);
      local_34 = *(float *)(param_9 + 0x3c);
      local_30 = *(float *)(param_9 + 0x40);
    }
    else {
      local_38 = *(float *)(param_9 + 0x9c);
      local_34 = *(float *)(param_9 + 0xa0);
      local_30 = *(float *)(param_9 + 0xa4);
    }
  }
  else {
    local_38 = *(float *)(param_9 + 100);
    local_34 = *(float *)(param_9 + 0x68);
    local_30 = *(float *)(param_9 + 0x6c);
  }
  gnt4_PSVECSubtract_bl(&local_38,(float *)(param_9 + 0x20),&local_38);
  gnt4_PSQUATScale_bl((double)FLOAT_8043aa34,&local_38,&local_38);
  gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_38,(float *)(param_9 + 0x20));
  local_30 = FLOAT_8043aa14;
  local_34 = FLOAT_8043aa14;
  local_38 = FLOAT_8043aa14;
  iVar2 = (int)*(short *)(param_9 + 0x1e);
  iVar3 = (int)*(char *)(param_10 + 0x62);
  if (iVar2 != iVar3) {
    param_2 = (double)*(float *)(param_9 + 0x58);
    dVar10 = param_2;
    if (param_2 < (double)FLOAT_8043aa14) {
      dVar10 = -param_2;
    }
    if ((double)FLOAT_8043ab04 <= dVar10) {
      if (param_2 < (double)FLOAT_8043ab04) {
        if (param_2 <= (double)FLOAT_8043abb8) {
          *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x58) + FLOAT_8043abac;
        }
      }
      else {
        *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x58) - FLOAT_8043abac;
      }
      *(short *)(param_9 + 0x1e) = (short)*(char *)(param_10 + 0x62);
    }
    else {
      if (iVar3 < iVar2) {
        local_38 = FLOAT_8043abac;
      }
      else if (iVar2 < iVar3) {
        local_38 = FLOAT_8043ab9c;
      }
      iVar2 = (int)*(char *)(param_10 + 0x62) - (int)*(short *)(param_9 + 0x1e);
      if (iVar2 < 0) {
        iVar2 = -iVar2;
      }
      if (1 < iVar2) {
        local_38 = -local_38;
      }
    }
  }
  gnt4_PSVECSubtract_bl(&local_38,(float *)(param_9 + 0x58),&local_38);
  dVar10 = gnt4_PSVECMag_bl(&local_38);
  if ((double)FLOAT_8043abe0 < dVar10) {
    gnt4_PSVECNormalize_bl(&local_38,&local_38);
    gnt4_PSQUATScale_bl((double)FLOAT_8043abe0,&local_38,&local_38);
  }
  uVar11 = gnt4_PSVECAdd_bl((float *)(param_9 + 0x58),&local_38,(float *)(param_9 + 0x58));
  if (*(short *)(param_9 + 0x1c) != *(short *)(param_9 + 0x1e)) {
    *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1e);
    iVar9 = 0;
    iVar2 = param_9;
    for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
      iVar8 = *(int *)(param_9 + 0x54) + iVar9;
      if (iVar3 < 3) {
        for (iVar4 = (int)*(short *)(param_9 + 0x1c) + iVar3 + -1; iVar4 < 0;
            iVar4 = iVar4 + (char)PTR_DAT_80433944[0x6a]) {
        }
        for (; (char)PTR_DAT_80433944[0x6a] <= iVar4; iVar4 = iVar4 - (char)PTR_DAT_80433944[0x6a])
        {
        }
        puVar6 = &DAT_8035162c + (char)PTR_DAT_80433944[iVar4 + 0x58] * 2;
        cVar1 = (&DAT_8035162d)[(char)PTR_DAT_80433944[iVar4 + 0x58] * 2];
        uVar11 = zz_0006fb4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             DAT_803bb384,*(int *)(iVar2 + 0xe0),(int)*(short *)(iVar8 + 0x22),
                             puVar6,iVar8,in_r8,in_r9,in_r10);
        uVar11 = zz_00075cc_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             DAT_803bb384,*(int *)(iVar2 + 0xe0),
                             (char *)(int)*(short *)(&DAT_80350158 + cVar1 * 2),puVar6,iVar8,in_r8,
                             in_r9,in_r10);
      }
      else if (iVar3 == 3) {
        local_28 = 0x43300000;
        pfVar5 = (float *)(&DAT_8035162c +
                          (char)PTR_DAT_80433944[*(short *)(param_9 + 0x1c) + 0x58] * 2);
        uStack_24 = (int)(char)(&DAT_8035162d)
                               [(char)PTR_DAT_80433944[*(short *)(param_9 + 0x1c) + 0x58] * 2] ^
                    0x80000000;
        puVar7 = PTR_DAT_80433944;
        uVar11 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_24) -
                                            DOUBLE_8043aa90),param_2,param_3,param_4,param_5,param_6
                             ,param_7,param_8,DAT_803bb384,*(int *)(iVar2 + 0xe0),pfVar5,
                             PTR_DAT_80433944,iVar8,in_r8,in_r9,in_r10);
        uVar11 = zz_0007c30_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             *(int *)(iVar2 + 0xe0),extraout_r4,pfVar5,puVar7,iVar8,in_r8,in_r9,
                             in_r10);
      }
      iVar9 = iVar9 + 0x24;
      iVar2 = iVar2 + 4;
    }
  }
  return;
}



// ==== 8016b5ac  FUN_8016b5ac ====

/* WARNING: Removing unreachable block (ram,0x8016b664) */
/* WARNING: Removing unreachable block (ram,0x8016b698) */

void FUN_8016b5ac(int param_1)

{
  short sVar1;
  bool bVar2;
  int iVar3;
  uint uVar4;
  float *pfVar5;
  int iVar6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  int iVar8;
  int iVar9;
  float *pfVar10;
  undefined8 uVar11;
  double dVar12;
  double dVar13;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  dVar12 = (double)*(float *)(param_1 + 0x24);
  dVar13 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar12,dVar13,(float *)(param_1 + 0x114));
  iVar9 = 0;
  iVar8 = param_1;
  for (iVar7 = 0; iVar7 < *(char *)(param_1 + 0x13); iVar7 = iVar7 + 1) {
    pfVar10 = (float *)(*(int *)(param_1 + 0x54) + iVar9);
    zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar10);
    if (iVar7 < 3) {
      zz_00455fc_(afStack_48,afStack_48,(float *)(param_1 + 0x58));
    }
    pfVar5 = afStack_48;
    sVar1 = *(short *)(pfVar10 + 8);
    iVar6 = (int)sVar1;
    uVar11 = zz_00457d4_('x',pfVar5,pfVar5,sVar1);
    zz_00076d0_(uVar11,dVar12,dVar13,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar8 + 0xe0),afStack_48
                ,(undefined *)pfVar5,iVar6,in_r7,in_r8,in_r9,in_r10);
    if (iVar7 < 3) {
      iVar3 = *(int *)(*(int *)(iVar8 + 0xe0) + 0xc);
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(iVar3 + 0x10);
      }
      if (iVar3 != 0) {
        uVar11 = gnt4_PSMTXCopy_bl(afStack_48,(float *)(iVar3 + 0x44));
        *(uint *)(iVar3 + 0x14) = *(uint *)(iVar3 + 0x14) | 0x3800000;
        if (iVar3 != 0) {
          uVar4 = *(uint *)(iVar3 + 0x14);
          bVar2 = false;
          if (((uVar4 & 0x800000) == 0) && ((uVar4 & 0x40) != 0)) {
            bVar2 = true;
          }
          if (!bVar2) {
            gnt4_HSD_JObjSetMtxDirtySub_bl
                      (uVar11,dVar12,dVar13,in_f4,in_f5,in_f6,in_f7,in_f8,iVar3,uVar4,
                       (undefined *)pfVar5,iVar6,in_r7,in_r8,in_r9,in_r10);
          }
        }
      }
      zz_00097b4_(*(int *)(iVar8 + 0xe0),0x45);
    }
    else {
      zz_00097b4_(*(int *)(iVar8 + 0xe0),0x44);
    }
    iVar9 = iVar9 + 0x24;
    iVar8 = iVar8 + 4;
  }
  return;
}



// ==== 8016b720  FUN_8016b720 ====

void FUN_8016b720(int param_1,int param_2,undefined4 param_3,int param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  fVar4 = FLOAT_8043abec;
  fVar3 = FLOAT_8043abe8;
  fVar2 = FLOAT_8043abe4;
  fVar1 = FLOAT_8043aa14;
  iVar7 = -0x7fc40000;
  dVar13 = (double)FLOAT_8043abe4;
  dVar12 = (double)FLOAT_8043abe8;
  dVar11 = (double)FLOAT_8043abec;
  iVar10 = 0;
  *(float *)(param_1 + 0x44) = FLOAT_8043aa14;
  *(float *)(param_1 + 0xd4) = fVar1;
  fVar1 = FLOAT_8043abf0;
  *(float *)(param_1 + 0x38) = fVar2;
  *(float *)(param_1 + 0x3c) = fVar3;
  *(float *)(param_1 + 0x40) = fVar4;
  *(float *)(param_1 + 100) = fVar2;
  *(float *)(param_1 + 0x68) = fVar3;
  *(float *)(param_1 + 0x6c) = fVar1;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x40);
  iVar9 = param_1;
  for (iVar8 = 0; fVar2 = FLOAT_8043aa50, fVar1 = FLOAT_8043aa10, iVar8 < *(char *)(param_1 + 0x13);
      iVar8 = iVar8 + 1) {
    puVar6 = (undefined4 *)(*(int *)(param_1 + 0x54) + iVar10);
    iVar7 = 2;
    if (iVar8 < 2) {
      iVar7 = iVar8;
    }
    if (iVar8 < 2) {
      puVar6[5] = FLOAT_8043aa10;
      puVar6[4] = fVar1;
      puVar6[3] = fVar1;
    }
    else {
      dVar11 = (double)FLOAT_8043aa50;
      puVar6[3] = FLOAT_8043aa50;
      puVar6[4] = fVar2;
      puVar6[5] = fVar1;
    }
    *(undefined2 *)(puVar6 + 8) = (&DAT_8035017e)[iVar7 * 8];
    uVar5 = (&DAT_80350184)[iVar7 * 4];
    *puVar6 = (&DAT_80350180)[iVar7 * 4];
    puVar6[1] = uVar5;
    puVar6[2] = (&DAT_80350188)[iVar7 * 4];
    iVar7 = (int)(short)(&DAT_8035017c)[iVar7 * 8];
    dVar11 = (double)zz_0006fb4_(dVar11,dVar12,dVar13,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb384,
                                 *(int *)(iVar9 + 0xe0),iVar7,param_4,param_5,param_6,param_7,
                                 param_8);
    iVar10 = iVar10 + 0x24;
    iVar9 = iVar9 + 4;
  }
  zz_016b860_(dVar11,dVar12,dVar13,in_f4,in_f5,in_f6,in_f7,in_f8,param_1,param_2,iVar7,param_4,
              param_5,param_6,param_7,param_8);
  return;
}



// ==== 8016b860  zz_016b860_ ====

/* WARNING: Removing unreachable block (ram,0x8016bb80) */
/* WARNING: Removing unreachable block (ram,0x8016b870) */

void zz_016b860_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,int param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  uint uVar2;
  size_t sVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  bool bVar10;
  double dVar11;
  double dVar12;
  undefined8 uVar13;
  double dVar14;
  char cStack_48;
  char acStack_47 [3];
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  uint uStack_34;
  
  fVar1 = FLOAT_8043aa14;
  dVar14 = (double)*(float *)(param_9 + 0x44);
  if ((*(byte *)(param_10 + 0x3d) & 0x20) == 0) {
    dVar12 = (double)FLOAT_8043aa14;
    if (dVar14 <= dVar12) {
      local_44 = *(float *)(param_9 + 0x38);
      local_40 = *(undefined4 *)(param_9 + 0x3c);
      local_3c = *(undefined4 *)(param_9 + 0x40);
      *(float *)(param_9 + 0x20) = local_44;
      *(undefined4 *)(param_9 + 0x24) = local_40;
      *(undefined4 *)(param_9 + 0x28) = local_3c;
    }
    else {
      dVar11 = (double)FLOAT_8043aa2c;
      *(float *)(param_9 + 0x44) = (float)(dVar14 - dVar11);
      if ((double)(float)(dVar14 - dVar11) < dVar12) {
        *(float *)(param_9 + 0x44) = fVar1;
      }
      local_44 = *(float *)(param_9 + 100);
      local_40 = *(undefined4 *)(param_9 + 0x68);
      local_3c = *(undefined4 *)(param_9 + 0x6c);
    }
  }
  else {
    *(float *)(param_9 + 0x44) = FLOAT_8043aa10;
    local_44 = *(float *)(param_9 + 100);
    local_40 = *(undefined4 *)(param_9 + 0x68);
    local_3c = *(undefined4 *)(param_9 + 0x6c);
  }
  gnt4_PSVECSubtract_bl(&local_44,(float *)(param_9 + 0x20),&local_44);
  gnt4_PSQUATScale_bl((double)FLOAT_8043aa34,&local_44,&local_44);
  gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_44,(float *)(param_9 + 0x20));
  fVar1 = FLOAT_8043aa14;
  if (*(char *)(param_10 + 99) == '\0') {
    param_2 = (double)*(float *)(param_9 + 0xd4);
    bVar10 = (float)(param_2 - DOUBLE_8043abf8) < FLOAT_8043aa14;
    *(float *)(param_9 + 0xd4) = (float)(param_2 - DOUBLE_8043abf8);
    if (bVar10) {
      *(float *)(param_9 + 0xd4) = fVar1;
    }
  }
  else {
    *(float *)(param_9 + 0xd4) = FLOAT_8043aa10;
  }
  if (FLOAT_8043aa14 != *(float *)(param_9 + 0x44)) {
    uVar2 = (uint)*(short *)(PTR_DAT_80433944 + *(char *)(param_10 + 0x62) * 2 + 0x30);
    if ((int)uVar2 < 1000) {
      uVar2 = uVar2 & ~((int)uVar2 >> 0x1f);
    }
    else {
      uVar2 = 999;
    }
    sprintf(&cStack_48,&DAT_8043ab38,uVar2);
    sVar3 = strlen(&cStack_48);
    iVar9 = 0;
    *(short *)(param_9 + 0x1c) = (short)sVar3;
    iVar8 = 0;
    iVar7 = param_9;
    for (iVar6 = 0; dVar12 = DOUBLE_8043aa90, iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1)
    {
      pfVar5 = *(float **)(param_9 + 0x54);
      if (iVar6 == 0) {
        uVar13 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,
                             param_6,param_7,param_8,DAT_803bb384,*(int *)(iVar7 + 0xe0),pfVar5,
                             param_12,param_13,param_14,param_15,param_16);
        zz_0007c30_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar7 + 0xe0),extraout_r4,pfVar5,param_12,param_13,param_14,param_15,
                    param_16);
      }
      else if (iVar6 == 1) {
        local_38 = 0x43300000;
        uStack_34 = 1U - (int)*(short *)(param_9 + 0x1c) ^ 0x80000000;
        param_4 = (double)FLOAT_8043ac00;
        param_2 = (double)(float)(param_4 *
                                 (double)(float)((double)CONCAT44(0x43300000,uStack_34) -
                                                DOUBLE_8043aa90));
        *(float *)((int)pfVar5 + iVar9) =
             (float)(param_2 * (double)FLOAT_8043aab8 - (double)FLOAT_8043ac04);
        param_3 = dVar12;
      }
      else if ((1 < iVar6) && (param_12 = (int)*(short *)(param_9 + 0x1c), iVar6 < param_12 + 2)) {
        iVar4 = (int)acStack_47[param_12 - iVar6];
        fVar1 = FLOAT_8043aa14;
        if ((0x2f < iVar4) && (iVar4 < 0x3a)) {
          fVar1 = (float)((double)CONCAT44(0x43300000,iVar4 - 0x30U ^ 0x80000000) - DOUBLE_8043aa90)
          ;
        }
        local_38 = 0x43300000;
        uStack_34 = (param_12 - iVar8) + 3U ^ 0x80000000;
        param_4 = (double)FLOAT_8043ac00;
        param_2 = (double)FLOAT_8043aab8;
        param_3 = (double)(float)(param_4 *
                                 (double)(float)((double)CONCAT44(0x43300000,uStack_34) -
                                                DOUBLE_8043aa90));
        *(float *)((int)pfVar5 + iVar9) = (float)(param_3 * param_2 + (double)FLOAT_8043ac08);
        uVar13 = zz_00086b8_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             DAT_803bb384,*(int *)(iVar7 + 0xe0),pfVar5,param_12,param_13,param_14,
                             param_15,param_16);
        zz_0007c30_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar7 + 0xe0),extraout_r4_00,pfVar5,param_12,param_13,param_14,param_15
                    ,param_16);
      }
      iVar9 = iVar9 + 0x24;
      iVar7 = iVar7 + 4;
      iVar8 = iVar8 + 2;
    }
  }
  if ((double)*(float *)(param_9 + 0x44) != dVar14) {
    iVar7 = param_9;
    for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
      zz_0007cac_((double)*(float *)(param_9 + 0x44),*(int *)(iVar7 + 0xe0));
      iVar7 = iVar7 + 4;
    }
  }
  return;
}



// ==== 8016bb9c  FUN_8016bb9c ====

void FUN_8016bb9c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
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
  
  if (FLOAT_8043aa14 != *(float *)(param_1 + 0x44)) {
    dVar7 = (double)*(float *)(param_1 + 0x24);
    dVar8 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar7,dVar8,(float *)(param_1 + 0x114));
    iVar5 = 0;
    iVar4 = param_1;
    for (iVar3 = 0; iVar3 < (int)*(char *)(param_1 + 0x13) + *(short *)(param_1 + 0x1c) + -3;
        iVar3 = iVar3 + 1) {
      pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
      zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar2);
      pfVar1 = pfVar2 + 3;
      uVar6 = zz_00456a0_(afStack_48,afStack_48,pfVar1);
      zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),afStack_48,
                  (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar4 + 0xe0),(int)*(short *)(pfVar2 + 8));
      iVar5 = iVar5 + 0x24;
      iVar4 = iVar4 + 4;
    }
  }
  return;
}



// ==== 8016bc60  FUN_8016bc60 ====

void FUN_8016bc60(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  
  fVar2 = FLOAT_8043ac0c;
  fVar1 = FLOAT_8043aa14;
  dVar4 = (double)FLOAT_8043aa14;
  pfVar3 = (float *)0x67;
  *(float *)(param_9 + 0xd4) = FLOAT_8043aa14;
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



// ==== 8016bcd8  FUN_8016bcd8 ====

void FUN_8016bcd8(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,int param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  bool bVar3;
  undefined8 uVar4;
  double dVar5;
  
  fVar2 = FLOAT_8043aa14;
  fVar1 = FLOAT_8043aa10;
  dVar5 = (double)*(float *)(param_9 + 0xd4);
  if ((*(byte *)(param_10 + 0x3d) & 0x10) == 0) {
    bVar3 = (float)(dVar5 - (double)FLOAT_8043aa28) < FLOAT_8043aa14;
    *(float *)(param_9 + 0xd4) = (float)(dVar5 - (double)FLOAT_8043aa28);
    if (bVar3) {
      *(float *)(param_9 + 0xd4) = fVar2;
    }
  }
  else {
    bVar3 = FLOAT_8043aa10 < (float)(dVar5 + (double)FLOAT_8043aa28);
    *(float *)(param_9 + 0xd4) = (float)(dVar5 + (double)FLOAT_8043aa28);
    if (bVar3) {
      *(float *)(param_9 + 0xd4) = fVar1;
    }
  }
  if ((double)*(float *)(param_9 + 0xd4) != dVar5) {
    uVar4 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),dVar5,param_3,param_4,param_5,param_6,
                        param_7,param_8,DAT_803bb384,*(int *)(param_9 + 0xe0),param_11,param_12,
                        param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
                ,extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8016bd74  FUN_8016bd74 ====

void FUN_8016bd74(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  
  if (FLOAT_8043aa14 < *(float *)(param_9 + 0xd4)) {
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



// ==== 8016be08  FUN_8016be08 ====

void FUN_8016be08(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                 undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  fVar1 = FLOAT_8043ac14;
  *(float *)(param_1 + 100) = FLOAT_8043ac10;
  fVar2 = FLOAT_8043ac18;
  *(float *)(param_1 + 0x68) = fVar1;
  *(float *)(param_1 + 0x6c) = fVar2;
  if (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_1 + 0x96)) == 0) {
    *(float *)(param_1 + 100) = *(float *)(param_1 + 100) + FLOAT_8043ac1c;
  }
  dVar6 = (double)FLOAT_8043aaf8;
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 100);
  fVar2 = FLOAT_8043aa24;
  dVar5 = (double)FLOAT_8043aa24;
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x68);
  fVar1 = FLOAT_8043aa14;
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x6c);
  dVar8 = (double)*(float *)(param_1 + 0x3c);
  dVar7 = (double)(float)(dVar8 + dVar6);
  *(float *)(param_1 + 0x3c) = (float)(dVar8 + dVar6);
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x40);
  *(float *)(param_1 + 0xd4) = fVar2;
  *(float *)(param_1 + 0xd8) = fVar1;
  iVar4 = param_1;
  for (iVar3 = 0; iVar3 < *(char *)(param_1 + 0x13); iVar3 = iVar3 + 1) {
    dVar5 = (double)zz_0006fb4_(dVar5,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb384,
                                *(int *)(iVar4 + 0xe0),0x9b,param_4,param_5,param_6,param_7,param_8)
    ;
    iVar4 = iVar4 + 4;
  }
  zz_016bf18_(param_1,param_2);
  return;
}



// ==== 8016bf18  zz_016bf18_ ====

/* WARNING: Removing unreachable block (ram,0x8016c0fc) */
/* WARNING: Removing unreachable block (ram,0x8016c0f4) */
/* WARNING: Removing unreachable block (ram,0x8016bf30) */
/* WARNING: Removing unreachable block (ram,0x8016bf28) */

void zz_016bf18_(int param_1,int param_2)

{
  byte bVar1;
  float *pfVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar3;
  float fVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  int iVar6;
  double dVar7;
  undefined8 uVar8;
  double dVar9;
  double dVar10;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar11;
  float local_68;
  undefined4 local_64;
  undefined4 local_60;
  double local_58;
  float local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_40;
  uint uStack_3c;
  
  fVar4 = FLOAT_8043aba8;
  dVar10 = DOUBLE_8043aa90;
  dVar11 = (double)*(float *)(param_1 + 0xd4);
  dVar7 = (double)FLOAT_8043aab8;
  local_58 = (double)(CONCAT44(0x43300000,
                               (int)(char)PTR_DAT_80433944[*(char *)(param_2 + 0x66) + 0x88]) ^
                     0x80000000);
  *(float *)(param_1 + 0xd4) = (float)(local_58 - DOUBLE_8043aa90);
  dVar9 = (double)*(float *)(param_1 + 0xd8);
  *(float *)(param_1 + 0xd8) = (float)(dVar9 + dVar7);
  if (fVar4 <= (float)(dVar9 + dVar7)) {
    *(float *)(param_1 + 0xd8) = *(float *)(param_1 + 0xd8) - fVar4;
  }
  if (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_1 + 0x96)) == 0) {
    bVar1 = *(byte *)(param_2 + 0x3d) | *(byte *)(param_2 + 0x3f);
  }
  else {
    bVar1 = *(byte *)(param_2 + 0x3d);
  }
  if ((bVar1 & 4) == 0) {
    local_50 = *(float *)(param_1 + 0x38);
    local_4c = *(undefined4 *)(param_1 + 0x3c);
    local_48 = *(undefined4 *)(param_1 + 0x40);
  }
  else {
    local_50 = *(float *)(param_1 + 100);
    local_4c = *(undefined4 *)(param_1 + 0x68);
    local_48 = *(undefined4 *)(param_1 + 0x6c);
  }
  local_68 = local_50;
  local_64 = local_4c;
  local_60 = local_48;
  uVar3 = local_4c;
  fVar4 = local_50;
  gnt4_PSVECSubtract_bl(&local_68,(float *)(param_1 + 0x20),&local_68);
  gnt4_PSQUATScale_bl((double)FLOAT_8043aa34,&local_68,&local_68);
  pfVar2 = (float *)(param_1 + 0x20);
  gnt4_PSVECAdd_bl(pfVar2,&local_68,pfVar2);
  iVar6 = param_1;
  dVar7 = DOUBLE_8043aa90;
  for (iVar5 = 0; iVar5 < *(char *)(param_1 + 0x13); iVar5 = iVar5 + 1) {
    if ((double)*(float *)(param_1 + 0xd4) != dVar11) {
      uVar8 = zz_00086b8_((double)*(float *)(param_1 + 0xd4),dVar9,dVar10,in_f4,in_f5,in_f6,in_f7,
                          in_f8,DAT_803bb384,*(int *)(iVar6 + 0xe0),pfVar2,uVar3,fVar4,in_r8,in_r9,
                          in_r10);
      uVar8 = zz_0007c30_(uVar8,dVar9,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar6 + 0xe0),
                          extraout_r4,pfVar2,uVar3,fVar4,in_r8,in_r9,in_r10);
      zz_0007d40_(uVar8,dVar9,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar6 + 0xe0),
                  extraout_r4_00,pfVar2,uVar3,fVar4,in_r8,in_r9,in_r10);
    }
    local_40 = 0x43300000;
    local_58 = (double)(longlong)(int)*(float *)(param_1 + 0xd8);
    uStack_3c = (int)*(float *)(param_1 + 0xd8) ^ 0x80000000;
    uVar8 = zz_0008744_((double)(float)((double)CONCAT44(0x43300000,uStack_3c) - dVar7),dVar9,dVar10
                        ,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb384,*(int *)(iVar6 + 0xe0),pfVar2,
                        uVar3,fVar4,in_r8,in_r9,in_r10);
    zz_0007c30_(uVar8,dVar9,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar6 + 0xe0),
                extraout_r4_01,pfVar2,uVar3,fVar4,in_r8,in_r9,in_r10);
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 8016c118  FUN_8016c118 ====

void FUN_8016c118(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  int iVar2;
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
  uVar3 = gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar4,dVar5,
                             (float *)(param_1 + 0x114));
  iVar2 = param_1;
  for (iVar1 = 0; iVar1 < *(char *)(param_1 + 0x13); iVar1 = iVar1 + 1) {
    zz_00076d0_(uVar3,dVar4,dVar5,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar2 + 0xe0),
                (float *)(param_1 + 0x114),param_3,param_4,param_5,param_6,param_7,param_8);
    uVar3 = zz_00097b4_(*(int *)(iVar2 + 0xe0),0x45);
    iVar2 = iVar2 + 4;
  }
  return;
}



// ==== 8016c1a0  FUN_8016c1a0 ====

void FUN_8016c1a0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 extraout_r4;
  float *pfVar6;
  undefined4 *puVar7;
  short *psVar8;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  int iVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  undefined8 uVar14;
  
  fVar2 = FLOAT_8043ac24;
  *(float *)(param_9 + 100) = FLOAT_8043ac20;
  fVar3 = FLOAT_8043ac28;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar3;
  if (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_9 + 0x96)) == 0) {
    *(float *)(param_9 + 100) = *(float *)(param_9 + 100) + FLOAT_8043ac1c;
  }
  dVar12 = (double)FLOAT_8043aaf8;
  *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(param_9 + 100);
  *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 0x68);
  iVar11 = 0;
  *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_9 + 0x6c);
  dVar13 = (double)*(float *)(param_9 + 0x3c);
  *(float *)(param_9 + 0x3c) = (float)(dVar13 + dVar12);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
  *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x3c);
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x40);
  iVar10 = param_9;
  for (iVar9 = 0; iVar9 < *(char *)(param_9 + 0x13); iVar9 = iVar9 + 1) {
    puVar7 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar11);
    iVar5 = 2;
    if (iVar9 < 2) {
      iVar5 = iVar9;
    }
    psVar8 = &DAT_803501ac + iVar5 * 8;
    pfVar6 = (float *)(int)*psVar8;
    bVar1 = PTR_DAT_80433944[*(char *)(param_9 + 0x96) + 0x28];
    *(undefined2 *)(puVar7 + 8) = (&DAT_803501ae)[iVar5 * 8];
    uVar4 = (&DAT_803501b4)[iVar5 * 4];
    *puVar7 = (&DAT_803501b0)[iVar5 * 4];
    puVar7[1] = uVar4;
    puVar7[2] = (&DAT_803501b8)[iVar5 * 4];
    if (1 < iVar9) {
      pfVar6 = (float *)((int)pfVar6 + (bVar1 & 1));
    }
    dVar13 = (double)zz_0006fb4_(dVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_803bb384,*(int *)(iVar10 + 0xe0),(int)pfVar6,puVar7,psVar8,
                                 in_r8,in_r9,in_r10);
    if (iVar9 == 0) {
      uVar14 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,bVar1 & 1 ^ 0x80000000) -
                                          DOUBLE_8043aa90),param_2,param_3,param_4,param_5,param_6,
                           param_7,param_8,DAT_803bb384,*(int *)(iVar10 + 0xe0),pfVar6,puVar7,psVar8
                           ,in_r8,in_r9,in_r10);
      dVar13 = (double)zz_0007c30_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   *(int *)(iVar10 + 0xe0),extraout_r4,pfVar6,puVar7,psVar8,in_r8,
                                   in_r9,in_r10);
    }
    iVar11 = iVar11 + 0x24;
    iVar10 = iVar10 + 4;
  }
  zz_016c34c_(param_9,param_10);
  return;
}



// ==== 8016c34c  zz_016c34c_ ====

void zz_016c34c_(int param_1,int param_2)

{
  double dVar1;
  byte bVar2;
  float fVar3;
  size_t sVar4;
  undefined4 extraout_r4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  char local_48 [8];
  float local_40;
  undefined4 local_3c;
  undefined4 local_38;
  float local_34;
  undefined4 local_30;
  undefined4 local_2c;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  
  if (((int)(char)PTR_DAT_80433930[2] & 1 << (int)*(char *)(param_1 + 0x96)) == 0) {
    bVar2 = *(byte *)(param_2 + 0x3d) | *(byte *)(param_2 + 0x3f);
  }
  else {
    bVar2 = *(byte *)(param_2 + 0x3d);
  }
  if ((bVar2 & 4) == 0) {
    local_34 = *(float *)(param_1 + 0x38);
    local_30 = *(undefined4 *)(param_1 + 0x3c);
    local_2c = *(undefined4 *)(param_1 + 0x40);
  }
  else {
    local_34 = *(float *)(param_1 + 100);
    local_30 = *(undefined4 *)(param_1 + 0x68);
    local_2c = *(undefined4 *)(param_1 + 0x6c);
  }
  local_40 = local_34;
  local_3c = local_30;
  local_38 = local_2c;
  gnt4_PSVECSubtract_bl(&local_40,(float *)(param_1 + 0x20),&local_40);
  gnt4_PSQUATScale_bl((double)FLOAT_8043aa34,&local_40,&local_40);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),&local_40,(float *)(param_1 + 0x20));
  iVar9 = 999999;
  if (*(int *)(PTR_DAT_80433934 +
              ((byte)PTR_DAT_80433944[*(char *)(param_1 + 0x96) + 0x28] & 1) * 0x3c + 0x120) <
      999999) {
    iVar9 = *(int *)(PTR_DAT_80433934 +
                    ((byte)PTR_DAT_80433944[*(char *)(param_1 + 0x96) + 0x28] & 1) * 0x3c + 0x120);
  }
  sprintf(local_48,&DAT_8043ab38,iVar9);
  sVar4 = strlen(local_48);
  *(short *)(param_1 + 0x1c) = (short)sVar4;
  pcVar11 = local_48;
  iVar10 = 1;
  iVar9 = param_1;
  for (iVar8 = 0; dVar14 = DOUBLE_8043aa90, iVar8 < *(short *)(param_1 + 0x1c); iVar8 = iVar8 + 1) {
    pfVar5 = (float *)((iVar8 + 2) * 0x24);
    iVar6 = *(int *)(param_1 + 0x54);
    iVar7 = (int)*pcVar11;
    if ((0x2f < iVar7) && (iVar7 < 0x3a)) {
      uStack_24 = iVar10 - *(short *)(param_1 + 0x1c) ^ 0x80000000;
      uStack_1c = iVar7 - 0x30U ^ 0x80000000;
      local_28 = 0x43300000;
      local_20 = 0x43300000;
      fVar3 = FLOAT_8043ac2c * (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_8043aa90) *
              FLOAT_8043aab8;
      dVar13 = (double)fVar3;
      dVar1 = (double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8043aa90;
      *(float *)(iVar6 + (int)pfVar5) = fVar3;
      uVar12 = zz_00086b8_((double)(float)dVar1,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,
                           DAT_803bb384,*(int *)(iVar9 + 0xe8),pfVar5,iVar6,iVar7,in_r8,in_r9,in_r10
                          );
      zz_0007c30_(uVar12,dVar13,dVar14,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar9 + 0xe8),
                  extraout_r4,pfVar5,iVar6,iVar7,in_r8,in_r9,in_r10);
    }
    pcVar11 = pcVar11 + 1;
    iVar10 = iVar10 + 2;
    iVar9 = iVar9 + 4;
  }
  return;
}



// ==== 8016c544  FUN_8016c544 ====

void FUN_8016c544(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
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
  
  dVar7 = (double)*(float *)(param_1 + 0x24);
  dVar8 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar7,dVar8,(float *)(param_1 + 0x114));
  iVar3 = (int)*(char *)(param_1 + 0x13) + (int)*(short *)(param_1 + 0x1c) + -7;
  iVar5 = iVar3 * 0x24;
  iVar4 = param_1 + iVar3 * 4;
  for (; -1 < iVar3; iVar3 = iVar3 + -1) {
    pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
    pfVar1 = pfVar2;
    uVar6 = zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar2);
    zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),afStack_48,
                (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(iVar4 + 0xe0),(int)*(short *)(pfVar2 + 8));
    iVar5 = iVar5 + -0x24;
    iVar4 = iVar4 + -4;
  }
  return;
}



// ==== 8016c5f4  FUN_8016c5f4 ====

/* WARNING: Removing unreachable block (ram,0x8016c7d0) */
/* WARNING: Removing unreachable block (ram,0x8016c7c8) */
/* WARNING: Removing unreachable block (ram,0x8016c7c0) */
/* WARNING: Removing unreachable block (ram,0x8016c614) */
/* WARNING: Removing unreachable block (ram,0x8016c60c) */
/* WARNING: Removing unreachable block (ram,0x8016c604) */

void FUN_8016c5f4(double param_1,double param_2,double param_3,float *param_4,undefined4 *param_5,
                 undefined4 param_6,undefined1 param_7,short *param_8)

{
  short sVar1;
  short sVar2;
  size_t sVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  double dVar7;
  undefined1 local_88;
  undefined1 local_87;
  undefined1 local_86;
  undefined1 local_85;
  short local_84;
  short local_82;
  short local_80;
  short local_7e;
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  longlong local_58;
  
  DAT_803c1160 = zz_0098214_();
  DAT_803c1140 = &local_7c;
  DAT_803c1150 = &local_88;
  DAT_803c115c = &local_84;
  DAT_803c1144 = &local_64;
  dVar7 = (double)(float)(param_3 * (double)FLOAT_8043aab8);
  local_58 = (longlong)(int)((double)FLOAT_8043aaa4 * param_1);
  DAT_803c1168 = 0xf;
  DAT_803c1170 = 1;
  local_7c = *param_4;
  local_78 = param_4[1];
  local_74 = param_4[2];
  local_6c = local_78 + (float)((double)FLOAT_8043ac30 * param_2) / FLOAT_8043ac34;
  local_64 = *param_5;
  local_60 = param_5[1];
  local_5c = param_5[2];
  local_86 = 0xff;
  local_87 = 0xff;
  local_88 = 0xff;
  local_85 = (undefined1)(int)((double)FLOAT_8043aaa4 * param_1);
  DAT_803c1164 = param_6;
  DAT_803c1173 = param_7;
  local_68 = local_74;
  sVar3 = strlen((char *)param_8);
  for (iVar6 = 0; iVar6 < (int)(sVar3 >> 1); iVar6 = iVar6 + 1) {
    if (*param_8 != DAT_8043aab0) {
      iVar4 = zz_0097fbc_(*param_8);
      sVar5 = (short)iVar4;
      local_70 = (float)((double)local_7c + param_2);
      iVar4 = (int)sVar5 / 10 + ((int)sVar5 >> 0x1f);
      sVar1 = (short)iVar4;
      sVar2 = (short)(iVar4 >> 0x1f);
      local_82 = (sVar1 - sVar2) * 0x18;
      local_84 = (sVar5 + (sVar1 - sVar2) * -10) * 0x18;
      local_7e = local_82 + 0x18;
      local_80 = local_84 + 0x18;
      FUN_80051ef4(-0x7fc3eed0);
    }
    param_8 = param_8 + 1;
    local_7c = (float)((double)local_7c + dVar7);
  }
  return;
}



// ==== 8016c7ec  zz_016c7ec_ ====

void zz_016c7ec_(int param_1,undefined1 param_2,undefined4 param_3)

{
  FUN_8016c810((double)FLOAT_8043ac38,param_1,param_2,param_3);
  return;
}



// ==== 8016c810  FUN_8016c810 ====

/* WARNING: Removing unreachable block (ram,0x8016c908) */
/* WARNING: Removing unreachable block (ram,0x8016c820) */

void FUN_8016c810(double param_1,int param_2,undefined1 param_3,undefined4 param_4)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_2,3,8,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x58;
    puVar1[0x11] = param_3;
    *(code **)(puVar1 + 0xc) = FUN_8016c92c;
    *(undefined4 *)(puVar1 + 0x10c) = 0;
    *(float *)(puVar1 + 0xd8) = (float)param_1;
    *(undefined4 *)(puVar1 + 0x144) = param_4;
    *(int *)(puVar1 + 0x8c) = param_2;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_2 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_2 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_2 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_2 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_2 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_2 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_2 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_2 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_2 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_2 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_2 + 0xd0);
  }
  return;
}



// ==== 8016c92c  FUN_8016c92c ====

void FUN_8016c92c(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_80350280)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8016c97c  FUN_8016c97c ====

void FUN_8016c97c(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x90);
  *(undefined1 *)(param_1 + 0x18) = 1;
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x14;
  *(code **)(param_1 + 0x100) = FUN_80047f60;
  zz_0089100_(param_1,0,1);
  *(undefined1 *)(param_1 + 0x84) = 0x50;
  *(float *)(param_1 + 0xd4) =
       (float)((double)CONCAT44(0x43300000,(int)(char)(&DAT_803501e2)[iVar2] ^ 0x80000000) -
              DOUBLE_8043ac40);
  *(short *)(param_1 + 0x1e) = (short)(char)(&DAT_803501e3)[iVar2];
  if ('\0' < (char)(&DAT_803501f2)[iVar2]) {
    *(byte *)(param_1 + 0x2ac) = *(byte *)(param_1 + 0x2ac) | (&DAT_803501f2)[iVar2];
  }
  iVar1 = zz_008ac80_(param_1,(int)(char)(&DAT_803501e1)[iVar2]);
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar3 + (char)(&DAT_803501e0)[iVar2] * 0x30 + 0x8d4),
               (float *)(iVar2 + -0x7fcafe1c),(float *)(param_1 + 0x20));
    FUN_8016ca94(param_1);
  }
  return;
}



// ==== 8016ca94  FUN_8016ca94 ====

void FUN_8016ca94(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  bool bVar6;
  
  iVar5 = *(int *)(param_1 + 0x90);
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x14;
  if ((&DAT_803501f3)[iVar2] == '\0') {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar5 + (char)(&DAT_803501e0)[iVar2] * 0x30 + 0x8d4),
               (float *)(iVar2 + -0x7fcafe1c),(float *)(param_1 + 0x20));
  }
  iVar3 = zz_0083244_((float *)(param_1 + 0x20));
  fVar1 = FLOAT_8043ac38;
  if (iVar3 == 0) {
    *(undefined2 *)(param_1 + 0x272) = 0;
    if (fVar1 < *(float *)(param_1 + 0xd8)) {
      *(float *)(param_1 + 0xd8) = *(float *)(param_1 + 0xd8) - *(float *)(iVar5 + 0x1dc8);
      *(undefined2 *)(param_1 + 0x272) = 0xffff;
      return;
    }
    if ((*(byte *)(param_1 + 0x1d9) & 0x10) != 0) {
      if ((-1 < *(short *)(&DAT_803501f0 + iVar2)) &&
         (*(char *)(*(int *)(param_1 + 0x290) + 0x83) == '\0')) {
        zz_00f036c_(*(int *)(param_1 + 0x290),(int)*(short *)(&DAT_803501f0 + iVar2));
      }
      sVar4 = *(short *)(param_1 + 0x1e) + -1;
      *(short *)(param_1 + 0x1e) = sVar4;
      if (sVar4 < 1) goto LAB_8016cbb8;
    }
    if (((*(byte *)(param_1 + 0x1da) & 2) != 0) && ((char)(&DAT_803501f2)[iVar2] < '\0')) {
      **(undefined1 **)(param_1 + 0x144) = 1;
    }
    fVar1 = *(float *)(param_1 + 0xd4) - *(float *)(iVar5 + 0x1dc8);
    bVar6 = FLOAT_8043ac38 <= fVar1;
    *(float *)(param_1 + 0xd4) = fVar1;
    if (bVar6) {
      return;
    }
  }
LAB_8016cbb8:
  *(undefined1 *)(param_1 + 0x18) = 2;
  return;
}



// ==== 8016cbdc  FUN_8016cbdc ====

void FUN_8016cbdc(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  return;
}



// ==== 8016cc04  FUN_8016cc04 ====

void FUN_8016cc04(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8016cc24  zz_016cc24_ ====

void zz_016cc24_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x59;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_8016cd1c;
    *(code **)(puVar1 + 0x10c) = FUN_8016d4ac;
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



// ==== 8016cd1c  FUN_8016cd1c ====

void FUN_8016cd1c(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(char *)(param_1 + 0x18) < '\x02') {
    if (*(char *)(iVar1 + 0x18) < '\x02') {
      if ((*(short *)(iVar1 + 1000) == *(short *)(param_1 + 0x94)) &&
         ((*(uint *)(iVar1 + 0x5e0) & 0x1000000) == 0)) goto LAB_8016cd98;
    }
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
LAB_8016cd98:
  (*(code *)(&PTR_FUN_80350624)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8016cdd0  FUN_8016cdd0 ====

void FUN_8016cdd0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  undefined8 uVar6;
  float afStack_48 [3];
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  
  iVar3 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  iVar2 = -((int)(char)(&DAT_8035029e)[iVar3] >> 0x1f);
  if (iVar2 == 0) {
    iVar2 = zz_008ac80_(param_9,(int)(char)(&DAT_8035029e)[iVar3]);
  }
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    iVar5 = *(int *)(param_9 + 0x8c);
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined2 *)(param_9 + 0x272) = 0xffff;
    *(undefined1 *)(param_9 + 0x13) = 0;
    *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_8035029c + iVar3);
    *(undefined *)(param_9 + 0x17d) = (&DAT_8035029f)[iVar3];
    *(undefined *)(param_9 + 0x98) = (&DAT_803502a0)[iVar3];
    uVar1 = *(undefined4 *)(&DAT_803502ac + iVar3);
    *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803502a8 + iVar3);
    *(undefined4 *)(param_9 + 0x68) = uVar1;
    *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803502b0 + iVar3);
    iVar2 = (int)(char)(&DAT_803502a0)[iVar3];
    pfVar4 = (float *)(iVar5 + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4);
    local_30 = pfVar4[iVar2];
    local_2c = pfVar4[iVar2 + 4];
    local_28 = pfVar4[iVar2 + 8];
    if ((char)(&DAT_803502a1)[iVar3] < '\0') {
      gnt4_PSQUATScale_bl((double)FLOAT_8043ac48,afStack_48,afStack_48);
    }
    iVar2 = (int)(char)(&DAT_803502a2)[iVar3];
    local_3c = pfVar4[iVar2];
    local_38 = pfVar4[iVar2 + 4];
    local_34 = pfVar4[iVar2 + 8];
    if ((char)(&DAT_803502a3)[iVar3] < '\0') {
      gnt4_PSQUATScale_bl((double)FLOAT_8043ac48,&local_3c,&local_3c);
    }
    zz_0045ef4_((float *)(param_9 + 0x144),5,afStack_48,&local_3c);
    gnt4_PSMTXMultVec_bl(pfVar4,(float *)(param_9 + 100),&local_30);
    *(float *)(param_9 + 0x150) = local_30;
    *(float *)(param_9 + 0x160) = local_2c;
    *(float *)(param_9 + 0x170) = local_28;
    gnt4_PSMTXMultVec_bl
              ((float *)(param_9 + 0x144),(float *)&DAT_80350290,(float *)(param_9 + 0x20));
    *(undefined4 *)(param_9 + 0x2c) = *(undefined4 *)(param_9 + 0x20);
    *(undefined4 *)(param_9 + 0x30) = *(undefined4 *)(param_9 + 0x24);
    *(undefined4 *)(param_9 + 0x34) = *(undefined4 *)(param_9 + 0x28);
    *(code **)(param_9 + 0x100) = FUN_8016d398;
    uVar6 = zz_0089100_(param_9,0x41,1);
    zz_016d4d4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *(undefined1 *)(param_9 + 0x82) = 1;
    if ((&DAT_803502b4)[iVar3] == '\0') {
      zz_00f036c_(iVar5,0xb0);
    }
    else {
      zz_00f061c_((double)FLOAT_8043ac4c,iVar5,0xb0);
    }
  }
  return;
}



// ==== 8016cfe8  FUN_8016cfe8 ====

void FUN_8016cfe8(int param_1)

{
  *(float *)(param_1 + 0xd4) =
       *(float *)(param_1 + 0xd4) + *(float *)(*(int *)(param_1 + 0x8c) + 0x1dc8);
  (*(code *)(&PTR_FUN_80350634)[*(char *)(param_1 + 0x19)])();
  zz_0018fd8_((int *)(param_1 + 0x174),(int)*(float *)(param_1 + 0xd4),(float *)(param_1 + 0x58));
  return;
}



// ==== 8016d060  FUN_8016d060 ====

/* WARNING: Removing unreachable block (ram,0x8016d2b4) */
/* WARNING: Removing unreachable block (ram,0x8016d070) */

void FUN_8016d060(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  float fVar2;
  char cVar4;
  int iVar3;
  int iVar5;
  float *pfVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  
  uVar1 = DAT_80350294;
  iVar7 = *(int *)(param_9 + 0x8c);
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  *(undefined4 *)(param_9 + 0x20) = DAT_80350290;
  *(undefined4 *)(param_9 + 0x24) = uVar1;
  *(undefined4 *)(param_9 + 0x28) = DAT_80350298;
  dVar8 = (double)*(float *)(param_9 + 0xd4);
  if ((double)*(float *)(param_9 + 0xd8) <= dVar8) {
    cVar4 = *(char *)(param_9 + 0x13) + '\x01';
    *(char *)(param_9 + 0x13) = cVar4;
    fVar2 = FLOAT_8043ac50;
    if (cVar4 == '\x02') {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      *(undefined2 *)(param_9 + 0x272) = 0;
      *(float *)(param_9 + 0x28) = *(float *)(param_9 + 0x28) + fVar2;
      if ((&DAT_803502b4)[iVar5] == '\0') {
        dVar8 = (double)zz_00f036c_(iVar7,0xb1);
      }
      else {
        dVar8 = (double)zz_00f061c_((double)FLOAT_8043ac4c,iVar7,0xb1);
      }
    }
    zz_016d4d4_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  pfVar6 = (float *)(iVar7 + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4);
  if (*(char *)(param_9 + 0x13) == '\0') {
    iVar3 = (int)(char)(&DAT_803502a0)[iVar5];
    local_34 = pfVar6[iVar3];
    local_30 = pfVar6[iVar3 + 4];
    local_2c = pfVar6[iVar3 + 8];
    if ((char)(&DAT_803502a1)[iVar5] < '\0') {
      gnt4_PSQUATScale_bl((double)FLOAT_8043ac48,&local_34,&local_34);
    }
    gnt4_PSMTXMultVec_bl(pfVar6,(float *)(param_9 + 100),&local_58);
    gnt4_PSVECSubtract_bl((float *)(iVar7 + 0x518),&local_58,&local_4c);
    zz_006ec1c_(&local_34,&local_34);
    zz_006ec1c_(&local_4c,&local_4c);
    dVar8 = gnt4_PSQUATDotProduct_bl(&local_34,&local_4c);
    dVar9 = gnt4_cos_bl((double)*(float *)(&DAT_803502a4 + iVar5));
    if (dVar8 < (double)(float)dVar9) {
      local_4c = local_34;
      local_48 = local_30;
      local_44 = local_2c;
    }
    iVar7 = (int)(char)(&DAT_803502a2)[iVar5];
    local_40 = pfVar6[iVar7];
    local_3c = pfVar6[iVar7 + 4];
    local_38 = pfVar6[iVar7 + 8];
    if ((char)(&DAT_803502a3)[iVar5] < '\0') {
      gnt4_PSQUATScale_bl((double)FLOAT_8043ac48,&local_40,&local_40);
    }
    zz_0045ef4_((float *)(param_9 + 0x144),5,&local_4c,&local_40);
    *(float *)(param_9 + 0x150) = local_58;
    *(undefined4 *)(param_9 + 0x160) = local_54;
    *(undefined4 *)(param_9 + 0x170) = local_50;
  }
  gnt4_PSMTXMultVec_bl
            ((float *)(param_9 + 0x144),(float *)(param_9 + 0x20),(float *)(param_9 + 0x20));
  if (*(char *)(param_9 + 0x13) == '\x02') {
    iVar5 = zz_0084170_(param_9);
    *(char *)(param_9 + 0x17c) = (char)iVar5;
  }
  return;
}



// ==== 8016d2d0  FUN_8016d2d0 ====

void FUN_8016d2d0(int param_1)

{
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  zz_008aff0_(param_1);
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    if (*(char *)(param_1 + 0x17c) != '\0') {
      zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),*(undefined1 *)(param_1 + 0x17d));
    }
  }
  else {
    zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x2a0),*(undefined1 *)(param_1 + 0x17d));
  }
  return;
}



// ==== 8016d364  FUN_8016d364 ====

void FUN_8016d364(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8016d378  FUN_8016d378 ====

void FUN_8016d378(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8016d398  FUN_8016d398 ====

/* WARNING: Removing unreachable block (ram,0x8016d48c) */
/* WARNING: Removing unreachable block (ram,0x8016d3a8) */

void FUN_8016d398(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  double dVar2;
  undefined8 uVar3;
  double dVar4;
  float afStack_54 [2];
  float local_4c;
  float afStack_48 [12];
  
  dVar2 = gnt4_PSVECSquareDistance_bl((float *)(param_9 + 0x20),afStack_54);
  if ((double)FLOAT_8043ac54 < dVar2) {
    dVar4 = 1.0 / SQRT(dVar2);
    dVar4 = DOUBLE_8043ac58 * dVar4 * -(dVar2 * dVar4 * dVar4 - DOUBLE_8043ac60);
    dVar4 = DOUBLE_8043ac58 * dVar4 * -(dVar2 * dVar4 * dVar4 - DOUBLE_8043ac60);
    dVar2 = (double)(float)(dVar2 * DOUBLE_8043ac58 * dVar4 *
                                    -(dVar2 * dVar4 * dVar4 - DOUBLE_8043ac60));
    param_3 = DOUBLE_8043ac60;
    param_4 = DOUBLE_8043ac58;
  }
  dVar4 = (double)(float)(dVar2 / (double)(float)((double)FLOAT_8043ac68 *
                                                 (double)*(float *)(param_9 + 0xb4)));
  gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(param_9 + 0x58),afStack_54);
  if (*(char *)(param_9 + 0x13) == '\x02') {
    local_4c = (float)((double)local_4c * dVar4);
  }
  pfVar1 = afStack_54;
  uVar3 = zz_00456a0_((float *)(param_9 + 0x144),afStack_48,pfVar1);
  zz_00076d0_(uVar3,dVar2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0),
              afStack_48,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_9 + 0x20),(double)*(float *)(param_9 + 0x24),
                     (double)*(float *)(param_9 + 0x28),(float *)(param_9 + 0x114));
  return;
}



// ==== 8016d4ac  FUN_8016d4ac ====

void FUN_8016d4ac(int param_1)

{
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
  return;
}



// ==== 8016d4d4  zz_016d4d4_ ====

void zz_016d4d4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  double dVar1;
  undefined *puVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar3;
  undefined8 uVar4;
  
  dVar1 = DOUBLE_8043ac70;
  puVar2 = (&PTR_DAT_803505e0)[*(byte *)(param_9 + 0x11)];
  *(float *)(param_9 + 0xd4) = FLOAT_8043ac54;
  psVar3 = (short *)(puVar2 + *(char *)(param_9 + 0x13) * 8);
  *(float *)(param_9 + 0xd8) =
       (float)((double)CONCAT44(0x43300000,(int)psVar3[1] ^ 0x80000000) - dVar1);
  uVar4 = zz_0018f88_((int *)(param_9 + 0x174),*(int *)(psVar3 + 2),(float *)(param_9 + 0x58));
  zz_000726c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),(float *)(int)*psVar3,(int)*(char *)(param_9 + 0x88),in_r7,
              in_r8,in_r9,in_r10);
  return;
}



// ==== 8016d584  FUN_8016d584 ====

/* WARNING: Removing unreachable block (ram,0x8016d940) */
/* WARNING: Removing unreachable block (ram,0x8016d938) */
/* WARNING: Removing unreachable block (ram,0x8016d930) */
/* WARNING: Removing unreachable block (ram,0x8016d928) */
/* WARNING: Removing unreachable block (ram,0x8016d920) */
/* WARNING: Removing unreachable block (ram,0x8016d5b4) */
/* WARNING: Removing unreachable block (ram,0x8016d5ac) */
/* WARNING: Removing unreachable block (ram,0x8016d5a4) */
/* WARNING: Removing unreachable block (ram,0x8016d59c) */
/* WARNING: Removing unreachable block (ram,0x8016d594) */

void FUN_8016d584(int param_1,byte param_2,float *param_3)

{
  char cVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  undefined1 *unaff_r30;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  float local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  float afStack_b4 [3];
  float local_a8;
  undefined4 local_98;
  undefined4 local_88;
  undefined4 local_80;
  uint uStack_7c;
  undefined4 local_78;
  uint uStack_74;
  undefined4 local_70;
  uint uStack_6c;
  
  iVar2 = (uint)param_2 * 0x30;
  if ((char)(&DAT_80350662)[iVar2] < '\0') {
    pfVar3 = (float *)(param_1 + 0x114);
  }
  else {
    pfVar3 = (float *)(param_1 + (char)(&DAT_80350662)[iVar2] * 0x30 + 0x8d4);
  }
  gnt4_PSMTXMultVec_bl(pfVar3,(float *)(iVar2 + -0x7fcaf99c),&local_c0);
  gnt4_PSVECSubtract_bl(param_3,&local_c0,&local_d8);
  cVar1 = (&DAT_8035068b)[iVar2];
  if (cVar1 == '\x01') {
    local_cc = pfVar3[1];
    local_c8 = pfVar3[5];
    local_c4 = pfVar3[9];
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      local_cc = *pfVar3;
      local_c8 = pfVar3[4];
      local_c4 = pfVar3[8];
    }
  }
  else if (cVar1 < '\x03') {
    local_cc = pfVar3[2];
    local_c8 = pfVar3[6];
    local_c4 = pfVar3[10];
  }
  if ((&DAT_8035068c)[iVar2] == '\x01') {
    gnt4_PSQUATScale_bl((double)FLOAT_8043ac78,&local_cc,&local_cc);
  }
  zz_0045ef4_(afStack_b4,5,&local_d8,&local_cc);
  uStack_7c = (int)(char)(&DAT_80350687)[iVar2] ^ 0x80000000;
  local_80 = 0x43300000;
  local_a8 = local_c0;
  local_98 = local_bc;
  local_88 = local_b8;
  dVar8 = (double)(FLOAT_8043ac7c *
                  (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_8043ac90) * FLOAT_8043ac80
                  );
  uStack_74 = zz_00055fc_();
  uStack_74 = uStack_74 & 0xf;
  uStack_6c = (int)(char)(&DAT_80350686)[iVar2] ^ 0x80000000;
  local_78 = 0x43300000;
  dVar6 = (double)FLOAT_8043ac8c;
  dVar7 = (double)FLOAT_8043ac7c;
  dVar5 = (double)(FLOAT_8043ac84 *
                  ((float)((double)CONCAT44(0x43300000,uStack_74) - DOUBLE_8043ac98) *
                   FLOAT_8043ac80 +
                  FLOAT_8043ac88 / (float)((double)CONCAT44(0x43300000,uStack_6c) - DOUBLE_8043ac90)
                  ));
  dVar9 = DOUBLE_8043ac90;
  for (iVar4 = 0; local_70 = 0x43300000, iVar4 < (char)(&DAT_80350688)[iVar2]; iVar4 = iVar4 + 1) {
    unaff_r30 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,0,1);
    if (unaff_r30 != (undefined1 *)0x0) {
      *unaff_r30 = 1;
      unaff_r30[0x10] = 0;
      unaff_r30[0x11] = param_2;
      *(code **)(unaff_r30 + 0xc) = FUN_8016d95c;
      *(code **)(unaff_r30 + 0x10c) = FUN_8016dd48;
      *(int *)(unaff_r30 + 0x8c) = param_1;
      *(undefined4 *)(unaff_r30 + 0x90) = *(undefined4 *)(param_1 + 0x90);
      *(undefined2 *)(unaff_r30 + 0x94) = *(undefined2 *)(param_1 + 0x94);
      unaff_r30[0x96] = *(undefined1 *)(param_1 + 0x96);
      unaff_r30[0x97] = *(undefined1 *)(param_1 + 0x97);
      unaff_r30[0x88] = *(undefined1 *)(param_1 + 0x88);
      *(undefined4 *)(unaff_r30 + 200) = *(undefined4 *)(param_1 + 200);
      *(undefined4 *)(unaff_r30 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
      *(undefined4 *)(unaff_r30 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
      *(undefined4 *)(unaff_r30 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(unaff_r30 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(unaff_r30 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(unaff_r30 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(unaff_r30 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
      *(undefined4 *)(unaff_r30 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
      unaff_r30[0xd0] = *(undefined1 *)(param_1 + 0xd0);
      gnt4_PSQUATScale_bl((double)*(float *)(unaff_r30 + 0xb4),(float *)(iVar2 + -0x7fcaf988),
                          (float *)(unaff_r30 + 0x58));
      *(float *)(unaff_r30 + 0x20) = local_c0;
      *(undefined4 *)(unaff_r30 + 0x24) = local_bc;
      *(undefined4 *)(unaff_r30 + 0x28) = local_b8;
      *(float *)(unaff_r30 + 0x9c) = local_cc;
      *(float *)(unaff_r30 + 0xa0) = local_c8;
      *(float *)(unaff_r30 + 0xa4) = local_c4;
      *(float *)(unaff_r30 + 0x38) = local_d8;
      *(undefined4 *)(unaff_r30 + 0x3c) = local_d4;
      *(undefined4 *)(unaff_r30 + 0x40) = local_d0;
      gnt4_PSMTXCopy_bl(afStack_b4,(float *)(unaff_r30 + 0x114));
      *(float *)(unaff_r30 + 0x144) = (float)dVar8;
      *(float *)(unaff_r30 + 0x148) = (float)dVar5;
    }
    uStack_6c = (int)(char)(&DAT_80350688)[iVar2] ^ 0x80000000;
    dVar5 = (double)(float)(dVar5 + (double)(float)(dVar6 / (double)(float)((double)CONCAT44(
                                                  0x43300000,uStack_6c) - dVar9)));
    if (dVar7 < dVar5) {
      dVar5 = (double)(float)(dVar5 - dVar6);
    }
  }
  zz_00aedc0_(param_1,(float *)(unaff_r30 + 0x114),(int)(char)(&DAT_8035068d)[iVar2],unaff_r30[0x88]
             );
  zz_00f036c_(param_1,(uint)(byte)(&DAT_8035068f)[iVar2]);
  return;
}



// ==== 8016d95c  FUN_8016d95c ====

void FUN_8016d95c(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_803507e0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8016d9ac  FUN_8016d9ac ====

void FUN_8016d9ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  float afStack_38 [12];
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar2 = (uint)*(byte *)(param_9 + 0x11) * 0x30;
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_80350684 + iVar2);
  uVar3 = zz_00055fc_();
  fVar1 = *(float *)(&DAT_80350640 + (uVar3 & 7) * 4);
  *(float *)(param_9 + 0x44) = fVar1 * *(float *)(&DAT_80350670 + iVar2);
  *(float *)(param_9 + 0x4c) = fVar1 * *(float *)(&DAT_80350674 + iVar2);
  *(code **)(param_9 + 0x100) = zz_0048288_;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  *(undefined1 *)(param_9 + 0x98) = 5;
  gnt4_PSMTXRotRad_bl((double)*(float *)(param_9 + 0x148),afStack_38,0x7a);
  gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_38,(float *)(param_9 + 0x114));
  gnt4_PSMTXRotRad_bl((double)*(float *)(param_9 + 0x144),afStack_38,0x78);
  gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_38,(float *)(param_9 + 0x114));
  *(undefined4 *)(param_9 + 0x9c) = *(undefined4 *)(param_9 + 0x118);
  *(undefined4 *)(param_9 + 0xa0) = *(undefined4 *)(param_9 + 0x128);
  *(undefined4 *)(param_9 + 0xa4) = *(undefined4 *)(param_9 + 0x138);
  *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(param_9 + 0x11c);
  *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(param_9 + 300);
  *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(param_9 + 0x13c);
  zz_006ebb4_((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  uVar5 = gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x44),(float *)(param_9 + 0x38),
                              (float *)(param_9 + 0x38));
  iVar4 = zz_008ac80_(param_9,(int)(char)(&DAT_80350663)[iVar2]);
  if (iVar4 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    zz_000726c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(float *)(int)*(short *)(&DAT_80350660 + iVar2),
                (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 8016db34  FUN_8016db34 ====

void FUN_8016db34(int param_1)

{
  byte bVar1;
  float fVar2;
  int iVar3;
  undefined4 auStack_28 [3];
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  if (((0 < *(short *)(param_1 + 0x1c)) &&
      (iVar3 = zz_0083244_((float *)(param_1 + 0x20)), iVar3 == 0)) &&
     (*(char *)(param_1 + 0x1d9) == '\0')) {
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
    *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x1400;
    bVar1 = *(byte *)(param_1 + 0x11);
    zz_006ebb4_((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                        (float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x20),(float *)(param_1 + 0x20));
    fVar2 = FLOAT_8043aca0;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x4c);
    if (*(float *)(param_1 + 0x44) < fVar2) {
      *(float *)(param_1 + 0x44) = fVar2;
    }
    zz_00833ec_(param_1);
    zz_0083524_(param_1);
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),
                        (float *)((uint)bVar1 * 0x30 + -0x7fcaf988),(float *)(param_1 + 0x58));
    iVar3 = zz_0083714_(param_1);
    if (iVar3 == 0) {
      iVar3 = zz_003ecb8_((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),&local_1c,auStack_28);
      if (iVar3 == 0) {
        return;
      }
      *(float *)(param_1 + 0x20) = local_1c;
      *(undefined4 *)(param_1 + 0x24) = local_18;
      *(undefined4 *)(param_1 + 0x28) = local_14;
      FUN_8001b9ac((double)*(float *)(param_1 + 0xb4),&local_1c,auStack_28);
      zz_0019550_(param_1,&local_1c,0);
      *(undefined1 *)(param_1 + 0x18) = 2;
      return;
    }
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  return;
}



// ==== 8016dcc0  FUN_8016dcc0 ====

void FUN_8016dcc0(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043aca8;
  *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) * FLOAT_8043aca4;
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x58);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x58);
  if (*(float *)(param_1 + 0x58) < fVar1) {
    *(undefined1 *)(param_1 + 0x18) = 3;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 8016dd28  FUN_8016dd28 ====

void FUN_8016dd28(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8016dd48  FUN_8016dd48 ====

/* WARNING: Removing unreachable block (ram,0x8016dd5c) */

void FUN_8016dd48(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  undefined8 uVar2;
  float afStack_38 [13];
  
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043acac *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x74) *
                                             0x3ff0000000000000)),afStack_38,0x7a);
  pfVar1 = afStack_38;
  uVar2 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 8016ddb0  zz_016ddb0_ ====

void zz_016ddb0_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 6;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_8016dea8;
    *(code **)(puVar1 + 0x10c) = FUN_8016e39c;
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



// ==== 8016dea8  FUN_8016dea8 ====

void FUN_8016dea8(int param_1)

{
  zz_00840b8_(param_1);
  (*(code *)(&PTR_FUN_80350970)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8016def8  FUN_8016def8 ====

void FUN_8016def8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar5;
  int iVar6;
  undefined8 uVar7;
  
  pfVar5 = (float *)(param_9 + 0x144);
  iVar6 = *(int *)(param_9 + 0x8c);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x3c;
  *(undefined2 *)(param_9 + 0x1c) = 600;
  iVar2 = -((int)(char)(&DAT_803507f3)[iVar4] >> 0x1f);
  if (iVar2 == 0) {
    iVar2 = zz_008ac80_(param_9,(int)(char)(&DAT_803507f3)[iVar4]);
  }
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    gnt4_PSMTXCopy_bl((float *)(iVar6 + (char)(&DAT_803507f2)[iVar4] * 0x30 + 0x8d4),pfVar5);
    gnt4_PSMTXMultVec_bl(pfVar5,(float *)(iVar4 + -0x7fcaf7fc),(float *)(param_9 + 0x20));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8035081c + iVar4);
    *(undefined4 *)(param_9 + 0x4c) = *(undefined4 *)(&DAT_80350820 + iVar4);
    *(float *)(param_9 + 0xb4) = *(float *)(&DAT_80350800 + iVar4) * *(float *)(iVar6 + 0xb4);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_803507f6 + iVar4);
    *(undefined2 *)(param_9 + 0x72) = 0;
    *(undefined2 *)(param_9 + 0x70) = 0;
    uVar3 = zz_00055fc_();
    *(short *)(param_9 + 0x74) = (short)(uVar3 << 8);
    uVar1 = *(undefined4 *)(param_9 + 0xb4);
    *(undefined4 *)(param_9 + 0xc0) = uVar1;
    *(undefined4 *)(param_9 + 0x60) = uVar1;
    *(undefined4 *)(param_9 + 0x5c) = uVar1;
    *(undefined4 *)(param_9 + 0x58) = uVar1;
    *(undefined4 *)(param_9 + 0x188) = *(undefined4 *)(&DAT_80350828 + iVar4);
    zz_0083e64_(param_9,pfVar5,(float *)(iVar4 + -0x7fcaf7f0));
    gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x44),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    if (-1 < *(short *)(&DAT_803507f4 + iVar4)) {
      zz_016e3dc_(param_9);
      zz_00aedc0_(iVar6,(float *)(param_9 + 0x114),(int)*(short *)(&DAT_803507f4 + iVar4),
                  *(undefined1 *)(param_9 + 0x88));
    }
    *(code **)(param_9 + 0x100) = zz_016e3dc_;
    uVar7 = zz_0089100_(param_9,1,1);
    iVar2 = zz_0006f78_(*(int *)(param_9 + 0x90));
    zz_000726c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                *(int *)(param_9 + 0xe0),(float *)(uint)(byte)(&DAT_803507f0)[iVar4],
                (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    if (*(char *)(param_9 + 0x11) == '\0') {
      zz_00f036c_(param_9,0xec);
    }
  }
  return;
}



// ==== 8016e0c0  FUN_8016e0c0 ====

void FUN_8016e0c0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar7;
  
  iVar6 = (uint)*(byte *)(param_9 + 0x11) * 0x3c;
  zz_016e478_(param_9);
  FUN_80083874((double)FLOAT_8043acb0,param_9);
  *(float *)(param_9 + 0x44) = *(float *)(param_9 + 0x44) + *(float *)(param_9 + 0x4c);
  if (*(float *)(param_9 + 0x188) < *(float *)(param_9 + 0x44)) {
    *(float *)(param_9 + 0x44) = *(float *)(param_9 + 0x188);
  }
  if (*(float *)(param_9 + 0x44) < *(float *)(&DAT_80350824 + iVar6)) {
    *(float *)(param_9 + 0x44) = *(float *)(&DAT_80350824 + iVar6);
  }
  *(short *)(param_9 + 0x74) = *(short *)(param_9 + 0x74) + 0x2000;
  uVar1 = *(undefined4 *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0xc0) = uVar1;
  *(undefined4 *)(param_9 + 0x60) = uVar1;
  *(undefined4 *)(param_9 + 0x5c) = uVar1;
  *(undefined4 *)(param_9 + 0x58) = uVar1;
  iVar3 = zz_0083244_((float *)(param_9 + 0x20));
  iVar4 = zz_0083714_(param_9);
  sVar5 = *(short *)(param_9 + 0x1c) + -1;
  *(short *)(param_9 + 0x1c) = sVar5;
  uVar2 = countLeadingZeros((int)sVar5);
  if ((iVar3 == 0 && iVar4 == 0) && ((1 << (uVar2 & 0x1f) | 1U >> 0x20 - (uVar2 & 0x1f)) & 1) == 0)
  {
    if ((*(char *)(param_9 + 0x1d9) != '\0') || (iVar6 = zz_0084170_(param_9), iVar6 != 0)) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      *(undefined1 *)(param_9 + 0x19) = 1;
      zz_008aff0_(param_9);
    }
  }
  else {
    iVar3 = (int)(char)(&DAT_803507f1)[iVar6];
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x19) = 0;
    zz_008aff0_(param_9);
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined2 *)(param_9 + 0x1e) = *(undefined2 *)(&DAT_80350966 + iVar3 * 0xc);
    zz_0018f88_((int *)(param_9 + 0x174),(int)(&PTR_DAT_80350968)[iVar3 * 3],
                (float *)(param_9 + 0x58));
    zz_0019338_((int *)(param_9 + 0x17c),(int)(&PTR_DAT_8035096c)[iVar3 * 3],
                (float *)(param_9 + 0x184));
    uVar7 = gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(param_9 + 0x58),
                                (float *)(param_9 + 0x58));
    iVar6 = zz_0006f78_(*(int *)(param_9 + 0x90));
    zz_000726c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                *(int *)(param_9 + 0xe0),(float *)(int)*(short *)(&DAT_80350964 + iVar3 * 0xc),
                (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
    zz_0007cac_((double)*(float *)(param_9 + 0x184),*(int *)(param_9 + 0xe0));
  }
  zz_00833ec_(param_9);
  zz_0083610_(param_9,(float *)(param_9 + 0x188));
  return;
}



// ==== 8016e29c  FUN_8016e29c ====

void FUN_8016e29c(int param_1)

{
  (**(code **)(&DAT_80434780 + *(char *)(param_1 + 0x19) * 4))();
  return;
}



// ==== 8016e2d4  FUN_8016e2d4 ====

void FUN_8016e2d4(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (sVar1 < *(short *)(param_1 + 0x1e)) {
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x2000;
    zz_0018fd8_((int *)(param_1 + 0x174),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x58));
    zz_0019370_((int *)(param_1 + 0x17c),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x184))
    ;
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(param_1 + 0x58),
                        (float *)(param_1 + 0x58));
    zz_0007cac_((double)*(float *)(param_1 + 0x184),*(int *)(param_1 + 0xe0));
  }
  else {
    zz_016e368_(param_1);
  }
  return;
}



// ==== 8016e368  zz_016e368_ ====

void zz_016e368_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8016e37c  FUN_8016e37c ====

void FUN_8016e37c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8016e39c  FUN_8016e39c ====

void FUN_8016e39c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 8016e3dc  zz_016e3dc_ ====

void zz_016e3dc_(int param_1)

{
  bool bVar1;
  
  bVar1 = zz_0045ef4_((float *)(param_1 + 0x114),5,param_1 + 0x38,&DAT_802b0cb4);
  if (bVar1) {
    zz_0045ef4_((float *)(param_1 + 0x114),4,param_1 + 0x38,&DAT_802b0ca8);
  }
  zz_00457d4_('z',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x74));
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  return;
}



// ==== 8016e478  zz_016e478_ ====

void zz_016e478_(int param_1)

{
  uint uVar1;
  char cVar3;
  int iVar2;
  uint uVar4;
  bool bVar5;
  double dVar6;
  double dVar7;
  float afStack_24 [5];
  
  uVar4 = *(uint *)(param_1 + 200);
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  bVar5 = false;
  if ((int)(-uVar4 | uVar4) < 0) {
    cVar3 = *(char *)(param_1 + 0x1cb) + -1;
    *(char *)(param_1 + 0x1cb) = cVar3;
    uVar1 = countLeadingZeros((int)cVar3);
    bVar5 = false;
    if (((1 << (uVar1 & 0x1f) | 1U >> 0x20 - (uVar1 & 0x1f)) & 1) != 0) {
      iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x3c;
      *(char *)(param_1 + 0x1cb) = (char)*(undefined2 *)(&DAT_803507f6 + iVar2);
      *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(uVar4 + 100);
      *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(uVar4 + 0x68);
      *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(uVar4 + 0x6c);
      gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x144),(float *)(iVar2 + -0x7fcaf7f0),afStack_24);
      dVar6 = gnt4_PSVECSquareDistance_bl(afStack_24,(float *)(param_1 + 0x20));
      if ((double)FLOAT_8043acb0 < dVar6) {
        dVar7 = 1.0 / SQRT(dVar6);
        dVar7 = DOUBLE_8043acb8 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_8043acc0);
        dVar7 = DOUBLE_8043acb8 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_8043acc0);
        dVar6 = (double)(float)(dVar6 * DOUBLE_8043acb8 * dVar7 *
                                        -(dVar6 * dVar7 * dVar7 - DOUBLE_8043acc0));
      }
      bVar5 = (double)*(float *)(&DAT_803507fc + iVar2) < dVar6;
      if (bVar5) {
        zz_006c440_((double)*(float *)(&DAT_803507f8 + iVar2),param_1,afStack_24);
        zz_00833a4_(param_1);
      }
      else {
        *(undefined4 *)(param_1 + 200) = 0;
      }
    }
  }
  if (!bVar5) {
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  }
  return;
}



// ==== 8016e608  FUN_8016e608 ====

void FUN_8016e608(void)

{
  PTR_DAT_80433934[0x45] = 0;
  (*(code *)(&PTR_FUN_80351650)[*(short *)PTR_DAT_80433944])();
  return;
}



// ==== 8016e650  zz_016e650_ ====

void zz_016e650_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined8 extraout_f1;
  undefined8 uVar1;
  
  zz_01978d0_();
  uVar1 = zz_0008b58_();
  uVar1 = zz_0008924_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14
                      ,param_15,param_16);
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,extraout_r4,
                      param_11,param_12,param_13,param_14,param_15,param_16);
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,extraout_r4_00
                      ,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,extraout_r4_01,
              param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00f07c4_();
  return;
}



// ==== 8016e694  zz_016e694_ ====

int zz_016e694_(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  *(char *)(param_1 + 0x3c) = (char)param_2;
  *(undefined2 *)(param_1 + 10) = *(undefined2 *)(param_1 + 8);
  if ((&DAT_803c7291)[param_2 * 0x20] == '\0') {
    *(undefined2 *)(param_1 + 8) = 0;
  }
  else {
    *(ushort *)(param_1 + 8) = (ushort)(&DAT_803c727c)[param_2 * 8] & 0xf7f;
    *(ushort *)(param_1 + 8) =
         *(ushort *)(param_1 + 8) | (ushort)((uint)(&DAT_803c727c)[param_2 * 8] >> 0x10) & 0xf;
    *(ushort *)(param_1 + 8) =
         *(ushort *)(param_1 + 8) | (ushort)((uint)(&DAT_803c727c)[param_2 * 8] >> 8) & 0xf000;
    *(ushort *)(param_1 + 8) =
         *(ushort *)(param_1 + 8) | (ushort)((uint)(&DAT_803c727c)[param_2 * 8] >> 5) & 0x80;
  }
  iVar2 = 0;
  *(ushort *)(param_1 + 0xe) = *(ushort *)(param_1 + 8) & ~*(ushort *)(param_1 + 10);
  *(undefined2 *)(param_1 + 0xc) = *(undefined2 *)(param_1 + 0xe);
  iVar3 = 8;
  do {
    if (((uint)*(ushort *)(param_1 + 8) & 1 << iVar2) == 0) {
      *(undefined1 *)(param_1 + iVar2 + 0x10) = 0;
    }
    else {
      *(char *)(param_1 + iVar2 + 0x10) = *(char *)(param_1 + iVar2 + 0x10) + '\x01';
    }
    if (0x1f < *(byte *)(param_1 + iVar2 + 0x10)) {
      *(ushort *)(param_1 + 0xc) = *(ushort *)(param_1 + 0xc) | (ushort)(1 << iVar2);
      *(undefined1 *)(param_1 + iVar2 + 0x10) = 0x1b;
    }
    uVar1 = 1 << iVar2 + 1;
    if ((*(ushort *)(param_1 + 8) & uVar1) == 0) {
      *(undefined1 *)(param_1 + iVar2 + 0x11) = 0;
    }
    else {
      *(char *)(param_1 + iVar2 + 0x11) = *(char *)(param_1 + iVar2 + 0x11) + '\x01';
    }
    if (0x1f < *(byte *)(param_1 + iVar2 + 0x11)) {
      *(ushort *)(param_1 + 0xc) = *(ushort *)(param_1 + 0xc) | (ushort)uVar1;
      *(undefined1 *)(param_1 + iVar2 + 0x11) = 0x1b;
    }
    iVar2 = iVar2 + 2;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return (int)(char)(&DAT_803c7291)[param_2 * 0x20];
}



// ==== 8016e7fc  zz_016e7fc_ ====

void zz_016e7fc_(void)

{
  DAT_803bfde0 = DAT_80436238 + DAT_80351660;
  DAT_803bfe00 = DAT_80436238 + DAT_80351664;
  DAT_803bfde4 = DAT_80436238 + DAT_80351668;
  DAT_803bfe04 = DAT_80436238 + DAT_8035166c;
  DAT_803bfde8 = DAT_80436238 + DAT_80351670;
  DAT_803bfe08 = DAT_80436238 + DAT_80351674;
  DAT_803bfdec = DAT_80436238 + DAT_80351678;
  DAT_803bfe0c = DAT_80436238 + DAT_8035167c;
  DAT_803bfdf0 = DAT_80436238 + DAT_80351680;
  DAT_803bfe10 = DAT_80436238 + DAT_80351684;
  DAT_803bfdf4 = DAT_80436238 + DAT_80351688;
  DAT_803bfe14 = DAT_80436238 + DAT_8035168c;
  DAT_803bfdf8 = DAT_80436238 + DAT_80351690;
  DAT_803bfe18 = DAT_80436238 + DAT_80351694;
  DAT_803bfdfc = DAT_80436238 + DAT_80351698;
  DAT_803bfe1c = DAT_80436238 + DAT_8035169c;
  return;
}



// ==== 8016e8ec  FUN_8016e8ec ====

undefined4 FUN_8016e8ec(void)

{
  (*(code *)(&PTR_FUN_80434790)[*(short *)(PTR_DAT_80433944 + 2)])();
  return 0;
}



// ==== 8016e928  FUN_8016e928 ====

void FUN_8016e928(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined8 uVar1;
  
  *(short *)(PTR_DAT_80433944 + 2) = *(short *)(PTR_DAT_80433944 + 2) + 1;
  zz_0197854_(3);
  zz_0088398_(DAT_80436238 + 0xfe800,0x100000,3);
  uVar1 = zz_016e7fc_();
  zz_00449e8_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1);
  return;
}



// ==== 8016e980  FUN_8016e980 ====

void FUN_8016e980(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined *puVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 extraout_f1;
  undefined8 uVar5;
  
  iVar1 = zz_000a3c4_();
  if (iVar1 == 0) {
    *(undefined2 *)PTR_DAT_80433944 = 1;
    puVar4 = PTR_DAT_80433944;
    puVar2 = (undefined *)0xc0;
    uVar3 = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 2) = 0;
    zz_002a5f4_(0x40,0x80,0xc0,0);
    uVar5 = zz_008c3a0_(2);
    uVar5 = zz_004370c_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar5 >> 0x20),(int)uVar5,puVar2,uVar3,puVar4,in_r8,in_r9,
                        in_r10);
    uVar5 = zz_0008a94_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                        extraout_r4,puVar2,uVar3,puVar4,in_r8,in_r9,in_r10);
    zz_007fd6c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_016e650_,0,puVar2,
                uVar3,puVar4,in_r8,in_r9,in_r10);
    uVar5 = FUN_801749e4();
    zz_00e99c8_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,DAT_8031a0c8,uVar3
                ,puVar4,in_r8,in_r9,in_r10);
    if (PTR_DAT_80433944[0x93] == '\0') {
      uVar5 = zz_0027aac_(0xe0e0e000,0x1e,0);
    }
    else {
      uVar5 = zz_0027aac_(0,0x1e,0);
    }
    zz_00439a0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2);
  }
  return;
}



// ==== 8016ea60  FUN_8016ea60 ====

undefined4
FUN_8016ea60(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
            double param_6,double param_7,double param_8)

{
  int iVar1;
  float *pfVar2;
  float *pfVar3;
  undefined4 in_r8;
  undefined4 *in_r9;
  undefined4 *in_r10;
  int iVar4;
  int iVar5;
  undefined8 extraout_f1;
  undefined8 uVar6;
  
  iVar5 = 0;
  *(short *)(PTR_DAT_80433944 + 8) = *(short *)(PTR_DAT_80433944 + 8) + 1;
  PTR_DAT_80433944[0x14] = 0;
  for (iVar4 = 0; iVar4 < 4; iVar4 = iVar4 + 1) {
    iVar1 = zz_016e694_((int)(PTR_DAT_80433944 + iVar5 + 0x100),iVar4);
    if (iVar1 != 0) {
      PTR_DAT_80433944[0x14] = PTR_DAT_80433944[0x14] | (byte)(1 << iVar4);
    }
    iVar5 = iVar5 + 0x80;
  }
  PTR_DAT_80433944[0x15] = 0;
  for (iVar5 = 0; pfVar3 = (float *)PTR_DAT_80433944, iVar5 < 2; iVar5 = iVar5 + 1) {
    iVar4 = zz_008e340_(iVar5);
    if (iVar4 != 0) {
      PTR_DAT_80433944[0x15] = PTR_DAT_80433944[0x15] | (byte)(1 << iVar5);
    }
  }
  iVar4 = 0;
  iVar5 = 4;
  PTR_DAT_80433944[0x16] = PTR_DAT_80433944[0x16] | PTR_DAT_80433944[0x14];
  PTR_DAT_80433944[0x17] = 0;
  do {
    pfVar2 = (float *)PTR_DAT_80433944;
    if (((uint)(byte)PTR_DAT_80433944[0x16] & 1 << iVar4) != 0) {
      PTR_DAT_80433944[0x17] = PTR_DAT_80433944[0x17] + '\x01';
    }
    iVar4 = iVar4 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  uVar6 = (*(code *)(&PTR_FUN_803516a0)[*(short *)(PTR_DAT_80433944 + 2)])();
  zz_0174adc_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar6 >> 0x20),(int)uVar6,pfVar2,pfVar3,iVar4,in_r8,in_r9,in_r10);
  zz_0174ce8_();
  return 0;
}



// ==== 8016ebcc  FUN_8016ebcc ====

void FUN_8016ebcc(void)

{
  (*(code *)(&PTR_FUN_80434798)[*(short *)(PTR_DAT_80433944 + 4)])();
  return;
}



// ==== 8016ec04  FUN_8016ec04 ====

void FUN_8016ec04(void)

{
  float fVar1;
  int iVar2;
  char *pcVar3;
  
  pcVar3 = &DAT_80351118;
  *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
  while( true ) {
    fVar1 = FLOAT_8043acd8;
    if (*pcVar3 < '\0') break;
    zz_011c648_((int)*pcVar3,pcVar3[1]);
    pcVar3 = pcVar3 + 2;
  }
  iVar2 = 0;
  PTR_DAT_80433930[3] = 0;
  PTR_DAT_80433930[2] = 0;
  *(float *)(PTR_DAT_80433944 + 0x1c) = fVar1;
  PTR_DAT_80433944[0x2d] = 0;
  PTR_DAT_80433944[0x2e] = 0;
  PTR_DAT_80433944[0x6e] = 0;
  PTR_DAT_80433944[0x6f] = 0;
  PTR_DAT_80433944[0x6c] = 0;
  while( true ) {
    if (7 < iVar2) break;
    if (((uint)(byte)PTR_DAT_80433944[0x91] & 1 << iVar2) == 0) {
      iVar2 = 8;
    }
    else {
      PTR_DAT_80433944[0x6c] = (char)iVar2 + '\x01';
    }
    iVar2 = iVar2 + 1;
  }
  PTR_DAT_80433944[0x1a] = 1;
  zz_016fae8_();
  zz_016ecf8_();
  return;
}



// ==== 8016ecf8  zz_016ecf8_ ====

void zz_016ecf8_(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    if (PTR_DAT_80433944[0x93] == '\0') {
      *(undefined2 *)(PTR_DAT_80433944 + 2) = 1;
    }
    else {
      *(undefined2 *)(PTR_DAT_80433944 + 2) = 2;
    }
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    zz_0027c1c_();
  }
  return;
}



// ==== 8016ed54  FUN_8016ed54 ====

void FUN_8016ed54(void)

{
  zz_016fae8_();
  (*(code *)(&PTR_FUN_803516c0)[*(short *)(PTR_DAT_80433944 + 4)])();
  return;
}



// ==== 8016ed94  FUN_8016ed94 ====

void FUN_8016ed94(void)

{
  *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
  PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] | 1;
  *(undefined2 *)(PTR_DAT_80433944 + 10) = 0xf;
  PTR_DAT_80433944[0x1a] = 0;
  zz_016edec_();
  return;
}



// ==== 8016edec  zz_016edec_ ====

void zz_016edec_(void)

{
  bool bVar1;
  
  bVar1 = zz_0174464_((double)(float)((double)CONCAT44(0x43300000,
                                                       (int)*(short *)(PTR_DAT_80433944 + 10) ^
                                                       0x80000000) - DOUBLE_8043ace0));
  if (bVar1) {
    *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
    PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] | 1;
    PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] & 0xfe;
  }
  return;
}



// ==== 8016ee68  FUN_8016ee68 ====

/* WARNING: Removing unreachable block (ram,0x8016ee9c) */
/* WARNING: Removing unreachable block (ram,0x8016eee4) */

void FUN_8016ee68(void)

{
  ushort *puVar1;
  undefined *puVar2;
  ushort uVar3;
  int iVar4;
  
  uVar3 = 0;
  iVar4 = 4;
  puVar2 = PTR_DAT_80433944;
  do {
    puVar1 = (ushort *)(puVar2 + 0x10e);
    puVar2 = puVar2 + 0x80;
    uVar3 = uVar3 | *puVar1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  if ((uVar3 & 0x200) == 0) {
    if ((uVar3 & 0x100) == 0) {
      if ((uVar3 & 0x80) != 0) {
        *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 2;
        *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 4;
        PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xfe;
        PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] | 1;
        zz_00f0468_(0,0x7a,0);
      }
    }
    else if ((PTR_DAT_80433944[0x15] & 1) == 0) {
      zz_00f0468_(0,0x7d,0);
    }
    else {
      *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
      *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
      *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 10;
      zz_00f0468_(0,0x7a,0);
      PTR_DAT_80433944[0x6d] = 1;
      zz_011c648_(5,0);
    }
  }
  else {
    *(undefined2 *)(PTR_DAT_80433944 + 0x10) = *(undefined2 *)(PTR_DAT_80433944 + 2);
    *(undefined2 *)(PTR_DAT_80433944 + 0x12) = *(undefined2 *)(PTR_DAT_80433944 + 4);
    *(undefined2 *)(PTR_DAT_80433944 + 2) = 7;
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 8016f020  FUN_8016f020 ====

void FUN_8016f020(void)

{
  zz_0174464_((double)(float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(PTR_DAT_80433944 + 10) ^ 0x80000000)
                             - DOUBLE_8043ace0));
  (*(code *)(&PTR_FUN_803516d4)[*(short *)(PTR_DAT_80433944 + 6)])();
  return;
}



// ==== 8016f084  FUN_8016f084 ====

void FUN_8016f084(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  short sVar1;
  
  sVar1 = *(short *)(PTR_DAT_80433944 + 0xe);
  *(short *)(PTR_DAT_80433944 + 0xe) = sVar1 + -1;
  if ((short)(sVar1 + -1) < 1) {
    *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 1;
    zz_01af660_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,
                (&DAT_803bfde0)[(char)PTR_DAT_80433944[0x6c]],
                (&DAT_803bfe00)[(char)PTR_DAT_80433944[0x6c]]);
  }
  return;
}



// ==== 8016f0f8  FUN_8016f0f8 ====

void FUN_8016f0f8(void)

{
  char cVar1;
  int iVar2;
  
  iVar2 = zz_01af738_();
  if (iVar2 != 0) {
    *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 1;
    *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x20;
    PTR_DAT_80433944[0x6d] = 0;
    if (0 < iVar2) {
      PTR_DAT_80433944[0x91] =
           PTR_DAT_80433944[0x91] | (byte)(1 << (int)(char)PTR_DAT_80433944[0x6c]);
      zz_01748dc_((char *)((&DAT_803bfe00)[(char)PTR_DAT_80433944[0x6c]] + 0x2174));
      PTR_DAT_80433944[0x6c] = PTR_DAT_80433944[0x6c] + '\x01';
      cVar1 = PTR_DAT_80433944[0x6c];
      if (cVar1 < '\x02') {
        *(undefined2 *)(PTR_DAT_80433944 + 10) = 0xf;
      }
      else if (cVar1 < '\x04') {
        *(undefined2 *)(PTR_DAT_80433944 + 10) = 10;
      }
      else if (cVar1 < '\x06') {
        *(undefined2 *)(PTR_DAT_80433944 + 10) = 5;
      }
      else if (cVar1 < '\b') {
        *(undefined2 *)(PTR_DAT_80433944 + 10) = 0;
      }
      else {
        *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
        *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
        PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xfe;
        PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] | 1;
      }
    }
  }
  return;
}



// ==== 8016f2b8  FUN_8016f2b8 ====

void FUN_8016f2b8(void)

{
  zz_016fae8_();
  (*(code *)(&PTR_FUN_803516e0)[*(short *)(PTR_DAT_80433944 + 4)])();
  return;
}



// ==== 8016f2f8  FUN_8016f2f8 ====

void FUN_8016f2f8(void)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  short *psVar7;
  int *piVar8;
  int iVar9;
  char *pcVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  uint uVar14;
  short local_58 [2];
  int aiStack_54 [12];
  
  *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
  PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] | 2;
  if (PTR_DAT_80433944[0x91] == '\0') {
    zz_01cada4_(DAT_803bfde0,(undefined2 *)0x0,DAT_803bfe00);
    PTR_DAT_80433944[0x88] = 0;
    PTR_DAT_80433944[0x90] = 1;
    uVar12 = *(uint *)(DAT_803bfde0 + 0x54);
    PTR_DAT_80433944[0x89] = 0xff;
    PTR_DAT_80433944[0x8a] = 0xff;
    PTR_DAT_80433944[0x8b] = 0xff;
    PTR_DAT_80433944[0x8c] = 0xff;
    PTR_DAT_80433944[0x8d] = 0xff;
    PTR_DAT_80433944[0x8e] = 0xff;
    PTR_DAT_80433944[0x8f] = 0xff;
  }
  else {
    uVar12 = 0;
    iVar9 = 0;
    iVar3 = 8;
    PTR_DAT_80433944[0x90] = 0;
    piVar8 = (int *)&DAT_803bfde0;
    do {
      puVar2 = PTR_DAT_80433944;
      if (((uint)(byte)PTR_DAT_80433944[0x91] & 1 << iVar9) != 0) {
        cVar1 = PTR_DAT_80433944[0x90];
        PTR_DAT_80433944[0x90] = cVar1 + '\x01';
        puVar2[cVar1 + 0x88] = (char)iVar9;
        uVar12 = uVar12 | *(uint *)(*piVar8 + 0x54);
      }
      piVar8 = piVar8 + 1;
      iVar9 = iVar9 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    iVar3 = (int)(char)PTR_DAT_80433944[0x90];
    uVar5 = 8 - iVar3;
    if (iVar3 < 8) {
      uVar14 = uVar5 >> 3;
      if (uVar14 != 0) {
        do {
          PTR_DAT_80433944[iVar3 + 0x88] = 0xff;
          PTR_DAT_80433944[iVar3 + 0x89] = 0xff;
          PTR_DAT_80433944[iVar3 + 0x8a] = 0xff;
          PTR_DAT_80433944[iVar3 + 0x8b] = 0xff;
          PTR_DAT_80433944[iVar3 + 0x8c] = 0xff;
          PTR_DAT_80433944[iVar3 + 0x8d] = 0xff;
          PTR_DAT_80433944[iVar3 + 0x8e] = 0xff;
          iVar9 = iVar3 + 0x8f;
          iVar3 = iVar3 + 8;
          PTR_DAT_80433944[iVar9] = 0xff;
          uVar14 = uVar14 - 1;
        } while (uVar14 != 0);
        uVar5 = uVar5 & 7;
        if (uVar5 == 0) goto LAB_8016f4e4;
      }
      do {
        iVar9 = iVar3 + 0x88;
        iVar3 = iVar3 + 1;
        PTR_DAT_80433944[iVar9] = 0xff;
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
    }
  }
LAB_8016f4e4:
  *(undefined4 *)(PTR_DAT_80433944 + 0x78) = 0;
  for (iVar3 = 0; iVar3 < (char)PTR_DAT_80433944[0x90]; iVar3 = iVar3 + 1) {
    iVar13 = 0;
    cVar1 = PTR_DAT_80433944[iVar3 + 0x88];
    iVar11 = (int)(&DAT_803bfe00)[cVar1];
    aiStack_54[cVar1] = 999999;
    iVar9 = iVar11;
    do {
      if (*(char *)(iVar9 + 0x29) != '\0') {
        if (*(int *)(PTR_DAT_80433944 + 0x78) < *(int *)(iVar9 + 0x2c)) {
          *(int *)(PTR_DAT_80433944 + 0x78) = *(int *)(iVar9 + 0x2c);
        }
        for (iVar6 = 0; iVar6 < 0x1e; iVar6 = iVar6 + 1) {
          iVar4 = (int)*(short *)(iVar9 + iVar6 * 2 + 0x30);
          if (-1 < iVar4) {
            psVar7 = (short *)(iVar11 + iVar4 * 0x20 + 0x870);
            if (-1 < *psVar7) {
              local_58[0] = *psVar7;
              iVar6 = zz_0066168_((char *)local_58,(int)*(char *)(psVar7 + 1));
              if (iVar6 < aiStack_54[cVar1]) {
                aiStack_54[cVar1] = iVar6;
              }
            }
            iVar6 = 0x1e;
          }
        }
      }
      iVar13 = iVar13 + 1;
      iVar9 = iVar9 + 0x6c;
    } while (iVar13 < 0x14);
  }
  *(undefined4 *)(PTR_DAT_80433944 + 0x7c) = 0;
  for (iVar3 = 0; iVar3 < (char)PTR_DAT_80433944[0x90]; iVar3 = iVar3 + 1) {
    if (*(int *)(PTR_DAT_80433944 + 0x7c) < aiStack_54[(char)PTR_DAT_80433944[iVar3 + 0x88]]) {
      *(int *)(PTR_DAT_80433944 + 0x7c) = aiStack_54[(char)PTR_DAT_80433944[iVar3 + 0x88]];
    }
  }
  iVar9 = *(int *)(PTR_DAT_80433944 + 0x70);
  iVar3 = *(int *)(PTR_DAT_80433944 + 0x78);
  if ((iVar9 <= iVar3) && (iVar3 = iVar9, iVar9 < *(int *)(PTR_DAT_80433944 + 0x7c))) {
    iVar3 = *(int *)(PTR_DAT_80433944 + 0x7c);
  }
  *(int *)(PTR_DAT_80433944 + 0x70) = iVar3;
  iVar9 = *(int *)(PTR_DAT_80433944 + 0x74);
  iVar3 = *(int *)(PTR_DAT_80433944 + 0x78);
  if ((iVar9 <= iVar3) && (iVar3 = iVar9, iVar9 < *(int *)(PTR_DAT_80433944 + 0x7c))) {
    iVar3 = *(int *)(PTR_DAT_80433944 + 0x7c);
  }
  *(int *)(PTR_DAT_80433944 + 0x74) = iVar3;
  iVar9 = 0;
  iVar3 = 0x11;
  pcVar10 = &DAT_8035162c;
  *(undefined4 *)(PTR_DAT_80433934 + 0x120) = *(undefined4 *)(PTR_DAT_80433944 + 0x70);
  *(undefined4 *)(PTR_DAT_80433934 + 0x15c) = *(undefined4 *)(PTR_DAT_80433944 + 0x74);
  *(undefined4 *)(PTR_DAT_80433944 + 0x54) = 0;
  do {
    if ((uVar12 & 1 << iVar9) != 0) {
      *(uint *)(PTR_DAT_80433944 + 0x54) = *(uint *)(PTR_DAT_80433944 + 0x54) | 1 << (int)*pcVar10;
    }
    pcVar10 = pcVar10 + 2;
    iVar9 = iVar9 + 1;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  PTR_DAT_80433944[0x1a] = 0;
  zz_016f73c_();
  return;
}



// ==== 8016f73c  zz_016f73c_ ====

void zz_016f73c_(void)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  
  bVar2 = zz_0174464_((double)FLOAT_8043ace8);
  if (bVar2) {
    iVar3 = 0;
    iVar1 = 4;
    *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
    PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] | 2;
    PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] & 0xfd;
    PTR_DAT_80433930[2] = PTR_DAT_80433930[2] & ~PTR_DAT_80433944[0x6e];
    PTR_DAT_80433930[3] = 0;
    do {
      if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar3) != 0) {
        PTR_DAT_80433930[3] = PTR_DAT_80433930[3] + '\x01';
      }
      iVar3 = iVar3 + 1;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
    PTR_DAT_80433944[0x6e] = 0;
  }
  return;
}



// ==== 8016f80c  FUN_8016f80c ====

void FUN_8016f80c(void)

{
  ushort uVar1;
  byte bVar2;
  bool bVar3;
  bool bVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  
  iVar5 = 0;
  bVar4 = false;
  bVar3 = false;
  iVar7 = 0;
  PTR_DAT_80433930[3] = 0;
  while( true ) {
    if (3 < iVar5) break;
    uVar6 = 1 << iVar5;
    bVar2 = (byte)uVar6;
    if (((byte)PTR_DAT_80433944[0x14] & uVar6) == 0) {
      if (((int)(char)PTR_DAT_80433930[2] & uVar6) != 0) {
        PTR_DAT_80433930[2] = PTR_DAT_80433930[2] & ~bVar2;
        zz_00f0468_(0,0x7b,0);
      }
    }
    else {
      uVar1 = *(ushort *)(PTR_DAT_80433944 + iVar7 + 0x10e);
      if ((uVar1 & 0x200) == 0) {
        if ((uVar1 & 0x100) == 0) {
          if ((uVar1 & 0x80) != 0) {
            if (((int)(char)PTR_DAT_80433930[2] & uVar6) != 0) {
              bVar3 = true;
            }
          }
        }
        else {
          if (((int)(char)PTR_DAT_80433930[2] & uVar6) == 0) {
            PTR_DAT_80433930[2] = PTR_DAT_80433930[2] | bVar2;
            zz_011c648_(9,(char)iVar5 + '\x04');
          }
          else {
            zz_011c648_(9,(char)iVar5);
          }
          zz_00f0468_(0,0x7a,0);
        }
      }
      else if (((int)(char)PTR_DAT_80433930[2] & uVar6) == 0) {
        bVar4 = true;
      }
      else {
        PTR_DAT_80433930[2] = PTR_DAT_80433930[2] & ~bVar2;
        zz_00f0468_(0,0x7b,0);
      }
    }
    if (((int)(char)PTR_DAT_80433930[2] & uVar6) != 0) {
      PTR_DAT_80433930[3] = PTR_DAT_80433930[3] + '\x01';
    }
    iVar7 = iVar7 + 0x80;
    iVar5 = iVar5 + 1;
  }
  if (((int)(char)PTR_DAT_80433930[2] == (uint)(byte)PTR_DAT_80433944[0x14]) &&
     ((byte)PTR_DAT_80433944[0x14] != 0)) {
    bVar3 = true;
  }
  if (bVar4) {
    if ((char)PTR_DAT_80433944[0x6c] < '\b') {
      *(undefined2 *)(PTR_DAT_80433944 + 2) = 1;
    }
    else {
      *(undefined2 *)(PTR_DAT_80433944 + 0x10) = *(undefined2 *)(PTR_DAT_80433944 + 2);
      *(undefined2 *)(PTR_DAT_80433944 + 0x12) = 0;
      *(undefined2 *)(PTR_DAT_80433944 + 2) = 7;
    }
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] & 0xfd;
    PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xfd;
    zz_00f0468_(0,0x7b,0);
  }
  else if (bVar3) {
    *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
    *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x20;
    PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xfd;
    PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] | 2;
    zz_00f0468_(0,0x7a,0);
  }
  return;
}



// ==== 8016fae8  zz_016fae8_ ====

void zz_016fae8_(void)

{
  float fVar1;
  undefined *puVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  undefined1 *puVar6;
  float *pfVar7;
  int iVar8;
  uint uVar9;
  undefined8 local_10;
  
  if ((PTR_DAT_80433944[0x2e] & 2) == 0) {
    PTR_DAT_80433944[0x18] = PTR_DAT_80433944[0x16];
    PTR_DAT_80433944[0x19] = PTR_DAT_80433944[0x17];
  }
  fVar4 = FLOAT_8043acfc;
  fVar3 = FLOAT_8043acf8;
  puVar2 = PTR_DAT_80433944;
  uVar9 = 0;
  iVar8 = 0;
  iVar5 = 4;
  puVar6 = &DAT_803c73b0;
  pfVar7 = (float *)&DAT_803516f0;
  do {
    if (((uint)(byte)puVar2[0x18] & 1 << iVar8) == 0) {
      local_10 = (double)CONCAT44(0x43300000,(uint)(byte)puVar2[0x19]);
      fVar1 = FLOAT_8043acf4 + *pfVar7;
      *(float *)(puVar6 + 0x20) =
           FLOAT_8043acec *
           -((float)(local_10 - DOUBLE_8043ad00) * FLOAT_8043acf0 -
            (float)((double)CONCAT44(0x43300000,uVar9 ^ 0x80000000) - DOUBLE_8043ace0));
      *(float *)(puVar6 + 0x28) = fVar1;
    }
    else {
      local_10 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
      uVar9 = uVar9 + 1;
      fVar1 = *pfVar7;
      *(float *)(puVar6 + 0x20) =
           FLOAT_8043acec *
           -((float)((double)CONCAT44(0x43300000,(byte)puVar2[0x19] - 1 ^ 0x80000000) -
                    DOUBLE_8043ace0) * FLOAT_8043acf0 - (float)(local_10 - DOUBLE_8043ace0));
      *(float *)(puVar6 + 0x28) = fVar1;
    }
    fVar1 = pfVar7[1];
    *(float *)(puVar6 + 0x24) = fVar3;
    pfVar7 = pfVar7 + 2;
    iVar8 = iVar8 + 1;
    *(undefined2 *)(puVar6 + 0x70) = 0;
    *(short *)(puVar6 + 0x72) = (short)(int)(fVar4 * fVar1);
    *(undefined2 *)(puVar6 + 0x74) = 0;
    puVar6 = puVar6 + 0x3e4;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  return;
}



// ==== 8016fc5c  FUN_8016fc5c ====

void FUN_8016fc5c(void)

{
  (*(code *)(&PTR_FUN_80351710)[*(short *)(PTR_DAT_80433944 + 4)])();
  return;
}



// ==== 8016fc98  FUN_8016fc98 ====

void FUN_8016fc98(void)

{
  *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
  PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] | 4;
  PTR_DAT_80433944[0x1a] = 0;
  zz_016fce4_();
  return;
}



// ==== 8016fce4  zz_016fce4_ ====

void zz_016fce4_(void)

{
  int iVar1;
  bool bVar2;
  undefined *puVar3;
  int iVar4;
  uint uVar5;
  
  if ((FLOAT_8043ad08 < *(float *)(PTR_DAT_80433944 + 0x1c)) && (PTR_DAT_80433944[0x1b] != '\0')) {
    PTR_DAT_80433944[0x1b] = 0;
    zz_017035c_();
  }
  uVar5 = 0;
  iVar4 = 0;
  iVar1 = 4;
  bVar2 = false;
  puVar3 = PTR_DAT_80433944;
  do {
    if ((((int)(char)PTR_DAT_80433930[2] & 1 << iVar4) != 0) &&
       ((*(ushort *)(puVar3 + 0x10e) & 0x200) != 0)) {
      bVar2 = true;
      uVar5 = uVar5 | 1 << iVar4;
    }
    puVar3 = puVar3 + 0x80;
    iVar4 = iVar4 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  if (bVar2) {
    *(undefined2 *)(PTR_DAT_80433944 + 2) = 2;
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] & 0xfb;
    PTR_DAT_80433944[0x6e] = (char)uVar5;
    zz_00f0468_(0,0x7b,0);
  }
  else {
    bVar2 = zz_0174464_((double)FLOAT_8043ad0c);
    if (bVar2) {
      *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
      PTR_DAT_80433944[0x1a] = 1;
      PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] | 4;
      PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] & 0xfb;
    }
  }
  return;
}



// ==== 8016fe24  FUN_8016fe24 ====

/* WARNING: Removing unreachable block (ram,0x801702fc) */
/* WARNING: Removing unreachable block (ram,0x8016fe34) */

void FUN_8016fe24(void)

{
  double dVar1;
  char cVar2;
  byte bVar3;
  ushort uVar4;
  bool bVar5;
  undefined *puVar6;
  float fVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  bool bVar14;
  undefined1 *puVar15;
  undefined4 *puVar16;
  int iVar17;
  double dVar18;
  double dVar19;
  
  puVar16 = &DAT_803c727c;
  iVar13 = 0;
  puVar15 = &DAT_803c73b0;
  iVar17 = 0;
  do {
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar13) != 0) {
      dVar19 = (double)FLOAT_8043acd8;
      uVar4 = *(ushort *)(PTR_DAT_80433944 + iVar17 + 0x108);
      if ((uVar4 & 8) == 0) {
        dVar18 = dVar19;
        if ((uVar4 & 4) != 0) {
          dVar18 = (double)FLOAT_8043ad14;
        }
      }
      else {
        dVar18 = (double)FLOAT_8043ad10;
      }
      if ((uVar4 & 1) == 0) {
        if ((uVar4 & 2) != 0) {
          dVar19 = (double)FLOAT_8043ad10;
        }
      }
      else {
        dVar19 = (double)FLOAT_8043ad14;
      }
      if (((double)FLOAT_8043acd8 != dVar19) || ((double)FLOAT_8043acd8 != dVar18)) {
        iVar8 = FUN_800452a0(dVar19,dVar18);
        dVar19 = zz_0045204_((short)iVar8);
        dVar19 = (double)(float)((double)FLOAT_8043ad18 * dVar19);
        dVar18 = zz_0045238_((short)iVar8);
        dVar18 = (double)(float)((double)FLOAT_8043ad18 * dVar18);
      }
      dVar1 = (double)CONCAT44(0x43300000,(int)*(char *)((int)puVar16 + 0x17) ^ 0x80000000) -
              DOUBLE_8043ace0;
      *(float *)(puVar15 + 0x20) =
           *(float *)(puVar15 + 0x20) +
           (float)(dVar19 + (double)(float)((double)CONCAT44(0x43300000,
                                                             (int)*(char *)((int)puVar16 + 0x16) ^
                                                             0x80000000) - DOUBLE_8043ace0));
      *(float *)(puVar15 + 0x24) =
           *(float *)(puVar15 + 0x24) + (float)(dVar18 + (double)(float)dVar1);
    }
    iVar13 = iVar13 + 1;
    puVar16 = puVar16 + 8;
    puVar15 = puVar15 + 0x3e4;
    iVar17 = iVar17 + 0x80;
  } while (iVar13 < 4);
  do {
    iVar13 = zz_01744cc_();
  } while (iVar13 != 0);
  uVar12 = 0;
  bVar14 = false;
  bVar5 = false;
  iVar13 = 0;
  puVar15 = &DAT_803c73b0;
  for (iVar17 = 0; fVar7 = FLOAT_8043ad1c, puVar6 = PTR_DAT_80433944, iVar17 < 4;
      iVar17 = iVar17 + 1) {
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar17) != 0) {
      iVar8 = iVar17 + 0x24;
      PTR_DAT_80433944[iVar8] = FLOAT_8043acd8 <= *(float *)(puVar15 + 0x20);
      PTR_DAT_80433944[iVar8] =
           PTR_DAT_80433944[iVar8] +
           (byte)(((uint)(byte)((*(float *)(puVar15 + 0x24) <= fVar7) << 1) << 0x1c) >> 0x1c);
      uVar4 = *(ushort *)(puVar6 + iVar13 + 0x10e);
      if ((uVar4 & 0x200) == 0) {
        if ((uVar4 & 0x100) == 0) {
          if ((uVar4 & 0x400) == 0) {
            if ((uVar4 & 0x80) != 0) {
              bVar5 = true;
            }
          }
          else {
            iVar11 = (int)(char)PTR_DAT_80433944[iVar8] + 0x20;
            bVar3 = PTR_DAT_80433944[iVar11];
            if ((char)bVar3 < '\0') {
              if ((bVar3 & 0x40) == 0) {
                if ((PTR_DAT_80433944[((int)(char)PTR_DAT_80433944[iVar8] ^ 2U) + 0x20] & 0xc0) !=
                    0xc0) {
                  PTR_DAT_80433944[iVar11] = bVar3 | 0x40;
                }
              }
              else {
                PTR_DAT_80433944[iVar11] = bVar3 & 0xbf;
              }
            }
            if (PTR_DAT_80433944[(char)PTR_DAT_80433944[iVar17 + 0x24] + 0x20] == bVar3) {
              zz_00f0468_(0,0x7d,0);
            }
            else {
              zz_00f0468_(0,0x7a,0);
            }
          }
        }
        else {
          cVar2 = PTR_DAT_80433944[iVar17 + 0x28];
          uVar9 = (uint)(char)PTR_DAT_80433944[iVar17 + 0x24];
          if (uVar9 != (int)cVar2) {
            uVar10 = (int)cVar2 ^ 2;
            if (((uVar9 == uVar10) || ((PTR_DAT_80433944[uVar9 + 0x20] & 0xc0) != 0xc0)) ||
               ((PTR_DAT_80433944[uVar10 + 0x20] & 0xc0) != 0xc0)) {
              PTR_DAT_80433944[cVar2 + 0x20] = PTR_DAT_80433944[uVar9 + 0x20];
              PTR_DAT_80433944
              [((byte)PTR_DAT_80433944[(char)PTR_DAT_80433944[iVar17 + 0x24] + 0x20] & 0xf) + 0x28]
                   = PTR_DAT_80433944[iVar17 + 0x28];
              PTR_DAT_80433944[(char)PTR_DAT_80433944[iVar17 + 0x24] + 0x20] = (char)iVar17;
              PTR_DAT_80433944[iVar17 + 0x28] = PTR_DAT_80433944[iVar17 + 0x24];
              uVar9 = (int)(char)PTR_DAT_80433944[iVar17 + 0x24] ^ 1;
              if (PTR_DAT_80433930[3] == '\x02') {
                iVar8 = uVar9 + 0x20;
                cVar2 = PTR_DAT_80433944[iVar8];
                if (((int)cVar2 & 0x80U) == 0) {
                  uVar10 = (int)(char)PTR_DAT_80433944[iVar17 + 0x24] ^ 3;
                  iVar11 = uVar10 + 0x20;
                  PTR_DAT_80433944[iVar8] = PTR_DAT_80433944[iVar11];
                  PTR_DAT_80433944[((byte)PTR_DAT_80433944[iVar11] & 0xf) + 0x28] = (char)uVar9;
                  PTR_DAT_80433944[iVar11] = cVar2;
                  PTR_DAT_80433944[((int)cVar2 & 0xfU) + 0x28] = (char)uVar10;
                }
              }
              zz_00f0468_(0,0x7a,0);
            }
            else {
              zz_00f0468_(0,0x7d,0);
            }
          }
        }
      }
      else {
        bVar14 = true;
        uVar12 = uVar12 | 1 << iVar17;
      }
    }
    iVar13 = iVar13 + 0x80;
    puVar15 = puVar15 + 0x3e4;
  }
  if (bVar14) {
    *(undefined2 *)(PTR_DAT_80433944 + 2) = 2;
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] & 0xfb;
    PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xfb;
    PTR_DAT_80433944[0x6e] = (char)uVar12;
    zz_00f0468_(0,0x7b,0);
  }
  else if (bVar5) {
    *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
    *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x20;
    PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xfb;
    PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] | 4;
    zz_00f0468_(0,0x7a,0);
  }
  return;
}



// ==== 8017035c  zz_017035c_ ====

void zz_017035c_(void)

{
  char cVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  undefined1 *puVar6;
  undefined *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  
  PTR_DAT_80433944[0x20] = 0xff;
  PTR_DAT_80433944[0x21] = 0xff;
  PTR_DAT_80433944[0x22] = 0xff;
  PTR_DAT_80433944[0x23] = 0xff;
  cVar1 = PTR_DAT_80433930[2];
  uVar5 = (uint)(byte)PTR_DAT_80433944[0x94] - (int)cVar1 |
          (int)cVar1 - (uint)(byte)PTR_DAT_80433944[0x94];
  if ((int)uVar5 < 0) {
    PTR_DAT_80433944[0x94] = cVar1;
    PTR_DAT_80433944[0x95] = 0;
  }
  iVar8 = 0;
  iVar9 = 4;
  puVar6 = &DAT_803c73b0;
  iVar11 = 0;
  do {
    fVar4 = FLOAT_8043ad20;
    iVar10 = iVar11;
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar8) != 0) {
      if ((PTR_DAT_80433944[0x93] == '\0') || ((int)uVar5 < 0)) {
        iVar10 = 1;
        if (PTR_DAT_80433930[3] == '\x02') {
          iVar10 = 3;
        }
        iVar10 = iVar11 + iVar10;
      }
      else {
        iVar11 = (int)(char)PTR_DAT_80433944[iVar8 + 0x28];
      }
      uVar2 = (&DAT_80351724)[iVar11 * 2];
      *(undefined4 *)(puVar6 + 0x20) = (&DAT_80351720)[iVar11 * 2];
      fVar3 = FLOAT_8043acd8;
      *(undefined4 *)(puVar6 + 0x24) = uVar2;
      *(float *)(puVar6 + 0x28) = fVar4;
      *(undefined2 *)(puVar6 + 0x70) = 0x1555;
      *(undefined2 *)(puVar6 + 0x72) = 0;
      *(undefined2 *)(puVar6 + 0x74) = 0;
      iVar11 = iVar8 + 0x24;
      PTR_DAT_80433944[iVar11] = fVar3 <= *(float *)(puVar6 + 0x20);
      PTR_DAT_80433944[iVar11] =
           PTR_DAT_80433944[iVar11] +
           (byte)(((uint)(byte)((*(float *)(puVar6 + 0x24) <= FLOAT_8043ad1c) << 1) << 0x1c) >> 0x1c
                 );
      PTR_DAT_80433944[iVar8 + 0x28] = PTR_DAT_80433944[iVar8 + 0x24];
      PTR_DAT_80433944[(char)PTR_DAT_80433944[iVar8 + 0x28] + 0x20] = (char)iVar8;
    }
    puVar6 = puVar6 + 0x3e4;
    iVar8 = iVar8 + 1;
    iVar9 = iVar9 + -1;
    iVar11 = iVar10;
  } while (iVar9 != 0);
  iVar11 = 0;
  iVar8 = 4;
  do {
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar11) == 0) {
      iVar9 = 0;
      for (puVar7 = PTR_DAT_80433944; (iVar9 < 4 && (puVar7[0x20] != -1)); puVar7 = puVar7 + 1) {
        iVar9 = iVar9 + 1;
      }
      if ((iVar9 < 4) && (iVar10 = iVar9 + 0x20, PTR_DAT_80433944[iVar10] == -1)) {
        PTR_DAT_80433944[iVar11 + 0x28] = (char)iVar9;
        PTR_DAT_80433944[iVar11 + 0x24] = (char)iVar9;
        PTR_DAT_80433944[iVar10] = (byte)iVar11 | 0x80;
        if (((uint)(byte)PTR_DAT_80433944[0x95] & 1 << iVar11) != 0) {
          PTR_DAT_80433944[iVar10] = PTR_DAT_80433944[iVar10] | 0x40;
        }
      }
    }
    iVar11 = iVar11 + 1;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  return;
}



// ==== 801705b8  FUN_801705b8 ====

void FUN_801705b8(void)

{
  (*(code *)(&PTR_FUN_80351740)[*(short *)(PTR_DAT_80433944 + 4)])();
  return;
}



// ==== 801705f4  FUN_801705f4 ====

void FUN_801705f4(void)

{
  *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
  *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x38;
  PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] | 8;
  PTR_DAT_80433944[0x83] = 0;
  PTR_DAT_80433934[0x15d7] = PTR_DAT_80433944[0x82];
  *(undefined4 *)(PTR_DAT_80433934 + 0x120) = *(undefined4 *)(PTR_DAT_80433944 + 0x70);
  *(undefined4 *)(PTR_DAT_80433934 + 0x15c) = *(undefined4 *)(PTR_DAT_80433944 + 0x74);
  zz_017067c_();
  return;
}



// ==== 8017067c  zz_017067c_ ====

void zz_017067c_(void)

{
  if (*(short *)(PTR_DAT_80433944 + 0xe) != 0) {
    *(short *)(PTR_DAT_80433944 + 0xe) = *(short *)(PTR_DAT_80433944 + 0xe) + -1;
    return;
  }
  *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
  PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] | 8;
  PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] & 0xf7;
  return;
}



// ==== 801706c8  FUN_801706c8 ====

void FUN_801706c8(void)

{
  short sVar1;
  int iVar2;
  char cVar3;
  undefined *puVar4;
  int iVar5;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  
  iVar5 = 0;
  uVar6 = 0;
  iVar2 = 4;
  uVar8 = 0;
  uVar7 = 0;
  puVar4 = PTR_DAT_80433944;
  do {
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar5) != 0) {
      uVar6 = uVar6 | *(ushort *)(puVar4 + 0x108);
      uVar8 = uVar8 | *(ushort *)(puVar4 + 0x10e);
      uVar7 = uVar7 | *(ushort *)(puVar4 + 0x10c);
    }
    puVar4 = puVar4 + 0x80;
    iVar5 = iVar5 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if ((uVar6 & 0xc) == 0) {
    if ((uVar6 & 3) == 0) {
      *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0;
    }
    else if (*(short *)(PTR_DAT_80433944 + 0xe) < 0x1000) {
      *(short *)(PTR_DAT_80433944 + 0xe) = *(short *)(PTR_DAT_80433944 + 0xe) + 1;
    }
    cVar3 = PTR_DAT_80433944[0x83];
    if (cVar3 < '\x02') {
      sVar1 = *(short *)(PTR_DAT_80433944 + 0xe);
      iVar2 = 10;
      if (0x3b < sVar1) {
        iVar2 = 0x6e;
      }
      if (0x77 < sVar1) {
        iVar2 = iVar2 + 1000;
      }
      if (0xb3 < sVar1) {
        iVar2 = iVar2 + 10000;
      }
      if (0xef < sVar1) {
        iVar2 = iVar2 + 100000;
      }
      if ((uVar7 & 1) != 0) {
        if (*(int *)(PTR_DAT_80433944 + 0x7c) < *(int *)(PTR_DAT_80433944 + cVar3 * 4 + 0x70)) {
          iVar5 = *(int *)(PTR_DAT_80433944 + cVar3 * 4 + 0x70) - iVar2;
          *(int *)(PTR_DAT_80433944 + cVar3 * 4 + 0x70) = iVar5;
          if (iVar5 < *(int *)(PTR_DAT_80433944 + 0x7c)) {
            *(int *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x83] * 4 + 0x70) =
                 *(int *)(PTR_DAT_80433944 + 0x7c);
          }
          zz_00f0468_(0,0x77,0);
        }
      }
      if ((uVar7 & 2) != 0) {
        if (*(int *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x83] * 4 + 0x70) <
            *(int *)(PTR_DAT_80433944 + 0x78)) {
          iVar2 = *(int *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x83] * 4 + 0x70) + iVar2;
          *(int *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x83] * 4 + 0x70) = iVar2;
          if (*(int *)(PTR_DAT_80433944 + 0x78) < iVar2) {
            *(int *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x83] * 4 + 0x70) =
                 *(int *)(PTR_DAT_80433944 + 0x78);
          }
          zz_00f0468_(0,0x77,0);
        }
      }
    }
    else {
      if (((uVar7 & 1) != 0) && ('\0' < (char)PTR_DAT_80433944[0x82])) {
        cVar3 = PTR_DAT_80433944[0x82] + -1;
        PTR_DAT_80433944[0x82] = cVar3;
        if (cVar3 < '\0') {
          PTR_DAT_80433944[0x82] = 0;
        }
        zz_00f0468_(0,0x77,0);
      }
      if (((uVar7 & 2) != 0) && ((char)PTR_DAT_80433944[0x82] < '\x03')) {
        cVar3 = PTR_DAT_80433944[0x82] + '\x01';
        PTR_DAT_80433944[0x82] = cVar3;
        if ('\x03' < cVar3) {
          PTR_DAT_80433944[0x82] = 3;
        }
        zz_00f0468_(0,0x77,0);
      }
    }
  }
  else {
    iVar2 = (int)(char)PTR_DAT_80433944[0x83];
    if (((uVar7 & 8) != 0) && (iVar2 = iVar2 + -1, iVar2 < 0)) {
      iVar2 = 2;
    }
    if (((uVar7 & 4) != 0) && (iVar2 = iVar2 + 1, 2 < iVar2)) {
      iVar2 = 0;
    }
    if (iVar2 != (char)PTR_DAT_80433944[0x83]) {
      PTR_DAT_80433944[0x83] = (char)iVar2;
      *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0;
      zz_00f0468_(0,0x77,0);
    }
  }
  if ((uVar8 & 0x200) == 0) {
    if ((uVar8 & 0x180) != 0) {
      *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
      PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xf7;
      PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] | 8;
      PTR_DAT_80433934[0x15d7] = PTR_DAT_80433944[0x82];
      *(undefined4 *)(PTR_DAT_80433934 + 0x120) = *(undefined4 *)(PTR_DAT_80433944 + 0x70);
      *(undefined4 *)(PTR_DAT_80433934 + 0x15c) = *(undefined4 *)(PTR_DAT_80433944 + 0x74);
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *(undefined2 *)(PTR_DAT_80433944 + 2) = 3;
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] & 0xf7;
    PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xf7;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 80170a9c  FUN_80170a9c ====

void FUN_80170a9c(void)

{
  (*(code *)(&PTR_FUN_80351750)[*(short *)(PTR_DAT_80433944 + 4)])();
  return;
}



// ==== 80170ad8  FUN_80170ad8 ====

void FUN_80170ad8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  undefined1 uVar6;
  size_t sVar5;
  char cVar7;
  int iVar8;
  int iVar9;
  char *pcVar10;
  undefined1 *puVar11;
  
  iVar9 = 0;
  iVar3 = 0x12;
  iVar8 = 0;
  *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
  PTR_DAT_80433944[0x84] = 0xff;
  *(uint *)(PTR_DAT_80433944 + 0x54) = *(uint *)(PTR_DAT_80433944 + 0x54) | 0x20000;
  PTR_DAT_80433944[0x6a] = 0;
  do {
    puVar2 = PTR_DAT_80433944;
    if ((*(uint *)(PTR_DAT_80433944 + 0x54) & 1 << iVar9) != 0) {
      cVar7 = PTR_DAT_80433944[0x6a];
      PTR_DAT_80433944[0x6a] = cVar7 + '\x01';
      puVar2[cVar7 + 0x58] = (char)iVar9;
    }
    iVar4 = iVar8 + 0x30;
    iVar8 = iVar8 + 2;
    iVar9 = iVar9 + 1;
    *(undefined2 *)(PTR_DAT_80433944 + iVar4) = 0;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar8 = 0;
  iVar3 = 0;
  do {
    puVar11 = PTR_DAT_80433944 + iVar3 + 0x100;
    uVar6 = (undefined1)iVar8;
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar8) == 0) {
      if ((PTR_DAT_80433944[(char)PTR_DAT_80433944[iVar8 + 0x28] + 0x20] & 0x40) == 0) {
        for (pcVar10 = &DAT_80351190; -1 < *pcVar10; pcVar10 = pcVar10 + 2) {
          param_1 = zz_0167334_(uVar6,(int)*pcVar10,pcVar10[1]);
        }
      }
      else {
        param_1 = zz_0167334_(uVar6,0,2);
      }
      *puVar11 = 6;
      puVar11[0x66] = 0;
      puVar11[0x61] = 0xff;
      strcpy(puVar11 + 0x20,PTR_DAT_802cfdb0);
    }
    else {
      for (pcVar10 = &DAT_8035115c; -1 < *pcVar10; pcVar10 = pcVar10 + 2) {
        param_1 = zz_0167334_(uVar6,(int)*pcVar10,pcVar10[1]);
      }
      puVar11[0x62] = 0;
    }
    puVar11[0x38] = 0;
    sVar5 = strlen(puVar11 + 0x20);
    puVar11[0x39] = (char)sVar5;
    cVar7 = '\x16';
    if ((char)puVar11[0x39] < '\x16') {
      cVar7 = puVar11[0x39];
    }
    puVar11[0x3a] = cVar7;
    cVar7 = '\0';
    puVar11[0x3b] = 3;
    iVar9 = 0x14;
    iVar4 = 0;
    *(undefined4 *)(puVar11 + 0x40) =
         (&DAT_803bfe00)[(char)PTR_DAT_80433944[(char)puVar11[0x66] + 0x88]];
    puVar11[0x60] = 0;
    do {
      if (*(char *)(*(int *)(puVar11 + 0x40) + iVar4 + 0x29) != '\0') {
        cVar1 = puVar11[0x60];
        puVar11[0x60] = cVar1 + '\x01';
        puVar11[cVar1 + 0x4c] = cVar7;
      }
      iVar4 = iVar4 + 0x6c;
      cVar7 = cVar7 + '\x01';
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    iVar8 = iVar8 + 1;
    iVar3 = iVar3 + 0x80;
  } while (iVar8 < 4);
  zz_00437b0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
  zz_0170d60_();
  return;
}



// ==== 80170d60  zz_0170d60_ ====

void zz_0170d60_(void)

{
  int iVar1;
  bool bVar2;
  
  iVar1 = zz_000a3c4_();
  if ((iVar1 == 0) && (bVar2 = zz_0174464_((double)FLOAT_8043ad24), bVar2)) {
    *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
  }
  return;
}



// ==== 80170da8  FUN_80170da8 ====

void FUN_80170da8(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  PTR_DAT_80433944[0x2f] = 0;
  for (iVar1 = 0; iVar1 < 4; iVar1 = iVar1 + 1) {
    (*(code *)(&PTR_FUN_80351764)[(char)PTR_DAT_80433944[iVar2 + 0x100]])();
    iVar2 = iVar2 + 0x80;
  }
  if (PTR_DAT_80433944[0x2f] == '\x0f') {
    *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 2;
  }
  else if ((PTR_DAT_80433944[0x2c] & 8) != 0) {
    *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x38;
    PTR_DAT_80433944[0x83] = 0;
    PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] & 0xf7;
    PTR_DAT_80433944[0x82] = PTR_DAT_80433934[0x15d7];
    *(undefined4 *)(PTR_DAT_80433944 + 0x70) = *(undefined4 *)(PTR_DAT_80433934 + 0x120);
    *(undefined4 *)(PTR_DAT_80433944 + 0x74) = *(undefined4 *)(PTR_DAT_80433934 + 0x15c);
  }
  return;
}



// ==== 80170ec4  FUN_80170ec4 ====

void FUN_80170ec4(void)

{
  (*(code *)(&PTR_LAB_80351780)[*(short *)(PTR_DAT_80433944 + 6)])();
  return;
}



// ==== 80170f3c  FUN_80170f3c ====

void FUN_80170f3c(void)

{
  short sVar1;
  int iVar2;
  char cVar4;
  int iVar3;
  undefined *puVar5;
  int iVar6;
  ushort uVar7;
  undefined1 *puVar8;
  ushort uVar9;
  ushort uVar10;
  
  iVar6 = 0;
  uVar7 = 0;
  iVar2 = 4;
  uVar10 = 0;
  uVar9 = 0;
  puVar5 = PTR_DAT_80433944;
  do {
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar6) != 0) {
      uVar7 = uVar7 | *(ushort *)(puVar5 + 0x108);
      uVar9 = uVar9 | *(ushort *)(puVar5 + 0x10e);
      uVar10 = uVar10 | *(ushort *)(puVar5 + 0x10c);
    }
    puVar5 = puVar5 + 0x80;
    iVar6 = iVar6 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if ((uVar7 & 0xc) == 0) {
    if ((uVar7 & 3) == 0) {
      *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0;
    }
    else if (*(short *)(PTR_DAT_80433944 + 0xe) < 0x1000) {
      *(short *)(PTR_DAT_80433944 + 0xe) = *(short *)(PTR_DAT_80433944 + 0xe) + 1;
    }
    cVar4 = PTR_DAT_80433944[0x83];
    if (cVar4 < '\x02') {
      sVar1 = *(short *)(PTR_DAT_80433944 + 0xe);
      iVar2 = 10;
      if (0x3b < sVar1) {
        iVar2 = 0x6e;
      }
      if (0x77 < sVar1) {
        iVar2 = iVar2 + 1000;
      }
      if (0xb3 < sVar1) {
        iVar2 = iVar2 + 10000;
      }
      if (0xef < sVar1) {
        iVar2 = iVar2 + 100000;
      }
      if ((uVar10 & 1) != 0) {
        if (*(int *)(PTR_DAT_80433944 + 0x7c) < *(int *)(PTR_DAT_80433944 + cVar4 * 4 + 0x70)) {
          iVar6 = *(int *)(PTR_DAT_80433944 + cVar4 * 4 + 0x70) - iVar2;
          *(int *)(PTR_DAT_80433944 + cVar4 * 4 + 0x70) = iVar6;
          if (iVar6 < *(int *)(PTR_DAT_80433944 + 0x7c)) {
            *(int *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x83] * 4 + 0x70) =
                 *(int *)(PTR_DAT_80433944 + 0x7c);
          }
          zz_00f0468_(0,0x77,0);
        }
      }
      if ((uVar10 & 2) != 0) {
        if (*(int *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x83] * 4 + 0x70) <
            *(int *)(PTR_DAT_80433944 + 0x78)) {
          iVar2 = *(int *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x83] * 4 + 0x70) + iVar2;
          *(int *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x83] * 4 + 0x70) = iVar2;
          if (*(int *)(PTR_DAT_80433944 + 0x78) < iVar2) {
            *(int *)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x83] * 4 + 0x70) =
                 *(int *)(PTR_DAT_80433944 + 0x78);
          }
          zz_00f0468_(0,0x77,0);
        }
      }
    }
    else {
      if (((uVar10 & 1) != 0) && ('\0' < (char)PTR_DAT_80433944[0x82])) {
        cVar4 = PTR_DAT_80433944[0x82] + -1;
        PTR_DAT_80433944[0x82] = cVar4;
        if (cVar4 < '\0') {
          PTR_DAT_80433944[0x82] = 0;
        }
        zz_00f0468_(0,0x77,0);
      }
      if (((uVar10 & 2) != 0) && ((char)PTR_DAT_80433944[0x82] < '\x03')) {
        cVar4 = PTR_DAT_80433944[0x82] + '\x01';
        PTR_DAT_80433944[0x82] = cVar4;
        if ('\x03' < cVar4) {
          PTR_DAT_80433944[0x82] = 3;
        }
        zz_00f0468_(0,0x77,0);
      }
    }
  }
  else {
    iVar2 = (int)(char)PTR_DAT_80433944[0x83];
    if (((uVar10 & 8) != 0) && (iVar2 = iVar2 + -1, iVar2 < 0)) {
      iVar2 = 2;
    }
    if (((uVar10 & 4) != 0) && (iVar2 = iVar2 + 1, 2 < iVar2)) {
      iVar2 = 0;
    }
    if (iVar2 != (char)PTR_DAT_80433944[0x83]) {
      PTR_DAT_80433944[0x83] = (char)iVar2;
      *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0;
      zz_00f0468_(0,0x77,0);
    }
  }
  if ((uVar9 & 0x380) != 0) {
    *(short *)(PTR_DAT_80433944 + 6) = *(short *)(PTR_DAT_80433944 + 6) + 1;
    *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x20;
    PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] & 0xf7;
    PTR_DAT_80433944[0x2d] = PTR_DAT_80433944[0x2d] & 0xf7;
    PTR_DAT_80433944[0x2e] = PTR_DAT_80433944[0x2e] | 8;
    if ((uVar9 & 0x200) == 0) {
      iVar2 = 0;
      iVar6 = 0;
      PTR_DAT_80433934[0x15d7] = PTR_DAT_80433944[0x82];
      *(undefined4 *)(PTR_DAT_80433934 + 0x120) = *(undefined4 *)(PTR_DAT_80433944 + 0x70);
      *(undefined4 *)(PTR_DAT_80433934 + 0x15c) = *(undefined4 *)(PTR_DAT_80433944 + 0x74);
      do {
        puVar8 = PTR_DAT_80433944 + iVar6 + 0x100;
        if ((puVar8[0x3f] & 4) != 0) {
          if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar2) == 0) {
            if ((-1 < (char)puVar8[0x61]) &&
               (iVar3 = zz_01cce38_(*(int *)(puVar8 + 0x40),
                                    (int)(char)puVar8[(char)puVar8[0x61] + 0x4c],
                                    *(int *)(PTR_DAT_80433934 +
                                            ((byte)PTR_DAT_80433944[(byte)puVar8[0x3c] + 0x28] & 1)
                                            * 0x3c + 0x120),1), iVar3 == 0)) {
              puVar8[0x61] = 0xff;
            }
          }
          else {
            *puVar8 = 2;
            puVar8[1] = 0;
            puVar8[0x3d] = 0;
            puVar8[0x3f] = 0;
            puVar8[0x3e] = puVar8[0x3e] & 0xdf;
            PTR_DAT_80433944[0x2f] = PTR_DAT_80433944[0x2f] & ~(byte)(1 << (uint)(byte)puVar8[0x3c])
            ;
          }
        }
        iVar2 = iVar2 + 1;
        iVar6 = iVar6 + 0x80;
      } while (iVar2 < 4);
      zz_00f0468_(0,0x7a,0);
    }
    else {
      zz_00f0468_(0,0x7b,0);
    }
  }
  return;
}



// ==== 80171400  FUN_80171400 ====

void FUN_80171400(int param_1)

{
  (*(code *)(&PTR_LAB_8035178c)[*(char *)(param_1 + 1)])();
  return;
}



// ==== 801714a4  FUN_801714a4 ====

void FUN_801714a4(int param_1)

{
  ushort uVar1;
  int iVar2;
  size_t sVar3;
  char cVar4;
  char cVar5;
  int iVar6;
  
  if ((*(ushort *)(param_1 + 0xe) & 0x800) != 0) {
    if (PTR_DAT_80433944[0x6b] == '\0') {
      zz_00f0468_(0,0x7d,0);
    }
    else {
      strcpy((char *)(param_1 + 0x20),PTR_DAT_80433944 + *(char *)(param_1 + 0x68) * 0x1a + 0x300);
      sVar3 = strlen((char *)(param_1 + 0x20));
      *(char *)(param_1 + 0x39) = (char)sVar3;
      cVar4 = '\x16';
      if (*(char *)(param_1 + 0x39) < '\x16') {
        cVar4 = *(char *)(param_1 + 0x39);
      }
      *(char *)(param_1 + 0x3a) = cVar4;
      cVar4 = *(char *)(param_1 + 0x68) + '\x01';
      *(char *)(param_1 + 0x68) = cVar4;
      if ((char)PTR_DAT_80433944[0x6b] + -1 < (int)cVar4) {
        *(undefined1 *)(param_1 + 0x68) = 0;
      }
      zz_00f0468_(0,0x7a,0);
    }
  }
  cVar4 = *(char *)(param_1 + 100);
  iVar6 = (int)*(char *)(param_1 + 0x3b);
  iVar2 = iVar6 * 8;
  if ((*(ushort *)(param_1 + 0xc) & 1) == 0) {
    if ((*(ushort *)(param_1 + 0xc) & 2) != 0) {
      *(char *)(param_1 + 100) = *(char *)(param_1 + 100) + '\x01';
      while (*(short *)(&DAT_8035160e + iVar2) + -1 < (int)*(char *)(param_1 + 100)) {
        *(char *)(param_1 + 100) =
             *(char *)(param_1 + 100) - (char)*(short *)(&DAT_8035160e + iVar2);
      }
    }
  }
  else {
    *(char *)(param_1 + 100) = *(char *)(param_1 + 100) + -1;
    while (*(char *)(param_1 + 100) < '\0') {
      *(char *)(param_1 + 100) =
           *(char *)(param_1 + 100) + (char)*(undefined2 *)(&DAT_8035160e + iVar2);
    }
  }
  if (*(char *)(param_1 + 100) != cVar4) {
    zz_00f0468_(0,0x77,0);
  }
  cVar4 = *(char *)(param_1 + 0x65);
  if ((*(ushort *)(param_1 + 0xe) & 8) == 0) {
    if (((*(ushort *)(param_1 + 0xe) & 4) != 0) &&
       (cVar5 = *(char *)(param_1 + 0x65) + '\x01', *(char *)(param_1 + 0x65) = cVar5,
       '\x01' < cVar5)) {
      *(undefined1 *)(param_1 + 0x65) = 1;
    }
  }
  else {
    cVar5 = *(char *)(param_1 + 0x65) + -1;
    *(char *)(param_1 + 0x65) = cVar5;
    if (cVar5 < -1) {
      *(undefined1 *)(param_1 + 0x65) = 0xff;
    }
  }
  if (DAT_8043ad28 ==
      *(short *)((&PTR_DAT_80351610)[iVar6 * 2] +
                ((int)*(char *)(param_1 + 100) +
                (*(char *)(param_1 + 0x65) + 1) * (int)*(short *)(&DAT_8035160e + iVar2)) * 2)) {
    *(undefined1 *)(param_1 + 0x65) = 0;
  }
  if (*(char *)(param_1 + 0x65) != cVar4) {
    zz_00f0468_(0,0x77,0);
  }
  uVar1 = *(ushort *)(param_1 + 0xe);
  if ((uVar1 & 0x200) == 0) {
    if ((uVar1 & 0x100) == 0) {
      if ((uVar1 & 0x80) != 0) {
        if (*(char *)(param_1 + 0x39) < '\x01') {
          zz_00f0468_(0,0x7d,0);
        }
        else {
          *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x01';
          *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) & 0xfe;
          *(byte *)(param_1 + 0x3f) = *(byte *)(param_1 + 0x3f) | 1;
          *(undefined2 *)(param_1 + 4) = 4;
          zz_01748dc_((char *)(param_1 + 0x20));
          zz_00f0468_(0,0x7a,0);
        }
      }
    }
    else {
      *(undefined2 *)(param_1 + *(char *)(param_1 + 0x3a) + 0x20) =
           *(undefined2 *)
            ((&PTR_DAT_80351610)[iVar6 * 2] +
            ((int)*(char *)(param_1 + 100) +
            (*(char *)(param_1 + 0x65) + 1) * (int)*(short *)(&DAT_8035160e + iVar2)) * 2);
      *(undefined2 *)(*(char *)(param_1 + 0x3a) + param_1 + 0x22) = 0;
      sVar3 = strlen((char *)(param_1 + 0x20));
      *(char *)(param_1 + 0x39) = (char)sVar3;
      cVar4 = '\x16';
      if (*(char *)(param_1 + 0x39) < '\x16') {
        cVar4 = *(char *)(param_1 + 0x39);
      }
      *(char *)(param_1 + 0x3a) = cVar4;
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    if ('\0' < *(char *)(param_1 + 0x39)) {
      *(undefined1 *)(param_1 + *(char *)(param_1 + 0x39) + 0x1e) = 0;
      sVar3 = strlen((char *)(param_1 + 0x20));
      *(char *)(param_1 + 0x39) = (char)sVar3;
      cVar4 = '\x16';
      if (*(char *)(param_1 + 0x39) < '\x16') {
        cVar4 = *(char *)(param_1 + 0x39);
      }
      *(char *)(param_1 + 0x3a) = cVar4;
    }
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 801718b8  FUN_801718b8 ====

void FUN_801718b8(int param_1)

{
  (*(code *)(&PTR_LAB_8035179c)[*(char *)(param_1 + 1)])();
  return;
}



// ==== 80171954  FUN_80171954 ====

void FUN_80171954(undefined1 *param_1)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char cVar6;
  
  if (*(short *)(param_1 + 4) == 0) {
    iVar5 = (int)(char)param_1[0x66];
    if ((*(ushort *)(param_1 + 8) & 1) == 0) {
      if ((*(ushort *)(param_1 + 8) & 2) != 0) {
        for (iVar5 = iVar5 + 1; (char)PTR_DAT_80433944[0x90] <= iVar5;
            iVar5 = iVar5 - (char)PTR_DAT_80433944[0x90]) {
        }
        param_1[0x67] = 2;
      }
    }
    else {
      for (iVar5 = iVar5 + -1; iVar5 < 0; iVar5 = iVar5 + (char)PTR_DAT_80433944[0x90]) {
      }
      param_1[0x67] = 1;
    }
    if (iVar5 != (char)param_1[0x66]) {
      cVar6 = '\0';
      param_1[0x61] = 0;
      puVar2 = PTR_DAT_80433944;
      iVar3 = 0x14;
      iVar4 = 0;
      param_1[0x66] = (char)iVar5;
      *(undefined4 *)(param_1 + 0x40) = (&DAT_803bfe00)[(char)puVar2[(char)iVar5 + 0x88]];
      param_1[0x60] = 0;
      do {
        if (*(char *)(*(int *)(param_1 + 0x40) + iVar4 + 0x29) != '\0') {
          cVar1 = param_1[0x60];
          param_1[0x60] = cVar1 + '\x01';
          param_1[cVar1 + 0x4c] = cVar6;
        }
        iVar4 = iVar4 + 0x6c;
        cVar6 = cVar6 + '\x01';
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      *(undefined2 *)(param_1 + 4) = 9;
      zz_00f0468_(0,0x77,0);
    }
  }
  else {
    *(short *)(param_1 + 4) = *(short *)(param_1 + 4) + -1;
  }
  if ((*(ushort *)(param_1 + 0xe) & 0x200) == 0) {
    if ((*(ushort *)(param_1 + 0xe) & 0x180) != 0) {
      param_1[1] = param_1[1] + '\x01';
      param_1[0x3e] = param_1[0x3e] & 0xfd;
      param_1[0x3f] = param_1[0x3f] | 2;
      *(undefined2 *)(param_1 + 4) = 0x10;
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *param_1 = 0;
    param_1[1] = 0;
    param_1[0x3d] = param_1[0x3d] & 0xfd;
    param_1[0x3e] = param_1[0x3e] & 0xfd;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 80171b78  FUN_80171b78 ====

void FUN_80171b78(int param_1)

{
  (*(code *)(&PTR_LAB_803517ac)[*(char *)(param_1 + 1)])();
  return;
}



// ==== 80171c14  FUN_80171c14 ====

void FUN_80171c14(undefined1 *param_1)

{
  ushort uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  
  iVar3 = (int)(char)param_1[0x61];
  if ((*(ushort *)(param_1 + 0xc) & 1) == 0) {
    if ((*(ushort *)(param_1 + 0xc) & 2) != 0) {
      for (iVar3 = iVar3 + 1; (char)param_1[0x60] <= iVar3;
          iVar3 = iVar3 - ((char)param_1[0x60] + 1)) {
      }
    }
  }
  else {
    for (iVar3 = iVar3 + -1; iVar3 < -1; iVar3 = (char)param_1[0x60] + iVar3 + 1) {
    }
  }
  if (iVar3 != (char)param_1[0x61]) {
    param_1[0x61] = (char)iVar3;
    zz_00f0468_(0,0x77,0);
  }
  uVar1 = *(ushort *)(param_1 + 0xe);
  if ((uVar1 & 0x200) == 0) {
    if ((uVar1 & 0x10) == 0) {
      if ((uVar1 & 0x800) == 0) {
        if ((uVar1 & 0x400) == 0) {
          if ((uVar1 & 0x180) != 0) {
            if ((((char)param_1[0x61] < '\0') ||
                (iVar3 = zz_01cce38_(*(int *)(param_1 + 0x40),
                                     (int)(char)param_1[(char)param_1[0x61] + 0x4c],
                                     *(int *)(PTR_DAT_80433934 +
                                             ((byte)PTR_DAT_80433944[(byte)param_1[0x3c] + 0x28] & 1
                                             ) * 0x3c + 0x120),0), iVar3 == 0)) &&
               (param_1[0x61] != -1)) {
              zz_00f0468_(0,0x7d,0);
            }
            else {
              param_1[1] = param_1[1] + '\x01';
              param_1[0x3e] = param_1[0x3e] & 0xfb;
              param_1[0x3f] = param_1[0x3f] | 4;
              *(undefined2 *)(param_1 + 4) = 0x10;
              zz_00f0468_(0,0x7a,0);
            }
          }
        }
        else {
          iVar4 = 0;
          iVar3 = 4;
          uVar5 = 0;
          puVar2 = PTR_DAT_80433944;
          do {
            if ((puVar2[0x20] & 0xc0) == 0x80) {
              uVar5 = uVar5 | 1 << iVar4;
            }
            puVar2 = puVar2 + 1;
            iVar4 = iVar4 + 1;
            iVar3 = iVar3 + -1;
          } while (iVar3 != 0);
          if ((uVar5 == 0) || (-1 < (char)PTR_DAT_80433944[0x84])) {
            zz_00f0468_(0,0x7d,0);
          }
          else {
            *param_1 = 4;
            param_1[1] = 0;
            param_1[0x3e] = param_1[0x3e] & 0xfb;
            PTR_DAT_80433944[0x84] = param_1[0x3c];
            zz_00f0468_(0,0x7a,0);
          }
        }
      }
      else {
        PTR_DAT_80433944[0x2c] = PTR_DAT_80433944[0x2c] | 8;
        zz_00f0468_(0,0x7a,0);
      }
    }
    else if ((char)param_1[0x61] < '\0') {
      zz_00f0468_(0,0x7d,0);
    }
    else {
      *param_1 = 3;
      param_1[1] = 0;
      param_1[0x3d] = param_1[0x3d] & 0xfb;
      param_1[0x3e] = param_1[0x3e] & 0xfb;
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    if ((char)PTR_DAT_80433944[0x90] < '\x02') {
      *param_1 = 0;
    }
    else {
      *param_1 = 1;
    }
    param_1[1] = 0;
    param_1[0x3d] = param_1[0x3d] & 0xfb;
    param_1[0x3e] = param_1[0x3e] & 0xfb;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 80171f58  FUN_80171f58 ====

void FUN_80171f58(int param_1)

{
  (*(code *)(&PTR_FUN_803517bc)[*(char *)(param_1 + 1)])();
  return;
}



// ==== 80171f94  FUN_80171f94 ====

void FUN_80171f94(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x01';
  *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) | 8;
  *(undefined2 *)(param_1 + 4) = 4;
  *(short *)(param_1 + 6) =
       (short)*(char *)(*(int *)(param_1 + 0x40) +
                        *(char *)(param_1 + *(char *)(param_1 + 0x61) + 0x4c) * 0x6c + 0x29);
  *(undefined1 *)(param_1 + 100) = 0;
  *(char *)(param_1 + 0x65) = (char)*(undefined2 *)(param_1 + 6) + '\x02';
  do {
    zz_0167334_(*(undefined1 *)(param_1 + 0x3c),10,(char)iVar1);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 5);
  return;
}



// ==== 80172044  FUN_80172044 ====

void FUN_80172044(int param_1)

{
  char cVar1;
  short sVar2;
  
  if ((*(ushort *)(param_1 + 0xe) & 0x200) == 0) {
    sVar2 = *(short *)(param_1 + 4) + -1;
    *(short *)(param_1 + 4) = sVar2;
    if (sVar2 < 1) {
      cVar1 = *(char *)(param_1 + 0x65) + -1;
      *(char *)(param_1 + 0x65) = cVar1;
      if (cVar1 <= *(char *)(param_1 + 100)) {
        *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x01';
        *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) | 8;
        *(byte *)(param_1 + 0x3f) = *(byte *)(param_1 + 0x3f) & 0xf7;
        *(undefined1 *)(param_1 + 0x65) = *(undefined1 *)(param_1 + 100);
      }
      *(undefined2 *)(param_1 + 4) = 4;
    }
  }
  else {
    *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x02';
    *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) & 0xf7;
    *(undefined2 *)(param_1 + 4) = 4;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 80172108  FUN_80172108 ====

void FUN_80172108(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (*(short *)(param_1 + 4) == 0) {
    iVar2 = (int)*(char *)(param_1 + 100);
    if ((*(ushort *)(param_1 + 8) & 8) == 0) {
      iVar3 = iVar2;
      if ((*(ushort *)(param_1 + 8) & 4) != 0) {
        iVar1 = *(short *)(param_1 + 6) + -1;
        iVar3 = iVar2 + 1;
        if (iVar1 < iVar2 + 1) {
          iVar3 = iVar1;
        }
      }
    }
    else {
      iVar3 = iVar2 + -1;
      if (iVar2 + -1 < 0) {
        iVar3 = 0;
      }
    }
    if (iVar3 != *(char *)(param_1 + 100)) {
      *(char *)(param_1 + 0x65) = (char)iVar3;
      *(char *)(param_1 + 100) = (char)iVar3;
      *(undefined2 *)(param_1 + 4) = 7;
      zz_00f0468_(0,0x77,0);
    }
  }
  else {
    *(short *)(param_1 + 4) = *(short *)(param_1 + 4) + -1;
  }
  if ((*(ushort *)(param_1 + 0xe) & 0x200) != 0) {
    *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x01';
    *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) & 0xf7;
    *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) & 0xf7;
    *(undefined1 *)(param_1 + 0x65) = *(undefined1 *)(param_1 + 100);
    *(undefined2 *)(param_1 + 4) = 4;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 80172258  FUN_80172258 ====

void FUN_80172258(int param_1)

{
  (*(code *)(&PTR_FUN_803517cc)[*(char *)(param_1 + 1)])();
  return;
}



// ==== 80172294  FUN_80172294 ====

void FUN_80172294(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = 4;
  *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x01';
  *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) & 0xfb;
  *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) | 0x10;
  *(undefined2 *)(param_1 + 4) = 0x20;
  *(undefined *)(param_1 + 100) = PTR_DAT_80433944[*(byte *)(param_1 + 0x3c) + 0x28];
  *(undefined1 *)(param_1 + 0x65) = 0;
  do {
    if ((iVar2 == (char)PTR_DAT_80433944[*(byte *)(param_1 + 0x3c) + 0x28]) ||
       ((PTR_DAT_80433944[iVar2 + 0x20] & 0xc0) == 0x80)) {
      *(byte *)(param_1 + 0x65) = *(byte *)(param_1 + 0x65) | (byte)(1 << iVar2);
    }
    iVar2 = iVar2 + 1;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  zz_011c648_(0x10,*(undefined1 *)(param_1 + 0x3c));
  return;
}



// ==== 801723a8  FUN_801723a8 ====

void FUN_801723a8(int param_1)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  char cVar8;
  
  uVar2 = *(ushort *)(param_1 + 8);
  uVar6 = (uint)*(char *)(param_1 + 100);
  if ((uVar2 & 8) == 0) {
    if ((uVar2 & 4) != 0) {
      uVar6 = uVar6 | 2;
    }
  }
  else {
    uVar6 = uVar6 & 0xfffffffd;
  }
  if ((uVar2 & 1) == 0) {
    if ((uVar2 & 2) != 0) {
      uVar6 = uVar6 | 1;
    }
  }
  else {
    uVar6 = uVar6 & 0xfffffffe;
  }
  if ((int)uVar6 < 4) {
    uVar6 = uVar6 & ~((int)uVar6 >> 0x1f);
  }
  else {
    uVar6 = 3;
  }
  if ((((int)*(char *)(param_1 + 0x65) & 1 << uVar6) != 0) &&
     (uVar6 != (int)*(char *)(param_1 + 100))) {
    *(char *)(param_1 + 100) = (char)uVar6;
    zz_00f0468_(0,0x77,0);
  }
  puVar4 = PTR_DAT_80433944;
  if ((*(ushort *)(param_1 + 0xe) & 0x200) == 0) {
    if ((*(ushort *)(param_1 + 0xe) & 0x180) != 0) {
      if ((int)*(char *)(param_1 + 100) ==
          (int)(char)PTR_DAT_80433944[*(byte *)(param_1 + 0x3c) + 0x28]) {
        *(undefined1 *)(param_1 + 1) = 6;
        *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) & 0xef;
        *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) & 0xef;
        *(undefined2 *)(param_1 + 4) = 4;
        zz_00f0468_(0,0x7a,0);
      }
      else {
        iVar3 = ((byte)PTR_DAT_80433944[*(char *)(param_1 + 100) + 0x20] & 0xf) * 0x80;
        PTR_DAT_80433944[0x85] = PTR_DAT_80433944[iVar3 + 0x166];
        PTR_DAT_80433944[0x86] = puVar4[iVar3 + 0x161];
        PTR_DAT_80433944[0x87] = puVar4[iVar3 + 0x13f];
        if ((PTR_DAT_80433944[0x87] & 4) == 0) {
          if ((char)PTR_DAT_80433944[0x90] < '\x02') {
            *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x02';
          }
          else {
            *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x01';
          }
          cVar8 = '\0';
          puVar4[iVar3 + 0x161] = 0;
          iVar5 = 0x14;
          iVar7 = 0;
          puVar4[iVar3 + 0x166] = *(undefined1 *)(param_1 + 0x66);
          *(undefined4 *)(puVar4 + iVar3 + 0x140) =
               (&DAT_803bfe00)[(char)PTR_DAT_80433944[(char)puVar4[iVar3 + 0x166] + 0x88]];
          puVar4[iVar3 + 0x160] = 0;
          do {
            if (*(char *)(*(int *)(puVar4 + iVar3 + 0x140) + iVar7 + 0x29) != '\0') {
              cVar1 = puVar4[iVar3 + 0x160];
              puVar4[iVar3 + 0x160] = cVar1 + '\x01';
              puVar4[(int)cVar1 + iVar3 + 0x14c] = cVar8;
            }
            iVar7 = iVar7 + 0x6c;
            cVar8 = cVar8 + '\x01';
            iVar5 = iVar5 + -1;
          } while (iVar5 != 0);
        }
        else {
          *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x02';
        }
        *(undefined1 *)(param_1 + 2) = 0;
        *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) & 0xef;
        *(byte *)(param_1 + 0x3f) = *(byte *)(param_1 + 0x3f) | 0x10;
        *(undefined2 *)(param_1 + 4) = 4;
        zz_00f0468_(0,0x7b,0);
      }
    }
  }
  else {
    *(undefined1 *)(param_1 + 1) = 6;
    *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) & 0xef;
    *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) & 0xef;
    *(undefined2 *)(param_1 + 4) = 4;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 8017265c  FUN_8017265c ====

void FUN_8017265c(int param_1)

{
  (*(code *)(&PTR_LAB_803517e8)[*(char *)(param_1 + 2)])
            (param_1,PTR_DAT_80433944 +
                     ((byte)PTR_DAT_80433944[*(char *)(param_1 + 100) + 0x20] & 0xf) * 0x80 + 0x100)
  ;
  return;
}



// ==== 80172724  FUN_80172724 ====

void FUN_80172724(int param_1,int param_2)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  
  if (*(short *)(param_1 + 4) == 0) {
    iVar6 = (int)*(char *)(param_2 + 0x66);
    if ((*(ushort *)(param_1 + 8) & 1) == 0) {
      if ((*(ushort *)(param_1 + 8) & 2) != 0) {
        for (iVar6 = iVar6 + 1; (char)PTR_DAT_80433944[0x90] <= iVar6;
            iVar6 = iVar6 - (char)PTR_DAT_80433944[0x90]) {
        }
        *(undefined1 *)(param_2 + 0x67) = 2;
      }
    }
    else {
      for (iVar6 = iVar6 + -1; iVar6 < 0; iVar6 = iVar6 + (char)PTR_DAT_80433944[0x90]) {
      }
      *(undefined1 *)(param_2 + 0x67) = 1;
    }
    if (iVar6 != *(char *)(param_2 + 0x66)) {
      cVar5 = '\0';
      *(undefined1 *)(param_2 + 0x61) = 0;
      puVar2 = PTR_DAT_80433944;
      iVar3 = 0x14;
      iVar4 = 0;
      *(char *)(param_2 + 0x66) = (char)iVar6;
      *(undefined4 *)(param_2 + 0x40) = (&DAT_803bfe00)[(char)puVar2[(char)iVar6 + 0x88]];
      *(undefined1 *)(param_2 + 0x60) = 0;
      do {
        if (*(char *)(*(int *)(param_2 + 0x40) + iVar4 + 0x29) != '\0') {
          cVar1 = *(char *)(param_2 + 0x60);
          *(char *)(param_2 + 0x60) = cVar1 + '\x01';
          *(char *)(param_2 + cVar1 + 0x4c) = cVar5;
        }
        iVar4 = iVar4 + 0x6c;
        cVar5 = cVar5 + '\x01';
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
      *(undefined2 *)(param_1 + 4) = 9;
      zz_00f0468_(0,0x77,0);
    }
  }
  else {
    *(short *)(param_1 + 4) = *(short *)(param_1 + 4) + -1;
  }
  if ((*(ushort *)(param_1 + 0xe) & 0x200) == 0) {
    if ((*(ushort *)(param_1 + 0xe) & 0x180) != 0) {
      *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
      *(undefined2 *)(param_1 + 4) = 0x10;
      *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) & 0xfd;
      *(byte *)(param_2 + 0x3f) = *(byte *)(param_2 + 0x3f) | 2;
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    cVar5 = '\0';
    iVar6 = 0x14;
    *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + -2;
    iVar3 = 0;
    *(undefined1 *)(param_1 + 2) = 0;
    *(undefined2 *)(param_1 + 4) = 2;
    *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) & 0xfd;
    *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) & 0xfd;
    *(undefined *)(param_2 + 0x66) = PTR_DAT_80433944[0x85];
    *(undefined *)(param_2 + 0x61) = PTR_DAT_80433944[0x86];
    *(undefined *)(param_2 + 0x3f) = PTR_DAT_80433944[0x87];
    *(undefined4 *)(param_2 + 0x40) =
         (&DAT_803bfe00)[(char)PTR_DAT_80433944[*(char *)(param_2 + 0x66) + 0x88]];
    *(undefined1 *)(param_2 + 0x60) = 0;
    do {
      if (*(char *)(*(int *)(param_2 + 0x40) + iVar3 + 0x29) != '\0') {
        cVar1 = *(char *)(param_2 + 0x60);
        *(char *)(param_2 + 0x60) = cVar1 + '\x01';
        *(char *)(param_2 + cVar1 + 0x4c) = cVar5;
      }
      iVar3 = iVar3 + 0x6c;
      cVar5 = cVar5 + '\x01';
      iVar6 = iVar6 + -1;
    } while (iVar6 != 0);
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 80172a14  FUN_80172a14 ====

void FUN_80172a14(int param_1)

{
  (*(code *)(&PTR_LAB_803517f8)[*(char *)(param_1 + 2)])
            (param_1,PTR_DAT_80433944 +
                     ((byte)PTR_DAT_80433944[*(char *)(param_1 + 100) + 0x20] & 0xf) * 0x80 + 0x100)
  ;
  return;
}



// ==== 80172adc  FUN_80172adc ====

void FUN_80172adc(int param_1,int param_2)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  char cVar4;
  int iVar5;
  
  iVar5 = (int)*(char *)(param_2 + 0x61);
  if ((*(ushort *)(param_1 + 0xc) & 1) == 0) {
    if ((*(ushort *)(param_1 + 0xc) & 2) != 0) {
      for (iVar5 = iVar5 + 1; *(char *)(param_2 + 0x60) <= iVar5;
          iVar5 = iVar5 - (*(char *)(param_2 + 0x60) + 1)) {
      }
    }
  }
  else {
    for (iVar5 = iVar5 + -1; iVar5 < -1; iVar5 = *(char *)(param_2 + 0x60) + iVar5 + 1) {
    }
  }
  if (iVar5 != *(char *)(param_2 + 0x61)) {
    *(char *)(param_2 + 0x61) = (char)iVar5;
    zz_00f0468_(0,0x77,0);
  }
  uVar2 = *(ushort *)(param_1 + 0xe);
  if ((uVar2 & 0x200) == 0) {
    if ((uVar2 & 0x10) == 0) {
      if ((uVar2 & 0x180) != 0) {
        if (((*(char *)(param_2 + 0x61) < '\0') ||
            (iVar5 = zz_01cce38_(*(int *)(param_2 + 0x40),
                                 (int)*(char *)(param_2 + *(char *)(param_2 + 0x61) + 0x4c),
                                 *(int *)(PTR_DAT_80433934 +
                                         ((byte)PTR_DAT_80433944[*(byte *)(param_2 + 0x3c) + 0x28] &
                                         1) * 0x3c + 0x120),1), iVar5 == 0)) &&
           (*(char *)(param_2 + 0x61) != -1)) {
          zz_00f0468_(0,0x7d,0);
        }
        else {
          *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
          *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) & 0xfb;
          *(byte *)(param_2 + 0x3f) = *(byte *)(param_2 + 0x3f) | 4;
          *(undefined2 *)(param_1 + 4) = 0x10;
          zz_00f0468_(0,0x7a,0);
        }
      }
    }
    else if (*(char *)(param_2 + 0x61) < '\0') {
      zz_00f0468_(0,0x7d,0);
    }
    else {
      *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + '\x01';
      *(undefined1 *)(param_1 + 2) = 0;
      *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) & 0xfb;
      *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) & 0xfb;
      *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) | 0x80;
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    if ((char)PTR_DAT_80433944[0x90] < '\x02') {
      cVar4 = '\0';
      iVar5 = 0x14;
      *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + -3;
      iVar3 = 0;
      *(undefined *)(param_2 + 0x66) = PTR_DAT_80433944[0x85];
      *(undefined *)(param_2 + 0x61) = PTR_DAT_80433944[0x86];
      *(undefined *)(param_2 + 0x3f) = PTR_DAT_80433944[0x87];
      *(undefined4 *)(param_2 + 0x40) =
           (&DAT_803bfe00)[(char)PTR_DAT_80433944[*(char *)(param_2 + 0x66) + 0x88]];
      *(undefined1 *)(param_2 + 0x60) = 0;
      do {
        if (*(char *)(*(int *)(param_2 + 0x40) + iVar3 + 0x29) != '\0') {
          cVar1 = *(char *)(param_2 + 0x60);
          *(char *)(param_2 + 0x60) = cVar1 + '\x01';
          *(char *)(param_2 + cVar1 + 0x4c) = cVar4;
        }
        iVar3 = iVar3 + 0x6c;
        cVar4 = cVar4 + '\x01';
        iVar5 = iVar5 + -1;
      } while (iVar5 != 0);
    }
    else {
      *(char *)(param_1 + 1) = *(char *)(param_1 + 1) + -1;
      *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) | 0x80;
    }
    *(undefined1 *)(param_1 + 2) = 0;
    *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) & 0xfb;
    *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) & 0xfb;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 80172e24  FUN_80172e24 ====

void FUN_80172e24(int param_1)

{
  (*(code *)(&PTR_FUN_80351808)[*(char *)(param_1 + 2)])
            (param_1,PTR_DAT_80433944 +
                     ((byte)PTR_DAT_80433944[*(char *)(param_1 + 100) + 0x20] & 0xf) * 0x80 + 0x100)
  ;
  return;
}



// ==== 80172e80  FUN_80172e80 ====

void FUN_80172e80(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
  *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) & 0x7f;
  *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) | 8;
  *(undefined2 *)(param_1 + 4) = 4;
  *(short *)(param_2 + 6) =
       (short)*(char *)(*(int *)(param_2 + 0x40) +
                        *(char *)(param_2 + *(char *)(param_2 + 0x61) + 0x4c) * 0x6c + 0x29);
  *(undefined1 *)(param_2 + 100) = 0;
  *(char *)(param_2 + 0x65) = (char)*(undefined2 *)(param_2 + 6) + '\x02';
  do {
    zz_0167334_(*(undefined1 *)(param_2 + 0x3c),10,(char)iVar1);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 5);
  return;
}



// ==== 80172f3c  FUN_80172f3c ====

void FUN_80172f3c(int param_1,int param_2)

{
  char cVar1;
  short sVar2;
  
  if ((*(ushort *)(param_1 + 0xe) & 0x200) == 0) {
    sVar2 = *(short *)(param_1 + 4) + -1;
    *(short *)(param_1 + 4) = sVar2;
    if (sVar2 < 1) {
      cVar1 = *(char *)(param_2 + 0x65) + -1;
      *(char *)(param_2 + 0x65) = cVar1;
      if (cVar1 <= *(char *)(param_2 + 100)) {
        *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
        *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) | 8;
        *(byte *)(param_2 + 0x3f) = *(byte *)(param_2 + 0x3f) & 0xf7;
        *(undefined1 *)(param_2 + 0x65) = *(undefined1 *)(param_2 + 100);
      }
      *(undefined2 *)(param_1 + 4) = 4;
    }
  }
  else {
    *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x02';
    *(undefined2 *)(param_1 + 4) = 4;
    *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) & 0xf7;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 80173000  FUN_80173000 ====

void FUN_80173000(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (*(short *)(param_1 + 4) == 0) {
    iVar2 = (int)*(char *)(param_2 + 100);
    if ((*(ushort *)(param_1 + 8) & 8) == 0) {
      iVar3 = iVar2;
      if ((*(ushort *)(param_1 + 8) & 4) != 0) {
        iVar1 = *(short *)(param_2 + 6) + -1;
        iVar3 = iVar2 + 1;
        if (iVar1 < iVar2 + 1) {
          iVar3 = iVar1;
        }
      }
    }
    else {
      iVar3 = iVar2 + -1;
      if (iVar2 + -1 < 0) {
        iVar3 = 0;
      }
    }
    if (iVar3 != *(char *)(param_2 + 100)) {
      *(char *)(param_2 + 0x65) = (char)iVar3;
      *(char *)(param_2 + 100) = (char)iVar3;
      *(undefined2 *)(param_1 + 4) = 7;
      zz_00f0468_(0,0x77,0);
    }
  }
  else {
    *(short *)(param_1 + 4) = *(short *)(param_1 + 4) + -1;
  }
  if ((*(ushort *)(param_1 + 0xe) & 0x200) != 0) {
    *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
    *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) & 0xf7;
    *(byte *)(param_2 + 0x3e) = *(byte *)(param_2 + 0x3e) & 0xf7;
    *(byte *)(param_2 + 0x3d) = *(byte *)(param_2 + 0x3d) | 0x80;
    *(undefined1 *)(param_2 + 0x65) = *(undefined1 *)(param_2 + 100);
    *(undefined2 *)(param_1 + 4) = 4;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 801731ac  FUN_801731ac ====

void FUN_801731ac(int param_1)

{
  *(undefined1 *)(param_1 + 99) = 0;
  (*(code *)(&PTR_LAB_80351818)[*(char *)(param_1 + 1)])();
  return;
}



// ==== 80173250  FUN_80173250 ====

void FUN_80173250(undefined1 *param_1)

{
  int iVar1;
  
  if (*(short *)(param_1 + 4) == 0) {
    iVar1 = (int)(char)param_1[0x62];
    if ((*(ushort *)(param_1 + 8) & 1) == 0) {
      if ((*(ushort *)(param_1 + 8) & 2) != 0) {
        for (iVar1 = iVar1 + 1; (char)PTR_DAT_80433944[0x6a] <= iVar1;
            iVar1 = iVar1 - (char)PTR_DAT_80433944[0x6a]) {
        }
      }
    }
    else {
      for (iVar1 = iVar1 + -1; iVar1 < 0; iVar1 = iVar1 + (char)PTR_DAT_80433944[0x6a]) {
      }
    }
    if (iVar1 != (char)param_1[0x62]) {
      param_1[0x62] = (char)iVar1;
      *(undefined2 *)(param_1 + 4) = 9;
      zz_00f0468_(0,0x77,0);
    }
  }
  else {
    *(short *)(param_1 + 4) = *(short *)(param_1 + 4) + -1;
  }
  if ((*(ushort *)(param_1 + 0xe) & 0x200) == 0) {
    if ((*(ushort *)(param_1 + 0xe) & 0x180) != 0) {
      param_1[0x3f] = param_1[0x3f] | 0x20;
      if (*(short *)(PTR_DAT_80433944 + (char)param_1[0x62] * 2 + 0x30) < 999) {
        *(short *)(PTR_DAT_80433944 + (char)param_1[0x62] * 2 + 0x30) =
             *(short *)(PTR_DAT_80433944 + (char)param_1[0x62] * 2 + 0x30) + 1;
      }
      param_1[99] = param_1[99] + '\x01';
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *param_1 = 2;
    param_1[1] = 0;
    param_1[0x3d] = param_1[0x3d] & 0xdf;
    param_1[0x3f] = param_1[0x3f] & 0xdf;
    param_1[0x3e] = param_1[0x3e] & 0xdf;
    PTR_DAT_80433944[0x2f] = PTR_DAT_80433944[0x2f] & ~(byte)(1 << (uint)(byte)param_1[0x3c]);
    zz_00f0468_(0,0x7b,0);
  }
  if ((param_1[0x3f] & 0x20) != 0) {
    PTR_DAT_80433944[0x2f] = PTR_DAT_80433944[0x2f] | (byte)(1 << (uint)(byte)param_1[0x3c]);
  }
  return;
}



// ==== 80173464  FUN_80173464 ====

void FUN_80173464(void)

{
  (*(code *)(&PTR_FUN_804347a0)[*(short *)(PTR_DAT_80433944 + 4)])();
  return;
}



