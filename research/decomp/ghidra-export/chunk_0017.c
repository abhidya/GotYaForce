// ==== 800ab840  zz_00ab840_ ====

void zz_00ab840_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  zz_0016f58_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800ab860  zz_00ab860_ ====

void zz_00ab860_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  FUN_800173a0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
               param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800ab880  FUN_800ab880 ====

/* WARNING: Removing unreachable block (ram,0x800abb1c) */
/* WARNING: Removing unreachable block (ram,0x800ab890) */

void FUN_800ab880(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,uint param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  undefined4 extraout_r4;
  short sVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  short sVar9;
  int iVar10;
  float *pfVar11;
  int iVar12;
  int iVar13;
  undefined8 uVar14;
  double dVar15;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(*(int *)(param_9 + 0x90) + 1000);
    *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(*(int *)(param_9 + 0x90) + 0x3e4);
    *(undefined2 *)(param_9 + 0x17a) = 0;
    *(undefined1 *)(param_9 + 0x182) = 0;
    *(undefined1 *)(param_9 + 0x186) = 0;
    *(undefined2 *)(param_9 + 0x17c) = 0;
    *(undefined1 *)(param_9 + 0x183) = 0;
    *(undefined1 *)(param_9 + 0x187) = 0;
    *(undefined2 *)(param_9 + 0x17e) = 0;
    *(undefined1 *)(param_9 + 0x184) = 0;
    *(undefined1 *)(param_9 + 0x188) = 0;
    *(undefined2 *)(param_9 + 0x180) = 0;
    *(undefined1 *)(param_9 + 0x185) = 0;
    *(undefined1 *)(param_9 + 0x189) = 0;
    *(undefined1 *)(param_9 + 0x18a) = 0;
  }
  iVar6 = (&DAT_803c4e84)[*(char *)(param_9 + 0x96)];
  if (((uint)(byte)PTR_DAT_80433934[0x15d9] & 1 << (int)*(char *)(param_9 + 0x96)) == 0) {
    *(undefined1 *)(param_9 + 0x170) = 0;
  }
  else {
    pfVar11 = (float *)(param_9 + 0x144);
    iVar7 = 0;
    iVar13 = 2;
    pfVar5 = pfVar11;
    do {
      iVar3 = param_9 + iVar7;
      if (*(char *)(iVar3 + 0x186) != '\0') {
        *(char *)(iVar3 + 0x186) = *(char *)(iVar3 + 0x186) + -1;
      }
      sVar4 = *(short *)(iVar6 + 0x4f4);
      if (sVar4 != *(short *)((int)pfVar5 + 0x36)) {
        *(short *)((int)pfVar5 + 0x36) = sVar4;
        if (sVar4 == 0) {
          *(byte *)(param_9 + 0x18a) = *(byte *)(param_9 + 0x18a) & ~(byte)(1 << iVar7);
        }
        else {
          param_12 = 1 << iVar7;
          if (((*(byte *)(param_9 + 0x18a) & param_12) == 0) || (*(char *)(iVar3 + 0x186) == '\0'))
          {
            *(undefined1 *)(iVar3 + 0x186) = 8;
          }
          *(byte *)(param_9 + 0x18a) = *(byte *)(param_9 + 0x18a) | (byte)param_12;
        }
      }
      pfVar5 = (float *)((int)pfVar5 + 2);
      iVar6 = iVar6 + 2;
      iVar7 = iVar7 + 1;
      iVar13 = iVar13 + -1;
    } while (iVar13 != 0);
    iVar13 = 0;
    *(undefined1 *)(param_9 + 0x170) = 0;
    if (*(char *)(param_9 + 0x18a) != '\0') {
      iVar3 = 0;
      *(undefined1 *)(param_9 + 0x170) = 1;
      do {
        if (((uint)*(byte *)(param_9 + 0x18a) & 1 << iVar3) != 0) {
          sVar4 = *(short *)((int)pfVar11 + 0x36);
          if (1000 < sVar4) {
            sVar4 = 999;
            *(undefined2 *)((int)pfVar11 + 0x36) = 999;
          }
          iVar12 = param_9 + iVar3;
          iVar10 = 0;
          *(undefined1 *)(iVar12 + 0x182) = 0;
          iVar8 = iVar13 << 2;
          sVar9 = 100;
          dVar15 = DOUBLE_804381c0;
          do {
            uVar2 = (int)sVar4 / (int)sVar9;
            if (((uVar2 != 0) && (*(char *)(iVar12 + 0x182) == '\0')) ||
               ((*(char *)(iVar12 + 0x182) == '\0' && (sVar9 == 1)))) {
              *(char *)(iVar12 + 0x182) = '\x03' - (char)iVar10;
            }
            if (9 < (int)uVar2) {
              uVar2 = 9;
            }
            uVar14 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) -
                                                dVar15),param_2,param_3,param_4,param_5,param_6,
                                 param_7,param_8,DAT_804361fc,*(int *)(param_9 + iVar8 + 0x148),
                                 pfVar5,param_12,iVar6,iVar7,param_15,param_16);
            zz_0007c30_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + iVar8 + 0x148),extraout_r4,pfVar5,param_12,iVar6,iVar7,
                        param_15,param_16);
            pfVar5 = (float *)(int)sVar4;
            iVar10 = iVar10 + 1;
            iVar8 = iVar8 + 4;
            sVar1 = (sVar4 / sVar9) * sVar9;
            sVar9 = (short)((uint)(int)sVar9 / 10);
            sVar4 = sVar4 - sVar1;
          } while (iVar10 < 3);
        }
        iVar3 = iVar3 + 1;
        iVar13 = iVar13 + 4;
        pfVar11 = (float *)((int)pfVar11 + 2);
      } while (iVar3 < 2);
    }
    *(undefined1 *)(param_9 + 0x172) = 0;
  }
  return;
}



// ==== 800abb38  zz_00abb38_ ====

void zz_00abb38_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  zz_0012638_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800abb58  zz_00abb58_ ====

void zz_00abb58_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,uint param_12,undefined4 param_13,int param_14,undefined4 param_15,
                undefined4 param_16)

{
  if (*(char *)(param_9 + 0x171) == '\0') {
    param_11 = *(float **)(param_9 + 0x90);
    if ((*(char *)(param_11 + 6) == '\x01') &&
       (((*(short *)(param_9 + 0x94) != *(short *)(param_11 + 0xfa) ||
         (*(char *)(param_9 + 0x96) != *(char *)(param_11 + 0xf9))) ||
        (*(char *)(param_9 + 0x174) != *(char *)((int)param_11 + 0x491))))) {
      *(undefined1 *)(param_9 + 0x172) = 0xff;
      *(float **)(param_9 + 0x90) = param_11;
      *(undefined2 *)(param_9 + 0x94) = *(undefined2 *)(param_11 + 0xfa);
      *(undefined1 *)(param_9 + 0x96) = *(undefined1 *)(param_11 + 0xf9);
      *(undefined1 *)(param_9 + 0x174) = *(undefined1 *)((int)param_11 + 0x491);
    }
    if (*(short *)(param_9 + 0x94) < 0) {
      return;
    }
    if (*(char *)(param_9 + 0x96) < '\0') {
      return;
    }
  }
  switch(*(undefined1 *)(param_9 + 0x11)) {
  case 0:
    zz_00abb38_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 2:
    FUN_80012e74(param_9,-0x7fd06b40,param_11,param_12,param_13,param_14,param_15,param_16);
    break;
  case 5:
    FUN_800aa2d0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                 &switchD_800abc24::switchdataD_802f9fd4,param_11,param_12,param_13,param_14,
                 param_15,param_16);
    break;
  case 6:
    FUN_800aa664(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                 &switchD_800abc24::switchdataD_802f9fd4,param_11,param_12,param_13,param_14,
                 param_15,param_16);
    break;
  case 7:
    zz_00ab334_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 8:
    zz_00ab6a0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                &switchD_800abc24::switchdataD_802f9fd4,param_11,param_12,param_13,param_14,param_15
                ,param_16);
    break;
  case 9:
    zz_00ab6c0_(param_9);
    break;
  case 10:
    zz_00ab6e0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                &switchD_800abc24::switchdataD_802f9fd4,param_11,param_12,param_13,param_14,param_15
                ,param_16);
    break;
  case 0xb:
    FUN_800ab880(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                 &switchD_800abc24::switchdataD_802f9fd4,param_11,param_12,param_13,param_14,
                 param_15,param_16);
    break;
  case 0xe:
    zz_00ab700_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 0xf:
    zz_00ab840_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    break;
  case 0x10:
    zz_00ab860_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                &switchD_800abc24::switchdataD_802f9fd4,param_11,param_12,param_13,param_14,param_15
                ,param_16);
  }
  return;
}



// ==== 800abcb0  FUN_800abcb0 ====

void FUN_800abcb0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9,
                 undefined4 param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13,
                 undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  int iVar1;
  undefined4 *puVar2;
  
  iVar1 = 0;
  puVar2 = (undefined4 *)(param_9 + 0x144);
  do {
    if ((int *)*puVar2 != (int *)0x0) {
      param_1 = zz_0006d80_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                            (int *)*puVar2,param_10,param_11,param_12,param_13,param_14,param_15,
                            param_16);
      param_10 = extraout_r4;
    }
    iVar1 = iVar1 + 1;
    puVar2 = puVar2 + 1;
  } while (iVar1 < 8);
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800abd18  zz_00abd18_ ====

void zz_00abd18_(int param_1,undefined4 param_2,undefined4 param_3,int param_4,int param_5,
                undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  double dVar10;
  double dVar11;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_68;
  float local_64;
  float local_60;
  float afStack_5c [13];
  undefined4 local_28;
  uint uStack_24;
  
  cVar1 = *(char *)(param_1 + 400);
  iVar7 = (int)*(char *)(param_1 + 0x12);
  if ((double)FLOAT_80438208 < (double)*(float *)(param_1 + 0x17c)) {
    iVar6 = *(int *)(param_1 + 0x144);
    zz_020b520_((double)*(float *)(param_1 + 0x17c),(double)FLOAT_80438178,(double)FLOAT_80438178,
                (float *)(param_1 + 0x114),afStack_5c);
    param_5 = iVar7 * 8;
    dVar11 = (double)FLOAT_8043815c;
    param_4 = *(char *)(param_1 + 0x173) * 0x10 + -0x7fd05fe8;
    puVar4 = (undefined *)(param_4 + param_5);
    dVar10 = (double)*(float *)(puVar4 + 4);
    uVar9 = zz_020b4ac_((double)*(float *)(param_4 + param_5),dVar10,dVar11,afStack_5c,afStack_5c);
    zz_00076d0_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,iVar6,afStack_5c,puVar4,param_4,
                param_5,param_6,param_7,param_8);
    iVar2 = zz_00a97b4_(*(int *)(iVar6 + 0x14));
    zz_0009958_(iVar6,iVar2);
  }
  if (*(int *)(param_1 + 0x184) != *(int *)(PTR_DAT_80433934 + cVar1 * 0x3c + 0x118)) {
    iVar2 = *(int *)(param_1 + 0x148);
    local_60 = FLOAT_8043815c;
    local_64 = FLOAT_8043815c;
    zz_020b520_((double)(*(float *)(param_1 + 0x180) - *(float *)(param_1 + 0x17c)),
                (double)FLOAT_80438178,(double)FLOAT_80438178,(float *)(param_1 + 0x114),afStack_5c)
    ;
    if (iVar7 == 0) {
      param_4 = 0;
      puVar4 = (undefined *)(int)*(char *)(param_1 + 0x173);
      dVar10 = (double)*(float *)((int)puVar4 * 0x10 + -0x7fd05fe4);
      dVar11 = (double)FLOAT_8043815c;
      uVar9 = zz_020b4ac_((double)(FLOAT_8043820c * *(float *)(param_1 + 0x17c) +
                                  *(float *)((int)puVar4 * 0x10 + -0x7fd05fe8)),dVar10,dVar11,
                          afStack_5c,afStack_5c);
    }
    else {
      param_4 = iVar7 * 8;
      puVar4 = (undefined *)(int)*(char *)(param_1 + 0x173);
      iVar6 = (int)puVar4 * 0x10 + -0x7fd05fe8;
      dVar10 = (double)*(float *)(iVar6 + param_4 + 4);
      dVar11 = (double)FLOAT_8043815c;
      uVar9 = zz_020b4ac_(-(double)(FLOAT_8043820c * *(float *)(param_1 + 0x17c) -
                                   *(float *)(iVar6 + param_4)),dVar10,dVar11,afStack_5c,afStack_5c)
      ;
    }
    zz_00076d0_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,iVar2,afStack_5c,puVar4,param_4,
                param_5,param_6,param_7,param_8);
    iVar6 = zz_00a97b4_(*(int *)(iVar2 + 0x14));
    zz_0009958_(iVar2,iVar6);
  }
  iVar2 = *(int *)(param_1 + 0xe0);
  if (iVar7 == 0) {
    local_68 = FLOAT_8043820c * *(float *)(param_1 + 0x180) +
               *(float *)(*(char *)(param_1 + 0x173) * 0x10 + -0x7fd05fe8);
    if (*(char *)(param_1 + 0x173) == '\0') {
      local_64 = FLOAT_80438210;
    }
    else {
      local_64 = FLOAT_80438214;
    }
  }
  else {
    local_68 = -(FLOAT_8043820c * *(float *)(param_1 + 0x180) -
                *(float *)(*(char *)(param_1 + 0x173) * 0x10 + -0x7fd05fe8 + iVar7 * 8));
    if (*(char *)(param_1 + 0x173) == '\0') {
      local_64 = FLOAT_80438218;
    }
    else {
      local_64 = FLOAT_8043821c;
    }
  }
  pfVar5 = &local_68;
  local_60 = FLOAT_804381f0;
  gnt4_PSVECAdd_bl(pfVar5,(float *)(param_1 + 0x20),pfVar5);
  dVar10 = (double)local_64;
  dVar11 = (double)local_60;
  uVar9 = gnt4_PSMTXTrans_bl((double)local_68,dVar10,dVar11,afStack_5c);
  zz_00076d0_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,iVar2,afStack_5c,(undefined *)pfVar5
              ,param_4,param_5,param_6,param_7,param_8);
  iVar6 = zz_00a97b4_(*(int *)(iVar2 + 0x14));
  zz_0009958_(iVar2,iVar6);
  iVar2 = iVar7 * 0xc;
  dVar11 = (double)FLOAT_8043815c;
  dVar10 = (double)*(float *)(&DAT_802fa03c + iVar2);
  uVar9 = zz_020b4ac_((double)*(float *)(&DAT_802fa038 + iVar2),dVar11,dVar10,afStack_5c,afStack_5c)
  ;
  if (iVar7 == 1) {
    param_4 = 0x43300000;
    dVar11 = (double)FLOAT_8043815c;
    uStack_24 = (int)*(char *)(param_1 + 0x1b) ^ 0x80000000;
    pfVar5 = (float *)0x802fa044;
    local_28 = 0x43300000;
    dVar10 = dVar11;
    in_f4 = DOUBLE_804381c0;
    uVar9 = zz_020b4ac_(-(double)((float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_804381c0)
                                 * fRam802fa04c),dVar11,dVar11,afStack_5c,afStack_5c);
  }
  iVar6 = param_1 + 0x158;
  iVar7 = 5;
  do {
    iVar8 = *(int *)(iVar6 + 8);
    zz_00076d0_(uVar9,dVar11,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,iVar8,afStack_5c,
                (undefined *)pfVar5,param_4,param_5,param_6,param_7,param_8);
    iVar3 = zz_00a97b4_(*(int *)(iVar8 + 0x14));
    zz_0009958_(iVar8,iVar3);
    dVar11 = (double)FLOAT_8043815c;
    dVar10 = dVar11;
    uVar9 = zz_020b4ac_((double)*(float *)(&DAT_802fa040 + iVar2),dVar11,dVar11,afStack_5c,
                        afStack_5c);
    iVar7 = iVar7 + -1;
    iVar6 = iVar6 + -4;
  } while (-1 < iVar7);
  if (*(char *)(param_1 + 0x12) == '\0') {
    local_68 = FLOAT_80438220;
    local_60 = FLOAT_8043815c;
    if (*(char *)(param_1 + 0x173) == '\0') {
      local_64 = FLOAT_80438224;
    }
    else {
      local_64 = FLOAT_80438228;
    }
    pfVar5 = &local_68;
    uVar9 = gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),pfVar5,pfVar5);
    zz_0007834_(uVar9,dVar11,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe4),&local_68
                ,(char *)pfVar5,param_4,param_5,param_6,param_7,param_8);
    iVar7 = zz_00a97b4_(*(int *)(iVar8 + 0x14));
    zz_0009958_(*(int *)(param_1 + 0xe4),iVar7);
  }
  return;
}



// ==== 800ac104  zz_00ac104_ ====

void zz_00ac104_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  int *piVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  float local_88;
  float local_84;
  float local_80;
  float afStack_7c [12];
  float afStack_4c [13];
  undefined4 local_18;
  uint uStack_14;
  
  dVar7 = (double)FLOAT_804381f8;
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_9 + 0x74) ^ 0x80000000;
  iVar4 = *(int *)(param_9 + 0x15c);
  gnt4_PSMTXRotRad_bl((double)(float)(dVar7 * (double)(float)((double)CONCAT44(0x43300000,uStack_14)
                                                             - DOUBLE_804381c0)),afStack_4c,0x7a);
  pfVar3 = afStack_4c;
  uVar6 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar3,pfVar3);
  zz_00076d0_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,afStack_4c,
              (undefined *)pfVar3,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_00a97b4_(*(int *)(iVar4 + 0x14));
  zz_0009958_(iVar4,iVar1);
  iVar4 = *(int *)(param_9 + 0x160);
  pfVar3 = &local_88;
  local_88 = FLOAT_8043815c;
  local_84 = FLOAT_8043815c;
  local_80 = FLOAT_8043822c;
  uVar6 = gnt4_PSMTXMultVec_bl(afStack_4c,pfVar3,pfVar3);
  zz_0007834_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,&local_88,
              (char *)pfVar3,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_00a97b4_(*(int *)(iVar4 + 0x14));
  zz_0009958_(iVar4,iVar1);
  iVar1 = 0;
  piVar5 = (int *)(param_9 + 0x144);
  do {
    if (-1 < *(int *)(*piVar5 + 0x14)) {
      dVar7 = (double)((float *)piVar5[0xe])[1];
      iVar4 = *(int *)(param_9 + (iVar1 + *(char *)(param_9 + 0x193) * 3) * 4 + 0x144);
      if (*(char *)(param_9 + 0x173) != '\0') {
        dVar7 = (double)(float)(dVar7 + (double)FLOAT_80438230);
      }
      gnt4_PSMTXTrans_bl((double)*(float *)piVar5[0xe],dVar7,(double)FLOAT_80438234,afStack_4c);
      gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_4c,afStack_4c);
      dVar7 = (double)FLOAT_80438238;
      dVar8 = (double)FLOAT_80438178;
      gnt4_PSMTXScale_bl(dVar7,dVar7,dVar8,afStack_7c);
      pfVar3 = afStack_4c;
      uVar6 = gnt4_PSMTXConcat_bl(pfVar3,afStack_7c,pfVar3);
      zz_00076d0_(uVar6,dVar7,dVar8,param_4,param_5,param_6,param_7,param_8,iVar4,afStack_4c,
                  (undefined *)pfVar3,param_12,param_13,param_14,param_15,param_16);
      iVar2 = zz_00a97b4_(*(int *)(iVar4 + 0x14));
      zz_0009958_(iVar4,iVar2);
    }
    iVar1 = iVar1 + 1;
    piVar5 = piVar5 + 1;
  } while (iVar1 < 3);
  return;
}



