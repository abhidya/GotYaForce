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
                    (float)((double)CONCAT44(0x43300000,iVar8 - (iVar8 >> 0x1f) ^ 0x80000000) -
                           DOUBLE_8043bae8) + FLOAT_8043bac8;
            fVar5 = FLOAT_8043bad0 - fVar4;
            dVar1 = (double)CONCAT44(0x43300000,
                                     iVar14 + (iVar12 - (iVar12 >> 0x1f)) * -5 +
                                     (iVar11 - (iVar11 >> 0x1f)) * 5 ^ 0x80000000) - DOUBLE_8043bae8
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



// ==== 801bbfdc  FUN_801bbfdc ====

void FUN_801bbfdc(void)

{
  (*(code *)(&PTR_FUN_80383738)[*(short *)(PTR_DAT_80435a30 + 0x16)])();
  return;
}



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



// ==== 801bc608  FUN_801bc608 ====

void FUN_801bc608(void)

{
  (*(code *)(&PTR_FUN_8038375c)[*(short *)(PTR_DAT_80435a30 + 0x14)])();
  return;
}



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



// ==== 801bcb80  FUN_801bcb80 ====

void FUN_801bcb80(void)

{
  (*(code *)(&PTR_FUN_80383774)[*(short *)(PTR_DAT_80435a30 + 0x16)])();
  return;
}



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



// ==== 801bd158  FUN_801bd158 ====

void FUN_801bd158(void)

{
  (*(code *)(&PTR_FUN_80383798)[*(short *)(PTR_DAT_80435a30 + 0x16)])();
  return;
}



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



// ==== 801bd724  FUN_801bd724 ====

void FUN_801bd724(void)

{
  (*(code *)(&PTR_FUN_803837b0)[*(short *)(PTR_DAT_80435a30 + 0x14)])();
  return;
}



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



// ==== 801bdca0  FUN_801bdca0 ====

void FUN_801bdca0(void)

{
  (*(code *)(&PTR_FUN_803837c8)[*(short *)(PTR_DAT_80435a30 + 0x16)])();
  return;
}



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



// ==== 801be26c  FUN_801be26c ====

void FUN_801be26c(void)

{
  (*(code *)(&PTR_FUN_803837e0)[*(short *)(PTR_DAT_80435a30 + 0x16)])();
  return;
}



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



// ==== 801be708  FUN_801be708 ====

void FUN_801be708(void)

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



// ==== 801be7a8  FUN_801be7a8 ====

void FUN_801be7a8(void)

{
  (*(code *)(&PTR_FUN_803837f8)[*(short *)(PTR_DAT_80435a30 + 0x14)])();
  return;
}



// ==== 801be7e4  FUN_801be7e4 ====

void FUN_801be7e4(void)

{
  *(short *)(PTR_DAT_80435a30 + 0x14) = *(short *)(PTR_DAT_80435a30 + 0x14) + 1;
  zz_01c66a0_(1,PTR_DAT_80435a30[0x46],
              (char *)(*(int *)(PTR_DAT_80435a30 + 0x24) + (char)PTR_DAT_80435a30[0x40] * 0x6c));
  return;
}



// ==== 801be838  FUN_801be838 ====

void FUN_801be838(void)

{
  int iVar1;
  
  iVar1 = zz_01c677c_();
  if (iVar1 != 0) {
    *(short *)(PTR_DAT_80435a30 + 0x14) = *(short *)(PTR_DAT_80435a30 + 0x14) + 1;
  }
  return;
}



// ==== 801be88c  FUN_801be88c ====

void FUN_801be88c(void)

{
  (*(code *)(&PTR_FUN_80383804)[*(short *)(PTR_DAT_80435a30 + 0x14)])();
  return;
}



// ==== 801be8c8  FUN_801be8c8 ====

void FUN_801be8c8(void)

{
  undefined1 *puVar1;
  uint uVar2;
  
  uVar2 = zz_01bfbf4_();
  if (uVar2 == 0) {
    *(short *)(PTR_DAT_80435a30 + 0x14) = *(short *)(PTR_DAT_80435a30 + 0x14) + 2;
  }
  else {
    *(short *)(PTR_DAT_80435a30 + 0x14) = *(short *)(PTR_DAT_80435a30 + 0x14) + 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x1e) = 10;
    puVar1 = PTR_DAT_80435a30 + 0x46;
    PTR_DAT_80435a30[0x14b] = (char)uVar2;
    zz_01e488c_(*puVar1,0xb,(char)uVar2);
  }
  return;
}



// ==== 801be99c  FUN_801be99c ====

void FUN_801be99c(void)

{
  *(short *)(PTR_DAT_80435a30 + 0x14) = *(short *)(PTR_DAT_80435a30 + 0x14) + 1;
  zz_0027aac_(0,0x3c,1);
  zz_00e9b60_((double)FLOAT_8043baf0,2,0x3c,2);
  return;
}



// ==== 801be9ec  FUN_801be9ec ====

void FUN_801be9ec(void)

{
  int iVar1;
  int iVar2;
  size_t sVar3;
  int iVar4;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    iVar4 = 0;
    iVar1 = 0;
    *(short *)(PTR_DAT_80435a30 + 0x10) = *(short *)(PTR_DAT_80435a30 + 0x10) + 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = 0;
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = 0;
    do {
      iVar2 = zz_01ccd2c_(*(int *)(PTR_DAT_80435a30 + 0x24),iVar1);
      if (iVar2 == 0) {
        zz_01ccac8_(*(int *)(PTR_DAT_80435a30 + 0x24),iVar1);
      }
      else {
        sVar3 = strlen((char *)(*(int *)(PTR_DAT_80435a30 + 0x24) + iVar4));
        if (sVar3 == 0) {
          sprintf((char *)(*(int *)(PTR_DAT_80435a30 + 0x24) + iVar4),&DAT_802b3678);
          *(char *)(*(int *)(PTR_DAT_80435a30 + 0x24) + iVar4 + 0x15) =
               *(char *)(*(int *)(PTR_DAT_80435a30 + 0x24) + iVar4 + 0x15) + (char)iVar1;
        }
      }
      zz_01ccd94_(*(int *)(PTR_DAT_80435a30 + 0x24),iVar1);
      zz_01ccccc_(*(int *)(PTR_DAT_80435a30 + 0x24),iVar1);
      iVar1 = iVar1 + 1;
      iVar4 = iVar4 + 0x6c;
    } while (iVar1 < 0x14);
    zz_01cc768_(*(int *)(PTR_DAT_80435a30 + 0x24));
  }
  return;
}



// ==== 801beb00  FUN_801beb00 ====

void FUN_801beb00(void)

{
  (*(code *)(&PTR_FUN_80383814)[*(short *)(PTR_DAT_80435a30 + 0x14)])();
  return;
}



// ==== 801beb3c  FUN_801beb3c ====

void FUN_801beb3c(void)

{
  *(short *)(PTR_DAT_80435a30 + 0x14) = *(short *)(PTR_DAT_80435a30 + 0x14) + 1;
  zz_0027aac_(0,0x1e,1);
  return;
}



// ==== 801beb78  FUN_801beb78 ====

void FUN_801beb78(void)

{
  char cVar1;
  int iVar2;
  
  iVar2 = zz_0027adc_();
  if (iVar2 == 0) {
    *(short *)(PTR_DAT_80435a30 + 0x14) = *(short *)(PTR_DAT_80435a30 + 0x14) + 1;
    PTR_DAT_80435a30[0x16d] = 1;
    cVar1 = PTR_DAT_80435a30[0x16c];
    if (cVar1 == '\0') {
      zz_01cc418_(*(int *)(PTR_DAT_80435a30 + 0x24),(int)*(short *)(PTR_DAT_80435a30 + 0x16a));
      zz_01dc8e8_(1,PTR_DAT_80435a30[0x46],0,
                  (undefined2 *)
                  (*(int *)(PTR_DAT_80435a30 + 0x24) +
                  *(short *)(PTR_DAT_80435a30 + 0x16a) * 0x20 + 0x870));
    }
    else if (cVar1 == '\x01') {
      zz_01cc3d4_(*(int *)(PTR_DAT_80435a30 + 0x28),(int)*(short *)(PTR_DAT_80435a30 + 0x16a));
      zz_01dc8e8_(1,PTR_DAT_80435a30[0x46],0,
                  (undefined2 *)
                  (*(int *)(PTR_DAT_80435a30 + 0x28) + *(short *)(PTR_DAT_80435a30 + 0x16a) * 0x10))
      ;
    }
    else if (cVar1 == '\x02') {
      zz_01cc3f4_(*(int *)(PTR_DAT_80435a30 + 0x28),(int)*(short *)(PTR_DAT_80435a30 + 0x16a));
      zz_01dc8e8_(1,PTR_DAT_80435a30[0x46],1,
                  (undefined2 *)
                  (*(int *)(PTR_DAT_80435a30 + 0x28) +
                  *(short *)(PTR_DAT_80435a30 + 0x16a) * 0xc + 32000));
    }
    zz_0027c1c_();
  }
  return;
}



// ==== 801bec90  FUN_801bec90 ====

void FUN_801bec90(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  byte bVar1;
  
  bVar1 = zz_01dc970_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  if (bVar1 != 0) {
    *(short *)(PTR_DAT_80435a30 + 0x14) = *(short *)(PTR_DAT_80435a30 + 0x14) + 1;
    PTR_DAT_80435a30[0x16d] = 0;
    zz_00437b0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3);
    zz_0027aac_(0,0x1e,0);
  }
  return;
}



// ==== 801becec  FUN_801becec ====

void FUN_801becec(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    *(undefined2 *)(PTR_DAT_80435a30 + 0x12) = *(undefined2 *)(PTR_DAT_80435a30 + 0x20);
    *(undefined2 *)(PTR_DAT_80435a30 + 0x14) = *(undefined2 *)(PTR_DAT_80435a30 + 0x22);
  }
  return;
}



// ==== 801bed2c  FUN_801bed2c ====

undefined4
FUN_801bed2c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
            undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined8 extraout_f1;
  undefined8 uVar1;
  
  uVar1 = zz_0027c1c_();
  zz_01ba78c_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar1 >> 0x20),(int)uVar1,param_11,param_12,param_13,param_14,
              param_15,param_16);
  zz_007fd5c_();
  return 1;
}



// ==== 801bed58  zz_01bed58_ ====

bool zz_01bed58_(void)

{
  bool bVar1;
  
  gnt4_memset(&DAT_803c73b0,0,0x3e4);
  gnt4_memset(&DAT_803c7794,0,0x3e4);
  bVar1 = zz_01beda4_();
  return bVar1;
}



// ==== 801beda4  zz_01beda4_ ====

bool zz_01beda4_(void)

{
  int iVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  undefined1 *puVar5;
  int *piVar6;
  float afStack_28 [7];
  
  piVar6 = &DAT_80383824;
  puVar5 = &DAT_803c73b0;
  iVar4 = 0;
  do {
    PTR_DAT_80433930[*piVar6 + 0xc] = (char)iVar4;
    iVar3 = piVar6[2];
    *(int *)(puVar5 + 0x2e8) = piVar6[1];
    iVar1 = piVar6[3];
    *(int *)(puVar5 + 0x2ec) = iVar3;
    iVar3 = piVar6[4];
    *(int *)(puVar5 + 0x2f0) = iVar1;
    iVar1 = piVar6[5];
    *(int *)(puVar5 + 0x300) = iVar3;
    iVar3 = piVar6[6];
    *(int *)(puVar5 + 0x304) = iVar1;
    iVar1 = piVar6[7];
    *(int *)(puVar5 + 0x308) = iVar3;
    iVar3 = piVar6[8];
    *(int *)(puVar5 + 0x330) = iVar1;
    iVar1 = piVar6[9];
    *(int *)(puVar5 + 0x334) = iVar3;
    *(int *)(puVar5 + 0x338) = iVar1;
    gnt4_C_MTXLookAt_bl((float *)(puVar5 + 0x394),(float *)(puVar5 + 0x2e8),
                        (float *)(puVar5 + 0x330),(float *)(puVar5 + 0x300));
    *(undefined1 **)(PTR_DAT_80433930 + *piVar6 * 4 + 0x14) = puVar5 + 0x394;
    gnt4_PSVECSubtract_bl((float *)(puVar5 + 0x2e8),(float *)(puVar5 + 0x300),afStack_28);
    bVar2 = zz_0045ef4_((float *)(puVar5 + 0x364),5,afStack_28,puVar5 + 0x330);
    iVar4 = iVar4 + 1;
    piVar6 = piVar6 + 10;
    *(undefined4 *)(puVar5 + 0x370) = *(undefined4 *)(puVar5 + 0x2e8);
    *(undefined4 *)(puVar5 + 0x380) = *(undefined4 *)(puVar5 + 0x2ec);
    *(undefined4 *)(puVar5 + 0x390) = *(undefined4 *)(puVar5 + 0x2f0);
    puVar5 = puVar5 + 0x3e4;
  } while (iVar4 < 2);
  return bVar2;
}



// ==== 801beec0  zz_01beec0_ ====

void zz_01beec0_(void)

{
  zz_01beee4_();
  zz_01bef28_();
  return;
}



// ==== 801beee4  zz_01beee4_ ====

void zz_01beee4_(void)

{
  if ((char)PTR_DAT_80435a30[0x148] < '\x02') {
    zz_0089898_(0x10);
  }
  zz_0089898_(0x39);
  zz_0089554_();
  return;
}



// ==== 801bef28  zz_01bef28_ ====

void zz_01bef28_(void)

{
  zz_008a16c_();
  zz_0089c00_(0x10);
  zz_0089c00_(0x39);
  zz_008c0dc_(FUN_80089eb4);
  zz_008c104_(FUN_80089f28);
  return;
}



// ==== 801bef70  zz_01bef70_ ====

