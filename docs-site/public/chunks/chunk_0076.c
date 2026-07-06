// ==== 8027bfc8  zz_027bfc8_ ====

void zz_027bfc8_(char *param_1,undefined1 *param_2)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  
  iVar5 = 0x20;
  while( true ) {
    uVar3 = (uint)*param_1;
    uVar4 = ((int)uVar3 >> 3) + (uint)((int)uVar3 < 0 && (uVar3 & 7) != 0);
    iVar2 = (int)uVar3 >> 0x1f;
    iVar2 = (iVar2 * 8 | uVar3 * 0x20000000 + iVar2 >> 0x1d) - iVar2;
    if ((uVar4 & 1 ^ uVar4 >> 0x1f) == uVar4 >> 0x1f) {
      iVar2 = iVar2 * 2;
    }
    else {
      uVar4 = uVar4 - 1;
      iVar2 = iVar2 * 2 + 1;
    }
    iVar2 = iVar2 + uVar4 * 8;
    if (iVar2 < 0) break;
    if (0xff < iVar2) break;
    cVar1 = param_1[1];
    *param_2 = (char)iVar2;
    uVar3 = (uint)cVar1;
    uVar4 = ((int)uVar3 >> 3) + (uint)((int)uVar3 < 0 && (uVar3 & 7) != 0);
    iVar2 = (int)uVar3 >> 0x1f;
    iVar2 = (iVar2 * 8 | uVar3 * 0x20000000 + iVar2 >> 0x1d) - iVar2;
    if ((uVar4 & 1 ^ uVar4 >> 0x1f) == uVar4 >> 0x1f) {
      iVar2 = iVar2 * 2;
    }
    else {
      uVar4 = uVar4 - 1;
      iVar2 = iVar2 * 2 + 1;
    }
    iVar2 = iVar2 + uVar4 * 8;
    if ((iVar2 < 0) || (0xff < iVar2)) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    param_2[1] = (char)iVar2;
    param_2 = param_2 + 2;
    param_1 = param_1 + 2;
    iVar5 = iVar5 + -1;
    if (iVar5 == 0) {
      return;
    }
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== 8027c0b8  Bowser::DrawShadow(cPoseAccumulator ====

void Bowser__DrawShadow_cPoseAccumulator(char *param_1)

{
  FUN_8027c0dc(param_1,*(int *)(param_1 + 0x28));
  return;
}



// ==== 8027c0dc  FUN_8027c0dc ====

/* WARNING: Removing unreachable block (ram,0x8027c450) */
/* WARNING: Removing unreachable block (ram,0x8027c3e0) */
/* WARNING: Removing unreachable block (ram,0x8027c240) */
/* WARNING: Removing unreachable block (ram,0x8027c328) */
/* WARNING: Removing unreachable block (ram,0x8027c2d8) */
/* WARNING: Removing unreachable block (ram,0x8027c33c) */
/* WARNING: Removing unreachable block (ram,0x8027c324) */
/* WARNING: Removing unreachable block (ram,0x8027c300) */
/* WARNING: Removing unreachable block (ram,0x8027c2f0) */
/* WARNING: Removing unreachable block (ram,0x8027c228) */
/* WARNING: Removing unreachable block (ram,0x8027c2e0) */
/* WARNING: Removing unreachable block (ram,0x8027c334) */
/* WARNING: Removing unreachable block (ram,0x8027c2e8) */
/* WARNING: Removing unreachable block (ram,0x8027c40c) */
/* WARNING: Removing unreachable block (ram,0x8027c238) */
/* WARNING: Removing unreachable block (ram,0x8027c3f4) */
/* WARNING: Removing unreachable block (ram,0x8027c23c) */
/* WARNING: Removing unreachable block (ram,0x8027c414) */
/* WARNING: Removing unreachable block (ram,0x8027c338) */
/* WARNING: Removing unreachable block (ram,0x8027c2f8) */
/* WARNING: Removing unreachable block (ram,0x8027c234) */
/* WARNING: Removing unreachable block (ram,0x8027c32c) */
/* WARNING: Removing unreachable block (ram,0x8027c224) */
/* WARNING: Removing unreachable block (ram,0x8027c3ec) */
/* WARNING: Removing unreachable block (ram,0x8027c320) */
/* WARNING: Removing unreachable block (ram,0x8027c2d0) */
/* WARNING: Removing unreachable block (ram,0x8027c22c) */
/* WARNING: Removing unreachable block (ram,0x8027c114) */
/* WARNING: Removing unreachable block (ram,0x8027c110) */
/* WARNING: Removing unreachable block (ram,0x8027c10c) */
/* WARNING: Removing unreachable block (ram,0x8027c108) */
/* WARNING: Removing unreachable block (ram,0x8027c104) */
/* WARNING: Removing unreachable block (ram,0x8027c100) */
/* WARNING: Removing unreachable block (ram,0x8027c0e4) */
/* WARNING: Removing unreachable block (ram,0x8027c230) */
/* WARNING: Removing unreachable block (ram,0x8027c30c) */
/* WARNING: Removing unreachable block (ram,0x8027c330) */
/* WARNING: Removing unreachable block (ram,0x8027c3fc) */
/* WARNING: Removing unreachable block (ram,0x8027c41c) */
/* WARNING: Removing unreachable block (ram,0x8027c428) */

void FUN_8027c0dc(char *param_1,int param_2)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  float fVar15;
  float fVar16;
  float fVar17;
  float fVar18;
  float fVar19;
  float fVar20;
  float fVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  float fVar33;
  float fVar34;
  float fVar35;
  undefined2 uVar38;
  undefined4 uVar36;
  int iVar37;
  float *pfVar39;
  float *pfVar40;
  undefined4 *puVar41;
  float *pfVar42;
  undefined4 *puVar43;
  float *pfVar44;
  float *pfVar45;
  int iVar46;
  double dVar47;
  
  fVar35 = DAT_803ae29c;
  fVar34 = DAT_803ae298;
  fVar33 = DAT_803ae294;
  fVar32 = DAT_803ae290;
  fVar31 = DAT_803ae28c;
  fVar30 = DAT_803ae288;
  fVar29 = DAT_803ae284;
  fVar28 = DAT_803ae280;
  fVar27 = DAT_803ae27c;
  fVar26 = DAT_803ae278;
  fVar25 = DAT_803ae274;
  fVar24 = DAT_803ae270;
  pfVar42 = *(float **)(param_1 + 0x48);
  pfVar40 = *(float **)(param_1 + 0x2c);
  puVar41 = *(undefined4 **)(param_1 + 0x30);
  iVar46 = 6;
  do {
    if (param_2 < 0) {
      if (*param_1 == '\0') {
        dVar47 = (double)*pfVar40;
        puVar43 = (undefined4 *)*puVar41;
        if (DAT_802b86c0 <= dVar47) {
          uVar38 = (undefined2)(int)((double)DAT_802b86b8 + dVar47);
        }
        else {
          uVar38 = (undefined2)(int)(dVar47 - (double)DAT_802b86b8);
        }
        uVar36 = CONCAT22(uVar38,uVar38);
        puVar43[0x1f] = uVar36;
        puVar43[0x1e] = uVar36;
        puVar43[0x1d] = uVar36;
        puVar43[0x1c] = uVar36;
        puVar43[0x1b] = uVar36;
        puVar43[0x1a] = uVar36;
        puVar43[0x19] = uVar36;
        puVar43[0x18] = uVar36;
        puVar43[0x17] = uVar36;
        puVar43[0x16] = uVar36;
        puVar43[0x15] = uVar36;
        puVar43[0x14] = uVar36;
        puVar43[0x13] = uVar36;
        puVar43[0x12] = uVar36;
        puVar43[0x11] = uVar36;
        puVar43[0x10] = uVar36;
        puVar43[0xf] = uVar36;
        puVar43[0xe] = uVar36;
        puVar43[0xd] = uVar36;
        puVar43[0xc] = uVar36;
        puVar43[0xb] = uVar36;
        puVar43[10] = uVar36;
        puVar43[9] = uVar36;
        puVar43[8] = uVar36;
        puVar43[7] = uVar36;
        puVar43[6] = uVar36;
        puVar43[5] = uVar36;
        puVar43[4] = uVar36;
        puVar43[3] = uVar36;
        puVar43[2] = uVar36;
        puVar43[1] = uVar36;
        *puVar43 = uVar36;
      }
      else {
        pfVar44 = (float *)*puVar41;
        iVar37 = 4;
        pfVar39 = pfVar40 + -2;
        pfVar45 = pfVar42 + -2;
        do {
          fVar1 = pfVar39[0x10];
          fVar8 = pfVar39[6] + pfVar39[0xe];
          fVar11 = pfVar39[7] + pfVar39[0xf];
          fVar3 = pfVar39[2] - pfVar39[10];
          fVar14 = pfVar39[3] - pfVar39[0xb];
          fVar9 = pfVar39[2] + pfVar39[10];
          fVar19 = pfVar39[3] + pfVar39[0xb];
          fVar2 = (pfVar39[6] - pfVar39[0xe]) * fVar24 - fVar8;
          fVar10 = (pfVar39[7] - pfVar39[0xf]) * fVar25 - fVar11;
          fVar7 = fVar9 - fVar8;
          fVar18 = fVar19 - fVar11;
          fVar9 = fVar9 + fVar8;
          fVar19 = fVar19 + fVar11;
          fVar8 = fVar3 - fVar2;
          fVar15 = fVar14 - fVar10;
          fVar3 = fVar3 + fVar2;
          fVar14 = fVar14 + fVar10;
          fVar10 = pfVar39[0xc] - pfVar39[8];
          fVar20 = pfVar39[0xd] - pfVar39[9];
          fVar11 = pfVar39[0xc] + pfVar39[8];
          fVar5 = pfVar39[0xd] + pfVar39[9];
          fVar2 = pfVar39[4] - fVar1;
          fVar13 = pfVar39[5] - pfVar39[0x11];
          fVar1 = pfVar39[4] + fVar1;
          fVar17 = pfVar39[5] + pfVar39[0x11];
          fVar6 = fVar1 + fVar11;
          fVar4 = fVar17 + fVar5;
          fVar12 = (fVar10 - fVar2) * fVar30;
          fVar16 = (fVar20 - fVar13) * fVar31;
          fVar2 = (fVar2 * fVar28 - fVar12) - fVar6;
          fVar13 = (fVar13 * fVar29 - fVar16) - fVar4;
          fVar1 = (fVar1 - fVar11) * fVar24 - fVar2;
          fVar11 = (fVar17 - fVar5) * fVar25 - fVar13;
          fVar10 = (fVar10 * fVar26 - fVar12) - fVar1;
          fVar12 = (fVar20 * fVar27 - fVar16) - fVar11;
          pfVar45[2] = fVar9 + fVar6;
          pfVar45[3] = fVar3 + fVar2;
          pfVar45[4] = fVar8 + fVar1;
          pfVar45[5] = fVar7 + fVar10;
          pfVar45[6] = fVar7 - fVar10;
          pfVar45[7] = fVar8 - fVar1;
          pfVar45[8] = fVar3 - fVar2;
          pfVar45[9] = fVar9 - fVar6;
          pfVar45[10] = fVar19 + fVar4;
          pfVar45[0xb] = fVar14 + fVar13;
          pfVar45[0xc] = fVar15 + fVar11;
          pfVar45[0xd] = fVar18 + fVar12;
          pfVar45[0xe] = fVar18 - fVar12;
          pfVar45[0xf] = fVar15 - fVar11;
          iVar37 = iVar37 + -1;
          pfVar45[0x10] = fVar14 - fVar13;
          pfVar45[0x11] = fVar19 - fVar4;
          pfVar39 = pfVar39 + 0x10;
          pfVar45 = pfVar45 + 0x10;
        } while (0 < iVar37);
        iVar37 = 4;
        pfVar39 = pfVar42;
        while( true ) {
          fVar1 = pfVar39[0x10] + pfVar39[0x30];
          fVar3 = pfVar39[0x11] + pfVar39[0x31];
          fVar13 = *pfVar39 - pfVar39[0x20];
          fVar23 = pfVar39[1] - pfVar39[0x21];
          fVar7 = *pfVar39 + pfVar39[0x20];
          fVar20 = pfVar39[1] + pfVar39[0x21];
          fVar2 = (pfVar39[0x10] - pfVar39[0x30]) * fVar24 - fVar1;
          fVar8 = (pfVar39[0x11] - pfVar39[0x31]) * fVar25 - fVar3;
          fVar12 = fVar7 - fVar1;
          fVar22 = fVar20 - fVar3;
          fVar7 = fVar7 + fVar1;
          fVar20 = fVar20 + fVar3;
          fVar3 = fVar13 - fVar2;
          fVar15 = fVar23 - fVar8;
          fVar13 = fVar13 + fVar2;
          fVar23 = fVar23 + fVar8;
          fVar9 = pfVar39[0x28] - pfVar39[0x18];
          fVar17 = pfVar39[0x29] - pfVar39[0x19];
          fVar2 = pfVar39[0x28] + pfVar39[0x18];
          fVar5 = pfVar39[0x29] + pfVar39[0x19];
          fVar11 = pfVar39[8] - pfVar39[0x38];
          fVar16 = pfVar39[9] - pfVar39[0x39];
          fVar6 = pfVar39[8] + pfVar39[0x38];
          fVar21 = pfVar39[9] + pfVar39[0x39];
          fVar1 = fVar6 + fVar2;
          fVar19 = fVar21 + fVar5;
          fVar10 = (fVar9 - fVar11) * fVar30;
          fVar4 = (fVar17 - fVar16) * fVar31;
          fVar8 = fVar7 - fVar1;
          fVar18 = fVar20 - fVar19;
          fVar14 = (fVar11 * fVar28 - fVar10) - fVar1;
          fVar16 = (fVar16 * fVar29 - fVar4) - fVar19;
          fVar7 = fVar7 + fVar1;
          fVar20 = fVar20 + fVar19;
          fVar1 = (fVar6 - fVar2) * fVar24 - fVar14;
          fVar6 = (fVar21 - fVar5) * fVar25 - fVar16;
          fVar11 = fVar13 - fVar14;
          fVar19 = fVar23 - fVar16;
          fVar13 = fVar13 + fVar14;
          fVar23 = fVar23 + fVar16;
          fVar2 = (fVar9 * fVar26 - fVar10) - fVar1;
          fVar10 = (fVar17 * fVar27 - fVar4) - fVar6;
          fVar9 = fVar12 - fVar2;
          fVar14 = fVar22 - fVar10;
          fVar12 = fVar12 + fVar2;
          fVar22 = fVar22 + fVar10;
          fVar2 = fVar3 - fVar1;
          fVar10 = fVar15 - fVar6;
          fVar3 = fVar3 + fVar1;
          fVar15 = fVar15 + fVar6;
          fVar1 = fVar32;
          if (fVar7 < 0.0) {
            fVar1 = fVar34;
          }
          fVar6 = fVar33;
          if (fVar20 < 0.0) {
            fVar6 = fVar35;
          }
          fVar5 = fVar32;
          if (fVar13 < 0.0) {
            fVar5 = fVar34;
          }
          fVar17 = fVar33;
          if (fVar23 < 0.0) {
            fVar17 = fVar35;
          }
          fVar4 = fVar32;
          if (fVar3 < 0.0) {
            fVar4 = fVar34;
          }
          fVar16 = fVar33;
          if (fVar15 < 0.0) {
            fVar16 = fVar35;
          }
          *pfVar44 = fVar7 + fVar1;
          pfVar44[1] = fVar20 + fVar6;
          fVar1 = fVar32;
          if (fVar12 < 0.0) {
            fVar1 = fVar34;
          }
          fVar7 = fVar33;
          if (fVar22 < 0.0) {
            fVar7 = fVar35;
          }
          pfVar44[4] = fVar13 + fVar5;
          pfVar44[5] = fVar23 + fVar17;
          fVar6 = fVar32;
          if (fVar9 < 0.0) {
            fVar6 = fVar34;
          }
          fVar13 = fVar33;
          if (fVar14 < 0.0) {
            fVar13 = fVar35;
          }
          pfVar44[8] = fVar3 + fVar4;
          pfVar44[9] = fVar15 + fVar16;
          pfVar44[0xc] = fVar12 + fVar1;
          pfVar44[0xd] = fVar22 + fVar7;
          fVar1 = fVar32;
          if (fVar2 < 0.0) {
            fVar1 = fVar34;
          }
          fVar3 = fVar33;
          if (fVar10 < 0.0) {
            fVar3 = fVar35;
          }
          fVar7 = fVar32;
          if (fVar11 < 0.0) {
            fVar7 = fVar34;
          }
          fVar12 = fVar33;
          if (fVar19 < 0.0) {
            fVar12 = fVar35;
          }
          pfVar44[0x10] = fVar9 + fVar6;
          pfVar44[0x11] = fVar14 + fVar13;
          pfVar44[0x14] = fVar2 + fVar1;
          pfVar44[0x15] = fVar10 + fVar3;
          fVar1 = fVar32;
          if (fVar8 < 0.0) {
            fVar1 = fVar34;
          }
          fVar2 = fVar33;
          if (fVar18 < 0.0) {
            fVar2 = fVar35;
          }
          pfVar44[0x18] = fVar11 + fVar7;
          pfVar44[0x19] = fVar19 + fVar12;
          iVar37 = iVar37 + -1;
          pfVar44[0x1c] = fVar8 + fVar1;
          pfVar44[0x1d] = fVar18 + fVar2;
          if (iVar37 < 1) break;
          pfVar39 = pfVar39 + 2;
          pfVar44 = pfVar44 + 1;
        }
      }
    }
    param_2 = param_2 << 1;
    pfVar40 = pfVar40 + 0x40;
    puVar41 = puVar41 + 1;
    param_1 = param_1 + 1;
    iVar46 = iVar46 + -1;
  } while (iVar46 != 0);
  return;
}



// ==== 8027c464  zz_027c464_ ====

void zz_027c464_(char *param_1)

{
  FUN_8027c0dc(param_1,-1);
  return;
}



// ==== 8027c488  zz_027c488_ ====

void zz_027c488_(void)

{
  return;
}



// ==== 8027c498  FUN_8027c498 ====

/* WARNING: Removing unreachable block (ram,0x8027c6c4) */
/* WARNING: Removing unreachable block (ram,0x8027c6bc) */
/* WARNING: Removing unreachable block (ram,0x8027c4b0) */
/* WARNING: Removing unreachable block (ram,0x8027c4a8) */

void FUN_8027c498(void)

{
  double *pdVar1;
  double *pdVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  double dVar11;
  double dVar12;
  double local_438 [64];
  double local_238 [65];
  
  gnt4_memset(&DAT_80417418,0,0x4000);
  FUN_8027beb4();
  uVar8 = 0;
  dVar11 = DAT_802b86c8;
  dVar12 = DAT_802b86c0;
  do {
    pdVar2 = local_238;
    uVar3 = 0;
    iVar9 = 0x10;
    pdVar1 = (double *)&DAT_80417218;
    do {
      if (uVar3 == uVar8) {
        *pdVar2 = dVar11 / *pdVar1;
      }
      else {
        *pdVar2 = dVar12;
      }
      if (uVar3 + 1 == uVar8) {
        pdVar2[1] = dVar11 / pdVar1[1];
      }
      else {
        pdVar2[1] = dVar12;
      }
      if (uVar3 + 2 == uVar8) {
        pdVar2[2] = dVar11 / pdVar1[2];
      }
      else {
        pdVar2[2] = dVar12;
      }
      if (uVar3 + 3 == uVar8) {
        pdVar2[3] = dVar11 / pdVar1[3];
      }
      else {
        pdVar2[3] = dVar12;
      }
      pdVar1 = pdVar1 + 4;
      pdVar2 = pdVar2 + 4;
      uVar3 = uVar3 + 4;
      iVar9 = iVar9 + -1;
    } while (iVar9 != 0);
    FUN_8027be8c((int)local_238,(int)local_438);
    iVar9 = (int)uVar8 >> 0x1f;
    pdVar1 = local_438;
    iVar7 = 0;
    uVar3 = iVar9 * 8 | uVar8 * 0x20000000 + iVar9 >> 0x1d;
    iVar10 = 0x20;
    do {
      iVar4 = uVar3 + -iVar9;
      uVar6 = ((int)uVar8 >> 3) + (uint)((int)uVar8 < 0 && (uVar8 & 7) != 0);
      if ((uVar6 & 1 ^ uVar6 >> 0x1f) == uVar6 >> 0x1f) {
        iVar4 = iVar4 * 2;
      }
      else {
        uVar6 = uVar6 - 1;
        iVar4 = iVar4 * 2 + 1;
      }
      iVar4 = iVar4 + uVar6 * 8;
      if ((iVar4 < 0) || (0xff < iVar4)) {
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      uVar6 = ((int)uVar8 >> 3) + (uint)((int)uVar8 < 0 && (uVar8 & 7) != 0);
      iVar5 = uVar3 + -iVar9;
      *(float *)((int)&DAT_80417418 + iVar7 + iVar4 * 0x100) = (float)*pdVar1;
      if ((uVar6 & 1 ^ uVar6 >> 0x1f) == uVar6 >> 0x1f) {
        iVar5 = iVar5 * 2;
      }
      else {
        uVar6 = uVar6 - 1;
        iVar5 = iVar5 * 2 + 1;
      }
      iVar5 = iVar5 + uVar6 * 8;
      if ((iVar5 < 0) || (0xff < iVar5)) {
        do {
                    /* WARNING: Do nothing block with infinite loop */
        } while( true );
      }
      pdVar2 = pdVar1 + 1;
      pdVar1 = pdVar1 + 2;
      *(float *)((int)&DAT_8041741c + iVar5 * 0x100 + iVar7) = (float)*pdVar2;
      iVar7 = iVar7 + 8;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
    uVar8 = uVar8 + 1;
    if (0x3f < (int)uVar8) {
      return;
    }
  } while( true );
}



// ==== 8027c6e8  zz_027c6e8_ ====

void zz_027c6e8_(void *param_1)

{
  gnt4_memset(param_1,0,0x54);
  return;
}



// ==== 8027c710  zz_027c710_ ====

void zz_027c710_(int param_1)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  double *pdVar4;
  double *pdVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  
  pdVar4 = (double *)&DAT_80417218;
  uVar6 = 0;
  iVar8 = 0x20;
  while( true ) {
    uVar3 = ((int)uVar6 >> 3) + (uint)((int)uVar6 < 0 && (uVar6 & 7) != 0);
    iVar1 = (int)uVar6 >> 0x1f;
    iVar1 = (iVar1 * 8 | uVar6 * 0x20000000 + iVar1 >> 0x1d) - iVar1;
    if ((uVar3 & 1 ^ uVar3 >> 0x1f) == uVar3 >> 0x1f) {
      iVar1 = iVar1 * 2;
    }
    else {
      uVar3 = uVar3 - 1;
      iVar1 = iVar1 * 2 + 1;
    }
    iVar1 = iVar1 + uVar3 * 8;
    if (iVar1 < 0) break;
    if (0xff < iVar1) break;
    uVar7 = uVar6 + 1;
    uVar3 = ((int)uVar7 >> 3) + (uint)((int)uVar7 < 0 && (uVar7 & 7) != 0);
    iVar2 = (int)uVar7 >> 0x1f;
    *(float *)(param_1 + iVar1 * 4) = (float)*pdVar4;
    iVar2 = (iVar2 * 8 | uVar7 * 0x20000000 + iVar2 >> 0x1d) - iVar2;
    pdVar5 = pdVar4 + 1;
    if ((uVar3 & 1 ^ uVar3 >> 0x1f) == uVar3 >> 0x1f) {
      iVar2 = iVar2 * 2;
    }
    else {
      uVar3 = uVar3 - 1;
      iVar2 = iVar2 * 2 + 1;
    }
    iVar2 = iVar2 + uVar3 * 8;
    if ((iVar2 < 0) || (0xff < iVar2)) {
      do {
                    /* WARNING: Do nothing block with infinite loop */
      } while( true );
    }
    uVar6 = uVar6 + 2;
    pdVar4 = pdVar4 + 2;
    *(float *)(param_1 + iVar2 * 4) = (float)*pdVar5;
    iVar8 = iVar8 + -1;
    if (iVar8 == 0) {
      return;
    }
  }
  do {
                    /* WARNING: Do nothing block with infinite loop */
  } while( true );
}



// ==== 8027c814  zz_027c814_ ====

void zz_027c814_(void)

{
  double dVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  double *pdVar13;
  int iVar14;
  int iVar15;
  double dVar16;
  double dVar17;
  
  DAT_80417210 = zz_027bfb4_();
  dVar8 = DAT_802b86b0;
  dVar7 = DAT_802b86a8;
  dVar6 = DAT_802b86a0;
  dVar5 = DAT_802b8698;
  dVar4 = DAT_802b8690;
  dVar3 = DAT_802b8688;
  dVar2 = DAT_802b8680;
  dVar1 = DAT_802b8678;
  pdVar13 = &DAT_802b8678;
  iVar14 = 0;
  iVar11 = 0;
  iVar15 = 4;
  do {
    dVar16 = *pdVar13;
    *(double *)((int)&DAT_80417218 + iVar11) = dVar16 * dVar1;
    (&DAT_80417218)[iVar14 + 1] = dVar16 * dVar2;
    (&DAT_80417218)[iVar14 + 2] = dVar16 * dVar3;
    (&DAT_80417218)[iVar14 + 3] = dVar16 * dVar4;
    (&DAT_80417218)[iVar14 + 4] = dVar16 * dVar5;
    (&DAT_80417218)[iVar14 + 5] = dVar16 * dVar6;
    dVar17 = pdVar13[1];
    (&DAT_80417218)[iVar14 + 6] = dVar16 * dVar7;
    (&DAT_80417218)[iVar14 + 7] = dVar16 * dVar8;
    *(double *)((int)&DAT_80417258 + iVar11) = dVar17 * dVar1;
    (&DAT_80417218)[iVar14 + 9] = dVar17 * dVar2;
    iVar12 = iVar14 + 0xd;
    iVar9 = iVar14 + 0xf;
    (&DAT_80417218)[iVar14 + 10] = dVar17 * dVar3;
    iVar10 = iVar14 + 0xe;
    (&DAT_80417218)[iVar14 + 0xb] = dVar17 * dVar4;
    pdVar13 = pdVar13 + 2;
    (&DAT_80417218)[iVar14 + 0xc] = dVar17 * dVar5;
    iVar14 = iVar14 + 0x10;
    (&DAT_80417218)[iVar12] = dVar17 * dVar6;
    iVar11 = iVar11 + 0x80;
    (&DAT_80417218)[iVar10] = dVar17 * dVar7;
    (&DAT_80417218)[iVar9] = dVar17 * dVar8;
    iVar15 = iVar15 + -1;
  } while (iVar15 != 0);
  FUN_8027c498();
  return;
}



// ==== 8027c990  zz_027c990_ ====

void zz_027c990_(void *param_1,void *param_2,size_t param_3)

{
  gnt4_memcpy(param_1,param_2,param_3);
  return;
}



// ==== 8027c9b0  zz_027c9b0_ ====

void zz_027c9b0_(uint *param_1,int param_2,int *param_3,int param_4)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint *puVar11;
  uint uVar12;
  
  piVar1 = (int *)(param_2 + 3U & 0xfffffffc);
  iVar5 = ((param_2 + 3U) - (int)piVar1) * 8;
  uVar7 = piVar1[1];
  puVar11 = (uint *)(piVar1 + 2);
  uVar2 = *piVar1 << iVar5;
  if (iVar5 < 0x18) {
    uVar9 = uVar2 << 8;
    iVar5 = iVar5 + 8;
  }
  else {
    iVar5 = iVar5 + -0x18;
    if (iVar5 != 0) {
      uVar2 = uVar2 | uVar7 >> 8 - iVar5;
      uVar7 = uVar7 << iVar5;
    }
    uVar8 = *puVar11;
    puVar11 = (uint *)(piVar1 + 3);
    uVar9 = uVar7;
    uVar7 = uVar8;
  }
  uVar2 = uVar2 >> 0x18;
  *param_1 = uVar2;
  if ((uVar2 < 0xe0) || (0xef < uVar2)) {
    if ((uVar2 < 0xc0) || (0xdf < uVar2)) {
      if (uVar2 == 0xbd) {
        uVar8 = 2;
        uVar12 = 1;
      }
      else if (uVar2 == 0xbf) {
        uVar8 = 2;
        uVar12 = 2;
      }
      else if (uVar2 == 0xbe) {
        uVar8 = 3;
        uVar12 = 0;
      }
      else {
        uVar8 = 4;
        uVar12 = 0;
      }
    }
    else {
      uVar12 = uVar2 - 0xc0;
      uVar8 = 0;
    }
  }
  else {
    uVar12 = uVar2 - 0xe0;
    uVar8 = 1;
  }
  param_1[1] = uVar8;
  param_1[2] = uVar12;
  if (param_4 == 2) {
    if (iVar5 < 0x10) {
      uVar8 = uVar9 << 0x10;
      param_1[3] = uVar9 >> 0x10;
      iVar5 = iVar5 + 0x10;
    }
    else {
      iVar5 = iVar5 + -0x10;
      if (iVar5 == 0) {
        param_1[3] = uVar9 >> 0x10;
      }
      else {
        param_1[3] = (uVar9 | uVar7 >> 0x10 - iVar5) >> 0x10;
        uVar7 = uVar7 << iVar5;
      }
      uVar9 = *puVar11;
      puVar11 = puVar11 + 1;
      uVar8 = uVar7;
      uVar7 = uVar9;
    }
    iVar4 = 6;
  }
  else {
    if (iVar5 == 0) {
      param_1[3] = uVar9;
      uVar8 = uVar7;
    }
    else {
      param_1[3] = uVar9 | uVar7 >> 0x20 - iVar5;
      uVar8 = uVar7 << iVar5;
    }
    uVar7 = *puVar11;
    iVar4 = 8;
    puVar11 = puVar11 + 1;
  }
  if ((uVar2 == 0xbf) || (uVar2 == 0xbe)) {
    *param_3 = iVar4;
    param_1[7] = param_1[3];
  }
  else {
    while( true ) {
      uVar2 = uVar8 >> 0x18;
      if (0x18 < iVar5) {
        uVar2 = uVar2 | uVar7 >> 0x38 - iVar5;
      }
      if (uVar2 != 0xff) break;
      if (iVar5 + 8 < 0x20) {
        uVar8 = uVar8 << 8;
        iVar5 = iVar5 + 8;
      }
      else {
        uVar8 = uVar7 << iVar5 + -0x18;
        uVar7 = *puVar11;
        puVar11 = puVar11 + 1;
        iVar5 = iVar5 + -0x18;
      }
    }
    uVar2 = uVar8 >> 0x1e;
    if (0x1e < iVar5) {
      uVar2 = uVar2 | uVar7 >> 0x3e - iVar5;
    }
    if (uVar2 == 1) {
      iVar6 = iVar5 + 2;
      if (iVar6 < 0x20) {
        iVar3 = uVar8 << 2;
      }
      else {
        iVar6 = iVar5 + -0x1e;
        iVar3 = uVar7 << iVar6;
        uVar7 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      if (iVar6 == 0x1f) {
        uVar9 = *puVar11;
        iVar5 = 0;
        puVar11 = puVar11 + 1;
        uVar2 = uVar7;
        uVar7 = uVar9;
      }
      else {
        uVar2 = iVar3 << 1;
        iVar5 = iVar6 + 1;
      }
      if (iVar5 < 0x13) {
        uVar8 = uVar2 << 0xd;
        iVar5 = iVar5 + 0xd;
      }
      else {
        iVar5 = iVar5 + -0x13;
        if (iVar5 != 0) {
          uVar2 = uVar2 | uVar7 >> 0xd - iVar5;
          uVar7 = uVar7 << iVar5;
        }
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar8 = uVar7;
        uVar7 = uVar9;
      }
      uVar9 = (uVar2 >> 0x13) << 7;
      if (iVar3 < 0) {
        uVar9 = (uVar2 >> 0x13) << 10;
      }
      param_1[4] = uVar9;
    }
    uVar2 = uVar8 >> 0x1c;
    if (0x1c < iVar5) {
      uVar2 = uVar2 | uVar7 >> 0x3c - iVar5;
    }
    if (uVar2 == 2) {
      iVar6 = iVar5 + 4;
      if (iVar6 < 0x20) {
        uVar8 = uVar8 << 4;
      }
      else {
        iVar6 = iVar5 + -0x1c;
        uVar8 = uVar7 << iVar6;
        uVar7 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      if (iVar6 < 0x1d) {
        uVar2 = uVar8 << 3;
        iVar6 = iVar6 + 3;
      }
      else {
        iVar6 = iVar6 + -0x1d;
        if (iVar6 != 0) {
          uVar8 = uVar8 | uVar7 >> 3 - iVar6;
          uVar7 = uVar7 << iVar6;
        }
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar2 = uVar7;
        uVar7 = uVar9;
      }
      iVar5 = iVar6 + 1;
      if (iVar5 < 0x20) {
        uVar2 = uVar2 << 1;
      }
      else {
        iVar5 = iVar6 + -0x1f;
        uVar2 = uVar7 << iVar5;
        uVar7 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      if (iVar5 < 0x11) {
        uVar9 = uVar2 << 0xf;
        iVar5 = iVar5 + 0xf;
      }
      else {
        iVar5 = iVar5 + -0x11;
        if (iVar5 != 0) {
          uVar2 = uVar2 | uVar7 >> 0xf - iVar5;
          uVar7 = uVar7 << iVar5;
        }
        uVar12 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar9 = uVar7;
        uVar7 = uVar12;
      }
      iVar3 = iVar5 + 1;
      if (iVar3 < 0x20) {
        uVar9 = uVar9 << 1;
      }
      else {
        iVar3 = iVar5 + -0x1f;
        uVar9 = uVar7 << iVar3;
        uVar7 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      if (iVar3 < 0x11) {
        iVar3 = iVar3 + 0xf;
      }
      else {
        iVar3 = iVar3 + -0x11;
        if (iVar3 != 0) {
          uVar9 = uVar9 | uVar7 >> 0xf - iVar3;
        }
        puVar11 = puVar11 + 1;
      }
      iVar6 = iVar3 + 1;
      if (0x1f < iVar6) {
        iVar6 = iVar3 + -0x1f;
        puVar11 = puVar11 + 1;
      }
      param_1[5] = uVar9 >> 0x13 | (uVar8 >> 0x1d) << 0x1c | (uVar2 >> 0x11) << 0xd;
      param_1[6] = 0xffffffff;
    }
    else if (uVar2 == 3) {
      iVar6 = iVar5 + 4;
      if (iVar6 < 0x20) {
        uVar8 = uVar8 << 4;
      }
      else {
        iVar6 = iVar5 + -0x1c;
        uVar8 = uVar7 << iVar6;
        uVar7 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      if (iVar6 < 0x1d) {
        uVar2 = uVar8 << 3;
        iVar6 = iVar6 + 3;
      }
      else {
        iVar6 = iVar6 + -0x1d;
        if (iVar6 != 0) {
          uVar8 = uVar8 | uVar7 >> 3 - iVar6;
          uVar7 = uVar7 << iVar6;
        }
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar2 = uVar7;
        uVar7 = uVar9;
      }
      iVar5 = iVar6 + 1;
      if (iVar5 < 0x20) {
        uVar2 = uVar2 << 1;
      }
      else {
        iVar5 = iVar6 + -0x1f;
        uVar2 = uVar7 << iVar5;
        uVar7 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      if (iVar5 < 0x11) {
        uVar9 = uVar2 << 0xf;
        iVar5 = iVar5 + 0xf;
      }
      else {
        iVar5 = iVar5 + -0x11;
        if (iVar5 != 0) {
          uVar2 = uVar2 | uVar7 >> 0xf - iVar5;
          uVar7 = uVar7 << iVar5;
        }
        uVar12 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar9 = uVar7;
        uVar7 = uVar12;
      }
      iVar6 = iVar5 + 1;
      if (iVar6 < 0x20) {
        uVar9 = uVar9 << 1;
      }
      else {
        iVar6 = iVar5 + -0x1f;
        uVar9 = uVar7 << iVar6;
        uVar7 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      if (iVar6 < 0x11) {
        uVar12 = uVar9 << 0xf;
        iVar6 = iVar6 + 0xf;
      }
      else {
        iVar6 = iVar6 + -0x11;
        if (iVar6 != 0) {
          uVar9 = uVar9 | uVar7 >> 0xf - iVar6;
          uVar7 = uVar7 << iVar6;
        }
        uVar10 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar12 = uVar7;
        uVar7 = uVar10;
      }
      iVar5 = iVar6 + 1;
      if (iVar5 < 0x20) {
        iVar6 = uVar12 << 1;
      }
      else {
        iVar5 = iVar6 + -0x1f;
        iVar6 = uVar7 << iVar5;
        uVar7 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      iVar3 = iVar5 + 4;
      param_1[5] = uVar9 >> 0x13 | (uVar8 >> 0x1d) << 0x1c | (uVar2 >> 0x11) << 0xd;
      if (iVar3 < 0x20) {
        uVar2 = iVar6 << 4;
      }
      else {
        iVar3 = iVar5 + -0x1c;
        uVar2 = uVar7 << iVar3;
        uVar7 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      if (iVar3 < 0x1d) {
        uVar9 = uVar2 << 3;
        iVar3 = iVar3 + 3;
      }
      else {
        iVar3 = iVar3 + -0x1d;
        if (iVar3 != 0) {
          uVar2 = uVar2 | uVar7 >> 3 - iVar3;
          uVar7 = uVar7 << iVar3;
        }
        uVar8 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar9 = uVar7;
        uVar7 = uVar8;
      }
      iVar5 = iVar3 + 1;
      if (iVar5 < 0x20) {
        uVar9 = uVar9 << 1;
      }
      else {
        iVar5 = iVar3 + -0x1f;
        uVar9 = uVar7 << iVar5;
        uVar7 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      if (iVar5 < 0x11) {
        uVar8 = uVar9 << 0xf;
        iVar5 = iVar5 + 0xf;
      }
      else {
        iVar5 = iVar5 + -0x11;
        if (iVar5 != 0) {
          uVar9 = uVar9 | uVar7 >> 0xf - iVar5;
          uVar7 = uVar7 << iVar5;
        }
        uVar12 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar8 = uVar7;
        uVar7 = uVar12;
      }
      iVar3 = iVar5 + 1;
      if (iVar3 < 0x20) {
        uVar8 = uVar8 << 1;
      }
      else {
        iVar3 = iVar5 + -0x1f;
        uVar8 = uVar7 << iVar3;
        uVar7 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      if (iVar3 < 0x11) {
        iVar3 = iVar3 + 0xf;
      }
      else {
        iVar3 = iVar3 + -0x11;
        if (iVar3 != 0) {
          uVar8 = uVar8 | uVar7 >> 0xf - iVar3;
        }
        puVar11 = puVar11 + 1;
      }
      iVar6 = iVar3 + 1;
      if (0x1f < iVar6) {
        iVar6 = iVar3 + -0x1f;
        puVar11 = puVar11 + 1;
      }
      param_1[6] = uVar8 >> 0x13 | (uVar2 >> 0x1d) << 0x1c | (uVar9 >> 0x11) << 0xd;
    }
    else {
      iVar6 = iVar5 + 8;
      if (0x1f < iVar6) {
        iVar6 = iVar5 + -0x18;
        puVar11 = puVar11 + 1;
      }
      param_1[5] = 0xffffffff;
      param_1[6] = 0xffffffff;
    }
    *param_3 = (int)puVar11 + (((iVar6 + 7 >> 3) + -8) - param_2);
    param_1[7] = (param_1[3] + iVar4) - *param_3;
  }
  return;
}



// ==== 8027d140  zz_027d140_ ====

void zz_027d140_(uint *param_1,int param_2,int *param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint *puVar7;
  int *piVar8;
  
  piVar8 = (int *)(param_2 + 4U & 0xfffffffc);
  iVar4 = ((param_2 + 4U) - (int)piVar8) * 8;
  uVar6 = piVar8[1];
  puVar7 = (uint *)(piVar8 + 2);
  uVar1 = *piVar8 << iVar4;
  if (iVar4 < 0x10) {
    uVar2 = uVar1 << 0x10;
    *param_1 = uVar1 >> 0x10;
    iVar4 = iVar4 + 0x10;
  }
  else {
    iVar4 = iVar4 + -0x10;
    if (iVar4 == 0) {
      *param_1 = uVar1 >> 0x10;
    }
    else {
      *param_1 = (uVar1 | uVar6 >> 0x10 - iVar4) >> 0x10;
      uVar6 = uVar6 << iVar4;
    }
    uVar1 = *puVar7;
    puVar7 = (uint *)(piVar8 + 3);
    uVar2 = uVar6;
    uVar6 = uVar1;
  }
  iVar5 = iVar4 + 1;
  if (iVar5 < 0x20) {
    uVar2 = uVar2 << 1;
  }
  else {
    iVar5 = iVar4 + -0x1f;
    uVar2 = uVar6 << iVar5;
    uVar6 = *puVar7;
    puVar7 = puVar7 + 1;
  }
  if (iVar5 < 10) {
    uVar1 = uVar2 << 0x16;
    param_1[1] = uVar2 >> 10;
    iVar5 = iVar5 + 0x16;
  }
  else {
    iVar5 = iVar5 + -10;
    if (iVar5 == 0) {
      param_1[1] = uVar2 >> 10;
    }
    else {
      param_1[1] = (uVar2 | uVar6 >> 0x16 - iVar5) >> 10;
      uVar6 = uVar6 << iVar5;
    }
    uVar2 = *puVar7;
    puVar7 = puVar7 + 1;
    uVar1 = uVar6;
    uVar6 = uVar2;
  }
  iVar4 = iVar5 + 1;
  if (iVar4 < 0x20) {
    uVar1 = uVar1 << 1;
  }
  else {
    iVar4 = iVar5 + -0x1f;
    uVar1 = uVar6 << iVar4;
    uVar6 = *puVar7;
    puVar7 = puVar7 + 1;
  }
  if (iVar4 < 0x1a) {
    uVar2 = uVar1 << 6;
    param_1[2] = uVar1 >> 0x1a;
    iVar4 = iVar4 + 6;
  }
  else {
    iVar4 = iVar4 + -0x1a;
    if (iVar4 == 0) {
      param_1[2] = uVar1 >> 0x1a;
    }
    else {
      param_1[2] = (uVar1 | uVar6 >> 6 - iVar4) >> 0x1a;
      uVar6 = uVar6 << iVar4;
    }
    uVar1 = *puVar7;
    puVar7 = puVar7 + 1;
    uVar2 = uVar6;
    uVar6 = uVar1;
  }
  param_1[4] = uVar2 >> 0x1f;
  if (iVar4 == 0x1f) {
    uVar1 = *puVar7;
    iVar4 = 0;
    puVar7 = puVar7 + 1;
    uVar2 = uVar6;
    uVar6 = uVar1;
  }
  else {
    uVar2 = uVar2 << 1;
    iVar4 = iVar4 + 1;
  }
  param_1[5] = uVar2 >> 0x1f;
  if (iVar4 == 0x1f) {
    uVar1 = *puVar7;
    iVar4 = 0;
    puVar7 = puVar7 + 1;
    uVar2 = uVar6;
    uVar6 = uVar1;
  }
  else {
    uVar2 = uVar2 << 1;
    iVar4 = iVar4 + 1;
  }
  param_1[6] = uVar2 >> 0x1f;
  if (iVar4 == 0x1f) {
    uVar1 = *puVar7;
    iVar4 = 0;
    puVar7 = puVar7 + 1;
    uVar2 = uVar6;
    uVar6 = uVar1;
  }
  else {
    uVar2 = uVar2 << 1;
    iVar4 = iVar4 + 1;
  }
  param_1[7] = uVar2 >> 0x1f;
  if (iVar4 == 0x1f) {
    uVar1 = *puVar7;
    iVar4 = 0;
    puVar7 = puVar7 + 1;
    uVar2 = uVar6;
    uVar6 = uVar1;
  }
  else {
    uVar2 = uVar2 << 1;
    iVar4 = iVar4 + 1;
  }
  iVar5 = iVar4 + 1;
  if (iVar5 < 0x20) {
    uVar2 = uVar2 << 1;
  }
  else {
    iVar5 = iVar4 + -0x1f;
    uVar2 = uVar6 << iVar5;
    uVar6 = *puVar7;
    puVar7 = puVar7 + 1;
  }
  if (iVar5 < 0x1b) {
    uVar1 = uVar2 << 5;
    param_1[3] = uVar2 >> 0x1b;
    iVar5 = iVar5 + 5;
  }
  else {
    iVar5 = iVar5 + -0x1b;
    if (iVar5 == 0) {
      param_1[3] = uVar2 >> 0x1b;
    }
    else {
      param_1[3] = (uVar2 | uVar6 >> 5 - iVar5) >> 0x1b;
      uVar6 = uVar6 << iVar5;
    }
    uVar2 = *puVar7;
    puVar7 = puVar7 + 1;
    uVar1 = uVar6;
    uVar6 = uVar2;
  }
  iVar4 = iVar5 + 8;
  if (iVar4 < 0x20) {
    iVar3 = uVar1 << 8;
  }
  else {
    iVar3 = uVar6 << iVar5 + -0x18;
    uVar6 = *puVar7;
    puVar7 = puVar7 + 1;
    iVar4 = iVar5 + -0x18;
  }
  while (iVar3 < 0) {
    if (iVar4 + 0x18 < 0x20) {
      iVar3 = iVar3 << 0x18;
      iVar4 = iVar4 + 0x18;
    }
    else {
      iVar3 = uVar6 << iVar4 + -8;
      uVar6 = *puVar7;
      puVar7 = puVar7 + 1;
      iVar4 = iVar4 + -8;
    }
  }
  iVar4 = iVar4 + 7 >> 3;
  piVar8 = (int *)((int)puVar7 + iVar4 + -8);
  *param_3 = (int)piVar8 - param_2;
  iVar5 = zz_027d8ac_(piVar8);
  if ((iVar5 == 0) && (iVar4 = zz_027d8ac_((int *)((int)puVar7 + iVar4 + -7)), iVar4 == 0x40000)) {
    *param_3 = *param_3 + 1;
  }
  return;
}



// ==== 8027d498  zz_027d498_ ====

void zz_027d498_(uint *param_1,int param_2,undefined4 *param_3)

{
  int *piVar1;
  uint *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  
  piVar1 = (int *)(param_2 + 4U & 0xfffffffc);
  iVar3 = ((param_2 + 4U) - (int)piVar1) * 8;
  uVar8 = piVar1[1];
  puVar2 = (uint *)(piVar1 + 2);
  uVar6 = *piVar1 << iVar3;
  if (iVar3 < 0x1e) {
    uVar7 = uVar6 << 2;
    iVar3 = iVar3 + 2;
  }
  else {
    iVar3 = iVar3 + -0x1e;
    if (iVar3 != 0) {
      uVar6 = uVar6 | uVar8 >> 1;
      uVar8 = uVar8 << 1;
    }
    uVar9 = *puVar2;
    puVar2 = (uint *)(piVar1 + 3);
    uVar7 = uVar8;
    uVar8 = uVar9;
  }
  iVar4 = iVar3 + 2;
  if (iVar4 < 0x20) {
    uVar7 = uVar7 << 2;
  }
  else {
    iVar4 = iVar3 + -0x1e;
    uVar7 = uVar8 << iVar4;
    uVar8 = *puVar2;
    puVar2 = puVar2 + 1;
  }
  if (iVar4 < 0x1d) {
    uVar9 = uVar7 << 3;
    iVar4 = iVar4 + 3;
  }
  else {
    iVar4 = iVar4 + -0x1d;
    if (iVar4 != 0) {
      uVar7 = uVar7 | uVar8 >> 3 - iVar4;
      uVar8 = uVar8 << iVar4;
    }
    uVar10 = *puVar2;
    puVar2 = puVar2 + 1;
    uVar9 = uVar8;
    uVar8 = uVar10;
  }
  iVar3 = iVar4 + 1;
  if (iVar3 < 0x20) {
    uVar9 = uVar9 << 1;
  }
  else {
    iVar3 = iVar4 + -0x1f;
    uVar9 = uVar8 << iVar3;
    uVar8 = *puVar2;
    puVar2 = puVar2 + 1;
  }
  if (iVar3 < 0x11) {
    uVar10 = uVar9 << 0xf;
    iVar3 = iVar3 + 0xf;
  }
  else {
    iVar3 = iVar3 + -0x11;
    if (iVar3 != 0) {
      uVar9 = uVar9 | uVar8 >> 0xf - iVar3;
      uVar8 = uVar8 << iVar3;
    }
    uVar11 = *puVar2;
    puVar2 = puVar2 + 1;
    uVar10 = uVar8;
    uVar8 = uVar11;
  }
  iVar4 = iVar3 + 1;
  if (iVar4 < 0x20) {
    uVar10 = uVar10 << 1;
  }
  else {
    iVar4 = iVar3 + -0x1f;
    uVar10 = uVar8 << iVar4;
    uVar8 = *puVar2;
    puVar2 = puVar2 + 1;
  }
  if (iVar4 < 0x11) {
    uVar11 = uVar10 << 0xf;
    iVar4 = iVar4 + 0xf;
  }
  else {
    iVar4 = iVar4 + -0x11;
    if (iVar4 != 0) {
      uVar10 = uVar10 | uVar8 >> 0xf - iVar4;
      uVar8 = uVar8 << iVar4;
    }
    uVar12 = *puVar2;
    puVar2 = puVar2 + 1;
    uVar11 = uVar8;
    uVar8 = uVar12;
  }
  iVar3 = iVar4 + 1;
  if (iVar3 < 0x20) {
    iVar4 = uVar11 << 1;
  }
  else {
    iVar3 = iVar4 + -0x1f;
    iVar4 = uVar8 << iVar3;
    uVar8 = *puVar2;
    puVar2 = puVar2 + 1;
  }
  iVar5 = iVar3 + 1;
  if (iVar5 < 0x20) {
    uVar11 = iVar4 << 1;
  }
  else {
    iVar5 = iVar3 + -0x1f;
    uVar11 = uVar8 << iVar5;
    uVar8 = *puVar2;
  }
  if (iVar5 < 10) {
    uVar11 = uVar11 >> 10;
  }
  else if (iVar5 == 10) {
    uVar11 = uVar11 >> 10;
  }
  else {
    uVar11 = (uVar11 | uVar8 >> 0x16 - (iVar5 + -10)) >> 10;
  }
  uVar8 = countLeadingZeros(uVar6 >> 0x1e);
  *param_1 = uVar8 >> 5;
  param_1[1] = uVar10 >> 0x13 | (uVar7 >> 0x1d) << 0x1c | (uVar9 >> 0x11) << 0xd;
  param_1[2] = uVar11;
  *param_3 = 0xc;
  return;
}



// ==== 8027d6ec  zz_027d6ec_ ====

int zz_027d6ec_(int *param_1,int *param_2,int param_3,int *param_4,uint *param_5)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int local_28 [2];
  
  *param_4 = 0;
  *param_5 = 0;
  iVar3 = zz_027de18_(param_1);
  if (iVar3 == 0) {
    do {
      if (param_3 < 4) break;
      bVar1 = false;
      local_28[0] = 0;
      uVar4 = zz_027d8ac_(param_2);
      if (uVar4 == 0x40000) {
        zz_027c9b0_((uint *)(param_1 + 0x28),(int)param_2,local_28,param_1[4]);
      }
      else if ((int)uVar4 < 0x40000) {
        if (uVar4 == 0x20000) {
          zz_027d140_((uint *)(param_1 + 8),(int)param_2,local_28);
          bVar1 = true;
        }
        else if (((int)uVar4 < 0x20000) && (uVar4 == 0x10000)) {
          zz_027d498_((uint *)(param_1 + 5),(int)param_2,local_28);
          bVar1 = true;
        }
      }
      *param_5 = *param_5 | uVar4;
      param_2 = (int *)((int)param_2 + local_28[0]);
      param_3 = param_3 - local_28[0];
      *param_4 = *param_4 + local_28[0];
    } while (bVar1);
    if ((*param_5 & 0x20000) != 0) {
      if (param_1[10] == 0) {
        if (param_1[0xb] == 0) {
          iVar3 = 2;
        }
        else {
          iVar3 = 1;
        }
      }
      else {
        iVar3 = 0;
      }
      iVar2 = param_1[9];
      param_1[iVar3 * 8 + 0x10] = param_1[8];
      param_1[iVar3 * 8 + 0x11] = iVar2;
      iVar2 = param_1[0xb];
      param_1[iVar3 * 8 + 0x12] = param_1[10];
      param_1[iVar3 * 8 + 0x13] = iVar2;
      iVar2 = param_1[0xd];
      param_1[iVar3 * 8 + 0x14] = param_1[0xc];
      param_1[iVar3 * 8 + 0x15] = iVar2;
      iVar2 = param_1[0xf];
      param_1[iVar3 * 8 + 0x16] = param_1[0xe];
      param_1[iVar3 * 8 + 0x17] = iVar2;
    }
    iVar3 = 0;
  }
  else {
    iVar3 = zz_027defc_(0,-0xfdfcff);
  }
  return iVar3;
}



// ==== 8027d8a4  zz_027d8a4_ ====

void zz_027d8a4_(void)

{
  return;
}



// ==== 8027d8a8  zz_027d8a8_ ====

void zz_027d8a8_(void)

{
  return;
}



// ==== 8027d8ac  zz_027d8ac_ ====

undefined4 zz_027d8ac_(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  switch(iVar1) {
  case 0x1b9:
    return 0x80000;
  case 0x1ba:
    return 0x10000;
  case 0x1bb:
    return 0x20000;
  case 0x1bd:
    return 0x40000;
  case 0x1be:
    return 0x40000;
  case 0x1bf:
    return 0x40000;
  }
  if ((0x1bf < iVar1) && (iVar1 < 0x1f0)) {
    return 0x40000;
  }
  return 0;
}



// ==== 8027d944  zz_027d944_ ====

undefined4 zz_027d944_(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  switch(iVar1) {
  case 0x1b9:
    return 0x80000;
  case 0x1ba:
    return 0x10000;
  case 0x1bb:
    return 0x20000;
  case 0x1bd:
    return 0x40000;
  case 0x1be:
    return 0x40000;
  case 0x1bf:
    return 0x40000;
  }
  if ((0x1bf < iVar1) && (iVar1 < 0x1f0)) {
    return 0x40000;
  }
  return 0;
}



// ==== 8027d9dc  zz_027d9dc_ ====

int zz_027d9dc_(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = zz_027de18_(param_1);
  if (iVar1 == 0) {
    iVar2 = 0;
    iVar1 = param_1[0x29];
    *param_2 = param_1[0x28];
    param_2[1] = iVar1;
    iVar1 = param_1[0x2b];
    param_2[2] = param_1[0x2a];
    param_2[3] = iVar1;
    iVar1 = param_1[0x2d];
    param_2[4] = param_1[0x2c];
    param_2[5] = iVar1;
    iVar1 = param_1[0x2f];
    param_2[6] = param_1[0x2e];
    param_2[7] = iVar1;
  }
  else {
    iVar2 = zz_027defc_(0,-0xfdfdfd);
  }
  return iVar2;
}



// ==== 8027da74  zz_027da74_ ====

int zz_027da74_(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = zz_027de18_(param_1);
  if (iVar1 == 0) {
    iVar2 = 0;
    iVar1 = param_1[9];
    *param_2 = param_1[8];
    param_2[1] = iVar1;
    iVar1 = param_1[0xb];
    param_2[2] = param_1[10];
    param_2[3] = iVar1;
    iVar1 = param_1[0xd];
    param_2[4] = param_1[0xc];
    param_2[5] = iVar1;
    iVar1 = param_1[0xf];
    param_2[6] = param_1[0xe];
    param_2[7] = iVar1;
  }
  else {
    iVar2 = zz_027defc_(0,-0xfdfdfe);
  }
  return iVar2;
}



// ==== 8027db0c  zz_027db0c_ ====

int zz_027db0c_(int *param_1,int *param_2,int param_3)

{
  int iVar1;
  int iVar2;
  
  iVar1 = zz_027de18_(param_1);
  if (iVar1 == 0) {
    iVar2 = 0;
    iVar1 = param_1[param_3 * 8 + 0x11];
    *param_2 = param_1[param_3 * 8 + 0x10];
    param_2[1] = iVar1;
    iVar1 = param_1[param_3 * 8 + 0x13];
    param_2[2] = param_1[param_3 * 8 + 0x12];
    param_2[3] = iVar1;
    iVar1 = param_1[param_3 * 8 + 0x15];
    param_2[4] = param_1[param_3 * 8 + 0x14];
    param_2[5] = iVar1;
    iVar1 = param_1[param_3 * 8 + 0x17];
    param_2[6] = param_1[param_3 * 8 + 0x16];
    param_2[7] = iVar1;
  }
  else {
    iVar2 = zz_027defc_(0,-0xfdfdfe);
  }
  return iVar2;
}



// ==== 8027dbb8  zz_027dbb8_ ====

int zz_027dbb8_(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = zz_027de18_(param_1);
  if (iVar1 == 0) {
    iVar2 = 0;
    iVar1 = param_1[6];
    *param_2 = param_1[5];
    param_2[1] = iVar1;
    param_2[2] = param_1[7];
  }
  else {
    iVar2 = zz_027defc_(0,-0xfdfdff);
  }
  return iVar2;
}



// ==== 8027dc28  zz_027dc28_ ====

void zz_027dc28_(void)

{
  return;
}



// ==== 8027dc2c  zz_027dc2c_ ====

void zz_027dc2c_(void)

{
  return;
}



// ==== 8027dc30  zz_027dc30_ ====

undefined4 zz_027dc30_(int *param_1)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  code *pcVar4;
  
  puVar1 = DAT_8041b420;
  if (param_1 == (int *)0x0) {
    iVar2 = -1;
  }
  else if (*param_1 == 1) {
    iVar2 = -1;
  }
  else {
    iVar2 = 0;
  }
  DAT_8041b418 = param_1;
  if (iVar2 == 0) {
    *param_1 = 1;
    uVar3 = 0;
  }
  else {
    DAT_8041b420[2] = 0xff020103;
    pcVar4 = (code *)*puVar1;
    if (pcVar4 != (code *)0x0) {
      (*pcVar4)(puVar1[1]);
    }
    uVar3 = 0xff020103;
  }
  return uVar3;
}



// ==== 8027dcc8  zz_027dcc8_ ====

int * zz_027dcc8_(void)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = *(int *)(DAT_8041b420 + 0xc);
  piVar2 = (int *)(DAT_8041b420 + 0x10);
  if (0 < iVar1) {
    do {
      if (*piVar2 == 1) goto LAB_8027dd14;
      piVar2 = piVar2 + 0x30;
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  piVar2 = (int *)0x0;
LAB_8027dd14:
  if (piVar2 == (int *)0x0) {
    piVar2 = (int *)0x0;
  }
  else {
    zz_02a94c4_((int)piVar2,0,0x30);
    *piVar2 = 2;
    piVar2[1] = 0;
    piVar2[2] = 0;
    piVar2[3] = 0;
    piVar2[4] = 2;
    piVar2[5] = -1;
    piVar2[6] = -1;
    piVar2[7] = -1;
    piVar2[8] = -1;
    piVar2[9] = -1;
    piVar2[10] = -1;
    piVar2[0xb] = -1;
    piVar2[0xc] = -1;
    piVar2[0xd] = -1;
    piVar2[0xe] = -1;
    piVar2[0xf] = -1;
    piVar2[0x10] = -1;
    piVar2[0x11] = -1;
    piVar2[0x12] = -1;
    piVar2[0x13] = -1;
    piVar2[0x14] = -1;
    piVar2[0x15] = -1;
    piVar2[0x16] = -1;
    piVar2[0x17] = -1;
    piVar2[0x18] = -1;
    piVar2[0x19] = -1;
    piVar2[0x1a] = -1;
    piVar2[0x1b] = -1;
    piVar2[0x1c] = -1;
    piVar2[0x1d] = -1;
    piVar2[0x1e] = -1;
    piVar2[0x1f] = -1;
    piVar2[0x20] = -1;
    piVar2[0x21] = -1;
    piVar2[0x22] = -1;
    piVar2[0x23] = -1;
    piVar2[0x24] = -1;
    piVar2[0x25] = -1;
    piVar2[0x26] = -1;
    piVar2[0x27] = -1;
    piVar2[0x28] = -1;
    piVar2[0x29] = -1;
    piVar2[0x2a] = -1;
    piVar2[0x2b] = -1;
    piVar2[0x2c] = -1;
    piVar2[0x2d] = -1;
    piVar2[0x2e] = -1;
    piVar2[0x2f] = -1;
  }
  return piVar2;
}



// ==== 8027de18  zz_027de18_ ====

int zz_027de18_(int *param_1)

{
  DAT_8041b418 = param_1;
  if (param_1 == (int *)0x0) {
    return -1;
  }
  return (int)~(*param_1 - 1U | 1U - *param_1) >> 0x1f;
}



// ==== 8027de48  zz_027de48_ ====

/* WARNING: Removing unreachable block (ram,0x8027de80) */

undefined4 zz_027de48_(int *param_1,int param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = DAT_8041b420;
  if (param_1 == (int *)0x0) {
    *DAT_8041b420 = param_2;
    piVar1[1] = param_3;
  }
  else {
    if (*param_1 == 1) {
      iVar2 = -1;
    }
    else {
      iVar2 = 0;
    }
    DAT_8041b418 = param_1;
    if (iVar2 != 0) {
      DAT_8041b420[2] = -0xfdfeff;
      if ((code *)*piVar1 != (code *)0x0) {
        (*(code *)*piVar1)(piVar1[1]);
      }
      return 0xff020101;
    }
    param_1[1] = param_2;
    param_1[2] = param_3;
  }
  return 0;
}



// ==== 8027defc  zz_027defc_ ====

int zz_027defc_(int param_1,int param_2)

{
  undefined4 *puVar1;
  code *pcVar2;
  
  puVar1 = DAT_8041b420;
  if (param_1 == 0) {
    DAT_8041b420[2] = param_2;
    if ((param_2 != 0) && (pcVar2 = (code *)*puVar1, pcVar2 != (code *)0x0)) {
      (*pcVar2)(puVar1[1]);
    }
  }
  else {
    *(int *)(param_1 + 0xc) = param_2;
    if ((param_2 != 0) && (*(code **)(param_1 + 4) != (code *)0x0)) {
      (**(code **)(param_1 + 4))(*(undefined4 *)(param_1 + 8));
    }
  }
  return param_2;
}



// ==== 8027df88  zz_027df88_ ====

void zz_027df88_(void)

{
  undefined4 *puVar1;
  int iVar2;
  code *pcVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  
  iVar4 = DAT_8041b420[3];
  piVar6 = DAT_8041b420 + 4;
  for (iVar5 = 0; puVar1 = DAT_8041b420, iVar5 < iVar4; iVar5 = iVar5 + 1) {
    if (*piVar6 != 1) {
      if (piVar6 == (int *)0x0) {
        iVar2 = -1;
      }
      else if (*piVar6 == 1) {
        iVar2 = -1;
      }
      else {
        iVar2 = 0;
      }
      DAT_8041b418 = piVar6;
      if (iVar2 == 0) {
        *piVar6 = 1;
      }
      else {
        DAT_8041b420[2] = 0xff020103;
        pcVar3 = (code *)*puVar1;
        if (pcVar3 != (code *)0x0) {
          (*pcVar3)(puVar1[1]);
        }
      }
    }
    piVar6 = piVar6 + 0x30;
  }
  zz_027d8a4_();
  zz_027dc28_();
  return;
}



// ==== 8027e06c  zz_027e06c_ ====

undefined4 zz_027e06c_(int param_1,undefined4 *param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  uint uVar5;
  
  DAT_8041b41c = s_CRI_MPS_GC_Ver_1_669_Build_Feb_6_802b86d0;
  DAT_8041b420 = param_2;
  zz_02a94c4_((int)param_2,0,(param_1 + -1) * 0xc0 + 0xd0U >> 2);
  puVar2 = DAT_8041b420;
  iVar3 = 0;
  *DAT_8041b420 = 0;
  puVar2[1] = 0;
  puVar2[2] = 0;
  DAT_8041b420[3] = param_1;
  puVar2 = DAT_8041b420 + 4;
  if (0 < param_1) {
    if ((8 < param_1) && (uVar5 = param_1 - 1U >> 3, puVar4 = puVar2, 0 < param_1 + -8)) {
      do {
        *puVar4 = 1;
        iVar3 = iVar3 + 8;
        puVar4[0x30] = 1;
        puVar4[0x60] = 1;
        puVar4[0x90] = 1;
        puVar4[0xc0] = 1;
        puVar4[0xf0] = 1;
        puVar4[0x120] = 1;
        puVar4[0x150] = 1;
        puVar4 = puVar4 + 0x180;
        uVar5 = uVar5 - 1;
      } while (uVar5 != 0);
    }
    iVar1 = param_1 - iVar3;
    puVar2 = puVar2 + iVar3 * 0x30;
    if (iVar3 < param_1) {
      do {
        *puVar2 = 1;
        puVar2 = puVar2 + 0x30;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
  }
  zz_027d8a8_();
  zz_027dc2c_();
  return 0;
}



// ==== 8027e18c  zz_027e18c_ ====

void zz_027e18c_(undefined4 *param_1)

{
  undefined1 *puVar1;
  undefined1 uVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  char cVar8;
  char cVar9;
  char cVar10;
  char cVar11;
  char cVar12;
  char cVar13;
  char cVar14;
  char cVar15;
  char cVar16;
  char *pcVar17;
  char cVar18;
  undefined1 *puVar19;
  char *pcVar20;
  char *pcVar21;
  int iVar22;
  char local_c8 [64];
  char local_88 [76];
  
  cVar18 = '\0';
  pcVar17 = local_88;
  iVar22 = 4;
  do {
    *pcVar17 = cVar18;
    pcVar17[1] = cVar18 + '\x01';
    pcVar17[2] = cVar18 + '\x02';
    cVar16 = cVar18 + '\t';
    cVar15 = cVar18 + '\n';
    pcVar17[3] = cVar18 + '\x03';
    cVar14 = cVar18 + '\v';
    pcVar17[4] = cVar18 + '\x04';
    cVar13 = cVar18 + '\f';
    pcVar17[5] = cVar18 + '\x05';
    cVar12 = cVar18 + '\r';
    pcVar17[6] = cVar18 + '\x06';
    cVar11 = cVar18 + '\x0e';
    pcVar17[7] = cVar18 + '\a';
    cVar10 = cVar18 + '\x0f';
    pcVar17[8] = cVar18 + '\b';
    cVar18 = cVar18 + '\x10';
    pcVar17[9] = cVar16;
    pcVar17[10] = cVar15;
    pcVar17[0xb] = cVar14;
    pcVar17[0xc] = cVar13;
    pcVar17[0xd] = cVar12;
    pcVar17[0xe] = cVar11;
    pcVar17[0xf] = cVar10;
    pcVar17 = pcVar17 + 0x10;
    iVar22 = iVar22 + -1;
  } while (iVar22 != 0);
  zz_027bfc8_(local_88,local_c8);
  pcVar20 = &DAT_8041b468;
  pcVar21 = &DAT_802b8728;
  puVar19 = &DAT_802b8768;
  iVar22 = 8;
  pcVar17 = local_c8;
  do {
    cVar18 = *pcVar17;
    cVar10 = pcVar21[1];
    uVar2 = *puVar19;
    cVar11 = pcVar17[1];
    cVar12 = pcVar21[2];
    cVar13 = pcVar17[2];
    cVar14 = pcVar21[3];
    cVar15 = pcVar17[3];
    cVar16 = pcVar21[4];
    cVar3 = pcVar17[4];
    cVar4 = pcVar21[5];
    cVar5 = pcVar17[5];
    cVar6 = pcVar21[6];
    cVar7 = pcVar21[7];
    cVar8 = pcVar17[6];
    *pcVar20 = local_c8[*pcVar21];
    cVar9 = local_c8[cVar10];
    cVar10 = pcVar17[7];
    pcVar21 = pcVar21 + 8;
    (&DAT_8041b428)[cVar18] = uVar2;
    pcVar17 = pcVar17 + 8;
    uVar2 = puVar19[1];
    pcVar20[1] = cVar9;
    cVar18 = local_c8[cVar12];
    (&DAT_8041b428)[cVar11] = uVar2;
    uVar2 = puVar19[2];
    pcVar20[2] = cVar18;
    cVar18 = local_c8[cVar14];
    (&DAT_8041b428)[cVar13] = uVar2;
    uVar2 = puVar19[3];
    pcVar20[3] = cVar18;
    cVar18 = local_c8[cVar16];
    (&DAT_8041b428)[cVar15] = uVar2;
    uVar2 = puVar19[4];
    pcVar20[4] = cVar18;
    cVar18 = local_c8[cVar4];
    (&DAT_8041b428)[cVar3] = uVar2;
    uVar2 = puVar19[5];
    pcVar20[5] = cVar18;
    cVar18 = local_c8[cVar6];
    (&DAT_8041b428)[cVar5] = uVar2;
    puVar1 = puVar19 + 6;
    uVar2 = puVar19[7];
    puVar19 = puVar19 + 8;
    (&DAT_8041b428)[cVar8] = *puVar1;
    cVar11 = local_c8[cVar7];
    pcVar20[6] = cVar18;
    pcVar20[7] = cVar11;
    pcVar20 = pcVar20 + 8;
    (&DAT_8041b428)[cVar10] = uVar2;
    iVar22 = iVar22 + -1;
  } while (iVar22 != 0);
  if (param_1 + 8 != (undefined4 *)0x0) {
    zz_02a9400_(param_1 + 8,(undefined4 *)&DAT_8041b468,0x10);
  }
  if (param_1 != (undefined4 *)0x0) {
    zz_02a9400_(param_1,(undefined4 *)&DAT_802b8708,8);
  }
  return;
}



// ==== 8027e3e0  FUN_8027e3e0 ====

undefined4 FUN_8027e3e0(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  
  iVar2 = 0;
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x290);
  *(int *)(param_1 + 0x5c) = param_1 + 0xc60;
  *(undefined4 *)(param_1 + 0x6c) = 1;
  iVar3 = *(int *)(param_1 + 0x2e8) << 2;
  *(int *)(param_1 + 0x98) = iVar3;
  iVar4 = param_1;
  pcVar5 = (char *)(param_1 + 0x70);
  do {
    if (iVar3 < 0) {
      *(int *)(param_1 + 0x58) = iVar4 + 0x620;
      cVar1 = (**(code **)(param_1 + 0x12cc))(param_1,param_1 + 0x3c);
      *pcVar5 = cVar1;
    }
    iVar2 = iVar2 + 1;
    iVar3 = iVar3 << 1;
    iVar4 = iVar4 + 0x100;
    pcVar5 = pcVar5 + 1;
  } while (iVar2 < 6);
  Bowser__DrawShadow_cPoseAccumulator((char *)(param_1 + 0x70));
  return 0;
}



// ==== 8027e48c  FUN_8027e48c ====

undefined4 FUN_8027e48c(int param_1)

{
  undefined8 uVar1;
  char cVar2;
  undefined1 uVar3;
  int iVar4;
  
  uVar1 = DAT_802b87a8;
  *(undefined8 *)(param_1 + 0x620) = DAT_802b87a8;
  *(undefined8 *)(param_1 + 0x628) = uVar1;
  *(undefined8 *)(param_1 + 0x630) = uVar1;
  *(undefined8 *)(param_1 + 0x638) = uVar1;
  *(undefined8 *)(param_1 + 0x640) = uVar1;
  *(undefined8 *)(param_1 + 0x648) = uVar1;
  *(undefined8 *)(param_1 + 0x650) = uVar1;
  *(undefined8 *)(param_1 + 0x658) = uVar1;
  *(undefined8 *)(param_1 + 0x660) = uVar1;
  *(undefined8 *)(param_1 + 0x668) = uVar1;
  *(undefined8 *)(param_1 + 0x670) = uVar1;
  *(undefined8 *)(param_1 + 0x678) = uVar1;
  *(undefined8 *)(param_1 + 0x680) = uVar1;
  *(undefined8 *)(param_1 + 0x688) = uVar1;
  *(undefined8 *)(param_1 + 0x690) = uVar1;
  *(undefined8 *)(param_1 + 0x698) = uVar1;
  *(undefined8 *)(param_1 + 0x6a0) = uVar1;
  *(undefined8 *)(param_1 + 0x6a8) = uVar1;
  *(undefined8 *)(param_1 + 0x6b0) = uVar1;
  *(undefined8 *)(param_1 + 0x6b8) = uVar1;
  *(undefined8 *)(param_1 + 0x6c0) = uVar1;
  *(undefined8 *)(param_1 + 0x6c8) = uVar1;
  *(undefined8 *)(param_1 + 0x6d0) = uVar1;
  *(undefined8 *)(param_1 + 0x6d8) = uVar1;
  *(undefined8 *)(param_1 + 0x6e0) = uVar1;
  *(undefined8 *)(param_1 + 0x6e8) = uVar1;
  *(undefined8 *)(param_1 + 0x6f0) = uVar1;
  *(undefined8 *)(param_1 + 0x6f8) = uVar1;
  *(undefined8 *)(param_1 + 0x700) = uVar1;
  *(undefined8 *)(param_1 + 0x708) = uVar1;
  *(undefined8 *)(param_1 + 0x710) = uVar1;
  *(undefined8 *)(param_1 + 0x718) = uVar1;
  *(undefined8 *)(param_1 + 0x720) = uVar1;
  *(undefined8 *)(param_1 + 0x728) = uVar1;
  *(undefined8 *)(param_1 + 0x730) = uVar1;
  *(undefined8 *)(param_1 + 0x738) = uVar1;
  *(undefined8 *)(param_1 + 0x740) = uVar1;
  *(undefined8 *)(param_1 + 0x748) = uVar1;
  *(undefined8 *)(param_1 + 0x750) = uVar1;
  *(undefined8 *)(param_1 + 0x758) = uVar1;
  *(undefined8 *)(param_1 + 0x760) = uVar1;
  *(undefined8 *)(param_1 + 0x768) = uVar1;
  *(undefined8 *)(param_1 + 0x770) = uVar1;
  *(undefined8 *)(param_1 + 0x778) = uVar1;
  *(undefined8 *)(param_1 + 0x780) = uVar1;
  *(undefined8 *)(param_1 + 0x788) = uVar1;
  *(undefined8 *)(param_1 + 0x790) = uVar1;
  *(undefined8 *)(param_1 + 0x798) = uVar1;
  *(undefined8 *)(param_1 + 0x7a0) = uVar1;
  *(undefined8 *)(param_1 + 0x7a8) = uVar1;
  *(undefined8 *)(param_1 + 0x7b0) = uVar1;
  *(undefined8 *)(param_1 + 0x7b8) = uVar1;
  *(undefined8 *)(param_1 + 0x7c0) = uVar1;
  *(undefined8 *)(param_1 + 0x7c8) = uVar1;
  *(undefined8 *)(param_1 + 2000) = uVar1;
  *(undefined8 *)(param_1 + 0x7d8) = uVar1;
  *(undefined8 *)(param_1 + 0x7e0) = uVar1;
  *(undefined8 *)(param_1 + 0x7e8) = uVar1;
  *(undefined8 *)(param_1 + 0x7f0) = uVar1;
  *(undefined8 *)(param_1 + 0x7f8) = uVar1;
  *(undefined8 *)(param_1 + 0x800) = uVar1;
  *(undefined8 *)(param_1 + 0x808) = uVar1;
  *(undefined8 *)(param_1 + 0x810) = uVar1;
  *(undefined8 *)(param_1 + 0x818) = uVar1;
  *(undefined8 *)(param_1 + 0x820) = uVar1;
  *(undefined8 *)(param_1 + 0x828) = uVar1;
  *(undefined8 *)(param_1 + 0x830) = uVar1;
  *(undefined8 *)(param_1 + 0x838) = uVar1;
  *(undefined8 *)(param_1 + 0x840) = uVar1;
  *(undefined8 *)(param_1 + 0x848) = uVar1;
  *(undefined8 *)(param_1 + 0x850) = uVar1;
  *(undefined8 *)(param_1 + 0x858) = uVar1;
  *(undefined8 *)(param_1 + 0x860) = uVar1;
  *(undefined8 *)(param_1 + 0x868) = uVar1;
  *(undefined8 *)(param_1 + 0x870) = uVar1;
  *(undefined8 *)(param_1 + 0x878) = uVar1;
  *(undefined8 *)(param_1 + 0x880) = uVar1;
  *(undefined8 *)(param_1 + 0x888) = uVar1;
  *(undefined8 *)(param_1 + 0x890) = uVar1;
  *(undefined8 *)(param_1 + 0x898) = uVar1;
  *(undefined8 *)(param_1 + 0x8a0) = uVar1;
  *(undefined8 *)(param_1 + 0x8a8) = uVar1;
  *(undefined8 *)(param_1 + 0x8b0) = uVar1;
  *(undefined8 *)(param_1 + 0x8b8) = uVar1;
  *(undefined8 *)(param_1 + 0x8c0) = uVar1;
  *(undefined8 *)(param_1 + 0x8c8) = uVar1;
  *(undefined8 *)(param_1 + 0x8d0) = uVar1;
  *(undefined8 *)(param_1 + 0x8d8) = uVar1;
  *(undefined8 *)(param_1 + 0x8e0) = uVar1;
  *(undefined8 *)(param_1 + 0x8e8) = uVar1;
  *(undefined8 *)(param_1 + 0x8f0) = uVar1;
  *(undefined8 *)(param_1 + 0x8f8) = uVar1;
  *(undefined8 *)(param_1 + 0x900) = uVar1;
  *(undefined8 *)(param_1 + 0x908) = uVar1;
  *(undefined8 *)(param_1 + 0x910) = uVar1;
  *(undefined8 *)(param_1 + 0x918) = uVar1;
  *(undefined8 *)(param_1 + 0x920) = uVar1;
  *(undefined8 *)(param_1 + 0x928) = uVar1;
  *(undefined8 *)(param_1 + 0x930) = uVar1;
  *(undefined8 *)(param_1 + 0x938) = uVar1;
  *(undefined8 *)(param_1 + 0x940) = uVar1;
  *(undefined8 *)(param_1 + 0x948) = uVar1;
  *(undefined8 *)(param_1 + 0x950) = uVar1;
  *(undefined8 *)(param_1 + 0x958) = uVar1;
  *(undefined8 *)(param_1 + 0x960) = uVar1;
  *(undefined8 *)(param_1 + 0x968) = uVar1;
  *(undefined8 *)(param_1 + 0x970) = uVar1;
  *(undefined8 *)(param_1 + 0x978) = uVar1;
  *(undefined8 *)(param_1 + 0x980) = uVar1;
  *(undefined8 *)(param_1 + 0x988) = uVar1;
  *(undefined8 *)(param_1 + 0x990) = uVar1;
  *(undefined8 *)(param_1 + 0x998) = uVar1;
  *(undefined8 *)(param_1 + 0x9a0) = uVar1;
  *(undefined8 *)(param_1 + 0x9a8) = uVar1;
  *(undefined8 *)(param_1 + 0x9b0) = uVar1;
  *(undefined8 *)(param_1 + 0x9b8) = uVar1;
  *(undefined8 *)(param_1 + 0x9c0) = uVar1;
  *(undefined8 *)(param_1 + 0x9c8) = uVar1;
  *(undefined8 *)(param_1 + 0x9d0) = uVar1;
  *(undefined8 *)(param_1 + 0x9d8) = uVar1;
  *(undefined8 *)(param_1 + 0x9e0) = uVar1;
  *(undefined8 *)(param_1 + 0x9e8) = uVar1;
  *(undefined8 *)(param_1 + 0x9f0) = uVar1;
  *(undefined8 *)(param_1 + 0x9f8) = uVar1;
  *(undefined8 *)(param_1 + 0xa00) = uVar1;
  *(undefined8 *)(param_1 + 0xa08) = uVar1;
  *(undefined8 *)(param_1 + 0xa10) = uVar1;
  *(undefined8 *)(param_1 + 0xa18) = uVar1;
  *(undefined8 *)(param_1 + 0xa20) = uVar1;
  *(undefined8 *)(param_1 + 0xa28) = uVar1;
  *(undefined8 *)(param_1 + 0xa30) = uVar1;
  *(undefined8 *)(param_1 + 0xa38) = uVar1;
  *(undefined8 *)(param_1 + 0xa40) = uVar1;
  *(undefined8 *)(param_1 + 0xa48) = uVar1;
  *(undefined8 *)(param_1 + 0xa50) = uVar1;
  *(undefined8 *)(param_1 + 0xa58) = uVar1;
  *(undefined8 *)(param_1 + 0xa60) = uVar1;
  *(undefined8 *)(param_1 + 0xa68) = uVar1;
  *(undefined8 *)(param_1 + 0xa70) = uVar1;
  *(undefined8 *)(param_1 + 0xa78) = uVar1;
  *(undefined8 *)(param_1 + 0xa80) = uVar1;
  *(undefined8 *)(param_1 + 0xa88) = uVar1;
  *(undefined8 *)(param_1 + 0xa90) = uVar1;
  *(undefined8 *)(param_1 + 0xa98) = uVar1;
  *(undefined8 *)(param_1 + 0xaa0) = uVar1;
  *(undefined8 *)(param_1 + 0xaa8) = uVar1;
  *(undefined8 *)(param_1 + 0xab0) = uVar1;
  *(undefined8 *)(param_1 + 0xab8) = uVar1;
  *(undefined8 *)(param_1 + 0xac0) = uVar1;
  *(undefined8 *)(param_1 + 0xac8) = uVar1;
  *(undefined8 *)(param_1 + 0xad0) = uVar1;
  *(undefined8 *)(param_1 + 0xad8) = uVar1;
  *(undefined8 *)(param_1 + 0xae0) = uVar1;
  *(undefined8 *)(param_1 + 0xae8) = uVar1;
  *(undefined8 *)(param_1 + 0xaf0) = uVar1;
  *(undefined8 *)(param_1 + 0xaf8) = uVar1;
  *(undefined8 *)(param_1 + 0xb00) = uVar1;
  *(undefined8 *)(param_1 + 0xb08) = uVar1;
  *(undefined8 *)(param_1 + 0xb10) = uVar1;
  *(undefined8 *)(param_1 + 0xb18) = uVar1;
  *(undefined8 *)(param_1 + 0xb20) = uVar1;
  *(undefined8 *)(param_1 + 0xb28) = uVar1;
  *(undefined8 *)(param_1 + 0xb30) = uVar1;
  *(undefined8 *)(param_1 + 0xb38) = uVar1;
  *(undefined8 *)(param_1 + 0xb40) = uVar1;
  *(undefined8 *)(param_1 + 0xb48) = uVar1;
  *(undefined8 *)(param_1 + 0xb50) = uVar1;
  *(undefined8 *)(param_1 + 0xb58) = uVar1;
  iVar4 = param_1 + 0x3c;
  *(undefined8 *)(param_1 + 0xb60) = uVar1;
  *(undefined8 *)(param_1 + 0xb68) = uVar1;
  *(undefined8 *)(param_1 + 0xb70) = uVar1;
  *(undefined8 *)(param_1 + 0xb78) = uVar1;
  *(undefined8 *)(param_1 + 0xb80) = uVar1;
  *(undefined8 *)(param_1 + 0xb88) = uVar1;
  *(undefined8 *)(param_1 + 0xb90) = uVar1;
  *(undefined8 *)(param_1 + 0xb98) = uVar1;
  *(undefined8 *)(param_1 + 0xba0) = uVar1;
  *(undefined8 *)(param_1 + 0xba8) = uVar1;
  *(undefined8 *)(param_1 + 0xbb0) = uVar1;
  *(undefined8 *)(param_1 + 3000) = uVar1;
  *(undefined8 *)(param_1 + 0xbc0) = uVar1;
  *(undefined8 *)(param_1 + 0xbc8) = uVar1;
  *(undefined8 *)(param_1 + 0xbd0) = uVar1;
  *(undefined8 *)(param_1 + 0xbd8) = uVar1;
  *(undefined8 *)(param_1 + 0xbe0) = uVar1;
  *(undefined8 *)(param_1 + 0xbe8) = uVar1;
  *(undefined8 *)(param_1 + 0xbf0) = uVar1;
  *(undefined8 *)(param_1 + 0xbf8) = uVar1;
  *(undefined8 *)(param_1 + 0xc00) = uVar1;
  *(undefined8 *)(param_1 + 0xc08) = uVar1;
  *(undefined8 *)(param_1 + 0xc10) = uVar1;
  *(undefined8 *)(param_1 + 0xc18) = uVar1;
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x290);
  *(int *)(param_1 + 0x5c) = param_1 + 0xc20;
  *(undefined4 *)(param_1 + 0x6c) = 0;
  *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_1 + 0x12d8);
  *(int *)(param_1 + 100) = param_1 + 0x2ec;
  *(int *)(param_1 + 0x58) = param_1 + 0x620;
  cVar2 = (**(code **)(param_1 + 0x12c8))(param_1,iVar4);
  *(char *)(param_1 + 0x70) = cVar2;
  *(int *)(param_1 + 0x58) = param_1 + 0x720;
  uVar3 = (**(code **)(param_1 + 0x12c8))(param_1,iVar4);
  *(undefined1 *)(param_1 + 0x71) = uVar3;
  *(int *)(param_1 + 0x58) = param_1 + 0x820;
  uVar3 = (**(code **)(param_1 + 0x12c8))(param_1,iVar4);
  *(undefined1 *)(param_1 + 0x72) = uVar3;
  *(int *)(param_1 + 0x58) = param_1 + 0x920;
  uVar3 = (**(code **)(param_1 + 0x12c8))(param_1,iVar4);
  *(undefined1 *)(param_1 + 0x73) = uVar3;
  *(undefined4 *)(param_1 + 0x68) = *(undefined4 *)(param_1 + 0x12dc);
  *(int *)(param_1 + 100) = param_1 + 0x2f0;
  *(int *)(param_1 + 0x58) = param_1 + 0xa20;
  uVar3 = (**(code **)(param_1 + 0x12c8))(param_1,iVar4);
  *(undefined1 *)(param_1 + 0x74) = uVar3;
  *(int *)(param_1 + 100) = param_1 + 0x2f4;
  *(int *)(param_1 + 0x58) = param_1 + 0xb20;
  uVar3 = (**(code **)(param_1 + 0x12c8))(param_1,iVar4);
  *(undefined1 *)(param_1 + 0x75) = uVar3;
  zz_027c464_((char *)(param_1 + 0x70));
  return 0;
}



// ==== 8027e8e0  FUN_8027e8e0 ====

void FUN_8027e8e0(int param_1,int param_2)

{
  int iVar1;
  code *pcVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x2dc);
  *(undefined4 *)(param_1 + 0x2e8) = 0;
  iVar1 = iVar3 - param_2;
  pcVar2 = *(code **)(param_1 + 0x27c);
  while (iVar1 = iVar1 + 1, iVar1 < iVar3) {
    *(int *)(param_1 + 0x2dc) = iVar1;
    (*pcVar2)(param_1);
  }
  *(int *)(param_1 + 0x2dc) = iVar3;
  return;
}



// ==== 8027e960  FUN_8027e960 ====

void FUN_8027e960(int param_1,int param_2)

{
  short sVar1;
  short sVar2;
  uint uVar3;
  undefined8 *puVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  undefined8 *puVar8;
  int local_28;
  int local_24;
  
  puVar8 = *(undefined8 **)(param_1 + 0x22c);
  sVar1 = *(short *)(param_1 + 0x21a);
  sVar2 = *(short *)(param_1 + 0x218);
  *(undefined8 **)(param_1 + 0x22c) = puVar8 + param_2 * 0x30 + -0x30;
  while( true ) {
    param_2 = param_2 + -1;
    if (param_2 == 0) break;
    pcVar6 = (char *)(param_1 + (*(int *)(param_1 + 0x2dc) - param_2) * 2 + 0x1324);
    iVar5 = (int)*pcVar6;
    iVar7 = (int)pcVar6[1];
    local_28 = iVar7 * 8 + iVar5 * 8 * (int)*(short *)(param_1 + 0x218);
    local_24 = iVar7 * 0x10 + iVar5 * 0x10 * (int)*(short *)(param_1 + 0x21a);
    *(int *)(param_1 + 0xd0) = (int)sVar2;
    *(undefined8 **)(param_1 + 200) = puVar8;
    *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0x20c) + local_28;
    uVar3 = *(uint *)(param_1 + 0xd0) & 0xfffffff8;
    *(undefined8 *)(param_1 + 0xca0) = **(undefined8 **)(param_1 + 0xd8);
    puVar8 = (undefined8 *)((int)*(undefined8 **)(param_1 + 0xd8) + uVar3);
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xca8) = *puVar8;
    puVar8 = (undefined8 *)((int)puVar4 + uVar3);
    *(undefined8 *)(param_1 + 0xcb0) = *puVar4;
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xcb8) = *puVar8;
    puVar8 = (undefined8 *)((int)puVar4 + uVar3);
    *(undefined8 *)(param_1 + 0xcc0) = *puVar4;
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xcc8) = *puVar8;
    *(undefined8 *)(param_1 + 0xcd0) = *puVar4;
    *(undefined8 *)(param_1 + 0xcd8) = *(undefined8 *)((int)puVar4 + uVar3);
    puVar8 = *(undefined8 **)(param_1 + 200);
    *puVar8 = *(undefined8 *)(param_1 + 0xca0);
    puVar8[1] = *(undefined8 *)(param_1 + 0xca8);
    puVar8[2] = *(undefined8 *)(param_1 + 0xcb0);
    puVar8[3] = *(undefined8 *)(param_1 + 0xcb8);
    puVar8[4] = *(undefined8 *)(param_1 + 0xcc0);
    puVar8[5] = *(undefined8 *)(param_1 + 0xcc8);
    puVar8[6] = *(undefined8 *)(param_1 + 0xcd0);
    puVar8[7] = *(undefined8 *)(param_1 + 0xcd8);
    *(undefined8 **)(param_1 + 200) = puVar8 + 8;
    *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0x210) + local_28;
    uVar3 = *(uint *)(param_1 + 0xd0) & 0xfffffff8;
    *(undefined8 *)(param_1 + 0xce0) = **(undefined8 **)(param_1 + 0xd8);
    puVar8 = (undefined8 *)((int)*(undefined8 **)(param_1 + 0xd8) + uVar3);
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xce8) = *puVar8;
    puVar8 = (undefined8 *)((int)puVar4 + uVar3);
    *(undefined8 *)(param_1 + 0xcf0) = *puVar4;
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xcf8) = *puVar8;
    puVar8 = (undefined8 *)((int)puVar4 + uVar3);
    *(undefined8 *)(param_1 + 0xd00) = *puVar4;
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xd08) = *puVar8;
    *(undefined8 *)(param_1 + 0xd10) = *puVar4;
    *(undefined8 *)(param_1 + 0xd18) = *(undefined8 *)((int)puVar4 + uVar3);
    puVar8 = *(undefined8 **)(param_1 + 200);
    *puVar8 = *(undefined8 *)(param_1 + 0xce0);
    puVar8[1] = *(undefined8 *)(param_1 + 0xce8);
    puVar8[2] = *(undefined8 *)(param_1 + 0xcf0);
    puVar8[3] = *(undefined8 *)(param_1 + 0xcf8);
    puVar8[4] = *(undefined8 *)(param_1 + 0xd00);
    puVar8[5] = *(undefined8 *)(param_1 + 0xd08);
    puVar8[6] = *(undefined8 *)(param_1 + 0xd10);
    puVar8[7] = *(undefined8 *)(param_1 + 0xd18);
    *(int *)(param_1 + 0xd0) = (int)sVar1;
    *(undefined8 **)(param_1 + 200) = puVar8 + 8;
    *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0x214) + local_24;
    uVar3 = *(uint *)(param_1 + 0xd0) & 0xfffffff8;
    *(undefined8 *)(param_1 + 0xd20) = **(undefined8 **)(param_1 + 0xd8);
    puVar8 = (undefined8 *)((int)*(undefined8 **)(param_1 + 0xd8) + uVar3);
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xd28) = *puVar8;
    puVar8 = (undefined8 *)((int)puVar4 + uVar3);
    *(undefined8 *)(param_1 + 0xd30) = *puVar4;
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xd38) = *puVar8;
    puVar8 = (undefined8 *)((int)puVar4 + uVar3);
    *(undefined8 *)(param_1 + 0xd40) = *puVar4;
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xd48) = *puVar8;
    *(undefined8 *)(param_1 + 0xd50) = *puVar4;
    *(undefined8 *)(param_1 + 0xd58) = *(undefined8 *)((int)puVar4 + uVar3);
    puVar8 = *(undefined8 **)(param_1 + 200);
    *puVar8 = *(undefined8 *)(param_1 + 0xd20);
    puVar8[1] = *(undefined8 *)(param_1 + 0xd28);
    puVar8[2] = *(undefined8 *)(param_1 + 0xd30);
    puVar8[3] = *(undefined8 *)(param_1 + 0xd38);
    puVar8[4] = *(undefined8 *)(param_1 + 0xd40);
    puVar8[5] = *(undefined8 *)(param_1 + 0xd48);
    puVar8[6] = *(undefined8 *)(param_1 + 0xd50);
    puVar8[7] = *(undefined8 *)(param_1 + 0xd58);
    *(undefined8 **)(param_1 + 200) = puVar8 + 8;
    *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + 8;
    uVar3 = *(uint *)(param_1 + 0xd0) & 0xfffffff8;
    *(undefined8 *)(param_1 + 0xd60) = **(undefined8 **)(param_1 + 0xd8);
    puVar8 = (undefined8 *)((int)*(undefined8 **)(param_1 + 0xd8) + uVar3);
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xd68) = *puVar8;
    puVar8 = (undefined8 *)((int)puVar4 + uVar3);
    *(undefined8 *)(param_1 + 0xd70) = *puVar4;
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xd78) = *puVar8;
    puVar8 = (undefined8 *)((int)puVar4 + uVar3);
    *(undefined8 *)(param_1 + 0xd80) = *puVar4;
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xd88) = *puVar8;
    *(undefined8 *)(param_1 + 0xd90) = *puVar4;
    *(undefined8 *)(param_1 + 0xd98) = *(undefined8 *)((int)puVar4 + uVar3);
    puVar8 = *(undefined8 **)(param_1 + 200);
    *puVar8 = *(undefined8 *)(param_1 + 0xd60);
    puVar8[1] = *(undefined8 *)(param_1 + 0xd68);
    puVar8[2] = *(undefined8 *)(param_1 + 0xd70);
    puVar8[3] = *(undefined8 *)(param_1 + 0xd78);
    puVar8[4] = *(undefined8 *)(param_1 + 0xd80);
    puVar8[5] = *(undefined8 *)(param_1 + 0xd88);
    puVar8[6] = *(undefined8 *)(param_1 + 0xd90);
    puVar8[7] = *(undefined8 *)(param_1 + 0xd98);
    *(undefined8 **)(param_1 + 200) = puVar8 + 8;
    *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + (sVar1 + -1) * 8;
    uVar3 = *(uint *)(param_1 + 0xd0) & 0xfffffff8;
    *(undefined8 *)(param_1 + 0xda0) = **(undefined8 **)(param_1 + 0xd8);
    puVar8 = (undefined8 *)((int)*(undefined8 **)(param_1 + 0xd8) + uVar3);
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xda8) = *puVar8;
    puVar8 = (undefined8 *)((int)puVar4 + uVar3);
    *(undefined8 *)(param_1 + 0xdb0) = *puVar4;
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xdb8) = *puVar8;
    puVar8 = (undefined8 *)((int)puVar4 + uVar3);
    *(undefined8 *)(param_1 + 0xdc0) = *puVar4;
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xdc8) = *puVar8;
    *(undefined8 *)(param_1 + 0xdd0) = *puVar4;
    *(undefined8 *)(param_1 + 0xdd8) = *(undefined8 *)((int)puVar4 + uVar3);
    puVar8 = *(undefined8 **)(param_1 + 200);
    *puVar8 = *(undefined8 *)(param_1 + 0xda0);
    puVar8[1] = *(undefined8 *)(param_1 + 0xda8);
    puVar8[2] = *(undefined8 *)(param_1 + 0xdb0);
    puVar8[3] = *(undefined8 *)(param_1 + 0xdb8);
    puVar8[4] = *(undefined8 *)(param_1 + 0xdc0);
    puVar8[5] = *(undefined8 *)(param_1 + 0xdc8);
    puVar8[6] = *(undefined8 *)(param_1 + 0xdd0);
    puVar8[7] = *(undefined8 *)(param_1 + 0xdd8);
    *(undefined8 **)(param_1 + 200) = puVar8 + 8;
    *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + 8;
    uVar3 = *(uint *)(param_1 + 0xd0) & 0xfffffff8;
    *(undefined8 *)(param_1 + 0xde0) = **(undefined8 **)(param_1 + 0xd8);
    puVar8 = (undefined8 *)((int)*(undefined8 **)(param_1 + 0xd8) + uVar3);
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xde8) = *puVar8;
    puVar8 = (undefined8 *)((int)puVar4 + uVar3);
    *(undefined8 *)(param_1 + 0xdf0) = *puVar4;
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xdf8) = *puVar8;
    puVar8 = (undefined8 *)((int)puVar4 + uVar3);
    *(undefined8 *)(param_1 + 0xe00) = *puVar4;
    puVar4 = (undefined8 *)((int)puVar8 + uVar3);
    *(undefined8 *)(param_1 + 0xe08) = *puVar8;
    *(undefined8 *)(param_1 + 0xe10) = *puVar4;
    *(undefined8 *)(param_1 + 0xe18) = *(undefined8 *)((int)puVar4 + uVar3);
    puVar4 = *(undefined8 **)(param_1 + 200);
    *puVar4 = *(undefined8 *)(param_1 + 0xde0);
    puVar4[1] = *(undefined8 *)(param_1 + 0xde8);
    puVar4[2] = *(undefined8 *)(param_1 + 0xdf0);
    puVar4[3] = *(undefined8 *)(param_1 + 0xdf8);
    puVar8 = puVar4 + 8;
    puVar4[4] = *(undefined8 *)(param_1 + 0xe00);
    puVar4[5] = *(undefined8 *)(param_1 + 0xe08);
    puVar4[6] = *(undefined8 *)(param_1 + 0xe10);
    puVar4[7] = *(undefined8 *)(param_1 + 0xe18);
    zz_027eea8_((undefined8 *)(param_1 + 0xca0),&local_28,(int *)(param_1 + 0x21c));
  }
  return;
}



// ==== 8027eea8  zz_027eea8_ ====

void zz_027eea8_(undefined8 *param_1,int *param_2,int *param_3)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined8 *puVar4;
  undefined8 *puVar5;
  
  iVar3 = *param_3;
  iVar2 = *param_2;
  uVar1 = (int)*(short *)(param_3 + 3) & 0xfffffff8;
  *(undefined8 *)(iVar3 + iVar2) = *param_1;
  puVar4 = (undefined8 *)(iVar3 + iVar2 + uVar1);
  *puVar4 = param_1[1];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar4 = param_1[2];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar4 = param_1[3];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar4 = param_1[4];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar4 = param_1[5];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar4 = param_1[6];
  *(undefined8 *)((int)puVar4 + uVar1) = param_1[7];
  iVar3 = param_3[1];
  iVar2 = *param_2;
  *(undefined8 *)(iVar3 + iVar2) = param_1[8];
  puVar4 = (undefined8 *)(iVar3 + iVar2 + uVar1);
  *puVar4 = param_1[9];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar4 = param_1[10];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar4 = param_1[0xb];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar4 = param_1[0xc];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar4 = param_1[0xd];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar4 = param_1[0xe];
  *(undefined8 *)((int)puVar4 + uVar1) = param_1[0xf];
  uVar1 = (int)*(short *)((int)param_3 + 0xe) & 0xfffffff8;
  puVar4 = (undefined8 *)(param_3[2] + param_2[1]);
  *puVar4 = param_1[0x10];
  puVar4[1] = param_1[0x18];
  puVar5 = (undefined8 *)((int)(puVar4 + 1) + uVar1);
  *(undefined8 *)((int)puVar4 + uVar1) = param_1[0x11];
  puVar4 = (undefined8 *)((int)((int)puVar4 + uVar1) + uVar1);
  *puVar5 = param_1[0x19];
  puVar5 = (undefined8 *)((int)puVar5 + uVar1);
  *puVar4 = param_1[0x12];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar5 = param_1[0x1a];
  puVar5 = (undefined8 *)((int)puVar5 + uVar1);
  *puVar4 = param_1[0x13];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar5 = param_1[0x1b];
  puVar5 = (undefined8 *)((int)puVar5 + uVar1);
  *puVar4 = param_1[0x14];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar5 = param_1[0x1c];
  puVar5 = (undefined8 *)((int)puVar5 + uVar1);
  *puVar4 = param_1[0x15];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar5 = param_1[0x1d];
  puVar5 = (undefined8 *)((int)puVar5 + uVar1);
  *puVar4 = param_1[0x16];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar5 = param_1[0x1e];
  puVar5 = (undefined8 *)((int)puVar5 + uVar1);
  *puVar4 = param_1[0x17];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar5 = param_1[0x1f];
  puVar5 = (undefined8 *)((int)puVar5 + uVar1);
  *puVar4 = param_1[0x20];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar5 = param_1[0x28];
  puVar5 = (undefined8 *)((int)puVar5 + uVar1);
  *puVar4 = param_1[0x21];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar5 = param_1[0x29];
  puVar5 = (undefined8 *)((int)puVar5 + uVar1);
  *puVar4 = param_1[0x22];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar5 = param_1[0x2a];
  puVar5 = (undefined8 *)((int)puVar5 + uVar1);
  *puVar4 = param_1[0x23];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar5 = param_1[0x2b];
  puVar5 = (undefined8 *)((int)puVar5 + uVar1);
  *puVar4 = param_1[0x24];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar5 = param_1[0x2c];
  puVar5 = (undefined8 *)((int)puVar5 + uVar1);
  *puVar4 = param_1[0x25];
  puVar4 = (undefined8 *)((int)puVar4 + uVar1);
  *puVar5 = param_1[0x2d];
  puVar5 = (undefined8 *)((int)puVar5 + uVar1);
  *puVar4 = param_1[0x26];
  *puVar5 = param_1[0x2e];
  *(undefined8 *)((int)puVar4 + uVar1) = param_1[0x27];
  *(undefined8 *)((int)puVar5 + uVar1) = param_1[0x2f];
  return;
}



// ==== 8027f10c  zz_027f10c_ ====

void zz_027f10c_(undefined8 *param_1,int *param_2,int param_3)

{
  byte *pbVar1;
  short *psVar2;
  int iVar3;
  byte *pbVar4;
  byte *pbVar5;
  short *psVar6;
  int iVar7;
  int iVar8;
  
  psVar6 = (short *)param_2[1];
  iVar7 = 0;
  pbVar4 = (byte *)param_2[2];
  pbVar5 = (byte *)param_2[3];
  iVar3 = *param_2;
  do {
    if (param_3 < 0) {
      iVar8 = 8;
      do {
        *pbVar4 = *(byte *)(iVar3 + (int)*psVar6 + ((int)((uint)*pbVar4 + *pbVar5 + 1) >> 1));
        pbVar4[1] = *(byte *)(iVar3 + (int)psVar6[1] + ((int)((uint)pbVar4[1] + pbVar5[1] + 1) >> 1)
                             );
        pbVar4[2] = *(byte *)(iVar3 + (int)psVar6[2] + ((int)((uint)pbVar4[2] + pbVar5[2] + 1) >> 1)
                             );
        pbVar4[3] = *(byte *)(iVar3 + (int)psVar6[3] + ((int)((uint)pbVar4[3] + pbVar5[3] + 1) >> 1)
                             );
        pbVar4[4] = *(byte *)(iVar3 + (int)psVar6[4] + ((int)((uint)pbVar4[4] + pbVar5[4] + 1) >> 1)
                             );
        pbVar4[5] = *(byte *)(iVar3 + (int)psVar6[5] + ((int)((uint)pbVar4[5] + pbVar5[5] + 1) >> 1)
                             );
        pbVar4[6] = *(byte *)(iVar3 + (int)psVar6[6] + ((int)((uint)pbVar4[6] + pbVar5[6] + 1) >> 1)
                             );
        pbVar1 = pbVar5 + 7;
        pbVar5 = pbVar5 + 8;
        psVar2 = psVar6 + 7;
        psVar6 = psVar6 + 8;
        pbVar4[7] = *(byte *)(iVar3 + (int)*psVar2 + ((int)((uint)pbVar4[7] + *pbVar1 + 1) >> 1));
        pbVar4 = pbVar4 + 8;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
    else {
      iVar8 = 8;
      psVar6 = psVar6 + 0x40;
      do {
        *pbVar4 = (byte)((int)((uint)*pbVar4 + *pbVar5 + 1) >> 1);
        pbVar4[1] = (byte)((int)((uint)pbVar4[1] + pbVar5[1] + 1) >> 1);
        pbVar4[2] = (byte)((int)((uint)pbVar4[2] + pbVar5[2] + 1) >> 1);
        pbVar4[3] = (byte)((int)((uint)pbVar4[3] + pbVar5[3] + 1) >> 1);
        pbVar4[4] = (byte)((int)((uint)pbVar4[4] + pbVar5[4] + 1) >> 1);
        pbVar4[5] = (byte)((int)((uint)pbVar4[5] + pbVar5[5] + 1) >> 1);
        pbVar4[6] = (byte)((int)((uint)pbVar4[6] + pbVar5[6] + 1) >> 1);
        pbVar1 = pbVar5 + 7;
        pbVar5 = pbVar5 + 8;
        pbVar4[7] = (byte)((int)((uint)pbVar4[7] + *pbVar1 + 1) >> 1);
        pbVar4 = pbVar4 + 8;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
    }
    iVar7 = iVar7 + 1;
    param_3 = param_3 << 1;
    *param_1 = *(undefined8 *)(pbVar4 + -0x40);
    param_1[1] = *(undefined8 *)(pbVar4 + -0x38);
    param_1[2] = *(undefined8 *)(pbVar4 + -0x30);
    param_1[3] = *(undefined8 *)(pbVar4 + -0x28);
    param_1[4] = *(undefined8 *)(pbVar4 + -0x20);
    param_1[5] = *(undefined8 *)(pbVar4 + -0x18);
    param_1[6] = *(undefined8 *)(pbVar4 + -0x10);
    param_1[7] = *(undefined8 *)(pbVar4 + -8);
    param_1 = param_1 + 8;
  } while (iVar7 < 6);
  return;
}



// ==== 8027f394  zz_027f394_ ====

void zz_027f394_(undefined8 *param_1,int *param_2,int param_3)

{
  short *psVar1;
  int iVar2;
  byte *pbVar3;
  byte *pbVar4;
  short *psVar5;
  int iVar6;
  int iVar7;
  
  psVar5 = (short *)param_2[1];
  iVar6 = 0;
  iVar2 = *param_2;
  pbVar4 = (byte *)param_2[2];
  do {
    if (param_3 < 0) {
      iVar7 = 8;
      do {
        pbVar3 = pbVar4;
        *pbVar3 = *(byte *)(iVar2 + (uint)*pbVar3 + (int)*psVar5);
        pbVar3[1] = *(byte *)(iVar2 + (uint)pbVar3[1] + (int)psVar5[1]);
        pbVar3[2] = *(byte *)(iVar2 + (uint)pbVar3[2] + (int)psVar5[2]);
        pbVar3[3] = *(byte *)(iVar2 + (uint)pbVar3[3] + (int)psVar5[3]);
        pbVar3[4] = *(byte *)(iVar2 + (uint)pbVar3[4] + (int)psVar5[4]);
        pbVar3[5] = *(byte *)(iVar2 + (uint)pbVar3[5] + (int)psVar5[5]);
        pbVar3[6] = *(byte *)(iVar2 + (uint)pbVar3[6] + (int)psVar5[6]);
        psVar1 = psVar5 + 7;
        psVar5 = psVar5 + 8;
        pbVar3[7] = *(byte *)(iVar2 + (uint)pbVar3[7] + (int)*psVar1);
        iVar7 = iVar7 + -1;
        pbVar4 = pbVar3 + 8;
      } while (iVar7 != 0);
      pbVar4 = pbVar3 + -0x38;
    }
    else {
      psVar5 = psVar5 + 0x40;
    }
    iVar6 = iVar6 + 1;
    *param_1 = *(undefined8 *)pbVar4;
    param_3 = param_3 << 1;
    param_1[1] = *(undefined8 *)(pbVar4 + 8);
    param_1[2] = *(undefined8 *)(pbVar4 + 0x10);
    param_1[3] = *(undefined8 *)(pbVar4 + 0x18);
    param_1[4] = *(undefined8 *)(pbVar4 + 0x20);
    param_1[5] = *(undefined8 *)(pbVar4 + 0x28);
    param_1[6] = *(undefined8 *)(pbVar4 + 0x30);
    param_1[7] = *(undefined8 *)(pbVar4 + 0x38);
    param_1 = param_1 + 8;
    pbVar4 = pbVar4 + 0x40;
  } while (iVar6 < 6);
  return;
}



// ==== 8027f4cc  zz_027f4cc_ ====

void zz_027f4cc_(int param_1,int param_2,int *param_3,int *param_4,int param_5)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  code *pcVar10;
  code *pcVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  
  iVar12 = param_1 + 0xc4;
  iVar13 = (int)*(short *)(param_4 + 3);
  uVar9 = *(uint *)(param_1 + 0x174);
  iVar14 = (int)*(short *)((int)param_4 + 0xe);
  pcVar4 = (char *)(param_1 + *(int *)(param_1 + 0x2dc) * 2 + 0x1324);
  iVar5 = (int)*pcVar4;
  iVar2 = (int)pcVar4[1];
  iVar3 = uVar9 * 0x10 + -0x7fbe4b58;
  *param_3 = iVar2 * 8 + iVar5 * 8 * iVar13;
  param_3[1] = iVar2 * 0x10 + iVar5 * 0x10 * iVar14;
  uVar7 = *(uint *)(param_5 + 0x1c);
  uVar6 = *(uint *)(param_5 + 0x18);
  iVar5 = *param_3;
  uVar1 = (int)uVar6 / 2 & 1;
  pcVar10 = *(code **)(iVar3 + ((uVar7 & 1) * 2 + (uVar6 & 1)) * 4);
  iVar8 = param_3[1];
  pcVar11 = *(code **)(iVar3 + (((int)uVar7 / 2 & 1U) * 2 + uVar1) * 4);
  *(int *)(param_1 + 0xd4) = iVar13;
  *(int *)(param_1 + 0xcc) = param_2;
  iVar5 = iVar5 + ((int)(uVar6 - ((int)uVar6 >> 0x1f)) >> 2) +
                  ((int)(uVar7 - ((int)uVar7 >> 0x1f)) >> 2) * iVar13;
  iVar2 = *param_4 + iVar5;
  *(int *)(param_1 + 0xd8) = iVar2;
  *(uint *)(param_1 + 0xdc) = iVar13 + (uVar1 & (int)(-uVar9 | uVar9) >> 0x1f) + iVar2;
  (*pcVar11)(iVar12);
  *(int *)(param_1 + 0xcc) = param_2 + 0x40;
  iVar5 = param_4[1] + iVar5;
  *(int *)(param_1 + 0xd8) = iVar5;
  *(uint *)(param_1 + 0xdc) = iVar13 + (uVar1 & (int)(-uVar9 | uVar9) >> 0x1f) + iVar5;
  (*pcVar11)(iVar12);
  *(int *)(param_1 + 0xd4) = iVar14;
  *(int *)(param_1 + 0xcc) = param_2 + 0x80;
  iVar2 = param_4[2] + iVar8 + ((int)uVar6 >> 1) + ((int)uVar7 >> 1) * iVar14;
  *(int *)(param_1 + 0xd8) = iVar2;
  *(uint *)(param_1 + 0xdc) = iVar14 + (uVar6 & 1 & (int)(-uVar9 | uVar9) >> 0x1f) + iVar2;
  (*pcVar10)(iVar12);
  *(int *)(param_1 + 0xcc) = param_2 + 0xc0;
  *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + 8;
  *(int *)(param_1 + 0xdc) = *(int *)(param_1 + 0xdc) + 8;
  (*pcVar10)(iVar12);
  *(int *)(param_1 + 0xcc) = param_2 + 0x100;
  iVar2 = (iVar14 + -1) * 8;
  *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + iVar2;
  *(int *)(param_1 + 0xdc) = *(int *)(param_1 + 0xdc) + iVar2;
  (*pcVar10)(iVar12);
  *(int *)(param_1 + 0xcc) = param_2 + 0x140;
  *(int *)(param_1 + 0xd8) = *(int *)(param_1 + 0xd8) + 8;
  *(int *)(param_1 + 0xdc) = *(int *)(param_1 + 0xdc) + 8;
  (*pcVar10)(iVar12);
  return;
}



// ==== 8027f734  FUN_8027f734 ====

void FUN_8027f734(int param_1)

{
  undefined8 *puVar1;
  int aiStack_18 [3];
  
  zz_027f4cc_(param_1,*(int *)(param_1 + 0xf0),aiStack_18,(int *)(param_1 + 0x20c),param_1 + 0x294);
  zz_027f4cc_(param_1,*(int *)(param_1 + 0xf4),aiStack_18,(int *)(param_1 + 0x21c),param_1 + 0x2b8);
  puVar1 = *(undefined8 **)(param_1 + 0x22c);
  *(undefined8 **)(param_1 + 0x22c) = puVar1 + 0x30;
  zz_027f10c_(puVar1,(int *)(param_1 + 0xe8),*(int *)(param_1 + 0x2e8));
  return;
}



// ==== 8027f7b8  FUN_8027f7b8 ====

void FUN_8027f7b8(int param_1)

{
  undefined8 *puVar1;
  int aiStack_18 [4];
  
  zz_027f4cc_(param_1,*(int *)(param_1 + 0xf0),aiStack_18,(int *)(param_1 + 0x21c),param_1 + 0x2b8);
  puVar1 = *(undefined8 **)(param_1 + 0x22c);
  *(undefined8 **)(param_1 + 0x22c) = puVar1 + 0x30;
  zz_027f394_(puVar1,(int *)(param_1 + 0xe8),*(int *)(param_1 + 0x2e8));
  return;
}



// ==== 8027f818  FUN_8027f818 ====

void FUN_8027f818(int param_1)

{
  undefined8 *puVar1;
  int aiStack_18 [4];
  
  zz_027f4cc_(param_1,*(int *)(param_1 + 0xf0),aiStack_18,(int *)(param_1 + 0x20c),param_1 + 0x294);
  puVar1 = *(undefined8 **)(param_1 + 0x22c);
  *(undefined8 **)(param_1 + 0x22c) = puVar1 + 0x30;
  zz_027f394_(puVar1,(int *)(param_1 + 0xe8),*(int *)(param_1 + 0x2e8));
  return;
}



// ==== 8027f878  FUN_8027f878 ====

void FUN_8027f878(int param_1)

{
  undefined8 *puVar1;
  int aiStack_18 [3];
  
  zz_027f4cc_(param_1,*(int *)(param_1 + 0xf0),aiStack_18,(int *)(param_1 + 0x20c),param_1 + 0x294);
  puVar1 = *(undefined8 **)(param_1 + 0x22c);
  *(undefined8 **)(param_1 + 0x22c) = puVar1 + 0x30;
  zz_027f394_(puVar1,(int *)(param_1 + 0xe8),*(int *)(param_1 + 0x2e8));
  zz_027eea8_(*(undefined8 **)(param_1 + 0xf0),aiStack_18,(int *)(param_1 + 0x21c));
  return;
}



// ==== 8027f8f4  zz_027f8f4_ ====

void zz_027f8f4_(short *param_1,undefined8 *param_2,int param_3,int param_4)

{
  short *psVar1;
  undefined4 *puVar2;
  int iVar3;
  uint uVar4;
  undefined8 *puVar5;
  undefined1 *puVar6;
  undefined8 *puVar7;
  int iVar8;
  
  puVar2 = (undefined4 *)(param_3 + 4);
  iVar3 = 6;
  do {
    puVar5 = (undefined8 *)*puVar2;
    uVar4 = puVar2[1];
    iVar8 = 4;
    puVar2 = puVar2 + 2;
    puVar7 = puVar5;
    do {
      *(undefined1 *)puVar7 = *(undefined1 *)(param_4 + *param_1);
      *(undefined1 *)((int)puVar7 + 1) = *(undefined1 *)(param_4 + param_1[1]);
      *(undefined1 *)((int)puVar7 + 2) = *(undefined1 *)(param_4 + param_1[2]);
      *(undefined1 *)((int)puVar7 + 3) = *(undefined1 *)(param_4 + param_1[3]);
      *(undefined1 *)((int)puVar7 + 4) = *(undefined1 *)(param_4 + param_1[4]);
      *(undefined1 *)((int)puVar7 + 5) = *(undefined1 *)(param_4 + param_1[5]);
      *(undefined1 *)((int)puVar7 + 6) = *(undefined1 *)(param_4 + param_1[6]);
      *(undefined1 *)((int)puVar7 + 7) = *(undefined1 *)(param_4 + param_1[7]);
      puVar6 = (undefined1 *)((int)puVar7 + uVar4);
      *puVar6 = *(undefined1 *)(param_4 + param_1[8]);
      puVar6[1] = *(undefined1 *)(param_4 + param_1[9]);
      puVar6[2] = *(undefined1 *)(param_4 + param_1[10]);
      puVar6[3] = *(undefined1 *)(param_4 + param_1[0xb]);
      puVar6[4] = *(undefined1 *)(param_4 + param_1[0xc]);
      puVar6[5] = *(undefined1 *)(param_4 + param_1[0xd]);
      puVar6[6] = *(undefined1 *)(param_4 + param_1[0xe]);
      psVar1 = param_1 + 0xf;
      param_1 = param_1 + 0x10;
      puVar6[7] = *(undefined1 *)(param_4 + *psVar1);
      puVar7 = (undefined8 *)(puVar6 + uVar4);
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
    uVar4 = uVar4 & 0xfffffff8;
    iVar3 = iVar3 + -1;
    *param_2 = *puVar5;
    puVar7 = (undefined8 *)((int)((int)puVar5 + uVar4) + uVar4);
    param_2[1] = *(undefined8 *)((int)puVar5 + uVar4);
    puVar5 = (undefined8 *)((int)puVar7 + uVar4);
    param_2[2] = *puVar7;
    puVar7 = (undefined8 *)((int)puVar5 + uVar4);
    param_2[3] = *puVar5;
    puVar5 = (undefined8 *)((int)puVar7 + uVar4);
    param_2[4] = *puVar7;
    puVar7 = (undefined8 *)((int)puVar5 + uVar4);
    param_2[5] = *puVar5;
    param_2[6] = *puVar7;
    param_2[7] = *(undefined8 *)((int)puVar7 + uVar4);
    param_2 = param_2 + 8;
  } while (0 < iVar3);
  return;
}



// ==== 8027fa50  FUN_8027fa50 ====

void FUN_8027fa50(int param_1)

{
  undefined8 *puVar1;
  
  puVar1 = *(undefined8 **)(param_1 + 0x22c);
  *(undefined8 **)(param_1 + 0x22c) = puVar1 + 0x30;
  zz_027f8f4_((short *)(param_1 + 800),puVar1,param_1 + 300,*(int *)(param_1 + 0x38));
  return;
}



// ==== 8027fa8c  FUN_8027fa8c ====

void FUN_8027fa8c(int param_1)

{
  undefined8 *puVar1;
  char *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  puVar1 = *(undefined8 **)(param_1 + 0x22c);
  *(undefined8 **)(param_1 + 0x22c) = puVar1 + 0x30;
  pcVar2 = (char *)(param_1 + *(int *)(param_1 + 0x2dc) * 2 + 0x1324);
  iVar5 = (int)*pcVar2;
  iVar3 = (int)pcVar2[1];
  iVar4 = iVar3 * 8 + iVar5 * 8 * (int)*(short *)(param_1 + 0x228);
  *(int *)(param_1 + 0xfc) = *(int *)(param_1 + 0x21c) + iVar4;
  *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x220) + iVar4;
  *(int *)(param_1 + 0x10c) =
       *(int *)(param_1 + 0x224) + iVar3 * 0x10 + iVar5 * 0x10 * (int)*(short *)(param_1 + 0x22a);
  *(int *)(param_1 + 0x114) = *(int *)(param_1 + 0x10c) + 8;
  *(int *)(param_1 + 0x11c) = *(int *)(param_1 + 0x10c) + *(short *)(param_1 + 0x22a) * 8;
  *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x11c) + 8;
  zz_027f8f4_((short *)(param_1 + 800),puVar1,param_1 + 0xf8,*(int *)(param_1 + 0x38));
  return;
}



// ==== 8027fb5c  zz_027fb5c_ ====

void zz_027fb5c_(int param_1)

{
  undefined4 uVar1;
  
  uVar1 = 4;
  if (*(int *)(param_1 + 0x17c) == 0) {
    uVar1 = 0xffffffff;
  }
  *(undefined4 *)(param_1 + 300) = uVar1;
  *(undefined4 *)(param_1 + 0xf8) = uVar1;
  return;
}



// ==== 8027fb7c  zz_027fb7c_ ====

void zz_027fb7c_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  uVar2 = 4;
  if (*(int *)(param_1 + 0x17c) == 0) {
    uVar2 = 0xffffffff;
  }
  *(undefined4 *)(param_1 + 0xf8) = uVar2;
  *(int *)(param_1 + 0x100) = (int)*(short *)(param_1 + 0x228);
  *(int *)(param_1 + 0x108) = (int)*(short *)(param_1 + 0x228);
  iVar1 = (int)*(short *)(param_1 + 0x22a);
  *(int *)(param_1 + 0x110) = iVar1;
  *(int *)(param_1 + 0x118) = iVar1;
  *(int *)(param_1 + 0x120) = iVar1;
  *(int *)(param_1 + 0x128) = iVar1;
  return;
}



// ==== 8027fbbc  zz_027fbbc_ ====

void zz_027fbbc_(int param_1)

{
  undefined4 uVar1;
  int iVar2;
  
  zz_028500c_();
  iVar2 = param_1 + 0xca0;
  uVar1 = 4;
  if (*(int *)(param_1 + 0x17c) == 0) {
    uVar1 = 0xffffffff;
  }
  *(undefined4 *)(param_1 + 300) = uVar1;
  *(int *)(param_1 + 0x130) = iVar2;
  *(int *)(param_1 + 0x138) = iVar2;
  *(int *)(param_1 + 0x140) = iVar2;
  *(int *)(param_1 + 0x148) = iVar2;
  *(int *)(param_1 + 0x150) = iVar2;
  *(int *)(param_1 + 0x158) = iVar2;
  *(undefined4 *)(param_1 + 0x134) = 8;
  *(undefined4 *)(param_1 + 0x13c) = 8;
  *(undefined4 *)(param_1 + 0x144) = 8;
  *(undefined4 *)(param_1 + 0x14c) = 8;
  *(undefined4 *)(param_1 + 0x154) = 8;
  *(undefined4 *)(param_1 + 0x15c) = 8;
  return;
}



// ==== 8027fc40  FUN_8027fc40 ====

void FUN_8027fc40(uint *param_1,int *param_2)

{
  short sVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint uVar8;
  int iVar9;
  int aiStack_28 [2];
  int aiStack_20 [5];
  
  (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x4aa);
  piVar2 = (int *)(param_1[0x4aa] & 0xfffffffc);
  iVar9 = (param_1[0x4aa] - (int)piVar2) * 8;
  uVar5 = piVar2[1];
  puVar7 = (uint *)(piVar2 + 2);
  uVar6 = iVar9 + param_1[0x4ac];
  if ((int)uVar6 < 0x20) {
    uVar3 = (*piVar2 << iVar9) << param_1[0x4ac];
  }
  else {
    uVar6 = uVar6 - 0x20;
    uVar3 = uVar5 << uVar6;
    uVar5 = *puVar7;
    puVar7 = (uint *)(piVar2 + 3);
  }
  while( true ) {
    uVar4 = uVar3 >> 9;
    if (9 < (int)uVar6) {
      uVar4 = uVar4 | uVar5 >> 0x29 - uVar6;
    }
    if (uVar4 == 0) break;
    uVar4 = param_1[0xb7];
    while( true ) {
      do {
        uVar8 = uVar3 >> 0x14;
        if (0x14 < (int)uVar6) {
          uVar8 = uVar8 | uVar5 >> 0x34 - uVar6;
        }
        if (uVar8 >> 8 == 0) {
          sVar1 = *(short *)(DAT_8041cfac + uVar8 * 2);
        }
        else {
          sVar1 = *(short *)(DAT_8041cfa8 + (uVar8 >> 5 & 0x7fffffe));
        }
        uVar8 = (uint)sVar1;
        uVar6 = uVar6 + (uVar8 & 0xf);
        if ((int)uVar6 < 0x20) {
          uVar3 = uVar3 << (uVar8 & 0xf);
        }
        else {
          uVar6 = uVar6 - 0x20;
          uVar3 = uVar5 << uVar6;
          uVar5 = *puVar7;
          puVar7 = puVar7 + 1;
        }
        iVar9 = (int)(uVar8 >> 2 & 0xff) >> 2;
      } while (iVar9 == 0x22);
      if (iVar9 != 0x23) break;
      param_1[0xb7] = param_1[0xb7] + 0x21;
    }
    if (iVar9 == 0x24) {
      iVar9 = -2;
    }
    else {
      param_1[0xb7] = param_1[0xb7] + iVar9;
      param_1[0xb9] = uVar8 >> 10;
      if ((int)param_1[0xb8] < (int)param_1[0xb7]) {
        iVar9 = -2;
      }
      else {
        iVar9 = param_1[0xb7] - uVar4;
      }
    }
    if (iVar9 == -2) break;
    *param_1 = uVar3;
    param_1[1] = uVar5;
    param_1[2] = uVar6;
    param_1[3] = (uint)puVar7;
    (*(code *)param_1[0x9c])(param_1);
    (*(code *)param_1[0x9e])(param_1);
    uVar5 = param_1[0x4b5];
    param_1[0x4b5] = uVar5 - 1;
    if ((int)(uVar5 - 1) < 1) {
      param_1[0x4b5] = param_1[0x61];
      (*(code *)param_1[0x62])(param_1[99]);
    }
    uVar5 = param_1[1];
    puVar7 = (uint *)param_1[3];
    if (param_1[2] == 0x1f) {
      uVar4 = *puVar7;
      uVar6 = 0;
      puVar7 = puVar7 + 1;
      uVar3 = uVar5;
      uVar5 = uVar4;
    }
    else {
      uVar3 = *param_1 << 1;
      uVar6 = param_1[2] + 1;
    }
    if (-1 < (int)*param_1) break;
    uVar4 = uVar6 & 7;
    iVar9 = (int)puVar7 + ((((int)((uVar6 - uVar4) + 7) >> 3) + -8) - param_1[0x4aa]);
    if ((int)(param_1[0x4ab] - iVar9) < 0x801) {
      zz_02779cc_((int *)(param_1 + 0x4aa),iVar9,(int *)(param_1 + 0x4aa),aiStack_20);
      (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x4aa);
      (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_20);
      (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x4aa);
      piVar2 = (int *)(param_1[0x4aa] & 0xfffffffc);
      iVar9 = (param_1[0x4aa] - (int)piVar2) * 8;
      uVar5 = piVar2[1];
      puVar7 = (uint *)(piVar2 + 2);
      uVar6 = iVar9 + uVar4;
      if ((int)uVar6 < 0x20) {
        uVar3 = (*piVar2 << iVar9) << uVar4;
      }
      else {
        uVar6 = uVar6 - 0x20;
        uVar3 = uVar5 << uVar6;
        uVar5 = *puVar7;
        puVar7 = (uint *)(piVar2 + 3);
      }
    }
  }
  param_1[0x4ac] = uVar6 & 7;
  zz_02779cc_((int *)(param_1 + 0x4aa),
              (int)puVar7 + ((((int)((uVar6 - param_1[0x4ac]) + 7) >> 3) + -8) - param_1[0x4aa]),
              (int *)(param_1 + 0x4aa),aiStack_28);
  (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x4aa);
  (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_28);
  zz_028215c_(param_2);
  return;
}



// ==== 8027ffe8  FUN_8027ffe8 ====

void FUN_8027ffe8(uint *param_1,int *param_2)

{
  short sVar1;
  bool bVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int aiStack_38 [2];
  int aiStack_30 [5];
  
  bVar2 = true;
  (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x4aa);
  piVar3 = (int *)(param_1[0x4aa] & 0xfffffffc);
  iVar7 = (param_1[0x4aa] - (int)piVar3) * 8;
  uVar9 = piVar3[1];
  puVar8 = (uint *)(piVar3 + 2);
  uVar11 = iVar7 + param_1[0x4ac];
  if ((int)uVar11 < 0x20) {
    uVar10 = (*piVar3 << iVar7) << param_1[0x4ac];
  }
  else {
    uVar11 = uVar11 - 0x20;
    uVar10 = uVar9 << uVar11;
    uVar9 = *puVar8;
    puVar8 = (uint *)(piVar3 + 3);
  }
  while( true ) {
    uVar4 = uVar10 >> 9;
    if (9 < (int)uVar11) {
      uVar4 = uVar4 | uVar9 >> 0x29 - uVar11;
    }
    if (uVar4 == 0) break;
    uVar4 = param_1[0xb7];
    while( true ) {
      do {
        uVar6 = uVar10 >> 0x15;
        if (0x15 < (int)uVar11) {
          uVar6 = uVar6 | uVar9 >> 0x35 - uVar11;
        }
        if (uVar6 >> 7 == 0) {
          sVar1 = *(short *)(DAT_8041cf9c + uVar6 * 2);
        }
        else {
          sVar1 = *(short *)(DAT_8041cf98 + (uVar6 >> 5 & 0x7fffffe));
        }
        uVar6 = (uint)sVar1;
        uVar11 = uVar11 + (uVar6 & 0xf);
        if ((int)uVar11 < 0x20) {
          uVar10 = uVar10 << (uVar6 & 0xf);
        }
        else {
          uVar11 = uVar11 - 0x20;
          uVar10 = uVar9 << uVar11;
          uVar9 = *puVar8;
          puVar8 = puVar8 + 1;
        }
        iVar7 = (int)(uVar6 >> 2 & 0xff) >> 2;
      } while (iVar7 == 0x22);
      if (iVar7 != 0x23) break;
      param_1[0xb7] = param_1[0xb7] + 0x21;
    }
    if (iVar7 == 0x24) {
      uVar4 = 0xfffffffe;
    }
    else {
      param_1[0xb7] = param_1[0xb7] + iVar7;
      param_1[0xb9] = uVar6 >> 10;
      if ((int)param_1[0xb8] < (int)param_1[0xb7]) {
        uVar4 = 0xfffffffe;
      }
      else {
        uVar4 = param_1[0xb7] - uVar4;
      }
    }
    if (uVar4 == 0xfffffffe) break;
    if ((!bVar2) && (1 < uVar4)) {
      (*(code *)param_1[0x9b])(param_1);
      param_1[0xbb] = 0x400;
      param_1[0xbd] = 0x400;
      param_1[0xbc] = 0x400;
    }
    if ((param_1[0xb9] & 0x20) == 0) {
      uVar4 = uVar10 >> 0x1a;
      if (0x1a < (int)uVar11) {
        uVar4 = uVar4 | uVar9 >> 0x3a - uVar11;
      }
      uVar6 = (uint)*(short *)(DAT_8041cf90 + uVar4 * 2);
      uVar4 = uVar6 & 0xff;
      uVar11 = uVar11 + uVar4;
      param_1[0xb9] = uVar6 >> 8;
      if ((int)uVar11 < 0x20) {
        uVar10 = uVar10 << uVar4;
      }
      else {
        uVar11 = uVar11 - 0x20;
        uVar10 = uVar9 << uVar11;
        uVar9 = *puVar8;
        puVar8 = puVar8 + 1;
      }
    }
    uVar4 = uVar10;
    if ((param_1[0xb9] & 0x10) != 0) {
      if ((int)uVar11 < 0x1b) {
        uVar4 = uVar10 << 5;
        uVar11 = uVar11 + 5;
      }
      else {
        uVar11 = uVar11 - 0x1b;
        uVar4 = uVar9;
        if (uVar11 != 0) {
          uVar10 = uVar10 | uVar9 >> 5 - uVar11;
          uVar4 = uVar9 << uVar11;
        }
        uVar9 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      param_1[0xa4] = uVar10 >> 0x1b;
    }
    if ((param_1[0xb9] & 8) != 0) {
      *param_1 = uVar4;
      param_1[1] = uVar9;
      param_1[2] = uVar11;
      param_1[3] = (uint)puVar8;
      iVar7 = zz_02805fc_(param_1,(int *)(param_1 + 0xa5),(int *)(param_1 + 0xab),
                          (int *)(param_1 + 0xa9));
      iVar5 = zz_02805fc_(param_1,(int *)(param_1 + 0xa5),(int *)(param_1 + 0xac),
                          (int *)(param_1 + 0xaa));
      uVar4 = *param_1;
      uVar9 = param_1[1];
      uVar11 = param_1[2];
      puVar8 = (uint *)param_1[3];
      if (iVar7 != 0 || iVar5 != 0) break;
    }
    if ((param_1[0xb9] & 4) != 0) {
      *param_1 = uVar4;
      param_1[1] = uVar9;
      param_1[2] = uVar11;
      param_1[3] = (uint)puVar8;
      iVar7 = zz_02805fc_(param_1,(int *)(param_1 + 0xae),(int *)(param_1 + 0xb4),
                          (int *)(param_1 + 0xb2));
      iVar5 = zz_02805fc_(param_1,(int *)(param_1 + 0xae),(int *)(param_1 + 0xb5),
                          (int *)(param_1 + 0xb3));
      uVar4 = *param_1;
      uVar9 = param_1[1];
      uVar11 = param_1[2];
      puVar8 = (uint *)param_1[3];
      if (iVar7 != 0 || iVar5 != 0) break;
    }
    if ((param_1[0xb9] & 2) == 0) {
      param_1[0xba] = 0;
    }
    else {
      uVar10 = uVar4 >> 0x17;
      if (0x17 < (int)uVar11) {
        uVar10 = uVar10 | uVar9 >> 0x37 - uVar11;
      }
      uVar6 = (uint)*(short *)(DAT_8041cf84 + uVar10 * 2);
      uVar10 = uVar6 & 0xff;
      uVar11 = uVar11 + uVar10;
      param_1[0xba] = (uVar6 & 0xfff0) << 0x10;
      if ((int)uVar11 < 0x20) {
        uVar4 = uVar4 << uVar10;
      }
      else {
        uVar11 = uVar11 - 0x20;
        uVar4 = uVar9 << uVar11;
        uVar9 = *puVar8;
        puVar8 = puVar8 + 1;
      }
    }
    *param_1 = uVar4;
    param_1[1] = uVar9;
    param_1[2] = uVar11;
    param_1[3] = (uint)puVar8;
    if ((param_1[0xb9] & 1) == 0) {
      param_1[0x9f] = *(uint *)((int)param_1 + (param_1[0xb9] & 0xc) + 0x27c);
      if (param_1[0xba] != 0) {
        (*(code *)param_1[0x9d])(param_1);
      }
      (*(code *)param_1[0x9f])(param_1);
      param_1[0xbb] = 0x400;
      param_1[0xbd] = 0x400;
      param_1[0xbc] = 0x400;
    }
    else {
      (*(code *)param_1[0x9c])(param_1);
      (*(code *)param_1[0x9e])(param_1);
      param_1[0xa9] = 0;
      param_1[0xaa] = 0;
      param_1[0xab] = 0;
      param_1[0xac] = 0;
      param_1[0xb2] = 0;
      param_1[0xb3] = 0;
      param_1[0xb4] = 0;
      param_1[0xb5] = 0;
    }
    uVar9 = param_1[0x4b5];
    param_1[0x4b5] = uVar9 - 1;
    if ((int)(uVar9 - 1) < 1) {
      param_1[0x4b5] = param_1[0x61];
      (*(code *)param_1[0x62])(param_1[99]);
    }
    uVar11 = param_1[2];
    puVar8 = (uint *)param_1[3];
    uVar4 = uVar11 & 7;
    uVar10 = *param_1;
    uVar9 = param_1[1];
    iVar7 = (int)puVar8 + ((((int)((uVar11 - uVar4) + 7) >> 3) + -8) - param_1[0x4aa]);
    if ((int)(param_1[0x4ab] - iVar7) < 0x801) {
      zz_02779cc_((int *)(param_1 + 0x4aa),iVar7,(int *)(param_1 + 0x4aa),aiStack_30);
      (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x4aa);
      (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_30);
      (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x4aa);
      piVar3 = (int *)(param_1[0x4aa] & 0xfffffffc);
      iVar7 = (param_1[0x4aa] - (int)piVar3) * 8;
      uVar9 = piVar3[1];
      puVar8 = (uint *)(piVar3 + 2);
      uVar11 = iVar7 + uVar4;
      if ((int)uVar11 < 0x20) {
        uVar10 = (*piVar3 << iVar7) << uVar4;
      }
      else {
        uVar11 = uVar11 - 0x20;
        uVar10 = uVar9 << uVar11;
        uVar9 = *puVar8;
        puVar8 = (uint *)(piVar3 + 3);
      }
    }
    bVar2 = false;
  }
  param_1[0x4ac] = uVar11 & 7;
  zz_02779cc_((int *)(param_1 + 0x4aa),
              (int)puVar8 + ((((int)((uVar11 - param_1[0x4ac]) + 7) >> 3) + -8) - param_1[0x4aa]),
              (int *)(param_1 + 0x4aa),aiStack_38);
  (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x4aa);
  (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_38);
  zz_028215c_(param_2);
  return;
}



// ==== 802805fc  zz_02805fc_ ====

undefined4 zz_02805fc_(uint *param_1,int *param_2,int *param_3,int *param_4)

{
  short sVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint *puVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  
  uVar7 = 0;
  uVar3 = param_1[2];
  uVar2 = *param_1;
  uVar4 = param_1[1];
  puVar6 = (uint *)param_1[3];
  uVar9 = uVar2 >> 0x15;
  iVar8 = param_2[1];
  if (0x15 < (int)uVar3) {
    uVar9 = uVar9 | uVar4 >> 0x35 - uVar3;
  }
  if (uVar9 >> 7 == 0) {
    sVar1 = *(short *)(DAT_8041cf8c + uVar9 * 2);
  }
  else {
    sVar1 = *(short *)(DAT_8041cf88 + (uVar9 >> 5 & 0x7fffffe));
  }
  iVar11 = (int)(char)sVar1;
  if (iVar11 == 0x7f) {
    uVar7 = 0xffffffff;
  }
  else {
    uVar9 = (uint)(int)sVar1 >> 8 & 0xff;
    uVar3 = uVar3 + uVar9;
    if ((int)uVar3 < 0x20) {
      uVar9 = uVar2 << uVar9;
    }
    else {
      uVar3 = uVar3 - 0x20;
      uVar9 = uVar4 << uVar3;
      uVar4 = *puVar6;
      puVar6 = puVar6 + 1;
    }
    uVar2 = uVar9;
    if (iVar11 == 0) {
      *param_3 = *param_4;
    }
    else {
      if (iVar8 != 0) {
        iVar10 = 0x20 - iVar8;
        if ((int)uVar3 < iVar10) {
          uVar3 = uVar3 + iVar8;
          uVar2 = uVar9 << iVar8;
        }
        else {
          uVar3 = uVar3 - iVar10;
          if (uVar3 != 0) {
            uVar9 = uVar9 | uVar4 >> iVar8 - uVar3;
            uVar4 = uVar4 << uVar3;
          }
          uVar5 = *puVar6;
          puVar6 = puVar6 + 1;
          uVar2 = uVar4;
          uVar4 = uVar5;
        }
        iVar11 = iVar11 << iVar8;
        iVar8 = (param_2[3] + -1) - (uVar9 >> iVar10);
        if (iVar11 < 1) {
          iVar11 = iVar11 + iVar8;
        }
        else {
          iVar11 = iVar11 - iVar8;
        }
      }
      *param_3 = (iVar11 + *param_4 << param_2[2]) >> (param_2[2] & 0x3fU);
      *param_4 = *param_3;
    }
    if (*param_2 != 0) {
      *param_3 = *param_3 << 1;
    }
  }
  *param_1 = uVar2;
  param_1[1] = uVar4;
  param_1[2] = uVar3;
  param_1[3] = (uint)puVar6;
  return uVar7;
}



// ==== 80280798  zz_0280798_ ====

void zz_0280798_(int param_1)

{
  *(undefined4 *)(param_1 + 0x2ec) = 0x400;
  *(undefined4 *)(param_1 + 0x2f4) = 0x400;
  *(undefined4 *)(param_1 + 0x2f0) = 0x400;
  return;
}



// ==== 802807ac  cPlayer::ClearSwapControllerTimer(void) ====

void cPlayer__ClearSwapControllerTimer_void_(int param_1)

{
  *(undefined4 *)(param_1 + 0x10) = 0;
  *(undefined4 *)(param_1 + 0x14) = 0;
  *(undefined4 *)(param_1 + 0x18) = 0;
  *(undefined4 *)(param_1 + 0x1c) = 0;
  return;
}



// ==== 802807c4  FUN_802807c4 ====

void FUN_802807c4(uint *param_1,int *param_2)

{
  short sVar1;
  bool bVar2;
  int *piVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  uint *puVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int aiStack_38 [2];
  int aiStack_30 [5];
  
  bVar2 = true;
  (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x4aa);
  piVar3 = (int *)(param_1[0x4aa] & 0xfffffffc);
  iVar7 = (param_1[0x4aa] - (int)piVar3) * 8;
  uVar9 = piVar3[1];
  puVar8 = (uint *)(piVar3 + 2);
  uVar11 = iVar7 + param_1[0x4ac];
  if ((int)uVar11 < 0x20) {
    uVar10 = (*piVar3 << iVar7) << param_1[0x4ac];
  }
  else {
    uVar11 = uVar11 - 0x20;
    uVar10 = uVar9 << uVar11;
    uVar9 = *puVar8;
    puVar8 = (uint *)(piVar3 + 3);
  }
  while( true ) {
    uVar4 = uVar10 >> 9;
    if (9 < (int)uVar11) {
      uVar4 = uVar4 | uVar9 >> 0x29 - uVar11;
    }
    if (uVar4 == 0) break;
    uVar4 = param_1[0xb7];
    while( true ) {
      do {
        uVar6 = uVar10 >> 0x15;
        if (0x15 < (int)uVar11) {
          uVar6 = uVar6 | uVar9 >> 0x35 - uVar11;
        }
        if (uVar6 >> 7 == 0) {
          sVar1 = *(short *)(DAT_8041cfa4 + uVar6 * 2);
        }
        else {
          sVar1 = *(short *)(DAT_8041cfa0 + (uVar6 >> 5 & 0x7fffffe));
        }
        uVar6 = (uint)sVar1;
        uVar11 = uVar11 + (uVar6 & 0xf);
        if ((int)uVar11 < 0x20) {
          uVar10 = uVar10 << (uVar6 & 0xf);
        }
        else {
          uVar11 = uVar11 - 0x20;
          uVar10 = uVar9 << uVar11;
          uVar9 = *puVar8;
          puVar8 = puVar8 + 1;
        }
        iVar7 = (int)(uVar6 >> 2 & 0xff) >> 2;
      } while (iVar7 == 0x22);
      if (iVar7 != 0x23) break;
      param_1[0xb7] = param_1[0xb7] + 0x21;
    }
    if (iVar7 == 0x24) {
      uVar4 = 0xfffffffe;
    }
    else {
      param_1[0xb7] = param_1[0xb7] + iVar7;
      param_1[0xb9] = uVar6 >> 10;
      if ((int)param_1[0xb8] < (int)param_1[0xb7]) {
        uVar4 = 0xfffffffe;
      }
      else {
        uVar4 = param_1[0xb7] - uVar4;
      }
    }
    if (uVar4 == 0xfffffffe) break;
    if ((!bVar2) && (1 < uVar4)) {
      (*(code *)param_1[0x9b])(param_1);
      param_1[0xa9] = 0;
      param_1[0xaa] = 0;
      param_1[0xab] = 0;
      param_1[0xac] = 0;
      param_1[0xbb] = 0x400;
      param_1[0xbd] = 0x400;
      param_1[0xbc] = 0x400;
    }
    if ((param_1[0xb9] & 0x20) == 0) {
      uVar4 = uVar10 >> 0x1b;
      if (0x1b < (int)uVar11) {
        uVar4 = uVar4 | uVar9 >> 0x3b - uVar11;
      }
      uVar6 = (uint)*(short *)(DAT_8041cf94 + uVar4 * 2);
      uVar4 = uVar6 & 0xff;
      uVar11 = uVar11 + uVar4;
      param_1[0xb9] = uVar6 >> 8;
      if ((int)uVar11 < 0x20) {
        uVar10 = uVar10 << uVar4;
      }
      else {
        uVar11 = uVar11 - 0x20;
        uVar10 = uVar9 << uVar11;
        uVar9 = *puVar8;
        puVar8 = puVar8 + 1;
      }
    }
    uVar4 = uVar10;
    if ((param_1[0xb9] & 0x10) != 0) {
      if ((int)uVar11 < 0x1b) {
        uVar4 = uVar10 << 5;
        uVar11 = uVar11 + 5;
      }
      else {
        uVar11 = uVar11 - 0x1b;
        uVar4 = uVar9;
        if (uVar11 != 0) {
          uVar10 = uVar10 | uVar9 >> 5 - uVar11;
          uVar4 = uVar9 << uVar11;
        }
        uVar9 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      param_1[0xa4] = uVar10 >> 0x1b;
    }
    if ((param_1[0xb9] & 8) == 0) {
      param_1[0xa9] = 0;
      param_1[0xaa] = 0;
      param_1[0xab] = 0;
      param_1[0xac] = 0;
    }
    else {
      *param_1 = uVar4;
      param_1[1] = uVar9;
      param_1[2] = uVar11;
      param_1[3] = (uint)puVar8;
      iVar7 = zz_02805fc_(param_1,(int *)(param_1 + 0xa5),(int *)(param_1 + 0xab),
                          (int *)(param_1 + 0xa9));
      iVar5 = zz_02805fc_(param_1,(int *)(param_1 + 0xa5),(int *)(param_1 + 0xac),
                          (int *)(param_1 + 0xaa));
      uVar4 = *param_1;
      uVar9 = param_1[1];
      uVar11 = param_1[2];
      puVar8 = (uint *)param_1[3];
      if (iVar7 != 0 || iVar5 != 0) break;
    }
    if ((param_1[0xb9] & 2) == 0) {
      param_1[0xba] = 0;
    }
    else {
      uVar10 = uVar4 >> 0x17;
      if (0x17 < (int)uVar11) {
        uVar10 = uVar10 | uVar9 >> 0x37 - uVar11;
      }
      uVar6 = (uint)*(short *)(DAT_8041cf84 + uVar10 * 2);
      uVar10 = uVar6 & 0xff;
      uVar11 = uVar11 + uVar10;
      param_1[0xba] = (uVar6 & 0xfff0) << 0x10;
      if ((int)uVar11 < 0x20) {
        uVar4 = uVar4 << uVar10;
      }
      else {
        uVar11 = uVar11 - 0x20;
        uVar4 = uVar9 << uVar11;
        uVar9 = *puVar8;
        puVar8 = puVar8 + 1;
      }
    }
    *param_1 = uVar4;
    param_1[1] = uVar9;
    param_1[2] = uVar11;
    param_1[3] = (uint)puVar8;
    if ((param_1[0xb9] & 1) == 0) {
      if (param_1[0xba] != 0) {
        (*(code *)param_1[0x9d])(param_1);
      }
      (*(code *)param_1[0xa1])(param_1);
      param_1[0xbb] = 0x400;
      param_1[0xbd] = 0x400;
      param_1[0xbc] = 0x400;
    }
    else {
      (*(code *)param_1[0x9c])(param_1);
      (*(code *)param_1[0x9e])(param_1);
    }
    uVar9 = param_1[0x4b5];
    param_1[0x4b5] = uVar9 - 1;
    if ((int)(uVar9 - 1) < 1) {
      param_1[0x4b5] = param_1[0x61];
      (*(code *)param_1[0x62])(param_1[99]);
    }
    uVar11 = param_1[2];
    puVar8 = (uint *)param_1[3];
    uVar4 = uVar11 & 7;
    uVar10 = *param_1;
    uVar9 = param_1[1];
    iVar7 = (int)puVar8 + ((((int)((uVar11 - uVar4) + 7) >> 3) + -8) - param_1[0x4aa]);
    if ((int)(param_1[0x4ab] - iVar7) < 0x801) {
      zz_02779cc_((int *)(param_1 + 0x4aa),iVar7,(int *)(param_1 + 0x4aa),aiStack_30);
      (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x4aa);
      (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_30);
      (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x4aa);
      piVar3 = (int *)(param_1[0x4aa] & 0xfffffffc);
      iVar7 = (param_1[0x4aa] - (int)piVar3) * 8;
      uVar9 = piVar3[1];
      puVar8 = (uint *)(piVar3 + 2);
      uVar11 = iVar7 + uVar4;
      if ((int)uVar11 < 0x20) {
        uVar10 = (*piVar3 << iVar7) << uVar4;
      }
      else {
        uVar11 = uVar11 - 0x20;
        uVar10 = uVar9 << uVar11;
        uVar9 = *puVar8;
        puVar8 = (uint *)(piVar3 + 3);
      }
    }
    bVar2 = false;
  }
  param_1[0x4ac] = uVar11 & 7;
  zz_02779cc_((int *)(param_1 + 0x4aa),
              (int)puVar8 + ((((int)((uVar11 - param_1[0x4ac]) + 7) >> 3) + -8) - param_1[0x4aa]),
              (int *)(param_1 + 0x4aa),aiStack_38);
  (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x4aa);
  (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_38);
  zz_028215c_(param_2);
  return;
}



// ==== 80280d70  FUN_80280d70 ====

void FUN_80280d70(uint *param_1,int *param_2)

{
  short sVar1;
  int *piVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  uint *puVar7;
  uint uVar8;
  int iVar9;
  int aiStack_28 [2];
  int aiStack_20 [5];
  
  (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x4aa);
  piVar2 = (int *)(param_1[0x4aa] & 0xfffffffc);
  iVar9 = (param_1[0x4aa] - (int)piVar2) * 8;
  uVar5 = piVar2[1];
  puVar7 = (uint *)(piVar2 + 2);
  uVar6 = iVar9 + param_1[0x4ac];
  if ((int)uVar6 < 0x20) {
    uVar3 = (*piVar2 << iVar9) << param_1[0x4ac];
  }
  else {
    uVar6 = uVar6 - 0x20;
    uVar3 = uVar5 << uVar6;
    uVar5 = *puVar7;
    puVar7 = (uint *)(piVar2 + 3);
  }
  while( true ) {
    uVar4 = uVar3 >> 9;
    if (9 < (int)uVar6) {
      uVar4 = uVar4 | uVar5 >> 0x29 - uVar6;
    }
    if (uVar4 == 0) break;
    uVar4 = param_1[0xb7];
    while( true ) {
      do {
        uVar8 = uVar3 >> 0x14;
        if (0x14 < (int)uVar6) {
          uVar8 = uVar8 | uVar5 >> 0x34 - uVar6;
        }
        if (uVar8 >> 8 == 0) {
          sVar1 = *(short *)(DAT_8041cfac + uVar8 * 2);
        }
        else {
          sVar1 = *(short *)(DAT_8041cfa8 + (uVar8 >> 5 & 0x7fffffe));
        }
        uVar8 = (uint)sVar1;
        uVar6 = uVar6 + (uVar8 & 0xf);
        if ((int)uVar6 < 0x20) {
          uVar3 = uVar3 << (uVar8 & 0xf);
        }
        else {
          uVar6 = uVar6 - 0x20;
          uVar3 = uVar5 << uVar6;
          uVar5 = *puVar7;
          puVar7 = puVar7 + 1;
        }
        iVar9 = (int)(uVar8 >> 2 & 0xff) >> 2;
      } while (iVar9 == 0x22);
      if (iVar9 != 0x23) break;
      param_1[0xb7] = param_1[0xb7] + 0x21;
    }
    if (iVar9 == 0x24) {
      iVar9 = -2;
    }
    else {
      param_1[0xb7] = param_1[0xb7] + iVar9;
      param_1[0xb9] = uVar8 >> 10;
      if ((int)param_1[0xb8] < (int)param_1[0xb7]) {
        iVar9 = -2;
      }
      else {
        iVar9 = param_1[0xb7] - uVar4;
      }
    }
    if (iVar9 == -2) break;
    uVar4 = uVar3;
    if ((param_1[0xb9] & 0x10) != 0) {
      if ((int)uVar6 < 0x1b) {
        uVar4 = uVar3 << 5;
        uVar6 = uVar6 + 5;
      }
      else {
        uVar6 = uVar6 - 0x1b;
        if (uVar6 != 0) {
          uVar3 = uVar3 | uVar5 >> 5 - uVar6;
          uVar5 = uVar5 << uVar6;
        }
        uVar8 = *puVar7;
        puVar7 = puVar7 + 1;
        uVar4 = uVar5;
        uVar5 = uVar8;
      }
      param_1[0xa4] = uVar3 >> 0x1b;
    }
    *param_1 = uVar4;
    param_1[1] = uVar5;
    param_1[2] = uVar6;
    param_1[3] = (uint)puVar7;
    (*(code *)param_1[0x9c])(param_1);
    (*(code *)param_1[0x9e])(param_1);
    uVar5 = param_1[0x4b5];
    param_1[0x4b5] = uVar5 - 1;
    if ((int)(uVar5 - 1) < 1) {
      param_1[0x4b5] = param_1[0x61];
      (*(code *)param_1[0x62])(param_1[99]);
    }
    uVar6 = param_1[2];
    puVar7 = (uint *)param_1[3];
    uVar4 = uVar6 & 7;
    uVar3 = *param_1;
    uVar5 = param_1[1];
    iVar9 = (int)puVar7 + ((((int)((uVar6 - uVar4) + 7) >> 3) + -8) - param_1[0x4aa]);
    if ((int)(param_1[0x4ab] - iVar9) < 0x801) {
      zz_02779cc_((int *)(param_1 + 0x4aa),iVar9,(int *)(param_1 + 0x4aa),aiStack_20);
      (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x4aa);
      (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_20);
      (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x4aa);
      piVar2 = (int *)(param_1[0x4aa] & 0xfffffffc);
      iVar9 = (param_1[0x4aa] - (int)piVar2) * 8;
      uVar5 = piVar2[1];
      puVar7 = (uint *)(piVar2 + 2);
      uVar6 = iVar9 + uVar4;
      if ((int)uVar6 < 0x20) {
        uVar3 = (*piVar2 << iVar9) << uVar4;
      }
      else {
        uVar6 = uVar6 - 0x20;
        uVar3 = uVar5 << uVar6;
        uVar5 = *puVar7;
        puVar7 = (uint *)(piVar2 + 3);
      }
    }
  }
  param_1[0x4ac] = uVar6 & 7;
  zz_02779cc_((int *)(param_1 + 0x4aa),
              (int)puVar7 + ((((int)((uVar6 - param_1[0x4ac]) + 7) >> 3) + -8) - param_1[0x4aa]),
              (int *)(param_1 + 0x4aa),aiStack_28);
  (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x4aa);
  (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_28);
  zz_028215c_(param_2);
  return;
}



// ==== 80281140  zz_0281140_ ====

/* WARNING: Removing unreachable block (ram,0x8028118c) */

char * zz_0281140_(char *param_1,int param_2,uint param_3)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  char *pcVar4;
  
  uVar2 = 0;
  pcVar3 = param_1;
  while( true ) {
    do {
      while( true ) {
        while( true ) {
          pcVar4 = pcVar3;
          if (param_1 + param_2 <= pcVar4) {
            return (char *)0x0;
          }
          cVar1 = *pcVar4;
          pcVar3 = pcVar4 + 1;
          if (uVar2 != 2) break;
          if (cVar1 == '\x01') {
            uVar2 = 3;
          }
          else if (cVar1 != '\0') {
            uVar2 = 0;
          }
        }
        if (1 < uVar2) break;
        if (uVar2 == 0) {
          if (cVar1 == '\0') {
            uVar2 = 1;
          }
        }
        else if (cVar1 == '\0') {
          uVar2 = 2;
        }
        else {
          uVar2 = 0;
        }
      }
    } while (3 < uVar2);
    uVar2 = zz_028132c_((int *)(pcVar4 + -3));
    if ((param_3 & uVar2) != 0) break;
    uVar2 = 0;
  }
  return pcVar4 + -3;
}



// ==== 8028122c  zz_028122c_ ====

/* WARNING: Removing unreachable block (ram,0x80281274) */

int * zz_028122c_(int *param_1,int param_2,uint param_3)

{
  char cVar1;
  uint uVar2;
  int *piVar3;
  
  piVar3 = (int *)((int)param_1 - param_2);
  uVar2 = 0;
  while( true ) {
    while( true ) {
      do {
        while( true ) {
          while( true ) {
            if (param_1 <= piVar3) {
              return (int *)0x0;
            }
            param_1 = (int *)((int)param_1 + -1);
            cVar1 = *(char *)param_1;
            if (uVar2 != 2) break;
            if (cVar1 == '\0') {
              uVar2 = 3;
            }
            else if (cVar1 != '\x01') {
              uVar2 = 1;
            }
          }
          if (1 < uVar2) break;
          if (uVar2 == 0) {
            uVar2 = 1;
          }
          else if (cVar1 == '\x01') {
            uVar2 = 2;
          }
        }
      } while (3 < uVar2);
      if (cVar1 == '\0') break;
      if (cVar1 == '\x01') {
        uVar2 = 2;
      }
      else {
        uVar2 = 1;
      }
    }
    uVar2 = zz_028132c_(param_1);
    if ((param_3 & uVar2) != 0) break;
    uVar2 = 0;
  }
  return param_1;
}



// ==== 8028132c  zz_028132c_ ====

undefined4 zz_028132c_(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  if (iVar1 == 0x100) {
    return 4;
  }
  if (iVar1 == 0x101) {
    return 3;
  }
  if ((0x101 < iVar1) && (iVar1 < 0x1b0)) {
    return 1;
  }
  if (iVar1 == 0x1b2) {
    return 0x20;
  }
  if (iVar1 == 0x1b3) {
    return 0x40;
  }
  if (iVar1 == 0x1b5) {
    return 0x10;
  }
  if (iVar1 == 0x1b7) {
    return 0x80;
  }
  if (iVar1 == 0x1b8) {
    return 8;
  }
  return 0;
}



// ==== 802813dc  zz_0281554_ ====

int zz_0281554_(uint param_1,uint param_2,int param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint *puVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  
  piVar1 = (int *)(param_1 & 0xfffffffc);
  iVar2 = (param_1 - (int)piVar1) * 8;
  uVar9 = piVar1[1];
  uVar6 = *piVar1 << iVar2;
  if (iVar2 != 0) {
    uVar6 = uVar6 | uVar9 >> (param_1 - (int)piVar1) * -8 + 0x20;
    uVar9 = uVar9 << iVar2;
  }
  uVar7 = piVar1[2];
  puVar5 = (uint *)(piVar1 + 3);
  if (uVar6 != 0x101) {
    return 0;
  }
  if (iVar2 < 0x1b) {
    uVar9 = uVar9 << 5;
    iVar2 = iVar2 + 5;
  }
  else {
    iVar2 = iVar2 + -0x1b;
    if (iVar2 != 0) {
      uVar7 = uVar7 << iVar2;
    }
    uVar6 = *puVar5;
    puVar5 = (uint *)(piVar1 + 4);
    uVar9 = uVar7;
    uVar7 = uVar6;
  }
  if (iVar2 == 0x1f) {
    uVar8 = *puVar5;
    iVar2 = 0;
    puVar5 = puVar5 + 1;
    uVar6 = uVar7;
    uVar7 = uVar8;
  }
  else {
    uVar6 = uVar9 << 1;
    iVar2 = iVar2 + 1;
  }
  if ((int)uVar9 < 0) {
    return 0;
  }
  if (iVar2 == 0x1f) {
    uVar8 = *puVar5;
    iVar2 = 0;
    puVar5 = puVar5 + 1;
    uVar9 = uVar7;
    uVar7 = uVar8;
  }
  else {
    uVar9 = uVar6 << 1;
    iVar2 = iVar2 + 1;
  }
  if (-1 < (int)uVar6) {
    return 0;
  }
  uVar6 = uVar9 >> 0x1a;
  if (0x1a < iVar2) {
    uVar6 = uVar6 | uVar7 >> 0x3a - iVar2;
  }
  if ((int)uVar6 < 0x16) {
    if (uVar6 != 0xb) {
      return 0;
    }
    iVar3 = iVar2 + 6;
    if (iVar3 < 0x20) {
      uVar9 = uVar9 << 6;
    }
    else {
      iVar3 = iVar2 + -0x1a;
      uVar9 = uVar7 << iVar3;
      uVar7 = *puVar5;
      puVar5 = puVar5 + 1;
    }
  }
  else {
    if (0x17 < (int)uVar6) {
      return 0;
    }
    iVar3 = iVar2 + 5;
    if (iVar3 < 0x20) {
      uVar9 = uVar9 << 5;
    }
    else {
      iVar3 = iVar2 + -0x1b;
      uVar9 = uVar7 << iVar3;
      uVar7 = *puVar5;
      puVar5 = puVar5 + 1;
    }
  }
  iVar2 = param_3 + -1;
  do {
    uVar6 = uVar9 >> 0x15;
    if (0x15 < iVar3) {
      uVar6 = uVar6 | uVar7 >> 0x35 - iVar3;
    }
    iVar4 = iVar3;
    if (uVar6 != 8) break;
    iVar4 = iVar3 + 0xb;
    if (iVar4 < 0x20) {
      uVar9 = uVar9 << 0xb;
    }
    else {
      iVar4 = iVar3 + -0x15;
      uVar9 = uVar7 << iVar4;
      uVar7 = *puVar5;
      puVar5 = puVar5 + 1;
    }
    iVar2 = iVar2 + -0x21;
    iVar3 = iVar4;
  } while (0x21 < iVar2);
  if ((iVar2 < 1) || (0x21 < iVar2)) {
    return 0;
  }
  uVar6 = (int)*(short *)(&DAT_803ae2d8 + iVar2 * 2) & 0xff;
  iVar3 = 0x20 - uVar6;
  if (iVar4 < iVar3) {
    iVar4 = iVar4 + uVar6;
    uVar6 = uVar9 << uVar6;
  }
  else {
    iVar4 = iVar4 - iVar3;
    if (iVar4 != 0) {
      uVar9 = uVar9 | uVar7 >> uVar6 - iVar4;
      uVar7 = uVar7 << iVar4;
    }
    uVar8 = *puVar5;
    puVar5 = puVar5 + 1;
    uVar6 = uVar7;
    uVar7 = uVar8;
  }
  if (uVar9 >> iVar3 != (uint)(int)*(short *)(&DAT_803ae2d8 + iVar2 * 2) >> 8) {
    return 0;
  }
  uVar6 = uVar6 >> 0x1a;
  if (0x1a < iVar4) {
    uVar6 = uVar6 | uVar7 >> 0x3a - iVar4;
  }
  if ((int)uVar6 < 0x16) {
    if (uVar6 == 0xb) {
      iVar2 = iVar4 + 6;
      if (0x1f < iVar2) {
        iVar2 = iVar4 + -0x1a;
        puVar5 = puVar5 + 1;
      }
LAB_802816a0:
      uVar9 = (int)puVar5 + (((iVar2 + 7 >> 3) + -8) - param_1);
      return ((int)param_2 >> 0x1f) + ((uint)(uVar9 <= param_2) - ((int)uVar9 >> 0x1f));
    }
  }
  else if ((int)uVar6 < 0x18) {
    iVar2 = iVar4 + 5;
    if (0x1f < iVar2) {
      iVar2 = iVar4 + -0x1b;
      puVar5 = puVar5 + 1;
    }
    goto LAB_802816a0;
  }
  return 0;
}



// ==== 802816c8  zz_02816c8_ ====

int zz_02816c8_(int param_1,int param_2)

{
  if (param_1 == 0) {
    DAT_8041b4d0 = param_2;
    if ((param_2 != 0) && (DAT_8041b4c8 != (code *)0x0)) {
      (*DAT_8041b4c8)(DAT_8041b4cc);
    }
  }
  else {
    *(int *)(param_1 + 0x200) = param_2;
    if ((param_2 != 0) && (*(code **)(param_1 + 0x1f8) != (code *)0x0)) {
      (**(code **)(param_1 + 0x1f8))(*(undefined4 *)(param_1 + 0x1fc));
    }
  }
  return param_2;
}



// ==== 80281750  zz_0281750_ ====

undefined4 zz_0281750_(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = zz_0283ac0_(param_1);
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0x1f8) = param_2;
    uVar2 = 0;
    *(undefined4 *)(param_1 + 0x1fc) = param_3;
  }
  else {
    DAT_8041b4d0 = 0xff030203;
    if (DAT_8041b4c8 != (code *)0x0) {
      (*DAT_8041b4c8)(DAT_8041b4cc);
    }
    uVar2 = 0xff030203;
  }
  return uVar2;
}



// ==== 802817dc  zz_02817dc_ ====

void zz_02817dc_(undefined4 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  param_1[3] = 0;
  param_1[4] = 0;
  return;
}



// ==== 802817f8  zz_02817f8_ ====

void zz_02817f8_(void)

{
  DAT_8041b4c8 = 0;
  DAT_8041b4cc = 0;
  DAT_8041b4d0 = 0;
  DAT_8041b4d4 = 0;
  DAT_8041b4d8 = 0;
  return;
}



// ==== 80281818  zz_0281818_ ====

void zz_0281818_(int param_1,int *param_2)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  
  iVar1 = zz_0283ac0_(param_1);
  if (iVar1 == 0) {
    iVar1 = -0xfcfcfb;
    do {
      uVar2 = zz_028215c_(param_2);
      if (uVar2 == 0) break;
      if ((uVar2 & 0xcc) != 0) {
        iVar1 = 0;
        break;
      }
      iVar3 = zz_0281e60_(param_2,1);
    } while (iVar3 == 4);
    zz_02816c8_(param_1,iVar1);
  }
  else {
    zz_02816c8_(0,-0xfcfdf6);
  }
  return;
}



// ==== 802818c0  zz_02818c0_ ====

int zz_02818c0_(int param_1,int *param_2,undefined4 *param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined1 auStack_38 [36];
  
  iVar3 = zz_0283ac0_(param_1);
  if (iVar3 == 0) {
    zz_02a96dc_((int)auStack_38);
    zz_0289414_();
    zz_027c488_();
    if (*(int *)(param_1 + 0x12b4) == 2) {
      iVar3 = zz_0296fe8_();
    }
    else {
      iVar7 = *(int *)(param_1 + 0x204);
      iVar6 = *(int *)(param_1 + 0x208);
      uVar2 = param_3[1];
      *(undefined4 *)(param_1 + 0x20c) = *param_3;
      *(undefined4 *)(param_1 + 0x210) = uVar2;
      uVar2 = param_3[3];
      *(undefined4 *)(param_1 + 0x214) = param_3[2];
      *(undefined4 *)(param_1 + 0x218) = uVar2;
      uVar2 = param_3[5];
      *(undefined4 *)(param_1 + 0x21c) = param_3[4];
      *(undefined4 *)(param_1 + 0x220) = uVar2;
      uVar2 = param_3[7];
      *(undefined4 *)(param_1 + 0x224) = param_3[6];
      *(undefined4 *)(param_1 + 0x228) = uVar2;
      uVar2 = param_3[9];
      *(undefined4 *)(param_1 + 0x22c) = param_3[8];
      *(undefined4 *)(param_1 + 0x230) = uVar2;
      uVar2 = param_3[0xb];
      *(undefined4 *)(param_1 + 0x234) = param_3[10];
      *(undefined4 *)(param_1 + 0x238) = uVar2;
      zz_028943c_(param_1);
      zz_027fb7c_(param_1);
      zz_027fb5c_(param_1);
      iVar3 = zz_0281ecc_(param_1,param_2);
      puVar4 = (undefined4 *)(param_1 + 0x1a4);
      puVar5 = (undefined4 *)(param_3[9] + -4);
      iVar8 = 10;
      do {
        puVar1 = puVar4 + 1;
        puVar4 = puVar4 + 2;
        uVar2 = *puVar4;
        puVar5[1] = *puVar1;
        puVar5 = puVar5 + 2;
        *puVar5 = uVar2;
        iVar8 = iVar8 + -1;
      } while (iVar8 != 0);
      param_3[10] = *(int *)(param_1 + 0x204) - iVar7;
      param_3[0xb] = *(int *)(param_1 + 0x208) - iVar6;
      zz_02a96a8_((int)auStack_38);
    }
  }
  else {
    iVar3 = zz_02816c8_(0,-0xfcfdf7);
  }
  return iVar3;
}



// ==== 80281a1c  zz_0281a1c_ ====

void zz_0281a1c_(void)

{
  return;
}



// ==== 80281a20  zz_0281a20_ ====

int zz_0281a20_(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  int iVar1;
  
  iVar1 = zz_0283ac0_(param_1);
  if (iVar1 == 0) {
    iVar1 = 0;
    *param_2 = *(undefined4 *)(param_1 + 0x25c);
    *param_3 = *(undefined4 *)(param_1 + 0x260);
  }
  else {
    iVar1 = zz_02816c8_(0,-0xfcfdf2);
  }
  return iVar1;
}



// ==== 80281a94  zz_0281a94_ ====

int zz_0281a94_(int param_1,int *param_2,undefined4 *param_3,int *param_4)

{
  int iVar1;
  
  iVar1 = zz_0283ac0_(param_1);
  if (iVar1 == 0) {
    *param_2 = *(int *)(param_1 + 0x254) << 0xb;
    *param_3 = *(undefined4 *)(param_1 + 0x264);
    if (*(int *)(param_1 + 0x250) == 0x3ffff) {
      *param_4 = -1;
    }
    else {
      iVar1 = *(int *)(param_1 + 0x264) * *(int *)(param_1 + 0x250);
      iVar1 = iVar1 / 0x708 + (iVar1 >> 0x1f);
      *param_4 = iVar1 - (iVar1 >> 0x1f);
    }
    iVar1 = 0;
  }
  else {
    iVar1 = zz_02816c8_(0,-0xfcfdf1);
  }
  return iVar1;
}



// ==== 80281b5c  zz_0281b5c_ ====

int zz_0281b5c_(int param_1,undefined4 *param_2)

{
  int iVar1;
  
  iVar1 = zz_0283ac0_(param_1);
  if (iVar1 == 0) {
    iVar1 = 0;
    *param_2 = *(undefined4 *)(param_1 + 0x250);
  }
  else {
    iVar1 = zz_02816c8_(0,-0xfcfdf3);
  }
  return iVar1;
}



// ==== 80281bbc  zz_0281bbc_ ====

int zz_0281bbc_(int param_1,int param_2)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  
  iVar3 = zz_0283ac0_(param_1);
  if (iVar3 == 0) {
    puVar5 = (undefined4 *)(param_2 + -4);
    puVar4 = (undefined4 *)(param_1 + 0x1a4);
    iVar3 = 10;
    do {
      puVar1 = puVar4 + 1;
      puVar4 = puVar4 + 2;
      uVar2 = *puVar4;
      puVar5[1] = *puVar1;
      puVar5 = puVar5 + 2;
      *puVar5 = uVar2;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
    iVar3 = 0;
  }
  else {
    iVar3 = zz_02816c8_(0,-0xfcfdf4);
  }
  return iVar3;
}



// ==== 80281c38  zz_0281c38_ ====

void zz_0281c38_(int param_1,int *param_2)

{
  int *piVar1;
  uint uVar2;
  uint uVar3;
  uint *puVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int aiStack_28 [4];
  
  (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x12a8);
  piVar1 = (int *)(*(uint *)(param_1 + 0x12a8) & 0xfffffffc);
  iVar6 = (*(uint *)(param_1 + 0x12a8) - (int)piVar1) * 8;
  uVar3 = piVar1[1];
  puVar4 = (uint *)(piVar1 + 2);
  uVar2 = *piVar1 << iVar6;
  if (0x1f < iVar6) {
    iVar6 = iVar6 + -0x20;
    uVar2 = uVar3 << iVar6;
    uVar3 = *puVar4;
    puVar4 = (uint *)(piVar1 + 3);
  }
  if (iVar6 != 0) {
    uVar2 = uVar2 | uVar3 >> 0x20 - iVar6;
    uVar3 = uVar3 << iVar6;
  }
  uVar8 = *puVar4;
  puVar5 = puVar4 + 1;
  *(uint *)(param_1 + 0x2dc) = ((uVar2 & 0xff) - 1) * *(int *)(param_1 + 0x1b0) + -1;
  if (iVar6 < 0x1b) {
    uVar2 = uVar3 << 5;
    *(uint *)(param_1 + 0x290) = uVar3 >> 0x1b;
    iVar6 = iVar6 + 5;
  }
  else {
    iVar6 = iVar6 + -0x1b;
    if (iVar6 == 0) {
      *(uint *)(param_1 + 0x290) = uVar3 >> 0x1b;
      uVar2 = uVar8;
    }
    else {
      *(uint *)(param_1 + 0x290) = (uVar3 | uVar8 >> 5 - iVar6) >> 0x1b;
      uVar2 = uVar8 << iVar6;
    }
    uVar8 = *puVar5;
    puVar5 = puVar4 + 2;
  }
  cPlayer__ClearSwapControllerTimer_void_(param_1 + 0x294);
  cPlayer__ClearSwapControllerTimer_void_(param_1 + 0x2b8);
  zz_0280798_(param_1);
  do {
    if (-1 < (int)uVar2) {
      uVar3 = iVar6 + 1;
      if (0x1f < (int)uVar3) {
        uVar3 = iVar6 - 0x1f;
        puVar5 = puVar5 + 1;
      }
      *(uint *)(param_1 + 0x12b0) = uVar3 & 7;
      zz_02779cc_((int *)(param_1 + 0x12a8),
                  (int)puVar5 +
                  ((((int)((uVar3 - *(int *)(param_1 + 0x12b0)) + 7) >> 3) + -8) -
                  *(int *)(param_1 + 0x12a8)),(int *)(param_1 + 0x12a8),aiStack_28);
      (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x12a8);
      (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_28);
      (**(code **)(param_1 + 0x268))(param_1,param_2);
      return;
    }
    iVar7 = iVar6 + 9;
    if (iVar7 < 0x20) {
      uVar2 = uVar2 << 9;
    }
    else {
      iVar7 = iVar6 + -0x17;
      uVar2 = uVar8 << iVar7;
      uVar8 = *puVar5;
      puVar5 = puVar5 + 1;
    }
    iVar6 = iVar7;
  } while ((int)puVar5 + (((iVar7 + 7 >> 3) + -8) - *(int *)(param_1 + 0x12a8)) <
           *(int *)(param_1 + 0x12ac));
  return;
}



// ==== 80281e60  zz_0281e60_ ====

undefined4 zz_0281e60_(int *param_1,undefined4 param_2)

{
  uint uVar1;
  undefined1 auStack_18 [4];
  undefined4 local_14;
  
  uVar1 = countLeadingZeros(param_2);
  (**(code **)(*param_1 + 0x18))();
  (**(code **)(*param_1 + 0x20))(param_1,uVar1 >> 5,auStack_18);
  return local_14;
}



// ==== 80281ecc  zz_0281ecc_ ====

int zz_0281ecc_(int param_1,int *param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  undefined1 auStack_48 [4];
  int local_44;
  char *local_40;
  int local_3c;
  int aiStack_38 [2];
  int *local_30;
  int local_2c;
  
  *(undefined4 *)(param_1 + 0x12d4) = *(undefined4 *)(param_1 + 0x184);
  do {
    if (*(int *)(param_1 + 0x12a0) == 0) {
LAB_80281f3c:
      if (*(int *)(param_1 + 0x16c) == 0) {
        iVar4 = -2;
      }
      else {
        iVar4 = -3;
      }
LAB_80281f54:
      do {
        (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,&local_40);
        if (local_3c < 4) {
          (**(code **)(*param_2 + 0x1c))(param_2,1,&local_40);
          iVar3 = 0;
        }
        else {
          piVar1 = (int *)zz_0281140_(local_40,local_3c,0xffffffff);
          if (piVar1 == (int *)0x0) {
            zz_02779cc_((int *)&local_40,local_3c + -3,(int *)&local_40,aiStack_38);
            (**(code **)(*param_2 + 0x20))(param_2,0,&local_40);
            (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_38);
            goto LAB_80281f54;
          }
          iVar3 = zz_028132c_(piVar1);
          zz_02779cc_((int *)&local_40,(int)piVar1 - (int)local_40,(int *)&local_40,aiStack_38);
          (**(code **)(*param_2 + 0x20))(param_2,0,&local_40);
          (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_38);
        }
        if (iVar3 == 0) break;
        if (iVar3 != 0) {
          iVar4 = 0;
          break;
        }
        (**(code **)(*param_2 + 0x18))(param_2,1,4,auStack_48);
        (**(code **)(*param_2 + 0x20))(param_2,0,auStack_48);
      } while (local_44 == 4);
    }
    else {
      *(undefined4 *)(param_1 + 0x12a0) = 0;
      *(int *)(param_1 + 0x12a4) = *(int *)(param_1 + 0x12a4) + 1;
      *(int *)(param_1 + 0x204) = *(int *)(param_1 + 0x204) + 1;
      if (*(int *)(param_1 + 0x16c) != 0) {
        *(int *)(param_1 + 0x208) = *(int *)(param_1 + 0x208) + 1;
        goto LAB_80281f3c;
      }
      iVar4 = -2;
    }
    if (iVar4 != 0) {
      iVar4 = zz_02816c8_(param_1,iVar4);
      return iVar4;
    }
    (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,&local_30);
    (**(code **)(*param_2 + 0x1c))(param_2,1,&local_30);
    if ((local_2c < 4) || (uVar2 = zz_028132c_(local_30), (uVar2 & 1) == 0)) {
      return 0;
    }
    zz_0281c38_(param_1,param_2);
  } while( true );
}



// ==== 8028215c  zz_028215c_ ====

undefined4 zz_028215c_(int *param_1)

{
  int *piVar1;
  undefined4 uVar2;
  int aiStack_28 [2];
  char *local_20;
  int local_1c;
  
  while( true ) {
    (**(code **)(*param_1 + 0x18))(param_1,1,0x7fffffff,&local_20);
    if (local_1c < 4) {
      (**(code **)(*param_1 + 0x1c))(param_1,1,&local_20);
      return 0;
    }
    piVar1 = (int *)zz_0281140_(local_20,local_1c,0xffffffff);
    if (piVar1 != (int *)0x0) break;
    zz_02779cc_((int *)&local_20,local_1c + -3,(int *)&local_20,aiStack_28);
    (**(code **)(*param_1 + 0x20))(param_1,0,&local_20);
    (**(code **)(*param_1 + 0x1c))(param_1,1,aiStack_28);
  }
  uVar2 = zz_028132c_(piVar1);
  zz_02779cc_((int *)&local_20,(int)piVar1 - (int)local_20,(int *)&local_20,aiStack_28);
  (**(code **)(*param_1 + 0x20))(param_1,0,&local_20);
  (**(code **)(*param_1 + 0x1c))(param_1,1,aiStack_28);
  return uVar2;
}



// ==== 802822b0  zz_02822b0_ ====

undefined4 zz_02822b0_(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *__s1;
  undefined4 uVar4;
  
  uVar4 = 0;
  for (iVar2 = 0; iVar2 < param_3 + -4; iVar2 = iVar2 + 1) {
    iVar3 = param_2 + iVar2;
    __s1 = (int *)(iVar3 + 4);
    iVar1 = gnt4_strncmp((char *)__s1,s_IDCPREC_802b88b4,7);
    if (iVar1 == 0) {
      iVar1 = atoi((char *)(iVar3 + 0x14));
      if (iVar1 == 0) {
        *(undefined4 *)(param_1 + 0x12c4) = 0;
      }
      else {
        *(undefined4 *)(param_1 + 0x12c4) = 3;
      }
    }
    iVar1 = gnt4_strncmp((char *)__s1,s_STCCODE_802b88bc,7);
    if (iVar1 == 0) {
      iVar1 = atoi((char *)(iVar3 + 0x14));
      *(int *)(param_1 + 0x12b8) = iVar1;
      iVar1 = atoi((char *)(iVar3 + 0x1c));
      *(int *)(param_1 + 0x12bc) = iVar1;
      iVar1 = atoi((char *)(iVar3 + 0x24));
      *(int *)(param_1 + 0x12c0) = iVar1;
    }
    iVar1 = zz_028132c_(__s1);
    if (iVar1 != 0) break;
  }
  if (*(int *)(param_1 + 0x12c4) == 0) {
    *(code **)(param_1 + 0x12c8) = FUN_8028d9f4;
    *(undefined4 *)(param_1 + 0x12d8) = DAT_8041cf80;
    *(undefined4 *)(param_1 + 0x12dc) = DAT_8041cf7c;
  }
  else {
    *(code **)(param_1 + 0x12c8) = FUN_80291c24;
    *(undefined4 *)(param_1 + 0x12d8) = DAT_8041cf78;
    *(undefined4 *)(param_1 + 0x12dc) = DAT_8041cf74;
  }
  if (*(int *)(param_1 + 0x12b8) == 8) {
    uVar4 = 0xffffffff;
  }
  else {
    if (*(int *)(param_1 + 0x12c4) == 0) {
      *(code **)(param_1 + 0x12c8) = FUN_8028d9f4;
    }
    else {
      *(code **)(param_1 + 0x12c8) = FUN_80291c24;
    }
    *(code **)(param_1 + 0x12cc) = zz_028955c_;
  }
  return uVar4;
}



// ==== 8028243c  zz_028243c_ ====

int zz_028243c_(int param_1,void *param_2,int param_3)

{
  int iVar1;
  code *pcVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  void *local_38;
  size_t local_34;
  void *local_30;
  size_t local_2c;
  
  iVar6 = 0;
  iVar7 = 0;
  iVar3 = 4;
  iVar5 = *(int *)(param_1 + 0x12e4);
  while ((iVar3 < param_3 + -3 && (iVar1 = zz_028132c_((int *)((int)param_2 + iVar3)), iVar1 == 0)))
  {
    iVar3 = iVar3 + 1;
  }
  if (iVar3 == param_3 + -3) {
    iVar7 = -1;
  }
  if (iVar5 == 1) {
    iVar6 = zz_02822b0_(param_1,(int)param_2,iVar3);
  }
  piVar4 = *(int **)(param_1 + iVar5 * 0xc + 0x12e8);
  if (piVar4 != (int *)0x0) {
    (**(code **)(*piVar4 + 0x18))(piVar4,0,iVar3,&local_30);
    gnt4_memcpy(local_30,param_2,local_2c);
    (**(code **)(*piVar4 + 0x20))(piVar4,1,&local_30);
    if ((int)local_2c < iVar3) {
      (**(code **)(*piVar4 + 0x18))(piVar4,0,iVar3 - local_2c,&local_38);
      gnt4_memcpy(local_38,(void *)((int)param_2 + local_2c),local_34);
      (**(code **)(*piVar4 + 0x20))(piVar4,1,&local_38);
    }
    iVar1 = param_1 + iVar5 * 0xc;
    pcVar2 = *(code **)(iVar1 + 0x12ec);
    if (pcVar2 != (code *)0x0) {
      (*pcVar2)(*(undefined4 *)(iVar1 + 0x12f0),iVar5);
    }
  }
  if ((iVar5 == 3) && (*(int *)(param_1 + 0x1318) != 0)) {
    iVar5 = *(int *)(param_1 + 0x131c);
    if (iVar3 < *(int *)(param_1 + 0x131c)) {
      iVar5 = iVar3;
    }
    *(int *)(param_1 + 0x1320) = iVar5;
    gnt4_memcpy(*(void **)(param_1 + 0x1318),param_2,*(size_t *)(param_1 + 0x1320));
  }
  if (iVar6 != 0) {
    iVar7 = iVar6;
  }
  return iVar7;
}



// ==== 802825f4  zz_02825f4_ ====

undefined4 zz_02825f4_(int param_1,int *param_2)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  uint *puVar6;
  uint *puVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int aiStack_28 [5];
  
  *(undefined4 *)(param_1 + 0x12e4) = 3;
  (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x12a8);
  uVar1 = *(uint *)(param_1 + 0x12a8) & 0xfffffffc;
  uVar2 = *(uint *)(uVar1 + 4);
  iVar4 = (*(uint *)(param_1 + 0x12a8) - uVar1) * 8;
  puVar6 = (uint *)(uVar1 + 8);
  if (0x1f < iVar4) {
    uVar2 = *puVar6;
    puVar6 = (uint *)(uVar1 + 0xc);
    iVar4 = iVar4 + -0x20;
  }
  if (iVar4 != 0) {
    uVar2 = uVar2 << iVar4;
  }
  uVar1 = *puVar6;
  puVar7 = puVar6 + 1;
  if (iVar4 < 0x16) {
    uVar3 = uVar2 << 10;
    *(uint *)(param_1 + 0x1bc) = uVar2 >> 0x16;
    iVar4 = iVar4 + 10;
  }
  else {
    iVar4 = iVar4 + -0x16;
    if (iVar4 == 0) {
      *(uint *)(param_1 + 0x1bc) = uVar2 >> 0x16;
      uVar3 = uVar1;
    }
    else {
      *(uint *)(param_1 + 0x1bc) = (uVar2 | uVar1 >> 10 - iVar4) >> 0x16;
      uVar3 = uVar1 << iVar4;
    }
    uVar1 = *puVar7;
    puVar7 = puVar6 + 2;
  }
  if (iVar4 < 0x1d) {
    uVar2 = uVar3 << 3;
    iVar4 = iVar4 + 3;
  }
  else {
    iVar4 = iVar4 + -0x1d;
    uVar2 = uVar1;
    if (iVar4 != 0) {
      uVar3 = uVar3 | uVar1 >> 3 - iVar4;
      uVar2 = uVar1 << iVar4;
    }
    uVar1 = *puVar7;
    puVar7 = puVar7 + 1;
  }
  *(uint *)(param_1 + 0x1c0) = uVar3 >> 0x1d;
  if (iVar4 < 0x10) {
    uVar3 = uVar2 << 0x10;
    *(uint *)(param_1 + 0x264) = uVar2 >> 0x10;
    iVar4 = iVar4 + 0x10;
  }
  else {
    iVar4 = iVar4 + -0x10;
    if (iVar4 == 0) {
      *(uint *)(param_1 + 0x264) = uVar2 >> 0x10;
      uVar3 = uVar1;
    }
    else {
      *(uint *)(param_1 + 0x264) = (uVar2 | uVar1 >> 0x10 - iVar4) >> 0x10;
      uVar3 = uVar1 << iVar4;
    }
    uVar1 = *puVar7;
    puVar7 = puVar7 + 1;
  }
  iVar10 = *(int *)(param_1 + 0x1c0);
  if ((iVar10 == 2) || (iVar10 == 3)) {
    *(uint *)(param_1 + 0x294) = uVar3 >> 0x1f;
    if (iVar4 == 0x1f) {
      uVar3 = *puVar7;
      iVar4 = 0;
      puVar7 = puVar7 + 1;
      uVar2 = uVar1;
    }
    else {
      uVar2 = uVar3 << 1;
      iVar4 = iVar4 + 1;
      uVar3 = uVar1;
    }
    uVar1 = uVar3;
    if (iVar4 < 0x1d) {
      uVar3 = uVar2 << 3;
      iVar4 = iVar4 + 3;
    }
    else {
      iVar4 = iVar4 + -0x1d;
      uVar3 = uVar1;
      if (iVar4 != 0) {
        uVar2 = uVar2 | uVar1 >> 3 - iVar4;
        uVar3 = uVar1 << iVar4;
      }
      uVar1 = *puVar7;
      puVar7 = puVar7 + 1;
    }
    iVar8 = (uVar2 >> 0x1d) - 1;
    *(int *)(param_1 + 0x298) = iVar8;
    *(int *)(param_1 + 0x29c) = 0x1b - iVar8;
    *(int *)(param_1 + 0x2a0) = 1 << iVar8;
  }
  if (iVar10 == 3) {
    *(uint *)(param_1 + 0x2b8) = uVar3 >> 0x1f;
    if (iVar4 == 0x1f) {
      uVar3 = *puVar7;
      iVar4 = 0;
      puVar7 = puVar7 + 1;
      uVar2 = uVar1;
    }
    else {
      uVar2 = uVar3 << 1;
      iVar4 = iVar4 + 1;
      uVar3 = uVar1;
    }
    uVar1 = uVar3;
    if (iVar4 < 0x1d) {
      uVar3 = uVar2 << 3;
      iVar4 = iVar4 + 3;
    }
    else {
      iVar4 = iVar4 + -0x1d;
      uVar3 = uVar1;
      if (iVar4 != 0) {
        uVar2 = uVar2 | uVar1 >> 3 - iVar4;
        uVar3 = uVar1 << iVar4;
      }
      uVar1 = *puVar7;
      puVar7 = puVar7 + 1;
    }
    iVar8 = (uVar2 >> 0x1d) - 1;
    *(int *)(param_1 + 700) = iVar8;
    *(int *)(param_1 + 0x2c0) = 0x1b - iVar8;
    *(int *)(param_1 + 0x2c4) = 1 << iVar8;
  }
  iVar10 = iVar10 * 4;
  iVar8 = ((int)(3U - *(int *)(param_1 + 0x180) | *(int *)(param_1 + 0x180) - 3U) >> 0x1f) * -0x14;
  *(undefined4 *)(param_1 + 0x268) = *(undefined4 *)(&DAT_802b87b0 + iVar10);
  iVar11 = iVar8 + iVar10;
  *(undefined4 *)(param_1 + 0x26c) = *(undefined4 *)(&DAT_802b87c4 + iVar11);
  *(code **)(param_1 + 0x270) = FUN_8027e48c;
  *(code **)(param_1 + 0x274) = FUN_8027e3e0;
  uVar9 = *(undefined4 *)(&DAT_802b8864 + iVar11);
  *(undefined4 *)(param_1 + 0x278) =
       *(undefined4 *)(&DAT_802b87ec + *(int *)(param_1 + 0x178) * 0x28 + iVar8 + iVar10);
  uVar5 = *(undefined4 *)(&DAT_802b883c + iVar11);
  *(undefined4 *)(param_1 + 0x280) = uVar9;
  uVar9 = *(undefined4 *)(&DAT_802b888c + iVar11);
  *(undefined4 *)(param_1 + 0x284) = uVar5;
  *(undefined4 *)(param_1 + 0x288) = uVar9;
  *(undefined4 *)(param_1 + 0x27c) = *(undefined4 *)(param_1 + 0x284);
  do {
    if (-1 < (int)uVar3) {
      uVar1 = iVar4 + 1;
      if (0x1f < (int)uVar1) {
        uVar1 = iVar4 - 0x1f;
        puVar7 = puVar7 + 1;
      }
      *(uint *)(param_1 + 0x12b0) = uVar1 & 7;
      zz_02779cc_((int *)(param_1 + 0x12a8),
                  (int)puVar7 +
                  ((((int)((uVar1 - *(int *)(param_1 + 0x12b0)) + 7) >> 3) + -8) -
                  *(int *)(param_1 + 0x12a8)),(int *)(param_1 + 0x12a8),aiStack_28);
      (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x12a8);
      (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_28);
      return 0;
    }
    iVar10 = iVar4 + 9;
    if (iVar10 < 0x20) {
      uVar3 = uVar3 << 9;
    }
    else {
      iVar10 = iVar4 + -0x17;
      uVar3 = uVar1 << iVar10;
      uVar1 = *puVar7;
      puVar7 = puVar7 + 1;
    }
    iVar4 = iVar10;
  } while ((int)puVar7 + (((iVar10 + 7 >> 3) + -8) - *(int *)(param_1 + 0x12a8)) <
           *(int *)(param_1 + 0x12ac));
  return 0xfffffffd;
}



// ==== 80282a44  zz_0282a44_ ====

undefined4 zz_0282a44_(int param_1,int *param_2)

{
  uint uVar1;
  uint *puVar2;
  uint *puVar3;
  uint uVar4;
  uint uVar5;
  int iVar6;
  int aiStack_18 [4];
  
  *(undefined4 *)(param_1 + 0x12e4) = 2;
  *(int *)(param_1 + 0x1d8) = *(int *)(param_1 + 0x1d8) + 1;
  (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x12a8);
  uVar4 = *(uint *)(param_1 + 0x12a8) & 0xfffffffc;
  uVar1 = *(uint *)(uVar4 + 4);
  iVar6 = (*(uint *)(param_1 + 0x12a8) - uVar4) * 8;
  puVar2 = (uint *)(uVar4 + 8);
  if (0x1f < iVar6) {
    uVar1 = *puVar2;
    puVar2 = (uint *)(uVar4 + 0xc);
    iVar6 = iVar6 + -0x20;
  }
  if (iVar6 != 0) {
    uVar1 = uVar1 << iVar6;
  }
  uVar4 = *puVar2;
  puVar3 = puVar2 + 1;
  if (iVar6 < 7) {
    uVar5 = uVar1 << 0x19;
    iVar6 = iVar6 + 0x19;
  }
  else {
    iVar6 = iVar6 + -7;
    uVar5 = uVar4;
    if (iVar6 != 0) {
      uVar1 = uVar1 | uVar4 >> 0x19 - iVar6;
      uVar5 = uVar4 << iVar6;
    }
    uVar4 = *puVar3;
    puVar3 = puVar2 + 2;
  }
  *(uint *)(param_1 + 0x1d4) = uVar1 >> 7 & 0x3f;
  *(uint *)(param_1 + 0x1d0) = uVar1 >> 0xd & 0x3f;
  *(uint *)(param_1 + 0x1cc) = uVar1 >> 0x14 & 0x3f;
  *(uint *)(param_1 + 0x1c8) = uVar1 >> 0x1a & 0x1f;
  *(uint *)(param_1 + 0x1c4) = uVar1 >> 0x1f;
  *(uint *)(param_1 + 0x25c) = uVar5 >> 0x1f;
  if (iVar6 == 0x1f) {
    iVar6 = 0;
    puVar3 = puVar3 + 1;
  }
  else {
    uVar4 = uVar5 << 1;
    iVar6 = iVar6 + 1;
  }
  *(uint *)(param_1 + 0x260) = uVar4 >> 0x1f;
  if (iVar6 == 0x1f) {
    uVar4 = 0;
    puVar3 = puVar3 + 1;
  }
  else {
    uVar4 = iVar6 + 1;
  }
  *(uint *)(param_1 + 0x12b0) = uVar4 & 7;
  zz_02779cc_((int *)(param_1 + 0x12a8),
              (int)puVar3 +
              ((((int)((uVar4 - *(int *)(param_1 + 0x12b0)) + 7) >> 3) + -8) -
              *(int *)(param_1 + 0x12a8)),(int *)(param_1 + 0x12a8),aiStack_18);
  (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x12a8);
  (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_18);
  return 0;
}



// ==== 80282c1c  zz_0282c1c_ ====

undefined4 zz_0282c1c_(int param_1,int *param_2)

{
  undefined1 uVar1;
  uint uVar2;
  char *pcVar3;
  char *pcVar4;
  char cVar5;
  uint *puVar6;
  uint *puVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int aiStack_28 [4];
  
  *(undefined4 *)(param_1 + 0x12e4) = 1;
  (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x12a8);
  uVar10 = *(uint *)(param_1 + 0x12a8) & 0xfffffffc;
  uVar2 = *(uint *)(uVar10 + 4);
  iVar8 = (*(uint *)(param_1 + 0x12a8) - uVar10) * 8;
  puVar6 = (uint *)(uVar10 + 8);
  if (0x1f < iVar8) {
    uVar2 = *puVar6;
    puVar6 = (uint *)(uVar10 + 0xc);
    iVar8 = iVar8 + -0x20;
  }
  if (iVar8 != 0) {
    uVar2 = uVar2 << iVar8;
  }
  uVar10 = *puVar6;
  puVar7 = puVar6 + 1;
  if (iVar8 < 0x14) {
    uVar11 = uVar2 << 0xc;
    *(uint *)(param_1 + 0x1a8) = uVar2 >> 0x14;
    iVar8 = iVar8 + 0xc;
  }
  else {
    iVar8 = iVar8 + -0x14;
    if (iVar8 == 0) {
      *(uint *)(param_1 + 0x1a8) = uVar2 >> 0x14;
    }
    else {
      *(uint *)(param_1 + 0x1a8) = (uVar2 | uVar10 >> 0xc - iVar8) >> 0x14;
      uVar10 = uVar10 << iVar8;
    }
    uVar2 = *puVar7;
    puVar7 = puVar6 + 2;
    uVar11 = uVar10;
    uVar10 = uVar2;
  }
  if (iVar8 < 0x14) {
    uVar2 = uVar11 << 0xc;
    *(uint *)(param_1 + 0x1ac) = uVar11 >> 0x14;
    iVar8 = iVar8 + 0xc;
  }
  else {
    iVar8 = iVar8 + -0x14;
    if (iVar8 == 0) {
      *(uint *)(param_1 + 0x1ac) = uVar11 >> 0x14;
    }
    else {
      *(uint *)(param_1 + 0x1ac) = (uVar11 | uVar10 >> 0xc - iVar8) >> 0x14;
      uVar10 = uVar10 << iVar8;
    }
    uVar11 = *puVar7;
    puVar7 = puVar7 + 1;
    uVar2 = uVar10;
    uVar10 = uVar11;
  }
  if (iVar8 < 0x1c) {
    uVar11 = uVar2 << 4;
    *(uint *)(param_1 + 0x24c) = uVar2 >> 0x1c;
    iVar8 = iVar8 + 4;
  }
  else {
    iVar8 = iVar8 + -0x1c;
    if (iVar8 == 0) {
      *(uint *)(param_1 + 0x24c) = uVar2 >> 0x1c;
    }
    else {
      *(uint *)(param_1 + 0x24c) = (uVar2 | uVar10 >> 4 - iVar8) >> 0x1c;
      uVar10 = uVar10 << iVar8;
    }
    uVar2 = *puVar7;
    puVar7 = puVar7 + 1;
    uVar11 = uVar10;
    uVar10 = uVar2;
  }
  if (iVar8 < 0x1c) {
    uVar2 = uVar11 << 4;
    iVar8 = iVar8 + 4;
  }
  else {
    iVar8 = iVar8 + -0x1c;
    if (iVar8 != 0) {
      uVar11 = uVar11 | uVar10 >> 4 - iVar8;
      uVar10 = uVar10 << iVar8;
    }
    uVar12 = *puVar7;
    puVar7 = puVar7 + 1;
    uVar2 = uVar10;
    uVar10 = uVar12;
  }
  *(uint *)(param_1 + 0x1b8) = uVar11 >> 0x1c;
  if (iVar8 < 0xe) {
    uVar11 = uVar2 << 0x12;
    *(uint *)(param_1 + 0x250) = uVar2 >> 0xe;
    iVar8 = iVar8 + 0x12;
  }
  else {
    iVar8 = iVar8 + -0xe;
    if (iVar8 == 0) {
      *(uint *)(param_1 + 0x250) = uVar2 >> 0xe;
    }
    else {
      *(uint *)(param_1 + 0x250) = (uVar2 | uVar10 >> 0x12 - iVar8) >> 0xe;
      uVar10 = uVar10 << iVar8;
    }
    uVar2 = *puVar7;
    puVar7 = puVar7 + 1;
    uVar11 = uVar10;
    uVar10 = uVar2;
  }
  iVar9 = iVar8 + 1;
  if (iVar9 < 0x20) {
    uVar11 = uVar11 << 1;
  }
  else {
    iVar9 = iVar8 + -0x1f;
    uVar11 = uVar10 << iVar9;
    uVar10 = *puVar7;
    puVar7 = puVar7 + 1;
  }
  if (iVar9 < 0x16) {
    uVar2 = uVar11 << 10;
    *(uint *)(param_1 + 0x254) = uVar11 >> 0x16;
    iVar9 = iVar9 + 10;
  }
  else {
    iVar9 = iVar9 + -0x16;
    if (iVar9 == 0) {
      *(uint *)(param_1 + 0x254) = uVar11 >> 0x16;
    }
    else {
      *(uint *)(param_1 + 0x254) = (uVar11 | uVar10 >> 10 - iVar9) >> 0x16;
      uVar10 = uVar10 << iVar9;
    }
    uVar11 = *puVar7;
    puVar7 = puVar7 + 1;
    uVar2 = uVar10;
    uVar10 = uVar11;
  }
  *(uint *)(param_1 + 600) = uVar2 >> 0x1f;
  if (iVar9 == 0x1f) {
    uVar11 = *puVar7;
    iVar9 = 0;
    puVar7 = puVar7 + 1;
    uVar2 = uVar10;
    uVar10 = uVar11;
  }
  else {
    uVar2 = uVar2 << 1;
    iVar9 = iVar9 + 1;
  }
  if (iVar9 == 0x1f) {
    uVar12 = *puVar7;
    iVar9 = 0;
    puVar7 = puVar7 + 1;
    uVar11 = uVar10;
    uVar10 = uVar12;
  }
  else {
    uVar11 = uVar2 << 1;
    iVar9 = iVar9 + 1;
  }
  if ((int)uVar2 < 0) {
    pcVar3 = &DAT_8041b468;
    iVar8 = 0x20;
    do {
      if (iVar9 < 0x18) {
        uVar1 = (undefined1)(uVar11 >> 0x18);
        uVar11 = uVar11 << 8;
        iVar9 = iVar9 + 8;
      }
      else {
        iVar9 = iVar9 + -0x18;
        if (iVar9 != 0) {
          uVar11 = uVar11 | uVar10 >> 8 - iVar9;
          uVar10 = uVar10 << iVar9;
        }
        uVar1 = (undefined1)(uVar11 >> 0x18);
        uVar2 = *puVar7;
        puVar7 = puVar7 + 1;
        uVar11 = uVar10;
        uVar10 = uVar2;
      }
      pcVar4 = pcVar3 + 1;
      *(undefined1 *)(param_1 + *pcVar3 + 0xc20) = uVar1;
      if (iVar9 < 0x18) {
        uVar1 = (undefined1)(uVar11 >> 0x18);
        uVar11 = uVar11 << 8;
        iVar9 = iVar9 + 8;
      }
      else {
        iVar9 = iVar9 + -0x18;
        if (iVar9 != 0) {
          uVar11 = uVar11 | uVar10 >> 8 - iVar9;
          uVar10 = uVar10 << iVar9;
        }
        uVar1 = (undefined1)(uVar11 >> 0x18);
        uVar2 = *puVar7;
        puVar7 = puVar7 + 1;
        uVar11 = uVar10;
        uVar10 = uVar2;
      }
      pcVar3 = pcVar3 + 2;
      *(undefined1 *)(param_1 + *pcVar4 + 0xc20) = uVar1;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  else {
    zz_02a9400_((undefined4 *)(param_1 + 0xc20),(undefined4 *)&DAT_8041b428,0x10);
  }
  if (iVar9 == 0x1f) {
    uVar13 = *puVar7;
    uVar12 = 0;
    puVar7 = puVar7 + 1;
    uVar2 = uVar10;
    uVar10 = uVar13;
  }
  else {
    uVar2 = uVar11 << 1;
    uVar12 = iVar9 + 1;
  }
  if ((int)uVar11 < 0) {
    pcVar3 = &DAT_8041b468;
    iVar8 = 0x20;
    do {
      if ((int)uVar12 < 0x18) {
        uVar1 = (undefined1)(uVar2 >> 0x18);
        uVar2 = uVar2 << 8;
        iVar9 = uVar12 + 8;
      }
      else {
        iVar9 = uVar12 - 0x18;
        if (iVar9 != 0) {
          uVar2 = uVar2 | uVar10 >> 8 - iVar9;
          uVar10 = uVar10 << iVar9;
        }
        uVar1 = (undefined1)(uVar2 >> 0x18);
        uVar11 = *puVar7;
        puVar7 = puVar7 + 1;
        uVar2 = uVar10;
        uVar10 = uVar11;
      }
      pcVar4 = pcVar3 + 1;
      *(undefined1 *)(param_1 + *pcVar3 + 0xc60) = uVar1;
      if (iVar9 < 0x18) {
        uVar1 = (undefined1)(uVar2 >> 0x18);
        uVar2 = uVar2 << 8;
        uVar12 = iVar9 + 8;
      }
      else {
        uVar12 = iVar9 - 0x18;
        if (uVar12 != 0) {
          uVar2 = uVar2 | uVar10 >> 8 - uVar12;
          uVar10 = uVar10 << uVar12;
        }
        uVar1 = (undefined1)(uVar2 >> 0x18);
        uVar11 = *puVar7;
        puVar7 = puVar7 + 1;
        uVar2 = uVar10;
        uVar10 = uVar11;
      }
      pcVar3 = pcVar3 + 2;
      *(undefined1 *)(param_1 + *pcVar4 + 0xc60) = uVar1;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  else {
    zz_02a94c4_(param_1 + 0xc60,0x10101010,0x10);
  }
  pcVar3 = (char *)(param_1 + 0x1324);
  cVar5 = '\0';
  *(int *)(param_1 + 0x1b0) = *(int *)(param_1 + 0x1a8) + 0xf >> 4;
  uVar10 = (uint)((param_1 + 0x1fcd) - (int)pcVar3) >> 1;
  iVar9 = 0;
  *(int *)(param_1 + 0x1b4) = *(int *)(param_1 + 0x1ac) + 0xf >> 4;
  *(int *)(param_1 + 0x2e0) = *(int *)(param_1 + 0x1b4) * *(int *)(param_1 + 0x1b0) + -1;
  iVar8 = *(int *)(param_1 + 0x1b0);
  if (pcVar3 < (char *)(param_1 + 0x1fccU)) {
    do {
      if (iVar8 <= iVar9) {
        iVar9 = 0;
        cVar5 = cVar5 + '\x01';
      }
      *pcVar3 = cVar5;
      pcVar3[1] = (char)iVar9;
      pcVar3 = pcVar3 + 2;
      iVar9 = iVar9 + 1;
      uVar10 = uVar10 - 1;
    } while (uVar10 != 0);
  }
  *(uint *)(param_1 + 0x12b0) = uVar12 & 7;
  zz_02779cc_((int *)(param_1 + 0x12a8),
              (int)puVar7 +
              ((((int)((uVar12 - *(int *)(param_1 + 0x12b0)) + 7) >> 3) + -8) -
              *(int *)(param_1 + 0x12a8)),(int *)(param_1 + 0x12a8),aiStack_28);
  (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x12a8);
  (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_28);
  return 0;
}



// ==== 80283224  zz_0283224_ ====

int zz_0283224_(int param_1,undefined4 *param_2,int *param_3)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  
  piVar1 = zz_0276c34_(*param_2,param_2[1]);
  if (piVar1 == (int *)0x0) {
    iVar2 = -1;
  }
  else {
    iVar2 = zz_02832d4_(param_1,piVar1);
    iVar3 = (**(code **)(*piVar1 + 0x24))(piVar1,1);
    *param_3 = param_2[1] - iVar3;
    (**(code **)(*piVar1 + 0xc))(piVar1);
  }
  return iVar2;
}



// ==== 802832d4  zz_02832d4_ ====

int zz_02832d4_(int param_1,int *param_2)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  int *piVar4;
  void *pvVar5;
  int iVar6;
  char *local_78;
  int local_74;
  int aiStack_70 [2];
  char *local_68;
  int local_64;
  int aiStack_60 [2];
  undefined1 auStack_58 [4];
  int local_54;
  char *local_50;
  int local_4c;
  int aiStack_48 [2];
  int aiStack_40 [2];
  int aiStack_38 [2];
  int *local_30;
  int local_2c;
  char *local_28;
  int local_24;
  
  iVar1 = zz_0283ac0_(param_1);
  if (iVar1 == 0) {
    *(undefined4 *)(param_1 + 0x1320) = 0;
    (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,&local_28);
    (**(code **)(*param_2 + 0x1c))(param_2,1,&local_28);
    iVar1 = *(int *)(param_1 + 0x12b4);
    if (iVar1 == 0) {
      pcVar2 = zz_0281140_(local_28,local_24,0x40);
      if (pcVar2 == (char *)0x0) {
        iVar1 = *(int *)(param_1 + 0x12b4);
      }
      else {
        piVar4 = (int *)zz_0281140_(pcVar2 + 4,local_24 - ((int)(pcVar2 + 4) - (int)local_28),
                                    0xffffffff);
        if (piVar4 == (int *)0x0) {
          iVar1 = *(int *)(param_1 + 0x12b4);
        }
        else {
          uVar3 = zz_028132c_(piVar4);
          if ((uVar3 & 0x10) == 0) {
            if (uVar3 != 0) {
              *(undefined4 *)(param_1 + 0x12b4) = 1;
            }
          }
          else {
            *(undefined4 *)(param_1 + 0x12b4) = 2;
          }
          iVar1 = *(int *)(param_1 + 0x12b4);
        }
      }
    }
    if (iVar1 != 2) {
LAB_802833f8:
      do {
        if (*(int *)(param_1 + 0x12a0) == 0) {
LAB_80283444:
          if (*(int *)(param_1 + 0x16c) == 0) {
            iVar1 = -2;
          }
          else {
            iVar1 = -3;
          }
LAB_8028345c:
          do {
            (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,&local_50);
            if (local_4c < 4) {
              (**(code **)(*param_2 + 0x1c))(param_2,1,&local_50);
              iVar6 = 0;
            }
            else {
              piVar4 = (int *)zz_0281140_(local_50,local_4c,0xffffffff);
              if (piVar4 == (int *)0x0) {
                zz_02779cc_((int *)&local_50,local_4c + -3,(int *)&local_50,aiStack_48);
                (**(code **)(*param_2 + 0x20))(param_2,0,&local_50);
                (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_48);
                goto LAB_8028345c;
              }
              iVar6 = zz_028132c_(piVar4);
              zz_02779cc_((int *)&local_50,(int)piVar4 - (int)local_50,(int *)&local_50,aiStack_48);
              (**(code **)(*param_2 + 0x20))(param_2,0,&local_50);
              (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_48);
            }
            if (iVar6 == 0) break;
            if (iVar6 != 0) {
              iVar1 = 0;
              break;
            }
            (**(code **)(*param_2 + 0x18))(param_2,1,4,auStack_58);
            (**(code **)(*param_2 + 0x20))(param_2,0,auStack_58);
          } while (local_54 == 4);
        }
        else {
          *(undefined4 *)(param_1 + 0x12a0) = 0;
          *(int *)(param_1 + 0x12a4) = *(int *)(param_1 + 0x12a4) + 1;
          *(int *)(param_1 + 0x204) = *(int *)(param_1 + 0x204) + 1;
          if (*(int *)(param_1 + 0x16c) != 0) {
            *(int *)(param_1 + 0x208) = *(int *)(param_1 + 0x208) + 1;
            goto LAB_80283444;
          }
          iVar1 = -2;
        }
        if (iVar1 != 0) {
          iVar1 = zz_02816c8_(param_1,iVar1);
          return iVar1;
        }
        (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,&local_30);
        (**(code **)(*param_2 + 0x1c))(param_2,1,&local_30);
        if (local_2c < 4) {
          uVar3 = 0;
        }
        else {
          uVar3 = zz_028132c_(local_30);
        }
        if ((uVar3 == 0) || ((uVar3 & 3) != 0)) {
          return 0;
        }
        if (uVar3 == 0x10) {
          (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x12a8);
          uVar3 = *(uint *)(param_1 + 0x12a8) & 0xfffffffc;
          iVar1 = (*(uint *)(param_1 + 0x12a8) - uVar3) * 8;
          iVar6 = uVar3 + 8;
          if (0x1f < iVar1) {
            iVar1 = iVar1 + -0x20;
            iVar6 = uVar3 + 0xc;
          }
          *(undefined4 *)(param_1 + 0x12b0) = 0;
          zz_02779cc_((int *)(param_1 + 0x12a8),
                      (iVar6 + ((iVar1 - *(int *)(param_1 + 0x12b0)) + 7 >> 3) + -4) -
                      *(int *)(param_1 + 0x12a8),(int *)(param_1 + 0x12a8),aiStack_38);
          (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x12a8);
          (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_38);
          while ((**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,&local_68), 3 < local_64) {
            piVar4 = (int *)zz_0281140_(local_68,local_64,0xffffffff);
            if (piVar4 != (int *)0x0) {
              zz_028132c_(piVar4);
              zz_02779cc_((int *)&local_68,(int)piVar4 - (int)local_68,(int *)&local_68,aiStack_60);
              (**(code **)(*param_2 + 0x20))(param_2,0,&local_68);
              (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_60);
              goto LAB_802833f8;
            }
            zz_02779cc_((int *)&local_68,local_64 + -3,(int *)&local_68,aiStack_60);
            (**(code **)(*param_2 + 0x20))(param_2,0,&local_68);
            (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_60);
          }
          (**(code **)(*param_2 + 0x1c))(param_2,1,&local_68);
        }
        else if ((int)uVar3 < 0x10) {
          if (uVar3 == 8) {
            zz_0282a44_(param_1,param_2);
          }
          else if (((int)uVar3 < 8) && (uVar3 == 4)) {
            zz_02825f4_(param_1,param_2);
          }
        }
        else if (uVar3 == 0x40) {
          zz_0282c1c_(param_1,param_2);
        }
        else if (((int)uVar3 < 0x40) && (uVar3 == 0x20)) {
          (**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,param_1 + 0x12a8);
          pvVar5 = *(void **)(param_1 + 0x12a8);
          uVar3 = (uint)pvVar5 & 0xfffffffc;
          iVar1 = ((int)pvVar5 - uVar3) * 8;
          iVar6 = uVar3 + 8;
          if (0x1f < iVar1) {
            iVar1 = iVar1 + -0x20;
            iVar6 = uVar3 + 0xc;
          }
          zz_028243c_(param_1,pvVar5,*(int *)(param_1 + 0x12ac));
          *(undefined4 *)(param_1 + 0x12b0) = 0;
          zz_02779cc_((int *)(param_1 + 0x12a8),
                      (iVar6 + ((iVar1 - *(int *)(param_1 + 0x12b0)) + 7 >> 3) + -4) -
                      *(int *)(param_1 + 0x12a8),(int *)(param_1 + 0x12a8),aiStack_40);
          (**(code **)(*param_2 + 0x20))(param_2,0,param_1 + 0x12a8);
          (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_40);
          while ((**(code **)(*param_2 + 0x18))(param_2,1,0x7fffffff,&local_78), 3 < local_74) {
            piVar4 = (int *)zz_0281140_(local_78,local_74,0xffffffff);
            if (piVar4 != (int *)0x0) {
              zz_028132c_(piVar4);
              zz_02779cc_((int *)&local_78,(int)piVar4 - (int)local_78,(int *)&local_78,aiStack_70);
              (**(code **)(*param_2 + 0x20))(param_2,0,&local_78);
              (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_70);
              goto LAB_802833f8;
            }
            zz_02779cc_((int *)&local_78,local_74 + -3,(int *)&local_78,aiStack_70);
            (**(code **)(*param_2 + 0x20))(param_2,0,&local_78);
            (**(code **)(*param_2 + 0x1c))(param_2,1,aiStack_70);
          }
          (**(code **)(*param_2 + 0x1c))(param_2,1,&local_78);
        }
      } while( true );
    }
    iVar1 = zz_0296ff0_();
  }
  else {
    iVar1 = zz_02816c8_(0,-0xfcfdf4);
  }
  return iVar1;
}



// ==== 80283a6c  zz_0283a6c_ ====

void zz_0283a6c_(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = *(undefined4 *)(param_1 + 0x1318);
  }
  if (param_3 == (undefined4 *)0x0) {
    return;
  }
  *param_3 = *(undefined4 *)(param_1 + 0x1320);
  return;
}



// ==== 80283a90  zz_0283a90_ ====

void zz_0283a90_(int param_1,undefined4 param_2,undefined4 param_3)

{
  *(undefined4 *)(param_1 + 0x1318) = param_2;
  *(undefined4 *)(param_1 + 0x131c) = param_3;
  *(undefined4 *)(param_1 + 0x1320) = 0;
  return;
}



// ==== 80283aa4  zz_0283aa4_ ====

void zz_0283aa4_(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5)

{
  undefined4 *puVar1;
  
  puVar1 = (undefined4 *)(param_1 + param_2 * 0xc + 0x12e8);
  *puVar1 = param_3;
  puVar1[1] = param_4;
  puVar1[2] = param_5;
  return;
}



// ==== 80283ac0  zz_0283ac0_ ====

int zz_0283ac0_(int param_1)

{
  DAT_8041b8e8 = param_1;
  if (param_1 == 0) {
    return -1;
  }
  return (int)(*(int *)(param_1 + 0x160) - 2U | 2U - *(int *)(param_1 + 0x160)) >> 0x1f;
}



// ==== 80283af0  zz_0283af0_ ====

/* WARNING: Removing unreachable block (ram,0x80283b74) */

int zz_0283af0_(int param_1,int param_2,undefined *param_3)

{
  undefined *puVar1;
  int iVar2;
  int iVar3;
  
  if ((param_2 == 8) && (param_3 == (undefined *)0x0)) {
    param_3 = &DAT_80283bd0;
  }
  if (param_1 == 0) {
    iVar2 = DAT_8041b94c;
    iVar3 = DAT_8041b948;
    if (0 < DAT_8041b948) {
      do {
        if (*(int *)(iVar2 + 0x160) == 2) {
          *(undefined **)(param_2 * 4 + iVar2 + 0x168) = param_3;
        }
        iVar2 = iVar2 + 0x1fe0;
        iVar3 = iVar3 + -1;
      } while (iVar3 != 0);
    }
    puVar1 = &DAT_8041b8f4;
  }
  else {
    if (*(int *)(param_1 + 0x160) == 2) {
      iVar2 = 0;
    }
    else {
      iVar2 = -1;
    }
    DAT_8041b8e8 = param_1;
    if (iVar2 != 0) {
      iVar2 = zz_02816c8_(0,-0xfcfdfe);
      return iVar2;
    }
    puVar1 = (undefined *)(param_1 + 0x168);
  }
  *(undefined **)(puVar1 + param_2 * 4) = param_3;
  return 0;
}



// ==== 80283bd4  zz_0283bd4_ ====

int zz_0283bd4_(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == 0) {
    iVar1 = -1;
  }
  else if (*(int *)(param_1 + 0x160) == 2) {
    iVar1 = 0;
  }
  else {
    iVar1 = -1;
  }
  DAT_8041b8e8 = param_1;
  if (iVar1 == 0) {
    zz_0296ff8_();
    if ((DAT_8041b93c & 0x10000000) != 0) {
      iVar1 = 0;
      iVar2 = 0x33;
      do {
        dataCacheBlockInvalidate(param_1 + iVar1);
        dataCacheBlockInvalidate(param_1 + iVar1 + 0x20);
        dataCacheBlockInvalidate(param_1 + iVar1 + 0x40);
        dataCacheBlockInvalidate(param_1 + iVar1 + 0x60);
        dataCacheBlockInvalidate(param_1 + iVar1 + 0x80);
        iVar1 = iVar1 + 0xa0;
        iVar2 = iVar2 + -1;
      } while (iVar2 != 0);
    }
    iVar1 = 0;
    *(undefined4 *)(param_1 + 0x160) = 1;
  }
  else {
    iVar1 = zz_02816c8_(0,-0xfcfdff);
  }
  return iVar1;
}



// ==== 80283ca4  zz_0283ca4_ ====

void zz_0283ca4_(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  *param_2 = *(undefined4 *)(param_1 + 0x88);
  *param_3 = *(undefined4 *)(param_1 + 0x8c);
  return;
}



// ==== 80283cb8  zz_0283cb8_ ====

int zz_0283cb8_(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_8041b944;
  iVar2 = DAT_8041b944 + 0x20;
  *(undefined4 *)(param_1 + 0x10) = DAT_8041cf58;
  *(int *)(param_1 + 0x14) = DAT_8041cf5c + -0x10;
  *(int *)(param_1 + 0x18) = DAT_8041cf60 + -0x20;
  *(int *)(param_1 + 0x1c) = DAT_8041cf64 + -0x20;
  *(undefined4 *)(param_1 + 0x20) = DAT_8041cf68;
  *(undefined4 *)(param_1 + 0x24) = DAT_8041cf6c;
  *(undefined4 *)(param_1 + 0x28) = DAT_8041cf70;
  *(int *)(param_1 + 0x2c) = iVar2;
  *(int *)(param_1 + 0x30) = iVar1;
  *(int *)(param_1 + 0x34) = iVar1 + 0x60;
  *(undefined4 *)(param_1 + 0x38) = DAT_8041b8e4;
  *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_1 + 0x38);
  *(int *)(param_1 + 0xec) = param_1 + 800;
  *(int *)(param_1 + 0xf0) = param_1 + 0xca0;
  *(int *)(param_1 + 0xf4) = *(int *)(param_1 + 0xf0) + 0x180;
  *(int *)(param_1 + 0x2f8) = param_1 + 0x420;
  *(int *)(param_1 + 0x2fc) = param_1 + 0x4a0;
  *(int *)(param_1 + 0x300) = param_1 + 0x520;
  *(int *)(param_1 + 0x304) = param_1 + 0x5a0;
  *(int *)(param_1 + 0x308) = param_1 + 800;
  *(int *)(param_1 + 0x30c) = param_1 + 0x3a0;
  *(undefined4 *)(param_1 + 0x28c) = 0;
  *(undefined4 *)(param_1 + 0x164) = 0;
  zz_02a9400_((undefined4 *)(param_1 + 0x168),(undefined4 *)&DAT_8041b8f4,0x10);
  zz_02817dc_((undefined4 *)(param_1 + 0x1f8));
  zz_027fbbc_(param_1);
  zz_027c6e8_((void *)(param_1 + 0x70));
  *(int *)(param_1 + 0xb8) = param_1 + 0xca0;
  *(int *)(param_1 + 0x9c) = param_1 + 0x620;
  *(int *)(param_1 + 0xa0) = param_1 + 0x2f8;
  *(undefined4 *)(param_1 + 0x1a8) = 0;
  iVar1 = 0;
  *(undefined4 *)(param_1 + 0x1ac) = 0;
  *(undefined4 *)(param_1 + 0x1b0) = 0;
  *(undefined4 *)(param_1 + 0x1b4) = 0;
  *(undefined4 *)(param_1 + 0x1b8) = 0;
  *(undefined4 *)(param_1 + 0x1bc) = 0;
  *(undefined4 *)(param_1 + 0x1c0) = 0;
  *(undefined4 *)(param_1 + 0x1c4) = 0;
  *(undefined4 *)(param_1 + 0x1c8) = 0;
  *(undefined4 *)(param_1 + 0x1cc) = 0;
  *(undefined4 *)(param_1 + 0x1d0) = 0;
  *(undefined4 *)(param_1 + 0x1d4) = 0;
  *(undefined4 *)(param_1 + 0x1d8) = 0;
  *(undefined4 *)(param_1 + 0x1dc) = 3;
  *(undefined4 *)(param_1 + 0x1e0) = 1;
  *(undefined4 *)(param_1 + 0x1e4) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1e8) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1ec) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x1f0) = 1;
  *(undefined4 *)(param_1 + 500) = 1;
  *(undefined4 *)(param_1 + 0x12a0) = 0;
  *(undefined4 *)(param_1 + 0x12a4) = 0;
  *(undefined4 *)(param_1 + 0x12d8) = DAT_8041cf80;
  *(undefined4 *)(param_1 + 0x12dc) = DAT_8041cf7c;
  *(undefined4 *)(param_1 + 0x12b4) = 0;
  *(undefined4 *)(param_1 + 0x12b8) = 0;
  *(undefined4 *)(param_1 + 0x12bc) = 0;
  *(undefined4 *)(param_1 + 0x12c0) = 0;
  *(undefined4 *)(param_1 + 0x12c4) = 0;
  *(code **)(param_1 + 0x12c8) = FUN_8028d9f4;
  *(code **)(param_1 + 0x12cc) = zz_028955c_;
  *(undefined4 *)(param_1 + 0x12d4) = *(undefined4 *)(param_1 + 0x184);
  do {
    zz_0283aa4_(param_1,iVar1,0,0,0);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 4);
  zz_0283a90_(param_1,0,0);
  *(undefined4 *)(param_1 + 0x160) = 2;
  return param_1;
}



// ==== 80283f10  zz_0283f10_ ====

int zz_0283f10_(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar1 = DAT_8041b94c;
  iVar2 = DAT_8041b948;
  if (0 < DAT_8041b948) {
    do {
      if (*(int *)(iVar1 + 0x160) == 1) goto LAB_80283f58;
      iVar1 = iVar1 + 0x1fe0;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  iVar1 = 0;
LAB_80283f58:
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    if ((DAT_8041b93c & 0x10000000) != 0) {
      iVar2 = 0;
      iVar4 = 0x33;
      do {
        dataCacheBlockInvalidate(iVar1 + iVar2);
        dataCacheBlockSetToZeroLocked(iVar1 + iVar2);
        dataCacheBlockInvalidate(iVar1 + iVar2 + 0x20);
        dataCacheBlockSetToZeroLocked(iVar1 + iVar2 + 0x20);
        dataCacheBlockInvalidate(iVar1 + iVar2 + 0x40);
        dataCacheBlockSetToZeroLocked(iVar1 + iVar2 + 0x40);
        dataCacheBlockInvalidate(iVar1 + iVar2 + 0x60);
        dataCacheBlockSetToZeroLocked(iVar1 + iVar2 + 0x60);
        dataCacheBlockInvalidate(iVar1 + iVar2 + 0x80);
        dataCacheBlockSetToZeroLocked(iVar1 + iVar2 + 0x80);
        iVar2 = iVar2 + 0xa0;
        iVar4 = iVar4 + -1;
      } while (iVar4 != 0);
    }
    iVar1 = zz_0283cb8_(iVar1);
    uVar3 = zz_0296ffc_();
    *(undefined4 *)(iVar1 + 0x12e0) = uVar3;
  }
  return iVar1;
}



// ==== 80283ff8  zz_0283ff8_ ====

undefined8 zz_0283ff8_(void)

{
  undefined *puVar1;
  int iVar2;
  
  zz_0297004_();
  puVar1 = &DAT_8041b8f4;
  if ((DAT_8041b93c & 0x10000000) != 0) {
    puVar1 = (undefined *)0x0;
    iVar2 = 0x59;
    do {
      dataCacheBlockInvalidate(puVar1 + DAT_8041b944);
      puVar1 = puVar1 + 0x20;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return CONCAT44(puVar1,DAT_8041b944);
}



// ==== 80284048  zz_0284048_ ====

/* WARNING: Removing unreachable block (ram,0x802840c0) */
/* WARNING: Removing unreachable block (ram,0x80284084) */

undefined4 zz_0284048_(uint param_1,uint param_2)

{
  int iVar1;
  char cVar3;
  uint uVar2;
  char *pcVar4;
  uint uVar5;
  int iVar6;
  undefined4 *puVar7;
  int iVar8;
  uint uVar9;
  uint in_HID2;
  uint local_28;
  
  DAT_8041b950 = s_CRI_MPV_GC_Ver_1_840_Build_Feb_6_802b88c8;
  iVar6 = zz_0288084_();
  if (iVar6 == 0) {
    if (DAT_802b895c == 0x5a5a5a5a) {
      iVar6 = 0;
    }
    else {
      iVar6 = zz_02816c8_(0,-0xfc00fe);
    }
  }
  else {
    iVar6 = zz_02816c8_(0,-0xfc00fd);
  }
  if (iVar6 != 0) {
    if (iVar6 == -0xfc00fb) {
      return 0xff03ff05;
    }
    do {
                    /* WARNING: Do nothing block with infinite loop */
    } while( true );
  }
  local_28 = in_HID2;
  if (DAT_8041b4e0 == 0) {
    local_28 = in_HID2 & 0xefffffff;
  }
  DAT_8041b93c = local_28;
  if (DAT_8041b938 != 0) {
    param_2 = param_2 | 0x2000000;
  }
  uVar2 = param_2 + 0x1f & 0xffffffe0;
  zz_02a94c4_(uVar2,0,param_1 * 0x2000 + 0x2000 >> 2);
  iVar6 = uVar2 + param_1 * 0x1fe0;
  puVar7 = (undefined4 *)(iVar6 + 0x14e0);
  if ((DAT_8041b93c & 0x10000000) != 0) {
    iVar1 = 0;
    iVar8 = 0x59;
    do {
      dataCacheBlockInvalidate((int)puVar7 + iVar1);
      dataCacheBlockSetToZeroLocked((int)puVar7 + iVar1);
      iVar1 = iVar1 + 0x20;
      iVar8 = iVar8 + -1;
    } while (iVar8 != 0);
  }
  zz_02a9400_((undefined4 *)&DAT_8041b8f4,(undefined4 *)&DAT_802b891c,0x10);
  DAT_8041b940 = iVar6;
  DAT_8041b944 = puVar7;
  DAT_8041b948 = param_1;
  DAT_8041b94c = uVar2;
  zz_02817f8_();
  zz_0281a1c_();
  zz_0287e58_((undefined4 *)(iVar6 + 0x1650));
  zz_027e18c_(puVar7);
  zz_02894d0_();
  pcVar4 = &DAT_8041b4e4;
  iVar1 = 0x30;
  do {
    *pcVar4 = '\0';
    pcVar4[1] = '\0';
    pcVar4[2] = '\0';
    pcVar4[3] = '\0';
    pcVar4[4] = '\0';
    pcVar4[5] = '\0';
    pcVar4[6] = '\0';
    pcVar4[7] = '\0';
    pcVar4 = pcVar4 + 8;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  cVar3 = '\0';
  iVar1 = 0x20;
  do {
    *pcVar4 = cVar3;
    pcVar4[1] = cVar3 + '\x01';
    pcVar4[2] = cVar3 + '\x02';
    pcVar4[3] = cVar3 + '\x03';
    pcVar4[4] = cVar3 + '\x04';
    pcVar4[5] = cVar3 + '\x05';
    pcVar4[6] = cVar3 + '\x06';
    pcVar4[7] = cVar3 + '\a';
    pcVar4 = pcVar4 + 8;
    cVar3 = cVar3 + '\b';
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  iVar1 = 0x30;
  do {
    *pcVar4 = -1;
    pcVar4[1] = -1;
    pcVar4[2] = -1;
    pcVar4[3] = -1;
    pcVar4[4] = -1;
    pcVar4[5] = -1;
    pcVar4[6] = -1;
    pcVar4[7] = -1;
    pcVar4 = pcVar4 + 8;
    iVar1 = iVar1 + -1;
  } while (iVar1 != 0);
  DAT_8041b8e4 = &DAT_8041b664;
  if (iVar6 != -0x1c00) {
    zz_02a9400_((undefined4 *)(iVar6 + 0x1c00),(undefined4 *)&DAT_8041b4e4,0x100);
    DAT_8041b8e4 = (undefined *)(iVar6 + 0x1d80);
  }
  uVar2 = DAT_8041b948;
  if (0 < (int)DAT_8041b948) {
    uVar9 = DAT_8041b948 >> 3;
    uVar5 = DAT_8041b94c;
    if (uVar9 != 0) {
      do {
        *(undefined4 *)(uVar5 + 0x160) = 1;
        *(undefined4 *)(uVar5 + 0x2140) = 1;
        *(undefined4 *)(uVar5 + 0x4120) = 1;
        *(undefined4 *)(uVar5 + 0x6100) = 1;
        *(undefined4 *)(uVar5 + 0x80e0) = 1;
        *(undefined4 *)(uVar5 + 0xa0c0) = 1;
        *(undefined4 *)(uVar5 + 0xc0a0) = 1;
        *(undefined4 *)(uVar5 + 0xe080) = 1;
        uVar5 = uVar5 + 0xff00;
        uVar9 = uVar9 - 1;
      } while (uVar9 != 0);
      uVar2 = uVar2 & 7;
      if (uVar2 == 0) goto LAB_80284348;
    }
    do {
      *(undefined4 *)(uVar5 + 0x160) = 1;
      uVar2 = uVar2 - 1;
      uVar5 = uVar5 + 0x1fe0;
    } while (uVar2 != 0);
  }
LAB_80284348:
  zz_027c814_();
  zz_027c710_(iVar6 + 0x1540);
  zz_0297008_();
  return 0;
}



// ==== 80284370  zz_0284370_ ====

void zz_0284370_(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  uint *puVar11;
  int iVar12;
  byte *pbVar13;
  byte *pbVar14;
  int iVar15;
  
  iVar12 = *(int *)(param_1 + 0x10);
  pbVar13 = *(byte **)(param_1 + 0x14);
  pbVar14 = *(byte **)(param_1 + 0x18);
  puVar11 = *(uint **)(param_1 + 8);
  iVar15 = 8;
  do {
    dataCacheBlockTouch(pbVar14 + iVar12);
    bVar1 = pbVar13[4];
    bVar2 = pbVar14[4];
    bVar3 = pbVar13[5];
    bVar4 = pbVar14[5];
    bVar5 = pbVar13[6];
    bVar6 = pbVar14[6];
    bVar7 = pbVar13[8];
    bVar8 = pbVar13[7];
    bVar9 = pbVar14[7];
    bVar10 = pbVar14[8];
    *puVar11 = (uint)pbVar13[3] + (uint)bVar1 + (uint)pbVar14[3] + (uint)bVar2 + 2 >> 2 & 0xff |
               ((uint)pbVar13[2] + (uint)pbVar13[3] + (uint)pbVar14[2] + (uint)pbVar14[3] + 2) *
               0x40 & 0xff00 |
               ((uint)*pbVar13 + (uint)pbVar13[1] + (uint)*pbVar14 + (uint)pbVar14[1] + 2) *
               0x400000 & 0xff000000 |
               ((uint)pbVar13[1] + (uint)pbVar13[2] + (uint)pbVar14[1] + (uint)pbVar14[2] + 2) *
               0x4000 & 0xff0000;
    pbVar13 = pbVar13 + iVar12;
    pbVar14 = pbVar14 + iVar12;
    puVar11[1] = (uint)bVar8 + (uint)bVar7 + (uint)bVar9 + (uint)bVar10 + 2 >> 2 & 0xff |
                 ((uint)bVar5 + (uint)bVar8 + (uint)bVar6 + (uint)bVar9 + 2) * 0x40 & 0xff00 |
                 ((uint)bVar1 + (uint)bVar3 + (uint)bVar2 + (uint)bVar4 + 2) * 0x400000 & 0xff000000
                 | ((uint)bVar3 + (uint)bVar5 + (uint)bVar4 + (uint)bVar6 + 2) * 0x4000 & 0xff0000;
    puVar11 = puVar11 + 2;
    iVar15 = iVar15 + -1;
  } while (iVar15 != 0);
  return;
}



// ==== 802844a0  zz_02844a0_ ====

/* WARNING: Removing unreachable block (ram,0x802844d8) */

void zz_02844a0_(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  uint *puVar5;
  int *piVar6;
  int *piVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  
  puVar5 = *(uint **)(param_1 + 0x14);
  piVar4 = *(int **)(param_1 + 8);
  uVar1 = (uint)puVar5 & 3;
  iVar2 = *(int *)(param_1 + 0x10);
  if (uVar1 == 2) {
    iVar12 = 4;
    piVar6 = (int *)((int)puVar5 + -2);
    do {
      dataCacheBlockTouch((int)piVar6 + iVar2);
      uVar1 = piVar6[1];
      uVar3 = uVar1 >> 8 | *piVar6 << 0x18;
      uVar8 = uVar1 >> 0x10 | *piVar6 << 0x10;
      uVar11 = uVar8 ^ uVar3;
      uVar10 = (uint)piVar6[2] >> 8 | uVar1 << 0x18;
      uVar9 = (uint)piVar6[2] >> 0x10 | uVar1 << 0x10;
      piVar6 = (int *)((int)piVar6 + iVar2);
      uVar1 = uVar9 ^ uVar10;
      *piVar4 = (uVar8 & uVar3) + (uVar11 & 0x1010101) + ((uVar11 & 0xfefefefe) >> 1);
      piVar4[1] = (uVar9 & uVar10) + (uVar1 & 0x1010101) + ((uVar1 & 0xfefefefe) >> 1);
      dataCacheBlockTouch((int)piVar6 + iVar2);
      uVar1 = piVar6[1];
      uVar3 = uVar1 >> 8 | *piVar6 << 0x18;
      uVar8 = uVar1 >> 0x10 | *piVar6 << 0x10;
      uVar11 = uVar8 ^ uVar3;
      uVar10 = (uint)piVar6[2] >> 8 | uVar1 << 0x18;
      uVar9 = (uint)piVar6[2] >> 0x10 | uVar1 << 0x10;
      piVar6 = (int *)((int)piVar6 + iVar2);
      uVar1 = uVar9 ^ uVar10;
      piVar4[2] = (uVar8 & uVar3) + (uVar11 & 0x1010101) + ((uVar11 & 0xfefefefe) >> 1);
      piVar4[3] = (uVar9 & uVar10) + (uVar1 & 0x1010101) + ((uVar1 & 0xfefefefe) >> 1);
      piVar4 = piVar4 + 4;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
    return;
  }
  if (uVar1 < 2) {
    if (uVar1 != 0) {
      iVar12 = 4;
      piVar6 = (int *)((int)puVar5 + -1);
      do {
        dataCacheBlockTouch((int)piVar6 + iVar2);
        uVar8 = piVar6[1];
        uVar3 = *piVar6 << 8 | uVar8 >> 0x18;
        uVar1 = *piVar6 << 0x10 | uVar8 >> 0x10;
        uVar10 = uVar8 << 0x10 | (uint)*(ushort *)(piVar6 + 2);
        uVar11 = uVar3 ^ uVar1;
        uVar9 = (uint)(*(ushort *)(piVar6 + 2) >> 8) | uVar8 << 8;
        uVar8 = uVar9 ^ uVar10;
        *piVar4 = (uVar3 & uVar1) + (uVar11 & 0x1010101) + ((uVar11 & 0xfefefefe) >> 1);
        piVar7 = (int *)((int)piVar6 + iVar2);
        piVar4[1] = (uVar9 & uVar10) + (uVar8 & 0x1010101) + ((uVar8 & 0xfefefefe) >> 1);
        dataCacheBlockTouch((int)piVar7 + iVar2);
        uVar8 = piVar7[1];
        uVar10 = uVar8 << 0x10 | (uint)*(ushort *)(piVar7 + 2);
        piVar6 = (int *)((int)piVar7 + iVar2);
        uVar3 = *piVar7 << 8 | uVar8 >> 0x18;
        uVar1 = *piVar7 << 0x10 | uVar8 >> 0x10;
        uVar11 = uVar3 ^ uVar1;
        uVar9 = (uint)(*(ushort *)(piVar7 + 2) >> 8) | uVar8 << 8;
        uVar8 = uVar9 ^ uVar10;
        piVar4[2] = (uVar3 & uVar1) + (uVar11 & 0x1010101) + ((uVar11 & 0xfefefefe) >> 1);
        piVar4[3] = (uVar9 & uVar10) + (uVar8 & 0x1010101) + ((uVar8 & 0xfefefefe) >> 1);
        piVar4 = piVar4 + 4;
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
      return;
    }
    iVar12 = 4;
    do {
      dataCacheBlockTouch((int)puVar5 + iVar2);
      uVar8 = *puVar5;
      uVar9 = puVar5[1];
      uVar3 = uVar9 >> 0x18 | uVar8 << 8;
      uVar10 = uVar9 << 8 | (uint)*(byte *)(puVar5 + 2);
      uVar11 = uVar8 ^ uVar3;
      puVar5 = (uint *)((int)puVar5 + iVar2);
      uVar1 = uVar9 ^ uVar10;
      *piVar4 = (uVar8 & uVar3) + (uVar11 & 0x1010101) + ((uVar11 & 0xfefefefe) >> 1);
      piVar4[1] = (uVar9 & uVar10) + (uVar1 & 0x1010101) + ((uVar1 & 0xfefefefe) >> 1);
      dataCacheBlockTouch((int)puVar5 + iVar2);
      uVar8 = *puVar5;
      uVar9 = puVar5[1];
      uVar3 = uVar9 >> 0x18 | uVar8 << 8;
      uVar10 = uVar9 << 8 | (uint)*(byte *)(puVar5 + 2);
      uVar11 = uVar8 ^ uVar3;
      puVar5 = (uint *)((int)puVar5 + iVar2);
      uVar1 = uVar9 ^ uVar10;
      piVar4[2] = (uVar8 & uVar3) + (uVar11 & 0x1010101) + ((uVar11 & 0xfefefefe) >> 1);
      piVar4[3] = (uVar9 & uVar10) + (uVar1 & 0x1010101) + ((uVar1 & 0xfefefefe) >> 1);
      piVar4 = piVar4 + 4;
      iVar12 = iVar12 + -1;
    } while (iVar12 != 0);
    return;
  }
  if (uVar1 < 4) {
    iVar13 = 4;
    iVar12 = (int)puVar5 + -3;
    do {
      dataCacheBlockTouch(iVar12 + iVar2);
      uVar3 = *(uint *)(iVar12 + 4);
      uVar8 = uVar3 >> 8 | (uint)*(byte *)(iVar12 + 3) << 0x18;
      uVar10 = *(uint *)(iVar12 + 8);
      uVar11 = uVar8 ^ uVar3;
      uVar9 = uVar10 >> 8 | uVar3 << 0x18;
      uVar1 = uVar9 ^ uVar10;
      *piVar4 = (uVar8 & uVar3) + (uVar11 & 0x1010101) + ((uVar11 & 0xfefefefe) >> 1);
      iVar12 = iVar12 + iVar2;
      piVar4[1] = (uVar9 & uVar10) + (uVar1 & 0x1010101) + ((uVar1 & 0xfefefefe) >> 1);
      dataCacheBlockTouch(iVar12 + iVar2);
      uVar3 = *(uint *)(iVar12 + 4);
      uVar8 = uVar3 >> 8 | (uint)*(byte *)(iVar12 + 3) << 0x18;
      uVar10 = *(uint *)(iVar12 + 8);
      uVar11 = uVar8 ^ uVar3;
      uVar9 = uVar10 >> 8 | uVar3 << 0x18;
      uVar1 = uVar9 ^ uVar10;
      piVar4[2] = (uVar8 & uVar3) + (uVar11 & 0x1010101) + ((uVar11 & 0xfefefefe) >> 1);
      iVar12 = iVar12 + iVar2;
      piVar4[3] = (uVar9 & uVar10) + (uVar1 & 0x1010101) + ((uVar1 & 0xfefefefe) >> 1);
      piVar4 = piVar4 + 4;
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
    return;
  }
  return;
}



// ==== 8028488c  FUN_8028488c ====

/* WARNING: Removing unreachable block (ram,0x802848cc) */

void FUN_8028488c(int param_1)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  uint *puVar4;
  uint *puVar5;
  int *piVar6;
  uint *puVar7;
  int *piVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  int iVar14;
  
  puVar4 = *(uint **)(param_1 + 0x14);
  puVar7 = *(uint **)(param_1 + 0x18);
  uVar2 = (uint)puVar4 & 3;
  piVar3 = *(int **)(param_1 + 8);
  iVar1 = *(int *)(param_1 + 0x10);
  if (uVar2 == 2) {
    iVar14 = 8;
    piVar6 = (int *)((int)puVar4 - 2);
    piVar8 = (int *)((int)puVar7 + -2);
    do {
      uVar2 = *piVar6 << 0x10 | (uint)piVar6[1] >> 0x10;
      uVar12 = piVar6[1] << 0x10 | (uint)*(ushort *)(piVar6 + 2);
      uVar10 = *piVar8 << 0x10 | (uint)piVar8[1] >> 0x10;
      uVar11 = piVar8[1] << 0x10 | (uint)*(ushort *)(piVar8 + 2);
      uVar9 = uVar2 ^ uVar10;
      piVar6 = (int *)((int)piVar6 + iVar1);
      uVar13 = uVar12 ^ uVar11;
      *piVar3 = (uVar2 & uVar10) + ((uVar9 & 0xfefefefe) >> 1) + (uVar9 & 0x1010101);
      piVar8 = (int *)((int)piVar8 + iVar1);
      piVar3[1] = (uVar12 & uVar11) + ((uVar13 & 0xfefefefe) >> 1) + (uVar13 & 0x1010101);
      piVar3 = piVar3 + 2;
      iVar14 = iVar14 + -1;
    } while (iVar14 != 0);
  }
  else if (uVar2 < 2) {
    if (uVar2 == 0) {
      iVar14 = 4;
      do {
        uVar10 = puVar4[1];
        puVar5 = (uint *)((int)puVar4 + iVar1);
        uVar11 = puVar7[1];
        uVar2 = *puVar4 ^ *puVar7;
        uVar9 = uVar10 ^ uVar11;
        *piVar3 = (*puVar4 & *puVar7) + ((uVar2 & 0xfefefefe) >> 1) + (uVar2 & 0x1010101);
        puVar7 = (uint *)((int)puVar7 + iVar1);
        piVar3[1] = (uVar10 & uVar11) + ((uVar9 & 0xfefefefe) >> 1) + (uVar9 & 0x1010101);
        uVar10 = puVar5[1];
        puVar4 = (uint *)((int)puVar5 + iVar1);
        uVar11 = puVar7[1];
        uVar2 = *puVar5 ^ *puVar7;
        uVar9 = uVar10 ^ uVar11;
        piVar3[2] = (*puVar5 & *puVar7) + ((uVar2 & 0xfefefefe) >> 1) + (uVar2 & 0x1010101);
        puVar7 = (uint *)((int)puVar7 + iVar1);
        piVar3[3] = (uVar10 & uVar11) + ((uVar9 & 0xfefefefe) >> 1) + (uVar9 & 0x1010101);
        piVar3 = piVar3 + 4;
        iVar14 = iVar14 + -1;
      } while (iVar14 != 0);
    }
    else {
      iVar14 = 8;
      piVar6 = (int *)((int)puVar4 - 1);
      piVar8 = (int *)((int)puVar7 + -1);
      do {
        uVar2 = *piVar6 << 8 | (uint)piVar6[1] >> 0x18;
        uVar10 = *piVar8 << 8 | (uint)piVar8[1] >> 0x18;
        uVar12 = piVar6[1] << 8 | (uint)*(byte *)(piVar6 + 2);
        uVar9 = uVar2 ^ uVar10;
        uVar11 = piVar8[1] << 8 | (uint)*(byte *)(piVar8 + 2);
        uVar13 = uVar12 ^ uVar11;
        piVar6 = (int *)((int)piVar6 + iVar1);
        piVar8 = (int *)((int)piVar8 + iVar1);
        *piVar3 = (uVar2 & uVar10) + ((uVar9 & 0xfefefefe) >> 1) + (uVar9 & 0x1010101);
        piVar3[1] = (uVar12 & uVar11) + ((uVar13 & 0xfefefefe) >> 1) + (uVar13 & 0x1010101);
        piVar3 = piVar3 + 2;
        iVar14 = iVar14 + -1;
      } while (iVar14 != 0);
    }
  }
  else if (uVar2 < 4) {
    iVar14 = 8;
    piVar6 = (int *)((int)puVar4 - 3);
    piVar8 = (int *)((int)puVar7 + -3);
    do {
      uVar2 = *piVar6 << 0x18 | (uint)piVar6[1] >> 8;
      uVar10 = *piVar8 << 0x18 | (uint)piVar8[1] >> 8;
      uVar13 = piVar6[1] << 0x18 | (uint)piVar6[2] >> 8;
      piVar6 = (int *)((int)piVar6 + iVar1);
      uVar9 = uVar2 ^ uVar10;
      uVar12 = piVar8[1] << 0x18 | (uint)piVar8[2] >> 8;
      piVar8 = (int *)((int)piVar8 + iVar1);
      uVar11 = uVar13 ^ uVar12;
      *piVar3 = (uVar2 & uVar10) + ((uVar9 & 0xfefefefe) >> 1) + (uVar9 & 0x1010101);
      piVar3[1] = (uVar13 & uVar12) + ((uVar11 & 0xfefefefe) >> 1) + (uVar11 & 0x1010101);
      piVar3 = piVar3 + 2;
      iVar14 = iVar14 + -1;
    } while (iVar14 != 0);
  }
  return;
}



// ==== 8028500c  zz_028500c_ ====

void zz_028500c_(void)

{
  return;
}



// ==== 80285010  zz_0285010_ ====

void zz_0285010_(void)

{
  DAT_8041b958 = 0;
  DAT_8041b95c = 0;
  DAT_8041b960 = 0;
  DAT_8041b964 = 0;
  DAT_8041b968 = 0x64040;
  DAT_8041b96c = 0x64040;
  DAT_8041b970 = 0x64040;
  DAT_8041b974 = 0x64040;
  DAT_8041b978 = 0x80202;
  DAT_8041b97c = 0x80202;
  DAT_8041b980 = 0x80109;
  DAT_8041b984 = 0x80109;
  DAT_8041b988 = 0x80400;
  DAT_8041b98c = 0x80400;
  DAT_8041b990 = 0x80108;
  DAT_8041b994 = 0x80108;
  DAT_8041b998 = 0x70107;
  DAT_8041b99c = 0x70107;
  DAT_8041b9a0 = 0x70107;
  DAT_8041b9a4 = 0x70107;
  DAT_8041b9a8 = 0x70106;
  DAT_8041b9ac = 0x70106;
  DAT_8041b9b0 = 0x70106;
  DAT_8041b9b4 = 0x70106;
  DAT_8041b9b8 = 0x70201;
  DAT_8041b9bc = 0x70201;
  DAT_8041b9c0 = 0x70201;
  DAT_8041b9c4 = 0x70201;
  DAT_8041b9c8 = 0x70105;
  DAT_8041b9cc = 0x70105;
  DAT_8041b9d0 = 0x70105;
  DAT_8041b9d4 = 0x70105;
  DAT_8041b9d8 = 0x9010d;
  DAT_8041b9dc = 0x90600;
  DAT_8041b9e0 = 0x9010c;
  DAT_8041b9e4 = 0x9010b;
  DAT_8041b9e8 = 0x90203;
  DAT_8041b9ec = 0x90301;
  DAT_8041b9f0 = 0x90500;
  DAT_8041b9f4 = 0x9010a;
  DAT_8041b9f8 = 0x60300;
  DAT_8041b9fc = 0x60300;
  DAT_8041ba00 = 0x60300;
  DAT_8041ba04 = 0x60300;
  DAT_8041ba08 = 0x60300;
  DAT_8041ba0c = 0x60300;
  DAT_8041ba10 = 0x60300;
  DAT_8041ba14 = 0x60300;
  DAT_8041ba18 = 0x60104;
  DAT_8041ba1c = 0x60104;
  DAT_8041ba20 = 0x60104;
  DAT_8041ba24 = 0x60104;
  DAT_8041ba28 = 0x60104;
  DAT_8041ba2c = 0x60104;
  DAT_8041ba30 = 0x60104;
  DAT_8041ba34 = 0x60104;
  DAT_8041ba38 = 0x60103;
  DAT_8041ba3c = 0x60103;
  DAT_8041ba40 = 0x60103;
  DAT_8041ba44 = 0x60103;
  DAT_8041ba48 = 0x60103;
  DAT_8041ba4c = 0x60103;
  DAT_8041ba50 = 0x60103;
  DAT_8041ba54 = 0x60103;
  DAT_8041ba58 = 0x50200;
  DAT_8041ba5c = 0x50200;
  DAT_8041ba60 = 0x50200;
  DAT_8041ba64 = 0x50200;
  DAT_8041ba68 = 0x50200;
  DAT_8041ba6c = 0x50200;
  DAT_8041ba70 = 0x50200;
  DAT_8041ba74 = 0x50200;
  DAT_8041ba78 = 0x50200;
  DAT_8041ba7c = 0x50200;
  DAT_8041ba80 = 0x50200;
  DAT_8041ba84 = 0x50200;
  DAT_8041ba88 = 0x50200;
  DAT_8041ba8c = 0x50200;
  DAT_8041ba90 = 0x50200;
  DAT_8041ba94 = 0x50200;
  DAT_8041ba98 = 0x50102;
  DAT_8041ba9c = 0x50102;
  DAT_8041baa0 = 0x50102;
  DAT_8041baa4 = 0x50102;
  DAT_8041baa8 = 0x50102;
  DAT_8041baac = 0x50102;
  DAT_8041bab0 = 0x50102;
  DAT_8041bab4 = 0x50102;
  DAT_8041bab8 = 0x50102;
  DAT_8041babc = 0x50102;
  DAT_8041bac0 = 0x50102;
  DAT_8041bac4 = 0x50102;
  DAT_8041bac8 = 0x50102;
  DAT_8041bacc = 0x50102;
  DAT_8041bad0 = 0x50102;
  DAT_8041bad4 = 0x50102;
  DAT_8041bad8 = 0x40101;
  DAT_8041badc = 0x40101;
  DAT_8041bae0 = 0x40101;
  DAT_8041bae4 = 0x40101;
  DAT_8041bae8 = 0x40101;
  DAT_8041baec = 0x40101;
  DAT_8041baf0 = 0x40101;
  DAT_8041baf4 = 0x40101;
  DAT_8041baf8 = 0x40101;
  DAT_8041bafc = 0x40101;
  DAT_8041bb00 = 0x40101;
  DAT_8041bb04 = 0x40101;
  DAT_8041bb08 = 0x40101;
  DAT_8041bb0c = 0x40101;
  DAT_8041bb10 = 0x40101;
  DAT_8041bb14 = 0x40101;
  DAT_8041bb18 = 0x40101;
  DAT_8041bb1c = 0x40101;
  DAT_8041bb20 = 0x40101;
  DAT_8041bb24 = 0x40101;
  DAT_8041bb28 = 0x40101;
  DAT_8041bb2c = 0x40101;
  DAT_8041bb30 = 0x40101;
  DAT_8041bb34 = 0x40101;
  DAT_8041bb38 = 0x40101;
  DAT_8041bb3c = 0x40101;
  DAT_8041bb40 = 0x40101;
  DAT_8041bb44 = 0x40101;
  DAT_8041bb48 = 0x40101;
  DAT_8041bb4c = 0x40101;
  DAT_8041bb50 = 0x40101;
  DAT_8041bb54 = 0x40101;
  return;
}



// ==== 802852d8  zz_02852d8_ ====

void zz_02852d8_(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  
  puVar1 = &DAT_8041bb58;
  iVar3 = 8;
  do {
    *puVar1 = 2;
    puVar1[1] = 2;
    puVar1[2] = 2;
    puVar1[3] = 2;
    puVar1[4] = 2;
    puVar1[5] = 2;
    puVar1[6] = 2;
    puVar1[7] = 2;
    puVar1[8] = 2;
    puVar1[9] = 2;
    puVar1[10] = 2;
    puVar1[0xb] = 2;
    puVar1[0xc] = 2;
    puVar1[0xd] = 2;
    puVar1[0xe] = 2;
    puVar1[0xf] = 2;
    puVar1[0x10] = 2;
    puVar1[0x11] = 2;
    puVar1[0x12] = 2;
    puVar1[0x13] = 2;
    puVar1[0x14] = 2;
    puVar1[0x15] = 2;
    puVar1[0x16] = 2;
    puVar1[0x17] = 2;
    puVar1[0x18] = 2;
    puVar1[0x19] = 2;
    puVar1[0x1a] = 2;
    puVar1[0x1b] = 2;
    puVar1[0x1c] = 2;
    puVar1[0x1d] = 2;
    puVar1[0x1e] = 2;
    puVar1[0x1f] = 2;
    puVar1 = puVar1 + 0x20;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 8;
  do {
    *puVar1 = 0x12;
    puVar1[1] = 0x12;
    puVar1[2] = 0x12;
    puVar1[3] = 0x12;
    puVar1[4] = 0x12;
    puVar1[5] = 0x12;
    puVar1[6] = 0x12;
    puVar1[7] = 0x12;
    puVar1[8] = 0x12;
    puVar1[9] = 0x12;
    puVar1[10] = 0x12;
    puVar1[0xb] = 0x12;
    puVar1[0xc] = 0x12;
    puVar1[0xd] = 0x12;
    puVar1[0xe] = 0x12;
    puVar1[0xf] = 0x12;
    puVar1[0x10] = 0x12;
    puVar1[0x11] = 0x12;
    puVar1[0x12] = 0x12;
    puVar1[0x13] = 0x12;
    puVar1[0x14] = 0x12;
    puVar1[0x15] = 0x12;
    puVar1[0x16] = 0x12;
    puVar1[0x17] = 0x12;
    puVar1[0x18] = 0x12;
    puVar1[0x19] = 0x12;
    puVar1[0x1a] = 0x12;
    puVar1[0x1b] = 0x12;
    puVar1[0x1c] = 0x12;
    puVar1[0x1d] = 0x12;
    puVar1[0x1e] = 0x12;
    puVar1[0x1f] = 0x12;
    puVar1 = puVar1 + 0x20;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 8;
  do {
    *puVar1 = 0x22;
    puVar1[1] = 0x22;
    puVar1[2] = 0x22;
    puVar1[3] = 0x22;
    puVar1[4] = 0x22;
    puVar1[5] = 0x22;
    puVar1[6] = 0x22;
    puVar1[7] = 0x22;
    puVar1[8] = 0x22;
    puVar1[9] = 0x22;
    puVar1[10] = 0x22;
    puVar1[0xb] = 0x22;
    puVar1[0xc] = 0x22;
    puVar1[0xd] = 0x22;
    puVar1[0xe] = 0x22;
    puVar1[0xf] = 0x22;
    puVar1[0x10] = 0x22;
    puVar1[0x11] = 0x22;
    puVar1[0x12] = 0x22;
    puVar1[0x13] = 0x22;
    puVar1[0x14] = 0x22;
    puVar1[0x15] = 0x22;
    puVar1[0x16] = 0x22;
    puVar1[0x17] = 0x22;
    puVar1[0x18] = 0x22;
    puVar1[0x19] = 0x22;
    puVar1[0x1a] = 0x22;
    puVar1[0x1b] = 0x22;
    puVar1[0x1c] = 0x22;
    puVar1[0x1d] = 0x22;
    puVar1[0x1e] = 0x22;
    puVar1[0x1f] = 0x22;
    puVar1 = puVar1 + 0x20;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 4;
  do {
    *puVar1 = 0x33;
    puVar1[1] = 0x33;
    puVar1[2] = 0x33;
    puVar1[3] = 0x33;
    puVar1[4] = 0x33;
    puVar1[5] = 0x33;
    puVar1[6] = 0x33;
    puVar1[7] = 0x33;
    puVar1[8] = 0x33;
    puVar1[9] = 0x33;
    puVar1[10] = 0x33;
    puVar1[0xb] = 0x33;
    puVar1[0xc] = 0x33;
    puVar1[0xd] = 0x33;
    puVar1[0xe] = 0x33;
    puVar1[0xf] = 0x33;
    puVar1[0x10] = 0x33;
    puVar1[0x11] = 0x33;
    puVar1[0x12] = 0x33;
    puVar1[0x13] = 0x33;
    puVar1[0x14] = 0x33;
    puVar1[0x15] = 0x33;
    puVar1[0x16] = 0x33;
    puVar1[0x17] = 0x33;
    puVar1[0x18] = 0x33;
    puVar1[0x19] = 0x33;
    puVar1[0x1a] = 0x33;
    puVar1[0x1b] = 0x33;
    puVar1[0x1c] = 0x33;
    puVar1[0x1d] = 0x33;
    puVar1[0x1e] = 0x33;
    puVar1[0x1f] = 0x33;
    puVar1 = puVar1 + 0x20;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 2;
  do {
    puVar2 = puVar1;
    *puVar2 = 0x44;
    puVar2[1] = 0x44;
    puVar2[2] = 0x44;
    puVar2[3] = 0x44;
    puVar2[4] = 0x44;
    puVar2[5] = 0x44;
    puVar2[6] = 0x44;
    puVar2[7] = 0x44;
    puVar2[8] = 0x44;
    puVar2[9] = 0x44;
    puVar2[10] = 0x44;
    puVar2[0xb] = 0x44;
    puVar2[0xc] = 0x44;
    puVar2[0xd] = 0x44;
    puVar2[0xe] = 0x44;
    puVar2[0xf] = 0x44;
    puVar2[0x10] = 0x44;
    puVar2[0x11] = 0x44;
    puVar2[0x12] = 0x44;
    puVar2[0x13] = 0x44;
    puVar2[0x14] = 0x44;
    puVar2[0x15] = 0x44;
    puVar2[0x16] = 0x44;
    puVar2[0x17] = 0x44;
    puVar2[0x18] = 0x44;
    puVar2[0x19] = 0x44;
    puVar2[0x1a] = 0x44;
    puVar2[0x1b] = 0x44;
    puVar2[0x1c] = 0x44;
    puVar2[0x1d] = 0x44;
    puVar2[0x1e] = 0x44;
    puVar2[0x1f] = 0x44;
    iVar3 = iVar3 + -1;
    puVar1 = puVar2 + 0x20;
  } while (iVar3 != 0);
  puVar2[0x20] = 0x55;
  puVar2[0x21] = 0x55;
  puVar2[0x22] = 0x55;
  puVar2[0x23] = 0x55;
  puVar2[0x24] = 0x55;
  puVar2[0x25] = 0x55;
  puVar2[0x26] = 0x55;
  puVar2[0x27] = 0x55;
  puVar2[0x28] = 0x55;
  puVar2[0x29] = 0x55;
  puVar2[0x2a] = 0x55;
  puVar2[0x2b] = 0x55;
  puVar2[0x2c] = 0x55;
  puVar2[0x2d] = 0x55;
  puVar2[0x2e] = 0x55;
  puVar2[0x2f] = 0x55;
  puVar2[0x30] = 0x55;
  puVar2[0x31] = 0x55;
  puVar2[0x32] = 0x55;
  puVar2[0x33] = 0x55;
  puVar2[0x34] = 0x55;
  puVar2[0x35] = 0x55;
  puVar2[0x36] = 0x55;
  puVar2[0x37] = 0x55;
  puVar2[0x38] = 0x55;
  puVar2[0x39] = 0x55;
  puVar2[0x3a] = 0x55;
  puVar2[0x3b] = 0x55;
  puVar2[0x3c] = 0x55;
  puVar2[0x3d] = 0x55;
  puVar2[0x3e] = 0x55;
  puVar2[0x3f] = 0x55;
  puVar2[0x40] = 0x66;
  puVar2[0x41] = 0x66;
  puVar2[0x42] = 0x66;
  puVar2[0x43] = 0x66;
  puVar2[0x44] = 0x66;
  puVar2[0x45] = 0x66;
  puVar2[0x46] = 0x66;
  puVar2[0x47] = 0x66;
  puVar2[0x48] = 0x66;
  puVar2[0x49] = 0x66;
  puVar2[0x4a] = 0x66;
  puVar2[0x4b] = 0x66;
  puVar2[0x4c] = 0x66;
  puVar2[0x4d] = 0x66;
  puVar2[0x4e] = 0x66;
  puVar2[0x4f] = 0x66;
  puVar2[0x50] = 0x77;
  puVar2[0x51] = 0x77;
  puVar2[0x52] = 0x77;
  puVar2[0x53] = 0x77;
  puVar2[0x54] = 0x77;
  puVar2[0x55] = 0x77;
  puVar2[0x56] = 0x77;
  puVar2[0x57] = 0x77;
  puVar2[0x58] = 0x88;
  puVar2[0x59] = 0x88;
  puVar2[0x5a] = 0x88;
  puVar2[0x5b] = 0x88;
  puVar2[0x5c] = 0x99;
  puVar2[0x5d] = 0x99;
  puVar2[0x5e] = 0xaa;
  puVar2[0x5f] = 0xba;
  return;
}



// ==== 80285744  zz_0285744_ ====

void zz_0285744_(void)

{
  undefined1 *puVar1;
  undefined1 *puVar2;
  int iVar3;
  
  puVar1 = &DAT_8041bf58;
  iVar3 = 8;
  do {
    *puVar1 = 0x12;
    puVar1[1] = 0x12;
    puVar1[2] = 0x12;
    puVar1[3] = 0x12;
    puVar1[4] = 0x12;
    puVar1[5] = 0x12;
    puVar1[6] = 0x12;
    puVar1[7] = 0x12;
    puVar1[8] = 0x12;
    puVar1[9] = 0x12;
    puVar1[10] = 0x12;
    puVar1[0xb] = 0x12;
    puVar1[0xc] = 0x12;
    puVar1[0xd] = 0x12;
    puVar1[0xe] = 0x12;
    puVar1[0xf] = 0x12;
    puVar1[0x10] = 0x12;
    puVar1[0x11] = 0x12;
    puVar1[0x12] = 0x12;
    puVar1[0x13] = 0x12;
    puVar1[0x14] = 0x12;
    puVar1[0x15] = 0x12;
    puVar1[0x16] = 0x12;
    puVar1[0x17] = 0x12;
    puVar1[0x18] = 0x12;
    puVar1[0x19] = 0x12;
    puVar1[0x1a] = 0x12;
    puVar1[0x1b] = 0x12;
    puVar1[0x1c] = 0x12;
    puVar1[0x1d] = 0x12;
    puVar1[0x1e] = 0x12;
    puVar1[0x1f] = 0x12;
    puVar1 = puVar1 + 0x20;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 8;
  do {
    *puVar1 = 0x22;
    puVar1[1] = 0x22;
    puVar1[2] = 0x22;
    puVar1[3] = 0x22;
    puVar1[4] = 0x22;
    puVar1[5] = 0x22;
    puVar1[6] = 0x22;
    puVar1[7] = 0x22;
    puVar1[8] = 0x22;
    puVar1[9] = 0x22;
    puVar1[10] = 0x22;
    puVar1[0xb] = 0x22;
    puVar1[0xc] = 0x22;
    puVar1[0xd] = 0x22;
    puVar1[0xe] = 0x22;
    puVar1[0xf] = 0x22;
    puVar1[0x10] = 0x22;
    puVar1[0x11] = 0x22;
    puVar1[0x12] = 0x22;
    puVar1[0x13] = 0x22;
    puVar1[0x14] = 0x22;
    puVar1[0x15] = 0x22;
    puVar1[0x16] = 0x22;
    puVar1[0x17] = 0x22;
    puVar1[0x18] = 0x22;
    puVar1[0x19] = 0x22;
    puVar1[0x1a] = 0x22;
    puVar1[0x1b] = 0x22;
    puVar1[0x1c] = 0x22;
    puVar1[0x1d] = 0x22;
    puVar1[0x1e] = 0x22;
    puVar1[0x1f] = 0x22;
    puVar1 = puVar1 + 0x20;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 4;
  do {
    *puVar1 = 3;
    puVar1[1] = 3;
    puVar1[2] = 3;
    puVar1[3] = 3;
    puVar1[4] = 3;
    puVar1[5] = 3;
    puVar1[6] = 3;
    puVar1[7] = 3;
    puVar1[8] = 3;
    puVar1[9] = 3;
    puVar1[10] = 3;
    puVar1[0xb] = 3;
    puVar1[0xc] = 3;
    puVar1[0xd] = 3;
    puVar1[0xe] = 3;
    puVar1[0xf] = 3;
    puVar1[0x10] = 3;
    puVar1[0x11] = 3;
    puVar1[0x12] = 3;
    puVar1[0x13] = 3;
    puVar1[0x14] = 3;
    puVar1[0x15] = 3;
    puVar1[0x16] = 3;
    puVar1[0x17] = 3;
    puVar1[0x18] = 3;
    puVar1[0x19] = 3;
    puVar1[0x1a] = 3;
    puVar1[0x1b] = 3;
    puVar1[0x1c] = 3;
    puVar1[0x1d] = 3;
    puVar1[0x1e] = 3;
    puVar1[0x1f] = 3;
    puVar1 = puVar1 + 0x20;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 4;
  do {
    *puVar1 = 0x33;
    puVar1[1] = 0x33;
    puVar1[2] = 0x33;
    puVar1[3] = 0x33;
    puVar1[4] = 0x33;
    puVar1[5] = 0x33;
    puVar1[6] = 0x33;
    puVar1[7] = 0x33;
    puVar1[8] = 0x33;
    puVar1[9] = 0x33;
    puVar1[10] = 0x33;
    puVar1[0xb] = 0x33;
    puVar1[0xc] = 0x33;
    puVar1[0xd] = 0x33;
    puVar1[0xe] = 0x33;
    puVar1[0xf] = 0x33;
    puVar1[0x10] = 0x33;
    puVar1[0x11] = 0x33;
    puVar1[0x12] = 0x33;
    puVar1[0x13] = 0x33;
    puVar1[0x14] = 0x33;
    puVar1[0x15] = 0x33;
    puVar1[0x16] = 0x33;
    puVar1[0x17] = 0x33;
    puVar1[0x18] = 0x33;
    puVar1[0x19] = 0x33;
    puVar1[0x1a] = 0x33;
    puVar1[0x1b] = 0x33;
    puVar1[0x1c] = 0x33;
    puVar1[0x1d] = 0x33;
    puVar1[0x1e] = 0x33;
    puVar1[0x1f] = 0x33;
    puVar1 = puVar1 + 0x20;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 4;
  do {
    *puVar1 = 0x43;
    puVar1[1] = 0x43;
    puVar1[2] = 0x43;
    puVar1[3] = 0x43;
    puVar1[4] = 0x43;
    puVar1[5] = 0x43;
    puVar1[6] = 0x43;
    puVar1[7] = 0x43;
    puVar1[8] = 0x43;
    puVar1[9] = 0x43;
    puVar1[10] = 0x43;
    puVar1[0xb] = 0x43;
    puVar1[0xc] = 0x43;
    puVar1[0xd] = 0x43;
    puVar1[0xe] = 0x43;
    puVar1[0xf] = 0x43;
    puVar1[0x10] = 0x43;
    puVar1[0x11] = 0x43;
    puVar1[0x12] = 0x43;
    puVar1[0x13] = 0x43;
    puVar1[0x14] = 0x43;
    puVar1[0x15] = 0x43;
    puVar1[0x16] = 0x43;
    puVar1[0x17] = 0x43;
    puVar1[0x18] = 0x43;
    puVar1[0x19] = 0x43;
    puVar1[0x1a] = 0x43;
    puVar1[0x1b] = 0x43;
    puVar1[0x1c] = 0x43;
    puVar1[0x1d] = 0x43;
    puVar1[0x1e] = 0x43;
    puVar1[0x1f] = 0x43;
    puVar1 = puVar1 + 0x20;
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  iVar3 = 2;
  do {
    puVar2 = puVar1;
    *puVar2 = 0x54;
    puVar2[1] = 0x54;
    puVar2[2] = 0x54;
    puVar2[3] = 0x54;
    puVar2[4] = 0x54;
    puVar2[5] = 0x54;
    puVar2[6] = 0x54;
    puVar2[7] = 0x54;
    puVar2[8] = 0x54;
    puVar2[9] = 0x54;
    puVar2[10] = 0x54;
    puVar2[0xb] = 0x54;
    puVar2[0xc] = 0x54;
    puVar2[0xd] = 0x54;
    puVar2[0xe] = 0x54;
    puVar2[0xf] = 0x54;
    puVar2[0x10] = 0x54;
    puVar2[0x11] = 0x54;
    puVar2[0x12] = 0x54;
    puVar2[0x13] = 0x54;
    puVar2[0x14] = 0x54;
    puVar2[0x15] = 0x54;
    puVar2[0x16] = 0x54;
    puVar2[0x17] = 0x54;
    puVar2[0x18] = 0x54;
    puVar2[0x19] = 0x54;
    puVar2[0x1a] = 0x54;
    puVar2[0x1b] = 0x54;
    puVar2[0x1c] = 0x54;
    puVar2[0x1d] = 0x54;
    puVar2[0x1e] = 0x54;
    puVar2[0x1f] = 0x54;
    iVar3 = iVar3 + -1;
    puVar1 = puVar2 + 0x20;
  } while (iVar3 != 0);
  puVar2[0x20] = 0x65;
  puVar2[0x21] = 0x65;
  puVar2[0x22] = 0x65;
  puVar2[0x23] = 0x65;
  puVar2[0x24] = 0x65;
  puVar2[0x25] = 0x65;
  puVar2[0x26] = 0x65;
  puVar2[0x27] = 0x65;
  puVar2[0x28] = 0x65;
  puVar2[0x29] = 0x65;
  puVar2[0x2a] = 0x65;
  puVar2[0x2b] = 0x65;
  puVar2[0x2c] = 0x65;
  puVar2[0x2d] = 0x65;
  puVar2[0x2e] = 0x65;
  puVar2[0x2f] = 0x65;
  puVar2[0x30] = 0x65;
  puVar2[0x31] = 0x65;
  puVar2[0x32] = 0x65;
  puVar2[0x33] = 0x65;
  puVar2[0x34] = 0x65;
  puVar2[0x35] = 0x65;
  puVar2[0x36] = 0x65;
  puVar2[0x37] = 0x65;
  puVar2[0x38] = 0x65;
  puVar2[0x39] = 0x65;
  puVar2[0x3a] = 0x65;
  puVar2[0x3b] = 0x65;
  puVar2[0x3c] = 0x65;
  puVar2[0x3d] = 0x65;
  puVar2[0x3e] = 0x65;
  puVar2[0x3f] = 0x65;
  puVar2[0x40] = 0x76;
  puVar2[0x41] = 0x76;
  puVar2[0x42] = 0x76;
  puVar2[0x43] = 0x76;
  puVar2[0x44] = 0x76;
  puVar2[0x45] = 0x76;
  puVar2[0x46] = 0x76;
  puVar2[0x47] = 0x76;
  puVar2[0x48] = 0x76;
  puVar2[0x49] = 0x76;
  puVar2[0x4a] = 0x76;
  puVar2[0x4b] = 0x76;
  puVar2[0x4c] = 0x76;
  puVar2[0x4d] = 0x76;
  puVar2[0x4e] = 0x76;
  puVar2[0x4f] = 0x76;
  puVar2[0x50] = 0x87;
  puVar2[0x51] = 0x87;
  puVar2[0x52] = 0x87;
  puVar2[0x53] = 0x87;
  puVar2[0x54] = 0x87;
  puVar2[0x55] = 0x87;
  puVar2[0x56] = 0x87;
  puVar2[0x57] = 0x87;
  puVar2[0x58] = 0x98;
  puVar2[0x59] = 0x98;
  puVar2[0x5a] = 0x98;
  puVar2[0x5b] = 0x98;
  puVar2[0x5c] = 0xa9;
  puVar2[0x5d] = 0xa9;
  puVar2[0x5e] = 0xb9;
  puVar2[0x5f] = 0xb9;
  return;
}



// ==== 80285c4c  zz_0285c4c_ ====

void zz_0285c4c_(void)

{
  DAT_8041c358 = 2;
  DAT_8041c359 = 2;
  DAT_8041c35a = 2;
  DAT_8041c35b = 2;
  DAT_8041c35c = 2;
  DAT_8041c35d = 2;
  DAT_8041c35e = 2;
  DAT_8041c35f = 2;
  DAT_8041c360 = 2;
  DAT_8041c361 = 2;
  DAT_8041c362 = 2;
  DAT_8041c363 = 2;
  DAT_8041c364 = 2;
  DAT_8041c365 = 2;
  DAT_8041c366 = 2;
  DAT_8041c367 = 2;
  DAT_8041c368 = 2;
  DAT_8041c369 = 2;
  DAT_8041c36a = 2;
  DAT_8041c36b = 2;
  DAT_8041c36c = 2;
  DAT_8041c36d = 2;
  DAT_8041c36e = 2;
  DAT_8041c36f = 2;
  DAT_8041c370 = 2;
  DAT_8041c371 = 2;
  DAT_8041c372 = 2;
  DAT_8041c373 = 2;
  DAT_8041c374 = 2;
  DAT_8041c375 = 2;
  DAT_8041c376 = 2;
  DAT_8041c377 = 2;
  DAT_8041c378 = 0x12;
  DAT_8041c379 = 0x12;
  DAT_8041c37a = 0x12;
  DAT_8041c37b = 0x12;
  DAT_8041c37c = 0x12;
  DAT_8041c37d = 0x12;
  DAT_8041c37e = 0x12;
  DAT_8041c37f = 0x12;
  DAT_8041c380 = 0x12;
  DAT_8041c381 = 0x12;
  DAT_8041c382 = 0x12;
  DAT_8041c383 = 0x12;
  DAT_8041c384 = 0x12;
  DAT_8041c385 = 0x12;
  DAT_8041c386 = 0x12;
  DAT_8041c387 = 0x12;
  DAT_8041c388 = 0x12;
  DAT_8041c389 = 0x12;
  DAT_8041c38a = 0x12;
  DAT_8041c38b = 0x12;
  DAT_8041c38c = 0x12;
  DAT_8041c38d = 0x12;
  DAT_8041c38e = 0x12;
  DAT_8041c38f = 0x12;
  DAT_8041c390 = 0x12;
  DAT_8041c391 = 0x12;
  DAT_8041c392 = 0x12;
  DAT_8041c393 = 0x12;
  DAT_8041c394 = 0x12;
  DAT_8041c395 = 0x12;
  DAT_8041c396 = 0x12;
  DAT_8041c397 = 0x12;
  DAT_8041c398 = 0x22;
  DAT_8041c399 = 0x22;
  DAT_8041c39a = 0x22;
  DAT_8041c39b = 0x22;
  DAT_8041c39c = 0x22;
  DAT_8041c39d = 0x22;
  DAT_8041c39e = 0x22;
  DAT_8041c39f = 0x22;
  DAT_8041c3a0 = 0x22;
  DAT_8041c3a1 = 0x22;
  DAT_8041c3a2 = 0x22;
  DAT_8041c3a3 = 0x22;
  DAT_8041c3a4 = 0x22;
  DAT_8041c3a5 = 0x22;
  DAT_8041c3a6 = 0x22;
  DAT_8041c3a7 = 0x22;
  DAT_8041c3a8 = 0x22;
  DAT_8041c3a9 = 0x22;
  DAT_8041c3aa = 0x22;
  DAT_8041c3ab = 0x22;
  DAT_8041c3ac = 0x22;
  DAT_8041c3ad = 0x22;
  DAT_8041c3ae = 0x22;
  DAT_8041c3af = 0x22;
  DAT_8041c3b0 = 0x22;
  DAT_8041c3b1 = 0x22;
  DAT_8041c3b2 = 0x22;
  DAT_8041c3b3 = 0x22;
  DAT_8041c3b4 = 0x22;
  DAT_8041c3b5 = 0x22;
  DAT_8041c3b6 = 0x22;
  DAT_8041c3b7 = 0x22;
  DAT_8041c3b8 = 0x33;
  DAT_8041c3b9 = 0x33;
  DAT_8041c3ba = 0x33;
  DAT_8041c3bb = 0x33;
  DAT_8041c3bc = 0x33;
  DAT_8041c3bd = 0x33;
  DAT_8041c3be = 0x33;
  DAT_8041c3bf = 0x33;
  DAT_8041c3c0 = 0x33;
  DAT_8041c3c1 = 0x33;
  DAT_8041c3c2 = 0x33;
  DAT_8041c3c3 = 0x33;
  DAT_8041c3c4 = 0x33;
  DAT_8041c3c5 = 0x33;
  DAT_8041c3c6 = 0x33;
  DAT_8041c3c7 = 0x33;
  DAT_8041c3c8 = 0x44;
  DAT_8041c3c9 = 0x44;
  DAT_8041c3ca = 0x44;
  DAT_8041c3cb = 0x44;
  DAT_8041c3cc = 0x44;
  DAT_8041c3cd = 0x44;
  DAT_8041c3ce = 0x44;
  DAT_8041c3cf = 0x44;
  DAT_8041c3d0 = 0x55;
  DAT_8041c3d1 = 0x55;
  DAT_8041c3d2 = 0x55;
  DAT_8041c3d3 = 0x55;
  DAT_8041c3d4 = 0x66;
  DAT_8041c3d5 = 0x66;
  DAT_8041c3d6 = 0x77;
  DAT_8041c3d7 = 0x88;
  return;
}



// ==== 80285ec0  zz_0285ec0_ ====

void zz_0285ec0_(void)

{
  DAT_8041c3d8 = 0x12;
  DAT_8041c3d9 = 0x12;
  DAT_8041c3da = 0x12;
  DAT_8041c3db = 0x12;
  DAT_8041c3dc = 0x12;
  DAT_8041c3dd = 0x12;
  DAT_8041c3de = 0x12;
  DAT_8041c3df = 0x12;
  DAT_8041c3e0 = 0x12;
  DAT_8041c3e1 = 0x12;
  DAT_8041c3e2 = 0x12;
  DAT_8041c3e3 = 0x12;
  DAT_8041c3e4 = 0x12;
  DAT_8041c3e5 = 0x12;
  DAT_8041c3e6 = 0x12;
  DAT_8041c3e7 = 0x12;
  DAT_8041c3e8 = 0x12;
  DAT_8041c3e9 = 0x12;
  DAT_8041c3ea = 0x12;
  DAT_8041c3eb = 0x12;
  DAT_8041c3ec = 0x12;
  DAT_8041c3ed = 0x12;
  DAT_8041c3ee = 0x12;
  DAT_8041c3ef = 0x12;
  DAT_8041c3f0 = 0x12;
  DAT_8041c3f1 = 0x12;
  DAT_8041c3f2 = 0x12;
  DAT_8041c3f3 = 0x12;
  DAT_8041c3f4 = 0x12;
  DAT_8041c3f5 = 0x12;
  DAT_8041c3f6 = 0x12;
  DAT_8041c3f7 = 0x12;
  DAT_8041c3f8 = 0x22;
  DAT_8041c3f9 = 0x22;
  DAT_8041c3fa = 0x22;
  DAT_8041c3fb = 0x22;
  DAT_8041c3fc = 0x22;
  DAT_8041c3fd = 0x22;
  DAT_8041c3fe = 0x22;
  DAT_8041c3ff = 0x22;
  DAT_8041c400 = 0x22;
  DAT_8041c401 = 0x22;
  DAT_8041c402 = 0x22;
  DAT_8041c403 = 0x22;
  DAT_8041c404 = 0x22;
  DAT_8041c405 = 0x22;
  DAT_8041c406 = 0x22;
  DAT_8041c407 = 0x22;
  DAT_8041c408 = 0x22;
  DAT_8041c409 = 0x22;
  DAT_8041c40a = 0x22;
  DAT_8041c40b = 0x22;
  DAT_8041c40c = 0x22;
  DAT_8041c40d = 0x22;
  DAT_8041c40e = 0x22;
  DAT_8041c40f = 0x22;
  DAT_8041c410 = 0x22;
  DAT_8041c411 = 0x22;
  DAT_8041c412 = 0x22;
  DAT_8041c413 = 0x22;
  DAT_8041c414 = 0x22;
  DAT_8041c415 = 0x22;
  DAT_8041c416 = 0x22;
  DAT_8041c417 = 0x22;
  DAT_8041c418 = 3;
  DAT_8041c419 = 3;
  DAT_8041c41a = 3;
  DAT_8041c41b = 3;
  DAT_8041c41c = 3;
  DAT_8041c41d = 3;
  DAT_8041c41e = 3;
  DAT_8041c41f = 3;
  DAT_8041c420 = 3;
  DAT_8041c421 = 3;
  DAT_8041c422 = 3;
  DAT_8041c423 = 3;
  DAT_8041c424 = 3;
  DAT_8041c425 = 3;
  DAT_8041c426 = 3;
  DAT_8041c427 = 3;
  DAT_8041c428 = 0x33;
  DAT_8041c429 = 0x33;
  DAT_8041c42a = 0x33;
  DAT_8041c42b = 0x33;
  DAT_8041c42c = 0x33;
  DAT_8041c42d = 0x33;
  DAT_8041c42e = 0x33;
  DAT_8041c42f = 0x33;
  DAT_8041c430 = 0x33;
  DAT_8041c431 = 0x33;
  DAT_8041c432 = 0x33;
  DAT_8041c433 = 0x33;
  DAT_8041c434 = 0x33;
  DAT_8041c435 = 0x33;
  DAT_8041c436 = 0x33;
  DAT_8041c437 = 0x33;
  DAT_8041c438 = 0x43;
  DAT_8041c439 = 0x43;
  DAT_8041c43a = 0x43;
  DAT_8041c43b = 0x43;
  DAT_8041c43c = 0x43;
  DAT_8041c43d = 0x43;
  DAT_8041c43e = 0x43;
  DAT_8041c43f = 0x43;
  DAT_8041c440 = 0x43;
  DAT_8041c441 = 0x43;
  DAT_8041c442 = 0x43;
  DAT_8041c443 = 0x43;
  DAT_8041c444 = 0x43;
  DAT_8041c445 = 0x43;
  DAT_8041c446 = 0x43;
  DAT_8041c447 = 0x43;
  DAT_8041c448 = 0x54;
  DAT_8041c449 = 0x54;
  DAT_8041c44a = 0x54;
  DAT_8041c44b = 0x54;
  DAT_8041c44c = 0x54;
  DAT_8041c44d = 0x54;
  DAT_8041c44e = 0x54;
  DAT_8041c44f = 0x54;
  DAT_8041c450 = 0x65;
  DAT_8041c451 = 0x65;
  DAT_8041c452 = 0x65;
  DAT_8041c453 = 0x65;
  DAT_8041c454 = 0x76;
  DAT_8041c455 = 0x76;
  DAT_8041c456 = 0x87;
  DAT_8041c457 = 0x87;
  return;
}



// ==== 80286144  zz_0286144_ ====

undefined2 * zz_0286144_(undefined2 *param_1)

{
  undefined2 *puVar1;
  int iVar2;
  
  *param_1 = 0xa207;
  param_1[1] = 0xa207;
  param_1[2] = 0xa207;
  param_1[3] = 0xa207;
  param_1[4] = 0x9207;
  param_1[5] = 0x9207;
  param_1[6] = 0x9207;
  param_1[7] = 0x9207;
  param_1[8] = 0x8a07;
  param_1[9] = 0x8a07;
  param_1[10] = 0x8a07;
  param_1[0xb] = 0x8a07;
  param_1[0xc] = 0x8607;
  param_1[0xd] = 0x8607;
  param_1[0xe] = 0x8607;
  param_1[0xf] = 0x8607;
  param_1[0x10] = 0x6107;
  param_1[0x11] = 0x6107;
  param_1[0x12] = 0x6107;
  param_1[0x13] = 0x6107;
  param_1[0x14] = 0x5107;
  param_1[0x15] = 0x5107;
  param_1[0x16] = 0x5107;
  param_1[0x17] = 0x5107;
  param_1[0x18] = 0x4907;
  param_1[0x19] = 0x4907;
  param_1[0x1a] = 0x4907;
  param_1[0x1b] = 0x4907;
  param_1[0x1c] = 0x4507;
  param_1[0x1d] = 0x4507;
  param_1[0x1e] = 0x4507;
  param_1[0x1f] = 0x4507;
  param_1[0x20] = 0xff06;
  param_1[0x21] = 0xff06;
  param_1[0x22] = 0xff06;
  param_1[0x23] = 0xff06;
  param_1[0x24] = 0xff06;
  param_1[0x25] = 0xff06;
  param_1[0x26] = 0xff06;
  param_1[0x27] = 0xff06;
  param_1[0x28] = 0xc306;
  param_1[0x29] = 0xc306;
  param_1[0x2a] = 0xc306;
  param_1[0x2b] = 0xc306;
  param_1[0x2c] = 0xc306;
  param_1[0x2d] = 0xc306;
  param_1[0x2e] = 0xc306;
  param_1[0x2f] = 0xc306;
  param_1[0x30] = 0x2406;
  param_1[0x31] = 0x2406;
  param_1[0x32] = 0x2406;
  param_1[0x33] = 0x2406;
  param_1[0x34] = 0x2406;
  param_1[0x35] = 0x2406;
  param_1[0x36] = 0x2406;
  param_1[0x37] = 0x2406;
  param_1[0x38] = 0x1806;
  param_1[0x39] = 0x1806;
  param_1[0x3a] = 0x1806;
  param_1[0x3b] = 0x1806;
  param_1[0x3c] = 0x1806;
  param_1[0x3d] = 0x1806;
  param_1[0x3e] = 0x1806;
  param_1[0x3f] = 0x1806;
  param_1[0x40] = 0xbe05;
  param_1[0x41] = 0xbe05;
  param_1[0x42] = 0xbe05;
  param_1[0x43] = 0xbe05;
  param_1[0x44] = 0xbe05;
  param_1[0x45] = 0xbe05;
  param_1[0x46] = 0xbe05;
  param_1[0x47] = 0xbe05;
  param_1[0x48] = 0xbe05;
  param_1[0x49] = 0xbe05;
  param_1[0x4a] = 0xbe05;
  param_1[0x4b] = 0xbe05;
  param_1[0x4c] = 0xbe05;
  param_1[0x4d] = 0xbe05;
  param_1[0x4e] = 0xbe05;
  param_1[0x4f] = 0xbe05;
  param_1[0x50] = 0x8205;
  param_1[0x51] = 0x8205;
  param_1[0x52] = 0x8205;
  param_1[0x53] = 0x8205;
  param_1[0x54] = 0x8205;
  param_1[0x55] = 0x8205;
  param_1[0x56] = 0x8205;
  param_1[0x57] = 0x8205;
  param_1[0x58] = 0x8205;
  param_1[0x59] = 0x8205;
  param_1[0x5a] = 0x8205;
  param_1[0x5b] = 0x8205;
  param_1[0x5c] = 0x8205;
  param_1[0x5d] = 0x8205;
  param_1[0x5e] = 0x8205;
  param_1[0x5f] = 0x8205;
  param_1[0x60] = 0x7d05;
  param_1[0x61] = 0x7d05;
  param_1[0x62] = 0x7d05;
  param_1[99] = 0x7d05;
  param_1[100] = 0x7d05;
  param_1[0x65] = 0x7d05;
  param_1[0x66] = 0x7d05;
  param_1[0x67] = 0x7d05;
  param_1[0x68] = 0x7d05;
  param_1[0x69] = 0x7d05;
  param_1[0x6a] = 0x7d05;
  param_1[0x6b] = 0x7d05;
  param_1[0x6c] = 0x7d05;
  param_1[0x6d] = 0x7d05;
  param_1[0x6e] = 0x7d05;
  param_1[0x6f] = 0x7d05;
  param_1[0x70] = 0x4105;
  param_1[0x71] = 0x4105;
  param_1[0x72] = 0x4105;
  param_1[0x73] = 0x4105;
  param_1[0x74] = 0x4105;
  param_1[0x75] = 0x4105;
  param_1[0x76] = 0x4105;
  param_1[0x77] = 0x4105;
  param_1[0x78] = 0x4105;
  param_1[0x79] = 0x4105;
  param_1[0x7a] = 0x4105;
  param_1[0x7b] = 0x4105;
  param_1[0x7c] = 0x4105;
  param_1[0x7d] = 0x4105;
  param_1[0x7e] = 0x4105;
  param_1[0x7f] = 0x4105;
  param_1[0x80] = 0x3805;
  param_1[0x81] = 0x3805;
  param_1[0x82] = 0x3805;
  param_1[0x83] = 0x3805;
  param_1[0x84] = 0x3805;
  param_1[0x85] = 0x3805;
  param_1[0x86] = 0x3805;
  param_1[0x87] = 0x3805;
  param_1[0x88] = 0x3805;
  param_1[0x89] = 0x3805;
  param_1[0x8a] = 0x3805;
  param_1[0x8b] = 0x3805;
  param_1[0x8c] = 0x3805;
  param_1[0x8d] = 0x3805;
  param_1[0x8e] = 0x3805;
  param_1[0x8f] = 0x3805;
  param_1[0x90] = 0x3405;
  param_1[0x91] = 0x3405;
  param_1[0x92] = 0x3405;
  param_1[0x93] = 0x3405;
  param_1[0x94] = 0x3405;
  param_1[0x95] = 0x3405;
  param_1[0x96] = 0x3405;
  param_1[0x97] = 0x3405;
  param_1[0x98] = 0x3405;
  param_1[0x99] = 0x3405;
  param_1[0x9a] = 0x3405;
  param_1[0x9b] = 0x3405;
  param_1[0x9c] = 0x3405;
  param_1[0x9d] = 0x3405;
  param_1[0x9e] = 0x3405;
  param_1[0x9f] = 0x3405;
  param_1[0xa0] = 0x2c05;
  param_1[0xa1] = 0x2c05;
  param_1[0xa2] = 0x2c05;
  param_1[0xa3] = 0x2c05;
  param_1[0xa4] = 0x2c05;
  param_1[0xa5] = 0x2c05;
  param_1[0xa6] = 0x2c05;
  param_1[0xa7] = 0x2c05;
  param_1[0xa8] = 0x2c05;
  param_1[0xa9] = 0x2c05;
  param_1[0xaa] = 0x2c05;
  param_1[0xab] = 0x2c05;
  param_1[0xac] = 0x2c05;
  param_1[0xad] = 0x2c05;
  param_1[0xae] = 0x2c05;
  param_1[0xaf] = 0x2c05;
  param_1[0xb0] = 0x1c05;
  param_1[0xb1] = 0x1c05;
  param_1[0xb2] = 0x1c05;
  param_1[0xb3] = 0x1c05;
  param_1[0xb4] = 0x1c05;
  param_1[0xb5] = 0x1c05;
  param_1[0xb6] = 0x1c05;
  param_1[0xb7] = 0x1c05;
  param_1[0xb8] = 0x1c05;
  param_1[0xb9] = 0x1c05;
  param_1[0xba] = 0x1c05;
  param_1[0xbb] = 0x1c05;
  param_1[0xbc] = 0x1c05;
  param_1[0xbd] = 0x1c05;
  param_1[0xbe] = 0x1c05;
  param_1[0xbf] = 0x1c05;
  param_1[0xc0] = 0x2805;
  param_1[0xc1] = 0x2805;
  param_1[0xc2] = 0x2805;
  param_1[0xc3] = 0x2805;
  param_1[0xc4] = 0x2805;
  param_1[0xc5] = 0x2805;
  param_1[0xc6] = 0x2805;
  param_1[199] = 0x2805;
  param_1[200] = 0x2805;
  param_1[0xc9] = 0x2805;
  param_1[0xca] = 0x2805;
  param_1[0xcb] = 0x2805;
  param_1[0xcc] = 0x2805;
  param_1[0xcd] = 0x2805;
  param_1[0xce] = 0x2805;
  param_1[0xcf] = 0x2805;
  param_1[0xd0] = 0x1405;
  param_1[0xd1] = 0x1405;
  param_1[0xd2] = 0x1405;
  param_1[0xd3] = 0x1405;
  param_1[0xd4] = 0x1405;
  param_1[0xd5] = 0x1405;
  param_1[0xd6] = 0x1405;
  param_1[0xd7] = 0x1405;
  param_1[0xd8] = 0x1405;
  param_1[0xd9] = 0x1405;
  param_1[0xda] = 0x1405;
  param_1[0xdb] = 0x1405;
  param_1[0xdc] = 0x1405;
  param_1[0xdd] = 0x1405;
  param_1[0xde] = 0x1405;
  param_1[0xdf] = 0x1405;
  param_1[0xe0] = 0x3005;
  param_1[0xe1] = 0x3005;
  param_1[0xe2] = 0x3005;
  param_1[0xe3] = 0x3005;
  param_1[0xe4] = 0x3005;
  param_1[0xe5] = 0x3005;
  param_1[0xe6] = 0x3005;
  param_1[0xe7] = 0x3005;
  param_1[0xe8] = 0x3005;
  param_1[0xe9] = 0x3005;
  param_1[0xea] = 0x3005;
  param_1[0xeb] = 0x3005;
  param_1[0xec] = 0x3005;
  param_1[0xed] = 0x3005;
  param_1[0xee] = 0x3005;
  param_1[0xef] = 0x3005;
  param_1[0xf0] = 0xc05;
  param_1[0xf1] = 0xc05;
  param_1[0xf2] = 0xc05;
  param_1[0xf3] = 0xc05;
  param_1[0xf4] = 0xc05;
  param_1[0xf5] = 0xc05;
  param_1[0xf6] = 0xc05;
  param_1[0xf7] = 0xc05;
  param_1[0xf8] = 0xc05;
  param_1[0xf9] = 0xc05;
  param_1[0xfa] = 0xc05;
  param_1[0xfb] = 0xc05;
  param_1[0xfc] = 0xc05;
  param_1[0xfd] = 0xc05;
  param_1[0xfe] = 0xc05;
  param_1[0xff] = 0xc05;
  param_1[0x100] = 0x2004;
  param_1[0x101] = 0x2004;
  param_1[0x102] = 0x2004;
  param_1[0x103] = 0x2004;
  param_1[0x104] = 0x2004;
  param_1[0x105] = 0x2004;
  param_1[0x106] = 0x2004;
  param_1[0x107] = 0x2004;
  param_1[0x108] = 0x2004;
  param_1[0x109] = 0x2004;
  param_1[0x10a] = 0x2004;
  param_1[0x10b] = 0x2004;
  param_1[0x10c] = 0x2004;
  param_1[0x10d] = 0x2004;
  param_1[0x10e] = 0x2004;
  param_1[0x10f] = 0x2004;
  param_1[0x110] = 0x2004;
  param_1[0x111] = 0x2004;
  param_1[0x112] = 0x2004;
  param_1[0x113] = 0x2004;
  param_1[0x114] = 0x2004;
  param_1[0x115] = 0x2004;
  param_1[0x116] = 0x2004;
  param_1[0x117] = 0x2004;
  param_1[0x118] = 0x2004;
  param_1[0x119] = 0x2004;
  param_1[0x11a] = 0x2004;
  param_1[0x11b] = 0x2004;
  param_1[0x11c] = 0x2004;
  param_1[0x11d] = 0x2004;
  param_1[0x11e] = 0x2004;
  param_1[0x11f] = 0x2004;
  param_1[0x120] = 0x1004;
  param_1[0x121] = 0x1004;
  param_1[0x122] = 0x1004;
  param_1[0x123] = 0x1004;
  param_1[0x124] = 0x1004;
  param_1[0x125] = 0x1004;
  param_1[0x126] = 0x1004;
  param_1[0x127] = 0x1004;
  param_1[0x128] = 0x1004;
  param_1[0x129] = 0x1004;
  param_1[0x12a] = 0x1004;
  param_1[299] = 0x1004;
  param_1[300] = 0x1004;
  param_1[0x12d] = 0x1004;
  param_1[0x12e] = 0x1004;
  param_1[0x12f] = 0x1004;
  param_1[0x130] = 0x1004;
  param_1[0x131] = 0x1004;
  param_1[0x132] = 0x1004;
  param_1[0x133] = 0x1004;
  param_1[0x134] = 0x1004;
  param_1[0x135] = 0x1004;
  param_1[0x136] = 0x1004;
  param_1[0x137] = 0x1004;
  param_1[0x138] = 0x1004;
  param_1[0x139] = 0x1004;
  param_1[0x13a] = 0x1004;
  param_1[0x13b] = 0x1004;
  param_1[0x13c] = 0x1004;
  param_1[0x13d] = 0x1004;
  param_1[0x13e] = 0x1004;
  param_1[0x13f] = 0x1004;
  param_1[0x140] = 0x804;
  param_1[0x141] = 0x804;
  param_1[0x142] = 0x804;
  param_1[0x143] = 0x804;
  param_1[0x144] = 0x804;
  param_1[0x145] = 0x804;
  param_1[0x146] = 0x804;
  param_1[0x147] = 0x804;
  param_1[0x148] = 0x804;
  param_1[0x149] = 0x804;
  param_1[0x14a] = 0x804;
  param_1[0x14b] = 0x804;
  param_1[0x14c] = 0x804;
  param_1[0x14d] = 0x804;
  param_1[0x14e] = 0x804;
  param_1[0x14f] = 0x804;
  param_1[0x150] = 0x804;
  param_1[0x151] = 0x804;
  param_1[0x152] = 0x804;
  param_1[0x153] = 0x804;
  param_1[0x154] = 0x804;
  param_1[0x155] = 0x804;
  param_1[0x156] = 0x804;
  param_1[0x157] = 0x804;
  param_1[0x158] = 0x804;
  param_1[0x159] = 0x804;
  param_1[0x15a] = 0x804;
  param_1[0x15b] = 0x804;
  param_1[0x15c] = 0x804;
  param_1[0x15d] = 0x804;
  param_1[0x15e] = 0x804;
  param_1[0x15f] = 0x804;
  param_1[0x160] = 0x404;
  param_1[0x161] = 0x404;
  param_1[0x162] = 0x404;
  param_1[0x163] = 0x404;
  param_1[0x164] = 0x404;
  param_1[0x165] = 0x404;
  param_1[0x166] = 0x404;
  param_1[0x167] = 0x404;
  param_1[0x168] = 0x404;
  param_1[0x169] = 0x404;
  param_1[0x16a] = 0x404;
  param_1[0x16b] = 0x404;
  param_1[0x16c] = 0x404;
  param_1[0x16d] = 0x404;
  param_1[0x16e] = 0x404;
  param_1[0x16f] = 0x404;
  param_1[0x170] = 0x404;
  param_1[0x171] = 0x404;
  param_1[0x172] = 0x404;
  param_1[0x173] = 0x404;
  param_1[0x174] = 0x404;
  param_1[0x175] = 0x404;
  param_1[0x176] = 0x404;
  param_1[0x177] = 0x404;
  param_1[0x178] = 0x404;
  param_1[0x179] = 0x404;
  param_1[0x17a] = 0x404;
  param_1[0x17b] = 0x404;
  param_1[0x17c] = 0x404;
  param_1[0x17d] = 0x404;
  param_1[0x17e] = 0x404;
  param_1[0x17f] = 0x404;
  puVar1 = param_1 + 0x180;
  iVar2 = 2;
  do {
    *puVar1 = 0x3c03;
    puVar1[1] = 0x3c03;
    puVar1[2] = 0x3c03;
    puVar1[3] = 0x3c03;
    puVar1[4] = 0x3c03;
    puVar1[5] = 0x3c03;
    puVar1[6] = 0x3c03;
    puVar1[7] = 0x3c03;
    puVar1[8] = 0x3c03;
    puVar1[9] = 0x3c03;
    puVar1[10] = 0x3c03;
    puVar1[0xb] = 0x3c03;
    puVar1[0xc] = 0x3c03;
    puVar1[0xd] = 0x3c03;
    puVar1[0xe] = 0x3c03;
    puVar1[0xf] = 0x3c03;
    puVar1[0x10] = 0x3c03;
    puVar1[0x11] = 0x3c03;
    puVar1[0x12] = 0x3c03;
    puVar1[0x13] = 0x3c03;
    puVar1[0x14] = 0x3c03;
    puVar1[0x15] = 0x3c03;
    puVar1[0x16] = 0x3c03;
    puVar1[0x17] = 0x3c03;
    puVar1[0x18] = 0x3c03;
    puVar1[0x19] = 0x3c03;
    puVar1[0x1a] = 0x3c03;
    puVar1[0x1b] = 0x3c03;
    puVar1[0x1c] = 0x3c03;
    puVar1[0x1d] = 0x3c03;
    puVar1[0x1e] = 0x3c03;
    puVar1[0x1f] = 0x3c03;
    puVar1 = puVar1 + 0x20;
    iVar2 = iVar2 + -1;
  } while (iVar2 != 0);
  return puVar1;
}



// ==== 80286978  zz_0286978_ ====

undefined2 * zz_0286978_(undefined2 *param_1)

{
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0xe709;
  param_1[3] = 0xdb09;
  param_1[4] = 0xfb09;
  param_1[5] = 0xf709;
  param_1[6] = 0xef09;
  param_1[7] = 0xdf09;
  param_1[8] = 0xba08;
  param_1[9] = 0xba08;
  param_1[10] = 0xb608;
  param_1[0xb] = 0xb608;
  param_1[0xc] = 0xae08;
  param_1[0xd] = 0xae08;
  param_1[0xe] = 0x9e08;
  param_1[0xf] = 0x9e08;
  param_1[0x10] = 0x7908;
  param_1[0x11] = 0x7908;
  param_1[0x12] = 0x7508;
  param_1[0x13] = 0x7508;
  param_1[0x14] = 0x6d08;
  param_1[0x15] = 0x6d08;
  param_1[0x16] = 0x5d08;
  param_1[0x17] = 0x5d08;
  param_1[0x18] = 0xa608;
  param_1[0x19] = 0xa608;
  param_1[0x1a] = 0x9a08;
  param_1[0x1b] = 0x9a08;
  param_1[0x1c] = 0x6508;
  param_1[0x1d] = 0x6508;
  param_1[0x1e] = 0x5908;
  param_1[0x1f] = 0x5908;
  param_1[0x20] = 0xeb08;
  param_1[0x21] = 0xeb08;
  param_1[0x22] = 0xd708;
  param_1[0x23] = 0xd708;
  param_1[0x24] = 0xf308;
  param_1[0x25] = 0xf308;
  param_1[0x26] = 53000;
  param_1[0x27] = 53000;
  param_1[0x28] = 0xaa08;
  param_1[0x29] = 0xaa08;
  param_1[0x2a] = 0x9608;
  param_1[0x2b] = 0x9608;
  param_1[0x2c] = 0xb208;
  param_1[0x2d] = 0xb208;
  param_1[0x2e] = 0x8e08;
  param_1[0x2f] = 0x8e08;
  param_1[0x30] = 0x6908;
  param_1[0x31] = 0x6908;
  param_1[0x32] = 0x5508;
  param_1[0x33] = 0x5508;
  param_1[0x34] = 0x7108;
  param_1[0x35] = 0x7108;
  param_1[0x36] = 0x4d08;
  param_1[0x37] = 0x4d08;
  param_1[0x38] = 0xe308;
  param_1[0x39] = 0xe308;
  param_1[0x3a] = 0xd308;
  param_1[0x3b] = 0xd308;
  param_1[0x3c] = 0xcb08;
  param_1[0x3d] = 0xcb08;
  param_1[0x3e] = 0xc708;
  param_1[0x3f] = 0xc708;
  return param_1 + 0x40;
}



// ==== 80286b20  zz_0286b20_ ====

/* WARNING: Removing unreachable block (ram,0x80286eb4) */

void zz_0286b20_(void)

{
  ushort *puVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort *puVar5;
  int iVar6;
  
  DAT_8041c898 = 0x7f;
  DAT_8041c89a = 0x7f;
  DAT_8041c89c = 0x7f;
  DAT_8041c89e = 0x7f;
  DAT_8041c8a0 = 0x7f;
  DAT_8041c8a2 = 0x7f;
  DAT_8041c8a4 = 0x7f;
  DAT_8041c8a6 = 0x7f;
  DAT_8041c8a8 = 0x7f;
  DAT_8041c8aa = 0x7f;
  DAT_8041c8ac = 0x7f;
  DAT_8041c8ae = 0x7f;
  DAT_8041c8b0 = 0x7f;
  DAT_8041c8b2 = 0x7f;
  DAT_8041c8b4 = 0x7f;
  DAT_8041c8b6 = 0x7f;
  DAT_8041c8b8 = 0x7f;
  DAT_8041c8ba = 0x7f;
  DAT_8041c8bc = 0x7f;
  DAT_8041c8be = 0x7f;
  DAT_8041c8c0 = 0x7f;
  DAT_8041c8c2 = 0x7f;
  DAT_8041c8c4 = 0x7f;
  DAT_8041c8c6 = 0x7f;
  DAT_8041c8c8 = 0xb10;
  DAT_8041c8ca = 0xbf0;
  DAT_8041c8cc = 0xb0f;
  DAT_8041c8ce = 0xbf1;
  DAT_8041c8d0 = 0xb0e;
  DAT_8041c8d2 = 0xbf2;
  DAT_8041c8d4 = 0xb0d;
  DAT_8041c8d6 = 0xbf3;
  DAT_8041c8d8 = 0xb0c;
  DAT_8041c8da = 0xbf4;
  DAT_8041c8dc = 0xb0b;
  DAT_8041c8de = 0xbf5;
  DAT_8041c8e0 = 0xa0a;
  DAT_8041c8e2 = 0xa0a;
  DAT_8041c8e4 = 0xaf6;
  DAT_8041c8e6 = 0xaf6;
  uVar4 = 7;
  DAT_8041c8e8 = 0xa09;
  DAT_8041c8ea = 0xa09;
  DAT_8041c8ec = 0xaf7;
  DAT_8041c8ee = 0xaf7;
  DAT_8041c8f0 = 0xa08;
  DAT_8041c8f2 = 0xa08;
  DAT_8041c8f4 = 0xaf8;
  DAT_8041c8f6 = 0xaf8;
  iVar6 = 3;
  puVar1 = &DAT_8041c8f8;
  do {
    puVar5 = puVar1;
    uVar2 = -uVar4;
    uVar3 = uVar4 & 0xff | 0x800;
    uVar4 = uVar4 - 1;
    *puVar5 = uVar3;
    uVar2 = uVar2 & 0xff | 0x800;
    puVar5[1] = uVar3;
    puVar5[2] = uVar3;
    puVar5[3] = uVar3;
    puVar5[4] = uVar3;
    puVar5[5] = uVar3;
    puVar5[6] = uVar3;
    puVar5[7] = uVar3;
    puVar5[8] = uVar2;
    puVar5[9] = uVar2;
    puVar5[10] = uVar2;
    puVar5[0xb] = uVar2;
    puVar5[0xc] = uVar2;
    puVar5[0xd] = uVar2;
    puVar5[0xe] = uVar2;
    puVar5[0xf] = uVar2;
    iVar6 = iVar6 + -1;
    puVar1 = puVar5 + 0x10;
  } while (iVar6 != 0);
  puVar5[0x10] = 0x704;
  puVar5[0x11] = 0x704;
  puVar5[0x12] = 0x704;
  puVar5[0x13] = 0x704;
  puVar5[0x14] = 0x704;
  puVar5[0x15] = 0x704;
  puVar5[0x16] = 0x704;
  puVar5[0x17] = 0x704;
  puVar5[0x18] = 0x704;
  puVar5[0x19] = 0x704;
  puVar5[0x1a] = 0x704;
  puVar5[0x1b] = 0x704;
  puVar5[0x1c] = 0x704;
  puVar5[0x1d] = 0x704;
  puVar5[0x1e] = 0x704;
  puVar5[0x1f] = 0x704;
  puVar5[0x20] = 0x7fc;
  puVar5[0x21] = 0x7fc;
  puVar5[0x22] = 0x7fc;
  puVar5[0x23] = 0x7fc;
  puVar5[0x24] = 0x7fc;
  puVar5[0x25] = 0x7fc;
  puVar5[0x26] = 0x7fc;
  puVar5[0x27] = 0x7fc;
  puVar5[0x28] = 0x7fc;
  puVar5[0x29] = 0x7fc;
  puVar5[0x2a] = 0x7fc;
  puVar5[0x2b] = 0x7fc;
  puVar5[0x2c] = 0x7fc;
  puVar5[0x2d] = 0x7fc;
  puVar5[0x2e] = 0x7fc;
  puVar5[0x2f] = 0x7fc;
  DAT_8041c858 = 0x7f;
  DAT_8041c85a = 0x7f;
  DAT_8041c85c = 0x503;
  DAT_8041c85e = 0x5fd;
  DAT_8041c860 = 0x402;
  DAT_8041c862 = 0x402;
  DAT_8041c864 = 0x4fe;
  DAT_8041c866 = 0x4fe;
  DAT_8041c868 = 0x301;
  DAT_8041c86a = 0x301;
  DAT_8041c86c = 0x301;
  DAT_8041c86e = 0x301;
  DAT_8041c870 = 0x3ff;
  DAT_8041c872 = 0x3ff;
  DAT_8041c874 = 0x3ff;
  DAT_8041c876 = 0x3ff;
  DAT_8041c878 = 0x100;
  DAT_8041c87a = 0x100;
  DAT_8041c87c = 0x100;
  DAT_8041c87e = 0x100;
  DAT_8041c880 = 0x100;
  DAT_8041c882 = 0x100;
  DAT_8041c884 = 0x100;
  DAT_8041c886 = 0x100;
  DAT_8041c888 = 0x100;
  DAT_8041c88a = 0x100;
  DAT_8041c88c = 0x100;
  DAT_8041c88e = 0x100;
  DAT_8041c890 = 0x100;
  DAT_8041c892 = 0x100;
  DAT_8041c894 = 0x100;
  DAT_8041c896 = 0x100;
  return;
}



// ==== 80286efc  zz_0286efc_ ====

void zz_0286efc_(void)

{
  DAT_8041c998 = 0x1f00;
  DAT_8041c99a = 0x1106;
  DAT_8041c99c = 0x1606;
  DAT_8041c99e = 0x1a06;
  DAT_8041c9a0 = 0x1e05;
  DAT_8041c9a2 = 0x1e05;
  DAT_8041c9a4 = 0x105;
  DAT_8041c9a6 = 0x105;
  DAT_8041c9a8 = 0x804;
  DAT_8041c9aa = 0x804;
  DAT_8041c9ac = 0x804;
  DAT_8041c9ae = 0x804;
  DAT_8041c9b0 = 0xa04;
  DAT_8041c9b2 = 0xa04;
  DAT_8041c9b4 = 0xa04;
  DAT_8041c9b6 = 0xa04;
  DAT_8041c9b8 = 0x403;
  DAT_8041c9ba = 0x403;
  DAT_8041c9bc = 0x403;
  DAT_8041c9be = 0x403;
  DAT_8041c9c0 = 0x403;
  DAT_8041c9c2 = 0x403;
  DAT_8041c9c4 = 0x403;
  DAT_8041c9c6 = 0x403;
  DAT_8041c9c8 = 0x603;
  DAT_8041c9ca = 0x603;
  DAT_8041c9cc = 0x603;
  DAT_8041c9ce = 0x603;
  DAT_8041c9d0 = 0x603;
  DAT_8041c9d2 = 0x603;
  DAT_8041c9d4 = 0x603;
  DAT_8041c9d6 = 0x603;
  DAT_8041c9d8 = 0xc02;
  DAT_8041c9da = 0xc02;
  DAT_8041c9dc = 0xc02;
  DAT_8041c9de = 0xc02;
  DAT_8041c9e0 = 0xc02;
  DAT_8041c9e2 = 0xc02;
  DAT_8041c9e4 = 0xc02;
  DAT_8041c9e6 = 0xc02;
  DAT_8041c9e8 = 0xc02;
  DAT_8041c9ea = 0xc02;
  DAT_8041c9ec = 0xc02;
  DAT_8041c9ee = 0xc02;
  DAT_8041c9f0 = 0xc02;
  DAT_8041c9f2 = 0xc02;
  DAT_8041c9f4 = 0xc02;
  DAT_8041c9f6 = 0xc02;
  DAT_8041c9f8 = 0xe02;
  DAT_8041c9fa = 0xe02;
  DAT_8041c9fc = 0xe02;
  DAT_8041c9fe = 0xe02;
  DAT_8041ca00 = 0xe02;
  DAT_8041ca02 = 0xe02;
  DAT_8041ca04 = 0xe02;
  DAT_8041ca06 = 0xe02;
  DAT_8041ca08 = 0xe02;
  DAT_8041ca0a = 0xe02;
  DAT_8041ca0c = 0xe02;
  DAT_8041ca0e = 0xe02;
  DAT_8041ca10 = 0xe02;
  DAT_8041ca12 = 0xe02;
  DAT_8041ca14 = 0xe02;
  DAT_8041ca16 = 0xe02;
  return;
}



// ==== 80287068  zz_0287068_ ====

/* WARNING: Removing unreachable block (ram,0x802870d0) */

void zz_0287068_(void)

{
  DAT_8041ca18 = 0x1106;
  DAT_8041ca1a = 0x1205;
  DAT_8041ca1c = 0x1a05;
  DAT_8041ca1e = 0x105;
  DAT_8041ca20 = 0x803;
  DAT_8041ca22 = 0x803;
  DAT_8041ca24 = 0x803;
  DAT_8041ca26 = 0x803;
  DAT_8041ca28 = 0x202;
  DAT_8041ca2a = 0x202;
  DAT_8041ca2c = 0x202;
  DAT_8041ca2e = 0x202;
  DAT_8041ca30 = 0x202;
  DAT_8041ca32 = 0x202;
  DAT_8041ca34 = 0x202;
  DAT_8041ca36 = 0x202;
  DAT_8041ca38 = 0xa01;
  DAT_8041ca3a = 0xa01;
  DAT_8041ca3c = 0xa01;
  DAT_8041ca3e = 0xa01;
  DAT_8041ca40 = 0xa01;
  DAT_8041ca42 = 0xa01;
  DAT_8041ca44 = 0xa01;
  DAT_8041ca46 = 0xa01;
  DAT_8041ca48 = 0xa01;
  DAT_8041ca4a = 0xa01;
  DAT_8041ca4c = 0xa01;
  DAT_8041ca4e = 0xa01;
  DAT_8041ca50 = 0xa01;
  DAT_8041ca52 = 0xa01;
  DAT_8041ca54 = 0xa01;
  DAT_8041ca56 = 0xa01;
  return;
}



// ==== 8028711c  zz_028711c_ ====

void zz_028711c_(void)

{
  ushort *puVar1;
  ushort *puVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  int iVar6;
  
  uVar4 = 0x210;
  DAT_8041ca98 = 0x240;
  DAT_8041ca9a = 0x240;
  DAT_8041ca9c = 0x240;
  DAT_8041ca9e = 0x240;
  DAT_8041caa0 = 0x240;
  DAT_8041caa2 = 0x240;
  DAT_8041caa4 = 0x240;
  DAT_8041caa6 = 0x240;
  DAT_8041caa8 = 0x23b;
  DAT_8041caaa = 0x240;
  DAT_8041caac = 0x240;
  DAT_8041caae = 0x240;
  DAT_8041cab0 = 0x240;
  DAT_8041cab2 = 0x240;
  DAT_8041cab4 = 0x240;
  DAT_8041cab6 = 0x22b;
  DAT_8041cab8 = 0x240;
  DAT_8041caba = 0x240;
  DAT_8041cabc = 0x240;
  DAT_8041cabe = 0x240;
  DAT_8041cac0 = 0x240;
  DAT_8041cac2 = 0x240;
  DAT_8041cac4 = 0x240;
  DAT_8041cac6 = 0x240;
  iVar6 = 2;
  puVar1 = &DAT_8041cac8;
  do {
    puVar2 = puVar1;
    *puVar2 = uVar4 | 0xb;
    puVar2[1] = uVar4 - 0x10 | 0xb;
    puVar2[2] = uVar4 - 0x20 | 0xb;
    puVar2[3] = uVar4 - 0x30 | 0xb;
    uVar5 = uVar4 - 0x50;
    puVar2[4] = uVar4 - 0x40 | 0xb;
    uVar4 = uVar4 - 0x60;
    puVar2[5] = uVar5 | 0xb;
    iVar6 = iVar6 + -1;
    puVar1 = puVar2 + 6;
  } while (iVar6 != 0);
  uVar4 = 0xf0;
  puVar2[6] = 0x15a;
  puVar2[7] = 0x15a;
  puVar2[8] = 0x14a;
  puVar2[9] = 0x14a;
  puVar2[10] = 0x13a;
  puVar2[0xb] = 0x13a;
  puVar2[0xc] = 0x12a;
  puVar2[0xd] = 0x12a;
  puVar2[0xe] = 0x11a;
  puVar2[0xf] = 0x11a;
  puVar2[0x10] = 0x10a;
  puVar2[0x11] = 0x10a;
  iVar6 = 2;
  puVar1 = puVar2 + 0x12;
  do {
    puVar2 = puVar1;
    *puVar2 = uVar4 | 8;
    puVar2[1] = uVar4 | 8;
    uVar5 = uVar4 - 0x10;
    puVar2[2] = uVar4 | 0x900b;
    puVar2[3] = uVar4 | 0x980b;
    puVar2[4] = uVar4 | 0xb00a;
    puVar2[5] = uVar4 | 0xb00a;
    puVar2[6] = uVar4 | 0xb80a;
    puVar2[7] = uVar4 | 0xb80a;
    uVar3 = uVar4 - 0x20;
    puVar2[8] = uVar5 | 8;
    puVar2[9] = uVar5 | 8;
    puVar2[10] = uVar5 | 0x900b;
    puVar2[0xb] = uVar5 | 0x980b;
    puVar2[0xc] = uVar5 | 0xb00a;
    puVar2[0xd] = uVar5 | 0xb00a;
    puVar2[0xe] = uVar5 | 0xb80a;
    puVar2[0xf] = uVar5 | 0xb80a;
    uVar4 = uVar4 - 0x30;
    puVar2[0x10] = uVar3 | 8;
    puVar2[0x11] = uVar3 | 8;
    puVar2[0x12] = uVar3 | 0x900b;
    puVar2[0x13] = uVar3 | 0x980b;
    puVar2[0x14] = uVar3 | 0xb00a;
    puVar2[0x15] = uVar3 | 0xb00a;
    puVar2[0x16] = uVar3 | 0xb80a;
    puVar2[0x17] = uVar3 | 0xb80a;
    iVar6 = iVar6 + -1;
    puVar1 = puVar2 + 0x18;
  } while (iVar6 != 0);
  puVar2[0x18] = 0x97;
  puVar2[0x19] = 0x97;
  puVar2[0x1a] = 0xa09b;
  puVar2[0x1b] = 0xa89b;
  puVar2[0x1c] = 0x909a;
  puVar2[0x1d] = 0x909a;
  puVar2[0x1e] = 0x989a;
  puVar2[0x1f] = 0x989a;
  puVar2[0x20] = 0xb099;
  puVar2[0x21] = 0xb099;
  puVar2[0x22] = 0xb099;
  puVar2[0x23] = 0xb099;
  puVar2[0x24] = 0xb899;
  puVar2[0x25] = 0xb899;
  puVar2[0x26] = 0xb899;
  puVar2[0x27] = 0xb899;
  puVar2[0x28] = 0x87;
  puVar2[0x29] = 0x87;
  puVar2[0x2a] = 0xa08b;
  puVar2[0x2b] = 0xa88b;
  puVar2[0x2c] = 0x908a;
  puVar2[0x2d] = 0x908a;
  puVar2[0x2e] = 0x988a;
  puVar2[0x2f] = 0x988a;
  puVar2[0x30] = 0xb089;
  puVar2[0x31] = 0xb089;
  puVar2[0x32] = 0xb089;
  puVar2[0x33] = 0xb089;
  puVar2[0x34] = 0xb889;
  puVar2[0x35] = 0xb889;
  puVar2[0x36] = 0xb889;
  DAT_8041ca58 = 0x240;
  DAT_8041ca5a = 0x240;
  DAT_8041ca5c = 0x75;
  DAT_8041ca5e = 0x65;
  DAT_8041ca60 = 0x54;
  DAT_8041ca62 = 0x54;
  DAT_8041ca64 = 0x44;
  puVar2[0x37] = 0xb889;
  DAT_8041ca66 = 0x44;
  DAT_8041ca68 = 0x33;
  DAT_8041ca6a = 0x33;
  DAT_8041ca6c = 0xb035;
  DAT_8041ca6e = 0xb835;
  DAT_8041ca70 = 0x23;
  DAT_8041ca72 = 0x23;
  DAT_8041ca74 = 0xb025;
  DAT_8041ca76 = 0xb825;
  DAT_8041ca78 = 0x11;
  DAT_8041ca7a = 0x11;
  DAT_8041ca7c = 0xa015;
  DAT_8041ca7e = 0xa815;
  DAT_8041ca80 = 0x9014;
  DAT_8041ca82 = 0x9014;
  DAT_8041ca84 = 0x9814;
  DAT_8041ca86 = 0x9814;
  DAT_8041ca88 = 0xb013;
  DAT_8041ca8a = 0xb013;
  DAT_8041ca8c = 0xb013;
  DAT_8041ca8e = 0xb013;
  DAT_8041ca90 = 0xb813;
  DAT_8041ca92 = 0xb813;
  DAT_8041ca94 = 0xb813;
  DAT_8041ca96 = 0xb813;
  return;
}



// ==== 802874d8  zz_02874d8_ ====

void zz_02874d8_(void)

{
  ushort *puVar1;
  ushort *puVar2;
  ushort uVar3;
  ushort uVar4;
  ushort uVar5;
  ushort uVar6;
  int iVar7;
  
  uVar5 = 0x210;
  DAT_8041cbd8 = 0x240;
  DAT_8041cbda = 0x240;
  DAT_8041cbdc = 0x240;
  DAT_8041cbde = 0x240;
  DAT_8041cbe0 = 0x240;
  DAT_8041cbe2 = 0x240;
  DAT_8041cbe4 = 0x240;
  DAT_8041cbe6 = 0x240;
  DAT_8041cbe8 = 0x23b;
  DAT_8041cbea = 0x240;
  DAT_8041cbec = 0x240;
  DAT_8041cbee = 0x240;
  DAT_8041cbf0 = 0x240;
  DAT_8041cbf2 = 0x240;
  DAT_8041cbf4 = 0x240;
  DAT_8041cbf6 = 0x22b;
  DAT_8041cbf8 = 0x240;
  DAT_8041cbfa = 0x240;
  DAT_8041cbfc = 0x240;
  DAT_8041cbfe = 0x240;
  DAT_8041cc00 = 0x240;
  DAT_8041cc02 = 0x240;
  DAT_8041cc04 = 0x240;
  DAT_8041cc06 = 0x240;
  iVar7 = 2;
  puVar1 = &DAT_8041cc08;
  do {
    puVar2 = puVar1;
    *puVar2 = uVar5 | 0xb;
    puVar2[1] = uVar5 - 0x10 | 0xb;
    puVar2[2] = uVar5 - 0x20 | 0xb;
    puVar2[3] = uVar5 - 0x30 | 0xb;
    uVar6 = uVar5 - 0x50;
    puVar2[4] = uVar5 - 0x40 | 0xb;
    uVar5 = uVar5 - 0x60;
    puVar2[5] = uVar6 | 0xb;
    iVar7 = iVar7 + -1;
    puVar1 = puVar2 + 6;
  } while (iVar7 != 0);
  uVar5 = 0xf0;
  puVar2[6] = 0x15a;
  puVar2[7] = 0xa95b;
  puVar2[8] = 0x14a;
  puVar2[9] = 0xa94b;
  puVar2[10] = 0x13a;
  puVar2[0xb] = 0xa93b;
  puVar2[0xc] = 0x12a;
  puVar2[0xd] = 0xa92b;
  puVar2[0xe] = 0x11a;
  puVar2[0xf] = 0xa91b;
  puVar2[0x10] = 0x10a;
  puVar2[0x11] = 0xa90b;
  iVar7 = 2;
  puVar1 = puVar2 + 0x12;
  do {
    puVar2 = puVar1;
    *puVar2 = uVar5 | 8;
    uVar6 = uVar5 | 0xa809;
    uVar3 = uVar5 - 0x10;
    puVar2[1] = uVar5 | 0xa00b;
    puVar2[2] = uVar5 | 0x880a;
    puVar2[3] = uVar5 | 0x880a;
    puVar2[4] = uVar6;
    puVar2[5] = uVar6;
    puVar2[6] = uVar6;
    puVar2[7] = uVar6;
    uVar6 = uVar3 | 0xa809;
    uVar4 = uVar5 - 0x20;
    puVar2[8] = uVar3 | 8;
    puVar2[9] = uVar3 | 0xa00b;
    puVar2[10] = uVar3 | 0x880a;
    puVar2[0xb] = uVar3 | 0x880a;
    puVar2[0xc] = uVar6;
    puVar2[0xd] = uVar6;
    puVar2[0xe] = uVar6;
    puVar2[0xf] = uVar6;
    uVar6 = uVar4 | 0xa809;
    uVar5 = uVar5 - 0x30;
    puVar2[0x10] = uVar4 | 8;
    puVar2[0x11] = uVar4 | 0xa00b;
    puVar2[0x12] = uVar4 | 0x880a;
    puVar2[0x13] = uVar4 | 0x880a;
    puVar2[0x14] = uVar6;
    puVar2[0x15] = uVar6;
    puVar2[0x16] = uVar6;
    puVar2[0x17] = uVar6;
    iVar7 = iVar7 + -1;
    puVar1 = puVar2 + 0x18;
  } while (iVar7 != 0);
  puVar2[0x18] = 0x97;
  puVar2[0x19] = 0x97;
  puVar2[0x1a] = 0xa09a;
  puVar2[0x1b] = 0xa09a;
  puVar2[0x1c] = 0x8899;
  puVar2[0x1d] = 0x8899;
  puVar2[0x1e] = 0x8899;
  puVar2[0x1f] = 0x8899;
  puVar2[0x20] = 0xa898;
  puVar2[0x21] = 0xa898;
  puVar2[0x22] = 0xa898;
  puVar2[0x23] = 0xa898;
  puVar2[0x24] = 0xa898;
  puVar2[0x25] = 0xa898;
  puVar2[0x26] = 0xa898;
  puVar2[0x27] = 0xa898;
  puVar2[0x28] = 0x87;
  puVar2[0x29] = 0x87;
  puVar2[0x2a] = 0xa08a;
  puVar2[0x2b] = 0xa08a;
  puVar2[0x2c] = 0x8889;
  puVar2[0x2d] = 0x8889;
  puVar2[0x2e] = 0x8889;
  puVar2[0x2f] = 0x8889;
  puVar2[0x30] = 0xa888;
  puVar2[0x31] = 0xa888;
  puVar2[0x32] = 0xa888;
  puVar2[0x33] = 0xa888;
  puVar2[0x34] = 0xa888;
  puVar2[0x35] = 0xa888;
  puVar2[0x36] = 0xa888;
  DAT_8041cb98 = 0x240;
  DAT_8041cb9a = 0x240;
  DAT_8041cb9c = 0x75;
  DAT_8041cb9e = 0x65;
  DAT_8041cba0 = 0x54;
  DAT_8041cba2 = 0xa855;
  DAT_8041cba4 = 0x44;
  puVar2[0x37] = 0xa888;
  DAT_8041cba6 = 0xa845;
  DAT_8041cba8 = 0x33;
  DAT_8041cbaa = 0x8835;
  DAT_8041cbac = 0xa834;
  DAT_8041cbae = 0xa834;
  DAT_8041cbb0 = 0x23;
  DAT_8041cbb2 = 0x8825;
  DAT_8041cbb4 = 0xa824;
  DAT_8041cbb6 = 0xa824;
  DAT_8041cbb8 = 0x11;
  DAT_8041cbba = 0x11;
  DAT_8041cbbc = 0xa014;
  DAT_8041cbbe = 0xa014;
  DAT_8041cbc0 = 0x8813;
  DAT_8041cbc2 = 0x8813;
  DAT_8041cbc4 = 0x8813;
  DAT_8041cbc6 = 0x8813;
  DAT_8041cbc8 = 0xa812;
  DAT_8041cbca = 0xa812;
  DAT_8041cbcc = 0xa812;
  DAT_8041cbce = 0xa812;
  DAT_8041cbd0 = 0xa812;
  DAT_8041cbd2 = 0xa812;
  DAT_8041cbd4 = 0xa812;
  DAT_8041cbd6 = 0xa812;
  return;
}



// ==== 8028789c  zz_028789c_ ====

void zz_028789c_(void)

{
  ushort *puVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  ushort *puVar5;
  int iVar6;
  
  DAT_8041cd58 = 0x240;
  DAT_8041cd5a = 0x240;
  DAT_8041cd5c = 0x240;
  DAT_8041cd5e = 0x240;
  DAT_8041cd60 = 0x240;
  DAT_8041cd62 = 0x240;
  DAT_8041cd64 = 0x240;
  DAT_8041cd66 = 0x240;
  DAT_8041cd68 = 0x240;
  DAT_8041cd6a = 0x240;
  DAT_8041cd6c = 0x240;
  DAT_8041cd6e = 0x240;
  DAT_8041cd70 = 0x240;
  DAT_8041cd72 = 0x240;
  DAT_8041cd74 = 0x240;
  DAT_8041cd76 = 0x240;
  DAT_8041cd78 = 0x23b;
  DAT_8041cd7a = 0x23b;
  DAT_8041cd7c = 0x240;
  DAT_8041cd7e = 0x240;
  DAT_8041cd80 = 0x240;
  DAT_8041cd82 = 0x240;
  DAT_8041cd84 = 0x240;
  DAT_8041cd86 = 0x240;
  DAT_8041cd88 = 0x240;
  DAT_8041cd8a = 0x240;
  DAT_8041cd8c = 0x240;
  DAT_8041cd8e = 0x240;
  DAT_8041cd90 = 0x240;
  DAT_8041cd92 = 0x240;
  DAT_8041cd94 = 0x22b;
  DAT_8041cd96 = 0x22b;
  DAT_8041cd98 = 0x240;
  DAT_8041cd9a = 0x240;
  DAT_8041cd9c = 0x240;
  DAT_8041cd9e = 0x240;
  DAT_8041cda0 = 0x240;
  DAT_8041cda2 = 0x240;
  DAT_8041cda4 = 0x240;
  DAT_8041cda6 = 0x240;
  DAT_8041cda8 = 0x240;
  DAT_8041cdaa = 0x240;
  DAT_8041cdac = 0x240;
  DAT_8041cdae = 0x240;
  DAT_8041cdb0 = 0x240;
  DAT_8041cdb2 = 0x240;
  DAT_8041cdb4 = 0x240;
  DAT_8041cdb6 = 0x240;
  uVar4 = 0x210;
  iVar6 = 2;
  puVar1 = &DAT_8041cdb8;
  do {
    puVar5 = puVar1;
    *puVar5 = uVar4 | 0x440d;
    puVar5[1] = uVar4 | 0x40c;
    puVar5[2] = uVar4 - 0x10 | 0x440d;
    puVar5[3] = uVar4 - 0x10 | 0x40c;
    puVar5[4] = uVar4 - 0x20 | 0x440d;
    puVar5[5] = uVar4 - 0x20 | 0x40c;
    puVar5[6] = uVar4 - 0x30 | 0x440d;
    puVar5[7] = uVar4 - 0x30 | 0x40c;
    uVar2 = uVar4 - 0x50;
    puVar5[8] = uVar4 - 0x40 | 0x440d;
    puVar5[9] = uVar4 - 0x40 | 0x40c;
    uVar4 = uVar4 - 0x60;
    puVar5[10] = uVar2 | 0x440d;
    puVar5[0xb] = uVar2 | 0x40c;
    iVar6 = iVar6 + -1;
    puVar1 = puVar5 + 0xc;
  } while (iVar6 != 0);
  uVar4 = 0xf0;
  puVar5[0xc] = 0x455c;
  puVar5[0xd] = 0x455c;
  puVar5[0xe] = 0x55b;
  puVar5[0xf] = 0x55b;
  puVar5[0x10] = 0x454c;
  puVar5[0x11] = 0x454c;
  puVar5[0x12] = 0x54b;
  puVar5[0x13] = 0x54b;
  puVar5[0x14] = 0x453c;
  puVar5[0x15] = 0x453c;
  puVar5[0x16] = 0x53b;
  puVar5[0x17] = 0x53b;
  puVar5[0x18] = 0x452c;
  puVar5[0x19] = 0x452c;
  puVar5[0x1a] = 0x52b;
  puVar5[0x1b] = 0x52b;
  puVar5[0x1c] = 0x451c;
  puVar5[0x1d] = 0x451c;
  puVar5[0x1e] = 0x51b;
  puVar5[0x1f] = 0x51b;
  puVar5[0x20] = 0x450c;
  puVar5[0x21] = 0x450c;
  puVar5[0x22] = 0x50b;
  puVar5[0x23] = 0x50b;
  iVar6 = 2;
  puVar5 = puVar5 + 0x24;
  do {
    uVar3 = uVar4 | 0x440a;
    uVar2 = uVar4 | 0x409;
    *puVar5 = uVar3;
    puVar5[1] = uVar3;
    puVar5[2] = uVar3;
    puVar5[3] = uVar3;
    puVar5[4] = uVar3;
    puVar5[5] = uVar3;
    puVar5[6] = uVar3;
    puVar5[7] = uVar3;
    uVar3 = uVar4 - 0x10 | 0x440a;
    puVar5[8] = uVar2;
    puVar5[9] = uVar2;
    puVar5[10] = uVar2;
    puVar5[0xb] = uVar2;
    puVar5[0xc] = uVar2;
    puVar5[0xd] = uVar2;
    puVar5[0xe] = uVar2;
    puVar5[0xf] = uVar2;
    uVar2 = uVar4 - 0x10 | 0x409;
    puVar5[0x10] = uVar3;
    puVar5[0x11] = uVar3;
    puVar5[0x12] = uVar3;
    puVar5[0x13] = uVar3;
    puVar5[0x14] = uVar3;
    puVar5[0x15] = uVar3;
    puVar5[0x16] = uVar3;
    puVar5[0x17] = uVar3;
    uVar3 = uVar4 - 0x20 | 0x440a;
    puVar5[0x18] = uVar2;
    puVar5[0x19] = uVar2;
    puVar5[0x1a] = uVar2;
    puVar5[0x1b] = uVar2;
    puVar5[0x1c] = uVar2;
    puVar5[0x1d] = uVar2;
    puVar5[0x1e] = uVar2;
    puVar5[0x1f] = uVar2;
    uVar2 = uVar4 - 0x20 | 0x409;
    uVar4 = uVar4 - 0x30;
    puVar5[0x20] = uVar3;
    puVar5[0x21] = uVar3;
    puVar5[0x22] = uVar3;
    puVar5[0x23] = uVar3;
    puVar5[0x24] = uVar3;
    puVar5[0x25] = uVar3;
    puVar5[0x26] = uVar3;
    puVar5[0x27] = uVar3;
    puVar5[0x28] = uVar2;
    puVar5[0x29] = uVar2;
    puVar5[0x2a] = uVar2;
    puVar5[0x2b] = uVar2;
    puVar5[0x2c] = uVar2;
    puVar5[0x2d] = uVar2;
    puVar5[0x2e] = uVar2;
    puVar5[0x2f] = uVar2;
    puVar5 = puVar5 + 0x30;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  uVar4 = 0x90;
  iVar6 = 2;
  do {
    uVar2 = uVar4 | 0x4409;
    *puVar5 = uVar2;
    puVar5[1] = uVar2;
    puVar5[2] = uVar2;
    puVar5[3] = uVar2;
    puVar5[4] = uVar2;
    puVar5[5] = uVar2;
    puVar5[6] = uVar2;
    puVar5[7] = uVar2;
    puVar5[8] = uVar2;
    puVar5[9] = uVar2;
    puVar5[10] = uVar2;
    puVar5[0xb] = uVar2;
    puVar5[0xc] = uVar2;
    puVar5[0xd] = uVar2;
    puVar5[0xe] = uVar2;
    puVar5[0xf] = uVar2;
    uVar2 = uVar4 | 0x408;
    puVar5[0x10] = uVar2;
    puVar5[0x11] = uVar2;
    puVar5[0x12] = uVar2;
    puVar5[0x13] = uVar2;
    puVar5[0x14] = uVar2;
    puVar5[0x15] = uVar2;
    puVar5[0x16] = uVar2;
    puVar5[0x17] = uVar2;
    puVar5[0x18] = uVar2;
    puVar5[0x19] = uVar2;
    puVar5[0x1a] = uVar2;
    puVar5[0x1b] = uVar2;
    puVar5[0x1c] = uVar2;
    puVar5[0x1d] = uVar2;
    puVar5[0x1e] = uVar2;
    puVar5[0x1f] = uVar2;
    puVar5 = puVar5 + 0x20;
    uVar4 = uVar4 - 0x10;
    iVar6 = iVar6 + -1;
  } while (iVar6 != 0);
  DAT_8041ccd8 = 0x240;
  DAT_8041ccda = 0x240;
  DAT_8041ccdc = 0x240;
  DAT_8041ccde = 0x240;
  DAT_8041cce0 = 0x4477;
  DAT_8041cce2 = 0x476;
  DAT_8041cce4 = 0x4467;
  DAT_8041cce6 = 0x466;
  DAT_8041cce8 = 0x4456;
  DAT_8041ccea = 0x4456;
  DAT_8041ccec = 0x455;
  DAT_8041ccee = 0x455;
  DAT_8041ccf0 = 0x4446;
  DAT_8041ccf2 = 0x4446;
  DAT_8041ccf4 = 0x445;
  DAT_8041ccf6 = 0x445;
  DAT_8041ccf8 = 0x4435;
  DAT_8041ccfa = 0x4435;
  DAT_8041ccfc = 0x4435;
  DAT_8041ccfe = 0x4435;
  DAT_8041cd00 = 0x434;
  DAT_8041cd02 = 0x434;
  DAT_8041cd04 = 0x434;
  DAT_8041cd06 = 0x434;
  DAT_8041cd08 = 0x4425;
  DAT_8041cd0a = 0x4425;
  DAT_8041cd0c = 0x4425;
  DAT_8041cd0e = 0x4425;
  DAT_8041cd10 = 0x424;
  DAT_8041cd12 = 0x424;
  DAT_8041cd14 = 0x424;
  DAT_8041cd16 = 0x424;
  DAT_8041cd18 = 0x4413;
  DAT_8041cd1a = 0x4413;
  DAT_8041cd1c = 0x4413;
  DAT_8041cd1e = 0x4413;
  DAT_8041cd20 = 0x4413;
  DAT_8041cd22 = 0x4413;
  DAT_8041cd24 = 0x4413;
  DAT_8041cd26 = 0x4413;
  DAT_8041cd28 = 0x4413;
  DAT_8041cd2a = 0x4413;
  DAT_8041cd2c = 0x4413;
  DAT_8041cd2e = 0x4413;
  DAT_8041cd30 = 0x4413;
  DAT_8041cd32 = 0x4413;
  DAT_8041cd34 = 0x4413;
  DAT_8041cd36 = 0x4413;
  DAT_8041cd38 = 0x412;
  DAT_8041cd3a = 0x412;
  DAT_8041cd3c = 0x412;
  DAT_8041cd3e = 0x412;
  DAT_8041cd40 = 0x412;
  DAT_8041cd42 = 0x412;
  DAT_8041cd44 = 0x412;
  DAT_8041cd46 = 0x412;
  DAT_8041cd48 = 0x412;
  DAT_8041cd4a = 0x412;
  DAT_8041cd4c = 0x412;
  DAT_8041cd4e = 0x412;
  DAT_8041cd50 = 0x412;
  DAT_8041cd52 = 0x412;
  DAT_8041cd54 = 0x412;
  DAT_8041cd56 = 0x412;
  return;
}



// ==== 80287e58  zz_0287e58_ ====

void zz_0287e58_(undefined4 *param_1)

{
  undefined2 *puVar1;
  
  zz_028789c_();
  zz_02874d8_();
  zz_028711c_();
  zz_0287068_();
  zz_0286efc_();
  zz_0286b20_();
  puVar1 = zz_0286978_((undefined2 *)&DAT_8041c458);
  zz_0286144_(puVar1);
  zz_0285ec0_();
  zz_0285c4c_();
  zz_0285744_();
  zz_02852d8_();
  zz_0285010_();
  DAT_8041cfac = &DAT_8041cd58;
  DAT_8041cfa8 = &DAT_8041ccd8;
  DAT_8041cfa4 = &DAT_8041cbd8;
  DAT_8041cfa0 = &DAT_8041cb98;
  DAT_8041cf9c = &DAT_8041ca98;
  DAT_8041cf98 = &DAT_8041ca58;
  DAT_8041cf94 = (undefined4 *)&DAT_8041ca18;
  DAT_8041cf90 = (undefined4 *)&DAT_8041c998;
  DAT_8041cf8c = (undefined4 *)&DAT_8041c898;
  DAT_8041cf88 = (undefined4 *)&DAT_8041c858;
  DAT_8041cf84 = &DAT_8041c458;
  DAT_8041cf80 = (undefined4 *)&DAT_8041c3d8;
  DAT_8041cf7c = (undefined4 *)&DAT_8041c358;
  DAT_8041cf78 = &DAT_8041bf58;
  DAT_8041cf74 = &DAT_8041bb58;
  DAT_8041cf70 = (undefined4 *)&DAT_802b8960;
  DAT_8041cf6c = (undefined4 *)&DAT_802b8980;
  DAT_8041cf68 = (undefined4 *)&DAT_802b89a0;
  DAT_8041cf64 = (undefined4 *)&DAT_802b89c0;
  DAT_8041cf60 = (undefined4 *)&DAT_802b89e0;
  DAT_8041cf5c = (undefined4 *)&DAT_802b8a00;
  DAT_8041cf58 = &DAT_8041b958;
  if (param_1 != (undefined4 *)0x0) {
    DAT_8041cf58 = param_1 + 0xec;
    zz_02a9400_(DAT_8041cf58,&DAT_8041b958,0x80);
    DAT_8041cf5c = param_1 + 0xe8;
    zz_02a9400_(DAT_8041cf5c,(undefined4 *)&DAT_802b8a00,4);
    DAT_8041cf60 = param_1 + 0xe0;
    zz_02a9400_(DAT_8041cf60,(undefined4 *)&DAT_802b89e0,8);
    DAT_8041cf64 = param_1 + 0xd8;
    zz_02a9400_(DAT_8041cf64,(undefined4 *)&DAT_802b89c0,8);
    DAT_8041cf68 = param_1 + 0xd0;
    zz_02a9400_(DAT_8041cf68,(undefined4 *)&DAT_802b89a0,8);
    DAT_8041cf6c = param_1 + 200;
    zz_02a9400_(DAT_8041cf6c,(undefined4 *)&DAT_802b8980,8);
    DAT_8041cf70 = param_1 + 0xc0;
    zz_02a9400_(DAT_8041cf70,(undefined4 *)&DAT_802b8960,8);
    DAT_8041cf80 = param_1 + 0xa0;
    zz_02a9400_(DAT_8041cf80,(undefined4 *)&DAT_8041c3d8,0x20);
    DAT_8041cf7c = param_1 + 0x80;
    zz_02a9400_(DAT_8041cf7c,(undefined4 *)&DAT_8041c358,0x20);
    DAT_8041cf8c = param_1 + 0x40;
    zz_02a9400_(DAT_8041cf8c,(undefined4 *)&DAT_8041c898,0x40);
    DAT_8041cf88 = param_1 + 0x30;
    zz_02a9400_(DAT_8041cf88,(undefined4 *)&DAT_8041c858,0x10);
    DAT_8041cf94 = param_1 + 0x20;
    zz_02a9400_(DAT_8041cf94,(undefined4 *)&DAT_8041ca18,0x10);
    DAT_8041cf90 = param_1;
    zz_02a9400_(param_1,(undefined4 *)&DAT_8041c998,0x20);
  }
  return;
}



// ==== 80288084  zz_0288084_ ====

undefined4 zz_0288084_(void)

{
  return 0;
}



// ==== 802880a4  FUN_802880a4 ====

void FUN_802880a4(int param_1,int param_2)

{
  int iVar1;
  code *pcVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x2dc);
  *(undefined4 *)(param_1 + 0x2e8) = 0;
  iVar1 = iVar3 - param_2;
  pcVar2 = *(code **)(param_1 + 0x27c);
  while (iVar1 = iVar1 + 1, iVar1 < iVar3) {
    *(int *)(param_1 + 0x2dc) = iVar1;
    (*pcVar2)(param_1);
  }
  *(int *)(param_1 + 0x2dc) = iVar3;
  return;
}



// ==== 80288124  zz_0288124_ ====

void zz_0288124_(uint *param_1,int *param_2,int *param_3)

{
  uint uVar1;
  undefined8 *puVar2;
  undefined8 *puVar3;
  uint uVar4;
  int iVar5;
  undefined8 *puVar6;
  undefined8 uVar7;
  
  uVar4 = *param_1;
  uVar1 = (uint)*(short *)(param_3 + 3);
  iVar5 = ((int)uVar1 >> 3) + (uint)((int)uVar1 < 0 && (uVar1 & 7) != 0);
  if ((uVar4 & 0x1f) == 0) {
    puVar6 = (undefined8 *)(*param_3 + uVar4);
    puVar2 = (undefined8 *)(*param_2 + uVar4);
    dataCacheBlockClearToZero(puVar6);
    dataCacheBlockClearToZero(puVar6 + iVar5);
    uVar7 = puVar2[iVar5];
    puVar3 = puVar2 + iVar5 * 2;
    *puVar6 = *puVar2;
    puVar6[iVar5] = uVar7;
    puVar6 = puVar6 + iVar5 * 2;
    dataCacheBlockClearToZero(puVar6);
    dataCacheBlockClearToZero(puVar6 + iVar5);
    uVar7 = puVar3[iVar5];
    puVar2 = puVar3 + iVar5 * 2;
    *puVar6 = *puVar3;
    puVar6[iVar5] = uVar7;
    puVar6 = puVar6 + iVar5 * 2;
    dataCacheBlockClearToZero(puVar6);
    dataCacheBlockClearToZero(puVar6 + iVar5);
    uVar7 = puVar2[iVar5];
    *puVar6 = *puVar2;
    puVar6[iVar5] = uVar7;
    puVar6 = puVar6 + iVar5 * 2;
    dataCacheBlockClearToZero(puVar6);
    dataCacheBlockClearToZero(puVar6 + iVar5);
    uVar7 = (puVar2 + iVar5 * 2)[iVar5];
    *puVar6 = puVar2[iVar5 * 2];
    puVar6[iVar5] = uVar7;
    puVar2 = (undefined8 *)(param_2[1] + *param_1);
    puVar6 = (undefined8 *)(param_3[1] + *param_1);
    dataCacheBlockClearToZero(puVar6);
    dataCacheBlockClearToZero(puVar6 + iVar5);
    uVar7 = puVar2[iVar5];
    puVar3 = puVar2 + iVar5 * 2;
    *puVar6 = *puVar2;
    puVar6[iVar5] = uVar7;
    puVar6 = puVar6 + iVar5 * 2;
    dataCacheBlockClearToZero(puVar6);
    dataCacheBlockClearToZero(puVar6 + iVar5);
    uVar7 = puVar3[iVar5];
    puVar2 = puVar3 + iVar5 * 2;
    *puVar6 = *puVar3;
    puVar6[iVar5] = uVar7;
    puVar6 = puVar6 + iVar5 * 2;
    dataCacheBlockClearToZero(puVar6);
    dataCacheBlockClearToZero(puVar6 + iVar5);
    uVar7 = puVar2[iVar5];
    *puVar6 = *puVar2;
    puVar6[iVar5] = uVar7;
    puVar6 = puVar6 + iVar5 * 2;
    dataCacheBlockClearToZero(puVar6);
    dataCacheBlockClearToZero(puVar6 + iVar5);
    uVar7 = (puVar2 + iVar5 * 2)[iVar5];
    *puVar6 = puVar2[iVar5 * 2];
    puVar6[iVar5] = uVar7;
  }
  else {
    puVar2 = (undefined8 *)(*param_2 + uVar4);
    puVar6 = (undefined8 *)(*param_3 + uVar4);
    uVar7 = puVar2[iVar5];
    puVar3 = puVar2 + iVar5 * 2;
    *puVar6 = *puVar2;
    puVar6[iVar5] = uVar7;
    puVar6 = puVar6 + iVar5 * 2;
    uVar7 = puVar3[iVar5];
    puVar2 = puVar3 + iVar5 * 2;
    *puVar6 = *puVar3;
    puVar6[iVar5] = uVar7;
    puVar6 = puVar6 + iVar5 * 2;
    uVar7 = puVar2[iVar5];
    *puVar6 = *puVar2;
    puVar6[iVar5] = uVar7;
    uVar7 = (puVar2 + iVar5 * 2)[iVar5];
    puVar6[iVar5 * 2] = puVar2[iVar5 * 2];
    (puVar6 + iVar5 * 2)[iVar5] = uVar7;
    puVar2 = (undefined8 *)(param_2[1] + *param_1);
    puVar6 = (undefined8 *)(param_3[1] + *param_1);
    uVar7 = puVar2[iVar5];
    puVar3 = puVar2 + iVar5 * 2;
    *puVar6 = *puVar2;
    puVar6[iVar5] = uVar7;
    puVar6 = puVar6 + iVar5 * 2;
    uVar7 = puVar3[iVar5];
    puVar2 = puVar3 + iVar5 * 2;
    *puVar6 = *puVar3;
    puVar6[iVar5] = uVar7;
    puVar6 = puVar6 + iVar5 * 2;
    uVar7 = puVar2[iVar5];
    *puVar6 = *puVar2;
    puVar6[iVar5] = uVar7;
    uVar7 = (puVar2 + iVar5 * 2)[iVar5];
    puVar6[iVar5 * 2] = puVar2[iVar5 * 2];
    (puVar6 + iVar5 * 2)[iVar5] = uVar7;
  }
  uVar4 = param_1[1];
  uVar1 = (uint)*(short *)((int)param_3 + 0xe);
  iVar5 = ((int)uVar1 >> 3) + (uint)((int)uVar1 < 0 && (uVar1 & 7) != 0);
  if ((uVar4 & 0x1f) == 0) {
    puVar2 = (undefined8 *)(param_2[2] + uVar4);
    puVar6 = (undefined8 *)(param_3[2] + uVar4);
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar2[1];
    puVar3 = puVar2 + iVar5;
    *puVar6 = *puVar2;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar3[1];
    puVar2 = puVar3 + iVar5;
    *puVar6 = *puVar3;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar2[1];
    puVar3 = puVar2 + iVar5;
    *puVar6 = *puVar2;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar3[1];
    puVar2 = puVar3 + iVar5;
    *puVar6 = *puVar3;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar2[1];
    puVar3 = puVar2 + iVar5;
    *puVar6 = *puVar2;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar3[1];
    puVar2 = puVar3 + iVar5;
    *puVar6 = *puVar3;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar2[1];
    puVar3 = puVar2 + iVar5;
    *puVar6 = *puVar2;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar3[1];
    puVar2 = puVar3 + iVar5;
    *puVar6 = *puVar3;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar2[1];
    puVar3 = puVar2 + iVar5;
    *puVar6 = *puVar2;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar3[1];
    puVar2 = puVar3 + iVar5;
    *puVar6 = *puVar3;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar2[1];
    puVar3 = puVar2 + iVar5;
    *puVar6 = *puVar2;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar3[1];
    puVar2 = puVar3 + iVar5;
    *puVar6 = *puVar3;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar2[1];
    puVar3 = puVar2 + iVar5;
    *puVar6 = *puVar2;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar3[1];
    puVar2 = puVar3 + iVar5;
    *puVar6 = *puVar3;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = puVar2[1];
    *puVar6 = *puVar2;
    puVar6[1] = uVar7;
    puVar6 = puVar6 + iVar5;
    dataCacheBlockClearToZero(puVar6);
    uVar7 = (puVar2 + iVar5)[1];
    *puVar6 = puVar2[iVar5];
    puVar6[1] = uVar7;
    return;
  }
  puVar2 = (undefined8 *)(param_2[2] + uVar4);
  puVar6 = (undefined8 *)(param_3[2] + uVar4);
  uVar7 = puVar2[1];
  puVar3 = puVar2 + iVar5;
  *puVar6 = *puVar2;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar3[1];
  puVar2 = puVar3 + iVar5;
  *puVar6 = *puVar3;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar2[1];
  puVar3 = puVar2 + iVar5;
  *puVar6 = *puVar2;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar3[1];
  puVar2 = puVar3 + iVar5;
  *puVar6 = *puVar3;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar2[1];
  puVar3 = puVar2 + iVar5;
  *puVar6 = *puVar2;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar3[1];
  puVar2 = puVar3 + iVar5;
  *puVar6 = *puVar3;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar2[1];
  puVar3 = puVar2 + iVar5;
  *puVar6 = *puVar2;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar3[1];
  puVar2 = puVar3 + iVar5;
  *puVar6 = *puVar3;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar2[1];
  puVar3 = puVar2 + iVar5;
  *puVar6 = *puVar2;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar3[1];
  puVar2 = puVar3 + iVar5;
  *puVar6 = *puVar3;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar2[1];
  puVar3 = puVar2 + iVar5;
  *puVar6 = *puVar2;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar3[1];
  puVar2 = puVar3 + iVar5;
  *puVar6 = *puVar3;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar2[1];
  puVar3 = puVar2 + iVar5;
  *puVar6 = *puVar2;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar3[1];
  puVar2 = puVar3 + iVar5;
  *puVar6 = *puVar3;
  puVar6[1] = uVar7;
  puVar6 = puVar6 + iVar5;
  uVar7 = puVar2[1];
  *puVar6 = *puVar2;
  puVar6[1] = uVar7;
  uVar7 = (puVar2 + iVar5)[1];
  puVar6[iVar5] = puVar2[iVar5];
  (puVar6 + iVar5)[1] = uVar7;
  return;
}



// ==== 802886b0  FUN_802886b0 ====

void FUN_802886b0(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  uint local_18;
  int local_14;
  
  while( true ) {
    param_2 = param_2 + -1;
    if (param_2 == 0) break;
    pcVar2 = (char *)(param_1 + (*(int *)(param_1 + 0x2dc) - param_2) * 2 + 0x1324);
    iVar1 = (int)*pcVar2;
    iVar3 = (int)pcVar2[1];
    local_18 = iVar3 * 8 + iVar1 * 8 * (int)*(short *)(param_1 + 0x218);
    local_14 = iVar3 * 0x10 + iVar1 * 0x10 * (int)*(short *)(param_1 + 0x21a);
    zz_0288124_(&local_18,(int *)(param_1 + 0x20c),(int *)(param_1 + 0x21c));
  }
  return;
}



// ==== 8028876c  FUN_8028876c ====

/* WARNING: Removing unreachable block (ram,0x80288814) */
/* WARNING: Removing unreachable block (ram,0x8028881c) */
/* WARNING: Removing unreachable block (ram,0x80288824) */
/* WARNING: Removing unreachable block (ram,0x80288858) */
/* WARNING: Removing unreachable block (ram,0x802887c4) */
/* WARNING: Removing unreachable block (ram,0x802887d8) */
/* WARNING: Removing unreachable block (ram,0x8028882c) */
/* WARNING: Removing unreachable block (ram,0x80288828) */
/* WARNING: Removing unreachable block (ram,0x802888f4) */
/* WARNING: Removing unreachable block (ram,0x802887d0) */
/* WARNING: Removing unreachable block (ram,0x802888f0) */
/* WARNING: Removing unreachable block (ram,0x80288820) */
/* WARNING: Removing unreachable block (ram,0x802887c8) */
/* WARNING: Removing unreachable block (ram,0x802888c8) */
/* WARNING: Removing unreachable block (ram,0x80288818) */
/* WARNING: Removing unreachable block (ram,0x80288918) */
/* WARNING: Removing unreachable block (ram,0x802888ec) */
/* WARNING: Removing unreachable block (ram,0x802888e8) */
/* WARNING: Removing unreachable block (ram,0x802888e4) */
/* WARNING: Removing unreachable block (ram,0x802888e0) */
/* WARNING: Removing unreachable block (ram,0x802888a0) */
/* WARNING: Removing unreachable block (ram,0x802887cc) */
/* WARNING: Removing unreachable block (ram,0x80288a2c) */
/* WARNING: Removing unreachable block (ram,0x802887c0) */
/* WARNING: Removing unreachable block (ram,0x802887bc) */
/* WARNING: Removing unreachable block (ram,0x8028889c) */
/* WARNING: Removing unreachable block (ram,0x80288a04) */
/* WARNING: Removing unreachable block (ram,0x802888c4) */
/* WARNING: Removing unreachable block (ram,0x80288890) */
/* WARNING: Removing unreachable block (ram,0x802889e0) */
/* WARNING: Removing unreachable block (ram,0x80288888) */
/* WARNING: Removing unreachable block (ram,0x80288a34) */
/* WARNING: Removing unreachable block (ram,0x802888dc) */
/* WARNING: Removing unreachable block (ram,0x80288a28) */
/* WARNING: Removing unreachable block (ram,0x80288a00) */
/* WARNING: Removing unreachable block (ram,0x802888d0) */
/* WARNING: Removing unreachable block (ram,0x802889e4) */
/* WARNING: Removing unreachable block (ram,0x802888cc) */
/* WARNING: Removing unreachable block (ram,0x80288898) */
/* WARNING: Removing unreachable block (ram,0x802889b8) */
/* WARNING: Removing unreachable block (ram,0x802889b4) */
/* WARNING: Removing unreachable block (ram,0x80288894) */
/* WARNING: Removing unreachable block (ram,0x8028888c) */
/* WARNING: Removing unreachable block (ram,0x80288884) */
/* WARNING: Removing unreachable block (ram,0x80288958) */
/* WARNING: Removing unreachable block (ram,0x80288960) */
/* WARNING: Removing unreachable block (ram,0x80288980) */
/* WARNING: Removing unreachable block (ram,0x8028898c) */
/* WARNING: Removing unreachable block (ram,0x802889c8) */
/* WARNING: Removing unreachable block (ram,0x802889dc) */
/* WARNING: Removing unreachable block (ram,0x80288954) */
/* WARNING: Removing unreachable block (ram,0x80288988) */
/* WARNING: Removing unreachable block (ram,0x802889f8) */
/* WARNING: Removing unreachable block (ram,0x80288ab8) */
/* WARNING: Removing unreachable block (ram,0x802889bc) */
/* WARNING: Removing unreachable block (ram,0x802889fc) */
/* WARNING: Removing unreachable block (ram,0x80288b08) */
/* WARNING: Removing unreachable block (ram,0x80288a90) */
/* WARNING: Removing unreachable block (ram,0x80288950) */
/* WARNING: Removing unreachable block (ram,0x80288a5c) */
/* WARNING: Removing unreachable block (ram,0x80288ad0) */
/* WARNING: Removing unreachable block (ram,0x80288a58) */
/* WARNING: Removing unreachable block (ram,0x80288adc) */
/* WARNING: Removing unreachable block (ram,0x80288a8c) */
/* WARNING: Removing unreachable block (ram,0x80288ae8) */
/* WARNING: Removing unreachable block (ram,0x80288a70) */
/* WARNING: Removing unreachable block (ram,0x80288b30) */
/* WARNING: Removing unreachable block (ram,0x80288a88) */
/* WARNING: Removing unreachable block (ram,0x80288a60) */
/* WARNING: Removing unreachable block (ram,0x80288b2c) */
/* WARNING: Removing unreachable block (ram,0x80288afc) */
/* WARNING: Removing unreachable block (ram,0x80288ad4) */
/* WARNING: Removing unreachable block (ram,0x80288abc) */
/* WARNING: Removing unreachable block (ram,0x80288a6c) */
/* WARNING: Removing unreachable block (ram,0x80288b38) */
/* WARNING: Removing unreachable block (ram,0x80288b34) */
/* WARNING: Removing unreachable block (ram,0x80288b04) */
/* WARNING: Removing unreachable block (ram,0x80288b00) */
/* WARNING: Removing unreachable block (ram,0x80288ae4) */
/* WARNING: Removing unreachable block (ram,0x80288ae0) */
/* WARNING: Removing unreachable block (ram,0x80288ad8) */
/* WARNING: Removing unreachable block (ram,0x80288acc) */
/* WARNING: Removing unreachable block (ram,0x80288ac4) */
/* WARNING: Removing unreachable block (ram,0x80288ac0) */
/* WARNING: Removing unreachable block (ram,0x80288a94) */
/* WARNING: Removing unreachable block (ram,0x80288a74) */
/* WARNING: Removing unreachable block (ram,0x80288a68) */
/* WARNING: Removing unreachable block (ram,0x80288a64) */
/* WARNING: Removing unreachable block (ram,0x8028877c) */
/* WARNING: Removing unreachable block (ram,0x802889cc) */
/* WARNING: Removing unreachable block (ram,0x80288964) */
/* WARNING: Removing unreachable block (ram,0x8028895c) */
/* WARNING: Removing unreachable block (ram,0x8028896c) */
/* WARNING: Removing unreachable block (ram,0x802889d4) */
/* WARNING: Removing unreachable block (ram,0x80288984) */
/* WARNING: Removing unreachable block (ram,0x80288968) */
/* WARNING: Removing unreachable block (ram,0x802889b0) */
/* WARNING: Removing unreachable block (ram,0x802889d0) */
/* WARNING: Removing unreachable block (ram,0x802889d8) */
/* WARNING: Removing unreachable block (ram,0x802888d8) */
/* WARNING: Removing unreachable block (ram,0x80288a30) */
/* WARNING: Removing unreachable block (ram,0x802887fc) */
/* WARNING: Removing unreachable block (ram,0x80288800) */
/* WARNING: Removing unreachable block (ram,0x80288804) */
/* WARNING: Removing unreachable block (ram,0x80288808) */
/* WARNING: Removing unreachable block (ram,0x8028891c) */
/* WARNING: Removing unreachable block (ram,0x80288920) */
/* WARNING: Removing unreachable block (ram,0x80288924) */
/* WARNING: Removing unreachable block (ram,0x802887d4) */
/* WARNING: Removing unreachable block (ram,0x8028885c) */
/* WARNING: Removing unreachable block (ram,0x80288830) */
/* WARNING: Removing unreachable block (ram,0x80288860) */
/* WARNING: Removing unreachable block (ram,0x80288854) */

void FUN_8028876c(int param_1,int param_2,int param_3)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  char cVar8;
  char cVar9;
  char cVar10;
  char cVar11;
  char cVar12;
  char cVar13;
  char cVar14;
  short sVar15;
  short sVar16;
  short sVar17;
  short sVar18;
  short sVar19;
  short sVar20;
  short sVar21;
  char *pcVar22;
  short *psVar23;
  int iVar24;
  char *pcVar25;
  short *psVar26;
  undefined4 *puVar27;
  int iVar28;
  int iVar29;
  
  psVar26 = *(short **)(param_1 + 4);
  pcVar25 = *(char **)(param_1 + 8);
  puVar27 = (undefined4 *)(param_2 + 4);
  pcVar22 = *(char **)(param_1 + 0xc);
  iVar28 = 0;
  do {
    psVar23 = (short *)*puVar27;
    iVar24 = puVar27[1];
    puVar27 = puVar27 + 2;
    if (param_3 < 0) {
      if (((uint)psVar23 & 0x1f) == 0) {
        iVar29 = 4;
        do {
          dataCacheBlockClearToZero(psVar23);
          cVar7 = pcVar25[1];
          cVar8 = pcVar22[1];
          cVar1 = pcVar25[2];
          cVar9 = pcVar25[3];
          cVar2 = pcVar22[2];
          cVar10 = pcVar22[3];
          cVar3 = pcVar25[4];
          cVar11 = pcVar25[5];
          cVar4 = pcVar22[4];
          cVar12 = pcVar22[5];
          cVar5 = pcVar25[6];
          cVar13 = pcVar25[7];
          cVar6 = pcVar22[6];
          cVar14 = pcVar22[7];
          sVar18 = psVar26[1];
          sVar15 = psVar26[2];
          sVar19 = psVar26[3];
          sVar16 = psVar26[4];
          sVar20 = psVar26[5];
          sVar17 = psVar26[6];
          sVar21 = psVar26[7];
          *psVar23 = (short)(((double)((longlong)(double)*pcVar25 * 0x3ff0000000000000) +
                              (double)((longlong)(double)*pcVar22 * 0x3ff0000000000000) + 1.0 +
                             (double)((longlong)(double)*psVar26 * 0x3ff0000000000000)) * 1.0);
          psVar23[1] = (short)(((double)((longlong)(double)cVar7 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar8 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar18 * 0x3ff0000000000000)) * 1.0);
          psVar23[1] = (short)(((double)((longlong)(double)cVar1 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar2 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar15 * 0x3ff0000000000000)) * 1.0);
          psVar23[2] = (short)(((double)((longlong)(double)cVar9 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar10 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar19 * 0x3ff0000000000000)) * 1.0);
          psVar23[2] = (short)(((double)((longlong)(double)cVar3 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar4 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar16 * 0x3ff0000000000000)) * 1.0);
          psVar23[3] = (short)(((double)((longlong)(double)cVar11 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar12 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar20 * 0x3ff0000000000000)) * 1.0);
          psVar23[3] = (short)(((double)((longlong)(double)cVar5 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar6 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar17 * 0x3ff0000000000000)) * 1.0);
          psVar23[4] = (short)(((double)((longlong)(double)cVar13 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar14 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar21 * 0x3ff0000000000000)) * 1.0);
          psVar23 = (short *)((int)psVar23 + iVar24);
          dataCacheBlockClearToZero(psVar23);
          cVar7 = pcVar25[9];
          cVar8 = pcVar22[9];
          cVar1 = pcVar25[10];
          cVar9 = pcVar25[0xb];
          cVar2 = pcVar22[10];
          cVar10 = pcVar22[0xb];
          cVar3 = pcVar25[0xc];
          cVar11 = pcVar25[0xd];
          cVar4 = pcVar22[0xc];
          cVar12 = pcVar22[0xd];
          cVar5 = pcVar25[0xe];
          cVar13 = pcVar25[0xf];
          cVar6 = pcVar22[0xe];
          cVar14 = pcVar22[0xf];
          sVar18 = psVar26[9];
          sVar15 = psVar26[10];
          sVar19 = psVar26[0xb];
          sVar16 = psVar26[0xc];
          sVar20 = psVar26[0xd];
          sVar17 = psVar26[0xe];
          sVar21 = psVar26[0xf];
          *psVar23 = (short)(((double)((longlong)(double)pcVar25[8] * 0x3ff0000000000000) +
                              (double)((longlong)(double)pcVar22[8] * 0x3ff0000000000000) + 1.0 +
                             (double)((longlong)(double)psVar26[8] * 0x3ff0000000000000)) * 1.0);
          psVar23[1] = (short)(((double)((longlong)(double)cVar7 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar8 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar18 * 0x3ff0000000000000)) * 1.0);
          psVar23[1] = (short)(((double)((longlong)(double)cVar1 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar2 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar15 * 0x3ff0000000000000)) * 1.0);
          psVar23[2] = (short)(((double)((longlong)(double)cVar9 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar10 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar19 * 0x3ff0000000000000)) * 1.0);
          psVar23[2] = (short)(((double)((longlong)(double)cVar3 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar4 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar16 * 0x3ff0000000000000)) * 1.0);
          psVar23[3] = (short)(((double)((longlong)(double)cVar11 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar12 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar20 * 0x3ff0000000000000)) * 1.0);
          psVar23[3] = (short)(((double)((longlong)(double)cVar5 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar6 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar17 * 0x3ff0000000000000)) * 1.0);
          psVar23[4] = (short)(((double)((longlong)(double)cVar13 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar14 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar21 * 0x3ff0000000000000)) * 1.0);
          psVar23 = (short *)((int)psVar23 + iVar24);
          pcVar25 = pcVar25 + 0x10;
          pcVar22 = pcVar22 + 0x10;
          psVar26 = psVar26 + 0x10;
          iVar29 = iVar29 + -1;
        } while (iVar29 != 0);
      }
      else {
        iVar29 = 4;
        do {
          cVar7 = pcVar25[1];
          cVar8 = pcVar22[1];
          cVar1 = pcVar25[2];
          cVar9 = pcVar25[3];
          cVar2 = pcVar22[2];
          cVar10 = pcVar22[3];
          cVar3 = pcVar25[4];
          cVar11 = pcVar25[5];
          cVar4 = pcVar22[4];
          cVar12 = pcVar22[5];
          cVar5 = pcVar25[6];
          cVar13 = pcVar25[7];
          cVar6 = pcVar22[6];
          cVar14 = pcVar22[7];
          sVar18 = psVar26[1];
          sVar15 = psVar26[2];
          sVar19 = psVar26[3];
          sVar16 = psVar26[4];
          sVar20 = psVar26[5];
          sVar17 = psVar26[6];
          sVar21 = psVar26[7];
          *psVar23 = (short)(((double)((longlong)(double)*pcVar25 * 0x3ff0000000000000) +
                              (double)((longlong)(double)*pcVar22 * 0x3ff0000000000000) + 1.0 +
                             (double)((longlong)(double)*psVar26 * 0x3ff0000000000000)) * 1.0);
          psVar23[1] = (short)(((double)((longlong)(double)cVar7 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar8 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar18 * 0x3ff0000000000000)) * 1.0);
          psVar23[1] = (short)(((double)((longlong)(double)cVar1 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar2 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar15 * 0x3ff0000000000000)) * 1.0);
          psVar23[2] = (short)(((double)((longlong)(double)cVar9 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar10 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar19 * 0x3ff0000000000000)) * 1.0);
          psVar23[2] = (short)(((double)((longlong)(double)cVar3 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar4 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar16 * 0x3ff0000000000000)) * 1.0);
          psVar23[3] = (short)(((double)((longlong)(double)cVar11 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar12 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar20 * 0x3ff0000000000000)) * 1.0);
          psVar23[3] = (short)(((double)((longlong)(double)cVar5 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar6 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar17 * 0x3ff0000000000000)) * 1.0);
          psVar23[4] = (short)(((double)((longlong)(double)cVar13 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar14 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar21 * 0x3ff0000000000000)) * 1.0);
          psVar23 = (short *)((int)psVar23 + iVar24);
          cVar7 = pcVar25[9];
          cVar8 = pcVar22[9];
          cVar1 = pcVar25[10];
          cVar9 = pcVar25[0xb];
          cVar2 = pcVar22[10];
          cVar10 = pcVar22[0xb];
          cVar3 = pcVar25[0xc];
          cVar11 = pcVar25[0xd];
          cVar4 = pcVar22[0xc];
          cVar12 = pcVar22[0xd];
          cVar5 = pcVar25[0xe];
          cVar13 = pcVar25[0xf];
          cVar6 = pcVar22[0xe];
          cVar14 = pcVar22[0xf];
          sVar18 = psVar26[9];
          sVar15 = psVar26[10];
          sVar19 = psVar26[0xb];
          sVar16 = psVar26[0xc];
          sVar20 = psVar26[0xd];
          sVar17 = psVar26[0xe];
          sVar21 = psVar26[0xf];
          *psVar23 = (short)(((double)((longlong)(double)pcVar25[8] * 0x3ff0000000000000) +
                              (double)((longlong)(double)pcVar22[8] * 0x3ff0000000000000) + 1.0 +
                             (double)((longlong)(double)psVar26[8] * 0x3ff0000000000000)) * 1.0);
          psVar23[1] = (short)(((double)((longlong)(double)cVar7 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar8 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar18 * 0x3ff0000000000000)) * 1.0);
          psVar23[1] = (short)(((double)((longlong)(double)cVar1 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar2 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar15 * 0x3ff0000000000000)) * 1.0);
          psVar23[2] = (short)(((double)((longlong)(double)cVar9 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar10 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar19 * 0x3ff0000000000000)) * 1.0);
          psVar23[2] = (short)(((double)((longlong)(double)cVar3 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar4 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar16 * 0x3ff0000000000000)) * 1.0);
          psVar23[3] = (short)(((double)((longlong)(double)cVar11 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar12 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar20 * 0x3ff0000000000000)) * 1.0);
          psVar23[3] = (short)(((double)((longlong)(double)cVar5 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar6 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar17 * 0x3ff0000000000000)) * 1.0);
          psVar23[4] = (short)(((double)((longlong)(double)cVar13 * 0x3ff0000000000000) +
                                (double)((longlong)(double)cVar14 * 0x3ff0000000000000) + 1.0 +
                               (double)((longlong)(double)sVar21 * 0x3ff0000000000000)) * 1.0);
          psVar23 = (short *)((int)psVar23 + iVar24);
          pcVar25 = pcVar25 + 0x10;
          pcVar22 = pcVar22 + 0x10;
          psVar26 = psVar26 + 0x10;
          iVar29 = iVar29 + -1;
        } while (iVar29 != 0);
      }
    }
    else if (((uint)psVar23 & 0x1f) == 0) {
      iVar29 = 4;
      psVar26 = psVar26 + 0x40;
      do {
        dataCacheBlockClearToZero(psVar23);
        cVar7 = pcVar25[1];
        cVar8 = pcVar22[1];
        cVar1 = pcVar25[2];
        cVar9 = pcVar25[3];
        cVar2 = pcVar22[2];
        cVar10 = pcVar22[3];
        cVar3 = pcVar25[4];
        cVar11 = pcVar25[5];
        cVar4 = pcVar22[4];
        cVar12 = pcVar22[5];
        cVar5 = pcVar25[6];
        cVar13 = pcVar25[7];
        cVar6 = pcVar22[6];
        cVar14 = pcVar22[7];
        *psVar23 = (short)(((double)((longlong)(double)*pcVar25 * 0x3ff0000000000000) +
                            (double)((longlong)(double)*pcVar22 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[1] = (short)(((double)((longlong)(double)cVar7 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar8 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[1] = (short)(((double)((longlong)(double)cVar1 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar2 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[2] = (short)(((double)((longlong)(double)cVar9 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar10 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[2] = (short)(((double)((longlong)(double)cVar3 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar4 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[3] = (short)(((double)((longlong)(double)cVar11 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar12 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[3] = (short)(((double)((longlong)(double)cVar5 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar6 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[4] = (short)(((double)((longlong)(double)cVar13 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar14 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23 = (short *)((int)psVar23 + iVar24);
        dataCacheBlockClearToZero(psVar23);
        cVar7 = pcVar25[9];
        cVar8 = pcVar22[9];
        cVar1 = pcVar25[10];
        cVar9 = pcVar25[0xb];
        cVar2 = pcVar22[10];
        cVar10 = pcVar22[0xb];
        cVar3 = pcVar25[0xc];
        cVar11 = pcVar25[0xd];
        cVar4 = pcVar22[0xc];
        cVar12 = pcVar22[0xd];
        cVar5 = pcVar25[0xe];
        cVar13 = pcVar25[0xf];
        cVar6 = pcVar22[0xe];
        cVar14 = pcVar22[0xf];
        *psVar23 = (short)(((double)((longlong)(double)pcVar25[8] * 0x3ff0000000000000) +
                            (double)((longlong)(double)pcVar22[8] * 0x3ff0000000000000) + 1.0) * 1.0
                          );
        psVar23[1] = (short)(((double)((longlong)(double)cVar7 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar8 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[1] = (short)(((double)((longlong)(double)cVar1 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar2 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[2] = (short)(((double)((longlong)(double)cVar9 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar10 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[2] = (short)(((double)((longlong)(double)cVar3 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar4 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[3] = (short)(((double)((longlong)(double)cVar11 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar12 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[3] = (short)(((double)((longlong)(double)cVar5 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar6 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[4] = (short)(((double)((longlong)(double)cVar13 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar14 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23 = (short *)((int)psVar23 + iVar24);
        pcVar25 = pcVar25 + 0x10;
        pcVar22 = pcVar22 + 0x10;
        iVar29 = iVar29 + -1;
      } while (iVar29 != 0);
    }
    else {
      iVar29 = 4;
      psVar26 = psVar26 + 0x40;
      do {
        cVar7 = pcVar25[1];
        cVar8 = pcVar22[1];
        cVar1 = pcVar25[2];
        cVar9 = pcVar25[3];
        cVar2 = pcVar22[2];
        cVar10 = pcVar22[3];
        cVar3 = pcVar25[4];
        cVar11 = pcVar25[5];
        cVar4 = pcVar22[4];
        cVar12 = pcVar22[5];
        cVar5 = pcVar25[6];
        cVar13 = pcVar25[7];
        cVar6 = pcVar22[6];
        cVar14 = pcVar22[7];
        *psVar23 = (short)(((double)((longlong)(double)*pcVar25 * 0x3ff0000000000000) +
                            (double)((longlong)(double)*pcVar22 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[1] = (short)(((double)((longlong)(double)cVar7 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar8 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[1] = (short)(((double)((longlong)(double)cVar1 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar2 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[2] = (short)(((double)((longlong)(double)cVar9 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar10 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[2] = (short)(((double)((longlong)(double)cVar3 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar4 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[3] = (short)(((double)((longlong)(double)cVar11 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar12 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[3] = (short)(((double)((longlong)(double)cVar5 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar6 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[4] = (short)(((double)((longlong)(double)cVar13 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar14 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23 = (short *)((int)psVar23 + iVar24);
        cVar7 = pcVar25[9];
        cVar8 = pcVar22[9];
        cVar1 = pcVar25[10];
        cVar9 = pcVar25[0xb];
        cVar2 = pcVar22[10];
        cVar10 = pcVar22[0xb];
        cVar3 = pcVar25[0xc];
        cVar11 = pcVar25[0xd];
        cVar4 = pcVar22[0xc];
        cVar12 = pcVar22[0xd];
        cVar5 = pcVar25[0xe];
        cVar13 = pcVar25[0xf];
        cVar6 = pcVar22[0xe];
        cVar14 = pcVar22[0xf];
        *psVar23 = (short)(((double)((longlong)(double)pcVar25[8] * 0x3ff0000000000000) +
                            (double)((longlong)(double)pcVar22[8] * 0x3ff0000000000000) + 1.0) * 1.0
                          );
        psVar23[1] = (short)(((double)((longlong)(double)cVar7 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar8 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[1] = (short)(((double)((longlong)(double)cVar1 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar2 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[2] = (short)(((double)((longlong)(double)cVar9 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar10 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[2] = (short)(((double)((longlong)(double)cVar3 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar4 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[3] = (short)(((double)((longlong)(double)cVar11 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar12 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[3] = (short)(((double)((longlong)(double)cVar5 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar6 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23[4] = (short)(((double)((longlong)(double)cVar13 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar14 * 0x3ff0000000000000) + 1.0) * 1.0);
        psVar23 = (short *)((int)psVar23 + iVar24);
        pcVar25 = pcVar25 + 0x10;
        pcVar22 = pcVar22 + 0x10;
        iVar29 = iVar29 + -1;
      } while (iVar29 != 0);
    }
    iVar28 = iVar28 + 1;
    param_3 = param_3 << 1;
  } while (iVar28 < 6);
  return;
}



// ==== 80288b64  FUN_80288b64 ====

/* WARNING: Removing unreachable block (ram,0x80288ca0) */
/* WARNING: Removing unreachable block (ram,0x80288ccc) */
/* WARNING: Removing unreachable block (ram,0x80288cf4) */
/* WARNING: Removing unreachable block (ram,0x80288c98) */
/* WARNING: Removing unreachable block (ram,0x80288ce4) */
/* WARNING: Removing unreachable block (ram,0x80288ca8) */
/* WARNING: Removing unreachable block (ram,0x80288d50) */
/* WARNING: Removing unreachable block (ram,0x80288cd0) */
/* WARNING: Removing unreachable block (ram,0x80288d84) */
/* WARNING: Removing unreachable block (ram,0x80288d44) */
/* WARNING: Removing unreachable block (ram,0x80288d14) */
/* WARNING: Removing unreachable block (ram,0x80288c94) */
/* WARNING: Removing unreachable block (ram,0x80288c9c) */
/* WARNING: Removing unreachable block (ram,0x80288ca4) */
/* WARNING: Removing unreachable block (ram,0x80288cec) */
/* WARNING: Removing unreachable block (ram,0x80288cf8) */
/* WARNING: Removing unreachable block (ram,0x80288d94) */
/* WARNING: Removing unreachable block (ram,0x80288cf0) */
/* WARNING: Removing unreachable block (ram,0x80288d80) */
/* WARNING: Removing unreachable block (ram,0x80288cdc) */
/* WARNING: Removing unreachable block (ram,0x80288d3c) */
/* WARNING: Removing unreachable block (ram,0x80288d38) */
/* WARNING: Removing unreachable block (ram,0x80288d40) */
/* WARNING: Removing unreachable block (ram,0x80288db8) */
/* WARNING: Removing unreachable block (ram,0x80288db4) */
/* WARNING: Removing unreachable block (ram,0x80288db0) */
/* WARNING: Removing unreachable block (ram,0x80288dac) */
/* WARNING: Removing unreachable block (ram,0x80288d98) */
/* WARNING: Removing unreachable block (ram,0x80288d90) */
/* WARNING: Removing unreachable block (ram,0x80288d8c) */
/* WARNING: Removing unreachable block (ram,0x80288d88) */
/* WARNING: Removing unreachable block (ram,0x80288d7c) */
/* WARNING: Removing unreachable block (ram,0x80288d74) */
/* WARNING: Removing unreachable block (ram,0x80288d70) */
/* WARNING: Removing unreachable block (ram,0x80288d6c) */
/* WARNING: Removing unreachable block (ram,0x80288d68) */
/* WARNING: Removing unreachable block (ram,0x80288d54) */
/* WARNING: Removing unreachable block (ram,0x80288d4c) */
/* WARNING: Removing unreachable block (ram,0x80288d48) */
/* WARNING: Removing unreachable block (ram,0x80288ce8) */
/* WARNING: Removing unreachable block (ram,0x80288d10) */
/* WARNING: Removing unreachable block (ram,0x80288cc4) */
/* WARNING: Removing unreachable block (ram,0x80288ce0) */
/* WARNING: Removing unreachable block (ram,0x80288cac) */
/* WARNING: Removing unreachable block (ram,0x80288cc8) */
/* WARNING: Removing unreachable block (ram,0x80288cb0) */
/* WARNING: Removing unreachable block (ram,0x80288d0c) */
/* WARNING: Removing unreachable block (ram,0x80288d18) */

void FUN_80288b64(int param_1,int param_2,int param_3)

{
  char cVar1;
  char cVar2;
  char cVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  short sVar8;
  short sVar9;
  short sVar10;
  short sVar11;
  short sVar12;
  short sVar13;
  short sVar14;
  char *pcVar15;
  char *pcVar16;
  short *psVar17;
  undefined4 *puVar18;
  uint uVar19;
  char *pcVar20;
  int iVar21;
  int iVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 uVar25;
  
  psVar17 = *(short **)(param_1 + 4);
  puVar18 = (undefined4 *)(param_2 + 4);
  pcVar15 = *(char **)(param_1 + 8);
  iVar21 = 0;
  do {
    pcVar16 = (char *)*puVar18;
    uVar19 = puVar18[1];
    puVar18 = puVar18 + 2;
    if (param_3 < 0) {
      if (((uint)pcVar16 & 0x1f) == 0) {
        iVar22 = 4;
        do {
          dataCacheBlockClearToZero(pcVar16);
          sVar11 = psVar17[1];
          cVar4 = pcVar15[1];
          sVar8 = psVar17[2];
          sVar12 = psVar17[3];
          cVar1 = pcVar15[2];
          cVar5 = pcVar15[3];
          sVar9 = psVar17[4];
          sVar13 = psVar17[5];
          cVar2 = pcVar15[4];
          cVar6 = pcVar15[5];
          sVar10 = psVar17[6];
          sVar14 = psVar17[7];
          cVar3 = pcVar15[6];
          cVar7 = pcVar15[7];
          *pcVar16 = (char)(((double)((longlong)(double)*psVar17 * 0x3ff0000000000000) +
                            (double)((longlong)(double)*pcVar15 * 0x3ff0000000000000)) * 1.0);
          pcVar16[1] = (char)(((double)((longlong)(double)sVar11 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar4 * 0x3ff0000000000000)) * 1.0);
          pcVar16[2] = (char)(((double)((longlong)(double)sVar8 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar1 * 0x3ff0000000000000)) * 1.0);
          pcVar16[3] = (char)(((double)((longlong)(double)sVar12 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar5 * 0x3ff0000000000000)) * 1.0);
          pcVar16[4] = (char)(((double)((longlong)(double)sVar9 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar2 * 0x3ff0000000000000)) * 1.0);
          pcVar16[5] = (char)(((double)((longlong)(double)sVar13 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar6 * 0x3ff0000000000000)) * 1.0);
          pcVar16[6] = (char)(((double)((longlong)(double)sVar10 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar3 * 0x3ff0000000000000)) * 1.0);
          pcVar16[7] = (char)(((double)((longlong)(double)sVar14 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar7 * 0x3ff0000000000000)) * 1.0);
          pcVar16 = pcVar16 + uVar19;
          dataCacheBlockClearToZero(pcVar16);
          sVar11 = psVar17[9];
          cVar4 = pcVar15[9];
          sVar8 = psVar17[10];
          sVar12 = psVar17[0xb];
          cVar1 = pcVar15[10];
          cVar5 = pcVar15[0xb];
          sVar9 = psVar17[0xc];
          sVar13 = psVar17[0xd];
          cVar2 = pcVar15[0xc];
          cVar6 = pcVar15[0xd];
          sVar10 = psVar17[0xe];
          sVar14 = psVar17[0xf];
          cVar3 = pcVar15[0xe];
          cVar7 = pcVar15[0xf];
          *pcVar16 = (char)(((double)((longlong)(double)psVar17[8] * 0x3ff0000000000000) +
                            (double)((longlong)(double)pcVar15[8] * 0x3ff0000000000000)) * 1.0);
          pcVar16[1] = (char)(((double)((longlong)(double)sVar11 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar4 * 0x3ff0000000000000)) * 1.0);
          pcVar16[2] = (char)(((double)((longlong)(double)sVar8 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar1 * 0x3ff0000000000000)) * 1.0);
          pcVar16[3] = (char)(((double)((longlong)(double)sVar12 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar5 * 0x3ff0000000000000)) * 1.0);
          pcVar16[4] = (char)(((double)((longlong)(double)sVar9 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar2 * 0x3ff0000000000000)) * 1.0);
          pcVar16[5] = (char)(((double)((longlong)(double)sVar13 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar6 * 0x3ff0000000000000)) * 1.0);
          pcVar16[6] = (char)(((double)((longlong)(double)sVar10 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar3 * 0x3ff0000000000000)) * 1.0);
          pcVar16[7] = (char)(((double)((longlong)(double)sVar14 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar7 * 0x3ff0000000000000)) * 1.0);
          pcVar16 = pcVar16 + uVar19;
          pcVar15 = pcVar15 + 0x10;
          psVar17 = psVar17 + 0x10;
          iVar22 = iVar22 + -1;
        } while (iVar22 != 0);
      }
      else {
        iVar22 = 4;
        do {
          sVar11 = psVar17[1];
          cVar4 = pcVar15[1];
          sVar8 = psVar17[2];
          sVar12 = psVar17[3];
          cVar1 = pcVar15[2];
          cVar5 = pcVar15[3];
          sVar9 = psVar17[4];
          sVar13 = psVar17[5];
          cVar2 = pcVar15[4];
          cVar6 = pcVar15[5];
          sVar10 = psVar17[6];
          sVar14 = psVar17[7];
          cVar3 = pcVar15[6];
          cVar7 = pcVar15[7];
          *pcVar16 = (char)(((double)((longlong)(double)*psVar17 * 0x3ff0000000000000) +
                            (double)((longlong)(double)*pcVar15 * 0x3ff0000000000000)) * 1.0);
          pcVar16[1] = (char)(((double)((longlong)(double)sVar11 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar4 * 0x3ff0000000000000)) * 1.0);
          pcVar16[2] = (char)(((double)((longlong)(double)sVar8 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar1 * 0x3ff0000000000000)) * 1.0);
          pcVar16[3] = (char)(((double)((longlong)(double)sVar12 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar5 * 0x3ff0000000000000)) * 1.0);
          pcVar16[4] = (char)(((double)((longlong)(double)sVar9 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar2 * 0x3ff0000000000000)) * 1.0);
          pcVar16[5] = (char)(((double)((longlong)(double)sVar13 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar6 * 0x3ff0000000000000)) * 1.0);
          pcVar16[6] = (char)(((double)((longlong)(double)sVar10 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar3 * 0x3ff0000000000000)) * 1.0);
          pcVar16[7] = (char)(((double)((longlong)(double)sVar14 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar7 * 0x3ff0000000000000)) * 1.0);
          pcVar16 = pcVar16 + uVar19;
          sVar11 = psVar17[9];
          cVar4 = pcVar15[9];
          sVar8 = psVar17[10];
          sVar12 = psVar17[0xb];
          cVar1 = pcVar15[10];
          cVar5 = pcVar15[0xb];
          sVar9 = psVar17[0xc];
          sVar13 = psVar17[0xd];
          cVar2 = pcVar15[0xc];
          cVar6 = pcVar15[0xd];
          sVar10 = psVar17[0xe];
          sVar14 = psVar17[0xf];
          cVar3 = pcVar15[0xe];
          cVar7 = pcVar15[0xf];
          *pcVar16 = (char)(((double)((longlong)(double)psVar17[8] * 0x3ff0000000000000) +
                            (double)((longlong)(double)pcVar15[8] * 0x3ff0000000000000)) * 1.0);
          pcVar16[1] = (char)(((double)((longlong)(double)sVar11 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar4 * 0x3ff0000000000000)) * 1.0);
          pcVar16[2] = (char)(((double)((longlong)(double)sVar8 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar1 * 0x3ff0000000000000)) * 1.0);
          pcVar16[3] = (char)(((double)((longlong)(double)sVar12 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar5 * 0x3ff0000000000000)) * 1.0);
          pcVar16[4] = (char)(((double)((longlong)(double)sVar9 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar2 * 0x3ff0000000000000)) * 1.0);
          pcVar16[5] = (char)(((double)((longlong)(double)sVar13 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar6 * 0x3ff0000000000000)) * 1.0);
          pcVar16[6] = (char)(((double)((longlong)(double)sVar10 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar3 * 0x3ff0000000000000)) * 1.0);
          pcVar16[7] = (char)(((double)((longlong)(double)sVar14 * 0x3ff0000000000000) +
                              (double)((longlong)(double)cVar7 * 0x3ff0000000000000)) * 1.0);
          pcVar16 = pcVar16 + uVar19;
          pcVar15 = pcVar15 + 0x10;
          psVar17 = psVar17 + 0x10;
          iVar22 = iVar22 + -1;
        } while (iVar22 != 0);
      }
    }
    else {
      psVar17 = psVar17 + 0x40;
      if (((uint)pcVar16 & 0x1f) == 0) {
        dataCacheBlockClearToZero(pcVar16);
        iVar22 = (uVar19 >> 3) * 8;
        pcVar20 = pcVar16 + iVar22;
        uVar23 = *(undefined8 *)(pcVar15 + 8);
        uVar24 = *(undefined8 *)(pcVar15 + 0x10);
        uVar25 = *(undefined8 *)(pcVar15 + 0x18);
        *(undefined8 *)pcVar16 = *(undefined8 *)pcVar15;
        dataCacheBlockClearToZero(pcVar20);
        *(undefined8 *)pcVar20 = uVar23;
        pcVar20 = pcVar20 + iVar22;
        dataCacheBlockClearToZero(pcVar20);
        *(undefined8 *)pcVar20 = uVar24;
        pcVar20 = pcVar20 + iVar22;
        dataCacheBlockClearToZero(pcVar20);
        *(undefined8 *)pcVar20 = uVar25;
        pcVar20 = pcVar20 + iVar22;
        dataCacheBlockClearToZero(pcVar20);
        uVar23 = *(undefined8 *)(pcVar15 + 0x28);
        uVar24 = *(undefined8 *)(pcVar15 + 0x30);
        uVar25 = *(undefined8 *)(pcVar15 + 0x38);
        *(undefined8 *)pcVar20 = *(undefined8 *)(pcVar15 + 0x20);
        pcVar20 = pcVar20 + iVar22;
        dataCacheBlockClearToZero(pcVar20);
        *(undefined8 *)pcVar20 = uVar23;
        pcVar20 = pcVar20 + iVar22;
        dataCacheBlockClearToZero(pcVar20);
        *(undefined8 *)pcVar20 = uVar24;
        dataCacheBlockClearToZero(pcVar20 + iVar22);
        *(undefined8 *)(pcVar20 + iVar22) = uVar25;
      }
      else {
        iVar22 = (uVar19 >> 3) * 8;
        uVar23 = *(undefined8 *)(pcVar15 + 8);
        pcVar20 = pcVar16 + iVar22;
        uVar24 = *(undefined8 *)(pcVar15 + 0x10);
        uVar25 = *(undefined8 *)(pcVar15 + 0x18);
        *(undefined8 *)pcVar16 = *(undefined8 *)pcVar15;
        *(undefined8 *)pcVar20 = uVar23;
        pcVar20 = pcVar20 + iVar22;
        *(undefined8 *)pcVar20 = uVar24;
        pcVar20 = pcVar20 + iVar22;
        *(undefined8 *)pcVar20 = uVar25;
        pcVar20 = pcVar20 + iVar22;
        uVar23 = *(undefined8 *)(pcVar15 + 0x28);
        uVar24 = *(undefined8 *)(pcVar15 + 0x30);
        uVar25 = *(undefined8 *)(pcVar15 + 0x38);
        *(undefined8 *)pcVar20 = *(undefined8 *)(pcVar15 + 0x20);
        pcVar20 = pcVar20 + iVar22;
        *(undefined8 *)pcVar20 = uVar23;
        *(undefined8 *)(pcVar20 + iVar22) = uVar24;
        *(undefined8 *)(pcVar20 + iVar22 + iVar22) = uVar25;
      }
      pcVar15 = pcVar15 + 0x40;
    }
    iVar21 = iVar21 + 1;
    param_3 = param_3 << 1;
  } while (iVar21 < 6);
  return;
}



// ==== 80288de0  FUN_80288de0 ====

void FUN_80288de0(int param_1,int param_2,int *param_3,int *param_4,int param_5)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  code *pcVar9;
  code *pcVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  
  iVar11 = param_1 + 0xc4;
  uVar2 = *(uint *)(param_1 + 0x174);
  iVar12 = (int)*(short *)(param_4 + 3);
  iVar13 = (int)*(short *)((int)param_4 + 0xe);
  pcVar5 = (char *)(param_1 + *(int *)(param_1 + 0x2dc) * 2 + 0x1324);
  iVar6 = (int)*pcVar5;
  iVar3 = (int)pcVar5[1];
  *param_3 = iVar3 * 8 + iVar6 * 8 * iVar12;
  param_3[1] = iVar3 * 0x10 + iVar6 * 0x10 * iVar13;
  uVar1 = *(uint *)(param_5 + 0x18);
  uVar7 = *(uint *)(param_5 + 0x1c);
  pcVar10 = (code *)(&DAT_8041cfd0)[uVar2 * 4 + ((int)uVar7 / 2 & 1U) * 2 + ((int)uVar1 / 2 & 1U)];
  pcVar9 = (code *)(&DAT_8041cfb0)[uVar2 * 4 + (uVar7 & 1) * 2 + (uVar1 & 1)];
  iVar4 = param_3[1];
  iVar3 = *param_3;
  uVar8 = (int)uVar1 / 2 & 1U & uVar2;
  *(int *)(param_1 + 0xd4) = iVar12;
  *(int *)(param_1 + 0xcc) = param_2;
  iVar3 = iVar3 + ((int)(uVar1 - ((int)uVar1 >> 0x1f)) >> 2) +
                  ((int)(uVar7 - ((int)uVar7 >> 0x1f)) >> 2) * iVar12;
  iVar6 = *param_4 + iVar3;
  *(int *)(param_1 + 0xd8) = iVar6;
  *(uint *)(param_1 + 0xdc) = iVar6 + iVar12 + uVar8;
  (*pcVar10)(iVar11);
  *(int *)(param_1 + 0xcc) = param_2 + 0x40;
  iVar3 = param_4[1] + iVar3;
  *(int *)(param_1 + 0xd8) = iVar3;
  *(uint *)(param_1 + 0xdc) = iVar3 + iVar12 + uVar8;
  (*pcVar10)(iVar11);
  *(int *)(param_1 + 0xd4) = iVar13;
  *(int *)(param_1 + 0xcc) = param_2 + 0x80;
  iVar3 = param_4[2] + iVar4 + ((int)uVar1 >> 1) + ((int)uVar7 >> 1) * iVar13;
  *(int *)(param_1 + 0xd8) = iVar3;
  *(uint *)(param_1 + 0xdc) = iVar13 + (uVar1 & 1 & uVar2) + iVar3;
  (*pcVar9)(iVar11);
  return;
}



// ==== 80288f94  FUN_80288f94 ====

void FUN_80288f94(int param_1)

{
  int local_18;
  int local_14;
  
  FUN_80288de0(param_1,*(int *)(param_1 + 0xf0),&local_18,(int *)(param_1 + 0x20c),param_1 + 0x294);
  FUN_80288de0(param_1,*(int *)(param_1 + 0xf4),&local_18,(int *)(param_1 + 0x21c),param_1 + 0x2b8);
  *(int *)(param_1 + 0xfc) = *(int *)(param_1 + 0x23c) + local_18;
  *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x240) + local_18;
  *(int *)(param_1 + 0x10c) = *(int *)(param_1 + 0x244) + local_14;
  *(int *)(param_1 + 0x114) = *(int *)(param_1 + 0x10c) + 8;
  *(int *)(param_1 + 0x11c) = *(int *)(param_1 + 0x10c) + *(short *)(param_1 + 0x24a) * 8;
  *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x11c) + 8;
  FUN_8028876c(param_1 + 0xe8,param_1 + 0xf8,*(int *)(param_1 + 0x2e8));
  return;
}



// ==== 8028906c  FUN_8028906c ====

void FUN_8028906c(int param_1)

{
  int local_18;
  int local_14;
  
  FUN_80288de0(param_1,*(int *)(param_1 + 0xf0),&local_18,(int *)(param_1 + 0x21c),param_1 + 0x2b8);
  *(int *)(param_1 + 0xfc) = *(int *)(param_1 + 0x23c) + local_18;
  *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x240) + local_18;
  *(int *)(param_1 + 0x10c) = *(int *)(param_1 + 0x244) + local_14;
  *(int *)(param_1 + 0x114) = *(int *)(param_1 + 0x10c) + 8;
  *(int *)(param_1 + 0x11c) = *(int *)(param_1 + 0x10c) + *(short *)(param_1 + 0x24a) * 8;
  *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x11c) + 8;
  FUN_80288b64(param_1 + 0xe8,param_1 + 0xf8,*(int *)(param_1 + 0x2e8));
  return;
}



// ==== 80289120  FUN_80289120 ====

void FUN_80289120(int param_1)

{
  int local_18;
  int local_14;
  
  FUN_80288de0(param_1,*(int *)(param_1 + 0xf0),&local_18,(int *)(param_1 + 0x20c),param_1 + 0x294);
  *(int *)(param_1 + 0xfc) = *(int *)(param_1 + 0x23c) + local_18;
  *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x240) + local_18;
  *(int *)(param_1 + 0x10c) = *(int *)(param_1 + 0x244) + local_14;
  *(int *)(param_1 + 0x114) = *(int *)(param_1 + 0x10c) + 8;
  *(int *)(param_1 + 0x11c) = *(int *)(param_1 + 0x10c) + *(short *)(param_1 + 0x24a) * 8;
  *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x11c) + 8;
  FUN_80288b64(param_1 + 0xe8,param_1 + 0xf8,*(int *)(param_1 + 0x2e8));
  return;
}



// ==== 802891d4  FUN_802891d4 ====

/* WARNING: Removing unreachable block (ram,0x802891fc) */
/* WARNING: Removing unreachable block (ram,0x80289204) */
/* WARNING: Removing unreachable block (ram,0x80289218) */
/* WARNING: Removing unreachable block (ram,0x80289238) */
/* WARNING: Removing unreachable block (ram,0x80289258) */
/* WARNING: Removing unreachable block (ram,0x80289280) */
/* WARNING: Removing unreachable block (ram,0x80289334) */
/* WARNING: Removing unreachable block (ram,0x8028922c) */
/* WARNING: Removing unreachable block (ram,0x80289274) */
/* WARNING: Removing unreachable block (ram,0x80289210) */
/* WARNING: Removing unreachable block (ram,0x8028923c) */
/* WARNING: Removing unreachable block (ram,0x80289300) */
/* WARNING: Removing unreachable block (ram,0x80289250) */
/* WARNING: Removing unreachable block (ram,0x80289224) */
/* WARNING: Removing unreachable block (ram,0x80289214) */
/* WARNING: Removing unreachable block (ram,0x8028924c) */
/* WARNING: Removing unreachable block (ram,0x802892d8) */
/* WARNING: Removing unreachable block (ram,0x802892fc) */
/* WARNING: Removing unreachable block (ram,0x802892bc) */
/* WARNING: Removing unreachable block (ram,0x80289328) */
/* WARNING: Removing unreachable block (ram,0x802892d0) */
/* WARNING: Removing unreachable block (ram,0x802892d4) */
/* WARNING: Removing unreachable block (ram,0x802892dc) */
/* WARNING: Removing unreachable block (ram,0x802892f4) */
/* WARNING: Removing unreachable block (ram,0x8028930c) */
/* WARNING: Removing unreachable block (ram,0x8028931c) */
/* WARNING: Removing unreachable block (ram,0x80289320) */
/* WARNING: Removing unreachable block (ram,0x802892e4) */
/* WARNING: Removing unreachable block (ram,0x80289324) */
/* WARNING: Removing unreachable block (ram,0x80289318) */
/* WARNING: Removing unreachable block (ram,0x802892e8) */
/* WARNING: Removing unreachable block (ram,0x802892c4) */
/* WARNING: Removing unreachable block (ram,0x802892ac) */
/* WARNING: Removing unreachable block (ram,0x80289330) */
/* WARNING: Removing unreachable block (ram,0x80289304) */
/* WARNING: Removing unreachable block (ram,0x802892e0) */
/* WARNING: Removing unreachable block (ram,0x802892b4) */
/* WARNING: Removing unreachable block (ram,0x802892b0) */
/* WARNING: Removing unreachable block (ram,0x802892b8) */
/* WARNING: Removing unreachable block (ram,0x802892c0) */
/* WARNING: Removing unreachable block (ram,0x802892c8) */
/* WARNING: Removing unreachable block (ram,0x802892ec) */
/* WARNING: Removing unreachable block (ram,0x802892f8) */
/* WARNING: Removing unreachable block (ram,0x80289308) */
/* WARNING: Removing unreachable block (ram,0x80289310) */
/* WARNING: Removing unreachable block (ram,0x8028932c) */
/* WARNING: Removing unreachable block (ram,0x80289290) */
/* WARNING: Removing unreachable block (ram,0x80289200) */
/* WARNING: Removing unreachable block (ram,0x80289268) */
/* WARNING: Removing unreachable block (ram,0x80289208) */
/* WARNING: Removing unreachable block (ram,0x8028920c) */
/* WARNING: Removing unreachable block (ram,0x80289254) */
/* WARNING: Removing unreachable block (ram,0x80289284) */
/* WARNING: Removing unreachable block (ram,0x80289260) */
/* WARNING: Removing unreachable block (ram,0x8028925c) */
/* WARNING: Removing unreachable block (ram,0x80289278) */
/* WARNING: Removing unreachable block (ram,0x8028927c) */
/* WARNING: Removing unreachable block (ram,0x80289230) */
/* WARNING: Removing unreachable block (ram,0x80289234) */
/* WARNING: Removing unreachable block (ram,0x80289240) */
/* WARNING: Removing unreachable block (ram,0x80289228) */
/* WARNING: Removing unreachable block (ram,0x80289288) */
/* WARNING: Removing unreachable block (ram,0x8028928c) */
/* WARNING: Removing unreachable block (ram,0x80289264) */

void FUN_802891d4(float *param_1,int param_2)

{
  short sVar1;
  short sVar2;
  short sVar3;
  short sVar4;
  short sVar5;
  short sVar6;
  short sVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  short *psVar11;
  int iVar12;
  
  puVar8 = (undefined4 *)(param_2 + 4);
  iVar9 = 6;
  do {
    psVar11 = (short *)*puVar8;
    iVar10 = puVar8[1];
    puVar8 = puVar8 + 2;
    if (((uint)psVar11 & 0x1f) == 0) {
      iVar12 = 2;
      do {
        dataCacheBlockClearToZero(psVar11);
        sVar4 = *(short *)((int)param_1 + 2);
        sVar1 = *(short *)(param_1 + 1);
        sVar5 = *(short *)((int)param_1 + 6);
        sVar2 = *(short *)(param_1 + 2);
        sVar6 = *(short *)((int)param_1 + 10);
        sVar3 = *(short *)(param_1 + 3);
        sVar7 = *(short *)((int)param_1 + 0xe);
        *psVar11 = (short)((double)((longlong)(double)*(short *)param_1 * 0x3ff0000000000000) * 1.0)
        ;
        psVar11[1] = (short)((double)((longlong)(double)sVar4 * 0x3ff0000000000000) * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar1 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar5 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar2 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar6 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar3 * 0x3ff0000000000000) * 1.0);
        psVar11[4] = (short)((double)((longlong)(double)sVar7 * 0x3ff0000000000000) * 1.0);
        psVar11 = (short *)((int)psVar11 + iVar10);
        dataCacheBlockClearToZero(psVar11);
        sVar4 = *(short *)((int)param_1 + 0x12);
        sVar1 = *(short *)(param_1 + 5);
        sVar5 = *(short *)((int)param_1 + 0x16);
        sVar2 = *(short *)(param_1 + 6);
        sVar6 = *(short *)((int)param_1 + 0x1a);
        sVar3 = *(short *)(param_1 + 7);
        sVar7 = *(short *)((int)param_1 + 0x1e);
        *psVar11 = (short)((double)((longlong)(double)*(short *)(param_1 + 4) * 0x3ff0000000000000)
                          * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar4 * 0x3ff0000000000000) * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar1 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar5 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar2 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar6 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar3 * 0x3ff0000000000000) * 1.0);
        psVar11[4] = (short)((double)((longlong)(double)sVar7 * 0x3ff0000000000000) * 1.0);
        psVar11 = (short *)((int)psVar11 + iVar10);
        dataCacheBlockClearToZero(psVar11);
        sVar4 = *(short *)((int)param_1 + 0x22);
        sVar1 = *(short *)(param_1 + 9);
        sVar5 = *(short *)((int)param_1 + 0x26);
        sVar2 = *(short *)(param_1 + 10);
        sVar6 = *(short *)((int)param_1 + 0x2a);
        sVar3 = *(short *)(param_1 + 0xb);
        sVar7 = *(short *)((int)param_1 + 0x2e);
        *psVar11 = (short)((double)((longlong)(double)*(short *)(param_1 + 8) * 0x3ff0000000000000)
                          * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar4 * 0x3ff0000000000000) * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar1 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar5 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar2 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar6 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar3 * 0x3ff0000000000000) * 1.0);
        psVar11[4] = (short)((double)((longlong)(double)sVar7 * 0x3ff0000000000000) * 1.0);
        psVar11 = (short *)((int)psVar11 + iVar10);
        dataCacheBlockClearToZero(psVar11);
        sVar4 = *(short *)((int)param_1 + 0x32);
        sVar1 = *(short *)(param_1 + 0xd);
        sVar5 = *(short *)((int)param_1 + 0x36);
        sVar2 = *(short *)(param_1 + 0xe);
        sVar6 = *(short *)((int)param_1 + 0x3a);
        sVar3 = *(short *)(param_1 + 0xf);
        sVar7 = *(short *)((int)param_1 + 0x3e);
        *psVar11 = (short)((double)((longlong)(double)*(short *)(param_1 + 0xc) * 0x3ff0000000000000
                                   ) * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar4 * 0x3ff0000000000000) * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar1 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar5 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar2 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar6 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar3 * 0x3ff0000000000000) * 1.0);
        psVar11[4] = (short)((double)((longlong)(double)sVar7 * 0x3ff0000000000000) * 1.0);
        psVar11 = (short *)((int)psVar11 + iVar10);
        param_1 = param_1 + 0x10;
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
    }
    else {
      iVar12 = 2;
      do {
        sVar4 = *(short *)((int)param_1 + 2);
        sVar1 = *(short *)(param_1 + 1);
        sVar5 = *(short *)((int)param_1 + 6);
        sVar2 = *(short *)(param_1 + 2);
        sVar6 = *(short *)((int)param_1 + 10);
        sVar3 = *(short *)(param_1 + 3);
        sVar7 = *(short *)((int)param_1 + 0xe);
        *psVar11 = (short)((double)((longlong)(double)*(short *)param_1 * 0x3ff0000000000000) * 1.0)
        ;
        psVar11[1] = (short)((double)((longlong)(double)sVar4 * 0x3ff0000000000000) * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar1 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar5 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar2 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar6 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar3 * 0x3ff0000000000000) * 1.0);
        psVar11[4] = (short)((double)((longlong)(double)sVar7 * 0x3ff0000000000000) * 1.0);
        psVar11 = (short *)((int)psVar11 + iVar10);
        sVar4 = *(short *)((int)param_1 + 0x12);
        sVar1 = *(short *)(param_1 + 5);
        sVar5 = *(short *)((int)param_1 + 0x16);
        sVar2 = *(short *)(param_1 + 6);
        sVar6 = *(short *)((int)param_1 + 0x1a);
        sVar3 = *(short *)(param_1 + 7);
        sVar7 = *(short *)((int)param_1 + 0x1e);
        *psVar11 = (short)((double)((longlong)(double)*(short *)(param_1 + 4) * 0x3ff0000000000000)
                          * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar4 * 0x3ff0000000000000) * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar1 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar5 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar2 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar6 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar3 * 0x3ff0000000000000) * 1.0);
        psVar11[4] = (short)((double)((longlong)(double)sVar7 * 0x3ff0000000000000) * 1.0);
        psVar11 = (short *)((int)psVar11 + iVar10);
        sVar4 = *(short *)((int)param_1 + 0x22);
        sVar1 = *(short *)(param_1 + 9);
        sVar5 = *(short *)((int)param_1 + 0x26);
        sVar2 = *(short *)(param_1 + 10);
        sVar6 = *(short *)((int)param_1 + 0x2a);
        sVar3 = *(short *)(param_1 + 0xb);
        sVar7 = *(short *)((int)param_1 + 0x2e);
        *psVar11 = (short)((double)((longlong)(double)*(short *)(param_1 + 8) * 0x3ff0000000000000)
                          * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar4 * 0x3ff0000000000000) * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar1 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar5 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar2 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar6 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar3 * 0x3ff0000000000000) * 1.0);
        psVar11[4] = (short)((double)((longlong)(double)sVar7 * 0x3ff0000000000000) * 1.0);
        psVar11 = (short *)((int)psVar11 + iVar10);
        sVar4 = *(short *)((int)param_1 + 0x32);
        sVar1 = *(short *)(param_1 + 0xd);
        sVar5 = *(short *)((int)param_1 + 0x36);
        sVar2 = *(short *)(param_1 + 0xe);
        sVar6 = *(short *)((int)param_1 + 0x3a);
        sVar3 = *(short *)(param_1 + 0xf);
        sVar7 = *(short *)((int)param_1 + 0x3e);
        *psVar11 = (short)((double)((longlong)(double)*(short *)(param_1 + 0xc) * 0x3ff0000000000000
                                   ) * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar4 * 0x3ff0000000000000) * 1.0);
        psVar11[1] = (short)((double)((longlong)(double)sVar1 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar5 * 0x3ff0000000000000) * 1.0);
        psVar11[2] = (short)((double)((longlong)(double)sVar2 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar6 * 0x3ff0000000000000) * 1.0);
        psVar11[3] = (short)((double)((longlong)(double)sVar3 * 0x3ff0000000000000) * 1.0);
        psVar11[4] = (short)((double)((longlong)(double)sVar7 * 0x3ff0000000000000) * 1.0);
        psVar11 = (short *)((int)psVar11 + iVar10);
        param_1 = param_1 + 0x10;
        iVar12 = iVar12 + -1;
      } while (iVar12 != 0);
    }
    iVar9 = iVar9 + -1;
  } while (0 < iVar9);
  return;
}



// ==== 80289350  FUN_80289350 ====

void FUN_80289350(int param_1)

{
  char *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  pcVar1 = (char *)(param_1 + *(int *)(param_1 + 0x2dc) * 2 + 0x1324);
  iVar4 = (int)*pcVar1;
  iVar2 = (int)pcVar1[1];
  iVar3 = iVar2 * 8 + iVar4 * 8 * (int)*(short *)(param_1 + 0x248);
  *(int *)(param_1 + 0xfc) = *(int *)(param_1 + 0x23c) + iVar3;
  *(int *)(param_1 + 0x104) = *(int *)(param_1 + 0x240) + iVar3;
  *(int *)(param_1 + 0x10c) =
       *(int *)(param_1 + 0x244) + iVar2 * 0x10 + iVar4 * 0x10 * (int)*(short *)(param_1 + 0x24a);
  *(int *)(param_1 + 0x114) = *(int *)(param_1 + 0x10c) + 8;
  *(int *)(param_1 + 0x11c) = *(int *)(param_1 + 0x10c) + *(short *)(param_1 + 0x24a) * 8;
  *(int *)(param_1 + 0x124) = *(int *)(param_1 + 0x11c) + 8;
  FUN_802891d4((float *)(param_1 + 800),param_1 + 0xf8);
  return;
}



// ==== 80289414  zz_0289414_ ====

void zz_0289414_(void)

{
  return;
}



// ==== 8028943c  zz_028943c_ ====

void zz_028943c_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  uint uVar5;
  uint uVar6;
  
  uVar4 = *(int *)(param_1 + 0x1a8) + 0xf;
  uVar5 = ((int)uVar4 >> 4) + (uint)((int)uVar4 < 0 && (uVar4 & 0xf) != 0);
  uVar4 = *(int *)(param_1 + 0x1ac) + 0xf;
  iVar1 = uVar5 * 0x10;
  uVar6 = iVar1 + 0x1f;
  uVar5 = ((int)((uVar5 >> 0x1b & 1) + iVar1) >> 1) + 0x1f;
  iVar1 = (((int)uVar6 >> 5) + (uint)((int)uVar6 < 0 && (uVar6 & 0x1f) != 0)) * 0x20;
  *(short *)(param_1 + 0x24a) = (short)iVar1;
  iVar2 = (((int)uVar5 >> 5) + (uint)((int)uVar5 < 0 && (uVar5 & 0x1f) != 0)) * 0x20;
  uVar4 = ((int)uVar4 >> 4) + (uint)((int)uVar4 < 0 && (uVar4 & 0xf) != 0);
  *(short *)(param_1 + 0x248) = (short)iVar2;
  iVar3 = uVar4 * 0x10;
  *(undefined4 *)(param_1 + 0x244) = *(undefined4 *)(param_1 + 0x22c);
  *(int *)(param_1 + 0x23c) = *(int *)(param_1 + 0x244) + iVar3 * iVar1;
  *(int *)(param_1 + 0x240) =
       *(int *)(param_1 + 0x23c) + ((int)((uVar4 >> 0x1b & 1) + iVar3) >> 1) * iVar2;
  return;
}



// ==== 802894d0  zz_02894d0_ ====

void zz_02894d0_(void)

{
  DAT_8041cfd0 = &LAB_80284bbc;
  DAT_8041cfb0 = &LAB_80296988;
  DAT_8041cfd4 = zz_02844a0_;
  DAT_8041cfd8 = FUN_8028488c;
  DAT_8041cfdc = zz_0284370_;
  DAT_8041cfe0 = &LAB_80284bbc;
  DAT_8041cfe4 = zz_02844a0_;
  DAT_8041cfe8 = FUN_8028488c;
  DAT_8041cfec = FUN_8028488c;
  DAT_8041cfb4 = FUN_80296058;
  DAT_8041cfb8 = FUN_802964c8;
  DAT_8041cfbc = FUN_80295e2c;
  DAT_8041cfc0 = &LAB_80296988;
  DAT_8041cfc4 = FUN_80296058;
  DAT_8041cfc8 = FUN_802964c8;
  DAT_8041cfcc = FUN_802964c8;
  return;
}



// ==== 8028955c  zz_028955c_ ====

/* WARNING: Removing unreachable block (ram,0x80289668) */

uint zz_028955c_(uint *param_1,uint *param_2)

{
  char cVar1;
  short sVar2;
  undefined8 uVar3;
  double dVar4;
  uint uVar5;
  uint uVar6;
  undefined8 *puVar7;
  char *pcVar8;
  uint uVar9;
  uint uVar10;
  uint *puVar11;
  uint uVar12;
  int iVar13;
  
  uVar3 = DAT_802b8a18;
  puVar7 = (undefined8 *)param_2[7];
  *puVar7 = DAT_802b8a18;
  puVar7[1] = uVar3;
  puVar7[2] = uVar3;
  puVar7[3] = uVar3;
  puVar7[4] = uVar3;
  puVar7[5] = uVar3;
  puVar7[6] = uVar3;
  puVar7[7] = uVar3;
  puVar7[8] = uVar3;
  puVar7[9] = uVar3;
  puVar7[10] = uVar3;
  puVar7[0xb] = uVar3;
  puVar7[0xc] = uVar3;
  puVar7[0xd] = uVar3;
  puVar7[0xe] = uVar3;
  puVar7[0xf] = uVar3;
  puVar7[0x10] = uVar3;
  puVar7[0x11] = uVar3;
  puVar7[0x12] = uVar3;
  puVar7[0x13] = uVar3;
  puVar7[0x14] = uVar3;
  puVar7[0x15] = uVar3;
  puVar7[0x16] = uVar3;
  puVar7[0x17] = uVar3;
  puVar7[0x18] = uVar3;
  puVar7[0x19] = uVar3;
  puVar7[0x1a] = uVar3;
  puVar7[0x1b] = uVar3;
  puVar7[0x1c] = uVar3;
  puVar7[0x1d] = uVar3;
  puVar7[0x1e] = uVar3;
  puVar7[0x1f] = uVar3;
  uVar10 = param_1[2];
  uVar5 = *param_1;
  uVar9 = param_1[1];
  puVar11 = (uint *)param_1[3];
  uVar6 = uVar5;
  if (uVar10 != 0) {
    uVar6 = uVar5 | uVar9 >> 0x20 - uVar10;
  }
  if ((int)uVar6 < 0) {
    param_2[2] = uVar6 >> 0x1e & 1;
    param_2[1] = 1;
    *param_2 = 0;
    param_2[3] = 2;
  }
  else {
    uVar12 = (uVar6 & 0x7fffffff) >> 0x17;
    if (uVar12 == 1) {
      uVar6 = (uVar6 & 0x7fffffff) >> 0x12;
      param_2[3] = 0xe;
      uVar12 = (uint)*(short *)(param_1[7] + (uVar6 & 0x1ffe));
    }
    else if (uVar12 == 0) {
      if ((int)(uVar6 << 9 | (uVar6 & 0x7fffffff) >> 0x17) < 0) {
        uVar12 = (uVar6 & 0x7fffffff) >> 0x11;
        uVar6 = uVar12 & 0x1f;
        param_2[3] = 0xf;
        uVar12 = (uint)*(short *)(param_1[8] + (uVar12 & 0x1e));
      }
      else if ((int)(uVar6 << 10 | (uVar6 & 0x7fffffff) >> 0x16) < 0) {
        uVar12 = (uVar6 & 0x7fffffff) >> 0x10;
        uVar6 = uVar12 & 0x1f;
        param_2[3] = 0x10;
        uVar12 = (uint)*(short *)(param_1[9] + (uVar12 & 0x1e));
      }
      else {
        uVar12 = (uVar6 & 0x7fffffff) >> 0xf;
        uVar6 = uVar12 & 0x1f;
        param_2[3] = 0x11;
        uVar12 = (uint)*(short *)(param_1[10] + (uVar12 & 0x1e));
      }
    }
    else {
      if (7 < uVar12) {
        uVar12 = *(uint *)(param_1[4] + (uVar12 & 0xfe) * 2);
        *param_2 = uVar12 & 0xff;
        if (*param_2 == 0x40) {
          iVar13 = (int)((uVar6 & 0x7fffffff) >> 10 & 0xffff) >> 2;
          uVar12 = (uint)(char)iVar13;
          *param_2 = (int)(char)((uint)iVar13 >> 8);
          param_2[3] = 0x14;
          if ((uVar12 & 0x7f) == 0) {
            param_2[3] = param_2[3] + 8;
            uVar12 = uVar12 << 1 | (uVar6 & 0x7fffffff) >> 4 & 0xff;
          }
          if ((int)uVar12 < 0) {
            uVar12 = -uVar12;
            param_2[2] = 1;
          }
          else {
            param_2[2] = 0;
          }
          param_2[1] = uVar12;
        }
        else {
          param_2[3] = uVar12 >> 0x10;
          param_2[1] = (int)(char)(uVar12 >> 8);
          param_2[2] = (uVar6 << 1) >> 0x21 - param_2[3] & 1;
        }
        goto LAB_80289804;
      }
      if (uVar12 < 4) {
        uVar6 = (uVar6 & 0x7fffffff) >> 0x13;
        param_2[3] = 0xd;
        uVar12 = (uint)*(short *)(param_1[6] + (uVar6 & 0xffe));
      }
      else {
        uVar6 = (uVar6 & 0x7fffffff) >> 0x15;
        param_2[3] = 0xb;
        uVar12 = (uint)*(short *)(param_1[5] + (uVar6 & 0x3fe));
      }
    }
    *param_2 = uVar12 & 0xff;
    param_2[1] = (int)(char)(uVar12 >> 8);
    param_2[2] = uVar6 & 1;
  }
LAB_80289804:
  uVar10 = uVar10 + param_2[3];
  if ((int)uVar10 < 0x20) {
    uVar5 = uVar5 << param_2[3];
  }
  else {
    uVar10 = uVar10 - 0x20;
    uVar5 = uVar9 << uVar10;
    uVar9 = *puVar11;
    puVar11 = puVar11 + 1;
  }
  pcVar8 = (char *)(param_1[0xb] + *param_2);
  cVar1 = *pcVar8;
  param_2[4] = (int)cVar1;
  param_2[5] = (int)cVar1;
  uVar6 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * (param_2[1] * 2 + 1) * param_2[9]) >> 4)
          - 1U | 1;
  if (param_2[2] != 0) {
    uVar6 = -uVar6;
  }
  iVar13 = param_2[5] * 4;
  *(float *)(param_2[7] + iVar13) =
       (float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - DAT_802b8a20) *
       *(float *)(param_1[0xd] + iVar13);
  do {
    dVar4 = DAT_802b8a20;
    uVar6 = uVar5;
    if (uVar10 != 0) {
      uVar6 = uVar5 | uVar9 >> 0x20 - uVar10;
    }
    uVar12 = uVar10;
    switch(uVar6 >> 0x18) {
    case 0:
      if ((uVar6 & 0x7fffffff) >> 0x17 == 0) {
        if ((int)(uVar6 << 9) < 0) {
          uVar12 = (uVar6 & 0x7fffffff) >> 0x11;
          uVar6 = uVar12 & 0x1f;
          param_2[3] = 0xf;
          uVar12 = (uint)*(short *)(param_1[8] + (uVar12 & 0x1e));
        }
        else if ((int)(uVar6 << 10) < 0) {
          uVar12 = (uVar6 & 0x7fffffff) >> 0x10;
          uVar6 = uVar12 & 0x1f;
          param_2[3] = 0x10;
          uVar12 = (uint)*(short *)(param_1[9] + (uVar12 & 0x1e));
        }
        else {
          uVar12 = (uVar6 & 0x7fffffff) >> 0xf;
          uVar6 = uVar12 & 0x1f;
          param_2[3] = 0x11;
          uVar12 = (uint)*(short *)(param_1[10] + (uVar12 & 0x1e));
        }
      }
      else {
        uVar6 = (uVar6 & 0x7fffffff) >> 0x12;
        param_2[3] = 0xe;
        uVar12 = (uint)*(short *)(param_1[7] + (uVar6 & 0x1ffe));
      }
      *param_2 = uVar12 & 0xff;
      param_2[1] = (int)(char)(uVar12 >> 8);
      param_2[2] = uVar6 & 1;
      uVar10 = uVar10 + param_2[3];
      if ((int)uVar10 < 0x20) {
        uVar5 = uVar5 << param_2[3];
      }
      else {
        uVar10 = uVar10 - 0x20;
        uVar5 = uVar9 << uVar10;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      pcVar8 = pcVar8 + *param_2 + 1;
      param_2[5] = (int)*pcVar8;
      uVar6 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * (param_2[1] * 2 + 1) * param_2[9])
              >> 4) - 1U | 1;
      if (param_2[2] != 0) {
        uVar6 = -uVar6;
      }
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar13);
      break;
    case 1:
      param_2[3] = 0xd;
      sVar2 = *(short *)(param_1[6] + (uVar6 >> 0x13 & 0xffe));
      *param_2 = (int)sVar2 & 0xff;
      param_2[1] = (int)(char)((ushort)sVar2 >> 8);
      param_2[2] = uVar6 >> 0x13 & 1;
      uVar10 = uVar10 + param_2[3];
      if ((int)uVar10 < 0x20) {
        uVar5 = uVar5 << param_2[3];
      }
      else {
        uVar10 = uVar10 - 0x20;
        uVar5 = uVar9 << uVar10;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      pcVar8 = pcVar8 + *param_2 + 1;
      param_2[5] = (int)*pcVar8;
      uVar6 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * (param_2[1] * 2 + 1) * param_2[9])
              >> 4) - 1U | 1;
      if (param_2[2] != 0) {
        uVar6 = -uVar6;
      }
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar13);
      break;
    case 2:
    case 3:
      param_2[3] = 0xb;
      sVar2 = *(short *)(param_1[5] + (uVar6 >> 0x15 & 0x3fe));
      *param_2 = (int)sVar2 & 0xff;
      param_2[1] = (int)(char)((ushort)sVar2 >> 8);
      param_2[2] = uVar6 >> 0x15 & 1;
      uVar10 = uVar10 + param_2[3];
      if ((int)uVar10 < 0x20) {
        uVar5 = uVar5 << param_2[3];
      }
      else {
        uVar10 = uVar10 - 0x20;
        uVar5 = uVar9 << uVar10;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      pcVar8 = pcVar8 + *param_2 + 1;
      param_2[5] = (int)*pcVar8;
      uVar6 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * (param_2[1] * 2 + 1) * param_2[9])
              >> 4) - 1U | 1;
      if (param_2[2] != 0) {
        uVar6 = -uVar6;
      }
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar13);
      break;
    case 4:
    case 5:
    case 6:
    case 7:
      iVar13 = (int)(uVar6 >> 10 & 0xffff) >> 2;
      uVar12 = (uint)(char)iVar13;
      *param_2 = (int)(char)((uint)iVar13 >> 8);
      param_2[3] = 0x14;
      if ((uVar12 & 0x7f) == 0) {
        param_2[3] = param_2[3] + 8;
        uVar12 = uVar12 << 1 | (uVar6 & 0x7fffffff) >> 4 & 0xff;
      }
      if ((int)uVar12 < 0) {
        uVar12 = -uVar12;
        param_2[2] = 1;
      }
      else {
        param_2[2] = 0;
      }
      param_2[1] = uVar12;
      pcVar8 = pcVar8 + *param_2 + 1;
      param_2[5] = (int)*pcVar8;
      uVar6 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * (param_2[1] * 2 + 1) * param_2[9])
              >> 4) - 1U | 1;
      if (param_2[2] != 0) {
        uVar6 = -uVar6;
      }
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar13);
      uVar10 = uVar10 + param_2[3];
      if ((int)uVar10 < 0x20) {
        uVar5 = uVar5 << param_2[3];
      }
      else {
        uVar10 = uVar10 - 0x20;
        uVar5 = uVar9 << uVar10;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      break;
    case 8:
      pcVar8 = pcVar8 + 3;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 5 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 9:
      pcVar8 = pcVar8 + 3;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 5 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 10:
      pcVar8 = pcVar8 + 10;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0xb:
      pcVar8 = pcVar8 + 10;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0xc:
      pcVar8 = pcVar8 + 1;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 9 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0xd:
      pcVar8 = pcVar8 + 1;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 9 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0xe:
      pcVar8 = pcVar8 + 9;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0xf:
      pcVar8 = pcVar8 + 9;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0x10:
    case 0x11:
      pcVar8 = pcVar8 + 8;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0x12:
    case 0x13:
      pcVar8 = pcVar8 + 8;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0x14:
    case 0x15:
      pcVar8 = pcVar8 + 7;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0x16:
    case 0x17:
      pcVar8 = pcVar8 + 7;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0x18:
    case 0x19:
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 5 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0x1a:
    case 0x1b:
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 5 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0x1c:
    case 0x1d:
      pcVar8 = pcVar8 + 6;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0x1e:
    case 0x1f:
      pcVar8 = pcVar8 + 6;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
      uVar12 = *(uint *)(param_1[4] + ((uVar6 & 0x7fffffff) >> 0x16 & 0x1fc));
      *param_2 = uVar12 & 0xff;
      if (*param_2 == 0x40) {
        iVar13 = (int)((uVar6 & 0x7fffffff) >> 10 & 0xffff) >> 2;
        uVar12 = (uint)(char)iVar13;
        *param_2 = (int)(char)((uint)iVar13 >> 8);
        param_2[3] = 0x14;
        if ((uVar12 & 0x7f) == 0) {
          param_2[3] = param_2[3] + 8;
          uVar12 = uVar12 << 1 | (uVar6 & 0x7fffffff) >> 4 & 0xff;
        }
        if ((int)uVar12 < 0) {
          uVar12 = -uVar12;
          param_2[2] = 1;
        }
        else {
          param_2[2] = 0;
        }
        param_2[1] = uVar12;
      }
      else {
        param_2[3] = uVar12 >> 0x10;
        param_2[1] = (int)(char)(uVar12 >> 8);
        param_2[2] = (uVar6 << 1) >> 0x21 - param_2[3] & 1;
      }
      uVar10 = uVar10 + param_2[3];
      if ((int)uVar10 < 0x20) {
        uVar5 = uVar5 << param_2[3];
      }
      else {
        uVar10 = uVar10 - 0x20;
        uVar5 = uVar9 << uVar10;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      pcVar8 = pcVar8 + *param_2 + 1;
      param_2[5] = (int)*pcVar8;
      uVar6 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * (param_2[1] * 2 + 1) * param_2[9])
              >> 4) - 1U | 1;
      if (param_2[2] != 0) {
        uVar6 = -uVar6;
      }
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,uVar6 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar13);
      break;
    case 0x28:
    case 0x29:
    case 0x2b:
      pcVar8 = pcVar8 + 1;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 7 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 6) < 0x20) {
        uVar5 = uVar5 << 6;
        uVar10 = uVar10 + 6;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1a;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1a;
      }
      break;
    case 0x2a:
      uVar12 = uVar10 + 8;
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 7 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 8;
      }
      else {
        uVar12 = uVar10 - 0x18;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
def_802898FC:
      *param_1 = uVar5;
      param_1[1] = uVar9;
      param_1[2] = uVar12;
      param_1[3] = (uint)puVar11;
      uVar5 = param_2[5];
      if (uVar5 != param_2[4]) {
        uVar5 = -uVar5;
      }
      param_2[5] = uVar5;
      return param_2[5];
    case 0x2c:
    case 0x2d:
    case 0x2f:
      pcVar8 = pcVar8 + 1;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 7 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 6) < 0x20) {
        uVar5 = uVar5 << 6;
        uVar10 = uVar10 + 6;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1a;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1a;
      }
      break;
    case 0x2e:
      uVar12 = uVar10 + 8;
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 7 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 8;
      }
      else {
        uVar12 = uVar10 - 0x18;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0x30:
    case 0x31:
    case 0x33:
      pcVar8 = pcVar8 + 5;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 6) < 0x20) {
        uVar5 = uVar5 << 6;
        uVar10 = uVar10 + 6;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1a;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1a;
      }
      break;
    case 0x32:
      uVar12 = uVar10 + 8;
      param_2[5] = (int)pcVar8[5];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 8;
      }
      else {
        uVar12 = uVar10 - 0x18;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0x34:
    case 0x35:
    case 0x37:
      pcVar8 = pcVar8 + 5;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 6) < 0x20) {
        uVar5 = uVar5 << 6;
        uVar10 = uVar10 + 6;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1a;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1a;
      }
      break;
    case 0x36:
      uVar12 = uVar10 + 8;
      param_2[5] = (int)pcVar8[5];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 8;
      }
      else {
        uVar12 = uVar10 - 0x18;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0x38:
    case 0x39:
    case 0x3b:
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 6) < 0x20) {
        uVar5 = uVar5 << 6;
        uVar10 = uVar10 + 6;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1a;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1a;
      }
      break;
    case 0x3a:
      uVar12 = uVar10 + 8;
      param_2[5] = (int)pcVar8[4];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 8;
      }
      else {
        uVar12 = uVar10 - 0x18;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0x3c:
    case 0x3d:
    case 0x3f:
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 6) < 0x20) {
        uVar5 = uVar5 << 6;
        uVar10 = uVar10 + 6;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1a;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1a;
      }
      break;
    case 0x3e:
      uVar12 = uVar10 + 8;
      param_2[5] = (int)pcVar8[4];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 8;
      }
      else {
        uVar12 = uVar10 - 0x18;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
      pcVar8 = pcVar8 + 1;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 5 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 5) < 0x20) {
        uVar5 = uVar5 << 5;
        uVar10 = uVar10 + 5;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1b;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1b;
      }
      break;
    case 0x44:
    case 0x45:
      uVar12 = uVar10 + 7;
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 5 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 7;
      }
      else {
        uVar12 = uVar10 - 0x19;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0x46:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 5 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0x47:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 5 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x4b:
      pcVar8 = pcVar8 + 1;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 5 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 5) < 0x20) {
        uVar5 = uVar5 << 5;
        uVar10 = uVar10 + 5;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1b;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1b;
      }
      break;
    case 0x4c:
    case 0x4d:
      uVar12 = uVar10 + 7;
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 5 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 7;
      }
      else {
        uVar12 = uVar10 - 0x19;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0x4e:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 5 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0x4f:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 5 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
      pcVar8 = pcVar8 + 3;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 5) < 0x20) {
        uVar5 = uVar5 << 5;
        uVar10 = uVar10 + 5;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1b;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1b;
      }
      break;
    case 0x54:
    case 0x55:
      uVar12 = uVar10 + 7;
      param_2[5] = (int)pcVar8[3];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 7;
      }
      else {
        uVar12 = uVar10 - 0x19;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0x56:
      param_2[5] = (int)pcVar8[3];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0x57:
      param_2[5] = (int)pcVar8[3];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
      pcVar8 = pcVar8 + 3;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 5) < 0x20) {
        uVar5 = uVar5 << 5;
        uVar10 = uVar10 + 5;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1b;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1b;
      }
      break;
    case 0x5c:
    case 0x5d:
      uVar12 = uVar10 + 7;
      param_2[5] = (int)pcVar8[3];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 7;
      }
      else {
        uVar12 = uVar10 - 0x19;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0x5e:
      param_2[5] = (int)pcVar8[3];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0x5f:
      param_2[5] = (int)pcVar8[3];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0x60:
    case 0x61:
    case 0x62:
    case 99:
    case 100:
    case 0x65:
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 4) < 0x20) {
        uVar5 = uVar5 << 4;
        uVar10 = uVar10 + 4;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1c;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1c;
      }
      break;
    case 0x66:
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0x67:
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0x68:
    case 0x69:
    case 0x6a:
    case 0x6b:
      uVar12 = uVar10 + 6;
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 6;
      }
      else {
        uVar12 = uVar10 - 0x1a;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0x6c:
    case 0x6d:
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 3;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0x6e:
    case 0x6f:
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 3;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 4) < 0x20) {
        uVar5 = uVar5 << 4;
        uVar10 = uVar10 + 4;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1c;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1c;
      }
      break;
    case 0x76:
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0x77:
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0x78:
    case 0x79:
    case 0x7a:
    case 0x7b:
      uVar12 = uVar10 + 6;
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 6;
      }
      else {
        uVar12 = uVar10 - 0x1a;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0x7c:
    case 0x7d:
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 3;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0x7e:
    case 0x7f:
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 3;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
    case 0x88:
    case 0x89:
    case 0x8a:
    case 0x8b:
    case 0x8c:
    case 0x8d:
    case 0x8e:
    case 0x8f:
    case 0x90:
    case 0x91:
    case 0x92:
    case 0x93:
    case 0x94:
    case 0x95:
    case 0x96:
    case 0x97:
    case 0x98:
    case 0x99:
    case 0x9a:
    case 0x9b:
    case 0x9c:
    case 0x9d:
    case 0x9e:
    case 0x9f:
    case 0xa0:
    case 0xa1:
    case 0xa2:
    case 0xa3:
    case 0xa4:
    case 0xa5:
    case 0xa6:
    case 0xa7:
    case 0xa8:
    case 0xa9:
    case 0xaa:
    case 0xab:
    case 0xac:
    case 0xad:
    case 0xae:
    case 0xaf:
    case 0xb0:
    case 0xb1:
    case 0xb2:
    case 0xb3:
    case 0xb4:
    case 0xb5:
    case 0xb6:
    case 0xb7:
    case 0xb8:
    case 0xb9:
    case 0xba:
    case 0xbb:
    case 0xbc:
    case 0xbd:
    case 0xbe:
    case 0xbf:
      uVar12 = uVar10 + 2;
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 2;
      }
      else {
        uVar12 = uVar10 - 0x1e;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0xc0:
    case 0xc1:
    case 0xc2:
    case 0xc3:
    case 0xc4:
    case 0xc5:
    case 0xc6:
    case 199:
      pcVar8 = pcVar8 + 1;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 3) < 0x20) {
        uVar5 = uVar5 << 3;
        uVar10 = uVar10 + 3;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1d;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1d;
      }
      break;
    case 200:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 5 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0xc9:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 5 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0xca:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0xcb:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0xcc:
    case 0xcd:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 3;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0xce:
    case 0xcf:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 3;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0xd0:
    case 0xd1:
    case 0xd2:
    case 0xd3:
    case 0xd4:
    case 0xd5:
    case 0xd6:
    case 0xd7:
      uVar12 = uVar10 + 5;
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 5;
      }
      else {
        uVar12 = uVar10 - 0x1b;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0xd8:
    case 0xd9:
    case 0xdb:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 6) < 0x20) {
        uVar5 = uVar5 << 6;
        uVar10 = uVar10 + 6;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1a;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1a;
      }
      break;
    case 0xda:
      uVar12 = uVar10 + 8;
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 8;
      }
      else {
        uVar12 = uVar10 - 0x18;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0xdc:
    case 0xdd:
    case 0xdf:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 6) < 0x20) {
        uVar5 = uVar5 << 6;
        uVar10 = uVar10 + 6;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1a;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1a;
      }
      break;
    case 0xde:
      uVar12 = uVar10 + 8;
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 8;
      }
      else {
        uVar12 = uVar10 - 0x18;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0xe0:
    case 0xe1:
    case 0xe2:
    case 0xe3:
    case 0xe4:
    case 0xe5:
    case 0xe6:
    case 0xe7:
      pcVar8 = pcVar8 + 1;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 3) < 0x20) {
        uVar5 = uVar5 << 3;
        uVar10 = uVar10 + 3;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1d;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1d;
      }
      break;
    case 0xe8:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 5 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0xe9:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 5 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0xea:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0xeb:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 4;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 8) < 0x20) {
        uVar5 = uVar5 << 8;
        uVar10 = uVar10 + 8;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x18;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x18;
      }
      break;
    case 0xec:
    case 0xed:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 3;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0xee:
    case 0xef:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 3;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 7) < 0x20) {
        uVar5 = uVar5 << 7;
        uVar10 = uVar10 + 7;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x19;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x19;
      }
      break;
    case 0xf0:
    case 0xf1:
    case 0xf2:
    case 0xf3:
    case 0xf4:
    case 0xf5:
    case 0xf6:
    case 0xf7:
      uVar12 = uVar10 + 5;
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 5;
      }
      else {
        uVar12 = uVar10 - 0x1b;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0xf8:
    case 0xf9:
    case 0xfb:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 6) < 0x20) {
        uVar5 = uVar5 << 6;
        uVar10 = uVar10 + 6;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1a;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1a;
      }
      break;
    case 0xfa:
      uVar12 = uVar10 + 8;
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 3 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 8;
      }
      else {
        uVar12 = uVar10 - 0x18;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
      goto def_802898FC;
    case 0xfc:
    case 0xfd:
    case 0xff:
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      pcVar8 = pcVar8 + 2;
      param_2[5] = (int)*pcVar8;
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)(uVar10 + 6) < 0x20) {
        uVar5 = uVar5 << 6;
        uVar10 = uVar10 + 6;
      }
      else {
        uVar5 = uVar9 << uVar10 - 0x1a;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
        uVar10 = uVar10 - 0x1a;
      }
      break;
    case 0xfe:
      uVar12 = uVar10 + 8;
      param_2[5] = (int)pcVar8[1];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      param_2[5] = (int)pcVar8[2];
      iVar13 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar13) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 3 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar4) * *(float *)(param_1[0xd] + iVar13);
      if ((int)uVar12 < 0x20) {
        uVar5 = uVar5 << 8;
      }
      else {
        uVar12 = uVar10 - 0x18;
        uVar5 = uVar9 << uVar12;
        uVar9 = *puVar11;
        puVar11 = puVar11 + 1;
      }
    default:
      goto def_802898FC;
    }
  } while( true );
}



// ==== 8028d9f4  FUN_8028d9f4 ====

uint FUN_8028d9f4(uint *param_1,uint *param_2)

{
  byte bVar1;
  short sVar2;
  double dVar3;
  float fVar4;
  uint uVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  char *pcVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  
  fVar4 = DAT_802b8a28;
  dVar3 = DAT_802b8a20;
  uVar7 = param_1[2];
  uVar6 = param_1[1];
  puVar8 = (uint *)param_1[3];
  uVar10 = *param_1 >> 0x10;
  if (0x10 < (int)uVar7) {
    uVar10 = uVar10 | uVar6 >> 0x30 - uVar7;
  }
  bVar1 = *(byte *)(param_2[0xb] + (uVar10 >> 9));
  uVar5 = (uint)(bVar1 >> 4);
  uVar11 = bVar1 & 0xf;
  iVar12 = 0;
  if (uVar5 != 0) {
    iVar12 = uVar11 * 2;
    uVar11 = uVar11 + uVar5;
    uVar5 = 1 << uVar5 - 1;
    uVar10 = (uVar10 & (int)*(short *)(param_1[0xc] + iVar12)) >> 0x10 - uVar11;
    if ((uVar10 & uVar5) == 0) {
      uVar10 = uVar10 + uVar5 * -2 + 1;
    }
    iVar12 = uVar10 << 3;
  }
  uVar7 = uVar7 + uVar11;
  if ((int)uVar7 < 0x20) {
    uVar11 = *param_1 << uVar11;
  }
  else {
    uVar7 = uVar7 - 0x20;
    uVar11 = uVar6 << uVar7;
    uVar6 = *puVar8;
    puVar8 = puVar8 + 1;
  }
  uVar10 = iVar12 + *(uint *)param_2[10];
  *(uint *)param_2[10] = uVar10;
  *(float *)param_2[7] = fVar4 * (float)((double)CONCAT44(0x43300000,uVar10 ^ 0x80000000) - dVar3);
  param_2[4] = 0;
  param_2[5] = 0;
  pcVar9 = (char *)param_1[0xb];
  uVar10 = uVar7;
  if (param_1[0x70] != 4) {
LAB_8028db10:
    dVar3 = DAT_802b8a20;
    uVar5 = uVar11;
    if (uVar7 != 0) {
      uVar5 = uVar11 | uVar6 >> 0x20 - uVar7;
    }
    uVar10 = uVar7;
    switch(uVar5 >> 0x18) {
    case 0:
      if ((uVar5 & 0x7fffffff) >> 0x17 == 0) {
        if ((int)(uVar5 << 9) < 0) {
          uVar5 = (uVar5 & 0x7fffffff) >> 0x11;
          uVar10 = uVar5 & 0x1f;
          param_2[3] = 0xf;
          uVar5 = (uint)*(short *)(param_1[8] + (uVar5 & 0x1e));
        }
        else if ((int)(uVar5 << 10) < 0) {
          uVar5 = (uVar5 & 0x7fffffff) >> 0x10;
          uVar10 = uVar5 & 0x1f;
          param_2[3] = 0x10;
          uVar5 = (uint)*(short *)(param_1[9] + (uVar5 & 0x1e));
        }
        else {
          uVar5 = (uVar5 & 0x7fffffff) >> 0xf;
          uVar10 = uVar5 & 0x1f;
          param_2[3] = 0x11;
          uVar5 = (uint)*(short *)(param_1[10] + (uVar5 & 0x1e));
        }
      }
      else {
        uVar10 = (uVar5 & 0x7fffffff) >> 0x12;
        param_2[3] = 0xe;
        uVar5 = (uint)*(short *)(param_1[7] + (uVar10 & 0x1ffe));
      }
      *param_2 = uVar5 & 0xff;
      param_2[1] = (int)(char)(uVar5 >> 8);
      param_2[2] = uVar10 & 1;
      uVar7 = uVar7 + param_2[3];
      if ((int)uVar7 < 0x20) {
        uVar11 = uVar11 << param_2[3];
      }
      else {
        uVar7 = uVar7 - 0x20;
        uVar11 = uVar6 << uVar7;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      pcVar9 = pcVar9 + *param_2 + 1;
      param_2[5] = (int)*pcVar9;
      uVar10 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * param_2[1] * 2 * param_2[9]) >> 4)
               - 1U | 1;
      if (param_2[2] != 0) {
        uVar10 = -uVar10;
      }
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,uVar10 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar12);
      goto LAB_8028db10;
    case 1:
      param_2[3] = 0xd;
      sVar2 = *(short *)(param_1[6] + (uVar5 >> 0x13 & 0xffe));
      *param_2 = (int)sVar2 & 0xff;
      param_2[1] = (int)(char)((ushort)sVar2 >> 8);
      param_2[2] = uVar5 >> 0x13 & 1;
      uVar7 = uVar7 + param_2[3];
      if ((int)uVar7 < 0x20) {
        uVar11 = uVar11 << param_2[3];
      }
      else {
        uVar7 = uVar7 - 0x20;
        uVar11 = uVar6 << uVar7;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      pcVar9 = pcVar9 + *param_2 + 1;
      param_2[5] = (int)*pcVar9;
      uVar10 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * param_2[1] * 2 * param_2[9]) >> 4)
               - 1U | 1;
      if (param_2[2] != 0) {
        uVar10 = -uVar10;
      }
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,uVar10 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar12);
      goto LAB_8028db10;
    case 2:
    case 3:
      param_2[3] = 0xb;
      sVar2 = *(short *)(param_1[5] + (uVar5 >> 0x15 & 0x3fe));
      *param_2 = (int)sVar2 & 0xff;
      param_2[1] = (int)(char)((ushort)sVar2 >> 8);
      param_2[2] = uVar5 >> 0x15 & 1;
      uVar7 = uVar7 + param_2[3];
      if ((int)uVar7 < 0x20) {
        uVar11 = uVar11 << param_2[3];
      }
      else {
        uVar7 = uVar7 - 0x20;
        uVar11 = uVar6 << uVar7;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      pcVar9 = pcVar9 + *param_2 + 1;
      param_2[5] = (int)*pcVar9;
      uVar10 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * param_2[1] * 2 * param_2[9]) >> 4)
               - 1U | 1;
      if (param_2[2] != 0) {
        uVar10 = -uVar10;
      }
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,uVar10 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar12);
      goto LAB_8028db10;
    case 4:
    case 5:
    case 6:
    case 7:
      iVar12 = (int)(uVar5 >> 10 & 0xffff) >> 2;
      uVar10 = (uint)(char)iVar12;
      *param_2 = (int)(char)((uint)iVar12 >> 8);
      param_2[3] = 0x14;
      if ((uVar10 & 0x7f) == 0) {
        param_2[3] = param_2[3] + 8;
        uVar10 = uVar10 << 1 | (uVar5 & 0x7fffffff) >> 4 & 0xff;
      }
      if ((int)uVar10 < 0) {
        uVar10 = -uVar10;
        param_2[2] = 1;
      }
      else {
        param_2[2] = 0;
      }
      param_2[1] = uVar10;
      pcVar9 = pcVar9 + *param_2 + 1;
      param_2[5] = (int)*pcVar9;
      uVar10 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * param_2[1] * 2 * param_2[9]) >> 4)
               - 1U | 1;
      if (param_2[2] != 0) {
        uVar10 = -uVar10;
      }
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,uVar10 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar12);
      uVar7 = uVar7 + param_2[3];
      if ((int)uVar7 < 0x20) {
        uVar11 = uVar11 << param_2[3];
      }
      else {
        uVar7 = uVar7 - 0x20;
        uVar11 = uVar6 << uVar7;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      goto LAB_8028db10;
    case 8:
      pcVar9 = pcVar9 + 3;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 9:
      pcVar9 = pcVar9 + 3;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 10:
      pcVar9 = pcVar9 + 10;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0xb:
      pcVar9 = pcVar9 + 10;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0xc:
      pcVar9 = pcVar9 + 1;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 8 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0xd:
      pcVar9 = pcVar9 + 1;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 8 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0xe:
      pcVar9 = pcVar9 + 9;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0xf:
      pcVar9 = pcVar9 + 9;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0x10:
    case 0x11:
      pcVar9 = pcVar9 + 8;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0x12:
    case 0x13:
      pcVar9 = pcVar9 + 8;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0x14:
    case 0x15:
      pcVar9 = pcVar9 + 7;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0x16:
    case 0x17:
      pcVar9 = pcVar9 + 7;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0x18:
    case 0x19:
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0x1a:
    case 0x1b:
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0x1c:
    case 0x1d:
      pcVar9 = pcVar9 + 6;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0x1e:
    case 0x1f:
      pcVar9 = pcVar9 + 6;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
      uVar10 = *(uint *)(param_1[4] + ((uVar5 & 0x7fffffff) >> 0x16 & 0x1fc));
      *param_2 = uVar10 & 0xff;
      if (*param_2 == 0x40) {
        iVar12 = (int)((uVar5 & 0x7fffffff) >> 10 & 0xffff) >> 2;
        uVar10 = (uint)(char)iVar12;
        *param_2 = (int)(char)((uint)iVar12 >> 8);
        param_2[3] = 0x14;
        if ((uVar10 & 0x7f) == 0) {
          param_2[3] = param_2[3] + 8;
          uVar10 = uVar10 << 1 | (uVar5 & 0x7fffffff) >> 4 & 0xff;
        }
        if ((int)uVar10 < 0) {
          uVar10 = -uVar10;
          param_2[2] = 1;
        }
        else {
          param_2[2] = 0;
        }
        param_2[1] = uVar10;
      }
      else {
        param_2[3] = uVar10 >> 0x10;
        param_2[1] = (int)(char)(uVar10 >> 8);
        param_2[2] = (uVar5 << 1) >> 0x21 - param_2[3] & 1;
      }
      uVar7 = uVar7 + param_2[3];
      if ((int)uVar7 < 0x20) {
        uVar11 = uVar11 << param_2[3];
      }
      else {
        uVar7 = uVar7 - 0x20;
        uVar11 = uVar6 << uVar7;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      pcVar9 = pcVar9 + *param_2 + 1;
      param_2[5] = (int)*pcVar9;
      uVar10 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * param_2[1] * 2 * param_2[9]) >> 4)
               - 1U | 1;
      if (param_2[2] != 0) {
        uVar10 = -uVar10;
      }
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,uVar10 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar12);
      goto LAB_8028db10;
    case 0x28:
    case 0x29:
    case 0x2b:
      pcVar9 = pcVar9 + 1;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 6 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar11 = uVar11 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      goto LAB_8028db10;
    case 0x2a:
      uVar10 = uVar7 + 8;
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 6 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 8;
      }
      else {
        uVar10 = uVar7 - 0x18;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0x2c:
    case 0x2d:
    case 0x2f:
      pcVar9 = pcVar9 + 1;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 6 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar11 = uVar11 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      goto LAB_8028db10;
    case 0x2e:
      uVar10 = uVar7 + 8;
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 6 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 8;
      }
      else {
        uVar10 = uVar7 - 0x18;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0x30:
    case 0x31:
    case 0x33:
      pcVar9 = pcVar9 + 5;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar11 = uVar11 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      goto LAB_8028db10;
    case 0x32:
      uVar10 = uVar7 + 8;
      param_2[5] = (int)pcVar9[5];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 8;
      }
      else {
        uVar10 = uVar7 - 0x18;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0x34:
    case 0x35:
    case 0x37:
      pcVar9 = pcVar9 + 5;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar11 = uVar11 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      goto LAB_8028db10;
    case 0x36:
      uVar10 = uVar7 + 8;
      param_2[5] = (int)pcVar9[5];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 8;
      }
      else {
        uVar10 = uVar7 - 0x18;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0x38:
    case 0x39:
    case 0x3b:
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar11 = uVar11 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      goto LAB_8028db10;
    case 0x3a:
      uVar10 = uVar7 + 8;
      param_2[5] = (int)pcVar9[4];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 8;
      }
      else {
        uVar10 = uVar7 - 0x18;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0x3c:
    case 0x3d:
    case 0x3f:
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar11 = uVar11 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      goto LAB_8028db10;
    case 0x3e:
      uVar10 = uVar7 + 8;
      param_2[5] = (int)pcVar9[4];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 8;
      }
      else {
        uVar10 = uVar7 - 0x18;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
      pcVar9 = pcVar9 + 1;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 5) < 0x20) {
        uVar11 = uVar11 << 5;
        uVar7 = uVar7 + 5;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1b;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1b;
      }
      goto LAB_8028db10;
    case 0x44:
    case 0x45:
      uVar10 = uVar7 + 7;
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 7;
      }
      else {
        uVar10 = uVar7 - 0x19;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0x46:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0x47:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x4b:
      pcVar9 = pcVar9 + 1;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 5) < 0x20) {
        uVar11 = uVar11 << 5;
        uVar7 = uVar7 + 5;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1b;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1b;
      }
      goto LAB_8028db10;
    case 0x4c:
    case 0x4d:
      uVar10 = uVar7 + 7;
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 7;
      }
      else {
        uVar10 = uVar7 - 0x19;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0x4e:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0x4f:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
      pcVar9 = pcVar9 + 3;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 5) < 0x20) {
        uVar11 = uVar11 << 5;
        uVar7 = uVar7 + 5;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1b;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1b;
      }
      goto LAB_8028db10;
    case 0x54:
    case 0x55:
      uVar10 = uVar7 + 7;
      param_2[5] = (int)pcVar9[3];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 7;
      }
      else {
        uVar10 = uVar7 - 0x19;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0x56:
      param_2[5] = (int)pcVar9[3];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0x57:
      param_2[5] = (int)pcVar9[3];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
      pcVar9 = pcVar9 + 3;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 5) < 0x20) {
        uVar11 = uVar11 << 5;
        uVar7 = uVar7 + 5;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1b;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1b;
      }
      goto LAB_8028db10;
    case 0x5c:
    case 0x5d:
      uVar10 = uVar7 + 7;
      param_2[5] = (int)pcVar9[3];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 7;
      }
      else {
        uVar10 = uVar7 - 0x19;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0x5e:
      param_2[5] = (int)pcVar9[3];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0x5f:
      param_2[5] = (int)pcVar9[3];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0x60:
    case 0x61:
    case 0x62:
    case 99:
    case 100:
    case 0x65:
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 4) < 0x20) {
        uVar11 = uVar11 << 4;
        uVar7 = uVar7 + 4;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1c;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1c;
      }
      goto LAB_8028db10;
    case 0x66:
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0x67:
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0x68:
    case 0x69:
    case 0x6a:
    case 0x6b:
      uVar10 = uVar7 + 6;
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 6;
      }
      else {
        uVar10 = uVar7 - 0x1a;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0x6c:
    case 0x6d:
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 3;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0x6e:
    case 0x6f:
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 3;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 4) < 0x20) {
        uVar11 = uVar11 << 4;
        uVar7 = uVar7 + 4;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1c;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1c;
      }
      goto LAB_8028db10;
    case 0x76:
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0x77:
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0x78:
    case 0x79:
    case 0x7a:
    case 0x7b:
      uVar10 = uVar7 + 6;
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 6;
      }
      else {
        uVar10 = uVar7 - 0x1a;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0x7c:
    case 0x7d:
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 3;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0x7e:
    case 0x7f:
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 3;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
    case 0x88:
    case 0x89:
    case 0x8a:
    case 0x8b:
    case 0x8c:
    case 0x8d:
    case 0x8e:
    case 0x8f:
    case 0x90:
    case 0x91:
    case 0x92:
    case 0x93:
    case 0x94:
    case 0x95:
    case 0x96:
    case 0x97:
    case 0x98:
    case 0x99:
    case 0x9a:
    case 0x9b:
    case 0x9c:
    case 0x9d:
    case 0x9e:
    case 0x9f:
    case 0xa0:
    case 0xa1:
    case 0xa2:
    case 0xa3:
    case 0xa4:
    case 0xa5:
    case 0xa6:
    case 0xa7:
    case 0xa8:
    case 0xa9:
    case 0xaa:
    case 0xab:
    case 0xac:
    case 0xad:
    case 0xae:
    case 0xaf:
    case 0xb0:
    case 0xb1:
    case 0xb2:
    case 0xb3:
    case 0xb4:
    case 0xb5:
    case 0xb6:
    case 0xb7:
    case 0xb8:
    case 0xb9:
    case 0xba:
    case 0xbb:
    case 0xbc:
    case 0xbd:
    case 0xbe:
    case 0xbf:
      uVar10 = uVar7 + 2;
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 2;
      }
      else {
        uVar10 = uVar7 - 0x1e;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0xc0:
    case 0xc1:
    case 0xc2:
    case 0xc3:
    case 0xc4:
    case 0xc5:
    case 0xc6:
    case 199:
      pcVar9 = pcVar9 + 1;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 3) < 0x20) {
        uVar11 = uVar11 << 3;
        uVar7 = uVar7 + 3;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1d;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1d;
      }
      goto LAB_8028db10;
    case 200:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0xc9:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0xca:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0xcb:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0xcc:
    case 0xcd:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 3;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0xce:
    case 0xcf:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 3;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0xd0:
    case 0xd1:
    case 0xd2:
    case 0xd3:
    case 0xd4:
    case 0xd5:
    case 0xd6:
    case 0xd7:
      uVar10 = uVar7 + 5;
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 5;
      }
      else {
        uVar10 = uVar7 - 0x1b;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0xd8:
    case 0xd9:
    case 0xdb:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar11 = uVar11 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      goto LAB_8028db10;
    case 0xda:
      uVar10 = uVar7 + 8;
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 8;
      }
      else {
        uVar10 = uVar7 - 0x18;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0xdc:
    case 0xdd:
    case 0xdf:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar11 = uVar11 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      goto LAB_8028db10;
    case 0xde:
      uVar10 = uVar7 + 8;
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 8;
      }
      else {
        uVar10 = uVar7 - 0x18;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0xe0:
    case 0xe1:
    case 0xe2:
    case 0xe3:
    case 0xe4:
    case 0xe5:
    case 0xe6:
    case 0xe7:
      pcVar9 = pcVar9 + 1;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 3) < 0x20) {
        uVar11 = uVar11 << 3;
        uVar7 = uVar7 + 3;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1d;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1d;
      }
      goto LAB_8028db10;
    case 0xe8:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0xe9:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0xea:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0xeb:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 4;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar11 = uVar11 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x18;
      }
      goto LAB_8028db10;
    case 0xec:
    case 0xed:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 3;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0xee:
    case 0xef:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 3;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar11 = uVar11 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x19;
      }
      goto LAB_8028db10;
    case 0xf0:
    case 0xf1:
    case 0xf2:
    case 0xf3:
    case 0xf4:
    case 0xf5:
    case 0xf6:
    case 0xf7:
      uVar10 = uVar7 + 5;
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 5;
      }
      else {
        uVar10 = uVar7 - 0x1b;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0xf8:
    case 0xf9:
    case 0xfb:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar11 = uVar11 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      goto LAB_8028db10;
    case 0xfa:
      uVar10 = uVar7 + 8;
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 8;
      }
      else {
        uVar10 = uVar7 - 0x18;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
      break;
    case 0xfc:
    case 0xfd:
    case 0xff:
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      pcVar9 = pcVar9 + 2;
      param_2[5] = (int)*pcVar9;
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar11 = uVar11 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar11 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      goto LAB_8028db10;
    case 0xfe:
      uVar10 = uVar7 + 8;
      param_2[5] = (int)pcVar9[1];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      param_2[5] = (int)pcVar9[2];
      iVar12 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar12) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar12);
      if ((int)uVar10 < 0x20) {
        uVar11 = uVar11 << 8;
      }
      else {
        uVar10 = uVar7 - 0x18;
        uVar11 = uVar6 << uVar10;
        uVar6 = *puVar8;
        puVar8 = puVar8 + 1;
      }
    default:
      break;
    }
  }
  *param_1 = uVar11;
  param_1[1] = uVar6;
  param_1[2] = uVar10;
  param_1[3] = (uint)puVar8;
  uVar10 = param_2[5];
  if (uVar10 != param_2[4]) {
    uVar10 = -uVar10;
  }
  param_2[5] = uVar10;
  return param_2[5];
}



// ==== 80291c24  FUN_80291c24 ====

uint FUN_80291c24(uint *param_1,uint *param_2)

{
  byte bVar1;
  short sVar2;
  double dVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  uint *puVar9;
  uint uVar10;
  char *pcVar11;
  uint uVar12;
  
  dVar3 = DAT_802b8a20;
  uVar7 = param_1[2];
  uVar10 = *param_1;
  uVar6 = param_1[1];
  puVar9 = (uint *)param_1[3];
  uVar4 = uVar10;
  if (uVar7 != 0) {
    uVar4 = uVar10 | uVar6 >> 0x20 - uVar7;
  }
  bVar1 = *(byte *)(param_2[0xb] + (uVar4 >> 0x16));
  uVar8 = (uint)(bVar1 >> 4);
  uVar12 = bVar1 & 0xf;
  iVar5 = 0;
  if (uVar8 != 0) {
    iVar5 = uVar4 << uVar12;
    uVar12 = uVar12 + uVar8;
    uVar4 = iVar5 >> 1 ^ 0x80000000;
    iVar5 = ((int)uVar4 >> (0x1f - uVar8 & 0x3f)) - ((int)uVar4 >> 0x1f);
  }
  uVar7 = uVar7 + uVar12;
  if ((int)uVar7 < 0x20) {
    uVar10 = uVar10 << uVar12;
  }
  else {
    uVar7 = uVar7 - 0x20;
    uVar10 = uVar6 << uVar7;
    uVar6 = *puVar9;
    puVar9 = puVar9 + 1;
  }
  uVar4 = iVar5 + *(uint *)param_2[10];
  *(uint *)param_2[10] = uVar4;
  *(float *)param_2[7] =
       DAT_802b8a28 * (float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - dVar3);
  param_2[4] = 0;
  param_2[5] = 0;
  pcVar11 = (char *)param_1[0xb];
  do {
    dVar3 = DAT_802b8a20;
    uVar4 = uVar10;
    if (uVar7 != 0) {
      uVar4 = uVar10 | uVar6 >> 0x20 - uVar7;
    }
    uVar8 = uVar7;
    switch(uVar4 >> 0x18) {
    case 0:
      if ((uVar4 & 0x7fffffff) >> 0x17 == 0) {
        if ((int)(uVar4 << 9) < 0) {
          uVar8 = (uVar4 & 0x7fffffff) >> 0x11;
          uVar4 = uVar8 & 0x1f;
          param_2[3] = 0xf;
          uVar8 = (uint)*(short *)(param_1[8] + (uVar8 & 0x1e));
        }
        else if ((int)(uVar4 << 10) < 0) {
          uVar8 = (uVar4 & 0x7fffffff) >> 0x10;
          uVar4 = uVar8 & 0x1f;
          param_2[3] = 0x10;
          uVar8 = (uint)*(short *)(param_1[9] + (uVar8 & 0x1e));
        }
        else {
          uVar8 = (uVar4 & 0x7fffffff) >> 0xf;
          uVar4 = uVar8 & 0x1f;
          param_2[3] = 0x11;
          uVar8 = (uint)*(short *)(param_1[10] + (uVar8 & 0x1e));
        }
      }
      else {
        uVar4 = (uVar4 & 0x7fffffff) >> 0x12;
        param_2[3] = 0xe;
        uVar8 = (uint)*(short *)(param_1[7] + (uVar4 & 0x1ffe));
      }
      *param_2 = uVar8 & 0xff;
      param_2[1] = (int)(char)(uVar8 >> 8);
      param_2[2] = uVar4 & 1;
      uVar7 = uVar7 + param_2[3];
      if ((int)uVar7 < 0x20) {
        uVar10 = uVar10 << param_2[3];
      }
      else {
        uVar7 = uVar7 - 0x20;
        uVar10 = uVar6 << uVar7;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      pcVar11 = pcVar11 + *param_2 + 1;
      param_2[5] = (int)*pcVar11;
      uVar4 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * param_2[1] * 2 * param_2[9]) >> 4) -
              1U | 1;
      if (param_2[2] != 0) {
        uVar4 = -uVar4;
      }
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar5);
      break;
    case 1:
      param_2[3] = 0xd;
      sVar2 = *(short *)(param_1[6] + (uVar4 >> 0x13 & 0xffe));
      *param_2 = (int)sVar2 & 0xff;
      param_2[1] = (int)(char)((ushort)sVar2 >> 8);
      param_2[2] = uVar4 >> 0x13 & 1;
      uVar7 = uVar7 + param_2[3];
      if ((int)uVar7 < 0x20) {
        uVar10 = uVar10 << param_2[3];
      }
      else {
        uVar7 = uVar7 - 0x20;
        uVar10 = uVar6 << uVar7;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      pcVar11 = pcVar11 + *param_2 + 1;
      param_2[5] = (int)*pcVar11;
      uVar4 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * param_2[1] * 2 * param_2[9]) >> 4) -
              1U | 1;
      if (param_2[2] != 0) {
        uVar4 = -uVar4;
      }
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar5);
      break;
    case 2:
    case 3:
      param_2[3] = 0xb;
      sVar2 = *(short *)(param_1[5] + (uVar4 >> 0x15 & 0x3fe));
      *param_2 = (int)sVar2 & 0xff;
      param_2[1] = (int)(char)((ushort)sVar2 >> 8);
      param_2[2] = uVar4 >> 0x15 & 1;
      uVar7 = uVar7 + param_2[3];
      if ((int)uVar7 < 0x20) {
        uVar10 = uVar10 << param_2[3];
      }
      else {
        uVar7 = uVar7 - 0x20;
        uVar10 = uVar6 << uVar7;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      pcVar11 = pcVar11 + *param_2 + 1;
      param_2[5] = (int)*pcVar11;
      uVar4 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * param_2[1] * 2 * param_2[9]) >> 4) -
              1U | 1;
      if (param_2[2] != 0) {
        uVar4 = -uVar4;
      }
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar5);
      break;
    case 4:
    case 5:
    case 6:
    case 7:
      iVar5 = (int)(uVar4 >> 10 & 0xffff) >> 2;
      uVar8 = (uint)(char)iVar5;
      *param_2 = (int)(char)((uint)iVar5 >> 8);
      param_2[3] = 0x14;
      if ((uVar8 & 0x7f) == 0) {
        param_2[3] = param_2[3] + 8;
        uVar8 = uVar8 << 1 | (uVar4 & 0x7fffffff) >> 4 & 0xff;
      }
      if ((int)uVar8 < 0) {
        uVar8 = -uVar8;
        param_2[2] = 1;
      }
      else {
        param_2[2] = 0;
      }
      param_2[1] = uVar8;
      pcVar11 = pcVar11 + *param_2 + 1;
      param_2[5] = (int)*pcVar11;
      uVar4 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * param_2[1] * 2 * param_2[9]) >> 4) -
              1U | 1;
      if (param_2[2] != 0) {
        uVar4 = -uVar4;
      }
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar5);
      uVar7 = uVar7 + param_2[3];
      if ((int)uVar7 < 0x20) {
        uVar10 = uVar10 << param_2[3];
      }
      else {
        uVar7 = uVar7 - 0x20;
        uVar10 = uVar6 << uVar7;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      break;
    case 8:
      pcVar11 = pcVar11 + 3;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 9:
      pcVar11 = pcVar11 + 3;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 10:
      pcVar11 = pcVar11 + 10;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0xb:
      pcVar11 = pcVar11 + 10;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0xc:
      pcVar11 = pcVar11 + 1;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 8 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0xd:
      pcVar11 = pcVar11 + 1;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 8 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0xe:
      pcVar11 = pcVar11 + 9;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0xf:
      pcVar11 = pcVar11 + 9;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0x10:
    case 0x11:
      pcVar11 = pcVar11 + 8;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0x12:
    case 0x13:
      pcVar11 = pcVar11 + 8;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0x14:
    case 0x15:
      pcVar11 = pcVar11 + 7;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0x16:
    case 0x17:
      pcVar11 = pcVar11 + 7;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0x18:
    case 0x19:
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0x1a:
    case 0x1b:
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0x1c:
    case 0x1d:
      pcVar11 = pcVar11 + 6;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0x1e:
    case 0x1f:
      pcVar11 = pcVar11 + 6;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0x20:
    case 0x21:
    case 0x22:
    case 0x23:
    case 0x24:
    case 0x25:
    case 0x26:
    case 0x27:
      uVar8 = *(uint *)(param_1[4] + ((uVar4 & 0x7fffffff) >> 0x16 & 0x1fc));
      *param_2 = uVar8 & 0xff;
      if (*param_2 == 0x40) {
        iVar5 = (int)((uVar4 & 0x7fffffff) >> 10 & 0xffff) >> 2;
        uVar8 = (uint)(char)iVar5;
        *param_2 = (int)(char)((uint)iVar5 >> 8);
        param_2[3] = 0x14;
        if ((uVar8 & 0x7f) == 0) {
          param_2[3] = param_2[3] + 8;
          uVar8 = uVar8 << 1 | (uVar4 & 0x7fffffff) >> 4 & 0xff;
        }
        if ((int)uVar8 < 0) {
          uVar8 = -uVar8;
          param_2[2] = 1;
        }
        else {
          param_2[2] = 0;
        }
        param_2[1] = uVar8;
      }
      else {
        param_2[3] = uVar8 >> 0x10;
        param_2[1] = (int)(char)(uVar8 >> 8);
        param_2[2] = (uVar4 << 1) >> 0x21 - param_2[3] & 1;
      }
      uVar7 = uVar7 + param_2[3];
      if ((int)uVar7 < 0x20) {
        uVar10 = uVar10 << param_2[3];
      }
      else {
        uVar7 = uVar7 - 0x20;
        uVar10 = uVar6 << uVar7;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      pcVar11 = pcVar11 + *param_2 + 1;
      param_2[5] = (int)*pcVar11;
      uVar4 = ((int)((uint)*(byte *)(param_2[8] + param_2[5]) * param_2[1] * 2 * param_2[9]) >> 4) -
              1U | 1;
      if (param_2[2] != 0) {
        uVar4 = -uVar4;
      }
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - DAT_802b8a20) *
           *(float *)(param_1[0xd] + iVar5);
      break;
    case 0x28:
    case 0x29:
    case 0x2b:
      pcVar11 = pcVar11 + 1;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 6 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar10 = uVar10 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      break;
    case 0x2a:
      uVar8 = uVar7 + 8;
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 6 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 8;
      }
      else {
        uVar8 = uVar7 - 0x18;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
switchD_80291d48_default:
      *param_1 = uVar10;
      param_1[1] = uVar6;
      param_1[2] = uVar8;
      param_1[3] = (uint)puVar9;
      uVar10 = param_2[5];
      if (uVar10 != param_2[4]) {
        uVar10 = -uVar10;
      }
      param_2[5] = uVar10;
      return param_2[5];
    case 0x2c:
    case 0x2d:
    case 0x2f:
      pcVar11 = pcVar11 + 1;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 6 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar10 = uVar10 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      break;
    case 0x2e:
      uVar8 = uVar7 + 8;
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 6 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 8;
      }
      else {
        uVar8 = uVar7 - 0x18;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0x30:
    case 0x31:
    case 0x33:
      pcVar11 = pcVar11 + 5;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar10 = uVar10 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      break;
    case 0x32:
      uVar8 = uVar7 + 8;
      param_2[5] = (int)pcVar11[5];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 8;
      }
      else {
        uVar8 = uVar7 - 0x18;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0x34:
    case 0x35:
    case 0x37:
      pcVar11 = pcVar11 + 5;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar10 = uVar10 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      break;
    case 0x36:
      uVar8 = uVar7 + 8;
      param_2[5] = (int)pcVar11[5];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 8;
      }
      else {
        uVar8 = uVar7 - 0x18;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0x38:
    case 0x39:
    case 0x3b:
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar10 = uVar10 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      break;
    case 0x3a:
      uVar8 = uVar7 + 8;
      param_2[5] = (int)pcVar11[4];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 8;
      }
      else {
        uVar8 = uVar7 - 0x18;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0x3c:
    case 0x3d:
    case 0x3f:
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar10 = uVar10 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      break;
    case 0x3e:
      uVar8 = uVar7 + 8;
      param_2[5] = (int)pcVar11[4];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 8;
      }
      else {
        uVar8 = uVar7 - 0x18;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0x40:
    case 0x41:
    case 0x42:
    case 0x43:
      pcVar11 = pcVar11 + 1;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 5) < 0x20) {
        uVar10 = uVar10 << 5;
        uVar7 = uVar7 + 5;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1b;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1b;
      }
      break;
    case 0x44:
    case 0x45:
      uVar8 = uVar7 + 7;
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 7;
      }
      else {
        uVar8 = uVar7 - 0x19;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0x46:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0x47:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0x48:
    case 0x49:
    case 0x4a:
    case 0x4b:
      pcVar11 = pcVar11 + 1;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 5) < 0x20) {
        uVar10 = uVar10 << 5;
        uVar7 = uVar7 + 5;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1b;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1b;
      }
      break;
    case 0x4c:
    case 0x4d:
      uVar8 = uVar7 + 7;
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 7;
      }
      else {
        uVar8 = uVar7 - 0x19;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0x4e:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0x4f:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0x50:
    case 0x51:
    case 0x52:
    case 0x53:
      pcVar11 = pcVar11 + 3;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 5) < 0x20) {
        uVar10 = uVar10 << 5;
        uVar7 = uVar7 + 5;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1b;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1b;
      }
      break;
    case 0x54:
    case 0x55:
      uVar8 = uVar7 + 7;
      param_2[5] = (int)pcVar11[3];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 7;
      }
      else {
        uVar8 = uVar7 - 0x19;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0x56:
      param_2[5] = (int)pcVar11[3];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0x57:
      param_2[5] = (int)pcVar11[3];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0x58:
    case 0x59:
    case 0x5a:
    case 0x5b:
      pcVar11 = pcVar11 + 3;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 5) < 0x20) {
        uVar10 = uVar10 << 5;
        uVar7 = uVar7 + 5;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1b;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1b;
      }
      break;
    case 0x5c:
    case 0x5d:
      uVar8 = uVar7 + 7;
      param_2[5] = (int)pcVar11[3];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 7;
      }
      else {
        uVar8 = uVar7 - 0x19;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0x5e:
      param_2[5] = (int)pcVar11[3];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0x5f:
      param_2[5] = (int)pcVar11[3];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0x60:
    case 0x61:
    case 0x62:
    case 99:
    case 100:
    case 0x65:
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 4) < 0x20) {
        uVar10 = uVar10 << 4;
        uVar7 = uVar7 + 4;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1c;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1c;
      }
      break;
    case 0x66:
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0x67:
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0x68:
    case 0x69:
    case 0x6a:
    case 0x6b:
      uVar8 = uVar7 + 6;
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 6;
      }
      else {
        uVar8 = uVar7 - 0x1a;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0x6c:
    case 0x6d:
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 3;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0x6e:
    case 0x6f:
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 3;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0x70:
    case 0x71:
    case 0x72:
    case 0x73:
    case 0x74:
    case 0x75:
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 4) < 0x20) {
        uVar10 = uVar10 << 4;
        uVar7 = uVar7 + 4;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1c;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1c;
      }
      break;
    case 0x76:
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0x77:
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0x78:
    case 0x79:
    case 0x7a:
    case 0x7b:
      uVar8 = uVar7 + 6;
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 6;
      }
      else {
        uVar8 = uVar7 - 0x1a;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0x7c:
    case 0x7d:
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 3;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0x7e:
    case 0x7f:
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 3;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0x80:
    case 0x81:
    case 0x82:
    case 0x83:
    case 0x84:
    case 0x85:
    case 0x86:
    case 0x87:
    case 0x88:
    case 0x89:
    case 0x8a:
    case 0x8b:
    case 0x8c:
    case 0x8d:
    case 0x8e:
    case 0x8f:
    case 0x90:
    case 0x91:
    case 0x92:
    case 0x93:
    case 0x94:
    case 0x95:
    case 0x96:
    case 0x97:
    case 0x98:
    case 0x99:
    case 0x9a:
    case 0x9b:
    case 0x9c:
    case 0x9d:
    case 0x9e:
    case 0x9f:
    case 0xa0:
    case 0xa1:
    case 0xa2:
    case 0xa3:
    case 0xa4:
    case 0xa5:
    case 0xa6:
    case 0xa7:
    case 0xa8:
    case 0xa9:
    case 0xaa:
    case 0xab:
    case 0xac:
    case 0xad:
    case 0xae:
    case 0xaf:
    case 0xb0:
    case 0xb1:
    case 0xb2:
    case 0xb3:
    case 0xb4:
    case 0xb5:
    case 0xb6:
    case 0xb7:
    case 0xb8:
    case 0xb9:
    case 0xba:
    case 0xbb:
    case 0xbc:
    case 0xbd:
    case 0xbe:
    case 0xbf:
      uVar8 = uVar7 + 2;
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 2;
      }
      else {
        uVar8 = uVar7 - 0x1e;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0xc0:
    case 0xc1:
    case 0xc2:
    case 0xc3:
    case 0xc4:
    case 0xc5:
    case 0xc6:
    case 199:
      pcVar11 = pcVar11 + 1;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 3) < 0x20) {
        uVar10 = uVar10 << 3;
        uVar7 = uVar7 + 3;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1d;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1d;
      }
      break;
    case 200:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0xc9:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0xca:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0xcb:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0xcc:
    case 0xcd:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 3;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0xce:
    case 0xcf:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 3;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0xd0:
    case 0xd1:
    case 0xd2:
    case 0xd3:
    case 0xd4:
    case 0xd5:
    case 0xd6:
    case 0xd7:
      uVar8 = uVar7 + 5;
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 5;
      }
      else {
        uVar8 = uVar7 - 0x1b;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0xd8:
    case 0xd9:
    case 0xdb:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar10 = uVar10 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      break;
    case 0xda:
      uVar8 = uVar7 + 8;
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 8;
      }
      else {
        uVar8 = uVar7 - 0x18;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0xdc:
    case 0xdd:
    case 0xdf:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar10 = uVar10 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      break;
    case 0xde:
      uVar8 = uVar7 + 8;
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 8;
      }
      else {
        uVar8 = uVar7 - 0x18;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0xe0:
    case 0xe1:
    case 0xe2:
    case 0xe3:
    case 0xe4:
    case 0xe5:
    case 0xe6:
    case 0xe7:
      pcVar11 = pcVar11 + 1;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 3) < 0x20) {
        uVar10 = uVar10 << 3;
        uVar7 = uVar7 + 3;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1d;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1d;
      }
      break;
    case 0xe8:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 4 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0xe9:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 4 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0xea:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0xeb:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 4;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 8) < 0x20) {
        uVar10 = uVar10 << 8;
        uVar7 = uVar7 + 8;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x18;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x18;
      }
      break;
    case 0xec:
    case 0xed:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 3;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0xee:
    case 0xef:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 3;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 7) < 0x20) {
        uVar10 = uVar10 << 7;
        uVar7 = uVar7 + 7;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x19;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x19;
      }
      break;
    case 0xf0:
    case 0xf1:
    case 0xf2:
    case 0xf3:
    case 0xf4:
    case 0xf5:
    case 0xf6:
    case 0xf7:
      uVar8 = uVar7 + 5;
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 5;
      }
      else {
        uVar8 = uVar7 - 0x1b;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0xf8:
    case 0xf9:
    case 0xfb:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar10 = uVar10 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      break;
    case 0xfa:
      uVar8 = uVar7 + 8;
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    (((int)(param_2[9] * 2 *
                                           (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1)
                                    ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 8;
      }
      else {
        uVar8 = uVar7 - 0x18;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
      goto switchD_80291d48_default;
    case 0xfc:
    case 0xfd:
    case 0xff:
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      pcVar11 = pcVar11 + 2;
      param_2[5] = (int)*pcVar11;
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)(uVar7 + 6) < 0x20) {
        uVar10 = uVar10 << 6;
        uVar7 = uVar7 + 6;
      }
      else {
        uVar10 = uVar6 << uVar7 - 0x1a;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
        uVar7 = uVar7 - 0x1a;
      }
      break;
    case 0xfe:
      uVar8 = uVar7 + 8;
      param_2[5] = (int)pcVar11[1];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      param_2[5] = (int)pcVar11[2];
      iVar5 = param_2[5] * 4;
      *(float *)(param_2[7] + iVar5) =
           (float)((double)CONCAT44(0x43300000,
                                    -(((int)(param_2[9] * 2 *
                                            (uint)*(byte *)(param_2[8] + param_2[5])) >> 4) - 1U | 1
                                     ) ^ 0x80000000) - dVar3) * *(float *)(param_1[0xd] + iVar5);
      if ((int)uVar8 < 0x20) {
        uVar10 = uVar10 << 8;
      }
      else {
        uVar8 = uVar7 - 0x18;
        uVar10 = uVar6 << uVar8;
        uVar6 = *puVar9;
        puVar9 = puVar9 + 1;
      }
    default:
      goto switchD_80291d48_default;
    }
  } while( true );
}



// ==== 80295e2c  FUN_80295e2c ====

void FUN_80295e2c(int param_1)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  byte bVar4;
  byte bVar5;
  byte bVar6;
  byte bVar7;
  byte bVar8;
  byte bVar9;
  byte bVar10;
  byte bVar11;
  byte bVar12;
  byte bVar13;
  byte bVar14;
  int iVar15;
  uint *puVar16;
  uint *puVar17;
  int iVar18;
  byte *pbVar19;
  byte *pbVar20;
  int iVar21;
  
  iVar18 = 0;
  iVar15 = *(int *)(param_1 + 0x10);
  pbVar19 = *(byte **)(param_1 + 0x14);
  pbVar20 = *(byte **)(param_1 + 0x18);
  iVar21 = 0x10;
  puVar16 = *(uint **)(param_1 + 8);
  do {
    dataCacheBlockTouch(pbVar20 + iVar15);
    bVar1 = pbVar20[5];
    bVar2 = pbVar19[6];
    bVar3 = pbVar19[4];
    bVar4 = pbVar20[4];
    bVar5 = pbVar19[5];
    bVar6 = pbVar20[6];
    bVar7 = pbVar19[7];
    bVar8 = pbVar20[7];
    bVar9 = pbVar19[8];
    bVar10 = pbVar20[8];
    bVar11 = pbVar19[9];
    bVar12 = pbVar20[9];
    *puVar16 = (uint)pbVar19[3] + (uint)bVar3 + (uint)pbVar20[3] + (uint)bVar4 + 2 >> 2 & 0xff |
               ((uint)pbVar19[2] + (uint)pbVar19[3] + (uint)pbVar20[2] + (uint)pbVar20[3] + 2) *
               0x40 & 0xff00 |
               ((uint)*pbVar19 + (uint)pbVar19[1] + (uint)*pbVar20 + (uint)pbVar20[1] + 2) *
               0x400000 & 0xff000000 |
               ((uint)pbVar19[1] + (uint)pbVar19[2] + (uint)pbVar20[1] + (uint)pbVar20[2] + 2) *
               0x4000 & 0xff0000;
    puVar16[1] = (uint)bVar7 + (uint)bVar9 + (uint)bVar8 + (uint)bVar10 + 2 >> 2 & 0xff |
                 ((uint)bVar2 + (uint)bVar7 + (uint)bVar6 + (uint)bVar8 + 2) * 0x40 & 0xff00 |
                 ((uint)bVar3 + (uint)bVar5 + (uint)bVar4 + (uint)bVar1 + 2) * 0x400000 & 0xff000000
                 | ((uint)bVar5 + (uint)bVar2 + (uint)bVar1 + (uint)bVar6 + 2) * 0x4000 & 0xff0000;
    bVar1 = pbVar20[0xd];
    bVar2 = pbVar19[0xe];
    bVar3 = pbVar19[0xc];
    bVar4 = pbVar20[0xc];
    bVar5 = pbVar20[0xe];
    bVar6 = pbVar19[0xd];
    bVar7 = pbVar19[0xf];
    bVar8 = pbVar19[0x10];
    bVar13 = pbVar20[0xf];
    bVar14 = pbVar20[0x10];
    puVar16[0x10] =
         (uint)pbVar19[0xb] + (uint)bVar3 + (uint)pbVar20[0xb] + (uint)bVar4 + 2 >> 2 & 0xff |
         ((uint)pbVar19[10] + (uint)pbVar19[0xb] + (uint)pbVar20[10] + (uint)pbVar20[0xb] + 2) *
         0x40 & 0xff00 |
         ((uint)bVar9 + (uint)bVar11 + (uint)bVar10 + (uint)bVar12 + 2) * 0x400000 & 0xff000000 |
         ((uint)bVar11 + (uint)pbVar19[10] + (uint)bVar12 + (uint)pbVar20[10] + 2) * 0x4000 &
         0xff0000;
    pbVar19 = pbVar19 + iVar15;
    pbVar20 = pbVar20 + iVar15;
    puVar16[0x11] =
         (uint)bVar7 + (uint)bVar8 + (uint)bVar13 + (uint)bVar14 + 2 >> 2 & 0xff |
         ((uint)bVar2 + (uint)bVar7 + (uint)bVar5 + (uint)bVar13 + 2) * 0x40 & 0xff00 |
         ((uint)bVar3 + (uint)bVar6 + (uint)bVar4 + (uint)bVar1 + 2) * 0x400000 & 0xff000000 |
         ((uint)bVar6 + (uint)bVar2 + (uint)bVar1 + (uint)bVar5 + 2) * 0x4000 & 0xff0000;
    puVar17 = puVar16 + 2;
    if (iVar18 == 7) {
      puVar17 = puVar16 + 0x12;
    }
    iVar18 = iVar18 + 1;
    iVar21 = iVar21 + -1;
    puVar16 = puVar17;
  } while (iVar21 != 0);
  return;
}



// ==== 80296058  FUN_80296058 ====

/* WARNING: Removing unreachable block (ram,0x80296088) */

void FUN_80296058(int param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint *puVar4;
  int *piVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  uint uVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  
  puVar4 = *(uint **)(param_1 + 0x14);
  iVar1 = *(int *)(param_1 + 0x10);
  uVar9 = (uint)puVar4 & 3;
  piVar2 = *(int **)(param_1 + 8);
  if (uVar9 == 2) {
    iVar6 = 0;
    iVar19 = 0x10;
    piVar5 = (int *)((int)puVar4 - 2);
    do {
      dataCacheBlockTouch((int)piVar5 + iVar1);
      uVar11 = piVar5[1];
      uVar16 = piVar5[2];
      uVar14 = piVar5[3];
      uVar8 = piVar5[4];
      uVar10 = *piVar5 << 0x10 | uVar11 >> 0x10;
      uVar9 = *piVar5 << 0x18 | uVar11 >> 8;
      uVar12 = uVar10 ^ uVar9;
      uVar7 = uVar11 << 0x10 | uVar16 >> 0x10;
      uVar18 = uVar11 << 0x18 | uVar16 >> 8;
      uVar13 = uVar7 ^ uVar18;
      *piVar2 = (uVar10 & uVar9) + ((uVar12 & 0xfefefefe) >> 1) + (uVar12 & 0x1010101);
      uVar9 = uVar16 << 0x10 | uVar14 >> 0x10;
      uVar11 = uVar16 << 0x18 | uVar14 >> 8;
      uVar12 = uVar9 ^ uVar11;
      uVar10 = uVar14 << 0x10 | uVar8 >> 0x10;
      uVar8 = uVar14 << 0x18 | uVar8 >> 8;
      uVar14 = uVar10 ^ uVar8;
      piVar2[1] = (uVar7 & uVar18) + ((uVar13 & 0xfefefefe) >> 1) + (uVar13 & 0x1010101);
      piVar2[0x10] = (uVar9 & uVar11) + ((uVar12 & 0xfefefefe) >> 1) + (uVar12 & 0x1010101);
      piVar5 = (int *)((int)piVar5 + iVar1);
      piVar2[0x11] = (uVar10 & uVar8) + ((uVar14 & 0xfefefefe) >> 1) + (uVar14 & 0x1010101);
      piVar3 = piVar2 + 2;
      if (iVar6 == 7) {
        piVar3 = piVar2 + 0x12;
      }
      iVar6 = iVar6 + 1;
      iVar19 = iVar19 + -1;
      piVar2 = piVar3;
    } while (iVar19 != 0);
  }
  else if (uVar9 < 2) {
    if (uVar9 == 0) {
      iVar6 = 0;
      iVar19 = 0x10;
      do {
        dataCacheBlockTouch((int)puVar4 + iVar1);
        uVar7 = puVar4[1];
        uVar8 = puVar4[2];
        uVar12 = *puVar4;
        uVar15 = puVar4[3];
        uVar13 = uVar12 << 8 | uVar7 >> 0x18;
        uVar14 = uVar12 ^ uVar13;
        uVar11 = uVar7 << 8 | uVar8 >> 0x18;
        uVar16 = uVar7 ^ uVar11;
        uVar18 = uVar8 << 8 | uVar15 >> 0x18;
        uVar17 = uVar8 ^ uVar18;
        uVar10 = uVar15 << 8 | (uint)*(byte *)(puVar4 + 4);
        uVar9 = uVar15 ^ uVar10;
        *piVar2 = (uVar12 & uVar13) + ((uVar14 & 0xfefefefe) >> 1) + (uVar14 & 0x1010101);
        piVar2[1] = (uVar7 & uVar11) + ((uVar16 & 0xfefefefe) >> 1) + (uVar16 & 0x1010101);
        piVar2[0x10] = (uVar8 & uVar18) + ((uVar17 & 0xfefefefe) >> 1) + (uVar17 & 0x1010101);
        puVar4 = (uint *)((int)puVar4 + iVar1);
        piVar2[0x11] = (uVar15 & uVar10) + ((uVar9 & 0xfefefefe) >> 1) + (uVar9 & 0x1010101);
        piVar5 = piVar2 + 2;
        if (iVar6 == 7) {
          piVar5 = piVar2 + 0x12;
        }
        iVar6 = iVar6 + 1;
        iVar19 = iVar19 + -1;
        piVar2 = piVar5;
      } while (iVar19 != 0);
    }
    else {
      iVar6 = 0;
      iVar19 = 0x10;
      piVar5 = (int *)((int)puVar4 - 1);
      do {
        dataCacheBlockTouch((int)piVar5 + iVar1);
        uVar11 = piVar5[1];
        uVar14 = piVar5[2];
        uVar16 = piVar5[3];
        uVar8 = piVar5[4];
        uVar10 = *piVar5 << 8 | uVar11 >> 0x18;
        uVar9 = *piVar5 << 0x10 | uVar11 >> 0x10;
        uVar12 = uVar10 ^ uVar9;
        uVar7 = uVar11 << 8 | uVar14 >> 0x18;
        uVar18 = uVar11 << 0x10 | uVar14 >> 0x10;
        uVar13 = uVar7 ^ uVar18;
        *piVar2 = (uVar10 & uVar9) + ((uVar12 & 0xfefefefe) >> 1) + (uVar12 & 0x1010101);
        uVar9 = uVar14 << 8 | uVar16 >> 0x18;
        uVar11 = uVar14 << 0x10 | uVar16 >> 0x10;
        uVar12 = uVar9 ^ uVar11;
        uVar10 = uVar16 << 8 | uVar8 >> 0x18;
        uVar8 = uVar16 << 0x10 | uVar8 >> 0x10;
        uVar14 = uVar10 ^ uVar8;
        piVar2[1] = (uVar7 & uVar18) + ((uVar13 & 0xfefefefe) >> 1) + (uVar13 & 0x1010101);
        piVar2[0x10] = (uVar9 & uVar11) + ((uVar12 & 0xfefefefe) >> 1) + (uVar12 & 0x1010101);
        piVar5 = (int *)((int)piVar5 + iVar1);
        piVar2[0x11] = (uVar10 & uVar8) + ((uVar14 & 0xfefefefe) >> 1) + (uVar14 & 0x1010101);
        piVar3 = piVar2 + 2;
        if (iVar6 == 7) {
          piVar3 = piVar2 + 0x12;
        }
        iVar6 = iVar6 + 1;
        iVar19 = iVar19 + -1;
        piVar2 = piVar3;
      } while (iVar19 != 0);
    }
  }
  else if (uVar9 < 4) {
    iVar6 = 0;
    iVar19 = 0x10;
    piVar5 = (int *)((int)puVar4 - 3);
    do {
      dataCacheBlockTouch((int)piVar5 + iVar1);
      uVar10 = piVar5[1];
      uVar15 = piVar5[2];
      uVar18 = piVar5[3];
      uVar12 = *piVar5 << 0x18 | uVar10 >> 8;
      uVar16 = piVar5[4];
      uVar14 = uVar12 ^ uVar10;
      uVar7 = uVar10 << 0x18 | uVar15 >> 8;
      uVar13 = uVar7 ^ uVar15;
      uVar11 = uVar15 << 0x18 | uVar18 >> 8;
      uVar9 = uVar11 ^ uVar18;
      uVar8 = uVar18 << 0x18 | uVar16 >> 8;
      *piVar2 = (uVar12 & uVar10) + ((uVar14 & 0xfefefefe) >> 1) + (uVar14 & 0x1010101);
      uVar10 = uVar8 ^ uVar16;
      piVar2[1] = (uVar7 & uVar15) + ((uVar13 & 0xfefefefe) >> 1) + (uVar13 & 0x1010101);
      piVar2[0x10] = (uVar11 & uVar18) + ((uVar9 & 0xfefefefe) >> 1) + (uVar9 & 0x1010101);
      piVar5 = (int *)((int)piVar5 + iVar1);
      piVar2[0x11] = (uVar8 & uVar16) + ((uVar10 & 0xfefefefe) >> 1) + (uVar10 & 0x1010101);
      piVar3 = piVar2 + 2;
      if (iVar6 == 7) {
        piVar3 = piVar2 + 0x12;
      }
      iVar6 = iVar6 + 1;
      iVar19 = iVar19 + -1;
      piVar2 = piVar3;
    } while (iVar19 != 0);
  }
  return;
}



// ==== 802964c8  FUN_802964c8 ====

/* WARNING: Removing unreachable block (ram,0x80296500) */

void FUN_802964c8(int param_1)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  uint *puVar4;
  int *piVar5;
  uint *puVar6;
  int *piVar7;
  uint uVar8;
  int iVar9;
  uint uVar10;
  uint uVar11;
  uint uVar12;
  uint uVar13;
  uint uVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  uint uVar18;
  uint uVar19;
  int iVar20;
  
  puVar6 = *(uint **)(param_1 + 0x18);
  puVar4 = *(uint **)(param_1 + 0x14);
  piVar2 = *(int **)(param_1 + 8);
  iVar1 = *(int *)(param_1 + 0x10);
  dataCacheBlockTouch(puVar6);
  uVar8 = (uint)puVar4 & 3;
  if (uVar8 == 2) {
    iVar9 = 0;
    iVar20 = 0x10;
    piVar5 = (int *)((int)puVar4 - 2);
    piVar7 = (int *)((int)puVar6 + -2);
    do {
      dataCacheBlockTouch((int)piVar7 + iVar1);
      uVar10 = *piVar5 << 0x10 | (uint)piVar5[1] >> 0x10;
      uVar11 = *piVar7 << 0x10 | (uint)piVar7[1] >> 0x10;
      uVar14 = uVar10 ^ uVar11;
      uVar12 = piVar5[1] << 0x10 | (uint)piVar5[2] >> 0x10;
      uVar19 = piVar7[1] << 0x10 | (uint)piVar7[2] >> 0x10;
      uVar13 = uVar12 ^ uVar19;
      uVar17 = piVar7[2] << 0x10 | (uint)piVar7[3] >> 0x10;
      uVar18 = piVar5[2] << 0x10 | (uint)piVar5[3] >> 0x10;
      uVar8 = uVar18 ^ uVar17;
      uVar16 = piVar5[3] << 0x10 | (uint)*(ushort *)(piVar5 + 4);
      uVar15 = piVar7[3] << 0x10 | (uint)*(ushort *)(piVar7 + 4);
      *piVar2 = (uVar10 & uVar11) + ((uVar14 & 0xfefefefe) >> 1) + (uVar14 & 0x1010101);
      uVar10 = uVar16 ^ uVar15;
      piVar2[1] = (uVar12 & uVar19) + ((uVar13 & 0xfefefefe) >> 1) + (uVar13 & 0x1010101);
      piVar2[0x10] = (uVar18 & uVar17) + ((uVar8 & 0xfefefefe) >> 1) + (uVar8 & 0x1010101);
      piVar5 = (int *)((int)piVar5 + iVar1);
      piVar7 = (int *)((int)piVar7 + iVar1);
      piVar2[0x11] = (uVar16 & uVar15) + ((uVar10 & 0xfefefefe) >> 1) + (uVar10 & 0x1010101);
      piVar3 = piVar2 + 2;
      if (iVar9 == 7) {
        piVar3 = piVar2 + 0x12;
      }
      iVar9 = iVar9 + 1;
      iVar20 = iVar20 + -1;
      piVar2 = piVar3;
    } while (iVar20 != 0);
  }
  else if (uVar8 < 2) {
    if (uVar8 == 0) {
      iVar9 = 0;
      iVar20 = 0x10;
      do {
        dataCacheBlockTouch((int)puVar6 + iVar1);
        uVar12 = puVar4[1];
        uVar10 = *puVar4 ^ *puVar6;
        uVar13 = puVar6[1];
        uVar14 = puVar4[2];
        uVar18 = uVar12 ^ uVar13;
        uVar15 = puVar6[2];
        uVar16 = puVar4[3];
        uVar17 = puVar6[3];
        uVar8 = uVar14 ^ uVar15;
        uVar11 = uVar16 ^ uVar17;
        *piVar2 = (*puVar4 & *puVar6) + ((uVar10 & 0xfefefefe) >> 1) + (uVar10 & 0x1010101);
        piVar2[1] = (uVar12 & uVar13) + ((uVar18 & 0xfefefefe) >> 1) + (uVar18 & 0x1010101);
        piVar2[0x10] = (uVar14 & uVar15) + ((uVar8 & 0xfefefefe) >> 1) + (uVar8 & 0x1010101);
        puVar4 = (uint *)((int)puVar4 + iVar1);
        puVar6 = (uint *)((int)puVar6 + iVar1);
        piVar2[0x11] = (uVar16 & uVar17) + ((uVar11 & 0xfefefefe) >> 1) + (uVar11 & 0x1010101);
        piVar5 = piVar2 + 2;
        if (iVar9 == 7) {
          piVar5 = piVar2 + 0x12;
        }
        iVar9 = iVar9 + 1;
        iVar20 = iVar20 + -1;
        piVar2 = piVar5;
      } while (iVar20 != 0);
    }
    else {
      iVar9 = 0;
      iVar20 = 0x10;
      piVar5 = (int *)((int)puVar4 - 1);
      piVar7 = (int *)((int)puVar6 + -1);
      do {
        dataCacheBlockTouch((int)piVar7 + iVar1);
        uVar10 = *piVar5 << 8 | (uint)piVar5[1] >> 0x18;
        uVar11 = *piVar7 << 8 | (uint)piVar7[1] >> 0x18;
        uVar19 = uVar10 ^ uVar11;
        uVar18 = piVar7[1] << 8 | (uint)piVar7[2] >> 0x18;
        uVar12 = piVar5[1] << 8 | (uint)piVar5[2] >> 0x18;
        uVar17 = piVar5[2] << 8 | (uint)piVar5[3] >> 0x18;
        uVar13 = uVar12 ^ uVar18;
        uVar16 = piVar7[2] << 8 | (uint)piVar7[3] >> 0x18;
        uVar8 = uVar17 ^ uVar16;
        uVar15 = piVar5[3] << 8 | (uint)*(byte *)(piVar5 + 4);
        uVar14 = piVar7[3] << 8 | (uint)*(byte *)(piVar7 + 4);
        *piVar2 = (uVar10 & uVar11) + ((uVar19 & 0xfefefefe) >> 1) + (uVar19 & 0x1010101);
        uVar10 = uVar15 ^ uVar14;
        piVar2[1] = (uVar12 & uVar18) + ((uVar13 & 0xfefefefe) >> 1) + (uVar13 & 0x1010101);
        piVar2[0x10] = (uVar17 & uVar16) + ((uVar8 & 0xfefefefe) >> 1) + (uVar8 & 0x1010101);
        piVar5 = (int *)((int)piVar5 + iVar1);
        piVar7 = (int *)((int)piVar7 + iVar1);
        piVar2[0x11] = (uVar15 & uVar14) + ((uVar10 & 0xfefefefe) >> 1) + (uVar10 & 0x1010101);
        piVar3 = piVar2 + 2;
        if (iVar9 == 7) {
          piVar3 = piVar2 + 0x12;
        }
        iVar9 = iVar9 + 1;
        iVar20 = iVar20 + -1;
        piVar2 = piVar3;
      } while (iVar20 != 0);
    }
  }
  else if (uVar8 < 4) {
    iVar9 = 0;
    iVar20 = 0x10;
    piVar5 = (int *)((int)puVar4 - 3);
    piVar7 = (int *)((int)puVar6 + -3);
    do {
      dataCacheBlockTouch((int)piVar7 + iVar1);
      uVar10 = *piVar5 << 0x18 | (uint)piVar5[1] >> 8;
      uVar11 = *piVar7 << 0x18 | (uint)piVar7[1] >> 8;
      uVar13 = uVar10 ^ uVar11;
      uVar17 = piVar7[2] << 0x18 | (uint)piVar7[3] >> 8;
      uVar18 = piVar5[2] << 0x18 | (uint)piVar5[3] >> 8;
      uVar12 = piVar5[1] << 0x18 | (uint)piVar5[2] >> 8;
      uVar19 = piVar7[1] << 0x18 | (uint)piVar7[2] >> 8;
      uVar14 = uVar12 ^ uVar19;
      uVar8 = uVar18 ^ uVar17;
      uVar16 = piVar5[3] << 0x18 | (uint)piVar5[4] >> 8;
      uVar15 = piVar7[3] << 0x18 | (uint)piVar7[4] >> 8;
      *piVar2 = (uVar10 & uVar11) + ((uVar13 & 0xfefefefe) >> 1) + (uVar13 & 0x1010101);
      uVar10 = uVar16 ^ uVar15;
      piVar2[1] = (uVar12 & uVar19) + ((uVar14 & 0xfefefefe) >> 1) + (uVar14 & 0x1010101);
      piVar2[0x10] = (uVar18 & uVar17) + ((uVar8 & 0xfefefefe) >> 1) + (uVar8 & 0x1010101);
      piVar5 = (int *)((int)piVar5 + iVar1);
      piVar7 = (int *)((int)piVar7 + iVar1);
      piVar2[0x11] = (uVar16 & uVar15) + ((uVar10 & 0xfefefefe) >> 1) + (uVar10 & 0x1010101);
      piVar3 = piVar2 + 2;
      if (iVar9 == 7) {
        piVar3 = piVar2 + 0x12;
      }
      iVar9 = iVar9 + 1;
      iVar20 = iVar20 + -1;
      piVar2 = piVar3;
    } while (iVar20 != 0);
  }
  return;
}



// ==== 80296fe8  zz_0296fe8_ ====

undefined4 zz_0296fe8_(void)

{
  return 0xffffffff;
}



// ==== 80296ff0  zz_0296ff0_ ====

undefined4 zz_0296ff0_(void)

{
  return 0xffffffff;
}



// ==== 80296ff8  zz_0296ff8_ ====

void zz_0296ff8_(void)

{
  return;
}



// ==== 80296ffc  zz_0296ffc_ ====

undefined4 zz_0296ffc_(void)

{
  return 0;
}



// ==== 80297004  zz_0297004_ ====

void zz_0297004_(void)

{
  return;
}



// ==== 80297008  zz_0297008_ ====

void zz_0297008_(void)

{
  return;
}



// ==== 8029700c  FUN_8029700c ====

undefined4
FUN_8029700c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9)

{
  int *piVar1;
  int iVar2;
  int *piVar3;
  
  piVar3 = *(int **)(param_9 + 0x1b74);
  if (*(int *)(param_9 + 0x2898) == 0) {
    piVar1 = (int *)0x0;
  }
  else if (piVar3[0x10] < 1) {
    piVar1 = (int *)(*(int *)(param_9 + 0x2898) + 0xcfc);
  }
  else {
    piVar1 = (int *)0x0;
  }
  if (((piVar1 != (int *)0x0) && (iVar2 = *piVar3, piVar3[0xd] == 0)) && (*piVar1 != 0)) {
    zz_026a3f4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,piVar1[3],
                piVar1[4],piVar1[5]);
    zz_026e344_(iVar2,0);
    piVar3[0xd] = 1;
    piVar3[0xf] = (int)FUN_802978e4;
  }
  return 0;
}



// ==== 802970dc  FUN_802970dc ====

void FUN_802970dc(int param_1)

{
  zz_029abec_(param_1,-0xfff3fd);
  return;
}



// ==== 80297104  FUN_80297104 ====

void FUN_80297104(int param_1)

{
  zz_029abec_(param_1,-0xfff3fd);
  return;
}



// ==== 8029712c  FUN_8029712c ====

void FUN_8029712c(int param_1)

{
  zz_029abec_(param_1,-0xfff3fd);
  return;
}



// ==== 80297154  FUN_80297154 ====

void FUN_80297154(int param_1)

{
  zz_029abec_(param_1,-0xfff3fd);
  return;
}



// ==== 8029717c  FUN_8029717c ====

undefined4
FUN_8029717c(undefined8 param_1,double param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
            int param_10,undefined4 param_11,int param_12,int param_13,undefined4 param_14,
            undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined8 uVar7;
  uint local_38;
  void **local_34;
  int local_30;
  int local_2c;
  int local_28;
  uint local_24;
  
  piVar6 = *(int **)(param_9 + 0x1b74);
  iVar5 = *piVar6;
  if (param_10 == 1) {
    zz_026e4b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,1,param_11,
                param_12,param_13,param_14,param_15,param_16);
    zz_02a6b28_((undefined4 *)(param_9 + 0xf60),1);
  }
  else if (param_10 < 1) {
    if (-1 < param_10) {
      piVar6[0xc] = 0;
      if ((*(int **)(param_9 + 0x1b74))[0xb] != 1) {
        zz_026e4b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    **(int **)(param_9 + 0x1b74),0,param_11,param_12,param_13,param_14,param_15,
                    param_16);
        zz_02a6b28_((undefined4 *)(param_9 + 0xf60),0);
      }
    }
  }
  else if (param_10 < 3) {
    iVar2 = zz_026ee64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                        param_10,param_11,param_12,param_13,param_14,param_15,param_16);
    if ((iVar2 == 0) || (iVar2 == 1)) {
      bVar1 = false;
    }
    else {
      bVar1 = true;
    }
    if (bVar1) {
      uVar3 = zz_026e8c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                          param_10,param_11,param_12,param_13,param_14,param_15,param_16);
      uVar7 = zz_02a41ac_(param_9,&local_38,&local_34);
      iVar4 = zz_02a953c_(uVar3,local_38,(uint)local_34);
      iVar2 = piVar6[0xc];
      iVar5 = zz_026e34c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                          iVar4 + iVar2,local_34,param_12,param_13,param_14,param_15,param_16);
      local_30 = iVar4 >> 0x1f;
      piVar6[0xc] = (iVar4 + iVar2) - iVar5;
      local_28 = (int)uVar3 >> 0x1f;
      local_2c = iVar4;
      local_24 = uVar3;
      zz_02a6aa0_(param_9 + 0xf60,&local_30);
    }
  }
  return 0;
}



// ==== 802972c8  FUN_802972c8 ====

undefined4
FUN_802972c8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
            undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
            undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_026eea4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              **(int **)(param_9 + 0x1b74),param_10,param_11,param_12,param_13,param_14,param_15,
              param_16);
  return 0;
}



// ==== 802972f4  FUN_802972f4 ====

undefined4
FUN_802972f4(undefined8 param_1,double param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
            undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
            undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  
  piVar1 = *(int **)(param_9 + 0x1b74);
  piVar1[0xb] = 0;
  if (*(int *)(param_9 + 0x50) != 1) {
    zz_026e4b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar1,0,piVar1,
                param_12,param_13,param_14,param_15,param_16);
    zz_02a6b28_((undefined4 *)(param_9 + 0xf60),0);
  }
  return 0;
}



// ==== 8029735c  FUN_8029735c ====

undefined4
FUN_8029735c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
            undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
            undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  int *piVar4;
  char *pcVar5;
  
  puVar3 = *(undefined4 **)(param_9 + 0x1b74);
  pcVar5 = (char *)*puVar3;
  piVar4 = (int *)puVar3[1];
  if (pcVar5 != (char *)0x0) {
    DAT_8041cff8 = puVar3[2];
    DAT_8041cffc = puVar3[3];
    puVar2 = &DAT_8041cff8;
    DAT_8041d000 = puVar3[4];
    DAT_8041d004 = puVar3[5];
    DAT_8041d008 = puVar3[6];
    DAT_8041d00c = puVar3[7];
    DAT_8041d010 = puVar3[8];
    iVar1 = zz_02a1168_();
    if (iVar1 == 1) {
      zz_026eea4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  **(int **)(param_9 + 0x1b74),puVar2,puVar3,param_12,param_13,param_14,param_15,
                  param_16);
      DAT_8041d42c = pcVar5;
    }
    else {
      zz_026f31c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,pcVar5,puVar2,
                  puVar3,param_12,param_13,param_14,param_15,param_16);
    }
    (**(code **)(*piVar4 + 0xc))(piVar4);
  }
  return 0;
}



// ==== 8029743c  FUN_8029743c ====

undefined4
FUN_8029743c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,int param_9,
            int *param_10,int *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
            undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  uint local_58;
  uint local_54;
  uint local_50;
  uint local_4c;
  int local_48;
  uint local_44;
  undefined8 local_40;
  undefined8 local_38;
  uint uStack_30;
  int local_2c;
  int local_24;
  
  piVar5 = *(int **)(param_9 + 0x1b74);
  iVar4 = *piVar5;
  piVar2 = param_10;
  piVar3 = param_11;
  iVar1 = zz_02a4648_(param_9,param_10,param_11);
  if (iVar1 != 0) {
    if (*(int *)(param_9 + 0x48) == 4) {
      DAT_8041cff0 = zz_026ee64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                 iVar4,piVar2,piVar3,param_12,param_13,param_14,param_15,param_16);
      zz_026e970_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,&local_58,
                  &local_54,&DAT_8041cff0,param_13,param_14,param_15,param_16);
      local_50 = (int)local_58 >> 0x1f;
      local_4c = local_58;
      local_48 = (int)local_54 >> 0x1f;
      local_44 = local_54;
      local_40 = zz_02a9654_();
      local_38 = glGetCurrentTextureState_void_();
      zz_02a5fdc_((int *)(param_9 + 0xf60),&local_50,(int *)&local_40,&uStack_30);
      if (piVar5[9] < local_2c) {
        piVar5[9] = local_2c;
        piVar5[10] = local_24;
      }
    }
    *param_10 = piVar5[9];
    *param_11 = piVar5[10];
  }
  return 0;
}



// ==== 80297538  zz_0297538_ ====

int zz_0297538_(int param_1,undefined4 *param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_48;
  int local_44;
  undefined4 local_40;
  undefined4 local_3c;
  int local_38;
  int local_34;
  undefined4 local_30;
  undefined4 local_2c;
  int local_28;
  int local_24;
  undefined4 local_20;
  undefined4 local_1c;
  int local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  
  uVar1 = DAT_8041cffc;
  if ((DAT_8041d000 == 0) || (DAT_8041d010 == 0)) {
    iVar2 = zz_029abec_(param_1,-0xfff3fa);
  }
  else {
    param_2[2] = DAT_8041cff8;
    puVar3 = (undefined4 *)(param_1 + 0xf60);
    param_2[3] = uVar1;
    uVar1 = DAT_8041d004;
    param_2[4] = DAT_8041d000;
    param_2[5] = uVar1;
    uVar1 = DAT_8041d00c;
    param_2[6] = DAT_8041d008;
    param_2[7] = uVar1;
    param_2[8] = DAT_8041d010;
    *param_2 = 0;
    param_2[1] = 0;
    param_2[9] = 0xffffffff;
    param_2[10] = 1;
    param_2[0xb] = 0;
    param_2[0xc] = 0;
    param_2[0xd] = 0;
    param_2[0xe] = 0;
    param_2[0xf] = FUN_80297db4;
    param_2[0x10] = 0;
    param_2[0x11] = 0xffffffff;
    param_2[0x12] = 0;
    local_14 = cTeam__GetPlayer_int_(param_1,0x3f);
    local_18 = local_14 >> 0x1f;
    local_c = 1000000;
    local_10 = 0;
    local_24 = cTeam__GetPlayer_int_(param_1,0x40);
    local_28 = local_24 >> 0x1f;
    local_1c = 1000000;
    local_20 = 0;
    local_34 = cTeam__GetPlayer_int_(param_1,0x41);
    local_38 = local_34 >> 0x1f;
    local_2c = 1000000;
    local_30 = 0;
    local_44 = cTeam__GetPlayer_int_(param_1,0x42);
    local_48 = local_44 >> 0x1f;
    local_3c = 1000000;
    local_40 = 0;
    zz_02a6b90_(puVar3);
    zz_02a6b7c_((int)puVar3,(undefined8 *)&local_18);
    zz_02a6b68_((int)puVar3,(undefined8 *)&local_28);
    zz_02a6b54_((int)puVar3,(undefined8 *)&local_38);
    zz_02a6b40_((int)puVar3,(undefined8 *)&local_48);
    iVar2 = cTeam__GetPlayer_int_(param_1,0x3e);
    zz_02a6b30_((int)puVar3,iVar2);
    cTeam__GetPlayer_int_(param_1,0x3d);
    zz_02a966c_();
    iVar2 = 0;
  }
  return iVar2;
}