// ==== 800ac2b8  FUN_800ac2b8 ====

/* WARNING: Removing unreachable block (ram,0x800ac4d0) */
/* WARNING: Removing unreachable block (ram,0x800ac4c8) */
/* WARNING: Removing unreachable block (ram,0x800ac2d0) */
/* WARNING: Removing unreachable block (ram,0x800ac2c8) */

void FUN_800ac2b8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 char *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  undefined4 local_b8;
  float local_b4;
  float local_b0;
  float afStack_ac [12];
  float afStack_7c [13];
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  
  if (*(char *)(param_9 + 0x173) == '\0') {
    iVar3 = *(int *)(param_9 + 0x144);
    local_b8 = *(undefined4 *)(param_9 + 0x120);
    local_b4 = *(float *)(param_9 + 0x130) - FLOAT_80438170;
    local_b0 = *(float *)(param_9 + 0x140);
    zz_0007834_((double)local_b0,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                &local_b8,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar1 = zz_00a97b4_(*(int *)(iVar3 + 0x14));
    zz_0009958_(iVar3,iVar1);
  }
  dVar7 = (double)(FLOAT_8043823c * *(float *)((&DAT_803c4e84)[*(char *)(param_9 + 0x96)] + 0x20));
  local_48 = 0x43300000;
  dVar9 = (double)(float)(dVar7 / (double)*(float *)(DAT_8043625c + 0x38));
  iVar4 = *(int *)(param_9 + 0x148);
  dVar8 = (double)(-(FLOAT_8043823c * *(float *)((&DAT_803c4e84)[*(char *)(param_9 + 0x96)] + 0x28))
                  / *(float *)(DAT_8043625c + 0x40));
  uStack_44 = 0x10000U - (int)(short)(&DAT_803c7422)[*(char *)(param_9 + 0x173) * 0x1f2] ^
              0x80000000;
  iVar1 = DAT_8043625c;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_804381f8 *
                              (float)((double)CONCAT44(0x43300000,uStack_44) - DOUBLE_804381c0)),
                      afStack_ac,0x7a);
  gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_ac,afStack_ac);
  dVar6 = (double)FLOAT_80438240;
  gnt4_PSMTXTrans_bl(dVar9,dVar8,dVar6,afStack_7c);
  pfVar2 = afStack_7c;
  uVar5 = gnt4_PSMTXConcat_bl(afStack_ac,pfVar2,pfVar2);
  zz_00076d0_(uVar5,dVar8,dVar6,dVar7,param_5,param_6,param_7,param_8,iVar4,afStack_7c,
              (undefined *)pfVar2,iVar1,param_13,param_14,param_15,param_16);
  iVar3 = zz_00a97b4_(*(int *)(iVar4 + 0x14));
  zz_0009958_(iVar4,iVar3);
  iVar3 = *(int *)(param_9 + 0x14c);
  dVar6 = (double)FLOAT_80438178;
  gnt4_PSMTXTrans_bl((double)FLOAT_8043815c,(double)FLOAT_8043815c,dVar6,afStack_7c);
  gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_7c,afStack_7c);
  local_40 = 0x43300000;
  dVar8 = (double)FLOAT_804381f8;
  uStack_3c = 0x10000U - (int)(short)(&DAT_803c7422)[*(char *)(param_9 + 0x173) * 0x1f2] ^
              0x80000000;
  gnt4_PSMTXRotRad_bl((double)(float)(dVar8 * (double)(float)((double)CONCAT44(0x43300000,uStack_3c)
                                                             - DOUBLE_804381c0)),afStack_ac,0x7a);
  pfVar2 = afStack_7c;
  uVar5 = gnt4_PSMTXConcat_bl(pfVar2,afStack_ac,pfVar2);
  zz_00076d0_(uVar5,dVar8,dVar6,dVar7,param_5,param_6,param_7,param_8,iVar3,afStack_7c,
              (undefined *)pfVar2,iVar1,param_13,param_14,param_15,param_16);
  iVar1 = zz_00a97b4_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  return;
}



// ==== 800ac4f4  FUN_800ac4f4 ====

/* WARNING: Removing unreachable block (ram,0x800ac81c) */
/* WARNING: Removing unreachable block (ram,0x800ac814) */
/* WARNING: Removing unreachable block (ram,0x800ac50c) */
/* WARNING: Removing unreachable block (ram,0x800ac504) */

void FUN_800ac4f4(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  undefined4 *puVar5;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  uint uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int *piVar12;
  int *piVar13;
  undefined8 uVar14;
  double dVar15;
  double dVar16;
  float afStack_b8 [12];
  float afStack_88 [12];
  undefined4 local_58;
  uint uStack_54;
  undefined4 local_50;
  uint uStack_4c;
  
  puVar5 = &DAT_803c4e84;
  iVar6 = (int)*(char *)(param_9 + 0x96);
  local_58 = 0x43300000;
  iVar9 = (&DAT_803c4e84)[iVar6];
  dVar15 = (double)FLOAT_804381f8;
  uStack_54 = (int)(short)(*(short *)(iVar9 + 0x72) -
                          (&DAT_803c7422)[*(char *)(param_9 + 0x173) * 0x1f2]) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(float)(dVar15 * (double)(float)((double)CONCAT44(0x43300000,uStack_54
                                                                               ) - DOUBLE_804381c0))
                      ,afStack_88,0x7a);
  pfVar3 = afStack_88;
  uVar14 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar3,pfVar3);
  iVar7 = *(int *)(param_9 + 0x158);
  zz_00076d0_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,afStack_88,
              (undefined *)pfVar3,puVar5,iVar6,in_r8,in_r9,in_r10);
  iVar2 = zz_00a97b4_(*(int *)(iVar7 + 0x14));
  uVar14 = zz_0009958_(iVar7,iVar2);
  iVar7 = *(int *)(param_9 + 0x15c);
  zz_00076d0_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,afStack_88,
              (undefined *)pfVar3,puVar5,iVar6,in_r8,in_r9,in_r10);
  iVar2 = zz_00a97b4_(*(int *)(iVar7 + 0x14));
  uVar14 = zz_0009958_(iVar7,iVar2);
  iVar2 = 0;
  cVar1 = *(char *)(iVar9 + 0x88);
  uVar8 = 1 << (int)*(char *)(iVar9 + 0x3e4) & 0xff;
  piVar13 = &DAT_803c4e6c;
  piVar12 = (int *)(param_9 + 0x144);
  iVar7 = 0;
  while ((iVar7 < DAT_80436260 && (iVar2 < 5))) {
    iVar10 = *piVar13;
    if (((uVar8 & 1 << (int)*(char *)(iVar10 + 0x3e4)) == 0) && (*(char *)(iVar10 + 0x18) == '\x01')
       ) {
      iVar11 = *piVar12;
      if (*(char *)(iVar10 + 0x88) == cVar1) {
        iVar4 = 0xb;
      }
      else if (*(char *)(iVar10 + 0x88) == '\x02') {
        iVar4 = 0xd;
      }
      else {
        iVar4 = 0xc;
      }
      zz_0006fb4_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,DAT_804361fc,iVar11,
                  iVar4,puVar5,iVar6,in_r8,in_r9,in_r10);
      param_4 = (double)(FLOAT_8043823c * -(*(float *)(iVar10 + 0x20) - *(float *)(iVar9 + 0x20)));
      dVar16 = (double)(float)(param_4 / (double)*(float *)(DAT_8043625c + 0x38));
      local_58 = 0x43300000;
      uStack_54 = (int)(short)-(&DAT_803c7422)[*(char *)(param_9 + 0x173) * 0x1f2] ^ 0x80000000;
      dVar15 = (double)((FLOAT_8043823c * (*(float *)(iVar10 + 0x28) - *(float *)(iVar9 + 0x28))) /
                       *(float *)(DAT_8043625c + 0x40));
      gnt4_PSMTXRotRad_bl((double)(FLOAT_804381f8 *
                                  (float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_804381c0))
                          ,afStack_b8,0x7a);
      gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_b8,afStack_b8);
      param_3 = (double)FLOAT_80438240;
      gnt4_PSMTXTrans_bl(dVar16,dVar15,param_3,afStack_88);
      gnt4_PSMTXConcat_bl(afStack_b8,afStack_88,afStack_b8);
      iVar6 = *(char *)(param_9 + 0x173) * 0x3e4;
      local_50 = 0x43300000;
      dVar15 = (double)FLOAT_804381f8;
      puVar5 = (undefined4 *)(&DAT_803c73b0 + iVar6);
      uStack_4c = (int)(short)(*(short *)(iVar10 + 0x72) -
                              (&DAT_803c7422)[*(char *)(param_9 + 0x173) * 0x1f2]) ^ 0x80000000;
      gnt4_PSMTXRotRad_bl((double)(float)(dVar15 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                    uStack_4c) -
                                                                  DOUBLE_804381c0)),afStack_88,0x7a)
      ;
      pfVar3 = afStack_88;
      uVar14 = gnt4_PSMTXConcat_bl(afStack_b8,pfVar3,pfVar3);
      zz_00076d0_(uVar14,dVar15,param_3,param_4,param_5,param_6,param_7,param_8,iVar11,afStack_88,
                  (undefined *)pfVar3,puVar5,iVar6,in_r8,in_r9,in_r10);
      iVar4 = zz_00a97b4_(*(int *)(iVar11 + 0x14));
      uVar14 = zz_0009958_(iVar11,iVar4);
      piVar12 = piVar12 + 1;
      iVar2 = iVar2 + 1;
      uVar8 = uVar8 | 1 << (int)*(char *)(iVar10 + 0x3e4) & 0xffU;
    }
    piVar13 = piVar13 + 1;
    iVar7 = iVar7 + 1;
  }
  return;
}



// ==== 800ac838  FUN_800ac838 ====

void FUN_800ac838(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,int param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    FUN_800aa2d0(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 param_11,param_12,param_13,param_14,param_15,param_16);
  }
  uVar1 = zz_0010514_((int)*(char *)(param_9 + 0x96));
  if ((uVar1 == 0) && (*(char *)(param_9 + 0x170) != '\0')) {
    if (*(char *)(param_9 + 0x17a) == '\0') {
      piVar5 = (int *)(param_9 + 0x144);
      iVar6 = param_9;
      for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x17b); iVar3 = iVar3 + 1) {
        if (iVar3 < 8) {
          iVar4 = *piVar5;
        }
        else {
          iVar4 = *(int *)(iVar6 + 0xc0);
        }
        iVar2 = zz_00a97b4_(*(int *)(iVar4 + 0x14));
        zz_0009958_(iVar4,iVar2);
        iVar6 = iVar6 + 4;
        piVar5 = piVar5 + 1;
      }
    }
    else {
      iVar3 = *(int *)(param_9 + 0x144);
      iVar6 = zz_00a97b4_(*(int *)(iVar3 + 0x14));
      zz_0009958_(iVar3,iVar6);
    }
  }
  return;
}



// ==== 800ac90c  FUN_800ac90c ====

void FUN_800ac90c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  undefined8 uVar8;
  double dVar9;
  float afStack_78 [12];
  float afStack_48 [12];
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    FUN_800aa664(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 param_11,param_12,param_13,param_14,param_15,param_16);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    dVar7 = (double)FLOAT_8043815c;
    iVar5 = *(int *)(param_9 + 0xe0);
    dVar9 = (double)FLOAT_80438244;
    gnt4_PSMTXTrans_bl(dVar7,dVar7,dVar9,afStack_48);
    pfVar4 = afStack_48;
    uVar8 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar4,pfVar4);
    zz_00076d0_(uVar8,dVar7,dVar9,param_4,param_5,param_6,param_7,param_8,iVar5,afStack_48,
                (undefined *)pfVar4,param_12,param_13,param_14,param_15,param_16);
    iVar3 = zz_00a97b4_(*(int *)(iVar5 + 0x14));
    zz_0009958_(iVar5,iVar3);
    cVar1 = *(char *)(param_9 + 0x1a2);
    iVar5 = (int)*(short *)(param_9 + 0x196);
    for (iVar3 = iVar5; 0 < iVar3; iVar3 = iVar3 + -1) {
      iVar2 = iVar5 - iVar3;
      iVar6 = *(int *)(param_9 + ((((-(int)cVar1 | (int)cVar1) >> 0x1f & 4U) + iVar5) - iVar3) * 4 +
                      0x144);
      gnt4_PSMTXTrans_bl((double)(float)(&DAT_802f9568)[iVar2 * 3],
                         (double)(float)(&DAT_802f956c)[iVar2 * 3],
                         (double)(float)(&DAT_802f9570)[iVar2 * 3],afStack_48);
      gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_48,afStack_48);
      dVar7 = (double)FLOAT_80438248;
      dVar9 = (double)FLOAT_80438178;
      gnt4_PSMTXScale_bl(dVar7,dVar7,dVar9,afStack_78);
      pfVar4 = afStack_48;
      uVar8 = gnt4_PSMTXConcat_bl(pfVar4,afStack_78,pfVar4);
      zz_00076d0_(uVar8,dVar7,dVar9,param_4,param_5,param_6,param_7,param_8,iVar6,afStack_48,
                  (undefined *)pfVar4,param_12,param_13,param_14,param_15,param_16);
      iVar2 = zz_00a97b4_(*(int *)(iVar6 + 0x14));
      zz_0009958_(iVar6,iVar2);
    }
  }
  return;
}



// ==== 800aca5c  FUN_800aca5c ====

void FUN_800aca5c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  int *piVar6;
  undefined8 uVar7;
  undefined4 auStack_a8 [2];
  float local_a0;
  float local_98;
  float local_94;
  float local_90;
  float local_8c;
  float local_88;
  float local_84;
  float afStack_80 [12];
  float afStack_50 [15];
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    param_1 = zz_00ab334_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    iVar4 = 0;
    piVar6 = (int *)(param_9 + 0x144);
    do {
      iVar3 = *piVar6;
      if ((iVar3 != 0) && (*(int *)(iVar3 + 0xc) != 0)) {
        uVar7 = zz_0007bb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                            &local_98,param_11,param_12,param_13,param_14,param_15,param_16);
        uVar7 = zz_0007a60_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                            auStack_a8,param_11,param_12,param_13,param_14,param_15,param_16);
        zz_0007908_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,&local_8c,
                    param_11,param_12,param_13,param_14,param_15,param_16);
        gnt4_PSMTXScale_bl((double)local_98,(double)local_94,(double)local_90,afStack_50);
        gnt4_PSMTXRotRad_bl((double)local_a0,afStack_80,0x7a);
        gnt4_PSMTXConcat_bl(afStack_50,afStack_80,afStack_50);
        param_2 = (double)local_88;
        param_3 = (double)local_84;
        zz_020b4ac_((double)local_8c,param_2,param_3,afStack_50,afStack_50);
        param_11 = afStack_50;
        uVar7 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),param_11,param_11);
        zz_00076d0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_50,
                    (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
        iVar1 = zz_00a97b4_(*(int *)(iVar3 + 0x14));
        param_1 = zz_0009958_(iVar3,iVar1);
      }
      iVar4 = iVar4 + 1;
      piVar6 = piVar6 + 1;
    } while (iVar4 < 8);
    pfVar5 = (float *)&DAT_802f95b8;
    iVar3 = 0;
    iVar4 = param_9;
    while( true ) {
      if (*(short *)(param_9 + 0x17c) <= iVar3) break;
      if (*(char *)(param_9 + 0x180) == '\0') {
        iVar1 = *(int *)(iVar4 + 0xe0);
      }
      else {
        iVar1 = *(int *)(iVar4 + 0xec);
      }
      zz_0007bb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,&local_98,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      gnt4_PSMTXScale_bl((double)local_98,(double)local_94,(double)local_90,afStack_50);
      param_2 = (double)pfVar5[1];
      param_3 = (double)pfVar5[2];
      zz_020b4ac_((double)*pfVar5,param_2,param_3,afStack_50,afStack_50);
      param_11 = afStack_50;
      uVar7 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),param_11,param_11);
      zz_00076d0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,afStack_50,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      iVar2 = zz_00a97b4_(*(int *)(iVar1 + 0x14));
      param_1 = zz_0009958_(iVar1,iVar2);
      iVar4 = iVar4 + 4;
      pfVar5 = pfVar5 + 3;
      iVar3 = iVar3 + 1;
    }
  }
  return;
}



// ==== 800acc1c  FUN_800acc1c ====

/* WARNING: Removing unreachable block (ram,0x800acfe0) */
/* WARNING: Removing unreachable block (ram,0x800acfd8) */
/* WARNING: Removing unreachable block (ram,0x800acc34) */
/* WARNING: Removing unreachable block (ram,0x800acc2c) */

