// ==== 800c0b44  FUN_800c0b44 ====

void FUN_800c0b44(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if (((*(char *)(param_1 + 0x1d10) != '\0') &&
      (zz_006d144_(param_1,0xc0), *(short *)(param_1 + 1000) == 0x30b)) &&
     ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar2 = zz_006dbe0_(param_1,2,1,1);
    if (iVar2 == 0) goto LAB_800c0cc4;
    if (*(short *)(param_1 + 1000) == 0x300) {
      zz_00fe668_(param_1,0,0);
    }
    else if (*(short *)(param_1 + 1000) == 0x30b) {
      zz_00fe668_(param_1,1,1);
    }
  }
  fVar1 = FLOAT_80438618;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar1 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar1;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043861c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar2 = zz_00679d0_(param_1);
  if (((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) &&
     ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438624 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    return;
  }
LAB_800c0cc4:
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006a474_(param_1);
  }
  else {
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800c0d0c  zz_00c0d0c_ ====

bool zz_00c0d0c_(int param_1,undefined1 param_2)

{
  bool bVar2;
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x400) || (*(short *)(param_1 + 1000) == 0x40a)) {
    puVar1 = zz_0088aa0_(param_1,2,0,0,2);
    bVar2 = puVar1 != (undefined1 *)0x0;
    if (bVar2) {
      *puVar1 = 1;
      puVar1[0x11] = param_2;
      *(code **)(puVar1 + 0xc) = FUN_800c0e2c;
      *(code **)(puVar1 + 0x10c) = FUN_800c1058;
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
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}



// ==== 800c0d3c  zz_00c0d3c_ ====

undefined4 zz_00c0d3c_(void)

{
  return 0;
}



// ==== 800c0e2c  FUN_800c0e2c ====

void FUN_800c0e2c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80302e58)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800c0e80  FUN_800c0e80 ====

void FUN_800c0e80(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  fVar1 = FLOAT_80438628;
  iVar3 = *(char *)(param_9 + 0x11) * 0x18;
  *(undefined *)(param_9 + 0x89) = (&DAT_80302d98)[iVar3];
  uVar2 = *(undefined4 *)(&DAT_80302da0 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80302d9c + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80302da4 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80302da8 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80302dac + iVar3);
  *(undefined *)(param_9 + 0x13) = (&DAT_80302d99)[iVar3];
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80302d9a + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80302d9a + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043862c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  FUN_800c0fb4(param_9);
  return;
}



// ==== 800c0fb4  FUN_800c0fb4 ====

void FUN_800c0fb4(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80438630;
  fVar1 = FLOAT_80438628;
  if (*(char *)(*(int *)(param_1 + 0x90) + (int)*(char *)(param_1 + 0x13) + 0x144) != '\0') {
    *(float *)(param_1 + 0x58) = FLOAT_80438630;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x60) = fVar2;
    return;
  }
  if (*(float *)(param_1 + 0x58) < FLOAT_80438628) {
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + FLOAT_80438630;
    *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + fVar2;
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + fVar2;
    return;
  }
  *(float *)(param_1 + 0x58) = FLOAT_80438628;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x60) = fVar1;
  return;
}



// ==== 800c1038  FUN_800c1038 ====

void FUN_800c1038(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c1058  FUN_800c1058 ====

void FUN_800c1058(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined *param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + (char)param_9[0x13] + 0x144) == '\0') {
    if (*(char *)(iVar1 + 0xae) == '\0') {
      iVar2 = *(int *)(param_9 + 0xe0);
      if (*(char *)(iVar1 + 0x3ec) == '\x04') {
        uVar3 = 0x44;
      }
      else {
        uVar3 = 1;
      }
    }
    else {
      iVar2 = *(int *)(param_9 + 0xe4);
      uVar3 = 0x44;
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                (float *)(param_9 + 0x114),param_9,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar2,uVar3);
  }
  return;
}



// ==== 800c10f0  FUN_800c10f0 ====

bool FUN_800c10f0(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    puVar1 = zz_0088aa0_(param_1,2,0,0,4);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x13] = (char)iVar2;
      puVar1[0x11] = 0;
      *(code **)(puVar1 + 0xc) = FUN_800c1208;
      *(code **)(puVar1 + 0x10c) = FUN_800c1518;
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
    iVar2 = iVar2 + 1;
  } while (iVar2 < 2);
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800c1208  FUN_800c1208 ====

void FUN_800c1208(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80302ea0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800c125c  FUN_800c125c ====

void FUN_800c125c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  double dVar7;
  undefined8 uVar8;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar6 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  fVar2 = FLOAT_8043863c;
  fVar1 = FLOAT_80438638;
  dVar7 = (double)FLOAT_80438638;
  iVar4 = *(char *)(param_9 + 0x13) * 0x1c;
  uVar3 = *(undefined4 *)(&DAT_80302e74 + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80302e70 + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar3;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80302e78 + iVar4);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80302e7c + iVar4);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80302e80 + iVar4);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80302e6c + iVar4);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x144) = fVar1;
  *(float *)(param_9 + 0x148) = fVar2;
  *(float *)(param_9 + 0x14c) = fVar2;
  iVar6 = zz_0006f98_(iVar6);
  uVar8 = zz_0007030_(dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80302e68 + iVar4),iVar6 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe4),
                      (int)*(short *)(&DAT_80302e6a + iVar4),iVar6 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe8),
                      (int)*(short *)(&DAT_80302e68 + iVar4),iVar6 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar5 = iVar6 + 0xc28;
  iVar4 = (int)*(short *)(&DAT_80302e6a + iVar4);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xec),iVar4,iVar5,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe8)
              ,extraout_r4,iVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
  uVar8 = zz_0007cac_((double)FLOAT_80438640,*(int *)(param_9 + 0xe8));
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,iVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438640,*(int *)(param_9 + 0xec));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  FUN_800c13d4(param_9);
  return;
}



// ==== 800c13d4  FUN_800c13d4 ====

void FUN_800c13d4(int param_1)

{
  float fVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  if ((*(uint *)(iVar2 + 0x5e0) & 0x20000000) != 0) {
    return;
  }
  fVar1 = (float)(DOUBLE_80438648 *
                  (double)(float)((double)*(float *)(param_1 + 0x144) -
                                 (double)*(float *)(param_1 + 0x58)) +
                 (double)*(float *)(param_1 + 0x58));
  *(float *)(param_1 + 0x60) = fVar1;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  fVar1 = FLOAT_8043863c;
  if (*(char *)(iVar2 + *(char *)(param_1 + 0x13) + 0x144) != '\0') {
    *(float *)(param_1 + 0x58) = FLOAT_8043863c;
    *(float *)(param_1 + 0x5c) = fVar1;
    *(float *)(param_1 + 0x60) = fVar1;
  }
  if (*(float *)(param_1 + 0x58) < FLOAT_80438638) {
    *(float *)(param_1 + 0x144) = FLOAT_80438650;
  }
  if (DOUBLE_80438658 <= (double)*(float *)(param_1 + 0x58)) {
    *(float *)(param_1 + 0x144) = FLOAT_80438638;
  }
  fVar1 = FLOAT_80438664;
  if (*(char *)(iVar2 + 0x6e9) < '\x01') {
    *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) * FLOAT_80438668;
  }
  else {
    *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) + FLOAT_80438660;
    if (fVar1 < *(float *)(param_1 + 0x14c)) {
      *(float *)(param_1 + 0x14c) = fVar1;
    }
  }
  if (*(float *)(param_1 + 0x14c) < FLOAT_8043866c) {
    *(float *)(param_1 + 0x14c) = FLOAT_8043866c;
  }
  fVar1 = FLOAT_80438670;
  *(float *)(param_1 + 0x148) = *(float *)(param_1 + 0x148) + *(float *)(param_1 + 0x14c);
  if (*(float *)(param_1 + 0x148) <= fVar1) {
    return;
  }
  *(float *)(param_1 + 0x148) = *(float *)(param_1 + 0x148) - FLOAT_80438674;
  return;
}



// ==== 800c14f8  FUN_800c14f8 ====

void FUN_800c14f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c1518  FUN_800c1518 ====

void FUN_800c1518(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined8 uVar6;
  float afStack_48 [14];
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + *(char *)(param_9 + 0x13) + 0x144) == '\0') {
    if (*(char *)(iVar1 + 0xae) == '\0') {
      iVar4 = *(int *)(param_9 + 0xe0);
      iVar3 = *(int *)(param_9 + 0xe4);
      if (*(char *)(iVar1 + 0x3ec) == '\x04') {
        uVar5 = 0x44;
      }
      else {
        uVar5 = 1;
      }
    }
    else {
      iVar4 = *(int *)(param_9 + 0xe8);
      uVar5 = 0x44;
      iVar3 = *(int *)(param_9 + 0xec);
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar4,uVar5);
    gnt4_PSMTXRotRad_bl((double)*(float *)(param_9 + 0x148),afStack_48,0x7a);
    pfVar2 = afStack_48;
    uVar6 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
    zz_00076d0_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_48,
                (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar3,uVar5);
  }
  return;
}



// ==== 800c1600  zz_00c1600_ ====

bool zz_00c1600_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,0,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = 0;
    *(code **)(puVar1 + 0xc) = FUN_800c16fc;
    *(code **)(puVar1 + 0x10c) = FUN_800c1b10;
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
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800c16fc  FUN_800c16fc ====

void FUN_800c16fc(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80302ec8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800c1750  FUN_800c1750 ====

void FUN_800c1750(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  uint uVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
  uVar5 = (uint)*(byte *)(param_9 + 0x18);
  *(byte *)(param_9 + 0x18) = *(byte *)(param_9 + 0x18) + 1;
  *(undefined1 *)(param_9 + 0x19) = 0;
  *(undefined1 *)(param_9 + 0x1a) = 0;
  iVar6 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  fVar1 = FLOAT_80438678;
  iVar3 = *(char *)(param_9 + 0x13) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_80302eb8 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80302eb4 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80302ebc + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80302ec0 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80302ec4 + iVar3);
  *(undefined *)(param_9 + 0x89) = (&DAT_80302eb2)[iVar3];
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar6 = zz_0006f98_(iVar6);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80302eb0 + iVar3),iVar6 + 0xc28,uVar5,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar6 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80302eb0 + iVar3);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,uVar5,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,uVar5,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043867c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  iVar6 = zz_008ac80_(param_9,0);
  if (iVar6 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(ushort *)(param_9 + 0x272) = *(ushort *)(param_9 + 0x272) | 1;
    *(byte *)(param_9 + 0x2ac) = *(byte *)(param_9 + 0x2ac) | 4;
    *(undefined2 *)(param_9 + 0x1c4) = 100;
    *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
    *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
    zz_00c18e8_(param_9);
  }
  return;
}



// ==== 800c18e8  zz_00c18e8_ ====

void zz_00c18e8_(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  
  iVar6 = *(int *)(param_1 + 0x90);
  if (*(char *)(iVar6 + 0x144) != '\0') {
    *(undefined1 *)(param_1 + 0x19) = 1;
    fVar3 = FLOAT_80438690;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined2 *)(param_1 + 0x272) = 0xffff;
    *(float *)(param_1 + 0xb4) = fVar3;
    goto LAB_800c1a6c;
  }
  *(undefined2 *)(param_1 + 0x272) = *(undefined2 *)(iVar6 + 0x272);
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 1;
  fVar5 = FLOAT_8043868c;
  fVar4 = FLOAT_80438680;
  fVar3 = FLOAT_80438678;
  if (*(char *)(param_1 + 0x19) == '\0') goto LAB_800c1a6c;
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x01') {
LAB_800c196c:
    fVar5 = FLOAT_80438688;
    fVar4 = FLOAT_80438678;
    fVar3 = FLOAT_80438684 * *(float *)(iVar6 + 0x1dc8);
    *(float *)(param_1 + 0xb4) =
         *(float *)(param_1 + 0xb4) * (FLOAT_80438678 - fVar3) + *(float *)(param_1 + 0xb8) * fVar3;
    if (fVar5 * *(float *)(param_1 + 0xb8) < *(float *)(param_1 + 0xb4)) {
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      *(float *)(param_1 + 0xb8) = fVar4;
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
      *(float *)(param_1 + 0xb8) = fVar4;
      goto LAB_800c196c;
    }
  }
  else if ((cVar1 < '\x03') &&
          (fVar4 = FLOAT_80438684 * *(float *)(iVar6 + 0x1dc8),
          *(float *)(param_1 + 0xb4) =
               *(float *)(param_1 + 0xb4) * (FLOAT_80438678 - fVar4) +
               *(float *)(param_1 + 0xb8) * fVar4,
          *(float *)(param_1 + 0xb4) < fVar5 * *(float *)(param_1 + 0xb8))) {
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(float *)(param_1 + 0xb8) = fVar3;
    *(float *)(param_1 + 0xb4) = fVar3;
  }
  *(float *)(param_1 + 0x68) =
       *(float *)(param_1 + 0xb4) * *(float *)(&DAT_80302eb8 + *(char *)(param_1 + 0x13) * 0x18);
LAB_800c1a6c:
  uVar2 = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  *(undefined4 *)(param_1 + 0x5c) = uVar2;
  *(undefined4 *)(param_1 + 0x58) = uVar2;
  if (*(short *)(param_1 + 0x1c6) < 1) {
    zz_006dbe0_(iVar6,2,1,1);
    *(undefined1 *)(iVar6 + 0x144) = 1;
    FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
    *(undefined2 *)(param_1 + 0x1c4) = 100;
    *(undefined2 *)(param_1 + 0x1c6) = *(undefined2 *)(param_1 + 0x1c4);
    *(undefined2 *)(param_1 + 0x1c8) = *(undefined2 *)(param_1 + 0x1c4);
  }
  return;
}



// ==== 800c1af0  FUN_800c1af0 ====

void FUN_800c1af0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c1b10  FUN_800c1b10 ====

void FUN_800c1b10(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + 0x144) == '\0') {
    if (*(char *)(iVar1 + 0xae) == '\0') {
      iVar2 = *(int *)(param_9 + 0xe0);
      if (*(char *)(iVar1 + 0x3ec) == '\x04') {
        uVar3 = 0x44;
      }
      else {
        uVar3 = 1;
      }
    }
    else {
      iVar2 = *(int *)(param_9 + 0xe4);
      uVar3 = 0x44;
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar2,uVar3);
  }
  return;
}



// ==== 800c1b9c  zz_00c1b9c_ ====

bool zz_00c1b9c_(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    puVar1 = zz_0088aa0_(param_1,2,0,0,2);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x13] = (char)iVar2;
      puVar1[0x11] = 0;
      *(code **)(puVar1 + 0xc) = FUN_800c1cb4;
      *(code **)(puVar1 + 0x10c) = FUN_800c1ed8;
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
    iVar2 = iVar2 + 1;
  } while (iVar2 < 2);
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800c1cb4  FUN_800c1cb4 ====

void FUN_800c1cb4(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80302f08)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800c1d08  FUN_800c1d08 ====

void FUN_800c1d08(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  fVar1 = FLOAT_80438698;
  iVar3 = *(char *)(param_9 + 0x13) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_80302ee0 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80302edc + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80302ee4 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80302ee8 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80302eec + iVar3);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80302eda + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80302ed8 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80302ed8 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043869c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00c1e34_(param_9);
  return;
}



// ==== 800c1e34  zz_00c1e34_ ====

void zz_00c1e34_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_804386a0;
  fVar1 = FLOAT_80438698;
  if (*(char *)(*(int *)(param_1 + 0x90) + (int)*(char *)(param_1 + 0x13) + 0x149) != '\0') {
    *(float *)(param_1 + 0x58) = FLOAT_804386a0;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x60) = fVar2;
    return;
  }
  if (*(float *)(param_1 + 0x58) < FLOAT_80438698) {
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + FLOAT_804386a0;
    *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + fVar2;
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + fVar2;
    return;
  }
  *(float *)(param_1 + 0x58) = FLOAT_80438698;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x60) = fVar1;
  return;
}



// ==== 800c1eb8  FUN_800c1eb8 ====

void FUN_800c1eb8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c1ed8  FUN_800c1ed8 ====

void FUN_800c1ed8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined *param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + (char)param_9[0x13] + 0x149) == '\0') {
    if (*(char *)(iVar1 + 0xae) == '\0') {
      iVar2 = *(int *)(param_9 + 0xe0);
      if (*(char *)(iVar1 + 0x3ec) == '\x04') {
        uVar3 = 0x44;
      }
      else {
        uVar3 = 1;
      }
    }
    else {
      iVar2 = *(int *)(param_9 + 0xe4);
      uVar3 = 0x44;
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                (float *)(param_9 + 0x114),param_9,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar2,uVar3);
  }
  return;
}



// ==== 800c1f70  zz_00c1f70_ ====

void zz_00c1f70_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,4);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0xd;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 4;
    *(code **)(puVar1 + 0xc) = FUN_800c2078;
    *(code **)(puVar1 + 0x10c) = FUN_800c2298;
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



// ==== 800c2078  FUN_800c2078 ====

void FUN_800c2078(int param_1)

