// ==== 80128524  zz_0128524_ ====

void zz_0128524_(int param_1)

{
  char cVar1;
  short sVar2;
  
  sVar2 = *(short *)(param_1 + 0x146) + -1;
  *(short *)(param_1 + 0x146) = sVar2;
  if (sVar2 < 1) {
    zz_0128dd0_(*(int *)(param_1 + 0x90));
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    cVar1 = *(char *)(param_1 + 0x19);
    if (cVar1 == '\x01') {
      zz_012870c_(param_1);
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      zz_01285f8_(param_1);
    }
    if ('\0' < *(char *)(param_1 + 0x144)) {
      *(char *)(param_1 + 0x144) = *(char *)(param_1 + 0x144) + -1;
    }
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x2000;
    cVar1 = *(char *)(param_1 + 0x145) + -1;
    *(char *)(param_1 + 0x145) = cVar1;
    if (cVar1 < '\x01') {
      zz_00f036c_(param_1,0xdf);
      *(undefined1 *)(param_1 + 0x145) = 0x10;
    }
  }
  return;
}



// ==== 801285f8  zz_01285f8_ ====

void zz_01285f8_(int param_1)

{
  float fVar1;
  int iVar2;
  
  iVar2 = zz_0083244_((float *)(param_1 + 0x20));
  if (iVar2 == 0) {
    if (*(char *)(param_1 + 0x1d9) == '\0') {
      if (*(char *)(param_1 + 0x19) != '\0') {
        return;
      }
      *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
      iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x38;
      FUN_80083874((double)*(float *)(&DAT_80330980 + iVar2),param_1);
      FUN_80083ad4((double)*(float *)(&DAT_8033097c + iVar2),param_1,
                   (char)*(undefined2 *)(&DAT_8033097a + iVar2));
      zz_00833ec_(param_1);
      zz_0083524_(param_1);
      iVar2 = zz_0083714_(param_1);
      if ((iVar2 != 0) || (iVar2 = zz_0084170_(param_1), iVar2 != 0)) goto LAB_801286b8;
      if (0 < *(short *)(param_1 + 0x1c)) {
        return;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x144) = 8;
    }
    *(undefined1 *)(param_1 + 0x19) = 1;
    *(undefined1 *)(param_1 + 0x1a) = 0;
  }
  else {
LAB_801286b8:
    fVar1 = FLOAT_80439cc0;
    *(undefined1 *)(param_1 + 0x19) = 1;
    *(undefined1 *)(param_1 + 0x1a) = 1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined2 *)(param_1 + 0x1e) = 0xf;
  }
  return;
}



// ==== 8012870c  zz_012870c_ ====

void zz_012870c_(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar4 = *(int *)(param_1 + 0x90);
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x38;
  if ((*(char *)(param_1 + 0x1d9) != '\0') && (*(char *)(param_1 + 0x144) == '\0')) {
    *(undefined1 *)(param_1 + 0x144) = 3;
  }
  if (*(char *)(param_1 + 0x144) < '\x01') {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  }
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + FLOAT_80439cc4;
    if (*(float *)(&DAT_80330974 + iVar2) <= *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = *(float *)(&DAT_80330974 + iVar2);
      *(undefined1 *)(param_1 + 0x1a) = 3;
    }
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) - FLOAT_80439cc4;
        iVar2 = zz_0083244_((float *)(param_1 + 0x20));
        if ((iVar2 == 0) && (FLOAT_80439cc0 < *(float *)(param_1 + 0x44))) {
          if ('\0' < *(char *)(param_1 + 0x144)) {
            return;
          }
          gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
          gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                              (float *)(param_1 + 0x38));
          gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                           (float *)(param_1 + 0x20));
          return;
        }
        *(float *)(param_1 + 0x44) = FLOAT_80439cc0;
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined2 *)(param_1 + 0x1e) = 0xf;
        return;
      }
      if (cVar1 < '\0') {
        return;
      }
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
      if (0 < *(short *)(param_1 + 0x1e)) {
        return;
      }
      *(undefined1 *)(param_1 + 0x1a) = 2;
      dVar5 = (double)FLOAT_80439ccc;
      *(float *)(param_1 + 0x44) = FLOAT_80439cc8;
      *(short *)(param_1 + 0x1e) = (short)*(undefined4 *)(&DAT_80330990 + iVar2);
      gnt4_PSQUATScale_bl(dVar5,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  iVar3 = iVar4 + (char)(&DAT_80330966)[iVar2] * 0x30;
  local_24 = *(float *)(iVar3 + 0x8e0);
  local_20 = *(undefined4 *)(iVar3 + 0x8f0);
  local_1c = *(undefined4 *)(iVar3 + 0x900);
  dVar5 = gnt4_PSVECSquareDistance_bl(&local_24,(float *)(param_1 + 0x20));
  if ((double)FLOAT_80439cc0 < dVar5) {
    dVar6 = 1.0 / SQRT(dVar5);
    dVar6 = DOUBLE_80439cd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80439cd8);
    dVar6 = DOUBLE_80439cd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80439cd8);
    dVar5 = (double)(float)(dVar5 * DOUBLE_80439cd0 * dVar6 *
                                    -(dVar5 * dVar6 * dVar6 - DOUBLE_80439cd8));
  }
  if ((double)*(float *)(param_1 + 0x44) <= dVar5) {
    if (*(char *)(param_1 + 0x144) < '\x01') {
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
      if (*(short *)(param_1 + 0x1e) < 1) {
        *(short *)(param_1 + 0x1e) = (short)*(undefined4 *)(&DAT_80330990 + iVar2);
        zz_006c440_((double)*(float *)(&DAT_80330994 + iVar2),param_1,&local_24);
      }
      else {
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                         (float *)(param_1 + 0x20));
      }
    }
  }
  else {
    zz_0128dd0_(iVar4);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801289ec  FUN_801289ec ====

void FUN_801289ec(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80128a28  FUN_80128a28 ====

void FUN_80128a28(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80128a48  FUN_80128a48 ====

/* WARNING: Removing unreachable block (ram,0x80128ce8) */

void FUN_80128a48(int param_1)

{
  float local_68;
  undefined4 local_64;
  undefined4 local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float afStack_38 [13];
  
  gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
  local_50 = FLOAT_80439cc0;
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  local_5c = *(float *)(param_1 + 0x38);
  local_58 = *(float *)(param_1 + 0x3c);
  local_54 = *(float *)(param_1 + 0x40);
  if (local_50 == *(float *)(param_1 + 0x3c)) {
    local_40 = local_50;
    local_44 = FLOAT_80439ce0;
    local_3c = local_50;
    local_4c = FLOAT_80439ce0;
    local_48 = local_50;
    local_5c = local_50;
    local_58 = local_50;
    local_54 = FLOAT_80439ce0;
  }
  else {
    if (local_54 * local_54 + local_5c * local_5c + local_58 * local_58 <= local_50) {
      local_5c = local_50;
      local_58 = local_50;
      local_54 = FLOAT_80439ccc;
    }
    local_50 = local_5c;
    local_48 = local_54;
    local_4c = FLOAT_80439cc0;
    if (FLOAT_80439cc0 < local_54 * local_54 + local_5c * local_5c + FLOAT_80439cc0 * FLOAT_80439cc0
       ) {
      if (*(float *)(param_1 + 0x3c) < FLOAT_80439cc0) {
        gnt4_PSVECCrossProduct_bl(&local_5c,&local_50,&local_50);
      }
      else {
        gnt4_PSVECCrossProduct_bl(&local_50,&local_5c,&local_50);
      }
    }
    else {
      gnt4_PSVECSubtract_bl
                ((float *)(param_1 + 0x20),(float *)(*(int *)(param_1 + 0x90) + 0x20),&local_50);
      gnt4_PSVECCrossProduct_bl(&local_50,&local_5c,&local_50);
    }
    if (local_48 * local_48 + local_50 * local_50 + local_4c * local_4c <= FLOAT_80439cc0) {
      local_4c = FLOAT_80439cc0;
      local_50 = FLOAT_80439ce0;
      local_48 = FLOAT_80439cc0;
    }
    gnt4_PSVECCrossProduct_bl(&local_50,&local_5c,&local_50);
    if (local_48 * local_48 + local_50 * local_50 + local_4c * local_4c <= FLOAT_80439cc0) {
      local_50 = FLOAT_80439cc0;
      local_4c = FLOAT_80439ce0;
      local_48 = FLOAT_80439cc0;
    }
    gnt4_PSVECCrossProduct_bl(&local_50,&local_5c,&local_44);
    if (local_3c * local_3c + local_44 * local_44 + local_40 * local_40 <= FLOAT_80439cc0) {
      local_40 = FLOAT_80439cc0;
      local_44 = FLOAT_80439ccc;
      local_3c = FLOAT_80439cc0;
    }
    gnt4_PSVECNormalize_bl(&local_44,&local_44);
    gnt4_PSVECNormalize_bl(&local_50,&local_50);
    gnt4_PSVECNormalize_bl(&local_5c,&local_5c);
  }
  *(float *)(param_1 + 0x114) = local_44;
  *(float *)(param_1 + 0x124) = local_40;
  *(float *)(param_1 + 0x134) = local_3c;
  *(float *)(param_1 + 0x118) = local_50;
  *(float *)(param_1 + 0x128) = local_4c;
  *(float *)(param_1 + 0x138) = local_48;
  *(float *)(param_1 + 0x11c) = local_5c;
  *(float *)(param_1 + 300) = local_58;
  *(float *)(param_1 + 0x13c) = local_54;
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80439ce4 *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                             0x3ff0000000000000)),afStack_38,0x79);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)&DAT_80330958,&local_68);
  *(float *)(param_1 + 0x120) = local_68;
  *(undefined4 *)(param_1 + 0x130) = local_64;
  *(undefined4 *)(param_1 + 0x140) = local_60;
  gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                     (double)*(float *)(param_1 + 0x60),afStack_38);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  return;
}



// ==== 80128d74  FUN_80128d74 ====

void FUN_80128d74(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 80128dd0  zz_0128dd0_ ====

void zz_0128dd0_(int param_1)

{
  if (*(char *)(param_1 + 0x5db) == '<') {
    return;
  }
  if (*(char *)(param_1 + 0x145) == '\x03') {
    return;
  }
  *(undefined1 *)(param_1 + 0x145) = 0;
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  return;
}



// ==== 80128df8  FUN_80128df8 ====

bool FUN_80128df8(int param_1,undefined1 param_2,undefined1 param_3,int param_4)

{
  short sVar1;
  bool bVar3;
  undefined1 *puVar2;
  int iVar4;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((sVar1 == 0x601) || (sVar1 == 0x617)) || (sVar1 == 0x20e)) {
    iVar4 = 1;
    if (-1 < param_4) {
      iVar4 = 2;
    }
    puVar2 = zz_0088aa0_(param_1,3,8,0,iVar4);
    bVar3 = puVar2 != (undefined1 *)0x0;
    if (bVar3) {
      *puVar2 = 1;
      puVar2[0x13] = param_2;
      puVar2[0x11] = param_3;
      puVar2[0x10] = 0x34;
      *(code **)(puVar2 + 0xc) = FUN_80128f54;
      *(code **)(puVar2 + 0x10c) = FUN_80129534;
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
      *(short *)(puVar2 + 0x158) = (short)param_4;
    }
  }
  else {
    bVar3 = false;
  }
  return bVar3;
}



// ==== 80128f54  FUN_80128f54 ====

void FUN_80128f54(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80330b74)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80128fec  FUN_80128fec ====

void FUN_80128fec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined *puVar8;
  uint uVar9;
  int iVar10;
  double dVar11;
  undefined8 uVar12;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  puVar8 = &DAT_80330b08;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  uVar9 = (uint)*(byte *)(param_9 + 0x11);
  iVar10 = *(int *)(param_9 + 0x90);
  iVar6 = *(char *)(param_9 + 0x13) * 0x24;
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  uVar4 = (uint)(byte)(&DAT_803309fe)[iVar6];
  iVar5 = uVar9 * 0x24;
  *(undefined *)(param_9 + 0x98) = (&DAT_803309fe)[iVar6];
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar3 = iVar5;
  iVar7 = iVar6;
  zz_0089100_(param_9,0,1);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_803309f8 + iVar6);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_803309fc + iVar6);
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)(iVar10 + *(short *)(&DAT_803309ea + iVar6) * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar10 + *(short *)(&DAT_803309ea + iVar6) * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar10 + *(short *)(&DAT_803309ea + iVar6) * 0x30 + 0x8f8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar10 + *(short *)(&DAT_803309ea + iVar6) * 0x30 + 0x8d4),
             (float *)(iVar6 + -0x7fccf614),(float *)(param_9 + 0x20));
  if ((&DAT_803309ff)[iVar6] == '\0') {
    zz_0083d60_(param_9,iVar10,1);
  }
  else {
    *(undefined4 *)(param_9 + 0x38) =
         *(undefined4 *)(iVar10 + *(short *)(&DAT_803309ea + iVar6) * 0x30 + 0x8d4);
    *(undefined4 *)(param_9 + 0x3c) =
         *(undefined4 *)(iVar10 + *(short *)(&DAT_803309ea + iVar6) * 0x30 + 0x8e4);
    *(undefined4 *)(param_9 + 0x40) =
         *(undefined4 *)(iVar10 + *(short *)(&DAT_803309ea + iVar6) * 0x30 + 0x8f4);
    if ((char)(&DAT_803309ff)[iVar6] < '\0') {
      gnt4_PSQUATScale_bl((double)FLOAT_80439ce8,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38)
                         );
    }
  }
  local_28 = *(float *)(param_9 + 0x38);
  local_24 = *(undefined4 *)(param_9 + 0x3c);
  local_20 = *(undefined4 *)(param_9 + 0x40);
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80330b18 + iVar5),(float *)(param_9 + 0x38),
                      (float *)(param_9 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439cec,&local_28,&local_28);
  gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_28,(float *)(param_9 + 0x20));
  fVar1 = FLOAT_80439cf0;
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80330b18 + iVar5);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_80330b0a + iVar5);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_80330b0c + iVar5);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_80330b0e + iVar5);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  dVar11 = (double)*(float *)(&DAT_80330b1c + iVar5);
  *(float *)(param_9 + 0x144) = *(float *)(&DAT_80330b1c + iVar5);
  uVar2 = *(undefined4 *)(&DAT_80330a04 + iVar6);
  *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(&DAT_80330a00 + iVar6);
  *(undefined4 *)(param_9 + 0x14c) = uVar2;
  *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(&DAT_80330a08 + iVar6);
  *(float *)(param_9 + 0x154) = fVar1;
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  iVar10 = zz_0006f98_(iVar10);
  uVar12 = zz_0006fb4_(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar10 + 0x600),*(int *)(param_9 + 0xe0),
                       (int)*(short *)(&DAT_803309e8 + iVar6),uVar4,iVar3,iVar7,puVar8,uVar9);
  if (-1 < *(short *)(param_9 + 0x158)) {
    zz_000726c_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe4),(float *)(int)*(short *)(param_9 + 0x158),
                (int)*(char *)(param_9 + 0x88),iVar3,iVar7,puVar8,uVar9);
  }
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar3 = zz_008ac80_(param_9,(int)*(short *)(&DAT_80330b08 + iVar5));
  if (iVar3 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0xa8) = 1;
    if (-1 < *(short *)(&DAT_80330b24 + iVar5)) {
      zz_00c74ec_(param_9,(int)*(short *)(&DAT_80330b24 + iVar5));
    }
    zz_00f036c_(param_9,(int)*(short *)(&DAT_80330b28 + iVar5));
  }
  return;
}



