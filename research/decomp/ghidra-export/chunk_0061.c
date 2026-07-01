// ==== 801f2d40  FUN_801f2d40 ====

void FUN_801f2d40(int param_1)

{
  int iVar1;
  
  iVar1 = zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  if (iVar1 == 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_0089444_(param_1);
    zz_008aff0_(param_1);
  }
  (*(code *)(&PTR_FUN_803a2320)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801f2dbc  FUN_801f2dbc ====

/* WARNING: Removing unreachable block (ram,0x801f3068) */
/* WARNING: Removing unreachable block (ram,0x801f2dcc) */

void FUN_801f2dbc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  double dVar6;
  undefined8 uVar7;
  float fStack_48;
  float local_44;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 local_28;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(undefined1 *)(param_9 + 0x19) = 0;
  iVar5 = *(int *)(param_9 + 0x90);
  iVar3 = *(char *)(param_9 + 0x13) * 0x2c;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  dVar6 = (double)zz_0089100_(param_9,0,1);
  if ((*(char *)(param_9 + 0x13) == '\x06') || (*(char *)(param_9 + 0x13) == '\a')) {
    *(undefined1 *)(param_9 + 0x84) = 0x5f;
  }
  else {
    *(undefined1 *)(param_9 + 0x84) = 0x57;
  }
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_803a1dd8 + iVar3);
  uVar2 = *(undefined4 *)(&DAT_803a1de0 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803a1ddc + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803a1de4 + iVar3);
  *(undefined2 *)(param_9 + 0x72) = *(undefined2 *)(&DAT_803a1dea + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_803a1dec + iVar3);
  iVar4 = *(int *)(param_9 + 200);
  if (iVar4 == 0) {
    *(undefined2 *)(param_9 + 0x70) = *(undefined2 *)(&DAT_803a1de8 + iVar3);
  }
  else {
    iVar3 = iVar5 + *(char *)(param_9 + 0x89) * 0x30;
    local_30 = *(float *)(iVar3 + 0x8e0);
    local_2c = *(undefined4 *)(iVar3 + 0x8f0);
    local_28 = *(undefined4 *)(iVar3 + 0x900);
    local_3c = *(float *)(iVar4 + 100);
    local_38 = *(undefined4 *)(iVar4 + 0x68);
    local_34 = *(undefined4 *)(iVar4 + 0x6c);
    gnt4_PSVECSubtract_bl(&local_3c,&local_30,&fStack_48);
    gnt4_PSVECNormalize_bl(&fStack_48,&fStack_48);
    dVar6 = -(double)local_44;
    local_44 = FLOAT_8043c628;
    param_2 = gnt4_PSVECMag_bl(&fStack_48);
    iVar3 = FUN_800452a0(dVar6,param_2);
    *(short *)(param_9 + 0x70) = (short)iVar3;
    iVar3 = *(char *)(param_9 + 0x13) * 0x2c;
    if (*(short *)(&DAT_803a1e00 + iVar3) < *(short *)(param_9 + 0x70)) {
      *(short *)(param_9 + 0x70) = *(short *)(&DAT_803a1e00 + iVar3);
    }
    else if (*(short *)(param_9 + 0x70) < *(short *)(&DAT_803a1e02 + iVar3)) {
      *(short *)(param_9 + 0x70) = *(short *)(&DAT_803a1e02 + iVar3);
    }
  }
  fVar1 = FLOAT_8043c628;
  *(float *)(param_9 + 0x60) = FLOAT_8043c628;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  iVar3 = zz_0006f98_(iVar5);
  if (*(char *)(param_9 + 0x13) < '\b') {
    uVar7 = zz_000726c_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),
                        *(float **)(&DAT_803a2300 + *(char *)(param_9 + 0x11) * 0x10),
                        (int)*(char *)(param_9 + 0x88),iVar4,in_r8,in_r9,in_r10);
    zz_000726c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),
                *(float **)(&DAT_803a2304 + *(char *)(param_9 + 0x11) * 0x10),
                (int)*(char *)(param_9 + 0x88),iVar4,in_r8,in_r9,in_r10);
  }
  else {
    uVar7 = zz_000726c_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),
                        *(float **)(&DAT_803a2308 + *(char *)(param_9 + 0x11) * 0x10),
                        (int)*(char *)(param_9 + 0x88),iVar4,in_r8,in_r9,in_r10);
    zz_000726c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),
                *(float **)(&DAT_803a230c + *(char *)(param_9 + 0x11) * 0x10),
                (int)*(char *)(param_9 + 0x88),iVar4,in_r8,in_r9,in_r10);
  }
  fVar1 = FLOAT_8043c62c;
  *(undefined1 *)(param_9 + 0x168) = 0;
  *(float *)(param_9 + 0xd4) = fVar1;
  *(undefined1 *)(param_9 + 0x82) = 0;
  FUN_801f308c(param_9);
  return;
}



// ==== 801f308c  FUN_801f308c ====

void FUN_801f308c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  int iVar10;
  float *pfVar11;
  bool bVar12;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float afStack_50 [3];
  float afStack_44 [13];
  
  fVar2 = FLOAT_8043c628;
  cVar1 = *(char *)(param_1 + 0x19);
  iVar10 = *(int *)(param_1 + 0x90);
  iVar8 = *(char *)(param_1 + 0x13) * 0x2c;
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 < '\x04') {
        fVar3 = *(float *)(param_1 + 0xd4) - FLOAT_8043c634;
        *(float *)(param_1 + 0xd4) = fVar3;
        if (fVar3 < fVar2) {
          *(undefined1 *)(param_1 + 0x18) = 2;
          *(undefined1 *)(param_1 + 0x82) = 0;
          *(float *)(param_1 + 0x144) = fVar2;
        }
        else {
          fVar3 = *(float *)(param_1 + 0x144) - FLOAT_8043c648;
          *(float *)(param_1 + 0x144) = fVar3;
          if (fVar3 < fVar2) {
            *(float *)(param_1 + 0x144) = fVar2;
          }
        }
        zz_0007cac_((double)*(float *)(param_1 + 0x144),*(int *)(param_1 + 0xe4));
      }
      goto LAB_801f3320;
    }
    if (cVar1 == '\0') {
      bVar12 = FLOAT_8043c628 < *(float *)(param_1 + 0xd8);
      *(float *)(param_1 + 0xd8) = *(float *)(param_1 + 0xd8) - FLOAT_8043c634;
      if (bVar12) {
        return;
      }
      FUN_801fe424(iVar10,*(undefined1 *)(param_1 + 0x13),(undefined4 *)(param_1 + 0x70));
      *(float *)(param_1 + 0xd8) = FLOAT_8043c630;
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    }
    else if (cVar1 < '\0') goto LAB_801f3320;
    fVar2 = FLOAT_8043c628;
    *(float *)(param_1 + 0xd8) = *(float *)(param_1 + 0xd8) - *(float *)(iVar10 + 0x1dc8);
    if (fVar2 < *(float *)(param_1 + 0xd8)) {
      return;
    }
    *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
  fVar5 = FLOAT_8043c634;
  fVar3 = FLOAT_8043c628;
  fVar2 = *(float *)(param_1 + 0xd4) - FLOAT_8043c634;
  *(float *)(param_1 + 0xd4) = fVar2;
  fVar6 = FLOAT_8043c638;
  fVar4 = FLOAT_8043c62c;
  if (fVar2 < fVar3) {
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(&DAT_803a1df0 + iVar8);
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(&DAT_803a1df4 + iVar8);
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(&DAT_803a1df8 + iVar8);
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(float *)(param_1 + 0xd4) = fVar6;
    *(float *)(param_1 + 0x144) = fVar5;
    zz_0007cac_((double)*(float *)(param_1 + 0x144),*(int *)(param_1 + 0xe4));
    local_68 = FLOAT_8043c628;
    local_64 = FLOAT_8043c628;
    local_60 = FLOAT_8043c63c;
    local_5c = FLOAT_8043c628;
    local_58 = FLOAT_8043c628;
    local_54 = FLOAT_8043c640;
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),&local_5c,&local_5c);
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),&local_68,&local_68);
    FUN_801f3580(&local_5c,&local_5c,&local_68);
    iVar7 = zz_003e6e4_(&local_5c,&local_68,afStack_50);
    if (0 < iVar7) {
      zz_0085e00_(param_1,afStack_50,0x1a);
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(&DAT_803a1df0 + iVar8);
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(&DAT_803a1df4 + iVar8);
    *(float *)(param_1 + 0x60) =
         *(float *)(param_1 + 0x60) + *(float *)(&DAT_803a1df0 + iVar8) / fVar4;
  }
  if (*(char *)(param_1 + 0x168) == '\0') {
    *(undefined1 *)(param_1 + 0x168) = 1;
    FUN_80047aa4(param_1);
    zz_00aedc0_(iVar10,(float *)(param_1 + 0x114),1,*(undefined1 *)(param_1 + 0x88));
    zz_00f061c_((double)FLOAT_8043c644,iVar10,0x110);
  }
LAB_801f3320:
  if (*(char *)(param_1 + 0x18) < '\x02') {
    FUN_801f345c(param_1,afStack_44);
    fVar2 = FLOAT_8043c628;
    pfVar11 = (float *)(param_1 + 0x150);
    *(float *)(param_1 + 0x150) = FLOAT_8043c628;
    *(float *)(param_1 + 0x154) = fVar2;
    *(float *)(param_1 + 0x158) = fVar2;
    gnt4_PSMTXMultVec_bl(afStack_44,pfVar11,pfVar11);
    fVar3 = FLOAT_8043c640;
    fVar2 = FLOAT_8043c628;
    pfVar9 = (float *)(param_1 + 0x15c);
    *(float *)(param_1 + 0x15c) = FLOAT_8043c628;
    *(float *)(param_1 + 0x160) = fVar2;
    *(float *)(param_1 + 0x164) = fVar2;
    *(float *)(param_1 + 0x164) = fVar3 * *(float *)(param_1 + 0x60);
    gnt4_PSMTXMultVec_bl(afStack_44,pfVar9,pfVar9);
    zz_0139a6c_(param_1,pfVar11,pfVar9,(char)*(undefined4 *)(&DAT_803a1dfc + iVar8));
  }
  return;
}



// ==== 801f33c8  FUN_801f33c8 ====

void FUN_801f33c8(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801f33e0  FUN_801f33e0 ====

void FUN_801f33e0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801f3400  FUN_801f3400 ====

void FUN_801f3400(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (*(char *)(param_9 + 0x19) < '\x02') {
    iVar1 = *(int *)(param_9 + 0xe0);
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,0x44);
  return;
}



// ==== 801f345c  FUN_801f345c ====

/* WARNING: Removing unreachable block (ram,0x801f3530) */
/* WARNING: Removing unreachable block (ram,0x801f3500) */
/* WARNING: Removing unreachable block (ram,0x801f34d0) */

void FUN_801f345c(int param_1,float *param_2)

{
  byte bVar1;
  float local_88;
  undefined4 local_84;
  undefined4 local_80;
  float afStack_7c [3];
  float local_70;
  undefined4 local_60;
  undefined4 local_50;
  float afStack_4c [16];
  
  bVar1 = *(byte *)(param_1 + 0x84);
  gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
                    afStack_7c);
  gnt4_PSMTXMultVec_bl(afStack_7c,(float *)(param_1 + 100),&local_88);
  local_70 = local_88;
  local_60 = local_84;
  local_50 = local_80;
  if ((bVar1 & 8) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c64c *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                               0x3ff0000000000000)),afStack_4c,0x7a);
    gnt4_PSMTXConcat_bl(afStack_7c,afStack_4c,afStack_7c);
  }
  if ((bVar1 & 4) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c64c *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                               0x3ff0000000000000)),afStack_4c,0x79);
    gnt4_PSMTXConcat_bl(afStack_7c,afStack_4c,afStack_7c);
  }
  if ((bVar1 & 2) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c64c *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                               0x3ff0000000000000)),afStack_4c,0x78);
    gnt4_PSMTXConcat_bl(afStack_7c,afStack_4c,afStack_7c);
  }
  gnt4_PSMTXCopy_bl(afStack_7c,param_2);
  return;
}



// ==== 801f3580  FUN_801f3580 ====

void FUN_801f3580(float *param_1,float *param_2,float *param_3)

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



// ==== 801f3784  FUN_801f3784 ====

/* WARNING: Removing unreachable block (ram,0x801f3890) */
/* WARNING: Removing unreachable block (ram,0x801f3794) */

void FUN_801f3784(double param_1,int param_2,char param_3)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_2 + 1000) == 0xe03) && (param_3 < '\b')) &&
     (puVar1 = zz_0088aa0_(param_2,3,8,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x13] = param_3;
    puVar1[0x83] = 0x10;
    *(code **)(puVar1 + 0xc) = FUN_801f38b0;
    *(code **)(puVar1 + 0x10c) = FUN_801f3edc;
    *(float *)(puVar1 + 0xd8) = (float)param_1;
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



// ==== 801f38b0  FUN_801f38b0 ====

void FUN_801f38b0(int param_1)

{
  int iVar1;
  
  iVar1 = zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  if (iVar1 == 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_0089444_(param_1);
    zz_008aff0_(param_1);
  }
  (*(code *)(&PTR_FUN_803a2490)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801f392c  FUN_801f392c ====

/* WARNING: Removing unreachable block (ram,0x801f3b48) */
/* WARNING: Removing unreachable block (ram,0x801f393c) */

void FUN_801f392c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  double dVar5;
  undefined8 uVar6;
  float fStack_48;
  float local_44;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  float local_30;
  undefined4 local_2c;
  undefined4 local_28;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(undefined1 *)(param_9 + 0x19) = 0;
  iVar4 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  dVar5 = (double)zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x57;
  *(char *)(param_9 + 0x89) =
       (char)*(undefined2 *)(&DAT_803a2330 + *(char *)(param_9 + 0x13) * 0x2c);
  iVar2 = *(char *)(param_9 + 0x13) * 0x2c;
  uVar3 = *(undefined4 *)(&DAT_803a2338 + iVar2);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803a2334 + iVar2);
  *(undefined4 *)(param_9 + 0x68) = uVar3;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803a233c + iVar2);
  *(undefined2 *)(param_9 + 0x72) =
       *(undefined2 *)(&DAT_803a2342 + *(char *)(param_9 + 0x13) * 0x2c);
  *(undefined2 *)(param_9 + 0x74) =
       *(undefined2 *)(&DAT_803a2344 + *(char *)(param_9 + 0x13) * 0x2c);
  iVar2 = *(int *)(param_9 + 200);
  if (iVar2 == 0) {
    *(undefined2 *)(param_9 + 0x70) =
         *(undefined2 *)(&DAT_803a2340 + *(char *)(param_9 + 0x13) * 0x2c);
  }
  else {
    iVar4 = iVar4 + *(char *)(param_9 + 0x89) * 0x30;
    local_30 = *(float *)(iVar4 + 0x8e0);
    local_2c = *(undefined4 *)(iVar4 + 0x8f0);
    local_28 = *(undefined4 *)(iVar4 + 0x900);
    local_3c = *(float *)(iVar2 + 100);
    local_38 = *(undefined4 *)(iVar2 + 0x68);
    local_34 = *(undefined4 *)(iVar2 + 0x6c);
    gnt4_PSVECSubtract_bl(&local_3c,&local_30,&fStack_48);
    gnt4_PSVECNormalize_bl(&fStack_48,&fStack_48);
    dVar5 = -(double)local_44;
    local_44 = FLOAT_8043c650;
    param_2 = gnt4_PSVECMag_bl(&fStack_48);
    iVar4 = FUN_800452a0(dVar5,param_2);
    *(short *)(param_9 + 0x70) = (short)iVar4;
    iVar4 = *(char *)(param_9 + 0x13) * 0x2c;
    if (*(short *)(&DAT_803a2358 + iVar4) < *(short *)(param_9 + 0x70)) {
      *(short *)(param_9 + 0x70) = *(short *)(&DAT_803a2358 + iVar4);
    }
    else if (*(short *)(param_9 + 0x70) < *(short *)(&DAT_803a235a + iVar4)) {
      *(short *)(param_9 + 0x70) = *(short *)(&DAT_803a235a + iVar4);
    }
  }
  fVar1 = FLOAT_8043c650;
  *(float *)(param_9 + 0x60) = FLOAT_8043c650;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  iVar4 = zz_0006f78_(param_9);
  uVar6 = zz_000726c_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                      *(int *)(param_9 + 0xe0),(float *)0x2,(int)*(char *)(param_9 + 0x88),iVar2,
                      in_r8,in_r9,in_r10);
  iVar4 = zz_0006f78_(param_9);
  zz_000726c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
              *(int *)(param_9 + 0xe4),(float *)0x3,(int)*(char *)(param_9 + 0x88),iVar2,in_r8,in_r9
              ,in_r10);
  *(float *)(param_9 + 0xd4) = FLOAT_8043c654;
  *(undefined1 *)(param_9 + 0x168) = 0;
  *(undefined1 *)(param_9 + 0x82) = 0;
  FUN_801f3b68(param_9);
  return;
}



// ==== 801f3b68  FUN_801f3b68 ====

void FUN_801f3b68(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  float *pfVar9;
  bool bVar10;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float afStack_50 [3];
  float afStack_44 [13];
  
  fVar2 = FLOAT_8043c650;
  cVar1 = *(char *)(param_1 + 0x19);
  iVar8 = *(int *)(param_1 + 0x90);
  iVar6 = *(char *)(param_1 + 0x13) * 0x2c;
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 < '\x04') {
        fVar3 = *(float *)(param_1 + 0xd4) - FLOAT_8043c65c;
        *(float *)(param_1 + 0xd4) = fVar3;
        if (fVar3 < fVar2) {
          *(undefined1 *)(param_1 + 0x18) = 2;
          *(undefined1 *)(param_1 + 0x82) = 0;
          *(float *)(param_1 + 0x144) = fVar2;
        }
        else {
          fVar3 = *(float *)(param_1 + 0x144) - FLOAT_8043c670;
          *(float *)(param_1 + 0x144) = fVar3;
          if (fVar3 < fVar2) {
            *(float *)(param_1 + 0x144) = fVar2;
          }
        }
        zz_0007cac_((double)*(float *)(param_1 + 0x144),*(int *)(param_1 + 0xe4));
      }
      goto LAB_801f3dfc;
    }
    if (cVar1 == '\0') {
      bVar10 = FLOAT_8043c650 < *(float *)(param_1 + 0xd8);
      *(float *)(param_1 + 0xd8) = *(float *)(param_1 + 0xd8) - FLOAT_8043c65c;
      if (bVar10) {
        return;
      }
      FUN_801fe424(iVar8,*(char *)(param_1 + 0x13) + '\b',(undefined4 *)(param_1 + 0x70));
      *(float *)(param_1 + 0xd8) = FLOAT_8043c658;
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    }
    else if (cVar1 < '\0') goto LAB_801f3dfc;
    fVar2 = FLOAT_8043c650;
    *(float *)(param_1 + 0xd8) = *(float *)(param_1 + 0xd8) - *(float *)(iVar8 + 0x1dc8);
    if (fVar2 < *(float *)(param_1 + 0xd8)) {
      return;
    }
    *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
  fVar3 = FLOAT_8043c65c;
  fVar2 = *(float *)(param_1 + 0xd4) - FLOAT_8043c65c;
  bVar10 = fVar2 <= FLOAT_8043c650;
  *(float *)(param_1 + 0xd4) = fVar2;
  fVar4 = FLOAT_8043c660;
  fVar2 = FLOAT_8043c654;
  if (bVar10) {
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(&DAT_803a2348 + iVar6);
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(&DAT_803a234c + iVar6);
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(&DAT_803a2350 + iVar6);
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(float *)(param_1 + 0xd4) = fVar4;
    *(float *)(param_1 + 0x144) = fVar3;
    zz_0007cac_((double)*(float *)(param_1 + 0x144),*(int *)(param_1 + 0xe4));
    local_68 = FLOAT_8043c650;
    local_64 = FLOAT_8043c650;
    local_60 = FLOAT_8043c664;
    local_5c = FLOAT_8043c650;
    local_58 = FLOAT_8043c650;
    local_54 = FLOAT_8043c668;
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),&local_5c,&local_5c);
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),&local_68,&local_68);
    FUN_801f405c(&local_5c,&local_5c,&local_68);
    iVar5 = zz_003e6e4_(&local_5c,&local_68,afStack_50);
    if (0 < iVar5) {
      zz_0085e00_(param_1,afStack_50,0x1a);
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(&DAT_803a2348 + iVar6);
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(&DAT_803a234c + iVar6);
    *(float *)(param_1 + 0x60) =
         *(float *)(param_1 + 0x60) + *(float *)(&DAT_803a2348 + iVar6) / fVar2;
  }
  if (*(char *)(param_1 + 0x168) == '\0') {
    *(undefined1 *)(param_1 + 0x168) = 1;
    FUN_80047aa4(param_1);
    zz_00aedc0_(iVar8,(float *)(param_1 + 0x114),1,*(undefined1 *)(param_1 + 0x88));
    zz_00f061c_((double)FLOAT_8043c66c,iVar8,0x110);
  }