{
  (*(code *)(&PTR_FUN_80303068)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800c20b4  FUN_800c20b4 ====

void FUN_800c20b4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  int iVar6;
  double dVar7;
  
  iVar6 = *(int *)(param_9 + 0x8c);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar5 = *(char *)(param_9 + 0x11) * 0x10;
  *(short *)(param_9 + 0x1c) = (short)*(char *)(param_9 + 0x13);
  *(undefined2 *)(param_9 + 0x1e) = 0x20;
  *(float *)(param_9 + 0xb4) = *(float *)(iVar6 + 0xb4) * *(float *)(iVar6 + 0x7fc);
  *(undefined1 *)(param_9 + 0x144) = 0;
  uVar1 = zz_00055fc_();
  *(short *)(param_9 + 0x72) = (short)(uVar1 << 8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar6 + *(int *)(&DAT_80302f18 + iVar5) * 0x30 + 0x8d4),
             (float *)(iVar5 + -0x7fcfd0e4),(float *)(param_9 + 0x20));
  *(short *)(param_9 + 0x14c) = *(short *)(param_9 + 0x1c) * 0x50;
  *(short *)(param_9 + 0x14e) = *(short *)(param_9 + 0x1e) * 0x48;
  uVar1 = (int)*(short *)(param_9 + 0x14c) + *(short *)(param_9 + 0x14e) + 0x1f;
  piVar2 = zz_0006dc8_((((int)uVar1 >> 5) + (uint)((int)uVar1 < 0 && (uVar1 & 0x1f) != 0)) * 0x20);
  *(int **)(param_9 + 0xdc) = piVar2;
  if (piVar2 == (int *)0x0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    uVar4 = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    uVar3 = 1;
    *(undefined4 *)(param_9 + 0x54) = uVar4;
    *(code **)(param_9 + 0x100) = FUN_800c2424;
    dVar7 = (double)zz_0089100_(param_9,1,1);
    iVar5 = 0;
    do {
      dVar7 = (double)FUN_800c25a0(dVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   param_9,(byte)iVar5,uVar3,uVar4,in_r7,in_r8,in_r9,in_r10);
      iVar5 = iVar5 + 1;
    } while (iVar5 < 3);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 800c2200  FUN_800c2200 ====

void FUN_800c2200(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  
  bVar1 = zz_00c2868_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  if (bVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 800c2250  FUN_800c2250 ====

void FUN_800c2250(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c2298  FUN_800c2298 ====

/* WARNING: Removing unreachable block (ram,0x800c2388) */

void FUN_800c2298(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar9 = 0;
  iVar8 = param_9;
  for (iVar7 = 0; iVar7 < *(short *)(param_9 + 0x1c); iVar7 = iVar7 + 1) {
    if (((uint)*(byte *)(param_9 + 0x144) & 1 << iVar7) != 0) {
      if (((byte *)(param_9 + 0x144))[iVar7 + 0xc] == 3) {
        iVar2 = *(int *)(*(int *)(iVar8 + 0xe0) + 0xc);
        if (iVar2 == 0) {
          iVar2 = 0;
        }
        else {
          iVar2 = *(int *)(iVar2 + 0x10);
        }
        iVar6 = 0;
        for (iVar5 = 0; iVar5 < *(short *)(param_9 + 0x1e); iVar5 = iVar5 + 1) {
          pfVar4 = (float *)(*(int *)(param_9 + 0x54) + *(short *)(param_9 + 0x14c) + iVar6);
          if (iVar2 == 0) {
            param_11 = &DAT_804386b0;
            param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,
                                       param_8,&DAT_804386a8,0x495,&DAT_804386b0,param_12,param_13,
                                       param_14,param_15,param_16);
          }
          if (pfVar4 == (float *)0x0) {
            param_11 = &DAT_804386b8;
            gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             &DAT_804386a8,0x496,&DAT_804386b8,param_12,param_13,param_14,param_15,
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
                                   iVar2,uVar3,param_11,param_12,param_13,param_14,param_15,param_16
                                  );
            }
          }
          if (iVar2 == 0) {
            iVar2 = 0;
          }
          else {
            iVar2 = *(int *)(iVar2 + 8);
          }
          iVar6 = iVar6 + 0x48;
        }
      }
      else {
        zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar8 + 0xe0),(float *)(*(int *)(param_9 + 0x54) + iVar9),param_11,
                    param_12,param_13,param_14,param_15,param_16);
      }
      param_1 = zz_00097b4_(*(int *)(iVar8 + 0xe0),0x44);
    }
    iVar9 = iVar9 + 0x50;
    iVar8 = iVar8 + 4;
  }
  return;
}



// ==== 800c2424  FUN_800c2424 ====

void FUN_800c2424(int param_1)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  float local_38;
  float local_34;
  float local_30;
  
  iVar4 = 0;
  iVar5 = 0;
  while( true ) {
    if (*(short *)(param_1 + 0x1c) <= iVar4) break;
    if (((uint)*(byte *)(param_1 + 0x144) & 1 << iVar4) != 0) {
      if (((byte *)(param_1 + 0x144))[iVar4 + 0xc] == 3) {
        iVar3 = 0;
        for (iVar2 = 0; iVar2 < *(short *)(param_1 + 0x1e); iVar2 = iVar2 + 1) {
          pfVar1 = (float *)(*(int *)(param_1 + 0x54) + *(short *)(param_1 + 0x14c) + iVar3);
          gnt4_PSMTXIdentity_bl(pfVar1);
          zz_00457d4_('y',pfVar1,pfVar1,*(short *)((int)pfVar1 + 0x46));
          zz_00457d4_('x',pfVar1,pfVar1,*(short *)(pfVar1 + 0x11));
          gnt4_PSMTXMultVec_bl(pfVar1,(float *)&DAT_802b0cc0,&local_38);
          gnt4_PSQUATScale_bl((double)pfVar1[0xc],&local_38,&local_38);
          gnt4_PSVECAdd_bl(&local_38,(float *)(param_1 + 0x20),&local_38);
          gnt4_PSMTXTrans_bl((double)local_38,(double)local_34,(double)local_30,pfVar1);
          dVar6 = (double)pfVar1[0xf];
          zz_0045654_(dVar6,dVar6,dVar6,pfVar1,pfVar1);
          iVar3 = iVar3 + 0x48;
        }
      }
      else {
        pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
        gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                           (double)*(float *)(param_1 + 0x28),pfVar1);
        zz_00457d4_('y',pfVar1,pfVar1,*(short *)(param_1 + 0x72));
        zz_00456a0_(pfVar1,pfVar1,pfVar1 + 0x10);
      }
    }
    iVar5 = iVar5 + 0x50;
    iVar4 = iVar4 + 1;
  }
  return;
}



// ==== 800c25a0  FUN_800c25a0 ====

/* WARNING: Removing unreachable block (ram,0x800c284c) */
/* WARNING: Removing unreachable block (ram,0x800c2844) */
/* WARNING: Removing unreachable block (ram,0x800c283c) */
/* WARNING: Removing unreachable block (ram,0x800c2834) */
/* WARNING: Removing unreachable block (ram,0x800c282c) */
/* WARNING: Removing unreachable block (ram,0x800c2824) */
/* WARNING: Removing unreachable block (ram,0x800c281c) */
/* WARNING: Removing unreachable block (ram,0x800c2814) */
/* WARNING: Removing unreachable block (ram,0x800c25e8) */
/* WARNING: Removing unreachable block (ram,0x800c25e0) */
/* WARNING: Removing unreachable block (ram,0x800c25d8) */
/* WARNING: Removing unreachable block (ram,0x800c25d0) */
/* WARNING: Removing unreachable block (ram,0x800c25c8) */
/* WARNING: Removing unreachable block (ram,0x800c25c0) */
/* WARNING: Removing unreachable block (ram,0x800c25b8) */
/* WARNING: Removing unreachable block (ram,0x800c25b0) */

void FUN_800c25a0(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,byte param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  byte *pbVar7;
  undefined8 uVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  
  pbVar7 = (byte *)(param_9 + 0x144);
  for (iVar6 = 0; iVar6 < *(short *)(param_9 + 0x1c); iVar6 = iVar6 + 1) {
    if (((uint)*pbVar7 & 1 << iVar6) == 0) {
      iVar1 = (int)(char)param_10;
      pbVar7[iVar6 + 0xc] = param_10;
      *pbVar7 = *pbVar7 | (byte)(1 << iVar6);
      if (pbVar7[iVar6 + 0xc] == 3) {
        dVar13 = (double)FLOAT_804386bc;
        iVar5 = 0;
        dVar15 = (double)FLOAT_804386c4;
        dVar16 = (double)FLOAT_804386c0;
        dVar9 = (double)FLOAT_804386cc;
        dVar10 = (double)FLOAT_804386c8;
        dVar11 = (double)FLOAT_804386d4;
        dVar12 = (double)FLOAT_804386d0;
        dVar14 = DOUBLE_804386d8;
        for (iVar3 = 0; iVar3 < *(short *)(param_9 + 0x1e); iVar3 = iVar3 + 1) {
          iVar4 = *(int *)(param_9 + 0x54) + *(short *)(param_9 + 0x14c) + iVar5;
          *(float *)(iVar4 + 0x30) = (float)(dVar13 * (double)*(float *)(param_9 + 0xb4));
          uVar2 = zz_00055fc_();
          *(float *)(iVar4 + 0x34) =
               *(float *)(param_9 + 0xb4) *
               (float)(dVar16 + (double)(float)((double)(float)((double)CONCAT44(0x43300000,
                                                                                 uVar2 & 0xff) -
                                                               dVar14) / dVar15));
          uVar2 = zz_00055fc_();
          *(float *)(iVar4 + 0x38) =
               *(float *)(param_9 + 0xb4) *
               (float)(dVar10 + (double)(float)((double)(float)((double)CONCAT44(0x43300000,
                                                                                 uVar2 & 0xff) -
                                                               dVar14) / dVar9));
          uVar2 = zz_00055fc_();
          param_1 = (double)(float)((double)(float)((double)CONCAT44(0x43300000,uVar2 & 0xff) -
                                                   dVar14) * dVar11 + dVar12);
          *(float *)(iVar4 + 0x3c) = (float)((double)*(float *)(param_9 + 0xb4) * param_1);
          *(float *)(iVar4 + 0x40) = (float)dVar12;
          uVar2 = zz_00055fc_();
          *(short *)(iVar4 + 0x44) = (short)(uVar2 << 8);
          uVar2 = zz_00055fc_();
          iVar5 = iVar5 + 0x48;
          *(short *)(iVar4 + 0x46) = (short)(uVar2 << 8);
        }
        param_13 = 2;
        *(short *)(pbVar7 + iVar6 * 2 + 0x10) = *(short *)(param_9 + 0x1e);
        zz_000744c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                    *(int *)(param_9 + iVar6 * 4 + 0xe0),
                    (float *)(int)*(short *)(&DAT_80303038 + iVar1 * 0xc),
                    (int)*(short *)(param_9 + 0x1e),2,param_14,param_15,param_16);
        param_1 = (double)zz_00f03c0_(param_9,0xd);
      }
      else {
        iVar3 = *(int *)(param_9 + 0x54);
        (pbVar7 + iVar6 * 2 + 0x10)[0] = 0;
        (pbVar7 + iVar6 * 2 + 0x10)[1] = 0;
        iVar3 = iVar3 + iVar6 * 0x50;
        *(undefined2 *)(pbVar7 + iVar6 * 2 + 0x18) = *(undefined2 *)(&DAT_8030303a + iVar1 * 0xc);
        zz_0018f88_((int *)(iVar3 + 0x30),(int)(&PTR_DAT_8030303c)[iVar1 * 3],
                    (float *)(iVar3 + 0x40));
        gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(iVar3 + 0x40),
                            (float *)(iVar3 + 0x40));
        uVar8 = zz_0019338_((int *)(iVar3 + 0x38),(int)(&PTR_DAT_80303040)[iVar1 * 3],
                            (float *)(iVar3 + 0x4c));
        param_1 = (double)zz_000726c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                      DAT_803bb374,*(int *)(param_9 + iVar6 * 4 + 0xe0),
                                      (float *)(int)*(short *)(&DAT_80303038 + iVar1 * 0xc),2,
                                      param_13,param_14,param_15,param_16);
      }
      iVar6 = (int)*(short *)(param_9 + 0x1c);
    }
  }
  return;
}



// ==== 800c2868  zz_00c2868_ ====

/* WARNING: Removing unreachable block (ram,0x800c2a5c) */
/* WARNING: Removing unreachable block (ram,0x800c2878) */

byte zz_00c2868_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  short sVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  byte *pbVar10;
  int iVar11;
  byte *pbVar12;
  int iVar13;
  double dVar14;
  
  pbVar10 = (byte *)(param_9 + 0x144);
  iVar13 = 0;
  iVar11 = param_9;
  pbVar12 = pbVar10;
  for (iVar9 = 0; iVar9 < *(short *)(param_9 + 0x1c); iVar9 = iVar9 + 1) {
    if (((uint)*pbVar10 & 1 << iVar9) != 0) {
      iVar6 = iVar9 + 0xc;
      bVar4 = (byte)(1 << iVar9);
      if (pbVar10[iVar6] == 3) {
        iVar6 = *(int *)(*(int *)(iVar11 + 0xe0) + 0xc);
        if (iVar6 == 0) {
          iVar6 = 0;
        }
        else {
          iVar6 = *(int *)(iVar6 + 0x10);
        }
        dVar14 = (double)FLOAT_804386e0;
        iVar8 = 0;
        for (iVar5 = 0; iVar5 < *(short *)(param_9 + 0x1e); iVar5 = iVar5 + 1) {
          iVar7 = *(int *)(param_9 + 0x54) + *(short *)(param_9 + 0x14c) + iVar8;
          if ((dVar14 < (double)*(float *)(iVar7 + 0x40)) &&
             (fVar1 = *(float *)(iVar7 + 0x30) + *(float *)(iVar7 + 0x38),
             *(float *)(iVar7 + 0x30) = fVar1, *(float *)(iVar7 + 0x34) <= fVar1)) {
            fVar2 = *(float *)(iVar7 + 0x40);
            fVar1 = (float)((double)fVar2 - (double)FLOAT_804386e4);
            *(float *)(iVar7 + 0x40) = fVar1;
            if ((double)fVar1 <= dVar14) {
              sVar3 = *(short *)(pbVar12 + 0x10);
              *(short *)(pbVar12 + 0x10) = sVar3 + -1;
              *(float *)(iVar7 + 0x40) = (float)dVar14;
              gnt4_HSD_JObjSetFlagsAll
                        ((double)fVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6
                         ,0x10,(undefined *)(int)sVar3,param_12,param_13,param_14,param_15,param_16)
              ;
            }
          }
          param_1 = (double)zz_00091e4_((double)*(float *)(iVar7 + 0x40),iVar6);
          if (iVar6 == 0) {
            iVar6 = 0;
          }
          else {
            iVar6 = *(int *)(iVar6 + 8);
          }
          iVar8 = iVar8 + 0x48;
        }
        if (*(short *)(pbVar12 + 0x10) == 0) {
          *pbVar10 = *pbVar10 & ~bVar4;
        }
      }
      else {
        sVar3 = *(short *)(pbVar12 + 0x10);
        iVar5 = *(int *)(param_9 + 0x54);
        *(short *)(pbVar12 + 0x10) = sVar3 + 1;
        iVar5 = iVar5 + iVar13;
        if (*(short *)(pbVar12 + 0x18) <= (short)(sVar3 + 1)) {
          if (pbVar10[iVar6] == 2) {
            FUN_800c25a0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,3,
                         iVar6,param_12,param_13,param_14,param_15,param_16);
          }
          *pbVar10 = *pbVar10 & ~bVar4;
        }
        zz_0018fd8_((int *)(iVar5 + 0x30),(int)*(short *)(pbVar12 + 0x10),(float *)(iVar5 + 0x40));
        gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(iVar5 + 0x40),
                            (float *)(iVar5 + 0x40));
        zz_0019370_((int *)(iVar5 + 0x38),(int)*(short *)(pbVar12 + 0x10),(float *)(iVar5 + 0x4c));
        param_1 = (double)zz_0007cac_((double)*(float *)(iVar5 + 0x4c),*(int *)(iVar11 + 0xe0));
      }
    }
    iVar13 = iVar13 + 0x50;
    pbVar12 = pbVar12 + 2;
    iVar11 = iVar11 + 4;
  }
  return *pbVar10;
}



// ==== 800c2a78  zz_00c2a78_ ====

bool zz_00c2a78_(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    puVar1 = zz_0088aa0_(param_1,2,0,0,2);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x13] = (char)iVar2;
      puVar1[0x11] = 0;
      puVar1[0x83] = 0x18;
      *(code **)(puVar1 + 0xc) = FUN_800c2b98;
      *(code **)(puVar1 + 0x10c) = FUN_800c3b60;
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
    iVar2 = iVar2 + 1;
  } while (iVar2 < 2);
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800c2b98  FUN_800c2b98 ====

void FUN_800c2b98(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803030d8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800c2bec  FUN_800c2bec ====

void FUN_800c2bec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(undefined1 *)(param_9 + 0x152) = 0;
  *(undefined2 *)(param_9 + 0x166) = 0;
  iVar6 = *(int *)(param_9 + 0x90);
  iVar4 = *(char *)(param_9 + 0x13) * 0x18;
  *(code **)(param_9 + 0x100) = FUN_800480f4;
  iVar5 = iVar4;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  *(undefined *)(param_9 + 0x89) = (&DAT_8030307a)[iVar4];
  uVar7 = gnt4_PSMTXMultVec_bl
                    ((float *)(iVar6 + (char)(&DAT_8030307a)[iVar4] * 0x30 + 0x8d4),
                     (float *)(&DAT_8030307c + iVar4),(float *)(param_9 + 0x20));
  fVar1 = FLOAT_804386e8;
  *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(param_9 + 0x20);
  *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(param_9 + 0x24);
  *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(param_9 + 0x28);
  uVar2 = *(undefined4 *)(&DAT_80303080 + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8030307c + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80303084 + iVar4);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80303088 + iVar4);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8030308c + iVar4);
  *(undefined2 *)(param_9 + 0x150) = 0;
  *(float *)(param_9 + 0x154) = fVar1;
  iVar6 = zz_0006f98_(iVar6);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80303078 + iVar4),iVar6 + 0xc28,iVar5,in_r8,in_r9,in_r10)
  ;
  iVar3 = iVar6 + 0xc28;
  iVar4 = (int)*(short *)(&DAT_80303078 + iVar4);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe4),iVar4,iVar3,iVar5,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar4,iVar3,iVar5,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804386ec,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00c3484_(param_9);
  return;
}



