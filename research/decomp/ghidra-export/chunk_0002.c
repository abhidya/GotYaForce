// ==== 80017610  zz_0017610_ ====

/* WARNING: Removing unreachable block (ram,0x800176ec) */
/* WARNING: Removing unreachable block (ram,0x80017620) */

void zz_0017610_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  undefined4 extraout_r4;
  float *pfVar4;
  float *pfVar5;
  int iVar6;
  int *piVar7;
  double dVar8;
  undefined8 uVar9;
  double dVar10;
  
  fVar2 = FLOAT_80436d34;
  fVar1 = FLOAT_80436bc4;
  dVar8 = (double)FLOAT_80436bc4;
  *(float *)(param_9 + 0x20) = FLOAT_80436bc4;
  dVar10 = DOUBLE_80436bd0;
  *(float *)(param_9 + 0x24) = fVar1;
  piVar7 = (int *)(param_9 + 0x144);
  pfVar5 = (float *)0x0;
  *(float *)(param_9 + 0x28) = fVar2;
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(undefined2 *)(param_9 + 0x1e) = 0;
  *(undefined4 *)(param_9 + 0x54) = DAT_803bb34c;
  iVar6 = param_9;
  do {
    pfVar4 = pfVar5;
    zz_0006fb4_(dVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0x54),*piVar7,(int)pfVar5,param_12,param_13,param_14,param_15,
                param_16);
    uVar9 = zz_00087d4_((double)(float)((double)CONCAT44(0x43300000,
                                                         (int)*(short *)(param_9 + 0x1c) ^
                                                         0x80000000) - dVar10),param_2,param_3,
                        param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x54),*piVar7,
                        pfVar4,param_12,param_13,param_14,param_15,param_16);
    uVar9 = zz_0007c30_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar7,
                        extraout_r4,pfVar4,param_12,param_13,param_14,param_15,param_16);
    dVar8 = zz_000850c_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar7,0,
                        pfVar4,param_12,param_13,param_14,param_15,param_16);
    *(float *)(iVar6 + 0xd4) = (float)dVar8;
    iVar3 = 1 << (int)pfVar5;
    pfVar5 = (float *)((int)pfVar5 + 1);
    piVar7 = piVar7 + 1;
    iVar6 = iVar6 + 4;
    *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) | (ushort)iVar3;
  } while ((int)pfVar5 < 2);
  *(undefined1 *)(param_9 + 0x82) = 0x11;
  return;
}



// ==== 80017708  zz_0017708_ ====

void zz_0017708_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined8 uVar7;
  
  iVar3 = 0;
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 == '\x01') {
    if ((*(short *)(PTR_DAT_80433934 + 8) < 0x22) || ('\x01' < (char)PTR_DAT_80433934[1])) {
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      sVar2 = *(short *)(param_9 + 0x1c) + 1;
      *(short *)(param_9 + 0x1c) = sVar2;
      if (0x1c < sVar2) {
        *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
        *(undefined2 *)(param_9 + 0x1c) = 0x1d;
      }
      iVar3 = 1;
    }
  }
  else if (cVar1 < '\x03') {
    iVar3 = 1;
  }
  if (iVar3 != 0) {
    piVar6 = (int *)(param_9 + 0x144);
    iVar4 = 0;
    iVar5 = param_9;
    do {
      uVar7 = zz_0007c30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar6,
                          iVar3,param_11,param_12,param_13,param_14,param_15,param_16);
      iVar3 = 0;
      param_1 = zz_0008590_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*piVar6,0,
                            param_11,param_12,param_13,param_14,param_15,param_16);
      if ((double)*(float *)(iVar5 + 0xd4) <= param_1) {
        *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) & ~(ushort)(1 << iVar4);
      }
      iVar4 = iVar4 + 1;
      iVar5 = iVar5 + 4;
      piVar6 = piVar6 + 1;
    } while (iVar4 < 2);
    if (*(short *)(param_9 + 0x1e) == 0) {
      *(undefined1 *)(param_9 + 0x18) = 2;
    }
  }
  return;
}



// ==== 8001783c  zz_001783c_ ====

void zz_001783c_(int param_1)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = 0;
  piVar2 = (int *)(param_1 + 0x144);
  do {
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar1) != 0) {
      zz_0009958_(*piVar2,2);
    }
    iVar1 = iVar1 + 1;
    piVar2 = piVar2 + 1;
  } while (iVar1 < 2);
  return;
}



// ==== 800178b4  zz_00178b4_ ====

void zz_00178b4_(void)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x38,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x83] = 0x14;
    *(undefined **)(puVar1 + 0xc) = &DAT_80017914;
    *(undefined4 *)(puVar1 + 0x10c) = 0;
  }
  zz_0011abc_();
  return;
}



// ==== 80017918  FUN_80017918 ====

void FUN_80017918(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  undefined8 uVar1;
  
  zz_008c098_();
  if ((char)PTR_DAT_80433930[1] < '\x01') {
    uVar1 = zz_002a5f4_(0,0,0,0xff);
    gnt4_memset(PTR_DAT_8043393c,0,0x20);
    if ((char)PTR_DAT_80433930[1] < '\0') {
      *PTR_DAT_8043393c = 1;
    }
    else {
      *PTR_DAT_8043393c = 0;
      zz_01c78b0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    }
    PTR_DAT_80433930[1] = 1;
    set_global_menu_mode(0);
  }
  PTR_DAT_8043393c[0x14] = 0;
  uVar1 = (*(code *)(&PTR_FUN_802c4a00)[(char)*PTR_DAT_8043393c])();
  zz_0018098_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  zz_0027ae8_();
  return;
}



// ==== 800179e8  FUN_800179e8 ====

void FUN_800179e8(void)

{
  int iVar1;
  
  iVar1 = zz_01c7908_();
  if (iVar1 != 0) {
    *PTR_DAT_80433930 = 2;
    PTR_DAT_80433930[1] = 0xff;
  }
  return;
}



// ==== 80017a28  FUN_80017a28 ====

void FUN_80017a28(void)

{
  (*(code *)(&PTR_LAB_802c4a0c)[(char)PTR_DAT_8043393c[1]])();
  return;
}



// ==== 80017a78  FUN_80017a78 ====

void FUN_80017a78(void)

{
  (*(code *)(&PTR_FUN_802c4a1c)[(char)PTR_DAT_8043393c[2]])();
  return;
}



// ==== 80017ab8  FUN_80017ab8 ====

void FUN_80017ab8(void)

{
  char cVar1;
  int iVar2;
  
  cVar1 = PTR_DAT_8043393c[3];
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    PTR_DAT_8043393c[3] = cVar1 + '\x01';
    PTR_DAT_80433930[0x40] = 1;
  }
  iVar2 = zz_000a3c4_();
  if (iVar2 == 0) {
    zz_0018238_();
    zz_0018288_();
    zz_0027c1c_();
    PTR_DAT_8043393c[2] = PTR_DAT_8043393c[2] + '\x01';
    *(undefined2 *)(PTR_DAT_8043393c + 0xc) = 0xe40;
    *(undefined2 *)(PTR_DAT_8043393c + 10) = 0;
    *(undefined2 *)(PTR_DAT_8043393c + 0xe) = 0;
    PTR_DAT_8043393c[0x11] = 0;
    PTR_DAT_8043393c[0x10] = 1;
    zz_0027aac_(0,0x3c,0);
  }
  return;
}



// ==== 80017b78  FUN_80017b78 ====

void FUN_80017b78(void)

{
  short sVar1;
  
  zz_0028264_();
  if (*PTR_DAT_80433934 == '\x02') {
    zz_0017cc4_();
    if (PTR_DAT_8043393c[0x11] != '\0') {
      zz_008c0dc_(&DAT_80018234);
    }
  }
  sVar1 = *(short *)(PTR_DAT_8043393c + 0xc);
  *(short *)(PTR_DAT_8043393c + 0xc) = sVar1 + -1;
  if ((short)(sVar1 + -1) < 1) {
    PTR_DAT_8043393c[2] = PTR_DAT_8043393c[2] + '\x01';
    PTR_DAT_8043393c[3] = 0;
    zz_0027aac_(0,0x3c,1);
    zz_00f07c4_();
    zz_00f0920_(0);
    zz_00e9b60_((double)FLOAT_80436d38,2,0x3c,2);
  }
  return;
}



// ==== 80017c2c  FUN_80017c2c ====

void FUN_80017c2c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  undefined8 uVar4;
  
  cVar1 = PTR_DAT_8043393c[3];
  if (cVar1 == '\x01') {
    iVar3 = zz_000a3c4_();
    if (iVar3 == 0) {
      uVar4 = zz_0018270_();
      PTR_DAT_8043393c[1] = 3;
      PTR_DAT_8043393c[2] = 0;
      puVar2 = PTR_DAT_8043393c;
      PTR_DAT_8043393c[0x10] = 0;
      zz_00282c0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar2,3,param_11,
                  param_12,param_13,param_14,param_15,param_16);
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_0028264_();
    iVar3 = zz_0027adc_();
    if (iVar3 == 0) {
      PTR_DAT_8043393c[3] = PTR_DAT_8043393c[3] + '\x01';
    }
  }
  return;
}



// ==== 80017cc4  zz_0017cc4_ ====

void zz_0017cc4_(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(short *)(PTR_DAT_8043393c + 10) * 4;
  if (*(short *)(PTR_DAT_8043393c + 0xe) == 0) {
    *(short *)(PTR_DAT_8043393c + 10) = *(short *)(PTR_DAT_8043393c + 10) + 1;
    iVar2 = *(int *)(&DAT_802c4a28 + iVar1);
    if (iVar2 == 2) {
      PTR_DAT_8043393c[0x11] = 0;
      zz_008b010_(0);
    }
    else if (iVar2 < 2) {
      if (iVar2 == 0) {
        *(short *)(PTR_DAT_8043393c + 0xe) = (short)*(undefined4 *)(&DAT_802c4a2c + iVar1);
        *(short *)(PTR_DAT_8043393c + 10) = *(short *)(PTR_DAT_8043393c + 10) + 1;
      }
      else if (-1 < iVar2) {
        zz_008b010_(1);
      }
    }
    else if (iVar2 == 4) {
      *(undefined2 *)(PTR_DAT_8043393c + 0xc) = 1;
    }
    else if (iVar2 < 4) {
      PTR_DAT_8043393c[0x11] = (char)*(undefined4 *)(&DAT_802c4a2c + iVar1);
      *(short *)(PTR_DAT_8043393c + 10) = *(short *)(PTR_DAT_8043393c + 10) + 1;
    }
  }
  else {
    *(short *)(PTR_DAT_8043393c + 0xe) = *(short *)(PTR_DAT_8043393c + 0xe) + -1;
  }
  return;
}



// ==== 80017dbc  FUN_80017dbc ====

void FUN_80017dbc(void)

{
  (*(code *)(&PTR_FUN_802c4ad4)[(char)PTR_DAT_8043393c[2]])();
  return;
}



// ==== 80017dfc  FUN_80017dfc ====

void FUN_80017dfc(void)

{
  char cVar1;
  int iVar2;
  
  cVar1 = PTR_DAT_8043393c[3];
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    PTR_DAT_8043393c[3] = cVar1 + '\x01';
    PTR_DAT_80433930[0x40] = 1;
  }
  iVar2 = zz_000a3c4_();
  if (iVar2 == 0) {
    zz_0018494_();
    zz_0027c1c_();
    PTR_DAT_8043393c[2] = PTR_DAT_8043393c[2] + '\x01';
    *(undefined2 *)(PTR_DAT_8043393c + 0xc) = 0xe40;
    PTR_DAT_8043393c[0x10] = 1;
    zz_0027aac_(0,0x3c,0);
  }
  return;
}



// ==== 80017e9c  FUN_80017e9c ====

void FUN_80017e9c(void)

{
  undefined4 *puVar1;
  short sVar2;
  undefined *puVar3;
  
  zz_0028264_();
  puVar3 = PTR_DAT_80433934;
  if (*PTR_DAT_80433934 == '\x02') {
    puVar1 = (undefined4 *)(PTR_DAT_80433934 + 0x114);
    *(undefined4 *)(PTR_DAT_80433934 + 0x11c) = *puVar1;
    *(undefined4 *)(puVar3 + 0x118) = *puVar1;
    puVar3 = PTR_DAT_80433934;
    puVar1 = (undefined4 *)(PTR_DAT_80433934 + 0x150);
    *(undefined4 *)(PTR_DAT_80433934 + 0x158) = *puVar1;
    *(undefined4 *)(puVar3 + 0x154) = *puVar1;
    puVar3 = PTR_DAT_80433934;
    puVar1 = (undefined4 *)(PTR_DAT_80433934 + 0x18c);
    *(undefined4 *)(PTR_DAT_80433934 + 0x194) = *puVar1;
    *(undefined4 *)(puVar3 + 400) = *puVar1;
    puVar3 = PTR_DAT_80433934;
    puVar1 = (undefined4 *)(PTR_DAT_80433934 + 0x1c8);
    *(undefined4 *)(PTR_DAT_80433934 + 0x1d0) = *puVar1;
    *(undefined4 *)(puVar3 + 0x1cc) = *puVar1;
    *(undefined4 *)(PTR_DAT_80433934 + 0x4c) = *(undefined4 *)(PTR_DAT_80433934 + 0x48);
    if ((DAT_803c727c & 0x1000) != 0) {
      *(undefined2 *)(PTR_DAT_8043393c + 0xc) = 1;
    }
  }
  sVar2 = *(short *)(PTR_DAT_8043393c + 0xc);
  *(short *)(PTR_DAT_8043393c + 0xc) = sVar2 + -1;
  if ((short)(sVar2 + -1) < 1) {
    PTR_DAT_8043393c[2] = PTR_DAT_8043393c[2] + '\x01';
    PTR_DAT_8043393c[3] = 0;
    zz_0027aac_(0,0x3c,1);
    zz_00f07c4_();
    zz_00f0920_(0);
    zz_00e9b60_((double)FLOAT_80436d38,2,0x3c,2);
  }
  return;
}



// ==== 80017f94  FUN_80017f94 ====

void FUN_80017f94(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined *puVar2;
  int iVar3;
  
  cVar1 = PTR_DAT_8043393c[3];
  if (cVar1 == '\x01') {
    iVar3 = zz_000a3c4_();
    if (iVar3 == 0) {
      PTR_DAT_8043393c[1] = 3;
      PTR_DAT_8043393c[2] = 0;
      puVar2 = PTR_DAT_8043393c;
      PTR_DAT_8043393c[0x10] = 0;
      zz_00282c0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,puVar2,3,param_11,
                  param_12,param_13,param_14,param_15,param_16);
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    zz_0028264_();
    iVar3 = zz_0027adc_();
    if (iVar3 == 0) {
      PTR_DAT_8043393c[3] = PTR_DAT_8043393c[3] + '\x01';
    }
  }
  return;
}



// ==== 8001805c  FUN_8001805c ====

void FUN_8001805c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  *PTR_DAT_8043393c = 0;
  *(short *)(PTR_DAT_8043393c + 8) = *(short *)(PTR_DAT_8043393c + 8) + 1;
  zz_01c78b0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
  return;
}



// ==== 80018098  zz_0018098_ ====

undefined4
zz_0018098_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
           undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  char cVar1;
  int iVar2;
  undefined *puVar3;
  int in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 extraout_f1;
  undefined8 uVar4;
  
  puVar3 = PTR_DAT_8043393c;
  if (*PTR_DAT_80433930 != '\x01') {
    return 0;
  }
  cVar1 = PTR_DAT_8043393c[7];
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if (cVar1 < '\x03') {
        iVar2 = zz_000a07c_();
        if (iVar2 != 0) {
          return 0;
        }
        zz_008c098_();
        zz_007fe60_();
      }
      goto LAB_800181d4;
    }
    if (cVar1 < '\0') goto LAB_800181d4;
    for (in_r6 = 0; in_r6 < 4; in_r6 = in_r6 + 1) {
      if (((&DAT_803c7284)[in_r6 * 8] & 0x1000) != 0) {
        in_r6 = 4;
      }
    }
    if (in_r6 == 4) {
      return 0;
    }
    if (PTR_DAT_8043393c[0x10] == '\0') {
      iVar2 = zz_000a3c4_();
      if ((iVar2 != 0) || (iVar2 = zz_000a07c_(), iVar2 != 0)) {
        PTR_DAT_8043393c[7] = 2;
        return 0;
      }
      if (PTR_DAT_8043393c[0x14] == '\0') {
        zz_008c098_();
        zz_007fe60_();
      }
      goto LAB_800181d4;
    }
    PTR_DAT_8043393c[7] = PTR_DAT_8043393c[7] + '\x01';
  }
  iVar2 = zz_000a07c_();
  if ((iVar2 != 0) || (iVar2 = zz_000a3c4_(), iVar2 != 0)) {
    return 0;
  }
  uVar4 = zz_008c098_();
  zz_00282c0_(extraout_f1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              (int)((ulonglong)uVar4 >> 0x20),(int)uVar4,puVar3,in_r6,in_r7,in_r8,in_r9,in_r10);
LAB_800181d4:
  PTR_DAT_80433930[0x40] = 0;
  cVar1 = PTR_DAT_8043393c[0x14];
  *PTR_DAT_80433930 = 2;
  PTR_DAT_80433930[1] = (char)((byte)((uint)-(int)cVar1 >> 0x18) | cVar1 >> 7) >> 7;
  PTR_DAT_80433930[0x32] = 0;
  zz_0027c1c_();
  zz_002affc_();
  zz_007fd5c_();
  return 1;
}



// ==== 80018238  zz_0018238_ ====

void zz_0018238_(void)

{
  PTR_DAT_8043393c[0x12] = DAT_804360c7;
  PTR_DAT_8043393c[0x13] = DAT_804360c6;
  zz_00055e0_();
  return;
}



// ==== 80018270  zz_0018270_ ====

void zz_0018270_(void)

{
  DAT_804360c7 = PTR_DAT_8043393c[0x12];
  DAT_804360c6 = PTR_DAT_8043393c[0x13];
  return;
}



// ==== 80018288  zz_0018288_ ====

void zz_0018288_(void)

{
  undefined2 *puVar1;
  int iVar2;
  undefined2 *puVar3;
  int iVar4;
  int iVar5;
  
  gnt4_memset(PTR_DAT_80433934,0,0x18b8);
  iVar5 = 0;
  puVar3 = (undefined2 *)0x802c4ae0;
  iVar2 = 0;
  iVar4 = 0;
  do {
    if (iVar2 < 4) {
      PTR_DAT_80433934[iVar2 + 0xcb] = (byte)iVar2 & 1;
      PTR_DAT_80433934[iVar2 + 0x20] = (byte)iVar2;
      PTR_DAT_80433934[iVar2 + 0x32] = 0;
      puVar1 = (undefined2 *)(PTR_DAT_80433934 + iVar4 + 0x1e8);
      *puVar1 = *puVar3;
      *(undefined1 *)(puVar1 + 1) = 0;
      *(undefined1 *)(puVar1 + 0xb) = 0;
      *(undefined1 *)((int)puVar1 + 0x17) = 0;
      *(undefined1 *)(puVar1 + 0xc) = 0;
      puVar1 = (undefined2 *)(PTR_DAT_80433934 + iVar4 + 0x204);
      *puVar1 = puVar3[1];
      *(undefined1 *)(puVar1 + 1) = 0;
      *(undefined1 *)(puVar1 + 0xb) = 0;
      *(undefined1 *)((int)puVar1 + 0x17) = 0;
      *(undefined1 *)(puVar1 + 0xc) = 0;
      puVar1 = (undefined2 *)(PTR_DAT_80433934 + iVar4 + 0x220);
      *puVar1 = puVar3[2];
      *(undefined1 *)(puVar1 + 1) = 0;
      *(undefined1 *)(puVar1 + 0xb) = 0;
      *(undefined1 *)((int)puVar1 + 0x17) = 0;
      *(undefined1 *)(puVar1 + 0xc) = 0;
      puVar1 = (undefined2 *)(PTR_DAT_80433934 + iVar4 + 0x23c);
      *puVar1 = puVar3[3];
      *(undefined1 *)(puVar1 + 1) = 0;
      *(undefined1 *)(puVar1 + 0xb) = 0;
      *(undefined1 *)((int)puVar1 + 0x17) = 0;
      *(undefined1 *)(puVar1 + 0xc) = 0;
      PTR_DAT_80433934[iVar2 + 0x5a] = 4;
      PTR_DAT_80433934[iVar2 + 0x54] = 0;
      PTR_DAT_80433934[iVar2 + 0x15c8] = 0;
      zz_0068424_(iVar2,(undefined2 *)(PTR_DAT_80433934 + iVar5 + 0x10),
                  PTR_DAT_80433934 + iVar2 + 0xa0);
      PTR_DAT_80433934[iVar2 + 0xc0] = 0xff;
    }
    else {
      *(undefined2 *)(PTR_DAT_80433934 + iVar5 + 0x10) = 0xffff;
    }
    iVar2 = iVar2 + 1;
    iVar4 = iVar4 + 0x348;
    puVar3 = puVar3 + 4;
    iVar5 = iVar5 + 2;
  } while (iVar2 < 6);
  PTR_DAT_80433934[0x1c] = 0;
  PTR_DAT_80433934[0x1d] = 0;
  PTR_DAT_80433934[0x1e] = 0;
  PTR_DAT_80433934[0x15da] = 4;
  PTR_DAT_80433934[0x53] = 2;
  *(undefined2 *)(PTR_DAT_80433934 + 0x46) = 0;
  PTR_DAT_80433934[0xf4] = 0;
  PTR_DAT_80433934[0x130] = 1;
  *(undefined2 *)(PTR_DAT_80433934 + 0x110) = 0;
  *(undefined2 *)(PTR_DAT_80433934 + 0x14c) = 0;
  PTR_DAT_80433934[0xc0] = 0;
  PTR_DAT_80433930[2] = 0;
  PTR_DAT_80433930[3] = 0;
  PTR_DAT_80433930[0x29] = 0;
  return;
}



// ==== 80018494  zz_0018494_ ====

void zz_0018494_(void)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  int iVar6;
  
  gnt4_memset(PTR_DAT_80433934,0,0x18b8);
  iVar6 = 0;
  iVar5 = 0;
  *(undefined2 *)(PTR_DAT_8043393c + 0xc) = 0;
  do {
    if (iVar5 < 4) {
      PTR_DAT_80433934[iVar5 + 0xcb] = (byte)iVar5 & 1;
      PTR_DAT_80433934[iVar5 + 0x20] = (byte)iVar5;
      PTR_DAT_80433934[iVar5 + 0x32] = 7;
      zz_0018678_(iVar5,8);
    }
    else {
      *(undefined2 *)(PTR_DAT_80433934 + iVar6 + 0x10) = 0xffff;
    }
    iVar5 = iVar5 + 1;
    iVar6 = iVar6 + 2;
  } while (iVar5 < 6);
  PTR_DAT_80433930[2] = 0;
  PTR_DAT_80433930[3] = 0;
  PTR_DAT_80433930[0x29] = 0;
  PTR_DAT_80433930[0x32] = 2;
  uVar2 = zz_00055fc_();
  PTR_DAT_80433934[0x1c] = (&DAT_802c4b00)[uVar2 % 0xd];
  uVar2 = zz_00055fc_();
  PTR_DAT_80433934[0x1d] = (char)uVar2 + (char)(uVar2 / 3) * -3;
  iVar5 = LooseBallAnims__GetDesperationInfo_unsigned((int)(char)PTR_DAT_80433934[0x1c]);
  uVar2 = zz_00055fc_();
  cVar1 = '\x10';
  iVar5 = uVar2 - (uVar2 / (iVar5 + 1U)) * (iVar5 + 1U);
  if (iVar5 != 0) {
    cVar1 = (char)iVar5 + -1;
  }
  PTR_DAT_80433934[0x1e] = cVar1;
  iVar5 = 0;
  PTR_DAT_80433934[0x15da] = 4;
  PTR_DAT_80433934[0x53] = 2;
  *(undefined2 *)(PTR_DAT_80433934 + 0x46) = 0;
  PTR_DAT_80433934[0xc0] = 0;
  for (iVar6 = 0; iVar6 < (char)PTR_DAT_80433934[0x53]; iVar6 = iVar6 + 1) {
    iVar3 = iVar5 + 0xf4;
    iVar5 = iVar5 + 0x3c;
    puVar4 = PTR_DAT_80433934 + iVar3;
    *puVar4 = (char)iVar6;
    *(undefined2 *)(puVar4 + 0x1c) = 0;
    *(undefined4 *)(puVar4 + 0x20) = 0x7fffffff;
  }
  zz_000685c_(1);
  zz_00064d4_();
  zz_0006abc_();
  return;
}



// ==== 80018678  zz_0018678_ ====

void zz_0018678_(int param_1,int param_2)

{
  bool bVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  short *psVar5;
  undefined2 *puVar6;
  int iVar7;
  int iVar8;
  
  iVar7 = 0;
  iVar8 = 0;
  do {
    if (param_2 <= iVar7) {
      PTR_DAT_80433934[param_1 + 0x5a] = (char)param_2;
      PTR_DAT_80433934[param_1 + 0x54] = 0;
      PTR_DAT_80433934[param_1 + 0x15c8] = 0;
      zz_0068424_(param_1,(undefined2 *)(PTR_DAT_80433934 + param_1 * 2 + 0x10),
                  PTR_DAT_80433934 + param_1 + 0xa0);
      PTR_DAT_80433934[iVar7 + 0xc0] = 0xff;
      return;
    }
    do {
      do {
        do {
          do {
            uVar2 = zz_00055fc_();
            uVar2 = uVar2 & 0xf;
            uVar3 = zz_00055fc_();
            uVar3 = uVar3 - (uVar3 / (byte)(&DAT_802c3460)[uVar2]) *
                            (uint)(byte)(&DAT_802c3460)[uVar2];
          } while (uVar2 == 4);
          uVar4 = zz_0068570_(uVar2,uVar3);
        } while (uVar4 == 0);
        bVar1 = false;
        uVar3 = uVar3 | uVar2 << 8;
        psVar5 = &DAT_802c4b10;
        while( true ) {
          if (*psVar5 < 0) break;
          if (uVar3 == (int)*psVar5) {
            bVar1 = true;
            break;
          }
          psVar5 = psVar5 + 1;
        }
      } while (bVar1);
      bVar1 = false;
      psVar5 = &DAT_802c4b88;
      while( true ) {
        if (*psVar5 < 0) break;
        if (uVar3 == (int)*psVar5) {
          bVar1 = true;
          break;
        }
        psVar5 = psVar5 + 1;
      }
      if (!bVar1) goto LAB_80018780;
    } while (*(short *)(PTR_DAT_8043393c + 0xc) != 0);
    *(undefined2 *)(PTR_DAT_8043393c + 0xc) = 1;
LAB_80018780:
    puVar6 = (undefined2 *)(PTR_DAT_80433934 + param_1 * 0x348 + iVar8 + 0x1e8);
    iVar8 = iVar8 + 0x1c;
    *puVar6 = (short)uVar3;
    iVar7 = iVar7 + 1;
    *(undefined1 *)(puVar6 + 1) = 0;
    *(undefined1 *)(puVar6 + 0xb) = 0;
    *(undefined1 *)((int)puVar6 + 0x17) = 0;
    *(undefined1 *)(puVar6 + 0xc) = 0;
  } while( true );
}



// ==== 80018824  zz_0018824_ ====

undefined4 zz_0018824_(void)

{
  return 0;
}



// ==== 8001882c  zz_001882c_ ====

void zz_001882c_(undefined4 param_1)

{
  DAT_804360e8 = param_1;
  zz_008c0dc_(FUN_80018858);
  return;
}



// ==== 80018858  FUN_80018858 ====

void FUN_80018858(void)

{
  DAT_803c1140 = &DAT_802c7dd8;
  DAT_803c1144 = 0;
  DAT_803c1150 = &DAT_80433620;
  DAT_803c115c = &DAT_80433628;
  DAT_803c113c = 0;
  DAT_803c1174 = FLOAT_80436d40;
  DAT_803c1160 = DAT_804360e8;
  DAT_803c1164 = 3;
  DAT_803c1168 = 0xf;
  DAT_803c1170 = 0;
  DAT_803c1173 = 0xff;
  FUN_80051ef4(-0x7fc3eed0);
  return;
}



// ==== 800188d4  zz_00188d4_ ====

undefined4 zz_00188d4_(int param_1,int *param_2)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  ushort *puVar8;
  ushort *puVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  uint uVar14;
  
  zz_00f19f8_(0x803c0740,param_1,0x800,1);
  iVar2 = DAT_803c0740;
  iVar6 = 0;
  puVar8 = (ushort *)*param_2;
  iVar4 = 0;
  iVar13 = 0;
  iVar12 = -1;
  iVar7 = -4;
  iVar11 = 1;
  iVar10 = 0;
  do {
    uVar14 = *(uint *)((int)&DAT_803c0744 + iVar6);
    uVar1 = uVar14 & 0xbfffffff;
    if (uVar1 == 0) {
      if (*(ushort **)((int)param_2 + iVar6) != (ushort *)0x0) {
        iVar12 = iVar12 + 1;
        iVar7 = iVar7 + 4;
        puVar8 = *(ushort **)((int)param_2 + iVar6);
      }
      *(undefined4 *)((int)param_2 + iVar6) = 0;
    }
    else {
      puVar9 = *(ushort **)((int)param_2 + iVar6);
      if (puVar9 == (ushort *)0x0) {
        if (iVar10 == 0) {
          *(ushort **)((int)param_2 + iVar6) = (ushort *)((int)puVar8 + iVar4);
          puVar8 = (ushort *)((int)puVar8 + iVar4);
LAB_800189e4:
          puVar9 = puVar8;
          if ((uVar14 & 0x40000000) != 0) {
            puVar9 = (ushort *)(DAT_80436238 + 0x4800);
          }
          iVar4 = uVar14 << 0xb;
          uVar5 = 1;
          iVar3 = iVar4;
          zz_00f19f8_((uint)puVar9,param_1 + iVar11 * 0x800,iVar4,1);
          if ((uVar14 & 0x40000000) != 0) {
            iVar4 = zz_0048588_(puVar9,puVar8,iVar3,uVar5);
          }
          uVar14 = iVar4 + 0x7ff;
          iVar11 = iVar11 + uVar1;
          iVar3 = ((int)uVar14 >> 0xb) + (uint)((int)uVar14 < 0 && (uVar14 & 0x7ff) != 0);
          iVar4 = iVar3 * 0x800;
          if (-1 < iVar12) {
            *(ushort **)((int)&DAT_803c06cc + iVar7) = puVar8 + iVar3 * 0x400;
          }
        }
        else {
          iVar10 = iVar10 + uVar1;
        }
      }
      else {
        if (((uint)puVar9 & 0xf0000000) != 0xf0000000) {
          if (iVar10 != 0) {
            iVar11 = iVar11 + iVar10;
            iVar10 = 0;
          }
          iVar12 = iVar12 + 1;
          iVar7 = iVar7 + 4;
          puVar8 = puVar9;
          goto LAB_800189e4;
        }
        iVar10 = iVar10 + uVar1;
        iVar12 = iVar12 + 1;
        iVar7 = iVar7 + 4;
      }
    }
    iVar13 = iVar13 + 1;
    iVar6 = iVar6 + 4;
    if (iVar2 <= iVar13) {
      return 0;
    }
  } while( true );
}



// ==== 80018a80  zz_0018a80_ ====

void zz_0018a80_(void)

{
  DAT_804360f4 = gnt4_DVDGetDriveStatus_bl();
  DAT_804360f8 = DAT_804360f4;
  DAT_80436100 = DAT_804360f4;
  DAT_80436104 = DAT_804360f4;
  DAT_804360fc = 0;
  return;
}



// ==== 80018ab8  zz_0018ab8_ ====

int zz_0018ab8_(int param_1,int param_2)

{
  if ((param_1 == 1) && ((param_2 - 4U < 2 || (param_2 == 6)))) {
    return 0x7fffffff;
  }
  if (param_1 < 7) {
    if (param_1 == -1) {
      return -1;
    }
    if ((-2 < param_1) && (3 < param_1)) {
      return param_1;
    }
  }
  else if (param_1 == 0xb) {
    return 0xb;
  }
  return 0;
}



// ==== 80018b10  zz_0018b10_ ====

