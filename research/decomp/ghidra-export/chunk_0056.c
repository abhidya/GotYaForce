// ==== 801cc0a4  zz_01cc0a4_ ====

void zz_01cc0a4_(int param_1,int param_2,int param_3)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  ushort uVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  int iVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined4 uVar17;
  int iVar18;
  
  iVar3 = param_2 * 0x20;
  iVar2 = param_1 + iVar3;
  iVar10 = param_1 + param_3 * 0x20;
  uVar12 = *(undefined4 *)(iVar2 + 0x870);
  uVar14 = *(undefined4 *)(iVar2 + 0x874);
  uVar15 = *(undefined4 *)(iVar2 + 0x878);
  uVar16 = *(undefined4 *)(iVar2 + 0x87c);
  uVar17 = *(undefined4 *)(iVar2 + 0x880);
  uVar8 = *(undefined4 *)(iVar2 + 0x884);
  uVar6 = *(undefined4 *)(iVar2 + 0x888);
  uVar5 = *(undefined4 *)(iVar2 + 0x88c);
  uVar1 = *(undefined4 *)(iVar10 + 0x874);
  *(undefined4 *)(iVar2 + 0x870) = *(undefined4 *)(iVar10 + 0x870);
  *(undefined4 *)(iVar2 + 0x874) = uVar1;
  uVar1 = *(undefined4 *)(iVar10 + 0x87c);
  *(undefined4 *)(iVar2 + 0x878) = *(undefined4 *)(iVar10 + 0x878);
  *(undefined4 *)(iVar2 + 0x87c) = uVar1;
  uVar1 = *(undefined4 *)(iVar10 + 0x884);
  *(undefined4 *)(iVar2 + 0x880) = *(undefined4 *)(iVar10 + 0x880);
  *(undefined4 *)(iVar2 + 0x884) = uVar1;
  uVar1 = *(undefined4 *)(iVar10 + 0x88c);
  *(undefined4 *)(iVar2 + 0x888) = *(undefined4 *)(iVar10 + 0x888);
  *(undefined4 *)(iVar2 + 0x88c) = uVar1;
  *(undefined4 *)(iVar10 + 0x870) = uVar12;
  *(undefined4 *)(iVar10 + 0x874) = uVar14;
  *(undefined4 *)(iVar10 + 0x878) = uVar15;
  *(undefined4 *)(iVar10 + 0x87c) = uVar16;
  *(undefined4 *)(iVar10 + 0x880) = uVar17;
  *(undefined4 *)(iVar10 + 0x884) = uVar8;
  *(undefined4 *)(iVar10 + 0x888) = uVar6;
  *(undefined4 *)(iVar10 + 0x88c) = uVar5;
  if (-1 < *(short *)(iVar10 + 0x870)) {
    if (*(int *)(iVar10 + 0x880) != 0) {
      uVar9 = (ushort)param_3 | 0x8000;
      iVar7 = param_3 * 0x20 + 0x880;
      iVar11 = 0;
      iVar18 = 10;
      iVar10 = param_1;
      do {
        if ((*(uint *)(param_1 + iVar7) & 1 << iVar11) != 0) {
          iVar13 = 0;
          while( true ) {
            if (0x1d < iVar13) break;
            iVar4 = iVar13 * 2 + 0x30;
            if (param_2 == *(short *)(iVar10 + iVar4)) {
              *(ushort *)(iVar10 + iVar4) = uVar9;
              iVar13 = 0x1e;
            }
            iVar13 = iVar13 + 1;
          }
        }
        if ((*(uint *)(param_1 + iVar7) & 1 << iVar11 + 1) != 0) {
          iVar13 = 0;
          while( true ) {
            if (0x1d < iVar13) break;
            iVar4 = iVar13 * 2 + 0x30;
            if (param_2 == *(short *)(iVar10 + 0x6c + iVar4)) {
              *(ushort *)(iVar10 + 0x6c + iVar4) = uVar9;
              iVar13 = 0x1e;
            }
            iVar13 = iVar13 + 1;
          }
        }
        iVar10 = iVar10 + 0xd8;
        iVar11 = iVar11 + 2;
        iVar18 = iVar18 + -1;
      } while (iVar18 != 0);
    }
  }
  if (-1 < *(short *)(iVar2 + 0x870)) {
    if (*(int *)(param_1 + iVar3 + 0x880) != 0) {
      uVar9 = (ushort)param_2 | 0x8000;
      iVar10 = 0;
      iVar7 = 10;
      iVar2 = param_1;
      do {
        if ((*(uint *)(param_1 + iVar3 + 0x880) & 1 << iVar10) != 0) {
          iVar11 = 0;
          while( true ) {
            if (0x1d < iVar11) break;
            iVar18 = iVar11 * 2 + 0x30;
            if (param_3 == *(short *)(iVar2 + iVar18)) {
              *(ushort *)(iVar2 + iVar18) = uVar9;
              iVar11 = 0x1e;
            }
            iVar11 = iVar11 + 1;
          }
        }
        if ((*(uint *)(param_1 + iVar3 + 0x880) & 1 << iVar10 + 1) != 0) {
          iVar11 = 0;
          while( true ) {
            if (0x1d < iVar11) break;
            iVar18 = iVar11 * 2 + 0x30;
            if (param_3 == *(short *)(iVar2 + 0x6c + iVar18)) {
              *(ushort *)(iVar2 + 0x6c + iVar18) = uVar9;
              iVar11 = 0x1e;
            }
            iVar11 = iVar11 + 1;
          }
        }
        iVar2 = iVar2 + 0xd8;
        iVar10 = iVar10 + 2;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
    }
  }
  iVar3 = 0;
  do {
    iVar10 = 5;
    iVar2 = param_1;
    do {
      uVar9 = *(ushort *)(iVar2 + 0x30);
      if (((int)(short)uVar9 & 0x8000U) != 0) {
        if ((int)(short)uVar9 != 0xffffffff) {
          *(ushort *)(iVar2 + 0x30) = uVar9 & 0x7fff;
        }
      }
      uVar9 = *(ushort *)(iVar2 + 0x32);
      if (((int)(short)uVar9 & 0x8000U) != 0) {
        if ((int)(short)uVar9 != 0xffffffff) {
          *(ushort *)(iVar2 + 0x32) = uVar9 & 0x7fff;
        }
      }
      uVar9 = *(ushort *)(iVar2 + 0x34);
      if (((int)(short)uVar9 & 0x8000U) != 0) {
        if ((int)(short)uVar9 != 0xffffffff) {
          *(ushort *)(iVar2 + 0x34) = uVar9 & 0x7fff;
        }
      }
      uVar9 = *(ushort *)(iVar2 + 0x36);
      if (((int)(short)uVar9 & 0x8000U) != 0) {
        if ((int)(short)uVar9 != 0xffffffff) {
          *(ushort *)(iVar2 + 0x36) = uVar9 & 0x7fff;
        }
      }
      uVar9 = *(ushort *)(iVar2 + 0x38);
      if (((int)(short)uVar9 & 0x8000U) != 0) {
        if ((int)(short)uVar9 != 0xffffffff) {
          *(ushort *)(iVar2 + 0x38) = uVar9 & 0x7fff;
        }
      }
      uVar9 = *(ushort *)(iVar2 + 0x3a);
      if (((int)(short)uVar9 & 0x8000U) != 0) {
        if ((int)(short)uVar9 != 0xffffffff) {
          *(ushort *)(iVar2 + 0x3a) = uVar9 & 0x7fff;
        }
      }
      iVar2 = iVar2 + 0xc;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    iVar3 = iVar3 + 1;
    param_1 = param_1 + 0x6c;
  } while (iVar3 < 0x14);
  return;
}



// ==== 801cc3d4  zz_01cc3d4_ ====

void zz_01cc3d4_(int param_1,int param_2)

{
  short *psVar1;
  
  psVar1 = (short *)(param_1 + param_2 * 0x10);
  if (*psVar1 < 0) {
    return;
  }
  *(undefined1 *)(psVar1 + 6) = 0;
  return;
}



// ==== 801cc3f4  zz_01cc3f4_ ====

void zz_01cc3f4_(int param_1,int param_2)

{
  int *piVar1;
  
  piVar1 = (int *)(param_1 + param_2 * 0xc + 32000);
  if (*piVar1 < 0) {
    return;
  }
  *(undefined1 *)(piVar1 + 2) = 0;
  return;
}



// ==== 801cc418  zz_01cc418_ ====

void zz_01cc418_(int param_1,int param_2)

{
  short *psVar1;
  
  psVar1 = (short *)(param_1 + param_2 * 0x20 + 0x870);
  if (*psVar1 < 0) {
    return;
  }
  *(undefined1 *)(psVar1 + 6) = 0;
  return;
}



// ==== 801cc43c  zz_01cc43c_ ====

void zz_01cc43c_(int param_1,short *param_2,int param_3)

{
  short *psVar1;
  int iVar2;
  
  iVar2 = 0x28;
  do {
    if (-1 < *(short *)(param_3 + 0x870)) {
      if ((*(int *)(param_3 + 0x874) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(param_3 + 0x87c) != '\0')) {
        *(undefined1 *)(param_3 + 0x87c) = 0;
      }
    }
    if (-1 < *(short *)(param_3 + 0x890)) {
      if ((*(int *)(param_3 + 0x894) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(param_3 + 0x89c) != '\0')) {
        *(undefined1 *)(param_3 + 0x89c) = 0;
      }
    }
    if (-1 < *(short *)(param_3 + 0x8b0)) {
      if ((*(int *)(param_3 + 0x8b4) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(param_3 + 0x8bc) != '\0')) {
        *(undefined1 *)(param_3 + 0x8bc) = 0;
      }
    }
    if (-1 < *(short *)(param_3 + 0x8d0)) {
      if ((*(int *)(param_3 + 0x8d4) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(param_3 + 0x8dc) != '\0')) {
        *(undefined1 *)(param_3 + 0x8dc) = 0;
      }
    }
    if (-1 < *(short *)(param_3 + 0x8f0)) {
      if ((*(int *)(param_3 + 0x8f4) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(param_3 + 0x8fc) != '\0')) {
        *(undefined1 *)(param_3 + 0x8fc) = 0;
      }
    }
    param_3 = param_3 + 0xa0;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  iVar2 = 400;
  psVar1 = param_2;
  do {
    if (-1 < *psVar1) {
      if ((*(int *)(psVar1 + 2) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(psVar1 + 6) != '\0')) {
        *(undefined1 *)(psVar1 + 6) = 0;
      }
    }
    if (-1 < psVar1[8]) {
      if ((*(int *)(psVar1 + 10) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(psVar1 + 0xe) != '\0')) {
        *(undefined1 *)(psVar1 + 0xe) = 0;
      }
    }
    if (-1 < psVar1[0x10]) {
      if ((*(int *)(psVar1 + 0x12) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(psVar1 + 0x16) != '\0')) {
        *(undefined1 *)(psVar1 + 0x16) = 0;
      }
    }
    if (-1 < psVar1[0x18]) {
      if ((*(int *)(psVar1 + 0x1a) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(psVar1 + 0x1e) != '\0')) {
        *(undefined1 *)(psVar1 + 0x1e) = 0;
      }
    }
    if (-1 < psVar1[0x20]) {
      if ((*(int *)(psVar1 + 0x22) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(psVar1 + 0x26) != '\0')) {
        *(undefined1 *)(psVar1 + 0x26) = 0;
      }
    }
    psVar1 = psVar1 + 0x28;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  iVar2 = 200;
  do {
    if (-1 < *(int *)(param_2 + 16000)) {
      if ((*(int *)(param_2 + 0x3e82) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(param_2 + 0x3e84) != '\0')) {
        *(undefined1 *)(param_2 + 0x3e84) = 0;
      }
    }
    if (-1 < *(int *)(param_2 + 0x3e86)) {
      if ((*(int *)(param_2 + 0x3e88) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(param_2 + 0x3e8a) != '\0')) {
        *(undefined1 *)(param_2 + 0x3e8a) = 0;
      }
    }
    if (-1 < *(int *)(param_2 + 0x3e8c)) {
      if ((*(int *)(param_2 + 0x3e8e) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(param_2 + 0x3e90) != '\0')) {
        *(undefined1 *)(param_2 + 0x3e90) = 0;
      }
    }
    if (-1 < *(int *)(param_2 + 0x3e92)) {
      if ((*(int *)(param_2 + 0x3e94) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(param_2 + 0x3e96) != '\0')) {
        *(undefined1 *)(param_2 + 0x3e96) = 0;
      }
    }
    if (-1 < *(int *)(param_2 + 0x3e98)) {
      if ((*(int *)(param_2 + 0x3e9a) < *(int *)(param_1 + 0x50) + -0x32) &&
         (*(char *)(param_2 + 0x3e9c) != '\0')) {
        *(undefined1 *)(param_2 + 0x3e9c) = 0;
      }
    }
    param_2 = param_2 + 0x1e;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}



// ==== 801cc768  zz_01cc768_ ====

int zz_01cc768_(int param_1)

{
  int iVar1;
  int iVar2;
  
  *(undefined2 *)(param_1 + 0x2170) = 0;
  iVar1 = 0x14;
  iVar2 = param_1;
  do {
    if (*(char *)(iVar2 + 0x29) != '\0') {
      *(short *)(param_1 + 0x2170) = *(short *)(param_1 + 0x2170) + 1;
    }
    iVar2 = iVar2 + 0x6c;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  return (int)*(short *)(param_1 + 0x2170);
}



// ==== 801cc7b4  zz_01cc7b4_ ====

int zz_01cc7b4_(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar4 = 0;
  iVar3 = -1;
  iVar5 = param_1 + param_2 * 0x6c;
  iVar6 = param_1;
  while ((iVar4 < 0x14 && (iVar3 < 0))) {
    if ((iVar4 != param_2) && (*(char *)(iVar6 + 0x29) == '\0')) {
      uVar1 = 1 << iVar4;
      iVar7 = 6;
      iVar3 = iVar5;
      do {
        if ((-1 < *(short *)(iVar3 + 0x30)) &&
           (iVar2 = param_1 + *(short *)(iVar3 + 0x30) * 0x20, -1 < *(short *)(iVar2 + 0x870))) {
          *(uint *)(iVar2 + 0x880) = *(uint *)(iVar2 + 0x880) | uVar1;
        }
        if ((-1 < *(short *)(iVar3 + 0x32)) &&
           (iVar2 = param_1 + *(short *)(iVar3 + 0x32) * 0x20, -1 < *(short *)(iVar2 + 0x870))) {
          *(uint *)(iVar2 + 0x880) = *(uint *)(iVar2 + 0x880) | uVar1;
        }
        if ((-1 < *(short *)(iVar3 + 0x34)) &&
           (iVar2 = param_1 + *(short *)(iVar3 + 0x34) * 0x20, -1 < *(short *)(iVar2 + 0x870))) {
          *(uint *)(iVar2 + 0x880) = *(uint *)(iVar2 + 0x880) | uVar1;
        }
        if ((-1 < *(short *)(iVar3 + 0x36)) &&
           (iVar2 = param_1 + *(short *)(iVar3 + 0x36) * 0x20, -1 < *(short *)(iVar2 + 0x870))) {
          *(uint *)(iVar2 + 0x880) = *(uint *)(iVar2 + 0x880) | uVar1;
        }
        if ((-1 < *(short *)(iVar3 + 0x38)) &&
           (iVar2 = param_1 + *(short *)(iVar3 + 0x38) * 0x20, -1 < *(short *)(iVar2 + 0x870))) {
          *(uint *)(iVar2 + 0x880) = *(uint *)(iVar2 + 0x880) | uVar1;
        }
        iVar3 = iVar3 + 10;
        iVar7 = iVar7 + -1;
      } while (iVar7 != 0);
      *(undefined1 *)(iVar6 + 0x29) = *(undefined1 *)(iVar5 + 0x29);
      *(undefined4 *)(iVar6 + 0x2c) = *(undefined4 *)(iVar5 + 0x2c);
      gnt4_memcpy((void *)(iVar6 + 0x30),(void *)(iVar5 + 0x30),0x3c);
      *(short *)(param_1 + 0x2170) = *(short *)(param_1 + 0x2170) + 1;
      iVar3 = iVar4;
    }
    iVar6 = iVar6 + 0x6c;
    iVar4 = iVar4 + 1;
  }
  zz_01cc768_(param_1);
  return iVar3;
}



// ==== 801cc960  zz_01cc960_ ====

void zz_01cc960_(int param_1,int param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = param_1 + param_2 * 0x6c;
  if (*(char *)(iVar4 + 0x29) != '\0') {
    uVar2 = ~(1 << param_2);
    iVar5 = 6;
    iVar1 = iVar4;
    do {
      if ((-1 < *(short *)(iVar1 + 0x30)) &&
         (iVar3 = param_1 + *(short *)(iVar1 + 0x30) * 0x20, -1 < *(short *)(iVar3 + 0x870))) {
        *(uint *)(iVar3 + 0x880) = *(uint *)(iVar3 + 0x880) & uVar2;
      }
      *(undefined2 *)(iVar1 + 0x30) = 0xffff;
      if ((-1 < *(short *)(iVar1 + 0x32)) &&
         (iVar3 = param_1 + *(short *)(iVar1 + 0x32) * 0x20, -1 < *(short *)(iVar3 + 0x870))) {
        *(uint *)(iVar3 + 0x880) = *(uint *)(iVar3 + 0x880) & uVar2;
      }
      *(undefined2 *)(iVar1 + 0x32) = 0xffff;
      if ((-1 < *(short *)(iVar1 + 0x34)) &&
         (iVar3 = param_1 + *(short *)(iVar1 + 0x34) * 0x20, -1 < *(short *)(iVar3 + 0x870))) {
        *(uint *)(iVar3 + 0x880) = *(uint *)(iVar3 + 0x880) & uVar2;
      }
      *(undefined2 *)(iVar1 + 0x34) = 0xffff;
      if ((-1 < *(short *)(iVar1 + 0x36)) &&
         (iVar3 = param_1 + *(short *)(iVar1 + 0x36) * 0x20, -1 < *(short *)(iVar3 + 0x870))) {
        *(uint *)(iVar3 + 0x880) = *(uint *)(iVar3 + 0x880) & uVar2;
      }
      *(undefined2 *)(iVar1 + 0x36) = 0xffff;
      if ((-1 < *(short *)(iVar1 + 0x38)) &&
         (iVar3 = param_1 + *(short *)(iVar1 + 0x38) * 0x20, -1 < *(short *)(iVar3 + 0x870))) {
        *(uint *)(iVar3 + 0x880) = *(uint *)(iVar3 + 0x880) & uVar2;
      }
      *(undefined2 *)(iVar1 + 0x38) = 0xffff;
      iVar1 = iVar1 + 10;
      iVar5 = iVar5 + -1;
    } while (iVar5 != 0);
    *(short *)(param_1 + 0x2170) = *(short *)(param_1 + 0x2170) + -1;
  }
  *(undefined1 *)(iVar4 + 0x29) = 0;
  *(undefined4 *)(iVar4 + 0x2c) = 0;
  zz_01cc768_(param_1);
  return;
}



// ==== 801ccac8  zz_01ccac8_ ====

void zz_01ccac8_(int param_1,int param_2)

{
  gnt4_memset((void *)(param_1 + param_2 * 0x6c),0,0x29);
  return;
}



// ==== 801ccaf8  zz_01ccaf8_ ====

void zz_01ccaf8_(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  
  if ((-1 < param_4) &&
     (iVar1 = param_1 + param_2 * 0x6c + param_3 * 2, *(short *)(iVar1 + 0x30) < 0)) {
    *(short *)(iVar1 + 0x30) = (short)param_4;
    iVar1 = param_1 + (short)param_4 * 0x20;
    *(uint *)(iVar1 + 0x880) = *(uint *)(iVar1 + 0x880) | 1 << param_2;
  }
  zz_01ccd2c_(param_1,param_2);
  zz_01ccd94_(param_1,param_2);
  zz_01cc768_(param_1);
  return;
}



// ==== 801ccb94  zz_01ccb94_ ====

void zz_01ccb94_(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_2 * 0x6c + 0x30 + param_3 * 2;
  iVar1 = param_1 + *(short *)(param_1 + iVar2) * 0x20;
  *(uint *)(iVar1 + 0x880) = *(uint *)(iVar1 + 0x880) & ~(1 << param_2);
  *(undefined2 *)(param_1 + iVar2) = 0xffff;
  zz_01ccd2c_(param_1,param_2);
  zz_01ccd94_(param_1,param_2);
  zz_01cc768_(param_1);
  return;
}



// ==== 801ccc1c  zz_01ccc1c_ ====

int zz_01ccc1c_(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = -1;
  if (-1 < param_4) {
    iVar3 = param_1 + param_2 * 0x6c + param_3 * 2;
    iVar4 = (int)*(short *)(iVar3 + 0x30);
    iVar2 = param_1 + iVar4 * 0x20;
    iVar1 = param_1 + (short)param_4 * 0x20;
    *(uint *)(iVar2 + 0x880) = *(uint *)(iVar2 + 0x880) & ~(1 << param_2);
    *(short *)(iVar3 + 0x30) = (short)param_4;
    *(uint *)(iVar1 + 0x880) = *(uint *)(iVar1 + 0x880) | 1 << param_2;
  }
  zz_01ccd2c_(param_1,param_2);
  zz_01ccd94_(param_1,param_2);
  return iVar4;
}



// ==== 801ccccc  zz_01ccccc_ ====

/* WARNING: Removing unreachable block (ram,0x801cccf4) */

void zz_01ccccc_(int param_1,int param_2)

{
  short sVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar6 = 0;
  iVar5 = 0;
  iVar3 = param_1 + param_2 * 0x6c;
  iVar2 = 0x1e;
  iVar4 = iVar3;
  do {
    sVar1 = *(short *)(iVar3 + 0x30);
    if (-1 < sVar1) {
      if (iVar5 != iVar6) {
        *(undefined2 *)(iVar3 + 0x30) = 0xffff;
        *(short *)(iVar4 + 0x30) = sVar1;
      }
      iVar4 = iVar4 + 2;
      iVar6 = iVar6 + 1;
    }
    iVar3 = iVar3 + 2;
    iVar5 = iVar5 + 1;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return;
}



// ==== 801ccd2c  zz_01ccd2c_ ====

int zz_01ccd2c_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  char cVar4;
  
  cVar4 = '\0';
  iVar3 = param_1 + param_2 * 0x6c;
  iVar1 = 0x1e;
  iVar2 = iVar3;
  do {
    if (-1 < *(short *)(iVar2 + 0x30)) {
      if (*(short *)(param_1 + *(short *)(iVar2 + 0x30) * 0x20 + 0x870) < 0) {
        *(undefined2 *)(iVar2 + 0x30) = 0xffff;
      }
      else {
        cVar4 = cVar4 + '\x01';
      }
    }
    iVar2 = iVar2 + 2;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  *(char *)(iVar3 + 0x29) = cVar4;
  return (int)cVar4;
}



// ==== 801ccd94  zz_01ccd94_ ====

int zz_01ccd94_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  short local_28 [2];
  short local_24;
  
  iVar2 = 0;
  iVar4 = param_1 + param_2 * 0x6c;
  iVar5 = iVar4;
  for (iVar3 = 0; iVar3 < 0x1e; iVar3 = iVar3 + 1) {
    if (-1 < *(short *)(iVar5 + 0x30)) {
      iVar1 = param_1 + *(short *)(iVar5 + 0x30) * 0x20;
      local_28[0] = *(short *)(iVar1 + 0x870);
      if (local_28[0] < 0) {
        *(undefined2 *)(iVar5 + 0x30) = 0xffff;
      }
      else {
        local_24 = local_28[0];
        iVar1 = zz_0066168_((char *)local_28,(int)*(char *)(iVar1 + 0x872));
        iVar2 = iVar2 + iVar1;
      }
    }
    iVar5 = iVar5 + 2;
  }
  *(int *)(iVar4 + 0x2c) = iVar2;
  return iVar2;
}



// ==== 801cce38  zz_01cce38_ ====

int zz_01cce38_(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  uint uVar2;
  short *psVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  short local_28 [6];
  
  if (param_3 < 1) {
    iVar4 = -1;
  }
  else {
    iVar4 = 0;
    iVar5 = 0;
    for (iVar6 = 0; iVar6 < 0x1e; iVar6 = iVar6 + 1) {
      iVar1 = (int)*(short *)(param_1 + param_2 * 0x6c + iVar6 * 2 + 0x30);
      if ((-1 < iVar1) && (psVar3 = (short *)(param_1 + iVar1 * 0x20 + 0x870), -1 < *psVar3)) {
        local_28[0] = *psVar3;
        uVar2 = zz_0066168_((char *)local_28,(int)*(char *)(psVar3 + 1));
        if (param_4 == 0) {
          iVar5 = iVar5 + uVar2;
        }
        else {
          iVar5 = iVar5 + (int)(uVar2 << 1) / 3 + ((int)(uVar2 << 1 | uVar2 >> 0x1f) >> 0x1f) +
                          ((uVar2 & 0x7fffffff) >> 0x1e);
        }
      }
      if (iVar5 <= param_3) {
        iVar4 = iVar6 + 1;
      }
      if (param_3 <= iVar5) {
        iVar6 = 0x1e;
      }
    }
  }
  return iVar4;
}



// ==== 801ccf24  zz_01ccf24_ ====

uint zz_01ccf24_(int param_1,int param_2,int param_3)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  int iVar4;
  short *psVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  short local_38 [4];
  
  uVar6 = 0;
  iVar8 = 0;
  for (iVar7 = 0; iVar7 < (char)PTR_DAT_80433934[param_2 + 0x5a]; iVar7 = iVar7 + 1) {
    psVar5 = (short *)(PTR_DAT_80433934 + param_2 * 0x348 + iVar8 + 0x1e8);
    iVar3 = *(int *)(psVar5 + 4);
    if (param_3 != 0) {
      iVar3 = iVar3 / 2;
    }
    if (iVar3 != 0) {
      for (iVar4 = 0; iVar4 < 200; iVar4 = iVar4 + 1) {
        psVar2 = (short *)(param_1 + iVar4 * 0x20 + 0x870);
        if (((*(int *)(psVar2 + 2) == *(int *)(psVar5 + 6)) && (*psVar2 == *psVar5)) &&
           (*(char *)(psVar2 + 1) == *(char *)(psVar5 + 1))) {
          iVar4 = 200;
          *(int *)(psVar2 + 4) = *(int *)(psVar2 + 4) + iVar3;
          while( true ) {
            local_38[0] = *psVar2;
            iVar1 = zz_00662f0_((char *)local_38,*(uint *)(psVar2 + 4),
                                (int)*(char *)((int)psVar2 + 3));
            if (iVar1 == 0) break;
            uVar6 = uVar6 | 1 << iVar7;
            *(char *)((int)psVar2 + 3) = *(char *)((int)psVar2 + 3) + '\x01';
          }
        }
      }
    }
    iVar8 = iVar8 + 0x1c;
  }
  return uVar6;
}



// ==== 801cd060  zz_01cd060_ ====

int zz_01cd060_(short *param_1,int param_2,int param_3,int param_4,uint param_5)

{
  int iVar1;
  uint uVar2;
  undefined2 *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  short *psVar8;
  uint uVar9;
  short local_38 [2];
  short local_34;
  
  iVar6 = 0;
  iVar4 = 0;
  iVar5 = (int)*(short *)(&DAT_80435a90 + param_4 * 2);
  psVar8 = param_1;
  for (iVar7 = 0; iVar7 < iVar5; iVar7 = iVar7 + 1) {
    if (param_4 == 0) {
      local_34 = *(short *)(param_2 + 0x870);
    }
    else if (param_4 == 1) {
      local_34 = *psVar8;
    }
    else if (param_4 == 2) {
      local_34 = param_1[16000];
    }
    if (-1 < local_34) {
      local_38[0] = local_34;
      iVar1 = zz_0066298_((char *)local_38);
      if ((param_5 & 1 << iVar1) != 0) {
        *(short *)(param_3 + iVar4) = (short)iVar7;
        iVar6 = iVar6 + 1;
        iVar4 = iVar4 + 2;
      }
    }
    param_2 = param_2 + 0x20;
    psVar8 = psVar8 + 8;
    param_1 = param_1 + 6;
  }
  puVar3 = (undefined2 *)(param_3 + iVar6 * 2);
  uVar2 = iVar5 - iVar6;
  if (iVar6 < iVar5) {
    uVar9 = uVar2 >> 3;
    if (uVar9 != 0) {
      do {
        *puVar3 = 0xffff;
        puVar3[1] = 0xffff;
        puVar3[2] = 0xffff;
        puVar3[3] = 0xffff;
        puVar3[4] = 0xffff;
        puVar3[5] = 0xffff;
        puVar3[6] = 0xffff;
        puVar3[7] = 0xffff;
        puVar3 = puVar3 + 8;
        uVar9 = uVar9 - 1;
      } while (uVar9 != 0);
      uVar2 = uVar2 & 7;
      if (uVar2 == 0) {
        return iVar6;
      }
    }
    do {
      *puVar3 = 0xffff;
      puVar3 = puVar3 + 1;
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
  return iVar6;
}



// ==== 801cd1b4  zz_01cd1b4_ ====

void zz_01cd1b4_(int param_1,int param_2,short *param_3,int param_4,byte *param_5)

{
  short sVar1;
  short sVar2;
  byte *pbVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  uint unaff_r19;
  uint unaff_r21;
  uint unaff_r22;
  int iVar8;
  byte *pbVar9;
  short *psVar10;
  uint unaff_r27;
  short *psVar11;
  uint unaff_r29;
  char acStack_108 [48];
  char acStack_d8 [48];
  char acStack_a8 [48];
  char acStack_78 [52];
  
  iVar6 = 0;
  sVar2 = *(short *)(&DAT_80435a98 + param_4 * 2);
  for (psVar10 = param_3; (iVar6 < sVar2 && (uVar5 = (uint)*psVar10, -1 < *psVar10));
      psVar10 = psVar10 + 1) {
    uVar4 = (uint)*param_5;
    if (uVar4 == 6) {
      zz_01cd534_(param_1,param_2,uVar5,param_4,acStack_78);
    }
    else if (param_4 == 0) {
      unaff_r19 = zz_01cd694_(param_2,uVar5,uVar4);
    }
    else if (param_4 == 1) {
      unaff_r19 = zz_01cd778_(param_1,uVar5,uVar4);
    }
    else if (param_4 == 2) {
      unaff_r19 = zz_01cd858_(param_1,uVar5,uVar4);
    }
    iVar7 = iVar6 + 1;
    for (psVar11 = param_3 + iVar7; (iVar7 < sVar2 && (uVar5 = (uint)*psVar11, -1 < *psVar11));
        psVar11 = psVar11 + 1) {
      uVar4 = (uint)*param_5;
      if (uVar4 == 6) {
        zz_01cd534_(param_1,param_2,uVar5,param_4,acStack_a8);
      }
      else if (param_4 == 0) {
        unaff_r21 = zz_01cd694_(param_2,uVar5,uVar4);
      }
      else if (param_4 == 1) {
        unaff_r21 = zz_01cd778_(param_1,uVar5,uVar4);
      }
      else if (param_4 == 2) {
        unaff_r21 = zz_01cd858_(param_1,uVar5,uVar4);
      }
      if (*param_5 == 6) {
        uVar5 = gnt4_strcmp(acStack_78,acStack_a8);
      }
      else if ((int)unaff_r21 < (int)unaff_r19) {
        uVar5 = 1;
      }
      else {
        uVar5 = -((uint)(unaff_r19 < unaff_r21) - ((int)unaff_r19 >> 0x1f)) -
                ((int)unaff_r21 >> 0x1f);
      }
      uVar4 = uVar5;
      if (param_5[1] == 0) {
        uVar4 = -uVar5 & ~uVar5;
      }
      uVar4 = uVar4 >> 0x1f;
      if (uVar5 == 0) {
        iVar8 = 1;
        uVar4 = 0;
        pbVar3 = param_5;
        while ((pbVar9 = pbVar3 + 2, iVar8 < 4 && (uVar4 == 0))) {
          uVar5 = (uint)*pbVar9;
          if (uVar5 == 6) {
            zz_01cd534_(param_1,param_2,(int)*psVar10,param_4,acStack_d8);
            zz_01cd534_(param_1,param_2,(int)*psVar11,param_4,acStack_108);
          }
          else if (param_4 == 0) {
            unaff_r27 = zz_01cd694_(param_2,(int)*psVar10,uVar5);
            unaff_r29 = zz_01cd694_(param_2,(int)*psVar11,(uint)*pbVar9);
          }
          else if (param_4 == 1) {
            unaff_r27 = zz_01cd778_(param_1,(int)*psVar10,uVar5);
            unaff_r29 = zz_01cd778_(param_1,(int)*psVar11,(uint)*pbVar9);
          }
          else if (param_4 == 2) {
            unaff_r27 = zz_01cd858_(param_1,(int)*psVar10,uVar5);
            unaff_r29 = zz_01cd858_(param_1,(int)*psVar11,(uint)*pbVar9);
          }
          if (*pbVar9 == 6) {
            uVar4 = gnt4_strcmp(acStack_d8,acStack_108);
          }
          else if ((int)unaff_r29 < (int)unaff_r27) {
            uVar4 = 1;
          }
          else {
            uVar4 = -((uint)(unaff_r27 < unaff_r29) - ((int)unaff_r27 >> 0x1f)) -
                    ((int)unaff_r29 >> 0x1f);
          }
          unaff_r22 = (uint)pbVar3[3];
          iVar8 = iVar8 + 1;
          pbVar3 = pbVar9;
        }
        if (unaff_r22 == 0) {
          uVar4 = (-uVar4 & ~uVar4) >> 0x1f;
        }
        else {
          uVar4 = uVar4 >> 0x1f;
        }
      }
      uVar5 = unaff_r19;
      if (uVar4 != 0) {
        sVar1 = *psVar10;
        *psVar10 = *psVar11;
        *psVar11 = sVar1;
        uVar5 = unaff_r21;
        if (*param_5 == 6) {
          strcpy(acStack_78,acStack_a8);
          uVar5 = unaff_r19;
        }
      }
      iVar7 = iVar7 + 1;
      unaff_r19 = uVar5;
    }
    iVar6 = iVar6 + 1;
  }
  return;
}



// ==== 801cd534  zz_01cd534_ ====

void zz_01cd534_(int param_1,int param_2,int param_3,int param_4,char *param_5)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined2 local_24 [2];
  undefined2 local_20;
  undefined4 local_1c;
  
  if (param_4 == 2) {
    local_1c = *(undefined4 *)(param_1 + param_3 * 0xc + 32000);
    strcpy(param_5,&DAT_802b36a8);
    zz_0238c90_((int)param_5,(int)(&PTR_DAT_80390a28)[(char)local_1c]);
    uVar2 = 100;
    local_24[0] = local_1c._0_2_;
    iVar5 = zz_00661d8_((char *)local_24);
    iVar7 = 0;
    do {
      iVar6 = (iVar5 + 1) / (int)uVar2;
      iVar3 = iVar6 / 10 + (iVar6 >> 0x1f);
      zz_0238c90_((int)param_5,(int)(&PTR_DAT_80390a40)[iVar6 + (iVar3 - (iVar3 >> 0x1f)) * -10]);
      iVar7 = iVar7 + 1;
      uVar2 = uVar2 / 10;
    } while (iVar7 < 3);
    zz_0238c90_((int)param_5,(int)(&PTR_DAT_80390a68)[local_1c._2_1_]);
  }
  else {
    if (param_4 == 0) {
      puVar4 = (undefined2 *)(param_2 + param_3 * 0x20 + 0x870);
    }
    else {
      puVar4 = (undefined2 *)(param_1 + param_3 * 0x10);
    }
    uVar1 = *puVar4;
    local_20._0_1_ = (char)((ushort)uVar1 >> 8);
    local_20._1_1_ = (byte)uVar1;
    uVar2 = (uint)(byte)local_20;
    iVar5 = (int)local_20._0_1_;
    local_20 = uVar1;
    strcpy(param_5,*(char **)((&PTR_PTR_803510d8)[iVar5] + uVar2 * 4));
  }
  return;
}



// ==== 801cd694  zz_01cd694_ ====

uint zz_01cd694_(int param_1,uint param_2,int param_3)

{
  int iVar1;
  undefined2 *puVar2;
  undefined2 local_18 [2];
  undefined2 local_14 [2];
  undefined2 local_10 [6];
  
  puVar2 = (undefined2 *)(param_1 + param_2 * 0x20 + 0x870);
  if (param_3 != 0) {
    if (param_3 == 1) {
      local_10[0] = *puVar2;
      iVar1 = zz_00661d8_((char *)local_10);
      param_2 = (int)*(char *)(puVar2 + 1) | iVar1 << 8;
    }
    else if (param_3 == 2) {
      param_2 = *(uint *)(puVar2 + 2);
    }
    else if (param_3 == 3) {
      param_2 = (int)*(char *)((int)puVar2 + 3) << 0x1b | *(uint *)(puVar2 + 4) & 0x7ffffff;
    }
    else if (param_3 == 4) {
      local_14[0] = *puVar2;
      param_2 = zz_0066168_((char *)local_14,(int)*(char *)(puVar2 + 1));
    }
    else if (param_3 == 5) {
      local_18[0] = *puVar2;
      param_2 = zz_00662c0_((char *)local_18,(int)*(char *)(puVar2 + 1));
    }
    else {
      param_2 = 0;
    }
  }
  return param_2;
}



// ==== 801cd778  zz_01cd778_ ====

uint zz_01cd778_(int param_1,uint param_2,int param_3)

{
  int iVar1;
  undefined2 *puVar2;
  undefined2 local_18 [2];
  undefined2 local_14 [2];
  undefined2 local_10 [6];
  
  puVar2 = (undefined2 *)(param_1 + param_2 * 0x10);
  if (param_3 != 0) {
    if (param_3 == 1) {
      local_10[0] = *puVar2;
      iVar1 = zz_00661d8_((char *)local_10);
      param_2 = (int)*(char *)(puVar2 + 1) | iVar1 << 8;
    }
    else if (param_3 == 2) {
      param_2 = *(uint *)(puVar2 + 2);
    }
    else if (param_3 == 3) {
      param_2 = (int)*(char *)((int)puVar2 + 3) << 0x1b | *(uint *)(puVar2 + 4) & 0x7ffffff;
    }
    else if (param_3 == 4) {
      local_14[0] = *puVar2;
      param_2 = zz_0066168_((char *)local_14,(int)*(char *)(puVar2 + 1));
    }
    else if (param_3 == 5) {
      local_18[0] = *puVar2;
      param_2 = zz_00662c0_((char *)local_18,(int)*(char *)(puVar2 + 1));
    }
    else {
      param_2 = 0;
    }
  }
  return param_2;
}



// ==== 801cd858  zz_01cd858_ ====

uint zz_01cd858_(int param_1,uint param_2,int param_3)

{
  int iVar1;
  undefined2 *puVar2;
  undefined2 local_18 [2];
  undefined2 local_14 [2];
  undefined2 local_10;
  
  puVar2 = (undefined2 *)(param_1 + param_2 * 0xc + 32000);
  local_18[0] = *puVar2;
  if (param_3 != 0) {
    local_10 = local_18[0];
    if (param_3 == 1) {
      local_14[0] = local_18[0];
      iVar1 = zz_00661d8_((char *)local_14);
      param_2 = (int)*(char *)(puVar2 + 1) | (int)*(char *)((int)puVar2 + 3) << 8 | iVar1 << 0x10;
    }
    else if (param_3 == 2) {
      param_2 = *(uint *)(puVar2 + 2);
    }
    else if (param_3 == 5) {
      param_2 = zz_00662c0_((char *)local_18,(int)*(char *)((int)puVar2 + 3));
    }
    else {
      param_2 = 0;
    }
  }
  return param_2;
}



// ==== 801cd90c  FUN_801cd90c ====

void FUN_801cd90c(void)

{
  char *pcVar1;
  undefined1 *puVar2;
  
  for (pcVar1 = &DAT_8038a720; -1 < *pcVar1; pcVar1 = pcVar1 + 4) {
    puVar2 = zz_008893c_(2,0x28,1,(int)*(short *)(pcVar1 + 2));
    if (puVar2 != (undefined1 *)0x0) {
      *puVar2 = 1;
      puVar2[0x10] = 0;
      *(code **)(puVar2 + 0xc) = FUN_801cd9a8;
      *(code **)(puVar2 + 0x10c) = FUN_801cdab0;
      *(char **)(puVar2 + 0x54) = pcVar1;
      puVar2[0x11] = *pcVar1;
      puVar2[0x12] = pcVar1[1];
    }
  }
  return;
}



// ==== 801cd9a8  FUN_801cd9a8 ====

void FUN_801cd9a8(int param_1)

{
  (*(code *)(&PTR_FUN_8038a79c)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801cd9e4  FUN_801cd9e4 ====

void FUN_801cd9e4(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(undefined1 *)(param_1 + 0x82) = 1;
  (*(code *)(&PTR_FUN_8038a7ac)[*(char *)(param_1 + 0x11)])();
  zz_01cda40_(param_1);
  return;
}



// ==== 801cda40  zz_01cda40_ ====

void zz_01cda40_(int param_1)

{
  (*(code *)(&PTR_FUN_8038a7b8)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801cda90  FUN_801cda90 ====

void FUN_801cda90(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801cdab0  FUN_801cdab0 ====

void FUN_801cdab0(int param_1)

{
  (*(code *)(&PTR_FUN_8038a7c4)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801cdaec  FUN_801cdaec ====

/* WARNING: Removing unreachable block (ram,0x801cdbc4) */
/* WARNING: Removing unreachable block (ram,0x801cdafc) */

void FUN_801cdaec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  short *psVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  float local_38;
  float local_34;
  float local_30;
  
  *(code **)(param_9 + 0x100) = FUN_801cdcd0;
  uVar6 = zz_0089100_(param_9,1,1);
  dVar7 = (double)FLOAT_8043bd58;
  puVar4 = (undefined4 *)(param_9 + 0x144);
  psVar2 = (short *)(&DAT_8038a760 + *(char *)(param_9 + 0x12) * 6);
  iVar3 = 0;
  iVar5 = param_9;
  do {
    iVar1 = (int)*psVar2;
    uVar6 = zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb470,
                        *(int *)(iVar5 + 0xe0),iVar1,param_12,param_13,param_14,param_15,param_16);
    uVar6 = zz_0007908_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar5 + 0xe0),puVar4,iVar1,param_12,param_13,param_14,param_15,
                        param_16);
    uVar6 = zz_0007a60_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar5 + 0xe0),&local_38,iVar1,param_12,param_13,param_14,param_15,
                        param_16);
    iVar3 = iVar3 + 1;
    iVar5 = iVar5 + 4;
    psVar2 = psVar2 + 1;
    puVar4[6] = (float)(dVar7 * (double)local_38);
    puVar4[7] = (float)(dVar7 * (double)local_34);
    puVar4[8] = (float)(dVar7 * (double)local_30);
    puVar4 = puVar4 + 3;
  } while (iVar3 < 2);
  *(undefined2 *)(param_9 + 0x7e) = 0xfe00;
  *(undefined2 *)(param_9 + 0x72) = 0;
  return;
}



// ==== 801cdbe0  FUN_801cdbe0 ====

void FUN_801cdbe0(int param_1)

{
  uint uVar1;
  
  *(short *)(param_1 + 0x72) =
       *(short *)(param_1 + 0x72) + *(short *)(&DAT_8038a78c + *(char *)(param_1 + 0x12) * 2);
  uVar1 = countLeadingZeros((int)*(char *)(param_1 + 0x12) - (int)(char)PTR_DAT_80433930[0x32]);
  uVar1 = uVar1 >> 5;
  if (PTR_DAT_80433940[0x1a] == '\0') {
    uVar1 = 0;
  }
  if (uVar1 == 0) {
    *(undefined1 *)(*(int *)(param_1 + 0xe4) + 0x10) = 1;
    *(float *)(param_1 + 0x16c) =
         *(float *)(param_1 + 0x16c) +
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x7e) ^ 0x80000000) -
                DOUBLE_8043bd60);
  }
  else {
    *(undefined1 *)(*(int *)(param_1 + 0xe4) + 0x10) = 0;
  }
  if ((*(short *)PTR_DAT_80433940 == 2) && (*(char *)(param_1 + 0x12) != '\x05')) {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  return;
}



// ==== 801cdcd0  FUN_801cdcd0 ====

/* WARNING: Removing unreachable block (ram,0x801cdde8) */
/* WARNING: Removing unreachable block (ram,0x801cdce0) */

void FUN_801cdcd0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar8;
  float afStack_88 [12];
  float afStack_58 [12];
  undefined4 local_28;
  uint uStack_24;
  
  dVar8 = (double)FLOAT_8043bd68;
  iVar2 = 0;
  pfVar4 = (float *)(param_1 + 0x144);
  iVar3 = param_1;
  do {
    gnt4_PSMTXRotRad_bl((double)(float)(dVar8 * (double)pfVar4[8]),afStack_58,0x7a);
    gnt4_PSMTXRotRad_bl((double)(float)(dVar8 * (double)pfVar4[7]),afStack_88,0x79);
    gnt4_PSMTXConcat_bl(afStack_58,afStack_88,afStack_58);
    gnt4_PSMTXRotRad_bl((double)(float)(dVar8 * (double)pfVar4[6]),afStack_88,0x78);
    pfVar1 = afStack_58;
    gnt4_PSMTXConcat_bl(pfVar1,afStack_88,pfVar1);
    dVar6 = (double)pfVar4[1];
    dVar7 = (double)pfVar4[2];
    uVar5 = zz_020b4ac_((double)*pfVar4,dVar6,dVar7,afStack_58,afStack_58);
    if (iVar2 == 0) {
      local_28 = 0x43300000;
      uStack_24 = (int)*(short *)(param_1 + 0x72) ^ 0x80000000;
      dVar6 = (double)FLOAT_8043bd68;
      gnt4_PSMTXRotRad_bl((double)(float)(dVar6 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                   uStack_24) -
                                                                 DOUBLE_8043bd60)),afStack_88,0x79);
      pfVar1 = afStack_58;
      uVar5 = gnt4_PSMTXConcat_bl(pfVar1,afStack_88,pfVar1);
    }
    zz_00076d0_(uVar5,dVar6,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar3 + 0xe0),afStack_58,
                (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 + 4;
    pfVar4 = pfVar4 + 3;
  } while (iVar2 < 2);
  return;
}



// ==== 801cde10  FUN_801cde10 ====

void FUN_801cde10(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    zz_00097b4_(*(int *)(param_1 + 0xe0),0x47);
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 4;
  } while (iVar1 < 2);
  return;
}



// ==== 801cde60  FUN_801cde60 ====

void FUN_801cde60(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  int iVar2;
  float *pfVar3;
  undefined8 uVar4;
  
  iVar2 = *(int *)(param_9 + 4);
  for (iVar1 = 0; (iVar2 != 0 && (iVar1 < 7)); iVar1 = iVar1 + 1) {
    *(int *)(param_9 + 0x144 + *(char *)(iVar2 + 0x12) * 4) = iVar2;
    iVar2 = *(int *)(iVar2 + 4);
  }
  *(undefined2 *)(param_9 + 0x74) = 0;
  pfVar3 = (float *)0x38;
  zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb470,
              *(int *)(param_9 + 0xe0),0x38,param_12,param_13,param_14,param_15,param_16);
  uVar4 = zz_00086b8_((double)FLOAT_8043bd6c,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                      ,DAT_803bb470,*(int *)(param_9 + 0xe0),pfVar3,param_12,param_13,param_14,
                      param_15,param_16);
  zz_0007c30_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,pfVar3,param_12,param_13,param_14,param_15,param_16);
  zz_01cdf08_(param_9);
  return;
}



