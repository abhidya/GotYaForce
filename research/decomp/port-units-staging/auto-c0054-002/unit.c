#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801bd194(void);
void FUN_801bd248(void);
void FUN_801bd468(void);
void FUN_801bd684(void);
void FUN_801bd724(void);
void FUN_801bd760(void);
void FUN_801bd854(void);
void FUN_801bd88c(void);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 832-847 ==== */
// ==== 801bd194  FUN_801bd194 ====

void FUN_801bd194(void)

{
  *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 1;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
  PTR_DAT_80435a30[0x15a] = 0;
  PTR_DAT_80435a30[0x15b] = 0;
  PTR_DAT_80435a30[0x15c] = 2;
  PTR_DAT_80435a30[0x15d] = 2;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 8;
  zz_01bfb74_();
  zz_01e488c_(PTR_DAT_80435a30[0x46],8,3);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 851-917 ==== */
// ==== 801bd248  FUN_801bd248 ====

void FUN_801bd248(void)

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
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x200) == 0) {
    if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x100) != 0) {
      cVar1 = PTR_DAT_80435a30[0x15b];
      if ((*(uint *)(PTR_DAT_80435a30 + 0x154) & 1 << (int)cVar1) == 0) {
        if (cVar1 == '\0') {
          *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 3;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
          zz_01cbd48_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                      (int)*(short *)(PTR_DAT_80435a30 + 0x168));
          iVar2 = zz_01cd060_(*(short **)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24)
                              ,-0x7fc2b4a0,1,*(uint *)(PTR_DAT_80435a30 + 0x164));
          *(short *)(PTR_DAT_80435a30 + 0x162) = (short)iVar2;
          zz_01cd1b4_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                      (short *)&DAT_803d4b60,1,PTR_DAT_80435a30 + 0x14c);
        }
        else if (cVar1 == 1) {
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 921-979 ==== */
// ==== 801bd468  FUN_801bd468 ====

void FUN_801bd468(void)

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
          zz_01cbd00_(*(int *)(PTR_DAT_80435a30 + 0x28),(int)*(short *)(PTR_DAT_80435a30 + 0x168));
          iVar1 = zz_01cd060_(*(short **)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24)
                              ,-0x7fc2b4a0,1,*(uint *)(PTR_DAT_80435a30 + 0x164));
          *(short *)(PTR_DAT_80435a30 + 0x162) = (short)iVar1;
          zz_01cd1b4_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                      (short *)&DAT_803d4b60,1,PTR_DAT_80435a30 + 0x14c);
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
    PTR_DAT_80435a30[0x15b] = 1;
    PTR_DAT_80435a30[0x15c] = 2;
    PTR_DAT_80435a30[0x15d] = 2;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 8;
    zz_01bfb74_();
    zz_01e488c_(PTR_DAT_80435a30[0x46],8,3);
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 983-1010 ==== */
// ==== 801bd684  FUN_801bd684 ====

void FUN_801bd684(void)

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
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 1014-1021 ==== */
// ==== 801bd724  FUN_801bd724 ====

void FUN_801bd724(void)

