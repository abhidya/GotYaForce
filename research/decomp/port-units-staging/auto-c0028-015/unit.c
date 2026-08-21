#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80102ec0(int param_1);
void FUN_80102f50(int param_1);
void FUN_80103024(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_801031ec(int param_1);
void FUN_80103234(int param_1);
void FUN_80103308(int param_1);
void zz_01033f8_(int param_1);
void FUN_80103428(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4158-4182 ==== */
// ==== 80102ec0  FUN_80102ec0 ====

void FUN_80102ec0(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 6;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = *(uint *)(param_1 + 0x5e0);
  if ((uVar1 & 0x80) != 0) {
    iVar2 = 9;
  }
  if ((uVar1 & 0x10) != 0) {
    iVar2 = 3;
  }
  if ((uVar1 & 0x20) != 0) {
    iVar2 = 0;
  }
  zz_004beb8_((double)FLOAT_804393ac,param_1,1,2,iVar2 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  zz_01033f8_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4186-4218 ==== */
// ==== 80102f50  FUN_80102f50 ====

void FUN_80102f50(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_804393b0;
  if (iVar3 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else {
    if ((iVar3 < 1) &&
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
      return;
    }
    if (*(char *)(param_1 + 0x1cef) != '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      FUN_80103428(param_1);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4222-4290 ==== */
// ==== 80103024  FUN_80103024 ====

void FUN_80103024(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  if (*(float *)(param_9 + 0x55c) <= FLOAT_804393b0) {
    zz_004cd24_(param_9,1);
  }
  else {
    *(float *)(param_9 + 0x55c) = *(float *)(param_9 + 0x55c) - *(float *)(param_9 + 0x1dc8);
  }
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_804393b0) {
    if ((*(uint *)(param_9 + 0x5d4) & 0x20) != 0) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if ((iVar1 != 0) && ('\0' < *(char *)(param_9 + 0x6ef))) {
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        uVar2 = *(uint *)(param_9 + 0x5e0);
        if (((uVar2 & 0x40) != 0) || (*(char *)(param_9 + 0x5e4) == '\x04')) {
          iVar1 = 7;
          *(undefined1 *)(param_9 + 0x581) = 3;
          if ((*(uint *)(param_9 + 0x5e0) & 0x80) != 0) {
            iVar1 = 10;
          }
          zz_004beb8_((double)FLOAT_804393ac,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x10) != 0) {
          dVar3 = (double)FLOAT_804393ac;
          *(undefined1 *)(param_9 + 0x581) = 1;
          zz_004beb8_(dVar3,param_9,1,2,4,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x20) != 0) {
          dVar3 = (double)FLOAT_804393ac;
          *(undefined1 *)(param_9 + 0x581) = 2;
          zz_004beb8_(dVar3,param_9,1,2,1,0xffffffff,0xffffffff);
          return;
        }
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      goto LAB_801031b8;
    }
    *(float *)(param_9 + 0x55c) = FLOAT_804393b0;
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_801031b8:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4294-4302 ==== */
// ==== 801031ec  FUN_801031ec ====

void FUN_801031ec(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8032164c)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4306-4327 ==== */
// ==== 80103234  FUN_80103234 ====

void FUN_80103234(int param_1)

{
  double dVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_804393bc;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804393ac,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
              0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\x16')) {
    zz_004beb8_((double)FLOAT_804393ac,param_1,2,0,0x16,0xffffffff,0xffffffff);
  }
  zz_01033f8_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_804393b0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4331-4365 ==== */
// ==== 80103308  FUN_80103308 ====

/* WARNING: Removing unreachable block (ram,0x801033dc) */
/* WARNING: Removing unreachable block (ram,0x80103318) */

void FUN_80103308(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_804393b0;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  FUN_80067310((double)FLOAT_804393bc,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  fVar2 = FLOAT_804393b0;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_80103428(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4369-4387 ==== */
// ==== 801033f8  zz_01033f8_ ====

void zz_01033f8_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_804393c4;
  *(float *)(param_1 + 0x560) = FLOAT_804393c0;
  fVar1 = FLOAT_804393b0;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  if (*(char *)(param_1 + 0x6ee) != '\0') {
    return;
  }
  *(undefined1 *)(param_1 + 0x6ef) = 100;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4391-4449 ==== */
// ==== 80103428  FUN_80103428 ====

/* WARNING: Removing unreachable block (ram,0x8010358c) */
/* WARNING: Removing unreachable block (ram,0x80103438) */

void FUN_80103428(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_28;
  float local_24;
  undefined4 local_20;
  
  fVar2 = FLOAT_804393c4;
  *(float *)(param_1 + 0x560) = FLOAT_804393c0;
  fVar1 = FLOAT_804393b0;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  if ('\0' < *(char *)(param_1 + 0x6ef)) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    zz_0046698_(param_1);
    if (*(int *)(param_1 + 0xcc) != 0) {
      local_28 = *(float *)(param_1 + 0xa24);
      dVar5 = (double)*(float *)(param_1 + 0xa34);
      local_20 = *(undefined4 *)(param_1 + 0xa44);
      local_24 = FLOAT_804393b0;
      dVar6 = gnt4_PSVECMag_bl(&local_28);
      iVar3 = FUN_800452a0(dVar5,dVar6);
      local_28 = *(float *)(param_1 + 0xa30);
      local_24 = *(float *)(param_1 + 0xa40);
      local_20 = *(undefined4 *)(param_1 + 0xa50);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
      dVar6 = (double)local_24;
      local_24 = FLOAT_804393b0;
      dVar5 = gnt4_PSVECMag_bl(&local_28);
      iVar4 = FUN_800452a0(dVar6,dVar5);
      *(short *)(param_1 + 0x1900) = (short)iVar3 + (short)iVar4;
      zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + 0x19b2) * 0x30 + 0x8d4),
                  (float *)(param_1 + 0xa24),(short *)(param_1 + 0x18fe),
                  (undefined4 *)(param_1 + 0x1328),(float *)(param_1 + 0xf44),
                  (float *)(param_1 + 0x1628));
    }
    iVar3 = zz_006dbe0_(param_1,0,1,1);
    if (iVar3 != 0) {
      zz_00c3be0_(param_1,0xb);
      *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
    }
    if (*(short *)(param_1 + 0x774) < 1) {
      *(undefined1 *)(param_1 + 0x6ef) = 0;
    }
  }
  return;
}