int zz_0018b10_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
               undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined4 in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar2;
  undefined8 uVar3;
  
  iVar1 = DAT_804360f8;
  iVar2 = *(int *)(PTR_DAT_80433930 + 0x38);
  if (iVar2 == 0) {
    DAT_804360f0 = 0;
  }
  DAT_804360f0 = DAT_804360f0 + 1;
  DAT_804360f8 = gnt4_DVDGetDriveStatus_bl();
  if (DAT_804360f8 != iVar1) {
    DAT_804360f4 = iVar1;
  }
  iVar1 = zz_0018ab8_(DAT_804360f8,DAT_804360f4);
  if ((iVar1 == 0) && (DAT_804360fc != 0)) {
    iVar1 = zz_0018ab8_(DAT_80436104,DAT_80436100);
  }
  *(int *)(PTR_DAT_80433930 + 0x38) = iVar1;
  if (iVar1 == 0) {
    if (iVar2 != 0) {
      uVar3 = zz_00e9b08_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,0,
                          in_r6,in_r7,in_r8,in_r9,in_r10);
      uVar3 = zz_00e9b08_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,0,in_r6,
                          in_r7,in_r8,in_r9,in_r10);
      zz_00e9b08_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,0,0,in_r6,in_r7,
                  in_r8,in_r9,in_r10);
      zz_01b786c_(0);
      zz_00f094c_(0);
    }
  }
  else {
    uVar3 = zz_008c0b4_(zz_0018c88_);
    if (iVar2 == 0) {
      uVar3 = zz_00e9b08_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,1,in_r6,
                          in_r7,in_r8,in_r9,in_r10);
      uVar3 = zz_00e9b08_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,0,1,in_r6,
                          in_r7,in_r8,in_r9,in_r10);
      zz_00e9b08_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,0,1,in_r6,in_r7,
                  in_r8,in_r9,in_r10);
      zz_01b786c_(1);
      zz_00f094c_(1);
    }
  }
  return iVar1;
}



// ==== 80018c58  PlatAudio::IsSFXPlaying(unsigned ====

uint PlatAudio__IsSFXPlaying_unsigned(void)

{
  int iVar1;
  
  iVar1 = gnt4_DVDCheckDisk_bl();
  return (1U - iVar1 | iVar1 - 1U) >> 0x1f;
}



// ==== 80018c88  zz_0018c88_ ====

void zz_0018c88_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  float fVar1;
  undefined **ppuVar2;
  int iVar3;
  undefined **ppuVar4;
  size_t sVar5;
  int iVar6;
  undefined2 *puVar7;
  undefined1 *puVar8;
  undefined4 uVar9;
  undefined *puVar10;
  char *pcVar11;
  undefined8 uVar12;
  double dVar13;
  undefined1 local_38;
  undefined1 local_37;
  undefined1 local_36;
  undefined1 local_35;
  undefined2 local_34;
  undefined2 local_32;
  float local_30;
  float local_2c;
  float local_28;
  undefined8 local_20;
  
  if (*(int *)(PTR_DAT_80433930 + 0x38) != -1) {
    fVar1 = FLOAT_80436d48;
    if ((int)DAT_804360f0 < 10) {
      local_20 = (double)CONCAT44(0x43300000,DAT_804360f0 ^ 0x80000000);
      fVar1 = (float)(local_20 - DOUBLE_80436d60) / FLOAT_80436d4c;
    }
    dVar13 = (double)fVar1;
    uVar9 = 0;
    puVar10 = &DAT_803c1130;
    DAT_803c1140 = &local_30;
    puVar8 = &local_38;
    puVar7 = &local_34;
    DAT_803c1144 = 0;
    DAT_803c1164 = 7;
    DAT_803c1170 = 5;
    local_30 = FLOAT_80436d50;
    local_2c = FLOAT_80436d50;
    local_28 = FLOAT_80436d54;
    local_34 = 0x280;
    local_32 = 0x1c0;
    local_36 = 0;
    local_37 = 0;
    local_38 = 0;
    if ((int)DAT_804360f0 < 10) {
      local_20 = (double)(longlong)(int)((double)FLOAT_80436d58 * dVar13);
      local_35 = (undefined1)(int)((double)FLOAT_80436d58 * dVar13);
    }
    else {
      local_35 = 0xc0;
    }
    DAT_803c1150 = puVar8;
    DAT_803c1154 = puVar7;
    FUN_80051998(-0x7fc3eed0);
    if (9 < (int)DAT_804360f0) {
      iVar6 = *(int *)(PTR_DAT_80433930 + 0x38);
      if (iVar6 == 6) {
        iVar6 = 2;
        ppuVar2 = (undefined **)0x802c7e0c;
      }
      else if (iVar6 < 6) {
        if (iVar6 == 4) {
          iVar6 = 0;
          ppuVar2 = (undefined **)0x802c7df0;
        }
        else {
          if (iVar6 < 4) {
            return;
          }
          iVar6 = 1;
          ppuVar2 = &PTR_s_The_Disc_Cover_is_open__802c7dfc;
        }
      }
      else if (iVar6 == 0xb) {
        iVar6 = 3;
        ppuVar2 = &PTR_s_The_Game_Disc_could_not_be_read__802c7e18;
      }
      else {
        if (iVar6 < 0xb) {
          return;
        }
        if (iVar6 < 0x7fffffff) {
          return;
        }
        iVar6 = 4;
        ppuVar2 = (undefined **)&DAT_80433630;
      }
      iVar3 = zz_008017c_();
      if (iVar3 == 0) {
        zz_0018ed0_(iVar6);
      }
      else {
        uVar12 = zz_008028c_((double)FLOAT_80436d48);
        iVar6 = 0;
        for (ppuVar4 = ppuVar2; *ppuVar4 != (undefined *)0x0; ppuVar4 = ppuVar4 + 1) {
          iVar6 = iVar6 + 1;
        }
        iVar6 = iVar6 * -0xe + 0xe0;
        for (ppuVar4 = ppuVar2; pcVar11 = *ppuVar4, pcVar11 != (char *)0x0; ppuVar4 = ppuVar4 + 1) {
          sVar5 = strlen(*ppuVar2);
          uVar12 = zz_0080184_(uVar12,dVar13,param_3,param_4,param_5,param_6,param_7,param_8,
                               0x140 - (sVar5 * 0xc >> 1),iVar6,0xe0e000ff,pcVar11,puVar7,puVar8,
                               uVar9,puVar10);
          iVar6 = iVar6 + 0x1c;
        }
      }
    }
  }
  return;
}



// ==== 80018ed0  zz_0018ed0_ ====

void zz_0018ed0_(int param_1)

{
  DAT_803c1140 = param_1 * 0x18 + -0x7fd381d4;
  DAT_803c115c = param_1 * 8 + -0x7fd3815c;
  DAT_803c1144 = 0;
  DAT_803c1150 = &DAT_80433638;
  DAT_803c1160 = &DAT_803c012c;
  DAT_803c1164 = 7;
  DAT_803c1168 = 0xf;
  DAT_803c1170 = 1;
  DAT_803c1173 = 0x1f;
  FUN_80051ef4(-0x7fc3eed0);
  return;
}



// ==== 80018f5c  zz_0018f5c_ ====

uint zz_0018f5c_(void)

{
  uint uVar1;
  
  uVar1 = gnt4_DVDGetDriveStatus_bl();
  return (-uVar1 | uVar1) >> 0x1f;
}



// ==== 80018f88  zz_0018f88_ ====

void zz_0018f88_(int *param_1,int param_2,float *param_3)

{
  float fVar1;
  int iVar2;
  
  *(undefined2 *)(param_1 + 1) = 0;
  *param_1 = param_2;
  fVar1 = FLOAT_80436d68;
  if (param_2 != 0) {
    iVar2 = param_2 + *(short *)(param_1 + 1) * 0x10;
    fVar1 = *(float *)(iVar2 + 8);
    *param_3 = *(float *)(iVar2 + 4);
    param_3[1] = fVar1;
    param_3[2] = *(float *)(iVar2 + 0xc);
    return;
  }
  param_3[2] = FLOAT_80436d68;
  param_3[1] = fVar1;
  *param_3 = fVar1;
  return;
}



// ==== 80018fd8  zz_0018fd8_ ====

uint zz_0018fd8_(int *param_1,int param_2,float *param_3)

{
  double dVar1;
  float fVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  
  uVar8 = 0xffffffff;
  iVar7 = *param_1;
  if (iVar7 != 0) {
    iVar6 = *(short *)(param_1 + 1) + 1;
    piVar4 = (int *)(iVar7 + iVar6 * 0x10);
    piVar3 = (int *)(iVar7 + *(short *)(param_1 + 1) * 0x10);
    piVar5 = piVar4;
    if ((*piVar4 != -1) && (*piVar4 <= param_2)) {
      *(short *)(param_1 + 1) = (short)iVar6;
      piVar5 = (int *)(*param_1 + (*(short *)(param_1 + 1) + 1) * 0x10);
      piVar3 = piVar4;
    }
    fVar2 = (float)piVar3[2];
    *param_3 = (float)piVar3[1];
    param_3[1] = fVar2;
    param_3[2] = (float)piVar3[3];
    dVar1 = DOUBLE_80436d70;
    uVar8 = countLeadingZeros(-1 - *piVar5);
    uVar8 = uVar8 >> 5;
    if (uVar8 == 0) {
      *param_3 = *param_3 +
                 ((float)((double)CONCAT44(0x43300000,param_2 - *piVar3 ^ 0x80000000) -
                         DOUBLE_80436d70) * ((float)piVar5[1] - (float)piVar3[1])) /
                 (float)((double)CONCAT44(0x43300000,*piVar5 - *piVar3 ^ 0x80000000) -
                        DOUBLE_80436d70);
      param_3[1] = param_3[1] +
                   ((float)((double)CONCAT44(0x43300000,param_2 - *piVar3 ^ 0x80000000) - dVar1) *
                   ((float)piVar5[2] - (float)piVar3[2])) /
                   (float)((double)CONCAT44(0x43300000,*piVar5 - *piVar3 ^ 0x80000000) - dVar1);
      param_3[2] = param_3[2] +
                   ((float)((double)CONCAT44(0x43300000,param_2 - *piVar3 ^ 0x80000000) - dVar1) *
                   ((float)piVar5[3] - (float)piVar3[3])) /
                   (float)((double)CONCAT44(0x43300000,*piVar5 - *piVar3 ^ 0x80000000) - dVar1);
    }
  }
  return uVar8;
}



// ==== 80019178  zz_0019178_ ====

uint zz_0019178_(double param_1,int *param_2,float *param_3)

{
  double dVar1;
  float fVar2;
  uint *puVar3;
  uint *puVar4;
  uint *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  
  uVar8 = 0xffffffff;
  iVar6 = *param_2;
  if (iVar6 != 0) {
    iVar7 = *(short *)(param_2 + 1) + 1;
    puVar4 = (uint *)(iVar6 + iVar7 * 0x10);
    puVar3 = (uint *)(iVar6 + *(short *)(param_2 + 1) * 0x10);
    puVar5 = puVar4;
    if (*puVar4 != 0xffffffff) {
      if ((double)(float)((double)CONCAT44(0x43300000,*puVar4 ^ 0x80000000) - DOUBLE_80436d70) <=
          param_1) {
        *(short *)(param_2 + 1) = (short)iVar7;
        puVar5 = (uint *)(*param_2 + (*(short *)(param_2 + 1) + 1) * 0x10);
        puVar3 = puVar4;
      }
    }
    fVar2 = (float)puVar3[2];
    *param_3 = (float)puVar3[1];
    param_3[1] = fVar2;
    param_3[2] = (float)puVar3[3];
    dVar1 = DOUBLE_80436d70;
    uVar8 = countLeadingZeros(-1 - *puVar5);
    uVar8 = uVar8 >> 5;
    if (uVar8 == 0) {
      *param_3 = *param_3 +
                 ((float)(param_1 -
                         (double)(float)((double)CONCAT44(0x43300000,*puVar3 ^ 0x80000000) -
                                        DOUBLE_80436d70)) * ((float)puVar5[1] - (float)puVar3[1])) /
                 (float)((double)CONCAT44(0x43300000,*puVar5 - *puVar3 ^ 0x80000000) -
                        DOUBLE_80436d70);
      param_3[1] = param_3[1] +
                   ((float)(param_1 -
                           (double)(float)((double)CONCAT44(0x43300000,*puVar3 ^ 0x80000000) - dVar1
                                          )) * ((float)puVar5[2] - (float)puVar3[2])) /
                   (float)((double)CONCAT44(0x43300000,*puVar5 - *puVar3 ^ 0x80000000) - dVar1);
      param_3[2] = param_3[2] +
                   ((float)(param_1 -
                           (double)(float)((double)CONCAT44(0x43300000,*puVar3 ^ 0x80000000) - dVar1
                                          )) * ((float)puVar5[3] - (float)puVar3[3])) /
                   (float)((double)CONCAT44(0x43300000,*puVar5 - *puVar3 ^ 0x80000000) - dVar1);
    }
  }
  return uVar8;
}



// ==== 80019338  zz_0019338_ ====

void zz_0019338_(int *param_1,int param_2,float *param_3)

{
  *(undefined2 *)(param_1 + 1) = 0;
  *param_1 = param_2;
  if (param_2 != 0) {
    *param_3 = *(float *)(param_2 + *(short *)(param_1 + 1) * 8 + 4);
    return;
  }
  *param_3 = FLOAT_80436d68;
  return;
}



// ==== 80019370  zz_0019370_ ====

uint zz_0019370_(int *param_1,int param_2,float *param_3)

{
  int iVar1;
  uint uVar2;
  int iVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  
  uVar2 = 0xffffffff;
  iVar3 = *param_1;
  if (iVar3 != 0) {
    iVar1 = *(short *)(param_1 + 1) + 1;
    piVar5 = (int *)(iVar3 + iVar1 * 8);
    piVar4 = (int *)(iVar3 + *(short *)(param_1 + 1) * 8);
    piVar6 = piVar5;
    if ((*piVar5 != -1) && (*piVar5 <= param_2)) {
      *(short *)(param_1 + 1) = (short)iVar1;
      piVar6 = (int *)(*param_1 + (*(short *)(param_1 + 1) + 1) * 8);
      piVar4 = piVar5;
    }
    *param_3 = (float)piVar4[1];
    uVar2 = countLeadingZeros(-1 - *piVar6);
    uVar2 = uVar2 >> 5;
    if (uVar2 == 0) {
      *param_3 = *param_3 +
                 ((float)((double)CONCAT44(0x43300000,param_2 - *piVar4 ^ 0x80000000) -
                         DOUBLE_80436d70) * ((float)piVar6[1] - (float)piVar4[1])) /
                 (float)((double)CONCAT44(0x43300000,*piVar6 - *piVar4 ^ 0x80000000) -
                        DOUBLE_80436d70);
    }
  }
  return uVar2;
}



// ==== 80019450  zz_0019450_ ====

uint zz_0019450_(double param_1,int *param_2,float *param_3)

{
  int iVar1;
  int iVar2;
  uint *puVar3;
  uint uVar4;
  uint *puVar5;
  uint *puVar6;
  
  uVar4 = 0xffffffff;
  iVar2 = *param_2;
  if (iVar2 != 0) {
    iVar1 = *(short *)(param_2 + 1) + 1;
    puVar5 = (uint *)(iVar2 + iVar1 * 8);
    puVar3 = (uint *)(iVar2 + *(short *)(param_2 + 1) * 8);
    puVar6 = puVar5;
    if (*puVar5 != 0xffffffff) {
      if ((double)(float)((double)CONCAT44(0x43300000,*puVar5 ^ 0x80000000) - DOUBLE_80436d70) <=
          param_1) {
        *(short *)(param_2 + 1) = (short)iVar1;
        puVar6 = (uint *)(*param_2 + (*(short *)(param_2 + 1) + 1) * 8);
        puVar3 = puVar5;
      }
    }
    *param_3 = (float)puVar3[1];
    uVar4 = countLeadingZeros(-1 - *puVar6);
    uVar4 = uVar4 >> 5;
    if (uVar4 == 0) {
      *param_3 = *param_3 +
                 ((float)(param_1 -
                         (double)(float)((double)CONCAT44(0x43300000,*puVar3 ^ 0x80000000) -
                                        DOUBLE_80436d70)) * ((float)puVar6[1] - (float)puVar3[1])) /
                 (float)((double)CONCAT44(0x43300000,*puVar6 - *puVar3 ^ 0x80000000) -
                        DOUBLE_80436d70);
    }
  }
  return uVar4;
}



// ==== 80019550  zz_0019550_ ====

void zz_0019550_(int param_1,undefined4 *param_2,uint param_3)

{
  int iVar1;
  char local_8;
  undefined1 local_7;
  undefined1 local_6;
  
  iVar1 = (param_3 & 0xff) * 4;
  local_8 = (&DAT_802c7ed3)[iVar1];
  local_7 = (&DAT_802c7ed1)[iVar1];
  local_6 = (&DAT_802c7ed2)[iVar1];
  zz_001959c_(param_1,param_2,&local_8);
  return;
}



// ==== 8001959c  zz_001959c_ ====

void zz_001959c_(int param_1,undefined4 *param_2,char *param_3)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  puVar2 = zz_008893c_(2,0x1f,0,(int)*param_3);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x10] = 0;
    puVar2[0x11] = param_3[1];
    puVar2[0x12] = param_3[2];
    puVar2[0x13] = *param_3;
    *(code **)(puVar2 + 0xc) = FUN_800196d0;
    *(code **)(puVar2 + 0x10c) = FUN_80019824;
    uVar1 = param_2[1];
    *(undefined4 *)(puVar2 + 0x20) = *param_2;
    *(undefined4 *)(puVar2 + 0x24) = uVar1;
    *(undefined4 *)(puVar2 + 0x28) = param_2[2];
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



// ==== 800196d0  FUN_800196d0 ====

void FUN_800196d0(int param_1)

{
  (*(code *)(&PTR_FUN_802c8164)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 8001970c  FUN_8001970c ====

void FUN_8001970c(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 1;
  (*(code *)(&PTR_FUN_802c8174)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 80019750  FUN_80019750 ====

void FUN_80019750(int param_1)

{
  (*(code *)(&PTR_FUN_802c8184)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 800197a0  FUN_800197a0 ====

void FUN_800197a0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800197e8  FUN_800197e8 ====

void FUN_800197e8(int param_1)

{
  (*(code *)(&PTR_FUN_802c8194)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 80019824  FUN_80019824 ====

void FUN_80019824(int param_1)

{
  (*(code *)(&PTR_FUN_802c81a4)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 80019860  FUN_80019860 ====

void FUN_80019860(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  short *psVar2;
  undefined8 uVar3;
  
  psVar2 = (short *)(&PTR_DAT_802c8154)[*(char *)(param_9 + 0x11)];
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(short *)(param_9 + 0x1e) = psVar2[1];
  *(undefined4 *)(param_9 + 0xdc) = 0;
  uVar1 = zz_00055fc_();
  *(short *)(param_9 + 0x70) = (short)(uVar1 << 8);
  uVar1 = zz_00055fc_();
  *(short *)(param_9 + 0x72) = (short)(uVar1 << 8);
  zz_0018f88_((int *)(param_9 + 0x144),*(int *)(psVar2 + 2),(float *)(param_9 + 0x58));
  zz_0019338_((int *)(param_9 + 0x14c),*(int *)(psVar2 + 4),(float *)(param_9 + 0x154));
  *(undefined1 *)(param_9 + 0x84) = 0x16;
  *(code **)(param_9 + 0x100) = FUN_80047c38;
  uVar3 = zz_0089100_(param_9,0,1);
  zz_0006fb4_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),(int)*psVar2,param_12,param_13,param_14,param_15,param_16);
  zz_0007cac_((double)*(float *)(param_9 + 0x154),*(int *)(param_9 + 0xe0));
  *(undefined1 *)(param_9 + 0x82) = 1;
  return;
}



// ==== 80019950  FUN_80019950 ====

void FUN_80019950(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (*(short *)(param_1 + 0x1e) <= sVar1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x58));
  zz_0019370_((int *)(param_1 + 0x14c),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x154));
  zz_0007cac_((double)*(float *)(param_1 + 0x154),*(int *)(param_1 + 0xe0));
  return;
}



// ==== 800199d4  FUN_800199d4 ====

void FUN_800199d4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 80019a14  FUN_80019a14 ====

void FUN_80019a14(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  undefined *puVar6;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  
  iVar8 = ((int)*(short *)(PTR_DAT_80433934 + 0x1e4) >> 0x1f) +
          (uint)(0x1f < (uint)(int)*(short *)(PTR_DAT_80433934 + 0x1e4));
  if ((iVar8 == 0) &&
     (iVar8 = ((int)*(short *)(PTR_DAT_80433934 + 0x1e6) >> 0x1f) +
              (uint)(0x1ff < (uint)(int)*(short *)(PTR_DAT_80433934 + 0x1e6)), iVar8 == 0)) {
    uVar1 = zz_00055fc_();
    *(ushort *)(param_9 + 0x1c) = ((ushort)uVar1 & 3) + 8;
    *(ushort *)(param_9 + 0x1e) = ((ushort)(uVar1 >> 4) & 3) + 8;
    *(char *)(param_9 + 0x13) =
         (char)*(undefined2 *)(param_9 + 0x1c) + (char)*(undefined2 *)(param_9 + 0x1e);
    if (0x200 - *(short *)(PTR_DAT_80433934 + 0x1e6) < (int)*(char *)(param_9 + 0x13)) {
      *(char *)(param_9 + 0x13) = (char)(0x200 - *(short *)(PTR_DAT_80433934 + 0x1e6));
      *(short *)(param_9 + 0x1e) = (short)((int)*(char *)(param_9 + 0x13) >> 1);
      *(short *)(param_9 + 0x1c) = (short)*(char *)(param_9 + 0x13) - *(short *)(param_9 + 0x1e);
    }
  }
  if (iVar8 == 0) {
    piVar2 = zz_0006dc8_(*(char *)(param_9 + 0x13) * 0x38);
    *(int **)(param_9 + 0xdc) = piVar2;
    if (piVar2 != (int *)0x0) {
      puVar6 = (&PTR_DAT_802c8154)[*(char *)(param_9 + 0x11)];
      if (PTR_DAT_80433934[0x51] == '\x03') {
        iVar8 = 0;
      }
      else {
        iVar8 = (int)*(char *)(param_9 + 0x88);
      }
      iVar8 = iVar8 * 0xc;
      *(float *)(param_9 + 0xd4) = FLOAT_80436d78;
      *(short *)(PTR_DAT_80433934 + 0x1e4) = *(short *)(PTR_DAT_80433934 + 0x1e4) + 1;
      *(short *)(PTR_DAT_80433934 + 0x1e6) =
           *(short *)(PTR_DAT_80433934 + 0x1e6) + (short)*(char *)(param_9 + 0x13);
      iVar5 = (int)*(char *)(param_9 + 0x13);
      pcVar4 = (char *)(int)*(short *)(puVar6 + iVar8);
      uVar9 = zz_0007198_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          DAT_803bb374,*(int *)(param_9 + 0xe0),pcVar4,iVar5,iVar8,puVar6,in_r9,
                          in_r10);
      iVar7 = 0;
      iVar3 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(iVar3 + 0x10);
      }
      while (iVar7 < *(char *)(param_9 + 0x13)) {
        *(uint *)(param_9 + 0x158) = *(uint *)(param_9 + 0x158) & ~(1 << iVar7);
        uVar9 = gnt4_HSD_JObjSetFlagsAll
                          (uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,0x10,
                           pcVar4,iVar5,iVar8,puVar6,in_r9,in_r10);
        iVar7 = iVar7 + 1;
        if (iVar3 == 0) {
          iVar3 = 0;
        }
        else {
          iVar3 = *(int *)(iVar3 + 8);
        }
      }
      zz_0019e6c_(param_9,0,pcVar4,iVar5,iVar8,puVar6,in_r9,in_r10);
      *(undefined1 *)(param_9 + 0x82) = 1;
      return;
    }
  }
  *(undefined1 *)(param_9 + 0x18) = 2;
  return;
}



// ==== 80019c3c  FUN_80019c3c ====

void FUN_80019c3c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  double dVar2;
  double dVar3;
  double dVar4;
  
  dVar3 = (double)FLOAT_80436d7c;
  dVar4 = (double)*(float *)(param_9 + 0xd4);
  if ((dVar3 < dVar4) &&
     (dVar2 = (double)FLOAT_80436d68, *(float *)(param_9 + 0xd4) = (float)(dVar4 - dVar2),
     (double)(float)(dVar4 - dVar2) == dVar3)) {
    dVar3 = (double)zz_0019e6c_(param_9,1,param_11,param_12,param_13,param_14,param_15,param_16);
    param_10 = extraout_r4;
  }
  iVar1 = zz_001a128_(dVar3,dVar4,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
                      param_11,param_12,param_13,param_14,param_15,param_16);
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(short *)(PTR_DAT_80433934 + 0x1e4) = *(short *)(PTR_DAT_80433934 + 0x1e4) + -1;
    *(short *)(PTR_DAT_80433934 + 0x1e6) =
         *(short *)(PTR_DAT_80433934 + 0x1e6) - (short)*(char *)(param_9 + 0x13);
  }
  return;
}



// ==== 80019cd0  FUN_80019cd0 ====

/* WARNING: Removing unreachable block (ram,0x80019de4) */

void FUN_80019cd0(int param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  float *pfVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  double dVar9;
  double dVar10;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [14];
  
  if (*(int *)(param_1 + 0x158) != 0) {
    iVar7 = 0;
    iVar2 = *(int *)(*(int *)(param_1 + 0xe0) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    iVar6 = 0;
    while (iVar7 < *(char *)(param_1 + 0x13)) {
      if ((*(uint *)(param_1 + 0x158) & 1 << iVar7) != 0) {
        uVar4 = 1;
        pfVar5 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar6);
        zz_00484e8_(afStack_4c,pfVar5,pfVar5 + 3,1);
        dVar10 = (double)FLOAT_80436d68;
        local_50 = FLOAT_80436d68;
        local_54 = FLOAT_80436d68;
        dVar9 = (double)(FLOAT_80436d80 * pfVar5[10]);
        local_58 = (float)((double)(pfVar5[0xb] * (float)(dVar9 - (double)pfVar5[7])) / dVar9);
        if ((double)local_58 < dVar10) {
          local_58 = FLOAT_80436d68;
        }
        gnt4_PSQUATScale_bl((double)pfVar5[6],&local_58,&local_58);
        pfVar5 = &local_58;
        uVar8 = zz_00456a0_(afStack_4c,afStack_4c,pfVar5);
        if (iVar2 == 0) {
          pfVar5 = (float *)&DAT_80436d8c;
          gnt4___assert_bl(uVar8,dVar9,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,&DAT_80436d84,0x495,
                           &DAT_80436d8c,uVar4,in_r7,in_r8,in_r9,in_r10);
        }
        uVar8 = gnt4_PSMTXCopy_bl(afStack_4c,(float *)(iVar2 + 0x44));
        *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
        if (iVar2 != 0) {
          uVar3 = *(uint *)(iVar2 + 0x14);
          bVar1 = false;
          if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
            bVar1 = true;
          }
          if (!bVar1) {
            gnt4_HSD_JObjSetMtxDirtySub_bl
                      (uVar8,dVar9,dVar10,in_f4,in_f5,in_f6,in_f7,in_f8,iVar2,uVar3,
                       (undefined *)pfVar5,uVar4,in_r7,in_r8,in_r9,in_r10);
          }
        }
      }
      iVar6 = iVar6 + 0x38;
      iVar7 = iVar7 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
    zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
  }
  return;
}



// ==== 80019e6c  zz_0019e6c_ ====

/* WARNING: Removing unreachable block (ram,0x8001a10c) */
/* WARNING: Removing unreachable block (ram,0x80019e7c) */

void zz_0019e6c_(int param_1,int param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5,
                undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float fVar1;
  int iVar2;
  short sVar3;
  float fVar4;
  undefined4 uVar5;
  int iVar6;
  uint uVar7;
  float *pfVar8;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  double dVar14;
  double dVar15;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  double dVar16;
  double dVar17;
  float afStack_78 [2];
  undefined4 local_70;
  undefined4 local_60;
  undefined4 local_50;
  undefined4 local_48;
  uint uStack_44;
  undefined4 local_40;
  uint uStack_3c;
  undefined4 local_38;
  uint uStack_34;
  undefined4 local_30;
  uint uStack_2c;
  
  iVar2 = param_2 * 0x20;
  iVar6 = 0;
  for (iVar11 = 0; iVar12 = iVar6, iVar11 < *(short *)(param_1 + param_2 * 2 + 0x1c);
      iVar11 = iVar11 + 1) {
    for (; iVar12 < *(char *)(param_1 + 0x13); iVar12 = iVar12 + 1) {
      if ((*(uint *)(param_1 + 0x158) & 1 << iVar12) == 0) {
        iVar6 = *(int *)(*(int *)(param_1 + 0xdc) + 0xc);
        *(uint *)(param_1 + 0x158) = *(uint *)(param_1 + 0x158) | 1 << iVar12;
        puVar10 = (undefined4 *)(iVar6 + iVar12 * 0x38);
        puVar10[0xd] = 0x10;
        uVar5 = *(undefined4 *)(param_1 + 0x24);
        *puVar10 = *(undefined4 *)(param_1 + 0x20);
        puVar10[1] = uVar5;
        puVar10[2] = *(undefined4 *)(param_1 + 0x28);
        gnt4_PSMTXIdentity_bl(afStack_78);
        uVar7 = zz_00055fc_();
        zz_00457d4_('z',afStack_78,afStack_78,(short)(uVar7 << 8));
        uVar7 = zz_00055fc_();
        zz_00457d4_('y',afStack_78,afStack_78,(short)(uVar7 << 8));
        uVar7 = zz_00055fc_();
        sVar3 = (short)(uVar7 << 8);
        pfVar8 = afStack_78;
        iVar9 = (int)sVar3;
        zz_00457d4_('x',pfVar8,pfVar8,sVar3);
        fVar1 = FLOAT_80436d7c;
        puVar10[3] = local_70;
        puVar10[4] = local_60;
        puVar10[5] = local_50;
        puVar10[7] = fVar1;
        dVar16 = (double)*(float *)(&DAT_802c81b4 + iVar2);
        uStack_44 = zz_00055fc_();
        uStack_44 = uStack_44 & 0xff;
        local_48 = 0x43300000;
        puVar10[6] = (float)(dVar16 + (double)(((float)((double)*(float *)(&DAT_802c81b8 + iVar2) -
                                                       dVar16) *
                                               (float)((double)CONCAT44(0x43300000,uStack_44) -
                                                      DOUBLE_80436da0)) / FLOAT_80436d94));
        dVar16 = (double)*(float *)(&DAT_802c81bc + iVar2);
        uStack_3c = zz_00055fc_();
        uStack_3c = uStack_3c & 0xff;
        local_40 = 0x43300000;
        puVar10[8] = (float)(dVar16 + (double)(((float)((double)*(float *)(&DAT_802c81c0 + iVar2) -
                                                       dVar16) *
                                               (float)((double)CONCAT44(0x43300000,uStack_3c) -
                                                      DOUBLE_80436da0)) / FLOAT_80436d94));
        dVar16 = (double)*(float *)(&DAT_802c81c4 + iVar2);
        uStack_34 = zz_00055fc_();
        uStack_34 = uStack_34 & 0xff;
        local_38 = 0x43300000;
        puVar10[10] = (float)(dVar16 + (double)(((float)((double)*(float *)(&DAT_802c81c8 + iVar2) -
                                                        dVar16) *
                                                (float)((double)CONCAT44(0x43300000,uStack_34) -
                                                       DOUBLE_80436da0)) / FLOAT_80436d94));
        dVar17 = (double)*(float *)(&DAT_802c81cc + iVar2);
        uStack_2c = zz_00055fc_();
        fVar4 = FLOAT_80436d68;
        uStack_2c = uStack_2c & 0xff;
        local_30 = 0x43300000;
        dVar15 = (double)(float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_80436da0);
        dVar16 = (double)FLOAT_80436d98;
        dVar14 = (double)(float)((double)(float)((double)*(float *)(&DAT_802c81d0 + iVar2) - dVar17)
                                * dVar15);
        puVar10[0xb] = (float)(dVar17 + (double)(float)(dVar14 / (double)FLOAT_80436d94));
        fVar1 = (float)((double)(float)puVar10[8] * dVar16);
        puVar10[9] = fVar1;
        puVar10[0xc] = fVar4;
        iVar6 = *(int *)(*(int *)(param_1 + 0xe0) + 0xc);
        if (iVar6 == 0) {
          iVar6 = 0;
        }
        else {
          iVar6 = *(int *)(iVar6 + 0x10);
        }
        iVar13 = iVar12;
        if (0 < iVar12) {
          do {
            if (iVar6 == 0) {
              iVar6 = 0;
            }
            else {
              iVar6 = *(int *)(iVar6 + 8);
            }
            iVar13 = iVar13 + -1;
          } while (iVar13 != 0);
        }
        gnt4_HSD_JObjClearFlagsAll
                  ((double)fVar1,(double)(float)puVar10[8],dVar14,dVar15,in_f5,in_f6,in_f7,in_f8,
                   iVar6,0x10,(undefined *)pfVar8,iVar9,param_5,param_6,param_7,param_8);
        iVar6 = iVar12 + 1;
        iVar12 = (int)*(char *)(param_1 + 0x13);
      }
    }
  }
  return;
}



// ==== 8001a128  zz_001a128_ ====

undefined4
zz_001a128_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
           double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
           undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
           undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  uint uVar2;
  int iVar3;
  float fVar4;
  float *pfVar5;
  float *pfVar6;
  int iVar7;
  int iVar8;
  double dVar9;
  float afStack_28 [4];
  
  iVar7 = 0;
  iVar3 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
  if (iVar3 == 0) {
    iVar3 = 0;
  }
  else {
    iVar3 = *(int *)(iVar3 + 0x10);
  }
  iVar8 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar7) break;
    if ((*(uint *)(param_9 + 0x158) & 1 << iVar7) != 0) {
      pfVar6 = (float *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar8);
      gnt4_PSQUATScale_bl((double)pfVar6[8],pfVar6 + 3,afStack_28);
      pfVar5 = pfVar6;
      gnt4_PSVECAdd_bl(pfVar6,afStack_28,pfVar6);
      fVar4 = pfVar6[0xd];
      pfVar6[0xd] = (float)((int)fVar4 + -1);
      uVar2 = countLeadingZeros((int)fVar4 + -1);
      uVar2 = (1 << (uVar2 & 0x1f) | 1U >> 0x20 - (uVar2 & 0x1f)) & 1;
      fVar4 = pfVar6[7];
      pfVar6[7] = fVar4 + pfVar6[8];
      fVar1 = FLOAT_80436d7c;
      if (pfVar6[10] <= fVar4 + pfVar6[8]) {
        param_2 = (double)pfVar6[0xc];
        dVar9 = (double)FLOAT_80436da8;
        pfVar6[0xc] = (float)(param_2 - dVar9);
        if ((float)(param_2 - dVar9) <= fVar1) {
          uVar2 = 1;
        }
      }
      fVar4 = pfVar6[8];
      pfVar6[8] = (float)((double)fVar4 + (double)pfVar6[9]);
      fVar1 = FLOAT_80436d7c;
      if (uVar2 != 0) {
        *(uint *)(param_9 + 0x158) = *(uint *)(param_9 + 0x158) & ~(1 << iVar7);
        pfVar6[0xc] = fVar1;
        gnt4_HSD_JObjSetFlagsAll
                  ((double)fVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,0x10,
                   (undefined *)pfVar5,param_12,param_13,param_14,param_15,param_16);
      }
      zz_0007cac_((double)pfVar6[0xc],iVar3);
    }
    iVar8 = iVar8 + 0x38;
    iVar7 = iVar7 + 1;
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *(int *)(iVar3 + 8);
    }
  }
  return *(undefined4 *)(param_9 + 0x158);
}



