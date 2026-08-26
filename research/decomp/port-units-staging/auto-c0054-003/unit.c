#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801bdca0(void);
void FUN_801bdcdc(void);
void FUN_801bdd90(void);
void FUN_801bdfe0(void);
void FUN_801be26c(void);
void FUN_801be2a8(void);
void FUN_801be35c(void);
void FUN_801be4f0(void);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 1240-1247 ==== */
// ==== 801bdca0  FUN_801bdca0 ====

void FUN_801bdca0(void)

{
  (*(code *)(&PTR_FUN_803837c8)[*(short *)(PTR_DAT_80435a30 + 0x16)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 1251-1266 ==== */
// ==== 801bdcdc  FUN_801bdcdc ====

void FUN_801bdcdc(void)

{
  *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 1;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
  PTR_DAT_80435a30[0x15a] = 0;
  PTR_DAT_80435a30[0x15b] = 0;
  PTR_DAT_80435a30[0x15c] = 4;
  PTR_DAT_80435a30[0x15d] = 4;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 4;
  *(undefined4 *)(PTR_DAT_80435a30 + 0x154) = 0;
  zz_01e488c_(PTR_DAT_80435a30[0x46],8,2);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 1270-1340 ==== */
// ==== 801bdd90  FUN_801bdd90 ====

void FUN_801bdd90(void)

{
  int iVar1;
  
  iVar1 = (int)(char)PTR_DAT_80435a30[0x15b];
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x8008) == 0) {
    if (((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x4004) != 0) &&
       (iVar1 = iVar1 + 1, (char)PTR_DAT_80435a30[0x15c] + -1 < iVar1)) {
      iVar1 = 0;
    }
  }
  else {
    iVar1 = iVar1 + -1;
    if (iVar1 < 0) {
      iVar1 = (char)PTR_DAT_80435a30[0x15c] + -1;
    }
  }
  if (iVar1 != (char)PTR_DAT_80435a30[0x15b]) {
    PTR_DAT_80435a30[0x15b] = (char)iVar1;
    zz_00f0468_(0,0x77,0);
  }
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0xa00) == 0) {
    if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x100) != 0) {
      iVar1 = (int)(char)PTR_DAT_80435a30[0x15b];
      if ((*(uint *)(PTR_DAT_80435a30 + 0x154) & 1 << iVar1) == 0) {
        if (iVar1 < 3) {
          *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 3;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
          if (PTR_DAT_80435a30[0x14c] == (&DAT_80435a44)[(char)PTR_DAT_80435a30[0x15b] * 2]) {
            PTR_DAT_80435a30[0x14d] = PTR_DAT_80435a30[0x14d] ^ 1;
          }
          else {
            *(undefined2 *)(PTR_DAT_80435a30 + 0x152) = *(undefined2 *)(PTR_DAT_80435a30 + 0x150);
            *(undefined2 *)(PTR_DAT_80435a30 + 0x150) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14e);
            *(undefined2 *)(PTR_DAT_80435a30 + 0x14e) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14c);
            *(undefined2 *)(PTR_DAT_80435a30 + 0x14c) =
                 *(undefined2 *)(&DAT_80435a44 + (char)PTR_DAT_80435a30[0x15b] * 2);
          }
          zz_01cd1b4_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                      (short *)&DAT_803d4b60,2,PTR_DAT_80435a30 + 0x14c);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
        }
        else if (iVar1 == 3) {
          *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 1;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
          *(undefined4 *)(PTR_DAT_80435a30 + 0x154) = 0;
          PTR_DAT_80435a30[0x15a] = 0;
          PTR_DAT_80435a30[0x15b] = 0;
          PTR_DAT_80435a30[0x15c] = 0x15;
          PTR_DAT_80435a30[0x15d] = 8;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0x20;
          zz_01e488c_(PTR_DAT_80435a30[0x46],8,5);
        }
        zz_00f0468_(0,0x7a,0);
      }
      else {
        zz_00f0468_(0,0x7d,0);
      }
    }
  }
  else {
    *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 3;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 1344-1415 ==== */
// ==== 801bdfe0  FUN_801bdfe0 ====

void FUN_801bdfe0(void)

{
  char cVar1;
  int iVar2;
  
  iVar2 = (int)(char)PTR_DAT_80435a30[0x15b];
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x8008) == 0) {
    if (((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x4004) != 0) &&
       (iVar2 = iVar2 + 1, (char)PTR_DAT_80435a30[0x15c] + -1 < iVar2)) {
      iVar2 = 0;
    }
  }
  else {
    iVar2 = iVar2 + -1;
    if (iVar2 < 0) {
      iVar2 = (char)PTR_DAT_80435a30[0x15c] + -1;
    }
  }
  if (iVar2 != (char)PTR_DAT_80435a30[0x15b]) {
    PTR_DAT_80435a30[0x15b] = (char)iVar2;
    zz_00f0468_(0,0x77,0);
  }
  cVar1 = PTR_DAT_80435a30[0x15b];
  if ((int)cVar1 < (int)(char)PTR_DAT_80435a30[0x15a]) {
    PTR_DAT_80435a30[0x15a] = cVar1;
  }
  else if ((int)(char)PTR_DAT_80435a30[0x15a] + (char)PTR_DAT_80435a30[0x15d] + -1 < (int)cVar1) {
    PTR_DAT_80435a30[0x15a] = cVar1 - (char)((char)PTR_DAT_80435a30[0x15d] + -1);
  }
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x200) == 0) {
    if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x100) != 0) {
      if ((*(uint *)(PTR_DAT_80435a30 + 0x154) & 1 << (int)(char)PTR_DAT_80435a30[0x15b]) == 0) {
        *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 1;
        *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
        if (PTR_DAT_80435a30[0x15b] == '\0') {
          *(undefined4 *)(PTR_DAT_80435a30 + 0x164) = 0xffffffff;
        }
        else {
          *(int *)(PTR_DAT_80435a30 + 0x164) = 1 << (char)PTR_DAT_80435a30[0x15b] + -1;
        }
        *(undefined2 *)(PTR_DAT_80435a30 + 0x15e) = 0;
        *(undefined2 *)(PTR_DAT_80435a30 + 0x160) = 0;
        iVar2 = zz_01cd060_(*(short **)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                            -0x7fc2b4a0,2,*(uint *)(PTR_DAT_80435a30 + 0x164));
        *(short *)(PTR_DAT_80435a30 + 0x162) = (short)iVar2;
        zz_01cd1b4_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                    (short *)&DAT_803d4b60,2,PTR_DAT_80435a30 + 0x14c);
        *(ushort *)(PTR_DAT_80435a30 + 0x158) = *(ushort *)(PTR_DAT_80435a30 + 0x158) & 0xffdf;
        zz_00f0468_(0,0x7a,0);
      }
      else {
        zz_00f0468_(0,0x7d,0);
      }
    }
  }
  else {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
    *(undefined4 *)(PTR_DAT_80435a30 + 0x154) = 0;
    PTR_DAT_80435a30[0x15a] = 0;
    PTR_DAT_80435a30[0x15b] = 3;
    PTR_DAT_80435a30[0x15c] = 4;
    PTR_DAT_80435a30[0x15d] = 4;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 4;
    zz_01e488c_(PTR_DAT_80435a30[0x46],8,2);
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 1419-1426 ==== */
// ==== 801be26c  FUN_801be26c ====

void FUN_801be26c(void)

{
  (*(code *)(&PTR_FUN_803837e0)[*(short *)(PTR_DAT_80435a30 + 0x16)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 1430-1445 ==== */
// ==== 801be2a8  FUN_801be2a8 ====

void FUN_801be2a8(void)

{
  *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 1;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
  PTR_DAT_80435a30[0x15a] = 0;
  PTR_DAT_80435a30[0x15b] = 0;
  PTR_DAT_80435a30[0x15c] = 1;
  PTR_DAT_80435a30[0x15d] = 1;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0x10;
  zz_01bfbe4_();
  zz_01e488c_(PTR_DAT_80435a30[0x46],8,4);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 1449-1501 ==== */
// ==== 801be35c  FUN_801be35c ====

void FUN_801be35c(void)

{
  int iVar1;
  
  iVar1 = (int)(char)PTR_DAT_80435a30[0x15b];
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x8008) == 0) {
    if (((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x4004) != 0) &&
       (iVar1 = iVar1 + 1, (char)PTR_DAT_80435a30[0x15c] + -1 < iVar1)) {
      iVar1 = 0;
    }
  }
  else {
    iVar1 = iVar1 + -1;
    if (iVar1 < 0) {
      iVar1 = (char)PTR_DAT_80435a30[0x15c] + -1;
    }
  }
  if (iVar1 != (char)PTR_DAT_80435a30[0x15b]) {
    PTR_DAT_80435a30[0x15b] = (char)iVar1;
    zz_00f0468_(0,0x77,0);
  }
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x200) == 0) {
    if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x100) != 0) {
      if ((*(uint *)(PTR_DAT_80435a30 + 0x154) & 1 << (int)(char)PTR_DAT_80435a30[0x15b]) == 0) {
        if (PTR_DAT_80435a30[0x15b] == '\0') {
          *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 1;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
          *(undefined4 *)(PTR_DAT_80435a30 + 0x154) = 0;
          PTR_DAT_80435a30[0x15a] = 0;
          PTR_DAT_80435a30[0x15b] = 1;
          PTR_DAT_80435a30[0x15c] = 2;
          PTR_DAT_80435a30[0x15d] = 2;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0x80;
          zz_01e488c_(PTR_DAT_80435a30[0x46],7,7);
        }
        zz_00f0468_(0,0x7a,0);
      }
      else {
        zz_00f0468_(0,0x7d,0);
      }
    }
  }
  else {
    *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 3;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 1505-1563 ==== */
// ==== 801be4f0  FUN_801be4f0 ====

void FUN_801be4f0(void)

{
  int iVar1;
  
  iVar1 = (int)(char)PTR_DAT_80435a30[0x15b];
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x8008) == 0) {
    if (((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x4004) != 0) &&
       (iVar1 = iVar1 + 1, (char)PTR_DAT_80435a30[0x15c] + -1 < iVar1)) {
      iVar1 = 0;
    }
  }
  else {
    iVar1 = iVar1 + -1;
    if (iVar1 < 0) {
      iVar1 = (char)PTR_DAT_80435a30[0x15c] + -1;
    }
  }
  if (iVar1 != (char)PTR_DAT_80435a30[0x15b]) {
    PTR_DAT_80435a30[0x15b] = (char)iVar1;
    zz_00f0468_(0,0x77,0);
  }
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x200) == 0) {
    if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x100) != 0) {
      if ((*(uint *)(PTR_DAT_80435a30 + 0x154) & 1 << (int)(char)PTR_DAT_80435a30[0x15b]) == 0) {
        *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 1;
        *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
        if (PTR_DAT_80435a30[0x15b] == '\0') {
          zz_01cbe14_(*(int *)(PTR_DAT_80435a30 + 0x28),(int)*(short *)(PTR_DAT_80435a30 + 0x168));
          iVar1 = zz_01cd060_(*(short **)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24)
                              ,-0x7fc2b4a0,2,*(uint *)(PTR_DAT_80435a30 + 0x164));
          *(short *)(PTR_DAT_80435a30 + 0x162) = (short)iVar1;
          zz_01cd1b4_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                      (short *)&DAT_803d4b60,2,PTR_DAT_80435a30 + 0x14c);
        }
        *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
        zz_00f0468_(0,0x7a,0);
      }
      else {
        zz_00f0468_(0,0x7d,0);
      }
    }
  }
  else {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
    PTR_DAT_80435a30[0x15a] = 0;
    PTR_DAT_80435a30[0x15b] = 0;
    PTR_DAT_80435a30[0x15c] = 1;
    PTR_DAT_80435a30[0x15d] = 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0x10;
    zz_01bfbe4_();
    zz_01e488c_(PTR_DAT_80435a30[0x46],8,4);
    zz_00f0468_(0,0x7b,0);
  }
  return;
}
