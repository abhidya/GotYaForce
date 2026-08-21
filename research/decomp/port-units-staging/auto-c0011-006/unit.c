#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80079ba8(int param_1);
void FUN_80079c3c(int param_1);
void FUN_80079d00(int param_1);
void zz_0079d54_(int param_1);
void FUN_80079de8(int param_1);
void FUN_80079e24(int param_1);
void FUN_80079e88(int param_1);
void FUN_80079fb4(double param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1678-1695 ==== */
// ==== 80079ba8  FUN_80079ba8 ====

void FUN_80079ba8(int param_1)

{
  int iVar1;
  
  if ((*(char *)(param_1 + 0x1cef) != '\x01') || (*(char *)(param_1 + 0x1cf0) != '\x03')) {
    zz_004cd24_(param_1,0xf);
  }
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = zz_006d0dc_(param_1,0xc1,0);
  if ((iVar1 != 1) && (FLOAT_804378e8 < *(float *)(param_1 + 0x558))) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1699-1727 ==== */
// ==== 80079c3c  FUN_80079c3c ====

void FUN_80079c3c(int param_1)

{
  short sVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x908) {
        zz_0082824_(param_1,99);
      }
      else if (sVar1 < 0x908) {
        if (sVar1 == 0x900) {
          zz_0082824_(param_1,0x18);
        }
      }
      else if (sVar1 == 0x90d) {
        zz_0082824_(param_1,100);
      }
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1731-1745 ==== */
// ==== 80079d00  FUN_80079d00 ====

void FUN_80079d00(int param_1)

{
  int iVar1;
  
  iVar1 = zz_004cd24_(param_1,0xf);
  if (iVar1 == 1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1749-1771 ==== */
// ==== 80079d54  zz_0079d54_ ====

void zz_0079d54_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_804378f4;
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_804378f4;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  if (*(float *)(param_1 + 0x44) < fVar1) {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x54a));
  zz_00679d0_(param_1);
  if ((*(char *)(param_1 + 0x581) == '\x03') && ('\0' < *(char *)(param_1 + 0x540))) {
    zz_00b22f4_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1775-1782 ==== */
// ==== 80079de8  FUN_80079de8 ====

void FUN_80079de8(int param_1)

{
  (*(code *)(&PTR_FUN_802d65e0)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1786-1799 ==== */
// ==== 80079e24  FUN_80079e24 ====

void FUN_80079e24(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804378fc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_006dee8_(param_1,1);
  zz_004beb8_((double)FLOAT_804378f0,param_1,1,2,3,0xffffffff,0xffffffff);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1803-1843 ==== */
// ==== 80079e88  FUN_80079e88 ====

void FUN_80079e88(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  iVar4 = zz_006dee8_(param_1,1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,1);
  }
  fVar3 = FLOAT_804378e8;
  if (iVar4 < 0) {
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else if ((((0 < iVar4) ||
            (fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
            *(float *)(param_1 + 0x558) = fVar2, fVar2 <= fVar3)) &&
           (*(char *)(param_1 + 0x1cef) == '\x01')) && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar4 = zz_006dbe0_(param_1,0,1,1);
    if (iVar4 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x908) {
        zz_0082824_(param_1,99);
      }
      else if (sVar1 < 0x908) {
        if (sVar1 == 0x900) {
          zz_0082824_(param_1,0x18);
        }
      }
      else if (sVar1 == 0x90d) {
        zz_0082824_(param_1,100);
      }
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1847-1863 ==== */
// ==== 80079fb4  FUN_80079fb4 ====

void FUN_80079fb4(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_004cd24_(param_9,1);
  if (*(char *)(param_9 + 0x1cee) != '\0') {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x14,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}
