#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80131080(int param_1);
void FUN_80131184(uint param_1);
void FUN_801312b4(int param_1);
void zz_013138c_(int param_1);
uint zz_01313bc_(uint param_1);
void FUN_80131598(int param_1);
void FUN_801315d4(int param_1);
void FUN_80131604(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 312-338 ==== */
// ==== 80131080  FUN_80131080 ====

void FUN_80131080(int param_1)

{
  double dVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_80439e9c;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(short *)(param_1 + 1000) == 0x103) {
    zz_004beb8_((double)FLOAT_80439e90,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
                0xffffffff);
    if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
      zz_004beb8_((double)FLOAT_80439e90,param_1,2,0,0xd,0xffffffff,0xffffffff);
    }
  }
  else {
    zz_004beb8_((double)FLOAT_80439e90,param_1,0xf,2,0x15,4,1);
  }
  zz_013138c_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_80439e78;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 342-382 ==== */
// ==== 80131184  FUN_80131184 ====

/* WARNING: Removing unreachable block (ram,0x80131298) */
/* WARNING: Removing unreachable block (ram,0x80131194) */

void FUN_80131184(uint param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if ((*(char *)(param_1 + 0x1cef) != '\0') && (*(char *)(param_1 + 0x1b03) == '\0')) {
    *(float *)(param_1 + 0x1dc8) = FLOAT_80439e78;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  FUN_80067310((double)FLOAT_80439e9c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  fVar2 = FLOAT_80439e78;
  if ((((iVar3 != 0) ||
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) &&
      (*(char *)(param_1 + 0x1cef) != '\0')) && (*(char *)(param_1 + 0x1b03) == '\0')) {
    zz_01313bc_(param_1);
    if (*(short *)(param_1 + 1000) == 0x103) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
      zz_006a5a4_(param_1);
    }
    else {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
  }
  zz_00b22f4_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 386-415 ==== */
// ==== 801312b4  FUN_801312b4 ====

void FUN_801312b4(int param_1)

{
  int iVar1;
  
  if (*(float *)(param_1 + 0x55c) <= FLOAT_80439e78) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  FUN_80067310((double)FLOAT_80439e9c,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
    if (((*(ushort *)(param_1 + 0x5d8) & 0xf0) != 0) || (*(char *)(param_1 + 0x1cee) != '\0')) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439ea0 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 419-437 ==== */
// ==== 8013138c  zz_013138c_ ====

void zz_013138c_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_80439e7c;
  *(float *)(param_1 + 0x560) = FLOAT_80439ea4;
  fVar1 = FLOAT_80439e78;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  if (*(char *)(param_1 + 0x6ee) != '\0') {
    return;
  }
  *(undefined1 *)(param_1 + 0x6ef) = 5;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 441-516 ==== */
// ==== 801313bc  zz_01313bc_ ====

/* WARNING: Removing unreachable block (ram,0x80131578) */
/* WARNING: Removing unreachable block (ram,0x801313cc) */

uint zz_01313bc_(uint param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  double dVar7;
  double dVar8;
  float local_28;
  float local_24;
  undefined4 local_20;
  
  fVar2 = FLOAT_80439e7c;
  *(float *)(param_1 + 0x560) = FLOAT_80439ea4;
  fVar1 = FLOAT_80439e78;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  uVar3 = param_1;
  if ('\0' < *(char *)(param_1 + 0x6ef)) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    uVar3 = zz_0046698_(param_1);
    if (*(int *)(param_1 + 0xcc) != 0) {
      local_28 = *(float *)(param_1 + 0xa24);
      dVar7 = (double)*(float *)(param_1 + 0xa34);
      local_20 = *(undefined4 *)(param_1 + 0xa44);
      local_24 = FLOAT_80439e78;
      dVar8 = gnt4_PSVECMag_bl(&local_28);
      iVar4 = FUN_800452a0(dVar7,dVar8);
      local_28 = *(float *)(param_1 + 0xa30);
      local_24 = *(float *)(param_1 + 0xa40);
      local_20 = *(undefined4 *)(param_1 + 0xa50);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
      dVar8 = (double)local_24;
      local_24 = FLOAT_80439e78;
      dVar7 = gnt4_PSVECMag_bl(&local_28);
      iVar5 = FUN_800452a0(dVar8,dVar7);
      *(short *)(param_1 + 0x1900) = (short)iVar4 + (short)iVar5;
      uVar3 = zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + 0x19b2) * 0x30 + 0x8d4),
                          (float *)(param_1 + 0xa24),(short *)(param_1 + 0x18fe),
                          (undefined4 *)(param_1 + 0x1328),(float *)(param_1 + 0xf44),
                          (float *)(param_1 + 0x1628));
    }
    if (*(short *)(param_1 + 1000) == 0x103) {
      iVar4 = zz_006dbe0_(param_1,0,1,1);
      uVar3 = 0;
      if (iVar4 != 0) {
        zz_0082824_(param_1,0x26);
        uVar3 = (uint)*(byte *)(param_1 + 0x6ef);
        *(byte *)(param_1 + 0x6ef) = *(byte *)(param_1 + 0x6ef) - 1;
      }
      if (*(short *)(param_1 + 0x774) < 1) {
        *(undefined1 *)(param_1 + 0x6ef) = 0;
      }
    }
    else if (*(short *)(param_1 + 1000) == 0x106) {
      iVar4 = zz_006dbe0_(param_1,2,1,1);
      uVar3 = 0;
      if (iVar4 != 0) {
        *(byte *)(param_1 + 0x15b) = *(byte *)(param_1 + 0x15b) | 2;
        bVar6 = zz_00fe668_(param_1,2,2);
        uVar3 = (uint)bVar6;
      }
      *(undefined1 *)(param_1 + 0x6ef) = 0;
    }
  }
  return uVar3;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 520-527 ==== */
// ==== 80131598  FUN_80131598 ====

void FUN_80131598(int param_1)

{
  (*(code *)(&PTR_FUN_80335d04)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 531-539 ==== */
// ==== 801315d4  FUN_801315d4 ====

void FUN_801315d4(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 543-551 ==== */
// ==== 80131604  FUN_80131604 ====

void FUN_80131604(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}
