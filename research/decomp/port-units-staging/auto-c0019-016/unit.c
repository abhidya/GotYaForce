#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_800c01c8(void);
void FUN_800c020c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8);
void FUN_800c028c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,float *param_9,undefined4 param_10, float *param_11,float *param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_800c0358(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_800c0390(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10 ,undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_800c03b4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5, double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10 ,undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14, undefined4 param_15,undefined4 param_16);
void FUN_800c03fc(void);
uint FUN_800c0454(uint param_1,uint param_2);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 3995-4008 ==== */
// ==== 800c01c8  FUN_800c01c8 ====

void FUN_800c01c8(void)

{
  int iVar1;
  
  iVar1 = zz_00ff618_();
  if (iVar1 != 0) {
    *(short *)(PTR_DAT_80433940 + 2) = *(short *)(PTR_DAT_80433940 + 2) + 1;
    *(undefined2 *)(PTR_DAT_80433940 + 4) = 0;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4012-4032 ==== */
// ==== 800c020c  FUN_800c020c ====

void FUN_800c020c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  
  if (*(short *)(PTR_DAT_80433940 + 4) == 0) {
    *(undefined2 *)(PTR_DAT_80433940 + 4) = 1;
    PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] | 0x80;
    zz_01b1f10_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  iVar1 = zz_01b1fb8_();
  if (iVar1 != 1) {
    PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] & 0x7f;
    *(short *)(PTR_DAT_80433940 + 2) = *(short *)(PTR_DAT_80433940 + 2) + 1;
    *(undefined2 *)(PTR_DAT_80433940 + 4) = 0;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4036-4081 ==== */
// ==== 800c028c  FUN_800c028c ====

void FUN_800c028c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,float *param_9,undefined4 param_10,
                 float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined *extraout_r4;
  undefined *puVar2;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined8 uVar3;
  undefined4 auStack_28 [3];
  undefined4 auStack_1c [6];
  
  fVar1 = FLOAT_80438610;
  puVar2 = PTR_DAT_80433940;
  if (*(short *)(PTR_DAT_80433940 + 4) == 0) {
    *(undefined2 *)(PTR_DAT_80433940 + 4) = 1;
    *param_9 = fVar1;
  }
  else {
    *param_9 = *param_9 - FLOAT_80438604;
  }
  if (*param_9 <= FLOAT_8043860c) {
    param_11 = (float *)0x708;
    *param_9 = FLOAT_80438608;
    *(undefined2 *)(PTR_DAT_80433940 + 8) = 0x708;
    *(undefined2 *)PTR_DAT_80433940 = 1;
    *(undefined2 *)(PTR_DAT_80433940 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80433940 + 2) = 0;
    zz_01ae8a8_();
    puVar2 = extraout_r4;
  }
  uVar3 = zz_00088a4_((double)*param_9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      DAT_803bb470,puVar2,param_11,param_12,param_13,param_14,param_15,param_16);
  uVar3 = zz_0008970_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,auStack_28,
                      extraout_r4_00,(undefined *)param_11,param_12,param_13,param_14,param_15,
                      param_16);
  cCameraManager__HasCamera_cBaseCamera
            (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,auStack_1c,extraout_r4_01
             ,(undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4085-4105 ==== */
// ==== 800c0358  FUN_800c0358 ====

void FUN_800c0358(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined8 extraout_f1;
  undefined8 uVar1;
  
  zz_0008b58_();
  zz_0008cf4_();
  zz_01978d0_();
  zz_0040910_();
  uVar1 = zz_0005984_(0);
  zz_0008924_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14,
              param_15,param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4109-4121 ==== */
// ==== 800c0390  FUN_800c0390 ====

void FUN_800c0390(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  FUN_800c03b4(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
  FUN_800c03fc();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4125-4145 ==== */
// ==== 800c03b4  FUN_800c03b4 ====

void FUN_800c03b4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  zz_0087cf0_();
  zz_0089898_(0x28);
  zz_0089898_(0x38);
  zz_0089554_();
  zz_0089658_();
  uVar1 = zz_0040b94_();
  zz_0008948_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(float *)&DAT_803c7380,
              extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4149-4162 ==== */
// ==== 800c03fc  FUN_800c03fc ====

void FUN_800c03fc(void)

{
  zz_008a16c_();
  zz_0089c00_(0x28);
  zz_0089c00_(0x38);
  zz_0087814_();
  zz_008c0dc_(FUN_80089eb4);
  zz_008c104_(FUN_80089f28);
  zz_008c12c_(FUN_80089f9c);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0019.c 4166-4196 ==== */
// ==== 800c0454  FUN_800c0454 ====

uint FUN_800c0454(uint param_1,uint param_2)

{
  char cVar1;
  
  cVar1 = -1;
  if ((param_1 & 8) == 0) {
    if ((param_1 & 4) == 0) {
      if ((param_1 & 1) == 0) {
        if ((param_1 & 2) != 0) {
          cVar1 = '\x03';
        }
      }
      else {
        cVar1 = '\x02';
      }
    }
    else {
      cVar1 = '\x01';
    }
  }
  else {
    cVar1 = '\0';
  }
  if (-1 < cVar1) {
    param_2 = (uint)(byte)(&DAT_80301cf0)[(int)cVar1 + (char)param_2 * 4];
  }
  return param_2;
}
