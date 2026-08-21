#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800ba3b4(int param_1);
void FUN_800ba3ec(int param_1);
void FUN_800ba418(int param_1);
void FUN_800ba454(int param_1);
void FUN_800ba4d4(int param_1);
void FUN_800ba51c(int param_1);
void FUN_800ba61c(int param_1);
void FUN_800ba71c(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 1-9 ==== */
// ==== 800ba3b4  FUN_800ba3b4 ====

void FUN_800ba3b4(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0xf);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 13-21 ==== */
// ==== 800ba3ec  FUN_800ba3ec ====

void FUN_800ba3ec(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x78);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 25-32 ==== */
// ==== 800ba418  FUN_800ba418 ====

void FUN_800ba418(int param_1)

{
  (*(code *)(&PTR_FUN_803003a8)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 36-48 ==== */
// ==== 800ba454  FUN_800ba454 ====

void FUN_800ba454(int param_1)

{
  *(short *)(param_1 + 0x1918) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1918) ^ 0x80000000) -
                           DOUBLE_804384f0) * FLOAT_804384ec);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_803003b4)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 52-60 ==== */
// ==== 800ba4d4  FUN_800ba4d4 ====

void FUN_800ba4d4(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_803003c8)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 64-94 ==== */
// ==== 800ba51c  FUN_800ba51c ====

void FUN_800ba51c(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_804384f8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,1,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,0xffffffff);
  zz_004beb8_((double)FLOAT_804384f8,param_1,2,0,0,0xffffffff,0xffffffff);
  zz_006d0dc_(param_1,0xc1,0);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  FUN_800bae3c(param_1);
  fVar1 = FLOAT_804384fc;
  *(float *)(param_1 + 0x50) = FLOAT_804384fc;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80438500,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_804384fc;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 98-134 ==== */
// ==== 800ba61c  FUN_800ba61c ====

/* WARNING: Removing unreachable block (ram,0x800ba700) */
/* WARNING: Removing unreachable block (ram,0x800ba62c) */

void FUN_800ba61c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_804384fc;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_804384fc;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_800bae68(param_1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80438500,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80438504 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 138-191 ==== */
// ==== 800ba71c  FUN_800ba71c ====

void FUN_800ba71c(int param_1)

{
  int iVar1;
  double dVar2;
  
  if (*(float *)(param_1 + 0x55c) <= FLOAT_804384fc) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(float *)(param_1 + 0x558) <= FLOAT_804384fc) {
    if ((*(uint *)(param_1 + 0x5d4) & 0x20) != 0) {
      iVar1 = zz_006dbe0_(param_1,0,1,0);
      if ((iVar1 != 0) && ('\0' < *(char *)(param_1 + 0x6ef))) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
          zz_006a3d0_(param_1,'\0',3,0);
          return;
        }
        zz_006bf80_(param_1);
        dVar2 = (double)FLOAT_804384f8;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        zz_004beb8_(dVar2,param_1,1,2,1,0xffffffff,0xffffffff);
        zz_004beb8_((double)FLOAT_804384f8,param_1,2,0,0,0xffffffff,0xffffffff);
        return;
      }
      goto LAB_800ba850;
    }
    *(float *)(param_1 + 0x55c) = FLOAT_804384fc;
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_1 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_80438500,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00679d0_(param_1);
    dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if (dVar2 <= (double)FLOAT_80438504) {
      return;
    }
    zz_00b22f4_(param_1);
    return;
  }
LAB_800ba850:
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}
