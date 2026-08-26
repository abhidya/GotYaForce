#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
undefined4 FUN_801ba960(void);
void FUN_801ba9ec(void);
void FUN_801babbc(void);
void FUN_801bac50(void);
void FUN_801bac88(void);
void FUN_801bacd8(void);
void FUN_801baf6c(void);
void FUN_801bb1e0(void);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4047-4064 ==== */
// ==== 801ba960  FUN_801ba960 ====

undefined4 FUN_801ba960(void)

{
  if (PTR_DAT_80435a30[0x148] == '\0') {
    zz_01bef70_();
  }
  if ((char)PTR_DAT_80435a30[0x148] < '\x02') {
    *(short *)(PTR_DAT_80435a30 + 0x18) = *(short *)(PTR_DAT_80435a30 + 0x18) + 1;
    (*(code *)(&PTR_FUN_803836d4)[*(short *)(PTR_DAT_80435a30 + 0x12)])();
  }
  if (PTR_DAT_80435a30[0x16d] == '\0') {
    zz_01beda4_();
    zz_01beec0_();
  }
  return 0;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4068-4134 ==== */
// ==== 801ba9ec  FUN_801ba9ec ====

void FUN_801ba9ec(void)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  char *pcVar6;
  int iVar7;
  
  cVar1 = PTR_DAT_80435a30[0x149];
  if (cVar1 == '\0') {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 2;
  }
  else if (cVar1 == '\x01') {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 3;
  }
  else if (cVar1 == '\x02') {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 4;
  }
  else {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 1;
  }
  *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
  pcVar6 = &DAT_80383610;
  while( true ) {
    if (*pcVar6 < '\0') break;
    zz_01c13c8_(PTR_DAT_80435a30[0x46],(int)*pcVar6,pcVar6[1]);
    pcVar6 = pcVar6 + 2;
  }
  iVar7 = 0;
  do {
    zz_01c13c8_(PTR_DAT_80435a30[0x46],0xb,(char)iVar7);
    fVar2 = FLOAT_8043bab8;
    iVar7 = iVar7 + 1;
  } while (iVar7 < 0x1e);
  *(undefined2 *)(PTR_DAT_80435a30 + 0x158) = 0;
  fVar4 = FLOAT_8043bac0;
  fVar3 = FLOAT_8043babc;
  PTR_DAT_80435a30[0x53] = 0;
  fVar5 = FLOAT_8043bac4;
  PTR_DAT_80435a30[0x41] = 0;
  PTR_DAT_80435a30[0x42] = 0xff;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x50) = 0;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
  PTR_DAT_80435a30[0x52] = 0;
  PTR_DAT_80435a30[0x43] = 0;
  PTR_DAT_80435a30[0x44] = 0;
  *(float *)(PTR_DAT_80435a30 + 0x48) = fVar2;
  *(float *)(PTR_DAT_80435a30 + 0x4c) = fVar3;
  *(float *)(PTR_DAT_80435a30 + 0x30) = fVar4;
  *(float *)(PTR_DAT_80435a30 + 0x34) = fVar5;
  iVar7 = zz_01cce38_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40],
                      *(int *)(PTR_DAT_80433934 + 0x120),0);
  PTR_DAT_80435a30[0x45] = (char)iVar7;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x14c) = 0x200;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x14e) = 0x100;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x150) = 0x600;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x152) = 0x200;
  zz_01cc43c_(*(int *)(PTR_DAT_80435a30 + 0x2c),*(short **)(PTR_DAT_80435a30 + 0x28),
              *(int *)(PTR_DAT_80435a30 + 0x24));
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4138-4156 ==== */
// ==== 801babbc  FUN_801babbc ====

void FUN_801babbc(void)