// ==== 800c2d4c  zz_00c3484_ ====

void zz_00c3484_(int param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_1 + 0x90);
  *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(iVar1 + 0xb4);
  switch(*(undefined1 *)(iVar1 + 0x144)) {
  case 0:
    if (*(char *)(param_1 + 0x152) != '\0') {
      *(undefined1 *)(param_1 + 0x152) = 0;
      *(code **)(param_1 + 0x100) = FUN_800480f4;
    }
    break;
  case 1:
    if (*(char *)(param_1 + 0x152) == '\0') {
      *(undefined1 *)(param_1 + 0x19) = 0;
      *(undefined1 *)(param_1 + 0x152) = 1;
      *(char *)(iVar1 + 0x145) = *(char *)(iVar1 + 0x145) + -1;
      if (*(char *)(iVar1 + 0x145) < '\x01') {
        *(undefined1 *)(iVar1 + 0x144) = 99;
      }
      uVar2 = zz_00055fc_();
      *(byte *)(param_1 + 0x164) = (byte)uVar2 & 0xf;
    }
    break;
  case 2:
    *(undefined1 *)(param_1 + 0x152) = 2;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(char *)(iVar1 + 0x145) = *(char *)(iVar1 + 0x145) + -1;
    if (*(char *)(iVar1 + 0x145) < '\x01') {
      *(undefined1 *)(iVar1 + 0x144) = 99;
    }
    break;
  case 3:
    if (*(char *)(param_1 + 0x152) == '\x02') {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      *(char *)(iVar1 + 0x145) = *(char *)(iVar1 + 0x145) + -1;
      if (*(char *)(iVar1 + 0x145) < '\x01') {
        *(undefined1 *)(iVar1 + 0x144) = 99;
      }
    }
    break;
  case 7:
    *(undefined1 *)(param_1 + 0x152) = 3;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(char *)(iVar1 + 0x145) = *(char *)(iVar1 + 0x145) + -1;
    if (*(char *)(iVar1 + 0x145) < '\x01') {
      *(undefined1 *)(iVar1 + 0x144) = 99;
    }
    break;
  case 8:
    if (*(char *)(param_1 + 0x152) == '\x03') {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      *(char *)(iVar1 + 0x145) = *(char *)(iVar1 + 0x145) + -1;
      if (*(char *)(iVar1 + 0x145) < '\x01') {
        *(undefined1 *)(iVar1 + 0x144) = 99;
      }
    }
  }
  (*(code *)(&PTR_FUN_803030e8)[*(char *)(param_1 + 0x152)])(param_1);
  *(float *)(param_1 + 0x58) =
       *(float *)(param_1 + 0x154) * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0xb4);
  *(float *)(param_1 + 0x5c) =
       *(float *)(param_1 + 0x154) * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0xb4);
  *(float *)(param_1 + 0x60) =
       *(float *)(param_1 + 0x154) * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0xb4);
  return;
}



// ==== 800c2f48  FUN_800c2f48 ====

/* WARNING: Removing unreachable block (ram,0x800c30d4) */
/* WARNING: Removing unreachable block (ram,0x800c2f58) */

void FUN_800c2f48(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  float local_38;
  float local_34;
  float local_30;
  
  *(undefined1 *)(param_1 + 0x152) = 0;
  iVar7 = *(int *)(param_1 + 0x90);
  *(short *)(param_1 + 0x150) = *(short *)(param_1 + 0x150) + 0x200;
  iVar6 = *(char *)(param_1 + 0x13) * 0x18;
  dVar8 = zz_0045204_(*(short *)(param_1 + 0x150));
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar7 + (char)(&DAT_8030307a)[iVar6] * 0x30 + 0x8d4),
             (float *)(&DAT_8030307c + iVar6),&local_38);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(iVar7 + 0x70);
  *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(iVar7 + 0x74);
  *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + *(short *)(&DAT_80303088 + iVar6);
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(&DAT_8030308a + iVar6);
  if ((*(uint *)(iVar7 + 0x5e0) & 0x20000000) == 0) {
    if (*(char *)(param_1 + 0x13) == '\0') {
      *(short *)(param_1 + 0x74) =
           *(short *)(param_1 + 0x74) +
           (*(short *)(&DAT_8030308c + iVar6) - *(short *)(param_1 + 0x150));
    }
    else {
      *(short *)(param_1 + 0x74) =
           *(short *)(&DAT_8030308c + iVar6) +
           *(short *)(param_1 + 0x150) + *(short *)(param_1 + 0x74);
    }
  }
  fVar5 = FLOAT_804386fc;
  fVar4 = FLOAT_804386f8;
  fVar3 = FLOAT_804386f4;
  fVar2 = FLOAT_804386f0;
  fVar1 = FLOAT_804386e8;
  *(float *)(param_1 + 0x144) =
       (FLOAT_804386f0 * *(float *)(param_1 + 0x144) + local_38) / FLOAT_804386f4;
  *(float *)(param_1 + 0x148) = (fVar2 * *(float *)(param_1 + 0x148) + local_34) / fVar3;
  *(float *)(param_1 + 0x14c) = (fVar2 * *(float *)(param_1 + 0x14c) + local_30) / fVar3;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x144);
  *(float *)(param_1 + 0x24) =
       (float)(dVar8 * (double)(fVar4 * *(float *)(param_1 + 0xb4)) +
              (double)*(float *)(param_1 + 0x148));
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x14c);
  *(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x154) - fVar5;
  if (*(float *)(param_1 + 0x154) < fVar1) {
    *(float *)(param_1 + 0x154) = fVar1;
  }
  return;
}



// ==== 800c30f8  FUN_800c30f8 ====

void FUN_800c30f8(int param_1)

{
  (*(code *)(&PTR_LAB_80433b20)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 800c3178  FUN_800c3178 ====

/* WARNING: Removing unreachable block (ram,0x800c3428) */
/* WARNING: Removing unreachable block (ram,0x800c3188) */

void FUN_800c3178(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  double dVar10;
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
  
  iVar8 = *(int *)(param_1 + 0x90);
  *(short *)(param_1 + 0x150) = *(short *)(param_1 + 0x150) + 0x200;
  iVar4 = (*(char *)(param_1 + 0x13) + 2) * 0x18;
  dVar9 = zz_0045204_(*(short *)(param_1 + 0x150));
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar8 + (char)(&DAT_8030307a)[iVar4] * 0x30 + 0x8d4),
             (float *)(&DAT_8030307c + iVar4),&local_34);
  fVar3 = FLOAT_804386f8;
  fVar2 = FLOAT_804386f4;
  fVar1 = FLOAT_804386f0;
  *(float *)(param_1 + 0x144) =
       (FLOAT_804386f0 * *(float *)(param_1 + 0x144) + local_34) / FLOAT_804386f4;
  *(float *)(param_1 + 0x148) = (fVar1 * *(float *)(param_1 + 0x148) + local_30) / fVar2;
  *(float *)(param_1 + 0x14c) = (fVar1 * *(float *)(param_1 + 0x14c) + local_2c) / fVar2;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x144);
  *(float *)(param_1 + 0x24) =
       (float)(dVar9 * (double)(fVar3 * *(float *)(param_1 + 0xb4)) +
              (double)*(float *)(param_1 + 0x148));
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x14c);
  iVar7 = *(int *)(param_1 + 200);
  if (iVar7 == 0) {
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(iVar8 + 0x70);
    *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(iVar8 + 0x74);
    *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + *(short *)(&DAT_80303088 + iVar4);
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(&DAT_8030308a + iVar4);
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(&DAT_8030308c + iVar4);
  }
  else {
    local_40 = *(float *)(iVar7 + 100);
    local_3c = *(float *)(iVar7 + 0x68);
    local_38 = *(float *)(iVar7 + 0x6c);
    local_4c = local_40 - *(float *)(param_1 + 0x20);
    local_48 = local_3c - *(float *)(param_1 + 0x24);
    local_44 = local_38 - *(float *)(param_1 + 0x28);
    local_58 = *(float *)(param_1 + 0x11c);
    local_54 = *(undefined4 *)(param_1 + 300);
    local_50 = *(undefined4 *)(param_1 + 0x13c);
    zz_0046588_((double)FLOAT_80438704,&local_58,&local_4c,&local_4c);
    dVar10 = -(double)local_48;
    local_48 = FLOAT_804386e8;
    dVar9 = gnt4_PSVECMag_bl(&local_4c);
    iVar4 = FUN_800452a0(dVar10,dVar9);
    *(short *)(param_1 + 0x70) = (short)iVar4;
    iVar4 = FUN_800452a0((double)local_4c,(double)local_44);
    *(short *)(param_1 + 0x72) = (short)iVar4;
  }
  fVar3 = FLOAT_80438714;
  fVar2 = FLOAT_80438710;
  fVar1 = FLOAT_8043870c;
  if (*(float *)(param_1 + 0x158) <= FLOAT_804386e8) {
    if (*(short *)(param_1 + 0x160) < 0) {
      *(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x154) + *(float *)(param_1 + 0x158);
      if (*(float *)(param_1 + 0x154) < fVar3) {
        *(float *)(param_1 + 0x154) = fVar3;
        *(float *)(param_1 + 0x158) = FLOAT_80438700;
      }
    }
    else {
      *(short *)(param_1 + 0x160) = *(short *)(param_1 + 0x160) + -1;
      *(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x154) - fVar2;
    }
  }
  else {
    *(float *)(param_1 + 0x154) = FLOAT_80438708;
    *(float *)(param_1 + 0x158) = fVar1;
    *(undefined2 *)(param_1 + 0x160) = 3;
    uVar5 = zz_00055fc_();
    *(byte *)(param_1 + 0x164) = (byte)uVar5 & 0xf;
    FUN_8014c810(param_1,0);
    FUN_8014cbb0(param_1,*(char *)(param_1 + 0x164),(char)*(undefined2 *)(param_1 + 0x166),0);
    sVar6 = *(short *)(param_1 + 0x166) + 1;
    *(short *)(param_1 + 0x166) = sVar6;
    if (99 < sVar6) {
      *(undefined2 *)(param_1 + 0x166) = 0;
    }
  }
  return;
}



// ==== 800c344c  FUN_800c344c ====

void FUN_800c344c(int param_1)

{
  (*(code *)(&PTR_FUN_80433b28)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 800c3484  FUN_800c3484 ====

void FUN_800c3484(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = FLOAT_80438718;
  fVar2 = FLOAT_80438700;
  fVar1 = FLOAT_804386fc;
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(float *)(param_1 + 0x158) = fVar1;
  fVar1 = FLOAT_8043871c;
  *(float *)(param_1 + 0x15c) = fVar2;
  fVar2 = FLOAT_80438720;
  *(float *)(param_1 + 0x16c) = fVar3;
  *(float *)(param_1 + 0x170) = (fVar1 + *(float *)(param_1 + 0x154)) / fVar2;
  *(undefined2 *)(param_1 + 0x160) = 3;
  *(undefined1 *)(param_1 + 0x168) = 0;
  FUN_800c34f0(param_1);
  return;
}



// ==== 800c34f0  FUN_800c34f0 ====

/* WARNING: Removing unreachable block (ram,0x800c3820) */
/* WARNING: Removing unreachable block (ram,0x800c3500) */

void FUN_800c34f0(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  short sVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  undefined4 local_48;
  undefined4 local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  
  iVar8 = *(int *)(param_1 + 0x90);
  *(short *)(param_1 + 0x150) = *(short *)(param_1 + 0x150) + 0x200;
  iVar5 = (*(char *)(param_1 + 0x13) + 2) * 0x18;
  dVar9 = zz_0045204_(*(short *)(param_1 + 0x150));
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar8 + (char)(&DAT_8030307a)[iVar5] * 0x30 + 0x8d4),
             (float *)(&DAT_8030307c + iVar5),&local_34);
  fVar4 = FLOAT_804386f8;
  fVar3 = FLOAT_804386f4;
  fVar2 = FLOAT_804386f0;
  *(float *)(param_1 + 0x144) =
       (FLOAT_804386f0 * *(float *)(param_1 + 0x144) + local_34) / FLOAT_804386f4;
  *(float *)(param_1 + 0x148) = (fVar2 * *(float *)(param_1 + 0x148) + local_30) / fVar3;
  *(float *)(param_1 + 0x14c) = (fVar2 * *(float *)(param_1 + 0x14c) + local_2c) / fVar3;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x144);
  *(float *)(param_1 + 0x24) =
       (float)(dVar9 * (double)(fVar4 * *(float *)(param_1 + 0xb4)) +
              (double)*(float *)(param_1 + 0x148));
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x14c);
  iVar7 = *(int *)(param_1 + 200);
  if (iVar7 == 0) {
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(iVar8 + 0x70);
    *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(iVar8 + 0x74);
    *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + *(short *)(&DAT_80303088 + iVar5);
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(&DAT_8030308a + iVar5);
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(&DAT_8030308c + iVar5);
  }
  else {
    local_40 = *(float *)(iVar7 + 100);
    local_3c = *(float *)(iVar7 + 0x68);
    local_38 = *(float *)(iVar7 + 0x6c);
    local_58 = local_40 - *(float *)(param_1 + 0x20);
    local_54 = local_3c - *(float *)(param_1 + 0x24);
    local_50 = local_38 - *(float *)(param_1 + 0x28);
    local_4c = *(float *)(param_1 + 0x11c);
    local_48 = *(undefined4 *)(param_1 + 300);
    local_44 = *(undefined4 *)(param_1 + 0x13c);
    zz_0046588_((double)FLOAT_80438704,&local_4c,&local_58,&local_58);
    dVar10 = -(double)local_54;
    local_54 = FLOAT_804386e8;
    dVar9 = gnt4_PSVECMag_bl(&local_58);
    iVar5 = FUN_800452a0(dVar10,dVar9);
    *(short *)(param_1 + 0x70) = (short)iVar5;
    iVar5 = FUN_800452a0((double)local_58,(double)local_50);
    *(short *)(param_1 + 0x72) = (short)iVar5;
  }
  fVar3 = FLOAT_8043872c;
  fVar2 = FLOAT_80438724;
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x01') {
    *(float *)(param_1 + 0x154) = FLOAT_80438728;
    sVar6 = *(short *)(param_1 + 0x160) + 1;
    *(short *)(param_1 + 0x160) = sVar6;
    if (2 < sVar6) {
      if (*(char *)(param_1 + 0x168) < '\x03') {
        FUN_8014c810(param_1,0);
        if (*(char *)(param_1 + 0x168) == '\x02') {
          FUN_8014cbb0(param_1,*(char *)(param_1 + 0x164),(char)*(undefined2 *)(param_1 + 0x166),1);
        }
        else {
          FUN_8014cbb0(param_1,*(char *)(param_1 + 0x164),(char)*(undefined2 *)(param_1 + 0x166),0);
        }
        *(char *)(param_1 + 0x168) = *(char *)(param_1 + 0x168) + '\x01';
        sVar6 = *(short *)(param_1 + 0x166) + 1;
        *(short *)(param_1 + 0x166) = sVar6;
        if (99 < sVar6) {
          *(undefined2 *)(param_1 + 0x166) = 0;
        }
      }
      *(undefined2 *)(param_1 + 0x160) = 0;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  }
  else if (cVar1 < '\x01') {
    if ((-1 < cVar1) &&
       (*(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x154) - *(float *)(param_1 + 0x170),
       *(float *)(param_1 + 0x154) < fVar2)) {
      *(float *)(param_1 + 0x154) = fVar2;
    }
  }
  else if (cVar1 < '\x03') {
    *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x16c);
    fVar2 = FLOAT_80438728;
    *(float *)(param_1 + 0x16c) = *(float *)(param_1 + 0x16c) + fVar3;
    if (fVar2 < *(float *)(param_1 + 0x16c)) {
      *(float *)(param_1 + 0x16c) = fVar2;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + -1;
  }
  return;
}



// ==== 800c3844  FUN_800c3844 ====

void FUN_800c3844(int param_1)

