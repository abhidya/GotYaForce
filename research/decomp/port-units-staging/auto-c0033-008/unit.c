#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80124388(int param_1);
void FUN_80124484(int param_1);
void FUN_80124538(int param_1);
void FUN_801245c8(int param_1);
void FUN_80124630(int param_1);
void FUN_801246f4(int param_1);
void FUN_801247f4(int param_1);
void FUN_80124898(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2120-2153 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2157-2182 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2186-2204 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2208-2220 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2224-2244 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2248-2278 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2282-2306 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2310-2342 ==== */
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