// ==== 801cdf08  zz_01cdf08_ ====

void zz_01cdf08_(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + (char)PTR_DAT_80433930[0x32] * 4 + 0x144);
  uVar1 = *(undefined4 *)(iVar2 + 0x148);
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(iVar2 + 0x144);
  *(undefined4 *)(param_1 + 0x24) = uVar1;
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(iVar2 + 0x14c);
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0x400;
  if (*(short *)PTR_DAT_80433940 < 2) {
    *(undefined1 *)(param_1 + 0x82) = 0x21;
  }
  else {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  if (PTR_DAT_80433940[0x1a] != '\0') {
    return;
  }
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801cdf84  FUN_801cdf84 ====

void FUN_801cdf84(int param_1,undefined4 param_2,undefined *param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  undefined8 uVar1;
  double dVar2;
  double dVar3;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_28;
  float local_24;
  float local_20;
  undefined4 local_18;
  uint uStack_14;
  
  zz_00057f0_((float *)(param_1 + 0x20),&local_28);
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_1 + 0x74) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_8043bd68 *
                              (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8043bd60)),
                      (float *)(param_1 + 0x114),0x7a);
  dVar2 = (double)local_24;
  dVar3 = (double)local_20;
  uVar1 = zz_020b4ac_((double)local_28,dVar2,dVar3,(float *)(param_1 + 0x114),
                      (float *)(param_1 + 0x114));
  zz_00076d0_(uVar1,dVar2,dVar3,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),
              (float *)(param_1 + 0x114),param_3,param_4,param_5,param_6,param_7,param_8);
  zz_0009958_(*(int *)(param_1 + 0xe0),1);
  return;
}



