#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_0185044_(int param_1);
void FUN_80185068(int param_1,int param_2);
void zz_0185284_(int param_1);
void FUN_80185300(double param_1,int param_2);
void FUN_80185470(int param_1);
void FUN_8018547c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void FUN_8018549c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_801855f4(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0046.c 1-9 ==== */
// ==== 80185044  zz_0185044_ ====

void zz_0185044_(int param_1)

{
  **(byte **)(param_1 + 0x164) =
       **(byte **)(param_1 + 0x164) | (byte)(1 << (*(byte *)(param_1 + 0x13) & 3));
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0046.c 13-84 ==== */
// ==== 80185068  FUN_80185068 ====

/* WARNING: Removing unreachable block (ram,0x80185260) */
/* WARNING: Removing unreachable block (ram,0x80185258) */
/* WARNING: Removing unreachable block (ram,0x80185250) */
/* WARNING: Removing unreachable block (ram,0x80185088) */
/* WARNING: Removing unreachable block (ram,0x80185080) */
/* WARNING: Removing unreachable block (ram,0x80185078) */

void FUN_80185068(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float local_c8;
  float local_c4;
  float local_c0;
  float afStack_bc [2];
  float local_b4;
  float local_a4;
  float local_94;
  undefined4 local_88;
  uint uStack_84;
  undefined4 local_80;
  uint uStack_7c;
  
  uStack_84 = (int)*(short *)(param_1 + 0x1c) ^ 0x80000000;
  local_88 = 0x43300000;
  iVar1 = param_2 * 0x18 + *(char *)(param_1 + 0x13) * 0x30;
  dVar7 = (double)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,uStack_84)) - DOUBLE_8043af20) /
                  FLOAT_8043af30);
  pfVar3 = (float *)(*(int *)(param_1 + 0x90) + *(short *)(&DAT_8035c3b0 + iVar1 + 2) * 0x30 + 0x8d4
                    );
  dVar6 = (double)(float)((double)FLOAT_8043af34 - dVar7);
  gnt4_PSMTXCopy_bl(pfVar3,(float *)(param_1 + 0x114));
  gnt4_PSMTXMultVec_bl(pfVar3,(float *)(&DAT_8035c3b0 + iVar1 + 4),&local_c8);
  zz_0046588_(dVar7,(float *)(param_1 + 0x20),&local_c8,(float *)(param_1 + 0x20));
  local_80 = 0x43300000;
  uStack_7c = (int)*(short *)(&DAT_8035c3b0 + iVar1 + 0x10) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_8043af14 *
                              (float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,uStack_7c)) - DOUBLE_8043af20)),
                      afStack_bc,0x78);
  gnt4_PSMTXConcat_bl(pfVar3,afStack_bc,afStack_bc);
  dVar5 = (double)local_a4;
  local_c8 = local_b4;
  local_c0 = local_94;
  local_c4 = FLOAT_8043af1c;
  dVar4 = gnt4_PSVECMag_bl(&local_c8);
  iVar1 = FUN_800452a0(-dVar5,dVar4);
  iVar2 = FUN_800452a0((double)local_c8,(double)local_c0);
  dVar5 = DOUBLE_8043af20;
  dVar4 = __gnt4_bitcast_f64(CONCAT44(0x43300000,(int)(short)iVar2 ^ 0x80000000)) - DOUBLE_8043af20;
  *(short *)(param_1 + 0x70) =
       (short)(int)(dVar7 * (double)(float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                                             (int)*(short *)(param_1 + 0x70) ^
                                                             0x80000000)) - DOUBLE_8043af20) +
                   (double)(float)(dVar6 * (double)(float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                                                            (int)(short)iVar1 ^
                                                                            0x80000000)) -
                                                          DOUBLE_8043af20)));
  *(short *)(param_1 + 0x72) =
       (short)(int)(dVar7 * (double)(float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,
                                                             (int)*(short *)(param_1 + 0x72) ^
                                                             0x80000000)) - dVar5) +
                   (double)(float)(dVar6 * (double)(float)dVar4));
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0046.c 88-108 ==== */
// ==== 80185284  zz_0185284_ ====

void zz_0185284_(int param_1)

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

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0046.c 112-160 ==== */
// ==== 80185300  FUN_80185300 ====

/* WARNING: Removing unreachable block (ram,0x80185448) */
/* WARNING: Removing unreachable block (ram,0x80185310) */

void FUN_80185300(double param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float local_98;
  float local_94;
  float local_90;
  float afStack_8c [12];
  float afStack_5c [3];
  undefined4 local_50;
  undefined4 local_40;
  undefined4 local_30;
  undefined4 local_28;
  uint uStack_24;
  
  iVar3 = *(int *)(param_2 + 0xcc);
  if ((iVar3 != 0) && (iVar2 = *(int *)(param_2 + 200), iVar2 != 0)) {
    iVar1 = *(char *)(param_2 + 0x1a) * 8;
    gnt4_PSMTXRotRad_bl((double)*(float *)(&DAT_8035c6f0 + iVar1),afStack_5c,0x78);
    gnt4_PSMTXRotRad_bl((double)*(float *)(&DAT_8035c6f4 + iVar1),afStack_8c,0x79);
    gnt4_PSMTXConcat_bl(afStack_8c,afStack_5c,afStack_5c);
    local_50 = *(undefined4 *)(iVar2 + 100);
    local_40 = *(undefined4 *)(iVar2 + 0x68);
    local_30 = *(undefined4 *)(iVar2 + 0x6c);
    local_98 = FLOAT_8043af1c;
    local_94 = FLOAT_8043af1c;
    if ((*(char *)(iVar3 + 0x83) == '\0') && (*(int *)(iVar3 + 0x4b0) != 0)) {
      local_90 = FLOAT_8043af38 * *(float *)(*(int *)(iVar3 + 0x4b0) + 0x44);
    }
    else {
      local_90 = FLOAT_8043af3c;
    }
    local_90 = (float)((double)(local_90 * *(float *)(iVar3 + 0xb4)) + param_1);
    gnt4_PSMTXMultVec_bl(afStack_5c,&local_98,(float *)(param_2 + 0x158));
  }
  local_28 = 0x43300000;
  uStack_24 = (int)*(short *)(param_2 + 0x1c) ^ 0x80000000;
  zz_0046588_((double)((float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,uStack_24)) - DOUBLE_8043af20) /
                      FLOAT_8043af30),(float *)(param_2 + 0x14c),(float *)(param_2 + 0x158),
              (float *)(param_2 + 0x20));
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0046.c 164-171 ==== */
// ==== 80185470  FUN_80185470 ====

void FUN_80185470(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0046.c 175-183 ==== */
// ==== 8018547c  FUN_8018547c ====

void FUN_8018547c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0046.c 187-208 ==== */
// ==== 8018549c  FUN_8018549c ====

void FUN_8018549c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0046.c 212-219 ==== */
// ==== 801855f4  FUN_801855f4 ====

void FUN_801855f4(int param_1)

{
  zz_00c74ec_(param_1,0x10);
  return;
}
