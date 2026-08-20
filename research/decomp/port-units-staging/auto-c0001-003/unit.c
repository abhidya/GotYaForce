#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_8000e28c(int param_1);
void FUN_8000e2c4(int param_1,int param_2);
void FUN_8000e4f4(int param_1);
void FUN_8000e560(int param_1,int param_2);
void zz_000e5f8_(int param_1,int param_2);
void FUN_8000e950(int param_1,int param_2);
void FUN_8000eaf4(int param_1);
void FUN_8000eb2c(int param_1,int param_2);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 1714-1721 ==== */
// ==== 8000e28c  FUN_8000e28c ====

void FUN_8000e28c(int param_1)

{
  (*(code *)(&PTR_FUN_804335b8)[*(char *)(param_1 + 0x19)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 1725-1798 ==== */
// ==== 8000e2c4  FUN_8000e2c4 ====

void FUN_8000e2c4(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  int iVar6;
  float local_18;
  float local_14;
  undefined4 local_10;
  
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined1 *)(param_1 + 0x1b) = 0;
  iVar5 = *(int *)(PTR_DAT_80433934 + 0xb8);
  if (iVar5 == 0) {
    *(int *)(param_1 + 0x3c8) = param_2;
    iVar5 = param_2;
  }
  else {
    *(int *)(param_1 + 0x3c8) = iVar5;
  }
  iVar6 = *(int *)(PTR_DAT_80433934 + 0xb4);
  if (iVar6 == 0) {
    *(int *)(param_1 + 0x3c4) = iVar5;
    iVar6 = iVar5;
  }
  else {
    *(int *)(param_1 + 0x3c4) = iVar6;
  }
  fVar1 = FLOAT_80436ac4;
  *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(iVar5 + 0x8a0);
  fVar4 = FLOAT_80436b20;
  fVar3 = FLOAT_80436b1c;
  fVar2 = FLOAT_80436b18;
  *(float *)(param_1 + 0x350) =
       fVar1 * *(float *)(iVar5 + *(char *)(param_2 + 0x582) * 4 + 0x88c) *
       (*(float *)(iVar5 + 0x668) / *(float *)(*(int *)(iVar5 + 0x4b0) + 0x4c));
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(iVar5 + 0x20);
  *(float *)(param_1 + 0x304) = *(float *)(iVar5 + 0x24) + *(float *)(param_1 + 0x350);
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(iVar5 + 0x28);
  *(float *)(param_1 + 0x348) = fVar2 * ((fVar3 * *(float *)(iVar5 + 0x668)) / fVar4);
  if (iVar6 == 0) {
    local_18 = *(float *)(param_2 + 0x8dc);
    local_10 = *(undefined4 *)(param_2 + 0x8fc);
    local_14 = FLOAT_80436aa8;
    FUN_800452e4((double)FLOAT_80436aec,&local_18,*(short *)(iVar5 + 0x72));
    zz_00453fc_('y',&local_18,&local_18,0x4000);
    gnt4_PSVECNormalize_bl(&local_18,&local_18);
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_18,&local_18);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),&local_18,(float *)(param_1 + 0x2e8));
  }
  else {
    gnt4_PSVECSubtract_bl((float *)(iVar6 + 0x20),(float *)(iVar5 + 0x20),&local_18);
    local_14 = FLOAT_80436aa8;
    gnt4_PSQUATScale_bl((double)FLOAT_80436ac4,&local_18,&local_18);
    FUN_800452e4((double)FLOAT_80436aec,&local_18,*(short *)(iVar5 + 0x72));
    zz_00453fc_('y',&local_18,&local_18,0x4000);
    gnt4_PSVECNormalize_bl(&local_18,&local_18);
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x348),&local_18,&local_18);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),&local_18,(float *)(param_1 + 0x2e8));
  }
  *(undefined4 *)(param_1 + 0x30c) = *(undefined4 *)(param_1 + 0x300);
  *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(param_1 + 0x304);
  *(undefined4 *)(param_1 + 0x314) = *(undefined4 *)(param_1 + 0x308);
  *(undefined4 *)(param_1 + 0x2f4) = *(undefined4 *)(param_1 + 0x2e8);
  *(undefined4 *)(param_1 + 0x2f8) = *(undefined4 *)(param_1 + 0x2ec);
  *(undefined4 *)(param_1 + 0x2fc) = *(undefined4 *)(param_1 + 0x2f0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 1802-1815 ==== */
// ==== 8000e4f4  FUN_8000e4f4 ====

void FUN_8000e4f4(int param_1)

{
  *(undefined4 *)(param_1 + 0x30c) = *(undefined4 *)(param_1 + 0x300);
  *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(param_1 + 0x304);
  *(undefined4 *)(param_1 + 0x314) = *(undefined4 *)(param_1 + 0x308);
  *(undefined4 *)(param_1 + 0x2f4) = *(undefined4 *)(param_1 + 0x2e8);
  *(undefined4 *)(param_1 + 0x2f8) = *(undefined4 *)(param_1 + 0x2ec);
  *(undefined4 *)(param_1 + 0x2fc) = *(undefined4 *)(param_1 + 0x2f0);
  (*(code *)(&PTR_FUN_802c392c)[*(char *)(param_1 + 0x1a)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 1819-1848 ==== */
// ==== 8000e560  FUN_8000e560 ====

void FUN_8000e560(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  
  fVar4 = FLOAT_80436ae8;
  fVar3 = FLOAT_80436acc;
  if (PTR_DAT_80433934[0x52] == '\x04') {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined1 *)(param_1 + 0x1b) = 0;
    zz_000e5f8_(param_1,param_2);
  }
  else {
    iVar5 = *(int *)(param_1 + 0x3c8);
    fVar1 = *(float *)(iVar5 + 0x24);
    fVar2 = *(float *)(iVar5 + 0x28);
    *(float *)(param_1 + 0x300) =
         (FLOAT_80436acc * *(float *)(param_1 + 0x30c) + *(float *)(iVar5 + 0x20)) / FLOAT_80436ae8;
    *(float *)(param_1 + 0x308) = (fVar3 * *(float *)(param_1 + 0x314) + fVar2) / fVar4;
    *(float *)(param_1 + 0x304) =
         (fVar3 * *(float *)(param_1 + 0x310) + fVar1 + *(float *)(param_1 + 0x350)) / fVar4;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 1852-1971 ==== */
// ==== 8000e5f8  zz_000e5f8_ ====

void zz_000e5f8_(int param_1,int param_2)

{
  float fVar1;
  short sVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float afStack_54 [3];
  float local_48;
  float local_44;
  float local_40;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  undefined4 local_20;
  uint uStack_1c;
  undefined4 local_18;
  uint uStack_14;
  undefined4 local_10;
  uint uStack_c;
  
  iVar3 = *(int *)(param_1 + 0x3c4);
  if (*(char *)(param_1 + 0x1b) == '\0') {
    *(undefined1 *)(param_1 + 0x1b) = 1;
    fVar1 = FLOAT_80436b28;
    *(undefined2 *)(param_1 + 0x1c) = 0x28;
    *(float *)(param_1 + 0x350) =
         fVar1 * *(float *)(iVar3 + *(char *)(param_2 + 0x582) * 4 + 0x88c) *
         (*(float *)(iVar3 + 0x668) / *(float *)(*(int *)(iVar3 + 0x4b0) + 0x4c));
    local_48 = *(float *)(iVar3 + 0x20);
    local_44 = *(float *)(iVar3 + 0x24) + *(float *)(param_1 + 0x350);
    local_40 = *(float *)(iVar3 + 0x28);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x300),&local_48,afStack_54);
    dVar4 = gnt4_PSVECMag_bl(afStack_54);
    if ((double)*(float *)(param_2 + 0x894) <= dVar4) {
      *(undefined4 *)(param_1 + 0x3cc) = *(undefined4 *)(param_1 + 0x300);
      *(undefined4 *)(param_1 + 0x3d0) = *(undefined4 *)(param_1 + 0x304);
      *(undefined4 *)(param_1 + 0x3d4) = *(undefined4 *)(param_1 + 0x308);
    }
    else {
      gnt4_PSVECNormalize_bl(afStack_54,afStack_54);
      gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x894),afStack_54,afStack_54);
      gnt4_PSVECAdd_bl(&local_48,afStack_54,(float *)(param_1 + 0x3cc));
      zz_0010664_(param_1);
    }
  }
  else {
    local_48 = *(float *)(iVar3 + 0x20);
    local_44 = *(float *)(iVar3 + 0x24) + *(float *)(param_1 + 0x350);
    local_40 = *(float *)(iVar3 + 0x28);
  }
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  dVar4 = DOUBLE_80436b30;
  if (sVar2 == 0) {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0x3cc);
    *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x3d0);
    *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 0x3d4);
    *(float *)(param_1 + 0x300) = local_48;
    *(float *)(param_1 + 0x304) = local_44;
    *(float *)(param_1 + 0x308) = local_40;
  }
  else {
    local_38 = 0x43300000;
    uStack_34 = (int)*(short *)(param_1 + 0x1c) + 1U ^ 0x80000000;
    local_30 = 0x43300000;
    local_28 = 0x43300000;
    local_20 = 0x43300000;
    local_18 = 0x43300000;
    local_10 = 0x43300000;
    *(float *)(param_1 + 0x2e8) =
         *(float *)(param_1 + 0x2f4) +
         (*(float *)(param_1 + 0x3cc) - *(float *)(param_1 + 0x2f4)) /
         (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80436b30);
    uStack_2c = (int)*(short *)(param_1 + 0x1c) + 1U ^ 0x80000000;
    *(float *)(param_1 + 0x2ec) =
         *(float *)(param_1 + 0x2f8) +
         (*(float *)(param_1 + 0x3d0) - *(float *)(param_1 + 0x2f8)) /
         (float)((double)CONCAT44(0x43300000,uStack_2c) - dVar4);
    uStack_24 = (int)*(short *)(param_1 + 0x1c) + 1U ^ 0x80000000;
    *(float *)(param_1 + 0x2f0) =
         *(float *)(param_1 + 0x2fc) +
         (*(float *)(param_1 + 0x3d4) - *(float *)(param_1 + 0x2fc)) /
         (float)((double)CONCAT44(0x43300000,uStack_24) - dVar4);
    uStack_1c = (int)*(short *)(param_1 + 0x1c) + 1U ^ 0x80000000;
    *(float *)(param_1 + 0x300) =
         *(float *)(param_1 + 0x30c) +
         (local_48 - *(float *)(param_1 + 0x30c)) /
         (float)((double)CONCAT44(0x43300000,uStack_1c) - dVar4);
    uStack_14 = (int)*(short *)(param_1 + 0x1c) + 1U ^ 0x80000000;
    *(float *)(param_1 + 0x304) =
         *(float *)(param_1 + 0x310) +
         (local_44 - *(float *)(param_1 + 0x310)) /
         (float)((double)CONCAT44(0x43300000,uStack_14) - dVar4);
    uStack_c = (int)*(short *)(param_1 + 0x1c) + 1U ^ 0x80000000;
    *(float *)(param_1 + 0x308) =
         *(float *)(param_1 + 0x314) +
         (local_40 - *(float *)(param_1 + 0x314)) /
         (float)((double)CONCAT44(0x43300000,uStack_c) - dVar4);
  }
  zz_00106fc_(param_1,param_2,(float *)(param_1 + 0x2e8));
  dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300));
  if ((double)FLOAT_80436aa8 < dVar4) {
    dVar5 = 1.0 / SQRT(dVar4);
    dVar5 = DOUBLE_80436ab0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436ab8);
    dVar5 = DOUBLE_80436ab0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436ab8);
    dVar4 = (double)(float)(dVar4 * DOUBLE_80436ab0 * dVar5 *
                                    -(dVar4 * dVar5 * dVar5 - DOUBLE_80436ab8));
  }
  *(float *)(param_1 + 0x348) = (float)dVar4;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 1975-2026 ==== */