{
  (*(code *)(&PTR_FUN_80433b30)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 800c387c  FUN_800c387c ====

void FUN_800c387c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = FLOAT_80438718;
  fVar2 = FLOAT_80438700;
  fVar1 = FLOAT_804386fc;
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(code **)(param_1 + 0x100) = FUN_800480f4;
  *(float *)(param_1 + 0x158) = fVar1;
  *(float *)(param_1 + 0x15c) = fVar2;
  *(float *)(param_1 + 0x16c) = fVar3;
  zz_00c38cc_(param_1);
  return;
}



// ==== 800c38cc  zz_00c38cc_ ====

void zz_00c38cc_(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  float local_18;
  float local_14;
  float local_10;
  
  iVar6 = *(int *)(param_1 + 0x90);
  *(undefined2 *)(param_1 + 0x70) = *(undefined2 *)(iVar6 + 0x70);
  iVar5 = *(char *)(param_1 + 0x13) * 0x18;
  *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(*(int *)(param_1 + 0x90) + 0x72);
  *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + *(short *)(&DAT_80303088 + iVar5);
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(&DAT_8030308a + iVar5);
  gnt4_PSMTXMultVec_bl
            ((float *)(*(int *)(param_1 + 0x90) + 0x904),
             (float *)(*(char *)(param_1 + 0x13) * 0xc + -0x7fcfcee4),&local_18);
  fVar3 = FLOAT_8043872c;
  cVar1 = *(char *)(param_1 + 0x1a);
  dVar7 = (double)FLOAT_804386e8;
  if (cVar1 == '\x02') {
    *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x16c);
    fVar2 = FLOAT_80438728;
    *(float *)(param_1 + 0x16c) = *(float *)(param_1 + 0x16c) + fVar3;
    if (*(float *)(param_1 + 0x16c) <= fVar2) {
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + -1;
    }
    else {
      *(float *)(param_1 + 0x16c) = fVar2;
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x24);
      *(undefined2 *)(param_1 + 0x162) = 0;
      *(undefined2 *)(param_1 + 0x150) = 0;
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if ((*(uint *)(iVar6 + 0x5e0) & 0x20000000) == 0) {
        if (*(char *)(param_1 + 0x13) == '\0') {
          *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + -0x200;
        }
        else {
          *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x200;
        }
      }
    }
    else if (-1 < cVar1) {
      *(float *)(param_1 + 0x154) = FLOAT_80438728;
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    }
  }
  else if (cVar1 < '\x04') {
    *(short *)(param_1 + 0x150) = *(short *)(param_1 + 0x150) + 0x200;
    dVar7 = zz_0045204_(*(short *)(param_1 + 0x150));
    *(short *)(param_1 + 0x162) = *(short *)(param_1 + 0x162) + 0x10;
    if (0x500 < *(short *)(param_1 + 0x162)) {
      *(undefined2 *)(param_1 + 0x162) = 0x500;
    }
    if ((*(uint *)(iVar6 + 0x5e0) & 0x20000000) == 0) {
      if (*(char *)(param_1 + 0x13) == '\0') {
        *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) - *(short *)(param_1 + 0x162);
      }
      else {
        *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x162);
      }
    }
  }
  fVar4 = FLOAT_80438738;
  fVar2 = FLOAT_80438734;
  fVar3 = FLOAT_80438730;
  *(float *)(param_1 + 0x144) =
       FLOAT_80438730 * *(float *)(param_1 + 0x144) + FLOAT_80438734 * local_18;
  *(float *)(param_1 + 0x148) = fVar3 * *(float *)(param_1 + 0x148) + fVar2 * local_14;
  *(float *)(param_1 + 0x14c) = fVar3 * *(float *)(param_1 + 0x14c) + fVar2 * local_10;
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x144);
  *(float *)(param_1 + 0x24) =
       (float)(dVar7 * (double)(fVar4 * *(float *)(param_1 + 0xb4)) +
              (double)*(float *)(param_1 + 0x148));
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x14c);
  return;
}



// ==== 800c3b40  FUN_800c3b40 ====

void FUN_800c3b40(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c3b60  FUN_800c3b60 ====

void FUN_800c3b60(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar1 = *(int *)(param_9 + 0xe0);
    if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
      uVar2 = 0x44;
    }
    else {
      uVar2 = 1;
    }
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



// ==== 800c3be0  zz_00c3be0_ ====

void zz_00c3be0_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 2;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_800c3cdc;
    *(code **)(puVar1 + 0x10c) = FUN_800c4468;
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



// ==== 800c3cdc  FUN_800c3cdc ====

void FUN_800c3cdc(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_803051e4)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800c3d2c  FUN_800c3d2c ====

void FUN_800c3d2c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  bool bVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  int iVar8;
  float *pfVar9;
  double dVar10;
  undefined8 uVar11;
  double dVar12;
  
  pfVar9 = (float *)(param_9 + 0x144);
  iVar8 = *(int *)(param_9 + 0x90);
  iVar7 = *(int *)(param_9 + 0x8c);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar6 = (uint)*(byte *)(param_9 + 0x11) * 0x44;
  *(undefined2 *)(param_9 + 0x1c) = 300;
  if (((char)(&DAT_8030313a)[iVar6] < '\0') ||
     (iVar4 = zz_008ac80_(param_9,(int)(char)(&DAT_8030313a)[iVar6]), iVar4 == 0)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    if ((char)(&DAT_80303139)[iVar6] < '\0') {
      gnt4_PSMTXCopy_bl((float *)(iVar7 + 0x114),pfVar9);
    }
    else {
      gnt4_PSMTXCopy_bl((float *)(iVar7 + (char)(&DAT_80303139)[iVar6] * 0x30 + 0x8d4),pfVar9);
    }
    gnt4_PSMTXMultVec_bl(pfVar9,(float *)(iVar6 + -0x7fcfcec4),(float *)(param_9 + 0x174));
    *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x174);
    *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x178);
    *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x17c);
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80303164 + iVar6);
    *(undefined4 *)(param_9 + 0x4c) = *(undefined4 *)(&DAT_80303168 + iVar6);
    *(undefined *)(param_9 + 0x1cb) = (&DAT_80303156)[iVar6];
    iVar4 = zz_006ec84_(iVar8);
    if (iVar4 == 0) {
      *(undefined4 *)(param_9 + 200) = 0;
    }
    bVar2 = false;
    uVar5 = (uint)(char)(&DAT_80303154)[iVar6];
    if ((uVar5 & 0x80) != 0) {
      if (*(int *)(param_9 + 200) == 0) {
        if ((uVar5 & 0x40) != 0) {
          bVar2 = true;
        }
      }
      else {
        bVar2 = true;
      }
    }
    if (bVar2) {
      zz_0083e64_(param_9,pfVar9,(float *)(iVar6 + -0x7fcfceb8));
    }
    else {
      *(float *)(param_9 + 0x38) = pfVar9[uVar5 & 0x7f];
      *(float *)(param_9 + 0x3c) = pfVar9[((byte)(&DAT_80303154)[iVar6] & 0x7f) + 4];
      *(float *)(param_9 + 0x40) = pfVar9[((byte)(&DAT_80303154)[iVar6] & 0x7f) + 8];
      gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
      if ((char)(&DAT_80303155)[iVar6] < '\0') {
        gnt4_PSQUATScale_bl((double)FLOAT_80438740,(float *)(param_9 + 0x38),
                            (float *)(param_9 + 0x38));
      }
    }
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),(float *)(param_9 + 0x20));
    dVar10 = gnt4_PSVECSquareDistance_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x174));
    if ((double)FLOAT_80438744 < dVar10) {
      dVar12 = 1.0 / SQRT(dVar10);
      dVar12 = DOUBLE_80438748 * dVar12 * -(dVar10 * dVar12 * dVar12 - DOUBLE_80438750);
      dVar12 = DOUBLE_80438748 * dVar12 * -(dVar10 * dVar12 * dVar12 - DOUBLE_80438750);
      dVar10 = (double)(float)(dVar10 * DOUBLE_80438748 * dVar12 *
                                        -(dVar10 * dVar12 * dVar12 - DOUBLE_80438750));
      param_3 = DOUBLE_80438750;
      param_4 = DOUBLE_80438748;
    }
    *(float *)(param_9 + 0x180) = (float)dVar10;
    gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0x44),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    dVar10 = (double)*(float *)(&DAT_80303174 + iVar6);
    *(float *)(param_9 + 0x188) =
         (float)(dVar10 / (double)FLOAT_80438758) * *(float *)(iVar7 + 0xb4);
    *(undefined4 *)(param_9 + 0xb4) = *(undefined4 *)(param_9 + 0x188);
    *(undefined4 *)(param_9 + 0xc0) = *(undefined4 *)(param_9 + 0x188);
    *(float *)(param_9 + 0xc4) = *(float *)(param_9 + 0xb4) / *(float *)(param_9 + 0x188);
    *(undefined4 *)(param_9 + 0xb8) = *(undefined4 *)(param_9 + 0xb4);
    *(undefined4 *)(param_9 + 0x5c) = *(undefined4 *)(param_9 + 0xb4);
    *(undefined4 *)(param_9 + 0x58) = *(undefined4 *)(param_9 + 0xb4);
    fVar3 = FLOAT_8043875c;
    fVar1 = *(float *)(&DAT_80303170 + iVar6);
    if (*(float *)(param_9 + 0x180) < fVar1) {
      fVar1 = *(float *)(param_9 + 0x180);
    }
    *(float *)(param_9 + 0x184) = fVar1;
    *(float *)(param_9 + 0x60) = fVar1 / fVar3;
    if (-1 < (char)(&DAT_8030313b)[iVar6]) {
      zz_00c44a8_(param_9);
      zz_00aedc0_(iVar8,(float *)(param_9 + 0x114),(int)(char)(&DAT_8030313b)[iVar6],
                  *(undefined1 *)(param_9 + 0x88));
    }
    *(code **)(param_9 + 0x100) = zz_00c44a8_;
    uVar11 = zz_0089100_(param_9,1,1);
    if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
      *(undefined4 *)(param_9 + 200) = 0;
    }
    iVar7 = DAT_803bb374;
    if (*(short *)(&DAT_8030317a + iVar6) != 0) {
      iVar7 = zz_0006f78_(iVar8);
    }
    zz_000726c_(uVar11,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,
                *(int *)(param_9 + 0xe0),(float *)(uint)(byte)(&DAT_80303138)[iVar6],
                (int)*(char *)(param_9 + 0x88),in_r7,in_r8,in_r9,in_r10);
    *(undefined1 *)(param_9 + 0x82) = 1;
    zz_00f036c_(param_9,(int)*(short *)(&DAT_80303178 + iVar6));
  }
  return;
}



// ==== 800c4088  FUN_800c4088 ====

void FUN_800c4088(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  
  iVar5 = (uint)*(byte *)(param_1 + 0x11) * 0x44;
  zz_00c4540_(param_1);
  fVar1 = *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x4c);
  *(float *)(param_1 + 0x44) = fVar1;
  if (*(float *)(&DAT_8030316c + iVar5) < fVar1) {
    *(float *)(param_1 + 0x44) = *(float *)(&DAT_8030316c + iVar5);
  }
  FUN_80083874((double)FLOAT_80438744,param_1);
  iVar3 = zz_0083714_(param_1);
  if ((iVar3 == 0) && (((int)*(char *)(param_1 + 0x1d9) & 0xa2U) == 0)) {
    iVar3 = zz_0084170_(param_1);
    if (iVar3 == 0) {
      iVar3 = zz_0083244_((float *)(param_1 + 0x20));
      if ((iVar3 != 0) ||
         (sVar4 = *(short *)(param_1 + 0x1c) + -1, *(short *)(param_1 + 0x1c) = sVar4, sVar4 < 1)) {
        *(undefined1 *)(param_1 + 0x18) = 2;
        *(undefined1 *)(param_1 + 0x19) = 2;
        zz_008aff0_(param_1);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x19) = 1;
      zz_008aff0_(param_1);
      dVar6 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x174));
      if ((double)FLOAT_80438744 < dVar6) {
        dVar7 = 1.0 / SQRT(dVar6);
        dVar7 = DOUBLE_80438748 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80438750);
        dVar7 = DOUBLE_80438748 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80438750);
        dVar6 = (double)(float)(dVar6 * DOUBLE_80438748 * dVar7 *
                                        -(dVar6 * dVar7 * dVar7 - DOUBLE_80438750));
      }
      *(float *)(param_1 + 0x180) = (float)dVar6;
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x19) = 1;
    zz_008aff0_(param_1);
  }
  zz_00834b0_(param_1,(float *)(param_1 + 0xb4));
  zz_0083524_(param_1);
  *(undefined4 *)(param_1 + 0xc0) = *(undefined4 *)(param_1 + 0xb4);
  *(float *)(param_1 + 0xc4) = *(float *)(param_1 + 0xb4) / *(float *)(param_1 + 0x188);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
  fVar2 = FLOAT_8043875c;
  fVar1 = *(float *)(&DAT_80303170 + iVar5);
  if (*(float *)(param_1 + 0x180) < fVar1) {
    fVar1 = *(float *)(param_1 + 0x180);
  }
  *(float *)(param_1 + 0x184) = fVar1;
  *(float *)(param_1 + 0x60) = fVar1 / fVar2;
  return;
}



// ==== 800c426c  FUN_800c426c ====

void FUN_800c426c(int param_1)

{
  (*(code *)(&PTR_zz_00c42a8__803051f4)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 800c42a8  zz_00c42a8_ ====

void zz_00c42a8_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800c42bc  FUN_800c42bc ====

void FUN_800c42bc(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = FLOAT_80438744;
  fVar2 = *(float *)(param_1 + 0x184) - *(float *)(param_1 + 0x44);
  fVar1 = fVar2 / FLOAT_8043875c;
  *(float *)(param_1 + 0x184) = fVar2;
  *(float *)(param_1 + 0x60) = fVar1;
  if (fVar1 <= fVar3) {
    zz_00c42a8_(param_1);
  }
  return;
}



// ==== 800c4308  FUN_800c4308 ====

void FUN_800c4308(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x44;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x174));
  if ((double)FLOAT_80438744 < dVar4) {
    dVar5 = 1.0 / SQRT(dVar4);
    dVar5 = DOUBLE_80438748 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80438750);
    dVar5 = DOUBLE_80438748 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80438750);
    dVar4 = (double)(float)(dVar4 * DOUBLE_80438748 * dVar5 *
                                    -(dVar4 * dVar5 * dVar5 - DOUBLE_80438750));
  }
  *(float *)(param_1 + 0x180) = (float)dVar4;
  fVar1 = *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x4c);
  *(float *)(param_1 + 0x44) = fVar1;
  if (*(float *)(&DAT_8030316c + iVar3) < fVar1) {
    *(float *)(param_1 + 0x44) = *(float *)(&DAT_8030316c + iVar3);
  }
  fVar2 = FLOAT_80438764;
  fVar1 = *(float *)(param_1 + 0xb4) * FLOAT_80438760;
  *(float *)(param_1 + 0xb4) = fVar1;
  if (fVar1 <= fVar2) {
    zz_00c42a8_(param_1);
  }
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
  fVar2 = FLOAT_8043875c;
  fVar1 = *(float *)(&DAT_80303170 + iVar3);
  if (*(float *)(param_1 + 0x180) < fVar1) {
    fVar1 = *(float *)(param_1 + 0x180);
  }
  *(float *)(param_1 + 0x184) = fVar1;
  *(float *)(param_1 + 0x60) = fVar1 / fVar2;
  return;
}



// ==== 800c4448  FUN_800c4448 ====

void FUN_800c4448(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c4468  FUN_800c4468 ====

void FUN_800c4468(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800c44a8  zz_00c44a8_ ====

void zz_00c44a8_(int param_1)

{
  bool bVar1;
  float afStack_18 [5];
  
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x174),afStack_18);
  bVar1 = zz_0045ef4_((float *)(param_1 + 0x114),5,afStack_18,&DAT_802b0cb4);
  if (bVar1) {
    zz_0045ef4_((float *)(param_1 + 0x114),4,afStack_18,&DAT_802b0ca8);
  }
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  return;
}



// ==== 800c4540  zz_00c4540_ ====

void zz_00c4540_(int param_1)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  float afStack_34 [3];
  float afStack_28 [5];
  
  uVar4 = *(uint *)(param_1 + 200);
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x44;
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  uVar1 = 0;
  if ((int)(-uVar4 | uVar4) < 0) {
    *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(uVar4 + 100);
    *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(uVar4 + 0x68);
    *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(uVar4 + 0x6c);
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x144),(float *)(iVar3 + -0x7fcfceb8),afStack_28);
    gnt4_PSVECSubtract_bl(afStack_28,(float *)(param_1 + 0x20),afStack_34);
    dVar5 = gnt4_PSVECSquareMag_bl(afStack_34);
    if (dVar5 <= (double)(*(float *)(&DAT_80303160 + iVar3) * *(float *)(&DAT_80303160 + iVar3))) {
      *(undefined4 *)(param_1 + 200) = 0;
      uVar1 = 0;
    }
    else {
      dVar5 = gnt4_PSQUATDotProduct_bl((float *)(param_1 + 0x38),afStack_34);
      if (dVar5 < (double)FLOAT_80438744) {
        *(undefined4 *)(param_1 + 200) = 0;
        uVar1 = 0;
      }
      else {
        cVar2 = *(char *)(param_1 + 0x1cb) + -1;
        *(char *)(param_1 + 0x1cb) = cVar2;
        uVar1 = countLeadingZeros((int)cVar2);
        uVar1 = (1 << (uVar1 & 0x1f) | 1U >> 0x20 - (uVar1 & 0x1f)) & 1;
        if (uVar1 != 0) {
          *(undefined *)(param_1 + 0x1cb) = (&DAT_80303157)[iVar3];
          zz_006c440_((double)*(float *)(&DAT_80303158 + iVar3),param_1,afStack_28);
          zz_00833a4_(param_1);
        }
      }
    }
  }
  if (uVar1 == 0) {
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  }
  dVar5 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x174));
  if ((double)FLOAT_80438744 < dVar5) {
    dVar6 = 1.0 / SQRT(dVar5);
    dVar6 = DOUBLE_80438748 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80438750);
    dVar6 = DOUBLE_80438748 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80438750);
    dVar5 = (double)(float)(dVar5 * DOUBLE_80438748 * dVar6 *
                                    -(dVar5 * dVar6 * dVar6 - DOUBLE_80438750));
  }
  *(float *)(param_1 + 0x180) = (float)dVar5;
  return;
}



// ==== 800c4704  zz_00c4704_ ====

bool zz_00c4704_(int param_1,undefined1 param_2,undefined1 *param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,2);
  if (puVar1 == (undefined1 *)0x0) {
    *param_3 = 0;
    zz_006de10_(param_1,2);
  }
  else {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = param_2;
    puVar1[0x10] = 0x19;
    *(code **)(puVar1 + 0xc) = FUN_800c4838;
    *(code **)(puVar1 + 0x10c) = FUN_800c5a60;
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
    *(undefined1 **)(puVar1 + 0x184) = param_3;
  }
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800c4838  FUN_800c4838 ====

void FUN_800c4838(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80305240)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800c48d0  FUN_800c48d0 ====

