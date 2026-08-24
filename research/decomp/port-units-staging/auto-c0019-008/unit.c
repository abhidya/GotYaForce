#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800bcce8(int param_1);
void FUN_800bcd88(int param_1);
void FUN_800bce18(int param_1);
void FUN_800bcea0(int param_1);
void FUN_800bcf48(int param_1);
void FUN_800bd008(int param_1);
void FUN_800bd02c(int param_1);
void FUN_800bd050(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1654-1677 ==== */
// ==== 800bcce8  FUN_800bcce8 ====

void FUN_800bcce8(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_0046588_((double)(FLOAT_80438564 * *(float *)(param_1 + 0x1dc8)),(float *)(param_1 + 0x38),
              (float *)(param_1 + 0x20),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  uVar3 = FUN_80066838((double)FLOAT_80438568,param_1);
  fVar2 = FLOAT_8043852c;
  if (((int)uVar3 < 1) &&
     (fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
     *(float *)(param_1 + 0x558) = fVar1, fVar2 < fVar1)) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1681-1706 ==== */
// ==== 800bcd88  FUN_800bcd88 ====

void FUN_800bcd88(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  fVar2 = FLOAT_8043856c;
  fVar1 = FLOAT_8043852c;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_80438570;
    *(float *)(param_1 + 0x44) = fVar1;
    dVar4 = (double)FLOAT_80438540;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar3;
    zz_004beb8_(dVar4,param_1,0xf,3,6,0xffffffff,0xffffffff);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1710-1728 ==== */
// ==== 800bce18  FUN_800bce18 ====

void FUN_800bce18(int param_1)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80438534,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 != 0) {
    dVar2 = (double)FLOAT_80438540;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar2,param_1,0xf,3,7,0xffffffff,0xffffffff);
    zz_00b2190_(param_1,2);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1732-1759 ==== */
// ==== 800bcea0  FUN_800bcea0 ====

void FUN_800bcea0(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80438534,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar3 = FLOAT_80438574;
  fVar2 = FLOAT_80438540;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    dVar4 = (double)FLOAT_80438540;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar1 = FLOAT_80438538;
    *(float *)(param_1 + 0x44) = fVar3;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x50) = fVar2;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5ae) + -0x8000;
    zz_004beb8_(dVar4,param_1,0xf,3,8,0xffffffff,0xffffffff);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1763-1790 ==== */
// ==== 800bcf48  FUN_800bcf48 ====

void FUN_800bcf48(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(float *)(param_1 + 0x44) < FLOAT_8043852c) {
    *(float *)(param_1 + 0x44) = FLOAT_8043852c;
  }
  FUN_80067310((double)FLOAT_80438534,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438534 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1794-1801 ==== */
// ==== 800bd008  FUN_800bd008 ====

void FUN_800bd008(int param_1)

{
  zz_015809c_(param_1,0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1805-1812 ==== */
// ==== 800bd02c  FUN_800bd02c ====

void FUN_800bd02c(int param_1)

{
  zz_0158688_(param_1,3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1816-1823 ==== */
// ==== 800bd050  FUN_800bd050 ====

void FUN_800bd050(int param_1)

{
  zz_0158a94_(param_1);
  return;
}
