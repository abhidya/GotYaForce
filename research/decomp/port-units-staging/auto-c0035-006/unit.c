#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01330b4_(int param_1);
void zz_01330cc_(int param_1,int param_2);
void zz_01332dc_(int param_1);
void FUN_80133358(double param_1,int param_2);
void FUN_80133504(int param_1);
void FUN_80133510(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void FUN_80133530(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_013358c_(int param_1,undefined1 param_2);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1654-1661 ==== */
// ==== 801330b4  zz_01330b4_ ====

void zz_01330b4_(int param_1)

{
  **(byte **)(param_1 + 0x164) = **(byte **)(param_1 + 0x164) | *(byte *)(param_1 + 0x168);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1665-1738 ==== */
// ==== 801330cc  zz_01330cc_ ====

/* WARNING: Removing unreachable block (ram,0x801332b8) */
/* WARNING: Removing unreachable block (ram,0x801330dc) */

void zz_01330cc_(int param_1,int param_2)

{
  int iVar1;
  float *pfVar2;
  double dVar3;
  double dVar4;
  float local_b8;
  undefined4 local_b4;
  undefined4 local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float afStack_a0 [12];
  float afStack_70 [2];
  float local_68;
  float local_58;
  float local_48;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  
  uStack_3c = (int)*(short *)(param_1 + 0x1c) ^ 0x80000000;
  local_40 = 0x43300000;
  iVar1 = *(char *)(param_1 + 0x11) * 0x24;
  dVar3 = (double)((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_80439ee8) /
                  FLOAT_80439ef8);
  pfVar2 = (float *)(*(int *)(param_1 + 0x90) + (char)(&DAT_80336561)[iVar1] * 0x30 + 0x8d4);
  gnt4_PSMTXMultVec_bl(pfVar2,(float *)(iVar1 + param_2 * 0xc + -0x7fcc9a9c),&local_ac);
  zz_0046588_(dVar3,(float *)(param_1 + 0x20),&local_ac,(float *)(param_1 + 0x20));
  local_38 = 0x43300000;
  uStack_34 = (int)*(short *)(&DAT_80336580 + iVar1) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80439ed8 *
                              (float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80439ee8)),
                      afStack_a0,0x7a);
  gnt4_PSMTXConcat_bl(pfVar2,afStack_a0,afStack_70);
  local_30 = 0x43300000;
  uStack_2c = (int)*(short *)(&DAT_8033657e + iVar1) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80439ed8 *
                              (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80439ee8)),
                      afStack_a0,0x79);
  gnt4_PSMTXConcat_bl(afStack_70,afStack_a0,afStack_70);
  local_28 = 0x43300000;
  uStack_24 = (int)*(short *)(&DAT_8033657c + iVar1) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80439ed8 *
                              (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_80439ee8)),
                      afStack_a0,0x78);
  gnt4_PSMTXConcat_bl(afStack_70,afStack_a0,afStack_70);
  local_ac = local_68;
  local_a8 = local_58;
  local_a4 = local_48;
  local_b8 = *(float *)(param_1 + 0x11c);
  local_b4 = *(undefined4 *)(param_1 + 300);
  local_b0 = *(undefined4 *)(param_1 + 0x13c);
  zz_0046588_(dVar3,&local_b8,&local_ac,&local_ac);
  dVar4 = (double)local_a8;
  local_a8 = FLOAT_80439ee0;
  dVar3 = gnt4_PSVECMag_bl(&local_ac);
  iVar1 = FUN_800452a0(-dVar4,dVar3);
  *(short *)(param_1 + 0x70) = (short)iVar1;
  iVar1 = FUN_800452a0((double)local_ac,(double)local_a4);
  *(short *)(param_1 + 0x72) = (short)iVar1;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1742-1762 ==== */
// ==== 801332dc  zz_01332dc_ ====

void zz_01332dc_(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_00055fc_();
  uVar1 = uVar1 & 0xf;
  if (uVar1 == (int)*(char *)(param_1 + 0x1a)) {
    uVar1 = uVar1 + 1 & 0xf;
  }
  *(char *)(param_1 + 0x1a) = (char)uVar1;
  *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x28);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1766-1825 ==== */
// ==== 80133358  FUN_80133358 ====