{
  (*(code *)(&PTR_FUN_803837b0)[*(short *)(PTR_DAT_80435a30 + 0x14)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 1025-1052 ==== */
// ==== 801bd760  FUN_801bd760 ====

void FUN_801bd760(void)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = &DAT_80383694;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 1;
  while( true ) {
    if (*pcVar2 < '\0') break;
    zz_01e488c_(PTR_DAT_80435a30[0x46],(int)*pcVar2,pcVar2[1]);
    pcVar2 = pcVar2 + 2;
  }
  PTR_DAT_80435a30[0x14a] = 2;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x168) = 0xffff;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x160) = 0;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x15e) = 0;
  *(undefined4 *)(PTR_DAT_80435a30 + 0x164) = 0xffffffff;
  iVar1 = zz_01cd060_(*(short **)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                      -0x7fc2b4a0,2,*(uint *)(PTR_DAT_80435a30 + 0x164));
  *(short *)(PTR_DAT_80435a30 + 0x162) = (short)iVar1;
  zz_01cd1b4_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
              (short *)&DAT_803d4b60,2,PTR_DAT_80435a30 + 0x14c);
  zz_0027aac_(0,0x1e,0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 1056-1069 ==== */
// ==== 801bd854  FUN_801bd854 ====

void FUN_801bd854(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 2;
    zz_0027c1c_();
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 1073-1236 ==== */
// ==== 801bd88c  FUN_801bd88c ====

void FUN_801bd88c(void)

{
  short sVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar2 = *(short *)(PTR_DAT_80435a30 + 0x162) + -1;
  if ((-1 < iVar2) && (iVar2 < *(short *)(PTR_DAT_80435a30 + 0x160))) {
    *(short *)(PTR_DAT_80435a30 + 0x160) = (short)iVar2;
  }
  iVar2 = *(short *)(PTR_DAT_80435a30 + 0x162) + -10;
  if ((-1 < iVar2) && (iVar2 < *(short *)(PTR_DAT_80435a30 + 0x15e))) {
    *(short *)(PTR_DAT_80435a30 + 0x15e) = (short)iVar2;
  }
  uVar3 = *(uint *)(PTR_DAT_80435a30 + 0x1d8);
  iVar5 = (int)*(short *)(PTR_DAT_80435a30 + 0x15e);
  iVar6 = (int)*(short *)(PTR_DAT_80435a30 + 0x160);
  iVar2 = iVar5;
  if ((uVar3 & 0x8008) == 0) {
    if ((uVar3 & 0x4004) == 0) {
      if ((uVar3 & 0x1001) == 0) {
        iVar7 = iVar6;
        if ((uVar3 & 0x2002) != 0) {
          iVar4 = (int)*(short *)(PTR_DAT_80435a30 + 0x162);
          iVar2 = iVar4 + -1;
          if ((iVar6 < iVar2) || (iVar5 < iVar4 + -10)) {
            iVar7 = iVar6 + 10;
            if ((iVar2 < iVar6 + 10) && (iVar7 = iVar2, iVar2 < 0)) {
              iVar7 = 0;
            }
            iVar4 = iVar4 + -10;
            iVar2 = iVar5 + 10;
            if ((iVar4 < iVar5 + 10) && (iVar2 = iVar4, iVar4 < 0)) {
              iVar2 = 0;
            }
          }
          else {
            iVar7 = 0;
            iVar2 = 0;
          }
        }
      }
      else if ((iVar6 < 1) && (iVar5 < 1)) {
        iVar7 = *(short *)(PTR_DAT_80435a30 + 0x162) + -1;
        if (iVar7 < 0) {
          iVar7 = 0;
        }
        iVar2 = iVar7 + -9;
        if (iVar7 + -9 < 0) {
          iVar2 = 0;
        }
      }
      else {
        iVar7 = iVar6 + -10;
        if (iVar7 < 0) {
          iVar7 = 0;
        }
        iVar2 = iVar5 + -10;
        if (iVar5 + -10 < 0) {
          iVar2 = 0;
        }
      }
    }
    else {
      iVar7 = iVar6 + 1;
      if (*(short *)(PTR_DAT_80435a30 + 0x162) + -1 < iVar6 + 1) {
        iVar7 = 0;
      }
    }
  }
  else {
    iVar7 = iVar6 + -1;
    if ((iVar6 + -1 < 0) &&
       (iVar7 = *(short *)(PTR_DAT_80435a30 + 0x162) + -1,
       *(short *)(PTR_DAT_80435a30 + 0x162) + -1 < 0)) {
      iVar7 = 0;
    }
  }
  iVar4 = iVar7;
  if ((iVar2 <= iVar7) && (iVar4 = iVar2, iVar2 + 9 < iVar7)) {
    iVar4 = iVar7 + -9;
  }
  if ((iVar4 != iVar5) || (iVar7 != iVar6)) {
    *(short *)(PTR_DAT_80435a30 + 0x15e) = (short)iVar4;
    *(short *)(PTR_DAT_80435a30 + 0x160) = (short)iVar7;
    zz_00f0468_(0,0x77,0);
  }
  *(undefined2 *)(PTR_DAT_80435a30 + 0x168) =
       *(undefined2 *)(&DAT_803d4b60 + *(short *)(PTR_DAT_80435a30 + 0x160) * 2);
  sVar1 = *(short *)(PTR_DAT_80435a30 + 0x168);
  uVar3 = *(uint *)(PTR_DAT_80435a30 + 0x1dc);
  iVar2 = sVar1 * 0xc + 32000;
  if ((uVar3 & 0x80) == 0) {
    if ((uVar3 & 0x40) == 0) {
      if ((uVar3 & 0x20) == 0) {
        if ((uVar3 & 0x400) == 0) {
          if ((uVar3 & 0x800) == 0) {
            if ((uVar3 & 0x10) == 0) {
              if ((((uVar3 & 0x100) != 0) && (-1 < sVar1)) &&
                 (-1 < *(int *)(*(int *)(PTR_DAT_80435a30 + 0x28) + iVar2))) {
                *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
                *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 4;
                *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
                zz_01cc3f4_(*(int *)(PTR_DAT_80435a30 + 0x28),
                            (int)*(short *)(PTR_DAT_80435a30 + 0x168));
                zz_00f0468_(0,0x7a,0);
              }
            }
            else {
              PTR_DAT_80435a30[0x14a] = PTR_DAT_80435a30[0x14a] ^ 2;
              zz_00f0468_(0,0x7a,0);
            }
          }
          else {
            *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
            *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 3;
            *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
            zz_00f0468_(0,0x7a,0);
          }
        }
        else if ((sVar1 < 0) || (*(int *)(*(int *)(PTR_DAT_80435a30 + 0x28) + iVar2) < 0)) {
          zz_00f0468_(0,0x7d,0);
        }
        else {
          *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 7;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x16a) = *(undefined2 *)(PTR_DAT_80435a30 + 0x168);
          PTR_DAT_80435a30[0x16c] = 2;
          zz_00f0468_(0,0x7a,0);
        }
      }
      else {
        *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 5;
        *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
        zz_0027aac_(0,0x1e,1);
        zz_00f0468_(0,0x7a,0);
      }
    }
    else {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 5;
      *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 1;
      zz_0027aac_(0,0x1e,1);
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
    *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 6;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
    zz_00f0468_(0,0x7a,0);
  }
  return;
}
