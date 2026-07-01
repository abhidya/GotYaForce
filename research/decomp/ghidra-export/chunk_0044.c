// ==== 8017349c  FUN_8017349c ====

void FUN_8017349c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
  zz_017354c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_0027aac_(0,0x1e,1);
  zz_00e9b60_((double)FLOAT_8043acd8,2,0x1e,2);
  return;
}



// ==== 801734f0  FUN_801734f0 ====

void FUN_801734f0(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    *(undefined2 *)PTR_DAT_80433944 = 2;
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 2) = 0;
    zz_002a5f4_(0,0,0,0);
  }
  return;
}



// ==== 8017354c  zz_017354c_ ====

void zz_017354c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  char cVar2;
  short sVar3;
  undefined2 uVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  short *psVar12;
  undefined *puVar13;
  short sVar14;
  int iVar15;
  int iVar16;
  uint uVar17;
  int iVar18;
  int iVar19;
  undefined2 *puVar20;
  int iVar21;
  int iVar22;
  int iVar23;
  int iVar24;
  int iVar25;
  int iVar26;
  undefined8 uVar27;
  undefined2 local_2a8 [2];
  undefined2 local_2a4 [2];
  undefined2 local_2a0 [2];
  short local_29c [58];
  undefined4 local_228;
  int local_224 [18];
  short local_1dc [204];
  
  iVar11 = 0;
  iVar10 = 0;
  do {
    iVar26 = 5;
    iVar22 = 0;
    do {
      *(undefined2 *)(PTR_DAT_80433934 + iVar10 + iVar22 + 0x1e8) = 0xffff;
      PTR_DAT_80433934[iVar10 + iVar22 + 0x1ea] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar10 + iVar22 + 0x204) = 0xffff;
      PTR_DAT_80433934[iVar10 + iVar22 + 0x206] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar10 + iVar22 + 0x220) = 0xffff;
      PTR_DAT_80433934[iVar10 + iVar22 + 0x222] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar10 + iVar22 + 0x23c) = 0xffff;
      PTR_DAT_80433934[iVar10 + iVar22 + 0x23e] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar10 + iVar22 + 600) = 0xffff;
      PTR_DAT_80433934[iVar10 + iVar22 + 0x25a] = 0;
      *(undefined2 *)(PTR_DAT_80433934 + iVar10 + iVar22 + 0x274) = 0xffff;
      PTR_DAT_80433934[iVar10 + iVar22 + 0x276] = 0;
      iVar26 = iVar26 + -1;
      iVar22 = iVar22 + 0xa8;
    } while (iVar26 != 0);
    iVar11 = iVar11 + 1;
    iVar10 = iVar10 + 0x348;
  } while (iVar11 < 6);
  iVar22 = 0;
  iVar10 = 0;
  PTR_DAT_80433934[0x15d9] = 0;
  iVar23 = 0;
  iVar26 = 0;
  iVar11 = 0;
  PTR_DAT_80433934[0x15da] = 0;
  do {
    puVar13 = PTR_DAT_80433944;
    if ((iVar22 < 4) &&
       (iVar6 = iVar22 + 0x28, (PTR_DAT_80433944[(char)PTR_DAT_80433944[iVar6] + 0x20] & 0x40) == 0)
       ) {
      PTR_DAT_80433934[0x15da] = PTR_DAT_80433934[0x15da] + '\x01';
      PTR_DAT_80433934[0x15d9] = PTR_DAT_80433934[0x15d9] | (byte)(1 << iVar22);
      PTR_DAT_80433934[iVar22 + 0xcb] = PTR_DAT_80433944[iVar6] & 1;
      PTR_DAT_80433934[iVar22 + 0x20] = (char)iVar22;
      PTR_DAT_80433934[iVar22 + 0x3e] = 3;
      PTR_DAT_80433934[iVar22 + 0x32] = 4;
      cVar1 = PTR_DAT_80433944[(char)PTR_DAT_80433944[iVar6] + 0x20];
      iVar6 = *(int *)(PTR_DAT_80433934 + (char)PTR_DAT_80433934[iVar22 + 0xcb] * 0x3c + 0x120);
      if ((char)puVar13[iVar10 + 0x161] < '\0') {
        local_29c[1] = 0xffff;
        local_29c[0] = -1;
        local_29c[3] = 0xffff;
        local_29c[2] = 0xffff;
        local_29c[5] = 0xffff;
        local_29c[4] = 0xffff;
        local_29c[7] = 0xffff;
        local_29c[6] = 0xffff;
        local_29c[9] = 0xffff;
        local_29c[8] = 0xffff;
        local_29c[0xb] = 0xffff;
        local_29c[10] = 0xffff;
        local_29c[0xd] = 0xffff;
        local_29c[0xc] = 0xffff;
        local_29c[0xf] = 0xffff;
        local_29c[0xe] = 0xffff;
        local_29c[0x11] = 0xffff;
        local_29c[0x10] = 0xffff;
        local_29c[0x13] = 0xffff;
        local_29c[0x12] = 0xffff;
        local_29c[0x15] = 0xffff;
        local_29c[0x14] = 0xffff;
        local_29c[0x17] = 0xffff;
        local_29c[0x16] = 0xffff;
        local_29c[0x19] = 0xffff;
        local_29c[0x18] = 0xffff;
        local_29c[0x1b] = 0xffff;
        local_29c[0x1a] = 0xffff;
        local_29c[0x1d] = 0xffff;
        local_29c[0x1c] = 0xffff;
        local_29c[0x1f] = 0xffff;
        local_29c[0x1e] = 0xffff;
        local_29c[0x21] = 0xffff;
        local_29c[0x20] = 0xffff;
        local_29c[0x23] = 0xffff;
        local_29c[0x22] = 0xffff;
        local_29c[0x25] = 0xffff;
        local_29c[0x24] = 0xffff;
        local_29c[0x27] = 0xffff;
        local_29c[0x26] = 0xffff;
        local_29c[0x29] = 0xffff;
        local_29c[0x28] = 0xffff;
        local_29c[0x2b] = 0xffff;
        local_29c[0x2a] = 0xffff;
        local_29c[0x2d] = 0xffff;
        local_29c[0x2c] = 0xffff;
        local_29c[0x2f] = 0xffff;
        local_29c[0x2e] = 0xffff;
        local_29c[0x31] = 0xffff;
        local_29c[0x30] = 0xffff;
        local_29c[0x33] = 0xffff;
        local_29c[0x32] = 0xffff;
        local_29c[0x35] = 0xffff;
        local_29c[0x34] = 0xffff;
        local_29c[0x37] = 0xffff;
        local_29c[0x36] = 0xffff;
        local_29c[0x39] = 0xffff;
        local_29c[0x38] = 0xffff;
        local_228._2_2_ = 0xffff;
        local_228._0_2_ = 0xffff;
        iVar16 = 0;
        PTR_DAT_80433934[iVar22 + 0x5a] = 0;
        for (iVar18 = 0; iVar18 < 0x1e; iVar18 = iVar18 + 1) {
          uVar8 = zz_00055fc_();
          uVar17 = 0;
          iVar24 = 0;
          iVar25 = (uVar8 & 0xff) -
                   ((uVar8 & 0xff) / (uint)(int)(char)PTR_DAT_80433944[0x90]) *
                   (int)(char)PTR_DAT_80433944[0x90];
          iVar7 = (&DAT_803bfe00)[(char)PTR_DAT_80433944[iVar25 + 0x88]];
          iVar19 = iVar7;
          for (iVar21 = 0; iVar21 < 200; iVar21 = iVar21 + 1) {
            if (-1 < *(short *)(iVar19 + 0x870)) {
              local_2a4[0] = *(undefined2 *)(iVar19 + 0x870);
              uVar8 = zz_0066168_((char *)local_2a4,(int)*(char *)(iVar19 + 0x872));
              if (cVar1 < '\0') {
                uVar8 = (int)(uVar8 << 1) / 3 + ((int)(uVar8 << 1 | uVar8 >> 0x1f) >> 0x1f) +
                        ((uVar8 & 0x7fffffff) >> 0x1e);
              }
              if (-1 < (int)((iVar6 - iVar16) - uVar8)) {
                bVar5 = false;
                psVar12 = local_29c;
                iVar15 = 0;
                while ((iVar15 < (char)PTR_DAT_80433934[iVar22 + 0x5a] && (!bVar5))) {
                  if (((int)(char)PTR_DAT_80433944[iVar25 + 0x88] == (int)*psVar12) &&
                     (iVar21 == psVar12[1])) {
                    bVar5 = true;
                  }
                  psVar12 = psVar12 + 2;
                  iVar15 = iVar15 + 1;
                }
                if (!bVar5) {
                  uVar17 = uVar17 + 1;
                  *(short *)((int)local_1dc + iVar24) = (short)iVar21;
                  iVar24 = iVar24 + 2;
                }
              }
            }
            iVar19 = iVar19 + 0x20;
          }
          if (uVar17 == 0) {
            iVar18 = 0x1e;
          }
          else {
            uVar8 = zz_00055fc_();
            sVar14 = local_1dc[(uVar8 & 0xff) - ((uVar8 & 0xff) / uVar17) * uVar17];
            puVar20 = (undefined2 *)(iVar7 + sVar14 * 0x20 + 0x870);
            local_2a8[0] = *puVar20;
            uVar8 = zz_0066168_((char *)local_2a8,(int)*(char *)(puVar20 + 1));
            if (cVar1 < '\0') {
              uVar8 = (int)(uVar8 << 1) / 3 + ((int)(uVar8 << 1 | uVar8 >> 0x1f) >> 0x1f) +
                      ((uVar8 & 0x7fffffff) >> 0x1e);
            }
            uVar4 = *puVar20;
            iVar16 = iVar16 + uVar8;
            iVar19 = (int)(char)PTR_DAT_80433934[iVar22 + 0x5a];
            local_29c[iVar19 * 2] = (short)(char)PTR_DAT_80433944[iVar25 + 0x88];
            local_29c[iVar19 * 2 + 1] = sVar14;
            *(undefined2 *)(PTR_DAT_80433934 + iVar23 + iVar19 * 0x1c + 0x1e8) = uVar4;
            PTR_DAT_80433934[iVar23 + (char)PTR_DAT_80433934[iVar22 + 0x5a] * 0x1c + 0x1ea] =
                 *(undefined1 *)(puVar20 + 1);
            PTR_DAT_80433934[iVar23 + (char)PTR_DAT_80433934[iVar22 + 0x5a] * 0x1c + 0x1eb] =
                 *(undefined1 *)((int)puVar20 + 3);
            *(undefined4 *)
             (PTR_DAT_80433934 + iVar23 + (char)PTR_DAT_80433934[iVar22 + 0x5a] * 0x1c + 0x1ec) =
                 *(undefined4 *)(puVar20 + 4);
            *(undefined4 *)
             (PTR_DAT_80433934 + iVar23 + (char)PTR_DAT_80433934[iVar22 + 0x5a] * 0x1c + 500) =
                 *(undefined4 *)(puVar20 + 2);
            PTR_DAT_80433934[iVar22 + 0x5a] = PTR_DAT_80433934[iVar22 + 0x5a] + '\x01';
          }
        }
        sprintf(PTR_DAT_80433934 + iVar26 + 0x1654,&DAT_802b3508);
      }
      else {
        iVar18 = *(int *)(puVar13 + iVar10 + 0x140);
        iVar21 = 0;
        cVar2 = puVar13[(int)(char)puVar13[iVar10 + 0x161] + iVar10 + 0x14c];
        PTR_DAT_80433934[iVar22 + 0x5a] = 0;
        iVar19 = iVar18 + cVar2 * 0x6c;
        for (iVar16 = 0; iVar16 < 0x1e; iVar16 = iVar16 + 1) {
          iVar7 = (int)*(short *)(iVar19 + iVar16 * 2 + 0x30);
          if (-1 < iVar7) {
            puVar20 = (undefined2 *)(iVar18 + iVar7 * 0x20 + 0x870);
            local_2a0[0] = *puVar20;
            uVar8 = zz_0066168_((char *)local_2a0,(int)*(char *)(puVar20 + 1));
            if (cVar1 < '\0') {
              uVar8 = (int)(uVar8 << 1) / 3 + ((int)(uVar8 << 1 | uVar8 >> 0x1f) >> 0x1f) +
                      ((uVar8 & 0x7fffffff) >> 0x1e);
            }
            iVar21 = iVar21 + uVar8;
            if (iVar6 < iVar21) {
              iVar16 = 0x1e;
            }
            else {
              *(undefined2 *)
               (PTR_DAT_80433934 + iVar23 + (char)PTR_DAT_80433934[iVar22 + 0x5a] * 0x1c + 0x1e8) =
                   *puVar20;
              PTR_DAT_80433934[iVar23 + (char)PTR_DAT_80433934[iVar22 + 0x5a] * 0x1c + 0x1ea] =
                   *(undefined1 *)(puVar20 + 1);
              PTR_DAT_80433934[iVar23 + (char)PTR_DAT_80433934[iVar22 + 0x5a] * 0x1c + 0x1eb] =
                   *(undefined1 *)((int)puVar20 + 3);
              *(undefined4 *)
               (PTR_DAT_80433934 + iVar23 + (char)PTR_DAT_80433934[iVar22 + 0x5a] * 0x1c + 0x1ec) =
                   *(undefined4 *)(puVar20 + 4);
              *(undefined4 *)
               (PTR_DAT_80433934 + iVar23 + (char)PTR_DAT_80433934[iVar22 + 0x5a] * 0x1c + 500) =
                   *(undefined4 *)(puVar20 + 2);
              PTR_DAT_80433934[iVar22 + 0x5a] = PTR_DAT_80433934[iVar22 + 0x5a] + '\x01';
            }
          }
        }
        zz_0238cbc_((int)(PTR_DAT_80433934 + iVar26 + 0x1654),iVar19,0x28);
      }
    }
    iVar19 = iVar11 + 0x10;
    PTR_DAT_80433934[iVar22 + 0x54] = 0;
    iVar6 = iVar22 + 0xa0;
    iVar22 = iVar22 + 1;
    iVar18 = iVar23 + 0x1e8;
    iVar16 = iVar23 + 0x1ea;
    iVar10 = iVar10 + 0x80;
    iVar23 = iVar23 + 0x348;
    iVar26 = iVar26 + 0x29;
    iVar11 = iVar11 + 2;
    *(undefined2 *)(PTR_DAT_80433934 + iVar19) = *(undefined2 *)(PTR_DAT_80433934 + iVar18);
    PTR_DAT_80433934[iVar6] = PTR_DAT_80433934[iVar16];
  } while (iVar22 < 6);
  sVar14 = 0;
  piVar9 = local_224;
  puVar13 = PTR_DAT_80433944;
  iVar10 = 0;
  for (iVar11 = 0; iVar11 < (char)PTR_DAT_80433944[0x6a]; iVar11 = iVar11 + 1) {
    sVar3 = *(short *)(puVar13 + 0x30);
    *piVar9 = 0;
    if (sVar14 < sVar3) {
      iVar22 = 1;
      sVar14 = sVar3;
      local_224[0] = iVar11;
    }
    else {
      iVar22 = iVar10;
      if (sVar3 == sVar14) {
        iVar22 = iVar10 + 1;
        local_224[iVar10] = iVar11;
      }
    }
    piVar9 = piVar9 + 1;
    puVar13 = puVar13 + 2;
    iVar10 = iVar22;
  }
  if (iVar10 == 0) {
    iVar10 = 1;
    local_224[0] = 0;
  }
  uVar8 = zz_00055fc_();
  uVar8 = uVar8 & 0xff;
  iVar11 = (char)PTR_DAT_80433944[0x6a] + -1;
  if (iVar10 == 1) {
    iVar10 = local_224[0];
    if (local_224[0] == iVar11) {
      iVar10 = uVar8 - ((int)uVar8 / iVar11) * iVar11;
    }
  }
  else {
    if (iVar11 == (&local_228)[iVar10]) {
      iVar10 = iVar10 + -1;
    }
    iVar10 = local_224[uVar8 - ((int)uVar8 / iVar10) * iVar10];
  }
  iVar11 = 0;
  PTR_DAT_80433934[0x1c] = (&DAT_8035162d)[(char)PTR_DAT_80433944[iVar10 + 0x58] * 2];
  PTR_DAT_80433934[0x1d] = (char)*(undefined2 *)(&DAT_80351828 + (char)PTR_DAT_80433934[0x1c] * 2);
  PTR_DAT_80433934[0x1e] = 3;
  PTR_DAT_80433934[0x53] = 2;
  for (iVar10 = 0; iVar10 < (char)PTR_DAT_80433934[0x53]; iVar10 = iVar10 + 1) {
    iVar22 = iVar11 + 0xf4;
    iVar11 = iVar11 + 0x3c;
    puVar13 = PTR_DAT_80433934 + iVar22;
    *puVar13 = (char)iVar10;
    *(undefined2 *)(puVar13 + 0x1c) = 0;
    *(undefined4 *)(puVar13 + 0x20) = 3000;
  }
  if (PTR_DAT_80433934[0x15d7] == '\0') {
    *(undefined4 *)(PTR_DAT_80433934 + 0x4c) = 0xea24;
    *(undefined4 *)(PTR_DAT_80433934 + 0x48) = 0xea24;
    PTR_DAT_80433934[0x50] = 1;
  }
  else {
    sVar14 = *(short *)(&DAT_80434788 + (char)PTR_DAT_80433934[0x15d7] * 2);
    *(int *)(PTR_DAT_80433934 + 0x4c) = sVar14 * 0x3c;
    *(int *)(PTR_DAT_80433934 + 0x48) = sVar14 * 0x3c;
    PTR_DAT_80433934[0x50] = 0;
  }
  PTR_DAT_80433930[0x33] = 1;
  cVar1 = PTR_DAT_80433930[3];
  if (cVar1 == '\x01') {
    iVar11 = 0;
    iVar22 = 0;
    iVar10 = 4;
    PTR_DAT_80433930[0x29] = 0;
    do {
      if (((int)(char)PTR_DAT_80433944[iVar11 + 0x20] & 0xf0U) == 0) {
        iVar26 = iVar22 + 0xc0;
        iVar22 = iVar22 + 1;
        PTR_DAT_80433934[iVar26] = PTR_DAT_80433944[iVar11 + 0x20] & 0xf;
      }
      iVar11 = iVar11 + 1;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
  }
  else if (cVar1 == '\x02') {
    PTR_DAT_80433930[0x29] = 1;
    iVar11 = 0;
    iVar10 = 4;
    iVar22 = 0;
    PTR_DAT_80433930[0x3d] = 1;
    do {
      if (((int)(char)PTR_DAT_80433944[iVar11 + 0x20] & 0xf0U) == 0) {
        iVar26 = iVar22 + 0xc0;
        iVar22 = iVar22 + 1;
        PTR_DAT_80433934[iVar26] = PTR_DAT_80433944[iVar11 + 0x20] & 0xf;
      }
      iVar11 = iVar11 + 1;
      iVar10 = iVar10 + -1;
    } while (iVar10 != 0);
  }
  else if ('\x02' < cVar1) {
    PTR_DAT_80433930[0x29] = 2;
    PTR_DAT_80433934[0xc0] = PTR_DAT_80433944[0x20] & 0xf;
    PTR_DAT_80433934[0xc1] = PTR_DAT_80433944[0x21] & 0xf;
    PTR_DAT_80433934[0xc2] = PTR_DAT_80433944[0x22] & 0xf;
    PTR_DAT_80433934[0xc3] = PTR_DAT_80433944[0x23] & 0xf;
  }
  zz_017486c_();
  zz_000685c_(0);
  zz_00064d4_();
  uVar27 = zz_0006abc_();
  uVar27 = zz_0042454_(uVar27,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_0042690_(uVar27,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 80174084  FUN_80174084 ====

void FUN_80174084(void)

{
  (*(code *)(&PTR_FUN_8035184c)[*(short *)(PTR_DAT_80433944 + 4)])();
  return;
}



// ==== 801740c0  FUN_801740c0 ====

void FUN_801740c0(void)

{
  if (PTR_DAT_80433944[0x91] == '\0') {
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 4;
  }
  else {
    *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
    *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 10;
    PTR_DAT_80433944[0x6f] = 1;
    PTR_DAT_80433944[0x83] = 1;
    zz_011c648_(0x11,0);
  }
  return;
}



// ==== 8017415c  FUN_8017415c ====

/* WARNING: Removing unreachable block (ram,0x80174194) */
/* WARNING: Removing unreachable block (ram,0x801741dc) */

void FUN_8017415c(void)

{
  ushort *puVar1;
  undefined *puVar2;
  ushort uVar3;
  int iVar4;
  
  uVar3 = 0;
  iVar4 = 4;
  puVar2 = PTR_DAT_80433944;
  do {
    puVar1 = (ushort *)(puVar2 + 0x10e);
    puVar2 = puVar2 + 0x80;
    uVar3 = uVar3 | *puVar1;
    iVar4 = iVar4 + -1;
  } while (iVar4 != 0);
  if ((uVar3 & 3) != 0) {
    PTR_DAT_80433944[0x83] = PTR_DAT_80433944[0x83] ^ 1;
    zz_00f0468_(0,0x77,0);
  }
  if ((uVar3 & 0x200) == 0) {
    if ((uVar3 & 0x180) != 0) {
      *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
      if (PTR_DAT_80433944[0x83] == '\0') {
        *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 0x18;
        PTR_DAT_80433944[0x6f] = 2;
      }
      else {
        *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 10;
        PTR_DAT_80433944[0x6f] = 0;
      }
      zz_00f0468_(0,0x7a,0);
    }
  }
  else {
    *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
    *(undefined2 *)(PTR_DAT_80433944 + 0xe) = 10;
    PTR_DAT_80433944[0x6f] = 0;
    zz_00f0468_(0,0x7b,0);
  }
  return;
}



// ==== 80174328  FUN_80174328 ====

void FUN_80174328(void)

{
  *(short *)(PTR_DAT_80433944 + 4) = *(short *)(PTR_DAT_80433944 + 4) + 1;
  zz_0027aac_(0,0x1e,1);
  zz_00e9b60_((double)FLOAT_8043acd8,2,0x1e,2);
  return;
}



// ==== 80174378  FUN_80174378 ====

void FUN_80174378(void)

{
  int iVar1;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    *(undefined2 *)PTR_DAT_80433944 = 3;
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 2) = 0;
    zz_002a5f4_(0,0,0,0);
  }
  return;
}



// ==== 801743d4  FUN_801743d4 ====

bool FUN_801743d4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  int iVar2;
  
  iVar2 = zz_000a3c4_();
  if (iVar2 == 0) {
    *(undefined2 *)(PTR_DAT_80433944 + 6) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 4) = 0;
    *(undefined2 *)(PTR_DAT_80433944 + 2) = 0;
    puVar1 = PTR_DAT_80433944;
    *(undefined2 *)PTR_DAT_80433944 = 0;
    zz_016e650_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar1,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
    zz_007fd5c_();
    zz_0027c1c_();
  }
  return iVar2 == 0;
}



