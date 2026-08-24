#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80074d3c(int param_1);
undefined4 FUN_80074de0(int param_1);
void FUN_80074e48(int param_1);
void FUN_80074ea8(int param_1);
void FUN_80074ecc(int param_1);
void FUN_80074ef0(int param_1);
void FUN_80074f14(int param_1);
void FUN_80074f38(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 1972-1991 ==== */
// ==== 80074d3c  FUN_80074d3c ====

void FUN_80074d3c(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    if (*(short *)(param_1 + 1000) == 0x400) {
      zz_007f29c_(param_1,*(undefined1 *)(param_1 + 0x148),0);
    }
    else if (*(short *)(param_1 + 1000) == 0x40a) {
      zz_007f29c_(param_1,*(char *)(param_1 + 0x148) + '\x04',1);
    }
    *(undefined1 *)(param_1 + *(char *)(param_1 + 0x148) + 0x144) = 1;
    *(char *)(param_1 + 0x148) = *(char *)(param_1 + 0x148) + '\x01';
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 1995-2007 ==== */
// ==== 80074de0  FUN_80074de0 ====

undefined4 FUN_80074de0(int param_1)

{
  int iVar1;
  
  if (((*(char *)(param_1 + 0x1cef) < '\0') && (iVar1 = zz_006dbe0_(param_1,0,1,0), iVar1 != 0)) &&
     ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0)) {
    return 0x8444;
  }
  return 0;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 2011-2021 ==== */
// ==== 80074e48  FUN_80074e48 ====

void FUN_80074e48(int param_1)

{
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_802d4ebc)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 2025-2032 ==== */
// ==== 80074ea8  FUN_80074ea8 ====

void FUN_80074ea8(int param_1)

{
  zz_00f2374_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 2036-2043 ==== */
// ==== 80074ecc  FUN_80074ecc ====

void FUN_80074ecc(int param_1)

{
  zz_00f2764_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 2047-2054 ==== */
// ==== 80074ef0  FUN_80074ef0 ====

void FUN_80074ef0(int param_1)

{
  zz_00f3028_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 2058-2065 ==== */
// ==== 80074f14  FUN_80074f14 ====

void FUN_80074f14(int param_1)

{
  zz_00f3738_(param_1);
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0010.c 2069-2089 ==== */
// ==== 80074f38  FUN_80074f38 ====

void FUN_80074f38(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80437800;
  fVar1 = FLOAT_804377f8;
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000)) -
                           DOUBLE_80437800) * FLOAT_804377f8);
  *(short *)(param_1 + 0x18e2) =
       (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e2) ^ 0x80000000)) - dVar2
                           ) * fVar1);
  zz_00f41c4_(param_1);
  return;
}
