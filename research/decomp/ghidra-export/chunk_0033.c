// ==== 80120c70  FUN_80120c70 ====

void FUN_80120c70(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8032c67c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80120cc4  FUN_80120cc4 ====

void FUN_80120cc4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  double dVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 extraout_r4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar8;
  undefined8 uVar9;
  
  iVar7 = *(byte *)(param_9 + 0x18) + 1;
  *(char *)(param_9 + 0x18) = (char)iVar7;
  iVar8 = *(int *)(param_9 + 0x90);
  iVar4 = *(char *)(param_9 + 0x11) * 0x14;
  *(undefined *)(param_9 + 0x89) = (&DAT_8032c461)[iVar4];
  *(undefined *)(param_9 + 0x13) = (&DAT_8032c462)[iVar4];
  *(undefined *)(param_9 + 0x12) = (&DAT_8032c463)[iVar4];
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar9 = zz_0089100_(param_9,(int)*(char *)(iVar8 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80439a58;
  *(undefined1 *)(param_9 + 0x84) = 0x55;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x72) = *(undefined2 *)(&DAT_8032c466 + iVar4);
  *(undefined2 *)(param_9 + 0x74) = 0;
  uVar3 = *(undefined4 *)(&DAT_8032c46c + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8032c468 + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar3;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8032c470 + iVar4);
  iVar8 = zz_0006f98_(iVar8);
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)(char)(&DAT_8032c460)[iVar4],iVar8 + 0xc28,iVar7,in_r8,in_r9,in_r10);
  iVar6 = iVar8 + 0xc28;
  iVar5 = (int)(char)(&DAT_8032c460)[iVar4];
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xe4),iVar5,iVar6,iVar7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar5,iVar6,iVar7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80439a5c,*(int *)(param_9 + 0xe4));
  dVar2 = DOUBLE_80439a60;
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  *(float *)(param_9 + 0xd4) =
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(&DAT_8032c464 + iVar4) ^ 0x80000000) -
              dVar2);
  zz_0120e30_(param_9);
  return;
}



// ==== 80120e30  zz_0120e30_ ====

void zz_0120e30_(int param_1)

{
  (*(code *)(&PTR_LAB_8032c68c)[*(char *)(param_1 + 0x13)])(param_1,*(undefined4 *)(param_1 + 0x90))
  ;
  return;
}



// ==== 80120f80  FUN_80120f80 ====

void FUN_80120f80(int param_1,int param_2)

{
  char cVar1;
  byte bVar2;
  float fVar3;
  float fVar4;
  
  fVar4 = FLOAT_80439a74;
  fVar3 = FLOAT_80439a58;
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    fVar3 = FLOAT_80439a6c * *(float *)(param_2 + 0x1dc8) + *(float *)(param_1 + 0x58);
    if (FLOAT_80439a74 < fVar3) {
      *(undefined1 *)(param_1 + 0x19) = 2;
      fVar3 = fVar4;
    }
    *(float *)(param_1 + 0x60) = fVar3;
    *(float *)(param_1 + 0x5c) = fVar3;
    *(float *)(param_1 + 0x58) = fVar3;
  }
  else if (cVar1 < '\x01') {
    if (((-1 < cVar1) && (*(char *)(param_2 + 0x6f6) == '\0')) &&
       (*(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - *(float *)(param_2 + 0x1dc8),
       *(float *)(param_1 + 0xd4) <= fVar3)) {
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      zz_00f036c_(param_2,0x20);
    }
  }
  else if ((cVar1 < '\x03') && (bVar2 = *(byte *)(param_2 + 0x6e9), -1 < (char)bVar2)) {
    if (((*(char *)(param_1 + 0x11) == '\f') && ((bVar2 & 1) != 0)) ||
       ((*(char *)(param_1 + 0x11) == '\r' && ((bVar2 & 2) != 0)))) {
      fVar3 = *(float *)(param_1 + 0x58) + FLOAT_80439a78;
    }
    else {
      fVar3 = *(float *)(param_1 + 0x58) - FLOAT_80439a78;
    }
    if (fVar3 < FLOAT_80439a58) {
      fVar3 = FLOAT_80439a58;
    }
    if (FLOAT_80439a74 < fVar3) {
      fVar3 = FLOAT_80439a74;
    }
    *(float *)(param_1 + 0x60) = fVar3;
    *(float *)(param_1 + 0x5c) = fVar3;
    *(float *)(param_1 + 0x58) = fVar3;
  }
  return;
}



// ==== 801212b0  FUN_801212b0 ====

void FUN_801212b0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801212d0  FUN_801212d0 ====

void FUN_801212d0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  float *pfVar2;
  uint uVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [3];
  undefined4 local_3c;
  undefined4 local_2c;
  undefined4 local_1c;
  
  if (*(char *)(*(int *)(param_1 + 0x90) + 0xae) == '\0') {
    if (*(char *)(*(int *)(param_1 + 0x90) + 0x3ec) != '\x04') {
      iVar1 = 0;
      uVar3 = (uint)*(char *)(param_1 + 0x12);
      goto LAB_80121320;
    }
  }
  iVar1 = 1;
  uVar3 = 0x44;
LAB_80121320:
  dVar5 = (double)*(float *)(param_1 + 0x5c);
  iVar1 = *(int *)(param_1 + iVar1 * 4 + 0xe0);
  dVar6 = (double)*(float *)(param_1 + 0x60);
  gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),dVar5,dVar6,afStack_48);
  if (*(char *)(param_1 + 0x13) == '\0') {
    pfVar2 = afStack_48;
    uVar4 = gnt4_PSMTXConcat_bl(pfVar2,(float *)(param_1 + 0x114),pfVar2);
  }
  else {
    pfVar2 = afStack_48;
    uVar4 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar2,pfVar2);
  }
  local_3c = *(undefined4 *)(param_1 + 0x120);
  local_2c = *(undefined4 *)(param_1 + 0x130);
  local_1c = *(undefined4 *)(param_1 + 0x140);
  zz_00076d0_(uVar4,dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,iVar1,afStack_48,(undefined *)pfVar2,
              param_4,param_5,param_6,param_7,param_8);
  zz_00097b4_(iVar1,uVar3);
  return;
}



// ==== 801213bc  zz_01213bc_ ====

void zz_01213bc_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,2);
  if (puVar1 == (undefined1 *)0x0) {
    *(undefined1 *)(param_1 + 0x6f4) = 0;
  }
  else {
    *puVar1 = 1;
    puVar1[0x10] = 0x3a;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 0x20;
    *(code **)(puVar1 + 0xc) = FUN_801214cc;
    *(code **)(puVar1 + 0x10c) = FUN_80121b1c;
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
    *(undefined1 *)(param_1 + 0x6f4) = 1;
  }
  return;
}



// ==== 801214cc  FUN_801214cc ====

void FUN_801214cc(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_8032c700)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8012151c  FUN_8012151c ====

void FUN_8012151c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  int iVar2;
  float fVar3;
  int iVar4;
  int *piVar5;
  undefined4 extraout_r4;
  float *pfVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  double dVar10;
  undefined8 uVar11;
  
  iVar9 = *(int *)(param_9 + 0x90);
  iVar2 = (uint)*(byte *)(param_9 + 0x11) * 0x20;
  iVar4 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8032c6a4 + iVar2));
  if (iVar4 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(iVar9 + 0x6f4) = 0;
  }
  else {
    uVar8 = 1;
    *(undefined1 *)(param_9 + 0x18) = 1;
    fVar3 = FLOAT_80439a88;
    uVar7 = 0;
    iVar4 = (int)*(short *)(&DAT_8032c6a6 + iVar2);
    *(short *)(param_9 + 0x1c) = *(short *)(&DAT_8032c6a6 + iVar2);
    *(undefined2 *)(param_9 + 0x1e) = 0;
    *(float *)(param_9 + 0xd4) = fVar3;
    *(undefined4 *)(param_9 + 0xd8) = *(undefined4 *)(&DAT_8032c6bc + iVar2);
    *(undefined1 *)(param_9 + 0x150) = 1;
    *(code **)(param_9 + 0x100) = FUN_80121a24;
    zz_0089100_(param_9,1,1);
    pfVar6 = (float *)(param_9 + 0x20);
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar9 + *(short *)(&DAT_8032c6a2 + iVar2) * 0x30 + 0x8d4),
               (float *)(iVar2 + -0x7fcd3958),pfVar6);
    *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(iVar9 + 0xb4);
    *(float *)(param_9 + 0xb4) = *(float *)(param_9 + 0x144) * *(float *)(&DAT_8032c6b4 + iVar2);
    dVar10 = (double)*(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x148) = (float)(dVar10 * (double)*(float *)(&DAT_8032c6b8 + iVar2));
    uVar1 = *(undefined4 *)(param_9 + 0xb4);
    *(undefined4 *)(param_9 + 0x60) = uVar1;
    *(undefined4 *)(param_9 + 0x5c) = uVar1;
    *(undefined4 *)(param_9 + 0x58) = uVar1;
    *(undefined4 *)(param_9 + 0xc0) = uVar1;
    piVar5 = zz_0006dc8_(*(char *)(param_9 + 0x13) * 0x5c);
    *(int **)(param_9 + 0xdc) = piVar5;
    uVar11 = zz_0121c88_(dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                         pfVar6,uVar7,iVar4,uVar8,in_r9,in_r10);
    pfVar6 = (float *)(int)*(short *)(&DAT_8032c6a0 + iVar2);
    zz_0006fb4_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(int)pfVar6,uVar7,iVar4,uVar8,in_r9,in_r10);
    uVar11 = zz_00086b8_((double)*(float *)(param_9 + 0xd8),param_2,param_3,param_4,param_5,param_6,
                         param_7,param_8,DAT_803bb374,*(int *)(param_9 + 0xe0),pfVar6,uVar7,iVar4,
                         uVar8,in_r9,in_r10);
    zz_0007c30_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4,pfVar6,uVar7,iVar4,uVar8,in_r9,in_r10);
    *(undefined1 *)(param_9 + 0x82) = 1;
    zz_00f036c_(param_9,0xa4);
  }
  return;
}



// ==== 80121694  FUN_80121694 ====

void FUN_80121694(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  int iVar2;
  float fVar3;
  short sVar4;
  float *pfVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  pfVar5 = (float *)(param_1 + 0x20);
  iVar6 = *(int *)(param_1 + 0x90);
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x20;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar6 + *(short *)(&DAT_8032c6a2 + iVar2) * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fcd3958),pfVar5);
  *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(iVar6 + 0xb4);
  (*(code *)(&PTR_LAB_80434590)[*(char *)(param_1 + 0x19)])(param_1);
  fVar3 = FLOAT_80439a90;
  fVar1 = *(float *)(param_1 + 0xd4) + FLOAT_80439a8c;
  *(float *)(param_1 + 0xd4) = fVar1;
  if (fVar3 <= fVar1) {
    *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - fVar3;
  }
  dVar8 = zz_0045204_((short)(int)(FLOAT_80439a9c * *(float *)(param_1 + 0xd4)));
  fVar3 = FLOAT_80439a9c;
  dVar10 = (double)FLOAT_80439a98;
  fVar1 = (float)(dVar10 * dVar8 + (double)FLOAT_80439a94);
  *(float *)(param_1 + 0x60) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  dVar8 = zz_0045204_((short)(int)(fVar3 * *(float *)(param_1 + 0xd4)));
  *(float *)(param_1 + 0x5c) = (float)((double)FLOAT_80439aa0 * -dVar8 + (double)FLOAT_80439a94);
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(param_1 + 0x58),
                      (float *)(param_1 + 0x58));
  dVar8 = DOUBLE_80439aa8;
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xb4);
  dVar7 = (double)FLOAT_80439a88;
  sVar4 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar4;
  dVar9 = (double)(float)((double)CONCAT44(0x43300000,(int)sVar4 ^ 0x80000000) - dVar8);
  if (dVar9 <= dVar7) {
    *(undefined2 *)(param_1 + 0x1e) = 0x1e;
    dVar9 = (double)zz_0121db0_(param_1,0,pfVar5,param_4,param_5,param_6,param_7,param_8);
  }
  zz_0122208_(dVar9,dVar8,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,param_1,0,pfVar5,param_4,param_5,
              param_6,param_7,param_8);
  return;
}



// ==== 80121860  FUN_80121860 ====

void FUN_80121860(int param_1)

{
  byte bVar1;
  short sVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x90);
  bVar1 = *(byte *)(param_1 + 0x11);
  if (*(char *)(iVar3 + 0x6f4) == '\x02') {
    *(undefined1 *)(iVar3 + 0x6f4) = 1;
    *(undefined2 *)(param_1 + 0x1c) = *(undefined2 *)(&DAT_8032c6a6 + (uint)bVar1 * 0x20);
  }
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(undefined1 *)(iVar3 + 0x6f4) = 0;
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x19) = 0;
    zz_008aff0_(param_1);
  }
  return;
}



// ==== 801218e0  FUN_801218e0 ====

void FUN_801218e0(int param_1)

