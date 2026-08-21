#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80124ee8(int param_1);
void zz_0124fbc_(int param_1);
void FUN_8012509c(int param_1);
void FUN_801251c0(int param_1);
undefined4 zz_01252c8_(int param_1);
void FUN_801253a0(int param_1);
void FUN_80125400(int param_1);
void FUN_80125474(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2553-2578 ==== */
// ==== 80124ee8  FUN_80124ee8 ====

void FUN_80124ee8(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_80439b9c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  zz_004beb8_((double)FLOAT_80439b94,param_1,0xf,3,5,0xffffffff,0xffffffff);
  zz_0124fbc_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2582-2615 ==== */
// ==== 80124fbc  zz_0124fbc_ ====

void zz_0124fbc_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439ba4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar3 = FLOAT_80439ba0;
    fVar1 = FLOAT_80439b90;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar2 = FLOAT_80439b98;
    *(float *)(param_1 + 0x558) = fVar3;
    *(float *)(param_1 + 0x55c) = fVar1;
    *(float *)(param_1 + 0x560) = fVar2;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x50) = fVar2;
    zz_0092dcc_(param_1,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2619-2656 ==== */
// ==== 8012509c  FUN_8012509c ====

void FUN_8012509c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  
  iVar3 = zz_01252c8_(param_1);
  if (iVar3 != 0) {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  dVar5 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439be0 * dVar5);
  dVar5 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar6 = (double)FLOAT_80439be4;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439be0 * -dVar5);
  FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar4 = FUN_800668cc((double)FLOAT_80439bf0,param_1), 0 < (int)uVar4)) {
    dVar5 = DOUBLE_80439bd8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar5);
    *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(param_1 + 0x4c) * dVar5);
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x48) * dVar5);
    *(float *)(param_1 + 0x50) = (float)((double)*(float *)(param_1 + 0x50) * dVar5);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2660-2696 ==== */
// ==== 801251c0  FUN_801251c0 ====

void FUN_801251c0(int param_1)

{
  float fVar1;
  int iVar2;
  
  iVar2 = zz_01252c8_(param_1);
  if (iVar2 != 0) {
    zz_004cd24_(param_1,0xf);
  }
  fVar1 = FLOAT_80439b98;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar1 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar1;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_80439ba4,param_1);
  FUN_80067310((double)FLOAT_80439be4,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
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

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0033.c 2700-2737 ==== */
// ==== 801252c8  zz_01252c8_ ====

undefined4 zz_01252c8_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  
  fVar3 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x55c) <= FLOAT_80439b98) || (*(char *)(param_1 + 0x1cf0) == '\0')) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    uVar4 = 0x81cd;
  }
  else {
    *(short *)(param_1 + 0x1900) =
         (short)(int)-(FLOAT_80439bf4 * fVar1 -
                      (float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1900) ^ 0x80000000)) -
                             DOUBLE_80439b88));
    fVar2 = *(float *)(param_1 + 0x55c) - fVar1;
    *(float *)(param_1 + 0x55c) = fVar2;
    if (fVar2 <= fVar3) {
      *(undefined1 *)(param_1 + 0x1cf0) = 0;
    }
    fVar3 = FLOAT_80439b98;
    fVar1 = *(float *)(param_1 + 0x560) - fVar1;
    *(float *)(param_1 + 0x560) = fVar1;
    if (fVar1 <= fVar3) {
      *(float *)(param_1 + 0x560) = FLOAT_80439bf8;
      zz_00f036c_(param_1,0xb);
    }
    uVar4 = 0;
  }
  return uVar4;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2741-2751 ==== */
// ==== 801253a0  FUN_801253a0 ====

void FUN_801253a0(int param_1)

{
  *(short *)(param_1 + 0x18e2) = *(short *)(param_1 + 0x18e2) >> 1;
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
  (*(code *)(&PTR_FUN_8032e410)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0033.c 2755-2766 ==== */
// ==== 80125400  FUN_80125400 ====

void FUN_80125400(int param_1)

{
  *(short *)(param_1 + 0x18dc) =
       (short)(int)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18dc) ^ 0x80000000)) -
                           DOUBLE_80439b88) * FLOAT_80439bfc);
  (*(code *)(&PTR_FUN_8032e424)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 2770-2804 ==== */
// ==== 80125474  FUN_80125474 ====

void FUN_80125474(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if (*(short *)(param_1 + 1000) == 0x20b) {
    *(undefined1 *)(param_1 + 0x6ea) = 2;
  }
  zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_80439b98;
  *(float *)(param_1 + 0x50) = FLOAT_80439b98;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(float *)(param_1 + 0x48) = FLOAT_80439be0;
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80439b94;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  zz_0125550_(param_1);
  return;
}
