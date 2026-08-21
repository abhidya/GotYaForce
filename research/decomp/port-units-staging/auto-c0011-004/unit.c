#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80078c68(int param_1);
void FUN_80078fc8(int param_1);
undefined4 zz_007933c_(int param_1,uint param_2);
void zz_007950c_(int param_1);
void zz_00795e0_(int param_1);
void zz_0079754_(int param_1);
void zz_007978c_(int param_1);
void FUN_800798d4(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1140-1261 ==== */
// ==== 80078c68  FUN_80078c68 ====

void FUN_80078c68(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float local_38;
  float local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  fVar3 = FLOAT_80437848;
  if (*(char *)(param_1 + 0x541) == '\0') {
    if (*(char *)(param_1 + 0x1d9) == '\0') {
      if (*(int *)(param_1 + 0xcc) == 0) {
        *(float *)(param_1 + 0x44) =
             FLOAT_804378e0 *
             (*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) /
             FLOAT_80437878);
        *(float *)(param_1 + 0x4c) = fVar3;
        *(float *)(param_1 + 0x48) = fVar3;
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      }
      else {
        iVar4 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
        local_2c = *(float *)(iVar4 + 0x8e0);
        local_28 = *(float *)(iVar4 + 0x8f0);
        local_24 = *(undefined4 *)(iVar4 + 0x900);
        local_38 = *(float *)(param_1 + 0x518);
        local_30 = *(undefined4 *)(param_1 + 0x520);
        local_34 = FLOAT_80437858 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
        gnt4_PSVECSubtract_bl(&local_38,&local_2c,&local_2c);
        dVar5 = gnt4_PSVECMag_bl(&local_2c);
        fVar3 = FLOAT_80437848;
        if (dVar5 < (double)FLOAT_804378d8) {
          *(undefined1 *)(param_1 + 0x541) = 1;
          goto LAB_80078e40;
        }
        *(float *)(param_1 + 0x48) = local_28 * FLOAT_8043787c;
        fVar2 = *(float *)(param_1 + 0x48);
        if (fVar2 <= fVar3) {
          if (fVar2 < FLOAT_804378dc) {
            *(float *)(param_1 + 0x48) = FLOAT_804378dc;
          }
          *(float *)(param_1 + 0x50) = FLOAT_80437848;
        }
        else {
          if (FLOAT_80437884 < fVar2) {
            *(float *)(param_1 + 0x48) = FLOAT_80437884;
          }
          *(float *)(param_1 + 0x50) = FLOAT_804378a0;
        }
        local_28 = FLOAT_80437848;
        dVar5 = gnt4_PSVECMag_bl(&local_2c);
        fVar3 = FLOAT_80437880;
        *(float *)(param_1 + 0x44) = (float)(dVar5 * (double)FLOAT_8043787c);
        *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar3;
      }
      zz_006660c_(param_1);
      *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
    }
    else {
      *(undefined1 *)(param_1 + 0x541) = 1;
    }
  }
LAB_80078e40:
  zz_0067458_((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
  iVar4 = zz_00677b0_(param_1);
  if (iVar4 != 0) {
    zz_00b22f4_(param_1);
  }
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 == '\x01') {
    zz_0067754_(param_1,(short *)(param_1 + 0x72),0x3000);
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) && (*(char *)(param_1 + 0x1cee) != '\0')) {
    *(char *)(param_1 + 0x542) = cVar1 + '\x01';
    zz_01005ec_(param_1,0);
    *(undefined1 *)(param_1 + 0x6f7) = 0x38;
  }
  fVar3 = FLOAT_8043784c;
  dVar5 = DOUBLE_80437840;
  dVar6 = (double)FLOAT_80437848;
  if ((double)*(float *)(param_1 + 0x558) <= dVar6) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar2 = FLOAT_804378a4;
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(float *)(param_1 + 0x4c) = fVar3;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    fVar3 = fVar2 * (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x72) ^ 0x80000000
                                            ) - dVar5);
    dVar7 = (double)fVar3;
    *(float *)(param_1 + 0x170) = fVar3;
    dVar5 = (double)(fVar2 * (float)((double)CONCAT44(0x43300000,
                                                      (int)*(short *)(param_1 + 0x5ae) ^ 0x80000000)
                                    - dVar5));
    if (dVar7 < dVar6) {
      dVar7 = (double)(float)(DOUBLE_804378a8 + dVar7);
    }
    if (dVar5 < (double)FLOAT_80437848) {
      dVar5 = (double)(float)(DOUBLE_804378a8 + dVar5);
    }
    if (dVar5 < dVar7) {
      *(float *)(param_1 + 0x154) = FLOAT_804378b0 + (FLOAT_804378b4 - (float)(dVar7 - dVar5));
    }
    else {
      *(float *)(param_1 + 0x154) = FLOAT_804378b0 + (float)(dVar5 - dVar7);
    }
    *(undefined1 *)(param_1 + 0x175) = 0;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1265-1388 ==== */