LAB_801f3dfc:
  if (*(char *)(param_1 + 0x18) < '\x02') {
    FUN_801f3f38(param_1,afStack_44);
    fVar2 = FLOAT_8043c650;
    pfVar9 = (float *)(param_1 + 0x150);
    *(float *)(param_1 + 0x150) = FLOAT_8043c650;
    *(float *)(param_1 + 0x154) = fVar2;
    *(float *)(param_1 + 0x158) = fVar2;
    gnt4_PSMTXMultVec_bl(afStack_44,pfVar9,pfVar9);
    fVar3 = FLOAT_8043c668;
    fVar2 = FLOAT_8043c650;
    pfVar7 = (float *)(param_1 + 0x15c);
    *(float *)(param_1 + 0x15c) = FLOAT_8043c650;
    *(float *)(param_1 + 0x160) = fVar2;
    *(float *)(param_1 + 0x164) = fVar2;
    *(float *)(param_1 + 0x164) = fVar3 * *(float *)(param_1 + 0x60);
    gnt4_PSMTXMultVec_bl(afStack_44,pfVar7,pfVar7);
    zz_0139a6c_(param_1,pfVar9,pfVar7,(char)*(undefined4 *)(&DAT_803a2354 + iVar6));
  }
  return;
}



// ==== 801f3ea4  FUN_801f3ea4 ====

void FUN_801f3ea4(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801f3ebc  FUN_801f3ebc ====

void FUN_801f3ebc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801f3edc  FUN_801f3edc ====

void FUN_801f3edc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (*(char *)(param_9 + 0x19) < '\x02') {
    iVar1 = *(int *)(param_9 + 0xe0);
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,0x44);
  return;
}



// ==== 801f3f38  FUN_801f3f38 ====

/* WARNING: Removing unreachable block (ram,0x801f400c) */
/* WARNING: Removing unreachable block (ram,0x801f3fdc) */
/* WARNING: Removing unreachable block (ram,0x801f3fac) */

void FUN_801f3f38(int param_1,float *param_2)

{
  byte bVar1;
  float local_88;
  undefined4 local_84;
  undefined4 local_80;
  float afStack_7c [3];
  float local_70;
  undefined4 local_60;
  undefined4 local_50;
  float afStack_4c [16];
  
  bVar1 = *(byte *)(param_1 + 0x84);
  gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
                    afStack_7c);
  gnt4_PSMTXMultVec_bl(afStack_7c,(float *)(param_1 + 100),&local_88);
  local_70 = local_88;
  local_60 = local_84;
  local_50 = local_80;
  if ((bVar1 & 8) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c674 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                               0x3ff0000000000000)),afStack_4c,0x7a);
    gnt4_PSMTXConcat_bl(afStack_7c,afStack_4c,afStack_7c);
  }
  if ((bVar1 & 4) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c674 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                               0x3ff0000000000000)),afStack_4c,0x79);
    gnt4_PSMTXConcat_bl(afStack_7c,afStack_4c,afStack_7c);
  }
  if ((bVar1 & 2) != 0) {
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043c674 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                               0x3ff0000000000000)),afStack_4c,0x78);
    gnt4_PSMTXConcat_bl(afStack_7c,afStack_4c,afStack_7c);
  }
  gnt4_PSMTXCopy_bl(afStack_7c,param_2);
  return;
}



// ==== 801f405c  FUN_801f405c ====

void FUN_801f405c(float *param_1,float *param_2,float *param_3)

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



// ==== 801f4260  zz_01f4260_ ====

void zz_01f4260_(int param_1,int param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,1,*(int *)(&DAT_80435bd8 + param_2 * 8));
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 99;
    puVar1[0x11] = (char)param_2;
    puVar1[0x13] = (char)*(undefined4 *)(&DAT_80435bd8 + param_2 * 8);
    *(code **)(puVar1 + 0xc) = FUN_801f4380;
    *(code **)(puVar1 + 0x10c) = FUN_801f4770;
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
    *(undefined4 *)(puVar1 + 0x54) = 0;
  }
  return;
}



// ==== 801f4380  FUN_801f4380 ====

void FUN_801f4380(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(char *)(param_1 + 0x18) < '\x02') {
    if (*(char *)(iVar1 + 0x18) < '\x02') {
      if ((*(short *)(iVar1 + 1000) == *(short *)(param_1 + 0x94)) &&
         ((*(uint *)(iVar1 + 0x5e0) & 0x1000000) == 0)) goto LAB_801f43e8;
    }
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
LAB_801f43e8:
  (*(code *)(&PTR_FUN_803a2550)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801f4418  FUN_801f4418 ====

void FUN_801f4418(int param_1)

{
  int iVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar5;
  double dVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  iVar1 = zz_008ac80_(param_1,0x18);
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    piVar2 = zz_0006dc8_(*(char *)(param_1 + 0x13) * 0x28);
    *(int **)(param_1 + 0xdc) = piVar2;
    if (piVar2 != (int *)0x0) {
      *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(*(int *)(param_1 + 0xdc) + 0xc);
    }
    if (*(int *)(param_1 + 0x54) == 0) {
      *(undefined1 *)(param_1 + 0x18) = 2;
    }
    else {
      iVar1 = *(int *)(param_1 + 0x8c);
      *(undefined1 *)(param_1 + 0x18) = 1;
      *(undefined2 *)(param_1 + 0x1e) = 0;
      *(undefined2 *)(param_1 + 0x1c) = 0;
      gnt4_PSMTXCopy_bl((float *)(iVar1 + 0x114),(float *)(param_1 + 0x114));
      dVar6 = FUN_8003d6e4((double)*(float *)(iVar1 + 0x668),iVar1,(float *)(iVar1 + 0x20));
      dVar8 = (double)FLOAT_8043c678;
      dVar9 = (double)*(float *)(iVar1 + 0x24);
      dVar5 = -(double)(float)(dVar8 * (double)*(float *)(iVar1 + 0x668) - dVar9);
      if (dVar6 < dVar5) {
        dVar6 = dVar5;
      }
      if (dVar9 < dVar6) {
        dVar6 = dVar9;
      }
      *(float *)(param_1 + 0x130) = (float)dVar6;
      gnt4_PSMTXCopy_bl((float *)(param_1 + 0x114),(float *)(param_1 + 0x144));
      *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
      *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
      *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
      uVar4 = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x2c) = uVar4;
      *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x24);
      uVar3 = *(undefined4 *)(param_1 + 0x28);
      *(undefined4 *)(param_1 + 0x34) = uVar3;
      *(code **)(param_1 + 0x100) = FUN_801f46bc;
      uVar7 = zz_0089100_(param_1,1,1);
      zz_01f47f4_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,param_1,
                  (int)(&DAT_80435bd8 + *(char *)(param_1 + 0x11) * 8),0,uVar3,uVar4,in_r8,in_r9,
                  in_r10);
      *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + '1';
    }
  }
  return;
}



// ==== 801f4590  FUN_801f4590 ====

void FUN_801f4590(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  short sVar2;
  undefined8 uVar3;
  
  uVar3 = zz_00f0104_(*(int *)(param_9 + 0x90),0x16,2);
  iVar1 = zz_01f48f0_(param_9);
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    sVar2 = *(short *)(param_9 + 0x1c) + 1;
    *(short *)(param_9 + 0x1c) = sVar2;
    if (sVar2 == 0x46) {
      zz_01f47f4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                  (int)(&DAT_80435bd8 + *(char *)(param_9 + 0x11) * 8),1,param_12,param_13,param_14,
                  param_15,param_16);
      zz_008aff0_(param_9);
    }
  }
  *(float *)(param_9 + 0xc0) =
       *(float *)(*(int *)(param_9 + 0x54) + 0x10) * *(float *)(param_9 + 0xb4);
  return;
}



// ==== 801f4638  FUN_801f4638 ====

void FUN_801f4638(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801f4674  FUN_801f4674 ====

void FUN_801f4674(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801f46bc  FUN_801f46bc ====

void FUN_801f46bc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

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
  int iVar7;
  undefined8 uVar8;
  float afStack_48 [13];
  
  iVar5 = 0;
  iVar7 = 0;
  iVar6 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar5) break;
    if (((int)*(short *)(param_9 + 0x1e) & 1 << iVar5) != 0) {
      iVar4 = *(int *)(param_9 + 0x54) + iVar7;
      sVar1 = *(short *)(iVar4 + 0x24);
      iVar3 = (int)sVar1;
      zz_00457d4_('y',(float *)(param_9 + 0x144),afStack_48,sVar1);
      pfVar2 = (float *)(iVar4 + 0x10);
      uVar8 = zz_00456a0_(afStack_48,afStack_48,pfVar2);
      zz_00076d0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar6 + 0xe0),afStack_48,(undefined *)pfVar2,iVar3,in_r7,in_r8,in_r9,
                  in_r10);
      if (iVar5 == 0) {
        gnt4_PSMTXCopy_bl(afStack_48,(float *)(param_9 + 0x114));
      }
    }
    iVar7 = iVar7 + 0x28;
    iVar6 = iVar6 + 4;
    iVar5 = iVar5 + 1;
  }
  return;
}



// ==== 801f4770  FUN_801f4770 ====

void FUN_801f4770(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar1) break;
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar1) != 0) {
      zz_00097b4_(*(int *)(iVar2 + 0xe0),0x44);
    }
    iVar2 = iVar2 + 4;
    iVar1 = iVar1 + 1;
  }
  return;
}



// ==== 801f47f4  zz_01f47f4_ ====

void zz_01f47f4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,int param_11,
                undefined4 param_12,undefined4 param_13,undefined4 param_14,undefined4 param_15,
                undefined4 param_16)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  short *psVar4;
  int *piVar5;
  int iVar6;
  undefined8 uVar7;
  
  iVar6 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar6) break;
    uVar3 = 1 << iVar6;
    if (((int)(short)*(ushort *)(param_9 + 0x1e) & uVar3) == 0) {
      iVar1 = *(int *)(param_10 + 4);
      piVar5 = (int *)(*(int *)(param_9 + 0x54) + iVar6 * 0x28);
      *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | (ushort)uVar3;
      uVar2 = 0;
      *(undefined2 *)(piVar5 + 8) = 0;
      psVar4 = (short *)(iVar1 + param_11 * 0xc);
      *(short *)((int)piVar5 + 0x22) = psVar4[1];
      *(undefined2 *)(piVar5 + 9) = 0;
      *(ushort *)((int)piVar5 + 0x26) =
           ~((short)((ushort)((uint)-param_11 >> 0x10) | (ushort)((uint)param_11 >> 0x10)) >> 0xf) &
           0xccc;
      zz_0018f88_(piVar5,*(int *)(psVar4 + 2),(float *)(piVar5 + 4));
      uVar7 = zz_0019338_(piVar5 + 2,*(int *)(psVar4 + 4),(float *)(piVar5 + 7));
      iVar1 = zz_0006f78_(*(int *)(param_9 + 0x90));
      iVar6 = iVar6 * 4 + 0xe0;
      zz_0006fb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                  *(int *)(param_9 + iVar6),(int)*psVar4,uVar2,uVar3,param_14,param_15,param_16);
      zz_0007cac_((double)(float)piVar5[7],*(int *)(param_9 + iVar6));
      iVar6 = (int)*(char *)(param_9 + 0x13);
    }
    iVar6 = iVar6 + 1;
  }
  return;
}



// ==== 801f48f0  zz_01f48f0_ ====

int zz_01f48f0_(int param_1)

{
  short sVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = 0;
  iVar5 = 0;
  iVar4 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar3) break;
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar3) != 0) {
      piVar2 = (int *)(*(int *)(param_1 + 0x54) + iVar5);
      sVar1 = *(short *)(piVar2 + 8);
      *(short *)(piVar2 + 8) = sVar1 + 1;
      if (*(short *)((int)piVar2 + 0x22) <= (short)(sVar1 + 1)) {
        *(ushort *)(param_1 + 0x1e) = *(ushort *)(param_1 + 0x1e) & ~(ushort)(1 << iVar3);
      }
      *(short *)(piVar2 + 9) = *(short *)(piVar2 + 9) - *(short *)((int)piVar2 + 0x26);
      zz_0018fd8_(piVar2,(int)*(short *)(piVar2 + 8),(float *)(piVar2 + 4));
      zz_0019370_(piVar2 + 2,(int)*(short *)(piVar2 + 8),(float *)(piVar2 + 7));
      zz_0007cac_((double)(float)piVar2[7],*(int *)(iVar4 + 0xe0));
    }
    iVar5 = iVar5 + 0x28;
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 1;
  }
  return (int)*(short *)(param_1 + 0x1e);
}



// ==== 801f49c8  zz_01f49c8_ ====

void zz_01f49c8_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = param_2;
    puVar1[0x10] = 0x62;
    *(code **)(puVar1 + 0xc) = FUN_801f4ac8;
    *(code **)(puVar1 + 0x10c) = FUN_801f5a84;
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



// ==== 801f4ac8  FUN_801f4ac8 ====

void FUN_801f4ac8(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  (*(code *)(&PTR_FUN_803a25e0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801f4b40  FUN_801f4b40 ====

void FUN_801f4b40(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  uVar6 = 0x803a0000;
  *(undefined1 *)(param_1 + 0x18) = 1;
  iVar8 = *(int *)(param_1 + 0x90);
  iVar7 = (int)*(char *)(param_1 + 0x11);
  *(undefined2 *)(iVar8 + 0x148) = 0x3c;
  iVar4 = iVar7 * 0x40;
  *(undefined1 *)(param_1 + 0x84) = 0x5f;
  *(code **)(param_1 + 0x100) = FUN_80047c38;
  iVar5 = iVar4;
  zz_0089100_(param_1,0,1);
  uVar2 = *(undefined4 *)(&DAT_803a2568 + iVar4);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_803a2564 + iVar4);
  *(undefined4 *)(param_1 + 0x68) = uVar2;
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_803a256c + iVar4);
  *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(&DAT_803a2594 + iVar4);
  *(char *)(param_1 + 0x89) = (char)*(undefined2 *)(&DAT_803a2562 + iVar4);
  *(undefined2 *)(param_1 + 0x1c4) = *(undefined2 *)(&DAT_803a2592 + iVar4);
  *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x1c4);
  *(undefined2 *)(param_1 + 0x1c8) = *(undefined2 *)(param_1 + 0x1c4);
  uVar3 = zz_00055fc_();
  fVar1 = FLOAT_8043c688;
  dVar12 = (double)(float)((double)CONCAT44(0x43300000,uVar3 & 0x1f) - DOUBLE_8043c690);
  *(float *)(param_1 + 0x150) =
       *(float *)(&DAT_803a2598 + iVar4) *
       ((FLOAT_8043c680 + (float)(dVar12 - (double)FLOAT_8043c684)) / FLOAT_8043c680);
  *(float *)(param_1 + 0x154) = fVar1 * *(float *)(param_1 + 0x150);
  uVar3 = zz_00055fc_();
  dVar11 = (double)FLOAT_8043c680;
  dVar10 = (double)(float)(dVar11 + (double)((float)((double)CONCAT44(0x43300000,uVar3 & 0x1f) -
                                                    DOUBLE_8043c690) - FLOAT_8043c684));
  dVar9 = (double)(float)(dVar10 / dVar11);
  *(short *)(param_1 + 0x158) =
       (short)(int)((double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(short *)(&DAT_803a259c + iVar4) ^
                                                     0x80000000) - DOUBLE_8043c698) * dVar9);
  *(undefined1 *)(param_1 + 0x15a) = 0;
  *(undefined1 *)(param_1 + 0x15b) = 0;
  iVar8 = zz_0006f98_(iVar8);
  zz_0006fb4_(dVar9,dVar10,dVar11,dVar12,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar8 + 0x600),
              *(int *)(param_1 + 0xe0),(int)*(short *)(&DAT_803a2560 + iVar4),iVar5,uVar6,iVar7,
              in_r9,in_r10);
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + '1';
  iVar4 = zz_008ac80_(param_1,(int)*(short *)(&DAT_803a2590 + iVar4));
  if (iVar4 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801f4d14  FUN_801f4d14 ====

void FUN_801f4d14(int param_1)

{
  (*(code *)(&PTR_FUN_803a25f0)[*(char *)(param_1 + 0x19)])(param_1,*(undefined4 *)(param_1 + 0x90))
  ;
  return;
}



// ==== 801f4d54  FUN_801f4d54 ====

void FUN_801f4d54(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  short sVar3;
  double dVar4;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      goto LAB_801f4e64;
    }
    if (cVar1 < '\0') {
      return;
    }
    if (*(char *)(param_2 + 0x14c) != '\x03') {
      return;
    }
    dVar4 = (double)FLOAT_8043c6a0;
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    *(undefined4 *)(param_1 + 0xd4) =
         *(undefined4 *)(&DAT_803a2588 + *(char *)(param_1 + 0x11) * 0x40);
    zz_00f061c_(dVar4,param_1,0x11c);
  }
  fVar2 = FLOAT_8043c6a4;
  *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - *(float *)(param_1 + 0x44);
  if (fVar2 < *(float *)(param_1 + 0xd4)) {
    *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + *(float *)(param_1 + 0x44);
    return;
  }
  *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  *(undefined2 *)(param_1 + 0x1c) = 0x3c;
  *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_2 + 0x72);
  *(byte *)(param_1 + 0x84) = *(byte *)(param_1 + 0x84) & 0xbe;
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x11c);
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 300);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x13c);
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
LAB_801f4e64:
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  sVar3 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar3;
  if (sVar3 < 1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined1 *)(param_1 + 0x1a) = 0;
  }
  return;
}



// ==== 801f4eb4  FUN_801f4eb4 ====

/* WARNING: Removing unreachable block (ram,0x801f532c) */
/* WARNING: Removing unreachable block (ram,0x801f4ec4) */

void FUN_801f4eb4(int param_1)

{
  char cVar1;
  char cVar2;
  float fVar3;
  short sVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  float local_74 [2];
  float local_6c;
  float local_68;
  float local_64;
  undefined4 local_60;
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  longlong local_48;
  undefined4 local_40;
  uint uStack_3c;
  longlong local_38;
  
  cVar1 = *(char *)(param_1 + 0x11);
  iVar7 = *(int *)(param_1 + 0xcc);
  iVar6 = *(int *)(param_1 + 200);
  if ((iVar7 == 0) || ('\x01' < *(char *)(iVar7 + 0x18))) {
    *(undefined1 *)(param_1 + 0x19) = 2;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    return;
  }
  if (iVar6 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    return;
  }
  if ((*(short *)(param_1 + 0x1c6) < 1) || (*(char *)(param_1 + 0x1d9) != '\0')) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    return;
  }
  local_68 = *(float *)(iVar6 + 100);
  local_64 = *(float *)(iVar6 + 0x68);
  local_60 = *(undefined4 *)(iVar6 + 0x6c);
  gnt4_PSVECSubtract_bl(&local_68,(float *)(param_1 + 0x20),local_74);
  iVar6 = FUN_800452a0((double)local_74[0],(double)local_6c);
  sVar4 = (short)iVar6 - *(short *)(param_1 + 0x72);
  gnt4_PSVECSquareMag_bl(local_74);
  dVar9 = (double)(local_74[0] * local_74[0] + local_6c * local_6c);
  if ((double)FLOAT_8043c6a4 < dVar9) {
    dVar8 = 1.0 / SQRT(dVar9);
    dVar8 = DOUBLE_8043c6a8 * dVar8 * -(dVar9 * dVar8 * dVar8 - DOUBLE_8043c6b0);
    dVar8 = DOUBLE_8043c6a8 * dVar8 * -(dVar9 * dVar8 * dVar8 - DOUBLE_8043c6b0);
    dVar9 = (double)(float)(dVar9 * DOUBLE_8043c6a8 * dVar8 *
                                    -(dVar9 * dVar8 * dVar8 - DOUBLE_8043c6b0));
  }
  cVar2 = *(char *)(param_1 + 0x1a);
  if (cVar2 == '\x02') {
    if (dVar9 <= (double)FLOAT_8043c6b8) {
      *(undefined1 *)(param_1 + 0x1a) = 3;
    }
    else {
      iVar6 = zz_01f5900_(param_1,*(short *)(param_1 + 0x158),sVar4);
      if (iVar6 == 0) {
        *(undefined1 *)(param_1 + 0x1a) = 4;
        fVar3 = FLOAT_8043c6a4;
        *(undefined2 *)(param_1 + 0x1c) = 0x3c;
        *(float *)(param_1 + 0x48) = fVar3;
      }
      else {
        *(float *)(param_1 + 0x48) =
             (local_64 - *(float *)(param_1 + 0x24)) /
             ((float)(dVar9 - (double)FLOAT_8043c6bc) / *(float *)(param_1 + 0x44));
      }
    }
  }
  else if (cVar2 < '\x02') {
    if (cVar2 == '\0') {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      fVar3 = FLOAT_8043c6a4;
      *(undefined2 *)(param_1 + 0x1c) = 0x78;
      *(float *)(param_1 + 0x48) = fVar3;
    }
    else if (cVar2 < '\0') goto LAB_801f519c;
    iVar5 = zz_01f5900_(param_1,*(short *)(param_1 + 0x158),sVar4);
    if (iVar5 != 0) {
      *(short *)(param_1 + 0x72) = (short)iVar6;
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    }
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    if (sVar4 < 1) {
      *(undefined1 *)(param_1 + 0x1a) = 4;
      *(undefined2 *)(param_1 + 0x1c) = 0x3c;
    }
  }
  else {
    if (cVar2 != '\x04') {
      if ('\x03' < cVar2) goto LAB_801f519c;
      zz_008296c_(param_1,0x7c);
      fVar3 = FLOAT_8043c688;
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 0x78;
      *(float *)(param_1 + 0x48) = fVar3 * *(float *)(param_1 + 0x44);
      *(char *)(param_1 + 0x15a) = *(char *)(param_1 + 0x15a) + '\x01';
    }
    sVar4 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar4;
    if (sVar4 < 1) {
      if ((int)*(char *)(param_1 + 0x15a) < (int)*(short *)(&DAT_803a259e + cVar1 * 0x40)) {
        *(undefined1 *)(param_1 + 0x1a) = 0;
      }
      else {
        *(undefined1 *)(param_1 + 0x19) = 2;
        *(undefined1 *)(param_1 + 0x1a) = 0;
      }
    }
  }
