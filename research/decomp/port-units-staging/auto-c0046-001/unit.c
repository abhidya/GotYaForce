#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80185618(int param_1);
void FUN_801856e8(int param_1);
void FUN_80185724(int param_1);
void FUN_80185784(int param_1);
void FUN_801857a8(int param_1);
void FUN_801857cc(int param_1);
void FUN_801857f0(int param_1);
void FUN_80185814(int param_1);

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0046.c 223-250 ==== */
// ==== 80185618  FUN_80185618 ====

void FUN_80185618(int param_1)

{
  float fVar1;
  double dVar2;
  
  *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 1;
  *(undefined1 *)(param_1 + 0x748) = 2;
  dVar2 = DOUBLE_8043af48;
  fVar1 = FLOAT_8043af40;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                             DOUBLE_8043af48) * FLOAT_8043af40);
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0046.c 254-261 ==== */
// ==== 801856e8  FUN_801856e8 ====

void FUN_801856e8(int param_1)

{
  (*(code *)(&PTR_FUN_8035d120)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0046.c 265-275 ==== */
// ==== 80185724  FUN_80185724 ====

void FUN_80185724(int param_1)

{
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8035d12c)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0046.c 279-286 ==== */
// ==== 80185784  FUN_80185784 ====

void FUN_80185784(int param_1)

{
  zz_00f2374_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0046.c 290-297 ==== */
// ==== 801857a8  FUN_801857a8 ====

void FUN_801857a8(int param_1)

{
  zz_00f2764_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0046.c 301-308 ==== */
// ==== 801857cc  FUN_801857cc ====

void FUN_801857cc(int param_1)

{
  zz_00f33f4_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0046.c 312-319 ==== */
// ==== 801857f0  FUN_801857f0 ====

void FUN_801857f0(int param_1)

{
  zz_00f3738_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0046.c 323-332 ==== */
// ==== 80185814  FUN_80185814 ====

void FUN_80185814(int param_1)

{
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  zz_00f41c4_(param_1);
  return;
}
