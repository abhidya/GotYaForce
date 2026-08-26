#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801bb21c(void);
void FUN_801bb2d0(void);
void FUN_801bb69c(void);
void FUN_801bb8c8(void);
void FUN_801bb990(void);
void FUN_801bb9cc(void);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4379-4394 ==== */
// ==== 801bb21c  FUN_801bb21c ====

void FUN_801bb21c(void)

{
  *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 1;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
  PTR_DAT_80435a30[0x15a] = 0;
  PTR_DAT_80435a30[0x15b] = 0;
  PTR_DAT_80435a30[0x15c] = 6;
  PTR_DAT_80435a30[0x15d] = 6;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 1;
  zz_01bfa54_();
  zz_01e488c_(PTR_DAT_80435a30[0x46],8,0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4398-4517 ==== */
// ==== 801bb2d0  FUN_801bb2d0 ====

void FUN_801bb2d0(void)

{
  int iVar1;
  undefined1 uVar2;
  int iVar3;
  
  iVar3 = (int)(char)PTR_DAT_80435a30[0x15b];
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x8008) == 0) {
    if (((*(uint *)(PTR_DAT_80435a30 + 0x1d8) & 0x4004) != 0) &&
       (iVar3 = iVar3 + 1, (char)PTR_DAT_80435a30[0x15c] + -1 < iVar3)) {
      iVar3 = 0;
    }
  }
  else {
    iVar3 = iVar3 + -1;
    if (iVar3 < 0) {
      iVar3 = (char)PTR_DAT_80435a30[0x15c] + -1;
    }
  }
  if (iVar3 != (char)PTR_DAT_80435a30[0x15b]) {
    PTR_DAT_80435a30[0x15b] = (char)iVar3;
    zz_00f0468_(0,0x77,0);
  }
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0xa00) == 0) {
    if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x100) != 0) {
      iVar3 = (int)(char)PTR_DAT_80435a30[0x15b];
      if ((*(uint *)(PTR_DAT_80435a30 + 0x154) & 1 << iVar3) == 0) {
        if (PTR_DAT_80435a30[0x15b] == '\0') {
          *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 5;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 3;
          zz_0027aac_(0,0x1e,1);
        }
        else if (iVar3 == 1) {
          *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 5;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
        }
        else if (iVar3 == 2) {
          *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 3;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
          iVar3 = zz_01cc7b4_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40]);
          if (-1 < iVar3) {
            iVar1 = iVar3 - (char)PTR_DAT_80435a30[0x40];
            if (iVar1 < 0) {
              iVar1 = iVar1 + 0x14;
            }
            uVar2 = 1;
            if (iVar1 < 0xb) {
              uVar2 = 0xff;
            }
            zz_01c13c8_(PTR_DAT_80435a30[0x46],2,uVar2);
            PTR_DAT_80435a30[0x52] = 0;
            PTR_DAT_80435a30[0x40] = (char)iVar3;
            PTR_DAT_80435a30[0x41] = 0x10;
          }
        }
        else if (iVar3 == 3) {
          *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 3;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
          zz_01cc960_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40]);
        }
        else if (iVar3 == 4) {
          *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 3;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
          if (*(short *)(PTR_DAT_80435a30 + 0x144) < 0) {
            zz_01cc418_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)*(short *)(PTR_DAT_80435a30 + 0x146))
            ;
            zz_01cbf38_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                        (int)*(short *)(PTR_DAT_80435a30 + 0x146));
            *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
          }
          else {
            zz_01cbf38_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                        (int)*(short *)(PTR_DAT_80435a30 + 0x144));
            if (*(short *)(PTR_DAT_80435a30 + 0x146) == *(short *)(PTR_DAT_80435a30 + 0x144)) {
              *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
            }
            *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
          }
          *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = 2;
        }
        else if (iVar3 == 5) {
          if (*(short *)(PTR_DAT_80435a30 + 0x144) < 0) {
            zz_01cc418_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)*(short *)(PTR_DAT_80435a30 + 0x146))
            ;
          }
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4521-4587 ==== */
// ==== 801bb69c  FUN_801bb69c ====

void FUN_801bb69c(void)

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
          if (*(short *)(PTR_DAT_80435a30 + 0x144) < 0) {
            zz_01cbe54_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)*(short *)(PTR_DAT_80435a30 + 0x146))
            ;
            *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
          }
          else {
            zz_01cbe54_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)*(short *)(PTR_DAT_80435a30 + 0x144))
            ;
            if (*(short *)(PTR_DAT_80435a30 + 0x146) == *(short *)(PTR_DAT_80435a30 + 0x144)) {
              *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
            }
            *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
          }
          *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = 2;
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
    PTR_DAT_80435a30[0x15b] = 5;
    PTR_DAT_80435a30[0x15c] = 6;
    PTR_DAT_80435a30[0x15d] = 6;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 1;
    zz_01bfa54_();
    zz_01e488c_(PTR_DAT_80435a30[0x46],8,0);
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4591-4623 ==== */
// ==== 801bb8c8  FUN_801bb8c8 ====

void FUN_801bb8c8(void)

{
  short sVar1;
  int iVar2;
  
  iVar2 = zz_0027adc_();
  if (iVar2 == 0) {
    sVar1 = *(short *)(PTR_DAT_80435a30 + 0x16);
    if (sVar1 == 0) {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 1;
      PTR_DAT_80435a30[0x149] = 3;
    }
    else if (sVar1 == 1) {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 3;
      PTR_DAT_80435a30[0x149] = 1;
    }
    else if (sVar1 == 2) {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 4;
      PTR_DAT_80435a30[0x149] = 2;
    }
    else if (sVar1 == 3) {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 2;
      PTR_DAT_80435a30[0x149] = 0;
      *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
    }
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4627-4634 ==== */
// ==== 801bb990  FUN_801bb990 ====

void FUN_801bb990(void)

{
  (*(code *)(&PTR_FUN_80383724)[*(short *)(PTR_DAT_80435a30 + 0x14)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4638-4665 ==== */
// ==== 801bb9cc  FUN_801bb9cc ====

void FUN_801bb9cc(void)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = &DAT_80383648;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 1;
  while( true ) {
    if (*pcVar2 < '\0') break;
    zz_01e488c_(PTR_DAT_80435a30[0x46],(int)*pcVar2,pcVar2[1]);
    pcVar2 = pcVar2 + 2;
  }
  PTR_DAT_80435a30[0x14a] = 1;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x168) = 0xffff;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x160) = 0;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x15e) = 0;
  *(undefined4 *)(PTR_DAT_80435a30 + 0x164) = 0xffffffff;
  iVar1 = zz_01cd060_(*(short **)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                      -0x7fc2b4a0,0,*(uint *)(PTR_DAT_80435a30 + 0x164));
  *(short *)(PTR_DAT_80435a30 + 0x162) = (short)iVar1;
  zz_01cd1b4_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
              (short *)&DAT_803d4b60,0,PTR_DAT_80435a30 + 0x14c);
  zz_0027aac_(0,0x1e,0);
  return;
}
