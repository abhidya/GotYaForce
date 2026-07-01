// ==== 80185044  zz_0185044_ ====

void zz_0185044_(int param_1)

{
  **(byte **)(param_1 + 0x164) =
       **(byte **)(param_1 + 0x164) | (byte)(1 << (*(byte *)(param_1 + 0x13) & 3));
  return;
}



// ==== 80185068  FUN_80185068 ====

/* WARNING: Removing unreachable block (ram,0x80185260) */
/* WARNING: Removing unreachable block (ram,0x80185258) */
/* WARNING: Removing unreachable block (ram,0x80185250) */
/* WARNING: Removing unreachable block (ram,0x80185088) */
/* WARNING: Removing unreachable block (ram,0x80185080) */
/* WARNING: Removing unreachable block (ram,0x80185078) */

void FUN_80185068(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float local_c8;
  float local_c4;
  float local_c0;
  float afStack_bc [2];
  float local_b4;
  float local_a4;
  float local_94;
  undefined4 local_88;
  uint uStack_84;
  undefined4 local_80;
  uint uStack_7c;
  
  uStack_84 = (int)*(short *)(param_1 + 0x1c) ^ 0x80000000;
  local_88 = 0x43300000;
  iVar1 = param_2 * 0x18 + *(char *)(param_1 + 0x13) * 0x30;
  dVar7 = (double)((float)((double)CONCAT44(0x43300000,uStack_84) - DOUBLE_8043af20) /
                  FLOAT_8043af30);
  pfVar3 = (float *)(*(int *)(param_1 + 0x90) + *(short *)(&DAT_8035c3b0 + iVar1 + 2) * 0x30 + 0x8d4
                    );
  dVar6 = (double)(float)((double)FLOAT_8043af34 - dVar7);
  gnt4_PSMTXCopy_bl(pfVar3,(float *)(param_1 + 0x114));
  gnt4_PSMTXMultVec_bl(pfVar3,(float *)(&DAT_8035c3b0 + iVar1 + 4),&local_c8);
  zz_0046588_(dVar7,(float *)(param_1 + 0x20),&local_c8,(float *)(param_1 + 0x20));
  local_80 = 0x43300000;
  uStack_7c = (int)*(short *)(&DAT_8035c3b0 + iVar1 + 0x10) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_8043af14 *
                              (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_8043af20)),
                      afStack_bc,0x78);
  gnt4_PSMTXConcat_bl(pfVar3,afStack_bc,afStack_bc);
  dVar5 = (double)local_a4;
  local_c8 = local_b4;
  local_c0 = local_94;
  local_c4 = FLOAT_8043af1c;
  dVar4 = gnt4_PSVECMag_bl(&local_c8);
  iVar1 = FUN_800452a0(-dVar5,dVar4);
  iVar2 = FUN_800452a0((double)local_c8,(double)local_c0);
  dVar5 = DOUBLE_8043af20;
  dVar4 = (double)CONCAT44(0x43300000,(int)(short)iVar2 ^ 0x80000000) - DOUBLE_8043af20;
  *(short *)(param_1 + 0x70) =
       (short)(int)(dVar7 * (double)(float)((double)CONCAT44(0x43300000,
                                                             (int)*(short *)(param_1 + 0x70) ^
                                                             0x80000000) - DOUBLE_8043af20) +
                   (double)(float)(dVar6 * (double)(float)((double)CONCAT44(0x43300000,
                                                                            (int)(short)iVar1 ^
                                                                            0x80000000) -
                                                          DOUBLE_8043af20)));
  *(short *)(param_1 + 0x72) =
       (short)(int)(dVar7 * (double)(float)((double)CONCAT44(0x43300000,
                                                             (int)*(short *)(param_1 + 0x72) ^
                                                             0x80000000) - dVar5) +
                   (double)(float)(dVar6 * (double)(float)dVar4));
  return;
}



// ==== 80185284  zz_0185284_ ====

void zz_0185284_(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_00055fc_();
  uVar1 = uVar1 & 0xf;
  if (uVar1 == (int)*(char *)(param_1 + 0x1a)) {
    uVar1 = uVar1 + 1 & 0xf;
  }
  *(char *)(param_1 + 0x1a) = (char)uVar1;
  *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x28);
  return;
}



// ==== 80185300  FUN_80185300 ====

/* WARNING: Removing unreachable block (ram,0x80185448) */
/* WARNING: Removing unreachable block (ram,0x80185310) */

void FUN_80185300(double param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float local_98;
  float local_94;
  float local_90;
  float afStack_8c [12];
  float afStack_5c [3];
  undefined4 local_50;
  undefined4 local_40;
  undefined4 local_30;
  undefined4 local_28;
  uint uStack_24;
  
  iVar3 = *(int *)(param_2 + 0xcc);
  if ((iVar3 != 0) && (iVar2 = *(int *)(param_2 + 200), iVar2 != 0)) {
    iVar1 = *(char *)(param_2 + 0x1a) * 8;
    gnt4_PSMTXRotRad_bl((double)*(float *)(&DAT_8035c6f0 + iVar1),afStack_5c,0x78);
    gnt4_PSMTXRotRad_bl((double)*(float *)(&DAT_8035c6f4 + iVar1),afStack_8c,0x79);
    gnt4_PSMTXConcat_bl(afStack_8c,afStack_5c,afStack_5c);
    local_50 = *(undefined4 *)(iVar2 + 100);
    local_40 = *(undefined4 *)(iVar2 + 0x68);
    local_30 = *(undefined4 *)(iVar2 + 0x6c);
    local_98 = FLOAT_8043af1c;
    local_94 = FLOAT_8043af1c;
    if ((*(char *)(iVar3 + 0x83) == '\0') && (*(int *)(iVar3 + 0x4b0) != 0)) {
      local_90 = FLOAT_8043af38 * *(float *)(*(int *)(iVar3 + 0x4b0) + 0x44);
    }
    else {
      local_90 = FLOAT_8043af3c;
    }
    local_90 = (float)((double)(local_90 * *(float *)(iVar3 + 0xb4)) + param_1);
    gnt4_PSMTXMultVec_bl(afStack_5c,&local_98,(float *)(param_2 + 0x158));
  }
  local_28 = 0x43300000;
  uStack_24 = (int)*(short *)(param_2 + 0x1c) ^ 0x80000000;
  zz_0046588_((double)((float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_8043af20) /
                      FLOAT_8043af30),(float *)(param_2 + 0x14c),(float *)(param_2 + 0x158),
              (float *)(param_2 + 0x20));
  return;
}



// ==== 80185470  FUN_80185470 ====

void FUN_80185470(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 8018547c  FUN_8018547c ====

void FUN_8018547c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8018549c  FUN_8018549c ====

void FUN_8018549c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801855f4  FUN_801855f4 ====

void FUN_801855f4(int param_1)

{
  zz_00c74ec_(param_1,0x10);
  return;
}



// ==== 80185618  FUN_80185618 ====

void FUN_80185618(int param_1)

{
  float fVar1;
  double dVar2;
  
  *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 1;
  *(undefined1 *)(param_1 + 0x748) = 2;
  dVar2 = DOUBLE_8043af48;
  fVar1 = FLOAT_8043af40;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043af48) * FLOAT_8043af40);
    *(short *)(param_1 + 0x18e0) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x18e2) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) -
                             dVar2) * fVar1);
  }
  return;
}



// ==== 801856e8  FUN_801856e8 ====

void FUN_801856e8(int param_1)

{
  (*(code *)(&PTR_FUN_8035d120)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80185724  FUN_80185724 ====

void FUN_80185724(int param_1)

{
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8035d12c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80185784  FUN_80185784 ====

void FUN_80185784(int param_1)

{
  zz_00f2374_(param_1);
  return;
}



// ==== 801857a8  FUN_801857a8 ====

void FUN_801857a8(int param_1)

{
  zz_00f2764_(param_1);
  return;
}



// ==== 801857cc  FUN_801857cc ====

void FUN_801857cc(int param_1)

{
  zz_00f33f4_(param_1);
  return;
}



// ==== 801857f0  FUN_801857f0 ====

void FUN_801857f0(int param_1)

{
  zz_00f3738_(param_1);
  return;
}



// ==== 80185814  FUN_80185814 ====

void FUN_80185814(int param_1)

{
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  zz_00f41c4_(param_1);
  return;
}



// ==== 80185850  zz_0185850_ ====

void zz_0185850_(int param_1,undefined1 param_2,undefined1 param_3)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((sVar1 == 0x610) || (sVar1 == 0x61e)) || (sVar1 == 0x621)) || (sVar1 == 0x623)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x13] = param_3;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_80185980;
    *(code **)(puVar2 + 0x10c) = FUN_80185ec4;
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



// ==== 80185980  FUN_80185980 ====

void FUN_80185980(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8035d5dc)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801859d4  FUN_801859d4 ====

void FUN_801859d4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  int iVar8;
  double dVar9;
  undefined8 uVar10;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar8 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,(int)*(char *)(iVar8 + 0x3e4) + 0x10,1);
  *(undefined *)(param_9 + 0x84) = (&DAT_80435664)[*(char *)(param_9 + 0x11)];
  fVar2 = FLOAT_8043af54;
  fVar1 = FLOAT_8043af50;
  dVar9 = (double)FLOAT_8043af50;
  *(undefined *)(param_9 + 0x89) = (&DAT_80435660)[*(char *)(param_9 + 0x11)];
  iVar4 = *(char *)(param_9 + 0x11) * 0xc;
  puVar6 = (undefined4 *)(&DAT_8035d4fc + iVar4);
  uVar5 = *puVar6;
  uVar3 = *(undefined4 *)(&DAT_8035d500 + iVar4);
  *(undefined4 *)(param_9 + 100) = uVar5;
  *(undefined4 *)(param_9 + 0x68) = uVar3;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8035d504 + iVar4);
  iVar4 = *(char *)(param_9 + 0x11) * 6;
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_8035d520 + iVar4);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8035d524 + iVar4);
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0x144) = fVar2;
  *(undefined2 *)(param_9 + 0x14c) = 0;
  iVar7 = (int)*(char *)(*(char *)(param_9 + 0x13) * 3 + -0x7fca2b10 +
                        (int)*(char *)(param_9 + 0x11));
  iVar4 = zz_0006f98_(iVar8);
  uVar10 = zz_0007030_(dVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),iVar7,iVar4 + 0xc28,uVar5,
                       puVar6,in_r9,in_r10);
  iVar8 = iVar4 + 0xc28;
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),iVar7,iVar8,uVar5,puVar6,
                       in_r9,in_r10);
  zz_0007c54_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe4),extraout_r4,iVar7,iVar8,uVar5,puVar6,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043af58,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0185b68_(param_9);
  return;
}



// ==== 80185b68  zz_0185b68_ ====

void zz_0185b68_(int param_1)

{
  char cVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 0x90);
  if (((int)*(char *)(iVar5 + 0x6e8) & 1 << (int)*(char *)(param_1 + 0x11)) == 0) {
    *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) - FLOAT_8043af5c;
  }
  else {
    *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) + FLOAT_8043af5c;
    iVar2 = (int)*(char *)(iVar5 + 0x6e9);
    if (iVar2 < 3) {
      if (iVar2 == 0) {
        *(undefined4 *)(param_1 + 0x148) = 0;
        *(undefined2 *)(param_1 + 0x14c) = 0;
        iVar2 = *(char *)(param_1 + 0x11) * 6;
        *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(&DAT_8035d520 + iVar2);
        *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(&DAT_8035d524 + iVar2);
      }
      else if (-1 < iVar2) {
        piVar3 = (int *)(*(char *)(param_1 + 0x11) * 0x38 + -0x7fca2acc + iVar2 * 8);
        iVar4 = piVar3[1];
        iVar2 = *piVar3 - (int)*(short *)(param_1 + 0x14c);
        if (iVar4 < iVar2) {
          iVar2 = iVar4;
        }
        if (iVar2 < -iVar4) {
          iVar2 = -iVar4;
        }
        *(undefined4 *)(param_1 + 0x148) = 0;
        *(short *)(param_1 + 0x14c) = *(short *)(param_1 + 0x14c) + (short)iVar2;
        *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(param_1 + 0x14c);
      }
    }
    else if (iVar2 < 7) {
      piVar3 = (int *)(*(char *)(param_1 + 0x11) * 0x38 + -0x7fca2acc + iVar2 * 8);
      iVar4 = piVar3[1];
      iVar2 = *piVar3 - *(int *)(param_1 + 0x148);
      if (iVar4 < iVar2) {
        iVar2 = iVar4;
      }
      if (iVar2 < -iVar4) {
        iVar2 = -iVar4;
      }
      *(int *)(param_1 + 0x148) = *(int *)(param_1 + 0x148) + iVar2;
      *(undefined2 *)(param_1 + 0x14c) = 0;
      *(short *)(param_1 + 0x72) = (short)*(undefined4 *)(param_1 + 0x148);
    }
  }
  if (FLOAT_8043af50 < *(float *)(param_1 + 0x144)) {
    *(float *)(param_1 + 0x144) = FLOAT_8043af50;
  }
  if (*(float *)(param_1 + 0x144) < FLOAT_8043af54) {
    *(float *)(param_1 + 0x144) = FLOAT_8043af54;
  }
  cVar1 = *(char *)(param_1 + 0x11);
  if (cVar1 == '\x01') {
    if ((*(byte *)(iVar5 + 0x146) & 2) != 0) {
      *(byte *)(iVar5 + 0x146) = *(byte *)(iVar5 + 0x146) & 0xfd;
      *(undefined1 *)(param_1 + 0xaf) = 0;
      *(undefined2 *)(param_1 + 0x14e) = *(undefined2 *)(iVar5 + 0x148);
      zz_001ac80_(param_1,0x2c);
    }
    if ((*(byte *)(iVar5 + 0x146) & 0x20) != 0) {
      *(byte *)(iVar5 + 0x146) = *(byte *)(iVar5 + 0x146) & 0xdf;
      *(undefined1 *)(param_1 + 0xaf) = 0xff;
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      if ((*(byte *)(iVar5 + 0x146) & 1) != 0) {
        *(byte *)(iVar5 + 0x146) = *(byte *)(iVar5 + 0x146) & 0xfe;
        *(undefined1 *)(param_1 + 0xaf) = 0;
        *(undefined2 *)(param_1 + 0x14e) = *(undefined2 *)(iVar5 + 0x148);
        zz_001ac80_(param_1,0x2d);
      }
      if ((*(byte *)(iVar5 + 0x146) & 0x10) != 0) {
        *(byte *)(iVar5 + 0x146) = *(byte *)(iVar5 + 0x146) & 0xef;
        *(undefined1 *)(param_1 + 0xaf) = 0xff;
      }
    }
  }
  else if (cVar1 < '\x03') {
    if ((*(byte *)(iVar5 + 0x146) & 0xc) != 0) {
      if (*(char *)(param_1 + 0xaf) != '\0') {
        zz_001ac80_(param_1,0x2e);
        zz_001ac80_(param_1,0x2f);
      }
      *(byte *)(iVar5 + 0x146) = *(byte *)(iVar5 + 0x146) & 0xf3;
      *(undefined1 *)(param_1 + 0xaf) = 0;
      *(undefined2 *)(param_1 + 0x14e) = *(undefined2 *)(iVar5 + 0x148);
    }
    if ((*(byte *)(iVar5 + 0x146) & 0xc0) != 0) {
      *(byte *)(iVar5 + 0x146) = *(byte *)(iVar5 + 0x146) & 0x3f;
      *(undefined1 *)(param_1 + 0xaf) = 0xff;
    }
  }
  if (*(short *)(param_1 + 0x14e) != *(short *)(iVar5 + 0x148)) {
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
  }
  return;
}



// ==== 80185ea4  FUN_80185ea4 ====

void FUN_80185ea4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80185ec4  FUN_80185ec4 ====

void FUN_80185ec4(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  undefined8 uVar5;
  double dVar6;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [15];
  
  dVar4 = (double)*(float *)(param_1 + 0x144);
  if ((double)FLOAT_8043af54 < dVar4) {
    if (*(char *)(*(int *)(param_1 + 0x90) + 0xae) == '\0') {
      iVar3 = *(int *)(param_1 + 0xe0);
      uVar2 = 0x45;
    }
    else {
      iVar3 = *(int *)(param_1 + 0xe4);
      uVar2 = 0x44;
    }
    dVar6 = dVar4;
    gnt4_PSMTXScale_bl(dVar4,dVar4,dVar4,afStack_48);
    pfVar1 = afStack_48;
    uVar5 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar1,pfVar1);
    zz_00076d0_(uVar5,dVar4,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,iVar3,afStack_48,(undefined *)pfVar1
                ,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(iVar3,uVar2);
  }
  return;
}



// ==== 80185f6c  zz_0185f6c_ ====

void zz_0185f6c_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((((sVar1 == 0x600) || (sVar1 == 0x608)) || (sVar1 == 0x602)) ||
        ((sVar1 == 0x60a || (sVar1 == 0x60c)))) ||
       ((sVar1 == 0x60e || ((sVar1 == 0x616 || (sVar1 == 0x61c)))))) ||
      ((sVar1 == 0x615 || ((sVar1 == 0x629 || (sVar1 == 0x62a)))))) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_801860c4;
    *(code **)(puVar2 + 0x10c) = FUN_80186480;
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



// ==== 801860c4  FUN_801860c4 ====

void FUN_801860c4(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8035d88c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80186118  FUN_80186118 ====

void FUN_80186118(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 extraout_r4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  int iVar6;
  double dVar7;
  undefined8 uVar8;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar6 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  *(undefined *)(param_9 + 0x89) = (&DAT_8035d614)[*(char *)(param_9 + 0x11)];
  iVar3 = *(char *)(param_9 + 0x11) * 0xc;
  uVar4 = *(undefined4 *)(&DAT_8035d63c + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8035d638 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar4;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8035d640 + iVar3);
  iVar3 = *(char *)(param_9 + 0x11) * 6;
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_8035d7c4 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8035d7c8 + iVar3);
  if (*(short *)(param_9 + 0x70) != 0) {
    *(byte *)(param_9 + 0x84) = *(byte *)(param_9 + 0x84) | 2;
  }
  if (*(short *)(param_9 + 0x72) != 0) {
    *(byte *)(param_9 + 0x84) = *(byte *)(param_9 + 0x84) | 4;
  }
  if (*(short *)(param_9 + 0x74) != 0) {
    *(byte *)(param_9 + 0x84) = *(byte *)(param_9 + 0x84) | 8;
  }
  fVar2 = FLOAT_8043af64;
  fVar1 = FLOAT_8043af60;
  dVar7 = (double)FLOAT_8043af60;
  *(float *)(param_9 + 0x60) = FLOAT_8043af60;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0x144) = fVar2;
  iVar5 = (int)(char)(&DAT_8035d5f0)[*(char *)(param_9 + 0x11)];
  iVar3 = zz_0006f98_(iVar6);
  uVar8 = zz_0007030_(dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),iVar5,iVar3 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar6 = iVar3 + 0xc28;
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),iVar5,iVar6,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar5,iVar6,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043af68,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_01862d4_(param_9);
  return;
}



// ==== 801862d4  zz_01862d4_ ====