// ==== 80174438  FUN_80174438 ====

undefined4
FUN_80174438(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
            double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
            undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
            undefined4 param_15,undefined4 param_16)

{
  zz_016e650_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  zz_007fd5c_();
  zz_0027c1c_();
  return 0xffffffff;
}



// ==== 80174464  zz_0174464_ ====

bool zz_0174464_(double param_1)

{
  double dVar1;
  double dVar2;
  
  dVar2 = (double)*(float *)(PTR_DAT_80433944 + 0x1c);
  if (dVar2 <= param_1) {
    if ((dVar2 < param_1) &&
       (dVar1 = (double)FLOAT_8043ad10, *(float *)(PTR_DAT_80433944 + 0x1c) = (float)(dVar2 + dVar1)
       , param_1 < (double)(float)(dVar2 + dVar1))) {
      *(float *)(PTR_DAT_80433944 + 0x1c) = (float)param_1;
    }
  }
  else {
    dVar1 = (double)FLOAT_8043ad10;
    *(float *)(PTR_DAT_80433944 + 0x1c) = (float)(dVar2 - dVar1);
    if ((double)(float)(dVar2 - dVar1) < param_1) {
      *(float *)(PTR_DAT_80433944 + 0x1c) = (float)param_1;
    }
  }
  return (double)*(float *)(PTR_DAT_80433944 + 0x1c) == param_1;
}



// ==== 801744cc  zz_01744cc_ ====

int zz_01744cc_(void)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  float local_38 [11];
  
  fVar6 = FLOAT_8043ad38;
  fVar4 = FLOAT_8043ad34;
  fVar5 = FLOAT_8043ad30;
  fVar3 = FLOAT_8043ad2c;
  fVar2 = FLOAT_8043acd8;
  puVar11 = &DAT_803c73b0;
  pfVar9 = local_38;
  iVar16 = 2;
  puVar10 = puVar11;
  do {
    fVar1 = *(float *)(puVar10 + 0x24);
    pfVar9[1] = fVar2;
    *pfVar9 = fVar2;
    if (fVar3 < fVar1) {
      *(float *)(puVar10 + 0x24) = fVar3;
    }
    if (*(float *)(puVar10 + 0x24) < fVar5) {
      *(float *)(puVar10 + 0x24) = fVar5;
    }
    if (fVar4 < *(float *)(puVar10 + 0x20)) {
      *(float *)(puVar10 + 0x20) = fVar4;
    }
    if (*(float *)(puVar10 + 0x20) < fVar6) {
      *(float *)(puVar10 + 0x20) = fVar6;
    }
    pfVar9[3] = fVar2;
    fVar1 = *(float *)(puVar10 + 0x408);
    pfVar9[2] = fVar2;
    if (fVar3 < fVar1) {
      *(float *)(puVar10 + 0x408) = fVar3;
    }
    if (*(float *)(puVar10 + 0x408) < fVar5) {
      *(float *)(puVar10 + 0x408) = fVar5;
    }
    if (fVar4 < *(float *)(puVar10 + 0x404)) {
      *(float *)(puVar10 + 0x404) = fVar4;
    }
    if (*(float *)(puVar10 + 0x404) < fVar6) {
      *(float *)(puVar10 + 0x404) = fVar6;
    }
    fVar1 = FLOAT_8043ad40;
    pfVar9 = pfVar9 + 4;
    puVar10 = puVar10 + 0x7c8;
    iVar16 = iVar16 + -1;
  } while (iVar16 != 0);
  iVar16 = 0;
  do {
    if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar16) != 0) {
      iVar12 = iVar16 + 1;
      iVar7 = 4 - iVar12;
      puVar10 = &DAT_803c73b0 + iVar12 * 0x3e4;
      if (iVar12 < 4) {
        do {
          if (((int)(char)PTR_DAT_80433930[2] & 1 << iVar12) != 0) {
            fVar3 = *(float *)(puVar10 + 0x20) - *(float *)(puVar11 + 0x20);
            fVar2 = fVar3;
            if (fVar3 < FLOAT_8043acd8) {
              fVar2 = -fVar3;
            }
            fVar4 = *(float *)(puVar10 + 0x24) - *(float *)(puVar11 + 0x24);
            fVar5 = fVar4;
            if (fVar4 < FLOAT_8043acd8) {
              fVar5 = -fVar4;
            }
            if ((fVar2 < FLOAT_8043ad3c * DAT_8035186c) && (fVar5 < FLOAT_8043ad3c * DAT_80351870))
            {
              iVar8 = iVar12;
              iVar13 = iVar16;
              if (fVar4 < FLOAT_8043acd8) {
                iVar8 = iVar16;
                iVar13 = iVar12;
              }
              iVar14 = iVar16;
              iVar15 = iVar12;
              if (fVar3 < FLOAT_8043acd8) {
                iVar14 = iVar12;
                iVar15 = iVar16;
              }
              fVar3 = (FLOAT_8043ad3c * DAT_8035186c - fVar2) * FLOAT_8043acf0;
              fVar4 = (FLOAT_8043ad3c * DAT_80351870 - fVar5) * FLOAT_8043acf0;
              if (fVar4 * fVar2 <= fVar3 * fVar5) {
                fVar3 = FLOAT_8043ad40;
                if (FLOAT_8043ad40 <= fVar5) {
                  fVar3 = fVar5;
                }
                fVar2 = fVar4 * (fVar2 / fVar3);
                local_38[iVar8 * 2 + 1] = local_38[iVar8 * 2 + 1] + fVar4;
                local_38[iVar13 * 2 + 1] = local_38[iVar13 * 2 + 1] - fVar4;
                local_38[iVar15 * 2] = local_38[iVar15 * 2] + fVar2;
                local_38[iVar14 * 2] = local_38[iVar14 * 2] - fVar2;
              }
              else {
                fVar4 = FLOAT_8043ad40;
                if (FLOAT_8043ad40 <= fVar2) {
                  fVar4 = fVar2;
                }
                fVar2 = fVar3 * (fVar5 / fVar4);
                local_38[iVar8 * 2 + 1] = local_38[iVar8 * 2 + 1] + fVar2;
                local_38[iVar13 * 2 + 1] = local_38[iVar13 * 2 + 1] - fVar2;
                local_38[iVar15 * 2] = local_38[iVar15 * 2] + fVar3;
                local_38[iVar14 * 2] = local_38[iVar14 * 2] - fVar3;
              }
            }
          }
          puVar10 = puVar10 + 0x3e4;
          iVar12 = iVar12 + 1;
          iVar7 = iVar7 + -1;
        } while (iVar7 != 0);
      }
    }
    iVar16 = iVar16 + 1;
    puVar11 = puVar11 + 0x3e4;
  } while (iVar16 < 4);
  iVar7 = 0;
  pfVar9 = local_38;
  iVar16 = 4;
  puVar10 = &DAT_803c73b0;
  do {
    fVar2 = *pfVar9;
    fVar3 = pfVar9[1];
    *(float *)(puVar10 + 0x20) = *(float *)(puVar10 + 0x20) + fVar2;
    *(float *)(puVar10 + 0x24) = *(float *)(puVar10 + 0x24) + fVar3;
    if ((fVar1 < fVar2) || (fVar1 < fVar3)) {
      iVar7 = iVar7 + 1;
    }
    pfVar9 = pfVar9 + 2;
    puVar10 = puVar10 + 0x3e4;
    iVar16 = iVar16 + -1;
  } while (iVar16 != 0);
  return iVar7;
}



// ==== 8017486c  zz_017486c_ ====

void zz_017486c_(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = 0;
  iVar1 = 0;
  do {
    zz_0098084_(-0x7fc44bc0,iVar1,PTR_DAT_80433944 + iVar2 + 0x120);
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 0x80;
  } while (iVar1 < 4);
  gnt4_GXInvalidateTexAll_bl();
  return;
}



// ==== 801748dc  zz_01748dc_ ====

void zz_01748dc_(char *param_1)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = 0;
  bVar1 = false;
  iVar4 = 0;
  while( true ) {
    if (((char)PTR_DAT_80433944[0x6b] <= iVar3) || (bVar1)) break;
    iVar2 = gnt4_strcmp(PTR_DAT_80433944 + iVar4 + 0x300,param_1);
    if (iVar2 == 0) {
      bVar1 = true;
    }
    iVar4 = iVar4 + 0x1a;
    iVar3 = iVar3 + 1;
  }
  if (!bVar1) {
    iVar3 = (char)PTR_DAT_80433944[0x6b] + -1;
    iVar4 = iVar3 * 0x1a;
    for (; -1 < iVar3; iVar3 = iVar3 + -1) {
      if (iVar3 + 1 < 0x10) {
        strcpy(PTR_DAT_80433944 + (iVar3 + 1) * 0x1a + 0x300,PTR_DAT_80433944 + iVar4 + 0x300);
      }
      iVar4 = iVar4 + -0x1a;
    }
    strcpy(PTR_DAT_80433944 + 0x300,param_1);
    if ((char)PTR_DAT_80433944[0x6b] < '\x10') {
      PTR_DAT_80433944[0x6b] = PTR_DAT_80433944[0x6b] + '\x01';
    }
  }
  return;
}



// ==== 801749e4  FUN_801749e4 ====

/* WARNING: Removing unreachable block (ram,0x80174ab8) */
/* WARNING: Removing unreachable block (ram,0x80174ab0) */
/* WARNING: Removing unreachable block (ram,0x80174aa8) */
/* WARNING: Removing unreachable block (ram,0x80174a04) */
/* WARNING: Removing unreachable block (ram,0x801749fc) */
/* WARNING: Removing unreachable block (ram,0x801749f4) */

void FUN_801749e4(void)

{
  int iVar1;
  int iVar2;
  undefined1 *__s;
  double dVar3;
  double dVar4;
  double dVar5;
  
  dVar3 = (double)FLOAT_8043acd8;
  dVar4 = (double)FLOAT_8043ad44;
  __s = &DAT_803c73b0;
  dVar5 = (double)FLOAT_8043ad48;
  iVar1 = 0;
  iVar2 = 0;
  do {
    gnt4_memset(__s,0,0x3e4);
    *(float *)(__s + 0x2e8) = (float)dVar3;
    *(float *)(__s + 0x2ec) = (float)dVar3;
    *(float *)(__s + 0x2f0) = (float)dVar3;
    *(float *)(__s + 0x300) = (float)dVar3;
    *(float *)(__s + 0x304) = (float)dVar3;
    *(float *)(__s + 0x308) = (float)dVar4;
    *(float *)(__s + 0x330) = (float)dVar3;
    *(float *)(__s + 0x334) = (float)dVar5;
    *(float *)(__s + 0x338) = (float)dVar3;
    gnt4_C_MTXLookAt_bl((float *)(__s + 0x394),(float *)(__s + 0x2e8),(float *)(__s + 0x330),
                        (float *)(__s + 0x300));
    *(undefined1 **)(PTR_DAT_80433930 + iVar2 + 0x14) = __s + 0x394;
    __s = __s + 0x3e4;
    iVar2 = iVar2 + 4;
    PTR_DAT_80433930[iVar1 + 0xc] = (char)iVar1;
    iVar1 = iVar1 + 1;
  } while (iVar1 < 5);
  return;
}