{
  (*(code *)(&PTR_FUN_80434598)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 80121918  FUN_80121918 ====

void FUN_80121918(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,int param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  uVar1 = 0;
  *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x6f4) = 0;
  *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  *(undefined1 *)(param_9 + 0x150) = 0;
  uVar3 = zz_008aff0_(param_9);
  zz_0121c88_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,uVar1,param_12
              ,param_13,param_14,param_15,param_16);
  iVar2 = 0;
  do {
    zz_0121db0_(param_9,1,uVar1,param_12,param_13,param_14,param_15,param_16);
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0x20);
  return;
}



// ==== 80121990  FUN_80121990 ====

void FUN_80121990(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_0122208_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,param_11,
              param_12,param_13,param_14,param_15,param_16);
  if (*(int *)(param_9 + 0x14c) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 3;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801219dc  FUN_801219dc ====

void FUN_801219dc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80121a24  FUN_80121a24 ====

void FUN_80121a24(int param_1)

{
  float *pfVar1;
  uint uVar2;
  int iVar3;
  
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                     (double)*(float *)(param_1 + 0x28),(float *)(param_1 + 0x114));
  if (*(int *)(param_1 + 0xdc) != 0) {
    uVar2 = 0;
    iVar3 = 0;
    while( true ) {
      if ((int)*(char *)(param_1 + 0x13) <= (int)uVar2) break;
      if ((*(uint *)(param_1 + 0x14c) & 1 << (uVar2 & 0x1f)) != 0) {
        pfVar1 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar3);
        zz_00455fc_((float *)(param_1 + 0x114),pfVar1,pfVar1 + 0xc);
        zz_00457d4_('y',pfVar1,pfVar1,*(short *)(pfVar1 + 0x15));
        zz_00456a0_(pfVar1,pfVar1,pfVar1 + 0xf);
      }
      iVar3 = iVar3 + 0x5c;
      uVar2 = uVar2 + 1;
    }
  }
  if (*(char *)(param_1 + 0x150) != '\0') {
    zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  }
  return;
}



// ==== 80121b1c  FUN_80121b1c ====

/* WARNING: Removing unreachable block (ram,0x80121bdc) */

void FUN_80121b1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  uint uVar6;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    uVar6 = 0;
    iVar2 = *(int *)(*(int *)(param_9 + 0xe4) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    iVar5 = 0;
    while ((int)uVar6 < (int)*(char *)(param_9 + 0x13)) {
      if ((*(uint *)(param_9 + 0x14c) & 1 << (uVar6 & 0x1f)) != 0) {
        pfVar4 = (float *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar5);
        if (iVar2 == 0) {
          param_11 = &DAT_80439abc;
          param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                     ,&DAT_80439ab4,0x495,&DAT_80439abc,param_12,param_13,param_14,
                                     param_15,param_16);
        }
        if (pfVar4 == (float *)0x0) {
          param_11 = &DAT_80439ac4;
          gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           &DAT_80439ab4,0x496,&DAT_80439ac4,param_12,param_13,param_14,param_15,
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
      iVar5 = iVar5 + 0x5c;
      uVar6 = uVar6 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
    param_1 = zz_00097b4_(*(int *)(param_9 + 0xe4),0x44);
  }
  if (*(char *)(param_9 + 0x150) != '\0') {
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  }
  return;
}



// ==== 80121c88  zz_0121c88_ ====

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void zz_0121c88_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,int param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  undefined8 uVar5;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    if (param_10 == 0) {
      iVar3 = (int)*(char *)(param_9 + 0x13);
      uVar5 = zz_0007198_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb374,*(int *)(param_9 + 0xe4),(char *)(int)_DAT_804345a0,iVar3,
                          param_13,param_14,param_15,param_16);
    }
    else {
      param_13 = (int)*(float *)(param_9 + 0xd8);
      iVar3 = (int)*(char *)(param_9 + 0x13);
      uVar5 = zz_000744c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb374,*(int *)(param_9 + 0xe4),
                          (float *)(int)*(short *)(&DAT_804345a0 + param_10 * 2),iVar3,param_13,
                          param_14,param_15,param_16);
    }
    uVar4 = 0;
    iVar1 = *(int *)(*(int *)(param_9 + 0xe4) + 0xc);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(iVar1 + 0x10);
    }
    while ((int)uVar4 < (int)*(char *)(param_9 + 0x13)) {
      puVar2 = *(undefined **)(param_9 + 0x14c);
      *(uint *)(param_9 + 0x14c) = (uint)puVar2 & ~(1 << (uVar4 & 0x1f));
      uVar5 = gnt4_HSD_JObjSetFlagsAll
                        (uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,0x10,
                         puVar2,iVar3,param_13,param_14,param_15,param_16);
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



// ==== 80121db0  zz_0121db0_ ====

/* WARNING: Removing unreachable block (ram,0x801221ec) */
/* WARNING: Removing unreachable block (ram,0x80121dc0) */

void zz_0121db0_(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  float fVar4;
  float fVar5;
  undefined2 uVar6;
  uint uVar7;
  int iVar8;
  int iVar9;
  undefined *puVar10;
  uint uVar11;
  uint uVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar16;
  
  if (*(int *)(param_1 + 0xdc) != 0) {
    for (uVar12 = 0; (int)uVar12 < (int)*(char *)(param_1 + 0x13); uVar12 = uVar12 + 1) {
      puVar10 = *(undefined **)(param_1 + 0x14c);
      uVar11 = 1 << (uVar12 & 0x1f);
      if (((uint)puVar10 & uVar11) == 0) {
        iVar9 = *(int *)(*(int *)(param_1 + 0xdc) + 0xc);
        *(uint *)(param_1 + 0x14c) = (uint)puVar10 | uVar11;
        iVar9 = iVar9 + uVar12 * 0x5c;
        if (param_2 == 0) {
          uVar7 = zz_00055fc_();
          fVar5 = FLOAT_80439ad0;
          fVar4 = FLOAT_80439acc;
          dVar15 = (double)(float)((double)CONCAT44(0x43300000,uVar7 & 0xff) - DOUBLE_80439b00);
          fVar1 = FLOAT_80439a94 + (float)(dVar15 / (double)FLOAT_80439ac8);
          *(float *)(iVar9 + 0x44) = fVar1;
          *(float *)(iVar9 + 0x40) = fVar1;
          *(float *)(iVar9 + 0x3c) = fVar1;
          dVar16 = (double)(fVar4 * *(float *)(param_1 + 0xb4) - fVar5 * *(float *)(iVar9 + 0x3c));
          uVar7 = zz_00055fc_();
          *(float *)(iVar9 + 0x30) =
               (float)(dVar16 * (double)((float)((double)CONCAT44(0x43300000,uVar7 & 0xff) -
                                                DOUBLE_80439b00) / FLOAT_80439ad4 - FLOAT_80439a94))
          ;
          uVar7 = zz_00055fc_();
          *(float *)(iVar9 + 0x34) =
               (float)(dVar16 * (double)((float)((double)CONCAT44(0x43300000,uVar7 & 0xff) -
                                                DOUBLE_80439b00) / FLOAT_80439ad8 - FLOAT_80439a94))
          ;
          uVar7 = zz_00055fc_();
          *(float *)(iVar9 + 0x38) =
               (float)(dVar16 * (double)((float)((double)CONCAT44(0x43300000,uVar7 & 0xff) -
                                                DOUBLE_80439b00) / FLOAT_80439ad4 - FLOAT_80439a94))
          ;
          dVar13 = gnt4_PSVECMag_bl((float *)(iVar9 + 0x30));
          if (dVar16 < dVar13) {
            gnt4_PSQUATScale_bl((double)(float)(dVar16 / dVar13),(float *)(iVar9 + 0x30),
                                (float *)(iVar9 + 0x30));
          }
          fVar1 = FLOAT_80439a88;
          *(float *)(iVar9 + 0x50) = FLOAT_80439a88;
          *(float *)(iVar9 + 0x48) = fVar1;
          uVar7 = zz_00055fc_();
          dVar13 = DOUBLE_80439b00;
          dVar14 = (double)(float)((double)CONCAT44(0x43300000,uVar7 & 0xff) - DOUBLE_80439b00);
          dVar16 = (double)(float)(dVar14 / (double)FLOAT_80439ad4);
          *(float *)(iVar9 + 0x4c) = (float)((double)FLOAT_80439adc + dVar16);
          uVar7 = zz_00055fc_();
          *(short *)(iVar9 + 0x54) = (short)(uVar7 << 9);
          uVar6 = 0xfc00;
          if ((uVar7 & 0x80) != 0) {
            uVar6 = 0x400;
          }
          *(undefined2 *)(iVar9 + 0x56) = uVar6;
          *(float *)(iVar9 + 0x58) = FLOAT_80439ae0;
        }
        else {
          uVar7 = zz_00055fc_();
          fVar5 = FLOAT_80439ad0;
          fVar4 = FLOAT_80439acc;
          dVar15 = (double)(float)((double)CONCAT44(0x43300000,uVar7 & 0xff) - DOUBLE_80439b00);
          fVar1 = FLOAT_80439ae4 + (float)(dVar15 / (double)FLOAT_80439ac8);
          *(float *)(iVar9 + 0x44) = fVar1;
          *(float *)(iVar9 + 0x40) = fVar1;
          *(float *)(iVar9 + 0x3c) = fVar1;
          dVar16 = (double)(fVar4 * *(float *)(param_1 + 0xb4) - fVar5 * *(float *)(iVar9 + 0x3c));
          uVar7 = zz_00055fc_();
          *(float *)(iVar9 + 0x30) =
               (float)(dVar16 * (double)((float)((double)CONCAT44(0x43300000,uVar7 & 0xff) -
                                                DOUBLE_80439b00) / FLOAT_80439ad4 - FLOAT_80439a94))
          ;
          uVar7 = zz_00055fc_();
          *(float *)(iVar9 + 0x34) =
               (float)(dVar16 * (double)((float)((double)CONCAT44(0x43300000,uVar7 & 0xff) -
                                                DOUBLE_80439b00) / FLOAT_80439ae8 - FLOAT_80439a94))
          ;
          uVar7 = zz_00055fc_();
          *(float *)(iVar9 + 0x38) =
               (float)(dVar16 * (double)((float)((double)CONCAT44(0x43300000,uVar7 & 0xff) -
                                                DOUBLE_80439b00) / FLOAT_80439ad4 - FLOAT_80439a94))
          ;
          dVar13 = gnt4_PSVECMag_bl((float *)(iVar9 + 0x30));
          uVar2 = DAT_802b0cb8;
          if (dVar13 < (double)FLOAT_80439aec) {
            *(undefined4 *)(iVar9 + 0x30) = DAT_802b0cb4;
            uVar3 = DAT_802b0cbc;
            *(undefined4 *)(iVar9 + 0x34) = uVar2;
            *(undefined4 *)(iVar9 + 0x38) = uVar3;
          }
          gnt4_PSVECNormalize_bl((float *)(iVar9 + 0x30),(float *)(iVar9 + 0x48));
          uVar7 = zz_00055fc_();
          gnt4_PSQUATScale_bl((double)(float)(dVar16 * (double)(FLOAT_80439af0 +
                                                               (float)((double)CONCAT44(0x43300000,
                                                                                        uVar7 & 0xff
                                                                                       ) -
                                                                      DOUBLE_80439b00) /
                                                               FLOAT_80439af4)),
                              (float *)(iVar9 + 0x48),(float *)(iVar9 + 0x30));
          uVar7 = zz_00055fc_();
          dVar13 = (double)(float)((double)CONCAT44(0x43300000,uVar7 & 0xff) - DOUBLE_80439b00);
          dVar14 = (double)(float)(dVar13 / (double)FLOAT_80439afc);
          dVar16 = (double)gnt4_PSQUATScale_bl((double)(*(float *)(param_1 + 0xb4) *
                                                       (float)((double)FLOAT_80439af8 + dVar14)),
                                               (float *)(iVar9 + 0x48),(float *)(iVar9 + 0x48));
          fVar1 = FLOAT_80439ae0;
          *(undefined2 *)(iVar9 + 0x56) = 0;
          *(undefined2 *)(iVar9 + 0x54) = 0;
          *(float *)(iVar9 + 0x58) = fVar1;
        }
        iVar8 = *(int *)(*(int *)(param_1 + 0xe4) + 0xc);
        if (iVar8 == 0) {
          iVar8 = 0;
        }
        else {
          iVar8 = *(int *)(iVar8 + 0x10);
        }
        if (0 < (int)uVar12) {
          do {
            if (iVar8 == 0) {
              iVar8 = 0;
            }
            else {
              iVar8 = *(int *)(iVar8 + 8);
            }
            uVar12 = uVar12 - 1;
          } while (uVar12 != 0);
        }
        gnt4_HSD_JObjClearFlagsAll
                  (dVar16,dVar14,dVar13,dVar15,in_f5,in_f6,in_f7,in_f8,iVar8,0x10,puVar10,uVar11,
                   param_5,param_6,param_7,param_8);
        zz_00091e4_((double)*(float *)(iVar9 + 0x58),iVar8);
        uVar12 = (uint)*(char *)(param_1 + 0x13);
      }
    }
  }
  return;
}



// ==== 80122208  zz_0122208_ ====

/* WARNING: Removing unreachable block (ram,0x801223a4) */
/* WARNING: Removing unreachable block (ram,0x80122218) */

void zz_0122208_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  float fVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    uVar7 = 0;
    iVar3 = *(int *)(*(int *)(param_9 + 0xe4) + 0xc);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *(int *)(iVar3 + 0x10);
    }
    iVar8 = 0;
    while ((int)uVar7 < (int)*(char *)(param_9 + 0x13)) {
      uVar6 = 1 << (uVar7 & 0x1f);
      if ((*(uint *)(param_9 + 0x14c) & uVar6) != 0) {
        iVar5 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar8;
        if (param_10 == 0) {
          param_3 = (double)*(float *)(param_9 + 0xb4);
          dVar10 = (double)FLOAT_80439ad0;
          param_4 = (double)FLOAT_80439acc;
          *(float *)(iVar5 + 0x34) = *(float *)(iVar5 + 0x34) + *(float *)(iVar5 + 0x4c);
          dVar11 = (double)(float)(param_4 * param_3 -
                                  (double)(float)(dVar10 * (double)*(float *)(iVar5 + 0x3c)));
          *(short *)(iVar5 + 0x54) = *(short *)(iVar5 + 0x54) + *(short *)(iVar5 + 0x56);
          dVar9 = gnt4_PSVECMag_bl((float *)(iVar5 + 0x30));
          bVar1 = dVar11 <= dVar9;
        }
        else {
          dVar10 = (double)FLOAT_80439acc;
          dVar11 = (double)(float)(dVar10 * (double)*(float *)(param_9 + 0xb4) -
                                  (double)(FLOAT_80439ad0 * *(float *)(iVar5 + 0x3c)));
          gnt4_PSVECAdd_bl((float *)(iVar5 + 0x30),(float *)(iVar5 + 0x48),(float *)(iVar5 + 0x30));
          dVar9 = gnt4_PSVECMag_bl((float *)(iVar5 + 0x30));
          fVar2 = FLOAT_80439a88;
          bVar1 = false;
          if (dVar11 < dVar9) {
            dVar10 = (double)*(float *)(iVar5 + 0x58);
            dVar11 = (double)FLOAT_80439a88;
            dVar9 = (double)(float)(dVar10 - (double)FLOAT_80439b08);
            *(float *)(iVar5 + 0x58) = (float)(dVar10 - (double)FLOAT_80439b08);
            bVar1 = dVar9 <= dVar11;
            if (bVar1) {
              *(float *)(iVar5 + 0x58) = fVar2;
            }
          }
        }
        if (bVar1) {
          puVar4 = *(undefined **)(param_9 + 0x14c);
          *(uint *)(param_9 + 0x14c) = (uint)puVar4 & ~uVar6;
          gnt4_HSD_JObjSetFlagsAll
                    (dVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,0x10,puVar4,
                     param_12,param_13,param_14,param_15,param_16);
        }
        else {
          zz_00091e4_((double)*(float *)(iVar5 + 0x58),iVar3);
        }
      }
      iVar8 = iVar8 + 0x5c;
      uVar7 = uVar7 + 1;
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



// ==== 801223c0  zz_01223c0_ ====

void zz_01223c0_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_FUN_8032c728;
  *(undefined **)(param_1 + 0x4b8) = PTR_FUN_8032c72c;
  *(undefined **)(param_1 + 0x4bc) = PTR_FUN_8032c730;
  *(undefined **)(param_1 + 0x4c0) = PTR_FUN_8032c734;
  *(undefined **)(param_1 + 0x4c4) = PTR_LAB_8032c738;
  *(undefined **)(param_1 + 0x4c8) = PTR_LAB_8032c73c;
  *(undefined **)(param_1 + 0x4cc) = PTR_LAB_8032c740;
  *(undefined **)(param_1 + 0x4d0) = PTR_LAB_8032c744;
  *(undefined4 *)(param_1 + 0x4d4) = DAT_8032c748;
  *(undefined **)(param_1 + 0x4d8) = PTR_FUN_8032c74c;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_8032c750;
  *(undefined4 *)(param_1 + 0x4e0) = DAT_8032c754;
  *(undefined **)(param_1 + 0x4e4) = PTR_FUN_8032c758;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_8032c75c;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_8032c760;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_8032c764;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_8032d2a8;
  *(undefined **)(param_1 + 0x1d80) = &DAT_8032c860;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bc080;
  *(undefined **)(param_1 + 0x1d88) = &DAT_8032cec0;
  *(undefined **)(param_1 + 0x1d8c) = &DAT_802bae60;
  *(undefined **)(param_1 + 0x27c) = &DAT_8032d628;
  if (*(short *)(param_1 + 1000) == 0x708) {
    *(undefined **)(param_1 + 0x1d80) = &DAT_8032c86c;
  }
  if (*(short *)(param_1 + 1000) == 0x70c) {
    *(undefined **)(param_1 + 0x4b0) = &DAT_8032d3c0;
    *(undefined **)(param_1 + 0x27c) = &DAT_8032d850;
  }
  if (*(short *)(param_1 + 1000) == 0x70d) {
    *(undefined **)(param_1 + 0x4b0) = &DAT_8032d3c0;
    *(undefined **)(param_1 + 0x1d80) = &DAT_8032c86c;
    *(undefined **)(param_1 + 0x27c) = &DAT_8032d850;
    return;
  }
  return;
}