void zz_01862d4_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  switch(*(undefined1 *)(param_1 + 0x11)) {
  case 0:
  case 4:
  case 7:
  case 9:
  case 0xc:
  case 0xf:
  case 0x12:
  case 0x16:
  case 0x18:
  case 0x1a:
  case 0x1d:
    if (*(char *)(iVar1 + 0x6e8) == '\x01') {
      *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) + FLOAT_8043af6c;
    }
    else {
      *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) - FLOAT_8043af6c;
    }
    break;
  case 1:
  case 5:
  case 8:
  case 10:
  case 0xd:
  case 0x10:
  case 0x13:
  case 0x17:
  case 0x19:
  case 0x1e:
    if (*(char *)(iVar1 + 0x6e8) == '\x02') {
      *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) + FLOAT_8043af6c;
    }
    else {
      *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) - FLOAT_8043af6c;
    }
    break;
  case 2:
  case 0x14:
  case 0x1b:
  case 0x20:
    if (*(char *)(iVar1 + 0x6e8) < '\x02') {
      *(float *)(param_1 + 0x144) = FLOAT_8043af64;
    }
    else {
      *(float *)(param_1 + 0x144) = FLOAT_8043af60;
    }
    break;
  case 3:
  case 0x15:
    if (*(char *)(iVar1 + 0x6e8) < '\x02') {
      *(float *)(param_1 + 0x144) = FLOAT_8043af60;
    }
    else {
      *(float *)(param_1 + 0x144) = FLOAT_8043af64;
    }
    break;
  case 6:
  case 0xb:
  case 0xe:
  case 0x11:
    if (*(char *)(iVar1 + 0x6e8) < '\x02') {
      *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) - FLOAT_8043af6c;
    }
    else {
      *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) + FLOAT_8043af6c;
    }
    break;
  case 0x1c:
  case 0x1f:
    if (*(char *)(iVar1 + 0x6e8) < '\x02') {
      *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) + FLOAT_8043af70;
    }
    else {
      *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) - FLOAT_8043af70;
    }
  }
  if (FLOAT_8043af60 < *(float *)(param_1 + 0x144)) {
    *(float *)(param_1 + 0x144) = FLOAT_8043af60;
  }
  if (*(float *)(param_1 + 0x144) < FLOAT_8043af64) {
    *(float *)(param_1 + 0x144) = FLOAT_8043af64;
    return;
  }
  return;
}



// ==== 80186460  FUN_80186460 ====

void FUN_80186460(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80186480  FUN_80186480 ====

void FUN_80186480(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  undefined8 uVar5;
  double dVar6;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [15];
  
  dVar4 = (double)*(float *)(param_1 + 0x144);
  if ((double)FLOAT_8043af64 < dVar4) {
    if (*(char *)(*(int *)(param_1 + 0x90) + 0xae) == '\0') {
      iVar3 = *(int *)(param_1 + 0xe0);
      uVar2 = 0x25;
    }
    else {
      iVar3 = *(int *)(param_1 + 0xe4);
      uVar2 = 0x24;
    }
    dVar6 = dVar4;
    gnt4_PSMTXScale_bl(dVar4,dVar4,dVar4,afStack_48);
    pfVar1 = afStack_48;
    uVar5 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar1,pfVar1);
    zz_00076d0_(uVar5,dVar4,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,iVar3,afStack_48,(undefined *)pfVar1
                ,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(iVar3,uVar2);
  }
  return;
}



// ==== 80186528  zz_0186528_ ====

void zz_0186528_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((sVar1 == 0x612) || (sVar1 == 0x620)) || (sVar1 == 0x624)) || (sVar1 == 0x626)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_80186648;
    *(code **)(puVar2 + 0x10c) = FUN_801868bc;
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



// ==== 80186648  FUN_80186648 ====

void FUN_80186648(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8035d968)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8018669c  FUN_8018669c ====

void FUN_8018669c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar6 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_8043af78;
  *(undefined *)(param_9 + 0x84) = (&DAT_80435670)[*(char *)(param_9 + 0x11)];
  *(undefined *)(param_9 + 0x89) = (&DAT_8043566c)[*(char *)(param_9 + 0x11)];
  iVar3 = *(char *)(param_9 + 0x11) * 0xc;
  puVar4 = (undefined4 *)(&DAT_8035d920 + iVar3);
  uVar2 = *(undefined4 *)(&DAT_8035d924 + iVar3);
  *(undefined4 *)(param_9 + 100) = *puVar4;
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8035d928 + iVar3);
  iVar3 = *(char *)(param_9 + 0x11) * 6;
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_8035d950 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8035d954 + iVar3);
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0x144) = fVar1;
  iVar5 = (int)(char)(&DAT_80435668)[*(char *)(param_9 + 0x11)];
  iVar3 = zz_0006f98_(iVar6);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),iVar5,iVar3 + 0xc28,puVar4,
                      in_r8,in_r9,in_r10);
  iVar6 = iVar3 + 0xc28;
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),iVar5,iVar6,puVar4,in_r8,
                      in_r9,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar5,iVar6,puVar4,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043af7c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_0186810_(param_9);
  return;
}



// ==== 80186810  zz_0186810_ ====

void zz_0186810_(int param_1)

{
  float fVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  if ((*(byte *)(iVar2 + 0x6e8) & 1) == 0) {
    *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) - FLOAT_8043af80;
  }
  else {
    *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) + FLOAT_8043af80;
  }
  if (FLOAT_8043af78 < *(float *)(param_1 + 0x144)) {
    *(float *)(param_1 + 0x144) = FLOAT_8043af78;
  }
  if (*(float *)(param_1 + 0x144) < FLOAT_8043af84) {
    *(float *)(param_1 + 0x144) = FLOAT_8043af84;
  }
  fVar1 = FLOAT_8043af84;
  if ((*(byte *)(iVar2 + 0x144) & 1) == 0) {
    return;
  }
  *(byte *)(iVar2 + 0x144) = *(byte *)(iVar2 + 0x144) & 0xfe;
  *(float *)(param_1 + 0x144) = fVar1;
  return;
}



// ==== 8018689c  FUN_8018689c ====

void FUN_8018689c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801868bc  FUN_801868bc ====

void FUN_801868bc(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  uint uVar2;
  int iVar3;
  double dVar4;
  undefined8 uVar5;
  double dVar6;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [15];
  
  dVar4 = (double)*(float *)(param_1 + 0x144);
  if ((double)FLOAT_8043af84 < dVar4) {
    if (*(char *)(*(int *)(param_1 + 0x90) + 0xae) == '\0') {
      iVar3 = *(int *)(param_1 + 0xe0);
      uVar2 = 0x45;
    }
    else {
      iVar3 = *(int *)(param_1 + 0xe4);
      uVar2 = 0x44;
    }
    dVar6 = dVar4;
    gnt4_PSMTXScale_bl(dVar4,dVar4,dVar4,afStack_48);
    pfVar1 = afStack_48;
    uVar5 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar1,pfVar1);
    zz_00076d0_(uVar5,dVar4,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,iVar3,afStack_48,(undefined *)pfVar1
                ,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(iVar3,uVar2);
  }
  return;
}



// ==== 80186964  zz_0186964_ ====

void zz_0186964_(int param_1)

{
  char cVar1;
  int iVar2;
  ushort uVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  undefined4 *puVar12;
  short *psVar13;
  int unaff_r29;
  short *psVar14;
  int iVar15;
  ushort local_48 [2];
  undefined2 local_44 [2];
  undefined2 local_40 [2];
  ushort local_3c;
  undefined8 local_38;
  undefined8 local_30;
  
  DAT_80436358 = 0;
  DAT_8043635c = zz_00055fc_();
  if ((PTR_DAT_80433930[2] & 1) != 0) {
    unaff_r29 = 0;
  }
  if ((PTR_DAT_80433930[2] & 2) != 0) {
    unaff_r29 = 1;
  }
  if ((PTR_DAT_80433930[2] & 4) != 0) {
    unaff_r29 = 2;
  }
  if ((PTR_DAT_80433930[2] & 8) != 0) {
    unaff_r29 = 3;
  }
  if ((PTR_DAT_80433930[2] & 0x10) != 0) {
    unaff_r29 = 4;
  }
  if ((PTR_DAT_80433930[2] & 0x20) != 0) {
    unaff_r29 = 5;
  }
  psVar14 = (short *)(&PTR_DAT_8037f5d0)[param_1];
  iVar8 = 0;
  PTR_DAT_80433934[0x15da] = 0;
  iVar4 = 0;
  iVar6 = 0;
  PTR_DAT_80433934[0x15d9] = 0;
  PTR_DAT_80433934[0x105] = 0;
  iVar15 = 6;
  do {
    if (-1 < *(short *)(PTR_DAT_80433934 + iVar4 + 0x10)) {
      PTR_DAT_80433934[0x15da] = PTR_DAT_80433934[0x15da] + '\x01';
      iVar7 = (unaff_r29 - iVar8 | iVar8 - unaff_r29) >> 0x1f;
      iVar2 = 0x24 - iVar7;
      iVar11 = iVar8 + 0x15fe;
      iVar10 = iVar8 + 0x164c;
      PTR_DAT_80433934[0x15d9] = PTR_DAT_80433934[0x15d9] | (byte)(1 << iVar8);
      psVar13 = psVar14 + iVar7 * -6 + 6;
      PTR_DAT_80433934[0x105] = PTR_DAT_80433934[0x105] + '\x01';
      uVar9 = *(undefined4 *)(psVar13 + 2);
      puVar12 = (undefined4 *)(PTR_DAT_80433934 + iVar6 + 0x1604);
      *puVar12 = *(undefined4 *)psVar13;
      puVar12[1] = uVar9;
      puVar12[2] = *(undefined4 *)(psVar13 + 4);
      PTR_DAT_80433934[iVar11] = *(undefined1 *)((int)psVar14 + iVar2);
      PTR_DAT_80433934[iVar11] = PTR_DAT_80433934[iVar11] & 0xf8;
      PTR_DAT_80433934[iVar10] = *(undefined1 *)((int)psVar14 + iVar2);
      PTR_DAT_80433934[iVar10] = PTR_DAT_80433934[iVar10] & 3;
    }
    iVar4 = iVar4 + 2;
    iVar6 = iVar6 + 0xc;
    iVar8 = iVar8 + 1;
    iVar15 = iVar15 + -1;
  } while (iVar15 != 0);
  iVar4 = 0;
  PTR_DAT_80433934[0x141] = 0;
  psVar13 = psVar14;
  do {
    if (*psVar13 != -1) {
      iVar6 = *psVar13 * 0x14;
      iVar8 = 0;
      if (*(short *)(PTR_DAT_80433934 + 0x10) < 0) {
        iVar8 = 0;
      }
      else if (*(short *)(PTR_DAT_80433934 + 0x12) < 0) {
        iVar8 = 1;
      }
      else if (*(short *)(PTR_DAT_80433934 + 0x14) < 0) {
        iVar8 = 2;
      }
      else if (*(short *)(PTR_DAT_80433934 + 0x16) < 0) {
        iVar8 = 3;
      }
      else if (*(short *)(PTR_DAT_80433934 + 0x18) < 0) {
        iVar8 = 4;
      }
      else if (*(short *)(PTR_DAT_80433934 + 0x1a) < 0) {
        iVar8 = 5;
      }
      PTR_DAT_80433934[iVar8 + 0xcb] = 1;
      PTR_DAT_80433934[iVar8 + 0x20] = (&DAT_8037f8f0)[iVar6];
      PTR_DAT_80433934[iVar8 + 0x26] = 0;
      PTR_DAT_80433934[iVar8 + 0x32] = (&DAT_8037f8f1)[iVar6] & 0xf;
      if (((&DAT_8037f8f1)[iVar6] & 0xf0) != 0) {
        PTR_DAT_80433934[iVar8 + 0x26] = (char)((int)((byte)(&DAT_8037f8f1)[iVar6] & 0xf0) >> 4);
      }
      PTR_DAT_80433934[iVar8 + 0x15e6] = 0;
      PTR_DAT_80433934[iVar8 + 0x15e0] = 0;
      PTR_DAT_80433934[iVar8 + 0x15ec] = 0;
      PTR_DAT_80433934[iVar8 + 0x15f2] = 0;
      PTR_DAT_80433934[iVar8 + 0x15f8] = 0;
      iVar15 = (int)(char)(&DAT_8037f8f3)[iVar6];
      if (*(int *)(DAT_80436354 + 100) != 0) {
        iVar7 = iVar8 + 0x32;
        PTR_DAT_80433934[iVar7] = PTR_DAT_80433934[iVar7] + (char)*(int *)(DAT_80436354 + 100);
        if ('\x0e' < (char)PTR_DAT_80433934[iVar7]) {
          PTR_DAT_80433934[iVar7] = 0xf;
        }
        iVar15 = iVar15 + *(int *)(DAT_80436354 + 100);
        if (8 < iVar15) {
          iVar15 = 9;
        }
      }
      zz_018841c_(iVar8,(int)(char)(&DAT_8037f8f2)[iVar6],(char)iVar15);
      iVar7 = iVar8 + 0x15fe;
      iVar15 = iVar8 + 0x164c;
      PTR_DAT_80433934[0x15da] = PTR_DAT_80433934[0x15da] + '\x01';
      PTR_DAT_80433934[0x15d9] = PTR_DAT_80433934[0x15d9] | (byte)(1 << iVar8);
      PTR_DAT_80433934[0x141] = PTR_DAT_80433934[0x141] + '\x01';
      uVar9 = *(undefined4 *)(&DAT_8037f8f8 + iVar6);
      puVar12 = (undefined4 *)(PTR_DAT_80433934 + iVar8 * 0xc + 0x1604);
      *puVar12 = *(undefined4 *)(&DAT_8037f8f4 + iVar6);
      puVar12[1] = uVar9;
      puVar12[2] = *(undefined4 *)(&DAT_8037f8fc + iVar6);
      PTR_DAT_80433934[iVar7] = (&DAT_8037f900)[iVar6];
      PTR_DAT_80433934[iVar7] = PTR_DAT_80433934[iVar7] & 0xf8;
      PTR_DAT_80433934[iVar15] = (&DAT_8037f900)[iVar6];
      PTR_DAT_80433934[iVar15] = PTR_DAT_80433934[iVar15] & 3;
      if ((char)PTR_DAT_80433934[iVar8 + 0x20] < 0xe) {
        zz_018262c_((int)(char)PTR_DAT_80433934[iVar8 + 0x20]);
      }
    }
    iVar4 = iVar4 + 1;
    psVar13 = psVar13 + 1;
  } while (iVar4 < 5);
  if (psVar14[0x13] == 0) {
    PTR_DAT_80433934[0x15df] = 0;
    PTR_DAT_80433934[0x50] = 1;
    *(undefined4 *)(PTR_DAT_80433934 + 0x4c) = 59999;
    *(undefined4 *)(PTR_DAT_80433934 + 0x48) = 59999;
  }
  else {
    PTR_DAT_80433934[0x15df] = 1;
    iVar4 = psVar14[0x13] * 0x3c + 0x3b;
    *(int *)(PTR_DAT_80433934 + 0x4c) = iVar4;
    *(int *)(PTR_DAT_80433934 + 0x48) = iVar4;
  }
  iVar6 = 0;
  *(undefined4 *)(PTR_DAT_80433934 + 0x114) = 0;
  iVar4 = 0;
  while ((iVar6 < (char)PTR_DAT_80433934[unaff_r29 + 0x5a] &&
         (iVar8 = unaff_r29 * 0x348 + iVar4, *(short *)(PTR_DAT_80433934 + iVar8 + 0x1e8) != -1))) {
    local_40[0] = *(undefined2 *)(PTR_DAT_80433934 + iVar8 + 0x1e8);
    iVar8 = zz_0066168_((char *)local_40,(int)(char)PTR_DAT_80433934[iVar8 + 0x1ea]);
    iVar4 = iVar4 + 0x1c;
    iVar6 = iVar6 + 1;
    *(int *)(PTR_DAT_80433934 + 0x114) = *(int *)(PTR_DAT_80433934 + 0x114) + iVar8;
  }
  *(undefined4 *)(PTR_DAT_80433934 + 0x118) = *(undefined4 *)(PTR_DAT_80433934 + 0x114);
  *(undefined4 *)(PTR_DAT_80433934 + 0x11c) = *(undefined4 *)(PTR_DAT_80433934 + 0x114);
  DAT_803d4938 = (undefined2 *)(&PTR_DAT_8037c3d0)[param_1 * 4];
  DAT_803d493c = (undefined2 *)(&PTR_DAT_8037c3d4)[param_1 * 4];
  DAT_803d4940 = (undefined2 *)(&PTR_DAT_8037c3d8)[param_1 * 4];
  DAT_803d4944 = (undefined2 *)(&PTR_DAT_8037c3dc)[param_1 * 4];
  *(undefined4 *)(PTR_DAT_80433934 + 0x150) = 0;
  if (((psVar14[0x14] & 2U) != 0) || ((psVar14[0x14] & 0x40U) != 0)) {
    if (psVar14[4] != -1 ||
        (psVar14[3] != -1 || (psVar14[2] != -1 || (psVar14[1] != -1 || *psVar14 != -1)))) {
      iVar4 = 0;
      iVar6 = 0;
      do {
        if (PTR_DAT_80433934[iVar4 + 0xcb] == '\x01') {
          iVar15 = 0;
          for (iVar8 = 0; iVar8 < (char)PTR_DAT_80433934[iVar4 + 0x5a]; iVar8 = iVar8 + 1) {
            local_44[0] = *(undefined2 *)(PTR_DAT_80433934 + iVar6 + iVar15 + 0x1e8);
            uVar5 = zz_0066168_((char *)local_44,(int)(char)PTR_DAT_80433934[iVar6 + iVar15 + 0x1ea]
                               );
            if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar4) == 0) {
              local_38 = (double)CONCAT44(0x43300000,uVar5 ^ 0x80000000);
              uVar5 = (uint)((float)(local_38 - DOUBLE_8043af90) * FLOAT_8043af88);
              local_30 = (double)(longlong)(int)uVar5;
            }
            iVar15 = iVar15 + 0x1c;
            *(uint *)(PTR_DAT_80433934 + 0x150) = *(int *)(PTR_DAT_80433934 + 0x150) + uVar5;
          }
        }
        iVar4 = iVar4 + 1;
        iVar6 = iVar6 + 0x348;
      } while (iVar4 < 6);
    }
    iVar4 = 0;
    puVar12 = &DAT_803d4938;
    do {
      for (psVar13 = (short *)puVar12[2]; (*psVar13 != -1 && (*psVar13 != 0x7fff));
          psVar13 = psVar13 + 0x10) {
        cVar1 = *(char *)(psVar13 + 5);
        if (((cVar1 != 'p') &&
            ((((cVar1 != 'q' && (cVar1 != 'r')) && (cVar1 != 's')) &&
             ((cVar1 != 't' && (cVar1 != 'u')))))) && (cVar1 != 'v')) {
          uVar3 = psVar13[4];
          if (((int)(short)uVar3 & 0x8000U) != 0) {
            iVar6 = zz_0188560_((int)(short)(uVar3 & 0x7fff));
            uVar3 = (ushort)iVar6;
          }
          local_48[0] = uVar3;
          local_3c = uVar3;
          uVar5 = zz_0066168_((char *)local_48,0);
          local_30 = (double)CONCAT44(0x43300000,uVar5 ^ 0x80000000);
          iVar6 = (int)((float)(local_30 - DOUBLE_8043af90) * FLOAT_8043af88);
          local_38 = (double)(longlong)iVar6;
          *(int *)(PTR_DAT_80433934 + 0x150) = *(int *)(PTR_DAT_80433934 + 0x150) + iVar6;
        }
      }
      iVar4 = iVar4 + 1;
      puVar12 = puVar12 + 1;
    } while (iVar4 < 2);
  }
  iVar4 = *(int *)(PTR_DAT_80433934 + 0x150) / 10 + (*(int *)(PTR_DAT_80433934 + 0x150) >> 0x1f);
  *(int *)(PTR_DAT_80433934 + 0x150) = (iVar4 - (iVar4 >> 0x1f)) * 10;
  *(undefined4 *)(PTR_DAT_80433934 + 0x154) = *(undefined4 *)(PTR_DAT_80433934 + 0x150);
  *(undefined4 *)(PTR_DAT_80433934 + 0x158) = *(undefined4 *)(PTR_DAT_80433934 + 0x150);
  if ((psVar14[0x14] & 1U) == 0) {
    PTR_DAT_80433934[0x108] = 0;
  }
  else {
    PTR_DAT_80433934[0x108] = 1;
  }
  if (((psVar14[0x14] & 2U) == 0) && ((psVar14[0x14] & 0x40U) == 0)) {
    PTR_DAT_80433934[0x144] = 0;
  }
  else {
    PTR_DAT_80433934[0x144] = 1;
  }
  if ((psVar14[0x14] & 4U) == 0) {
    PTR_DAT_80433934[0x109] = 0;
    PTR_DAT_80433934[0x10a] = 0;
  }
  else {
    PTR_DAT_80433934[0x109] = 1;
    PTR_DAT_80433934[0x10a] = *(undefined1 *)(psVar14 + 0x15);
  }
  if ((psVar14[0x14] & 8U) == 0) {
    PTR_DAT_80433934[0x145] = 0;
    PTR_DAT_80433934[0x146] = 0;
  }
  else {
    PTR_DAT_80433934[0x145] = 1;
    PTR_DAT_80433934[0x146] = *(undefined1 *)((int)psVar14 + 0x2b);
  }
  if ((psVar14[0x14] & 0x10U) != 0) {
    PTR_DAT_80433934[0x10b] = 1;
    PTR_DAT_80433934[0x147] = 0;
  }
  if ((psVar14[0x14] & 0x20U) != 0) {
    PTR_DAT_80433934[0x10b] = 0;
    PTR_DAT_80433934[0x147] = 1;
  }
  PTR_DAT_80433934[0x53] = 2;
  *(undefined2 *)(PTR_DAT_80433934 + 0x46) = 0;
  PTR_DAT_80433934[0xf4] = 0;
  PTR_DAT_80433934[0x130] = 1;
  *(undefined2 *)(PTR_DAT_80433934 + 0x110) = 0;
  *(undefined2 *)(PTR_DAT_80433934 + 0x14c) = 0;
  DAT_80436370 = *DAT_803d4938;
  DAT_80436368 = DAT_803d4938[1];
  DAT_80436360 = 0;
  uRam80436374 = *DAT_803d4940;
  uRam8043636c = DAT_803d4940[1];
  uRam80436364 = 0;
  uRam80436372 = *DAT_803d493c;
  uRam8043636a = DAT_803d493c[1];
  uRam80436362 = 0;
  uRam80436376 = *DAT_803d4944;
  uRam8043636e = DAT_803d4944[1];
  uRam80436366 = 0;
  *PTR_DAT_80433950 = *(undefined1 *)(psVar14 + 0x16);
  PTR_DAT_80433950[1] = *(undefined1 *)((int)psVar14 + 0x2d);
  PTR_DAT_80433934[0x1652] = *(undefined1 *)(psVar14 + 0x17);
  zz_0187ce4_();
  PTR_DAT_80433934[0x15db] = PTR_DAT_80433934[0x15d9];
  PTR_DAT_80433934[0x15dc] = PTR_DAT_80433934[0x15da];
  return;
}