// ==== 80174adc  zz_0174adc_ ====

void zz_0174adc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                float *param_11,float *param_12,undefined4 param_13,undefined4 param_14,
                undefined4 *param_15,undefined4 *param_16)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  float fVar5;
  int iVar6;
  undefined1 *puVar7;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  int iVar8;
  int iVar9;
  undefined1 *puVar10;
  double dVar11;
  undefined8 uVar12;
  float local_28;
  float local_24;
  float local_20;
  
  puVar7 = (undefined1 *)0x803c0000;
  puVar10 = &DAT_803c73b0;
  iVar9 = 0;
  iVar8 = 0;
  do {
    fVar5 = FLOAT_8043acd8;
    if (iVar8 < 4) {
      param_16 = &DAT_802b0ce4;
      *(float *)(puVar10 + 0x2e8) = FLOAT_8043acd8;
      uVar1 = DAT_802b0ce4;
      param_15 = &DAT_802b0cb4;
      *(float *)(puVar10 + 0x2ec) = fVar5;
      uVar2 = DAT_802b0ce8;
      *(float *)(puVar10 + 0x2f0) = fVar5;
      uVar3 = DAT_802b0cec;
      *(undefined4 *)(puVar10 + 0x300) = uVar1;
      param_14 = DAT_802b0cb4;
      *(undefined4 *)(puVar10 + 0x304) = uVar2;
      param_13 = DAT_802b0cb8;
      *(undefined4 *)(puVar10 + 0x308) = uVar3;
      uVar1 = DAT_802b0cbc;
      *(undefined4 *)(puVar10 + 0x330) = param_14;
      *(undefined4 *)(puVar10 + 0x334) = param_13;
      *(undefined4 *)(puVar10 + 0x338) = uVar1;
      gnt4_C_MTXLookAt_bl((float *)(puVar10 + 0x394),(float *)(puVar10 + 0x2e8),
                          (float *)(puVar10 + 0x330),(float *)(puVar10 + 0x300));
    }
    else {
      dVar11 = (double)*(float *)(PTR_DAT_80433944 + 0x1c);
      if ((double)FLOAT_8043ad0c < dVar11) {
        dVar11 = (double)((float)(dVar11 - (double)FLOAT_8043ad0c) / FLOAT_8043ad4c);
        if ((double)FLOAT_8043ad10 < dVar11) {
          dVar11 = (double)FLOAT_8043ad10;
        }
        param_3 = (double)FLOAT_8043acd8;
        param_2 = (double)FLOAT_8043ad50;
        local_28 = FLOAT_8043acd8;
        local_24 = FLOAT_8043ad50;
        local_20 = FLOAT_8043ad54;
        gnt4_PSQUATScale_bl(dVar11,&local_28,&local_28);
        gnt4_PSVECAdd_bl((float *)(puVar10 + 0x2f4),&local_28,(float *)(puVar10 + 0x2e8));
        gnt4_PSVECAdd_bl((float *)(puVar10 + 0x30c),&local_28,(float *)(puVar10 + 0x300));
        gnt4_C_MTXLookAt_bl((float *)(puVar10 + 0x394),(float *)(puVar10 + 0x2e8),
                            (float *)(puVar10 + 0x330),(float *)(puVar10 + 0x300));
      }
      else {
        uVar12 = zz_00088a4_(dVar11,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             DAT_803bb384,puVar7,param_11,param_12,param_13,param_14,param_15,
                             param_16);
        uVar12 = zz_0008970_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             (undefined4 *)(puVar10 + 0x2e8),extraout_r4,(undefined *)param_11,
                             param_12,param_13,param_14,param_15,param_16);
        uVar12 = cCameraManager__HasCamera_cBaseCamera
                           (uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (undefined4 *)(puVar10 + 0x300),extraout_r4_00,(undefined *)param_11,
                            param_12,param_13,param_14,param_15,param_16);
        uVar12 = zz_00089c0_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                             (float *)(puVar10 + 0x330),extraout_r4_01,(undefined *)param_11,
                             param_12,param_13,param_14,param_15,param_16);
        zz_0008948_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    (float *)(puVar10 + 0x394),extraout_r4_02,(undefined *)param_11,param_12,
                    param_13,param_14,param_15,param_16);
        *(undefined4 *)(puVar10 + 0x2f4) = *(undefined4 *)(puVar10 + 0x2e8);
        *(undefined4 *)(puVar10 + 0x2f8) = *(undefined4 *)(puVar10 + 0x2ec);
        *(undefined4 *)(puVar10 + 0x2fc) = *(undefined4 *)(puVar10 + 0x2f0);
        *(undefined4 *)(puVar10 + 0x30c) = *(undefined4 *)(puVar10 + 0x300);
        *(undefined4 *)(puVar10 + 0x310) = *(undefined4 *)(puVar10 + 0x304);
        *(undefined4 *)(puVar10 + 0x314) = *(undefined4 *)(puVar10 + 0x308);
      }
    }
    gnt4_PSVECSubtract_bl((float *)(puVar10 + 0x2e8),(float *)(puVar10 + 0x300),&local_28);
    param_11 = &local_28;
    param_12 = (float *)(puVar10 + 0x330);
    zz_0045ef4_((float *)(puVar10 + 0x364),5,param_11,param_12);
    puVar4 = PTR_DAT_80433930;
    iVar8 = iVar8 + 1;
    iVar6 = iVar9 + 0x14;
    *(undefined4 *)(puVar10 + 0x370) = *(undefined4 *)(puVar10 + 0x2e8);
    puVar7 = puVar10 + 0x394;
    iVar9 = iVar9 + 4;
    *(undefined4 *)(puVar10 + 0x380) = *(undefined4 *)(puVar10 + 0x2ec);
    *(undefined4 *)(puVar10 + 0x390) = *(undefined4 *)(puVar10 + 0x2f0);
    puVar10 = puVar10 + 0x3e4;
    *(undefined1 **)(puVar4 + iVar6) = puVar7;
  } while (iVar8 < 5);
  return;
}



// ==== 80174ce8  zz_0174ce8_ ====

void zz_0174ce8_(void)

{
  zz_0174d0c_();
  zz_0174d40_();
  return;
}



// ==== 80174d0c  zz_0174d0c_ ====

void zz_0174d0c_(void)

{
  zz_0089898_(0x10);
  zz_0089898_(0x38);
  zz_0089554_();
  zz_0089658_();
  return;
}



// ==== 80174d40  zz_0174d40_ ====

void zz_0174d40_(void)

{
  zz_008a16c_();
  zz_0089c00_(0x10);
  zz_0089c00_(0x38);
  zz_008c0dc_(FUN_80089eb4);
  zz_008c104_(FUN_80089f28);
  return;
}



// ==== 80174e84  FUN_80174e84 ====

void FUN_80174e84(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x707) {
    zz_01b6e0c_(param_1,0);
    zz_01b6e0c_(param_1,1);
  }
  return;
}



// ==== 80174ecc  FUN_80174ecc ====

void FUN_80174ecc(int param_1)

{
  char cVar1;
  
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043ad60) * FLOAT_8043ad58);
  }
  if (*(short *)(param_1 + 1000) == 0x707) {
    cVar1 = zz_008b480_();
    if (cVar1 == '\0') {
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) & 0xdf;
    }
    else {
      *(byte *)(param_1 + 0x58e) = *(byte *)(param_1 + 0x58e) | 0x20;
    }
  }
  return;
}



// ==== 80174f80  FUN_80174f80 ====

void FUN_80174f80(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_803518b8)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80174fc0  FUN_80174fc0 ====

void FUN_80174fc0(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x704) {
    zz_001ab6c_(param_1,0x1a);
  }
  else if (*(short *)(param_1 + 1000) == 0x707) {
    zz_001ab6c_(param_1,0x54);
  }
  return;
}



// ==== 8017500c  FUN_8017500c ====

void FUN_8017500c(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x704) {
    zz_001ab6c_(param_1,0x19);
  }
  else if (*(short *)(param_1 + 1000) == 0x707) {
    zz_001ab6c_(param_1,0x53);
  }
  return;
}



// ==== 80175058  FUN_80175058 ====

void FUN_80175058(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x704) {
    zz_001ab6c_(param_1,0x1a);
    zz_001ab6c_(param_1,0x19);
  }
  else if (*(short *)(param_1 + 1000) == 0x707) {
    zz_001ab6c_(param_1,0x54);
    zz_001ab6c_(param_1,0x53);
  }
  return;
}



// ==== 801750d4  FUN_801750d4 ====

uint FUN_801750d4(int param_1)

{
  uint uVar1;
  bool bVar2;
  
  uVar1 = zz_006dbe0_(param_1,0,1,1);
  if (uVar1 != 0) {
    if (*(short *)(param_1 + 1000) == 0x704) {
      bVar2 = zz_00fbc64_(param_1,3);
      uVar1 = (uint)bVar2;
    }
    else if (*(short *)(param_1 + 1000) == 0x707) {
      bVar2 = zz_00fbc64_(param_1,4);
      uVar1 = (uint)bVar2;
    }
  }
  return uVar1;
}



// ==== 80175148  FUN_80175148 ====

void FUN_80175148(int param_1)

{
  (*(code *)(&PTR_FUN_803518d4)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80175184  FUN_80175184 ====

void FUN_80175184(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043ad60) * FLOAT_8043ad58);
  (*(code *)(&PTR_FUN_803518e0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801751f8  FUN_801751f8 ====

void FUN_801751f8(int param_1)

{
  zz_0148d74_(param_1);
  return;
}



// ==== 80175220  FUN_80175220 ====

void FUN_80175220(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80351908)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80175270  FUN_80175270 ====

void FUN_80175270(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_8043ad6c;
  fVar1 = FLOAT_8043ad68;
  *(float *)(param_1 + 0x48) = FLOAT_8043ad68;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / fVar2;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x558) = fVar2;
  zz_0092dcc_(param_1,0);
  zz_004beb8_((double)FLOAT_8043ad70,param_1,0xf,3,3,0xffffffff,0xffffffff);
  zz_0175380_(param_1);
  return;
}



// ==== 80175380  zz_0175380_ ====

void zz_0175380_(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  float local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  if (*(int *)(param_1 + 0xcc) != 0) {
    iVar4 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
    local_1c = *(float *)(iVar4 + 0x8e0);
    local_18 = *(float *)(iVar4 + 0x8f0);
    local_14 = *(undefined4 *)(iVar4 + 0x900);
    local_28 = *(float *)(param_1 + 0x518);
    local_20 = *(undefined4 *)(param_1 + 0x520);
    local_24 = FLOAT_8043ad74 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
    gnt4_PSVECSubtract_bl(&local_28,&local_1c,&local_1c);
    fVar1 = FLOAT_8043ad68;
    *(float *)(param_1 + 0x48) = local_18 / FLOAT_8043ad78;
    local_18 = fVar1;
    dVar5 = gnt4_PSVECMag_bl(&local_1c);
    *(float *)(param_1 + 0x44) = (float)(dVar5 / (double)FLOAT_8043ad6c);
  }
  zz_006d144_(param_1,0xc0);
  FUN_80067310((double)FLOAT_8043ad7c,param_1,*(short *)(param_1 + 0x5ac));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043ad68;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_8043ad80,param_1), uVar3 != 0)) {
    dVar5 = DOUBLE_8043ad88;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * dVar5);
    *(float *)(param_1 + 0x4c) = (float)((double)*(float *)(param_1 + 0x4c) * dVar5);
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x48) * dVar5);
    *(float *)(param_1 + 0x50) = (float)((double)*(float *)(param_1 + 0x50) * dVar5);
  }
  return;
}



// ==== 80175508  FUN_80175508 ====

void FUN_80175508(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868) /
           FLOAT_8043ad6c;
    }
    else {
      *(float *)(param_1 + 0x44) =
           (float)((DOUBLE_8043ad90 * (double)*(float *)(param_1 + 0x760)) / DOUBLE_8043ad98);
    }
  }
  fVar1 = FLOAT_8043ad68;
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    if (fVar1 < *(float *)(param_1 + 0x48)) {
      *(float *)(param_1 + 0x48) = fVar1;
    }
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  if (*(float *)(param_1 + 0x760) < FLOAT_8043ad80) {
    zz_006ed8c_((double)FLOAT_8043ada0,param_1);
  }
  zz_006ed8c_((double)FLOAT_8043ada4,param_1);
  FUN_80067310((double)FLOAT_8043ad7c,param_1,*(short *)(param_1 + 0x5ac));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043ad7c + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 801756bc  FUN_801756bc ====

void FUN_801756bc(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80351914)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8017570c  FUN_8017570c ====

void FUN_8017570c(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043ada8;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_8043ad70,param_1,0xf,3,5,0xffffffff,0xffffffff);
  return;
}



// ==== 801757c8  FUN_801757c8 ====

void FUN_801757c8(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043ad68;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar1 = FLOAT_8043ad6c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_8043adac;
    fVar2 = FLOAT_8043ad68;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x760))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_8043ad6c;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 801758c8  FUN_801758c8 ====

void FUN_801758c8(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043adb0,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043ad68;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_8043adac,param_1), uVar3 != 0)) {
    dVar4 = (double)FLOAT_8043ad70;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,4,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8017597c  FUN_8017597c ====

void FUN_8017597c(int param_1)

{
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
  }
  if (*(float *)(param_1 + 0x760) <= FLOAT_8043adac) {
    *(undefined1 *)(param_1 + 0x1d9b) = 0;
  }
  else {
    zz_006ed8c_((double)FLOAT_8043adb0,param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80175a20  FUN_80175a20 ====

void FUN_80175a20(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80351924)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80175a70  FUN_80175a70 ====

void FUN_80175a70(int param_1)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043ada8;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_8043ad70,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}



// ==== 80175b2c  FUN_80175b2c ====

void FUN_80175b2c(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043ad68;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar1 = FLOAT_8043ad6c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_8043adac;
    fVar2 = FLOAT_8043ad68;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x760))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_8043ad6c;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 80175c20  FUN_80175c20 ====

void FUN_80175c20(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043adb0,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043ad68;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_8043adac,param_1), uVar3 != 0)) {
    dVar4 = (double)FLOAT_8043ad70;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,7,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80175cd4  FUN_80175cd4 ====

void FUN_80175cd4(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043adb4,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043adb8;
  fVar1 = FLOAT_8043ada8;
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_8043adbc;
    *(float *)(param_1 + 0x558) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2;
    *(float *)(param_1 + 0x50) = fVar3;
  }
  return;
}



// ==== 80175d58  FUN_80175d58 ====