{
  int iVar1;
  
  (*(code *)(&PTR_FUN_803836f4)[*(short *)(PTR_DAT_80435a30 + 0x14)])();
  iVar1 = zz_01cce38_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40],
                      *(int *)(PTR_DAT_80433934 + 0x120),0);
  PTR_DAT_80435a30[0x45] = (char)iVar1;
  if ('\0' < (char)PTR_DAT_80435a30[0x53]) {
    PTR_DAT_80435a30[0x53] = PTR_DAT_80435a30[0x53] + -1;
  }
  if ('\0' < (char)PTR_DAT_80435a30[0x41]) {
    PTR_DAT_80435a30[0x41] = PTR_DAT_80435a30[0x41] + -1;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4160-4168 ==== */
// ==== 801bac50  FUN_801bac50 ====

void FUN_801bac50(void)

{
  *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 1;
  zz_0027aac_(0,0x1e,0);
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4172-4190 ==== */
// ==== 801bac88  FUN_801bac88 ====

void FUN_801bac88(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    if (*(short *)(PTR_DAT_80435a30 + 0x144) < 0) {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 2;
    }
    else {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 3;
    }
    zz_0027c1c_();
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4194-4279 ==== */
// ==== 801bacd8  FUN_801bacd8 ====

void FUN_801bacd8(void)

{
  uint uVar1;
  
  zz_01bf144_();
  uVar1 = *(uint *)(PTR_DAT_80435a30 + 0x1dc);
  if ((uVar1 & 0x80) == 0) {
    if ((uVar1 & 0x40) == 0) {
      if ((uVar1 & 0x20) == 0) {
        if ((uVar1 & 0x400) == 0) {
          if ((uVar1 & 0x800) == 0) {
            if ((uVar1 & 0x100) != 0) {
              if ((char)PTR_DAT_80435a30[0x42] < '\0') {
                if (-1 < *(short *)(PTR_DAT_80435a30 + 0x50)) {
                  if ((*(uint *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                                *(short *)(PTR_DAT_80435a30 + 0x146) * 0x20 + 0x880) &
                      1 << (int)(char)PTR_DAT_80435a30[0x40]) == 0) {
                    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 3;
                    *(undefined2 *)(PTR_DAT_80435a30 + 0x144) =
                         *(undefined2 *)(PTR_DAT_80435a30 + 0x146);
                    zz_00f0468_(0,0x7a,0);
                  }
                }
              }
              else if (-1 < *(short *)(PTR_DAT_80435a30 + 0x146)) {
                *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 3;
                *(undefined2 *)(PTR_DAT_80435a30 + 0x144) =
                     *(undefined2 *)(PTR_DAT_80435a30 + 0x146);
                *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
                zz_01ccb94_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40],
                            (int)(char)PTR_DAT_80435a30[0x42]);
                zz_00f0468_(0,0x7a,0);
              }
              if (-1 < *(short *)(PTR_DAT_80435a30 + 0x144)) {
                zz_01cc418_(*(int *)(PTR_DAT_80435a30 + 0x24),
                            (int)*(short *)(PTR_DAT_80435a30 + 0x144));
              }
            }
          }
          else {
            *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
            *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 4;
            *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
            zz_00f0468_(0,0x7a,0);
          }
        }
        else if (*(short *)(PTR_DAT_80435a30 + 0x146) < 0) {
          zz_00f0468_(0,0x7d,0);
        }
        else {
          *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
          *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 7;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x16a) = *(undefined2 *)(PTR_DAT_80435a30 + 0x146);
          PTR_DAT_80435a30[0x16c] = 0;
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
      *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 5;
      *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 2;
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4283-4364 ==== */
// ==== 801baf6c  FUN_801baf6c ====

void FUN_801baf6c(void)

{
  short sVar1;
  uint uVar2;
  short *psVar3;
  
  zz_01bf144_();
  uVar2 = *(uint *)(PTR_DAT_80435a30 + 0x1dc);
  if ((uVar2 & 0x200) != 0) {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 2;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
    zz_00f0468_(0,0x7b,0);
    return;
  }
  if ((uVar2 & 0x400) != 0) {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
    *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 7;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16a) = *(undefined2 *)(PTR_DAT_80435a30 + 0x144);
    PTR_DAT_80435a30[0x16c] = 0;
    zz_00f0468_(0,0x7a,0);
    return;
  }
  if ((uVar2 & 0x800) != 0) {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 4;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
    zz_00f0468_(0,0x7a,0);
    return;
  }
  if ((uVar2 & 0x100) != 0) {
    if ((char)PTR_DAT_80435a30[0x42] < '\0') {
      sVar1 = *(short *)(PTR_DAT_80435a30 + 0x50);
      if (-1 < sVar1) {
        if ((int)sVar1 == (int)*(short *)(PTR_DAT_80435a30 + 0x144)) {
          *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 2;
          *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
        }
        else {
          zz_01cc0a4_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)sVar1,
                      (int)*(short *)(PTR_DAT_80435a30 + 0x144));
          psVar3 = (short *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                            *(short *)(PTR_DAT_80435a30 + 0x144) * 0x20 + 0x870);
          if ((*psVar3 < 0) ||
             ((*(uint *)(psVar3 + 8) & 1 << (int)(char)PTR_DAT_80435a30[0x40]) != 0)) {
            *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 2;
            *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
          }
        }
        zz_00f0468_(0,0x7a,0);
      }
    }
    else if ((*(uint *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                        *(short *)(PTR_DAT_80435a30 + 0x144) * 0x20 + 0x880) &
             1 << (int)(char)PTR_DAT_80435a30[0x40]) == 0) {
      if (*(short *)(PTR_DAT_80435a30 + 0x146) < 0) {
        *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 2;
        zz_01ccaf8_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40],
                    (int)(char)PTR_DAT_80435a30[0x42],(int)*(short *)(PTR_DAT_80435a30 + 0x144));
        *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = 0xffff;
        *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
        zz_00f0468_(0,0x7a,0);
      }
      else {
        zz_01ccc1c_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)(char)PTR_DAT_80435a30[0x40],
                    (int)(char)PTR_DAT_80435a30[0x42],(int)*(short *)(PTR_DAT_80435a30 + 0x144));
        *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = *(undefined2 *)(PTR_DAT_80435a30 + 0x146);
        *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
        zz_00f0468_(0,0x7a,0);
      }
    }
    if (-1 < *(short *)(PTR_DAT_80435a30 + 0x144)) {
      zz_01cc418_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)*(short *)(PTR_DAT_80435a30 + 0x144));
    }
    return;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0053.c 4368-4375 ==== */
// ==== 801bb1e0  FUN_801bb1e0 ====

void FUN_801bb1e0(void)

{
  (*(code *)(&PTR_FUN_8038370c)[*(short *)(PTR_DAT_80435a30 + 0x16)])();
  return;
}