void FUN_800acc1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  float *pfVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int *piVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  undefined8 uVar12;
  double dVar13;
  double dVar14;
  float local_d8;
  float local_d4;
  float local_d0;
  float afStack_cc [12];
  float afStack_9c [13];
  undefined4 local_68;
  uint uStack_64;
  undefined4 local_60;
  uint uStack_5c;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    zz_00ab6a0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  if ((-1 < *(char *)(param_9 + 400)) &&
     (uVar1 = zz_0010514_((int)*(char *)(param_9 + 0x96)), uVar1 == 0)) {
    if (*(char *)(param_9 + 400) == '\0') {
      iVar10 = 0;
      uVar4 = 0x80300000;
      dVar14 = (double)FLOAT_804381f8;
      iVar9 = 0;
      iVar7 = 0;
      iVar11 = param_9 + 0x144;
      iVar5 = 0;
      dVar13 = DOUBLE_804381c0;
      do {
        pfVar3 = &local_d8;
        iVar6 = *(int *)(iVar11 + 8);
        uVar12 = gnt4_PSMTXMultVec_bl
                           ((float *)(param_9 + 0x114),
                            (float *)(*(char *)(param_9 + 0x173) * 0x60 + -0x7fd06944 +
                                      *(char *)(param_9 + 0x12) * 0x18 + iVar10),pfVar3);
        zz_0007834_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,&local_d8,
                    (char *)pfVar3,uVar4,param_13,param_14,param_15,param_16);
        local_68 = 0x43300000;
        uStack_64 = (int)*(short *)(&DAT_802f97bc + *(char *)(param_9 + 0x12) * 4 + iVar9) ^
                    0x80000000;
        zz_0007e74_((double)(float)(dVar14 * (double)(float)((double)CONCAT44(0x43300000,uStack_64)
                                                            - dVar13)),param_2,param_3,param_4,
                    param_5,param_6,param_7,param_8,iVar6,
                    &DAT_802f97bc + *(char *)(param_9 + 0x12) * 4,(char *)pfVar3,uVar4,param_13,
                    param_14,param_15,param_16);
        local_60 = 0x43300000;
        uStack_5c = (int)*(short *)(&DAT_802f97ac + *(char *)(param_9 + 0x12) * 4 + iVar9) ^
                    0x80000000;
        uVar12 = FUN_80007db0((double)(float)(dVar14 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                        uStack_5c) -
                                                                      dVar13)),param_2,param_3,
                              param_4,param_5,param_6,param_7,param_8,iVar6,
                              &DAT_802f97ac + *(char *)(param_9 + 0x12) * 4,(char *)pfVar3,uVar4,
                              param_13,param_14,param_15,param_16);
        local_d8 = *(float *)(param_9 + 0x17c);
        local_d0 = *(float *)(&DAT_802f977c + *(char *)(param_9 + 0x12) * 8 + iVar7);
        local_d4 = local_d8;
        zz_0007ae4_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,&local_d8,
                    &DAT_802f977c + *(char *)(param_9 + 0x12) * 8,uVar4,param_13,param_14,param_15,
                    param_16);
        iVar2 = zz_00a97b4_(*(int *)(iVar6 + 0x14));
        zz_0009958_(iVar6,iVar2);
        iVar5 = iVar5 + 1;
        iVar10 = iVar10 + 0xc;
        iVar9 = iVar9 + 2;
        iVar7 = iVar7 + 4;
        iVar11 = iVar11 + 4;
      } while (iVar5 < 2);
    }
    else {
      iVar10 = 0;
      piVar8 = (int *)(param_9 + 0x144);
      iVar5 = 0;
      iVar7 = 0;
      iVar9 = 0;
      do {
        if ((iVar10 != 0) || (FLOAT_8043824c <= *(float *)(param_9 + 0x180))) {
          iVar11 = *piVar8;
          pfVar3 = (float *)((int)u_________________802f95de +
                            iVar5 + *(char *)(param_9 + 0x12) * 0x18 +
                                    *(char *)(param_9 + 0x173) * 0x60 + 0x1e);
          gnt4_PSMTXTrans_bl((double)*pfVar3,(double)pfVar3[1],(double)pfVar3[2],afStack_9c);
          gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_9c,afStack_9c);
          local_60 = 0x43300000;
          uStack_5c = (int)*(short *)(&DAT_802f97bc + iVar7 + *(char *)(param_9 + 0x12) * 4) ^
                      0x80000000;
          gnt4_PSMTXRotRad_bl((double)(FLOAT_804381f8 *
                                      (float)((double)CONCAT44(0x43300000,uStack_5c) -
                                             DOUBLE_804381c0)),afStack_cc,0x7a);
          gnt4_PSMTXConcat_bl(afStack_9c,afStack_cc,afStack_9c);
          local_68 = 0x43300000;
          uStack_64 = (int)*(short *)(&DAT_802f979c + iVar7 + *(char *)(param_9 + 0x12) * 4) ^
                      0x80000000;
          gnt4_PSMTXRotRad_bl((double)(FLOAT_804381f8 *
                                      (float)((double)CONCAT44(0x43300000,uStack_64) -
                                             DOUBLE_804381c0)),afStack_cc,0x79);
          gnt4_PSMTXConcat_bl(afStack_9c,afStack_cc,afStack_9c);
          if (iVar10 == 0) {
            iVar2 = *(char *)(param_9 + 0x12) * 0xc;
            local_d0 = FLOAT_80438178;
            local_d8 = *(float *)(&DAT_802f9d6c + iVar2);
            local_d4 = *(float *)(&DAT_802f9d70 + iVar2);
          }
          else {
            local_d8 = *(float *)(param_9 + 0x184);
            local_d4 = *(float *)(param_9 + 0x188);
            local_d0 = *(float *)(param_9 + 0x18c);
          }
          dVar13 = (double)local_d4;
          local_d0 = local_d0 * *(float *)(&DAT_802f977c + iVar9 + *(char *)(param_9 + 0x12) * 8);
          dVar14 = (double)local_d0;
          gnt4_PSMTXScale_bl((double)local_d8,dVar13,dVar14,afStack_cc);
          pfVar3 = afStack_9c;
          uVar12 = gnt4_PSMTXConcat_bl(pfVar3,afStack_cc,pfVar3);
          zz_00076d0_(uVar12,dVar13,dVar14,param_4,param_5,param_6,param_7,param_8,iVar11,afStack_9c
                      ,(undefined *)pfVar3,param_12,param_13,param_14,param_15,param_16);
          iVar2 = zz_00a97b4_(*(int *)(iVar11 + 0x14));
          zz_0009958_(iVar11,iVar2);
        }
        iVar10 = iVar10 + 1;
        iVar5 = iVar5 + 0xc;
        iVar7 = iVar7 + 2;
        iVar9 = iVar9 + 4;
        piVar8 = piVar8 + 1;
      } while (iVar10 < 2);
    }
  }
  return;
}



// ==== 800acffc  zz_00acffc_ ====

void zz_00acffc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_9 + 0x144);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_00a97b4_(*(int *)(iVar2 + 0x14));
  zz_0009958_(iVar2,iVar1);
  return;
}



// ==== 800ad044  zz_00ad044_ ====

void zz_00ad044_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  
  if (PTR_DAT_80433930[0x3d] == '\x01') {
    iVar2 = *(int *)(param_9 + 0x144);
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
    iVar1 = zz_00a97b4_(*(int *)(iVar2 + 0x14));
    zz_0009958_(iVar2,iVar1);
  }
  return;
}



// ==== 800ad09c  zz_00ad09c_ ====

void zz_00ad09c_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    zz_00ab6e0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_9 + 0x74) ^ 0x80000000;
  dVar5 = (double)FLOAT_804381f8;
  iVar3 = *(int *)(param_9 + 0x144);
  gnt4_PSMTXRotRad_bl((double)(float)(dVar5 * (double)(float)((double)CONCAT44(0x43300000,uStack_14)
                                                             - DOUBLE_804381c0)),afStack_48,0x7a);
  pfVar2 = afStack_48;
  uVar4 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_00076d0_(uVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_48,
              (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_00a97b4_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  dVar5 = (double)FLOAT_8043815c;
  iVar3 = *(int *)(param_9 + 0x148);
  dVar6 = (double)FLOAT_804381b0;
  gnt4_PSMTXTrans_bl(dVar5,dVar5,dVar6,afStack_48);
  pfVar2 = afStack_48;
  uVar4 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_00076d0_(uVar4,dVar5,dVar6,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_48,
              (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_00a97b4_(*(int *)(iVar3 + 0x14));
  zz_0009958_(iVar3,iVar1);
  return;
}



// ==== 800ad18c  FUN_800ad18c ====

/* WARNING: Removing unreachable block (ram,0x800ad3d8) */
/* WARNING: Removing unreachable block (ram,0x800ad3d0) */
/* WARNING: Removing unreachable block (ram,0x800ad1a4) */
/* WARNING: Removing unreachable block (ram,0x800ad19c) */

void FUN_800ad18c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,uint param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  float fVar2;
  int iVar3;
  char *pcVar4;
  char **ppcVar5;
  int iVar6;
  uint uVar7;
  uint uVar8;
  undefined *puVar9;
  int iVar10;
  undefined4 *puVar11;
  int *piVar12;
  undefined4 *puVar13;
  double dVar14;
  undefined8 uVar15;
  double dVar16;
  double dVar17;
  char *local_68;
  float local_64;
  float local_60;
  undefined4 local_58;
  uint uStack_54;
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    FUN_800ab880(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                 param_11,param_12,param_13,param_14,param_15,param_16);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    puVar11 = &DAT_802f9dac;
    piVar12 = (int *)(param_9 + 0x144);
    puVar9 = &DAT_802fa050;
    uVar7 = 0;
    iVar10 = 1;
    do {
      if (((uint)*(byte *)(param_9 + 0x18a) & 1 << uVar7) != 0) {
        uStack_54 = uVar7 ^ 0x80000000;
        iVar6 = *piVar12;
        local_58 = 0x43300000;
        pcVar4 = *(char **)(param_9 + 0x20);
        dVar14 = (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_804381c0);
        local_64 = (float)((double)FLOAT_80438250 * dVar14 + (double)*(float *)(param_9 + 0x24));
        local_60 = *(float *)(param_9 + 0x28);
        local_68 = pcVar4;
        zz_0007834_(dVar14,(double)FLOAT_80438250,param_3,param_4,param_5,param_6,param_7,param_8,
                    iVar6,&local_68,pcVar4,param_12,param_13,param_14,param_15,param_16);
        iVar3 = zz_00a97b4_(*(int *)(iVar6 + 0x14));
        zz_0009958_(iVar6,iVar3);
        if ((uVar7 == 1) && (*(char *)(param_9 + 0x183) != '\0')) {
          iVar6 = *(int *)(param_9 + 0xe0);
          uStack_54 = (int)*(char *)(param_9 + 0x183) - 1U ^ 0x80000000;
          local_58 = 0x43300000;
          dVar14 = (double)(float)((double)CONCAT44(0x43300000,uStack_54) - DOUBLE_804381c0);
          dVar16 = (double)(float)local_68;
          local_68 = (char *)(float)(dVar16 + (double)(float)((double)FLOAT_80438258 * dVar14 +
                                                             (double)FLOAT_80438254));
          zz_0007834_(dVar14,dVar16,(double)FLOAT_80438258,param_4,param_5,param_6,param_7,param_8,
                      iVar6,&local_68,pcVar4,param_12,param_13,param_14,param_15,param_16);
          iVar3 = zz_00a97b4_(*(int *)(iVar6 + 0x14));
          zz_0009958_(iVar6,iVar3);
        }
        uStack_54 = uVar7 ^ 0x80000000;
        local_58 = 0x43300000;
        param_3 = (double)FLOAT_80438260;
        dVar17 = (double)FLOAT_80438244;
        dVar16 = (double)(float)(param_3 * (double)(float)((double)CONCAT44(0x43300000,uStack_54) -
                                                          DOUBLE_804381c0) + (double)FLOAT_8043825c)
        ;
        puVar13 = puVar11;
        dVar14 = DOUBLE_804381c0;
        for (uVar8 = 0; (int)uVar8 < (int)*(char *)(param_9 + uVar7 + 0x182); uVar8 = uVar8 + 1) {
          local_68 = (char *)*puVar13;
          iVar3 = *(int *)(param_9 + ((2 - uVar8) + iVar10) * 4 + 0x144);
          local_64 = (float)dVar16;
          local_60 = (float)dVar17;
          bVar1 = *(byte *)(param_9 + uVar7 + 0x186);
          if (bVar1 != 0) {
            fVar2 = *(float *)(puVar9 + (bVar1 & 3) * 4);
            if ((uVar8 & 1) != 0) {
              fVar2 = fVar2 * FLOAT_80438264;
            }
            local_64 = local_64 + fVar2;
          }
          ppcVar5 = &local_68;
          uVar15 = gnt4_PSMTXMultVec_bl
                             ((float *)(param_9 + 0x114),(float *)ppcVar5,(float *)ppcVar5);
          zz_0007834_(uVar15,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,&local_68,
                      (char *)ppcVar5,param_12,param_13,param_14,param_15,param_16);
          iVar6 = zz_00a97b4_(*(int *)(iVar3 + 0x14));
          zz_0009958_(iVar3,iVar6);
          puVar13 = puVar13 + 1;
        }
      }
      uVar7 = uVar7 + 1;
      puVar11 = puVar11 + 3;
      iVar10 = iVar10 + 4;
      puVar9 = puVar9 + 0x10;
      piVar12 = piVar12 + 4;
    } while ((int)uVar7 < 2);
  }
  return;
}



// ==== 800ad3f4  zz_00ad3f4_ ====

void zz_00ad3f4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined *puVar2;
  undefined *puVar3;
  int iVar4;
  undefined8 uVar5;
  double dVar6;
  double dVar7;
  float afStack_38 [12];
  
  iVar4 = *(int *)(param_9 + 0x144);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  iVar1 = zz_00a97b4_(*(int *)(iVar4 + 0x14));
  zz_0009958_(iVar4,iVar1);
  iVar1 = *(int *)(param_9 + 0x148);
  if ((*(int *)(iVar1 + 0x14) != -1) && ('\x02' < *(char *)(param_9 + 0x19))) {
    puVar3 = &DAT_802fa070;
    iVar4 = *(char *)(param_9 + 0x173) * 0xc;
    puVar2 = &DAT_802fa070 + iVar4;
    dVar6 = (double)*(float *)(&DAT_802fa074 + iVar4);
    dVar7 = (double)*(float *)(&DAT_802fa078 + iVar4);
    uVar5 = zz_020b4ac_((double)*(float *)(&DAT_802fa070 + iVar4),dVar6,dVar7,
                        (float *)(param_9 + 0x114),afStack_38);
    zz_00076d0_(uVar5,dVar6,dVar7,param_4,param_5,param_6,param_7,param_8,iVar1,afStack_38,puVar2,
                puVar3,param_13,param_14,param_15,param_16);
    iVar4 = zz_00a97b4_(*(int *)(iVar1 + 0x14));
    zz_0009958_(iVar1,iVar4);
  }
  return;
}



// ==== 800ad4b8  zz_00ad4b8_ ====

void zz_00ad4b8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  float *pfVar4;
  int iVar5;
  int *piVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  float afStack_78 [12];
  float afStack_48 [12];
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    zz_00ab840_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    piVar6 = (int *)(param_9 + 0x144);
    pfVar4 = (float *)&DAT_802fa0d0;
    iVar2 = 0;
    iVar5 = 0;
    do {
      iVar3 = *piVar6;
      if (*(char *)(iVar3 + 0x10) != '\0') {
        pfVar1 = (float *)(&DAT_802fa088 + iVar5 + *(char *)(param_9 + 0x173) * 0x24);
        gnt4_PSMTXTrans_bl((double)*pfVar1,(double)pfVar1[1],(double)pfVar1[2],afStack_48);
        gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_48,afStack_48);
        dVar8 = (double)pfVar4[1];
        dVar9 = (double)pfVar4[2];
        gnt4_PSMTXScale_bl((double)*pfVar4,dVar8,dVar9,afStack_78);
        pfVar1 = afStack_48;
        uVar7 = gnt4_PSMTXConcat_bl(afStack_78,pfVar1,pfVar1);
        zz_00076d0_(uVar7,dVar8,dVar9,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_48,
                    (undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
        zz_0009958_(iVar3,3);
      }
      iVar2 = iVar2 + 1;
      iVar5 = iVar5 + 0xc;
      pfVar4 = pfVar4 + 3;
      piVar6 = piVar6 + 1;
    } while (iVar2 < 3);
  }
  return;
}



// ==== 800ad5b4  zz_00ad5b4_ ====

void zz_00ad5b4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  float afStack_38 [12];
  
  if (*(char *)(param_9 + 0x172) != '\0') {
    param_1 = zz_00ab860_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                          param_10,param_11,param_12,param_13,param_14,param_15,param_16);
  }
  if (*(char *)(param_9 + 0x170) != '\0') {
    iVar3 = *(int *)(param_9 + 0x144);
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                (float *)(param_9 + 0x114),(undefined *)param_11,param_12,param_13,param_14,param_15
                ,param_16);
    iVar1 = zz_00a97b4_(*(int *)(iVar3 + 0x14));
    zz_0009958_(iVar3,iVar1);
    dVar5 = (double)FLOAT_8043815c;
    dVar6 = dVar5;
    gnt4_PSMTXTrans_bl((double)FLOAT_80438268,dVar5,dVar5,afStack_38);
    pfVar2 = afStack_38;
    uVar4 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
    iVar3 = *(int *)(param_9 + 0x148);
    zz_00076d0_(uVar4,dVar5,dVar6,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_38,
                (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    iVar1 = zz_00a97b4_(*(int *)(iVar3 + 0x14));
    zz_0009958_(iVar3,iVar1);
  }
  return;
}



// ==== 800ad66c  FUN_800ad66c ====

void FUN_800ad66c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,uint param_12,int param_13,int param_14,undefined4 param_15,
                 undefined4 param_16)