void FUN_800c48d0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  undefined8 uVar10;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar9 = *(int *)(param_9 + 0x90);
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x20;
  *(undefined *)(param_9 + 0x89) = (&DAT_80305201)[iVar5];
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  *(undefined *)(param_9 + 0x98) = (&DAT_8030521e)[iVar5];
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar8 = iVar5;
  zz_0089100_(param_9,0,1);
  uVar2 = DAT_802b0cb8;
  puVar7 = &DAT_802b0cb4;
  *(undefined4 *)(param_9 + 0x9c) = DAT_802b0cb4;
  uVar3 = DAT_802b0cbc;
  *(undefined4 *)(param_9 + 0xa0) = uVar2;
  *(undefined4 *)(param_9 + 0xa4) = uVar3;
  *(undefined4 *)(param_9 + 0x20) =
       *(undefined4 *)(iVar9 + *(char *)(param_9 + 0x89) * 0x30 + 0x8e0);
  *(undefined4 *)(param_9 + 0x24) =
       *(undefined4 *)(iVar9 + *(char *)(param_9 + 0x89) * 0x30 + 0x8f0);
  iVar6 = iVar9 + *(char *)(param_9 + 0x89) * 0x30;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(iVar6 + 0x900);
  zz_0083d60_(param_9,iVar9,0);
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  uVar10 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80305210 + iVar5),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80305210 + iVar5);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_80305202 + iVar5);
  *(short *)(param_9 + 0x1c4) = (short)*(undefined4 *)(&DAT_80305204 + iVar5);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x180) = *(undefined4 *)(&DAT_80305214 + iVar5);
  iVar4 = zz_0006f98_(iVar9);
  uVar10 = zz_0006fb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),
                       (int)(char)(&DAT_8030521c)[iVar5],iVar6,puVar7,iVar8,in_r9,in_r10);
  cVar1 = (&DAT_8030521d)[iVar5];
  *(char *)(param_9 + 0x12) = cVar1;
  if (-1 < cVar1) {
    zz_0006fb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),(int)(char)(&DAT_8030521d)[iVar5],
                iVar6,puVar7,iVar8,in_r9,in_r10);
  }
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar5 = zz_008ac80_(param_9,(int)(char)(&DAT_80305200)[iVar5]);
  if (iVar5 == 0) {
    **(undefined1 **)(param_9 + 0x184) = 0;
    zz_006de10_(iVar9,2);
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined4 *)(param_9 + 0x144) =
         *(undefined4 *)(iVar9 + *(char *)(param_9 + 0x89) * 0x30 + 0x8e0);
    *(undefined4 *)(param_9 + 0x148) =
         *(undefined4 *)(iVar9 + *(char *)(param_9 + 0x89) * 0x30 + 0x8f0);
    *(undefined4 *)(param_9 + 0x14c) =
         *(undefined4 *)(iVar9 + *(char *)(param_9 + 0x89) * 0x30 + 0x900);
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),(float *)(param_9 + 0x150))
    ;
    zz_00a2bf8_(iVar9,param_9,(undefined4 *)(param_9 + 0x144),(float *)(param_9 + 0x150),1,0);
    zz_00f036c_(param_9,0xdb);
  }
  return;
}



// ==== 800c4b48  FUN_800c4b48 ====

void FUN_800c4b48(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    FUN_800c5010(param_1);
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      zz_00c4ba4_(param_1);
    }
  }
  else if (cVar1 < '\x03') {
    zz_00c5730_(param_1);
  }
  return;
}



// ==== 800c4ba4  zz_00c4ba4_ ====

void zz_00c4ba4_(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float afStack_24 [5];
  
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x20;
  iVar4 = *(int *)(param_1 + 0x90);
  if (*(byte *)(param_1 + 0x1d9) == 0) {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      cVar1 = (&DAT_8030521f)[iVar3];
      if (cVar1 == '\x01') {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x114);
          *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x124);
          *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x134);
        }
      }
      else if (cVar1 < '\x03') {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x11c);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 300);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x13c);
      }
      if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x180)) {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(&DAT_80305218 + iVar3);
      }
      else {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x180);
      }
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      FUN_80083874((double)*(float *)(&DAT_8030520c + iVar3),param_1);
      FUN_80083ad4((double)*(float *)(&DAT_80305208 + iVar3),param_1,
                   (char)*(undefined2 *)(&DAT_80305202 + iVar3));
      zz_00833ec_(param_1);
      zz_0083610_(param_1,(float *)(param_1 + 0x180));
      iVar3 = zz_0083714_(param_1);
      if (iVar3 == 0) {
        iVar3 = zz_0084170_(param_1);
        if (iVar3 == 0) {
          *(undefined4 *)(param_1 + 0x144) =
               *(undefined4 *)(iVar4 + *(char *)(param_1 + 0x89) * 0x30 + 0x8e0);
          *(undefined4 *)(param_1 + 0x148) =
               *(undefined4 *)(iVar4 + *(char *)(param_1 + 0x89) * 0x30 + 0x8f0);
          *(undefined4 *)(param_1 + 0x14c) =
               *(undefined4 *)(iVar4 + *(char *)(param_1 + 0x89) * 0x30 + 0x900);
          *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
          *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
          *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
          gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x144),afStack_24);
          dVar5 = gnt4_PSVECMag_bl(afStack_24);
          if ((double)FLOAT_80438780 <= dVar5) {
            gnt4_PSQUATScale_bl((double)(float)((double)FLOAT_80438780 / dVar5),afStack_24,
                                afStack_24);
            gnt4_PSVECAdd_bl((float *)(param_1 + 0x144),afStack_24,(float *)(param_1 + 0x20));
            *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
            *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
            *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
            zz_00c590c_(param_1);
          }
        }
        else {
          zz_00c590c_(param_1);
        }
      }
      else {
        zz_00c590c_(param_1);
      }
    }
    else {
      zz_00c590c_(param_1);
    }
  }
  else if ((*(byte *)(param_1 + 0x1d9) & 0x10) == 0) {
    zz_00c590c_(param_1);
  }
  else {
    *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x290);
    iVar3 = *(int *)(param_1 + 0x15c);
    if (*(char *)(iVar3 + 0x83) == '\0') {
      iVar4 = *(int *)(param_1 + 0x90);
      if ((((int)*(char *)(iVar4 + 0x71e) & 1 << (int)*(char *)(iVar3 + 0x3e4)) == 0) ||
         (((int)*(char *)(iVar3 + 0x71e) & 1 << (int)*(char *)(iVar4 + 0x3e4)) == 0)) {
        *(undefined1 *)(iVar3 + 0x719) = 1;
        *(undefined1 *)(param_1 + 0x19) = 1;
        *(undefined2 *)(param_1 + 0x1c) = 600;
        zz_008aff0_(param_1);
        *(byte *)(iVar4 + 0x71e) =
             *(byte *)(iVar4 + 0x71e) | (byte)(1 << (int)*(char *)(iVar3 + 0x3e4));
        *(byte *)(iVar3 + 0x71e) =
             *(byte *)(iVar3 + 0x71e) | (byte)(1 << (int)*(char *)(iVar4 + 0x3e4));
        *(byte *)(iVar4 + 0x71f) =
             *(byte *)(iVar4 + 0x71f) & ~(byte)(1 << (int)*(char *)(iVar3 + 0x3e4));
        *(byte *)(iVar3 + 0x71f) =
             *(byte *)(iVar3 + 0x71f) & ~(byte)(1 << (int)*(char *)(iVar4 + 0x3e4));
        *(undefined1 *)(param_1 + 0x188) = *(undefined1 *)(iVar3 + 0x71a);
        zz_0066408_(iVar3,(int)*(char *)(param_1 + 0x188),(float *)(param_1 + 0x20),
                    (float *)(param_1 + 0x168));
        *(undefined4 *)(param_1 + 0x144) =
             *(undefined4 *)(iVar4 + *(char *)(param_1 + 0x89) * 0x30 + 0x8e0);
        *(undefined4 *)(param_1 + 0x148) =
             *(undefined4 *)(iVar4 + *(char *)(param_1 + 0x89) * 0x30 + 0x8f0);
        *(undefined4 *)(param_1 + 0x14c) =
             *(undefined4 *)(iVar4 + *(char *)(param_1 + 0x89) * 0x30 + 0x900);
        *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
        *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
        *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
        dVar5 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x144));
        if ((double)FLOAT_80438768 < dVar5) {
          dVar6 = 1.0 / SQRT(dVar5);
          dVar6 = DOUBLE_80438770 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80438778);
          dVar6 = DOUBLE_80438770 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80438778);
          dVar5 = (double)(float)(dVar5 * DOUBLE_80438770 * dVar6 *
                                          -(dVar5 * dVar6 * dVar6 - DOUBLE_80438778));
        }
        *(float *)(param_1 + 0x164) = (float)dVar5;
        **(undefined1 **)(param_1 + 0x184) = 2;
      }
      else {
        zz_00c590c_(param_1);
      }
    }
    else {
      zz_00c590c_(param_1);
    }
  }
  return;
}



// ==== 800c5010  FUN_800c5010 ====

/* WARNING: Removing unreachable block (ram,0x800c5714) */
/* WARNING: Removing unreachable block (ram,0x800c570c) */
/* WARNING: Removing unreachable block (ram,0x800c5704) */
/* WARNING: Removing unreachable block (ram,0x800c55e8) */
/* WARNING: Removing unreachable block (ram,0x800c5030) */
/* WARNING: Removing unreachable block (ram,0x800c5028) */
/* WARNING: Removing unreachable block (ram,0x800c5020) */
/* WARNING: Removing unreachable block (ram,0x800c544c) */

void FUN_800c5010(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  float afStack_a4 [3];
  float afStack_98 [3];
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  undefined4 local_7c;
  undefined4 local_78;
  float local_74;
  undefined4 local_70;
  undefined4 local_6c;
  float afStack_68 [3];
  float afStack_5c [5];
  
  iVar7 = *(int *)(param_1 + 0x15c);
  iVar8 = *(int *)(param_1 + 0x90);
  *(byte *)(iVar8 + 0x71e) = *(byte *)(iVar8 + 0x71e) & ~(byte)(1 << (int)*(char *)(iVar7 + 0x3e4));
  *(byte *)(iVar7 + 0x71e) = *(byte *)(iVar7 + 0x71e) & ~(byte)(1 << (int)*(char *)(iVar8 + 0x3e4));
  *(byte *)(iVar8 + 0x71f) = *(byte *)(iVar8 + 0x71f) & ~(byte)(1 << (int)*(char *)(iVar7 + 0x3e4));
  *(byte *)(iVar7 + 0x71f) = *(byte *)(iVar7 + 0x71f) & ~(byte)(1 << (int)*(char *)(iVar8 + 0x3e4));
  if (((byte)PTR_DAT_80433934[0xd4] == 0) ||
     (((int)*(char *)(iVar7 + 0x3e5) & ~(uint)(byte)PTR_DAT_80433934[0xd4]) == 0)) {
    iVar5 = zz_0084434_(iVar8,1);
    if (iVar5 == 0) {
      iVar5 = zz_0084434_(iVar7,0);
      if (iVar5 == 0) {
        pfVar9 = (float *)(param_1 + 0x150);
        *(undefined4 *)(param_1 + 0x144) =
             *(undefined4 *)(iVar8 + *(char *)(param_1 + 0x89) * 0x30 + 0x8e0);
        *(undefined4 *)(param_1 + 0x148) =
             *(undefined4 *)(iVar8 + *(char *)(param_1 + 0x89) * 0x30 + 0x8f0);
        *(undefined4 *)(param_1 + 0x14c) =
             *(undefined4 *)(iVar8 + *(char *)(param_1 + 0x89) * 0x30 + 0x900);
        gnt4_PSMTXMultVec_bl
                  ((float *)(iVar7 + *(char *)(param_1 + 0x188) * 0x30 + 0x8d4),
                   (float *)(param_1 + 0x168),pfVar9);
        uVar2 = DAT_802b0cb4;
        *(float *)(param_1 + 0x20) = *pfVar9;
        uVar3 = DAT_802b0cb8;
        *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x154);
        uVar4 = DAT_802b0cbc;
        *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x158);
        *(undefined4 *)(param_1 + 0x9c) = uVar2;
        *(undefined4 *)(param_1 + 0xa0) = uVar3;
        *(undefined4 *)(param_1 + 0xa4) = uVar4;
        gnt4_PSVECSubtract_bl(pfVar9,(float *)(param_1 + 0x144),&local_8c);
        dVar10 = gnt4_PSVECSquareMag_bl(&local_8c);
        if ((double)FLOAT_80438768 < dVar10) {
          *(float *)(param_1 + 0x38) = local_8c;
          *(float *)(param_1 + 0x3c) = local_88;
          *(float *)(param_1 + 0x40) = local_84;
        }
        *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) - (*(char *)(iVar7 + 0x749) * 3 + 1)
        ;
        if (*(short *)(param_1 + 0x1c) < 1) {
          zz_00c590c_(param_1);
        }
        else if (**(char **)(param_1 + 0x184) == '\x03') {
          zz_00c590c_(param_1);
        }
        else {
          *(undefined1 *)(iVar7 + 0x719) = 1;
          zz_00f0104_(iVar7,0x1b,7);
          dVar10 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x144),pfVar9);
          if ((double)FLOAT_80438768 < dVar10) {
            dVar12 = 1.0 / SQRT(dVar10);
            dVar12 = DOUBLE_80438770 * dVar12 * -(dVar10 * dVar12 * dVar12 - DOUBLE_80438778);
            dVar12 = DOUBLE_80438770 * dVar12 * -(dVar10 * dVar12 * dVar12 - DOUBLE_80438778);
            dVar10 = (double)(float)(dVar10 * DOUBLE_80438770 * dVar12 *
                                              -(dVar10 * dVar12 * dVar12 - DOUBLE_80438778));
          }
          *(float *)(param_1 + 0x160) = (float)dVar10;
          if ((*(char *)(iVar8 + 0x6cb) == '\0') && (*(char *)(iVar7 + 0x6cb) == '\0')) {
            if ((*(char *)(iVar8 + 0x1dd) == '\0') || (*(char *)(iVar7 + 0x1dd) == '\0')) {
              if (*(float *)(param_1 + 0x164) <= FLOAT_80438784) {
                *(float *)(param_1 + 0x164) = FLOAT_80438784;
              }
              else {
                *(float *)(param_1 + 0x164) = *(float *)(param_1 + 0x164) - FLOAT_80438788;
              }
            }
            else {
              dVar10 = gnt4_PSQUATDotProduct_bl((float *)(iVar8 + 0x1cc),(float *)(iVar7 + 0x1cc));
              if (dVar10 < (double)FLOAT_80438768) {
                *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x160);
              }
            }
          }
          else if (*(float *)(param_1 + 0x164) <= *(float *)(param_1 + 0x160)) {
            *(float *)(param_1 + 0x164) = *(float *)(param_1 + 0x160);
          }
          if (*(float *)(param_1 + 0x164) < *(float *)(param_1 + 0x160)) {
            bVar6 = *(char *)(iVar8 + 0x87) != '\0';
            if (*(char *)(iVar7 + 0x87) != '\0') {
              bVar6 = bVar6 | 2;
            }
            local_80 = *(float *)(param_1 + 0x144);
            local_7c = *(undefined4 *)(param_1 + 0x148);
            local_78 = *(undefined4 *)(param_1 + 0x14c);
            local_74 = *pfVar9;
            local_70 = *(undefined4 *)(param_1 + 0x154);
            local_6c = *(undefined4 *)(param_1 + 0x158);
            gnt4_PSVECSubtract_bl((float *)(iVar8 + 0x20),(float *)(iVar8 + 0x5e8),&local_8c);
            dVar10 = gnt4_PSVECMag_bl(&local_8c);
            if ((double)FLOAT_80438790 <= dVar10) {
              fVar1 = (float)((double)(FLOAT_8043878c * *(float *)(iVar8 + 0x204)) * dVar10);
            }
            else {
              fVar1 = FLOAT_8043878c * *(float *)(iVar8 + 0x204);
            }
            dVar12 = (double)fVar1;
            gnt4_PSVECSubtract_bl((float *)(iVar7 + 0x20),(float *)(iVar7 + 0x5e8),&local_8c);
            dVar10 = gnt4_PSVECMag_bl(&local_8c);
            if ((double)FLOAT_80438790 <= dVar10) {
              fVar1 = (float)((double)*(float *)(iVar7 + 0x204) * dVar10);
            }
            else {
              fVar1 = *(float *)(iVar7 + 0x204);
            }
            dVar10 = (double)fVar1;
            if (bVar6 == 2) {
              dVar10 = (double)(float)(dVar10 * (double)FLOAT_80438794);
            }
            else if (bVar6 < 2) {
              if (bVar6 != 0) {
                dVar12 = (double)(float)(dVar12 * (double)FLOAT_80438794);
              }
            }
            else if (bVar6 < 4) {
              if (*(float *)(iVar8 + 0x24) <= *(float *)(iVar7 + 0x24)) {
                if (*(float *)(iVar8 + 0x24) < *(float *)(iVar7 + 0x24)) {
                  dVar10 = (double)(float)(dVar10 * (double)FLOAT_80438794);
                }
              }
              else {
                dVar12 = (double)(float)(dVar12 * (double)FLOAT_80438794);
              }
            }
            gnt4_PSVECSubtract_bl(&local_74,&local_80,&local_8c);
            dVar11 = gnt4_PSVECSquareMag_bl(&local_8c);
            if (dVar11 <= (double)FLOAT_80438768) {
              return;
            }
            gnt4_PSVECNormalize_bl(&local_8c,afStack_98);
            gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x164),afStack_98,&local_8c);
            gnt4_PSVECAdd_bl(&local_80,&local_8c,afStack_a4);
            gnt4_PSVECSubtract_bl(afStack_a4,&local_74,&local_8c);
            dVar11 = gnt4_PSVECMag_bl(&local_8c);
            if (dVar11 <= (double)FLOAT_80438768) {
              return;
            }
            if (*(float *)(iVar7 + 0x204) < FLOAT_80438798) {
              dVar10 = (double)(float)(dVar11 * (double)(float)(dVar10 / (double)(float)(dVar12 + 
                                                  dVar10)));
              gnt4_PSQUATScale_bl(dVar10,afStack_98,afStack_68);
              gnt4_PSQUATScale_bl(-(double)(float)(dVar11 - dVar10),afStack_98,afStack_5c);
              zz_0084498_(iVar8,afStack_68);
              zz_0084498_(iVar7,afStack_5c);
              gnt4_PSVECNormalize_bl(afStack_5c,afStack_98);
            }
            else {
              gnt4_PSQUATScale_bl(dVar11,afStack_98,afStack_68);
              zz_0084498_(iVar8,afStack_68);
              gnt4_PSQUATScale_bl((double)FLOAT_8043879c,afStack_98,afStack_98);
            }
            local_8c = FLOAT_80438768;
            local_88 = FLOAT_8043879c;
            local_84 = FLOAT_80438768;
            dVar10 = gnt4_PSQUATDotProduct_bl(afStack_98,&local_8c);
            if (bVar6 == 2) {
              if ((double)FLOAT_804387a4 <= dVar10) {
                *(byte *)(iVar8 + 0x732) = *(byte *)(iVar8 + 0x732) | 8;
              }
            }
            else if (bVar6 < 2) {
              if ((bVar6 != 0) && (dVar10 <= (double)FLOAT_804387a0)) {
                *(byte *)(iVar7 + 0x732) = *(byte *)(iVar7 + 0x732) | 8;
              }
            }
            else if (bVar6 < 4) {
              if (*(float *)(iVar8 + 0x24) <= *(float *)(iVar7 + 0x24)) {
                if ((*(float *)(iVar8 + 0x24) < *(float *)(iVar7 + 0x24)) &&
                   ((double)FLOAT_804387ac <= dVar10)) {
                  *(float *)(iVar8 + 0x48) = FLOAT_80438768;
                  *(byte *)(iVar8 + 0x732) = *(byte *)(iVar8 + 0x732) | 8;
                }
              }
              else if (dVar10 <= (double)FLOAT_804387a8) {
                *(float *)(iVar7 + 0x48) = FLOAT_80438768;
                *(byte *)(iVar7 + 0x732) = *(byte *)(iVar7 + 0x732) | 8;
              }
            }
            *(byte *)(iVar8 + 0x71f) =
                 *(byte *)(iVar8 + 0x71f) | (byte)(1 << (int)*(char *)(iVar7 + 0x3e4));
            *(byte *)(iVar7 + 0x71f) =
                 *(byte *)(iVar7 + 0x71f) | (byte)(1 << (int)*(char *)(iVar8 + 0x3e4));
          }
          *(byte *)(iVar8 + 0x71e) =
               *(byte *)(iVar8 + 0x71e) | (byte)(1 << (int)*(char *)(iVar7 + 0x3e4));
          *(byte *)(iVar7 + 0x71e) =
               *(byte *)(iVar7 + 0x71e) | (byte)(1 << (int)*(char *)(iVar8 + 0x3e4));
        }
      }
      else {
        zz_00c590c_(param_1);
      }
    }
    else {
      zz_00c590c_(param_1);
    }
  }
  else {
    zz_00c590c_(param_1);
  }
  return;
}



