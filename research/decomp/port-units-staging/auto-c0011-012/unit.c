#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_8007c4b8(int param_1);
void FUN_8007c6b0(int param_1);
void FUN_8007c7a4(int param_1);
void zz_007c800_(int param_1,uint param_2);
void zz_007c844_(int param_1);
void zz_007c9ac_(int param_1);
void FUN_8007cb58(int param_1);
void FUN_8007cba4(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 3276-3343 ==== */
// ==== 8007c4b8  FUN_8007c4b8 ====

void FUN_8007c4b8(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  bool bVar5;
  
  zz_004cd24_(param_1,0xf);
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x01') {
    if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\b')) {
      *(undefined1 *)(param_1 + 0x542) = 99;
      if (*(char *)(param_1 + 0x581) == '\0') {
        zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,4,4,0xffffffff,0xffffffff);
      }
      else {
        zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,4,4,0xffffffff,0xffffffff);
      }
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      zz_007c800_(param_1,0xc0);
      FUN_80067310((double)FLOAT_804378f8,param_1,*(short *)(param_1 + 0x5ae));
      fVar3 = FLOAT_804378fc;
      fVar2 = FLOAT_804378e8;
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\x06')) {
        if (*(char *)(param_1 + 0x1d9) < '\x01') {
          *(float *)(param_1 + 0x4c) = FLOAT_804378e8;
          *(float *)(param_1 + 0x44) = fVar2;
          *(undefined1 *)(param_1 + 0x542) = 2;
          *(float *)(param_1 + 0x558) = fVar3;
        }
        else {
          *(float *)(param_1 + 0x4c) = FLOAT_804378e8;
          *(float *)(param_1 + 0x44) = fVar2;
          *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
        }
      }
    }
  }
  else if ((cVar1 < '\x03') &&
          (fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
          bVar5 = fVar2 <= FLOAT_804378e8, *(float *)(param_1 + 0x558) = fVar2, bVar5)) {
    if (*(char *)(param_1 + 0x581) == '\0') {
      zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,4,4,0xffffffff,0xffffffff);
    }
    else {
      zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,4,4,0xffffffff,0xffffffff);
    }
    *(undefined1 *)(param_1 + 0x542) = 99;
  }
  iVar4 = zz_00677b0_(param_1);
  if (iVar4 == 0) {
    *(undefined1 *)(param_1 + 0x547) = 1;
  }
  else {
    *(undefined1 *)(param_1 + 0x547) = 0;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x540) = 8;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 3347-3382 ==== */
// ==== 8007c6b0  FUN_8007c6b0 ====

/* WARNING: Removing unreachable block (ram,0x8007c788) */
/* WARNING: Removing unreachable block (ram,0x8007c780) */
/* WARNING: Removing unreachable block (ram,0x8007c6c8) */
/* WARNING: Removing unreachable block (ram,0x8007c6c0) */

void FUN_8007c6b0(int param_1)

