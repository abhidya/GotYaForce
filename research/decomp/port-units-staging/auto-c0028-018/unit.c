#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01040c4_(int param_1);
void FUN_801041b0(int param_1);
void FUN_80104204(int param_1);
void zz_0104310_(int param_1);
void FUN_80104330(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void FUN_80104350(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4891-4921 ==== */
// ==== 801040c4  zz_01040c4_ ====

void zz_01040c4_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0xb03) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_801041b0;
    *(code **)(puVar1 + 0x10c) = FUN_80104350;
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
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4925-4933 ==== */
// ==== 801041b0  FUN_801041b0 ====

void FUN_801041b0(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803216b0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4937-5000 ==== */
// ==== 80104204  FUN_80104204 ====

void FUN_80104204(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 extraout_r4;
  undefined4 uVar5;
  int iVar6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  double dVar8;
  undefined8 uVar9;
  double dVar10;
  double dVar11;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  iVar7 = *(int *)(param_1 + 0x90);
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  *(code **)(param_1 + 0x100) = FUN_80047dcc;
  zz_0089100_(param_1,(int)*(char *)(iVar7 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_804393d8;
  dVar11 = (double)FLOAT_804393d8;
  *(undefined1 *)(param_1 + 0x84) = 0x47;
  fVar2 = FLOAT_804393dc;
  dVar10 = (double)FLOAT_804393dc;
  *(float *)(param_1 + 0xb4) = fVar1;
  fVar3 = FLOAT_804393e0;
  dVar8 = (double)FLOAT_804393e0;
  *(float *)(param_1 + 0xb8) = fVar1;
  fVar4 = FLOAT_804393e4;
  *(float *)(param_1 + 0x58) = fVar1;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x60) = fVar1;
  *(undefined1 *)(param_1 + 0x89) = 0xc;
  *(float *)(param_1 + 100) = fVar2;
  *(float *)(param_1 + 0x68) = fVar3;
  *(float *)(param_1 + 0x6c) = fVar4;
  *(undefined2 *)(param_1 + 0x70) = 0xee39;
  *(undefined2 *)(param_1 + 0x72) = 0;
  iVar7 = zz_0006f98_(iVar7);
  uVar9 = zz_0007030_(dVar8,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar7 + 0x600),
                      *(int *)(param_1 + 0xe0),10,iVar7 + 0xc28,in_r7,in_r8,in_r9,in_r10);
  iVar6 = iVar7 + 0xc28;
  uVar5 = 10;
  uVar9 = zz_0007030_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar7 + 0x600),
                      *(int *)(param_1 + 0xe4),10,iVar6,in_r7,in_r8,in_r9,in_r10);
  zz_0007c54_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe4),extraout_r4
              ,uVar5,iVar6,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804393e8,*(int *)(param_1 + 0xe4));
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
  zz_0104310_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 5004-5011 ==== */
// ==== 80104310  zz_0104310_ ====

void zz_0104310_(int param_1)

{
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x800;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 5015-5023 ==== */
// ==== 80104330  FUN_80104330 ====

void FUN_80104330(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 5027-5047 ==== */
// ==== 80104350  FUN_80104350 ====

void FUN_80104350(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar1 = *(int *)(param_9 + 0xe0);
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,0x45);
  return;
}