// ==== 8001a288  FUN_8001a288 ====

void FUN_8001a288(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int *piVar3;
  bool bVar4;
  undefined8 uVar5;
  
  piVar3 = zz_0006dc8_(*(char *)(param_9 + 0x13) * 0x2c);
  *(int **)(param_9 + 0xdc) = piVar3;
  if (piVar3 == (int *)0x0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined2 *)(param_9 + 0x1c) = 0;
    uVar1 = DAT_802b0cb8;
    *(undefined4 *)(param_9 + 0x38) = DAT_802b0cb4;
    uVar2 = DAT_802b0cbc;
    *(undefined4 *)(param_9 + 0x3c) = uVar1;
    *(undefined4 *)(param_9 + 0x40) = uVar2;
    gnt4_PSVECSubtract_bl
              ((float *)(*(int *)(param_9 + 0x8c) + 0x20),(float *)(param_9 + 0x20),
               (float *)(param_9 + 0x9c));
    bVar4 = zz_0045ef4_((float *)(param_9 + 0x114),3,param_9 + 0x38,param_9 + 0x9c);
    uVar1 = DAT_802b0cac;
    if (bVar4) {
      *(undefined4 *)(param_9 + 0x38) = DAT_802b0ca8;
      uVar2 = DAT_802b0cb0;
      *(undefined4 *)(param_9 + 0x3c) = uVar1;
      *(undefined4 *)(param_9 + 0x40) = uVar2;
      zz_0045ef4_((float *)(param_9 + 0x114),3,param_9 + 0x38,param_9 + 0x9c);
    }
    *(undefined4 *)(param_9 + 0x120) = *(undefined4 *)(param_9 + 0x20);
    *(undefined4 *)(param_9 + 0x130) = *(undefined4 *)(param_9 + 0x24);
    *(undefined4 *)(param_9 + 0x140) = *(undefined4 *)(param_9 + 0x28);
    *(code **)(param_9 + 0x100) = FUN_800197e8;
    uVar5 = zz_0089100_(param_9,1,1);
    uVar5 = zz_001a550_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0);
    uVar5 = zz_001a550_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1);
    zz_001a550_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,2);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 8001a3c4  FUN_8001a3c4 ====

void FUN_8001a3c4(int param_1)

{
  int iVar1;
  
  iVar1 = zz_001a65c_(param_1);
  if (iVar1 == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 8001a400  FUN_8001a400 ====

void FUN_8001a400(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

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
  float afStack_48 [13];
  
  iVar4 = 0;
  iVar6 = 0;
  iVar5 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar4) break;
    if (((int)*(short *)(param_9 + 0x1c) & 1 << iVar4) != 0) {
      iVar3 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar6;
      zz_00457d4_('z',(float *)(param_9 + 0x114),afStack_48,*(short *)(iVar3 + 0x28));
      zz_00457d4_('y',afStack_48,afStack_48,*(short *)(iVar3 + 0x26));
      iVar2 = (int)*(short *)(iVar3 + 0x24);
      zz_00457d4_('x',afStack_48,afStack_48,*(short *)(iVar3 + 0x24));
      pfVar1 = (float *)(iVar3 + 0x18);
      uVar7 = zz_00456a0_(afStack_48,afStack_48,pfVar1);
      zz_00076d0_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar5 + 0xe0),afStack_48,(undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,
                  in_r10);
    }
    iVar6 = iVar6 + 0x2c;
    iVar5 = iVar5 + 4;
    iVar4 = iVar4 + 1;
  }
  return;
}



// ==== 8001a4cc  FUN_8001a4cc ====

void FUN_8001a4cc(int param_1)

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



// ==== 8001a550  zz_001a550_ ====

void zz_001a550_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,ushort param_10)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar6;
  int *piVar7;
  int iVar8;
  undefined8 uVar9;
  
  iVar8 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar8) break;
    uVar5 = 1 << iVar8;
    if (((int)*(short *)(param_9 + 0x1c) & uVar5) == 0) {
      iVar3 = iVar8 * 0x2c;
      iVar4 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc);
      puVar2 = (&PTR_DAT_802c8154)[*(char *)(param_9 + 0x11)];
      piVar7 = (int *)(iVar4 + iVar3);
      *(ushort *)((int)piVar7 + 0x2a) = param_10;
      psVar6 = (short *)(puVar2 + (uint)param_10 * 0xc);
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)uVar5;
      *(undefined2 *)(piVar7 + 5) = 0;
      *(short *)((int)piVar7 + 0x16) = psVar6[1];
      *(undefined2 *)(piVar7 + 9) = 0;
      *(undefined2 *)((int)piVar7 + 0x26) = 0;
      uVar1 = zz_00055fc_();
      *(short *)(piVar7 + 10) = (short)(uVar1 << 8);
      zz_0018f88_(piVar7,*(int *)(psVar6 + 2),(float *)(piVar7 + 6));
      uVar9 = zz_0019338_(piVar7 + 2,*(int *)(psVar6 + 4),(float *)(piVar7 + 4));
      zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                  *(int *)(param_9 + iVar8 * 4 + 0xe0),(int)*psVar6,iVar3,iVar4,uVar5,in_r9,in_r10);
      iVar8 = (int)*(char *)(param_9 + 0x13);
    }
    iVar8 = iVar8 + 1;
  }
  return;
}



// ==== 8001a65c  zz_001a65c_ ====

int zz_001a65c_(int param_1)

{
  short sVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = 0;
  iVar4 = param_1;
  for (iVar3 = 0; iVar3 < *(char *)(param_1 + 0x13); iVar3 = iVar3 + 1) {
    piVar2 = (int *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar5);
    sVar1 = *(short *)(piVar2 + 5);
    *(short *)(piVar2 + 5) = sVar1 + 1;
    if (*(short *)((int)piVar2 + 0x16) <= (short)(sVar1 + 1)) {
      *(ushort *)(param_1 + 0x1c) = *(ushort *)(param_1 + 0x1c) & ~(ushort)(1 << iVar3);
    }
    zz_0018fd8_(piVar2,(int)*(short *)(piVar2 + 5),(float *)(piVar2 + 6));
    zz_0019370_(piVar2 + 2,(int)*(short *)(piVar2 + 5),(float *)(piVar2 + 4));
    zz_0007cac_((double)(float)piVar2[4],*(int *)(iVar4 + 0xe0));
    iVar5 = iVar5 + 0x2c;
    iVar4 = iVar4 + 4;
  }
  return (int)*(short *)(param_1 + 0x1c);
}



// ==== 8001a71c  FUN_8001a71c ====

void FUN_8001a71c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int *piVar1;
  undefined8 uVar2;
  
  piVar1 = zz_0006dc8_((int)*(char *)(param_9 + 0x13) << 5);
  *(int **)(param_9 + 0xdc) = piVar1;
  if (piVar1 == (int *)0x0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(code **)(param_9 + 0x100) = FUN_800197e8;
    uVar2 = zz_0089100_(param_9,1,1);
    uVar2 = zz_001a950_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0);
    zz_001a950_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 8001a7b0  FUN_8001a7b0 ====

void FUN_8001a7b0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  
  iVar1 = zz_001aa64_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 8001a7ec  FUN_8001a7ec ====

void FUN_8001a7ec(int param_1)

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
  float afStack_48 [13];
  
  dVar8 = (double)*(float *)(param_1 + 0x24);
  dVar9 = (double)*(float *)(param_1 + 0x28);
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),dVar8,dVar9,(float *)(param_1 + 0x114));
  iVar4 = 0;
  iVar6 = 0;
  iVar5 = param_1;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar4) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar4) != 0) {
      iVar3 = *(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar6;
      zz_00457d4_('z',(float *)(param_1 + 0x114),afStack_48,*(short *)(iVar3 + 0x1c));
      zz_00457d4_('y',afStack_48,afStack_48,*(short *)(iVar3 + 0x1a));
      iVar2 = (int)*(short *)(iVar3 + 0x18);
      zz_00457d4_('x',afStack_48,afStack_48,*(short *)(iVar3 + 0x18));
      pfVar1 = (float *)(iVar3 + 0xc);
      uVar7 = zz_00456a0_(afStack_48,afStack_48,pfVar1);
      zz_00076d0_(uVar7,dVar8,dVar9,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar5 + 0xe0),afStack_48,
                  (undefined *)pfVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
    }
    iVar6 = iVar6 + 0x20;
    iVar5 = iVar5 + 4;
    iVar4 = iVar4 + 1;
  }
  return;
}



// ==== 8001a8cc  FUN_8001a8cc ====

void FUN_8001a8cc(int param_1)

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



// ==== 8001a950  zz_001a950_ ====

void zz_001a950_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,ushort param_10)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  uint uVar4;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar5;
  int *piVar6;
  int iVar7;
  undefined8 uVar8;
  
  iVar7 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar7) break;
    uVar4 = 1 << iVar7;
    if (((int)*(short *)(param_9 + 0x1c) & uVar4) == 0) {
      iVar3 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc);
      puVar2 = (&PTR_DAT_802c8154)[*(char *)(param_9 + 0x11)];
      piVar6 = (int *)(iVar3 + iVar7 * 0x20);
      *(ushort *)((int)piVar6 + 0x1e) = param_10;
      psVar5 = (short *)(puVar2 + (uint)param_10 * 0xc);
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)uVar4;
      *(undefined2 *)(piVar6 + 2) = 0;
      *(short *)((int)piVar6 + 10) = psVar5[1];
      uVar1 = zz_00055fc_();
      *(short *)(piVar6 + 6) = (short)(uVar1 << 8);
      uVar1 = zz_00055fc_();
      *(short *)((int)piVar6 + 0x1a) = (short)(uVar1 << 8);
      uVar1 = zz_00055fc_();
      *(short *)(piVar6 + 7) = (short)(uVar1 << 8);
      uVar8 = zz_0018f88_(piVar6,*(int *)(psVar5 + 2),(float *)(piVar6 + 3));
      zz_000726c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                  *(int *)(param_9 + iVar7 * 4 + 0xe0),(float *)(int)*psVar5,
                  (int)*(char *)(param_9 + 0x88),iVar3,uVar4,in_r9,in_r10);
      iVar7 = (int)*(char *)(param_9 + 0x13);
    }
    iVar7 = iVar7 + 1;
  }
  return;
}



// ==== 8001aa64  zz_001aa64_ ====

int zz_001aa64_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9)

{
  short sVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar3) break;
    if (((int)*(short *)(param_9 + 0x1c) & 1 << iVar3) != 0) {
      piVar2 = (int *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar4);
      sVar1 = *(short *)(piVar2 + 2);
      *(short *)(piVar2 + 2) = sVar1 + 1;
      if (*(short *)((int)piVar2 + 10) <= (short)(sVar1 + 1)) {
        *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) & ~(ushort)(1 << iVar3);
      }
      if (*(short *)((int)piVar2 + 0x1e) == 0) {
        if (*(short *)(piVar2 + 2) < 5) {
          param_1 = zz_001a950_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                param_9,1);
        }
        *(short *)(piVar2 + 6) = *(short *)(piVar2 + 6) + 0xccc;
        *(short *)((int)piVar2 + 0x1a) = *(short *)((int)piVar2 + 0x1a) + 0xccc;
        *(short *)(piVar2 + 7) = *(short *)(piVar2 + 7) + 0xccc;
      }
      zz_0018fd8_(piVar2,(int)*(short *)(piVar2 + 2),(float *)(piVar2 + 3));
    }
    iVar4 = iVar4 + 0x20;
    iVar3 = iVar3 + 1;
  }
  return (int)*(short *)(param_9 + 0x1c);
}



// ==== 8001ab6c  zz_001ab6c_ ====

void zz_001ab6c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 2;
    puVar1[0x11] = param_2;
    puVar1[0x12] = 0;
    *(code **)(puVar1 + 0xc) = FUN_8001ad80;
    *(code **)(puVar1 + 0x10c) = FUN_8001b308;
    puVar1[0x16a] = *(undefined1 *)(param_1 + 0x1afe);
    puVar1[0x16b] = *(undefined1 *)(param_1 + 0x1aff);
    puVar1[0x17c] = 0;
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



// ==== 8001ac80  zz_001ac80_ ====

void zz_001ac80_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,1,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 2;
    puVar1[0x11] = param_2;
    puVar1[0x12] = 1;
    *(code **)(puVar1 + 0xc) = FUN_8001ad80;
    *(code **)(puVar1 + 0x10c) = FUN_8001b308;
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



// ==== 8001ad80  FUN_8001ad80 ====

void FUN_8001ad80(int param_1)

{
  (*(code *)(&PTR_FUN_802ca040)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 8001adbc  FUN_8001adbc ====

void FUN_8001adbc(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x2c;
  *(ushort *)(param_1 + 0x16e) = (*(short *)(&DAT_802c821c + iVar2) + 1) * 0x18 + 0x1fU & 0xffe0;
  piVar3 = zz_0006dc8_((int)*(short *)(param_1 + 0x16e));
  *(int **)(param_1 + 0xdc) = piVar3;
  if (piVar3 == (int *)0x0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 1;
    *(code **)(param_1 + 0x100) = FUN_8001b0c8;
    *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(&DAT_802c81f8 + iVar2);
    *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(&DAT_802c81fc + iVar2);
    *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(&DAT_802c8200 + iVar2);
    *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(&DAT_802c8204 + iVar2);
    *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(&DAT_802c8208 + iVar2);
    *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(&DAT_802c820c + iVar2);
    *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(&DAT_802c8214 + iVar2);
    *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(&DAT_802c8218 + iVar2);
    *(undefined2 *)(param_1 + 0x168) = *(undefined2 *)(&DAT_802c821c + iVar2);
    *(char *)(param_1 + 0x16c) = (char)*(undefined2 *)(&DAT_802c821e + iVar2);
    *(undefined *)(param_1 + 0x17d) = (&DAT_802c8222)[iVar2];
    *(undefined *)(param_1 + 0x16d) = (&DAT_802c8220)[iVar2];
    *(undefined *)(param_1 + 0x17c) = (&DAT_802c8221)[iVar2];
    *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(*(int *)(param_1 + 0xdc) + 0xc);
    *(int *)(param_1 + 0x174) =
         *(int *)(*(int *)(param_1 + 0xdc) + 0xc) + (int)*(short *)(param_1 + 0x16e) / 2;
    iVar1 = (int)*(char *)(*(int *)(param_1 + 0x90) + 0x3ec);
    if (1 < iVar1) {
      *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(&DAT_802ca028 + iVar1 * 4);
      *(undefined *)(param_1 + 0x17d) = (&DAT_80433640)[*(char *)(*(int *)(param_1 + 0x90) + 0x3ec)]
      ;
    }
    if (*(char *)(param_1 + 0x12) == '\0') {
      *(int *)(param_1 + 0x160) =
           *(int *)(param_1 + 0x8c) + *(int *)(&DAT_802c8210 + iVar2) * 0x30 + 0x8d4;
      *(undefined4 *)(param_1 + 0x178) = 0;
      if (*(char *)(param_1 + 0x17c) != '\0') {
        *(int *)(param_1 + 0x178) = *(int *)(param_1 + 0x8c) + 0x8d4;
      }
      zz_0089100_(param_1,1,1);
    }
    else {
      *(int *)(param_1 + 0x160) = *(int *)(param_1 + 0x8c) + 0x114;
      *(undefined1 *)(param_1 + 0x17c) = 0;
      zz_0089338_(param_1,*(int *)(param_1 + 0x8c),1);
    }
  }
  return;
}



// ==== 8001b084  FUN_8001b084 ====

void FUN_8001b084(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  undefined8 uVar1;
  
  uVar1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
  *(undefined4 *)(param_9 + 0xdc) = 0;
  *(undefined4 *)(param_9 + 0xdc) = 0;
  zz_0088e50_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8001b0c8  FUN_8001b0c8 ====

void FUN_8001b0c8(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  undefined4 uVar4;
  bool bVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  float local_48;
  float local_44;
  float local_40;
  float afStack_3c [13];
  
  cVar1 = *(char *)(param_1 + 0x16d);
  iVar7 = *(int *)(param_1 + 0x8c);
  if (cVar1 == '\x01') {
    dVar8 = gnt4_PSVECMag_bl((float *)(iVar7 + 0x38));
    fVar3 = FLOAT_80436db8;
    fVar2 = FLOAT_80436db4;
    if (dVar8 <= (double)FLOAT_80436db0) {
      *(float *)(param_1 + 0x3c) = FLOAT_80436db4;
      *(float *)(param_1 + 0x38) = fVar2;
      *(float *)(param_1 + 0x40) = fVar3;
    }
    else {
      uVar4 = *(undefined4 *)(iVar7 + 0x3c);
      *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(iVar7 + 0x38);
      *(undefined4 *)(param_1 + 0x3c) = uVar4;
      *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(iVar7 + 0x40);
    }
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(*(int *)(param_1 + 0x160) + 4);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(*(int *)(param_1 + 0x160) + 0x14);
    *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(*(int *)(param_1 + 0x160) + 0x24);
    bVar5 = zz_0045ef4_((float *)(param_1 + 0x114),5,param_1 + 0x38,param_1 + 0x9c);
    if (bVar5) {
      gnt4_PSMTXCopy_bl(*(float **)(param_1 + 0x160),(float *)(param_1 + 0x114));
    }
    else {
      *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(*(int *)(param_1 + 0x160) + 0xc);
      *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(*(int *)(param_1 + 0x160) + 0x1c);
      *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(*(int *)(param_1 + 0x160) + 0x2c);
      *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
      zz_0046470_(*(float **)(param_1 + 0x160),&local_48);
      gnt4_PSMTXScale_bl((double)local_48,(double)local_44,(double)local_40,afStack_3c);
      gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_3c,(float *)(param_1 + 0x114));
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    gnt4_PSMTXCopy_bl(*(float **)(param_1 + 0x160),(float *)(param_1 + 0x114));
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
  }
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    *(undefined1 *)(param_1 + 0x19) = 2;
    for (iVar7 = 0; iVar6 = (int)*(short *)(param_1 + 0x168), iVar7 < iVar6; iVar7 = iVar7 + 1) {
      zz_001b754_(param_1 + 0x144,iVar6,iVar7);
    }
    zz_001b7b8_(param_1,(float *)(param_1 + 0x144),iVar6);
    *(undefined2 *)(param_1 + 0x1c) = 0;
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(undefined1 *)(param_1 + 0x19) = 1;
      zz_001b7b8_(param_1,(float *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x168));
    }
  }
  else if (cVar1 < '\x03') {
    for (iVar7 = 0; iVar7 < *(short *)(param_1 + 0x168); iVar7 = iVar7 + 1) {
      zz_001b754_(param_1 + 0x144,iVar7 + 1,iVar7);
    }
    zz_001b7b8_(param_1,(float *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x168));
  }
  return;
}



// ==== 8001b308  FUN_8001b308 ====

/* WARNING: Removing unreachable block (ram,0x8001b738) */
/* WARNING: Removing unreachable block (ram,0x8001b730) */
/* WARNING: Removing unreachable block (ram,0x8001b728) */
/* WARNING: Removing unreachable block (ram,0x8001b328) */
/* WARNING: Removing unreachable block (ram,0x8001b320) */
/* WARNING: Removing unreachable block (ram,0x8001b318) */

void FUN_8001b308(int param_1)

{
  undefined4 *puVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  int iVar7;
  uint uVar8;
  float *pfVar9;
  float *pfVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  float local_c8;
  float local_c4;
  float local_c0;
  float local_bc;
  float local_b8;
  float local_b4;
  undefined4 local_b0;
  uint uStack_ac;
  int local_a8;
  float *local_a4;
  float *local_a0;
  float *local_9c;
  float *local_98;
  float *local_94;
  float *local_90;
  float *local_8c;
  float *local_88;
  float *local_84;
  float *local_80;
  uint local_7c;
  
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
  if (*(char *)(param_1 + 0x19) == '\x02') {
    iVar7 = *(short *)(param_1 + 0x168) * 0xc;
    iVar4 = 0;
    puVar5 = (undefined4 *)(&DAT_803b0208 + iVar7);
    puVar6 = (undefined4 *)(&DAT_803b0148 + iVar7);
    for (iVar7 = 0; iVar7 <= *(short *)(param_1 + 0x168); iVar7 = iVar7 + 1) {
      iVar3 = iVar4 + 4;
      iVar2 = iVar4 + 8;
      *puVar5 = *(undefined4 *)(*(int *)(param_1 + 0x170) + iVar4);
      puVar5[1] = *(undefined4 *)(*(int *)(param_1 + 0x170) + iVar3);
      puVar5[2] = *(undefined4 *)(*(int *)(param_1 + 0x170) + iVar2);
      puVar5 = puVar5 + -3;
      puVar1 = (undefined4 *)(*(int *)(param_1 + 0x174) + iVar4);
      iVar4 = iVar4 + 0xc;
      *puVar6 = *puVar1;
      puVar6[1] = *(undefined4 *)(*(int *)(param_1 + 0x174) + iVar3);
      puVar6[2] = *(undefined4 *)(*(int *)(param_1 + 0x174) + iVar2);
      puVar6 = puVar6 + -3;
    }
    FUN_80005af4((float *)&DAT_803b0208,(float *)&DAT_803afe48,*(short *)(param_1 + 0x168) + 1);
    FUN_80005af4((float *)&DAT_803b0148,(float *)&DAT_803afb48,*(short *)(param_1 + 0x168) + 1);
    dVar11 = (double)FLOAT_80436db8;
    pfVar10 = (float *)&DAT_803afe48;
    pfVar9 = (float *)&DAT_803afb48;
    iVar7 = 0;
    dVar12 = DOUBLE_80436dc0;
    for (local_a8 = 0; local_a8 < *(short *)(param_1 + 0x168); local_a8 = local_a8 + 1) {
      dVar13 = (double)FLOAT_80436db4;
      uVar8 = 0x20 / (int)*(short *)(param_1 + 0x168);
      local_80 = pfVar10 + 3;
      local_84 = pfVar10 + 6;
      local_88 = pfVar10 + 9;
      local_8c = pfVar10 + 4;
      local_90 = pfVar10 + 1;
      local_94 = pfVar10 + 7;
      local_98 = pfVar10 + 10;
      local_9c = pfVar10 + 5;
      local_a0 = pfVar10 + 2;
      local_a4 = pfVar10 + 8;
      local_7c = uVar8 ^ 0x80000000;
      for (iVar4 = 0; iVar4 < (int)uVar8; iVar4 = iVar4 + 1) {
        uStack_ac = local_7c;
        local_b0 = 0x43300000;
        local_b4 = (float)(dVar13 * (double)(float)(dVar13 * (double)(float)(dVar13 * (double)*
                                                  local_a0 + (double)*local_9c) + (double)*local_a4)
                          + (double)pfVar10[0xb]);
        local_c8 = (float)(dVar13 * (double)(float)(dVar13 * (double)(float)(dVar13 * (double)*
                                                  pfVar9 + (double)pfVar9[3]) + (double)pfVar9[6]) +
                          (double)pfVar9[9]);
        local_bc = (float)(dVar13 * (double)(float)(dVar13 * (double)(float)(dVar13 * (double)*
                                                  pfVar10 + (double)*local_80) + (double)*local_84)
                          + (double)*local_88);
        local_b8 = (float)(dVar13 * (double)(float)(dVar13 * (double)(float)(dVar13 * (double)*
                                                  local_90 + (double)*local_8c) + (double)*local_94)
                          + (double)*local_98);
        local_c4 = (float)(dVar13 * (double)(float)(dVar13 * (double)(float)(dVar13 * (double)pfVar9
                                                  [1] + (double)pfVar9[4]) + (double)pfVar9[7]) +
                          (double)pfVar9[10]);
        local_c0 = (float)(dVar13 * (double)(float)(dVar13 * (double)(float)(dVar13 * (double)pfVar9
                                                  [2] + (double)pfVar9[5]) + (double)pfVar9[8]) +
                          (double)pfVar9[0xb]);
        dVar13 = (double)(float)(dVar13 + (double)(float)(dVar11 / (double)(float)((double)CONCAT44(
                                                  0x43300000,local_7c) - dVar12)));
        if (*(char *)(param_1 + 0x17c) != '\0') {
          gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x178),&local_c8,&local_c8);
          gnt4_PSMTXMultVec_bl(*(float **)(param_1 + 0x178),&local_bc,&local_bc);
        }
        FUN_8001b8d4(&local_c8,&local_bc,iVar7);
        FUN_8001b918(iVar7,*(undefined4 *)(param_1 + 0x15c));
        iVar7 = iVar7 + 1;
      }
      pfVar10 = pfVar10 + 0xc;
      pfVar9 = pfVar9 + 0xc;
    }
    FUN_8001b8d4(&local_c8,&local_bc,iVar7);
    FUN_8001b918(iVar7,*(undefined4 *)(param_1 + 0x15c));
    DAT_803c1140 = &DAT_803af590;
    DAT_803c1150 = &DAT_803af3a8;
    DAT_803c116a = (short)(iVar7 << 1) + 2;
    DAT_803c113c = 0;
    DAT_803c1174 = *(undefined4 *)(param_1 + 0x164);
    DAT_803c1164 = 2;
    DAT_803c1170 = *(undefined1 *)(param_1 + 0x17d);
    DAT_803c1160 = &DAT_803c0634;
    DAT_803c1172 = 0;
    DAT_803c1173 = 0xff;
    DAT_803c115c = *(int *)(&DAT_802ca018 + *(char *)(param_1 + 0x16c) * 4);
    if (DAT_803c115c == 0) {
      FUN_80051b2c(-0x7fc3eed0);
    }
    else {
      zz_0052214_(-0x7fc3eed0);
    }
  }
  return;
}



// ==== 8001b754  zz_001b754_ ====

void zz_001b754_(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = param_2 * 0xc;
  iVar3 = param_3 * 0xc;
  *(undefined4 *)(*(int *)(param_1 + 0x2c) + iVar3) =
       *(undefined4 *)(*(int *)(param_1 + 0x2c) + iVar1);
  iVar2 = *(int *)(param_1 + 0x2c) + 4;
  *(undefined4 *)(iVar2 + iVar3) = *(undefined4 *)(iVar2 + iVar1);
  iVar2 = *(int *)(param_1 + 0x2c) + 8;
  *(undefined4 *)(iVar2 + iVar3) = *(undefined4 *)(iVar2 + iVar1);
  *(undefined4 *)(*(int *)(param_1 + 0x30) + iVar3) =
       *(undefined4 *)(*(int *)(param_1 + 0x30) + iVar1);
  iVar2 = *(int *)(param_1 + 0x30) + 4;
  *(undefined4 *)(iVar2 + iVar3) = *(undefined4 *)(iVar2 + iVar1);
  iVar2 = *(int *)(param_1 + 0x30) + 8;
  *(undefined4 *)(iVar2 + iVar3) = *(undefined4 *)(iVar2 + iVar1);
  return;
}



// ==== 8001b7b8  zz_001b7b8_ ====

void zz_001b7b8_(int param_1,float *param_2,int param_3)

{
  float *pfVar1;
  int iVar2;
  float local_58;
  float local_54;
  float local_50;
  float local_4c;
  float local_48;
  float local_44;
  float afStack_40 [13];
  
  iVar2 = param_3 * 0xc;
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),param_2,(float *)((int)param_2[0xb] + iVar2));
  gnt4_PSMTXMultVec_bl((float *)(param_1 + 0x114),param_2 + 3,(float *)((int)param_2[0xc] + iVar2));
  if (*(char *)(param_2 + 0xe) != '\0') {
    pfVar1 = (float *)((int)param_2[0xb] + iVar2);
    local_4c = *pfVar1;
    local_48 = pfVar1[1];
    local_44 = pfVar1[2];
    pfVar1 = (float *)((int)param_2[0xc] + iVar2);
    local_58 = *pfVar1;
    local_54 = pfVar1[1];
    local_50 = pfVar1[2];
    gnt4_PSMTXInverse_bl(*(float **)(param_1 + 0x178),afStack_40);
    gnt4_PSMTXMultVec_bl(afStack_40,&local_4c,&local_4c);
    gnt4_PSMTXMultVec_bl(afStack_40,&local_58,&local_58);
    pfVar1 = (float *)((int)param_2[0xb] + iVar2);
    *pfVar1 = local_4c;
    pfVar1[1] = local_48;
    pfVar1[2] = local_44;
    pfVar1 = (float *)((int)param_2[0xc] + iVar2);
    *pfVar1 = local_58;
    pfVar1[1] = local_54;
    pfVar1[2] = local_50;
  }
  return;
}



// ==== 8001b8d4  FUN_8001b8d4 ====

void FUN_8001b8d4(undefined4 *param_1,undefined4 *param_2,int param_3)

{
  int iVar1;
  
  iVar1 = param_3 * 0x18;
  *(undefined4 *)(&DAT_803af590 + iVar1) = *param_1;
  *(undefined4 *)(&DAT_803af594 + iVar1) = param_1[1];
  *(undefined4 *)(&DAT_803af598 + iVar1) = param_1[2];
  *(undefined4 *)(&DAT_803af59c + iVar1) = *param_2;
  *(undefined4 *)(&DAT_803af5a0 + iVar1) = param_2[1];
  *(undefined4 *)(&DAT_803af5a4 + iVar1) = param_2[2];
  return;
}



// ==== 8001b918  FUN_8001b918 ====

void FUN_8001b918(int param_1,undefined4 param_2)

{
  *(undefined4 *)(&DAT_803af3a8 + param_1 * 8) = param_2;
  *(undefined4 *)(&DAT_803af3ac + param_1 * 8) = param_2;
  return;
}



// ==== 8001b934  FUN_8001b934 ====

void FUN_8001b934(int param_1)

{
  char cVar1;
  
  *(undefined *)(param_1 + 0x13) = PTR_DAT_80433934[0x44];
  cVar1 = PTR_DAT_80433934[0x44];
  PTR_DAT_80433934[0x44] = cVar1 + 1U;
  if ((byte)(cVar1 + 1U) < 0x80) {
    return;
  }
  PTR_DAT_80433934[0x44] = 0;
  return;
}



// ==== 8001b96c  FUN_8001b96c ====

bool FUN_8001b96c(uint param_1)

{
  uint uVar1;
  
  uVar1 = (uint)(byte)PTR_DAT_80433934[0x44];
  if (uVar1 < (param_1 & 0xff)) {
    uVar1 = uVar1 + 0x80 & 0xff;
  }
  return (param_1 & 0xff) + 0x10 < uVar1;
}



// ==== 8001b9ac  FUN_8001b9ac ====

/* WARNING: Removing unreachable block (ram,0x8001ba60) */
/* WARNING: Removing unreachable block (ram,0x8001b9bc) */

