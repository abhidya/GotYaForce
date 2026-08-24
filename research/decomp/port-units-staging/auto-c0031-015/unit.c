#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80116c30(int param_1);
void FUN_80116d28(int param_1);
void FUN_80116dac(undefined4 param_1,char param_2,char param_3);
void FUN_80116dec(int param_1);
void FUN_80116e18(int param_1);
void FUN_80116e58(int param_1);
void FUN_80116ed0(int param_1);
void FUN_80116f0c(int param_1);

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0031.c 3506-3554 ==== */
// ==== 80116c30  FUN_80116c30 ====

void FUN_80116c30(int param_1)

{
  float fVar1;
  float fVar2;
  
  *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 1;
  *(undefined1 *)(param_1 + 0x748) = 2;
  if (*(short *)(param_1 + 0x6f6) < 1) {
    fVar1 = FLOAT_804397e8 * *(float *)(param_1 + 0x150);
    fVar2 = *(float *)(param_1 + 0x144);
    if (*(float *)(param_1 + 0x144) < fVar1) {
      fVar2 = fVar1;
    }
    *(float *)(param_1 + 0x874) = fVar2;
    *(float *)(param_1 + 0x85c) = fVar2;
    *(float *)(param_1 + 0x858) = fVar2;
    fVar2 = *(float *)(param_1 + 0x148);
    if (*(float *)(param_1 + 0x148) < fVar1) {
      fVar2 = fVar1;
    }
    *(float *)(param_1 + 0x878) = fVar2;
    fVar2 = *(float *)(param_1 + 0x14c);
    if (*(float *)(param_1 + 0x14c) < fVar1) {
      fVar2 = fVar1;
    }
    *(float *)(param_1 + 0x87c) = fVar2;
  }
  else {
    fVar1 = FLOAT_804397e0 +
            (float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x6f6) ^ 0x80000000)) -
                   DOUBLE_804397f0) / FLOAT_804397e4;
    fVar2 = *(float *)(param_1 + 0x144) * fVar1;
    *(float *)(param_1 + 0x874) = fVar2;
    *(float *)(param_1 + 0x85c) = fVar2;
    *(float *)(param_1 + 0x858) = fVar2;
    *(float *)(param_1 + 0x878) = *(float *)(param_1 + 0x148) * fVar1;
    *(float *)(param_1 + 0x87c) = *(float *)(param_1 + 0x14c) * fVar1;
  }
  if (*(short *)(param_1 + 0x6f6) < 1) {
    *(undefined4 *)(param_1 + 0x16cc) = *(undefined4 *)(param_1 + 0x150);
  }
  else {
    *(float *)(param_1 + 0x16cc) = FLOAT_804397ec;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0031.c 3558-3571 ==== */
// ==== 80116d28  FUN_80116d28 ====

void FUN_80116d28(int param_1)

{
  if (0 < *(short *)(param_1 + 0x6f6)) {
    zz_00f0104_(param_1,0x1a,3);
    *(short *)(param_1 + 0x6f6) = *(short *)(param_1 + 0x6f6) + -1;
    if ((*(short *)(param_1 + 0x6f6) == 0) && ((*(uint *)(param_1 + 0x5e0) & 3) != 0)) {
      *(undefined2 *)(param_1 + 0x6f6) = 1;
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0031.c 3575-3582 ==== */
// ==== 80116dac  FUN_80116dac ====

void FUN_80116dac(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8032a188)[param_2])(param_1,(int)param_3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0031.c 3586-3594 ==== */
// ==== 80116dec  FUN_80116dec ====

void FUN_80116dec(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x14);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0031.c 3598-3607 ==== */
// ==== 80116e18  FUN_80116e18 ====

void FUN_80116e18(int param_1)

{
  if (0 < *(short *)(param_1 + 0x6f6)) {
    zz_00f0214_(param_1,0x1a,3);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0031.c 3611-3623 ==== */
// ==== 80116e58  FUN_80116e58 ====

void FUN_80116e58(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_0082824_(param_1,0x25);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0031.c 3627-3634 ==== */
// ==== 80116ed0  FUN_80116ed0 ====

void FUN_80116ed0(int param_1)

{
  (*(code *)(&PTR_FUN_8032a1a4)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0031.c 3638-3645 ==== */
// ==== 80116f0c  FUN_80116f0c ====

void FUN_80116f0c(int param_1)

{
  (*(code *)(&PTR_FUN_8032a1b0)[*(char *)(param_1 + 0x581)])();
  return;
}