// ==== 801292c8  FUN_801292c8 ====

void FUN_801292c8(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  
  fVar1 = FLOAT_80439cf8;
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x24;
  if (-1 < *(short *)(param_1 + 0x158)) {
    *(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x154) + FLOAT_80439cf4;
    if (fVar1 < *(float *)(param_1 + 0x154)) {
      *(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x154) - FLOAT_80439cfc;
    }
  }
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar3 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar3 == 0) {
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_01294cc_(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        if (*(short *)(param_1 + 0x1c) < 1) {
          zz_01294cc_(param_1);
          FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
        }
        else {
          if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x144)) {
            *(float *)(param_1 + 0x44) =
                 *(float *)(param_1 + 0x44) + *(float *)(&DAT_80330b20 + iVar2);
          }
          else {
            *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x144);
          }
          gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
          gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                              (float *)(param_1 + 0x38));
          FUN_80083874((double)*(float *)(&DAT_80330b14 + iVar2),param_1);
          FUN_80083ad4((double)*(float *)(&DAT_80330b10 + iVar2),param_1,
                       (char)*(undefined2 *)(&DAT_80330b0c + iVar2));
          *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
          zz_00833ec_(param_1);
          zz_0083610_(param_1,(float *)(param_1 + 0x144));
          iVar3 = zz_0083714_(param_1);
          if (iVar3 == 0) {
            iVar3 = zz_0084170_(param_1);
            if (iVar3 != 0) {
              zz_01294cc_(param_1);
              if (-1 < *(short *)(&DAT_80330b26 + iVar2)) {
                zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),
                            (char)*(short *)(&DAT_80330b26 + iVar2));
              }
            }
          }
          else {
            zz_01294cc_(param_1);
          }
        }
      }
    }
    else {
      zz_01294cc_(param_1);
    }
  }
  else {
    zz_01294cc_(param_1);
    if (-1 < *(short *)(&DAT_80330b26 + iVar2)) {
      zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x2a0),(char)*(short *)(&DAT_80330b26 + iVar2));
    }
  }
  return;
}



// ==== 801294cc  zz_01294cc_ ====

void zz_01294cc_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80129508  FUN_80129508 ====

void FUN_80129508(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 80129514  FUN_80129514 ====

void FUN_80129514(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80129534  FUN_80129534 ====

void FUN_80129534(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  float *pfVar2;
  int iVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  float afStack_68 [12];
  float afStack_38 [12];
  
  pfVar2 = (float *)(param_9 + 0x148);
  iVar3 = *(int *)(param_9 + 0x90);
  uVar4 = zz_00456a0_((float *)(param_9 + 0x114),afStack_38,pfVar2);
  zz_00076d0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_38,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  uVar1 = 1;
  if (*(char *)(iVar3 + 0x3ec) == '\x04') {
    uVar1 = 0x44;
  }
  zz_00097b4_(*(int *)(param_9 + 0xe0),uVar1);
  if (-1 < *(short *)(param_9 + 0x158)) {
    dVar5 = (double)FLOAT_80439d00;
    dVar6 = dVar5;
    gnt4_PSMTXScale_bl(dVar5,dVar5,dVar5,afStack_68);
    gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_68,afStack_38);
    gnt4_PSMTXRotRad_bl((double)*(float *)(param_9 + 0x154),afStack_68,0x79);
    pfVar2 = afStack_38;
    uVar4 = gnt4_PSMTXConcat_bl(pfVar2,afStack_68,pfVar2);
    zz_00076d0_(uVar4,dVar5,dVar6,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4),
                afStack_38,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe4),0x44);
  }
  return;
}



// ==== 80129728  FUN_80129728 ====

void FUN_80129728(int param_1)

{
  zz_00c74ec_(param_1,0x1f);
  if (*(short *)(param_1 + 1000) == 0x606) {
    zz_012aa24_(param_1,0xc);
    zz_012aa24_(param_1,0xd);
  }
  else if (*(short *)(param_1 + 1000) == 0x61a) {
    zz_012aa24_(param_1,0xe);
    zz_012aa24_(param_1,0xf);
  }
  return;
}



// ==== 8012980c  FUN_8012980c ====

void FUN_8012980c(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80331928)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80129854  FUN_80129854 ====

void FUN_80129854(int param_1,uint param_2)

{
  if ((param_2 & 1) != 0) {
    *(undefined1 *)(param_1 + 0xaf) = 1;
    if (*(short *)(param_1 + 1000) == 0x606) {
      zz_001ab6c_(param_1,0x29);
    }
    else if (*(short *)(param_1 + 1000) == 0x61a) {
      zz_001ab6c_(param_1,0x68);
    }
  }
  if ((param_2 & 2) != 0) {
    *(undefined1 *)(param_1 + 0xaf) = 1;
    if (*(short *)(param_1 + 1000) == 0x606) {
      zz_001ab6c_(param_1,0x28);
    }
    else if (*(short *)(param_1 + 1000) == 0x61a) {
      zz_001ab6c_(param_1,0x67);
    }
  }
  return;
}



// ==== 8012990c  FUN_8012990c ====

void FUN_8012990c(int param_1)

{
  (*(code *)(&PTR_FUN_8033193c)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80129948  FUN_80129948 ====

void FUN_80129948(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  (*(code *)(&PTR_FUN_80331948)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8012999c  FUN_8012999c ====

void FUN_8012999c(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8033195c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801299e4  FUN_801299e4 ====

void FUN_801299e4(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80439d08;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d0dc_(param_1,0xc1,0);
  zz_004beb8_((double)FLOAT_80439d0c,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  fVar1 = FLOAT_80439d10;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439d14,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_80439d10;
  return;
}



// ==== 80129ac4  FUN_80129ac4 ====

/* WARNING: Removing unreachable block (ram,0x80129bac) */
/* WARNING: Removing unreachable block (ram,0x80129ad4) */

void FUN_80129ac4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_80439d10;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_80439d10;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0046698_(param_1);
    FUN_8012a308(param_1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439d14,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80439d18 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80129bc8  FUN_80129bc8 ====

void FUN_80129bc8(int param_1)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(float *)(param_1 + 0x558) <= FLOAT_80439d10) {
    if (((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
      iVar1 = zz_006dbe0_(param_1,0,1,0);
      if ((iVar1 != 0) && ('\0' < *(char *)(param_1 + 0x6ef))) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
          zz_006a3d0_(param_1,'\0',3,0);
          return;
        }
        zz_006bf80_(param_1);
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        if (*(char *)(param_1 + 0x1cef) < '\0') {
          zz_004beb8_((double)FLOAT_80439d0c,param_1,0xf,2,1,0xffffffff,0xffffffff);
          return;
        }
        zz_004beb8_((double)FLOAT_80439d0c,param_1,0xf,2,1,4,1);
        return;
      }
      goto LAB_80129cf4;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_1 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_80439d14,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00679d0_(param_1);
    dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if (dVar2 <= (double)FLOAT_80439d18) {
      return;
    }
    zz_00b22f4_(param_1);
    return;
  }
LAB_80129cf4:
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 80129d6c  FUN_80129d6c ====

void FUN_80129d6c(int param_1)

{
  (*(code *)(&PTR_FUN_80331968)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80129da8  FUN_80129da8 ====

void FUN_80129da8(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  
  fVar1 = FLOAT_80439d1c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006dee8_(param_1,1);
  uVar2 = *(uint *)(param_1 + 0x5e0);
  iVar3 = 4;
  if ((uVar2 & 0x80) != 0) {
    iVar3 = 6;
  }
  if ((uVar2 & 0x10) != 0) {
    iVar3 = 2;
  }
  if (((uVar2 & 0x20) != 0) &&
     (iVar3 = *(char *)(param_1 + 0x1d10) + 8, *(char *)(param_1 + 0x5db) == '\x0f')) {
    iVar3 = 0;
  }
  zz_004beb8_((double)FLOAT_80439d0c,param_1,1,2,iVar3 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  return;
}



// ==== 80129e58  FUN_80129e58 ====

void FUN_80129e58(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,1);
  }
  fVar2 = FLOAT_80439d10;
  if (iVar3 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else {
    if ((iVar3 < 1) &&
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
      return;
    }
    if (*(char *)(param_1 + 0x1cef) != '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      FUN_8012a308(param_1);
    }
  }
  return;
}



// ==== 80129f40  FUN_80129f40 ====

void FUN_80129f40(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  zz_004cd24_(param_9,1);
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_80439d10) {
    if (((*(uint *)(param_9 + 0x5b4) & 0x200) != 0) && (*(char *)(param_9 + 0x1cef) < '\0')) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if ((iVar1 != 0) && ('\0' < *(char *)(param_9 + 0x6ef))) {
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        uVar2 = *(uint *)(param_9 + 0x5e0);
        if (((uVar2 & 0x40) == 0) && (*(char *)(param_9 + 0x5e4) != '\x04')) {
          if ((uVar2 & 0x10) == 0) {
            if ((uVar2 & 0x20) == 0) {
              zz_006a3d0_(param_9,'\0',0,2);
              return;
            }
            *(undefined1 *)(param_9 + 0x581) = 2;
            iVar1 = *(char *)(param_9 + 0x1d10) + 9;
            if (*(char *)(param_9 + 0x5db) == '\x0f') {
              iVar1 = 1;
            }
          }
          else {
            iVar1 = 3;
            *(undefined1 *)(param_9 + 0x581) = 1;
          }
        }
        else {
          iVar1 = 5;
          *(undefined1 *)(param_9 + 0x581) = 3;
          if ((*(uint *)(param_9 + 0x5e0) & 0x80) != 0) {
            iVar1 = 7;
          }
        }
        if ((*(char *)(param_9 + 0x1cef) < '\0') &&
           (iVar1 == (int)*(char *)(param_9 + 0x1afd) + *(char *)(param_9 + 0x1afc) * 0x1000)) {
          zz_004beb8_((double)FLOAT_80439d0c,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        zz_004beb8_((double)FLOAT_80439d0c,param_9,1,2,iVar1,4,1);
        return;
      }
      goto LAB_8012a0f4;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
    zz_006dee8_(param_9,1);
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_8012a0f4:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8012a128  FUN_8012a128 ====

void FUN_8012a128(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80331974)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8012a170  FUN_8012a170 ====

void FUN_8012a170(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80439d08;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d0dc_(param_1,0x81,0);
  FUN_80067310((double)FLOAT_80439d20,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_80439d0c,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
              0xffffffff);
  zz_004beb8_((double)FLOAT_80439d0c,param_1,2,0,0xd,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439d10;
  return;
}



// ==== 8012a220  FUN_8012a220 ====

void FUN_8012a220(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  FUN_80067310((double)FLOAT_80439d20,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439d10;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if (fVar2 < fVar1) {
    iVar3 = zz_006d0dc_(param_1,0x81,0);
    if (iVar3 == 0) goto LAB_8012a2dc;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_8012a308(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
LAB_8012a2dc:
  if (FLOAT_80439d18 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8012a308  FUN_8012a308 ====

void FUN_8012a308(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_80439d24;
  fVar1 = FLOAT_80439d1c;
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  if (*(short *)(param_1 + 1000) == 0x61a) {
    *(float *)(param_1 + 0x558) = FLOAT_80439d28;
  }
  *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
  iVar3 = zz_006dbe0_(param_1,0,1,1);
  if (iVar3 != 0) {
    if (*(short *)(param_1 + 1000) == 0x606) {
      zz_00c3be0_(param_1,0x1e);
      zz_00c3be0_(param_1,0x1f);
    }
    else if (*(short *)(param_1 + 1000) == 0x61a) {
      zz_0082824_(param_1,0x6e);
      zz_0082824_(param_1,0x6f);
    }
  }
  return;
}



// ==== 8012a3cc  FUN_8012a3cc ====

void FUN_8012a3cc(int param_1)

{
  (*(code *)(&PTR_FUN_80331980)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8012a408  FUN_8012a408 ====

void FUN_8012a408(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8012a448  FUN_8012a448 ====

void FUN_8012a448(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8012a488  FUN_8012a488 ====

void FUN_8012a488(int param_1)

{
  zz_0178394_(param_1);
  return;
}



// ==== 8012a4b0  FUN_8012a4b0 ====

void FUN_8012a4b0(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x606) {
    FUN_8012a4e4(param_1);
  }
  else {
    FUN_8012a50c(param_1);
  }
  return;
}



// ==== 8012a4e4  FUN_8012a4e4 ====

void FUN_8012a4e4(int param_1)

{
  zz_017a374_(param_1);
  return;
}



// ==== 8012a50c  FUN_8012a50c ====

void FUN_8012a50c(int param_1)

{
  (*(code *)(&PTR_FUN_803319ec)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8012a548  FUN_8012a548 ====

void FUN_8012a548(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 1;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 2;
  }
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006e39c_(param_1,0xc1,2,0x2000,(float *)(param_1 + 0x524));
  }
  else {
    zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  }
  fVar2 = FLOAT_80439d10;
  *(float *)(param_1 + 0x50) = FLOAT_80439d10;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439d14,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80439d0c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8012a68c  FUN_8012a68c ====

void FUN_8012a68c(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006e39c_(param_1,0xc1,2,0x2000,(float *)(param_1 + 0x524));
  }
  else {
    zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439d14,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6f7) = 2;
    iVar1 = zz_006dbe0_(param_1,2,1,1);
    if (iVar1 == 0) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        zz_006a474_(param_1);
      }
      else {
        zz_006a5a4_(param_1);
      }
      *(float *)(param_1 + 0x694) = FLOAT_80439d24 + *(float *)(param_1 + 0x1dc8);
    }
    else {
      zz_00e19a8_(param_1,0xc,param_1 + 0x6f7);
      zz_00e19a8_(param_1,0xd,param_1 + 0x6f7);
    }
  }
  return;
}



// ==== 8012a7d8  FUN_8012a7d8 ====

void FUN_8012a7d8(int param_1)

{
  *(undefined1 *)(param_1 + 0x6f7) = 2;
  zz_004cd24_(param_1,0xf);
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006e39c_(param_1,0xc1,2,0x2000,(float *)(param_1 + 0x524));
  }
  else {
    zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_80439d20,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_80439d14,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6f7) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 8012a8e4  FUN_8012a8e4 ====

void FUN_8012a8e4(int param_1)

{
  float fVar1;
  double dVar2;
  int iVar3;
  
  dVar2 = DOUBLE_80439d38;
  fVar1 = FLOAT_80439d2c;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80439d38) * FLOAT_80439d2c);
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) - dVar2
                           ) * fVar1);
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439d20,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  if (((iVar3 != 0) && ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) &&
     (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439d30 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 8012aa24  zz_012aa24_ ====

void zz_012aa24_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((((sVar1 == 0x604) || (sVar1 == 0x605)) || (sVar1 == 0x613)) ||
        ((sVar1 == 0x618 || (sVar1 == 0x619)))) ||
       ((sVar1 == 0x606 || ((sVar1 == 0x607 || (sVar1 == 0x61a)))))) ||
      ((sVar1 == 0x61b || (sVar1 == 0x627)))) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_8012ab74;
    *(code **)(puVar2 + 0x10c) = FUN_8012ade4;
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



// ==== 8012ab74  FUN_8012ab74 ====

void FUN_8012ab74(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80332120)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8012abc8  FUN_8012abc8 ====

void FUN_8012abc8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
  iVar5 = *(byte *)(param_9 + 0x18) + 1;
  *(char *)(param_9 + 0x18) = (char)iVar5;
  iVar6 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar3 = *(char *)(param_9 + 0x11) * 0x18;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80439d40;
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80331f42 + iVar3);
  uVar2 = *(undefined4 *)(&DAT_80331f48 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80331f44 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80331f4c + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80331f50 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80331f54 + iVar3);
  *(char *)(param_9 + 0x12) = (char)*(undefined2 *)(&DAT_80331f56 + iVar3);
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  iVar6 = zz_0006f98_(iVar6);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80331f40 + iVar3),iVar6 + 0xc28,iVar5,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar6 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80331f40 + iVar3);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,iVar5,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,iVar5,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80439d44,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_012acf4_(param_9);
  return;
}



// ==== 8012acf4  zz_012acf4_ ====

void zz_012acf4_(int param_1)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  dVar4 = DOUBLE_80439d58;
  fVar3 = FLOAT_80439d4c;
  fVar2 = FLOAT_80439d40;
  bVar1 = *(byte *)(*(int *)(param_1 + 0x90) + 0x6e8);
  if ((bVar1 & *(byte *)(param_1 + 0x12)) == 0) {
    if ((char)bVar1 < '\x01') {
      *(float *)(param_1 + 0x58) = FLOAT_80439d40;
    }
    else {
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) - FLOAT_80439d48;
      if (*(float *)(param_1 + 0x58) < fVar2) {
        *(float *)(param_1 + 0x58) = fVar2;
      }
    }
  }
  else if ((char)bVar1 < '\x01') {
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + FLOAT_80439d50;
    if (dVar4 < (double)*(float *)(param_1 + 0x58)) {
      *(float *)(param_1 + 0x58) = FLOAT_80439d60;
    }
  }
  else {
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + FLOAT_80439d48;
    if (fVar3 < *(float *)(param_1 + 0x58)) {
      *(float *)(param_1 + 0x58) = fVar3;
    }
  }
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x58);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x58);
  return;
}



// ==== 8012adc4  FUN_8012adc4 ====

void FUN_8012adc4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8012ade4  FUN_8012ade4 ====

void FUN_8012ade4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined *puVar2;
  uint uVar3;
  int iVar4;
  
  uVar3 = 0x44;
  cVar1 = *(char *)(*(int *)(param_9 + 0x90) + 0x3ec);
  puVar2 = (undefined *)(int)*(char *)(*(int *)(param_9 + 0x90) + 0xae);
  if (((cVar1 == '\x02') || (cVar1 == '\x03')) || (cVar1 == '\x05')) {
    uVar3 = 1;
  }
  iVar4 = *(int *)(param_9 + ((int)(-(int)puVar2 | (uint)puVar2) >> 0x1f) * -4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
              (float *)(param_9 + 0x114),puVar2,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar4,uVar3);
  return;
}



// ==== 8012af8c  FUN_8012af8c ====

void FUN_8012af8c(int param_1)

{
  zz_00c74ec_(param_1,0x20);
  if (*(short *)(param_1 + 1000) == 0x607) {
    zz_012aa24_(param_1,0x10);
    zz_012aa24_(param_1,0x11);
  }
  else if (*(short *)(param_1 + 1000) == 0x61b) {
    zz_012aa24_(param_1,0x12);
    zz_012aa24_(param_1,0x13);
  }
  return;
}



// ==== 8012b004  FUN_8012b004 ====

void FUN_8012b004(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80439d70;
  fVar1 = FLOAT_80439d68;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x1978) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1978) ^ 0x80000000) -
                             DOUBLE_80439d70) * FLOAT_80439d68);
    *(short *)(param_1 + 0x197a) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x197a) ^ 0x80000000) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x197e) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x197e) ^ 0x80000000) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x1980) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1980) ^ 0x80000000) -
                             dVar2) * fVar1);
  }
  *(undefined1 *)(param_1 + 0x6e8) = 0;
  return;
}