void FUN_8001b9ac(double param_1,undefined4 *param_2,undefined4 *param_3)

{
  float fVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  
  puVar3 = zz_008893c_(2,0x18,0,0);
  if (puVar3 != (undefined1 *)0x0) {
    *puVar3 = 1;
    puVar3[0x10] = 3;
    fVar1 = FLOAT_80436dc8;
    *(code **)(puVar3 + 0xc) = FUN_8001ba80;
    *(code **)(puVar3 + 0x10c) = FUN_8001bcf4;
    uVar2 = param_2[1];
    *(undefined4 *)(puVar3 + 100) = *param_2;
    *(undefined4 *)(puVar3 + 0x68) = uVar2;
    *(undefined4 *)(puVar3 + 0x6c) = param_2[2];
    uVar2 = param_3[1];
    *(undefined4 *)(puVar3 + 0x38) = *param_3;
    *(undefined4 *)(puVar3 + 0x3c) = uVar2;
    *(undefined4 *)(puVar3 + 0x40) = param_3[2];
    *(float *)(puVar3 + 0xb4) = (float)param_1;
    *(float *)(puVar3 + 0x58) = fVar1;
    *(float *)(puVar3 + 0x5c) = fVar1;
    *(float *)(puVar3 + 0x60) = fVar1;
    FUN_8001b934((int)puVar3);
  }
  return;
}



// ==== 8001ba80  FUN_8001ba80 ====

void FUN_8001ba80(int param_1)

{
  (*(code *)(&PTR_FUN_802ca050)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 8001babc  FUN_8001babc ====

void FUN_8001babc(int param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  bool bVar3;
  
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(undefined2 *)(param_1 + 0x1c) = 0xf0;
  uVar1 = DAT_802b0cb4;
  *(undefined2 *)(param_1 + 0x1e) = 0x1e;
  uVar2 = DAT_802b0cb8;
  *(undefined4 *)(param_1 + 0x9c) = uVar1;
  uVar1 = DAT_802b0cbc;
  *(undefined4 *)(param_1 + 0xa0) = uVar2;
  *(undefined4 *)(param_1 + 0xa4) = uVar1;
  bVar3 = zz_0045ef4_((float *)(param_1 + 0x114),5,param_1 + 0x38,param_1 + 0x9c);
  uVar1 = DAT_802b0cc4;
  if (bVar3) {
    *(undefined4 *)(param_1 + 0x9c) = DAT_802b0cc0;
    uVar2 = DAT_802b0cc8;
    *(undefined4 *)(param_1 + 0xa0) = uVar1;
    *(undefined4 *)(param_1 + 0xa4) = uVar2;
    zz_0045ef4_((float *)(param_1 + 0x114),5,param_1 + 0x38,param_1 + 0x9c);
  }
  *(undefined4 *)(param_1 + 0x118) = *(undefined4 *)(param_1 + 0x9c);
  *(undefined4 *)(param_1 + 0x128) = *(undefined4 *)(param_1 + 0xa0);
  *(undefined4 *)(param_1 + 0x138) = *(undefined4 *)(param_1 + 0xa4);
  *(undefined4 *)(param_1 + 0x11c) = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 300) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x13c) = *(undefined4 *)(param_1 + 0x40);
  *(undefined1 *)(param_1 + 0x98) = 5;
  *(undefined1 *)(param_1 + 0x84) = 0x11;
  *(code **)(param_1 + 0x100) = zz_0048288_;
  zz_0089100_(param_1,0,1);
  *(undefined1 *)(param_1 + 0x82) = 1;
  return;
}



// ==== 8001bbd0  FUN_8001bbd0 ====

void FUN_8001bbd0(int param_1)

{
  char cVar1;
  bool bVar3;
  short sVar2;
  
  bVar3 = FUN_8001b96c((uint)*(byte *)(param_1 + 0x13));
  if (bVar3) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    cVar1 = *(char *)(param_1 + 0x19);
    if (cVar1 == '\x01') {
      *(float *)(param_1 + 0x58) =
           (FLOAT_80436dcc *
            ((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000) -
                    DOUBLE_80436dd8) / FLOAT_80436dd0) + FLOAT_80436dcc) *
           *(float *)(param_1 + 0xb4);
      sVar2 = *(short *)(param_1 + 0x1e) + -1;
      *(short *)(param_1 + 0x1e) = sVar2;
      if (sVar2 < 0) {
        *(undefined1 *)(param_1 + 0x18) = 2;
      }
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      *(undefined4 *)(param_1 + 0x58) = *(undefined4 *)(param_1 + 0xb4);
      sVar2 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar2;
      if (sVar2 < 0) {
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      }
    }
    *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x58);
  }
  return;
}



// ==== 8001bcd4  FUN_8001bcd4 ====

void FUN_8001bcd4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8001bcf4  FUN_8001bcf4 ====

void FUN_8001bcf4(int param_1)

{
  DAT_803c113c = param_1 + 0x114;
  DAT_803c1150 = &DAT_802ca070;
  DAT_803c1140 = &DAT_802ca080;
  DAT_803c115c = &DAT_802ca060;
  DAT_803c1160 = &DAT_803c0634;
  DAT_803c1164 = 2;
  DAT_803c1174 = (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000) -
                        DOUBLE_80436dd8) / FLOAT_80436dd0;
  DAT_803c116a = 4;
  DAT_803c1170 = 1;
  DAT_803c1172 = 2;
  DAT_803c1173 = 0xff;
  zz_0052214_(-0x7fc3eed0);
  return;
}



// ==== 8001bda8  FUN_8001bda8 ====

void FUN_8001bda8(int param_1,undefined4 *param_2,undefined1 param_3)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  puVar2 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,0,1);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x10] = 4;
    puVar2[0x11] = param_3;
    *(code **)(puVar2 + 0xc) = FUN_8001bec8;
    *(code **)(puVar2 + 0x10c) = FUN_8001c1f4;
    uVar1 = param_2[1];
    *(undefined4 *)(puVar2 + 0x20) = *param_2;
    *(undefined4 *)(puVar2 + 0x24) = uVar1;
    *(undefined4 *)(puVar2 + 0x28) = param_2[2];
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



// ==== 8001bec8  FUN_8001bec8 ====

void FUN_8001bec8(int param_1)

{
  (*(code *)(&PTR_FUN_802ca140)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 8001bf04  FUN_8001bf04 ====

void FUN_8001bf04(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  uint uVar2;
  short *psVar3;
  undefined *puVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  
  puVar4 = &DAT_80433648;
  psVar3 = *(short **)(*(char *)(param_9 + 0x11) * 8 + -0x7fbcc9b4);
  *(undefined1 *)(param_9 + 0x12) = 0;
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(char *)(param_9 + 0x13) = (char)*(undefined4 *)(&DAT_80433648 + *(char *)(param_9 + 0x11) * 8);
  *(undefined2 *)(param_9 + 0x1c) = 0;
  *(short *)(param_9 + 0x1e) = psVar3[1];
  uVar2 = zz_00055fc_();
  *(short *)(param_9 + 0x72) = (short)(uVar2 << 8);
  uVar1 = *(undefined4 *)(*(int *)(param_9 + 0x8c) + 0xb4);
  *(undefined4 *)(param_9 + 0x15c) = uVar1;
  *(undefined4 *)(param_9 + 0x158) = uVar1;
  *(undefined4 *)(param_9 + 0x154) = uVar1;
  zz_0018f88_((int *)(param_9 + 0x144),*(int *)(psVar3 + 2),(float *)(param_9 + 0x58));
  FUN_8001c294((float *)(param_9 + 0x58),(float *)(param_9 + 0x58),(float *)(param_9 + 0x154));
  zz_0019338_((int *)(param_9 + 0x14c),*(int *)(psVar3 + 4),(float *)(param_9 + 0x160));
  *(code **)(param_9 + 0x100) = FUN_8001c234;
  uVar5 = zz_0089100_(param_9,1,1);
  zz_0006fb4_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),(int)*psVar3,puVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)*(float *)(param_9 + 0x160),*(int *)(param_9 + 0xe0));
  *(undefined1 *)(param_9 + 0x82) = 1;
  return;
}



// ==== 8001c028  FUN_8001c028 ====

void FUN_8001c028(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar3;
  undefined8 uVar4;
  
  if (*(char *)(param_9 + 0x12) == '\0') {
    *(short *)(param_9 + 0x72) = *(short *)(param_9 + 0x72) + 0x1000;
  }
  *(short *)(param_9 + 0x1c) = *(short *)(param_9 + 0x1c) + 1;
  zz_0018fd8_((int *)(param_9 + 0x144),(int)*(short *)(param_9 + 0x1c),(float *)(param_9 + 0x58));
  FUN_8001c294((float *)(param_9 + 0x58),(float *)(param_9 + 0x58),(float *)(param_9 + 0x154));
  zz_0019370_((int *)(param_9 + 0x14c),(int)*(short *)(param_9 + 0x1c),(float *)(param_9 + 0x160));
  if (*(short *)(param_9 + 0x1e) <= *(short *)(param_9 + 0x1c)) {
    cVar1 = *(char *)(param_9 + 0x12) + '\x01';
    *(char *)(param_9 + 0x12) = cVar1;
    if (cVar1 < *(char *)(param_9 + 0x13)) {
      iVar2 = *(int *)(*(char *)(param_9 + 0x11) * 8 + -0x7fbcc9b4);
      *(undefined2 *)(param_9 + 0x1c) = 0;
      psVar3 = (short *)(iVar2 + *(char *)(param_9 + 0x12) * 0xc);
      *(short *)(param_9 + 0x1e) = psVar3[1];
      *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(param_9 + 0x58);
      *(undefined4 *)(param_9 + 0x158) = *(undefined4 *)(param_9 + 0x5c);
      *(undefined4 *)(param_9 + 0x15c) = *(undefined4 *)(param_9 + 0x60);
      zz_0018f88_((int *)(param_9 + 0x144),*(int *)(psVar3 + 2),(float *)(param_9 + 0x58));
      FUN_8001c294((float *)(param_9 + 0x58),(float *)(param_9 + 0x58),(float *)(param_9 + 0x154));
      uVar4 = zz_0019338_((int *)(param_9 + 0x14c),*(int *)(psVar3 + 4),(float *)(param_9 + 0x160));
      zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                  *(int *)(param_9 + 0xe0),(int)*psVar3,iVar2,in_r7,in_r8,in_r9,in_r10);
    }
    else {
      *(undefined1 *)(param_9 + 0x18) = 2;
    }
  }
  zz_0007cac_((double)*(float *)(param_9 + 0x160),*(int *)(param_9 + 0xe0));
  return;
}



// ==== 8001c1ac  FUN_8001c1ac ====

void FUN_8001c1ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8001c1f4  FUN_8001c1f4 ====

void FUN_8001c1f4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 8001c234  FUN_8001c234 ====

void FUN_8001c234(int param_1)

{
  gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                     (double)*(float *)(param_1 + 0x28),(float *)(param_1 + 0x114));
  zz_00457d4_('y',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x72));
  zz_00456a0_((float *)(param_1 + 0x114),(float *)(param_1 + 0x114),(float *)(param_1 + 0x58));
  return;
}



// ==== 8001c294  FUN_8001c294 ====

void FUN_8001c294(float *param_1,float *param_2,float *param_3)

{
  *param_1 = *param_2 * *param_3;
  param_1[1] = param_2[1] * param_3[1];
  param_1[2] = param_2[2] * param_3[2];
  return;
}



// ==== 8001c2c8  FUN_8001c2c8 ====

void FUN_8001c2c8(int param_1)

{
  undefined1 *puVar1;
  short *psVar2;
  
  if ((char)(&PTR_DAT_802ca344)[*(char *)(param_1 + 1000)][*(byte *)(param_1 + 0x3e9)] != -1) {
    for (psVar2 = (short *)(&PTR_DAT_802ca258)
                           [(char)(&PTR_DAT_802ca344)[*(char *)(param_1 + 1000)]
                                  [*(byte *)(param_1 + 0x3e9)]]; -1 < *psVar2; psVar2 = psVar2 + 6)
    {
      puVar1 = zz_0088aa0_(param_1,2,0x18,0,0);
      if (puVar1 != (undefined1 *)0x0) {
        *puVar1 = 1;
        puVar1[0x10] = 6;
        *(code **)(puVar1 + 0xc) = FUN_8001c42c;
        *(code **)(puVar1 + 0x10c) = FUN_8001c70c;
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
        puVar1[0x89] = (char)*psVar2;
        puVar1[0x11] = (char)psVar2[1];
        puVar1[0x12] = (char)*(undefined4 *)(psVar2 + 4);
        *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(psVar2 + 2);
      }
    }
  }
  return;
}



// ==== 8001c42c  FUN_8001c42c ====

void FUN_8001c42c(int param_1)

{
  (*(code *)(&PTR_FUN_802ca384)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 8001c468  FUN_8001c468 ====

void FUN_8001c468(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  double dVar3;
  float local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(code **)(param_9 + 0x100) = FUN_8001c5ac;
  zz_0089100_(param_9,(int)*(char *)(param_9 + 0x96) + 0x10,1);
  fVar2 = FLOAT_80436de4;
  fVar1 = FLOAT_80436de0;
  dVar3 = (double)FLOAT_80436de0;
  *(float *)(param_9 + 0x9c) = FLOAT_80436de0;
  *(float *)(param_9 + 0xa0) = fVar1;
  *(float *)(param_9 + 0xa4) = fVar2;
  if (DAT_80436208 != 0) {
    zz_0040e94_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_80436208,&local_18
               );
    dVar3 = gnt4_PSVECMag_bl(&local_18);
    if ((double)FLOAT_80436de8 < dVar3) {
      *(float *)(param_9 + 0x9c) = local_18;
      *(undefined4 *)(param_9 + 0xa0) = local_14;
      *(undefined4 *)(param_9 + 0xa4) = local_10;
    }
  }
  *(float *)(param_9 + 0x144) = FLOAT_80436de4;
  *(undefined1 *)(param_9 + 0x82) = 1;
  zz_001c524_(param_9);
  return;
}



// ==== 8001c524  zz_001c524_ ====

void zz_001c524_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if (*(char *)(param_1 + 0x11) == '\x01') {
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(iVar1 + 0x8dc);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(iVar1 + 0x8ec);
    *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(iVar1 + 0x8fc);
  }
  if ((*(char *)(iVar1 + 0x18) < '\x02') && (*(short *)(iVar1 + 1000) == *(short *)(param_1 + 0x94))
     ) {
    return;
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8001c58c  FUN_8001c58c ====

void FUN_8001c58c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8001c5ac  FUN_8001c5ac ====

/* WARNING: Removing unreachable block (ram,0x8001c6ec) */
/* WARNING: Removing unreachable block (ram,0x8001c5bc) */

void FUN_8001c5ac(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_58;
  undefined4 local_54;
  undefined4 local_50;
  float afStack_4c [13];
  
  iVar4 = *(int *)(param_1 + 0x90);
  iVar3 = iVar4 + *(char *)(param_1 + 0x89) * 0x30;
  local_58 = *(float *)(iVar3 + 0x8e0);
  local_54 = *(undefined4 *)(iVar3 + 0x8f0);
  local_50 = *(undefined4 *)(iVar3 + 0x900);
  FUN_8003f688(iVar4,&local_58,(float *)(param_1 + 0x20),(float *)(param_1 + 0x38));
  zz_0045ef4_((float *)(param_1 + 0x114),4,param_1 + 0x38,param_1 + 0x9c);
  dVar6 = (double)(*(float *)(param_1 + 0xb4) * *(float *)(iVar4 + 0x7fc) * *(float *)(iVar4 + 0xb4)
                  );
  dVar5 = dVar6;
  if (*(char *)(param_1 + 0x11) == '\0') {
    dVar5 = (double)(float)(dVar6 * (double)FLOAT_80436dec);
  }
  gnt4_PSMTXScale_bl(dVar5,dVar6,(double)FLOAT_80436de4,afStack_4c);
  gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_4c,(float *)(param_1 + 0x114));
  fVar1 = FLOAT_80436df0;
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  fVar1 = fVar1 * *(float *)(iVar4 + 0x7fc) * *(float *)(iVar4 + 0xb4);
  dVar6 = (double)(fVar1 * fVar1);
  dVar5 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),&local_58);
  fVar2 = FLOAT_80436de4;
  fVar1 = FLOAT_80436de0;
  if (dVar5 <= dVar6) {
    *(float *)(param_1 + 0x144) = FLOAT_80436de4 - (float)(dVar5 / dVar6);
    if (fVar1 <= *(float *)(param_1 + 0x144)) {
      if (fVar2 < *(float *)(param_1 + 0x144)) {
        *(float *)(param_1 + 0x144) = fVar2;
      }
    }
    else {
      *(float *)(param_1 + 0x144) = fVar1;
    }
  }
  else {
    *(float *)(param_1 + 0x144) = FLOAT_80436de0;
  }
  return;
}



// ==== 8001c70c  FUN_8001c70c ====

void FUN_8001c70c(int param_1)

{
  char cVar1;
  
  cVar1 = zz_008b290_();
  if (cVar1 == '\0') {
    if (*(char *)(*(int *)(param_1 + 0x90) + 0x82) != '\0') {
      if (*(char *)(*(int *)(param_1 + 0x90) + 0x592) == '\0') {
        if (*(char *)(param_1 + 0x11) == '\0') {
          DAT_803c1140 = &DAT_802ca3c4;
          DAT_803c115c = &DAT_802ca394;
        }
        else {
          DAT_803c1140 = (&PTR_DAT_802ca484)[*(char *)(param_1 + 0x12)];
          DAT_803c115c = &DAT_802ca3a4;
        }
        DAT_803c113c = param_1 + 0x114;
        DAT_803c1150 = &DAT_802ca3b4;
        DAT_803c1174 = FLOAT_80436df4 * *(float *)(param_1 + 0x144);
        DAT_803c1160 = &DAT_803c0634;
        DAT_803c1164 = 1;
        DAT_803c116a = 4;
        DAT_803c1170 = 1;
        DAT_803c1172 = 2;
        DAT_803c1173 = 0xff;
        zz_0052214_(-0x7fc3eed0);
      }
    }
  }
  return;
}



// ==== 8001c80c  zz_001c80c_ ====

void zz_001c80c_(char *param_1)

{
  uint uVar1;
  
  param_1[0x2e4] = '\0';
  param_1[0x2e5] = '\0';
  param_1[0x2e6] = '\0';
  param_1[0x2e7] = '\0';
  param_1[0x32c] = '\0';
  param_1[0x32d] = '\0';
  param_1[0x337] = '\0';
  param_1[0x338] = '\0';
  param_1[0x336] = '\0';
  param_1[0x347] = '\0';
  param_1[0x33e] = '\0';
  param_1[0x33f] = '\0';
  param_1[0x340] = '\0';
  param_1[0x341] = '\0';
  param_1[0x33a] = '\0';
  param_1[0x33b] = '\0';
  uVar1 = zz_00055fc_();
  *(short *)(param_1 + 0x33c) = (short)uVar1;
  param_1[0x308] = '\0';
  param_1[0x309] = '\0';
  param_1[0x328] = '\0';
  param_1[0x329] = '\0';
  param_1[0x30f] = '\0';
  zz_0021b9c_((int)param_1);
  zz_0022744_((int)param_1);
  zz_00227b0_((int)param_1);
  zz_0023234_((int)param_1);
  zz_00232a0_((int)param_1);
  param_1[0x346] = '\0';
  param_1[0x335] = '\0';
  param_1[0x366] = '\0';
  param_1[0x367] = '\0';
  param_1[0x368] = '\0';
  param_1[0x369] = '\0';
  param_1[0x36a] = '\0';
  param_1[0x36b] = '\0';
  param_1[0x373] = '\0';
  param_1[0x374] = '\0';
  param_1[0x375] = '\0';
  param_1[0x377] = '\0';
  param_1[0x37e] = '\0';
  param_1[0x38d] = '\0';
  param_1[0x38e] = '\0';
  param_1[0x38f] = '\0';
  *(undefined2 *)(param_1 + 0x37c) = *(undefined2 *)(param_1 + 0x1c6);
  param_1[0x30a] = '\0';
  param_1[0x30b] = '\0';
  if (PTR_DAT_80433934[0x15dd] == '\0') {
    param_1[0x339] = '\0';
    param_1[0x352] = '\0';
    param_1[0x37f] = '\0';
    param_1[0x1e9] = '\0';
    param_1[0x1ea] = '\0';
    if (param_1[0x439] < '\x01') {
      param_1[0x339] = param_1[0x339] | 0x10;
    }
  }
  else {
    param_1[0x339] = PTR_DAT_80433934[param_1[0x3e4] + 0x15e0];
    param_1[0x352] = PTR_DAT_80433934[param_1[0x3e4] + 0x15e6];
    param_1[0x37f] = PTR_DAT_80433934[param_1[0x3e4] + 0x15ec];
    param_1[0x1e9] = PTR_DAT_80433934[param_1[0x3e4] + 0x15f2];
    param_1[0x1ea] = PTR_DAT_80433934[param_1[0x3e4] + 0x15f8];
  }
  FUN_800263ec((int)param_1);
  zz_002532c_(param_1);
  zz_0020fd4_((int)param_1);
  uVar1 = zz_00055fc_();
  *(ushort *)(param_1 + 0x328) = (ushort)uVar1 & 7;
  return;
}



// ==== 8001c9d0  zz_001c9d0_ ====

/* WARNING: Removing unreachable block (ram,0x8001d034) */
/* WARNING: Removing unreachable block (ram,0x8001c9e0) */

void zz_001c9d0_(char *param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  
  param_1[0x5cf] = '\0';
  param_1[0x5ce] = '\0';
  param_1[0x5cd] = '\0';
  param_1[0x5cc] = '\0';
  param_1[0x5cb] = '\0';
  param_1[0x5ca] = '\0';
  param_1[0x5b4] = '\0';
  param_1[0x5b5] = '\0';
  param_1[0x5b6] = '\0';
  param_1[0x5b7] = '\0';
  *(short *)(param_1 + 0x33c) = *(short *)(param_1 + 0x33c) + 1;
  if (*(short *)(param_1 + 1000) != 0xe04) {
    if ((((PTR_DAT_80433930[0x32] == '\0') &&
         (iVar3 = *(int *)(PTR_DAT_80433934 + 0xbc), iVar3 != 0)) &&
        (*(short *)(iVar3 + 1000) == 0xe04)) && (*(char *)(iVar3 + 0x88) != param_1[0x88])) {
      param_1[0x352] = '\n';
    }
    if (param_1[0x352] == '\x02') {
      if (param_1[0x1da] == '\0') {
        dVar7 = (double)FLOAT_80436df8;
        iVar5 = 0;
        iVar3 = DAT_803c4e84;
        do {
          if ((param_1[0x88] != *(char *)(iVar3 + 0x88)) &&
             (dVar6 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(iVar3 + 0x20))
             , dVar6 <= dVar7)) {
            param_1[0x352] = '\0';
            break;
          }
          iVar5 = iVar5 + 1;
          iVar3 = iVar3 + 0x1e00;
        } while (iVar5 < 6);
      }
      else {
        param_1[0x352] = '\0';
      }
    }
    FUN_80025a84((int)param_1);
    if (param_1[0x364] == '\0') {
      if ((param_1[0x2e4] != '\v') && (zz_00252bc_(param_1), param_1[0x6cb] != '\0')) {
        param_1[0x2e4] = '\v';
        param_1[0x2e5] = '\0';
        param_1[0x2e6] = '\0';
        param_1[0x2e7] = '\0';
      }
      zz_0026050_(param_1);
    }
    else {
      zz_00262b4_((int)param_1);
    }
    iVar3 = zz_0026368_();
    if (iVar3 == 0) {
      switch(param_1[0x661]) {
      case '\x03':
        cVar1 = param_1[0x2e4];
        if (cVar1 == '\x01') {
          zz_001d934_(param_1);
          FUN_80024bb4((int)param_1);
          zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,(int)param_1[0x337] ^ 0x80000000)
                                     - DOUBLE_80436e18),
                      (double)(float)((double)CONCAT44(0x43300000,(int)param_1[0x338] ^ 0x80000000)
                                     - DOUBLE_80436e18),(int)param_1,0);
        }
        else if (cVar1 < '\x01') {
          if (-1 < cVar1) {
            zz_001d464_((int)param_1);
            FUN_80024bb4((int)param_1);
            zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,(int)param_1[0x337] ^ 0x80000000
                                                        ) - DOUBLE_80436e18),
                        (double)(float)((double)CONCAT44(0x43300000,(int)param_1[0x338] ^ 0x80000000
                                                        ) - DOUBLE_80436e18),(int)param_1,0);
          }
        }
        else if (cVar1 == '\x06') {
          zz_002065c_((int)param_1);
        }
        break;
      default:
        if (((param_1[0x2e4] != '\n') && (param_1[0x2e4] != '\v')) &&
           ((param_1[0x1da] != '\0' && ((*(uint *)(param_1 + 0x5e0) & 0x1000000) != 0)))) {
          param_1[0x2e4] = '\n';
          param_1[0x2e5] = '\0';
          param_1[0x2e7] = '\0';
          uVar4 = zz_00055fc_();
          if ((uVar4 & 1) == 0) {
            param_1[0x2e6] = '\x01';
          }
          else {
            param_1[0x2e6] = '\0';
          }
        }
        if ((param_1[0x2e4] != '\x01') && (param_1[0x2e4] != '\x02')) {
          param_1[0x33a] = '\0';
          param_1[0x33b] = '\0';
        }
        switch(param_1[0x2e4]) {
        case '\0':
          zz_001d058_(param_1);
          break;
        case '\x01':
        case '\x02':
          zz_001d5a0_(param_1);
          break;
        case '\x03':
          zz_001f69c_((int)param_1);
          break;
        case '\x04':
          zz_001fb28_(param_1);
          break;
        case '\x05':
          zz_00201f8_((int)param_1);
          break;
        case '\x06':
          zz_00203f4_((int)param_1);
          break;
        case '\n':
          FUN_800209a4((int)param_1);
          break;
        case '\v':
          zz_0020c0c_((int)param_1);
        }
        break;
      case '\x06':
        cVar1 = param_1[0x2e4];
        if (cVar1 == '\x01') {
          zz_001dd20_(param_1);
          FUN_80024f64((int)param_1);
          zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,(int)param_1[0x337] ^ 0x80000000)
                                     - DOUBLE_80436e18),
                      (double)(float)((double)CONCAT44(0x43300000,(int)param_1[0x338] ^ 0x80000000)
                                     - DOUBLE_80436e18),(int)param_1,0);
        }
        else if (cVar1 < '\x01') {
          if (-1 < cVar1) {
            zz_001d464_((int)param_1);
            FUN_80024f64((int)param_1);
            zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,(int)param_1[0x337] ^ 0x80000000
                                                        ) - DOUBLE_80436e18),
                        (double)(float)((double)CONCAT44(0x43300000,(int)param_1[0x338] ^ 0x80000000
                                                        ) - DOUBLE_80436e18),(int)param_1,0);
          }
        }
        else if (cVar1 == '\x06') {
          zz_00207d4_((int)param_1);
        }
        break;
      case '\a':
        sVar2 = *(short *)(param_1 + 1000);
        if ((((sVar2 == 0x603) || (sVar2 == 0x60b)) || (sVar2 == 0x60d)) || (sVar2 == 0x60f)) {
          FUN_800251d0((int)param_1);
        }
        cVar1 = param_1[0x2e4];
        if (cVar1 == '\x03') {
          zz_001f69c_((int)param_1);
        }
        else if (cVar1 < '\x03') {
          if (cVar1 == '\0') {
            zz_001d4e4_(param_1);
          }
        }
        else if (cVar1 < '\x05') {
          zz_001fb28_(param_1);
        }
        break;
      case '\b':
      case '\t':
      case '\v':
        cVar1 = param_1[0x2e4];
        if (cVar1 == '\x03') {
          zz_001f69c_((int)param_1);
        }
        else if (cVar1 < '\x03') {
          if (cVar1 == '\0') {
            zz_001d53c_(param_1);
          }
          else if (-1 < cVar1) {
            zz_001e04c_(param_1);
          }
        }
        break;
      case '\n':
        iVar3 = *(int *)(param_1 + 0x304);
        if (iVar3 != 0) {
          *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(iVar3 + 0x20);
          *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(iVar3 + 0x28);
          *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(iVar3 + 0x24);
          if (*(float *)(iVar3 + 0x24) <= *(float *)(param_1 + 0x24)) {
            dVar7 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(iVar3 + 0x20));
            if ((double)FLOAT_80436dfc < dVar7) {
              dVar6 = 1.0 / SQRT(dVar7);
              dVar6 = DOUBLE_80436e00 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_80436e08);
              dVar6 = DOUBLE_80436e00 * dVar6 * -(dVar7 * dVar6 * dVar6 - DOUBLE_80436e08);
              dVar7 = (double)(float)(dVar7 * DOUBLE_80436e00 * dVar6 *
                                              -(dVar7 * dVar6 * dVar6 - DOUBLE_80436e08));
            }
            if ((dVar7 <= (double)FLOAT_80436e10) && ((*(uint *)(param_1 + 0x5b8) & 0x400) == 0)) {
              *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
            }
          }
        }
        zz_0024900_((int)param_1,1);
      }
      zz_00234e4_((int)param_1);
      FUN_8002645c((int)param_1);
    }
  }
  return;
}



// ==== 8001d058  zz_001d058_ ====

void zz_001d058_(char *param_1)

{
  char cVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  
  param_1[0x346] = '\0';
  if ((param_1[0x352] == '\b') &&
     (*(float *)(param_1 + 0x24) <= *(float *)(param_1 + 0x358) - FLOAT_80436e20)) {
    param_1[0x352] = '\0';
  }
  if (param_1[0x38d] == '\x02') {
    zz_0023bf4_((int)param_1);
    zz_002104c_((int)param_1);
  }
  else {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      iVar2 = zz_002115c_((int)param_1);
      if (iVar2 != 0) {
        zz_0021134_((int)param_1);
        return;
      }
    }
    else {
      uVar3 = zz_00694c0_((int)param_1);
      if ((uVar3 != 0) && (iVar2 = zz_002115c_((int)param_1), iVar2 != 0)) {
        zz_0021148_((int)param_1);
        return;
      }
    }
    iVar2 = zz_00228fc_(param_1);
    if (iVar2 == 0) {
      uVar3 = zz_0021db0_(param_1);
      if (uVar3 == 0) {
        if (param_1[0x352] != '\t') {
          if (param_1[0x661] == '\x02') {
            *(short *)(param_1 + 0x328) = *(short *)(param_1 + 0x328) + -1;
            cVar1 = param_1[0x2e5];
            if (cVar1 == '\x01') {
              *(short *)(param_1 + 0x34c) = *(short *)(param_1 + 0x34c) + -1;
              dVar4 = FUN_8003d964((double)*(float *)(param_1 + 0x668),(int)param_1,
                                   (float *)(param_1 + 0x20));
              if (*(float *)(param_1 + 0x24) < (float)(dVar4 + (double)*(float *)(param_1 + 0x36c)))
              {
                dVar4 = zz_003f320_((double)(*(float *)(param_1 + 0x30) +
                                            *(float *)(param_1 + 0x6d4)),(float *)(param_1 + 0x20));
                if (dVar4 < (double)(FLOAT_80436e24 * *(float *)(param_1 + 0x668) +
                                    *(float *)(param_1 + 0x24))) {
                  param_1[0x2e5] = '\x02';
                }
                else {
                  if ((*(uint *)(param_1 + 0x5b8) & 0x100) == 0) {
                    *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
                  }
                  if ((*(short *)(param_1 + 0x34c) < 1) && (*(short *)(param_1 + 0x328) < 1)) {
                    zz_0023bf4_((int)param_1);
                    zz_002104c_((int)param_1);
                  }
                }
              }
              else {
                param_1[0x2e5] = '\x02';
              }
              zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,
                                                           (int)param_1[0x337] ^ 0x80000000) -
                                         DOUBLE_80436e18),
                          (double)(float)((double)CONCAT44(0x43300000,
                                                           (int)param_1[0x338] ^ 0x80000000) -
                                         DOUBLE_80436e18),(int)param_1,1);
            }
            else if (cVar1 < '\x01') {
              if (-1 < cVar1) {
                dVar4 = FUN_8003d964((double)*(float *)(param_1 + 0x668),(int)param_1,
                                     (float *)(param_1 + 0x20));
                if (*(float *)(param_1 + 0x24) <
                    (float)(dVar4 + (double)*(float *)(param_1 + 0x36c))) {
                  param_1[0x2e5] = '\x01';
                  param_1[0x34c] = '\0';
                  param_1[0x34d] = '<';
                }
                else {
                  param_1[0x2e5] = '\x02';
                }
                zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,
                                                             (int)param_1[0x337] ^ 0x80000000) -
                                           DOUBLE_80436e18),
                            (double)(float)((double)CONCAT44(0x43300000,
                                                             (int)param_1[0x338] ^ 0x80000000) -
                                           DOUBLE_80436e18),(int)param_1,1);
              }
            }
            else if ((cVar1 < '\x03') && (*(short *)(param_1 + 0x328) < 1)) {
              zz_0023bf4_((int)param_1);
              zz_002104c_((int)param_1);
            }
          }
          else if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
            if (*(short *)(param_1 + 0x328) < 1) {
              zz_0023bf4_((int)param_1);
              zz_002104c_((int)param_1);
            }
            else {
              *(short *)(param_1 + 0x328) = *(short *)(param_1 + 0x328) + -1;
            }
          }
          else {
            cVar1 = param_1[0x2e5];
            if (cVar1 == '\x01') {
              if (param_1[0x336] != '\0') {
                zz_0020c2c_((int)param_1);
              }
            }
            else if ((cVar1 < '\x01') && (-1 < cVar1)) {
              param_1[0x2e5] = '\x01';
              iVar2 = zz_0026370_((int)param_1);
              if (iVar2 == 0) {
                param_1[0x336] = '\0';
                param_1[0x347] = '\0';
              }
              else {
                param_1[0x336] = '\x01';
                param_1[0x347] = '\0';
              }
            }
            zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,(int)param_1[0x337] ^ 0x80000000
                                                        ) - DOUBLE_80436e18),
                        (double)(float)((double)CONCAT44(0x43300000,(int)param_1[0x338] ^ 0x80000000
                                                        ) - DOUBLE_80436e18),(int)param_1,1);
          }
        }
      }
      else {
        zz_0021100_((int)param_1);
      }
    }
    else {
      zz_002111c_((int)param_1);
    }
  }
  return;
}