int zz_01bef70_(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  *(undefined4 *)(PTR_DAT_80435a30 + 0x1d4) = *(undefined4 *)(PTR_DAT_80435a30 + 0x1d0);
  if ((&DAT_803c7211)[(char)PTR_DAT_80435a30[0x46] * 0x20] == '\0') {
    *(undefined4 *)(PTR_DAT_80435a30 + 0x1d0) = 0;
  }
  else {
    *(uint *)(PTR_DAT_80435a30 + 0x1d0) = (&DAT_803c71fc)[(char)PTR_DAT_80435a30[0x46] * 8] & 0xf7f;
    *(uint *)(PTR_DAT_80435a30 + 0x1d0) =
         *(uint *)(PTR_DAT_80435a30 + 0x1d0) |
         (uint)(&DAT_803c71fc)[(char)PTR_DAT_80435a30[0x46] * 8] >> 4 & 0xf000;
    *(uint *)(PTR_DAT_80435a30 + 0x1d0) =
         *(uint *)(PTR_DAT_80435a30 + 0x1d0) |
         (uint)(&DAT_803c71fc)[(char)PTR_DAT_80435a30[0x46] * 8] >> 4 & 0xf0000;
    *(uint *)(PTR_DAT_80435a30 + 0x1d0) =
         *(uint *)(PTR_DAT_80435a30 + 0x1d0) |
         (uint)(&DAT_803c71fc)[(char)PTR_DAT_80435a30[0x46] * 8] >> 5 & 0x80;
  }
  iVar2 = 0;
  *(uint *)(PTR_DAT_80435a30 + 0x1dc) =
       *(uint *)(PTR_DAT_80435a30 + 0x1d0) & ~*(uint *)(PTR_DAT_80435a30 + 0x1d4);
  *(undefined4 *)(PTR_DAT_80435a30 + 0x1d8) = *(undefined4 *)(PTR_DAT_80435a30 + 0x1dc);
  iVar3 = 10;
  do {
    if ((*(uint *)(PTR_DAT_80435a30 + 0x1d0) & 1 << iVar2) == 0) {
      PTR_DAT_80435a30[iVar2 + 0x1e0] = 0;
    }
    else {
      PTR_DAT_80435a30[iVar2 + 0x1e0] = PTR_DAT_80435a30[iVar2 + 0x1e0] + '\x01';
    }
    if (0x1f < (byte)PTR_DAT_80435a30[iVar2 + 0x1e0]) {
      *(uint *)(PTR_DAT_80435a30 + 0x1d8) = *(uint *)(PTR_DAT_80435a30 + 0x1d8) | 1 << iVar2;
      PTR_DAT_80435a30[iVar2 + 0x1e0] = 0x1b;
    }
    uVar1 = 1 << iVar2 + 1;
    if ((*(uint *)(PTR_DAT_80435a30 + 0x1d0) & uVar1) == 0) {
      PTR_DAT_80435a30[iVar2 + 0x1e1] = 0;
    }
    else {
      PTR_DAT_80435a30[iVar2 + 0x1e1] = PTR_DAT_80435a30[iVar2 + 0x1e1] + '\x01';
    }
    if (0x1f < (byte)PTR_DAT_80435a30[iVar2 + 0x1e1]) {
      *(uint *)(PTR_DAT_80435a30 + 0x1d8) = *(uint *)(PTR_DAT_80435a30 + 0x1d8) | uVar1;
      PTR_DAT_80435a30[iVar2 + 0x1e1] = 0x1b;
    }
    iVar2 = iVar2 + 2;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return (int)(char)(&DAT_803c7211)[(char)PTR_DAT_80435a30[0x46] * 0x20];
}



// ==== 801bf144  zz_01bf144_ ====

void zz_01bf144_(void)

{
  char cVar1;
  short sVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  undefined1 uVar7;
  int iVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  double dVar13;
  double dVar14;
  
  if (PTR_DAT_80435a30[0x43] == '\0') {
    if ((PTR_DAT_80435a30[0x41] == '\0') && (*(short *)(PTR_DAT_80435a30 + 0x144) < 0)) {
      cVar1 = PTR_DAT_80435a30[0x40];
      iVar12 = (int)cVar1;
      if ((*(uint *)(PTR_DAT_80435a30 + 0x1d0) & 5) == 0) {
        if (((*(uint *)(PTR_DAT_80435a30 + 0x1d0) & 10) != 0) &&
           (iVar12 = iVar12 + 1, 0x13 < iVar12)) {
          iVar12 = 0;
        }
      }
      else {
        iVar12 = iVar12 + -1;
        if (iVar12 < 0) {
          iVar12 = 0x13;
        }
      }
      if (iVar12 != cVar1) {
        iVar6 = iVar12 - cVar1;
        if (iVar6 < 0) {
          iVar6 = iVar6 + 0x14;
        }
        uVar7 = 1;
        if (iVar6 < 0xb) {
          uVar7 = 0xff;
        }
        zz_01c13c8_(PTR_DAT_80435a30[0x46],2,uVar7);
        PTR_DAT_80435a30[0x52] = 0;
        PTR_DAT_80435a30[0x40] = (char)iVar12;
        PTR_DAT_80435a30[0x41] = 0x10;
        zz_00f0468_(0,0x171,0);
      }
    }
    if (PTR_DAT_80435a30[0x53] == '\0') {
      iVar12 = (int)(char)PTR_DAT_80435a30[0x52];
      if ((*(uint *)(PTR_DAT_80435a30 + 0x1d0) & 0x90000) == 0) {
        if (((*(uint *)(PTR_DAT_80435a30 + 0x1d0) & 0x60000) != 0) &&
           (iVar12 = iVar12 + 1, 0x1d < iVar12)) {
          iVar12 = 0;
        }
      }
      else {
        iVar12 = iVar12 + -1;
        if (iVar12 < 0) {
          iVar12 = 0x1d;
        }
      }
      if (iVar12 != (char)PTR_DAT_80435a30[0x52]) {
        PTR_DAT_80435a30[0x52] = (char)iVar12;
        PTR_DAT_80435a30[0x53] = 8;
        zz_00f0468_(0,0x77,0);
      }
    }
  }
  if ((*(uint *)(PTR_DAT_80435a30 + 0x1dc) & 0x10) != 0) {
    PTR_DAT_80435a30[0x43] = PTR_DAT_80435a30[0x43] ^ 1;
    zz_00f0468_(0,0x171,0);
  }
  fVar3 = FLOAT_8043baf8;
  fVar5 = FLOAT_8043baf4;
  dVar13 = DOUBLE_8043bae8;
  *(float *)(PTR_DAT_80435a30 + 0x30) =
       *(float *)(PTR_DAT_80435a30 + 0x30) +
       (float)((double)CONCAT44(0x43300000,
                                (int)(char)(&DAT_803c7212)[(char)PTR_DAT_80435a30[0x46] * 0x20] ^
                                0x80000000) - DOUBLE_8043bae8) / FLOAT_8043baf4;
  *(float *)(PTR_DAT_80435a30 + 0x34) =
       *(float *)(PTR_DAT_80435a30 + 0x34) -
       (float)((double)CONCAT44(0x43300000,
                                (int)(char)(&DAT_803c7213)[(char)PTR_DAT_80435a30[0x46] * 0x20] ^
                                0x80000000) - dVar13) / fVar5;
  fVar5 = FLOAT_8043bad4;
  if (fVar3 < *(float *)(PTR_DAT_80435a30 + 0x34)) {
    fVar3 = *(float *)(PTR_DAT_80435a30 + 0x34) - fVar3;
    fVar4 = fVar3;
    if (fVar3 < FLOAT_8043baf0) {
      fVar4 = -fVar3;
    }
    if (FLOAT_8043bafc < fVar4) {
      fVar4 = FLOAT_8043bafc * fVar3;
      if (fVar3 < FLOAT_8043baf0) {
        fVar3 = -fVar3;
      }
      fVar3 = fVar4 / fVar3;
    }
    *(float *)(PTR_DAT_80435a30 + 0x4c) = *(float *)(PTR_DAT_80435a30 + 0x4c) - fVar3;
    *(float *)(PTR_DAT_80435a30 + 0x34) = *(float *)(PTR_DAT_80435a30 + 0x34) - fVar3;
    fVar3 = FLOAT_8043baf8;
    if (*(float *)(PTR_DAT_80435a30 + 0x4c) < fVar5) {
      *(float *)(PTR_DAT_80435a30 + 0x34) =
           *(float *)(PTR_DAT_80435a30 + 0x34) - (*(float *)(PTR_DAT_80435a30 + 0x4c) - fVar5);
      *(float *)(PTR_DAT_80435a30 + 0x4c) = fVar5;
      if (fVar3 < *(float *)(PTR_DAT_80435a30 + 0x34)) {
        *(float *)(PTR_DAT_80435a30 + 0x34) = fVar3;
      }
    }
  }
  fVar3 = FLOAT_8043babc;
  if (*(float *)(PTR_DAT_80435a30 + 0x34) < FLOAT_8043bb00) {
    fVar5 = *(float *)(PTR_DAT_80435a30 + 0x34) - FLOAT_8043bb00;
    fVar4 = fVar5;
    if (fVar5 < FLOAT_8043baf0) {
      fVar4 = -fVar5;
    }
    if (FLOAT_8043bafc < fVar4) {
      fVar4 = FLOAT_8043bafc * fVar5;
      if (fVar5 < FLOAT_8043baf0) {
        fVar5 = -fVar5;
      }
      fVar5 = fVar4 / fVar5;
    }
    *(float *)(PTR_DAT_80435a30 + 0x4c) = *(float *)(PTR_DAT_80435a30 + 0x4c) - fVar5;
    *(float *)(PTR_DAT_80435a30 + 0x34) = *(float *)(PTR_DAT_80435a30 + 0x34) - fVar5;
    fVar5 = FLOAT_8043bb00;
    if (fVar3 < *(float *)(PTR_DAT_80435a30 + 0x4c)) {
      *(float *)(PTR_DAT_80435a30 + 0x34) =
           *(float *)(PTR_DAT_80435a30 + 0x34) - (*(float *)(PTR_DAT_80435a30 + 0x4c) - fVar3);
      *(float *)(PTR_DAT_80435a30 + 0x4c) = fVar3;
      if (*(float *)(PTR_DAT_80435a30 + 0x34) < fVar5) {
        *(float *)(PTR_DAT_80435a30 + 0x34) = fVar5;
      }
    }
  }
  fVar5 = FLOAT_8043bad8;
  fVar3 = FLOAT_8043bb08;
  if (PTR_DAT_80435a30[0x43] != '\0') {
    fVar3 = FLOAT_8043bb04;
  }
  if (fVar3 < *(float *)(PTR_DAT_80435a30 + 0x30)) {
    fVar3 = *(float *)(PTR_DAT_80435a30 + 0x30) - fVar3;
    fVar4 = fVar3;
    if (fVar3 < FLOAT_8043baf0) {
      fVar4 = -fVar3;
    }
    if (FLOAT_8043bafc < fVar4) {
      fVar4 = FLOAT_8043bafc * fVar3;
      if (fVar3 < FLOAT_8043baf0) {
        fVar3 = -fVar3;
      }
      fVar3 = fVar4 / fVar3;
    }
    *(float *)(PTR_DAT_80435a30 + 0x48) = *(float *)(PTR_DAT_80435a30 + 0x48) - fVar3;
    *(float *)(PTR_DAT_80435a30 + 0x30) = *(float *)(PTR_DAT_80435a30 + 0x30) - fVar3;
    fVar3 = FLOAT_8043bb08;
    if (*(float *)(PTR_DAT_80435a30 + 0x48) < fVar5) {
      *(float *)(PTR_DAT_80435a30 + 0x30) =
           *(float *)(PTR_DAT_80435a30 + 0x30) - (*(float *)(PTR_DAT_80435a30 + 0x48) - fVar5);
      *(float *)(PTR_DAT_80435a30 + 0x48) = fVar5;
      if (fVar3 < *(float *)(PTR_DAT_80435a30 + 0x30)) {
        *(float *)(PTR_DAT_80435a30 + 0x30) = fVar3;
      }
    }
  }
  fVar3 = FLOAT_8043bab8;
  if (*(float *)(PTR_DAT_80435a30 + 0x30) < FLOAT_8043bb0c) {
    fVar5 = *(float *)(PTR_DAT_80435a30 + 0x30) - FLOAT_8043bb0c;
    fVar4 = fVar5;
    if (fVar5 < FLOAT_8043baf0) {
      fVar4 = -fVar5;
    }
    if (FLOAT_8043bafc < fVar4) {
      fVar4 = FLOAT_8043bafc * fVar5;
      if (fVar5 < FLOAT_8043baf0) {
        fVar5 = -fVar5;
      }
      fVar5 = fVar4 / fVar5;
    }
    *(float *)(PTR_DAT_80435a30 + 0x48) = *(float *)(PTR_DAT_80435a30 + 0x48) - fVar5;
    *(float *)(PTR_DAT_80435a30 + 0x30) = *(float *)(PTR_DAT_80435a30 + 0x30) - fVar5;
    fVar5 = FLOAT_8043bb10;
    if (fVar3 < *(float *)(PTR_DAT_80435a30 + 0x48)) {
      *(float *)(PTR_DAT_80435a30 + 0x30) =
           *(float *)(PTR_DAT_80435a30 + 0x30) - (*(float *)(PTR_DAT_80435a30 + 0x48) - fVar3);
      *(float *)(PTR_DAT_80435a30 + 0x48) = fVar3;
      if (*(float *)(PTR_DAT_80435a30 + 0x30) < fVar5) {
        *(float *)(PTR_DAT_80435a30 + 0x30) = fVar5;
      }
    }
  }
  dVar13 = (double)FLOAT_8043baf0;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x146) = 0xffff;
  PTR_DAT_80435a30[0x42] = 0xff;
  *(undefined2 *)(PTR_DAT_80435a30 + 0x50) = 0xffff;
  dVar14 = (double)((*(float *)(PTR_DAT_80435a30 + 0x30) - *(float *)(PTR_DAT_80435a30 + 0x38)) *
                    (*(float *)(PTR_DAT_80435a30 + 0x30) - *(float *)(PTR_DAT_80435a30 + 0x38)) +
                   (*(float *)(PTR_DAT_80435a30 + 0x34) - *(float *)(PTR_DAT_80435a30 + 0x3c)) *
                   (*(float *)(PTR_DAT_80435a30 + 0x34) - *(float *)(PTR_DAT_80435a30 + 0x3c)));
  if (dVar13 < dVar14) {
    dVar13 = 1.0 / SQRT(dVar14);
    dVar13 = DOUBLE_8043bb18 * dVar13 * -(dVar14 * dVar13 * dVar13 - DOUBLE_8043bb20);
    dVar13 = DOUBLE_8043bb18 * dVar13 * -(dVar14 * dVar13 * dVar13 - DOUBLE_8043bb20);
    dVar14 = (double)(float)(dVar14 * DOUBLE_8043bb18 * dVar13 *
                                      -(dVar14 * dVar13 * dVar13 - DOUBLE_8043bb20));
  }
  dVar13 = (double)FLOAT_8043bb28;
  PTR_DAT_80435a30[0x44] = dVar14 <= dVar13;
  if (dVar14 <= dVar13) {
    if ((PTR_DAT_80435a30[0x41] == '\0') && (PTR_DAT_80435a30[0x53] == '\0')) {
      iVar8 = 0;
      iVar6 = 0;
      iVar12 = -1;
      while ((iVar8 < 0x1e && (iVar12 == -1))) {
        if (*(float *)(PTR_DAT_80435a30 + iVar6 + 0x54) <= FLOAT_8043bb2c) {
          fVar3 = *(float *)(PTR_DAT_80435a30 + 0x30) - *(float *)(PTR_DAT_80435a30 + iVar6 + 0x54);
          dVar13 = (double)(fVar3 * fVar3 +
                           (*(float *)(PTR_DAT_80435a30 + 0x34) -
                           *(float *)(PTR_DAT_80435a30 + iVar6 + 0x58)) *
                           (*(float *)(PTR_DAT_80435a30 + 0x34) -
                           *(float *)(PTR_DAT_80435a30 + iVar6 + 0x58)));
          if ((double)FLOAT_8043baf0 < dVar13) {
            dVar14 = 1.0 / SQRT(dVar13);
            dVar14 = DOUBLE_8043bb18 * dVar14 * -(dVar13 * dVar14 * dVar14 - DOUBLE_8043bb20);
            dVar14 = DOUBLE_8043bb18 * dVar14 * -(dVar13 * dVar14 * dVar14 - DOUBLE_8043bb20);
            dVar13 = (double)(float)(dVar13 * DOUBLE_8043bb18 * dVar14 *
                                              -(dVar13 * dVar14 * dVar14 - DOUBLE_8043bb20));
          }
          if (dVar13 <= (double)FLOAT_8043bac8) {
            iVar12 = iVar8;
          }
        }
        iVar6 = iVar6 + 8;
        iVar8 = iVar8 + 1;
      }
      PTR_DAT_80435a30[0x42] = (char)iVar12;
    }
    if (-1 < (char)PTR_DAT_80435a30[0x42]) {
      sVar2 = *(short *)(*(int *)(PTR_DAT_80435a30 + 0x24) + (char)PTR_DAT_80435a30[0x40] * 0x6c +
                         (char)PTR_DAT_80435a30[0x42] * 2 + 0x30);
      if ((-1 < sVar2) &&
         (-1 < *(short *)(*(int *)(PTR_DAT_80435a30 + 0x24) + sVar2 * 0x20 + 0x870))) {
        *(short *)(PTR_DAT_80435a30 + 0x146) = sVar2;
      }
    }
  }
  else {
    uVar9 = 0;
    iVar12 = 0;
    iVar6 = -1;
    fVar3 = (*(float *)(PTR_DAT_80435a30 + 0x30) - *(float *)(PTR_DAT_80435a30 + 0x48)) -
            FLOAT_8043badc;
    fVar5 = (*(float *)(PTR_DAT_80435a30 + 0x34) - *(float *)(PTR_DAT_80435a30 + 0x4c)) -
            FLOAT_8043bae0;
    while (((int)uVar9 < 5 && (iVar6 == -1))) {
      fVar4 = FLOAT_8043bb30 *
              FLOAT_8043bacc *
              (float)((double)CONCAT44(0x43300000,uVar9 ^ 0x80000000) - DOUBLE_8043bae8);
      if ((fVar4 <= fVar3) &&
         (fVar3 < FLOAT_8043bb30 *
                  FLOAT_8043bacc *
                  (float)((double)CONCAT44(0x43300000,uVar9 + 1 ^ 0x80000000) - DOUBLE_8043bae8))) {
        fVar3 = fVar3 - fVar4;
        uVar10 = 0;
        uVar11 = 0xffffffff;
        while (((int)uVar10 < 5 && (uVar11 == 0xffffffff))) {
          if ((FLOAT_8043bacc *
               (float)((double)CONCAT44(0x43300000,uVar10 ^ 0x80000000) - DOUBLE_8043bae8) <= fVar3)
             && (fVar3 < FLOAT_8043bacc *
                         (float)((double)CONCAT44(0x43300000,uVar10 + 1 ^ 0x80000000) -
                                DOUBLE_8043bae8))) {
            uVar11 = uVar10;
          }
          uVar10 = uVar10 + 1;
        }
        iVar6 = iVar12 + uVar11;
      }
      iVar12 = iVar12 + 0x28;
      uVar9 = uVar9 + 1;
    }
    uVar9 = 0;
    iVar8 = 0;
    iVar12 = -1;
    while (((int)uVar9 < 8 && (iVar12 == -1))) {
      if ((FLOAT_8043bacc *
           (float)((double)CONCAT44(0x43300000,uVar9 ^ 0x80000000) - DOUBLE_8043bae8) <= fVar5) &&
         (fVar5 < FLOAT_8043bacc *
                  (float)((double)CONCAT44(0x43300000,uVar9 + 1 ^ 0x80000000) - DOUBLE_8043bae8))) {
        iVar12 = iVar8;
      }
      iVar8 = iVar8 + 5;
      uVar9 = uVar9 + 1;
    }
    if ((iVar6 != -1) && (iVar12 != -1)) {
      *(short *)(PTR_DAT_80435a30 + 0x50) = (short)iVar6 + (short)iVar12;
    }
    sVar2 = *(short *)(PTR_DAT_80435a30 + 0x50);
    if ((-1 < sVar2) && (-1 < *(short *)(*(int *)(PTR_DAT_80435a30 + 0x24) + sVar2 * 0x20 + 0x870)))
    {
      *(short *)(PTR_DAT_80435a30 + 0x146) = sVar2;
    }
  }
  return;
}



// ==== 801bfa54  zz_01bfa54_ ====

void zz_01bfa54_(void)

{
  short *psVar1;
  
  *(undefined4 *)(PTR_DAT_80435a30 + 0x154) = 0;
  if (*(short *)(PTR_DAT_80435a30 + 0x144) < 0) {
    if (*(char *)(*(int *)(PTR_DAT_80435a30 + 0x24) + (char)PTR_DAT_80435a30[0x40] * 0x6c + 0x29) ==
        '\0') {
      *(uint *)(PTR_DAT_80435a30 + 0x154) = *(uint *)(PTR_DAT_80435a30 + 0x154) | 0xc;
    }
    if (0x13 < *(short *)(*(int *)(PTR_DAT_80435a30 + 0x24) + 0x2170)) {
      *(uint *)(PTR_DAT_80435a30 + 0x154) = *(uint *)(PTR_DAT_80435a30 + 0x154) | 4;
    }
    if (*(short *)(PTR_DAT_80435a30 + 0x146) < 0) {
      psVar1 = (short *)0x0;
    }
    else {
      psVar1 = (short *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                        *(short *)(PTR_DAT_80435a30 + 0x146) * 0x20 + 0x870);
    }
  }
  else {
    *(uint *)(PTR_DAT_80435a30 + 0x154) = *(uint *)(PTR_DAT_80435a30 + 0x154) | 0xf;
    psVar1 = (short *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                      *(short *)(PTR_DAT_80435a30 + 0x144) * 0x20 + 0x870);
  }
  if (psVar1 != (short *)0x0) {
    if (1999 < *(short *)(*(int *)(PTR_DAT_80435a30 + 0x28) + 44000)) {
      *(uint *)(PTR_DAT_80435a30 + 0x154) = *(uint *)(PTR_DAT_80435a30 + 0x154) | 0x10;
    }
    if ((*psVar1 != 0x615) && (*psVar1 != 0x629)) {
      return;
    }
    *(uint *)(PTR_DAT_80435a30 + 0x154) = *(uint *)(PTR_DAT_80435a30 + 0x154) | 0x20;
    return;
  }
  *(uint *)(PTR_DAT_80435a30 + 0x154) = *(uint *)(PTR_DAT_80435a30 + 0x154) | 0x30;
  return;
}



// ==== 801bfb74  zz_01bfb74_ ====

void zz_01bfb74_(void)