// ==== 8012b0e4  FUN_8012b0e4 ====

void FUN_8012b0e4(char *param_1)

{
  if ((*(short *)(param_1 + 1000) == 0x607) && ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0)) {
    zz_006a8c0_(param_1,0x606);
    zz_005f00c_((int)param_1);
    zz_017a608_((int)param_1);
  }
  return;
}



// ==== 8012b14c  FUN_8012b14c ====

void FUN_8012b14c(int param_1)

{
  (*(code *)(&PTR_FUN_80332370)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8012b188  FUN_8012b188 ====

void FUN_8012b188(int param_1)

{
  float fVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  float local_28;
  undefined4 local_24;
  float local_20;
  double local_18;
  double local_10;
  
  fVar1 = FLOAT_80439d78;
  if (*(char *)(param_1 + 0x540) == '\0') {
    *(undefined1 *)(param_1 + 0x540) = 1;
    *(float *)(param_1 + 0x558) = fVar1;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),(float *)(param_1 + 0x20),&local_28);
  iVar3 = FUN_800452a0((double)local_28,(double)local_20);
  sVar2 = (short)iVar3 - *(short *)(param_1 + 0x72);
  if ((sVar2 < 0x2001) && (-0x2001 < sVar2)) {
    zz_017a6e0_(param_1,1,(short *)(param_1 + 0x1978),0);
    zz_017a6e0_(param_1,1,(short *)(param_1 + 0x197e),1);
    local_28 = *(float *)(param_1 + 0x8dc);
    local_24 = *(undefined4 *)(param_1 + 0x8ec);
    local_20 = *(float *)(param_1 + 0x8fc);
    iVar3 = FUN_800452a0((double)local_28,(double)local_20);
    local_28 = *(float *)(param_1 + 0xdf0);
    local_24 = *(undefined4 *)(param_1 + 0xe00);
    local_20 = *(float *)(param_1 + 0xe10);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
    iVar4 = FUN_800452a0((double)local_28,(double)local_20);
    sVar2 = (short)iVar4 - (short)iVar3;
    if ((sVar2 < 0x2000) && (-0x2000 < sVar2)) {
      if (0x1000 < sVar2) {
        sVar2 = 0x1000;
      }
      if (sVar2 < -0x1000) {
        sVar2 = -0x1000;
      }
      *(short *)(param_1 + 0x197a) = sVar2;
    }
    else {
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x197a)) ^ 0x80000000);
      iVar4 = (int)((float)(local_18 - DOUBLE_80439d70) * FLOAT_80439d68);
      local_10 = (double)(longlong)iVar4;
      *(short *)(param_1 + 0x197a) = (short)iVar4;
    }
    local_28 = *(float *)(param_1 + 0xe20);
    local_24 = *(undefined4 *)(param_1 + 0xe30);
    local_20 = *(float *)(param_1 + 0xe40);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
    iVar4 = FUN_800452a0((double)local_28,(double)local_20);
    sVar2 = (short)iVar4 - (short)iVar3;
    if ((sVar2 < 0x2000) && (-0x2000 < sVar2)) {
      if (0x1000 < sVar2) {
        sVar2 = 0x1000;
      }
      if (sVar2 < -0x1000) {
        sVar2 = -0x1000;
      }
      *(short *)(param_1 + 0x1980) = sVar2;
    }
    else {
      local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1980)) ^ 0x80000000);
      iVar3 = (int)((float)(local_10 - DOUBLE_80439d70) * FLOAT_80439d68);
      local_18 = (double)(longlong)iVar3;
      *(short *)(param_1 + 0x1980) = (short)iVar3;
    }
    fVar1 = FLOAT_80439d7c;
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar1 < *(float *)(param_1 + 0x558)) {
      return;
    }
  }
  zz_006bf80_(param_1);
  iVar3 = zz_006dbe0_(param_1,0,1,1);
  if (iVar3 != 0) {
    if (*(short *)(param_1 + 1000) == 0x607) {
      zz_00c3be0_(param_1,0x20);
      zz_00c3be0_(param_1,0x21);
    }
    else if (*(short *)(param_1 + 1000) == 0x61b) {
      zz_00c3be0_(param_1,0x53);
      zz_00c3be0_(param_1,0x54);
    }
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a53c_(param_1,0x10);
  return;
}



// ==== 8012b458  FUN_8012b458 ====

void FUN_8012b458(int param_1)

{
  float fVar1;
  float fVar2;
  
  *(undefined1 *)(param_1 + 0x6e8) = 0x83;
  fVar2 = FLOAT_80439d80;
  fVar1 = FLOAT_80439d7c;
  if (*(char *)(param_1 + 0x540) == '\0') {
    *(undefined1 *)(param_1 + 0x540) = 1;
    *(float *)(param_1 + 0x558) = fVar2;
    zz_00107a0_(param_1,0x7f);
    zz_00f036c_(param_1,0x20);
    if (*(short *)(param_1 + 1000) == 0x607) {
      zz_016c7ec_(param_1,1,0);
      zz_016c7ec_(param_1,2,0);
    }
    else if (*(short *)(param_1 + 1000) == 0x61b) {
      zz_016c7ec_(param_1,4,0);
      zz_016c7ec_(param_1,5,0);
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (*(float *)(param_1 + 0x558) <= fVar1) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a53c_(param_1,0x10);
    }
  }
  return;
}



// ==== 8012b554  FUN_8012b554 ====

void FUN_8012b554(int param_1)

{
  zz_012b574_(param_1);
  return;
}



// ==== 8012b574  zz_012b574_ ====

void zz_012b574_(int param_1)

{
  zz_017a374_(param_1);
  return;
}



// ==== 8012b59c  zz_012b59c_ ====

void zz_012b59c_(int param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  int *piVar2;
  
  if (((*(short *)(param_1 + 1000) == 0x202) || (*(short *)(param_1 + 1000) == 0x20b)) &&
     (puVar1 = zz_0088aa0_(param_1,3,0,0,4), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x13] = param_3;
    *(code **)(puVar1 + 0xc) = FUN_8012b6d8;
    *(code **)(puVar1 + 0x10c) = FUN_8012bf60;
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
    piVar2 = zz_0006dc8_(0x60);
    *(int **)(puVar1 + 0xdc) = piVar2;
    if (piVar2 == (int *)0x0) {
      puVar1[0x18] = 2;
    }
  }
  return;
}



// ==== 8012b6d8  FUN_8012b6d8 ====

void FUN_8012b6d8(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80332968)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8012b72c  FUN_8012b72c ====

void FUN_8012b72c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar4;
  int iVar5;
  undefined8 uVar6;
  
  iVar5 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 400) = 0xff;
  pfVar4 = *(float **)(*(int *)(param_9 + 0xdc) + 0xc);
  gnt4_PSMTXIdentity_bl(pfVar4);
  gnt4_PSMTXIdentity_bl(pfVar4 + 0xc);
  *(code **)(param_9 + 0x100) = FUN_8012be5c;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  fVar1 = FLOAT_80439d88;
  *(float *)(param_9 + 0xb4) = FLOAT_80439d88;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x18c) = fVar1;
  if ((char)(&DAT_803327c9)[*(char *)(param_9 + 0x13) * 0x10 + *(char *)(param_9 + 0x11) * 2] <
      '\x01') {
    *(undefined1 *)(param_9 + 0x12) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0x12) = 1;
  }
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(char *)(*(char *)(param_9 + 0x13) * 0x10 + -0x7fccd838 +
                                    *(char *)(param_9 + 0x11) * 2),iVar5 + 0xc28,in_r7,in_r8,in_r9,
                      in_r10);
  iVar3 = iVar5 + 0xc28;
  iVar2 = (int)*(char *)(*(char *)(param_9 + 0x13) * 0x10 + -0x7fccd838 +
                        *(char *)(param_9 + 0x11) * 2);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  uVar6 = zz_0007cac_((double)FLOAT_80439d8c,*(int *)(param_9 + 0xe4));
  if (*(char *)(param_9 + 0x12) != '\0') {
    uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe8),
                        (int)(char)(&DAT_803327c9)
                                   [*(char *)(param_9 + 0x13) * 0x10 + *(char *)(param_9 + 0x11) * 2
                                   ],iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10);
    iVar3 = iVar5 + 0xc28;
    iVar2 = (int)(char)(&DAT_803327c9)
                       [*(char *)(param_9 + 0x13) * 0x10 + *(char *)(param_9 + 0x11) * 2];
    uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xec),iVar2,iVar3,in_r7,in_r8,
                        in_r9,in_r10);
    zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xec),extraout_r4_00,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
    zz_0007cac_((double)FLOAT_80439d8c,*(int *)(param_9 + 0xec));
  }
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  FUN_8012b954(param_9);
  return;
}