{
  int iVar1;
  double dVar2;
  double dVar3;
  
  *(undefined2 *)(param_1 + 0x18da) = 0;
  FUN_80067610(param_1);
  if (*(char *)(param_1 + 0x547) == '\x01') {
    iVar1 = FUN_800452a0((double)*(float *)(param_1 + 0x38),(double)*(float *)(param_1 + 0x40));
    dVar2 = (double)*(float *)(param_1 + 0x44);
    *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3c);
    dVar3 = DOUBLE_80437968;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    dVar3 = (double)(float)((double)CONCAT44(0x43300000,(int)(short)iVar1 ^ 0x80000000) - dVar3);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(short *)(param_1 + 0x5ae) = (short)(int)dVar3;
    *(float *)(param_1 + 0x44) = (float)dVar2;
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 3386-3403 ==== */
// ==== 8007c7a4  FUN_8007c7a4 ====

void FUN_8007c7a4(int param_1)

{
  *(undefined2 *)(param_1 + 0x18da) = 0;
  if (*(char *)(param_1 + 0x547) == '\x01') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 3407-3415 ==== */
// ==== 8007c800  zz_007c800_ ====

void zz_007c800_(int param_1,uint param_2)

{
  zz_006660c_(param_1);
  FUN_800669d0(param_1,param_2);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 3419-3469 ==== */
// ==== 8007c844  zz_007c844_ ====

void zz_007c844_(int param_1)

{
  float fVar1;
  double dVar2;
  double dVar3;
  float afStack_28 [3];
  float local_1c;
  float local_18;
  undefined4 local_14;
  double local_10;
  
  local_1c = *(float *)(param_1 + 0x38);
  local_18 = FLOAT_804378e8;
  local_14 = *(undefined4 *)(param_1 + 0x40);
  gnt4_PSVECNormalize_bl(&local_1c,&local_1c);
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),afStack_28);
  dVar3 = gnt4_PSQUATDotProduct_bl(&local_1c,afStack_28);
  dVar2 = (double)FLOAT_804378f8;
  if ((dVar3 <= dVar2) && (dVar2 = dVar3, dVar3 < (double)FLOAT_804378f0)) {
    dVar2 = (double)FLOAT_804378f0;
  }
  dVar3 = (double)gnt4_acos_bl(dVar2);
  dVar2 = DOUBLE_80437968;
  if (*(float *)(param_1 + 0x3c) <= FLOAT_804378e8) {
    fVar1 = FLOAT_80437974 * (float)dVar3;
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) + 0x222;
    local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x18da)) ^ 0x80000000);
    if (fVar1 < (float)(local_10 - dVar2)) {
      *(short *)(param_1 + 0x18da) = (short)(int)fVar1;
    }
    if (0x3c71 < *(short *)(param_1 + 0x18da)) {
      *(undefined2 *)(param_1 + 0x18da) = 0x3c71;
    }
  }
  else {
    fVar1 = FLOAT_80437974 * (float)dVar3;
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) + -0x222;
    fVar1 = -fVar1;
    local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x18da)) ^ 0x80000000);
    if ((float)(local_10 - dVar2) < fVar1) {
      *(short *)(param_1 + 0x18da) = (short)(int)fVar1;
    }
    if (*(short *)(param_1 + 0x18da) < -0x3c71) {
      *(undefined2 *)(param_1 + 0x18da) = 0xc38f;
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 3473-3504 ==== */
// ==== 8007c9ac  zz_007c9ac_ ====

void zz_007c9ac_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float *pfVar4;
  
  fVar2 = FLOAT_804378f0;
  fVar1 = FLOAT_804378e8;
  pfVar4 = (float *)(param_1 + 0x148);
  *(undefined1 *)(param_1 + 0x543) = 1;
  *(float *)(param_1 + 0x148) = fVar2 * *(float *)(param_1 + 0x38);
  *(float *)(param_1 + 0x14c) = fVar1;
  *(float *)(param_1 + 0x150) = fVar2 * *(float *)(param_1 + 0x40);
  gnt4_PSVECNormalize_bl(pfVar4,pfVar4);
  *(float *)(param_1 + 0x14c) = FLOAT_80437978;
  gnt4_PSVECNormalize_bl(pfVar4,pfVar4);
  fVar2 = FLOAT_804378f8;
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x38) = FLOAT_804378e8;
  fVar3 = FLOAT_8043797c;
  *(float *)(param_1 + 0x3c) = fVar2;
  fVar2 = FLOAT_80437980;
  *(float *)(param_1 + 0x40) = fVar1;
  *(float *)(param_1 + 0x44) = fVar3;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x694) = fVar2 + *(float *)(param_1 + 0x1dc8);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 3508-3517 ==== */
// ==== 8007cb58  FUN_8007cb58 ====

void FUN_8007cb58(int param_1)

{
  zz_004f1c4_(param_1);
  *(undefined2 *)(param_1 + 0x144) = 0;
  zz_00c74ec_(param_1,0x2e);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 3521-3551 ==== */
// ==== 8007cba4  FUN_8007cba4 ====

void FUN_8007cba4(int param_1)

{
  short sVar1;
  
  zz_006d520_(param_1,(float *)&DAT_802d6a48);
  if ((*(short *)(param_1 + 1000) == 0xc00) || (*(short *)(param_1 + 1000) == 0xc06)) {
    if (((*(uint *)(param_1 + 0x5e0) & 0x1000000) == 0) && (*(char *)(param_1 + 0x146) == '\0')) {
      sVar1 = *(short *)(param_1 + 0x144);
      if (sVar1 < -0x1400) {
        *(short *)(param_1 + 0x144) = sVar1 + 0xc0;
        if (-0x1401 < *(short *)(param_1 + 0x144)) {
          *(undefined2 *)(param_1 + 0x144) = 0xec00;
        }
      }
      else if ((-0x1400 < sVar1) &&
              (*(short *)(param_1 + 0x144) = sVar1 + -0xc0, *(short *)(param_1 + 0x144) < -0x13ff))
      {
        *(undefined2 *)(param_1 + 0x144) = 0xec00;
      }
    }
    *(undefined2 *)(param_1 + 0x18f2) = *(undefined2 *)(param_1 + 0x144);
    sVar1 = *(short *)(param_1 + 0x144);
    *(short *)(param_1 + 0x18ec) =
         (short)((ulonglong)((longlong)(int)sVar1 * 0x55555556) >> 0x20) -
         ((short)((short)((int)sVar1 / 0x30000) + (sVar1 >> 0xf)) >> 0xf);
  }
  return;
}