// ==== 800c5730  zz_00c5730_ ====

void zz_00c5730_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  iVar5 = *(int *)(param_1 + 0x90);
  iVar1 = iVar5 + *(char *)(param_1 + 0x89) * 0x30;
  local_18 = *(float *)(iVar1 + 0x8e0);
  local_14 = *(undefined4 *)(iVar1 + 0x8f0);
  local_10 = *(undefined4 *)(iVar1 + 0x900);
  dVar6 = gnt4_PSVECSquareDistance_bl(&local_18,(float *)(param_1 + 0x20));
  if ((double)FLOAT_80438768 < dVar6) {
    dVar7 = 1.0 / SQRT(dVar6);
    dVar7 = DOUBLE_80438770 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80438778);
    dVar7 = DOUBLE_80438770 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80438778);
    dVar6 = (double)(float)(dVar6 * DOUBLE_80438770 * dVar7 *
                                    -(dVar6 * dVar7 * dVar7 - DOUBLE_80438778));
  }
  if ((double)*(float *)(param_1 + 0x44) <= dVar6) {
    uVar4 = *(undefined4 *)(param_1 + 0x38);
    uVar3 = *(undefined4 *)(param_1 + 0x3c);
    uVar2 = *(undefined4 *)(param_1 + 0x40);
    dVar6 = (double)FLOAT_804387b0;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x174);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x178);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x17c);
    zz_006c440_(dVar6,param_1,&local_18);
    *(undefined4 *)(param_1 + 0x174) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(param_1 + 0x178) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x17c) = *(undefined4 *)(param_1 + 0x40);
    *(undefined4 *)(param_1 + 0x38) = uVar4;
    *(undefined4 *)(param_1 + 0x3c) = uVar3;
    *(undefined4 *)(param_1 + 0x40) = uVar2;
    *(undefined4 *)(param_1 + 0x144) =
         *(undefined4 *)(iVar5 + *(char *)(param_1 + 0x89) * 0x30 + 0x8e0);
    *(undefined4 *)(param_1 + 0x148) =
         *(undefined4 *)(iVar5 + *(char *)(param_1 + 0x89) * 0x30 + 0x8f0);
    *(undefined4 *)(param_1 + 0x14c) =
         *(undefined4 *)(iVar5 + *(char *)(param_1 + 0x89) * 0x30 + 0x900);
    *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
  }
  else {
    **(undefined1 **)(param_1 + 0x184) = 0;
    zz_006de10_(iVar5,2);
    zz_00f036c_(param_1,0xc0);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 800c590c  zz_00c590c_ ====

void zz_00c590c_(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  float *pfVar5;
  double dVar6;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  bVar1 = *(byte *)(param_1 + 0x11);
  iVar4 = *(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30;
  local_1c = *(float *)(iVar4 + 0x8e0);
  local_18 = *(undefined4 *)(iVar4 + 0x8f0);
  local_14 = *(undefined4 *)(iVar4 + 0x900);
  gnt4_PSVECSubtract_bl(&local_1c,(float *)(param_1 + 0x20),&local_28);
  dVar6 = gnt4_PSVECSquareMag_bl(&local_28);
  uVar2 = DAT_802b0cac;
  if (dVar6 <= (double)FLOAT_80438768) {
    *(undefined4 *)(param_1 + 0x174) = DAT_802b0ca8;
    uVar3 = DAT_802b0cb0;
    *(undefined4 *)(param_1 + 0x178) = uVar2;
    *(undefined4 *)(param_1 + 0x17c) = uVar3;
  }
  else {
    *(float *)(param_1 + 0x174) = local_28;
    *(undefined4 *)(param_1 + 0x178) = local_24;
    *(undefined4 *)(param_1 + 0x17c) = local_20;
  }
  if (*(float *)(&DAT_80305214 + (uint)bVar1 * 0x20) <= *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = *(float *)(&DAT_80305214 + (uint)bVar1 * 0x20);
  }
  pfVar5 = (float *)(param_1 + 0x174);
  gnt4_PSVECNormalize_bl(pfVar5,pfVar5);
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),pfVar5,pfVar5);
  *(undefined1 *)(param_1 + 0x19) = 2;
  zz_008aff0_(param_1);
  **(undefined1 **)(param_1 + 0x184) = 3;
  return;
}



// ==== 800c5a34  FUN_800c5a34 ====

void FUN_800c5a34(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800c5a40  FUN_800c5a40 ====

void FUN_800c5a40(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c5a60  FUN_800c5a60 ====

void FUN_800c5a60(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined8 uVar2;
  
  uVar1 = 1;
  if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
    uVar1 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  uVar2 = zz_00097b4_(*(int *)(param_9 + 0xe0),uVar1);
  if (-1 < *(char *)(param_9 + 0x12)) {
    zz_00076d0_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe4),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe4),uVar1);
  }
  return;
}



// ==== 800c5ae4  zz_00c5ae4_ ====

void zz_00c5ae4_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_800c5bc4;
    *(code **)(puVar1 + 0x10c) = FUN_800c5e0c;
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



// ==== 800c5bc4  FUN_800c5bc4 ====

void FUN_800c5bc4(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80305250)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800c5c18  FUN_800c5c18 ====

void FUN_800c5c18(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  float *pfVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  double dVar8;
  
  iVar6 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0xc0;
  fVar1 = FLOAT_804387b8;
  *(undefined1 *)(param_9 + 0x89) = 7;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar6 = zz_0006f98_(iVar6);
  iVar4 = iVar6 + 0xc28;
  uVar2 = 6;
  zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar6 + 0x600),
              *(int *)(param_9 + 0xe0),6,iVar4,in_r7,in_r8,in_r9,in_r10);
  dVar8 = (double)FLOAT_804387bc;
  zz_0008614_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar6 + 0x600),
              *(int *)(param_9 + 0xe0),uVar2,iVar4,in_r7,in_r8,in_r9,in_r10);
  iVar5 = iVar6 + 0xc28;
  pfVar3 = (float *)0x6;
  zz_0007030_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar6 + 0x600),
              *(int *)(param_9 + 0xe4),6,iVar5,in_r7,in_r8,in_r9,in_r10);
  iVar4 = *(int *)(param_9 + 0xe4);
  dVar8 = (double)FLOAT_804387bc;
  zz_0008614_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar6 + 0x600),
              iVar4,pfVar3,iVar5,in_r7,in_r8,in_r9,in_r10);
  zz_0007c54_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,iVar4,pfVar3,iVar5,in_r7,in_r8,in_r9,in_r10);
  uVar7 = zz_0007cac_((double)FLOAT_804387c0,*(int *)(param_9 + 0xe4));
  *(byte *)(param_9 + 0x82) = *(byte *)(param_9 + 0x96) + 0x41;
  FUN_800c5d18(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
               (uint)*(byte *)(param_9 + 0x96),pfVar3,iVar5,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 800c5d18  FUN_800c5d18 ====

/* WARNING: Removing unreachable block (ram,0x800c5db8) */
/* WARNING: Removing unreachable block (ram,0x800c5d28) */

void FUN_800c5d18(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int iVar2;
  undefined8 uVar3;
  double dVar4;
  
  iVar2 = *(int *)(param_9 + 0x90);
  if ((*(uint *)(iVar2 + 0x5e0) & 0x20000000) == 0) {
    iVar1 = *(char *)(iVar2 + 0x6e8) * 4;
    dVar4 = (double)*(float *)(&DAT_80305260 + iVar1);
    if (*(char *)(iVar2 + 0x71c) == '\0') {
      dVar4 = (double)(float)(dVar4 * (double)*(float *)(iVar2 + 0x1dc8));
    }
    uVar3 = FUN_80008ef4(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         *(int *)(param_9 + 0xe0),iVar1,param_11,param_12,param_13,param_14,param_15
                         ,param_16);
    zz_0007c30_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,param_15,
                param_16);
    uVar3 = FUN_80008ef4(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         *(int *)(param_9 + 0xe4),extraout_r4_00,param_11,param_12,param_13,param_14
                         ,param_15,param_16);
    zz_0007c30_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe4),extraout_r4_01,param_11,param_12,param_13,param_14,param_15
                ,param_16);
    if ('\0' < *(char *)(iVar2 + 0x6e8)) {
      zz_00f0104_(*(int *)(param_9 + 0x90),2,2);
    }
  }
  return;
}



// ==== 800c5dec  FUN_800c5dec ====

void FUN_800c5dec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c5e0c  FUN_800c5e0c ====

void FUN_800c5e0c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') &&
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) != '\x04')) {
    iVar2 = *(int *)(param_9 + 0xe0);
    uVar1 = 1;
  }
  else {
    iVar2 = *(int *)(param_9 + 0xe4);
    uVar1 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar2,uVar1);
  return;
}



// ==== 800c5e84  zz_00c5e84_ ====

void zz_00c5e84_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,4);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_800c5f64;
    *(code **)(puVar1 + 0x10c) = FUN_800c6178;
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



// ==== 800c5f64  FUN_800c5f64 ====

void FUN_800c5f64(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80305270)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800c5fb8  FUN_800c5fb8 ====

void FUN_800c5fb8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  iVar4 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0xc0;
  fVar1 = FLOAT_804387c8;
  *(undefined1 *)(param_9 + 0x89) = 0xb;
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),5,iVar4 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),7,iVar4 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe8),5,iVar4 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  uVar2 = 7;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xec),7,iVar3,in_r7,in_r8,in_r9,
                      in_r10);
  uVar5 = zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe8),extraout_r4,uVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,uVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804387cc,*(int *)(param_9 + 0xe8));
  zz_0007cac_((double)FLOAT_804387cc,*(int *)(param_9 + 0xec));
  *(undefined2 *)(param_9 + 0x144) = 0;
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00c60dc_(param_9);
  return;
}



// ==== 800c60dc  zz_00c60dc_ ====

void zz_00c60dc_(int param_1)

{
  *(short *)(param_1 + 0x144) =
       (short)(int)(FLOAT_804387d0 *
                    *(float *)(*(int *)(param_1 + 0x90) + 0x1dc8) *
                    *(float *)(&DAT_80305280 + *(char *)(*(int *)(param_1 + 0x90) + 0x6e8) * 4) +
                   (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x144) ^ 0x80000000
                                           ) - DOUBLE_804387d8));
  return;
}



// ==== 800c6158  FUN_800c6158 ====

void FUN_800c6158(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c6178  FUN_800c6178 ====

void FUN_800c6178(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  uint uVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + 0x144) == '\0') {
    if ((*(char *)(iVar1 + 0xae) == '\0') && (*(char *)(iVar1 + 0x3ec) != '\x04')) {
      iVar1 = 0;
      uVar3 = 1;
    }
    else {
      iVar1 = 2;
      uVar3 = 0x44;
    }
    iVar4 = param_9 + iVar1 * 4;
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar4 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_00097b4_(*(int *)(iVar4 + 0xe0),uVar3);
    local_18 = 0x43300000;
    uStack_14 = (int)*(short *)(param_9 + 0x144) ^ 0x80000000;
    dVar6 = (double)FLOAT_804387e0;
    gnt4_PSMTXRotRad_bl((double)(float)(dVar6 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                 uStack_14) -
                                                               DOUBLE_804387d8)),afStack_48,0x78);
    pfVar2 = afStack_48;
    uVar5 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
    iVar1 = param_9 + (iVar1 + 1) * 4;
    zz_00076d0_(uVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar1 + 0xe0),
                afStack_48,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(*(int *)(iVar1 + 0xe0),uVar3);
  }
  return;
}



// ==== 800c627c  zz_00c627c_ ====

bool zz_00c627c_(int param_1,undefined1 param_2,undefined4 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x11] = 0;
    *(code **)(puVar1 + 0xc) = FUN_800c6394;
    *(code **)(puVar1 + 0x10c) = FUN_800c6724;
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
    *(undefined4 *)(puVar1 + 0x144) = param_3;
  }
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800c6394  FUN_800c6394 ====

void FUN_800c6394(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80305344)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800c63e8  FUN_800c63e8 ====

void FUN_800c63e8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 extraout_r4;
  int iVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar2 = *(char *)(param_9 + 0x13) * 0x24;
  uVar1 = *(undefined4 *)(&DAT_80305298 + iVar2);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80305294 + iVar2);
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8030529c + iVar2);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_803052a0 + iVar2);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_803052a4 + iVar2);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80305292 + iVar2);
  uVar6 = gnt4_PSMTXMultVec_bl
                    ((float *)(iVar5 + *(short *)(&DAT_80305292 + iVar2) * 0x30 + 0x8d4),
                     (float *)(&DAT_80305294 + iVar2),(float *)(param_9 + 0x20));
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80305290 + iVar2),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80305290 + iVar2);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804387e8,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(param_9 + 0x20);
  *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(param_9 + 0x24);
  *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(param_9 + 0x28);
  *(undefined2 *)(param_9 + 0x154) = 0;
  if (-1 < *(short *)(&DAT_803052a6 + iVar2)) {
    zz_00c74ec_(param_9,(int)*(short *)(&DAT_803052a6 + iVar2));
  }
  zz_00c6544_(param_9);
  return;
}



// ==== 800c6544  zz_00c6544_ ====

/* WARNING: Removing unreachable block (ram,0x800c66d0) */
/* WARNING: Removing unreachable block (ram,0x800c6554) */

void zz_00c6544_(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  byte *pbVar3;
  float *pfVar4;
  int iVar5;
  double dVar6;
  float afStack_38 [6];
  
  iVar5 = *(int *)(param_1 + 0x90);
  iVar2 = *(char *)(param_1 + 0x13) * 0x24;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar5 + *(short *)(&DAT_80305292 + iVar2) * 0x30 + 0x8d4),
             (float *)(&DAT_80305294 + iVar2),afStack_38);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(iVar5 + 0x70);
  *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(iVar5 + 0x74);
  *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + *(short *)(&DAT_803052a0 + iVar2);
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + *(short *)(&DAT_803052a2 + iVar2);
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(&DAT_803052a4 + iVar2);
  *(short *)(param_1 + 0x154) = *(short *)(param_1 + 0x154) + *(short *)(&DAT_803052b0 + iVar2);
  dVar6 = zz_0045204_(*(short *)(param_1 + 0x154));
  pfVar4 = (float *)(param_1 + 0x148);
  zz_0046588_((double)*(float *)(&DAT_803052a8 + iVar2),pfVar4,afStack_38,pfVar4);
  *(float *)(param_1 + 0x20) = *pfVar4;
  *(float *)(param_1 + 0x24) =
       (float)(dVar6 * (double)(*(float *)(&DAT_803052ac + iVar2) * *(float *)(iVar5 + 0xb4)) +
              (double)*(float *)(param_1 + 0x14c));
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x150);
  uVar1 = *(undefined4 *)(iVar5 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x58) = uVar1;
  *(undefined1 *)(param_1 + 0xa8) = *(undefined1 *)(iVar5 + 0xa8);
  pbVar3 = *(byte **)(param_1 + 0x144);
  if ((((pbVar3 != (byte *)0x0) && ((*pbVar3 & 0x80) != 0)) &&
      (*pbVar3 = *pbVar3 & 0x7f, (**(byte **)(param_1 + 0x144) & 1) != 0)) &&
     (-1 < *(short *)(&DAT_803052b2 + iVar2))) {
    *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(iVar5 + 0xcc);
    *(undefined4 *)(param_1 + 200) = *(undefined4 *)(iVar5 + 200);
    *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(iVar5 + 0xd0);
    uVar1 = *(undefined4 *)(iVar5 + 0xb4);
    *(undefined4 *)(param_1 + 0x60) = uVar1;
    *(undefined4 *)(param_1 + 0x5c) = uVar1;
    *(undefined4 *)(param_1 + 0x58) = uVar1;
    *(undefined4 *)(param_1 + 0xb8) = uVar1;
    *(undefined4 *)(param_1 + 0xb4) = uVar1;
    zz_00c3be0_(param_1,(char)*(undefined2 *)(&DAT_803052b2 + iVar2));
  }
  return;
}