void FUN_80175d58(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043adb0,param_1);
  FUN_80067310((double)FLOAT_8043ad7c,param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_8043ad68;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_00677b0_(param_1), iVar3 != 0)) {
    dVar4 = (double)FLOAT_8043ad70;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,3,8,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80175e00  FUN_80175e00 ====

void FUN_80175e00(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043adb0,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 80175e70  FUN_80175e70 ====

void FUN_80175e70(int param_1)

{
  (*(code *)(&PTR_FUN_8035193c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80175eac  FUN_80175eac ====

void FUN_80175eac(int param_1)

{
  (*(code *)(&PTR_FUN_80351950)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80175ee8  FUN_80175ee8 ====

void FUN_80175ee8(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  if (*(short *)(param_1 + 1000) == 0x707) {
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043ada8;
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043ad68;
  *(float *)(param_1 + 0x50) = FLOAT_8043ad68;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043adb0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043ad70;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  if (*(short *)(param_1 + 1000) == 0x704) {
    zz_01a5e88_(param_1,0);
  }
  return;
}



// ==== 80175ffc  FUN_80175ffc ====

void FUN_80175ffc(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_8043adb0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043ad68;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 801760b4  FUN_801760b4 ====

void FUN_801760b4(int param_1)

{
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSQUATScale_bl((double)FLOAT_8043adb0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cf0) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(short *)(param_1 + 1000) == 0x704) {
      zz_018eea4_(param_1,0);
    }
    else if (*(short *)(param_1 + 1000) == 0x707) {
      zz_0067f98_(param_1,300);
    }
  }
  return;
}



// ==== 80176170  FUN_80176170 ====

void FUN_80176170(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043ad60) * FLOAT_8043ad58);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_8043ad7c,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 == 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_8043adc0 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
    *(float *)(param_1 + 0x694) = FLOAT_8043adc0 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80176294  zz_0176294_ ====

void zz_0176294_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(*(int *)(param_1 + 0x90) + 1000);
  if (((sVar1 == 0xa02) || (sVar1 == 0xa07)) &&
     (puVar2 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,0,1), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x10] = 0x5d;
    puVar2[0x11] = param_2;
    puVar2[0x13] = 0xff;
    puVar2[0x12] = 0;
    zz_01763b8_(param_1,(int)puVar2);
  }
  return;
}



// ==== 80176328  FUN_80176328 ====

void FUN_80176328(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(*(int *)(param_1 + 0x90) + 1000);
  if (((sVar1 == 0xa02) || (sVar1 == 0xa07)) &&
     (puVar2 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,0,1), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x10] = 0x5d;
    puVar2[0x11] = 2;
    puVar2[0x13] = param_2;
    puVar2[0x12] = 1;
    zz_01763b8_(param_1,(int)puVar2);
  }
  return;
}



// ==== 801763b8  zz_01763b8_ ====

void zz_01763b8_(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  *(code **)(param_2 + 0xc) = FUN_80176534;
  *(code **)(param_2 + 0x10c) = FUN_80176d74;
  *(int *)(param_2 + 0x8c) = param_1;
  *(undefined4 *)(param_2 + 0x90) = *(undefined4 *)(param_1 + 0x90);
  *(undefined2 *)(param_2 + 0x94) = *(undefined2 *)(param_1 + 0x94);
  *(undefined1 *)(param_2 + 0x96) = *(undefined1 *)(param_1 + 0x96);
  *(undefined1 *)(param_2 + 0x97) = *(undefined1 *)(param_1 + 0x97);
  *(undefined1 *)(param_2 + 0x88) = *(undefined1 *)(param_1 + 0x88);
  *(undefined4 *)(param_2 + 200) = *(undefined4 *)(param_1 + 200);
  *(undefined4 *)(param_2 + 0xcc) = *(undefined4 *)(param_1 + 0xcc);
  *(undefined4 *)(param_2 + 0xb8) = *(undefined4 *)(param_1 + 0xb8);
  *(undefined4 *)(param_2 + 0xb4) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_2 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_2 + 0x5c) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_2 + 0x60) = *(undefined4 *)(param_1 + 0xb4);
  *(undefined4 *)(param_2 + 0xc0) = *(undefined4 *)(param_1 + 0xc0);
  *(undefined4 *)(param_2 + 0xc4) = *(undefined4 *)(param_1 + 0xc4);
  *(undefined1 *)(param_2 + 0xd0) = *(undefined1 *)(param_1 + 0xd0);
  *(undefined4 *)(param_2 + 0x148) = *(undefined4 *)(param_2 + 0xcc);
  *(undefined4 *)(param_2 + 0x144) = *(undefined4 *)(param_2 + 200);
  *(undefined1 *)(param_2 + 0x15d) = *(undefined1 *)(param_2 + 0xd0);
  if (*(char *)(param_1 + 0x83) == '\0') {
    iVar1 = (uint)*(byte *)(param_2 + 0x11) * 0x40;
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + (char)(&DAT_803528c2)[iVar1] * 0x30 + 0x8d4),
               (float *)(iVar1 + -0x7fcad724),(float *)(param_2 + 0x20));
    zz_0083d60_(param_2,param_1,0);
  }
  else {
    uVar2 = *(undefined4 *)(param_1 + 0xa0);
    *(undefined4 *)(param_2 + 0x9c) = *(undefined4 *)(param_1 + 0x9c);
    *(undefined4 *)(param_2 + 0xa0) = uVar2;
    *(undefined4 *)(param_2 + 0xa4) = *(undefined4 *)(param_1 + 0xa4);
    uVar2 = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_2 + 0x20) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_2 + 0x24) = uVar2;
    *(undefined4 *)(param_2 + 0x28) = *(undefined4 *)(param_1 + 0x28);
    uVar2 = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_2 + 0x38) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(param_2 + 0x3c) = uVar2;
    *(undefined4 *)(param_2 + 0x40) = *(undefined4 *)(param_1 + 0x40);
  }
  return;
}



// ==== 80176534  FUN_80176534 ====

void FUN_80176534(int param_1)

{
  float fVar1;
  
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    fVar1 = FLOAT_8043adc8;
    *(undefined1 *)(param_1 + 0x82) = 0;
    *(float *)(param_1 + 0x14c) = fVar1;
  }
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x1800;
  zz_0176e54_(param_1);
  (*(code *)(&PTR_FUN_80352a00)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801765e8  FUN_801765e8 ====

void FUN_801765e8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  if (*(char *)(param_9 + 0x12) == '\0') {
    zz_017661c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  else {
    zz_01767c8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  return;
}



// ==== 8017661c  zz_017661c_ ====

void zz_017661c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  iVar5 = *(int *)(param_9 + 0x90);
  iVar1 = (uint)*(byte *)(param_9 + 0x11) * 0x40;
  iVar2 = zz_008ac80_(param_9,(int)(char)(&DAT_803528c3)[iVar1]);
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    if (-1 < (char)(&DAT_803528c2)[iVar1]) {
      *(undefined4 *)(param_9 + 0x9c) =
           *(undefined4 *)(iVar5 + (char)(&DAT_803528c2)[iVar1] * 0x30 + 0x8d8);
      *(undefined4 *)(param_9 + 0xa0) =
           *(undefined4 *)(iVar5 + (char)(&DAT_803528c2)[iVar1] * 0x30 + 0x8e8);
      *(undefined4 *)(param_9 + 0xa4) =
           *(undefined4 *)(iVar5 + (char)(&DAT_803528c2)[iVar1] * 0x30 + 0x8f8);
      zz_006ebb4_((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
      zz_0048288_(param_9);
    }
    uVar4 = 0x10;
    *(float *)(param_9 + 0x14c) = FLOAT_8043adcc;
    uVar3 = 5;
    *(undefined1 *)(param_9 + 0x15c) = 0;
    iVar2 = *(byte *)(param_9 + 0x18) + 1;
    *(char *)(param_9 + 0x18) = (char)iVar2;
    *(undefined1 *)(param_9 + 0x84) = 0x10;
    *(undefined1 *)(param_9 + 0x98) = 5;
    *(code **)(param_9 + 0x100) = zz_0048288_;
    uVar6 = zz_0089100_(param_9,0,1);
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_803528c4 + iVar1);
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_803528d0 + iVar1);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_803528d2 + iVar1);
    if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
      *(undefined4 *)(param_9 + 0x144) = 0;
    }
    iVar5 = zz_0006f98_(iVar5);
    if ((&DAT_803528c1)[iVar1] == '\0') {
      zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),(int)(char)(&DAT_803528c0)[iVar1]
                  ,uVar3,uVar4,iVar2,in_r9,in_r10);
    }
    else {
      zz_000726c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                  (float *)(int)(char)(&DAT_803528c0)[iVar1],(int)*(char *)(param_9 + 0x88),uVar4,
                  iVar2,in_r9,in_r10);
    }
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    zz_0176a44_(param_9);
  }
  return;
}



// ==== 801767c8  zz_01767c8_ ====

void zz_01767c8_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  undefined8 uVar10;
  double dVar11;
  float local_88;
  float local_84;
  float local_80;
  float afStack_7c [12];
  float afStack_4c [3];
  undefined4 local_40;
  undefined4 local_30;
  undefined4 local_20;
  
  iVar7 = *(int *)(param_9 + 0x148);
  iVar8 = *(int *)(param_9 + 0x90);
  iVar2 = (uint)*(byte *)(param_9 + 0x11) * 0x40;
  if ((iVar7 != 0) && (iVar6 = *(int *)(param_9 + 0x144), iVar6 != 0)) {
    iVar1 = *(char *)(param_9 + 0x13) * 8;
    gnt4_PSMTXRotRad_bl((double)*(float *)(&DAT_803529c0 + iVar1),afStack_4c,0x78);
    gnt4_PSMTXRotRad_bl((double)*(float *)(&DAT_803529c4 + iVar1),afStack_7c,0x79);
    gnt4_PSMTXConcat_bl(afStack_7c,afStack_4c,afStack_4c);
    local_40 = *(undefined4 *)(iVar6 + 100);
    local_30 = *(undefined4 *)(iVar6 + 0x68);
    local_20 = *(undefined4 *)(iVar6 + 0x6c);
    local_88 = FLOAT_8043adc8;
    local_84 = FLOAT_8043adc8;
    if ((*(char *)(iVar7 + 0x83) == '\0') && (*(int *)(iVar7 + 0x4b0) != 0)) {
      local_80 = FLOAT_8043add0 * *(float *)(*(int *)(iVar7 + 0x4b0) + 0x44);
    }
    else {
      local_80 = FLOAT_8043add4;
    }
    dVar11 = (double)local_80;
    local_80 = (float)(dVar11 * (double)*(float *)(iVar7 + 0xb4)) + FLOAT_8043add8;
    gnt4_PSMTXMultVec_bl(afStack_4c,&local_88,(float *)(param_9 + 0x20));
    gnt4_PSVECSubtract_bl
              ((float *)(param_9 + 0x20),(float *)(iVar6 + 100),(float *)(param_9 + 0x150));
    dVar9 = (double)FLOAT_8043addc;
    *(float *)(param_9 + 0x9c) = *(float *)(param_9 + 0x150);
    *(undefined4 *)(param_9 + 0xa0) = *(undefined4 *)(param_9 + 0x154);
    *(undefined4 *)(param_9 + 0xa4) = *(undefined4 *)(param_9 + 0x158);
    gnt4_PSQUATScale_bl(dVar9,(float *)(param_9 + 0x9c),(float *)(param_9 + 0x9c));
    gnt4_PSVECCrossProduct_bl((float *)(param_9 + 0x9c),(float *)&DAT_802b0cb4,&local_88);
    gnt4_PSVECCrossProduct_bl(&local_88,(float *)(param_9 + 0x9c),(float *)(param_9 + 0x38));
    zz_006ebb4_((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    zz_0048288_(param_9);
    *(float *)(param_9 + 0x14c) = FLOAT_8043adc8;
    *(undefined1 *)(param_9 + 0x15c) = 0;
    uVar3 = zz_00055fc_();
    uVar5 = 0x10;
    uVar4 = 5;
    *(ushort *)(param_9 + 0x1e) = ((ushort)uVar3 & 0xf) + 0x3c;
    iVar6 = *(byte *)(param_9 + 0x18) + 1;
    *(char *)(param_9 + 0x18) = (char)iVar6;
    *(undefined1 *)(param_9 + 0x84) = 0x10;
    *(undefined1 *)(param_9 + 0x98) = 5;
    *(code **)(param_9 + 0x100) = zz_0048288_;
    uVar10 = zz_0089100_(param_9,0,1);
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_803528c4 + iVar2);
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_803528d0 + iVar2);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_803528d2 + iVar2);
    iVar7 = zz_0006f98_(iVar8);
    if ((&DAT_803528c1)[iVar2] == '\0') {
      zz_0006fb4_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe0),(int)(char)(&DAT_803528c0)[iVar2]
                  ,uVar4,uVar5,iVar6,in_r9,in_r10);
    }
    else {
      zz_000726c_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe0),
                  (float *)(int)(char)(&DAT_803528c0)[iVar2],(int)*(char *)(param_9 + 0x88),uVar5,
                  iVar6,in_r9,in_r10);
    }
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    zz_0176a44_(param_9);
    return;
  }
  *(undefined1 *)(param_9 + 0x18) = 2;
  *(undefined1 *)(param_9 + 0x82) = 0;
  return;
}



// ==== 80176a44  zz_0176a44_ ====

void zz_0176a44_(int param_1)

{
  char cVar1;
  
  cVar1 = *(char *)(param_1 + 0x15c) + -1;
  *(char *)(param_1 + 0x15c) = cVar1;
  if (cVar1 < '\x01') {
    zz_00f036c_(param_1,0xdf);
    *(undefined1 *)(param_1 + 0x15c) = 0x10;
  }
  if (*(char *)(param_1 + 0x12) == '\0') {
    zz_0176ab0_(param_1);
  }
  else {
    zz_0176bac_(param_1);
  }
  return;
}



// ==== 80176ab0  zz_0176ab0_ ====

void zz_0176ab0_(int param_1)

{
  int iVar1;
  short sVar3;
  int iVar2;
  
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x40;
  iVar1 = zz_0083244_((float *)(param_1 + 0x20));
  if (((iVar1 == 0) && (*(char *)(param_1 + 0x1d9) == '\0')) &&
     (sVar3 = *(short *)(param_1 + 0x1c) + -1, *(short *)(param_1 + 0x1c) = sVar3, 0 < sVar3)) {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(&DAT_803528cc + iVar2);
    if (*(float *)(&DAT_803528c8 + iVar2) < *(float *)(param_1 + 0x44)) {
      *(float *)(param_1 + 0x44) = *(float *)(&DAT_803528c8 + iVar2);
    }
    FUN_80083874((double)*(float *)(&DAT_803528d8 + iVar2),param_1);
    FUN_80083ad4((double)*(float *)(&DAT_803528d4 + iVar2),param_1,
                 (char)*(undefined2 *)(&DAT_803528d2 + iVar2));
    zz_00833ec_(param_1);
    zz_0083524_(param_1);
    iVar2 = zz_0083714_(param_1);
    if ((iVar2 == 0) && (iVar2 = zz_0084170_(param_1), iVar2 == 0)) {
      return;
    }
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  return;
}



// ==== 80176bac  zz_0176bac_ ====

void zz_0176bac_(int param_1)

{
  float fVar1;
  int iVar2;
  short sVar3;
  double dVar4;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  fVar1 = FLOAT_8043adcc;
  *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) + FLOAT_8043ade0;
  if (fVar1 < *(float *)(param_1 + 0x14c)) {
    *(float *)(param_1 + 0x14c) = fVar1;
  }
  *(undefined2 *)(param_1 + 0x272) = 0xffff;
  iVar2 = zz_0083244_((float *)(param_1 + 0x20));
  if (((iVar2 == 0) && (*(int *)(param_1 + 0x148) != 0)) &&
     (iVar2 = *(int *)(param_1 + 0x144), iVar2 != 0)) {
    gnt4_PSVECAdd_bl((float *)(iVar2 + 100),(float *)(param_1 + 0x150),(float *)(param_1 + 0x20));
    sVar3 = *(short *)(param_1 + 0x1e) + -1;
    *(short *)(param_1 + 0x1e) = sVar3;
    if (0 < sVar3) {
      if (0x1d < *(short *)(param_1 + 0x1e)) {
        return;
      }
      zz_00833a4_(param_1);
      return;
    }
    if ((*(byte *)(param_1 + 0x15d) & 4) != 0) {
      gnt4_PSVECSubtract_bl((float *)(iVar2 + 100),(float *)(param_1 + 0x20),&local_18);
      dVar4 = gnt4_PSVECMag_bl(&local_18);
      if ((double)FLOAT_8043adc8 < dVar4) {
        *(float *)(param_1 + 0x38) = local_18;
        *(undefined4 *)(param_1 + 0x3c) = local_14;
        *(undefined4 *)(param_1 + 0x40) = local_10;
        zz_006ebb4_((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        zz_0176294_(param_1,3);
        zz_00833a4_(param_1);
        *(float *)(param_1 + 0x14c) = FLOAT_8043adc8;
      }
    }
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  return;
}



// ==== 80176cf0  FUN_80176cf0 ====

void FUN_80176cf0(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043adc8;
  *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) - FLOAT_8043ade0;
  if (*(float *)(param_1 + 0x14c) < fVar1) {
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x18) = 3;
    fVar1 = FLOAT_8043adc8;
    *(undefined1 *)(param_1 + 0x82) = 0;
    *(float *)(param_1 + 0x14c) = fVar1;
  }
  return;
}



// ==== 80176d54  FUN_80176d54 ====

void FUN_80176d54(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80176d74  FUN_80176d74 ====

/* WARNING: Removing unreachable block (ram,0x80176dbc) */

void FUN_80176d74(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  int iVar1;
  uint uVar2;
  float *pfVar3;
  int iVar4;
  double dVar5;
  undefined8 uVar6;
  double dVar7;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_78 [12];
  float afStack_48 [15];
  
  if (FLOAT_8043adc8 < *(float *)(param_1 + 0x14c)) {
    iVar4 = *(int *)(param_1 + 0x90);
    iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x40;
    gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043ade4 *
                                       (double)((longlong)(double)*(short *)(param_1 + 0x72) *
                                               0x3ff0000000000000)),afStack_48,0x79);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_48,afStack_48);
    dVar5 = (double)(*(float *)(param_1 + 0x14c) * *(float *)(&DAT_803528fc + iVar1));
    dVar7 = dVar5;
    gnt4_PSMTXScale_bl(dVar5,dVar5,dVar5,afStack_78);
    pfVar3 = afStack_48;
    uVar6 = gnt4_PSMTXConcat_bl(pfVar3,afStack_78,pfVar3);
    zz_00076d0_(uVar6,dVar5,dVar7,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),afStack_48,
                (undefined *)pfVar3,param_4,param_5,param_6,param_7,param_8);
    uVar2 = (uint)*(short *)(&DAT_803528fa + iVar1);
    if (*(char *)(iVar4 + 0x3ec) == '\x04') {
      uVar2 = 0x44;
    }
    zz_00097b4_(*(int *)(param_1 + 0xe0),uVar2);
  }
  return;
}



// ==== 80176e54  zz_0176e54_ ====

void zz_0176e54_(int param_1)

