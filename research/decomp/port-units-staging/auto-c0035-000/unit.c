#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_8013088c(int param_1);
void FUN_801309b8(uint param_1);
void FUN_80130ad0(int param_1);
void FUN_80130c5c(int param_1);
void FUN_80130c98(int param_1);
void FUN_80130d34(uint param_1);
void FUN_80130e50(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_80131038(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 1-35 ==== */
// ==== 8013088c  FUN_8013088c ====

void FUN_8013088c(int param_1)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(short *)(param_1 + 1000) == 0x103) {
    zz_004beb8_((double)FLOAT_80439e90,param_1,1,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,
                0xffffffff);
    zz_004beb8_((double)FLOAT_80439e90,param_1,2,0,0,0xffffffff,0xffffffff);
  }
  else {
    zz_004beb8_((double)FLOAT_80439e90,param_1,0xf,2,0xc,4,1);
  }
  zz_006d0dc_(param_1,0xc1,0);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  zz_013138c_(param_1);
  fVar1 = FLOAT_80439e78;
  *(float *)(param_1 + 0x50) = FLOAT_80439e78;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_80439e78;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 39-75 ==== */
// ==== 801309b8  FUN_801309b8 ====

/* WARNING: Removing unreachable block (ram,0x80130ab4) */
/* WARNING: Removing unreachable block (ram,0x801309c8) */

void FUN_801309b8(uint param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if ((*(char *)(param_1 + 0x1cef) != '\0') && (*(char *)(param_1 + 0x1b03) == '\0')) {
    *(float *)(param_1 + 0x1dc8) = FLOAT_80439e78;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_80439e78;
  if ((((iVar3 != 0) ||
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) &&
      (*(char *)(param_1 + 0x1cef) != '\0')) && (*(char *)(param_1 + 0x1b03) == '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_01313bc_(param_1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_80439e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80439e98 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 79-133 ==== */
// ==== 80130ad0  FUN_80130ad0 ====

void FUN_80130ad0(int param_1)

{
  int iVar1;
  double dVar2;
  
  if (*(float *)(param_1 + 0x55c) <= FLOAT_80439e78) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(float *)(param_1 + 0x558) <= FLOAT_80439e78) {
    if ('\0' < *(char *)(param_1 + 0x6ef)) {
      iVar1 = zz_006dbe0_(param_1,0,1,0);
      if (iVar1 != 0) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
          zz_006a3d0_(param_1,'\0',3,0);
          return;
        }
        zz_006bf80_(param_1);
        iVar1 = 1;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        if (*(short *)(param_1 + 1000) != 0x103) {
          iVar1 = 0xd;
        }
        zz_004beb8_((double)FLOAT_80439e90,param_1,0xf,2,iVar1,0xffffffff,0xffffffff);
        return;
      }
      goto LAB_80130be4;
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_1 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_80439e94,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00679d0_(param_1);
    dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if (dVar2 <= (double)FLOAT_80439e98) {
      return;
    }
    zz_00b22f4_(param_1);
    return;
  }
LAB_80130be4:
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 137-144 ==== */
// ==== 80130c5c  FUN_80130c5c ====

void FUN_80130c5c(int param_1)

{
  (*(code *)(&PTR_FUN_80335ce8)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 148-175 ==== */
// ==== 80130c98  FUN_80130c98 ====

void FUN_80130c98(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar2 = 0xffffffff;
  uVar3 = 0xffffffff;
  iVar1 = 6;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if ((*(uint *)(param_1 + 0x5e0) & 0x10) != 0) {
    iVar1 = 3;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x20) != 0) {
    iVar1 = 0;
  }
  if (*(short *)(param_1 + 1000) != 0x103) {
    uVar2 = 4;
    uVar3 = 1;
    iVar1 = iVar1 + 0xc;
  }
  zz_004beb8_((double)FLOAT_80439e90,param_1,1,2,iVar1 + *(char *)(param_1 + 0x6ee),uVar2,uVar3);
  zz_013138c_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 179-216 ==== */
// ==== 80130d34  FUN_80130d34 ====

/* WARNING: Removing unreachable block (ram,0x80130e30) */
/* WARNING: Removing unreachable block (ram,0x80130d44) */

void FUN_80130d34(uint param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  iVar3 = zz_006dee8_(param_1,1);
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if ((*(char *)(param_1 + 0x1cef) != '\0') && (*(char *)(param_1 + 0x1b03) == '\0')) {
    *(float *)(param_1 + 0x1dc8) = (float)(dVar4 * (double)FLOAT_80439e78);
  }
  zz_004cd24_(param_1,1);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  fVar2 = FLOAT_80439e78;
  if (iVar3 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else if ((((0 < iVar3) ||
            (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
            *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) &&
           (*(char *)(param_1 + 0x1cef) != '\0')) && (*(char *)(param_1 + 0x1b03) == '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_01313bc_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 220-296 ==== */
// ==== 80130e50  FUN_80130e50 ====

void FUN_80130e50(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  if (*(float *)(param_9 + 0x55c) <= FLOAT_80439e78) {
    zz_004cd24_(param_9,1);
  }
  else {
    *(float *)(param_9 + 0x55c) = *(float *)(param_9 + 0x55c) - *(float *)(param_9 + 0x1dc8);
  }
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_80439e78) {
    if ('\0' < *(char *)(param_9 + 0x6ef)) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if (iVar1 != 0) {
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        uVar2 = *(uint *)(param_9 + 0x5e0);
        if (((uVar2 & 0x40) != 0) || (*(char *)(param_9 + 0x5e4) == '\x04')) {
          iVar1 = 7;
          *(undefined1 *)(param_9 + 0x581) = 3;
          if ((*(uint *)(param_9 + 0x5e0) & 0x80) != 0) {
            iVar1 = 10;
          }
          if (*(short *)(param_9 + 1000) != 0x103) {
            iVar1 = iVar1 + 0xc;
          }
          zz_004beb8_((double)FLOAT_80439e90,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x10) != 0) {
          iVar1 = 4;
          *(undefined1 *)(param_9 + 0x581) = 1;
          if (*(short *)(param_9 + 1000) != 0x103) {
            iVar1 = 0x10;
          }
          zz_004beb8_((double)FLOAT_80439e90,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x20) != 0) {
          iVar1 = 1;
          *(undefined1 *)(param_9 + 0x581) = 2;
          if (*(short *)(param_9 + 1000) != 0x103) {
            iVar1 = 0xd;
          }
          zz_004beb8_((double)FLOAT_80439e90,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      goto LAB_80131004;
    }
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_80131004:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0035.c 300-308 ==== */
// ==== 80131038  FUN_80131038 ====

void FUN_80131038(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80335cf4)[*(char *)(param_1 + 0x540)])();
  return;
}
