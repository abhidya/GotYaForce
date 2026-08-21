#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80131634(int param_1);
void FUN_80131664(int param_1);
void FUN_80131688(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void zz_01316e0_(double param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_80131834(int param_1);
void FUN_801318a8(int param_1);
void FUN_801318f8(int param_1);
void FUN_80131a00(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 555-563 ==== */
// ==== 80131634  FUN_80131634 ====

void FUN_80131634(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0161d7c_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 567-574 ==== */
// ==== 80131664  FUN_80131664 ====

void FUN_80131664(int param_1)

{
  zz_01618ac_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 578-597 ==== */
// ==== 80131688  FUN_80131688 ====

void FUN_80131688(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  double dVar2;
  double dVar3;
  
  dVar2 = DOUBLE_80439e88;
  sVar1 = *(short *)(param_9 + 0x1900);
  dVar3 = (double)(float)((double)CONCAT44(0x43300000,(int)sVar1 ^ 0x80000000) - DOUBLE_80439e88);
  *(short *)(param_9 + 0x1900) = (short)(int)(dVar3 * (double)FLOAT_80439e80);
  zz_01316e0_(dVar3,dVar2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,(int)sVar1,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 601-647 ==== */
// ==== 801316e0  zz_01316e0_ ====

void zz_01316e0_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  if (*(char *)(param_9 + 0x540) == '\0') {
    *(undefined1 *)(param_9 + 0x540) = 1;
    if (((*(uint *)(param_9 + 0x5e0) & 0x20) == 0) || (*(char *)(param_9 + 0x1cef) == '\0')) {
      *(undefined1 *)(param_9 + 0x543) = 1;
      if (*(char *)(param_9 + 0x5db) == '\x01') {
        *(undefined1 *)(param_9 + 0x543) = 0xf;
      }
      *(undefined1 *)(param_9 + 0x6ea) = 2;
      if ((*(uint *)(param_9 + 0x5e0) & 0x10) != 0) {
        *(undefined1 *)(param_9 + 0x6ea) = 4;
      }
      if ((*(uint *)(param_9 + 0x5e0) & 0x40) != 0) {
        *(undefined1 *)(param_9 + 0x6ea) = 3;
      }
      zz_004beb8_((double)FLOAT_80439e90,param_9,(int)*(char *)(param_9 + 0x543),4,
                  (int)*(char *)(param_9 + 0x6ea),0xffffffff,0xffffffff);
    }
    else {
      *(undefined1 *)(param_9 + 0x73f) = 0;
      *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
      zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,4,param_11
                  ,param_12,param_13,param_14,param_15,param_16);
      *(float *)(param_9 + 0x694) =
           *(float *)(param_9 + 0x1dc8) +
           ((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1af8) ^ 0x80000000) -
                   DOUBLE_80439e88) - *(float *)(param_9 + 0x1ae0));
    }
  }
  else {
    zz_004cd24_(param_9,1);
    if (*(char *)(param_9 + 0x1cee) != '\0') {
      *(undefined1 *)(param_9 + 0x73f) = 0;
      *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
      zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x1e,
                  param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 651-662 ==== */
// ==== 80131834  FUN_80131834 ====

void FUN_80131834(int param_1)

{
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_80439e88) * FLOAT_80439e80);
  (*(code *)(&PTR_FUN_80335d18)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 666-676 ==== */
// ==== 801318a8  FUN_801318a8 ====

void FUN_801318a8(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80335d2c)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 680-714 ==== */
// ==== 801318f8  FUN_801318f8 ====

void FUN_801318f8(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar1 = FLOAT_80439e78;
  *(float *)(param_1 + 0x50) = FLOAT_80439e78;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  zz_006d144_(param_1,0xc1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_80439e90,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),8,1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 718-747 ==== */
// ==== 80131a00  FUN_80131a00 ====

void FUN_80131a00(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    if (*(short *)(param_1 + 1000) == 0x103) {
      zz_013a954_(param_1,0);
    }
    else if ((*(short *)(param_1 + 1000) == 0x106) &&
            (iVar1 = zz_006dbe0_(param_1,2,1,1), iVar1 != 0)) {
      *(byte *)(param_1 + 0x15b) = *(byte *)(param_1 + 0x15b) | 2;
      zz_00fe668_(param_1,2,2);
      zz_00f036c_(param_1,0xeb);
    }
  }
  return;
}