{
  char *pcVar1;
  
  pcVar1 = *(char **)(param_1 + 0x148);
  if ((pcVar1 != (char *)0x0) && (*pcVar1 != '\0')) {
    if ((*(char **)(param_1 + 0x144) != (char *)0x0) &&
       ((**(char **)(param_1 + 0x144) != '\0' && (pcVar1[0x18] < '\x02')))) goto LAB_80176ea4;
  }
  *(undefined4 *)(param_1 + 0x144) = 0;
  *(undefined4 *)(param_1 + 0x148) = 0;
  *(undefined1 *)(param_1 + 0x15d) = 0;
LAB_80176ea4:
  *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 200) = *(undefined4 *)(param_1 + 0x144);
  *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(param_1 + 0x15d);
  return;
}



// ==== 80176ec0  zz_0176ec0_ ====

undefined1 * zz_0176ec0_(int param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,3);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x21;
    puVar1[0x11] = param_3;
    puVar1[0x12] = param_2;
    puVar1[0x13] = 3;
    *(code **)(puVar1 + 0xc) = FUN_80176ff0;
    *(code **)(puVar1 + 0x10c) = FUN_801772f4;
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
    *(undefined4 *)(puVar1 + 0x54) = 0;
  }
  zz_00f036c_(param_1,0x21);
  return puVar1;
}



// ==== 80176ff0  FUN_80176ff0 ====

void FUN_80176ff0(int param_1)

{
  (*(code *)(&PTR_FUN_80352ad8)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 8017702c  FUN_8017702c ====

void FUN_8017702c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  
  uVar2 = *(char *)(param_9 + 0x13) * 0x2c;
  if (uVar2 < 0x81) {
    *(int *)(param_9 + 0x54) = param_9 + 0x144;
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar3 = zz_0006dc8_(uVar2);
    *(int **)(param_9 + 0xdc) = piVar3;
    if (piVar3 != (int *)0x0) {
      *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_9 + 0x54) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    iVar5 = *(int *)(param_9 + 0x8c);
    *(undefined1 *)(param_9 + 0x18) = 1;
    iVar1 = *(char *)(param_9 + 0x11) * 0x10;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined2 *)(param_9 + 0x1e) = 0xf;
    *(float *)(param_9 + 0xb4) = *(float *)(iVar5 + 0xb4) * *(float *)(iVar5 + 0x7fc);
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar5 + *(int *)(&DAT_80352a10 + iVar1) * 0x30 + 0x8d4),
               (float *)(iVar1 + -0x7fcad5ec),(float *)(param_9 + 0x20));
    *(code **)(param_9 + 0x100) = FUN_8017721c;
    uVar4 = 1;
    uVar6 = zz_0089100_(param_9,1,1);
    zz_0177378_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar4,iVar5,
                in_r7,in_r8,in_r9,in_r10);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 80177140  FUN_80177140 ====

void FUN_80177140(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  int iVar2;
  
  if (0 < *(short *)(param_9 + 0x1e)) {
    sVar1 = *(short *)(param_9 + 0x1e) + -1;
    *(short *)(param_9 + 0x1e) = sVar1;
    if (sVar1 == 0) {
      iVar2 = 0;
      do {
        param_1 = zz_0177378_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                              param_9,1,param_11,param_12,param_13,param_14,param_15,param_16);
        iVar2 = iVar2 + 1;
      } while (iVar2 < 2);
    }
  }
  iVar2 = zz_017754c_(param_9);
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 801771d4  FUN_801771d4 ====

void FUN_801771d4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8017721c  FUN_8017721c ====

void FUN_8017721c(int param_1)

{
  float *pfVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
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
  float afStack_58 [3];
  float afStack_4c [14];
  
  iVar4 = 0;
  iVar6 = 0;
  iVar5 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar4) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar4) != 0) {
      iVar3 = *(int *)(param_1 + 0x54) + iVar6;
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(iVar3 + 0x10),afStack_58);
      dVar8 = (double)*(float *)(param_1 + 0x24);
      dVar9 = (double)*(float *)(param_1 + 0x28);
      gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar8,dVar9,afStack_4c);
      zz_00457d4_('y',afStack_4c,afStack_4c,*(short *)(iVar3 + 0x26));
      iVar2 = (int)*(short *)(iVar3 + 0x24);
      zz_00457d4_('x',afStack_4c,afStack_4c,*(short *)(iVar3 + 0x24));
      pfVar1 = afStack_58;
      uVar7 = zz_00456a0_(afStack_4c,afStack_4c,pfVar1);
      zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),afStack_4c,
                  (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
    }
    iVar6 = iVar6 + 0x2c;
    iVar5 = iVar5 + 4;
    iVar4 = iVar4 + 1;
  }
  return;
}



// ==== 801772f4  FUN_801772f4 ====

void FUN_801772f4(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar1) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar1) != 0) {
      zz_00097b4_(*(int *)(iVar2 + 0xe0),0x44);
    }
    iVar2 = iVar2 + 4;
    iVar1 = iVar1 + 1;
  }
  return;
}



// ==== 80177378  zz_0177378_ ====

void zz_0177378_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined4 extraout_r4;
  float *pfVar2;
  int iVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  undefined8 uVar9;
  double local_28;
  
  iVar3 = param_10 * 0xc;
  iVar6 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar6) break;
    uVar4 = 1 << iVar6;
    if (((int)(short)*(ushort *)(param_9 + 0x1c) & uVar4) == 0) {
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)uVar4;
      piVar5 = (int *)(*(int *)(param_9 + 0x54) + iVar6 * 0x2c);
      *(undefined2 *)(piVar5 + 8) = 0;
      *(undefined2 *)((int)piVar5 + 0x22) = *(undefined2 *)(&DAT_80352ac2 + iVar3);
      uVar1 = zz_00055fc_();
      *(short *)(piVar5 + 9) = (short)(uVar1 << 8);
      uVar1 = zz_00055fc_();
      *(short *)((int)piVar5 + 0x26) = (short)(uVar1 << 8);
      if (param_10 == 0) {
        *(undefined2 *)((int)piVar5 + 0x2a) = 0;
        *(undefined2 *)(piVar5 + 10) = 0;
      }
      else {
        uVar1 = zz_00055fc_();
        uVar4 = uVar1 & 0xff;
        dVar8 = (double)FLOAT_8043ade8;
        dVar7 = (double)FLOAT_8043adf0;
        param_3 = (double)(float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - DOUBLE_8043adf8)
        ;
        param_2 = (double)FLOAT_8043adec;
        *(short *)(piVar5 + 10) = (short)(int)(param_2 * (double)(float)(param_3 / dVar8));
        *(short *)((int)piVar5 + 0x2a) =
             (short)(int)(param_2 * (double)(float)(dVar7 - (double)(float)(param_3 / dVar8)));
        if ((uVar1 & 1) != 0) {
          *(short *)(piVar5 + 10) = -*(short *)(piVar5 + 10);
        }
        if ((uVar1 & 2) != 0) {
          *(short *)((int)piVar5 + 0x2a) = -*(short *)((int)piVar5 + 0x2a);
        }
      }
      zz_0018f88_(piVar5,(int)(&PTR_DAT_80352ac4)[param_10 * 3],(float *)(piVar5 + 4));
      uVar9 = zz_0019338_(piVar5 + 2,*(int *)(&DAT_80352ac8 + iVar3),(float *)(piVar5 + 7));
      iVar6 = iVar6 * 4 + 0xe0;
      pfVar2 = (float *)(int)*(short *)(&DAT_80352ac0 + iVar3);
      zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                  *(int *)(param_9 + iVar6),(int)pfVar2,uVar4,param_13,param_14,param_15,param_16);
      local_28 = (double)(CONCAT44(0x43300000,(int)*(char *)(param_9 + 0x12)) ^ 0x80000000);
      uVar9 = zz_00086b8_((double)(float)(local_28 - DOUBLE_8043adf8),param_2,param_3,param_4,
                          param_5,param_6,param_7,param_8,DAT_803bb374,*(int *)(param_9 + iVar6),
                          pfVar2,uVar4,param_13,param_14,param_15,param_16);
      zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + iVar6),extraout_r4,pfVar2,uVar4,param_13,param_14,param_15,
                  param_16);
      zz_0007cac_((double)(float)piVar5[7],*(int *)(param_9 + iVar6));
      iVar6 = (int)*(char *)(param_9 + 0x13);
    }
    iVar6 = iVar6 + 1;
  }
  return;
}



// ==== 8017754c  zz_017754c_ ====

int zz_017754c_(int param_1)

{
  short sVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = 0;
  iVar5 = 0;
  iVar4 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar3) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar3) != 0) {
      piVar2 = (int *)(*(int *)(param_1 + 0x54) + iVar5);
      sVar1 = *(short *)(piVar2 + 8);
      *(short *)(piVar2 + 8) = sVar1 + 1;
      if (*(short *)((int)piVar2 + 0x22) <= (short)(sVar1 + 1)) {
        *(ushort *)(param_1 + 0x1c) = *(ushort *)(param_1 + 0x1c) & ~(ushort)(1 << iVar3);
      }
      *(short *)(piVar2 + 9) = *(short *)(piVar2 + 9) + *(short *)(piVar2 + 10);
      *(short *)((int)piVar2 + 0x26) =
           *(short *)((int)piVar2 + 0x26) + *(short *)((int)piVar2 + 0x2a);
      zz_0018fd8_(piVar2,(int)*(short *)(piVar2 + 8),(float *)(piVar2 + 4));
      zz_0019370_(piVar2 + 2,(int)*(short *)(piVar2 + 8),(float *)(piVar2 + 7));
      zz_0007cac_((double)(float)piVar2[7],*(int *)(iVar4 + 0xe0));
    }
    iVar5 = iVar5 + 0x2c;
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 1;
  }
  return (int)*(short *)(param_1 + 0x1c);
}



// ==== 80177634  zz_0177634_ ====

void zz_0177634_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80352ae8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80177684  FUN_80177684 ====

void FUN_80177684(int param_1,int *param_2)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_8043ae08;
  fVar1 = FLOAT_8043ae00;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  *(float *)(param_1 + 0x558) =
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 5) ^ 0x80000000) - dVar2);
  *(char *)(param_1 + 0x6ef) = (char)*(undefined2 *)((int)param_2 + 0x16);
  if (*(short *)(param_1 + 0x774) < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  if ((code *)param_2[4] != (code *)0x0) {
    (*(code *)param_2[4])(param_1);
  }
  *(undefined1 *)(param_1 + 0x543) = 1;
  if (*(char *)(param_1 + 0x5db) == '\x01') {
    *(undefined1 *)(param_1 + 0x543) = 0xf;
  }
  zz_004beb8_((double)FLOAT_8043ae04,param_1,(int)*(char *)(param_1 + 0x543),2,*param_2,0xffffffff,
              0xffffffff);
  return;
}



// ==== 8017776c  FUN_8017776c ====

void FUN_8017776c(int param_1,int param_2)

{
  float fVar1;
  int iVar2;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,(int)*(char *)(param_1 + 0x543));
  }
  fVar1 = FLOAT_8043ae10;
  *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  if ((*(float *)(param_1 + 0x560) <= fVar1) ||
     ((*(code **)(param_2 + 0x10) != (code *)0x0 &&
      (iVar2 = (**(code **)(param_2 + 0x10))(param_1), iVar2 != 0)))) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80177808  FUN_80177808 ====

void FUN_80177808(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  
  zz_004cd24_(param_9,(int)*(char *)(param_9 + 0x543));
  if (*(code **)(param_10 + 0x10) != (code *)0x0) {
    param_1 = (double)(**(code **)(param_10 + 0x10))(param_9);
  }
  if (*(char *)(param_9 + 0x1cef) != '\0') {
    uVar3 = 1;
    uVar4 = 0;
    iVar2 = zz_006dbe0_(param_9,0,1,0);
    fVar1 = FLOAT_8043ae10;
    if (iVar2 == 0) {
      *(undefined1 *)(param_9 + 0x73f) = 0;
      *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
      zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,4,uVar3,
                  uVar4,param_13,param_14,param_15,param_16);
    }
    else {
      *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + '\x01';
      *(float *)(param_9 + 0x558) = fVar1;
      *(char *)(param_9 + 0x6ef) = *(char *)(param_9 + 0x6ef) + -1;
      if (*(code **)(param_10 + 8) != (code *)0x0) {
        (**(code **)(param_10 + 8))(param_9);
      }
      *(undefined1 *)(param_9 + 0x543) = 1;
      if (*(char *)(param_9 + 0x5db) == '\x01') {
        *(undefined1 *)(param_9 + 0x543) = 0xf;
      }
    }
  }
  return;
}



// ==== 80177900  FUN_80177900 ====

void FUN_80177900(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,int param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  double extraout_f1;
  
  zz_004cd24_(param_9,1);
  dVar2 = (double)*(float *)(param_9 + 0x558);
  if (dVar2 <= (double)FLOAT_8043ae10) {
    if (*(code **)(param_10 + 0xc) != (code *)0x0) {
      iVar1 = (**(code **)(param_10 + 0xc))(param_9);
      dVar2 = extraout_f1;
      if (iVar1 != 0) {
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -2;
        *(undefined1 *)(param_9 + 0x543) = 1;
        if (*(char *)(param_9 + 0x5db) == '\x01') {
          *(undefined1 *)(param_9 + 0x543) = 0xf;
        }
        zz_004beb8_((double)FLOAT_8043ae04,param_9,(int)*(char *)(param_9 + 0x543),2,
                    *(int *)(param_10 + 4),0xffffffff,0xffffffff);
        return;
      }
      goto LAB_80177a04;
    }
    if ((*(ushort *)(param_9 + 0x5d8) & 0xf0) != 0) goto LAB_80177a04;
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar2 - (double)*(float *)(param_9 + 0x1dc8));
    if (*(code **)(param_10 + 0x10) != (code *)0x0) {
      dVar2 = (double)(**(code **)(param_10 + 0x10))(param_9);
    }
  }
  if (((-1 < *(char *)(param_9 + 0x1cef)) || (*(char *)(param_9 + 0x5db) == '\x01')) &&
     (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_80177a04:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,4,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80177a3c  zz_0177a3c_ ====

void zz_0177a3c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80352af8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80177a8c  FUN_80177a8c ====

void FUN_80177a8c(int param_1,int *param_2)

{
  float fVar1;
  
  fVar1 = FLOAT_8043ae00;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  fVar1 = FLOAT_8043ae10;
  *(float *)(param_1 + 0x50) = FLOAT_8043ae10;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)(float)param_2[1],(float *)(param_1 + 0x38),(float *)(param_1 + 0x38))
  ;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_004beb8_((double)FLOAT_8043ae04,param_1,0xf,2,*param_2,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043ae10;
  return;
}



// ==== 80177b88  FUN_80177b88 ====

void FUN_80177b88(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 4),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  zz_006e1ac_(param_1,0xc1,1);
  fVar2 = FLOAT_8043ae10;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc1), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80177c48  FUN_80177c48 ====

void FUN_80177c48(int param_1,int param_2)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 4),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(code **)(param_2 + 8) != (code *)0x0) {
      (**(code **)(param_2 + 8))(param_1);
    }
    fVar1 = FLOAT_8043ae18;
    *(float *)(param_1 + 0x44) = FLOAT_8043ae14;
    *(float *)(param_1 + 0x4c) = fVar1;
  }
  return;
}



// ==== 80177d08  FUN_80177d08 ====

void FUN_80177d08(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_00b22f4_(param_1);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_8043ae1c,param_1,*(short *)(param_1 + 0x72) + -0x8000);
  iVar2 = zz_00679d0_(param_1);
  fVar1 = FLOAT_8043ae10;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
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
  }
  return;
}



// ==== 80177dd8  zz_0177dd8_ ====

void zz_0177dd8_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80352b08)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80177e28  FUN_80177e28 ====

void FUN_80177e28(int param_1,undefined4 *param_2)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043ae20;
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043ae04;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043ae10;
  return;
}



// ==== 80177f10  FUN_80177f10 ====

void FUN_80177f10(int param_1,int param_2)

{
  float fVar1;
  double dVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar3 = FLOAT_8043ae10;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar3) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    dVar2 = DOUBLE_8043ae08;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,*(uint *)(param_2 + 8) ^ 0x80000000) - dVar2);
    zz_01782dc_(param_1,param_2);
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 80177fd4  FUN_80177fd4 ====