{
  short sVar1;
  
  sVar1 = *(short *)(*(int *)(PTR_DAT_80435a30 + 0x28) + *(short *)(PTR_DAT_80435a30 + 0x168) * 0x10
                    );
  *(undefined4 *)(PTR_DAT_80435a30 + 0x154) = 0;
  if (199 < *(short *)(*(int *)(PTR_DAT_80435a30 + 0x24) + 0x2172)) {
    *(uint *)(PTR_DAT_80435a30 + 0x154) = *(uint *)(PTR_DAT_80435a30 + 0x154) | 1;
  }
  if ((sVar1 == 0x615) || (sVar1 == 0x629)) {
    *(uint *)(PTR_DAT_80435a30 + 0x154) = *(uint *)(PTR_DAT_80435a30 + 0x154) | 2;
  }
  return;
}



// ==== 801bfbe4  zz_01bfbe4_ ====

void zz_01bfbe4_(void)

{
  *(undefined4 *)(PTR_DAT_80435a30 + 0x154) = 0;
  return;
}



// ==== 801bfbf4  zz_01bfbf4_ ====

uint zz_01bfbf4_(void)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  iVar2 = 0;
  while ((iVar3 < 0x14 && (iVar2 == 0))) {
    iVar2 = zz_01ccd2c_(*(int *)(PTR_DAT_80435a30 + 0x24),iVar3);
    iVar3 = iVar3 + 1;
  }
  uVar1 = countLeadingZeros(iVar2);
  return uVar1 >> 5;
}



// ==== 801bfc5c  zz_01bfc5c_ ====

void zz_01bfc5c_(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  if (*(int *)(param_1 + 0xdc) == 0) {
    piVar2 = zz_0006dc8_(0xc0);
    *(int **)(param_1 + 0xdc) = piVar2;
    puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
    if (puVar3 != (undefined4 *)0x0) {
      uVar1 = *(undefined4 *)(param_1 + 0x24);
      *puVar3 = *(undefined4 *)(param_1 + 0x20);
      puVar3[1] = uVar1;
      puVar3[2] = *(undefined4 *)(param_1 + 0x28);
      zz_00e3ca0_(param_1,-0x7fc7c788,5,puVar3 + 3,(float *)(puVar3 + 0x12));
    }
  }
  return;
}



// ==== 801bfce0  zz_01bfce0_ ====

void zz_01bfce0_(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  if (*(int *)(param_1 + 0xdc) != 0) {
    puVar2 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
    if (puVar2 != (undefined4 *)0x0) {
      uVar1 = *(undefined4 *)(param_1 + 0x24);
      *puVar2 = *(undefined4 *)(param_1 + 0x20);
      puVar2[1] = uVar1;
      puVar2[2] = *(undefined4 *)(param_1 + 0x28);
      if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
        FUN_800e3dec(param_1,(float *)&DAT_80383878,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x12)
                     ,(int *)&DAT_80383978);
      }
      else {
        FUN_800e4f9c(param_1,-0x7fc7c788,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
      }
    }
  }
  return;
}



// ==== 801bfd7c  AsyncImage::FreeLoadBuffer(void) ====

void AsyncImage__FreeLoadBuffer_void_(int param_1)

{
  if (*(int **)(param_1 + 0xdc) != (int *)0x0) {
    zz_0197ad8_(*(int **)(param_1 + 0xdc));
    *(undefined4 *)(param_1 + 0xdc) = 0;
  }
  return;
}



// ==== 801bfdbc  zz_01bfdbc_ ====

void zz_01bfdbc_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  if ((*(int *)(param_1 + 0xdc) != 0) &&
     (pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc), pfVar2 != (float *)0x0)) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fc7c788,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fc7c788,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 801bff90  zz_01bff90_ ====

void zz_01bff90_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  
  *(undefined4 *)(param_9 + 0x144) = 0;
  zz_01bfc5c_(param_9);
  zz_0120b58_(param_9,0x1a);
  iVar1 = zz_0006f98_(param_9);
  iVar4 = iVar1;
  for (cVar2 = '\0'; cVar2 < '\x02'; cVar2 = cVar2 + '\x01') {
    iVar3 = *(int *)(iVar4 + 0x708);
    uVar5 = zz_00086b8_((double)FLOAT_8043bb38,param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,*(int *)(iVar1 + 0x600),iVar3,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    uVar5 = zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                        extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
    zz_0007d40_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,extraout_r4_00,
                param_11,param_12,param_13,param_14,param_15,param_16);
    iVar4 = iVar4 + 0x80;
  }
  *(undefined1 *)(param_9 + 0x6f7) = 0;
  return;
}



// ==== 801c0028  zz_01c0028_ ====

void zz_01c0028_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  char cVar3;
  int iVar2;
  int iVar4;
  undefined8 uVar5;
  
  *(undefined4 *)(param_9 + 0x144) = 0x708;
  zz_01bfc5c_(param_9);
  for (cVar3 = '\x0e'; cVar3 < '\x1b'; cVar3 = cVar3 + '\x01') {
    zz_0120b58_(param_9,cVar3);
  }
  iVar1 = zz_0006f98_(param_9);
  iVar4 = iVar1;
  for (cVar3 = '\0'; cVar3 < '\x02'; cVar3 = cVar3 + '\x01') {
    iVar2 = *(int *)(iVar4 + 0x708);
    uVar5 = zz_00086b8_((double)FLOAT_8043bb3c,param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,*(int *)(iVar1 + 0x600),iVar2,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    uVar5 = zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                        extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
    zz_0007d40_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,extraout_r4_00,
                param_11,param_12,param_13,param_14,param_15,param_16);
    iVar4 = iVar4 + 0x80;
  }
  *(undefined1 *)(param_9 + 0x6f7) = 0;
  return;
}



// ==== 801c0198  FUN_801c0198 ====

void FUN_801c0198(int param_1)

{
  zz_01bfce0_(param_1);
  return;
}



// ==== 801c01b8  FUN_801c01b8 ====

void FUN_801c01b8(char *param_1)

{
  param_1[0x6f7] = '\0';
  if (*(short *)(param_1 + 1000) == 0x80b) {
    if (((*(uint *)(param_1 + 0x5e0) & 0x20000000) == 0) &&
       ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0)) {
      zz_006a8c0_(param_1,0x80a);
      (**(code **)(param_1 + 0x4d0))(param_1);
      (**(code **)(param_1 + 0x4b8))(param_1);
      FUN_800562b8((int)param_1);
      FUN_800061a8((int)param_1,6);
      zz_005f00c_((int)param_1);
    }
  }
  return;
}



// ==== 801c0250  FUN_801c0250 ====

void FUN_801c0250(int param_1)

{
  uint uVar1;
  int iVar2;
  
  if (*(short *)(param_1 + 1000) == 0x80a) {
    if ((((0 < *(short *)(param_1 + 0x784)) && ((*(uint *)(param_1 + 0x5bc) & 0x400) != 0)) &&
        (uVar1 = zz_006ab9c_(param_1), uVar1 != 0)) &&
       (iVar2 = zz_006dbe0_(param_1,2,1,1), iVar2 != 0)) {
      zz_006a3d0_(param_1,'\x04',0,0);
    }
  }
  return;
}



// ==== 801c02dc  zz_01c02dc_ ====

void zz_01c02dc_(int param_1)

{
  AsyncImage__FreeLoadBuffer_void_(param_1);
  return;
}



// ==== 801c02fc  FUN_801c02fc ====

void FUN_801c02fc(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_803839c4)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 801c033c  FUN_801c033c ====

void FUN_801c033c(int param_1)

{
  float local_18;
  float local_14;
  float local_10;
  
  if (((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) && (*(char *)(param_1 + 0x1db) == '\0')) {
    local_18 = FLOAT_8043bb38;
    local_14 = FLOAT_8043bb38;
    local_10 = FLOAT_8043bb40;
    gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x8d4),&local_18,&local_18);
    zz_00fc208_(param_1,&local_18,6);
  }
  return;
}



// ==== 801c03b0  FUN_801c03b0 ====

void FUN_801c03b0(int param_1)

{
  zz_0137540_(param_1,4);
  return;
}



// ==== 801c03d4  FUN_801c03d4 ====

void FUN_801c03d4(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,0x69);
  zz_001ab6c_(param_1,0x69);
  return;
}



// ==== 801c0424  FUN_801c0424 ====

void FUN_801c0424(int param_1)

{
  zz_00e19a8_(param_1,0xb,param_1 + 0x6f7);
  return;
}



// ==== 801c044c  FUN_801c044c ====

void FUN_801c044c(int param_1)

{
  zz_01bfdbc_(param_1);
  return;
}



// ==== 801c0470  FUN_801c0470 ====

void FUN_801c0470(int param_1)

{
  (*(code *)(&PTR_FUN_803839dc)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801c04ac  FUN_801c04ac ====

void FUN_801c04ac(int param_1)

{
  (*(code *)(&PTR_FUN_803839f4)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801c04e8  FUN_801c04e8 ====

void FUN_801c04e8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80383a0c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801c0530  FUN_801c0530 ====

void FUN_801c0530(int param_1)

{
  (**(code **)(&DAT_80435a54 + *(char *)(param_1 + 0x540) * 4))();
  return;
}



// ==== 801c0568  FUN_801c0568 ====

void FUN_801c0568(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  fVar2 = FLOAT_8043bb38;
  *(float *)(param_1 + 0x50) = FLOAT_8043bb38;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d0dc_(param_1,0xc1,0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043bb44,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  dVar3 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_8043bb48 < dVar3) {
    gnt4_PSQUATScale_bl((double)(float)((double)FLOAT_8043bb48 / dVar3),(float *)(param_1 + 0x38),
                        (float *)(param_1 + 0x38));
  }
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043bb4c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,2,(int)cVar1,0xffffffff,0xffffffff);
  *(undefined1 *)(param_1 + 0x6f5) = 0;
  zz_016c7ec_(param_1,6,param_1 + 0x6f5);
  *(float *)(param_1 + 0x80c) = FLOAT_8043bb38;
  return;
}



// ==== 801c06a8  FUN_801c06a8 ====

void FUN_801c06a8(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  if ((*(char *)(param_1 + 0x6f5) != '\0') && (*(char *)(param_1 + 0x541) == '\0')) {
    *(undefined1 *)(param_1 + 0x541) = 1;
  }
  if (((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) && (*(char *)(param_1 + 0x541) != '\0')) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
      zz_006a3d0_(param_1,'\0',2,0);
      return;
    }
    zz_006a3d0_(param_1,'\0',0,0);
    return;
  }
  zz_006d0dc_(param_1,0xc1,0);
  zz_004cd24_(param_1,0xf);
  gnt4_PSQUATScale_bl((double)FLOAT_8043bb44,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar2 = zz_00679d0_(param_1);
  fVar1 = FLOAT_8043bb38;
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    dVar3 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if ((double)FLOAT_8043bb54 < dVar3) {
      zz_00b22f4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    if (iVar2 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = FLOAT_8043bb50 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 801c0800  FUN_801c0800 ====

void FUN_801c0800(int param_1)

{
  (*(code *)(&PTR_FUN_80383a20)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801c083c  FUN_801c083c ====

void FUN_801c083c(int param_1)

{
  (*(code *)(&PTR_FUN_80383a34)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801c0878  FUN_801c0878 ====

void FUN_801c0878(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01c9004_(param_1);
  return;
}



// ==== 801c08ac  FUN_801c08ac ====

void FUN_801c08ac(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01c9004_(param_1);
  return;
}



// ==== 801c08e0  FUN_801c08e0 ====

void FUN_801c08e0(int param_1)

{
  zz_01c956c_(param_1);
  return;
}



// ==== 801c0938  FUN_801c0938 ====

void FUN_801c0938(int param_1)

{
  zz_01c956c_(param_1);
  return;
}



// ==== 801c09a0  FUN_801c09a0 ====

void FUN_801c09a0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01c9004_(param_1);
  return;
}



// ==== 801c09d4  FUN_801c09d4 ====

void FUN_801c09d4(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01c9004_(param_1);
  return;
}



// ==== 801c0a08  FUN_801c0a08 ====

void FUN_801c0a08(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01c9004_(param_1);
  return;
}



// ==== 801c0a3c  FUN_801c0a3c ====

void FUN_801c0a3c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01c9004_(param_1);
  return;
}



// ==== 801c0a70  FUN_801c0a70 ====

void FUN_801c0a70(int param_1)

{
  zz_01c956c_(param_1);
  return;
}



// ==== 801c0ad4  FUN_801c0ad4 ====

void FUN_801c0ad4(int param_1)

{
  zz_01c956c_(param_1);
  return;
}



// ==== 801c0b3c  FUN_801c0b3c ====

void FUN_801c0b3c(int param_1)

{
  (*(code *)(&PTR_FUN_80383b40)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801c0b78  FUN_801c0b78 ====

void FUN_801c0b78(int param_1)

{
  (*(code *)(&PTR_FUN_80383b54)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801c0bb4  FUN_801c0bb4 ====

void FUN_801c0bb4(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_8043bb38;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  *(undefined1 *)(param_1 + 0x6f6) = 1;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x43;
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043bb44,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043bb4c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  zz_01c13b0_(param_1);
  return;
}



// ==== 801c0c98  FUN_801c0c98 ====

void FUN_801c0c98(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,char *param_9)

{
  char cVar1;
  undefined4 extraout_r4;
  float *pfVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar4;
  double dVar5;
  
  zz_004cd24_((int)param_9,0xf);
  gnt4_PSQUATScale_bl((double)FLOAT_8043bb44,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),(float *)(param_9 + 0x20));
  zz_00679d0_((int)param_9);
  if (param_9[0x1cee] != '\0') {
    iVar3 = (byte)param_9[0x540] + 1;
    param_9[0x540] = (char)iVar3;
    param_9[0x1c] = '\0';
    param_9[0x1d] = '<';
    param_9[0x6f6] = '\0';
    pfVar2 = (float *)(uint)(byte)param_9[0x3ec];
    zz_006a8c0_(param_9,0x80b);
    uVar4 = zz_01c02dc_((int)param_9);
    zz_01c0028_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,
                extraout_r4,pfVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
    FUN_800562b8((int)param_9);
    FUN_800061a8((int)param_9,4);
    cVar1 = param_9[0x6ea];
    dVar5 = (double)FLOAT_8043bb4c;
    param_9[0x6ea] = cVar1 + '\x01';
    zz_004beb8_(dVar5,(int)param_9,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
    zz_01c13b0_((int)param_9);
  }
  return;
}



// ==== 801c0d80  FUN_801c0d80 ====

void FUN_801c0d80(int param_1)

{
  int iVar1;
  short sVar2;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043bb44,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar1 = zz_00679d0_(param_1);
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (sVar2 < 1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xffbc;
    if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
  }
  return;
}



// ==== 801c0e24  FUN_801c0e24 ====

void FUN_801c0e24(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,char *param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  float *pfVar1;
  undefined8 uVar2;
  
  pfVar1 = (float *)(uint)(byte)param_9[0x3ec];
  zz_006a8c0_(param_9,0x80a);
  uVar2 = zz_01c02dc_((int)param_9);
  zz_01bff90_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,extraout_r4
              ,pfVar1,param_12,param_13,param_14,param_15,param_16);
  FUN_800562b8((int)param_9);
  FUN_800061a8((int)param_9,6);
  param_9[0x73f] = '\0';
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  if ((*(uint *)(param_9 + 0x5e0) & 0x40) == 0) {
    zz_006a474_((int)param_9);
  }
  else {
    zz_006a5a4_((int)param_9);
  }
  return;
}



// ==== 801c0eb0  FUN_801c0eb0 ====

void FUN_801c0eb0(int param_1)

{
  zz_01c0ed0_(param_1);
  return;
}



// ==== 801c0ed0  zz_01c0ed0_ ====

void zz_01c0ed0_(int param_1)

{
  (*(code *)(&PTR_FUN_80383b60)[*(char *)(param_1 + 0x540)])();
  if ('\0' < *(char *)(param_1 + 0x542)) {
    *(byte *)(param_1 + 0x597) = *(byte *)(param_1 + 0x597) | 4;
  }
  if ('\0' < *(char *)(param_1 + 0x541)) {
    *(undefined1 *)(param_1 + 0x7de) = 4;
  }
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    *(undefined1 *)(param_1 + 0x6f7) = 2;
  }
  return;
}



// ==== 801c0f58  FUN_801c0f58 ====

void FUN_801c0f58(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_8043bb5c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(undefined1 *)(param_1 + 0x542) = 0;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 2;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc0);
  fVar2 = FLOAT_8043bb38;
  *(float *)(param_1 + 0x50) = FLOAT_8043bb38;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043bb68,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043bb4c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  zz_01c13b0_(param_1);
  return;
}



// ==== 801c1058  FUN_801c1058 ====

/* WARNING: Removing unreachable block (ram,0x801c1208) */
/* WARNING: Removing unreachable block (ram,0x801c1068) */

void FUN_801c1058(int param_1)

{
  float fVar1;
  char cVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  bool bVar6;
  double dVar7;
  
  if (*(char *)(param_1 + 0x1cf0) < '\x01') {
    zz_004cd24_(param_1,0xf);
  }
  else {
    dVar7 = (double)*(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x1dc8) = (float)(dVar7 * DOUBLE_8043bb70);
    zz_004cd24_(param_1,0xf);
    *(float *)(param_1 + 0x1dc8) = (float)dVar7;
    fVar1 = (float)((double)*(float *)(param_1 + 0x558) - dVar7);
    bVar6 = fVar1 < FLOAT_8043bb38;
    *(float *)(param_1 + 0x558) = fVar1;
    if (bVar6) {
      *(undefined1 *)(param_1 + 0x1cf0) = 0;
    }
  }
  zz_006d144_(param_1,0xc0);
  gnt4_PSQUATScale_bl((double)FLOAT_8043bb68,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar4 = zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    iVar5 = zz_006dbe0_(param_1,2,1,1);
    if (iVar5 == 0) {
      *(undefined1 *)(param_1 + 0x541) = 0xff;
      *(undefined1 *)(param_1 + 0x6e9) = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x541) = 1;
      *(undefined1 *)(param_1 + 0x542) = 1;
    }
  }
  fVar3 = FLOAT_8043bb78;
  fVar1 = FLOAT_8043bb38;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x541) < '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x02';
    *(undefined1 *)(param_1 + 0x6e9) = 0;
    if (iVar4 != 0) {
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffbf;
    }
    cVar2 = *(char *)(param_1 + 0x6ea);
    dVar7 = (double)FLOAT_8043bb4c;
    *(char *)(param_1 + 0x6ea) = cVar2 + '\x01';
    zz_004beb8_(dVar7,param_1,0xf,4,(int)cVar2,0xffffffff,0xffffffff);
    zz_01c13b0_(param_1);
  }
  else if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar3;
    *(float *)(param_1 + 0x38) = fVar1;
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x7c);
    *(float *)(param_1 + 0x40) = fVar1;
  }
  return;
}



// ==== 801c1228  FUN_801c1228 ====

void FUN_801c1228(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  bool bVar4;
  
  *(float *)(param_1 + 0x3c) =
       *(float *)(*(int *)(param_1 + 0x4ac) + 0x6c) * *(float *)(param_1 + 0x1dc8) +
       *(float *)(param_1 + 0x3c);
  fVar1 = *(float *)(*(int *)(param_1 + 0x4b0) + 0x54);
  if (fVar1 < *(float *)(param_1 + 0x3c)) {
    *(float *)(param_1 + 0x3c) = fVar1;
  }
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar3 = zz_00679d0_(param_1);
  fVar1 = FLOAT_8043bb38;
  if (iVar3 == 0) {
    fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    bVar4 = fVar2 < FLOAT_8043bb38;
    *(float *)(param_1 + 0x558) = fVar2;
    if (bVar4) {
      *(undefined1 *)(param_1 + 0x541) = 0xff;
      *(undefined1 *)(param_1 + 0x6e9) = 0;
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      *(float *)(param_1 + 0x4c) = fVar1;
      *(float *)(param_1 + 0x44) = fVar1;
      zz_006a5a4_(param_1);
      *(float *)(param_1 + 0x694) = FLOAT_8043bb50 + *(float *)(param_1 + 0x1dc8);
    }
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 0xff;
    zz_00b2190_(param_1,2);
  }
  return;
}



// ==== 801c1320  FUN_801c1320 ====

void FUN_801c1320(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043bb38;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = FLOAT_8043bb50 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 801c13b0  zz_01c13b0_ ====

void zz_01c13b0_(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    return;
  }
  *(undefined1 *)(param_1 + 0x1d98) = 0;
  return;
}



// ==== 801c13c8  zz_01c13c8_ ====

void zz_01c13c8_(undefined1 param_1,int param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x10,1,(int)(char)(&DAT_80384e38)[param_2]);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_801c150c;
    *(code **)(puVar1 + 0x10c) = FUN_801c1690;
    puVar1[0x10] = 0;
    puVar1[0x11] = (char)param_2;
    puVar1[0x12] = param_3;
    puVar1[0x96] = param_1;
    puVar1[0x13] = (&DAT_80384e38)[(char)puVar1[0x11]];
  }
  return;
}



// ==== 801c147c  zz_01c147c_ ====

void zz_01c147c_(int param_1,int param_2,undefined1 param_3)

{
  int iVar1;
  
  iVar1 = zz_01c13c8_(*(undefined1 *)(param_1 + 0x96),param_2,param_3);
  if (iVar1 != 0) {
    *(int *)(iVar1 + 0x8c) = param_1;
  }
  return;
}



// ==== 801c14bc  zz_01c14bc_ ====

void zz_01c14bc_(int param_1,int param_2,undefined1 param_3,undefined4 param_4)

{
  int iVar1;
  
  iVar1 = zz_01c13c8_(*(undefined1 *)(param_1 + 0x96),param_2,param_3);
  if (iVar1 != 0) {
    *(int *)(iVar1 + 0x8c) = param_1;
    *(undefined4 *)(iVar1 + 0xcc) = param_4;
  }
  return;
}



// ==== 801c150c  FUN_801c150c ====

void FUN_801c150c(int param_1)

{
  (*(code *)(&PTR_FUN_80384e48)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801c1548  FUN_801c1548 ====

void FUN_801c1548(int param_1)

{
  uint uVar1;
  int *piVar2;
  
  uVar1 = *(char *)(param_1 + 0x13) * 0x24;
  if (uVar1 < 0x81) {
    *(int *)(param_1 + 0x54) = param_1 + 0x144;
    *(undefined4 *)(param_1 + 0xdc) = 0;
  }
  else {
    piVar2 = zz_0006dc8_(uVar1);
    *(int **)(param_1 + 0xdc) = piVar2;
    if (piVar2 != (int *)0x0) {
      *(undefined4 *)(param_1 + 0x54) = *(undefined4 *)(*(int *)(param_1 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_1 + 0x54) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 1;
    (*(code *)(&PTR_FUN_80384e58)[*(char *)(param_1 + 0x11)])(param_1);
  }
  return;
}



// ==== 801c15f8  FUN_801c15f8 ====

void FUN_801c15f8(int param_1)

{
  (*(code *)(&PTR_LAB_80384e98)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801c1648  FUN_801c1648 ====

void FUN_801c1648(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801c1690  FUN_801c1690 ====

void FUN_801c1690(int param_1)

{
  (*(code *)(&PTR_FUN_80384ed8)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801c16cc  FUN_801c16cc ====

void FUN_801c16cc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  
  piVar6 = &DAT_80384f18;
  iVar5 = 0;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    iVar1 = piVar6[2];
    piVar2 = (int *)(*(int *)(param_9 + 0x54) + iVar5);
    *piVar2 = piVar6[1];
    piVar2[1] = iVar1;
    piVar2[2] = piVar6[3];
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb32c,*(int *)(iVar4 + 0xe0),*piVar6,param_12,param_13,param_14,
                          param_15,param_16);
    piVar6 = piVar6 + 4;
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
  }
  *(undefined1 *)(param_9 + 0x82) = 5;
  return;
}



// ==== 801c1770  FUN_801c1770 ====

void FUN_801c1770(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  float afStack_48 [14];
  
  gnt4_PSMTXIdentity_bl((float *)(param_9 + 0x114));
  iVar4 = 0;
  iVar3 = param_9;
  for (iVar2 = 0; iVar2 < *(char *)(param_9 + 0x13); iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar4);
    uVar5 = zz_00455fc_((float *)(param_9 + 0x114),afStack_48,pfVar1);
    zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0xe0)
                ,afStack_48,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(*(int *)(iVar3 + 0xe0),1);
    iVar4 = iVar4 + 0x24;
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 801c1810  FUN_801c1810 ====

void FUN_801c1810(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,uint param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *extraout_r4;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  
  iVar8 = 0;
  uVar4 = (uint)*(byte *)(param_9 + 0x12);
  puVar6 = &DAT_80385108;
  iVar2 = (char)*(byte *)(param_9 + 0x12) * 0x18;
  puVar3 = (undefined4 *)(&DAT_80384f28 + iVar2);
  *(short *)(param_9 + 0x1c) = (short)*puVar3;
  uVar1 = *(undefined4 *)(&DAT_80384f38 + iVar2);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(&DAT_80384f34 + iVar2);
  *(undefined4 *)(param_9 + 0x24) = uVar1;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(&DAT_80384f3c + iVar2);
  iVar2 = param_9;
  puVar7 = puVar3;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    puVar3 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar8);
    *(undefined2 *)(puVar3 + 8) = *(undefined2 *)(puVar7 + 1);
    *(undefined2 *)((int)puVar3 + 0x22) = 0;
    uVar1 = puVar6[1];
    *puVar3 = *puVar6;
    puVar3[1] = uVar1;
    puVar3[2] = puVar6[2];
    uVar4 = (uint)*(short *)(puVar3 + 8);
    if (-1 < *(short *)(puVar3 + 8)) {
      param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            DAT_803bb32c,*(int *)(iVar2 + 0xe0),uVar4,param_12,param_13,param_14,
                            param_15,param_16);
      puVar3 = extraout_r4;
    }
    iVar8 = iVar8 + 0x24;
    puVar7 = (undefined4 *)((int)puVar7 + 2);
    puVar6 = puVar6 + 3;
    iVar2 = iVar2 + 4;
  }
  *(undefined1 *)(param_9 + 0x82) = 5;
  zz_01c1910_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,puVar3,uVar4,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801c1910  zz_01c1910_ ====

void zz_01c1910_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,uint param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = 0;
  iVar5 = param_9;
  for (iVar4 = 0; iVar4 < *(char *)(param_9 + 0x13); iVar4 = iVar4 + 1) {
    iVar3 = *(int *)(param_9 + 0x54) + iVar6;
    if (iVar4 == 0) {
      sVar1 = *(short *)(iVar3 + 0x22);
      uVar2 = (int)sVar1 + 1;
      *(short *)(iVar3 + 0x22) = (short)uVar2;
      param_12 = uVar2 & 0x10;
      if ((-1 < *(short *)(iVar3 + 0x20)) && (((int)sVar1 & 0x10U) != param_12)) {
        param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              DAT_803bb32c,*(int *)(iVar5 + 0xe0),
                              (int)*(short *)(iVar3 + 0x20) - ((int)-param_12 >> 0x1f),param_12,
                              param_13,param_14,param_15,param_16);
      }
    }
    else if (((iVar4 == 2) && (*(char *)(param_9 + 0x12) == '\x04')) &&
            (uVar2 = (uint)(int)*(short *)(PTR_DAT_80435a30 + 0x144) >> 0x1f ^ 1,
            uVar2 != (int)*(short *)(iVar3 + 0x22))) {
      *(short *)(iVar3 + 0x22) = (short)uVar2;
      param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            DAT_803bb32c,*(int *)(iVar5 + 0xe0),
                            (int)*(short *)(iVar3 + 0x20) + (int)*(short *)(iVar3 + 0x22),param_12,
                            param_13,param_14,param_15,param_16);
    }
    iVar6 = iVar6 + 0x24;
    iVar5 = iVar5 + 4;
  }
  return;
}



// ==== 801c1a30  FUN_801c1a30 ====

void FUN_801c1a30(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [14];
  
  if ((int)(char)PTR_DAT_80435a30[0x149] == (int)*(short *)(param_1 + 0x1c)) {
    dVar6 = (double)*(float *)(param_1 + 0x24);
    dVar7 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar6,dVar7,(float *)(param_1 + 0x114));
    iVar4 = 0;
    iVar3 = param_1;
    for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
      pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
      if (-1 < *(short *)(pfVar1 + 8)) {
        uVar5 = zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar1);
        zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),
                    afStack_48,(undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
        zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
      }
      iVar4 = iVar4 + 0x24;
      iVar3 = iVar3 + 4;
    }
  }
  return;
}



