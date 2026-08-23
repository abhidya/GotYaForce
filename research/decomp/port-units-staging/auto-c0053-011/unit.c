#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801b8330(int param_1);
void FUN_801b83c8(int param_1);
void FUN_801b84cc(int param_1);
void FUN_801b8704(int param_1);
void FUN_801b881c(int param_1);
void zz_01b883c_(int param_1);
void FUN_801b888c(int param_1);
void FUN_801b8964(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2506-2529 ==== */
// ==== 801b8330  FUN_801b8330 ====

void FUN_801b8330(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043ba18;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_8043ba34;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    FUN_801b8704(param_1);
    zz_00b2190_(param_1,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2533-2566 ==== */
// ==== 801b83c8  FUN_801b83c8 ====

void FUN_801b83c8(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  fVar1 = FLOAT_8043ba18;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar4);
  if (fVar1 < *(float *)(param_1 + 0x48)) {
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  }
  FUN_80067310((double)FLOAT_8043ba24,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043ba18;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) ||
     (uVar3 = FUN_800668cc((double)*(float *)(param_1 + 0x3c),param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2570-2640 ==== */
// ==== 801b84cc  FUN_801b84cc ====

void FUN_801b84cc(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if ((*(char *)(param_1 + 0x584) == '\x01') && ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0)) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  if ((*(char *)(param_1 + 0x584) == '\x02') && ((*(uint *)(param_1 + 0x5d4) & 0x80) != 0)) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043ba34;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    dVar4 = (double)FLOAT_8043ba30;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(float *)(param_1 + 0x558) = fVar2;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    FUN_801b8704(param_1);
    zz_00b2190_(param_1,0);
    return;
  }
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    FUN_801b8704(param_1);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_8043ba38,param_1);
  if (*(float *)(param_1 + 0x760) < *(float *)(param_1 + 0x3c)) {
    zz_006ed8c_((double)FLOAT_8043ba20,param_1);
  }
  FUN_80067310((double)FLOAT_8043ba24,param_1,*(short *)(param_1 + 0x5ac));
  iVar3 = zz_00677b0_(param_1);
  if (((iVar3 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) &&
     ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043ba3c + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar3 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffbf;
    }
  }
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0053.c 2644-2680 ==== */
// ==== 801b8704  FUN_801b8704 ====

/* WARNING: Removing unreachable block (ram,0x801b8800) */
/* WARNING: Removing unreachable block (ram,0x801b8714) */

void FUN_801b8704(int param_1)

{
  float fVar1;
  double dVar2;
  double dVar3;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c);
  }
  else {
    fVar1 = *(float *)(param_1 + 0x760) *
            (float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000)) -
                   DOUBLE_8043ba48) * FLOAT_8043ba40;
  }
  dVar3 = (double)(fVar1 / FLOAT_8043ba34);
  *(float *)(param_1 + 0x38) = fVar1 / FLOAT_8043ba34;
  fVar1 = *(float *)(*(int *)(param_1 + 0x4b0) + 0x54);
  if (fVar1 < *(float *)(param_1 + 0x38)) {
    *(float *)(param_1 + 0x38) = fVar1;
  }
  dVar2 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)(dVar3 * dVar2);
  dVar2 = zz_0045204_(*(short *)(param_1 + 0x54e));
  fVar1 = FLOAT_8043ba18;
  *(float *)(param_1 + 0x48) = (float)(dVar3 * -dVar2);
  if (fVar1 < *(float *)(param_1 + 0x48)) {
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  }
  *(undefined1 *)(param_1 + 0x1d0f) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2684-2691 ==== */
// ==== 801b881c  FUN_801b881c ====

void FUN_801b881c(int param_1)

{
  zz_01b883c_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2695-2705 ==== */
// ==== 801b883c  zz_01b883c_ ====

void zz_01b883c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80382228)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2709-2737 ==== */
// ==== 801b888c  FUN_801b888c ====

void FUN_801b888c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043ba34;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  fVar1 = FLOAT_8043ba18;
  *(float *)(param_1 + 0x50) = FLOAT_8043ba18;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043ba50,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_8043ba30,param_1,0xf,4,1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043ba18;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 2741-2764 ==== */
// ==== 801b8964  FUN_801b8964 ====

void FUN_801b8964(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043ba50,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043ba18;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}