void FUN_80177fd4(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  if ((*(byte *)(param_1 + 0x1dd) & 0x80) != 0) {
    if (*(char *)(param_1 + 0x745) == '\0') {
      if (*(code **)(param_2 + 0x14) != (code *)0x0) {
        (**(code **)(param_2 + 0x14))(param_1);
      }
    }
  }
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)*(float *)(param_2 + 0xc),param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043ae10;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) ||
     (uVar3 = FUN_800668cc((double)*(float *)(param_2 + 4),param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  zz_017a68c_(param_1);
  return;
}



// ==== 801780e4  FUN_801780e4 ====

void FUN_801780e4(int param_1,int param_2)

{
  char cVar1;
  double dVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  if ((((*(byte *)(param_1 + 0x1dd) & 0x80) != 0) && (*(char *)(param_1 + 0x745) == '\0')) &&
     (*(code **)(param_2 + 0x14) != (code *)0x0)) {
    (**(code **)(param_2 + 0x14))(param_1);
  }
  zz_004cd24_(param_1,0xf);
  dVar2 = DOUBLE_8043ae08;
  if (((char)*(byte *)(param_1 + 0x1cf0) < '\0') &&
     ((*(byte *)(param_1 + 0x746) & *(byte *)(param_1 + 0x745)) != 0)) {
    if (((*(byte *)(param_1 + 0x1cf0) & 1) == 0) && (*(code **)(param_2 + 0x10) != (code *)0x0)) {
      (**(code **)(param_2 + 0x10))(param_1);
      return;
    }
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    dVar3 = (double)FLOAT_8043ae04;
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(undefined1 *)(param_1 + 0x745) = 0;
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,*(uint *)(param_2 + 8) ^ 0x80000000) - dVar2);
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    zz_01782dc_(param_1,param_2);
    zz_00b2190_(param_1,0);
    return;
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    zz_01782dc_(param_1,param_2);
  }
  zz_006ed8c_((double)*(float *)(param_2 + 0xc),param_1);
  if (*(float *)(param_1 + 0x760) < *(float *)(param_2 + 4)) {
    zz_006ed8c_((double)FLOAT_8043ae24,param_1);
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  zz_017a68c_(param_1);
  return;
}



// ==== 801782dc  zz_01782dc_ ====

void zz_01782dc_(int param_1,int param_2)

{
  float fVar1;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
  }
  else {
    fVar1 = *(float *)(param_1 + 0x760) *
            (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000) -
                   DOUBLE_8043ae08) * FLOAT_8043ae28;
  }
  if (*(uint *)(param_2 + 8) != 0) {
    *(float *)(param_1 + 0x44) =
         fVar1 / (float)((double)CONCAT44(0x43300000,*(uint *)(param_2 + 8) ^ 0x80000000) -
                        DOUBLE_8043ae08);
  }
  *(undefined1 *)(param_1 + 0x1d0f) = 0;
  return;
}



// ==== 80178394  zz_0178394_ ====

void zz_0178394_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_01783e4__80352b18)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801783e4  zz_01783e4_ ====

void zz_01783e4_(int param_1,undefined4 *param_2)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043ae00;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(undefined1 *)(param_1 + 0x746) = 0;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_8043ae10;
  dVar4 = (double)FLOAT_8043ae04;
  *(float *)(param_1 + 0x50) = FLOAT_8043ae10;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  cVar1 = *(char *)(param_1 + 0x6ea);
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  else {
    zz_006e1ac_(param_1,0xc0,1);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)(float)param_2[3],(float *)(param_1 + 0x38),(float *)(param_1 + 0x38))
  ;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  return;
}



// ==== 80178574  FUN_80178574 ====

void FUN_80178574(int param_1,int param_2)

{
  float fVar1;
  double dVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0xc),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  else {
    zz_006e1ac_(param_1,0xc0,1);
  }
  fVar3 = FLOAT_8043ae10;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar3) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    dVar2 = DOUBLE_8043ae08;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 8) ^ 0x80000000) - dVar2);
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 80178684  FUN_80178684 ====

void FUN_80178684(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    if (*(char *)(param_1 + 0x1b03) == '\0') goto LAB_801786c4;
  }
  zz_004cd24_(param_1,0xf);
LAB_801786c4:
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  else {
    zz_006e1ac_(param_1,0xc0,1);
    *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x18da);
  }
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_2 + 0x10) * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_8043ae1c;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_2 + 0x10) * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043ae10;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) ||
     (uVar3 = FUN_800668cc((double)*(float *)(param_2 + 4),param_1), 0 < (int)uVar3)) {
    dVar4 = DOUBLE_8043ae08;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 10) ^ 0x80000000) - dVar4);
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * *(float *)(param_2 + 0x14);
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * *(float *)(param_2 + 0x14);
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * *(float *)(param_2 + 0x14);
    *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) * *(float *)(param_2 + 0x14);
  }
  return;
}



// ==== 80178808  FUN_80178808 ====

void FUN_80178808(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    if (*(char *)(param_1 + 0x1b03) == '\0') goto LAB_8017885c;
  }
  zz_004cd24_(param_1,0xf);
LAB_8017885c:
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  else {
    zz_006e1ac_(param_1,0xc0,1);
    *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x18da);
  }
  zz_006ed8c_((double)*(float *)(param_2 + 0x18),param_1);
  FUN_80067310((double)FLOAT_8043ae1c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043ae10;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80178908  FUN_80178908 ====

void FUN_80178908(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  }
  if (((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) &&
     (*(char *)(param_1 + 0x745) != '\0')) {
    dVar3 = (double)FLOAT_8043ae04;
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(undefined1 *)(param_1 + 0x745) = 0;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    if (*(char *)(param_1 + 0x1d0f) < '\x01') {
      return;
    }
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_2 + 0x10) * dVar3);
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_2 + 0x10) * -dVar3);
    return;
  }
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
    if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
      zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
    }
    else {
      zz_006e1ac_(param_1,0xc0,1);
      *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x18da);
    }
  }
  if ('\0' < *(char *)(param_1 + 0x1d0f)) {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_2 + 0x10) * dVar3);
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_2 + 0x10) * -dVar3);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)*(float *)(param_2 + 0x18),param_1);
  FUN_80067310((double)FLOAT_8043ae1c,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043ae1c + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80178b6c  zz_0178b6c_ ====

void zz_0178b6c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80352b2c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80178bbc  FUN_80178bbc ====

void FUN_80178bbc(int param_1,int *param_2)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_8043ae20;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(undefined1 *)(param_1 + 0x746) = 0;
  uVar2 = FUN_800668cc((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_004beb8_((double)FLOAT_8043ae04,param_1,0xf,3,*param_2,0xffffffff,0xffffffff);
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  else {
    zz_006e1ac_(param_1,0xc0,1);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)(float)param_2[3],(float *)(param_1 + 0x38),(float *)(param_1 + 0x38))
  ;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  return;
}



// ==== 80178d10  FUN_80178d10 ====

void FUN_80178d10(int param_1,int param_2)

{
  float fVar1;
  double dVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0xc),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  else {
    zz_006e1ac_(param_1,0xc0,1);
  }
  fVar3 = FLOAT_8043ae10;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar3) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    dVar2 = DOUBLE_8043ae08;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 8) ^ 0x80000000) - dVar2);
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 80178e20  FUN_80178e20 ====

void FUN_80178e20(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    if (*(char *)(param_1 + 0x1b03) == '\0') goto LAB_80178e60;
  }
  zz_004cd24_(param_1,0xf);
LAB_80178e60:
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  else {
    zz_006e1ac_(param_1,0xc0,1);
    *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x18da);
  }
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x54e));
  *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_2 + 0x10) * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x54e));
  dVar5 = (double)FLOAT_8043ae1c;
  *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_2 + 0x10) * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043ae10;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) ||
     (uVar3 = FUN_800668cc((double)*(float *)(param_2 + 4),param_1), 0 < (int)uVar3)) {
    dVar4 = DOUBLE_8043ae08;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 10) ^ 0x80000000) - dVar4);
  }
  return;
}



// ==== 80178f64  FUN_80178f64 ====

void FUN_80178f64(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
  }
  else {
    zz_006e1ac_(param_1,0xc0,1);
    *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x18da);
  }
  zz_006ed8c_((double)*(float *)(param_2 + 0x14),param_1);
  FUN_80067310((double)FLOAT_8043ae1c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043ae10;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_2 + 0x10);
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar3);
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar3);
  }
  return;
}



// ==== 80179074  FUN_80179074 ====

void FUN_80179074(int param_1,int param_2)

{
  int iVar1;
  double dVar2;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043ae08) * FLOAT_8043ae2c);
  }
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  if ('\0' < *(char *)(param_1 + 0x1d10)) {
    zz_006d144_(param_1,0xc0);
    if ((*(byte *)(param_1 + 0x1d10) & 2) == 0) {
      zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
    }
    else {
      zz_006e1ac_(param_1,0xc0,1);
      *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x18da);
    }
    dVar2 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x38) * dVar2);
    dVar2 = zz_0045204_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x48) = (float)((double)*(float *)(param_1 + 0x38) * -dVar2);
  }
  if ((*(byte *)(param_1 + 0x1d9) & 0x30) != 0) {
    if (*(code **)(param_2 + 0x1c) != (code *)0x0) {
      (**(code **)(param_2 + 0x1c))(param_1);
    }
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  zz_006eddc_((double)*(float *)(param_2 + 0x18),param_1,(float *)(param_1 + 0x38));
  zz_006ed8c_((double)*(float *)(param_2 + 0x18),param_1);
  FUN_80067310((double)FLOAT_8043ae1c,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043ae1c + *(float *)(param_1 + 0x1dc8);
    *(undefined2 *)(param_1 + 0x18da) = 0;
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80179280  zz_0179280_ ====

void zz_0179280_(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_80352b40)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801792dc  FUN_801792dc ====

void FUN_801792dc(int param_1,short *param_2)

{
  uint uVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(undefined1 *)(param_1 + 0x745) = 0;
  uVar1 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar1 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043ae20;
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 4),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_8043ae04,param_1,0xf,3,(int)*param_2,0xffffffff,0xffffffff);
  return;
}



// ==== 801793e8  FUN_801793e8 ====

void FUN_801793e8(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 8),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar1 = FLOAT_8043ae10;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if ((fVar2 <= fVar1) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    dVar3 = DOUBLE_8043ae08;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 2) ^ 0x80000000) - dVar3);
    fVar2 = FLOAT_8043ae10;
    if (*(int *)(param_1 + 0xcc) == 0) {
      fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    }
    else {
      fVar1 = *(float *)(param_1 + 0x760) *
              (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000) -
                     dVar3) * FLOAT_8043ae28;
    }
    *(float *)(param_1 + 0x44) =
         fVar1 / (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 2) ^ 0x80000000) -
                        DOUBLE_8043ae08);
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x80c) = fVar2;
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80179574  FUN_80179574 ====

void FUN_80179574(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)*(float *)(param_2 + 0xc),param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  fVar2 = FLOAT_8043ae10;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) ||
     (uVar3 = FUN_80066838((double)*(float *)(param_2 + 4),param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * *(float *)(param_2 + 0x10);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 8017965c  FUN_8017965c ====

void FUN_8017965c(int param_1,int param_2)

{
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_004cd24_(param_1,0xf);
    zz_006ed8c_((double)*(float *)(param_2 + 0x14),param_1);
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
    if ('\0' < *(char *)(param_1 + 0x1cf0)) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(param_2 + 0x18);
      *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_2 + 0x1c);
      *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_2 + 0x20);
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_2 + 0x24);
      zz_0066530_(param_1,0x2d);
      zz_00b2190_(param_1,0);
    }
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8017972c  FUN_8017972c ====

void FUN_8017972c(int param_1,int param_2)

{
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  zz_004cd24_(param_1,0xf);
  if (((*(char *)(param_1 + 0x1cf0) < '\0') &&
      ((*(byte *)(param_1 + 0x746) & *(byte *)(param_1 + 0x745)) != 0)) &&
     (*(code **)(param_2 + 0x28) != (code *)0x0)) {
    (**(code **)(param_2 + 0x28))(param_1);
    return;
  }
  FUN_80067310((double)FLOAT_8043ae1c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 80179814  zz_0179814_ ====

void zz_0179814_(int param_1)

{
  (*(code *)(&PTR_FUN_80352b54)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80179850  FUN_80179850 ====

void FUN_80179850(int param_1,undefined4 *param_2)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  dVar3 = DOUBLE_8043ae08;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) =
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_2 + 3) ^ 0x80000000) - dVar3);
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)((int)param_2 + 0xe);
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(char *)(param_1 + 0x6ea) = (char)param_2[1];
  }
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  fVar2 = FLOAT_8043ae10;
  *(float *)(param_1 + 0x50) = FLOAT_8043ae10;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  if ((code *)param_2[4] != (code *)0x0) {
    (*(code *)param_2[4])(param_1);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)(float)param_2[2],(float *)(param_1 + 0x38),(float *)(param_1 + 0x38))
  ;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043ae04;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801799bc  FUN_801799bc ====

void FUN_801799bc(int param_1,int param_2)

{
  zz_004cd24_(param_1,0xf);
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 8),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x6f7) = 2;
    if (*(code **)(param_2 + 0x14) != (code *)0x0) {
      (**(code **)(param_2 + 0x14))(param_1);
    }
  }
  return;
}



// ==== 80179a88  FUN_80179a88 ====

void FUN_80179a88(int param_1,int param_2)

{
  double dVar1;
  uint uVar2;
  
  *(undefined1 *)(param_1 + 0x6f7) = 2;
  uVar2 = zz_006de44_(param_1,0xf0f00);
  dVar1 = DOUBLE_8043ae08;
  if (uVar2 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar2) {
      uVar2 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar2;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - dVar1);
  }
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 8),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_8043ae1c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(float *)(param_1 + 0x560) <= FLOAT_8043ae10) {
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x1cef) < '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x6f7) = 0;
    }
  }
  else {
    *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
    if (-1 < *(char *)(param_1 + 0x1cef)) {
      zz_004cd24_(param_1,0xf);
    }
  }
  return;
}



// ==== 80179c00  FUN_80179c00 ====

void FUN_80179c00(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  dVar3 = (double)FLOAT_8043ae1c;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043ae08) * FLOAT_8043ae30);
  FUN_80067310(dVar3,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043ae34 + *(float *)(param_1 + 0x1dc8);
    *(undefined2 *)(param_1 + 0x18da) = 0;
    return;
  }
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043ae10;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
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
  }
  return;
}



// ==== 80179d20  zz_0179d20_ ====

void zz_0179d20_(int param_1)

{
  (*(code *)(&PTR_FUN_804347a8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80179d58  FUN_80179d58 ====

void FUN_80179d58(int param_1,undefined4 *param_2)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  zz_006d144_(param_1,0xc1);
  zz_006e1ac_(param_1,0xc1,1);
  fVar2 = FLOAT_8043ae10;
  *(float *)(param_1 + 0x50) = FLOAT_8043ae10;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  if ((code *)param_2[2] != (code *)0x0) {
    (*(code *)param_2[2])(param_1);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)(float)param_2[1],(float *)(param_1 + 0x38),(float *)(param_1 + 0x38))
  ;
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043ae04;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 80179e60  FUN_80179e60 ====

void FUN_80179e60(int param_1,int param_2)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043ae08) * FLOAT_8043ae30);
  }
  fVar1 = FLOAT_8043ae00;
  if ((*(char *)(param_1 + 0x1cef) < '\x01') || (*(char *)(param_1 + 0x541) < '\x01')) {
    if (*(char *)(param_1 + 0x1d10) != '\0') {
      zz_006d144_(param_1,0xc1);
      zz_006e1ac_(param_1,0xc1,1);
    }
    if (*(char *)(param_1 + 0x1d0f) < '\0') {
      *(undefined1 *)(param_1 + 0x1d0f) = 0;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    }
    gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 4),(float *)(param_1 + 0x38),
                        (float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    FUN_80067310((double)FLOAT_8043ae1c,param_1,*(short *)(param_1 + 0x5ae));
    zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) == '\0') {
      return;
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(float *)(param_1 + 0x694) = fVar1 + *(float *)(param_1 + 0x1dc8);
  }
  fVar1 = FLOAT_8043ae10;
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  zz_006a5a4_(param_1);
  return;
}



// ==== 80179fcc  zz_0179fcc_ ====

void zz_0179fcc_(int param_1)

{
  (*(code *)(&PTR_FUN_80352b64)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8017a008  FUN_8017a008 ====

void FUN_8017a008(int param_1,undefined2 *param_2)

{
  float fVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar1 = FLOAT_8043ae10;
  *(float *)(param_1 + 0x50) = FLOAT_8043ae10;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  if (*(code **)(param_2 + 6) != (code *)0x0) {
    (**(code **)(param_2 + 6))(param_1);
  }
  if (*(code **)(param_2 + 8) != (code *)0x0) {
    (**(code **)(param_2 + 8))(param_1);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 2),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(char *)(param_1 + 0x6ea) = (char)param_2[1];
  }
  zz_004beb8_((double)FLOAT_8043ae04,param_1,0xf,4,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
              0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043ae10;
  return;
}



// ==== 8017a130  FUN_8017a130 ====

void FUN_8017a130(int param_1,int param_2)

{
  double dVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(code **)(param_2 + 0x10) != (code *)0x0) {
    (**(code **)(param_2 + 0x10))(param_1);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 4),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  FUN_80067310((double)FLOAT_8043ae1c,param_1,*(short *)(param_1 + 0x5ae));
  zz_00679d0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(code **)(param_2 + 0x14) != (code *)0x0) {
      (**(code **)(param_2 + 0x14))(param_1);
    }
  }
  dVar1 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_8043ae38 < dVar1) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8017a208  FUN_8017a208 ====

