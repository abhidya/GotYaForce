#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801bc644(void);
void FUN_801bc738(void);
void FUN_801bc770(void);
void FUN_801bcb80(void);
void FUN_801bcbbc(void);
void FUN_801bcc74(void);
void FUN_801bcec8(void);
void FUN_801bd158(void);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 427-454 ==== */
// ==== 801bc644  FUN_801bc644 ====

void FUN_801bc644(void)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = &DAT_80383670;
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
                      -0x7fc2b4a0,1,*(uint *)(PTR_DAT_80435a30 + 0x164));
  *(short *)(PTR_DAT_80435a30 + 0x162) = (short)iVar1;
  zz_01cd1b4_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
              (short *)&DAT_803d4b60,1,PTR_DAT_80435a30 + 0x14c);
  zz_0027aac_(0,0x1e,0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 458-471 ==== */
// ==== 801bc738  FUN_801bc738 ====

void FUN_801bc738(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 2;
    zz_0027c1c_();
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 475-638 ==== */
// ==== 801bc770  FUN_801bc770 ====

void FUN_801bc770(void)

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
  iVar2 = *(short *)(PTR_DAT_80435a30 + 0x162) + -0xd;
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
          if ((iVar6 < iVar2) || (iVar5 < iVar4 + -0xd)) {
            iVar7 = iVar6 + 0xd;
            if ((iVar2 < iVar6 + 0xd) && (iVar7 = iVar2, iVar2 < 0)) {
              iVar7 = 0;
            }
            iVar4 = iVar4 + -0xd;
            iVar2 = iVar5 + 0xd;
            if ((iVar4 < iVar5 + 0xd) && (iVar2 = iVar4, iVar4 < 0)) {
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
        iVar2 = iVar7 + -0xc;
        if (iVar7 + -0xc < 0) {
          iVar2 = 0;
        }
      }
      else {
        iVar7 = iVar6 + -0xd;
        if (iVar7 < 0) {
          iVar7 = 0;
        }
        iVar2 = iVar5 + -0xd;
        if (iVar5 + -0xd < 0) {
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
  if ((iVar2 <= iVar7) && (iVar4 = iVar2, iVar2 + 0xc < iVar7)) {
    iVar4 = iVar7 + -0xc;
  }
  if ((iVar4 != iVar5) || (iVar7 != iVar6)) {
    *(short *)(PTR_DAT_80435a30 + 0x15e) = (short)iVar4;
    *(short *)(PTR_DAT_80435a30 + 0x160) = (short)iVar7;
    zz_00f0468_(0,0x77,0);
  }
  *(undefined2 *)(PTR_DAT_80435a30 + 0x168) =
       *(undefined2 *)(&DAT_803d4b60 + *(short *)(PTR_DAT_80435a30 + 0x160) * 2);
  uVar3 = *(uint *)(PTR_DAT_80435a30 + 0x1dc);
  sVar1 = *(short *)(PTR_DAT_80435a30 + 0x168);
  if ((uVar3 & 0x80) == 0) {
    if ((uVar3 & 0x40) == 0) {
      if ((uVar3 & 0x20) == 0) {
        if ((uVar3 & 0x400) == 0) {
          if ((uVar3 & 0x800) == 0) {
            if ((uVar3 & 0x10) == 0) {
              if ((((uVar3 & 0x100) != 0) && (-1 < sVar1)) &&
                 (-1 < *(short *)(*(int *)(PTR_DAT_80435a30 + 0x28) + sVar1 * 0x10))) {
                *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
                *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 4;
                *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
                zz_01cc3d4_(*(int *)(PTR_DAT_80435a30 + 0x28),
                            (int)*(short *)(PTR_DAT_80435a30 + 0x168));
                zz_00f0468_(0,0x7a,0);
              }
            }
            else {
              PTR_DAT_80435a30[0x14a] = PTR_DAT_80435a30[0x14a] ^ 1;
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
        else if ((sVar1 < 0) || (*(short *)(*(int *)(PTR_DAT_80435a30 + 0x28) + sVar1 * 0x10) < 0))
        {
          zz_00f0468_(0,0x7d,0);
        }
        else {
          *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 7;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x16a) = *(undefined2 *)(PTR_DAT_80435a30 + 0x168);
          PTR_DAT_80435a30[0x16c] = 1;
          zz_00f0468_(0,0x7a,0);
        }
      }
      else {
        *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 5;
        *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 2;
        zz_0027aac_(0,0x1e,1);
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
    *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
    *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 6;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
    zz_00f0468_(0,0x7a,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 642-649 ==== */
// ==== 801bcb80  FUN_801bcb80 ====

void FUN_801bcb80(void)

{
  (*(code *)(&PTR_FUN_80383774)[*(short *)(PTR_DAT_80435a30 + 0x16)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 653-668 ==== */
// ==== 801bcbbc  FUN_801bcbbc ====

void FUN_801bcbbc(void)

{
  *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 1;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
  PTR_DAT_80435a30[0x15a] = 0;
  PTR_DAT_80435a30[0x15b] = 0;
  PTR_DAT_80435a30[0x15c] = 7;
  PTR_DAT_80435a30[0x15d] = 7;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 2;
  *(undefined4 *)(PTR_DAT_80435a30 + 0x154) = 0;
  zz_01e488c_(PTR_DAT_80435a30[0x46],8,1);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 672-742 ==== */
// ==== 801bcc74  FUN_801bcc74 ====

void FUN_801bcc74(void)

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
        if (iVar1 < 6) {
          *(short *)(PTR_DAT_80435a30 + 0x16) = *(short *)(PTR_DAT_80435a30 + 0x16) + 3;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
          if (PTR_DAT_80435a30[0x14c] == (&DAT_8038378c)[(char)PTR_DAT_80435a30[0x15b] * 2]) {
            PTR_DAT_80435a30[0x14d] = PTR_DAT_80435a30[0x14d] ^ 1;
          }
          else {
            *(undefined2 *)(PTR_DAT_80435a30 + 0x152) = *(undefined2 *)(PTR_DAT_80435a30 + 0x150);
            *(undefined2 *)(PTR_DAT_80435a30 + 0x150) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14e);
            *(undefined2 *)(PTR_DAT_80435a30 + 0x14e) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14c);
            *(undefined2 *)(PTR_DAT_80435a30 + 0x14c) =
                 *(undefined2 *)(&DAT_8038378c + (char)PTR_DAT_80435a30[0x15b] * 2);
          }
          zz_01cd1b4_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                      (short *)&DAT_803d4b60,1,PTR_DAT_80435a30 + 0x14c);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
        }
        else if (iVar1 == 6) {
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 746-817 ==== */
// ==== 801bcec8  FUN_801bcec8 ====

void FUN_801bcec8(void)

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
                            -0x7fc2b4a0,1,*(uint *)(PTR_DAT_80435a30 + 0x164));
        *(short *)(PTR_DAT_80435a30 + 0x162) = (short)iVar2;
        zz_01cd1b4_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                    (short *)&DAT_803d4b60,1,PTR_DAT_80435a30 + 0x14c);
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
    PTR_DAT_80435a30[0x15b] = 5;
    PTR_DAT_80435a30[0x15c] = 7;
    PTR_DAT_80435a30[0x15d] = 7;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 2;
    zz_01e488c_(PTR_DAT_80435a30[0x46],8,1);
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 821-828 ==== */
// ==== 801bd158  FUN_801bd158 ====

void FUN_801bd158(void)

{
  (*(code *)(&PTR_FUN_80383798)[*(short *)(PTR_DAT_80435a30 + 0x16)])();
  return;
}