// ==== 8012b954  FUN_8012b954 ====

/* WARNING: Removing unreachable block (ram,0x8012bde4) */
/* WARNING: Removing unreachable block (ram,0x8012bddc) */
/* WARNING: Removing unreachable block (ram,0x8012bdd4) */
/* WARNING: Removing unreachable block (ram,0x8012b974) */
/* WARNING: Removing unreachable block (ram,0x8012b96c) */
/* WARNING: Removing unreachable block (ram,0x8012b964) */

void FUN_8012b954(int param_1)

{
  float *pfVar1;
  char cVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float *pfVar6;
  uint uVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  float local_98;
  float local_94;
  undefined4 local_90;
  float local_8c [3];
  float local_80;
  float local_70;
  undefined4 local_60;
  
  iVar9 = *(int *)(param_1 + 0x90);
  if (*(char *)(param_1 + 400) != *(char *)(iVar9 + 0x145)) {
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
  *(undefined1 *)(param_1 + 400) = *(undefined1 *)(iVar9 + 0x145);
  fVar3 = FLOAT_80439d88;
  cVar2 = *(char *)(param_1 + 0x11);
  if (cVar2 == '\0') {
    pfVar6 = (float *)&DAT_803328f8;
    *(undefined1 *)(param_1 + 400) = 0;
  }
  else {
    if (('\0' < *(char *)(param_1 + 0x13)) && ((cVar2 == '\x03' || (cVar2 == '\a')))) {
      *(float *)(param_1 + 0x18c) = *(float *)(param_1 + 0x18c) + FLOAT_80439d90;
      if (fVar3 < *(float *)(param_1 + 0x18c)) {
        *(float *)(param_1 + 0x18c) = fVar3;
      }
      if (*(short *)(iVar9 + 0x774) < 1) {
        *(float *)(param_1 + 0x18c) = FLOAT_80439d94;
      }
    }
    cVar2 = *(char *)(param_1 + 400);
    if (((cVar2 != '\x01') && ('\0' < cVar2)) && (cVar2 < '\x04')) {
      if (*(char *)(param_1 + 0x19) == '\0') {
        *(undefined1 *)(param_1 + 0x19) = 1;
        dVar16 = (double)FLOAT_80439d94;
        pfVar8 = (float *)(param_1 + 0x144);
        pfVar11 = (float *)(param_1 + 0x15c);
        pfVar6 = (float *)(param_1 + 0x174);
        *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(iVar9 + 0x70);
        iVar10 = 0;
        *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(iVar9 + 0x74);
        do {
          *pfVar8 = *(float *)(iVar9 + (char)(&DAT_803327e8)[iVar10 + *(char *)(param_1 + 0x11) * 2]
                                       * 0x30 + 0x8e0);
          pfVar8[1] = *(float *)(iVar9 + (char)(&DAT_803327e8)
                                               [iVar10 + *(char *)(param_1 + 0x11) * 2] * 0x30 +
                                         0x8f0);
          pfVar8[2] = *(float *)(iVar9 + (char)(&DAT_803327e8)
                                               [iVar10 + *(char *)(param_1 + 0x11) * 2] * 0x30 +
                                         0x900);
          uVar7 = zz_00055fc_();
          iVar12 = (uVar7 & 3) * 0x10;
          gnt4_PSVECSubtract_bl(pfVar8,(float *)(iVar9 + 0x20),&local_98);
          local_94 = (float)dVar16;
          dVar14 = gnt4_PSVECMag_bl(&local_98);
          fVar4 = DAT_802b0cdc;
          fVar3 = DAT_802b0cd8;
          if (dVar14 <= dVar16) {
            *pfVar11 = DAT_802b0cd8;
            fVar5 = DAT_802b0ce0;
            pfVar11[1] = fVar4;
            pfVar11[2] = fVar5;
            *pfVar6 = fVar3;
            pfVar6[1] = fVar4;
            pfVar6[2] = fVar5;
          }
          else {
            gnt4_PSVECNormalize_bl(&local_98,&local_98);
            gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80332928 + iVar12),&local_98,pfVar11);
            gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8033292c + iVar12),&local_98,pfVar6);
            pfVar11[1] = *(float *)(&DAT_80332930 + iVar12);
            pfVar6[1] = *(float *)(&DAT_80332934 + iVar12);
          }
          iVar10 = iVar10 + 1;
          pfVar11 = pfVar11 + 3;
          pfVar6 = pfVar6 + 3;
          pfVar8 = pfVar8 + 3;
        } while (iVar10 < 2);
        return;
      }
      dVar16 = (double)FLOAT_80439d98;
      pfVar6 = (float *)(param_1 + 0x144);
      pfVar8 = (float *)(param_1 + 0x15c);
      pfVar11 = (float *)(param_1 + 0x174);
      iVar9 = 0;
      *(short *)(param_1 + 0x70) =
           *(short *)(param_1 + 0x70) + *(short *)(&DAT_80332908 + *(char *)(param_1 + 0x11) * 4);
      *(short *)(param_1 + 0x72) =
           *(short *)(param_1 + 0x72) + *(short *)(&DAT_8033290a + *(char *)(param_1 + 0x11) * 4);
      do {
        gnt4_PSVECAdd_bl(pfVar8,pfVar11,pfVar8);
        if ((double)pfVar8[1] < dVar16) {
          pfVar8[1] = (float)dVar16;
        }
        gnt4_PSVECAdd_bl(pfVar6,pfVar8,pfVar6);
        iVar9 = iVar9 + 1;
        pfVar8 = pfVar8 + 3;
        pfVar11 = pfVar11 + 3;
        pfVar6 = pfVar6 + 3;
      } while (iVar9 < 2);
      return;
    }
    pfVar6 = (float *)(&DAT_803328b8 + *(char *)(param_1 + 0x11) * 8);
    if (*(char *)(iVar9 + 0x6e9) != '\0') {
      pfVar6 = (float *)&DAT_803328f8;
    }
  }
  iVar10 = 0;
  pfVar8 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  iVar12 = 0;
  dVar16 = DOUBLE_80439da0;
  do {
    dVar15 = (double)*pfVar6;
    pfVar6 = pfVar6 + 1;
    dVar14 = (double)(float)(dVar16 - dVar15);
    gnt4_PSMTXCopy_bl((float *)(iVar9 + (char)(&DAT_803327e8)
                                              [iVar10 + *(char *)(param_1 + 0x11) * 2] * 0x30 +
                                        0x8d4),local_8c);
    gnt4_PSMTXMultVec_bl
              (local_8c,(float *)(&DAT_803327f8 + iVar12 + *(char *)(param_1 + 0x11) * 0x18),
               &local_98);
    pfVar11 = local_8c;
    local_80 = local_98;
    local_70 = local_94;
    local_60 = local_90;
    iVar13 = 2;
    do {
      *pfVar8 = (float)(dVar15 * (double)*pfVar8 + (double)(float)(dVar14 * (double)*pfVar11));
      pfVar8[1] = (float)(dVar15 * (double)pfVar8[1] + (double)(float)(dVar14 * (double)pfVar11[1]))
      ;
      pfVar8[2] = (float)(dVar15 * (double)pfVar8[2] + (double)(float)(dVar14 * (double)pfVar11[2]))
      ;
      pfVar8[3] = (float)(dVar15 * (double)pfVar8[3] + (double)(float)(dVar14 * (double)pfVar11[3]))
      ;
      pfVar8[4] = (float)(dVar15 * (double)pfVar8[4] + (double)(float)(dVar14 * (double)pfVar11[4]))
      ;
      pfVar1 = pfVar11 + 5;
      pfVar11 = pfVar11 + 6;
      pfVar8[5] = (float)(dVar15 * (double)pfVar8[5] + (double)(float)(dVar14 * (double)*pfVar1));
      pfVar8 = pfVar8 + 6;
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
    iVar10 = iVar10 + 1;
    iVar12 = iVar12 + 0xc;
  } while (iVar10 < 2);
  return;
}



// ==== 8012be14  FUN_8012be14 ====

void FUN_8012be14(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8012be5c  FUN_8012be5c ====

void FUN_8012be5c(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  
  if ((*(char *)(param_1 + 400) == '\x02') || (*(char *)(param_1 + 400) == '\x03')) {
    iVar6 = 0;
    *(undefined1 *)(param_1 + 0x84) = 0x46;
    iVar4 = 0;
    puVar5 = (undefined4 *)(param_1 + 0x144);
    for (iVar3 = 0; iVar3 <= *(char *)(param_1 + 0x12); iVar3 = iVar3 + 1) {
      *(undefined *)(param_1 + 0x89) = (&DAT_803327e8)[iVar3 + *(char *)(param_1 + 0x11) * 2];
      puVar2 = (undefined4 *)(&DAT_803327f8 + iVar6 + *(char *)(param_1 + 0x11) * 0x18);
      uVar1 = puVar2[1];
      *(undefined4 *)(param_1 + 100) = *puVar2;
      *(undefined4 *)(param_1 + 0x68) = uVar1;
      *(undefined4 *)(param_1 + 0x6c) = puVar2[2];
      uVar1 = puVar5[1];
      *(undefined4 *)(param_1 + 0x20) = *puVar5;
      *(undefined4 *)(param_1 + 0x24) = uVar1;
      *(undefined4 *)(param_1 + 0x28) = puVar5[2];
      FUN_80047aa4(param_1);
      gnt4_PSMTXCopy_bl((float *)(param_1 + 0x114),
                        (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar4));
      iVar6 = iVar6 + 0xc;
      puVar5 = puVar5 + 3;
      iVar4 = iVar4 + 0x30;
    }
  }
  return;
}



// ==== 8012bf60  FUN_8012bf60 ====

/* WARNING: Removing unreachable block (ram,0x8012c0b4) */
/* WARNING: Removing unreachable block (ram,0x8012bf70) */

void FUN_8012bf60(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  float *pfVar5;
  uint uVar6;
  int iVar7;
  undefined8 uVar8;
  double dVar9;
  double dVar10;
  float afStack_58 [12];
  
  iVar2 = *(int *)(param_9 + 0x90);
  if ((*(char *)(iVar2 + 0xae) == '\0') && (*(char *)(iVar2 + 0x3ec) != '\x04')) {
    pfVar4 = (float *)0x0;
    uVar3 = 1;
  }
  else {
    pfVar4 = (float *)0x1;
    uVar3 = 0x44;
  }
  cVar1 = *(char *)(param_9 + 0x11);
  uVar6 = 2;
  if (cVar1 != '\x03') {
    if (cVar1 < '\x03') {
      if ((cVar1 == '\0') &&
         (uVar6 = (uint)(*(char *)(iVar2 + 0x145) != '\x02'), *(char *)(iVar2 + 0x145) == '\x01')) {
        uVar6 = 0;
      }
      goto LAB_8012c014;
    }
    if (cVar1 != '\a') goto LAB_8012c014;
  }
  if (*(short *)(iVar2 + 0x774) < 1) {
    uVar6 = 1;
  }
LAB_8012c014:
  dVar9 = (double)*(float *)(param_9 + 0x18c);
  pfVar5 = *(float **)(*(int *)(param_9 + 0xdc) + 0xc);
  iVar7 = param_9 + (int)pfVar4 * 4;
  for (iVar2 = 0; iVar2 < (int)uVar6; iVar2 = iVar2 + 1) {
    if ((iVar2 == 0) ||
       ((*(char *)(param_9 + 0x11) != '\x03' && (*(char *)(param_9 + 0x11) != '\a')))) {
      zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar7 + 0xe0),pfVar5,(undefined *)pfVar4,param_12,param_13,param_14,
                  param_15,param_16);
    }
    else {
      param_3 = dVar9;
      dVar10 = dVar9;
      gnt4_PSMTXScale_bl(dVar9,dVar9,dVar9,afStack_58);
      pfVar4 = afStack_58;
      uVar8 = gnt4_PSMTXConcat_bl(pfVar5,pfVar4,pfVar4);
      zz_00076d0_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar7 + 0xe0)
                  ,afStack_58,(undefined *)pfVar4,param_12,param_13,param_14,param_15,param_16);
      param_2 = dVar9;
      dVar9 = dVar10;
    }
    param_1 = zz_00097b4_(*(int *)(iVar7 + 0xe0),uVar3);
    pfVar5 = pfVar5 + 0xc;
    iVar7 = iVar7 + 8;
  }
  return;
}



// ==== 8012c0d0  FUN_8012c0d0 ====

void FUN_8012c0d0(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(300);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    FUN_800e4294(param_1,-0x7fccccb0,2,puVar3 + 3,(float *)(puVar3 + 0x1b));
    FUN_800e4294(param_1,-0x7fcccc50,2,puVar3 + 9,(float *)(puVar3 + 0x21));
    FUN_800e4294(param_1,-0x7fcccbf0,2,puVar3 + 0xf,(float *)(puVar3 + 0x27));
    FUN_800e4294(param_1,-0x7fcccb90,2,puVar3 + 0x15,(float *)(puVar3 + 0x2d));
  }
  return;
}



// ==== 8012c1a4  zz_012c1a4_ ====