// ==== 80122528  FUN_80122528 ====

void FUN_80122528(int param_1)

{
  short sVar1;
  float fVar2;
  double dVar3;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x701) {
    zz_00f5ca8_(param_1,0);
    zz_00f60a0_(param_1,0);
  }
  else if (sVar1 == 0x708) {
    zz_00f5ca8_(param_1,1);
  }
  else if (sVar1 == 0x70c) {
    zz_00f60a0_(param_1,1);
  }
  else if (sVar1 == 0x70d) {
    zz_00f60a0_(param_1,2);
  }
  dVar3 = DOUBLE_80439b18;
  local_18 = 0x43300000;
  *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x140);
  fVar2 = FLOAT_80439b10;
  *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x144);
  *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x148);
  *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x14c);
  *(undefined1 *)(param_1 + 0x15a) = 1;
  uStack_14 = (int)*(char *)(param_1 + 0x15a) ^ 0x80000000;
  *(float *)(param_1 + 0x154) = (float)((double)CONCAT44(0x43300000,uStack_14) - dVar3);
  *(undefined1 *)(param_1 + 0x159) = 0;
  *(undefined1 *)(param_1 + 0x158) = 0;
  *(undefined2 *)(param_1 + 0x18e) = *(undefined2 *)(param_1 + 0x72);
  *(undefined2 *)(param_1 + 0x18c) = *(undefined2 *)(param_1 + 0x72);
  *(float *)(param_1 + 400) = fVar2;
  *(undefined2 *)(param_1 + 0x194) = 0;
  gnt4_PSMTXRotRad_bl((double)*(float *)(param_1 + 400),afStack_48,0x79);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x904),afStack_48,afStack_48);
  gnt4_PSMTXMultVec_bl(afStack_48,(float *)&DAT_8032c710,(float *)(param_1 + 0x174));
  gnt4_PSMTXMultVec_bl(afStack_48,(float *)&DAT_8032c71c,(float *)(param_1 + 0x180));
  fVar2 = FLOAT_80439b14;
  *(float *)(param_1 + 0x184) = FLOAT_80439b14;
  *(float *)(param_1 + 0x178) = fVar2;
  *(float *)(param_1 + 0x15c) = *(float *)(param_1 + 0x174);
  *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x178);
  *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x17c);
  *(float *)(param_1 + 0x168) = *(float *)(param_1 + 0x180);
  *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(param_1 + 0x184);
  *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_1 + 0x188);
  return;
}



// ==== 801226d0  FUN_801226d0 ====

void FUN_801226d0(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80439b18) * FLOAT_80439b20);
  }
  if ((*(short *)(param_1 + 1000) == 0x701) || (*(short *)(param_1 + 1000) == 0x70c)) {
    if ((*(char *)(param_1 + 0x158) == '\0') &&
       ((*(char *)(param_1 + 0x159) == '\0' && (*(short *)(param_1 + 0x774) < 1)))) {
      zz_006de10_(param_1,0);
    }
  }
  return;
}



// ==== 80122770  FUN_80122770 ====

void FUN_80122770(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  float afStack_58 [3];
  float afStack_4c [13];
  undefined4 local_18;
  uint uStack_14;
  
  if ((*(short *)(param_1 + 1000) == 0x701) || (*(short *)(param_1 + 1000) == 0x708)) {
    if (*(char *)(param_1 + 0x3ec) < '\x02') {
      *(char *)(param_1 + 0x6f2) = *(char *)(param_1 + 0x6f2) + '\b';
      dVar3 = zz_0045204_((short)*(char *)(param_1 + 0x6f2) << 8);
      fVar1 = FLOAT_80439b24;
      dVar3 = DOUBLE_80439b30 * dVar3 + DOUBLE_80439b28;
      *(float *)(param_1 + 0x16d0) = FLOAT_80439b24;
      *(float *)(param_1 + 0x16c4) = fVar1;
      fVar1 = (float)dVar3;
      *(float *)(param_1 + 0x16d4) = fVar1;
      *(float *)(param_1 + 0x16c8) = fVar1;
    }
    if ('d' < *(char *)(param_1 + 0x15a)) {
      *(undefined1 *)(param_1 + 0x15a) = 100;
    }
    fVar1 = FLOAT_80439b38;
    local_18 = 0x43300000;
    uStack_14 = (int)*(char *)(param_1 + 0x15a) ^ 0x80000000;
    *(float *)(param_1 + 0x154) = (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80439b18);
    *(float *)(param_1 + 0x16cc) = *(float *)(param_1 + 0x16cc) + fVar1;
    if (*(float *)(param_1 + 0x154) < *(float *)(param_1 + 0x16cc)) {
      *(float *)(param_1 + 0x16cc) = *(float *)(param_1 + 0x154);
    }
    *(float *)(param_1 + 0x16d8) = *(float *)(param_1 + 0x16d8) + FLOAT_80439b38;
    if (*(float *)(param_1 + 0x154) < *(float *)(param_1 + 0x16d8)) {
      *(float *)(param_1 + 0x16d8) = *(float *)(param_1 + 0x154);
    }
    fVar1 = FLOAT_80439b3c * *(float *)(param_1 + 0x154);
    fVar2 = *(float *)(param_1 + 0x144) + fVar1;
    *(float *)(param_1 + 0x874) = fVar2;
    *(float *)(param_1 + 0x85c) = fVar2;
    *(float *)(param_1 + 0x858) = fVar2;
    *(float *)(param_1 + 0x878) = *(float *)(param_1 + 0x148) + fVar1;
    *(float *)(param_1 + 0x87c) = *(float *)(param_1 + 0x14c) + fVar1;
    *(float *)(param_1 + 0x880) = *(float *)(param_1 + 0x150) + fVar1;
  }
  fVar1 = FLOAT_80439b44;
  *(float *)(param_1 + 400) = *(float *)(param_1 + 400) + FLOAT_80439b40;
  if (fVar1 < *(float *)(param_1 + 400)) {
    *(float *)(param_1 + 400) = *(float *)(param_1 + 400) - FLOAT_80439b48;
  }
  gnt4_PSMTXRotRad_bl((double)*(float *)(param_1 + 400),afStack_4c,0x79);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x904),afStack_4c,afStack_4c);
  gnt4_PSMTXMultVec_bl(afStack_4c,(float *)&DAT_8032c710,afStack_58);
  zz_0046588_((double)FLOAT_80439b4c,afStack_58,(float *)(param_1 + 0x15c),
              (float *)(param_1 + 0x15c));
  gnt4_PSMTXMultVec_bl(afStack_4c,(float *)&DAT_8032c71c,afStack_58);
  zz_0046588_((double)FLOAT_80439b4c,afStack_58,(float *)(param_1 + 0x168),
              (float *)(param_1 + 0x168));
  *(undefined4 *)(param_1 + 0x174) = *(undefined4 *)(param_1 + 0x15c);
  *(undefined4 *)(param_1 + 0x178) = *(undefined4 *)(param_1 + 0x160);
  *(undefined4 *)(param_1 + 0x17c) = *(undefined4 *)(param_1 + 0x164);
  *(undefined4 *)(param_1 + 0x180) = *(undefined4 *)(param_1 + 0x168);
  *(undefined4 *)(param_1 + 0x184) = *(undefined4 *)(param_1 + 0x16c);
  *(undefined4 *)(param_1 + 0x188) = *(undefined4 *)(param_1 + 0x170);
  *(short *)(param_1 + 0x194) = *(short *)(param_1 + 0x194) + 0x200;
  dVar3 = zz_0045204_(*(short *)(param_1 + 0x194));
  fVar1 = *(float *)(param_1 + 0xb4) * (float)((double)FLOAT_80439b50 * dVar3);
  *(float *)(param_1 + 0x178) = *(float *)(param_1 + 0x178) + fVar1;
  *(float *)(param_1 + 0x184) = *(float *)(param_1 + 0x184) - fVar1;
  if (*(short *)(param_1 + 1000) == 0x70d) {
    *(undefined2 *)(param_1 + 0x18e) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x18c) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(short *)(param_1 + 0x18c) = *(short *)(param_1 + 0x18c) + 0xc0;
    *(short *)(param_1 + 0x18e) = *(short *)(param_1 + 0x18e) + -0xc0;
  }
  return;
}



