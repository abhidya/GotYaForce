#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_00747a4_(int param_1);
undefined4 zz_007486c_(int param_1,uint param_2);
void FUN_80074a3c(int param_1);
void FUN_80074ae8(int param_1);
void FUN_80074bcc(undefined4 param_1,char param_2,char param_3);
void FUN_80074c0c(int param_1,uint param_2);
void FUN_80074ccc(int param_1);
void FUN_80074d08(int param_1);

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0010.c 1750-1777 ==== */
// ==== 800747a4  zz_00747a4_ ====

void zz_00747a4_(int param_1)

{
  int iVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_804377d4;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                           DOUBLE_804377e0) * FLOAT_804377f4);
  FUN_80067310(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
  }
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0010.c 1781-1824 ==== */
// ==== 8007486c  zz_007486c_ ====

undefined4 zz_007486c_(int param_1,uint param_2)

{
  short sVar1;
  undefined4 uVar2;
  short sVar3;
  int iVar4;
  
  sVar1 = *(short *)(param_1 + 0x5aa);
  iVar4 = (int)sVar1;
  if (sVar1 < 0) {
    iVar4 = -iVar4;
  }
  sVar3 = (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                                (int)*(short *)(*(int *)(param_1 + 0x4ac) +
                                                                (param_2 & 0xf) * 2 + 0xac) ^
                                                0x80000000)) - DOUBLE_804377e0) *
                      *(float *)(param_1 + 0x1dc8));
  if (sVar3 < iVar4) {
    sVar1 = *(short *)(param_1 + 0x72) - sVar3;
    if ((param_2 & 0x40) != 0) {
      *(short *)(param_1 + 0x5ae) = sVar1;
    }
    if ((param_2 & 0x80) != 0) {
      *(short *)(param_1 + 0x72) = sVar1;
    }
    *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5aa) + sVar3;
    uVar2 = 0;
  }
  else {
    sVar1 = *(short *)(param_1 + 0x72) + sVar1;
    if ((param_2 & 0x40) != 0) {
      *(short *)(param_1 + 0x5ae) = sVar1;
    }
    if ((param_2 & 0x80) != 0) {
      *(short *)(param_1 + 0x72) = sVar1;
    }
    *(undefined2 *)(param_1 + 0x5aa) = 0;
    uVar2 = 1;
  }
  return uVar2;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 1828-1858 ==== */
// ==== 80074a3c  FUN_80074a3c ====

void FUN_80074a3c(int param_1)

{
  short sVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0x148) = 0;
  *(undefined1 *)(param_1 + 0x144) = 0;
  *(undefined1 *)(param_1 + 0x145) = 0;
  *(undefined1 *)(param_1 + 0x146) = 0;
  *(undefined1 *)(param_1 + 0x147) = 0;
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x40a) {
    iVar2 = 4;
    do {
      zz_00c0d0c_(param_1,(char)iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 8);
  }
  else if ((sVar1 < 0x40a) && (sVar1 == 0x400)) {
    iVar2 = 0;
    do {
      zz_00c0d0c_(param_1,(char)iVar2);
      iVar2 = iVar2 + 1;
    } while (iVar2 < 4);
  }
  zz_00c74ec_(param_1,10);
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0010.c 1862-1894 ==== */
// ==== 80074ae8  FUN_80074ae8 ====

void FUN_80074ae8(int param_1)

{
  float fVar1;
  double dVar2;
  
  if (*(short *)(param_1 + 0x78e) <= *(short *)(param_1 + 0x774)) {
    *(undefined1 *)(param_1 + 0x144) = 0;
    *(undefined1 *)(param_1 + 0x145) = 0;
    *(undefined1 *)(param_1 + 0x146) = 0;
    *(undefined1 *)(param_1 + 0x147) = 0;
    *(undefined1 *)(param_1 + 0x148) = 0;
  }
  dVar2 = DOUBLE_80437800;
  fVar1 = FLOAT_804377f8;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                             DOUBLE_80437800) * FLOAT_804377f8);
    *(short *)(param_1 + 0x18e0) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000)) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x18e2) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000)) -
                             dVar2) * fVar1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 1898-1905 ==== */
// ==== 80074bcc  FUN_80074bcc ====

void FUN_80074bcc(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_802d4e78)[param_2])(param_1,(int)param_3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 1909-1945 ==== */
// ==== 80074c0c  FUN_80074c0c ====

void FUN_80074c0c(int param_1,uint param_2)

{
  undefined2 *puVar1;
  int iVar2;
  undefined2 *puVar3;
  
  *(undefined1 *)(param_1 + 0xaf) = 1;
  puVar1 = &DAT_802d4e84;
  if (*(short *)(param_1 + 1000) == 0x40a) {
    puVar1 = &DAT_802d4e90;
  }
  else if (*(short *)(param_1 + 1000) != 0x400) {
    return;
  }
  if ((param_2 & 1) != 0) {
    iVar2 = 0;
    puVar3 = puVar1;
    do {
      zz_001ab6c_(param_1,(char)*puVar3);
      iVar2 = iVar2 + 1;
      puVar3 = puVar3 + 1;
    } while (iVar2 < 3);
  }
  if ((param_2 & 2) != 0) {
    iVar2 = 3;
    puVar1 = puVar1 + 3;
    do {
      zz_001ab6c_(param_1,(char)*puVar1);
      iVar2 = iVar2 + 1;
      puVar1 = puVar1 + 1;
    } while (iVar2 < 6);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 1949-1956 ==== */
// ==== 80074ccc  FUN_80074ccc ====

void FUN_80074ccc(int param_1)

{
  (*(code *)(&PTR_FUN_802d4e9c)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 1960-1968 ==== */
// ==== 80074d08  FUN_80074d08 ====

void FUN_80074d08(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_00f1e30_(param_1,&DAT_802d4ea8);
  return;
}