{
  char cVar1;
  
  if (((*(char *)(param_9 + 0x171) != '\0') ||
      ((((-1 < *(short *)(param_9 + 0x94) && (-1 < *(char *)(param_9 + 0x96))) &&
        (cVar1 = zz_008b290_(), cVar1 == '\0')) &&
       ((PTR_DAT_80433934[0x1833] == '\0' && (PTR_DAT_80433934[0x1832] == '\0')))))) &&
     (PTR_DAT_80433930[0x33] == '\0')) {
    switch(*(undefined1 *)(param_9 + 0x11)) {
    case 0:
      zz_00abd18_(param_9,param_10,param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 2:
      zz_00ac104_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 3:
      FUN_800ac2b8(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   (char *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 4:
      FUN_800ac4f4(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      break;
    case 5:
      FUN_800ac838(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 6:
      FUN_800ac90c(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 7:
      FUN_800aca5c(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 8:
      FUN_800acc1c(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 9:
      zz_00acffc_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 10:
      zz_00ad09c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0xb:
      FUN_800ad18c(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                   param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0xc:
      zz_00ad044_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0xe:
      zz_00ad3f4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  (undefined *)param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0xf:
      zz_00ad4b8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      break;
    case 0x10:
      zz_00ad5b4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                  param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 800ad8c8  FUN_800ad8c8 ====

void FUN_800ad8c8(int param_1)

{
  zz_004f1c4_(param_1);
  zz_00c1b9c_(param_1);
  zz_015091c_(param_1);
  *(undefined1 *)(param_1 + 0x148) = 0;
  *(undefined2 *)(param_1 + 0x144) = 0;
  *(undefined2 *)(param_1 + 0x146) = 0;
  *(undefined1 *)(param_1 + 0x14b) = 0;
  *(undefined1 *)(param_1 + 0x149) = 0;
  *(undefined1 *)(param_1 + 0x14a) = 0;
  zz_00c74ec_(param_1,0x2f);
  return;
}



// ==== 800ad954  FUN_800ad954 ====

void FUN_800ad954(int param_1)

{
  zz_006d520_(param_1,(float *)&DAT_802fa178);
  if (*(short *)(param_1 + 0x146) == 0) {
    if (*(short *)(param_1 + 0x144) < 1) {
      *(undefined2 *)(param_1 + 0x144) = 0;
    }
    else {
      *(short *)(param_1 + 0x144) = *(short *)(param_1 + 0x144) + -0x80;
    }
  }
  else if (*(short *)(param_1 + 0x144) < 0x1400) {
    *(short *)(param_1 + 0x144) = *(short *)(param_1 + 0x144) + 0x100;
  }
  else {
    *(undefined2 *)(param_1 + 0x144) = 0x1400;
  }
  *(short *)(param_1 + 0x1914) = *(short *)(param_1 + 0x1914) + *(short *)(param_1 + 0x144);
  *(short *)(param_1 + 0x191a) = *(short *)(param_1 + 0x191a) + *(short *)(param_1 + 0x144);
  *(short *)(param_1 + 0x1902) = *(short *)(param_1 + 0x1902) - *(short *)(param_1 + 0x144);
  *(short *)(param_1 + 0x1908) = *(short *)(param_1 + 0x1908) - *(short *)(param_1 + 0x144);
  return;
}



// ==== 800ada28  FUN_800ada28 ====

void FUN_800ada28(int param_1)

{
  (*(code *)(&PTR_FUN_802fa1a8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800ada64  FUN_800ada64 ====

void FUN_800ada64(int param_1)

{
  (*(code *)(&PTR_FUN_80433a68)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800ada9c  FUN_800ada9c ====

void FUN_800ada9c(int param_1)

{
  (*(code *)(&PTR_LAB_802fa1b4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800adb08  FUN_800adb08 ====

void FUN_800adb08(int param_1)

{
  bool bVar1;
  
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  *(undefined2 *)(param_1 + 0x146) = 1;
  if ((*(short *)(param_1 + 0x548) < 1) || (bVar1 = zz_00ae45c_(param_1), bVar1)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0;
    *(undefined2 *)(param_1 + 0x54a) = 0;
    *(undefined2 *)(param_1 + 0x54c) = 0;
  }
  return;
}



// ==== 800adb78  FUN_800adb78 ====

void FUN_800adb78(int param_1)

{
  *(undefined2 *)(param_1 + 0x146) = 1;
  zz_00ae45c_(param_1);
  if ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x548) = 1;
  }
  if (*(short *)(param_1 + 0x54a) == 0) {
    *(undefined2 *)(param_1 + 0x54a) = 2;
    *(short *)(param_1 + 0x54c) = *(short *)(param_1 + 0x54c) + 1;
    zz_00ae56c_(param_1);
    if (*(short *)(param_1 + 0x548) == 0) {
      if (9 < *(short *)(param_1 + 0x54c)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined2 *)(param_1 + 0x548) = 0x1e;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x548) = 0;
      if (0x31 < *(short *)(param_1 + 0x54c)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined2 *)(param_1 + 0x548) = 0x1e;
      }
    }
  }
  else {
    *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) + -1;
  }
  return;
}



// ==== 800adc4c  FUN_800adc4c ====

void FUN_800adc4c(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  *(short *)(param_9 + 0x548) = *(short *)(param_9 + 0x548) + -1;
  if (*(short *)(param_9 + 0x548) < 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 800adc9c  FUN_800adc9c ====

void FUN_800adc9c(int param_1)

{
  (*(code *)(&PTR_LAB_802fa1c8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800add08  FUN_800add08 ====

void FUN_800add08(int param_1)

{
  bool bVar1;
  
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  *(undefined2 *)(param_1 + 0x146) = 1;
  if ((*(short *)(param_1 + 0x548) < 1) || (bVar1 = zz_00ae45c_(param_1), bVar1)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0;
    *(undefined2 *)(param_1 + 0x54a) = 0;
    *(undefined2 *)(param_1 + 0x54c) = 0;
  }
  return;
}



// ==== 800add78  FUN_800add78 ====

void FUN_800add78(int param_1)

{
  *(undefined2 *)(param_1 + 0x146) = 1;
  zz_00ae45c_(param_1);
  if ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x548) = 1;
  }
  if (*(short *)(param_1 + 0x54a) == 0) {
    *(undefined2 *)(param_1 + 0x54a) = 2;
    *(short *)(param_1 + 0x54c) = *(short *)(param_1 + 0x54c) + 1;
    zz_00ae56c_(param_1);
    if (*(short *)(param_1 + 0x548) == 0) {
      if (9 < *(short *)(param_1 + 0x54c)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined2 *)(param_1 + 0x548) = 0x1e;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x548) = 0;
      if (0x31 < *(short *)(param_1 + 0x54c)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined2 *)(param_1 + 0x548) = 0x1e;
      }
    }
  }
  else {
    *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) + -1;
  }
  return;
}



// ==== 800ade4c  FUN_800ade4c ====

void FUN_800ade4c(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  *(short *)(param_9 + 0x548) = *(short *)(param_9 + 0x548) + -1;
  if (*(short *)(param_9 + 0x548) < 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 800ade9c  FUN_800ade9c ====

void FUN_800ade9c(int param_1)

{
  (*(code *)(&PTR_FUN_80433a70)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800aded4  FUN_800aded4 ====

void FUN_800aded4(int param_1)

{
  (*(code *)(&PTR_LAB_802fa1dc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800adf28  FUN_800adf28 ====

void FUN_800adf28(int param_1)

{
  if (*(char *)(param_1 + 0x587) == '\x02') {
    *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
    zz_006660c_(param_1);
    FUN_800669d0(param_1,0xc1);
    if (*(short *)(param_1 + 0x548) < 1) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined2 *)(param_1 + 0x548) = 10;
    }
  }
  else {
    zz_00ae400_(param_1);
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 10;
  }
  return;
}



// ==== 800adfb4  FUN_800adfb4 ====

void FUN_800adfb4(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if ((*(short *)(param_1 + 0x548) < 1) || (uVar1 = zz_00ae400_(param_1), uVar1 != 0)) {
    dVar2 = (double)FLOAT_80438270;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 0;
    zz_004beb8_(dVar2,param_1,1,4,0,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800ae034  FUN_800ae034 ====

void FUN_800ae034(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x541) == '\0') {
    *(undefined1 *)(param_1 + 0x541) = 1;
    iVar1 = zz_006dbe0_(param_1,2,1,1);
    if (iVar1 != 0) {
      zz_00b5878_(param_1,*(undefined1 *)(param_1 + 0x14b));
      *(undefined1 *)(param_1 + *(char *)(param_1 + 0x14b) + 0x149) = 1;
      *(char *)(param_1 + 0x14b) = *(char *)(param_1 + 0x14b) + '\x01';
    }
  }
  iVar1 = zz_004cd24_(param_1,1);
  if (iVar1 != 0) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800ae0d8  FUN_800ae0d8 ====

void FUN_800ae0d8(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  if (*(char *)(param_1 + 0x587) == '\x02') {
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800ae118  FUN_800ae118 ====

void FUN_800ae118(int param_1)

{
  float fVar1;
  int iVar2;
  
  (*(code *)(&PTR_LAB_802fa1f0)[*(char *)(param_1 + 0x540)])();
  if (*(char *)(param_1 + 0x587) == '\x02') {
    zz_0067458_((double)FLOAT_80438274,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_80438278;
    if (*(float *)(param_1 + 0x44) < FLOAT_80438278) {
      *(float *)(param_1 + 0x4c) = FLOAT_80438278;
      *(float *)(param_1 + 0x44) = fVar1;
    }
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 != 0) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a750_(param_1,7);
    }
  }
  return;
}



// ==== 800ae1dc  FUN_800ae1dc ====

void FUN_800ae1dc(int param_1)

{
  if (*(char *)(param_1 + 0x587) == '\x02') {
    *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
    zz_006660c_(param_1);
    FUN_800669d0(param_1,0xc1);
    if (*(short *)(param_1 + 0x548) < 1) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined2 *)(param_1 + 0x548) = 10;
    }
  }
  else {
    zz_00ae400_(param_1);
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 10;
  }
  return;
}



// ==== 800ae268  FUN_800ae268 ====

void FUN_800ae268(int param_1)

{
  uint uVar1;
  double dVar2;
  
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if ((*(short *)(param_1 + 0x548) < 1) || (uVar1 = zz_00ae400_(param_1), uVar1 != 0)) {
    dVar2 = (double)FLOAT_80438270;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 0;
    zz_004beb8_(dVar2,param_1,1,4,0,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800ae2e8  FUN_800ae2e8 ====

void FUN_800ae2e8(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  fVar1 = FLOAT_8043827c;
  if (*(char *)(param_1 + 0x541) == '\0') {
    *(undefined1 *)(param_1 + 0x541) = 1;
    fVar3 = FLOAT_80438284;
    fVar2 = FLOAT_80438280;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar3;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    iVar4 = zz_006dbe0_(param_1,2,1,1);
    if (iVar4 != 0) {
      zz_00b5878_(param_1,*(undefined1 *)(param_1 + 0x14b));
      *(undefined1 *)(param_1 + *(char *)(param_1 + 0x14b) + 0x149) = 1;
      *(char *)(param_1 + 0x14b) = *(char *)(param_1 + 0x14b) + '\x01';
    }
  }
  iVar4 = zz_004cd24_(param_1,1);
  if (iVar4 != 0) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800ae3c0  FUN_800ae3c0 ====

void FUN_800ae3c0(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  if (*(char *)(param_1 + 0x587) == '\x02') {
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800ae400  zz_00ae400_ ====

uint zz_00ae400_(int param_1)

{
  uint uVar1;
  short local_8 [4];
  
  local_8[0] = 0x6800;
  local_8[1] = 0x9800;
  local_8[2] = 0xffff;
  local_8[3] = 0;
  uVar1 = FUN_8006cc90((double)FLOAT_80438288,param_1,2,1,local_8);
  return (-uVar1 | uVar1) >> 0x1f;
}



// ==== 800ae45c  zz_00ae45c_ ====

bool zz_00ae45c_(int param_1)

{
  int iVar1;
  char cVar2;
  short local_18 [8];
  
  local_18[0] = 0x6800;
  local_18[1] = 0x9800;
  local_18[2] = 0xffff;
  local_18[3] = 0;
  iVar1 = FUN_8006cc90((double)FLOAT_80438288,param_1,2,1,local_18);
  cVar2 = iVar1 != 0;
  local_18[0] = 0x1000;
  local_18[1] = 0xe800;
  local_18[2] = 0xc000;
  local_18[3] = 0x4000;
  iVar1 = FUN_8006cc90((double)FLOAT_80438288,param_1,9,3,local_18);
  if (iVar1 != 0) {
    cVar2 = cVar2 + '\x01';
  }
  local_18[0] = 0x1800;
  local_18[1] = 0xf000;
  local_18[2] = 0xc000;
  local_18[3] = 0x4000;
  iVar1 = FUN_8006cc90((double)FLOAT_80438288,param_1,6,3,local_18);
  if (iVar1 != 0) {
    cVar2 = cVar2 + '\x01';
  }
  return cVar2 == '\x03';
}



// ==== 800ae56c  zz_00ae56c_ ====

void zz_00ae56c_(int param_1)

{
  char cVar1;
  int iVar2;
  
  *(char *)(param_1 + 0x148) = *(char *)(param_1 + 0x148) + '\x01';
  *(byte *)(param_1 + 0x148) = *(byte *)(param_1 + 0x148) & 3;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    cVar1 = *(char *)(param_1 + 0x148);
    if (cVar1 == '\x02') {
      zz_0082824_(param_1,6);
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        zz_0082824_(param_1,4);
      }
      else if (-1 < cVar1) {
        zz_0082824_(param_1,7);
      }
    }
    else if (cVar1 < '\x04') {
      zz_0082824_(param_1,5);
    }
  }
  return;
}



// ==== 800ae630  zz_00ae630_ ====

void zz_00ae630_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 7) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,6), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_800ae734;
    *(code **)(puVar1 + 0x10c) = FUN_800aece0;
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
  return;
}



// ==== 800ae734  FUN_800ae734 ====

void FUN_800ae734(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_802fa9f8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800ae788  FUN_800ae788 ====

void FUN_800ae788(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int iVar3;
  uint uVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x55;
  fVar1 = FLOAT_80438290;
  *(undefined *)(param_9 + 0x89) = (&DAT_80433a80)[*(char *)(param_9 + 0x11)];
  iVar3 = *(char *)(param_9 + 0x11) * 0xc;
  uVar2 = *(undefined4 *)(&DAT_802fa95c + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_802fa958 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_802fa960 + iVar3);
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(float *)(param_9 + 0x148) = fVar1;
  *(float *)(param_9 + 0x144) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(undefined2 *)(param_9 + 0x14c) = 0;
  iVar3 = zz_0006f98_(iVar5);
  uVar6 = zz_0007338_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),(float *)0x8,iVar3 + 0xc28,
                      (int)*(char *)(param_9 + 0x88),in_r8,in_r9,in_r10);
  uVar6 = zz_0007338_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe8),(float *)0xa,iVar3 + 0xc28,
                      (int)*(char *)(param_9 + 0x88),in_r8,in_r9,in_r10);
  uVar6 = zz_0007338_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xf0),(float *)0xb,iVar3 + 0xc28,
                      (int)*(char *)(param_9 + 0x88),in_r8,in_r9,in_r10);
  iVar5 = iVar3 + 0xc28;
  uVar2 = 8;
  uVar4 = (uint)*(char *)(param_9 + 0x88);
  uVar6 = zz_0007338_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),(float *)0x8,iVar5,uVar4,
                      in_r8,in_r9,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar2,iVar5,uVar4,in_r8,in_r9,in_r10);
  uVar6 = zz_0007cac_((double)FLOAT_80438294,*(int *)(param_9 + 0xe4));
  iVar5 = iVar3 + 0xc28;
  uVar2 = 10;
  uVar4 = (uint)*(char *)(param_9 + 0x88);
  uVar6 = zz_0007338_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xec),(float *)0xa,iVar5,uVar4,
                      in_r8,in_r9,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,uVar2,iVar5,uVar4,in_r8,in_r9,in_r10);
  uVar6 = zz_0007cac_((double)FLOAT_80438294,*(int *)(param_9 + 0xec));
  iVar5 = iVar3 + 0xc28;
  uVar2 = 0xb;
  uVar4 = (uint)*(char *)(param_9 + 0x88);
  uVar6 = zz_0007338_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xf4),(float *)0xb,iVar5,uVar4,
                      in_r8,in_r9,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xf4)
              ,extraout_r4_01,uVar2,iVar5,uVar4,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80438294,*(int *)(param_9 + 0xf4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00ae95c_(param_9);
  return;
}



// ==== 800ae95c  zz_00ae95c_ ====

void zz_00ae95c_(int param_1)

{
  float fVar1;
  float fVar2;
  short sVar4;
  undefined4 uVar3;
  float *pfVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  
  iVar8 = *(int *)(param_1 + 0x90);
  *(byte *)(param_1 + 0x12) = *(byte *)(iVar8 + *(char *)(param_1 + 0x11) + 0x6e8) & 0x7f;
  fVar2 = FLOAT_80438298;
  fVar1 = FLOAT_80438290;
  cVar6 = *(char *)(param_1 + 0x12);
  if (cVar6 < '\b') {
    if (cVar6 == '\x06') {
      *(float *)(param_1 + 0x148) = FLOAT_80438298;
    }
    else if (cVar6 == '\a') {
      *(float *)(param_1 + 0x148) = *(float *)(param_1 + 0x148) - FLOAT_8043829c;
      if (*(float *)(param_1 + 0x148) < fVar2) {
        *(float *)(param_1 + 0x148) = fVar2;
      }
    }
    else {
      *(float *)(param_1 + 0x148) =
           (float)(DOUBLE_804382a0 *
                   (double)(float)((double)*(float *)(param_1 + 0x144) -
                                  (double)*(float *)(param_1 + 0x148)) +
                  (double)*(float *)(param_1 + 0x148));
      if (*(float *)(param_1 + 0x148) < fVar1) {
        *(float *)(param_1 + 0x144) = FLOAT_804382a8;
      }
      if (DOUBLE_804382b0 <= (double)*(float *)(param_1 + 0x148)) {
        *(float *)(param_1 + 0x144) = FLOAT_80438290;
      }
    }
    if ((*(uint *)(iVar8 + 0x5e0) & 0x20000000) == 0) {
      sVar4 = *(short *)(*(char *)(param_1 + 0x12) * 4 + -0x7fd05660 + *(char *)(param_1 + 0x11) * 2
                        ) - *(short *)(param_1 + 0x7e);
      if (0x400 < sVar4) {
        sVar4 = 0x400;
      }
      if (sVar4 < -0x400) {
        sVar4 = -0x400;
      }
      *(short *)(param_1 + 0x7e) = *(short *)(param_1 + 0x7e) + sVar4;
      fVar1 = *(float *)(iVar8 + 0x1dc8);
      if (*(char *)(iVar8 + 0x71c) != '\0') {
        fVar1 = FLOAT_80438290;
      }
      *(short *)(param_1 + 0x72) =
           (short)(int)((float)((double)CONCAT44(0x43300000,
                                                 (int)*(short *)(param_1 + 0x7e) ^ 0x80000000) -
                               DOUBLE_804382c0) * fVar1 +
                       (float)((double)CONCAT44(0x43300000,
                                                (int)*(short *)(param_1 + 0x72) ^ 0x80000000) -
                              DOUBLE_804382c0));
      if (*(char *)(param_1 + 0x12) == '\x04') {
        pfVar5 = (float *)(*(char *)(param_1 + 0x11) * 0xc + -0x7fd05690);
      }
      else {
        pfVar5 = (float *)(&DAT_802fa958 + *(char *)(param_1 + 0x11) * 0xc);
      }
      zz_0046588_((double)FLOAT_804382b8,pfVar5,(float *)(param_1 + 100),(float *)(param_1 + 100));
    }
    if (*(char *)(param_1 + 0x12) == '\x02') {
      if ((*(char *)(param_1 + 0xaf) == -1) &&
         (((int)*(char *)(iVar8 + 0x6f6) & 1 << (int)*(char *)(param_1 + 0x11)) != 0)) {
        cVar6 = 'l';
        *(undefined1 *)(param_1 + 0xaf) = 0;
        *(undefined2 *)(param_1 + 0x14c) = *(undefined2 *)(iVar8 + 0x14a);
        if (*(char *)(iVar8 + 0x88) != '\0') {
          cVar6 = 'p';
        }
        iVar7 = 0;
        do {
          zz_001ac80_(param_1,cVar6 + (char)iVar7);
          iVar7 = iVar7 + 1;
        } while (iVar7 < 4);
      }
      if ((-1 < *(char *)(iVar8 + 0x6f6)) &&
         (*(short *)(param_1 + 0x14c) == *(short *)(iVar8 + 0x14a))) {
        return;
      }
    }
    *(undefined1 *)(param_1 + 0xaf) = 0xff;
  }
  else {
    iVar8 = *(char *)(param_1 + 0x11) * 0xc;
    uVar3 = *(undefined4 *)(&DAT_802fa98c + iVar8);
    *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_802fa988 + iVar8);
    *(undefined4 *)(param_1 + 0x68) = uVar3;
    *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_802fa990 + iVar8);
    fVar1 = FLOAT_80438290;
    sVar4 = *(short *)(*(char *)(param_1 + 0x12) * 4 + -0x7fd05660 + *(char *)(param_1 + 0x11) * 2)
            - *(short *)(param_1 + 0x72);
    if (0xc00 < sVar4) {
      sVar4 = 0xc00;
    }
    if (sVar4 < -0xc00) {
      sVar4 = -0xc00;
    }
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + sVar4;
    *(float *)(param_1 + 0x148) = fVar1;
  }
  return;
}



// ==== 800aecc0  FUN_800aecc0 ====

void FUN_800aecc0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800aece0  FUN_800aece0 ====

void FUN_800aece0(int param_1)

{
  char cVar1;
  int iVar2;
  float *pfVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar5;
  int iVar6;
  double dVar7;
  undefined8 uVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [15];
  
  iVar4 = *(int *)(param_1 + 0x90);
  iVar6 = *(char *)(param_1 + 0x12) * 4;
  iVar2 = (int)*(short *)(&DAT_802fa9cc + iVar6);
  uVar5 = (uint)*(short *)(&DAT_802fa9ce + iVar6);
  if (*(char *)(iVar4 + 0xae) == '\0') {
    cVar1 = *(char *)(iVar4 + 0x3ec);
    if (((cVar1 == '\x02') || (cVar1 == '\x03')) || (cVar1 == '\x05')) {
      uVar5 = 1;
    }
  }
  else {
    uVar5 = 0x44;
    iVar2 = iVar2 + 1;
  }
  dVar7 = (double)*(float *)(param_1 + 0x148);
  iVar6 = *(int *)(param_1 + iVar2 * 4 + 0xe0);
  dVar9 = dVar7;
  gnt4_PSMTXScale_bl(dVar7,dVar7,dVar7,afStack_48);
  pfVar3 = afStack_48;
  uVar8 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar3,pfVar3);
  zz_00076d0_(uVar8,dVar7,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,iVar6,afStack_48,(undefined *)pfVar3,
              iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_00097b4_(iVar6,uVar5);
  return;
}



// ==== 800aedc0  zz_00aedc0_ ====

undefined1 * zz_00aedc0_(int param_1,float *param_2,int param_3,undefined1 param_4)

{
  short sVar1;
  undefined1 *puVar2;
  int iVar3;
  
  sVar1 = *(short *)(&DAT_802fafd0 + param_3 * 2);
  iVar3 = (int)*(short *)(&DAT_802fafd2 + param_3 * 2) - (int)sVar1;
  puVar2 = zz_0088aa0_(param_1,2,0x18,0,iVar3);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x10] = 9;
    puVar2[0x11] = (char)param_3;
    puVar2[0x12] = (char)sVar1;
    puVar2[0x13] = (char)iVar3;
    *(code **)(puVar2 + 0xc) = FUN_800af018;
    *(code **)(puVar2 + 0x10c) = FUN_800af404;
    gnt4_PSMTXCopy_bl(param_2,(float *)(puVar2 + 0x114));
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
    *(undefined4 *)(puVar2 + 0x54) = 0;
    puVar2[0x88] = param_4;
  }
  return puVar2;
}



// ==== 800aeef8  zz_00aeef8_ ====

void zz_00aeef8_(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  double dVar3;
  float local_88;
  undefined4 local_84;
  undefined4 local_80;
  undefined4 local_7c;
  float local_78;
  undefined4 local_74;
  undefined4 local_70;
  float afStack_6c [12];
  float afStack_3c [3];
  float local_30;
  undefined4 local_20;
  undefined4 local_10;
  
  iVar1 = 6;
  if (param_2 == 0) {
    iVar1 = 10;
  }
  iVar1 = iVar1 * 0x30;
  iVar2 = param_1 + iVar1;
  local_78 = *(float *)(iVar2 + 0x8d4);
  local_74 = *(undefined4 *)(iVar2 + 0x8e4);
  local_70 = *(undefined4 *)(iVar2 + 0x8f4);
  local_84 = *(undefined4 *)(iVar2 + 0x8d8);
  local_80 = *(undefined4 *)(iVar2 + 0x8e8);
  local_7c = *(undefined4 *)(iVar2 + 0x8f8);
  if (param_2 != 0) {
    gnt4_PSQUATScale_bl((double)FLOAT_804382c8,&local_78,&local_78);
  }
  gnt4_PSMTXIdentity_bl(afStack_3c);
  zz_0045ef4_(afStack_3c,5,&local_78,&local_84);
  zz_0046470_((float *)(param_1 + iVar1 + 0x8d4),&local_88);
  dVar3 = (double)local_88;
  gnt4_PSMTXScale_bl(dVar3,dVar3,dVar3,afStack_6c);
  gnt4_PSMTXConcat_bl(afStack_3c,afStack_6c,afStack_3c);
  iVar1 = param_1 + iVar1;
  local_78 = *(float *)(iVar1 + 0x910);
  local_74 = *(undefined4 *)(iVar1 + 0x920);
  local_70 = *(undefined4 *)(iVar1 + 0x930);
  local_30 = local_78;
  local_20 = local_74;
  local_10 = local_70;
  zz_00aedc0_(param_1,afStack_3c,7,*(undefined1 *)(param_1 + 0x88));
  return;
}



// ==== 800af018  FUN_800af018 ====

void FUN_800af018(int param_1)

{
  (*(code *)(&PTR_FUN_802fafe4)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800af054  FUN_800af054 ====

void FUN_800af054(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,uint param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  int *piVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  undefined8 uVar10;
  
  uVar2 = *(char *)(param_9 + 0x13) * 0x28;
  if (uVar2 < 0x81) {
    *(int *)(param_9 + 0x54) = param_9 + 0x144;
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar5 = zz_0006dc8_(uVar2);
    *(int **)(param_9 + 0xdc) = piVar5;
    if (piVar5 != (int *)0x0) {
      *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_9 + 0x54) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    pfVar6 = (float *)(param_9 + 0x58);
    iVar7 = 0;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    iVar4 = param_9;
    do {
      *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(iVar4 + 0x114);
      *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(iVar4 + 0x124);
      *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(iVar4 + 0x134);
      dVar9 = gnt4_PSVECMag_bl((float *)(param_9 + 0x20));
      *pfVar6 = (float)dVar9;
      gnt4_PSVECNormalize_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x20));
      iVar7 = iVar7 + 1;
      pfVar6 = pfVar6 + 1;
      *(undefined4 *)(iVar4 + 0x114) = *(undefined4 *)(param_9 + 0x20);
      *(undefined4 *)(iVar4 + 0x124) = *(undefined4 *)(param_9 + 0x24);
      *(undefined4 *)(iVar4 + 0x134) = *(undefined4 *)(param_9 + 0x28);
      iVar4 = iVar4 + 4;
    } while (iVar7 < 3);
    fVar1 = *(float *)(param_9 + 0x5c);
    if (fVar1 < *(float *)(param_9 + 0x58)) {
      fVar1 = *(float *)(param_9 + 0x58);
    }
    *(float *)(param_9 + 0xb4) = fVar1;
    *(code **)(param_9 + 0x100) = FUN_800af488;
    zz_0089100_(param_9,1,1);
    iVar8 = 0;
    iVar4 = param_9;
    for (iVar7 = 0; iVar7 < *(char *)(param_9 + 0x13); iVar7 = iVar7 + 1) {
      iVar3 = *(char *)(param_9 + 0x12) + iVar7;
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar7);
      piVar5 = (int *)(*(int *)(param_9 + 0x54) + iVar8);
      *(undefined2 *)(piVar5 + 8) = 0;
      *(undefined2 *)((int)piVar5 + 0x22) = *(undefined2 *)(&DAT_802faefa + iVar3 * 0xc);
      if (*(char *)(param_9 + 0x12) + iVar7 == 7) {
        *(undefined2 *)(piVar5 + 9) = 0;
      }
      else {
        uVar2 = zz_00055fc_();
        *(short *)(piVar5 + 9) = (short)(uVar2 << 8);
      }
      zz_0018f88_(piVar5,(int)(&PTR_DAT_802faefc)[iVar3 * 3],(float *)(piVar5 + 4));
      uVar10 = zz_0019338_(piVar5 + 2,(int)(&PTR_DAT_802faf00)[iVar3 * 3],(float *)(piVar5 + 7));
      if (*(char *)(param_9 + 0x11) == '\x02') {
        pfVar6 = (float *)(int)*(short *)(&DAT_802faef8 + iVar3 * 0xc);
        zz_0006fb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                    *(int *)(iVar4 + 0xe0),(int)pfVar6,param_12,param_13,param_14,param_15,param_16)
        ;
        uVar10 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                              (int)*(char *)(param_9 + 0x88) ^
                                                              0x80000000) - DOUBLE_804382d0),param_2
                             ,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                             *(int *)(iVar4 + 0xe0),pfVar6,param_12,param_13,param_14,param_15,
                             param_16);
        zz_0007c30_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar4 + 0xe0),extraout_r4,pfVar6,param_12,param_13,param_14,param_15,
                    param_16);
      }
      else {
        param_12 = (uint)*(char *)(param_9 + 0x88);
        zz_000726c_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                    *(int *)(iVar4 + 0xe0),(float *)(int)*(short *)(&DAT_802faef8 + iVar3 * 0xc),
                    param_12,param_13,param_14,param_15,param_16);
      }
      zz_0007cac_((double)(float)piVar5[7],*(int *)(iVar4 + 0xe0));
      iVar8 = iVar8 + 0x28;
      iVar4 = iVar4 + 4;
    }
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 800af2d0  FUN_800af2d0 ====

void FUN_800af2d0(int param_1)

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
      zz_0018fd8_(piVar2,(int)*(short *)(piVar2 + 8),(float *)(piVar2 + 4));
      zz_0019370_(piVar2 + 2,(int)*(short *)(piVar2 + 8),(float *)(piVar2 + 7));
      zz_0007cac_((double)(float)piVar2[7],*(int *)(iVar4 + 0xe0));
    }
    iVar5 = iVar5 + 0x28;
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 1;
  }
  if (*(short *)(param_1 + 0x1c) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 800af3bc  FUN_800af3bc ====

void FUN_800af3bc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800af404  FUN_800af404 ====

void FUN_800af404(int param_1)

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



// ==== 800af488  FUN_800af488 ====

void FUN_800af488(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  short sVar1;
  float *pfVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  float afStack_58 [3];
  float afStack_4c [14];
  
  iVar5 = 0;
  iVar7 = 0;
  iVar6 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar5) break;
    if (((int)*(short *)(param_9 + 0x1c) & 1 << iVar5) != 0) {
      iVar4 = *(int *)(param_9 + 0x54) + iVar7;
      sVar1 = *(short *)(iVar4 + 0x24);
      iVar3 = (int)sVar1;
      zz_00457d4_('z',(float *)(param_9 + 0x114),afStack_4c,sVar1);
      gnt4_PSQUATScale_bl((double)*(float *)(param_9 + 0xb4),(float *)(iVar4 + 0x10),afStack_58);
      pfVar2 = afStack_58;
      uVar8 = zz_00456a0_(afStack_4c,afStack_4c,pfVar2);
      zz_00076d0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar6 + 0xe0),afStack_4c,(undefined *)pfVar2,iVar3,in_r7,in_r8,in_r9,
                  in_r10);
    }
    iVar7 = iVar7 + 0x28;
    iVar6 = iVar6 + 4;
    iVar5 = iVar5 + 1;
  }
  return;
}



