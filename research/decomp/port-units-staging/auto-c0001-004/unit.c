#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_8000ece4(int param_1,int param_2);
void FUN_8000ee04(int param_1,int param_2);
void FUN_8000eee8(int param_1);
void FUN_8000ef20(int param_1,int param_2);
void FUN_8000f02c(int param_1,int param_2);
void FUN_8000f36c(int param_1);
void FUN_8000f3a4(int param_1,int param_2);
void FUN_8000f448(int param_1,int param_2);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2121-2166 ==== */
// ==== 8000ece4  FUN_8000ece4 ====

void FUN_8000ece4(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  double dVar3;
  float fVar4;
  
  *(float *)(param_1 + 0x348) = *(float *)(param_1 + 0x348) + *(float *)(param_1 + 0x34c);
  if (*(float *)(param_1 + 0x348) < *(float *)(param_1 + 0x3dc)) {
    *(float *)(param_1 + 0x348) = *(float *)(param_1 + 0x3dc);
  }
  fVar2 = FLOAT_80436b50;
  fVar4 = FLOAT_80436b4c;
  dVar3 = DOUBLE_80436b30;
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x01') {
    *(float *)(param_1 + 0x3d8) =
         FLOAT_80436ac4 * *(float *)(param_2 + 0x7fc) + *(float *)(param_1 + 0x3d8);
    fVar2 = fVar2 * *(float *)(param_1 + 0x3d4);
    if (fVar2 < *(float *)(param_1 + 0x3d8)) {
      *(float *)(param_1 + 0x3d8) = fVar2;
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(float *)(param_1 + 0x3d8) = *(float *)(param_1 + 0x3d8) * FLOAT_80436b4c;
      *(short *)(param_1 + 0x3e2) =
           (short)(int)(fVar4 * (float)((double)CONCAT44(0x43300000,
                                                         (int)*(short *)(param_1 + 0x3e2) ^
                                                         0x80000000) - dVar3));
    }
  }
  else if (cVar1 < '\x03') {
    *(float *)(param_1 + 0x3d8) =
         FLOAT_80436b54 * *(float *)(param_2 + 0x7fc) + *(float *)(param_1 + 0x3d8);
    if (*(float *)(param_1 + 0x3d4) < *(float *)(param_1 + 0x3d8)) {
      *(float *)(param_1 + 0x3d8) = *(float *)(param_1 + 0x3d4);
    }
    *(short *)(param_1 + 0x3e2) = *(short *)(param_1 + 0x3e2) + 0x10;
  }
  FUN_8000ee04(param_1,param_2);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2170-2204 ==== */
// ==== 8000ee04  FUN_8000ee04 ====

/* WARNING: Removing unreachable block (ram,0x8000eec8) */
/* WARNING: Removing unreachable block (ram,0x8000ee14) */

void FUN_8000ee04(int param_1,int param_2)

{
  undefined4 uVar1;
  short sVar2;
  double dVar3;
  double dVar4;
  
  uVar1 = *(undefined4 *)(param_2 + 0x20);
  *(undefined4 *)(param_1 + 0x2e8) = uVar1;
  *(undefined4 *)(param_1 + 0x300) = uVar1;
  uVar1 = *(undefined4 *)(param_2 + 0x24);
  *(undefined4 *)(param_1 + 0x2ec) = uVar1;
  *(undefined4 *)(param_1 + 0x304) = uVar1;
  uVar1 = *(undefined4 *)(param_2 + 0x28);
  *(undefined4 *)(param_1 + 0x2f0) = uVar1;
  *(undefined4 *)(param_1 + 0x308) = uVar1;
  *(float *)(param_1 + 0x304) = *(float *)(param_1 + 0x304) + *(float *)(param_1 + 0x350);
  dVar4 = (double)(*(float *)(param_1 + 0x348) * *(float *)(param_1 + 0x354));
  sVar2 = *(short *)(param_2 + 0x72) + *(short *)(param_1 + 0x3e0) + *(short *)(param_1 + 0x3e2);
  dVar3 = zz_0045204_(sVar2);
  *(float *)(param_1 + 0x2e8) = (float)(dVar4 * dVar3 + (double)*(float *)(param_1 + 0x2e8));
  *(float *)(param_1 + 0x2ec) =
       *(float *)(param_1 + 0x2ec) +
       *(float *)(param_1 + 0x3d8) * *(float *)(param_1 + 0x354) + *(float *)(param_1 + 0x3d0);
  dVar3 = zz_0045238_(sVar2);
  *(float *)(param_1 + 0x2f0) = (float)(dVar4 * dVar3 + (double)*(float *)(param_1 + 0x2f0));
  zz_0010664_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2208-2215 ==== */
// ==== 8000eee8  FUN_8000eee8 ====

void FUN_8000eee8(int param_1)

{
  (*(code *)(&PTR_FUN_804335c8)[*(char *)(param_1 + 0x19)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2219-2255 ==== */
// ==== 8000ef20  FUN_8000ef20 ====

void FUN_8000ef20(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  if (*(char *)(param_1 + 0x12) != '\0') {
    zz_008b038_('\x02');
  }
  PTR_DAT_80433934[0x1829] = 1;
  FUN_801fe050(0);
  iVar2 = (int)*(char *)(param_2 + 0x3e4);
  *(undefined2 *)(param_1 + 0x1c) = 0x1e;
  uVar1 = (&DAT_803c769c)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x2f4) = (&DAT_803c7698)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x2f8) = uVar1;
  *(undefined4 *)(param_1 + 0x2fc) = (&DAT_803c76a0)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0x2f4);
  *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x2f8);
  *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 0x2fc);
  uVar1 = (&DAT_803c76b4)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x30c) = (&DAT_803c76b0)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x310) = uVar1;
  *(undefined4 *)(param_1 + 0x314) = (&DAT_803c76b8)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_1 + 0x30c);
  *(undefined4 *)(param_1 + 0x304) = *(undefined4 *)(param_1 + 0x310);
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_1 + 0x314);
  uVar1 = (&DAT_803c76e4)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x330) = (&DAT_803c76e0)[iVar2 * 0xf9];
  *(undefined4 *)(param_1 + 0x334) = uVar1;
  *(undefined4 *)(param_1 + 0x338) = (&DAT_803c76e8)[iVar2 * 0xf9];
  FUN_8000f02c(param_1,param_2);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2259-2394 ==== */
