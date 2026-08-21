#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_8007ac2c(int param_1);
void FUN_8007ac7c(int param_1);
void FUN_8007ad5c(int param_1);
void FUN_8007aea0(int param_1);
void FUN_8007af84(int param_1);
void FUN_8007b184(int param_1);
void FUN_8007b1bc(int param_1);
void FUN_8007b20c(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 2339-2349 ==== */
// ==== 8007ac2c  FUN_8007ac2c ====

void FUN_8007ac2c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d6634)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 2353-2380 ==== */
// ==== 8007ac7c  FUN_8007ac7c ====

void FUN_8007ac7c(int param_1)

{
  float fVar1;
  uint uVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x54e);
  }
  fVar1 = FLOAT_80437928;
  *(float *)(param_1 + 0x558) = FLOAT_80437904;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar1;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_804378e8;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 2384-2420 ==== */
// ==== 8007ad5c  FUN_8007ad5c ====

void FUN_8007ad5c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043792c;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043792c;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    fVar2 = FLOAT_804378e8;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    fVar1 = fVar1 / FLOAT_804378ec;
    *(float *)(param_1 + 0x558) = FLOAT_804378ec;
    fVar3 = FLOAT_8043790c;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_804378f0,param_1,0xf,3,5,0xffffffff,0xffffffff);
    *(undefined1 *)(param_1 + 0x542) = 0;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 2424-2454 ==== */
// ==== 8007aea0  FUN_8007aea0 ====

void FUN_8007aea0(int param_1)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  float afStack_18 [5];
  
  zz_004cd24_(param_1,0xf);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),afStack_18);
  gnt4_PSVECMag_bl(afStack_18);
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar1 = FLOAT_804378e8;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) ||
     (uVar3 = FUN_80066838((double)FLOAT_8043790c,param_1), uVar3 != 0)) {
    dVar4 = (double)FLOAT_804378f0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,5,0xffffffff,0xffffffff);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 2458-2546 ==== */
// ==== 8007af84  FUN_8007af84 ====

void FUN_8007af84(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = zz_00677b0_(param_1);
  if ((iVar5 != 0) && (FLOAT_804378f8 < *(float *)(param_1 + 0x44))) {
    zz_00b22f4_(param_1);
  }
  uVar6 = FUN_80066838((double)FLOAT_80437930,param_1);
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
  fVar3 = FLOAT_804378e8;
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
      goto LAB_8007b124;
    }
    if (cVar1 == '\0') {
      zz_004cd24_(param_1,0xf);
      fVar4 = FLOAT_80437934;
      fVar3 = FLOAT_80437918;
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
LAB_8007b124:
  iVar5 = zz_0066ff0_(param_1);
  if (iVar5 == 1) {
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 2550-2559 ==== */
// ==== 8007b184  FUN_8007b184 ====

void FUN_8007b184(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 2563-2573 ==== */
// ==== 8007b1bc  FUN_8007b1bc ====

void FUN_8007b1bc(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_802d6648)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 2577-2599 ==== */
// ==== 8007b20c  FUN_8007b20c ====

void FUN_8007b20c(int param_1)

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
  dVar2 = (double)FLOAT_804378f0;
  *(float *)(param_1 + 0x558) = FLOAT_80437904;
  *(undefined1 *)(param_1 + 0x6ea) = 3;
  zz_004beb8_(dVar2,param_1,0xf,3,4,0xffffffff,0xffffffff);
  return;
}
