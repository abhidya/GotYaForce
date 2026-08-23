#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01a254c_(int param_1);
void zz_01a2624_(int param_1);
void zz_01a2824_(int param_1);
void zz_01a2858_(int param_1);
void zz_01a28a8_(int param_1);
void zz_01a2964_(int param_1);
void zz_01a2a18_(int param_1);
void zz_01a2c58_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 478-508 ==== */
// ==== 801a254c  zz_01a254c_ ====

void zz_01a254c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  float afStack_18 [5];
  
  zz_004cd24_(param_1,0xf);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),afStack_18);
  gnt4_PSVECMag_bl(afStack_18);
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar2 = FLOAT_8043b594;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar4 = FUN_80066838((double)FLOAT_8043b5b4,param_1), uVar4 != 0)) {
    dVar5 = (double)FLOAT_8043b598;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,5,0xffffffff,0xffffffff);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 512-600 ==== */
// ==== 801a2624  zz_01a2624_ ====

void zz_01a2624_(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = zz_00677b0_(param_1);
  if ((iVar5 != 0) && (FLOAT_8043b5a8 < *(float *)(param_1 + 0x44))) {
    zz_00b22f4_(param_1);
  }
  uVar6 = FUN_80066838((double)FLOAT_8043b5d8,param_1);
  if (0 < (int)uVar6) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  if (*(char *)(param_1 + 0x541) == '\0') {
    uVar2 = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
    zz_006660c_(param_1);
    if (*(char *)(param_1 + 0x1d9) == '\0') {
      FUN_800669d0(param_1,0x40);
    }
    else {
      *(undefined1 *)(param_1 + 0x541) = 1;
    }
    *(undefined2 *)(param_1 + 0x72) = uVar2;
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar3 = FLOAT_8043b594;
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 == '\x04') {
        iVar5 = zz_004cd24_(param_1,0xf);
        if (iVar5 != 1) {
          return;
        }
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        return;
      }
      if ('\x03' < cVar1) {
        return;
      }
      goto LAB_801a27c4;
    }
    if (cVar1 == '\0') {
      zz_004cd24_(param_1,0xf);
      fVar4 = FLOAT_8043b5dc;
      fVar3 = FLOAT_8043b5bc;
      if (*(char *)(param_1 + 0x1cef) != '\x02') {
        return;
      }
      if (*(char *)(param_1 + 0x1cf0) != '\x01') {
        return;
      }
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      *(undefined2 *)(param_1 + 0x548) = 0;
      *(undefined2 *)(param_1 + 0x54a) = 0x1500;
      *(float *)(param_1 + 0x558) = fVar4;
      *(float *)(param_1 + 0x4c) = fVar3;
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    if (fVar3 < *(float *)(param_1 + 0x558)) {
      zz_0067754_(param_1,(short *)(param_1 + 0x72),*(short *)(param_1 + 0x54a));
      return;
    }
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 1;
  }
  zz_0066ed8_(param_1,*(ushort *)(param_1 + 0x5ae),*(undefined2 *)(param_1 + 0x54a));
  *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
LAB_801a27c4:
  iVar5 = zz_0066ff0_(param_1);
  if (iVar5 == 1) {
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 604-613 ==== */
// ==== 801a2824  zz_01a2824_ ====

void zz_01a2824_(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 617-627 ==== */
// ==== 801a2858  zz_01a2858_ ====

void zz_01a2858_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01a28a8__80378770)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 631-653 ==== */
// ==== 801a28a8  zz_01a28a8_ ====

void zz_01a28a8_(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  dVar2 = (double)FLOAT_8043b598;
  *(float *)(param_1 + 0x558) = FLOAT_8043b5ac;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,4,0xffffffff,0xffffffff);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 657-686 ==== */
// ==== 801a2964  zz_01a2964_ ====

void zz_01a2964_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043b594;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < fVar1) {
    iVar3 = zz_006d144_(param_1,0xc0);
    if (iVar3 == 0) goto LAB_801a29d8;
  }
  fVar2 = FLOAT_8043b5d8;
  fVar1 = FLOAT_8043b590;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar2 < *(float *)(param_1 + 0x760)) {
    zz_0092dcc_(param_1,0);
  }
LAB_801a29d8:
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 690-769 ==== */
// ==== 801a2a18  zz_01a2a18_ ====

/* WARNING: Removing unreachable block (ram,0x801a2c3c) */
/* WARNING: Removing unreachable block (ram,0x801a2a28) */

void zz_01a2a18_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  if (((*(char *)(param_1 + 0x542) == '\0') && (*(char *)(param_1 + 0x1cef) == '\x02')) &&
     (*(char *)(param_1 + 0x1cf0) == '\x02')) {
    *(undefined1 *)(param_1 + 0x542) = 1;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),&local_2c);
  dVar5 = gnt4_PSVECMag_bl(&local_2c);
  fVar1 = FLOAT_8043b594;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(float *)(param_1 + 0x44) =
         FLOAT_8043b5b0 *
         (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / FLOAT_8043b590
         );
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else {
    iVar4 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_2c = *(float *)(iVar4 + 0x8e0);
    local_28 = *(float *)(iVar4 + 0x8f0);
    local_24 = *(undefined4 *)(iVar4 + 0x900);
    local_38 = *(float *)(param_1 + 0x518);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    local_34 = FLOAT_8043b590 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
    fVar1 = FLOAT_8043b594;
    *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043b5e0;
    *(float *)(param_1 + 0x50) = fVar1;
    local_28 = fVar1;
    dVar6 = gnt4_PSVECMag_bl(&local_2c);
    fVar1 = FLOAT_8043b5e4;
    *(float *)(param_1 + 0x44) = (float)(dVar6 * (double)FLOAT_8043b5e0);
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x542) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  uVar3 = FUN_80066838((double)FLOAT_8043b5ac,param_1);
  if ((int)uVar3 < 1) {
    if (*(char *)(param_1 + 0x6ea) < '\x01') {
      if (dVar5 < DOUBLE_8043b5e8 * (double)*(float *)(param_1 + 0x44)) goto LAB_801a2c30;
    }
    else {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + -1;
    }
    fVar2 = FLOAT_8043b594;
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) {
      return;
    }
  }
LAB_801a2c30:
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 773-797 ==== */
// ==== 801a2c58  zz_01a2c58_ ====

void zz_01a2c58_(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043b594;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043b594) {
      *(float *)(param_1 + 0x44) = FLOAT_8043b594;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_8043b590 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}
