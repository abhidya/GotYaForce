#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801ba3c0(int param_1);
void FUN_801ba3e4(int param_1);
void FUN_801ba408(int param_1);
void FUN_801ba42c(int param_1);
void FUN_801ba450(int param_1);
void FUN_801ba474(void);
void FUN_801ba4f8(void);
void FUN_801ba5e4(void);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3756-3763 ==== */
// ==== 801ba3c0  FUN_801ba3c0 ====

void FUN_801ba3c0(int param_1)

{
  zz_010b2f4_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3767-3774 ==== */
// ==== 801ba3e4  FUN_801ba3e4 ====

void FUN_801ba3e4(int param_1)

{
  zz_010b7ac_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3778-3785 ==== */
// ==== 801ba408  FUN_801ba408 ====

void FUN_801ba408(int param_1)

{
  zz_010bd10_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3789-3796 ==== */
// ==== 801ba42c  FUN_801ba42c ====

void FUN_801ba42c(int param_1)

{
  zz_010c220_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3800-3807 ==== */
// ==== 801ba450  FUN_801ba450 ====

void FUN_801ba450(int param_1)

{
  zz_010c590_(param_1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3811-3824 ==== */
// ==== 801ba474  FUN_801ba474 ====

void FUN_801ba474(void)

{
  if (PTR_DAT_80433930[1] == '\0') {
    PTR_DAT_80433930[1] = 1;
    PTR_DAT_80433930[0x40] = 0;
    zz_002a5f4_(0,0,0,0);
    gnt4_memset(PTR_DAT_80435a30,0,0x200);
  }
  (*(code *)(&PTR_FUN_803836b4)[*(short *)PTR_DAT_80435a30])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3828-3857 ==== */
// ==== 801ba4f8  FUN_801ba4f8 ====

void FUN_801ba4f8(void)

{
  int iVar1;
  
  *(short *)PTR_DAT_80435a30 = *(short *)PTR_DAT_80435a30 + 1;
  gnt4_memset(PTR_DAT_80433934,0,0x18b8);
  *(undefined4 *)(PTR_DAT_80433934 + 0x120) = 0xffffffff;
  iVar1 = 0;
  *(undefined4 *)(PTR_DAT_80435a30 + 0x24) = DAT_80436220;
  *(undefined4 *)(PTR_DAT_80435a30 + 0x28) = DAT_80436224;
  *(undefined1 **)(PTR_DAT_80435a30 + 0x2c) = &DAT_803bfe20;
  PTR_DAT_80435a30[0x47] = 0;
  while( true ) {
    if (3 < iVar1) break;
    if (PTR_DAT_80435a30[0x47] != '\0') break;
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar1) != 0) {
      PTR_DAT_80435a30[0x46] = (char)iVar1;
      PTR_DAT_80435a30[0x47] = (char)(1 << iVar1);
    }
    iVar1 = iVar1 + 1;
  }
  if (PTR_DAT_80435a30[0x47] == '\0') {
    PTR_DAT_80435a30[0x46] = 0;
    PTR_DAT_80435a30[0x47] = 1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 3861-3876 ==== */
// ==== 801ba5e4  FUN_801ba5e4 ====

void FUN_801ba5e4(void)

{
  int iVar1;
  
  iVar1 = zz_01f1280_();
  if (iVar1 != 0) {
    *(short *)PTR_DAT_80435a30 = *(short *)PTR_DAT_80435a30 + 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 6) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 2) = 0;
  }
  return;
}