LAB_801f519c:
  if ((*(char *)(param_1 + 0x1b) == '\0') &&
     (*(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043c6c0,
     *(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x150))) {
    *(char *)(param_1 + 0x1b) = *(char *)(param_1 + 0x1b) + '\x01';
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x150);
  }
  dVar9 = zz_0045204_(*(short *)(param_1 + 0x72));
  *(float *)(param_1 + 0x20) =
       (float)((double)*(float *)(param_1 + 0x44) * dVar9 + (double)*(float *)(param_1 + 0x20));
  *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x48);
  dVar8 = zz_0045238_(*(short *)(param_1 + 0x72));
  dVar9 = (double)FLOAT_8043c6a4;
  *(float *)(param_1 + 0x28) =
       (float)((double)*(float *)(param_1 + 0x44) * dVar8 + (double)*(float *)(param_1 + 0x28));
  if (((double)*(float *)(param_1 + 0x48) < dVar9) &&
     (dVar9 = FUN_8003d964(-(double)*(float *)(param_1 + 0x48),param_1,(float *)(param_1 + 0x20)),
     fVar3 = FLOAT_8043c6a4, (double)*(float *)(param_1 + 0x24) < dVar9)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(float *)(param_1 + 0x24) = (float)dVar9;
    *(float *)(param_1 + 0x48) = fVar3;
  }
  iVar6 = zz_0083714_(param_1);
  if (iVar6 == 0) {
    iVar6 = FUN_800452a0(-(double)*(float *)(param_1 + 0x48),(double)*(float *)(param_1 + 0x44));
    fVar3 = FLOAT_8043c6cc;
    dVar9 = DOUBLE_8043c698;
    uStack_54 = (int)(short)iVar6 ^ 0x80000000;
    uStack_4c = (int)*(short *)(param_1 + 0x70) ^ 0x80000000;
    local_58 = 0x43300000;
    local_50 = 0x43300000;
    local_40 = 0x43300000;
    iVar6 = (int)(FLOAT_8043c6c4 * (float)((double)CONCAT44(0x43300000,uStack_4c) - DOUBLE_8043c698)
                 + FLOAT_8043c6c8 *
                   (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_8043c698));
    local_48 = (longlong)iVar6;
    *(short *)(param_1 + 0x70) = (short)iVar6;
    uStack_3c = (int)*(short *)(param_1 + 0x74) ^ 0x80000000;
    iVar6 = (int)((float)((double)CONCAT44(0x43300000,uStack_3c) - dVar9) * fVar3);
    local_38 = (longlong)iVar6;
    *(short *)(param_1 + 0x74) = (short)iVar6;
    if (*(char *)(iVar7 + 0x83) == '\0') {
      zz_006d228_(param_1,iVar7,0);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801f5348  FUN_801f5348 ====

void FUN_801f5348(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  int iVar3;
  short sVar5;
  int iVar4;
  double dVar6;
  float local_58;
  float local_54;
  float local_50;
  float fStack_4c;
  undefined4 local_48;
  double local_40;
  undefined8 local_38;
  undefined8 local_30;
  
  iVar4 = *(char *)(param_1 + 0x11) * 0x40;
  if (*(char *)(param_1 + 0x1a) < '\x03') {
    gnt4_PSMTXMultVec_bl
              ((float *)(param_2 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
               (float *)(iVar4 + -0x7fc5da90),&fStack_4c);
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(param_2 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
               (float *)(&DAT_803a257c + iVar4),&fStack_4c);
  }
  gnt4_PSVECSubtract_bl(&fStack_4c,(float *)(param_1 + 0x20),&local_58);
  iVar3 = FUN_800452a0((double)local_58,(double)local_50);
  fVar2 = FLOAT_8043c6a4;
  cVar1 = *(char *)(param_1 + 0x1a);
  sVar5 = (short)iVar3 - *(short *)(param_1 + 0x72);
  if (cVar1 == '\x02') {
    if (local_54 <= FLOAT_8043c6a4) {
      if (-*(float *)(param_1 + 0x154) <= local_54) {
        *(undefined4 *)(param_1 + 0x24) = local_48;
        *(float *)(param_1 + 0x48) = fVar2;
      }
      else {
        *(float *)(param_1 + 0x48) = -*(float *)(param_1 + 0x154);
      }
    }
    else if (local_54 <= *(float *)(param_1 + 0x154)) {
      *(undefined4 *)(param_1 + 0x24) = local_48;
      *(float *)(param_1 + 0x48) = fVar2;
    }
    else {
      *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x154);
    }
    dVar6 = zz_0045204_(*(short *)(param_1 + 0x72));
    *(float *)(param_1 + 0x20) =
         (float)((double)*(float *)(param_1 + 0x44) * dVar6 + (double)*(float *)(param_1 + 0x20));
    *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x48);
    dVar6 = zz_0045238_(*(short *)(param_1 + 0x72));
    *(float *)(param_1 + 0x28) =
         (float)((double)*(float *)(param_1 + 0x44) * dVar6 + (double)*(float *)(param_1 + 0x28));
    sVar5 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar5;
    if (sVar5 < 1) {
      *(undefined1 *)(param_1 + 0x1a) = 0;
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      *(undefined2 *)(param_1 + 0x1c) = 0x78;
    }
    else if (cVar1 < '\0') goto LAB_801f5848;
    zz_01f5900_(param_1,*(short *)(param_1 + 0x158),sVar5);
    fVar2 = FLOAT_8043c6a4;
    if (local_54 <= FLOAT_8043c6a4) {
      if (-*(float *)(param_1 + 0x154) <= local_54) {
        *(undefined4 *)(param_1 + 0x24) = local_48;
        *(float *)(param_1 + 0x48) = fVar2;
      }
      else {
        *(float *)(param_1 + 0x48) = -*(float *)(param_1 + 0x154);
      }
    }
    else if (local_54 <= *(float *)(param_1 + 0x154)) {
      *(undefined4 *)(param_1 + 0x24) = local_48;
      *(float *)(param_1 + 0x48) = fVar2;
    }
    else {
      *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x154);
    }
    dVar6 = zz_0045204_(*(short *)(param_1 + 0x72));
    *(float *)(param_1 + 0x20) =
         (float)((double)*(float *)(param_1 + 0x44) * dVar6 + (double)*(float *)(param_1 + 0x20));
    *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x48);
    dVar6 = zz_0045238_(*(short *)(param_1 + 0x72));
    *(float *)(param_1 + 0x28) =
         (float)((double)*(float *)(param_1 + 0x44) * dVar6 + (double)*(float *)(param_1 + 0x28));
    dVar6 = gnt4_PSVECSquareMag_bl(&local_58);
    if ((double)FLOAT_8043c6d0 < dVar6) {
      if ((((int)sVar5 - 0x4000U & 0x8000) == 0) &&
         (sVar5 = *(short *)(param_1 + 0x1c) + -1, *(short *)(param_1 + 0x1c) = sVar5, sVar5 < 1)) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(undefined2 *)(param_1 + 0x1c) = 0x3c;
      }
    }
    else {
      sVar5 = *(short *)(param_2 + 0x72) - *(short *)(param_1 + 0x72);
      if ((sVar5 < 0x3001) && (-0x3001 < sVar5)) {
        *(undefined1 *)(param_1 + 0x1a) = 3;
        *(undefined2 *)(param_1 + 0x1c) = 0x78;
        zz_0066408_(param_2,(int)*(char *)(param_1 + 0x89),(float *)(param_1 + 0x20),
                    (float *)(param_1 + 100));
        iVar4 = (int)((*(float *)(&DAT_803a2584 + iVar4) - *(float *)(&DAT_803a2578 + iVar4)) /
                     (*(float *)(param_1 + 0x28) - *(float *)(param_1 + 0x34)));
        local_40 = (double)(longlong)iVar4;
        sVar5 = (short)iVar4;
        if (sVar5 < 0) {
          sVar5 = -sVar5;
          local_30 = local_40;
        }
        *(short *)(param_1 + 0x1e) = sVar5;
        if (*(short *)(param_1 + 0x1e) < *(short *)(param_1 + 0x1c)) {
          *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1e);
        }
        *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) - *(short *)(param_2 + 0x72);
        *(byte *)(param_1 + 0x84) = *(byte *)(param_1 + 0x84) | 0x41;
        local_38 = local_40;
      }
      else {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(undefined2 *)(param_1 + 0x1c) = 0x3c;
      }
    }
  }
  else {
    if (cVar1 != '\x04') {
      if ('\x03' < cVar1) goto LAB_801f5848;
      *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * FLOAT_8043c6cc;
      sVar5 = -*(short *)(param_1 + 0x72);
      iVar3 = (int)sVar5;
      if (iVar3 < 0) {
        iVar3 = -iVar3;
      }
      if (iVar3 / (int)*(short *)(param_1 + 0x1c) < (int)*(short *)(&DAT_803a259c + iVar4)) {
        *(short *)(param_1 + 0x158) = *(short *)(&DAT_803a259c + iVar4);
      }
      else {
        *(short *)(param_1 + 0x158) = sVar5 / *(short *)(param_1 + 0x1c);
      }
      zz_01f5900_(param_1,*(short *)(param_1 + 0x158),sVar5);
      dVar6 = DOUBLE_8043c698;
      local_30 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c)) ^ 0x80000000);
      *(float *)(param_1 + 100) =
           *(float *)(param_1 + 100) +
           (*(float *)(&DAT_803a257c + iVar4) - *(float *)(param_1 + 100)) /
           (float)(local_30 - DOUBLE_8043c698);
      local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c)) ^ 0x80000000);
      *(float *)(param_1 + 0x68) =
           *(float *)(param_1 + 0x68) +
           (*(float *)(&DAT_803a2580 + iVar4) - *(float *)(param_1 + 0x68)) /
           (float)(local_38 - dVar6);
      local_40 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c)) ^ 0x80000000);
      *(float *)(param_1 + 0x44) =
           (*(float *)(&DAT_803a2584 + iVar4) - *(float *)(param_1 + 0x6c)) /
           (float)(local_40 - dVar6);
      *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + *(float *)(param_1 + 0x44);
      sVar5 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar5;
      if (0 < sVar5) goto LAB_801f5848;
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(&DAT_803a258c + iVar4);
    }
    fVar2 = FLOAT_8043c6a4;
    *(undefined2 *)(param_2 + 0x14a) = 0x1e;
    *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - *(float *)(param_1 + 0x44);
    if (*(float *)(param_1 + 0xd4) <= fVar2) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x15b) = 1;
    }
    else {
      *(float *)(param_1 + 0x6c) = *(float *)(param_1 + 0x6c) + *(float *)(param_1 + 0x44);
    }
  }
LAB_801f5848:
  iVar4 = FUN_800452a0(-(double)*(float *)(param_1 + 0x48),(double)*(float *)(param_1 + 0x44));
  fVar2 = FLOAT_8043c6cc;
  dVar6 = DOUBLE_8043c698;
  local_30 = (double)CONCAT44(0x43300000,(int)(short)iVar4 ^ 0x80000000);
  local_38 = (double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x70) ^ 0x80000000);
  *(short *)(param_1 + 0x70) =
       (short)(int)(FLOAT_8043c6c4 * (float)(local_38 - DOUBLE_8043c698) +
                   FLOAT_8043c6c8 * (float)(local_30 - DOUBLE_8043c698));
  *(short *)(param_1 + 0x74) =
       (short)(int)((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x74) ^ 0x80000000
                                            ) - dVar6) * fVar2);
  return;
}



// ==== 801f5900  zz_01f5900_ ====

undefined4 zz_01f5900_(int param_1,short param_2,short param_3)

{
  double dVar1;
  undefined4 uVar2;
  undefined8 local_18;
  undefined8 local_10;
  
  dVar1 = DOUBLE_8043c698;
  uVar2 = 0;
  if (param_3 < 0) {
    if ((int)param_3 < -(int)param_2) {
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) - param_2;
      local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x74)) ^ 0x80000000);
      *(short *)(param_1 + 0x74) =
           (short)(int)(FLOAT_8043c6c4 * (float)(local_10 - dVar1) + FLOAT_8043c6d8);
    }
    else {
      uVar2 = 1;
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + param_3;
    }
  }
  else if (param_2 < param_3) {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + param_2;
    local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x74)) ^ 0x80000000);
    *(short *)(param_1 + 0x74) =
         (short)(int)(FLOAT_8043c6c4 * (float)(local_18 - dVar1) + FLOAT_8043c6d4);
  }
  else {
    uVar2 = 1;
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + param_3;
  }
  return uVar2;
}



// ==== 801f59fc  FUN_801f59fc ====

void FUN_801f59fc(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_006de10_(*(int *)(param_1 + 0x90),2);
  if (*(char *)(param_1 + 0x15b) == '\0') {
    FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
  }
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_008aff0_(param_1);
  return;
}



// ==== 801f5a64  FUN_801f5a64 ====

void FUN_801f5a64(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801f5a84  FUN_801f5a84 ====

void FUN_801f5a84(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801f5ae0  zz_01f5ae0_ ====

void zz_01f5ae0_(undefined1 param_1)

{
  DAT_804363b0 = PTR_DAT_80433934 + 0x1838;
  gnt4_memset(DAT_804363b0,0,0x10);
  DAT_804363b0[9] = param_1;
  DAT_804363b0[0xb] = PTR_DAT_80433930[2];
  DAT_804363b0[0xc] = PTR_DAT_80433930[3];
  DAT_804363b0[0xd] = PTR_DAT_80433934[0xc0];
  DAT_804363b0[0xe] = PTR_DAT_80433934[0xc1];
  return;
}



// ==== 801f5b68  zz_01f5b68_ ====

int zz_01f5b68_(void)

{
  (*(code *)(&PTR_FUN_803a2600)[*DAT_804363b0])();
  if (DAT_804363b0[10] == '\0') {
    zz_01f5fb0_();
    zz_008c104_(FUN_80089f28);
  }
  return (int)DAT_804363b0[10];
}



// ==== 801f5bd4  FUN_801f5bd4 ====

void FUN_801f5bd4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  char *pcVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  
  cVar1 = DAT_804363b0[1];
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      iVar3 = zz_0027adc_();
      pcVar2 = DAT_804363b0;
      if (iVar3 != 0) {
        return;
      }
      iVar3 = 0x16;
      *DAT_804363b0 = *DAT_804363b0 + '\x01';
      DAT_804363b0[1] = '\0';
      DAT_804363b0[2] = '\0';
      DAT_804363b0[3] = '\0';
      if (DAT_804363b0[9] == '\x03') {
        iVar3 = 0x14;
      }
      zz_00e99c8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,
                  *(int *)(&DAT_8031a074 + iVar3 * 4),iVar3,pcVar2,in_r8,in_r9,in_r10);
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    DAT_804363b0[1] = cVar1 + '\x01';
    uVar5 = 0;
    zz_002a5f4_(0,0,0,0);
    zz_0197854_(1);
    uVar4 = 0;
    zz_0088398_(DAT_80436238 + 0xfe800,0xe0000,0);
    uVar6 = zz_00f0a60_();
    uVar6 = zz_0044848_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        DAT_804363b0[9] + 0x14);
    zz_00439a0_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,5);
    uVar6 = zz_007fd5c_();
    zz_007fd6c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_01f6024_,0,uVar4,
                uVar5,in_r7,in_r8,in_r9,in_r10);
  }
  iVar3 = zz_000a3c4_();
  if ((iVar3 == 0) && (iVar3 = zz_01f60d0_(DAT_804363b0,0), iVar3 != 0)) {
    DAT_804363b0[1] = DAT_804363b0[1] + '\x01';
    zz_0027aac_(0,0x20,0);
    zz_008c3a0_(10);
    if (DAT_804363b0[0xc] < '\x02') {
      PTR_DAT_80433930[0x29] = 0;
    }
    else {
      PTR_DAT_80433930[0x29] = 1;
    }
  }
  return;
}



// ==== 801f5d7c  FUN_801f5d7c ====

void FUN_801f5d7c(void)

{
  (**(code **)(&DAT_80435be0 + *(char *)(DAT_804363b0 + 1) * 4))();
  return;
}



// ==== 801f5db8  FUN_801f5db8 ====

void FUN_801f5db8(void)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(DAT_804363b0 + 2);
  if (cVar1 == '\x01') {
    sVar2 = *(short *)(DAT_804363b0 + 4) + -1;
    *(short *)(DAT_804363b0 + 4) = sVar2;
    if (0 < sVar2) {
      return;
    }
    *(char *)(DAT_804363b0 + 2) = *(char *)(DAT_804363b0 + 2) + '\x01';
    *(undefined1 *)(DAT_804363b0 + 8) = 1;
    *(undefined2 *)(DAT_804363b0 + 4) = 0x3c;
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') {
        return;
      }
      *(char *)(DAT_804363b0 + 2) = cVar1 + '\x01';
      *(undefined1 *)(DAT_804363b0 + 8) = 0;
      *(undefined2 *)(DAT_804363b0 + 4) = 0x3c;
      zz_01f60d0_(0,1);
      return;
    }
    if ('\x02' < cVar1) {
      return;
    }
  }
  sVar2 = *(short *)(DAT_804363b0 + 4) + -1;
  *(short *)(DAT_804363b0 + 4) = sVar2;
  if (sVar2 < 1) {
    *(char *)(DAT_804363b0 + 1) = *(char *)(DAT_804363b0 + 1) + '\x01';
    *(undefined1 *)(DAT_804363b0 + 2) = 0;
  }
  return;
}



// ==== 801f5ea4  FUN_801f5ea4 ====

void FUN_801f5ea4(void)

{
  int iVar1;
  
  iVar1 = zz_01f6088_();
  if (1 < iVar1) {
    *DAT_804363b0 = *DAT_804363b0 + '\x01';
    DAT_804363b0[1] = '\0';
    DAT_804363b0[2] = '\0';
    DAT_804363b0[3] = '\0';
  }
  return;
}



// ==== 801f5ef8  FUN_801f5ef8 ====

void FUN_801f5ef8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  undefined8 extraout_f1;
  undefined8 uVar3;
  
  cVar1 = *(char *)(DAT_804363b0 + 1);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(DAT_804363b0 + 1) = cVar1 + '\x01';
    zz_0027aac_(0,0x20,1);
    param_11 = 2;
    zz_00e9b60_((double)FLOAT_8043c6e0,2,0x20,2);
  }
  iVar2 = zz_0027adc_();
  if (iVar2 == 0) {
    *(undefined1 *)(DAT_804363b0 + 10) = 1;
    uVar3 = zz_01f6098_(3);
    zz_01f6024_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,param_11,param_12,param_13,param_14,
                param_15,param_16);
    uVar3 = zz_007fd5c_();
    zz_0009e08_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    PTR_DAT_80433930[0x29] = 0;
    *PTR_DAT_80433930 = 1;
    PTR_DAT_80433930[1] = 0;
  }
  return;
}



// ==== 801f5fb0  zz_01f5fb0_ ====

void zz_01f5fb0_(void)

{
  zz_01f5fd4_();
  zz_01f5ffc_();
  return;
}



// ==== 801f5fd4  zz_01f5fd4_ ====

void zz_01f5fd4_(void)

{
  zz_0089898_(0x38);
  zz_0089658_();
  return;
}



// ==== 801f5ffc  zz_01f5ffc_ ====

void zz_01f5ffc_(void)

{
  zz_008a16c_();
  zz_0089c00_(0x38);
  return;
}



// ==== 801f6024  zz_01f6024_ ====

void zz_01f6024_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined8 uVar1;
  
  zz_00448dc_(*(char *)(DAT_804363b0 + 9) + 0x14);
  zz_0043a24_(5);
  zz_01978d0_();
  uVar1 = zz_00f0a60_();
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,extraout_r4,
                      param_11,param_12,param_13,param_14,param_15,param_16);
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,extraout_r4_00
                      ,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,extraout_r4_01,
              param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00f07c4_();
  zz_008c3a0_(0);
  return;
}



// ==== 801f6088  zz_01f6088_ ====

int zz_01f6088_(void)

{
  return (int)*(char *)(DAT_804363b0 + 8);
}



