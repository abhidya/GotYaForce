#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01a346c_(int param_1);
void zz_01a35d4_(int param_1);
void zz_01a37f0_(int param_1);
void zz_01a39a4_(int param_1);
void zz_01a3a68_(int param_1);
void zz_01a3b0c_(int param_1);
void FUN_801a3d04(int param_1);
void FUN_801a3df8(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1090-1143 ==== */
// ==== 801a346c  zz_01a346c_ ====

void zz_01a346c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar1 = FLOAT_8043b594;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar3 = zz_01a3e54_(param_1,0xc0), iVar3 != 0)) {
    if ((*(int *)(param_1 + 0xcc) != 0) &&
       (*(char *)(param_1 + 0x88) != *(char *)(*(int *)(param_1 + 0xcc) + 0x88))) {
      *(undefined1 *)(param_1 + 0x541) = 1;
      *(undefined4 *)(param_1 + 0xcc) = 0;
    }
    FUN_80066958(param_1);
    fVar2 = FLOAT_8043b5a8;
    fVar1 = FLOAT_8043b590;
    if (*(char *)(param_1 + 0x544) == '\x01') {
      if (*(short *)(param_1 + 0x548) == 0) {
        if (*(char *)(param_1 + 0x581) == '\0') {
          *(undefined1 *)(param_1 + 0x73f) = 0;
          *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
          zz_006a474_(param_1);
          return;
        }
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        zz_006a5a4_(param_1);
        return;
      }
      *(undefined1 *)(param_1 + 0x540) = 5;
      fVar2 = FLOAT_8043b5cc;
      *(float *)(param_1 + 0x558) = fVar1;
      fVar1 = FLOAT_8043b594;
      *(float *)(param_1 + 0x44) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x48) = fVar1;
      *(float *)(param_1 + 0x50) = fVar1;
    }
    else {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x44) = fVar2;
      *(float *)(param_1 + 0x4c) = fVar2;
      *(undefined1 *)(param_1 + 0x144) = 1;
    }
    if (FLOAT_8043b5b4 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1147-1215 ==== */
// ==== 801a35d4  zz_01a35d4_ ====

void zz_01a35d4_(int param_1)

{
  float fVar1;
  
  if (*(char *)(param_1 + 0x144) == '\x01') {
    *(undefined1 *)(param_1 + 0x144) = 0;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x8dc);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x8ec);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x8fc);
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d9) < '\x01') {
    if (*(short *)(param_1 + 0x548) == 0) {
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\t')) {
        *(float *)(param_1 + 0x694) = FLOAT_8043b590 + *(float *)(param_1 + 0x1dc8);
        *(undefined1 *)(param_1 + 0x73f) = 0;
        *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
        zz_006a5a4_(param_1);
        return;
      }
    }
    else {
      zz_01a3e54_(param_1,0xc0);
      if ((*(char *)(param_1 + 0x541) == '\0') && (*(int *)(param_1 + 0xcc) != 0)) {
        FUN_8006c1c8((double)FLOAT_8043b5c0,param_1,(float *)(param_1 + 0x518));
        if (FLOAT_8043b5d8 <= *(float *)(param_1 + 0x760)) {
          *(float *)(param_1 + 0x4c) = FLOAT_8043b5a8;
        }
        else {
          *(float *)(param_1 + 0x4c) = FLOAT_8043b600;
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x541) = 1;
      }
      FUN_80067610(param_1);
      if ((*(float *)(param_1 + 0x4c) < FLOAT_8043b594) &&
         (*(float *)(param_1 + 0x44) < FLOAT_8043b5cc)) {
        *(float *)(param_1 + 0x44) = FLOAT_8043b5cc;
      }
      fVar1 = FLOAT_8043b590;
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\n')) {
        *(undefined1 *)(param_1 + 0x545) = 1;
        *(undefined1 *)(param_1 + 0x1cef) = 0;
        *(undefined1 *)(param_1 + 0x1cf0) = 0;
      }
      else if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar1;
        *(undefined1 *)(param_1 + 0x1cef) = 0;
        *(undefined1 *)(param_1 + 0x1cf0) = 0;
      }
    }
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 1;
    zz_01a4000_(param_1);
    zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,4,1,0xffffffff,0xffffffff);
  }
  if (*(char *)(param_1 + 0x545) == '\x01') {
    zz_00f0104_(param_1,0x1c,1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1219-1275 ==== */
// ==== 801a37f0  zz_01a37f0_ ====

void zz_01a37f0_(int param_1)

{
  float fVar1;
  double dVar2;
  float local_18;
  float local_14;
  undefined4 local_10;
  
  zz_00f0104_(param_1,0x1c,1);
  zz_01a3e54_(param_1,0xc0);
  if ((*(char *)(param_1 + 0x541) == '\0') && (*(int *)(param_1 + 0xcc) != 0)) {
    local_18 = *(float *)(param_1 + 0x518);
    local_14 = *(float *)(param_1 + 0x51c) - FLOAT_8043b5f8;
    local_10 = *(undefined4 *)(param_1 + 0x520);
    FUN_8006c1c8((double)FLOAT_8043b5c0,param_1,&local_18);
    if (FLOAT_8043b5d8 <= *(float *)(param_1 + 0x760)) {
      *(float *)(param_1 + 0x4c) = FLOAT_8043b5a8;
    }
    else {
      *(float *)(param_1 + 0x4c) = FLOAT_8043b600;
    }
    zz_01a3e98_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 1;
  }
  FUN_80067610(param_1);
  if (*(float *)(param_1 + 0x4c) < FLOAT_8043b594) {
    if (*(float *)(param_1 + 0x44) < FLOAT_8043b5cc) {
      *(float *)(param_1 + 0x44) = FLOAT_8043b5cc;
    }
  }
  zz_00677b0_(param_1);
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  fVar1 = FLOAT_8043b604;
  if (*(char *)(param_1 + 0x1d9) < '\x01') {
    if (*(float *)(param_1 + 0x558) <= FLOAT_8043b594) {
      dVar2 = (double)FLOAT_8043b598;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x542) = 0;
      *(undefined1 *)(param_1 + 0x543) = 0;
      *(float *)(param_1 + 0x4c) = fVar1;
      zz_004beb8_(dVar2,param_1,0xf,4,1,0xffffffff,0xffffffff);
    }
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x543) = 1;
    zz_01a4000_(param_1);
    zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,4,1,0xffffffff,0xffffffff);
  }
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0050.c 1279-1302 ==== */
// ==== 801a39a4  zz_01a39a4_ ====