// ==== 800af634  FUN_800af634 ====

void FUN_800af634(int param_1)

{
  zz_004f1c4_(param_1);
  zz_00c1600_(param_1);
  zz_00c74ec_(param_1,0x33);
  return;
}



// ==== 800af674  FUN_800af674 ====

void FUN_800af674(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  double dVar6;
  double dVar7;
  
  if (*(short *)(param_1 + 0x79e) <= *(short *)(param_1 + 0x784)) {
    if (*(char *)(param_1 + 0x144) != '\0') {
      *(undefined4 *)(param_1 + 0x148) = 0x34000;
      *(undefined2 *)(param_1 + 0x146) = 0x400;
    }
    *(undefined1 *)(param_1 + 0x144) = 0;
  }
  if (((*(uint *)(param_1 + 0x5e0) & 0x20000003) == 0) && (0 < *(int *)(param_1 + 0x148))) {
    dVar7 = zz_0045204_((short)*(int *)(param_1 + 0x148));
    dVar6 = DOUBLE_804382f0;
    fVar5 = FLOAT_804382e8;
    fVar4 = FLOAT_804382e4;
    fVar3 = FLOAT_804382e0;
    fVar2 = FLOAT_804382dc;
    fVar1 = FLOAT_804382d8;
    *(short *)(param_1 + 0x18e6) =
         (short)(int)((double)(float)((double)CONCAT44(0x43300000,
                                                       (int)*(short *)(param_1 + 0x146) ^ 0x80000000
                                                      ) - DOUBLE_804382f0) * dVar7);
    *(int *)(param_1 + 0x148) =
         (int)((float)((double)CONCAT44(0x43300000,*(uint *)(param_1 + 0x148) ^ 0x80000000) - dVar6)
              * (fVar2 * (fVar3 - *(float *)(param_1 + 0x1dc8)) + fVar1));
    *(short *)(param_1 + 0x146) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x146) ^ 0x80000000) -
                             dVar6) * (fVar5 * (fVar3 - *(float *)(param_1 + 0x1dc8)) + fVar4));
  }
  return;
}



// ==== 800af7b8  FUN_800af7b8 ====

void FUN_800af7b8(int param_1)

{
  zz_006d520_(param_1,(float *)&DAT_802fb2d0);
  return;
}



// ==== 800af7f0  FUN_800af7f0 ====

void FUN_800af7f0(int param_1)

{
  (*(code *)(&PTR_FUN_802fb300)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800af82c  FUN_800af82c ====

void FUN_800af82c(int param_1)

{
  (*(code *)(&PTR_FUN_80433a90)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800af864  FUN_800af864 ====

void FUN_800af864(int param_1)

{
  (*(code *)(&PTR_LAB_802fb30c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800af8d0  FUN_800af8d0 ====

/* WARNING: Removing unreachable block (ram,0x800af9a8) */
/* WARNING: Removing unreachable block (ram,0x800af8e0) */

void FUN_800af8d0(int param_1)

{
  uint uVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if (*(int *)(param_1 + 0xcc) == 0) {
    iVar2 = 0;
  }
  else {
    local_28 = *(float *)(param_1 + 0xa00);
    local_24 = *(undefined4 *)(param_1 + 0xa10);
    local_20 = *(undefined4 *)(param_1 + 0xa20);
    dVar3 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    local_28 = *(float *)(param_1 + 0x9d0);
    local_24 = *(undefined4 *)(param_1 + 0x9e0);
    local_20 = *(undefined4 *)(param_1 + 0x9f0);
    dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    if (dVar4 < dVar3) {
      iVar2 = 1;
    }
    else {
      iVar2 = 0;
    }
  }
  if ((*(short *)(param_1 + 0x548) < 1) || (uVar1 = FUN_800b04f8(param_1,iVar2), uVar1 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0;
    *(undefined2 *)(param_1 + 0x54a) = 0;
    *(undefined2 *)(param_1 + 0x54c) = 0;
  }
  return;
}



// ==== 800af9c4  FUN_800af9c4 ====

/* WARNING: Removing unreachable block (ram,0x800afb40) */
/* WARNING: Removing unreachable block (ram,0x800af9d4) */

void FUN_800af9c4(int param_1)

{
  int iVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    iVar2 = 0;
  }
  else {
    local_28 = *(float *)(param_1 + 0xa00);
    local_24 = *(undefined4 *)(param_1 + 0xa10);
    local_20 = *(undefined4 *)(param_1 + 0xa20);
    dVar3 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    local_28 = *(float *)(param_1 + 0x9d0);
    local_24 = *(undefined4 *)(param_1 + 0x9e0);
    local_20 = *(undefined4 *)(param_1 + 0x9f0);
    dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    if (dVar4 < dVar3) {
      iVar2 = 1;
    }
    else {
      iVar2 = 0;
    }
  }
  FUN_800b04f8(param_1,iVar2);
  if ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x548) = 1;
  }
  if (*(short *)(param_1 + 0x54a) == 0) {
    *(undefined2 *)(param_1 + 0x54a) = 6;
    *(short *)(param_1 + 0x54c) = *(short *)(param_1 + 0x54c) + 1;
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      if (iVar2 == 0) {
        zz_0082824_(param_1,9);
      }
      else {
        zz_0082824_(param_1,8);
      }
    }
    if (*(short *)(param_1 + 0x548) == 0) {
      if (1 < *(short *)(param_1 + 0x54c)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined2 *)(param_1 + 0x548) = 0x1e;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x548) = 0;
      if (2 < *(short *)(param_1 + 0x54c)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined2 *)(param_1 + 0x548) = 0x1e;
      }
    }
  }
  else {
    *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) + -1;
  }
  return;
}



// ==== 800afb60  FUN_800afb60 ====

void FUN_800afb60(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  *(short *)(param_9 + 0x548) = *(short *)(param_9 + 0x548) + -1;
  if (*(short *)(param_9 + 0x548) < 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 800afbb0  FUN_800afbb0 ====

void FUN_800afbb0(int param_1)

{
  (*(code *)(&PTR_LAB_802fb320)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800afc1c  FUN_800afc1c ====

/* WARNING: Removing unreachable block (ram,0x800afcf4) */
/* WARNING: Removing unreachable block (ram,0x800afc2c) */

void FUN_800afc1c(int param_1)

{
  uint uVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if (*(int *)(param_1 + 0xcc) == 0) {
    iVar2 = 0;
  }
  else {
    local_28 = *(float *)(param_1 + 0xa00);
    local_24 = *(undefined4 *)(param_1 + 0xa10);
    local_20 = *(undefined4 *)(param_1 + 0xa20);
    dVar3 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    local_28 = *(float *)(param_1 + 0x9d0);
    local_24 = *(undefined4 *)(param_1 + 0x9e0);
    local_20 = *(undefined4 *)(param_1 + 0x9f0);
    dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    if (dVar4 < dVar3) {
      iVar2 = 1;
    }
    else {
      iVar2 = 0;
    }
  }
  if ((*(short *)(param_1 + 0x548) < 1) || (uVar1 = FUN_800b04f8(param_1,iVar2), uVar1 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 0;
    *(undefined2 *)(param_1 + 0x54a) = 0;
    *(undefined2 *)(param_1 + 0x54c) = 0;
  }
  return;
}



// ==== 800afd10  FUN_800afd10 ====

/* WARNING: Removing unreachable block (ram,0x800afe8c) */
/* WARNING: Removing unreachable block (ram,0x800afd20) */

void FUN_800afd10(int param_1)

{
  int iVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    iVar2 = 0;
  }
  else {
    local_28 = *(float *)(param_1 + 0xa00);
    local_24 = *(undefined4 *)(param_1 + 0xa10);
    local_20 = *(undefined4 *)(param_1 + 0xa20);
    dVar3 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    local_28 = *(float *)(param_1 + 0x9d0);
    local_24 = *(undefined4 *)(param_1 + 0x9e0);
    local_20 = *(undefined4 *)(param_1 + 0x9f0);
    dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x518),&local_28);
    if (dVar4 < dVar3) {
      iVar2 = 1;
    }
    else {
      iVar2 = 0;
    }
  }
  FUN_800b04f8(param_1,iVar2);
  if ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x548) = 1;
  }
  if (*(short *)(param_1 + 0x54a) == 0) {
    *(undefined2 *)(param_1 + 0x54a) = 6;
    *(short *)(param_1 + 0x54c) = *(short *)(param_1 + 0x54c) + 1;
    iVar1 = zz_006dbe0_(param_1,0,1,1);
    if (iVar1 != 0) {
      if (iVar2 == 0) {
        zz_0082824_(param_1,9);
      }
      else {
        zz_0082824_(param_1,8);
      }
    }
    if (*(short *)(param_1 + 0x548) == 0) {
      if (1 < *(short *)(param_1 + 0x54c)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined2 *)(param_1 + 0x548) = 0x1e;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x548) = 0;
      if (2 < *(short *)(param_1 + 0x54c)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(undefined2 *)(param_1 + 0x548) = 0x1e;
      }
    }
  }
  else {
    *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) + -1;
  }
  return;
}



