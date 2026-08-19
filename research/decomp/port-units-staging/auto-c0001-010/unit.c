#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_0011f30_(double param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,int param_10, float *param_11,undefined4 param_12,undefined4 *param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_800120b0(int param_1);
void FUN_800120c4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined1 *param_9, undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13, undefined4 param_14,undefined4 param_15,undefined4 param_16);
void FUN_8001212c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9,undefined4 param_10, float *param_11,undefined *param_12,undefined4 *param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_80012274(int param_1);
void zz_00122c8_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8);
void zz_00122e8_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,int param_9);
void zz_0012308_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4, undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 4292-4357 ==== */
// ==== 80011f30  zz_0011f30_ ====

void zz_0011f30_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                float *param_11,undefined4 param_12,undefined4 *param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  if (((*(char *)(param_9 + 0x171) == '\0') &&
      (param_10 = (&DAT_803c4e84)[(char)PTR_DAT_80433934[0xc0]],
      *(char *)(param_10 + 0x18) == '\x01')) &&
     ((*(short *)(param_9 + 0x94) != *(short *)(param_10 + 1000) ||
      ((*(char *)(param_9 + 0x96) != *(char *)(param_10 + 0x3e4) ||
       (*(char *)(param_9 + 0x174) != *(char *)(param_10 + 0x491))))))) {
    *(undefined1 *)(param_9 + 0x172) = 0xff;
    *(int *)(param_9 + 0x90) = param_10;
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(param_10 + 1000);
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(param_10 + 0x3e4);
    *(undefined1 *)(param_9 + 0x174) = *(undefined1 *)(param_10 + 0x491);
  }
  switch(*(undefined1 *)(param_9 + 0x11)) {
  case 0:
    zz_00122e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 2:
    zz_0012e4c_(param_9,param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 5:
    zz_0013a28_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 6:
    zz_00141d8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 7:
    zz_00156cc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
    break;
  case 8:
    zz_0015ca8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 9:
    zz_0016364_(param_9);
    break;
  case 10:
    zz_00165cc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 0xb:
    FUN_800169f0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 0xf:
    zz_0016f38_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 0x10:
    zz_0017380_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 0x11:
    zz_0017708_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 4361-4369 ==== */
// ==== 800120b0  FUN_800120b0 ====

void FUN_800120b0(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 4373-4399 ==== */
// ==== 800120c4  FUN_800120c4 ====

void FUN_800120c4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9,
                 undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
                 undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = 0;
  puVar2 = (undefined4 *)(param_9 + 0x144);
  do {
    if ((int *)*puVar2 != (int *)0x0) {
      param_1 = zz_0006d80_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int *)*puVar2,param_10,param_11,param_12,param_13,param_14,param_15,
                            param_16);
      param_10 = extraout_r4;
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 1;
  } while (iVar1 < 8);
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 4403-4474 ==== */
// ==== 8001212c  FUN_8001212c ====

void FUN_8001212c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined *param_12,undefined4 *param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  
  if ((((-1 < *(short *)(param_9 + 0x94)) && (-1 < *(char *)(param_9 + 0x96))) &&
      (cVar1 = zz_008b290_(), cVar1 == '\0')) &&
     (((PTR_DAT_80433934[0x1833] == '\0' && (PTR_DAT_80433934[0x1832] == '\0')) &&
      (PTR_DAT_80433930[0x33] == '\0')))) {
    switch(*(undefined1 *)(param_9 + 0x11)) {
    case 0:
      zz_0012984_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 2:
      zz_00131b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 3:
      zz_00133f4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 4:
      zz_0013690_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      break;
    case 5:
      zz_0013d80_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 6:
      zz_00147e0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 7:
      zz_0015a30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 8:
      FUN_80015ef0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 9:
      zz_00164e0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 10:
      zz_0016844_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0xb:
      FUN_80016c70(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0xf:
      zz_00171e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0x10:
      zz_0017558_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0x11:
      zz_001783c_(param_9);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 4478-4490 ==== */
// ==== 80012274  FUN_80012274 ====

void FUN_80012274(int param_1)

{
  FUN_80047aa4(param_1);
  gnt4_PSMTXMultVec_bl
            ((float *)(param_1 + 0x114),(float *)(param_1 + 0x164),(float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 4494-4502 ==== */
// ==== 800122c8  zz_00122c8_ ====

void zz_00122c8_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  zz_0012308_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 4506-4514 ==== */
// ==== 800122e8  zz_00122e8_ ====

void zz_00122e8_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  zz_0012638_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0001.c 4518-4675 ==== */
// ==== 80012308  zz_0012308_ ====

void zz_0012308_(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  char cVar5;
  undefined *puVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  undefined8 uVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  *(code **)(param_1 + 0x100) = FUN_80012274;
  zz_0089100_(param_1,0x21,1);
  *(undefined1 *)(param_1 + 0x84) = 3;
  *(undefined2 *)(param_1 + 0x70) = 0;
  dVar13 = DOUBLE_80436bd0;
  *(undefined2 *)(param_1 + 0x7c) = 0x444;
  fVar2 = FLOAT_80436bc0;
  dVar14 = (double)FLOAT_80436bc0;
  *(undefined2 *)(param_1 + 0x1c) = 0x14;
  fVar4 = FLOAT_80436bc8;
  fVar3 = FLOAT_80436bc4;
  dVar10 = (double)FLOAT_80436bc4;
  dVar12 = -(double)(float)(dVar14 / (double)(float)((double)CONCAT44(0x43300000,
                                                                      (int)*(short *)(param_1 + 0x1c
                                                                                     ) ^ 0x80000000)
                                                    - dVar13));
  *(float *)(param_1 + 0x38) = (float)dVar12;
  *(float *)(param_1 + 100) = fVar3;
  *(float *)(param_1 + 0x68) = fVar3;
  *(float *)(param_1 + 0x6c) = fVar4;
  *(float *)(param_1 + 0x164) = fVar2;
  *(float *)(param_1 + 0x16c) = fVar3;
  *(float *)(param_1 + 0x168) = fVar3;
  iVar1 = DAT_804361fc;
  uVar11 = zz_0006fb4_(dVar10,dVar12,dVar13,dVar14,in_f5,in_f6,in_f7,in_f8,DAT_804361fc,
                       *(int *)(param_1 + 0x144),(int)*(char *)(param_1 + 0x12),param_4,param_5,
                       param_6,param_7,param_8);
  iVar8 = *(int *)(param_1 + 0x148);
  zz_0006fb4_(uVar11,dVar12,dVar13,dVar14,in_f5,in_f6,in_f7,in_f8,iVar1,iVar8,
              (int)*(char *)(param_1 + 0x12),param_4,param_5,param_6,param_7,param_8);
  zz_0007cd0_(iVar8,0xff,0xea,0);
  uVar7 = 0;
  uVar11 = zz_0007cf4_(iVar8,0xe5,0xb2,0);
  iVar8 = 0;
  iVar9 = param_1 + 0x144;
  do {
    uVar11 = zz_0006fb4_(uVar11,dVar12,dVar13,dVar14,in_f5,in_f6,in_f7,in_f8,iVar1,
                         *(int *)(iVar9 + 8),*(char *)(param_1 + 0x12) * 2 + 2,uVar7,param_5,param_6
                         ,param_7,param_8);
    iVar8 = iVar8 + 1;
    iVar9 = iVar9 + 4;
  } while (iVar8 < 6);
  cVar5 = PTR_DAT_80433930[0x29];
  if (cVar5 == '\x02') goto LAB_800125b0;
  if (cVar5 < '\x02') {
    if (cVar5 == '\0') {
      if (*(char *)(param_1 + 0x12) == '\0') {
        cVar5 = '\0';
        iVar8 = (int)(char)PTR_DAT_80433934[0x53];
        puVar6 = PTR_DAT_80433934;
        if (0 < iVar8) {
          do {
            if (puVar6[0xf4] == PTR_DAT_80433934[(char)PTR_DAT_80433934[0xc0] + 0xcb]) {
              *(char *)(param_1 + 400) = cVar5;
              break;
            }
            puVar6 = puVar6 + 0x3c;
            cVar5 = cVar5 + '\x01';
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
        }
      }
      else {
        cVar5 = '\0';
        iVar8 = (int)(char)PTR_DAT_80433934[0x53];
        puVar6 = PTR_DAT_80433934;
        if (0 < iVar8) {
          do {
            if (puVar6[0xf4] != PTR_DAT_80433934[(char)PTR_DAT_80433934[0xc0] + 0xcb]) {
              *(char *)(param_1 + 400) = cVar5;
              break;
            }
            puVar6 = puVar6 + 0x3c;
            cVar5 = cVar5 + '\x01';
            iVar8 = iVar8 + -1;
          } while (iVar8 != 0);
        }
      }
      goto LAB_800125b0;
    }
    if (cVar5 < '\0') goto LAB_800125b0;
  }
  else if ('\x03' < cVar5) goto LAB_800125b0;
  if (*(char *)(param_1 + 0x12) == '\0') {
    cVar5 = '\0';
    iVar8 = (int)(char)PTR_DAT_80433934[0x53];
    puVar6 = PTR_DAT_80433934;
    if (0 < iVar8) {
      do {
        if (puVar6[0xf4] ==
            PTR_DAT_80433934[(char)PTR_DAT_80433934[*(char *)(param_1 + 0x173) + 0xc0] + 0xcb]) {
          *(char *)(param_1 + 400) = cVar5;
          break;
        }
        puVar6 = puVar6 + 0x3c;
        cVar5 = cVar5 + '\x01';
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
  }
  else {
    cVar5 = '\0';
    iVar8 = (int)(char)PTR_DAT_80433934[0x53];
    puVar6 = PTR_DAT_80433934;
    if (0 < iVar8) {
      do {
        if (puVar6[0xf4] !=
            PTR_DAT_80433934[(char)PTR_DAT_80433934[*(char *)(param_1 + 0x173) + 0xc0] + 0xcb]) {
          *(char *)(param_1 + 400) = cVar5;
          break;
        }
        puVar6 = puVar6 + 0x3c;
        cVar5 = cVar5 + '\x01';
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
  }
LAB_800125b0:
  fVar2 = FLOAT_80436bcc;
  *(float *)(param_1 + 0x180) = FLOAT_80436bcc;
  *(float *)(param_1 + 0x17c) = fVar2;
  iVar8 = *(int *)(PTR_DAT_80433934 + *(char *)(param_1 + 400) * 0x3c + 0x118);
  *(int *)(param_1 + 0x18c) = iVar8 + -1;
  *(int *)(param_1 + 0x184) = iVar8 + -1;
  uVar11 = zz_0006fb4_(uVar11,dVar12,dVar13,dVar14,in_f5,in_f6,in_f7,in_f8,iVar1,
                       *(int *)(param_1 + 0xe0),*(char *)(param_1 + 0x12) * 2 + 3,uVar7,param_5,
                       param_6,param_7,param_8);
  if (*(char *)(param_1 + 0x12) == '\0') {
    zz_0006fb4_(uVar11,dVar12,dVar13,dVar14,in_f5,in_f6,in_f7,in_f8,iVar1,*(int *)(param_1 + 0xe4),
                0x57,uVar7,param_5,param_6,param_7,param_8);
  }
  return;
}