// ==== 801c1b00  FUN_801c1b00 ====

void FUN_801c1b00(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  float fVar4;
  size_t sVar5;
  int iVar6;
  undefined4 extraout_r4;
  float *pfVar7;
  int iVar8;
  char *pcVar9;
  short *psVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  undefined8 uVar14;
  double dVar15;
  char local_39 [9];
  undefined4 local_30;
  uint uStack_2c;
  
  fVar2 = FLOAT_8043bb88;
  fVar1 = FLOAT_8043bb84;
  fVar4 = FLOAT_8043bb80;
  dVar15 = (double)FLOAT_8043bb80;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(float *)(param_9 + 0xd8) = fVar4;
  *(float *)(param_9 + 0x38) = fVar1;
  dVar12 = (double)FLOAT_8043bb8c;
  *(float *)(param_9 + 0x3c) = fVar4;
  *(float *)(param_9 + 0x40) = fVar2;
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(param_9 + 0x38);
  *(undefined4 *)(param_9 + 0x68) = *(undefined4 *)(param_9 + 0x3c);
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(param_9 + 0x40);
  dVar13 = (double)*(float *)(param_9 + 100);
  *(float *)(param_9 + 100) = (float)(dVar13 + dVar12);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x38);
  *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x3c);
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x40);
  *(short *)(param_9 + 0x72) = (short)*(char *)(param_9 + 0x12) << 0xe;
  *(undefined2 *)(param_9 + 0x7e) = *(undefined2 *)(param_9 + 0x72);
  *(undefined *)(param_9 + 0x12) = PTR_DAT_80435a30[0x40];
  iVar3 = *(char *)(param_9 + 0x12) + 1;
  iVar8 = 0x14;
  if (iVar3 < 0x14) {
    iVar8 = iVar3;
  }
  sprintf(local_39 + 1,&DAT_8043bb90,iVar8);
  sVar5 = strlen(local_39 + 1);
  psVar10 = &DAT_80385138;
  pcVar9 = local_39;
  iVar11 = 0;
  iVar8 = param_9;
  for (iVar3 = 0; pcVar9 = pcVar9 + 1, iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    pfVar7 = (float *)(*(int *)(param_9 + 0x54) + iVar11);
    *(short *)(pfVar7 + 8) = psVar10[1];
    fVar4 = *(float *)(psVar10 + 4);
    *pfVar7 = *(float *)(psVar10 + 2);
    pfVar7[1] = fVar4;
    pfVar7[2] = *(float *)(psVar10 + 6);
    dVar13 = (double)zz_0006fb4_(dVar13,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_803bb32c,*(int *)(iVar8 + 0xe0),(int)*psVar10,param_12,param_13
                                 ,param_14,param_15,param_16);
    if (iVar3 == 0) {
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | 1;
    }
    else {
      if (sVar5 == 1) {
        dVar13 = (double)*pfVar7;
        *pfVar7 = (float)(dVar13 + (double)FLOAT_8043bb94);
      }
      dVar12 = DOUBLE_8043bb98;
      if (((iVar3 + -1 < (int)sVar5) && (iVar6 = (int)pcVar9[-1], 0x2f < iVar6)) && (iVar6 < 0x3a))
      {
        uStack_2c = iVar6 - 0x30U ^ 0x80000000;
        pfVar7 = (float *)(int)(short)*(ushort *)(param_9 + 0x1c);
        local_30 = 0x43300000;
        *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar3);
        uVar14 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_2c) - dVar12),dVar15
                             ,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                             *(int *)(iVar8 + 0xe0),pfVar7,param_12,param_13,param_14,param_15,
                             param_16);
        dVar13 = (double)zz_0007c30_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,
                                     *(int *)(iVar8 + 0xe0),extraout_r4,pfVar7,param_12,param_13,
                                     param_14,param_15,param_16);
      }
    }
    iVar11 = iVar11 + 0x24;
    psVar10 = psVar10 + 8;
    iVar8 = iVar8 + 4;
  }
  iVar8 = 0;
  do {
    uVar14 = zz_01c147c_(param_9,3,(char)iVar8);
    iVar8 = iVar8 + 1;
  } while (iVar8 < 0x1e);
  if (-1 < (char)PTR_DAT_80435a30[0x45]) {
    iVar8 = 0;
    do {
      uVar14 = zz_01c147c_(param_9,4,(char)iVar8);
      iVar8 = iVar8 + 1;
    } while (iVar8 < 0xb);
  }
  iVar8 = 0;
  do {
    if ((iVar8 == 0) || (-1 < *(int *)(PTR_DAT_80433934 + 0x120))) {
      uVar14 = zz_01c147c_(param_9,9,(char)iVar8);
    }
    iVar8 = iVar8 + 1;
  } while (iVar8 < 3);
  *(undefined1 *)(param_9 + 0x82) = 3;
  zz_01c1dac_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801c1dac  zz_01c1dac_ ====

void zz_01c1dac_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float *pfVar2;
  undefined4 extraout_r4;
  undefined4 uVar3;
  float fVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar5;
  undefined8 uVar6;
  double dVar7;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  if (PTR_DAT_80435a30[0x43] == '\0') {
    local_2c = *(float *)(param_9 + 0x38);
    local_28 = *(undefined4 *)(param_9 + 0x3c);
    local_24 = *(undefined4 *)(param_9 + 0x40);
  }
  else {
    local_2c = *(float *)(param_9 + 100);
    local_28 = *(undefined4 *)(param_9 + 0x68);
    local_24 = *(undefined4 *)(param_9 + 0x6c);
  }
  local_38 = local_2c;
  local_34 = local_28;
  local_30 = local_24;
  uVar3 = local_28;
  fVar4 = local_2c;
  gnt4_PSVECSubtract_bl(&local_38,(float *)(param_9 + 0x20),&local_38);
  dVar5 = gnt4_PSVECMag_bl(&local_38);
  if ((double)FLOAT_8043bba0 < dVar5) {
    gnt4_PSVECNormalize_bl(&local_38,&local_38);
    gnt4_PSQUATScale_bl((double)FLOAT_8043bba0,&local_38,&local_38);
  }
  pfVar2 = (float *)(param_9 + 0x20);
  gnt4_PSVECAdd_bl(pfVar2,&local_38,pfVar2);
  fVar1 = FLOAT_8043bba8;
  dVar7 = (double)*(float *)(param_9 + 0xd8);
  dVar5 = (double)FLOAT_8043bba4;
  *(float *)(param_9 + 0xd8) = (float)(dVar7 + dVar5);
  if (fVar1 <= (float)(dVar7 + dVar5)) {
    *(float *)(param_9 + 0xd8) = *(float *)(param_9 + 0xd8) - fVar1;
  }
  uVar6 = zz_00086b8_((double)*(float *)(param_9 + 0xd8),dVar7,param_3,param_4,param_5,param_6,
                      param_7,param_8,DAT_803bb32c,*(int *)(param_9 + 0xe0),pfVar2,uVar3,fVar4,in_r8
                      ,in_r9,in_r10);
  zz_0007c30_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0),
              extraout_r4,pfVar2,uVar3,fVar4,in_r8,in_r9,in_r10);
  (**(code **)(&DAT_80435a60 + *(char *)(param_9 + 0x19) * 4))(param_9);
  *(short *)(param_9 + 0x72) =
       (short)(int)((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x7e) ^ 0x80000000
                                            ) - DOUBLE_8043bb98) * *(float *)(param_9 + 0xd4));
  return;
}



// ==== 801c1f24  FUN_801c1f24 ====

void FUN_801c1f24(int param_1)

{
  float fVar1;
  undefined2 uVar2;
  int iVar3;
  
  *(float *)(param_1 + 0xd4) =
       (float)((double)CONCAT44(0x43300000,(int)(char)PTR_DAT_80435a30[0x41] ^ 0x80000000) -
              DOUBLE_8043bb98) * FLOAT_8043bbac;
  fVar1 = FLOAT_8043bba4;
  if (*(char *)(param_1 + 0x12) != PTR_DAT_80435a30[0x40]) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(float *)(param_1 + 0xd4) = fVar1 - *(float *)(param_1 + 0xd4);
    iVar3 = (int)(char)PTR_DAT_80435a30[0x40] - (int)*(char *)(param_1 + 0x12);
    if (iVar3 < 0) {
      iVar3 = iVar3 + 0x14;
    }
    uVar2 = 0xc000;
    if (iVar3 < 0xb) {
      uVar2 = 0x4000;
    }
    *(undefined2 *)(param_1 + 0x7e) = uVar2;
  }
  return;
}



// ==== 801c1fd4  FUN_801c1fd4 ====

void FUN_801c1fd4(int param_1)

