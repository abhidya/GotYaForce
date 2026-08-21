#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801081d4(int param_1);
void FUN_801081f8(int param_1);
void FUN_8010821c(int param_1);
void FUN_80108250(int param_1);
void FUN_80108294(int param_1);
void FUN_80108344(int param_1);
void FUN_80108508(int param_1);
undefined4 FUN_80108530(int param_1);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2770-2777 ==== */
// ==== 801081d4  FUN_801081d4 ====

void FUN_801081d4(int param_1)

{
  zz_010c220_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2781-2788 ==== */
// ==== 801081f8  FUN_801081f8 ====

void FUN_801081f8(int param_1)

{
  zz_010c590_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2792-2804 ==== */
// ==== 8010821c  FUN_8010821c ====

void FUN_8010821c(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x306) {
    FUN_80108508(param_1);
  }
  else {
    FUN_80108250(param_1);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2808-2816 ==== */
// ==== 80108250  FUN_80108250 ====

void FUN_80108250(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_804344d8)[*(char *)(param_1 + 0x540)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2820-2846 ==== */
// ==== 80108294  FUN_80108294 ====

void FUN_80108294(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804394e8;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  zz_004beb8_((double)FLOAT_804394ec,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  FUN_80108344(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2850-2904 ==== */
// ==== 80108344  FUN_80108344 ====

void FUN_80108344(int param_1)

{
  char cVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_804394f0,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_804394f4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar2 = zz_00677b0_(param_1);
  if (((iVar2 == 0) || ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0)) ||
     (-1 < *(char *)(param_1 + 0x1cef))) {
    if ('\0' < *(char *)(param_1 + 0x1cef)) {
      *(undefined1 *)(param_1 + 0x1cef) = 0;
      cVar1 = *(char *)(param_1 + 0x146);
      if (cVar1 == '\x01') {
        iVar2 = zz_006dbe0_(param_1,2,1,1);
        if (iVar2 != 0) {
          *(undefined1 *)(param_1 + 0x146) = 2;
          FUN_800061a8(param_1,0x11);
        }
      }
      else if (((cVar1 < '\x01') && (-1 < cVar1)) &&
              (iVar2 = zz_006dbe0_(param_1,2,1,1), iVar2 != 0)) {
        FUN_800a6108(param_1,0);
        FUN_800061a8(param_1,0x11);
      }
    }
    if (*(char *)(param_1 + 0x1d0f) < '\0') {
      *(undefined1 *)(param_1 + 0x1d0f) = 0;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        zz_006a474_(param_1);
      }
      else {
        zz_006a5a4_(param_1);
      }
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804394f8 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2908-2915 ==== */
// ==== 80108508  FUN_80108508 ====

void FUN_80108508(int param_1)

{
  zz_010c9d8_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0029.c 2919-2936 ==== */
// ==== 80108530  FUN_80108530 ====

undefined4 FUN_80108530(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = zz_006dbe0_(param_1,2,1,1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    zz_016cc24_(param_1,0xf);
    uVar2 = 0x8444;
  }
  return uVar2;
}
