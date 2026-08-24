#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_8014d57c(int param_1);
void FUN_8014d5b4(int param_1);
void FUN_8014d734(int param_1);
void FUN_8014d784(int param_1);
void FUN_8014d7b8(int param_1);
void FUN_8014d7d8(int param_1);
void FUN_8014d7f8(int param_1);
void FUN_8014d834(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 1-9 ==== */
// ==== 8014d57c  FUN_8014d57c ====

void FUN_8014d57c(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 13-41 ==== */
// ==== 8014d5b4  FUN_8014d5b4 ====

void FUN_8014d5b4(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbf3b8,3,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbf328,3,pfVar2 + 0xc,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbf298,2,pfVar2 + 0x15,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbf238,1,pfVar2 + 0x1b,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcbf208,1,pfVar2 + 0x1e,afStack_18);
    zz_00e5184_(param_1,-0x7fcbf3b8,3,pfVar2 + 3,pfVar2 + 0x3f);
    zz_00e5184_(param_1,-0x7fcbf328,3,pfVar2 + 0xc,pfVar2 + 0x48);
    zz_00e5184_(param_1,-0x7fcbf298,2,pfVar2 + 0x15,pfVar2 + 0x51);
    zz_00e5184_(param_1,-0x7fcbf238,1,pfVar2 + 0x1b,pfVar2 + 0x57);
    zz_00e5184_(param_1,-0x7fcbf208,1,pfVar2 + 0x1e,pfVar2 + 0x5a);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 45-53 ==== */
// ==== 8014d734  FUN_8014d734 ====

void FUN_8014d734(int param_1)

{
  FUN_8014d2fc(param_1);
  FUN_801eea8c(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 57-64 ==== */
// ==== 8014d784  FUN_8014d784 ====

void FUN_8014d784(int param_1)

{
  FUN_8014d3fc(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 68-75 ==== */
// ==== 8014d7b8  FUN_8014d7b8 ====

void FUN_8014d7b8(int param_1)

{
  FUN_8014d57c(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 79-86 ==== */
// ==== 8014d7d8  FUN_8014d7d8 ====

void FUN_8014d7d8(int param_1)

{
  FUN_8014d5b4(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 90-97 ==== */
// ==== 8014d7f8  FUN_8014d7f8 ====

void FUN_8014d7f8(int param_1)

{
  (*(code *)(&PTR_FUN_80340e28)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0039.c 101-109 ==== */
// ==== 8014d834  FUN_8014d834 ====

void FUN_8014d834(int param_1)

{
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  (*(code *)(&PTR_FUN_80340e34)[*(char *)(param_1 + 0x581)])();
  return;
}
