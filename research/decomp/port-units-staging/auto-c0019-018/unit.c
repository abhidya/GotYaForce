#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800c0938(int param_1);
void FUN_800c095c(int param_1);
void FUN_800c0980(int param_1);
void FUN_800c09a4(int param_1);
void FUN_800c09e0(int param_1);
void FUN_800c0a2c(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4359-4366 ==== */
// ==== 800c0938  FUN_800c0938 ====

void FUN_800c0938(int param_1)

{
  zz_010bd10_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4370-4377 ==== */
// ==== 800c095c  FUN_800c095c ====

void FUN_800c095c(int param_1)

{
  zz_010c220_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4381-4388 ==== */
// ==== 800c0980  FUN_800c0980 ====

void FUN_800c0980(int param_1)

{
  zz_010c590_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4392-4399 ==== */
// ==== 800c09a4  FUN_800c09a4 ====

void FUN_800c09a4(int param_1)

{
  (*(code *)(&PTR_FUN_803029a8)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4403-4413 ==== */
// ==== 800c09e0  FUN_800c09e0 ====

void FUN_800c09e0(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80433b18)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4417-4451 ==== */
// ==== 800c0a2c  FUN_800c0a2c ====

void FUN_800c0a2c(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  zz_006d144_(param_1,0xc0);
  if ((*(short *)(param_1 + 1000) == 0x30b) && ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  fVar1 = FLOAT_80438618;
  *(float *)(param_1 + 0x50) = FLOAT_80438618;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043861c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_80438620,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),8,1);
  return;
}
