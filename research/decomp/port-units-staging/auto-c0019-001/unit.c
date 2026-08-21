#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800ba8c8(int param_1);
void FUN_800ba904(int param_1);
void FUN_800ba994(int param_1);
void FUN_800baa68(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_800bac30(int param_1);
void FUN_800bac78(int param_1);
void FUN_800bad4c(int param_1);
void FUN_800bae3c(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 195-202 ==== */
// ==== 800ba8c8  FUN_800ba8c8 ====

void FUN_800ba8c8(int param_1)

{
  (*(code *)(&PTR_FUN_803003d4)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 206-230 ==== */
// ==== 800ba904  FUN_800ba904 ====

void FUN_800ba904(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 6;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = *(uint *)(param_1 + 0x5e0);
  if ((uVar1 & 0x80) != 0) {
    iVar2 = 9;
  }
  if ((uVar1 & 0x10) != 0) {
    iVar2 = 3;
  }
  if ((uVar1 & 0x20) != 0) {
    iVar2 = 0;
  }
  zz_004beb8_((double)FLOAT_804384f8,param_1,1,2,iVar2 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  FUN_800bae3c(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 234-266 ==== */
// ==== 800ba994  FUN_800ba994 ====

void FUN_800ba994(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_804384fc;
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
      FUN_800bae68(param_1);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 270-338 ==== */
// ==== 800baa68  FUN_800baa68 ====

void FUN_800baa68(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  if (*(float *)(param_9 + 0x55c) <= FLOAT_804384fc) {
    zz_004cd24_(param_9,1);
  }
  else {
    *(float *)(param_9 + 0x55c) = *(float *)(param_9 + 0x55c) - *(float *)(param_9 + 0x1dc8);
  }
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_804384fc) {
    if ((*(uint *)(param_9 + 0x5d4) & 0x20) != 0) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if ((iVar1 != 0) && ('\0' < *(char *)(param_9 + 0x6ef))) {
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        uVar2 = *(uint *)(param_9 + 0x5e0);
        if (((uVar2 & 0x40) != 0) || (*(char *)(param_9 + 0x5e4) == '\x04')) {
          iVar1 = 7;
          *(undefined1 *)(param_9 + 0x581) = 3;
          if ((*(uint *)(param_9 + 0x5e0) & 0x80) != 0) {
            iVar1 = 10;
          }
          zz_004beb8_((double)FLOAT_804384f8,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x10) != 0) {
          dVar3 = (double)FLOAT_804384f8;
          *(undefined1 *)(param_9 + 0x581) = 1;
          zz_004beb8_(dVar3,param_9,1,2,4,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x20) != 0) {
          dVar3 = (double)FLOAT_804384f8;
          *(undefined1 *)(param_9 + 0x581) = 2;
          zz_004beb8_(dVar3,param_9,1,2,1,0xffffffff,0xffffffff);
          return;
        }
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      goto LAB_800babfc;
    }
    *(float *)(param_9 + 0x55c) = FLOAT_804384fc;
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_800babfc:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 342-350 ==== */
// ==== 800bac30  FUN_800bac30 ====

void FUN_800bac30(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_803003e0)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 354-375 ==== */
// ==== 800bac78  FUN_800bac78 ====

void FUN_800bac78(int param_1)

{
  double dVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_80438508;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_804384f8,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
              0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\x16')) {
    zz_004beb8_((double)FLOAT_804384f8,param_1,2,0,0x16,0xffffffff,0xffffffff);
  }
  FUN_800bae3c(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_804384fc;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 379-413 ==== */
// ==== 800bad4c  FUN_800bad4c ====

/* WARNING: Removing unreachable block (ram,0x800bae20) */
/* WARNING: Removing unreachable block (ram,0x800bad5c) */

void FUN_800bad4c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_804384fc;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  FUN_80067310((double)FLOAT_80438508,param_1,*(short *)(param_1 + 0x5ae));
  zz_00679d0_(param_1);
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  fVar2 = FLOAT_804384fc;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800bae68(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 417-435 ==== */
// ==== 800bae3c  FUN_800bae3c ====

void FUN_800bae3c(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80438510;
  fVar1 = FLOAT_8043850c;
  *(float *)(param_1 + 0x560) = FLOAT_8043850c;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  if (*(char *)(param_1 + 0x6ee) != '\0') {
    return;
  }
  *(undefined1 *)(param_1 + 0x6ef) = 100;
  return;
}