// ==== 801873a4  zz_01873a4_ ====

void zz_01873a4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  short sVar1;
  bool bVar2;
  char cVar4;
  int iVar3;
  short *psVar5;
  short *psVar6;
  short *psVar7;
  short *psVar8;
  int iVar9;
  int iVar10;
  short *psVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined4 *puVar15;
  short *psVar16;
  
  if (DAT_80436358 != 0) {
    PTR_DAT_80433934[0x1828] = PTR_DAT_80433934[0x1828] | (byte)DAT_80436358;
  }
  if ((((('\x01' < (char)PTR_DAT_80433934[0x45]) && ((char)PTR_DAT_80433934[0x45] < '\x05')) &&
       (PTR_DAT_80433934[0x66] != '\x01')) &&
      ((cVar4 = Wiper__CutHasOccured_(), cVar4 == '\0' && (cVar4 = zz_008b480_(), cVar4 == '\0'))))
     && (cVar4 = zz_008b290_(), cVar4 == '\0')) {
    psVar11 = &DAT_80436370;
    iVar13 = 0;
    iVar9 = 0;
    iVar12 = 0;
    do {
      psVar6 = (short *)((int)&DAT_80436360 + iVar13);
      psVar7 = (short *)((int)&DAT_80436368 + iVar13);
      psVar8 = (short *)((int)&DAT_80436370 + iVar13);
      iVar10 = 0;
      iVar14 = 0;
      puVar15 = &DAT_803d4938;
      psVar16 = psVar11;
      do {
        if (-1 < *psVar16) {
          bVar2 = true;
          while (bVar2) {
            if (*psVar8 == 0) {
              iVar3 = *(int *)((int)puVar15 + iVar12);
              if (((int)*(short *)(iVar3 + 4) < (int)(char)PTR_DAT_80433934[iVar14 + 0x105]) ||
                 ((int)*(short *)(iVar3 + 6) < (int)(char)PTR_DAT_80433934[iVar14 + 0x106])) {
                bVar2 = false;
              }
              else {
                iVar3 = zz_01875d8_(iVar3);
                if (iVar3 == 0) {
                  bVar2 = false;
                }
                else if (*psVar7 == 0) {
                  iVar3 = zz_0187624_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                      param_8,iVar10,*(int *)((int)puVar15 + iVar12));
                  if (iVar3 == 0) {
                    bVar2 = false;
                  }
                  else {
                    sVar1 = *psVar6;
                    *(int *)((int)puVar15 + iVar12) = *(int *)((int)puVar15 + iVar12) + 0x20;
                    *psVar6 = sVar1 + 1;
                    psVar5 = *(short **)((int)puVar15 + iVar12);
                    if (*psVar5 == 0x7fff) {
                      sVar1 = psVar5[1];
                      *psVar6 = *psVar6 - sVar1;
                      *(short **)((int)puVar15 + iVar12) = psVar5 + sVar1 * -0x10;
                    }
                    psVar5 = *(short **)((int)puVar15 + iVar12);
                    *psVar8 = *psVar5;
                    *psVar7 = psVar5[1];
                  }
                }
                else {
                  bVar2 = false;
                  *psVar7 = *psVar7 + -1;
                }
              }
            }
            else {
              bVar2 = false;
              *psVar8 = *psVar8 + -1;
            }
          }
        }
        iVar10 = iVar10 + 1;
        psVar8 = psVar8 + 2;
        puVar15 = puVar15 + 2;
        iVar14 = iVar14 + 0x3c;
        psVar7 = psVar7 + 2;
        psVar6 = psVar6 + 2;
        psVar16 = psVar16 + 2;
      } while (iVar10 < 2);
      iVar9 = iVar9 + 1;
      iVar13 = iVar13 + 2;
      iVar12 = iVar12 + 4;
      psVar11 = psVar11 + 1;
    } while (iVar9 < 2);
  }
  return;
}



// ==== 801875d8  zz_01875d8_ ====

undefined4 zz_01875d8_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (((*(char *)(param_1 + 10) == 't') && (*(char *)(param_1 + 0xe) != '\0')) &&
     (iVar1 = zz_00ea140_(), iVar1 != 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 80187624  zz_0187624_ ====

undefined4
zz_0187624_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
           int param_10)

{
  char cVar1;
  undefined1 uVar2;
  ushort uVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  byte bVar7;
  undefined4 extraout_r4;
  int iVar8;
  byte *pbVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined1 *puVar12;
  int iVar13;
  undefined8 uVar14;
  undefined2 local_18 [2];
  undefined2 local_14 [2];
  
  cVar1 = *(char *)(param_10 + 10);
  if (cVar1 == 'p') {
    systemCallbackFunc_MCCSysEvent_((int)*(char *)(param_10 + 0xb));
    uVar4 = 1;
  }
  else if (cVar1 == 'r') {
    zz_00e9ce4_((double)FLOAT_8043af98,2,0x20,1,
                *(undefined4 *)(&DAT_8031a074 + *(char *)(param_10 + 0xb) * 4));
    uVar4 = 1;
  }
  else if (cVar1 == 's') {
    zz_01885bc_(param_10);
    uVar4 = 1;
  }
  else if (cVar1 == 't') {
    zz_00ea440_((int)*(char *)(param_10 + 0xb),(uint)*(byte *)(param_10 + 0xc),
                (int)*(char *)(param_10 + 0xd));
    uVar4 = 1;
  }
  else if (cVar1 == 'u') {
    if (*(char *)(param_10 + 0xb) < '\0') {
      PTR_DAT_80433934[0x1828] = PTR_DAT_80433934[0x1828] & 0xc0;
      DAT_80436358 = 0;
    }
    else {
      iVar5 = zz_0188750_((int)*(char *)(param_10 + 0xb));
      if (-1 < iVar5) {
        PTR_DAT_80433934[0x1828] = PTR_DAT_80433934[0x1828] & (byte)~(1 << iVar5);
        DAT_80436358 = DAT_80436358 & ~(1 << iVar5);
      }
    }
    uVar4 = 1;
  }
  else if (cVar1 == 'v') {
    if (*(char *)(param_10 + 0xb) < '\0') {
      PTR_DAT_80433934[0x1828] = PTR_DAT_80433934[0x1828] | 0x3f;
      DAT_80436358 = 0x3f;
    }
    else {
      iVar5 = zz_0188750_((int)*(char *)(param_10 + 0xb));
      if (-1 < iVar5) {
        PTR_DAT_80433934[0x1828] = PTR_DAT_80433934[0x1828] | (byte)(1 << iVar5);
        DAT_80436358 = DAT_80436358 | 1 << iVar5;
      }
    }
    uVar4 = 1;
  }
  else if (cVar1 == 'q') {
    uVar4 = 1;
  }
  else {
    iVar5 = zz_0188338_();
    if (iVar5 < 0) {
      uVar4 = 0;
    }
    else {
      puVar12 = (undefined1 *)(&DAT_803c4e84)[iVar5];
      *puVar12 = 1;
      puVar12[0x83] = 0;
      puVar12[0x3e4] = (char)iVar5;
      puVar12[999] = (char)iVar5;
      bVar7 = (byte)(1 << iVar5);
      puVar12[0x3e5] = bVar7;
      PTR_DAT_80433934[0x15da] = PTR_DAT_80433934[0x15da] + '\x01';
      PTR_DAT_80433934[0x15d9] = PTR_DAT_80433934[0x15d9] | bVar7;
      if (*(char *)(param_10 + 0xf) == '\x01') {
        PTR_DAT_80433934[iVar5 + 0x15f2] = 1;
        PTR_DAT_80433934[param_9 * 0x3c + 0x106] = PTR_DAT_80433934[param_9 * 0x3c + 0x106] + '\x01'
        ;
      }
      else {
        PTR_DAT_80433934[iVar5 + 0x15f2] = 0;
        PTR_DAT_80433934[param_9 * 0x3c + 0x105] = PTR_DAT_80433934[param_9 * 0x3c + 0x105] + '\x01'
        ;
      }
      if (*(char *)(param_10 + 0x10) == '\x01') {
        PTR_DAT_80433934[iVar5 + 0x15f8] = 1;
        PTR_DAT_80433934[param_9 * 0x3c + 0x107] = PTR_DAT_80433934[param_9 * 0x3c + 0x107] + '\x01'
        ;
      }
      else {
        PTR_DAT_80433934[iVar5 + 0x15f8] = 0;
      }
      PTR_DAT_80433934[iVar5 + 0xcb] = (char)param_9;
      PTR_DAT_80433934[iVar5 + 0x20] = *(undefined1 *)(param_10 + 0xb);
      PTR_DAT_80433934[iVar5 + 0x26] = 0;
      PTR_DAT_80433934[iVar5 + 0x32] = *(byte *)(param_10 + 0xc) & 0xf;
      if ((*(byte *)(param_10 + 0xc) & 0xf0) != 0) {
        PTR_DAT_80433934[iVar5 + 0x26] = (char)((int)(*(byte *)(param_10 + 0xc) & 0xf0) >> 4);
      }
      iVar8 = iVar5 * 0xc;
      PTR_DAT_80433934[iVar5 + 0x15ec] = 1;
      iVar13 = iVar5 * 0x348;
      PTR_DAT_80433934[iVar5 + 0x15e6] = *(undefined1 *)(param_10 + 0xd);
      PTR_DAT_80433934[iVar5 + 0x15e0] = *(undefined1 *)(param_10 + 0xe);
      *(undefined4 *)(PTR_DAT_80433934 + iVar8 + 0x1604) = *(undefined4 *)(param_10 + 0x14);
      *(undefined4 *)(PTR_DAT_80433934 + iVar8 + 0x1608) = *(undefined4 *)(param_10 + 0x18);
      *(undefined4 *)(PTR_DAT_80433934 + iVar8 + 0x160c) = *(undefined4 *)(param_10 + 0x1c);
      PTR_DAT_80433934[iVar5 + 0x15fe] = *(undefined1 *)(param_10 + 0x11);
      PTR_DAT_80433934[iVar5 + 0x15fe] = PTR_DAT_80433934[iVar5 + 0x15fe] & 0xf8;
      PTR_DAT_80433934[iVar5 + 0x164c] = *(undefined1 *)(param_10 + 0x11);
      PTR_DAT_80433934[iVar5 + 0x164c] = PTR_DAT_80433934[iVar5 + 0x164c] & 3;
      PTR_DAT_80433934[iVar13 + 0x1eb] = *(undefined1 *)(param_10 + 10);
      if (*(int *)(DAT_80436354 + 100) != 0) {
        if (PTR_DAT_80433934[iVar5 + 0xcb] == '\x01') {
          PTR_DAT_80433934[iVar5 + 0x32] =
               PTR_DAT_80433934[iVar5 + 0x32] + (char)*(int *)(DAT_80436354 + 100);
          if ('\x0e' < (char)PTR_DAT_80433934[iVar5 + 0x32]) {
            PTR_DAT_80433934[iVar5 + 0x32] = 0xf;
          }
          PTR_DAT_80433934[iVar13 + 0x1eb] =
               PTR_DAT_80433934[iVar13 + 0x1eb] + (char)*(undefined4 *)(DAT_80436354 + 100);
          if ('\b' < (char)PTR_DAT_80433934[iVar13 + 0x1eb]) {
            PTR_DAT_80433934[iVar13 + 0x1eb] = 9;
          }
        }
      }
      uVar3 = *(ushort *)(param_10 + 8);
      if (((int)(short)uVar3 & 0x8000U) == 0) {
        *(ushort *)(PTR_DAT_80433934 + iVar13 + 0x1e8) = uVar3;
      }
      else {
        iVar8 = zz_0188560_((int)(short)(uVar3 & 0x7fff));
        *(short *)(PTR_DAT_80433934 + iVar13 + 0x1e8) = (short)iVar8;
      }
      PTR_DAT_80433934[iVar13 + 0x1ea] = 0;
      uVar6 = zz_00055fc_();
      if (((uVar6 & 0xff) == 0) && (*(int *)(DAT_80436354 + 100) != 0)) {
        local_14[0] = *(undefined2 *)(PTR_DAT_80433934 + iVar13 + 0x1e8);
        bVar7 = zz_006854c_((char *)local_14);
        uVar6 = zz_00055fc_();
        if (((uint)bVar7 & 1 << (int)(char)(&DAT_80380944)[uVar6 & 0xf]) != 0) {
          PTR_DAT_80433934[iVar13 + 0x1ea] = (&DAT_80380944)[uVar6 & 0xf];
        }
      }
      else {
        uVar6 = zz_00055fc_();
        if ((uVar6 & 3) == 0) {
          local_18[0] = *(undefined2 *)(PTR_DAT_80433934 + iVar13 + 0x1e8);
          bVar7 = zz_006854c_((char *)local_18);
          if ((bVar7 & 2) != 0) {
            PTR_DAT_80433934[iVar13 + 0x1ea] = 1;
          }
        }
      }
      uVar11 = 0;
      uVar4 = 1;
      PTR_DAT_80433934[iVar13 + 0x1fe] = 0;
      PTR_DAT_80433934[iVar13 + 0x1ff] = 0;
      PTR_DAT_80433934[iVar13 + 0x200] = 0;
      PTR_DAT_80433934[iVar5 + 0x5a] = 1;
      PTR_DAT_80433934[iVar5 + 0x54] = 0;
      PTR_DAT_80433934[iVar5 + 0x15c8] = 0;
      uVar14 = zz_0068424_(iVar5,(undefined2 *)(PTR_DAT_80433934 + iVar5 * 2 + 0x10),
                           PTR_DAT_80433934 + iVar5 + 0xa0);
      puVar12[999] = puVar12[0x3e4];
      *(undefined2 *)(puVar12 + 0x3ea) = *(undefined2 *)(PTR_DAT_80433934 + iVar5 * 2 + 0x10);
      *(undefined2 *)(puVar12 + 1000) = *(undefined2 *)(puVar12 + 0x3ea);
      uVar2 = PTR_DAT_80433934[iVar5 + 0xa0];
      puVar12[0x3ed] = uVar2;
      puVar12[0x3ec] = uVar2;
      puVar12[0x492] = PTR_DAT_80433934[iVar5 + 0x54];
      *(undefined1 **)(puVar12 + 0x8c) = puVar12;
      *(undefined1 **)(puVar12 + 0x90) = puVar12;
      *(undefined2 *)(puVar12 + 0x94) = *(undefined2 *)(puVar12 + 1000);
      puVar12[0x96] = puVar12[0x3e4];
      puVar12[0x97] = puVar12[999];
      zz_00410bc_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5);
      iVar8 = (int)(char)PTR_DAT_80433934[iVar5 + 0x20];
      if (iVar8 < 0xe) {
        if (PTR_DAT_80433934[iVar5 + 0xcb] == '\0') {
          zz_0182610_(iVar8);
        }
        else {
          zz_018262c_(iVar8);
        }
      }
      else {
        iVar8 = 0xe;
      }
      uVar10 = 0x803c0000;
      pbVar9 = (&PTR_DAT_8035b294)[iVar8];
      uVar14 = zz_0098084_(-0x7fc44bc0,iVar5,pbVar9);
      uVar14 = zz_0042ebc_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                           extraout_r4,pbVar9,uVar10,uVar4,uVar11,in_r9,in_r10);
      zz_0042b94_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5);
      uVar4 = 1;
    }
  }
  return uVar4;
}



// ==== 80187ce4  zz_0187ce4_ ====

void zz_0187ce4_(void)