void zz_012c1a4_(int param_1)

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
      FUN_800e43e0(param_1,(float *)&DAT_80333350,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x1b),
                   (int *)&DAT_80333560);
      FUN_800e43e0(param_1,(float *)&DAT_803333b0,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x21),
                   (int *)&DAT_8033356c);
      FUN_800e43e0(param_1,(float *)&DAT_80333410,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x27)
                   ,(int *)&DAT_80333578);
      FUN_800e43e0(param_1,(float *)&DAT_80333470,2,(float *)(puVar2 + 0x15),
                   (float *)(puVar2 + 0x2d),(int *)&DAT_80333584);
    }
    else {
      FUN_800e4f9c(param_1,-0x7fccccb0,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x33));
      FUN_800e4f9c(param_1,-0x7fcccc50,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x39));
      FUN_800e4f9c(param_1,-0x7fcccbf0,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x3f));
      FUN_800e4f9c(param_1,-0x7fcccb90,2,(float *)(puVar2 + 0x15),(float *)(puVar2 + 0x45));
    }
  }
  return;
}



// ==== 8012c318  zz_012c318_ ====

void zz_012c318_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 8012c350  zz_012c350_ ====

void zz_012c350_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fccccb0,2,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcccc50,2,pfVar2 + 9,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcccbf0,2,pfVar2 + 0xf,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcccb90,2,pfVar2 + 0x15,afStack_18);
    zz_00e5184_(param_1,-0x7fccccb0,2,pfVar2 + 3,pfVar2 + 0x33);
    zz_00e5184_(param_1,-0x7fcccc50,2,pfVar2 + 9,pfVar2 + 0x39);
    zz_00e5184_(param_1,-0x7fcccbf0,2,pfVar2 + 0xf,pfVar2 + 0x3f);
    zz_00e5184_(param_1,-0x7fcccb90,2,pfVar2 + 0x15,pfVar2 + 0x45);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 8012c594  FUN_8012c594 ====

void FUN_8012c594(int param_1)

{
  zz_0197048_(param_1);
  zz_00c2a78_(param_1);
  FUN_8012c0d0(param_1);
  return;
}



// ==== 8012c624  FUN_8012c624 ====

void FUN_8012c624(int param_1)

{
  zz_012c1a4_(param_1);
  return;
}



// ==== 8012c668  FUN_8012c668 ====

void FUN_8012c668(int param_1)

{
  zz_012c318_(param_1);
  return;
}



// ==== 8012c688  FUN_8012c688 ====

void FUN_8012c688(int param_1)

{
  zz_012c350_(param_1);
  return;
}



// ==== 8012c6a8  FUN_8012c6a8 ====

void FUN_8012c6a8(int param_1)

{
  (*(code *)(&PTR_FUN_803335d0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8012c6e4  FUN_8012c6e4 ====

void FUN_8012c6e4(int param_1)

{
  (*(code *)(&PTR_FUN_803335dc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8012c720  FUN_8012c720 ====

void FUN_8012c720(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_803335f0)[*(char *)(param_1 + 0x540)])(param_1);
  zz_012cd6c_(param_1);
  return;
}



// ==== 8012c788  FUN_8012c788 ====

void FUN_8012c788(int param_1)

{
  char cVar1;
  float fVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x544) = 0;
  *(undefined1 *)(param_1 + 0x545) = 0;
  fVar2 = FLOAT_80439da8;
  cVar1 = *(char *)(param_1 + 0x581);
  if (cVar1 == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_80439da8;
    *(float *)(param_1 + 0x44) = fVar2;
  }
  else if (cVar1 == '\x03') {
    *(float *)(param_1 + 0x48) = FLOAT_80439da8;
    *(float *)(param_1 + 0x50) = fVar2;
  }
  else if (cVar1 == '\x02') {
    fVar2 = *(float *)(param_1 + 0x48);
    if (FLOAT_80439da8 <= fVar2) {
      if (FLOAT_80439dac < fVar2) {
        *(float *)(param_1 + 0x48) = fVar2 + FLOAT_80439db4;
      }
      else {
        *(float *)(param_1 + 0x48) = fVar2 + FLOAT_80439db0;
      }
    }
  }
  else if ((cVar1 == '\x04') && (0 < *(short *)(param_1 + 0x774))) {
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + FLOAT_80439db0;
  }
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439db8;
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  if ((*(char *)(param_1 + 0x581) == '\x02') || (*(char *)(param_1 + 0x581) == '\x04')) {
    zz_004beb8_((double)FLOAT_80439dbc,param_1,0xf,2,3,0xffffffff,0xffffffff);
  }
  else {
    zz_004beb8_((double)FLOAT_80439dbc,param_1,0xf,2,0,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8012c91c  FUN_8012c91c ====

void FUN_8012c91c(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  iVar1 = zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (((*(char *)(param_1 + 0x1cee) == '\0') || (iVar1 != 1)) &&
     (FLOAT_80439da8 < *(float *)(param_1 + 0x558))) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if ((*(char *)(param_1 + 0x581) == '\x02') || (*(char *)(param_1 + 0x581) == '\x04')) {
    zz_004beb8_((double)FLOAT_80439dbc,param_1,0xf,2,4,0xffffffff,0xffffffff);
  }
  else {
    zz_004beb8_((double)FLOAT_80439dbc,param_1,0xf,2,1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8012ca14  FUN_8012ca14 ====

void FUN_8012ca14(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      zz_0082824_(param_1,0x22);
    }
    fVar1 = FLOAT_80439db8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    if ((*(char *)(param_1 + 0x581) == '\x02') || (*(char *)(param_1 + 0x581) == '\x04')) {
      dVar3 = (double)FLOAT_80439dbc;
      *(undefined1 *)(param_1 + 0x544) = 1;
      zz_004beb8_(dVar3,param_1,0xf,2,5,0xffffffff,0xffffffff);
    }
    else {
      zz_004beb8_((double)FLOAT_80439dbc,param_1,0xf,2,2,0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 8012cafc  FUN_8012cafc ====

void FUN_8012cafc(int param_1)

{
  float fVar1;
  int iVar2;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80439dc8) * FLOAT_80439dc0);
  iVar2 = zz_004cd24_(param_1,0xf);
  if ((iVar2 != 0) &&
     ((*(char *)(param_1 + 0x581) == '\x02' || (*(char *)(param_1 + 0x581) == '\x04')))) {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
  }
  fVar1 = FLOAT_80439da8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (fVar1 < *(float *)(param_1 + 0x558)) {
    if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x03')) {
      *(undefined1 *)(param_1 + 0x544) = 1;
    }
    if (*(char *)(param_1 + 0x545) == '\x01') {
      if ((*(char *)(param_1 + 0x581) == '\x02') || (*(char *)(param_1 + 0x581) == '\x04')) {
        *(undefined2 *)(param_1 + 0x18da) = 0;
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        zz_006a5a4_(param_1);
        *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
      }
      else {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        zz_00b2190_(param_1,2);
      }
    }
  }
  else {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8012cc80  FUN_8012cc80 ====

void FUN_8012cc80(int param_1)

{
  float fVar1;
  int iVar2;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80439dc8) * FLOAT_80439dd0);
  iVar2 = zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_80439da8;
  if (iVar2 == 1) {
    if ((*(char *)(param_1 + 0x581) == '\x02') || (*(char *)(param_1 + 0x581) == '\x04')) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54a);
    }
    else {
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffbf;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x44) = fVar1;
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a474_(param_1);
    }
    *(undefined2 *)(param_1 + 0x18da) = 0;
  }
  return;
}



// ==== 8012cd6c  zz_012cd6c_ ====

void zz_012cd6c_(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80439dd4;
  if (*(char *)(param_1 + 0x581) != '\x01') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80439dd4;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  }
  fVar1 = FLOAT_80439da8;
  if (*(float *)(param_1 + 0x44) < FLOAT_80439da8) {
    *(float *)(param_1 + 0x4c) = FLOAT_80439da8;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  FUN_80067310((double)FLOAT_80439dd8,param_1,*(short *)(param_1 + 0x54a));
  iVar2 = zz_00679d0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x544) == '\x01')) {
    *(undefined1 *)(param_1 + 0x545) = 1;
  }
  return;
}



// ==== 8012ce08  FUN_8012ce08 ====

void FUN_8012ce08(int param_1)

{
  (*(code *)(&PTR_FUN_80333604)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8012ce44  FUN_8012ce44 ====

void FUN_8012ce44(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033361c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8012ce94  FUN_8012ce94 ====

void FUN_8012ce94(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  fVar2 = FLOAT_80439db8;
  fVar1 = FLOAT_80439da8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x44) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(undefined1 *)(param_1 + 0x541) = 0;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_80439da8;
  return;
}



// ==== 8012cf50  FUN_8012cf50 ====

void FUN_8012cf50(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80439da8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar2 = zz_006d144_(param_1,0xc0), iVar2 != 0)) {
    fVar1 = FLOAT_80439ddc;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           FLOAT_80439de0 *
           (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar1);
    }
    else {
      *(float *)(param_1 + 0x44) = (FLOAT_80439de0 * *(float *)(param_1 + 0x764)) / fVar1;
    }
    fVar1 = FLOAT_80439de4;
    *(float *)(param_1 + 0x4c) = FLOAT_80439da8;
    if (fVar1 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_80439dbc,param_1,0xf,3,2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8012d068  FUN_8012d068 ====

void FUN_8012d068(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  
  if (*(char *)(param_1 + 0x1cef) == '\x03') {
    if (*(char *)(param_1 + 0x1cf0) == '\x01') goto LAB_8012d0a0;
  }
  zz_004cd24_(param_1,0xf);
LAB_8012d0a0:
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1dd) & 0x80) == 0) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80439de8;
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar1 = FLOAT_80439da8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar4 = FUN_80066838((double)FLOAT_80439de4,param_1), 0 < (int)uVar4)) {
    fVar2 = FLOAT_80439df0;
    fVar1 = FLOAT_80439dec;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 0;
  }
  return;
}



// ==== 8012d168  FUN_8012d168 ====

void FUN_8012d168(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  iVar2 = zz_004cd24_(param_1,0xf);
  if (iVar2 == 1) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
  }
  else {
    if (*(char *)(param_1 + 0x542) == '\0') {
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\x02')) {
        *(undefined1 *)(param_1 + 0x543) = 1;
      }
      if (((*(char *)(param_1 + 0x1cef) != '\x03') || (*(char *)(param_1 + 0x1cf0) != '\x03')) &&
         ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0)) {
        *(undefined1 *)(param_1 + 0x745) = 1;
      }
      if (((*(char *)(param_1 + 0x543) == '\x01') && (*(char *)(param_1 + 0x745) == '\x01')) ||
         ((*(char *)(param_1 + 0x1cef) == '\x03' && (*(char *)(param_1 + 0x1cf0) == '\x03')))) {
        if (*(char *)(param_1 + 0x745) == '\x01') {
          *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
          *(undefined1 *)(param_1 + 0x542) = 0;
          fVar1 = FLOAT_80439df4;
          if (*(char *)(param_1 + 0x541) == '\0') {
            if (*(int *)(param_1 + 0xcc) == 0) {
              *(undefined1 *)(param_1 + 0x541) = 1;
            }
            else {
              *(float *)(param_1 + 0x558) = FLOAT_80439ddc;
              *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / fVar1;
            }
          }
          if (*(char *)(param_1 + 0x541) == '\x01') {
            *(float *)(param_1 + 0x558) = FLOAT_80439df8;
          }
          dVar3 = (double)FLOAT_80439dbc;
          *(float *)(param_1 + 0x4c) = FLOAT_80439da8;
          zz_004beb8_(dVar3,param_1,0xf,3,3,0xffffffff,0xffffffff);
        }
        else {
          *(undefined1 *)(param_1 + 0x542) = 99;
        }
      }
    }
    zz_006d144_(param_1,0xc0);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 != 0) {
      zz_00b22f4_(param_1);
    }
  }
  return;
}



// ==== 8012d310  FUN_8012d310 ====

void FUN_8012d310(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x02') {
    zz_004cd24_(param_1,0xf);
    if ((*(char *)(param_1 + 0x1cef) == '\x02') && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x4c) = FLOAT_80439dbc;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if ((*(char *)(param_1 + 0x1cef) != '\x02') || (*(char *)(param_1 + 0x1cf0) != '\x04')) {
        zz_004cd24_(param_1,0xf);
      }
      fVar2 = FLOAT_80439da8;
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
      if ((*(float *)(param_1 + 0x558) <= fVar2) ||
         (uVar4 = FUN_80066838((double)FLOAT_80439de4,param_1), 0 < (int)uVar4)) {
        fVar3 = FLOAT_80439dfc;
        fVar2 = FLOAT_80439df0;
        *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar3;
        *(float *)(param_1 + 0x4c) = fVar2;
      }
    }
    else if (((-1 < cVar1) &&
             (zz_004cd24_(param_1,0xf), fVar2 = FLOAT_80439da8,
             *(char *)(param_1 + 0x1cef) == '\x02')) && (*(char *)(param_1 + 0x1cf0) == '\x04')) {
      *(float *)(param_1 + 0x44) = FLOAT_80439db0;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      *(undefined1 *)(param_1 + 0x541) = 1;
      *(undefined4 *)(param_1 + 0xcc) = 0;
      *(undefined1 *)(param_1 + 0x1cef) = 0;
      *(undefined1 *)(param_1 + 0x1cf0) = 0;
    }
  }
  else if ((cVar1 < '\x04') && (iVar5 = zz_004cd24_(param_1,0xf), iVar5 == 1)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    return;
  }
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar5 = zz_00677b0_(param_1);
  if (iVar5 != 0) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8012d4cc  FUN_8012d4cc ====

void FUN_8012d4cc(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 8012d504  FUN_8012d504 ====

void FUN_8012d504(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80333634)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8012d554  FUN_8012d554 ====

void FUN_8012d554(int param_1)

{
  float fVar1;
  uint uVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x54e);
  }
  fVar1 = FLOAT_80439dd4;
  *(float *)(param_1 + 0x558) = FLOAT_80439db8;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_80439da8;
  return;
}



// ==== 8012d634  FUN_8012d634 ====