// ==== 80122a1c  FUN_80122a1c ====

void FUN_80122a1c(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8032c768)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80122a5c  FUN_80122a5c ====

void FUN_80122a5c(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x701) {
    zz_001ab6c_(param_1,0x13);
  }
  else if (*(short *)(param_1 + 1000) == 0x708) {
    zz_001ab6c_(param_1,0x5a);
  }
  return;
}



// ==== 80122aa8  FUN_80122aa8 ====

void FUN_80122aa8(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x701) {
    zz_001ab6c_(param_1,0x12);
  }
  else if (*(short *)(param_1 + 1000) == 0x708) {
    zz_001ab6c_(param_1,0x59);
  }
  return;
}



// ==== 80122af4  FUN_80122af4 ====

void FUN_80122af4(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x701) {
    zz_001ab6c_(param_1,0x13);
    zz_001ab6c_(param_1,0x12);
  }
  else if (*(short *)(param_1 + 1000) == 0x708) {
    zz_001ab6c_(param_1,0x5a);
    zz_001ab6c_(param_1,0x59);
  }
  return;
}



// ==== 80122b70  FUN_80122b70 ====

void FUN_80122b70(int param_1)

{
  short sVar1;
  int iVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((sVar1 == 0x701) || (sVar1 == 0x70c)) {
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      if (*(char *)(param_1 + 0x158) == '\0') {
        *(undefined1 *)(param_1 + 0x158) = 1;
      }
      if (*(char *)(param_1 + 0x159) == '\0') {
        *(undefined1 *)(param_1 + 0x159) = 1;
      }
    }
  }
  else if (sVar1 == 0x708) {
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      zz_00c3be0_(param_1,0x3b);
    }
  }
  else if (sVar1 == 0x70d) {
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      zz_00c3be0_(param_1,0x61);
      if (*(char *)(param_1 + 0x158) == '\0') {
        *(undefined1 *)(param_1 + 0x158) = 1;
      }
      if (*(char *)(param_1 + 0x159) == '\0') {
        *(undefined1 *)(param_1 + 0x159) = 1;
      }
    }
  }
  return;
}



// ==== 80122c74  FUN_80122c74 ====

void FUN_80122c74(int param_1)

{
  (*(code *)(&PTR_FUN_8032c784)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80122cb0  FUN_80122cb0 ====

void FUN_80122cb0(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80439b18) * FLOAT_80439b20);
  (*(code *)(&PTR_FUN_8032c790)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80122d24  FUN_80122d24 ====

void FUN_80122d24(int param_1)

{
  zz_0148d74_(param_1);
  return;
}



// ==== 80122d4c  FUN_80122d4c ====

void FUN_80122d4c(int param_1)

{
  zz_0149178_(param_1);
  return;
}



// ==== 80122d74  FUN_80122d74 ====

void FUN_80122d74(int param_1)

{
  zz_0148d74_(param_1);
  return;
}



// ==== 80122d9c  FUN_80122d9c ====

void FUN_80122d9c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032c7e4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80122dec  FUN_80122dec ====

void FUN_80122dec(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439b54;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_80439b58,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}



// ==== 80122ea8  FUN_80122ea8 ====

void FUN_80122ea8(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  double dVar6;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439b10;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar3 = FLOAT_80439b5c;
    fVar1 = FLOAT_80439b10;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar2 = FLOAT_80439b58;
    *(float *)(param_1 + 0x558) = fVar3;
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar3;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x50) = fVar2;
    fVar1 = *(float *)(*(int *)(param_1 + 0x4b0) + 0x54);
    if (fVar1 < *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = fVar1;
    }
    dVar6 = (double)FLOAT_80439b60;
    *(undefined2 *)(param_1 + 0x54e) = 0;
    uVar5 = FUN_80066838(dVar6,param_1);
    if (0 < (int)uVar5) {
      *(undefined2 *)(param_1 + 0x54e) = 0x8000;
    }
    zz_0066530_(param_1,0x2d);
    *(float *)(param_1 + 0x80c) = FLOAT_80439b10;
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 80122fd4  FUN_80122fd4 ====

void FUN_80122fd4(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  uint uVar4;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  if (*(int *)(param_1 + 0xcc) != 0) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / FLOAT_80439b5c;
    fVar1 = *(float *)(*(int *)(param_1 + 0x4b0) + 0x54);
    if (fVar1 < *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = fVar1;
    }
  }
  FUN_80067310((double)FLOAT_80439b64,param_1,
               *(short *)(param_1 + 0x5ae) + *(short *)(param_1 + 0x54e));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439b10;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar4 = FUN_80066838((double)FLOAT_80439b68,param_1), 0 < (int)uVar4)) {
    fVar1 = FLOAT_80439b6c;
    dVar3 = DOUBLE_80439b30;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar3);
    *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(param_1 + 0x4c) * dVar3);
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x48) * dVar3);
    *(float *)(param_1 + 0x50) = (float)((double)*(float *)(param_1 + 0x50) * dVar3);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 801230fc  FUN_801230fc ====

void FUN_801230fc(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  fVar1 = FLOAT_80439b10;
  if (*(float *)(param_1 + 0x48) < FLOAT_80439b10) {
    *(float *)(param_1 + 0x48) = FLOAT_80439b10;
    *(float *)(param_1 + 0x50) = fVar1;
  }
  FUN_80067310((double)FLOAT_80439b64,param_1,
               *(short *)(param_1 + 0x5ae) + *(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_80439b10;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    dVar3 = (double)FLOAT_80439b58;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,7,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 801231b8  FUN_801231b8 ====

void FUN_801231b8(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  fVar1 = FLOAT_80439b10;
  if (*(float *)(param_1 + 0x48) < FLOAT_80439b10) {
    *(float *)(param_1 + 0x48) = FLOAT_80439b10;
    *(float *)(param_1 + 0x50) = fVar1;
  }
  FUN_80067310((double)FLOAT_80439b64,param_1,
               *(short *)(param_1 + 0x5ae) + *(short *)(param_1 + 0x54e));
  fVar1 = FLOAT_80439b70;
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 80123254  FUN_80123254 ====

void FUN_80123254(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * DOUBLE_80439b78);
    *(undefined1 *)(param_1 + 0x541) = 0xff;
  }
  FUN_80067310((double)FLOAT_80439b64,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cee) != '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0066530_(param_1,0x2c);
    zz_004beb8_((double)FLOAT_80439b58,param_1,0xf,3,8,0xffffffff,0xffffffff);
    *(float *)(param_1 + 0x80c) = FLOAT_80439b10;
  }
  return;
}



// ==== 80123318  FUN_80123318 ====

void FUN_80123318(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_80439b20,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80123390  FUN_80123390 ====

void FUN_80123390(int param_1)

{
  (*(code *)(&PTR_FUN_8032c800)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801233cc  FUN_801233cc ====

void FUN_801233cc(int param_1)

{
  zz_0149708_(param_1);
  return;
}



// ==== 80123534  FUN_80123534 ====

void FUN_80123534(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = -1;
  *(undefined1 *)(param_1 + 0x144) = 0;
  *(undefined1 *)(param_1 + 0x145) = 0;
  *(undefined1 **)(param_1 + 0x4d4) = &LAB_80123808;
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  if (*(short *)(param_1 + 1000) == 0x202) {
    iVar1 = 0;
  }
  if (*(short *)(param_1 + 1000) == 0x20b) {
    iVar1 = 1;
  }
  if (-1 < iVar1) {
    iVar2 = 0;
    do {
      zz_012b59c_(param_1,(char)iVar2,(char)iVar1);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 8);
  }
  return;
}



// ==== 801235d0  FUN_801235d0 ====

void FUN_801235d0(int param_1)

{
  float fVar1;
  double dVar2;
  
  if (*(short *)(param_1 + 1000) == 0x202) {
    if (*(short *)(param_1 + 0x774) < 1) {
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 1;
    }
    else {
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xfe;
    }
    if ((*(uint *)(param_1 + 0x5e0) & 0x81000000) == 0) {
      if (*(char *)(param_1 + 0x5da) != '/') {
        if (*(char *)(param_1 + 0x145) == '\0') {
          *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xfffd;
        }
        else {
          *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 2;
        }
      }
    }
  }
  else if (*(short *)(param_1 + 1000) == 0x20b) {
    if (*(char *)(param_1 + 0x145) == '\0') {
      *(undefined1 *)(param_1 + 0x748) = 0;
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xfd;
    }
    else {
      *(undefined1 *)(param_1 + 0x748) = 1;
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 2;
    }
    if ((*(uint *)(param_1 + 0x5e0) & 0x81000000) == 0) {
      if (*(char *)(param_1 + 0x5da) != '/') {
        *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xfffd;
      }
    }
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    dVar2 = DOUBLE_80439b88;
    fVar1 = FLOAT_80439b80;
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80439b88) * FLOAT_80439b80);
    *(short *)(param_1 + 0x18e2) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) -
                             dVar2) * fVar1);
  }
  return;
}



// ==== 80123730  FUN_80123730 ====

void FUN_80123730(int param_1)

{
  char cVar1;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_00b241c_(param_1);
  }
  cVar1 = *(char *)(param_1 + 0x6e8);
  if (cVar1 == '\x02') {
    *(undefined1 *)(param_1 + 0x6e8) = 0;
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
  }
  else if ((cVar1 < '\x02') && ('\0' < cVar1)) {
    *(undefined1 *)(param_1 + 0x6e8) = 0;
    *(undefined1 *)(param_1 + 0xaf) = 1;
    if (*(short *)(param_1 + 1000) == 0x202) {
      zz_001ab6c_(param_1,0xc);
    }
    else if (*(short *)(param_1 + 1000) == 0x20b) {
      zz_001ab6c_(param_1,0x5e);
    }
  }
  if (((*(char *)(param_1 + 0x145) == '\x03') && (*(char *)(param_1 + 0x5db) != '\x01')) &&
     (*(char *)(param_1 + 0x5db) != '<')) {
    *(undefined1 *)(param_1 + 0x145) = 0;
  }
  return;
}



// ==== 80123854  FUN_80123854 ====

void FUN_80123854(int param_1,char param_2)

{
  if (param_2 == '\x01') {
    if (*(short *)(param_1 + 1000) == 0x20b) {
      zz_00f036c_(param_1,9);
    }
  }
  else if ((param_2 < '\x01') && (-1 < param_2)) {
    *(undefined1 *)(param_1 + 0x145) = 3;
    *(undefined1 *)(param_1 + 0x6f7) = 1;
    zz_00f036c_(param_1,0xd8);
  }
  return;
}



// ==== 801238bc  FUN_801238bc ====

void FUN_801238bc(int param_1)