{
  short sVar1;
  bool bVar2;
  bool bVar3;
  undefined *puVar4;
  int iVar5;
  short *psVar6;
  int iVar7;
  int iVar8;
  short *psVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined4 *puVar15;
  short *psVar16;
  short *psVar17;
  short *psVar18;
  short *psVar19;
  int iVar20;
  
  psVar9 = &DAT_80436370;
  iVar13 = 0;
  iVar10 = 0;
  iVar12 = 0;
  do {
    psVar17 = (short *)((int)&DAT_80436360 + iVar13);
    psVar18 = (short *)((int)&DAT_80436368 + iVar13);
    psVar19 = (short *)((int)&DAT_80436370 + iVar13);
    iVar11 = 0;
    iVar14 = 0;
    puVar15 = &DAT_803d4938;
    psVar16 = psVar9;
    do {
      if (-1 < *psVar16) {
        bVar3 = true;
        while (bVar3) {
          if (*psVar19 == 0) {
            iVar5 = *(int *)((int)puVar15 + iVar12);
            if (((int)*(short *)(iVar5 + 4) < (int)(char)PTR_DAT_80433934[iVar14 + 0x105]) ||
               ((int)*(short *)(iVar5 + 6) < (int)(char)PTR_DAT_80433934[iVar14 + 0x106])) {
              bVar3 = false;
            }
            else if (*psVar18 == 0) {
              bVar2 = false;
              iVar7 = 0;
              iVar8 = 0;
              iVar20 = 6;
              puVar4 = PTR_DAT_80433934;
              do {
                if (*(short *)(puVar4 + 0x10) < 0) {
                  bVar2 = true;
                  iVar7 = iVar8;
                  break;
                }
                puVar4 = puVar4 + 2;
                iVar8 = iVar8 + 1;
                iVar20 = iVar20 + -1;
              } while (iVar20 != 0);
              if (!bVar2) break;
              iVar5 = zz_0187ebc_(iVar11,iVar5,iVar7);
              if (iVar5 != 0) {
                sVar1 = *psVar17;
                *(int *)((int)puVar15 + iVar12) = *(int *)((int)puVar15 + iVar12) + 0x20;
                *psVar17 = sVar1 + 1;
                psVar6 = *(short **)((int)puVar15 + iVar12);
                if (*psVar6 == 0x7fff) {
                  sVar1 = psVar6[1];
                  *psVar17 = *psVar17 - sVar1;
                  *(short **)((int)puVar15 + iVar12) = psVar6 + sVar1 * -0x10;
                }
                psVar6 = *(short **)((int)puVar15 + iVar12);
                *psVar19 = *psVar6;
                *psVar18 = psVar6[1];
              }
            }
            else {
              bVar3 = false;
            }
          }
          else {
            bVar3 = false;
          }
        }
      }
      iVar11 = iVar11 + 1;
      psVar19 = psVar19 + 2;
      puVar15 = puVar15 + 2;
      iVar14 = iVar14 + 0x3c;
      psVar18 = psVar18 + 2;
      psVar17 = psVar17 + 2;
      psVar16 = psVar16 + 2;
    } while (iVar11 < 2);
    iVar10 = iVar10 + 1;
    iVar13 = iVar13 + 2;
    iVar12 = iVar12 + 4;
    psVar9 = psVar9 + 1;
    if (1 < iVar10) {
      return;
    }
  } while( true );
}



// ==== 80187ebc  zz_0187ebc_ ====

undefined4 zz_0187ebc_(int param_1,int param_2,int param_3)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  int iVar4;
  
  cVar1 = *(char *)(param_2 + 10);
  if ((((cVar1 != 'p') && (cVar1 != 'r')) && (cVar1 != 's')) && (cVar1 != 't')) {
    if (cVar1 == 'u') {
      if (*(char *)(param_2 + 0xb) < '\0') {
        PTR_DAT_80433934[0x1828] = PTR_DAT_80433934[0x1828] & 0xc0;
        DAT_80436358 = 0;
      }
      else {
        iVar3 = zz_0188750_((int)*(char *)(param_2 + 0xb));
        if (-1 < iVar3) {
          PTR_DAT_80433934[0x1828] = PTR_DAT_80433934[0x1828] & (byte)~(1 << iVar3);
          DAT_80436358 = DAT_80436358 & ~(1 << iVar3);
        }
      }
    }
    else if (cVar1 == 'v') {
      if (*(char *)(param_2 + 0xb) < '\0') {
        PTR_DAT_80433934[0x1828] = PTR_DAT_80433934[0x1828] | 0x3f;
        DAT_80436358 = 0x3f;
      }
      else {
        iVar3 = zz_0188750_((int)*(char *)(param_2 + 0xb));
        if (-1 < iVar3) {
          PTR_DAT_80433934[0x1828] = PTR_DAT_80433934[0x1828] | (byte)(1 << iVar3);
          DAT_80436358 = DAT_80436358 | 1 << iVar3;
        }
      }
    }
    else if (cVar1 != 'q') {
      PTR_DAT_80433934[0x15da] = PTR_DAT_80433934[0x15da] + '\x01';
      PTR_DAT_80433934[0x15d9] = PTR_DAT_80433934[0x15d9] | (byte)(1 << param_3);
      if (*(char *)(param_2 + 0xf) == '\x01') {
        PTR_DAT_80433934[param_3 + 0x15f2] = 1;
        PTR_DAT_80433934[param_1 * 0x3c + 0x106] = PTR_DAT_80433934[param_1 * 0x3c + 0x106] + '\x01'
        ;
      }
      else {
        PTR_DAT_80433934[param_3 + 0x15f2] = 0;
        PTR_DAT_80433934[param_1 * 0x3c + 0x105] = PTR_DAT_80433934[param_1 * 0x3c + 0x105] + '\x01'
        ;
      }
      if (*(char *)(param_2 + 0x10) == '\x01') {
        PTR_DAT_80433934[param_3 + 0x15f8] = 1;
        PTR_DAT_80433934[param_1 * 0x3c + 0x107] = PTR_DAT_80433934[param_1 * 0x3c + 0x107] + '\x01'
        ;
      }
      else {
        PTR_DAT_80433934[param_3 + 0x15f8] = 0;
      }
      PTR_DAT_80433934[param_3 + 0xcb] = (char)param_1;
      PTR_DAT_80433934[param_3 + 0x20] = *(undefined1 *)(param_2 + 0xb);
      PTR_DAT_80433934[param_3 + 0x26] = 0;
      PTR_DAT_80433934[param_3 + 0x32] = *(byte *)(param_2 + 0xc) & 0xf;
      if ((*(byte *)(param_2 + 0xc) & 0xf0) != 0) {
        PTR_DAT_80433934[param_3 + 0x26] = (char)((int)(*(byte *)(param_2 + 0xc) & 0xf0) >> 4);
      }
      iVar3 = param_3 * 0xc;
      PTR_DAT_80433934[param_3 + 0x15ec] = 1;
      iVar4 = param_3 * 0x348;
      PTR_DAT_80433934[param_3 + 0x15e6] = *(undefined1 *)(param_2 + 0xd);
      PTR_DAT_80433934[param_3 + 0x15e0] = *(undefined1 *)(param_2 + 0xe);
      *(undefined4 *)(PTR_DAT_80433934 + iVar3 + 0x1604) = *(undefined4 *)(param_2 + 0x14);
      *(undefined4 *)(PTR_DAT_80433934 + iVar3 + 0x1608) = *(undefined4 *)(param_2 + 0x18);
      *(undefined4 *)(PTR_DAT_80433934 + iVar3 + 0x160c) = *(undefined4 *)(param_2 + 0x1c);
      PTR_DAT_80433934[param_3 + 0x15fe] = *(undefined1 *)(param_2 + 0x11);
      PTR_DAT_80433934[param_3 + 0x15fe] = PTR_DAT_80433934[param_3 + 0x15fe] & 0xf8;
      PTR_DAT_80433934[param_3 + 0x164c] = *(undefined1 *)(param_2 + 0x11);
      PTR_DAT_80433934[param_3 + 0x164c] = PTR_DAT_80433934[param_3 + 0x164c] & 3;
      PTR_DAT_80433934[iVar4 + 0x1eb] = *(undefined1 *)(param_2 + 10);
      if ((*(int *)(DAT_80436354 + 100) != 0) && (PTR_DAT_80433934[param_3 + 0xcb] == '\x01')) {
        PTR_DAT_80433934[param_3 + 0x32] =
             PTR_DAT_80433934[param_3 + 0x32] + (char)*(int *)(DAT_80436354 + 100);
        if ('\x0e' < (char)PTR_DAT_80433934[param_3 + 0x32]) {
          PTR_DAT_80433934[param_3 + 0x32] = 0xf;
        }
        PTR_DAT_80433934[iVar4 + 0x1eb] =
             PTR_DAT_80433934[iVar4 + 0x1eb] + (char)*(undefined4 *)(DAT_80436354 + 100);
        if ('\b' < (char)PTR_DAT_80433934[iVar4 + 0x1eb]) {
          PTR_DAT_80433934[iVar4 + 0x1eb] = 9;
        }
      }
      uVar2 = *(ushort *)(param_2 + 8);
      if (((int)(short)uVar2 & 0x8000U) == 0) {
        *(ushort *)(PTR_DAT_80433934 + iVar4 + 0x1e8) = uVar2;
      }
      else {
        iVar3 = zz_0188560_((int)(short)(uVar2 & 0x7fff));
        *(short *)(PTR_DAT_80433934 + iVar4 + 0x1e8) = (short)iVar3;
      }
      zz_01884d8_(param_3,*(undefined2 *)(PTR_DAT_80433934 + iVar4 + 0x1e8));
      iVar3 = (int)(char)PTR_DAT_80433934[param_3 + 0x20];
      if (iVar3 < 0xe) {
        if (PTR_DAT_80433934[param_3 + 0xcb] == '\0') {
          zz_0182610_(iVar3);
        }
        else {
          zz_018262c_(iVar3);
        }
      }
      zz_0098084_(-0x7fc44bc0,param_3,(&PTR_DAT_8035b294)[iVar3]);
    }
  }
  return 1;
}



// ==== 80188338  zz_0188338_ ====

undefined4 zz_0188338_(void)

{
  if (*DAT_803c4e84 == '\0') {
    if (DAT_803c4e84[0x3f2] == '\0') {
      return 0;
    }
  }
  if (*DAT_803c4e88 == '\0') {
    if (DAT_803c4e88[0x3f2] == '\0') {
      return 1;
    }
  }
  if (*DAT_803c4e8c == '\0') {
    if (DAT_803c4e8c[0x3f2] == '\0') {
      return 2;
    }
  }
  if (*DAT_803c4e90 == '\0') {
    if (DAT_803c4e90[0x3f2] == '\0') {
      return 3;
    }
  }
  if (*DAT_803c4e94 == '\0') {
    if (DAT_803c4e94[0x3f2] == '\0') {
      return 4;
    }
  }
  if ((*DAT_803c4e98 == '\0') && (DAT_803c4e98[0x3f2] == '\0')) {
    return 5;
  }
  return 0xffffffff;
}



// ==== 8018841c  zz_018841c_ ====

void zz_018841c_(int param_1,int param_2,undefined1 param_3)

{
  short *psVar1;
  char cVar2;
  short *psVar3;
  
  psVar3 = (short *)(&PTR_DAT_80380164)[param_2];
  cVar2 = '\0';
  psVar1 = (short *)(PTR_DAT_80433934 + param_1 * 0x348 + 0x1e8);
  while( true ) {
    if (*psVar3 < 0) break;
    *psVar1 = *psVar3;
    psVar3 = psVar3 + 1;
    cVar2 = cVar2 + '\x01';
    *(undefined1 *)(psVar1 + 1) = 0;
    *(undefined1 *)((int)psVar1 + 3) = param_3;
    *(undefined1 *)(psVar1 + 0xb) = 0;
    *(undefined1 *)((int)psVar1 + 0x17) = 0;
    *(undefined1 *)(psVar1 + 0xc) = 0;
    psVar1 = psVar1 + 0xe;
  }
  PTR_DAT_80433934[param_1 + 0x5a] = cVar2;
  PTR_DAT_80433934[param_1 + 0x54] = 0;
  PTR_DAT_80433934[param_1 + 0x15c8] = 0;
  zz_0068424_(param_1,(undefined2 *)(PTR_DAT_80433934 + param_1 * 2 + 0x10),
              PTR_DAT_80433934 + param_1 + 0xa0);
  return;
}



// ==== 801884d8  zz_01884d8_ ====

void zz_01884d8_(int param_1,undefined2 param_2)

{
  undefined2 *puVar1;
  
  puVar1 = (undefined2 *)(PTR_DAT_80433934 + param_1 * 0x348 + 0x1e8);
  *puVar1 = param_2;
  *(undefined1 *)(puVar1 + 1) = 0;
  *(undefined1 *)(puVar1 + 0xb) = 0;
  *(undefined1 *)((int)puVar1 + 0x17) = 0;
  *(undefined1 *)(puVar1 + 0xc) = 0;
  PTR_DAT_80433934[param_1 + 0x5a] = 1;
  PTR_DAT_80433934[param_1 + 0x54] = 0;
  PTR_DAT_80433934[param_1 + 0x15c8] = 0;
  zz_0068424_(param_1,(undefined2 *)(PTR_DAT_80433934 + param_1 * 2 + 0x10),
              PTR_DAT_80433934 + param_1 + 0xa0);
  return;
}



// ==== 80188560  zz_0188560_ ====

int zz_0188560_(int param_1)

{
  short *psVar1;
  uint uVar2;
  
  uVar2 = 0;
  for (psVar1 = (short *)(&PTR_DAT_80380804)[param_1]; *psVar1 != -1; psVar1 = psVar1 + 1) {
    uVar2 = uVar2 + 1;
  }
  if (uVar2 == 0) {
    return 8;
  }
  return (int)*(short *)((int)(&PTR_DAT_80380804)[param_1] +
                        (DAT_8043635c - (DAT_8043635c / uVar2) * uVar2) * 2);
}



// ==== 801885bc  zz_01885bc_ ====

void zz_01885bc_(int param_1)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  int in_r9;
  int *piVar4;
  int iVar5;
  
  bVar1 = false;
  iVar3 = 0;
  piVar4 = &DAT_803c4e84;
  iVar5 = 2;
  piVar2 = piVar4;
  do {
    if (*(char *)*piVar2 != '\0') {
      if (*(short *)(param_1 + 8) == *(short *)((char *)*piVar2 + 1000)) {
        if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar3) == 0) {
          bVar1 = true;
          in_r9 = iVar3;
          break;
        }
      }
    }
    if (*(char *)piVar2[1] != '\0') {
      if (*(short *)(param_1 + 8) == *(short *)((char *)piVar2[1] + 1000)) {
        if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar3 + 1) == 0) {
          bVar1 = true;
          in_r9 = iVar3 + 1;
          break;
        }
      }
    }
    if (*(char *)piVar2[2] != '\0') {
      if (*(short *)(param_1 + 8) == *(short *)((char *)piVar2[2] + 1000)) {
        if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar3 + 2) == 0) {
          bVar1 = true;
          in_r9 = iVar3 + 2;
          break;
        }
      }
    }
    piVar2 = piVar2 + 3;
    iVar3 = iVar3 + 3;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  if (bVar1) {
    iVar3 = 0;
    do {
      if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar3) != 0) {
        zz_001080c_((double)*(float *)(param_1 + 0x14),*piVar4,(&DAT_803c4e84)[in_r9],
                    *(undefined1 *)(param_1 + 0x10),(short)(int)*(float *)(param_1 + 0x18),
                    *(undefined1 *)(param_1 + 0xb));
      }
      iVar3 = iVar3 + 1;
      piVar4 = piVar4 + 1;
    } while (iVar3 < 6);
  }
  return;
}



// ==== 80188750  zz_0188750_ ====

undefined4 zz_0188750_(int param_1)

{
  if ((char)PTR_DAT_80433934[0x20] == param_1) {
    return 0;
  }
  if ((char)PTR_DAT_80433934[0x21] == param_1) {
    return 1;
  }
  if ((char)PTR_DAT_80433934[0x22] == param_1) {
    return 2;
  }
  if ((char)PTR_DAT_80433934[0x23] == param_1) {
    return 3;
  }
  if ((char)PTR_DAT_80433934[0x24] == param_1) {
    return 4;
  }
  if ((char)PTR_DAT_80433934[0x25] == param_1) {
    return 5;
  }
  return 0xffffffff;
}



// ==== 801887ec  zz_01887ec_ ====

uint zz_01887ec_(void)

{
  if (((int)*(short *)((&PTR_DAT_8037f5d0)[*(int *)(DAT_80436354 + 0x9c8)] + 0x28) & 8U) != 0) {
    return 1;
  }
  return -((uint)(int)*(short *)((&PTR_DAT_8037f5d0)[*(int *)(DAT_80436354 + 0x9c8)] + 0x28) >> 6 &
          1) & 2;
}



// ==== 801889ec  FUN_801889ec ====

void FUN_801889ec(int param_1)

{
  *(undefined1 *)(param_1 + 0x145) = 0;
  *(undefined1 *)(param_1 + 0x146) = 0;
  *(undefined1 *)(param_1 + 0x147) = 0;
  if (*(short *)(param_1 + 1000) == 0xd01) {
    zz_00f846c_(param_1,0);
    zz_00f889c_(param_1,0);
  }
  else {
    zz_00f889c_(param_1,1);
  }
  *(float *)(param_1 + 0x1dc0) = FLOAT_8043afa0;
  zz_00c74ec_(param_1,0x35);
  return;
}



// ==== 80188a64  FUN_80188a64 ====

void FUN_80188a64(int param_1)

{
  if ((*(short *)(param_1 + 1000) == 0xd01) &&
     (*(short *)(param_1 + 0x78e) <= *(short *)(param_1 + 0x774))) {
    *(undefined1 *)(param_1 + 0x146) = 0;
    *(undefined1 *)(param_1 + 0x147) = 0;
    *(undefined1 *)(param_1 + 0x148) = 0;
  }
  if (*(short *)(param_1 + 0x79e) <= *(short *)(param_1 + 0x784)) {
    *(undefined1 *)(param_1 + 0x145) = 0;
  }
  if ((*(byte *)(param_1 + 0x7d2) & 1) != 0) {
    if (((*(byte *)(param_1 + 0x7d2) & 2) == 0) && (*(char *)(param_1 + 0x144) == '\0')) {
      if (*(short *)(param_1 + 1000) == 0xd01) {
        zz_011b68c_(param_1,0);
      }
      else if (*(short *)(param_1 + 1000) == 0xd05) {
        zz_011b68c_(param_1,1);
      }
    }
  }
  return;
}



// ==== 80188b24  FUN_80188b24 ====

void FUN_80188b24(int param_1)

{
  (*(code *)(&PTR_FUN_80362658)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80188b60  FUN_80188b60 ====

void FUN_80188b60(int param_1)

{
  (*(code *)(&PTR_LAB_80362664)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80188bc8  FUN_80188bc8 ====

void FUN_80188bc8(int param_1)

{
  int iVar1;
  double dVar2;
  
  if ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x14a) = 1;
  }
  dVar2 = (double)FLOAT_8043afa8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = FUN_8006cc90(dVar2,param_1,8,1,(short *)&DAT_80435678);
  if ((iVar1 == 0) && (FLOAT_8043afac < *(float *)(param_1 + 0x558))) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 80188c54  FUN_80188c54 ====

void FUN_80188c54(int param_1)

{
  float fVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x14a) = 1;
  }
  if (*(short *)(param_1 + 0x14c) == 0) {
    *(undefined2 *)(param_1 + 0x14c) = 10;
    *(short *)(param_1 + 0x14e) = *(short *)(param_1 + 0x14e) + 1;
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      zz_0082824_(param_1,(int)*(char *)(param_1 + 0x149) + 0x10);
      *(char *)(param_1 + 0x149) = *(char *)(param_1 + 0x149) + '\x01';
      *(byte *)(param_1 + 0x149) = *(byte *)(param_1 + 0x149) & 1;
    }
    fVar1 = FLOAT_8043afb0;
    if (*(short *)(param_1 + 0x14a) == 0) {
      if (0 < *(short *)(param_1 + 0x14e)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar1;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x14a) = 0;
      fVar1 = FLOAT_8043afb0;
      if (9 < *(short *)(param_1 + 0x14e)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar1;
      }
    }
  }
  else {
    *(short *)(param_1 + 0x14c) = *(short *)(param_1 + 0x14c) + -1;
  }
  return;
}



// ==== 80188d5c  FUN_80188d5c ====

void FUN_80188d5c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043afac;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 80188da4  FUN_80188da4 ====

void FUN_80188da4(int param_1)