/* WARNING: Removing unreachable block (ram,0x801334e8) */
/* WARNING: Removing unreachable block (ram,0x80133368) */

void FUN_80133358(double param_1,int param_2)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  float local_a8;
  float local_a4;
  float local_a0;
  float afStack_9c [12];
  float afStack_6c [3];
  undefined4 local_60;
  undefined4 local_50;
  undefined4 local_40;
  undefined4 local_38;
  uint uStack_34;
  
  iVar4 = *(int *)(param_2 + 0xcc);
  iVar1 = *(char *)(param_2 + 0x12) * 0x28;
  if ((iVar4 != 0) && (iVar3 = *(int *)(param_2 + 200), iVar3 != 0)) {
    pfVar2 = (float *)((char)(&DAT_8033692d)[iVar1] * 0x80 + -0x7fcc95e0 +
                      *(char *)(param_2 + 0x1a) * 8);
    gnt4_PSMTXRotRad_bl((double)*pfVar2,afStack_6c,0x78);
    gnt4_PSMTXRotRad_bl((double)pfVar2[1],afStack_9c,0x79);
    gnt4_PSMTXConcat_bl(afStack_9c,afStack_6c,afStack_6c);
    local_a8 = FLOAT_80439ee0;
    local_a4 = FLOAT_80439ee0;
    if ((*(char *)(iVar4 + 0x83) == '\0') && (*(int *)(iVar4 + 0x4b0) != 0)) {
      local_a0 = FLOAT_80439efc * *(float *)(*(int *)(iVar4 + 0x4b0) + 0x44);
    }
    else {
      local_a0 = FLOAT_80439f00;
    }
    local_a0 = (float)((double)(local_a0 * *(float *)(iVar4 + 0xb4)) + param_1);
    if ((&DAT_8033692d)[iVar1] == '\x01') {
      iVar1 = *(int *)(param_2 + 0x90);
      local_60 = *(undefined4 *)(iVar1 + 0xa60);
      local_50 = *(undefined4 *)(iVar1 + 0xa70);
      local_40 = *(undefined4 *)(iVar1 + 0xa80);
    }
    else {
      local_60 = *(undefined4 *)(iVar3 + 100);
      local_50 = *(undefined4 *)(iVar3 + 0x68);
      local_40 = *(undefined4 *)(iVar3 + 0x6c);
    }
    gnt4_PSMTXMultVec_bl(afStack_6c,&local_a8,(float *)(param_2 + 0x158));
  }
  local_38 = 0x43300000;
  uStack_34 = (int)*(short *)(param_2 + 0x1c) ^ 0x80000000;
  zz_0046588_((double)((float)((double)CONCAT44(0x43300000,uStack_34) - DOUBLE_80439ee8) /
                      FLOAT_80439ef8),(float *)(param_2 + 0x14c),(float *)(param_2 + 0x158),
              (float *)(param_2 + 0x20));
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1829-1836 ==== */
// ==== 80133504  FUN_80133504 ====

void FUN_80133504(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1840-1848 ==== */
// ==== 80133510  FUN_80133510 ====

void FUN_80133510(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1852-1873 ==== */
// ==== 80133530  FUN_80133530 ====

void FUN_80133530(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_9 + 0x90);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  uVar1 = 1;
  if (*(char *)(iVar2 + 0x3ec) == '\x04') {
    uVar1 = 0x44;
  }
  zz_00097b4_(*(int *)(param_9 + 0xe0),uVar1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1877-1910 ==== */
// ==== 8013358c  zz_013358c_ ====

void zz_013358c_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((sVar1 == 0x302) || (sVar1 == 0x306)) || (sVar1 == 0x307)) || (sVar1 == 0x30d)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,6), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x11] = param_2;
    *(code **)(puVar2 + 0xc) = FUN_801336a4;
    *(code **)(puVar2 + 0x10c) = FUN_80133cbc;
    *(int *)(puVar2 + 0x8c) = param_1;
    *(undefined4 *)(puVar2 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar2 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar2[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar2[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar2[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar2 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar2 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar2 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar2 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar2 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar2[0xd0] = *(undefined1 *)(param_1 + 0xd0);
  }
  return;
}