// ==== 800c6704  FUN_800c6704 ====

void FUN_800c6704(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c6724  FUN_800c6724 ====

void FUN_800c6724(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined *param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if ((*(byte **)(param_9 + 0x144) == (byte *)0x0) || ((**(byte **)(param_9 + 0x144) & 1) != 0)) {
    if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
      iVar1 = *(int *)(param_9 + 0xe0);
      if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
        uVar2 = 0x44;
      }
      else {
        uVar2 = 1;
      }
    }
    else {
      iVar1 = *(int *)(param_9 + 0xe4);
      uVar2 = 0x44;
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
                (float *)(param_9 + 0x114),param_9,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar1,uVar2);
  }
  return;
}



// ==== 800c67bc  zz_00c67bc_ ====

void zz_00c67bc_(int param_1,undefined1 param_2,undefined1 param_3)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  uint uVar4;
  
  puVar2 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x83] = 0x10;
    puVar2[0x10] = 0x12;
    puVar2[0x11] = param_2;
    *(code **)(puVar2 + 0xc) = FUN_800c6c84;
    *(code **)(puVar2 + 0x10c) = FUN_800c715c;
    puVar2[0x13] = param_3;
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
    iVar3 = (uint)(byte)puVar2[0x11] * 0x34;
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + (char)(&DAT_80305e59)[iVar3] * 0x30 + 0x8d4),
               (float *)(iVar3 + -0x7fcfa1a4),(float *)(puVar2 + 0x20));
    cVar1 = (&DAT_80305e84)[iVar3];
    if (cVar1 == '\x01') {
      *(undefined4 *)(puVar2 + 0x38) =
           *(undefined4 *)(param_1 + (char)(&DAT_80305e59)[iVar3] * 0x30 + 0x8d8);
      *(undefined4 *)(puVar2 + 0x3c) =
           *(undefined4 *)(param_1 + (char)(&DAT_80305e59)[iVar3] * 0x30 + 0x8e8);
      *(undefined4 *)(puVar2 + 0x40) =
           *(undefined4 *)(param_1 + (char)(&DAT_80305e59)[iVar3] * 0x30 + 0x8f8);
    }
    else if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        *(undefined4 *)(puVar2 + 0x38) =
             *(undefined4 *)(param_1 + (char)(&DAT_80305e59)[iVar3] * 0x30 + 0x8d4);
        *(undefined4 *)(puVar2 + 0x3c) =
             *(undefined4 *)(param_1 + (char)(&DAT_80305e59)[iVar3] * 0x30 + 0x8e4);
        *(undefined4 *)(puVar2 + 0x40) =
             *(undefined4 *)(param_1 + (char)(&DAT_80305e59)[iVar3] * 0x30 + 0x8f4);
      }
    }
    else if (cVar1 < '\x03') {
      *(undefined4 *)(puVar2 + 0x38) =
           *(undefined4 *)(param_1 + (char)(&DAT_80305e59)[iVar3] * 0x30 + 0x8dc);
      *(undefined4 *)(puVar2 + 0x3c) =
           *(undefined4 *)(param_1 + (char)(&DAT_80305e59)[iVar3] * 0x30 + 0x8ec);
      *(undefined4 *)(puVar2 + 0x40) =
           *(undefined4 *)(param_1 + (char)(&DAT_80305e59)[iVar3] * 0x30 + 0x8fc);
    }
    gnt4_PSVECNormalize_bl((float *)(puVar2 + 0x38),(float *)(puVar2 + 0x38));
    if ((&DAT_80305e85)[iVar3] == '\0') {
      gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80305e68 + iVar3),(float *)(puVar2 + 0x38),
                          (float *)(puVar2 + 0x38));
    }
    else {
      gnt4_PSQUATScale_bl(-(double)*(float *)(&DAT_80305e68 + iVar3),(float *)(puVar2 + 0x38),
                          (float *)(puVar2 + 0x38));
    }
    zz_0046470_((float *)(param_1 + (char)(&DAT_80305e59)[iVar3] * 0x30 + 0x8d4),
                (float *)(puVar2 + 0x15c));
    uVar4 = zz_00055fc_();
    *(short *)(puVar2 + 0x70) = (short)(uVar4 << 0xb);
    uVar4 = zz_00055fc_();
    *(short *)(puVar2 + 0x72) = (short)(uVar4 << 0xb);
    uVar4 = zz_00055fc_();
    *(short *)(puVar2 + 0x74) = (short)(uVar4 << 0xb);
  }
  return;
}



// ==== 800c6a94  FUN_800c6a94 ====

void FUN_800c6a94(int param_1,float *param_2,float *param_3,undefined1 param_4,undefined1 param_5)

{
  undefined1 *puVar1;
  int iVar2;
  uint uVar3;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x83] = 0x10;
    puVar1[0x10] = 0x12;
    puVar1[0x11] = param_5;
    *(code **)(puVar1 + 0xc) = FUN_800c6c84;
    *(code **)(puVar1 + 0x10c) = FUN_800c715c;
    puVar1[0x13] = param_4;
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
    iVar2 = (char)puVar1[0x11] * 0x34;
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + (char)(&DAT_80305e59)[iVar2] * 0x30 + 0x8d4),param_2,
               (float *)(puVar1 + 0x20));
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + (char)(&DAT_80305e59)[iVar2] * 0x30 + 0x8d4),param_3,
               (float *)(puVar1 + 0x38));
    gnt4_PSVECSubtract_bl
              ((float *)(puVar1 + 0x38),(float *)(puVar1 + 0x20),(float *)(puVar1 + 0x38));
    gnt4_PSVECNormalize_bl((float *)(puVar1 + 0x38),(float *)(puVar1 + 0x38));
    if ((&DAT_80305e85)[iVar2] == '\0') {
      gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80305e68 + iVar2),(float *)(puVar1 + 0x38),
                          (float *)(puVar1 + 0x38));
    }
    else {
      gnt4_PSQUATScale_bl(-(double)*(float *)(&DAT_80305e68 + iVar2),(float *)(puVar1 + 0x38),
                          (float *)(puVar1 + 0x38));
    }
    zz_0046470_((float *)(param_1 + (char)(&DAT_80305e59)[iVar2] * 0x30 + 0x8d4),
                (float *)(puVar1 + 0x15c));
    uVar3 = zz_00055fc_();
    *(short *)(puVar1 + 0x70) = (short)(uVar3 << 0xb);
    uVar3 = zz_00055fc_();
    *(short *)(puVar1 + 0x72) = (short)(uVar3 << 0xb);
    uVar3 = zz_00055fc_();
    *(short *)(puVar1 + 0x74) = (short)(uVar3 << 0xb);
  }
  return;
}



// ==== 800c6c84  FUN_800c6c84 ====

void FUN_800c6c84(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80306094)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800c6d1c  FUN_800c6d1c ====

void FUN_800c6d1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x34;
  uVar3 = (uint)(byte)(&DAT_80305e5b)[iVar4];
  *(undefined *)(param_9 + 0x12) = (&DAT_80305e5b)[iVar4];
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar5 = iVar4;
  uVar6 = zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  *(undefined2 *)(param_9 + 0x1c) = 0x14;
  *(undefined4 *)(param_9 + 0x168) = *(undefined4 *)(&DAT_80305e88 + iVar4);
  if ((-1 < (char)(&DAT_80305e5a)[iVar4]) &&
     (iVar1 = zz_008ac80_(param_9,(int)(char)(&DAT_80305e5a)[iVar4]), iVar1 == 0)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    return;
  }
  iVar1 = zz_0006f78_(param_9);
  uVar2 = zz_00055fc_();
  zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              *(int *)(param_9 + 0xe0),(uint)(byte)(&DAT_80305e58)[iVar4] + uVar2 % 3,uVar3,iVar5,
              in_r8,in_r9,in_r10);
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80305e68 + iVar4),(float *)(param_9 + 0x38),
                      (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80305e68 + iVar4);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined4 *)(&DAT_80305e6c + iVar4);
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  if ((-1 < *(short *)(&DAT_80305e86 + iVar4)) && ((*(byte *)(param_9 + 0x13) & 7) == 0)) {
    zz_00f036c_(param_9,199);
  }
  zz_00c6e8c_(param_9);
  return;
}



// ==== 800c6e8c  zz_00c6e8c_ ====

void zz_00c6e8c_(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  float afStack_28 [3];
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  fVar1 = FLOAT_804387f0;
  iVar3 = *(int *)(param_1 + 0x90);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  *(float *)(param_1 + 0x150) = *(float *)(param_1 + 0x150) + fVar1;
  zz_00c7034_((float *)(param_1 + 0x144));
  *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x15c) * *(float *)(param_1 + 0x144);
  *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x160) * *(float *)(param_1 + 0x148);
  *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x164) * *(float *)(param_1 + 0x14c);
  if (*(short *)(param_1 + 0x1c) < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x34;
      FUN_80083874((double)*(float *)(&DAT_80305e74 + iVar2),param_1);
      FUN_80083ad4((double)*(float *)(&DAT_80305e70 + iVar2),param_1,
                   (char)*(undefined4 *)(&DAT_80305e6c + iVar2));
      zz_00833ec_(param_1);
      zz_0083524_(param_1);
      iVar2 = zz_0083714_(param_1);
      if (iVar2 == 0) {
        iVar2 = zz_003e978_((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),&local_1c);
        if (iVar2 != 0) {
          *(float *)(param_1 + 0x20) = local_1c;
          *(undefined4 *)(param_1 + 0x24) = local_18;
          *(undefined4 *)(param_1 + 0x28) = local_14;
          *(undefined1 *)(param_1 + 0x18) = 2;
          zz_008aff0_(param_1);
        }
        if ('\0' < *(char *)(param_1 + 0x12)) {
          gnt4_PSVECSubtract_bl((float *)(iVar3 + 0x20),(float *)(iVar3 + 0x2c),afStack_28);
          gnt4_PSVECAdd_bl(afStack_28,(float *)(param_1 + 0x20),(float *)(param_1 + 0x20));
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



// ==== 800c7034  zz_00c7034_ ====

void zz_00c7034_(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  
  fVar7 = FLOAT_804387f4;
  iVar5 = *(char *)(param_1 + 4) * 0x10;
  fVar4 = *(float *)(&DAT_803060a4 + iVar5);
  fVar1 = *(float *)(&DAT_803060a8 + iVar5);
  fVar2 = *(float *)(&DAT_803060ac + iVar5);
  fVar3 = *(float *)(&DAT_803060b0 + iVar5);
  if ((param_1[3] == fVar4) || (FLOAT_804387f4 == fVar4)) {
    *param_1 = fVar1;
    param_1[1] = fVar2;
    param_1[2] = fVar3;
    return;
  }
  fVar6 = param_1[3] - fVar4;
  iVar5 = (*(char *)(param_1 + 4) + 1) * 0x10;
  fVar4 = *(float *)(&DAT_803060a4 + iVar5) - fVar4;
  *param_1 = ((*(float *)(&DAT_803060a8 + iVar5) - fVar1) / fVar4) * fVar6 + fVar1;
  param_1[1] = ((*(float *)(&DAT_803060ac + iVar5) - fVar2) / fVar4) * fVar6 + fVar2;
  param_1[2] = ((*(float *)(&DAT_803060b0 + iVar5) - fVar3) / fVar4) * fVar6 + fVar3;
  fVar1 = *(float *)(&DAT_803060a4 + iVar5);
  if ((param_1[3] <= fVar1) && (fVar7 != fVar1)) {
    return;
  }
  *(char *)(param_1 + 4) = *(char *)(param_1 + 4) + '\x01';
  return;
}



// ==== 800c7100  FUN_800c7100 ====

void FUN_800c7100(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800c713c  FUN_800c713c ====

void FUN_800c713c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c715c  FUN_800c715c ====

void FUN_800c715c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  double dVar2;
  undefined8 uVar3;
  double dVar4;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_38 [13];
  
  dVar2 = (double)*(float *)(param_1 + 0x168);
  dVar4 = dVar2;
  gnt4_PSMTXScale_bl(dVar2,dVar2,dVar2,afStack_38);
  pfVar1 = afStack_38;
  uVar3 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar3,dVar2,dVar4,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),afStack_38,
              (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
  return;
}



// ==== 800c71c0  zz_00c71c0_ ====

void zz_00c71c0_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,8,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_800c72c0;
    puVar1[0x13] = param_2;
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
    *(short *)(puVar1 + 0x14c) =
         (short)*(char *)(param_1 + 0x1afd) + *(char *)(param_1 + 0x1afc) * 0x1000;
  }
  return;
}



// ==== 800c72c0  FUN_800c72c0 ====

void FUN_800c72c0(int param_1)

{
  (*(code *)(&PTR_FUN_803060d4)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800c72fc  FUN_800c72fc ====

void FUN_800c72fc(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(undefined2 *)(param_1 + 0x1c) = 0;
  *(undefined2 *)(param_1 + 0x1e) = 300;
  *(char *)(param_1 + 0x89) = (char)*(undefined4 *)(&DAT_803060e4 + *(char *)(param_1 + 0x13) * 4);
  FUN_800c7350(param_1);
  return;
}



// ==== 800c7350  FUN_800c7350 ====

/* WARNING: Removing unreachable block (ram,0x800c74a4) */
/* WARNING: Removing unreachable block (ram,0x800c749c) */
/* WARNING: Removing unreachable block (ram,0x800c7368) */
/* WARNING: Removing unreachable block (ram,0x800c7360) */

void FUN_800c7350(int param_1)

{
  char cVar1;
  bool bVar2;
  short sVar3;
  float *pfVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  
  cVar1 = *(char *)(param_1 + 0x19);
  iVar5 = *(int *)(param_1 + 0x90);
  if (cVar1 != '\x01') {
    if (('\0' < cVar1) || (cVar1 < '\0')) goto LAB_800c7478;
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    *(undefined **)(param_1 + 0x148) = (&PTR_DAT_80305e48)[*(char *)(param_1 + 0x13)];
    *(undefined4 *)(param_1 + 0x150) = 0;
  }
  bVar2 = false;
  pfVar4 = *(float **)(param_1 + 0x148);
  dVar7 = (double)*(float *)(iVar5 + 0x1ae0);
  if (*(short *)(param_1 + 0x14c) ==
      (short)((short)*(char *)(iVar5 + 0x1afd) + *(char *)(iVar5 + 0x1afc) * 0x1000)) {
    dVar8 = (double)FLOAT_804387f8;
    while ((dVar6 = (double)*pfVar4, dVar8 < dVar6 && (dVar6 < dVar7))) {
      FUN_800c6a94(iVar5,pfVar4 + 1,pfVar4 + 4,(char)*(undefined4 *)(param_1 + 0x150),
                   (&DAT_80433b38)[*(char *)(param_1 + 0x13)]);
      pfVar4 = pfVar4 + 7;
      *(int *)(param_1 + 0x150) = *(int *)(param_1 + 0x150) + 1;
      *(float **)(param_1 + 0x148) = pfVar4;
    }
    if (dVar6 < (double)FLOAT_804387f8) {
      bVar2 = true;
    }
  }
  else {
    bVar2 = true;
  }
  if (bVar2) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
LAB_800c7478:
  sVar3 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar3;
  if (sVar3 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 800c74cc  FUN_800c74cc ====

void FUN_800c74cc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c74ec  zz_00c74ec_ ====

undefined1 * zz_00c74ec_(int param_1,int param_2)

{
  undefined1 *puVar1;
  
  puVar1 = (undefined1 *)0x0;
  if (*PTR_DAT_80433930 != '\x05') {
    puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,0,
                         (int)*(short *)(&DAT_803072c8 + param_2 * 8));
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x10] = 0xe;
      puVar1[0x11] = (char)param_2;
      puVar1[0x12] = (char)*(undefined2 *)(&DAT_803072ca + param_2 * 8);
      puVar1[0x13] = (char)*(short *)(&DAT_803072c8 + param_2 * 8);
      *(code **)(puVar1 + 0xc) = FUN_800c7664;
      *(code **)(puVar1 + 0x10c) = FUN_800c7954;
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
      if ((*(char *)(param_1 + 0x83) == '\0') || (*(char *)(param_1 + 0x83) == '\x18')) {
        *(byte *)(*(int *)(param_1 + 0x90) + 0x708) =
             *(byte *)(*(int *)(param_1 + 0x90) + 0x708) | (byte)(1 << (int)(char)puVar1[0x12]);
      }
    }
  }
  return puVar1;
}



// ==== 800c7664  FUN_800c7664 ====

void FUN_800c7664(int param_1)

{
  (*(code *)(&PTR_FUN_80307550)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800c76a0  FUN_800c76a0 ====

void FUN_800c76a0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  uVar1 = (int)*(char *)(param_9 + 0x13) << 6;
  if (uVar1 < 0x81) {
    *(int *)(param_9 + 0x54) = param_9 + 0x144;
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar2 = zz_0006dc8_(uVar1);
    *(int **)(param_9 + 0xdc) = piVar2;
    if (piVar2 != (int *)0x0) {
      *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_9 + 0x54) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(code **)(param_9 + 0x100) = FUN_800c79f8;
    if (*(char *)(*(int *)(param_9 + 0x8c) + 0x83) == '\0') {
      uVar6 = zz_0089100_(param_9,(int)*(char *)(*(int *)(param_9 + 0x8c) + 0x3e4) + 0x10,1);
    }
    else {
      uVar6 = zz_0089100_(param_9,1,1);
    }
    iVar5 = 0;
    iVar4 = param_9;
    for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
      uVar6 = zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374
                          ,*(int *)(iVar4 + 0xe0),
                          (uint)(byte)(&PTR_DAT_803072cc)[*(char *)(param_9 + 0x11) * 2][iVar5],
                          param_12,param_13,param_14,param_15,param_16);
      iVar5 = iVar5 + 0x18;
      iVar4 = iVar4 + 4;
    }
    *(undefined1 *)(param_9 + 0xa8) = 0;
    *(undefined1 *)(param_9 + 0xa9) = 0;
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 800c77ec  FUN_800c77ec ====

void FUN_800c77ec(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x8c);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + 1;
  if (*(char *)(iVar4 + *(char *)(param_1 + 0x12) + 0xa8) != '\0') {
    *(char *)(param_1 + 0xa9) = *(char *)(param_1 + 0xa8);
    if (*(char *)(param_1 + 0xa8) != '\0') {
      iVar3 = 0;
      for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
        iVar1 = *(int *)(param_1 + 0x54) + iVar3;
        *(undefined4 *)(iVar1 + 0x30) = *(undefined4 *)(iVar1 + 4);
        *(undefined4 *)(iVar1 + 0x34) = *(undefined4 *)(iVar1 + 0x14);
        *(undefined4 *)(iVar1 + 0x38) = *(undefined4 *)(iVar1 + 0x24);
        gnt4_PSVECNormalize_bl((float *)(iVar1 + 0x30),(float *)(iVar1 + 0x30));
        iVar3 = iVar3 + 0x40;
      }
    }
  }
  *(undefined1 *)(param_1 + 0xa8) = *(undefined1 *)(iVar4 + *(char *)(param_1 + 0x12) + 0xa8);
  if (('\x01' < *(char *)(iVar4 + 0x18)) || (*(short *)(iVar4 + 0x94) != *(short *)(param_1 + 0x94))
     ) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 800c790c  FUN_800c790c ====

void FUN_800c790c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800c7954  FUN_800c7954 ====

void FUN_800c7954(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if (*(char *)(*(int *)(param_9 + 0x8c) + (int)*(char *)(param_9 + 0x12) + 0xa8) != '\0') {
    iVar3 = 0;
    iVar2 = param_9;
    for (iVar1 = 0; iVar1 < *(char *)(param_9 + 0x13); iVar1 = iVar1 + 1) {
      zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar2 + 0xe0),(float *)(*(int *)(param_9 + 0x54) + iVar3),param_11,
                  param_12,param_13,param_14,param_15,param_16);
      param_1 = zz_00097b4_(*(int *)(iVar2 + 0xe0),0x44);
      iVar3 = iVar3 + 0x40;
      iVar2 = iVar2 + 4;
    }
  }
  return;
}



