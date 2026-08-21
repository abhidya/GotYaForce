#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801035ac(int param_1);
void FUN_801035e8(int param_1);
void FUN_80103618(int param_1);
void FUN_80103648(int param_1);
void FUN_80103678(int param_1);
void FUN_8010369c(int param_1);
void FUN_801036d8(int param_1);
void FUN_80103714(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4453-4460 ==== */
// ==== 801035ac  FUN_801035ac ====

void FUN_801035ac(int param_1)

{
  (*(code *)(&PTR_FUN_80321658)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4464-4472 ==== */
// ==== 801035e8  FUN_801035e8 ====

void FUN_801035e8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4476-4484 ==== */
// ==== 80103618  FUN_80103618 ====

void FUN_80103618(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4488-4496 ==== */
// ==== 80103648  FUN_80103648 ====

void FUN_80103648(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0161d7c_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4500-4507 ==== */
// ==== 80103678  FUN_80103678 ====

void FUN_80103678(int param_1)

{
  zz_01618ac_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4511-4518 ==== */
// ==== 8010369c  FUN_8010369c ====

void FUN_8010369c(int param_1)

{
  (*(code *)(&PTR_FUN_8032166c)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4522-4529 ==== */
// ==== 801036d8  FUN_801036d8 ====

void FUN_801036d8(int param_1)

{
  (*(code *)(&PTR_FUN_80321680)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0028.c 4533-4569 ==== */
// ==== 80103714  FUN_80103714 ====

void FUN_80103714(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  fVar4 = FLOAT_804393cc;
  fVar3 = FLOAT_804393c8;
  fVar2 = FLOAT_804393b0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(float *)(param_1 + 0x560) = fVar3;
  *(undefined2 *)(param_1 + 0x54e) = 0x3c;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(float *)(param_1 + 0x48) = fVar4;
  *(float *)(param_1 + 0x50) = fVar2;
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar5 = (double)FLOAT_804393ac;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar5,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}