void FUN_8012d634(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_80439e00;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_80439e00;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  fVar1 = FLOAT_80439da8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    fVar2 = FLOAT_80439da8;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    fVar1 = fVar1 / FLOAT_80439ddc;
    *(float *)(param_1 + 0x558) = FLOAT_80439ddc;
    fVar3 = FLOAT_80439de4;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_80439dbc,param_1,0xf,3,5,0xffffffff,0xffffffff);
    *(undefined1 *)(param_1 + 0x542) = 0;
  }
  return;
}



// ==== 8012d778  FUN_8012d778 ====

void FUN_8012d778(int param_1)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  float afStack_18 [5];
  
  zz_004cd24_(param_1,0xf);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),afStack_18);
  gnt4_PSVECMag_bl(afStack_18);
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar1 = FLOAT_80439da8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar3 = FUN_80066838((double)FLOAT_80439de4,param_1), uVar3 != 0)) {
    dVar4 = (double)FLOAT_80439dbc;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8012d85c  FUN_8012d85c ====

void FUN_8012d85c(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = zz_00677b0_(param_1);
  if ((iVar5 != 0) && (FLOAT_80439dd8 < *(float *)(param_1 + 0x44))) {
    zz_00b22f4_(param_1);
  }
  uVar6 = FUN_80066838((double)FLOAT_80439e04,param_1);
  if (0 < (int)uVar6) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  if (*(char *)(param_1 + 0x541) == '\0') {
    uVar2 = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
    zz_006660c_(param_1);
    if (*(char *)(param_1 + 0x1d9) == '\0') {
      FUN_800669d0(param_1,0x40);
    }
    else {
      *(undefined1 *)(param_1 + 0x541) = 1;
    }
    *(undefined2 *)(param_1 + 0x72) = uVar2;
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar3 = FLOAT_80439da8;
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 == '\x04') {
        iVar5 = zz_004cd24_(param_1,0xf);
        if (iVar5 != 1) {
          return;
        }
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        return;
      }
      if ('\x03' < cVar1) {
        return;
      }
      goto LAB_8012d9fc;
    }
    if (cVar1 == '\0') {
      zz_004cd24_(param_1,0xf);
      fVar4 = FLOAT_80439e08;
      fVar3 = FLOAT_80439df0;
      if (*(char *)(param_1 + 0x1cef) != '\x02') {
        return;
      }
      if (*(char *)(param_1 + 0x1cf0) != '\x01') {
        return;
      }
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      *(undefined2 *)(param_1 + 0x548) = 0;
      *(undefined2 *)(param_1 + 0x54a) = 0x1500;
      *(float *)(param_1 + 0x558) = fVar4;
      *(float *)(param_1 + 0x4c) = fVar3;
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar3 < *(float *)(param_1 + 0x558)) {
      zz_0067754_(param_1,(short *)(param_1 + 0x72),*(short *)(param_1 + 0x54a));
      return;
    }
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 1;
  }
  zz_0066ed8_(param_1,*(ushort *)(param_1 + 0x5ae),*(undefined2 *)(param_1 + 0x54a));
  *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
LAB_8012d9fc:
  iVar5 = zz_0066ff0_(param_1);
  if (iVar5 == 1) {
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
  }
  return;
}



// ==== 8012da5c  FUN_8012da5c ====

void FUN_8012da5c(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 8012da94  FUN_8012da94 ====

void FUN_8012da94(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80333648)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8012dae4  FUN_8012dae4 ====

void FUN_8012dae4(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  dVar2 = (double)FLOAT_80439dbc;
  *(float *)(param_1 + 0x558) = FLOAT_80439db8;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,4,0xffffffff,0xffffffff);
  return;
}



// ==== 8012dba0  FUN_8012dba0 ====

void FUN_8012dba0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  zz_006660c_(param_1);
  if (FLOAT_80439da8 < *(float *)(param_1 + 0x558)) {
    iVar3 = FUN_800669d0(param_1,0xc0);
    if (iVar3 == 0) goto LAB_8012dc20;
  }
  fVar2 = FLOAT_80439e04;
  fVar1 = FLOAT_80439ddc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_8012dc20:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 8012dc60  FUN_8012dc60 ====

/* WARNING: Removing unreachable block (ram,0x8012de90) */
/* WARNING: Removing unreachable block (ram,0x8012dc70) */

void FUN_8012dc60(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),&local_2c);
  dVar4 = gnt4_PSVECMag_bl(&local_2c);
  fVar1 = FLOAT_80439da8;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_80439de0 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_80439ddc
         );
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar3 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_2c = *(float *)(iVar3 + 0x8e0);
    local_28 = *(float *)(iVar3 + 0x8f0);
    local_24 = *(undefined4 *)(iVar3 + 0x900);
    local_38 = *(float *)(param_1 + 0x518);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    local_34 = FLOAT_80439ddc * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_80439da8;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_80439e0c;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar5 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_80439e10;
    *(float *)(param_1 + 0x44) = (float)(dVar5 * (double)FLOAT_80439e0c);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_80439dd8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar2 = FUN_80066838((double)FLOAT_80439db8,param_1);
  if ((int)uVar2 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar4 < DOUBLE_80439e18 * (double)*(float *)(param_1 + 0x44)) goto LAB_8012de84;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar1 = FLOAT_80439da8;
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar1 < *(float *)(param_1 + 0x558)) {
      return;
    }
  }
LAB_8012de84:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 8012deac  FUN_8012deac ====

void FUN_8012deac(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_80439dd8,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_80439da8;
    if (*(float *)(param_1 + 0x44) < FLOAT_80439da8) {
      *(float *)(param_1 + 0x44) = FLOAT_80439da8;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_80439ddc + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 8012df50  FUN_8012df50 ====

void FUN_8012df50(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80333658)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8012dfa0  FUN_8012dfa0 ====

void FUN_8012dfa0(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x870),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  dVar2 = (double)FLOAT_80439dbc;
  *(float *)(param_1 + 0x558) = FLOAT_80439db8;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}



// ==== 8012e05c  FUN_8012e05c ====

void FUN_8012e05c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  zz_006660c_(param_1);
  if (FLOAT_80439da8 < *(float *)(param_1 + 0x558)) {
    iVar3 = FUN_800669d0(param_1,0xc0);
    if (iVar3 == 0) goto LAB_8012e0dc;
  }
  fVar2 = FLOAT_80439e04;
  fVar1 = FLOAT_80439ddc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_8012e0dc:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}



// ==== 8012e11c  FUN_8012e11c ====

/* WARNING: Removing unreachable block (ram,0x8012e34c) */
/* WARNING: Removing unreachable block (ram,0x8012e12c) */

void FUN_8012e11c(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),&local_2c);
  dVar4 = gnt4_PSVECMag_bl(&local_2c);
  fVar1 = FLOAT_80439da8;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_80439e20 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_80439ddc
         );
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar3 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_2c = *(float *)(iVar3 + 0x8e0);
    local_28 = *(float *)(iVar3 + 0x8f0);
    local_24 = *(undefined4 *)(iVar3 + 0x900);
    local_38 = *(float *)(param_1 + 0x518);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    local_34 = FLOAT_80439ddc * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_80439da8;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_80439e0c;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar5 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_80439e10;
    *(float *)(param_1 + 0x44) = (float)(dVar5 * (double)FLOAT_80439e0c);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  FUN_80067310((double)FLOAT_80439dd8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar2 = FUN_80066838((double)FLOAT_80439db8,param_1);
  if ((int)uVar2 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar4 < DOUBLE_80439e18 * (double)*(float *)(param_1 + 0x44)) goto LAB_8012e340;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar1 = FLOAT_80439da8;
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar1 < *(float *)(param_1 + 0x558)) {
      return;
    }
  }
LAB_8012e340:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 8012e368  FUN_8012e368 ====

void FUN_8012e368(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_80439dd8,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_80439da8;
    if (*(float *)(param_1 + 0x44) < FLOAT_80439da8) {
      *(float *)(param_1 + 0x44) = FLOAT_80439da8;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_80439ddc + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 8012e40c  FUN_8012e40c ====

void FUN_8012e40c(int param_1)

{
  (*(code *)(&PTR_FUN_804345b8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8012e444  FUN_8012e444 ====

void FUN_8012e444(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80333668)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8012e494  FUN_8012e494 ====

void FUN_8012e494(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_80439db8;
  fVar1 = FLOAT_80439da8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  zz_006d144_(param_1,0xc0);
  iVar3 = zz_006dbe0_(param_1,2,1,1);
  if (iVar3 == 1) {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(byte *)(param_1 + 0x597) = *(byte *)(param_1 + 0x597) | 4;
  }
  else {
    *(undefined1 *)(param_1 + 0x544) = 0;
  }
  return;
}



// ==== 8012e550  FUN_8012e550 ====

void FUN_8012e550(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  fVar1 = FLOAT_80439da8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((fVar1 < *(float *)(param_1 + 0x558)) && (iVar2 = zz_006d144_(param_1,0xc0), iVar2 == 0)) {
    return;
  }
  dVar3 = (double)FLOAT_80439dbc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x542) = 0;
  zz_004beb8_(dVar3,param_1,0xf,4,0,0xffffffff,0xffffffff);
  if (*(char *)(param_1 + 0x544) == '\0') {
    *(undefined1 *)(param_1 + 0x6e8) = 0;
    *(undefined1 *)(param_1 + 0x545) = 99;
  }
  else {
    *(undefined1 *)(param_1 + 0x545) = 0;
    *(undefined1 *)(param_1 + 0x592) = 1;
  }
  return;
}



// ==== 8012e610  FUN_8012e610 ====

/* WARNING: Removing unreachable block (ram,0x8012eac4) */
/* WARNING: Removing unreachable block (ram,0x8012e620) */

void FUN_8012e610(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  short sVar8;
  int iVar7;
  bool bVar9;
  double dVar10;
  double dVar11;
  
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x01') {
    if ((*(uint *)(param_1 + 0x5d4) & 0x80) != 0) {
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) + FLOAT_80439e24;
    }
    if (*(char *)(param_1 + 0x1b01) != '\0') {
      *(float *)(param_1 + 0x1dcc) = *(float *)(param_1 + 0x1dcc) + FLOAT_80439dec;
      *(short *)(param_1 + 0x146) = *(short *)(param_1 + 0x146) + 1;
    }
    zz_004cd24_(param_1,0xf);
    fVar4 = -(FLOAT_80439de0 * *(float *)(param_1 + 0x1dc8) - *(float *)(param_1 + 0x558));
    bVar9 = fVar4 < FLOAT_80439da8;
    *(float *)(param_1 + 0x558) = fVar4;
    if (((bVar9) && (1 < *(short *)(param_1 + 0x146))) || (4 < *(short *)(param_1 + 0x146))) {
      dVar11 = (double)FLOAT_80439db0;
      *(float *)(param_1 + 0x1dcc) = FLOAT_80439dd8;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      zz_004beb8_(dVar11,param_1,0xf,4,2,3,1);
    }
  }
  else if (cVar1 < '\x01') {
    if ((-1 < cVar1) && (iVar7 = zz_004cd24_(param_1,0xf), iVar7 == 1)) {
      if (*(char *)(param_1 + 0x544) != '\x01') {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        return;
      }
      dVar11 = (double)FLOAT_80439dbc;
      *(undefined1 *)(param_1 + 0x745) = 0;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      zz_004beb8_(dVar11,param_1,0xf,4,1,0xffffffff,0xffffffff);
      *(float *)(param_1 + 0x558) = FLOAT_80439db8;
      *(undefined2 *)(param_1 + 0x146) = 1;
    }
  }
  else if ((cVar1 < '\x03') && (iVar7 = zz_004cd24_(param_1,0xf), iVar7 == 1)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  cVar1 = *(char *)(param_1 + 0x545);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if (cVar1 < '\x03') {
        sVar8 = *(short *)(param_1 + 0x548) + -1;
        *(short *)(param_1 + 0x548) = sVar8;
        if (sVar8 < 1) {
          dVar11 = zz_0045238_(*(short *)(param_1 + 0x148));
          *(float *)(param_1 + 0x24) =
               *(float *)(param_1 + 0xb4) * (float)((double)FLOAT_80439de0 * dVar11) +
               *(float *)(param_1 + 0x24);
        }
        else {
          dVar11 = zz_0045238_(*(short *)(param_1 + 0x148));
          *(float *)(param_1 + 0x24) =
               *(float *)(param_1 + 0x154) *
               *(float *)(param_1 + 0xb4) * (float)((double)FLOAT_80439de0 * dVar11) +
               *(float *)(param_1 + 0x24);
          *(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x154) + *(float *)(param_1 + 0x158);
        }
        *(short *)(param_1 + 0x148) = *(short *)(param_1 + 0x148) + *(short *)(param_1 + 0x14a);
        if ((*(short *)(param_1 + 0x14a) < 0x200) &&
           (*(short *)(param_1 + 0x14a) = *(short *)(param_1 + 0x14a) + 0x200,
           0x200 < *(short *)(param_1 + 0x14a))) {
          *(undefined2 *)(param_1 + 0x14a) = 0x200;
        }
      }
      goto LAB_8012e998;
    }
    if (cVar1 < '\0') goto LAB_8012e998;
    *(undefined2 *)(param_1 + 0x548) = 0x19;
    fVar5 = FLOAT_80439e28;
    fVar4 = FLOAT_80439da8;
    *(float *)(param_1 + 0x50) = FLOAT_80439da8;
    dVar11 = DOUBLE_80439dc8;
    *(float *)(param_1 + 0x48) = fVar4;
    fVar6 = FLOAT_80439e2c;
    *(float *)(param_1 + 0x4c) = fVar4;
    *(float *)(param_1 + 0x44) = fVar4;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
    *(float *)(param_1 + 0x50) = fVar5;
    *(float *)(param_1 + 0x48) =
         fVar6 * (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x548) ^ 0x80000000)
                        - dVar11);
    *(undefined2 *)(param_1 + 0x148) = 0;
    *(undefined2 *)(param_1 + 0x14a) = 0x1eb;
    *(char *)(param_1 + 0x545) = *(char *)(param_1 + 0x545) + '\x01';
  }
  zz_0067458_((double)FLOAT_80439dd8,param_1,*(short *)(param_1 + 0x5ae));
  dVar11 = zz_0045204_(*(short *)(param_1 + 0x148));
  *(float *)(param_1 + 0x24) =
       *(float *)(param_1 + 0xb4) * (float)((double)FLOAT_80439de0 * dVar11) +
       *(float *)(param_1 + 0x24);
  *(short *)(param_1 + 0x148) = *(short *)(param_1 + 0x148) + *(short *)(param_1 + 0x14a);
  sVar8 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar8;
  if (sVar8 < 1) {
    *(undefined2 *)(param_1 + 0x148) = 0x7000;
    fVar5 = FLOAT_80439dfc;
    *(undefined2 *)(param_1 + 0x14a) = 0x200;
    fVar6 = FLOAT_80439e30;
    *(undefined2 *)(param_1 + 0x548) = 0x14;
    fVar4 = FLOAT_80439da8;
    *(float *)(param_1 + 0x154) = fVar5;
    *(float *)(param_1 + 0x158) = fVar6;
    *(float *)(param_1 + 0x14c) = fVar4;
    *(undefined1 *)(param_1 + 0x152) = 2;
    *(char *)(param_1 + 0x545) = *(char *)(param_1 + 0x545) + '\x01';
  }