// ==== 801ce01c  FUN_801ce01c ====

void FUN_801ce01c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined8 uVar2;
  
  iVar1 = (int)u___>___________<&BCD_8038a764[*(char *)(param_9 + 0x12) * 3];
  uVar2 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb470,
                      *(int *)(param_9 + 0xe0),iVar1,param_12,param_13,param_14,param_15,param_16);
  zz_0007908_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,(undefined4 *)(param_9 + 0x20),iVar1,param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 2;
  return;
}



// ==== 801ce0dc  FUN_801ce0dc ====

void FUN_801ce0dc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  float *pfVar2;
  double dVar3;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [3];
  float afStack_40 [3];
  undefined4 local_34;
  undefined4 local_24;
  undefined4 local_14;
  
  zz_0008970_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,afStack_4c,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  gnt4_PSVECSubtract_bl(afStack_4c,(float *)(param_9 + 0x20),afStack_4c);
  dVar3 = (double)FLOAT_8043bd70;
  pfVar1 = afStack_4c;
  local_54 = FLOAT_8043bd74;
  pfVar2 = &local_58;
  local_58 = FLOAT_8043bd70;
  local_50 = FLOAT_8043bd74;
  zz_0045ef4_(afStack_40,2,pfVar1,pfVar2);
  local_34 = *(undefined4 *)(param_9 + 0x20);
  local_24 = *(undefined4 *)(param_9 + 0x24);
  local_14 = *(undefined4 *)(param_9 + 0x28);
  zz_00076d0_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_40,(undefined *)pfVar1,pfVar2,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x47);
  return;
}



// ==== 801ce174  zz_01ce174_ ====

void zz_01ce174_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,int param_12,
                undefined1 param_13,int param_14,int param_15,undefined1 param_16)

{
  byte bVar1;
  int iVar2;
  short sVar3;
  undefined1 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  
  DAT_80436390 = &DAT_803d5df8;
  gnt4_memset(&DAT_803d5df8,0,0x38);
  sVar3 = (short)param_14;
  *(undefined4 *)(DAT_80436390 + 0x14) = param_9;
  iVar5 = 1 - param_12;
  *(undefined4 *)(DAT_80436390 + 0x18) = param_10;
  *(undefined4 *)(DAT_80436390 + 0x1c) = param_11;
  DAT_80436390[0x30] = param_13;
  *(short *)(DAT_80436390 + 0x20) = sVar3;
  uVar4 = (undefined1)param_15;
  DAT_80436390[0x22] = uVar4;
  DAT_80436390[0x23] = param_16;
  DAT_80436390[0x36] = (char)param_12;
  bVar1 = DAT_80436390[0x23];
  iVar7 = (int)(char)DAT_80436390[0x36];
  iVar6 = iVar7 * 3;
  if (bVar1 == 0) {
    DAT_80436390[0x34] = 0;
    uVar8 = zz_00416d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,0,
                        sVar3,param_15);
    zz_0044eb4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,iVar7,iVar5);
    zz_005809c_(DAT_803c71dc,1);
    zz_005814c_(DAT_803c4e84,sVar3,uVar4);
    zz_0087718_(DAT_803c71e0);
  }
  else if ((bVar1 & 0x20) == 0) {
    if ((bVar1 & 0x10) == 0) {
      DAT_80436390[0x34] = 1;
      uVar8 = zz_0044cf4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar7 << 1
                          ,*(short *)(DAT_80436390 + 0x20));
      zz_0044eb4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,iVar7,iVar5);
      zz_005809c_(DAT_803c71dc,0);
    }
    else {
      DAT_80436390[0x34] = 2;
      iVar2 = zz_01cee00_(param_14);
      DAT_80436390[0x23] = (char)iVar2;
      if ((char)DAT_80436390[0x23] < '\x02') {
        DAT_80436390[0x23] = 2;
      }
      uVar8 = zz_00416d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,0,
                          sVar3,param_15);
      uVar8 = zz_0044cf4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar7 << 1,
                          *(short *)(DAT_80436390 + 0x20));
      zz_0044eb4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  (int)(char)DAT_80436390[0x23],iVar7,iVar5);
      zz_005809c_(DAT_803c71dc,1);
      zz_005814c_(DAT_803c4e84,sVar3,uVar4);
      zz_0087718_(DAT_803c71e0);
    }
  }
  else {
    DAT_80436390[0x34] = 3;
    uVar8 = zz_00416d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,0,
                        0x629,param_15);
    uVar8 = zz_00416d0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,1,0x615,
                        param_15);
    zz_0044eb4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,6,iVar7,iVar5);
    zz_005809c_(DAT_803c71dc,2);
    zz_005814c_(DAT_803c4e84,0x629,uVar4);
    zz_005814c_(DAT_803c4e88,0x615,uVar4);
    zz_0087718_(DAT_803c71e0);
  }
  zz_00059b8_();
  zz_00f0a4c_();
  return;
}



// ==== 801ce444  zz_01ce444_ ====

int zz_01ce444_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8)

{
  undefined8 uVar1;
  
  *(undefined4 *)(DAT_80436390 + 8) = (&DAT_803c71fc)[DAT_80436390[0x30] * 8];
  *(undefined4 *)(DAT_80436390 + 0xc) = (&DAT_803c7204)[DAT_80436390[0x30] * 8];
  *(uint *)(DAT_80436390 + 0x10) =
       *(uint *)(DAT_80436390 + 0xc) | (&DAT_803c720c)[DAT_80436390[0x30] * 8];
  uVar1 = (*(code *)(&PTR_FUN_8038a7d0)[*DAT_80436390])();
  if (DAT_80436390[0x31] != '\0') {
    zz_01ced1c_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  }
  return (int)DAT_80436390[0x32];
}



// ==== 801ce504  FUN_801ce504 ====

void FUN_801ce504(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  byte bVar1;
  int iVar2;
  uint uVar3;
  byte *pbVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int unaff_r31;
  undefined8 uVar5;
  
  iVar2 = zz_000a3c4_();
  pbVar4 = DAT_80436390;
  if (iVar2 == 0) {
    uVar3 = (uint)*DAT_80436390;
    *DAT_80436390 = *DAT_80436390 + 1;
    uVar5 = zz_00e99c8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,
                        DAT_8031a0bc,uVar3,pbVar4,in_r8,in_r9,in_r10);
    uVar5 = zz_00e9b08_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,1,1,uVar3,
                        pbVar4,in_r8,in_r9,in_r10);
    bVar1 = DAT_80436390[0x34];
    if (bVar1 == 2) {
      unaff_r31 = 0x83e;
    }
    else if ((char)bVar1 < '\x02') {
      if (-1 < (char)bVar1) {
        unaff_r31 = 0x83c;
      }
    }
    else if ((char)bVar1 < '\x04') {
      unaff_r31 = 0x83f;
    }
    uVar5 = zz_00e99c8_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,unaff_r31,
                        uVar3,pbVar4,in_r8,in_r9,in_r10);
    uVar5 = zz_00e9b08_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,1,1,uVar3,
                        pbVar4,in_r8,in_r9,in_r10);
    zz_00e9b08_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,1,1,uVar3,pbVar4,
                in_r8,in_r9,in_r10);
    pbVar4 = DAT_80436390;
    pbVar4[4] = 0;
    pbVar4[5] = 10;
  }
  return;
}



// ==== 801ce5ec  FUN_801ce5ec ====

void FUN_801ce5ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,float *param_11,float *param_12,char *param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  float *pfVar3;
  float *pfVar4;
  float fVar5;
  int iVar6;
  undefined4 extraout_r4;
  undefined *puVar7;
  undefined8 uVar8;
  double dVar9;
  undefined8 extraout_f1;
  char acStack_58 [84];
  
  uVar8 = CONCAT44(param_9,DAT_80436390);
  cVar1 = *(char *)((int)DAT_80436390 + 1);
  if (cVar1 == '\x02') {
    zz_01cf2a8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,DAT_80436390
                ,param_11,param_12,param_13,param_14,param_15,param_16);
    if (((uint)DAT_80436390[3] & 0x100) != 0) {
      dVar9 = (double)FLOAT_8043bd78;
      *(char *)((int)DAT_80436390 + 1) = *(char *)((int)DAT_80436390 + 1) + '\x01';
      *(undefined2 *)(DAT_80436390 + 1) = 4;
      zz_00e9b60_(dVar9,2,0x20,2);
      zz_0027aac_(0,0x20,1);
    }
    cVar1 = *(char *)(DAT_80436390 + 0xd);
    if (cVar1 == '\x02') {
      sprintf(acStack_58,s_PARTS_GOUSEI_______04X__d__d_802b36fc,(uint)*(ushort *)(DAT_80436390 + 8)
              ,(int)*(char *)((int)DAT_80436390 + 0x22),(int)*(char *)((int)DAT_80436390 + 0x23));
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        sprintf(acStack_58,s_UNIT_GET_______04X__d_802b36c8,(uint)*(ushort *)(DAT_80436390 + 8),
                (int)*(char *)((int)DAT_80436390 + 0x22));
      }
      else if (-1 < cVar1) {
        sprintf(acStack_58,s_PARTS_GET_______04X__d__d_802b36e0,(uint)*(ushort *)(DAT_80436390 + 8),
                (int)*(char *)((int)DAT_80436390 + 0x22),(int)*(char *)((int)DAT_80436390 + 0x23));
      }
    }
    else if (cVar1 < '\x04') {
      sprintf(acStack_58,s_G_RED_POWER_UP____802b371c);
    }
    zz_01cedfc_();
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      sVar2 = *(short *)(DAT_80436390 + 1);
      *(short *)(DAT_80436390 + 1) = sVar2 + -1;
      if (-1 < (short)(sVar2 + -1)) {
        return;
      }
      uVar8 = zz_00e9b08_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,1,0,
                          param_12,param_13,param_14,param_15,param_16);
      uVar8 = zz_00e9b08_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,1,0,
                          param_12,param_13,param_14,param_15,param_16);
      puVar7 = (undefined *)0x0;
      uVar8 = zz_00e9b08_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,1,0,
                          param_12,param_13,param_14,param_15,param_16);
      zz_0008a94_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb35c,
                  extraout_r4,puVar7,param_12,param_13,param_14,param_15,param_16);
      fVar5 = FLOAT_8043bd78;
      param_11 = (float *)0x0;
      *(char *)((int)DAT_80436390 + 1) = *(char *)((int)DAT_80436390 + 1) + '\x01';
      *(char *)((int)DAT_80436390 + 0x31) = '\x01';
      DAT_80436390[0xb] = fVar5;
      param_12 = DAT_80436390;
      dVar9 = FUN_801dc468((double)DAT_80436390[0xb],param_2,param_3,param_4,param_5,param_6,param_7
                           ,param_8,DAT_803bb35c,0x28,0,DAT_80436390,param_13,param_14,param_15,
                           param_16);
      DAT_80436390[10] = (float)dVar9;
      cVar1 = *(char *)(DAT_80436390 + 0xd);
      if (cVar1 == '\x02') {
        *(char *)((int)DAT_80436390 + 0x33) = '\0';
        zz_01e05dc_(*(char *)((int)DAT_80436390 + 0x22),(int)*(char *)((int)DAT_80436390 + 0x23),
                    (char *)((int)DAT_80436390 + 0x33));
        zz_01e053c_(2,0,0,1,(char *)((int)DAT_80436390 + 0x33));
        param_12 = (float *)0x1;
        param_13 = (char *)((int)DAT_80436390 + 0x33);
        param_11 = (float *)(int)*(char *)((int)DAT_80436390 + 0x22);
        zz_01e053c_(6,*(undefined2 *)(DAT_80436390 + 8),*(char *)((int)DAT_80436390 + 0x22),1,
                    param_13);
      }
      else if (cVar1 < '\x02') {
        if (cVar1 == '\0') {
          *(char *)((int)DAT_80436390 + 0x33) = '\0';
          zz_01e053c_(2,0,0,0,(char *)((int)DAT_80436390 + 0x33));
          zz_01e053c_(3,0,0,0,(char *)((int)DAT_80436390 + 0x33));
          param_12 = (float *)0x0;
          param_13 = (char *)((int)DAT_80436390 + 0x33);
          param_11 = (float *)(int)*(char *)((int)DAT_80436390 + 0x22);
          zz_01e053c_(6,*(undefined2 *)(DAT_80436390 + 8),*(char *)((int)DAT_80436390 + 0x22),0,
                      param_13);
        }
        else if (-1 < cVar1) {
          *(char *)((int)DAT_80436390 + 0x33) = '\0';
          zz_01e053c_(0,*(undefined2 *)(DAT_80436390 + 8),*(char *)((int)DAT_80436390 + 0x22),
                      *(char *)((int)DAT_80436390 + 0x23),(char *)((int)DAT_80436390 + 0x33));
          zz_01e053c_(3,0,0,0,(char *)((int)DAT_80436390 + 0x33));
          param_13 = (char *)((int)DAT_80436390 + 0x33);
          param_11 = (float *)(int)*(char *)((int)DAT_80436390 + 0x22);
          param_12 = (float *)(int)*(char *)((int)DAT_80436390 + 0x23);
          zz_01e053c_(7,*(undefined2 *)(DAT_80436390 + 8),*(char *)((int)DAT_80436390 + 0x22),
                      *(char *)((int)DAT_80436390 + 0x23),param_13);
        }
      }
      else if (cVar1 < '\x04') {
        *(char *)((int)DAT_80436390 + 0x33) = '\0';
        zz_01e053c_(2,0,0,2,(char *)((int)DAT_80436390 + 0x33));
        zz_01e053c_(2,0,0,3,(char *)((int)DAT_80436390 + 0x33));
        param_11 = (float *)0x0;
        param_13 = (char *)((int)DAT_80436390 + 0x33);
        param_12 = (float *)0x0;
        zz_01e053c_(5,0,0,0,param_13);
      }
      uVar8 = zz_0005984_(1);
      param_1 = extraout_f1;
    }
    else if (cVar1 < '\0') {
      return;
    }
    zz_01cf2a8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (int)((ulonglong)uVar8 >> 0x20),(int)uVar8,param_11,param_12,param_13,param_14,
                param_15,param_16);
    if (FLOAT_8043bd7c <= DAT_80436390[0xb]) {
      zz_00f0a60_();
      DAT_80436390[0xb] = FLOAT_8043bd7c;
      iVar6 = zz_000a3c4_();
      if (iVar6 == 0) {
        *(char *)((int)DAT_80436390 + 1) = *(char *)((int)DAT_80436390 + 1) + '\x01';
      }
    }
  }
  else if (cVar1 < '\x04') {
    uVar8 = zz_01cf2a8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                        DAT_80436390,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar6 = zz_0027adc_();
    pfVar3 = DAT_80436390;
    if ((iVar6 == 0) &&
       (sVar2 = *(short *)(DAT_80436390 + 1), *(short *)(DAT_80436390 + 1) = sVar2 + -1,
       pfVar4 = DAT_80436390, (short)(sVar2 + -1) < 1)) {
      *(char *)((int)DAT_80436390 + 0x33) = '\x01';
      zz_01dc614_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,pfVar4,pfVar3,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      zz_00f07c4_();
      *(char *)DAT_80436390 = *(char *)DAT_80436390 + '\x01';
      *(char *)((int)DAT_80436390 + 1) = '\0';
      cVar1 = *(char *)(DAT_80436390 + 0xd);
      if (cVar1 != '\x02') {
        if (cVar1 < '\x02') {
          if (cVar1 != '\0') {
            return;
          }
        }
        else {
          if ('\x03' < cVar1) {
            return;
          }
          *(undefined1 *)(DAT_803c4e88 + 0x18) = 2;
        }
      }
      *(undefined1 *)(DAT_803c4e84 + 0x18) = 2;
    }
  }
  return;
}