// ==== 8000f02c  FUN_8000f02c ====

void FUN_8000f02c(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  short sVar5;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  if (*(char *)(*(int *)(param_1 + 0xcc) + 0x18) != '\x01') {
    *(undefined1 *)(param_1 + 0x18) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_2 + 0x43d) = 0;
    *(undefined1 *)(param_2 + 0x6f8) = 0;
    if (*(char *)(param_1 + 0x12) != '\0') {
      zz_008b038_('\0');
    }
    PTR_DAT_80433934[0x1829] = 0;
    FUN_801fe134();
    zz_0066350_((int)(char)PTR_DAT_80433930[2]);
    return;
  }
  iVar4 = *(int *)(param_1 + 0xcc) + *(char *)(param_1 + 0x89) * 0x30;
  local_18 = *(float *)(iVar4 + 0x8e0);
  local_14 = *(undefined4 *)(iVar4 + 0x8f0);
  local_10 = *(undefined4 *)(iVar4 + 0x900);
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x03') {
LAB_8000f22c:
    sVar5 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar5;
    fVar2 = FLOAT_80436adc;
    if (0 < sVar5) {
      return;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(float *)(param_1 + 0xd4) = fVar2;
  }
  else {
    if (cVar1 < '\x03') {
      if (cVar1 == '\x01') {
LAB_8000f138:
        zz_0046588_((double)(FLOAT_80436ac0 / *(float *)(param_1 + 0xd4)),&local_18,
                    (float *)(param_1 + 0x300),(float *)(param_1 + 0x300));
        fVar2 = FLOAT_80436aa8;
        *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - FLOAT_80436ac0;
        fVar3 = FLOAT_80436adc;
        if (fVar2 < *(float *)(param_1 + 0xd4)) {
          return;
        }
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(float *)(param_1 + 0xd4) = fVar3;
        *(float *)(param_1 + 0x300) = local_18;
        *(undefined4 *)(param_1 + 0x304) = local_14;
        *(undefined4 *)(param_1 + 0x308) = local_10;
        gnt4_PSVECSubtract_bl
                  ((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300),(float *)(param_1 + 0x38));
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),(float *)(param_1 + 0x38),
                         (float *)(param_1 + 0x38));
      }
      else if (cVar1 < '\x01') {
        if (cVar1 < '\0') {
          return;
        }
        sVar5 = *(short *)(param_1 + 0x1c) + -1;
        *(short *)(param_1 + 0x1c) = sVar5;
        fVar2 = FLOAT_80436adc;
        if (0 < sVar5) {
          return;
        }
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(float *)(param_1 + 0xd4) = fVar2;
        goto LAB_8000f138;
      }
      zz_0046588_((double)(FLOAT_80436ac0 / *(float *)(param_1 + 0xd4)),(float *)(param_1 + 0x38),
                  (float *)(param_1 + 0x2e8),(float *)(param_1 + 0x2e8));
      fVar2 = FLOAT_80436aa8;
      *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - FLOAT_80436ac0;
      if (fVar2 < *(float *)(param_1 + 0xd4)) {
        return;
      }
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = *(undefined2 *)(param_1 + 0x1e);
      goto LAB_8000f22c;
    }
    if (cVar1 == '\x05') goto LAB_8000f2f0;
    if ('\x04' < cVar1) {
      return;
    }
  }
  zz_0046588_((double)(FLOAT_80436ac0 / *(float *)(param_1 + 0xd4)),(float *)(param_1 + 0x2f4),
              (float *)(param_1 + 0x2e8),(float *)(param_1 + 0x2e8));
  zz_0046588_((double)(FLOAT_80436ac0 / *(float *)(param_1 + 0xd4)),(float *)(param_1 + 0x30c),
              (float *)(param_1 + 0x300),(float *)(param_1 + 0x300));
  fVar2 = FLOAT_80436aa8;
  *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - FLOAT_80436ac0;
  if (fVar2 < *(float *)(param_1 + 0xd4)) {
    return;
  }
  *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0x2f4);
  *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x2f8);
  *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 0x2fc);
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_1 + 0x30c);
  *(undefined4 *)(param_1 + 0x304) = *(undefined4 *)(param_1 + 0x310);
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_1 + 0x314);
  *(undefined2 *)(param_1 + 0x1c) = 2;