// ==== 801f6098  zz_01f6098_ ====

void zz_01f6098_(undefined1 param_1)

{
  *(undefined1 *)(DAT_804363b0 + 8) = param_1;
  return;
}



// ==== 801f60a4  zz_01f60a4_ ====

void zz_01f60a4_(undefined1 *param_1,undefined1 *param_2)

{
  if (param_1 != (undefined1 *)0x0) {
    *param_1 = *(undefined1 *)(DAT_804363b0 + 0xd);
  }
  if (param_2 == (undefined1 *)0x0) {
    return;
  }
  *param_2 = *(undefined1 *)(DAT_804363b0 + 0xe);
  return;
}



// ==== 801f60d0  zz_01f60d0_ ====

int zz_01f60d0_(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  
  iVar2 = 0;
  for (pcVar3 = (&PTR_DAT_803a2694)[param_2]; -1 < *pcVar3; pcVar3 = pcVar3 + 4) {
    iVar1 = zz_01f614c_(param_1,pcVar3);
    if (iVar1 != 0) {
      iVar2 = iVar2 + 1;
    }
  }
  return iVar2;
}



// ==== 801f614c  zz_01f614c_ ====

void zz_01f614c_(undefined4 param_1,undefined1 *param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x38,(int)(char)param_2[3],(int)(char)param_2[2]);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x11] = *param_2;
    puVar1[0x12] = param_2[1];
    *(code **)(puVar1 + 0xc) = FUN_801f61f8;
    *(undefined4 *)(puVar1 + 0x8c) = param_1;
    *(undefined **)(puVar1 + 0x10c) = (&PTR_FUN_803a2610)[(char)puVar1[0x11]];
    *(undefined4 *)(puVar1 + 0xcc) = DAT_803bb38c;
  }
  return;
}



// ==== 801f61f8  FUN_801f61f8 ====

void FUN_801f61f8(int param_1)

{
  (*(code *)(&PTR_FUN_803a270c)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801f6234  FUN_801f6234 ====

void FUN_801f6234(int param_1)

{
  (*(code *)(&PTR_FUN_803a271c)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801f6270  FUN_801f6270 ====

void FUN_801f6270(int param_1)

{
  (*(code *)(&PTR_FUN_803a2740)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801f62c0  FUN_801f62c0 ====

void FUN_801f62c0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801f62e0  FUN_801f62e0 ====

void FUN_801f62e0(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x99) <= iVar1) break;
    if (*(char *)(*(int *)(iVar2 + 0xe0) + 0x10) != '\0') {
      zz_0009958_(*(int *)(iVar2 + 0xe0),1);
    }
    iVar2 = iVar2 + 4;
    iVar1 = iVar1 + 1;
  }
  return;
}



// ==== 801f6354  FUN_801f6354 ====

void FUN_801f6354(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  float *pfVar1;
  undefined8 uVar2;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  uVar2 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xcc),*(int *)(param_9 + 0xe0),0,param_12,param_13,param_14
                      ,param_15,param_16);
  pfVar1 = (float *)0x1;
  zz_0006fb4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xcc)
              ,*(int *)(param_9 + 0xe4),1,param_12,param_13,param_14,param_15,param_16);
  *(float *)(param_9 + 0xd4) = FLOAT_8043c6e8;
  uVar2 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,*(int *)(param_9 + 0xcc),*(int *)(param_9 + 0xe4),pfVar1,
                      param_12,param_13,param_14,param_15,param_16);
  zz_0007c30_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,pfVar1,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(*(int *)(param_9 + 0xe4) + 0x10) = 0;
  zz_01f60a4_((undefined1 *)(param_9 + 0x146),(undefined1 *)(param_9 + 0x147));
  *(undefined1 *)(param_9 + 0x145) = 0;
  if (-1 < *(char *)(param_9 + 0x146)) {
    *(char *)(param_9 + 0x145) = *(char *)(param_9 + 0x145) + '\x01';
  }
  if (-1 < *(char *)(param_9 + 0x147)) {
    *(char *)(param_9 + 0x145) = *(char *)(param_9 + 0x145) + '\x01';
  }
  *(undefined1 *)(param_9 + 0x82) = 0x13;
  return;
}



// ==== 801f641c  FUN_801f641c ====

void FUN_801f641c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined8 uVar4;
  double dVar5;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      if ('\0' < *(char *)(param_9 + 0x144)) {
        return;
      }
      zz_01f6098_(2);
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    iVar3 = zz_01f6088_();
    if (iVar3 < 1) {
      return;
    }
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined1 *)(*(int *)(param_9 + 0xe4) + 0x10) = 1;
  }
  fVar2 = FLOAT_8043c6f0;
  dVar5 = (double)*(float *)(param_9 + 0xd4);
  *(float *)(param_9 + 0xd4) = (float)(dVar5 + (double)FLOAT_8043c6ec);
  if (fVar2 <= *(float *)(param_9 + 0xd4)) {
    iVar3 = zz_01f60d0_(param_9,2);
    *(char *)(param_9 + 0x144) = (char)iVar3;
    fVar2 = FLOAT_8043c6f0;
    if ((char)iVar3 != '\0') {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      *(float *)(param_9 + 0xd4) = fVar2;
      *(undefined1 *)(*(int *)(param_9 + 0xe0) + 0x10) = 0;
    }
  }
  uVar4 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),dVar5,param_3,param_4,param_5,param_6,
                      param_7,param_8,*(int *)(param_9 + 0xcc),*(int *)(param_9 + 0xe4),param_11,
                      param_12,param_13,param_14,param_15,param_16);
  zz_0007c30_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4),
              extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801f6520  FUN_801f6520 ====

void FUN_801f6520(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  float *pfVar1;
  undefined8 uVar2;
  
  pfVar1 = (float *)0x14;
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined2 *)(param_9 + 0x1c) = 0x3c;
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xcc),*(int *)(param_9 + 0xe0),0x14,param_12,param_13,param_14,
              param_15,param_16);
  uVar2 = zz_0008744_((double)FLOAT_8043c6e8,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                      ,*(int *)(param_9 + 0xcc),*(int *)(param_9 + 0xe0),pfVar1,param_12,param_13,
                      param_14,param_15,param_16);
  zz_0007c30_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,pfVar1,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 0x15;
  return;
}



// ==== 801f6588  FUN_801f6588 ====

void FUN_801f6588(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  short sVar3;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_9 + 0x19) = 3;
    if (PTR_DAT_80433930[0x29] != '\0') {
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xcc),*(int *)(param_9 + 0xe0),0xf,param_12,param_13,param_14,
                  param_15,param_16);
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      zz_0007c30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xe0),param_10,param_11,param_12,param_13,param_14,param_15,
                  param_16);
      sVar3 = *(short *)(param_9 + 0x1c) + -1;
      *(short *)(param_9 + 0x1c) = sVar3;
      fVar2 = FLOAT_8043c6f0;
      if (0 < sVar3) {
        return;
      }
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      *(float *)(param_9 + 0xd4) = fVar2;
    }
    else if (cVar1 < '\0') {
      return;
    }
    fVar2 = FLOAT_8043c6e8;
    *(float *)(param_9 + 0xd4) = *(float *)(param_9 + 0xd4) - FLOAT_8043c6ec;
    if (*(float *)(param_9 + 0xd4) < fVar2) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      *(float *)(param_9 + 0xd4) = fVar2;
    }
    zz_0007cac_((double)*(float *)(param_9 + 0xd4),*(int *)(param_9 + 0xe0));
  }
  return;
}



// ==== 801f6670  FUN_801f6670 ====

void FUN_801f6670(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  char *pcVar4;
  
  fVar2 = FLOAT_8043c6f0;
  *(float *)(param_1 + 0x60) = FLOAT_8043c6f0;
  pcVar4 = (char *)(*(int *)(param_1 + 0x8c) + 0x144);
  *(float *)(param_1 + 0x58) = fVar2;
  if (*(char *)(*(int *)(param_1 + 0x8c) + 0x145) == '\x01') {
    *(float *)(param_1 + 0x5c) = fVar2;
  }
  else {
    *(float *)(param_1 + 0x5c) = FLOAT_8043c6f4;
  }
  cVar1 = pcVar4[*(char *)(param_1 + 0x12) + 2];
  *(char *)(param_1 + 0x96) = cVar1;
  fVar2 = FLOAT_8043c6e8;
  if (cVar1 < '\0') {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *pcVar4 = *pcVar4 + -1;
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 1;
    *(undefined1 *)(param_1 + 0x88) = *(undefined1 *)(param_1 + 0x12);
    *(float *)(param_1 + 100) = fVar2;
    *(float *)(param_1 + 0x6c) = fVar2;
    fVar3 = FLOAT_8043c6f8;
    if (PTR_DAT_80433930[0x29] == '\0') {
      *(float *)(param_1 + 0x148) = fVar2;
      *(float *)(param_1 + 0x68) = fVar2;
    }
    else {
      *(float *)(param_1 + 0x148) = FLOAT_8043c6f8;
      *(float *)(param_1 + 0x68) = fVar3;
    }
    *(undefined1 *)(param_1 + 0x84) = 0x11;
    *(code **)(param_1 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_1,0x20,1);
  }
  return;
}



// ==== 801f6754  FUN_801f6754 ====

void FUN_801f6754(int param_1)

{
  (*(code *)(&PTR_FUN_803a2764)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 801f6790  FUN_801f6790 ====

void FUN_801f6790(int param_1)

{
  int iVar1;
  
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  iVar1 = zz_01f60d0_(param_1,3);
  *(char *)(param_1 + 0x150) = (char)iVar1;
  return;
}



// ==== 801f67d0  FUN_801f67d0 ====

void FUN_801f67d0(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x150) == '\0') {
    iVar1 = zz_01f60d0_(param_1,7);
    *(char *)(param_1 + 0x150) = (char)iVar1;
    if ((char)iVar1 != '\0') {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    }
  }
  return;
}



// ==== 801f6824  FUN_801f6824 ====

void FUN_801f6824(int param_1)

{
  int iVar1;
  uint uVar2;
  
  if (*(char *)(param_1 + 0x150) == '\0') {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x148);
    if (PTR_DAT_80433930[0x29] == '\0') {
      uVar2 = 0;
      if (7 < *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x96) * 4 + 0x1810)) {
        iVar1 = *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x96) * 4 + 0x1810) + -1;
        iVar1 = iVar1 / 7 + (iVar1 >> 0x1f);
        uVar2 = (iVar1 - (iVar1 >> 0x1f)) - 1;
        *(float *)(param_1 + 0x144) =
             --(FLOAT_8043c700 *
                (float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - DOUBLE_8043c710) -
               FLOAT_8043c6fc);
      }
    }
    else {
      uVar2 = 0;
      if (7 < *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x96) * 4 + 0x1810)) {
        iVar1 = *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x96) * 4 + 0x1810) + -1;
        iVar1 = iVar1 / 7 + (iVar1 >> 0x1f);
        uVar2 = iVar1 - (iVar1 >> 0x1f);
      }
      *(float *)(param_1 + 0x144) =
           --(FLOAT_8043c708 *
              (float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - DOUBLE_8043c710) -
             (*(float *)(param_1 + 0x148) - FLOAT_8043c704));
    }
    *(uint *)(param_1 + 0x14c) = uVar2;
    *(undefined1 *)(param_1 + 0x151) = 0;
    zz_01f60d0_(param_1,6);
  }
  return;
}



// ==== 801f6a88  zz_01f6a88_ ====

void zz_01f6a88_(int param_1)

{
  *(char *)(param_1 + 0x150) = *(char *)(param_1 + 0x150) + -1;
  return;
}



// ==== 801f6a98  FUN_801f6a98 ====

void FUN_801f6a98(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined4 in_r10;
  undefined8 uVar10;
  
  uVar6 = 1;
  uVar5 = 0x31;
  iVar8 = *(char *)(param_9 + 0x12) * 0x1c;
  *(undefined **)(param_9 + 0x54) = &DAT_803a26b8 + iVar8;
  *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(*(int *)(param_9 + 0x8c) + 0x96);
  bVar1 = *(byte *)(*(int *)(param_9 + 0x8c) + 0x88);
  uVar7 = (uint)bVar1;
  *(byte *)(param_9 + 0x88) = bVar1;
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x31;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar9 = iVar8;
  uVar10 = zz_0089100_(param_9,0x20,1);
  zz_0006fb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xcc),*(int *)(param_9 + 0xe0),(int)(char)(&DAT_803a26b8)[iVar8],
              uVar5,uVar6,uVar7,iVar9,in_r10);
  fVar3 = FLOAT_8043c728;
  fVar2 = FLOAT_8043c6f0;
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x88) + '\x11';
  fVar4 = FLOAT_8043c72c;
  *(float *)(param_9 + 0x60) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  uVar5 = *(undefined4 *)(&DAT_803a26c0 + iVar8);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803a26bc + iVar8);
  *(undefined4 *)(param_9 + 0x68) = uVar5;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803a26c4 + iVar8);
  *(float *)(param_9 + 0x68) = *(float *)(param_9 + 0x68) + fVar3;
  *(float *)(param_9 + 0x3c) = fVar4;
  *(short *)(param_9 + 0x1c) = (short)(char)(&DAT_803a26b9)[iVar8];
  if (-1 < (char)(&DAT_80435c08)[*(char *)(param_9 + 0x12)]) {
    zz_01f60d0_(param_9,(int)(char)(&DAT_80435c08)[*(char *)(param_9 + 0x12)]);
  }
  return;
}



// ==== 801f6bb4  FUN_801f6bb4 ====

void FUN_801f6bb4(int param_1)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    sVar2 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar2;
    if (0 < sVar2) {
      return;
    }
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0x1e;
  }
  *(float *)(param_1 + 0x68) = *(float *)(param_1 + 0x68) + *(float *)(param_1 + 0x3c);
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(*(int *)(param_1 + 0x54) + 8);
    zz_01f6a88_(*(int *)(param_1 + 0x8c));
  }
  return;
}



// ==== 801f6c60  FUN_801f6c60 ====

void FUN_801f6c60(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_0009958_(*(int *)(param_9 + 0xe0),1);
  return;
}



// ==== 801f6ca0  FUN_801f6ca0 ====

/* WARNING: Removing unreachable block (ram,0x801f6fdc) */
/* WARNING: Removing unreachable block (ram,0x801f6cb0) */

void FUN_801f6ca0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  undefined4 extraout_r4;
  int iVar3;
  float *pfVar4;
  uint uVar5;
  int unaff_r28;
  int unaff_r29;
  int unaff_r30;
  int iVar6;
  undefined8 uVar7;
  double dVar8;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(*(int *)(param_9 + 0x8c) + 0x96);
  *(undefined1 *)(param_9 + 0x88) = *(undefined1 *)(*(int *)(param_9 + 0x8c) + 0x88);
  *(undefined *)(param_9 + 0x13) = (&DAT_80435c0c)[*(char *)(param_9 + 0x12) * 2];
  *(undefined1 *)(param_9 + 0x1b) = 0;
  cVar1 = *(char *)(param_9 + 0x12);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_9 + 0x84) = 0xa0;
    unaff_r30 = (int)*(short *)(PTR_DAT_80433934 + 0x182c);
    if (unaff_r30 == 0) {
      *(undefined1 *)(param_9 + 0x18) = 2;
      return;
    }
    unaff_r29 = 10;
    if ((*(short *)(PTR_DAT_80433934 + 0x1830) == 0) && (*(short *)(PTR_DAT_80433934 + 0x182e) == 0)
       ) {
      unaff_r28 = 0;
    }
    else {
      unaff_r28 = 1;
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_9 + 0x84) = 0xa0;
      unaff_r30 = (int)*(short *)(PTR_DAT_80433934 + 0x1830);
      if (unaff_r30 == 0) {
        *(undefined1 *)(param_9 + 0x18) = 2;
        return;
      }
      unaff_r29 = 10;
      unaff_r28 = 0;
    }
    else if (-1 < cVar1) {
      *(undefined1 *)(param_9 + 0x84) = 0xa0;
      unaff_r30 = (int)*(short *)(PTR_DAT_80433934 + 0x182e);
      if (unaff_r30 == 0) {
        *(undefined1 *)(param_9 + 0x18) = 2;
        return;
      }
      unaff_r29 = 10;
      if (*(short *)(PTR_DAT_80433934 + 0x1830) == 0) {
        unaff_r28 = 0;
      }
      else {
        unaff_r28 = 1;
      }
    }
  }
  else if (cVar1 < '\x04') {
    *(undefined1 *)(param_9 + 0x84) = 0xa0;
    unaff_r30 = *(int *)(PTR_DAT_80433934 + *(char *)(param_9 + 0x96) * 4 + 0x17e0);
    if (unaff_r30 < 0) {
      *(undefined1 *)(param_9 + 0x1b) = 1;
      iVar3 = 999999;
      unaff_r30 = -unaff_r30;
    }
    else {
      iVar3 = 9999999;
    }
    unaff_r29 = 1000000;
    if (iVar3 < unaff_r30) {
      unaff_r30 = iVar3;
    }
    unaff_r28 = 0;
  }
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar7 = zz_0089100_(param_9,0x20,1);
  iVar3 = param_9;
  dVar8 = DOUBLE_8043c710;
  for (iVar6 = 0; iVar2 = (int)*(char *)(param_9 + 0x13), iVar6 < iVar2; iVar6 = iVar6 + 1) {
    uVar5 = unaff_r30 / unaff_r29;
    if (uVar5 != 0) {
      unaff_r28 = 1;
    }
    pfVar4 = (float *)0xd;
    zz_0006fb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xcc),*(int *)(iVar3 + 0xe0),0xd,param_12,param_13,param_14,
                param_15,param_16);
    uVar7 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uVar5 ^ 0x80000000) - dVar8),
                        param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0xcc),*(int *)(iVar3 + 0xe0),pfVar4,param_12,param_13,
                        param_14,param_15,param_16);
    uVar7 = zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar3 + 0xe0),extraout_r4,pfVar4,param_12,param_13,param_14,
                        param_15,param_16);
    if (((uVar5 == 0) && (unaff_r28 == 0)) && (unaff_r29 != 1)) {
      *(undefined1 *)(*(int *)(iVar3 + 0xe0) + 0x10) = 0;
    }
    iVar3 = iVar3 + 4;
    iVar2 = unaff_r29 / 10 + (unaff_r29 >> 0x1f);
    unaff_r30 = unaff_r30 - (unaff_r30 / unaff_r29) * unaff_r29;
    unaff_r29 = iVar2 - (iVar2 >> 0x1f);
  }
  if (*(char *)(param_9 + 0x1b) != '\0') {
    iVar6 = iVar2 + -1;
    iVar3 = param_9 + iVar6 * 4;
    if (-1 < iVar6) {
      do {
        if (*(char *)(*(int *)(iVar3 + 0xe0) + 0x10) == '\0') {
          uVar7 = zz_0006fb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              *(int *)(param_9 + 0xcc),*(int *)(param_9 + iVar6 * 4 + 0xe0),0xc,
                              param_12,param_13,param_14,param_15,param_16);
          break;
        }
        iVar3 = iVar3 + -4;
        iVar6 = iVar6 + -1;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
  }
  cVar1 = *(char *)(*(char *)(param_9 + 0x12) * 2 + -0x7fbca3f3);
  *(char *)(param_9 + 0x87) = cVar1;
  if (-1 < cVar1) {
    zz_0006fb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xcc),*(int *)(param_9 + *(char *)(param_9 + 0x13) * 4 + 0xe0),
                (int)*(char *)(*(char *)(param_9 + 0x12) * 2 + -0x7fbca3f3),param_12,param_13,
                param_14,param_15,param_16);
  }
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x88) + '\x11';
  return;
}



// ==== 801f6ffc  FUN_801f6ffc ====

void FUN_801f6ffc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  double dVar9;
  double dVar10;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [12];
  
  pfVar4 = (float *)(&PTR_DAT_803a27bc)[*(char *)(param_1 + 0x12)];
  iVar3 = (int)*(char *)(param_1 + 0x13);
  if (-1 < *(char *)(param_1 + 0x87)) {
    iVar3 = iVar3 + 1;
  }
  iVar7 = param_1;
  for (iVar6 = 0; iVar6 < iVar3; iVar6 = iVar6 + 1) {
    dVar9 = (double)FLOAT_8043c6e8;
    fVar1 = *pfVar4;
    pfVar4 = pfVar4 + 1;
    iVar5 = *(int *)(iVar7 + 0xe0);
    dVar10 = dVar9;
    gnt4_PSMTXTrans_bl((double)fVar1,dVar9,dVar9,afStack_48);
    pfVar2 = afStack_48;
    uVar8 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar2,pfVar2);
    zz_00076d0_(uVar8,dVar9,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,iVar5,afStack_48,
                (undefined *)pfVar2,param_4,param_5,param_6,param_7,param_8);
    zz_0009958_(iVar5,1);
    iVar7 = iVar7 + 4;
  }
  return;
}



// ==== 801f70b4  FUN_801f70b4 ====

/* WARNING: Removing unreachable block (ram,0x801f7294) */
/* WARNING: Removing unreachable block (ram,0x801f70c4) */