void FUN_8017a208(int param_1,int param_2)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043ae08) * FLOAT_8043ae30);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 4),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  FUN_80067310((double)FLOAT_8043ae1c,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00679d0_(param_1);
  if (iVar1 == 0) {
LAB_8017a2dc:
    if (*(char *)(param_1 + 0x1cee) == '\0') goto LAB_8017a344;
  }
  else if (-1 < *(char *)(param_1 + 0x1cef)) {
    zz_006ed8c_((double)FLOAT_8043ae3c,param_1);
    goto LAB_8017a2dc;
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  if (iVar1 == 0) {
    zz_006a5a4_(param_1);
  }
  else if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006a474_(param_1);
  }
  else {
    zz_006a750_(param_1,7);
  }
  *(float *)(param_1 + 0x694) = FLOAT_8043ae1c + *(float *)(param_1 + 0x1dc8);
LAB_8017a344:
  if (FLOAT_8043ae38 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8017a374  zz_017a374_ ====

void zz_017a374_(int param_1)

{
  (*(code *)(&PTR_FUN_804347b0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8017a3ac  FUN_8017a3ac ====

void FUN_8017a3ac(int param_1,char *param_2)

{
  int iVar1;
  double dVar2;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 8),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00f036c_(param_1,0xb2);
  zz_00660c8_(param_1,0xff);
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
    dVar2 = (double)FLOAT_8043ae04;
    *(undefined2 *)(param_1 + 0x548) = *(undefined2 *)(param_2 + 4);
    zz_004beb8_(dVar2,param_1,0xf,4,(int)param_2[1],0xffffffff,0xffffffff);
  }
  else {
    dVar2 = (double)FLOAT_8043ae04;
    *(undefined2 *)(param_1 + 0x548) = *(undefined2 *)(param_2 + 2);
    zz_004beb8_(dVar2,param_1,0xf,4,(int)*param_2,0xffffffff,0xffffffff);
    *(undefined1 *)(param_1 + 0x709) = 1;
  }
  return;
}



// ==== 8017a4a8  FUN_8017a4a8 ====

void FUN_8017a4a8(char *param_1,int param_2)

{
  double dVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043ae30;
  dVar1 = DOUBLE_8043ae08;
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x1d64) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d64) ^ 0x80000000) - dVar1
                           ) * fVar2);
  *(short *)(param_1 + 0x1d68) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1d68) ^ 0x80000000) - dVar1
                           ) * fVar2);
  zz_004cd24_((int)param_1,0xf);
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 8),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar3 = zz_00677b0_((int)param_1);
  if (iVar3 != 0) {
    param_1[0x709] = '\x01';
  }
  if (param_1[0x1cee] != '\0') {
    zz_006a8c0_(param_1,*(undefined2 *)(param_1 + 0x548));
    zz_017a608_((int)param_1);
    param_1[0x73f] = '\0';
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (*(short *)(param_1 + 0x548) == *(short *)(param_2 + 6)) {
      zz_006a750_((int)param_1,0x1b);
    }
    else if (iVar3 == 0) {
      zz_006a5a4_((int)param_1);
    }
    else {
      zz_006a474_((int)param_1);
    }
  }
  return;
}



// ==== 8017a608  zz_017a608_ ====

void zz_017a608_(int param_1)

{
  *(undefined2 *)(param_1 + 0x18da) = 0;
  *(undefined2 *)(param_1 + 0x197a) = 0;
  *(undefined2 *)(param_1 + 0x1976) = 0;
  *(undefined2 *)(param_1 + 0x1d68) = 0;
  *(undefined2 *)(param_1 + 0x1d64) = 0;
  *(undefined2 *)(param_1 + 0x1974) = 0;
  *(undefined2 *)(param_1 + 0x1970) = 0;
  *(undefined2 *)(param_1 + 0x1968) = 0;
  *(undefined2 *)(param_1 + 0x1964) = 0;
  *(undefined2 *)(param_1 + 0x1926) = 0;
  *(undefined2 *)(param_1 + 0x1922) = 0;
  *(undefined2 *)(param_1 + 0x196e) = 0;
  *(undefined2 *)(param_1 + 0x1962) = 0;
  *(undefined2 *)(param_1 + 0x18e2) = 0;
  *(undefined2 *)(param_1 + 0x18e0) = 0;
  if (*(code **)(param_1 + 0x4b8) != (code *)0x0) {
    (**(code **)(param_1 + 0x4b8))();
  }
  FUN_800562b8(param_1);
  return;
}



// ==== 8017a68c  zz_017a68c_ ====

void zz_017a68c_(int param_1)

{
  double dVar1;
  float afStack_18 [5];
  
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),afStack_18);
  dVar1 = gnt4_PSVECMag_bl(afStack_18);
  if ((double)FLOAT_8043ae38 < dVar1) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8017a6e0  zz_017a6e0_ ====

/* WARNING: Removing unreachable block (ram,0x8017a860) */
/* WARNING: Removing unreachable block (ram,0x8017a6f0) */

undefined4 zz_017a6e0_(int param_1,int param_2,short *param_3,int param_4)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  double dVar5;
  double dVar6;
  float local_48;
  float local_44;
  undefined4 local_40;
  
  iVar3 = *(int *)(param_1 + 0xcc);
  sVar1 = 0;
  if ((iVar3 != 0) &&
     ((*(char *)(iVar3 + 0x83) != '\0' ||
      ((*(byte *)(iVar3 + 0x5e6) & *(byte *)(param_1 + 0x3e5)) != 0)))) {
    iVar3 = param_1 + param_2 * 0x30;
    local_48 = *(float *)(iVar3 + 0x8e0);
    local_44 = *(float *)(iVar3 + 0x8f0);
    local_40 = *(undefined4 *)(iVar3 + 0x900);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_48,&local_48);
    dVar6 = (double)local_44;
    local_44 = FLOAT_8043ae10;
    dVar5 = gnt4_PSVECMag_bl(&local_48);
    iVar3 = FUN_800452a0(dVar6,dVar5);
    sVar1 = (-*(short *)(param_1 + 0x70) - (short)iVar3) - *(short *)(param_1 + 0x1d64);
  }
  if (param_4 != 0) {
    sVar1 = -sVar1;
  }
  if (0x2000 < sVar1) {
    sVar1 = 0x2000;
  }
  if (sVar1 < -0x2000) {
    sVar1 = -0x2000;
  }
  iVar3 = (int)(short)(sVar1 - *param_3);
  sVar2 = (short)(int)((float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(*(int *)(param_1 + 0x4ac) + 0xae) ^
                                                0x80000000) - DOUBLE_8043ae08) *
                      *(float *)(param_1 + 0x1dc8));
  if (iVar3 < 0) {
    iVar3 = -iVar3;
  }
  if (sVar2 < iVar3) {
    if ((short)(sVar1 - *param_3) < 0) {
      sVar2 = -sVar2;
    }
    uVar4 = 0;
    *param_3 = *param_3 + sVar2;
  }
  else {
    *param_3 = sVar1;
    uVar4 = 1;
  }
  return uVar4;
}



// ==== 8017a884  zz_017a884_ ====

undefined4 zz_017a884_(int param_1,int param_2,short *param_3,int param_4)

{
  short sVar1;
  short sVar2;
  int iVar3;
  undefined4 uVar4;
  float local_38;
  undefined4 local_34;
  float local_30;
  
  sVar1 = 0;
  iVar3 = *(int *)(param_1 + 0xcc);
  if (iVar3 != 0) {
    if ((*(char *)(iVar3 + 0x83) != '\0') ||
       ((*(byte *)(iVar3 + 0x5e6) & *(byte *)(param_1 + 0x3e5)) != 0)) {
      iVar3 = param_1 + param_2 * 0x30;
      local_38 = *(float *)(iVar3 + 0x8e0);
      local_34 = *(undefined4 *)(iVar3 + 0x8f0);
      local_30 = *(float *)(iVar3 + 0x900);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_38,&local_38);
      iVar3 = FUN_800452a0((double)local_38,(double)local_30);
      sVar1 = ((short)iVar3 - *(short *)(param_1 + 0x72)) - *(short *)(param_1 + 0x1d66);
    }
  }
  if (param_4 != 0) {
    sVar1 = -sVar1;
  }
  iVar3 = (int)(short)(sVar1 - *param_3);
  sVar2 = (short)(int)((float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(*(int *)(param_1 + 0x4ac) + 0xae) ^
                                                0x80000000) - DOUBLE_8043ae08) *
                      *(float *)(param_1 + 0x1dc8));
  if (iVar3 < 0) {
    iVar3 = -iVar3;
  }
  if (sVar2 < iVar3) {
    if ((short)(sVar1 - *param_3) < 0) {
      sVar2 = -sVar2;
    }
    uVar4 = 0;
    *param_3 = *param_3 + sVar2;
  }
  else {
    *param_3 = sVar1;
    uVar4 = 1;
  }
  return uVar4;
}



// ==== 8017a9e0  zz_017a9e0_ ====

void zz_017a9e0_(int param_1,undefined1 param_2)

{
  short sVar1;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((((sVar1 == 0x503) || (sVar1 == 0x506)) || (sVar1 == 0x508)) ||
      (((sVar1 == 0x50f || (sVar1 == 0x514)) || (sVar1 == 0x512)))) &&
     (puVar2 = zz_0088aa0_(param_1,2,0,0,2), puVar2 != (undefined1 *)0x0)) {
    *puVar2 = 1;
    puVar2[0x83] = 0x18;
    *(code **)(puVar2 + 0xc) = FUN_8017ab10;
    *(code **)(puVar2 + 0x10c) = FUN_8017acc8;
    puVar2[0x13] = param_2;
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



// ==== 8017ab10  FUN_8017ab10 ====

void FUN_8017ab10(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_80352db0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8017ab64  FUN_8017ab64 ====

void FUN_8017ab64(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined4 extraout_r4;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  iVar5 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar3 = *(char *)(param_9 + 0x13) * 0x24;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar4 = iVar3;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x43;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_80352b72 + iVar3);
  uVar1 = *(undefined4 *)(&DAT_80352b78 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_80352b74 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_80352b7c + iVar3);
  uVar1 = *(undefined4 *)(&DAT_80352b84 + iVar3);
  *(undefined4 *)(param_9 + 0x58) = *(undefined4 *)(&DAT_80352b80 + iVar3);
  *(undefined4 *)(param_9 + 0x5c) = uVar1;
  *(undefined4 *)(param_9 + 0x60) = *(undefined4 *)(&DAT_80352b88 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_80352b8c + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_80352b90 + iVar3);
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_80352b70 + iVar3),iVar5 + 0xc28,iVar4,in_r8,in_r9,in_r10)
  ;
  iVar2 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_80352b70 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar2,iVar4,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar2,iVar4,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043ae40,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_017ac8c_();
  return;
}



// ==== 8017ac8c  zz_017ac8c_ ====

void zz_017ac8c_(void)

{
  return;
}



// ==== 8017aca8  FUN_8017aca8 ====

void FUN_8017aca8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8017acc8  FUN_8017acc8 ====

void FUN_8017acc8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined *puVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar2;
  int iVar3;
  
  puVar1 = *(undefined **)(param_9 + 0x90);
  if (((int)(char)puVar1[0x18c] & 1 << (*(byte *)(param_9 + 0x13) & 3)) != 0) {
    if ((puVar1[0xae] == '\0') && (puVar1[0x3ec] != '\x04')) {
      iVar3 = *(int *)(param_9 + 0xe0);
      uVar2 = 1;
    }
    else {
      iVar3 = *(int *)(param_9 + 0xe4);
      uVar2 = 0x44;
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                (float *)(param_9 + 0x114),puVar1,param_9,in_r7,in_r8,in_r9,in_r10);
    zz_00097b4_(iVar3,uVar2);
  }
  return;
}



// ==== 8017ad60  FUN_8017ad60 ====

void FUN_8017ad60(void)

{
  if (PTR_DAT_80433930[1] == '\0') {
    PTR_DAT_80433930[1] = 1;
    zz_002a5f4_(0,0,0,0);
    DAT_80436354 = (char *)(DAT_80436238 + 0xcb6c00);
    gnt4_memset(DAT_80436354,0,0x4628);
  }
  *(undefined4 *)(DAT_80436354 + 0x14) = (&DAT_803c71fc)[*(int *)(DAT_80436354 + 0x3c) * 8];
  *(undefined4 *)(DAT_80436354 + 0x18) = (&DAT_803c7204)[*(int *)(DAT_80436354 + 0x3c) * 8];
  *(uint *)(DAT_80436354 + 0x1c) =
       *(uint *)(DAT_80436354 + 0x18) | (&DAT_803c720c)[*(int *)(DAT_80436354 + 0x3c) * 8];
  zz_018258c_();
  (*(code *)(&PTR_FUN_80352dc0)[*DAT_80436354])();
  return;
}



// ==== 8017ae40  FUN_8017ae40 ====

void FUN_8017ae40(void)

{
  (*(code *)(&PTR_FUN_80352dec)[*(char *)(DAT_80436354 + 1)])();
  zz_0181dd8_();
  return;
}



// ==== 8017ae84  FUN_8017ae84 ====

void FUN_8017ae84(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,int param_11,int param_12,int param_13,
                 undefined4 param_14,int param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  undefined8 uVar10;
  
  *(undefined1 *)(DAT_80436354 + 1) = 1;
  *(undefined1 *)(DAT_80436354 + 2) = 0;
  zz_0181a08_();
  *(undefined4 *)(DAT_80436354 + 0x78) = 300;
  *(undefined4 *)(DAT_80436354 + 0x74) = 300;
  strcpy((char *)(DAT_80436354 + 0xa4),&DAT_8043ae48);
  iVar8 = 0;
  iVar9 = 5;
  do {
    iVar5 = iVar8 + 0xce;
    iVar4 = iVar8 + 0xd0;
    *(undefined2 *)(DAT_80436354 + iVar8 + 0xcc) = 0xffff;
    iVar6 = DAT_80436354;
    iVar3 = iVar8 + 0xd2;
    iVar2 = iVar8 + 0xd4;
    iVar1 = iVar8 + 0xd6;
    iVar8 = iVar8 + 0xc;
    *(undefined2 *)(DAT_80436354 + iVar5) = 0xffff;
    iVar5 = DAT_80436354;
    *(undefined2 *)(DAT_80436354 + iVar4) = 0xffff;
    iVar4 = DAT_80436354;
    *(undefined2 *)(DAT_80436354 + iVar3) = 0xffff;
    *(undefined2 *)(DAT_80436354 + iVar2) = 0xffff;
    *(undefined2 *)(DAT_80436354 + iVar1) = 0xffff;
    iVar9 = iVar9 + -1;
  } while (iVar9 != 0);
  uVar7 = 0xffffffff;
  *(undefined4 *)(DAT_80436354 + 0x9c4) = 0;
  while ((&PTR_DAT_80358be4)[*(int *)(DAT_80436354 + 0x9c4) * 7] != (undefined *)0x0) {
    iVar4 = *(int *)(DAT_80436354 + 0x9c4);
    *(int *)(DAT_80436354 + 0x9c4) = iVar4 + 1;
  }
  uVar10 = FUN_80181e78();
  zz_0181cac_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,-1,extraout_r4,iVar4,
              iVar5,iVar6,uVar7,iVar8,param_16);
  return;
}



// ==== 8017af94  FUN_8017af94 ====

void FUN_8017af94(void)

{
  char cVar1;
  int iVar2;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
    zz_0027aac_(0xe0e0e000,0x20,0);
  }
  iVar2 = zz_0027adc_();
  if (iVar2 == 0) {
    *(undefined1 *)(DAT_80436354 + 1) = 2;
    *(undefined1 *)(DAT_80436354 + 2) = 0;
  }
  return;
}



// ==== 8017b014  FUN_8017b014 ====

void FUN_8017b014(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  
  cVar1 = DAT_80436354[2];
  if (cVar1 != '\x01') {
    if (('\0' < cVar1) || (cVar1 < '\0')) goto LAB_8017b0ec;
    DAT_80436354[2] = cVar1 + '\x01';
    DAT_80436354[3] = 0;
  }
  iVar3 = zz_01818b4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  if (iVar3 == 1) {
    return;
  }
  if ((iVar3 < 1) && (-1 < iVar3)) {
    *DAT_80436354 = 1;
    DAT_80436354[1] = 0;
    DAT_80436354[2] = 0;
    uVar4 = zz_017b10c_();
    uVar2 = countLeadingZeros(uVar4);
    *(short *)(DAT_80436354 + 0x28) = (short)(uVar2 >> 5);
    *(undefined4 *)(DAT_80436354 + 0x40) = 0;
    *(undefined4 *)(DAT_80436354 + 100) = *(undefined4 *)(DAT_80436354 + 0x60);
  }
  else {
    *DAT_80436354 = 2;
    DAT_80436354[1] = 0;
    *(undefined4 *)(DAT_80436354 + 0x40) = 1;
  }
LAB_8017b0ec:
  zz_0181c78_();
  glxSwapWaitDrawDone_void_();
  zz_007fd5c_();
  zz_0181a08_();
  return;
}



