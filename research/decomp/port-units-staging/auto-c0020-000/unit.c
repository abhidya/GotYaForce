#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800c0b44(int param_1);
bool zz_00c0d0c_(int param_1,undefined1 param_2);
undefined4 zz_00c0d3c_(void);
void FUN_800c0e2c(int param_1);
void FUN_800c0e80(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9);
void FUN_800c0fb4(int param_1);
void FUN_800c1038(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void FUN_800c1058(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined *param_9,undefined4 param_10 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 1-58 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 62-100 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 104-110 ==== */
// ==== 800c0d3c  zz_00c0d3c_ ====

undefined4 zz_00c0d3c_(void)

{
  return 0;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 114-122 ==== */
// ==== 800c0e2c  FUN_800c0e2c ====

void FUN_800c0e2c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80302e58)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 126-180 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 184-210 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 214-222 ==== */
// ==== 800c1038  FUN_800c1038 ====

void FUN_800c1038(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 226-258 ==== */
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
