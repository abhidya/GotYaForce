#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01b570c_(int param_1);
void zz_01b575c_(int param_1);
void zz_01b5840_(int param_1);
void zz_01b5980_(int param_1);
void zz_01b5a60_(int param_1);
void zz_01b5c60_(int param_1);
void zz_01b5c94_(void);
void zz_01b5c98_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 673-683 ==== */
// ==== 801b570c  zz_01b570c_ ====

void zz_01b570c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01b575c__80381748)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 687-717 ==== */
// ==== 801b575c  zz_01b575c_ ====

void zz_01b575c_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x54e);
  }
  fVar2 = FLOAT_8043b9cc;
  fVar1 = FLOAT_8043b9a0;
  *(float *)(param_1 + 0x558) = FLOAT_8043b9a0;
  *(float *)(param_1 + 0x558) = fVar1;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_8043b98c;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 721-758 ==== */
// ==== 801b5840  zz_01b5840_ ====

void zz_01b5840_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043b9d0;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043b9d0;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  zz_00670dc_(param_1,*(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_8043b98c;
  fVar1 = *(float *)(param_1 + 0x558) - FLOAT_8043b99c;
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    fVar2 = FLOAT_8043b98c;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    fVar1 = fVar1 / FLOAT_8043b988;
    *(float *)(param_1 + 0x558) = FLOAT_8043b988;
    fVar3 = FLOAT_8043b9ac;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x764)) {
      zz_00b2190_(param_1,0);
    }
    zz_004beb8_((double)FLOAT_8043b990,param_1,0xf,3,5,0xffffffff,0xffffffff);
    *(undefined1 *)(param_1 + 0x542) = 0;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 762-793 ==== */
// ==== 801b5980  zz_01b5980_ ====

void zz_01b5980_(int param_1)

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
  zz_006660c_(param_1);
  FUN_800669d0(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 != 0) {
    zz_00b22f4_(param_1);
  }
  fVar2 = FLOAT_8043b98c;
  fVar1 = *(float *)(param_1 + 0x558) - FLOAT_8043b99c;
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar4 = FUN_80066838((double)FLOAT_8043b9ac,param_1), uVar4 != 0)) {
    dVar5 = (double)FLOAT_8043b990;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,5,0xffffffff,0xffffffff);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 797-885 ==== */
// ==== 801b5a60  zz_01b5a60_ ====

void zz_01b5a60_(int param_1)

{
  char cVar1;
  undefined2 uVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = zz_00677b0_(param_1);
  if ((iVar5 != 0) && (FLOAT_8043b99c < *(float *)(param_1 + 0x44))) {
    zz_00b22f4_(param_1);
  }
  uVar6 = FUN_80066838((double)FLOAT_8043b9d4,param_1);
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
  fVar3 = FLOAT_8043b98c;
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
      goto LAB_801b5c00;
    }
    if (cVar1 == '\0') {
      zz_004cd24_(param_1,0xf);
      fVar4 = FLOAT_8043b9d8;
      fVar3 = FLOAT_8043b9b8;
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
LAB_801b5c00:
  iVar5 = zz_0066ff0_(param_1);
  if (iVar5 == 1) {
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(param_1 + 0x5ae);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 889-898 ==== */
// ==== 801b5c60  zz_01b5c60_ ====

void zz_01b5c60_(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 902-908 ==== */
// ==== 801b5c94  zz_01b5c94_ ====

void zz_01b5c94_(void)

{
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 912-922 ==== */
// ==== 801b5c98  zz_01b5c98_ ====

void zz_01b5c98_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01b5ce8__8038175c)[*(char *)(param_1 + 0x540)])();
  return;
}