// ==== 80078fc8  FUN_80078fc8 ====

void FUN_80078fc8(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  int iVar11;
  undefined4 uVar12;
  double dVar13;
  double local_18;
  
  fVar2 = FLOAT_80437848;
  cVar1 = *(char *)(param_1 + 0x542);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 != '\x04') {
        if (('\x03' < cVar1) || (iVar11 = zz_004cd24_(param_1,0xf), iVar11 != 1)) goto LAB_800792c4;
        *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
      }
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      if (*(char *)(param_1 + 0x545) == '\0') {
        zz_006a5a4_(param_1);
        return;
      }
      zz_006a474_(param_1);
      return;
    }
    if (cVar1 == '\0') {
      *(float *)(param_1 + 0x15c) = FLOAT_80437874;
      fVar9 = FLOAT_804378b8;
      fVar4 = FLOAT_804378a4;
      dVar13 = DOUBLE_80437840;
      *(float *)(param_1 + 0x4c) = -(*(float *)(param_1 + 0x44) / *(float *)(param_1 + 0x15c));
      *(float *)(param_1 + 0x144) = fVar2;
      *(float *)(param_1 + 0x14c) = fVar2;
      *(float *)(param_1 + 0x148) = fVar2;
      *(float *)(param_1 + 0x150) = fVar2;
      *(float *)(param_1 + 0x158) = fVar9;
      *(float *)(param_1 + 0x164) = fVar2;
      local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x72)) ^ 0x80000000);
      fVar4 = fVar4 * (float)(local_18 - dVar13);
      *(float *)(param_1 + 0x170) = fVar4;
      *(float *)(param_1 + 0x168) = fVar4;
      *(float *)(param_1 + 0x16c) = fVar4;
      *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
    }
    else if (cVar1 < '\0') goto LAB_800792c4;
    fVar9 = FLOAT_804378c0;
    fVar4 = FLOAT_804378bc;
    fVar2 = *(float *)(param_1 + 0x15c);
    if (*(float *)(param_1 + 0x164) < fVar2) {
      fVar3 = fVar2 - *(float *)(param_1 + 0x164);
      fVar5 = *(float *)(param_1 + 0x1dc8);
      if (fVar3 < *(float *)(param_1 + 0x1dc8)) {
        fVar5 = fVar3;
      }
      fVar3 = *(float *)(param_1 + 0x158);
      fVar6 = FLOAT_804378c0 * fVar3;
      fVar7 = FLOAT_804378c4 * fVar3;
      *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x14c);
      dVar13 = DOUBLE_804378d0;
      fVar10 = FLOAT_804378c8;
      fVar8 = FLOAT_80437860;
      *(float *)(param_1 + 0x14c) =
           ((fVar4 * *(float *)(param_1 + 0x154) + fVar6 * fVar2) / (fVar2 * fVar2 * fVar2)) * fVar5
           + *(float *)(param_1 + 0x14c);
      *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0x150);
      *(float *)(param_1 + 0x150) =
           ((*(float *)(param_1 + 0x14c) + *(float *)(param_1 + 0x144)) * fVar8 +
           (fVar9 * *(float *)(param_1 + 0x154) - fVar7 * fVar2) / (fVar2 * fVar2)) * fVar5 +
           *(float *)(param_1 + 0x150);
      fVar2 = ((*(float *)(param_1 + 0x150) + *(float *)(param_1 + 0x148)) * fVar8 + fVar3) * fVar5;
      *(float *)(param_1 + 0x16c) = *(float *)(param_1 + 0x16c) + fVar2;
      *(float *)(param_1 + 0x168) = *(float *)(param_1 + 0x168) + fVar2;
      *(short *)(param_1 + 0x72) = (short)(int)(fVar10 * *(float *)(param_1 + 0x16c));
      *(float *)(param_1 + 0x164) = *(float *)(param_1 + 0x164) + fVar5;
      if ((double)*(float *)(param_1 + 0x164) <= (double)*(float *)(param_1 + 0x15c) * dVar13) {
        *(char *)(param_1 + 0x6f7) = (char)((uint)(int)(fVar10 * fVar2) >> 8);
      }
      else if (*(char *)(param_1 + 0x175) == '\0') {
        *(undefined1 *)(param_1 + 0x175) = 1;
        dVar13 = (double)FLOAT_8043784c;
        *(undefined1 *)(param_1 + 0x6f7) = 0;
        zz_004beb8_(dVar13,param_1,0xf,4,4,0xffffffff,0xffffffff);
      }
      goto LAB_800792c4;
    }
    *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
  }
  if (*(char *)(param_1 + 0x174) == '\x01') {
    dVar13 = (double)FLOAT_8043784c;
    *(undefined1 *)(param_1 + 0x545) = 1;
    zz_004beb8_(dVar13,param_1,0xf,4,2,0xffffffff,0xffffffff);
  }
  else {
    dVar13 = (double)FLOAT_8043784c;
    *(undefined1 *)(param_1 + 0x545) = 0;
    zz_004beb8_(dVar13,param_1,0xf,0,0xd,0x14,1);
  }
  *(char *)(param_1 + 0x542) = *(char *)(param_1 + 0x542) + '\x01';