{
  (*(code *)(&PTR_FUN_8032e370)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801238f8  FUN_801238f8 ====

void FUN_801238f8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
  (*(code *)(&PTR_FUN_8032e37c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8012394c  FUN_8012394c ====

void FUN_8012394c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032e390)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8012399c  FUN_8012399c ====

void FUN_8012399c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80439b90;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined1 *)(param_1 + 0x6f2) = 0;
  if (*(short *)(param_1 + 0x774) < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  zz_006ea9c_(param_1);
  *(undefined1 *)(param_1 + 0x543) = 1;
  if (*(char *)(param_1 + 0x5db) == '\x01') {
    *(undefined1 *)(param_1 + 0x543) = 0xf;
  }
  zz_004beb8_((double)FLOAT_80439b94,param_1,(int)*(char *)(param_1 + 0x543),2,
              (int)*(char *)(param_1 + 0x6f2),0xffffffff,0xffffffff);
  return;
}



// ==== 80123a44  FUN_80123a44 ====

void FUN_80123a44(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = zz_006ea9c_(param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80123ab0  FUN_80123ab0 ====

void FUN_80123ab0(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,1);
  zz_006ea9c_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    iVar1 = zz_006dbe0_(param_1,0,1,0);
    if (iVar1 == 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
      if (*(char *)(param_1 + 0x5db) != '\x01') {
        *(undefined1 *)(param_1 + 0x543) = 1;
      }
      zz_004beb8_((double)FLOAT_80439b94,param_1,(int)*(char *)(param_1 + 0x543),2,
                  *(char *)(param_1 + 0x6f2) + 2,0xffffffff,0xffffffff);
    }
    else {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x543) = 1;
      if (*(char *)(param_1 + 0x5db) == '\x01') {
        *(undefined1 *)(param_1 + 0x543) = 0xf;
      }
      zz_004beb8_((double)FLOAT_80439b94,param_1,(int)*(char *)(param_1 + 0x543),2,
                  *(char *)(param_1 + 0x6f2) + 1,0xffffffff,0xffffffff);
    }
  }
  return;
}



// ==== 80123bb4  FUN_80123bb4 ====

void FUN_80123bb4(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,1);
  zz_006ea9c_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      if (*(short *)(param_1 + 1000) == 0x202) {
        zz_0126294_(param_1,0);
      }
      else if (*(short *)(param_1 + 1000) == 0x20b) {
        zz_0126294_(param_1,1);
      }
    }
  }
  if (((*(char *)(param_1 + 0x1cef) < '\0') && (0 < *(short *)(param_1 + 0x774))) &&
     ((*(uint *)(param_1 + 0x5d4) & 0x20) != 0)) {
    *(undefined1 *)(param_1 + 0x543) = 1;
    if (*(char *)(param_1 + 0x5db) == '\x01') {
      *(undefined1 *)(param_1 + 0x543) = 0xf;
    }
    zz_004beb8_((double)FLOAT_80439b94,param_1,(int)*(char *)(param_1 + 0x543),2,
                *(char *)(param_1 + 0x6f2) + 1,0xffffffff,0xffffffff);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(char *)(param_1 + 0x5db) != '\x01') {
      *(undefined1 *)(param_1 + 0x543) = 1;
    }
    zz_004beb8_((double)FLOAT_80439b94,param_1,(int)*(char *)(param_1 + 0x543),2,
                *(char *)(param_1 + 0x6f2) + 2,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80123d14  FUN_80123d14 ====

void FUN_80123d14(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_004cd24_(param_9,1);
  if (*(char *)(param_9 + 0x1cee) != '\0') {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 80123d70  FUN_80123d70 ====

void FUN_80123d70(int param_1)

{
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  (*(code *)(&PTR_FUN_8032e3a4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80123db8  FUN_80123db8 ====

void FUN_80123db8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032e3b8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80123e20  FUN_80123e20 ====

void FUN_80123e20(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  fVar3 = FLOAT_80439b9c;
  fVar2 = FLOAT_80439b98;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar3;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  *(float *)(param_1 + 0x44) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  uVar4 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar4 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar5 = (double)FLOAT_80439b94;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439b98;
  return;
}



// ==== 80123f08  FUN_80123f08 ====

void FUN_80123f08(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80439ba0;
    fVar1 = FLOAT_80439b98;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) / fVar2;
    }
    else {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x764) / fVar2;
    }
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 80123ff4  FUN_80123ff4 ====

void FUN_80123ff4(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1dd) & 0x80) == 0) {
    zz_006ed8c_((double)FLOAT_80439ba4,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_80439ba8,param_1), 0 < (int)uVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 801240a8  FUN_801240a8 ====

void FUN_801240a8(int param_1)

{
  char cVar1;
  double dVar2;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    *(undefined1 *)(param_1 + 0x746) = 0;
    zz_00b2190_(param_1,0);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar2 = (double)FLOAT_80439b94;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar2,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    return;
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if ((*(char *)(param_1 + 0x1b03) == '\0') && (*(char *)(param_1 + 0x1d0f) != '\0')) {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) /
           FLOAT_80439ba0;
    }
    else {
      *(float *)(param_1 + 0x44) =
           (float)((DOUBLE_80439bb0 * (double)*(float *)(param_1 + 0x764)) / DOUBLE_80439bb8);
    }
    if (FLOAT_80439b98 != *(float *)(param_1 + 0xb4)) {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) / *(float *)(param_1 + 0xb4);
    }
  }
  zz_006ed8c_((double)FLOAT_80439b80,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80124250  FUN_80124250 ====

void FUN_80124250(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032e3c8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801242b8  FUN_801242b8 ====

void FUN_801242b8(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 2;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439b9c;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_80439b94,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439b98;
  return;
}



// ==== 80124388  FUN_80124388 ====

void FUN_80124388(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if (param_1 != -0x1ad4) {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar1 = FLOAT_80439ba0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_80439bc0;
    fVar2 = FLOAT_80439b98;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80439ba0;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 80124484  FUN_80124484 ====

void FUN_80124484(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
  }
  zz_006ed8c_((double)FLOAT_80439ba4,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_80439bc0,param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80124538  FUN_80124538 ====

void FUN_80124538(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
  }
  zz_006ed8c_((double)FLOAT_80439b80,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 801245c8  FUN_801245c8 ====

void FUN_801245c8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032e3d8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80124630  FUN_80124630 ====

void FUN_80124630(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_80439b9c;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_80439b94,param_1,0xf,3,3,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439b98;
  return;
}



// ==== 801246f4  FUN_801246f4 ====

void FUN_801246f4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80439ba0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar1 = FLOAT_80439b98;
    dVar4 = (double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (dVar4 < (double)*(float *)(param_1 + 0x760))) {
      dVar4 = (double)*(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = (float)((DOUBLE_80439bc8 * dVar4) / DOUBLE_80439bb8);
    *(float *)(param_1 + 0x4c) = fVar1;
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    if (FLOAT_80439ba8 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 801247f4  FUN_801247f4 ====

void FUN_801247f4(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_80439ba8,param_1), uVar3 != 0)) {
    fVar1 = FLOAT_80439bd0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80124898  FUN_80124898 ====

/* WARNING: Removing unreachable block (ram,0x80124940) */
/* WARNING: Removing unreachable block (ram,0x801248a8) */

void FUN_80124898(int param_1)

{
  float fVar1;
  bool bVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  else {
    dVar3 = (double)*(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x1dc8) = (float)(dVar3 * DOUBLE_80439bd8);
    zz_004cd24_(param_1,0xf);
    *(float *)(param_1 + 0x1dc8) = (float)dVar3;
  }
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_80439b80,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  bVar2 = fVar1 < FLOAT_80439b98;
  *(float *)(param_1 + 0x558) = fVar1;
  if (bVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 8012495c  FUN_8012495c ====

void FUN_8012495c(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  zz_006ed8c_((double)FLOAT_80439b80,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 801249ec  FUN_801249ec ====

void FUN_801249ec(int param_1)

{
  *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032e3ec)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80124a48  FUN_80124a48 ====

void FUN_80124a48(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80439b9c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 4;
  uVar3 = FUN_800668cc((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439ba4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_80439b94;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80124b60  FUN_80124b60 ====

void FUN_80124b60(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80439ba4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80439ba0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 80124c2c  FUN_80124c2c ====

void FUN_80124c2c(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439be0 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_80439be4;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439be0 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_80439be8,param_1), 0 < (int)uVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80124d08  FUN_80124d08 ====

void FUN_80124d08(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  zz_006ed8c_((double)FLOAT_80439bec,param_1);
  FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    dVar1 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439be0 * dVar1);
    dVar1 = zz_0045204_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439be0 * -dVar1);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 80124dc8  FUN_80124dc8 ====

void FUN_80124dc8(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_80439ba4,param_1);
  FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439be4 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80124e8c  FUN_80124e8c ====

void FUN_80124e8c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032e400)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80124ee8  FUN_80124ee8 ====

void FUN_80124ee8(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_80439b9c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  zz_004beb8_((double)FLOAT_80439b94,param_1,0xf,3,5,0xffffffff,0xffffffff);
  zz_0124fbc_(param_1);
  return;
}



// ==== 80124fbc  zz_0124fbc_ ====

void zz_0124fbc_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439ba4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar3 = FLOAT_80439ba0;
    fVar1 = FLOAT_80439b90;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar2 = FLOAT_80439b98;
    *(float *)(param_1 + 0x558) = fVar3;
    *(float *)(param_1 + 0x55c) = fVar1;
    *(float *)(param_1 + 0x560) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x50) = fVar2;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 8012509c  FUN_8012509c ====

void FUN_8012509c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  
  iVar3 = zz_01252c8_(param_1);
  if (iVar3 != 0) {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar5 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439be0 * dVar5);
  dVar5 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar6 = (double)FLOAT_80439be4;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439be0 * -dVar5);
  FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar4 = FUN_800668cc((double)FLOAT_80439bf0,param_1), 0 < (int)uVar4)) {
    dVar5 = DOUBLE_80439bd8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar5);
    *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(param_1 + 0x4c) * dVar5);
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x48) * dVar5);
    *(float *)(param_1 + 0x50) = (float)((double)*(float *)(param_1 + 0x50) * dVar5);
  }
  return;
}



// ==== 801251c0  FUN_801251c0 ====

void FUN_801251c0(int param_1)

{
  float fVar1;
  int iVar2;
  
  iVar2 = zz_01252c8_(param_1);
  if (iVar2 != 0) {
    zz_004cd24_(param_1,0xf);
  }
  fVar1 = FLOAT_80439b98;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar1 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar1;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_80439ba4,param_1);
  FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439be4 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 801252c8  zz_01252c8_ ====

undefined4 zz_01252c8_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  
  fVar3 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x55c) <= FLOAT_80439b98) || (*(char *)(param_1 + 0x1cf0) == '\0')) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    uVar4 = 0x81cd;
  }
  else {
    *(short *)(param_1 + 0x1900) =
         (short)(int)-(FLOAT_80439bf4 * fVar1 -
                      (float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                             DOUBLE_80439b88));
    fVar2 = *(float *)(param_1 + 0x55c) - fVar1;
    *(float *)(param_1 + 0x55c) = fVar2;
    if (fVar2 <= fVar3) {
      *(undefined1 *)(param_1 + 0x1cf0) = 0;
    }
    fVar3 = FLOAT_80439b98;
    fVar1 = *(float *)(param_1 + 0x560) - fVar1;
    *(float *)(param_1 + 0x560) = fVar1;
    if (fVar1 <= fVar3) {
      *(float *)(param_1 + 0x560) = FLOAT_80439bf8;
      zz_00f036c_(param_1,0xb);
    }
    uVar4 = 0;
  }
  return uVar4;
}



// ==== 801253a0  FUN_801253a0 ====

void FUN_801253a0(int param_1)

{
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
  (*(code *)(&PTR_FUN_8032e410)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80125400  FUN_80125400 ====

void FUN_80125400(int param_1)

{
  *(short *)(param_1 + 0x18dc) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18dc) ^ 0x80000000) -
                           DOUBLE_80439b88) * FLOAT_80439bfc);
  (*(code *)(&PTR_FUN_8032e424)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80125474  FUN_80125474 ====

void FUN_80125474(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if (*(short *)(param_1 + 1000) == 0x20b) {
    *(undefined1 *)(param_1 + 0x6ea) = 2;
  }
  zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_80439b98;
  *(float *)(param_1 + 0x50) = FLOAT_80439b98;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(float *)(param_1 + 0x48) = FLOAT_80439be0;
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80439b94;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  zz_0125550_(param_1);
  return;
}



// ==== 80125550  zz_0125550_ ====

void zz_0125550_(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d0dc_(param_1,0xc1,0);
  gnt4_PSQUATScale_bl((double)FLOAT_80439ba4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_006ed8c_((double)FLOAT_80439b80,param_1);
  FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    fVar2 = FLOAT_80439c00;
    if (*(char *)(param_1 + 0x145) != '\0') {
      *(undefined1 *)(param_1 + 0x540) = 5;
      fVar1 = FLOAT_80439b98;
      *(float *)(param_1 + 0x558) = fVar2;
      dVar3 = (double)FLOAT_80439b94;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x44) = fVar1;
      *(float *)(param_1 + 0x48) = fVar1;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      zz_004beb8_(dVar3,param_1,0xf,0,0xd,0x14,1);
      return;
    }
    zz_0046698_(param_1);
    *(undefined1 *)(param_1 + 0x145) = 1;
    if (*(short *)(param_1 + 1000) == 0x202) {
      *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 2;
      zz_01281d4_(param_1,0);
    }
    else if (*(short *)(param_1 + 1000) == 0x20b) {
      zz_01281d4_(param_1,1);
    }
  }
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 801256ac  FUN_801256ac ====

void FUN_801256ac(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  zz_004cd24_(param_1,0xf);
  zz_006d0dc_(param_1,0xc1,0);
  FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar4 = FLOAT_80439c00;
  fVar3 = FLOAT_80439be8;
  fVar2 = FLOAT_80439b98;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    if ((*(short *)(param_1 + 1000) == 0x202) && (*(char *)(param_1 + 0x145) == '\x01')) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x55c) = fVar3;
      *(undefined1 *)(param_1 + 0x145) = 2;
      *(float *)(param_1 + 0x50) = fVar2;
      *(float *)(param_1 + 0x48) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(undefined2 *)(param_1 + 0x80) = 0;
      *(undefined2 *)(param_1 + 0x7e) = 0;
      *(undefined2 *)(param_1 + 0x7c) = 0;
      *(undefined1 *)(param_1 + 0x6f7) = 1;
      *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 2;
      zz_00f036c_(param_1,0xd8);
      cVar1 = *(char *)(param_1 + 0x6ea);
      dVar5 = (double)FLOAT_80439b94;
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar5,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
    }
    else {
      *(undefined1 *)(param_1 + 0x540) = 5;
      fVar2 = FLOAT_80439b98;
      *(float *)(param_1 + 0x558) = fVar4;
      dVar5 = (double)FLOAT_80439b94;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(float *)(param_1 + 0x48) = fVar2;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      zz_004beb8_(dVar5,param_1,0xf,0,0xd,0x14,1);
    }
  }
  return;
}