// ==== 801ceadc  FUN_801ceadc ====

void FUN_801ceadc(void)

{
  zz_01ceb20_();
  zz_0005984_(0);
  *(undefined1 *)(DAT_80436390 + 0x31) = 0;
  *(undefined1 *)(DAT_80436390 + 0x32) = 1;
  zz_0027c1c_();
  return;
}



// ==== 801ceb20  zz_01ceb20_ ====

void zz_01ceb20_(void)

{
  char cVar1;
  
  cVar1 = *(char *)(DAT_80436390 + 0x34);
  if (cVar1 == '\x02') {
    zz_00448dc_(*(char *)(DAT_80436390 + 0x23) + 4);
    zz_0044ddc_();
    zz_0041b58_(0);
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      zz_00448dc_(2);
      zz_00448dc_(0x10);
      zz_0041b58_(0);
    }
    else if (-1 < cVar1) {
      zz_00448dc_(4);
      zz_00448dc_(0x10);
      zz_0044ddc_();
    }
  }
  else if (cVar1 < '\x04') {
    zz_00448dc_(0xe);
    zz_0041b58_(0);
    zz_0041b58_(1);
  }
  zz_0008b58_();
  return;
}



// ==== 801cebe0  zz_01cebe0_ ====

undefined4 zz_01cebe0_(void)

{
  char cVar1;
  short local_14 [2];
  short local_10 [2];
  short local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  cVar1 = *(char *)(DAT_80436390 + 0x34);
  if (cVar1 == '\x02') {
    local_14[0] = *(short *)(DAT_80436390 + 0x20);
    zz_01cf03c_(*(int *)(DAT_80436390 + 0x14),*(short **)(DAT_80436390 + 0x18),
                *(int *)(DAT_80436390 + 0x1c),local_14,(int)*(char *)(DAT_80436390 + 0x22));
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      if ((199 < *(short *)(*(int *)(DAT_80436390 + 0x1c) + 0x2172)) &&
         (1999 < *(short *)(*(int *)(DAT_80436390 + 0x18) + 44000))) {
        return 0xffffffff;
      }
      local_10[0] = *(short *)(DAT_80436390 + 0x20);
      local_c = local_10[0];
      zz_01caf80_(*(int *)(DAT_80436390 + 0x14),*(short **)(DAT_80436390 + 0x18),
                  *(int *)(DAT_80436390 + 0x1c),local_10,(int)*(char *)(DAT_80436390 + 0x22));
    }
    else if (-1 < cVar1) {
      if (999 < *(short *)(*(int *)(DAT_80436390 + 0x18) + 0xabe2)) {
        return 0xfffffffe;
      }
      local_4 = CONCAT22(*(undefined2 *)(DAT_80436390 + 0x20),
                         CONCAT11(*(char *)(DAT_80436390 + 0x23) + -1,
                                  *(undefined1 *)(DAT_80436390 + 0x22)));
      local_8 = local_4;
      zz_01cb278_(*(int *)(DAT_80436390 + 0x14),*(int *)(DAT_80436390 + 0x18),&local_8);
    }
  }
  else if (cVar1 < '\x04') {
    zz_01cf16c_(*(int *)(DAT_80436390 + 0x14),*(short **)(DAT_80436390 + 0x18),
                *(int *)(DAT_80436390 + 0x1c));
  }
  return 0;
}



// ==== 801ced1c  zz_01ced1c_ ====

void zz_01ced1c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  zz_01ced40_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_01ceda4_();
  return;
}



// ==== 801ced40  zz_01ced40_ ====

void zz_01ced40_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8)

{
  undefined8 uVar1;
  
  zz_0058160_();
  zz_0089898_(1);
  zz_0089898_(0x28);
  *(int *)(PTR_DAT_80433934 + 0xb0) = *(int *)(PTR_DAT_80433934 + 0xb0) + 1;
  zz_0089554_();
  zz_008972c_();
  uVar1 = zz_0053a94_();
  uVar1 = zz_00897a4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,9);
  uVar1 = zz_00897a4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x19);
  zz_00897a4_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x31);
  return;
}



// ==== 801ceda4  zz_01ceda4_ ====

void zz_01ceda4_(void)

{
  zz_008a16c_();
  zz_0053928_();
  zz_0089c00_(1);
  zz_0089c00_(0x28);
  zz_008c0dc_(FUN_80089eb4);
  zz_008c0dc_(FUN_8008a010);
  zz_008c0dc_(FUN_8008a0a8);
  return;
}



// ==== 801cedfc  zz_01cedfc_ ====

void zz_01cedfc_(void)

{
  return;
}



// ==== 801cee00  zz_01cee00_ ====

int zz_01cee00_(int param_1)

{
  short *psVar1;
  
  psVar1 = &DAT_8035b2dc;
  while( true ) {
    if (*psVar1 < 0) {
      return 1;
    }
    if (*psVar1 == param_1) break;
    psVar1 = psVar1 + 8;
  }
  return (int)psVar1[1];
}



// ==== 801cee38  zz_01cee38_ ====

uint zz_01cee38_(int param_1,int param_2,int param_3)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  short sVar14;
  
  iVar2 = zz_01cee00_(param_2);
  if (iVar2 < 2) {
    uVar3 = 0;
  }
  else {
    uVar1 = 0;
    iVar13 = 0;
    if (0 < iVar2) {
      if ((8 < iVar2) && (uVar3 = iVar2 - 1U >> 3, 0 < iVar2 + -8)) {
        do {
          iVar7 = iVar13 + 2;
          uVar9 = 1 << iVar13;
          iVar4 = iVar13 + 1;
          iVar11 = iVar13 + 4;
          iVar5 = iVar13 + 3;
          iVar10 = iVar13 + 5;
          iVar8 = iVar13 + 6;
          iVar6 = iVar13 + 7;
          iVar13 = iVar13 + 8;
          uVar1 = uVar1 | uVar9 | 1 << iVar4 | 1 << iVar7 | 1 << iVar5 | 1 << iVar11 | 1 << iVar10 |
                  1 << iVar8 | 1 << iVar6;
          uVar3 = uVar3 - 1;
        } while (uVar3 != 0);
      }
      iVar4 = iVar2 - iVar13;
      if (iVar13 < iVar2) {
        do {
          uVar3 = 1 << iVar13;
          iVar13 = iVar13 + 1;
          uVar1 = uVar1 | uVar3;
          iVar4 = iVar4 + -1;
        } while (iVar4 != 0);
      }
    }
    uVar3 = 0;
    iVar2 = 0;
    sVar14 = 0;
    DAT_803d5de8 = 0xffff;
    uVar9 = 0;
    DAT_803d5dea = 0xffff;
    DAT_803d5dec = 0xffff;
    DAT_803d5dee = 0xffff;
    DAT_803d5df0 = 0xffff;
    DAT_803d5df2 = 0xffff;
    DAT_803d5df4 = 0xffff;
    DAT_803d5df6 = 0xffff;
    iVar13 = 500;
    do {
      if (*(short *)(param_1 + 32000) == param_2) {
        if (*(char *)(param_1 + 0x7d03) == param_3) {
          uVar12 = 1 << (int)*(char *)(param_1 + 0x7d02);
          if ((uVar9 & uVar12) == 0) {
            *(short *)((int)&DAT_803d5de8 + iVar2) = sVar14;
            uVar9 = uVar9 | uVar12;
            uVar3 = uVar3 + 1;
            iVar2 = iVar2 + 2;
          }
        }
      }
      if (*(short *)(param_1 + 0x7d0c) == param_2) {
        if (*(char *)(param_1 + 0x7d0f) == param_3) {
          uVar12 = 1 << (int)*(char *)(param_1 + 0x7d0e);
          if ((uVar9 & uVar12) == 0) {
            *(short *)((int)&DAT_803d5de8 + iVar2) = sVar14 + 1;
            uVar9 = uVar9 | uVar12;
            uVar3 = uVar3 + 1;
            iVar2 = iVar2 + 2;
          }
        }
      }
      param_1 = param_1 + 0x18;
      sVar14 = sVar14 + 2;
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
    uVar3 = uVar3 & (int)~(uVar9 - uVar1 | uVar1 - uVar9) >> 0x1f;
  }
  return uVar3;
}



// ==== 801cf03c  zz_01cf03c_ ====

undefined4 zz_01cf03c_(int param_1,short *param_2,int param_3,short *param_4,int param_5)

{
  short *psVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  short local_28 [10];
  
  iVar2 = zz_01cee00_((int)*param_4);
  iVar4 = 0;
  if (((((-1 < DAT_803d5de8) && (iVar4 = 1, -1 < DAT_803d5dea)) && (iVar4 = 2, -1 < DAT_803d5dec))
      && ((iVar4 = 3, -1 < DAT_803d5dee && (iVar4 = 4, -1 < DAT_803d5df0)))) &&
     ((iVar4 = 5, -1 < DAT_803d5df2 &&
      ((iVar4 = 6, -1 < DAT_803d5df4 && (iVar4 = 7, -1 < DAT_803d5df6)))))) {
    iVar4 = 8;
  }
  if (iVar4 == iVar2) {
    local_28[0] = *param_4;
    uVar3 = zz_01caf80_(param_1,param_2,param_3,local_28,param_5);
    psVar1 = &DAT_803d5de8;
    *(undefined4 *)(DAT_80436390 + 0x24) = uVar3;
    while( true ) {
      if (*psVar1 < 0) break;
      zz_01cbe14_((int)param_2,(int)*psVar1);
      psVar1 = psVar1 + 1;
    }
    uVar3 = *(undefined4 *)(DAT_80436390 + 0x24);
  }
  else {
    uVar3 = 0;
  }
  return uVar3;
}



// ==== 801cf16c  zz_01cf16c_ ====

undefined4 zz_01cf16c_(int param_1,short *param_2,int param_3)

{
  short *psVar1;
  int iVar2;
  int iVar3;
  short local_28 [2];
  short local_24 [8];
  
  psVar1 = (short *)(param_3 + 0x870);
  iVar3 = 200;
  do {
    if (*psVar1 == 0x615) {
      *psVar1 = 0x629;
      iVar2 = 0;
      *(undefined1 *)((int)psVar1 + 3) = 0;
      iVar3 = *(int *)(param_1 + 0x50);
      *(int *)(param_1 + 0x50) = iVar3 + 1;
      *(int *)(psVar1 + 2) = iVar3;
      psVar1[4] = 0;
      psVar1[5] = 0;
      *(undefined1 *)(psVar1 + 6) = 1;
      do {
        if ((*(uint *)(psVar1 + 8) & 1 << iVar2) != 0) {
          zz_01ccd94_(param_3,iVar2);
        }
        iVar2 = iVar2 + 1;
      } while (iVar2 < 0x14);
      local_24[0] = *psVar1;
      zz_01cb368_(param_1,local_24,(int)*(char *)(psVar1 + 1));
      return 1;
    }
    psVar1 = psVar1 + 0x10;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 2000;
  do {
    if (*param_2 == 0x615) {
      *param_2 = 0x629;
      *(undefined1 *)((int)param_2 + 3) = 0;
      iVar3 = *(int *)(param_1 + 0x50);
      *(int *)(param_1 + 0x50) = iVar3 + 1;
      *(int *)(param_2 + 2) = iVar3;
      param_2[4] = 0;
      param_2[5] = 0;
      *(undefined1 *)(param_2 + 6) = 1;
      local_28[0] = *param_2;
      zz_01cb368_(param_1,local_28,(int)*(char *)(param_2 + 1));
      return 2;
    }
    param_2 = param_2 + 8;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return 0;
}



// ==== 801cf2a8  zz_01cf2a8_ ====

void zz_01cf2a8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  double dVar1;
  
  *(float *)(DAT_80436390 + 0x2c) = *(float *)(DAT_80436390 + 0x2c) + FLOAT_8043bd80;
  if ((*(uint *)(DAT_80436390 + 0xc) & 0x1000) != 0) {
    dVar1 = (double)*(float *)(DAT_80436390 + 0x2c);
    if ((double)FLOAT_8043bd84 <= dVar1) {
      if (dVar1 < (double)FLOAT_8043bd7c) {
        *(float *)(DAT_80436390 + 0x2c) = FLOAT_8043bd7c;
      }
    }
    else {
      *(float *)(DAT_80436390 + 0x2c) = FLOAT_8043bd84;
      param_11 = (float *)0x83d;
      if (*(char *)(DAT_80436390 + 0x34) == '\x03') {
        param_11 = (float *)0x840;
      }
      zz_00e99c8_(dVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,(int)param_11,
                  param_12,param_13,param_14,param_15,param_16);
      param_10 = extraout_r4;
    }
  }
  if (*(float *)(DAT_80436390 + 0x28) <= *(float *)(DAT_80436390 + 0x2c)) {
    *(float *)(DAT_80436390 + 0x2c) = FLOAT_8043bd7c;
  }
  zz_01dc590_((double)*(float *)(DAT_80436390 + 0x2c),param_2,param_3,param_4,param_5,param_6,
              param_7,param_8,DAT_80436390,param_10,param_11,param_12,param_13,param_14,param_15,
              param_16);
  return;
}



// ==== 801cf360  zz_01cf360_ ====

void zz_01cf360_(int param_1)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((((sVar1 == 0x615) || (sVar1 == 0x629)) || (sVar1 == 0x62a)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,1), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x13] = 0;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_801cf470;
    *(code **)(puVar2 + 0x10c) = FUN_801cf720;
    *(int *)(puVar2 + 0x8c) = param_1;
    *(undefined4 *)(puVar2 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar2 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar2[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar2[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar2[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar2 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar2 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar2 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar2 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar2 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar2[0xd0] = *(undefined1 *)(param_1 + 0xd0);
  }
  return;
}



// ==== 801cf470  FUN_801cf470 ====

void FUN_801cf470(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8038a7ec)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801cf4c4  FUN_801cf4c4 ====

void FUN_801cf4c4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  uint uVar2;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  undefined8 uVar4;
  
  uVar2 = (uint)*(byte *)(param_9 + 0x18);
  *(byte *)(param_9 + 0x18) = *(byte *)(param_9 + 0x18) + 1;
  *(undefined1 *)(param_9 + 0x19) = 0;
  iVar3 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar4 = zz_0089100_(param_9,(int)*(char *)(iVar3 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0xd0;
  *(undefined1 *)(param_9 + 0x89) = 1;
  uVar1 = DAT_8038a7e4;
  *(undefined4 *)(param_9 + 0x58) = DAT_8038a7e0;
  *(undefined4 *)(param_9 + 0x5c) = uVar1;
  *(undefined4 *)(param_9 + 0x60) = DAT_8038a7e8;
  iVar3 = zz_0006f98_(iVar3);
  *(float *)(param_9 + 0x148) = FLOAT_8043bd88;
  zz_000726c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0x600),
              *(int *)(param_9 + 0xe0),(float *)0xc,(int)*(char *)(param_9 + 0x88),uVar2,in_r8,in_r9
              ,in_r10);
  zz_0007cac_((double)*(float *)(param_9 + 0x148),*(int *)(param_9 + 0xe0));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  return;
}



// ==== 801cf59c  FUN_801cf59c ====

void FUN_801cf59c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  bool bVar6;
  
  cVar1 = *(char *)(param_1 + 0x19);
  iVar5 = *(int *)(param_1 + 0x90);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    fVar2 = FLOAT_8043bd8c;
    *(undefined1 *)(param_1 + 0x84) = 0x50;
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
    *(float *)(param_1 + 0x144) = fVar2;
  }
  fVar3 = FLOAT_8043bd90;
  fVar2 = *(float *)(param_1 + 0x144) - *(float *)(iVar5 + 0x1dc8);
  bVar6 = fVar2 <= FLOAT_8043bd90;
  *(float *)(param_1 + 0x144) = fVar2;
  fVar4 = FLOAT_8043bd94;
  fVar2 = FLOAT_8043bd88;
  if (bVar6) {
    *(float *)(param_1 + 0x58) = FLOAT_8043bd88;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x60) = fVar2;
    *(float *)(param_1 + 0x148) = fVar3;
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    *(float *)(param_1 + 0x58) =
         FLOAT_8043bd94 * *(float *)(iVar5 + 0x1dc8) + *(float *)(param_1 + 0x58);
    *(float *)(param_1 + 0x5c) = fVar4 * *(float *)(iVar5 + 0x1dc8) + *(float *)(param_1 + 0x5c);
    *(float *)(param_1 + 0x60) = fVar4 * *(float *)(iVar5 + 0x1dc8) + *(float *)(param_1 + 0x60);
    if (fVar2 < *(float *)(param_1 + 0x58)) {
      *(float *)(param_1 + 0x58) = fVar2;
    }
    if (FLOAT_8043bd88 < *(float *)(param_1 + 0x5c)) {
      *(float *)(param_1 + 0x5c) = FLOAT_8043bd88;
    }
    if (FLOAT_8043bd88 < *(float *)(param_1 + 0x60)) {
      *(float *)(param_1 + 0x60) = FLOAT_8043bd88;
    }
    fVar2 = FLOAT_8043bd90;
    *(float *)(param_1 + 0x148) =
         -(FLOAT_8043bd98 * *(float *)(iVar5 + 0x1dc8) - *(float *)(param_1 + 0x148));
    if (*(float *)(param_1 + 0x148) < fVar2) {
      *(float *)(param_1 + 0x148) = fVar2;
    }
  }
  zz_0007cac_((double)*(float *)(param_1 + 0x148),*(int *)(param_1 + 0xe0));
  return;
}



// ==== 801cf700  FUN_801cf700 ====

