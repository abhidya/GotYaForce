#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800c42bc(int param_1);
void FUN_800c4308(int param_1);
void FUN_800c4448(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void FUN_800c4468(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_00c44a8_(int param_1);
void zz_00c4540_(int param_1);
bool zz_00c4704_(int param_1,undefined1 param_2,undefined1 *param_3);
void FUN_800c4838(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 2431-2449 ==== */
// ==== 800c42bc  FUN_800c42bc ====

void FUN_800c42bc(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = FLOAT_80438744;
  fVar2 = *(float *)(param_1 + 0x184) - *(float *)(param_1 + 0x44);
  fVar1 = fVar2 / FLOAT_8043875c;
  *(float *)(param_1 + 0x184) = fVar2;
  *(float *)(param_1 + 0x60) = fVar1;
  if (fVar1 <= fVar3) {
    zz_00c42a8_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 2453-2496 ==== */
// ==== 800c4308  FUN_800c4308 ====

void FUN_800c4308(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x44;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x174));
  if ((double)FLOAT_80438744 < dVar4) {
    dVar5 = 1.0 / SQRT(dVar4);
    dVar5 = DOUBLE_80438748 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80438750);
    dVar5 = DOUBLE_80438748 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80438750);
    dVar4 = (double)(float)(dVar4 * DOUBLE_80438748 * dVar5 *
                                    -(dVar4 * dVar5 * dVar5 - DOUBLE_80438750));
  }
  *(float *)(param_1 + 0x180) = (float)dVar4;
  fVar1 = *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x4c);
  *(float *)(param_1 + 0x44) = fVar1;
  if (*(float *)(&DAT_8030316c + iVar3) < fVar1) {
    *(float *)(param_1 + 0x44) = *(float *)(&DAT_8030316c + iVar3);
  }
  fVar2 = FLOAT_80438764;
  fVar1 = *(float *)(param_1 + 0xb4) * FLOAT_80438760;
  *(float *)(param_1 + 0xb4) = fVar1;
  if (fVar1 <= fVar2) {
    zz_00c42a8_(param_1);
  }
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
  fVar2 = FLOAT_8043875c;
  fVar1 = *(float *)(&DAT_80303170 + iVar3);
  if (*(float *)(param_1 + 0x180) < fVar1) {
    fVar1 = *(float *)(param_1 + 0x180);
  }
  *(float *)(param_1 + 0x184) = fVar1;
  *(float *)(param_1 + 0x60) = fVar1 / fVar2;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 2500-2508 ==== */
// ==== 800c4448  FUN_800c4448 ====

void FUN_800c4448(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 2512-2525 ==== */
// ==== 800c4468  FUN_800c4468 ====

void FUN_800c4468(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 2529-2547 ==== */
// ==== 800c44a8  zz_00c44a8_ ====

void zz_00c44a8_(int param_1)

{
  bool bVar1;
  float afStack_18 [5];
  
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x174),afStack_18);
  bVar1 = zz_0045ef4_((float *)(param_1 + 0x114),5,afStack_18,&DAT_802b0cb4);
  if (bVar1) {
    zz_0045ef4_((float *)(param_1 + 0x114),4,afStack_18,&DAT_802b0ca8);
  }
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 2551-2614 ==== */
// ==== 800c4540  zz_00c4540_ ====

void zz_00c4540_(int param_1)

{
  uint uVar1;
  char cVar2;
  int iVar3;
  uint uVar4;
  double dVar5;
  double dVar6;
  float afStack_34 [3];
  float afStack_28 [5];
  
  uVar4 = *(uint *)(param_1 + 200);
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x44;
  gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  uVar1 = 0;
  if ((int)(-uVar4 | uVar4) < 0) {
    *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(uVar4 + 100);
    *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(uVar4 + 0x68);
    *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(uVar4 + 0x6c);
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x144),(float *)(iVar3 + -0x7fcfceb8),afStack_28);
    gnt4_PSVECSubtract_bl(afStack_28,(float *)(param_1 + 0x20),afStack_34);
    dVar5 = gnt4_PSVECSquareMag_bl(afStack_34);
    if (dVar5 <= (double)(*(float *)(&DAT_80303160 + iVar3) * *(float *)(&DAT_80303160 + iVar3))) {
      *(undefined4 *)(param_1 + 200) = 0;
      uVar1 = 0;
    }
    else {
      dVar5 = gnt4_PSQUATDotProduct_bl((float *)(param_1 + 0x38),afStack_34);
      if (dVar5 < (double)FLOAT_80438744) {
        *(undefined4 *)(param_1 + 200) = 0;
        uVar1 = 0;
      }
      else {
        cVar2 = *(char *)(param_1 + 0x1cb) + -1;
        *(char *)(param_1 + 0x1cb) = cVar2;
        uVar1 = countLeadingZeros((int)cVar2);
        uVar1 = (1 << (uVar1 & 0x1f) | 1U >> 0x20 - (uVar1 & 0x1f)) & 1;
        if (uVar1 != 0) {
          *(undefined *)(param_1 + 0x1cb) = (&DAT_80303157)[iVar3];
          zz_006c440_((double)*(float *)(&DAT_80303158 + iVar3),param_1,afStack_28);
          zz_00833a4_(param_1);
        }
      }
    }
  }
  if (uVar1 == 0) {
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  }
  dVar5 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x174));
  if ((double)FLOAT_80438744 < dVar5) {
    dVar6 = 1.0 / SQRT(dVar5);
    dVar6 = DOUBLE_80438748 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80438750);
    dVar6 = DOUBLE_80438748 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80438750);
    dVar5 = (double)(float)(dVar5 * DOUBLE_80438748 * dVar6 *
                                    -(dVar5 * dVar6 * dVar6 - DOUBLE_80438750));
  }
  *(float *)(param_1 + 0x180) = (float)dVar5;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 2618-2656 ==== */
// ==== 800c4704  zz_00c4704_ ====

bool zz_00c4704_(int param_1,undefined1 param_2,undefined1 *param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,2);
  if (puVar1 == (undefined1 *)0x0) {
    *param_3 = 0;
    zz_006de10_(param_1,2);
  }
  else {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = param_2;
    puVar1[0x10] = 0x19;
    *(code **)(puVar1 + 0xc) = FUN_800c4838;
    *(code **)(puVar1 + 0x10c) = FUN_800c5a60;
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
    *(undefined1 **)(puVar1 + 0x184) = param_3;
  }
  return puVar1 != (undefined1 *)0x0;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 2660-2674 ==== */
// ==== 800c4838  FUN_800c4838 ====

void FUN_800c4838(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_80305240)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}
