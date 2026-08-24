#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
uint zz_00bdd9c_(int param_1,undefined4 *param_2,undefined1 param_3);
void FUN_800bdec4(int param_1);
void FUN_800bdf00(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_800be0a4(int param_1);
void FUN_800be184(int param_1);
void FUN_800be1cc(int param_1);
void FUN_800be1f4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void FUN_800be23c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2364-2401 ==== */
// ==== 800bdd9c  zz_00bdd9c_ ====

uint zz_00bdd9c_(int param_1,undefined4 *param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  puVar1 = zz_008893c_(3,8,1,5);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x49;
    puVar1[0x11] = param_3;
    uVar2 = param_2[1];
    *(undefined4 *)(puVar1 + 0x20) = *param_2;
    *(undefined4 *)(puVar1 + 0x24) = uVar2;
    *(undefined4 *)(puVar1 + 0x28) = param_2[2];
    *(code **)(puVar1 + 0xc) = FUN_800bdec4;
    *(code **)(puVar1 + 0x10c) = FUN_800be23c;
    *(int *)(puVar1 + 0x8c) = param_1;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
  }
  return (-(int)puVar1 | (uint)puVar1) >> 0x1f;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2405-2412 ==== */
// ==== 800bdec4  FUN_800bdec4 ====

void FUN_800bdec4(int param_1)

{
  (*(code *)(&PTR_FUN_80301a98)[*(char *)(param_1 + 0x18)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2416-2476 ==== */
// ==== 800bdf00  FUN_800bdf00 ====

void FUN_800bdf00(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  iVar2 = -((int)(char)(&DAT_80301a11)[iVar5] >> 0x1f);
  if (iVar2 == 0) {
    iVar2 = zz_008ae10_(param_9,(&DAT_80301a11)[iVar5]);
  }
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    iVar2 = *(int *)(param_9 + 0x90);
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    piVar3 = zz_0006dc8_(0xa0);
    *(int **)(param_9 + 0xdc) = piVar3;
    *(undefined1 *)(param_9 + 0x13) = 0x10;
    *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(param_9 + 0xb4);
    *(float *)(param_9 + 0x148) = *(float *)(&DAT_80301a14 + iVar5) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x14c) = *(float *)(&DAT_80301a18 + iVar5) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x150) = *(float *)(&DAT_80301a1c + iVar5) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x154) = *(float *)(&DAT_80301a20 + iVar5) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x158) = *(float *)(&DAT_80301a24 + iVar5) * *(float *)(param_9 + 0x144);
    *(float *)(param_9 + 0x15c) = *(float *)(&DAT_80301a28 + iVar5) * *(float *)(param_9 + 0x144);
    *(int *)(param_9 + 0x160) = (int)*(short *)(&DAT_80301a12 + iVar5);
    uVar4 = zz_00055fc_();
    *(short *)(param_9 + 0x72) = (short)(uVar4 << 8);
    uVar1 = *(undefined4 *)(param_9 + 0x148);
    uVar6 = 1;
    *(undefined4 *)(param_9 + 0x60) = uVar1;
    *(undefined4 *)(param_9 + 0x5c) = uVar1;
    *(undefined4 *)(param_9 + 0x58) = uVar1;
    *(undefined4 *)(param_9 + 0xb4) = uVar1;
    *(undefined4 *)(param_9 + 0xc0) = uVar1;
    *(code **)(param_9 + 0x100) = FUN_800be314;
    uVar7 = zz_0089100_(param_9,1,1);
    zz_00be36c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar6,
                param_12,param_13,param_14,param_15,param_16);
    uVar7 = zz_0040d64_((int)*(char *)(iVar2 + 0x3e4),1);
    zz_0006fb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xf0),(uint)(byte)(&DAT_80301a10)[iVar5],param_12,param_13,
                param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
    zz_00f0468_(0,0xfd,(int)*(char *)(param_9 + 0x96));
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2480-2496 ==== */
// ==== 800be0a4  FUN_800be0a4 ====

void FUN_800be0a4(int param_1)

{
  undefined4 uVar1;
  
  (*(code *)(&PTR_LAB_80433b08)[*(char *)(param_1 + 0x19)])();
  uVar1 = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 0x60) = uVar1;
  *(undefined4 *)(param_1 + 0x5c) = uVar1;
  *(undefined4 *)(param_1 + 0x58) = uVar1;
  *(undefined4 *)(param_1 + 0xb4) = uVar1;
  *(undefined4 *)(param_1 + 0xc0) = uVar1;
  zz_00be484_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2500-2511 ==== */
// ==== 800be184  FUN_800be184 ====

void FUN_800be184(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x19) = 0;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x13) = 0;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2515-2523 ==== */
// ==== 800be1cc  FUN_800be1cc ====

void FUN_800be1cc(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2527-2539 ==== */
// ==== 800be1f4  FUN_800be1f4 ====

void FUN_800be1f4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 2543-2589 ==== */
// ==== 800be23c  FUN_800be23c ====

void FUN_800be23c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  float afStack_48 [13];
  
  if ((*(byte *)(param_9 + 0x13) & 0x10) != 0) {
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xf0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xf0),0x44);
  }
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar3 = 0;
    iVar5 = 0;
    iVar4 = param_9;
    do {
      if (((int)*(char *)(param_9 + 0x13) & 1 << iVar3) != 0) {
        iVar1 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc);
        dVar7 = (double)*(float *)(param_9 + 0x24);
        dVar8 = (double)*(float *)(param_9 + 0x28);
        gnt4_PSMTXTrans_bl((double)*(float *)(param_9 + 0x20),dVar7,dVar8,afStack_48);
        pfVar2 = (float *)(iVar1 + iVar5 + 0x10);
        uVar6 = zz_00456a0_(afStack_48,afStack_48,pfVar2);
        zz_00076d0_(uVar6,dVar7,dVar8,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar4 + 0xe0)
                    ,afStack_48,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
        zz_00097b4_(*(int *)(iVar4 + 0xe0),0x44);
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 4;
      iVar5 = iVar5 + 0x28;
    } while (iVar3 < 4);
  }
  return;
}
