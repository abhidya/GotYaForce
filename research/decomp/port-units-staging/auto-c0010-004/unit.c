#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_007320c_(int param_1);
void zz_0073330_(int param_1);
void zz_00734d8_(int param_1);
void zz_0073558_(int param_1);
void zz_0073594_(int param_1);
void zz_00735c4_(int param_1);
void zz_00735f4_(int param_1);
void zz_0073624_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 839-900 ==== */
// ==== 8007320c  zz_007320c_ ====

void zz_007320c_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined1 uVar5;
  
  uVar3 = *(uint *)(param_1 + 0x5e0);
  if ((uVar3 & 0x100) == 0) {
    if ((uVar3 & 0x80) == 0) {
      if ((uVar3 & 0x20) == 0) {
        if ((uVar3 & 0x40) == 0) {
          if ((uVar3 & 0x10) == 0) {
            if (*(char *)(param_1 + 0x5e4) == '\x04') {
              uVar5 = 3;
            }
            else {
              uVar5 = 0;
            }
          }
          else {
            uVar5 = 1;
          }
        }
        else {
          uVar5 = 3;
        }
      }
      else if ((uVar3 & 0x40) == 0) {
        uVar5 = 0;
      }
      else {
        uVar5 = 3;
      }
    }
    else {
      uVar5 = 4;
    }
  }
  else {
    uVar5 = 5;
  }
  uVar4 = zz_006c674_(param_1);
  zz_006a3d0_(param_1,'\0',uVar5,(char)uVar4);
  *(undefined1 *)(param_1 + 0x540) = 1;
  fVar1 = FLOAT_80437790;
  uVar4 = 1;
  *(undefined1 *)(param_1 + 0x542) = 0;
  fVar2 = FLOAT_80437794;
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  *(char *)(param_1 + 0x1b04) = *(char *)(param_1 + 0x1b44);
  if (*(char *)(param_1 + 0x1b44) != '\0') {
    uVar4 = 0x12;
  }
  (*(code *)(&PTR_zz_00724c8__802d4348)[*(char *)(param_1 + 0x581)])(param_1,uVar4);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 904-974 ==== */
// ==== 80073330  zz_0073330_ ====

/* WARNING: Removing unreachable block (ram,0x800734b8) */
/* WARNING: Removing unreachable block (ram,0x80073340) */

void zz_0073330_(int param_1)

{
  short sVar1;
  int iVar2;
  byte *pbVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  *(undefined2 *)(param_1 + 0x1900) = 0;
  *(undefined2 *)(param_1 + 0x1918) = 0;
  zz_0046698_(param_1);
  if (*(int *)(param_1 + 0xcc) != 0) {
    iVar4 = 7;
    if (*(char *)(param_1 + 0x1b04) != '\0') {
      iVar4 = 0xb;
    }
    local_2c = *(float *)(param_1 + 0x910);
    local_28 = *(undefined4 *)(param_1 + 0x920);
    local_24 = *(undefined4 *)(param_1 + 0x930);
    local_38 = *(float *)(param_1 + 0x518);
    local_34 = *(float *)(param_1 + 0x51c);
    local_30 = *(undefined4 *)(param_1 + 0x520);
    gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_38);
    dVar6 = (double)local_34;
    local_34 = FLOAT_80437798;
    dVar5 = gnt4_PSVECMag_bl(&local_38);
    iVar2 = FUN_800452a0(dVar6,dVar5);
    sVar1 = (short)iVar2;
    if (iVar4 == 0xb) {
      sVar1 = -sVar1;
    }
    *(short *)(param_1 + iVar4 * 6 + 0x18d6) = sVar1;
    iVar2 = param_1 + iVar4 * 0xc;
    zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + iVar4 * 4 + 0x1996) * 0x30 + 0x8d4),
                (float *)(param_1 + iVar4 * 0x30 + 0x8d4),(short *)(param_1 + iVar4 * 6 + 0x18d4),
                (undefined4 *)(iVar2 + 0x12d4),(float *)(param_1 + iVar4 * 0x10 + 0xed4),
                (float *)(iVar2 + 0x15d4));
  }
  iVar4 = zz_006dbe0_(param_1,0,1,1);
  if (iVar4 != 0) {
    if (*(short *)(param_1 + 1000) == 0x100) {
      pbVar3 = &DAT_80433878;
    }
    else if (*(short *)(param_1 + 1000) == 0x108) {
      pbVar3 = (byte *)0x8043387a;
    }
    else {
      pbVar3 = (byte *)0x0;
    }
    if (pbVar3 != (byte *)0x0) {
      if (*(char *)(param_1 + 0x1b04) != '\0') {
        pbVar3 = pbVar3 + 1;
      }
      zz_0082824_(param_1,(uint)*pbVar3);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 978-999 ==== */
// ==== 800734d8  zz_00734d8_ ====

void zz_00734d8_(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80437794;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x558) = fVar1;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    if (*(short *)(param_1 + 1000) == 0x100) {
      zz_0082824_(param_1,0x14);
    }
    else if (*(short *)(param_1 + 1000) == 0x108) {
      zz_0082824_(param_1,0x46);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 1003-1010 ==== */
// ==== 80073558  zz_0073558_ ====

void zz_0073558_(int param_1)

{
  (*(code *)(&PTR_zz_0073594__802d4360)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 1014-1022 ==== */
// ==== 80073594  zz_0073594_ ====

void zz_0073594_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 1026-1034 ==== */
// ==== 800735c4  zz_00735c4_ ====

void zz_00735c4_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 1038-1046 ==== */
// ==== 800735f4  zz_00735f4_ ====

void zz_00735f4_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0161d7c_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0010.c 1050-1057 ==== */
// ==== 80073624  zz_0073624_ ====

void zz_0073624_(int param_1)

{
  zz_01618ac_(param_1);
  return;
}