// ==== 8001d464  zz_001d464_ ====

void zz_001d464_(int param_1)

{
  uint uVar1;
  int iVar2;
  
  *(undefined1 *)(param_1 + 0x346) = 0;
  uVar1 = zz_00694c0_(param_1);
  if ((uVar1 == 0) || (iVar2 = zz_002115c_(param_1), iVar2 == 0)) {
    if (*(short *)(param_1 + 0x328) < 1) {
      zz_0023bf4_(param_1);
      zz_002104c_(param_1);
    }
    else {
      *(short *)(param_1 + 0x328) = *(short *)(param_1 + 0x328) + -1;
    }
  }
  else {
    zz_0021148_(param_1);
  }
  return;
}



// ==== 8001d4e4  zz_001d4e4_ ====

void zz_001d4e4_(char *param_1)

{
  int iVar1;
  uint uVar2;
  
  iVar1 = zz_00228fc_(param_1);
  if (iVar1 == 0) {
    uVar2 = zz_0021db0_(param_1);
    if (uVar2 != 0) {
      zz_0021100_((int)param_1);
    }
  }
  else {
    zz_002111c_((int)param_1);
  }
  return;
}



// ==== 8001d53c  zz_001d53c_ ====

void zz_001d53c_(char *param_1)

{
  uint uVar1;
  
  if (*(short *)(param_1 + 0x328) < 1) {
    zz_0023bf4_((int)param_1);
    zz_002104c_((int)param_1);
  }
  else {
    *(short *)(param_1 + 0x328) = *(short *)(param_1 + 0x328) + -1;
  }
  uVar1 = zz_0021db0_(param_1);
  if (uVar1 != 0) {
    zz_0021100_((int)param_1);
  }
  return;
}



// ==== 8001d5a0  zz_001d5a0_ ====

void zz_001d5a0_(char *param_1)

{
  char cVar1;
  int iVar2;
  
  if (*(short *)(param_1 + 0x308) != 0) {
    *(short *)(param_1 + 0x308) = *(short *)(param_1 + 0x308) + -1;
  }
  cVar1 = param_1[0x2e5];
  if (cVar1 == '\x06') {
    param_1[0x2e4] = '\x01';
    param_1[0x2e7] = '\0';
    zz_001ef84_((int)param_1);
  }
  else if (cVar1 < '\x06') {
    if (cVar1 < '\x02') {
      if (-1 < cVar1) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x10) == 0) {
          param_1[0x2e4] = '\x01';
          param_1[0x2e7] = '\0';
          zz_001e11c_(param_1);
        }
        else {
          iVar2 = zz_001d6ec_((int)param_1);
          if (iVar2 != 0) {
            zz_001e11c_(param_1);
          }
        }
      }
    }
    else if (cVar1 < '\x04') {
      param_1[0x2e4] = '\x01';
      param_1[0x2e7] = '\0';
      zz_001e810_((int)param_1);
    }
    else {
      iVar2 = zz_001d6ec_((int)param_1);
      if (iVar2 != 0) {
        FUN_8001e9a4(param_1);
      }
    }
  }
  else if (cVar1 == '\b') {
    iVar2 = zz_001d6ec_((int)param_1);
    if (iVar2 != 0) {
      zz_001f438_(param_1);
    }
  }
  else if ((cVar1 < '\b') && (iVar2 = zz_001d6ec_((int)param_1), iVar2 != 0)) {
    zz_001f034_(param_1);
  }
  return;
}



// ==== 8001d6ec  zz_001d6ec_ ====

undefined4 zz_001d6ec_(int param_1)

{
  char cVar1;
  uint uVar2;
  
  if (*(char *)(param_1 + 0x2e4) == '\x02') {
    if ((*(short *)(param_1 + 1000) == 0xc04) || (*(char *)(param_1 + 0x661) == '\x04')) {
      zz_0021100_(param_1);
      return 0;
    }
    cVar1 = *(char *)(param_1 + 0x2e7);
    if (cVar1 == '\x02') {
      if (((*(uint *)(param_1 + 0x5e0) & 3) == 0) && (*(char *)(param_1 + 0x661) != '\b')) {
        *(undefined1 *)(param_1 + 0x2e4) = 1;
        *(undefined1 *)(param_1 + 0x2e7) = 0;
      }
      else if ((*(char *)(param_1 + 0x30b) == '\x01') &&
              ((*(int *)(param_1 + 0x508) != 0 && (0 < *(short *)(param_1 + 0x350))))) {
        if (*(short *)(param_1 + *(char *)(param_1 + 0x353) * 8 + 0x774) < 1) {
          *(undefined1 *)(param_1 + 0x2e7) = 3;
        }
        else {
          *(short *)(param_1 + 0x350) = *(short *)(param_1 + 0x350) + -1;
          if ((*(uint *)(param_1 + 0x5b8) & (int)*(short *)(param_1 + 0x33e)) == 0) {
            *(uint *)(param_1 + 0x5b4) =
                 *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x33e);
          }
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x2e7) = 3;
      }
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
          *(undefined1 *)(param_1 + 0x2e7) = 1;
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x33e)
          ;
        }
        else if (*(char *)(*(int *)(param_1 + 0x4b0) + (int)*(char *)(param_1 + 0x584) + 0xb8) ==
                 '\0') {
          *(undefined1 *)(param_1 + 0x2e7) = 3;
        }
        else {
          *(undefined1 *)(param_1 + 0x2e7) = 2;
          uVar2 = zz_00055fc_();
          *(ushort *)(param_1 + 0x350) = ((ushort)uVar2 & 0x7f) + 0x78;
          if (*(short *)(param_1 + 1000) == 0x904) {
            *(undefined2 *)(param_1 + 0x350) = 600;
          }
        }
      }
      else if (-1 < cVar1) {
        if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
          *(undefined1 *)(param_1 + 0x2e7) = 0;
        }
        else if (*(char *)(*(int *)(param_1 + 0x4b0) + (int)*(char *)(param_1 + 0x584) + 0xb8) ==
                 '\0') {
          *(undefined1 *)(param_1 + 0x2e7) = 3;
        }
        else {
          *(undefined1 *)(param_1 + 0x2e7) = 2;
          uVar2 = zz_00055fc_();
          *(ushort *)(param_1 + 0x350) = ((ushort)uVar2 & 0x7f) + 0x78;
          if (*(short *)(param_1 + 1000) == 0x904) {
            *(undefined2 *)(param_1 + 0x350) = 600;
          }
        }
      }
    }
    else if ((cVar1 < '\x04') && ((*(uint *)(param_1 + 0x5e0) & 3) == 0)) {
      *(undefined1 *)(param_1 + 0x2e4) = 1;
      *(undefined1 *)(param_1 + 0x2e7) = 0;
    }
  }
  return 1;
}



// ==== 8001d934  zz_001d934_ ====

void zz_001d934_(char *param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  uint unaff_r31;
  double dVar5;
  
  cVar1 = param_1[0x2e5];
  if (cVar1 == '\x01') {
    cVar1 = param_1[0x2e7];
    if (cVar1 == '\x02') {
      if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
        param_1[0x2e5] = '\0';
        param_1[0x2e6] = '\0';
        param_1[0x2e7] = '\0';
      }
      else if (((param_1[0x30b] == '\x01') && (*(int *)(param_1 + 0x508) != 0)) &&
              (0 < *(short *)(param_1 + 0x350))) {
        if (*(short *)(param_1 + param_1[0x353] * 8 + 0x774) < 1) {
          param_1[0x2e7] = '\x03';
        }
        else {
          *(short *)(param_1 + 0x350) = *(short *)(param_1 + 0x350) + -1;
          if ((*(uint *)(param_1 + 0x5b8) & (int)*(short *)(param_1 + 0x33e)) == 0) {
            *(uint *)(param_1 + 0x5b4) =
                 *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x33e);
          }
        }
      }
      else {
        param_1[0x2e7] = '\x03';
      }
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
          param_1[0x2e7] = '\x01';
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x33e)
          ;
        }
        else {
          param_1[0x2e7] = '\x02';
          uVar2 = zz_00055fc_();
          *(ushort *)(param_1 + 0x350) = ((ushort)uVar2 & 0x7f) + 0x78;
        }
      }
      else if (-1 < cVar1) {
        if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
          param_1[0x2e7] = '\0';
        }
        else {
          param_1[0x2e7] = '\x02';
          uVar2 = zz_00055fc_();
          *(ushort *)(param_1 + 0x350) = ((ushort)uVar2 & 0x7f) + 0x78;
        }
      }
    }
    else if ((cVar1 < '\x04') && ((*(uint *)(param_1 + 0x5e0) & 3) == 0)) {
      param_1[0x2e5] = '\0';
      param_1[0x2e6] = '\0';
      param_1[0x2e7] = '\0';
    }
    zz_0024b24_((int)param_1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    uVar2 = zz_00694c0_((int)param_1);
    if ((uVar2 == 0) || (iVar3 = zz_002115c_((int)param_1), iVar3 == 0)) {
      cVar1 = param_1[0x2e6];
      if (cVar1 == '\x01') {
        if ((*(uint *)(param_1 + 0x5e0) & 0x80) == 0) {
          if ((*(uint *)(param_1 + 0x5b8) & 0x100) == 0) {
            *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
          }
        }
        else {
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
          param_1[0x2e6] = '\x02';
        }
      }
      else if (cVar1 < '\x01') {
        if (((-1 < cVar1) &&
            (*(short *)(*(int *)(param_1 + 0x4ac) + 4) <= *(short *)(param_1 + 0x736))) &&
           (bVar4 = zz_002512c_((double)FLOAT_80436e28,(int)param_1), !bVar4)) {
          uVar2 = zz_0027704_((int)param_1,(float *)(param_1 + 0x2e8));
          unaff_r31 = uVar2 & 0xffff;
          if ((unaff_r31 < 0x1000) || (0xf000 < unaff_r31)) {
            param_1[0x2e6] = '\x01';
          }
        }
      }
      else if (cVar1 < '\x03') {
        dVar5 = (double)FLOAT_80436e2c;
        *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
        bVar4 = zz_002512c_(dVar5,(int)param_1);
        if (bVar4) {
          param_1[0x2e6] = '\0';
        }
        else if ((*(uint *)(param_1 + 0x5e0) & 0x80) == 0) {
          param_1[0x2e6] = '\0';
        }
      }
      if (*(int *)(param_1 + 0x300) != 0) {
        uVar2 = zz_0027704_((int)param_1,(float *)(param_1 + 0x50c));
        unaff_r31 = uVar2 & 0xffff;
        if ((unaff_r31 < 0x1800) || (0xe800 < unaff_r31)) {
          zz_002288c_((int)param_1);
          zz_002281c_((int)param_1);
        }
        if ((unaff_r31 < 0x800) || (0xf800 < unaff_r31)) {
          zz_002288c_((int)param_1);
          zz_002281c_((int)param_1);
        }
      }
      uVar2 = zz_0021db0_(param_1);
      if ((uVar2 == 0) || ((0x17ff < (int)unaff_r31 && ((int)unaff_r31 < 0xe801)))) {
        if (*(short *)(param_1 + 0x308) != 0) {
          *(short *)(param_1 + 0x308) = *(short *)(param_1 + 0x308) + -1;
        }
        bVar4 = zz_002512c_((double)FLOAT_80436e30,(int)param_1);
        if ((bVar4) || (*(short *)(param_1 + 0x308) == 0)) {
          zz_0020fd4_((int)param_1);
        }
        else {
          zz_0024a94_((int)param_1);
        }
      }
      else {
        param_1[0x2e5] = '\x01';
        param_1[0x2e6] = '\0';
        param_1[0x2e7] = '\0';
        zz_0024b24_((int)param_1);
      }
    }
    else {
      zz_0021148_((int)param_1);
    }
  }
  return;
}



// ==== 8001dd20  zz_001dd20_ ====

void zz_001dd20_(char *param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  bool bVar4;
  uint unaff_r30;
  
  cVar1 = param_1[0x2e5];
  if (cVar1 == '\x01') {
    cVar1 = param_1[0x2e7];
    if (cVar1 == '\x02') {
      if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
        param_1[0x2e5] = '\0';
        param_1[0x2e6] = '\0';
        param_1[0x2e7] = '\0';
      }
      else if (((param_1[0x30b] == '\x01') && (*(int *)(param_1 + 0x508) != 0)) &&
              (0 < *(short *)(param_1 + 0x350))) {
        if (*(short *)(param_1 + param_1[0x353] * 8 + 0x774) < 1) {
          param_1[0x2e7] = '\x03';
        }
        else {
          *(short *)(param_1 + 0x350) = *(short *)(param_1 + 0x350) + -1;
          if ((*(uint *)(param_1 + 0x5b8) & (int)*(short *)(param_1 + 0x33e)) == 0) {
            *(uint *)(param_1 + 0x5b4) =
                 *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x33e);
          }
        }
      }
      else {
        param_1[0x2e7] = '\x03';
      }
    }
    else if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
          param_1[0x2e7] = '\x01';
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x33e)
          ;
        }
        else {
          param_1[0x2e7] = '\x02';
          uVar2 = zz_00055fc_();
          *(ushort *)(param_1 + 0x350) = ((ushort)uVar2 & 0x7f) + 0x78;
        }
      }
      else if (-1 < cVar1) {
        if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
          param_1[0x2e7] = '\0';
        }
        else {
          param_1[0x2e7] = '\x02';
          uVar2 = zz_00055fc_();
          *(ushort *)(param_1 + 0x350) = ((ushort)uVar2 & 0x7f) + 0x78;
        }
      }
    }
    else if ((cVar1 < '\x04') && ((*(uint *)(param_1 + 0x5e0) & 3) == 0)) {
      param_1[0x2e5] = '\0';
      param_1[0x2e6] = '\0';
      param_1[0x2e7] = '\0';
    }
    FUN_80024ea8((int)param_1);
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    uVar2 = zz_00694c0_((int)param_1);
    if ((uVar2 == 0) || (iVar3 = zz_002115c_((int)param_1), iVar3 == 0)) {
      if (*(int *)(param_1 + 0x300) != 0) {
        uVar2 = zz_0027704_((int)param_1,(float *)(param_1 + 0x50c));
        unaff_r30 = uVar2 & 0xffff;
        if ((unaff_r30 < 0x1800) || (0xe800 < unaff_r30)) {
          zz_002288c_((int)param_1);
          zz_002281c_((int)param_1);
        }
        if ((unaff_r30 < 0x800) || (0xf800 < unaff_r30)) {
          zz_002288c_((int)param_1);
          zz_002281c_((int)param_1);
        }
      }
      uVar2 = zz_0021db0_(param_1);
      if (uVar2 != 0) {
        bVar4 = false;
        if (*(short *)(param_1 + 1000) == 0xd02) {
          if (((int)unaff_r30 < 0x1800) || (0xe800 < (int)unaff_r30)) {
            bVar4 = true;
          }
        }
        else if (((int)unaff_r30 < 0x4000) || (0xc000 < (int)unaff_r30)) {
          bVar4 = true;
        }
        if (bVar4) {
          param_1[0x2e5] = '\x01';
          param_1[0x2e6] = '\0';
          param_1[0x2e7] = '\0';
          FUN_80024ea8((int)param_1);
          return;
        }
      }
      if (*(short *)(param_1 + 0x308) != 0) {
        *(short *)(param_1 + 0x308) = *(short *)(param_1 + 0x308) + -1;
      }
      bVar4 = zz_002512c_((double)FLOAT_80436e34,(int)param_1);
      if ((bVar4) || (*(short *)(param_1 + 0x308) == 0)) {
        zz_0020fd4_((int)param_1);
      }
      else {
        FUN_80024dec((int)param_1);
      }
    }
    else {
      zz_0021148_((int)param_1);
    }
  }
  return;
}



// ==== 8001e04c  zz_001e04c_ ====

void zz_001e04c_(char *param_1)

{
  int iVar1;
  bool bVar3;
  uint uVar2;
  
  iVar1 = zz_001d6ec_((int)param_1);
  if (iVar1 != 0) {
    if (*(short *)(param_1 + 0x308) != 0) {
      *(short *)(param_1 + 0x308) = *(short *)(param_1 + 0x308) + -1;
    }
    if (param_1[0x2e4] == '\x01') {
      bVar3 = zz_002512c_((double)FLOAT_80436e30,(int)param_1);
      if ((bVar3) || (*(short *)(param_1 + 0x308) == 0)) {
        zz_0020fd4_((int)param_1);
        return;
      }
      uVar2 = zz_0021db0_(param_1);
      if (uVar2 != 0) {
        zz_00210ec_((int)param_1);
      }
    }
    else {
      bVar3 = zz_002512c_((double)FLOAT_80436e30,(int)param_1);
      if ((bVar3) || (*(short *)(param_1 + 0x308) == 0)) {
        zz_0023bf4_((int)param_1);
      }
    }
    zz_0024900_((int)param_1,1);
  }
  return;
}



// ==== 8001e11c  zz_001e11c_ ====

/* WARNING: Removing unreachable block (ram,0x8001e7f0) */
/* WARNING: Removing unreachable block (ram,0x8001e12c) */

void zz_001e11c_(char *param_1)

{
  int iVar1;
  uint uVar2;
  bool bVar3;
  double dVar4;
  double dVar5;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  float local_2c;
  float local_28;
  undefined4 local_24;
  
  param_1[0x377] = '\0';
  if (*(short *)(param_1 + 0x33a) != 0) {
    *(short *)(param_1 + 0x33a) = *(short *)(param_1 + 0x33a) + -1;
  }
  if (param_1[0x2e4] == '\x01') {
    iVar1 = zz_002115c_((int)param_1);
    if (iVar1 != 0) {
      zz_0021134_((int)param_1);
      return;
    }
    iVar1 = zz_00228fc_(param_1);
    if (iVar1 != 0) {
      zz_002111c_((int)param_1);
      return;
    }
    uVar2 = zz_0021db0_(param_1);
    if (uVar2 != 0) {
      zz_00210ec_((int)param_1);
    }
    if (param_1[0x661] == '\x02') {
      if ((param_1[0x2e5] == '\0') &&
         ((bVar3 = zz_002512c_((double)FLOAT_80436e30,(int)param_1), bVar3 ||
          (*(short *)(param_1 + 0x308) == 0)))) {
        zz_0020fd4_((int)param_1);
        return;
      }
    }
    else if ((param_1[0x2e5] == '\0') &&
            ((bVar3 = FUN_8002507c((double)FLOAT_80436e30,(int)param_1), bVar3 ||
             (*(short *)(param_1 + 0x308) == 0)))) {
      zz_0020fd4_((int)param_1);
      return;
    }
  }
  else if (param_1[0x661] == '\x02') {
    if ((param_1[0x2e5] == '\0') &&
       ((bVar3 = zz_002512c_((double)FLOAT_80436e30,(int)param_1), bVar3 ||
        (*(short *)(param_1 + 0x308) == 0)))) {
      zz_0023bf4_((int)param_1);
    }
  }
  else if ((param_1[0x2e5] == '\0') &&
          ((bVar3 = FUN_8002507c((double)FLOAT_80436e30,(int)param_1), bVar3 ||
           (*(short *)(param_1 + 0x308) == 0)))) {
    zz_0023bf4_((int)param_1);
  }
  zz_0024900_((int)param_1,1);
  if ((((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) && (param_1[0x661] != '\x02')) &&
     (param_1[0x38d] != '\x02')) {
    param_1[0x2e5] = '\b';
    iVar1 = zz_0026370_((int)param_1);
    param_1[0x336] = (char)iVar1;
    param_1[0x347] = '\0';
    return;
  }
  if (param_1[0x2e5] != '\0') {
    iVar1 = zz_0023b18_((int)param_1,(float *)(param_1 + 0x20));
    if ((iVar1 != 0) && (*(short *)(param_1 + 0x308) != 0)) {
      return;
    }
    param_1[0x2e5] = '\x03';
    *(undefined4 *)(param_1 + 0x2e8) = *(undefined4 *)(param_1 + 0x2f4);
    *(undefined4 *)(param_1 + 0x2ec) = *(undefined4 *)(param_1 + 0x2f8);
    *(undefined4 *)(param_1 + 0x2f0) = *(undefined4 *)(param_1 + 0x2fc);
    zz_0024824_((int)param_1);
    return;
  }
  dVar4 = zz_003f320_((double)(*(float *)(param_1 + 0x30) + *(float *)(param_1 + 0x6d4)),
                      (float *)(param_1 + 0x20));
  if (*(short *)(param_1 + 0x33a) != 0) {
    if ((((double)(FLOAT_80436e24 * *(float *)(param_1 + 0x668) + *(float *)(param_1 + 0x24)) <=
          dVar4) && (bVar3 = zz_002512c_((double)FLOAT_80436e40,(int)param_1), !bVar3)) &&
       ((*(uint *)(param_1 + 0x5e0) & 2) == 0)) {
      if (param_1[0x661] == '\x02') {
        param_1[0x2e5] = '\x06';
      }
      else if (param_1[0x7cd] == '\x01') {
        if (*(short *)(*(int *)(param_1 + 0x4ac) + 4) <= *(short *)(param_1 + 0x736)) {
          param_1[0x2e5] = '\x06';
        }
      }
      else {
        param_1[0x2e5] = '\x06';
      }
    }
    iVar1 = zz_00238b4_((int)param_1);
    if (iVar1 == 0) {
      return;
    }
    if (param_1[0x661] == '\x02') {
      param_1[0x2e5] = '\x02';
      return;
    }
    if (param_1[0x7cd] == '\x01') {
      if (*(short *)(param_1 + 0x736) < *(short *)(*(int *)(param_1 + 0x4ac) + 4)) {
        return;
      }
      param_1[0x2e5] = '\x02';
      return;
    }
    param_1[0x2e5] = '\x02';
    return;
  }
  bVar3 = false;
  if (((param_1[0x38d] != '\x02') &&
      (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x668) < *(float *)(param_1 + 0x2ec))) &&
     (iVar1 = zz_0023b18_((int)param_1,(float *)(param_1 + 0x20)), iVar1 != 0)) {
    param_1[0x2e5] = '\x01';
    *(undefined4 *)(param_1 + 0x2f4) = *(undefined4 *)(param_1 + 0x2e8);
    *(undefined4 *)(param_1 + 0x2f8) = *(undefined4 *)(param_1 + 0x2ec);
    *(undefined4 *)(param_1 + 0x2fc) = *(undefined4 *)(param_1 + 0x2f0);
    FUN_800245d0((int)param_1,(float *)(param_1 + 0x20));
    bVar3 = true;
  }
  if (!bVar3) {
    iVar1 = zz_00238b4_((int)param_1);
    if (iVar1 == 1) {
      if (param_1[0x661] == '\x02') {
        param_1[0x2e5] = '\x02';
      }
      else if (param_1[0x7cd] == '\x01') {
        if (*(short *)(*(int *)(param_1 + 0x4ac) + 4) <= *(short *)(param_1 + 0x736)) {
          param_1[0x2e5] = '\x02';
        }
      }
      else {
        param_1[0x2e5] = '\x02';
      }
    }
    else if ((iVar1 == 2) && (param_1[0x38d] != '\x02')) {
      param_1[0x2e5] = '\x01';
      *(undefined4 *)(param_1 + 0x2f4) = *(undefined4 *)(param_1 + 0x2e8);
      *(undefined4 *)(param_1 + 0x2f8) = *(undefined4 *)(param_1 + 0x2ec);
      *(undefined4 *)(param_1 + 0x2fc) = *(undefined4 *)(param_1 + 0x2f0);
      FUN_800245d0((int)param_1,(float *)(param_1 + 0x20));
    }
    local_38 = *(float *)(param_1 + 0x20);
    local_34 = *(undefined4 *)(param_1 + 0x24);
    local_30 = *(undefined4 *)(param_1 + 0x28);
    local_2c = *(float *)(param_1 + 0x2e8);
    local_28 = *(float *)(param_1 + 0x2ec);
    local_24 = *(undefined4 *)(param_1 + 0x2f0);
    gnt4_PSVECSubtract_bl(&local_2c,&local_38,&local_2c);
    dVar5 = gnt4_PSVECMag_bl(&local_2c);
    if (((double)FLOAT_80436e38 < dVar5) &&
       (gnt4_PSVECNormalize_bl(&local_2c,&local_2c), FLOAT_80436e3c <= local_28)) {
      if (param_1[0x661] == '\x02') {
        param_1[0x2e5] = '\x02';
        param_1[0x377] = '\x01';
      }
      else if (param_1[0x7cd] == '\x01') {
        if (*(short *)(*(int *)(param_1 + 0x4ac) + 4) <= *(short *)(param_1 + 0x736)) {
          param_1[0x2e5] = '\x02';
          param_1[0x377] = '\x01';
        }
      }
      else {
        param_1[0x2e5] = '\x02';
        param_1[0x377] = '\x01';
      }
    }
    if ((*(uint *)(param_1 + 0x5e0) & 2) == 0) {
      if (param_1[0x661] == '\x02') {
        if ((((*(ushort *)(param_1 + 0x33c) & 0x3f) == 0) &&
            ((double)(FLOAT_80436e24 * *(float *)(param_1 + 0x668) + *(float *)(param_1 + 0x24)) <=
             dVar4)) && (bVar3 = zz_002512c_((double)FLOAT_80436e40,(int)param_1), !bVar3)) {
          param_1[0x2e5] = '\x06';
        }
      }
      else if ((((*(ushort *)(param_1 + 0x33c) & 0x7f) == 0) &&
               ((double)(FLOAT_80436e24 * *(float *)(param_1 + 0x668) + *(float *)(param_1 + 0x24))
                <= dVar4)) && (bVar3 = zz_002512c_((double)FLOAT_80436e40,(int)param_1), !bVar3)) {
        if (param_1[0x7cd] == '\x01') {
          if (*(short *)(*(int *)(param_1 + 0x4ac) + 4) <= *(short *)(param_1 + 0x736)) {
            param_1[0x2e5] = '\x06';
          }
        }
        else {
          param_1[0x2e5] = '\x06';
        }
      }
    }
  }
  if ((param_1[0x274] & 1U) == 0) {
    if (param_1[0x346] < '\x01') {
      return;
    }
    param_1[0x346] = param_1[0x346] + -1;
    return;
  }
  param_1[0x346] = param_1[0x346] + '\x02';
  if (param_1[0x346] < '\b') {
    return;
  }
  param_1[0x346] = '\0';
  iVar1 = FUN_800452a0((double)*(float *)(param_1 + 0x8dc),(double)*(float *)(param_1 + 0x8fc));
  uVar2 = zz_0021c08_((int)param_1,(short)iVar1);
  if (uVar2 == 2) {
    param_1[0x32c] = '6';
  }
  else {
    if ((int)uVar2 < 2) {
      if (uVar2 != 0) {
        if (-1 < (int)uVar2) {
          param_1[0x32c] = -0x36;
        }
        goto LAB_8001e694;
      }
    }
    else if (3 < (int)uVar2) goto LAB_8001e694;
    uVar2 = zz_00055fc_();
    if ((uVar2 & 1) == 0) {
      param_1[0x32c] = -0x36;
    }
    else {
      param_1[0x32c] = '6';
    }
  }
LAB_8001e694:
  param_1[0x32d] = '\0';
  zz_0021134_((int)param_1);
  return;
}



// ==== 8001e810  zz_001e810_ ====

void zz_001e810_(int param_1)

{
  char cVar1;
  int iVar2;
  
  iVar2 = zz_0023b18_(param_1,(float *)(param_1 + 0x20));
  if (iVar2 == 0) {
    if (*(char *)(param_1 + 0x2e5) == '\x03') {
      if (*(float *)(param_1 + 0x2ec) < *(float *)(param_1 + 0x24)) {
        zz_0024900_(param_1,1);
      }
    }
    else {
      zz_0024900_(param_1,1);
    }
  }
  cVar1 = *(char *)(param_1 + 0x5e4);
  if ((cVar1 != '\x05') && (cVar1 != '\x06')) {
    if ((cVar1 == '\x04') || (cVar1 == '\b')) {
      *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
    }
    else if ((*(uint *)(param_1 + 0x5b8) & 0x100) == 0) {
      *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
    }
    if ((*(short *)(param_1 + 1000) == 0x203) && (*(char *)(param_1 + 0x38d) == '\x02')) {
      if (*(char *)(param_1 + 0x2e5) == '\x02') {
        *(undefined1 *)(param_1 + 0x2e5) = 4;
      }
      else {
        *(undefined1 *)(param_1 + 0x2e5) = 5;
      }
      *(undefined2 *)(param_1 + 0x34c) = 2;
      *(undefined1 *)(param_1 + 0x30c) = 5;
      *(undefined1 *)(param_1 + 0x30e) = 0;
      *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(param_1 + 0x24);
      *(float *)(param_1 + 0x318) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0);
      *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
    }
    return;
  }
  if (*(char *)(param_1 + 0x2e5) == '\x02') {
    *(undefined1 *)(param_1 + 0x2e5) = 4;
  }
  else {
    *(undefined1 *)(param_1 + 0x2e5) = 5;
  }
  *(undefined2 *)(param_1 + 0x34c) = 2;
  *(undefined1 *)(param_1 + 0x30c) = 5;
  *(undefined1 *)(param_1 + 0x30e) = 0;
  *(undefined4 *)(param_1 + 0x310) = *(undefined4 *)(param_1 + 0x24);
  *(float *)(param_1 + 0x318) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0);
  *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
  return;
}



// ==== 8001e9a4  FUN_8001e9a4 ====

/* WARNING: Removing unreachable block (ram,0x8001ef68) */
/* WARNING: Removing unreachable block (ram,0x8001e9b4) */

void FUN_8001e9a4(char *param_1)

