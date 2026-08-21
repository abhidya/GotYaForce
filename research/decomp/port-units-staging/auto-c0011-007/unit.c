#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_8007a010(int param_1);
void FUN_8007a068(int param_1);
void FUN_8007a0b4(int param_1);
void FUN_8007a1f8(double param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_8007a250(int param_1);
void FUN_8007a298(int param_1);
void FUN_8007a364(int param_1);
void FUN_8007a498(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1867-1878 ==== */
// ==== 8007a010  FUN_8007a010 ====

void FUN_8007a010(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = zz_006dee8_(param_1,1);
  *(char *)(param_1 + 0x543) = (char)uVar1;
  (*(code *)(&PTR_FUN_802d65ec)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1882-1896 ==== */
// ==== 8007a068  FUN_8007a068 ====

void FUN_8007a068(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_804378fc;
  dVar2 = (double)FLOAT_804378f0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_004beb8_(dVar2,param_1,1,2,3,0xffffffff,0xffffffff);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1900-1943 ==== */
// ==== 8007a0b4  FUN_8007a0b4 ====

void FUN_8007a0b4(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  iVar4 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar3 = FLOAT_804378e8;
  if (iVar4 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else if ((((0 < iVar4) ||
            (fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
            *(float *)(param_1 + 0x558) = fVar2, fVar2 <= fVar3)) &&
           (*(char *)(param_1 + 0x1cef) == '\x01')) && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
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
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1947-1965 ==== */
// ==== 8007a1f8  FUN_8007a1f8 ====

void FUN_8007a1f8(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = zz_004cd24_(param_9,1);
  if (iVar1 == 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1969-1977 ==== */
// ==== 8007a250  FUN_8007a250 ====

void FUN_8007a250(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_802d65f8)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1981-2003 ==== */
// ==== 8007a298  FUN_8007a298 ====

void FUN_8007a298(int param_1)

{
  float fVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar2 = (double)FLOAT_804378f8;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804378f0,param_1,1,2,3,0xffffffff,0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_804378f0,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x558) = FLOAT_804378fc;
  *(float *)(param_1 + 0x80c) = fVar1;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 2007-2044 ==== */
// ==== 8007a364  FUN_8007a364 ====

void FUN_8007a364(int param_1)

{
  short sVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 == 1) {
    zz_00b22f4_(param_1);
  }
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar2 = zz_006d0dc_(param_1,0x81,0);
  if ((((iVar2 != 0) || (*(float *)(param_1 + 0x558) <= FLOAT_804378e8)) &&
      (*(char *)(param_1 + 0x1cef) == '\x01')) && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 2048-2068 ==== */
// ==== 8007a498  FUN_8007a498 ====

void FUN_8007a498(int param_1)

{
  int iVar1;
  int iVar2;
  
  FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  iVar2 = zz_004cd24_(param_1,1);
  if ((iVar2 == 1) || (iVar1 == 1)) {
    if (iVar1 == 1) {
      *(float *)(param_1 + 0x694) = FLOAT_80437900 + *(float *)(param_1 + 0x1dc8);
    }
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}
