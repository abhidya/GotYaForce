#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01a1230_(void);
void zz_01a1234_(void);
void zz_01a1238_(void);
void zz_01a123c_(int param_1,char param_2);
void zz_01a1290_(int param_1);
void zz_01a12cc_(int param_1);
void zz_01a1308_(int param_1);
void zz_01a134c_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 2962-2968 ==== */
// ==== 801a1230  zz_01a1230_ ====

void zz_01a1230_(void)

{
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 2972-2978 ==== */
// ==== 801a1234  zz_01a1234_ ====

void zz_01a1234_(void)

{
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 2982-2988 ==== */
// ==== 801a1238  zz_01a1238_ ====

void zz_01a1238_(void)

{
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 2992-3005 ==== */
// ==== 801a123c  zz_01a123c_ ====

void zz_01a123c_(int param_1,char param_2)

{
  if (param_2 == '\x01') {
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
  }
  else if ((param_2 < '\x01') && (-1 < param_2)) {
    *(undefined1 *)(param_1 + 0xaf) = 1;
    zz_001ab6c_(param_1,0x47);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 3009-3016 ==== */
// ==== 801a1290  zz_01a1290_ ====

void zz_01a1290_(int param_1)

{
  (*(code *)(&PTR_zz_01a12cc__803786e8)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 3020-3027 ==== */
// ==== 801a12cc  zz_01a12cc_ ====

void zz_01a12cc_(int param_1)

{
  (*(code *)(&PTR_zz_01a1308__803786f4)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 3031-3039 ==== */
// ==== 801a1308  zz_01a1308_ ====

void zz_01a1308_(int param_1)

{
  *(undefined2 *)(param_1 + 0x1dfc) = 0;
  (*(code *)(&PTR_zz_01a134c__80378708)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 3043-3074 ==== */
// ==== 801a134c  zz_01a134c_ ====

void zz_01a134c_(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_8043b594;
  fVar1 = FLOAT_8043b590;
  dVar3 = (double)FLOAT_8043b598;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_004beb8_(dVar3,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,0xffffffff);
  zz_006d0dc_(param_1,0xc1,0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043b59c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_8043b594;
  return;
}