{
  (*(code *)(&PTR_LAB_80362674)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80188df8  FUN_80188df8 ====

bool FUN_80188df8(int param_1)

{
  float fVar1;
  int iVar2;
  bool bVar3;
  
  fVar1 = FLOAT_8043afb0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  iVar2 = zz_006dbe0_(param_1,2,1,1);
  bVar3 = false;
  if (iVar2 != 0) {
    *(undefined1 *)(param_1 + 0x145) = 1;
    if (*(short *)(param_1 + 1000) == 0xd01) {
      bVar3 = zz_00fb220_(param_1,0);
    }
    else {
      bVar3 = zz_00fb220_(param_1,1);
    }
  }
  return bVar3;
}



// ==== 80188e7c  FUN_80188e7c ====

void FUN_80188e7c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043afac;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 80188ec4  FUN_80188ec4 ====

void FUN_80188ec4(int param_1)

{
  (*(code *)(&PTR_LAB_80362680)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80188f18  FUN_80188f18 ====

void FUN_80188f18(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_8043afb0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    *(undefined1 *)(param_1 + *(char *)(param_1 + 0x148) + 0x146) = 1;
    zz_00fcd38_(param_1,0,*(undefined1 *)(param_1 + 0x148));
    *(char *)(param_1 + 0x148) = *(char *)(param_1 + 0x148) + '\x01';
    *(byte *)(param_1 + 0x148) = *(byte *)(param_1 + 0x148) & 1;
  }
  return;
}



// ==== 80188fac  FUN_80188fac ====

void FUN_80188fac(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043afac;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 801890d4  FUN_801890d4 ====

void FUN_801890d4(int param_1,undefined4 param_2)

{
  float fVar1;
  
  zz_010ee88_(param_1,param_2);
  zz_00c74ec_(param_1,0x37);
  zz_00c74ec_(param_1,0x38);
  zz_00c74ec_(param_1,0x39);
  zz_00c74ec_(param_1,0x3a);
  fVar1 = FLOAT_8043afb8;
  *(undefined1 *)(param_1 + 0x6e8) = 1;
  *(float *)(param_1 + 0x1dc0) = fVar1;
  return;
}



// ==== 80189140  FUN_80189140 ====

void FUN_80189140(int param_1)

{
  *(undefined2 *)(param_1 + 0x1d68) = 0;
  *(undefined2 *)(param_1 + 0x1d64) = 0;
  zz_0189798_(param_1,(float *)(param_1 + 0x144));
  if ('\0' < *(char *)(param_1 + 0x6f7)) {
    *(char *)(param_1 + 0x6f7) = *(char *)(param_1 + 0x6f7) + -1;
  }
  return;
}



// ==== 80189190  FUN_80189190 ====

void FUN_80189190(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_8043afbc;
  if (iVar3 == 0) {
    *(undefined1 *)(param_1 + 0x159) = 0;
  }
  else {
    if (*(char *)(param_1 + 0x159) == '\0') {
      *(undefined1 *)(param_1 + 0x159) = 1;
      *(float *)(param_1 + 0x80c) = fVar2;
    }
    zz_00b22f4_(param_1);
  }
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  *(undefined2 *)(param_1 + 0x1d68) = 0;
  *(undefined2 *)(param_1 + 0x1d64) = 0;
  cVar1 = *(char *)(param_1 + 0x5e4);
  if (cVar1 < '\x1d') {
    if (cVar1 == '\a') {
      return;
    }
    if (cVar1 < '\a') {
      if (cVar1 < '\x05') {
        return;
      }
    }
    else if ('\b' < cVar1) {
      return;
    }
  }
  else if (cVar1 != '&') {
    if ('%' < cVar1) {
      return;
    }
    if ('\x1e' < cVar1) {
      return;
    }
  }
  zz_00f0104_(param_1,0x1d,6);
  return;
}



// ==== 8018927c  FUN_8018927c ====

void FUN_8018927c(int param_1)

{
  (*(code *)(&PTR_FUN_80362990)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801892b8  FUN_801892b8 ====

void FUN_801892b8(int param_1)

{
  (*(code *)(&PTR_LAB_8036299c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80189320  FUN_80189320 ====

void FUN_80189320(int param_1)

{
  int iVar1;
  double dVar2;
  
  if ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x152) = 1;
  }
  dVar2 = (double)FLOAT_8043afc4;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = FUN_8006cc90(dVar2,param_1,3,1,(short *)&DAT_80435680);
  if (iVar1 == 0) {
    if (FLOAT_8043afbc < *(float *)(param_1 + 0x558)) goto LAB_80189398;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
LAB_80189398:
  *(undefined2 *)(param_1 + 0x18ec) = *(undefined2 *)(param_1 + 0x18e6);
  return;
}



// ==== 801893b4  FUN_801893b4 ====

void FUN_801893b4(int param_1)

{
  float fVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x152) = 1;
  }
  if (*(short *)(param_1 + 0x154) == 0) {
    *(undefined2 *)(param_1 + 0x154) = 10;
    *(short *)(param_1 + 0x156) = *(short *)(param_1 + 0x156) + 1;
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      zz_00c3be0_(param_1,0x36);
      zz_00c3be0_(param_1,0x37);
      *(char *)(param_1 + 0x151) = *(char *)(param_1 + 0x151) + '\x01';
      *(byte *)(param_1 + 0x151) = *(byte *)(param_1 + 0x151) & 1;
    }
    fVar1 = FLOAT_8043afc8;
    if (*(short *)(param_1 + 0x152) == 0) {
      if (0 < *(short *)(param_1 + 0x156)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar1;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x152) = 0;
      fVar1 = FLOAT_8043afc8;
      if (4 < *(short *)(param_1 + 0x156)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar1;
      }
    }
  }
  else {
    *(short *)(param_1 + 0x154) = *(short *)(param_1 + 0x154) + -1;
  }
  return;
}



// ==== 801894c0  FUN_801894c0 ====

void FUN_801894c0(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043afbc;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 80189508  FUN_80189508 ====

void FUN_80189508(int param_1)

{
  (*(code *)(&PTR_FUN_803629ac)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80189544  FUN_80189544 ====

void FUN_80189544(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_8043afcc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 0x4000;
  *(undefined2 *)(param_1 + 0x54a) = 0xfde0;
  *(undefined2 *)(param_1 + 0x54c) = 0x14;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined4 *)(param_1 + 0x174) = *(undefined4 *)(param_1 + 0x814);
  iVar2 = zz_006dbe0_(param_1,2,1,1);
  if (iVar2 == 0) {
    zz_006a53c_(param_1,0x1e);
  }
  else {
    zz_01deb68_(param_1,8,param_1 + 0x15c,param_1 + 0x168,param_1 + 0x6f7);
    zz_01895e8_(param_1);
  }
  return;
}



// ==== 801895e8  zz_01895e8_ ====

void zz_01895e8_(int param_1)

{
  float fVar1;
  float fVar2;
  
  *(undefined1 *)(param_1 + 0x6f7) = 2;
  zz_0189704_(param_1,param_1 + 0x144);
  fVar2 = FLOAT_8043afbc;
  if (*(short *)(param_1 + 0x54c) < 1) {
    *(short *)(param_1 + 0x548) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x54a) ^ 0x80000000) -
                             DOUBLE_8043afd0) * *(float *)(param_1 + 0x1dc8) +
                     (float)((double)CONCAT44(0x43300000,
                                              (int)*(short *)(param_1 + 0x548) ^ 0x80000000) -
                            DOUBLE_8043afd0));
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    }
  }
  else {
    *(short *)(param_1 + 0x54c) = *(short *)(param_1 + 0x54c) + -1;
  }
  return;
}



// ==== 801896b4  FUN_801896b4 ====

void FUN_801896b4(int param_1)

{
  short sVar1;
  
  zz_0189704_(param_1,param_1 + 0x144);
  sVar1 = *(short *)(param_1 + 0x548) + -1;
  *(short *)(param_1 + 0x548) = sVar1;
  if (sVar1 < 1) {
    zz_006a53c_(param_1,0x1e);
  }
  return;
}



// ==== 80189704  zz_0189704_ ====

/* WARNING: Removing unreachable block (ram,0x80189734) */

void zz_0189704_(int param_1,int param_2)

{
  float local_48;
  float local_44;
  undefined4 local_40;
  float afStack_3c [13];
  
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x934),(float *)&DAT_803629b8,(float *)(param_2 + 0x18));
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043afd8 *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x548) *
                                             0x3ff0000000000000)),afStack_3c,0x78);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x934),afStack_3c,afStack_3c);
  local_48 = FLOAT_8043afbc;
  local_44 = FLOAT_8043afbc;
  local_40 = *(undefined4 *)(param_2 + 0x30);
  gnt4_PSMTXMultVec_bl(afStack_3c,&local_48,(float *)(param_2 + 0x24));
  return;
}



// ==== 80189798  zz_0189798_ ====

void zz_0189798_(int param_1,float *param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  if (*(char *)((int)param_2 + 7) != *(char *)(param_1 + 0x6e8)) {
    *(char *)((int)param_2 + 6) = *(char *)(param_1 + 0x6e8);
    *(undefined2 *)(param_2 + 1) = 0;
  }
  fVar1 = FLOAT_8043afbc;
  if ((char)*(byte *)((int)param_2 + 6) < '\0') {
    *(byte *)((int)param_2 + 6) = *(byte *)((int)param_2 + 6) & 0x7f;
    *param_2 = fVar1;
    *(undefined2 *)(param_2 + 1) = 0;
  }
  fVar2 = FLOAT_8043afdc;
  fVar1 = FLOAT_8043afbc;
  if (*(char *)((int)param_2 + 6) == '\0') {
    if ((FLOAT_8043afbc < *param_2) && (*param_2 = *param_2 - FLOAT_8043afe0, *param_2 < fVar1)) {
      *param_2 = fVar1;
    }
  }
  else {
    if ((*param_2 < FLOAT_8043afdc) && (*param_2 = *param_2 + FLOAT_8043afe0, fVar2 < *param_2)) {
      *param_2 = fVar2;
    }
    *(short *)(param_2 + 1) = *(short *)(param_2 + 1) + 0x300;
  }
  dVar3 = zz_0045204_(*(short *)(param_2 + 1));
  *(float *)(param_1 + 0x1dc0) = *param_2 * (float)((double)FLOAT_8043afe4 * dVar3) + FLOAT_8043afb8
  ;
  *(undefined1 *)((int)param_2 + 7) = *(undefined1 *)((int)param_2 + 6);
  return;
}



// ==== 80189990  FUN_80189990 ====

void FUN_80189990(int param_1)

{
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  zz_00c74ec_(param_1,0x3c);
  *(float *)(*(int *)(param_1 + 0x4ac) + 0x98) = FLOAT_8043afe8;
  return;
}



// ==== 801899e8  FUN_801899e8 ====

void FUN_801899e8(int param_1)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  int iVar6;
  
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  dVar5 = DOUBLE_8043aff8;
  fVar4 = FLOAT_8043aff4;
  fVar3 = FLOAT_8043aff0;
  fVar2 = FLOAT_8043afec;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    iVar6 = 2;
    iVar1 = param_1;
    do {
      *(short *)(iVar1 + 0x18f8) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(iVar1 + 0x18f8) ^ 0x80000000) -
                               dVar5) * (fVar3 * (fVar4 - *(float *)(param_1 + 0x1dc8)) + fVar2));
      *(short *)(iVar1 + 0x18fa) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(iVar1 + 0x18fa) ^ 0x80000000) -
                               dVar5) * (fVar3 * (fVar4 - *(float *)(param_1 + 0x1dc8)) + fVar2));
      *(short *)(iVar1 + 0x18fe) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(iVar1 + 0x18fe) ^ 0x80000000) -
                               dVar5) * (fVar3 * (fVar4 - *(float *)(param_1 + 0x1dc8)) + fVar2));
      *(short *)(iVar1 + 0x1900) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(iVar1 + 0x1900) ^ 0x80000000) -
                               dVar5) * (fVar3 * (fVar4 - *(float *)(param_1 + 0x1dc8)) + fVar2));
      *(short *)(iVar1 + 0x1904) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(iVar1 + 0x1904) ^ 0x80000000) -
                               dVar5) * (fVar3 * (fVar4 - *(float *)(param_1 + 0x1dc8)) + fVar2));
      *(short *)(iVar1 + 0x1906) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(iVar1 + 0x1906) ^ 0x80000000) -
                               dVar5) * (fVar3 * (fVar4 - *(float *)(param_1 + 0x1dc8)) + fVar2));
      *(short *)(iVar1 + 0x190a) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(iVar1 + 0x190a) ^ 0x80000000) -
                               dVar5) * (fVar3 * (fVar4 - *(float *)(param_1 + 0x1dc8)) + fVar2));
      *(short *)(iVar1 + 0x190c) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(iVar1 + 0x190c) ^ 0x80000000) -
                               dVar5) * (fVar3 * (fVar4 - *(float *)(param_1 + 0x1dc8)) + fVar2));
      *(short *)(iVar1 + 0x1910) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(iVar1 + 0x1910) ^ 0x80000000) -
                               dVar5) * (fVar3 * (fVar4 - *(float *)(param_1 + 0x1dc8)) + fVar2));
      *(short *)(iVar1 + 0x1912) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(iVar1 + 0x1912) ^ 0x80000000) -
                               dVar5) * (fVar3 * (fVar4 - *(float *)(param_1 + 0x1dc8)) + fVar2));
      *(short *)(iVar1 + 0x1916) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(iVar1 + 0x1916) ^ 0x80000000) -
                               dVar5) * (fVar3 * (fVar4 - *(float *)(param_1 + 0x1dc8)) + fVar2));
      *(short *)(iVar1 + 0x1918) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(iVar1 + 0x1918) ^ 0x80000000) -
                               dVar5) * (fVar3 * (fVar4 - *(float *)(param_1 + 0x1dc8)) + fVar2));
      iVar6 = iVar6 + -1;
      iVar1 = iVar1 + 0x24;
    } while (iVar6 != 0);
  }
  return;
}



// ==== 80189cf0  FUN_80189cf0 ====

void FUN_80189cf0(int param_1)

{
  (*(code *)(&PTR_FUN_80362c98)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80189d2c  FUN_80189d2c ====

void FUN_80189d2c(int param_1)

{
  (*(code *)(&PTR_FUN_80362ca8)[*(char *)(param_1 + 0x540)])(param_1,param_1 + 0x144);
  return;
}



// ==== 80189d6c  FUN_80189d6c ====

void FUN_80189d6c(int param_1,char *param_2)

{
  float fVar1;
  int iVar2;
  float local_18;
  float local_14;
  float local_10;
  
  if ((*(int *)(param_1 + 0xcc) == 0) ||
     (iVar2 = zz_006dbe0_(param_1,0,1,1), fVar1 = FLOAT_8043b004, iVar2 == 0)) {
    fVar1 = FLOAT_8043b000;
    *(undefined1 *)(param_1 + 0x540) = 2;
    *(float *)(param_1 + 0x558) = fVar1;
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(undefined2 *)(param_1 + 0x548) = 8;
    zz_0066408_(param_1,0,(float *)(param_1 + 0x518),&local_18);
    fVar1 = FLOAT_8043b008;
    *param_2 = '\0';
    if (local_14 < fVar1) {
      *param_2 = *param_2 + '\x10';
    }
    fVar1 = FLOAT_8043b010;
    if (local_18 < FLOAT_8043b00c) {
      *param_2 = *param_2 + '\b';
      local_18 = local_18 * fVar1;
    }
    if ((FLOAT_8043b014 <= local_18) || (FLOAT_8043b018 <= local_10)) {
      if (FLOAT_8043b01c <= local_10) {
        if (FLOAT_8043b020 <= local_10) {
          if (FLOAT_8043b024 <= local_10) {
            if (local_10 < FLOAT_8043b028) {
              *param_2 = *param_2 + '\x01';
            }
          }
          else {
            *param_2 = *param_2 + '\x02';
          }
        }
        else {
          *param_2 = *param_2 + '\x03';
        }
      }
      else {
        *param_2 = *param_2 + '\x04';
      }
    }
    else {
      *param_2 = *param_2 + '\x05';
    }
    *param_2 = (&DAT_80362cb4)[*param_2];
  }
  return;
}



// ==== 80189f10  FUN_80189f10 ====

void FUN_80189f10(int param_1,undefined1 *param_2)

{
  float fVar1;
  
  fVar1 = FLOAT_8043b02c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_01fc1b0_(param_1,*param_2);
  return;
}



// ==== 80189f4c  FUN_80189f4c ====

void FUN_80189f4c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043b00c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 80189fa8  FUN_80189fa8 ====

void FUN_80189fa8(int param_1)

{
  (*(code *)(&PTR_FUN_80362cd4)[*(char *)(param_1 + 0x540)])(param_1,param_1 + 0x144);
  return;
}



// ==== 80189fe8  FUN_80189fe8 ====

void FUN_80189fe8(int param_1,int param_2)

{
  bool bVar1;
  float fVar2;
  int iVar3;
  float local_18;
  float local_14;
  float local_10;
  
  if ((*(int *)(param_1 + 0xcc) == 0) || (iVar3 = zz_006dbe0_(param_1,2,1,1), iVar3 == 0)) {
    fVar2 = FLOAT_8043b000;
    *(undefined1 *)(param_1 + 0x540) = 3;
    *(float *)(param_1 + 0x558) = fVar2;
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0066408_(param_1,0,(float *)(param_1 + 0x518),&local_18);
    fVar2 = FLOAT_8043b00c;
    *(undefined1 *)(param_2 + 1) = 0;
    bVar1 = false;
    if (local_18 < fVar2) {
      local_18 = local_18 * FLOAT_8043b010;
      *(char *)(param_2 + 1) = *(char *)(param_2 + 1) + '\b';
    }
    if (local_14 <= FLOAT_8043b030) {
      if (local_14 < FLOAT_8043b040) {
        if (local_10 <= FLOAT_8043b044) {
          if (((local_14 < FLOAT_8043b048) && (local_18 < FLOAT_8043b04c)) ||
             ((local_18 < FLOAT_8043b014 && (FLOAT_8043b00c < local_10)))) {
            bVar1 = true;
            *(char *)(param_2 + 1) = *(char *)(param_2 + 1) + '\x03';
          }
        }
        else {
          bVar1 = true;
          *(char *)(param_2 + 1) = *(char *)(param_2 + 1) + '\x02';
        }
      }
    }
    else if (((FLOAT_8043b034 < local_14) && (DOUBLE_8043b038 < (double)local_10)) ||
            ((local_18 < FLOAT_8043b014 && (FLOAT_8043b00c < local_10)))) {
      bVar1 = true;
    }
    else if (local_10 < FLOAT_8043b030) {
      bVar1 = true;
      *(char *)(param_2 + 1) = *(char *)(param_2 + 1) + '\x01';
    }
    if (!bVar1) {
      *(char *)(param_2 + 1) = *(char *)(param_2 + 1) + '\x04';
    }
    fVar2 = FLOAT_8043b050;
    *(undefined *)(param_2 + 1) = (&DAT_80362ce4)[*(char *)(param_2 + 1)];
    *(float *)(param_1 + 0x558) = fVar2;
  }
  return;
}



// ==== 8018a1cc  FUN_8018a1cc ====

void FUN_8018a1cc(int param_1,int param_2)

{
  int iVar1;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = zz_018a6fc_(param_1,(int)*(char *)(param_2 + 1),1);
  if ((iVar1 == 0) && (FLOAT_8043b00c < *(float *)(param_1 + 0x558))) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 8018a23c  FUN_8018a23c ====

void FUN_8018a23c(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043b050;
  fVar1 = FLOAT_8043b02c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  zz_018a6fc_(param_1,(int)*(char *)(param_2 + 1),1);
  FUN_801f2bf8((double)FLOAT_8043b00c,param_1,0,*(char *)(param_2 + 1));
  return;
}



// ==== 8018a2b0  FUN_8018a2b0 ====

void FUN_8018a2b0(int param_1,int param_2)

{
  float fVar1;
  
  if (FLOAT_8043b00c < *(float *)(param_1 + 0x55c)) {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
    zz_018a6fc_(param_1,(int)*(char *)(param_2 + 1),1);
  }
  fVar1 = FLOAT_8043b00c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 8018a348  FUN_8018a348 ====

void FUN_8018a348(int param_1)

{
  (*(code *)(&PTR_LAB_80362d04)[*(char *)(param_1 + 0x540)])(param_1,param_1 + 0x144);
  return;
}



// ==== 8018a3c0  FUN_8018a3c0 ====

void FUN_8018a3c0(int param_1)

{
  float fVar1;
  int iVar2;
  int unaff_r30;
  int iVar3;
  
  iVar3 = 0;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  do {
    iVar2 = zz_018a6fc_(param_1,iVar3,0);
    fVar1 = FLOAT_8043b054;
    if (iVar3 == 0) {
      unaff_r30 = iVar2;
    }
    iVar3 = iVar3 + 1;
  } while (iVar3 < 8);
  if ((unaff_r30 == 0) && (FLOAT_8043b00c < *(float *)(param_1 + 0x558))) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  return;
}



// ==== 8018a464  FUN_8018a464 ====

void FUN_8018a464(int param_1,char *param_2)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  fVar2 = FLOAT_8043b00c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (fVar2 < *(float *)(param_1 + 0x558)) {
    return;
  }
  iVar5 = 0;
  *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x564) = *(float *)(param_1 + 0x564) - *(float *)(param_1 + 0x1dc8);
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x01') {
LAB_8018a590:
    iVar5 = 1;
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) && (*(float *)(param_1 + 0x560) <= fVar2)) {
    iVar4 = 0;
    do {
      *param_2 = (&DAT_80362d14)[iVar4 + *(short *)(param_1 + 0x54c) * 2];
      if (-1 < *param_2) {
        iVar3 = zz_006dbe0_(param_1,0,1,1);
        if (iVar3 == 0) {
          zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),0);
        }
        else {
          zz_01fc1b0_(param_1,*param_2);
        }
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 2);
    *(float *)(param_1 + 0x560) = FLOAT_8043b058;
    *(short *)(param_1 + 0x54c) = *(short *)(param_1 + 0x54c) + 1;
    if (10 < *(short *)(param_1 + 0x54c)) {
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      goto LAB_8018a590;
    }
  }
  cVar1 = *(char *)(param_1 + 0x543);
  if (cVar1 != '\x01') {
    if ((('\0' < cVar1) || (cVar1 < '\0')) || (FLOAT_8043b00c < *(float *)(param_1 + 0x564)))
    goto LAB_8018a670;
    iVar4 = 0;
    do {
      param_2[1] = (&DAT_80362d2c)[iVar4 + *(short *)(param_1 + 0x54e) * 2];
      if (-1 < param_2[1]) {
        iVar3 = zz_006dbe0_(param_1,2,1,1);
        if (iVar3 == 0) {
          zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),2);
        }
        else {
          FUN_801f2bf8((double)FLOAT_8043b00c,param_1,0,param_2[1]);
        }
      }
      iVar4 = iVar4 + 1;
    } while (iVar4 < 2);
    *(float *)(param_1 + 0x564) = FLOAT_8043b058;
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) + 1;
    if (*(short *)(param_1 + 0x54e) < 10) goto LAB_8018a670;
    *(char *)(param_1 + 0x543) = *(char *)(param_1 + 0x543) + '\x01';
  }
  iVar5 = iVar5 + 1;