{
  *(float *)(param_1 + 0xd4) =
       -((float)((double)CONCAT44(0x43300000,(int)(char)PTR_DAT_80435a30[0x41] ^ 0x80000000) -
                DOUBLE_8043bb98) * FLOAT_8043bbac - FLOAT_8043bba4);
  if ((char)PTR_DAT_80435a30[0x41] < '\x05') {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801c2034  FUN_801c2034 ====

void FUN_801c2034(int param_1)

{
  float *pfVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float afStack_50 [14];
  
  dVar8 = (double)*(float *)(param_1 + 0x24);
  dVar9 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar8,dVar9,(float *)(param_1 + 0x114));
  iVar2 = (int)*(short *)(param_1 + 0x72);
  zz_00457d4_('y',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x72));
  iVar4 = 0;
  iVar6 = 0;
  iVar5 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar4) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar4) != 0) {
      pfVar3 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
      pfVar1 = pfVar3;
      uVar7 = zz_00455fc_((float *)(param_1 + 0x114),afStack_50,pfVar3);
      zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),afStack_50,
                  (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
      zz_00097b4_(*(int *)(iVar5 + 0xe0),(int)*(short *)(pfVar3 + 8));
    }
    iVar6 = iVar6 + 0x24;
    iVar5 = iVar5 + 4;
    iVar4 = iVar4 + 1;
  }
  local_5c = FLOAT_8043bbb0;
  local_58 = FLOAT_8043bbb4;
  local_54 = FLOAT_8043bbb8;
  local_60 = FLOAT_8043bba4;
  local_64 = FLOAT_8043bba4;
  local_68 = FLOAT_8043bba4;
  FUN_801c5600((double)FLOAT_8043bba4,(double)FLOAT_8043bbbc,(double)FLOAT_8043bbc0,
               (float *)(param_1 + 0x114),&local_5c,&local_68,2,0x1e,
               (short *)(*(int *)(PTR_DAT_80435a30 + 0x24) + (char)PTR_DAT_80435a30[0x40] * 0x6c));
  return;
}



// ==== 801c2154  FUN_801c2154 ====

void FUN_801c2154(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  float fVar5;
  size_t sVar6;
  int iVar7;
  undefined4 extraout_r4;
  float *pfVar8;
  float *pfVar9;
  char *pcVar10;
  int iVar11;
  undefined2 *puVar12;
  int iVar13;
  double dVar14;
  undefined8 uVar15;
  double dVar16;
  char acStack_38 [8];
  undefined4 local_30;
  uint uStack_2c;
  
  fVar2 = FLOAT_8043bbc8;
  fVar5 = FLOAT_8043bb80;
  dVar16 = (double)FLOAT_8043bb80;
  dVar14 = (double)FLOAT_8043bbc8;
  *(float *)(param_9 + 0x20) = FLOAT_8043bbc4;
  fVar3 = FLOAT_8043bbcc;
  *(float *)(param_9 + 0x24) = fVar5;
  *(float *)(param_9 + 0x28) = fVar5;
  *(float *)(param_9 + 100) = fVar2;
  *(float *)(param_9 + 0x68) = fVar5;
  *(float *)(param_9 + 0x6c) = fVar5;
  *(float *)(param_9 + 0x40) = fVar5;
  *(float *)(param_9 + 0x3c) = fVar5;
  *(float *)(param_9 + 0xa4) = fVar5;
  *(float *)(param_9 + 0xa0) = fVar5;
  cVar1 = PTR_DAT_80435a30[0x52];
  *(short *)(param_9 + 0x1e) = (short)cVar1;
  *(short *)(param_9 + 0x1c) = (short)cVar1;
  *(float *)(param_9 + 0xd4) = fVar3;
  *(float *)(param_9 + 0xd8) = fVar5;
  iVar4 = *(char *)(param_9 + 0x12) + 1;
  iVar11 = 0x1e;
  if (iVar4 < 0x1e) {
    iVar11 = iVar4;
  }
  sprintf(acStack_38,&DAT_8043bb90,iVar11);
  sVar6 = strlen(acStack_38);
  puVar12 = &DAT_80385168;
  pcVar10 = acStack_38;
  iVar13 = 0;
  iVar11 = param_9;
  for (iVar4 = 0; iVar4 < *(char *)(param_9 + 0x13); iVar4 = iVar4 + 1) {
    pfVar9 = (float *)(*(int *)(param_9 + 0x54) + iVar13);
    *(undefined2 *)(pfVar9 + 8) = *puVar12;
    *(undefined2 *)((int)pfVar9 + 0x22) = puVar12[1];
    fVar5 = *(float *)(puVar12 + 2);
    pfVar9[5] = fVar5;
    pfVar9[4] = fVar5;
    pfVar9[3] = fVar5;
    fVar5 = *(float *)(puVar12 + 6);
    *pfVar9 = *(float *)(puVar12 + 4);
    pfVar9[1] = fVar5;
    pfVar9[2] = *(float *)(puVar12 + 8);
    if ((sVar6 == 1) && (4 < iVar4)) {
      dVar14 = (double)*pfVar9;
      *pfVar9 = (float)(dVar14 + (double)FLOAT_8043bbd0);
    }
    pfVar8 = (float *)(int)*(short *)(pfVar9 + 8);
    if ((-1 < *(short *)(pfVar9 + 8)) &&
       (dVar14 = (double)zz_0006fb4_(dVar14,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,
                                     DAT_803bb32c,*(int *)(iVar11 + 0xe0),(int)pfVar8,param_12,
                                     param_13,param_14,param_15,param_16), 3 < iVar4)) {
      if (4 < iVar4) {
        if (iVar4 + -5 < (int)sVar6) {
          iVar7 = (int)pcVar10[-5];
          if ((0x2f < iVar7) && (iVar7 < 0x3a)) {
            uStack_2c = iVar7 - 0x30U ^ 0x80000000;
            local_30 = 0x43300000;
            uVar15 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_2c) -
                                                DOUBLE_8043bb98),dVar16,param_3,param_4,param_5,
                                 param_6,param_7,param_8,DAT_803bb32c,*(int *)(iVar11 + 0xe0),pfVar8
                                 ,param_12,param_13,param_14,param_15,param_16);
            zz_0007c30_(uVar15,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar11 + 0xe0),extraout_r4,pfVar8,param_12,param_13,param_14,
                        param_15,param_16);
          }
        }
        else {
          *(undefined2 *)(pfVar9 + 8) = 0xffff;
        }
      }
      dVar14 = (double)zz_0007d8c_(*(int *)(iVar11 + 0xe0),7);
    }
    iVar13 = iVar13 + 0x24;
    puVar12 = puVar12 + 10;
    iVar11 = iVar11 + 4;
    pcVar10 = pcVar10 + 1;
  }
  *(undefined1 *)(param_9 + 0x82) = 3;
  zz_01c2360_(param_9);
  return;
}



// ==== 801c2360  zz_01c2360_ ====

/* WARNING: Removing unreachable block (ram,0x801c28a8) */
/* WARNING: Removing unreachable block (ram,0x801c2370) */

void zz_01c2360_(int param_1)