LAB_800792c4:
  zz_0067458_((double)FLOAT_80437850,param_1,*(short *)(param_1 + 0x5ae));
  uVar12 = zz_00677b0_(param_1);
  *(char *)(param_1 + 0x174) = (char)uVar12;
  if ((char)uVar12 != '\0') {
    if ((*(char *)(param_1 + 0x542) < '\x02') || (*(char *)(param_1 + 0x545) == '\x01')) {
      zz_00b22f4_(param_1);
    }
    else if ((*(char *)(param_1 + 0x545) == '\0') && ('\x02' < *(char *)(param_1 + 0x542))) {
      *(undefined1 *)(param_1 + 0x542) = 4;
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1392-1435 ==== */
// ==== 8007933c  zz_007933c_ ====

undefined4 zz_007933c_(int param_1,uint param_2)

{
  short sVar1;
  undefined4 uVar2;
  short sVar3;
  int iVar4;
  
  sVar1 = *(short *)(param_1 + 0x5aa);
  iVar4 = (int)sVar1;
  if (sVar1 < 0) {
    iVar4 = -iVar4;
  }
  sVar3 = (short)(int)((float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(*(int *)(param_1 + 0x4ac) +
                                                                (param_2 & 0xf) * 2 + 0xac) ^
                                                0x80000000) - DOUBLE_80437840) *
                      *(float *)(param_1 + 0x1dc8));
  if (sVar3 < iVar4) {
    sVar1 = *(short *)(param_1 + 0x72) - sVar3;
    if ((param_2 & 0x40) != 0) {
      *(short *)(param_1 + 0x5ae) = sVar1;
    }
    if ((param_2 & 0x80) != 0) {
      *(short *)(param_1 + 0x72) = sVar1;
    }
    *(short *)(param_1 + 0x5aa) = *(short *)(param_1 + 0x5aa) + sVar3;
    uVar2 = 0;
  }
  else {
    sVar1 = *(short *)(param_1 + 0x72) + sVar1;
    if ((param_2 & 0x40) != 0) {
      *(short *)(param_1 + 0x5ae) = sVar1;
    }
    if ((param_2 & 0x80) != 0) {
      *(short *)(param_1 + 0x72) = sVar1;
    }
    *(undefined2 *)(param_1 + 0x5aa) = 0;
    uVar2 = 1;
  }
  return uVar2;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1439-1462 ==== */
// ==== 8007950c  zz_007950c_ ====

void zz_007950c_(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(300);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    FUN_800e4294(param_1,-0x7fd29c90,2,puVar3 + 3,(float *)(puVar3 + 0x1b));
    FUN_800e4294(param_1,-0x7fd29c30,2,puVar3 + 9,(float *)(puVar3 + 0x21));
    FUN_800e4294(param_1,-0x7fd29bd0,2,puVar3 + 0xf,(float *)(puVar3 + 0x27));
    FUN_800e4294(param_1,-0x7fd29b70,2,puVar3 + 0x15,(float *)(puVar3 + 0x2d));
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1466-1498 ==== */
// ==== 800795e0  zz_00795e0_ ====

void zz_00795e0_(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar2 = *(undefined4 *)(param_1 + 0x20);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(param_1 + 0x28);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
      FUN_800e43e0(param_1,(float *)&DAT_802d6370,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x1b),
                   (int *)&DAT_802d6580);
      FUN_800e43e0(param_1,(float *)&DAT_802d63d0,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x21),
                   (int *)&DAT_802d658c);
      FUN_800e43e0(param_1,(float *)&DAT_802d6430,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x27)
                   ,(int *)&DAT_802d6598);
      FUN_800e43e0(param_1,(float *)&DAT_802d6490,2,(float *)(puVar2 + 0x15),
                   (float *)(puVar2 + 0x2d),(int *)&DAT_802d65a4);
    }
    else {
      FUN_800e4f9c(param_1,-0x7fd29c90,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x33));
      FUN_800e4f9c(param_1,-0x7fd29c30,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x39));
      FUN_800e4f9c(param_1,-0x7fd29bd0,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x3f));
      FUN_800e4f9c(param_1,-0x7fd29b70,2,(float *)(puVar2 + 0x15),(float *)(puVar2 + 0x45));
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1502-1510 ==== */
// ==== 80079754  zz_0079754_ ====