void zz_01a39a4_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_004cd24_(param_1,0xf);
  if (iVar1 == 1) {
    *(undefined1 *)(param_1 + 0x540) = 7;
  }
  FUN_80067610(param_1);
  if (*(char *)(param_1 + 0x543) == '\x01') {
    *(float *)(param_1 + 0x38) = *(float *)(param_1 + 0x38) + *(float *)(param_1 + 0x148);
    *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) + *(float *)(param_1 + 0x14c);
    *(float *)(param_1 + 0x40) = *(float *)(param_1 + 0x40) + *(float *)(param_1 + 0x150);
  }
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000)) -
                           DOUBLE_8043b610) * FLOAT_8043b608);
  *(undefined1 *)(param_1 + 0x547) = 1;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1306-1326 ==== */
// ==== 801a3a68  zz_01a3a68_ ====

void zz_01a3a68_(int param_1)

{
  float fVar1;
  uint uVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_01a3e54_(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
  fVar1 = FLOAT_8043b594;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar2 = FUN_80066838((double)FLOAT_8043b618,param_1), 0 < (int)uVar2)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    zz_004cff4_(param_1,0xf);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1330-1397 ==== */
// ==== 801a3b0c  zz_01a3b0c_ ====

void zz_01a3b0c_(int param_1)

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
        zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,4,4,0xffffffff,0xffffffff);
      }
      else {
        zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,4,4,0xffffffff,0xffffffff);
      }
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      zz_01a3e54_(param_1,0xc0);
      FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
      fVar3 = FLOAT_8043b5a4;
      fVar2 = FLOAT_8043b594;
      if ((*(char *)(param_1 + 0x1cef) == '\x03') && (*(char *)(param_1 + 0x1cf0) == '\x06')) {
        if (*(char *)(param_1 + 0x1d9) < '\x01') {
          *(float *)(param_1 + 0x4c) = FLOAT_8043b594;
          *(float *)(param_1 + 0x44) = fVar2;
          *(undefined1 *)(param_1 + 0x542) = 2;
          *(float *)(param_1 + 0x558) = fVar3;
        }
        else {
          *(float *)(param_1 + 0x4c) = FLOAT_8043b594;
          *(float *)(param_1 + 0x44) = fVar2;
          *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
        }
      }
    }
  }
  else if ((cVar1 < '\x03') &&
          (fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
          bVar5 = fVar2 <= FLOAT_8043b594, *(float *)(param_1 + 0x558) = fVar2, bVar5)) {
    if (*(char *)(param_1 + 0x581) == '\0') {
      zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,4,4,0xffffffff,0xffffffff);
    }
    else {
      zz_004beb8_((double)FLOAT_8043b598,param_1,0xf,4,4,0xffffffff,0xffffffff);
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

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0050.c 1401-1436 ==== */
// ==== 801a3d04  FUN_801a3d04 ====

/* WARNING: Removing unreachable block (ram,0x801a3ddc) */
/* WARNING: Removing unreachable block (ram,0x801a3dd4) */
/* WARNING: Removing unreachable block (ram,0x801a3d1c) */
/* WARNING: Removing unreachable block (ram,0x801a3d14) */

void FUN_801a3d04(int param_1)

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
    dVar3 = DOUBLE_8043b610;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    dVar3 = (double)(float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,(int)(short)iVar1 ^ 0x80000000)) - dVar3);
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1440-1457 ==== */
// ==== 801a3df8  FUN_801a3df8 ====

void FUN_801a3df8(int param_1)

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
