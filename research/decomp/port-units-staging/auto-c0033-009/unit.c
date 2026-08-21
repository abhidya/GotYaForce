#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_8012495c(int param_1);
void FUN_801249ec(int param_1);
void FUN_80124a48(int param_1);
void FUN_80124b60(int param_1);
void FUN_80124c2c(int param_1);
void FUN_80124d08(int param_1);
void FUN_80124dc8(int param_1);
void FUN_80124e8c(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2346-2364 ==== */
// ==== 8012495c  FUN_8012495c ====

void FUN_8012495c(int param_1)

{
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  zz_006ed8c_((double)FLOAT_80439b80,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2368-2379 ==== */
// ==== 801249ec  FUN_801249ec ====

void FUN_801249ec(int param_1)

{
  *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032e3ec)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2383-2416 ==== */
// ==== 80124a48  FUN_80124a48 ====

void FUN_80124a48(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_80439b9c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 4;
  uVar3 = FUN_800668cc((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439ba4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_80439b94;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2420-2446 ==== */
// ==== 80124b60  FUN_80124b60 ====

void FUN_80124b60(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80439ba4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar1 = FLOAT_80439ba0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    zz_0092dcc_(param_1,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2450-2480 ==== */
// ==== 80124c2c  FUN_80124c2c ====

void FUN_80124c2c(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439be0 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_80439be4;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439be0 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_800668cc((double)FLOAT_80439be8,param_1), 0 < (int)uVar3)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2484-2506 ==== */
// ==== 80124d08  FUN_80124d08 ====

void FUN_80124d08(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  zz_006ed8c_((double)FLOAT_80439bec,param_1);
  FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    dVar1 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439be0 * dVar1);
    dVar1 = zz_0045204_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439be0 * -dVar1);
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2510-2534 ==== */
// ==== 80124dc8  FUN_80124dc8 ====

void FUN_80124dc8(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_80439ba4,param_1);
  FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439be4 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2538-2549 ==== */
// ==== 80124e8c  FUN_80124e8c ====

void FUN_80124e8c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032e400)[*(char *)(param_1 + 0x540)])();
  return;
}