{
  bool bVar1;
  bool bVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  float fStack_58;
  float local_54;
  float afStack_4c [3];
  float local_40;
  float local_3c;
  undefined4 local_38;
  float local_34;
  float local_30;
  undefined4 local_2c;
  
  if (*(float *)(param_1 + 0x318) < *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0)) {
    *(undefined4 *)(param_1 + 0x314) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x318) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x31c) = *(undefined4 *)(param_1 + 0x28);
    *(float *)(param_1 + 0x318) = *(float *)(param_1 + 0x318) + *(float *)(param_1 + 0x6d0);
  }
  uVar3 = zz_00694c0_((int)param_1);
  if ((uVar3 == 0) || (iVar4 = zz_002115c_((int)param_1), iVar4 == 0)) {
    iVar4 = zz_00228fc_(param_1);
    if (iVar4 == 0) {
      uVar3 = zz_0021db0_(param_1);
      if (uVar3 != 0) {
        zz_00210ec_((int)param_1);
      }
      local_40 = *(float *)(param_1 + 0x20);
      bVar2 = false;
      local_38 = *(undefined4 *)(param_1 + 0x28);
      local_3c = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0);
      local_34 = *(float *)(param_1 + 0x2e8);
      local_2c = *(undefined4 *)(param_1 + 0x2f0);
      local_30 = local_3c;
      gnt4_PSVECSubtract_bl(&local_34,&local_40,&local_34);
      dVar7 = gnt4_PSVECMag_bl(&local_34);
      if ((double)FLOAT_80436e38 < dVar7) {
        if (param_1[0x2e5] == '\x05') {
          if ((double)(FLOAT_80436e44 + *(float *)(param_1 + 0x668)) < dVar7) {
            dVar7 = (double)(FLOAT_80436e44 + *(float *)(param_1 + 0x668));
          }
        }
        else if ((double)*(float *)(param_1 + 0x668) < dVar7) {
          dVar7 = (double)*(float *)(param_1 + 0x668);
        }
        gnt4_PSVECNormalize_bl(&local_34,&local_34);
        gnt4_PSQUATScale_bl(dVar7,&local_34,&local_34);
        gnt4_PSVECAdd_bl(&local_40,&local_34,&local_34);
        dVar7 = (double)FLOAT_80436e48;
        local_30 = local_3c - (*(float *)(param_1 + 0x24) - *(float *)(param_1 + 0x5ec));
        if (dVar7 < (double)*(float *)(param_1 + 0x668)) {
          iVar4 = 5;
          dVar7 = (double)(float)((double)*(float *)(param_1 + 0x668) / (double)FLOAT_80436e4c);
        }
        else {
          iVar4 = 2;
        }
        for (iVar6 = 0; local_3c = local_30, iVar6 < iVar4; iVar6 = iVar6 + 1) {
          iVar5 = zz_003e978_(&local_40,&local_34,afStack_4c);
          if ((iVar5 == 2) || (iVar5 == 1)) {
            bVar2 = true;
            if (param_1[0x30c] != '\0') {
              param_1[0x30c] = param_1[0x30c] + -1;
            }
            break;
          }
          iVar5 = FUN_80037814(&local_40,&local_34,afStack_4c);
          if (iVar5 != 0) {
            bVar2 = true;
            break;
          }
          local_30 = (float)((double)local_3c + dVar7);
        }
      }
      if (param_1[0x280] != '\0') {
        bVar2 = true;
      }
      if ((param_1[0x377] != '\0') &&
         (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0) < *(float *)(param_1 + 0x2ec))) {
        bVar2 = true;
      }
      iVar4 = zz_0023b18_((int)param_1,(float *)(param_1 + 0x20));
      if (iVar4 == 0) {
        bVar1 = false;
        if ((((param_1[0x274] & 1U) != 0) || ((param_1[0x274] & 2U) != 0)) &&
           (*(float *)(param_1 + 0x1d0) < FLOAT_80436dfc)) {
          bVar1 = true;
        }
        if (param_1[0x377] != '\0') {
          bVar1 = true;
        }
        if (!bVar1) {
          if (param_1[0x2e5] == '\x05') {
            if (*(float *)(param_1 + 0x2ec) < *(float *)(param_1 + 0x24)) {
              zz_0024900_((int)param_1,1);
            }
            if ((param_1[0x30c] == '\0') && (!bVar2)) {
              zz_0024900_((int)param_1,1);
            }
          }
          else {
            zz_0024900_((int)param_1,1);
          }
        }
      }
      if (param_1[0x2e5] == '\x05') {
        if (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0) <
            *(float *)(param_1 + 0x2ec) + *(float *)(param_1 + 0x66c)) {
          bVar2 = true;
        }
        if ((param_1[0x30c] == '\0') && (!bVar2)) {
          bVar2 = false;
        }
      }
      if (bVar2) {
        if (param_1[0x661] == '\x02') {
          if (FLOAT_80436e50 < *(float *)(param_1 + 0x48)) {
            *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
          }
          else if ((*(uint *)(param_1 + 0x5b8) & 0x100) == 0) {
            *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
          }
        }
        else if (FLOAT_80436dfc <= *(float *)(param_1 + 0x48)) {
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
        }
        else if (param_1[0x7cd] == '\x01') {
          if (*(short *)(param_1 + 0x736) < 1) {
            param_1[0x2e5] = '\b';
            param_1[0x30e] = '\x01';
            param_1[0x336] = '\0';
            param_1[0x347] = '\0';
          }
        }
        else if ((int)param_1[0x747] < (int)(uint)*(byte *)(*(int *)(param_1 + 0x4ac) + 0x9f)) {
          if ((*(uint *)(param_1 + 0x5b8) & 0x100) == 0) {
            if (*(short *)(param_1 + 0x34c) < 1) {
              param_1[0x34c] = '\0';
              param_1[0x34d] = '\x02';
              *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
            }
            else {
              *(short *)(param_1 + 0x34c) = *(short *)(param_1 + 0x34c) + -1;
            }
          }
        }
        else {
          param_1[0x2e5] = '\b';
          param_1[0x30e] = '\x01';
          param_1[0x336] = '\0';
          param_1[0x347] = '\0';
        }
      }
      else if (param_1[0x661] == '\x02') {
        param_1[0x2e5] = '\b';
        iVar4 = zz_0026370_((int)param_1);
        param_1[0x336] = (char)iVar4;
        param_1[0x347] = '\0';
      }
      else if (param_1[0x7cd] == '\x01') {
        param_1[0x2e5] = '\a';
        param_1[0x2e6] = '\0';
      }
      else {
        param_1[0x2e5] = '\b';
        iVar4 = zz_0026370_((int)param_1);
        param_1[0x336] = (char)iVar4;
        param_1[0x347] = '\0';
      }
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        param_1[0x2e5] = '\0';
      }
      else if ((((param_1[0x274] & 2U) == 0) ||
               (dVar7 = gnt4_PSVECSquareMag_bl((float *)(param_1 + 0x1cc)),
               dVar7 <= (double)FLOAT_80436dfc)) ||
              (gnt4_PSVECNormalize_bl((float *)(param_1 + 0x1cc),&fStack_58),
              FLOAT_80436e54 < local_54)) {
        if ('\0' < param_1[0x346]) {
          param_1[0x346] = param_1[0x346] + -1;
        }
      }
      else {
        param_1[0x346] = param_1[0x346] + '\x02';
        if ('\a' < param_1[0x346]) {
          param_1[0x346] = '\0';
          param_1[0x2e5] = '\b';
          iVar4 = zz_0026370_((int)param_1);
          param_1[0x336] = (char)iVar4;
          param_1[0x347] = '\0';
        }
      }
    }
    else {
      zz_002111c_((int)param_1);
    }
  }
  else {
    zz_0021148_((int)param_1);
  }
  return;
}



// ==== 8001ef84  zz_001ef84_ ====

void zz_001ef84_(int param_1)

{
  char cVar1;
  uint uVar2;
  
  zz_0024900_(param_1,1);
  cVar1 = *(char *)(param_1 + 0x5e4);
  if ((cVar1 == '\x05') || (cVar1 == '\b')) {
    *(undefined1 *)(param_1 + 0x2e5) = 7;
    *(undefined1 *)(param_1 + 0x2e6) = 0;
    *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
    uVar2 = zz_00055fc_();
    *(ushort *)(param_1 + 0x34c) = (ushort)uVar2 & 0xf;
    *(short *)(param_1 + 0x34c) = *(short *)(param_1 + 0x34c) << 3;
  }
  else if (cVar1 == '\x04') {
    *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
  }
  else if ((*(uint *)(param_1 + 0x5b8) & 0x100) == 0) {
    *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
  }
  return;
}



// ==== 8001f034  zz_001f034_ ====

void zz_001f034_(char *param_1)

{
  char cVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  bool bVar5;
  double dVar6;
  
  iVar3 = zz_00228fc_(param_1);
  if (iVar3 == 0) {
    uVar4 = zz_0021db0_(param_1);
    if (uVar4 != 0) {
      zz_00210ec_((int)param_1);
    }
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      param_1[0x2e5] = '\0';
      zz_0024900_((int)param_1,1);
    }
    else {
      uVar4 = zz_00694c0_((int)param_1);
      if (uVar4 == 0) {
        if ((param_1[0x661] == '\x02') || (param_1[0x661] == '\x05')) {
          if ((*(uint *)(param_1 + 0x5e0) & 0x80) != 0) {
            *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
          }
          param_1[0x336] = '\0';
          zz_0020fd4_((int)param_1);
        }
        else {
          param_1[0x2e5] = '\b';
          iVar3 = zz_0026370_((int)param_1);
          param_1[0x336] = (char)iVar3;
          param_1[0x347] = '\0';
          zz_0024900_((int)param_1,1);
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
        }
      }
      else {
        iVar3 = zz_002115c_((int)param_1);
        if (iVar3 == 0) {
          bVar5 = zz_002512c_((double)FLOAT_80436e20,(int)param_1);
          if (bVar5) {
            if ((param_1[0x661] == '\x02') || (param_1[0x661] == '\x05')) {
              if (((*(uint *)(param_1 + 0x5e0) & 0x80) != 0) &&
                 ((*(uint *)(param_1 + 0x5b8) & 0x400) == 0)) {
                *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
                param_1[0x336] = '\0';
                zz_0020fd4_((int)param_1);
              }
            }
            else {
              param_1[0x2e5] = '\b';
              iVar3 = zz_0026370_((int)param_1);
              param_1[0x336] = (char)iVar3;
              param_1[0x347] = '\0';
              zz_0024900_((int)param_1,1);
              *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
            }
          }
          else {
            cVar1 = param_1[0x2e6];
            if (cVar1 == '\x02') {
              param_1[0x2e6] = '\x01';
              if ((param_1[0x661] == '\x02') || (param_1[0x661] == '\x05')) {
                zz_0024900_((int)param_1,1);
              }
            }
            else if (cVar1 < '\x02') {
              if (cVar1 == '\0') {
                dVar6 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),(int)param_1,
                                     (float *)(param_1 + 0x20));
                if (((FLOAT_80436e30 +
                      (float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x34c) ^ 0x80000000) -
                             DOUBLE_80436e18) <=
                      (float)((double)(*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0)) -
                             dVar6)) || (*(float *)(param_1 + 0x48) < FLOAT_80436dfc)) ||
                   ((param_1[0x274] & 2U) != 0)) {
                  param_1[0x2e6] = '\x01';
                  uVar2 = *(ushort *)(*(int *)(param_1 + 0x4ac) + 4);
                  *(ushort *)(param_1 + 0x344) =
                       ((short)uVar2 >> 2) + (ushort)((short)uVar2 < 0 && (uVar2 & 3) != 0);
                  uVar4 = zz_00055fc_();
                  *(ushort *)(param_1 + 0x344) =
                       *(short *)(param_1 + 0x344) +
                       *(short *)(param_1 + 0x344) * ((ushort)uVar4 & 3);
                }
                else {
                  zz_0024900_((int)param_1,1);
                }
              }
              else if (-1 < cVar1) {
                if ((*(uint *)(param_1 + 0x5e0) & 0x80) == 0) {
                  param_1[0x2e6] = '\x02';
                }
                else {
                  param_1[0x2e6] = '\x03';
                }
                zz_0024900_((int)param_1,0);
                if ((param_1[0x661] == '\x02') || (param_1[0x661] == '\x05')) {
                  *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x400;
                }
              }
            }
            else if (cVar1 < '\x04') {
              if ((*(uint *)(param_1 + 0x5e0) & 0x80) == 0) {
                uVar4 = zz_00694c0_((int)param_1);
                if (uVar4 == 0) {
                  param_1[0x2e5] = '\b';
                  iVar3 = zz_0026370_((int)param_1);
                  param_1[0x336] = (char)iVar3;
                  param_1[0x347] = '\0';
                  zz_0024900_((int)param_1,1);
                }
                else {
                  param_1[0x2e6] = '\x01';
                }
              }
              else {
                if (((param_1[0x661] != '\x02') && (param_1[0x7cd] == '\x01')) &&
                   (*(short *)(param_1 + 0x736) <= *(short *)(param_1 + 0x344))) {
                  param_1[0x2e5] = '\b';
                  iVar3 = zz_0026370_((int)param_1);
                  param_1[0x336] = (char)iVar3;
                  param_1[0x347] = '\0';
                }
                iVar3 = zz_00238b4_((int)param_1);
                if (iVar3 != 0) {
                  param_1[0x2e5] = '\b';
                  param_1[0x336] = '\0';
                  param_1[0x347] = '\0';
                  return;
                }
                zz_0024900_((int)param_1,0);
              }
            }
            *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
          }
        }
        else {
          zz_0021148_((int)param_1);
        }
      }
    }
  }
  else {
    zz_002111c_((int)param_1);
  }
  return;
}



// ==== 8001f438  zz_001f438_ ====

void zz_001f438_(char *param_1)

{
  uint uVar1;
  int iVar2;
  bool bVar3;
  double dVar4;
  
  if (param_1[0x38d] == '\x02') {
    zz_0020fd4_((int)param_1);
    param_1[0x30e] = '\0';
    return;
  }
  if (*(float *)(param_1 + 0x318) < *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0)) {
    *(undefined4 *)(param_1 + 0x314) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x318) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x31c) = *(undefined4 *)(param_1 + 0x28);
    *(float *)(param_1 + 0x318) = *(float *)(param_1 + 0x318) + *(float *)(param_1 + 0x6d0);
  }
  if (param_1[0x2e4] == '\x01') {
    uVar1 = zz_00694c0_((int)param_1);
    if ((uVar1 != 0) && (iVar2 = zz_002115c_((int)param_1), iVar2 != 0)) {
      zz_0021148_((int)param_1);
      return;
    }
    iVar2 = zz_00228fc_(param_1);
    if (iVar2 != 0) {
      zz_002111c_((int)param_1);
      return;
    }
    uVar1 = zz_0021db0_(param_1);
    if (uVar1 != 0) {
      zz_00210ec_((int)param_1);
    }
  }
  if (param_1[0x661] == '\x02') {
    dVar4 = FUN_8003d964((double)*(float *)(param_1 + 0x668),(int)param_1,(float *)(param_1 + 0x20))
    ;
    if ((*(float *)(param_1 + 0x24) <= (float)(dVar4 + (double)*(float *)(param_1 + 0x36c))) ||
       (param_1[0x1db] != '\0')) {
      zz_0020fd4_((int)param_1);
      param_1[0x30e] = '\0';
      return;
    }
  }
  else if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    param_1[0x2e5] = '\0';
    if ((param_1[0x30e] != '\0') &&
       (*(float *)(param_1 + 0x24) <= FLOAT_80436e58 + *(float *)(param_1 + 0x310))) {
      FUN_80024360((int)param_1);
    }
    param_1[0x30e] = '\0';
    return;
  }
  if (param_1[0x336] != '\0') {
    zz_0020c2c_((int)param_1);
  }
  iVar2 = zz_00238b4_((int)param_1);
  if (iVar2 == 0) {
    if (param_1[0x661] != '\x02') {
      bVar3 = zz_002512c_((double)FLOAT_80436e30,(int)param_1);
      if (bVar3) {
        zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,(int)param_1[0x337] ^ 0x80000000) -
                                   DOUBLE_80436e18),
                    (double)(float)((double)CONCAT44(0x43300000,(int)param_1[0x338] ^ 0x80000000) -
                                   DOUBLE_80436e18),(int)param_1,1);
      }
      else {
        zz_0024900_((int)param_1,1);
      }
    }
  }
  else if ((param_1[0x30e] == '\0') && ((param_1[0x5e4] == '\x06' || (param_1[0x5e4] == '\x11')))) {
    param_1[0x2e5] = '\x04';
  }
  return;
}



// ==== 8001f69c  zz_001f69c_ ====

void zz_001f69c_(int param_1)

{
  char cVar1;
  bool bVar2;
  int iVar3;
  short sVar5;
  uint uVar4;
  double dVar6;
  
  if (((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) &&
     (dVar6 = FUN_8003db9c((float *)(param_1 + 0x20)),
     *(float *)(param_1 + 0x24) < (float)((double)FLOAT_80436e40 + dVar6))) {
    *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
  }
  bVar2 = true;
  if ((*(short *)(param_1 + 1000) == 0xc04) || (*(char *)(param_1 + 0x661) == '\x04')) {
    bVar2 = false;
    if (*(int *)(param_1 + 0x300) == 0) {
      if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
        zz_0020fd4_(param_1);
        return;
      }
      bVar2 = true;
    }
    else {
      iVar3 = zz_0027704_(param_1,(float *)(*(int *)(param_1 + 0x300) + 0x20));
      sVar5 = (short)iVar3;
      if (((-1 < sVar5) && (sVar5 < 0x801)) || ((sVar5 < 1 && (-0x801 < sVar5)))) {
        bVar2 = true;
      }
      FUN_80025f7c(param_1);
    }
  }
  cVar1 = *(char *)(param_1 + 0x2e5);
  if (cVar1 == '\x03') {
    if (*(short *)(param_1 + 0x34c) < 1) {
      *(undefined1 *)(param_1 + 0x2e5) = 5;
    }
    else {
      *(short *)(param_1 + 0x34c) = *(short *)(param_1 + 0x34c) + -1;
      if ((*(uint *)(param_1 + 0x5b8) & (int)*(short *)(param_1 + 0x33e)) == 0) {
        *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x33e);
      }
      if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
        *(undefined1 *)(param_1 + 0x2e5) = 2;
      }
      else if (*(char *)(*(int *)(param_1 + 0x4b0) + (int)*(char *)(param_1 + 0x584) + 0xb8) == '\0'
              ) {
        *(undefined1 *)(param_1 + 0x2e5) = 5;
      }
      else {
        *(undefined1 *)(param_1 + 0x2e5) = 4;
        uVar4 = zz_00055fc_();
        *(ushort *)(param_1 + 0x350) = ((ushort)uVar4 & 0x1f) + 0x3c;
        if (*(short *)(param_1 + 1000) == 0xc04) {
          *(undefined2 *)(param_1 + 0x350) = 300;
        }
        if (*(short *)(param_1 + 1000) == 0x904) {
          *(undefined2 *)(param_1 + 0x350) = 600;
        }
      }
    }
  }
  else if (cVar1 < '\x03') {
    if (cVar1 == '\x01') {
      if ((bVar2) || (*(short *)(param_1 + 0x34c) < 1)) {
        *(undefined1 *)(param_1 + 0x2e5) = 2;
        *(undefined2 *)(param_1 + 0x34c) = 300;
      }
      else {
        *(short *)(param_1 + 0x34c) = *(short *)(param_1 + 0x34c) + -1;
      }
    }
    else if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        if ((*(short *)(param_1 + 1000) == 0xc04) || (*(char *)(param_1 + 0x661) == '\x04')) {
          *(undefined2 *)(param_1 + 0x34c) = 300;
          *(undefined1 *)(param_1 + 0x2e5) = 1;
        }
        else {
          *(undefined1 *)(param_1 + 0x2e5) = 2;
          *(undefined2 *)(param_1 + 0x34c) = 300;
        }
      }
    }
    else if (*(short *)(param_1 + 0x34c) < 1) {
      *(undefined1 *)(param_1 + 0x2e5) = 5;
    }
    else {
      *(short *)(param_1 + 0x34c) = *(short *)(param_1 + 0x34c) + -1;
      if ((*(uint *)(param_1 + 0x5b8) & (int)*(short *)(param_1 + 0x33e)) == 0) {
        *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x33e);
      }
      if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
        *(undefined1 *)(param_1 + 0x2e5) = 3;
      }
      else if (*(char *)(*(int *)(param_1 + 0x4b0) + (int)*(char *)(param_1 + 0x584) + 0xb8) == '\0'
              ) {
        *(undefined1 *)(param_1 + 0x2e5) = 5;
      }
      else {
        *(undefined1 *)(param_1 + 0x2e5) = 4;
        uVar4 = zz_00055fc_();
        *(ushort *)(param_1 + 0x350) = ((ushort)uVar4 & 0x1f) + 0x3c;
        if (*(short *)(param_1 + 1000) == 0xc04) {
          *(undefined2 *)(param_1 + 0x350) = 300;
        }
        if (*(short *)(param_1 + 1000) == 0x904) {
          *(undefined2 *)(param_1 + 0x350) = 600;
        }
      }
    }
  }
  else if (cVar1 == '\x05') {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      iVar3 = zz_002115c_(param_1);
      if (iVar3 != 0) {
        zz_0021134_(param_1);
        return;
      }
    }
    else {
      uVar4 = zz_00694c0_(param_1);
      if ((uVar4 != 0) && (iVar3 = zz_002115c_(param_1), iVar3 != 0)) {
        zz_0021148_(param_1);
        return;
      }
    }
    if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
      zz_0020fd4_(param_1);
    }
  }
  else if (cVar1 < '\x05') {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      iVar3 = zz_002115c_(param_1);
      if (iVar3 != 0) {
        zz_0021134_(param_1);
        return;
      }
    }
    else {
      uVar4 = zz_00694c0_(param_1);
      if ((uVar4 != 0) && (iVar3 = zz_002115c_(param_1), iVar3 != 0)) {
        zz_0021148_(param_1);
        return;
      }
    }
    if (((*(uint *)(param_1 + 0x5e0) & 3) == 0) && (*(char *)(param_1 + 0x661) != '\b')) {
      zz_0020fd4_(param_1);
    }
    else if ((*(char *)(param_1 + 0x30b) == '\x01') &&
            ((*(int *)(param_1 + 0x508) != 0 && (0 < *(short *)(param_1 + 0x350))))) {
      if (*(short *)(param_1 + *(char *)(param_1 + 0x353) * 8 + 0x774) < 1) {
        *(undefined1 *)(param_1 + 0x2e5) = 5;
      }
      else {
        *(short *)(param_1 + 0x350) = *(short *)(param_1 + 0x350) + -1;
        if ((*(uint *)(param_1 + 0x5b8) & (int)*(short *)(param_1 + 0x33e)) == 0) {
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x33e)
          ;
        }
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x2e5) = 5;
    }
  }
  return;
}



// ==== 8001fb28  zz_001fb28_ ====

void zz_001fb28_(char *param_1)

{
  char cVar1;
  uint uVar2;
  char *pcVar3;
  
  if ((*(short *)(param_1 + param_1[0x353] * 8 + 0x774) < 1) &&
     (*(short *)(param_1 + param_1[0x353] * 8 + 0x78e) != 0)) {
    zz_0020fd4_((int)param_1);
  }
  else {
    cVar1 = param_1[0x2e5];
    if (cVar1 == '\x01') {
      if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
        if ((*(uint *)(param_1 + 0x5b8) & 0x100) == 0) {
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
        }
      }
      else {
        param_1[0x2e5] = '\n';
        param_1[0x2e6] = '\x03';
        param_1[0x2e7] = '\0';
      }
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      param_1[0x34c] = '\0';
      param_1[0x34d] = '\0';
      uVar2 = *(uint *)(param_1 + 0x5e0);
      if ((uVar2 & 0x80) == 0) {
        if ((uVar2 & 0x40) == 0) {
          if ((uVar2 & 0x20) == 0) {
            if ((uVar2 & 0x200) == 0) {
              cVar1 = param_1[0x352];
              if (((cVar1 == '\x01') || (cVar1 == '\b')) || (cVar1 == '\t')) {
                param_1[0x2e5] = '\n';
                param_1[0x2e6] = '\x01';
                param_1[0x2e7] = '\0';
              }
              else {
                pcVar3 = FUN_80025944(param_1);
                if (pcVar3 == (char *)0x0) {
                  param_1[0x2e5] = '\n';
                  param_1[0x2e6] = '\x01';
                  param_1[0x2e7] = '\0';
                }
                else if (((*(uint *)(pcVar3 + 0x5e0) & 0x40) != 0) ||
                        (*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x668) <=
                         *(float *)(pcVar3 + 0x24))) {
                  param_1[0x2e5] = '\x01';
                  if ((*(uint *)(param_1 + 0x5b8) & 0x100) == 0) {
                    *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
                  }
                }
                else {
                  uVar2 = zz_00055fc_();
                  if ((&DAT_802cfac4)[uVar2 & 0xf] == '\0') {
                    param_1[0x2e5] = '\n';
                    param_1[0x2e6] = '\x01';
                    param_1[0x2e7] = '\0';
                  }
                  else {
                    param_1[0x2e5] = '\x01';
                    if ((*(uint *)(param_1 + 0x5b8) & 0x100) == 0) {
                      *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
                    }
                  }
                }
              }
            }
            else {
              param_1[0x2e5] = '\n';
              param_1[0x2e6] = '\x04';
              param_1[0x2e7] = '\0';
            }
          }
          else {
            param_1[0x2e5] = '\n';
            param_1[0x2e6] = '\x02';
            param_1[0x2e7] = '\0';
          }
        }
        else {
          param_1[0x2e5] = '\n';
          param_1[0x2e6] = '\x03';
          param_1[0x2e7] = '\0';
        }
      }
      else {
        param_1[0x2e5] = '\n';
        param_1[0x2e6] = '\x05';
        param_1[0x2e7] = '\0';
      }
    }
    cVar1 = param_1[0x2e6];
    if (cVar1 == '\x03') {
      zz_001fef0_(param_1);
    }
    else if (cVar1 < '\x03') {
      if (cVar1 == '\x01') {
        zz_001fdf4_((int)param_1);
      }
      else if ('\0' < cVar1) {
        zz_001fdf4_((int)param_1);
      }
    }
    else if (cVar1 == '\x05') {
      zz_001fef0_(param_1);
    }
    else if (cVar1 < '\x05') {
      zz_001fdf4_((int)param_1);
    }
  }
  return;
}



// ==== 8001fdf4  zz_001fdf4_ ====

void zz_001fdf4_(int param_1)

{
  char cVar1;
  int iVar2;
  
  cVar1 = *(char *)(param_1 + 0x2e7);
  if (cVar1 == '\x01') {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
      *(undefined1 *)(param_1 + 0x2e6) = 3;
    }
    if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
      zz_00200e4_(param_1);
    }
    else {
      iVar2 = zz_0020174_(param_1);
      if (iVar2 != 0) {
        *(undefined2 *)(param_1 + 0x34c) = 0x14;
      }
      if (*(short *)(param_1 + 0x34c) != 0) {
        *(short *)(param_1 + 0x34c) = *(short *)(param_1 + 0x34c) + -1;
        if ((*(uint *)(param_1 + 0x5b8) & (int)*(short *)(param_1 + 0x340)) == 0) {
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x340)
          ;
        }
      }
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
      if ((*(uint *)(param_1 + 0x5b8) & (int)*(short *)(param_1 + 0x340)) == 0) {
        *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x340);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x2e7) = 1;
      *(undefined2 *)(param_1 + 0x34c) = 0;
    }
  }
  return;
}



// ==== 8001fef0  zz_001fef0_ ====

void zz_001fef0_(char *param_1)

{
  char cVar1;
  int iVar2;
  char *pcVar3;
  double dVar4;
  double dVar5;
  
  *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
  cVar1 = param_1[0x2e7];
  if (cVar1 == '\x01') {
    if ((*(uint *)(param_1 + 0x5e0) & 0x200) == 0) {
      if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
        dVar4 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),(int)param_1,
                             (float *)(param_1 + 0x20));
        if (*(float *)(param_1 + 0x668) * FLOAT_80436e5c <
            (float)((double)*(float *)(param_1 + 0x24) - dVar4)) {
          zz_0020fd4_((int)param_1);
        }
        else {
          param_1[0x2e7] = '\x02';
        }
      }
      else {
        iVar2 = zz_0020174_((int)param_1);
        if (iVar2 != 0) {
          param_1[0x34c] = '\0';
          param_1[0x34d] = '\x14';
        }
        if (*(short *)(param_1 + 0x34c) != 0) {
          *(short *)(param_1 + 0x34c) = *(short *)(param_1 + 0x34c) + -1;
          if ((*(uint *)(param_1 + 0x5b8) & (int)*(short *)(param_1 + 0x340)) == 0) {
            *(uint *)(param_1 + 0x5b4) =
                 *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x340);
          }
        }
      }
    }
    else {
      param_1[0x2e7] = '\x02';
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
        if ((*(uint *)(param_1 + 0x5b8) & (int)*(short *)(param_1 + 0x340)) == 0) {
          *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | (int)*(short *)(param_1 + 0x340)
          ;
        }
      }
      else {
        param_1[0x2e7] = '\x01';
        param_1[0x34c] = '\0';
        param_1[0x34d] = '\0';
      }
    }
  }
  else if (cVar1 < '\x03') {
    pcVar3 = FUN_80025944(param_1);
    if (pcVar3 == (char *)0x0) {
      zz_0020fd4_((int)param_1);
    }
    else {
      dVar4 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(pcVar3 + 0x20));
      if ((double)FLOAT_80436dfc < dVar4) {
        dVar5 = 1.0 / SQRT(dVar4);
        dVar5 = DOUBLE_80436e00 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436e08);
        dVar5 = DOUBLE_80436e00 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_80436e08);
        dVar4 = (double)(float)(dVar4 * DOUBLE_80436e00 * dVar5 *
                                        -(dVar4 * dVar5 * dVar5 - DOUBLE_80436e08));
      }
      if ((double)FLOAT_80436e20 < dVar4) {
        zz_0020fd4_((int)param_1);
      }
      else {
        param_1[0x2e6] = '\x04';
        param_1[0x2e7] = '\0';
      }
    }
  }
  return;
}



// ==== 800200e4  zz_00200e4_ ====

void zz_00200e4_(int param_1)

{
  uint uVar1;
  
  uVar1 = zz_00055fc_();
  if ((uVar1 & 1) == 0) {
    uVar1 = zz_00055fc_();
    if ((uVar1 & 1) == 0) {
      *(undefined1 *)(param_1 + 0x32d) = 0;
      uVar1 = zz_00055fc_();
      if ((uVar1 & 1) == 0) {
        *(undefined1 *)(param_1 + 0x32c) = 0x35;
      }
      else {
        *(undefined1 *)(param_1 + 0x32c) = 0xcb;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x32c) = 0;
      *(undefined1 *)(param_1 + 0x32d) = 0xcb;
    }
    zz_0021134_(param_1);
  }
  else {
    zz_0020fd4_(param_1);
  }
  return;
}



// ==== 80020174  zz_0020174_ ====

undefined4 zz_0020174_(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    if (*(short *)(param_1 + 1000) == 6) {
      return 1;
    }
  }
  else {
    iVar1 = *(int *)(param_1 + 0x290);
    if (*(char *)(param_1 + 0x88) != *(char *)(iVar1 + 0x88)) {
      if (0 < *(short *)(iVar1 + 0x1c6)) {
        return 1;
      }
      iVar1 = *(int *)(iVar1 + 0x90);
      if (iVar1 != 0) {
        if ((*(char *)(iVar1 + 0x83) == '\0') && ((*(byte *)(iVar1 + 0x1da) & 2) != 0)) {
          return 1;
        }
      }
    }
  }
  return 0;
}



// ==== 800201f8  zz_00201f8_ ====

void zz_00201f8_(int param_1)

{
  char cVar1;
  double dVar2;
  uint uVar3;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    if (*(char *)(*(int *)(param_1 + 0x4f0) + 0x19) == -1) {
      zz_0020fd4_(param_1);
    }
    else {
      cVar1 = *(char *)(param_1 + 0x2e5);
      if (cVar1 == '\x01') {
        zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(char *)(param_1 + 0x32c) ^ 0x80000000) -
                                   DOUBLE_80436e18),
                    (double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(char *)(param_1 + 0x32d) ^ 0x80000000) -
                                   DOUBLE_80436e18),param_1,0);
        if ((*(uint *)(param_1 + 0x5e0) & 0x20) == 0) {
          *(undefined1 *)(param_1 + 0x2e5) = 0;
        }
        else {
          *(undefined1 *)(param_1 + 0x2e5) = 2;
          uVar3 = zz_00055fc_();
          *(ushort *)(param_1 + 0x34c) = ((ushort)uVar3 & 0x3f) + 0x3c;
        }
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          if ((*(uint *)(param_1 + 0x5e0) & 0x20) == 0) {
            *(undefined1 *)(param_1 + 0x2e5) = 1;
          }
          else {
            *(undefined1 *)(param_1 + 0x2e5) = 2;
            uVar3 = zz_00055fc_();
            dVar2 = DOUBLE_80436e18;
            *(ushort *)(param_1 + 0x34c) = ((ushort)uVar3 & 0x3f) + 0x3c;
            zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,
                                                         (int)*(char *)(param_1 + 0x32c) ^
                                                         0x80000000) - dVar2),
                        (double)(float)((double)CONCAT44(0x43300000,
                                                         (int)*(char *)(param_1 + 0x32d) ^
                                                         0x80000000) - dVar2),param_1,0);
          }
        }
      }
      else if (cVar1 < '\x03') {
        zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(char *)(param_1 + 0x32c) ^ 0x80000000) -
                                   DOUBLE_80436e18),
                    (double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(char *)(param_1 + 0x32d) ^ 0x80000000) -
                                   DOUBLE_80436e18),param_1,0);
        if ((*(uint *)(param_1 + 0x5e0) & 0x20) == 0) {
          zz_0020fd4_(param_1);
        }
        else if (*(short *)(param_1 + 0x34c) < 1) {
          zz_0020fd4_(param_1);
        }
        else {
          *(short *)(param_1 + 0x34c) = *(short *)(param_1 + 0x34c) + -1;
        }
      }
    }
  }
  else {
    zz_0020fd4_(param_1);
  }
  return;
}



// ==== 800203f4  zz_00203f4_ ====