LAB_8012e998:
  zz_006d144_(param_1,0xc0);
  if (('\x01' < *(char *)(param_1 + 0x545)) && (*(char *)(param_1 + 0x544) == '\x01')) {
    uVar2 = *(undefined2 *)(param_1 + 0x5aa);
    dVar11 = (double)(*(float *)(param_1 + 0x5f4) * *(float *)(param_1 + 0x5f8));
    uVar3 = *(undefined2 *)(param_1 + 0x5ac);
    iVar7 = zz_0066ac0_(param_1,0);
    if (iVar7 == 1) {
      if (*(char *)(param_1 + 0x152) != '\x02') {
        if (*(char *)(param_1 + 0x152) == '\0') {
          *(float *)(param_1 + 0x14c) = FLOAT_80439db0;
        }
        *(undefined1 *)(param_1 + 0x152) = 1;
        *(undefined2 *)(param_1 + 0x150) = *(undefined2 *)(param_1 + 0x5ac);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x152) = 0;
    }
    *(float *)(param_1 + 0x14c) =
         FLOAT_80439e34 * *(float *)(param_1 + 0x5f4) + *(float *)(param_1 + 0x14c);
    if (*(char *)(param_1 + 0x152) == '\x01') {
      if (*(float *)(param_1 + 0x14c) < FLOAT_80439e38) {
        *(float *)(param_1 + 0x14c) = FLOAT_80439e38;
      }
    }
    else if (*(float *)(param_1 + 0x14c) < FLOAT_80439da8) {
      *(float *)(param_1 + 0x14c) = FLOAT_80439da8;
    }
    if (FLOAT_80439da8 < *(float *)(param_1 + 0x14c)) {
      dVar10 = zz_0045204_(*(short *)(param_1 + 0x150));
      *(float *)(param_1 + 0x20) =
           (float)(dVar11 * (double)(float)((double)*(float *)(param_1 + 0x14c) * dVar10) +
                  (double)*(float *)(param_1 + 0x20));
      dVar10 = zz_0045238_(*(short *)(param_1 + 0x150));
      *(float *)(param_1 + 0x28) =
           (float)(dVar11 * (double)(float)((double)*(float *)(param_1 + 0x14c) * dVar10) +
                  (double)*(float *)(param_1 + 0x28));
    }
    *(undefined2 *)(param_1 + 0x5aa) = uVar2;
    *(undefined2 *)(param_1 + 0x5ac) = uVar3;
  }
  zz_00677b0_(param_1);
  return;
}



// ==== 8012eae8  FUN_8012eae8 ====

void FUN_8012eae8(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80439db8;
  *(undefined1 *)(param_1 + 0x592) = 0;
  *(byte *)(param_1 + 0x597) = *(byte *)(param_1 + 0x597) & 0xfb;
  *(float *)(param_1 + 0x694) = fVar1 + *(float *)(param_1 + 0x1dc8);
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a5a4_(param_1);
  return;
}



// ==== 8012eb3c  FUN_8012eb3c ====

void FUN_8012eb3c(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80333678)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8012eb8c  FUN_8012eb8c ====

void FUN_8012eb8c(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  fVar1 = FLOAT_80439ddc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  zz_004beb8_((double)FLOAT_80439dbc,param_1,0xf,4,3,0xffffffff,0xffffffff);
  zz_006d144_(param_1,0xc1);
  dVar3 = (double)FLOAT_80439dd8;
  *(float *)(param_1 + 0xd4) = FLOAT_80439e3c;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x44) / -*(float *)(param_1 + 0xd4);
  *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x48) / -*(float *)(param_1 + 0xd4);
  FUN_80067310(dVar3,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - *(float *)(param_1 + 0x1dc8);
  iVar2 = zz_006dbe0_(param_1,2,1,1);
  if (iVar2 == 1) {
    *(undefined1 *)(param_1 + 0x544) = 1;
    *(undefined1 *)(param_1 + 0x592) = 1;
    *(byte *)(param_1 + 0x597) = *(byte *)(param_1 + 0x597) | 4;
  }
  else {
    *(undefined1 *)(param_1 + 0x544) = 0;
    *(undefined1 *)(param_1 + 0x6e8) = 0;
  }
  return;
}



// ==== 8012ecc0  FUN_8012ecc0 ====

void FUN_8012ecc0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439dd8,param_1,*(short *)(param_1 + 0x54a));
  fVar2 = FLOAT_80439da8;
  fVar1 = *(float *)(param_1 + 0xd4) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0xd4) = fVar1;
  if (fVar1 <= fVar2) {
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar2;
  }
  zz_00677b0_(param_1);
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  if ((iVar3 != 1) && (FLOAT_80439da8 < *(float *)(param_1 + 0x558))) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 8012ed80  FUN_8012ed80 ====

void FUN_8012ed80(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_80439dd8,param_1,*(short *)(param_1 + 0x54a));
  fVar2 = FLOAT_80439da8;
  fVar1 = *(float *)(param_1 + 0xd4) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0xd4) = fVar1;
  if (fVar1 <= fVar2) {
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar2;
  }
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    if (*(char *)(param_1 + 0x544) == '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x03';
    }
    else {
      dVar3 = (double)FLOAT_80439dbc;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
      *(undefined1 *)(param_1 + 0x542) = 0;
      zz_004beb8_(dVar3,param_1,0xf,4,5,0xffffffff,0xffffffff);
      fVar1 = FLOAT_80439da8;
      *(float *)(param_1 + 0x558) = FLOAT_80439db8;
      *(undefined2 *)(param_1 + 0x146) = 1;
      *(undefined2 *)(param_1 + 0x148) = 0;
      *(float *)(param_1 + 0x44) = fVar1;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x48) = fVar1;
      *(float *)(param_1 + 0x50) = fVar1;
      *(float *)(param_1 + 0x14c) = fVar1;
      *(undefined1 *)(param_1 + 0x152) = 2;
    }
  }
  return;
}



// ==== 8012ee98  FUN_8012ee98 ====

void FUN_8012ee98(int param_1)

{
  float fVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    dVar2 = (double)FLOAT_80439dbc;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    zz_004beb8_(dVar2,param_1,0xf,4,5,0xffffffff,0xffffffff);
    fVar1 = FLOAT_80439da8;
    *(float *)(param_1 + 0x558) = FLOAT_80439db8;
    *(undefined2 *)(param_1 + 0x146) = 1;
    *(undefined2 *)(param_1 + 0x148) = 0;
    *(float *)(param_1 + 0x14c) = fVar1;
    *(undefined1 *)(param_1 + 0x152) = 2;
  }
  return;
}



// ==== 8012ef30  FUN_8012ef30 ====

/* WARNING: Removing unreachable block (ram,0x8012f18c) */
/* WARNING: Removing unreachable block (ram,0x8012ef40) */

void FUN_8012ef30(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  float fVar4;
  int iVar5;
  bool bVar6;
  double dVar7;
  double dVar8;
  
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x01') {
    iVar5 = zz_004cd24_(param_1,0xf);
    if (iVar5 == 1) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    if ((*(uint *)(param_1 + 0x5d4) & 0x80) != 0) {
      *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) + FLOAT_80439e24;
    }
    if (*(char *)(param_1 + 0x1b01) != '\0') {
      *(float *)(param_1 + 0x1dcc) = *(float *)(param_1 + 0x1dcc) + FLOAT_80439dec;
      *(short *)(param_1 + 0x146) = *(short *)(param_1 + 0x146) + 1;
    }
    zz_004cd24_(param_1,0xf);
    fVar4 = -(FLOAT_80439de0 * *(float *)(param_1 + 0x1dc8) - *(float *)(param_1 + 0x558));
    bVar6 = fVar4 < FLOAT_80439da8;
    *(float *)(param_1 + 0x558) = fVar4;
    if (((bVar6) && (1 < *(short *)(param_1 + 0x146))) || (4 < *(short *)(param_1 + 0x146))) {
      dVar7 = (double)FLOAT_80439db0;
      *(float *)(param_1 + 0x1dcc) = FLOAT_80439dd8;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      zz_004beb8_(dVar7,param_1,0xf,4,6,3,1);
    }
  }
  *(short *)(param_1 + 0x148) = *(short *)(param_1 + 0x148) + -0x300;
  dVar7 = zz_0045204_(*(short *)(param_1 + 0x148));
  *(float *)(param_1 + 0x24) =
       FLOAT_80439de0 * (float)((double)*(float *)(param_1 + 0xb4) * dVar7) +
       *(float *)(param_1 + 0x24);
  zz_006d144_(param_1,0xc0);
  uVar2 = *(undefined2 *)(param_1 + 0x5aa);
  dVar7 = (double)(*(float *)(param_1 + 0x5f4) * *(float *)(param_1 + 0x5f8));
  uVar3 = *(undefined2 *)(param_1 + 0x5ac);
  iVar5 = zz_0066ac0_(param_1,0);
  if (iVar5 == 1) {
    if (*(char *)(param_1 + 0x152) != '\x02') {
      if (*(char *)(param_1 + 0x152) == '\0') {
        *(float *)(param_1 + 0x14c) = FLOAT_80439db0;
      }
      *(undefined1 *)(param_1 + 0x152) = 1;
      *(undefined2 *)(param_1 + 0x150) = *(undefined2 *)(param_1 + 0x5ac);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x152) = 0;
  }
  *(float *)(param_1 + 0x14c) =
       FLOAT_80439e34 * *(float *)(param_1 + 0x5f4) + *(float *)(param_1 + 0x14c);
  if (*(char *)(param_1 + 0x152) == '\x01') {
    if (*(float *)(param_1 + 0x14c) < FLOAT_80439e38) {
      *(float *)(param_1 + 0x14c) = FLOAT_80439e38;
    }
  }
  else if (*(float *)(param_1 + 0x14c) < FLOAT_80439da8) {
    *(float *)(param_1 + 0x14c) = FLOAT_80439da8;
  }
  if (FLOAT_80439da8 < *(float *)(param_1 + 0x14c)) {
    dVar8 = zz_0045204_(*(short *)(param_1 + 0x150));
    *(float *)(param_1 + 0x20) =
         (float)(dVar7 * (double)(float)((double)*(float *)(param_1 + 0x14c) * dVar8) +
                (double)*(float *)(param_1 + 0x20));
    dVar8 = zz_0045238_(*(short *)(param_1 + 0x150));
    *(float *)(param_1 + 0x28) =
         (float)(dVar7 * (double)(float)((double)*(float *)(param_1 + 0x14c) * dVar8) +
                (double)*(float *)(param_1 + 0x28));
  }
  *(undefined2 *)(param_1 + 0x5aa) = uVar2;
  *(undefined2 *)(param_1 + 0x5ac) = uVar3;
  zz_00677b0_(param_1);
  return;
}



// ==== 8012f1b0  FUN_8012f1b0 ====

void FUN_8012f1b0(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80439db8;
  *(undefined1 *)(param_1 + 0x592) = 0;
  *(byte *)(param_1 + 0x597) = *(byte *)(param_1 + 0x597) & 0xfb;
  *(float *)(param_1 + 0x694) = fVar1 + *(float *)(param_1 + 0x1dc8);
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a5a4_(param_1);
  return;
}



// ==== 8012f330  FUN_8012f330 ====

void FUN_8012f330(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x309) {
    zz_0131c14_(param_1,8);
    zz_0131c14_(param_1,9);
    zz_00c74ec_(param_1,9);
    *(undefined1 *)(param_1 + 0x144) = 0;
  }
  else if (sVar1 < 0x309) {
    if (sVar1 == 0x305) {
      zz_0131c14_(param_1,0);
      zz_0131c14_(param_1,1);
      zz_0131c14_(param_1,2);
      zz_00c74ec_(param_1,9);
      *(undefined1 *)(param_1 + 0x144) = 3;
    }
  }
  else if (sVar1 < 0x30b) {
    zz_0131c14_(param_1,3);
    zz_0131c14_(param_1,4);
    zz_0131c14_(param_1,5);
    zz_0131c14_(param_1,6);
    zz_0131c14_(param_1,7);
    zz_00c74ec_(param_1,9);
    *(undefined1 *)(param_1 + 0x144) = 0xf;
  }
  return;
}



// ==== 8012f430  FUN_8012f430 ====

void FUN_8012f430(int param_1)

{
  zz_010a4ac_(param_1);
  return;
}



// ==== 8012f464  FUN_8012f464 ====

void FUN_8012f464(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80333a48)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 8012f4a8  FUN_8012f4a8 ====

void FUN_8012f4a8(int param_1,uint param_2)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x309) {
    if ((param_2 & 2) != 0) {
      zz_001ab6c_(param_1,0x6a);
    }
    if ((param_2 & 1) != 0) {
      zz_001ab6c_(param_1,0x6b);
    }
  }
  return;
}



// ==== 8012f520  FUN_8012f520 ====