// ==== 800afeac  FUN_800afeac ====

void FUN_800afeac(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  *(short *)(param_9 + 0x548) = *(short *)(param_9 + 0x548) + -1;
  if (*(short *)(param_9 + 0x548) < 1) {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 800afefc  FUN_800afefc ====

void FUN_800afefc(int param_1)

{
  (*(code *)(&PTR_FUN_80433a98)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800aff34  FUN_800aff34 ====

void FUN_800aff34(int param_1)

{
  (*(code *)(&PTR_FUN_802fb334)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800aff70  FUN_800aff70 ====

void FUN_800aff70(int param_1)

{
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined4 *)(param_1 + 0x148) = 0;
  *(undefined2 *)(param_1 + 0x146) = 0;
  if (*(short *)(param_1 + 0x784) == 0) {
    *(undefined1 *)(param_1 + 0x540) = 3;
  }
  else {
    zz_00f036c_(param_1,0xbe);
  }
  return;
}



// ==== 800affc4  FUN_800affc4 ====

void FUN_800affc4(int param_1)

{
  int iVar1;
  bool bVar2;
  byte bVar3;
  double dVar4;
  
  zz_006660c_(param_1);
  iVar1 = FUN_800669d0(param_1,0xc1);
  bVar3 = iVar1 != 0;
  bVar2 = FUN_800b0490(param_1);
  if (bVar2) {
    bVar3 = bVar3 | 2;
  }
  if (bVar3 == 3) {
    dVar4 = (double)FLOAT_804382f8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 0;
    zz_004beb8_(dVar4,param_1,3,4,0,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800b0064  FUN_800b0064 ====

void FUN_800b0064(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x541) == '\0') {
    *(undefined1 *)(param_1 + 0x541) = 1;
    iVar1 = zz_006dbe0_(param_1,2,1,1);
    if (iVar1 != 0) {
      FUN_800b6ac8(param_1);
      *(undefined1 *)(param_1 + 0x144) = 1;
    }
  }
  if (*(char *)(param_1 + 0x1cef) == '\x01') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
    *(undefined1 *)(param_1 + 0x1cef) = 0;
  }
  iVar1 = zz_004cd24_(param_1,3);
  if (iVar1 != 0) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800b0118  FUN_800b0118 ====

void FUN_800b0118(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 800b014c  FUN_800b014c ====

void FUN_800b014c(int param_1)

{
  (*(code *)(&PTR_FUN_802fb344)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b0188  FUN_800b0188 ====

void FUN_800b0188(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined4 *)(param_1 + 0x148) = 0;
  *(undefined2 *)(param_1 + 0x146) = 0;
  if (*(short *)(param_1 + 0x784) == 0) {
    *(undefined1 *)(param_1 + 0x540) = 3;
  }
  else {
    zz_00f036c_(param_1,0xbe);
    fVar3 = FLOAT_804382fc;
    fVar2 = FLOAT_804382dc;
    fVar1 = FLOAT_804382d8;
    dVar4 = (double)FLOAT_804382e0;
    *(float *)(param_1 + 0x44) =
         *(float *)(param_1 + 0x44) *
         (FLOAT_804382e8 * (float)(dVar4 - (double)*(float *)(param_1 + 0x1dc8)) + FLOAT_804382e4);
    *(float *)(param_1 + 0x48) =
         *(float *)(param_1 + 0x48) *
         (fVar2 * (float)(dVar4 - (double)*(float *)(param_1 + 0x1dc8)) + fVar1);
    *(float *)(param_1 + 0x4c) = fVar3;
    *(float *)(param_1 + 0x50) = fVar3;
    zz_0067458_(dVar4,param_1,*(short *)(param_1 + 0x5ae));
    zz_00677b0_(param_1);
    *(undefined1 *)(param_1 + 0x709) = 1;
  }
  return;
}



// ==== 800b0254  FUN_800b0254 ====

void FUN_800b0254(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  bool bVar5;
  byte bVar6;
  double dVar7;
  
  zz_006660c_(param_1);
  iVar3 = FUN_800669d0(param_1,0xc1);
  iVar4 = FUN_800669d0(param_1,0xc1);
  bVar6 = iVar4 != 0 || iVar3 != 0;
  bVar5 = FUN_800b0490(param_1);
  if (bVar5) {
    bVar6 = bVar6 | 2;
  }
  if (bVar6 == 3) {
    dVar7 = (double)FLOAT_804382f8;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 0;
    zz_004beb8_(dVar7,param_1,3,4,0,0xffffffff,0xffffffff);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
  }
  fVar2 = FLOAT_804382dc;
  fVar1 = FLOAT_804382d8;
  dVar7 = (double)FLOAT_804382e0;
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_804382e8 * (float)(dVar7 - (double)*(float *)(param_1 + 0x1dc8)) + FLOAT_804382e4);
  *(float *)(param_1 + 0x48) =
       *(float *)(param_1 + 0x48) *
       (fVar2 * (float)(dVar7 - (double)*(float *)(param_1 + 0x1dc8)) + fVar1);
  zz_0067458_(dVar7,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  *(undefined1 *)(param_1 + 0x709) = 1;
  return;
}



// ==== 800b0378  FUN_800b0378 ====

void FUN_800b0378(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x541) == '\0') {
    *(undefined1 *)(param_1 + 0x541) = 1;
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 != 0) {
      FUN_800b6ac8(param_1);
      *(undefined1 *)(param_1 + 0x144) = 1;
    }
  }
  iVar3 = zz_004cd24_(param_1,3);
  if (iVar3 != 0) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  fVar2 = FLOAT_804382dc;
  fVar1 = FLOAT_804382d8;
  dVar4 = (double)FLOAT_804382e0;
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_804382e8 * (float)(dVar4 - (double)*(float *)(param_1 + 0x1dc8)) + FLOAT_804382e4);
  *(float *)(param_1 + 0x48) =
       *(float *)(param_1 + 0x48) *
       (fVar2 * (float)(dVar4 - (double)*(float *)(param_1 + 0x1dc8)) + fVar1);
  zz_0067458_(dVar4,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  *(undefined1 *)(param_1 + 0x709) = 1;
  return;
}



// ==== 800b045c  FUN_800b045c ====

void FUN_800b045c(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a5a4_(param_1);
  return;
}



// ==== 800b0490  FUN_800b0490 ====

bool FUN_800b0490(int param_1)

{
  bool bVar1;
  
  *(short *)(param_1 + 0x18e6) =
       (short)(int)-(FLOAT_80438300 * *(float *)(param_1 + 0x1dc8) -
                    (float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e6) ^ 0x80000000) -
                           DOUBLE_804382f0));
  bVar1 = *(short *)(param_1 + 0x18e6) < -0x3fff;
  if (bVar1) {
    *(undefined2 *)(param_1 + 0x18e6) = 0xc000;
  }
  return bVar1;
}



// ==== 800b04f8  FUN_800b04f8 ====

uint FUN_800b04f8(int param_1,int param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  short local_18 [10];
  
  iVar3 = 0;
  if (param_2 == 0) {
    local_18[0] = 0x4000;
    local_18[1] = 0xe800;
    local_18[2] = 0xe800;
    local_18[3] = 0x1000;
    iVar2 = FUN_8006cc90((double)FLOAT_80438304,param_1,6,2,local_18);
    if (iVar2 != 0) {
      iVar3 = 1;
    }
  }
  else {
    local_18[0] = 0x1800;
    local_18[1] = 0xc000;
    local_18[2] = 0xe800;
    local_18[3] = 0x1000;
    iVar2 = FUN_8006cc90((double)FLOAT_80438304,param_1,5,2,local_18);
    if (iVar2 != 0) {
      iVar3 = 1;
    }
  }
  uVar1 = countLeadingZeros(1 - iVar3);
  return uVar1 >> 5;
}



// ==== 800b06b0  FUN_800b06b0 ====

void FUN_800b06b0(int param_1)

{
  *(undefined2 *)(param_1 + 0x144) = 0;
  *(undefined1 *)(param_1 + 0x14c) = 0;
  *(undefined1 *)(param_1 + 0x14e) = 0;
  *(undefined1 *)(param_1 + 0x14f) = 0;
  *(undefined1 *)(param_1 + 0x150) = 0;
  *(undefined1 *)(param_1 + 0x151) = 0;
  *(undefined1 *)(param_1 + 0x153) = 0;
  FUN_800e8220(param_1);
  zz_00c74ec_(param_1,0x32);
  return;
}



// ==== 800b0714  FUN_800b0714 ====

void FUN_800b0714(int param_1)

{
  float fVar1;
  double dVar2;
  
  zz_006d520_(param_1,(float *)&DAT_802fc3f0);
  if (*(char *)(param_1 + 0x14e) != '\0') {
    if (*(char *)(param_1 + 0x150) < '\x01') {
      *(undefined1 *)(param_1 + 0x14e) = 0;
    }
    else {
      *(char *)(param_1 + 0x150) = *(char *)(param_1 + 0x150) + -1;
    }
  }
  if (*(char *)(param_1 + 0x14f) != '\0') {
    if (*(char *)(param_1 + 0x151) < '\x01') {
      *(undefined1 *)(param_1 + 0x14f) = 0;
    }
    else {
      *(char *)(param_1 + 0x151) = *(char *)(param_1 + 0x151) + -1;
    }
  }
  dVar2 = DOUBLE_80438310;
  fVar1 = FLOAT_80438308;
  if (*(char *)(param_1 + 0x153) == '\0') {
    *(short *)(param_1 + 0x18fe) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18fe) ^ 0x80000000) -
                             DOUBLE_80438310) * FLOAT_80438308);
    *(short *)(param_1 + 0x1904) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1904) ^ 0x80000000) -
                             dVar2) * fVar1);
  }
  if ((*(char *)(param_1 + 0x5e4) == '\x01') || (*(char *)(param_1 + 0x5e4) == '\x02')) {
    zz_00f0104_(param_1,0x14,6);
  }
  return;
}



// ==== 800b085c  FUN_800b085c ====

void FUN_800b085c(int param_1)

