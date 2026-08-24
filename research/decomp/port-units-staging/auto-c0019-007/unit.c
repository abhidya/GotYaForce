#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800bc65c(int param_1);
void FUN_800bc72c(int param_1);
void FUN_800bc81c(int param_1);
void FUN_800bc8ac(int param_1);
void FUN_800bc930(int param_1);
void FUN_800bcb08(int param_1);
void FUN_800bcb60(int param_1);
void FUN_800bcbb0(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1413-1437 ==== */
// ==== 800bc65c  FUN_800bc65c ====

void FUN_800bc65c(int param_1)

{
  float fVar1;
  uint uVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar1 = FLOAT_80438544;
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = 10;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_80438540,param_1,0xf,3,9,0xffffffff,0xffffffff);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1441-1469 ==== */
// ==== 800bc72c  FUN_800bc72c ====

void FUN_800bc72c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043852c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80438538;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar2 = FLOAT_8043852c;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x764))) {
      fVar1 = *(float *)(param_1 + 0x764);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_80438538;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    zz_00b2190_(param_1,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1473-1494 ==== */
// ==== 800bc81c  FUN_800bc81c ====

void FUN_800bc81c(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_8043852c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_80438548,param_1), 0 < (int)uVar3)) {
    fVar1 = FLOAT_8043853c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1498-1521 ==== */
// ==== 800bc8ac  FUN_800bc8ac ====

void FUN_800bc8ac(int param_1)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  fVar2 = FLOAT_8043852c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  bVar3 = fVar1 < FLOAT_8043852c;
  *(float *)(param_1 + 0x558) = fVar1;
  if (bVar3) {
    dVar4 = (double)FLOAT_80438540;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 1;
    *(float *)(param_1 + 0x4c) = fVar2;
    zz_004beb8_(dVar4,param_1,0xf,3,10,0xffffffff,0xffffffff);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1525-1578 ==== */
// ==== 800bc930  FUN_800bc930 ====

void FUN_800bc930(int param_1)

{
  short sVar2;
  uint uVar1;
  int iVar3;
  double dVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043854c,param_1);
  if (*(float *)(param_1 + 0x764) < FLOAT_80438548) {
    zz_006ed8c_((double)FLOAT_8043854c,param_1);
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if ((*(char *)(param_1 + 0x1cef) != '\0') && ('\0' < *(char *)(param_1 + 0x746))) {
    *(undefined1 *)(param_1 + 0x746) = 0;
    sVar2 = *(short *)(param_1 + 0x54a) + -1;
    *(short *)(param_1 + 0x54a) = sVar2;
    if (0 < sVar2) {
      if (*(int *)(param_1 + 0xcc) == 0) {
        *(float *)(param_1 + 0x44) = FLOAT_80438558;
      }
      else {
        *(float *)(param_1 + 0x44) = (float)(DOUBLE_80438550 * (double)*(float *)(param_1 + 0x764));
      }
      uVar1 = zz_00055fc_();
      iVar3 = (uVar1 & 1) * 2;
      zz_004beb8_((double)FLOAT_80438540,param_1,0xf,3,
                  (int)*(char *)(*(char *)(param_1 + 0x542) * 4 + -0x7fcfe654 + iVar3),0xffffffff,
                  0xffffffff);
      *(undefined1 *)(param_1 + 0x542) =
           *(undefined1 *)(*(char *)(param_1 + 0x542) * 4 + iVar3 + -0x7fcfe653);
      uVar1 = zz_00055fc_();
      *(short *)(param_1 + 0x18e2) = (short)(char)(&DAT_80433af0)[uVar1 & 3];
      zz_00b2190_(param_1,0);
      return;
    }
    zz_006a3d0_(param_1,'\x01',1,0);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    dVar4 = (double)FLOAT_80438540;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x18e2) = 0;
    zz_004beb8_(dVar4,param_1,0xf,3,0xe,0xffffffff,0xffffffff);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1582-1594 ==== */
// ==== 800bcb08  FUN_800bcb08 ====

void FUN_800bcb08(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1598-1608 ==== */
// ==== 800bcb60  FUN_800bcb60 ====

void FUN_800bcb60(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_803019b8)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1612-1650 ==== */
// ==== 800bcbb0  FUN_800bcbb0 ====

void FUN_800bcbb0(int param_1)

{
  float fVar1;
  uint uVar2;
  float local_18;
  float local_14;
  float local_10;
  
  fVar1 = FLOAT_80438538;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    local_18 = FLOAT_8043852c;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    local_10 = FLOAT_80438560;
    local_14 = FLOAT_8043855c;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x8d4),&local_18,(float *)(param_1 + 0x38));
  }
  else {
    local_18 = *(float *)(param_1 + 0x518);
    local_10 = *(float *)(param_1 + 0x520);
    local_14 = FLOAT_8043855c * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    *(float *)(param_1 + 0x38) = local_18;
    *(float *)(param_1 + 0x3c) = local_14;
    *(float *)(param_1 + 0x40) = local_10;
  }
  zz_006d144_(param_1,0xc0);
  zz_0092dcc_(param_1,0);
  zz_004beb8_((double)FLOAT_80438540,param_1,0xf,3,5,0xffffffff,0xffffffff);
  return;
}