// ==== 80125880  FUN_80125880 ====

void FUN_80125880(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_80439b98;
  *(undefined1 *)(param_1 + 0x145) = 0;
  if (*(float *)(param_1 + 0x55c) <= fVar2) {
    zz_004cd24_(param_1,0xf);
    FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  }
  else {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_80439b98;
  if (iVar3 == 0) {
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
    *(float *)(param_1 + 0x694) = FLOAT_80439be4 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80125968  FUN_80125968 ====

void FUN_80125968(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_80439b98;
  if (iVar3 == 0) {
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
    *(float *)(param_1 + 0x694) = FLOAT_80439be4 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80125b48  FUN_80125b48 ====

void FUN_80125b48(int param_1)

{
  zz_00c74ec_(param_1,0x1c);
  zz_004f1c4_(param_1);
  if (*(short *)(param_1 + 1000) == 0x604) {
    zz_012aa24_(param_1,0);
    zz_012aa24_(param_1,1);
  }
  else if (*(short *)(param_1 + 1000) == 0x618) {
    zz_012aa24_(param_1,6);
    zz_012aa24_(param_1,7);
  }
  return;
}



// ==== 80125bcc  FUN_80125bcc ====

void FUN_80125bcc(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80439c10;
  fVar1 = FLOAT_80439c08;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x191e) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x191e) ^ 0x80000000) -
                             DOUBLE_80439c10) * FLOAT_80439c08);
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             dVar2) * fVar1);
  }
  return;
}



// ==== 80125c58  FUN_80125c58 ====

void FUN_80125c58(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8032f408)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80125c98  FUN_80125c98 ====

void FUN_80125c98(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x604) {
    zz_001ab6c_(param_1,0x2b);
  }
  else if (*(short *)(param_1 + 1000) == 0x618) {
    zz_001ab6c_(param_1,100);
  }
  return;
}



// ==== 80125ce4  FUN_80125ce4 ====

void FUN_80125ce4(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x604) {
    zz_001ab6c_(param_1,0x2a);
  }
  else if (*(short *)(param_1 + 1000) == 0x618) {
    zz_001ab6c_(param_1,99);
  }
  return;
}



// ==== 80125d30  FUN_80125d30 ====

void FUN_80125d30(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x604) {
    zz_001ab6c_(param_1,0x2b);
    zz_001ab6c_(param_1,0x2a);
  }
  else if (*(short *)(param_1 + 1000) == 0x618) {
    zz_001ab6c_(param_1,100);
    zz_001ab6c_(param_1,99);
  }
  return;
}



// ==== 80125dac  FUN_80125dac ====

void FUN_80125dac(int param_1)

{
  (*(code *)(&PTR_FUN_8032f41c)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80125de8  FUN_80125de8 ====

void FUN_80125de8(double param_1,double param_2,double param_3,double param_4,double param_5,
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
    fVar1 = FLOAT_80439c18;
    *(undefined1 *)(param_9 + 0x6ea) = 5;
    *(float *)(param_9 + 0x558) = fVar1;
  }
  iVar3 = zz_006672c_(param_9);
  dVar5 = DOUBLE_80439c10;
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
                             DOUBLE_80439c10);
    *(short *)(param_9 + 0x191e) = (short)(int)(param_1 * (double)FLOAT_80439c1c);
  }
  if (*(char *)(param_9 + 0x6ea) < '\x05') {
    if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_9 + 0x5d4) & 1) == 0))
    goto LAB_80125edc;
LAB_80125f88:
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,param_9,6,param_11,
                param_12,param_13,param_14,param_15,param_16);
    *(float *)(param_9 + 0x694) = FLOAT_80439c20 + *(float *)(param_9 + 0x1dc8);
  }
  else {
LAB_80125edc:
    param_1 = (double)*(float *)(param_9 + 0x558);
    if (param_1 <= (double)FLOAT_80439c18) {
      *(float *)(param_9 + 0x558) = FLOAT_80439c20;
      cVar4 = *(char *)(param_9 + 0x6ea) + -1;
      *(char *)(param_9 + 0x6ea) = cVar4;
      if (cVar4 < '\0') goto LAB_80125f88;
      param_11 = 1;
      param_12 = 1;
      iVar3 = zz_006dbe0_(param_9,0,1,1);
      if (iVar3 != 0) {
        param_1 = (double)zz_006bf80_(param_9);
        if (*(short *)(param_9 + 1000) == 0x604) {
          zz_0082824_(param_9,0x2b);
          param_1 = (double)zz_0082824_(param_9,0x2c);
        }
        else if (*(short *)(param_9 + 1000) == 0x618) {
          zz_0082824_(param_9,0x4b);
          param_1 = (double)zz_0082824_(param_9,0x4c);
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



// ==== 80125fdc  FUN_80125fdc ====

void FUN_80125fdc(int param_1)

{
  (*(code *)(&PTR_FUN_8032f42c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80126018  FUN_80126018 ====

void FUN_80126018(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 8012604c  FUN_8012604c ====

void FUN_8012604c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0177dd8_(param_1);
  return;
}



// ==== 80126080  FUN_80126080 ====

void FUN_80126080(int param_1)

{
  zz_0178394_(param_1);
  return;
}



// ==== 801260a8  FUN_801260a8 ====

void FUN_801260a8(int param_1)

{
  zz_01260c8_(param_1);
  return;
}



// ==== 801260c8  zz_01260c8_ ====

void zz_01260c8_(int param_1)

{
  zz_017a374_(param_1);
  return;
}



// ==== 801260f0  FUN_801260f0 ====

void FUN_801260f0(int param_1)

{
  zz_0126110_(param_1);
  return;
}



// ==== 80126110  zz_0126110_ ====

void zz_0126110_(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  }
  zz_0179fcc_(param_1);
  return;
}



// ==== 80126150  FUN_80126150 ====

void FUN_80126150(int param_1)

{
  zz_006d0dc_(param_1,0xc1,0);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  return;
}



// ==== 801261a0  FUN_801261a0 ====

uint FUN_801261a0(uint param_1)

{
  float fVar1;
  float fVar2;
  bool bVar5;
  int iVar3;
  bool bVar6;
  uint uVar4;
  
  bVar6 = false;
  *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
  if (*(short *)(param_1 + 1000) == 0x604) {
    zz_0182fcc_(param_1,0,0);
    bVar5 = zz_0182fcc_(param_1,1,0);
    bVar6 = true;
    uVar4 = (uint)bVar5;
  }
  else {
    uVar4 = param_1;
    if ((*(short *)(param_1 + 1000) == 0x618) &&
       (iVar3 = zz_006dbe0_(param_1,2,1,1), uVar4 = 0, iVar3 != 0)) {
      zz_0182fcc_(param_1,2,1);
      bVar6 = zz_0182fcc_(param_1,3,1);
      uVar4 = (uint)bVar6;
      bVar6 = true;
    }
  }
  fVar1 = FLOAT_80439c28;
  if (bVar6) {
    *(float *)(param_1 + 0x44) = FLOAT_80439c24;
    fVar2 = FLOAT_80439c2c;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2;
    uVar4 = *(uint *)(param_1 + 0x4ac);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(uVar4 + 0x6c);
  }
  fVar1 = FLOAT_80439c18;
  *(float *)(param_1 + 0x40) = FLOAT_80439c18;
  *(float *)(param_1 + 0x3c) = fVar1;
  *(float *)(param_1 + 0x38) = fVar1;
  return uVar4;
}



// ==== 80126294  zz_0126294_ ====

void zz_0126294_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x202) || (*(short *)(param_1 + 1000) == 0x20b)) {
    puVar1 = zz_0088aa0_(param_1,3,8,0,1);
    if (puVar1 == (undefined1 *)0x0) {
      zz_0126d78_(0,param_1);
    }
    else {
      *puVar1 = 1;
      puVar1[0x10] = 0x1a;
      puVar1[0x11] = param_2;
      *(code **)(puVar1 + 0xc) = FUN_80126420;
      *(code **)(puVar1 + 0x10c) = FUN_80126d1c;
      *(code **)(puVar1 + 0x100) = FUN_80126b7c;
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
      gnt4_PSMTXMultVec_bl
                ((float *)(param_1 +
                          (char)(&DAT_8032fa1a)[(uint)(byte)puVar1[0x11] * 0x38] * 0x30 + 0x8d4),
                 (float *)((uint)(byte)puVar1[0x11] * 0x38 + -0x7fcd05e4),(float *)(puVar1 + 0x20));
      zz_0083d60_((int)puVar1,param_1,0);
      *(undefined2 *)(puVar1 + 0x70) = 0;
      *(undefined2 *)(puVar1 + 0x72) = *(undefined2 *)(param_1 + 0x72);
      *(undefined2 *)(puVar1 + 0x74) = 0;
    }
  }
  return;
}



// ==== 80126420  FUN_80126420 ====

void FUN_80126420(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8032fa88)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801264c0  FUN_801264c0 ====

void FUN_801264c0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
  iVar6 = *(int *)(param_9 + 0x90);
  puVar4 = &DAT_8032fa18;
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x38;
  *(undefined1 *)(param_9 + 0x1b) = 4;
  iVar3 = iVar5;
  uVar7 = zz_0089100_(param_9,1,1);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar2 = zz_0006f78_(param_9);
  zz_0006fb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
              *(int *)(param_9 + 0xe0),(uint)*(ushort *)(&DAT_8032fa18 + iVar5),puVar4,iVar3,in_r8,
              in_r9,in_r10);
  fVar1 = FLOAT_80439c30;
  *(undefined1 *)(param_9 + 0x148) = 0;
  *(float *)(param_9 + 0x144) = fVar1;
  *(undefined1 *)(param_9 + 0x149) = 0;
  *(undefined2 *)(param_9 + 0x14a) = 0x4b0;
  iVar3 = zz_008ac80_(param_9,(int)(char)(&DAT_8032fa1b)[iVar5]);
  if (iVar3 == 0) {
    zz_0126d78_(param_9,iVar6);
  }
  else {
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8032fa28 + iVar5),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8032fa28 + iVar5);
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8032fa2c + iVar5);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8032fa2e + iVar5);
    *(undefined1 *)(param_9 + 0xa8) = 1;
    zz_00c74ec_(param_9,0x45);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    zz_01265f8_(param_9);
    *(undefined1 *)(param_9 + 0xaf) = 0;
  }
  return;
}



// ==== 801265f8  zz_01265f8_ ====

void zz_01265f8_(int param_1)

{
  char cVar1;
  short sVar2;
  
  sVar2 = *(short *)(param_1 + 0x14a) + -1;
  *(short *)(param_1 + 0x14a) = sVar2;
  if (sVar2 < 1) {
    zz_0126d78_(param_1,*(int *)(param_1 + 0x90));
  }
  else {
    cVar1 = *(char *)(param_1 + 0x19);
    if (cVar1 == '\x01') {
      zz_0126820_(param_1);
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      zz_0126680_(param_1);
    }
    if ('\0' < *(char *)(param_1 + 0x148)) {
      *(char *)(param_1 + 0x148) = *(char *)(param_1 + 0x148) + -1;
    }
  }
  return;
}



// ==== 80126680  zz_0126680_ ====

void zz_0126680_(int param_1)

{
  float fVar1;
  int iVar2;
  char cVar3;
  
  if (*(char *)(param_1 + 0x148) < '\x01') {
    *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0xc00;
  }
  fVar1 = FLOAT_80439c38;
  *(float *)(param_1 + 0x144) = *(float *)(param_1 + 0x144) + FLOAT_80439c34;
  if (fVar1 < *(float *)(param_1 + 0x144)) {
    *(float *)(param_1 + 0x144) = fVar1;
  }
  if ((0 < *(short *)(param_1 + 0x1c)) &&
     (iVar2 = zz_0083244_((float *)(param_1 + 0x20)), iVar2 == 0)) {
    if (*(char *)(param_1 + 0x1d9) == '\0') {
LAB_80126738:
      if (*(char *)(param_1 + 0x19) != '\0') goto LAB_801267f8;
      *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
      iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x38;
      FUN_80083874((double)*(float *)(&DAT_8032fa34 + iVar2),param_1);
      FUN_80083ad4((double)*(float *)(&DAT_8032fa30 + iVar2),param_1,
                   (char)*(undefined2 *)(&DAT_8032fa2e + iVar2));
      zz_00833ec_(param_1);
      zz_0083524_(param_1);
      iVar2 = zz_0083714_(param_1);
      if ((iVar2 == 0) && (iVar2 = zz_0084170_(param_1), iVar2 == 0)) goto LAB_801267f8;
    }
    else if (*(char *)(param_1 + 0x11) == '\0') {
      *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * DOUBLE_80439c40);
      *(undefined1 *)(param_1 + 0x148) = 8;
      cVar3 = *(char *)(param_1 + 0x1b) + -1;
      *(char *)(param_1 + 0x1b) = cVar3;
      if ('\0' < cVar3) goto LAB_80126738;
    }
  }
  fVar1 = FLOAT_80439c48;
  *(undefined1 *)(param_1 + 0x19) = 1;
  *(undefined1 *)(param_1 + 0x1a) = 1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x1e) = 0xf;
  zz_008aff0_(param_1);
  if (*(char *)(param_1 + 0x11) != '\0') {
    zz_0126d78_(param_1,*(int *)(param_1 + 0x90));
    return;
  }
