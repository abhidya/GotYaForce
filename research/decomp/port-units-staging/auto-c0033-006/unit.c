#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801238bc(int param_1);
void FUN_801238f8(int param_1);
void FUN_8012394c(int param_1);
void FUN_8012399c(int param_1);
void FUN_80123a44(int param_1);
void FUN_80123ab0(int param_1);
void FUN_80123bb4(int param_1);
void FUN_80123d14(double param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1713-1720 ==== */
// ==== 801238bc  FUN_801238bc ====

void FUN_801238bc(int param_1)

{
  (*(code *)(&PTR_FUN_8032e370)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1724-1733 ==== */
// ==== 801238f8  FUN_801238f8 ====

void FUN_801238f8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x1900) = *(short *)(param_1 + 0x1900) >> 1;
  (*(code *)(&PTR_FUN_8032e37c)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1737-1747 ==== */
// ==== 8012394c  FUN_8012394c ====

void FUN_8012394c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032e390)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1751-1774 ==== */
// ==== 8012399c  FUN_8012399c ====

void FUN_8012399c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80439b90;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined1 *)(param_1 + 0x6f2) = 0;
  if (*(short *)(param_1 + 0x774) < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  zz_006ea9c_(param_1);
  *(undefined1 *)(param_1 + 0x543) = 1;
  if (*(char *)(param_1 + 0x5db) == '\x01') {
    *(undefined1 *)(param_1 + 0x543) = 0xf;
  }
  zz_004beb8_((double)FLOAT_80439b94,param_1,(int)*(char *)(param_1 + 0x543),2,
              (int)*(char *)(param_1 + 0x6f2),0xffffffff,0xffffffff);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1778-1795 ==== */
// ==== 80123a44  FUN_80123a44 ====

void FUN_80123a44(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_80439b98;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = zz_006ea9c_(param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1799-1829 ==== */
// ==== 80123ab0  FUN_80123ab0 ====

void FUN_80123ab0(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,1);
  zz_006ea9c_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    iVar1 = zz_006dbe0_(param_1,0,1,0);
    if (iVar1 == 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
      if (*(char *)(param_1 + 0x5db) != '\x01') {
        *(undefined1 *)(param_1 + 0x543) = 1;
      }
      zz_004beb8_((double)FLOAT_80439b94,param_1,(int)*(char *)(param_1 + 0x543),2,
                  *(char *)(param_1 + 0x6f2) + 2,0xffffffff,0xffffffff);
    }
    else {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x543) = 1;
      if (*(char *)(param_1 + 0x5db) == '\x01') {
        *(undefined1 *)(param_1 + 0x543) = 0xf;
      }
      zz_004beb8_((double)FLOAT_80439b94,param_1,(int)*(char *)(param_1 + 0x543),2,
                  *(char *)(param_1 + 0x6f2) + 1,0xffffffff,0xffffffff);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1833-1873 ==== */
// ==== 80123bb4  FUN_80123bb4 ====

void FUN_80123bb4(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,1);
  zz_006ea9c_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      if (*(short *)(param_1 + 1000) == 0x202) {
        zz_0126294_(param_1,0);
      }
      else if (*(short *)(param_1 + 1000) == 0x20b) {
        zz_0126294_(param_1,1);
      }
    }
  }
  if (((*(char *)(param_1 + 0x1cef) < '\0') && (0 < *(short *)(param_1 + 0x774))) &&
     ((*(uint *)(param_1 + 0x5d4) & 0x20) != 0)) {
    *(undefined1 *)(param_1 + 0x543) = 1;
    if (*(char *)(param_1 + 0x5db) == '\x01') {
      *(undefined1 *)(param_1 + 0x543) = 0xf;
    }
    zz_004beb8_((double)FLOAT_80439b94,param_1,(int)*(char *)(param_1 + 0x543),2,
                *(char *)(param_1 + 0x6f2) + 1,0xffffffff,0xffffffff);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(char *)(param_1 + 0x5db) != '\x01') {
      *(undefined1 *)(param_1 + 0x543) = 1;
    }
    zz_004beb8_((double)FLOAT_80439b94,param_1,(int)*(char *)(param_1 + 0x543),2,
                *(char *)(param_1 + 0x6f2) + 2,0xffffffff,0xffffffff);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0033.c 1877-1893 ==== */
// ==== 80123d14  FUN_80123d14 ====

void FUN_80123d14(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_004cd24_(param_9,1);
  if (*(char *)(param_9 + 0x1cee) != '\0') {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}