{
  byte bVar1;
  short sVar2;
  undefined2 uVar3;
  float fVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  int iVar9;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar10;
  undefined *puVar11;
  int iVar12;
  int iVar13;
  undefined4 in_r10;
  int iVar14;
  int iVar15;
  int iVar16;
  int iVar17;
  double dVar18;
  double dVar19;
  undefined8 uVar20;
  double dVar21;
  double dVar22;
  double dVar23;
  double dVar24;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar25;
  char local_48;
  byte bStack_47;
  double local_38;
  undefined8 local_30;
  
  iVar14 = *(int *)(param_1 + 0x8c);
  dVar25 = (double)FLOAT_8043bb80;
  if (PTR_DAT_80435a30[0x40] == *(char *)(iVar14 + 0x12)) {
    if (PTR_DAT_80435a30[0x42] == *(char *)(param_1 + 0x12)) {
      dVar25 = (double)FLOAT_8043bbd4;
    }
    if ((int)(char)PTR_DAT_80435a30[0x52] != (int)*(short *)(param_1 + 0x1c)) {
      *(short *)(param_1 + 0x1c) = (short)(char)PTR_DAT_80435a30[0x52];
    }
  }
  if ((*(short *)(param_1 + 0x1c) != *(short *)(param_1 + 0x1e)) && (PTR_DAT_80435a30[0x53] == '\0')
     ) {
    *(short *)(param_1 + 0x1e) = *(short *)(param_1 + 0x1c);
  }
  dVar22 = DOUBLE_8043bb98;
  uVar8 = (int)*(char *)(param_1 + 0x12) - (int)*(short *)(param_1 + 0x1c);
  uVar6 = uVar8 / 0x1e;
  if (0x1d < (int)uVar8) {
    do {
      uVar8 = uVar8 - 0x1e;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
  uVar6 = (0x1d - uVar8) / 0x1e;
  if ((int)uVar8 < 0) {
    do {
      uVar8 = uVar8 + 0x1e;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
  uVar6 = (int)*(char *)(param_1 + 0x12) - (int)*(short *)(param_1 + 0x1e);
  uVar7 = uVar6 / 0x1e;
  if (0x1d < (int)uVar6) {
    do {
      uVar6 = uVar6 - 0x1e;
      uVar7 = uVar7 - 1;
    } while (uVar7 != 0);
  }
  uVar7 = (0x1d - uVar6) / 0x1e;
  if ((int)uVar6 < 0) {
    do {
      uVar6 = uVar6 + 0x1e;
      uVar7 = uVar7 - 1;
    } while (uVar7 != 0);
  }
  fVar4 = FLOAT_8043bb80;
  if (PTR_DAT_80435a30[0x53] != '\0') {
    fVar4 = -((float)((double)CONCAT44(0x43300000,(int)(char)PTR_DAT_80435a30[0x53] ^ 0x80000000) -
                     DOUBLE_8043bb98) * FLOAT_8043bbd8 - FLOAT_8043bba4);
  }
  iVar13 = uVar8 - uVar6;
  *(float *)(param_1 + 0x38) =
       fVar4 * (*(float *)(&DAT_803851f4 + uVar8 * 4) - *(float *)(&DAT_803851f4 + uVar6 * 4)) +
       *(float *)(&DAT_803851f4 + uVar6 * 4);
  local_38 = (double)(CONCAT44(0x43300000,
                               (int)*(short *)(&DAT_8038526c + uVar8 * 2) -
                               (int)*(short *)(&DAT_8038526c + uVar6 * 2)) ^ 0x80000000);
  *(short *)(param_1 + 0x72) =
       *(short *)(&DAT_8038526c + uVar6 * 2) + (short)(int)(fVar4 * (float)(local_38 - dVar22));
  dVar22 = DOUBLE_8043bb98;
  if (iVar13 < 0) {
    iVar13 = iVar13 + 0x1e;
  }
  if (0xf < iVar13) {
    fVar4 = FLOAT_8043bba4 - fVar4;
    uVar6 = uVar8;
  }
  local_30 = (double)CONCAT44(0x43300000,uVar6 ^ 0x80000000);
  for (fVar4 = ((float)(local_30 - DOUBLE_8043bb98) + fVar4) - FLOAT_8043bbdc;
      FLOAT_8043bba0 <= fVar4; fVar4 = fVar4 - FLOAT_8043bba0) {
  }
  for (; fVar4 < FLOAT_8043bb80; fVar4 = fVar4 + FLOAT_8043bba0) {
  }
  iVar13 = (int)fVar4;
  uVar8 = iVar13 + 1;
  uVar6 = uVar8 / 0x1e;
  local_38 = (double)(CONCAT44(0x43300000,iVar13) ^ 0x80000000);
  dVar24 = (double)(fVar4 - (float)(local_38 - DOUBLE_8043bb98));
  if (0x1d < (int)uVar8) {
    do {
      uVar8 = uVar8 - 0x1e;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
  uVar6 = (0x1d - uVar8) / 0x1e;
  if ((int)uVar8 < 0) {
    do {
      uVar8 = uVar8 + 0x1e;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
  puVar11 = &DAT_803851f4;
  iVar12 = iVar13 * 4;
  dVar23 = (double)*(float *)(&DAT_803851f4 + iVar12);
  dVar18 = (double)FLOAT_8043bbe0;
  dVar19 = (double)FLOAT_8043bba8;
  *(float *)(param_1 + 0x9c) =
       (float)(dVar24 * (double)(float)((double)*(float *)(&DAT_803851f4 + uVar8 * 4) - dVar23) +
              dVar23);
  pfVar10 = (float *)(int)*(short *)(&DAT_8038526c + iVar13 * 2);
  local_30 = (double)(CONCAT44(0x43300000,(int)*(short *)(&DAT_8038526c + uVar8 * 2) - (int)pfVar10)
                     ^ 0x80000000);
  *(short *)(param_1 + 0x74) =
       *(short *)(&DAT_8038526c + iVar13 * 2) +
       (short)(int)(dVar24 * (double)(float)(local_30 - dVar22));
  dVar21 = (double)*(float *)(param_1 + 0xd8);
  *(float *)(param_1 + 0xd8) = (float)(dVar21 + dVar18);
  if (dVar19 <= (double)(float)(dVar21 + dVar18)) {
    *(float *)(param_1 + 0xd8) = (float)((double)*(float *)(param_1 + 0xd8) - dVar19);
  }
  iVar17 = 0;
  iVar16 = param_1;
  for (iVar15 = 0; iVar5 = DAT_803bb32c, iVar15 < *(char *)(param_1 + 0x13); iVar15 = iVar15 + 1) {
    iVar9 = *(int *)(param_1 + 0x54) + iVar17;
    if (iVar15 == 0) {
      if (dVar25 != (double)*(float *)(param_1 + 0xd4)) {
        iVar9 = *(int *)(iVar16 + 0xe0);
        *(float *)(param_1 + 0xd4) = (float)dVar25;
        uVar20 = zz_00086b8_(dVar25,dVar21,dVar22,dVar23,dVar24,in_f6,in_f7,in_f8,iVar5,iVar9,
                             pfVar10,puVar11,iVar12,uVar8,iVar13,in_r10);
        dVar19 = (double)zz_0007c30_(uVar20,dVar21,dVar22,dVar23,dVar24,in_f6,in_f7,in_f8,
                                     *(int *)(iVar16 + 0xe0),extraout_r4,pfVar10,puVar11,iVar12,
                                     uVar8,iVar13,in_r10);
      }
    }
    else if (iVar15 == 1) {
      if (PTR_DAT_80435a30[0x42] == *(char *)(param_1 + 0x12)) {
        *(undefined2 *)(iVar9 + 0x20) = 0;
      }
      else {
        *(undefined2 *)(iVar9 + 0x20) = 0xffff;
      }
      uVar20 = zz_00086b8_((double)*(float *)(param_1 + 0xd8),dVar21,dVar22,dVar23,dVar24,in_f6,
                           in_f7,in_f8,DAT_803bb32c,*(int *)(iVar16 + 0xe0),pfVar10,puVar11,iVar12,
                           uVar8,iVar13,in_r10);
      dVar19 = (double)zz_0007c30_(uVar20,dVar21,dVar22,dVar23,dVar24,in_f6,in_f7,in_f8,
                                   *(int *)(iVar16 + 0xe0),extraout_r4_00,pfVar10,puVar11,iVar12,
                                   uVar8,iVar13,in_r10);
    }
    else if (iVar15 == 2) {
      bVar1 = PTR_DAT_80435a30[0x45];
      pfVar10 = (float *)(uint)bVar1;
      if (((char)bVar1 < '\0') ||
         ((*(byte *)(param_1 + 0x12) != 0 && (*(byte *)(param_1 + 0x12) != bVar1)))) {
        *(undefined2 *)(iVar9 + 0x20) = 0xffff;
      }
      else {
        *(undefined2 *)(iVar9 + 0x20) = 0;
      }
    }
    else if (iVar15 == 3) {
      pfVar10 = (float *)(*(char *)(iVar14 + 0x12) * 0x6c);
      puVar11 = *(undefined **)(PTR_DAT_80435a30 + 0x24);
      sVar2 = *(short *)((int)pfVar10 + (int)(puVar11 + *(char *)(param_1 + 0x12) * 2 + 0x30));
      if (((int)*(short *)(iVar9 + 0x20) != (int)sVar2) &&
         (*(short *)(iVar9 + 0x20) = sVar2, -1 < sVar2)) {
        uVar3 = *(undefined2 *)(*(int *)(PTR_DAT_80435a30 + 0x24) + sVar2 * 0x20 + 0x870);
        local_48 = (char)((ushort)uVar3 >> 8);
        bStack_47 = (byte)uVar3;
        puVar11 = (undefined *)(local_48 * 4);
        pfVar10 = *(float **)((&PTR_DAT_80350d0c)[local_48] + (uint)bStack_47 * 4);
        zz_0006fb4_(dVar19,dVar21,dVar22,dVar23,dVar24,in_f6,in_f7,in_f8,DAT_803bb334,
                    *(int *)(iVar16 + 0xe0),(int)pfVar10,puVar11,iVar12,uVar8,iVar13,in_r10);
        dVar19 = (double)zz_0007d8c_(*(int *)(iVar16 + 0xe0),7);
      }
    }
    iVar17 = iVar17 + 0x24;
    iVar16 = iVar16 + 4;
  }
  if ('\x01' < *(char *)(iVar14 + 0x18)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801c28c4  FUN_801c28c4 ====

void FUN_801c28c4(int param_1)

{
  float *pfVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_88;
  float local_84;
  float local_80;
  float afStack_7c [3];
  float local_70;
  float local_60;
  float local_50;
  float afStack_4c [14];
  
  iVar4 = *(int *)(param_1 + 0x8c);
  zz_00455fc_((float *)(iVar4 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x20));
  gnt4_PSMTXCopy_bl((float *)(param_1 + 0x114),afStack_4c);
  if ((PTR_DAT_80435a30[0x40] == *(char *)(iVar4 + 0x12)) && (*(char *)(param_1 + 0x12) == '\0')) {
    local_88 = *(float *)(param_1 + 0x120);
    local_84 = *(float *)(param_1 + 0x130);
    local_80 = *(float *)(param_1 + 0x140);
    *(float *)(PTR_DAT_80435a30 + 0x38) = local_88;
    *(float *)(PTR_DAT_80435a30 + 0x3c) = local_80;
  }
  zz_00455fc_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x38));
  iVar2 = (int)*(short *)(param_1 + 0x72);
  zz_00457d4_('y',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x72));
  zz_00455fc_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 100));
  local_88 = *(float *)(param_1 + 0x120);
  local_84 = *(float *)(param_1 + 0x130);
  dVar8 = (double)local_84;
  local_80 = *(float *)(param_1 + 0x140);
  dVar9 = (double)local_80;
  gnt4_PSMTXTrans_bl((double)local_88,dVar8,dVar9,(float *)(param_1 + 0x114));
  if (PTR_DAT_80435a30[0x40] == *(char *)(iVar4 + 0x12)) {
    *(float *)(PTR_DAT_80435a30 + *(char *)(param_1 + 0x12) * 8 + 0x54) = local_88;
    *(float *)(PTR_DAT_80435a30 + *(char *)(param_1 + 0x12) * 8 + 0x58) = local_80;
  }
  iVar4 = *(char *)(param_1 + 0x13) + -1;
  iVar6 = iVar4 * 0x24;
  iVar5 = param_1 + iVar4 * 4;
  for (; -1 < iVar4; iVar4 = iVar4 + -1) {
    pfVar3 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
    if (-1 < *(short *)(pfVar3 + 8)) {
      if (iVar4 == 2) {
        zz_00455fc_(afStack_4c,afStack_7c,(float *)(param_1 + 0x9c));
        iVar2 = (int)*(short *)(param_1 + 0x74);
        zz_00457d4_('y',afStack_7c,afStack_7c,*(short *)(param_1 + 0x74));
      }
      else {
        zz_00455fc_((float *)(param_1 + 0x114),afStack_7c,pfVar3);
      }
      if (2 < iVar4) {
        dVar8 = (double)local_70;
        local_88 = local_70;
        iVar2 = 1;
        local_84 = local_60;
        local_80 = local_50;
        zz_00484e8_(afStack_7c,&local_88,&DAT_802b0ca8,1);
      }
      pfVar1 = pfVar3 + 3;
      uVar7 = zz_00456a0_(afStack_7c,afStack_7c,pfVar1);
      zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),afStack_7c,
                  (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
      zz_00097b4_(*(int *)(iVar5 + 0xe0),(int)*(short *)((int)pfVar3 + 0x22));
    }
    iVar6 = iVar6 + -0x24;
    iVar5 = iVar5 + -4;
  }
  return;
}



// ==== 801c2ae4  FUN_801c2ae4 ====

void FUN_801c2ae4(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 extraout_r4;
  float *pfVar5;
  double dVar6;
  undefined8 uVar7;
  double dVar8;
  
  fVar4 = FLOAT_8043bbe4;
  fVar3 = FLOAT_8043bbc4;
  pfVar5 = (float *)0xab;
  dVar8 = (double)FLOAT_8043bbc4;
  dVar6 = (double)FLOAT_8043bbe4;
  *(float *)(param_9 + 0xd4) = FLOAT_8043bbcc;
  fVar2 = FLOAT_8043bb80;
  cVar1 = PTR_DAT_80435a30[0x52];
  *(short *)(param_9 + 0x1e) = (short)cVar1;
  *(short *)(param_9 + 0x1c) = (short)cVar1;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x20) = fVar3;
  *(float *)(param_9 + 0x24) = fVar4;
  *(float *)(param_9 + 0x28) = fVar2;
  uVar7 = zz_0006fb4_(dVar6,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                      *(int *)(param_9 + 0xe0),0xab,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 3;
  zz_01c2b70_(uVar7,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,pfVar5
              ,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801c2b70  zz_01c2b70_ ====

void zz_01c2b70_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  uint uVar2;
  uint uVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  float *pfVar4;
  undefined *puVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  undefined8 uVar11;
  double dVar12;
  
  iVar8 = *(int *)(param_9 + 0x8c);
  *(short *)(param_9 + 0x70) = *(short *)(param_9 + 0x70) + 0x800;
  dVar10 = zz_0045204_(*(short *)(param_9 + 0x70));
  dVar9 = (double)FLOAT_8043bba4;
  dVar10 = (double)(float)(dVar10 * (double)FLOAT_8043bbdc + (double)FLOAT_8043bbdc);
  if ((dVar10 <= dVar9) && (dVar9 = dVar10, dVar10 < (double)FLOAT_8043bb80)) {
    dVar9 = (double)FLOAT_8043bb80;
  }
  uVar11 = zz_00086b8_(dVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                       *(int *)(param_9 + 0xe0),param_11,param_12,param_13,param_14,param_15,
                       param_16);
  uVar11 = zz_0007c30_(uVar11,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                       param_15,param_16);
  zz_0007d40_(uVar11,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4_00,param_11,param_12,param_13,param_14,param_15,param_16);
  if (PTR_DAT_80435a30[0x40] == *(char *)(iVar8 + 0x12)) {
    *(short *)(param_9 + 0x1c) = (short)(char)PTR_DAT_80435a30[0x52];
  }
  if ((*(short *)(param_9 + 0x1c) != *(short *)(param_9 + 0x1e)) && (PTR_DAT_80435a30[0x53] == '\0')
     ) {
    *(short *)(param_9 + 0x1e) = *(short *)(param_9 + 0x1c);
  }
  dVar9 = DOUBLE_8043bb98;
  cVar1 = *(char *)(param_9 + 0x12);
  uVar3 = (int)*(short *)(param_9 + 0x1c) + cVar1 + -3;
  uVar2 = uVar3 / 0x1e;
  if (0x1d < (int)uVar3) {
    do {
      uVar3 = uVar3 - 0x1e;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  uVar2 = (0x1d - uVar3) / 0x1e;
  if ((int)uVar3 < 0) {
    do {
      uVar3 = uVar3 + 0x1e;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  uVar7 = (int)*(short *)(param_9 + 0x1e) + cVar1 + -3;
  uVar2 = uVar7 / 0x1e;
  if (0x1d < (int)uVar7) {
    do {
      uVar7 = uVar7 - 0x1e;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  uVar2 = (0x1d - uVar7) / 0x1e;
  if ((int)uVar7 < 0) {
    do {
      uVar7 = uVar7 + 0x1e;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  puVar5 = &DAT_803852a8;
  pfVar4 = (float *)0x43300000;
  dVar12 = (double)*(float *)(param_9 + 0xd4);
  *(float *)(param_9 + 0xd4) =
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(&DAT_803852aa + cVar1 * 4) ^ 0x80000000)
              - DOUBLE_8043bb98);
  *(undefined2 *)(param_9 + 0x72) = *(undefined2 *)(&DAT_803852a8 + *(char *)(param_9 + 0x12) * 4);
  dVar10 = DOUBLE_8043bb98;
  if (uVar3 != uVar7) {
    iVar6 = uVar3 - uVar7;
    param_4 = (double)((float)((double)CONCAT44(0x43300000,
                                                (int)(char)PTR_DAT_80435a30[0x53] ^ 0x80000000) -
                              dVar9) * FLOAT_8043bbd8);
    if (iVar6 < 0) {
      iVar6 = iVar6 + 0x1e;
    }
    if (0xf < iVar6) {
      param_4 = (double)(float)((double)FLOAT_8043bba4 - param_4);
      uVar3 = uVar7;
    }
    puVar5 = (undefined *)(int)*(short *)(param_9 + 0x72);
    pfVar4 = (float *)&DAT_803852a8;
    *(short *)(param_9 + 0x72) =
         *(short *)(param_9 + 0x72) +
         (short)(int)(param_4 *
                     (double)(float)((double)CONCAT44(0x43300000,
                                                      (int)*(short *)(&DAT_803852ac +
                                                                     *(char *)(param_9 + 0x12) * 4)
                                                      - (int)puVar5 ^ 0x80000000) - DOUBLE_8043bb98)
                     );
    *(float *)(param_9 + 0xd4) =
         (float)(param_4 * (double)(float)((double)(float)((double)CONCAT44(0x43300000,
                                                                            (int)*(short *)(&
                                                  DAT_803852ae + *(char *)(param_9 + 0x12) * 4) ^
                                                  0x80000000) - dVar10) -
                                          (double)*(float *)(param_9 + 0xd4)) +
                (double)*(float *)(param_9 + 0xd4));
    dVar9 = dVar10;
  }
  uVar3 = (int)(char)PTR_DAT_80435a30[0x45] ^ uVar3;
  *(byte *)(param_9 + 0x87) =
       (byte)(((int)uVar3 >> 1) - (uVar3 & (int)(char)PTR_DAT_80435a30[0x45]) >> 0x1f);
  dVar10 = (double)*(float *)(param_9 + 0xd4);
  if (dVar10 != dVar12) {
    iVar6 = *(int *)(param_9 + 0xe0);
    zz_0008614_(dVar10,dVar9,dVar12,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,iVar6,
                pfVar4,puVar5,uVar7,param_14,param_15,param_16);
    uVar11 = zz_0007c30_(dVar10,dVar9,dVar12,param_4,param_5,param_6,param_7,param_8,
                         *(int *)(param_9 + 0xe0),iVar6,pfVar4,puVar5,uVar7,param_14,param_15,
                         param_16);
    zz_0007d18_(uVar11,dVar9,dVar12,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
                ,extraout_r4_01,pfVar4,puVar5,uVar7,param_14,param_15,param_16);
  }
  if ('\x01' < *(char *)(iVar8 + 0x18)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801c2e8c  FUN_801c2e8c ====

void FUN_801c2e8c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float *pfVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar3;
  
  if (*(char *)(param_9 + 0x87) != '\0') {
    zz_00455fc_((float *)(*(int *)(param_9 + 0x8c) + 0x114),(float *)(param_9 + 0x114),
                (float *)(param_9 + 0x20));
    pfVar1 = (float *)(param_9 + 0x114);
    iVar2 = (int)*(short *)(param_9 + 0x72);
    uVar3 = zz_00457d4_('y',pfVar1,pfVar1,*(short *)(param_9 + 0x72));
    zz_00076d0_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),(undefined *)pfVar1,iVar2,in_r7,
                in_r8,in_r9,in_r10);
    zz_00097b4_(*(int *)(param_9 + 0xe0),1);
  }
  return;
}



// ==== 801c2f00  FUN_801c2f00 ====

/* WARNING: Removing unreachable block (ram,0x801c300c) */
/* WARNING: Removing unreachable block (ram,0x801c3004) */
/* WARNING: Removing unreachable block (ram,0x801c2f18) */
/* WARNING: Removing unreachable block (ram,0x801c2f10) */

void FUN_801c2f00(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  int iVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  
  iVar3 = 0;
  do {
    zz_01c147c_(param_9,6,(char)iVar3);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x19);
  iVar3 = 0;
  do {
    zz_01c147c_(param_9,10,(char)iVar3);
    iVar3 = iVar3 + 1;
  } while (iVar3 < 0x19);
  pfVar2 = (float *)0x0;
  uVar7 = zz_01c147c_(param_9,8,0);
  dVar8 = (double)FLOAT_8043bb80;
  psVar5 = &DAT_803852d8;
  *(float *)(param_9 + 0xd4) = FLOAT_8043bb80;
  dVar9 = (double)FLOAT_8043bbe8;
  iVar6 = 0;
  uVar1 = extraout_r4;
  iVar3 = param_9;
  for (iVar4 = 0; iVar4 < *(char *)(param_9 + 0x13); iVar4 = iVar4 + 1) {
    pfVar2 = (float *)(*(int *)(param_9 + 0x54) + iVar6);
    if (iVar4 == 1) {
      *pfVar2 = (float)dVar8;
      pfVar2[1] = (float)dVar8;
      pfVar2[2] = (float)dVar9;
    }
    *(short *)(pfVar2 + 8) = psVar5[1];
    pfVar2 = (float *)(int)*psVar5;
    uVar7 = zz_0006fb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                        *(int *)(iVar3 + 0xe0),(int)pfVar2,param_12,param_13,param_14,param_15,
                        param_16);
    iVar6 = iVar6 + 0x24;
    psVar5 = psVar5 + 2;
    iVar3 = iVar3 + 4;
    uVar1 = extraout_r4_00;
  }
  *(undefined1 *)(param_9 + 0x82) = 1;
  FUN_801c3028(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar1,pfVar2,
               param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801c3028  FUN_801c3028 ====

void FUN_801c3028(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  double dVar3;
  undefined8 uVar4;
  double dVar5;
  
  fVar1 = FLOAT_8043bb80;
  dVar3 = (double)FLOAT_8043bbec;
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(PTR_DAT_80435a30 + 0x48);
  fVar2 = FLOAT_8043bbf0;
  *(float *)(param_9 + 0x24) = fVar1;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(PTR_DAT_80435a30 + 0x4c);
  dVar5 = (double)*(float *)(param_9 + 0xd4);
  *(float *)(param_9 + 0xd4) = (float)(dVar5 + dVar3);
  if (fVar2 <= (float)(dVar5 + dVar3)) {
    *(float *)(param_9 + 0xd4) = *(float *)(param_9 + 0xd4) - fVar2;
  }
  uVar4 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),dVar5,param_3,param_4,param_5,param_6,
                      param_7,param_8,DAT_803bb32c,*(int *)(param_9 + 0xe4),param_11,param_12,
                      param_13,param_14,param_15,param_16);
  zz_0007c30_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4),
              extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801c30bc  FUN_801c30bc ====

void FUN_801c30bc(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  dVar6 = (double)*(float *)(param_1 + 0x24);
  dVar7 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar6,dVar7,(float *)(param_1 + 0x114));
  iVar4 = 0;
  iVar3 = param_1;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
    if (iVar2 == 1) {
      dVar6 = (double)pfVar1[1];
      dVar7 = (double)pfVar1[2];
      uVar5 = gnt4_PSMTXTrans_bl((double)*pfVar1,dVar6,dVar7,afStack_48);
    }
    else {
      uVar5 = gnt4_PSMTXCopy_bl((float *)(param_1 + 0x114),afStack_48);
    }
    zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_48,
                param_3,param_4,param_5,param_6,param_7,param_8);
    zz_00097b4_(*(int *)(iVar3 + 0xe0),(int)*(short *)(pfVar1 + 8));
    iVar4 = iVar4 + 0x24;
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 801c3170  FUN_801c3170 ====

void FUN_801c3170(int param_1,undefined4 param_2,int param_3,int param_4)

{
  float fVar1;
  float fVar2;
  short sVar3;
  float fVar4;
  double dVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  undefined4 *puVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  double in_f8;
  
  fVar6 = FLOAT_8043bc08;
  fVar1 = FLOAT_8043bc00;
  dVar5 = DOUBLE_8043bb98;
  fVar4 = FLOAT_8043bb80;
  iVar9 = 0;
  iVar7 = 0x66660000;
  iVar10 = 0;
  dVar17 = (double)FLOAT_8043bbf8;
  dVar15 = (double)FLOAT_8043bb80;
  dVar14 = (double)FLOAT_8043bc04;
  dVar16 = (double)(float)(dVar17 * (double)(float)((double)CONCAT44(0x43300000,
                                                                     (int)*(char *)(param_1 + 0x12)
                                                                     ^ 0x80000000) - DOUBLE_8043bb98
                                                   ) + (double)FLOAT_8043bbf4);
  fVar2 = (float)(dVar16 - (double)FLOAT_8043bbfc);
  dVar13 = (double)fVar2;
  *(float *)(param_1 + 0x20) = fVar2;
  *(float *)(param_1 + 0x28) = fVar1;
  for (uVar11 = 0; (int)uVar11 < (int)*(char *)(param_1 + 0x13); uVar11 = uVar11 + 1) {
    puVar12 = (undefined4 *)(*(int *)(param_1 + 0x54) + iVar9);
    iVar9 = iVar9 + 0x24;
    *(undefined2 *)(puVar12 + 8) = 0xffff;
    iVar7 = (int)*(char *)(param_1 + 0x12);
    dVar13 = (double)(float)((double)CONCAT44(0x43300000,uVar11 ^ 0x80000000) - dVar5);
    iVar8 = iVar7 / 5 + (iVar7 >> 0x1f);
    param_4 = -(iVar8 >> 0x1f);
    param_3 = iVar8 + param_4;
    iVar7 = iVar7 + param_3 * -5;
    sVar3 = (short)iVar10;
    iVar10 = iVar10 + 5;
    *(short *)((int)puVar12 + 0x22) =
         (short)iVar7 + ((short)iVar8 - (short)(iVar8 >> 0x1f)) * 0x28 + sVar3;
    *puVar12 = *(undefined4 *)(param_1 + 0x20);
    puVar12[1] = fVar4;
    fVar1 = (float)(dVar14 + (double)(float)(dVar17 * dVar13 + (double)*(float *)(param_1 + 0x28)));
    puVar12[2] = fVar1;
    puVar12[3] = fVar6;
    puVar12[4] = fVar6;
    puVar12[5] = fVar6;
  }
  *(undefined1 *)(param_1 + 0x82) = 2;
  FUN_801c32ac((double)fVar1,dVar13,dVar14,dVar15,dVar16,dVar5,dVar17,in_f8,param_1,iVar7,param_3,
               param_4,0x66666667,0x43300000,iVar9,iVar10);
  return;
}



// ==== 801c32ac  FUN_801c32ac ====

void FUN_801c32ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  char local_28;
  byte bStack_27;
  
  iVar5 = 0;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    iVar2 = *(int *)(param_9 + 0x54) + iVar5;
    sVar1 = *(short *)(*(int *)(PTR_DAT_80435a30 + 0x24) + *(short *)(iVar2 + 0x22) * 0x20 + 0x870);
    if ((*(short *)(iVar2 + 0x20) != sVar1) && (*(short *)(iVar2 + 0x20) = sVar1, -1 < sVar1)) {
      local_28 = (char)((ushort)sVar1 >> 8);
      bStack_27 = (byte)sVar1;
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb334,
                  *(int *)(iVar4 + 0xe0),
                  *(int *)((&PTR_DAT_80350d0c)[local_28] + (uint)bStack_27 * 4),param_12,param_13,
                  param_14,param_15,param_16);
      param_1 = zz_0007d8c_(*(int *)(iVar4 + 0xe0),7);
    }
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
  }
  return;
}



// ==== 801c3384  FUN_801c3384 ====

void FUN_801c3384(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  double dVar10;
  float afStack_58 [3];
  float afStack_4c [13];
  
  dVar10 = (double)*(float *)(param_9 + 0x20);
  iVar6 = *(int *)(param_9 + 0x8c);
  fVar1 = (float)(dVar10 + (double)*(float *)(PTR_DAT_80435a30 + 0x48));
  if (fVar1 < FLOAT_8043bb80) {
    fVar1 = -fVar1;
  }
  if (fVar1 <= FLOAT_8043bb8c) {
    iVar8 = 0;
    iVar7 = param_9;
    for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
      pfVar4 = (float *)(*(int *)(param_9 + 0x54) + iVar8);
      iVar3 = *(int *)(PTR_DAT_80435a30 + 0x24) + *(short *)((int)pfVar4 + 0x22) * 0x20 + 0x870;
      if (-1 < *(short *)(pfVar4 + 8)) {
        if (((int)*(short *)((int)pfVar4 + 0x22) != (int)*(short *)(PTR_DAT_80435a30 + 0x144)) &&
           ((*(uint *)(iVar3 + 0x10) & 1 << (int)(char)PTR_DAT_80435a30[0x40]) == 0)) {
          gnt4_PSMTXMultVec_bl((float *)(iVar6 + 0x114),pfVar4,afStack_58);
          uVar2 = 1;
          zz_00484e8_(afStack_4c,afStack_58,&DAT_802b0ca8,1);
          pfVar4 = pfVar4 + 3;
          uVar9 = zz_00456a0_(afStack_4c,afStack_4c,pfVar4);
          zz_00076d0_(uVar9,dVar10,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0xe0),afStack_4c,(undefined *)pfVar4,uVar2,iVar3,in_r8,in_r9,
                      in_r10);
          zz_00097b4_(*(int *)(iVar7 + 0xe0),0x44);
        }
      }
      iVar8 = iVar8 + 0x24;
      iVar7 = iVar7 + 4;
    }
  }
  return;
}



// ==== 801c34b0  FUN_801c34b0 ====

void FUN_801c34b0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 *in_r10;
  
  uVar3 = 0x80380000;
  iVar4 = 0;
  puVar5 = &DAT_803852e4;
  *(undefined2 *)(param_9 + 0x1c) = 0xffff;
  *(undefined2 *)(param_9 + 0x1e) = 0;
  for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    in_r10 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar4);
    iVar4 = iVar4 + 0x24;
    *(undefined2 *)(in_r10 + 8) = 0xffff;
    *(undefined2 *)((int)in_r10 + 0x22) = 4;
    uVar3 = *puVar5;
    in_r10[5] = uVar3;
    in_r10[4] = uVar3;
    in_r10[3] = uVar3;
    uVar3 = puVar5[1];
    uVar2 = puVar5[2];
    *in_r10 = uVar3;
    in_r10[1] = uVar2;
    puVar1 = puVar5 + 3;
    puVar5 = puVar5 + 4;
    in_r10[2] = *puVar1;
  }
  *(undefined1 *)(param_9 + 0x82) = 4;
  FUN_801c3550(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar3,4,
               0xffffffff,iVar4,puVar5,iVar6,in_r10);
  return;
}



// ==== 801c3550  FUN_801c3550 ====

/* WARNING: Removing unreachable block (ram,0x801c3704) */
/* WARNING: Removing unreachable block (ram,0x801c3560) */

void FUN_801c3550(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  undefined4 extraout_r4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  undefined8 uVar11;
  double dVar12;
  char local_38;
  byte bStack_37;
  
  fVar3 = FLOAT_8043bc0c;
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(PTR_DAT_80435a30 + 0x30);
  fVar2 = FLOAT_8043bb80;
  if (-1 < *(short *)(PTR_DAT_80435a30 + 0x144)) {
    fVar2 = FLOAT_8043bba0;
  }
  *(float *)(param_9 + 0x24) = fVar3 + fVar2;
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(PTR_DAT_80435a30 + 0x34);
  *(short *)(param_9 + 0x1e) = *(short *)(param_9 + 0x1e) + 0x800;
  dVar10 = zz_0045204_(*(short *)(param_9 + 0x1e));
  dVar12 = (double)FLOAT_8043bba4;
  dVar9 = (double)(float)(dVar10 * (double)FLOAT_8043bbdc + (double)FLOAT_8043bbdc);
  if ((dVar9 <= dVar12) && (dVar12 = dVar9, dVar9 < (double)FLOAT_8043bb80)) {
    dVar12 = (double)FLOAT_8043bb80;
  }
  iVar8 = 0;
  iVar7 = param_9;
  for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    pfVar5 = (float *)(*(int *)(param_9 + 0x54) + iVar8);
    if (iVar6 == 0) {
      iVar4 = (int)*(short *)((int)pfVar5 + 0x22) +
              ((uint)(int)*(short *)(PTR_DAT_80435a30 + 0x144) >> 0x1f ^ 1);
      if (iVar4 != *(short *)(pfVar5 + 8)) {
        *(short *)(pfVar5 + 8) = (short)iVar4;
        pfVar5 = (float *)(int)*(short *)(pfVar5 + 8);
        zz_0006fb4_(dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                    *(int *)(iVar7 + 0xe0),(int)pfVar5,param_12,param_13,param_14,param_15,param_16)
        ;
      }
      uVar11 = zz_00086b8_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_803bb32c,*(int *)(iVar7 + 0xe0),pfVar5,param_12,param_13,param_14,
                           param_15,param_16);
      dVar10 = (double)zz_0007c30_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   *(int *)(iVar7 + 0xe0),extraout_r4,pfVar5,param_12,param_13,
                                   param_14,param_15,param_16);
    }
    else if (((-1 < *(short *)(PTR_DAT_80435a30 + 0x144)) &&
             (sVar1 = *(short *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                                *(short *)(PTR_DAT_80435a30 + 0x144) * 0x20 + 0x870),
             *(short *)(pfVar5 + 8) != sVar1)) && (*(short *)(pfVar5 + 8) = sVar1, -1 < sVar1)) {
      local_38 = (char)((ushort)sVar1 >> 8);
      bStack_37 = (byte)sVar1;
      dVar10 = (double)zz_0006fb4_(dVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   DAT_803bb334,*(int *)(iVar7 + 0xe0),
                                   *(int *)((&PTR_DAT_80350d0c)[local_38] + (uint)bStack_37 * 4),
                                   param_12,param_13,param_14,param_15,param_16);
    }
    iVar8 = iVar8 + 0x24;
    iVar7 = iVar7 + 4;
  }
  return;
}



