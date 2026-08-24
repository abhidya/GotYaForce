#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
uint FUN_800bd708(int param_1);
void FUN_800bd7e4(int param_1);
void zz_00bd918_(int param_1,undefined1 param_2);
void FUN_800bda24(int param_1);
void FUN_800bda78(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9);
void zz_00bdb80_(int param_1);
void FUN_800bdcfc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void FUN_800bdd1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2076-2106 ==== */
// ==== 800bd708  FUN_800bd708 ====

uint FUN_800bd708(int param_1)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  uVar1 = zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar2 = zz_006dbe0_(param_1,2,1,1);
    uVar1 = 0;
    if (iVar2 != 0) {
      zz_00f036c_(param_1,0xeb);
      iVar2 = 0;
      do {
        bVar3 = zz_00e058c_(param_1,1,(char)iVar2 + '\x04');
        uVar1 = (uint)bVar3;
        iVar2 = iVar2 + 1;
      } while (iVar2 < 6);
    }
  }
  return uVar1;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0019.c 2110-2148 ==== */
// ==== 800bd7e4  FUN_800bd7e4 ====

void FUN_800bd7e4(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80438534,param_1,*(short *)(param_1 + 0x54a));
  gnt4_PSQUATScale_bl((double)FLOAT_80438530,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                             DOUBLE_80438520) * FLOAT_80438518);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  fVar1 = FLOAT_8043852c;
  if (((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_1 + 0x1cee) == '\0')) {
    return;
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006a474_(param_1);
  }
  else {
    zz_006a5a4_(param_1);
  }
  *(float *)(param_1 + 0x694) = FLOAT_80438580 + *(float *)(param_1 + 0x1dc8);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2152-2187 ==== */
// ==== 800bd918  zz_00bd918_ ====

void zz_00bd918_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (*(short *)(param_1 + 1000) == 0x800) {
    puVar1 = zz_0088aa0_(param_1,2,0,0,2);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x13] = param_2;
      puVar1[0x83] = 0x18;
      *(code **)(puVar1 + 0xc) = FUN_800bda24;
      *(code **)(puVar1 + 0x10c) = FUN_800bdd1c;
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
    puVar1[0x144] = 3;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2191-2199 ==== */
// ==== 800bda24  FUN_800bda24 ====

void FUN_800bda24(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80301a00)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2203-2247 ==== */
// ==== 800bda78  FUN_800bda78 ====

void FUN_800bda78(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 extraout_r4;
  int iVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  fVar1 = FLOAT_80438588;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar4 = *(int *)(param_9 + 0x90);
  *(undefined *)(param_9 + 0x89) = (&DAT_80433af8)[*(char *)(param_9 + 0x13)];
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),
                      *(int *)(&DAT_80433afc + *(char *)(param_9 + 0x13) * 4),iVar4 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar4 + 0xc28;
  iVar2 = *(int *)(&DAT_80433afc + *(char *)(param_9 + 0x13) * 4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043858c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00bdb80_(param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2251-2319 ==== */
// ==== 800bdb80  zz_00bdb80_ ====

void zz_00bdb80_(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(*(int *)(param_1 + 0x90) + 0x6e8);
  if (cVar1 == '\x01') {
    if (*(char *)(param_1 + 0x144) != '\x01') {
      *(undefined1 *)(param_1 + 0x144) = 1;
      *(undefined1 *)(param_1 + 0x84) = 200;
      if (*(char *)(param_1 + 0x13) == '\0') {
        *(undefined2 *)(param_1 + 0x146) = 0x1000;
      }
      else {
        *(undefined2 *)(param_1 + 0x146) = 0xf000;
      }
    }
  }
  else if (cVar1 == '\0') {
    if (*(char *)(param_1 + 0x144) == '\x01') {
      *(undefined1 *)(param_1 + 0x144) = 2;
      *(undefined1 *)(param_1 + 0x84) = 200;
      if (*(char *)(param_1 + 0x13) == '\0') {
        *(undefined2 *)(param_1 + 0x146) = 0xfb00;
      }
      else {
        *(undefined2 *)(param_1 + 0x146) = 0x500;
      }
    }
    else if (*(char *)(param_1 + 0x144) == '\x03') {
      *(undefined1 *)(param_1 + 0x84) = 0xc0;
    }
  }
  if (*(char *)(param_1 + 0x144) != '\x01') {
    if (*(char *)(param_1 + 0x144) != '\x02') {
      return;
    }
    *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x146);
    if (*(char *)(param_1 + 0x13) == '\0') {
      if (-1 < *(short *)(param_1 + 0x74)) {
        return;
      }
      *(undefined2 *)(param_1 + 0x74) = 0;
      *(undefined1 *)(param_1 + 0x144) = 3;
      return;
    }
    if (*(short *)(param_1 + 0x74) < 1) {
      return;
    }
    *(undefined2 *)(param_1 + 0x74) = 0;
    *(undefined1 *)(param_1 + 0x144) = 3;
    return;
  }
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + *(short *)(param_1 + 0x146);
  if (*(char *)(param_1 + 0x13) != '\0') {
    if (-0x4001 < *(short *)(param_1 + 0x74)) {
      return;
    }
    *(undefined2 *)(param_1 + 0x74) = 0xc000;
    return;
  }
  if (*(short *)(param_1 + 0x74) < 0x4001) {
    return;
  }
  *(undefined2 *)(param_1 + 0x74) = 0x4000;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2323-2331 ==== */
// ==== 800bdcfc  FUN_800bdcfc ====

void FUN_800bdcfc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2335-2360 ==== */
// ==== 800bdd1c  FUN_800bdd1c ====

void FUN_800bdd1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') &&
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) != '\x04')) {
    iVar1 = 0;
    uVar2 = 1;
  }
  else {
    iVar1 = 1;
    uVar2 = 0x44;
  }
  iVar1 = *(int *)(param_9 + iVar1 * 4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,uVar2);
  return;
}