void FUN_801cf700(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801cf720  FUN_801cf720 ====

void FUN_801cf720(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = *(int *)(param_9 + *(char *)(param_9 + 0x13) * 4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,0x44);
  return;
}



// ==== 801cf770  zz_01cf770_ ====

void zz_01cf770_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if ((((sVar1 == 0x615) || (sVar1 == 0x629)) || (sVar1 == 0x62a)) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x13] = 0;
    puVar2[0x11] = param_2;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_801cf890;
    *(code **)(puVar2 + 0x10c) = FUN_801d0014;
    *(int *)(puVar2 + 0x8c) = param_1;
    *(undefined4 *)(puVar2 + 0x90) = *(undefined4 *)(param_1 + 0x90);
    *(undefined2 *)(puVar2 + 0x94) = *(undefined2 *)(param_1 + 0x94);
    puVar2[0x96] = *(undefined1 *)(param_1 + 0x96);
    puVar2[0x97] = *(undefined1 *)(param_1 + 0x97);
    puVar2[0x88] = *(undefined1 *)(param_1 + 0x88);
    *(undefined4 *)(puVar2 + 200) = *(undefined4 *)(param_1 + 200);
    *(undefined4 *)(puVar2 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
    *(undefined4 *)(puVar2 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
    *(undefined4 *)(puVar2 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(puVar2 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
    *(undefined4 *)(puVar2 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
    puVar2[0xd0] = *(undefined1 *)(param_1 + 0xd0);
  }
  return;
}



// ==== 801cf890  FUN_801cf890 ====

void FUN_801cf890(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_1 + 0x90);
  iVar1 = zz_00660e8_(param_1,iVar2);
  if ((iVar1 == 0) && (*(short *)(iVar2 + 0x6f6) == 0)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
    zz_0089444_(param_1);
    zz_008aff0_(param_1);
  }
  (*(code *)(&PTR_FUN_8038a8e4)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801cf924  FUN_801cf924 ====

void FUN_801cf924(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined4 extraout_r4;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  iVar4 = *(byte *)(param_9 + 0x18) + 1;
  *(char *)(param_9 + 0x18) = (char)iVar4;
  *(undefined1 *)(param_9 + 0x19) = 0;
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_801d0064;
  uVar6 = zz_0089100_(param_9,1,1);
  iVar1 = *(char *)(param_9 + 0x11) * 0x30;
  iVar5 = zz_0006f98_(iVar5);
  iVar3 = iVar5 + 0xc28;
  iVar2 = (int)*(short *)(&DAT_8038a800 + iVar1);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),iVar2,iVar3,iVar4,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,iVar2,iVar3,iVar4,in_r8,in_r9,in_r10);
  uVar6 = zz_0007cac_((double)FLOAT_8043bda0,*(int *)(param_9 + 0xe0));
  zz_000726c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar5 + 0x600),
              *(int *)(param_9 + 0xe4),(float *)(int)*(short *)(&DAT_8038a818 + iVar1),
              (int)*(char *)(param_9 + 0x88),iVar4,in_r8,in_r9,in_r10);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_01cfa04_(param_9);
  return;
}



// ==== 801cfa04  zz_01cfa04_ ====

void zz_01cfa04_(int param_1)

{
  (*(code *)(&PTR_FUN_80435aa0)[*(char *)(param_1 + 0x13)])();
  return;
}



// ==== 801cfa3c  FUN_801cfa3c ====

void FUN_801cfa3c(int param_1)

{
  (*(code *)(&PTR_LAB_80435aa8)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 801cfb24  FUN_801cfb24 ====

void FUN_801cfb24(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  short sVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = *(int *)(param_1 + 0x90);
  sVar3 = *(short *)(iVar5 + 0x6f6);
  if (sVar3 == 1) {
    sVar3 = (short)(int)((float)((double)CONCAT44(0x43300000,
                                                  (int)*(short *)(param_1 + 0x146) ^ 0x80000000) -
                                DOUBLE_8043bda8) - *(float *)(iVar5 + 0x1dc8));
    *(short *)(param_1 + 0x146) = sVar3;
    if (sVar3 < 1) {
      iVar4 = *(short *)(param_1 + 0x144) * 0xc;
      *(short *)(param_1 + 0x144) = *(short *)(param_1 + 0x144) + 1;
      uVar2 = *(undefined4 *)(&DAT_8038a894 + iVar4);
      *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(&DAT_8038a890 + iVar4);
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(&DAT_8038a898 + iVar4);
      *(ushort *)(param_1 + 0x144) = *(ushort *)(param_1 + 0x144) & 1;
      *(undefined2 *)(param_1 + 0x146) = 0;
    }
  }
  else if (sVar3 == 2) {
    cVar1 = *(char *)(param_1 + 0x1a);
    if (cVar1 != '\x01') {
      if (('\0' < cVar1) || (cVar1 < '\0')) goto LAB_801cfc84;
      *(undefined2 *)(param_1 + 0x144) = 2;
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    }
    iVar4 = *(short *)(param_1 + 0x144) * 0xc;
    uVar2 = *(undefined4 *)(&DAT_8038a894 + iVar4);
    *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(&DAT_8038a890 + iVar4);
    *(undefined4 *)(param_1 + 0x5c) = uVar2;
    *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(&DAT_8038a898 + iVar4);
    sVar3 = *(short *)(param_1 + 0x144) + 1;
    *(short *)(param_1 + 0x144) = sVar3;
    if (3 < sVar3) {
      *(undefined2 *)(param_1 + 0x144) = 2;
    }
  }
  else if (sVar3 == 3) {
    *(char *)(param_1 + 0x13) = *(char *)(param_1 + 0x13) + '\x01';
    *(undefined1 *)(param_1 + 0x19) = 0;
    zz_01cfcfc_(param_1);
  }
LAB_801cfc84:
  *(short *)(param_1 + 0x70) =
       *(short *)(param_1 + 0x70) + (short)(int)(FLOAT_8043bda4 * *(float *)(iVar5 + 0x1dc8));
  return;
}



// ==== 801cfcc0  FUN_801cfcc0 ====

void FUN_801cfcc0(int param_1)

{
  (*(code *)(&PTR_zz_01cfcfc__8038a8f4)[*(char *)(param_1 + 0x19)])();
  return;
}



// ==== 801cfcfc  zz_01cfcfc_ ====

void zz_01cfcfc_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  iVar1 = *(char *)(param_1 + 0x13) * 0x18 + *(char *)(param_1 + 0x11) * 0x30;
  *(undefined *)(param_1 + 0x89) = (&DAT_8038a800)[iVar1 + 2];
  *(undefined *)(param_1 + 0x12) = (&DAT_8038a800)[iVar1 + 3];
  iVar3 = *(char *)(param_1 + 0x11) * 0xc;
  uVar2 = *(undefined4 *)(&DAT_8038a8c4 + iVar3);
  *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(&DAT_8038a8c0 + iVar3);
  *(undefined4 *)(param_1 + 0x5c) = uVar2;
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(&DAT_8038a8c8 + iVar3);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(&DAT_8038a800 + iVar1 + 0x10);
  *(undefined2 *)(param_1 + 0x74) = *(undefined2 *)(&DAT_8038a800 + iVar1 + 0x14);
  uVar2 = *(undefined4 *)(&DAT_8038a800 + iVar1 + 8);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_8038a800 + iVar1 + 4);
  *(undefined4 *)(param_1 + 0x68) = uVar2;
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_8038a800 + iVar1 + 0xc);
  *(undefined1 *)(param_1 + 0x1a) = 0;
  *(undefined2 *)(param_1 + 0x146) = 2;
  return;
}



// ==== 801cfdac  FUN_801cfdac ====

void FUN_801cfdac(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  short sVar4;
  undefined4 uVar5;
  int iVar6;
  double local_18;
  double local_10;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  iVar3 = *(int *)(param_1 + 0x90);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if (cVar1 < '\x03') {
        iVar6 = *(char *)(param_1 + 0x11) * 0xc;
        uVar5 = *(undefined4 *)(&DAT_8038a8c4 + iVar6);
        *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(&DAT_8038a8c0 + iVar6);
        *(undefined4 *)(param_1 + 0x5c) = uVar5;
        *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(&DAT_8038a8c8 + iVar6);
        *(undefined1 *)(param_1 + 0x1a) = 0;
        *(undefined2 *)(param_1 + 0x146) = 2;
      }
      goto LAB_801cfef0;
    }
    if (cVar1 < '\0') goto LAB_801cfef0;
    local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x146)) ^ 0x80000000);
    sVar4 = (short)(int)((float)(local_18 - DOUBLE_8043bda8) - *(float *)(iVar3 + 0x1dc8));
    *(short *)(param_1 + 0x146) = sVar4;
    if (0 < sVar4) goto LAB_801cfef0;
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    *(undefined2 *)(param_1 + 0x146) = 2;
  }
  local_10 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x146)) ^ 0x80000000);
  sVar4 = (short)(int)((float)(local_10 - DOUBLE_8043bda8) - *(float *)(iVar3 + 0x1dc8));
  *(short *)(param_1 + 0x146) = sVar4;
  fVar2 = FLOAT_8043bdb0;
  if (sVar4 < 1) {
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  }
  else {
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) - FLOAT_8043bdb0;
    *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) - fVar2;
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) - fVar2;
  }
LAB_801cfef0:
  *(short *)(param_1 + 0x70) =
       *(short *)(param_1 + 0x70) + (short)(int)(FLOAT_8043bda4 * *(float *)(iVar3 + 0x1dc8));
  if (*(short *)(iVar3 + 0x6f6) == 4) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801cffe4  FUN_801cffe4 ====

void FUN_801cffe4(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  return;
}



// ==== 801cfff4  FUN_801cfff4 ====

void FUN_801cfff4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801d0014  FUN_801d0014 ====

void FUN_801d0014(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  iVar1 = *(int *)(param_9 + *(char *)(param_9 + 0x13) * 4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,0x44);
  return;
}



// ==== 801d0064  FUN_801d0064 ====

/* WARNING: Removing unreachable block (ram,0x801d010c) */
/* WARNING: Removing unreachable block (ram,0x801d00e4) */

void FUN_801d0064(int param_1)

{
  int iVar1;
  float afStack_38 [12];
  
  iVar1 = *(int *)(param_1 + 0x90);
  gnt4_PSMTXCopy_bl((float *)(iVar1 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
                    (float *)(param_1 + 0x114));
  *(undefined4 *)(param_1 + 0x120) =
       *(undefined4 *)(iVar1 + *(char *)(param_1 + 0x12) * 0x30 + 0x8e0);
  *(undefined4 *)(param_1 + 0x130) =
       *(undefined4 *)(iVar1 + *(char *)(param_1 + 0x12) * 0x30 + 0x8f0);
  *(undefined4 *)(param_1 + 0x140) =
       *(undefined4 *)(iVar1 + *(char *)(param_1 + 0x12) * 0x30 + 0x900);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043bdbc *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                             0x3ff0000000000000)),afStack_38,0x79);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043bdbc *
                                     (double)((longlong)(double)*(short *)(param_1 + 0x70) *
                                             0x3ff0000000000000)),afStack_38,0x78);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),(double)*(float *)(param_1 + 0x5c),
                     (double)*(float *)(param_1 + 0x60),afStack_38);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
  return;
}



// ==== 801d0170  zz_01d0170_ ====

void zz_01d0170_(undefined4 param_1)

{
  char *pcVar1;
  undefined1 *puVar2;
  
  for (pcVar1 = &DAT_8038a900; -1 < *pcVar1; pcVar1 = pcVar1 + 0x24) {
    puVar2 = zz_008893c_(2,0x28,0,(int)pcVar1[3]);
    if (puVar2 != (undefined1 *)0x0) {
      *puVar2 = 1;
      puVar2[0x10] = 0;
      *(code **)(puVar2 + 0xc) = FUN_801d0220;
      *(code **)(puVar2 + 0x10c) = FUN_801d0368;
      *(char **)(puVar2 + 0x54) = pcVar1;
      *(undefined4 *)(puVar2 + 0x8c) = param_1;
      puVar2[0x11] = *pcVar1;
      puVar2[0x12] = pcVar1[1];
    }
  }
  return;
}



// ==== 801d0220  FUN_801d0220 ====

void FUN_801d0220(int param_1)

{
  (*(code *)(&PTR_FUN_8038ac60)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801d025c  FUN_801d025c ====

void FUN_801d025c(int param_1)

{
  int iVar1;
  
  iVar1 = zz_000a3c4_();
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 1;
    *(undefined4 *)(param_1 + 0xdc) = 0;
    *(undefined1 *)(param_1 + 0x82) = 1;
    (*(code *)(&PTR_FUN_8038ac70)[*(char *)(param_1 + 0x11)])(param_1);
    zz_01d02d0_(param_1);
  }
  return;
}



// ==== 801d02d0  zz_01d02d0_ ====

void zz_01d02d0_(int param_1)

{
  (*(code *)(&PTR_LAB_8038ac8c)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801d0320  FUN_801d0320 ====

void FUN_801d0320(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801d0368  FUN_801d0368 ====

void FUN_801d0368(int param_1)

{
  (*(code *)(&PTR_FUN_8038aca8)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801d03a4  FUN_801d03a4 ====

void FUN_801d03a4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x84) = 0xf;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  iVar2 = *(int *)(param_9 + 0x54);
  uVar1 = *(undefined4 *)(iVar2 + 8);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(iVar2 + 4);
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(iVar2 + 0xc);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(iVar2 + 0x1c);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(iVar2 + 0x20);
  zz_0006fb4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb364,
              *(int *)(param_9 + 0xe0),(int)*(char *)(iVar2 + 2),param_12,param_13,param_14,param_15
              ,param_16);
  return;
}



// ==== 801d0478  FUN_801d0478 ====

void FUN_801d0478(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 801d04b8  FUN_801d04b8 ====

void FUN_801d04b8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x84) = 0xf;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  iVar2 = *(int *)(param_9 + 0x54);
  uVar1 = *(undefined4 *)(iVar2 + 8);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(iVar2 + 4);
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(iVar2 + 0xc);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(iVar2 + 0x1c);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(iVar2 + 0x20);
  uVar3 = zz_0006fb4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb364,
                      *(int *)(param_9 + 0xe0),(int)*(char *)(iVar2 + 2),param_12,param_13,param_14,
                      param_15,param_16);
  if ('\x01' < *(char *)(param_9 + 0x99)) {
    zz_0006fb4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb364,
                *(int *)(param_9 + 0xe4),10,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801d0570  FUN_801d0570 ====

void FUN_801d0570(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x8c);
  iVar2 = *(char *)(param_1 + 0x12) * 2;
  cVar1 = *(char *)(iVar3 + 0x15);
  if ((cVar1 < (char)(&DAT_8038acec)[iVar2]) || ((char)(&DAT_8038aced)[iVar2] < cVar1)) {
    zz_0007cd0_(*(int *)(param_1 + 0xe0),0,0x9a,0);
    if ('\x01' < *(char *)(param_1 + 0x99)) {
      zz_0007cd0_(*(int *)(param_1 + 0xe4),0,0x9a,0);
    }
  }
  else {
    zz_0007cd0_(*(int *)(param_1 + 0xe0),0x33,0xcd,0x33);
    if ('\x01' < *(char *)(param_1 + 0x99)) {
      zz_0007cd0_(*(int *)(param_1 + 0xe4),0x33,0xcd,0x33);
    }
  }
  if (*(int *)(iVar3 + 0x2c) == 0) {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  return;
}



// ==== 801d0678  FUN_801d0678 ====

void FUN_801d0678(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  uVar1 = zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  if ('\x01' < *(char *)(param_9 + 0x99)) {
    zz_00076d0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe4),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe4),0x44);
  }
  return;
}



// ==== 801d06d4  FUN_801d06d4 ====

void FUN_801d06d4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x84) = 0xf;
  *(code **)(param_9 + 0x100) = FUN_80047c38;
  uVar3 = zz_0089100_(param_9,0,1);
  iVar2 = *(int *)(param_9 + 0x54);
  uVar1 = *(undefined4 *)(iVar2 + 8);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(iVar2 + 4);
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(iVar2 + 0xc);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(iVar2 + 0x1c);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(iVar2 + 0x20);
  zz_0006fb4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb364,
              *(int *)(param_9 + 0xe0),(int)*(char *)(iVar2 + 2),param_12,param_13,param_14,param_15
              ,param_16);
  return;
}



// ==== 801d0820  FUN_801d0820 ====

void FUN_801d0820(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x47);
  return;
}



// ==== 801d0860  FUN_801d0860 ====

void FUN_801d0860(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x84) = 0xf;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  iVar2 = *(int *)(param_9 + 0x54);
  uVar1 = *(undefined4 *)(iVar2 + 8);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(iVar2 + 4);
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(iVar2 + 0xc);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(iVar2 + 0x1c);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(iVar2 + 0x20);
  zz_0006fb4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb364,
              *(int *)(param_9 + 0xe0),(int)*(char *)(iVar2 + 2),param_12,param_13,param_14,param_15
              ,param_16);
  return;
}



// ==== 801d08f0  FUN_801d08f0 ====

void FUN_801d08f0(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined4 extraout_r4;
  int iVar2;
  undefined8 uVar3;
  
  cVar1 = *(char *)(param_9 + 0x12);
  iVar2 = *(int *)(param_9 + 0x8c);
  if (cVar1 == '\x01') {
    param_2 = (double)FLOAT_8043bdc0;
    param_1 = (double)(float)(param_2 +
                             (double)(float)((double)CONCAT44(0x43300000,
                                                              (int)(char)PTR_DAT_8043394c[0x2d] ^
                                                              0x80000000) - DOUBLE_8043bdc8));
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      param_2 = (double)FLOAT_8043bdc0;
      param_1 = (double)(float)(param_2 +
                               (double)(float)((double)CONCAT44(0x43300000,
                                                                (int)(char)PTR_DAT_8043394c[0x2c] ^
                                                                0x80000000) - DOUBLE_8043bdc8));
    }
  }
  else if (cVar1 < '\x03') {
    param_2 = (double)FLOAT_8043bdc0;
    param_1 = (double)(float)(param_2 +
                             (double)(float)((double)CONCAT44(0x43300000,
                                                              (int)(char)PTR_DAT_8043394c[0x2e] ^
                                                              0x80000000) - DOUBLE_8043bdc8));
  }
  uVar3 = zz_00086b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb364,
                      *(int *)(param_9 + 0xe0),param_11,param_12,param_13,param_14,param_15,param_16
                     );
  zz_0007c30_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  if (*(int *)(iVar2 + 0x2c) == 0) {
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 801d0a24  FUN_801d0a24 ====

void FUN_801d0a24(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x47);
  return;
}



// ==== 801d0a64  FUN_801d0a64 ====

void FUN_801d0a64(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x84) = 0xf;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  iVar2 = *(int *)(param_9 + 0x54);
  uVar1 = *(undefined4 *)(iVar2 + 8);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(iVar2 + 4);
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(iVar2 + 0xc);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(iVar2 + 0x1c);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(iVar2 + 0x20);
  uVar3 = zz_0006fb4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb364,
                      *(int *)(param_9 + 0xe0),(int)*(char *)(iVar2 + 2),param_12,param_13,param_14,
                      param_15,param_16);
  if ('\x01' < *(char *)(param_9 + 0x99)) {
    zz_0006fb4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb364,
                *(int *)(param_9 + 0xe4),10,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801d0b1c  FUN_801d0b1c ====

void FUN_801d0b1c(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x8c);
  if ((int)*(char *)(iVar1 + 0x15) == *(int *)(&DAT_8038ad20 + *(char *)(param_1 + 0x12) * 4)) {
    zz_0007cd0_(*(int *)(param_1 + 0xe0),0x33,0xcd,0x33);
    if ('\x01' < *(char *)(param_1 + 0x99)) {
      zz_0007cd0_(*(int *)(param_1 + 0xe4),0x33,0xcd,0x33);
    }
  }
  else {
    zz_0007cd0_(*(int *)(param_1 + 0xe0),0,0x9a,0);
    if ('\x01' < *(char *)(param_1 + 0x99)) {
      zz_0007cd0_(*(int *)(param_1 + 0xe4),0,0x9a,0);
    }
  }
  if (*(int *)(iVar1 + 0x2c) == 0) {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  return;
}



// ==== 801d0c0c  FUN_801d0c0c ====

void FUN_801d0c0c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined8 uVar1;
  
  uVar1 = zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  if ('\x01' < *(char *)(param_9 + 0x99)) {
    zz_00076d0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe4),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe4),0x44);
  }
  return;
}



// ==== 801d0c68  FUN_801d0c68 ====

void FUN_801d0c68(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  int iVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x84) = 0xf;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  iVar2 = *(int *)(param_9 + 0x54);
  uVar1 = *(undefined4 *)(iVar2 + 8);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(iVar2 + 4);
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(iVar2 + 0xc);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(iVar2 + 0x1c);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(iVar2 + 0x20);
  uVar3 = zz_0006fb4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb364,
                      *(int *)(param_9 + 0xe0),(int)*(char *)(iVar2 + 2),param_12,param_13,param_14,
                      param_15,param_16);
  zz_0006fb4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb364,
              *(int *)(param_9 + 0xe4),(int)(char)(&DAT_80435ab4)[*(char *)(param_9 + 0x12)],
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801d0d20  FUN_801d0d20 ====

