// ==== 80031160  FUN_80031160 ====

/* WARNING: Removing unreachable block (ram,0x80031468) */
/* WARNING: Removing unreachable block (ram,0x80031460) */
/* WARNING: Removing unreachable block (ram,0x80031458) */
/* WARNING: Removing unreachable block (ram,0x800312c0) */
/* WARNING: Removing unreachable block (ram,0x80031180) */
/* WARNING: Removing unreachable block (ram,0x80031178) */
/* WARNING: Removing unreachable block (ram,0x80031170) */

uint FUN_80031160(int param_1,int param_2)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  byte bVar4;
  int iVar5;
  int *piVar6;
  int iVar7;
  char *pcVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  float afStack_a8 [3];
  int local_9c [6];
  float local_84;
  undefined4 local_80;
  undefined4 local_7c;
  float local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  
  dVar11 = (double)FLOAT_80436f68;
  piVar6 = local_9c;
  local_9c[0] = 0;
  pcVar8 = &DAT_802cffc8;
  local_9c[1] = 0;
  iVar3 = 0;
  iVar5 = 0;
  local_9c[2] = 0;
  local_9c[5] = 0;
  local_9c[3] = -1;
  local_9c[4] = -1;
  local_84 = *(float *)(param_2 + 0x34);
  local_80 = *(undefined4 *)(param_2 + 0x38);
  local_7c = *(undefined4 *)(param_2 + 0x3c);
  local_78 = *(float *)(param_2 + 0x40);
  local_74 = *(undefined4 *)(param_2 + 0x44);
  local_70 = *(undefined4 *)(param_2 + 0x48);
  local_6c = *(undefined4 *)(param_2 + 0xc);
  local_68 = *(undefined4 *)(param_2 + 0x10);
  local_64 = *(undefined4 *)(param_2 + 0x14);
  iVar7 = param_1;
  do {
    gnt4_PSVECSubtract_bl((float *)(param_1 + *pcVar8 * 0xc + 0x30),&local_84,afStack_a8);
    dVar9 = gnt4_PSQUATDotProduct_bl(afStack_a8,(float *)(iVar7 + 0x90));
    bVar4 = dVar11 <= dVar9;
    gnt4_PSVECSubtract_bl((float *)(param_1 + *pcVar8 * 0xc + 0x30),&local_78,afStack_a8);
    dVar10 = gnt4_PSQUATDotProduct_bl(afStack_a8,(float *)(iVar7 + 0x90));
    if (dVar11 <= dVar10) {
      bVar4 = bVar4 | 2;
    }
    if (bVar4 == 2) {
      gnt4_PSVECSubtract_bl(&local_84,&local_78,afStack_a8);
      dVar10 = gnt4_PSQUATDotProduct_bl(afStack_a8,(float *)(iVar7 + 0x90));
      if (((double)FLOAT_80436f68 == dVar10) || ((double)FLOAT_80436fcc == dVar10)) {
        gnt4_PSQUATScale_bl(dVar9,(float *)(iVar7 + 0x90),afStack_a8);
      }
      else {
        gnt4_PSQUATScale_bl((double)(float)(dVar9 / dVar10),afStack_a8,afStack_a8);
      }
      gnt4_PSVECAdd_bl(&local_84,afStack_a8,&local_84);
      local_9c[4] = iVar5;
    }
    else if (bVar4 < 2) {
      if (bVar4 == 0) {
        iVar3 = iVar3 + 1;
        *piVar6 = iVar5;
        piVar6 = piVar6 + 1;
        if (3 < iVar3) {
          return 0;
        }
      }
      else {
        gnt4_PSVECSubtract_bl(&local_78,&local_84,afStack_a8);
        dVar9 = gnt4_PSQUATDotProduct_bl(afStack_a8,(float *)(iVar7 + 0x90));
        if (((double)FLOAT_80436f68 == dVar9) || ((double)FLOAT_80436fcc == dVar9)) {
          gnt4_PSQUATScale_bl(dVar10,(float *)(iVar7 + 0x90),afStack_a8);
        }
        else {
          gnt4_PSQUATScale_bl((double)(float)(dVar10 / dVar9),afStack_a8,afStack_a8);
        }
        gnt4_PSVECAdd_bl(&local_78,afStack_a8,&local_78);
        local_9c[3] = iVar5;
      }
    }
    iVar5 = iVar5 + 1;
    iVar7 = iVar7 + 0x18;
    pcVar8 = pcVar8 + 4;
  } while (iVar5 < 6);
  if (iVar3 == 2) {
    uVar1 = FUN_80031778(param_1,param_2,local_9c);
    return uVar1;
  }
  if (iVar3 < 2) {
    if (iVar3 == 0) {
      uVar1 = FUN_80031484(param_1,param_2,&local_84,local_9c + 3);
      return uVar1;
    }
    if (-1 < iVar3) {
      bVar2 = FUN_80031634(param_1,param_2,&local_84,local_9c);
      return (uint)bVar2;
    }
  }
  else if (iVar3 < 4) {
    uVar1 = FUN_800318b4(param_1,param_2,local_9c);
    return uVar1;
  }
  return 0;
}



// ==== 80031484  FUN_80031484 ====

/* WARNING: Removing unreachable block (ram,0x80031618) */
/* WARNING: Removing unreachable block (ram,0x80031494) */

undefined4 FUN_80031484(int param_1,int param_2,undefined4 *param_3,int *param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  double dVar6;
  double dVar7;
  float afStack_38 [4];
  
  if ((*param_4 == -1) && (param_4[1] == -1)) {
    dVar7 = (double)FLOAT_80436fc8;
    pcVar5 = &DAT_802cffc8;
    iVar2 = 0;
    iVar3 = 0;
    iVar4 = param_1;
    do {
      gnt4_PSVECSubtract_bl
                ((float *)(param_2 + 0xc),(float *)(param_1 + *pcVar5 * 0xc + 0x30),afStack_38);
      dVar6 = gnt4_PSQUATDotProduct_bl(afStack_38,(float *)(iVar4 + 0x90));
      if ((float)ABS(dVar6) < (float)ABS(dVar7)) {
        iVar2 = iVar3;
        dVar7 = dVar6;
      }
      iVar3 = iVar3 + 1;
      iVar4 = iVar4 + 0x18;
      pcVar5 = pcVar5 + 4;
    } while (iVar3 < 6);
    gnt4_PSQUATScale_bl(dVar7,(float *)(param_1 + iVar2 * 0x18 + 0x90),afStack_38);
    gnt4_PSVECSubtract_bl((float *)(param_2 + 0xc),afStack_38,(float *)&DAT_803b0720);
  }
  else {
    if ((*param_4 == -1) || (param_4[1] != -1)) {
      DAT_803b0720 = *param_3;
      uVar1 = param_3[1];
      DAT_803b0728 = param_3[2];
      DAT_803b0724 = uVar1;
      *(undefined4 *)(param_2 + 0x40) = DAT_803b0720;
      *(undefined4 *)(param_2 + 0x44) = uVar1;
      *(undefined4 *)(param_2 + 0x48) = param_3[2];
    }
    else {
      DAT_803b0720 = param_3[3];
      uVar1 = param_3[4];
      DAT_803b0728 = param_3[5];
      DAT_803b0724 = uVar1;
      *(undefined4 *)(param_2 + 0x34) = DAT_803b0720;
      *(undefined4 *)(param_2 + 0x38) = uVar1;
      *(undefined4 *)(param_2 + 0x3c) = param_3[5];
    }
    gnt4_PSVECSubtract_bl
              ((float *)(param_2 + 0x40),(float *)(param_2 + 0x34),(float *)(param_2 + 0x4c));
    gnt4_PSVECSubtract_bl
              ((float *)(param_2 + 0x34),(float *)(param_2 + 0x40),(float *)(param_2 + 0x58));
    gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,(float *)(param_2 + 0x4c),afStack_38);
    gnt4_PSVECAdd_bl((float *)(param_2 + 0x34),afStack_38,(float *)(param_2 + 0xc));
  }
  return 1;
}



// ==== 80031634  FUN_80031634 ====

/* WARNING: Removing unreachable block (ram,0x8003175c) */
/* WARNING: Removing unreachable block (ram,0x80031644) */

bool FUN_80031634(int param_1,int param_2,float *param_3,int *param_4)

{
  bool bVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  float afStack_38 [5];
  
  gnt4_PSVECSubtract_bl
            (param_3,(float *)(param_1 + (char)(&DAT_802cffc8)[*param_4 * 4] * 0xc + 0x30),
             afStack_38);
  dVar3 = gnt4_PSQUATDotProduct_bl(afStack_38,(float *)(param_1 + *param_4 * 0x18 + 0x90));
  dVar4 = (double)(float)ABS(dVar3);
  gnt4_PSVECSubtract_bl
            (param_3 + 3,(float *)(param_1 + (char)(&DAT_802cffc8)[*param_4 * 4] * 0xc + 0x30),
             afStack_38);
  dVar3 = gnt4_PSQUATDotProduct_bl(afStack_38,(float *)(param_1 + *param_4 * 0x18 + 0x90));
  dVar2 = (double)(float)ABS(dVar3);
  dVar3 = dVar4;
  if (dVar2 < dVar4) {
    dVar3 = dVar2;
  }
  bVar1 = dVar3 <= (double)*(float *)(param_2 + 0x30);
  if (bVar1) {
    gnt4_PSQUATScale_bl(dVar3,(float *)(param_1 + *param_4 * 0x18 + 0x90),afStack_38);
    gnt4_PSVECSubtract_bl(param_3 + (uint)(dVar2 < dVar4) * 3,afStack_38,(float *)&DAT_803b0720);
  }
  return bVar1;
}



// ==== 80031778  FUN_80031778 ====

undefined4 FUN_80031778(int param_1,int param_2,int *param_3)

{
  int iVar1;
  double dVar2;
  int local_88;
  int local_84;
  float afStack_80 [3];
  float local_74;
  undefined4 local_70;
  undefined4 local_6c;
  float afStack_68 [3];
  float afStack_5c [21];
  
  iVar1 = zz_0039938_(param_3,(int)&local_88);
  if (iVar1 != 0) {
    zz_0038b34_((float *)(param_1 + local_88 * 0xc + 0x30),
                (float *)(param_1 + local_84 * 0xc + 0x30),afStack_5c);
    iVar1 = zz_0038c00_(afStack_5c,(float *)(param_2 + 0x34),&local_74);
    if (iVar1 != 0) {
      gnt4_PSVECSubtract_bl(&local_74,afStack_68,afStack_80);
      dVar2 = gnt4_PSVECMag_bl(afStack_80);
      if (dVar2 <= (double)*(float *)(param_2 + 0x30)) {
        *(float *)(param_2 + 0x40) = local_74;
        *(undefined4 *)(param_2 + 0x44) = local_70;
        *(undefined4 *)(param_2 + 0x48) = local_6c;
        gnt4_PSVECSubtract_bl
                  ((float *)(param_2 + 0x40),(float *)(param_2 + 0x34),(float *)(param_2 + 0x4c));
        gnt4_PSVECSubtract_bl
                  ((float *)(param_2 + 0x34),(float *)(param_2 + 0x40),(float *)(param_2 + 0x58));
        gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,(float *)(param_2 + 0x4c),afStack_80);
        gnt4_PSVECAdd_bl((float *)(param_2 + 0x34),afStack_80,(float *)(param_2 + 0xc));
        DAT_803b0720 = local_74;
        DAT_803b0724 = local_70;
        DAT_803b0728 = local_6c;
        return 1;
      }
    }
  }
  return 0;
}



// ==== 800318b4  FUN_800318b4 ====

undefined4 FUN_800318b4(int param_1,int param_2,int *param_3)

{
  int iVar1;
  double dVar2;
  int local_48;
  float local_44;
  undefined4 local_40;
  undefined4 local_3c;
  float afStack_38 [3];
  float afStack_2c [3];
  float afStack_20 [6];
  
  iVar1 = zz_0039a48_(param_3,&local_48);
  if (iVar1 != 0) {
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + local_48 * 0xc + 0x30),(float *)(param_2 + 0x34),afStack_20);
    gnt4_PSVECNormalize_bl((float *)(param_2 + 0x4c),afStack_2c);
    dVar2 = gnt4_PSQUATDotProduct_bl(afStack_20,afStack_2c);
    gnt4_PSQUATScale_bl(dVar2,afStack_2c,&local_44);
    gnt4_PSVECAdd_bl(&local_44,(float *)(param_2 + 0x34),&local_44);
    gnt4_PSVECSubtract_bl(&local_44,(float *)(param_2 + 0x34),afStack_20);
    gnt4_PSVECNormalize_bl((float *)(param_2 + 0x4c),afStack_2c);
    dVar2 = gnt4_PSQUATDotProduct_bl(afStack_20,afStack_2c);
    if (dVar2 < (double)FLOAT_80436f68) {
      local_44 = *(float *)(param_2 + 0x34);
      local_40 = *(undefined4 *)(param_2 + 0x38);
      local_3c = *(undefined4 *)(param_2 + 0x3c);
    }
    gnt4_PSVECSubtract_bl(&local_44,(float *)(param_2 + 0x40),afStack_20);
    gnt4_PSVECNormalize_bl((float *)(param_2 + 0x58),afStack_2c);
    dVar2 = gnt4_PSQUATDotProduct_bl(afStack_20,afStack_2c);
    if (dVar2 < (double)FLOAT_80436f68) {
      local_44 = *(float *)(param_2 + 0x40);
      local_40 = *(undefined4 *)(param_2 + 0x44);
      local_3c = *(undefined4 *)(param_2 + 0x48);
    }
    gnt4_PSVECSubtract_bl((float *)(param_1 + local_48 * 0xc + 0x30),&local_44,afStack_38);
    dVar2 = gnt4_PSVECMag_bl(afStack_38);
    if (dVar2 <= (double)*(float *)(param_2 + 0x30)) {
      *(float *)(param_2 + 0x40) = local_44;
      *(undefined4 *)(param_2 + 0x44) = local_40;
      *(undefined4 *)(param_2 + 0x48) = local_3c;
      gnt4_PSVECSubtract_bl
                ((float *)(param_2 + 0x40),(float *)(param_2 + 0x34),(float *)(param_2 + 0x4c));
      gnt4_PSVECSubtract_bl
                ((float *)(param_2 + 0x34),(float *)(param_2 + 0x40),(float *)(param_2 + 0x58));
      gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,(float *)(param_2 + 0x4c),afStack_20);
      gnt4_PSVECAdd_bl((float *)(param_2 + 0x34),afStack_20,(float *)(param_2 + 0xc));
      iVar1 = param_1 + local_48 * 0xc;
      DAT_803b0720 = *(undefined4 *)(iVar1 + 0x30);
      DAT_803b0724 = *(undefined4 *)(iVar1 + 0x34);
      DAT_803b0728 = *(undefined4 *)(iVar1 + 0x38);
      return 1;
    }
  }
  return 0;
}



// ==== 80031aa8  FUN_80031aa8 ====

/* WARNING: Removing unreachable block (ram,0x80031e34) */
/* WARNING: Removing unreachable block (ram,0x80031e2c) */
/* WARNING: Removing unreachable block (ram,0x80031e24) */
/* WARNING: Removing unreachable block (ram,0x80031d10) */
/* WARNING: Removing unreachable block (ram,0x80031ac8) */
/* WARNING: Removing unreachable block (ram,0x80031ac0) */
/* WARNING: Removing unreachable block (ram,0x80031ab8) */

undefined4 FUN_80031aa8(int param_1,int param_2)

{
  float *pfVar1;
  float *pfVar2;
  uint uVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  int iVar8;
  char *pcVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  float afStack_88 [3];
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  
  dVar12 = (double)FLOAT_80436f68;
  pcVar7 = &DAT_80433688;
  iVar5 = 0;
  do {
    uVar3 = 0;
    iVar6 = 0;
    pfVar2 = (float *)(param_2 + *pcVar7 * 0xc + 0x34);
    local_7c = *pfVar2;
    local_78 = pfVar2[1];
    pfVar1 = (float *)(param_2 + pcVar7[1] * 0xc + 0x34);
    local_74 = pfVar2[2];
    local_70 = *pfVar1;
    local_6c = pfVar1[1];
    local_68 = pfVar1[2];
    iVar8 = param_1;
    pcVar9 = &DAT_802cffc8;
    do {
      gnt4_PSVECSubtract_bl((float *)(param_1 + *pcVar9 * 0xc + 0x30),&local_7c,afStack_88);
      dVar10 = gnt4_PSQUATDotProduct_bl(afStack_88,(float *)(iVar8 + 0x90));
      bVar4 = dVar12 <= dVar10;
      gnt4_PSVECSubtract_bl((float *)(param_1 + *pcVar9 * 0xc + 0x30),&local_70,afStack_88);
      dVar11 = gnt4_PSQUATDotProduct_bl(afStack_88,(float *)(iVar8 + 0x90));
      if (dVar12 <= dVar11) {
        bVar4 = bVar4 | 2;
      }
      if (bVar4 == 0) break;
      if (bVar4 == 2) {
        gnt4_PSVECSubtract_bl(&local_7c,&local_70,afStack_88);
        dVar11 = gnt4_PSQUATDotProduct_bl(afStack_88,(float *)(iVar8 + 0x90));
        if (((double)FLOAT_80436f68 == dVar11) || ((double)FLOAT_80436fcc == dVar11)) {
          gnt4_PSQUATScale_bl(dVar10,(float *)(iVar8 + 0x90),afStack_88);
        }
        else {
          gnt4_PSQUATScale_bl((double)(float)(dVar10 / dVar11),afStack_88,afStack_88);
        }
        gnt4_PSVECAdd_bl(&local_7c,afStack_88,&local_7c);
        uVar3 = uVar3 | 1;
      }
      else if ((bVar4 < 2) && (bVar4 != 0)) {
        gnt4_PSVECSubtract_bl(&local_70,&local_7c,afStack_88);
        dVar10 = gnt4_PSQUATDotProduct_bl(afStack_88,(float *)(iVar8 + 0x90));
        if (((double)FLOAT_80436f68 == dVar10) || ((double)FLOAT_80436fcc == dVar10)) {
          gnt4_PSQUATScale_bl(dVar11,(float *)(iVar8 + 0x90),afStack_88);
        }
        else {
          gnt4_PSQUATScale_bl((double)(float)(dVar11 / dVar10),afStack_88,afStack_88);
        }
        gnt4_PSVECAdd_bl(&local_70,afStack_88,&local_70);
        uVar3 = uVar3 | 2;
      }
      iVar6 = iVar6 + 1;
      iVar8 = iVar8 + 0x18;
      pcVar9 = pcVar9 + 4;
    } while (iVar6 < 6);
    if (iVar6 == 6) {
      if (uVar3 == 2) {
        DAT_803b0720 = local_70;
        DAT_803b0724 = local_6c;
        DAT_803b0728 = local_68;
      }
      else if (uVar3 < 2) {
        if (uVar3 == 0) {
          DAT_803b0720 = *(float *)(param_2 + 0xc);
          DAT_803b0724 = *(float *)(param_2 + 0x10);
          DAT_803b0728 = *(float *)(param_2 + 0x14);
        }
        else {
          DAT_803b0720 = local_7c;
          DAT_803b0724 = local_78;
          DAT_803b0728 = local_74;
        }
      }
      else if (uVar3 < 4) {
        gnt4_PSVECSubtract_bl((float *)(param_2 + 0xc),&local_7c,afStack_88);
        dVar12 = gnt4_PSVECMag_bl(afStack_88);
        gnt4_PSVECSubtract_bl((float *)(param_2 + 0xc),&local_70,afStack_88);
        dVar10 = gnt4_PSVECMag_bl(afStack_88);
        if (dVar10 <= dVar12) {
          DAT_803b0720 = local_70;
          DAT_803b0724 = local_6c;
          DAT_803b0728 = local_68;
        }
        else {
          DAT_803b0720 = local_7c;
          DAT_803b0724 = local_78;
          DAT_803b0728 = local_74;
        }
      }
      return 1;
    }
    iVar5 = iVar5 + 1;
    pcVar7 = pcVar7 + 1;
    if (3 < iVar5) {
      return 0;
    }
  } while( true );
}



// ==== 80031e50  FUN_80031e50 ====

undefined4 FUN_80031e50(int param_1,int param_2)

{
  int iVar1;
  double dVar2;
  float afStack_38 [3];
  float afStack_2c [3];
  float afStack_20 [5];
  
  iVar1 = zz_0038c00_((float *)(param_1 + 0x34),(float *)(param_2 + 0x34),afStack_2c);
  if (iVar1 == 0) {
    DAT_803b0720 = *(undefined4 *)(param_1 + 0xc);
    DAT_803b0724 = *(undefined4 *)(param_1 + 0x10);
    DAT_803b0728 = *(undefined4 *)(param_1 + 0x14);
  }
  else {
    gnt4_PSVECSubtract_bl(afStack_2c,afStack_20,afStack_38);
    dVar2 = gnt4_PSVECMag_bl(afStack_38);
    if ((double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30)) < dVar2) {
      return 0;
    }
    gnt4_PSVECNormalize_bl(afStack_38,afStack_38);
    gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x30),afStack_38,afStack_38);
    gnt4_PSVECAdd_bl(afStack_38,afStack_20,(float *)&DAT_803b0720);
  }
  return 1;
}



// ==== 80031f30  FUN_80031f30 ====

/* WARNING: Removing unreachable block (ram,0x80032250) */
/* WARNING: Removing unreachable block (ram,0x80032248) */
/* WARNING: Removing unreachable block (ram,0x80032240) */
/* WARNING: Removing unreachable block (ram,0x80031f50) */
/* WARNING: Removing unreachable block (ram,0x80031f48) */
/* WARNING: Removing unreachable block (ram,0x80031f40) */

uint FUN_80031f30(int param_1,int param_2)

{
  byte bVar2;
  uint uVar1;
  float *pfVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double in_f30;
  float afStack_c4 [3];
  float afStack_b8 [3];
  float local_ac;
  undefined4 local_a8;
  undefined4 local_a4;
  float afStack_a0 [3];
  float afStack_94 [19];
  
  iVar7 = 0;
  iVar4 = param_2;
  iVar6 = param_2;
  while ((bVar2 = FUN_80039da4((float *)(param_1 + 0x34),(float *)(iVar4 + 0x7c),
                               (float *)(param_2 + 0x4c),afStack_b8), bVar2 == 0 ||
         (uVar1 = zz_0039aec_(afStack_b8,(float *)(iVar6 + 0x34),(float *)(iVar4 + 0x7c)),
         uVar1 == 0))) {
    iVar7 = iVar7 + 1;
    iVar6 = iVar6 + 0x24;
    iVar4 = iVar4 + 0x18;
    if (1 < iVar7) {
      if ((*(ushort *)(*(int *)(*(int *)(param_2 + 4) + 0x28) + 2) & 0x40) == 0) {
        dVar8 = (double)FLOAT_80436f68;
        iVar4 = -1;
        pcVar5 = &DAT_80433688;
        iVar6 = 0;
        do {
          zz_0038b34_((float *)(param_2 + *pcVar5 * 0xc + 0x34),
                      (float *)(param_2 + pcVar5[1] * 0xc + 0x34),afStack_94);
          iVar7 = zz_0038c00_(afStack_94,(float *)(param_1 + 0x34),&local_ac);
          if (iVar7 == 0) {
            DAT_803b0720 = (float)*(undefined4 *)(param_1 + 0xc);
            DAT_803b0724 = *(undefined4 *)(param_1 + 0x10);
            DAT_803b0728 = *(undefined4 *)(param_1 + 0x14);
            return 1;
          }
          dVar9 = gnt4_PSVECSquareDistance_bl(afStack_a0,&local_ac);
          if (dVar8 < dVar9) {
            dVar10 = 1.0 / SQRT(dVar9);
            dVar10 = DOUBLE_80436fd0 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80436fd8);
            dVar10 = DOUBLE_80436fd0 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80436fd8);
            dVar9 = (double)(float)(dVar9 * DOUBLE_80436fd0 * dVar10 *
                                            -(dVar9 * dVar10 * dVar10 - DOUBLE_80436fd8));
          }
          if ((dVar9 < (double)(*(float *)(param_2 + 0x30) + *(float *)(param_1 + 0x30))) &&
             ((iVar4 == -1 || (dVar9 < in_f30)))) {
            gnt4_PSVECSubtract_bl(afStack_a0,&local_ac,afStack_b8);
            dVar10 = gnt4_PSVECSquareMag_bl(afStack_b8);
            iVar4 = iVar6;
            if ((double)FLOAT_80436f68 < dVar10) {
              gnt4_PSVECNormalize_bl(afStack_b8,afStack_b8);
              gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x30),afStack_b8,afStack_b8);
              gnt4_PSVECAdd_bl(&local_ac,afStack_b8,&DAT_803b0720);
              in_f30 = dVar9;
            }
            else {
              DAT_803b0720 = local_ac;
              DAT_803b0724 = local_a8;
              DAT_803b0728 = local_a4;
              in_f30 = dVar9;
            }
          }
          iVar6 = iVar6 + 1;
          pcVar5 = pcVar5 + 1;
        } while (iVar6 < 4);
        uVar1 = (-iVar4 - 1U | iVar4 + 1U) >> 0x1f;
      }
      else {
        uVar1 = 0;
      }
      return uVar1;
    }
  }
  if ((*(ushort *)(*(int *)(*(int *)(param_2 + 4) + 0x28) + 2) & 0x40) != 0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x34),(float *)(param_2 + 0x4c),afStack_c4);
    dVar8 = gnt4_PSQUATDotProduct_bl(afStack_c4,(float *)(param_2 + iVar7 * 0x18 + 0x7c));
    if (dVar8 < (double)FLOAT_80436f68) {
      return 0;
    }
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x34),(float *)(param_2 + 0x4c),afStack_c4);
  pfVar3 = (float *)(param_2 + iVar7 * 0x18 + 0x7c);
  dVar8 = gnt4_PSQUATDotProduct_bl(afStack_c4,pfVar3);
  if (dVar8 < (double)FLOAT_80436f68) {
    dVar8 = -(double)*(float *)(param_2 + 0x30);
  }
  else {
    dVar8 = (double)*(float *)(param_2 + 0x30);
  }
  gnt4_PSQUATScale_bl(dVar8,pfVar3,afStack_c4);
  gnt4_PSVECAdd_bl(afStack_b8,afStack_c4,&DAT_803b0720);
  return 1;
}



// ==== 8003226c  FUN_8003226c ====

undefined4 FUN_8003226c(int param_1,int param_2)

{
  byte bVar2;
  int iVar1;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float afStack_c0 [3];
  float afStack_b4 [3];
  float afStack_a8 [3];
  float afStack_9c [3];
  float local_90;
  undefined4 local_8c;
  undefined4 local_88;
  float afStack_84 [3];
  float afStack_78 [3];
  float local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float afStack_60 [18];
  
  if ((*(ushort *)(*(int *)(*(int *)(param_2 + 4) + 0x28) + 2) & 0x40) != 0) {
    dVar5 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0xc),(float *)(param_1 + 0x18));
    if (dVar5 <= (double)FLOAT_80436f78) {
      gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x48),(float *)(param_2 + 0x30),afStack_9c);
      gnt4_PSVECAdd_bl((float *)(param_2 + 0xc),afStack_9c,afStack_c0);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x34),afStack_c0,afStack_9c);
      dVar5 = gnt4_PSQUATDotProduct_bl(afStack_9c,(float *)(param_2 + 0x30));
      if (dVar5 <= (double)*(float *)(param_1 + 0x30)) {
        return 0;
      }
    }
    else {
      gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x48),(float *)(param_2 + 0x30),afStack_9c);
      gnt4_PSVECAdd_bl((float *)(param_2 + 0xc),afStack_9c,afStack_c0);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x34),afStack_c0,afStack_9c);
      dVar5 = gnt4_PSQUATDotProduct_bl(afStack_9c,(float *)(param_2 + 0x30));
      if (dVar5 <= (double)*(float *)(param_1 + 0x30)) {
        return 0;
      }
    }
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x30),(float *)(param_1 + 100),afStack_9c);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x40),afStack_9c,&local_6c);
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x30),(float *)(param_1 + 0x70),afStack_9c);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x34),afStack_9c,afStack_78);
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x48),(float *)(param_2 + 0x30),afStack_9c);
  gnt4_PSVECAdd_bl((float *)(param_2 + 0xc),afStack_9c,afStack_c0);
  bVar2 = FUN_80039da4(afStack_78,(float *)(param_2 + 0x30),afStack_c0,afStack_b4);
  if (bVar2 != 0) {
    dVar5 = gnt4_PSVECSquareDistance_bl(afStack_b4,afStack_c0);
    if ((double)FLOAT_80436f68 < dVar5) {
      dVar6 = 1.0 / SQRT(dVar5);
      dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
      dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
      dVar5 = (double)(float)(dVar5 * DOUBLE_80436fd0 * dVar6 *
                                      -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8));
    }
    if (dVar5 <= (double)(float)((double)*(float *)(param_2 + 0x4c) +
                                (double)*(float *)(param_1 + 0x30))) {
      if ((double)*(float *)(param_2 + 0x4c) < dVar5) {
        gnt4_PSVECSubtract_bl(afStack_c0,afStack_b4,afStack_9c);
        dVar5 = gnt4_PSVECMag_bl(afStack_9c);
        gnt4_PSQUATScale_bl((double)(float)((double)(float)(dVar5 - (double)*(float *)(param_2 +
                                                                                      0x4c)) / dVar5
                                           ),afStack_9c,afStack_9c);
        gnt4_PSVECAdd_bl(afStack_b4,afStack_9c,afStack_b4);
      }
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x34),(float *)(param_2 + 0xc),afStack_a8);
      dVar5 = gnt4_PSQUATDotProduct_bl(afStack_a8,(float *)(param_2 + 0x30));
      if (dVar5 < (double)FLOAT_80436f68) {
        dVar5 = -(double)*(float *)(param_2 + 0x48);
      }
      else {
        dVar5 = (double)*(float *)(param_2 + 0x48);
      }
      gnt4_PSQUATScale_bl(dVar5,(float *)(param_2 + 0x30),afStack_a8);
      gnt4_PSVECAdd_bl(afStack_b4,afStack_a8,&DAT_803b0720);
      return 1;
    }
  }
  iVar3 = 0;
  iVar4 = param_2;
  do {
    local_90 = *(float *)(iVar4 + 0x50);
    local_8c = *(undefined4 *)(iVar4 + 0x54);
    local_88 = *(undefined4 *)(iVar4 + 0x58);
    gnt4_PSVECSubtract_bl((float *)(param_2 + 0xc),&local_90,afStack_9c);
    gnt4_PSVECAdd_bl((float *)(param_2 + 0xc),afStack_9c,afStack_84);
    zz_0038b34_(&local_90,afStack_84,afStack_60);
    iVar1 = zz_0038c00_((float *)(param_1 + 0x34),afStack_60,afStack_78);
    if (iVar1 != 0) {
      dVar5 = gnt4_PSVECSquareDistance_bl(afStack_78,&local_6c);
      if ((double)FLOAT_80436f68 < dVar5) {
        dVar6 = 1.0 / SQRT(dVar5);
        dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
        dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
        dVar5 = (double)(float)(dVar5 * DOUBLE_80436fd0 * dVar6 *
                                        -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8));
      }
      if (dVar5 <= (double)*(float *)(param_1 + 0x30)) {
        DAT_803b0720 = local_6c;
        DAT_803b0724 = local_68;
        DAT_803b0728 = local_64;
        return 1;
      }
    }
    iVar3 = iVar3 + 1;
    iVar4 = iVar4 + 0xc;
    if (5 < iVar3) {
      return 0;
    }
  } while( true );
}



// ==== 80032630  FUN_80032630 ====

undefined4 FUN_80032630(int param_1,int param_2)

{
  byte bVar2;
  uint uVar1;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  float *pfVar9;
  int iVar10;
  float *pfVar11;
  double dVar12;
  double dVar13;
  float afStack_88 [3];
  float local_7c;
  undefined4 local_78;
  undefined4 local_74;
  float local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  undefined4 local_50;
  float local_4c;
  undefined4 local_48;
  undefined4 local_44;
  
  iVar6 = 0;
  iVar7 = param_2;
  iVar8 = param_2;
  do {
    pfVar9 = (float *)(iVar8 + 0x7c);
    iVar3 = 0;
    iVar10 = param_1;
    do {
      local_70 = *(float *)(iVar10 + 0x34);
      pfVar11 = &local_70;
      local_6c = *(undefined4 *)(iVar10 + 0x38);
      iVar5 = 0;
      local_68 = *(undefined4 *)(iVar10 + 0x3c);
      local_64 = *(undefined4 *)(iVar10 + 0x40);
      local_60 = *(undefined4 *)(iVar10 + 0x44);
      local_5c = *(undefined4 *)(iVar10 + 0x48);
      local_58 = *(undefined4 *)(iVar10 + 0x4c);
      local_54 = *(undefined4 *)(iVar10 + 0x50);
      local_50 = *(undefined4 *)(iVar10 + 0x54);
      local_4c = local_70;
      local_48 = local_6c;
      local_44 = local_68;
      do {
        bVar2 = FUN_80039da4(pfVar11,pfVar9,(float *)(param_2 + 0x4c),&local_7c);
        if ((bVar2 != 0) &&
           (uVar1 = zz_0039aec_(&local_7c,(float *)(iVar7 + 0x34),pfVar9), uVar1 != 0)) {
          if ((*(ushort *)(*(int *)(*(int *)(param_2 + 4) + 0x28) + 2) & 0x40) == 0) {
            DAT_803b0720 = local_7c;
            DAT_803b0724 = local_78;
            DAT_803b0728 = local_74;
            return 1;
          }
          gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0x4c),afStack_88);
          dVar12 = gnt4_PSQUATDotProduct_bl(afStack_88,pfVar9);
          gnt4_PSVECSubtract_bl((float *)(param_1 + 0x18),(float *)(param_2 + 0x4c),afStack_88);
          dVar13 = gnt4_PSQUATDotProduct_bl(afStack_88,pfVar9);
          if (dVar12 < dVar13) {
            DAT_803b0720 = local_7c;
            DAT_803b0724 = local_78;
            DAT_803b0728 = local_74;
            return 1;
          }
        }
        iVar5 = iVar5 + 1;
        pfVar11 = pfVar11 + 3;
      } while (iVar5 < 3);
      iVar3 = iVar3 + 1;
      iVar10 = iVar10 + 0x24;
    } while (iVar3 < 2);
    iVar6 = iVar6 + 1;
    iVar7 = iVar7 + 0x24;
    iVar8 = iVar8 + 0x18;
  } while (iVar6 < 2);
  iVar10 = 0;
  iVar7 = param_2;
  iVar8 = param_1;
  iVar6 = param_1;
  do {
    iVar5 = 0;
    iVar3 = param_2;
    do {
      local_70 = *(float *)(iVar3 + 0x34);
      pfVar9 = &local_70;
      local_6c = *(undefined4 *)(iVar3 + 0x38);
      iVar4 = 0;
      local_68 = *(undefined4 *)(iVar3 + 0x3c);
      local_64 = *(undefined4 *)(iVar3 + 0x40);
      local_60 = *(undefined4 *)(iVar3 + 0x44);
      local_5c = *(undefined4 *)(iVar3 + 0x48);
      local_58 = *(undefined4 *)(iVar3 + 0x4c);
      local_54 = *(undefined4 *)(iVar3 + 0x50);
      local_50 = *(undefined4 *)(iVar3 + 0x54);
      local_4c = local_70;
      local_48 = local_6c;
      local_44 = local_68;
      do {
        bVar2 = FUN_80039da4(pfVar9,(float *)(iVar6 + 0x7c),(float *)(param_1 + 0x4c),&local_7c);
        if ((bVar2 != 0) &&
           (uVar1 = zz_0039aec_(&local_7c,(float *)(iVar8 + 0x34),(float *)(iVar6 + 0x7c)),
           uVar1 != 0)) {
          if ((*(ushort *)(*(int *)(*(int *)(param_2 + 4) + 0x28) + 2) & 0x40) == 0) {
            DAT_803b0720 = local_7c;
            DAT_803b0724 = local_78;
            DAT_803b0728 = local_74;
            return 1;
          }
          gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0x4c),afStack_88);
          dVar12 = gnt4_PSQUATDotProduct_bl(afStack_88,(float *)(iVar7 + 0x7c));
          gnt4_PSVECSubtract_bl((float *)(param_1 + 0x18),(float *)(param_2 + 0x4c),afStack_88);
          dVar13 = gnt4_PSQUATDotProduct_bl(afStack_88,(float *)(iVar7 + 0x7c));
          if (dVar12 < dVar13) {
            DAT_803b0720 = local_7c;
            DAT_803b0724 = local_78;
            DAT_803b0728 = local_74;
            return 1;
          }
        }
        iVar4 = iVar4 + 1;
        pfVar9 = pfVar9 + 3;
      } while (iVar4 < 3);
      iVar5 = iVar5 + 1;
      iVar3 = iVar3 + 0x24;
    } while (iVar5 < 2);
    iVar10 = iVar10 + 1;
    iVar8 = iVar8 + 0x24;
    iVar7 = iVar7 + 0x18;
    iVar6 = iVar6 + 0x18;
    if (1 < iVar10) {
      return 0;
    }
  } while( true );
}



// ==== 80032984  FUN_80032984 ====

/* WARNING: Removing unreachable block (ram,0x80032d88) */
/* WARNING: Removing unreachable block (ram,0x80032d80) */
/* WARNING: Removing unreachable block (ram,0x8003299c) */
/* WARNING: Removing unreachable block (ram,0x80032994) */

undefined4 FUN_80032984(int param_1,int param_2)

{
  byte bVar2;
  uint uVar1;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  float *pfVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  float afStack_a8 [3];
  float afStack_9c [3];
  float afStack_90 [3];
  float local_84;
  undefined4 local_80;
  undefined4 local_7c;
  float local_78;
  undefined4 local_74;
  undefined4 local_70;
  float local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  float local_54;
  undefined4 local_50;
  undefined4 local_4c;
  
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x48),(float *)(param_2 + 0x30),afStack_9c);
  gnt4_PSVECAdd_bl((float *)(param_2 + 0xc),afStack_9c,afStack_a8);
  dVar11 = (double)FLOAT_80436f68;
  iVar4 = 0;
  iVar7 = param_2;
  do {
    local_78 = *(float *)(iVar7 + 0x50);
    local_74 = *(undefined4 *)(iVar7 + 0x54);
    local_70 = *(undefined4 *)(iVar7 + 0x58);
    gnt4_PSVECAdd_bl(&local_78,afStack_9c,&local_78);
    gnt4_PSVECSubtract_bl(afStack_a8,&local_78,&local_84);
    dVar9 = gnt4_PSVECMag_bl(&local_84);
    if (dVar11 < dVar9) {
      gnt4_PSVECNormalize_bl(&local_84,afStack_90);
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x30),afStack_90,afStack_90);
      gnt4_PSVECAdd_bl(&local_84,afStack_90,&local_84);
    }
    gnt4_PSVECAdd_bl(afStack_a8,&local_84,&local_6c);
    iVar3 = 0;
    iVar5 = param_1;
    iVar6 = param_1;
    do {
      bVar2 = FUN_80039da4(&local_78,(float *)(iVar5 + 0x7c),(float *)(param_1 + 0x4c),&local_84);
      if ((bVar2 != 0) &&
         (uVar1 = zz_0039aec_(&local_84,(float *)(iVar6 + 0x34),(float *)(iVar5 + 0x7c)), uVar1 != 0
         )) {
        if ((*(ushort *)(*(int *)(*(int *)(param_2 + 4) + 0x28) + 2) & 0x40) == 0) {
          DAT_803b0720 = local_84;
          DAT_803b0724 = local_80;
          DAT_803b0728 = local_7c;
          return 1;
        }
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0xc),afStack_90);
        dVar9 = gnt4_PSQUATDotProduct_bl(afStack_90,(float *)(param_2 + 0x30));
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0x18),(float *)(param_2 + 0xc),afStack_90);
        dVar10 = gnt4_PSQUATDotProduct_bl(afStack_90,(float *)(param_2 + 0x30));
        if (dVar9 < dVar10) {
          DAT_803b0720 = local_84;
          DAT_803b0724 = local_80;
          DAT_803b0728 = local_7c;
          return 1;
        }
        if ((dVar10 == dVar9) &&
           (dVar9 = gnt4_PSQUATDotProduct_bl
                              ((float *)(*(int *)(*(int *)(param_1 + 4) + 0x20) + 0x38),
                               (float *)(param_2 + 0x30)), dVar9 < (double)FLOAT_80436f68)) {
          DAT_803b0720 = local_84;
          DAT_803b0724 = local_80;
          DAT_803b0728 = local_7c;
          return 1;
        }
      }
      iVar3 = iVar3 + 1;
      iVar6 = iVar6 + 0x24;
      iVar5 = iVar5 + 0x18;
    } while (iVar3 < 2);
    iVar4 = iVar4 + 1;
    iVar7 = iVar7 + 0xc;
  } while (iVar4 < 6);
  iVar4 = 0;
  iVar7 = param_1;
  do {
    local_78 = *(float *)(iVar7 + 0x34);
    pfVar8 = &local_78;
    local_74 = *(undefined4 *)(iVar7 + 0x38);
    iVar5 = 0;
    local_70 = *(undefined4 *)(iVar7 + 0x3c);
    local_6c = *(float *)(iVar7 + 0x40);
    local_68 = *(undefined4 *)(iVar7 + 0x44);
    local_64 = *(undefined4 *)(iVar7 + 0x48);
    local_60 = *(undefined4 *)(iVar7 + 0x4c);
    local_5c = *(undefined4 *)(iVar7 + 0x50);
    local_58 = *(undefined4 *)(iVar7 + 0x54);
    local_54 = local_78;
    local_50 = local_74;
    local_4c = local_70;
    do {
      bVar2 = FUN_80039da4(pfVar8,(float *)(param_2 + 0x30),(float *)(param_2 + 0xc),&local_84);
      if (bVar2 != 0) {
        gnt4_PSVECSubtract_bl(&local_84,(float *)(param_2 + 0xc),afStack_90);
        dVar11 = gnt4_PSVECMag_bl(afStack_90);
        if (dVar11 <= (double)*(float *)(param_2 + 0x4c)) {
          if ((*(ushort *)(*(int *)(*(int *)(param_2 + 4) + 0x28) + 2) & 0x40) == 0) {
            DAT_803b0720 = local_84;
            DAT_803b0724 = local_80;
            DAT_803b0728 = local_7c;
            return 1;
          }
          gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0xc),afStack_90);
          dVar11 = gnt4_PSQUATDotProduct_bl(afStack_90,(float *)(param_2 + 0x30));
          gnt4_PSVECSubtract_bl((float *)(param_1 + 0x18),(float *)(param_2 + 0xc),afStack_90);
          dVar9 = gnt4_PSQUATDotProduct_bl(afStack_90,(float *)(param_2 + 0x30));
          if (dVar11 < dVar9) {
            DAT_803b0720 = local_84;
            DAT_803b0724 = local_80;
            DAT_803b0728 = local_7c;
            return 1;
          }
          if ((dVar9 == dVar11) &&
             (dVar11 = gnt4_PSQUATDotProduct_bl
                                 ((float *)(*(int *)(*(int *)(param_1 + 4) + 0x20) + 0x38),
                                  (float *)(param_2 + 0x30)), dVar11 < (double)FLOAT_80436f68)) {
            DAT_803b0720 = local_84;
            DAT_803b0724 = local_80;
            DAT_803b0728 = local_7c;
            return 1;
          }
        }
      }
      iVar5 = iVar5 + 1;
      pfVar8 = pfVar8 + 3;
    } while (iVar5 < 3);
    iVar4 = iVar4 + 1;
    iVar7 = iVar7 + 0x24;
    if (1 < iVar4) {
      return 0;
    }
  } while( true );
}



// ==== 80032da4  FUN_80032da4 ====

undefined4 FUN_80032da4(int param_1,int param_2)

{
  int iVar1;
  bool bVar3;
  undefined4 uVar2;
  
  iVar1 = FUN_80030a3c(param_1,param_2);
  if ((iVar1 == 0) || (bVar3 = FUN_80032e94(param_2), !bVar3)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 80032df4  FUN_80032df4 ====

undefined4 FUN_80032df4(int param_1,int param_2)

{
  int iVar1;
  bool bVar3;
  undefined4 uVar2;
  
  iVar1 = FUN_80031e50(param_1,param_2);
  if ((iVar1 == 0) || (bVar3 = FUN_80032e94(param_2), !bVar3)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 80032e44  FUN_80032e44 ====

undefined4 FUN_80032e44(int param_1,int param_2)

{
  uint uVar1;
  bool bVar3;
  undefined4 uVar2;
  
  uVar1 = FUN_80031f30(param_1,param_2);
  if ((uVar1 == 0) || (bVar3 = FUN_80032e94(param_1), !bVar3)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 80032e94  FUN_80032e94 ====

bool FUN_80032e94(int param_1)

{
  byte bVar1;
  double dVar2;
  float afStack_18 [4];
  
  gnt4_PSVECSubtract_bl((float *)&DAT_803b0720,(float *)(param_1 + 0x34),afStack_18);
  dVar2 = gnt4_PSQUATDotProduct_bl(afStack_18,(float *)(param_1 + 100));
  bVar1 = dVar2 < (double)FLOAT_80436f68;
  gnt4_PSVECSubtract_bl((float *)&DAT_803b0720,(float *)(param_1 + 0x40),afStack_18);
  dVar2 = gnt4_PSQUATDotProduct_bl(afStack_18,(float *)(param_1 + 0x70));
  if (dVar2 < (double)FLOAT_80436f68) {
    bVar1 = bVar1 | 2;
  }
  return bVar1 == 0;
}



// ==== 80032f3c  FUN_80032f3c ====

undefined4 FUN_80032f3c(int param_1,int param_2)

{
  undefined4 uVar1;
  double dVar2;
  double dVar3;
  float local_18;
  float local_14;
  float local_10;
  
  gnt4_PSVECSubtract_bl((float *)(param_2 + 0xc),(float *)(param_1 + 0xc),&local_18);
  dVar2 = gnt4_PSVECMag_bl(&local_18);
  local_18 = *(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30);
  dVar3 = (double)local_18;
  if (DOUBLE_80436fe0 <= dVar2) {
    if (dVar3 <= dVar2) {
      uVar1 = 0;
    }
    else {
      FUN_800358f4((double)(float)(dVar3 - dVar2),*(int *)(param_1 + 4),*(int *)(param_2 + 4),
                   &local_18);
      uVar1 = 1;
    }
  }
  else {
    local_14 = FLOAT_80436f68;
    local_10 = FLOAT_80436f68;
    FUN_800358f4(dVar3,*(int *)(param_1 + 4),*(int *)(param_2 + 4),&local_18);
    uVar1 = 1;
  }
  return uVar1;
}



// ==== 80032ff8  FUN_80032ff8 ====

/* WARNING: Removing unreachable block (ram,0x80033478) */
/* WARNING: Removing unreachable block (ram,0x80033470) */
/* WARNING: Removing unreachable block (ram,0x80033010) */
/* WARNING: Removing unreachable block (ram,0x80033008) */

undefined4 FUN_80032ff8(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  char *pcVar10;
  int iVar11;
  int unaff_r29;
  float *pfVar12;
  float *pfVar13;
  int iVar14;
  double dVar15;
  double in_f30;
  double dVar16;
  float local_d8;
  undefined4 local_d4;
  undefined4 local_d0;
  float afStack_cc [3];
  float afStack_c0 [3];
  int local_b4;
  int local_b0;
  int local_9c [6];
  float local_84 [6];
  float local_6c [8];
  
  pfVar13 = local_6c;
  pfVar12 = local_84;
  dVar16 = (double)FLOAT_80436fc8;
  pcVar10 = &DAT_802cffc8;
  iVar5 = 0;
  pfVar6 = pfVar12;
  iVar7 = param_2;
  pfVar8 = pfVar13;
  iVar9 = param_2;
  do {
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + 0xc),(float *)(param_2 + *pcVar10 * 0xc + 0x30),afStack_c0);
    dVar15 = gnt4_PSQUATDotProduct_bl(afStack_c0,(float *)(iVar9 + 0x90));
    *pfVar8 = (float)dVar15;
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x18),(float *)(iVar7 + 0x120),afStack_c0);
    dVar15 = gnt4_PSQUATDotProduct_bl(afStack_c0,(float *)(iVar9 + 0x9c));
    *pfVar6 = (float)dVar15;
    if ((float)ABS((double)*pfVar6) <= (float)ABS(dVar16)) {
      unaff_r29 = iVar5;
      dVar16 = (double)*pfVar6;
    }
    iVar5 = iVar5 + 1;
    iVar9 = iVar9 + 0x18;
    pfVar8 = pfVar8 + 1;
    iVar7 = iVar7 + 0xc;
    pfVar6 = pfVar6 + 1;
    pcVar10 = pcVar10 + 4;
  } while (iVar5 < 6);
  piVar3 = local_9c;
  iVar9 = 0;
  iVar5 = 0;
  iVar7 = 0;
  iVar11 = 0;
  iVar14 = 6;
  piVar4 = piVar3;
  do {
    fVar1 = *pfVar13;
    *piVar4 = 0;
    fVar2 = *(float *)(param_1 + 0x30);
    if (fVar1 <= fVar2) {
      if (fVar1 <= FLOAT_80436f68) {
        iVar11 = iVar11 + 1;
      }
      if ((((FLOAT_80436f68 <= *pfVar12) && (local_6c[(char)(&DAT_802d00e0)[iVar7]] <= fVar2)) &&
          (local_6c[(char)(&DAT_802d00e1)[iVar7]] <= fVar2)) &&
         ((local_6c[(char)(&DAT_802d00e2)[iVar7]] <= fVar2 &&
          (local_6c[(char)(&DAT_802d00e3)[iVar7]] <= fVar2)))) {
        *piVar3 = iVar9;
        iVar5 = iVar5 + 1;
        in_f30 = (double)*pfVar13;
        piVar3 = piVar3 + 1;
      }
    }
    piVar4 = piVar4 + 1;
    pfVar13 = pfVar13 + 1;
    pfVar12 = pfVar12 + 1;
    iVar7 = iVar7 + 4;
    iVar9 = iVar9 + 1;
    iVar14 = iVar14 + -1;
  } while (iVar14 != 0);
  if (iVar5 == 2) {
    iVar7 = zz_0039938_(local_9c,(int)&local_b4);
    if (iVar7 != 0) {
      gnt4_PSVECSubtract_bl
                ((float *)(param_1 + 0xc),(float *)(param_2 + local_b4 * 0xc + 0x30),afStack_c0);
      gnt4_PSVECSubtract_bl
                ((float *)(param_2 + local_b0 * 0xc + 0x30),
                 (float *)(param_2 + local_b4 * 0xc + 0x30),afStack_cc);
      gnt4_PSVECNormalize_bl(afStack_cc,afStack_cc);
      dVar15 = gnt4_PSQUATDotProduct_bl(afStack_c0,afStack_cc);
      gnt4_PSQUATScale_bl(dVar15,afStack_cc,&local_d8);
      gnt4_PSVECAdd_bl(&local_d8,(float *)(param_2 + local_b4 * 0xc + 0x30),&local_d8);
      gnt4_PSVECSubtract_bl(&local_d8,(float *)(param_2 + local_b4 * 0xc + 0x30),afStack_c0);
      dVar15 = gnt4_PSQUATDotProduct_bl(afStack_c0,afStack_cc);
      if ((double)FLOAT_80436f68 <= dVar15) {
        gnt4_PSVECSubtract_bl(&local_d8,(float *)(param_2 + local_b0 * 0xc + 0x30),afStack_c0);
        dVar15 = gnt4_PSQUATDotProduct_bl(afStack_c0,afStack_cc);
        if ((double)FLOAT_80436f68 < dVar15) {
          iVar7 = param_2 + local_b0 * 0xc;
          local_d8 = *(float *)(iVar7 + 0x30);
          local_d4 = *(undefined4 *)(iVar7 + 0x34);
          local_d0 = *(undefined4 *)(iVar7 + 0x38);
        }
      }
      else {
        iVar7 = param_2 + local_b4 * 0xc;
        local_d8 = *(float *)(iVar7 + 0x30);
        local_d4 = *(undefined4 *)(iVar7 + 0x34);
        local_d0 = *(undefined4 *)(iVar7 + 0x38);
      }
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_d8,afStack_c0);
      dVar15 = gnt4_PSVECMag_bl(afStack_c0);
      if (dVar15 <= (double)*(float *)(param_1 + 0x30)) {
        FUN_800358f4((double)(float)(dVar15 - (double)*(float *)(param_1 + 0x30)),
                     *(int *)(param_1 + 4),*(int *)(param_2 + 4),afStack_c0);
        return 1;
      }
    }
  }
  else if (iVar5 < 2) {
    if ((iVar5 != 0) && (-1 < iVar5)) {
      FUN_800358f4((double)(float)(in_f30 - (double)*(float *)(param_1 + 0x30)),
                   *(int *)(param_1 + 4),*(int *)(param_2 + 4),
                   (float *)(param_2 + local_9c[0] * 0x18 + 0x90));
      return 1;
    }
  }
  else if (((iVar5 < 7) && (iVar5 < 4)) && (iVar7 = zz_0039a48_(local_9c,&local_b4), iVar7 != 0)) {
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + 0xc),(float *)(param_2 + local_b4 * 0xc + 0x30),afStack_c0);
    dVar15 = gnt4_PSVECMag_bl(afStack_c0);
    if (dVar15 <= (double)*(float *)(param_1 + 0x30)) {
      FUN_800358f4((double)(float)(dVar15 - (double)*(float *)(param_1 + 0x30)),
                   *(int *)(param_1 + 4),*(int *)(param_2 + 4),afStack_c0);
      return 1;
    }
  }
  if (5 < iVar11) {
    FUN_800358f4((double)(float)(dVar16 - (double)*(float *)(param_1 + 0x30)),*(int *)(param_1 + 4),
                 *(int *)(param_2 + 4),(float *)(param_2 + unaff_r29 * 0x18 + 0x90));
  }
  return 0;
}



// ==== 80033494  FUN_80033494 ====

/* WARNING: Removing unreachable block (ram,0x80033600) */
/* WARNING: Removing unreachable block (ram,0x80033530) */
/* WARNING: Removing unreachable block (ram,0x800334a4) */

uint FUN_80033494(int param_1,int param_2)

{
  byte bVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  float afStack_38 [3];
  float local_2c;
  undefined4 local_28;
  undefined4 local_24;
  
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0x34),&local_2c);
  dVar2 = gnt4_PSQUATDotProduct_bl(&local_2c,(float *)(param_2 + 100));
  bVar1 = dVar2 < (double)FLOAT_80436f68;
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0x40),&local_2c);
  dVar2 = gnt4_PSQUATDotProduct_bl(&local_2c,(float *)(param_2 + 0x70));
  if (dVar2 < (double)FLOAT_80436f68) {
    bVar1 = bVar1 | 2;
  }
  if (bVar1 == 2) {
    local_2c = *(float *)(param_2 + 0x40);
    local_28 = *(undefined4 *)(param_2 + 0x44);
    local_24 = *(undefined4 *)(param_2 + 0x48);
  }
  else if (bVar1 < 2) {
    if (bVar1 == 0) {
      gnt4_PSQUATScale_bl(dVar2,(float *)(param_2 + 0x70),&local_2c);
      gnt4_PSVECAdd_bl((float *)(param_2 + 0x40),&local_2c,&local_2c);
    }
    else {
      local_2c = *(float *)(param_2 + 0x34);
      local_28 = *(undefined4 *)(param_2 + 0x38);
      local_24 = *(undefined4 *)(param_2 + 0x3c);
    }
  }
  else if (bVar1 < 4) {
    return 0;
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_2c,afStack_38);
  dVar3 = gnt4_PSVECMag_bl(afStack_38);
  dVar2 = (double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30));
  if (dVar3 < dVar2) {
    dVar4 = (double)(float)(dVar2 - dVar3);
    gnt4_PSVECSubtract_bl(&local_2c,(float *)(param_1 + 0xc),&local_2c);
    FUN_800358f4(dVar4,*(int *)(param_1 + 4),*(int *)(param_2 + 4),&local_2c);
  }
  return (uint)(dVar3 < dVar2);
}



// ==== 80033624  zz_0033624_ ====

/* WARNING: Removing unreachable block (ram,0x80033c80) */
/* WARNING: Removing unreachable block (ram,0x80033c78) */
/* WARNING: Removing unreachable block (ram,0x8003363c) */
/* WARNING: Removing unreachable block (ram,0x80033634) */
/* WARNING: Removing unreachable block (ram,0x80033984) */

undefined4 zz_0033624_(int param_1,int param_2)

{
  bool bVar1;
  uint uVar2;
  byte bVar4;
  undefined4 uVar3;
  int iVar5;
  int unaff_r29;
  float *pfVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  float afStack_b0 [3];
  float afStack_a4 [3];
  float afStack_98 [3];
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  undefined4 local_7c;
  undefined4 local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  undefined4 local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  float local_50;
  undefined4 local_4c;
  undefined4 local_48;
  
  iVar5 = 0;
  iVar7 = param_2;
  iVar8 = param_2;
  do {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0x4c),afStack_98);
    dVar9 = gnt4_PSQUATDotProduct_bl(afStack_98,(float *)(iVar7 + 0x7c));
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x18),(float *)(param_2 + 0xac),afStack_98);
    dVar10 = gnt4_PSQUATDotProduct_bl(afStack_98,(float *)(iVar7 + 0x88));
    if ((float)ABS(dVar9) < *(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30)) {
      gnt4_PSQUATScale_bl(dVar9,(float *)(iVar7 + 0x7c),&local_8c);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_8c,&local_8c);
      bVar1 = false;
      if ((dVar9 < (double)FLOAT_80436f68) || ((double)FLOAT_80436f68 <= dVar10)) {
        if ((dVar9 < (double)FLOAT_80436f68) && ((double)FLOAT_80436f68 < dVar10)) {
          bVar1 = true;
        }
      }
      else {
        bVar1 = true;
      }
      uVar2 = zz_0039aec_(&local_8c,(float *)(iVar8 + 0x34),(float *)(iVar7 + 0x7c));
      if (uVar2 != 0) {
        if (bVar1) {
          if (dVar9 < (double)FLOAT_80436f68) {
            dVar9 = dVar9 - (double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30));
          }
          else {
            dVar9 = dVar9 + (double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30));
          }
          FUN_800358f4((double)(float)dVar9,*(int *)(param_1 + 4),*(int *)(param_2 + 4),
                       (float *)(param_2 + iVar5 * 0x18 + 0x7c));
        }
        else {
          if (dVar9 < (double)FLOAT_80436f68) {
            dVar9 = (double)(float)(dVar9 + (double)(*(float *)(param_1 + 0x30) +
                                                    *(float *)(param_2 + 0x30)));
          }
          else {
            dVar9 = -(double)(float)((double)(*(float *)(param_1 + 0x30) +
                                             *(float *)(param_2 + 0x30)) - dVar9);
          }
          FUN_800358f4(dVar9,*(int *)(param_1 + 4),*(int *)(param_2 + 4),
                       (float *)(param_2 + iVar5 * 0x18 + 0x7c));
        }
        return 1;
      }
    }
    bVar4 = FUN_80039da4((float *)(param_1 + 0xc),(float *)(iVar7 + 0x7c),(float *)(param_2 + 0x4c),
                         &local_8c);
    if ((bVar4 != 0) &&
       (uVar2 = zz_0039aec_(&local_8c,(float *)(iVar8 + 0x34),(float *)(iVar7 + 0x7c)), uVar2 != 0))
    {
      if (dVar9 < (double)FLOAT_80436f68) {
        dVar9 = dVar9 - (double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30));
      }
      else {
        dVar9 = dVar9 + (double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30));
      }
      FUN_800358f4((double)(float)dVar9,*(int *)(param_1 + 4),*(int *)(param_2 + 4),
                   (float *)(param_2 + iVar5 * 0x18 + 0x7c));
      return 1;
    }
    iVar5 = iVar5 + 1;
    iVar8 = iVar8 + 0x24;
    iVar7 = iVar7 + 0x18;
    if (1 < iVar5) {
      local_80 = *(float *)(param_2 + 0x34);
      pfVar6 = &local_80;
      local_7c = *(undefined4 *)(param_2 + 0x38);
      iVar7 = 0;
      dVar9 = (double)FLOAT_80436fe8;
      dVar10 = (double)FLOAT_80436f68;
      local_78 = *(undefined4 *)(param_2 + 0x3c);
      local_74 = *(undefined4 *)(param_2 + 0x40);
      local_70 = *(undefined4 *)(param_2 + 0x44);
      local_6c = *(undefined4 *)(param_2 + 0x48);
      local_68 = *(undefined4 *)(param_2 + 0x58);
      local_64 = *(undefined4 *)(param_2 + 0x5c);
      local_60 = *(undefined4 *)(param_2 + 0x60);
      local_5c = *(undefined4 *)(param_2 + 0x4c);
      local_58 = *(undefined4 *)(param_2 + 0x50);
      local_54 = *(undefined4 *)(param_2 + 0x54);
      local_50 = local_80;
      local_4c = local_7c;
      local_48 = local_78;
      do {
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),pfVar6,afStack_98);
        gnt4_PSVECSubtract_bl(pfVar6 + 3,pfVar6,afStack_a4);
        gnt4_PSVECNormalize_bl(afStack_a4,afStack_a4);
        dVar11 = gnt4_PSQUATDotProduct_bl(afStack_98,afStack_a4);
        bVar4 = dVar11 < dVar10;
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),pfVar6 + 3,afStack_98);
        dVar11 = gnt4_PSQUATDotProduct_bl(afStack_98,afStack_a4);
        if (dVar10 < dVar11) {
          bVar4 = bVar4 | 2;
        }
        if (bVar4 == 2) {
          local_8c = pfVar6[3];
          local_88 = pfVar6[4];
          local_84 = pfVar6[5];
        }
        else if (bVar4 < 2) {
          if (bVar4 == 0) {
            gnt4_PSQUATScale_bl(dVar11,afStack_a4,&local_8c);
            gnt4_PSVECAdd_bl(pfVar6 + 3,&local_8c,&local_8c);
          }
          else {
            local_8c = *pfVar6;
            local_88 = pfVar6[1];
            local_84 = pfVar6[2];
          }
        }
        else if (bVar4 < 4) {
          return 0;
        }
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_8c,afStack_98);
        dVar11 = gnt4_PSVECMag_bl(afStack_98);
        if (dVar11 < dVar9) {
          local_bc = local_8c;
          local_b8 = local_88;
          local_b4 = local_84;
          unaff_r29 = iVar7;
          dVar9 = dVar11;
        }
        iVar7 = iVar7 + 1;
        pfVar6 = pfVar6 + 3;
      } while (iVar7 < 4);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0x4c),afStack_98);
      pfVar6 = (float *)(param_2 + (unaff_r29 / 2) * 0x18 + 0x7c);
      dVar9 = gnt4_PSQUATDotProduct_bl(afStack_98,pfVar6);
      gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x30),pfVar6,&local_8c);
      gnt4_PSVECAdd_bl(&local_bc,&local_8c,&local_c8);
      gnt4_PSVECAdd_bl((float *)(param_2 + 0x4c),&local_8c,afStack_98);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),afStack_98,afStack_98);
      dVar10 = gnt4_PSQUATDotProduct_bl(afStack_98,pfVar6);
      gnt4_PSQUATScale_bl(-(double)*(float *)(param_2 + 0x30),pfVar6,&local_8c);
      gnt4_PSVECAdd_bl(&local_bc,&local_8c,&local_d4);
      gnt4_PSVECAdd_bl((float *)(param_2 + 0x4c),&local_8c,afStack_98);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),afStack_98,afStack_98);
      dVar11 = gnt4_PSQUATDotProduct_bl(afStack_98,pfVar6);
      if ((float)ABS(dVar10) < (float)ABS(dVar9)) {
        local_bc = local_c8;
        local_b8 = local_c4;
        local_b4 = local_c0;
        dVar9 = dVar10;
      }
      if ((float)ABS(dVar11) < (float)ABS(dVar9)) {
        local_bc = local_d4;
        local_b8 = local_d0;
        local_b4 = local_cc;
        dVar9 = dVar11;
      }
      gnt4_PSQUATScale_bl(dVar9,pfVar6,&local_8c);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_8c,afStack_b0);
      dVar9 = (double)(*(float *)(param_1 + 0x30) * *(float *)(param_1 + 0x30) -
                      (float)(dVar9 * dVar9));
      if ((double)FLOAT_80436f68 < dVar9) {
        dVar10 = 1.0 / SQRT(dVar9);
        dVar10 = DOUBLE_80436fd0 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80436fd8);
        dVar10 = DOUBLE_80436fd0 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80436fd8);
        dVar9 = (double)(float)(dVar9 * DOUBLE_80436fd0 * dVar10 *
                                        -(dVar9 * dVar10 * dVar10 - DOUBLE_80436fd8));
      }
      gnt4_PSVECSubtract_bl(&local_bc,afStack_b0,afStack_98);
      dVar10 = gnt4_PSVECMag_bl(afStack_98);
      if ((double)FLOAT_80436fc4 <= dVar10) {
        if (dVar9 <= dVar10) {
          uVar3 = 0;
        }
        else {
          gnt4_PSVECNormalize_bl(afStack_98,afStack_98);
          FUN_800358f4((double)(float)(dVar9 - dVar10),*(int *)(param_1 + 4),*(int *)(param_2 + 4),
                       afStack_98);
          uVar3 = 1;
        }
      }
      else {
        uVar3 = 0;
      }
      return uVar3;
    }
  } while( true );
}



// ==== 80033c9c  zz_0033c9c_ ====

/* WARNING: Removing unreachable block (ram,0x80034108) */
/* WARNING: Removing unreachable block (ram,0x80034100) */
/* WARNING: Removing unreachable block (ram,0x80033cb4) */
/* WARNING: Removing unreachable block (ram,0x80033cac) */

undefined4 zz_0033c9c_(int param_1,int param_2)

{
  bool bVar1;
  byte bVar3;
  undefined4 uVar2;
  double dVar4;
  double dVar5;
  double dVar6;
  float local_84;
  undefined4 local_80;
  undefined4 local_7c;
  float local_78;
  undefined4 local_74;
  undefined4 local_70;
  float local_6c;
  undefined4 local_68;
  undefined4 local_64;
  float afStack_60 [3];
  float afStack_54 [3];
  float afStack_48 [7];
  
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0xc),afStack_54);
  dVar4 = gnt4_PSQUATDotProduct_bl(afStack_54,(float *)(param_2 + 0x30));
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x18),(float *)(param_2 + 0x18),afStack_54);
  dVar5 = gnt4_PSQUATDotProduct_bl(afStack_54,(float *)(param_2 + 0x3c));
  if ((float)ABS(dVar4) < *(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x48)) {
    gnt4_PSQUATScale_bl(dVar4,(float *)(param_2 + 0x30),afStack_48);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),afStack_48,afStack_48);
    bVar1 = false;
    if ((dVar4 < (double)FLOAT_80436f68) || ((double)FLOAT_80436f68 <= dVar5)) {
      if ((dVar4 < (double)FLOAT_80436f68) && ((double)FLOAT_80436f68 < dVar5)) {
        bVar1 = true;
      }
    }
    else {
      bVar1 = true;
    }
    gnt4_PSVECSubtract_bl(afStack_48,(float *)(param_2 + 0xc),afStack_54);
    dVar5 = gnt4_PSVECMag_bl(afStack_54);
    if (dVar5 <= (double)*(float *)(param_2 + 0x4c)) {
      if (bVar1) {
        if (dVar4 < (double)FLOAT_80436f68) {
          dVar4 = dVar4 - (double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x48));
        }
        else {
          dVar4 = dVar4 + (double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x48));
        }
        FUN_800358f4((double)(float)dVar4,*(int *)(param_1 + 4),*(int *)(param_2 + 4),
                     (float *)(param_2 + 0x30));
      }
      else {
        if (dVar4 < (double)FLOAT_80436f68) {
          dVar4 = (double)(float)(dVar4 + (double)(*(float *)(param_1 + 0x30) +
                                                  *(float *)(param_2 + 0x48)));
        }
        else {
          dVar4 = -(double)(float)((double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x48))
                                  - dVar4);
        }
        FUN_800358f4(dVar4,*(int *)(param_1 + 4),*(int *)(param_2 + 4),(float *)(param_2 + 0x30));
      }
      return 1;
    }
  }
  bVar3 = FUN_80039da4((float *)(param_1 + 0xc),(float *)(param_2 + 0x30),(float *)(param_2 + 0xc),
                       afStack_48);
  if (bVar3 != 0) {
    gnt4_PSVECSubtract_bl(afStack_48,(float *)(param_2 + 0xc),afStack_54);
    dVar5 = gnt4_PSVECMag_bl(afStack_54);
    if (dVar5 <= (double)*(float *)(param_2 + 0x4c)) {
      if (dVar4 < (double)FLOAT_80436f68) {
        dVar4 = dVar4 - (double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x48));
      }
      else {
        dVar4 = dVar4 + (double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x48));
      }
      FUN_800358f4((double)(float)dVar4,*(int *)(param_1 + 4),*(int *)(param_2 + 4),
                   (float *)(param_2 + 0x30));
      return 1;
    }
  }
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0xc),afStack_54);
  dVar4 = gnt4_PSQUATDotProduct_bl(afStack_54,(float *)(param_2 + 0x30));
  local_6c = *(float *)(param_2 + 0xc);
  local_68 = *(undefined4 *)(param_2 + 0x10);
  local_64 = *(undefined4 *)(param_2 + 0x14);
  gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x48),(float *)(param_2 + 0x30),afStack_48);
  gnt4_PSVECAdd_bl((float *)(param_2 + 0xc),afStack_48,&local_78);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_78,afStack_54);
  dVar5 = gnt4_PSQUATDotProduct_bl(afStack_54,(float *)(param_2 + 0x30));
  gnt4_PSQUATScale_bl(-(double)*(float *)(param_2 + 0x48),(float *)(param_2 + 0x30),afStack_48);
  gnt4_PSVECAdd_bl((float *)(param_2 + 0xc),afStack_48,&local_84);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),&local_84,afStack_54);
  dVar6 = gnt4_PSQUATDotProduct_bl(afStack_54,(float *)(param_2 + 0x30));
  if ((float)ABS(dVar5) < (float)ABS(dVar4)) {
    local_6c = local_78;
    local_68 = local_74;
    local_64 = local_70;
    dVar4 = dVar5;
  }
  if ((float)ABS(dVar6) < (float)ABS(dVar4)) {
    local_6c = local_84;
    local_68 = local_80;
    local_64 = local_7c;
    dVar4 = dVar6;
  }
  gnt4_PSQUATScale_bl(dVar4,(float *)(param_2 + 0x30),afStack_48);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),afStack_48,afStack_60);
  dVar4 = (double)(*(float *)(param_1 + 0x30) * *(float *)(param_1 + 0x30) - (float)(dVar4 * dVar4))
  ;
  if ((double)FLOAT_80436f68 < dVar4) {
    dVar5 = 1.0 / SQRT(dVar4);
    dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436fd8);
    dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436fd8);
    dVar4 = (double)(float)(dVar4 * DOUBLE_80436fd0 * dVar5 *
                                    -(dVar4 * dVar5 * dVar5 - DOUBLE_80436fd8));
  }
  gnt4_PSVECSubtract_bl(&local_6c,afStack_60,afStack_48);
  dVar5 = gnt4_PSVECMag_bl(afStack_48);
  if ((double)FLOAT_80436fc4 <= dVar5) {
    dVar4 = (double)(float)(dVar4 + (double)*(float *)(param_2 + 0x4c));
    if (dVar4 <= dVar5) {
      uVar2 = 0;
    }
    else {
      gnt4_PSVECNormalize_bl(afStack_48,afStack_54);
      FUN_800358f4((double)(float)(dVar4 - dVar5),*(int *)(param_1 + 4),*(int *)(param_2 + 4),
                   afStack_54);
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}



// ==== 8003412c  FUN_8003412c ====

/* WARNING: Removing unreachable block (ram,0x80034434) */
/* WARNING: Removing unreachable block (ram,0x8003442c) */
/* WARNING: Removing unreachable block (ram,0x80034424) */
/* WARNING: Removing unreachable block (ram,0x80034284) */
/* WARNING: Removing unreachable block (ram,0x8003414c) */
/* WARNING: Removing unreachable block (ram,0x80034144) */
/* WARNING: Removing unreachable block (ram,0x8003413c) */

uint FUN_8003412c(int param_1,int param_2)

{
  uint uVar1;
  bool bVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  char *pcVar7;
  byte bVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  float afStack_a8 [3];
  int local_9c [6];
  float local_84;
  undefined4 local_80;
  undefined4 local_7c;
  float local_78;
  undefined4 local_74;
  undefined4 local_70;
  undefined4 local_6c;
  undefined4 local_68;
  undefined4 local_64;
  
  dVar11 = (double)FLOAT_80436f68;
  piVar5 = local_9c;
  local_9c[0] = 0;
  pcVar7 = &DAT_802cffc8;
  local_9c[1] = 0;
  iVar3 = 0;
  iVar4 = 0;
  local_9c[2] = 0;
  local_9c[5] = 0;
  local_9c[3] = -1;
  local_9c[4] = -1;
  local_84 = *(float *)(param_2 + 0x34);
  local_80 = *(undefined4 *)(param_2 + 0x38);
  local_7c = *(undefined4 *)(param_2 + 0x3c);
  local_78 = *(float *)(param_2 + 0x40);
  local_74 = *(undefined4 *)(param_2 + 0x44);
  local_70 = *(undefined4 *)(param_2 + 0x48);
  local_6c = *(undefined4 *)(param_2 + 0xc);
  local_68 = *(undefined4 *)(param_2 + 0x10);
  local_64 = *(undefined4 *)(param_2 + 0x14);
  iVar6 = param_1;
  do {
    gnt4_PSVECSubtract_bl(&local_84,(float *)(param_1 + *pcVar7 * 0xc + 0x30),afStack_a8);
    dVar9 = gnt4_PSQUATDotProduct_bl(afStack_a8,(float *)(iVar6 + 0x90));
    bVar8 = dVar9 < dVar11;
    gnt4_PSVECSubtract_bl(&local_78,(float *)(param_1 + *pcVar7 * 0xc + 0x30),afStack_a8);
    dVar10 = gnt4_PSQUATDotProduct_bl(afStack_a8,(float *)(iVar6 + 0x90));
    if (dVar10 < dVar11) {
      bVar8 = bVar8 | 2;
    }
    if (bVar8 == 2) {
      gnt4_PSVECSubtract_bl(&local_84,&local_78,afStack_a8);
      dVar10 = gnt4_PSQUATDotProduct_bl(afStack_a8,(float *)(iVar6 + 0x90));
      if (((double)FLOAT_80436f68 == dVar10) || ((double)FLOAT_80436fcc == dVar10)) {
        gnt4_PSQUATScale_bl(dVar9,(float *)(iVar6 + 0x90),afStack_a8);
      }
      else {
        gnt4_PSQUATScale_bl((double)(float)(dVar9 / dVar10),afStack_a8,afStack_a8);
      }
      gnt4_PSVECSubtract_bl(&local_84,afStack_a8,&local_84);
      local_9c[4] = iVar4;
    }
    else if (bVar8 < 2) {
      if (bVar8 == 0) {
        iVar3 = iVar3 + 1;
        *piVar5 = iVar4;
        piVar5 = piVar5 + 1;
        if (3 < iVar3) {
          return 0;
        }
      }
      else {
        gnt4_PSVECSubtract_bl(&local_78,&local_84,afStack_a8);
        dVar9 = gnt4_PSQUATDotProduct_bl(afStack_a8,(float *)(iVar6 + 0x90));
        if (((double)FLOAT_80436f68 == dVar9) || ((double)FLOAT_80436fcc == dVar9)) {
          gnt4_PSQUATScale_bl(dVar10,(float *)(iVar6 + 0x90),afStack_a8);
        }
        else {
          gnt4_PSQUATScale_bl((double)(float)(dVar10 / dVar9),afStack_a8,afStack_a8);
        }
        gnt4_PSVECSubtract_bl(&local_78,afStack_a8,&local_78);
        local_9c[3] = iVar4;
      }
    }
    iVar4 = iVar4 + 1;
    iVar6 = iVar6 + 0x18;
    pcVar7 = pcVar7 + 4;
  } while (iVar4 < 6);
  if (iVar3 == 2) {
    uVar1 = zz_0034930_(param_1,param_2,&local_84,local_9c);
    return uVar1;
  }
  if (iVar3 < 2) {
    if (iVar3 == 0) {
      uVar1 = zz_0034450_(param_1,param_2,&local_84,local_9c + 3);
      return uVar1;
    }
    if (-1 < iVar3) {
      bVar2 = zz_00347f0_(param_1,param_2,&local_84,local_9c);
      return (uint)bVar2;
    }
  }
  else if (iVar3 < 4) {
    uVar1 = zz_0034a5c_(param_1,param_2,&local_84,local_9c);
    return uVar1;
  }
  return 0;
}



// ==== 80034450  zz_0034450_ ====

/* WARNING: Removing unreachable block (ram,0x800347c8) */
/* WARNING: Removing unreachable block (ram,0x80034460) */

undefined4 zz_0034450_(int param_1,int param_2,float *param_3,int *param_4)

{
  int iVar1;
  double dVar2;
  int local_e8;
  int local_e4;
  float afStack_e0 [3];
  float afStack_d4 [3];
  float afStack_c8 [3];
  float afStack_bc [3];
  float afStack_b0 [18];
  float afStack_68 [12];
  float afStack_38 [6];
  
  iVar1 = *param_4;
  if ((iVar1 != -1) || (param_4[1] != -1)) {
    if ((iVar1 == -1) || (param_4[1] != -1)) {
      if ((iVar1 == -1) && (param_4[1] != -1)) {
        gnt4_PSVECSubtract_bl(param_3,param_3 + 3,afStack_d4);
        dVar2 = gnt4_PSVECMag_bl(afStack_d4);
        if (dVar2 <= (double)FLOAT_80436f68) {
          gnt4_PSVECSubtract_bl
                    ((float *)(param_1 + (char)(&DAT_802cffc8)[param_4[1] * 4] * 0xc + 0x30),
                     param_3 + 3,afStack_e0);
          dVar2 = gnt4_PSQUATDotProduct_bl(afStack_e0,(float *)(param_1 + param_4[1] * 0x18 + 0x90))
          ;
          FUN_800358f4((double)((float)ABS(dVar2) + *(float *)(param_2 + 0x30)),
                       *(int *)(param_1 + 4),*(int *)(param_2 + 4),
                       (float *)(param_1 + param_4[1] * 0x18 + 0x90));
        }
        else {
          gnt4_PSVECNormalize_bl(afStack_d4,afStack_d4);
          FUN_800358f4((double)(float)(dVar2 + (double)*(float *)(param_2 + 0x30)),
                       *(int *)(param_1 + 4),*(int *)(param_2 + 4),afStack_d4);
        }
      }
      else {
        iVar1 = zz_0039938_(param_4,(int)&local_e8);
        if (iVar1 == 0) {
          gnt4_PSVECSubtract_bl
                    ((float *)(param_2 + 0x40),
                     (float *)(param_1 + (char)(&DAT_802cffc8)[param_4[1] * 4] * 0xc + 0x30),
                     afStack_d4);
          dVar2 = gnt4_PSQUATDotProduct_bl(afStack_d4,(float *)(param_1 + param_4[1] * 0x18 + 0x90))
          ;
          FUN_800358f4(-dVar2,*(int *)(param_1 + 4),*(int *)(param_2 + 4),
                       (float *)(param_1 + param_4[1] * 0x18 + 0x90));
        }
        else {
          zz_0038b34_((float *)(param_1 + local_e8 * 0xc + 0x30),
                      (float *)(param_1 + local_e4 * 0xc + 0x30),afStack_68);
          zz_0038b34_(param_3,param_3 + 3,afStack_b0);
          iVar1 = zz_0038c00_(afStack_68,afStack_b0,afStack_c8);
          if (iVar1 == 0) {
            gnt4_PSVECSubtract_bl(afStack_68,afStack_b0,afStack_d4);
            dVar2 = gnt4_PSQUATDotProduct_bl(afStack_d4,afStack_38);
            gnt4_PSQUATScale_bl(dVar2,afStack_38,afStack_d4);
            gnt4_PSVECAdd_bl(afStack_d4,afStack_68,afStack_d4);
            gnt4_PSVECSubtract_bl(afStack_d4,afStack_b0,afStack_d4);
            dVar2 = gnt4_PSVECMag_bl(afStack_d4);
            FUN_800358f4(dVar2,*(int *)(param_1 + 4),*(int *)(param_2 + 4),afStack_d4);
          }
          else {
            gnt4_PSVECSubtract_bl(afStack_c8,afStack_bc,afStack_d4);
            dVar2 = gnt4_PSVECMag_bl(afStack_d4);
            FUN_800358f4((double)(float)(dVar2 + (double)*(float *)(param_2 + 0x30)),
                         *(int *)(param_1 + 4),*(int *)(param_2 + 4),afStack_d4);
          }
        }
      }
    }
    else {
      gnt4_PSVECSubtract_bl(param_3 + 3,param_3,afStack_d4);
      dVar2 = gnt4_PSVECMag_bl(afStack_d4);
      if (dVar2 <= (double)FLOAT_80436f68) {
        gnt4_PSVECSubtract_bl
                  ((float *)(param_1 + (char)(&DAT_802cffc8)[*param_4 * 4] * 0xc + 0x30),param_3,
                   afStack_e0);
        dVar2 = gnt4_PSQUATDotProduct_bl(afStack_e0,(float *)(param_1 + *param_4 * 0x18 + 0x90));
        FUN_800358f4((double)((float)ABS(dVar2) + *(float *)(param_2 + 0x30)),*(int *)(param_1 + 4),
                     *(int *)(param_2 + 4),(float *)(param_1 + *param_4 * 0x18 + 0x90));
      }
      else {
        gnt4_PSVECNormalize_bl(afStack_d4,afStack_d4);
        FUN_800358f4((double)(float)(dVar2 + (double)*(float *)(param_2 + 0x30)),
                     *(int *)(param_1 + 4),*(int *)(param_2 + 4),afStack_d4);
      }
    }
  }
  return 1;
}



// ==== 800347f0  zz_00347f0_ ====

/* WARNING: Removing unreachable block (ram,0x80034908) */
/* WARNING: Removing unreachable block (ram,0x80034800) */

bool zz_00347f0_(int param_1,int param_2,float *param_3,int *param_4)

{
  double dVar1;
  double dVar2;
  float afStack_38 [6];
  
  gnt4_PSVECSubtract_bl
            (param_3,(float *)(param_1 + (char)(&DAT_802cffc8)[*param_4 * 4] * 0xc + 0x30),
             afStack_38);
  dVar1 = gnt4_PSQUATDotProduct_bl(afStack_38,(float *)(param_1 + *param_4 * 0x18 + 0x90));
  dVar1 = (double)(float)ABS(dVar1);
  gnt4_PSVECSubtract_bl
            (param_3 + 3,(float *)(param_1 + (char)(&DAT_802cffc8)[*param_4 * 4] * 0xc + 0x30),
             afStack_38);
  dVar2 = gnt4_PSQUATDotProduct_bl(afStack_38,(float *)(param_1 + *param_4 * 0x18 + 0x90));
  if ((double)(float)ABS(dVar2) < dVar1) {
    dVar1 = (double)(float)ABS(dVar2);
  }
  dVar2 = (double)*(float *)(param_2 + 0x30);
  if (dVar1 <= dVar2) {
    FUN_800358f4((double)(float)(dVar2 - dVar1),*(int *)(param_1 + 4),*(int *)(param_2 + 4),
                 (float *)(param_1 + *param_4 * 0x18 + 0x90));
  }
  return dVar1 <= dVar2;
}



// ==== 80034930  zz_0034930_ ====

/* WARNING: Removing unreachable block (ram,0x80034a38) */
/* WARNING: Removing unreachable block (ram,0x80034940) */

undefined4 zz_0034930_(int param_1,int param_2,float *param_3,int *param_4)

{
  int iVar1;
  double dVar2;
  double dVar3;
  int local_e8;
  int local_e4;
  float afStack_e0 [3];
  float afStack_d4 [3];
  float afStack_c8 [3];
  float afStack_bc [18];
  float afStack_74 [22];
  
  iVar1 = zz_0039938_(param_4,(int)&local_e8);
  if (iVar1 != 0) {
    zz_0038b34_((float *)(param_1 + local_e8 * 0xc + 0x30),
                (float *)(param_1 + local_e4 * 0xc + 0x30),afStack_74);
    zz_0038b34_(param_3,param_3 + 3,afStack_bc);
    iVar1 = zz_0038c00_(afStack_74,afStack_bc,afStack_d4);
    if (iVar1 != 0) {
      gnt4_PSVECSubtract_bl(afStack_c8,afStack_d4,afStack_e0);
      dVar2 = gnt4_PSVECMag_bl(afStack_e0);
      if (dVar2 < (double)*(float *)(param_2 + 0x30)) {
        dVar3 = (double)(float)((double)*(float *)(param_2 + 0x30) - dVar2);
        dVar2 = gnt4_PSVECSquareMag_bl(afStack_e0);
        if ((double)FLOAT_80436f68 < dVar2) {
          gnt4_PSVECNormalize_bl(afStack_e0,afStack_e0);
          FUN_800358f4(dVar3,*(int *)(param_1 + 4),*(int *)(param_2 + 4),afStack_e0);
          return 1;
        }
        return 0;
      }
    }
  }
  return 0;
}



// ==== 80034a5c  zz_0034a5c_ ====

/* WARNING: Removing unreachable block (ram,0x80034c20) */
/* WARNING: Removing unreachable block (ram,0x80034a6c) */

undefined4 zz_0034a5c_(int param_1,int param_2,float *param_3,int *param_4)

{
  int iVar1;
  undefined4 uVar2;
  double dVar3;
  int local_48;
  float local_44;
  float local_40;
  float local_3c;
  float afStack_38 [3];
  float afStack_2c [4];
  
  iVar1 = zz_0039a48_(param_4,&local_48);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    gnt4_PSVECSubtract_bl((float *)(param_1 + local_48 * 0xc + 0x30),param_3,afStack_2c);
    gnt4_PSVECSubtract_bl(param_3 + 3,param_3,afStack_38);
    dVar3 = gnt4_PSVECSquareMag_bl(afStack_38);
    if ((double)FLOAT_80436f68 < dVar3) {
      gnt4_PSVECNormalize_bl(afStack_38,afStack_38);
      dVar3 = gnt4_PSQUATDotProduct_bl(afStack_2c,afStack_38);
      gnt4_PSQUATScale_bl(dVar3,afStack_38,&local_44);
      gnt4_PSVECAdd_bl(&local_44,param_3,&local_44);
      gnt4_PSVECSubtract_bl(&local_44,param_3,afStack_2c);
      gnt4_PSVECSubtract_bl(param_3 + 3,param_3,afStack_38);
      dVar3 = gnt4_PSQUATDotProduct_bl(afStack_2c,afStack_38);
      if (dVar3 < (double)FLOAT_80436f68) {
        local_44 = *param_3;
        local_40 = param_3[1];
        local_3c = param_3[2];
      }
      gnt4_PSVECSubtract_bl(&local_44,param_3 + 3,afStack_2c);
      dVar3 = gnt4_PSQUATDotProduct_bl(afStack_2c,afStack_38);
      if ((double)FLOAT_80436f68 < dVar3) {
        local_44 = param_3[3];
        local_40 = param_3[4];
        local_3c = param_3[5];
      }
      gnt4_PSVECSubtract_bl((float *)(param_1 + local_48 * 0xc + 0x30),&local_44,afStack_38);
      dVar3 = gnt4_PSVECMag_bl(afStack_38);
      if ((double)*(float *)(param_2 + 0x30) <= dVar3) {
        uVar2 = 0;
      }
      else {
        dVar3 = (double)(float)((double)*(float *)(param_2 + 0x30) - dVar3);
        gnt4_PSVECSubtract_bl(&local_44,(float *)(param_1 + local_48 * 0xc + 0x30),afStack_2c);
        FUN_800358f4(dVar3,*(int *)(param_1 + 4),*(int *)(param_2 + 4),afStack_2c);
        uVar2 = 1;
      }
    }
    else {
      uVar2 = 0;
    }
  }
  return uVar2;
}



// ==== 80034c44  FUN_80034c44 ====

undefined4 FUN_80034c44(int param_1,int param_2)

{
  int iVar1;
  double dVar2;
  double dVar3;
  float afStack_38 [3];
  float afStack_2c [3];
  float afStack_20 [6];
  
  iVar1 = zz_0038c00_((float *)(param_1 + 0x34),(float *)(param_2 + 0x34),afStack_2c);
  if (iVar1 != 0) {
    gnt4_PSVECSubtract_bl(afStack_20,afStack_2c,afStack_38);
    dVar3 = gnt4_PSVECMag_bl(afStack_38);
    dVar2 = (double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30));
    if (dVar3 < dVar2) {
      FUN_800358f4((double)(float)(dVar2 - dVar3),*(int *)(param_1 + 4),*(int *)(param_2 + 4),
                   afStack_38);
      return 1;
    }
  }
  return 0;
}



// ==== 80034cdc  FUN_80034cdc ====

undefined4 FUN_80034cdc(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  byte bVar3;
  float local_17c;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  undefined4 local_168;
  float local_164;
  undefined4 local_160;
  undefined4 local_15c;
  float local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_140;
  
  local_170 = *param_1;
  local_16c = param_1[1];
  local_168 = param_1[2];
  local_14c = param_1[9];
  local_164 = (float)param_1[0xd];
  local_160 = param_1[0xe];
  local_15c = param_1[0xf];
  local_158 = (float)param_1[0x1f];
  local_154 = param_1[0x20];
  local_150 = param_1[0x21];
  local_140 = param_1[0xc];
  iVar1 = zz_0033624_((int)&local_170,param_2);
  if (iVar1 == 0) {
    local_164 = (float)param_1[0x10];
    local_160 = param_1[0x11];
    local_15c = param_1[0x12];
    local_158 = (float)param_1[0x22];
    local_154 = param_1[0x23];
    local_150 = param_1[0x24];
    local_140 = param_1[0xc];
    iVar1 = zz_0033624_((int)&local_170,param_2);
    if (iVar1 == 0) {
      bVar3 = FUN_80039da4((float *)(param_1 + 0xd),(float *)(param_2 + 0x7c),
                           (float *)(param_2 + 0x4c),&local_17c);
      if (bVar3 != 0) {
        local_164 = local_17c;
        local_160 = local_178;
        local_15c = local_174;
        local_158 = local_17c;
        local_154 = local_178;
        local_150 = local_174;
        local_140 = param_1[0xc];
        iVar1 = zz_0033624_((int)&local_170,param_2);
        if (iVar1 != 0) {
          return 1;
        }
      }
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 80034e48  FUN_80034e48 ====

undefined4 FUN_80034e48(undefined4 *param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  byte bVar3;
  float local_17c;
  undefined4 local_178;
  undefined4 local_174;
  undefined4 local_170;
  undefined4 local_16c;
  undefined4 local_168;
  float local_164;
  undefined4 local_160;
  undefined4 local_15c;
  float local_158;
  undefined4 local_154;
  undefined4 local_150;
  undefined4 local_14c;
  undefined4 local_140;
  
  local_170 = *param_1;
  local_16c = param_1[1];
  local_168 = param_1[2];
  local_14c = param_1[9];
  local_164 = (float)param_1[0xd];
  local_160 = param_1[0xe];
  local_15c = param_1[0xf];
  local_158 = (float)param_1[0x1f];
  local_154 = param_1[0x20];
  local_150 = param_1[0x21];
  local_140 = param_1[0xc];
  iVar1 = zz_0033c9c_((int)&local_170,param_2);
  if (iVar1 == 0) {
    local_164 = (float)param_1[0x10];
    local_160 = param_1[0x11];
    local_15c = param_1[0x12];
    local_158 = (float)param_1[0x22];
    local_154 = param_1[0x23];
    local_150 = param_1[0x24];
    local_140 = param_1[0xc];
    iVar1 = zz_0033c9c_((int)&local_170,param_2);
    if (iVar1 == 0) {
      bVar3 = FUN_80039da4((float *)(param_1 + 0xd),(float *)(param_2 + 0x30),
                           (float *)(param_2 + 0xc),&local_17c);
      if (bVar3 != 0) {
        local_164 = local_17c;
        local_160 = local_178;
        local_15c = local_174;
        local_158 = local_17c;
        local_154 = local_178;
        local_150 = local_174;
        local_140 = param_1[0xc];
        iVar1 = zz_0033c9c_((int)&local_170,param_2);
        if (iVar1 != 0) {
          return 1;
        }
      }
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}



// ==== 80034fb4  FUN_80034fb4 ====

/* WARNING: Removing unreachable block (ram,0x800350d4) */
/* WARNING: Removing unreachable block (ram,0x80034fc4) */

undefined4 FUN_80034fb4(int param_1,int param_2)

{
  byte bVar1;
  double dVar2;
  double dVar3;
  float afStack_38 [3];
  float afStack_2c [4];
  
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0x34),afStack_2c);
  dVar2 = gnt4_PSQUATDotProduct_bl(afStack_2c,(float *)(param_2 + 100));
  bVar1 = dVar2 < (double)FLOAT_80436f68;
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0x40),afStack_2c);
  dVar2 = gnt4_PSQUATDotProduct_bl(afStack_2c,(float *)(param_2 + 0x70));
  if (dVar2 < (double)FLOAT_80436f68) {
    bVar1 = bVar1 | 2;
  }
  if (bVar1 == 0) {
    gnt4_PSQUATScale_bl(dVar2,(float *)(param_2 + 0x70),afStack_2c);
    gnt4_PSVECAdd_bl((float *)(param_2 + 0x40),afStack_2c,afStack_2c);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),afStack_2c,afStack_38);
    dVar3 = gnt4_PSVECMag_bl(afStack_38);
    dVar2 = (double)(*(float *)(param_1 + 0x30) + *(float *)(param_2 + 0x30));
    if (dVar3 < dVar2) {
      dVar2 = (double)(float)(dVar2 - dVar3);
      gnt4_PSVECSubtract_bl(afStack_2c,(float *)(param_1 + 0xc),afStack_2c);
      FUN_800358f4(dVar2,*(int *)(param_1 + 4),*(int *)(param_2 + 4),afStack_2c);
      return 1;
    }
  }
  else if (bVar1 < 4) {
    return 0;
  }
  return 0;
}



// ==== 800350f8  FUN_800350f8 ====

/* WARNING: Removing unreachable block (ram,0x80035428) */
/* WARNING: Removing unreachable block (ram,0x80035420) */
/* WARNING: Removing unreachable block (ram,0x80035110) */
/* WARNING: Removing unreachable block (ram,0x80035108) */

undefined4 FUN_800350f8(int param_1,int param_2)

{
  byte bVar2;
  uint uVar1;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  float *pfVar6;
  float *pfVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  char *pcVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  float afStack_c8 [3];
  float local_bc;
  float local_b8;
  undefined4 local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  undefined4 local_98;
  undefined4 local_94;
  undefined4 local_90;
  undefined4 local_8c;
  undefined4 local_88;
  undefined4 local_84;
  float afStack_80 [15];
  
  iVar9 = *(int *)(*(int *)(param_1 + 4) + 0x20);
  if (iVar9 != 0) {
    dVar16 = (double)FLOAT_80436f7c;
    pcVar12 = &DAT_802cffc8;
    iVar8 = 0;
    iVar10 = 0;
    iVar3 = param_2;
    iVar11 = param_2;
    do {
      if (dVar16 <= (double)*(float *)(iVar11 + 0x94)) {
        gnt4_PSVECSubtract_bl
                  ((float *)(param_1 + 0xc),(float *)(param_2 + *pcVar12 * 0xc + 0x30),afStack_c8);
        dVar13 = gnt4_PSQUATDotProduct_bl(afStack_c8,(float *)(iVar11 + 0x90));
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0x18),(float *)(iVar3 + 0x120),afStack_c8);
        dVar14 = gnt4_PSQUATDotProduct_bl(afStack_c8,(float *)(iVar11 + 0x9c));
        dVar15 = (double)*(float *)(param_1 + 0x30);
        dVar13 = (double)(float)(dVar13 - dVar15);
        if ((((dVar13 <= (double)FLOAT_80436f68) &&
             ((double)FLOAT_80436f68 <= (double)(float)(dVar14 - dVar15))) ||
            ((dVar13 <= (double)FLOAT_80436f68 && (-dVar15 <= dVar13)))) ||
           (((*(char *)(iVar9 + 0x1de) != '\0' && (*(int *)(param_2 + 4) == *(int *)(iVar9 + 0x1e0))
             ) && (dVar13 <= (double)FLOAT_80436f68)))) {
          local_b0 = *(float *)(param_1 + 0xc);
          local_a8 = *(float *)(param_1 + 0x14);
          local_ac = *(float *)(param_1 + 0x10) + FLOAT_80436fec;
          local_a0 = *(float *)(param_1 + 0x10) - FLOAT_80436fec;
          local_a4 = local_b0;
          local_9c = local_a8;
          bVar2 = FUN_80039da4(&local_b0,(float *)(iVar11 + 0x90),
                               (float *)(param_2 + *pcVar12 * 0xc + 0x30),&local_bc);
          if (bVar2 != 0) {
            pfVar7 = (float *)(param_2 + (char)(&DAT_802cffc8)[iVar10] * 0xc + 0x30);
            local_b0 = *pfVar7;
            local_ac = pfVar7[1];
            pfVar6 = (float *)(param_2 + (char)(&DAT_802cffc9)[iVar10] * 0xc + 0x30);
            local_a8 = pfVar7[2];
            puVar5 = (undefined4 *)(param_2 + (char)(&DAT_802cffca)[iVar10] * 0xc + 0x30);
            local_a4 = *pfVar6;
            local_a0 = pfVar6[1];
            puVar4 = (undefined4 *)(param_2 + (char)(&DAT_802cffcb)[iVar10] * 0xc + 0x30);
            local_9c = pfVar6[2];
            local_98 = *puVar5;
            local_94 = puVar5[1];
            local_90 = puVar5[2];
            local_8c = *puVar4;
            local_88 = puVar4[1];
            local_84 = puVar4[2];
            uVar1 = zz_0039c20_(&local_bc,&local_b0,(float *)(iVar11 + 0x90));
            if (uVar1 != 0) {
              zz_0035b3c_(dVar13,*(int *)(param_1 + 4),*(int *)(param_2 + 4),
                          (float *)(param_2 + iVar8 * 0x18 + 0x90));
              local_bc = *(float *)(iVar9 + 0x20);
              local_b8 = *(float *)(iVar9 + 0x24);
              local_b4 = *(undefined4 *)(iVar9 + 0x28);
              if (*(char *)(iVar9 + 0x83) == '\0') {
                local_b8 = local_b8 + *(float *)(iVar9 + 0x6d0);
              }
              gnt4_PSMTXCopy_bl(*(float **)(param_2 + 8),afStack_80);
              gnt4_PSMTXInverse_bl(afStack_80,afStack_80);
              gnt4_PSMTXMultVec_bl(afStack_80,&local_bc,(float *)(iVar9 + 0x1f8));
              iVar3 = *(int *)(*(int *)(param_2 + 4) + 0x20);
              if (iVar3 != 0) {
                gnt4_PSVECSubtract_bl
                          ((float *)(iVar9 + 0x1f8),(float *)(iVar3 + 0x1cc),
                           (float *)(iVar9 + 0x1f8));
              }
              return 1;
            }
          }
        }
      }
      iVar8 = iVar8 + 1;
      pcVar12 = pcVar12 + 4;
      iVar3 = iVar3 + 0xc;
      iVar10 = iVar10 + 4;
      iVar11 = iVar11 + 0x18;
    } while (iVar8 < 6);
  }
  return 0;
}



// ==== 80035444  FUN_80035444 ====

/* WARNING: Removing unreachable block (ram,0x8003567c) */
/* WARNING: Removing unreachable block (ram,0x80035674) */
/* WARNING: Removing unreachable block (ram,0x8003545c) */
/* WARNING: Removing unreachable block (ram,0x80035454) */

undefined4 FUN_80035444(int param_1,int param_2)

{
  byte bVar2;
  uint uVar1;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  float afStack_98 [3];
  float local_8c;
  float local_88;
  undefined4 local_84;
  float local_80;
  float local_7c;
  undefined4 local_78;
  float local_74;
  float local_70;
  undefined4 local_6c;
  float afStack_68 [12];
  
  iVar6 = *(int *)(*(int *)(param_1 + 4) + 0x20);
  if (iVar6 != 0) {
    dVar10 = (double)FLOAT_80436f68;
    iVar4 = 0;
    iVar3 = param_2;
    iVar5 = param_2;
    do {
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0x4c),afStack_98);
      dVar8 = gnt4_PSQUATDotProduct_bl(afStack_98,(float *)(iVar5 + 0x7c));
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x18),(float *)(param_2 + 0xac),afStack_98);
      dVar9 = gnt4_PSQUATDotProduct_bl(afStack_98,(float *)(iVar5 + 0x88));
      dVar7 = (double)(float)((double)*(float *)(param_1 + 0x30) +
                             (double)*(float *)(param_2 + 0x30));
      dVar8 = (double)(float)(dVar8 - dVar7);
      if ((((dVar8 <= dVar10) && (dVar10 <= (double)(float)(dVar9 - dVar7))) ||
          ((dVar8 <= (double)FLOAT_80436f68 && (-(double)*(float *)(param_1 + 0x30) <= dVar8)))) ||
         (((*(char *)(iVar6 + 0x1de) != '\0' && (*(int *)(param_2 + 4) == *(int *)(iVar6 + 0x1e0)))
          && (dVar8 <= (double)FLOAT_80436f68)))) {
        local_80 = *(float *)(param_1 + 0xc);
        local_78 = *(undefined4 *)(param_1 + 0x14);
        local_7c = *(float *)(param_1 + 0x10) + FLOAT_80436fec;
        local_70 = *(float *)(param_1 + 0x10) - FLOAT_80436fec;
        local_74 = local_80;
        local_6c = local_78;
        bVar2 = FUN_80039da4(&local_80,(float *)(iVar5 + 0x7c),(float *)(param_2 + 0x4c),&local_8c);
        if ((bVar2 != 0) &&
           (uVar1 = zz_0039aec_(&local_8c,(float *)(iVar3 + 0x34),(float *)(iVar5 + 0x7c)),
           uVar1 != 0)) {
          zz_0035b3c_(dVar8,*(int *)(param_1 + 4),*(int *)(param_2 + 4),
                      (float *)(param_2 + iVar4 * 0x18 + 0x7c));
          local_8c = *(float *)(iVar6 + 0x20);
          local_88 = *(float *)(iVar6 + 0x24);
          local_84 = *(undefined4 *)(iVar6 + 0x28);
          if (*(char *)(iVar6 + 0x83) == '\0') {
            local_88 = local_88 + *(float *)(iVar6 + 0x6d0);
          }
          gnt4_PSMTXCopy_bl(*(float **)(param_2 + 8),afStack_68);
          gnt4_PSMTXInverse_bl(afStack_68,afStack_68);
          gnt4_PSMTXMultVec_bl(afStack_68,&local_8c,(float *)(iVar6 + 0x1f8));
          iVar3 = *(int *)(*(int *)(param_2 + 4) + 0x20);
          if (iVar3 != 0) {
            gnt4_PSVECSubtract_bl
                      ((float *)(iVar6 + 0x1f8),(float *)(iVar3 + 0x1cc),(float *)(iVar6 + 0x1f8));
          }
          return 1;
        }
      }
      iVar4 = iVar4 + 1;
      iVar3 = iVar3 + 0x24;
      iVar5 = iVar5 + 0x18;
    } while (iVar4 < 2);
  }
  return 0;
}



// ==== 80035698  FUN_80035698 ====

/* WARNING: Removing unreachable block (ram,0x800358d0) */
/* WARNING: Removing unreachable block (ram,0x800356a8) */

undefined4 FUN_80035698(int param_1,int param_2)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  float afStack_98 [3];
  float afStack_8c [3];
  float local_80;
  float local_7c;
  undefined4 local_78;
  float local_74;
  float local_70;
  undefined4 local_6c;
  float local_68;
  float local_64;
  undefined4 local_60;
  float afStack_5c [16];
  
  iVar3 = *(int *)(*(int *)(param_1 + 4) + 0x20);
  if (iVar3 != 0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0xc),afStack_98);
    dVar4 = gnt4_PSQUATDotProduct_bl(afStack_98,(float *)(param_2 + 0x30));
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x18),(float *)(param_2 + 0x18),afStack_98);
    dVar5 = gnt4_PSQUATDotProduct_bl(afStack_98,(float *)(param_2 + 0x3c));
    dVar6 = (double)(float)((double)*(float *)(param_1 + 0x30) + (double)*(float *)(param_2 + 0x48))
    ;
    dVar4 = (double)(float)(dVar4 - dVar6);
    if ((((dVar4 <= (double)FLOAT_80436f68) &&
         ((double)FLOAT_80436f68 <= (double)(float)(dVar5 - dVar6))) ||
        ((dVar4 <= (double)FLOAT_80436f68 && (-(double)*(float *)(param_1 + 0x30) <= dVar4)))) ||
       (((*(char *)(iVar3 + 0x1de) != '\0' && (*(int *)(param_2 + 4) == *(int *)(iVar3 + 0x1e0))) &&
        (dVar4 <= (double)FLOAT_80436f68)))) {
      local_74 = *(float *)(param_1 + 0xc);
      local_6c = *(undefined4 *)(param_1 + 0x14);
      local_70 = *(float *)(param_1 + 0x10) + FLOAT_80436fec;
      local_64 = *(float *)(param_1 + 0x10) - FLOAT_80436fec;
      local_68 = local_74;
      local_60 = local_6c;
      gnt4_PSQUATScale_bl((double)*(float *)(param_2 + 0x48),(float *)(param_2 + 0x30),afStack_98);
      gnt4_PSVECAdd_bl((float *)(param_2 + 0xc),afStack_98,afStack_8c);
      bVar1 = FUN_80039da4(&local_74,(float *)(param_2 + 0x30),afStack_8c,&local_80);
      if (bVar1 != 0) {
        gnt4_PSVECSubtract_bl(&local_80,afStack_8c,afStack_98);
        dVar5 = gnt4_PSVECMag_bl(afStack_98);
        if (dVar5 <= (double)*(float *)(param_2 + 0x4c)) {
          zz_0035b3c_(dVar4,*(int *)(param_1 + 4),*(int *)(param_2 + 4),(float *)(param_2 + 0x30));
          local_80 = *(float *)(iVar3 + 0x20);
          local_7c = *(float *)(iVar3 + 0x24);
          local_78 = *(undefined4 *)(iVar3 + 0x28);
          if (*(char *)(iVar3 + 0x83) == '\0') {
            local_7c = local_7c + *(float *)(iVar3 + 0x6d0);
          }
          gnt4_PSMTXCopy_bl(*(float **)(param_2 + 8),afStack_5c);
          gnt4_PSMTXInverse_bl(afStack_5c,afStack_5c);
          gnt4_PSMTXMultVec_bl(afStack_5c,&local_80,(float *)(iVar3 + 0x1f8));
          iVar2 = *(int *)(*(int *)(param_2 + 4) + 0x20);
          if (iVar2 != 0) {
            gnt4_PSVECSubtract_bl
                      ((float *)(iVar3 + 0x1f8),(float *)(iVar2 + 0x1cc),(float *)(iVar3 + 0x1f8));
          }
          return 1;
        }
      }
    }
  }
  return 0;
}



// ==== 800358f4  FUN_800358f4 ====

/* WARNING: Removing unreachable block (ram,0x80035b1c) */
/* WARNING: Removing unreachable block (ram,0x80035b14) */
/* WARNING: Removing unreachable block (ram,0x80035b0c) */
/* WARNING: Removing unreachable block (ram,0x80035914) */
/* WARNING: Removing unreachable block (ram,0x8003590c) */
/* WARNING: Removing unreachable block (ram,0x80035904) */

void FUN_800358f4(double param_1,int param_2,int param_3,float *param_4)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  
  iVar3 = *(int *)(param_3 + 0x20);
  iVar2 = *(int *)(param_2 + 0x20);
  if ((*(byte *)(iVar3 + 0x2ac) & 4) != 0) {
    iVar3 = *(int *)(param_3 + 0x24);
  }
  if ((*(byte *)(iVar2 + 0x2ac) & 4) != 0) {
    iVar2 = *(int *)(param_2 + 0x24);
  }
  local_4c = *param_4;
  local_48 = param_4[1];
  local_44 = param_4[2];
  dVar4 = gnt4_PSVECSquareMag_bl(&local_4c);
  if ((double)FLOAT_80436f68 < dVar4) {
    if (param_1 <= (double)FLOAT_80436f68) {
      if ((double)FLOAT_80436ff4 < param_1) {
        param_1 = (double)FLOAT_80436ff4;
      }
    }
    else if (param_1 < (double)FLOAT_80436ff0) {
      param_1 = (double)FLOAT_80436ff0;
    }
    gnt4_PSVECNormalize_bl(&local_4c,&local_4c);
    local_58 = local_4c;
    local_54 = local_48;
    local_50 = local_44;
    dVar4 = (double)*(float *)(iVar3 + 0x204);
    if ((double)*(float *)(iVar3 + 0x204) <= (double)FLOAT_80436f78) {
      dVar4 = (double)FLOAT_80436f78;
    }
    dVar5 = (double)*(float *)(iVar2 + 0x204);
    if ((double)*(float *)(iVar2 + 0x204) <= (double)FLOAT_80436f78) {
      dVar5 = (double)FLOAT_80436f78;
    }
    bVar1 = zz_008b480_();
    if (bVar1 != 0) {
      if (*(char *)(iVar3 + 0x83) == '\0') {
        if ((bVar1 & *(byte *)(iVar3 + 0x3e5)) == 0) {
          dVar4 = (double)FLOAT_80436f90;
        }
      }
      else {
        dVar4 = (double)FLOAT_80436f90;
      }
      if (*(char *)(iVar2 + 0x83) == '\0') {
        if ((bVar1 & *(byte *)(iVar2 + 0x3e5)) == 0) {
          dVar5 = (double)FLOAT_80436f90;
        }
      }
      else {
        dVar5 = (double)FLOAT_80436f90;
      }
    }
    if ((dVar4 < (double)FLOAT_80436f90) || ((double)FLOAT_80436f90 <= dVar5)) {
      if ((dVar5 < (double)FLOAT_80436f90) || ((double)FLOAT_80436f90 <= dVar4)) {
        dVar4 = (double)(float)(param_1 * (double)(float)(dVar5 / (double)(float)(dVar4 + dVar5)));
        gnt4_PSQUATScale_bl(dVar4,&local_4c,&local_4c);
        zz_0035ca4_(iVar3,&local_4c);
        gnt4_PSQUATScale_bl(-(double)(float)(param_1 - dVar4),&local_58,&local_58);
        zz_0035ca4_(iVar2,&local_58);
      }
      else {
        gnt4_PSQUATScale_bl(param_1,&local_4c,&local_4c);
        zz_0035ca4_(iVar3,&local_4c);
      }
    }
    else {
      gnt4_PSQUATScale_bl(-param_1,&local_58,&local_58);
      zz_0035ca4_(iVar2,&local_58);
    }
  }
  return;
}



// ==== 80035b3c  zz_0035b3c_ ====

/* WARNING: Removing unreachable block (ram,0x80035c7c) */
/* WARNING: Removing unreachable block (ram,0x80035b4c) */

void zz_0035b3c_(double param_1,int param_2,int param_3,float *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  float afStack_38 [3];
  float local_2c;
  float local_28;
  float local_24;
  
  iVar3 = *(int *)(param_3 + 0x20);
  iVar2 = *(int *)(param_2 + 0x20);
  local_2c = *param_4;
  local_28 = param_4[1];
  local_24 = param_4[2];
  dVar4 = gnt4_PSVECSquareMag_bl(&local_2c);
  if ((double)FLOAT_80436f68 < dVar4) {
    if (param_1 <= (double)FLOAT_80436f68) {
      if ((double)FLOAT_80436ff4 < param_1) {
        param_1 = (double)FLOAT_80436ff4;
      }
    }
    else if (param_1 < (double)FLOAT_80436ff0) {
      param_1 = (double)FLOAT_80436ff0;
    }
    iVar1 = *(int *)(param_2 + 0x28);
    gnt4_PSVECNormalize_bl(&local_2c,&local_2c);
    if ((((*(ushort *)(iVar1 + 2) & 0x10) != 0) && (FLOAT_80436f7c <= local_28)) &&
       ((*(char *)(iVar3 + 0x1db) == '\0' || (*(int *)(iVar3 + 0x1e4) != iVar2)))) {
      *(undefined1 *)(iVar2 + 0x1db) = 1;
      if (*(char *)(iVar2 + 0x83) == '\0') {
        *(byte *)(iVar3 + 0x1dc) = *(byte *)(iVar3 + 0x1dc) | *(byte *)(iVar2 + 0x3e5);
      }
      *(int *)(iVar2 + 0x1e0) = param_3;
      *(int *)(iVar2 + 0x1e4) = iVar3;
      *(float *)(iVar2 + 0x1ec) = local_2c;
      *(float *)(iVar2 + 0x1f0) = local_28;
      *(float *)(iVar2 + 500) = local_24;
      gnt4_PSQUATScale_bl((double)(float)(-param_1 - (double)*(float *)(iVar1 + 0x18)),&local_2c,
                          afStack_38);
      zz_0035ca4_(iVar2,afStack_38);
    }
  }
  return;
}



// ==== 80035ca4  zz_0035ca4_ ====

void zz_0035ca4_(int param_1,float *param_2)

{
  char cVar1;
  byte bVar2;
  char *pcVar3;
  char *pcVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int local_38 [8];
  
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x1cc),(float *)(param_1 + 0x20));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x1cc),param_2,(float *)(param_1 + 0x1cc));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x1cc),(float *)(param_1 + 0x20));
  piVar8 = local_38;
  iVar7 = 0;
  *(byte *)(param_1 + 0x1dd) = *(byte *)(param_1 + 0x1dd) | 1;
  pcVar3 = DAT_803c4e84;
  piVar5 = piVar8;
  do {
    cVar1 = *pcVar3;
    *piVar5 = 0;
    if ((cVar1 != '\0') && (((int)*(char *)(param_1 + 0x1dc) & 1 << iVar7) != 0)) {
      gnt4_PSVECSubtract_bl
                ((float *)(pcVar3 + 0x20),(float *)(pcVar3 + 0x1cc),(float *)(pcVar3 + 0x20));
      gnt4_PSVECAdd_bl((float *)(pcVar3 + 0x1cc),param_2,(float *)(pcVar3 + 0x1cc));
      gnt4_PSVECAdd_bl((float *)(pcVar3 + 0x20),(float *)(pcVar3 + 0x1cc),(float *)(pcVar3 + 0x20));
      bVar2 = pcVar3[0x1dd];
      *piVar5 = 1;
      pcVar3[0x1dd] = bVar2 | 1;
    }
    iVar7 = iVar7 + 1;
    pcVar3 = pcVar3 + 0x1e00;
    piVar5 = piVar5 + 1;
  } while (iVar7 < 6);
  iVar7 = 0;
  pcVar3 = DAT_803c4e84;
  do {
    if (*pcVar3 != '\0') {
      if (*piVar8 != 0) {
        iVar6 = 0;
        pcVar4 = DAT_803c4e84;
        do {
          if ((*pcVar4 != '\0') && (((int)pcVar3[0x1dc] & 1 << iVar6) != 0)) {
            gnt4_PSVECSubtract_bl
                      ((float *)(pcVar4 + 0x20),(float *)(pcVar4 + 0x1cc),(float *)(pcVar4 + 0x20));
            gnt4_PSVECAdd_bl((float *)(pcVar4 + 0x1cc),param_2,(float *)(pcVar4 + 0x1cc));
            gnt4_PSVECAdd_bl((float *)(pcVar4 + 0x20),(float *)(pcVar4 + 0x1cc),
                             (float *)(pcVar4 + 0x20));
            pcVar4[0x1dd] = pcVar4[0x1dd] | 1;
          }
          iVar6 = iVar6 + 1;
          pcVar4 = pcVar4 + 0x1e00;
        } while (iVar6 < 6);
      }
    }
    iVar7 = iVar7 + 1;
    pcVar3 = pcVar3 + 0x1e00;
    piVar8 = piVar8 + 1;
  } while (iVar7 < 6);
  return;
}



// ==== 80035e58  FUN_80035e58 ====

/* WARNING: Removing unreachable block (ram,0x80036d58) */
/* WARNING: Removing unreachable block (ram,0x80036d50) */
/* WARNING: Removing unreachable block (ram,0x80036d48) */
/* WARNING: Removing unreachable block (ram,0x80035e78) */
/* WARNING: Removing unreachable block (ram,0x80035e70) */
/* WARNING: Removing unreachable block (ram,0x80035e68) */

undefined4 FUN_80035e58(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  int iVar7;
  float *pfVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  char cVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  float local_128;
  float local_124;
  float local_120;
  float local_11c;
  float local_118;
  float local_114;
  float afStack_110 [3];
  float fStack_104;
  float local_100;
  float local_f8;
  float local_f4;
  float local_f0;
  float local_ec;
  float local_e8;
  float local_e4;
  float local_e0 [4];
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c8;
  undefined4 local_c4;
  undefined4 local_c0;
  float local_bc;
  undefined4 local_b8;
  undefined4 local_b4;
  double local_b0;
  double local_a8;
  double local_a0;
  double local_98;
  int local_90;
  int local_8c;
  int local_88;
  int local_84;
  int local_80;
  int local_7c;
  
  iVar10 = *(int *)(*(int *)(param_1 + 4) + 0x20);
  if (((*(byte *)(iVar10 + 0x2ac) & 4) == 0) ||
     (iVar10 = *(int *)(*(int *)(param_1 + 4) + 0x24),
     *(float *)(iVar10 + 0x24) <= *(float *)(param_1 + 0x10))) {
    gnt4_PSVECAdd_bl((float *)(iVar10 + 0x1cc),(float *)(param_1 + 0xc),&local_ec);
    iVar5 = zz_003fb00_(&local_ec);
    if (iVar5 == 0) {
      uVar4 = 0;
    }
    else {
      iVar11 = *(int *)(DAT_8043625c + 0x20);
      uVar4 = 0;
      cVar13 = '\0';
      local_b0 = (double)(CONCAT44(0x43300000,*(undefined4 *)(iVar11 + 0x10)) ^ 0x80000000);
      local_a0 = (double)(CONCAT44(0x43300000,*(undefined4 *)(iVar11 + 0x14)) ^ 0x80000000);
      dVar17 = (double)*(float *)(param_1 + 0x30);
      iVar5 = (int)(local_ec - (float)(local_b0 - DOUBLE_80436f88));
      local_a8 = (double)(longlong)iVar5;
      iVar12 = (int)(local_e4 - (float)(local_a0 - DOUBLE_80436f88));
      local_98 = (double)(longlong)iVar12;
      iVar2 = iVar5 / 500 + (iVar5 >> 0x1f);
      local_8c = iVar2 - (iVar2 >> 0x1f);
      iVar3 = iVar12 / 500 + (iVar12 >> 0x1f);
      local_88 = iVar3 - (iVar3 >> 0x1f);
      if (dVar17 < (double)FLOAT_80436ff8) {
        iVar7 = 2;
        if ((iVar5 + (iVar2 - (iVar2 >> 0x1f)) * -500 < 0xfa) &&
           (local_8c = local_8c + -1, local_8c < 0)) {
          local_8c = 0;
        }
        if ((iVar12 + (iVar3 - (iVar3 >> 0x1f)) * -500 < 0xfa) &&
           (local_88 = local_88 + -1, local_88 < 0)) {
          local_88 = 0;
        }
      }
      else if ((double)FLOAT_80436ffc < dVar17) {
        if ((double)FLOAT_80437000 <= dVar17) {
          dVar17 = (double)FLOAT_80437000;
        }
        iVar7 = 5;
        local_8c = local_8c + -2;
        if (local_8c < 0) {
          local_8c = 0;
        }
        local_88 = local_88 + -2;
        if (local_88 < 0) {
          local_88 = 0;
        }
      }
      else {
        iVar7 = 3;
        local_8c = local_8c + -1;
        if (local_8c < 0) {
          local_8c = 0;
        }
        local_88 = local_88 + -1;
        if (local_88 < 0) {
          local_88 = 0;
        }
      }
      dVar16 = (double)(float)(dVar17 * dVar17);
      for (local_90 = 0; local_90 < iVar7; local_90 = local_90 + 1) {
        if (*(int *)(iVar11 + 8) < local_8c) {
          local_8c = *(int *)(iVar11 + 8);
        }
        iVar5 = local_88;
        for (iVar12 = 0; iVar12 < iVar7; iVar12 = iVar12 + 1) {
          iVar2 = *(int *)(iVar11 + 0xc);
          if (iVar2 < iVar5) {
            iVar5 = iVar2;
          }
          for (piVar9 = *(int **)(*(int *)(iVar11 + 0x18) + (iVar5 + local_8c * iVar2) * 4);
              iVar2 = *piVar9, iVar2 != -1; piVar9 = piVar9 + 1) {
            local_128 = *(float *)(iVar2 + 0x28);
            local_124 = *(float *)(iVar2 + 0x2c);
            local_120 = *(float *)(iVar2 + 0x30);
            gnt4_PSVECSubtract_bl((float *)(param_1 + 0x18),(float *)(iVar2 + 4),&local_11c);
            dVar15 = gnt4_PSQUATDotProduct_bl(&local_11c,&local_128);
            gnt4_PSVECSubtract_bl(&local_ec,(float *)(iVar2 + 4),&local_11c);
            dVar14 = gnt4_PSQUATDotProduct_bl(&local_11c,&local_128);
            if (((dVar14 <= dVar17) && ((double)FLOAT_80436f68 <= dVar14)) &&
               ((double)FLOAT_80436f68 <= dVar15)) {
              uVar6 = zz_0039aec_(&local_ec,(float *)(iVar2 + 4),&local_128);
              if (uVar6 == 0) {
                local_e0[0] = *(float *)(iVar2 + 4);
                pfVar8 = local_e0;
                local_e0[1] = *(float *)(iVar2 + 8);
                iVar3 = 0;
                local_e0[2] = *(float *)(iVar2 + 0xc);
                local_e0[3] = *(float *)(iVar2 + 0x10);
                local_d0 = *(undefined4 *)(iVar2 + 0x14);
                local_cc = *(undefined4 *)(iVar2 + 0x18);
                local_c8 = *(undefined4 *)(iVar2 + 0x1c);
                local_c4 = *(undefined4 *)(iVar2 + 0x20);
                local_c0 = *(undefined4 *)(iVar2 + 0x24);
                local_bc = local_e0[0];
                local_b8 = local_e0[1];
                local_b4 = local_e0[2];
                do {
                  gnt4_PSVECSubtract_bl(local_e0 + (iVar3 + 1) * 3,pfVar8,&local_11c);
                  fVar1 = ((local_11c * -(*pfVar8 - local_ec) - local_118 * (pfVar8[1] - local_e8))
                          - local_114 * (pfVar8[2] - local_e4)) /
                          (local_11c * local_11c + local_118 * local_118 + local_114 * local_114);
                  local_f8 = *pfVar8 + local_11c * fVar1;
                  local_f4 = pfVar8[1] + local_118 * fVar1;
                  local_f0 = pfVar8[2] + local_114 * fVar1;
                  dVar15 = gnt4_PSVECSquareDistance_bl(&local_f8,&local_ec);
                  if (dVar15 <= dVar16) {
                    gnt4_PSVECSubtract_bl(&local_f8,pfVar8,&fStack_104);
                    gnt4_PSVECSubtract_bl(&local_f8,local_e0 + (iVar3 + 1) * 3,afStack_110);
                    dVar15 = gnt4_PSQUATDotProduct_bl(&fStack_104,afStack_110);
                    if ((double)FLOAT_80436f68 <= dVar15) {
                      dVar15 = gnt4_PSVECSquareDistance_bl(pfVar8,&local_ec);
                      if (dVar15 <= dVar16) {
                        gnt4_PSVECSubtract_bl(&local_ec,pfVar8,&local_11c);
                        gnt4_PSVECNormalize_bl(&local_11c,&local_11c);
                        gnt4_PSQUATScale_bl(dVar17,&local_11c,&local_11c);
                        gnt4_PSVECAdd_bl(pfVar8,&local_11c,&fStack_104);
                        gnt4_PSVECSubtract_bl(&fStack_104,&local_ec,&fStack_104);
                        *(byte *)(iVar10 + 0x274) = *(byte *)(iVar10 + 0x274) | 1;
                        zz_0035ca4_(iVar10,&fStack_104);
                        gnt4_PSVECAdd_bl((float *)(iVar10 + 0x1cc),(float *)(param_1 + 0xc),
                                         &local_ec);
                        uVar4 = 1;
                        cVar13 = cVar13 + '\x01';
                      }
                    }
                    else {
                      gnt4_PSVECSubtract_bl(&local_ec,&local_f8,&local_11c);
                      gnt4_PSVECNormalize_bl(&local_11c,&local_11c);
                      gnt4_PSQUATScale_bl(dVar17,&local_11c,&local_11c);
                      gnt4_PSVECAdd_bl(&local_f8,&local_11c,&local_f8);
                      gnt4_PSVECSubtract_bl(&local_f8,&local_ec,&local_f8);
                      *(byte *)(iVar10 + 0x274) = *(byte *)(iVar10 + 0x274) | 1;
                      zz_0035ca4_(iVar10,&local_f8);
                      gnt4_PSVECAdd_bl((float *)(iVar10 + 0x1cc),(float *)(param_1 + 0xc),&local_ec)
                      ;
                      uVar4 = 1;
                      cVar13 = cVar13 + '\x01';
                    }
                  }
                  iVar3 = iVar3 + 1;
                  pfVar8 = pfVar8 + 3;
                } while (iVar3 < 3);
              }
              else {
                fVar1 = ((-(local_128 * (local_ec - *(float *)(iVar2 + 4))) -
                         local_124 * (local_e8 - *(float *)(iVar2 + 8))) -
                        local_120 * (local_e4 - *(float *)(iVar2 + 0xc))) /
                        (local_128 * local_128 + local_124 * local_124 + local_120 * local_120);
                local_f8 = local_ec + local_128 * fVar1;
                local_f4 = local_e8 + local_124 * fVar1;
                local_f0 = local_e4 + local_120 * fVar1;
                gnt4_PSQUATScale_bl(dVar17,&local_128,&fStack_104);
                gnt4_PSVECAdd_bl(&local_f8,&fStack_104,&local_f8);
                gnt4_PSVECSubtract_bl(&local_f8,&local_ec,&local_f8);
                *(byte *)(iVar10 + 0x274) = *(byte *)(iVar10 + 0x274) | 1;
                zz_0035ca4_(iVar10,&local_f8);
                gnt4_PSVECAdd_bl((float *)(iVar10 + 0x1cc),(float *)(param_1 + 0xc),&local_ec);
                uVar4 = 1;
                cVar13 = cVar13 + '\x01';
              }
            }
          }
          iVar5 = iVar5 + 1;
        }
        local_8c = local_8c + 1;
      }
      if (*(char *)(iVar10 + 0x83) == '\0') {
        (&DAT_80436144)[*(char *)(iVar10 + 0x3e4)] =
             (&DAT_80436144)[*(char *)(iVar10 + 0x3e4)] + cVar13;
      }
      iVar11 = *(int *)(DAT_8043625c + 0x24);
      local_98 = (double)(CONCAT44(0x43300000,*(undefined4 *)(iVar11 + 0x10)) ^ 0x80000000);
      local_a8 = (double)(CONCAT44(0x43300000,*(undefined4 *)(iVar11 + 0x14)) ^ 0x80000000);
      iVar5 = (int)(local_ec - (float)(local_98 - DOUBLE_80436f88));
      local_a0 = (double)(longlong)iVar5;
      iVar12 = (int)(local_e4 - (float)(local_a8 - DOUBLE_80436f88));
      local_b0 = (double)(longlong)iVar12;
      iVar2 = iVar5 / 500 + (iVar5 >> 0x1f);
      local_7c = iVar2 - (iVar2 >> 0x1f);
      iVar3 = iVar12 / 500 + (iVar12 >> 0x1f);
      local_80 = iVar3 - (iVar3 >> 0x1f);
      if (iVar7 == 3) {
        local_7c = local_7c + -1;
        if (local_7c < 0) {
          local_7c = 0;
        }
        local_80 = local_80 + -1;
        if (local_80 < 0) {
          local_80 = 0;
        }
      }
      else {
        if ((iVar5 + (iVar2 - (iVar2 >> 0x1f)) * -500 < 0xfa) &&
           (local_7c = local_7c + -1, local_7c < 0)) {
          local_7c = 0;
        }
        if ((iVar12 + (iVar3 - (iVar3 >> 0x1f)) * -500 < 0xfa) &&
           (local_80 = local_80 + -1, local_80 < 0)) {
          local_80 = 0;
        }
      }
      for (local_84 = 0; local_84 < iVar7; local_84 = local_84 + 1) {
        if (*(int *)(iVar11 + 8) < local_7c) {
          local_7c = *(int *)(iVar11 + 8);
        }
        iVar5 = local_80;
        for (iVar12 = 0; iVar12 < iVar7; iVar12 = iVar12 + 1) {
          iVar2 = *(int *)(iVar11 + 0xc);
          if (iVar2 < iVar5) {
            iVar5 = iVar2;
          }
          for (piVar9 = *(int **)(*(int *)(iVar11 + 0x18) + (iVar5 + local_7c * iVar2) * 4);
              iVar2 = *piVar9, iVar2 != -1; piVar9 = piVar9 + 1) {
            local_128 = *(float *)(iVar2 + 0x28);
            local_124 = *(float *)(iVar2 + 0x2c);
            local_120 = *(float *)(iVar2 + 0x30);
            gnt4_PSVECSubtract_bl(&local_ec,(float *)(iVar2 + 4),&local_11c);
            dVar15 = gnt4_PSQUATDotProduct_bl(&local_11c,&local_128);
            if ((dVar15 <= dVar17) && ((double)FLOAT_80436f68 <= dVar15)) {
              uVar6 = zz_0039aec_(&local_ec,(float *)(iVar2 + 4),&local_128);
              if (uVar6 == 0) {
                local_e0[0] = *(float *)(iVar2 + 4);
                pfVar8 = local_e0;
                local_e0[1] = *(float *)(iVar2 + 8);
                iVar3 = 0;
                local_e0[2] = *(float *)(iVar2 + 0xc);
                local_e0[3] = *(float *)(iVar2 + 0x10);
                local_d0 = *(undefined4 *)(iVar2 + 0x14);
                local_cc = *(undefined4 *)(iVar2 + 0x18);
                local_c8 = *(undefined4 *)(iVar2 + 0x1c);
                local_c4 = *(undefined4 *)(iVar2 + 0x20);
                local_c0 = *(undefined4 *)(iVar2 + 0x24);
                local_bc = local_e0[0];
                local_b8 = local_e0[1];
                local_b4 = local_e0[2];
                do {
                  gnt4_PSVECSubtract_bl(local_e0 + (iVar3 + 1) * 3,pfVar8,&local_11c);
                  fVar1 = ((local_11c * -(*pfVar8 - local_ec) - local_118 * (pfVar8[1] - local_e8))
                          - local_114 * (pfVar8[2] - local_e4)) /
                          (local_11c * local_11c + local_118 * local_118 + local_114 * local_114);
                  local_f8 = *pfVar8 + local_11c * fVar1;
                  local_f4 = pfVar8[1] + local_118 * fVar1;
                  local_f0 = pfVar8[2] + local_114 * fVar1;
                  dVar15 = gnt4_PSVECSquareDistance_bl(&local_f8,&local_ec);
                  if (dVar15 <= dVar16) {
                    gnt4_PSVECSubtract_bl(&local_f8,pfVar8,&fStack_104);
                    gnt4_PSVECSubtract_bl(&local_f8,local_e0 + (iVar3 + 1) * 3,afStack_110);
                    dVar15 = gnt4_PSQUATDotProduct_bl(&fStack_104,afStack_110);
                    if ((double)FLOAT_80436f68 <= dVar15) {
                      dVar15 = gnt4_PSVECSquareDistance_bl(pfVar8,&local_ec);
                      if (dVar15 <= dVar16) {
                        gnt4_PSVECSubtract_bl(&local_ec,pfVar8,&local_11c);
                        gnt4_PSVECNormalize_bl(&local_11c,&local_11c);
                        gnt4_PSQUATScale_bl(dVar17,&local_11c,&local_11c);
                        gnt4_PSVECAdd_bl(pfVar8,&local_11c,&fStack_104);
                        gnt4_PSVECSubtract_bl(&fStack_104,&local_ec,&fStack_104);
                        *(byte *)(iVar10 + 0x274) = *(byte *)(iVar10 + 0x274) | 2;
                        if ((*(char *)(iVar10 + 0x83) == '\0') &&
                           (local_100 <= (float)(&DAT_803b0644)[*(char *)(iVar10 + 0x3e4)])) {
                          (&DAT_803b0644)[*(char *)(iVar10 + 0x3e4)] = local_100;
                        }
                        zz_0035ca4_(iVar10,&fStack_104);
                        FUN_80036d74(iVar10,&fStack_104);
                        gnt4_PSVECAdd_bl((float *)(iVar10 + 0x1cc),(float *)(param_1 + 0xc),
                                         &local_ec);
                        uVar4 = 1;
                      }
                    }
                    else {
                      gnt4_PSVECSubtract_bl(&local_ec,&local_f8,&local_11c);
                      gnt4_PSVECNormalize_bl(&local_11c,&local_11c);
                      gnt4_PSQUATScale_bl(dVar17,&local_11c,&local_11c);
                      gnt4_PSVECAdd_bl(&local_f8,&local_11c,&local_f8);
                      gnt4_PSVECSubtract_bl(&local_f8,&local_ec,&local_f8);
                      *(byte *)(iVar10 + 0x274) = *(byte *)(iVar10 + 0x274) | 2;
                      if ((*(char *)(iVar10 + 0x83) == '\0') &&
                         (local_f4 <= (float)(&DAT_803b0644)[*(char *)(iVar10 + 0x3e4)])) {
                        (&DAT_803b0644)[*(char *)(iVar10 + 0x3e4)] = local_f4;
                      }
                      zz_0035ca4_(iVar10,&local_f8);
                      FUN_80036d74(iVar10,&local_f8);
                      gnt4_PSVECAdd_bl((float *)(iVar10 + 0x1cc),(float *)(param_1 + 0xc),&local_ec)
                      ;
                      uVar4 = 1;
                    }
                  }
                  iVar3 = iVar3 + 1;
                  pfVar8 = pfVar8 + 3;
                } while (iVar3 < 3);
              }
              else {
                fVar1 = ((-(local_128 * (local_ec - *(float *)(iVar2 + 4))) -
                         local_124 * (local_e8 - *(float *)(iVar2 + 8))) -
                        local_120 * (local_e4 - *(float *)(iVar2 + 0xc))) /
                        (local_128 * local_128 + local_124 * local_124 + local_120 * local_120);
                local_f8 = local_ec + local_128 * fVar1;
                local_f4 = local_e8 + local_124 * fVar1;
                local_f0 = local_e4 + local_120 * fVar1;
                gnt4_PSQUATScale_bl(dVar17,&local_128,&fStack_104);
                gnt4_PSVECAdd_bl(&local_f8,&fStack_104,&local_f8);
                gnt4_PSVECSubtract_bl(&local_f8,&local_ec,&local_f8);
                *(byte *)(iVar10 + 0x274) = *(byte *)(iVar10 + 0x274) | 2;
                if ((*(char *)(iVar10 + 0x83) == '\0') &&
                   (local_f4 <= (float)(&DAT_803b0644)[*(char *)(iVar10 + 0x3e4)])) {
                  (&DAT_803b0644)[*(char *)(iVar10 + 0x3e4)] = local_f4;
                }
                zz_0035ca4_(iVar10,&local_f8);
                FUN_80036d74(iVar10,&local_f8);
                gnt4_PSVECAdd_bl((float *)(iVar10 + 0x1cc),(float *)(param_1 + 0xc),&local_ec);
                uVar4 = 1;
              }
            }
          }
          iVar5 = iVar5 + 1;
        }
        local_7c = local_7c + 1;
      }
      gnt4_PSVECAdd_bl((float *)(iVar10 + 0x1cc),(float *)(param_1 + 0xc),&local_ec);
      dVar16 = gnt4_PSVECSquareDistance_bl(&local_ec,(float *)(param_1 + 0x18));
      if ((((((double)FLOAT_80436f68 < dVar16) ||
            (*(float *)(param_1 + 0x34) < *(float *)(param_1 + 0x30))) &&
           (iVar5 = zz_003fb00_(&local_ec), iVar5 != 0)) &&
          (iVar5 = zz_003fb00_((float *)(param_1 + 0x18)), iVar5 != 0)) &&
         ((iVar5 = FUN_8003ed44((float *)(param_1 + 0x18),&local_ec,&local_f8,&local_11c),
          iVar5 == 2 || (iVar5 == 3)))) {
        gnt4_PSQUATScale_bl(dVar17,&local_11c,afStack_110);
        gnt4_PSVECAdd_bl(&local_f8,afStack_110,afStack_110);
        gnt4_PSVECSubtract_bl(afStack_110,&local_ec,&fStack_104);
        dVar17 = gnt4_PSQUATDotProduct_bl(&local_11c,&fStack_104);
        if ((double)FLOAT_80436f68 <= dVar17) {
          if (iVar5 == 2) {
            *(byte *)(iVar10 + 0x274) = *(byte *)(iVar10 + 0x274) | 1;
          }
          else {
            *(byte *)(iVar10 + 0x274) = *(byte *)(iVar10 + 0x274) | 2;
            if ((*(char *)(iVar10 + 0x83) == '\0') &&
               (local_100 <= (float)(&DAT_803b0644)[*(char *)(iVar10 + 0x3e4)])) {
              (&DAT_803b0644)[*(char *)(iVar10 + 0x3e4)] = local_100;
            }
          }
          zz_0035ca4_(iVar10,&fStack_104);
          if ((*(byte *)(iVar10 + 0x274) & 2) != 0) {
            FUN_80036d74(iVar10,&fStack_104);
          }
          uVar4 = 1;
        }
      }
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}



// ==== 80036d74  FUN_80036d74 ====

void FUN_80036d74(int param_1,float *param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  do {
    if (*(char *)(param_1 + 0x1db) == '\0') {
      return;
    }
    iVar2 = *(int *)(param_1 + 0x1e4);
    if ((*(char *)(iVar2 + 0x83) == '\0') && (*(char *)(iVar2 + 0x281) == '\0')) {
      gnt4_PSVECSubtract_bl
                ((float *)(iVar2 + 0x20),(float *)(iVar2 + 0x1cc),(float *)(iVar2 + 0x20));
      gnt4_PSVECAdd_bl((float *)(iVar2 + 0x1cc),param_2,(float *)(iVar2 + 0x1cc));
      gnt4_PSVECAdd_bl((float *)(iVar2 + 0x20),(float *)(iVar2 + 0x1cc),(float *)(iVar2 + 0x20));
      *(byte *)(iVar2 + 0x1dd) = *(byte *)(iVar2 + 0x1dd) | 1;
      param_1 = iVar2;
    }
    iVar1 = iVar1 + 1;
  } while (iVar1 < 6);
  return;
}



// ==== 80036e24  FUN_80036e24 ====

/* WARNING: Removing unreachable block (ram,0x800372c8) */
/* WARNING: Removing unreachable block (ram,0x80036e34) */

void FUN_80036e24(void)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  int *piVar7;
  int iVar8;
  char *pcVar9;
  int iVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  int local_a0;
  float afStack_9c [3];
  undefined1 auStack_90 [12];
  float local_84;
  undefined4 local_80;
  undefined4 local_7c;
  float local_78;
  undefined4 local_74;
  undefined4 local_70;
  int local_6c [13];
  
  piVar7 = local_6c;
  puVar2 = &DAT_803c73b0;
  iVar11 = 0xd;
  piVar6 = piVar7;
  do {
    puVar2[0x26f] = 0;
    puVar2 = puVar2 + 0x3e4;
    *piVar6 = 0;
    piVar6 = piVar6 + 1;
    iVar11 = iVar11 + -1;
  } while (iVar11 != 0);
  cVar1 = PTR_DAT_80433930[0x29];
  for (iVar11 = 0; iVar11 < 1 << (int)cVar1; iVar11 = iVar11 + 1) {
    iVar5 = (int)(char)PTR_DAT_80433930[iVar11 + 0xc];
    iVar10 = iVar5 * 0x3e4;
    if ((&DAT_803c73b0)[iVar10] != '\0') {
      local_78 = (float)(&DAT_803c7698)[iVar5 * 0xf9];
      local_74 = (&DAT_803c769c)[iVar5 * 0xf9];
      local_70 = (&DAT_803c76a0)[iVar5 * 0xf9];
      local_84 = (float)(&DAT_803c76b0)[iVar5 * 0xf9];
      local_80 = (&DAT_803c76b4)[iVar5 * 0xf9];
      local_7c = (&DAT_803c76b8)[iVar5 * 0xf9];
      local_6c[iVar5] = 1;
      dVar12 = gnt4_PSVECSquareDistance_bl(&local_78,&local_84);
      if ((double)FLOAT_80436f68 < dVar12) {
        gnt4_PSVECAdd_bl(&local_78,&local_84,afStack_9c);
        gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,afStack_9c,afStack_9c);
        piVar6 = &DAT_803c3b7c;
        dVar12 = (double)(float)(dVar12 * (double)FLOAT_80436f7c);
        for (iVar5 = 0; iVar5 < (int)(uint)DAT_8043624c; iVar5 = iVar5 + 1) {
          iVar4 = *piVar6;
          iVar8 = *(int *)(iVar4 + 0x20);
          if (((iVar8 != 0) && (*(char *)(iVar8 + 0x26f) != '\0')) &&
             ((*(char *)(iVar8 + 0x83) != '\0' ||
              (((int)*(char *)(iVar8 + 0x3e4) != (int)(char)(&DAT_803c7695)[iVar10] &&
               ((*(char *)((&DAT_803c4e84)[(char)(&DAT_803c7695)[iVar10]] + 0x4a0) == '\0' ||
                (*(int *)((&DAT_803c4e84)[(char)(&DAT_803c7695)[iVar10]] + 0x4a4) != iVar8)))))))) {
            dVar13 = gnt4_PSVECSquareDistance_bl((float *)(iVar4 + 100),afStack_9c);
            if ((double)FLOAT_80436f68 < dVar13) {
              dVar14 = 1.0 / SQRT(dVar13);
              dVar14 = DOUBLE_80436fd0 * dVar14 * -(dVar13 * dVar14 * dVar14 - DOUBLE_80436fd8);
              dVar14 = DOUBLE_80436fd0 * dVar14 * -(dVar13 * dVar14 * dVar14 - DOUBLE_80436fd8);
              dVar13 = (double)(float)(dVar13 * DOUBLE_80436fd0 * dVar14 *
                                                -(dVar13 * dVar14 * dVar14 - DOUBLE_80436fd8));
            }
            if ((dVar13 <= (double)(float)((double)*(float *)(iVar4 + 0x7c) + dVar12)) &&
               (iVar3 = (*(code *)(&PTR_FUN_802cffb0)[*(int *)(iVar4 + 0x58)])
                                  ((int *)(iVar4 + 0x58),&local_78,&local_84,auStack_90,&local_a0),
               iVar3 != 0)) {
              *(ushort *)(iVar8 + 0x270) =
                   *(ushort *)(iVar8 + 0x270) |
                   (ushort)(1 << (int)(char)PTR_DAT_80433930[iVar11 + 0xc]);
              if (local_a0 != 0) {
                *(ushort *)(iVar8 + 0x286) =
                     *(ushort *)(iVar8 + 0x286) |
                     (ushort)(1 << (int)(char)PTR_DAT_80433930[iVar11 + 0xc]);
              }
              if ((*(ushort *)(*(int *)(iVar4 + 0x28) + 2) & 0x800) != 0) {
                (&DAT_803c761f)[iVar10] = 1;
              }
            }
          }
          piVar6 = piVar6 + 1;
        }
      }
    }
  }
  iVar11 = 0;
  pcVar9 = &DAT_803c73b0;
  do {
    if ((*piVar7 == 0) && (*pcVar9 != '\0')) {
      local_78 = *(float *)(pcVar9 + 0x2e8);
      local_74 = *(undefined4 *)(pcVar9 + 0x2ec);
      local_70 = *(undefined4 *)(pcVar9 + 0x2f0);
      local_84 = *(float *)(pcVar9 + 0x300);
      local_80 = *(undefined4 *)(pcVar9 + 0x304);
      local_7c = *(undefined4 *)(pcVar9 + 0x308);
      dVar12 = gnt4_PSVECSquareDistance_bl(&local_78,&local_84);
      if ((double)FLOAT_80436f68 < dVar12) {
        gnt4_PSVECAdd_bl(&local_78,&local_84,afStack_9c);
        gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,afStack_9c,afStack_9c);
        piVar6 = &DAT_803c3b7c;
        dVar12 = (double)(float)(dVar12 * (double)FLOAT_80436f7c);
        for (iVar10 = 0; iVar10 < (int)(uint)DAT_8043624c; iVar10 = iVar10 + 1) {
          iVar5 = *piVar6;
          if (((((*(ushort *)(*(int *)(iVar5 + 0x28) + 2) & 0x800) != 0) &&
               (iVar4 = *(int *)(iVar5 + 0x20), iVar4 != 0)) && (*(char *)(iVar4 + 0x26f) != '\0'))
             && ((*(char *)(iVar4 + 0x83) != '\0' || (*(char *)(iVar4 + 0x3e4) != pcVar9[0x2e5]))))
          {
            dVar13 = gnt4_PSVECSquareDistance_bl((float *)(iVar5 + 100),afStack_9c);
            if ((double)FLOAT_80436f68 < dVar13) {
              dVar14 = 1.0 / SQRT(dVar13);
              dVar14 = DOUBLE_80436fd0 * dVar14 * -(dVar13 * dVar14 * dVar14 - DOUBLE_80436fd8);
              dVar14 = DOUBLE_80436fd0 * dVar14 * -(dVar13 * dVar14 * dVar14 - DOUBLE_80436fd8);
              dVar13 = (double)(float)(dVar13 * DOUBLE_80436fd0 * dVar14 *
                                                -(dVar13 * dVar14 * dVar14 - DOUBLE_80436fd8));
            }
            if ((dVar13 <= (double)(float)((double)*(float *)(iVar5 + 0x7c) + dVar12)) &&
               (iVar5 = (*(code *)(&PTR_FUN_802cffb0)[*(int *)(iVar5 + 0x58)])
                                  ((int *)(iVar5 + 0x58),&local_78,&local_84,auStack_90,&local_a0),
               iVar5 != 0)) {
              pcVar9[0x26f] = '\x01';
            }
          }
          piVar6 = piVar6 + 1;
        }
      }
    }
    iVar11 = iVar11 + 1;
    pcVar9 = pcVar9 + 0x3e4;
    piVar7 = piVar7 + 1;
  } while (iVar11 < 0xd);
  return;
}



// ==== 800372e4  FUN_800372e4 ====

/* WARNING: Removing unreachable block (ram,0x8003749c) */
/* WARNING: Removing unreachable block (ram,0x800372f4) */

undefined4 FUN_800372e4(int param_1,float *param_2,float *param_3,int param_4)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float *local_58;
  float *local_54;
  float local_50;
  undefined1 auStack_4c [4];
  float afStack_48 [3];
  undefined1 auStack_3c [24];
  
  local_58 = param_2;
  local_54 = param_3;
  dVar5 = gnt4_PSVECSquareDistance_bl(param_2,param_3);
  if ((double)FLOAT_80436f68 < dVar5) {
    gnt4_PSVECAdd_bl((float *)&local_58,(float *)&local_54,afStack_48);
    gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,afStack_48,afStack_48);
    piVar1 = &DAT_803c417c;
    dVar5 = (double)(float)(dVar5 * (double)FLOAT_80436f7c);
    for (iVar4 = 0; iVar4 < (int)(uint)DAT_8043624e; iVar4 = iVar4 + 1) {
      iVar3 = *piVar1;
      iVar2 = *(int *)(iVar3 + 0x20);
      if (((iVar2 != 0) && (*(char *)(iVar2 + 0x83) == '\0')) && (iVar2 != param_1)) {
        if (param_4 == 0) {
          if (*(char *)(iVar2 + 0x88) == *(char *)(param_1 + 0x88)) {
LAB_800373cc:
            dVar6 = gnt4_PSVECSquareDistance_bl((float *)(iVar3 + 100),afStack_48);
            if ((double)FLOAT_80436f68 < dVar6) {
              dVar7 = 1.0 / SQRT(dVar6);
              dVar7 = DOUBLE_80436fd0 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80436fd8);
              dVar7 = DOUBLE_80436fd0 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80436fd8);
              local_50 = (float)(dVar6 * DOUBLE_80436fd0 * dVar7 *
                                         -(dVar6 * dVar7 * dVar7 - DOUBLE_80436fd8));
              dVar6 = (double)local_50;
            }
            if ((dVar6 <= (double)(float)((double)*(float *)(iVar3 + 0x7c) + dVar5)) &&
               (iVar2 = (*(code *)(&PTR_FUN_802cffb0)[*(int *)(iVar3 + 0x58)])
                                  ((int *)(iVar3 + 0x58),local_58,local_54,auStack_3c,auStack_4c),
               iVar2 != 0)) {
              return 1;
            }
          }
        }
        else if (*(char *)(iVar2 + 0x88) != *(char *)(param_1 + 0x88)) goto LAB_800373cc;
      }
      piVar1 = piVar1 + 1;
    }
  }
  return 0;
}



// ==== 800374b8  FUN_800374b8 ====

/* WARNING: Removing unreachable block (ram,0x800377f8) */
/* WARNING: Removing unreachable block (ram,0x800377f0) */
/* WARNING: Removing unreachable block (ram,0x800374d0) */
/* WARNING: Removing unreachable block (ram,0x800374c8) */

undefined4 FUN_800374b8(float *param_1,float *param_2,float *param_3)

{
  char cVar1;
  ushort uVar2;
  bool bVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  float *local_78;
  float *local_74;
  float local_70;
  float local_6c;
  undefined1 auStack_68 [4];
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [6];
  
  local_78 = param_1;
  local_74 = param_2;
  dVar8 = gnt4_PSVECSquareDistance_bl(param_1,param_2);
  if ((double)FLOAT_80436f68 < dVar8) {
    dVar11 = (double)FLOAT_80436f98;
    bVar3 = false;
    gnt4_PSVECAdd_bl((float *)&local_78,(float *)&local_74,afStack_4c);
    gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,afStack_4c,afStack_4c);
    piVar4 = &DAT_803c237c;
    dVar8 = (double)(float)(dVar8 * (double)FLOAT_80436f7c);
    for (iVar7 = 0; iVar7 < (int)(uint)DAT_80436244; iVar7 = iVar7 + 1) {
      iVar6 = *piVar4;
      if ((*(int *)(iVar6 + 0x20) != 0) &&
         (((cVar1 = *(char *)(*(int *)(iVar6 + 0x20) + 0x83), cVar1 == '\x16' || (cVar1 == '\x17'))
          || (cVar1 == '\x11')))) {
        dVar9 = gnt4_PSVECSquareDistance_bl((float *)(iVar6 + 100),afStack_4c);
        if ((double)FLOAT_80436f68 < dVar9) {
          dVar10 = 1.0 / SQRT(dVar9);
          dVar10 = DOUBLE_80436fd0 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80436fd8);
          dVar10 = DOUBLE_80436fd0 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80436fd8);
          local_6c = (float)(dVar9 * DOUBLE_80436fd0 * dVar10 *
                                     -(dVar9 * dVar10 * dVar10 - DOUBLE_80436fd8));
          dVar9 = (double)local_6c;
        }
        if (((dVar9 <= (double)(float)((double)*(float *)(iVar6 + 0x7c) + dVar8)) &&
            (iVar6 = (*(code *)(&PTR_FUN_802cffb0)[*(int *)(iVar6 + 0x58)])
                               ((int *)(iVar6 + 0x58),local_78,local_74,&local_58,auStack_68),
            iVar6 != 0)) &&
           (dVar9 = gnt4_PSVECSquareDistance_bl(local_78,&local_58), dVar9 <= dVar11)) {
          bVar3 = true;
          local_64 = local_58;
          local_60 = local_54;
          local_5c = local_50;
          dVar11 = dVar9;
        }
      }
      piVar4 = piVar4 + 1;
    }
    piVar4 = &DAT_803c3b7c;
    for (iVar7 = 0; iVar7 < (int)(uint)DAT_8043624c; iVar7 = iVar7 + 1) {
      iVar6 = *piVar4;
      uVar2 = *(ushort *)(*(int *)(iVar6 + 0x28) + 2);
      if ((((uVar2 & 0x800) == 0) && (*(int *)(iVar6 + 0x20) != 0)) &&
         (((cVar1 = *(char *)(*(int *)(iVar6 + 0x20) + 0x83), cVar1 == '\x16' ||
           ((cVar1 == '\x17' || (cVar1 == '\x11')))) && ((uVar2 & 0x20) == 0)))) {
        dVar9 = gnt4_PSVECSquareDistance_bl((float *)(iVar6 + 100),afStack_4c);
        if ((double)FLOAT_80436f68 < dVar9) {
          dVar10 = 1.0 / SQRT(dVar9);
          dVar10 = DOUBLE_80436fd0 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80436fd8);
          dVar10 = DOUBLE_80436fd0 * dVar10 * -(dVar9 * dVar10 * dVar10 - DOUBLE_80436fd8);
          local_70 = (float)(dVar9 * DOUBLE_80436fd0 * dVar10 *
                                     -(dVar9 * dVar10 * dVar10 - DOUBLE_80436fd8));
          dVar9 = (double)local_70;
        }
        if (((dVar9 <= (double)(float)((double)*(float *)(iVar6 + 0x7c) + dVar8)) &&
            (iVar6 = (*(code *)(&PTR_FUN_802cffb0)[*(int *)(iVar6 + 0x58)])
                               ((int *)(iVar6 + 0x58),local_78,local_74,&local_58,auStack_68),
            iVar6 != 0)) &&
           (dVar9 = gnt4_PSVECSquareDistance_bl(local_78,&local_58), dVar9 <= dVar11)) {
          bVar3 = true;
          local_64 = local_58;
          local_60 = local_54;
          local_5c = local_50;
          dVar11 = dVar9;
        }
      }
      piVar4 = piVar4 + 1;
    }
    if (bVar3) {
      uVar5 = 1;
      *param_3 = local_64;
      param_3[1] = local_60;
      param_3[2] = local_5c;
    }
    else {
      uVar5 = 0;
    }
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}



// ==== 80037814  FUN_80037814 ====

/* WARNING: Removing unreachable block (ram,0x80037b7c) */
/* WARNING: Removing unreachable block (ram,0x80037b74) */
/* WARNING: Removing unreachable block (ram,0x8003782c) */
/* WARNING: Removing unreachable block (ram,0x80037824) */

undefined4 FUN_80037814(float *param_1,float *param_2,float *param_3)

{
  char cVar1;
  ushort uVar2;
  bool bVar3;
  int *piVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  float *local_78;
  float *local_74;
  float local_70;
  float local_6c;
  undefined1 auStack_68 [4];
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [6];
  
  local_78 = param_1;
  local_74 = param_2;
  dVar9 = gnt4_PSVECSquareDistance_bl(param_1,param_2);
  if ((double)FLOAT_80436f68 < dVar9) {
    dVar12 = (double)FLOAT_80436f98;
    bVar3 = false;
    gnt4_PSVECAdd_bl((float *)&local_78,(float *)&local_74,afStack_4c);
    gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,afStack_4c,afStack_4c);
    piVar4 = &DAT_803c237c;
    dVar9 = (double)(float)(dVar9 * (double)FLOAT_80436f7c);
    for (iVar8 = 0; iVar8 < (int)(uint)DAT_80436244; iVar8 = iVar8 + 1) {
      iVar6 = *piVar4;
      iVar7 = *(int *)(iVar6 + 0x20);
      if ((iVar7 != 0) &&
         ((((cVar1 = *(char *)(iVar7 + 0x83), cVar1 == '\x16' || (cVar1 == '\x17')) ||
           (cVar1 == '\x11')) || ((cVar1 == '\0' && (*(char *)(iVar7 + 1000) == '\x0e')))))) {
        dVar10 = gnt4_PSVECSquareDistance_bl((float *)(iVar6 + 100),afStack_4c);
        if ((double)FLOAT_80436f68 < dVar10) {
          dVar11 = 1.0 / SQRT(dVar10);
          dVar11 = DOUBLE_80436fd0 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_80436fd8);
          dVar11 = DOUBLE_80436fd0 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_80436fd8);
          local_6c = (float)(dVar10 * DOUBLE_80436fd0 * dVar11 *
                                      -(dVar10 * dVar11 * dVar11 - DOUBLE_80436fd8));
          dVar10 = (double)local_6c;
        }
        if (((dVar10 <= (double)(float)((double)*(float *)(iVar6 + 0x7c) + dVar9)) &&
            (iVar7 = (*(code *)(&PTR_FUN_802cffb0)[*(int *)(iVar6 + 0x58)])
                               ((int *)(iVar6 + 0x58),local_78,local_74,&local_58,auStack_68),
            iVar7 != 0)) &&
           (dVar10 = gnt4_PSVECSquareDistance_bl(local_78,&local_58), dVar10 <= dVar12)) {
          bVar3 = true;
          local_64 = local_58;
          local_60 = local_54;
          local_5c = local_50;
          dVar12 = dVar10;
        }
      }
      piVar4 = piVar4 + 1;
    }
    piVar4 = &DAT_803c3b7c;
    for (iVar8 = 0; iVar8 < (int)(uint)DAT_8043624c; iVar8 = iVar8 + 1) {
      iVar7 = *piVar4;
      uVar2 = *(ushort *)(*(int *)(iVar7 + 0x28) + 2);
      if ((((uVar2 & 0x800) == 0) && (iVar6 = *(int *)(iVar7 + 0x20), iVar6 != 0)) &&
         ((((cVar1 = *(char *)(iVar6 + 0x83), cVar1 == '\x16' ||
            ((cVar1 == '\x17' || (cVar1 == '\x11')))) ||
           ((cVar1 == '\0' && (*(char *)(iVar6 + 1000) == '\x0e')))) && ((uVar2 & 0x20) == 0)))) {
        dVar10 = gnt4_PSVECSquareDistance_bl((float *)(iVar7 + 100),afStack_4c);
        if ((double)FLOAT_80436f68 < dVar10) {
          dVar11 = 1.0 / SQRT(dVar10);
          dVar11 = DOUBLE_80436fd0 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_80436fd8);
          dVar11 = DOUBLE_80436fd0 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_80436fd8);
          local_70 = (float)(dVar10 * DOUBLE_80436fd0 * dVar11 *
                                      -(dVar10 * dVar11 * dVar11 - DOUBLE_80436fd8));
          dVar10 = (double)local_70;
        }
        if (((dVar10 <= (double)(float)((double)*(float *)(iVar7 + 0x7c) + dVar9)) &&
            (iVar7 = (*(code *)(&PTR_FUN_802cffb0)[*(int *)(iVar7 + 0x58)])
                               ((int *)(iVar7 + 0x58),local_78,local_74,&local_58,auStack_68),
            iVar7 != 0)) &&
           (dVar10 = gnt4_PSVECSquareDistance_bl(local_78,&local_58), dVar10 <= dVar12)) {
          bVar3 = true;
          local_64 = local_58;
          local_60 = local_54;
          local_5c = local_50;
          dVar12 = dVar10;
        }
      }
      piVar4 = piVar4 + 1;
    }
    if (bVar3) {
      uVar5 = 1;
      *param_3 = local_64;
      param_3[1] = local_60;
      param_3[2] = local_5c;
    }
    else {
      uVar5 = 0;
    }
  }
  else {
    uVar5 = 0;
  }
  return uVar5;
}



// ==== 80037b98  FUN_80037b98 ====

/* WARNING: Removing unreachable block (ram,0x80037f04) */
/* WARNING: Removing unreachable block (ram,0x80037efc) */
/* WARNING: Removing unreachable block (ram,0x80037ef4) */
/* WARNING: Removing unreachable block (ram,0x80037eec) */
/* WARNING: Removing unreachable block (ram,0x80037ee4) */
/* WARNING: Removing unreachable block (ram,0x80037bc8) */
/* WARNING: Removing unreachable block (ram,0x80037bc0) */
/* WARNING: Removing unreachable block (ram,0x80037bb8) */
/* WARNING: Removing unreachable block (ram,0x80037bb0) */
/* WARNING: Removing unreachable block (ram,0x80037ba8) */

undefined4 FUN_80037b98(int param_1,float *param_2,float *param_3,float *param_4)

{
  ushort uVar1;
  bool bVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double in_f27;
  double in_f29;
  double in_f30;
  double in_f31;
  float *local_98;
  float *local_94;
  float local_90;
  float local_8c;
  undefined1 auStack_88 [4];
  float local_84;
  float local_80;
  float local_7c;
  float afStack_78 [4];
  
  local_98 = param_2;
  local_94 = param_3;
  dVar7 = gnt4_PSVECSquareDistance_bl(param_2,param_3);
  if ((double)FLOAT_80436f68 < dVar7) {
    bVar2 = false;
    gnt4_PSVECAdd_bl((float *)&local_98,(float *)&local_94,afStack_78);
    gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,afStack_78,afStack_78);
    piVar3 = &DAT_803c237c;
    dVar7 = (double)(float)(dVar7 * (double)FLOAT_80436f7c);
    for (iVar6 = 0; iVar6 < (int)(uint)DAT_80436244; iVar6 = iVar6 + 1) {
      iVar5 = *piVar3;
      if ((*(int *)(iVar5 + 0x20) != 0) && (*(int *)(iVar5 + 0x20) != param_1)) {
        dVar8 = gnt4_PSVECSquareDistance_bl((float *)(iVar5 + 100),afStack_78);
        if ((double)FLOAT_80436f68 < dVar8) {
          dVar9 = 1.0 / SQRT(dVar8);
          dVar9 = DOUBLE_80436fd0 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_80436fd8);
          dVar9 = DOUBLE_80436fd0 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_80436fd8);
          local_8c = (float)(dVar8 * DOUBLE_80436fd0 * dVar9 *
                                     -(dVar8 * dVar9 * dVar9 - DOUBLE_80436fd8));
          dVar8 = (double)local_8c;
        }
        if ((dVar8 <= (double)(float)((double)*(float *)(iVar5 + 0x7c) + dVar7)) &&
           (iVar5 = (*(code *)(&PTR_FUN_802cffb0)[*(int *)(iVar5 + 0x58)])
                              ((int *)(iVar5 + 0x58),local_98,local_94,&local_84,auStack_88),
           iVar5 != 0)) {
          if (bVar2) {
            dVar8 = gnt4_PSVECSquareDistance_bl(&local_84,local_98);
            if (dVar8 < in_f27) {
              in_f31 = (double)local_84;
              in_f30 = (double)local_80;
              in_f29 = (double)local_7c;
              in_f27 = dVar8;
            }
          }
          else {
            in_f31 = (double)local_84;
            in_f30 = (double)local_80;
            bVar2 = true;
            in_f29 = (double)local_7c;
            in_f27 = gnt4_PSVECSquareDistance_bl(&local_84,local_98);
          }
        }
      }
      piVar3 = piVar3 + 1;
    }
    piVar3 = &DAT_803c3b7c;
    for (iVar6 = 0; iVar6 < (int)(uint)DAT_8043624c; iVar6 = iVar6 + 1) {
      iVar5 = *piVar3;
      uVar1 = *(ushort *)(*(int *)(iVar5 + 0x28) + 2);
      if (((((uVar1 & 0x800) == 0) && (*(int *)(iVar5 + 0x20) != 0)) &&
          (*(int *)(iVar5 + 0x20) != param_1)) && ((uVar1 & 0x20) == 0)) {
        dVar8 = gnt4_PSVECSquareDistance_bl((float *)(iVar5 + 100),afStack_78);
        if ((double)FLOAT_80436f68 < dVar8) {
          dVar9 = 1.0 / SQRT(dVar8);
          dVar9 = DOUBLE_80436fd0 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_80436fd8);
          dVar9 = DOUBLE_80436fd0 * dVar9 * -(dVar8 * dVar9 * dVar9 - DOUBLE_80436fd8);
          local_90 = (float)(dVar8 * DOUBLE_80436fd0 * dVar9 *
                                     -(dVar8 * dVar9 * dVar9 - DOUBLE_80436fd8));
          dVar8 = (double)local_90;
        }
        if ((dVar8 <= (double)(float)((double)*(float *)(iVar5 + 0x7c) + dVar7)) &&
           (iVar5 = (*(code *)(&PTR_FUN_802cffb0)[*(int *)(iVar5 + 0x58)])
                              ((int *)(iVar5 + 0x58),local_98,local_94,&local_84,auStack_88),
           iVar5 != 0)) {
          if (bVar2) {
            dVar8 = gnt4_PSVECSquareDistance_bl(&local_84,local_98);
            if (dVar8 < in_f27) {
              in_f31 = (double)local_84;
              in_f30 = (double)local_80;
              in_f29 = (double)local_7c;
              in_f27 = dVar8;
            }
          }
          else {
            in_f31 = (double)local_84;
            in_f30 = (double)local_80;
            bVar2 = true;
            in_f29 = (double)local_7c;
            in_f27 = gnt4_PSVECSquareDistance_bl(&local_84,local_98);
          }
        }
      }
      piVar3 = piVar3 + 1;
    }
    if (bVar2) {
      *param_4 = (float)in_f31;
      uVar4 = 1;
      param_4[1] = (float)in_f30;
      param_4[2] = (float)in_f29;
    }
    else {
      uVar4 = 0;
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}



// ==== 80037f20  FUN_80037f20 ====

/* WARNING: Removing unreachable block (ram,0x800381b4) */
/* WARNING: Removing unreachable block (ram,0x800380ac) */
/* WARNING: Removing unreachable block (ram,0x80037f30) */

undefined4
FUN_80037f20(int param_1,float *param_2,float *param_3,float *param_4,undefined4 *param_5)

{
  int iVar1;
  undefined4 uVar2;
  byte bVar3;
  double dVar4;
  double dVar5;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float afStack_98 [3];
  float afStack_8c [3];
  float afStack_80 [3];
  float afStack_74 [20];
  
  dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0xc),param_2);
  if ((double)FLOAT_80436f68 < dVar4) {
    dVar5 = 1.0 / SQRT(dVar4);
    dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436fd8);
    dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436fd8);
    dVar4 = (double)(float)(dVar4 * DOUBLE_80436fd0 * dVar5 *
                                    -(dVar4 * dVar5 * dVar5 - DOUBLE_80436fd8));
  }
  if ((double)*(float *)(param_1 + 0x30) < dVar4) {
    *param_5 = 0;
  }
  else {
    *param_5 = 1;
  }
  zz_0038b34_(param_2,param_3,afStack_74);
  iVar1 = FUN_80039564(afStack_74,param_1,&local_a4);
  if (iVar1 == 1) {
    uVar2 = 1;
    *param_4 = local_a4;
    param_4[1] = local_a0;
    param_4[2] = local_9c;
  }
  else {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),param_2,afStack_8c);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xc),param_3,afStack_98);
    gnt4_PSVECSubtract_bl(param_3,param_2,afStack_80);
    gnt4_PSVECNormalize_bl(afStack_80,afStack_80);
    dVar4 = gnt4_PSQUATDotProduct_bl(afStack_8c,afStack_80);
    bVar3 = dVar4 < (double)FLOAT_80436f68;
    dVar5 = gnt4_PSQUATDotProduct_bl(afStack_98,afStack_80);
    if ((double)FLOAT_80436f68 < dVar5) {
      bVar3 = bVar3 | 2;
    }
    if (bVar3 == 2) {
      local_b0 = *param_3;
      local_ac = param_3[1];
      local_a8 = param_3[2];
    }
    else if (bVar3 < 2) {
      if (bVar3 == 0) {
        gnt4_PSQUATScale_bl(dVar4,afStack_80,&local_b0);
        gnt4_PSVECAdd_bl(param_2,&local_b0,&local_b0);
      }
      else {
        local_b0 = *param_2;
        local_ac = param_2[1];
        local_a8 = param_2[2];
      }
    }
    else if (bVar3 < 4) {
      return 0;
    }
    dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0xc),&local_b0);
    if ((double)FLOAT_80436f68 < dVar4) {
      dVar5 = 1.0 / SQRT(dVar4);
      dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436fd8);
      dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436fd8);
      dVar4 = (double)(float)(dVar4 * DOUBLE_80436fd0 * dVar5 *
                                      -(dVar4 * dVar5 * dVar5 - DOUBLE_80436fd8));
    }
    if ((double)*(float *)(param_1 + 0x30) <= dVar4) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
      *param_4 = local_a4;
      param_4[1] = local_a0;
      param_4[2] = local_9c;
    }
  }
  return uVar2;
}



// ==== 800381d0  FUN_800381d0 ====

/* WARNING: Removing unreachable block (ram,0x8003845c) */
/* WARNING: Removing unreachable block (ram,0x80038454) */
/* WARNING: Removing unreachable block (ram,0x8003844c) */
/* WARNING: Removing unreachable block (ram,0x800381f0) */
/* WARNING: Removing unreachable block (ram,0x800381e8) */
/* WARNING: Removing unreachable block (ram,0x800381e0) */

undefined4
FUN_800381d0(int param_1,float *param_2,float *param_3,float *param_4,undefined4 *param_5)

{
  byte bVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  char *pcVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  float afStack_88 [3];
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  
  *param_5 = 0;
  dVar8 = (double)FLOAT_80436f68;
  local_7c = *param_2;
  local_78 = param_2[1];
  pcVar5 = &DAT_802cffc8;
  uVar2 = 0;
  iVar3 = 0;
  local_74 = param_2[2];
  local_70 = *param_3;
  local_6c = param_3[1];
  local_68 = param_3[2];
  iVar4 = param_1;
  do {
    gnt4_PSVECSubtract_bl((float *)(param_1 + *pcVar5 * 0xc + 0x30),&local_7c,afStack_88);
    dVar6 = gnt4_PSQUATDotProduct_bl(afStack_88,(float *)(iVar4 + 0x90));
    bVar1 = dVar8 <= dVar6;
    gnt4_PSVECSubtract_bl((float *)(param_1 + *pcVar5 * 0xc + 0x30),&local_70,afStack_88);
    dVar7 = gnt4_PSQUATDotProduct_bl(afStack_88,(float *)(iVar4 + 0x90));
    if (dVar8 <= dVar7) {
      bVar1 = bVar1 | 2;
    }
    if (bVar1 == 0) {
      return 0;
    }
    if (bVar1 == 2) {
      gnt4_PSVECSubtract_bl(&local_7c,&local_70,afStack_88);
      dVar7 = gnt4_PSQUATDotProduct_bl(afStack_88,(float *)(iVar4 + 0x90));
      if (((double)FLOAT_80436f68 == dVar7) || ((double)FLOAT_80436fcc == dVar7)) {
        gnt4_PSQUATScale_bl(dVar6,(float *)(iVar4 + 0x90),afStack_88);
      }
      else {
        gnt4_PSQUATScale_bl((double)(float)(dVar6 / dVar7),afStack_88,afStack_88);
      }
      gnt4_PSVECAdd_bl(&local_7c,afStack_88,&local_7c);
      uVar2 = uVar2 | 1;
    }
    else if ((bVar1 < 2) && (bVar1 != 0)) {
      gnt4_PSVECSubtract_bl(&local_70,&local_7c,afStack_88);
      dVar6 = gnt4_PSQUATDotProduct_bl(afStack_88,(float *)(iVar4 + 0x90));
      if (((double)FLOAT_80436f68 == dVar6) || ((double)FLOAT_80436fcc == dVar6)) {
        gnt4_PSQUATScale_bl(dVar7,(float *)(iVar4 + 0x90),afStack_88);
      }
      else {
        gnt4_PSQUATScale_bl((double)(float)(dVar7 / dVar6),afStack_88,afStack_88);
      }
      gnt4_PSVECAdd_bl(&local_70,afStack_88,&local_70);
      uVar2 = uVar2 | 2;
    }
    iVar3 = iVar3 + 1;
    iVar4 = iVar4 + 0x18;
    pcVar5 = pcVar5 + 4;
  } while (iVar3 < 6);
  if (uVar2 == 2) {
    *param_4 = local_70;
    param_4[1] = local_6c;
    param_4[2] = local_68;
    *param_5 = 1;
  }
  else {
    *param_4 = local_7c;
    param_4[1] = local_78;
    param_4[2] = local_74;
    *param_5 = 0;
  }
  return 1;
}



// ==== 80038478  FUN_80038478 ====

/* WARNING: Removing unreachable block (ram,0x80038514) */

undefined4
FUN_80038478(int param_1,float *param_2,float *param_3,float *param_4,undefined4 *param_5)

{
  float fVar1;
  int iVar2;
  undefined4 uVar3;
  byte bVar4;
  double dVar5;
  double dVar6;
  float afStack_90 [3];
  float local_84;
  float local_80;
  float local_7c;
  float afStack_78 [3];
  float afStack_6c [21];
  
  *param_5 = 0;
  gnt4_PSVECSubtract_bl(param_2,(float *)(param_1 + 0x34),afStack_90);
  dVar5 = gnt4_PSQUATDotProduct_bl(afStack_90,(float *)(param_1 + 100));
  bVar4 = dVar5 < (double)FLOAT_80436f68;
  gnt4_PSVECSubtract_bl(param_2,(float *)(param_1 + 0x40),afStack_90);
  dVar5 = gnt4_PSQUATDotProduct_bl(afStack_90,(float *)(param_1 + 0x70));
  if (dVar5 < (double)FLOAT_80436f68) {
    bVar4 = bVar4 | 2;
  }
  if (bVar4 == 1) {
    local_84 = *(float *)(param_1 + 0x34);
    local_80 = *(float *)(param_1 + 0x38);
    local_7c = *(float *)(param_1 + 0x3c);
  }
  else if (bVar4 == 0) {
    gnt4_PSQUATScale_bl(dVar5,(float *)(param_1 + 0x70),&local_84);
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x40),&local_84,&local_84);
  }
  else if (bVar4 < 4) {
    local_84 = *(float *)(param_1 + 0x40);
    local_80 = *(float *)(param_1 + 0x44);
    local_7c = *(float *)(param_1 + 0x48);
  }
  dVar5 = gnt4_PSVECSquareDistance_bl(param_2,&local_84);
  if ((double)FLOAT_80436f68 < dVar5) {
    dVar6 = 1.0 / SQRT(dVar5);
    dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
    dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
    dVar5 = (double)(float)(dVar5 * DOUBLE_80436fd0 * dVar6 *
                                    -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8));
  }
  if (dVar5 <= (double)*(float *)(param_1 + 0x30)) {
    *param_5 = 1;
  }
  zz_0038b34_(param_2,param_3,afStack_6c);
  iVar2 = zz_0038c00_(afStack_6c,(float *)(param_1 + 0x34),&local_84);
  if (iVar2 == 0) {
    uVar3 = 1;
    fVar1 = param_2[1];
    *param_4 = *param_2;
    param_4[1] = fVar1;
    param_4[2] = param_2[2];
  }
  else {
    dVar5 = gnt4_PSVECSquareDistance_bl(&local_84,afStack_78);
    if ((double)FLOAT_80436f68 < dVar5) {
      dVar6 = 1.0 / SQRT(dVar5);
      dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
      dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
      dVar5 = (double)(float)(dVar5 * DOUBLE_80436fd0 * dVar6 *
                                      -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8));
    }
    if ((double)*(float *)(param_1 + 0x30) <= dVar5) {
      uVar3 = 0;
    }
    else {
      uVar3 = 1;
      *param_4 = local_84;
      param_4[1] = local_80;
      param_4[2] = local_7c;
    }
  }
  return uVar3;
}



// ==== 800386e4  FUN_800386e4 ====

/* WARNING: Removing unreachable block (ram,0x800389cc) */
/* WARNING: Removing unreachable block (ram,0x800389c4) */
/* WARNING: Removing unreachable block (ram,0x800389bc) */
/* WARNING: Removing unreachable block (ram,0x80038704) */
/* WARNING: Removing unreachable block (ram,0x800386fc) */
/* WARNING: Removing unreachable block (ram,0x800386f4) */

uint FUN_800386e4(int param_1,float *param_2,float *param_3,float *param_4,undefined4 *param_5)

{
  float fVar1;
  byte bVar3;
  uint uVar2;
  byte *pbVar4;
  int iVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double in_f30;
  float local_114;
  float local_110;
  float local_10c;
  float afStack_108 [3];
  float afStack_fc [3];
  float local_f0;
  undefined4 local_ec;
  undefined4 local_e8;
  float afStack_e4 [3];
  float afStack_d8 [18];
  float afStack_90 [18];
  
  *param_5 = 0;
  zz_0038b34_(param_2,param_3,afStack_90);
  iVar5 = 0;
  iVar7 = param_1;
  iVar8 = param_1;
  while ((bVar3 = FUN_80039da4(afStack_90,(float *)(iVar8 + 0x7c),(float *)(param_1 + 0x4c),
                               afStack_fc), bVar3 == 0 ||
         (uVar2 = zz_0039aec_(afStack_fc,(float *)(iVar7 + 0x34),(float *)(iVar8 + 0x7c)),
         uVar2 == 0))) {
    iVar5 = iVar5 + 1;
    iVar7 = iVar7 + 0x24;
    iVar8 = iVar8 + 0x18;
    if (1 < iVar5) {
      dVar9 = (double)FLOAT_80436f68;
      iVar7 = -1;
      pbVar4 = &DAT_80433688;
      iVar8 = 0;
      do {
        zz_0038b34_((float *)(param_1 + (uint)*pbVar4 * 0xc + 0x34),
                    (float *)(param_1 + (uint)pbVar4[1] * 0xc + 0x34),afStack_d8);
        iVar5 = zz_0038c00_(afStack_d8,afStack_90,&local_f0);
        if (iVar5 == 0) {
          fVar1 = *(float *)(param_1 + 0x10);
          *param_4 = *(float *)(param_1 + 0xc);
          param_4[1] = fVar1;
          param_4[2] = *(float *)(param_1 + 0x14);
          return 1;
        }
        dVar10 = gnt4_PSVECSquareDistance_bl(&local_f0,afStack_e4);
        if (dVar9 < dVar10) {
          dVar11 = 1.0 / SQRT(dVar10);
          dVar11 = DOUBLE_80436fd0 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_80436fd8);
          dVar11 = DOUBLE_80436fd0 * dVar11 * -(dVar10 * dVar11 * dVar11 - DOUBLE_80436fd8);
          dVar10 = (double)(float)(dVar10 * DOUBLE_80436fd0 * dVar11 *
                                            -(dVar10 * dVar11 * dVar11 - DOUBLE_80436fd8));
        }
        if ((dVar10 < (double)*(float *)(param_1 + 0x30)) && ((iVar7 == -1 || (dVar10 < in_f30)))) {
          gnt4_PSVECSubtract_bl(afStack_e4,&local_f0,afStack_fc);
          dVar11 = gnt4_PSVECSquareMag_bl(afStack_fc);
          iVar7 = iVar8;
          if ((double)FLOAT_80436f68 < dVar11) {
            gnt4_PSVECNormalize_bl(afStack_fc,afStack_fc);
            gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x30),afStack_fc,afStack_fc);
            gnt4_PSVECAdd_bl(&local_f0,afStack_fc,&local_114);
            in_f30 = dVar10;
          }
          else {
            DAT_803b0720 = local_f0;
            DAT_803b0724 = local_ec;
            DAT_803b0728 = local_e8;
            in_f30 = dVar10;
          }
        }
        iVar8 = iVar8 + 1;
        pbVar4 = pbVar4 + 1;
      } while (iVar8 < 4);
      if (iVar7 != -1) {
        *param_4 = local_114;
        param_4[1] = local_110;
        param_4[2] = local_10c;
      }
      return (uint)(iVar7 != -1);
    }
  }
  gnt4_PSVECSubtract_bl(afStack_90,(float *)(param_1 + 0x4c),afStack_108);
  pfVar6 = (float *)(param_1 + iVar5 * 0x18 + 0x7c);
  dVar9 = gnt4_PSQUATDotProduct_bl(afStack_108,pfVar6);
  if (dVar9 < (double)FLOAT_80436f68) {
    dVar9 = -(double)*(float *)(param_1 + 0x30);
  }
  else {
    dVar9 = (double)*(float *)(param_1 + 0x30);
  }
  gnt4_PSQUATScale_bl(dVar9,pfVar6,afStack_108);
  gnt4_PSVECAdd_bl(afStack_fc,afStack_108,&local_114);
  *param_4 = local_114;
  param_4[1] = local_110;
  param_4[2] = local_10c;
  return 1;
}



// ==== 800389e8  FUN_800389e8 ====

undefined4
FUN_800389e8(int param_1,float *param_2,float *param_3,float *param_4,undefined4 *param_5)

{
  byte bVar1;
  double dVar2;
  double dVar3;
  float afStack_74 [3];
  float afStack_68 [3];
  float afStack_5c [20];
  
  *param_5 = 0;
  zz_0038b34_(param_2,param_3,afStack_5c);
  bVar1 = FUN_80039da4(afStack_5c,(float *)(param_1 + 0x30),(float *)(param_1 + 0xc),afStack_74);
  if (bVar1 != 0) {
    dVar2 = gnt4_PSVECSquareDistance_bl(afStack_74,(float *)(param_1 + 0xc));
    if ((double)FLOAT_80436f68 < dVar2) {
      dVar3 = 1.0 / SQRT(dVar2);
      dVar3 = DOUBLE_80436fd0 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80436fd8);
      dVar3 = DOUBLE_80436fd0 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80436fd8);
      dVar2 = (double)(float)(dVar2 * DOUBLE_80436fd0 * dVar3 *
                                      -(dVar2 * dVar3 * dVar3 - DOUBLE_80436fd8));
    }
    if (dVar2 <= (double)*(float *)(param_1 + 0x4c)) {
      gnt4_PSVECSubtract_bl(param_2,(float *)(param_1 + 0xc),afStack_68);
      dVar2 = gnt4_PSQUATDotProduct_bl(afStack_68,(float *)(param_1 + 0x30));
      if (dVar2 < (double)FLOAT_80436f68) {
        dVar2 = -(double)*(float *)(param_1 + 0x48);
      }
      else {
        dVar2 = (double)*(float *)(param_1 + 0x48);
      }
      gnt4_PSQUATScale_bl(dVar2,(float *)(param_1 + 0x30),afStack_68);
      gnt4_PSVECAdd_bl(afStack_74,afStack_68,param_4);
      return 1;
    }
  }
  return 0;
}



// ==== 80038b34  zz_0038b34_ ====

void zz_0038b34_(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  
  fVar1 = param_1[1];
  *param_3 = *param_1;
  param_3[1] = fVar1;
  param_3[2] = param_1[2];
  fVar1 = param_2[1];
  param_3[3] = *param_2;
  param_3[4] = fVar1;
  param_3[5] = param_2[2];
  if (((*param_3 == param_3[3]) && (param_3[1] == param_3[4])) && (param_3[2] == param_3[5])) {
    param_3[4] = param_3[4] + FLOAT_80436f78;
  }
  gnt4_PSVECSubtract_bl(param_3 + 3,param_3,param_3 + 6);
  gnt4_PSVECSubtract_bl(param_3,param_3 + 3,param_3 + 9);
  gnt4_PSVECNormalize_bl(param_3 + 6,param_3 + 0xc);
  gnt4_PSVECNormalize_bl(param_3 + 9,param_3 + 0xf);
  return;
}



// ==== 80038c00  zz_0038c00_ ====

/* WARNING: Removing unreachable block (ram,0x8003953c) */
/* WARNING: Removing unreachable block (ram,0x80039534) */
/* WARNING: Removing unreachable block (ram,0x8003952c) */
/* WARNING: Removing unreachable block (ram,0x80038da0) */
/* WARNING: Removing unreachable block (ram,0x80038c20) */
/* WARNING: Removing unreachable block (ram,0x80038c18) */
/* WARNING: Removing unreachable block (ram,0x80038c10) */

undefined4 zz_0038c00_(float *param_1,float *param_2,float *param_3)

{
  float fVar1;
  float fVar2;
  bool bVar3;
  float fVar4;
  uint uVar5;
  byte bVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double in_f31;
  float afStack_b8 [3];
  float afStack_ac [3];
  float afStack_a0 [3];
  float afStack_94 [3];
  float afStack_88 [3];
  float local_7c;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float afStack_64 [3];
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  
  gnt4_PSVECCrossProduct_bl(param_1 + 6,param_2 + 6,&local_4c);
  dVar9 = gnt4_PSVECSquareMag_bl(&local_4c);
  if ((double)FLOAT_80436f68 < dVar9) {
    gnt4_PSVECNormalize_bl(&local_4c,&local_4c);
    gnt4_PSVECSubtract_bl(param_1,param_2,&local_58);
    dVar9 = gnt4_PSQUATDotProduct_bl(&local_58,&local_4c);
    if ((float)ABS(dVar9) < FLOAT_80436fc4) {
      dVar9 = (double)FLOAT_80436f68;
    }
    gnt4_PSQUATScale_bl(dVar9,&local_4c,afStack_64);
    gnt4_PSVECAdd_bl(param_2,afStack_64,&local_70);
    gnt4_PSVECSubtract_bl(&local_70,param_1,&local_70);
    local_4c = param_1[6];
    local_48 = param_1[7];
    local_44 = param_1[8];
    local_58 = param_2[6];
    local_54 = param_2[7];
    local_50 = param_2[8];
    fVar4 = local_58 * local_48 - local_54 * local_4c;
    fVar1 = local_58 * local_44 - local_50 * local_4c;
    fVar2 = local_50 * local_48 - local_54 * local_44;
    bVar6 = FLOAT_80436fc0 < ABS(fVar4);
    if (FLOAT_80436fc0 < ABS(fVar1)) {
      bVar6 = 2;
    }
    if (FLOAT_80436fc0 < ABS(fVar2)) {
      bVar6 = 3;
    }
    if (bVar6 == 2) {
      in_f31 = (double)((local_4c * local_68 - local_44 * local_70) / fVar1);
    }
    else if (bVar6 < 2) {
      if (bVar6 == 0) {
        in_f31 = (double)FLOAT_80436f68;
      }
      else {
        in_f31 = (double)((local_4c * local_6c - local_48 * local_70) / fVar4);
      }
    }
    else if (bVar6 < 4) {
      in_f31 = (double)((local_44 * local_6c - local_48 * local_68) / fVar2);
    }
    if (bVar6 == 0) {
      bVar3 = true;
      fVar4 = param_1[1];
      *param_3 = *param_1;
      param_3[1] = fVar4;
      param_3[2] = param_1[2];
      fVar4 = param_2[1];
      param_3[3] = *param_2;
      param_3[4] = fVar4;
      param_3[5] = param_2[2];
    }
    else {
      gnt4_PSQUATScale_bl(in_f31,param_2 + 6,param_3);
      gnt4_PSVECAdd_bl(param_3,param_2,param_3);
      gnt4_PSVECAdd_bl(param_3,afStack_64,param_3);
      gnt4_PSVECSubtract_bl(param_3,afStack_64,param_3 + 3);
      gnt4_PSVECSubtract_bl(param_3,param_1,&local_4c);
      dVar10 = gnt4_PSQUATDotProduct_bl(&local_4c,param_1 + 6);
      dVar9 = (double)FLOAT_80436f68;
      if (dVar10 < dVar9) {
        fVar4 = param_1[1];
        *param_3 = *param_1;
        param_3[1] = fVar4;
        param_3[2] = param_1[2];
      }
      gnt4_PSVECSubtract_bl(param_3,param_1 + 3,&local_4c);
      dVar11 = gnt4_PSQUATDotProduct_bl(&local_4c,param_1 + 9);
      dVar7 = (double)FLOAT_80436f68;
      if (dVar11 < dVar7) {
        fVar4 = param_1[4];
        *param_3 = param_1[3];
        param_3[1] = fVar4;
        param_3[2] = param_1[5];
      }
      gnt4_PSVECSubtract_bl(param_3 + 3,param_2,&local_4c);
      dVar12 = gnt4_PSQUATDotProduct_bl(&local_4c,param_2 + 6);
      dVar8 = (double)FLOAT_80436f68;
      if (dVar12 < dVar8) {
        fVar4 = param_2[1];
        param_3[3] = *param_2;
        param_3[4] = fVar4;
        param_3[5] = param_2[2];
      }
      bVar3 = dVar12 < dVar8 || (dVar11 < dVar7 || dVar10 < dVar9);
      gnt4_PSVECSubtract_bl(param_3 + 3,param_2 + 3,&local_4c);
      dVar9 = gnt4_PSQUATDotProduct_bl(&local_4c,param_2 + 9);
      if (dVar9 < (double)FLOAT_80436f68) {
        bVar3 = true;
        fVar4 = param_2[4];
        param_3[3] = param_2[3];
        param_3[4] = fVar4;
        param_3[5] = param_2[5];
      }
    }
    if (bVar3) {
      gnt4_PSVECSubtract_bl(param_3 + 3,param_3,&local_58);
      dVar9 = gnt4_PSQUATDotProduct_bl(&local_58,param_1 + 0xc);
      gnt4_PSQUATScale_bl(dVar9,param_1 + 0xc,&local_7c);
      gnt4_PSVECAdd_bl(&local_7c,param_3,&local_7c);
      gnt4_PSVECSubtract_bl(&local_7c,param_1,&local_4c);
      gnt4_PSVECSubtract_bl(&local_7c,param_1 + 3,&local_58);
      dVar9 = gnt4_PSQUATDotProduct_bl(&local_4c,param_1 + 6);
      if (((double)FLOAT_80436f68 < dVar9) &&
         (dVar9 = gnt4_PSQUATDotProduct_bl(&local_58,param_1 + 9), (double)FLOAT_80436f68 < dVar9))
      {
        *param_3 = local_7c;
        param_3[1] = local_78;
        param_3[2] = local_74;
      }
      gnt4_PSVECSubtract_bl(param_3,param_3 + 3,&local_58);
      dVar9 = gnt4_PSQUATDotProduct_bl(&local_58,param_2 + 0xc);
      gnt4_PSQUATScale_bl(dVar9,param_2 + 0xc,&local_7c);
      gnt4_PSVECAdd_bl(&local_7c,param_3 + 3,&local_7c);
      gnt4_PSVECSubtract_bl(&local_7c,param_2,&local_4c);
      gnt4_PSVECSubtract_bl(&local_7c,param_2 + 3,&local_58);
      dVar9 = gnt4_PSQUATDotProduct_bl(&local_4c,param_2 + 6);
      if (((double)FLOAT_80436f68 < dVar9) &&
         (dVar9 = gnt4_PSQUATDotProduct_bl(&local_58,param_2 + 9), (double)FLOAT_80436f68 < dVar9))
      {
        param_3[3] = local_7c;
        param_3[4] = local_78;
        param_3[5] = local_74;
      }
    }
  }
  else {
    gnt4_PSVECSubtract_bl(param_2,param_1,afStack_94);
    gnt4_PSVECSubtract_bl(param_2 + 3,param_1,afStack_a0);
    gnt4_PSVECSubtract_bl(param_2,param_1 + 3,afStack_ac);
    gnt4_PSVECSubtract_bl(param_2 + 3,param_1 + 3,afStack_b8);
    dVar9 = gnt4_PSQUATDotProduct_bl(afStack_94,param_1 + 0xc);
    dVar10 = gnt4_PSQUATDotProduct_bl(afStack_a0,param_1 + 0xc);
    dVar7 = gnt4_PSQUATDotProduct_bl(afStack_ac,param_1 + 0xf);
    dVar11 = gnt4_PSQUATDotProduct_bl(afStack_b8,param_1 + 0xf);
    uVar5 = 0;
    if ((double)FLOAT_80436f68 <= dVar9) {
      uVar5 = 8;
    }
    if ((double)FLOAT_80436f68 <= dVar10) {
      uVar5 = uVar5 | 4;
    }
    if ((double)FLOAT_80436f68 <= dVar7) {
      uVar5 = uVar5 | 2;
    }
    if ((double)FLOAT_80436f68 <= dVar11) {
      uVar5 = uVar5 | 1;
    }
    switch(uVar5) {
    case 3:
      fVar4 = param_1[1];
      *param_3 = *param_1;
      param_3[1] = fVar4;
      param_3[2] = param_1[2];
      dVar9 = gnt4_PSVECSquareMag_bl(afStack_94);
      dVar10 = gnt4_PSVECSquareMag_bl(afStack_a0);
      if (dVar10 < dVar9) {
        fVar4 = param_2[4];
        param_3[3] = param_2[3];
        param_3[4] = fVar4;
        param_3[5] = param_2[5];
      }
      else {
        fVar4 = param_2[1];
        param_3[3] = *param_2;
        param_3[4] = fVar4;
        param_3[5] = param_2[2];
      }
      break;
    default:
      return 0;
    case 6:
    case 9:
      gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,param_1 + 0xc,afStack_88);
      gnt4_PSVECAdd_bl(param_1,afStack_88,param_3);
      gnt4_PSVECSubtract_bl(param_3,param_2,afStack_88);
      dVar9 = gnt4_PSQUATDotProduct_bl(afStack_88,param_2 + 0xc);
      gnt4_PSQUATScale_bl(dVar9,param_2 + 0xc,afStack_88);
      gnt4_PSVECAdd_bl(param_2,afStack_88,param_3 + 3);
      break;
    case 7:
      dVar9 = gnt4_PSQUATDotProduct_bl(afStack_a0,param_1 + 0xc);
      dVar9 = (double)(float)(dVar9 * (double)FLOAT_80436f7c);
      gnt4_PSQUATScale_bl(dVar9,param_1 + 0xc,afStack_88);
      gnt4_PSVECAdd_bl(param_1,afStack_88,param_3);
      gnt4_PSQUATScale_bl(dVar9,param_2 + 0xf,afStack_88);
      gnt4_PSVECAdd_bl(param_2 + 3,afStack_88,param_3 + 3);
      break;
    case 0xb:
      dVar9 = gnt4_PSQUATDotProduct_bl(afStack_94,param_1 + 0xc);
      dVar9 = (double)(float)(dVar9 * (double)FLOAT_80436f7c);
      gnt4_PSQUATScale_bl(dVar9,param_1 + 0xc,afStack_88);
      gnt4_PSVECAdd_bl(param_1,afStack_88,param_3);
      gnt4_PSQUATScale_bl(dVar9,param_2 + 0xc,afStack_88);
      gnt4_PSVECAdd_bl(param_2,afStack_88,param_3 + 3);
      break;
    case 0xc:
      fVar4 = param_1[4];
      *param_3 = param_1[3];
      param_3[1] = fVar4;
      param_3[2] = param_1[5];
      dVar9 = gnt4_PSVECSquareMag_bl(afStack_ac);
      dVar10 = gnt4_PSVECSquareMag_bl(afStack_b8);
      if (dVar10 < dVar9) {
        fVar4 = param_2[4];
        param_3[3] = param_2[3];
        param_3[4] = fVar4;
        param_3[5] = param_2[5];
      }
      else {
        fVar4 = param_2[1];
        param_3[3] = *param_2;
        param_3[4] = fVar4;
        param_3[5] = param_2[2];
      }
      break;
    case 0xd:
      dVar9 = gnt4_PSQUATDotProduct_bl(afStack_b8,param_1 + 0xf);
      dVar9 = (double)(float)(dVar9 * (double)FLOAT_80436f7c);
      gnt4_PSQUATScale_bl(dVar9,param_1 + 0xf,afStack_88);
      gnt4_PSVECAdd_bl(param_1 + 3,afStack_88,param_3);
      gnt4_PSQUATScale_bl(dVar9,param_2 + 0xf,afStack_88);
      gnt4_PSVECAdd_bl(param_2 + 3,afStack_88,param_3 + 3);
      break;
    case 0xe:
      dVar9 = gnt4_PSQUATDotProduct_bl(afStack_ac,param_1 + 0xf);
      dVar9 = (double)(float)(dVar9 * (double)FLOAT_80436f7c);
      gnt4_PSQUATScale_bl(dVar9,param_1 + 0xf,afStack_88);
      gnt4_PSVECAdd_bl(param_1 + 3,afStack_88,param_3);
      gnt4_PSQUATScale_bl(dVar9,param_2 + 0xc,afStack_88);
      gnt4_PSVECAdd_bl(param_2,afStack_88,param_3 + 3);
      break;
    case 0xf:
      gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,param_2 + 0xc,afStack_88);
      gnt4_PSVECAdd_bl(param_2,afStack_88,param_3 + 3);
      gnt4_PSVECSubtract_bl(param_3 + 3,param_1,afStack_88);
      dVar9 = gnt4_PSQUATDotProduct_bl(afStack_88,param_1 + 0xc);
      gnt4_PSQUATScale_bl(dVar9,param_1 + 0xc,afStack_88);
      gnt4_PSVECAdd_bl(param_1,afStack_88,param_3);
    }
  }
  gnt4_PSVECSubtract_bl(param_3,param_3 + 3,&local_4c);
  dVar9 = gnt4_PSVECMag_bl(&local_4c);
  if (dVar9 < (double)FLOAT_80436fc4) {
    *param_3 = *param_3 + FLOAT_80436f9c;
  }
  return 1;
}



// ==== 80039564  FUN_80039564 ====

/* WARNING: Removing unreachable block (ram,0x80039914) */
/* WARNING: Removing unreachable block (ram,0x8003990c) */
/* WARNING: Removing unreachable block (ram,0x80039904) */
/* WARNING: Removing unreachable block (ram,0x80039584) */
/* WARNING: Removing unreachable block (ram,0x8003957c) */
/* WARNING: Removing unreachable block (ram,0x80039574) */

undefined4 FUN_80039564(float *param_1,int param_2,float *param_3)

{
  float fVar1;
  undefined4 uVar2;
  byte bVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  
  local_54 = param_1[0xc];
  local_50 = param_1[0xd];
  local_4c = param_1[0xe];
  gnt4_PSVECSubtract_bl(param_1,(float *)(param_2 + 0xc),&local_60);
  fVar1 = local_54 * local_54 + local_50 * local_50 + local_4c * local_4c;
  dVar4 = (double)((local_54 * local_60 + local_50 * local_5c + local_4c * local_58) *
                  FLOAT_80436f9c);
  dVar6 = (double)((float)(dVar4 * dVar4) -
                  FLOAT_80436fa0 * fVar1 *
                  ((local_60 * local_60 + local_5c * local_5c + local_58 * local_58) -
                  *(float *)(param_2 + 0x30) * *(float *)(param_2 + 0x30)));
  if (dVar6 < (double)FLOAT_80436f68) {
    uVar2 = 0;
  }
  else {
    if ((double)FLOAT_80436f68 < dVar6) {
      dVar5 = 1.0 / SQRT(dVar6);
      dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar6 * dVar5 * dVar5 - DOUBLE_80436fd8);
      dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar6 * dVar5 * dVar5 - DOUBLE_80436fd8);
      dVar6 = (double)(float)(dVar6 * DOUBLE_80436fd0 * dVar5 *
                                      -(dVar6 * dVar5 * dVar5 - DOUBLE_80436fd8));
    }
    dVar4 = -dVar4;
    dVar7 = (double)(FLOAT_80436f9c * fVar1);
    gnt4_PSQUATScale_bl((double)(float)((double)(float)(dVar4 + dVar6) / dVar7),param_1 + 0xc,
                        &local_54);
    gnt4_PSVECAdd_bl(&local_54,param_1,&local_60);
    dVar5 = gnt4_PSQUATDotProduct_bl(&local_54,param_1 + 0xc);
    bVar3 = dVar5 < (double)FLOAT_80436f68;
    gnt4_PSVECSubtract_bl(&local_60,param_1 + 3,&local_54);
    dVar5 = gnt4_PSQUATDotProduct_bl(&local_54,param_1 + 0xf);
    if (dVar5 < (double)FLOAT_80436f68) {
      bVar3 = bVar3 | 2;
    }
    gnt4_PSQUATScale_bl((double)(float)((double)(float)(dVar4 - dVar6) / dVar7),param_1 + 0xc,
                        &local_54);
    gnt4_PSVECAdd_bl(&local_54,param_1,&local_6c);
    dVar4 = gnt4_PSQUATDotProduct_bl(&local_54,param_1 + 0xc);
    if (dVar4 < (double)FLOAT_80436f68) {
      bVar3 = bVar3 | 4;
    }
    gnt4_PSVECSubtract_bl(&local_6c,param_1 + 3,&local_54);
    dVar4 = gnt4_PSQUATDotProduct_bl(&local_54,param_1 + 0xf);
    if (dVar4 < (double)FLOAT_80436f68) {
      bVar3 = bVar3 | 8;
    }
    switch(bVar3) {
    default:
      dVar4 = gnt4_PSVECSquareDistance_bl(&local_60,param_1);
      if ((double)FLOAT_80436f68 < dVar4) {
        dVar6 = 1.0 / SQRT(dVar4);
        dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar4 * dVar6 * dVar6 - DOUBLE_80436fd8);
        dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar4 * dVar6 * dVar6 - DOUBLE_80436fd8);
        dVar4 = (double)(float)(dVar4 * DOUBLE_80436fd0 * dVar6 *
                                        -(dVar4 * dVar6 * dVar6 - DOUBLE_80436fd8));
      }
      dVar6 = gnt4_PSVECSquareDistance_bl(&local_6c,param_1);
      if ((double)FLOAT_80436f68 < dVar6) {
        dVar5 = 1.0 / SQRT(dVar6);
        dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar6 * dVar5 * dVar5 - DOUBLE_80436fd8);
        dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar6 * dVar5 * dVar5 - DOUBLE_80436fd8);
        dVar6 = (double)(float)(dVar6 * DOUBLE_80436fd0 * dVar5 *
                                        -(dVar6 * dVar5 * dVar5 - DOUBLE_80436fd8));
      }
      if (dVar4 <= dVar6) {
        *param_3 = local_60;
        param_3[1] = local_5c;
        param_3[2] = local_58;
      }
      else {
        *param_3 = local_6c;
        param_3[1] = local_68;
        param_3[2] = local_64;
      }
      uVar2 = 2;
      break;
    case 1:
    case 2:
      uVar2 = 1;
      *param_3 = local_6c;
      param_3[1] = local_68;
      param_3[2] = local_64;
      break;
    case 4:
    case 8:
      uVar2 = 1;
      *param_3 = local_60;
      param_3[1] = local_5c;
      param_3[2] = local_58;
    }
  }
  return uVar2;
}



// ==== 80039938  zz_0039938_ ====

undefined4 zz_0039938_(int *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  
  iVar4 = 0;
  pcVar3 = &DAT_802cffc8 + *param_1 * 4;
  iVar2 = 0;
  iVar5 = 4;
  while( true ) {
    iVar1 = param_1[1] * 4;
    if ((int)*pcVar3 == (int)(char)(&DAT_802cffc8)[iVar1]) {
      *(int *)(param_2 + iVar2) = (int)*pcVar3;
      iVar4 = iVar4 + 1;
      iVar2 = iVar2 + 4;
    }
    if (iVar4 == 2) {
      return 1;
    }
    if ((int)*pcVar3 == (int)(char)(&DAT_802cffc9)[iVar1]) {
      *(int *)(param_2 + iVar2) = (int)*pcVar3;
      iVar4 = iVar4 + 1;
      iVar2 = iVar2 + 4;
    }
    if (iVar4 == 2) break;
    if ((int)*pcVar3 == (int)(char)(&DAT_802cffca)[iVar1]) {
      *(int *)(param_2 + iVar2) = (int)*pcVar3;
      iVar4 = iVar4 + 1;
      iVar2 = iVar2 + 4;
    }
    if (iVar4 == 2) {
      return 1;
    }
    if ((int)*pcVar3 == (int)(char)(&DAT_802cffcb)[iVar1]) {
      *(int *)(param_2 + iVar2) = (int)*pcVar3;
      iVar4 = iVar4 + 1;
      iVar2 = iVar2 + 4;
    }
    if (iVar4 == 2) {
      return 1;
    }
    pcVar3 = pcVar3 + 1;
    iVar5 = iVar5 + -1;
    if (iVar5 == 0) {
      return 0;
    }
  }
  return 1;
}



// ==== 80039a48  zz_0039a48_ ====

undefined4 zz_0039a48_(int *param_1,int *param_2)

{
  int iVar1;
  int iVar2;
  char *pcVar3;
  int local_18;
  int local_14;
  
  iVar2 = zz_0039938_(param_1,(int)&local_18);
  if (iVar2 != 0) {
    pcVar3 = &DAT_802cffc8 + param_1[2] * 4;
    iVar2 = 4;
    do {
      iVar1 = (int)*pcVar3;
      if (iVar1 == local_18) {
        *param_2 = iVar1;
        return 1;
      }
      if (iVar1 == local_14) {
        *param_2 = iVar1;
        return 1;
      }
      pcVar3 = pcVar3 + 1;
      iVar2 = iVar2 + -1;
    } while (iVar2 != 0);
  }
  return 0;
}



// ==== 80039aec  zz_0039aec_ ====

uint zz_0039aec_(float *param_1,float *param_2,float *param_3)

{
  uint uVar1;
  double dVar2;
  float afStack_38 [3];
  float afStack_2c [3];
  float afStack_20 [5];
  
  gnt4_PSVECSubtract_bl(param_2,param_1,afStack_2c);
  gnt4_PSVECSubtract_bl(param_2 + 3,param_1,afStack_38);
  gnt4_PSVECCrossProduct_bl(afStack_2c,afStack_38,afStack_20);
  dVar2 = gnt4_PSQUATDotProduct_bl(afStack_20,param_3);
  if ((double)FLOAT_80436f68 <= dVar2) {
    gnt4_PSVECSubtract_bl(param_2 + 3,param_1,afStack_2c);
    gnt4_PSVECSubtract_bl(param_2 + 6,param_1,afStack_38);
    gnt4_PSVECCrossProduct_bl(afStack_2c,afStack_38,afStack_20);
    dVar2 = gnt4_PSQUATDotProduct_bl(afStack_20,param_3);
    if ((double)FLOAT_80436f68 <= dVar2) {
      gnt4_PSVECSubtract_bl(param_2 + 6,param_1,afStack_2c);
      gnt4_PSVECSubtract_bl(param_2,param_1,afStack_38);
      gnt4_PSVECCrossProduct_bl(afStack_2c,afStack_38,afStack_20);
      dVar2 = gnt4_PSQUATDotProduct_bl(afStack_20,param_3);
      uVar1 = countLeadingZeros((uint)(dVar2 < (double)FLOAT_80436f68));
      uVar1 = uVar1 >> 5;
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80039c20  zz_0039c20_ ====

uint zz_0039c20_(float *param_1,float *param_2,float *param_3)

{
  uint uVar1;
  double dVar2;
  float afStack_38 [3];
  float afStack_2c [3];
  float afStack_20 [5];
  
  gnt4_PSVECSubtract_bl(param_2,param_1,afStack_2c);
  gnt4_PSVECSubtract_bl(param_2 + 3,param_1,afStack_38);
  gnt4_PSVECCrossProduct_bl(afStack_2c,afStack_38,afStack_20);
  dVar2 = gnt4_PSQUATDotProduct_bl(afStack_20,param_3);
  if ((double)FLOAT_80436f68 <= dVar2) {
    gnt4_PSVECSubtract_bl(param_2 + 3,param_1,afStack_2c);
    gnt4_PSVECSubtract_bl(param_2 + 6,param_1,afStack_38);
    gnt4_PSVECCrossProduct_bl(afStack_2c,afStack_38,afStack_20);
    dVar2 = gnt4_PSQUATDotProduct_bl(afStack_20,param_3);
    if ((double)FLOAT_80436f68 <= dVar2) {
      gnt4_PSVECSubtract_bl(param_2 + 6,param_1,afStack_2c);
      gnt4_PSVECSubtract_bl(param_2 + 9,param_1,afStack_38);
      gnt4_PSVECCrossProduct_bl(afStack_2c,afStack_38,afStack_20);
      dVar2 = gnt4_PSQUATDotProduct_bl(afStack_20,param_3);
      if ((double)FLOAT_80436f68 <= dVar2) {
        gnt4_PSVECSubtract_bl(param_2 + 9,param_1,afStack_2c);
        gnt4_PSVECSubtract_bl(param_2,param_1,afStack_38);
        gnt4_PSVECCrossProduct_bl(afStack_2c,afStack_38,afStack_20);
        dVar2 = gnt4_PSQUATDotProduct_bl(afStack_20,param_3);
        uVar1 = countLeadingZeros((uint)(dVar2 < (double)FLOAT_80436f68));
        uVar1 = uVar1 >> 5;
      }
      else {
        uVar1 = 0;
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 80039da4  FUN_80039da4 ====

/* WARNING: Removing unreachable block (ram,0x80039f50) */
/* WARNING: Removing unreachable block (ram,0x80039f48) */
/* WARNING: Removing unreachable block (ram,0x80039dbc) */
/* WARNING: Removing unreachable block (ram,0x80039db4) */
/* WARNING: Removing unreachable block (ram,0x80039e7c) */

byte FUN_80039da4(float *param_1,float *param_2,float *param_3,float *param_4)

{
  byte bVar1;
  double dVar2;
  double dVar3;
  float afStack_68 [3];
  float afStack_5c [3];
  float afStack_50 [6];
  
  gnt4_PSVECSubtract_bl(param_1 + 3,param_1,afStack_5c);
  gnt4_PSVECSubtract_bl(param_1,param_1 + 3,afStack_50);
  gnt4_PSVECSubtract_bl(param_1,param_3,afStack_68);
  dVar2 = gnt4_PSQUATDotProduct_bl(afStack_68,param_2);
  bVar1 = (double)FLOAT_80436f68 <= dVar2;
  gnt4_PSVECSubtract_bl(param_1 + 3,param_3,afStack_68);
  dVar3 = gnt4_PSQUATDotProduct_bl(afStack_68,param_2);
  if ((double)FLOAT_80436f68 <= dVar3) {
    bVar1 = bVar1 | 2;
  }
  if (bVar1 == 2) {
    dVar2 = gnt4_PSQUATDotProduct_bl(afStack_5c,param_2);
    if (((double)FLOAT_80436f68 == dVar2) || ((double)FLOAT_80436fcc == dVar2)) {
      gnt4_PSQUATScale_bl(dVar3,param_2,afStack_68);
    }
    else {
      gnt4_PSQUATScale_bl((double)(float)(dVar3 / dVar2),afStack_5c,afStack_68);
    }
    gnt4_PSVECSubtract_bl(param_1 + 3,afStack_68,param_4);
    bVar1 = 2;
  }
  else {
    if (bVar1 < 2) {
      if (bVar1 != 0) {
        dVar3 = gnt4_PSQUATDotProduct_bl(afStack_50,param_2);
        if (((double)FLOAT_80436f68 == dVar3) || ((double)FLOAT_80436fcc == dVar3)) {
          gnt4_PSQUATScale_bl(dVar2,param_2,afStack_68);
        }
        else {
          gnt4_PSQUATScale_bl((double)(float)(dVar2 / dVar3),afStack_50,afStack_68);
        }
        gnt4_PSVECSubtract_bl(param_1,afStack_68,param_4);
        return bVar1;
      }
    }
    else if (3 < bVar1) {
      return bVar1;
    }
    bVar1 = 0;
  }
  return bVar1;
}



// ==== 80039f6c  zz_0039f6c_ ====

undefined4 zz_0039f6c_(int param_1,int param_2)

{
  undefined4 uVar1;
  double dVar2;
  double dVar3;
  
  if (FLOAT_80437004 < *(float *)(param_1 + 0x24)) {
    if (FLOAT_80437004 < *(float *)(param_2 + 0x24)) {
      dVar2 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0xc),(float *)(param_2 + 0xc));
      if ((double)FLOAT_80436f68 < dVar2) {
        dVar3 = 1.0 / SQRT(dVar2);
        dVar3 = DOUBLE_80436fd0 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80436fd8);
        dVar3 = DOUBLE_80436fd0 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80436fd8);
        dVar2 = (double)(float)(dVar2 * DOUBLE_80436fd0 * dVar3 *
                                        -(dVar2 * dVar3 * dVar3 - DOUBLE_80436fd8));
      }
      if ((double)(*(float *)(param_1 + 0x24) + *(float *)(param_2 + 0x24)) < dVar2) {
        uVar1 = 0;
      }
      else {
        uVar1 = 1;
      }
    }
    else {
      uVar1 = 0;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}



// ==== 8003a05c  zz_003a05c_ ====

void zz_003a05c_(int param_1,int param_2,int param_3,int param_4)

{
  if (*(char *)(param_3 + 0x1dd) != '\0') {
    gnt4_PSVECAdd_bl((float *)(param_3 + 0x1cc),(float *)(param_1 + 0xc),(float *)(param_1 + 0xc));
  }
  if (*(char *)(param_4 + 0x1dd) != '\0') {
    gnt4_PSVECAdd_bl((float *)(param_4 + 0x1cc),(float *)(param_2 + 0xc),(float *)(param_2 + 0xc));
  }
  return;
}



// ==== 8003a0cc  FUN_8003a0cc ====

/* WARNING: Removing unreachable block (ram,0x8003a238) */
/* WARNING: Removing unreachable block (ram,0x8003a0dc) */

void FUN_8003a0cc(int param_1)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  char *pcVar4;
  float *pfVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  double dVar10;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  
  iVar9 = 0;
  iVar8 = *(int *)(*(int *)(param_1 + 4) + 0x20);
  iVar7 = param_1;
  do {
    gnt4_PSVECAdd_bl((float *)(iVar8 + 0x1cc),(float *)(iVar7 + 0x30),(float *)(iVar7 + 0x30));
    iVar9 = iVar9 + 1;
    iVar7 = iVar7 + 0xc;
  } while (iVar9 < 8);
  dVar10 = (double)FLOAT_80436f68;
  pcVar4 = &DAT_802cffc8;
  iVar8 = 0;
  iVar7 = param_1;
  do {
    cVar3 = *pcVar4;
    pcVar1 = pcVar4 + 1;
    pcVar2 = pcVar4 + 2;
    pcVar4 = pcVar4 + 4;
    pfVar6 = (float *)(param_1 + cVar3 * 0xc + 0x30);
    local_30 = *pfVar6;
    local_2c = pfVar6[1];
    pfVar5 = (float *)(param_1 + *pcVar1 * 0xc + 0x30);
    local_28 = pfVar6[2];
    pfVar6 = (float *)(param_1 + *pcVar2 * 0xc + 0x30);
    local_3c = *pfVar5;
    local_38 = pfVar5[1];
    local_34 = pfVar5[2];
    local_48 = *pfVar6;
    local_44 = pfVar6[1];
    local_40 = pfVar6[2];
    gnt4_PSVECSubtract_bl(&local_3c,&local_30,&local_3c);
    gnt4_PSVECSubtract_bl(&local_48,&local_30,&local_48);
    gnt4_PSVECCrossProduct_bl(&local_3c,&local_48,(float *)(iVar7 + 0x90));
    if (dVar10 < (double)(*(float *)(iVar7 + 0x98) * *(float *)(iVar7 + 0x98) +
                         *(float *)(iVar7 + 0x90) * *(float *)(iVar7 + 0x90) +
                         *(float *)(iVar7 + 0x94) * *(float *)(iVar7 + 0x94))) {
      gnt4_PSVECNormalize_bl((float *)(iVar7 + 0x90),(float *)(iVar7 + 0x90));
    }
    iVar8 = iVar8 + 1;
    iVar7 = iVar7 + 0x18;
  } while (iVar8 < 6);
  return;
}



// ==== 8003a260  FUN_8003a260 ====

void FUN_8003a260(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 4) + 0x20);
  gnt4_PSVECAdd_bl((float *)(iVar1 + 0x1cc),(float *)(param_1 + 0x34),(float *)(param_1 + 0x34));
  gnt4_PSVECAdd_bl((float *)(iVar1 + 0x1cc),(float *)(param_1 + 0x40),(float *)(param_1 + 0x40));
  return;
}



// ==== 8003a2b8  FUN_8003a2b8 ====

void FUN_8003a2b8(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  float afStack_28 [3];
  float afStack_1c [3];
  
  iVar1 = 0;
  iVar2 = *(int *)(*(int *)(param_1 + 4) + 0x20);
  iVar3 = param_1;
  do {
    gnt4_PSVECAdd_bl((float *)(iVar2 + 0x1cc),(float *)(iVar3 + 0x34),(float *)(iVar3 + 0x34));
    iVar1 = iVar1 + 1;
    iVar3 = iVar3 + 0xc;
  } while (iVar1 < 6);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x40),(float *)(param_1 + 0x34),afStack_28);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x4c),(float *)(param_1 + 0x40),afStack_1c);
  gnt4_PSVECCrossProduct_bl(afStack_28,afStack_1c,(float *)(param_1 + 0x7c));
  if (FLOAT_80436f68 <
      *(float *)(param_1 + 0x84) * *(float *)(param_1 + 0x84) +
      *(float *)(param_1 + 0x7c) * *(float *)(param_1 + 0x7c) +
      *(float *)(param_1 + 0x80) * *(float *)(param_1 + 0x80)) {
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0x7c),(float *)(param_1 + 0x7c));
    gnt4_PSVECSubtract_bl((float *)(param_1 + 100),(float *)(param_1 + 0x58),afStack_28);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x70),(float *)(param_1 + 100),afStack_1c);
    gnt4_PSVECCrossProduct_bl(afStack_28,afStack_1c,(float *)(param_1 + 0x94));
    if (FLOAT_80436f68 <
        *(float *)(param_1 + 0x9c) * *(float *)(param_1 + 0x9c) +
        *(float *)(param_1 + 0x94) * *(float *)(param_1 + 0x94) +
        *(float *)(param_1 + 0x98) * *(float *)(param_1 + 0x98)) {
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x94),(float *)(param_1 + 0x94));
    }
  }
  return;
}



// ==== 8003a3fc  FUN_8003a3fc ====

void FUN_8003a3fc(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = *(int *)(*(int *)(param_1 + 4) + 0x20);
  do {
    gnt4_PSVECAdd_bl((float *)(iVar2 + 0x1cc),(float *)(param_1 + 0x50),(float *)(param_1 + 0x50));
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 0xc;
  } while (iVar1 < 6);
  return;
}



// ==== 8003a460  FUN_8003a460 ====

void FUN_8003a460(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(*(int *)(param_1 + 4) + 0x20);
  gnt4_PSVECAdd_bl((float *)(iVar1 + 0x1cc),(float *)(param_1 + 0x34),(float *)(param_1 + 0x34));
  gnt4_PSVECAdd_bl((float *)(iVar1 + 0x1cc),(float *)(param_1 + 0x40),(float *)(param_1 + 0x40));
  return;
}



// ==== 8003a4b8  FUN_8003a4b8 ====

void FUN_8003a4b8(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x28);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),(float *)(iVar1 + 0xc),(float *)(param_1 + 100));
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x6c);
  *(float *)(param_1 + 0x88) =
       *(float *)(iVar1 + 0x18) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
  *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_1 + 0x88);
  *(undefined4 *)(param_1 + 0x58) = 0;
  if ((*(ushort *)(iVar1 + 2) & 0x10) == 0) {
    *(float *)(param_1 + 0x7c) =
         *(float *)(iVar1 + 0x18) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
  }
  else {
    *(float *)(param_1 + 0x7c) = FLOAT_80437008 * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
  }
  if (((*(ushort *)(iVar1 + 2) & 1) != 0) || ((*(ushort *)(iVar1 + 2) & 0x80) != 0)) {
    *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_1 + 100);
    *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(param_1 + 0x68);
    *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(param_1 + 0x6c);
    *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_1 + 100);
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x68);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x6c);
    *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(param_1 + 100);
    *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0x68);
    *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(param_1 + 0x6c);
    *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_1 + 100);
    *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(param_1 + 0x68);
    *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_1 + 0x6c);
  }
  return;
}



// ==== 8003a5e4  FUN_8003a5e4 ====

/* WARNING: Removing unreachable block (ram,0x8003a8dc) */
/* WARNING: Removing unreachable block (ram,0x8003a5f4) */

void FUN_8003a5e4(int param_1)

{
  int iVar1;
  double dVar2;
  double dVar3;
  
  iVar1 = *(int *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x6c);
  *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_1 + 0x88);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),(float *)(iVar1 + 0xc),(float *)(param_1 + 100));
  if (((*(ushort *)(iVar1 + 2) & 1) != 0) || ((*(ushort *)(iVar1 + 2) & 0x80) != 0)) {
    *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(param_1 + 0x8c);
    *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0x90);
    *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(param_1 + 0x94);
    *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_1 + 0x98);
    *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(param_1 + 0x9c);
    *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_1 + 0xa0);
    dVar2 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 100),(float *)(param_1 + 0x98));
    if ((double)FLOAT_80436f68 < dVar2) {
      dVar3 = 1.0 / SQRT(dVar2);
      dVar3 = DOUBLE_80436fd0 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80436fd8);
      dVar3 = DOUBLE_80436fd0 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80436fd8);
      dVar2 = (double)(float)(dVar2 * DOUBLE_80436fd0 * dVar3 *
                                      -(dVar2 * dVar3 * dVar3 - DOUBLE_80436fd8));
    }
    dVar3 = (double)FLOAT_80436f7c;
    *(undefined4 *)(param_1 + 0x8c) = *(undefined4 *)(param_1 + 0x98);
    *(undefined4 *)(param_1 + 0x90) = *(undefined4 *)(param_1 + 0x9c);
    *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(param_1 + 0xa0);
    *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 0x98);
    *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x9c);
    *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0xa0);
    *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_1 + 100);
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x68);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x6c);
    if (dVar3 < dVar2) {
      *(undefined1 *)(param_1 + 0x13) = 1;
      *(undefined4 *)(param_1 + 0x58) = 2;
      *(float *)(param_1 + 0x88) =
           *(float *)(iVar1 + 0x18) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
      gnt4_PSVECSubtract_bl
                ((float *)(param_1 + 0x98),(float *)(param_1 + 0x8c),(float *)(param_1 + 0xa4));
      gnt4_PSVECSubtract_bl
                ((float *)(param_1 + 0x8c),(float *)(param_1 + 0x98),(float *)(param_1 + 0xb0));
      if (*(float *)(param_1 + 0xac) * *(float *)(param_1 + 0xac) +
          *(float *)(param_1 + 0xa4) * *(float *)(param_1 + 0xa4) +
          *(float *)(param_1 + 0xa8) * *(float *)(param_1 + 0xa8) <= FLOAT_80436f68) {
        return;
      }
      if (*(float *)(param_1 + 0xb8) * *(float *)(param_1 + 0xb8) +
          *(float *)(param_1 + 0xb0) * *(float *)(param_1 + 0xb0) +
          *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0xb4) <= FLOAT_80436f68) {
        return;
      }
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0xa4),(float *)(param_1 + 0xbc));
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0xb0),(float *)(param_1 + 200));
      gnt4_PSVECAdd_bl((float *)(param_1 + 0x8c),(float *)(param_1 + 0x98),(float *)(param_1 + 100))
      ;
      gnt4_PSQUATScale_bl((double)FLOAT_80436f7c,(float *)(param_1 + 100),(float *)(param_1 + 100));
      *(float *)(param_1 + 0x7c) =
           (float)(dVar2 * (double)FLOAT_80436f7c) + *(float *)(param_1 + 0x88);
      return;
    }
  }
  dVar2 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 100),(float *)(param_1 + 0x70));
  if ((double)FLOAT_80436f68 < dVar2) {
    dVar3 = 1.0 / SQRT(dVar2);
    dVar3 = DOUBLE_80436fd0 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80436fd8);
    dVar3 = DOUBLE_80436fd0 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80436fd8);
    dVar2 = (double)(float)(dVar2 * DOUBLE_80436fd0 * dVar3 *
                                    -(dVar2 * dVar3 * dVar3 - DOUBLE_80436fd8));
  }
  *(undefined4 *)(param_1 + 0x58) = 0;
  *(float *)(param_1 + 0x88) =
       *(float *)(iVar1 + 0x18) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
  if ((*(ushort *)(iVar1 + 2) & 0x10) == 0) {
    *(float *)(param_1 + 0x7c) =
         (float)((double)*(float *)(iVar1 + 0x18) *
                 (double)*(float *)(*(int *)(param_1 + 0x20) + 0xc0) + dVar2);
  }
  else {
    *(float *)(param_1 + 0x7c) =
         (float)((double)FLOAT_80437008 * (double)*(float *)(*(int *)(param_1 + 0x20) + 0xc0) +
                dVar2);
  }
  return;
}



// ==== 8003a8fc  FUN_8003a8fc ====

/* WARNING: Removing unreachable block (ram,0x8003acdc) */
/* WARNING: Removing unreachable block (ram,0x8003a90c) */

void FUN_8003a8fc(int param_1)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  char *pcVar4;
  undefined4 uVar5;
  float *pfVar6;
  int iVar7;
  undefined4 *puVar8;
  float *pfVar9;
  undefined4 *puVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  
  puVar8 = (undefined4 *)(param_1 + 0x58);
  iVar7 = *(int *)(param_1 + 0x28);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),(float *)(iVar7 + 0xc),(float *)(param_1 + 100));
  *puVar8 = 1;
  pfVar9 = (float *)&DAT_802cffe0;
  iVar11 = 0;
  puVar10 = puVar8;
  do {
    local_40 = *pfVar9;
    local_3c = pfVar9[1];
    local_38 = pfVar9[2];
    puVar10[0xc] = *(float *)(iVar7 + 0x18) * local_40 + *(float *)(iVar7 + 0xc);
    puVar10[0xd] = *(float *)(iVar7 + 0x1c) * local_3c + *(float *)(iVar7 + 0x10);
    puVar10[0xe] = *(float *)(iVar7 + 0x20) * local_38 + *(float *)(iVar7 + 0x14);
    gnt4_PSMTXMultVec_bl
              (*(float **)(param_1 + 0x60),(float *)(puVar10 + 0xc),(float *)(puVar10 + 0xc));
    iVar11 = iVar11 + 1;
    puVar10 = puVar10 + 3;
    pfVar9 = pfVar9 + 3;
  } while (iVar11 < 8);
  dVar13 = (double)FLOAT_80436f68;
  pcVar4 = &DAT_802cffc8;
  iVar7 = 0;
  puVar10 = puVar8;
  do {
    cVar3 = *pcVar4;
    pcVar1 = pcVar4 + 1;
    pcVar2 = pcVar4 + 2;
    pcVar4 = pcVar4 + 4;
    pfVar9 = (float *)(puVar8 + cVar3 * 3 + 0xc);
    local_4c = *pfVar9;
    local_48 = pfVar9[1];
    pfVar6 = (float *)(puVar8 + *pcVar1 * 3 + 0xc);
    local_44 = pfVar9[2];
    pfVar9 = (float *)(puVar8 + *pcVar2 * 3 + 0xc);
    local_58 = *pfVar6;
    local_54 = pfVar6[1];
    local_50 = pfVar6[2];
    local_64 = *pfVar9;
    local_60 = pfVar9[1];
    local_5c = pfVar9[2];
    gnt4_PSVECSubtract_bl(&local_58,&local_4c,&local_58);
    gnt4_PSVECSubtract_bl(&local_64,&local_4c,&local_64);
    gnt4_PSVECCrossProduct_bl(&local_58,&local_64,(float *)(puVar10 + 0x24));
    if ((double)((float)puVar10[0x26] * (float)puVar10[0x26] +
                (float)puVar10[0x24] * (float)puVar10[0x24] +
                (float)puVar10[0x25] * (float)puVar10[0x25]) <= dVar13) {
      return;
    }
    gnt4_PSVECNormalize_bl((float *)(puVar10 + 0x24),(float *)(puVar10 + 0x24));
    iVar7 = iVar7 + 1;
    puVar10 = puVar10 + 6;
  } while (iVar7 < 6);
  dVar13 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x88),(float *)(param_1 + 100));
  *(float *)(param_1 + 0x7c) = (float)dVar13;
  dVar13 = (double)*(float *)(param_1 + 0x7c);
  if ((double)FLOAT_80436f68 < dVar13) {
    dVar12 = 1.0 / SQRT(dVar13);
    dVar12 = DOUBLE_80436fd0 * dVar12 * -(dVar13 * dVar12 * dVar12 - DOUBLE_80436fd8);
    dVar12 = DOUBLE_80436fd0 * dVar12 * -(dVar13 * dVar12 * dVar12 - DOUBLE_80436fd8);
    dVar13 = (double)(float)(dVar13 * DOUBLE_80436fd0 * dVar12 *
                                      -(dVar13 * dVar12 * dVar12 - DOUBLE_80436fd8));
  }
  *(float *)(param_1 + 0x7c) = (float)dVar13;
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x6c);
  *(undefined4 *)(param_1 + 0xf4) = *(undefined4 *)(param_1 + 0xe8);
  *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(param_1 + 0xec);
  *(undefined4 *)(param_1 + 0xfc) = *(undefined4 *)(param_1 + 0xf0);
  cVar3 = DAT_802cffc8;
  uVar5 = puVar8[DAT_802cffc8 * 3 + 0xd];
  *(undefined4 *)(param_1 + 0x178) = puVar8[DAT_802cffc8 * 3 + 0xc];
  *(undefined4 *)(param_1 + 0x17c) = uVar5;
  *(undefined4 *)(param_1 + 0x180) = puVar8[cVar3 * 3 + 0xe];
  *(undefined4 *)(param_1 + 0x10c) = *(undefined4 *)(param_1 + 0x100);
  *(undefined4 *)(param_1 + 0x110) = *(undefined4 *)(param_1 + 0x104);
  *(undefined4 *)(param_1 + 0x114) = *(undefined4 *)(param_1 + 0x108);
  cVar3 = DAT_802cffcc;
  uVar5 = puVar8[DAT_802cffcc * 3 + 0xd];
  *(undefined4 *)(param_1 + 0x184) = puVar8[DAT_802cffcc * 3 + 0xc];
  *(undefined4 *)(param_1 + 0x188) = uVar5;
  *(undefined4 *)(param_1 + 0x18c) = puVar8[cVar3 * 3 + 0xe];
  *(undefined4 *)(param_1 + 0x124) = *(undefined4 *)(param_1 + 0x118);
  *(undefined4 *)(param_1 + 0x128) = *(undefined4 *)(param_1 + 0x11c);
  *(undefined4 *)(param_1 + 300) = *(undefined4 *)(param_1 + 0x120);
  cVar3 = DAT_802cffd0;
  uVar5 = puVar8[DAT_802cffd0 * 3 + 0xd];
  *(undefined4 *)(param_1 + 400) = puVar8[DAT_802cffd0 * 3 + 0xc];
  *(undefined4 *)(param_1 + 0x194) = uVar5;
  *(undefined4 *)(param_1 + 0x198) = puVar8[cVar3 * 3 + 0xe];
  *(undefined4 *)(param_1 + 0x13c) = *(undefined4 *)(param_1 + 0x130);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x134);
  *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x138);
  cVar3 = DAT_802cffd4;
  uVar5 = puVar8[DAT_802cffd4 * 3 + 0xd];
  *(undefined4 *)(param_1 + 0x19c) = puVar8[DAT_802cffd4 * 3 + 0xc];
  *(undefined4 *)(param_1 + 0x1a0) = uVar5;
  *(undefined4 *)(param_1 + 0x1a4) = puVar8[cVar3 * 3 + 0xe];
  *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x14c);
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x150);
  cVar3 = DAT_802cffd8;
  uVar5 = puVar8[DAT_802cffd8 * 3 + 0xd];
  *(undefined4 *)(param_1 + 0x1a8) = puVar8[DAT_802cffd8 * 3 + 0xc];
  *(undefined4 *)(param_1 + 0x1ac) = uVar5;
  *(undefined4 *)(param_1 + 0x1b0) = puVar8[cVar3 * 3 + 0xe];
  *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(param_1 + 0x160);
  *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_1 + 0x164);
  *(undefined4 *)(param_1 + 0x174) = *(undefined4 *)(param_1 + 0x168);
  cVar3 = DAT_802cffdc;
  uVar5 = puVar8[DAT_802cffdc * 3 + 0xd];
  *(undefined4 *)(param_1 + 0x1b4) = puVar8[DAT_802cffdc * 3 + 0xc];
  *(undefined4 *)(param_1 + 0x1b8) = uVar5;
  *(undefined4 *)(param_1 + 0x1bc) = puVar8[cVar3 * 3 + 0xe];
  return;
}



// ==== 8003acf8  FUN_8003acf8 ====

/* WARNING: Removing unreachable block (ram,0x8003b154) */
/* WARNING: Removing unreachable block (ram,0x8003ad08) */

void FUN_8003acf8(int param_1)

{
  char *pcVar1;
  char *pcVar2;
  char cVar3;
  undefined4 uVar4;
  char *pcVar5;
  float *pfVar6;
  int iVar7;
  undefined4 *puVar8;
  int iVar9;
  float *pfVar10;
  undefined4 *puVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  float local_60;
  float local_5c;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  float local_38;
  float local_34;
  
  puVar8 = (undefined4 *)(param_1 + 0x58);
  iVar9 = *(int *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x6c);
  *(undefined4 *)(param_1 + 0xf4) = *(undefined4 *)(param_1 + 0xe8);
  *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(param_1 + 0xec);
  *(undefined4 *)(param_1 + 0xfc) = *(undefined4 *)(param_1 + 0xf0);
  cVar3 = DAT_802cffc8;
  uVar4 = puVar8[DAT_802cffc8 * 3 + 0xd];
  *(undefined4 *)(param_1 + 0x178) = puVar8[DAT_802cffc8 * 3 + 0xc];
  *(undefined4 *)(param_1 + 0x17c) = uVar4;
  *(undefined4 *)(param_1 + 0x180) = puVar8[cVar3 * 3 + 0xe];
  *(undefined4 *)(param_1 + 0x10c) = *(undefined4 *)(param_1 + 0x100);
  *(undefined4 *)(param_1 + 0x110) = *(undefined4 *)(param_1 + 0x104);
  *(undefined4 *)(param_1 + 0x114) = *(undefined4 *)(param_1 + 0x108);
  cVar3 = DAT_802cffcc;
  uVar4 = puVar8[DAT_802cffcc * 3 + 0xd];
  *(undefined4 *)(param_1 + 0x184) = puVar8[DAT_802cffcc * 3 + 0xc];
  *(undefined4 *)(param_1 + 0x188) = uVar4;
  *(undefined4 *)(param_1 + 0x18c) = puVar8[cVar3 * 3 + 0xe];
  *(undefined4 *)(param_1 + 0x124) = *(undefined4 *)(param_1 + 0x118);
  *(undefined4 *)(param_1 + 0x128) = *(undefined4 *)(param_1 + 0x11c);
  *(undefined4 *)(param_1 + 300) = *(undefined4 *)(param_1 + 0x120);
  cVar3 = DAT_802cffd0;
  uVar4 = puVar8[DAT_802cffd0 * 3 + 0xd];
  *(undefined4 *)(param_1 + 400) = puVar8[DAT_802cffd0 * 3 + 0xc];
  *(undefined4 *)(param_1 + 0x194) = uVar4;
  *(undefined4 *)(param_1 + 0x198) = puVar8[cVar3 * 3 + 0xe];
  *(undefined4 *)(param_1 + 0x13c) = *(undefined4 *)(param_1 + 0x130);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x134);
  *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x138);
  cVar3 = DAT_802cffd4;
  uVar4 = puVar8[DAT_802cffd4 * 3 + 0xd];
  *(undefined4 *)(param_1 + 0x19c) = puVar8[DAT_802cffd4 * 3 + 0xc];
  *(undefined4 *)(param_1 + 0x1a0) = uVar4;
  *(undefined4 *)(param_1 + 0x1a4) = puVar8[cVar3 * 3 + 0xe];
  *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x14c);
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x150);
  cVar3 = DAT_802cffd8;
  uVar4 = puVar8[DAT_802cffd8 * 3 + 0xd];
  *(undefined4 *)(param_1 + 0x1a8) = puVar8[DAT_802cffd8 * 3 + 0xc];
  *(undefined4 *)(param_1 + 0x1ac) = uVar4;
  *(undefined4 *)(param_1 + 0x1b0) = puVar8[cVar3 * 3 + 0xe];
  *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(param_1 + 0x160);
  *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_1 + 0x164);
  *(undefined4 *)(param_1 + 0x174) = *(undefined4 *)(param_1 + 0x168);
  cVar3 = DAT_802cffdc;
  uVar4 = puVar8[DAT_802cffdc * 3 + 0xd];
  *(undefined4 *)(param_1 + 0x1b4) = puVar8[DAT_802cffdc * 3 + 0xc];
  *(undefined4 *)(param_1 + 0x1b8) = uVar4;
  *(undefined4 *)(param_1 + 0x1bc) = puVar8[cVar3 * 3 + 0xe];
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),(float *)(iVar9 + 0xc),(float *)(param_1 + 100));
  *puVar8 = 1;
  pfVar10 = (float *)&DAT_802cffe0;
  iVar7 = 0;
  puVar11 = puVar8;
  do {
    local_3c = *pfVar10;
    local_38 = pfVar10[1];
    local_34 = pfVar10[2];
    puVar11[0xc] = *(float *)(iVar9 + 0x18) * local_3c + *(float *)(iVar9 + 0xc);
    puVar11[0xd] = *(float *)(iVar9 + 0x1c) * local_38 + *(float *)(iVar9 + 0x10);
    puVar11[0xe] = *(float *)(iVar9 + 0x20) * local_34 + *(float *)(iVar9 + 0x14);
    gnt4_PSMTXMultVec_bl
              (*(float **)(param_1 + 0x60),(float *)(puVar11 + 0xc),(float *)(puVar11 + 0xc));
    iVar7 = iVar7 + 1;
    puVar11 = puVar11 + 3;
    pfVar10 = pfVar10 + 3;
  } while (iVar7 < 8);
  dVar14 = (double)FLOAT_80436f68;
  pcVar5 = &DAT_802cffc8;
  iVar7 = 0;
  puVar11 = puVar8;
  do {
    cVar3 = *pcVar5;
    pcVar1 = pcVar5 + 1;
    pcVar2 = pcVar5 + 2;
    pcVar5 = pcVar5 + 4;
    pfVar10 = (float *)(puVar8 + cVar3 * 3 + 0xc);
    local_48 = *pfVar10;
    local_44 = pfVar10[1];
    pfVar6 = (float *)(puVar8 + *pcVar1 * 3 + 0xc);
    local_40 = pfVar10[2];
    pfVar10 = (float *)(puVar8 + *pcVar2 * 3 + 0xc);
    local_54 = *pfVar6;
    local_50 = pfVar6[1];
    local_4c = pfVar6[2];
    local_60 = *pfVar10;
    local_5c = pfVar10[1];
    local_58 = pfVar10[2];
    gnt4_PSVECSubtract_bl(&local_54,&local_48,&local_54);
    gnt4_PSVECSubtract_bl(&local_60,&local_48,&local_60);
    gnt4_PSVECCrossProduct_bl(&local_54,&local_60,(float *)(puVar11 + 0x24));
    if ((double)((float)puVar11[0x26] * (float)puVar11[0x26] +
                (float)puVar11[0x24] * (float)puVar11[0x24] +
                (float)puVar11[0x25] * (float)puVar11[0x25]) <= dVar14) {
      return;
    }
    gnt4_PSVECNormalize_bl((float *)(puVar11 + 0x24),(float *)(puVar11 + 0x24));
    iVar7 = iVar7 + 1;
    puVar11 = puVar11 + 6;
  } while (iVar7 < 6);
  dVar14 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x88),(float *)(param_1 + 100));
  if ((double)FLOAT_80436f68 < dVar14) {
    dVar13 = 1.0 / SQRT(dVar14);
    dVar13 = DOUBLE_80436fd0 * dVar13 * -(dVar14 * dVar13 * dVar13 - DOUBLE_80436fd8);
    dVar13 = DOUBLE_80436fd0 * dVar13 * -(dVar14 * dVar13 * dVar13 - DOUBLE_80436fd8);
    dVar14 = (double)(float)(dVar14 * DOUBLE_80436fd0 * dVar13 *
                                      -(dVar14 * dVar13 * dVar13 - DOUBLE_80436fd8));
  }
  dVar13 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 100),(float *)(param_1 + 0x70));
  *(float *)(param_1 + 0x7c) = (float)dVar13;
  dVar13 = (double)*(float *)(param_1 + 0x7c);
  if ((double)FLOAT_80436f68 < dVar13) {
    dVar12 = 1.0 / SQRT(dVar13);
    dVar12 = DOUBLE_80436fd0 * dVar12 * -(dVar13 * dVar12 * dVar12 - DOUBLE_80436fd8);
    dVar12 = DOUBLE_80436fd0 * dVar12 * -(dVar13 * dVar12 * dVar12 - DOUBLE_80436fd8);
    dVar13 = (double)(float)(dVar13 * DOUBLE_80436fd0 * dVar12 *
                                      -(dVar13 * dVar12 * dVar12 - DOUBLE_80436fd8));
  }
  *(float *)(param_1 + 0x7c) = (float)dVar13;
  *(float *)(param_1 + 0x7c) = (float)((double)*(float *)(param_1 + 0x7c) + dVar14);
  return;
}



// ==== 8003b170  FUN_8003b170 ====

void FUN_8003b170(int param_1)

{
  int iVar1;
  double dVar2;
  float afStack_18 [4];
  
  iVar1 = *(int *)(param_1 + 0x28);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),(float *)(iVar1 + 0xc),(float *)(param_1 + 100));
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x6c);
  *(undefined4 *)(param_1 + 0x58) = 2;
  gnt4_PSVECSubtract_bl((float *)(iVar1 + 0xc),(float *)(iVar1 + 0x18),afStack_18);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),afStack_18,(float *)(param_1 + 0x8c));
  gnt4_PSVECAdd_bl((float *)(iVar1 + 0xc),(float *)(iVar1 + 0x18),afStack_18);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),afStack_18,(float *)(param_1 + 0x98));
  *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(param_1 + 0x8c);
  *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0x90);
  *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(param_1 + 0x94);
  *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_1 + 0x98);
  *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(param_1 + 0x9c);
  *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_1 + 0xa0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x98),(float *)(param_1 + 0x8c),(float *)(param_1 + 0xa4));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x8c),(float *)(param_1 + 0x98),(float *)(param_1 + 0xb0));
  if ((FLOAT_80436f68 <
       *(float *)(param_1 + 0xac) * *(float *)(param_1 + 0xac) +
       *(float *)(param_1 + 0xa4) * *(float *)(param_1 + 0xa4) +
       *(float *)(param_1 + 0xa8) * *(float *)(param_1 + 0xa8)) &&
     (FLOAT_80436f68 <
      *(float *)(param_1 + 0xb8) * *(float *)(param_1 + 0xb8) +
      *(float *)(param_1 + 0xb0) * *(float *)(param_1 + 0xb0) +
      *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0xb4))) {
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0xa4),(float *)(param_1 + 0xbc));
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0xb0),(float *)(param_1 + 200));
    *(float *)(param_1 + 0x88) =
         *(float *)(iVar1 + 0x24) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
    dVar2 = gnt4_PSVECMag_bl((float *)(iVar1 + 0x18));
    *(float *)(param_1 + 0x7c) =
         (float)(dVar2 * (double)*(float *)(*(int *)(param_1 + 0x20) + 0xc0)) +
         *(float *)(param_1 + 0x88);
  }
  return;
}



// ==== 8003b304  FUN_8003b304 ====

/* WARNING: Removing unreachable block (ram,0x8003bd6c) */
/* WARNING: Removing unreachable block (ram,0x8003b314) */

void FUN_8003b304(int param_1)

{
  float fVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float afStack_84 [3];
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  undefined4 local_5c;
  undefined4 local_58;
  float local_54;
  undefined4 local_50;
  undefined4 local_4c;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  
  iVar3 = *(int *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x6c);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),(float *)(iVar3 + 0xc),(float *)(param_1 + 100));
  *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(param_1 + 0x8c);
  *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0x90);
  *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(param_1 + 0x94);
  *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_1 + 0x98);
  *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(param_1 + 0x9c);
  *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_1 + 0xa0);
  if (((*(ushort *)(iVar3 + 2) & 1) != 0) || ((*(ushort *)(iVar3 + 2) & 0x80) != 0)) {
    dVar5 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 100),(float *)(param_1 + 0x70));
    if ((double)FLOAT_80436f68 < dVar5) {
      dVar6 = 1.0 / SQRT(dVar5);
      dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
      dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
      dVar5 = (double)(float)(dVar5 * DOUBLE_80436fd0 * dVar6 *
                                      -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8));
    }
    fVar1 = *(float *)(iVar3 + 0x24) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
    if ((double)fVar1 <= dVar5) {
      if (*(int *)(param_1 + 0x58) == 3) {
        *(float *)(param_1 + 0x88) = fVar1;
        *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_1 + 0xd4);
        *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(param_1 + 0xd8);
        *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_1 + 0xdc);
        *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(param_1 + 0xec);
        *(undefined4 *)(param_1 + 0xfc) = *(undefined4 *)(param_1 + 0xf0);
        *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(param_1 + 0xf4);
        *(undefined4 *)(param_1 + 0x104) = *(undefined4 *)(param_1 + 0xa4);
        *(undefined4 *)(param_1 + 0x108) = *(undefined4 *)(param_1 + 0xa8);
        *(undefined4 *)(param_1 + 0x10c) = *(undefined4 *)(param_1 + 0xac);
        local_54 = *(float *)(param_1 + 0xa4);
        local_50 = *(undefined4 *)(param_1 + 0xa8);
        local_4c = *(undefined4 *)(param_1 + 0xac);
        local_3c = *(undefined4 *)(param_1 + 0xb0);
        local_38 = *(undefined4 *)(param_1 + 0xb4);
        local_34 = *(undefined4 *)(param_1 + 0xb8);
        gnt4_PSVECSubtract_bl((float *)(iVar3 + 0xc),(float *)(iVar3 + 0x18),afStack_84);
        gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),afStack_84,&local_60);
        gnt4_PSVECAdd_bl((float *)(iVar3 + 0xc),(float *)(iVar3 + 0x18),afStack_84);
        gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),afStack_84,&local_48);
        dVar5 = (double)FLOAT_80436f68;
        pfVar4 = &local_60;
        iVar2 = 0;
        do {
          dVar6 = gnt4_PSVECSquareDistance_bl(pfVar4,(float *)(param_1 + 100));
          if (dVar5 <= dVar6) {
            dVar5 = dVar6;
          }
          iVar2 = iVar2 + 1;
          pfVar4 = pfVar4 + 3;
        } while (iVar2 < 4);
        if ((double)FLOAT_80436f68 < dVar5) {
          dVar6 = 1.0 / SQRT(dVar5);
          dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
          dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
          dVar5 = (double)(float)(dVar5 * DOUBLE_80436fd0 * dVar6 *
                                          -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8));
        }
        *(float *)(param_1 + 0x8c) = local_54;
        *(undefined4 *)(param_1 + 0x90) = local_50;
        *(undefined4 *)(param_1 + 0x94) = local_4c;
        *(undefined4 *)(param_1 + 0x98) = local_3c;
        *(undefined4 *)(param_1 + 0x9c) = local_38;
        *(undefined4 *)(param_1 + 0xa0) = local_34;
        *(float *)(param_1 + 0xa4) = local_60;
        *(undefined4 *)(param_1 + 0xa8) = local_5c;
        *(undefined4 *)(param_1 + 0xac) = local_58;
        *(float *)(param_1 + 0xb0) = local_48;
        *(undefined4 *)(param_1 + 0xb4) = local_44;
        *(undefined4 *)(param_1 + 0xb8) = local_40;
        *(float *)(param_1 + 0xbc) = local_60;
        *(undefined4 *)(param_1 + 0xc0) = local_5c;
        *(undefined4 *)(param_1 + 0xc4) = local_58;
        *(undefined4 *)(param_1 + 200) = local_3c;
        *(undefined4 *)(param_1 + 0xcc) = local_38;
        *(undefined4 *)(param_1 + 0xd0) = local_34;
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0x8c),(float *)(param_1 + 0x98),&local_78);
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0x8c),(float *)(param_1 + 0xa4),&local_6c);
        if (FLOAT_80436f68 < local_64 * local_64 + local_6c * local_6c + local_68 * local_68 &&
            FLOAT_80436f68 < local_70 * local_70 + local_78 * local_78 + local_74 * local_74) {
          gnt4_PSVECNormalize_bl(&local_78,&local_78);
          gnt4_PSVECNormalize_bl(&local_6c,&local_6c);
          dVar6 = gnt4_PSQUATDotProduct_bl(&local_78,&local_6c);
          if ((dVar6 < (double)FLOAT_8043700c) && ((double)FLOAT_80437010 < dVar6)) {
            gnt4_PSVECSubtract_bl((float *)(param_1 + 0x98),(float *)(param_1 + 0x8c),&local_60);
            gnt4_PSVECSubtract_bl((float *)(param_1 + 0xa4),(float *)(param_1 + 0x98),&local_54);
            gnt4_PSVECCrossProduct_bl(&local_60,&local_54,(float *)(param_1 + 0xd4));
            if (*(float *)(param_1 + 0xdc) * *(float *)(param_1 + 0xdc) +
                *(float *)(param_1 + 0xd4) * *(float *)(param_1 + 0xd4) +
                *(float *)(param_1 + 0xd8) * *(float *)(param_1 + 0xd8) <= FLOAT_80436f68) {
              return;
            }
            gnt4_PSVECNormalize_bl((float *)(param_1 + 0xd4),(float *)(param_1 + 0xd4));
            gnt4_PSVECSubtract_bl((float *)(param_1 + 0xbc),(float *)(param_1 + 0xb0),&local_60);
            gnt4_PSVECSubtract_bl((float *)(param_1 + 200),(float *)(param_1 + 0xbc),&local_54);
            gnt4_PSVECCrossProduct_bl(&local_60,&local_54,(float *)(param_1 + 0xec));
            if (*(float *)(param_1 + 0xf4) * *(float *)(param_1 + 0xf4) +
                *(float *)(param_1 + 0xec) * *(float *)(param_1 + 0xec) +
                *(float *)(param_1 + 0xf0) * *(float *)(param_1 + 0xf0) <= FLOAT_80436f68) {
              return;
            }
            gnt4_PSVECNormalize_bl((float *)(param_1 + 0xec),(float *)(param_1 + 0xec));
            dVar6 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 100),(float *)(param_1 + 0x70));
            if ((double)FLOAT_80436f68 < dVar6) {
              dVar7 = 1.0 / SQRT(dVar6);
              dVar7 = DOUBLE_80436fd0 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80436fd8);
              dVar7 = DOUBLE_80436fd0 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80436fd8);
              dVar6 = (double)(float)(dVar6 * DOUBLE_80436fd0 * dVar7 *
                                              -(dVar6 * dVar7 * dVar7 - DOUBLE_80436fd8));
            }
            *(float *)(param_1 + 0x7c) = (float)(dVar5 + dVar6);
            return;
          }
        }
      }
      else {
        *(undefined4 *)(param_1 + 0x58) = 3;
        *(float *)(param_1 + 0x88) =
             *(float *)(iVar3 + 0x24) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
        local_54 = *(float *)(param_1 + 0x8c);
        local_50 = *(undefined4 *)(param_1 + 0x90);
        local_4c = *(undefined4 *)(param_1 + 0x94);
        local_3c = *(undefined4 *)(param_1 + 0x98);
        local_38 = *(undefined4 *)(param_1 + 0x9c);
        local_34 = *(undefined4 *)(param_1 + 0xa0);
        gnt4_PSVECSubtract_bl((float *)(iVar3 + 0xc),(float *)(iVar3 + 0x18),afStack_84);
        gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),afStack_84,&local_60);
        gnt4_PSVECAdd_bl((float *)(iVar3 + 0xc),(float *)(iVar3 + 0x18),afStack_84);
        gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),afStack_84,&local_48);
        dVar5 = (double)FLOAT_80436f68;
        pfVar4 = &local_60;
        iVar2 = 0;
        do {
          dVar6 = gnt4_PSVECSquareDistance_bl(pfVar4,(float *)(param_1 + 100));
          if (dVar5 <= dVar6) {
            dVar5 = dVar6;
          }
          iVar2 = iVar2 + 1;
          pfVar4 = pfVar4 + 3;
        } while (iVar2 < 4);
        if ((double)FLOAT_80436f68 < dVar5) {
          dVar6 = 1.0 / SQRT(dVar5);
          dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
          dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
          dVar5 = (double)(float)(dVar5 * DOUBLE_80436fd0 * dVar6 *
                                          -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8));
        }
        *(float *)(param_1 + 0x8c) = local_54;
        *(undefined4 *)(param_1 + 0x90) = local_50;
        *(undefined4 *)(param_1 + 0x94) = local_4c;
        *(undefined4 *)(param_1 + 0x98) = local_3c;
        *(undefined4 *)(param_1 + 0x9c) = local_38;
        *(undefined4 *)(param_1 + 0xa0) = local_34;
        *(float *)(param_1 + 0xa4) = local_60;
        *(undefined4 *)(param_1 + 0xa8) = local_5c;
        *(undefined4 *)(param_1 + 0xac) = local_58;
        *(float *)(param_1 + 0xb0) = local_48;
        *(undefined4 *)(param_1 + 0xb4) = local_44;
        *(undefined4 *)(param_1 + 0xb8) = local_40;
        *(float *)(param_1 + 0xbc) = local_60;
        *(undefined4 *)(param_1 + 0xc0) = local_5c;
        *(undefined4 *)(param_1 + 0xc4) = local_58;
        *(undefined4 *)(param_1 + 200) = local_3c;
        *(undefined4 *)(param_1 + 0xcc) = local_38;
        *(undefined4 *)(param_1 + 0xd0) = local_34;
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0x8c),(float *)(param_1 + 0x98),&local_78);
        gnt4_PSVECSubtract_bl((float *)(param_1 + 0x8c),(float *)(param_1 + 0xa4),&local_6c);
        if (FLOAT_80436f68 < local_64 * local_64 + local_6c * local_6c + local_68 * local_68 &&
            FLOAT_80436f68 < local_70 * local_70 + local_78 * local_78 + local_74 * local_74) {
          gnt4_PSVECNormalize_bl(&local_78,&local_78);
          gnt4_PSVECNormalize_bl(&local_6c,&local_6c);
          dVar6 = gnt4_PSQUATDotProduct_bl(&local_78,&local_6c);
          if ((dVar6 < (double)FLOAT_8043700c) && ((double)FLOAT_80437010 < dVar6)) {
            gnt4_PSVECSubtract_bl((float *)(param_1 + 0x98),(float *)(param_1 + 0x8c),&local_60);
            gnt4_PSVECSubtract_bl((float *)(param_1 + 0xa4),(float *)(param_1 + 0x98),&local_54);
            gnt4_PSVECCrossProduct_bl(&local_60,&local_54,(float *)(param_1 + 0xd4));
            if (*(float *)(param_1 + 0xdc) * *(float *)(param_1 + 0xdc) +
                *(float *)(param_1 + 0xd4) * *(float *)(param_1 + 0xd4) +
                *(float *)(param_1 + 0xd8) * *(float *)(param_1 + 0xd8) <= FLOAT_80436f68) {
              return;
            }
            gnt4_PSVECNormalize_bl((float *)(param_1 + 0xd4),(float *)(param_1 + 0xd4));
            gnt4_PSVECSubtract_bl((float *)(param_1 + 0xbc),(float *)(param_1 + 0xb0),&local_60);
            gnt4_PSVECSubtract_bl((float *)(param_1 + 200),(float *)(param_1 + 0xbc),&local_54);
            gnt4_PSVECCrossProduct_bl(&local_60,&local_54,(float *)(param_1 + 0xec));
            if (*(float *)(param_1 + 0xf4) * *(float *)(param_1 + 0xf4) +
                *(float *)(param_1 + 0xec) * *(float *)(param_1 + 0xec) +
                *(float *)(param_1 + 0xf0) * *(float *)(param_1 + 0xf0) <= FLOAT_80436f68) {
              return;
            }
            gnt4_PSVECNormalize_bl((float *)(param_1 + 0xec),(float *)(param_1 + 0xec));
            dVar6 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 100),(float *)(param_1 + 0x70));
            if ((double)FLOAT_80436f68 < dVar6) {
              dVar7 = 1.0 / SQRT(dVar6);
              dVar7 = DOUBLE_80436fd0 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80436fd8);
              dVar7 = DOUBLE_80436fd0 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80436fd8);
              dVar6 = (double)(float)(dVar6 * DOUBLE_80436fd0 * dVar7 *
                                              -(dVar6 * dVar7 * dVar7 - DOUBLE_80436fd8));
            }
            *(float *)(param_1 + 0x7c) = (float)(dVar5 + dVar6);
            *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_1 + 0xd4);
            *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(param_1 + 0xd8);
            *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_1 + 0xdc);
            *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(param_1 + 0xec);
            *(undefined4 *)(param_1 + 0xfc) = *(undefined4 *)(param_1 + 0xf0);
            *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(param_1 + 0xf4);
            *(undefined4 *)(param_1 + 0x104) = *(undefined4 *)(param_1 + 0xa4);
            *(undefined4 *)(param_1 + 0x108) = *(undefined4 *)(param_1 + 0xa8);
            *(undefined4 *)(param_1 + 0x10c) = *(undefined4 *)(param_1 + 0xac);
            return;
          }
        }
      }
    }
  }
  *(undefined4 *)(param_1 + 0x58) = 2;
  gnt4_PSVECSubtract_bl((float *)(iVar3 + 0xc),(float *)(iVar3 + 0x18),afStack_84);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),afStack_84,(float *)(param_1 + 0x8c));
  gnt4_PSVECAdd_bl((float *)(iVar3 + 0xc),(float *)(iVar3 + 0x18),afStack_84);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),afStack_84,(float *)(param_1 + 0x98));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x98),(float *)(param_1 + 0x8c),(float *)(param_1 + 0xa4));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x8c),(float *)(param_1 + 0x98),(float *)(param_1 + 0xb0));
  if ((*(float *)(param_1 + 0xac) * *(float *)(param_1 + 0xac) +
       *(float *)(param_1 + 0xa4) * *(float *)(param_1 + 0xa4) +
       *(float *)(param_1 + 0xa8) * *(float *)(param_1 + 0xa8) <= FLOAT_80436f68) ||
     (*(float *)(param_1 + 0xb8) * *(float *)(param_1 + 0xb8) +
      *(float *)(param_1 + 0xb0) * *(float *)(param_1 + 0xb0) +
      *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0xb4) <= FLOAT_80436f68)) {
    *(float *)(param_1 + 0x7c) = FLOAT_80436f68;
  }
  else {
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0xa4),(float *)(param_1 + 0xbc));
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0xb0),(float *)(param_1 + 200));
    gnt4_PSVECSubtract_bl((float *)(param_1 + 100),(float *)(param_1 + 0x70),afStack_84);
    dVar5 = gnt4_PSVECMag_bl(afStack_84);
    *(float *)(param_1 + 0x88) =
         *(float *)(iVar3 + 0x24) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
    dVar6 = gnt4_PSVECMag_bl((float *)(iVar3 + 0x18));
    *(float *)(param_1 + 0x7c) =
         (float)(dVar5 + (double)((float)(dVar6 * (double)*(float *)(*(int *)(param_1 + 0x20) + 0xc0
                                                                    )) + *(float *)(param_1 + 0x88))
                );
    *(float *)(param_1 + 0x7c) = *(float *)(param_1 + 0x7c) * *(float *)(param_1 + 0x7c);
  }
  return;
}



// ==== 8003bd88  FUN_8003bd88 ====

/* WARNING: Removing unreachable block (ram,0x8003c064) */
/* WARNING: Removing unreachable block (ram,0x8003bd98) */

void FUN_8003bd88(int param_1)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  double dVar5;
  double dVar6;
  float local_64;
  undefined4 local_60;
  undefined4 local_5c;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  
  pfVar4 = (float *)&stack0xffffff90;
  iVar3 = *(int *)(param_1 + 0x28);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),(float *)(iVar3 + 0xc),(float *)(param_1 + 100));
  dVar6 = (double)FLOAT_80436f68;
  *(undefined4 *)(param_1 + 0x58) = 3;
  pfVar2 = (float *)(iVar3 + 0x1c);
  iVar1 = 0;
  *(float *)(param_1 + 0x88) =
       *(float *)(iVar3 + 0x18) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
  do {
    pfVar4 = pfVar4 + 3;
    gnt4_PSVECAdd_bl((float *)(iVar3 + 0xc),pfVar2,pfVar4);
    gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),pfVar4,pfVar4);
    dVar5 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 100),pfVar4);
    if (dVar6 <= dVar5) {
      dVar6 = dVar5;
    }
    iVar1 = iVar1 + 1;
    pfVar2 = pfVar2 + 3;
  } while (iVar1 < 4);
  if ((double)FLOAT_80436f68 < dVar6) {
    dVar5 = 1.0 / SQRT(dVar6);
    dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar6 * dVar5 * dVar5 - DOUBLE_80436fd8);
    dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar6 * dVar5 * dVar5 - DOUBLE_80436fd8);
    dVar6 = (double)(float)(dVar6 * DOUBLE_80436fd0 * dVar5 *
                                    -(dVar6 * dVar5 * dVar5 - DOUBLE_80436fd8));
  }
  *(float *)(param_1 + 0x7c) = (float)(dVar6 + (double)*(float *)(param_1 + 0x88));
  *(float *)(param_1 + 0x8c) = local_58;
  *(undefined4 *)(param_1 + 0x90) = local_54;
  *(undefined4 *)(param_1 + 0x94) = local_50;
  *(undefined4 *)(param_1 + 0x98) = local_40;
  *(undefined4 *)(param_1 + 0x9c) = local_3c;
  *(undefined4 *)(param_1 + 0xa0) = local_38;
  *(float *)(param_1 + 0xa4) = local_64;
  *(undefined4 *)(param_1 + 0xa8) = local_60;
  *(undefined4 *)(param_1 + 0xac) = local_5c;
  *(undefined4 *)(param_1 + 0xb0) = local_4c;
  *(undefined4 *)(param_1 + 0xb4) = local_48;
  *(undefined4 *)(param_1 + 0xb8) = local_44;
  *(float *)(param_1 + 0xbc) = local_64;
  *(undefined4 *)(param_1 + 0xc0) = local_60;
  *(undefined4 *)(param_1 + 0xc4) = local_5c;
  *(undefined4 *)(param_1 + 200) = local_40;
  *(undefined4 *)(param_1 + 0xcc) = local_3c;
  *(undefined4 *)(param_1 + 0xd0) = local_38;
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x98),(float *)(param_1 + 0x8c),&local_64);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xa4),(float *)(param_1 + 0x98),&local_58);
  gnt4_PSVECCrossProduct_bl(&local_64,&local_58,(float *)(param_1 + 0xd4));
  if (FLOAT_80436f68 <
      *(float *)(param_1 + 0xdc) * *(float *)(param_1 + 0xdc) +
      *(float *)(param_1 + 0xd4) * *(float *)(param_1 + 0xd4) +
      *(float *)(param_1 + 0xd8) * *(float *)(param_1 + 0xd8)) {
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0xd4),(float *)(param_1 + 0xd4));
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xbc),(float *)(param_1 + 0xb0),&local_64);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 200),(float *)(param_1 + 0xbc),&local_58);
    gnt4_PSVECCrossProduct_bl(&local_64,&local_58,(float *)(param_1 + 0xec));
    if (FLOAT_80436f68 <
        *(float *)(param_1 + 0xf4) * *(float *)(param_1 + 0xf4) +
        *(float *)(param_1 + 0xec) * *(float *)(param_1 + 0xec) +
        *(float *)(param_1 + 0xf0) * *(float *)(param_1 + 0xf0)) {
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0xec),(float *)(param_1 + 0xec));
      *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
      *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x68);
      *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x6c);
      *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_1 + 0xd4);
      *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(param_1 + 0xd8);
      *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_1 + 0xdc);
      *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(param_1 + 0xec);
      *(undefined4 *)(param_1 + 0xfc) = *(undefined4 *)(param_1 + 0xf0);
      *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(param_1 + 0xf4);
      *(undefined4 *)(param_1 + 0x104) = *(undefined4 *)(param_1 + 0xa4);
      *(undefined4 *)(param_1 + 0x108) = *(undefined4 *)(param_1 + 0xa8);
      *(undefined4 *)(param_1 + 0x10c) = *(undefined4 *)(param_1 + 0xac);
    }
  }
  return;
}



// ==== 8003c080  FUN_8003c080 ====

/* WARNING: Removing unreachable block (ram,0x8003c3bc) */
/* WARNING: Removing unreachable block (ram,0x8003c090) */

void FUN_8003c080(int param_1)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  float *pfVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  float local_60;
  undefined4 local_5c;
  undefined4 local_58;
  float local_54;
  undefined4 local_50;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  undefined4 local_38;
  undefined4 local_34;
  
  iVar3 = *(int *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x6c);
  *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_1 + 0xd4);
  *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(param_1 + 0xd8);
  *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_1 + 0xdc);
  *(undefined4 *)(param_1 + 0xf8) = *(undefined4 *)(param_1 + 0xec);
  *(undefined4 *)(param_1 + 0xfc) = *(undefined4 *)(param_1 + 0xf0);
  *(undefined4 *)(param_1 + 0x100) = *(undefined4 *)(param_1 + 0xf4);
  *(undefined4 *)(param_1 + 0x104) = *(undefined4 *)(param_1 + 0xa4);
  *(undefined4 *)(param_1 + 0x108) = *(undefined4 *)(param_1 + 0xa8);
  *(undefined4 *)(param_1 + 0x10c) = *(undefined4 *)(param_1 + 0xac);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),(float *)(iVar3 + 0xc),(float *)(param_1 + 100));
  dVar7 = (double)FLOAT_80436f68;
  *(undefined4 *)(param_1 + 0x58) = 3;
  pfVar2 = (float *)(iVar3 + 0x1c);
  pfVar4 = &local_60;
  iVar1 = 0;
  *(float *)(param_1 + 0x88) =
       *(float *)(iVar3 + 0x18) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
  do {
    gnt4_PSVECAdd_bl((float *)(iVar3 + 0xc),pfVar2,pfVar4);
    gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),pfVar4,pfVar4);
    dVar5 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 100),pfVar4);
    if (dVar7 <= dVar5) {
      dVar7 = dVar5;
    }
    iVar1 = iVar1 + 1;
    pfVar2 = pfVar2 + 3;
    pfVar4 = pfVar4 + 3;
  } while (iVar1 < 4);
  if ((double)FLOAT_80436f68 < dVar7) {
    dVar5 = 1.0 / SQRT(dVar7);
    dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar7 * dVar5 * dVar5 - DOUBLE_80436fd8);
    dVar5 = DOUBLE_80436fd0 * dVar5 * -(dVar7 * dVar5 * dVar5 - DOUBLE_80436fd8);
    dVar7 = (double)(float)(dVar7 * DOUBLE_80436fd0 * dVar5 *
                                    -(dVar7 * dVar5 * dVar5 - DOUBLE_80436fd8));
  }
  dVar5 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 100),(float *)(param_1 + 0x70));
  if ((double)FLOAT_80436f68 < dVar5) {
    dVar6 = 1.0 / SQRT(dVar5);
    dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
    dVar6 = DOUBLE_80436fd0 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8);
    dVar5 = (double)(float)(dVar5 * DOUBLE_80436fd0 * dVar6 *
                                    -(dVar5 * dVar6 * dVar6 - DOUBLE_80436fd8));
  }
  *(float *)(param_1 + 0x7c) = *(float *)(param_1 + 0x88) + (float)(dVar7 + dVar5);
  *(float *)(param_1 + 0x8c) = local_54;
  *(undefined4 *)(param_1 + 0x90) = local_50;
  *(undefined4 *)(param_1 + 0x94) = local_4c;
  *(undefined4 *)(param_1 + 0x98) = local_3c;
  *(undefined4 *)(param_1 + 0x9c) = local_38;
  *(undefined4 *)(param_1 + 0xa0) = local_34;
  *(float *)(param_1 + 0xa4) = local_60;
  *(undefined4 *)(param_1 + 0xa8) = local_5c;
  *(undefined4 *)(param_1 + 0xac) = local_58;
  *(undefined4 *)(param_1 + 0xb0) = local_48;
  *(undefined4 *)(param_1 + 0xb4) = local_44;
  *(undefined4 *)(param_1 + 0xb8) = local_40;
  *(float *)(param_1 + 0xbc) = local_60;
  *(undefined4 *)(param_1 + 0xc0) = local_5c;
  *(undefined4 *)(param_1 + 0xc4) = local_58;
  *(undefined4 *)(param_1 + 200) = local_3c;
  *(undefined4 *)(param_1 + 0xcc) = local_38;
  *(undefined4 *)(param_1 + 0xd0) = local_34;
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x98),(float *)(param_1 + 0x8c),&local_60);
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0xa4),(float *)(param_1 + 0x98),&local_54);
  gnt4_PSVECCrossProduct_bl(&local_60,&local_54,(float *)(param_1 + 0xd4));
  if (FLOAT_80436f68 <
      *(float *)(param_1 + 0xdc) * *(float *)(param_1 + 0xdc) +
      *(float *)(param_1 + 0xd4) * *(float *)(param_1 + 0xd4) +
      *(float *)(param_1 + 0xd8) * *(float *)(param_1 + 0xd8)) {
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0xd4),(float *)(param_1 + 0xd4));
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0xbc),(float *)(param_1 + 0xb0),&local_60);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 200),(float *)(param_1 + 0xbc),&local_54);
    gnt4_PSVECCrossProduct_bl(&local_60,&local_54,(float *)(param_1 + 0xec));
    if (FLOAT_80436f68 <
        *(float *)(param_1 + 0xf4) * *(float *)(param_1 + 0xf4) +
        *(float *)(param_1 + 0xec) * *(float *)(param_1 + 0xec) +
        *(float *)(param_1 + 0xf0) * *(float *)(param_1 + 0xf0)) {
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0xec),(float *)(param_1 + 0xec));
    }
  }
  return;
}



// ==== 8003c3d8  FUN_8003c3d8 ====

void FUN_8003c3d8(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  double dVar3;
  float local_88;
  undefined4 local_84;
  float local_80;
  float afStack_7c [3];
  float afStack_70 [12];
  float afStack_40 [13];
  
  puVar1 = (undefined4 *)(param_1 + 0x58);
  iVar2 = *(int *)(param_1 + 0x28);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),(float *)(iVar2 + 0xc),(float *)(param_1 + 100));
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x6c);
  *puVar1 = 4;
  *(float *)(param_1 + 0xa0) =
       *(float *)(iVar2 + 0x18) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
  *(float *)(param_1 + 0xa4) =
       *(float *)(iVar2 + 0x1c) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
  gnt4_PSMTXCopy_bl(*(float **)(param_1 + 0x60),afStack_40);
  gnt4_PSMTXTrans_bl((double)*(float *)(iVar2 + 0xc),(double)*(float *)(iVar2 + 0x10),
                     (double)*(float *)(iVar2 + 0x14),afStack_70);
  gnt4_PSMTXConcat_bl(afStack_40,afStack_70,afStack_40);
  dVar3 = (double)gnt4_atan2_bl((double)*(float *)(iVar2 + 0x28),(double)*(float *)(iVar2 + 0x24));
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80437014 * FLOAT_80437018 * (float)dVar3),afStack_70,0x78);
  gnt4_PSMTXConcat_bl(afStack_40,afStack_70,afStack_40);
  dVar3 = (double)gnt4_atan2_bl((double)*(float *)(iVar2 + 0x20),(double)*(float *)(iVar2 + 0x24));
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80437014 * FLOAT_80437018 * (float)dVar3),afStack_70,0x7a);
  gnt4_PSMTXConcat_bl(afStack_40,afStack_70,afStack_40);
  local_88 = FLOAT_80436f68;
  local_84 = *(undefined4 *)(param_1 + 0xa4);
  local_80 = FLOAT_80436f68;
  gnt4_PSMTXMultVec_bl(afStack_40,&local_88,afStack_7c);
  gnt4_PSVECSubtract_bl(afStack_7c,(float *)(param_1 + 100),(float *)(param_1 + 0x88));
  if (FLOAT_80436f68 <
      *(float *)(param_1 + 0x90) * *(float *)(param_1 + 0x90) +
      *(float *)(param_1 + 0x88) * *(float *)(param_1 + 0x88) +
      *(float *)(param_1 + 0x8c) * *(float *)(param_1 + 0x8c)) {
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0x88),(float *)(param_1 + 0x88));
    gnt4_PSMTXRotRad_bl((double)FLOAT_8043701c,afStack_70,0x78);
    gnt4_PSMTXConcat_bl(afStack_40,afStack_70,afStack_40);
    iVar2 = 0;
    do {
      gnt4_PSMTXMultVec_bl(afStack_40,&local_88,(float *)(puVar1 + 0x14));
      gnt4_PSMTXRotRad_bl((double)FLOAT_80437020,afStack_70,0x7a);
      gnt4_PSMTXConcat_bl(afStack_40,afStack_70,afStack_40);
      iVar2 = iVar2 + 1;
      puVar1 = puVar1 + 3;
    } while (iVar2 < 6);
    *(float *)(param_1 + 0x7c) = *(float *)(param_1 + 0xa4) + *(float *)(param_1 + 0xa0);
    *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(param_1 + 0x88);
    *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_1 + 0x8c);
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x90);
  }
  return;
}



// ==== 8003c614  FUN_8003c614 ====

void FUN_8003c614(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  double dVar3;
  double dVar4;
  float local_94;
  undefined4 local_90;
  float local_8c;
  float afStack_88 [3];
  float afStack_7c [12];
  float afStack_4c [16];
  
  puVar2 = (undefined4 *)(param_1 + 0x58);
  iVar1 = *(int *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x6c);
  *(undefined4 *)(param_1 + 0x94) = *(undefined4 *)(param_1 + 0x88);
  *(undefined4 *)(param_1 + 0x98) = *(undefined4 *)(param_1 + 0x8c);
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x90);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),(float *)(iVar1 + 0xc),(float *)(param_1 + 100));
  *puVar2 = 4;
  *(float *)(param_1 + 0xa0) =
       *(float *)(iVar1 + 0x18) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
  *(float *)(param_1 + 0xa4) =
       *(float *)(iVar1 + 0x1c) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
  dVar3 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 100),(float *)(param_1 + 0x70));
  if ((double)FLOAT_80436f68 < dVar3) {
    dVar4 = 1.0 / SQRT(dVar3);
    dVar4 = DOUBLE_80436fd0 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80436fd8);
    dVar4 = DOUBLE_80436fd0 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80436fd8);
    dVar3 = (double)(float)(dVar3 * DOUBLE_80436fd0 * dVar4 *
                                    -(dVar3 * dVar4 * dVar4 - DOUBLE_80436fd8));
  }
  *(float *)(param_1 + 0x7c) =
       (float)(dVar3 + (double)(*(float *)(param_1 + 0xa4) + *(float *)(param_1 + 0xa0)));
  gnt4_PSMTXCopy_bl(*(float **)(param_1 + 0x60),afStack_4c);
  gnt4_PSMTXTrans_bl((double)*(float *)(iVar1 + 0xc),(double)*(float *)(iVar1 + 0x10),
                     (double)*(float *)(iVar1 + 0x14),afStack_7c);
  gnt4_PSMTXConcat_bl(afStack_4c,afStack_7c,afStack_4c);
  dVar3 = (double)gnt4_atan2_bl((double)*(float *)(iVar1 + 0x28),(double)*(float *)(iVar1 + 0x24));
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80437014 * FLOAT_80437018 * (float)dVar3),afStack_7c,0x78);
  gnt4_PSMTXConcat_bl(afStack_4c,afStack_7c,afStack_4c);
  dVar3 = (double)gnt4_atan2_bl((double)*(float *)(iVar1 + 0x20),(double)*(float *)(iVar1 + 0x24));
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80437014 * FLOAT_80437018 * (float)dVar3),afStack_7c,0x7a);
  gnt4_PSMTXConcat_bl(afStack_4c,afStack_7c,afStack_4c);
  local_94 = FLOAT_80436f68;
  local_90 = *(undefined4 *)(param_1 + 0xa4);
  local_8c = FLOAT_80436f68;
  gnt4_PSMTXMultVec_bl(afStack_4c,&local_94,afStack_88);
  gnt4_PSVECSubtract_bl(afStack_88,(float *)(param_1 + 100),(float *)(param_1 + 0x88));
  if (FLOAT_80436f68 <
      *(float *)(param_1 + 0x90) * *(float *)(param_1 + 0x90) +
      *(float *)(param_1 + 0x88) * *(float *)(param_1 + 0x88) +
      *(float *)(param_1 + 0x8c) * *(float *)(param_1 + 0x8c)) {
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0x88),(float *)(param_1 + 0x88));
    gnt4_PSMTXRotRad_bl((double)FLOAT_8043701c,afStack_7c,0x78);
    gnt4_PSMTXConcat_bl(afStack_4c,afStack_7c,afStack_4c);
    iVar1 = 0;
    do {
      gnt4_PSMTXMultVec_bl(afStack_4c,&local_94,(float *)(puVar2 + 0x14));
      gnt4_PSMTXRotRad_bl((double)FLOAT_80437020,afStack_7c,0x7a);
      gnt4_PSMTXConcat_bl(afStack_4c,afStack_7c,afStack_4c);
      iVar1 = iVar1 + 1;
      puVar2 = puVar2 + 3;
    } while (iVar1 < 6);
  }
  return;
}



// ==== 8003c8b4  FUN_8003c8b4 ====

void FUN_8003c8b4(int param_1)

{
  int iVar1;
  double dVar2;
  float afStack_18 [4];
  
  iVar1 = *(int *)(param_1 + 0x28);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),(float *)(iVar1 + 0xc),(float *)(param_1 + 100));
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x6c);
  *(undefined4 *)(param_1 + 0x58) = 5;
  gnt4_PSVECSubtract_bl((float *)(iVar1 + 0xc),(float *)(iVar1 + 0x18),afStack_18);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),afStack_18,(float *)(param_1 + 0x8c));
  gnt4_PSVECAdd_bl((float *)(iVar1 + 0xc),(float *)(iVar1 + 0x18),afStack_18);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),afStack_18,(float *)(param_1 + 0x98));
  *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(param_1 + 0x8c);
  *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0x90);
  *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(param_1 + 0x94);
  *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_1 + 0x98);
  *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(param_1 + 0x9c);
  *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_1 + 0xa0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x98),(float *)(param_1 + 0x8c),(float *)(param_1 + 0xa4));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x8c),(float *)(param_1 + 0x98),(float *)(param_1 + 0xb0));
  if ((FLOAT_80436f68 <
       *(float *)(param_1 + 0xac) * *(float *)(param_1 + 0xac) +
       *(float *)(param_1 + 0xa4) * *(float *)(param_1 + 0xa4) +
       *(float *)(param_1 + 0xa8) * *(float *)(param_1 + 0xa8)) &&
     (FLOAT_80436f68 <
      *(float *)(param_1 + 0xb8) * *(float *)(param_1 + 0xb8) +
      *(float *)(param_1 + 0xb0) * *(float *)(param_1 + 0xb0) +
      *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0xb4))) {
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0xa4),(float *)(param_1 + 0xbc));
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0xb0),(float *)(param_1 + 200));
    *(float *)(param_1 + 0x88) =
         *(float *)(iVar1 + 0x24) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
    dVar2 = gnt4_PSVECMag_bl((float *)(iVar1 + 0x18));
    *(float *)(param_1 + 0x7c) =
         (float)(dVar2 * (double)*(float *)(*(int *)(param_1 + 0x20) + 0xc0)) +
         *(float *)(param_1 + 0x88);
  }
  return;
}



// ==== 8003ca48  FUN_8003ca48 ====

/* WARNING: Removing unreachable block (ram,0x8003cc04) */
/* WARNING: Removing unreachable block (ram,0x8003ca58) */

void FUN_8003ca48(int param_1)

{
  int iVar1;
  double dVar2;
  double dVar3;
  float afStack_28 [4];
  
  iVar1 = *(int *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x70) = *(undefined4 *)(param_1 + 100);
  *(undefined4 *)(param_1 + 0x74) = *(undefined4 *)(param_1 + 0x68);
  *(undefined4 *)(param_1 + 0x78) = *(undefined4 *)(param_1 + 0x6c);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),(float *)(iVar1 + 0xc),(float *)(param_1 + 100));
  *(undefined4 *)(param_1 + 0xd4) = *(undefined4 *)(param_1 + 0x8c);
  *(undefined4 *)(param_1 + 0xd8) = *(undefined4 *)(param_1 + 0x90);
  *(undefined4 *)(param_1 + 0xdc) = *(undefined4 *)(param_1 + 0x94);
  *(undefined4 *)(param_1 + 0xe0) = *(undefined4 *)(param_1 + 0x98);
  *(undefined4 *)(param_1 + 0xe4) = *(undefined4 *)(param_1 + 0x9c);
  *(undefined4 *)(param_1 + 0xe8) = *(undefined4 *)(param_1 + 0xa0);
  *(undefined4 *)(param_1 + 0x58) = 5;
  gnt4_PSVECSubtract_bl((float *)(iVar1 + 0xc),(float *)(iVar1 + 0x18),afStack_28);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),afStack_28,(float *)(param_1 + 0x8c));
  gnt4_PSVECAdd_bl((float *)(iVar1 + 0xc),(float *)(iVar1 + 0x18),afStack_28);
  gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x60),afStack_28,(float *)(param_1 + 0x98));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x98),(float *)(param_1 + 0x8c),(float *)(param_1 + 0xa4));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x8c),(float *)(param_1 + 0x98),(float *)(param_1 + 0xb0));
  if ((*(float *)(param_1 + 0xac) * *(float *)(param_1 + 0xac) +
       *(float *)(param_1 + 0xa4) * *(float *)(param_1 + 0xa4) +
       *(float *)(param_1 + 0xa8) * *(float *)(param_1 + 0xa8) <= FLOAT_80436f68) ||
     (*(float *)(param_1 + 0xb8) * *(float *)(param_1 + 0xb8) +
      *(float *)(param_1 + 0xb0) * *(float *)(param_1 + 0xb0) +
      *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0xb4) <= FLOAT_80436f68)) {
    *(float *)(param_1 + 0x7c) = FLOAT_80436f68;
  }
  else {
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0xa4),(float *)(param_1 + 0xbc));
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0xb0),(float *)(param_1 + 200));
    gnt4_PSVECSubtract_bl((float *)(param_1 + 100),(float *)(param_1 + 0x70),afStack_28);
    dVar2 = gnt4_PSVECMag_bl(afStack_28);
    *(float *)(param_1 + 0x88) =
         *(float *)(iVar1 + 0x24) * *(float *)(*(int *)(param_1 + 0x20) + 0xc0);
    dVar3 = gnt4_PSVECMag_bl((float *)(iVar1 + 0x18));
    *(float *)(param_1 + 0x7c) =
         (float)(dVar2 + (double)((float)(dVar3 * (double)*(float *)(*(int *)(param_1 + 0x20) + 0xc0
                                                                    )) + *(float *)(param_1 + 0x88))
                );
    *(float *)(param_1 + 0x7c) = *(float *)(param_1 + 0x7c) * *(float *)(param_1 + 0x7c);
  }
  return;
}



// ==== 8003cc24  zz_003cc24_ ====

void zz_003cc24_(int param_1)

{
  *(undefined4 *)(param_1 + 0x3fc) =
       *(undefined4 *)(PTR_DAT_80433934 + *(char *)(param_1 + 999) * 4 + 0x80);
  *(undefined4 *)(param_1 + 0x1e0) = 0;
  *(undefined4 *)(param_1 + 0x1e4) = 0;
  *(undefined1 *)(param_1 + 0x1d9) = 0;
  *(undefined1 *)(param_1 + 0x1da) = 0;
  *(undefined1 *)(param_1 + 0x1db) = 0;
  *(undefined1 *)(param_1 + 0x1de) = 0;
  *(undefined1 *)(param_1 + 0x1dc) = 0;
  *(undefined1 *)(param_1 + 0x1dd) = 0;
  *(undefined1 *)(param_1 + 0x280) = 0;
  *(undefined1 *)(param_1 + 0x703) = 0;
  *(undefined1 *)(param_1 + 0x704) = 0;
  *(undefined1 *)(param_1 + 0x26e) = 0;
  *(undefined2 *)(param_1 + 0x26c) = 0;
  *(undefined1 *)(param_1 + 0x274) = 0;
  *(undefined1 *)(param_1 + 0x1eb) = 0;
  *(undefined1 *)(param_1 + 0x276) = 0;
  *(undefined2 *)(param_1 + 0x20c) = 0;
  *(undefined2 *)(param_1 + 0x20e) = 0;
  *(undefined2 *)(param_1 + 0x210) = 0;
  *(undefined2 *)(param_1 + 0x212) = 0;
  *(undefined2 *)(param_1 + 0x214) = 0;
  *(undefined2 *)(param_1 + 0x216) = 0;
  *(undefined2 *)(param_1 + 0x218) = 0;
  *(undefined2 *)(param_1 + 0x21a) = 0;
  *(undefined2 *)(param_1 + 0x21c) = 0;
  *(undefined2 *)(param_1 + 0x21e) = 0;
  *(undefined2 *)(param_1 + 0x220) = 0;
  *(undefined2 *)(param_1 + 0x222) = 0;
  *(undefined2 *)(param_1 + 0x224) = 0;
  *(undefined2 *)(param_1 + 0x226) = 0;
  *(undefined2 *)(param_1 + 0x228) = 0;
  *(undefined2 *)(param_1 + 0x22a) = 0;
  *(undefined2 *)(param_1 + 0x22c) = 0;
  *(undefined2 *)(param_1 + 0x22e) = 0;
  *(undefined2 *)(param_1 + 0x230) = 0;
  *(undefined2 *)(param_1 + 0x232) = 0;
  *(undefined2 *)(param_1 + 0x234) = 0;
  *(undefined2 *)(param_1 + 0x236) = 0;
  *(undefined2 *)(param_1 + 0x238) = 0;
  *(undefined2 *)(param_1 + 0x23a) = 0;
  *(undefined2 *)(param_1 + 0x23c) = 0;
  *(undefined2 *)(param_1 + 0x23e) = 0;
  *(undefined2 *)(param_1 + 0x240) = 0;
  *(undefined2 *)(param_1 + 0x242) = 0;
  *(undefined2 *)(param_1 + 0x244) = 0;
  *(undefined2 *)(param_1 + 0x246) = 0;
  *(undefined2 *)(param_1 + 0x248) = 0;
  *(undefined2 *)(param_1 + 0x24a) = 0;
  *(undefined2 *)(param_1 + 0x24c) = 0;
  *(undefined2 *)(param_1 + 0x24e) = 0;
  *(undefined2 *)(param_1 + 0x250) = 0;
  *(undefined2 *)(param_1 + 0x252) = 0;
  *(undefined2 *)(param_1 + 0x254) = 0;
  *(undefined2 *)(param_1 + 0x256) = 0;
  *(undefined2 *)(param_1 + 600) = 0;
  *(undefined2 *)(param_1 + 0x25a) = 0;
  *(undefined2 *)(param_1 + 0x25c) = 0;
  *(undefined2 *)(param_1 + 0x25e) = 0;
  *(undefined2 *)(param_1 + 0x260) = 0;
  *(undefined2 *)(param_1 + 0x262) = 0;
  *(undefined2 *)(param_1 + 0x264) = 0;
  *(undefined2 *)(param_1 + 0x266) = 0;
  *(undefined2 *)(param_1 + 0x268) = 0;
  *(undefined2 *)(param_1 + 0x26a) = 0;
  *(undefined2 *)(param_1 + 0x272) = 0xef;
  return;
}



// ==== 8003cd5c  zz_003cd5c_ ====

/* WARNING: Removing unreachable block (ram,0x8003d31c) */
/* WARNING: Removing unreachable block (ram,0x8003cd6c) */

int zz_003cd5c_(ushort *param_1,int param_2,char *param_3)

{
  float fVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  char *pcVar7;
  char *pcVar8;
  uint uVar9;
  char *pcVar10;
  short sVar12;
  int iVar11;
  char *pcVar13;
  double dVar14;
  undefined2 local_38 [2];
  undefined2 local_34 [2];
  undefined8 local_30;
  
  local_30 = (double)CONCAT44(0x43300000,(uint)*param_1);
  fVar1 = (float)(local_30 - DOUBLE_80436fb0);
  if (FLOAT_80436f68 < fVar1) {
    if (((param_3[0x83] == '\0') && (*(uint *)(param_3 + 0x5a0) != 0)) &&
       ((*(uint *)(param_3 + 0x5a0) & 1 << (int)param_3[0x71a]) != 0)) {
      iVar4 = 0;
    }
    else {
      pcVar13 = *(char **)(param_2 + 0x90);
      dVar14 = (double)(fVar1 + fVar1 * FLOAT_80436f7c *
                                        (*(float *)(param_2 + 0xc4) - FLOAT_80436f78));
      if (((pcVar13[0x83] == '\0') && (*pcVar13 != '\0')) && (pcVar13[0x18] == '\x01')) {
        if (pcVar13[0x6fc] != '\0') {
          dVar14 = (double)(float)(dVar14 * (double)FLOAT_80436f9c);
        }
        cVar2 = pcVar13[0x3e6];
        iVar4 = (int)pcVar13[0x88];
        uVar3 = (uint)(-(int)cVar2 | (int)cVar2) >> 0x1d & 4;
        fVar1 = (float)(dVar14 * (double)*(float *)(*(int *)((int)&PTR_DAT_804335e0 + uVar3) +
                                                   (char)PTR_DAT_80433950[iVar4] * 4));
        if (((PTR_DAT_80433930[0x32] == '\0') || (PTR_DAT_80433930[0x32] == '\x01')) &&
           ((cVar2 != '\0' && (pcVar13[0x88] == '\0')))) {
          fVar1 = FLOAT_80436f7c * fVar1;
        }
        uVar9 = (uint)(short)(&DAT_803b069c)[pcVar13[0x3e4]];
        if ((int)uVar9 < 0xc9) {
          if (*(short *)(pcVar13 + 0x1c4) < 200) {
            iVar5 = (int)(uVar9 << 5) / (int)*(short *)(pcVar13 + 0x1c4);
          }
          else {
            iVar5 = (int)(uVar9 << 5) / 200 + ((int)(uVar9 << 5 | uVar9 >> 0x1b) >> 0x1f);
            iVar5 = iVar5 - (iVar5 >> 0x1f);
          }
          iVar5 = 0x20 - iVar5;
          if (0x1f < iVar5) {
            iVar5 = 0x1f;
          }
          fVar1 = fVar1 * *(float *)(*(int *)(*(int *)((int)&PTR_PTR_804335e8 + uVar3) +
                                             (uint)*(byte *)(param_1 + 3) * 4) + iVar5 * 4);
        }
        iVar4 = 0x20 - (int)((&DAT_803b068c)[iVar4] << 5) /
                       *(int *)(PTR_DAT_80433934 + iVar4 * 0x3c + 0x114);
        if (0x1f < iVar4) {
          iVar4 = 0x1f;
        }
        dVar14 = (double)(fVar1 * *(float *)(*(int *)(*(int *)((int)&PTR_PTR_804335f0 + uVar3) +
                                                     (uint)*(byte *)((int)param_1 + 7) * 4) +
                                            iVar4 * 4) *
                         *(float *)(*(int *)((int)&PTR_DAT_804335f8 + uVar3) + pcVar13[0x43a] * 4));
        if (((param_3[0x83] == '\0') && (*param_3 != '\0')) && (param_3[0x18] == '\x01')) {
          local_34[0] = *(undefined2 *)(pcVar13 + 1000);
          iVar4 = zz_0066298_((char *)local_34);
          local_38[0] = *(undefined2 *)(param_3 + 1000);
          iVar5 = zz_0066298_((char *)local_38);
          dVar14 = (double)(float)(dVar14 * (double)*(float *)(iVar5 * 0x50 + -0x7fd3a2a0 +
                                                              iVar4 * 4));
        }
      }
      pcVar7 = *(char **)(param_3 + 0x90);
      pcVar8 = param_3;
      pcVar10 = param_3;
      if (((pcVar7 != (char *)0x0) && (pcVar8 = pcVar7, param_3[0x83] != '\0')) &&
         (pcVar7[0x83] == '\0')) {
        pcVar10 = pcVar7;
      }
      if (((pcVar10[0x83] == '\0') && (*pcVar10 != '\0')) && (pcVar10[0x18] == '\x01')) {
        cVar2 = pcVar10[0x3e6];
        iVar4 = (-(int)cVar2 | (int)cVar2) >> 0x1f;
        if (pcVar10[0x6fc] != '\0') {
          dVar14 = (double)(float)(dVar14 * (double)FLOAT_80436f7c);
        }
        iVar5 = *(int *)(pcVar10 + 0x4ac);
        iVar6 = (int)pcVar10[0x88];
        fVar1 = (float)(dVar14 * (double)*(float *)(*(int *)((&PTR_PTR_80433600)[-iVar4] +
                                                            (uint)*(byte *)(iVar5 + 0x9c) * 4) +
                                                   (char)PTR_DAT_80433950[iVar6] * 4));
        if ((((PTR_DAT_80433930[0x32] == '\0') || (PTR_DAT_80433930[0x32] == '\x01')) &&
            (cVar2 != '\0')) && (pcVar10[0x88] == '\0')) {
          fVar1 = FLOAT_80436f7c * fVar1;
        }
        sVar12 = (&DAT_803b069c)[pcVar10[0x3e4]] - *param_1;
        fVar1 = fVar1 * (FLOAT_80436f78 /
                        (FLOAT_80436f78 +
                        FLOAT_80436f7c * (*(float *)(pcVar10 + 0xb4) - FLOAT_80436f78)));
        if (sVar12 < 1) {
          sVar12 = 0;
        }
        uVar3 = (uint)sVar12;
        if ((int)uVar3 < 0xc9) {
          if (*(short *)(pcVar10 + 0x1c4) < 200) {
            iVar11 = (int)(uVar3 << 5) / (int)*(short *)(pcVar10 + 0x1c4);
          }
          else {
            iVar11 = (int)(uVar3 << 5) / 200 + ((int)(uVar3 << 5 | uVar3 >> 0x1b) >> 0x1f);
            iVar11 = iVar11 - (iVar11 >> 0x1f);
          }
          iVar11 = 0x20 - iVar11;
          if (0x1f < iVar11) {
            iVar11 = 0x1f;
          }
          fVar1 = fVar1 * *(float *)(*(int *)((&PTR_PTR_80433608)[-iVar4] +
                                             (uint)*(byte *)(iVar5 + 0x9d) * 4) + iVar11 * 4);
        }
        iVar6 = 0x20 - (int)((&DAT_803b068c)[iVar6] << 5) /
                       *(int *)(PTR_DAT_80433934 + iVar6 * 0x3c + 0x114);
        if (0x1f < iVar6) {
          iVar6 = 0x1f;
        }
        dVar14 = (double)(fVar1 * *(float *)(*(int *)((&PTR_PTR_80433610)[-iVar4] +
                                                     (uint)*(byte *)(iVar5 + 0x9e) * 4) + iVar6 * 4)
                         * *(float *)((&PTR_DAT_80433618)[-iVar4] + pcVar10[0x43a] * 4));
        if ((param_1[9] & 0x4000) == 0) {
          dVar14 = (double)(float)(dVar14 * (double)*(float *)(&DAT_802c7ca0 + pcVar10[0x6ca] * 4));
        }
        if ((*(uint *)(pcVar10 + 0x5e0) & 0x4000000) != 0) {
          dVar14 = (double)(float)(dVar14 * (double)FLOAT_80436f7c);
        }
      }
      if ((pcVar13[0x88] == pcVar8[0x88]) && ((param_1[8] & 0x1000) == 0)) {
        dVar14 = (double)(float)(dVar14 * (double)FLOAT_80437024);
      }
      if (((param_3[0x83] == '\0') && ((param_1[8] & 0x1000) != 0)) &&
         ((*(ushort *)(param_3 + 0x59c) & 0x1000) != 0)) {
        dVar14 = (double)(float)(dVar14 / (double)FLOAT_80437028);
      }
      if (dVar14 < (double)FLOAT_80436f78) {
        dVar14 = (double)FLOAT_80436f78;
      }
      iVar4 = (int)dVar14;
    }
  }
  else {
    iVar4 = 0;
  }
  return iVar4;
}



// ==== 8003d344  zz_003d344_ ====

uint zz_003d344_(int param_1,short param_2)

{
  uint uVar1;
  
  if (*(short *)(param_1 + 0x1c6) == 0) {
    return 0;
  }
  if (PTR_DAT_80433934[0x1f] != '\0') {
    if (*(char *)(param_1 + 0x83) == '\0') {
      return 0;
    }
  }
  *(short *)(param_1 + 0x1c8) = *(short *)(param_1 + 0x1c6);
  *(short *)(param_1 + 0x1c6) = *(short *)(param_1 + 0x1c6) - param_2;
  if (*(short *)(param_1 + 0x1c6) < 0) {
    *(undefined2 *)(param_1 + 0x1c6) = 0;
  }
  else if (*(short *)(param_1 + 0x1c4) < *(short *)(param_1 + 0x1c6)) {
    *(short *)(param_1 + 0x1c6) = *(short *)(param_1 + 0x1c4);
  }
  if ((*(char *)(param_1 + 0x83) == '\0') && (*(char *)(param_1 + 0x4a0) == '\x01')) {
    *(undefined2 *)(*(int *)(param_1 + 0x4a4) + 0x1c6) = *(undefined2 *)(param_1 + 0x1c6);
  }
  uVar1 = countLeadingZeros((int)*(short *)(param_1 + 0x1c6));
  return uVar1 >> 5;
}



// ==== 8003d3e8  zz_003d3e8_ ====

void zz_003d3e8_(int param_1)

{
  *(short *)(param_1 + 0x6c6) =
       *(short *)(param_1 + 0x6c4) +
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x6c4) ^ 0x80000000) -
                           DOUBLE_80436f88) *
                   FLOAT_80436f7c * (*(float *)(param_1 + 0xb4) - FLOAT_80436f78));
  return;
}



// ==== 8003d444  zz_003d444_ ====

void zz_003d444_(int param_1)

{
  *(short *)(param_1 + 0x7dc) =
       *(short *)(param_1 + 0x7d6) +
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x7d6) ^ 0x80000000) -
                           DOUBLE_80436f88) *
                   FLOAT_80436f7c * (*(float *)(param_1 + 0xb4) - FLOAT_80436f78));
  return;
}



// ==== 8003d4a0  zz_003d4a0_ ====

void zz_003d4a0_(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar6 = *(int *)PTR_DAT_80433954;
  *(undefined4 *)(DAT_8043625c + 0x28) = *(undefined4 *)(iVar6 + 4);
  *(int *)(DAT_8043625c + 0x1c) = iVar6 + 8;
  *(int *)(iVar6 + 0x20) = iVar6 + *(int *)(iVar6 + 0x20) + 8;
  *(int *)(iVar6 + 0x24) = iVar6 + *(int *)(iVar6 + 0x24) + 8;
  for (iVar2 = 0; iVar2 < *(int *)(iVar6 + 0x10); iVar2 = iVar2 + 1) {
    for (iVar7 = 0; iVar7 < *(int *)(iVar6 + 0x14); iVar7 = iVar7 + 1) {
      iVar4 = *(int *)(iVar6 + 0x20);
      iVar1 = (iVar7 + iVar2 * *(int *)(iVar6 + 0x14)) * 4;
      *(int *)(iVar4 + iVar1) = iVar6 + *(int *)(iVar4 + iVar1) + 8;
      for (iVar5 = 0; iVar3 = *(int *)(iVar4 + iVar1), *(int *)(iVar3 + iVar5) != -1;
          iVar5 = iVar5 + 4) {
        *(int *)(iVar3 + iVar5) = *(int *)(iVar3 + iVar5) + *(int *)(iVar6 + 0x24);
      }
    }
  }
  iVar6 = *(int *)(PTR_DAT_80433954 + 4);
  *(undefined4 *)(DAT_8043625c + 0x2c) = *(undefined4 *)(iVar6 + 4);
  *(int *)(DAT_8043625c + 0x20) = iVar6 + 8;
  *(int *)(iVar6 + 0x20) = iVar6 + *(int *)(iVar6 + 0x20) + 8;
  *(int *)(iVar6 + 0x24) = iVar6 + *(int *)(iVar6 + 0x24) + 8;
  for (iVar2 = 0; iVar2 < *(int *)(iVar6 + 0x10); iVar2 = iVar2 + 1) {
    for (iVar7 = 0; iVar7 < *(int *)(iVar6 + 0x14); iVar7 = iVar7 + 1) {
      iVar4 = *(int *)(iVar6 + 0x20);
      iVar1 = (iVar7 + iVar2 * *(int *)(iVar6 + 0x14)) * 4;
      *(int *)(iVar4 + iVar1) = iVar6 + *(int *)(iVar4 + iVar1) + 8;
      for (iVar5 = 0; iVar3 = *(int *)(iVar4 + iVar1), *(int *)(iVar3 + iVar5) != -1;
          iVar5 = iVar5 + 4) {
        *(int *)(iVar3 + iVar5) = *(int *)(iVar3 + iVar5) + *(int *)(iVar6 + 0x24);
      }
    }
  }
  iVar6 = *(int *)(PTR_DAT_80433954 + 8);
  *(undefined4 *)(DAT_8043625c + 0x30) = *(undefined4 *)(iVar6 + 4);
  *(int *)(DAT_8043625c + 0x24) = iVar6 + 8;
  *(int *)(iVar6 + 0x20) = iVar6 + *(int *)(iVar6 + 0x20) + 8;
  *(int *)(iVar6 + 0x24) = iVar6 + *(int *)(iVar6 + 0x24) + 8;
  for (iVar2 = 0; iVar2 < *(int *)(iVar6 + 0x10); iVar2 = iVar2 + 1) {
    for (iVar7 = 0; iVar7 < *(int *)(iVar6 + 0x14); iVar7 = iVar7 + 1) {
      iVar4 = *(int *)(iVar6 + 0x20);
      iVar1 = (iVar7 + iVar2 * *(int *)(iVar6 + 0x14)) * 4;
      *(int *)(iVar4 + iVar1) = iVar6 + *(int *)(iVar4 + iVar1) + 8;
      for (iVar5 = 0; iVar3 = *(int *)(iVar4 + iVar1), *(int *)(iVar3 + iVar5) != -1;
          iVar5 = iVar5 + 4) {
        *(int *)(iVar3 + iVar5) = *(int *)(iVar3 + iVar5) + *(int *)(iVar6 + 0x24);
      }
    }
  }
  return;
}



// ==== 8003d6e4  FUN_8003d6e4 ====

/* WARNING: Removing unreachable block (ram,0x8003d940) */
/* WARNING: Removing unreachable block (ram,0x8003d938) */
/* WARNING: Removing unreachable block (ram,0x8003d6fc) */
/* WARNING: Removing unreachable block (ram,0x8003d6f4) */

double FUN_8003d6e4(double param_1,int param_2,float *param_3)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  int *piVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  float local_4c;
  float local_48;
  float local_44;
  float local_40;
  float local_3c;
  
  if (*(char *)(param_2 + 0x1db) == '\0') {
    iVar8 = zz_003fb00_(param_3);
    if (iVar8 == 0) {
      dVar12 = (double)param_3[1];
    }
    else {
      bVar1 = param_1 < (double)*(float *)(DAT_8043625c + 0x34);
      local_4c = *param_3;
      local_48 = param_3[1] + *(float *)(param_2 + 0x6d0);
      local_44 = param_3[2];
      dVar11 = zz_003f320_((double)(*(float *)(param_2 + 0x30) + *(float *)(param_2 + 0x6d4)),
                           &local_4c);
      dVar10 = (double)((*(float *)(param_2 + 0x30) + *(float *)(param_2 + 0x6d4)) -
                       (*(float *)(param_2 + 0x24) + *(float *)(param_2 + 0x6d0)));
      if ((double)FLOAT_80436f68 < dVar10) {
        param_1 = (double)(float)(param_1 + dVar10);
      }
      dVar15 = (double)(float)(param_1 + (double)param_3[1]);
      piVar9 = (int *)FUN_8003fa68(param_3);
      dVar10 = (double)*(float *)(DAT_8043625c + 0x68);
      dVar13 = (double)*(float *)(DAT_8043625c + 0x34);
      dVar12 = dVar10;
      for (; iVar8 = *piVar9, iVar8 != -1; piVar9 = piVar9 + 1) {
        fVar2 = *(float *)(iVar8 + 4) - local_4c;
        fVar5 = *(float *)(iVar8 + 0xc) - local_44;
        fVar3 = *(float *)(iVar8 + 0x10) - local_4c;
        fVar6 = *(float *)(iVar8 + 0x18) - local_44;
        fVar4 = *(float *)(iVar8 + 0x1c) - local_4c;
        fVar7 = *(float *)(iVar8 + 0x24) - local_44;
        if (((fVar2 * fVar6 <= fVar5 * fVar3) && (fVar3 * fVar7 <= fVar6 * fVar4)) &&
           (fVar4 * fVar5 <= fVar7 * fVar2)) {
          dVar14 = (double)((*(float *)(iVar8 + 0x28) * fVar2 + *(float *)(iVar8 + 0x30) * fVar5 +
                            *(float *)(iVar8 + 0x2c) * *(float *)(iVar8 + 8)) /
                           *(float *)(iVar8 + 0x2c));
          if (((dVar14 < dVar15) && (dVar14 < dVar11)) && (dVar10 <= dVar14)) {
            dVar10 = dVar14;
          }
          if (dVar14 <= dVar13) {
            dVar13 = dVar14;
          }
          if (dVar12 <= dVar14) {
            dVar12 = dVar14;
          }
        }
      }
      if (((bVar1) && (dVar12 = dVar10, dVar10 == (double)*(float *)(DAT_8043625c + 0x68))) &&
         (dVar12 = dVar13, dVar13 == (double)*(float *)(DAT_8043625c + 0x34))) {
        dVar12 = (double)*(float *)(DAT_8043625c + 0x68);
      }
    }
  }
  else {
    gnt4_PSMTXMultVec_bl
              (*(float **)(*(int *)(param_2 + 0x1e0) + 0x60),(float *)(param_2 + 0x1f8),&local_40);
    dVar12 = (double)local_3c;
  }
  return dVar12;
}



// ==== 8003d964  FUN_8003d964 ====

/* WARNING: Removing unreachable block (ram,0x8003db78) */
/* WARNING: Removing unreachable block (ram,0x8003db70) */
/* WARNING: Removing unreachable block (ram,0x8003db68) */
/* WARNING: Removing unreachable block (ram,0x8003db60) */
/* WARNING: Removing unreachable block (ram,0x8003d98c) */
/* WARNING: Removing unreachable block (ram,0x8003d984) */
/* WARNING: Removing unreachable block (ram,0x8003d97c) */
/* WARNING: Removing unreachable block (ram,0x8003d974) */

double FUN_8003d964(double param_1,int param_2,float *param_3)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  int iVar8;
  int *piVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  
  iVar8 = zz_003fb00_(param_3);
  if (iVar8 == 0) {
    dVar12 = (double)param_3[1];
  }
  else {
    bVar1 = param_1 < (double)*(float *)(DAT_8043625c + 0x34);
    dVar11 = zz_003f320_((double)*(float *)(param_2 + 0x30),param_3);
    if ((*(float *)(param_2 + 0x24) != *(float *)(param_2 + 0x30)) &&
       (dVar10 = (double)(*(float *)(param_2 + 0x30) - *(float *)(param_2 + 0x24)), param_1 < dVar10
       )) {
      param_1 = (double)(float)(param_1 + dVar10);
    }
    dVar17 = (double)*param_3;
    dVar15 = (double)(float)(param_1 + (double)param_3[1]);
    dVar16 = (double)param_3[2];
    piVar9 = (int *)FUN_8003fa68(param_3);
    dVar10 = (double)*(float *)(DAT_8043625c + 0x68);
    dVar13 = (double)*(float *)(DAT_8043625c + 0x34);
    dVar12 = dVar10;
    for (; iVar8 = *piVar9, iVar8 != -1; piVar9 = piVar9 + 1) {
      fVar2 = (float)((double)*(float *)(iVar8 + 4) - dVar17);
      fVar3 = (float)((double)*(float *)(iVar8 + 0xc) - dVar16);
      fVar4 = (float)((double)*(float *)(iVar8 + 0x10) - dVar17);
      fVar5 = (float)((double)*(float *)(iVar8 + 0x18) - dVar16);
      fVar6 = (float)((double)*(float *)(iVar8 + 0x1c) - dVar17);
      fVar7 = (float)((double)*(float *)(iVar8 + 0x24) - dVar16);
      if (((fVar2 * fVar5 <= fVar3 * fVar4) && (fVar4 * fVar7 <= fVar5 * fVar6)) &&
         (fVar6 * fVar3 <= fVar7 * fVar2)) {
        dVar14 = (double)((*(float *)(iVar8 + 0x28) * fVar2 + *(float *)(iVar8 + 0x30) * fVar3 +
                          *(float *)(iVar8 + 0x2c) * *(float *)(iVar8 + 8)) /
                         *(float *)(iVar8 + 0x2c));
        if (((dVar14 < dVar15) && (dVar14 < dVar11)) && (dVar10 <= dVar14)) {
          dVar10 = dVar14;
        }
        if (dVar14 <= dVar13) {
          dVar13 = dVar14;
        }
        if (dVar12 <= dVar14) {
          dVar12 = dVar14;
        }
      }
    }
    if (((bVar1) && (dVar12 = dVar10, dVar10 == (double)*(float *)(DAT_8043625c + 0x68))) &&
       (dVar12 = dVar13, dVar13 == (double)*(float *)(DAT_8043625c + 0x34))) {
      dVar12 = (double)*(float *)(DAT_8043625c + 0x68);
    }
  }
  return dVar12;
}



// ==== 8003db9c  FUN_8003db9c ====

/* WARNING: Removing unreachable block (ram,0x8003dd18) */
/* WARNING: Removing unreachable block (ram,0x8003dd10) */
/* WARNING: Removing unreachable block (ram,0x8003dd08) */
/* WARNING: Removing unreachable block (ram,0x8003dbbc) */
/* WARNING: Removing unreachable block (ram,0x8003dbb4) */
/* WARNING: Removing unreachable block (ram,0x8003dbac) */

double FUN_8003db9c(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int *piVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  
  iVar7 = zz_003fb00_(param_1);
  if (iVar7 == 0) {
    dVar10 = (double)param_1[1];
  }
  else {
    dVar14 = (double)*param_1;
    dVar13 = (double)param_1[1];
    dVar12 = (double)param_1[2];
    piVar8 = (int *)FUN_8003fa68(param_1);
    dVar10 = (double)*(float *)(DAT_8043625c + 0x68);
    dVar9 = (double)*(float *)(DAT_8043625c + 0x34);
    for (; iVar7 = *piVar8, iVar7 != -1; piVar8 = piVar8 + 1) {
      fVar1 = (float)((double)*(float *)(iVar7 + 4) - dVar14);
      fVar2 = (float)((double)*(float *)(iVar7 + 0xc) - dVar12);
      fVar3 = (float)((double)*(float *)(iVar7 + 0x10) - dVar14);
      fVar4 = (float)((double)*(float *)(iVar7 + 0x18) - dVar12);
      fVar5 = (float)((double)*(float *)(iVar7 + 0x1c) - dVar14);
      fVar6 = (float)((double)*(float *)(iVar7 + 0x24) - dVar12);
      if (((fVar1 * fVar4 <= fVar2 * fVar3) && (fVar3 * fVar6 <= fVar4 * fVar5)) &&
         (fVar5 * fVar2 <= fVar6 * fVar1)) {
        dVar11 = (double)((*(float *)(iVar7 + 0x28) * fVar1 + *(float *)(iVar7 + 0x30) * fVar2 +
                          *(float *)(iVar7 + 0x2c) * *(float *)(iVar7 + 8)) /
                         *(float *)(iVar7 + 0x2c));
        if ((dVar11 <= dVar13) && (dVar10 <= dVar11)) {
          dVar10 = dVar11;
        }
        if (dVar11 <= dVar9) {
          dVar9 = dVar11;
        }
      }
    }
    if ((dVar10 == (double)*(float *)(DAT_8043625c + 0x68)) &&
       (dVar10 = dVar9, dVar9 == (double)*(float *)(DAT_8043625c + 0x34))) {
      dVar10 = (double)*(float *)(DAT_8043625c + 0x68);
    }
  }
  return dVar10;
}



// ==== 8003dd34  FUN_8003dd34 ====

/* WARNING: Removing unreachable block (ram,0x8003de64) */
/* WARNING: Removing unreachable block (ram,0x8003de5c) */
/* WARNING: Removing unreachable block (ram,0x8003dd4c) */
/* WARNING: Removing unreachable block (ram,0x8003dd44) */

double FUN_8003dd34(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  float fVar6;
  int iVar7;
  int *piVar8;
  double dVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  
  iVar7 = zz_003fb00_(param_1);
  if (iVar7 == 0) {
    dVar9 = (double)param_1[1];
  }
  else {
    dVar12 = (double)*param_1;
    dVar11 = (double)param_1[2];
    piVar8 = (int *)FUN_8003fa68(param_1);
    dVar9 = (double)*(float *)(DAT_8043625c + 0x34);
    for (; iVar7 = *piVar8, iVar7 != -1; piVar8 = piVar8 + 1) {
      fVar1 = (float)((double)*(float *)(iVar7 + 4) - dVar12);
      fVar2 = (float)((double)*(float *)(iVar7 + 0xc) - dVar11);
      fVar3 = (float)((double)*(float *)(iVar7 + 0x10) - dVar12);
      fVar4 = (float)((double)*(float *)(iVar7 + 0x18) - dVar11);
      fVar5 = (float)((double)*(float *)(iVar7 + 0x1c) - dVar12);
      fVar6 = (float)((double)*(float *)(iVar7 + 0x24) - dVar11);
      if ((((fVar1 * fVar4 <= fVar2 * fVar3) && (fVar3 * fVar6 <= fVar4 * fVar5)) &&
          (fVar5 * fVar2 <= fVar6 * fVar1)) &&
         (dVar10 = (double)((*(float *)(iVar7 + 0x28) * fVar1 + *(float *)(iVar7 + 0x30) * fVar2 +
                            *(float *)(iVar7 + 0x2c) * *(float *)(iVar7 + 8)) /
                           *(float *)(iVar7 + 0x2c)), dVar10 <= dVar9)) {
        dVar9 = dVar10;
      }
    }
    if (dVar9 == (double)*(float *)(DAT_8043625c + 0x34)) {
      dVar9 = (double)*(float *)(DAT_8043625c + 0x68);
    }
  }
  return dVar9;
}



// ==== 8003de80  zz_003de80_ ====

/* WARNING: Removing unreachable block (ram,0x8003e084) */
/* WARNING: Removing unreachable block (ram,0x8003e07c) */
/* WARNING: Removing unreachable block (ram,0x8003de98) */
/* WARNING: Removing unreachable block (ram,0x8003de90) */

undefined4 zz_003de80_(double param_1,int param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  undefined4 uVar6;
  int iVar7;
  int *piVar8;
  float fVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  float local_3c;
  float local_38;
  float local_34;
  
  fVar5 = FLOAT_80436f78;
  fVar4 = FLOAT_80436f68;
  if (*(char *)(param_2 + 0x1db) == '\0') {
    *param_4 = FLOAT_80436f68;
    param_4[1] = fVar5;
    param_4[2] = fVar4;
    iVar7 = zz_003fb00_(param_3);
    if (iVar7 == 0) {
      uVar6 = 0;
    }
    else {
      local_3c = *param_3;
      local_38 = param_3[1] + *(float *)(param_2 + 0x6d0);
      local_34 = param_3[2];
      dVar11 = zz_003f320_((double)(*(float *)(param_2 + 0x30) + *(float *)(param_2 + 0x6d4)),
                           &local_3c);
      dVar10 = (double)((*(float *)(param_2 + 0x30) + *(float *)(param_2 + 0x6d4)) -
                       (*(float *)(param_2 + 0x24) + *(float *)(param_2 + 0x6d0)));
      if ((double)FLOAT_80436f68 < dVar10) {
        param_1 = (double)(float)(param_1 + dVar10);
      }
      dVar13 = (double)(float)(param_1 + (double)param_3[1]);
      piVar8 = (int *)FUN_8003fa68(param_3);
      dVar10 = (double)*(float *)(DAT_8043625c + 0x68);
      for (; iVar7 = *piVar8, iVar7 != -1; piVar8 = piVar8 + 1) {
        fVar4 = *(float *)(iVar7 + 4) - local_3c;
        fVar5 = *(float *)(iVar7 + 0x10) - local_3c;
        fVar1 = *(float *)(iVar7 + 0xc) - local_34;
        fVar2 = *(float *)(iVar7 + 0x18) - local_34;
        fVar9 = *(float *)(iVar7 + 0x1c) - local_3c;
        fVar3 = *(float *)(iVar7 + 0x24) - local_34;
        if (((fVar4 * fVar2 <= fVar1 * fVar5) && (fVar5 * fVar3 <= fVar2 * fVar9)) &&
           (fVar9 * fVar1 <= fVar3 * fVar4)) {
          fVar5 = *(float *)(iVar7 + 0x30);
          fVar9 = *(float *)(iVar7 + 0x2c);
          dVar12 = (double)((*(float *)(iVar7 + 0x28) * fVar4 + fVar5 * fVar1 +
                            fVar9 * *(float *)(iVar7 + 8)) / fVar9);
          if (((dVar12 < dVar13) && (dVar12 < dVar11)) && (dVar10 <= dVar12)) {
            *param_4 = *(float *)(iVar7 + 0x28);
            param_4[1] = fVar9;
            param_4[2] = fVar5;
            dVar10 = dVar12;
          }
        }
      }
      uVar6 = 1;
    }
  }
  else {
    uVar6 = 1;
    fVar4 = *(float *)(param_2 + 0x1f0);
    *param_4 = *(float *)(param_2 + 0x1ec);
    param_4[1] = fVar4;
    param_4[2] = *(float *)(param_2 + 500);
  }
  return uVar6;
}



// ==== 8003e0a8  FUN_8003e0a8 ====

/* WARNING: Removing unreachable block (ram,0x8003e3cc) */
/* WARNING: Removing unreachable block (ram,0x8003e3c4) */
/* WARNING: Removing unreachable block (ram,0x8003e0c0) */
/* WARNING: Removing unreachable block (ram,0x8003e0b8) */

double FUN_8003e0a8(double param_1,int param_2,float *param_3,float *param_4)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int *piVar7;
  float fVar8;
  float fVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  
  fVar5 = FLOAT_80436f78;
  fVar4 = FLOAT_80436f68;
  if (*(char *)(param_2 + 0x1db) == '\0') {
    *param_4 = FLOAT_80436f68;
    param_4[1] = fVar5;
    param_4[2] = fVar4;
    iVar6 = zz_003fb00_(param_3);
    if (iVar6 == 0) {
      dVar10 = (double)FLOAT_8043702c;
    }
    else {
      bVar1 = param_1 < (double)*(float *)(DAT_8043625c + 0x34);
      local_54 = *param_3;
      local_50 = param_3[1] + *(float *)(param_2 + 0x6d0);
      local_4c = param_3[2];
      dVar11 = zz_003f320_((double)(*(float *)(param_2 + 0x30) + *(float *)(param_2 + 0x6d4)),
                           &local_54);
      dVar10 = (double)((*(float *)(param_2 + 0x30) + *(float *)(param_2 + 0x6d4)) -
                       (*(float *)(param_2 + 0x24) + *(float *)(param_2 + 0x6d0)));
      if ((double)FLOAT_80436f68 < dVar10) {
        param_1 = (double)(float)(param_1 + dVar10);
      }
      dVar15 = (double)(float)(param_1 + (double)param_3[1]);
      piVar7 = (int *)FUN_8003fa68(param_3);
      dVar10 = (double)*(float *)(DAT_8043625c + 0x68);
      local_6c = FLOAT_80436f68;
      dVar13 = (double)*(float *)(DAT_8043625c + 0x34);
      local_68 = FLOAT_80436f78;
      local_64 = FLOAT_80436f68;
      local_78 = FLOAT_80436f68;
      local_74 = FLOAT_80436f78;
      local_70 = FLOAT_80436f68;
      dVar12 = dVar10;
      for (; iVar6 = *piVar7, iVar6 != -1; piVar7 = piVar7 + 1) {
        fVar4 = *(float *)(iVar6 + 4) - local_54;
        fVar2 = *(float *)(iVar6 + 0xc) - local_4c;
        fVar5 = *(float *)(iVar6 + 0x10) - local_54;
        fVar9 = *(float *)(iVar6 + 0x18) - local_4c;
        fVar8 = *(float *)(iVar6 + 0x1c) - local_54;
        fVar3 = *(float *)(iVar6 + 0x24) - local_4c;
        if (((fVar4 * fVar9 <= fVar2 * fVar5) && (fVar5 * fVar3 <= fVar9 * fVar8)) &&
           (fVar8 * fVar2 <= fVar3 * fVar4)) {
          fVar9 = *(float *)(iVar6 + 0x28);
          fVar5 = *(float *)(iVar6 + 0x30);
          fVar8 = *(float *)(iVar6 + 0x2c);
          dVar14 = (double)((fVar9 * fVar4 + fVar5 * fVar2 + fVar8 * *(float *)(iVar6 + 8)) / fVar8)
          ;
          if (((dVar14 < dVar15) && (dVar14 < dVar11)) && (dVar10 <= dVar14)) {
            *param_4 = fVar9;
            param_4[1] = fVar8;
            param_4[2] = fVar5;
            dVar10 = dVar14;
          }
          if (dVar14 <= dVar13) {
            dVar13 = dVar14;
            local_6c = fVar9;
            local_68 = fVar8;
            local_64 = fVar5;
          }
          if (dVar12 <= dVar14) {
            dVar12 = dVar14;
            local_78 = fVar9;
            local_74 = fVar8;
            local_70 = fVar5;
          }
        }
      }
      if (bVar1) {
        if (dVar10 == (double)*(float *)(DAT_8043625c + 0x68)) {
          *param_4 = local_6c;
          param_4[1] = local_68;
          param_4[2] = local_64;
          dVar10 = dVar13;
          if (dVar13 == (double)*(float *)(DAT_8043625c + 0x34)) {
            dVar10 = (double)*(float *)(DAT_8043625c + 0x68);
          }
        }
      }
      else {
        *param_4 = local_78;
        param_4[1] = local_74;
        param_4[2] = local_70;
        dVar10 = dVar12;
      }
    }
  }
  else {
    gnt4_PSMTXMultVec_bl
              (*(float **)(*(int *)(param_2 + 0x1e0) + 0x60),(float *)(param_2 + 0x1f8),&local_48);
    fVar4 = *(float *)(param_2 + 0x1f0);
    *param_4 = *(float *)(param_2 + 0x1ec);
    param_4[1] = fVar4;
    param_4[2] = *(float *)(param_2 + 500);
    dVar10 = (double)local_44;
  }
  return dVar10;
}



// ==== 8003e3f4  FUN_8003e3f4 ====

/* WARNING: Removing unreachable block (ram,0x8003e6bc) */
/* WARNING: Removing unreachable block (ram,0x8003e6b4) */
/* WARNING: Removing unreachable block (ram,0x8003e6ac) */
/* WARNING: Removing unreachable block (ram,0x8003e6a4) */
/* WARNING: Removing unreachable block (ram,0x8003e41c) */
/* WARNING: Removing unreachable block (ram,0x8003e414) */
/* WARNING: Removing unreachable block (ram,0x8003e40c) */
/* WARNING: Removing unreachable block (ram,0x8003e404) */

double FUN_8003e3f4(double param_1,int param_2,float *param_3,float *param_4)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  int iVar6;
  int *piVar7;
  float fVar8;
  float fVar9;
  double dVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  float local_78;
  float local_74;
  float local_70;
  float local_6c;
  float local_68;
  float local_64;
  
  fVar3 = FLOAT_80436f78;
  fVar2 = FLOAT_80436f68;
  *param_4 = FLOAT_80436f68;
  param_4[1] = fVar3;
  param_4[2] = fVar2;
  iVar6 = zz_003fb00_(param_3);
  if (iVar6 == 0) {
    dVar10 = (double)FLOAT_8043702c;
  }
  else {
    dVar11 = zz_003f320_((double)*(float *)(param_2 + 0x30),param_3);
    bVar1 = param_1 < (double)*(float *)(DAT_8043625c + 0x34);
    if ((*(float *)(param_2 + 0x24) != *(float *)(param_2 + 0x30)) &&
       (dVar10 = (double)(*(float *)(param_2 + 0x30) - *(float *)(param_2 + 0x24)), param_1 < dVar10
       )) {
      param_1 = (double)(float)(param_1 + dVar10);
    }
    dVar17 = (double)*param_3;
    dVar15 = (double)(float)(param_1 + (double)param_3[1]);
    dVar16 = (double)param_3[2];
    piVar7 = (int *)FUN_8003fa68(param_3);
    dVar10 = (double)*(float *)(DAT_8043625c + 0x68);
    local_6c = FLOAT_80436f68;
    dVar13 = (double)*(float *)(DAT_8043625c + 0x34);
    local_68 = FLOAT_80436f78;
    local_64 = FLOAT_80436f68;
    local_78 = FLOAT_80436f68;
    local_74 = FLOAT_80436f78;
    local_70 = FLOAT_80436f68;
    dVar12 = dVar10;
    for (; iVar6 = *piVar7, iVar6 != -1; piVar7 = piVar7 + 1) {
      fVar2 = (float)((double)*(float *)(iVar6 + 4) - dVar17);
      fVar3 = (float)((double)*(float *)(iVar6 + 0xc) - dVar16);
      fVar5 = (float)((double)*(float *)(iVar6 + 0x10) - dVar17);
      fVar8 = (float)((double)*(float *)(iVar6 + 0x18) - dVar16);
      fVar9 = (float)((double)*(float *)(iVar6 + 0x1c) - dVar17);
      fVar4 = (float)((double)*(float *)(iVar6 + 0x24) - dVar16);
      if (((fVar2 * fVar8 <= fVar3 * fVar5) && (fVar5 * fVar4 <= fVar8 * fVar9)) &&
         (fVar9 * fVar3 <= fVar4 * fVar2)) {
        fVar9 = *(float *)(iVar6 + 0x28);
        fVar5 = *(float *)(iVar6 + 0x30);
        fVar8 = *(float *)(iVar6 + 0x2c);
        dVar14 = (double)((fVar9 * fVar2 + fVar5 * fVar3 + fVar8 * *(float *)(iVar6 + 8)) / fVar8);
        if (((dVar14 < dVar15) && (dVar14 < dVar11)) && (dVar10 <= dVar14)) {
          *param_4 = fVar9;
          param_4[1] = fVar8;
          param_4[2] = fVar5;
          dVar10 = dVar14;
        }
        if (dVar14 <= dVar13) {
          dVar13 = dVar14;
          local_6c = fVar9;
          local_68 = fVar8;
          local_64 = fVar5;
        }
        if (dVar12 <= dVar14) {
          dVar12 = dVar14;
          local_78 = fVar9;
          local_74 = fVar8;
          local_70 = fVar5;
        }
      }
    }
    if (bVar1) {
      if (dVar10 == (double)*(float *)(DAT_8043625c + 0x68)) {
        *param_4 = local_6c;
        param_4[1] = local_68;
        param_4[2] = local_64;
        dVar10 = dVar13;
        if (dVar13 == (double)*(float *)(DAT_8043625c + 0x34)) {
          dVar10 = (double)*(float *)(DAT_8043625c + 0x68);
        }
      }
    }
    else {
      *param_4 = local_78;
      param_4[1] = local_74;
      param_4[2] = local_70;
      dVar10 = dVar12;
    }
  }
  return dVar10;
}



// ==== 8003e6e4  zz_003e6e4_ ====

/* WARNING: Removing unreachable block (ram,0x8003e95c) */
/* WARNING: Removing unreachable block (ram,0x8003e6f4) */

undefined4 zz_003e6e4_(float *param_1,float *param_2,float *param_3)

{
  bool bVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  byte bVar6;
  uint uVar5;
  int iVar7;
  int iVar8;
  int *piVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  double dVar14;
  double in_f31;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  undefined4 local_90;
  uint uStack_8c;
  longlong local_88;
  undefined4 local_80;
  uint uStack_7c;
  longlong local_78;
  undefined4 local_70;
  uint uStack_6c;
  longlong local_68;
  undefined4 local_60;
  uint uStack_5c;
  longlong local_58;
  
  iVar3 = zz_003fb00_(param_1);
  if (iVar3 == 0) {
    uVar4 = 0;
  }
  else {
    iVar3 = zz_003fb00_(param_2);
    if (iVar3 == 0) {
      uVar4 = 0;
    }
    else {
      local_90 = 0x43300000;
      iVar13 = *(int *)(DAT_8043625c + 0x1c);
      local_70 = 0x43300000;
      uStack_8c = *(uint *)(iVar13 + 0x10) ^ 0x80000000;
      uStack_7c = *(uint *)(iVar13 + 0x14) ^ 0x80000000;
      local_80 = 0x43300000;
      local_60 = 0x43300000;
      iVar3 = (int)((*param_1 - (float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80436f88)) /
                   FLOAT_80436ffc);
      local_88 = (longlong)iVar3;
      iVar7 = (int)((*param_2 - (float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80436f88)) /
                   FLOAT_80436ffc);
      local_68 = (longlong)iVar7;
      iVar12 = (int)((param_1[2] - (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80436f88)
                     ) / FLOAT_80436ffc);
      local_78 = (longlong)iVar12;
      iVar11 = (int)((param_2[2] - (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80436f88)
                     ) / FLOAT_80436ffc);
      local_58 = (longlong)iVar11;
      iVar2 = iVar7;
      if (iVar7 < iVar3) {
        iVar2 = iVar3;
        iVar3 = iVar7;
      }
      iVar7 = iVar11;
      if (iVar11 < iVar12) {
        iVar7 = iVar12;
        iVar12 = iVar11;
      }
      local_ac = *param_1;
      local_a8 = param_1[1];
      uVar4 = 0;
      bVar1 = false;
      local_a4 = param_1[2];
      local_a0 = *param_2;
      local_9c = param_2[1];
      local_98 = param_2[2];
      uStack_6c = uStack_8c;
      uStack_5c = uStack_7c;
      for (iVar11 = 0; iVar11 <= iVar2 - iVar3; iVar11 = iVar11 + 1) {
        for (iVar10 = 0; iVar10 <= iVar7 - iVar12; iVar10 = iVar10 + 1) {
          for (piVar9 = *(int **)(*(int *)(iVar13 + 0x18) +
                                 (iVar12 + iVar10 + *(int *)(iVar13 + 0xc) * (iVar3 + iVar11)) * 4);
              iVar8 = *piVar9, iVar8 != -1; piVar9 = piVar9 + 1) {
            bVar6 = FUN_80039da4(&local_ac,(float *)(iVar8 + 0x28),(float *)(iVar8 + 4),&local_b8);
            if ((bVar6 != 0) &&
               (uVar5 = zz_0039aec_(&local_b8,(float *)(iVar8 + 4),(float *)(iVar8 + 0x28)),
               uVar5 != 0)) {
              dVar14 = gnt4_PSVECSquareDistance_bl(&local_ac,&local_b8);
              if (bVar1) {
                if (dVar14 < in_f31) {
                  uVar4 = 1;
                  *param_3 = local_b8;
                  param_3[1] = local_b4;
                  param_3[2] = local_b0;
                  in_f31 = dVar14;
                }
              }
              else {
                bVar1 = true;
                uVar4 = 1;
                *param_3 = local_b8;
                param_3[1] = local_b4;
                param_3[2] = local_b0;
                in_f31 = dVar14;
              }
            }
          }
        }
      }
    }
  }
  return uVar4;
}



// ==== 8003e978  zz_003e978_ ====

int zz_003e978_(float *param_1,float *param_2,float *param_3)

{
  int iVar1;
  
  iVar1 = zz_003fb58_(param_1);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = zz_003fb58_(param_2);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = FUN_8003e9f4(param_1,param_2,param_3);
    }
  }
  return iVar1;
}



// ==== 8003e9f4  FUN_8003e9f4 ====

/* WARNING: Removing unreachable block (ram,0x8003ec9c) */
/* WARNING: Removing unreachable block (ram,0x8003ec94) */
/* WARNING: Removing unreachable block (ram,0x8003ec8c) */
/* WARNING: Removing unreachable block (ram,0x8003ea14) */
/* WARNING: Removing unreachable block (ram,0x8003ea0c) */
/* WARNING: Removing unreachable block (ram,0x8003ea04) */

int FUN_8003e9f4(float *param_1,float *param_2,float *param_3)

{
  bool bVar1;
  int iVar2;
  byte bVar4;
  uint uVar3;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int *piVar14;
  double dVar15;
  double in_f29;
  double dVar16;
  double dVar17;
  float local_e8;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  undefined4 local_c0;
  uint uStack_bc;
  longlong local_b8;
  undefined4 local_b0;
  uint uStack_ac;
  longlong local_a8;
  undefined4 local_a0;
  uint uStack_9c;
  longlong local_98;
  undefined4 local_90;
  uint uStack_8c;
  longlong local_88;
  int local_80;
  
  dVar17 = (double)FLOAT_80436ffc;
  local_80 = 8;
  iVar6 = 0;
  bVar1 = false;
  iVar7 = 2;
  dVar16 = DOUBLE_80436f88;
  do {
    local_c0 = 0x43300000;
    iVar12 = *(int *)(DAT_8043625c + local_80 + 0x1c);
    local_a0 = 0x43300000;
    uStack_bc = *(uint *)(iVar12 + 0x10) ^ 0x80000000;
    local_b0 = 0x43300000;
    uStack_ac = *(uint *)(iVar12 + 0x14) ^ 0x80000000;
    local_90 = 0x43300000;
    iVar11 = (int)((double)(*param_1 - (float)((double)CONCAT44(0x43300000,uStack_bc) - dVar16)) /
                  dVar17);
    local_b8 = (longlong)iVar11;
    iVar5 = (int)((double)(*param_2 - (float)((double)CONCAT44(0x43300000,uStack_bc) - dVar16)) /
                 dVar17);
    local_98 = (longlong)iVar5;
    iVar10 = (int)((double)(param_1[2] - (float)((double)CONCAT44(0x43300000,uStack_ac) - dVar16)) /
                  dVar17);
    local_a8 = (longlong)iVar10;
    iVar9 = (int)((double)(param_2[2] - (float)((double)CONCAT44(0x43300000,uStack_ac) - dVar16)) /
                 dVar17);
    local_88 = (longlong)iVar9;
    iVar2 = iVar5;
    if (iVar5 < iVar11) {
      iVar2 = iVar11;
      iVar11 = iVar5;
    }
    iVar5 = iVar9;
    if (iVar9 < iVar10) {
      iVar5 = iVar10;
      iVar10 = iVar9;
    }
    local_dc = *param_1;
    local_d8 = param_1[1];
    local_d4 = param_1[2];
    local_d0 = *param_2;
    local_cc = param_2[1];
    local_c8 = param_2[2];
    uStack_9c = uStack_bc;
    uStack_8c = uStack_ac;
    for (iVar9 = 0; iVar9 <= iVar2 - iVar11; iVar9 = iVar9 + 1) {
      for (iVar8 = 0; iVar8 <= iVar5 - iVar10; iVar8 = iVar8 + 1) {
        for (piVar14 = *(int **)(*(int *)(iVar12 + 0x18) +
                                (iVar10 + iVar8 + *(int *)(iVar12 + 0xc) * (iVar11 + iVar9)) * 4);
            iVar13 = *piVar14, iVar13 != -1; piVar14 = piVar14 + 1) {
          bVar4 = FUN_80039da4(&local_dc,(float *)(iVar13 + 0x28),(float *)(iVar13 + 4),&local_e8);
          if ((bVar4 != 0) &&
             (uVar3 = zz_0039aec_(&local_e8,(float *)(iVar13 + 4),(float *)(iVar13 + 0x28)),
             uVar3 != 0)) {
            dVar15 = gnt4_PSVECSquareDistance_bl(&local_dc,&local_e8);
            if (bVar1) {
              if (dVar15 < in_f29) {
                iVar6 = iVar7 + 1;
                *param_3 = local_e8;
                param_3[1] = local_e4;
                param_3[2] = local_e0;
                in_f29 = dVar15;
              }
            }
            else {
              iVar6 = iVar7 + 1;
              bVar1 = true;
              *param_3 = local_e8;
              param_3[1] = local_e4;
              param_3[2] = local_e0;
              in_f29 = dVar15;
            }
          }
        }
      }
    }
    iVar7 = iVar7 + -1;
    local_80 = local_80 + -4;
  } while (-1 < iVar7);
  return iVar6;
}



// ==== 8003ecb8  zz_003ecb8_ ====

int zz_003ecb8_(float *param_1,float *param_2,float *param_3,undefined4 *param_4)

{
  int iVar1;
  
  iVar1 = zz_003fb58_(param_1);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = zz_003fb58_(param_2);
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = FUN_8003ed44(param_1,param_2,param_3,param_4);
    }
  }
  return iVar1;
}



// ==== 8003ed44  FUN_8003ed44 ====

/* WARNING: Removing unreachable block (ram,0x8003f028) */
/* WARNING: Removing unreachable block (ram,0x8003f020) */
/* WARNING: Removing unreachable block (ram,0x8003f018) */
/* WARNING: Removing unreachable block (ram,0x8003ed64) */
/* WARNING: Removing unreachable block (ram,0x8003ed5c) */
/* WARNING: Removing unreachable block (ram,0x8003ed54) */

int FUN_8003ed44(float *param_1,float *param_2,float *param_3,undefined4 *param_4)

{
  bool bVar1;
  int iVar2;
  undefined4 uVar3;
  byte bVar5;
  uint uVar4;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  int *piVar15;
  double dVar16;
  double in_f29;
  double dVar17;
  double dVar18;
  float local_e4;
  float local_e0;
  float local_dc;
  float local_d8;
  float local_d4;
  float local_d0;
  float local_cc;
  float local_c8;
  float local_c4;
  undefined4 local_c0;
  uint uStack_bc;
  longlong local_b8;
  undefined4 local_b0;
  uint uStack_ac;
  longlong local_a8;
  undefined4 local_a0;
  uint uStack_9c;
  longlong local_98;
  undefined4 local_90;
  uint uStack_8c;
  longlong local_88;
  int local_80;
  
  dVar18 = (double)FLOAT_80436ffc;
  local_80 = 8;
  iVar7 = 0;
  bVar1 = false;
  iVar8 = 2;
  dVar17 = DOUBLE_80436f88;
  do {
    local_c0 = 0x43300000;
    iVar13 = *(int *)(DAT_8043625c + local_80 + 0x1c);
    local_a0 = 0x43300000;
    uStack_bc = *(uint *)(iVar13 + 0x10) ^ 0x80000000;
    local_b0 = 0x43300000;
    uStack_ac = *(uint *)(iVar13 + 0x14) ^ 0x80000000;
    local_90 = 0x43300000;
    iVar12 = (int)((double)(*param_1 - (float)((double)CONCAT44(0x43300000,uStack_bc) - dVar17)) /
                  dVar18);
    local_b8 = (longlong)iVar12;
    iVar6 = (int)((double)(*param_2 - (float)((double)CONCAT44(0x43300000,uStack_bc) - dVar17)) /
                 dVar18);
    local_98 = (longlong)iVar6;
    iVar11 = (int)((double)(param_1[2] - (float)((double)CONCAT44(0x43300000,uStack_ac) - dVar17)) /
                  dVar18);
    local_a8 = (longlong)iVar11;
    iVar10 = (int)((double)(param_2[2] - (float)((double)CONCAT44(0x43300000,uStack_ac) - dVar17)) /
                  dVar18);
    local_88 = (longlong)iVar10;
    iVar2 = iVar6;
    if (iVar6 < iVar12) {
      iVar2 = iVar12;
      iVar12 = iVar6;
    }
    iVar6 = iVar10;
    if (iVar10 < iVar11) {
      iVar6 = iVar11;
      iVar11 = iVar10;
    }
    local_d8 = *param_1;
    local_d4 = param_1[1];
    local_d0 = param_1[2];
    local_cc = *param_2;
    local_c8 = param_2[1];
    local_c4 = param_2[2];
    uStack_9c = uStack_bc;
    uStack_8c = uStack_ac;
    for (iVar10 = 0; iVar10 <= iVar2 - iVar12; iVar10 = iVar10 + 1) {
      for (iVar9 = 0; iVar9 <= iVar6 - iVar11; iVar9 = iVar9 + 1) {
        for (piVar15 = *(int **)(*(int *)(iVar13 + 0x18) +
                                (iVar11 + iVar9 + *(int *)(iVar13 + 0xc) * (iVar12 + iVar10)) * 4);
            iVar14 = *piVar15, iVar14 != -1; piVar15 = piVar15 + 1) {
          bVar5 = FUN_80039da4(&local_d8,(float *)(iVar14 + 0x28),(float *)(iVar14 + 4),&local_e4);
          if ((bVar5 != 0) &&
             (uVar4 = zz_0039aec_(&local_e4,(float *)(iVar14 + 4),(float *)(iVar14 + 0x28)),
             uVar4 != 0)) {
            dVar16 = gnt4_PSVECSquareDistance_bl(&local_d8,&local_e4);
            if (bVar1) {
              if (dVar16 < in_f29) {
                iVar7 = iVar8 + 1;
                *param_3 = local_e4;
                param_3[1] = local_e0;
                param_3[2] = local_dc;
                uVar3 = *(undefined4 *)(iVar14 + 0x2c);
                *param_4 = *(undefined4 *)(iVar14 + 0x28);
                param_4[1] = uVar3;
                param_4[2] = *(undefined4 *)(iVar14 + 0x30);
                in_f29 = dVar16;
              }
            }
            else {
              iVar7 = iVar8 + 1;
              bVar1 = true;
              *param_3 = local_e4;
              param_3[1] = local_e0;
              param_3[2] = local_dc;
              uVar3 = *(undefined4 *)(iVar14 + 0x2c);
              *param_4 = *(undefined4 *)(iVar14 + 0x28);
              param_4[1] = uVar3;
              param_4[2] = *(undefined4 *)(iVar14 + 0x30);
              in_f29 = dVar16;
            }
          }
        }
      }
    }
    iVar8 = iVar8 + -1;
    local_80 = local_80 + -4;
  } while (-1 < iVar8);
  return iVar7;
}



// ==== 8003f044  zz_003f044_ ====

undefined4 zz_003f044_(float *param_1,float *param_2,float *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = zz_003fb58_(param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    iVar1 = zz_003fb58_(param_2);
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = zz_003f0c0_(param_1,param_2,param_3);
    }
  }
  return uVar2;
}



// ==== 8003f0c0  zz_003f0c0_ ====

/* WARNING: Removing unreachable block (ram,0x8003f304) */
/* WARNING: Removing unreachable block (ram,0x8003f0d0) */

undefined4 zz_003f0c0_(float *param_1,float *param_2,float *param_3)

{
  bool bVar1;
  int iVar2;
  byte bVar4;
  uint uVar3;
  int iVar5;
  int iVar6;
  int *piVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  double dVar14;
  double in_f31;
  float local_b8;
  float local_b4;
  float local_b0;
  float local_ac;
  float local_a8;
  float local_a4;
  float local_a0;
  float local_9c;
  float local_98;
  undefined4 local_90;
  uint uStack_8c;
  longlong local_88;
  undefined4 local_80;
  uint uStack_7c;
  longlong local_78;
  undefined4 local_70;
  uint uStack_6c;
  longlong local_68;
  undefined4 local_60;
  uint uStack_5c;
  longlong local_58;
  
  local_90 = 0x43300000;
  iVar13 = *(int *)(DAT_8043625c + 0x20);
  local_70 = 0x43300000;
  uStack_8c = *(uint *)(iVar13 + 0x10) ^ 0x80000000;
  uStack_7c = *(uint *)(iVar13 + 0x14) ^ 0x80000000;
  local_80 = 0x43300000;
  local_60 = 0x43300000;
  iVar12 = (int)((*param_1 - (float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80436f88)) /
                FLOAT_80436ffc);
  local_88 = (longlong)iVar12;
  iVar5 = (int)((*param_2 - (float)((double)CONCAT44(0x43300000,uStack_8c) - DOUBLE_80436f88)) /
               FLOAT_80436ffc);
  local_68 = (longlong)iVar5;
  iVar11 = (int)((param_1[2] - (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80436f88)) /
                FLOAT_80436ffc);
  local_78 = (longlong)iVar11;
  iVar10 = (int)((param_2[2] - (float)((double)CONCAT44(0x43300000,uStack_7c) - DOUBLE_80436f88)) /
                FLOAT_80436ffc);
  local_58 = (longlong)iVar10;
  iVar2 = iVar5;
  if (iVar5 < iVar12) {
    iVar2 = iVar12;
    iVar12 = iVar5;
  }
  iVar5 = iVar10;
  if (iVar10 < iVar11) {
    iVar5 = iVar11;
    iVar11 = iVar10;
  }
  local_ac = *param_1;
  local_a8 = param_1[1];
  uVar8 = 0;
  bVar1 = false;
  local_a4 = param_1[2];
  local_a0 = *param_2;
  local_9c = param_2[1];
  local_98 = param_2[2];
  uStack_6c = uStack_8c;
  uStack_5c = uStack_7c;
  for (iVar10 = 0; iVar10 <= iVar2 - iVar12; iVar10 = iVar10 + 1) {
    for (iVar9 = 0; iVar9 <= iVar5 - iVar11; iVar9 = iVar9 + 1) {
      for (piVar7 = *(int **)(*(int *)(iVar13 + 0x18) +
                             (iVar11 + iVar9 + *(int *)(iVar13 + 0xc) * (iVar12 + iVar10)) * 4);
          iVar6 = *piVar7, iVar6 != -1; piVar7 = piVar7 + 1) {
        bVar4 = FUN_80039da4(&local_ac,(float *)(iVar6 + 0x28),(float *)(iVar6 + 4),&local_b8);
        if ((bVar4 != 0) &&
           (uVar3 = zz_0039aec_(&local_b8,(float *)(iVar6 + 4),(float *)(iVar6 + 0x28)), uVar3 != 0)
           ) {
          dVar14 = gnt4_PSVECSquareDistance_bl(&local_ac,&local_b8);
          if (bVar1) {
            if (dVar14 < in_f31) {
              uVar8 = 1;
              *param_3 = local_b8;
              param_3[1] = local_b4;
              param_3[2] = local_b0;
              in_f31 = dVar14;
            }
          }
          else {
            bVar1 = true;
            uVar8 = 1;
            *param_3 = local_b8;
            param_3[1] = local_b4;
            param_3[2] = local_b0;
            in_f31 = dVar14;
          }
        }
      }
    }
  }
  return uVar8;
}



// ==== 8003f320  zz_003f320_ ====

/* WARNING: Removing unreachable block (ram,0x8003f66c) */
/* WARNING: Removing unreachable block (ram,0x8003f330) */

double zz_003f320_(double param_1,float *param_2)

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
  int iVar11;
  int *piVar12;
  double dVar13;
  double dVar14;
  double local_38;
  double local_30;
  double local_28;
  undefined8 local_20;
  
  iVar11 = zz_003fb00_(param_2);
  if (iVar11 == 0) {
    dVar13 = (double)param_2[1];
  }
  else {
    iVar11 = *(int *)(DAT_8043625c + 0x24);
    fVar1 = *param_2;
    local_28 = (double)(CONCAT44(0x43300000,*(undefined4 *)(iVar11 + 0x10)) ^ 0x80000000);
    local_38 = (double)(CONCAT44(0x43300000,*(undefined4 *)(iVar11 + 0x14)) ^ 0x80000000);
    fVar2 = param_2[2];
    dVar13 = (double)*(float *)(DAT_8043625c + 0x34);
    for (piVar12 = *(int **)(*(int *)(iVar11 + 0x18) +
                            ((int)((fVar2 - (float)(local_38 - DOUBLE_80436f88)) / FLOAT_80436ffc) +
                            (int)((fVar1 - (float)(local_28 - DOUBLE_80436f88)) / FLOAT_80436ffc) *
                            *(int *)(iVar11 + 0xc)) * 4); iVar11 = *piVar12, iVar11 != -1;
        piVar12 = piVar12 + 1) {
      fVar3 = *(float *)(iVar11 + 4) - fVar1;
      fVar5 = *(float *)(iVar11 + 0xc) - fVar2;
      fVar10 = *(float *)(iVar11 + 0x10) - fVar1;
      fVar6 = *(float *)(iVar11 + 0x18) - fVar2;
      fVar4 = *(float *)(iVar11 + 0x1c) - fVar1;
      fVar9 = fVar5 * fVar10;
      fVar8 = fVar3 * fVar6;
      fVar7 = *(float *)(iVar11 + 0x24) - fVar2;
      if (fVar9 - fVar8 <= FLOAT_80436f68) {
        fVar6 = fVar6 * fVar4;
        fVar10 = fVar10 * fVar7;
        if (fVar6 - fVar10 <= FLOAT_80436f68) {
          fVar7 = fVar7 * fVar3;
          fVar4 = fVar4 * fVar5;
          if ((((fVar7 - fVar4 <= FLOAT_80436f68) && (fVar9 <= fVar8)) && (fVar6 <= fVar10)) &&
             (((fVar7 <= fVar4 &&
               (dVar14 = (double)((*(float *)(iVar11 + 0x28) * fVar3 +
                                   *(float *)(iVar11 + 0x30) * fVar5 +
                                  *(float *)(iVar11 + 0x2c) * *(float *)(iVar11 + 8)) /
                                 *(float *)(iVar11 + 0x2c)), param_1 < dVar14)) &&
              (dVar14 <= dVar13)))) {
            dVar13 = dVar14;
          }
        }
      }
    }
    iVar11 = *(int *)(DAT_8043625c + 0x20);
    local_30 = (double)(CONCAT44(0x43300000,*(undefined4 *)(iVar11 + 0x10)) ^ 0x80000000);
    local_20 = (double)CONCAT44(0x43300000,*(uint *)(iVar11 + 0x14) ^ 0x80000000);
    for (piVar12 = *(int **)(*(int *)(iVar11 + 0x18) +
                            ((int)((param_2[2] - (float)(local_20 - DOUBLE_80436f88)) /
                                  FLOAT_80436ffc) +
                            (int)((*param_2 - (float)(local_30 - DOUBLE_80436f88)) / FLOAT_80436ffc)
                            * *(int *)(iVar11 + 0xc)) * 4); iVar11 = *piVar12, iVar11 != -1;
        piVar12 = piVar12 + 1) {
      fVar3 = *(float *)(iVar11 + 4) - fVar1;
      fVar5 = *(float *)(iVar11 + 0xc) - fVar2;
      fVar10 = *(float *)(iVar11 + 0x10) - fVar1;
      fVar6 = *(float *)(iVar11 + 0x18) - fVar2;
      fVar4 = *(float *)(iVar11 + 0x1c) - fVar1;
      fVar9 = fVar5 * fVar10;
      fVar8 = fVar3 * fVar6;
      fVar7 = *(float *)(iVar11 + 0x24) - fVar2;
      if (fVar9 - fVar8 <= FLOAT_80436f68) {
        fVar6 = fVar6 * fVar4;
        fVar10 = fVar10 * fVar7;
        if (fVar6 - fVar10 <= FLOAT_80436f68) {
          fVar7 = fVar7 * fVar3;
          fVar4 = fVar4 * fVar5;
          if (((fVar7 - fVar4 <= FLOAT_80436f68) && (fVar9 <= fVar8)) &&
             ((fVar6 <= fVar10 && (fVar7 <= fVar4)))) {
            fVar10 = *(float *)(iVar11 + 0x2c);
            if (((fVar10 <= FLOAT_80436f70) &&
                (dVar14 = (double)((*(float *)(iVar11 + 0x28) * fVar3 +
                                    *(float *)(iVar11 + 0x30) * fVar5 +
                                   fVar10 * *(float *)(iVar11 + 8)) / fVar10), param_1 < dVar14)) &&
               (dVar14 <= dVar13)) {
              dVar13 = dVar14;
            }
          }
        }
      }
    }
  }
  return dVar13;
}



// ==== 8003f688  FUN_8003f688 ====

void FUN_8003f688(int param_1,float *param_2,float *param_3,float *param_4)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  float local_38;
  float local_34;
  float local_30;
  float local_2c;
  float local_28;
  float local_24;
  float local_20;
  float local_1c;
  float local_18;
  
  dVar4 = FUN_8003e0a8((double)*(float *)(param_1 + 0x668),param_1,param_2,&local_38);
  if ((*(char *)(param_1 + 0x1db) == '\0') && (*(char *)(param_1 + 0x87) == '\0')) {
    fVar2 = param_2[1];
    *param_3 = *param_2;
    param_3[1] = fVar2;
    param_3[2] = param_2[2];
    param_3[1] = (float)dVar4;
    *param_4 = local_38;
    param_4[1] = local_34;
    param_4[2] = local_30;
  }
  else {
    local_2c = *param_2;
    local_28 = param_2[1];
    local_24 = param_2[2];
    local_1c = (float)dVar4;
    local_20 = local_2c;
    local_18 = local_24;
    iVar3 = FUN_80037b98(param_1,&local_2c,&local_20,&local_2c);
    fVar2 = FLOAT_80436f68;
    if (iVar3 == 0) {
      *param_3 = local_20;
      param_3[1] = local_1c;
      param_3[2] = local_18;
      *param_4 = local_38;
      param_4[1] = local_34;
      param_4[2] = local_30;
    }
    else {
      *param_3 = local_2c;
      fVar1 = FLOAT_80436f78;
      param_3[1] = local_28;
      param_3[2] = local_24;
      *param_4 = fVar2;
      param_4[1] = fVar1;
      param_4[2] = fVar2;
    }
  }
  return;
}



// ==== 8003f7d4  zz_003f7d4_ ====

void zz_003f7d4_(int param_1)

{
  float fVar1;
  bool bVar2;
  int iVar3;
  double dVar4;
  float local_48;
  float local_44;
  undefined4 local_40;
  float local_3c;
  float local_38;
  undefined4 local_34;
  float local_30;
  float local_2c;
  undefined4 local_28;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  if (*(float *)(DAT_8043625c + 0x3c) <= *(float *)(param_1 + 0x7bc)) {
    if (*(float *)(DAT_8043625c + 0x38) < *(float *)(param_1 + 0x7bc)) {
      *(float *)(param_1 + 0x7bc) = *(float *)(DAT_8043625c + 0x38);
    }
  }
  else {
    *(float *)(param_1 + 0x7bc) = *(float *)(DAT_8043625c + 0x3c);
  }
  if (*(float *)(DAT_8043625c + 0x44) <= *(float *)(param_1 + 0x7c4)) {
    if (*(float *)(DAT_8043625c + 0x40) < *(float *)(param_1 + 0x7c4)) {
      *(float *)(param_1 + 0x7c4) = *(float *)(DAT_8043625c + 0x40);
    }
  }
  else {
    *(float *)(param_1 + 0x7c4) = *(float *)(DAT_8043625c + 0x44);
  }
  if (*(char *)(param_1 + 0x7c9) == '\x01') {
    local_48 = *(float *)(param_1 + 0x20);
    bVar2 = false;
    local_40 = *(undefined4 *)(param_1 + 0x28);
    local_44 = *(float *)(param_1 + 0x24) + FLOAT_80437030;
    local_3c = *(float *)(param_1 + 0x7bc);
    local_38 = *(float *)(param_1 + 0x7c0) + FLOAT_80437030;
    local_34 = *(undefined4 *)(param_1 + 0x7c4);
    iVar3 = FUN_80037b98(param_1,&local_48,&local_3c,&local_24);
    if (iVar3 != 0) {
      local_30 = local_3c;
      local_28 = local_34;
      local_2c = local_38 + *(float *)(DAT_8043625c + 0x34);
      iVar3 = FUN_80037b98(param_1,&local_30,&local_3c,&local_24);
      if (iVar3 != 0) {
        bVar2 = true;
        *(float *)(param_1 + 0x20) = local_24;
        *(undefined4 *)(param_1 + 0x24) = local_20;
        *(undefined4 *)(param_1 + 0x28) = local_1c;
      }
    }
    if (!bVar2) {
      iVar3 = zz_003f0c0_(&local_48,&local_3c,&local_48);
      if (iVar3 == 0) {
        dVar4 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x7bc))
        ;
        local_38 = (float)dVar4;
        *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x7bc);
        *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x7c0);
        *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x7c4);
        if (*(float *)(param_1 + 0x24) <= local_38) {
          *(float *)(param_1 + 0x24) = local_38;
        }
      }
      else {
        dVar4 = FUN_8003d6e4((double)*(float *)(DAT_8043625c + 0x34),param_1,&local_3c);
        local_38 = (float)dVar4;
        *(float *)(param_1 + 0x20) = local_3c;
        *(float *)(param_1 + 0x24) = local_38;
        *(undefined4 *)(param_1 + 0x28) = local_34;
      }
    }
  }
  else {
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x7bc);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x7c0);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x7c4);
  }
  *(undefined4 *)(param_1 + 0x2c) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x30) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x34) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x5e8) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x5ec) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x5f0) = *(undefined4 *)(param_1 + 0x28);
  dVar4 = zz_003f320_((double)*(float *)(param_1 + 0x24),(float *)(param_1 + 0x20));
  fVar1 = (float)(dVar4 - (double)*(float *)(param_1 + 0x24));
  if (fVar1 < *(float *)(param_1 + 0x668)) {
    zz_002caa8_((double)((fVar1 / *(float *)(param_1 + 0x668)) * FLOAT_80436f7c),param_1);
  }
  return;
}



// ==== 8003fa68  FUN_8003fa68 ====

undefined4 FUN_8003fa68(float *param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(DAT_8043625c + 0x1c);
  return *(undefined4 *)
          (*(int *)(iVar1 + 0x18) +
          ((int)((param_1[2] -
                 (float)((double)CONCAT44(0x43300000,*(uint *)(iVar1 + 0x14) ^ 0x80000000) -
                        DOUBLE_80436f88)) / FLOAT_80436ffc) +
          (int)((*param_1 -
                (float)((double)CONCAT44(0x43300000,*(uint *)(iVar1 + 0x10) ^ 0x80000000) -
                       DOUBLE_80436f88)) / FLOAT_80436ffc) * *(int *)(iVar1 + 0xc)) * 4);
}



// ==== 8003fb00  zz_003fb00_ ====

undefined4 zz_003fb00_(float *param_1)

{
  if ((*param_1 <= FLOAT_80437034) || (FLOAT_80437038 <= *param_1)) {
    return 0;
  }
  if ((FLOAT_80437034 < param_1[2]) && (param_1[2] < FLOAT_80437038)) {
    return 1;
  }
  return 0;
}



// ==== 8003fb58  zz_003fb58_ ====

undefined4 zz_003fb58_(float *param_1)

{
  if ((*param_1 < *(float *)(DAT_8043625c + 0x3c)) || (*(float *)(DAT_8043625c + 0x38) < *param_1))
  {
    return 0;
  }
  if ((*(float *)(DAT_8043625c + 0x44) <= param_1[2]) &&
     (param_1[2] <= *(float *)(DAT_8043625c + 0x40))) {
    return 1;
  }
  return 0;
}



// ==== 8003fbac  zz_003fbac_ ====

void zz_003fbac_(void)

{
  zz_008c098_();
  if ((char)PTR_DAT_80433930[1] < '\x01') {
    gnt4_memset(PTR_DAT_80433938,0,0x20);
    zz_008c3a0_(0);
    if ((char)PTR_DAT_80433930[1] < '\0') {
      PTR_DAT_80433938[0x14] = 1;
    }
    PTR_DAT_80433930[1] = 1;
  }
  (*(code *)(&PTR_zz_003fc44__802d0158)[(char)*PTR_DAT_80433938])();
  zz_0027ae8_();
  return;
}



// ==== 8003fc44  zz_003fc44_ ====

void zz_003fc44_(void)

{
  (*(code *)(&PTR_zz_003fc84__802d0174)[(char)PTR_DAT_80433938[1]])();
  return;
}



// ==== 8003fc84  zz_003fc84_ ====

void zz_003fc84_(void)

{
  undefined8 uVar1;
  double dVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  
  PTR_DAT_80433938[1] = PTR_DAT_80433938[1] + '\x01';
  if (DAT_804361c4 != 0) {
    PTR_DAT_80433938[1] = PTR_DAT_80433938[1] + '\x01';
  }
  zz_00059b8_();
  zz_002a5f4_(0,0,0,0);
  dVar5 = (double)DAT_803c1080;
  DAT_803c0fd8 = DAT_803c1098;
  dVar8 = (double)DAT_803c10a8;
  dVar7 = (double)DAT_803c10ac;
  dVar6 = (double)DAT_803c10b0;
  dVar4 = (double)DAT_803c1084;
  DAT_803c0fc0 = DAT_803c1080;
  dVar3 = (double)DAT_803c1088;
  dVar2 = (double)DAT_803c108c;
  DAT_803c0fdc = DAT_803c109c;
  DAT_803c0fe0 = DAT_803c10a0;
  DAT_803c0fe4 = DAT_803c10a4;
  DAT_803c0fe8 = DAT_803c10a8;
  DAT_803c0fec = DAT_803c10ac;
  DAT_803c0ff0 = DAT_803c10b0;
  DAT_803c0fc4 = DAT_803c1084;
  DAT_803c0fc8 = DAT_803c1088;
  DAT_803c0fcc = DAT_803c108c;
  DAT_803c0fd0 = DAT_803c1090;
  DAT_803c0fd4 = DAT_803c1094;
  zz_000584c_();
  zz_00055e0_();
  zz_0027a78_();
  zz_000bb70_();
  uVar1 = zz_0197854_(6);
  zz_0088398_(DAT_80436238 + 0x9ebc00,0x60000,1);
  zz_01ae92c_(uVar1,dVar2,dVar3,dVar4,dVar5,dVar6,dVar7,dVar8);
  zz_0080124_();
  gnt4_HSD_VISetBlack_bl(0);
  gnt4_VIFlush_bl();
  gnt4_VIWaitForRetrace();
  gnt4_VIWaitForRetrace();
  return;
}



// ==== 8003fdb8  zz_003fdb8_ ====

void zz_003fdb8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,uint *param_12,
                undefined4 *param_13,uint param_14,int param_15,uint param_16)

{
  int iVar1;
  
  iVar1 = zz_0088190_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  if (iVar1 != 0) {
    PTR_DAT_80433938[1] = PTR_DAT_80433938[1] + '\x01';
  }
  return;
}



// ==== 8003fdf0  zz_003fdf0_ ====

void zz_003fdf0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  *PTR_DAT_80433938 = *PTR_DAT_80433938 + '\x01';
  PTR_DAT_80433938[1] = 0;
  zz_00447a8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 8003fe2c  zz_003fe2c_ ====

void zz_003fe2c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined *puVar2;
  undefined8 uVar3;
  undefined8 extraout_f1;
  undefined8 extraout_f1_00;
  undefined8 extraout_f1_01;
  undefined8 extraout_f1_02;
  undefined8 extraout_f1_03;
  undefined8 extraout_f1_04;
  undefined8 extraout_f1_05;
  undefined8 extraout_f1_06;
  
  zz_00055fc_();
  iVar1 = zz_000a3c4_();
  if (iVar1 == 0) {
    uVar3 = zz_00449e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0);
    *PTR_DAT_80433938 = *PTR_DAT_80433938 + '\x01';
    if (PTR_DAT_80433938[0x14] != '\0') {
      *PTR_DAT_80433938 = *PTR_DAT_80433938 + '\x01';
    }
    PTR_DAT_80433938[1] = 0;
    PTR_DAT_80433938[2] = 0;
    puVar2 = PTR_DAT_80433938;
    PTR_DAT_80433938[3] = 0;
    uVar3 = zz_0044920_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,puVar2,
                        param_11,param_12,param_13,param_14,param_15,param_16);
    puVar2 = PTR_DAT_80433938;
    PTR_DAT_80433938[3] = 0xff;
    uVar3 = zz_000a154_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_004060c_,0,
                        puVar2,param_12,param_13,param_14,param_15,param_16);
    uVar3 = zz_00449c0_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,puVar2,param_12,param_13,param_14
                        ,param_15,param_16);
    uVar3 = zz_0042994_(extraout_f1_00,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,puVar2,param_12,param_13,param_14
                        ,param_15,param_16);
    uVar3 = zz_004394c_(extraout_f1_01,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,puVar2,param_12,param_13,param_14
                        ,param_15,param_16);
    uVar3 = zz_0040f1c_(extraout_f1_02,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,puVar2,param_12,param_13,param_14
                        ,param_15,param_16);
    uVar3 = zz_0040ff4_(extraout_f1_03,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,puVar2,param_12,param_13,param_14
                        ,param_15,param_16);
    uVar3 = zz_0043758_(extraout_f1_04,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,puVar2,param_12,param_13,param_14
                        ,param_15,param_16);
    uVar3 = zz_0043890_(extraout_f1_05,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,puVar2,param_12,param_13,param_14
                        ,param_15,param_16);
    zz_0043a64_(extraout_f1_06,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                (int)((ulonglong)uVar3 >> 0x20),(int)uVar3,puVar2,param_12,param_13,param_14,
                param_15,param_16);
  }
  return;
}



// ==== 8003fef0  zz_003fef0_ ====

void zz_003fef0_(void)

{
  int iVar1;
  
  iVar1 = zz_01ae9b4_();
  if (iVar1 == 0) {
    zz_0089898_(0x38);
    zz_0089658_();
    zz_008a16c_();
    zz_0089c00_(0x38);
    zz_008c104_(FUN_80089f28);
  }
  else {
    *PTR_DAT_80433938 = *PTR_DAT_80433938 + '\x01';
    PTR_DAT_80433938[1] = 0;
  }
  return;
}



// ==== 8003ff5c  zz_003ff5c_ ====

/* WARNING: Removing unreachable block (ram,0x80040024) */
/* WARNING: Removing unreachable block (ram,0x8004008c) */

void zz_003ff5c_(void)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  undefined2 uVar4;
  undefined1 uVar5;
  ushort uVar7;
  byte bVar8;
  undefined1 *puVar6;
  uint uVar9;
  uint *puVar10;
  uint uVar11;
  int iVar12;
  undefined1 local_8;
  undefined1 uStack_7;
  undefined1 uStack_6;
  undefined1 uStack_5;
  undefined1 local_4;
  undefined1 uStack_3;
  
  uVar5 = DAT_80437046;
  uVar4 = DAT_80437044;
  uVar3 = DAT_80437040;
  cVar1 = PTR_DAT_80433938[1];
  if (cVar1 != '\x02') {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined4 *)(PTR_DAT_80433938 + 0x10) = 0;
        uVar7 = VIGetDTVStatus();
        if (uVar7 == 0) {
          PTR_DAT_80433938[1] = 0xff;
        }
        else {
          PTR_DAT_80433938[1] = PTR_DAT_80433938[1] + '\x01';
          PTR_DAT_80433938[2] = 0;
          PTR_DAT_80433938[6] = 0;
        }
        goto LAB_80040528;
      }
      if (-1 < cVar1) {
        bVar8 = gnt4_OSGetProgressiveMode_bl();
        if (bVar8 == 0) {
          uVar11 = 0;
          puVar10 = &DAT_803c727c;
          iVar12 = 4;
          do {
            uVar9 = *puVar10;
            puVar10 = puVar10 + 8;
            uVar11 = uVar11 | uVar9 & 0x200;
            iVar12 = iVar12 + -1;
          } while (iVar12 != 0);
          if (uVar11 == 0) {
            PTR_DAT_80433938[1] = 0xff;
          }
          else {
            PTR_DAT_80433938[1] = PTR_DAT_80433938[1] + '\x01';
          }
        }
        else {
          PTR_DAT_80433938[1] = PTR_DAT_80433938[1] + '\x01';
        }
        goto LAB_80040528;
      }
    }
    else {
      if (cVar1 == '\x04') {
        cVar1 = PTR_DAT_80433938[2];
        if (cVar1 == '\x02') {
LAB_80040488:
          uVar11 = zz_01b27a0_(*(int *)(PTR_DAT_80433938 + 0x10));
          if (uVar11 == 0) goto LAB_80040528;
          PTR_DAT_80433938[2] = PTR_DAT_80433938[2] + '\x01';
        }
        else {
          if (cVar1 < '\x02') {
            if (cVar1 == '\0') {
              sVar2 = *(short *)(PTR_DAT_80433938 + 0xe);
              *(short *)(PTR_DAT_80433938 + 0xe) = sVar2 + -1;
              if ((0 < (short)(sVar2 + -1)) && (PTR_DAT_80433938[6] == '\0')) goto LAB_80040528;
              if (PTR_DAT_80433938[6] == '\0') {
                gnt4_HSD_VISetBlack_bl(0);
                gnt4_VIFlush_bl();
                gnt4_VIWaitForRetrace();
                gnt4_VIWaitForRetrace();
                gnt4_VIWaitForRetrace();
              }
              PTR_DAT_80433938[2] = PTR_DAT_80433938[2] + '\x01';
              *(undefined2 *)(PTR_DAT_80433938 + 0xe) = 0xf0;
            }
            else if (cVar1 < '\0') goto LAB_80040528;
            PTR_DAT_80433938[7] = PTR_DAT_80433938[6] + ',';
            puVar6 = zz_01b1fd8_(1,0xff,PTR_DAT_80433938 + 7,PTR_DAT_80433938 + 8);
            *(undefined1 **)(PTR_DAT_80433938 + 0x10) = puVar6;
            if (*(int *)(PTR_DAT_80433938 + 0x10) == 0) goto LAB_80040528;
            PTR_DAT_80433938[2] = PTR_DAT_80433938[2] + '\x01';
            goto LAB_80040488;
          }
          if ('\x03' < cVar1) goto LAB_80040528;
        }
        sVar2 = *(short *)(PTR_DAT_80433938 + 0xe);
        *(short *)(PTR_DAT_80433938 + 0xe) = sVar2 + -1;
        if (((short)(sVar2 + -1) < 1) || (uVar11 = zz_008b810_(0xf), uVar11 != 0)) {
          *(undefined4 *)(PTR_DAT_80433938 + 0x10) = 0;
          PTR_DAT_80433938[1] = 0xff;
          PTR_DAT_80433938[7] = 0xff;
          *(undefined2 *)(PTR_DAT_80433938 + 8) = 1;
        }
        goto LAB_80040528;
      }
      if (cVar1 < '\x04') {
        if (PTR_DAT_80433938[6] == '\0') {
          zz_02278c8_((uint *)&DAT_803aa9f4,(uint *)&DAT_803ca644,0,0x10);
          local_8 = (undefined1)((uint)uVar3 >> 0x18);
          uStack_7 = (undefined1)((uint)uVar3 >> 0x10);
          uStack_6 = (undefined1)((uint)uVar3 >> 8);
          uStack_5 = (undefined1)uVar3;
          local_4 = (undefined1)((ushort)uVar4 >> 8);
          uStack_3 = (undefined1)uVar4;
          DAT_803ca676 = local_8;
          DAT_803ca677 = uStack_7;
          DAT_803ca678 = uStack_6;
          DAT_803ca679 = uStack_5;
          DAT_803ca67a = local_4;
          DAT_803ca67b = uStack_3;
          DAT_803ca67c = uVar5;
          gnt4_GXSetCopyFilter_bl(DAT_803ca65d,&DAT_803ca65e,'\x01',&DAT_803ca676);
          gnt4_HSD_VISetConfigure_bl((undefined4 *)&DAT_803ca644);
          DAT_804362ac = &DAT_803f8e80;
          gnt4_HSD_VISetBlack_bl(1);
          gnt4_VIFlush_bl();
          gnt4_VIWaitForRetrace();
          gnt4_VIWaitForRetrace();
          gnt4_VIWaitForRetrace();
          gnt4_OSSetProgressiveMode_bl('\x01');
          PTR_DAT_80433938[0x14] = 1;
          *(undefined2 *)(PTR_DAT_80433938 + 0xe) = 100;
        }
        else {
          gnt4_OSSetProgressiveMode_bl('\0');
          PTR_DAT_80433938[0x14] = 1;
          *(undefined2 *)(PTR_DAT_80433938 + 0xe) = 0;
        }
        PTR_DAT_80433938[1] = PTR_DAT_80433938[1] + '\x01';
        PTR_DAT_80433938[2] = 0;
        goto LAB_80040528;
      }
    }
    *PTR_DAT_80433938 = *PTR_DAT_80433938 + '\x01';
    PTR_DAT_80433938[1] = 0;
    PTR_DAT_80433938[0x14] = 1;
    goto LAB_80040528;
  }
  cVar1 = PTR_DAT_80433938[2];
  if (cVar1 == '\x01') {
LAB_8004017c:
    uVar11 = zz_01b27a0_(*(int *)(PTR_DAT_80433938 + 0x10));
    if (uVar11 == 0) goto LAB_80040528;
    PTR_DAT_80433938[2] = PTR_DAT_80433938[2] + '\x01';
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') goto LAB_80040528;
      PTR_DAT_80433938[7] = 0x2b;
      *(undefined2 *)(PTR_DAT_80433938 + 8) = 0;
      *(undefined2 *)(PTR_DAT_80433938 + 10) = 0;
      *(undefined2 *)(PTR_DAT_80433938 + 0xc) = 600;
      puVar6 = zz_01b1fd8_(1,0xff,PTR_DAT_80433938 + 7,PTR_DAT_80433938 + 8);
      *(undefined1 **)(PTR_DAT_80433938 + 0x10) = puVar6;
      if (*(int *)(PTR_DAT_80433938 + 0x10) == 0) goto LAB_80040528;
      PTR_DAT_80433938[2] = PTR_DAT_80433938[2] + '\x01';
      goto LAB_8004017c;
    }
    if ('\x02' < cVar1) goto LAB_80040528;
  }
  PTR_DAT_80433938[5] = PTR_DAT_80433938[6];
  uVar11 = zz_008bab0_(0xf,3,1);
  iVar12 = zz_008ba58_(uVar11,(int)(char)PTR_DAT_80433938[6],1,1);
  PTR_DAT_80433938[6] = (char)iVar12;
  if (PTR_DAT_80433938[6] != PTR_DAT_80433938[5]) {
    zz_00f0468_(0,1,0);
    *(undefined2 *)(PTR_DAT_80433938 + 0xc) = 600;
  }
  sVar2 = *(short *)(PTR_DAT_80433938 + 0xc);
  *(short *)(PTR_DAT_80433938 + 0xc) = sVar2 + -1;
  if (((short)(sVar2 + -1) < 1) || (uVar11 = zz_008b810_(0xf), uVar11 != 0)) {
    PTR_DAT_80433938[1] = PTR_DAT_80433938[1] + '\x01';
    PTR_DAT_80433938[7] = 0xff;
    zz_00f0468_(0,2,0);
  }
  else {
    zz_008c104_(zz_004056c_);
  }
LAB_80040528:
  if (*(int *)(PTR_DAT_80433938 + 0x10) != 0) {
    zz_0089898_(0x38);
    zz_0089658_();
    zz_008a16c_();
    zz_0089c00_(0x38);
    zz_008c104_(FUN_80089f28);
  }
  return;
}



// ==== 8004056c  zz_004056c_ ====

void zz_004056c_(void)

{
  int iVar1;
  undefined4 local_8;
  undefined4 local_4;
  
  zz_01b27b8_(*(int *)(PTR_DAT_80433938 + 0x10),&local_4,&local_8);
  iVar1 = 0x1b;
  if (PTR_DAT_80433938[6] == '\0') {
    iVar1 = 0x1d;
  }
  zz_0097144_(100,local_4._2_2_ + (local_8._2_2_ + -1) * 0x18,iVar1,&DAT_802b0ba0);
  iVar1 = 0x1b;
  if (PTR_DAT_80433938[6] == '\x01') {
    iVar1 = 0x1d;
  }
  zz_0097144_(100,local_4._2_2_ + local_8._2_2_ * 0x18,iVar1,&DAT_80437048);
  return;
}



// ==== 8004060c  zz_004060c_ ====

void zz_004060c_(void)

{
  PTR_DAT_80433938[3] = 0;
  return;
}



// ==== 8004061c  zz_004061c_ ====

void zz_004061c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined *param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined8 uVar4;
  
  if (PTR_DAT_80433938[3] != '\0') {
    return;
  }
  cVar1 = PTR_DAT_80433938[1];
  if (cVar1 == '\x02') {
    sVar2 = *(short *)(PTR_DAT_80433938 + 8);
    *(short *)(PTR_DAT_80433938 + 8) = sVar2 + -1;
    if ((short)(sVar2 + -1) < 1) {
      PTR_DAT_80433938[1] = PTR_DAT_80433938[1] + '\x01';
      zz_0027aac_(0xff,0x3c,1);
    }
    goto LAB_8004076c;
  }
  if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      zz_00434f8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,PTR_DAT_80433938
                  ,param_11,param_12,param_13,param_14,param_15,param_16);
      PTR_DAT_80433938[1] = PTR_DAT_80433938[1] + '\x01';
      PTR_DAT_80433938[2] = 0;
      zz_0027aac_(0xff,0x3c,0);
      *(undefined2 *)(PTR_DAT_80433938 + 8) = 0x78;
    }
    else if (cVar1 < '\0') goto LAB_80040700;
  }
  else if ('\x03' < cVar1) {
LAB_80040700:
    if (PTR_DAT_80433938[2] == '\0') {
      iVar3 = zz_000a3c4_();
      if (iVar3 == 0) {
        PTR_DAT_80433938[2] = PTR_DAT_80433938[2] + '\x01';
        zz_00f07c4_();
      }
    }
    else {
      zz_0027dc0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                  PTR_DAT_80433938,param_11,param_12,param_13,param_14,param_15,param_16);
      uVar4 = zz_00435dc_(0);
      zz_00438dc_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      zz_0080170_();
      zz_0027c1c_();
      *PTR_DAT_80433938 = *PTR_DAT_80433938 + '\x01';
      PTR_DAT_80433938[1] = 0;
      PTR_DAT_80433938[2] = 0;
    }
    goto LAB_8004076c;
  }
  iVar3 = zz_0027adc_();
  if (iVar3 == 0) {
    PTR_DAT_80433938[1] = PTR_DAT_80433938[1] + '\x01';
  }
LAB_8004076c:
  if (*PTR_DAT_80433938 == '\x05') {
    zz_001882c_(&DAT_803c04b0);
  }
  return;
}



// ==== 80040798  zz_0040798_ ====

void zz_0040798_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  short sVar2;
  int iVar3;
  undefined *in_r7;
  undefined *puVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  
  cVar1 = PTR_DAT_80433938[1];
  if (cVar1 == '\x02') {
LAB_80040818:
    sVar2 = *(short *)(PTR_DAT_80433938 + 8);
    *(short *)(PTR_DAT_80433938 + 8) = sVar2 + -1;
    puVar4 = PTR_DAT_80433938;
    if (0 < (short)(sVar2 + -1)) goto LAB_8004087c;
    PTR_DAT_80433938[1] = PTR_DAT_80433938[1] + '\x01';
    zz_0027aac_(0xff,0x3c,1);
    in_r7 = puVar4;
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        PTR_DAT_80433938[1] = 1;
        zz_0027aac_(0xff,0x3c,0);
      }
      else if (cVar1 < '\0') goto LAB_8004087c;
      iVar3 = zz_0027adc_();
      if (iVar3 != 0) goto LAB_8004087c;
      PTR_DAT_80433938[1] = PTR_DAT_80433938[1] + '\x01';
      *(undefined2 *)(PTR_DAT_80433938 + 8) = 0x3c;
      goto LAB_80040818;
    }
    if ('\x03' < cVar1) goto LAB_8004087c;
  }
  iVar3 = zz_0027adc_();
  if (iVar3 == 0) {
    *PTR_DAT_80433938 = *PTR_DAT_80433938 + '\x01';
    PTR_DAT_80433938[1] = 0;
    zz_0027c1c_();
  }
LAB_8004087c:
  if (*PTR_DAT_80433938 == '\x02') {
    uVar5 = zz_008028c_((double)FLOAT_80437050);
    zz_0080184_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0xb0,0xd4,0xffffffff,
                s_Licensed_by_Nintendo_802b0bac,in_r7,in_r8,in_r9,in_r10);
  }
  return;
}



// ==== 800408c0  zz_00408c0_ ====

void zz_00408c0_(void)

{
  zz_01978d0_();
  *PTR_DAT_80433930 = 1;
  PTR_DAT_80433930[1] = 0;
  PTR_DAT_80433930[0x32] = 0;
  PTR_DAT_80433930[0x32] = 0;
  PTR_DAT_80433930[0x41] = 1;
  return;
}



// ==== 80040910  zz_0040910_ ====

void zz_0040910_(void)

{
  gnt4_memset(&DAT_803bb168,0,0x1c4);
  return;
}



// ==== 80040940  zz_0040940_ ====

void zz_0040940_(void)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  
  zz_0040910_();
  iVar2 = 0;
  puVar3 = &DAT_803bb168;
  DAT_803bb188 = 0;
  iVar1 = DAT_8043620c;
  while (iVar1 != 0) {
    zz_0245a80_(iVar1,puVar3);
    DAT_803bb188 = DAT_803bb188 + 1;
    *(undefined4 *)((int)&DAT_803bb1d4 + iVar2) = *puVar3;
    *(undefined4 *)((int)&DAT_803bb23c + iVar2) = *puVar3;
    *(undefined4 *)((int)&DAT_803bb2a4 + iVar2) = *puVar3;
    *(undefined4 *)((int)&DAT_803bb30c + iVar2) = *puVar3;
    if (iVar1 == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(iVar1 + 0xc);
    }
    puVar3 = puVar3 + 1;
    iVar2 = iVar2 + 4;
  }
  return;
}



// ==== 80040a00  zz_0040a00_ ====

void zz_0040a00_(undefined4 param_1,int param_2,int param_3)

{
  float fVar1;
  double dVar2;
  double dVar3;
  int iVar4;
  
  dVar3 = DOUBLE_80437060;
  dVar2 = DOUBLE_80437058;
  iVar4 = param_2 + param_3 * 4;
  fVar1 = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(iVar4 + 8)) - DOUBLE_80437058);
  *(char *)(iVar4 + 0x48) =
       (char)(int)((float)((double)CONCAT44(0x43300000,(int)*(char *)(param_2 + 4) ^ 0x80000000) -
                          DOUBLE_80437060) *
                   (((float)((double)CONCAT44(0x43300000,(uint)*(byte *)(iVar4 + 0x28)) -
                            DOUBLE_80437058) - fVar1) /
                   (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_2 + 5) ^ 0x80000000) -
                          DOUBLE_80437060)) + fVar1);
  fVar1 = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(iVar4 + 9)) - dVar2);
  *(char *)(iVar4 + 0x49) =
       (char)(int)((float)((double)CONCAT44(0x43300000,(int)*(char *)(param_2 + 4) ^ 0x80000000) -
                          dVar3) *
                   (((float)((double)CONCAT44(0x43300000,(uint)*(byte *)(iVar4 + 0x29)) - dVar2) -
                    fVar1) / (float)((double)CONCAT44(0x43300000,
                                                      (int)*(char *)(param_2 + 5) ^ 0x80000000) -
                                    dVar3)) + fVar1);
  fVar1 = (float)((double)CONCAT44(0x43300000,(uint)*(byte *)(iVar4 + 10)) - dVar2);
  *(char *)(iVar4 + 0x4a) =
       (char)(int)((float)((double)CONCAT44(0x43300000,(int)*(char *)(param_2 + 4) ^ 0x80000000) -
                          dVar3) *
                   (((float)((double)CONCAT44(0x43300000,(uint)*(byte *)(iVar4 + 0x2a)) - dVar2) -
                    fVar1) / (float)((double)CONCAT44(0x43300000,
                                                      (int)*(char *)(param_2 + 5) ^ 0x80000000) -
                                    dVar3)) + fVar1);
  return;
}



// ==== 80040b94  zz_0040b94_ ====

void zz_0040b94_(void)

{
  char cVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  short sVar5;
  undefined4 *puVar4;
  int iVar6;
  int iVar7;
  undefined4 *puVar8;
  undefined4 local_28 [5];
  
  iVar7 = 0;
  puVar8 = &DAT_803bb168;
  do {
    puVar3 = puVar8 + 9;
    if (*(char *)(puVar8 + 9) != '\0') {
      cVar1 = *(char *)((int)puVar8 + 0x25);
      if (cVar1 == '\x02') {
LAB_80040bf4:
        *(char *)(puVar8 + 10) = *(char *)(puVar8 + 10) + '\x01';
        if (*(char *)(puVar8 + 10) == *(char *)((int)puVar8 + 0x29)) {
          for (iVar6 = 0; iVar6 < DAT_803bb188; iVar6 = iVar6 + 1) {
            puVar3[0x12] = puVar3[10];
            puVar3 = puVar3 + 1;
          }
          *(char *)((int)puVar8 + 0x25) = *(char *)((int)puVar8 + 0x25) + '\x01';
        }
        else {
          for (iVar6 = 0; iVar6 < DAT_803bb188; iVar6 = iVar6 + 1) {
            zz_0040a00_(&DAT_803bb168,(int)puVar3,iVar6);
          }
        }
      }
      else if (cVar1 < '\x02') {
        if (cVar1 == '\0') goto LAB_80040bf4;
        if ((-1 < cVar1) &&
           (sVar5 = *(short *)((int)puVar8 + 0x2a) + -1, *(short *)((int)puVar8 + 0x2a) = sVar5,
           sVar5 < 1)) {
          *(char *)((int)puVar8 + 0x25) = *(char *)((int)puVar8 + 0x25) + '\x01';
          *(undefined1 *)(puVar8 + 10) = 0;
          *(undefined1 *)((int)puVar8 + 0x29) = *(undefined1 *)((int)puVar8 + 0x27);
          puVar4 = &DAT_803bb168;
          for (iVar6 = 0; iVar6 < DAT_803bb188; iVar6 = iVar6 + 1) {
            puVar3[2] = puVar3[0x12];
            uVar2 = *puVar4;
            puVar4 = puVar4 + 1;
            puVar3[10] = uVar2;
            puVar3 = puVar3 + 1;
          }
        }
      }
      else if (cVar1 < '\x04') {
        *(undefined1 *)((int)puVar8 + 0x25) = 0;
        *(undefined1 *)puVar3 = 0;
      }
    }
    iVar7 = iVar7 + 1;
    puVar8 = puVar8 + 0x1a;
    if (3 < iVar7) {
      if (DAT_8043620c != 0) {
        puVar8 = &DAT_803bb168;
        iVar7 = DAT_8043620c;
        while (iVar7 != 0) {
          local_28[0] = puVar8[0x1b];
          gnt4_HSD_LObjSetColor(iVar7,local_28);
          if (iVar7 == 0) {
            iVar7 = 0;
          }
          else {
            iVar7 = *(int *)(iVar7 + 0xc);
          }
          puVar8 = puVar8 + 1;
        }
      }
      return;
    }
  } while( true );
}



// ==== 80040d64  zz_0040d64_ ====

void zz_0040d64_(undefined4 param_1,int param_2)

{
  undefined1 uVar1;
  undefined1 uVar2;
  undefined2 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  int iVar9;
  int iVar10;
  
  iVar4 = param_2 * 8;
  puVar7 = &DAT_803bb168;
  iVar10 = 2;
  do {
    *(undefined1 *)(puVar7 + 9) = 1;
    puVar8 = puVar7 + 9;
    uVar1 = (&DAT_802d01bc)[iVar4];
    *(undefined1 *)((int)puVar7 + 0x25) = 0;
    uVar2 = (&DAT_802d01bd)[iVar4];
    *(undefined1 *)((int)puVar7 + 0x26) = uVar1;
    uVar3 = *(undefined2 *)(&DAT_802d01be + iVar4);
    *(undefined1 *)((int)puVar7 + 0x27) = uVar2;
    puVar6 = (undefined4 *)(&PTR_DAT_802d01c0)[param_2 * 2];
    *(undefined2 *)((int)puVar7 + 0x2a) = uVar3;
    *(undefined1 *)(puVar7 + 10) = 0;
    *(undefined1 *)((int)puVar7 + 0x29) = *(undefined1 *)((int)puVar7 + 0x26);
    for (iVar9 = 0; iVar9 < DAT_803bb188; iVar9 = iVar9 + 1) {
      uVar5 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8[10] = uVar5;
      puVar8[2] = puVar8[0x12];
      puVar8 = puVar8 + 1;
    }
    *(undefined1 *)(puVar7 + 0x23) = 1;
    puVar8 = puVar7 + 0x23;
    uVar1 = (&DAT_802d01bc)[iVar4];
    *(undefined1 *)((int)puVar7 + 0x8d) = 0;
    uVar2 = (&DAT_802d01bd)[iVar4];
    *(undefined1 *)((int)puVar7 + 0x8e) = uVar1;
    uVar3 = *(undefined2 *)(&DAT_802d01be + iVar4);
    *(undefined1 *)((int)puVar7 + 0x8f) = uVar2;
    puVar6 = (undefined4 *)(&PTR_DAT_802d01c0)[param_2 * 2];
    *(undefined2 *)((int)puVar7 + 0x92) = uVar3;
    *(undefined1 *)(puVar7 + 0x24) = 0;
    *(undefined1 *)((int)puVar7 + 0x91) = *(undefined1 *)((int)puVar7 + 0x8e);
    for (iVar9 = 0; iVar9 < DAT_803bb188; iVar9 = iVar9 + 1) {
      uVar5 = *puVar6;
      puVar6 = puVar6 + 1;
      puVar8[10] = uVar5;
      puVar8[2] = puVar8[0x12];
      puVar8 = puVar8 + 1;
    }
    puVar7 = puVar7 + 0x34;
    iVar10 = iVar10 + -1;
  } while (iVar10 != 0);
  return;
}



// ==== 80040e94  zz_0040e94_ ====

void zz_0040e94_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,float *param_10)

{
  gnt4_HSD_LObjGetLightVector_bl
            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10);
  return;
}



// ==== 80040eb4  zz_0040eb4_ ====

void zz_0040eb4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,uint *param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  *(uint **)(param_9 + 0x14) = param_10;
  zz_0006c88_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              *param_10,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80040edc  zz_0040edc_ ====

void zz_0040edc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int *param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int *piVar1;
  
  piVar1 = zz_0197a0c_(1);
  *param_9 = (int)piVar1;
  zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*param_9,
              (uint *)param_9[1],param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80040f1c  zz_0040f1c_ ====

void zz_0040f1c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_80436238 + 0xfe800;
  iVar1 = zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x2b8,iVar2,
                      param_11,param_12,param_13,param_14,param_15,param_16);
  *(int *)(PTR_DAT_80433954 + 0x88) = iVar1;
  zz_000b1a0_(iVar2,0xa49800,iVar1);
  return;
}



// ==== 80040f74  zz_0040f74_ ====

void zz_0040f74_(void)

{
  DAT_803b079c = DAT_80436238 + 0x25f400;
  DAT_803b07a0 = DAT_80436238 + 0x264c00;
  DAT_803b07a4 = DAT_80436238 + 0x1f3400;
  DAT_803b07a8 = DAT_80436238 + 0x1f2c00;
  *(int *)(PTR_DAT_80433934 + 0x98) = DAT_803b079c;
  *(int *)(PTR_DAT_80433934 + 0x9c) = DAT_803b07a0;
  DAT_80436254 = DAT_803b07a4;
  DAT_80436258 = DAT_803b07a8;
  zz_00188d4_(0xa49800,&DAT_803b079c);
  return;
}



// ==== 80040ff4  zz_0040ff4_ ====

void zz_0040ff4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_80436238 + 0xfe800;
  iVar1 = zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0xaa0,iVar2,
                      param_11,param_12,param_13,param_14,param_15,param_16);
  *(int *)(PTR_DAT_80433954 + 0x8c) = iVar1;
  zz_000b1a0_(iVar2,0xa36800,iVar1);
  return;
}



// ==== 8004104c  zz_004104c_ ====

void zz_004104c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint *puVar3;
  
  uVar2 = 1;
  iVar1 = *(int *)(PTR_DAT_80433954 + 0x8c);
  puVar3 = (uint *)(DAT_80436238 + 0x918400);
  zz_00f19f8_((uint)puVar3,0xa36800,iVar1,1);
  DAT_803bb384 = zz_0197a0c_(1);
  zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_803bb384,
              puVar3,iVar1,uVar2,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 800410bc  zz_00410bc_ ====

void zz_00410bc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  undefined *puVar1;
  int iVar2;
  undefined *puVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  char cVar8;
  undefined *puVar7;
  undefined *puVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  
  iVar2 = DAT_80436238;
  puVar1 = PTR_DAT_80433934;
  iVar6 = param_9 * 4;
  iVar11 = DAT_80436238 + 0x270000;
  iVar13 = DAT_80436238 + param_9 * 0x6c000;
  *(undefined4 *)(&DAT_803c4d94 + iVar6) = 0;
  *(undefined4 *)(puVar1 + iVar6 + 0x80) = 0;
  iVar12 = iVar11 + param_9 * 0x58000;
  iVar14 = iVar11 + param_9 * 0x800;
  *(undefined4 *)(&DAT_803bb4a0 + iVar6) = 0;
  *(undefined4 *)(&DAT_803c4d7c + iVar6) = 0;
  gnt4_memset((void *)(param_9 * 0xc30 + -0x7fc44b40),0,0xc30);
  iVar6 = param_9 * 0x38;
  piVar4 = (int *)(&DAT_803b07ac + iVar6);
  piVar5 = piVar4;
  for (cVar8 = '\0'; puVar1 = PTR_DAT_80433934, cVar8 < '\x0e'; cVar8 = cVar8 + '\a') {
    *piVar5 = -0x10000000;
    piVar5[1] = -0x10000000;
    piVar5[2] = -0x10000000;
    piVar5[3] = -0x10000000;
    piVar5[4] = -0x10000000;
    piVar5[5] = -0x10000000;
    piVar5[6] = -0x10000000;
    piVar5 = piVar5 + 7;
  }
  cVar8 = PTR_DAT_80433934[param_9 * 2 + 0x10];
  if (-1 < cVar8) {
    uVar10 = (uint)(byte)PTR_DAT_80433934[param_9 * 2 + 0x11];
    *piVar4 = iVar14 + -0x7400;
    puVar7 = &DAT_803b07ac + iVar6;
    *(int *)(&DAT_803b07b4 + iVar6) = iVar2 + param_9 * 0x2000 + 0x703c00;
    puVar9 = &DAT_803b07bc + iVar6;
    *(int *)(&DAT_803b07b8 + iVar6) = iVar13 + 0x47bc00;
    puVar3 = (&PTR_DAT_802d0584)[cVar8];
    *(undefined4 *)(&DAT_803b07d0 + iVar6) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07cc + iVar6) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07c8 + iVar6) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07c4 + iVar6) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07c0 + iVar6) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07bc + iVar6) = 0xf0000000;
    cVar8 = puVar1[param_9 + 0xa0];
    *(int *)(puVar9 + cVar8 * 4) = iVar12 + -0x4400;
    zz_000b07c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(puVar3 + uVar10 * 4),piVar4,cVar8 * 4,0xf0000000,puVar7,puVar9,uVar10,
                iVar11);
    zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_00412c4_,2,
                param_9,(int)(char)PTR_DAT_80433934[param_9 + 0xa0],puVar7,puVar9,uVar10,iVar11);
  }
  return;
}



// ==== 80041288  zz_0041288_ ====

void zz_0041288_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    param_1 = zz_00410bc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1);
    iVar1 = iVar1 + 1;
  } while (iVar1 < 6);
  return;
}



// ==== 800412c4  zz_00412c4_ ====

void zz_00412c4_(int param_1,int param_2)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  
  puVar2 = PTR_DAT_80433934;
  iVar5 = param_1 * 0x38;
  iVar1 = param_1 * 4;
  *(undefined4 *)(&DAT_803c4d94 + iVar1) = *(undefined4 *)(&DAT_803b07ac + iVar5);
  *(undefined4 *)(puVar2 + iVar1 + 0x80) = *(undefined4 *)(&DAT_803b07b4 + iVar5);
  uVar3 = *(undefined4 *)(&DAT_803b07bc + iVar5 + param_2 * 4);
  *(undefined4 *)(&DAT_803c4d7c + iVar1) = *(undefined4 *)(&DAT_803b07b8 + iVar5);
  *(undefined4 *)(&DAT_803bb4a0 + iVar1) = uVar3;
  piVar4 = zz_0197a0c_(1);
  *(int **)(&DAT_803bbac0 + param_1 * 0xc30) = piVar4;
  return;
}



// ==== 80041364  FUN_80041364 ====

void FUN_80041364(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined *puVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  
  puVar2 = PTR_DAT_80433934;
  iVar5 = param_1 * 0x38;
  iVar1 = param_1 * 4;
  *(undefined4 *)(&DAT_803c4d94 + iVar1) = *(undefined4 *)(&DAT_803b07ac + iVar5);
  *(undefined4 *)(puVar2 + iVar1 + 0x80) = *(undefined4 *)(&DAT_803b07b4 + iVar5);
  uVar3 = *(undefined4 *)((int)(&DAT_803b07ac + iVar5) + param_3 * 4);
  *(undefined4 *)(&DAT_803c4d7c + iVar1) = *(undefined4 *)(&DAT_803b07b8 + iVar5);
  *(undefined4 *)(&DAT_803bb4a0 + iVar1) = uVar3;
  piVar4 = zz_0197a0c_(1);
  puVar2 = PTR_DAT_80433934;
  iVar5 = param_2 * 0x38;
  iVar1 = param_2 * 4;
  *(undefined4 *)(&DAT_803c4d94 + iVar1) = *(undefined4 *)(&DAT_803b07ac + iVar5);
  uVar3 = *(undefined4 *)(&DAT_803b07b4 + iVar5);
  *(int **)(&DAT_803bbac0 + param_1 * 0xc30) = piVar4;
  *(undefined4 *)(puVar2 + iVar1 + 0x80) = uVar3;
  uVar3 = *(undefined4 *)((int)(&DAT_803b07ac + iVar5) + param_3 * 4);
  *(undefined4 *)(&DAT_803c4d7c + iVar1) = *(undefined4 *)(&DAT_803b07b8 + iVar5);
  *(undefined4 *)(&DAT_803bb4a0 + iVar1) = uVar3;
  piVar4 = zz_0197a0c_(1);
  *(int **)(&DAT_803bbac0 + param_2 * 0xc30) = piVar4;
  return;
}



// ==== 80041470  FUN_80041470 ====

void FUN_80041470(int param_1,int param_2,int param_3)

{
  int iVar1;
  size_t __n;
  
  iVar1 = param_3 * 4;
  __n = (&DAT_803c06cc)[param_3] - (int)*(void **)(&DAT_803b07ac + iVar1 + param_1 * 0x38);
  gnt4_memcpy(*(void **)(&DAT_803b07ac + iVar1 + param_2 * 0x38),
              *(void **)(&DAT_803b07ac + iVar1 + param_1 * 0x38),__n);
  gnt4_DCFlushRange_bl(*(uint *)(&DAT_803b07ac + iVar1 + param_2 * 0x38),__n);
  return;
}



// ==== 800414ec  zz_00414ec_ ====

void zz_00414ec_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  undefined *puVar1;
  int iVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  
  iVar7 = DAT_80436238;
  puVar1 = PTR_DAT_80433934;
  iVar2 = param_9 * 4;
  iVar9 = DAT_80436238 + 0x270000;
  iVar11 = DAT_80436238 + param_9 * 0x6c000;
  *(undefined4 *)(&DAT_803c4d94 + iVar2) = 0;
  iVar8 = param_9 * 0x800;
  *(undefined4 *)(puVar1 + iVar2 + 0x80) = 0;
  iVar10 = iVar9 + param_9 * 0x58000;
  iVar13 = iVar9 + iVar8;
  *(undefined4 *)(&DAT_803bb4a0 + iVar2) = 0;
  iVar7 = iVar7 + 0x700000;
  *(undefined4 *)(&DAT_803c4d7c + iVar2) = 0;
  iVar12 = iVar7 + param_9 * 0x2000;
  gnt4_memset((void *)(param_9 * 0xc30 + -0x7fc44b40),0,0xc30);
  iVar5 = param_9 * 0x38;
  piVar3 = (int *)(&DAT_803b07ac + iVar5);
  piVar4 = piVar3;
  for (cVar6 = '\0'; puVar1 = PTR_DAT_80433934, cVar6 < '\x0e'; cVar6 = cVar6 + '\a') {
    *piVar4 = -0x10000000;
    piVar4[1] = -0x10000000;
    piVar4[2] = -0x10000000;
    piVar4[3] = -0x10000000;
    piVar4[4] = -0x10000000;
    piVar4[5] = -0x10000000;
    piVar4[6] = -0x10000000;
    piVar4 = piVar4 + 7;
  }
  if (-1 < (char)PTR_DAT_80433934[param_9 * 2 + 0x10]) {
    *piVar3 = iVar13 + -0x7400;
    *(int *)(&DAT_803b07b4 + iVar5) = iVar12 + 0x3c00;
    iVar2 = *(int *)(&DAT_80433690 + iVar2);
    *(int *)(&DAT_803b07b8 + iVar5) = iVar11 + 0x47bc00;
    *(undefined4 *)(&DAT_803b07d0 + iVar5) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07cc + iVar5) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07c8 + iVar5) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07c4 + iVar5) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07c0 + iVar5) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07bc + iVar5) = 0xf0000000;
    *(int *)(&DAT_803b07bc + iVar5 + (char)(puVar1 + param_9)[0xa0] * 4) = iVar10 + -0x4400;
    zz_000b07c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,piVar3,
                puVar1 + param_9,&DAT_803b07ac + iVar5,&DAT_803b07bc + iVar5,iVar7,iVar8,iVar9);
  }
  return;
}



// ==== 80041678  FUN_80041678 ====

void FUN_80041678(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 int param_9)

{
  int iVar1;
  int *piVar2;
  uint *puVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  iVar4 = param_9 * 0xc30;
  iVar1 = *(int *)(&DAT_803bbac0 + iVar4);
  piVar2 = *(int **)(&DAT_803bb4a0 + param_9 * 4);
  *(int **)(&DAT_803bbac4 + iVar4) = piVar2;
  puVar3 = (uint *)((int)piVar2 + *piVar2);
  *(uint **)(iVar1 + 0x14) = puVar3;
  zz_0006c88_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,puVar3,*puVar3,
              iVar4,in_r7,in_r8,in_r9,in_r10);
  return;
}



// ==== 800416d0  zz_00416d0_ ====

void zz_00416d0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,short param_11,int param_12)

{
  int iVar1;
  undefined *puVar2;
  int *piVar3;
  int *piVar4;
  int iVar5;
  char cVar7;
  int iVar6;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  undefined8 uVar14;
  
  iVar1 = DAT_80436238;
  puVar2 = PTR_DAT_80433934;
  iVar5 = param_9 * 0x10;
  iVar9 = *(int *)(&DAT_802d0b98 + iVar5);
  iVar11 = param_10 * 4;
  iVar12 = *(int *)(&DAT_802d0b90 + iVar5);
  *(undefined4 *)(&DAT_803c4d94 + iVar11) = 0;
  iVar13 = *(int *)(&DAT_802d0b94 + iVar5);
  iVar10 = *(int *)(&DAT_802d0b9c + iVar5);
  *(undefined4 *)(puVar2 + iVar11 + 0x80) = 0;
  *(undefined4 *)(&DAT_803c4d7c + iVar11) = 0;
  *(undefined4 *)(&DAT_803bb4a0 + iVar11) = 0;
  gnt4_memset((void *)(param_10 * 0xc30 + -0x7fc44b40),0,0xc30);
  iVar5 = param_10 * 0x38;
  piVar3 = (int *)(&DAT_803b07ac + iVar5);
  piVar4 = piVar3;
  for (cVar7 = '\0'; cVar7 < '\x0e'; cVar7 = cVar7 + '\a') {
    *piVar4 = -0x10000000;
    piVar4[1] = -0x10000000;
    piVar4[2] = -0x10000000;
    piVar4[3] = -0x10000000;
    piVar4[4] = -0x10000000;
    piVar4[5] = -0x10000000;
    piVar4[6] = -0x10000000;
    piVar4 = piVar4 + 7;
  }
  iVar11 = (int)(char)((ushort)param_11 >> 8);
  if (-1 < iVar11) {
    *piVar3 = iVar1 + iVar12 + param_10 * 0x800;
    uVar8 = 0xf0000000;
    *(int *)(&DAT_803b07b4 + iVar5) = iVar1 + iVar13 + param_10 * 0x2000;
    *(int *)(&DAT_803b07b8 + iVar5) = iVar1 + iVar9 + param_10 * 0x6c000;
    iVar13 = *(int *)(&DAT_802d0b70 + param_9 * 8);
    iVar9 = param_12 * 4;
    *(undefined4 *)(&DAT_803b07d0 + iVar5) = 0xf0000000;
    iVar6 = *(int *)(&DAT_802d0b74 + param_9 * 8);
    *(undefined4 *)(&DAT_803b07cc + iVar5) = 0xf0000000;
    iVar12 = DAT_80436238;
    *(undefined4 *)(&DAT_803b07c8 + iVar5) = 0xf0000000;
    iVar6 = iVar12 + iVar6;
    puVar2 = (&PTR_DAT_802d0584)[iVar11];
    *(undefined4 *)(&DAT_803b07c4 + iVar5) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07c0 + iVar5) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07bc + iVar5) = 0xf0000000;
    *(int *)(&DAT_803b07bc + iVar9 + iVar5) = iVar1 + iVar10 + param_10 * 0x58000;
    piVar3[iVar13 + 2] = iVar6;
    zz_000b07c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(puVar2 + ((int)param_11 & 0xffU) * 4),piVar3,iVar11 * 4,(iVar13 + 2) * 4,
                iVar6,iVar12,iVar9,0xf0000000);
    uVar14 = zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_00412c4_
                         ,2,param_10,param_12,iVar6,iVar12,iVar9,uVar8);
    uVar14 = zz_000a154_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80041678
                         ,2,param_10,param_12,iVar6,iVar12,iVar9,uVar8);
    zz_000a154_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_008bed8_,4,
                DAT_80436238 + *(int *)(&DAT_802d0b74 + param_9 * 8),&DAT_803c04b0,&DAT_803c03b0,
                &DAT_803c0350,iVar9,uVar8);
  }
  return;
}



// ==== 80041910  FUN_80041910 ====

void FUN_80041910(int param_1)

{
  *(undefined4 *)PTR_DAT_80433954 = *(undefined4 *)(param_1 + 4);
  *(undefined4 *)(PTR_DAT_80433954 + 4) = *(undefined4 *)(param_1 + 8);
  *(undefined4 *)(PTR_DAT_80433954 + 8) = *(undefined4 *)(param_1 + 0xc);
  zz_003d4a0_();
  return;
}



// ==== 80041954  zz_0041954_ ====

void zz_0041954_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  undefined4 uVar5;
  
  puVar4 = &DAT_803b078c;
  uVar5 = 0;
  PTR_DAT_80433934[0x1c] = (char)param_10;
  uVar3 = 0xf0000000;
  iVar1 = *(int *)(&DAT_802d0bd0 + param_9 * 4);
  DAT_803b0790 = DAT_80436238 + iVar1;
  DAT_803b0794 = 0;
  DAT_803b0798 = 0;
  DAT_803b078c = 0xf0000000;
  iVar2 = DAT_80436238;
  zz_000b07c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(&DAT_802d05c4 + param_10 * 4),&DAT_803b078c,DAT_803b0790,iVar1,DAT_80436238,
              0xf0000000,&DAT_803b078c,0);
  zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80041910,1,
              &DAT_803b078c,iVar1,iVar2,uVar3,puVar4,uVar5);
  return;
}



// ==== 800419ec  zz_00419ec_ ====

void zz_00419ec_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  uint *puVar3;
  undefined4 extraout_r4;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  
  iVar1 = zz_0006f98_(param_9);
  piVar2 = *(int **)(&DAT_803bb4a0 + *(char *)(param_9 + 0x3e4) * 4);
  if (piVar2 != (int *)0x0) {
    iVar6 = *(int *)(iVar1 + 0x600);
    *(int **)(iVar1 + 0x604) = piVar2;
    puVar3 = (uint *)((int)piVar2 + *piVar2);
    *(uint **)(iVar6 + 0x14) = puVar3;
    uVar9 = zz_0006c88_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,puVar3
                        ,*puVar3,param_12,param_13,param_14,param_15,param_16);
    *(undefined4 *)(iVar1 + 0xc28) = 0xff;
    *(undefined4 *)(iVar1 + 0xc2c) = 0;
    iVar8 = iVar1;
    for (iVar7 = 0; iVar7 < *(short *)(*(int *)(iVar1 + 0x600) + 0x1a); iVar7 = iVar7 + 1) {
      piVar2 = zz_0197a0c_(0);
      *(int **)(iVar8 + 0x708) = piVar2;
      uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                          *(int *)(iVar8 + 0x708),iVar7,iVar1 + 0xc28,param_13,param_14,param_15,
                          param_16);
      iVar8 = iVar8 + 4;
    }
    iVar8 = iVar1;
    for (iVar7 = 0; iVar7 < *(short *)(*(int *)(iVar1 + 0x600) + 0x1a); iVar7 = iVar7 + 1) {
      piVar2 = zz_0197a0c_(0);
      *(int **)(iVar8 + 0x788) = piVar2;
      iVar5 = iVar1 + 0xc28;
      iVar4 = iVar7;
      uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                          *(int *)(iVar8 + 0x788),iVar7,iVar5,param_13,param_14,param_15,param_16);
      zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar8 + 0x788),extraout_r4,iVar4,iVar5,param_13,param_14,param_15,
                  param_16);
      uVar9 = zz_0007cac_((double)FLOAT_80437068,*(int *)(iVar8 + 0x788));
      iVar8 = iVar8 + 4;
    }
  }
  return;
}



// ==== 80041b20  zz_0041b20_ ====

void zz_0041b20_(int param_1)

{
  zz_004be08_(*(int **)(&DAT_803c4d7c + *(char *)(param_1 + 0x3e4) * 4));
  return;
}



// ==== 80041b58  zz_0041b58_ ====

void zz_0041b58_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = param_1 * 0xc30;
  iVar3 = iVar1 + -0x7fc44b40;
  for (iVar2 = 0; iVar2 < *(short *)((int)*(int **)(&DAT_803bbac0 + iVar1) + 0x1a);
      iVar2 = iVar2 + 1) {
    zz_0197ad8_(*(int **)(iVar3 + 0x708));
    zz_0197ad8_(*(int **)(iVar3 + 0x788));
    iVar3 = iVar3 + 4;
  }
  zz_0197ad8_(*(int **)(&DAT_803bbac0 + iVar1));
  *(undefined4 *)(&DAT_803bbac0 + iVar1) = 0;
  zz_004d63c_(param_1);
  return;
}



// ==== 80041bf0  zz_0041bf0_ ====

void zz_0041bf0_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,char *param_10,char param_11)

{
  char cVar1;
  byte bVar2;
  void *__s;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  undefined4 uVar6;
  int iVar7;
  undefined8 uVar8;
  
  uVar8 = zz_0041b58_((int)*(char *)(param_9 + 999));
  __s = (void *)zz_0006f98_(param_9);
  gnt4_memset(__s,0,0xc30);
  puVar5 = PTR_DAT_80433934;
  *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_9 + 0x3e4) * 4) = 0;
  *(undefined4 *)(puVar5 + *(char *)(param_9 + 0x3e4) * 4 + 0x80) = 0;
  *(undefined4 *)(&DAT_803c4d7c + *(char *)(param_9 + 0x3e4) * 4) = 0;
  *(undefined4 *)(&DAT_803bb4a0 + *(char *)(param_9 + 0x3e4) * 4) = 0;
  gnt4_memset((void *)(*(char *)(param_9 + 0x3e4) * 0xc30 + -0x7fc44b40),0,0xc30);
  iVar3 = 0;
  iVar7 = 2;
  do {
    *(undefined4 *)(&DAT_803b07ac + iVar3 + *(char *)(param_9 + 0x3e4) * 0x38) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07b0 + *(char *)(param_9 + 0x3e4) * 0x38 + iVar3) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07b4 + *(char *)(param_9 + 0x3e4) * 0x38 + iVar3) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07b8 + *(char *)(param_9 + 0x3e4) * 0x38 + iVar3) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07bc + *(char *)(param_9 + 0x3e4) * 0x38 + iVar3) = 0xf0000000;
    *(undefined4 *)(&DAT_803b07c0 + *(char *)(param_9 + 0x3e4) * 0x38 + iVar3) = 0xf0000000;
    iVar4 = *(char *)(param_9 + 0x3e4) * 0x38 + iVar3;
    iVar3 = iVar3 + 0x1c;
    *(undefined4 *)(&DAT_803b07c4 + iVar4) = 0xf0000000;
    iVar4 = DAT_80436238;
    iVar7 = iVar7 + -1;
  } while (iVar7 != 0);
  iVar7 = DAT_80436238 + 0x270000;
  cVar1 = *param_10;
  bVar2 = param_10[1];
  *(int *)(&DAT_803b07ac + *(char *)(param_9 + 0x3e4) * 0x38) =
       iVar7 + *(char *)(param_9 + 0x3e4) * 0x800 + -0x7400;
  uVar6 = 0x58000;
  iVar3 = param_11 * 4;
  *(int *)(&DAT_803b07b4 + *(char *)(param_9 + 0x3e4) * 0x38) =
       iVar4 + *(char *)(param_9 + 0x3e4) * 0x2000 + 0x703c00;
  puVar5 = (&PTR_DAT_802d0584)[cVar1];
  *(int *)(&DAT_803b07b8 + *(char *)(param_9 + 0x3e4) * 0x38) =
       iVar4 + *(char *)(param_9 + 0x3e4) * 0x6c000 + 0x47bc00;
  *(undefined4 *)(&DAT_803b07d0 + *(char *)(param_9 + 0x3e4) * 0x38) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07cc + *(char *)(param_9 + 0x3e4) * 0x38) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07c8 + *(char *)(param_9 + 0x3e4) * 0x38) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07c4 + *(char *)(param_9 + 0x3e4) * 0x38) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07c0 + *(char *)(param_9 + 0x3e4) * 0x38) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07bc + *(char *)(param_9 + 0x3e4) * 0x38) = 0xf0000000;
  iVar4 = *(char *)(param_9 + 0x3e4) * 0x58000;
  *(int *)(&DAT_803b07bc + *(char *)(param_9 + 0x3e4) * 0x38 + iVar3) = iVar7 + iVar4 + -0x4400;
  zz_000b07c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(puVar5 + (uint)bVar2 * 4),&DAT_803b07ac + *(char *)(param_9 + 0x3e4) * 0x38,
              &DAT_803b07bc,(uint)bVar2 * 4,puVar5,iVar4,iVar3,0x58000);
  zz_000a154_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_00412c4_,2,
              (int)*(char *)(param_9 + 0x3e4),(int)param_11,puVar5,iVar4,iVar3,uVar6);
  return;
}



// ==== 80041f18  zz_0041f18_ ====

void zz_0041f18_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,char *param_11,undefined4 param_12,char param_13)

{
  char cVar1;
  byte bVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  undefined *puVar6;
  undefined **ppuVar7;
  undefined *puVar8;
  undefined *puVar9;
  int iVar10;
  void *pvVar11;
  int iVar12;
  undefined8 uVar13;
  
  iVar4 = param_9 * 0xc30;
  iVar3 = param_10 * 0xc30;
  pvVar11 = (void *)(iVar4 + -0x7fc44b40);
  for (iVar12 = 0; iVar12 < *(short *)((int)*(int **)(&DAT_803bbac0 + iVar4) + 0x1a);
      iVar12 = iVar12 + 1) {
    zz_0197ad8_(*(int **)((int)pvVar11 + 0x708));
    zz_0197ad8_(*(int **)((int)pvVar11 + 0x788));
    pvVar11 = (void *)((int)pvVar11 + 4);
  }
  zz_0197ad8_(*(int **)(&DAT_803bbac0 + iVar4));
  *(undefined4 *)(&DAT_803bbac0 + iVar4) = 0;
  zz_004d63c_(param_9);
  pvVar11 = (void *)(iVar3 + -0x7fc44b40);
  for (iVar12 = 0; iVar12 < *(short *)((int)*(int **)(&DAT_803bbac0 + iVar3) + 0x1a);
      iVar12 = iVar12 + 1) {
    zz_0197ad8_(*(int **)((int)pvVar11 + 0x708));
    zz_0197ad8_(*(int **)((int)pvVar11 + 0x788));
    pvVar11 = (void *)((int)pvVar11 + 4);
  }
  zz_0197ad8_(*(int **)(&DAT_803bbac0 + iVar3));
  *(undefined4 *)(&DAT_803bbac0 + iVar3) = 0;
  uVar13 = zz_004d63c_(param_10);
  puVar6 = PTR_DAT_80433934;
  iVar12 = param_9 * 4;
  *(undefined4 *)(&DAT_803c4d94 + iVar12) = 0;
  *(undefined4 *)(puVar6 + iVar12 + 0x80) = 0;
  *(undefined4 *)(&DAT_803c4d7c + iVar12) = 0;
  *(undefined4 *)(&DAT_803bb4a0 + iVar12) = 0;
  gnt4_memset((void *)(iVar4 + -0x7fc44b40),0,0xc30);
  puVar6 = PTR_DAT_80433934;
  iVar4 = param_10 * 4;
  *(undefined4 *)(&DAT_803c4d94 + iVar4) = 0;
  *(undefined4 *)(puVar6 + iVar4 + 0x80) = 0;
  *(undefined4 *)(&DAT_803c4d7c + iVar4) = 0;
  *(undefined4 *)(&DAT_803bb4a0 + iVar4) = 0;
  gnt4_memset((void *)(iVar3 + -0x7fc44b40),0,0xc30);
  iVar4 = param_9 * 0x38;
  iVar3 = param_10 * 0x38;
  *(undefined4 *)(&DAT_803b07ac + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07ac + iVar3) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07b0 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07b0 + iVar3) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07b4 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07b4 + iVar3) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07b8 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07b8 + iVar3) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07bc + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07bc + iVar3) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07c0 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07c0 + iVar3) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07c4 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07c4 + iVar3) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07c8 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07c8 + iVar3) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07cc + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07cc + iVar3) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07d0 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07d0 + iVar3) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07d4 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07d4 + iVar3) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07d8 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07d8 + iVar3) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07dc + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07dc + iVar3) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07e0 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07e0 + iVar3) = 0xf0000000;
  iVar3 = DAT_80436238;
  iVar4 = param_9 * 0x38;
  cVar1 = *param_11;
  bVar2 = param_11[1];
  piVar5 = (int *)(&DAT_803b07ac + iVar4);
  iVar10 = DAT_80436238 + 0x268c00 + param_10 * 0x800;
  *piVar5 = DAT_80436238 + 0x268c00 + param_9 * 0x800;
  iVar12 = param_10 * 0x38;
  *(int *)(&DAT_803b07b0 + iVar4) = iVar10;
  *(int *)(&DAT_803b07ac + iVar12) = iVar10;
  *(int *)(&DAT_803b07b4 + iVar4) = iVar3 + 0x703c00 + param_9 * 0x2000;
  *(int *)(&DAT_803b07b4 + iVar12) = iVar3 + 0x703c00 + param_10 * 0x2000;
  *(int *)(&DAT_803b07b8 + iVar4) = iVar3 + 0x47bc00 + param_9 * 0x6c000;
  iVar10 = param_13 + 4;
  *(int *)(&DAT_803b07b8 + iVar12) = iVar3 + 0x47bc00 + param_10 * 0x6c000;
  *(undefined4 *)(&DAT_803b07d0 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07cc + iVar4) = 0xf0000000;
  puVar8 = &DAT_803b07c8;
  puVar9 = &DAT_803b07c4;
  *(undefined4 *)(&DAT_803b07c8 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07c4 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07c0 + iVar4) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07bc + iVar4) = 0xf0000000;
  piVar5[iVar10] = iVar3 + 0x26bc00 + param_9 * 0x58000;
  *(undefined4 *)(&DAT_803b07d0 + iVar12) = 0xf0000000;
  ppuVar7 = &PTR_DAT_802d0584;
  *(undefined4 *)(&DAT_803b07cc + iVar12) = 0xf0000000;
  puVar6 = (&PTR_DAT_802d0584)[cVar1];
  *(undefined4 *)(&DAT_803b07c8 + iVar12) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07c4 + iVar12) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07c0 + iVar12) = 0xf0000000;
  *(undefined4 *)(&DAT_803b07bc + iVar12) = 0xf0000000;
  *(int *)((int)(&DAT_803b07ac + iVar12) + iVar10 * 4) = iVar3 + 0x26bc00 + param_10 * 0x58000;
  zz_000b07c_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(puVar6 + (uint)bVar2 * 4),piVar5,(uint)bVar2 * 4,puVar6,iVar12,
              &PTR_DAT_802d0584,&DAT_803b07c8,&DAT_803b07c4);
  uVar13 = zz_000a154_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80041470,3
                       ,param_9,param_10,2,ppuVar7,puVar8,puVar9);
  uVar13 = zz_000a154_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80041470,3
                       ,param_9,param_10,3,ppuVar7,puVar8,puVar9);
  uVar13 = zz_000a154_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80041470,3
                       ,param_9,param_10,iVar10,ppuVar7,puVar8,puVar9);
  zz_000a154_(uVar13,param_2,param_3,param_4,param_5,param_6,param_7,param_8,FUN_80041364,3,param_9,
              param_10,iVar10,ppuVar7,puVar8,puVar9);
  return;
}



// ==== 800422d8  zz_00422d8_ ====

undefined4 zz_00422d8_(int param_1)

{
  if (*(int *)(&DAT_803bbac0 + param_1 * 0xc30) == 0) {
    return 0;
  }
  return 1;
}



// ==== 80042300  zz_0042300_ ====

void zz_0042300_(void)

{
  zz_004be08_(DAT_80436254);
  return;
}



// ==== 80042324  zz_0042324_ ====

void zz_0042324_(undefined4 *param_1)

{
  gnt4_memset(&DAT_803bb470,0,0x30);
  DAT_803bb474 = *param_1;
  *(undefined4 *)PTR_DAT_80433954 = param_1[1];
  *(undefined4 *)(PTR_DAT_80433954 + 4) = param_1[2];
  *(undefined4 *)(PTR_DAT_80433954 + 8) = param_1[3];
  return;
}



// ==== 80042394  zz_0042394_ ====

void zz_0042394_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  
  uVar2 = 0;
  DAT_803b078c = DAT_80436238 + 0x81c400;
  DAT_803b0794 = 0;
  DAT_803b0790 = DAT_80436238 + 0x70fc00;
  DAT_803b0798 = 0;
  if (param_9 == 0) {
    puVar1 = PTR_DAT_80433934;
    zz_000b07c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(&DAT_802d05c4 +
                        (char)PTR_DAT_80433934[0x1c] * 4 + (char)PTR_DAT_80433934[0x1d] * 0x48),
                &DAT_803b078c,(char)PTR_DAT_80433934[0x1d] * 0x48,PTR_DAT_80433934,0,in_r8,in_r9,
                in_r10);
    zz_000a154_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_0042324_,1,
                &DAT_803b078c,puVar1,uVar2,in_r8,in_r9,in_r10);
  }
  else {
    zz_00188d4_(0xab4800,&DAT_803b078c);
    zz_0042324_(&DAT_803b078c);
  }
  return;
}



// ==== 80042454  zz_0042454_ ====

void zz_0042454_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar2;
  
  iVar2 = DAT_80436238 + 0x655400;
  iVar1 = zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(&DAT_802d05c4 +
                              (char)PTR_DAT_80433934[0x1c] * 4 + (char)PTR_DAT_80433934[0x1d] * 0x48
                              ),iVar2,DAT_80436238,PTR_DAT_80433934,in_r7,in_r8,in_r9,in_r10);
  zz_000b1a0_(iVar2,0xab4800,iVar1);
  return;
}



// ==== 800424cc  zz_00424cc_ ====

void zz_00424cc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined8 uVar1;
  
  DAT_803bb470 = zz_0197a0c_(1);
  uVar1 = zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)DAT_803bb470,DAT_803bb474,param_11,param_12,param_13,param_14,param_15,
                      param_16);
  uVar1 = zz_0008a94_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)DAT_803bb470,extraout_r4,param_11,param_12,param_13,param_14,param_15,
                      param_16);
  zz_0008ca8_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_803bb470,
              extraout_r4_00,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 80042520  zz_0042520_ ====

void zz_0042520_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  
  cVar1 = PTR_DAT_80433930[0x29];
  iVar2 = DAT_80436238 + 0x8cc400;
  if (cVar1 == '\x02') {
    param_9 = 0xa95;
    goto LAB_80042584;
  }
  if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      param_9 = 0xa93;
      goto LAB_80042584;
    }
    if (cVar1 < '\0') goto LAB_80042584;
  }
  else if ('\x03' < cVar1) goto LAB_80042584;
  param_9 = 0xa94;
LAB_80042584:
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar2,
              DAT_80436238,param_12,param_13,param_14,param_15,param_16);
  gnt4_memset(&DAT_804361fc,0,8);
  iRam80436200 = iVar2;
  return;
}



// ==== 800425b8  zz_00425b8_ ====

void zz_00425b8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined4 param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  DAT_804361fc = zz_0197a0c_(1);
  uVar1 = zz_0040eb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int)DAT_804361fc,puRam80436200,param_11,param_12,param_13,param_14,param_15,
                      param_16);
  zz_0008b90_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)DAT_804361fc,
              extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800425f4  zz_00425f4_ ====

void zz_00425f4_(void)

{
  return;
}



// ==== 800425f8  zz_00425f8_ ====

void zz_00425f8_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  
  cVar1 = PTR_DAT_80433930[0x29];
  iVar2 = DAT_80436238 + 0x8cc400;
  if (cVar1 == '\x02') {
    param_9 = 0xa97;
    goto LAB_8004265c;
  }
  if (cVar1 < '\x02') {
    if (cVar1 == '\0') {
      param_9 = 0xa97;
      goto LAB_8004265c;
    }
    if (cVar1 < '\0') goto LAB_8004265c;
  }
  else if ('\x03' < cVar1) goto LAB_8004265c;
  param_9 = 0xa97;
LAB_8004265c:
  zz_000af84_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar2,
              DAT_80436238,param_12,param_13,param_14,param_15,param_16);
  gnt4_memset(&DAT_804361fc,0,8);
  iRam80436200 = iVar2;
  return;
}