// ==== 8017b10c  zz_017b10c_ ====

undefined4 zz_017b10c_(void)

{
  if (*(int *)(DAT_80436354 + 0x20) == 0x65) {
    return 0;
  }
  return 1;
}



// ==== 8017b128  FUN_8017b128 ====

void FUN_8017b128(void)

{
  char cVar1;
  int iVar2;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 == '\x01') {
    iVar2 = zz_0027adc_();
    if (iVar2 == 0) {
      zz_0181c78_();
      glxSwapWaitDrawDone_void_();
      zz_007fd5c_();
      *PTR_DAT_80433930 = 2;
      PTR_DAT_80433930[1] = 0;
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
    zz_0027aac_(0,0x20,1);
  }
  return;
}



// ==== 8017b1b4  FUN_8017b1b4 ====

void FUN_8017b1b4(void)

{
  (*(code *)(&PTR_FUN_80352dfc)[*(char *)(DAT_80436354 + 1)])();
  zz_0181dd8_();
  return;
}



// ==== 8017b1f8  FUN_8017b1f8 ====

void FUN_8017b1f8(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  
  iVar2 = DAT_80436354;
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
    zz_0181cac_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,iVar2,param_11,
                param_12,param_13,param_14,param_15,param_16);
  }
  iVar2 = zz_000a3c4_();
  if (iVar2 == 0) {
    *(undefined1 *)(DAT_80436354 + 1) = 1;
    *(undefined1 *)(DAT_80436354 + 2) = 0;
  }
  return;
}



// ==== 8017b26c  FUN_8017b26c ====

void FUN_8017b26c(void)

{
  char cVar1;
  int iVar2;
  short sVar3;
  uint uVar4;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 == '\x02') {
    uVar4 = 3;
    iVar2 = (int)*(short *)(DAT_80436354 + 0x24);
    if (1 < *(uint *)(DAT_80436354 + 0x68)) {
      uVar4 = 7;
    }
    if ((*(uint *)(DAT_80436354 + 0x18) & 0x100) == 0) {
      if ((*(uint *)(DAT_80436354 + 0x18) & 0x200) == 0) {
        if ((*(uint *)(DAT_80436354 + 0x1c) & 0x40004) == 0) {
          if ((*(uint *)(DAT_80436354 + 0x1c) & 0x80008) == 0) goto LAB_8017b47c;
          do {
            iVar2 = iVar2 + -1;
            if (iVar2 < 0) {
              iVar2 = 5;
            }
          } while ((uVar4 & 1 << iVar2) == 0);
        }
        else {
          do {
            iVar2 = iVar2 + 1;
            if (5 < iVar2) {
              iVar2 = 0;
            }
          } while ((uVar4 & 1 << iVar2) == 0);
        }
        *(short *)(DAT_80436354 + 0x24) = (short)iVar2;
        zz_0181814_();
      }
      else {
        *(undefined1 *)(DAT_80436354 + 1) = 4;
        *(undefined1 *)(DAT_80436354 + 2) = 0;
        zz_0181864_();
      }
    }
    else {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
      *(undefined2 *)(DAT_80436354 + 8) = 0x1e;
      *(int *)(DAT_80436354 + 0x40) = iVar2;
      zz_018183c_();
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(DAT_80436354 + 2) = 1;
      *(undefined2 *)(DAT_80436354 + 8) = 0x10;
      *(short *)(DAT_80436354 + 0x24) = (short)*(undefined4 *)(DAT_80436354 + 0x40);
      *(undefined4 *)(DAT_80436354 + 0x10) = 0;
      zz_01d2078_();
    }
    else if (cVar1 < '\0') goto LAB_8017b47c;
    sVar3 = *(short *)(DAT_80436354 + 8) + -1;
    *(short *)(DAT_80436354 + 8) = sVar3;
    if (sVar3 < 1) {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
    }
  }
  else if (cVar1 == '\x04') {
    iVar2 = zz_0027adc_();
    if (iVar2 == 0) {
      *(undefined1 *)(DAT_80436354 + 1) = 3;
    }
  }
  else if ((cVar1 < '\x04') &&
          (sVar3 = *(short *)(DAT_80436354 + 8) + -1, *(short *)(DAT_80436354 + 8) = sVar3,
          sVar3 < 1)) {
    iVar2 = *(int *)(DAT_80436354 + 0x40);
    if ((iVar2 == 2) || (((iVar2 < 2 && (0 < iVar2)) && (*(int *)(DAT_80436354 + 0x68) != 0)))) {
      *(undefined1 *)(DAT_80436354 + 1) = 2;
      *(undefined1 *)(DAT_80436354 + 2) = 0;
    }
    else {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
      zz_0027aac_(0,0x20,1);
    }
  }
LAB_8017b47c:
  if (((*(char *)(DAT_80436354 + 1) == '\x01') && ('\x02' < *(char *)(DAT_80436354 + 2))) &&
     (iVar2 = *(int *)(DAT_80436354 + 0x10) + 1, *(int *)(DAT_80436354 + 0x10) = iVar2, 0x1f < iVar2
     )) {
    *(undefined4 *)(DAT_80436354 + 0x10) = 0;
  }
  return;
}



// ==== 8017b4cc  FUN_8017b4cc ====

void FUN_8017b4cc(void)

{
  char cVar1;
  int iVar2;
  int iVar3;
  short sVar4;
  int iVar5;
  
  iVar2 = zz_0181a74_();
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 == '\x02') {
    sVar4 = *(short *)(DAT_80436354 + 8) + -1;
    *(short *)(DAT_80436354 + 8) = sVar4;
    if (sVar4 < 1) {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
      zz_0027aac_(0,0x20,1);
    }
  }
  else if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      *(undefined1 *)(DAT_80436354 + 2) = 1;
      *(short *)(DAT_80436354 + 0x26) = (short)iVar2 + -1;
      *(undefined4 *)(DAT_80436354 + 0x10) = 0;
      zz_01d2248_();
    }
    else if (cVar1 < '\0') goto LAB_8017b658;
    if ((*(uint *)(DAT_80436354 + 0x18) & 0x100) == 0) {
      if ((*(uint *)(DAT_80436354 + 0x18) & 0x200) == 0) {
        iVar5 = (int)*(short *)(DAT_80436354 + 0x26);
        if ((*(uint *)(DAT_80436354 + 0x1c) & 0x40004) == 0) {
          if ((*(uint *)(DAT_80436354 + 0x1c) & 0x80008) == 0) goto LAB_8017b658;
          iVar3 = iVar5 + -1;
          if (iVar3 < 0) {
            iVar3 = 0;
          }
        }
        else {
          iVar3 = iVar5 + 1;
          if (iVar2 + -1 < iVar5 + 1) {
            iVar3 = iVar2 + -1;
          }
        }
        if (iVar5 != iVar3) {
          *(short *)(DAT_80436354 + 0x26) = (short)iVar3;
          zz_0181814_();
        }
      }
      else {
        *(undefined1 *)(DAT_80436354 + 1) = 1;
        *(undefined1 *)(DAT_80436354 + 2) = 2;
        *(undefined4 *)(DAT_80436354 + 0x10) = 0;
        zz_0181864_();
      }
    }
    else {
      *(char *)(DAT_80436354 + 2) = *(char *)(DAT_80436354 + 2) + '\x01';
      *(undefined2 *)(DAT_80436354 + 8) = 0x1e;
      *(int *)(DAT_80436354 + 100) = (int)*(short *)(DAT_80436354 + 0x26);
      zz_018183c_();
    }
  }
  else if ((cVar1 < '\x04') && (iVar2 = zz_0027adc_(), iVar2 == 0)) {
    *(undefined1 *)(DAT_80436354 + 1) = 3;
  }
LAB_8017b658:
  if (((*(char *)(DAT_80436354 + 1) == '\x02') && ('\x01' < *(char *)(DAT_80436354 + 2))) &&
     (iVar2 = *(int *)(DAT_80436354 + 0x10) + 1, *(int *)(DAT_80436354 + 0x10) = iVar2, 0x1f < iVar2
     )) {
    *(undefined4 *)(DAT_80436354 + 0x10) = 0;
  }
  return;
}



// ==== 8017b6ac  FUN_8017b6ac ====

void FUN_8017b6ac(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  iVar1 = *(int *)(DAT_80436354 + 0x40);
  if (iVar1 == 1) {
    *DAT_80436354 = 2;
    DAT_80436354[1] = 0;
    *(undefined4 *)(DAT_80436354 + 0x48) = 0;
  }
  else if (iVar1 < 1) {
    if (-1 < iVar1) {
      if (*(int *)(DAT_80436354 + 0x48) != 0) {
        *(undefined4 *)(DAT_80436354 + 0x48) = 0;
        *(undefined2 *)(DAT_80436354 + 0x28) = 0;
      }
      if (*(short *)(DAT_80436354 + 0x28) == 0) {
        *DAT_80436354 = 2;
        DAT_80436354[1] = 0;
      }
      else {
        *DAT_80436354 = 3;
        DAT_80436354[1] = 0;
        DAT_80436354[2] = 0;
        *(undefined4 *)(DAT_80436354 + 100) = *(undefined4 *)(DAT_80436354 + 0x60);
        *(undefined4 *)(DAT_80436354 + 0x44) = 0;
        zz_0096d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,
                    DAT_80436354 + 0xa4,0,in_r6,in_r7,in_r8,in_r9,in_r10);
      }
    }
  }
  else if (iVar1 < 3) {
    *DAT_80436354 = 3;
    DAT_80436354[1] = 0;
    DAT_80436354[2] = 0;
    *(undefined4 *)(DAT_80436354 + 0x5c) = 0;
    *(undefined4 *)(DAT_80436354 + 0x58) = 1;
    *(undefined4 *)(DAT_80436354 + 0x54) = 0;
    *(uint *)(DAT_80436354 + 0x4624) = *(uint *)(DAT_80436354 + 0x4624) | 0x1ff6;
  }
  zz_0181c78_();
  glxSwapWaitDrawDone_void_();
  zz_007fd5c_();
  return;
}



// ==== 8017b7f4  FUN_8017b7f4 ====

void FUN_8017b7f4(void)

{
  char cVar1;
  int iVar2;
  
  cVar1 = *(char *)(DAT_80436354 + 2);
  if (cVar1 == '\x01') {
    iVar2 = zz_0027adc_();
    if (iVar2 == 0) {
      zz_0181c78_();
      glxSwapWaitDrawDone_void_();
      zz_007fd5c_();
      *PTR_DAT_80433930 = 2;
      PTR_DAT_80433930[1] = 0;
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    *(char *)(DAT_80436354 + 2) = cVar1 + '\x01';
    zz_0027aac_(0,0x20,1);
  }
  return;
}



// ==== 8017b880  FUN_8017b880 ====

void FUN_8017b880(void)

{
  (*(code *)(&PTR_FUN_80352e10)[*(char *)(DAT_80436354 + 1)])();
  return;
}



// ==== 8017b8c0  FUN_8017b8c0 ====

void FUN_8017b8c0(void)

{
  int iVar1;
  
  iVar1 = zz_017f344_(0x629,-1);
  if (iVar1 == 0) {
    *(undefined4 *)(DAT_80436354 + 0x78) = 300;
  }
  else {
    *(undefined4 *)(DAT_80436354 + 0x78) = 500;
  }
  *(undefined4 *)(DAT_80436354 + 0x74) = *(undefined4 *)(DAT_80436354 + 0x78);
  *(undefined4 *)(DAT_80436354 + 0x120) = 10;
  *(undefined4 *)(DAT_80436354 + 0x11c) = 10;
  *(undefined4 *)(DAT_80436354 + 0x118) = 10;
  *(undefined4 *)(DAT_80436354 + 0x124) = 0;
  *(undefined4 *)(DAT_80436354 + 0x114) = 0x400;
  *(undefined4 *)(DAT_80436354 + 0x6c) = 0;
  *(undefined4 *)(DAT_80436354 + 0x90) = 0;
  *(undefined4 *)(DAT_80436354 + 0x8c) = 1;
  *(undefined4 *)(DAT_80436354 + 0x50) = 0;
  *(undefined4 *)(DAT_80436354 + 0x38) = 0;
  DAT_803bfe20 = 0;
  *(undefined1 *)(DAT_80436220 + 0x2174) = 0;
  gnt4_memset((void *)(DAT_80436354 + 0x94),0,0x10);
  gnt4_memset((void *)(DAT_80436354 + 0xa34),0,0x800);
  gnt4_memset((void *)(DAT_80436354 + 0x1234),0,0x80);
  gnt4_memset((void *)(DAT_80436354 + 0x130),0,0x10);
  gnt4_memset((void *)(DAT_80436354 + 0x1434),0,0xd8);
  *(undefined4 *)(DAT_80436354 + 0x44) = 1;
  zz_017e5a0_();
  zz_017ee94_(0);
  *(undefined1 *)(DAT_80436354 + 1) = 1;
  *(undefined1 *)(DAT_80436354 + 2) = 0;
  zz_0027c1c_();
  return;
}



// ==== 8017ba20  FUN_8017ba20 ====

void FUN_8017ba20(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,int param_11,uint param_12,uint param_13,
                 undefined4 ***param_14,undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  uint uVar2;
  short sVar3;
  char cVar4;
  uint uVar5;
  undefined8 uVar6;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  
  uVar5 = DAT_80436354;
  bVar1 = *(byte *)(DAT_80436354 + 2);
  uVar2 = (uint)bVar1;
  if (bVar1 == 1) {
    sVar3 = *(short *)(DAT_80436354 + 8) + -1;
    *(short *)(DAT_80436354 + 8) = sVar3;
    if ((0 < sVar3) && (uVar2 = zz_01b79a4_(0), uVar2 == 0)) {
      cVar4 = zz_01b7968_(0);
      uVar2 = 0;
      if ((cVar4 == '\0') || (uVar2 = DAT_80436354, (*(uint *)(DAT_80436354 + 0x18) & 0x1000) == 0))
      goto LAB_8017bb5c;
    }
    param_13 = DAT_80436354;
    param_11 = 1;
    param_12 = (uint)*(byte *)(DAT_80436354 + 2);
    *(byte *)(DAT_80436354 + 2) = *(byte *)(DAT_80436354 + 2) + 1;
    zz_0027aac_(0,0x20,1);
    uVar6 = zz_01b7928_(0,0x20);
    uVar2 = (uint)((ulonglong)uVar6 >> 0x20);
    uVar5 = (uint)uVar6;
    param_1 = extraout_f1_00;
  }
  else if ((char)bVar1 < '\x01') {
    if (-1 < (char)bVar1) {
      *(byte *)(DAT_80436354 + 2) = bVar1 + 1;
      uVar6 = zz_008c3a0_(0);
      *(undefined2 *)(DAT_80436354 + 8) = 0x1518;
      uVar6 = zz_01b7304_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,
                          DAT_80436238 + 0x208c00);
      param_11 = 0;
      uVar6 = zz_01b757c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,
                          param_12,param_13,param_14,param_15,param_16);
      uVar2 = (uint)((ulonglong)uVar6 >> 0x20);
      uVar5 = (uint)uVar6;
      param_1 = extraout_f1;
    }
  }
  else if ((((char)bVar1 < '\x03') && (uVar2 = zz_0027adc_(), uVar2 == 0)) &&
          (uVar2 = zz_0018f5c_(), uVar2 == 0)) {
    *(undefined1 *)(DAT_80436354 + 1) = 2;
    *(undefined1 *)(DAT_80436354 + 2) = 0;
    zz_01b74a8_(0);
    zz_008c3a0_(4);
    return;
  }
LAB_8017bb5c:
  zz_01b7b98_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,uVar2,uVar5,param_11,
              param_12,param_13,param_14,param_15,param_16);
  zz_008c0dc_(FUN_801b7bf0);
  return;
}



// ==== 8017bb7c  zz_017bb7c_ ====

undefined4 zz_017bb7c_(void)

{
  ushort uVar1;
  ushort uVar2;
  short sVar3;
  ushort *puVar4;
  ushort *puVar5;
  
  puVar4 = *(ushort **)(DAT_80436354 + 0xa28);
  puVar5 = puVar4;
  if (*(short *)(DAT_80436354 + 8) != 0) {
    sVar3 = *(short *)(DAT_80436354 + 8) + -1;
    *(short *)(DAT_80436354 + 8) = sVar3;
    if (0 < sVar3) {
      return 0;
    }
    uVar1 = *puVar4;
    puVar5 = puVar4 + 1;
    if (uVar1 == 0) {
      return 1;
    }
    if ((uVar1 & 0x10) == 0) {
      uVar2 = *puVar5;
      puVar5 = puVar4 + 2;
      *(char *)(DAT_80436354 + (uint)uVar1 + 0xa0c) = (char)uVar2;
    }
    else {
      zz_00ea170_(0xf,0,-1,uVar1 & 0xf);
    }
  }
  *(ushort *)(DAT_80436354 + 8) = *puVar5;
  *(ushort **)(DAT_80436354 + 0xa28) = puVar5 + 1;
  return 0;
}