void FUN_801d0d20(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  float *pfVar3;
  int iVar4;
  undefined8 uVar5;
  undefined1 local_28 [20];
  
  pfVar3 = (float *)0x0;
  iVar4 = *(int *)(param_9 + 0x8c);
  iVar2 = (int)*(char *)(param_9 + 0x12);
  if (iVar2 == 0) {
    pfVar3 = (float *)(PTR_DAT_8043394c + 0x2b);
  }
  else if ((-1 < iVar2) && (iVar2 < 5)) {
    pfVar3 = (float *)local_28;
    uVar1 = countLeadingZeros((int)(char)PTR_DAT_8043394c[0x30] & 1 << iVar2 + -1);
    local_28[0] = (char)(uVar1 >> 5);
  }
  if (pfVar3 != (float *)0x0) {
    uVar1 = -(int)*(char *)pfVar3 | (int)*(char *)pfVar3;
    iVar2 = param_9 + (uVar1 >> 0x1d & 4);
    uVar5 = zz_00086b8_((double)FLOAT_8043bdc0,param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,DAT_803bb364,*(int *)(iVar2 + 0xe0),pfVar3,param_12,param_13,
                        param_14,param_15,param_16);
    zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0xe0)
                ,extraout_r4,pfVar3,param_12,param_13,param_14,param_15,param_16);
    iVar2 = param_9 + (uVar1 >> 0x1f ^ 1) * 4;
    uVar5 = zz_00086b8_((double)FLOAT_8043bdd0,param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,DAT_803bb364,*(int *)(iVar2 + 0xe0),pfVar3,param_12,param_13,
                        param_14,param_15,param_16);
    zz_0007c30_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0xe0)
                ,extraout_r4_00,pfVar3,param_12,param_13,param_14,param_15,param_16);
  }
  if (*(int *)(iVar4 + 0x2c) == 0) {
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 801d0e2c  FUN_801d0e2c ====

void FUN_801d0e2c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined *puVar2;
  undefined *puVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  float afStack_38 [13];
  
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  if ('\x01' < *(char *)(param_9 + 0x99)) {
    puVar3 = &DAT_8038ad3c;
    iVar1 = *(char *)(param_9 + 0x12) * 0xc;
    puVar2 = &DAT_8038ad3c + iVar1;
    dVar5 = (double)*(float *)(&DAT_8038ad40 + iVar1);
    dVar6 = (double)*(float *)(&DAT_8038ad44 + iVar1);
    uVar4 = zz_020b4ac_((double)*(float *)(&DAT_8038ad3c + iVar1),dVar5,dVar6,
                        (float *)(param_9 + 0x114),afStack_38);
    zz_00076d0_(uVar4,dVar5,dVar6,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4),
                afStack_38,puVar2,puVar3,param_13,param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe4),0x44);
  }
  return;
}



// ==== 801d0ec4  FUN_801d0ec4 ====

void FUN_801d0ec4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  undefined8 uVar2;
  
  uVar2 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb364,
                      *(int *)(param_9 + 0xe0),0x15,param_12,param_13,param_14,param_15,param_16);
  zz_0006fb4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb364,
              *(int *)(param_9 + 0xe4),0x16,param_12,param_13,param_14,param_15,param_16);
  piVar1 = zz_0006dc8_(0x18);
  *(int **)(param_9 + 0xdc) = piVar1;
  if (*(int *)(param_9 + 0xdc) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801d0f3c  FUN_801d0f3c ====

void FUN_801d0f3c(int param_1)

{
  if (*(char *)(param_1 + 0x19) == '\0') {
    if (PTR_DAT_80433940[0x19] != '\0') {
      *(undefined1 *)(param_1 + 0x19) = 1;
      zz_000804c_(*(int *)(param_1 + 0xe0),DAT_80436228,*(int **)(*(int *)(param_1 + 0xdc) + 0xc));
    }
  }
  else if (PTR_DAT_80433940[0x19] == '\0') {
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  return;
}



// ==== 801d0fbc  FUN_801d0fbc ====

void FUN_801d0fbc(int param_1)

{
  if (PTR_DAT_80433940[0x19] != '\0') {
    zz_00097b4_(*(int *)(param_1 + 0xe0),1);
    zz_00097b4_(*(int *)(param_1 + 0xe4),0x44);
  }
  return;
}



// ==== 801d100c  zz_01d100c_ ====

void zz_01d100c_(undefined1 param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x39,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x11] = param_1;
    *(code **)(puVar1 + 0xc) = FUN_801d10a4;
    *(code **)(puVar1 + 0x10c) = FUN_801d1768;
    *(undefined **)(puVar1 + 0x164) = (&PTR_DAT_8035b208)[*(int *)(DAT_80436354 + 0x84)];
    *(undefined4 *)(DAT_80436354 + 0x80) = 0;
    *(undefined4 *)(DAT_80436354 + 0x88) = 0;
  }
  return;
}



// ==== 801d10a4  FUN_801d10a4 ====

void FUN_801d10a4(int param_1)

{
  (*(code *)(&PTR_FUN_8038ad84)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801d10e0  FUN_801d10e0 ====

void FUN_801d10e0(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  
  iVar5 = zz_01d1870_(param_1);
  if (iVar5 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 1;
    *(undefined1 *)(param_1 + 0x84) = 0x1f;
    *(code **)(param_1 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_1,0,1);
    fVar1 = FLOAT_8043bdd8;
    *(undefined2 *)(param_1 + 0x74) = 0;
    fVar2 = FLOAT_8043bddc;
    *(undefined2 *)(param_1 + 0x72) = 0;
    fVar3 = FLOAT_8043bde0;
    *(undefined2 *)(param_1 + 0x70) = 0;
    fVar4 = FLOAT_8043bde4;
    *(float *)(param_1 + 0x60) = fVar1;
    *(float *)(param_1 + 0x5c) = fVar1;
    *(float *)(param_1 + 0x58) = fVar1;
    *(float *)(param_1 + 100) = fVar2;
    *(float *)(param_1 + 0x68) = fVar3;
    *(float *)(param_1 + 0x6c) = fVar4;
    zz_01d1180_(param_1);
  }
  return;
}



// ==== 801d1180  zz_01d1180_ ====

void zz_01d1180_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_01d189c_(param_1);
  if (iVar1 == 0) {
    (*(code *)(&PTR_FUN_8038ad94)[*(char *)(param_1 + 0x19)])(param_1);
  }
  return;
}



// ==== 801d11d8  FUN_801d11d8 ====

void FUN_801d11d8(int param_1)

{
  char cVar1;
  byte bVar2;
  uint uVar3;
  byte *pbVar4;
  byte *pbVar5;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      goto LAB_801d1258;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    if (*(char *)(param_1 + 0x11) == '\0') {
      *(undefined1 *)(param_1 + 0x82) = 7;
    }
    else {
      *(undefined1 *)(param_1 + 0x82) = 0x11;
    }
  }
  *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  *(undefined4 *)(param_1 + 0x144) = 0;
LAB_801d1258:
  pbVar4 = *(byte **)(param_1 + 0x164);
  uVar3 = (uint)*pbVar4;
  pbVar5 = pbVar4 + 1;
  if (uVar3 == 0) {
    *(undefined1 *)(param_1 + 0x19) = 1;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    bVar2 = *pbVar5;
    pbVar5 = pbVar4 + 2;
    *(uint *)(param_1 + 0x148) = (uint)bVar2;
  }
  else if (uVar3 == 1) {
    bVar2 = *pbVar5;
    pbVar5 = pbVar4 + 3;
    zz_00ea170_((uint)bVar2,0,-1,(uint)pbVar4[2]);
  }
  else if (uVar3 == 2) {
    if (*pbVar5 == 0) {
      zz_01d1918_(param_1);
    }
    else {
      zz_01d1968_(param_1);
    }
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else if (uVar3 == 3) {
    *(undefined1 *)(param_1 + 0x19) = 2;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    bVar2 = *pbVar5;
    pbVar5 = pbVar4 + 2;
    *(ushort *)(param_1 + 0x1c) = (ushort)bVar2;
    zz_01d1918_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x19) = 3;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(uint *)(param_1 + 0x168) = uVar3 - 4;
    zz_01d1918_(param_1);
  }
  *(byte **)(param_1 + 0x164) = pbVar5;
  return;
}



// ==== 801d1358  FUN_801d1358 ====

void FUN_801d1358(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined8 uVar4;
  double dVar5;
  
  cVar1 = *(char *)(param_9 + 0x1a);
  if (cVar1 == '\x03') {
    sVar2 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar2;
    if (0 < sVar2) {
      return;
    }
    *(char *)(param_9 + 0x1a) = *(char *)(param_9 + 0x1a) + '\x01';
    return;
  }
  if (cVar1 < '\x03') {
    if (cVar1 != '\x01') {
      if ('\0' < cVar1) {
        if (((*(uint *)(DAT_80436354 + 0x18) & 0x100) == 0) && (*(int *)(param_9 + 0x160) == 0)) {
          iVar3 = *(int *)(param_9 + 0x158) + 1;
          *(int *)(param_9 + 0x158) = iVar3;
          if (iVar3 < 4) {
            return;
          }
          *(int *)(param_9 + 0x15c) = *(int *)(param_9 + 0x15c) + 1;
          *(undefined4 *)(param_9 + 0x158) = 0;
          return;
        }
        *(char *)(param_9 + 0x1a) = *(char *)(param_9 + 0x1a) + '\x01';
        *(undefined2 *)(param_9 + 0x1c) = 8;
        *(undefined4 *)(param_9 + 0x15c) = 0xffffffff;
        return;
      }
      if (cVar1 < '\0') {
        return;
      }
      param_11 = (float *)0x0;
      *(char *)(param_9 + 0x1a) = cVar1 + '\x01';
      *(undefined2 *)(param_9 + 0x1c) = 0;
      *(undefined2 *)(param_9 + 0x1e) = 8;
      *(undefined4 *)(param_9 + 0x144) = 1;
      *(undefined4 *)(param_9 + 0x15c) = 0;
      uVar4 = zz_01d18d8_(param_9);
      zz_01d1668_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    }
    sVar2 = *(short *)(param_9 + 0x1c) + 1;
    *(short *)(param_9 + 0x1c) = sVar2;
    if (*(short *)(param_9 + 0x1e) <= sVar2) {
      *(char *)(param_9 + 0x1a) = *(char *)(param_9 + 0x1a) + '\x01';
      *(undefined4 *)(param_9 + 0x158) = 0;
      *(undefined4 *)(param_9 + 0x160) = 0;
      zz_01d79d0_(param_9);
    }
  }
  else {
    if (cVar1 != '\x05') {
      if ('\x04' < cVar1) {
        return;
      }
      if ((*(uint *)(DAT_80436354 + 0x18) & 0x100) == 0) {
        return;
      }
      *(char *)(param_9 + 0x1a) = cVar1 + '\x01';
      *(undefined2 *)(param_9 + 0x1e) = 8;
      *(undefined2 *)(param_9 + 0x1c) = 8;
      *(undefined4 *)(param_9 + 0x15c) = 0;
    }
    sVar2 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar2;
    if (sVar2 < 1) {
      *(undefined1 *)(param_9 + 0x19) = 0;
      *(undefined1 *)(param_9 + 0x1a) = 2;
      *(undefined4 *)(param_9 + 0x144) = 0;
    }
  }
  dVar5 = zz_0045204_((short)(((int)*(short *)(param_9 + 0x1c) << 0xe) /
                             (int)*(short *)(param_9 + 0x1e)));
  dVar5 = (double)(float)((double)*(float *)(param_9 + 0x154) * dVar5);
  iVar3 = *(int *)(param_9 + 0xe0);
  zz_0008614_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x54)
              ,iVar3,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_0007c30_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,iVar3,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_0007cac_((double)((FLOAT_8043bde8 *
                       (float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(param_9 + 0x1c) ^ 0x80000000) -
                              DOUBLE_8043bdf0)) /
                      (float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_9 + 0x1e) ^ 0x80000000) -
                             DOUBLE_8043bdf0)),*(int *)(param_9 + 0xe0));
  return;
}



// ==== 801d15b8  FUN_801d15b8 ====

void FUN_801d15b8(int param_1)

{
  char cVar1;
  int iVar2;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x1a) = cVar1 + '\x01';
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined2 *)(param_1 + 0x1c) = 0;
  }
  iVar2 = zz_01d19b8_(param_1);
  if (iVar2 != 0) {
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 2;
  }
  return;
}



// ==== 801d1648  FUN_801d1648 ====

void FUN_801d1648(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801d1668  zz_01d1668_ ====

void zz_01d1668_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  undefined4 extraout_r4;
  int iVar2;
  uint *puVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar4;
  undefined8 uVar5;
  double dVar6;
  uint local_18;
  int local_14 [4];
  
  puVar3 = &local_18;
  dVar4 = (double)zz_009749c_(0,*(int *)(param_9 + 0x148),local_14,puVar3);
  *(int *)(param_9 + 0x150) = local_14[0];
  dVar6 = DOUBLE_8043bdf0;
  uVar1 = *(uint *)(param_9 + 0x150);
  if ((int)uVar1 < 10) {
    *(float *)(param_9 + 0x154) = FLOAT_8043bdf8;
    dVar6 = param_2;
  }
  else if ((int)uVar1 < 0x29) {
    local_14[2] = uVar1 ^ 0x80000000;
    local_14[1] = 0x43300000;
    dVar4 = (double)(float)((double)CONCAT44(0x43300000,local_14[2]) - DOUBLE_8043bdf0);
    *(float *)(param_9 + 0x154) = (float)(dVar4 * (double)FLOAT_8043be00);
  }
  else {
    *(float *)(param_9 + 0x154) = FLOAT_8043bdfc;
    dVar6 = param_2;
  }
  if ((int)local_18 < 2) {
    local_18 = 2;
  }
  else if (4 < (int)local_18) {
    local_18 = 4;
  }
  *(uint *)(param_9 + 0x14c) = local_18 - 2;
  *(undefined4 *)(param_9 + 0x54) = DAT_803bb344;
  iVar2 = (int)(char)(&DAT_80435ac0)[*(int *)(param_9 + 0x14c)];
  uVar5 = zz_0006fb4_(dVar4,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),iVar2,puVar3,in_r7,in_r8,
                      in_r9,in_r10);
  zz_0007c54_(uVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0),
              extraout_r4,iVar2,puVar3,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 801d1768  FUN_801d1768 ====

void FUN_801d1768(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  short sVar2;
  undefined4 uVar3;
  
  if (*(int *)(param_9 + 0x144) != 0) {
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
    zz_0096d0c_((double)FLOAT_8043bdd8);
    zz_0096d14_((double)FLOAT_8043bdfc);
    iVar1 = 0x28;
    if (*(int *)(param_9 + 0x150) < 0x29) {
      iVar1 = *(int *)(param_9 + 0x150);
    }
    uVar3 = *(undefined4 *)(&DAT_8038ad78 + *(int *)(param_9 + 0x14c) * 4);
    sVar2 = (short)((iVar1 * -10 + 0x280) / 2) + 0x20;
    if (*(char *)(param_9 + 0x11) == '\0') {
      zz_00097b4_(*(int *)(param_9 + 0xe0),0x45);
      uVar3 = zz_00970b4_(sVar2,(short)uVar3,0,'\0',(short)*(undefined4 *)(param_9 + 0x148),
                          *(int *)(param_9 + 0x15c));
      *(undefined4 *)(param_9 + 0x160) = uVar3;
    }
    else {
      zz_0009958_(*(int *)(param_9 + 0xe0),2);
      uVar3 = zz_00970fc_(sVar2,(short)uVar3,0,'\0',(short)*(undefined4 *)(param_9 + 0x148),
                          *(int *)(param_9 + 0x15c));
      *(undefined4 *)(param_9 + 0x160) = uVar3;
    }
  }
  return;
}



// ==== 801d1870  zz_01d1870_ ====

undefined4 zz_01d1870_(int param_1)

{
  if ((*(char *)(param_1 + 0x11) != '\0') && (PTR_DAT_80433934[0x45] != '\x03')) {
    return 1;
  }
  return 0;
}



// ==== 801d189c  zz_01d189c_ ====

undefined4 zz_01d189c_(int param_1)

{
  if ((*(char *)(param_1 + 0x11) != '\0') && (PTR_DAT_80433934[0x45] == '\x05')) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
    return 1;
  }
  return 0;
}



// ==== 801d18d8  zz_01d18d8_ ====

void zz_01d18d8_(int param_1)

{
  if (*(char *)(param_1 + 0x11) == '\0') {
    PTR_DAT_80435a30[0x148] = 2;
  }
  else {
    zz_008b038_('\x01');
  }
  return;
}



// ==== 801d1918  zz_01d1918_ ====

void zz_01d1918_(int param_1)

{
  if (*(char *)(param_1 + 0x11) == '\0') {
    PTR_DAT_80435a30[0x148] = 0;
  }
  else {
    zz_008b038_('\0');
    zz_0066350_((int)(char)PTR_DAT_80433930[2]);
  }
  return;
}



// ==== 801d1968  zz_01d1968_ ====

void zz_01d1968_(int param_1)

{
  if (*(char *)(param_1 + 0x11) == '\0') {
    PTR_DAT_80435a30[0x148] = 0;
  }
  else {
    zz_008b038_('\x02');
    zz_0066350_((int)(char)PTR_DAT_80433930[2]);
  }
  return;
}



// ==== 801d19b8  zz_01d19b8_ ====

void zz_01d19b8_(int param_1)

{
  (*(code *)(&PTR_LAB_8038ada4)[*(int *)(param_1 + 0x168)])();
  return;
}



// ==== 801d2078  zz_01d2078_ ====

void zz_01d2078_(void)

{
  bool bVar1;
  int *piVar2;
  int iVar3;
  
  bVar1 = 1 < *(uint *)(DAT_80436354 + 0x68);
  if (bVar1) {
    piVar2 = (int *)0x8038ae6c;
  }
  else {
    piVar2 = &DAT_8038ade0;
  }
  for (; -1 < *piVar2; piVar2 = piVar2 + 5) {
    iVar3 = zz_01a7538_(4,piVar2);
    if (iVar3 != 0) {
      *(code **)(iVar3 + 0xc) = FUN_801d23fc;
      *(code **)(iVar3 + 0x10c) = FUN_801d2f30;
      *(bool *)(iVar3 + 0x12) = bVar1;
    }
  }
  gnt4_C_MTXLookAt_bl((float *)&DAT_803c7380,(float *)&DAT_8038b13c,(float *)&DAT_8038b154,
                      (float *)&DAT_8038b148);
  *(undefined **)(PTR_DAT_80433930 + 0x14) = &DAT_803c7380;
  PTR_DAT_80433930[0xc] = 0xff;
  *(undefined **)(PTR_DAT_80433930 + 0x18) = &DAT_803c7380;
  PTR_DAT_80433930[0xd] = 0xff;
  *(undefined **)(PTR_DAT_80433930 + 0x1c) = &DAT_803c7380;
  PTR_DAT_80433930[0xe] = 0xff;
  *(undefined **)(PTR_DAT_80433930 + 0x20) = &DAT_803c7380;
  PTR_DAT_80433930[0xf] = 0xff;
  *(undefined **)(PTR_DAT_80433930 + 0x24) = &DAT_803c7380;
  PTR_DAT_80433930[0x10] = 0xff;
  return;
}



// ==== 801d21ac  zz_01d21ac_ ====

void zz_01d21ac_(void)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_8038af0c; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(4,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = FUN_801d23fc;
      *(code **)(iVar2 + 0x10c) = FUN_801d2f30;
      *(undefined1 *)(iVar2 + 0x12) = 2;
    }
  }
  *(undefined2 *)(DAT_80436354 + 0x2a) = 0;
  return;
}



// ==== 801d2248  zz_01d2248_ ====

void zz_01d2248_(void)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_8038af98; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(4,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = FUN_801d23fc;
      *(code **)(iVar2 + 0x10c) = FUN_801d2f30;
      *(undefined1 *)(iVar2 + 0x12) = 4;
    }
  }
  return;
}



// ==== 801d22d8  zz_01d22d8_ ====

void zz_01d22d8_(int param_1)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)0x8038b010;
  if (param_1 != 0) {
    piVar1 = &DAT_8038b09c;
  }
  for (; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = nlQSort<20AnimAudioEventLookup>_AnimAudioEventLookup(4,piVar1,0x15);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = FUN_801d23fc;
      *(code **)(iVar2 + 0x10c) = FUN_801d2f30;
      *(undefined1 *)(iVar2 + 0x12) = 3;
    }
  }
  gnt4_C_MTXLookAt_bl((float *)&DAT_803c7380,(float *)&DAT_8038b160,(float *)&DAT_8038b178,
                      (float *)&DAT_8038b16c);
  *(undefined **)(PTR_DAT_80433930 + 0x14) = &DAT_803c7380;
  PTR_DAT_80433930[0xc] = 0xff;
  *(undefined **)(PTR_DAT_80433930 + 0x18) = &DAT_803c7380;
  PTR_DAT_80433930[0xd] = 0xff;
  *(undefined **)(PTR_DAT_80433930 + 0x1c) = &DAT_803c7380;
  PTR_DAT_80433930[0xe] = 0xff;
  *(undefined **)(PTR_DAT_80433930 + 0x20) = &DAT_803c7380;
  PTR_DAT_80433930[0xf] = 0xff;
  *(undefined **)(PTR_DAT_80433930 + 0x24) = &DAT_803c7380;
  PTR_DAT_80433930[0x10] = 0xff;
  return;
}



// ==== 801d23fc  FUN_801d23fc ====

void FUN_801d23fc(int param_1)

{
  (*(code *)(&PTR_FUN_8038b184)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801d2438  FUN_801d2438 ====

void FUN_801d2438(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 uVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  uVar2 = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043be08;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  zz_01a7688_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar2,param_12
              ,param_13,param_14,param_15,param_16);
  zz_01d24bc_(param_9);
  return;
}



// ==== 801d24bc  zz_01d24bc_ ====

void zz_01d24bc_(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x12);
  if (cVar1 == '\x03') goto LAB_801d252c;
  if (cVar1 < '\x03') {
    if ('\x01' < cVar1) {
      if (DAT_80436354[1] != '\n') {
        *(undefined1 *)(param_1 + 0x18) = 2;
      }
      goto LAB_801d252c;
    }
    if (cVar1 < '\0') goto LAB_801d252c;
  }
  else if ('\x04' < cVar1) goto LAB_801d252c;
  if (*DAT_80436354 != '\x01') {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
LAB_801d252c:
  (*(code *)(&PTR_FUN_8038b194)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801d255c  FUN_801d255c ====

void FUN_801d255c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      zz_01d2634_(param_9);
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined1 *)(param_9 + 0x82) = 7;
    *(undefined4 *)(DAT_80436354 + 0x2c) = 1;
  }
  zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_9 + 0x1c) ^ 0x80000000) -
                             DOUBLE_8043be10),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,param_9,0,param_11,param_12,param_13,param_14,param_15,param_16);
  sVar2 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar2;
  if (0x14 < sVar2) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined1 *)(param_9 + 0x1a) = 0;
  }
  return;
}



