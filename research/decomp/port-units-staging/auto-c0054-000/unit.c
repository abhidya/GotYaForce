#include "gnt4_shim.h"

/* auto-generated prototypes (from chunk markers) */
void FUN_801bbac0(void);
void FUN_801bbaf8(void);
void FUN_801bbfdc(void);
void FUN_801bc018(void);
void FUN_801bc0d0(void);
void FUN_801bc324(void);
void FUN_801bc5b4(void);
void FUN_801bc608(void);

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 1-14 ==== */
// ==== 801bbac0  FUN_801bbac0 ====

void FUN_801bbac0(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 2;
    zz_0027c1c_();
  }
  return;
}

/* ==== VERBATIM+D5: research/decomp/ghidra-export/chunk_0054.c 18-214 ==== */
// ==== 801bbaf8  FUN_801bbaf8 ====

void FUN_801bbaf8(void)

{
  double dVar1;
  short sVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  short *psVar13;
  int iVar14;
  bool bVar15;
  
  iVar8 = *(short *)(PTR_DAT_80435a30 + 0x162) + -1;
  if ((-1 < iVar8) && (iVar8 < *(short *)(PTR_DAT_80435a30 + 0x160))) {
    *(short *)(PTR_DAT_80435a30 + 0x160) = (short)iVar8;
  }
  iVar8 = *(short *)(PTR_DAT_80435a30 + 0x162) + -0xd;
  if ((-1 < iVar8) && (iVar8 < *(short *)(PTR_DAT_80435a30 + 0x15e))) {
    *(short *)(PTR_DAT_80435a30 + 0x15e) = (short)iVar8;
  }
  uVar9 = *(uint *)(PTR_DAT_80435a30 + 0x1d8);
  iVar11 = (int)*(short *)(PTR_DAT_80435a30 + 0x15e);
  iVar12 = (int)*(short *)(PTR_DAT_80435a30 + 0x160);
  iVar8 = iVar11;
  if ((uVar9 & 0x8008) == 0) {
    if ((uVar9 & 0x4004) == 0) {
      if ((uVar9 & 0x1001) == 0) {
        iVar14 = iVar12;
        if ((uVar9 & 0x2002) != 0) {
          iVar10 = (int)*(short *)(PTR_DAT_80435a30 + 0x162);
          iVar8 = iVar10 + -1;
          if ((iVar12 < iVar8) || (iVar11 < iVar10 + -0xd)) {
            iVar14 = iVar12 + 0xd;
            if ((iVar8 < iVar12 + 0xd) && (iVar14 = iVar8, iVar8 < 0)) {
              iVar14 = 0;
            }
            iVar10 = iVar10 + -0xd;
            iVar8 = iVar11 + 0xd;
            if ((iVar10 < iVar11 + 0xd) && (iVar8 = iVar10, iVar10 < 0)) {
              iVar8 = 0;
            }
          }
          else {
            iVar14 = 0;
            iVar8 = 0;
          }
        }
      }
      else if ((iVar12 < 1) && (iVar11 < 1)) {
        iVar14 = *(short *)(PTR_DAT_80435a30 + 0x162) + -1;
        if (iVar14 < 0) {
          iVar14 = 0;
        }
        iVar8 = iVar14 + -0xc;
        if (iVar14 + -0xc < 0) {
          iVar8 = 0;
        }
      }
      else {
        iVar14 = iVar12 + -0xd;
        if (iVar14 < 0) {
          iVar14 = 0;
        }
        iVar8 = iVar11 + -0xd;
        if (iVar11 + -0xd < 0) {
          iVar8 = 0;
        }
      }
    }
    else {
      iVar14 = iVar12 + 1;
      if (*(short *)(PTR_DAT_80435a30 + 0x162) + -1 < iVar12 + 1) {
        iVar14 = 0;
      }
    }
  }
  else {
    iVar14 = iVar12 + -1;
    if ((iVar12 + -1 < 0) &&
       (iVar14 = *(short *)(PTR_DAT_80435a30 + 0x162) + -1,
       *(short *)(PTR_DAT_80435a30 + 0x162) + -1 < 0)) {
      iVar14 = 0;
    }
  }
  iVar10 = iVar14;
  if ((iVar8 <= iVar14) && (iVar10 = iVar8, iVar8 + 0xc < iVar14)) {
    iVar10 = iVar14 + -0xc;
  }
  if ((iVar10 != iVar11) || (iVar14 != iVar12)) {
    *(short *)(PTR_DAT_80435a30 + 0x15e) = (short)iVar10;
    *(short *)(PTR_DAT_80435a30 + 0x160) = (short)iVar14;
    zz_00f0468_(0,0x77,0);
  }
  *(undefined2 *)(PTR_DAT_80435a30 + 0x168) =
       *(undefined2 *)(&DAT_803d4b60 + *(short *)(PTR_DAT_80435a30 + 0x160) * 2);
  uVar9 = *(uint *)(PTR_DAT_80435a30 + 0x1dc);
  sVar2 = *(short *)(PTR_DAT_80435a30 + 0x168);
  psVar13 = (short *)(*(int *)(PTR_DAT_80435a30 + 0x24) + sVar2 * 0x20 + 0x870);
  if ((uVar9 & 0x200) == 0) {
    if ((uVar9 & 0x400) == 0) {
      if ((uVar9 & 0x800) == 0) {
        if ((uVar9 & 0x10) == 0) {
          if (((((uVar9 & 0x100) != 0) && (-1 < sVar2)) && (-1 < *psVar13)) &&
             ((*(uint *)(psVar13 + 8) & 1 << (int)(char)PTR_DAT_80435a30[0x40]) == 0)) {
            *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 4;
            *(undefined2 *)(PTR_DAT_80435a30 + 0x144) = *(undefined2 *)(PTR_DAT_80435a30 + 0x168);
            zz_01cc418_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)*(short *)(PTR_DAT_80435a30 + 0x144))
            ;
            zz_00f0468_(0,0x7a,0);
            fVar7 = FLOAT_8043bacc;
            fVar3 = FLOAT_8043bac8;
            fVar6 = FLOAT_8043babc;
            iVar14 = (int)*(short *)(PTR_DAT_80435a30 + 0x168);
            iVar12 = iVar14 / 5 + (iVar14 >> 0x1f);
            iVar11 = iVar14 / 0x28 + (iVar14 >> 0x1f);
            iVar8 = iVar14 + (iVar11 - (iVar11 >> 0x1f)) * -0x28;
            iVar8 = iVar8 / 5 + (iVar8 >> 0x1f);
            fVar4 = FLOAT_8043bacc *
                    (float)(__gnt4_bitcast_f64(CONCAT44(0x43300000,iVar8 - (iVar8 >> 0x1f) ^ 0x80000000)) -
                           DOUBLE_8043bae8) + FLOAT_8043bac8;
            fVar5 = FLOAT_8043bad0 - fVar4;
            dVar1 = __gnt4_bitcast_f64(CONCAT44(0x43300000,
                                     iVar14 + (iVar12 - (iVar12 >> 0x1f)) * -5 +
                                     (iVar11 - (iVar11 >> 0x1f)) * 5 ^ 0x80000000)) - DOUBLE_8043bae8
            ;
            bVar15 = fVar5 <= FLOAT_8043babc;
            *(float *)(PTR_DAT_80435a30 + 0x4c) = fVar5;
            fVar3 = fVar7 * (float)dVar1 + fVar3;
            if (bVar15) {
              if (*(float *)(PTR_DAT_80435a30 + 0x4c) < FLOAT_8043bad4) {
                *(float *)(PTR_DAT_80435a30 + 0x4c) = FLOAT_8043bad4;
              }
            }
            else {
              *(float *)(PTR_DAT_80435a30 + 0x4c) = fVar6;
            }
            fVar6 = FLOAT_8043bab8;
            fVar5 = FLOAT_8043bad0 - fVar3;
            bVar15 = fVar5 <= FLOAT_8043bab8;
            *(float *)(PTR_DAT_80435a30 + 0x48) = fVar5;
            if (bVar15) {
              if (*(float *)(PTR_DAT_80435a30 + 0x48) < FLOAT_8043bad8) {
                *(float *)(PTR_DAT_80435a30 + 0x48) = FLOAT_8043bad8;
              }
            }
            else {
              *(float *)(PTR_DAT_80435a30 + 0x48) = fVar6;
            }
            fVar5 = FLOAT_8043bae0;
            *(float *)(PTR_DAT_80435a30 + 0x30) =
                 FLOAT_8043badc + fVar3 + *(float *)(PTR_DAT_80435a30 + 0x48);
            *(float *)(PTR_DAT_80435a30 + 0x34) =
                 fVar5 + fVar4 + *(float *)(PTR_DAT_80435a30 + 0x4c);
            zz_0027aac_(0,0x1e,1);
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
    else if ((sVar2 < 0) || (*psVar13 < 0)) {
      zz_00f0468_(0,0x7d,0);
    }
    else {
      *(undefined2 *)(PTR_DAT_80435a30 + 0x20) = *(undefined2 *)(PTR_DAT_80435a30 + 0x12);
      *(undefined2 *)(PTR_DAT_80435a30 + 0x22) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14);
      *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 7;
      *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
      *(undefined2 *)(PTR_DAT_80435a30 + 0x16a) = *(undefined2 *)(PTR_DAT_80435a30 + 0x168);
      PTR_DAT_80435a30[0x16c] = 0;
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 4;
    zz_0027aac_(0,0x1e,1);
    zz_00f0468_(0,0x7b,0);
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 218-225 ==== */
// ==== 801bbfdc  FUN_801bbfdc ====

void FUN_801bbfdc(void)

{
  (*(code *)(&PTR_FUN_80383738)[*(short *)(PTR_DAT_80435a30 + 0x16)])();
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 229-244 ==== */
// ==== 801bc018  FUN_801bc018 ====

void FUN_801bc018(void)

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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 248-318 ==== */
// ==== 801bc0d0  FUN_801bc0d0 ====

void FUN_801bc0d0(void)

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
          if (PTR_DAT_80435a30[0x14c] == (&DAT_80383750)[(char)PTR_DAT_80435a30[0x15b] * 2]) {
            PTR_DAT_80435a30[0x14d] = PTR_DAT_80435a30[0x14d] ^ 1;
          }
          else {
            *(undefined2 *)(PTR_DAT_80435a30 + 0x152) = *(undefined2 *)(PTR_DAT_80435a30 + 0x150);
            *(undefined2 *)(PTR_DAT_80435a30 + 0x150) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14e);
            *(undefined2 *)(PTR_DAT_80435a30 + 0x14e) = *(undefined2 *)(PTR_DAT_80435a30 + 0x14c);
            *(undefined2 *)(PTR_DAT_80435a30 + 0x14c) =
                 *(undefined2 *)(&DAT_80383750 + (char)PTR_DAT_80435a30[0x15b] * 2);
          }
          zz_01cd1b4_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                      (short *)&DAT_803d4b60,0,PTR_DAT_80435a30 + 0x14c);
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 322-393 ==== */
// ==== 801bc324  FUN_801bc324 ====

void FUN_801bc324(void)

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
                            -0x7fc2b4a0,0,*(uint *)(PTR_DAT_80435a30 + 0x164));
        *(short *)(PTR_DAT_80435a30 + 0x162) = (short)iVar2;
        zz_01cd1b4_(*(int *)(PTR_DAT_80435a30 + 0x28),*(int *)(PTR_DAT_80435a30 + 0x24),
                    (short *)&DAT_803d4b60,0,PTR_DAT_80435a30 + 0x14c);
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

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 397-412 ==== */
// ==== 801bc5b4  FUN_801bc5b4 ====

void FUN_801bc5b4(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x16) = 0;
    PTR_DAT_80435a30[0x149] = 3;
  }
  return;
}

/* ==== VERBATIM: research/decomp/ghidra-export/chunk_0054.c 416-423 ==== */
// ==== 801bc608  FUN_801bc608 ====

void FUN_801bc608(void)

{
  (*(code *)(&PTR_FUN_8038375c)[*(short *)(PTR_DAT_80435a30 + 0x14)])();
  return;
}
