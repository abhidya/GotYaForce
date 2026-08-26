#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void zz_01b6564_(int param_1);
void zz_01b6608_(int param_1);
void zz_01b6644_(int param_1);
void zz_01b6694_(int param_1);
void zz_01b6798_(int param_1);
void zz_01b6868_(int param_1);
void zz_01b6968_(int param_1);
void zz_01b6a1c_(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 1252-1276 ==== */
// ==== 801b6564  zz_01b6564_ ====

void zz_01b6564_(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x71c) == '\0') {
    FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_8043b98c;
    if (*(float *)(param_1 + 0x44) < FLOAT_8043b98c) {
      *(float *)(param_1 + 0x44) = FLOAT_8043b98c;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x694) = FLOAT_8043b988 + *(float *)(param_1 + 0x1dc8);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 1280-1287 ==== */
// ==== 801b6608  zz_01b6608_ ====

void zz_01b6608_(int param_1)

{
  (*(code *)(&PTR_zz_01b6644__8038177c)[*(char *)(param_1 + 0x581)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 1291-1301 ==== */
// ==== 801b6644  zz_01b6644_ ====

void zz_01b6644_(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01b6694__8038178c)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 1305-1342 ==== */
// ==== 801b6694  zz_01b6694_ ====

void zz_01b6694_(int param_1)

{
  float fVar1;
  float fVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  else {
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  fVar2 = FLOAT_8043b9b0;
  fVar1 = FLOAT_8043b98c;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_8043b98c;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  else if (*(char *)(param_1 + 0x581) == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043b9b0;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  }
  fVar2 = FLOAT_8043b9ec;
  *(float *)(param_1 + 0x48) = FLOAT_8043b9e8;
  fVar1 = FLOAT_8043b9a0;
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x558) = fVar1;
  zz_006d144_(param_1,0xc1);
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043b990,param_1,0xf,4,0,0xffffffff,0xffffffff);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 1346-1370 ==== */
// ==== 801b6798  zz_01b6798_ ====

void zz_01b6798_(int param_1)

{
  float fVar1;
  int iVar2;
  
  if ((*(char *)(param_1 + 0x1cef) != '\x01') || (*(char *)(param_1 + 0x1cf0) != '\x03')) {
    zz_004cd24_(param_1,0xf);
  }
  fVar1 = FLOAT_8043b98c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x558) <= fVar1) || (iVar2 = zz_006d144_(param_1,0xc1), iVar2 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  fVar1 = FLOAT_8043b9b0;
  if (*(char *)(param_1 + 0x581) == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043b9b0;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  }
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 1374-1408 ==== */
// ==== 801b6868  zz_01b6868_ ====

void zz_01b6868_(int param_1)

{
  short sVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined1 *)(param_1 + 0x1cf0) = 0;
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 == 1) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x90c) {
        zz_014452c_(param_1,3);
      }
      else if ((sVar1 < 0x90c) && (sVar1 == 0x907)) {
        zz_014452c_(param_1,1);
      }
    }
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_006d144_(param_1,0xc1);
  fVar2 = FLOAT_8043b9b0;
  if (*(char *)(param_1 + 0x581) == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043b9b0;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
  }
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 1412-1435 ==== */
// ==== 801b6968  zz_01b6968_ ====

void zz_01b6968_(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  fVar1 = FLOAT_8043b9b0;
  if (*(char *)(param_1 + 0x581) == '\x02') {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043b9b0;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar1;
  }
  FUN_80067310((double)FLOAT_8043b99c,param_1,*(short *)(param_1 + 0x54a));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(float *)(param_1 + 0x694) = FLOAT_8043b994 + *(float *)(param_1 + 0x1dc8);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 1439-1449 ==== */
// ==== 801b6a1c  zz_01b6a1c_ ====

void zz_01b6a1c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) == '\x01') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01b6a6c__8038179c)[*(char *)(param_1 + 0x540)])();
  return;
}