// ==== 8000e950  FUN_8000e950 ====

/* WARNING: Removing unreachable block (ram,0x8000ead4) */
/* WARNING: Removing unreachable block (ram,0x8000eacc) */
/* WARNING: Removing unreachable block (ram,0x8000e968) */
/* WARNING: Removing unreachable block (ram,0x8000e960) */

void FUN_8000e950(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float afStack_44 [3];
  float local_38;
  float local_34;
  float local_30;
  
  iVar3 = *(int *)(param_1 + 0x3c4);
  dVar4 = (double)*(float *)(iVar3 + 0x898);
  dVar5 = (double)*(float *)(iVar3 + 0x894);
  *(undefined4 *)(param_1 + 0x300) = *(undefined4 *)(iVar3 + 0x20);
  *(float *)(param_1 + 0x304) = *(float *)(iVar3 + 0x24) + *(float *)(param_1 + 0x350);
  *(undefined4 *)(param_1 + 0x308) = *(undefined4 *)(iVar3 + 0x28);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300),afStack_44);
  gnt4_PSVECNormalize_bl(afStack_44,afStack_44);
  gnt4_PSQUATScale_bl(dVar5,afStack_44,afStack_44);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x300),afStack_44,&local_38);
  if ((*(char *)(param_1 + 0x1b) != '\0') || ((double)*(float *)(param_1 + 0x348) < dVar4)) {
    *(undefined1 *)(param_1 + 0x1b) = 1;
    zz_0010664_(param_1);
  }
  fVar2 = FLOAT_80436ae8;
  fVar1 = FLOAT_80436acc;
  *(float *)(param_1 + 0x2e8) =
       (FLOAT_80436acc * *(float *)(param_1 + 0x2f4) + local_38) / FLOAT_80436ae8;
  *(float *)(param_1 + 0x2f0) = (fVar1 * *(float *)(param_1 + 0x2fc) + local_30) / fVar2;
  *(float *)(param_1 + 0x2ec) = (fVar1 * *(float *)(param_1 + 0x2f8) + local_34) / fVar2;
  zz_00106fc_(param_1,param_2,(float *)(param_1 + 0x2e8));
  dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x2e8),(float *)(param_1 + 0x300));
  if ((double)FLOAT_80436aa8 < dVar4) {
    dVar5 = 1.0 / SQRT(dVar4);
    dVar5 = DOUBLE_80436ab0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436ab8);
    dVar5 = DOUBLE_80436ab0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436ab8);
    dVar4 = (double)(float)(dVar4 * DOUBLE_80436ab0 * dVar5 *
                                    -(dVar4 * dVar5 * dVar5 - DOUBLE_80436ab8));
  }
  *(float *)(param_1 + 0x348) = (float)dVar4;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2030-2037 ==== */