LAB_801267f8:
  zz_00f0104_(param_1,0xf,2);
  return;
}



// ==== 80126820  zz_0126820_ ====

void zz_0126820_(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar5 = *(int *)(param_1 + 0x90);
  *(undefined2 *)(param_1 + 0x70) = 0;
  fVar2 = FLOAT_80439c30;
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x38;
  if ((*(char *)(param_1 + 0x148) < '\x01') &&
     (*(float *)(param_1 + 0x144) = (float)((double)*(float *)(param_1 + 0x144) - DOUBLE_80439c50),
     *(float *)(param_1 + 0x144) < fVar2)) {
    *(float *)(param_1 + 0x144) = fVar2;
  }
  if ((*(char *)(param_1 + 0x1d9) != '\0') && (*(char *)(param_1 + 0x148) == '\0')) {
    *(undefined1 *)(param_1 + 0x148) = 3;
  }
  if (*(char *)(param_1 + 0x148) < '\x01') {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  }
  fVar2 = FLOAT_80439c48;
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + FLOAT_80439c58;
    if (*(float *)(&DAT_8032fa28 + iVar3) <= *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = *(float *)(&DAT_8032fa28 + iVar3);
      *(undefined1 *)(param_1 + 0x1a) = 3;
    }
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) - FLOAT_80439c58;
        if (*(float *)(param_1 + 0x44) <= fVar2) {
          *(float *)(param_1 + 0x44) = fVar2;
          *(undefined1 *)(param_1 + 0x1a) = 1;
          *(undefined2 *)(param_1 + 0x1e) = 0xf;
          return;
        }
        if ('\0' < *(char *)(param_1 + 0x148)) {
          return;
        }
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                         (float *)(param_1 + 0x20));
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
      fVar2 = FLOAT_80439c5c;
      *(undefined1 *)(param_1 + 0x149) = 1;
      dVar6 = (double)FLOAT_80439c60;
      *(float *)(param_1 + 0x44) = fVar2;
      *(short *)(param_1 + 0x1e) = (short)*(undefined4 *)(&DAT_8032fa44 + iVar3);
      gnt4_PSQUATScale_bl(dVar6,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  iVar4 = iVar5 + (char)(&DAT_8032fa1a)[iVar3] * 0x30;
  local_24 = *(float *)(iVar4 + 0x8e0);
  local_20 = *(undefined4 *)(iVar4 + 0x8f0);
  local_1c = *(undefined4 *)(iVar4 + 0x900);
  dVar6 = gnt4_PSVECSquareDistance_bl(&local_24,(float *)(param_1 + 0x20));
  if ((double)FLOAT_80439c48 < dVar6) {
    dVar7 = 1.0 / SQRT(dVar6);
    dVar7 = DOUBLE_80439c68 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80439c70);
    dVar7 = DOUBLE_80439c68 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80439c70);
    dVar6 = (double)(float)(dVar6 * DOUBLE_80439c68 * dVar7 *
                                    -(dVar6 * dVar7 * dVar7 - DOUBLE_80439c70));
  }
  if ((double)*(float *)(param_1 + 0x44) <= dVar6) {
    if (*(char *)(param_1 + 0x148) < '\x01') {
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
      if (*(short *)(param_1 + 0x1e) < 1) {
        *(short *)(param_1 + 0x1e) = (short)*(undefined4 *)(&DAT_8032fa44 + iVar3);
        zz_006c440_((double)*(float *)(&DAT_8032fa48 + iVar3),param_1,&local_24);
      }
      else {
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                         (float *)(param_1 + 0x20));
      }
    }
  }
  else {
    zz_0126d78_(param_1,iVar5);
  }
  return;
}



// ==== 80126b20  FUN_80126b20 ====

void FUN_80126b20(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80126b5c  FUN_80126b5c ====

void FUN_80126b5c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80126b7c  FUN_80126b7c ====

/* WARNING: Removing unreachable block (ram,0x80126cac) */
/* WARNING: Removing unreachable block (ram,0x80126c84) */
/* WARNING: Removing unreachable block (ram,0x80126c5c) */

void FUN_80126b7c(int param_1)

{
  int iVar1;
  double dVar2;
  float local_48;
  float local_44;
  float local_40;
  float afStack_3c [14];
  
  gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  local_48 = *(float *)(param_1 + 0x38);
  local_44 = *(float *)(param_1 + 0x3c);
  local_40 = *(float *)(param_1 + 0x40);
  dVar2 = gnt4_PSVECMag_bl(&local_48);
  if (dVar2 <= (double)FLOAT_80439c48) {
    if ((double)*(float *)(param_1 + 0x3c) < (double)FLOAT_80439c48) {
      *(undefined2 *)(param_1 + 0x74) = 0x4000;
      *(undefined2 *)(param_1 + 0x72) = 0;
    }
    else {
      *(undefined2 *)(param_1 + 0x74) = 0xc000;
      *(undefined2 *)(param_1 + 0x72) = 0;
    }
  }
  else {
    iVar1 = FUN_800452a0((double)*(float *)(param_1 + 0x3c),dVar2);
    *(short *)(param_1 + 0x74) = (short)iVar1;
    iVar1 = FUN_800452a0((double)*(float *)(param_1 + 0x38),(double)*(float *)(param_1 + 0x40));
    *(short *)(param_1 + 0x72) = (short)iVar1;
  }
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x4000;
  if (*(char *)(param_1 + 0x149) != '\0') {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x8000;
  }
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80439c78 *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                             0x3ff0000000000000)),afStack_3c,0x79);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80439c78 *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x74) *
                                             0x3ff0000000000000)),afStack_3c,0x7a);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80439c78 *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                             0x3ff0000000000000)),afStack_3c,0x78);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x144),(float *)(param_1 + 0x58),&local_48);
  gnt4_PSMTXScale_bl((double)local_48,(double)local_44,(double)local_40,afStack_3c);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
  return;
}



// ==== 80126d1c  FUN_80126d1c ====

void FUN_80126d1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 80126d78  zz_0126d78_ ====

void zz_0126d78_(int param_1,int param_2)

{
  if (param_1 != 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  if (*(char *)(param_1 + 0x11) == '\0') {
    if (param_2 != 0) {
      *(undefined1 *)(param_2 + 0x144) = 0;
      zz_006de10_(param_2,0);
    }
  }
  else {
    zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),0);
  }
  return;
}



// ==== 80126f24  FUN_80126f24 ====

void FUN_80126f24(int param_1)

{
  zz_00c74ec_(param_1,0x1d);
  zz_00c74ec_(param_1,0x1e);
  zz_004f1c4_(param_1);
  if (*(short *)(param_1 + 1000) == 0x605) {
    zz_012aa24_(param_1,2);
    zz_012aa24_(param_1,3);
  }
  else if (*(short *)(param_1 + 1000) == 0x619) {
    zz_012aa24_(param_1,8);
    zz_012aa24_(param_1,9);
  }
  return;
}



// ==== 80126fd4  FUN_80126fd4 ====

void FUN_80126fd4(int param_1)

{
  float fVar1;
  double dVar2;
  
  zz_006d520_(param_1,(float *)&DAT_80330350);
  dVar2 = DOUBLE_80439c88;
  fVar1 = FLOAT_80439c80;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18e0) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) -
                             DOUBLE_80439c88) * FLOAT_80439c80);
    *(short *)(param_1 + 0x18e2) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x1962) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1962) ^ 0x80000000) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x196e) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x196e) ^ 0x80000000) -
                             dVar2) * fVar1);
  }
  return;
}



// ==== 801270fc  FUN_801270fc ====

void FUN_801270fc(char *param_1)

{
  if ((*(short *)(param_1 + 1000) == 0x605) && ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0)) {
    zz_00f036c_((int)param_1,0xb2);
    zz_006a8c0_(param_1,0x604);
    zz_005f00c_((int)param_1);
    zz_017a608_((int)param_1);
  }
  return;
}



// ==== 80127174  FUN_80127174 ====

void FUN_80127174(int param_1)

{
  (*(code *)(&PTR_FUN_80330380)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801271b0  FUN_801271b0 ====

void FUN_801271b0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80330390)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801271f8  FUN_801271f8 ====

void FUN_801271f8(int param_1)

{
  zz_0177634_(param_1);
  return;
}



// ==== 80127220  FUN_80127220 ====

void FUN_80127220(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    if (*(short *)(param_1 + 1000) == 0x605) {
      zz_00c3be0_(param_1,0x23);
      zz_00c3be0_(param_1,0x24);
    }
    else if (*(short *)(param_1 + 1000) == 0x619) {
      zz_00c3be0_(param_1,0x4f);
      zz_00c3be0_(param_1,0x50);
    }
    *(float *)(param_1 + 0x558) = FLOAT_80439c90;
  }
  return;
}



// ==== 801272b0  FUN_801272b0 ====

undefined4 FUN_801272b0(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (((*(uint *)(param_1 + 0x5bc) & 0x200) == 0) ||
     (iVar1 = zz_006dbe0_(param_1,0,1,0), iVar1 == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 0x8444;
  }
  return uVar2;
}



// ==== 80127300  FUN_80127300 ====

undefined4 FUN_80127300(int param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  float local_18;
  undefined4 local_14;
  float local_10;
  
  iVar2 = zz_017a6e0_(param_1,2,(short *)(param_1 + 0x18e0),0);
  iVar3 = zz_017a884_(param_1,2,(short *)(param_1 + 0x18e2),0);
  if (iVar2 + iVar3 == 2) {
    if (*(int *)(param_1 + 0xcc) != 0) {
      local_18 = *(float *)(param_1 + 0x93c);
      local_14 = *(undefined4 *)(param_1 + 0x94c);
      local_10 = *(float *)(param_1 + 0x95c);
      iVar2 = FUN_800452a0((double)local_18,(double)local_10);
      local_18 = *(float *)(param_1 + 0xd30);
      local_14 = *(undefined4 *)(param_1 + 0xd40);
      local_10 = *(float *)(param_1 + 0xd50);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_18,&local_18);
      iVar3 = FUN_800452a0((double)local_18,(double)local_10);
      sVar1 = -((short)iVar3 - (short)iVar2);
      if (0 < sVar1) {
        sVar1 = 0;
      }
      if (sVar1 < -0x2000) {
        sVar1 = -0x2000;
      }
      *(short *)(param_1 + 0x1962) = sVar1;
      local_18 = *(float *)(param_1 + 0xd90);
      local_14 = *(undefined4 *)(param_1 + 0xda0);
      local_10 = *(float *)(param_1 + 0xdb0);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_18,&local_18);
      iVar3 = FUN_800452a0((double)local_18,(double)local_10);
      sVar1 = -((short)iVar3 - (short)iVar2);
      if (sVar1 < 0) {
        sVar1 = 0;
      }
      if (0x2000 < sVar1) {
        sVar1 = 0x2000;
      }
      *(short *)(param_1 + 0x196e) = sVar1;
    }
    uVar4 = 0x8444;
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}



// ==== 8012745c  FUN_8012745c ====

void FUN_8012745c(char *param_1)

{
  param_1[0x581] = '\x03';
  zz_00f036c_((int)param_1,0xb2);
  zz_006a8c0_(param_1,0x604);
  zz_017a608_((int)param_1);
  return;
}



// ==== 801274ac  FUN_801274ac ====

void FUN_801274ac(int param_1)

{
  zz_01274cc_(param_1);
  return;
}



// ==== 801274cc  zz_01274cc_ ====

void zz_01274cc_(int param_1)

{
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  zz_017a374_(param_1);
  return;
}



// ==== 8012750c  FUN_8012750c ====

void FUN_8012750c(int param_1)

{
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  zz_0127544_(param_1);
  return;
}



// ==== 80127544  zz_0127544_ ====

void zz_0127544_(int param_1)

{
  zz_0177a3c_(param_1);
  return;
}



// ==== 8012756c  FUN_8012756c ====

uint FUN_8012756c(uint param_1)

{
  bool bVar3;
  int iVar1;
  uint uVar2;
  
  if (*(short *)(param_1 + 1000) == 0x605) {
    zz_0182fcc_(param_1,0,0);
    bVar3 = zz_0182fcc_(param_1,1,0);
    uVar2 = (uint)bVar3;
  }
  else {
    uVar2 = param_1;
    if ((*(short *)(param_1 + 1000) == 0x619) &&
       (iVar1 = zz_006dbe0_(param_1,2,1,1), uVar2 = 0, iVar1 != 0)) {
      zz_0182fcc_(param_1,2,1);
      bVar3 = zz_0182fcc_(param_1,3,1);
      uVar2 = (uint)bVar3;
    }
  }
  return uVar2;
}



// ==== 80127600  zz_0127600_ ====