void FUN_801f70b4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  bool bVar1;
  float fVar2;
  undefined4 extraout_r4;
  undefined4 uVar3;
  float *pfVar4;
  undefined4 uVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined8 uVar12;
  double dVar13;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(*(int *)(param_9 + 0x8c) + 0x96);
  *(undefined1 *)(param_9 + 0x88) = *(undefined1 *)(*(int *)(param_9 + 0x8c) + 0x88);
  *(undefined4 *)(param_9 + 0x54) =
       *(undefined4 *)(PTR_DAT_80433934 + *(char *)(param_9 + 0x96) * 4 + 0x17f8);
  *(undefined4 *)(param_9 + 0x14c) =
       *(undefined4 *)(PTR_DAT_80433934 + *(char *)(param_9 + 0x96) * 4 + 0x1810);
  if (*(int *)(param_9 + 0x14c) < 0) {
    *(undefined4 *)(param_9 + 0x14c) = 0;
  }
  *(undefined4 *)(param_9 + 0x144) = 0;
  uVar5 = 0xa0;
  *(undefined4 *)(param_9 + 0x148) = 0;
  *(undefined1 *)(param_9 + 0x84) = 0xa0;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar12 = zz_0089100_(param_9,0x20,1);
  fVar2 = FLOAT_8043c6e8;
  uVar3 = 6;
  *(float *)(param_9 + 0x6c) = FLOAT_8043c6e8;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 100) = fVar2;
  uVar12 = zz_0006fb4_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(param_9 + 0xcc),*(int *)(param_9 + 0xe0),6,uVar5,in_r7,in_r8,in_r9,
                       in_r10);
  uVar12 = zz_0007908_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(param_9 + 0xe0),(undefined4 *)(param_9 + 100),uVar3,uVar5,in_r7,
                       in_r8,in_r9,in_r10);
  uVar12 = zz_0006fb4_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(param_9 + 0xcc),*(int *)(param_9 + 0xe4),5,uVar5,in_r7,in_r8,in_r9,
                       in_r10);
  iVar11 = *(int *)(param_9 + 0x14c);
  bVar1 = false;
  *(undefined1 *)(param_9 + 0x13) = 0;
  uVar8 = 100;
  iVar10 = param_9;
  dVar13 = DOUBLE_8043c710;
  for (iVar9 = 0; iVar9 < 3; iVar9 = iVar9 + 1) {
    uVar7 = iVar11 / (int)uVar8;
    iVar6 = *(int *)(iVar10 + 0xe8);
    if (uVar7 != 0) {
      bVar1 = true;
    }
    pfVar4 = (float *)0xd;
    zz_0006fb4_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xcc),iVar6,0xd,uVar5,in_r7,in_r8,in_r9,in_r10);
    uVar12 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uVar7 ^ 0x80000000) - dVar13),
                         param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         *(int *)(param_9 + 0xcc),iVar6,pfVar4,uVar5,in_r7,in_r8,in_r9,in_r10);
    uVar12 = zz_0007c30_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                         extraout_r4,pfVar4,uVar5,in_r7,in_r8,in_r9,in_r10);
    if (((uVar7 != 0) || (bVar1)) || (uVar8 == 1)) {
      *(char *)(param_9 + 0x13) = *(char *)(param_9 + 0x13) + '\x01';
    }
    else {
      *(undefined1 *)(iVar6 + 0x10) = 0;
    }
    iVar10 = iVar10 + 4;
    iVar6 = (iVar11 / (int)uVar8) * uVar8;
    uVar8 = uVar8 / 10;
    iVar11 = iVar11 - iVar6;
  }
  zz_01f60d0_(param_9,8);
  *(undefined2 *)(param_9 + 0x1c) = 4;
  return;
}



// ==== 801f72b0  FUN_801f72b0 ====

void FUN_801f72b0(int param_1)

{
  (**(code **)(&DAT_80435c14 + *(char *)(param_1 + 0x19) * 4))(param_1,param_1 + 0x144);
  return;
}



// ==== 801f72ec  FUN_801f72ec ====

void FUN_801f72ec(int param_1,int param_2)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (sVar1 < 1) {
    *(undefined2 *)(param_1 + 0x1c) = 4;
    *(int *)(param_2 + 4) = *(int *)(param_2 + 4) + 1;
    if ((*(int *)(param_2 + 8) <= *(int *)(param_2 + 4)) || (0x14 < *(int *)(param_2 + 4))) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      *(undefined4 *)(param_2 + 4) = 0x38;
      if (*(int *)(param_2 + 8) < *(int *)(param_2 + 4)) {
        *(int *)(param_2 + 4) = *(int *)(param_2 + 8);
      }
      *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x88) + '\x11';
      zz_01f6a88_(*(int *)(param_1 + 0x8c));
      zz_01f73a8_(param_1,param_2);
    }
  }
  return;
}



// ==== 801f73a8  zz_01f73a8_ ====

void zz_01f73a8_(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < *(int *)(param_2 + 8)) {
    iVar1 = *(int *)(param_2 + 8) + -1;
    iVar1 = iVar1 / 7 + (iVar1 >> 0x1f);
    iVar1 = iVar1 - (iVar1 >> 0x1f);
  }
  *(float *)(param_1 + 0x68) =
       -(FLOAT_8043c700 *
         (float)((double)CONCAT44(0x43300000,iVar1 + 1U ^ 0x80000000) - DOUBLE_8043c710) -
        FLOAT_8043c6fc);
  return;
}



// ==== 801f7414  FUN_801f7414 ====

/* WARNING: Removing unreachable block (ram,0x801f7620) */
/* WARNING: Removing unreachable block (ram,0x801f7424) */

void FUN_801f7414(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar7;
  float fStack_a8;
  float local_a4;
  float local_9c;
  float local_98;
  float local_94;
  float afStack_90 [12];
  float afStack_60 [12];
  undefined4 local_30;
  uint uStack_2c;
  
  uVar2 = 0xffffffff;
  local_9c = FLOAT_8043c6e8;
  dVar7 = (double)FLOAT_8043c700;
  local_94 = FLOAT_8043c730;
  do {
    uVar2 = uVar2 + 1;
    if (PTR_DAT_80433930[0x29] == '\0') {
      local_98 = FLOAT_8043c700 *
                 (float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - DOUBLE_8043c710) -
                 FLOAT_8043c6fc;
    }
    else {
      local_98 = FLOAT_8043c700 *
                 (float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - DOUBLE_8043c710) -
                 FLOAT_8043c734;
    }
    uStack_2c = uVar2 ^ 0x80000000;
    local_98 = -local_98;
    local_30 = 0x43300000;
    zz_0005744_((float *)(param_1 + 0x114),&local_9c,&fStack_a8);
  } while (local_a4 < (float)((double)*(float *)(*(int *)(param_1 + 0x8c) + 0x3c) - dVar7));
  if (*(int *)(param_1 + 0x144) != uVar2 * 7) {
    *(uint *)(param_1 + 0x144) = uVar2 * 7;
    *(int *)(param_1 + 0x148) = *(int *)(param_1 + 0x14c) - *(int *)(param_1 + 0x144);
    if (0x38 < *(int *)(param_1 + 0x148)) {
      *(undefined4 *)(param_1 + 0x148) = 0x38;
    }
  }
  dVar7 = (double)*(float *)(param_1 + 0x68);
  dVar6 = (double)*(float *)(param_1 + 0x6c);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 100),dVar7,dVar6,afStack_60);
  pfVar1 = afStack_60;
  uVar5 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar5,dVar7,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),afStack_60,
              (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
  zz_0009958_(*(int *)(param_1 + 0xe0),1);
  dVar6 = (double)FLOAT_8043c6e8;
  dVar7 = dVar6;
  gnt4_PSMTXTrans_bl((double)FLOAT_8043c738,dVar6,dVar6,afStack_90);
  pfVar1 = afStack_60;
  uVar5 = gnt4_PSMTXConcat_bl(pfVar1,afStack_90,pfVar1);
  for (iVar3 = 0; iVar3 < *(char *)(param_1 + 0x13); iVar3 = iVar3 + 1) {
    iVar4 = (4 - iVar3) * 4 + 0xe0;
    zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + iVar4),afStack_60
                ,(undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
    zz_0009958_(*(int *)(param_1 + iVar4),1);
    dVar6 = (double)FLOAT_8043c6e8;
    dVar7 = dVar6;
    gnt4_PSMTXTrans_bl((double)FLOAT_8043c738,dVar6,dVar6,afStack_90);
    pfVar1 = afStack_60;
    uVar5 = gnt4_PSMTXConcat_bl(pfVar1,afStack_90,pfVar1);
  }
  dVar6 = (double)FLOAT_8043c6e8;
  dVar7 = dVar6;
  gnt4_PSMTXTrans_bl((double)FLOAT_8043c73c,dVar6,dVar6,afStack_90);
  pfVar1 = afStack_60;
  uVar5 = gnt4_PSMTXConcat_bl(pfVar1,afStack_90,pfVar1);
  zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe4),afStack_60,
              (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
  zz_0009958_(*(int *)(param_1 + 0xe4),1);
  return;
}



// ==== 801f7644  FUN_801f7644 ====

void FUN_801f7644(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = *(undefined4 *)(param_1 + 0x148);
  }
  if (param_3 == (undefined4 *)0x0) {
    return;
  }
  *param_3 = *(undefined4 *)(param_1 + 0x144);
  return;
}



// ==== 801f7668  FUN_801f7668 ====

void FUN_801f7668(int param_1)

{
  int *piVar1;
  byte bVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  undefined2 *puVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  uVar5 = 0x31;
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(undefined1 *)(param_1 + 0x96) = *(undefined1 *)(*(int *)(param_1 + 0x8c) + 0x96);
  bVar2 = *(byte *)(*(int *)(param_1 + 0x8c) + 0x88);
  uVar6 = (uint)bVar2;
  *(byte *)(param_1 + 0x88) = bVar2;
  *(undefined1 *)(param_1 + 0x84) = 0x31;
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0x20,1);
  *(float *)(param_1 + 100) = FLOAT_8043c6e8;
  fVar4 = FLOAT_8043c740;
  puVar8 = (undefined2 *)(param_1 + 0x144);
  *(float *)(param_1 + 0x6c) = FLOAT_8043c730;
  fVar3 = FLOAT_8043c6f0;
  *(float *)(param_1 + 0x5c) = fVar4;
  dVar11 = DOUBLE_8043c710;
  *(float *)(param_1 + 0x58) = fVar4;
  dVar12 = (double)FLOAT_8043c700;
  *(float *)(param_1 + 0x60) = fVar3;
  dVar10 = (double)(float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x12) ^ 0x80000000)
                          - dVar11);
  *(float *)(param_1 + 0x68) = -(float)(dVar12 * dVar10 - (double)FLOAT_8043c6fc);
  iVar9 = param_1;
  for (iVar7 = 0; iVar7 < *(char *)(param_1 + 0x99); iVar7 = iVar7 + 1) {
    dVar10 = (double)zz_0006fb4_(dVar10,dVar11,dVar12,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb334,
                                 *(int *)(iVar9 + 0xe0),*(int *)PTR_DAT_80350d0c,uVar5,uVar6,in_r8,
                                 in_r9,in_r10);
    *puVar8 = 0xffff;
    puVar8 = puVar8 + 1;
    piVar1 = (int *)(iVar9 + 0xe0);
    iVar9 = iVar9 + 4;
    *(undefined1 *)(*piVar1 + 0x10) = 0;
  }
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x88) + '\x11';
  return;
}



// ==== 801f7798  FUN_801f7798 ====

void FUN_801f7798(int param_1)

{
  int *piVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 uVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  char local_38;
  byte bStack_37;
  int local_34;
  int local_30 [2];
  undefined4 local_28;
  uint uStack_24;
  
  psVar7 = (short *)(param_1 + 0x144);
  FUN_801f7644(*(int *)(param_1 + 0x8c),local_30,&local_34);
  dVar11 = DOUBLE_8043c710;
  uVar6 = 0x92492493;
  iVar4 = local_34 / 7 + (local_34 >> 0x1f);
  iVar3 = local_34 / 0x38 + (local_34 >> 0x1f);
  uVar5 = iVar4 - (iVar4 >> 0x1f);
  local_34 = local_34 + (iVar3 - (iVar3 >> 0x1f)) * -0x38;
  iVar4 = local_34 / 7 + (local_34 >> 0x1f);
  iVar3 = local_34;
  for (iVar4 = iVar4 - (iVar4 >> 0x1f); iVar4 != *(char *)(param_1 + 0x12);
      iVar4 = (iVar9 * 8 | (uint)((iVar4 + 1) * 0x20000000 + iVar9) >> 0x1d) - iVar9) {
    uVar5 = uVar5 + 1;
    iVar3 = iVar3 + 7;
    iVar9 = iVar4 + 1 >> 0x1f;
  }
  uStack_24 = uVar5 ^ 0x80000000;
  local_28 = 0x43300000;
  dVar12 = (double)FLOAT_8043c700;
  dVar10 = (double)(float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_8043c710);
  *(float *)(param_1 + 0x68) = -(float)(dVar12 * dVar10 - (double)FLOAT_8043c6fc);
  iVar3 = iVar3 - local_34;
  if (local_30[0] < iVar3) {
    iVar3 = param_1;
    for (iVar4 = 0; iVar4 < *(char *)(param_1 + 0x99); iVar4 = iVar4 + 1) {
      piVar1 = (int *)(iVar3 + 0xe0);
      iVar3 = iVar3 + 4;
      *(undefined1 *)(*piVar1 + 0x10) = 0;
    }
  }
  else {
    iVar4 = uVar5 * 0xe;
    iVar9 = param_1;
    for (iVar8 = 0; iVar8 < *(char *)(param_1 + 0x99); iVar8 = iVar8 + 1) {
      if (iVar3 + iVar8 < local_30[0]) {
        *(undefined1 *)(*(int *)(iVar9 + 0xe0) + 0x10) = 1;
        sVar2 = *(short *)(*(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 0x96) * 4 + 0x17f8) +
                          iVar4);
        if (sVar2 != *psVar7) {
          local_38 = (char)((ushort)sVar2 >> 8);
          *psVar7 = sVar2;
          bStack_37 = (byte)sVar2;
          dVar10 = (double)zz_0006fb4_(dVar10,dVar11,dVar12,in_f4,in_f5,in_f6,in_f7,in_f8,
                                       DAT_803bb334,*(int *)(iVar9 + 0xe0),
                                       *(int *)((&PTR_DAT_80350d0c)[local_38] + (uint)bStack_37 * 4)
                                       ,uVar5,uVar6,in_r8,in_r9,in_r10);
        }
      }
      else {
        *(undefined1 *)(*(int *)(iVar9 + 0xe0) + 0x10) = 0;
      }
      iVar9 = iVar9 + 4;
      iVar4 = iVar4 + 2;
      psVar7 = psVar7 + 1;
    }
  }
  return;
}



// ==== 801f79a0  FUN_801f79a0 ====

/* WARNING: Removing unreachable block (ram,0x801f7a34) */
/* WARNING: Removing unreachable block (ram,0x801f7a2c) */
/* WARNING: Removing unreachable block (ram,0x801f79b8) */
/* WARNING: Removing unreachable block (ram,0x801f79b0) */

void FUN_801f79a0(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  int iVar2;
  int iVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar7;
  double dVar8;
  float afStack_68 [15];
  
  dVar8 = (double)FLOAT_8043c748;
  iVar3 = param_1;
  fVar1 = FLOAT_8043c744;
  for (iVar2 = 0; dVar7 = (double)fVar1, iVar2 < *(char *)(param_1 + 0x99); iVar2 = iVar2 + 1) {
    dVar5 = (double)FLOAT_8043c6e8;
    dVar6 = dVar5;
    uVar4 = zz_020b4ac_(dVar7,dVar5,dVar5,(float *)(param_1 + 0x114),afStack_68);
    zz_00076d0_(uVar4,dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_68,
                param_3,param_4,param_5,param_6,param_7,param_8);
    zz_0009958_(*(int *)(iVar3 + 0xe0),1);
    fVar1 = (float)(dVar7 + dVar8);
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 801f7a58  FUN_801f7a58 ====

void FUN_801f7a58(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar6;
  
  uVar4 = 0x19;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(*(int *)(param_9 + 0x8c) + 0x96);
  bVar1 = *(byte *)(*(int *)(param_9 + 0x8c) + 0x88);
  uVar5 = (uint)bVar1;
  *(byte *)(param_9 + 0x88) = bVar1;
  *(undefined1 *)(param_9 + 0x84) = 0x19;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0x20,1);
  fVar3 = FLOAT_8043c74c;
  dVar6 = (double)FLOAT_8043c74c;
  *(float *)(param_9 + 100) = FLOAT_8043c6e8;
  fVar2 = FLOAT_8043c6f0;
  *(float *)(param_9 + 0x6c) = fVar3;
  *(float *)(param_9 + 0x60) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  if (PTR_DAT_80433930[0x29] != '\0') {
    *(float *)(param_9 + 0x5c) = FLOAT_8043c6f4;
  }
  if (*(char *)(param_9 + 0x12) == '\0') {
    *(float *)(param_9 + 0x68) = FLOAT_8043c750;
    *(undefined2 *)(param_9 + 0x74) = 0;
  }
  else {
    *(float *)(param_9 + 0x68) = FLOAT_8043c754;
    *(undefined2 *)(param_9 + 0x74) = 0x8000;
  }
  *(undefined2 *)(param_9 + 0x1c) = 0;
  zz_0006fb4_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xcc)
              ,*(int *)(param_9 + 0xe0),0xe,uVar4,uVar5,in_r8,in_r9,in_r10);
  *(undefined1 *)(*(int *)(param_9 + 0xe0) + 0x10) = 0;
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x88) + '\x11';
  return;
}



// ==== 801f7be0  FUN_801f7be0 ====

void FUN_801f7be0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_0009958_(*(int *)(param_9 + 0xe0),2);
  return;
}



// ==== 801f7c20  FUN_801f7c20 ====

void FUN_801f7c20(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  uint uVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  int iVar7;
  short *psVar8;
  double dVar9;
  double dVar10;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(*(int *)(param_9 + 0x8c) + 0x96);
  bVar1 = *(byte *)(*(int *)(param_9 + 0x8c) + 0x88);
  uVar5 = (uint)bVar1;
  *(byte *)(param_9 + 0x88) = bVar1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0x20,1);
  fVar2 = FLOAT_8043c758;
  *(undefined1 *)(param_9 + 0x84) = 0x11;
  fVar3 = FLOAT_8043c75c;
  *(float *)(param_9 + 100) = fVar2;
  fVar4 = FLOAT_8043c760;
  dVar10 = (double)FLOAT_8043c760;
  *(float *)(param_9 + 0x68) = fVar3;
  fVar2 = FLOAT_8043c6f0;
  *(float *)(param_9 + 0x6c) = fVar4;
  *(float *)(param_9 + 0x60) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  if (PTR_DAT_80433930[0x29] == '\x01') {
    dVar9 = (double)FLOAT_8043c724;
    *(float *)(param_9 + 0x5c) = FLOAT_8043c6f4;
    dVar10 = (double)*(float *)(param_9 + 0x68);
    *(float *)(param_9 + 0x68) = (float)(dVar10 + dVar9);
  }
  else {
    *(float *)(param_9 + 0x5c) = fVar2;
  }
  *(undefined2 *)(param_9 + 0x1c) = 0;
  iVar6 = 0;
  psVar8 = (short *)&DAT_80435c1c;
  iVar7 = param_9;
  do {
    dVar10 = (double)zz_0006fb4_(dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 *(int *)(param_9 + 0xcc),*(int *)(iVar7 + 0xe0),(int)*psVar8,uVar5,
                                 in_r7,in_r8,in_r9,in_r10);
    iVar6 = iVar6 + 1;
    iVar7 = iVar7 + 4;
    psVar8 = psVar8 + 1;
  } while (iVar6 < 4);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x88) + '\x11';
  return;
}



// ==== 801f7d68  FUN_801f7d68 ====

void FUN_801f7d68(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [14];
  
  pfVar4 = (float *)&DAT_803a27cc;
  iVar2 = 0;
  iVar3 = param_1;
  do {
    dVar6 = (double)pfVar4[1];
    dVar7 = (double)pfVar4[2];
    gnt4_PSMTXTrans_bl((double)*pfVar4,dVar6,dVar7,afStack_48);
    pfVar1 = afStack_48;
    uVar5 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar1,pfVar1);
    zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_48,
                (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
    zz_0009958_(*(int *)(iVar3 + 0xe0),0);
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + 4;
    pfVar4 = pfVar4 + 3;
  } while (iVar2 < 2);
  iVar3 = 2;
  if ((*(ushort *)(param_1 + 0x1c) & 0x10) != 0) {
    iVar3 = 3;
  }
  dVar6 = (double)(float)(&DAT_803a27d0)[iVar3 * 3];
  dVar7 = (double)(float)(&DAT_803a27d4)[iVar3 * 3];
  gnt4_PSMTXTrans_bl((double)(float)(&DAT_803a27cc)[iVar3 * 3],dVar6,dVar7,afStack_48);
  pfVar4 = afStack_48;
  uVar5 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar4,pfVar4);
  iVar3 = param_1 + iVar3 * 4;
  zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_48,
              (undefined *)pfVar4,param_4,param_5,param_6,param_7,param_8);
  zz_0009958_(*(int *)(iVar3 + 0xe0),0);
  return;
}



