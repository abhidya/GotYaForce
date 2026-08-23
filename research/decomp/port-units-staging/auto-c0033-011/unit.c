#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_0125550_(int param_1);
void FUN_801256ac(int param_1);
void FUN_80125880(int param_1);
void FUN_80125968(int param_1);
void FUN_80125b48(int param_1);
void FUN_80125bcc(int param_1);
void FUN_80125c58(undefined4 param_1,char param_2,char param_3);
void FUN_80125c98(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2808-2853 ==== */
// ==== 80125550  zz_0125550_ ====

void zz_0125550_(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d0dc_(param_1,0xc1,0);
  gnt4_PSQUATScale_bl((double)FLOAT_80439ba4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_006ed8c_((double)FLOAT_80439b80,param_1);
  FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    fVar2 = FLOAT_80439c00;
    if (*(char *)(param_1 + 0x145) != '\0') {
      *(undefined1 *)(param_1 + 0x540) = 5;
      fVar1 = FLOAT_80439b98;
      *(float *)(param_1 + 0x558) = fVar2;
      dVar3 = (double)FLOAT_80439b94;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x44) = fVar1;
      *(float *)(param_1 + 0x48) = fVar1;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      zz_004beb8_(dVar3,param_1,0xf,0,0xd,0x14,1);
      return;
    }
    zz_0046698_(param_1);
    *(undefined1 *)(param_1 + 0x145) = 1;
    if (*(short *)(param_1 + 1000) == 0x202) {
      *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 2;
      zz_01281d4_(param_1,0);
    }
    else if (*(short *)(param_1 + 1000) == 0x20b) {
      zz_01281d4_(param_1,1);
    }
  }
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2857-2908 ==== */
// ==== 801256ac  FUN_801256ac ====

void FUN_801256ac(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  zz_004cd24_(param_1,0xf);
  zz_006d0dc_(param_1,0xc1,0);
  FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar4 = FLOAT_80439c00;
  fVar3 = FLOAT_80439be8;
  fVar2 = FLOAT_80439b98;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    if ((*(short *)(param_1 + 1000) == 0x202) && (*(char *)(param_1 + 0x145) == '\x01')) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x55c) = fVar3;
      *(undefined1 *)(param_1 + 0x145) = 2;
      *(float *)(param_1 + 0x50) = fVar2;
      *(float *)(param_1 + 0x48) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(undefined2 *)(param_1 + 0x80) = 0;
      *(undefined2 *)(param_1 + 0x7e) = 0;
      *(undefined2 *)(param_1 + 0x7c) = 0;
      *(undefined1 *)(param_1 + 0x6f7) = 1;
      *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 2;
      zz_00f036c_(param_1,0xd8);
      cVar1 = *(char *)(param_1 + 0x6ea);
      dVar5 = (double)FLOAT_80439b94;
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar5,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
    }
    else {
      *(undefined1 *)(param_1 + 0x540) = 5;
      fVar2 = FLOAT_80439b98;
      *(float *)(param_1 + 0x558) = fVar4;
      dVar5 = (double)FLOAT_80439b94;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(float *)(param_1 + 0x44) = fVar2;
      *(float *)(param_1 + 0x48) = fVar2;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      zz_004beb8_(dVar5,param_1,0xf,0,0xd,0x14,1);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2912-2948 ==== */
// ==== 80125880  FUN_80125880 ====

void FUN_80125880(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_80439b98;
  *(undefined1 *)(param_1 + 0x145) = 0;
  if (*(float *)(param_1 + 0x55c) <= fVar2) {
    zz_004cd24_(param_1,0xf);
    FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  }
  else {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_80439b98;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439be4 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2952-2981 ==== */
// ==== 80125968  FUN_80125968 ====

void FUN_80125968(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_80439b98;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439be4 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2985-3001 ==== */
// ==== 80125b48  FUN_80125b48 ====

void FUN_80125b48(int param_1)

{
  zz_00c74ec_(param_1,0x1c);
  zz_004f1c4_(param_1);
  if (*(short *)(param_1 + 1000) == 0x604) {
    zz_012aa24_(param_1,0);
    zz_012aa24_(param_1,1);
  }
  else if (*(short *)(param_1 + 1000) == 0x618) {
    zz_012aa24_(param_1,6);
    zz_012aa24_(param_1,7);
  }
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0033.c 3005-3026 ==== */
// ==== 80125bcc  FUN_80125bcc ====

void FUN_80125bcc(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_80439c10;
  fVar1 = FLOAT_80439c08;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x191e) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x191e) ^ 0x80000000)) -
                             DOUBLE_80439c10) * FLOAT_80439c08);
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                             dVar2) * fVar1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 3030-3037 ==== */
// ==== 80125c58  FUN_80125c58 ====

void FUN_80125c58(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8032f408)[param_2])(param_1,(int)param_3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 3041-3054 ==== */
// ==== 80125c98  FUN_80125c98 ====

void FUN_80125c98(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x604) {
    zz_001ab6c_(param_1,0x2b);
  }
  else if (*(short *)(param_1 + 1000) == 0x618) {
    zz_001ab6c_(param_1,100);
  }
  return;
}
