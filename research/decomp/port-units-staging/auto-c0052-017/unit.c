#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01b41c4_(void);
void zz_01b41c8_(int param_1);
void zz_01b41e8_(int param_1);
void zz_01b4208_(int param_1);
void zz_01b4244_(int param_1);
void zz_01b4280_(int param_1);
void zz_01b42f4_(int param_1);
void zz_01b433c_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4895-4901 ==== */
// ==== 801b41c4  zz_01b41c4_ ====

void zz_01b41c4_(void)

{
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4905-4912 ==== */
// ==== 801b41c8  zz_01b41c8_ ====

void zz_01b41c8_(int param_1)

{
  zz_01b3f94_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4916-4923 ==== */
// ==== 801b41e8  zz_01b41e8_ ====

void zz_01b41e8_(int param_1)

{
  zz_01b3fcc_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4927-4934 ==== */
// ==== 801b4208  zz_01b4208_ ====

void zz_01b4208_(int param_1)

{
  (*(code *)(&PTR_zz_01b4244__803816b0)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4938-4945 ==== */
// ==== 801b4244  zz_01b4244_ ====

void zz_01b4244_(int param_1)

{
  (*(code *)(&PTR_zz_01b4280__803816bc)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0052.c 4949-4959 ==== */
// ==== 801b4280  zz_01b4280_ ====

void zz_01b4280_(int param_1)

{
  *(short *)(param_1 + 0x1dfc) =
       (short)(int)((__gnt4_bitcast_f64(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1dfc) ^ 0x80000000)) -
                    DOUBLE_8043b980) * DOUBLE_8043b978);
  (*(code *)(&PTR_zz_01b42f4__803816d0)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4963-4979 ==== */
// ==== 801b42f4  zz_01b42f4_ ====

void zz_01b42f4_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043b98c;
  fVar1 = FLOAT_8043b988;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  zz_006d0dc_(param_1,0xc1,0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0052.c 4983-5000 ==== */
// ==== 801b433c  zz_01b433c_ ====

void zz_01b433c_(int param_1)

{
  int iVar1;
  double dVar2;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = zz_006d0dc_(param_1,0xc1,0);
  if ((iVar1 != 1) && (FLOAT_8043b98c < *(float *)(param_1 + 0x558))) {
    return;
  }
  dVar2 = (double)FLOAT_8043b990;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,0xf,2,0,0xffffffff,0xffffffff);
  return;
}