// ==== 801f7e70  zz_01f7e70_ ====

void zz_01f7e70_(void)

{
  PTR_DAT_80433934[0x45] = 0;
  (*(code *)(&PTR_FUN_803a281c)[*(short *)PTR_DAT_80433944])();
  return;
}



// ==== 801f7eb8  FUN_801f7eb8 ====

undefined4 FUN_801f7eb8(void)

{
  (*(code *)(&PTR_FUN_80435c28)[*(short *)(PTR_DAT_80433944 + 2)])();
  return 0;
}



// ==== 801f7ef4  FUN_801f7ef4 ====

void FUN_801f7ef4(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 uVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 uVar2;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar3;
  
  *(short *)(PTR_DAT_80433944 + 2) = *(short *)(PTR_DAT_80433944 + 2) + 1;
  uVar3 = zz_0197854_(3);
  uVar1 = 0x100000;
  uVar2 = 3;
  zz_0088398_(DAT_80436238 + 0xfe800,0x100000,3);
  uVar3 = zz_00e9ac0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,uVar1,uVar2,
                      in_r6,in_r7,in_r8,in_r9,in_r10);
  uVar3 = zz_00e9ac0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,extraout_r4,
                      uVar2,in_r6,in_r7,in_r8,in_r9,in_r10);
  uVar3 = zz_00e9ac0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,extraout_r4_00
                      ,uVar2,in_r6,in_r7,in_r8,in_r9,in_r10);
  uVar3 = zz_004369c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,extraout_r4_01
                      ,uVar2,in_r6,in_r7,in_r8,in_r9,in_r10);
  uVar3 = zz_00439a0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2);
  zz_00437b0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
  return;
}



// ==== 801f7f70  FUN_801f7f70 ====

void FUN_801f7f70(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined *puVar2;
  undefined4 uVar3;
  undefined *puVar4;
  uint uVar5;
  undefined *puVar6;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 extraout_f1;
  undefined8 uVar7;
  
  iVar1 = zz_000a3c4_();
  puVar6 = PTR_DAT_80433944;
  if (iVar1 == 0) {
    puVar2 = (undefined *)0x0;
    uVar3 = 0;
    *(short *)PTR_DAT_80433944 = *(short *)PTR_DAT_80433944 + 1;
    puVar4 = PTR_DAT_80433944;
    *(undefined2 *)(PTR_DAT_80433944 + 2) = 0;
    zz_002a5f4_(0,0,0,0);
    uVar7 = zz_008c3a0_(0);
    uVar7 = zz_004370c_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar7 >> 0x20),(int)uVar7,puVar2,uVar3,puVar4,puVar6,in_r9,
                        in_r10);
    uVar7 = zz_0008a94_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                        extraout_r4,puVar2,uVar3,puVar4,puVar6,in_r9,in_r10);
    zz_007fd6c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_016e650_,0,puVar2,
                uVar3,puVar4,puVar6,in_r9,in_r10);
    uVar7 = zz_01f87d8_();
    zz_00e99c8_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,DAT_8031a0c8,uVar3
                ,puVar4,puVar6,in_r9,in_r10);
    zz_0027aac_(0,0x3c,0);
    uVar5 = 0;
    for (iVar1 = 0; iVar1 < 4; iVar1 = iVar1 + 1) {
      if (uVar5 != 0) break;
      if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar1) != 0) {
        PTR_DAT_80433944[0x14] = (char)iVar1;
        uVar5 = 1 << iVar1;
      }
    }
    PTR_DAT_80433930[2] = (char)uVar5;
    PTR_DAT_80433930[3] = 1;
  }
  return;
}



// ==== 801f8080  FUN_801f8080 ====

undefined4 FUN_801f8080(void)

{
  *(short *)(PTR_DAT_80433944 + 8) = *(short *)(PTR_DAT_80433944 + 8) + 1;
  zz_016e694_((int)(PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x100),
              (int)(char)PTR_DAT_80433944[0x14]);
  (*(code *)(&PTR_FUN_803a2830)[*(short *)(PTR_DAT_80433944 + 2)])
            (PTR_DAT_80433944 + (char)PTR_DAT_80433944[0x14] * 0x80 + 0x100);
  zz_01f880c_();
  zz_01f88ec_();
  return 0;
}



// ==== 801f8108  FUN_801f8108 ====

void FUN_801f8108(void)

{
  (*(code *)(&PTR_FUN_80435c30)[*(short *)(PTR_DAT_80433944 + 4)])();
  return;
}



// ==== 801f8140  FUN_801f8140 ====

void FUN_801f8140(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char cVar5;
  char *pcVar6;
  
  iVar4 = 0;
  iVar2 = 0x14;
  iVar3 = 0;
  cVar5 = -1;
  *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
  *(undefined1 *)(param_1 + 0x60) = 0;
  do {
    if (*(char *)(*(int *)(param_1 + 0x40) + iVar3 + 0x29) != '\0') {
      if (iVar4 == *(char *)(param_1 + 0x61)) {
        cVar5 = *(char *)(param_1 + 0x60);
      }
      cVar1 = *(char *)(param_1 + 0x60);
      *(char *)(param_1 + 0x60) = cVar1 + '\x01';
      *(char *)(param_1 + cVar1 + 0x4c) = (char)iVar4;
    }
    iVar3 = iVar3 + 0x6c;
    iVar4 = iVar4 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  if (cVar5 < '\0') {
    *(undefined1 *)(param_1 + 0x61) = 0;
  }
  else {
    *(char *)(param_1 + 0x61) = cVar5;
  }
  *(undefined1 *)(param_1 + 0x3d) = 0;
  *(undefined1 *)(param_1 + 0x3e) = 0;
  *(undefined1 *)(param_1 + 0x3f) = 0;
  for (pcVar6 = &DAT_803a2800; -1 < *pcVar6; pcVar6 = pcVar6 + 2) {
    zz_01f896c_(PTR_DAT_80433944[0x14],(int)*pcVar6,pcVar6[1]);
  }
  return;
}



// ==== 801f8248  FUN_801f8248 ====

void FUN_801f8248(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    *(short *)(PTR_DAT_80433944 + 2) = *(short *)(PTR_DAT_80433944 + 2) + 1;
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    zz_0027c1c_();
  }
  return;
}



// ==== 801f8298  FUN_801f8298 ====

void FUN_801f8298(void)

{
  (*(code *)(&PTR_FUN_803a283c)[*(short *)(PTR_DAT_80433944 + 4)])();
  return;
}



// ==== 801f82d4  FUN_801f82d4 ====

void FUN_801f82d4(void)

{
  (*(code *)(&PTR_LAB_803a2848)[*(short *)(PTR_DAT_80433944 + 6)])();
  return;
}



// ==== 801f8374  FUN_801f8374 ====

void FUN_801f8374(int param_1)

{
  ushort uVar1;
  int iVar2;
  
  iVar2 = (int)*(char *)(param_1 + 0x61);
  if ((*(ushort *)(param_1 + 0xc) & 1) == 0) {
    if ((*(ushort *)(param_1 + 0xc) & 2) != 0) {
      for (iVar2 = iVar2 + 1; *(char *)(param_1 + 0x60) <= iVar2;
          iVar2 = iVar2 - *(char *)(param_1 + 0x60)) {
      }
    }
  }
  else {
    for (iVar2 = iVar2 + -1; iVar2 < 0; iVar2 = iVar2 + *(char *)(param_1 + 0x60)) {
    }
  }
  if (iVar2 != *(char *)(param_1 + 0x61)) {
    *(char *)(param_1 + 0x61) = (char)iVar2;
    zz_00f0468_(0,0x77,0);
  }
  uVar1 = *(ushort *)(param_1 + 0xe);
  if ((uVar1 & 0x200) == 0) {
    if ((uVar1 & 0x400) == 0) {
      if ((uVar1 & 0x180) != 0) {
        iVar2 = zz_01cce38_(*(int *)(param_1 + 0x40),
                            (int)*(char *)(param_1 + *(char *)(param_1 + 0x61) + 0x4c),
                            *(int *)(PTR_DAT_80433934 + 0x120),0);
        if (iVar2 == 0) {
          zz_00f0468_(0,0x7d,0);
        }
        else {
          *(undefined2 *)(PTR_DAT_80433944 + 4) = 1;
          *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
          *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) & 0xfb;
          *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) & 0xfb;
          *(byte *)(param_1 + 0x3f) = *(byte *)(param_1 + 0x3f) | 4;
          zz_00f0468_(0,0x7a,0);
        }
      }
    }
    else {
      *(undefined2 *)(PTR_DAT_80433944 + 4) = 2;
      *(undefined2 *)(PTR_DAT_80433944 + 6) = 1;
      *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) & 0xfb;
      *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) & 0xfb;
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 2;
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 2;
    *(byte *)(param_1 + 0x3d) = *(byte *)(param_1 + 0x3d) & 0xfb;
    *(byte *)(param_1 + 0x3e) = *(byte *)(param_1 + 0x3e) & 0xfb;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 801f8544  FUN_801f8544 ====

void FUN_801f8544(void)

{
  (*(code *)(&PTR_LAB_80435c38)[*(short *)(PTR_DAT_80433944 + 6)])();
  return;
}



// ==== 801f859c  FUN_801f859c ====

void FUN_801f859c(void)

{
  short sVar1;
  
  sVar1 = *(short *)(PTR_DAT_80433944 + 0xe);
  *(short *)(PTR_DAT_80433944 + 0xe) = sVar1 + -1;
  if ((short)(sVar1 + -1) < 0) {
    *(short *)(PTR_DAT_80433944 + 2) = *(short *)(PTR_DAT_80433944 + 2) + 1;
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 3;
    zz_0027aac_(0,0x3c,1);
    zz_00e9b60_((double)FLOAT_8043c768,2,0x3c,2);
  }
  return;
}



// ==== 801f861c  FUN_801f861c ====

void FUN_801f861c(void)

{
  *(short *)(PTR_DAT_80433944 + 2) = *(short *)(PTR_DAT_80433944 + 2) + 1;
  *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
  zz_0027aac_(0,0x1e,1);
  zz_00e9b60_((double)FLOAT_8043c768,2,0x1e,2);
  return;
}



// ==== 801f8678  FUN_801f8678 ====

void FUN_801f8678(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    *(short *)PTR_DAT_80433944 = *(short *)PTR_DAT_80433944 + *(short *)(PTR_DAT_80433944 + 6);
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 2) = 0;
    zz_002a5f4_(0,0,0,0);
  }
  return;
}



// ==== 801f86e4  FUN_801f86e4 ====

int FUN_801f86e4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined *puVar2;
  undefined8 extraout_f1;
  undefined8 uVar3;
  
  puVar2 = PTR_DAT_80433944;
  cVar1 = PTR_DAT_80433944[0x14];
  uVar3 = zz_0027c1c_();
  zz_016e650_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,param_11,param_12,param_13,param_14,
              param_15,param_16);
  zz_007fd5c_();
  return (char)puVar2[(int)(char)puVar2[cVar1 * 0x80 + 0x161] + cVar1 * 0x80 + 0x14c] + 0x8001;
}



// ==== 801f8748  FUN_801f8748 ====

undefined4
FUN_801f8748(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
            double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
            undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
            undefined4 param_15,undefined4 param_16)

{
  undefined8 extraout_f1;
  undefined8 uVar1;
  
  uVar1 = zz_0027c1c_();
  zz_016e650_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14,
              param_15,param_16);
  zz_007fd5c_();
  return 0xffffffff;
}



// ==== 801f8774  FUN_801f8774 ====

int FUN_801f8774(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined *puVar2;
  undefined8 extraout_f1;
  undefined8 uVar3;
  
  puVar2 = PTR_DAT_80433944;
  cVar1 = PTR_DAT_80433944[0x14];
  uVar3 = zz_0027c1c_();
  zz_016e650_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,param_11,param_12,param_13,param_14,
              param_15,param_16);
  zz_0029fd4_();
  zz_007fd5c_();
  return (char)puVar2[(int)(char)puVar2[cVar1 * 0x80 + 0x161] + cVar1 * 0x80 + 0x14c] + 1;
}



// ==== 801f87d8  zz_01f87d8_ ====

void zz_01f87d8_(void)

{
  gnt4_memset(&DAT_803c73b0,0,0x3e4);
  zz_01f880c_();
  return;
}



// ==== 801f880c  zz_01f880c_ ====

void zz_01f880c_(void)

{
  float afStack_28 [5];
  
  DAT_803c76e4 = FLOAT_8043c770;
  DAT_803c76b8 = FLOAT_8043c76c;
  DAT_803c7698 = FLOAT_8043c768;
  PTR_DAT_80433930[0xc] = 0;
  DAT_803c769c = DAT_803c7698;
  DAT_803c76a0 = DAT_803c7698;
  DAT_803c76b0 = DAT_803c7698;
  DAT_803c76b4 = DAT_803c7698;
  DAT_803c76e0 = DAT_803c7698;
  DAT_803c76e8 = DAT_803c7698;
  gnt4_C_MTXLookAt_bl((float *)&DAT_803c7744,&DAT_803c7698,&DAT_803c76e0,&DAT_803c76b0);
  *(undefined **)(PTR_DAT_80433930 + 0x14) = &DAT_803c7744;
  gnt4_PSVECSubtract_bl(&DAT_803c7698,&DAT_803c76b0,afStack_28);
  zz_0045ef4_((float *)&DAT_803c7714,5,afStack_28,&DAT_803c76e0);
  DAT_803c7720 = DAT_803c7698;
  DAT_803c7730 = DAT_803c769c;
  DAT_803c7740 = DAT_803c76a0;
  return;
}



// ==== 801f88ec  zz_01f88ec_ ====

void zz_01f88ec_(void)

{
  zz_01f8910_();
  zz_01f8938_();
  return;
}



// ==== 801f8910  zz_01f8910_ ====

void zz_01f8910_(void)

{
  zz_0089898_(0x10);
  zz_0089554_();
  return;
}



// ==== 801f8938  zz_01f8938_ ====

void zz_01f8938_(void)

{
  zz_008a16c_();
  zz_0089c00_(0x10);
  zz_008c0dc_(FUN_80089eb4);
  return;
}



// ==== 801f896c  zz_01f896c_ ====

void zz_01f896c_(undefined1 param_1,int param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x10,1,(int)(char)(&DAT_80435c40)[param_2]);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_801f8a18;
    *(code **)(puVar1 + 0x10c) = FUN_801f8bd4;
    puVar1[0x10] = 3;
    puVar1[0x11] = (char)param_2;
    puVar1[0x12] = param_3;
    puVar1[0x96] = param_1;
    puVar1[0x13] = (&DAT_80435c40)[(char)puVar1[0x11]];
  }
  return;
}



// ==== 801f8a18  FUN_801f8a18 ====

void FUN_801f8a18(int param_1)

{
  (*(code *)(&PTR_FUN_803a2858)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801f8a54  FUN_801f8a54 ====

void FUN_801f8a54(int param_1)

{
  uint uVar1;
  int *piVar2;
  
  uVar1 = (int)*(char *)(param_1 + 0x13) << 5;
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
    (*(code *)(&PTR_FUN_803a2868)[*(char *)(param_1 + 0x11)])
              (param_1,PTR_DAT_80433944 + *(char *)(param_1 + 0x96) * 0x80 + 0x100);
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  return;
}



// ==== 801f8b24  FUN_801f8b24 ====

void FUN_801f8b24(int param_1)

{
  (*(code *)(&PTR_zz_01f8cb0__803a2888)[*(char *)(param_1 + 0x11)])
            (param_1,PTR_DAT_80433944 + *(char *)(param_1 + 0x96) * 0x80 + 0x100);
  return;
}



// ==== 801f8b8c  FUN_801f8b8c ====

void FUN_801f8b8c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801f8bd4  FUN_801f8bd4 ====

void FUN_801f8bd4(int param_1)

{
  (*(code *)(&PTR_FUN_803a28a8)[*(char *)(param_1 + 0x11)])
            (param_1,PTR_DAT_80433944 + *(char *)(param_1 + 0x96) * 0x80 + 0x100);
  return;
}



// ==== 801f8c28  FUN_801f8c28 ====

void FUN_801f8c28(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar1;
  undefined8 uVar2;
  
  pfVar1 = (float *)0x62;
  *(float *)(param_9 + 0xd4) = FLOAT_8043c778;
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
              *(int *)(param_9 + 0xe0),0x62,param_12,param_13,param_14,param_15,param_16);
  uVar2 = zz_00086b8_((double)FLOAT_8043c77c,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                      ,DAT_803bb384,*(int *)(param_9 + 0xe0),pfVar1,param_12,param_13,param_14,
                      param_15,param_16);
  uVar2 = zz_0007c30_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),extraout_r4,pfVar1,param_12,param_13,param_14,
                      param_15,param_16);
  uVar2 = zz_0007d40_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),extraout_r4_00,pfVar1,param_12,param_13,param_14,
                      param_15,param_16);
  zz_01f8cb0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,pfVar1,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801f8cb0  zz_01f8cb0_ ====

void zz_01f8cb0_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 extraout_r4;
  double dVar2;
  undefined8 uVar3;
  double dVar4;
  
  fVar1 = FLOAT_8043c784;
  dVar2 = (double)FLOAT_8043c780;
  dVar4 = (double)*(float *)(param_9 + 0xd4);
  *(float *)(param_9 + 0xd4) = (float)(dVar4 + dVar2);
  if (fVar1 <= (float)(dVar4 + dVar2)) {
    *(float *)(param_9 + 0xd4) = *(float *)(param_9 + 0xd4) - fVar1;
  }
  uVar3 = zz_0008744_((double)*(float *)(param_9 + 0xd4),dVar4,param_3,param_4,param_5,param_6,
                      param_7,param_8,DAT_803bb384,*(int *)(param_9 + 0xe0),param_11,param_12,
                      param_13,param_14,param_15,param_16);
  zz_0007c30_(uVar3,dVar4,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0),
              extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801f8d24  FUN_801f8d24 ====

void FUN_801f8d24(int param_1)

{
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x45);
  return;
}



// ==== 801f8d4c  FUN_801f8d4c ====

void FUN_801f8d4c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar1 = FLOAT_8043c788;
  *(float *)(param_9 + 0x20) = FLOAT_8043c778;
  fVar2 = FLOAT_8043c78c;
  dVar3 = (double)FLOAT_8043c78c;
  *(float *)(param_9 + 0x24) = fVar1;
  fVar1 = FLOAT_8043c780;
  *(float *)(param_9 + 0x28) = fVar2;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  zz_0006fb4_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
              *(int *)(param_9 + 0xe0),0x18,param_12,param_13,param_14,param_15,param_16);
  zz_01f8dcc_(param_9);
  return;
}



// ==== 801f8dcc  zz_01f8dcc_ ====

void zz_01f8dcc_(int param_1)

{
  float fVar1;
  double dVar2;
  
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  while (0x7f < *(short *)(param_1 + 0x1c)) {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -0x40;
  }
  dVar2 = zz_0045238_((short)((int)*(short *)(param_1 + 0x1c) << 10));
  fVar1 = FLOAT_8043c794;
  if (*(short *)(param_1 + 0x1c) < 0x10) {
    fVar1 = FLOAT_8043c790;
  }
  *(float *)(param_1 + 0x58) = (float)(dVar2 * (double)fVar1 + (double)FLOAT_8043c780);
  fVar1 = FLOAT_8043c79c;
  if (*(short *)(param_1 + 0x1c) < 0x10) {
    fVar1 = FLOAT_8043c798;
  }
  *(float *)(param_1 + 0x5c) = (float)(dVar2 * (double)fVar1 + (double)FLOAT_8043c780);
  return;
}



// ==== 801f8e70  FUN_801f8e70 ====

void FUN_801f8e70(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  undefined8 uVar2;
  double dVar3;
  double dVar4;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  if (*(short *)(param_1 + 0x1c) != 0) {
    dVar3 = (double)*(float *)(param_1 + 0x24);
    dVar4 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar3,dVar4,(float *)(param_1 + 0x114));
    pfVar1 = (float *)(param_1 + 0x58);
    uVar2 = zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),pfVar1);
    zz_00076d0_(uVar2,dVar3,dVar4,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
                (float *)(param_1 + 0x114),(undefined *)pfVar1,param_4,param_5,param_6,param_7,
                param_8);
    zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
  }
  return;
}



// ==== 801f8ee0  FUN_801f8ee0 ====

