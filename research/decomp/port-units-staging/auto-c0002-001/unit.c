#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_80017ab8(void);
void FUN_80017b78(void);
void FUN_80017c2c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8, undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12, undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16);
void zz_0017cc4_(void);
void FUN_80017dbc(void);
void FUN_80017dfc(void);
void FUN_80017e9c(void);
void FUN_80017f94(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4, undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8, undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12, undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0002.c 239-272 ==== */
// ==== 80017ab8  FUN_80017ab8 ====

void FUN_80017ab8(void)

{
  char cVar1;
  int iVar2;
  
  cVar1 = PTR_DAT_8043393c[3];
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    PTR_DAT_8043393c[3] = cVar1 + '\x01';
    PTR_DAT_80433930[0x40] = 1;
  }
  iVar2 = zz_000a3c4_();
  if (iVar2 == 0) {
    zz_0018238_();
    zz_0018288_();
    zz_0027c1c_();
    PTR_DAT_8043393c[2] = PTR_DAT_8043393c[2] + '\x01';
    *(undefined2 *)(PTR_DAT_8043393c + 0xc) = 0xe40;
    *(undefined2 *)(PTR_DAT_8043393c + 10) = 0;
    *(undefined2 *)(PTR_DAT_8043393c + 0xe) = 0;
    PTR_DAT_8043393c[0x11] = 0;
    PTR_DAT_8043393c[0x10] = 1;
    zz_0027aac_(0,0x3c,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0002.c 276-301 ==== */
// ==== 80017b78  FUN_80017b78 ====

void FUN_80017b78(void)

{
  short sVar1;
  
  zz_0028264_();
  if (*PTR_DAT_80433934 == '\x02') {
    zz_0017cc4_();
    if (PTR_DAT_8043393c[0x11] != '\0') {
      zz_008c0dc_(&DAT_80018234);
    }
  }
  sVar1 = *(short *)(PTR_DAT_8043393c + 0xc);
  *(short *)(PTR_DAT_8043393c + 0xc) = sVar1 + -1;
  if ((short)(sVar1 + -1) < 1) {
    PTR_DAT_8043393c[2] = PTR_DAT_8043393c[2] + '\x01';
    PTR_DAT_8043393c[3] = 0;
    zz_0027aac_(0,0x3c,1);
    zz_00f07c4_();
    zz_00f0920_(0);
    zz_00e9b60_((double)FLOAT_80436d38,2,0x3c,2);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0002.c 305-339 ==== */
// ==== 80017c2c  FUN_80017c2c ====

void FUN_80017c2c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  undefined8 uVar4;
  
  cVar1 = PTR_DAT_8043393c[3];
  if (cVar1 == '\x01') {
    iVar3 = zz_000a3c4_();
    if (iVar3 == 0) {
      uVar4 = zz_0018270_();
      PTR_DAT_8043393c[1] = 3;
      PTR_DAT_8043393c[2] = 0;
      puVar2 = PTR_DAT_8043393c;
      PTR_DAT_8043393c[0x10] = 0;
      zz_00282c0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar2,3,param_11,
                  param_12,param_13,param_14,param_15,param_16);
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_0028264_();
    iVar3 = zz_0027adc_();
    if (iVar3 == 0) {
      PTR_DAT_8043393c[3] = PTR_DAT_8043393c[3] + '\x01';
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0002.c 343-380 ==== */
// ==== 80017cc4  zz_0017cc4_ ====

void zz_0017cc4_(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(short *)(PTR_DAT_8043393c + 10) * 4;
  if (*(short *)(PTR_DAT_8043393c + 0xe) == 0) {
    *(short *)(PTR_DAT_8043393c + 10) = *(short *)(PTR_DAT_8043393c + 10) + 1;
    iVar2 = *(int *)(&DAT_802c4a28 + iVar1);
    if (iVar2 == 2) {
      PTR_DAT_8043393c[0x11] = 0;
      zz_008b010_(0);
    }
    else if (iVar2 < 2) {
      if (iVar2 == 0) {
        *(short *)(PTR_DAT_8043393c + 0xe) = (short)*(undefined4 *)(&DAT_802c4a2c + iVar1);
        *(short *)(PTR_DAT_8043393c + 10) = *(short *)(PTR_DAT_8043393c + 10) + 1;
      }
      else if (-1 < iVar2) {
        zz_008b010_(1);
      }
    }
    else if (iVar2 == 4) {
      *(undefined2 *)(PTR_DAT_8043393c + 0xc) = 1;
    }
    else if (iVar2 < 4) {
      PTR_DAT_8043393c[0x11] = (char)*(undefined4 *)(&DAT_802c4a2c + iVar1);
      *(short *)(PTR_DAT_8043393c + 10) = *(short *)(PTR_DAT_8043393c + 10) + 1;
    }
  }
  else {
    *(short *)(PTR_DAT_8043393c + 0xe) = *(short *)(PTR_DAT_8043393c + 0xe) + -1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0002.c 384-391 ==== */
// ==== 80017dbc  FUN_80017dbc ====

void FUN_80017dbc(void)

{
  (*(code *)(&PTR_FUN_802c4ad4)[(char)PTR_DAT_8043393c[2]])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0002.c 395-424 ==== */
// ==== 80017dfc  FUN_80017dfc ====

void FUN_80017dfc(void)

{
  char cVar1;
  int iVar2;
  
  cVar1 = PTR_DAT_8043393c[3];
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    PTR_DAT_8043393c[3] = cVar1 + '\x01';
    PTR_DAT_80433930[0x40] = 1;
  }
  iVar2 = zz_000a3c4_();
  if (iVar2 == 0) {
    zz_0018494_();
    zz_0027c1c_();
    PTR_DAT_8043393c[2] = PTR_DAT_8043393c[2] + '\x01';
    *(undefined2 *)(PTR_DAT_8043393c + 0xc) = 0xe40;
    PTR_DAT_8043393c[0x10] = 1;
    zz_0027aac_(0,0x3c,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0002.c 428-471 ==== */
// ==== 80017e9c  FUN_80017e9c ====

void FUN_80017e9c(void)

{
  undefined4 *puVar1;
  short sVar2;
  undefined *puVar3;
  
  zz_0028264_();
  puVar3 = PTR_DAT_80433934;
  if (*PTR_DAT_80433934 == '\x02') {
    puVar1 = (undefined4 *)(PTR_DAT_80433934 + 0x114);
    *(undefined4 *)(PTR_DAT_80433934 + 0x11c) = *puVar1;
    *(undefined4 *)(puVar3 + 0x118) = *puVar1;
    puVar3 = PTR_DAT_80433934;
    puVar1 = (undefined4 *)(PTR_DAT_80433934 + 0x150);
    *(undefined4 *)(PTR_DAT_80433934 + 0x158) = *puVar1;
    *(undefined4 *)(puVar3 + 0x154) = *puVar1;
    puVar3 = PTR_DAT_80433934;
    puVar1 = (undefined4 *)(PTR_DAT_80433934 + 0x18c);
    *(undefined4 *)(PTR_DAT_80433934 + 0x194) = *puVar1;
    *(undefined4 *)(puVar3 + 400) = *puVar1;
    puVar3 = PTR_DAT_80433934;
    puVar1 = (undefined4 *)(PTR_DAT_80433934 + 0x1c8);
    *(undefined4 *)(PTR_DAT_80433934 + 0x1d0) = *puVar1;
    *(undefined4 *)(puVar3 + 0x1cc) = *puVar1;
    *(undefined4 *)(PTR_DAT_80433934 + 0x4c) = *(undefined4 *)(PTR_DAT_80433934 + 0x48);
    if ((DAT_803c727c & 0x1000) != 0) {
      *(undefined2 *)(PTR_DAT_8043393c + 0xc) = 1;
    }
  }
  sVar2 = *(short *)(PTR_DAT_8043393c + 0xc);
  *(short *)(PTR_DAT_8043393c + 0xc) = sVar2 + -1;
  if ((short)(sVar2 + -1) < 1) {
    PTR_DAT_8043393c[2] = PTR_DAT_8043393c[2] + '\x01';
    PTR_DAT_8043393c[3] = 0;
    zz_0027aac_(0,0x3c,1);
    zz_00f07c4_();
    zz_00f0920_(0);
    zz_00e9b60_((double)FLOAT_80436d38,2,0x3c,2);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0002.c 475-507 ==== */
// ==== 80017f94  FUN_80017f94 ====

void FUN_80017f94(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  
  cVar1 = PTR_DAT_8043393c[3];
  if (cVar1 == '\x01') {
    iVar3 = zz_000a3c4_();
    if (iVar3 == 0) {
      PTR_DAT_8043393c[1] = 3;
      PTR_DAT_8043393c[2] = 0;
      puVar2 = PTR_DAT_8043393c;
      PTR_DAT_8043393c[0x10] = 0;
      zz_00282c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar2,3,param_11,
                  param_12,param_13,param_14,param_15,param_16);
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_0028264_();
    iVar3 = zz_0027adc_();
    if (iVar3 == 0) {
      PTR_DAT_8043393c[3] = PTR_DAT_8043393c[3] + '\x01';
    }
  }
  return;
}