LAB_8018a670:
  fVar2 = FLOAT_8043b05c;
  if (iVar5 == 2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
  }
  return;
}



// ==== 8018a6a0  FUN_8018a6a0 ====

void FUN_8018a6a0(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043b00c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 8018a6fc  zz_018a6fc_ ====

undefined4 zz_018a6fc_(int param_1,int param_2,int param_3)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  
  iVar10 = (int)(char)(&DAT_80362d40)[param_2 * 2];
  iVar9 = (int)(char)(&DAT_80362d41)[param_2 * 2];
  if (param_3 != 0) {
    iVar7 = param_1 + 0x24;
    iVar8 = 6;
    iVar11 = 0xc;
    do {
      dVar5 = DOUBLE_8043aff8;
      fVar4 = FLOAT_8043aff4;
      fVar3 = FLOAT_8043aff0;
      fVar2 = FLOAT_8043afec;
      if ((iVar10 != iVar8) && (iVar9 != iVar8)) {
        *(short *)(iVar7 + 0x18d4) =
             (short)(int)((float)((double)CONCAT44(0x43300000,
                                                   (int)*(short *)(iVar7 + 0x18d4) ^ 0x80000000) -
                                 DOUBLE_8043aff8) *
                         (FLOAT_8043aff0 * (FLOAT_8043aff4 - *(float *)(param_1 + 0x1dc8)) +
                         FLOAT_8043afec));
        *(short *)(iVar7 + 0x18d6) =
             (short)(int)((float)((double)CONCAT44(0x43300000,
                                                   (int)*(short *)(iVar7 + 0x18d6) ^ 0x80000000) -
                                 dVar5) * (fVar3 * (fVar4 - *(float *)(param_1 + 0x1dc8)) + fVar2));
      }
      iVar7 = iVar7 + 6;
      iVar8 = iVar8 + 1;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
  }
  cVar1 = (&DAT_80435688)[param_2];
  if (cVar1 == '\x02') {
    FUN_8018a930((double)FLOAT_8043b060,param_1,iVar10,1,(short *)&DAT_80362d68);
    uVar6 = FUN_8006cc90((double)FLOAT_8043b060,param_1,iVar9,iVar10,(short *)&DAT_80362d70);
    return uVar6;
  }
  if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      uVar6 = FUN_8006cc90((double)FLOAT_8043b060,param_1,iVar10,1,(short *)&DAT_80362d50);
      return uVar6;
    }
    if (-1 < cVar1) {
      FUN_8006cc90((double)FLOAT_8043b060,param_1,iVar10,1,(short *)&DAT_80362d58);
      uVar6 = FUN_8006cc90((double)FLOAT_8043b060,param_1,iVar9,iVar10,(short *)&DAT_80362d60);
      return uVar6;
    }
  }
  else if (cVar1 < '\x04') {
    FUN_8018a930((double)FLOAT_8043b060,param_1,iVar10,1,(short *)&DAT_80362d78);
    uVar6 = FUN_8006cc90((double)FLOAT_8043b060,param_1,iVar9,iVar10,(short *)&DAT_80362d80);
    return uVar6;
  }
  return 1;
}



// ==== 8018a930  FUN_8018a930 ====

/* WARNING: Removing unreachable block (ram,0x8018add4) */
/* WARNING: Removing unreachable block (ram,0x8018a940) */

undefined4 FUN_8018a930(double param_1,int param_2,int param_3,int param_4,short *param_5)

{
  float fVar1;
  float fVar2;
  float fVar3;
  short sVar4;
  undefined4 uVar5;
  int iVar6;
  short sVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  double dVar11;
  double dVar12;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  float local_7c;
  float local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  double local_38;
  undefined8 local_30;
  
  dVar12 = DOUBLE_8043aff8;
  fVar3 = FLOAT_8043aff4;
  fVar2 = FLOAT_8043aff0;
  fVar1 = FLOAT_8043afec;
  if (*(int *)(param_2 + 0xcc) == 0) {
    uVar5 = 1;
    iVar8 = param_2 + param_3 * 6;
    *(short *)(iVar8 + 0x18d4) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(iVar8 + 0x18d4) ^ 0x80000000) -
                             DOUBLE_8043aff8) *
                     (FLOAT_8043aff0 * (FLOAT_8043aff4 - *(float *)(param_2 + 0x1dc8)) +
                     FLOAT_8043afec));
    local_38 = (double)(CONCAT44(0x43300000,(int)*(short *)(iVar8 + 0x18d6)) ^ 0x80000000);
    *(short *)(iVar8 + 0x18d6) =
         (short)(int)((float)(local_38 - dVar12) *
                     (fVar2 * (fVar3 - *(float *)(param_2 + 0x1dc8)) + fVar1));
  }
  else {
    iVar10 = param_2 + param_4 * 0x30;
    local_78 = *(float *)(iVar10 + 0x8d4);
    iVar8 = param_2 + param_3 * 0x30;
    local_68 = *(undefined4 *)(iVar10 + 0x8e4);
    local_58 = *(undefined4 *)(iVar10 + 0x8f4);
    local_74 = *(undefined4 *)(iVar10 + 0x8d8);
    local_64 = *(undefined4 *)(iVar10 + 0x8e8);
    local_54 = *(undefined4 *)(iVar10 + 0x8f8);
    local_70 = *(undefined4 *)(iVar10 + 0x8dc);
    local_60 = *(undefined4 *)(iVar10 + 0x8ec);
    local_50 = *(undefined4 *)(iVar10 + 0x8fc);
    local_6c = *(undefined4 *)(iVar8 + 0x8e0);
    local_5c = *(undefined4 *)(iVar8 + 0x8f0);
    local_4c = *(undefined4 *)(iVar8 + 0x900);
    local_84 = *(float *)(iVar8 + 0x8dc);
    local_80 = *(float *)(iVar8 + 0x8ec);
    local_7c = *(float *)(iVar8 + 0x8fc);
    zz_0066454_(param_2,param_4,&local_84,&local_84);
    zz_004516c_(&local_78,(float *)(param_2 + 0x518),&local_90);
    iVar8 = FUN_800452a0((double)local_80,(double)local_7c);
    dVar12 = (double)(local_80 * local_80 + local_7c * local_7c);
    if ((double)FLOAT_8043b00c < dVar12) {
      dVar11 = 1.0 / SQRT(dVar12);
      dVar11 = DOUBLE_8043b068 * dVar11 * -(dVar12 * dVar11 * dVar11 - DOUBLE_8043b070);
      dVar11 = DOUBLE_8043b068 * dVar11 * -(dVar12 * dVar11 * dVar11 - DOUBLE_8043b070);
      dVar12 = (double)(float)(dVar12 * DOUBLE_8043b068 * dVar11 *
                                        -(dVar12 * dVar11 * dVar11 - DOUBLE_8043b070));
    }
    iVar10 = FUN_800452a0((double)local_84,dVar12);
    iVar6 = FUN_800452a0((double)local_8c,(double)local_88);
    sVar4 = -(short)iVar6;
    dVar12 = (double)(local_8c * local_8c + local_88 * local_88);
    if ((double)FLOAT_8043b00c < dVar12) {
      dVar11 = 1.0 / SQRT(dVar12);
      dVar11 = DOUBLE_8043b068 * dVar11 * -(dVar12 * dVar11 * dVar11 - DOUBLE_8043b070);
      dVar11 = DOUBLE_8043b068 * dVar11 * -(dVar12 * dVar11 * dVar11 - DOUBLE_8043b070);
      dVar12 = (double)(float)(dVar12 * DOUBLE_8043b068 * dVar11 *
                                        -(dVar12 * dVar11 * dVar11 - DOUBLE_8043b070));
    }
    iVar6 = FUN_800452a0((double)local_90,dVar12);
    sVar7 = (short)iVar6;
    if (sVar4 < 1) {
      if (sVar4 <= param_5[2]) {
        sVar4 = param_5[2];
      }
    }
    else if (param_5[3] <= sVar4) {
      sVar4 = param_5[3];
    }
    if (sVar7 < 1) {
      if (sVar7 <= param_5[1]) {
        sVar7 = param_5[1];
      }
    }
    else if (*param_5 <= sVar7) {
      sVar7 = *param_5;
    }
    dVar12 = (double)FLOAT_8043aff4;
    if ((param_1 <= dVar12) && (dVar12 = param_1, param_1 < (double)FLOAT_8043b00c)) {
      dVar12 = (double)FLOAT_8043b00c;
    }
    fVar1 = (float)((double)*(float *)(param_2 + 0x1dc8) * dVar12);
    if ((param_5[2] == -0x7fff) && (param_5[3] == 0x7fff)) {
      uVar9 = (int)sVar4 - (int)(short)-(short)iVar8;
      if ((int)uVar9 < 0x8001) {
        if ((int)uVar9 < -0x8000) {
          uVar9 = uVar9 + 0x10000;
        }
      }
      else {
        uVar9 = uVar9 - 0x10000;
      }
      local_30 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
      sVar4 = (short)(int)((float)(local_30 - DOUBLE_8043aff8) * fVar1);
    }
    else {
      local_30 = (double)(CONCAT44(0x43300000,(int)sVar4 - (int)(short)-(short)iVar8) ^ 0x80000000);
      sVar4 = (short)(int)(fVar1 * (float)(local_30 - DOUBLE_8043aff8));
    }
    if ((param_5[1] == -0x7fff) && (*param_5 == 0x7fff)) {
      uVar9 = (int)sVar7 - (int)(short)iVar10;
      if ((int)uVar9 < 0x8001) {
        if ((int)uVar9 < -0x8000) {
          uVar9 = uVar9 + 0x10000;
        }
      }
      else {
        uVar9 = uVar9 - 0x10000;
      }
      local_30 = (double)CONCAT44(0x43300000,uVar9 ^ 0x80000000);
      sVar7 = (short)(int)((float)(local_30 - DOUBLE_8043aff8) * fVar1);
    }
    else {
      local_30 = (double)(CONCAT44(0x43300000,(int)sVar7 - (int)(short)iVar10) ^ 0x80000000);
      sVar7 = (short)(int)(fVar1 * (float)(local_30 - DOUBLE_8043aff8));
    }
    iVar8 = param_2 + param_3 * 6;
    *(short *)(iVar8 + 0x18d4) = *(short *)(iVar8 + 0x18d4) + sVar4;
    *(short *)(iVar8 + 0x18d6) = *(short *)(iVar8 + 0x18d6) + sVar7;
    if ((sVar4 == 0) && (sVar7 == 0)) {
      uVar5 = 1;
    }
    else {
      uVar5 = 0;
    }
  }
  return uVar5;
}



// ==== 8018adf0  zz_018adf0_ ====

void zz_018adf0_(int param_1,int param_2,undefined4 param_3)

{
  short sVar1;
  int iVar2;
  undefined1 *puVar3;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((sVar1 == 0x613) || (sVar1 == 0x614)) || (sVar1 == 0x627)) || (sVar1 == 0x628)) &&
     (puVar3 = zz_0088aa0_(param_1,2,0,0,4), puVar3 != (undefined1 *)0x0)) {
    *puVar3 = 1;
    iVar2 = param_2 * 4;
    puVar3[0x11] = (&DAT_803630f8)[iVar2];
    puVar3[0x12] = (&DAT_803630f9)[iVar2];
    puVar3[0x13] = (&DAT_803630fa)[iVar2];
    puVar3[0x83] = 0x18;
    *(code **)(puVar3 + 0xc) = FUN_8018af44;
    *(code **)(puVar3 + 0x10c) = FUN_8018ba74;
    *(int *)(puVar3 + 0x8c) = param_1;
    *(undefined4 *)(puVar3 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar3 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar3[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar3[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar3[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar3 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar3 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar3 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar3 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar3 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar3 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar3 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar3 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar3 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar3[0xd0] = *(undefined1 *)(param_1 + 0xd0);
    *(undefined4 *)(puVar3 + 0x160) = param_3;
  }
  return;
}



// ==== 8018af44  FUN_8018af44 ====

void FUN_8018af44(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80363138)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8018af98  FUN_8018af98 ====

void FUN_8018af98(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  undefined8 uVar8;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(undefined1 *)(param_9 + 0x19) = 0;
  *(undefined1 *)(param_9 + 0x1a) = 0;
  iVar7 = *(int *)(param_9 + 0x90);
  if (*(char *)(param_9 + 0x12) == '\0') {
    *(undefined *)(param_9 + 0x89) = (&DAT_80435690)[*(char *)(param_9 + 0x13)];
  }
  else {
    *(undefined1 *)(param_9 + 0x89) = 1;
  }
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar8 = zz_0089100_(param_9,(int)*(char *)(iVar7 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_8043b078;
  *(undefined *)(param_9 + 0x84) =
       (&DAT_8043569c)[*(char *)(param_9 + 0x12) * 4 + (int)*(char *)(param_9 + 0x13)];
  puVar6 = (undefined4 *)
           (&DAT_80363098 + *(char *)(param_9 + 0x13) * 0xc + *(char *)(param_9 + 0x12) * 0x30);
  uVar2 = puVar6[1];
  *(undefined4 *)(param_9 + 100) = *puVar6;
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = puVar6[2];
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80435694 + *(char *)(param_9 + 0x13) * 2);
  *(float *)(param_9 + 0x164) = fVar1;
  *(undefined1 *)(param_9 + 0x144) = 0;
  iVar3 = zz_0006f98_(iVar7);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),
                      *(int *)(&DAT_80363078 + *(char *)(param_9 + 0x11) * 8),iVar3 + 0xc28,puVar6,
                      in_r8,in_r9,in_r10);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe8),
                      *(int *)(&DAT_8036307c + *(char *)(param_9 + 0x11) * 8),iVar3 + 0xc28,puVar6,
                      in_r8,in_r9,in_r10);
  iVar5 = iVar3 + 0xc28;
  iVar4 = *(int *)(&DAT_80363078 + *(char *)(param_9 + 0x11) * 8);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),iVar4,iVar5,puVar6,in_r8,
                      in_r9,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar4,iVar5,puVar6,in_r8,in_r9,in_r10);
  uVar8 = zz_0007cac_((double)FLOAT_8043b07c,*(int *)(param_9 + 0xe4));
  iVar5 = iVar3 + 0xc28;
  iVar4 = *(int *)(&DAT_8036307c + *(char *)(param_9 + 0x11) * 8);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xec),iVar4,iVar5,puVar6,in_r8,
                      in_r9,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,iVar4,iVar5,puVar6,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043b07c,*(int *)(param_9 + 0xec));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(iVar7 + 0x8e0);
  *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(iVar7 + 0x8f0);
  *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(iVar7 + 0x900);
  *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(param_9 + 0x148);
  *(undefined4 *)(param_9 + 0x158) = *(undefined4 *)(param_9 + 0x14c);
  *(undefined4 *)(param_9 + 0x15c) = *(undefined4 *)(param_9 + 0x150);
  zz_018b1ec_(param_9);
  return;
}



// ==== 8018b1ec  zz_018b1ec_ ====

void zz_018b1ec_(int param_1)