void FUN_8012f520(int param_1,uint param_2)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x309) {
    if ((param_2 & 2) != 0) {
      zz_001ab6c_(param_1,0x8c);
    }
    if ((param_2 & 1) != 0) {
      zz_001ab6c_(param_1,0x8d);
    }
  }
  return;
}



// ==== 8012f5bc  FUN_8012f5bc ====

void FUN_8012f5bc(int param_1)

{
  (*(code *)(&PTR_FUN_80333a60)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8012f5f8  FUN_8012f5f8 ====

void FUN_8012f5f8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80333a6c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8012f640  FUN_8012f640 ====

void FUN_8012f640(int param_1)

{
  zz_010b2f4_(param_1);
  return;
}



// ==== 8012f664  FUN_8012f664 ====

void FUN_8012f664(int param_1)

{
  zz_010b7ac_(param_1);
  return;
}



// ==== 8012f688  FUN_8012f688 ====

void FUN_8012f688(int param_1)

{
  zz_010bd10_(param_1);
  return;
}



// ==== 8012f6ac  FUN_8012f6ac ====

void FUN_8012f6ac(int param_1)

{
  zz_010c220_(param_1);
  return;
}



// ==== 8012f6d0  FUN_8012f6d0 ====

void FUN_8012f6d0(int param_1)

{
  zz_010c590_(param_1);
  return;
}



// ==== 8012f6f4  FUN_8012f6f4 ====

void FUN_8012f6f4(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x309) {
    zz_012fb20_(param_1);
  }
  else {
    zz_012f728_(param_1);
  }
  return;
}



// ==== 8012f728  zz_012f728_ ====

void zz_012f728_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80333a80)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8012f778  FUN_8012f778 ====

void FUN_8012f778(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_80439e40;
  *(float *)(param_1 + 0x50) = FLOAT_80439e40;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(undefined1 *)(param_1 + 0x6eb) = 4;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 2;
  }
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80439e44;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  zz_012f854_(param_1);
  return;
}



// ==== 8012f854  zz_012f854_ ====

void zz_012f854_(int param_1)

{
  float fVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439e48,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  fVar1 = FLOAT_80439e40;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    if ((*(byte *)(param_1 + 0x144) & 0xf) == 0) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x44) = fVar1;
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        zz_006a474_(param_1);
      }
      else {
        zz_006a5a4_(param_1);
      }
    }
    else {
      dVar2 = (double)FLOAT_80439e44;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      zz_004beb8_(dVar2,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 8012f958  FUN_8012f958 ====

void FUN_8012f958(int param_1)

{
  int iVar1;
  int iVar2;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80439e48,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    if (*(char *)(param_1 + 0x1b03) == '\0') {
      *(undefined1 *)(param_1 + 0x1cef) = 0;
      iVar1 = 0;
      *(char *)(param_1 + 0x6eb) = *(char *)(param_1 + 0x6eb) + -1;
      iVar2 = 4;
      do {
        if (((int)*(char *)(param_1 + 0x144) & 1 << iVar1) != 0) {
          if (*(short *)(param_1 + 1000) == 0x305) {
            zz_013212c_(param_1,iVar1,param_1 + 0x144);
          }
          else if (*(short *)(param_1 + 1000) == 0x30a) {
            zz_013212c_(param_1,iVar1 + 6,param_1 + 0x144);
          }
          break;
        }
        iVar1 = iVar1 + 1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    if ((*(uint *)(param_1 + 0x5b4) & 0x400) != 0) {
      if ((*(byte *)(param_1 + 0x144) & 0xf) != 0) {
        if ('\0' < *(char *)(param_1 + 0x6eb)) {
          zz_004beb8_((double)FLOAT_80439e44,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),10,2);
        }
      }
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
    *(float *)(param_1 + 0x694) = FLOAT_80439e4c + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 8012fb20  zz_012fb20_ ====

void zz_012fb20_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_804345c0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8012fb6c  FUN_8012fb6c ====

void FUN_8012fb6c(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(undefined1 *)(param_1 + 0x6ea) = 4;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 5;
  }
  fVar2 = FLOAT_80439e40;
  *(float *)(param_1 + 0x50) = FLOAT_80439e40;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439e48,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80439e44;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8012fc64  FUN_8012fc64 ====

void FUN_8012fc64(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cf0) < '\0') {
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439e48,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar2 = zz_00679d0_(param_1);
  fVar1 = FLOAT_80439e40;
  if (((iVar2 != 0) && ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) &&
     (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439e50 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 8012fd9c  zz_012fd9c_ ====

void zz_012fd9c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x103) || (*(short *)(param_1 + 1000) == 0x106)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_8012feac;
    *(code **)(puVar1 + 0x10c) = FUN_80130154;
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



// ==== 8012feac  FUN_8012feac ====

void FUN_8012feac(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80334e10)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8012ff00  FUN_8012ff00 ====

void FUN_8012ff00(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 extraout_r4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar4 = *(char *)(param_9 + 0x13) * 0x1c;
  if (*(int *)(&DAT_80334df0 + iVar4) == 0) {
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    uVar6 = zz_0089100_(param_9,(int)*(char *)(*(int *)(param_9 + 0x90) + 0x3e4) + 0x10,1);
    *(undefined1 *)(param_9 + 0x84) = 0x55;
  }
  else {
    *(int *)(param_9 + 0x100) = *(int *)(&DAT_80334df0 + iVar4);
    uVar6 = zz_0089100_(param_9,(int)*(char *)(*(int *)(param_9 + 0x90) + 0x3e4) + 0x10,1);
  }
  fVar1 = FLOAT_80439e58;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80334dda + iVar4);
  uVar2 = *(undefined4 *)(&DAT_80334de0 + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80334ddc + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80334de4 + iVar4);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80334de8 + iVar4);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80334dec + iVar4);
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  iVar3 = zz_0006f98_(param_9);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80334dd8 + iVar4),iVar3 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar5 = iVar3 + 0xc28;
  iVar4 = (int)*(short *)(&DAT_80334dd8 + iVar4);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),iVar4,iVar5,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80439e5c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_013004c_(param_9);
  return;
}



// ==== 8013004c  zz_013004c_ ====

void zz_013004c_(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  
  iVar2 = *(int *)(param_1 + 0x90);
  if (*(char *)(param_1 + 0x13) < '\x01') {
    if (*(char *)(iVar2 + 0x6e8) < '\x01') {
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + FLOAT_80439e74;
    }
    else {
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) - FLOAT_80439e74;
    }
    if (FLOAT_80439e58 < *(float *)(param_1 + 0x58)) {
      *(float *)(param_1 + 0x58) = FLOAT_80439e58;
    }
    if (*(float *)(param_1 + 0x58) < FLOAT_80439e70) {
      *(float *)(param_1 + 0x58) = FLOAT_80439e70;
    }
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x58);
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x58);
    return;
  }
  dVar4 = (double)*(float *)(param_1 + 0x58);
  dVar3 = (double)FLOAT_80439e58;
  if (dVar4 <= dVar3) {
    dVar3 = (double)FLOAT_80439e60;
  }
  fVar1 = (float)(DOUBLE_80439e68 * (double)(float)(dVar3 - dVar4) + dVar4);
  if (((*(char *)(param_1 + 0x13) == '\x01') && (*(char *)(iVar2 + 0x6e9) == '\0')) &&
     ((*(byte *)(iVar2 + 0x655) & 1) == 0)) {
    fVar1 = FLOAT_80439e70;
  }
  *(float *)(param_1 + 0x60) = fVar1;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  return;
}



// ==== 80130134  FUN_80130134 ====

void FUN_80130134(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80130154  FUN_80130154 ====

void FUN_80130154(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if ((double)FLOAT_80439e70 < (double)*(float *)(param_9 + 0x58)) {
    if ((*(char *)(param_9 + 0x13) == '\0') && (*(char *)(iVar1 + 0x159) != '\0')) {
      return;
    }
    if ((*(char *)(iVar1 + 0xae) == '\0') && (*(char *)(iVar1 + 0x3ec) != '\x04')) {
      iVar1 = *(int *)(param_9 + 0xe0);
      uVar2 = 1;
    }
    else {
      iVar1 = *(int *)(param_9 + 0xe4);
      uVar2 = 0x44;
    }
    zz_00076d0_((double)*(float *)(param_9 + 0x58),param_2,param_3,param_4,param_5,param_6,param_7,
                param_8,iVar1,(float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,
                param_15,param_16);
    zz_00097b4_(iVar1,uVar2);
  }
  return;
}



// ==== 80130330  FUN_80130330 ====

void FUN_80130330(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int unaff_r28;
  undefined8 uVar4;
  
  sVar1 = *(short *)(param_9 + 1000);
  if ((sVar1 == 0x106) || (sVar1 == 0x107)) {
    if (sVar1 == 0x106) {
      unaff_r28 = 0;
    }
    else if (sVar1 == 0x107) {
      unaff_r28 = 1;
    }
    iVar3 = zz_0006f98_(param_9);
    iVar2 = unaff_r28 * 4;
    uVar4 = zz_00086b8_((double)FLOAT_80439e78,param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,*(int *)(iVar3 + 0x600),
                        *(int *)(iVar3 + *(int *)(&DAT_804345c8 + iVar2) * 4 + 0x708),param_11,
                        param_12,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar3 + *(int *)(&DAT_804345c8 + iVar2) * 4 + 0x708),extraout_r4,param_11,
                param_12,param_13,param_14,param_15,param_16);
    uVar4 = zz_00086b8_((double)FLOAT_80439e78,param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,*(int *)(iVar3 + 0x600),
                        *(int *)(iVar3 + *(int *)(&DAT_804345c8 + iVar2) * 4 + 0x788),param_11,
                        param_12,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar3 + *(int *)(&DAT_804345c8 + iVar2) * 4 + 0x788),extraout_r4_00,
                param_11,param_12,param_13,param_14,param_15,param_16);
    if (*(short *)(param_9 + 1000) == 0x106) {
      zz_01c621c_(param_9,2);
      zz_01c621c_(param_9,3);
    }
    else {
      zz_01c621c_(param_9,0);
      zz_01c621c_(param_9,1);
    }
  }
  if (*(short *)(param_9 + 1000) == 0x103) {
    zz_012fd9c_(param_9,0);
    zz_012fd9c_(param_9,1);
  }
  return;
}



// ==== 801304b8  FUN_801304b8 ====

void FUN_801304b8(int param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  
  sVar2 = *(short *)(param_1 + 1000);
  if (sVar2 < 0x106) {
    if (sVar2 == 0x103) {
      *(undefined1 *)(param_1 + 0x1d94) = 0;
    }
  }
  else if (sVar2 < 0x108) {
    *(undefined1 *)(param_1 + 0x1d95) = 0;
    *(undefined1 *)(param_1 + 0x1d94) = 0;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    *(undefined2 *)(param_1 + 0x1918) = 0;
  }
  if (((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) && (*(float *)(param_1 + 0x694) <= FLOAT_80439e78)
     ) {
    if ((*(short *)(param_1 + 1000) == 0x106) && (iVar3 = zz_006dbe0_(param_1,0,1,1), iVar3 != 0)) {
      *(byte *)(param_1 + 0x15b) = *(byte *)(param_1 + 0x15b) | 1;
      zz_00e058c_(param_1,2,10);
      zz_00f036c_(param_1,0xeb);
    }
    if ((*(short *)(param_1 + 1000) == 0x107) && (iVar3 = zz_006dbe0_(param_1,0,1,1), iVar3 != 0)) {
      *(byte *)(param_1 + 0x15b) =
           *(byte *)(param_1 + 0x15b) | (byte)(1 << ((int)*(short *)(param_1 + 0x774) & 1U));
      zz_00e058c_(param_1,3,((byte)*(undefined2 *)(param_1 + 0x774) & 1) + 0xb);
      zz_00f036c_(param_1,0xaa);
    }
    *(float *)(param_1 + 0x694) = FLOAT_80439e7c + *(float *)(param_1 + 0x1dc8);
  }
  if ((*(uint *)(param_1 + 0x5bc) & 0x400) != 0) {
    if ((*(short *)(param_1 + 1000) == 0x107) &&
       (*(short *)(param_1 + 0x774) < *(short *)(param_1 + 0x78e))) {
      *(undefined1 *)(param_1 + 0x6f7) = 1;
    }
    if ((*(short *)(param_1 + 1000) == 0x103) && (*(float *)(param_1 + 0x694) <= FLOAT_80439e78)) {
      cVar1 = *(char *)(param_1 + 0x159);
      if (cVar1 == '\x01') {
        iVar3 = zz_006dbe0_(param_1,2,1,1);
        if (iVar3 == 0) {
          zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),2);
        }
        else {
          *(char *)(param_1 + 0x15a) = *(char *)(param_1 + 0x15a) + '\x01';
          zz_00f0214_(param_1,4,3);
          if ('\x06' < *(char *)(param_1 + 0x15a)) {
            *(undefined1 *)(param_1 + 0x15a) = 7;
          }
        }
        *(float *)(param_1 + 0x694) = FLOAT_80439e7c + *(float *)(param_1 + 0x1dc8);
      }
      else if ((cVar1 < '\x01') && (-1 < cVar1)) {
        iVar3 = zz_006dbe0_(param_1,2,1,1);
        if (iVar3 == 0) {
          zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),2);
        }
        else {
          *(undefined1 *)(param_1 + 0x159) = 1;
          *(undefined1 *)(param_1 + 0x15a) = 1;
          zz_013b194_(param_1);
        }
        *(float *)(param_1 + 0x694) = FLOAT_80439e7c + *(float *)(param_1 + 0x1dc8);
      }
    }
  }
  if (*(char *)(param_1 + 0x159) == '\x01') {
    zz_00f0104_(param_1,4,3);
  }
  return;
}



// ==== 80130788  FUN_80130788 ====

void FUN_80130788(int param_1)

{
  (*(code *)(&PTR_FUN_80335cb8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801307c4  FUN_801307c4 ====

void FUN_801307c4(int param_1)

{
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_80439e88) * FLOAT_80439e80);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80335cc8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80130844  FUN_80130844 ====

void FUN_80130844(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80335cdc)[*(char *)(param_1 + 0x540)])();
  return;
}