// ==== 800c79f8  FUN_800c79f8 ====

void FUN_800c79f8(int param_1)

{
  undefined *puVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  float afStack_68 [3];
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  undefined4 local_40;
  uint uStack_3c;
  
  iVar4 = *(int *)(param_1 + 0x8c);
  if (*(char *)(iVar4 + *(char *)(param_1 + 0x12) + 0xa8) != '\0') {
    gnt4_PSVECSubtract_bl((float *)(iVar4 + 0x20),(float *)(iVar4 + 0x2c),afStack_68);
    dVar8 = gnt4_PSVECMag_bl(afStack_68);
    dVar7 = (double)FLOAT_80438800;
    if (dVar7 <= dVar8) {
      gnt4_PSVECNormalize_bl(afStack_68,afStack_68);
    }
    iVar6 = 0;
    iVar5 = 0;
    iVar3 = 0;
    while( true ) {
      if (*(char *)(param_1 + 0x13) <= iVar3) break;
      pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
      puVar1 = (&PTR_DAT_803072cc)[*(char *)(param_1 + 0x11) * 2];
      if ((*(char *)(iVar4 + 0x83) == '\0') && (-1 < (char)puVar1[iVar6 + 1])) {
        gnt4_PSMTXCopy_bl((float *)(iVar4 + (char)puVar1[iVar6 + 1] * 0x30 + 0x8d4),pfVar2);
      }
      else {
        gnt4_PSMTXCopy_bl((float *)(iVar4 + 0x114),pfVar2);
      }
      zz_00455fc_(pfVar2,pfVar2,(float *)(puVar1 + iVar6 + 8));
      zz_00457d4_('x',pfVar2,pfVar2,*(short *)(puVar1 + iVar6 + 4));
      zz_00457d4_('z',pfVar2,pfVar2,*(short *)(puVar1 + iVar6 + 6));
      if (*(short *)(puVar1 + iVar6 + 2) != 0) {
        local_5c = pfVar2[1];
        local_58 = pfVar2[5];
        local_54 = pfVar2[9];
        gnt4_PSVECNormalize_bl(&local_5c,&local_5c);
        if (dVar7 <= dVar8) {
          local_40 = 0x43300000;
          uStack_3c = (int)*(short *)(puVar1 + iVar6 + 2) ^ 0x80000000;
          FUN_80045460((double)((FLOAT_80438804 *
                                (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80438818)) /
                               FLOAT_80438808),&local_5c,afStack_68);
        }
        if (*(char *)(param_1 + 0xa9) == '\0') {
          local_50 = local_5c;
          local_4c = local_58;
          local_48 = local_54;
        }
        else {
          local_50 = pfVar2[0xc];
          local_4c = pfVar2[0xd];
          local_48 = pfVar2[0xe];
          FUN_80045460((double)FLOAT_8043880c,&local_50,&local_5c);
        }
        local_40 = 0x43300000;
        uStack_3c = (int)*(short *)(puVar1 + iVar6 + 2) ^ 0x80000000;
        FUN_80045bc8((double)(FLOAT_80438810 *
                             (float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80438818)),
                     pfVar2,&local_50,2);
      }
      gnt4_PSQUATScale_bl((double)*(float *)(puVar1 + iVar6 + 0x14),
                          (float *)(((uint)(*(short *)(param_1 + 0x1c) + iVar3) >> 1 & 1) * 0xc +
                                   -0x7fcf8aa0),&local_5c);
      zz_00456a0_(pfVar2,pfVar2,&local_5c);
      iVar6 = iVar6 + 0x18;
      iVar5 = iVar5 + 0x40;
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



// ==== 800c7d80  FUN_800c7d80 ====

void FUN_800c7d80(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80438828) * FLOAT_80438820);
  }
  return;
}



// ==== 800c7de4  FUN_800c7de4 ====

void FUN_800c7de4(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_80307fd0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800c7e24  FUN_800c7e24 ====

void FUN_800c7e24(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x700) {
    zz_001ab6c_(param_1,6);
  }
  else if (*(short *)(param_1 + 1000) == 0x709) {
    zz_001ab6c_(param_1,0x50);
  }
  return;
}



// ==== 800c7e70  FUN_800c7e70 ====

void FUN_800c7e70(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x700) {
    zz_001ab6c_(param_1,5);
  }
  else if (*(short *)(param_1 + 1000) == 0x709) {
    zz_001ab6c_(param_1,0x4f);
  }
  return;
}



// ==== 800c7ebc  FUN_800c7ebc ====

void FUN_800c7ebc(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x700) {
    zz_001ab6c_(param_1,6);
    zz_001ab6c_(param_1,5);
  }
  else if (*(short *)(param_1 + 1000) == 0x709) {
    zz_001ab6c_(param_1,0x50);
    zz_001ab6c_(param_1,0x4f);
  }
  return;
}



// ==== 800c7f38  FUN_800c7f38 ====

uint FUN_800c7f38(int param_1)

{
  uint uVar1;
  bool bVar2;
  
  uVar1 = zz_006dbe0_(param_1,0,1,1);
  if (uVar1 != 0) {
    if (*(short *)(param_1 + 1000) == 0x700) {
      bVar2 = zz_00fbc64_(param_1,0);
      uVar1 = (uint)bVar2;
    }
    else if (*(short *)(param_1 + 1000) == 0x709) {
      bVar2 = zz_00fbc64_(param_1,5);
      uVar1 = (uint)bVar2;
    }
  }
  return uVar1;
}



// ==== 800c7fac  FUN_800c7fac ====

void FUN_800c7fac(int param_1)

{
  (*(code *)(&PTR_FUN_80307fec)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800c7fe8  FUN_800c7fe8 ====

void FUN_800c7fe8(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80438828) * FLOAT_80438820);
  (*(code *)(&PTR_FUN_80307ff8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800c805c  FUN_800c805c ====

void FUN_800c805c(int param_1)

{
  zz_0148d74_(param_1);
  return;
}



// ==== 800c8084  FUN_800c8084 ====

void FUN_800c8084(int param_1)

{
  zz_0149178_(param_1);
  return;
}



// ==== 800c80ac  FUN_800c80ac ====

void FUN_800c80ac(int param_1)

{
  zz_0148d74_(param_1);
  return;
}



// ==== 800c80d4  FUN_800c80d4 ====

void FUN_800c80d4(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8030804c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800c8124  FUN_800c8124 ====

void FUN_800c8124(int param_1)

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
  *(float *)(param_1 + 0x558) = FLOAT_80438830;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_80438834,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}



// ==== 800c81e0  FUN_800c81e0 ====

void FUN_800c81e0(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_80438838;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar1 = FLOAT_8043883c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_80438840;
    fVar2 = FLOAT_80438838;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x760))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_8043883c;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 800c82d4  FUN_800c82d4 ====

void FUN_800c82d4(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_80438844,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_80438838;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_80438840,param_1), uVar3 != 0)) {
    dVar4 = (double)FLOAT_80438834;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,7,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800c8388  FUN_800c8388 ====

void FUN_800c8388(int param_1)

{
  float fVar1;
  float fVar2;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_80438848,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_80438850;
  fVar1 = FLOAT_8043884c;
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x50) = fVar2;
  }
  return;
}



// ==== 800c8404  FUN_800c8404 ====

void FUN_800c8404(int param_1)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_80438844,param_1);
  FUN_80067310((double)FLOAT_80438854,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 != 0) {
    dVar2 = (double)FLOAT_80438834;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar2,param_1,0xf,3,8,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800c848c  FUN_800c848c ====

void FUN_800c848c(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_80438844,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800c84fc  FUN_800c84fc ====

void FUN_800c84fc(int param_1)

{
  (*(code *)(&PTR_FUN_80308064)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800c8538  FUN_800c8538 ====

void FUN_800c8538(int param_1)

{
  zz_0149708_(param_1);
  return;
}



// ==== 800c865c  FUN_800c865c ====

void FUN_800c865c(int param_1)

{
  zz_00c5ae4_(param_1);
  zz_00c5e84_(param_1);
  return;
}



// ==== 800c86e4  FUN_800c86e4 ====

void FUN_800c86e4(int param_1)

{
  (*(code *)(&PTR_FUN_80309bf0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800c8720  FUN_800c8720 ====

void FUN_800c8720(int param_1)

{
  (*(code *)(&PTR_FUN_80309bfc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800c875c  FUN_800c875c ====

void FUN_800c875c(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_80438860) * FLOAT_80438858);
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80309c10)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800c87e4  FUN_800c87e4 ====

void FUN_800c87e4(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  double dVar5;
  
  fVar3 = FLOAT_8043886c;
  fVar2 = FLOAT_80438868;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  *(float *)(param_1 + 0x44) = fVar3;
  *(float *)(param_1 + 0x4c) = fVar3;
  uVar4 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar4 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar5 = (double)FLOAT_80438870;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043886c;
  return;
}



// ==== 800c88cc  FUN_800c88cc ====

void FUN_800c88cc(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043886c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800c8930  FUN_800c8930 ====

void FUN_800c8930(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    dVar3 = (double)FLOAT_80438870;
    *(undefined1 *)(param_1 + 0x746) = 0;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    return;
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if ((*(char *)(param_1 + 0x1b03) == '\0') && (*(char *)(param_1 + 0x1d0f) != '\0')) {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    fVar2 = FLOAT_8043886c;
    *(float *)(param_1 + 0x44) =
         (FLOAT_80438874 * *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868)
         ) / FLOAT_80438878;
    if (fVar2 != *(float *)(param_1 + 0xb4)) {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) / *(float *)(param_1 + 0xb4);
    }
    zz_00b2190_(param_1,0);
  }
  zz_006ed8c_((double)FLOAT_8043887c,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (FLOAT_80438880 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800c8ac4  FUN_800c8ac4 ====

void FUN_800c8ac4(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80309c1c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800c8b14  FUN_800c8b14 ====

void FUN_800c8b14(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80438868;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  uVar3 = FUN_800668cc((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043887c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_80438870;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800c8c30  FUN_800c8c30 ====

void FUN_800c8c30(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80438858,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043886c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80438878;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  return;
}



// ==== 800c8cec  FUN_800c8cec ====

void FUN_800c8cec(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSQUATScale_bl((double)FLOAT_80438858,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043886c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80438884 * dVar3);
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80438884 * -dVar3);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}



// ==== 800c8dd0  FUN_800c8dd0 ====

void FUN_800c8dd0(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043887c,param_1);
  FUN_80067310((double)FLOAT_80438880,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438880 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800c8e94  FUN_800c8e94 ====

void FUN_800c8e94(int param_1)

{
  (*(code *)(&PTR_FUN_80309c2c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800c8ed0  FUN_800c8ed0 ====

void FUN_800c8ed0(int param_1)

{
  (*(code *)(&PTR_FUN_80309c40)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800c8f0c  FUN_800c8f0c ====

void FUN_800c8f0c(int param_1)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  double dVar5;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  fVar1 = FLOAT_8043886c;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_8043886c;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  }
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  zz_006d144_(param_1,0xc1);
  fVar2 = FLOAT_8043887c;
  fVar1 = FLOAT_8043886c;
  dVar5 = (double)FLOAT_80438880;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043887c;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x54e));
  zz_00679d0_(param_1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    uVar3 = 0xffffffff;
    uVar4 = 0xffffffff;
  }
  else {
    uVar3 = 10;
    uVar4 = 2;
  }
  zz_004beb8_((double)FLOAT_80438870,param_1,0xf,4,0,uVar3,uVar4);
  *(undefined1 *)(param_1 + 0x145) = *(undefined1 *)(param_1 + 0x144);
  return;
}



// ==== 800c9000  FUN_800c9000 ====

uint FUN_800c9000(int param_1)

{
  uint uVar1;
  int iVar2;
  bool bVar4;
  uint uVar3;
  char *pcVar5;
  
  pcVar5 = (char *)(param_1 + 0x144);
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  zz_006ed8c_((double)FLOAT_8043887c,param_1);
  FUN_80067310((double)FLOAT_80438880,param_1,*(short *)(param_1 + 0x54e));
  uVar1 = zz_00679d0_(param_1);
  uVar3 = uVar1;
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    if (*pcVar5 == '\0') {
      if (*(char *)(param_1 + 0x145) == '\0') {
        iVar2 = zz_006dbe0_(param_1,2,1,1);
        if (iVar2 == 0) {
          *pcVar5 = '\0';
          uVar3 = 0;
        }
        else {
          *(undefined1 *)(param_1 + 0x1cef) = 0;
          *pcVar5 = '\x01';
          bVar4 = zz_00c4704_(param_1,0,pcVar5);
          uVar3 = (uint)bVar4;
        }
        goto LAB_800c90d4;
      }
    }
    *(undefined1 *)(param_1 + 0x1cef) = 0;
  }
LAB_800c90d4:
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    if ((*(char *)(param_1 + 0x145) == '\x02') && (*pcVar5 == '\x02')) {
      *pcVar5 = '\x03';
    }
    if (uVar1 == 0) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_0066530_(param_1,0x2d);
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x54e);
      uVar3 = zz_006a5a4_(param_1);
    }
    else {
      uVar3 = (uint)*(byte *)(param_1 + 0x540);
      *(byte *)(param_1 + 0x540) = *(byte *)(param_1 + 0x540) + 1;
    }
  }
  return uVar3;
}



// ==== 800c9164  FUN_800c9164 ====

void FUN_800c9164(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800c92b8  FUN_800c92b8 ====

void FUN_800c92b8(int param_1)

{
  short sVar1;
  int iVar2;
  
  zz_00c74ec_(param_1,0x19);
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x600) {
    iVar2 = 0;
    do {
      zz_0185f6c_(param_1,(char)iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 4);
    *(undefined1 *)(param_1 + 0x4a8) = 1;
  }
  else if (sVar1 == 0x608) {
    iVar2 = 7;
    do {
      zz_0185f6c_(param_1,(char)iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 9);
    *(undefined1 *)(param_1 + 0x4a8) = 1;
  }
  else if (sVar1 == 0x616) {
    iVar2 = 0x12;
    do {
      zz_0185f6c_(param_1,(char)iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x16);
  }
  else if (sVar1 == 0x61c) {
    iVar2 = 0x16;
    do {
      zz_0185f6c_(param_1,(char)iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 0x18);
  }
  return;
}