// ==== 801c3720  FUN_801c3720 ====

void FUN_801c3720(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  float afStack_4c [14];
  
  dVar6 = (double)*(float *)(param_1 + 0x24);
  dVar7 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar6,dVar7,(float *)(param_1 + 0x114));
  iVar4 = 0;
  iVar3 = param_1;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
    if (iVar2 == 0) {
      uVar5 = zz_00455fc_((float *)(param_1 + 0x114),afStack_4c,pfVar1);
      zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_4c,
                  (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),1);
    }
    else if (-1 < *(short *)(PTR_DAT_80435a30 + 0x144)) {
      local_58 = *(float *)(param_1 + 0x120);
      param_4 = 1;
      local_54 = *(undefined4 *)(param_1 + 0x130);
      local_50 = *(undefined4 *)(param_1 + 0x140);
      zz_00484e8_(afStack_4c,&local_58,&DAT_802b0ca8,1);
      zz_00456a0_(afStack_4c,afStack_4c,pfVar1 + 3);
      uVar5 = zz_00455fc_(afStack_4c,afStack_4c,pfVar1);
      zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_4c,
                  (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
    }
    iVar4 = iVar4 + 0x24;
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 801c383c  FUN_801c383c ====

/* WARNING: Removing unreachable block (ram,0x801c38dc) */
/* WARNING: Removing unreachable block (ram,0x801c38d4) */
/* WARNING: Removing unreachable block (ram,0x801c3854) */
/* WARNING: Removing unreachable block (ram,0x801c384c) */

void FUN_801c383c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  
  dVar5 = (double)FLOAT_8043bb80;
  dVar6 = (double)FLOAT_8043bc10;
  *(float *)(param_9 + 0xd4) = FLOAT_8043bb80;
  iVar4 = 0;
  iVar3 = param_9;
  for (iVar2 = 0; iVar2 < *(char *)(param_9 + 0x13); iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar4);
    *pfVar1 = (float)dVar5;
    pfVar1[1] = (float)dVar5;
    pfVar1[2] = (float)dVar6;
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb32c,*(int *)(iVar3 + 0xe0),0x7c,param_12,param_13,param_14,
                          param_15,param_16);
    iVar4 = iVar4 + 0x24;
    iVar3 = iVar3 + 4;
  }
  *(undefined1 *)(param_9 + 0x82) = 2;
  FUN_801c38f8(param_9);
  return;
}



// ==== 801c38f8  FUN_801c38f8 ====

void FUN_801c38f8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  undefined4 extraout_r4;
  float *pfVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar8;
  undefined8 uVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  
  fVar2 = FLOAT_8043bba8;
  dVar16 = DOUBLE_8043bb98;
  fVar1 = FLOAT_8043bb80;
  dVar17 = (double)FLOAT_8043bbf8;
  dVar11 = (double)FLOAT_8043bc14;
  iVar7 = (int)*(short *)(PTR_DAT_80435a30 + 0x50);
  pfVar5 = (float *)0x66666667;
  uVar6 = (undefined4)((ulonglong)((longlong)iVar7 * 0x66666667) >> 0x20);
  dVar10 = (double)FLOAT_8043bc18;
  dVar8 = (double)FLOAT_8043bba4;
  iVar4 = iVar7 / 5 + (iVar7 >> 0x1f);
  iVar3 = iVar7 / 0x28 + (iVar7 >> 0x1f);
  dVar15 = (double)(float)((double)CONCAT44(0x43300000,
                                            iVar7 + (iVar4 - (iVar4 >> 0x1f)) * -5 +
                                            (iVar3 - (iVar3 >> 0x1f)) * 5 ^ 0x80000000) -
                          DOUBLE_8043bb98);
  dVar14 = (double)(float)(dVar17 * dVar15 + (double)FLOAT_8043bbf4);
  dVar13 = (double)(float)(dVar14 - (double)FLOAT_8043bbfc);
  *(float *)(param_1 + 0x20) = (float)(dVar14 - (double)FLOAT_8043bbfc);
  *(float *)(param_1 + 0x24) = fVar1;
  iVar4 = (int)*(short *)(PTR_DAT_80435a30 + 0x50);
  iVar3 = iVar4 / 0x28 + (iVar4 >> 0x1f);
  iVar4 = iVar4 + (iVar3 - (iVar3 >> 0x1f)) * -0x28;
  iVar3 = iVar4 / 5 + (iVar4 >> 0x1f);
  dVar12 = (double)(float)((double)CONCAT44(0x43300000,iVar3 - (iVar3 >> 0x1f) ^ 0x80000000) -
                          dVar16);
  dVar11 = (double)(float)(dVar17 * dVar12 + dVar11);
  *(float *)(param_1 + 0x28) = (float)(dVar11 - dVar10);
  dVar10 = (double)*(float *)(param_1 + 0xd4);
  *(float *)(param_1 + 0xd4) = (float)(dVar10 + dVar8);
  while (fVar2 <= *(float *)(param_1 + 0xd4)) {
    *(float *)(param_1 + 0xd4) = *(float *)(param_1 + 0xd4) - fVar2;
  }
  iVar3 = param_1;
  for (iVar4 = 0; iVar4 < *(char *)(param_1 + 0x13); iVar4 = iVar4 + 1) {
    uVar9 = zz_00086b8_((double)*(float *)(param_1 + 0xd4),dVar10,dVar11,dVar12,dVar13,dVar14,dVar15
                        ,dVar16,DAT_803bb32c,*(int *)(iVar3 + 0xe0),pfVar5,uVar6,iVar7,in_r8,in_r9,
                        in_r10);
    zz_0007c30_(uVar9,dVar10,dVar11,dVar12,dVar13,dVar14,dVar15,dVar16,*(int *)(iVar3 + 0xe0),
                extraout_r4,pfVar5,uVar6,iVar7,in_r8,in_r9,in_r10);
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 801c3a80  FUN_801c3a80 ====

void FUN_801c3a80(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  undefined2 local_58;
  undefined2 local_56;
  undefined4 local_54;
  float local_50;
  float local_4c;
  float local_48;
  float afStack_44 [13];
  
  if (-1 < *(short *)(PTR_DAT_80435a30 + 0x50)) {
    zz_00455fc_((float *)(*(int *)(param_9 + 0x8c) + 0x114),(float *)(param_9 + 0x114),
                (float *)(param_9 + 0x20));
    iVar2 = 0;
    iVar4 = 0;
    iVar3 = param_9;
    while( true ) {
      if (*(char *)(param_9 + 0x13) <= iVar2) break;
      pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar4);
      uVar5 = zz_00455fc_((float *)(param_9 + 0x114),afStack_44,pfVar1);
      zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar3 + 0xe0),afStack_44,(undefined *)pfVar1,param_12,param_13,param_14,
                  param_15,param_16);
      zz_00097b4_(*(int *)(iVar3 + 0xe0),0x44);
      iVar4 = iVar4 + 0x24;
      iVar3 = iVar3 + 4;
      iVar2 = iVar2 + 1;
    }
  }
  if (PTR_DAT_80435a30[0x44] != '\0') {
    DAT_803c1140 = &local_50;
    DAT_803c1150 = &local_54;
    DAT_803c1154 = &local_58;
    DAT_803c1144 = 0;
    DAT_803c1164 = 3;
    DAT_803c1168 = 0xf;
    DAT_803c1170 = 1;
    local_50 = FLOAT_8043bb80;
    local_4c = FLOAT_8043bb80;
    local_48 = FLOAT_8043bba4;
    local_54 = 0x4c;
    local_58 = 0x280;
    local_56 = 0x1c0;
    FUN_80051998(-0x7fc3eed0);
  }
  return;
}



// ==== 801c3bbc  FUN_801c3bbc ====

void FUN_801c3bbc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 extraout_r4;
  int iVar5;
  short *psVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  
  fVar1 = FLOAT_8043bbcc;
  *(undefined4 *)(param_9 + 0xd4) = 0xffffffff;
  *(float *)(param_9 + 0xd8) = fVar1;
  iVar3 = *(char *)(param_9 + 0x12) * 0xc;
  uVar2 = *(undefined4 *)(&DAT_80385488 + iVar3);
  *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(&DAT_80385484 + iVar3);
  *(undefined4 *)(param_9 + 0x3c) = uVar2;
  *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(&DAT_8038548c + iVar3);
  if (*(int *)(PTR_DAT_80433934 + 0x120) < 0) {
    *(float *)(param_9 + 0x3c) = *(float *)(param_9 + 0x3c) - FLOAT_8043bc1c;
  }
  iVar5 = *(int *)(param_9 + 0x38);
  iVar9 = 0;
  uVar2 = 0x80380000;
  dVar10 = (double)FLOAT_8043bc20;
  *(int *)(param_9 + 100) = iVar5;
  iVar8 = 0;
  *(undefined4 *)(param_9 + 0x68) = *(undefined4 *)(param_9 + 0x3c);
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(param_9 + 0x40);
  dVar11 = (double)*(float *)(param_9 + 100);
  *(float *)(param_9 + 100) = (float)(dVar11 + dVar10);
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 100);
  *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x68);
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x6c);
  iVar3 = param_9;
  for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
    puVar4 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar9);
    psVar6 = (short *)(&DAT_80385304 + iVar8 + *(char *)(param_9 + 0x12) * 0x80);
    *(short *)(puVar4 + 8) = psVar6[1];
    uVar2 = *(undefined4 *)(psVar6 + 4);
    *puVar4 = *(undefined4 *)(psVar6 + 2);
    puVar4[1] = uVar2;
    puVar4[2] = *(undefined4 *)(psVar6 + 6);
    iVar5 = (int)*psVar6;
    dVar11 = (double)zz_0006fb4_(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 DAT_803bb32c,*(int *)(iVar3 + 0xe0),iVar5,param_12,param_13,
                                 param_14,param_15,param_16);
    iVar9 = iVar9 + 0x24;
    iVar8 = iVar8 + 0x10;
    iVar3 = iVar3 + 4;
    uVar2 = extraout_r4;
  }
  *(undefined1 *)(param_9 + 0x82) = 4;
  FUN_801c3d24(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar2,iVar5,
               param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801c3d24  FUN_801c3d24 ====

/* WARNING: Removing unreachable block (ram,0x801c3ffc) */
/* WARNING: Removing unreachable block (ram,0x801c3d34) */

void FUN_801c3d24(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  bool bVar3;
  float *pfVar4;
  int iVar5;
  size_t sVar6;
  int iVar7;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  uint uVar8;
  uint unaff_r29;
  int iVar9;
  int iVar10;
  int iVar11;
  double dVar12;
  undefined8 uVar13;
  double dVar14;
  char acStack_49 [9];
  float local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_30;
  uint uStack_2c;
  
  iVar10 = *(int *)(param_9 + 0x8c);
  iVar5 = (int)*(char *)(iVar10 + 0x12);
  iVar11 = *(int *)(PTR_DAT_80435a30 + 0x24) + iVar5 * 0x6c;
  if ((PTR_DAT_80435a30[0x43] == '\0') && (iVar5 == (char)PTR_DAT_80435a30[0x40])) {
    local_40 = *(float *)(param_9 + 0x38);
    local_3c = *(undefined4 *)(param_9 + 0x3c);
    local_38 = *(undefined4 *)(param_9 + 0x40);
  }
  else {
    local_40 = *(float *)(param_9 + 100);
    local_3c = *(undefined4 *)(param_9 + 0x68);
    local_38 = *(undefined4 *)(param_9 + 0x6c);
  }
  gnt4_PSVECSubtract_bl(&local_40,(float *)(param_9 + 0x20),&local_40);
  dVar12 = gnt4_PSVECMag_bl(&local_40);
  if ((double)FLOAT_8043bc24 < dVar12) {
    gnt4_PSVECNormalize_bl(&local_40,&local_40);
    gnt4_PSQUATScale_bl((double)FLOAT_8043bc24,&local_40,&local_40);
  }
  gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_40,(float *)(param_9 + 0x20));
  dVar12 = DOUBLE_8043bb98;
  cVar1 = *(char *)(param_9 + 0x12);
  iVar5 = *(int *)(param_9 + 0xd4);
  uVar8 = *(uint *)(PTR_DAT_80433934 + 0x120);
  dVar14 = (double)*(float *)(param_9 + 0xd8);
  if (cVar1 == '\0') {
    unaff_r29 = *(uint *)(iVar11 + 0x2c);
    bVar3 = false;
    if (((int)uVar8 < 0) || ((int)unaff_r29 <= (int)uVar8)) {
      bVar3 = true;
    }
    fVar2 = FLOAT_8043bba4;
    if (bVar3) {
      fVar2 = FLOAT_8043bb80;
    }
    *(float *)(param_9 + 0xd8) = fVar2;
  }
  else if (cVar1 == '\x01') {
    *(float *)(param_9 + 0xd8) = FLOAT_8043bb80;
    unaff_r29 = uVar8;
  }
  else if (cVar1 == '\x02') {
    local_30 = 0x43300000;
    unaff_r29 = uVar8 - *(int *)(iVar11 + 0x2c);
    uStack_2c = unaff_r29 ^ 0x80000000;
    fVar2 = FLOAT_8043bba4;
    if (FLOAT_8043bb80 <= (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_8043bb98)) {
      fVar2 = FLOAT_8043bb80;
    }
    *(float *)(param_9 + 0xd8) = fVar2;
    param_2 = dVar12;
  }
  pfVar4 = (float *)0xf423f;
  *(uint *)(param_9 + 0xd4) = ((int)unaff_r29 >> 0x1f ^ unaff_r29) - ((int)unaff_r29 >> 0x1f);
  if ((int)*(float **)(param_9 + 0xd4) < 999999) {
    pfVar4 = *(float **)(param_9 + 0xd4);
  }
  sprintf(acStack_49 + 1,&DAT_8043bb90);
  sVar6 = strlen(acStack_49 + 1);
  *(char *)(param_9 + 0x13) = (char)sVar6 + '\x02';
  iVar11 = param_9;
  for (iVar9 = 0; iVar9 < *(char *)(param_9 + 0x13); iVar9 = iVar9 + 1) {
    if (iVar9 < 2) {
      if (((double)*(float *)(param_9 + 0xd8) != dVar14) &&
         ((iVar9 == 1 || (*(char *)(param_9 + 0x12) == '\x02')))) {
        uVar13 = zz_00086b8_((double)*(float *)(param_9 + 0xd8),param_2,param_3,param_4,param_5,
                             param_6,param_7,param_8,DAT_803bb32c,*(int *)(iVar11 + 0xe0),pfVar4,
                             param_12,param_13,param_14,param_15,param_16);
        zz_0007c30_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar11 + 0xe0),extraout_r4,pfVar4,param_12,param_13,param_14,param_15,
                    param_16);
      }
    }
    else if (*(int *)(param_9 + 0xd4) != iVar5) {
      iVar7 = (int)acStack_49[*(char *)(param_9 + 0x13) - iVar9];
      fVar2 = FLOAT_8043bb80;
      if ((0x2f < iVar7) && (iVar7 < 0x3a)) {
        uStack_2c = iVar7 - 0x30U ^ 0x80000000;
        local_30 = 0x43300000;
        fVar2 = (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_8043bb98);
      }
      dVar14 = (double)fVar2;
      uVar13 = zz_00086b8_(dVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                           DAT_803bb32c,*(int *)(iVar11 + 0xe0),pfVar4,param_12,param_13,param_14,
                           param_15,param_16);
      zz_0007c30_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar11 + 0xe0),extraout_r4_00,pfVar4,param_12,param_13,param_14,param_15,
                  param_16);
    }
    iVar11 = iVar11 + 4;
  }
  if ('\x01' < *(char *)(iVar10 + 0x18)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801c4018  FUN_801c4018 ====

void FUN_801c4018(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float *pfVar1;
  uint uVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  float afStack_48 [13];
  
  uVar2 = (uint)(byte)PTR_DAT_80433930[0x28];
  zz_00455fc_((float *)(&DAT_803c7714 + (char)PTR_DAT_80433930[0x28] * 0x3e4),
              (float *)(param_9 + 0x114),(float *)(param_9 + 0x20));
  iVar6 = 0;
  iVar5 = param_9;
  for (iVar4 = 0; iVar4 < *(char *)(param_9 + 0x13); iVar4 = iVar4 + 1) {
    pfVar3 = (float *)(*(int *)(param_9 + 0x54) + iVar6);
    pfVar1 = pfVar3;
    uVar7 = zz_00455fc_((float *)(param_9 + 0x114),afStack_48,pfVar3);
    zz_00076d0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar5 + 0xe0)
                ,afStack_48,(undefined *)pfVar1,uVar2,in_r7,in_r8,in_r9,in_r10);
    zz_00097b4_(*(int *)(iVar5 + 0xe0),(int)*(short *)(pfVar3 + 8));
    iVar6 = iVar6 + 0x24;
    iVar5 = iVar5 + 4;
  }
  return;
}