void zz_0079754_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1514-1540 ==== */
// ==== 8007978c  zz_007978c_ ====

void zz_007978c_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd29c90,2,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd29c30,2,pfVar2 + 9,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd29bd0,2,pfVar2 + 0xf,afStack_18);
    zz_00e4ec4_(param_1,-0x7fd29b70,2,pfVar2 + 0x15,afStack_18);
    zz_00e5184_(param_1,-0x7fd29c90,2,pfVar2 + 3,pfVar2 + 0x33);
    zz_00e5184_(param_1,-0x7fd29c30,2,pfVar2 + 9,pfVar2 + 0x39);
    zz_00e5184_(param_1,-0x7fd29bd0,2,pfVar2 + 0xf,pfVar2 + 0x3f);
    zz_00e5184_(param_1,-0x7fd29b70,2,pfVar2 + 0x15,pfVar2 + 0x45);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0011.c 1544-1565 ==== */
// ==== 800798d4  FUN_800798d4 ====

void FUN_800798d4(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x908) {
    zz_004eb98_(param_1,1);
  }
  else if (sVar1 < 0x908) {
    if (sVar1 == 0x900) {
      zz_004eb98_(param_1,0);
    }
  }
  else if (sVar1 == 0x90d) {
    zz_004eb98_(param_1,2);
  }
  zz_007950c_(param_1);
  return;
}