// ==== 8000eaf4  FUN_8000eaf4 ====

void FUN_8000eaf4(int param_1)

{
  (*(code *)(&PTR_FUN_804335c0)[*(char *)(param_1 + 0x19)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 2041-2117 ==== */
// ==== 8000eb2c  FUN_8000eb2c ====

void FUN_8000eb2c(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  iVar6 = *(int *)(param_2 + 0x4ac);
  fVar1 = *(float *)(iVar6 + 400) *
          (*(float *)(param_2 + 0x668) / *(float *)(*(int *)(param_2 + 0x4b0) + 0x4c));
  *(float *)(param_1 + 0x3d4) = fVar1;
  fVar4 = FLOAT_80436b40;
  fVar3 = FLOAT_80436b38;
  fVar2 = FLOAT_80436ac4;
  if (((int)(char)PTR_DAT_80433934[0x1f] & 1 << (int)*(char *)(param_2 + 0x88)) == 0) {
    if (*(char *)(param_2 + 0x18) == '\x01') {
      fVar2 = FLOAT_80436b38 * fVar1;
      *(undefined1 *)(param_1 + 0x1a) = 1;
      fVar5 = FLOAT_80436b48;
      fVar3 = FLOAT_80436b44;
      *(float *)(param_1 + 0x350) = fVar2;
      *(float *)(param_1 + 0x3d8) = fVar4 * fVar1;
      *(float *)(param_1 + 0x3d0) = fVar3 * fVar1;
      *(undefined2 *)(param_1 + 0x3e2) = 0;
      *(undefined2 *)(param_1 + 0x3e0) = 0;
      *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(iVar6 + 0x194);
      *(undefined4 *)(param_1 + 0x3dc) = *(undefined4 *)(iVar6 + 0x198);
      *(float *)(param_1 + 0x34c) =
           (*(float *)(param_1 + 0x3dc) - *(float *)(param_1 + 0x348)) / fVar5;
    }
    else {
      *(undefined1 *)(param_1 + 0x1a) = 2;
      fVar2 = FLOAT_80436aa8;
      *(float *)(param_1 + 0x350) = fVar3 * fVar1;
      *(float *)(param_1 + 0x3d8) = fVar2;
      *(float *)(param_1 + 0x3d0) = fVar3 * fVar1;
      *(undefined2 *)(param_1 + 0x3e2) = 0;
      *(undefined2 *)(param_1 + 0x3e0) = 0;
      *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(iVar6 + 0x194);
      *(undefined4 *)(param_1 + 0x3dc) = *(undefined4 *)(iVar6 + 0x198);
      *(float *)(param_1 + 0x34c) = fVar2;
    }
  }
  else {
    fVar3 = FLOAT_80436b38 * fVar1;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(float *)(param_1 + 0x350) = fVar3;
    *(float *)(param_1 + 0x3d8) = fVar1;
    *(float *)(param_1 + 0x3d0) = fVar2 * fVar1;
    if ((*(uint *)(PTR_DAT_80433934 + 0xac) & 1) == 0) {
      *(undefined2 *)(param_1 + 0x3e0) = *(undefined2 *)(iVar6 + 0x19e);
    }
    else {
      *(undefined2 *)(param_1 + 0x3e0) = *(undefined2 *)(iVar6 + 0x19c);
    }
    if (*(short *)(param_1 + 0x3e0) < 0) {
      *(undefined2 *)(param_1 + 0x3e2) = 0x7800;
    }
    else {
      *(undefined2 *)(param_1 + 0x3e2) = 0x8800;
    }
    fVar1 = FLOAT_80436ac4;
    *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(iVar6 + 0x194);
    fVar2 = FLOAT_80436b3c;
    *(float *)(param_1 + 0x3dc) = *(float *)(iVar6 + 0x198) * fVar1;
    *(float *)(param_1 + 0x34c) =
         (*(float *)(param_1 + 0x3dc) - *(float *)(param_1 + 0x348)) / fVar2;
  }
  FUN_8000ee04(param_1,param_2);
  return;
}