{
  (*(code *)(&PTR_FUN_802fc420)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800b0898  FUN_800b0898 ====

void FUN_800b0898(int param_1)

{
  (*(code *)(&PTR_FUN_80433aa8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800b08d0  FUN_800b08d0 ====

void FUN_800b08d0(int param_1)

{
  (*(code *)(&PTR_FUN_802fc430)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b090c  FUN_800b090c ====

void FUN_800b090c(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_80438318;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x146) = 0;
  *(undefined2 *)(param_1 + 0x148) = 0;
  *(undefined2 *)(param_1 + 0x14a) = 0;
  *(undefined1 *)(param_1 + 0x14c) = 0;
  *(undefined1 *)(param_1 + 0x14d) = 0;
  *(undefined1 *)(param_1 + 0x152) = 0;
  zz_004beb8_(dVar1,param_1,0xf,2,0,0xffffffff,0xffffffff);
  return;
}



// ==== 800b096c  FUN_800b096c ====

void FUN_800b096c(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,0);
  iVar1 = FUN_800b1654(param_1);
  if (iVar1 == 0) {
    iVar1 = FUN_800b17cc(param_1,0);
    if (iVar1 != 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined2 *)(param_1 + 0x548) = 10;
    }
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 10;
  }
  return;
}



// ==== 800b0a04  FUN_800b0a04 ====

void FUN_800b0a04(int param_1)

{
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if (*(short *)(param_1 + 0x548) < 1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800b0a50  FUN_800b0a50 ====

void FUN_800b0a50(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  (*(code *)(&PTR_FUN_802fc43c)[*(char *)(param_1 + 0x540)])();
  fVar2 = FLOAT_80438324;
  fVar1 = FLOAT_80438320;
  dVar3 = (double)FLOAT_80438328;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043831c;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  zz_0067458_(dVar3,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 800b0adc  FUN_800b0adc ====

void FUN_800b0adc(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_80438318;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x146) = 0;
  *(undefined2 *)(param_1 + 0x148) = 0;
  *(undefined2 *)(param_1 + 0x14a) = 0;
  *(undefined1 *)(param_1 + 0x14c) = 0;
  *(undefined1 *)(param_1 + 0x14d) = 0;
  *(undefined1 *)(param_1 + 0x152) = 0;
  zz_004beb8_(dVar1,param_1,0xf,2,1,0xffffffff,0xffffffff);
  return;
}



// ==== 800b0b3c  FUN_800b0b3c ====

void FUN_800b0b3c(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,1);
  iVar1 = FUN_800b1654(param_1);
  if (iVar1 == 0) {
    iVar1 = FUN_800b17cc(param_1,1);
    if (iVar1 != 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined2 *)(param_1 + 0x548) = 10;
    }
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined2 *)(param_1 + 0x548) = 10;
  }
  return;
}



// ==== 800b0bd4  FUN_800b0bd4 ====

void FUN_800b0bd4(int param_1)

{
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if (*(short *)(param_1 + 0x548) < 1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800b0c20  FUN_800b0c20 ====

void FUN_800b0c20(int param_1)

{
  (*(code *)(&PTR_FUN_80433ab0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800b0c58  FUN_800b0c58 ====

void FUN_800b0c58(int param_1)

{
  (*(code *)(&PTR_FUN_802fc448)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b0c94  FUN_800b0c94 ====

void FUN_800b0c94(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_80438318;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x154) = 0;
  zz_004beb8_(dVar1,param_1,0xf,2,0,0xffffffff,0xffffffff);
  return;
}



// ==== 800b0ce0  FUN_800b0ce0 ====

void FUN_800b0ce0(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,0);
  FUN_800b1918(param_1);
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 10;
  return;
}



// ==== 800b0d44  FUN_800b0d44 ====

void FUN_800b0d44(int param_1)

{
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if (*(short *)(param_1 + 0x548) < 1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800b0d90  FUN_800b0d90 ====

void FUN_800b0d90(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  (*(code *)(&PTR_FUN_802fc454)[*(char *)(param_1 + 0x540)])();
  fVar2 = FLOAT_80438324;
  fVar1 = FLOAT_80438320;
  dVar3 = (double)FLOAT_80438328;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043831c;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  zz_0067458_(dVar3,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 800b0e1c  FUN_800b0e1c ====

void FUN_800b0e1c(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_80438318;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x154) = 0;
  zz_004beb8_(dVar1,param_1,0xf,2,1,0xffffffff,0xffffffff);
  return;
}



// ==== 800b0e68  FUN_800b0e68 ====

void FUN_800b0e68(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,1);
  FUN_800b1918(param_1);
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 10;
  return;
}



// ==== 800b0ecc  FUN_800b0ecc ====

void FUN_800b0ecc(int param_1)

{
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if (*(short *)(param_1 + 0x548) < 1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800b0f18  FUN_800b0f18 ====

void FUN_800b0f18(int param_1)

{
  (*(code *)(&PTR_FUN_80433ab8)[*(char *)(param_1 + 0x581)])();
  *(undefined1 *)(param_1 + 0x7de) = 1;
  return;
}



// ==== 800b0f64  FUN_800b0f64 ====

void FUN_800b0f64(int param_1)

{
  (*(code *)(&PTR_FUN_802fc460)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b0fa0  FUN_800b0fa0 ====

void FUN_800b0fa0(int param_1)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  
  fVar2 = FLOAT_8043832c;
  fVar1 = FLOAT_80438320;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  zz_00ec1f4_(param_1,0);
  zz_00f0104_(param_1,8,2);
  zz_004beb8_((double)FLOAT_80438318,param_1,0xf,4,0,0xffffffff,0xffffffff);
  uVar3 = zz_00677b0_(param_1);
  *(char *)(param_1 + 0x156) = (char)uVar3;
  return;
}



// ==== 800b1048  FUN_800b1048 ====

void FUN_800b1048(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_00f0104_(param_1,8,2);
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x156) == '\x01') && (iVar3 = zz_00677b0_(param_1), iVar3 == 0)) {
    dVar4 = (double)FLOAT_80438318;
    *(undefined1 *)(param_1 + 0x156) = 0;
    zz_004beb8_(dVar4,param_1,0xf,4,1,0xffffffff,0xffffffff);
  }
  fVar2 = FLOAT_80438320;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  fVar1 = *(float *)(param_1 + 0x558);
  iVar3 = FUN_800b18e8(param_1);
  if ((iVar3 != 0 || fVar1 <= fVar2) && (*(char *)(param_1 + 0x1cee) != '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 0;
    zz_004cff4_(param_1,0xf);
    if (*(char *)(param_1 + 0x156) == '\0') {
      *(undefined1 *)(param_1 + 0x581) = 1;
    }
  }
  return;
}



// ==== 800b115c  FUN_800b115c ====

void FUN_800b115c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar4;
  
  zz_00f0104_(param_9,5,3);
  fVar1 = FLOAT_80438330;
  if (*(char *)(param_9 + 0x541) == '\0') {
    *(undefined1 *)(param_9 + 0x541) = 1;
    fVar2 = FLOAT_80438334;
    *(short *)(param_9 + 0x5ae) = *(short *)(param_9 + 0x72) + -0x8000;
    *(float *)(param_9 + 0x44) = fVar1;
    *(float *)(param_9 + 0x4c) = fVar2;
    *(undefined1 *)(param_9 + 0x6ea) = 1;
  }
  iVar3 = zz_004cd24_(param_9,0xf);
  fVar1 = FLOAT_80438320;
  if (iVar3 == 0) {
    if (*(char *)(param_9 + 0x1cef) == '\x01') {
      zz_00670dc_(param_9,*(short *)(param_9 + 0x5ae));
      if (*(float *)(param_9 + 0x44) < FLOAT_80438338) {
        *(float *)(param_9 + 0x44) = FLOAT_80438338;
      }
    }
    else if (*(char *)(param_9 + 0x156) == '\x01') {
      *(float *)(param_9 + 0x50) = FLOAT_80438320;
      *(float *)(param_9 + 0x48) = fVar1;
      *(float *)(param_9 + 0x4c) = fVar1;
      *(float *)(param_9 + 0x44) = fVar1;
      *(undefined2 *)(param_9 + 0x80) = 0;
      *(undefined2 *)(param_9 + 0x7e) = 0;
      *(undefined2 *)(param_9 + 0x7c) = 0;
    }
    else {
      zz_0067458_((double)FLOAT_80438328,param_9,*(short *)(param_9 + 0x5ae));
      fVar1 = FLOAT_80438320;
      param_2 = (double)*(float *)(param_9 + 0x44);
      *(float *)(param_9 + 0x44) = (float)(param_2 * (double)FLOAT_8043831c);
      *(float *)(param_9 + 0x4c) = fVar1;
    }
    if ((*(char *)(param_9 + 0x156) == '\x01') && (iVar3 = zz_00677b0_(param_9), iVar3 == 0)) {
      dVar4 = (double)FLOAT_80438318;
      *(undefined1 *)(param_9 + 0x156) = 0;
      zz_0048648_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,4,1,10,2,
                  in_r9,in_r10);
      zz_0048648_((double)FLOAT_80438318,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  param_9,1,4,1,10,2,in_r9,in_r10);
    }
  }
  else {
    *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + '\x01';
    *(undefined1 *)(param_9 + 0x6ea) = 2;
  }
  return;
}



// ==== 800b12e8  FUN_800b12e8 ====

void FUN_800b12e8(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  if (*(char *)(param_1 + 0x156) == '\x01') {
    zz_006a474_(param_1);
  }
  else {
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 800b1330  FUN_800b1330 ====

void FUN_800b1330(int param_1)

{
  (*(code *)(&PTR_FUN_802fc470)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800b136c  FUN_800b136c ====

void FUN_800b136c(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  
  dVar3 = (double)FLOAT_80438318;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,1,0xffffffff,0xffffffff);
  fVar2 = FLOAT_80438324;
  fVar1 = FLOAT_80438320;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043831c;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar2;
  *(float *)(param_1 + 0x50) = fVar1;
  *(undefined2 *)(param_1 + 0x548) = 0x3c;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  zz_00ec1f4_(param_1,0);
  zz_00f0104_(param_1,8,2);
  zz_0067458_((double)FLOAT_80438328,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 800b142c  FUN_800b142c ====

void FUN_800b142c(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  zz_00f0104_(param_1,8,2);
  zz_004cd24_(param_1,0xf);
  iVar2 = FUN_800b18e8(param_1);
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if ((*(short *)(param_1 + 0x548) < 1 || iVar2 != 0) && (*(char *)(param_1 + 0x1cee) != '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 0;
    zz_004cff4_(param_1,0xf);
  }
  fVar1 = FLOAT_80438324;
  dVar3 = (double)FLOAT_80438328;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043831c;
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar1;
  zz_0067458_(dVar3,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 800b1514  FUN_800b1514 ====

void FUN_800b1514(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_00f0104_(param_1,5,3);
  if (*(char *)(param_1 + 0x541) == '\0') {
    *(undefined1 *)(param_1 + 0x541) = 1;
    fVar2 = FLOAT_80438334;
    fVar1 = FLOAT_80438330;
    dVar4 = (double)FLOAT_80438318;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x90c);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x91c);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x92c);
    gnt4_PSQUATScale_bl(dVar4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    *(undefined1 *)(param_1 + 0x6ea) = 1;
  }
  iVar3 = zz_004cd24_(param_1,0xf);
  if (iVar3 != 0) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x6ea) = 2;
  }
  FUN_80067610(param_1);
  fVar1 = FLOAT_80438320;
  if (*(char *)(param_1 + 0x1cef) == '\x01') {
    if (*(float *)(param_1 + 0x44) < FLOAT_80438338) {
      *(float *)(param_1 + 0x44) = FLOAT_80438338;
    }
  }
  else {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043831c;
    *(float *)(param_1 + 0x4c) = fVar1;
  }
  zz_00677b0_(param_1);
  return;
}



// ==== 800b1620  FUN_800b1620 ====

void FUN_800b1620(int param_1)

{
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a5a4_(param_1);
  return;
}



// ==== 800b1654  FUN_800b1654 ====

undefined4 FUN_800b1654(int param_1)

{
  short sVar1;
  int iVar2;
  short sVar3;
  
  iVar2 = zz_00853ec_(param_1,3);
  sVar3 = (short)iVar2;
  if (sVar3 < -0x4000) {
    sVar3 = -0x4000;
  }
  else if (0x1800 < sVar3) {
    sVar3 = 0x1800;
  }
  sVar1 = *(short *)(param_1 + 0x144);
  iVar2 = (int)sVar3;
  if (sVar1 < iVar2) {
    *(short *)(param_1 + 0x144) = sVar1 + 0x180;
    if (iVar2 + -0xc0 <= (int)*(short *)(param_1 + 0x144)) {
      *(short *)(param_1 + 0x144) = sVar3;
    }
  }
  else if ((iVar2 < sVar1) &&
          (*(short *)(param_1 + 0x144) = sVar1 + -0x180,
          (int)*(short *)(param_1 + 0x144) <= iVar2 + 0xc0)) {
    *(short *)(param_1 + 0x144) = sVar3;
  }
  *(undefined2 *)(param_1 + 0x18ec) = *(undefined2 *)(param_1 + 0x144);
  if (*(short *)(param_1 + 0x148) == 0) {
    *(undefined2 *)(param_1 + 0x148) = 5;
    *(short *)(param_1 + 0x14a) = *(short *)(param_1 + 0x14a) + 1;
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 == 0) {
      return 1;
    }
    zz_0084600_(param_1,*(char *)(param_1 + 0x14c) + 3);
    *(char *)(param_1 + 0x14c) = *(char *)(param_1 + 0x14c) + '\x01';
    *(byte *)(param_1 + 0x14c) = *(byte *)(param_1 + 0x14c) & 3;
    if (*(short *)(param_1 + 0x146) == 0) {
      if (0xb < *(short *)(param_1 + 0x14a)) {
        return 1;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x146) = 0;
      if (399 < *(short *)(param_1 + 0x14a)) {
        return 1;
      }
    }
  }
  else {
    *(short *)(param_1 + 0x148) = *(short *)(param_1 + 0x148) + -1;
    if ((*(uint *)(param_1 + 0x5b4) & 0x200) != 0) {
      *(undefined2 *)(param_1 + 0x146) = 1;
    }
  }
  return 0;
}



// ==== 800b17cc  FUN_800b17cc ====

undefined4 FUN_800b17cc(int param_1,undefined4 param_2)

{
  int iVar1;
  uint uVar2;
  ushort uVar3;
  
  uVar2 = countLeadingZeros(param_2);
  *(undefined1 *)(param_1 + 0x153) = 1;
  uVar3 = -((ushort)(uVar2 >> 5) & 1) & 0xc000;
  if (((short)uVar3 < *(short *)(param_1 + 0x18fe)) || ((short)uVar3 < *(short *)(param_1 + 0x1904))
     ) {
    *(short *)(param_1 + 0x18fe) = *(short *)(param_1 + 0x18fe) + -0x400;
    *(short *)(param_1 + 0x1904) = *(short *)(param_1 + 0x1904) + -0x400;
  }
  else {
    *(ushort *)(param_1 + 0x18fe) = uVar3;
    *(ushort *)(param_1 + 0x1904) = uVar3;
    if (*(char *)(param_1 + 0x14d) < '\x01') {
      *(undefined1 *)(param_1 + 0x14d) = 0x14;
      iVar1 = zz_006dbe0_(param_1,0,1,1);
      if (iVar1 == 0) {
        return 1;
      }
      FUN_800e85f4(param_1,*(undefined1 *)(param_1 + 0x152));
      *(undefined1 *)(param_1 + *(char *)(param_1 + 0x152) + 0x14e) = 1;
      *(undefined1 *)(param_1 + *(char *)(param_1 + 0x152) + 0x150) = 10;
      *(char *)(param_1 + 0x152) = *(char *)(param_1 + 0x152) + '\x01';
      *(byte *)(param_1 + 0x152) = *(byte *)(param_1 + 0x152) & 1;
    }
    else {
      *(char *)(param_1 + 0x14d) = *(char *)(param_1 + 0x14d) + -1;
    }
  }
  return 0;
}



// ==== 800b18e8  FUN_800b18e8 ====

void FUN_800b18e8(int param_1)

{
  FUN_8006cc90((double)FLOAT_8043833c,param_1,2,1,(short *)&DAT_80433ac0);
  return;
}



// ==== 800b1918  FUN_800b1918 ====

undefined4 FUN_800b1918(int param_1)

{
  int iVar1;
  
  if (*(short *)(param_1 + 0x154) == 0) {
    *(undefined2 *)(param_1 + 0x154) = 0x5a;
    iVar1 = zz_006dbe0_(param_1,2,1,1);
    if (iVar1 == 0) {
      return 1;
    }
    zz_00c3be0_(param_1,4);
    zz_00c3be0_(param_1,5);
    zz_00c3be0_(param_1,6);
    zz_00c3be0_(param_1,7);
  }
  else {
    *(short *)(param_1 + 0x154) = *(short *)(param_1 + 0x154) + -1;
  }
  return 0;
}



// ==== 800b19b4  zz_00b19b4_ ====

void zz_00b19b4_(int param_1,undefined1 param_2,int param_3)

{
  undefined1 *puVar1;
  int iVar2;
  
  for (; 0 < param_3; param_3 = param_3 - iVar2) {
    iVar2 = 8;
    if (param_3 < 8) {
      iVar2 = param_3;
    }
    puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,0,iVar2);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x10] = 10;
      puVar1[0x11] = param_2;
      puVar1[0x13] = (char)iVar2;
      *(code **)(puVar1 + 0xc) = FUN_800b1ae8;
      *(code **)(puVar1 + 0x10c) = FUN_800b1d7c;
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
  }
  return;
}



// ==== 800b1ae8  FUN_800b1ae8 ====

void FUN_800b1ae8(int param_1)

{
  (*(code *)(&PTR_FUN_802fc480)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800b1b24  FUN_800b1b24 ====

void FUN_800b1b24(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int *piVar2;
  undefined8 uVar3;
  
  uVar1 = *(char *)(param_9 + 0x13) * 0x30;
  if (uVar1 < 0x81) {
    *(int *)(param_9 + 0x54) = param_9 + 0x144;
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar2 = zz_0006dc8_(uVar1);
    *(int **)(param_9 + 0xdc) = piVar2;
    if (piVar2 != (int *)0x0) {
      *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_9 + 0x54) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined2 *)(param_9 + 0x1c) = 0x30;
    *(undefined2 *)(param_9 + 0x1e) = 0;
    *(code **)(param_9 + 0x100) = FUN_800b1cac;
    uVar3 = zz_0089100_(param_9,1,1);
    FUN_800b1e00(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 800b1bec  FUN_800b1bec ====

void FUN_800b1bec(int param_1)

{
  if (0 < *(short *)(param_1 + 0x1c)) {
    *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  }
  zz_00b20a8_(param_1);
  if ((*(short *)(param_1 + 0x1c) == 0) || (*(short *)(param_1 + 0x1e) == 0)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 800b1c64  FUN_800b1c64 ====

void FUN_800b1c64(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800b1cac  FUN_800b1cac ====

void FUN_800b1cac(int param_1)

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
  double dVar7;
  undefined8 uVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  iVar4 = 0;
  iVar6 = 0;
  iVar5 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar4) break;
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar4) != 0) {
      pfVar3 = (float *)(*(int *)(param_1 + 0x54) + iVar6);
      gnt4_PSMTXTrans_bl((double)*pfVar3,(double)pfVar3[1],(double)pfVar3[2],afStack_48);
      zz_00457d4_('y',afStack_48,afStack_48,*(short *)((int)pfVar3 + 0x2a));
      pfVar1 = afStack_48;
      iVar2 = (int)*(short *)(pfVar3 + 10);
      zz_00457d4_('x',pfVar1,pfVar1,*(short *)(pfVar3 + 10));
      dVar7 = (double)*(float *)(param_1 + 0xb4);
      dVar9 = dVar7;
      uVar8 = zz_0045654_(dVar7,dVar7,dVar7,afStack_48,afStack_48);
      zz_00076d0_(uVar8,dVar7,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),afStack_48,
                  (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
    }
    iVar6 = iVar6 + 0x30;
    iVar5 = iVar5 + 4;
    iVar4 = iVar4 + 1;
  }
  return;
}



// ==== 800b1d7c  FUN_800b1d7c ====

void FUN_800b1d7c(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar1) break;
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar1) != 0) {
      zz_00097b4_(*(int *)(iVar2 + 0xe0),0x44);
    }
    iVar2 = iVar2 + 4;
    iVar1 = iVar1 + 1;
  }
  return;
}



// ==== 800b1e00  FUN_800b1e00 ====

/* WARNING: Removing unreachable block (ram,0x800b208c) */
/* WARNING: Removing unreachable block (ram,0x800b2084) */
/* WARNING: Removing unreachable block (ram,0x800b207c) */
/* WARNING: Removing unreachable block (ram,0x800b2074) */
/* WARNING: Removing unreachable block (ram,0x800b206c) */
/* WARNING: Removing unreachable block (ram,0x800b2064) */
/* WARNING: Removing unreachable block (ram,0x800b205c) */
/* WARNING: Removing unreachable block (ram,0x800b1e40) */
/* WARNING: Removing unreachable block (ram,0x800b1e38) */
/* WARNING: Removing unreachable block (ram,0x800b1e30) */
/* WARNING: Removing unreachable block (ram,0x800b1e28) */
/* WARNING: Removing unreachable block (ram,0x800b1e20) */
/* WARNING: Removing unreachable block (ram,0x800b1e18) */
/* WARNING: Removing unreachable block (ram,0x800b1e10) */

void FUN_800b1e00(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  float fVar3;
  uint uVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined4 *puVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  longlong lVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  double dVar16;
  double dVar17;
  float afStack_e8 [2];
  undefined4 local_e0;
  undefined4 local_dc;
  undefined4 local_d0;
  undefined4 local_cc;
  undefined4 local_c0;
  undefined4 local_bc;
  undefined4 local_b8;
  uint uStack_b4;
  longlong local_b0;
  longlong local_a8;
  
  iVar7 = *(int *)(param_9 + 0x8c);
  dVar17 = (double)FLOAT_80438340;
  dVar12 = (double)FLOAT_80438348;
  dVar14 = (double)FLOAT_8043834c;
  dVar15 = (double)FLOAT_80438350;
  iVar9 = 0;
  dVar16 = (double)FLOAT_80438354;
  iVar8 = param_9;
  dVar13 = DOUBLE_80438358;
  for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    puVar5 = (undefined4 *)(*(int *)(param_9 + 0x54) + iVar9);
    uVar4 = zz_00055fc_();
    fVar3 = *(float *)(&DAT_802fc4d0 + (uVar4 & 0xf) * 4);
    *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | (ushort)(1 << iVar6);
    dVar11 = (double)(*(float *)(param_9 + 0xb4) * (float)(dVar17 * (double)fVar3));
    gnt4_PSMTXCopy_bl((float *)(iVar7 + 0x114),afStack_e8);
    *puVar5 = local_dc;
    puVar5[1] = local_cc;
    puVar5[2] = local_bc;
    uVar4 = zz_00055fc_();
    zz_00457d4_('z',afStack_e8,afStack_e8,(short)(uVar4 << 8));
    uVar4 = zz_00055fc_();
    zz_00457d4_('y',afStack_e8,afStack_e8,(short)(uVar4 << 8));
    uVar4 = zz_00055fc_();
    zz_00457d4_('x',afStack_e8,afStack_e8,(short)(uVar4 << 8));
    puVar5[3] = local_e0;
    puVar5[4] = local_d0;
    puVar5[5] = local_c0;
    gnt4_PSVECNormalize_bl((float *)(puVar5 + 3),(float *)(puVar5 + 3));
    gnt4_PSQUATScale_bl(dVar11,(float *)(puVar5 + 3),(float *)(puVar5 + 3));
    gnt4_PSQUATScale_bl((double)FLOAT_80438344,(float *)(param_9 + 0x38),(float *)(puVar5 + 6));
    puVar5[9] = (float)dVar12;
    uVar4 = zz_00055fc_();
    *(short *)(puVar5 + 10) = (short)(uVar4 << 8);
    uVar4 = zz_00055fc_();
    *(short *)((int)puVar5 + 0x2a) = (short)(uVar4 << 8);
    uVar4 = zz_00055fc_();
    uStack_b4 = uVar4 & 0xff ^ 0x80000000;
    local_b8 = 0x43300000;
    dVar11 = (double)(float)((double)(float)((double)CONCAT44(0x43300000,uStack_b4) - dVar13) /
                            dVar14);
    iVar1 = (int)(dVar15 * dVar11);
    lVar10 = (longlong)iVar1;
    iVar2 = (int)(dVar15 * (double)(float)(dVar16 - dVar11));
    local_a8 = (longlong)iVar2;
    *(short *)(puVar5 + 0xb) = (short)iVar1;
    *(short *)((int)puVar5 + 0x2e) = (short)iVar2;
    if ((uVar4 & 1) != 0) {
      *(short *)(puVar5 + 0xb) = -*(short *)(puVar5 + 0xb);
    }
    if ((uVar4 & 2) != 0) {
      *(short *)((int)puVar5 + 0x2e) = -*(short *)((int)puVar5 + 0x2e);
    }
    local_b0 = lVar10;
    uVar4 = zz_00055fc_();
    zz_0006fb4_(lVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(iVar8 + 0xe0),
                (int)*(char *)(*(char *)(param_9 + 0x11) * 0x10 + -0x7fd03b70 + (uVar4 & 0xf)),
                uVar4 & 0xf,in_r7,in_r8,in_r9,in_r10);
    iVar9 = iVar9 + 0x30;
    iVar8 = iVar8 + 4;
  }
  return;
}



// ==== 800b20a8  zz_00b20a8_ ====

int zz_00b20a8_(int param_1)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  
  iVar2 = 0;
  iVar3 = 0;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar2) break;
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar2) != 0) {
      pfVar1 = (float *)(*(int *)(param_1 + 0x54) + iVar3);
      gnt4_PSVECAdd_bl(pfVar1,pfVar1 + 3,pfVar1);
      gnt4_PSVECAdd_bl(pfVar1 + 3,pfVar1 + 6,pfVar1 + 3);
      dVar4 = (double)FLOAT_80438360;
      pfVar1[4] = pfVar1[4] + pfVar1[9];
      *(short *)(pfVar1 + 10) = *(short *)(pfVar1 + 10) + *(short *)(pfVar1 + 0xb);
      *(short *)((int)pfVar1 + 0x2a) =
           *(short *)((int)pfVar1 + 0x2a) + *(short *)((int)pfVar1 + 0x2e);
      dVar4 = FUN_8003d964(dVar4,param_1,pfVar1);
      if ((double)pfVar1[1] <= dVar4) {
        *(ushort *)(param_1 + 0x1e) = *(ushort *)(param_1 + 0x1e) & ~(ushort)(1 << iVar2);
      }
    }
    iVar3 = iVar3 + 0x30;
    iVar2 = iVar2 + 1;
  }
  return (int)*(short *)(param_1 + 0x1e);
}



// ==== 800b2190  zz_00b2190_ ====

void zz_00b2190_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0xb;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_800b26cc;
    *(code **)(puVar1 + 0x10c) = FUN_800b2ce4;
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
    puVar1[0x164] = 0;
  }
  return;
}



// ==== 800b2290  zz_00b2290_ ====

void zz_00b2290_(double param_1,int param_2,undefined1 param_3,undefined4 *param_4)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = zz_00b2190_(param_2,param_3);
  if (iVar1 != 0) {
    uVar2 = param_4[1];
    *(undefined4 *)(iVar1 + 0x20) = *param_4;
    *(undefined4 *)(iVar1 + 0x24) = uVar2;
    *(undefined4 *)(iVar1 + 0x28) = param_4[2];
    *(float *)(iVar1 + 0xb4) = (float)param_1;
    *(undefined1 *)(iVar1 + 0x164) = 1;
  }
  return;
}



// ==== 800b22f4  zz_00b22f4_ ====

undefined4 zz_00b22f4_(int param_1)

{
  undefined4 uVar1;
  double dVar2;
  double dVar3;
  
  uVar1 = 0;
  if ((FLOAT_80438368 != *(float *)(param_1 + 0x80c)) &&
     (*(float *)(param_1 + 0x80c) < FLOAT_8043836c)) {
    dVar2 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x800));
    if ((double)FLOAT_80438368 < dVar2) {
      dVar3 = 1.0 / SQRT(dVar2);
      dVar3 = DOUBLE_80438370 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80438378);
      dVar3 = DOUBLE_80438370 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80438378);
      dVar2 = (double)(float)(dVar2 * DOUBLE_80438370 * dVar3 *
                                      -(dVar2 * dVar3 * dVar3 - DOUBLE_80438378));
    }
    if (dVar2 < (double)(FLOAT_80438380 * *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0x7fc)))
    goto LAB_800b23ec;
  }
  *(float *)(param_1 + 0x80c) = FLOAT_80438368;
  *(float *)(param_1 + 0x800) = *(float *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x804) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x808) = *(undefined4 *)(param_1 + 0x28);
  uVar1 = zz_00b2190_(param_1,1);