{
  byte bVar1;
  char cVar2;
  float fVar3;
  undefined4 uVar4;
  uint uVar5;
  undefined4 *puVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  float *pfVar10;
  bool bVar11;
  double dVar12;
  double dVar13;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  float local_4c;
  undefined4 local_48;
  undefined4 local_44;
  float afStack_40 [3];
  float local_34;
  float local_30;
  float local_2c;
  double local_28;
  double local_20;
  
  fVar3 = FLOAT_8043b080;
  iVar8 = *(int *)(param_1 + 0x90);
  bVar1 = **(byte **)(param_1 + 0x160);
  if ((bVar1 & 0x40) != 0) {
    **(byte **)(param_1 + 0x160) = bVar1 & 0xbf;
    *(float *)(param_1 + 0x164) = fVar3;
  }
  fVar3 = FLOAT_8043b078;
  *(float *)(param_1 + 0x164) = (float)((double)*(float *)(param_1 + 0x164) + DOUBLE_8043b088);
  if (fVar3 < *(float *)(param_1 + 0x164)) {
    *(float *)(param_1 + 0x164) = fVar3;
  }
  if (*(char *)(param_1 + 0x12) == '\0') {
    return;
  }
  bVar11 = false;
  bVar1 = *(byte *)(iVar8 + 0x6e8);
  if (*(char *)(param_1 + 0x13) < '\x02') {
    if (*(char *)(param_1 + 0x144) == '\x01') {
      if ((bVar1 & 1) == 0) {
        bVar11 = true;
      }
    }
    else if ((bVar1 & 1) != 0) {
      bVar11 = true;
    }
  }
  else if (*(char *)(param_1 + 0x144) == '\x02') {
    if ((bVar1 & 2) == 0) {
      bVar11 = true;
    }
  }
  else if ((bVar1 & 2) != 0) {
    bVar11 = true;
  }
  if (bVar11) {
    if (*(char *)(param_1 + 0x13) < '\x02') {
      if ((bVar1 & 1) == 0) {
        iVar9 = 1;
        *(undefined1 *)(param_1 + 0x144) = 0;
        bVar11 = true;
      }
      else {
        iVar9 = 0;
        *(undefined1 *)(param_1 + 0x144) = 1;
        bVar11 = false;
      }
    }
    else if ((bVar1 & 2) == 0) {
      iVar9 = 1;
      *(undefined1 *)(param_1 + 0x144) = 0;
      bVar11 = true;
    }
    else {
      iVar9 = 0;
      *(undefined1 *)(param_1 + 0x144) = 2;
      bVar11 = false;
    }
    if (1 < *(char *)(param_1 + 0x13)) {
      iVar7 = iVar8 + (char)(&DAT_80435690)[*(char *)(param_1 + 0x13)] * 0x30;
      local_4c = *(float *)(iVar7 + 0x8d8);
      local_48 = *(undefined4 *)(iVar7 + 0x8e8);
      local_44 = *(undefined4 *)(iVar7 + 0x8f8);
      local_58 = *(float *)(iVar8 + 0x908);
      local_54 = *(undefined4 *)(iVar8 + 0x918);
      local_50 = *(undefined4 *)(iVar8 + 0x928);
      gnt4_PSVECNormalize_bl(&local_4c,&local_4c);
      gnt4_PSVECNormalize_bl(&local_58,&local_58);
      dVar13 = gnt4_PSQUATDotProduct_bl(&local_4c,&local_58);
      dVar12 = (double)FLOAT_8043b078;
      if ((dVar13 <= dVar12) && (dVar12 = dVar13, dVar13 < (double)FLOAT_8043b090)) {
        dVar12 = (double)FLOAT_8043b090;
      }
      if ((*(uint *)(iVar8 + 0x5e0) & 0x20000000) == 0) {
        if (bVar11) {
          dVar12 = (double)gnt4_acos_bl(dVar12);
          local_20 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x70)) ^ 0x80000000);
          iVar7 = (int)(FLOAT_8043b094 * (float)dVar12 + (float)(local_20 - DOUBLE_8043b0b8));
          local_28 = (double)(longlong)iVar7;
          *(short *)(param_1 + 0x70) = (short)iVar7;
        }
        else {
          dVar12 = (double)gnt4_acos_bl(dVar12);
          local_28 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x70)) ^ 0x80000000);
          iVar7 = (int)-(FLOAT_8043b094 * (float)dVar12 - (float)(local_28 - DOUBLE_8043b0b8));
          local_20 = (double)(longlong)iVar7;
          *(short *)(param_1 + 0x70) = (short)iVar7;
        }
      }
    }
    if (iVar9 == 0) {
      *(undefined *)(param_1 + 0x89) = (&DAT_80435690)[*(char *)(param_1 + 0x13)];
    }
    else {
      *(undefined1 *)(param_1 + 0x89) = 1;
    }
    *(undefined *)(param_1 + 0x84) = (&DAT_8043569c)[iVar9 * 4 + (int)*(char *)(param_1 + 0x13)];
    puVar6 = (undefined4 *)(&DAT_80363098 + *(char *)(param_1 + 0x13) * 0xc + iVar9 * 0x30);
    uVar4 = puVar6[1];
    *(undefined4 *)(param_1 + 100) = *puVar6;
    *(undefined4 *)(param_1 + 0x68) = uVar4;
    *(undefined4 *)(param_1 + 0x6c) = puVar6[2];
  }
  pfVar10 = (float *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(iVar8 + 0x8e0);
  *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(iVar8 + 0x8f0);
  *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(iVar8 + 0x900);
  cVar2 = *(char *)(param_1 + 0x19);
  if (cVar2 != '\x01') {
    if (cVar2 < '\x01') {
      if (-1 < cVar2) {
        uVar5 = *(uint *)(iVar8 + 0x5e0);
        if ((uVar5 & 0x2000000) == 0) {
          if (*(char *)(iVar8 + 0x6cb) == '\0') {
            if (((*(char *)(iVar8 + 0x1db) != '\0') && ((uVar5 & 0x10) == 0)) &&
               ((uVar5 & 0x20) == 0)) {
              *(float *)(param_1 + 0x154) = *pfVar10;
              *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x14c);
              *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x150);
              return;
            }
            if ((*(char *)(iVar8 + 0x1dd) == '\0') || (*(char *)(iVar8 + 0x1db) != '\0')) {
              gnt4_PSVECSubtract_bl(pfVar10,(float *)(param_1 + 0x154),&local_34);
            }
            else {
              dVar12 = gnt4_PSVECSquareMag_bl((float *)(iVar8 + 0x1cc));
              if (dVar12 <= (double)FLOAT_8043b080) {
                local_34 = FLOAT_8043b080;
                local_30 = FLOAT_8043b078;
                local_2c = FLOAT_8043b080;
              }
              else {
                gnt4_PSQUATScale_bl((double)FLOAT_8043b090,(float *)(iVar8 + 0x1cc),&local_34);
              }
              gnt4_PSVECSubtract_bl(pfVar10,(float *)(param_1 + 0x154),afStack_40);
              gnt4_PSVECAdd_bl(&local_34,afStack_40,&local_34);
            }
            dVar12 = gnt4_PSVECSquareMag_bl(&local_34);
            if ((double)FLOAT_8043b080 < dVar12) {
              zz_00451b8_((float *)(iVar8 + 0x8d4),&local_34,&local_34);
              if ((*(uint *)(iVar8 + 0x5e0) & 0x40) != 0) {
                if (local_2c < FLOAT_8043b080) {
                  local_2c = local_2c - FLOAT_8043b098;
                }
                else {
                  local_2c = local_2c + FLOAT_8043b098;
                }
              }
              local_2c = FLOAT_8043b09c * local_2c;
              fVar3 = FLOAT_8043b0a0;
              if ((local_2c < FLOAT_8043b0a0) && (fVar3 = local_2c, local_2c <= FLOAT_8043b0a4)) {
                fVar3 = FLOAT_8043b0a4;
              }
              uVar5 = *(uint *)(iVar8 + 0x5e0);
              if (((uVar5 & 0x20) != 0) || ((uVar5 & 0x40) != 0)) {
                fVar3 = fVar3 * FLOAT_8043b0a8;
              }
              if ((*(byte *)(param_1 + 0x144) & 3) == 0) {
                if ((uVar5 & 0x20000000) == 0) {
                  local_20 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x70)) ^
                                     0x80000000);
                  *(short *)(param_1 + 0x70) =
                       (short)(int)(FLOAT_8043b0ac * fVar3 + (float)(local_20 - DOUBLE_8043b0b8));
                }
              }
              else if ((uVar5 & 0x20000000) == 0) {
                if (*(char *)(param_1 + 0x13) < '\x02') {
                  local_20 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x70)) ^
                                     0x80000000);
                  *(short *)(param_1 + 0x70) =
                       (short)(int)-(FLOAT_8043b0ac * fVar3 - (float)(local_20 - DOUBLE_8043b0b8));
                }
                else {
                  local_20 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x70)) ^
                                     0x80000000);
                  *(short *)(param_1 + 0x70) =
                       (short)(int)(FLOAT_8043b0ac * fVar3 + (float)(local_20 - DOUBLE_8043b0b8));
                }
              }
            }
          }
          else {
            *(undefined1 *)(param_1 + 0x19) = 2;
            *(undefined1 *)(param_1 + 0x1a) = 0;
          }
        }
        else {
          *(undefined1 *)(param_1 + 0x19) = 1;
          *(undefined1 *)(param_1 + 0x1a) = 0;
        }
      }
    }
    else if (cVar2 < '\x03') {
      if (*(char *)(iVar8 + 0x6cb) == '\0') {
        *(undefined1 *)(param_1 + 0x19) = 0;
      }
      else {
        cVar2 = *(char *)(param_1 + 0x1a);
        if (cVar2 == '\x02') {
          *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
          if (*(short *)(param_1 + 0x1c) < 1) {
            *(undefined1 *)(param_1 + 0x1a) = 3;
          }
          if ((*(uint *)(iVar8 + 0x5e0) & 0x20000000) == 0) {
            local_20 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x70)) ^ 0x80000000);
            *(short *)(param_1 + 0x70) =
                 (short)(int)((float)(local_20 - DOUBLE_8043b0b8) + FLOAT_8043b0b4);
          }
        }
        else if (cVar2 < '\x02') {
          if (cVar2 == '\0') {
            if ((*(uint *)(iVar8 + 0x5e0) & 0x40) == 0) {
              *(undefined1 *)(param_1 + 0x1a) = 1;
              *(undefined2 *)(param_1 + 0x1c) = 0x1e;
            }
          }
          else if ((-1 < cVar2) &&
                  (*(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1,
                  *(short *)(param_1 + 0x1c) < 1)) {
            *(undefined1 *)(param_1 + 0x1a) = 2;
            *(undefined2 *)(param_1 + 0x1c) = 0x30;
          }
        }
      }
    }
    goto LAB_8018ba0c;
  }
  uVar5 = *(uint *)(iVar8 + 0x5e0);
  if ((uVar5 & 0x1000000) == 0) {
    *(undefined1 *)(param_1 + 0x19) = 0;
    goto LAB_8018ba0c;
  }
  cVar2 = *(char *)(param_1 + 0x1a);
  if (cVar2 == '\x02') {
LAB_8018b87c:
    fVar3 = *(float *)(param_1 + 0xd4) - *(float *)(iVar8 + 0x768);
    bVar11 = FLOAT_8043b080 < fVar3;
    *(float *)(param_1 + 0xd4) = fVar3;
    if (bVar11) {
      if ((*(uint *)(iVar8 + 0x5e0) & 0x20000000) == 0) {
        if (*(char *)(param_1 + 0x13) < '\x02') {
          *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + -0x300;
        }
        else {
          *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0x300;
        }
      }
      goto LAB_8018ba0c;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  }
  else {
    if (cVar2 < '\x02') {
      if (cVar2 == '\0') {
        if ((uVar5 & 0x2000000) != 0) {
          if ((uVar5 & 0x20000000) == 0) {
            if (*(char *)(param_1 + 0x13) < '\x02') {
              *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + -0x300;
            }
            else {
              *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0x300;
            }
          }
          goto LAB_8018ba0c;
        }
        *(undefined1 *)(param_1 + 0x1a) = 1;
      }
      else if (cVar2 < '\0') goto LAB_8018ba0c;
      if ((*(uint *)(iVar8 + 0x5e0) & 0x4000000) != 0) {
        *(float *)(param_1 + 0xd4) = FLOAT_8043b0b0;
      }
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      goto LAB_8018b87c;
    }
    if ('\x03' < cVar2) goto LAB_8018ba0c;
  }
  if ((*(uint *)(iVar8 + 0x5e0) & 0x20000000) == 0) {
    if (*(char *)(param_1 + 0x13) < '\x02') {
      *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + -0x1200;
    }
    else {
      *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0x1200;
    }
  }
LAB_8018ba0c:
  *(float *)(param_1 + 0x154) = *pfVar10;
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x14c);
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x150);
  return;
}



// ==== 8018ba54  FUN_8018ba54 ====

void FUN_8018ba54(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8018ba74  FUN_8018ba74 ====

void FUN_8018ba74(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  undefined8 uVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  iVar2 = *(int *)(param_1 + 0x90);
  if ((**(byte **)(param_1 + 0x160) & 1) == 0) {
    return;
  }
  dVar6 = (double)*(float *)(param_1 + 0x164);
  if ((double)FLOAT_8043b080 < dVar6) {
    if ((*(char *)(iVar2 + 0xae) == '\0') && (*(char *)(iVar2 + 0x3ec) != '\x04')) {
      iVar4 = 0;
      uVar3 = 1;
    }
    else {
      iVar4 = 1;
      uVar3 = 0x44;
    }
    dVar8 = dVar6;
    gnt4_PSMTXScale_bl(dVar6,dVar6,dVar6,afStack_48);
    pfVar1 = afStack_48;
    uVar7 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar1,pfVar1);
    iVar5 = *(int *)(param_1 + iVar4 * 4 + 0xe0);
    zz_00076d0_(uVar7,dVar6,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,iVar5,afStack_48,(undefined *)pfVar1
                ,param_4,param_5,param_6,param_7,param_8);
    uVar7 = zz_00097b4_(iVar5,uVar3);
    if (((*(uint *)(iVar2 + 0x5e0) & 2) != 0) && (*(char *)(iVar2 + 0x584) == '\x01')) {
      iVar2 = *(int *)(param_1 + iVar4 * 4 + 0xe8);
      zz_00076d0_(uVar7,dVar6,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,iVar2,afStack_48,
                  (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(iVar2,uVar3);
    }
    return;
  }
  return;
}



// ==== 8018bc90  FUN_8018bc90 ====

void FUN_8018bc90(int param_1)

{
  int iVar1;
  
  zz_00c74ec_(param_1,0x26);
  zz_00c74ec_(param_1,0x27);
  if (*(short *)(param_1 + 1000) == 0x614) {
    iVar1 = 0;
    do {
      zz_018adf0_(param_1,iVar1 + 4,param_1 + iVar1 + 0x144);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 4);
  }
  else if (*(short *)(param_1 + 1000) == 0x628) {
    iVar1 = 0;
    do {
      zz_018adf0_(param_1,iVar1 + 0xc,param_1 + iVar1 + 0x144);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 4);
  }
  *(undefined1 *)(param_1 + 0x144) = 1;
  *(undefined1 *)(param_1 + 0x145) = 1;
  *(undefined1 *)(param_1 + 0x146) = 1;
  *(undefined1 *)(param_1 + 0x147) = 1;
  return;
}



// ==== 8018bd6c  FUN_8018bd6c ====

void FUN_8018bd6c(int param_1)

{
  float fVar1;
  double dVar2;
  
  zz_006d520_(param_1,(float *)&DAT_803653c0);
  dVar2 = DOUBLE_8043b0c8;
  fVar1 = FLOAT_8043b0c0;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x1976) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1976) ^ 0x80000000) -
                             DOUBLE_8043b0c8) * FLOAT_8043b0c0);
    *(short *)(param_1 + 0x197a) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x197a) ^ 0x80000000) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             dVar2) * fVar1);
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x10) != 0) {
    zz_00f0104_(param_1,0x1e,6);
  }
  return;
}



// ==== 8018be58  FUN_8018be58 ====

void FUN_8018be58(char *param_1)

{
  if ((*(short *)(param_1 + 1000) == 0x614) && ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0)) {
    zz_006a8c0_(param_1,0x613);
    zz_005f00c_((int)param_1);
    zz_017a608_((int)param_1);
  }
  return;
}



// ==== 8018bec4  FUN_8018bec4 ====

void FUN_8018bec4(int param_1)

{
  (*(code *)(&PTR_FUN_803653f0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8018bf00  FUN_8018bf00 ====

void FUN_8018bf00(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  *(short *)(param_9 + 0x18da) = *(short *)(param_9 + 0x18da) >> 1;
  zz_018bf2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8018bf2c  zz_018bf2c_ ====

void zz_018bf2c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  char cVar3;
  int iVar2;
  short *psVar4;
  undefined4 uVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar6;
  
  fVar1 = FLOAT_8043b0d0;
  if (*(char *)(param_9 + 0x540) == '\0') {
    *(undefined1 *)(param_9 + 0x540) = 1;
    *(float *)(param_9 + 0x558) = fVar1;
    *(undefined1 *)(param_9 + 0x6ef) = 5;
  }
  psVar4 = (short *)(param_9 + 0x197a);
  uVar5 = 0;
  zz_006eae0_(param_9,(short *)(param_9 + 0x1976),psVar4,0);
  dVar6 = (double)*(float *)(param_9 + 0x558);
  if (dVar6 <= (double)FLOAT_8043b0d4) {
    *(float *)(param_9 + 0x558) = FLOAT_8043b0d8;
    cVar3 = *(char *)(param_9 + 0x6ef) + -1;
    *(char *)(param_9 + 0x6ef) = cVar3;
    if (-1 < cVar3) {
      psVar4 = (short *)0x1;
      uVar5 = 0;
      iVar2 = zz_006dbe0_(param_9,0,1,0);
      if (iVar2 != 0) {
        dVar6 = (double)zz_006bf80_(param_9);
        psVar4 = (short *)0x1;
        uVar5 = 1;
        iVar2 = zz_006dbe0_(param_9,0,1,1);
        if (iVar2 != 0) {
          if (*(short *)(param_9 + 1000) == 0x614) {
            zz_0082824_(param_9,0x34);
            dVar6 = (double)zz_0082824_(param_9,0x35);
          }
          else if (*(short *)(param_9 + 1000) == 0x628) {
            zz_0082824_(param_9,0x4f);
            dVar6 = (double)zz_0082824_(param_9,0x50);
          }
        }
        goto LAB_8018c074;
      }
    }
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,4,psVar4,uVar5
                ,in_r7,in_r8,in_r9,in_r10);
    *(float *)(param_9 + 0x694) = FLOAT_8043b0d8 + *(float *)(param_9 + 0x1dc8);
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar6 - (double)*(float *)(param_9 + 0x1dc8));
LAB_8018c074:
    zz_0048d54_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,psVar4,uVar5
                ,in_r7,in_r8,in_r9,in_r10);
  }
  return;
}



// ==== 8018c094  FUN_8018c094 ====

void FUN_8018c094(char *param_1)

{
  param_1[0x581] = '\x03';
  zz_006a8c0_(param_1,0x613);
  zz_017a608_((int)param_1);
  return;
}



// ==== 8018c0d8  FUN_8018c0d8 ====

void FUN_8018c0d8(int param_1)

{
  zz_018c0f8_(param_1);
  return;
}



// ==== 8018c0f8  zz_018c0f8_ ====

void zz_018c0f8_(int param_1)

{
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  zz_017a374_(param_1);
  return;
}



// ==== 8018c138  FUN_8018c138 ====

void FUN_8018c138(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  *(short *)(param_9 + 0x18da) = *(short *)(param_9 + 0x18da) >> 1;
  zz_018c164_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8018c164  zz_018c164_ ====

void zz_018c164_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  char cVar3;
  int iVar2;
  short *psVar4;
  undefined4 uVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar6;
  
  fVar1 = FLOAT_8043b0d0;
  if (*(char *)(param_9 + 0x540) == '\0') {
    *(undefined1 *)(param_9 + 0x540) = 1;
    *(float *)(param_9 + 0x558) = fVar1;
    *(undefined1 *)(param_9 + 0x6ef) = 1;
  }
  psVar4 = (short *)(param_9 + 0x197a);
  uVar5 = 0;
  zz_006eae0_(param_9,(short *)(param_9 + 0x1976),psVar4,0);
  dVar6 = (double)*(float *)(param_9 + 0x558);
  if (dVar6 <= (double)FLOAT_8043b0d4) {
    *(float *)(param_9 + 0x558) = FLOAT_8043b0dc;
    cVar3 = *(char *)(param_9 + 0x6ef) + -1;
    *(char *)(param_9 + 0x6ef) = cVar3;
    if (cVar3 < '\0') {
      *(undefined1 *)(param_9 + 0x73f) = 0;
      *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
      zz_006a668_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,4,psVar4,
                  uVar5,in_r7,in_r8,in_r9,in_r10);
      *(float *)(param_9 + 0x694) = FLOAT_8043b0d8 + *(float *)(param_9 + 0x1dc8);
      return;
    }
    dVar6 = (double)zz_006bf80_(param_9);
    if (*(short *)(param_9 + 1000) == 0x614) {
      zz_00c3be0_(param_9,0x31);
      dVar6 = (double)zz_00c3be0_(param_9,0x32);
    }
    else if (*(short *)(param_9 + 1000) == 0x628) {
      psVar4 = (short *)0x1;
      uVar5 = 1;
      iVar2 = zz_006dbe0_(param_9,2,1,1);
      if (iVar2 != 0) {
        zz_00c3be0_(param_9,0x51);
        dVar6 = (double)zz_00c3be0_(param_9,0x52);
      }
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar6 - (double)*(float *)(param_9 + 0x1dc8));
  }
  zz_0048d54_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,psVar4,uVar5,
              in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 8018c3d0  FUN_8018c3d0 ====