// ==== 801d2634  zz_01d2634_ ====

void zz_01d2634_(int param_1)

{
  if (*(char *)(param_1 + 0x12) != '\x02') {
    return;
  }
  if (*(short *)(DAT_80436354 + 0x2a) == 0) {
    return;
  }
  *(undefined1 *)(param_1 + 0x19) = 10;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801d2664  FUN_801d2664 ====

void FUN_801d2664(int param_1)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      goto LAB_801d26cc;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 5;
  }
  sVar2 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (0 < sVar2) {
    return;
  }
  *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
LAB_801d26cc:
  sVar2 = *(short *)(DAT_80436354 + 0x24);
  if ((int)sVar2 < (int)(char)(&DAT_80435acc)[*(char *)(param_1 + 0x12)]) {
    *(undefined1 *)(param_1 + 0x82) = 7;
    *(undefined4 *)(param_1 + 0x68) =
         *(undefined4 *)
          (&DAT_8038b128 + ((int)(char)(&DAT_80435ac8)[*(char *)(param_1 + 0x12)] + (int)sVar2) * 4)
    ;
    zz_01d2634_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801d2744  FUN_801d2744 ====

void FUN_801d2744(int param_1)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
LAB_801d2794:
    sVar2 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar2;
    if (0 < sVar2) goto LAB_801d2820;
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') goto LAB_801d2820;
      *(char *)(param_1 + 0x19) = cVar1 + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 5;
      goto LAB_801d2794;
    }
    if ('\x02' < cVar1) goto LAB_801d2820;
  }
  sVar2 = *(short *)(DAT_80436354 + 0x24);
  if ((int)sVar2 < (int)(char)(&DAT_80435acc)[*(char *)(param_1 + 0x12)]) {
    *(undefined1 *)(param_1 + 0x82) = 7;
    *(undefined4 *)(param_1 + 0x68) =
         *(undefined4 *)
          (&DAT_8038b128 + ((int)(char)(&DAT_80435ac8)[*(char *)(param_1 + 0x12)] + (int)sVar2) * 4)
    ;
    zz_01d2634_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
LAB_801d2820:
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + -0x100;
  return;
}



// ==== 801d2840  FUN_801d2840 ====

void FUN_801d2840(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  short sVar3;
  float *pfVar4;
  int iVar5;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if ('\x03' < cVar1) {
        return;
      }
      fVar2 = FLOAT_8043be18;
      if (((uint)DAT_80436354[4] & 4) != 0) {
        fVar2 = FLOAT_8043be08;
      }
      zz_01a76fc_((double)fVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                  DAT_80436354,param_12,param_13,param_14,param_15,param_16);
      if (DAT_80436354[4] == 0.0) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + -1;
        *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
      }
      zz_01d2634_(param_9);
      return;
    }
    if (cVar1 == '\0') {
      *(undefined1 *)(param_9 + 0x19) = 1;
      *(undefined2 *)(param_9 + 0x1c) = 5;
      *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
    }
    else if (cVar1 < '\0') {
      return;
    }
    sVar3 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar3;
    if (0 < sVar3) {
      return;
    }
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined1 *)(param_9 + 0x82) = 7;
  }
  pfVar4 = (float *)(int)*(short *)(DAT_80436354 + 9);
  iVar5 = *(char *)(param_9 + 0x11) + -3;
  if (*(float **)(param_9 + 0x180) != pfVar4) {
    *(float **)(param_9 + 0x180) = pfVar4;
    fVar2 = FLOAT_8043be1c;
    if (*(int *)(param_9 + 0x180) == iVar5) {
      fVar2 = FLOAT_8043be18;
    }
    zz_01a76fc_((double)fVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                pfVar4,param_12,param_13,param_14,param_15,param_16);
  }
  zz_01d2634_(param_9);
  if ((*(int *)(param_9 + 0x180) == iVar5) && (DAT_80436354[4] != 0.0)) {
    cVar1 = *(char *)(param_9 + 0x12);
    if (cVar1 < '\x02') {
      if ((-1 < cVar1) && (*(char *)((int)DAT_80436354 + 1) == '\x01')) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      }
    }
    else if (cVar1 < '\x04') {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    }
  }
  return;
}



// ==== 801d29f0  FUN_801d29f0 ====

void FUN_801d29f0(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_1 + 0x19) = cVar1 + '\x01';
    *(undefined1 *)(param_1 + 0x82) = 7;
  }
  zz_01d2634_(param_1);
  return;
}



// ==== 801d2a40  FUN_801d2a40 ====

void FUN_801d2a40(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if (('\0' < cVar1) || (cVar1 < '\0')) goto LAB_801d2af0;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined1 *)(param_9 + 0x82) = 7;
    *(undefined4 *)(DAT_80436354 + 0x2c) = 1;
  }
  zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_9 + 0x1c) ^ 0x80000000) -
                             DOUBLE_8043be10),param_2,param_3,param_4,param_5,param_6,param_7,
              param_8,param_9,0,param_11,param_12,param_13,param_14,param_15,param_16);
  sVar2 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar2;
  if (0x14 < sVar2) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined1 *)(param_9 + 0x1a) = 0;
  }
LAB_801d2af0:
  if (*(char *)(DAT_80436354 + 1) != '\x02') {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801d2b1c  FUN_801d2b1c ====

void FUN_801d2b1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  double dVar2;
  short sVar3;
  float *pfVar4;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if ((cVar1 < '\x04') &&
         (zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                                       *(int *)(param_9 + 0x180) +
                                                       (-(*(uint *)(DAT_80436354 + 0x10) >> 2 & 1) &
                                                       8) ^ 0x80000000) - DOUBLE_8043be10),param_2,
                      param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,(float *)0x8,
                      *(uint *)(DAT_80436354 + 0x10),*(int *)(param_9 + 0x180),param_14,param_15,
                      param_16), *(int *)(DAT_80436354 + 0x10) == 0)) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + -1;
        *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
      }
      goto LAB_801d2c68;
    }
    if (cVar1 == '\0') {
      *(undefined1 *)(param_9 + 0x19) = 1;
      *(undefined2 *)(param_9 + 0x1c) = 5;
      *(undefined4 *)(param_9 + 0x180) = 0xffffffff;
    }
    else if (cVar1 < '\0') goto LAB_801d2c68;
    sVar3 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar3;
    if (0 < sVar3) goto LAB_801d2c68;
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined1 *)(param_9 + 0x82) = 7;
  }
  dVar2 = DOUBLE_8043be10;
  pfVar4 = (float *)(int)*(short *)(DAT_80436354 + 0x26);
  if (*(float **)(param_9 + 0x180) != pfVar4) {
    *(float **)(param_9 + 0x180) = pfVar4;
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(uint)pfVar4 ^ 0x80000000) - dVar2),
                param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar4,param_12,
                param_13,param_14,param_15,param_16);
  }
  if (*(int *)(DAT_80436354 + 0x10) != 0) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  }
LAB_801d2c68:
  if (*(char *)(DAT_80436354 + 1) != '\x02') {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801d2c94  FUN_801d2c94 ====

void FUN_801d2c94(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  double dVar3;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if ((cVar1 < '\x04') &&
         (zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,
                                                       (uint)DAT_80436354[4] >> 2 & 1 ^ 0x80000000)
                                     - DOUBLE_8043be10),param_2,param_3,param_4,param_5,param_6,
                      param_7,param_8,param_9,0,DAT_80436354,param_12,param_13,param_14,param_15,
                      param_16), DAT_80436354[4] == 0.0)) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + -1;
      }
      goto LAB_801d2d88;
    }
    if (cVar1 == '\0') {
      *(undefined1 *)(param_9 + 0x19) = 1;
      dVar3 = (double)FLOAT_8043be18;
      *(undefined2 *)(param_9 + 0x1c) = 5;
      zz_01a76fc_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                  param_12,param_13,param_14,param_15,param_16);
    }
    else if (cVar1 < '\0') goto LAB_801d2d88;
    sVar2 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar2;
    if (0 < sVar2) goto LAB_801d2d88;
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined1 *)(param_9 + 0x82) = 7;
  }
  if (DAT_80436354[4] != 0.0) {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
  }
LAB_801d2d88:
  if (*(char *)((int)DAT_80436354 + 1) != '\x02') {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801d2db4  FUN_801d2db4 ====

void FUN_801d2db4(int param_1)

{
  char cVar1;
  short sVar3;
  int iVar2;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
LAB_801d2e18:
    sVar3 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar3;
    if (0 < sVar3) goto LAB_801d2ec8;
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(undefined2 *)(param_1 + 0x1c) = 0;
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') goto LAB_801d2ec8;
      *(char *)(param_1 + 0x19) = cVar1 + '\x01';
      *(undefined2 *)(param_1 + 0x1c) = 5;
      if (*(char *)(param_1 + 0x11) == '\v') {
        *(undefined2 *)(param_1 + 0x74) = 0x8000;
      }
      goto LAB_801d2e18;
    }
    if ('\x02' < cVar1) goto LAB_801d2ec8;
  }
  sVar3 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar3;
  if (0x46 < sVar3) {
    *(undefined2 *)(param_1 + 0x1c) = 0;
  }
  if (*(short *)(param_1 + 0x1c) < 0x32) {
    *(undefined1 *)(param_1 + 0x82) = 7;
  }
  else {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  iVar2 = zz_0181a74_();
  if (((*(char *)(param_1 + 0x11) == '\n') && (*(short *)(DAT_80436354 + 0x26) == 0)) ||
     ((*(char *)(param_1 + 0x11) == '\v' && (iVar2 + -1 <= (int)*(short *)(DAT_80436354 + 0x26)))))
  {
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
LAB_801d2ec8:
  if (*(char *)(DAT_80436354 + 1) != '\x02') {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801d2f10  FUN_801d2f10 ====

void FUN_801d2f10(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801d2f30  FUN_801d2f30 ====

void FUN_801d2f30(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  
  if ((*(char *)(param_9 + 0x11) == '\x06') && (*(char *)(param_9 + 0x12) < '\x02')) {
    param_1 = zz_01d2f80_();
    param_10 = extraout_r4;
  }
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801d2f80  zz_01d2f80_ ====

void zz_01d2f80_(void)

{
  short sVar1;
  
  zz_0096d0c_((double)FLOAT_8043be08);
  zz_0096d14_((double)FLOAT_8043be24);
  sVar1 = *(short *)(DAT_80436354 + 0x24);
  zz_0097144_(0x80,0x14a,0x1b,(&PTR_DAT_8038b1c4)[sVar1 * 2]);
  zz_0097144_(0x80,0x168,0x1b,(&PTR_DAT_8038b1c8)[sVar1 * 2]);
  return;
}



// ==== 801d2ffc  zz_01d2ffc_ ====

bool zz_01d2ffc_(int param_1,undefined1 param_2)

{
  bool bVar2;
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x307) || (*(short *)(param_1 + 1000) == 0x30d)) {
    puVar1 = zz_0088aa0_(param_1,3,8,0,2);
    if (puVar1 == (undefined1 *)0x0) {
      *(undefined1 *)(param_1 + 0x147) = 1;
      zz_006de10_(param_1,2);
    }
    else {
      *puVar1 = 1;
      puVar1[0x13] = param_2;
      puVar1[0x11] = param_2;
      puVar1[0x10] = 0x28;
      *(code **)(puVar1 + 0xc) = FUN_801d313c;
      *(code **)(puVar1 + 0x10c) = FUN_801d41d8;
      *(int *)(puVar1 + 0x8c) = param_1;
      *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_1 + 0x90);
      *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_1 + 0x94);
      puVar1[0x96] = *(undefined1 *)(param_1 + 0x96);
      puVar1[0x97] = *(undefined1 *)(param_1 + 0x97);
      puVar1[0x88] = *(undefined1 *)(param_1 + 0x88);
      *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_1 + 200);
      *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
      *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
      *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
      *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
      *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
      puVar1[0xd0] = *(undefined1 *)(param_1 + 0xd0);
    }
    bVar2 = puVar1 != (undefined1 *)0x0;
  }
  else {
    bVar2 = false;
  }
  return bVar2;
}



// ==== 801d313c  FUN_801d313c ====

void FUN_801d313c(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8038b260)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801d31d4  FUN_801d31d4 ====

void FUN_801d31d4(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  undefined4 extraout_r4;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar12;
  double dVar13;
  double dVar14;
  undefined8 uVar15;
  double dVar16;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  *(undefined1 *)(param_9 + 0x19) = 0;
  *(undefined1 *)(param_9 + 0x1a) = 0;
  *(undefined1 *)(param_9 + 0x1b) = 10;
  iVar12 = *(int *)(param_9 + 0x90);
  iVar8 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  iVar6 = *(char *)(param_9 + 0x13) * 0x24;
  if (*(char *)(param_9 + 0x11) == '\x01') {
    *(undefined1 *)(param_9 + 0x98) = 5;
  }
  else {
    *(undefined1 *)(param_9 + 0x98) = 1;
  }
  *(code **)(param_9 + 0x100) = zz_0048288_;
  zz_0089100_(param_9,0,1);
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)(iVar12 + *(short *)(&DAT_8038b1e2 + iVar6) * 0x30 + 0x8dc);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar12 + *(short *)(&DAT_8038b1e2 + iVar6) * 0x30 + 0x8ec);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar12 + *(short *)(&DAT_8038b1e2 + iVar6) * 0x30 + 0x8fc);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar12 + *(short *)(&DAT_8038b1e2 + iVar6) * 0x30 + 0x8d4),
             (float *)(iVar6 + -0x7fc74e1c),(float *)(param_9 + 0x20));
  uVar2 = DAT_802b0cbc;
  uVar1 = DAT_802b0cb8;
  uVar3 = DAT_802b0cb4;
  iVar11 = *(short *)(&DAT_8038b1e2 + iVar6) * 0x30;
  *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(iVar12 + iVar11 + 0x8d4);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)(iVar12 + *(short *)(&DAT_8038b1e2 + iVar6) * 0x30 + 0x8e4);
  iVar10 = iVar12 + *(short *)(&DAT_8038b1e2 + iVar6) * 0x30;
  *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(iVar10 + 0x8f4);
  *(undefined4 *)(param_9 + 0x184) = uVar3;
  *(undefined4 *)(param_9 + 0x188) = uVar1;
  *(undefined4 *)(param_9 + 0x18c) = uVar2;
  *(undefined4 *)(param_9 + 0x38) = *(undefined4 *)(iVar12 + 0x90c);
  *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(iVar12 + 0x91c);
  *(undefined4 *)(param_9 + 0x40) = *(undefined4 *)(iVar12 + 0x92c);
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8038b238 + iVar8),(float *)(param_9 + 0x38),
                      (float *)(param_9 + 0x38));
  dVar16 = DOUBLE_8043be30;
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8038b238 + iVar8);
  dVar13 = (double)FLOAT_8043be28;
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8038b22c + iVar8);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_8038b22e + iVar8);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_8038b1fc + iVar6);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8038b200 + iVar6);
  *(float *)(param_9 + 0xd4) =
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(&DAT_8038b22a + iVar8) ^ 0x80000000) -
              dVar16);
  *(undefined1 *)(param_9 + 0xaf) = 0;
  dVar14 = (double)*(float *)(iVar12 + 0x204);
  *(float *)(param_9 + 0x204) = (float)(dVar14 * dVar13);
  *(undefined4 *)(param_9 + 0x16c) = *(undefined4 *)(&DAT_8038b23c + iVar8);
  *(undefined4 *)(param_9 + 0x170) = *(undefined4 *)(param_9 + 0x38);
  *(undefined4 *)(param_9 + 0x174) = *(undefined4 *)(param_9 + 0x3c);
  *(undefined4 *)(param_9 + 0x178) = *(undefined4 *)(param_9 + 0x40);
  iVar4 = zz_0006f98_(iVar12);
  uVar15 = zz_0006fb4_(dVar14,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),
                       (int)(char)(&DAT_8038b1e0)[iVar6],uVar3,iVar10,iVar11,in_r9,in_r10);
  if (*(char *)(param_9 + 0x11) != '\x01') {
    iVar9 = iVar4 + 0xc28;
    iVar7 = (int)(char)(&DAT_8038b1e1)[iVar6];
    uVar15 = zz_0007030_(uVar15,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,
                         *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),iVar7,iVar9,iVar10,iVar11,
                         in_r9,in_r10);
    zz_0007c54_(uVar15,dVar16,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe4),extraout_r4,iVar7,iVar9,iVar10,iVar11,in_r9,in_r10);
    zz_0007cac_((double)FLOAT_8043be2c,*(int *)(param_9 + 0xe4));
  }
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  piVar5 = zz_0006dc8_(0x84);
  *(int **)(param_9 + 0xdc) = piVar5;
  if (piVar5 != (int *)0x0) {
    uVar3 = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    *(undefined4 *)(param_9 + 0x180) = uVar3;
    *(undefined4 *)(param_9 + 0x17c) = uVar3;
    iVar8 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8038b228 + iVar8));
    if (iVar8 != 0) {
      *(undefined4 *)(param_9 + 400) = 1;
      gnt4_PSMTXMultVec_bl
                ((float *)(iVar12 + *(short *)(&DAT_8038b1e2 + iVar6) * 0x30 + 0x8d4),
                 (float *)(iVar6 + -0x7fc74e10),*(float **)(param_9 + 0x180));
      gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),
                       (float *)(*(int *)(param_9 + 0x180) + 0xc));
      zz_00a2bf8_(iVar12,param_9,*(undefined4 **)(param_9 + 0x180),
                  *(undefined4 **)(param_9 + 0x180) + 3,5,0);
      *(undefined2 *)(param_9 + 0x1c) = 0;
      return;
    }
  }
  *(undefined1 *)(iVar12 + 0x147) = 1;
  zz_006de10_(iVar12,2);
  *(undefined1 *)(param_9 + 0x18) = 2;
  zz_008aff0_(param_9);
  *(undefined1 *)(param_9 + 0x82) = 0;
  return;
}



// ==== 801d3534  FUN_801d3534 ====

void FUN_801d3534(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    zz_01d3d00_(param_1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    FUN_801d35a0(param_1);
  }
  if (*(char *)(param_1 + 0x11) != '\x01') {
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x1300;
  }
  return;
}



// ==== 801d35a0  FUN_801d35a0 ====

/* WARNING: Removing unreachable block (ram,0x801d3ce4) */
/* WARNING: Removing unreachable block (ram,0x801d35b0) */

