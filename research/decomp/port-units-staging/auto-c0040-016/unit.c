#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_8015ae58(int param_1);
void FUN_8015af70(int param_1);
void FUN_8015b0b4(int param_1);
void FUN_8015b2ec(int param_1);
void FUN_8015b55c(int param_1);
void FUN_8015b5c0(int param_1);
void FUN_8015b6e8(char *param_1);
void FUN_8015b7a0(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0040.c 4179-4219 ==== */
// ==== 8015ae58  FUN_8015ae58 ====

void FUN_8015ae58(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_8043a74c;
  *(float *)(param_1 + 0x558) = FLOAT_8043a748;
  *(float *)(param_1 + 0x560) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 2;
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043a720;
  *(float *)(param_1 + 0x50) = FLOAT_8043a720;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a728,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043a72c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0040.c 4223-4261 ==== */
// ==== 8015af70  FUN_8015af70 ====

void FUN_8015af70(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                             DOUBLE_8043a740) * FLOAT_8043a730);
  }
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  if (*(float *)(param_1 + 0x760) < FLOAT_8043a750) {
    gnt4_PSQUATScale_bl((double)FLOAT_8043a754,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043a728,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc0,1);
  }
  fVar2 = FLOAT_8043a720;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6eb) = 4;
    *(undefined1 *)(param_1 + 0x6ec) = 0;
    *(undefined2 *)(param_1 + 0x54c) = 0;
    *(undefined2 *)(param_1 + 0x54e) = 0x14;
  }
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0040.c 4265-4333 ==== */
// ==== 8015b0b4  FUN_8015b0b4 ====

void FUN_8015b0b4(int param_1)

{
  uint uVar1;
  char cVar3;
  short sVar2;
  double dVar4;
  
  zz_00f0104_(param_1,0x17,2);
  if (FLOAT_8043a720 < *(float *)(param_1 + 0x558)) {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (*(short *)(param_1 + 1000) == 0x61e) {
      uVar1 = *(uint *)(param_1 + 0x5b4) & 0x400;
    }
    else {
      uVar1 = *(uint *)(param_1 + 0x5b4) & 0x200;
    }
    if ((uVar1 != 0) && (*(short *)(param_1 + 0x54c) < 2)) {
      *(undefined2 *)(param_1 + 0x54c) = 2;
    }
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                             DOUBLE_8043a740) * FLOAT_8043a730);
  }
  zz_004cd24_(param_1,0xf);
  if (('\0' < *(char *)(param_1 + 0x1d10)) &&
     (zz_006d144_(param_1,0xc0), (*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) {
    zz_006e1ac_(param_1,0xc0,1);
  }
  if (*(float *)(param_1 + 0x760) < FLOAT_8043a750) {
    gnt4_PSQUATScale_bl((double)FLOAT_8043a754,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  }
  gnt4_PSQUATScale_bl((double)FLOAT_8043a728,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    cVar3 = *(char *)(param_1 + 0x6eb) + -1;
    *(char *)(param_1 + 0x6eb) = cVar3;
    if (cVar3 < '\x01') {
      *(undefined1 *)(param_1 + 0x6eb) = 4;
      *(byte *)(param_1 + 0x6ec) = *(byte *)(param_1 + 0x6ec) ^ 1;
      sVar2 = *(short *)(param_1 + 1000);
      if (sVar2 == 0x610) {
        zz_0082824_(param_1,(int)*(char *)(param_1 + 0x6ec) + 0x36);
      }
      else if (sVar2 == 0x621) {
        zz_0082824_(param_1,(int)*(char *)(param_1 + 0x6ec) + 0x53);
      }
      else if (sVar2 == 0x623) {
        zz_0082824_(param_1,(int)*(char *)(param_1 + 0x6ec) + 0x55);
      }
    }
    sVar2 = *(short *)(param_1 + 0x54c) + -1;
    *(short *)(param_1 + 0x54c) = sVar2;
    if (sVar2 < 1) {
      dVar4 = (double)FLOAT_8043a72c;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      cVar3 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar3 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar3,0xffffffff,0xffffffff);
    }
  }
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0040.c 4337-4374 ==== */
// ==== 8015b2ec  FUN_8015b2ec ====

void FUN_8015b2ec(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                             DOUBLE_8043a740) * FLOAT_8043a730);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_8043a738,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a728,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar1 = zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      zz_006a750_(param_1,7);
    }
    *(float *)(param_1 + 0x694) = FLOAT_8043a724 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0040.c 4378-4393 ==== */
// ==== 8015b55c  FUN_8015b55c ====

void FUN_8015b55c(int param_1)

{
  int iVar1;
  
  zz_00c74ec_(param_1,0x22);
  zz_00c74ec_(param_1,0x23);
  zz_004f1c4_(param_1);
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 != 0) {
    zz_00b2190_(param_1,2);
  }
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0040.c 4397-4431 ==== */
// ==== 8015b5c0  FUN_8015b5c0 ====

void FUN_8015b5c0(int param_1)

{
  float fVar1;
  double dVar2;
  
  zz_006d520_(param_1,(float *)&DAT_80345bb8);
  dVar2 = DOUBLE_8043a760;
  fVar1 = FLOAT_8043a758;
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x1922) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1922) ^ 0x80000000)) -
                             DOUBLE_8043a760) * FLOAT_8043a758);
    *(short *)(param_1 + 0x1926) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1926) ^ 0x80000000)) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x1968) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1968) ^ 0x80000000)) -
                             dVar2) * fVar1);
    *(short *)(param_1 + 0x1974) =
         (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1974) ^ 0x80000000)) -
                             dVar2) * fVar1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0040.c 4435-4456 ==== */
// ==== 8015b6e8  FUN_8015b6e8 ====

void FUN_8015b6e8(char *param_1)

{
  if (*(short *)(param_1 + 1000) == 0x611) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0) {
      zz_00f036c_((int)param_1,0xb2);
      zz_006a8c0_(param_1,0x610);
      zz_005f00c_((int)param_1);
      zz_017a608_((int)param_1);
    }
  }
  else if ((*(short *)(param_1 + 1000) == 0x622) && ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0))
  {
    zz_00f036c_((int)param_1,0xb2);
    zz_006a8c0_(param_1,0x621);
    zz_005f00c_((int)param_1);
    zz_017a608_((int)param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0040.c 4460-4467 ==== */
// ==== 8015b7a0  FUN_8015b7a0 ====

void FUN_8015b7a0(int param_1)

{
  (*(code *)(&PTR_FUN_80345be8)[*(char *)(param_1 + 0x580)])();
  return;
}