void FUN_8018c3d0(int param_1)

{
  int iVar1;
  
  zz_00c74ec_(param_1,0x25);
  if (*(short *)(param_1 + 1000) == 0x613) {
    zz_012aa24_(param_1,4);
    zz_012aa24_(param_1,5);
    iVar1 = 0;
    do {
      zz_018adf0_(param_1,iVar1,param_1 + iVar1 + 0x144);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 4);
  }
  else if (*(short *)(param_1 + 1000) == 0x627) {
    zz_012aa24_(param_1,10);
    zz_012aa24_(param_1,0xb);
    iVar1 = 0;
    do {
      zz_018adf0_(param_1,iVar1 + 8,param_1 + iVar1 + 0x144);
      iVar1 = iVar1 + 1;
    } while (iVar1 < 4);
  }
  *(undefined1 *)(param_1 + 0x144) = 1;
  *(undefined1 *)(param_1 + 0x145) = 1;
  *(undefined1 *)(param_1 + 0x146) = 1;
  *(undefined1 *)(param_1 + 0x147) = 1;
  return;
}



// ==== 8018c4b0  FUN_8018c4b0 ====

void FUN_8018c4b0(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_8043b0e8;
  fVar1 = FLOAT_8043b0e0;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x191e) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x191e) ^ 0x80000000) -
                             DOUBLE_8043b0e8) * FLOAT_8043b0e0);
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             dVar2) * fVar1);
  }
  return;
}



// ==== 8018c554  FUN_8018c554 ====

void FUN_8018c554(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80365450)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 8018c594  FUN_8018c594 ====

void FUN_8018c594(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x613) {
    zz_001ab6c_(param_1,0x31);
  }
  else if (*(short *)(param_1 + 1000) == 0x627) {
    zz_001ab6c_(param_1,0x66);
  }
  return;
}



// ==== 8018c5e0  FUN_8018c5e0 ====

void FUN_8018c5e0(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x613) {
    zz_001ab6c_(param_1,0x30);
  }
  else if (*(short *)(param_1 + 1000) == 0x627) {
    zz_001ab6c_(param_1,0x65);
  }
  return;
}



// ==== 8018c62c  FUN_8018c62c ====

void FUN_8018c62c(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x613) {
    zz_001ab6c_(param_1,0x31);
    zz_001ab6c_(param_1,0x30);
  }
  else if (*(short *)(param_1 + 1000) == 0x627) {
    zz_001ab6c_(param_1,0x66);
    zz_001ab6c_(param_1,0x65);
  }
  return;
}



// ==== 8018c6a8  FUN_8018c6a8 ====

void FUN_8018c6a8(int param_1,int param_2)

{
  byte *pbVar1;
  char cVar2;
  
  pbVar1 = &DAT_804356a8 + param_2 * 2;
  *(byte *)(param_1 + 0x144) = *(byte *)(param_1 + 0x144) & 0x7f;
  *(byte *)(param_1 + 0x145) = *(byte *)(param_1 + 0x145) & 0x7f;
  if (*(short *)(param_1 + 1000) == 0x627) {
    pbVar1 = (byte *)(param_2 * 2 + -0x7fbca954);
  }
  cVar2 = '\0' < *(char *)(param_1 + 0x144);
  if ((bool)cVar2) {
    *(undefined1 *)(param_1 + 0x144) = 0;
    zz_01b2b64_(param_1,*pbVar1);
  }
  if ('\0' < *(char *)(param_1 + 0x145)) {
    *(undefined1 *)(param_1 + 0x145) = 0;
    zz_01b2b64_(param_1,pbVar1[1]);
    cVar2 = cVar2 + '\x01';
  }
  if (cVar2 != '\0') {
    zz_00f036c_(param_1,0x105);
  }
  return;
}



// ==== 8018c79c  FUN_8018c79c ====

void FUN_8018c79c(int param_1)

{
  (*(code *)(&PTR_FUN_8036546c)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8018c7d8  FUN_8018c7d8 ====

void FUN_8018c7d8(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  short sVar2;
  int iVar3;
  char cVar4;
  double dVar5;
  
  if (*(char *)(param_9 + 0x540) == '\0') {
    *(undefined1 *)(param_9 + 0x540) = 1;
    fVar1 = FLOAT_8043b0f0;
    *(undefined1 *)(param_9 + 0x6ea) = 5;
    *(float *)(param_9 + 0x558) = fVar1;
  }
  iVar3 = zz_006672c_(param_9);
  dVar5 = DOUBLE_8043b0e8;
  sVar2 = (short)iVar3 - *(short *)(param_9 + 0x72);
  if ((sVar2 < 0x4801) && (-0x4801 < sVar2)) {
    sVar2 = sVar2 - *(short *)(param_9 + 0x191e);
    if (0x400 < sVar2) {
      sVar2 = 0x400;
    }
    if (sVar2 < -0x400) {
      sVar2 = -0x400;
    }
    *(short *)(param_9 + 0x191e) = *(short *)(param_9 + 0x191e) + sVar2;
    dVar5 = param_2;
  }
  else {
    param_1 = (double)(float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_9 + 0x191e) ^ 0x80000000) -
                             DOUBLE_8043b0e8);
    *(short *)(param_9 + 0x191e) = (short)(int)(param_1 * (double)FLOAT_8043b0f4);
  }
  if (*(char *)(param_9 + 0x6ea) < '\x05') {
    if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_9 + 0x5d4) & 1) == 0))
    goto LAB_8018c8cc;
LAB_8018c978:
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,param_9,6,param_11,
                param_12,param_13,param_14,param_15,param_16);
    *(float *)(param_9 + 0x694) = FLOAT_8043b0f8 + *(float *)(param_9 + 0x1dc8);
  }
  else {
LAB_8018c8cc:
    param_1 = (double)*(float *)(param_9 + 0x558);
    if (param_1 <= (double)FLOAT_8043b0f0) {
      *(float *)(param_9 + 0x558) = FLOAT_8043b0f8;
      cVar4 = *(char *)(param_9 + 0x6ea) + -1;
      *(char *)(param_9 + 0x6ea) = cVar4;
      if (cVar4 < '\0') goto LAB_8018c978;
      param_11 = 1;
      param_12 = 1;
      iVar3 = zz_006dbe0_(param_9,0,1,1);
      if (iVar3 != 0) {
        param_1 = (double)zz_006bf80_(param_9);
        if (*(short *)(param_9 + 1000) == 0x613) {
          zz_0082824_(param_9,0x32);
          param_1 = (double)zz_0082824_(param_9,0x33);
        }
        else if (*(short *)(param_9 + 1000) == 0x627) {
          zz_0082824_(param_9,0x4d);
          param_1 = (double)zz_0082824_(param_9,0x4e);
        }
      }
    }
    else {
      *(float *)(param_9 + 0x558) = (float)(param_1 - (double)*(float *)(param_9 + 0x1dc8));
    }
    zz_0048d54_(param_1,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,param_11,
                param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 8018c9cc  FUN_8018c9cc ====

void FUN_8018c9cc(int param_1)

{
  (*(code *)(&PTR_FUN_8036547c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8018ca08  FUN_8018ca08 ====

void FUN_8018ca08(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8018ca3c  FUN_8018ca3c ====

void FUN_8018ca3c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8018ca70  FUN_8018ca70 ====

void FUN_8018ca70(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8018caa4  FUN_8018caa4 ====

void FUN_8018caa4(int param_1)

{
  zz_0178394_(param_1);
  return;
}



// ==== 8018cacc  FUN_8018cacc ====

void FUN_8018cacc(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0178394_(param_1);
  return;
}



// ==== 8018cb00  FUN_8018cb00 ====

void FUN_8018cb00(int param_1)

{
  zz_018cb20_(param_1);
  return;
}



// ==== 8018cb20  zz_018cb20_ ====

void zz_018cb20_(int param_1)

{
  zz_017a374_(param_1);
  return;
}



// ==== 8018cb48  zz_018cb48_ ====

void zz_018cb48_(int param_1)

{
  zz_018cb68_(param_1);
  return;
}



// ==== 8018cb68  zz_018cb68_ ====

void zz_018cb68_(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  }
  zz_0179fcc_(param_1);
  return;
}



// ==== 8018cba8  zz_018cba8_ ====

void zz_018cba8_(int param_1)

{
  *(float *)(param_1 + 0x48) = FLOAT_8043b0fc;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  return;
}



// ==== 8018cbc0  zz_018cbc0_ ====

void zz_018cbc0_(int param_1)

{
  zz_006d0dc_(param_1,0xc1,0);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  return;
}



// ==== 8018cc10  zz_018cc10_ ====

void zz_018cc10_(int param_1)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = false;
  *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
  if (*(short *)(param_1 + 1000) == 0x613) {
    *(byte *)(param_1 + 0x144) = *(byte *)(param_1 + 0x144) | 0xc0;
    zz_01b2b64_(param_1,8);
    *(byte *)(param_1 + 0x145) = *(byte *)(param_1 + 0x145) | 0xc0;
    zz_01b2b64_(param_1,9);
    bVar1 = true;
  }
  else if ((*(short *)(param_1 + 1000) == 0x627) && (iVar2 = zz_006dbe0_(param_1,2,1,1), iVar2 != 0)
          ) {
    *(byte *)(param_1 + 0x144) = *(byte *)(param_1 + 0x144) | 0xc0;
    zz_01b2b64_(param_1,10);
    *(byte *)(param_1 + 0x145) = *(byte *)(param_1 + 0x145) | 0xc0;
    zz_01b2b64_(param_1,0xb);
    bVar1 = true;
  }
  if (bVar1) {
    zz_00f036c_(param_1,0x105);
  }
  return;
}



// ==== 8018ccfc  zz_018ccfc_ ====

void zz_018ccfc_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_zz_018d24c__80365538;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_018ce1c__8036553c;
  *(undefined **)(param_1 + 0x4bc) = PTR_zz_018cef8__80365540;
  *(undefined **)(param_1 + 0x4c0) = PTR_zz_018cf54__80365544;
  *(undefined **)(param_1 + 0x4c4) = PTR_zz_018cfd8__80365548;
  *(undefined **)(param_1 + 0x4c8) = PTR_zz_018cfe4__8036554c;
  *(undefined **)(param_1 + 0x4cc) = PTR_zz_018cfe8__80365550;
  *(undefined **)(param_1 + 0x4d0) = PTR_zz_018cfec__80365554;
  *(undefined4 *)(param_1 + 0x4d4) = DAT_80365558;
  *(undefined **)(param_1 + 0x4d8) = PTR_zz_018cff0__8036555c;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_80365560;
  *(undefined4 *)(param_1 + 0x4e0) = DAT_80365564;
  *(undefined **)(param_1 + 0x4e4) = PTR_FUN_80365568;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_8036556c;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_80365570;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_80365574;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_80365ac8;
  *(undefined **)(param_1 + 0x1d80) = &DAT_80366220;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bcc64;
  *(undefined **)(param_1 + 0x1d88) = &DAT_80367460;
  *(undefined **)(param_1 + 0x1d8c) = &DAT_802bb698;
  *(undefined **)(param_1 + 0x27c) = &DAT_80365ec0;
  if (*(short *)(param_1 + 1000) == 0x62a) {
    *(undefined **)(param_1 + 0x4e8) = &DAT_803659a0;
    *(undefined **)(param_1 + 0x4b0) = &DAT_80365be0;
    return;
  }
  return;
}



// ==== 8018ce1c  zz_018ce1c_ ====

void zz_018ce1c_(int param_1)

{
  short sVar1;
  
  *(undefined1 *)(param_1 + 0x4a8) = 1;
  *(undefined2 *)(param_1 + 0x6f6) = 0;
  zz_00c74ec_(param_1,0x28);
  zz_00c74ec_(param_1,0x29);
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x615) {
    zz_0185f6c_(param_1,0x18);
    zz_0185f6c_(param_1,0x19);
  }
  else if (sVar1 == 0x629) {
    zz_0185f6c_(param_1,0x1a);
    zz_0185f6c_(param_1,0x1b);
    zz_0185f6c_(param_1,0x1c);
  }
  else if (sVar1 == 0x62a) {
    zz_0185f6c_(param_1,0x1d);
    zz_0185f6c_(param_1,0x1e);
    zz_0185f6c_(param_1,0x1f);
    zz_0185f6c_(param_1,0x20);
  }
  return;
}



// ==== 8018cef8  zz_018cef8_ ====

void zz_018cef8_(int param_1)

{
  double dVar1;
  
  if ((*(uint *)(param_1 + 0x5e0) & 1) == 0) {
    *(undefined1 *)(param_1 + 0x6ee) = 0;
    dVar1 = DOUBLE_8043b108;
    *(undefined2 *)(param_1 + 0x1dfc) = 0;
    *(short *)(param_1 + 0x18e2) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) -
                             dVar1) * FLOAT_8043b100);
  }
  return;
}



// ==== 8018cf54  zz_018cf54_ ====

void zz_018cf54_(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x6e9);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
  }
  else if ((cVar1 < '\x02') && ('\0' < cVar1)) {
    *(undefined1 *)(param_1 + 0xaf) = 1;
    if (*(short *)(param_1 + 1000) == 0x62a) {
      zz_001ab6c_(param_1,0x7f);
    }
    else {
      zz_001ab6c_(param_1,0x32);
    }
  }
  *(undefined1 *)(param_1 + 0x6e9) = 0;
  return;
}



// ==== 8018cfd8  zz_018cfd8_ ====

void zz_018cfd8_(int param_1)

{
  *(undefined2 *)(param_1 + 0x6f6) = 0;
  return;
}



// ==== 8018cfe4  zz_018cfe4_ ====

void zz_018cfe4_(void)

{
  return;
}



// ==== 8018cfe8  zz_018cfe8_ ====

void zz_018cfe8_(void)

{
  return;
}



// ==== 8018cfec  zz_018cfec_ ====

void zz_018cfec_(void)

{
  return;
}



// ==== 8018cff0  zz_018cff0_ ====

void zz_018cff0_(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_zz_018d02c__80365578)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 8018d02c  zz_018d02c_ ====

void zz_018d02c_(void)

{
  return;
}



// ==== 8018d030  zz_018d030_ ====

void zz_018d030_(int param_1,int param_2)

{
  short sVar1;
  
  if (param_2 == 2) {
    *(undefined2 *)(param_1 + 0x6f6) = 3;
    if (*(short *)(param_1 + 1000) != 0x615) {
      zz_00f036c_(param_1,0xa1);
    }
  }
  else if (param_2 < 2) {
    if (param_2 == 0) {
      *(undefined2 *)(param_1 + 0x6f6) = 1;
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x615) {
        zz_01cf770_(param_1,0);
        zz_00f036c_(param_1,0xa1);
      }
      else if (sVar1 == 0x629) {
        zz_01cf770_(param_1,1);
      }
      else if (sVar1 == 0x62a) {
        zz_01cf770_(param_1,2);
      }
    }
    else if (-1 < param_2) {
      *(undefined2 *)(param_1 + 0x6f6) = 2;
    }
  }
  else if (param_2 == 4) {
    zz_01cf360_(param_1);
    zz_00f036c_(param_1,0x1d);
  }
  else if (param_2 < 4) {
    *(undefined2 *)(param_1 + 0x6f6) = 4;
  }
  return;
}



// ==== 8018d120  zz_018d120_ ====

void zz_018d120_(int param_1)

{
  uint uVar1;
  
  zz_006bf80_(param_1);
  *(undefined1 *)(param_1 + 0x541) = 0;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  if (*(int *)(param_1 + 0xcc) == 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0xa0) == 0) {
      *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
    }
    else {
      *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
    }
  }
  return;
}



// ==== 8018d1d8  zz_018d1d8_ ====

void zz_018d1d8_(int param_1)

{
  float local_18;
  float local_14;
  float local_10;
  
  if (((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) && (*(char *)(param_1 + 0x1db) == '\0')) {
    local_18 = FLOAT_8043b110;
    local_14 = FLOAT_8043b110;
    local_10 = FLOAT_8043b114;
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x8d4),&local_18,&local_18);
    zz_00fc208_(param_1,&local_18,5);
  }
  return;
}



// ==== 8018d24c  zz_018d24c_ ====

void zz_018d24c_(int param_1)

{
  (*(code *)(&PTR_zz_018d288__80365588)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 8018d288  zz_018d288_ ====

void zz_018d288_(int param_1)

{
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_8043b108) * FLOAT_8043b118);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_zz_018d308__8036559c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8018d308  zz_018d308_ ====

void zz_018d308_(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_zz_018d350__803655b0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8018d350  zz_018d350_ ====

void zz_018d350_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043b11c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d0dc_(param_1,0xc1,0);
  zz_004beb8_((double)FLOAT_8043b120,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  fVar1 = FLOAT_8043b110;
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
  gnt4_PSQUATScale_bl((double)FLOAT_8043b124,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_8043b110;
  return;
}



// ==== 8018d438  zz_018d438_ ====

/* WARNING: Removing unreachable block (ram,0x8018d518) */
/* WARNING: Removing unreachable block (ram,0x8018d448) */

void zz_018d438_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_8043b110;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_8043b110;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_018dcb0_(param_1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043b124,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_8043b128 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8018d534  zz_018d534_ ====

void zz_018d534_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  
  if ((*(uint *)(param_9 + 0x5d4) & 0x20) != 0) {
    *(undefined1 *)(param_9 + 0x745) = 1;
  }
  zz_004cd24_(param_9,0xf);
  if (*(float *)(param_9 + 0x558) <= FLOAT_8043b110) {
    if (*(char *)(param_9 + 0x745) != '\0') {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_006bf80_(param_9);
        *(undefined1 *)(param_9 + 0x745) = 0;
        if ((*(uint *)(param_9 + 0x5e0) & 0x40) != 0) {
          zz_006a3d0_(param_9,'\0',3,0);
          return;
        }
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        if (*(char *)(param_9 + 0x1cef) < '\0') {
          zz_004beb8_((double)FLOAT_8043b120,param_9,0xf,2,1,0xffffffff,0xffffffff);
          return;
        }
        zz_004beb8_((double)FLOAT_8043b120,param_9,0xf,2,1,4,1);
        return;
      }
      goto LAB_8018d668;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = *(float *)(param_9 + 0x558) - *(float *)(param_9 + 0x1dc8);
  }
  if ((((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_9 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_9 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_8043b124,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),(float *)(param_9 + 0x20));
    zz_00679d0_(param_9);
    dVar2 = gnt4_PSVECMag_bl((float *)(param_9 + 0x38));
    if (dVar2 <= (double)FLOAT_8043b128) {
      return;
    }
    zz_00b22f4_(param_9);
    return;
  }
LAB_8018d668:
  *(undefined1 *)(param_9 + 0x6e8) = 0;
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  dVar2 = (double)zz_006a474_(param_9);
  zz_006a668_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x14,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



