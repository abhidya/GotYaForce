#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01a142c_(int param_1);
void zz_01a1514_(int param_1);
void zz_01a1620_(int param_1);
void zz_01a165c_(int param_1);
void zz_01a16b0_(int param_1);
void zz_01a1798_(double param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 3078-3111 ==== */
// ==== 801a142c  zz_01a142c_ ====

void zz_01a142c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043b59c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_8043b594;
  if (iVar3 != 1) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) goto LAB_801a14e4;
  }
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_01a1af0_(param_1);
  }
LAB_801a14e4:
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_8043b5a0 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 3115-3149 ==== */
// ==== 801a1514  zz_01a1514_ ====

void zz_01a1514_(int param_1)

{
  int iVar1;
  double dVar2;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043b59c,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  iVar1 = zz_01a1bbc_(param_1);
  if (iVar1 == 0) {
    iVar1 = zz_004cd24_(param_1,0xf);
    if ((iVar1 == 1) || ((*(ushort *)(param_1 + 0x5d8) & 0xf0) != 0)) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a474_(param_1);
    }
    dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if ((double)FLOAT_8043b5a0 < dVar2) {
      zz_00b22f4_(param_1);
    }
  }
  else {
    zz_006bf80_(param_1);
    dVar2 = (double)FLOAT_8043b598;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    zz_004beb8_(dVar2,param_1,0xf,2,3,0xffffffff,0xffffffff);
    if (*(short *)(param_1 + 1000) == 0x90b) {
      zz_00f0104_(param_1,0x24,2);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 3153-3160 ==== */
// ==== 801a1620  zz_01a1620_ ====

void zz_01a1620_(int param_1)

{
  (*(code *)(&PTR_zz_01a165c__80378714)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 3164-3178 ==== */
// ==== 801a165c  zz_01a165c_ ====

void zz_01a165c_(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_8043b5a4;
  dVar2 = (double)FLOAT_8043b598;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_004beb8_(dVar2,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,0xffffffff);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 3182-3216 ==== */
// ==== 801a16b0  zz_01a16b0_ ====

void zz_01a16b0_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,1);
  }
  fVar2 = FLOAT_8043b594;
  if (iVar3 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else {
    if ((iVar3 < 1) &&
       (fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x558) = fVar1, fVar2 < fVar1)) {
      return;
    }
    if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      zz_01a1af0_(param_1);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0049.c 3220-3270 ==== */
// ==== 801a1798  zz_01a1798_ ====

void zz_01a1798_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  iVar1 = zz_01a1bbc_(param_9);
  if (iVar1 == 0) {
    zz_004cd24_(param_9,1);
    if ((*(char *)(param_9 + 0x1cee) != '\0') || ((*(ushort *)(param_9 + 0x5d8) & 0xf0) != 0)) {
      *(undefined1 *)(param_9 + 0x73f) = 0;
      *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
      zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  else {
    zz_006bf80_(param_9);
    *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
    if (*(short *)(param_9 + 1000) == 0x90b) {
      zz_00f0104_(param_9,0x24,2);
    }
    uVar2 = *(uint *)(param_9 + 0x5e0);
    if (((uVar2 & 0x40) == 0) && (*(char *)(param_9 + 0x5e4) != '\x04')) {
      if ((uVar2 & 0x10) != 0) {
        dVar3 = (double)FLOAT_8043b598;
        *(undefined1 *)(param_9 + 0x581) = 1;
        zz_004beb8_(dVar3,param_9,1,2,9,0xffffffff,0xffffffff);
        return;
      }
      if ((uVar2 & 0x20) != 0) {
        dVar3 = (double)FLOAT_8043b598;
        *(undefined1 *)(param_9 + 0x581) = 3;
        zz_004beb8_(dVar3,param_9,1,2,9,0xffffffff,0xffffffff);
        return;
      }
      zz_006a3d0_(param_9,'\0',0,2);
      return;
    }
    dVar3 = (double)FLOAT_8043b598;
    *(undefined1 *)(param_9 + 0x581) = 2;
    zz_004beb8_(dVar3,param_9,1,2,9,0xffffffff,0xffffffff);
  }
  return;
}
