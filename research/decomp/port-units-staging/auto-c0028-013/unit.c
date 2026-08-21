#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_0102274_(int param_1);
void FUN_80102464(int param_1);
void FUN_8010250c(int param_1);
void FUN_801025a4(int param_1);
void FUN_8010268c(int param_1);
void FUN_80102740(int param_1);
void FUN_80102800(int param_1);
void FUN_80102920(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 3700-3765 ==== */
// ==== 80102274  zz_0102274_ ====

void zz_0102274_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  double dVar6;
  float local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006ed8c_((double)FLOAT_80439370,param_1);
  FUN_80067310((double)FLOAT_80439354,param_1,*(short *)(param_1 + 0x54e));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439348;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar5 = zz_006d144_(param_1,0xc0), iVar5 != 0)) {
    fVar1 = FLOAT_80439358;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x48) = FLOAT_80439378;
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / fVar1;
    }
    else {
      iVar5 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
      local_1c = *(float *)(iVar5 + 0x8e0);
      local_18 = *(float *)(iVar5 + 0x8f0);
      local_14 = *(undefined4 *)(iVar5 + 0x900);
      local_28 = *(float *)(param_1 + 0x518);
      local_20 = *(undefined4 *)(param_1 + 0x520);
      local_24 = FLOAT_80439374 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
      gnt4_PSVECSubtract_bl(&local_28,&local_1c,&local_1c);
      fVar1 = FLOAT_80439348;
      *(float *)(param_1 + 0x48) = local_18 / FLOAT_80439358;
      local_18 = fVar1;
      dVar6 = gnt4_PSVECMag_bl(&local_1c);
      *(float *)(param_1 + 0x44) = (float)(dVar6 / (double)FLOAT_80439358);
    }
    fVar4 = FLOAT_80439388;
    fVar3 = FLOAT_80439364;
    fVar2 = FLOAT_80439358;
    fVar1 = FLOAT_80439348;
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * DOUBLE_80439380);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar3 * (-*(float *)(param_1 + 0x48) / fVar2);
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x44);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x50);
    if (fVar4 < *(float *)(param_1 + 0x764)) {
      zz_0092dcc_(param_1,0);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 3769-3794 ==== */
// ==== 80102464  FUN_80102464 ====

void FUN_80102464(int param_1)

{
  float fVar1;
  uint uVar2;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  uVar2 = FUN_80066838((double)FLOAT_8043938c,param_1);
  if (0 < (int)uVar2) {
    zz_006eddc_((double)FLOAT_80439338,param_1,(float *)(param_1 + 0x44));
  }
  FUN_80067310((double)FLOAT_80439354,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar1 = FLOAT_80439348;
  if (*(float *)(param_1 + 0x48) < FLOAT_80439348) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x50) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 3798-3823 ==== */
// ==== 8010250c  FUN_8010250c ====

void FUN_8010250c(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  uVar3 = FUN_80066838((double)FLOAT_8043938c,param_1);
  if (uVar3 == 0) {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  fVar2 = FLOAT_80439390;
  fVar1 = FLOAT_80439348;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    zz_00677b0_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 3827-3862 ==== */
// ==== 801025a4  FUN_801025a4 ====

void FUN_801025a4(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_004cd24_(param_1,0xf);
    dVar4 = (double)FLOAT_80439360;
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x1e00;
    zz_006eddc_(dVar4,param_1,(float *)(param_1 + 0x44));
    fVar2 = FLOAT_80439348;
    if (*(float *)(param_1 + 0x44) < FLOAT_80439348) {
      *(float *)(param_1 + 0x44) = FLOAT_80439348;
      *(float *)(param_1 + 0x4c) = fVar2;
    }
    FUN_80067310((double)FLOAT_80439354,param_1,*(short *)(param_1 + 0x5ae));
    iVar3 = zz_00677b0_(param_1);
    fVar2 = FLOAT_80439394;
    if (iVar3 != 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x558) = fVar2;
      zz_0066530_(param_1,0x2c);
      cVar1 = *(char *)(param_1 + 0x6ea);
      dVar4 = (double)FLOAT_8043934c;
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
      zz_00b2190_(param_1,2);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 3866-3896 ==== */
// ==== 8010268c  FUN_8010268c ====

void FUN_8010268c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  zz_004cd24_(param_1,0xf);
  fVar4 = FLOAT_80439358;
  fVar2 = FLOAT_8043934c;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_80439350;
    *(float *)(param_1 + 0x44) = fVar4;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x50) = fVar2;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
    zz_00677b0_(param_1);
    zz_0066530_(param_1,0x2d);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar5 = (double)FLOAT_8043934c;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 3900-3927 ==== */
// ==== 80102740  FUN_80102740 ====

void FUN_80102740(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(float *)(param_1 + 0x44) < FLOAT_80439348) {
    *(float *)(param_1 + 0x44) = FLOAT_80439348;
  }
  FUN_80067310((double)FLOAT_80439354,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439354 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 3931-3938 ==== */
// ==== 80102800  FUN_80102800 ====

void FUN_80102800(int param_1)

{
  zz_0148384_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 3942-3950 ==== */
// ==== 80102920  FUN_80102920 ====

void FUN_80102920(int param_1)

{
  zz_0096570_(param_1);
  zz_00c74ec_(param_1,2);
  return;
}
