#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_0007ae4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 *param_10, char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0007bb4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 *param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0007c30_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0007c54_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0007c84_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, char *param_11,byte *param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_0007cac_(double param_1,int param_2);
void zz_0007cd0_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);
void zz_0007cf4_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 2236-2281 ==== */
// ==== 80007ae4  zz_0007ae4_ ====

/* WARNING: Removing unreachable block (ram,0x80007b60) */

void zz_0007ae4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
                char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_9 + 0xc);
  if (iVar4 == 0) {
    param_11 = &DAT_80436a58;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a50,0x316,&DAT_80436a58,param_12,param_13,param_14,param_15
                               ,param_16);
  }
  if (param_10 == (undefined4 *)0x0) {
    param_11 = s_scale_80436a6c;
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a50,0x317,s_scale_80436a6c,param_12,param_13,param_14,
                               param_15,param_16);
  }
  uVar2 = param_10[1];
  *(undefined4 *)(iVar4 + 0x2c) = *param_10;
  *(undefined4 *)(iVar4 + 0x30) = uVar2;
  *(undefined4 *)(iVar4 + 0x34) = param_10[2];
  if (((*(uint *)(iVar4 + 0x14) & 0x2000000) == 0) && (iVar4 != 0)) {
    uVar3 = *(uint *)(iVar4 + 0x14);
    bVar1 = false;
    if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      gnt4_HSD_JObjSetMtxDirtySub_bl
                (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,uVar3,
                 param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 2285-2311 ==== */
// ==== 80007bb4  zz_0007bb4_ ====

void zz_0007bb4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 *param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_9 + 0xc);
  if (iVar2 == 0) {
    param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                               &DAT_80436a50,0x351,&DAT_80436a58,param_12,param_13,param_14,param_15
                               ,param_16);
  }
  if (param_10 == (undefined4 *)0x0) {
    gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_80436a50,
                     0x352,s_scale_80436a6c,param_12,param_13,param_14,param_15,param_16);
  }
  uVar1 = *(undefined4 *)(iVar2 + 0x30);
  *param_10 = *(undefined4 *)(iVar2 + 0x2c);
  param_10[1] = uVar1;
  param_10[2] = *(undefined4 *)(iVar2 + 0x34);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 2315-2328 ==== */
// ==== 80007c30  zz_0007c30_ ====

void zz_0007c30_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  gnt4_HSD_JObjAnimAll
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
             *(int **)(param_9 + 0xc),param_10,param_11,param_12,param_13,param_14,param_15,param_16
            );
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 2332-2344 ==== */
// ==== 80007c54  zz_0007c54_ ====

void zz_0007c54_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_0008f18_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xc),0x60002001,(char *)0x400a,param_12,param_13,param_14,param_15,
              param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 2348-2359 ==== */
// ==== 80007c84  zz_0007c84_ ====

void zz_0007c84_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                char *param_11,byte *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_0009068_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xc),0,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 2363-2370 ==== */
// ==== 80007cac  zz_0007cac_ ====

void zz_0007cac_(double param_1,int param_2)

{
  zz_00091e4_(param_1,*(int *)(param_2 + 0xc));
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 2374-2381 ==== */
// ==== 80007cd0  zz_0007cd0_ ====

void zz_0007cd0_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  zz_00094b8_(*(int *)(param_1 + 0xc),param_2,param_3,param_4);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0000.c 2385-2392 ==== */
// ==== 80007cf4  zz_0007cf4_ ====

void zz_0007cf4_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  zz_00093d8_(*(int *)(param_1 + 0xc),param_2,param_3,param_4);
  return;
}
