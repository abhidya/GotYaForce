#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01b9f0c_(int param_1);
undefined4 zz_01b9f8c_(int param_1);
void FUN_801ba134(int param_1);
void FUN_801ba1b0(int param_1);
void FUN_801ba23c(undefined4 param_1,char param_2,char param_3);
void FUN_801ba27c(int param_1);
void FUN_801ba33c(int param_1);
void FUN_801ba378(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3610-3631 ==== */
// ==== 801b9f0c  zz_01b9f0c_ ====

void zz_01b9f0c_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043ba60;
  fVar1 = FLOAT_8043ba5c;
  *(undefined1 *)(param_1 + 0x19) = 2;
  *(undefined2 *)(param_1 + 0x1c) = 0x4b0;
  *(float *)(param_1 + 0x40) = fVar1;
  *(float *)(param_1 + 0x3c) = fVar1;
  *(float *)(param_1 + 0x38) = fVar1;
  *(float *)(param_1 + 0x50) =
       fVar2 * *(float *)(&DAT_8038246c + (*(byte *)(param_1 + 0x11) & 0x7f) * 0x48);
  *(undefined4 *)(param_1 + 200) = 0;
  *(undefined2 *)(param_1 + 0x272) = 1;
  zz_0019550_(param_1,(undefined4 *)(param_1 + 0x20),0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3635-3656 ==== */
// ==== 801b9f8c  zz_01b9f8c_ ====

undefined4 zz_01b9f8c_(int param_1)

{
  float fVar1;
  double dVar2;
  
  if (*(float *)(param_1 + 0x3c) <= FLOAT_8043ba5c) {
    if (*(char *)(param_1 + 0x1db) != '\0') {
      return 0x81cd;
    }
    dVar2 = FUN_8003d964((double)(FLOAT_8043baa8 * *(float *)(param_1 + 0xb4)),param_1,
                         (float *)(param_1 + 0x20));
    fVar1 = (float)((double)FLOAT_8043baa8 * (double)*(float *)(param_1 + 0xb4) + dVar2);
    if (*(float *)(param_1 + 0x24) < fVar1) {
      *(float *)(param_1 + 0x24) = fVar1;
      return 0x8444;
    }
  }
  return 0;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3660-3677 ==== */
// ==== 801ba134  FUN_801ba134 ====

void FUN_801ba134(int param_1)

{
  *(undefined1 *)(param_1 + 0x6e8) = 3;
  if (*(short *)(param_1 + 1000) == 0x307) {
    zz_013358c_(param_1,2);
    zz_00c74ec_(param_1,6);
  }
  else if (*(short *)(param_1 + 1000) == 0x30d) {
    zz_013358c_(param_1,3);
    zz_00c74ec_(param_1,7);
  }
  *(undefined1 *)(param_1 + 0x147) = 1;
  *(undefined1 *)(param_1 + 0x6f6) = 1;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3681-3695 ==== */
// ==== 801ba1b0  FUN_801ba1b0 ====

void FUN_801ba1b0(int param_1)

{
  zz_010a4ac_(param_1);
  *(undefined1 *)(param_1 + 0x748) = 2;
  if (*(char *)(param_1 + 0x147) == '\x01') {
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xfd;
  }
  else {
    *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 2;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3699-3706 ==== */
// ==== 801ba23c  FUN_801ba23c ====

void FUN_801ba23c(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_803826c8)[param_2])(param_1,(int)param_3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3710-3729 ==== */
// ==== 801ba27c  FUN_801ba27c ====

void FUN_801ba27c(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,2,1,1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x147) == '\x01')) {
    *(undefined1 *)(param_1 + 0x147) = 0;
    if (*(short *)(param_1 + 1000) == 0x307) {
      zz_01d2ffc_(param_1,0);
    }
    else if (*(short *)(param_1 + 1000) == 0x30d) {
      zz_01d2ffc_(param_1,1);
    }
    zz_00f036c_(param_1,0xdb);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3733-3740 ==== */
// ==== 801ba33c  FUN_801ba33c ====

void FUN_801ba33c(int param_1)

{
  (*(code *)(&PTR_FUN_803826d4)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3744-3752 ==== */
// ==== 801ba378  FUN_801ba378 ====

void FUN_801ba378(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_803826e4)[*(char *)(param_1 + 0x581)])();
  return;
}
