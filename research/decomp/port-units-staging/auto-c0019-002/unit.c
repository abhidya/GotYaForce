#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800bae68(int param_1);
void FUN_800bb004(int param_1);
void FUN_800bb040(int param_1);
void FUN_800bb064(int param_1);
void FUN_800bb088(int param_1);
void FUN_800bb0ac(int param_1);
void FUN_800bb0d0(int param_1);
void FUN_800bb10c(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 439-499 ==== */
// ==== 800bae68  FUN_800bae68 ====

/* WARNING: Removing unreachable block (ram,0x800bafe4) */
/* WARNING: Removing unreachable block (ram,0x800bae78) */

void FUN_800bae68(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_28;
  float local_24;
  undefined4 local_20;
  
  fVar2 = FLOAT_80438510;
  fVar1 = FLOAT_8043850c;
  *(float *)(param_1 + 0x560) = FLOAT_8043850c;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  if ('\0' < *(char *)(param_1 + 0x6ef)) {
    *(undefined2 *)(param_1 + 0x1918) = 0;
    zz_0046698_(param_1);
    if (*(int *)(param_1 + 0xcc) != 0) {
      local_28 = *(float *)(param_1 + 0xae4);
      dVar5 = (double)*(float *)(param_1 + 0xaf4);
      local_20 = *(undefined4 *)(param_1 + 0xb04);
      local_24 = FLOAT_804384fc;
      dVar6 = gnt4_PSVECMag_bl(&local_28);
      iVar3 = FUN_800452a0(dVar5,dVar6);
      local_28 = *(float *)(param_1 + 0xaf0);
      local_24 = *(float *)(param_1 + 0xb00);
      local_20 = *(undefined4 *)(param_1 + 0xb10);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
      dVar6 = (double)local_24;
      local_24 = FLOAT_804384fc;
      dVar5 = gnt4_PSVECMag_bl(&local_28);
      iVar4 = FUN_800452a0(dVar6,dVar5);
      *(short *)(param_1 + 0x1918) = (short)iVar3 + (short)iVar4;
      zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + 0x19c2) * 0x30 + 0x8d4),
                  (float *)(param_1 + 0xae4),(short *)(param_1 + 0x1916),
                  (undefined4 *)(param_1 + 0x1358),(float *)(param_1 + 0xf84),
                  (float *)(param_1 + 0x1658));
    }
    iVar3 = zz_006dbe0_(param_1,0,1,1);
    if (iVar3 != 0) {
      *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
      FUN_801177d0(param_1,*(undefined1 *)(param_1 + 0x172));
      *(char *)(param_1 + 0x172) = *(char *)(param_1 + 0x172) + '\x01';
      *(byte *)(param_1 + 0x172) = *(byte *)(param_1 + 0x172) & 3;
    }
    if (*(short *)(param_1 + 0x774) < 1) {
      *(undefined1 *)(param_1 + 0x6ef) = 0;
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 503-510 ==== */
// ==== 800bb004  FUN_800bb004 ====

void FUN_800bb004(int param_1)

{
  (*(code *)(&PTR_FUN_803003ec)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 514-521 ==== */
// ==== 800bb040  FUN_800bb040 ====

void FUN_800bb040(int param_1)

{
  zz_015809c_(param_1,0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 525-532 ==== */
// ==== 800bb064  FUN_800bb064 ====

void FUN_800bb064(int param_1)

{
  zz_0158688_(param_1,3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 536-543 ==== */
// ==== 800bb088  FUN_800bb088 ====

void FUN_800bb088(int param_1)

{
  zz_0158688_(param_1,4);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 547-554 ==== */
// ==== 800bb0ac  FUN_800bb0ac ====

void FUN_800bb0ac(int param_1)

{
  zz_0158a94_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 558-565 ==== */
// ==== 800bb0d0  FUN_800bb0d0 ====

void FUN_800bb0d0(int param_1)

{
  (*(code *)(&PTR_FUN_80300400)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 569-580 ==== */
// ==== 800bb10c  FUN_800bb10c ====

void FUN_800bb10c(int param_1)

{
  *(undefined1 *)(param_1 + 0x171) = 4;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (**(code **)(&DAT_80433ae0 + *(char *)(param_1 + 0x540) * 4))();
  return;
}