void FUN_801f8ee0(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  short sVar2;
  int iVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  float *pfVar9;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar10;
  int iVar11;
  
  fVar4 = FLOAT_8043c7a4;
  fVar1 = FLOAT_8043c7a0;
  iVar11 = 0;
  iVar6 = *(char *)(param_9 + 0x12) * 0xc;
  psVar7 = (short *)(&DAT_803a28c8 + iVar6);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(&DAT_803a28d0 + iVar6);
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x28) = fVar4;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  iVar6 = param_9;
  for (iVar10 = 0; fVar1 = FLOAT_8043c7b0, fVar4 = FLOAT_8043c778,
      iVar10 < *(char *)(param_9 + 0x13); iVar10 = iVar10 + 1) {
    pfVar9 = (float *)(*(int *)(param_9 + 0x54) + iVar11);
    if (iVar10 == 1) {
      *pfVar9 = FLOAT_8043c7a8;
      fVar1 = FLOAT_8043c7ac;
      pfVar9[1] = fVar4;
      fVar5 = FLOAT_8043c780;
      pfVar9[2] = fVar4;
      pfVar9[3] = fVar1;
      pfVar9[4] = fVar1;
      pfVar9[5] = fVar5;
    }
    else {
      pfVar9[2] = FLOAT_8043c778;
      fVar5 = FLOAT_8043c780;
      pfVar9[1] = fVar4;
      *pfVar9 = fVar4;
      pfVar9[3] = fVar1;
      pfVar9[4] = fVar1;
      pfVar9[5] = fVar5;
    }
    sVar2 = *psVar7;
    *(short *)(pfVar9 + 6) = sVar2;
    iVar3 = DAT_803bb384;
    if (-1 < sVar2) {
      iVar8 = *(int *)(iVar6 + 0xe0);
      *(short *)((int)pfVar9 + 0x1a) = *(short *)(pfVar9 + 6);
      zz_0006fb4_((double)fVar1,(double)fVar4,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                  iVar8,(int)*(short *)(pfVar9 + 6),pfVar9,in_r7,in_r8,in_r9,in_r10);
    }
    iVar11 = iVar11 + 0x20;
    psVar7 = psVar7 + 1;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 801f8ffc  FUN_801f8ffc ====

void FUN_801f8ffc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
  iVar2 = *(int *)(param_9 + 0x54);
  iVar1 = (int)*(short *)(iVar2 + 0x58);
  if (-1 < *(short *)(iVar2 + 0x58)) {
    if ((*(ushort *)(param_9 + 0x1c) & 0x10) != 0) {
      iVar1 = iVar1 + 1;
    }
    if (*(short *)(iVar2 + 0x5a) != iVar1) {
      *(short *)(iVar2 + 0x5a) = (short)iVar1;
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
                  *(int *)(param_9 + 0xe8),(int)*(short *)(iVar2 + 0x5a),param_12,param_13,param_14,
                  param_15,param_16);
    }
  }
  return;
}



// ==== 801f9070  FUN_801f9070 ====

void FUN_801f9070(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
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
  
  dVar6 = (double)*(float *)(param_1 + 0x24);
  dVar7 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar6,dVar7,(float *)(param_1 + 0x114));
  iVar4 = 0;
  iVar3 = param_1;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
    if (-1 < *(short *)(pfVar1 + 6)) {
      zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar1);
      pfVar1 = pfVar1 + 3;
      uVar5 = zz_00456a0_(afStack_48,afStack_48,pfVar1);
      zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_48,
                  (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
    }
    iVar4 = iVar4 + 0x20;
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 801f9124  FUN_801f9124 ====

void FUN_801f9124(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,int param_14,int param_15,
                 int param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  
  fVar1 = FLOAT_8043c7b4;
  iVar3 = 0;
  dVar5 = (double)FLOAT_8043c7b4;
  *(float *)(param_9 + 0x20) = FLOAT_8043c778;
  fVar2 = FLOAT_8043c7b8;
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x28) = fVar2;
  for (iVar4 = 0; iVar4 < *(char *)(param_9 + 0x13); iVar4 = iVar4 + 1) {
    param_11 = (float *)(*(int *)(param_9 + 0x54) + iVar3);
    *(undefined2 *)(param_11 + 6) = 0xffff;
    *(short *)((int)param_11 + 0x1a) = (short)iVar4 + *(char *)(param_9 + 0x12) * 8;
    fVar2 = FLOAT_8043c780;
    fVar1 = FLOAT_8043c778;
    if (*(short *)((int)param_11 + 0x1a) < 0x1e) {
      param_11[5] = FLOAT_8043c780;
      param_11[4] = fVar2;
      param_11[3] = fVar2;
    }
    else if (*(short *)((int)param_11 + 0x1a) == 0x1e) {
      dVar5 = (double)FLOAT_8043c778;
      param_11[2] = FLOAT_8043c778;
      param_11[1] = fVar1;
      *param_11 = fVar1;
      param_11[5] = fVar2;
      param_11[4] = fVar2;
      param_11[3] = fVar2;
    }
    iVar3 = iVar3 + 0x20;
  }
  zz_01f91e8_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,iVar3,iVar4,param_14,param_15,param_16);
  return;
}



// ==== 801f91e8  zz_01f91e8_ ====

void zz_01f91e8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,int param_12,int param_13,int param_14,int param_15,int param_16
                )

{
  short sVar1;
  undefined2 uVar2;
  float fVar3;
  int iVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  float *pfVar9;
  int unaff_r24;
  int iVar10;
  int iVar11;
  short *psVar12;
  uint uVar13;
  int iVar14;
  double dVar15;
  double dVar16;
  undefined8 uVar17;
  char local_58;
  byte bStack_57;
  double local_50;
  double local_40;
  
  if (*(char *)(param_10 + 0x61) < '\0') {
    iVar11 = 0;
    psVar12 = (short *)0x803a28f8;
  }
  else {
    iVar6 = (int)*(char *)(param_10 + *(char *)(param_10 + 0x61) + 0x4c);
    param_14 = 0;
    param_12 = 0;
    iVar11 = *(int *)(param_10 + 0x40) + iVar6 * 0x6c;
    uVar8 = (uint)*(char *)(iVar11 + 0x29);
    param_15 = (int)uVar8 >> 0x1f;
    param_16 = param_15 + (uint)(0xf < uVar8);
    param_13 = (param_16 + param_15 + (uint)(0x17 < uVar8)) * 4;
    psVar12 = (short *)(&DAT_803a28ec + param_13);
    unaff_r24 = zz_01cce38_(*(int *)(param_10 + 0x40),iVar6,*(int *)(PTR_DAT_80433934 + 0x120),0);
  }
  *(short *)(param_9 + 0x70) = psVar12[1];
  iVar6 = 0;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  iVar14 = param_9;
  for (iVar10 = 0; iVar10 < *(char *)(param_9 + 0x13); iVar10 = iVar10 + 1) {
    pfVar9 = (float *)(*(int *)(param_9 + 0x54) + iVar6);
    if ((iVar11 == 0) || (0x1d < *(short *)((int)pfVar9 + 0x1a))) {
      if (*(short *)((int)pfVar9 + 0x1a) == 0x1e) {
        *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar10);
        iVar4 = DAT_803bb384;
        sVar1 = *psVar12;
        if ((int)*(short *)(pfVar9 + 6) != (int)sVar1) {
          iVar7 = *(int *)(iVar14 + 0xe0);
          *(short *)(pfVar9 + 6) = sVar1;
          param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                iVar4,iVar7,(int)sVar1,param_12,param_13,param_14,param_15,param_16)
          ;
        }
      }
    }
    else {
      iVar4 = (int)*(short *)(iVar11 + *(short *)((int)pfVar9 + 0x1a) * 2 + 0x30);
      if (-1 < iVar4) {
        uVar2 = *(undefined2 *)(*(int *)(param_10 + 0x40) + iVar4 * 0x20 + 0x870);
        *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar10);
        if (*(char *)(iVar11 + 0x29) < 9) {
          local_50 = (double)(CONCAT44(0x43300000,(int)*(short *)((int)pfVar9 + 0x1a)) ^ 0x80000000)
          ;
          iVar4 = *(char *)(iVar11 + 0x29) * 8;
          uVar13 = 0;
          *pfVar9 = *(float *)(&DAT_803a2900 + iVar4) * (float)(local_50 - DOUBLE_8043c7f8) +
                    *(float *)(&DAT_803a28fc + iVar4);
          fVar3 = FLOAT_8043c7bc;
          if (('\x03' < *(char *)(iVar11 + 0x29)) &&
             (fVar3 = FLOAT_8043c7c4, (*(ushort *)((int)pfVar9 + 0x1a) & 1) != 0)) {
            fVar3 = FLOAT_8043c7c0;
          }
          pfVar9[2] = fVar3;
          param_2 = DOUBLE_8043c7f8;
          param_3 = (double)FLOAT_8043c7cc;
          dVar16 = (double)FLOAT_8043c7c8;
          param_4 = (double)FLOAT_8043c7d0;
          pfVar9[3] = (float)(param_3 * (double)(float)((double)CONCAT44(0x43300000,
                                                                         8U - (int)*(char *)(iVar11 
                                                  + 0x29) ^ 0x80000000) - DOUBLE_8043c7f8) + dVar16)
          ;
          dVar15 = (double)pfVar9[3];
          if ((dVar15 <= param_4) && (param_4 = dVar15, dVar15 < dVar16)) {
            param_4 = dVar16;
          }
          pfVar9[3] = (float)param_4;
          fVar3 = FLOAT_8043c780;
          dVar15 = (double)pfVar9[3];
          pfVar9[4] = pfVar9[3];
          pfVar9[5] = fVar3;
        }
        else {
          uVar8 = (uint)*(short *)((int)pfVar9 + 0x1a);
          param_12 = (int)uVar8 >> 0x1f;
          param_15 = param_12 + (uint)(0x16 < uVar8);
          param_13 = param_12 + (uint)(7 < uVar8);
          uVar13 = param_13 + param_12 + (uint)(0xe < uVar8) + param_15;
          local_40 = (double)(CONCAT44(0x43300000,
                                       uVar8 - (int)(FLOAT_8043c7d8 *
                                                     (float)((double)CONCAT44(0x43300000,
                                                                              uVar13 ^ 0x80000000) -
                                                            DOUBLE_8043c7f8) + FLOAT_8043c7ac)) ^
                             0x80000000);
          fVar3 = FLOAT_8043c7e0;
          if ((uVar13 & 1) == 0) {
            fVar3 = FLOAT_8043c7dc;
          }
          fVar3 = FLOAT_8043c7d4 * (float)(local_40 - DOUBLE_8043c7f8) - fVar3;
          param_4 = (double)fVar3;
          param_3 = (double)FLOAT_8043c7e8;
          dVar15 = (double)FLOAT_8043c7e4;
          param_2 = (double)(float)((double)CONCAT44(0x43300000,uVar13 ^ 0x80000000) -
                                   DOUBLE_8043c7f8);
          *pfVar9 = fVar3;
          fVar3 = FLOAT_8043c780;
          dVar15 = -(double)(float)(param_3 * param_2 - dVar15);
          pfVar9[2] = (float)dVar15;
          pfVar9[5] = fVar3;
          pfVar9[4] = fVar3;
          pfVar9[3] = fVar3;
          param_14 = param_12;
        }
        local_58 = (char)((ushort)uVar2 >> 8);
        pfVar9[1] = FLOAT_8043c7ac;
        bStack_57 = (byte)uVar2;
        uVar8 = *(uint *)((&PTR_DAT_80350d0c)[local_58] + (uint)bStack_57 * 4);
        if ((int)*(short *)(pfVar9 + 6) != uVar8) {
          uVar17 = zz_0006fb4_(dVar15,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               DAT_803bb384,*(int *)(iVar14 + 0xe0),0x6e,param_12,param_13,param_14,
                               param_15,param_16);
          iVar4 = DAT_803bb334;
          iVar7 = *(int *)(iVar14 + 0xe0);
          param_12 = 0;
          *(short *)(pfVar9 + 6) = (short)uVar8;
          zz_000761c_(uVar17,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,iVar7,
                      (char *)(uVar8 & 0xff),0,param_13,param_14,param_15,param_16);
          zz_0007d8c_(*(int *)(iVar14 + 0xe0),7);
        }
        if (*(short *)((int)pfVar9 + 0x1a) < unaff_r24) {
          param_3 = (double)FLOAT_8043c7ec;
          cVar5 = -1 - (char)(int)(param_3 *
                                  (double)(float)((double)CONCAT44(0x43300000,uVar13 ^ 0x80000000) -
                                                 DOUBLE_8043c7f8));
          param_2 = DOUBLE_8043c7f8;
          fVar3 = FLOAT_8043c780;
        }
        else {
          cVar5 = '\0';
          fVar3 = FLOAT_8043c7f0;
        }
        *(char *)(*(int *)(iVar14 + 0xe0) + 0x1e) = cVar5;
        *(char *)(*(int *)(iVar14 + 0xe0) + 0x1d) = cVar5;
        *(char *)(*(int *)(iVar14 + 0xe0) + 0x1c) = cVar5;
        param_1 = zz_0007cac_((double)fVar3,*(int *)(iVar14 + 0xe0));
      }
    }
    iVar6 = iVar6 + 0x20;
    iVar14 = iVar14 + 4;
  }
  return;
}



// ==== 801f965c  FUN_801f965c ====

/* WARNING: Removing unreachable block (ram,0x801f979c) */

void FUN_801f965c(int param_1)

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
        if (*(short *)((int)pfVar6 + 0x1a) < 0x1e) {
          iVar2 = *(int *)(*(int *)(iVar8 + 0xe0) + 0xc);
          if (iVar2 == 0) {
            iVar2 = 0;
          }
          else {
            iVar2 = *(int *)(iVar2 + 0x10);
          }
          if (iVar2 != 0) {
            dVar11 = (double)FLOAT_8043c7ac;
            dVar12 = (double)FLOAT_8043c800;
            FUN_800455b0((double)FLOAT_8043c778,dVar11,dVar12,afStack_48,afStack_48);
            pfVar4 = afStack_48;
            iVar5 = (int)-*(short *)(param_1 + 0x70);
            uVar10 = zz_00457d4_('x',pfVar4,pfVar4,-*(short *)(param_1 + 0x70));
            if (iVar2 == 0) {
              pfVar4 = (float *)&DAT_8043c80c;
              gnt4___assert_bl(uVar10,dVar11,dVar12,in_f4,in_f5,in_f6,in_f7,in_f8,&DAT_8043c804,
                               0x495,&DAT_8043c80c,iVar5,in_r7,in_r8,in_r9,in_r10);
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
        else if (*(short *)(pfVar6 + 6) == 0x91) {
          zz_00097b4_(*(int *)(iVar8 + 0xe0),0x44);
        }
        else {
          zz_00097b4_(*(int *)(iVar8 + 0xe0),1);
        }
      }
      iVar9 = iVar9 + 0x20;
      iVar8 = iVar8 + 4;
    }
  }
  return;
}



// ==== 801f9840  FUN_801f9840 ====

void FUN_801f9840(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  double dVar9;
  
  fVar1 = FLOAT_8043c818;
  iVar4 = -0x7fc60000;
  dVar9 = (double)FLOAT_8043c818;
  piVar8 = &DAT_803a2944;
  iVar7 = 0;
  *(float *)(param_9 + 0x20) = FLOAT_8043c814;
  fVar2 = FLOAT_8043c81c;
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x28) = fVar2;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    iVar4 = piVar8[2];
    piVar3 = (int *)(*(int *)(param_9 + 0x54) + iVar7);
    *piVar3 = piVar8[1];
    piVar3[1] = iVar4;
    piVar3[2] = piVar8[3];
    iVar4 = *piVar8;
    dVar9 = (double)zz_0006fb4_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                DAT_803bb384,*(int *)(iVar6 + 0xe0),iVar4,param_12,param_13,param_14
                                ,param_15,param_16);
    piVar8 = piVar8 + 4;
    iVar7 = iVar7 + 0x20;
    iVar6 = iVar6 + 4;
  }
  zz_01f9900_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,iVar4,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801f9900  zz_01f9900_ ====

void zz_01f9900_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float *pfVar2;
  size_t sVar3;
  int iVar4;
  undefined4 extraout_r4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  char *pcVar8;
  undefined8 uVar9;
  char local_28 [8];
  undefined4 local_20;
  uint uStack_1c;
  
  pfVar2 = (float *)(*(char *)(param_10 + *(char *)(param_10 + 0x61) + 0x4c) + 1);
  pfVar5 = (float *)0x14;
  if ((int)pfVar2 < 0x14) {
    pfVar5 = pfVar2;
  }
  sprintf(local_28,&DAT_8043c820);
  sVar3 = strlen(local_28);
  *(short *)(param_9 + 0x1c) = (short)sVar3;
  pcVar8 = local_28;
  iVar7 = param_9;
  for (iVar6 = 0; iVar6 < *(short *)(param_9 + 0x1c); iVar6 = iVar6 + 1) {
    iVar4 = (int)*pcVar8;
    fVar1 = FLOAT_8043c778;
    if ((0x2f < iVar4) && (iVar4 < 0x3a)) {
      uStack_1c = iVar4 - 0x30U ^ 0x80000000;
      local_20 = 0x43300000;
      fVar1 = (float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8043c7f8);
    }
    uVar9 = zz_00086b8_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        DAT_803bb384,*(int *)(iVar7 + 0xe8),pfVar5,param_12,param_13,param_14,
                        param_15,param_16);
    zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar7 + 0xe8)
                ,extraout_r4,pfVar5,param_12,param_13,param_14,param_15,param_16);
    pcVar8 = pcVar8 + 1;
    iVar7 = iVar7 + 4;
  }
  return;
}



// ==== 801f99f0  FUN_801f99f0 ====

void FUN_801f99f0(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
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
  float afStack_50 [15];
  
  dVar6 = (double)*(float *)(param_1 + 0x24);
  dVar7 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar6,dVar7,(float *)(param_1 + 0x114));
  iVar4 = 0;
  iVar3 = param_1;
  for (iVar2 = 0; iVar2 < (int)*(char *)(param_1 + 0x13) + (int)*(short *)(param_1 + 0x1c) + -2;
      iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
    uVar5 = zz_00455fc_((float *)(param_1 + 0x114),afStack_50,pfVar1);
    zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_50,
                (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
    iVar4 = iVar4 + 0x20;
    iVar3 = iVar3 + 4;
  }
  if (*(char *)(param_2 + 0x61) < '\0') {
    sprintf(&DAT_803d5eb8,&DAT_802b4458);
  }
  else {
    strcpy(&DAT_803d5eb8,
           (char *)(*(int *)(param_2 + 0x40) +
                   *(char *)(param_2 + *(char *)(param_2 + 0x61) + 0x4c) * 0x6c));
  }
  local_5c = FLOAT_8043c824;
  local_58 = FLOAT_8043c828;
  local_54 = FLOAT_8043c7ac;
  local_60 = FLOAT_8043c780;
  local_64 = FLOAT_8043c780;
  local_68 = FLOAT_8043c780;
  FUN_801c53dc((double)FLOAT_8043c780,(double)FLOAT_8043c82c,(double)FLOAT_8043c7ec,
               (float *)(param_1 + 0x114),&local_5c,&local_68,3,0x1e,(short *)&DAT_803d5eb8);
  return;
}



// ==== 801f9b34  FUN_801f9b34 ====

void FUN_801f9b34(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 *puVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  
  fVar1 = FLOAT_8043c834;
  iVar6 = -0x7fc40000;
  dVar10 = (double)FLOAT_8043c834;
  iVar8 = 0;
  *(float *)(param_9 + 0x20) = FLOAT_8043c830;
  fVar2 = FLOAT_8043c838;
  *(float *)(param_9 + 0x24) = fVar1;
  *(float *)(param_9 + 0x28) = fVar2;
  *(undefined2 *)(param_9 + 0x74) = 0x9f4;
  iVar9 = param_9;
  for (uVar7 = 0; (int)uVar7 < (int)*(char *)(param_9 + 0x13); uVar7 = uVar7 + 1) {
    uVar4 = (-uVar7 | uVar7) >> 0x1b & 0x10;
    puVar5 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar8);
    uVar3 = *(undefined4 *)((int)&DAT_803a298c + uVar4);
    *puVar5 = *(undefined4 *)((int)&DAT_803a2988 + uVar4);
    puVar5[1] = uVar3;
    puVar5[2] = *(undefined4 *)((int)&DAT_803a2990 + uVar4);
    iVar6 = *(int *)((int)&DAT_803a2984 + uVar4);
    dVar10 = (double)zz_0006fb4_(dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_803bb384,*(int *)(iVar9 + 0xe0),iVar6,param_12,param_13,
                                 param_14,param_15,param_16);
    iVar8 = iVar8 + 0x20;
    iVar9 = iVar9 + 4;
  }
  FUN_801f9c08(dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,iVar6
               ,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801f9c08  FUN_801f9c08 ====

/* WARNING: Removing unreachable block (ram,0x801f9d68) */
/* WARNING: Removing unreachable block (ram,0x801f9d60) */
/* WARNING: Removing unreachable block (ram,0x801f9d58) */
/* WARNING: Removing unreachable block (ram,0x801f9c28) */
/* WARNING: Removing unreachable block (ram,0x801f9c20) */
/* WARNING: Removing unreachable block (ram,0x801f9c18) */

void FUN_801f9c08(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  int iVar2;
  size_t sVar3;
  int iVar4;
  undefined4 extraout_r4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  char *pcVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  char local_68 [8];
  undefined4 local_60;
  uint uStack_5c;
  
  iVar2 = 999999;
  iVar5 = *(int *)(*(int *)(param_10 + 0x40) +
                   *(char *)(param_10 + *(char *)(param_10 + 0x61) + 0x4c) * 0x6c + 0x2c);
  if (iVar5 < 999999) {
    iVar2 = iVar5;
  }
  sprintf(local_68,&DAT_8043c820,iVar2);
  sVar3 = strlen(local_68);
  *(short *)(param_9 + 0x1c) = (short)sVar3;
  dVar11 = (double)FLOAT_8043c83c;
  pcVar9 = local_68;
  dVar13 = (double)FLOAT_8043c7ac;
  iVar8 = 1;
  iVar2 = param_9;
  dVar12 = DOUBLE_8043c7f8;
  for (iVar5 = 0; iVar7 = (int)*(short *)(param_9 + 0x1c), iVar5 < iVar7; iVar5 = iVar5 + 1) {
    pfVar6 = *(float **)(param_9 + 0x54);
    iVar4 = (int)*pcVar9;
    fVar1 = FLOAT_8043c778;
    if ((0x2f < iVar4) && (iVar4 < 0x3a)) {
      fVar1 = (float)((double)CONCAT44(0x43300000,iVar4 - 0x30U ^ 0x80000000) - DOUBLE_8043c7f8);
    }
    local_60 = 0x43300000;
    uStack_5c = iVar8 - iVar7 ^ 0x80000000;
    pfVar6[(iVar5 + 1) * 8] =
         (float)((double)(float)(dVar11 * (double)(float)((double)CONCAT44(0x43300000,uStack_5c) -
                                                         dVar12)) * dVar13);
    uVar10 = zz_00086b8_((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         DAT_803bb384,*(int *)(iVar2 + 0xe4),pfVar6,iVar7,param_13,param_14,param_15
                         ,param_16);
    zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar2 + 0xe4),extraout_r4,pfVar6,iVar7,param_13,param_14,param_15,param_16)
    ;
    pcVar9 = pcVar9 + 1;
    iVar8 = iVar8 + 2;
    iVar2 = iVar2 + 4;
  }
  return;
}



