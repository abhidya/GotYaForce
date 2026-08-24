#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800e58b4(int param_1);
void FUN_800e5920(int param_1);
void FUN_800e595c(int param_1);
void FUN_800e5980(int param_1);
void FUN_800e59a4(int param_1);
void FUN_800e59c8(int param_1);
void FUN_800e59ec(int param_1);
void zz_00e5a0c_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0024.c 4118-4131 ==== */
// ==== 800e58b4  FUN_800e58b4 ====

void FUN_800e58b4(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80438e80 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0024.c 4135-4142 ==== */
// ==== 800e5920  FUN_800e5920 ====

void FUN_800e5920(int param_1)

{
  (*(code *)(&PTR_FUN_803188c0)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0024.c 4146-4153 ==== */
// ==== 800e595c  FUN_800e595c ====

void FUN_800e595c(int param_1)

{
  zz_015809c_(param_1,0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0024.c 4157-4164 ==== */
// ==== 800e5980  FUN_800e5980 ====

void FUN_800e5980(int param_1)

{
  zz_0158688_(param_1,3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0024.c 4168-4175 ==== */
// ==== 800e59a4  FUN_800e59a4 ====

void FUN_800e59a4(int param_1)

{
  zz_0158688_(param_1,4);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0024.c 4179-4186 ==== */
// ==== 800e59c8  FUN_800e59c8 ====

void FUN_800e59c8(int param_1)

{
  zz_0158a94_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0024.c 4190-4197 ==== */
// ==== 800e59ec  FUN_800e59ec ====

void FUN_800e59ec(int param_1)

{
  zz_00e5a0c_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0024.c 4201-4211 ==== */
// ==== 800e5a0c  zz_00e5a0c_ ====

void zz_00e5a0c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_803188d4)[*(char *)(param_1 + 0x540)])();
  return;
}