LAB_8000f2f0:
  sVar5 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar5;
  if (sVar5 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_2 + 0x43d) = 0;
    *(undefined1 *)(param_2 + 0x6f8) = 0;
    if (*(char *)(param_1 + 0x12) != '\0') {
      zz_008b038_('\0');
    }
    PTR_DAT_80433934[0x1829] = 0;
    FUN_801fe134();
    zz_0066350_((int)(char)PTR_DAT_80433930[2]);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2398-2405 ==== */
// ==== 8000f36c  FUN_8000f36c ====

void FUN_8000f36c(int param_1)

{
  (*(code *)(&PTR_FUN_804335d0)[*(char *)(param_1 + 0x19)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2409-2435 ==== */
// ==== 8000f3a4  FUN_8000f3a4 ====

void FUN_8000f3a4(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  
  fVar2 = FLOAT_80436ae8;
  cVar1 = *(char *)(param_2 + 0x3e4);
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  iVar4 = (int)cVar1;
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(float *)(param_1 + 0x3d0) = fVar2;
  uVar3 = (&DAT_803c76e4)[iVar4 * 0xf9];
  *(undefined4 *)(param_1 + 0x330) = (&DAT_803c76e0)[iVar4 * 0xf9];
  *(undefined4 *)(param_1 + 0x334) = uVar3;
  *(undefined4 *)(param_1 + 0x338) = (&DAT_803c76e8)[iVar4 * 0xf9];
  FUN_8000f604(param_1,param_2);
  if (FLOAT_80436ae8 < *(float *)(param_1 + 0x350)) {
    *(float *)(param_1 + 0x3d0) = *(float *)(param_1 + 0x350);
    FUN_8000f604(param_1,param_2);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2439-2513 ==== */
// ==== 8000f448  FUN_8000f448 ====

void FUN_8000f448(int param_1,int param_2)

{
  char cVar1;
  float fVar2;
  undefined4 uVar3;
  short sVar5;
  int iVar4;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if ('\x03' < cVar1) {
        return;
      }
      goto LAB_8000f5bc;
    }
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 0x1a) = 1;
      *(undefined2 *)(param_1 + 0x1c) = 0x118;
    }
    else if (cVar1 < '\0') {
      return;
    }
    FUN_8000f604(param_1,param_2);
    sVar5 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar5;
    fVar2 = FLOAT_80436adc;
    if (0 < sVar5) {
      return;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(float *)(param_1 + 0xd4) = fVar2;
    iVar4 = (int)*(char *)(param_2 + 0x3e4);
    uVar3 = (&DAT_803c769c)[iVar4 * 0xf9];
    *(undefined4 *)(param_1 + 0x2f4) = (&DAT_803c7698)[iVar4 * 0xf9];
    *(undefined4 *)(param_1 + 0x2f8) = uVar3;
    *(undefined4 *)(param_1 + 0x2fc) = (&DAT_803c76a0)[iVar4 * 0xf9];
    uVar3 = (&DAT_803c76b4)[iVar4 * 0xf9];
    *(undefined4 *)(param_1 + 0x30c) = (&DAT_803c76b0)[iVar4 * 0xf9];
    *(undefined4 *)(param_1 + 0x310) = uVar3;
    *(undefined4 *)(param_1 + 0x314) = (&DAT_803c76b8)[iVar4 * 0xf9];
  }
  zz_0046588_((double)(FLOAT_80436ac0 / *(float *)(param_1 + 0xd4)),(float *)(param_1 + 0x2f4),
              (float *)(param_1 + 0x2e8),(float *)(param_1 + 0x2e8));
  zz_0046588_((double)(FLOAT_80436ac0 / *(float *)(param_1 + 0xd4)),(float *)(param_1 + 0x30c),
              (float *)(param_1 + 0x300),(float *)(param_1 + 0x300));
  fVar2 = FLOAT_80436aa8;
  *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - FLOAT_80436ac0;
  if (fVar2 < *(float *)(param_1 + 0xd4)) {
    return;
  }
  *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0x2f4);
  *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x2f8);
  *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 0x2fc);
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(param_1 + 0x30c);
  *(undefined4 *)(param_1 + 0x304) = *(undefined4 *)(param_1 + 0x310);
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(param_1 + 0x314);
  *(undefined2 *)(param_1 + 0x1c) = 2;
LAB_8000f5bc:
  sVar5 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar5;
  if (sVar5 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_2 + 0x43d) = 0;
    *(undefined1 *)(param_2 + 0x6f8) = 0;
  }
  return;
}
