#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801037f8(int param_1);
void FUN_8010398c(int param_1);
void FUN_80103aec(int param_1);
void FUN_80103b9c(int param_1);
void FUN_80103c10(int param_1);
void FUN_80103c60(int param_1);
void FUN_80103d88(int param_1);
void FUN_80103e7c(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4573-4621 ==== */
// ==== 801037f8  FUN_801037f8 ====

void FUN_801037f8(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  if (*(short *)(param_1 + 0x784) < 1) {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else if (*(char *)(param_1 + 0x541) == '\0') {
    *(undefined1 *)(param_1 + 0x541) = 1;
    zz_00107a0_(param_1,10);
  }
  FUN_80067310((double)FLOAT_804393bc,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if ((*(char *)(param_1 + 0x1cef) < '\x01') || (iVar3 = zz_006dbe0_(param_1,2,1,0), iVar3 != 0)) {
    if (*(char *)(param_1 + 0x1cee) == '\0') {
      return;
    }
    zz_00f036c_(param_1,0xc3);
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 != 0) {
      zz_00e19a8_(param_1,1,param_1 + 0x6f7);
      dVar4 = (double)FLOAT_804393ac;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x542) = 0;
      *(undefined1 *)(param_1 + 0x6f7) = 2;
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
      return;
    }
  }
  fVar2 = FLOAT_804393b0;
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  zz_006a5a4_(param_1);
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0028.c 4625-4670 ==== */
// ==== 8010398c  FUN_8010398c ====

void FUN_8010398c(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  *(undefined1 *)(param_1 + 0x6f7) = 2;
  uVar3 = zz_006de44_(param_1,0xf0f00);
  dVar4 = DOUBLE_804393a0;
  if (uVar3 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar3) {
      uVar3 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar3;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,uVar3 ^ 0x80000000)) - dVar4);
  }
  FUN_80067310((double)FLOAT_804393bc,param_1,*(short *)(param_1 + 0x5ae) + -0x8000);
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
    zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  }
  fVar2 = FLOAT_804393b0;
  if (*(float *)(param_1 + 0x560) <= FLOAT_804393b0) {
    dVar4 = (double)FLOAT_804393ac;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x6f7) = 0;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  else {
    *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4674-4700 ==== */
// ==== 80103aec  FUN_80103aec ====

void FUN_80103aec(int param_1)

{
  float fVar1;
  int iVar2;
  
  FUN_80067310((double)FLOAT_804393bc,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_804393b0;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    if (iVar2 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a750_(param_1,7);
      *(float *)(param_1 + 0x694) = FLOAT_804393bc + *(float *)(param_1 + 0x1dc8);
    }
  }
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0028.c 4704-4715 ==== */
// ==== 80103b9c  FUN_80103b9c ====

void FUN_80103b9c(int param_1)

{
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000)) -
                           DOUBLE_804393a0) * FLOAT_804393a8);
  (*(code *)(&PTR_FUN_80321690)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4719-4729 ==== */
// ==== 80103c10  FUN_80103c10 ====

void FUN_80103c10(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_803216a4)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4733-4775 ==== */
// ==== 80103c60  FUN_80103c60 ====

void FUN_80103c60(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_804393b0;
  *(float *)(param_1 + 0x50) = FLOAT_804393b0;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0xd;
  *(undefined1 *)(param_1 + 0x542) = 1;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 0xc;
    *(undefined1 *)(param_1 + 0x542) = 0;
  }
  zz_006d144_(param_1,0xc1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_804393ac;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,2,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_804393b0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4779-4808 ==== */
// ==== 80103d88  FUN_80103d88 ====

void FUN_80103d88(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_00c3be0_(param_1,0x1a);
    zz_00c3be0_(param_1,0x1b);
    dVar1 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804393d0 * dVar1);
    dVar1 = zz_0045204_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804393d0 * dVar1);
  }
  dVar1 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_804393b8 < dVar1) {
    zz_00b22f4_(param_1);
  }
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0028.c 4812-4887 ==== */
// ==== 80103e7c  FUN_80103e7c ====

void FUN_80103e7c(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  float afStack_28 [4];
  undefined4 local_18;
  uint uStack_14;
  longlong local_10;
  
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_1 + 0x18da) ^ 0x80000000;
  iVar2 = (int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,uStack_14)) - DOUBLE_804393a0) * FLOAT_80439398);
  local_10 = (longlong)iVar2;
  *(short *)(param_1 + 0x18da) = (short)iVar2;
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_804393b4,param_1);
  FUN_80067310((double)FLOAT_804393bc,param_1,*(short *)(param_1 + 0x72) + -0x8000);
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804393c4 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (('\0' < *(char *)(param_1 + 0x542)) && (*(char *)(param_1 + 0x1cee) != '\0')) {
    *(undefined1 *)(param_1 + 0x542) = 0;
    if (iVar2 == 0) {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + '\x01';
    }
    zz_004beb8_((double)FLOAT_804393ac,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
                0xffffffff);
  }
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    if (*(char *)(param_1 + 0x542) < '\x01') {
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),afStack_28);
      dVar3 = gnt4_PSVECMag_bl(afStack_28);
      if ((double)FLOAT_804393d4 < dVar3) {
        zz_00b22f4_(param_1);
      }
    }
    else {
      zz_00b22f4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      iVar2 = FUN_800452a0((double)*(float *)(param_1 + 0x38),(double)*(float *)(param_1 + 0x40));
      *(short *)(param_1 + 0x5ae) = (short)iVar2;
      fVar1 = FLOAT_804393b0;
      *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + *(float *)(param_1 + 0x3c);
      *(float *)(param_1 + 0x3c) = fVar1;
      dVar3 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
      *(float *)(param_1 + 0x44) = (float)dVar3;
      *(float *)(param_1 + 0x4c) = FLOAT_804393b0;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      zz_006a5a4_(param_1);
    }
  }
  return;
}
