#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01a1904_(int param_1);
void zz_01a1948_(int param_1);
void zz_01a1a1c_(int param_1);
void zz_01a1af0_(int param_1);
undefined4 zz_01a1bbc_(int param_1);
void zz_01a1c14_(int param_1);
void zz_01a1c50_(int param_1);
void zz_01a1ca0_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 1-9 ==== */
// ==== 801a1904  zz_01a1904_ ====

void zz_01a1904_(int param_1)

{
  *(undefined2 *)(param_1 + 0x1dfc) = 0;
  (*(code *)(&PTR_zz_01a1948__80378720)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 13-36 ==== */
// ==== 801a1948  zz_01a1948_ ====

void zz_01a1948_(int param_1)

{
  float fVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar2 = (double)FLOAT_8043b5a8;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043b598,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
              0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\r')) {
    zz_004beb8_((double)FLOAT_8043b598,param_1,2,0,0xd,0xffffffff,0xffffffff);
  }
  fVar1 = FLOAT_8043b594;
  *(float *)(param_1 + 0x558) = FLOAT_8043b5a4;
  *(float *)(param_1 + 0x80c) = fVar1;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 40-70 ==== */
// ==== 801a1a1c  zz_01a1a1c_ ====

void zz_01a1a1c_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  FUN_80067310((double)FLOAT_8043b5a8,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  fVar2 = FLOAT_8043b594;
  if (iVar3 == 0) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar2 < fVar1) goto LAB_801a1ad4;
  }
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_01a1af0_(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
LAB_801a1ad4:
  zz_00b22f4_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 74-101 ==== */
// ==== 801a1af0  zz_01a1af0_ ====

void zz_01a1af0_(int param_1)

{
  short sVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0x6ef) = 0;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    sVar1 = *(short *)(param_1 + 1000);
    if (sVar1 == 0x90b) {
      zz_00c67bc_(param_1,8,*(undefined1 *)(param_1 + 0x6ed));
    }
    else if ((sVar1 < 0x90b) && (sVar1 == 0x906)) {
      zz_0082824_(param_1,0x6a);
    }
    if (*(short *)(param_1 + 1000) == 0x90b) {
      zz_00f0104_(param_1,0x24,2);
    }
    *(char *)(param_1 + 0x6ed) = *(char *)(param_1 + 0x6ed) + '\x01';
    *(byte *)(param_1 + 0x6ed) = *(byte *)(param_1 + 0x6ed) & 1;
    *(undefined1 *)(param_1 + 0x6ef) = 1;
  }
  *(undefined1 *)(param_1 + 0x6ee) = 3;
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 105-121 ==== */
// ==== 801a1bbc  zz_01a1bbc_ ====

undefined4 zz_01a1bbc_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if (((*(short *)(param_1 + 1000) == 0x90b) && ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0)) &&
     (iVar1 = zz_006dbe0_(param_1,0,1,0), iVar1 != 0)) {
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 125-132 ==== */
// ==== 801a1c14  zz_01a1c14_ ====

void zz_01a1c14_(int param_1)

{
  (*(code *)(&PTR_zz_01a1c50__8037872c)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 136-146 ==== */
// ==== 801a1c50  zz_01a1c50_ ====

void zz_01a1c50_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01a1ca0__80378744)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0050.c 150-177 ==== */
// ==== 801a1ca0  zz_01a1ca0_ ====

void zz_01a1ca0_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  fVar2 = FLOAT_8043b5ac;
  fVar1 = FLOAT_8043b594;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(float *)(param_1 + 0x44) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(undefined1 *)(param_1 + 0x541) = 0;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  *(float *)(param_1 + 0x80c) = FLOAT_8043b594;
  return;
}
