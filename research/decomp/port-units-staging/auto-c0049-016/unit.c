#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01a0fa8_(int param_1);
void zz_01a10e8_(int param_1);
void zz_01a11fc_(void);
void zz_01a1204_(int param_1);
void zz_01a1220_(void);
void zz_01a1224_(void);
void zz_01a1228_(void);
void zz_01a122c_(void);

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0049.c 2810-2853 ==== */
// ==== 801a0fa8  zz_01a0fa8_ ====

void zz_01a0fa8_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043b57c;
  fVar1 = FLOAT_8043b54c;
  if ((*(byte *)(param_1 + 0x1d9) & 0x30) != 0) {
    *(float *)(param_1 + 0x44) = FLOAT_8043b54c;
    fVar3 = FLOAT_8043b580;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar3;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x5ae) + -0x8000;
  }
  zz_006ed8c_((double)FLOAT_8043b584,param_1);
  FUN_80067310((double)FLOAT_8043b56c,param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                             DOUBLE_8043b558) * FLOAT_8043b588);
  }
  iVar4 = zz_00677b0_(param_1);
  if ((iVar4 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043b56c + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 2857-2890 ==== */
// ==== 801a10e8  zz_01a10e8_ ====

void zz_01a10e8_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_zz_01a1290__803786a8;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_01a11fc__803786ac;
  *(undefined **)(param_1 + 0x4bc) = PTR_LAB_803786b0;
  *(undefined **)(param_1 + 0x4c0) = PTR_zz_01a1220__803786b4;
  *(undefined **)(param_1 + 0x4c4) = PTR_zz_01a1228__803786b8;
  *(undefined **)(param_1 + 0x4c8) = PTR_zz_01a122c__803786bc;
  *(undefined **)(param_1 + 0x4cc) = PTR_zz_01a1230__803786c0;
  *(undefined **)(param_1 + 0x4d0) = PTR_zz_01a1234__803786c4;
  *(undefined **)(param_1 + 0x4d4) = PTR_zz_01a1238__803786c8;
  *(undefined **)(param_1 + 0x4d8) = PTR_zz_01a123c__803786cc;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_803786d0;
  *(undefined **)(param_1 + 0x4e0) = PTR_zz_01a1224__803786d4;
  *(undefined **)(param_1 + 0x4e4) = PTR_FUN_803786d8;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_803786dc;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_803786e0;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_803786e4;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_803782b0;
  *(undefined **)(param_1 + 0x1d80) = &DAT_80378b80;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bc080;
  *(undefined **)(param_1 + 0x1d88) = &DAT_803787c0;
  *(undefined **)(param_1 + 0x1d8c) = &DAT_802bae60;
  *(undefined **)(param_1 + 0x27c) = &DAT_803785e8;
  if (*(short *)(param_1 + 1000) == 0x90b) {
    *(undefined **)(param_1 + 0x4b0) = &DAT_803783c8;
    return;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 2894-2900 ==== */
// ==== 801a11fc  zz_01a11fc_ ====

void zz_01a11fc_(void)

{
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 2904-2918 ==== */
// ==== 801a1204  zz_01a1204_ ====

void zz_01a1204_(int param_1)

{
  uint in_r0;
  
  if ((in_r0 & 1) != 0) {
    return;
  }
  *(undefined2 *)(param_1 + 0x1dfc) = 0;
  *(undefined1 *)(param_1 + 0x6ed) = 0;
  *(undefined1 *)(param_1 + 0x6ee) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 2922-2928 ==== */
// ==== 801a1220  zz_01a1220_ ====

void zz_01a1220_(void)

{
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 2932-2938 ==== */
// ==== 801a1224  zz_01a1224_ ====

void zz_01a1224_(void)

{
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 2942-2948 ==== */
// ==== 801a1228  zz_01a1228_ ====

void zz_01a1228_(void)

{
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 2952-2958 ==== */
// ==== 801a122c  zz_01a122c_ ====

void zz_01a122c_(void)

{
  return;
}
