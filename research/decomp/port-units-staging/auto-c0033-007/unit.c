#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80123d70(int param_1);
void FUN_80123db8(int param_1);
void FUN_80123e20(int param_1);
void FUN_80123f08(int param_1);
void FUN_80123ff4(int param_1);
void FUN_801240a8(int param_1);
void FUN_80124250(int param_1);
void FUN_801242b8(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1897-1905 ==== */
// ==== 80123d70  FUN_80123d70 ====

void FUN_80123d70(int param_1)

{
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  (*(code *)(&PTR_FUN_8032e3a4)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1909-1921 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1925-1958 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1962-1993 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1997-2022 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2026-2074 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2078-2090 ==== */
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2094-2116 ==== */
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