void zz_00203f4_(int param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_0020fd4_(param_1);
  }
  else {
    iVar3 = *(int *)(param_1 + 0x4f0);
    if ((((*(char *)(iVar3 + 0x1f) == -1) && (*(char *)(iVar3 + 0x2d) == -1)) &&
        (*(char *)(iVar3 + 0x39) == -1)) && (*(char *)(iVar3 + 0x4b) == -1)) {
      zz_0020fd4_(param_1);
    }
    else {
      *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
      uVar2 = *(uint *)(param_1 + 0x5e0);
      if ((uVar2 & 0x40) == 0) {
        zz_0020fd4_(param_1);
      }
      else {
        cVar1 = *(char *)(param_1 + 0x2e5);
        if (cVar1 == '\x01') {
          if (((uVar2 & 0x80) == 0) && ((uVar2 & 0x20) == 0)) {
            *(undefined1 *)(param_1 + 0x2e5) = 0;
            zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,
                                                         (int)*(char *)(param_1 + 0x32c) ^
                                                         0x80000000) - DOUBLE_80436e18),
                        (double)(float)((double)CONCAT44(0x43300000,
                                                         (int)*(char *)(param_1 + 0x32d) ^
                                                         0x80000000) - DOUBLE_80436e18),param_1,0);
          }
          else {
            *(undefined1 *)(param_1 + 0x2e5) = 2;
          }
        }
        else if (cVar1 < '\x01') {
          if (-1 < cVar1) {
            if (((uVar2 & 0x80) == 0) && ((uVar2 & 0x20) == 0)) {
              *(undefined1 *)(param_1 + 0x2e5) = 1;
            }
            else {
              *(undefined1 *)(param_1 + 0x2e5) = 2;
            }
          }
        }
        else if (cVar1 < '\x03') {
          zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,
                                                       (int)*(char *)(param_1 + 0x32c) ^ 0x80000000)
                                     - DOUBLE_80436e18),
                      (double)(float)((double)CONCAT44(0x43300000,
                                                       (int)*(char *)(param_1 + 0x32d) ^ 0x80000000)
                                     - DOUBLE_80436e18),param_1,0);
          if ((((*(uint *)(param_1 + 0x5e0) & 0x80) == 0) ||
              ((*(uint *)(param_1 + 0x5e0) & 0x20) != 0)) ||
             ((*(char *)(param_1 + 0x58d) == '\0' ||
              ((((*(float *)(param_1 + 0x20) < *(float *)(DAT_8043625c + 0x3c) ||
                 (*(float *)(DAT_8043625c + 0x38) < *(float *)(param_1 + 0x20))) ||
                (*(float *)(param_1 + 0x28) < *(float *)(DAT_8043625c + 0x44))) ||
               (*(float *)(DAT_8043625c + 0x40) < *(float *)(param_1 + 0x28))))))) {
            if (*(char *)(param_1 + 0x661) == '\x02') {
              *(undefined1 *)(param_1 + 0x336) = 0;
              zz_0020fd4_(param_1);
            }
            else {
              *(undefined1 *)(param_1 + 0x2e4) = 1;
              *(undefined1 *)(param_1 + 0x2e5) = 8;
              *(undefined1 *)(param_1 + 0x2e7) = 0;
              iVar3 = zz_0026370_(param_1);
              *(char *)(param_1 + 0x336) = (char)iVar3;
              *(undefined1 *)(param_1 + 0x347) = 0;
            }
          }
        }
      }
    }
  }
  return;
}



// ==== 8002065c  zz_002065c_ ====

void zz_002065c_(int param_1)

{
  char cVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    if (*(char *)(*(int *)(param_1 + 0x4f0) + 0x19) == -1) {
      zz_0020fd4_(param_1);
    }
  }
  else {
    iVar2 = *(int *)(param_1 + 0x4f0);
    if ((((*(char *)(iVar2 + 0x1f) == -1) && (*(char *)(iVar2 + 0x2d) == -1)) &&
        (*(char *)(iVar2 + 0x39) == -1)) && (*(char *)(iVar2 + 0x4b) == -1)) {
      zz_0020fd4_(param_1);
    }
  }
  cVar1 = *(char *)(param_1 + 0x2e5);
  if (cVar1 == '\x01') {
    *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
    if (*(short *)(param_1 + 0x34c) == 0) {
      zz_0020fd4_(param_1);
    }
    else {
      *(short *)(param_1 + 0x34c) = *(short *)(param_1 + 0x34c) + -1;
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x80) == 0) {
      if ((*(uint *)(param_1 + 0x5b8) & 0x100) == 0) {
        *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
      }
    }
    else {
      *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
      *(undefined2 *)(param_1 + 0x34c) = 0x3c;
      *(undefined1 *)(param_1 + 0x2e5) = 1;
    }
  }
  zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,
                                               (int)*(char *)(param_1 + 0x32c) ^ 0x80000000) -
                             DOUBLE_80436e18),
              (double)(float)((double)CONCAT44(0x43300000,
                                               (int)*(char *)(param_1 + 0x32d) ^ 0x80000000) -
                             DOUBLE_80436e18),param_1,0);
  return;
}



// ==== 800207d4  zz_00207d4_ ====

void zz_00207d4_(int param_1)

{
  char cVar1;
  double dVar2;
  uint uVar3;
  
  cVar1 = *(char *)(param_1 + 0x2e5);
  if (cVar1 == '\x01') {
    zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,
                                                 (int)*(char *)(param_1 + 0x32c) ^ 0x80000000) -
                               DOUBLE_80436e18),
                (double)(float)((double)CONCAT44(0x43300000,
                                                 (int)*(char *)(param_1 + 0x32d) ^ 0x80000000) -
                               DOUBLE_80436e18),param_1,0);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20) == 0) {
      *(undefined1 *)(param_1 + 0x2e5) = 0;
    }
    else {
      *(undefined1 *)(param_1 + 0x2e5) = 2;
      uVar3 = zz_00055fc_();
      *(ushort *)(param_1 + 0x34c) = ((ushort)uVar3 & 0x3f) + 0x3c;
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      if ((*(uint *)(param_1 + 0x5e0) & 0x20) == 0) {
        *(undefined1 *)(param_1 + 0x2e5) = 1;
      }
      else {
        *(undefined1 *)(param_1 + 0x2e5) = 2;
        uVar3 = zz_00055fc_();
        dVar2 = DOUBLE_80436e18;
        *(ushort *)(param_1 + 0x34c) = ((ushort)uVar3 & 0x3f) + 0x3c;
        zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(char *)(param_1 + 0x32c) ^ 0x80000000) -
                                   dVar2),
                    (double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(char *)(param_1 + 0x32d) ^ 0x80000000) -
                                   dVar2),param_1,0);
      }
    }
  }
  else if (cVar1 < '\x03') {
    zz_0024d1c_((double)(float)((double)CONCAT44(0x43300000,
                                                 (int)*(char *)(param_1 + 0x32c) ^ 0x80000000) -
                               DOUBLE_80436e18),
                (double)(float)((double)CONCAT44(0x43300000,
                                                 (int)*(char *)(param_1 + 0x32d) ^ 0x80000000) -
                               DOUBLE_80436e18),param_1,0);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20) == 0) {
      zz_0020fd4_(param_1);
    }
    else if (*(short *)(param_1 + 0x34c) < 1) {
      zz_0020fd4_(param_1);
    }
    else {
      *(short *)(param_1 + 0x34c) = *(short *)(param_1 + 0x34c) + -1;
    }
  }
  return;
}



// ==== 800209a4  FUN_800209a4 ====

/* WARNING: Removing unreachable block (ram,0x80020bec) */
/* WARNING: Removing unreachable block (ram,0x800209b4) */

void FUN_800209a4(int param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  double local_28;
  double local_20;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x1000000) == 0) {
    *(undefined1 *)(param_1 + 0x2e4) = 0;
    *(undefined1 *)(param_1 + 0x2e5) = 0;
    *(undefined2 *)(param_1 + 0x328) = 0;
  }
  else {
    if ((*(uint *)(param_1 + 0x5e0) & 0x2000000) != 0) {
      if ((*(char *)(param_1 + 0x2e6) == '\0') && ((*(uint *)(param_1 + 0x5b8) & 0x100) == 0)) {
        *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
      }
      if ((*(char *)(param_1 + 0x352) == '\b') || (*(char *)(param_1 + 0x352) == '\t')) {
        *(undefined1 *)(param_1 + 0x352) = 0;
      }
    }
    if ((((*(uint *)(param_1 + 0x5e0) & 0x20000000) != 0) &&
        (uVar3 = zz_00055fc_(), (uVar3 & 3) == 0)) && ((*(uint *)(param_1 + 0x5b8) & 0x200) == 0)) {
      *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x200;
    }
    cVar1 = *(char *)(param_1 + 0x2e5);
    if (cVar1 == '\x01') {
      if ((*(uint *)(param_1 + 0x5e0) & 0x4000000) == 0) {
        if (*(short *)(param_1 + 0x34c) == 0) {
          *(undefined1 *)(param_1 + 0x2e5) = 2;
        }
        else {
          *(short *)(param_1 + 0x34c) = *(short *)(param_1 + 0x34c) + -1;
        }
        if ((*(byte *)(param_1 + 0x274) & 1) == 0) {
          if ('\0' < *(char *)(param_1 + 0x346)) {
            *(char *)(param_1 + 0x346) = *(char *)(param_1 + 0x346) + -1;
          }
        }
        else {
          *(char *)(param_1 + 0x346) = *(char *)(param_1 + 0x346) + '\x02';
          if ('\a' < *(char *)(param_1 + 0x346)) {
            *(undefined1 *)(param_1 + 0x346) = 0;
            *(undefined1 *)(param_1 + 0x2e5) = 2;
          }
        }
      }
      local_20 = (double)(CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x337)) ^ 0x80000000);
      local_28 = (double)(CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x338)) ^ 0x80000000);
      zz_0024d1c_((double)(float)(local_20 - DOUBLE_80436e18),
                  (double)(float)(local_28 - DOUBLE_80436e18),param_1,1);
    }
    else if (((cVar1 < '\x01') && (-1 < cVar1)) && ((*(uint *)(param_1 + 0x5e0) & 0x4000000) != 0))
    {
      uVar3 = zz_00055fc_();
      if ((uVar3 & 3) == 0) {
        *(undefined1 *)(param_1 + 0x2e5) = 2;
      }
      else {
        *(undefined1 *)(param_1 + 0x2e5) = 1;
        uVar3 = zz_00055fc_();
        *(ushort *)(param_1 + 0x34c) = ((ushort)uVar3 & 0x3f) + 0xf;
        uVar3 = zz_00055fc_();
        sVar2 = *(short *)(&DAT_802cfb8c + (uVar3 & 7) * 2);
        dVar5 = zz_0045204_(sVar2);
        dVar6 = zz_0045238_(sVar2);
        dVar4 = (double)FLOAT_80436e60;
        *(char *)(param_1 + 0x337) = (char)(int)(dVar5 * dVar4);
        *(char *)(param_1 + 0x338) = (char)(int)(-dVar6 * dVar4);
        *(undefined1 *)(param_1 + 0x346) = 0;
      }
    }
  }
  return;
}



// ==== 80020c0c  zz_0020c0c_ ====

void zz_0020c0c_(int param_1)

{
  if (*(char *)(param_1 + 0x6cb) != '\0') {
    return;
  }
  *(undefined1 *)(param_1 + 0x2e4) = 0;
  *(undefined1 *)(param_1 + 0x2e5) = 0;
  *(undefined2 *)(param_1 + 0x328) = 0;
  return;
}



// ==== 80020c2c  zz_0020c2c_ ====

void zz_0020c2c_(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  double dVar5;
  
  if (*(char *)(param_1 + 0x661) == '\x02') {
    *(undefined1 *)(param_1 + 0x336) = 0;
  }
  else if (*(char *)(param_1 + 0x7cd) == '\x01') {
    if (*(short *)(param_1 + 0x736) < 1) {
      *(undefined1 *)(param_1 + 0x347) = 0;
    }
    if ((*(byte *)(param_1 + 0x274) & 2) != 0) {
      *(undefined1 *)(param_1 + 0x347) = 0;
    }
    cVar1 = *(char *)(param_1 + 0x347);
    if (cVar1 == '\x01') {
      if (*(short *)(param_1 + 0x344) == 0) {
        *(undefined1 *)(param_1 + 0x336) = 0;
      }
      else {
        *(short *)(param_1 + 0x344) = *(short *)(param_1 + 0x344) + -1;
        *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
        dVar5 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20));
        if (*(float *)(param_1 + 0x348) <=
            (float)((double)(*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0)) - dVar5)) {
          *(undefined1 *)(param_1 + 0x347) = 2;
          uVar3 = zz_00055fc_();
          *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(&DAT_802cfbbc + (uVar3 & 7) * 4);
        }
      }
    }
    else if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        dVar5 = zz_003f320_((double)(*(float *)(param_1 + 0x30) + *(float *)(param_1 + 0x6d4)),
                            (float *)(param_1 + 0x20));
        if (dVar5 < (double)(float)((double)FLOAT_80436e24 * (double)*(float *)(param_1 + 0x668) +
                                   (double)*(float *)(param_1 + 0x24))) {
          *(undefined1 *)(param_1 + 0x336) = 0;
        }
        else {
          dVar5 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20)
                              );
          if ((float)((double)(*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0)) - dVar5) <=
              FLOAT_80436e64) {
            *(undefined2 *)(param_1 + 0x344) = 0x3c;
            uVar3 = zz_00055fc_();
            fVar2 = FLOAT_80436dfc;
            *(ushort *)(param_1 + 0x344) = *(short *)(param_1 + 0x344) + ((ushort)uVar3 & 0x3f);
            if (fVar2 <= *(float *)(param_1 + 0x48)) {
              *(undefined1 *)(param_1 + 0x347) = 2;
              uVar3 = zz_00055fc_();
              *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(&DAT_802cfbbc + (uVar3 & 7) * 4);
            }
            else {
              *(undefined1 *)(param_1 + 0x347) = 1;
              uVar3 = zz_00055fc_();
              *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(&DAT_802cfb9c + (uVar3 & 7) * 4);
            }
          }
        }
      }
    }
    else if (cVar1 < '\x03') {
      if (*(short *)(param_1 + 0x344) == 0) {
        *(undefined1 *)(param_1 + 0x336) = 0;
      }
      else {
        *(short *)(param_1 + 0x344) = *(short *)(param_1 + 0x344) + -1;
        dVar5 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20));
        if ((float)((double)(*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0)) - dVar5) <=
            *(float *)(param_1 + 0x348)) {
          *(undefined1 *)(param_1 + 0x347) = 1;
          uVar3 = zz_00055fc_();
          *(undefined4 *)(param_1 + 0x348) = *(undefined4 *)(&DAT_802cfb9c + (uVar3 & 7) * 4);
        }
      }
    }
  }
  else {
    if ((*(byte *)(param_1 + 0x274) & 2) != 0) {
      *(undefined1 *)(param_1 + 0x347) = 0;
    }
    fVar2 = FLOAT_80436dfc;
    cVar1 = *(char *)(param_1 + 0x347);
    if (cVar1 == '\x01') {
      *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
      if (fVar2 < *(float *)(param_1 + 0x48)) {
        *(undefined1 *)(param_1 + 0x347) = 2;
      }
    }
    else if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        dVar5 = zz_003f320_((double)(*(float *)(param_1 + 0x30) + *(float *)(param_1 + 0x6d4)),
                            (float *)(param_1 + 0x20));
        if (dVar5 < (double)(float)((double)FLOAT_80436e24 * (double)*(float *)(param_1 + 0x668) +
                                   (double)*(float *)(param_1 + 0x24))) {
          *(undefined1 *)(param_1 + 0x336) = 0;
        }
        else {
          dVar5 = FUN_8003d6e4((double)*(float *)(param_1 + 0x668),param_1,(float *)(param_1 + 0x20)
                              );
          if ((float)((double)(*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x6d0)) - dVar5) <=
              FLOAT_80436e58) {
            *(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100;
            *(undefined1 *)(param_1 + 0x347) = 1;
          }
        }
      }
    }
    else if ((cVar1 < '\x03') &&
            (*(uint *)(param_1 + 0x5b4) = *(uint *)(param_1 + 0x5b4) | 0x100,
            *(float *)(param_1 + 0x48) < fVar2)) {
      iVar4 = zz_0026370_(param_1);
      if (iVar4 == 0) {
        *(undefined1 *)(param_1 + 0x336) = 0;
      }
      else {
        *(undefined1 *)(param_1 + 0x347) = 0;
      }
    }
  }
  return;
}



// ==== 80020fd4  zz_0020fd4_ ====

void zz_0020fd4_(int param_1)

{
  uint uVar1;
  undefined *puVar2;
  
  *(undefined1 *)(param_1 + 0x2e4) = 0;
  *(undefined1 *)(param_1 + 0x2e5) = 0;
  puVar2 = (&PTR_u_VTRPNLJ_802cb2f0)[*(char *)(param_1 + 0x438)];
  uVar1 = zz_00055fc_();
  *(undefined2 *)(param_1 + 0x328) =
       *(undefined2 *)(puVar2 + ((uVar1 & 7) + *(char *)(param_1 + 0x439) * 8) * 2);
  return;
}



// ==== 8002104c  zz_002104c_ ====

void zz_002104c_(int param_1)

{
  int iVar1;
  
  *(undefined1 *)(param_1 + 0x346) = 0;
  *(undefined1 *)(param_1 + 0x2e4) = 1;
  *(undefined1 *)(param_1 + 0x2e5) = 0;
  *(undefined1 *)(param_1 + 0x2e7) = 0;
  if (((*(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x668) < *(float *)(param_1 + 0x2ec)) &&
      (*(char *)(param_1 + 0x38d) != '\x02')) &&
     (iVar1 = zz_0023b18_(param_1,(float *)(param_1 + 0x20)), iVar1 != 0)) {
    *(undefined1 *)(param_1 + 0x2e5) = 1;
    *(undefined4 *)(param_1 + 0x2f4) = *(undefined4 *)(param_1 + 0x2e8);
    *(undefined4 *)(param_1 + 0x2f8) = *(undefined4 *)(param_1 + 0x2ec);
    *(undefined4 *)(param_1 + 0x2fc) = *(undefined4 *)(param_1 + 0x2f0);
    FUN_800245d0(param_1,(float *)(param_1 + 0x20));
  }
  return;
}



// ==== 800210ec  zz_00210ec_ ====

void zz_00210ec_(int param_1)

{
  *(undefined1 *)(param_1 + 0x2e4) = 2;
  *(undefined1 *)(param_1 + 0x2e7) = 0;
  return;
}



// ==== 80021100  zz_0021100_ ====

void zz_0021100_(int param_1)

{
  *(undefined1 *)(param_1 + 0x2e4) = 3;
  *(undefined1 *)(param_1 + 0x2e5) = 0;
  *(undefined1 *)(param_1 + 0x2e6) = 0;
  *(undefined1 *)(param_1 + 0x2e7) = 0;
  return;
}



// ==== 8002111c  zz_002111c_ ====

void zz_002111c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x2e4) = 4;
  *(undefined1 *)(param_1 + 0x2e5) = 0;
  *(undefined1 *)(param_1 + 0x2e6) = 0;
  return;
}



// ==== 80021134  zz_0021134_ ====

void zz_0021134_(int param_1)

{
  *(undefined1 *)(param_1 + 0x2e4) = 5;
  *(undefined1 *)(param_1 + 0x2e5) = 0;
  return;
}



// ==== 80021148  zz_0021148_ ====

void zz_0021148_(int param_1)

{
  *(undefined1 *)(param_1 + 0x2e4) = 6;
  *(undefined1 *)(param_1 + 0x2e5) = 0;
  return;
}



// ==== 8002115c  zz_002115c_ ====

/* WARNING: Removing unreachable block (ram,0x80021b80) */
/* WARNING: Removing unreachable block (ram,0x80021b78) */
/* WARNING: Removing unreachable block (ram,0x80021174) */
/* WARNING: Removing unreachable block (ram,0x8002116c) */

undefined4 zz_002115c_(int param_1)

{
  char cVar1;
  float fVar2;
  int *piVar3;
  int iVar4;
  ushort uVar5;
  int iVar6;
  uint uVar7;
  char *pcVar8;
  int iVar9;
  short sVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  double dVar15;
  float local_6c;
  float local_68;
  float local_64;
  float local_60;
  float local_5c;
  float local_58;
  
  cVar1 = *(char *)(param_1 + 0x352);
  if ((((cVar1 != '\x01') && (cVar1 != '\b')) && (cVar1 != '\t')) &&
     (((cVar1 != '\x02' && ((*(byte *)(param_1 + 0x339) & 0x10) == 0)) &&
      ((*(uint *)(param_1 + 0x5e0) & 3) == 0)))) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      if (*(char *)(*(int *)(param_1 + 0x4f0) + 0x19) == -1) {
        return 0;
      }
    }
    else {
      iVar9 = *(int *)(param_1 + 0x4f0);
      if (((*(char *)(iVar9 + 0x1f) == -1) && (*(char *)(iVar9 + 0x2d) == -1)) &&
         ((*(char *)(iVar9 + 0x39) == -1 && (*(char *)(iVar9 + 0x4b) == -1)))) {
        return 0;
      }
    }
    if (*(short *)(param_1 + 0x32e) < 1) {
      zz_0021b9c_(param_1);
      if (*(char *)(param_1 + 0x1dc) != '\0') {
        uVar7 = (uint)*(char *)(param_1 + 0x1dc);
        iVar9 = 0;
        iVar11 = 2;
        pcVar8 = DAT_803c4e84;
        do {
          if (((*pcVar8 != '\0') && ((uVar7 & 1 << iVar9) != 0)) &&
             (*(char *)(param_1 + 0x88) != pcVar8[0x88])) {
            *(undefined1 *)(param_1 + 0x32c) = *(undefined1 *)(param_1 + 0x337);
            *(undefined1 *)(param_1 + 0x32d) = *(undefined1 *)(param_1 + 0x338);
            return 1;
          }
          if (((pcVar8[0x1e00] != '\0') && ((uVar7 & 1 << iVar9 + 1) != 0)) &&
             (*(char *)(param_1 + 0x88) != pcVar8[0x1e88])) {
            *(undefined1 *)(param_1 + 0x32c) = *(undefined1 *)(param_1 + 0x337);
            *(undefined1 *)(param_1 + 0x32d) = *(undefined1 *)(param_1 + 0x338);
            return 1;
          }
          if (((pcVar8[0x3c00] != '\0') && ((uVar7 & 1 << iVar9 + 2) != 0)) &&
             (*(char *)(param_1 + 0x88) != pcVar8[0x3c88])) {
            *(undefined1 *)(param_1 + 0x32c) = *(undefined1 *)(param_1 + 0x337);
            *(undefined1 *)(param_1 + 0x32d) = *(undefined1 *)(param_1 + 0x338);
            return 1;
          }
          iVar9 = iVar9 + 3;
          pcVar8 = pcVar8 + 0x5a00;
          iVar11 = iVar11 + -1;
        } while (iVar11 != 0);
      }
      piVar3 = &DAT_803c477c;
      for (iVar9 = 0; iVar9 < (int)(uint)DAT_80436250; iVar9 = iVar9 + 1) {
        iVar11 = *piVar3;
        if ((((*(int *)(iVar11 + 0x24) != param_1) &&
             (*(char *)(param_1 + 0x88) != *(char *)(*(int *)(iVar11 + 0x24) + 0x88))) &&
            (iVar6 = *(int *)(iVar11 + 0x20), iVar6 != param_1)) &&
           ((*(char *)(param_1 + 0x88) != *(char *)(iVar6 + 0x88) &&
            (*(char *)(iVar6 + 0x83) != '\0')))) {
          gnt4_PSVECSubtract_bl((float *)(iVar11 + 100),(float *)(param_1 + 0x20),&local_60);
          dVar13 = (double)(local_60 * local_60 + local_58 * local_58);
          if ((double)FLOAT_80436dfc < dVar13) {
            dVar15 = 1.0 / SQRT(dVar13);
            dVar15 = DOUBLE_80436e00 * dVar15 * -(dVar13 * dVar15 * dVar15 - DOUBLE_80436e08);
            dVar15 = DOUBLE_80436e00 * dVar15 * -(dVar13 * dVar15 * dVar15 - DOUBLE_80436e08);
            dVar13 = (double)(float)(dVar13 * DOUBLE_80436e00 * dVar15 *
                                              -(dVar13 * dVar15 * dVar15 - DOUBLE_80436e08));
          }
          dVar13 = (double)(float)(dVar13 * dVar13 + (double)(local_5c * local_5c));
          if ((double)FLOAT_80436dfc < dVar13) {
            dVar15 = 1.0 / SQRT(dVar13);
            dVar15 = DOUBLE_80436e00 * dVar15 * -(dVar13 * dVar15 * dVar15 - DOUBLE_80436e08);
            dVar15 = DOUBLE_80436e00 * dVar15 * -(dVar13 * dVar15 * dVar15 - DOUBLE_80436e08);
            dVar13 = (double)(float)(dVar13 * DOUBLE_80436e00 * dVar15 *
                                              -(dVar13 * dVar15 * dVar15 - DOUBLE_80436e08));
          }
          gnt4_PSVECSubtract_bl((float *)(iVar11 + 0x70),(float *)(param_1 + 0x2c),&local_6c);
          dVar15 = (double)(local_6c * local_6c + local_64 * local_64);
          if ((double)FLOAT_80436dfc < dVar15) {
            dVar12 = 1.0 / SQRT(dVar15);
            dVar12 = DOUBLE_80436e00 * dVar12 * -(dVar15 * dVar12 * dVar12 - DOUBLE_80436e08);
            dVar12 = DOUBLE_80436e00 * dVar12 * -(dVar15 * dVar12 * dVar12 - DOUBLE_80436e08);
            dVar15 = (double)(float)(dVar15 * DOUBLE_80436e00 * dVar12 *
                                              -(dVar15 * dVar12 * dVar12 - DOUBLE_80436e08));
          }
          dVar15 = (double)(float)(dVar15 * dVar15 + (double)(local_68 * local_68));
          if ((double)FLOAT_80436dfc < dVar15) {
            dVar12 = 1.0 / SQRT(dVar15);
            dVar12 = DOUBLE_80436e00 * dVar12 * -(dVar15 * dVar12 * dVar12 - DOUBLE_80436e08);
            dVar12 = DOUBLE_80436e00 * dVar12 * -(dVar15 * dVar12 * dVar12 - DOUBLE_80436e08);
            dVar15 = (double)(float)(dVar15 * DOUBLE_80436e00 * dVar12 *
                                              -(dVar15 * dVar12 * dVar12 - DOUBLE_80436e08));
          }
          if (dVar13 <= dVar15) {
            dVar15 = gnt4_PSVECSquareDistance_bl((float *)(iVar11 + 100),(float *)(param_1 + 0x20));
            if ((double)FLOAT_80436dfc < dVar15) {
              dVar12 = 1.0 / SQRT(dVar15);
              dVar12 = DOUBLE_80436e00 * dVar12 * -(dVar15 * dVar12 * dVar12 - DOUBLE_80436e08);
              dVar12 = DOUBLE_80436e00 * dVar12 * -(dVar15 * dVar12 * dVar12 - DOUBLE_80436e08);
              dVar15 = (double)(float)(dVar15 * DOUBLE_80436e00 * dVar12 *
                                                -(dVar15 * dVar12 * dVar12 - DOUBLE_80436e08));
            }
            dVar12 = gnt4_PSVECSquareDistance_bl((float *)(iVar11 + 0x70),(float *)(param_1 + 0x2c))
            ;
            if ((double)FLOAT_80436dfc < dVar12) {
              dVar14 = 1.0 / SQRT(dVar12);
              dVar14 = DOUBLE_80436e00 * dVar14 * -(dVar12 * dVar14 * dVar14 - DOUBLE_80436e08);
              dVar14 = DOUBLE_80436e00 * dVar14 * -(dVar12 * dVar14 * dVar14 - DOUBLE_80436e08);
              dVar12 = (double)(float)(dVar12 * DOUBLE_80436e00 * dVar14 *
                                                -(dVar12 * dVar14 * dVar14 - DOUBLE_80436e08));
            }
            if (((double)FLOAT_80436dfc < (double)(float)(dVar12 - dVar15)) &&
               ((float)(dVar13 / (double)(float)(dVar12 - dVar15)) <= FLOAT_80436e68)) {
              iVar6 = FUN_800452a0((double)local_60,(double)local_58);
              iVar4 = FUN_800452a0((double)local_6c,(double)local_64);
              uVar5 = (short)iVar4 - (short)iVar6;
              if ((((short)uVar5 < 0x61) && (-1 < (short)uVar5)) ||
                 ((-0x61 < (short)uVar5 && ((short)uVar5 < 0)))) {
                gnt4_PSVECSubtract_bl((float *)(iVar11 + 0x70),(float *)(param_1 + 0x2c),&local_6c);
                gnt4_PSVECSubtract_bl((float *)(iVar11 + 100),(float *)(param_1 + 0x20),&local_60);
                gnt4_PSVECAdd_bl(&local_6c,&local_60,&local_60);
                iVar9 = FUN_800452a0((double)local_60,(double)local_58);
                sVar10 = (short)iVar9;
                uVar7 = zz_0021c08_(param_1,sVar10);
                if (uVar7 == 2) {
                  sVar10 = sVar10 + -0x4000;
                }
                else {
                  if ((int)uVar7 < 2) {
                    if (uVar7 != 0) {
                      if (-1 < (int)uVar7) {
                        sVar10 = sVar10 + 0x4000;
                      }
                      goto LAB_80021790;
                    }
                  }
                  else if (3 < (int)uVar7) goto LAB_80021790;
                  if ((uVar5 & 0x8000) == 0) {
                    sVar10 = sVar10 + 0x4000;
                  }
                  else {
                    sVar10 = sVar10 + -0x4000;
                  }
                }
LAB_80021790:
                if (*(char *)(param_1 + 0x661) == '\x03') {
                  uVar5 = sVar10 - *(short *)(param_1 + 0x72);
                  if (((uVar5 < 0x3000) || (0x6000 < uVar5)) &&
                     ((uVar5 < 0xa000 || (0xd000 < uVar5)))) {
                    if (uVar5 < 0x8001) {
                      *(undefined1 *)(param_1 + 0x32c) = 0xff;
                      *(char *)(param_1 + 0x32c) = *(char *)(param_1 + 0x32c) * '6';
                    }
                    else {
                      *(undefined1 *)(param_1 + 0x32c) = 1;
                      *(char *)(param_1 + 0x32c) = *(char *)(param_1 + 0x32c) * '6';
                    }
                  }
                  else {
                    *(undefined1 *)(param_1 + 0x32c) = 0;
                  }
                  *(undefined1 *)(param_1 + 0x32d) = 0xff;
                  *(char *)(param_1 + 0x32d) = *(char *)(param_1 + 0x32d) * '6';
                }
                else {
                  sVar10 = sVar10 - *(short *)(param_1 + 0x5b0);
                  dVar13 = zz_0045204_(sVar10);
                  local_60 = (float)dVar13;
                  dVar13 = zz_0045238_(sVar10);
                  fVar2 = (float)-dVar13 * FLOAT_80436e60;
                  *(char *)(param_1 + 0x32c) = (char)(int)(local_60 * FLOAT_80436e60);
                  *(char *)(param_1 + 0x32d) = (char)(int)fVar2;
                }
                return 1;
              }
            }
          }
        }
        piVar3 = piVar3 + 1;
      }
      iVar9 = 0;
      pcVar8 = DAT_803c4e84;
      do {
        if ((((*pcVar8 != '\0') && (*(char *)(param_1 + 0x88) != pcVar8[0x88])) &&
            (param_1 == *(int *)(pcVar8 + 0xcc))) && ((*(uint *)(pcVar8 + 0x5e0) & 3) != 0)) {
          dVar13 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(pcVar8 + 0x20));
          if ((double)FLOAT_80436dfc < dVar13) {
            dVar15 = 1.0 / SQRT(dVar13);
            dVar15 = DOUBLE_80436e00 * dVar15 * -(dVar13 * dVar15 * dVar15 - DOUBLE_80436e08);
            dVar15 = DOUBLE_80436e00 * dVar15 * -(dVar13 * dVar15 * dVar15 - DOUBLE_80436e08);
            dVar13 = (double)(float)(dVar13 * DOUBLE_80436e00 * dVar15 *
                                              -(dVar13 * dVar15 * dVar15 - DOUBLE_80436e08));
          }
          fVar2 = FLOAT_80436e6c;
          if (*(char *)(*(int *)(param_1 + 0x4b0) + *(char *)(param_1 + 0x584) + 0xb8) == '\0') {
            fVar2 = FLOAT_80436e28;
          }
          if (dVar13 <= (double)fVar2) {
            gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(pcVar8 + 0x20),&local_6c);
            iVar9 = FUN_800452a0((double)local_6c,(double)local_64);
            sVar10 = (short)iVar9;
            uVar7 = zz_0021c08_(param_1,sVar10);
            if (uVar7 == 2) {
              sVar10 = sVar10 + -0x4000;
            }
            else {
              if ((int)uVar7 < 2) {
                if (uVar7 != 0) {
                  if (-1 < (int)uVar7) {
                    sVar10 = sVar10 + 0x4000;
                  }
                  goto LAB_80021a2c;
                }
              }
              else if (3 < (int)uVar7) goto LAB_80021a2c;
              uVar7 = zz_00055fc_();
              if ((uVar7 & 1) == 0) {
                sVar10 = sVar10 + 0x4000;
              }
              else {
                sVar10 = sVar10 + -0x4000;
              }
            }
LAB_80021a2c:
            if (*(char *)(param_1 + 0x661) == '\x03') {
              uVar5 = sVar10 - *(short *)(param_1 + 0x72);
              if (((uVar5 < 0x3000) || (0x6000 < uVar5)) && ((uVar5 < 0xa000 || (0xd000 < uVar5))))
              {
                if (uVar5 < 0x8001) {
                  *(undefined1 *)(param_1 + 0x32c) = 0xff;
                  *(char *)(param_1 + 0x32c) = *(char *)(param_1 + 0x32c) * '6';
                }
                else {
                  *(undefined1 *)(param_1 + 0x32c) = 1;
                  *(char *)(param_1 + 0x32c) = *(char *)(param_1 + 0x32c) * '6';
                }
              }
              else {
                *(undefined1 *)(param_1 + 0x32c) = 0;
              }
              *(undefined1 *)(param_1 + 0x32d) = 0xff;
              *(char *)(param_1 + 0x32d) = *(char *)(param_1 + 0x32d) * '6';
            }
            else {
              sVar10 = sVar10 - *(short *)(param_1 + 0x5b0);
              dVar13 = zz_0045204_(sVar10);
              local_60 = (float)dVar13;
              dVar13 = zz_0045238_(sVar10);
              fVar2 = (float)-dVar13 * FLOAT_80436e60;
              *(char *)(param_1 + 0x32c) = (char)(int)(local_60 * FLOAT_80436e60);
              *(char *)(param_1 + 0x32d) = (char)(int)fVar2;
            }
            return 1;
          }
        }
        iVar9 = iVar9 + 1;
        pcVar8 = pcVar8 + 0x1e00;
      } while (iVar9 < 6);
    }
    else {
      *(short *)(param_1 + 0x32e) = *(short *)(param_1 + 0x32e) + -1;
    }
  }
  return 0;
}



