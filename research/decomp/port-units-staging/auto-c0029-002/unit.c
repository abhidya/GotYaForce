#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_0104f20_(int param_1,float *param_2);
void zz_0104f8c_(int param_1,float *param_2);
void zz_0105144_(int param_1);
void zz_0105240_(int param_1);
void zz_010528c_(void);
void zz_0105290_(int param_1);
void zz_01052b8_(void);
void zz_01052bc_(void);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 512-520 ==== */
// ==== 80104f20  zz_0104f20_ ====

void zz_0104f20_(int param_1,float *param_2)

{
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)&DAT_80321720,param_2);
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)&DAT_8032172c,param_2 + 3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 524-566 ==== */
// ==== 80104f8c  zz_0104f8c_ ====

void zz_0104f8c_(int param_1,float *param_2)

{
  int iVar1;
  double dVar2;
  double dVar3;
  float afStack_28 [3];
  float local_1c;
  float local_18;
  float local_14;
  
  iVar1 = *(int *)(param_1 + 0x90);
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)&DAT_80321720,param_2);
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)&DAT_80321738,&local_1c);
  gnt4_PSVECSubtract_bl(&local_1c,param_2 + 3,afStack_28);
  dVar3 = gnt4_PSVECMag_bl(afStack_28);
  dVar2 = (double)(FLOAT_80439404 * *(float *)(iVar1 + 0xb4));
  if (dVar3 <= dVar2) {
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),(float *)&DAT_8032172c,&local_1c);
    gnt4_PSVECSubtract_bl(&local_1c,param_2 + 3,&local_1c);
    dVar2 = gnt4_PSVECMag_bl(&local_1c);
    gnt4_PSQUATScale_bl((double)((float)(dVar2 * dVar2) / FLOAT_80439408),&local_1c,param_2 + 9);
    gnt4_PSVECAdd_bl(param_2 + 6,param_2 + 9,param_2 + 6);
    gnt4_PSVECAdd_bl(param_2 + 6,param_2 + 3,param_2 + 3);
    gnt4_PSQUATScale_bl((double)FLOAT_8043940c,param_2 + 6,param_2 + 6);
  }
  else {
    gnt4_PSQUATScale_bl((double)(float)(dVar2 / dVar3),afStack_28,afStack_28);
    gnt4_PSVECAdd_bl(&local_1c,afStack_28,param_2 + 3);
  }
  gnt4_PSVECSubtract_bl(param_2 + 3,param_2,&local_1c);
  if (local_14 * local_14 + local_1c * local_1c + local_18 * local_18 <= FLOAT_804393f4) {
    local_1c = FLOAT_804393f4;
    local_18 = FLOAT_804393f4;
    local_14 = FLOAT_804393f0;
  }
  gnt4_PSVECNormalize_bl(&local_1c,&local_1c);
  gnt4_PSQUATScale_bl((double)(FLOAT_80439410 * *(float *)(iVar1 + 0xb4)),&local_1c,&local_1c);
  gnt4_PSVECAdd_bl(&local_1c,param_2,param_2 + 3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 570-599 ==== */
// ==== 80105144  zz_0105144_ ====

void zz_0105144_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_zz_01052c8__80321f38;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_0105240__80321f3c;
  *(undefined **)(param_1 + 0x4bc) = PTR_zz_010528c__80321f40;
  *(undefined **)(param_1 + 0x4c0) = PTR_zz_0105290__80321f44;
  *(undefined **)(param_1 + 0x4c4) = PTR_zz_01052b8__80321f48;
  *(undefined **)(param_1 + 0x4c8) = PTR_zz_01052bc__80321f4c;
  *(undefined **)(param_1 + 0x4cc) = PTR_zz_01052c0__80321f50;
  *(undefined **)(param_1 + 0x4d0) = PTR_zz_01052c4__80321f54;
  *(undefined4 *)(param_1 + 0x4d4) = DAT_80321f58;
  *(undefined4 *)(param_1 + 0x4d8) = DAT_80321f5c;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_80321f60;
  *(undefined4 *)(param_1 + 0x4e0) = DAT_80321f64;
  *(undefined **)(param_1 + 0x4e4) = PTR_FUN_80321f68;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_80321f6c;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_80321f70;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_80321f74;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_80321c88;
  *(undefined **)(param_1 + 0x1d80) = &DAT_80321920;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bcfa8;
  *(undefined **)(param_1 + 0x1d88) = &DAT_80321760;
  *(undefined **)(param_1 + 0x1d8c) = &DAT_802bbd94;
  *(undefined **)(param_1 + 0x27c) = &DAT_80321ef0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 603-613 ==== */
// ==== 80105240  zz_0105240_ ====

void zz_0105240_(int param_1)

{
  zz_004f1c4_(param_1);
  zz_0106494_(param_1);
  zz_00c74ec_(param_1,0x30);
  zz_00c74ec_(param_1,0x31);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 617-623 ==== */
// ==== 8010528c  zz_010528c_ ====

void zz_010528c_(void)

{
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 627-634 ==== */
// ==== 80105290  zz_0105290_ ====

void zz_0105290_(int param_1)

{
  zz_006d520_(param_1,(float *)&DAT_80321f78);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 638-644 ==== */
// ==== 801052b8  zz_01052b8_ ====

void zz_01052b8_(void)

{
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 648-654 ==== */
// ==== 801052bc  zz_01052bc_ ====

void zz_01052bc_(void)

{
  return;
}