// ==== 801f9d84  FUN_801f9d84 ====

void FUN_801f9d84(int param_1)

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
  
  dVar7 = (double)*(float *)(param_1 + 0x24);
  dVar8 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar7,dVar8,(float *)(param_1 + 0x114));
  iVar2 = (int)*(short *)(param_1 + 0x74);
  zz_00457d4_('z',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x74));
  iVar3 = (int)*(char *)(param_1 + 0x13) + (int)*(short *)(param_1 + 0x1c) + -7;
  iVar5 = iVar3 * 0x20;
  iVar4 = param_1 + iVar3 * 4;
  for (; -1 < iVar3; iVar3 = iVar3 + -1) {
    pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
    uVar6 = zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar1);
    zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),afStack_48,
                (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
    zz_00097b4_(*(int *)(iVar4 + 0xe0),0x44);
    iVar5 = iVar5 + -0x20;
    iVar4 = iVar4 + -4;
  }
  return;
}



// ==== 801f9e50  FUN_801f9e50 ====

void FUN_801f9e50(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_8043c840;
  fVar1 = FLOAT_8043c778;
  dVar3 = (double)FLOAT_8043c840;
  *(undefined2 *)(param_9 + 0x1c) = 0x1f;
  *(undefined2 *)(param_9 + 0x1e) = 0;
  *(float *)(param_9 + 0x20) = fVar1;
  fVar1 = FLOAT_8043c844;
  *(float *)(param_9 + 0x24) = fVar2;
  *(float *)(param_9 + 0x28) = fVar1;
  zz_0006fb4_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,
              *(int *)(param_9 + 0xe0),6,param_12,param_13,param_14,param_15,param_16);
  FUN_801f9ed0(param_9,param_10);
  return;
}



// ==== 801f9ed0  FUN_801f9ed0 ====

void FUN_801f9ed0(int param_1,int param_2)

{
  if (((*(byte *)(param_2 + 0x3e) | *(byte *)(param_2 + 0x3f)) & 4) != 0) {
    if ('\x01' < *(char *)(param_2 + 0x60)) {
      if ((*(byte *)(param_2 + 0x3e) & 4) == 0) {
        if ((*(byte *)(param_2 + 0x3f) & 4) != 0) {
          *(undefined2 *)(param_1 + 0x1e) = 2;
        }
      }
      else {
        *(undefined2 *)(param_1 + 0x1e) = 0x20;
      }
      *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
      return;
    }
  }
  *(undefined2 *)(param_1 + 0x1c) = 0x1f;
  *(undefined2 *)(param_1 + 0x1e) = 0;
  return;
}



// ==== 801f9f3c  FUN_801f9f3c ====

void FUN_801f9f3c(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined8 uVar1;
  double dVar2;
  double dVar3;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  if ((*(ushort *)(param_1 + 0x1c) & *(ushort *)(param_1 + 0x1e)) != 0) {
    dVar2 = (double)*(float *)(param_1 + 0x24);
    dVar3 = (double)*(float *)(param_1 + 0x28);
    uVar1 = gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar2,dVar3,
                               (float *)(param_1 + 0x114));
    zz_00076d0_(uVar1,dVar2,dVar3,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
                (float *)(param_1 + 0x114),param_3,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
  }
  return;
}



// ==== 801f9fac  zz_01f9fac_ ====

void zz_01f9fac_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = param_2;
    puVar1[0x10] = 100;
    *(code **)(puVar1 + 0xc) = FUN_801fa0ac;
    *(code **)(puVar1 + 0x10c) = FUN_801fac4c;
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



// ==== 801fa0ac  FUN_801fa0ac ====

void FUN_801fa0ac(int param_1)

{
  undefined4 uVar1;
  
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  (*(code *)(&PTR_FUN_803a2aa8)[*(char *)(param_1 + 0x18)])(param_1);
  uVar1 = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x58) = uVar1;
  return;
}



// ==== 801fa144  FUN_801fa144 ====

void FUN_801fa144(int param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  undefined *puVar5;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  puVar5 = &DAT_803a29a8;
  *(undefined1 *)(param_1 + 0x18) = 1;
  iVar7 = *(int *)(param_1 + 0x90);
  iVar6 = (int)*(char *)(param_1 + 0x11);
  *(undefined1 *)(param_1 + 0x84) = 0x1e;
  iVar1 = iVar6 * 0x20;
  *(code **)(param_1 + 0x100) = FUN_80047c38;
  zz_0089100_(param_1,0,1);
  *(char *)(param_1 + 0x89) = (char)*(undefined2 *)(&DAT_803a29aa + iVar1);
  *(undefined2 *)(param_1 + 0x1c4) = *(undefined2 *)(&DAT_803a29ae + iVar1);
  *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x1c4);
  *(undefined2 *)(param_1 + 0x1c8) = *(undefined2 *)(param_1 + 0x1c4);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar7 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
             (float *)(iVar1 + -0x7fc5d644),(float *)(param_1 + 0x20));
  *(short *)(param_1 + 0x72) = *(short *)(iVar7 + 0x72) + *(short *)(&DAT_803a29b0 + iVar1);
  uVar4 = zz_00055fc_();
  fVar2 = FLOAT_8043c850;
  dVar11 = (double)(float)((double)CONCAT44(0x43300000,uVar4 & 0x1f) - DOUBLE_8043c860);
  *(float *)(param_1 + 0x150) =
       *(float *)(&DAT_803a29b8 + iVar1) *
       ((FLOAT_8043c848 + (float)(dVar11 - (double)FLOAT_8043c84c)) / FLOAT_8043c848);
  *(float *)(param_1 + 0x154) = fVar2 * *(float *)(param_1 + 0x150);
  uVar4 = zz_00055fc_();
  dVar10 = (double)FLOAT_8043c848;
  dVar9 = (double)(float)(dVar10 + (double)((float)((double)CONCAT44(0x43300000,uVar4 & 0x1f) -
                                                   DOUBLE_8043c860) - FLOAT_8043c84c));
  dVar8 = (double)(float)(dVar9 / dVar10);
  *(short *)(param_1 + 0x158) =
       (short)(int)((double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(short *)(&DAT_803a29b2 + iVar1) ^
                                                     0x80000000) - DOUBLE_8043c868) * dVar8);
  iVar7 = zz_0006f98_(iVar7);
  zz_0006fb4_(dVar8,dVar9,dVar10,dVar11,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar7 + 0x600),
              *(int *)(param_1 + 0xe0),(int)*(short *)(&DAT_803a29a8 + iVar1),puVar5,iVar6,in_r8,
              in_r9,in_r10);
  fVar3 = FLOAT_8043c858;
  fVar2 = FLOAT_8043c854;
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + '1';
  *(float *)(param_1 + 0xb4) = fVar2;
  *(float *)(param_1 + 0xb8) = fVar3;
  return;
}



// ==== 801fa2f8  FUN_801fa2f8 ====

void FUN_801fa2f8(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  (*(code *)(&PTR_FUN_803a2ab8)[*(char *)(param_1 + 0x19)])(param_1,*(undefined4 *)(param_1 + 0x90))
  ;
  if ((*(short *)(param_1 + 0x1c6) < 1) || (*(char *)(param_1 + 0x1d9) != '\0')) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else if (((double)FLOAT_8043c870 <= (double)*(float *)(param_1 + 0x48)) ||
          (dVar3 = FUN_8003d964(-(double)*(float *)(param_1 + 0x48),param_1,
                                (float *)(param_1 + 0x20)), fVar1 = FLOAT_8043c870,
          dVar3 <= (double)*(float *)(param_1 + 0x24))) {
    iVar2 = zz_0083714_(param_1);
    if (iVar2 != 0) {
      *(undefined1 *)(param_1 + 0x18) = 2;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(float *)(param_1 + 0x24) = (float)dVar3;
    *(float *)(param_1 + 0x48) = fVar1;
  }
  return;
}



// ==== 801fa3c4  FUN_801fa3c4 ====

void FUN_801fa3c4(int param_1)

{
  char cVar1;
  double dVar2;
  float fVar3;
  short sVar5;
  int iVar4;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  iVar4 = *(char *)(param_1 + 0x11) * 0x20;
  if (cVar1 == '\x01') {
LAB_801fa4b0:
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    sVar5 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar5;
    dVar2 = DOUBLE_8043c868;
    if (0 < sVar5) goto LAB_801fa5e4;
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0x3c;
    *(float *)(param_1 + 0x4c) =
         (*(float *)(param_1 + 0x150) - *(float *)(param_1 + 0x44)) /
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c) ^ 0x80000000) - dVar2);
    *(float *)(param_1 + 0x50) =
         -*(float *)(param_1 + 0x48) /
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c) ^ 0x80000000) - dVar2);
    iVar4 = zz_008ac80_(param_1,(int)*(short *)(&DAT_803a29ac + iVar4));
    if (iVar4 == 0) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
      *(undefined1 *)(param_1 + 0x82) = 0;
      goto LAB_801fa5e4;
    }
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') goto LAB_801fa5e4;
      *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 0x3c;
      *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(&DAT_803a29b4 + iVar4);
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x11c);
      *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 300);
      *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x13c);
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      if (*(char *)(param_1 + 0x11) < '\x04') {
        *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) + FLOAT_8043c874;
      }
      else {
        *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) - FLOAT_8043c874;
      }
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      zz_00f061c_((double)FLOAT_8043c878,param_1,0x11c);
      goto LAB_801fa4b0;
    }
    if ('\x02' < cVar1) goto LAB_801fa5e4;
  }
  zz_01faca8_(param_1);
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x4c);
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + *(float *)(param_1 + 0x50);
  sVar5 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar5;
  fVar3 = FLOAT_8043c870;
  if (sVar5 < 1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_1 + 0x150);
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x50) = fVar3;
  }
LAB_801fa5e4:
  if (*(float *)(param_1 + 0xb4) < *(float *)(param_1 + 0xb8)) {
    *(float *)(param_1 + 0xb4) =
         FLOAT_8043c87c * *(float *)(param_1 + 0xb4) + FLOAT_8043c880 * *(float *)(param_1 + 0xb8);
  }
  return;
}



// ==== 801fa620  FUN_801fa620 ====

void FUN_801fa620(int param_1,char *param_2)

{
  char cVar1;
  int iVar2;
  short sVar3;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_1 + 0x1a) = 3;
    *(undefined2 *)(param_1 + 0x1c) = 0x78;
    *(undefined2 *)(param_1 + 0x1e) = 0x6000;
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined2 *)(param_1 + 0x1c) = 0x78;
      }
      else if (cVar1 < '\0') {
        return;
      }
      zz_01faca8_(param_1);
      iVar2 = zz_006c060_(param_2,(float)(param_1 + 0x20));
      if ((iVar2 != 0) && (PTR_DAT_80433934[0x1f] == '\0')) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
        *(undefined1 *)(param_1 + 0x1a) = 0;
        *(int *)(param_1 + 200) = iVar2;
        *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(iVar2 + 0x20);
        return;
      }
      sVar3 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar3;
      if (0 < sVar3) {
        return;
      }
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  iVar2 = zz_01faab8_(param_1,*(short *)(param_1 + 0x158),*(short *)(param_1 + 0x1e));
  if (iVar2 == 0) {
    *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) - *(short *)(param_1 + 0x158);
  }
  else {
    *(undefined1 *)(param_1 + 0x1a) = 0;
  }
  return;
}



// ==== 801fa754  FUN_801fa754 ====

/* WARNING: Removing unreachable block (ram,0x801faa90) */
/* WARNING: Removing unreachable block (ram,0x801fa764) */

void FUN_801fa754(int param_1)

{
  char cVar1;
  float fVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  float local_64 [2];
  float local_5c;
  float local_58;
  float local_54;
  undefined4 local_50;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  longlong local_38;
  undefined4 local_30;
  uint uStack_2c;
  longlong local_28;
  
  iVar6 = *(int *)(param_1 + 0xcc);
  iVar5 = *(int *)(param_1 + 200);
  if (((iVar6 == 0) || (PTR_DAT_80433934[0x1f] != '\0')) || ('\x01' < *(char *)(iVar6 + 0x18))) {
    *(undefined1 *)(param_1 + 0x19) = 1;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    return;
  }
  local_58 = *(float *)(iVar5 + 100);
  local_54 = *(float *)(iVar5 + 0x68);
  local_50 = *(undefined4 *)(iVar5 + 0x6c);
  gnt4_PSVECSubtract_bl(&local_58,(float *)(param_1 + 0x20),local_64);
  iVar5 = FUN_800452a0((double)local_64[0],(double)local_5c);
  sVar3 = (short)iVar5 - *(short *)(param_1 + 0x72);
  gnt4_PSVECSquareMag_bl(local_64);
  dVar8 = (double)(local_64[0] * local_64[0] + local_5c * local_5c);
  if ((double)FLOAT_8043c870 < dVar8) {
    dVar7 = 1.0 / SQRT(dVar8);
    dVar7 = DOUBLE_8043c888 * dVar7 * -(dVar8 * dVar7 * dVar7 - DOUBLE_8043c890);
    dVar7 = DOUBLE_8043c888 * dVar7 * -(dVar8 * dVar7 * dVar7 - DOUBLE_8043c890);
    dVar8 = (double)(float)(dVar8 * DOUBLE_8043c888 * dVar7 *
                                    -(dVar8 * dVar7 * dVar7 - DOUBLE_8043c890));
  }
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    if (dVar8 <= (double)FLOAT_8043c898) {
      *(undefined1 *)(param_1 + 0x1a) = 3;
    }
    else {
      iVar5 = zz_01faab8_(param_1,*(short *)(param_1 + 0x158),sVar3);
      if (iVar5 == 0) {
        *(undefined1 *)(param_1 + 0x1a) = 4;
        fVar2 = FLOAT_8043c870;
        *(undefined2 *)(param_1 + 0x1c) = 0x3c;
        *(float *)(param_1 + 0x48) = fVar2;
      }
      else {
        *(float *)(param_1 + 0x48) =
             (local_54 - *(float *)(param_1 + 0x24)) /
             ((float)(dVar8 - (double)FLOAT_8043c89c) / *(float *)(param_1 + 0x44));
      }
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      fVar2 = FLOAT_8043c870;
      *(undefined2 *)(param_1 + 0x1c) = 0x78;
      *(float *)(param_1 + 0x48) = fVar2;
    }
    else if (cVar1 < '\0') goto LAB_801fa9d4;
    iVar4 = zz_01faab8_(param_1,*(short *)(param_1 + 0x158),sVar3);
    if (iVar4 != 0) {
      *(short *)(param_1 + 0x72) = (short)iVar5;
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    }
    sVar3 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar3;
    if (sVar3 < 1) {
      *(undefined1 *)(param_1 + 0x1a) = 4;
      *(undefined2 *)(param_1 + 0x1c) = 0x3c;
    }
  }
  else {
    if (cVar1 != '\x04') {
      if ('\x03' < cVar1) goto LAB_801fa9d4;
      zz_008296c_(param_1,0x7f);
      fVar2 = FLOAT_8043c850;
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 0x78;
      *(float *)(param_1 + 0x48) = fVar2 * *(float *)(param_1 + 0x44);
    }
    sVar3 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar3;
    if (sVar3 < 1) {
      *(undefined1 *)(param_1 + 0x1a) = 0;
    }
  }
LAB_801fa9d4:
  zz_01faca8_(param_1);
  iVar5 = FUN_800452a0(-(double)*(float *)(param_1 + 0x48),(double)*(float *)(param_1 + 0x44));
  fVar2 = FLOAT_8043c87c;
  dVar8 = DOUBLE_8043c868;
  uStack_44 = (int)(short)iVar5 ^ 0x80000000;
  uStack_3c = (int)*(short *)(param_1 + 0x70) ^ 0x80000000;
  local_48 = 0x43300000;
  local_40 = 0x43300000;
  local_30 = 0x43300000;
  iVar5 = (int)(FLOAT_8043c8a0 * (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_8043c868) +
               FLOAT_8043c874 * (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_8043c868));
  local_38 = (longlong)iVar5;
  *(short *)(param_1 + 0x70) = (short)iVar5;
  uStack_2c = (int)*(short *)(param_1 + 0x74) ^ 0x80000000;
  iVar5 = (int)((float)((double)CONCAT44(0x43300000,uStack_2c) - dVar8) * fVar2);
  local_28 = (longlong)iVar5;
  *(short *)(param_1 + 0x74) = (short)iVar5;
  if (*(char *)(iVar6 + 0x83) == '\0') {
    zz_006d228_(param_1,iVar6,0);
  }
  return;
}



// ==== 801faab8  zz_01faab8_ ====

undefined4 zz_01faab8_(int param_1,short param_2,short param_3)

{
  double dVar1;
  undefined4 uVar2;
  undefined8 local_18;
  undefined8 local_10;
  
  dVar1 = DOUBLE_8043c868;
  uVar2 = 0;
  if (param_3 < 0) {
    if ((int)param_3 < -(int)param_2) {
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) - param_2;
      local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x74)) ^ 0x80000000);
      *(short *)(param_1 + 0x74) =
           (short)(int)(FLOAT_8043c8a0 * (float)(local_10 - dVar1) + FLOAT_8043c8a8);
    }
    else {
      uVar2 = 1;
      *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + param_3;
    }
  }
  else if (param_2 < param_3) {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + param_2;
    local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x74)) ^ 0x80000000);
    *(short *)(param_1 + 0x74) =
         (short)(int)(FLOAT_8043c8a0 * (float)(local_18 - dVar1) + FLOAT_8043c8a4);
  }
  else {
    uVar2 = 1;
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + param_3;
  }
  return uVar2;
}



// ==== 801fabb4  FUN_801fabb4 ====

void FUN_801fabb4(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  *(undefined1 *)(param_1 + 0x18) = 3;
  FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
  *(char *)(iVar1 + 0x192) = *(char *)(iVar1 + 0x192) + -1;
  if (*(char *)(iVar1 + 0x192) < '\0') {
    *(undefined1 *)(iVar1 + 0x192) = 0;
  }
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_008aff0_(param_1);
  return;
}



// ==== 801fac2c  FUN_801fac2c ====

void FUN_801fac2c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801fac4c  FUN_801fac4c ====

void FUN_801fac4c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801faca8  zz_01faca8_ ====

void zz_01faca8_(int param_1)

{
  double dVar1;
  
  dVar1 = zz_0045204_(*(short *)(param_1 + 0x72));
  *(float *)(param_1 + 0x20) =
       (float)((double)*(float *)(param_1 + 0x44) * dVar1 + (double)*(float *)(param_1 + 0x20));
  *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x48);
  dVar1 = zz_0045238_(*(short *)(param_1 + 0x72));
  *(float *)(param_1 + 0x28) =
       (float)((double)*(float *)(param_1 + 0x44) * dVar1 + (double)*(float *)(param_1 + 0x28));
  return;
}



// ==== 801fad10  FUN_801fad10 ====

void FUN_801fad10(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x10;
    *(code **)(puVar1 + 0xc) = FUN_801fae24;
    *(code **)(puVar1 + 0x10c) = FUN_801fb330;
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
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      puVar1[0x16a] = 0;
    }
    else {
      puVar1[0x16a] = 1;
    }
  }
  return;
}