// ==== 80021b9c  zz_0021b9c_ ====

void zz_0021b9c_(int param_1)

{
  uint uVar1;
  undefined *puVar2;
  
  puVar2 = (&PTR_DAT_802cfa58)[*(char *)(param_1 + 0x438)];
  uVar1 = zz_00055fc_();
  *(undefined2 *)(param_1 + 0x32e) =
       *(undefined2 *)(puVar2 + ((uVar1 & 7) + *(char *)(param_1 + 0x439) * 8) * 2);
  return;
}



// ==== 80021c08  zz_0021c08_ ====

uint zz_0021c08_(int param_1,short param_2)

{
  int iVar1;
  uint uVar2;
  float local_d8;
  float local_d4;
  float local_d0;
  float afStack_cc [3];
  float afStack_c0 [3];
  float local_b4;
  undefined4 local_b0;
  undefined4 local_ac;
  float afStack_a8 [12];
  float afStack_78 [12];
  float afStack_48 [3];
  float local_3c;
  undefined4 local_2c;
  undefined4 local_1c;
  undefined4 local_18;
  uint uStack_14;
  
  uVar2 = 0;
  local_d8 = FLOAT_80436dfc;
  local_d4 = FLOAT_80436dfc;
  local_d0 = FLOAT_80436e20;
  gnt4_PSMTXIdentity_bl(afStack_48);
  local_b4 = *(float *)(param_1 + 0x910);
  uStack_14 = (int)(short)(param_2 + -0x4000) ^ 0x80000000;
  local_b0 = *(undefined4 *)(param_1 + 0x920);
  local_18 = 0x43300000;
  local_ac = *(undefined4 *)(param_1 + 0x930);
  local_3c = local_b4;
  local_2c = local_b0;
  local_1c = local_ac;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80436e70 *
                              (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80436e18)),
                      afStack_a8,0x79);
  gnt4_PSMTXConcat_bl(afStack_48,afStack_a8,afStack_78);
  gnt4_PSMTXMultVec_bl(afStack_78,&local_d8,afStack_c0);
  iVar1 = zz_003f044_(&local_b4,afStack_c0,afStack_cc);
  if (iVar1 == 0) {
    iVar1 = zz_00247b0_(afStack_c0);
    if (iVar1 != 0) {
      uVar2 = 1;
    }
  }
  else {
    uVar2 = 1;
  }
  local_18 = 0x43300000;
  uStack_14 = (int)(short)(param_2 + 0x4000) ^ 0x80000000;
  gnt4_PSMTXRotRad_bl((double)(FLOAT_80436e70 *
                              (float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_80436e18)),
                      afStack_a8,0x79);
  gnt4_PSMTXConcat_bl(afStack_48,afStack_a8,afStack_78);
  gnt4_PSMTXMultVec_bl(afStack_78,&local_d8,afStack_c0);
  iVar1 = zz_003f044_(&local_b4,afStack_c0,afStack_cc);
  if (iVar1 == 0) {
    iVar1 = zz_00247b0_(afStack_c0);
    if (iVar1 != 0) {
      uVar2 = uVar2 | 2;
    }
  }
  else {
    uVar2 = uVar2 | 2;
  }
  return uVar2;
}



// ==== 80021db0  zz_0021db0_ ====

uint zz_0021db0_(char *param_1)

{
  uint uVar1;
  int iVar2;
  char *pcVar3;
  float afStack_28 [3];
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  if (param_1[0x352] == '\x02') {
    uVar1 = 0;
  }
  else if ((param_1[0x339] & 1U) == 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
      if (*(int *)(param_1 + 0x508) == 0) {
        uVar1 = 0;
      }
      else if (param_1[0x364] == '\0') {
        iVar2 = 0;
        if ((param_1[0x339] & 4U) == 0) {
          if (*(short *)(param_1 + 0x322) < 1) {
            zz_00227b0_((int)param_1);
            if (*(int *)(param_1 + 0x300) != 0) {
              iVar2 = zz_00233ec_(*(int *)(param_1 + 0x300));
            }
          }
          else {
            zz_002288c_((int)param_1);
          }
        }
        if (*(short *)(param_1 + 800) < 1) {
          zz_0022744_((int)param_1);
          iVar2 = 1;
        }
        else {
          zz_002281c_((int)param_1);
        }
        if (iVar2 == 0) {
          uVar1 = 0;
        }
        else {
          pcVar3 = *(char **)(param_1 + 0x300);
          if (param_1[0x352] != '\n') {
            iVar2 = zz_0025cfc_(pcVar3);
            if (iVar2 == 0) {
              return 0;
            }
            iVar2 = zz_0025d74_(param_1,(int)pcVar3);
            if (iVar2 != 0) {
              return 0;
            }
          }
          local_1c = *(float *)(param_1 + 0x20);
          local_18 = *(float *)(param_1 + 0x24);
          local_14 = *(undefined4 *)(param_1 + 0x28);
          if (*(float *)(param_1 + 0x510) <= *(float *)(param_1 + 0x24)) {
            local_18 = local_18 + *(float *)(param_1 + 0x668);
          }
          iVar2 = 0;
          uVar1 = zz_00055fc_();
          if ((uVar1 & 3) != 0) {
            iVar2 = zz_003e978_(&local_1c,(float *)(param_1 + 0x50c),afStack_28);
          }
          if (iVar2 == 0) {
            uVar1 = zz_0021f7c_((int)param_1);
            uVar1 = (-uVar1 | uVar1) >> 0x1f;
          }
          else {
            uVar1 = 0;
          }
        }
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



// ==== 80021f7c  zz_0021f7c_ ====

undefined4 zz_0021f7c_(int param_1)

{
  char cVar1;
  short sVar2;
  float fVar3;
  float fVar4;
  undefined4 uVar5;
  uint uVar6;
  uint uVar7;
  uint *puVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  double dVar12;
  double dVar13;
  float local_30;
  float local_2c;
  undefined4 local_28;
  uint local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x10) == 0) {
      iVar10 = *(int *)(param_1 + 0x4b0);
      local_24 = (uint)*(char *)(iVar10 + 0xca);
      local_20 = (int)*(char *)(iVar10 + 0xcb);
      local_1c = (int)*(char *)(iVar10 + 0xcc);
      local_18 = (int)*(char *)(iVar10 + 0xcd);
      local_14 = (int)*(char *)(iVar10 + 0xce);
      local_10 = (int)*(char *)(iVar10 + 0xcf);
    }
    else {
      iVar10 = *(int *)(param_1 + 0x4b0);
      local_24 = (uint)*(char *)(iVar10 + 0xd0);
      local_20 = (int)*(char *)(iVar10 + 0xd1);
      local_1c = (int)*(char *)(iVar10 + 0xd2);
      local_18 = (int)*(char *)(iVar10 + 0xd3);
      local_14 = (int)*(char *)(iVar10 + 0xd4);
      local_10 = (int)*(char *)(iVar10 + 0xd5);
    }
  }
  else {
    iVar10 = *(int *)(param_1 + 0x4b0);
    local_24 = (uint)*(char *)(iVar10 + 0xd6);
    local_20 = (int)*(char *)(iVar10 + 0xd7);
    local_1c = (int)*(char *)(iVar10 + 0xd8);
    local_18 = (int)*(char *)(iVar10 + 0xd9);
    local_14 = (int)*(char *)(iVar10 + 0xda);
    local_10 = (int)*(char *)(iVar10 + 0xdb);
  }
  if ((*(byte *)(param_1 + 0x7d2) & 8) != 0) {
    local_24 = 0;
    local_20 = 0;
  }
  puVar8 = &local_24;
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0xb8) != '\x01') {
    local_24 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0xb9) != '\x01') {
    local_20 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0xba) != '\x01') {
    local_1c = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0xbb) != '\x01') {
    local_18 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0xbc) != '\x01') {
    local_14 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0xbd) != '\x01') {
    local_10 = 0;
  }
  if ((*(short *)(param_1 + 0x774) < 1) && (*(short *)(param_1 + 0x78e) != 0)) {
    local_24 = 0;
  }
  if ((*(short *)(param_1 + 0x77c) < 1) && (*(short *)(param_1 + 0x796) != 0)) {
    local_20 = 0;
  }
  if ((*(short *)(param_1 + 0x784) < 1) && (*(short *)(param_1 + 0x79e) != 0)) {
    local_1c = 0;
  }
  if (*(char *)(param_1 + 0x352) != '\n') {
    local_30 = *(float *)(param_1 + 0x20);
    local_28 = *(undefined4 *)(param_1 + 0x28);
    local_2c = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x66c);
    dVar12 = gnt4_PSVECSquareDistance_bl(&local_30,(float *)(param_1 + 0x50c));
    if ((double)FLOAT_80436dfc < dVar12) {
      dVar13 = 1.0 / SQRT(dVar12);
      dVar13 = DOUBLE_80436e00 * dVar13 * -(dVar12 * dVar13 * dVar13 - DOUBLE_80436e08);
      dVar13 = DOUBLE_80436e00 * dVar13 * -(dVar12 * dVar13 * dVar13 - DOUBLE_80436e08);
      dVar12 = (double)(float)(dVar12 * DOUBLE_80436e00 * dVar13 *
                                        -(dVar12 * dVar13 * dVar13 - DOUBLE_80436e08));
    }
    iVar9 = 0;
    iVar10 = 0;
    iVar11 = 2;
    do {
      if ((((double)*(float *)(*(int *)(param_1 + 0x4b0) + iVar10 + 0xf0) < dVar12) &&
          (cVar1 = *(char *)(*(int *)(param_1 + 0x4b0) + iVar9 + 0x10e), cVar1 != '\x02')) &&
         (cVar1 != '\x03')) {
        *puVar8 = 0;
      }
      if ((((double)*(float *)(*(int *)(param_1 + 0x4b0) + iVar10 + 0xf4) < dVar12) &&
          (cVar1 = *(char *)(*(int *)(param_1 + 0x4b0) + iVar9 + 0x10f), cVar1 != '\x02')) &&
         (cVar1 != '\x03')) {
        puVar8[1] = 0;
      }
      if ((((double)*(float *)(*(int *)(param_1 + 0x4b0) + iVar10 + 0xf8) < dVar12) &&
          (cVar1 = *(char *)(*(int *)(param_1 + 0x4b0) + iVar9 + 0x110), cVar1 != '\x02')) &&
         (cVar1 != '\x03')) {
        puVar8[2] = 0;
      }
      iVar10 = iVar10 + 0xc;
      puVar8 = puVar8 + 3;
      iVar9 = iVar9 + 3;
      iVar11 = iVar11 + -1;
    } while (iVar11 != 0);
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x108) != *(char *)(param_1 + 0x30a)) {
    local_24 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x109) != *(char *)(param_1 + 0x30a)) {
    local_20 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x10a) != *(char *)(param_1 + 0x30a)) {
    local_1c = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x10b) != *(char *)(param_1 + 0x30a)) {
    local_18 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x10c) != *(char *)(param_1 + 0x30a)) {
    local_14 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x10d) != *(char *)(param_1 + 0x30a)) {
    local_10 = 0;
  }
  if (*(char *)(param_1 + 0x373) != '\0') {
    if (*(short *)(param_1 + 0x370) == 0x200) {
      local_24 = 0;
      local_18 = 0;
    }
    if (*(short *)(param_1 + 0x370) == 0x200) {
      local_20 = 0;
      local_14 = 0;
    }
    if (*(short *)(param_1 + 0x370) == 0x400) {
      local_1c = 0;
      local_10 = 0;
    }
  }
  if (((*(short *)(param_1 + 1000) == 0xc00) || (*(short *)(param_1 + 1000) == 0xc05)) &&
     (uVar5 = zz_006c674_(param_1), (char)uVar5 == '\x02')) {
    local_24 = 0;
  }
  sVar2 = *(short *)(param_1 + 1000);
  if ((((sVar2 == 0x500) || (sVar2 == 0x504)) || ((sVar2 == 0x509 || (sVar2 == 0x50a)))) &&
     ((*(int *)(param_1 + 0x300) != 0 && (local_24 != 0)))) {
    fVar3 = *(float *)(param_1 + 0x514) - *(float *)(param_1 + 0x28);
    fVar4 = *(float *)(param_1 + 0x50c) - *(float *)(param_1 + 0x20);
    dVar12 = (double)(fVar4 * fVar4 + fVar3 * fVar3);
    if ((double)FLOAT_80436dfc < dVar12) {
      dVar13 = 1.0 / SQRT(dVar12);
      dVar13 = DOUBLE_80436e00 * dVar13 * -(dVar12 * dVar13 * dVar13 - DOUBLE_80436e08);
      dVar13 = DOUBLE_80436e00 * dVar13 * -(dVar12 * dVar13 * dVar13 - DOUBLE_80436e08);
      dVar12 = (double)(float)(dVar12 * DOUBLE_80436e00 * dVar13 *
                                        -(dVar12 * dVar13 * dVar13 - DOUBLE_80436e08));
    }
    if (dVar12 <= (double)FLOAT_80436e40) {
      local_24 = 0x20;
      local_20 = 0;
      local_1c = 0;
    }
  }
  iVar10 = local_24 + local_20 + local_1c + local_18 + local_14 + local_10;
  if (0x1f < iVar10) {
    iVar10 = 0x20;
  }
  iVar10 = 0x20 / iVar10;
  local_24 = local_24 * iVar10;
  local_20 = local_20 * iVar10;
  local_1c = local_1c * iVar10;
  local_18 = local_18 * iVar10;
  local_14 = local_14 * iVar10;
  local_10 = local_10 * iVar10;
  uVar6 = zz_00055fc_();
  uVar6 = (uVar6 & 0x1f) + 1;
  if (local_24 < uVar6) {
    if (local_24 + local_20 < uVar6) {
      uVar7 = local_24 + local_20 + local_1c;
      if (uVar7 < uVar6) {
        uVar7 = uVar7 + local_18;
        if (uVar7 < uVar6) {
          uVar7 = uVar7 + local_14;
          if (uVar7 < uVar6) {
            if (uVar7 + local_10 < uVar6) {
              uVar5 = 0;
            }
            else {
              *(undefined2 *)(param_1 + 0x33e) = 0x400;
              *(undefined1 *)(param_1 + 0x30b) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0x113);
              *(undefined1 *)(param_1 + 0x353) = 2;
              uVar5 = zz_002347c_((double)*(float *)(*(int *)(param_1 + 0x4b0) + 0x104),param_1,
                                  *(undefined2 *)(param_1 + 0x33e));
            }
          }
          else {
            *(undefined2 *)(param_1 + 0x33e) = 0x200;
            *(undefined1 *)(param_1 + 0x30b) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0x112);
            *(undefined1 *)(param_1 + 0x353) = 1;
            uVar5 = zz_002347c_((double)*(float *)(*(int *)(param_1 + 0x4b0) + 0x100),param_1,
                                *(undefined2 *)(param_1 + 0x33e));
          }
        }
        else {
          *(undefined2 *)(param_1 + 0x33e) = 0x200;
          *(undefined1 *)(param_1 + 0x30b) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0x111);
          *(undefined1 *)(param_1 + 0x353) = 0;
          uVar5 = zz_002347c_((double)*(float *)(*(int *)(param_1 + 0x4b0) + 0xfc),param_1,
                              *(undefined2 *)(param_1 + 0x33e));
        }
      }
      else {
        *(undefined2 *)(param_1 + 0x33e) = 0x400;
        *(undefined1 *)(param_1 + 0x30b) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0x110);
        *(undefined1 *)(param_1 + 0x353) = 2;
        uVar5 = zz_002347c_((double)*(float *)(*(int *)(param_1 + 0x4b0) + 0xf8),param_1,
                            *(undefined2 *)(param_1 + 0x33e));
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x33e) = 0x200;
      *(undefined1 *)(param_1 + 0x30b) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0x10f);
      *(undefined1 *)(param_1 + 0x353) = 1;
      uVar5 = zz_002347c_((double)*(float *)(*(int *)(param_1 + 0x4b0) + 0xf4),param_1,
                          *(undefined2 *)(param_1 + 0x33e));
    }
  }
  else {
    *(undefined2 *)(param_1 + 0x33e) = 0x200;
    *(undefined1 *)(param_1 + 0x30b) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0x10e);
    *(undefined1 *)(param_1 + 0x353) = 0;
    uVar5 = zz_002347c_((double)*(float *)(*(int *)(param_1 + 0x4b0) + 0xf0),param_1,
                        *(undefined2 *)(param_1 + 0x33e));
  }
  return uVar5;
}



// ==== 80022744  zz_0022744_ ====

void zz_0022744_(int param_1)

{
  uint uVar1;
  undefined *puVar2;
  
  puVar2 = (&PTR_DAT_802cc138)[*(char *)(param_1 + 0x438)];
  uVar1 = zz_00055fc_();
  *(undefined2 *)(param_1 + 800) =
       *(undefined2 *)(puVar2 + ((uVar1 & 7) + *(char *)(param_1 + 0x439) * 8) * 2);
  return;
}



// ==== 800227b0  zz_00227b0_ ====

void zz_00227b0_(int param_1)

{
  uint uVar1;
  undefined *puVar2;
  
  puVar2 = (&PTR_DAT_802ccf80)[*(char *)(param_1 + 0x438)];
  uVar1 = zz_00055fc_();
  *(undefined2 *)(param_1 + 0x322) =
       *(undefined2 *)(puVar2 + ((uVar1 & 7) + *(char *)(param_1 + 0x439) * 8) * 2);
  return;
}



// ==== 8002281c  zz_002281c_ ====

void zz_002281c_(int param_1)

{
  char cVar1;
  
  if ((*(char *)(param_1 + 0x6fc) == '\0') && (cVar1 = zz_008b480_(), cVar1 == '\0')) {
    *(short *)(param_1 + 800) = *(short *)(param_1 + 800) + -1;
  }
  else {
    *(short *)(param_1 + 800) = *(short *)(param_1 + 800) + -2;
  }
  if (*(short *)(param_1 + 800) < 1) {
    *(undefined2 *)(param_1 + 800) = 0;
  }
  return;
}



// ==== 8002288c  zz_002288c_ ====

void zz_002288c_(int param_1)

{
  char cVar1;
  
  if ((*(char *)(param_1 + 0x6fc) == '\0') && (cVar1 = zz_008b480_(), cVar1 == '\0')) {
    *(short *)(param_1 + 0x322) = *(short *)(param_1 + 0x322) + -1;
  }
  else {
    *(short *)(param_1 + 0x322) = *(short *)(param_1 + 0x322) + -2;
  }
  if (*(short *)(param_1 + 0x322) < 1) {
    *(undefined2 *)(param_1 + 0x322) = 0;
  }
  return;
}



// ==== 800228fc  zz_00228fc_ ====

undefined4 zz_00228fc_(char *param_1)

{
  char cVar1;
  uint uVar2;
  int iVar3;
  char *unaff_r31;
  float afStack_38 [3];
  float local_2c;
  float local_28;
  undefined4 local_24;
  float local_20;
  float local_1c;
  undefined4 local_18;
  
  cVar1 = param_1[0x352];
  if (((((cVar1 != '\x01') && (cVar1 != '\b')) && (cVar1 != '\t')) &&
      ((cVar1 != '\x02' && ((param_1[0x339] & 2U) == 0)))) &&
     (((*(uint *)(param_1 + 0x5e0) & 3) == 0 &&
      ((*(int *)(param_1 + 0x508) != 0 && (param_1[0x364] == '\0')))))) {
    iVar3 = 0;
    if ((param_1[0x339] & 8U) == 0) {
      if (*(short *)(param_1 + 0x326) < 1) {
        zz_00232a0_((int)param_1);
        unaff_r31 = FUN_80025944(param_1);
        if (unaff_r31 != (char *)0x0) {
          iVar3 = zz_00233ec_((int)unaff_r31);
        }
      }
      else {
        zz_002337c_((int)param_1);
      }
    }
    if (*(short *)(param_1 + 0x324) < 1) {
      zz_0023234_((int)param_1);
      unaff_r31 = FUN_80025944(param_1);
      iVar3 = 1;
    }
    else {
      zz_002330c_((int)param_1);
    }
    if ((iVar3 != 0) && (unaff_r31 != (char *)0x0)) {
      if ((param_1[0x352] != '\n') || ((param_1[0x30a] == '\x01' || (param_1[0x30a] == '\x02')))) {
        iVar3 = zz_0025cfc_(unaff_r31);
        if (iVar3 == 0) {
          return 0;
        }
        iVar3 = zz_0025d74_(param_1,(int)unaff_r31);
        if (iVar3 != 0) {
          return 0;
        }
        if (unaff_r31[0x5e4] == '\t') {
          return 0;
        }
        if (unaff_r31[0x5e4] == '\n') {
          return 0;
        }
      }
      local_2c = *(float *)(param_1 + 0x20);
      iVar3 = 0;
      local_24 = *(undefined4 *)(param_1 + 0x28);
      local_28 = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x66c);
      local_20 = *(float *)(unaff_r31 + 0x20);
      local_18 = *(undefined4 *)(unaff_r31 + 0x28);
      local_1c = *(float *)(unaff_r31 + 0x24) + *(float *)(unaff_r31 + 0x66c);
      uVar2 = zz_00055fc_();
      if ((uVar2 & 7) != 0) {
        iVar3 = zz_003e978_(&local_2c,&local_20,afStack_38);
      }
      if (iVar3 == 0) {
        iVar3 = FUN_80022b80((int)param_1,(int)unaff_r31);
        if (iVar3 == 0) {
          return 0;
        }
        *(char **)(param_1 + 0x300) = unaff_r31;
        param_1[0x30f] = '\0';
        FUN_80025a84((int)param_1);
        return 1;
      }
    }
  }
  return 0;
}



// ==== 80022b80  FUN_80022b80 ====

/* WARNING: Removing unreachable block (ram,0x80023218) */
/* WARNING: Removing unreachable block (ram,0x80023210) */
/* WARNING: Removing unreachable block (ram,0x80023208) */
/* WARNING: Removing unreachable block (ram,0x80022ba0) */
/* WARNING: Removing unreachable block (ram,0x80022b98) */
/* WARNING: Removing unreachable block (ram,0x80022b90) */

undefined4 FUN_80022b80(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 uVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  double dVar14;
  
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x20) == 0) {
      iVar9 = *(int *)(param_1 + 0x4b0);
      iVar10 = (int)*(char *)(iVar9 + 0xdc);
      iVar8 = (int)*(char *)(iVar9 + 0xdd);
      iVar7 = (int)*(char *)(iVar9 + 0xde);
      iVar6 = (int)*(char *)(iVar9 + 0xdf);
      iVar1 = (int)*(char *)(iVar9 + 0xe0);
      iVar9 = (int)*(char *)(iVar9 + 0xe1);
    }
    else {
      iVar9 = *(int *)(param_1 + 0x4b0);
      iVar10 = (int)*(char *)(iVar9 + 0xe2);
      iVar8 = (int)*(char *)(iVar9 + 0xe3);
      iVar7 = (int)*(char *)(iVar9 + 0xe4);
      iVar6 = (int)*(char *)(iVar9 + 0xe5);
      iVar1 = (int)*(char *)(iVar9 + 0xe6);
      iVar9 = (int)*(char *)(iVar9 + 0xe7);
    }
  }
  else {
    iVar9 = *(int *)(param_1 + 0x4b0);
    iVar10 = (int)*(char *)(iVar9 + 0xe8);
    iVar8 = (int)*(char *)(iVar9 + 0xe9);
    iVar7 = (int)*(char *)(iVar9 + 0xea);
    iVar6 = (int)*(char *)(iVar9 + 0xeb);
    iVar1 = (int)*(char *)(iVar9 + 0xec);
    iVar9 = (int)*(char *)(iVar9 + 0xed);
  }
  if ((*(byte *)(param_1 + 0x7d2) & 8) == 0) {
    iVar10 = 0;
    iVar8 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0xb8) != '\0') {
    iVar10 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0xb9) != '\0') {
    iVar8 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0xba) != '\0') {
    iVar7 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0xbb) != '\0') {
    iVar6 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0xbc) != '\0') {
    iVar1 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0xbd) != '\0') {
    iVar9 = 0;
  }
  if ((*(short *)(param_1 + 0x774) < 1) && (*(short *)(param_1 + 0x78e) != 0)) {
    iVar10 = 0;
  }
  if ((*(short *)(param_1 + 0x77c) < 1) && (*(short *)(param_1 + 0x796) != 0)) {
    iVar8 = 0;
  }
  if ((*(short *)(param_1 + 0x784) < 1) && (*(short *)(param_1 + 0x79e) != 0)) {
    iVar7 = 0;
  }
  dVar11 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_2 + 0x20));
  if ((double)FLOAT_80436dfc < dVar11) {
    dVar12 = 1.0 / SQRT(dVar11);
    dVar12 = DOUBLE_80436e00 * dVar12 * -(dVar11 * dVar12 * dVar12 - DOUBLE_80436e08);
    dVar12 = DOUBLE_80436e00 * dVar12 * -(dVar11 * dVar12 * dVar12 - DOUBLE_80436e08);
    dVar11 = (double)(float)(dVar11 * DOUBLE_80436e00 * dVar12 *
                                      -(dVar11 * dVar12 * dVar12 - DOUBLE_80436e08));
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x80) == 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      dVar14 = (double)*(float *)(param_1 + 0x82c);
      dVar13 = (double)*(float *)(param_1 + 0x838);
      dVar12 = (double)*(float *)(param_1 + 0x844);
    }
    else {
      dVar14 = (double)*(float *)(param_1 + 0x830);
      dVar13 = (double)*(float *)(param_1 + 0x83c);
      dVar12 = (double)*(float *)(param_1 + 0x848);
    }
  }
  else {
    dVar14 = (double)*(float *)(param_1 + 0x834);
    dVar13 = (double)*(float *)(param_1 + 0x840);
    dVar12 = (double)*(float *)(param_1 + 0x84c);
  }
  if ((double)(float)(dVar14 * (double)*(float *)(param_1 + 0xb4)) < dVar11) {
    if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x10e) != '\x02') {
      iVar10 = 0;
    }
    if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x111) != '\x02') {
      iVar6 = 0;
    }
  }
  if ((double)(float)(dVar13 * (double)*(float *)(param_1 + 0xb4)) < dVar11) {
    if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x10f) != '\x02') {
      iVar8 = 0;
    }
    if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x112) != '\x02') {
      iVar1 = 0;
    }
  }
  if ((double)(float)(dVar12 * (double)*(float *)(param_1 + 0xb4)) < dVar11) {
    if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x110) != '\x02') {
      iVar7 = 0;
    }
    if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x113) != '\x02') {
      iVar9 = 0;
    }
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x108) != *(char *)(param_1 + 0x30a)) {
    iVar10 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x109) != *(char *)(param_1 + 0x30a)) {
    iVar8 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x10a) != *(char *)(param_1 + 0x30a)) {
    iVar7 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x10b) != *(char *)(param_1 + 0x30a)) {
    iVar6 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x10c) != *(char *)(param_1 + 0x30a)) {
    iVar1 = 0;
  }
  if (*(char *)(*(int *)(param_1 + 0x4b0) + 0x10d) != *(char *)(param_1 + 0x30a)) {
    iVar9 = 0;
  }
  if ((*(short *)(param_1 + 0x774) < 1) && (*(short *)(param_1 + 0x78e) != 0)) {
    iVar10 = 0;
  }
  if ((*(short *)(param_1 + 0x77c) < 1) && (*(short *)(param_1 + 0x796) != 0)) {
    iVar8 = 0;
  }
  if ((*(short *)(param_1 + 0x784) < 1) && (*(short *)(param_1 + 0x79e) != 0)) {
    iVar7 = 0;
  }
  if (*(char *)(param_1 + 0x373) != '\0') {
    if (*(short *)(param_1 + 0x370) == 0x200) {
      iVar10 = 0;
      iVar6 = 0;
    }
    if (*(short *)(param_1 + 0x370) == 0x200) {
      iVar8 = 0;
      iVar1 = 0;
    }
    if (*(short *)(param_1 + 0x370) == 0x400) {
      iVar7 = 0;
      iVar9 = 0;
    }
  }
  iVar2 = iVar10 + iVar8 + iVar7 + iVar6 + iVar1 + iVar9;
  if (0x1f < iVar2) {
    iVar2 = 0x20;
  }
  iVar2 = 0x20 / iVar2;
  uVar3 = zz_00055fc_();
  uVar3 = (uVar3 & 0x1f) + 1;
  if ((uint)(iVar10 * iVar2) < uVar3) {
    uVar5 = iVar10 * iVar2 + iVar8 * iVar2;
    if (uVar5 < uVar3) {
      uVar5 = uVar5 + iVar7 * iVar2;
      if (uVar5 < uVar3) {
        uVar5 = uVar5 + iVar6 * iVar2;
        if (uVar5 < uVar3) {
          uVar5 = uVar5 + iVar1 * iVar2;
          if (uVar5 < uVar3) {
            if (uVar5 + iVar9 * iVar2 < uVar3) {
              uVar4 = 0;
            }
            else {
              *(undefined2 *)(param_1 + 0x340) = 0x400;
              *(undefined1 *)(param_1 + 0x30b) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0x113);
              *(undefined1 *)(param_1 + 0x353) = 2;
              uVar4 = zz_002347c_(dVar12,param_1,*(undefined2 *)(param_1 + 0x340));
            }
          }
          else {
            *(undefined2 *)(param_1 + 0x340) = 0x200;
            *(undefined1 *)(param_1 + 0x30b) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0x112);
            *(undefined1 *)(param_1 + 0x353) = 1;
            uVar4 = zz_002347c_(dVar13,param_1,*(undefined2 *)(param_1 + 0x340));
          }
        }
        else {
          *(undefined2 *)(param_1 + 0x340) = 0x200;
          *(undefined1 *)(param_1 + 0x30b) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0x111);
          *(undefined1 *)(param_1 + 0x353) = 0;
          uVar4 = zz_002347c_(dVar14,param_1,*(undefined2 *)(param_1 + 0x340));
        }
      }
      else {
        *(undefined2 *)(param_1 + 0x340) = 0x400;
        *(undefined1 *)(param_1 + 0x30b) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0x110);
        *(undefined1 *)(param_1 + 0x353) = 2;
        uVar4 = zz_002347c_(dVar12,param_1,*(undefined2 *)(param_1 + 0x340));
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x340) = 0x200;
      *(undefined1 *)(param_1 + 0x30b) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0x10f);
      *(undefined1 *)(param_1 + 0x353) = 1;
      uVar4 = zz_002347c_(dVar13,param_1,*(undefined2 *)(param_1 + 0x340));
    }
  }
  else {
    *(undefined2 *)(param_1 + 0x340) = 0x200;
    *(undefined1 *)(param_1 + 0x30b) = *(undefined1 *)(*(int *)(param_1 + 0x4b0) + 0x10e);
    *(undefined1 *)(param_1 + 0x353) = 0;
    uVar4 = zz_002347c_(dVar14,param_1,*(undefined2 *)(param_1 + 0x340));
  }
  return uVar4;
}



