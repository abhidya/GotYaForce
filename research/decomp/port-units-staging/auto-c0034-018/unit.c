#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80130154(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_80130330(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_801304b8(int param_1);
void FUN_80130788(int param_1);
void FUN_801307c4(int param_1);
void FUN_80130844(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0034.c 4781-4811 ==== */
// ==== 80130154  FUN_80130154 ====

void FUN_80130154(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if ((double)FLOAT_80439e70 < (double)*(float *)(param_9 + 0x58)) {
    if ((*(char *)(param_9 + 0x13) == '\0') && (*(char *)(iVar1 + 0x159) != '\0')) {
      return;
    }
    if ((*(char *)(iVar1 + 0xae) == '\0') && (*(char *)(iVar1 + 0x3ec) != '\x04')) {
      iVar1 = *(int *)(param_9 + 0xe0);
      uVar2 = 1;
    }
    else {
      iVar1 = *(int *)(param_9 + 0xe4);
      uVar2 = 0x44;
    }
    zz_00076d0_((double)*(float *)(param_9 + 0x58),param_2,param_3,param_4,param_5,param_6,param_7,
                param_8,iVar1,(float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,
                param_15,param_16);
    zz_00097b4_(iVar1,uVar2);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0034.c 4815-4869 ==== */
// ==== 80130330  FUN_80130330 ====

void FUN_80130330(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  int iVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int unaff_r28;
  undefined8 uVar4;
  
  sVar1 = *(short *)(param_9 + 1000);
  if ((sVar1 == 0x106) || (sVar1 == 0x107)) {
    if (sVar1 == 0x106) {
      unaff_r28 = 0;
    }
    else if (sVar1 == 0x107) {
      unaff_r28 = 1;
    }
    iVar3 = zz_0006f98_(param_9);
    iVar2 = unaff_r28 * 4;
    uVar4 = zz_00086b8_((double)FLOAT_80439e78,param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,*(int *)(iVar3 + 0x600),
                        *(int *)(iVar3 + *(int *)(&DAT_804345c8 + iVar2) * 4 + 0x708),param_11,
                        param_12,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar3 + *(int *)(&DAT_804345c8 + iVar2) * 4 + 0x708),extraout_r4,param_11,
                param_12,param_13,param_14,param_15,param_16);
    uVar4 = zz_00086b8_((double)FLOAT_80439e78,param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,*(int *)(iVar3 + 0x600),
                        *(int *)(iVar3 + *(int *)(&DAT_804345c8 + iVar2) * 4 + 0x788),param_11,
                        param_12,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar3 + *(int *)(&DAT_804345c8 + iVar2) * 4 + 0x788),extraout_r4_00,
                param_11,param_12,param_13,param_14,param_15,param_16);
    if (*(short *)(param_9 + 1000) == 0x106) {
      zz_01c621c_(param_9,2);
      zz_01c621c_(param_9,3);
    }
    else {
      zz_01c621c_(param_9,0);
      zz_01c621c_(param_9,1);
    }
  }
  if (*(short *)(param_9 + 1000) == 0x103) {
    zz_012fd9c_(param_9,0);
    zz_012fd9c_(param_9,1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0034.c 4873-4950 ==== */
// ==== 801304b8  FUN_801304b8 ====

void FUN_801304b8(int param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  
  sVar2 = *(short *)(param_1 + 1000);
  if (sVar2 < 0x106) {
    if (sVar2 == 0x103) {
      *(undefined1 *)(param_1 + 0x1d94) = 0;
    }
  }
  else if (sVar2 < 0x108) {
    *(undefined1 *)(param_1 + 0x1d95) = 0;
    *(undefined1 *)(param_1 + 0x1d94) = 0;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    *(undefined2 *)(param_1 + 0x1918) = 0;
  }
  if (((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) && (*(float *)(param_1 + 0x694) <= FLOAT_80439e78)
     ) {
    if ((*(short *)(param_1 + 1000) == 0x106) && (iVar3 = zz_006dbe0_(param_1,0,1,1), iVar3 != 0)) {
      *(byte *)(param_1 + 0x15b) = *(byte *)(param_1 + 0x15b) | 1;
      zz_00e058c_(param_1,2,10);
      zz_00f036c_(param_1,0xeb);
    }
    if ((*(short *)(param_1 + 1000) == 0x107) && (iVar3 = zz_006dbe0_(param_1,0,1,1), iVar3 != 0)) {
      *(byte *)(param_1 + 0x15b) =
           *(byte *)(param_1 + 0x15b) | (byte)(1 << ((int)*(short *)(param_1 + 0x774) & 1U));
      zz_00e058c_(param_1,3,((byte)*(undefined2 *)(param_1 + 0x774) & 1) + 0xb);
      zz_00f036c_(param_1,0xaa);
    }
    *(float *)(param_1 + 0x694) = FLOAT_80439e7c + *(float *)(param_1 + 0x1dc8);
  }
  if ((*(uint *)(param_1 + 0x5bc) & 0x400) != 0) {
    if ((*(short *)(param_1 + 1000) == 0x107) &&
       (*(short *)(param_1 + 0x774) < *(short *)(param_1 + 0x78e))) {
      *(undefined1 *)(param_1 + 0x6f7) = 1;
    }
    if ((*(short *)(param_1 + 1000) == 0x103) && (*(float *)(param_1 + 0x694) <= FLOAT_80439e78)) {
      cVar1 = *(char *)(param_1 + 0x159);
      if (cVar1 == '\x01') {
        iVar3 = zz_006dbe0_(param_1,2,1,1);
        if (iVar3 == 0) {
          zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),2);
        }
        else {
          *(char *)(param_1 + 0x15a) = *(char *)(param_1 + 0x15a) + '\x01';
          zz_00f0214_(param_1,4,3);
          if ('\x06' < *(char *)(param_1 + 0x15a)) {
            *(undefined1 *)(param_1 + 0x15a) = 7;
          }
        }
        *(float *)(param_1 + 0x694) = FLOAT_80439e7c + *(float *)(param_1 + 0x1dc8);
      }
      else if ((cVar1 < '\x01') && (-1 < cVar1)) {
        iVar3 = zz_006dbe0_(param_1,2,1,1);
        if (iVar3 == 0) {
          zz_0011cc4_((int)*(char *)(param_1 + 0x3e4),2);
        }
        else {
          *(undefined1 *)(param_1 + 0x159) = 1;
          *(undefined1 *)(param_1 + 0x15a) = 1;
          zz_013b194_(param_1);
        }
        *(float *)(param_1 + 0x694) = FLOAT_80439e7c + *(float *)(param_1 + 0x1dc8);
      }
    }
  }
  if (*(char *)(param_1 + 0x159) == '\x01') {
    zz_00f0104_(param_1,4,3);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0034.c 4954-4961 ==== */
// ==== 80130788  FUN_80130788 ====

void FUN_80130788(int param_1)

{
  (*(code *)(&PTR_FUN_80335cb8)[*(char *)(param_1 + 0x580)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0034.c 4965-4977 ==== */
// ==== 801307c4  FUN_801307c4 ====

void FUN_801307c4(int param_1)

{
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_80439e88) * FLOAT_80439e80);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80335cc8)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0034.c 4981-4989 ==== */
// ==== 80130844  FUN_80130844 ====

void FUN_80130844(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80335cdc)[*(char *)(param_1 + 0x540)])();
  return;
}