LAB_800b23ec:
  *(float *)(param_1 + 0x80c) = *(float *)(param_1 + 0x80c) + *(float *)(param_1 + 0x768);
  return uVar1;
}



// ==== 800b241c  zz_00b241c_ ====

undefined4 zz_00b241c_(int param_1)

{
  undefined4 uVar1;
  double dVar2;
  double dVar3;
  
  uVar1 = 0;
  if ((FLOAT_80438368 != *(float *)(param_1 + 0x80c)) &&
     (*(float *)(param_1 + 0x80c) < FLOAT_80438384)) {
    dVar2 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x800));
    if ((double)FLOAT_80438368 < dVar2) {
      dVar3 = 1.0 / SQRT(dVar2);
      dVar3 = DOUBLE_80438370 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80438378);
      dVar3 = DOUBLE_80438370 * dVar3 * -(dVar2 * dVar3 * dVar3 - DOUBLE_80438378);
      dVar2 = (double)(float)(dVar2 * DOUBLE_80438370 * dVar3 *
                                      -(dVar2 * dVar3 * dVar3 - DOUBLE_80438378));
    }
    if (dVar2 < (double)(FLOAT_80438380 * *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0x7fc)))
    goto LAB_800b2514;
  }
  *(float *)(param_1 + 0x80c) = FLOAT_80438368;
  *(float *)(param_1 + 0x800) = *(float *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x804) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x808) = *(undefined4 *)(param_1 + 0x28);
  uVar1 = zz_00b2190_(param_1,4);
LAB_800b2514:
  *(float *)(param_1 + 0x80c) = *(float *)(param_1 + 0x80c) + *(float *)(param_1 + 0x768);
  return uVar1;
}



// ==== 800b2544  zz_00b2544_ ====

int zz_00b2544_(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  undefined4 uVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  
  iVar2 = 0;
  if ((FLOAT_80438368 != *(float *)(param_1 + 0x80c)) &&
     (*(float *)(param_1 + 0x80c) < FLOAT_80438388)) {
    dVar3 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x800));
    if ((double)FLOAT_80438368 < dVar3) {
      dVar4 = 1.0 / SQRT(dVar3);
      dVar4 = DOUBLE_80438370 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80438378);
      dVar4 = DOUBLE_80438370 * dVar4 * -(dVar3 * dVar4 * dVar4 - DOUBLE_80438378);
      dVar3 = (double)(float)(dVar3 * DOUBLE_80438370 * dVar4 *
                                      -(dVar3 * dVar4 * dVar4 - DOUBLE_80438378));
    }
    if (dVar3 < (double)(FLOAT_80438380 * *(float *)(param_1 + 0xb4) * *(float *)(param_1 + 0x7fc)))
    goto LAB_800b26a4;
  }
  *(float *)(param_1 + 0x80c) = FLOAT_80438368;
  *(float *)(param_1 + 0x800) = *(float *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x804) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x808) = *(undefined4 *)(param_1 + 0x28);
  if ((param_2 != (undefined4 *)0x0) && (iVar2 = zz_00b2190_(param_1,1), iVar2 != 0)) {
    uVar1 = param_2[1];
    *(undefined4 *)(iVar2 + 0x20) = *param_2;
    *(undefined4 *)(iVar2 + 0x24) = uVar1;
    *(undefined4 *)(iVar2 + 0x28) = param_2[2];
    *(undefined1 *)(iVar2 + 0x164) = 1;
  }
  if ((param_3 != (undefined4 *)0x0) && (iVar2 = zz_00b2190_(param_1,1), iVar2 != 0)) {
    uVar1 = param_3[1];
    *(undefined4 *)(iVar2 + 0x20) = *param_3;
    *(undefined4 *)(iVar2 + 0x24) = uVar1;
    *(undefined4 *)(iVar2 + 0x28) = param_3[2];
    *(undefined1 *)(iVar2 + 0x164) = 1;
  }
LAB_800b26a4:
  *(float *)(param_1 + 0x80c) = *(float *)(param_1 + 0x80c) + *(float *)(param_1 + 0x768);
  return iVar2;
}



// ==== 800b26cc  FUN_800b26cc ====

void FUN_800b26cc(int param_1)

{
  (*(code *)(&PTR_FUN_802fc7ac)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800b2708  FUN_800b2708 ====

void FUN_800b2708(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  short *psVar3;
  undefined4 uVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  double dVar6;
  undefined8 uVar7;
  double dVar8;
  double dVar9;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  dVar6 = DOUBLE_80438390;
  fVar1 = FLOAT_80438368;
  iVar5 = *(int *)(param_1 + 0x8c);
  psVar3 = (short *)(&PTR_DAT_802fc794)[*(char *)(param_1 + 0x11)];
  *(undefined1 *)(param_1 + 0x13) = 0;
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(float *)(param_1 + 0xd4) = fVar1;
  *(float *)(param_1 + 0xd8) =
       (float)((double)CONCAT44(0x43300000,(int)psVar3[1] ^ 0x80000000) - dVar6);
  if (*(char *)(param_1 + 0x164) == '\0') {
    uVar2 = *(undefined4 *)(iVar5 + 0x24);
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(iVar5 + 0x20);
    *(undefined4 *)(param_1 + 0x24) = uVar2;
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(iVar5 + 0x28);
    *(float *)(param_1 + 0xb4) = *(float *)(iVar5 + 0xb4) * *(float *)(iVar5 + 0x7fc);
  }
  (*(code *)(&PTR_LAB_802fc7bc)[*(char *)(param_1 + 0x11)])(param_1);
  dVar6 = FUN_8003d6e4((double)*(float *)(iVar5 + 0x668),iVar5,(float *)(param_1 + 0x20));
  dVar9 = (double)(float)((double)*(float *)(param_1 + 0x24) - dVar6);
  if (dVar9 < (double)FLOAT_80438368) {
    dVar9 = -dVar9;
  }
  dVar8 = (double)*(float *)(iVar5 + 0x668);
  if ((double)(float)(dVar8 * (double)FLOAT_8043838c) <= dVar9) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    *(float *)(param_1 + 0x24) = (float)dVar6;
    uVar4 = 0x1e;
    uVar2 = *(undefined4 *)(param_1 + 0xb4);
    *(undefined4 *)(param_1 + 0x15c) = uVar2;
    *(undefined4 *)(param_1 + 0x158) = uVar2;
    *(undefined4 *)(param_1 + 0x154) = uVar2;
    *(undefined1 *)(param_1 + 0x84) = 0x1e;
    *(code **)(param_1 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_1,0,1);
    zz_0018f88_((int *)(param_1 + 0x144),*(int *)(psVar3 + 2),(float *)(param_1 + 0x58));
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) * *(float *)(param_1 + 0x154);
    *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * *(float *)(param_1 + 0x158);
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) * *(float *)(param_1 + 0x15c);
    uVar7 = zz_0019338_((int *)(param_1 + 0x14c),*(int *)(psVar3 + 4),(float *)(param_1 + 0x160));
    zz_0006fb4_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb374,
                *(int *)(param_1 + 0xe0),(int)*psVar3,uVar4,in_r7,in_r8,in_r9,in_r10);
    zz_0007cac_((double)*(float *)(param_1 + 0x160),*(int *)(param_1 + 0xe0));
    *(undefined1 *)(param_1 + 0x82) = 1;
  }
  return;
}



// ==== 800b2924  FUN_800b2924 ====

void FUN_800b2924(int param_1)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  
  *(undefined1 *)(param_1 + 0x12) = 1;
  *(undefined2 *)(param_1 + 0x74) = 0;
  *(undefined2 *)(param_1 + 0x70) = 0;
  uVar2 = zz_00055fc_();
  *(short *)(param_1 + 0x72) = (short)(uVar2 << 8);
  if (*(char *)(param_1 + 0x164) == '\0') {
    iVar3 = *(int *)(param_1 + 0x8c);
    gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
    zz_00457d4_('y',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(iVar3 + 0x5ae))
    ;
    fVar1 = FLOAT_80438398;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x11c);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 300);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x13c);
    gnt4_PSQUATScale_bl((double)(fVar1 * *(float *)(iVar3 + 0xb4) * *(float *)(iVar3 + 0x7fc)),
                        (float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECSubtract_bl
              ((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  }
  return;
}



// ==== 800b2a04  FUN_800b2a04 ====

void FUN_800b2a04(int param_1)

{
  uint uVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0x12) = 1;
  *(undefined2 *)(param_1 + 0x74) = 0;
  *(undefined2 *)(param_1 + 0x70) = 0;
  uVar1 = zz_00055fc_();
  *(short *)(param_1 + 0x72) = (short)(uVar1 << 8);
  if (*(char *)(param_1 + 0x164) == '\0') {
    iVar2 = *(int *)(param_1 + 0x8c);
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar2 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),(float *)&DAT_802fc7d4,
               (float *)(param_1 + 0x20));
    *(undefined4 *)(param_1 + 0xb4) = *(undefined4 *)(iVar2 + 0xb4);
  }
  return;
}



// ==== 800b2a90  FUN_800b2a90 ====

void FUN_800b2a90(int param_1)

{
  uint uVar1;
  
  *(undefined1 *)(param_1 + 0x12) = 1;
  *(undefined2 *)(param_1 + 0x74) = 0;
  *(undefined2 *)(param_1 + 0x70) = 0;
  uVar1 = zz_00055fc_();
  *(short *)(param_1 + 0x72) = (short)(uVar1 << 8);
  return;
}



// ==== 800b2ad8  FUN_800b2ad8 ====

void FUN_800b2ad8(int param_1)

{
  uint uVar1;
  
  *(undefined1 *)(param_1 + 0x12) = 1;
  *(undefined2 *)(param_1 + 0x74) = 0;
  *(undefined2 *)(param_1 + 0x70) = 0;
  uVar1 = zz_00055fc_();
  *(short *)(param_1 + 0x72) = (short)(uVar1 << 8);
  return;
}



// ==== 800b2b20  FUN_800b2b20 ====

void FUN_800b2b20(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  char cVar2;
  undefined *puVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar4;
  undefined8 uVar5;
  
  *(float *)(param_9 + 0xd4) =
       *(float *)(param_9 + 0xd4) + *(float *)(*(int *)(param_9 + 0x90) + 0x768);
  fVar1 = FLOAT_80438368;
  if (*(float *)(param_9 + 0xd8) <= *(float *)(param_9 + 0xd4)) {
    if ((int)*(char *)(param_9 + 0x13) < *(char *)(param_9 + 0x12) + -1) {
      cVar2 = *(char *)(param_9 + 0x13) + '\x01';
      puVar3 = (&PTR_DAT_802fc794)[*(char *)(param_9 + 0x11)];
      *(char *)(param_9 + 0x13) = cVar2;
      psVar4 = (short *)(puVar3 + cVar2 * 0xc);
      *(float *)(param_9 + 0xd4) = fVar1;
      *(float *)(param_9 + 0xd8) =
           (float)((double)CONCAT44(0x43300000,(int)psVar4[1] ^ 0x80000000) - DOUBLE_80438390);
      *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(param_9 + 0x58);
      *(undefined4 *)(param_9 + 0x158) = *(undefined4 *)(param_9 + 0x5c);
      *(undefined4 *)(param_9 + 0x15c) = *(undefined4 *)(param_9 + 0x60);
      zz_0018f88_((int *)(param_9 + 0x144),*(int *)(psVar4 + 2),(float *)(param_9 + 0x58));
      uVar5 = zz_0019338_((int *)(param_9 + 0x14c),*(int *)(psVar4 + 4),(float *)(param_9 + 0x160));
      zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                  *(int *)(param_9 + 0xe0),(int)*psVar4,puVar3,in_r7,in_r8,in_r9,in_r10);
    }
    else {
      *(undefined1 *)(param_9 + 0x18) = 2;
    }
  }
  zz_0019178_((double)*(float *)(param_9 + 0xd4),(int *)(param_9 + 0x144),(float *)(param_9 + 0x58))
  ;
  *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x58) * *(float *)(param_9 + 0x154);
  *(float *)(param_9 + 0x5c) = *(float *)(param_9 + 0x5c) * *(float *)(param_9 + 0x158);
  *(float *)(param_9 + 0x60) = *(float *)(param_9 + 0x60) * *(float *)(param_9 + 0x15c);
  zz_0019450_((double)*(float *)(param_9 + 0xd4),(int *)(param_9 + 0x14c),(float *)(param_9 + 0x160)
             );
  zz_0007cac_((double)*(float *)(param_9 + 0x160),*(int *)(param_9 + 0xe0));
  return;
}



// ==== 800b2cc4  FUN_800b2cc4 ====

void FUN_800b2cc4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800b2ce4  FUN_800b2ce4 ====

void FUN_800b2ce4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x24);
  return;
}



// ==== 800b2d24  zz_00b2d24_ ====

void zz_00b2d24_(undefined4 param_1,undefined2 *param_2)

{
  param_2[0xb] = 0;
  param_2[10] = 0;
  param_2[9] = 0;
  param_2[8] = 0;
  param_2[3] = 0;
  param_2[2] = 0;
  param_2[1] = 0;
  *param_2 = 0;
  *(undefined1 *)((int)param_2 + 0x1b) = 0;
  *(undefined1 *)(param_2 + 0xd) = 0;
  *(undefined1 *)((int)param_2 + 0x19) = 0;
  *(undefined1 *)(param_2 + 0xc) = 0;
  return;
}



// ==== 800b2d5c  zz_00b2d5c_ ====

void zz_00b2d5c_(int param_1,short *param_2)

{
  byte bVar1;
  short sVar2;
  short *psVar3;
  int iVar4;
  int iVar5;
  short sVar6;
  char cVar7;
  int iVar8;
  
  bVar1 = *(byte *)(param_1 + 0x6e9);
  if (bVar1 != 0) {
    if (((int)(char)(bVar1 & 0xc0) & 0x80U) != 0) {
      *(byte *)(param_2 + 0xc) = bVar1 & 0x3f;
    }
    if (((int)(char)(bVar1 & 0xc0) & 0x40U) != 0) {
      *(byte *)((int)param_2 + 0x19) = bVar1 & 0x3f;
    }
    *(undefined1 *)(param_1 + 0x6e9) = 0;
  }
  iVar4 = 0;
  iVar8 = 2;
  psVar3 = param_2;
  do {
    cVar7 = *(char *)((int)param_2 + iVar4 + 0x18);
    if (cVar7 == *(char *)((int)param_2 + iVar4 + 0x1a)) {
      sVar2 = psVar3[8];
      sVar6 = *psVar3 - psVar3[4];
      if ((int)sVar2 < (int)(short)(*psVar3 - psVar3[4])) {
        sVar6 = sVar2;
      }
      iVar5 = -(int)sVar2;
      if (sVar6 < iVar5) {
        sVar6 = (short)iVar5;
      }
      psVar3[4] = psVar3[4] + sVar6;
      sVar2 = psVar3[9];
      sVar6 = psVar3[1] - psVar3[5];
      if ((int)sVar2 < (int)(short)(psVar3[1] - psVar3[5])) {
        sVar6 = sVar2;
      }
      iVar5 = -(int)sVar2;
      if (sVar6 < iVar5) {
        sVar6 = (short)iVar5;
      }
      psVar3[5] = psVar3[5] + sVar6;
    }
    else {
      if (cVar7 == '\x02') {
        cVar7 = '\x03';
        psVar3[4] = sRam802fd210;
        psVar3[5] = sRam802fd212;
        *(undefined1 *)((int)param_2 + iVar4 + 0x18) = 3;
      }
      iVar5 = cVar7 * 8;
      *psVar3 = *(short *)(&DAT_802fd200 + iVar5);
      psVar3[1] = *(short *)(&DAT_802fd202 + iVar5);
      psVar3[8] = *(short *)(&DAT_802fd204 + iVar5);
      psVar3[9] = *(short *)(iVar5 + -0x7fd02dfa);
    }
    psVar3 = psVar3 + 2;
    iVar4 = iVar4 + 1;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  *(undefined1 *)(param_2 + 0xd) = *(undefined1 *)(param_2 + 0xc);
  *(undefined1 *)((int)param_2 + 0x1b) = *(undefined1 *)((int)param_2 + 0x19);
  *(short *)(param_1 + 0x1950) = -param_2[6];
  *(short *)(param_1 + 0x1956) = -param_2[7];
  *(short *)(param_1 + 0x195c) = param_2[4];
  *(short *)(param_1 + 0x1962) = param_2[5];
  return;
}



// ==== 800b2ff4  FUN_800b2ff4 ====

void FUN_800b2ff4(int param_1)

{
  zz_00b2d24_(param_1,(undefined2 *)(param_1 + 0x144));
  return;
}