// ==== 801c40c8  FUN_801c40c8 ====

/* WARNING: Removing unreachable block (ram,0x801c423c) */
/* WARNING: Removing unreachable block (ram,0x801c4234) */
/* WARNING: Removing unreachable block (ram,0x801c422c) */
/* WARNING: Removing unreachable block (ram,0x801c4224) */
/* WARNING: Removing unreachable block (ram,0x801c40f0) */
/* WARNING: Removing unreachable block (ram,0x801c40e8) */
/* WARNING: Removing unreachable block (ram,0x801c40e0) */
/* WARNING: Removing unreachable block (ram,0x801c40d8) */

void FUN_801c40c8(int param_1,undefined4 param_2,float *param_3,uint param_4,int param_5,
                 undefined4 *param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  uint uVar4;
  undefined4 extraout_r4;
  uint uVar5;
  int iVar6;
  short sVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  
  fVar2 = FLOAT_8043bc00;
  dVar13 = DOUBLE_8043bb98;
  fVar1 = FLOAT_8043bb80;
  iVar8 = 0;
  uVar3 = 0x66660000;
  sVar7 = 0;
  dVar12 = (double)FLOAT_8043bbf8;
  dVar11 = (double)(float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x12) ^ 0x80000000)
                          - DOUBLE_8043bb98);
  dVar14 = (double)FLOAT_8043bb80;
  dVar10 = (double)(float)(dVar12 * dVar11 + (double)FLOAT_8043bbf4);
  dVar15 = (double)FLOAT_8043bbd4;
  dVar9 = (double)(float)(dVar10 - (double)FLOAT_8043bbfc);
  *(float *)(param_1 + 0x20) = (float)(dVar10 - (double)FLOAT_8043bbfc);
  *(float *)(param_1 + 0x28) = fVar2;
  *(float *)(param_1 + 0xd4) = fVar1;
  iVar6 = param_1;
  for (uVar5 = 0; (int)uVar5 < (int)*(char *)(param_1 + 0x13); uVar5 = uVar5 + 1) {
    param_3 = (float *)0x7b;
    param_5 = (int)*(char *)(param_1 + 0x12);
    param_6 = (undefined4 *)(*(int *)(param_1 + 0x54) + iVar8);
    uVar4 = param_5 / 5 + (param_5 >> 0x1f);
    dVar9 = (double)(float)((double)CONCAT44(0x43300000,uVar5 ^ 0x80000000) - dVar13);
    param_4 = uVar4 >> 0x1f;
    *(short *)(param_6 + 8) =
         (short)*(char *)(param_1 + 0x12) +
         (short)uVar4 * 0x23 + (short)((int)uVar4 >> 0x1f) * -0x23 + sVar7;
    *param_6 = *(undefined4 *)(param_1 + 0x20);
    param_6[1] = (float)dVar14;
    param_6[2] = (float)((double)(float)(dVar12 * dVar9 + (double)*(float *)(param_1 + 0x28)) -
                        dVar15);
    dVar9 = (double)zz_0006fb4_(dVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb32c,
                                *(int *)(iVar6 + 0xe0),0x7b,param_4,param_5,param_6,param_7,param_8)
    ;
    iVar8 = iVar8 + 0x24;
    sVar7 = sVar7 + 5;
    iVar6 = iVar6 + 4;
    uVar3 = extraout_r4;
  }
  *(undefined1 *)(param_1 + 0x82) = 2;
  FUN_801c4258(dVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,param_1,uVar3,param_3,param_4,
               param_5,param_6,param_7,param_8);
  return;
}



// ==== 801c4258  FUN_801c4258 ====

void FUN_801c4258(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  short *psVar2;
  undefined4 extraout_r4;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  
  fVar1 = FLOAT_8043bba8;
  dVar7 = (double)*(float *)(param_9 + 0xd4);
  *(float *)(param_9 + 0xd4) = (float)(dVar7 + (double)FLOAT_8043bba4);
  while (fVar1 <= *(float *)(param_9 + 0xd4)) {
    *(float *)(param_9 + 0xd4) = *(float *)(param_9 + 0xd4) - fVar1;
  }
  iVar5 = 0;
  iVar4 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    psVar2 = (short *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                      *(short *)(*(int *)(param_9 + 0x54) + iVar5 + 0x20) * 0x20 + 0x870);
    if ((-1 < *psVar2) && (*(char *)(psVar2 + 6) != '\0')) {
      uVar6 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),dVar7,param_3,param_4,param_5,param_6,
                          param_7,param_8,DAT_803bb32c,*(int *)(iVar4 + 0xe0),param_11,param_12,
                          param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar4 + 0xe0)
                  ,extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
    }
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
  }
  return;
}



// ==== 801c4350  FUN_801c4350 ====

void FUN_801c4350(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  short *psVar2;
  float *pfVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  double dVar9;
  float afStack_48 [14];
  
  dVar9 = (double)*(float *)(param_9 + 0x20);
  fVar1 = (float)(dVar9 + (double)*(float *)(PTR_DAT_80435a30 + 0x48));
  if (fVar1 < FLOAT_8043bb80) {
    fVar1 = -fVar1;
  }
  if (fVar1 <= FLOAT_8043bb8c) {
    iVar7 = 0;
    iVar6 = param_9;
    for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
      pfVar3 = (float *)(*(int *)(param_9 + 0x54) + iVar7);
      iVar4 = (int)*(short *)(pfVar3 + 8);
      psVar2 = (short *)(*(int *)(PTR_DAT_80435a30 + 0x24) + iVar4 * 0x20 + 0x870);
      if (iVar4 != *(short *)(PTR_DAT_80435a30 + 0x144)) {
        if ((-1 < *psVar2) && (*(char *)(psVar2 + 6) != '\0')) {
          uVar8 = zz_00455fc_((float *)(*(int *)(param_9 + 0x8c) + 0x114),afStack_48,pfVar3);
          zz_00076d0_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0xe0),afStack_48,(undefined *)pfVar3,iVar4,in_r7,in_r8,in_r9,
                      in_r10);
          zz_00097b4_(*(int *)(iVar6 + 0xe0),0x44);
        }
      }
      iVar7 = iVar7 + 0x24;
      iVar6 = iVar6 + 4;
    }
  }
  return;
}



// ==== 801c4458  FUN_801c4458 ====

void FUN_801c4458(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  double dVar1;
  int iVar2;
  float fVar3;
  size_t sVar4;
  int iVar5;
  undefined4 extraout_r4;
  float *pfVar6;
  char *pcVar7;
  int iVar8;
  short *psVar9;
  int iVar10;
  undefined8 uVar11;
  char local_39 [9];
  undefined4 local_30;
  uint uStack_2c;
  
  iVar2 = *(char *)(param_9 + 0x12) + 1;
  iVar8 = 0x1e;
  if (iVar2 < 0x1e) {
    iVar8 = iVar2;
  }
  sprintf(local_39 + 1,&DAT_8043bb90,iVar8);
  sVar4 = strlen(local_39 + 1);
  iVar10 = 0;
  psVar9 = &DAT_803854a8;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  pcVar7 = local_39;
  iVar8 = param_9;
  for (iVar2 = 0; pcVar7 = pcVar7 + 1, iVar2 < *(char *)(param_9 + 0x13); iVar2 = iVar2 + 1) {
    pfVar6 = (float *)(*(int *)(param_9 + 0x54) + iVar10);
    *(short *)(pfVar6 + 8) = psVar9[1];
    fVar3 = *(float *)(psVar9 + 4);
    *pfVar6 = *(float *)(psVar9 + 2);
    pfVar6[1] = fVar3;
    pfVar6[2] = *(float *)(psVar9 + 6);
    param_1 = (double)zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                  DAT_803bb32c,*(int *)(iVar8 + 0xe0),(int)*psVar9,param_12,param_13
                                  ,param_14,param_15,param_16);
    if (iVar2 == 0) {
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | 1;
    }
    else {
      if (sVar4 == 1) {
        param_1 = (double)*pfVar6;
        *pfVar6 = (float)(param_1 + (double)FLOAT_8043bc28);
      }
      dVar1 = DOUBLE_8043bb98;
      if (((iVar2 + -1 < (int)sVar4) && (iVar5 = (int)pcVar7[-1], 0x2f < iVar5)) && (iVar5 < 0x3a))
      {
        uStack_2c = iVar5 - 0x30U ^ 0x80000000;
        pfVar6 = (float *)(int)(short)*(ushort *)(param_9 + 0x1c);
        local_30 = 0x43300000;
        *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar2);
        uVar11 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_2c) - dVar1),param_2
                             ,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                             *(int *)(iVar8 + 0xe0),pfVar6,param_12,param_13,param_14,param_15,
                             param_16);
        param_1 = (double)zz_0007c30_(uVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                                      ,*(int *)(iVar8 + 0xe0),extraout_r4,pfVar6,param_12,param_13,
                                      param_14,param_15,param_16);
      }
    }
    iVar10 = iVar10 + 0x24;
    psVar9 = psVar9 + 8;
    iVar8 = iVar8 + 4;
  }
  *(undefined1 *)(param_9 + 0x82) = 2;
  FUN_801c45f8(param_9);
  return;
}



// ==== 801c45f8  FUN_801c45f8 ====

void FUN_801c45f8(int param_1)

{
  short sVar1;
  float fVar2;
  double dVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  ushort uVar11;
  int iVar10;
  
  sVar1 = *(short *)(*(int *)(PTR_DAT_80435a30 + 0x24) +
                    (char)PTR_DAT_80435a30[0x40] * 0x6c + 0x30 + *(char *)(param_1 + 0x12) * 2);
  iVar7 = (int)sVar1;
  uVar11 = (ushort)(sVar1 >> 0xf) >> 0xf ^ 1;
  *(ushort *)(param_1 + 0x1e) = uVar11;
  dVar3 = DOUBLE_8043bb98;
  if (uVar11 != 0) {
    iVar10 = iVar7 / 5 + (iVar7 >> 0x1f);
    iVar9 = iVar7 / 0x28 + (iVar7 >> 0x1f);
    *(ushort *)(param_1 + 0x1e) =
         (ushort)(*(short *)(*(int *)(PTR_DAT_80435a30 + 0x24) + iVar7 * 0x20 + 0x870) >> 0xf) >>
         0xf ^ 1;
    fVar6 = FLOAT_8043bc18;
    fVar5 = FLOAT_8043bc14;
    fVar4 = FLOAT_8043bbf8;
    fVar2 = FLOAT_8043bb80;
    iVar8 = iVar7 + (iVar9 - (iVar9 >> 0x1f)) * -0x28;
    iVar8 = iVar8 / 5 + (iVar8 >> 0x1f);
    *(float *)(param_1 + 0x20) =
         (FLOAT_8043bbf4 +
         FLOAT_8043bbf8 *
         (float)((double)CONCAT44(0x43300000,
                                  iVar7 + (iVar10 - (iVar10 >> 0x1f)) * -5 +
                                  (iVar9 - (iVar9 >> 0x1f)) * 5 ^ 0x80000000) - dVar3) +
         *(float *)(PTR_DAT_80435a30 + 0x48)) - FLOAT_8043bbfc;
    *(float *)(param_1 + 0x24) = fVar2;
    *(float *)(param_1 + 0x28) =
         (fVar5 + fVar4 * (float)((double)CONCAT44(0x43300000,iVar8 - (iVar8 >> 0x1f) ^ 0x80000000)
                                 - dVar3) + *(float *)(PTR_DAT_80435a30 + 0x4c)) - fVar6;
  }
  return;
}



// ==== 801c4738  FUN_801c4738 ====

void FUN_801c4738(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [12];
  
  if ((*(short *)(param_1 + 0x1c) != 0) && (*(short *)(param_1 + 0x1e) != 0)) {
    dVar7 = (double)*(float *)(param_1 + 0x24);
    dVar8 = (double)*(float *)(param_1 + 0x28);
    gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar7,dVar8,(float *)(param_1 + 0x114));
    iVar3 = 0;
    iVar5 = 0;
    iVar4 = param_1;
    while( true ) {
      if (*(char *)(param_1 + 0x13) <= iVar3) break;
      if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar3) != 0) {
        pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar5);
        pfVar1 = pfVar2;
        uVar6 = zz_00455fc_((float *)(param_1 + 0x114),afStack_48,pfVar2);
        zz_00076d0_(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar4 + 0xe0),
                    afStack_48,(undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
        zz_00097b4_(*(int *)(iVar4 + 0xe0),(int)*(short *)(pfVar2 + 8));
      }
      iVar5 = iVar5 + 0x24;
      iVar4 = iVar4 + 4;
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



// ==== 801c47fc  FUN_801c47fc ====

void FUN_801c47fc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 *puVar2;
  float *pfVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined8 uVar9;
  
  *(undefined2 *)(param_9 + 0x1c) = 0;
  zz_01c14bc_(param_9,0xd,0,param_9 + 0xd4);
  iVar4 = param_9 + 0xd8;
  uVar9 = zz_01c14bc_(param_9,0xd,1,iVar4);
  puVar7 = &DAT_803854d8;
  iVar8 = 0;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    uVar1 = puVar7[2];
    puVar2 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar8);
    *puVar2 = puVar7[1];
    puVar2[1] = uVar1;
    puVar2[2] = puVar7[3];
    uVar1 = *puVar7;
    *(short *)(puVar2 + 8) = (short)uVar1;
    if (-1 < (short)uVar1) {
      pfVar3 = (float *)(int)*(short *)(puVar2 + 8);
      zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb32c,
                  *(int *)(iVar6 + 0xe0),(int)pfVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
      uVar9 = zz_00086b8_((double)FLOAT_8043bb80,param_2,param_3,param_4,param_5,param_6,param_7,
                          param_8,DAT_803bb32c,*(int *)(iVar6 + 0xe0),pfVar3,iVar4,in_r7,in_r8,in_r9
                          ,in_r10);
      uVar9 = zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar6 + 0xe0),extraout_r4,pfVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
      uVar9 = zz_0007d40_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar6 + 0xe0),extraout_r4_00,pfVar3,iVar4,in_r7,in_r8,in_r9,
                          in_r10);
    }
    iVar8 = iVar8 + 0x24;
    puVar7 = puVar7 + 4;
    iVar6 = iVar6 + 4;
  }
  *(undefined1 *)(param_9 + 0x82) = 4;
  zz_01c4908_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