void zz_0127600_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  int iVar3;
  float *pfVar4;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((sVar1 == 0xa04) || (sVar1 == 0xa08)) || (sVar1 == 0xa09)) {
    puVar2 = zz_0088aa0_(param_1,3,8,0,1);
    if (puVar2 == (undefined1 *)0x0) {
      zz_01281a8_(param_1);
    }
    else {
      *puVar2 = 1;
      puVar2[0x10] = 0x40;
      puVar2[0x11] = param_2;
      *(code **)(puVar2 + 0xc) = FUN_801277a0;
      *(code **)(puVar2 + 0x10c) = FUN_8012814c;
      *(code **)(puVar2 + 0x100) = FUN_80127e20;
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
      pfVar4 = (float *)(param_1 +
                        (char)(&DAT_8033089e)[(uint)(byte)puVar2[0x11] * 0x38] * 0x30 + 0x8d4);
      gnt4_PSMTXMultVec_bl
                (pfVar4,(float *)((uint)(byte)puVar2[0x11] * 0x38 + -0x7fccf760),
                 (float *)(puVar2 + 0x20));
      zz_0083d60_((int)puVar2,param_1,1);
      *(undefined2 *)(puVar2 + 0x70) = 0;
      iVar3 = FUN_800452a0((double)pfVar4[10],(double)pfVar4[2]);
      *(short *)(puVar2 + 0x72) = (short)iVar3;
      *(undefined2 *)(puVar2 + 0x74) = 0;
    }
  }
  return;
}



// ==== 801277a0  FUN_801277a0 ====

void FUN_801277a0(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80330944)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80127838  FUN_80127838 ====

void FUN_80127838(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  puVar3 = &DAT_8033089c;
  iVar4 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar1 = (uint)*(byte *)(param_9 + 0x11) * 0x38;
  uVar5 = zz_0089100_(param_9,1,1);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar2 = zz_0006f78_(param_9);
  zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
              *(int *)(param_9 + 0xe0),(uint)*(ushort *)(&DAT_8033089c + iVar1),puVar3,in_r7,in_r8,
              in_r9,in_r10);
  *(undefined1 *)(param_9 + 0x144) = 0;
  *(undefined1 *)(param_9 + 0x145) = 0;
  iVar2 = zz_008ac80_(param_9,(int)(char)(&DAT_8033089f)[iVar1]);
  if (iVar2 == 0) {
    zz_01281a8_(iVar4);
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_803308ac + iVar1),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_803308ac + iVar1);
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_803308b0 + iVar1);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_803308b2 + iVar1);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    zz_0127940_(param_9);
  }
  return;
}



// ==== 80127940  zz_0127940_ ====

void zz_0127940_(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    zz_0127af8_(param_1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_01279dc_(param_1);
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
  return;
}



// ==== 801279dc  zz_01279dc_ ====

void zz_01279dc_(int param_1)

{
  float fVar1;
  int iVar2;
  
  iVar2 = zz_0083244_((float *)(param_1 + 0x20));
  if (iVar2 == 0) {
    if (*(char *)(param_1 + 0x1d9) != '\0') {
      *(undefined1 *)(param_1 + 0x19) = 1;
      *(undefined2 *)(param_1 + 0x1e) = 8;
      *(undefined1 *)(param_1 + 0x144) = 8;
    }
    if (*(char *)(param_1 + 0x19) != '\0') {
      return;
    }
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
    iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x38;
    FUN_80083874((double)*(float *)(&DAT_803308b8 + iVar2),param_1);
    FUN_80083ad4((double)*(float *)(&DAT_803308b4 + iVar2),param_1,
                 (char)*(undefined2 *)(&DAT_803308b2 + iVar2));
    zz_00833ec_(param_1);
    zz_0083524_(param_1);
    iVar2 = zz_0083714_(param_1);
    if ((iVar2 == 0) && (iVar2 = zz_0084170_(param_1), iVar2 == 0)) {
      if (0 < *(short *)(param_1 + 0x1c)) {
        return;
      }
      *(undefined1 *)(param_1 + 0x19) = 1;
      *(undefined1 *)(param_1 + 0x1a) = 0;
      return;
    }
  }
  fVar1 = FLOAT_80439c98;
  *(undefined1 *)(param_1 + 0x19) = 1;
  *(undefined1 *)(param_1 + 0x1a) = 1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x1e) = 0xf;
  return;
}



// ==== 80127af8  zz_0127af8_ ====

void zz_0127af8_(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar5 = *(int *)(param_1 + 0x90);
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x38;
  if ((*(char *)(param_1 + 0x1d9) != '\0') && (*(char *)(param_1 + 0x144) == '\0')) {
    *(undefined1 *)(param_1 + 0x144) = 3;
  }
  if (*(char *)(param_1 + 0x144) < '\x01') {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  }
  fVar2 = FLOAT_80439c98;
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + FLOAT_80439c9c;
    if (*(float *)(&DAT_803308ac + iVar3) <= *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = *(float *)(&DAT_803308ac + iVar3);
      *(undefined1 *)(param_1 + 0x1a) = 3;
    }
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) - FLOAT_80439c9c;
        if (*(float *)(param_1 + 0x44) <= fVar2) {
          *(float *)(param_1 + 0x44) = fVar2;
          *(undefined1 *)(param_1 + 0x1a) = 1;
          *(undefined2 *)(param_1 + 0x1e) = 0xf;
          return;
        }
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
      if (cVar1 < '\0') {
        return;
      }
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
      if (0 < *(short *)(param_1 + 0x1e)) {
        return;
      }
      *(undefined1 *)(param_1 + 0x1a) = 2;
      dVar6 = (double)FLOAT_80439ca4;
      *(float *)(param_1 + 0x44) = FLOAT_80439ca0;
      *(short *)(param_1 + 0x1e) = (short)*(undefined4 *)(&DAT_803308c8 + iVar3);
      gnt4_PSQUATScale_bl(dVar6,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      return;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  iVar4 = iVar5 + (char)(&DAT_8033089e)[iVar3] * 0x30;
  local_24 = *(float *)(iVar4 + 0x8e0);
  local_20 = *(undefined4 *)(iVar4 + 0x8f0);
  local_1c = *(undefined4 *)(iVar4 + 0x900);
  dVar6 = gnt4_PSVECSquareDistance_bl(&local_24,(float *)(param_1 + 0x20));
  if ((double)FLOAT_80439c98 < dVar6) {
    dVar7 = 1.0 / SQRT(dVar6);
    dVar7 = DOUBLE_80439ca8 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80439cb0);
    dVar7 = DOUBLE_80439ca8 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80439cb0);
    dVar6 = (double)(float)(dVar6 * DOUBLE_80439ca8 * dVar7 *
                                    -(dVar6 * dVar7 * dVar7 - DOUBLE_80439cb0));
  }
  if ((double)*(float *)(param_1 + 0x44) <= dVar6) {
    if (*(char *)(param_1 + 0x144) < '\x01') {
      *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1e) + -1;
      if (*(short *)(param_1 + 0x1e) < 1) {
        *(short *)(param_1 + 0x1e) = (short)*(undefined4 *)(&DAT_803308c8 + iVar3);
        zz_006c440_((double)*(float *)(&DAT_803308cc + iVar3),param_1,&local_24);
      }
      else {
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                         (float *)(param_1 + 0x20));
      }
    }
  }
  else {
    zz_01281a8_(iVar5);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 80127dc4  FUN_80127dc4 ====

void FUN_80127dc4(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80127e00  FUN_80127e00 ====

void FUN_80127e00(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80127e20  FUN_80127e20 ====

/* WARNING: Removing unreachable block (ram,0x801280c0) */

void FUN_80127e20(int param_1)

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
  local_50 = FLOAT_80439c98;
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  local_5c = *(float *)(param_1 + 0x38);
  local_58 = *(float *)(param_1 + 0x3c);
  local_54 = *(float *)(param_1 + 0x40);
  if (local_50 == *(float *)(param_1 + 0x3c)) {
    local_40 = local_50;
    local_44 = FLOAT_80439cb8;
    local_3c = local_50;
    local_4c = FLOAT_80439cb8;
    local_48 = local_50;
    local_5c = local_50;
    local_58 = local_50;
    local_54 = FLOAT_80439cb8;
  }
  else {
    if (local_54 * local_54 + local_5c * local_5c + local_58 * local_58 <= local_50) {
      local_5c = local_50;
      local_58 = local_50;
      local_54 = FLOAT_80439ca4;
    }
    local_50 = local_5c;
    local_48 = local_54;
    local_4c = FLOAT_80439c98;
    if (FLOAT_80439c98 < local_54 * local_54 + local_5c * local_5c + FLOAT_80439c98 * FLOAT_80439c98
       ) {
      if (*(float *)(param_1 + 0x3c) < FLOAT_80439c98) {
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
    if (local_48 * local_48 + local_50 * local_50 + local_4c * local_4c <= FLOAT_80439c98) {
      local_4c = FLOAT_80439c98;
      local_50 = FLOAT_80439cb8;
      local_48 = FLOAT_80439c98;
    }
    gnt4_PSVECCrossProduct_bl(&local_50,&local_5c,&local_50);
    if (local_48 * local_48 + local_50 * local_50 + local_4c * local_4c <= FLOAT_80439c98) {
      local_50 = FLOAT_80439c98;
      local_4c = FLOAT_80439cb8;
      local_48 = FLOAT_80439c98;
    }
    gnt4_PSVECCrossProduct_bl(&local_50,&local_5c,&local_44);
    if (local_3c * local_3c + local_44 * local_44 + local_40 * local_40 <= FLOAT_80439c98) {
      local_40 = FLOAT_80439c98;
      local_44 = FLOAT_80439ca4;
      local_3c = FLOAT_80439c98;
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
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_80439cbc *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                             0x3ff0000000000000)),afStack_38,0x79);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)&DAT_80330890,&local_68);
  *(float *)(param_1 + 0x120) = local_68;
  *(undefined4 *)(param_1 + 0x130) = local_64;
  *(undefined4 *)(param_1 + 0x140) = local_60;
  gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                     (double)*(float *)(param_1 + 0x60),afStack_38);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  return;
}



// ==== 8012814c  FUN_8012814c ====

void FUN_8012814c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801281a8  zz_01281a8_ ====

void zz_01281a8_(int param_1)

{
  *(undefined1 *)(param_1 + 0x15c) = 0;
  zz_006de10_(param_1,2);
  return;
}



// ==== 801281d4  zz_01281d4_ ====

void zz_01281d4_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  int iVar2;
  float *pfVar3;
  
  if ((*(short *)(param_1 + 1000) == 0x202) || (*(short *)(param_1 + 1000) == 0x20b)) {
    puVar1 = zz_0088aa0_(param_1,3,8,0,1);
    if (puVar1 == (undefined1 *)0x0) {
      zz_0128dd0_(param_1);
    }
    else {
      *puVar1 = 1;
      puVar1[0x10] = 0x1b;
      puVar1[0x11] = param_2;
      *(code **)(puVar1 + 0xc) = FUN_8012836c;
      *(code **)(puVar1 + 0x10c) = FUN_80128d74;
      *(code **)(puVar1 + 0x100) = FUN_80128a48;
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
      pfVar3 = (float *)(param_1 +
                        (char)(&DAT_80330966)[(uint)(byte)puVar1[0x11] * 0x38] * 0x30 + 0x8d4);
      gnt4_PSMTXMultVec_bl
                (pfVar3,(float *)((uint)(byte)puVar1[0x11] * 0x38 + -0x7fccf698),
                 (float *)(puVar1 + 0x20));
      zz_0083d60_((int)puVar1,param_1,0);
      *(undefined2 *)(puVar1 + 0x70) = 0;
      iVar2 = FUN_800452a0((double)pfVar3[10],(double)pfVar3[2]);
      *(short *)(puVar1 + 0x72) = (short)iVar2;
      *(undefined2 *)(puVar1 + 0x74) = 0;
    }
  }
  return;
}



// ==== 8012836c  FUN_8012836c ====

void FUN_8012836c(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_803309d4)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8012840c  FUN_8012840c ====

void FUN_8012840c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  undefined *puVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  puVar3 = &DAT_80330964;
  iVar4 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar1 = (uint)*(byte *)(param_9 + 0x11) * 0x38;
  uVar5 = zz_0089100_(param_9,1,1);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar2 = zz_0006f78_(param_9);
  zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
              *(int *)(param_9 + 0xe0),(uint)*(ushort *)(&DAT_80330964 + iVar1),puVar3,in_r7,in_r8,
              in_r9,in_r10);
  *(undefined1 *)(param_9 + 0x144) = 0;
  *(undefined1 *)(param_9 + 0x145) = 0;
  *(undefined2 *)(param_9 + 0x146) = 0x4b0;
  iVar2 = zz_008ac80_(param_9,(int)(char)(&DAT_80330967)[iVar1]);
  if (iVar2 == 0) {
    zz_0128dd0_(iVar4);
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80330974 + iVar1),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80330974 + iVar1);
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_80330978 + iVar1);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8033097a + iVar1);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    zz_0128524_(param_9);
    *(undefined1 *)(param_9 + 0xaf) = 0;
  }
  return;
}