void FUN_801d35a0(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  float fVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  char cVar9;
  undefined4 *puVar8;
  int iVar10;
  float *pfVar11;
  float *pfVar12;
  int iVar13;
  float *pfVar14;
  uint uVar15;
  double dVar16;
  double dVar17;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  float afStack_4c [3];
  float local_40;
  float local_3c;
  undefined4 local_38;
  
  fVar3 = FLOAT_8043be3c;
  fVar1 = *(float *)(param_1 + 0xd4) - FLOAT_8043be38;
  iVar13 = *(int *)(param_1 + 0x90);
  iVar7 = *(char *)(param_1 + 0x13) * 0x24;
  iVar10 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  *(float *)(param_1 + 0xd4) = fVar1;
  if (fVar1 <= fVar3) {
    FUN_801d3f68(param_1);
    return;
  }
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined2 *)(param_1 + 0x1c) = 4;
    cVar9 = *(char *)(param_1 + 0x1b) + -1;
    *(char *)(param_1 + 0x1b) = cVar9;
    if (cVar9 < '\x01') {
      FUN_801d3f68(param_1);
      return;
    }
  }
  iVar5 = zz_0083244_((float *)(param_1 + 0x20));
  if (iVar5 != 0) {
    FUN_801d3f68(param_1);
    return;
  }
  if ((*(uint *)(iVar13 + 0x5e0) & 3) == 0) {
    FUN_801d3f68(param_1);
    return;
  }
  if (*(short *)(param_1 + 0x1c6) < 1) {
    FUN_801d3f68(param_1);
    *(undefined2 *)(param_1 + 0x1c) = 4;
    return;
  }
  if (*(char *)(param_1 + 0x11) == '\x01') {
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
    *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
  }
  else {
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x11c);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 300);
    *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x13c);
  }
  if (0 < *(short *)(param_1 + 0x1c)) {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
    goto LAB_801d3abc;
  }
  cVar9 = *(char *)(param_1 + 0x1a);
  if (cVar9 == '\0') {
    if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x16c)) {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(&DAT_8038b240 + iVar10);
    }
    else {
      *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x16c);
    }
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                        (float *)(param_1 + 0x38));
    FUN_80083874((double)*(float *)(&DAT_8038b234 + iVar10),param_1);
    FUN_80083ad4((double)*(float *)(&DAT_8038b230 + iVar10),param_1,
                 (char)*(undefined2 *)(&DAT_8038b22c + iVar10));
    *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(param_1 + 0x174) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x178) = *(undefined4 *)(param_1 + 0x40);
  }
  else {
    if ((cVar9 < '\0') || ('\x03' < cVar9)) goto LAB_801d3abc;
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x184),&local_40);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),&local_40,&local_40);
    iVar10 = zz_003ecb8_((float *)(param_1 + 0x20),&local_40,afStack_4c,&local_58);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x20),&local_40);
    iVar5 = zz_003ecb8_((float *)(param_1 + 0x20),&local_40,afStack_4c,&local_58);
    if (iVar10 == 0 && iVar5 == 0) {
      *(undefined1 *)(param_1 + 0x1a) = 0;
      *(float *)(param_1 + 0x20) = local_40;
      *(float *)(param_1 + 0x24) = local_3c;
      *(undefined4 *)(param_1 + 0x28) = local_38;
      if (9 < *(int *)(param_1 + 400)) {
        FUN_801d3f68(param_1);
        return;
      }
      *(int *)(param_1 + 400) = *(int *)(param_1 + 400) + 1;
      *(int *)(param_1 + 0x180) = *(int *)(param_1 + 0x180) + 0xc;
      zz_00a2bf8_(iVar13,param_1,*(undefined4 **)(param_1 + 0x180),
                  *(undefined4 **)(param_1 + 0x180) + 3,5,0);
      puVar8 = *(undefined4 **)(param_1 + 0x180);
      uVar4 = *(undefined4 *)(param_1 + 0x24);
      *puVar8 = *(undefined4 *)(param_1 + 0x20);
      puVar8[1] = uVar4;
      puVar8[2] = *(undefined4 *)(param_1 + 0x28);
      goto LAB_801d3abc;
    }
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x170),(float *)(param_1 + 0x20),(float *)(param_1 + 0x20))
    ;
  }
  iVar10 = zz_003ecb8_((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),afStack_4c,&local_58);
  if (iVar10 != 0) {
    FUN_8001b9ac((double)*(float *)(param_1 + 0xb4),afStack_4c,&local_58);
    zz_0019550_(param_1,afStack_4c,0);
    if (9 < *(int *)(param_1 + 400)) {
      FUN_801d3f68(param_1);
      return;
    }
    *(int *)(param_1 + 400) = *(int *)(param_1 + 400) + 1;
    *(int *)(param_1 + 0x180) = *(int *)(param_1 + 0x180) + 0xc;
    zz_00a2bf8_(iVar13,param_1,*(undefined4 **)(param_1 + 0x180),
                *(undefined4 **)(param_1 + 0x180) + 3,5,0);
    if ((*(char *)(param_1 + 0x1a) != '\0') &&
       (dVar16 = gnt4_PSQUATDotProduct_bl(&local_58,(float *)(param_1 + 0x184)),
       dVar16 < (double)FLOAT_8043be3c)) {
      FUN_801d3f68(param_1);
      return;
    }
    *(char *)(param_1 + 0x1a) = (char)iVar10;
    gnt4_PSVECNormalize_bl(&local_58,&local_58);
    if (iVar10 == 2) {
      local_40 = local_58;
      local_38 = local_50;
      local_3c = FLOAT_8043be3c;
      zz_006ec1c_(&local_40,(float *)(param_1 + 0x184));
      uVar4 = DAT_802b0cb8;
      *(undefined4 *)(param_1 + 0x170) = DAT_802b0cb4;
      uVar2 = DAT_802b0cbc;
      *(undefined4 *)(param_1 + 0x174) = uVar4;
      *(undefined4 *)(param_1 + 0x178) = uVar2;
    }
    else {
      *(float *)(param_1 + 0x184) = local_58;
      *(undefined4 *)(param_1 + 0x188) = local_54;
      *(undefined4 *)(param_1 + 0x18c) = local_50;
      dVar16 = gnt4_PSQUATDotProduct_bl(&local_58,(float *)(param_1 + 0x170));
      gnt4_PSQUATScale_bl(dVar16,&local_58,&local_40);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x170),&local_40,(float *)(param_1 + 0x170));
      gnt4_PSMTXMultVec_bl
                ((float *)(iVar13 + *(short *)(&DAT_8038b1e2 + iVar7) * 0x30 + 0x8d4),
                 (float *)(iVar7 + -0x7fc74e10),&local_40);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),&local_40,&local_40);
      dVar16 = gnt4_PSQUATDotProduct_bl((float *)(param_1 + 0x170),&local_40);
      if (dVar16 < (double)FLOAT_8043be3c) {
        FUN_801d3f68(param_1);
        return;
      }
    }
    zz_006ebb4_((float *)(param_1 + 0x170),(float *)(param_1 + 0x170));
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x170),
                        (float *)(param_1 + 0x170));
    gnt4_PSQUATScale_bl((double)FLOAT_8043be40,&local_58,&local_40);
    gnt4_PSVECAdd_bl(afStack_4c,&local_40,(float *)(param_1 + 0x20));
    iVar10 = zz_003ecb8_((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),afStack_4c,&local_58);
    if (iVar10 != 0) {
      FUN_801d3f68(param_1);
      return;
    }
    puVar8 = *(undefined4 **)(param_1 + 0x180);
    uVar4 = *(undefined4 *)(param_1 + 0x24);
    *puVar8 = *(undefined4 *)(param_1 + 0x20);
    puVar8[1] = uVar4;
    puVar8[2] = *(undefined4 *)(param_1 + 0x28);
  }
LAB_801d3abc:
  zz_00833ec_(param_1);
  zz_0083610_(param_1,(float *)(param_1 + 0x16c));
  iVar10 = zz_0083714_(param_1);
  if (iVar10 == 0) {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar13 + *(short *)(&DAT_8038b1e2 + iVar7) * 0x30 + 0x8d4),
               (float *)(iVar7 + -0x7fc74e10),*(float **)(param_1 + 0x17c));
    fVar1 = FLOAT_8043be3c;
    iVar7 = *(int *)(param_1 + 0x180);
    iVar10 = 0;
    uVar4 = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(iVar7 + 0xc) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(iVar7 + 0x10) = uVar4;
    *(undefined4 *)(iVar7 + 0x14) = *(undefined4 *)(param_1 + 0x28);
    pfVar11 = *(float **)(param_1 + 0x17c);
    while( true ) {
      dVar16 = (double)fVar1;
      if (*(int *)(param_1 + 400) <= iVar10) break;
      gnt4_PSVECSubtract_bl(pfVar11 + 3,pfVar11,&local_40);
      dVar17 = gnt4_PSVECMag_bl(&local_40);
      fVar1 = (float)(dVar16 + dVar17);
      iVar10 = iVar10 + 1;
      pfVar11 = pfVar11 + 3;
    }
    if (dVar16 < (double)FLOAT_8043be44) {
      if (1 < *(int *)(param_1 + 400)) {
        pfVar12 = *(float **)(param_1 + 0x17c);
        iVar7 = 0;
        pfVar14 = pfVar12 + 6;
        pfVar11 = pfVar12;
        while( true ) {
          pfVar11 = pfVar11 + 3;
          iVar10 = *(int *)(param_1 + 400);
          if (iVar10 + -1 <= iVar7) break;
          iVar10 = zz_003ecb8_(pfVar12,pfVar14,afStack_4c,&local_58);
          if (iVar10 == 0) {
            zz_0046588_((double)FLOAT_8043be28,pfVar12,pfVar14,&local_40);
            zz_0046588_((double)FLOAT_8043be28,&local_40,pfVar11,pfVar11);
          }
          iVar7 = iVar7 + 1;
          pfVar12 = pfVar12 + 3;
          pfVar14 = pfVar14 + 3;
        }
        uVar6 = 0xb - iVar10;
        iVar7 = iVar10 * 0xc;
        if (iVar10 < 0xb) {
          uVar15 = uVar6 >> 2;
          if (uVar15 != 0) {
            do {
              puVar8 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar7);
              uVar4 = *(undefined4 *)(param_1 + 0x24);
              *puVar8 = *(undefined4 *)(param_1 + 0x20);
              puVar8[1] = uVar4;
              puVar8[2] = *(undefined4 *)(param_1 + 0x28);
              puVar8 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar7 + 0xc);
              uVar4 = *(undefined4 *)(param_1 + 0x24);
              *puVar8 = *(undefined4 *)(param_1 + 0x20);
              puVar8[1] = uVar4;
              puVar8[2] = *(undefined4 *)(param_1 + 0x28);
              puVar8 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar7 + 0x18);
              uVar4 = *(undefined4 *)(param_1 + 0x24);
              *puVar8 = *(undefined4 *)(param_1 + 0x20);
              puVar8[1] = uVar4;
              puVar8[2] = *(undefined4 *)(param_1 + 0x28);
              puVar8 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar7 + 0x24);
              uVar4 = *(undefined4 *)(param_1 + 0x24);
              iVar7 = iVar7 + 0x30;
              *puVar8 = *(undefined4 *)(param_1 + 0x20);
              puVar8[1] = uVar4;
              puVar8[2] = *(undefined4 *)(param_1 + 0x28);
              uVar15 = uVar15 - 1;
            } while (uVar15 != 0);
            uVar6 = uVar6 & 3;
            if (uVar6 == 0) {
              return;
            }
          }
          do {
            puVar8 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar7);
            uVar4 = *(undefined4 *)(param_1 + 0x24);
            iVar7 = iVar7 + 0xc;
            *puVar8 = *(undefined4 *)(param_1 + 0x20);
            puVar8[1] = uVar4;
            puVar8[2] = *(undefined4 *)(param_1 + 0x28);
            uVar6 = uVar6 - 1;
          } while (uVar6 != 0);
        }
      }
    }
    else {
      FUN_801d3f68(param_1);
    }
  }
  else {
    FUN_801d3f68(param_1);
  }
  return;
}



// ==== 801d3d00  zz_01d3d00_ ====

void zz_01d3d00_(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  undefined4 *puVar4;
  int iVar5;
  float *pfVar6;
  float *pfVar7;
  float *pfVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  double dVar12;
  undefined4 auStack_48 [3];
  float afStack_3c [3];
  float afStack_30 [5];
  
  iVar10 = *(int *)(param_1 + 0x90);
  iVar3 = *(char *)(param_1 + 0x13) * 0x24;
  if (1 < *(int *)(param_1 + 400)) {
    pfVar8 = *(float **)(param_1 + 0x17c);
    pfVar6 = pfVar8 + 6;
    pfVar7 = pfVar8;
    for (iVar9 = 0; pfVar7 = pfVar7 + 3, iVar9 < *(int *)(param_1 + 400) + -1; iVar9 = iVar9 + 1) {
      iVar5 = zz_003ecb8_(pfVar8,pfVar6,afStack_3c,auStack_48);
      if (iVar5 == 0) {
        zz_0046588_((double)FLOAT_8043be28,pfVar8,pfVar6,afStack_30);
        zz_0046588_((double)FLOAT_8043be28,afStack_30,pfVar7,pfVar7);
      }
      pfVar8 = pfVar8 + 3;
      pfVar6 = pfVar6 + 3;
    }
  }
  gnt4_PSVECSubtract_bl(*(float **)(param_1 + 0x180),(float *)(param_1 + 0x20),afStack_30);
  dVar12 = gnt4_PSVECMag_bl(afStack_30);
  if ((double)*(float *)(param_1 + 0x44) <= dVar12) {
    gnt4_PSQUATScale_bl((double)(float)((double)*(float *)(param_1 + 0x44) / dVar12),afStack_30,
                        afStack_30);
  }
  else {
    *(int *)(param_1 + 400) = *(int *)(param_1 + 400) + -1;
    *(int *)(param_1 + 0x180) = *(int *)(param_1 + 0x180) + -0xc;
  }
  gnt4_PSVECAdd_bl(afStack_30,(float *)(param_1 + 0x20),(float *)(param_1 + 0x20));
  iVar9 = *(int *)(param_1 + 400);
  uVar2 = 0xb - iVar9;
  iVar5 = iVar9 * 0xc;
  if (iVar9 < 0xb) {
    uVar11 = uVar2 >> 2;
    if (uVar11 != 0) {
      do {
        puVar4 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar5);
        uVar1 = *(undefined4 *)(param_1 + 0x24);
        *puVar4 = *(undefined4 *)(param_1 + 0x20);
        puVar4[1] = uVar1;
        puVar4[2] = *(undefined4 *)(param_1 + 0x28);
        puVar4 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar5 + 0xc);
        uVar1 = *(undefined4 *)(param_1 + 0x24);
        *puVar4 = *(undefined4 *)(param_1 + 0x20);
        puVar4[1] = uVar1;
        puVar4[2] = *(undefined4 *)(param_1 + 0x28);
        puVar4 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar5 + 0x18);
        uVar1 = *(undefined4 *)(param_1 + 0x24);
        *puVar4 = *(undefined4 *)(param_1 + 0x20);
        puVar4[1] = uVar1;
        puVar4[2] = *(undefined4 *)(param_1 + 0x28);
        puVar4 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar5 + 0x24);
        uVar1 = *(undefined4 *)(param_1 + 0x24);
        iVar5 = iVar5 + 0x30;
        *puVar4 = *(undefined4 *)(param_1 + 0x20);
        puVar4[1] = uVar1;
        puVar4[2] = *(undefined4 *)(param_1 + 0x28);
        uVar11 = uVar11 - 1;
      } while (uVar11 != 0);
      uVar2 = uVar2 & 3;
      if (uVar2 == 0) goto LAB_801d3efc;
    }
    do {
      puVar4 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar5);
      uVar1 = *(undefined4 *)(param_1 + 0x24);
      iVar5 = iVar5 + 0xc;
      *puVar4 = *(undefined4 *)(param_1 + 0x20);
      puVar4[1] = uVar1;
      puVar4[2] = *(undefined4 *)(param_1 + 0x28);
      uVar2 = uVar2 - 1;
    } while (uVar2 != 0);
  }
LAB_801d3efc:
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar10 + *(short *)(&DAT_8038b1e2 + iVar3) * 0x30 + 0x8d4),
             (float *)(iVar3 + -0x7fc74e10),*(float **)(param_1 + 0x17c));
  if (*(int *)(param_1 + 400) < 1) {
    *(undefined1 *)(iVar10 + 0x147) = 1;
    zz_006de10_(iVar10,2);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    zz_00f036c_(param_1,0xdc);
  }
  return;
}



// ==== 801d3f68  FUN_801d3f68 ====

void FUN_801d3f68(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  float *pfVar8;
  uint uVar9;
  double dVar10;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float afStack_1c [4];
  
  bVar1 = *(byte *)(param_1 + 0x11);
  iVar5 = *(char *)(param_1 + 0x13) * 0x24;
  gnt4_PSMTXMultVec_bl
            ((float *)(*(int *)(param_1 + 0x90) + *(short *)(&DAT_8038b1e2 + iVar5) * 0x30 + 0x8d4),
             (float *)(iVar5 + -0x7fc74e1c),afStack_1c);
  gnt4_PSVECSubtract_bl(afStack_1c,(float *)(param_1 + 0x20),&local_28);
  dVar10 = gnt4_PSVECSquareMag_bl(&local_28);
  uVar3 = DAT_802b0cac;
  if (dVar10 <= (double)FLOAT_8043be3c) {
    *(undefined4 *)(param_1 + 0x15c) = DAT_802b0ca8;
    uVar2 = DAT_802b0cb0;
    *(undefined4 *)(param_1 + 0x160) = uVar3;
    *(undefined4 *)(param_1 + 0x164) = uVar2;
  }
  else {
    *(float *)(param_1 + 0x15c) = local_28;
    *(undefined4 *)(param_1 + 0x160) = local_24;
    *(undefined4 *)(param_1 + 0x164) = local_20;
  }
  pfVar8 = (float *)(param_1 + 0x15c);
  gnt4_PSVECNormalize_bl(pfVar8,pfVar8);
  if (*(float *)(&DAT_8038b23c + (uint)bVar1 * 0x1c) <= *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = *(float *)(&DAT_8038b23c + (uint)bVar1 * 0x1c);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),pfVar8,pfVar8);
  *(undefined1 *)(param_1 + 0x19) = 1;
  zz_008aff0_(param_1);
  iVar5 = *(int *)(param_1 + 400);
  uVar4 = 0xb - iVar5;
  iVar7 = iVar5 * 0xc;
  if (iVar5 < 0xb) {
    uVar9 = uVar4 >> 2;
    if (uVar9 != 0) {
      do {
        puVar6 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar7);
        uVar3 = *(undefined4 *)(param_1 + 0x24);
        *puVar6 = *(undefined4 *)(param_1 + 0x20);
        puVar6[1] = uVar3;
        puVar6[2] = *(undefined4 *)(param_1 + 0x28);
        puVar6 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar7 + 0xc);
        uVar3 = *(undefined4 *)(param_1 + 0x24);
        *puVar6 = *(undefined4 *)(param_1 + 0x20);
        puVar6[1] = uVar3;
        puVar6[2] = *(undefined4 *)(param_1 + 0x28);
        puVar6 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar7 + 0x18);
        uVar3 = *(undefined4 *)(param_1 + 0x24);
        *puVar6 = *(undefined4 *)(param_1 + 0x20);
        puVar6[1] = uVar3;
        puVar6[2] = *(undefined4 *)(param_1 + 0x28);
        puVar6 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar7 + 0x24);
        uVar3 = *(undefined4 *)(param_1 + 0x24);
        iVar7 = iVar7 + 0x30;
        *puVar6 = *(undefined4 *)(param_1 + 0x20);
        puVar6[1] = uVar3;
        puVar6[2] = *(undefined4 *)(param_1 + 0x28);
        uVar9 = uVar9 - 1;
      } while (uVar9 != 0);
      uVar4 = uVar4 & 3;
      if (uVar4 == 0) {
        return;
      }
    }
    do {
      puVar6 = (undefined4 *)(*(int *)(param_1 + 0x17c) + iVar7);
      uVar3 = *(undefined4 *)(param_1 + 0x24);
      iVar7 = iVar7 + 0xc;
      *puVar6 = *(undefined4 *)(param_1 + 0x20);
      puVar6[1] = uVar3;
      puVar6[2] = *(undefined4 *)(param_1 + 0x28);
      uVar4 = uVar4 - 1;
    } while (uVar4 != 0);
  }
  return;
}



// ==== 801d4180  FUN_801d4180 ====

void FUN_801d4180(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801d4194  FUN_801d4194 ====

void FUN_801d4194(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  undefined8 uVar1;
  
  uVar1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
  *(undefined4 *)(param_9 + 0xdc) = 0;
  *(undefined4 *)(param_9 + 0xdc) = 0;
  zz_0088e50_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801d41d8  FUN_801d41d8 ====

void FUN_801d41d8(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  float *pfVar2;
  int iVar3;
  undefined8 uVar4;
  double dVar5;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  dVar5 = (double)FLOAT_8043be48;
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_9 + 0x72) ^ 0x80000000;
  iVar3 = *(int *)(param_9 + 0x90);
  gnt4_PSMTXRotRad_bl((double)(float)(dVar5 * (double)(float)((double)CONCAT44(0x43300000,uStack_14)
                                                             - DOUBLE_8043be30)),afStack_48,0x79);
  pfVar2 = afStack_48;
  uVar4 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_00076d0_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0),
              afStack_48,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  uVar1 = 1;
  if (*(char *)(iVar3 + 0x3ec) == '\x04') {
    uVar1 = 0x44;
  }
  uVar4 = zz_00097b4_(*(int *)(param_9 + 0xe0),uVar1);
  if (*(char *)(param_9 + 0x11) != '\x01') {
    zz_00076d0_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
                ,afStack_48,(undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + 0xe4),0x45);
  }
  return;
}



// ==== 801d4398  FUN_801d4398 ====

void FUN_801d4398(int param_1)

{
  zz_00c74ec_(param_1,7);
  return;
}



// ==== 801d43bc  FUN_801d43bc ====

void FUN_801d43bc(int param_1)

{
  zz_010a4ac_(param_1);
  *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 1;
  *(undefined1 *)(param_1 + 0x748) = 2;
  return;
}



// ==== 801d4410  FUN_801d4410 ====

void FUN_801d4410(undefined4 param_1,char param_2,char param_3)

{
  (**(code **)(&DAT_80435ad0 + param_2 * 4))(param_1,(int)param_3);
  return;
}



// ==== 801d447c  FUN_801d447c ====

void FUN_801d447c(int param_1)

{
  (*(code *)(&PTR_FUN_8038b2b0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801d44b8  FUN_801d44b8 ====

void FUN_801d44b8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8038b2bc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801d4500  FUN_801d4500 ====

void FUN_801d4500(int param_1)

{
  zz_010b2f4_(param_1);
  return;
}



