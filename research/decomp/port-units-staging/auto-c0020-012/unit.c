#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_00c7034_(float *param_1);
void FUN_800c7100(int param_1);
void FUN_800c713c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9);
void FUN_800c715c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8);
void zz_00c71c0_(int param_1,undefined1 param_2);
void FUN_800c72c0(int param_1);
void FUN_800c72fc(int param_1);
void FUN_800c7350(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 4232-4269 ==== */
// ==== 800c7034  zz_00c7034_ ====

void zz_00c7034_(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  
  fVar7 = FLOAT_804387f4;
  iVar5 = *(char *)(param_1 + 4) * 0x10;
  fVar4 = *(float *)(&DAT_803060a4 + iVar5);
  fVar1 = *(float *)(&DAT_803060a8 + iVar5);
  fVar2 = *(float *)(&DAT_803060ac + iVar5);
  fVar3 = *(float *)(&DAT_803060b0 + iVar5);
  if ((param_1[3] == fVar4) || (FLOAT_804387f4 == fVar4)) {
    *param_1 = fVar1;
    param_1[1] = fVar2;
    param_1[2] = fVar3;
    return;
  }
  fVar6 = param_1[3] - fVar4;
  iVar5 = (*(char *)(param_1 + 4) + 1) * 0x10;
  fVar4 = *(float *)(&DAT_803060a4 + iVar5) - fVar4;
  *param_1 = ((*(float *)(&DAT_803060a8 + iVar5) - fVar1) / fVar4) * fVar6 + fVar1;
  param_1[1] = ((*(float *)(&DAT_803060ac + iVar5) - fVar2) / fVar4) * fVar6 + fVar2;
  param_1[2] = ((*(float *)(&DAT_803060b0 + iVar5) - fVar3) / fVar4) * fVar6 + fVar3;
  fVar1 = *(float *)(&DAT_803060a4 + iVar5);
  if ((param_1[3] <= fVar1) && (fVar7 != fVar1)) {
    return;
  }
  *(char *)(param_1 + 4) = *(char *)(param_1 + 4) + '\x01';
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 4273-4282 ==== */
// ==== 800c7100  FUN_800c7100 ====

void FUN_800c7100(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 4286-4294 ==== */
// ==== 800c713c  FUN_800c713c ====

void FUN_800c713c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 4298-4324 ==== */
// ==== 800c715c  FUN_800c715c ====

void FUN_800c715c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  double dVar2;
  undefined8 uVar3;
  double dVar4;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_38 [13];
  
  dVar2 = (double)*(float *)(param_1 + 0x168);
  dVar4 = dVar2;
  gnt4_PSMTXScale_bl(dVar2,dVar2,dVar2,afStack_38);
  pfVar1 = afStack_38;
  uVar3 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar3,dVar2,dVar4,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),afStack_38,
              (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 4328-4360 ==== */
// ==== 800c71c0  zz_00c71c0_ ====

void zz_00c71c0_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,8,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_800c72c0;
    puVar1[0x13] = param_2;
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
    *(short *)(puVar1 + 0x14c) =
         (short)*(char *)(param_1 + 0x1afd) + *(char *)(param_1 + 0x1afc) * 0x1000;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 4364-4371 ==== */
// ==== 800c72c0  FUN_800c72c0 ====

void FUN_800c72c0(int param_1)

{
  (*(code *)(&PTR_FUN_803060d4)[*(char *)(param_1 + 0x18)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 4375-4386 ==== */
// ==== 800c72fc  FUN_800c72fc ====

void FUN_800c72fc(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(undefined2 *)(param_1 + 0x1c) = 0;
  *(undefined2 *)(param_1 + 0x1e) = 300;
  *(char *)(param_1 + 0x89) = (char)*(undefined4 *)(&DAT_803060e4 + *(char *)(param_1 + 0x13) * 4);
  FUN_800c7350(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0020.c 4390-4448 ==== */
// ==== 800c7350  FUN_800c7350 ====

/* WARNING: Removing unreachable block (ram,0x800c74a4) */
/* WARNING: Removing unreachable block (ram,0x800c749c) */
/* WARNING: Removing unreachable block (ram,0x800c7368) */
/* WARNING: Removing unreachable block (ram,0x800c7360) */

void FUN_800c7350(int param_1)

{
  char cVar1;
  bool bVar2;
  short sVar3;
  float *pfVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  
  cVar1 = *(char *)(param_1 + 0x19);
  iVar5 = *(int *)(param_1 + 0x90);
  if (cVar1 != '\x01') {
    if (('\0' < cVar1) || (cVar1 < '\0')) goto LAB_800c7478;
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    *(undefined **)(param_1 + 0x148) = (&PTR_DAT_80305e48)[*(char *)(param_1 + 0x13)];
    *(undefined4 *)(param_1 + 0x150) = 0;
  }
  bVar2 = false;
  pfVar4 = *(float **)(param_1 + 0x148);
  dVar7 = (double)*(float *)(iVar5 + 0x1ae0);
  if (*(short *)(param_1 + 0x14c) ==
      (short)((short)*(char *)(iVar5 + 0x1afd) + *(char *)(iVar5 + 0x1afc) * 0x1000)) {
    dVar8 = (double)FLOAT_804387f8;
    while ((dVar6 = (double)*pfVar4, dVar8 < dVar6 && (dVar6 < dVar7))) {
      FUN_800c6a94(iVar5,pfVar4 + 1,pfVar4 + 4,(char)*(undefined4 *)(param_1 + 0x150),
                   (&DAT_80433b38)[*(char *)(param_1 + 0x13)]);
      pfVar4 = pfVar4 + 7;
      *(int *)(param_1 + 0x150) = *(int *)(param_1 + 0x150) + 1;
      *(float **)(param_1 + 0x148) = pfVar4;
    }
    if (dVar6 < (double)FLOAT_804387f8) {
      bVar2 = true;
    }
  }
  else {
    bVar2 = true;
  }
  if (bVar2) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
LAB_800c7478:
  sVar3 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar3;
  if (sVar3 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}
