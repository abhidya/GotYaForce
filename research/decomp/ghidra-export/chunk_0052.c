// ==== 801ada24  zz_01ada24_ ====

void zz_01ada24_(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  undefined4 uVar3;
  short sVar4;
  
  if (*(int *)(param_1 + 0x188) != 0) {
    iVar2 = ((int)*(char *)(param_1 + 0x11) + *(char *)(param_1 + 0x12) * 5) * 4;
    sVar4 = *(short *)(&DAT_8037bf1c + iVar2);
    uVar1 = *(undefined2 *)(&DAT_8037bf1e + iVar2);
    if ((&DAT_804357ac)[*(char *)(param_1 + 0x11)] == '\0') {
      if (*(char *)(param_1 + 0x13) < 10) {
        sVar4 = sVar4 + (short)(((10 - *(char *)(param_1 + 0x13)) * 10) / 2);
      }
    }
    else {
      iVar2 = (int)*(char *)(param_1 + 0x13);
      if (iVar2 < 10) {
        sVar4 = (short)(((10 - iVar2) * 10) / 2) + sVar4 + 0x120;
      }
      else if (0 < 0x28 - iVar2) {
        iVar2 = (0x28 - iVar2) * 0x60;
        iVar2 = iVar2 / 10 + (iVar2 >> 0x1f);
        sVar4 = sVar4 + ((short)iVar2 - (short)(iVar2 >> 0x1f));
      }
    }
    zz_0096d0c_((double)FLOAT_8043b858);
    zz_0096d14_((double)FLOAT_8043b870);
    uVar3 = zz_00970b4_(sVar4,uVar1,(int)(char)(&DAT_804357b4)[*(char *)(param_1 + 0x11)],'\0',
                        (short)*(undefined4 *)(param_1 + 0x180),*(int *)(param_1 + 0x188));
    *(undefined4 *)(param_1 + 0x18c) = uVar3;
  }
  return;
}



// ==== 801adb74  zz_01adb74_ ====

void zz_01adb74_(int param_1)

{
  short sVar1;
  short sVar2;
  size_t sVar3;
  byte *__s;
  int iVar4;
  int iVar5;
  
  if (*(int *)(param_1 + 0x188) != 0) {
    iVar5 = *(char *)(param_1 + 0x12) * 4;
    iVar4 = *(char *)(param_1 + 0x11) + -5;
    sVar1 = *(short *)(&DAT_8037bf58 + iVar5);
    sVar2 = *(short *)(&DAT_8037bf5a + iVar5);
    if (iVar4 == 0) {
      __s = (byte *)(DAT_80436354 + 0xa4);
    }
    else {
      iVar5 = (int)*(char *)(DAT_80436354 + iVar4 + 0xa08);
      if (iVar5 < 0) {
        iVar5 = 0;
      }
      __s = (&PTR_DAT_8035b294)[(char)(&DAT_8037bf94)[iVar5]];
    }
    sVar3 = strlen((char *)__s);
    iVar5 = 0x10;
    if (iVar4 < 2) {
      iVar5 = 0xf;
    }
    zz_0096d0c_((double)FLOAT_8043b874);
    zz_0096d14_((double)FLOAT_8043b878);
    zz_0097144_(sVar1 + (short)(0x18 - sVar3) * 2,sVar2 + -1,iVar5,__s);
  }
  return;
}



// ==== 801adc78  zz_01adc78_ ====

void zz_01adc78_(void)

{
  int iVar1;
  int iVar2;
  undefined4 local_28;
  int local_24;
  
  iVar2 = 0;
  local_28 = 0x2e;
  do {
    local_24 = iVar2;
    iVar1 = zz_01a761c_(0x15,&local_28,2);
    if (iVar1 != 0) {
      *(code **)(iVar1 + 0xc) = zz_01adcf8_;
      *(code **)(iVar1 + 0x10c) = FUN_801ae1c0;
    }
    iVar2 = iVar2 + 1;
  } while (iVar2 < 0xf);
  return;
}



// ==== 801adcf8  zz_01adcf8_ ====

void zz_01adcf8_(int param_1)

{
  (*(code *)(&PTR_zz_01add34__8037bfe0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801add34  zz_01add34_ ====

void zz_01add34_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 extraout_r4;
  float *pfVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  pfVar2 = (float *)0x1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043b880;
  *(undefined2 *)(param_9 + 0x74) = 0;
  iVar3 = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  iVar4 = param_9;
  do {
    uVar5 = zz_01a7688_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar3,
                        pfVar2,param_12,param_13,param_14,param_15,param_16);
    uVar5 = zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar4 + 0xe0),extraout_r4,pfVar2,param_12,param_13,param_14,
                        param_15,param_16);
    iVar3 = iVar3 + 1;
    iVar4 = iVar4 + 4;
  } while (iVar3 < 2);
  *(undefined1 *)(param_9 + 0x82) = 3;
  iVar4 = DAT_80436354;
  if (*(int *)(DAT_80436354 + 0x128) != 0) {
    if ((int)*(char *)(param_9 + 0x11) == *(int *)(DAT_80436354 + 0x118)) {
      *(undefined1 *)(param_9 + 0x19) = 1;
      *(undefined1 *)(param_9 + 0x1a) = 1;
    }
    else {
      *(undefined1 *)(param_9 + 0x19) = 2;
      *(undefined1 *)(param_9 + 0x1a) = 2;
      *(undefined1 *)(param_9 + 0x82) = 0;
    }
  }
  zz_01ade38_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,iVar4,pfVar2,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801ade38  zz_01ade38_ ====

/* WARNING: Removing unreachable block (ram,0x801adfa4) */
/* WARNING: Removing unreachable block (ram,0x801ade48) */

void zz_01ade38_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  int iVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  uint uVar6;
  double dVar7;
  undefined8 uVar8;
  double dVar9;
  
  zz_01a7668_(param_9,0x3d);
  uVar6 = *(uint *)(param_9 + 0x170) << 0x10;
  iVar1 = (int)uVar6 / 0x3d + ((int)(uVar6 | *(uint *)(param_9 + 0x170) >> 0x10) >> 0x1f);
  dVar7 = zz_0045204_((short)iVar1 - (short)(iVar1 >> 0x1f));
  dVar9 = DOUBLE_8043b888;
  uVar4 = 0;
  iVar5 = 0;
  *(float *)(param_9 + 0x15c) = (float)((double)FLOAT_8043b884 * dVar7);
  uVar6 = (uint)*(ushort *)(DAT_80436354 + *(char *)(param_9 + 0x11) * 2 + 0x154);
  *(undefined1 *)(param_9 + 0x13) = 0;
  iVar1 = param_9;
  do {
    if (uVar6 == 0) break;
    for (; uVar3 = 1 << uVar4, (uVar6 & uVar3) == 0; uVar4 = uVar4 + 1) {
    }
    iVar2 = *(int *)(iVar1 + 0xe0);
    uVar8 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - dVar9),
                        param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(param_9 + 0x154),iVar2,param_11,param_12,param_13,param_14,param_15
                        ,param_16);
    uVar8 = zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                        extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
    zz_0007d40_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,extraout_r4_00,
                param_11,param_12,param_13,param_14,param_15,param_16);
    uVar8 = zz_0008744_((double)(float)((double)CONCAT44(0x43300000,
                                                         *(uint *)(param_9 + 0x170) ^ 0x80000000) -
                                       dVar9),param_2,param_3,param_4,param_5,param_6,param_7,
                        param_8,*(int *)(param_9 + 0x154),iVar2,param_11,param_12,param_13,param_14,
                        param_15,param_16);
    uVar8 = zz_0007c30_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                        extraout_r4_01,param_11,param_12,param_13,param_14,param_15,param_16);
    zz_0007bb4_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                (undefined4 *)(param_9 + 0x58),param_11,param_12,param_13,param_14,param_15,param_16
               );
    iVar2 = 1 << iVar5;
    iVar5 = iVar5 + 1;
    uVar4 = uVar4 + 1;
    uVar6 = uVar6 & ~uVar3;
    *(byte *)(param_9 + 0x13) = *(byte *)(param_9 + 0x13) | (byte)iVar2;
    iVar1 = iVar1 + 4;
  } while (iVar5 < 2);
  (*(code *)(&PTR_zz_01adfc0__8037bff0)[*(char *)(param_9 + 0x19)])(param_9);
  return;
}



// ==== 801adfc0  zz_01adfc0_ ====

void zz_01adfc0_(int param_1)

{
  if (*(int *)(DAT_80436354 + 0x128) != 1) {
    return;
  }
  if ((int)*(char *)(param_1 + 0x11) == *(int *)(DAT_80436354 + 0x118)) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
  }
  else {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x02';
  }
  *(undefined1 *)(param_1 + 0x1a) = 0;
  return;
}



// ==== 801ae00c  zz_01ae00c_ ====

void zz_01ae00c_(int param_1)

{
  if (*(int *)(DAT_80436354 + 0x128) != 3) {
    return;
  }
  *(undefined1 *)(param_1 + 0x19) = 0;
  return;
}



// ==== 801ae028  FUN_801ae028 ====

/* WARNING: Removing unreachable block (ram,0x801ae16c) */
/* WARNING: Removing unreachable block (ram,0x801ae038) */

void FUN_801ae028(int param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  double dVar4;
  
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
    if (*(int *)(DAT_80436354 + 0x128) != 3) {
      return;
    }
    *(undefined1 *)(param_1 + 0x1a) = 3;
    *(undefined2 *)(param_1 + 0x1c) = 0;
    *(undefined2 *)(param_1 + 0x1e) = 0x20;
    *(undefined1 *)(param_1 + 0x82) = 3;
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        *(undefined1 *)(param_1 + 0x1a) = 1;
        *(undefined2 *)(param_1 + 0x1e) = 0x20;
        *(undefined2 *)(param_1 + 0x1c) = 0x20;
      }
      else if (cVar1 < '\0') {
        return;
      }
      sVar2 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar2;
      if (sVar2 < 1) {
        *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
        *(undefined1 *)(param_1 + 0x82) = 0;
      }
      goto LAB_801ae0b0;
    }
    if ('\x03' < cVar1) {
      return;
    }
  }
  sVar2 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar2;
  if (*(short *)(param_1 + 0x1e) <= sVar2) {
    *(undefined1 *)(param_1 + 0x19) = 0;
  }
LAB_801ae0b0:
  iVar3 = 0;
  dVar4 = (double)((float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1c) ^ 0x80000000)
                          - DOUBLE_8043b888) /
                  (float)((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1e) ^ 0x80000000)
                         - DOUBLE_8043b888));
  do {
    zz_0007cac_(dVar4,*(int *)(param_1 + 0xe0));
    iVar3 = iVar3 + 1;
    param_1 = param_1 + 4;
  } while (iVar3 < 2);
  return;
}



// ==== 801ae1a0  FUN_801ae1a0 ====

void FUN_801ae1a0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801ae1c0  FUN_801ae1c0 ====

/* WARNING: Removing unreachable block (ram,0x801ae2e4) */
/* WARNING: Removing unreachable block (ram,0x801ae1d0) */

void FUN_801ae1c0(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  byte bVar1;
  uint uVar2;
  char *pcVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  double dVar7;
  undefined8 uVar8;
  double dVar9;
  double dVar10;
  float afStack_38 [3];
  float local_2c;
  float local_28;
  
  uVar2 = zz_0181ab4_();
  bVar1 = *(byte *)(param_9 + 0x11);
  pcVar3 = (char *)(uint)bVar1;
  if (((1 << (int)(char)bVar1 & uVar2) != 0) &&
     (((char)bVar1 != 0xd || (FLOAT_8043b890 <= *(float *)(*(int *)(DAT_80436354 + 0x1514) + 0x20)))
     )) {
    zz_00057f0_((float *)(*(int *)(DAT_80436354 + (char)bVar1 * 4 + 0x984) + 100),&local_2c);
    iVar5 = 0;
    dVar7 = (double)FLOAT_8043b898;
    local_2c = local_2c - FLOAT_8043b894;
    dVar9 = (double)local_28;
    dVar10 = (double)FLOAT_8043b8a0;
    local_28 = (float)(dVar9 + (double)(float)(dVar7 + (double)*(float *)(param_9 + 0x15c)));
    iVar6 = param_9;
    do {
      if (((int)*(char *)(param_9 + 0x13) & 1 << iVar5) == 0) {
        return;
      }
      iVar4 = *(int *)(iVar6 + 0xe0);
      zz_0007834_(dVar7,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,&local_2c,pcVar3
                  ,param_12,param_13,param_14,param_15,param_16);
      uVar8 = gnt4_PSQUATScale_bl((double)FLOAT_8043b89c,(float *)(param_9 + 0x58),afStack_38);
      zz_0007ae4_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,afStack_38,
                  pcVar3,param_12,param_13,param_14,param_15,param_16);
      dVar7 = (double)zz_00097b4_(iVar4,0x45);
      iVar5 = iVar5 + 1;
      iVar6 = iVar6 + 4;
      local_2c = (float)((double)local_2c + dVar10);
    } while (iVar5 < 2);
  }
  return;
}



// ==== 801ae410  FUN_801ae410 ====

void FUN_801ae410(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0xd06) {
    zz_008ac80_(param_1,0);
    zz_00c74ec_(param_1,0x3b);
    *(float *)(param_1 + 0x1dc0) = FLOAT_8043b8a8;
  }
  else if (*(short *)(param_1 + 1000) == 0xd07) {
    zz_008ac80_(param_1,0);
    *(float *)(param_1 + 0x1dc0) = FLOAT_8043b8ac;
  }
  return;
}



// ==== 801ae47c  FUN_801ae47c ====

void FUN_801ae47c(int param_1)

{
  float fVar1;
  
  if ((((*(short *)(param_1 + 1000) == 0xd07) && (*(char *)(param_1 + 0x18) == '\x01')) &&
      ('\x01' < *(char *)(param_1 + 0x19))) && ((*(uint *)(param_1 + 0x5e0) & 3) == 0)) {
    zz_0066ac0_(param_1,0);
    zz_0066e40_(param_1,1);
    *(float *)(param_1 + 0x44) =
         FLOAT_8043b8b0 * *(float *)(param_1 + 0x44) +
         FLOAT_8043b8b4 * *(float *)(*(int *)(param_1 + 0x4ac) + 0x50);
    fVar1 = *(float *)(param_1 + 0x680);
    if (fVar1 < *(float *)(param_1 + 0x48)) {
      fVar1 = *(float *)(param_1 + 0x48);
    }
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  }
  return;
}



// ==== 801ae530  FUN_801ae530 ====

/* WARNING: Removing unreachable block (ram,0x801ae7a8) */
/* WARNING: Removing unreachable block (ram,0x801ae540) */

void FUN_801ae530(int param_1)

{
  float fVar1;
  short sVar2;
  int iVar3;
  double dVar4;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  float local_3c;
  undefined4 local_38;
  undefined4 local_34;
  undefined4 local_30;
  uint uStack_2c;
  undefined4 local_28;
  uint uStack_24;
  longlong local_20;
  
  fVar1 = FLOAT_8043b8b8;
  if (*(short *)(param_1 + 1000) == 0xd07) {
    if ((*(char *)(param_1 + 0x18) == '\x01') && ('\x01' < *(char *)(param_1 + 0x19))) {
      iVar3 = FUN_800452a0(-(double)*(float *)(param_1 + 0x48),(double)*(float *)(param_1 + 0x44));
      uStack_2c = (int)(short)iVar3 ^ 0x80000000;
      uStack_24 = (int)*(short *)(param_1 + 0x18da) ^ 0x80000000;
      local_30 = 0x43300000;
      local_28 = 0x43300000;
      iVar3 = (int)(FLOAT_8043b8b0 *
                    (float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_8043b8c0) +
                   FLOAT_8043b8b4 *
                   (float)((double)CONCAT44(0x43300000,uStack_2c) - DOUBLE_8043b8c0));
      local_20 = (longlong)iVar3;
      *(short *)(param_1 + 0x18da) = (short)iVar3;
      if (0x3800 < *(short *)(param_1 + 0x18da)) {
        *(undefined2 *)(param_1 + 0x18da) = 0x3800;
      }
    }
    else {
      *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x2c);
      *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x30);
      *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x34);
      *(float *)(param_1 + 0x48) = fVar1;
    }
    if (((*(char *)(param_1 + 0x18) == '\x01') && ('\x01' < *(char *)(param_1 + 0x19))) &&
       ((*(uint *)(param_1 + 0x5e0) & 3) == 0)) {
      zz_00f0104_(param_1,0x14,6);
    }
  }
  sVar2 = *(short *)(param_1 + 1000);
  if ((((sVar2 == 0xd07) || (sVar2 == 0xd06)) &&
      ((*(char *)(param_1 + 0x493) == '\0' &&
       ((*(char *)(param_1 + 0x18) == '\x01' && ('\x01' < *(char *)(param_1 + 0x19))))))) &&
     (*(float *)(param_1 + 0x720) <= FLOAT_8043b8b8)) {
    fVar1 = FLOAT_8043b8bc;
    if (sVar2 == 0xd07) {
      fVar1 = FLOAT_8043b8a8;
    }
    dVar4 = (double)fVar1;
    local_3c = *(float *)(param_1 + 0x90c);
    local_38 = *(undefined4 *)(param_1 + 0x91c);
    local_34 = *(undefined4 *)(param_1 + 0x92c);
    local_48 = *(float *)(param_1 + 0x910);
    local_44 = *(undefined4 *)(param_1 + 0x920);
    local_40 = *(undefined4 *)(param_1 + 0x930);
    gnt4_PSVECNormalize_bl(&local_3c,&local_3c);
    gnt4_PSQUATScale_bl(dVar4,&local_3c,&local_3c);
    gnt4_PSVECAdd_bl(&local_3c,&local_48,&local_3c);
    if ((((*(char *)(param_1 + 0x1d9) != '\0') || (*(char *)(param_1 + 0x1dd) != '\0')) ||
        (iVar3 = zz_00677b0_(param_1), iVar3 != 0)) ||
       (iVar3 = zz_003e978_(&local_3c,(float *)(param_1 + 0x20),&local_48), iVar3 != 0)) {
      *(undefined2 *)(param_1 + 0x1c6) = 1;
      *(undefined1 *)(param_1 + 0x663) = 1;
      *(undefined2 *)(param_1 + 0x272) = 0xff;
      local_48 = *(float *)(param_1 + 0x910);
      local_44 = *(undefined4 *)(param_1 + 0x920);
      local_40 = *(undefined4 *)(param_1 + 0x930);
      if (*(short *)(param_1 + 1000) == 0xd07) {
        zz_0085f28_(param_1,&local_48,0x11);
      }
      else {
        zz_00bdd9c_(param_1,&local_48,0);
      }
    }
  }
  return;
}



// ==== 801ae7cc  FUN_801ae7cc ====

void FUN_801ae7cc(int param_1)

{
  zz_00f036c_(param_1,0xea);
  return;
}



// ==== 801ae7f4  FUN_801ae7f4 ====

void FUN_801ae7f4(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x540) == '\0') {
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_00f036c_(param_1,0xe8);
    zz_00f036c_(param_1,0xe9);
  }
  *(float *)(param_1 + 0x44) =
       *(float *)(param_1 + 0x44) *
       (FLOAT_8043b8c8 * (FLOAT_8043b8cc - *(float *)(param_1 + 0x1dc8)) + FLOAT_8043b8b0);
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  iVar1 = zz_0066ac0_(param_1,0);
  if (iVar1 != 0) {
    FUN_800676d8((double)FLOAT_8043b8d0,param_1,*(short *)(param_1 + 0x5ac));
  }
  FUN_80067524((double)FLOAT_8043b8cc,param_1,*(short *)(param_1 + 0x5ae));
  return;
}



// ==== 801ae8a8  zz_01ae8a8_ ====

void zz_01ae8a8_(void)

{
  DAT_80436224 = (undefined2 *)(DAT_80436238 + 0xab800);
  DAT_80436220 = (char *)(DAT_80436238 + 0xa8800);
  gnt4_memset(DAT_80436224,0,0xabe4);
  gnt4_memset(DAT_80436220,0,0x2190);
  zz_008e610_(DAT_80436220);
  zz_008e600_(DAT_80436224);
  zz_008e620_(&DAT_803bfe20);
  zz_01cada4_(&DAT_803bfe20,DAT_80436224,DAT_80436220);
  return;
}



// ==== 801ae92c  zz_01ae92c_ ====

void zz_01ae92c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar4;
  
  gnt4_memset(&DAT_803d4978,0,0xd8);
  puVar3 = &DAT_803d4978;
  uVar2 = 0xf;
  uVar1 = 0x80;
  DAT_803d4a41 = 1;
  DAT_803d4a38 = 0xf;
  DAT_803d4a45 = 0x80;
  DAT_803d4a3c = 0;
  DAT_803d4a10 = 0;
  uVar4 = zz_0096d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,
                      &DAT_8043b8d8,0,0x80,0xf,&DAT_803d4978,in_r9,in_r10);
  zz_0096d2c_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,&DAT_8043b8dc,1,uVar1,
              uVar2,puVar3,in_r9,in_r10);
  zz_01ae8a8_();
  return;
}



// ==== 801ae9b4  zz_01ae9b4_ ====

void zz_01ae9b4_(void)

{
  zz_01b27dc_(&DAT_803d4978);
  DAT_803d4a1c = 0xffffffff;
  (*(code *)(&PTR_zz_01aea08__80380958)[DAT_803d4978])();
  return;
}



// ==== 801aea08  zz_01aea08_ ====

undefined4 zz_01aea08_(undefined1 *param_1)

{
  int iVar1;
  
  zz_002a5f4_(0,0,0,0xff);
  iVar1 = zz_008e0b8_(0);
  if (iVar1 != -1) {
    *param_1 = 2;
    param_1[3] = 0;
    param_1[2] = 0;
    param_1[1] = 0;
    *(undefined4 *)(param_1 + 0xa4) = 0xffffffff;
  }
  return 0;
}



// ==== 801aea78  zz_01aea78_ ====

undefined4 zz_01aea78_(undefined1 *param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  cVar1 = param_1[1];
  if (cVar1 == '\x01') {
    uVar2 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar2 == 0) {
      return 0;
    }
    param_1[1] = param_1[1] + '\x01';
    param_1[0xd0] = 1;
    param_1[0xd1] = 0;
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') {
        return 0;
      }
      param_1[1] = cVar1 + '\x01';
      param_1[0xcc] = 0xd;
      uVar3 = zz_01b2080_(1,2,param_1 + 0xcc);
      *(undefined4 *)(param_1 + 0xb4) = uVar3;
      *(undefined2 *)(param_1 + 4) = 0xf0;
      return 0;
    }
    if ('\x02' < cVar1) {
      return 0;
    }
  }
  uVar2 = zz_01af0f4_((int)param_1,(int)(char)param_1[0xd0],100,
                      (short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x154) +
                      (short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x14c) * 0x18,4,0x1b,0x1d);
  param_1[0xd0] = (char)uVar2;
  if ((param_1[0xd0] & 0x80) != 0) {
    param_1[0xd0] = param_1[0xd0] & 0x7f;
    if (param_1[0xd0] == '\0') {
      uVar3 = 1;
    }
    else {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
      param_1[0xcc] = 0xff;
    }
  }
  return uVar3;
}



// ==== 801aebb0  zz_01aebb0_ ====

undefined4 zz_01aebb0_(undefined1 *param_1)

{
  char cVar1;
  short sVar2;
  uint uVar3;
  int iVar4;
  undefined4 uVar5;
  char *pcVar6;
  
  uVar5 = 0;
  cVar1 = param_1[1];
  pcVar6 = param_1 + *(int *)(param_1 + 0x98) * 0x48 + 8;
  if (cVar1 == '\x01') {
    uVar3 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar3 == 0) {
      return 0;
    }
    sVar2 = *(short *)(param_1 + 6);
    *(short *)(param_1 + 6) = sVar2 + -1;
    if ((short)(sVar2 + -1) != 0) {
      return 0;
    }
    param_1[1] = param_1[1] + '\x01';
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') {
        return 0;
      }
      param_1[1] = cVar1 + '\x01';
      param_1[0xcc] = 0;
      uVar5 = zz_01b2080_(1,0xff,param_1 + 0xcc);
      *(undefined4 *)(param_1 + 0xb4) = uVar5;
      *(undefined2 *)(param_1 + 6) = 0x1e;
      pcVar6[4] = -1;
      pcVar6[5] = -1;
      pcVar6[6] = -1;
      pcVar6[7] = -1;
      return 0;
    }
    if ('\x02' < cVar1) {
      return 0;
    }
  }
  iVar4 = zz_01af378_((int)param_1,*(int *)(param_1 + 0x98));
  if (iVar4 != 0) {
    param_1[0xcb] = 0;
    cVar1 = *pcVar6;
    if (cVar1 == '\0') {
      *param_1 = 1;
    }
    else if ((((cVar1 == '\0') || (*(int *)(pcVar6 + 0x1c) != 0)) || (*(int *)(pcVar6 + 0x20) != 0))
            || (*(int *)(pcVar6 + 0x28) != 0x2000)) {
      if ((cVar1 == '\0') ||
         (((*(int *)(pcVar6 + 0x1c) == 0 && (*(int *)(pcVar6 + 0x20) == 0)) &&
          (*(int *)(pcVar6 + 0x28) == 0x2000)))) {
        uVar5 = 1;
      }
      else {
        param_1[0xcb] = 2;
        *param_1 = 3;
      }
    }
    else if (*(int *)(pcVar6 + 0x18) == 1) {
      *param_1 = 4;
    }
    else {
      uVar5 = 1;
    }
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
  }
  return uVar5;
}



// ==== 801aed68  zz_01aed68_ ====

undefined4 zz_01aed68_(undefined1 *param_1)

{
  int iVar1;
  
  iVar1 = zz_01b0048_(param_1,0);
  if (iVar1 != 0) {
    if (iVar1 < 0) {
      return 1;
    }
    *param_1 = 2;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
  }
  return 0;
}



// ==== 801aedc8  zz_01aedc8_ ====

int zz_01aedc8_(undefined1 *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  short sVar5;
  short sVar6;
  char cVar7;
  int iVar4;
  
  cVar7 = param_1[1];
  if (cVar7 == '\x03') {
    uVar2 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar2 == 0) {
      return 0;
    }
    sVar5 = *(short *)(param_1 + 4);
    *(short *)(param_1 + 4) = sVar5 + -1;
    if (((0 < (short)(sVar5 + -1)) && (uVar2 = zz_008b908_(0xf), uVar2 == 0)) &&
       (uVar2 = zz_008b810_(0xf), uVar2 == 0)) {
      return 0;
    }
    return 1;
  }
  if ('\x02' < cVar7) {
    if (cVar7 == '\x05') {
      iVar3 = zz_01b0d00_((int)param_1);
      if (iVar3 == 0) {
        return 0;
      }
      if (iVar3 < 1) {
        return iVar3;
      }
      *param_1 = 0;
      param_1[1] = 0;
      return 0;
    }
    if ('\x04' < cVar7) {
      return 0;
    }
    iVar3 = zz_01b0590_((int)param_1);
    if (iVar3 == 0) {
      return 0;
    }
    if (iVar3 < 1) {
      return iVar3;
    }
    *param_1 = 0;
    param_1[1] = 0;
    return 0;
  }
  if (cVar7 != '\x01') {
    if ('\0' < cVar7) goto LAB_801aee7c;
    if (cVar7 < '\0') {
      return 0;
    }
    param_1[1] = cVar7 + '\x01';
    param_1[0xcc] = 2;
    uVar1 = zz_01b2080_(1,0,param_1 + 0xcc);
    *(undefined4 *)(param_1 + 0xb4) = uVar1;
    *(undefined2 *)(param_1 + 6) = 0x1e;
  }
  uVar2 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
  if (uVar2 == 0) {
    return 0;
  }
  sVar5 = *(short *)(param_1 + 6);
  *(short *)(param_1 + 6) = sVar5 + -1;
  if ((short)(sVar5 + -1) != 0) {
    return 0;
  }
  param_1[1] = param_1[1] + '\x01';
  THPSimpleAudioStop();
LAB_801aee7c:
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x98);
  iVar3 = zz_008f1b8_(*(int *)(param_1 + 0x98),0x2f);
  *(int *)(param_1 + 0x9c) = iVar3;
  if (*(int *)(param_1 + 0x9c) == 0) {
    uVar2 = 0;
    sVar5 = zz_008e50c_(0);
    iVar3 = zz_008e5d8_(1);
    if (iVar3 == 0) {
      if ((param_1[0xca] & 2) != 0) {
        uVar2 = 2;
      }
    }
    else {
      sVar6 = zz_008e50c_(1);
      sVar5 = sVar5 + sVar6;
    }
    iVar3 = zz_008e5d8_(2);
    if (iVar3 == 0) {
      if ((param_1[0xca] & 4) != 0) {
        uVar2 = uVar2 | 4;
      }
    }
    else {
      sVar6 = zz_008e50c_(2);
      sVar5 = sVar5 + sVar6;
    }
    iVar3 = zz_008e5d8_(3);
    if (iVar3 == 0) {
      if ((param_1[0xca] & 8) != 0) {
        uVar2 = uVar2 | 8;
      }
    }
    else {
      sVar6 = zz_008e50c_(3);
      sVar5 = sVar5 + sVar6;
    }
    iVar3 = zz_008e5d8_(4);
    if (iVar3 == 0) {
      if ((param_1[0xca] & 0x10) != 0) {
        uVar2 = uVar2 | 0x10;
      }
    }
    else {
      sVar6 = zz_008e50c_(4);
      sVar5 = sVar5 + sVar6;
    }
    iVar3 = zz_008e5d8_(5);
    if (iVar3 == 0) {
      uVar2 = uVar2 | 0x20;
    }
    else {
      sVar6 = zz_008e50c_(5);
      sVar5 = sVar5 + sVar6;
    }
    cVar7 = zz_008e308_();
    iVar3 = zz_008e6a4_((int *)0x0,(int *)0x0);
    iVar4 = zz_008e594_();
    if (((sVar5 == 0) && (uVar2 == 0)) && ((cVar7 == '\f' && ((iVar3 == 0 && (iVar4 == 0)))))) {
      param_1[1] = 3;
      param_1[2] = 0;
      *(undefined4 *)(param_1 + 0xa8) = 1;
      *(undefined2 *)(param_1 + 4) = 0xf0;
      param_1[0xcc] = 5;
      uVar1 = zz_01b2080_(1,0,param_1 + 0xcc);
      *(undefined4 *)(param_1 + 0xb4) = uVar1;
    }
    else {
      param_1[1] = 4;
    }
  }
  else if (*(int *)(param_1 + 0x9c) < 0) {
    param_1[1] = 5;
    param_1[2] = 0;
  }
  return 0;
}



// ==== 801af0f4  zz_01af0f4_ ====

uint zz_01af0f4_(int param_1,uint param_2,undefined2 param_3,short param_4,int param_5,int param_6,
                int param_7)

{
  byte bVar1;
  uint uVar2;
  char cVar4;
  int iVar3;
  int iVar5;
  uint uVar6;
  uint uVar7;
  uint uVar8;
  char *pcVar9;
  uint uVar10;
  uint uVar11;
  int iVar12;
  
  iVar3 = param_5 * 8;
  cVar4 = *(char *)(param_1 + 0xd1);
  bVar1 = (&DAT_8038096c)[iVar3];
  iVar12 = (int)(char)(&DAT_8038096d)[iVar3];
  if (cVar4 == '\x01') {
    cVar4 = *(char *)(param_1 + 0xd2) + -1;
    *(char *)(param_1 + 0xd2) = cVar4;
    if (cVar4 < '\0') {
      *(char *)(param_1 + 0xd1) = *(char *)(param_1 + 0xd1) + '\x01';
      *(undefined1 *)(param_1 + 0xd2) = 0;
    }
    if ((*(byte *)(param_1 + 0xd2) & 4) == 0) {
      param_7 = param_6;
    }
  }
  else if (cVar4 < '\x01') {
    if (-1 < cVar4) {
      *(char *)(param_1 + 0xd3) = (char)param_2;
      if ((*(byte *)(param_1 + 0xcd) & 0x3f) == 0) {
        uVar11 = 1;
        uVar10 = 3;
        uVar7 = 2;
      }
      else {
        uVar11 = 0x77;
        uVar10 = 0x7b;
        uVar7 = 0x7a;
      }
      if ((bVar1 & 2) == 0) {
        uVar6 = *(uint *)(param_1 + 0xc0);
      }
      else {
        uVar6 = 0xf;
      }
      uVar8 = bVar1 >> 2 & 1 ^ 1;
      if ((bVar1 & 1) == 0) {
        uVar2 = zz_008bab0_(uVar6,3,1);
        uVar8 = zz_008ba00_(uVar2,param_2,iVar12 + -1,uVar8);
      }
      else {
        uVar2 = zz_008bab0_(uVar6,3,1);
        uVar8 = zz_008ba58_(uVar2,param_2,iVar12 + -1,uVar8);
      }
      if (param_2 != uVar8) {
        zz_00f0468_(0,uVar11,0);
        *(char *)(param_1 + 0xd3) = (char)uVar8;
      }
      uVar11 = zz_008b908_(uVar6);
      if (uVar11 == 0) {
        uVar10 = zz_008b810_(uVar6);
        if (uVar10 != 0) {
          *(char *)(param_1 + 0xd1) = *(char *)(param_1 + 0xd1) + '\x01';
          *(byte *)(param_1 + 0xd3) = *(byte *)(param_1 + 0xd3) | 0x80;
          zz_00f0468_(0,uVar7,0);
        }
      }
      else {
        *(char *)(param_1 + 0xd1) = *(char *)(param_1 + 0xd1) + '\x01';
        *(byte *)(param_1 + 0xd3) = (&DAT_8038096e)[iVar3] | 0x80;
        zz_00f0468_(0,uVar10,0);
      }
      *(undefined1 *)(param_1 + 0xd2) = 0x3c;
      param_2 = *(byte *)(param_1 + 0xd3) & 0x7f;
    }
  }
  else if (cVar4 < '\x03') {
    param_2 = (uint)*(char *)(param_1 + 0xd3);
  }
  if ((param_2 & 0x80) == 0) {
    pcVar9 = (&PTR_DAT_80380970)[param_5 * 2];
    for (uVar7 = 0; (int)uVar7 < iVar12; uVar7 = uVar7 + 1) {
      iVar3 = param_6;
      if ((param_2 & 0xffffff7f) == uVar7) {
        iVar3 = param_7;
      }
      cVar4 = *pcVar9;
      pcVar9 = pcVar9 + 1;
      iVar5 = (int)cVar4;
      if (iVar5 == -1) {
        iVar5 = (int)(char)(&DAT_804359d4)[*(int *)(param_1 + 0xc4)];
      }
      zz_00970b4_(param_3,param_4,iVar3,'\0',(short)iVar5,-1);
      param_4 = param_4 + 0x18;
    }
  }
  return param_2;
}



// ==== 801af378  zz_01af378_ ====

undefined4 zz_01af378_(int param_1,int param_2)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  ushort uVar5;
  int iVar6;
  undefined8 uVar7;
  
  iVar6 = param_1 + param_2 * 0x48 + 8;
  cVar1 = *(char *)(param_1 + 3);
  if (cVar1 == '\x03') {
    iVar2 = zz_008e87c_(*(int *)(param_1 + 0x98));
    if (iVar2 == 1) {
      return 0;
    }
    *(char *)(param_1 + 3) = *(char *)(param_1 + 3) + '\x01';
    iVar3 = zz_008e0d0_(*(int *)(param_1 + 0x98));
    *(int *)(iVar6 + 4) = iVar3;
    iVar3 = zz_008e0ec_(*(int *)(param_1 + 0x98));
    *(int *)(iVar6 + 8) = iVar3;
    if (iVar2 != 0) {
      return 0;
    }
    zz_008e45c_(*(int *)(param_1 + 0x98),(undefined4 *)(iVar6 + 0x14),(undefined4 *)(iVar6 + 0x10));
    return 0;
  }
  if (cVar1 < '\x03') {
    if (cVar1 != '\x01') {
      if ('\0' < cVar1) {
        iVar2 = zz_008e7b4_(*(int *)(param_1 + 0x98));
        if (iVar2 == 1) {
          return 0;
        }
        *(char *)(param_1 + 3) = *(char *)(param_1 + 3) + '\x01';
        iVar3 = zz_008e0d0_(*(int *)(param_1 + 0x98));
        *(int *)(iVar6 + 4) = iVar3;
        iVar3 = zz_008e0ec_(*(int *)(param_1 + 0x98));
        *(int *)(iVar6 + 8) = iVar3;
        if (iVar2 != 0) {
          return 0;
        }
        uVar5 = zz_008e4b0_(*(int *)(param_1 + 0x98));
        *(uint *)(iVar6 + 0xc) = (uint)uVar5;
        return 0;
      }
      if (cVar1 < '\0') {
        return 0;
      }
      *(char *)(param_1 + 3) = cVar1 + '\x01';
      *(int *)(param_1 + 0x98) = param_2;
      if (*(int *)(iVar6 + 0x44) != *(int *)(iVar6 + 0x40)) {
        *(undefined4 *)(iVar6 + 0xc) = 0xffffffff;
        *(undefined4 *)(iVar6 + 0x10) = 0xffffffff;
        *(undefined4 *)(iVar6 + 0x14) = 0xffffffff;
        *(undefined4 *)(iVar6 + 0x18) = 0xffffffff;
        *(undefined4 *)(iVar6 + 0x24) = 0;
        *(undefined4 *)(iVar6 + 0x20) = 0xffffffff;
        *(undefined1 *)(iVar6 + 2) = 0;
        *(undefined4 *)(iVar6 + 0x28) = 0;
        *(undefined4 *)(iVar6 + 0x44) = *(undefined4 *)(iVar6 + 0x40);
      }
      THPSimpleAudioStop();
    }
    iVar2 = zz_008ea20_(*(int *)(param_1 + 0x98));
    if (iVar2 == 1) {
      return 0;
    }
    *(char *)(param_1 + 3) = *(char *)(param_1 + 3) + '\x01';
    iVar3 = zz_008e0d0_(*(int *)(param_1 + 0x98));
    *(int *)(iVar6 + 4) = iVar3;
    iVar3 = zz_008e0ec_(*(int *)(param_1 + 0x98));
    *(int *)(iVar6 + 8) = iVar3;
    if (iVar2 == 0) {
      uVar7 = zz_008e4c8_(*(int *)(param_1 + 0x98));
      *(undefined8 *)(iVar6 + 0x30) = uVar7;
    }
    uVar4 = CARDGetXferredBytes(*(int *)(param_1 + 0x98));
    *(undefined4 *)(iVar6 + 0x28) = uVar4;
    return 0;
  }
  if (cVar1 != '\x05') {
    if ('\x04' < cVar1) {
      return 0;
    }
    iVar2 = zz_008e944_(*(int *)(param_1 + 0x98));
    if (iVar2 == 1) {
      return 0;
    }
    *(char *)(param_1 + 3) = *(char *)(param_1 + 3) + '\x01';
    iVar3 = zz_008e0d0_(*(int *)(param_1 + 0x98));
    *(int *)(iVar6 + 4) = iVar3;
    iVar3 = zz_008e0ec_(*(int *)(param_1 + 0x98));
    *(int *)(iVar6 + 8) = iVar3;
    if (iVar2 == 0) {
      *(undefined4 *)(iVar6 + 0x18) = 1;
      return 0;
    }
    *(undefined4 *)(iVar6 + 0x18) = 0;
    return 0;
  }
  iVar2 = *(int *)(iVar6 + 4);
  *(int *)(iVar6 + 0x1c) = iVar2;
  if (iVar2 < -6) {
    if ((iVar2 == -0xd) || ((iVar2 < -0xd && (iVar2 == -0x80)))) goto LAB_801af5d8;
  }
  else if ((iVar2 != -4) && ((iVar2 < -4 || (iVar2 < -1)))) goto LAB_801af5d8;
  *(undefined4 *)(iVar6 + 0x1c) = 0;
LAB_801af5d8:
  if (*(int *)(iVar6 + 0x1c) == 0) {
    if (*(int *)(iVar6 + 0x18) == 1) {
      *(undefined4 *)(iVar6 + 0x20) = 0;
    }
    else if ((*(int *)(iVar6 + 0x10) == 0) || (*(int *)(iVar6 + 0x14) < 0x14000)) {
      *(undefined4 *)(iVar6 + 0x20) = 1;
    }
    else {
      *(undefined4 *)(iVar6 + 0x20) = 0;
    }
  }
  *(undefined1 *)(iVar6 + 2) = 1;
  return 1;
}



// ==== 801af660  zz_01af660_ ====

void zz_01af660_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,undefined4 param_10,undefined4 param_11)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar5;
  
  gnt4_memset(&DAT_803d4978,0,0xd8);
  uVar4 = 0;
  puVar3 = &DAT_803d4978;
  uVar2 = 0x28;
  DAT_803d4a41 = 0;
  DAT_803d4a42 = 0x28;
  DAT_803d4a38 = 0xf;
  DAT_803d4a45 = 0x81;
  DAT_803d4a3c = 3;
  DAT_803d4a40 = 0;
  DAT_803d4a10 = param_9;
  DAT_803d4a28 = param_11;
  zz_008e610_(param_11);
  uVar5 = zz_008e620_(param_10);
  puVar1 = &DAT_8043b8e4;
  if (param_9 == 0) {
    puVar1 = &DAT_8043b8d8;
  }
  uVar5 = zz_0096d2c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,puVar1,0,uVar2
                      ,puVar3,uVar4,in_r9,in_r10);
  zz_0096d2c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,&DAT_8043b8dc,1,uVar2,
              puVar3,uVar4,in_r9,in_r10);
  return;
}



// ==== 801af738  zz_01af738_ ====

undefined4 zz_01af738_(void)

{
  if (DAT_803d4a40 == '\0') {
    DAT_803d4a40 = '\x01';
    zz_01b2080_(0,0,(undefined1 *)0x0);
  }
  zz_01b27dc_(&DAT_803d4978);
  DAT_803d4a1c = 0xffffffff;
  (*(code *)(&PTR_zz_01af7c4__803809ac)[DAT_803d4978])(&DAT_803d4978);
  return DAT_803d4a24;
}



// ==== 801af7c4  zz_01af7c4_ ====

void zz_01af7c4_(undefined1 *param_1)

{
  int iVar1;
  
  iVar1 = zz_008e0b8_(*(int *)(param_1 + 0x98));
  if (iVar1 != -1) {
    iVar1 = zz_008e35c_(*(int *)(param_1 + 0x98));
    param_1[*(int *)(param_1 + 0x98) * 0x48 + 0xb] = (char)iVar1;
    *param_1 = 2;
    param_1[3] = 0;
    param_1[2] = 0;
    param_1[1] = 0;
    *(undefined4 *)(param_1 + 0xa4) = 0xffffffff;
  }
  return;
}



// ==== 801af834  zz_01af834_ ====

void zz_01af834_(undefined1 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  
  cVar1 = param_1[1];
  if (cVar1 == '\x01') {
    uVar3 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar3 == 0) {
      return;
    }
    param_1[1] = param_1[1] + '\x01';
    param_1[0xd0] = 1;
    param_1[0xd1] = 0;
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') {
        return;
      }
      param_1[1] = cVar1 + '\x01';
      param_1[0xcc] = 9;
      uVar2 = zz_01b2080_(1,2,param_1 + 0xcc);
      *(undefined4 *)(param_1 + 0xb4) = uVar2;
      *(undefined2 *)(param_1 + 4) = 0xf0;
      return;
    }
    if ('\x02' < cVar1) {
      return;
    }
  }
  uVar3 = zz_01af0f4_((int)param_1,(int)(char)param_1[0xd0],100,
                      (short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x154) +
                      ((short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x14c) + -2) * 0x18,4,0x1b,
                      0x1d);
  param_1[0xd0] = (char)uVar3;
  if ((param_1[0xd0] & 0x80) != 0) {
    param_1[0xd0] = param_1[0xd0] & 0x7f;
    if (param_1[0xd0] == '\0') {
      *(undefined4 *)(param_1 + 0xac) = 0xffffffff;
      *(undefined4 *)(param_1 + 0xa8) = 1;
    }
    else {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
    }
  }
  return;
}



// ==== 801af964  zz_01af964_ ====

void zz_01af964_(undefined1 *param_1)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  
  cVar1 = param_1[1];
  pcVar6 = param_1 + *(int *)(param_1 + 0x98) * 0x48 + 8;
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if ('\x03' < cVar1) {
        return;
      }
      goto LAB_801afa48;
    }
    if (cVar1 == '\0') {
      param_1[1] = 1;
      param_1[0xcc] = 0;
      uVar3 = zz_01b2080_(1,(param_1[0xcd] & 0x40) != 0,param_1 + 0xcc);
      *(undefined4 *)(param_1 + 0xb4) = uVar3;
      *(undefined2 *)(param_1 + 6) = 0x1e;
    }
    else if (cVar1 < '\0') {
      return;
    }
    uVar4 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar4 == 0) {
      return;
    }
    sVar2 = *(short *)(param_1 + 6);
    *(short *)(param_1 + 6) = sVar2 + -1;
    if ((short)(sVar2 + -1) != 0) {
      return;
    }
    param_1[1] = param_1[1] + '\x01';
  }
  param_1[1] = param_1[1] + '\x01';
  param_1[2] = 0;
  param_1[3] = 0;
  pcVar6[4] = -1;
  pcVar6[5] = -1;
  pcVar6[6] = -1;
  pcVar6[7] = -1;
LAB_801afa48:
  iVar5 = zz_01af378_((int)param_1,*(int *)(param_1 + 0x98));
  if (iVar5 != 0) {
    param_1[0xcb] = 0;
    cVar1 = *pcVar6;
    if (cVar1 == '\0') {
      *param_1 = 1;
    }
    else if (((cVar1 == '\0') || (*(int *)(pcVar6 + 0x1c) != 0)) ||
            (*(int *)(pcVar6 + 0x28) != 0x2000)) {
      if ((cVar1 != '\0') && ((*(int *)(pcVar6 + 0x1c) != 0 || (*(int *)(pcVar6 + 0x28) != 0x2000)))
         ) {
        param_1[0xcb] = 2;
        *param_1 = 3;
      }
    }
    else if (*(int *)(pcVar6 + 0x18) == 1) {
      *param_1 = 4;
    }
    else {
      *param_1 = 5;
    }
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
  }
  return;
}



// ==== 801afb18  zz_01afb18_ ====

void zz_01afb18_(undefined1 *param_1)

{
  int iVar1;
  
  iVar1 = zz_01b0048_(param_1,*(undefined4 *)(param_1 + 0x98));
  if (iVar1 != 0) {
    if (iVar1 < 0) {
      *(undefined4 *)(param_1 + 0xac) = 0xffffffff;
    }
    else {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
      param_1[3] = 0;
    }
  }
  return;
}



// ==== 801afb74  zz_01afb74_ ====

void zz_01afb74_(undefined1 *param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  short sVar5;
  short sVar6;
  char cVar7;
  int iVar4;
  byte bVar8;
  
  cVar7 = param_1[1];
  if (cVar7 == '\x03') {
    uVar2 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar2 == 0) {
      return;
    }
    sVar5 = *(short *)(param_1 + 4);
    *(short *)(param_1 + 4) = sVar5 + -1;
    if (((0 < (short)(sVar5 + -1)) && (uVar2 = zz_008b908_(0xf), uVar2 == 0)) &&
       (uVar2 = zz_008b810_(0xf), uVar2 == 0)) {
      return;
    }
    if (param_1[0xcf] == '\0') {
      *(undefined4 *)(param_1 + 0xac) = 1;
      return;
    }
    *(undefined4 *)(param_1 + 0xac) = 0xffffffff;
    return;
  }
  if ('\x02' < cVar7) {
    if (cVar7 == '\x05') {
      iVar3 = zz_01b0d00_((int)param_1);
      if (0 < iVar3) {
        *param_1 = 0;
        param_1[1] = 0;
        return;
      }
      if (-1 < iVar3) {
        return;
      }
      *(undefined4 *)(param_1 + 0xac) = 0xffffffff;
      return;
    }
    if ('\x04' < cVar7) {
      return;
    }
    iVar3 = zz_01b0590_((int)param_1);
    if (iVar3 == 0) {
      return;
    }
    if (iVar3 < 0) {
      *(undefined4 *)(param_1 + 0xac) = 0xffffffff;
      return;
    }
    *param_1 = 0;
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
    return;
  }
  if (cVar7 != '\x01') {
    if ('\0' < cVar7) goto LAB_801afc2c;
    if (cVar7 < '\0') {
      return;
    }
    param_1[1] = cVar7 + '\x01';
    param_1[0xcc] = 2;
    uVar1 = zz_01b2080_(1,0,param_1 + 0xcc);
    *(undefined4 *)(param_1 + 0xb4) = uVar1;
    *(undefined2 *)(param_1 + 6) = 0x1e;
    param_1[0xcf] = 0;
  }
  uVar2 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
  if (uVar2 == 0) {
    return;
  }
  sVar5 = *(short *)(param_1 + 6);
  *(short *)(param_1 + 6) = sVar5 + -1;
  if ((short)(sVar5 + -1) != 0) {
    return;
  }
  param_1[1] = param_1[1] + '\x01';
  THPSimpleAudioStop();
LAB_801afc2c:
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x98);
  iVar3 = zz_008f1b8_(*(int *)(param_1 + 0x98),(uint)(byte)param_1[0xca]);
  *(int *)(param_1 + 0x9c) = iVar3;
  if (*(int *)(param_1 + 0x9c) == 0) {
    bVar8 = 0;
    sVar5 = zz_008e50c_(0);
    iVar3 = zz_008e5d8_(1);
    if (iVar3 == 0) {
      if ((param_1[0xca] & 2) != 0) {
        bVar8 = 2;
      }
    }
    else {
      sVar6 = zz_008e50c_(1);
      sVar5 = sVar5 + sVar6;
    }
    iVar3 = zz_008e5d8_(2);
    if (iVar3 == 0) {
      if ((param_1[0xca] & 4) != 0) {
        bVar8 = bVar8 | 4;
      }
    }
    else {
      sVar6 = zz_008e50c_(2);
      sVar5 = sVar5 + sVar6;
    }
    iVar3 = zz_008e5d8_(3);
    if (iVar3 == 0) {
      if ((param_1[0xca] & 8) != 0) {
        bVar8 = bVar8 | 8;
      }
    }
    else {
      sVar6 = zz_008e50c_(3);
      sVar5 = sVar5 + sVar6;
    }
    iVar3 = zz_008e5d8_(4);
    if (iVar3 == 0) {
      if ((param_1[0xca] & 0x10) != 0) {
        bVar8 = bVar8 | 0x10;
      }
    }
    else {
      sVar6 = zz_008e50c_(4);
      sVar5 = sVar5 + sVar6;
    }
    iVar3 = zz_008e5d8_(5);
    if (iVar3 == 0) {
      bVar8 = bVar8 | 0x20;
    }
    else {
      sVar6 = zz_008e50c_(5);
      sVar5 = sVar5 + sVar6;
    }
    cVar7 = zz_008e308_();
    iVar3 = zz_008e6a4_((int *)0x0,(int *)0x0);
    iVar4 = zz_008e594_();
    if (((sVar5 == 0) && (bVar8 == 0)) && ((cVar7 == '\f' && ((iVar3 == 0 && (iVar4 == 0)))))) {
      param_1[1] = 3;
      param_1[2] = 0;
      *(undefined4 *)(param_1 + 0xa8) = 1;
      *(undefined2 *)(param_1 + 4) = 0xf0;
      param_1[0xcc] = 5;
      uVar1 = zz_01b2080_(1,0,param_1 + 0xcc);
      *(undefined4 *)(param_1 + 0xb4) = uVar1;
    }
    else {
      param_1[0xcf] = param_1[0xcf] | bVar8;
      if (bVar8 == 0) {
        param_1[1] = 4;
      }
      else if (bVar8 == 0x10) {
        param_1[0xca] = param_1[0xca] & 0xef;
      }
      else {
        param_1[1] = 4;
      }
      param_1[2] = 0;
    }
  }
  else if (*(int *)(param_1 + 0x9c) < 0) {
    param_1[1] = 5;
    param_1[2] = 0;
  }
  return;
}



// ==== 801aff14  zz_01aff14_ ====

void zz_01aff14_(undefined1 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  
  cVar1 = param_1[1];
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      goto LAB_801affb4;
    }
    if (cVar1 < '\0') {
      return;
    }
    param_1[1] = cVar1 + '\x01';
    param_1[0xcc] = 10;
    uVar2 = zz_01b2080_(1,(param_1[0xcd] & 0x40) != 0,param_1 + 0xcc);
    *(undefined4 *)(param_1 + 0xb4) = uVar2;
  }
  uVar3 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
  if (uVar3 == 0) {
    return;
  }
  param_1[1] = param_1[1] + '\x01';
  param_1[0xd0] = 1;
  param_1[0xd1] = 0;
LAB_801affb4:
  uVar3 = zz_01af0f4_((int)param_1,(int)(char)param_1[0xd0],100,
                      (short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x154) +
                      ((short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x14c) + -2) * 0x18,3,0x1b,
                      0x1d);
  param_1[0xd0] = (char)uVar3;
  if ((param_1[0xd0] & 0x80) != 0) {
    param_1[0xd0] = param_1[0xd0] & 0x7f;
    if (param_1[0xd0] == '\0') {
      *(undefined4 *)(param_1 + 0xac) = 0xffffffff;
      *(undefined4 *)(param_1 + 0xa8) = 1;
    }
    else {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
    }
  }
  return;
}



// ==== 801b0048  zz_01b0048_ ====

undefined4 zz_01b0048_(undefined1 *param_1,undefined4 param_2)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  *(undefined4 *)(param_1 + 0x98) = param_2;
  cVar1 = param_1[1];
  iVar4 = *(int *)(param_1 + 0x98) * 0x48;
  if (cVar1 == '\x02') {
    uVar3 = zz_01b0bd8_((int)param_1);
    return uVar3;
  }
  if (cVar1 < '\x02') {
    if (cVar1 != '\0') {
      if (cVar1 < '\0') {
        return 0;
      }
      uVar3 = zz_01b0944_((int)param_1);
      return uVar3;
    }
    iVar2 = *(int *)(param_1 + iVar4 + 0x24);
    *(int *)(param_1 + 0xa0) = iVar2;
    if (iVar2 == 0) {
      if (*(int *)(param_1 + iVar4 + 0x28) != 0) {
        param_1[1] = 1;
        return 0;
      }
      param_1[1] = 2;
      return 0;
    }
    param_1[1] = 3;
    if (*(int *)(param_1 + iVar4 + 0x2c) == 0) {
      return 0;
    }
    *(undefined4 *)(param_1 + 0xa0) = 0xffffff80;
    return 0;
  }
  if ('\x03' < cVar1) {
    return 0;
  }
  iVar4 = *(int *)(param_1 + 0xa0);
  if (iVar4 == -6) {
LAB_801b0140:
    uVar3 = zz_01b0174_((int)param_1);
  }
  else {
    if (iVar4 < -6) {
      if (iVar4 == -0xd) goto LAB_801b0140;
    }
    else if (iVar4 == -2) {
      uVar3 = zz_01b0ab0_((int)param_1);
      return uVar3;
    }
    uVar3 = zz_01b0814_(param_1);
  }
  return uVar3;
}



// ==== 801b0174  zz_01b0174_ ====

undefined4 zz_01b0174_(int param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  cVar1 = *(char *)(param_1 + 2);
  if (cVar1 == '\x03') {
    uVar2 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar2 == 0) {
      return 0;
    }
    *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
    *(undefined1 *)(param_1 + 0xd0) = 1;
    *(undefined1 *)(param_1 + 0xd1) = 0;
LAB_801b0328:
    uVar2 = zz_01af0f4_(param_1,(int)*(char *)(param_1 + 0xd0),100,
                        (short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x154) +
                        ((short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x14c) + -2) * 0x18,1,
                        0x1b,0x1d);
    *(char *)(param_1 + 0xd0) = (char)uVar2;
    if ((*(byte *)(param_1 + 0xd0) & 0x80) != 0) {
      *(byte *)(param_1 + 0xd0) = *(byte *)(param_1 + 0xd0) & 0x7f;
      if (*(char *)(param_1 + 0xd0) == '\0') {
        *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
        *(undefined1 *)(param_1 + 3) = 0;
      }
      else {
        uVar3 = 1;
      }
    }
    return uVar3;
  }
  if ('\x02' < cVar1) {
    if (cVar1 == '\x05') {
      uVar3 = zz_01b03c8_(param_1,param_1 + *(int *)(param_1 + 0x98) * 0x48 + 8);
      return uVar3;
    }
    if ('\x04' < cVar1) {
      return 0;
    }
    goto LAB_801b0328;
  }
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) goto LAB_801b0234;
    if (cVar1 < '\0') {
      return 0;
    }
    *(char *)(param_1 + 2) = cVar1 + '\x01';
    *(undefined1 *)(param_1 + 3) = 0;
    *(undefined1 *)(param_1 + 0xcc) = 0x16;
    uVar3 = zz_01b2080_(1,2,(undefined1 *)(param_1 + 0xcc));
    *(undefined4 *)(param_1 + 0xb4) = uVar3;
  }
  uVar2 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
  if (uVar2 == 0) {
    return 0;
  }
  *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
  *(undefined1 *)(param_1 + 0xd0) = 1;
  *(undefined1 *)(param_1 + 0xd1) = 0;
LAB_801b0234:
  uVar2 = zz_01af0f4_(param_1,(int)*(char *)(param_1 + 0xd0),100,
                      (short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x154) +
                      ((short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x14c) + -1) * 0x18,2,0x1b,
                      0x1d);
  *(char *)(param_1 + 0xd0) = (char)uVar2;
  if ((*(byte *)(param_1 + 0xd0) & 0x80) == 0) {
    return 0;
  }
  *(byte *)(param_1 + 0xd0) = *(byte *)(param_1 + 0xd0) & 0x7f;
  cVar1 = *(char *)(param_1 + 0xd0);
  if (cVar1 == '\x01') {
    return 1;
  }
  if ('\0' < cVar1) {
    if ('\x02' < cVar1) {
      return 0;
    }
    *(undefined1 *)(param_1 + 0xcc) = 0x15;
    uVar3 = zz_01b2080_(1,2,(undefined1 *)(param_1 + 0xcc));
    *(undefined4 *)(param_1 + 0xb4) = uVar3;
    *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
    *(undefined1 *)(param_1 + 3) = 0;
    return 0;
  }
  if (cVar1 < '\0') {
    return 0;
  }
  *(undefined4 *)(param_1 + 0xa8) = 1;
  return 0xffffffff;
}



// ==== 801b03c8  zz_01b03c8_ ====

undefined4 zz_01b03c8_(int param_1,int param_2)

{
  char cVar1;
  uint uVar2;
  short sVar6;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  cVar1 = *(char *)(param_1 + 3);
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if (cVar1 != '\x04') {
        if ('\x03' < cVar1) {
          return 0;
        }
        uVar2 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
        if (uVar2 == 0) {
          return 0;
        }
        *(char *)(param_1 + 3) = *(char *)(param_1 + 3) + '\x01';
        *(undefined2 *)(param_1 + 4) = 0xf0;
      }
      sVar6 = *(short *)(param_1 + 4) + -1;
      *(short *)(param_1 + 4) = sVar6;
      if (((0 < sVar6) && (uVar2 = zz_008b908_(0xf), uVar2 == 0)) &&
         (uVar2 = zz_008b810_(0xf), uVar2 == 0)) {
        return 0;
      }
      return 1;
    }
    if (cVar1 == '\0') {
      *(undefined1 *)(param_1 + 3) = 1;
      *(undefined1 *)(param_1 + 0xcc) = 0xe;
      uVar5 = zz_01b2080_(1,2,(undefined1 *)(param_1 + 0xcc));
      *(undefined4 *)(param_1 + 0xb4) = uVar5;
      *(undefined2 *)(param_1 + 6) = 0x1e;
      return 0;
    }
    if (cVar1 < '\0') {
      return 0;
    }
    uVar2 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar2 == 0) {
      return 0;
    }
    sVar6 = *(short *)(param_1 + 6) + -1;
    *(short *)(param_1 + 6) = sVar6;
    if (sVar6 != 0) {
      return 0;
    }
    *(char *)(param_1 + 3) = *(char *)(param_1 + 3) + '\x01';
    THPSimpleAudioStop();
  }
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x98);
  iVar3 = zz_008f774_(*(int *)(param_1 + 0x98));
  if (iVar3 != 1) {
    iVar4 = zz_008e0d0_(*(int *)(param_1 + 0x98));
    *(int *)(param_2 + 4) = iVar4;
    iVar4 = zz_008e0ec_(*(int *)(param_1 + 0x98));
    *(int *)(param_2 + 8) = iVar4;
    if (iVar3 == 0) {
      *(undefined4 *)(param_2 + 0x24) = 0;
      *(undefined1 *)(param_1 + 0xcc) = 0xf;
      uVar5 = zz_01b2080_(1,0xff,(undefined1 *)(param_1 + 0xcc));
      *(undefined4 *)(param_1 + 0xb4) = uVar5;
      *(undefined1 *)(param_1 + 3) = 3;
    }
    else {
      *(undefined4 *)(param_2 + 0x24) = 1;
      *(undefined1 *)(param_1 + 1) = 0;
      *(undefined1 *)(param_1 + 2) = 0;
      *(undefined1 *)(param_1 + 3) = 0;
    }
  }
  return 0;
}



// ==== 801b0590  zz_01b0590_ ====

undefined4 zz_01b0590_(int param_1)

{
  char cVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  short sVar6;
  uint uVar5;
  int iVar7;
  undefined4 uVar8;
  
  uVar8 = 0;
  iVar7 = param_1 + *(int *)(param_1 + 0x98) * 0x48 + 8;
  switch(*(char *)(param_1 + 2)) {
  case '\0':
    *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
    *(undefined1 *)(param_1 + 0xcc) = 0x14;
    uVar4 = zz_01b2080_(1,2,(undefined1 *)(param_1 + 0xcc));
    *(undefined4 *)(param_1 + 0xb4) = uVar4;
  case '\x01':
    uVar5 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar5 != 0) {
      *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
      *(undefined1 *)(param_1 + 0xd0) = 1;
      *(undefined1 *)(param_1 + 0xd1) = 0;
switchD_801b05e8_caseD_2:
      uVar5 = zz_01af0f4_(param_1,(int)*(char *)(param_1 + 0xd0),100,
                          (short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x154) +
                          ((short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x14c) + -3) * 0x18,5,
                          0x1b,0x1d);
      *(char *)(param_1 + 0xd0) = (char)uVar5;
      if ((*(byte *)(param_1 + 0xd0) & 0x80) != 0) {
        *(byte *)(param_1 + 0xd0) = *(byte *)(param_1 + 0xd0) & 0x7f;
        cVar1 = *(char *)(param_1 + 0xd0);
        if (cVar1 == '\x01') {
          uVar8 = 1;
        }
        else if (cVar1 < '\x01') {
          if (-1 < cVar1) {
            uVar8 = 0xffffffff;
            *(undefined4 *)(param_1 + 0xa8) = 1;
          }
        }
        else if (cVar1 < '\x03') {
          *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
          *(undefined1 *)(param_1 + 0xcc) = 0x11;
          uVar4 = zz_01b2080_(1,2,(undefined1 *)(param_1 + 0xcc));
          *(undefined4 *)(param_1 + 0xb4) = uVar4;
        }
      }
    }
    break;
  case '\x02':
    goto switchD_801b05e8_caseD_2;
  case '\x03':
    uVar5 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar5 == 0) {
      return 0;
    }
    *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
    THPSimpleAudioStop();
  case '\x04':
    *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x98);
    iVar2 = zz_008f840_(*(int *)(param_1 + 0x98));
    if (iVar2 != 1) {
      iVar3 = zz_008e0d0_(*(int *)(param_1 + 0x98));
      *(int *)(iVar7 + 4) = iVar3;
      iVar3 = zz_008e0ec_(*(int *)(param_1 + 0x98));
      *(int *)(iVar7 + 8) = iVar3;
      *(undefined1 *)(param_1 + 2) = 5;
      if (iVar2 == 0) {
        *(undefined1 *)(param_1 + 0xcc) = 0x12;
        *(undefined4 *)(iVar7 + 0x18) = 0;
      }
      else {
        *(undefined1 *)(param_1 + 0xcc) = 0x13;
      }
      *(undefined2 *)(param_1 + 4) = 0xf0;
      uVar4 = zz_01b2080_(1,2,(undefined1 *)(param_1 + 0xcc));
      *(undefined4 *)(param_1 + 0xb4) = uVar4;
    }
    break;
  case '\x05':
    uVar5 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar5 == 0) {
      return 0;
    }
    *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
  case '\x06':
    sVar6 = *(short *)(param_1 + 4) + -1;
    *(short *)(param_1 + 4) = sVar6;
    if (((sVar6 < 1) || (uVar5 = zz_008b908_(0xf), uVar5 != 0)) ||
       (uVar5 = zz_008b810_(0xf), uVar5 != 0)) {
      uVar8 = 1;
    }
    break;
  default:
    break;
  }
  return uVar8;
}



// ==== 801b0814  zz_01b0814_ ====

undefined4 zz_01b0814_(undefined1 *param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  cVar1 = param_1[2];
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return 0;
      }
      goto LAB_801b08ac;
    }
    if (cVar1 < '\0') {
      return 0;
    }
    param_1[2] = cVar1 + '\x01';
    param_1[0xcc] = 0x17;
    uVar2 = zz_01b2080_(1,2,param_1 + 0xcc);
    *(undefined4 *)(param_1 + 0xb4) = uVar2;
  }
  uVar3 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
  if (uVar3 == 0) {
    return 0;
  }
  param_1[2] = param_1[2] + '\x01';
  param_1[0xd0] = 1;
  param_1[0xd1] = 0;
LAB_801b08ac:
  uVar3 = zz_01af0f4_((int)param_1,(int)(char)param_1[0xd0],100,
                      (short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x154) +
                      ((short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x14c) + -2) * 0x18,3,0x1b,
                      0x1d);
  param_1[0xd0] = (char)uVar3;
  if ((param_1[0xd0] & 0x80) != 0) {
    param_1[0xd0] = param_1[0xd0] & 0x7f;
    if (param_1[0xd0] == '\0') {
      uVar4 = 0xffffffff;
      *(undefined4 *)(param_1 + 0xa8) = 1;
    }
    else {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
    }
  }
  return uVar4;
}



// ==== 801b0944  zz_01b0944_ ====

undefined4 zz_01b0944_(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  
  uVar4 = 0;
  cVar1 = *(char *)(param_1 + 2);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return 0;
      }
      goto LAB_801b09dc;
    }
    if (cVar1 < '\0') {
      return 0;
    }
    *(char *)(param_1 + 2) = cVar1 + '\x01';
    *(undefined1 *)(param_1 + 0xcc) = 0xc;
    uVar2 = zz_01b2080_(1,2,(undefined1 *)(param_1 + 0xcc));
    *(undefined4 *)(param_1 + 0xb4) = uVar2;
  }
  uVar3 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
  if (uVar3 == 0) {
    return 0;
  }
  *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
  *(undefined1 *)(param_1 + 0xd0) = 1;
  *(undefined1 *)(param_1 + 0xd1) = 0;
LAB_801b09dc:
  uVar3 = countLeadingZeros(*(byte *)(param_1 + 0xcd) & 0x3f);
  uVar3 = zz_01af0f4_(param_1,(int)*(char *)(param_1 + 0xd0),100,
                      (short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x154) +
                      ((short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x14c) + -3) * 0x18,
                      ~-(uVar3 >> 5 & 1) & 3,0x1b,0x1d);
  *(char *)(param_1 + 0xd0) = (char)uVar3;
  if ((*(byte *)(param_1 + 0xd0) & 0x80) != 0) {
    *(byte *)(param_1 + 0xd0) = *(byte *)(param_1 + 0xd0) & 0x7f;
    cVar1 = *(char *)(param_1 + 0xd0);
    if (cVar1 == '\x01') {
      uVar4 = 1;
      *(undefined1 *)(param_1 + 0xce) = 0;
    }
    else if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        uVar4 = 0xffffffff;
        *(undefined4 *)(param_1 + 0xa8) = 1;
      }
    }
    else if (cVar1 < '\x03') {
      zz_002a84c_();
    }
  }
  return uVar4;
}



// ==== 801b0ab0  zz_01b0ab0_ ====

undefined4 zz_01b0ab0_(int param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  cVar1 = *(char *)(param_1 + 2);
  if (cVar1 == '\x01') {
    uVar2 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar2 == 0) {
      return 0;
    }
    *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
    *(undefined1 *)(param_1 + 0xd0) = 1;
    *(undefined1 *)(param_1 + 0xd1) = 0;
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') {
        return 0;
      }
      *(char *)(param_1 + 2) = cVar1 + '\x01';
      *(undefined1 *)(param_1 + 0xcc) = 0xb;
      uVar3 = zz_01b2080_(1,2,(undefined1 *)(param_1 + 0xcc));
      *(undefined4 *)(param_1 + 0xb4) = uVar3;
      return 0;
    }
    if ('\x02' < cVar1) {
      return 0;
    }
  }
  uVar2 = zz_01af0f4_(param_1,(int)*(char *)(param_1 + 0xd0),100,
                      (short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x154) +
                      ((short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x14c) + -2) * 0x18,4,0x1b,
                      0x1d);
  *(char *)(param_1 + 0xd0) = (char)uVar2;
  if ((*(byte *)(param_1 + 0xd0) & 0x80) != 0) {
    *(byte *)(param_1 + 0xd0) = *(byte *)(param_1 + 0xd0) & 0x7f;
    if (*(char *)(param_1 + 0xd0) == '\0') {
      uVar3 = 0xffffffff;
      *(undefined4 *)(param_1 + 0xa8) = 1;
    }
    else {
      uVar3 = 1;
    }
  }
  return uVar3;
}



// ==== 801b0bd8  zz_01b0bd8_ ====

undefined4 zz_01b0bd8_(int param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  cVar1 = *(char *)(param_1 + 2);
  if (cVar1 == '\x01') {
    uVar2 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar2 == 0) {
      return 0;
    }
    *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
    *(undefined1 *)(param_1 + 0xd0) = 1;
    *(undefined1 *)(param_1 + 0xd1) = 0;
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') {
        return 0;
      }
      *(char *)(param_1 + 2) = cVar1 + '\x01';
      *(undefined1 *)(param_1 + 0xcc) = 0x18;
      uVar3 = zz_01b2080_(1,2,(undefined1 *)(param_1 + 0xcc));
      *(undefined4 *)(param_1 + 0xb4) = uVar3;
      return 0;
    }
    if ('\x02' < cVar1) {
      return 0;
    }
  }
  uVar2 = zz_01af0f4_(param_1,(int)*(char *)(param_1 + 0xd0),100,
                      (short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x154) +
                      ((short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x14c) + -2) * 0x18,3,0x1b,
                      0x1d);
  *(char *)(param_1 + 0xd0) = (char)uVar2;
  if ((*(byte *)(param_1 + 0xd0) & 0x80) != 0) {
    *(byte *)(param_1 + 0xd0) = *(byte *)(param_1 + 0xd0) & 0x7f;
    if (*(char *)(param_1 + 0xd0) == '\0') {
      uVar3 = 0xffffffff;
      *(undefined4 *)(param_1 + 0xa8) = 1;
    }
    else {
      uVar3 = 1;
    }
  }
  return uVar3;
}



// ==== 801b0d00  zz_01b0d00_ ====

undefined4 zz_01b0d00_(int param_1)

{
  char cVar1;
  uint uVar2;
  undefined4 uVar3;
  
  uVar3 = 0;
  cVar1 = *(char *)(param_1 + 2);
  if (cVar1 == '\x01') {
    uVar2 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar2 == 0) {
      return 0;
    }
    *(char *)(param_1 + 2) = *(char *)(param_1 + 2) + '\x01';
    *(undefined1 *)(param_1 + 0xd0) = 1;
    *(undefined1 *)(param_1 + 0xd1) = 0;
  }
  else {
    if (cVar1 < '\x01') {
      if (cVar1 < '\0') {
        return 0;
      }
      *(char *)(param_1 + 2) = cVar1 + '\x01';
      *(undefined1 *)(param_1 + 0xcc) = 6;
      uVar3 = zz_01b2080_(1,2,(undefined1 *)(param_1 + 0xcc));
      *(undefined4 *)(param_1 + 0xb4) = uVar3;
      return 0;
    }
    if ('\x02' < cVar1) {
      return 0;
    }
  }
  uVar2 = zz_01af0f4_(param_1,(int)*(char *)(param_1 + 0xd0),100,
                      (short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x154) +
                      ((short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x14c) + -2) * 0x18,3,0x1b,
                      0x1d);
  *(char *)(param_1 + 0xd0) = (char)uVar2;
  if ((*(byte *)(param_1 + 0xd0) & 0x80) != 0) {
    *(byte *)(param_1 + 0xd0) = *(byte *)(param_1 + 0xd0) & 0x7f;
    if (*(char *)(param_1 + 0xd0) == '\0') {
      uVar3 = 0xffffffff;
      *(undefined4 *)(param_1 + 0xa8) = 1;
    }
    else {
      uVar3 = 1;
    }
  }
  return uVar3;
}



// ==== 801b0e28  zz_01b0e28_ ====

void zz_01b0e28_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 uVar1;
  int iVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined4 in_r10;
  undefined8 uVar5;
  
  gnt4_memset(&DAT_803d4978,0,0xd8);
  uVar4 = 0;
  puVar3 = &DAT_803d4978;
  DAT_803d4a41 = 0;
  uVar1 = 0x82;
  DAT_803d4a42 = 0x3c;
  DAT_803d4a10 = 0;
  iVar2 = (int)(char)PTR_DAT_80433930[2];
  DAT_803d4a45 = 0x82;
  DAT_803d4a3c = 6;
  DAT_803d4a40 = 0;
  DAT_803d4a38 = iVar2;
  uVar5 = zz_0096d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,
                      &DAT_8043b8d8,0,0x82,iVar2,&DAT_803d4978,0,in_r10);
  zz_0096d2c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,&DAT_8043b8dc,1,uVar1,
              iVar2,puVar3,uVar4,in_r10);
  zz_0027c1c_();
  zz_008e610_(DAT_80436220);
  zz_008e600_(DAT_80436224);
  uVar5 = zz_008e620_(&DAT_803bfe20);
  zz_00449e8_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2);
  return;
}



// ==== 801b0ee8  zz_01b0ee8_ ====

int zz_01b0ee8_(void)

{
  int iVar1;
  
  iVar1 = zz_01af738_();
  if (iVar1 == 0) {
    iVar1 = 1;
  }
  else if (iVar1 == 1) {
    iVar1 = 0;
  }
  else if (iVar1 < 0) {
    iVar1 = -1;
  }
  return iVar1;
}



// ==== 801b0f34  zz_01b0f34_ ====

void zz_01b0f34_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar3;
  
  gnt4_memset(&DAT_803d4978,0,0xd8);
  uVar2 = 1;
  puVar1 = &DAT_803d4978;
  DAT_803d4a41 = 1;
  DAT_803d4a38 = (int)(char)PTR_DAT_80433930[2];
  DAT_803d4a40 = 1;
  DAT_803d4a42 = 0x3c;
  DAT_803d4a10 = 0;
  DAT_803d4a45 = 0x42;
  if (param_9 == 0) {
    DAT_803d4a3c = 1;
  }
  else {
    DAT_803d4a3c = 2;
  }
  DAT_803d4a30 = param_9;
  uVar3 = zz_0096d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,
                      &DAT_8043b8d8,0,&DAT_803d4978,1,in_r8,in_r9,in_r10);
  zz_0096d2c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,&DAT_8043b8dc,1,puVar1
              ,uVar2,in_r8,in_r9,in_r10);
  zz_008e610_(DAT_80436220);
  zz_008e600_(DAT_80436224);
  uVar3 = zz_008e620_(&DAT_803bfe20);
  zz_00449e8_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2);
  return;
}



// ==== 801b1014  zz_01b1014_ ====

int zz_01b1014_(void)

{
  int iVar1;
  
  if (DAT_803d4a40 == '\0') {
    DAT_803d4a40 = '\x01';
    zz_01b2080_(0,0,(undefined1 *)0x0);
  }
  zz_01b27dc_(&DAT_803d4978);
  DAT_803d4a1c = 0xffffffff;
  (*(code *)(&PTR_zz_01af7c4__803809e0)[DAT_803d4978])(&DAT_803d4978);
  if (DAT_803d4a24 == 0) {
    iVar1 = 1;
  }
  else if (DAT_803d4a24 < 0) {
    iVar1 = -1;
  }
  else {
    iVar1 = 0;
  }
  if (iVar1 != 1) {
    zz_0044af0_();
  }
  return iVar1;
}



// ==== 801b10d0  zz_01b10d0_ ====

void zz_01b10d0_(undefined1 *param_1)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  
  cVar1 = param_1[1];
  pcVar6 = param_1 + *(int *)(param_1 + 0x98) * 0x48 + 8;
  if (cVar1 != '\x02') {
    if ('\x01' < cVar1) {
      if ('\x03' < cVar1) {
        return;
      }
      goto LAB_801b11b4;
    }
    if (cVar1 == '\0') {
      param_1[1] = 1;
      param_1[0xcc] = 0;
      uVar3 = zz_01b2080_(1,(param_1[0xcd] & 0x40) != 0,param_1 + 0xcc);
      *(undefined4 *)(param_1 + 0xb4) = uVar3;
      *(undefined2 *)(param_1 + 6) = 0x1e;
    }
    else if (cVar1 < '\0') {
      return;
    }
    uVar4 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar4 == 0) {
      return;
    }
    sVar2 = *(short *)(param_1 + 6);
    *(short *)(param_1 + 6) = sVar2 + -1;
    if ((short)(sVar2 + -1) != 0) {
      return;
    }
    param_1[1] = param_1[1] + '\x01';
  }
  param_1[1] = param_1[1] + '\x01';
  param_1[2] = 0;
  param_1[3] = 0;
  pcVar6[4] = -1;
  pcVar6[5] = -1;
  pcVar6[6] = -1;
  pcVar6[7] = -1;
LAB_801b11b4:
  iVar5 = zz_01af378_((int)param_1,*(int *)(param_1 + 0x98));
  if (iVar5 != 0) {
    param_1[0xcb] = 0;
    cVar1 = *pcVar6;
    if (cVar1 == '\0') {
      *param_1 = 1;
    }
    else if ((((cVar1 == '\0') || (*(int *)(pcVar6 + 0x1c) != 0)) || (*(int *)(pcVar6 + 0x20) != 0))
            || (*(int *)(pcVar6 + 0x28) != 0x2000)) {
      if ((cVar1 != '\0') &&
         (((*(int *)(pcVar6 + 0x1c) != 0 || (*(int *)(pcVar6 + 0x20) != 0)) ||
          (*(int *)(pcVar6 + 0x28) != 0x2000)))) {
        param_1[0xcb] = 2;
        *param_1 = 3;
      }
    }
    else {
      *param_1 = 4;
    }
    param_1[1] = 0;
    param_1[2] = 0;
    param_1[3] = 0;
  }
  return;
}



// ==== 801b1284  zz_01b1284_ ====

void zz_01b1284_(undefined1 *param_1)

{
  short sVar1;
  int iVar2;
  int iVar3;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  ushort uVar9;
  ushort uVar10;
  ushort uVar11;
  undefined4 uVar4;
  uint uVar5;
  
  iVar2 = *(int *)(param_1 + 0x98);
  switch(param_1[1]) {
  case 0:
    param_1[1] = param_1[1] + '\x01';
    THPSimpleAudioStop();
    param_1[0xcc] = 3;
    uVar4 = zz_01b2080_(1,1,param_1 + 0xcc);
    *(undefined4 *)(param_1 + 0xb4) = uVar4;
    *(undefined2 *)(param_1 + 6) = 0x1e;
  case 1:
    uVar5 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if ((uVar5 != 0) &&
       (sVar1 = *(short *)(param_1 + 6), *(short *)(param_1 + 6) = sVar1 + -1,
       (short)(sVar1 + -1) == 0)) {
      param_1[1] = param_1[1] + '\x01';
      zz_008e640_(*(int *)(param_1 + 0x98),0xff);
      zz_008e630_(&LAB_8008e674);
switchD_801b12d4_caseD_2:
      *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x98);
      iVar3 = zz_008eae8_(*(int *)(param_1 + 0x98),(uint)(byte)param_1[0xca]);
      *(int *)(param_1 + 0x9c) = iVar3;
      iVar3 = zz_008e658_(*(int *)(param_1 + 0x98));
      if ((*(int *)(param_1 + 0x9c) < 0) && (iVar3 == 0)) {
        *(undefined4 *)(param_1 + 0x9c) = 0;
      }
      if (*(int *)(param_1 + 0x9c) == 0) {
        uVar11 = 0;
        iVar3 = 0;
        if (*(int *)(param_1 + iVar2 * 0x48 + 0x20) == 1) {
          uVar6 = zz_008e50c_(0);
          uVar7 = zz_008e50c_(1);
          uVar8 = zz_008e50c_(2);
          uVar9 = zz_008e50c_(3);
          uVar10 = zz_008e50c_(4);
          uVar11 = zz_008e50c_(5);
          uVar11 = uVar6 | uVar7 | uVar8 | uVar9 | uVar10 | uVar11;
          iVar3 = zz_008e6a4_((int *)0x0,(int *)0x0);
        }
        if ((uVar11 == 0) && (iVar3 == 0)) {
          iVar3 = zz_008e554_();
          if (iVar3 == 0) {
            param_1[1] = 3;
            param_1[2] = 0;
            *(undefined4 *)(param_1 + 0xa8) = 1;
            *(undefined2 *)(param_1 + 4) = 0xf0;
            param_1[0xcc] = 7;
            uVar4 = zz_01b2080_(1,1,param_1 + 0xcc);
            *(undefined4 *)(param_1 + 0xb4) = uVar4;
          }
          else {
            param_1[1] = 4;
            param_1[2] = 0;
            param_1[0xcc] = 0x19;
            param_1[3] = 3;
            if (*(int *)(param_1 + iVar2 * 0x48 + 0x20) == 0) {
              param_1[0xcc] = 0x1a;
              param_1[3] = 6;
            }
            uVar4 = zz_01b2080_(1,2,param_1 + 0xcc);
            *(undefined4 *)(param_1 + 0xb4) = uVar4;
          }
        }
        else {
          param_1[1] = 6;
          param_1[2] = 0;
          param_1[3] = 0;
        }
      }
      else if (*(int *)(param_1 + 0x9c) < 0) {
        param_1[1] = 4;
        param_1[2] = 0;
        param_1[0xcc] = 8;
        uVar4 = zz_01b2080_(1,2,param_1 + 0xcc);
        *(undefined4 *)(param_1 + 0xb4) = uVar4;
        param_1[3] = 3;
      }
    }
    break;
  case 2:
    goto switchD_801b12d4_caseD_2;
  case 3:
    uVar5 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if ((uVar5 != 0) &&
       (((sVar1 = *(short *)(param_1 + 4), *(short *)(param_1 + 4) = sVar1 + -1,
         (short)(sVar1 + -1) < 1 || (uVar5 = zz_008b908_(0xf), uVar5 != 0)) ||
        (uVar5 = zz_008b810_(0xf), uVar5 != 0)))) {
      *(undefined4 *)(param_1 + 0xac) = 1;
    }
    break;
  case 4:
    uVar5 = zz_01b27a0_(*(int *)(param_1 + 0xb4));
    if (uVar5 == 0) {
      return;
    }
    param_1[1] = 5;
    param_1[0xd0] = 0;
    param_1[0xd1] = 0;
  case 5:
    uVar5 = zz_01af0f4_((int)param_1,(int)(char)param_1[0xd0],100,
                        (short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x154) +
                        ((short)*(undefined4 *)(*(int *)(param_1 + 0xb4) + 0x14c) + 1) * 0x18,
                        (int)(char)param_1[3],0x1b,0x1d);
    param_1[0xd0] = (char)uVar5;
    if ((param_1[0xd0] & 0x80) != 0) {
      param_1[0xd0] = param_1[0xd0] & 0x7f;
      if (param_1[0xd0] == '\0') {
        *(undefined4 *)(param_1 + 0xac) = 0xffffffff;
        *(undefined4 *)(param_1 + 0xa8) = 1;
      }
      else {
        *param_1 = 0;
        param_1[1] = 0;
        param_1[2] = 0;
        param_1[3] = 0;
      }
    }
    break;
  case 6:
    iVar2 = zz_01b0590_((int)param_1);
    if (iVar2 != 0) {
      if (iVar2 < 0) {
        *(undefined4 *)(param_1 + 0xac) = 0xffffffff;
      }
      else {
        *param_1 = 0;
        param_1[1] = 0;
        param_1[2] = 0;
        param_1[3] = 0;
      }
    }
  }
  return;
}



// ==== 801b1650  zz_01b1650_ ====

void zz_01b1650_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined4 in_r10;
  undefined8 uVar6;
  
  gnt4_memset(&DAT_803d4978,0,0xd8);
  puVar4 = &DAT_803d4978;
  uVar5 = 0;
  iVar3 = 1 << param_10;
  uVar2 = 0x2c;
  DAT_803d4a41 = 0;
  puVar1 = &DAT_8043b8e4;
  DAT_803d4a42 = 0x2c;
  DAT_803d4a45 = 0x84;
  DAT_803d4a3c = 4;
  DAT_803d4a40 = 0;
  if (param_9 == 0) {
    puVar1 = &DAT_8043b8d8;
  }
  DAT_803d4a10 = param_9;
  DAT_803d4a38 = iVar3;
  uVar6 = zz_0096d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,puVar1,0,
                      0x2c,iVar3,&DAT_803d4978,0,in_r10);
  zz_0096d2c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,&DAT_8043b8dc,1,uVar2,
              iVar3,puVar4,uVar5,in_r10);
  if (param_9 == 0) {
    iVar3 = DAT_80436238 + 0x2b2c00;
  }
  else {
    iVar3 = DAT_80436238 + 0x2c6c00;
  }
  zz_008e610_(iVar3 + 0xccb0);
  zz_008e600_(iVar3 + 0x20c8);
  uVar6 = zz_008e620_(iVar3 + 0x13470);
  zz_00449e8_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3);
  return;
}



// ==== 801b1758  zz_01b1758_ ====

int zz_01b1758_(void)

{
  int iVar1;
  
  iVar1 = zz_01af738_();
  if (iVar1 == 0) {
    iVar1 = 1;
  }
  else if (iVar1 == 1) {
    iVar1 = 0;
  }
  else if (iVar1 < 0) {
    iVar1 = -1;
  }
  if (iVar1 != 1) {
    zz_0044af0_();
  }
  return iVar1;
}



// ==== 801b17bc  zz_01b17bc_ ====

void zz_01b17bc_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10)

{
  undefined *puVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined1 *puVar5;
  undefined4 in_r10;
  undefined8 uVar6;
  
  gnt4_memset(&DAT_803d4978,0,0xd8);
  puVar5 = &DAT_803d4978;
  iVar4 = 1 << param_10;
  uVar3 = 0x2c;
  uVar2 = 0x44;
  DAT_803d4a41 = 1;
  puVar1 = &DAT_8043b8e4;
  DAT_803d4a42 = 0x2c;
  DAT_803d4a45 = 0x44;
  DAT_803d4a30 = 0;
  DAT_803d4a3c = 4;
  DAT_803d4a40 = 0;
  if (param_9 == 0) {
    puVar1 = &DAT_8043b8d8;
  }
  DAT_803d4a10 = param_9;
  DAT_803d4a38 = iVar4;
  uVar6 = zz_0096d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,puVar1,0,
                      0x44,0x2c,iVar4,&DAT_803d4978,in_r10);
  zz_0096d2c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,&DAT_8043b8dc,1,uVar2,
              uVar3,iVar4,puVar5,in_r10);
  if (param_9 == 0) {
    iVar4 = DAT_80436238 + 0x2b2c00;
  }
  else {
    iVar4 = DAT_80436238 + 0x2c6c00;
  }
  zz_008e610_(iVar4 + 0xccb0);
  zz_008e600_(iVar4 + 0x20c8);
  uVar6 = zz_008e620_(iVar4 + 0x13470);
  zz_00449e8_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,3);
  return;
}



// ==== 801b18c8  zz_01b18c8_ ====

int zz_01b18c8_(void)

{
  int iVar1;
  
  zz_01b27dc_(&DAT_803d4978);
  DAT_803d4a1c = 0xffffffff;
  (*(code *)(&PTR_zz_01af7c4__80380a14)[DAT_803d4978])();
  if (DAT_803d4a24 == 0) {
    iVar1 = 1;
  }
  else if (DAT_803d4a24 < 0) {
    iVar1 = -1;
  }
  else {
    iVar1 = 0;
  }
  if (iVar1 != 1) {
    zz_0044af0_();
  }
  return iVar1;
}



// ==== 801b1960  zz_01b1960_ ====

void zz_01b1960_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined1 *puVar5;
  undefined8 uVar6;
  
  gnt4_memset(&DAT_803d4978,0,0xd8);
  uVar4 = 1;
  puVar5 = &DAT_803d4978;
  iVar3 = 1 << param_10;
  uVar2 = 0x2c;
  DAT_803d4a41 = 0;
  puVar1 = &DAT_8043b8e4;
  DAT_803d4a42 = 0x2c;
  DAT_803d4a45 = 0x83;
  DAT_803d4a3c = 3;
  DAT_803d4a40 = 1;
  if (param_9 == 0) {
    puVar1 = &DAT_8043b8d8;
  }
  DAT_803d4a10 = param_9;
  DAT_803d4a38 = iVar3;
  uVar6 = zz_0096d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,puVar1,0,
                      0x2c,iVar3,1,&DAT_803d4978,param_16);
  zz_0096d2c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,&DAT_8043b8dc,1,uVar2,
              iVar3,uVar4,puVar5,param_16);
  zz_008e610_(param_13);
  zz_008e600_(param_12);
  uVar6 = zz_008e620_(param_11);
  zz_00449e8_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,4);
  return;
}



// ==== 801b1a40  zz_01b1a40_ ====

int zz_01b1a40_(void)

{
  int iVar1;
  
  iVar1 = zz_01af738_();
  if (iVar1 == 0) {
    iVar1 = 1;
  }
  else if (iVar1 == 1) {
    iVar1 = 0;
  }
  else if (iVar1 < 0) {
    iVar1 = -1;
  }
  if (iVar1 != 1) {
    zz_0044af0_();
  }
  return iVar1;
}



// ==== 801b1aa4  zz_01b1aa4_ ====

void zz_01b1aa4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  
  gnt4_memset(&DAT_803d4978,0,0xd8);
  uVar5 = 1;
  puVar4 = &DAT_803d4978;
  uVar2 = 0x2c;
  iVar3 = 1 << param_10;
  DAT_803d4a41 = 1;
  puVar1 = &DAT_8043b8e4;
  DAT_803d4a42 = 0x2c;
  DAT_803d4a45 = 0x43;
  DAT_803d4a30 = 0;
  DAT_803d4a3c = 1;
  DAT_803d4a40 = 1;
  if (param_9 == 0) {
    puVar1 = &DAT_8043b8d8;
  }
  DAT_803d4a10 = param_9;
  DAT_803d4a38 = iVar3;
  uVar6 = zz_0096d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,puVar1,0,
                      0x2c,iVar3,&DAT_803d4978,1,param_16);
  zz_0096d2c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,&DAT_8043b8dc,1,uVar2,
              iVar3,puVar4,uVar5,param_16);
  zz_008e610_(param_13);
  zz_008e600_(param_12);
  uVar6 = zz_008e620_(param_11);
  zz_00449e8_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,4);
  return;
}



// ==== 801b1b84  zz_01b1b84_ ====

void zz_01b1b84_(void)

{
  zz_01b1014_();
  return;
}



// ==== 801b1ba4  zz_01b1ba4_ ====

void zz_01b1ba4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined4 in_r10;
  undefined8 uVar5;
  
  gnt4_memset(&DAT_803d4978,0,0xd8);
  puVar4 = &DAT_803d4978;
  DAT_803d4a41 = 0;
  uVar2 = 0x85;
  uVar1 = 5;
  DAT_803d4a42 = 0x28;
  DAT_803d4a10 = 0;
  iVar3 = (int)(char)PTR_DAT_80433930[2];
  DAT_803d4a45 = 0x85;
  DAT_803d4a3c = 5;
  DAT_803d4a40 = 1;
  DAT_803d4a38 = iVar3;
  uVar5 = zz_0096d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,
                      &DAT_8043b8d8,0,5,0x85,iVar3,&DAT_803d4978,in_r10);
  zz_0096d2c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,&DAT_8043b8dc,1,uVar1,
              uVar2,iVar3,puVar4,in_r10);
  zz_0027c1c_();
  zz_008e610_(DAT_80436220);
  uVar5 = zz_008e620_(&DAT_803bfe20);
  zz_00449e8_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,5);
  return;
}



// ==== 801b1c60  zz_01b1c60_ ====

int zz_01b1c60_(void)

{
  int iVar1;
  
  iVar1 = zz_01af738_();
  if (iVar1 == 0) {
    iVar1 = 1;
  }
  else if (iVar1 == 1) {
    iVar1 = 0;
  }
  else if (iVar1 < 0) {
    iVar1 = -1;
  }
  if (iVar1 != 1) {
    zz_0044af0_();
  }
  return iVar1;
}



// ==== 801b1cc4  zz_01b1cc4_ ====

void zz_01b1cc4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9,int param_10,undefined4 param_11,undefined4 param_12,undefined4 param_13
                ,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 *puVar4;
  undefined4 uVar5;
  undefined8 uVar6;
  
  gnt4_memset(&DAT_803d4978,0,0xd8);
  puVar4 = &DAT_803d4978;
  uVar5 = 0;
  iVar3 = 1 << param_10;
  uVar2 = 0x2c;
  DAT_803d4a41 = 0;
  puVar1 = &DAT_8043b8e4;
  DAT_803d4a42 = 0x2c;
  DAT_803d4a45 = 0x86;
  DAT_803d4a3c = 3;
  DAT_803d4a40 = 0;
  if (param_9 == 0) {
    puVar1 = &DAT_8043b8d8;
  }
  DAT_803d4a10 = param_9;
  DAT_803d4a38 = iVar3;
  uVar6 = zz_0096d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,puVar1,0,
                      0x2c,iVar3,&DAT_803d4978,0,param_16);
  zz_0096d2c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,&DAT_8043b8dc,1,uVar2,
              iVar3,puVar4,uVar5,param_16);
  zz_008e610_(param_13);
  zz_008e600_(param_12);
  uVar6 = zz_008e620_(param_11);
  zz_00449e8_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,6);
  return;
}



// ==== 801b1da4  zz_01b1da4_ ====

int zz_01b1da4_(void)

{
  int iVar1;
  
  iVar1 = zz_01af738_();
  if (iVar1 == 0) {
    iVar1 = 1;
  }
  else if (iVar1 == 1) {
    iVar1 = 0;
  }
  else if (iVar1 < 0) {
    iVar1 = -1;
  }
  if (iVar1 != 1) {
    zz_0044af0_();
  }
  return iVar1;
}



// ==== 801b1e08  zz_01b1e08_ ====

void zz_01b1e08_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined4 in_r10;
  undefined8 uVar5;
  
  gnt4_memset(&DAT_803d4978,0,0xd8);
  uVar4 = 0;
  puVar3 = &DAT_803d4978;
  uVar2 = 0x22;
  uVar1 = 0x87;
  DAT_803d4a41 = 0;
  DAT_803d4a38 = 0xf;
  DAT_803d4a42 = 0x22;
  DAT_803d4a10 = 0;
  DAT_803d4a45 = 0x87;
  DAT_803d4a3c = 3;
  DAT_803d4a40 = 0;
  uVar5 = zz_0096d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,
                      &DAT_8043b8d8,0,0x87,0x22,&DAT_803d4978,0,in_r10);
  zz_0096d2c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,&DAT_8043b8dc,1,uVar1,
              uVar2,puVar3,uVar4,in_r10);
  uVar5 = zz_008e620_(&DAT_803bfe20);
  zz_00449e8_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,7);
  return;
}



// ==== 801b1eac  zz_01b1eac_ ====

int zz_01b1eac_(void)

{
  int iVar1;
  
  iVar1 = zz_01af738_();
  if (iVar1 == 0) {
    iVar1 = 1;
  }
  else if (iVar1 == 1) {
    iVar1 = 0;
  }
  else if (iVar1 < 0) {
    iVar1 = -1;
  }
  if (iVar1 != 1) {
    zz_0044af0_();
  }
  return iVar1;
}



// ==== 801b1f10  zz_01b1f10_ ====

void zz_01b1f10_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined1 *puVar3;
  undefined4 uVar4;
  undefined4 in_r10;
  undefined8 uVar5;
  
  gnt4_memset(&DAT_803d4978,0,0xd8);
  uVar4 = 1;
  puVar3 = &DAT_803d4978;
  uVar1 = 0;
  uVar2 = 0x22;
  DAT_803d4a41 = 1;
  DAT_803d4a38 = 0xf;
  DAT_803d4a42 = 0x22;
  DAT_803d4a10 = 0;
  DAT_803d4a45 = 0x47;
  DAT_803d4a30 = 0;
  DAT_803d4a3c = 1;
  DAT_803d4a40 = 0;
  uVar5 = zz_0096d2c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,
                      &DAT_8043b8d8,0,0,0x22,&DAT_803d4978,1,in_r10);
  zz_0096d2c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,&DAT_8043b8dc,1,uVar1,
              uVar2,puVar3,uVar4,in_r10);
  uVar5 = zz_008e620_(&DAT_803bfe20);
  zz_00449e8_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,7);
  return;
}



// ==== 801b1fb8  zz_01b1fb8_ ====

void zz_01b1fb8_(void)

{
  zz_01b1014_();
  return;
}



// ==== 801b1fd8  zz_01b1fd8_ ====

undefined1 *
zz_01b1fd8_(undefined1 param_1,undefined1 param_2,undefined1 *param_3,undefined4 param_4)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x38,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = zz_01b20ac_;
    *(code **)(puVar1 + 0x10c) = zz_01b26fc_;
    puVar1[0x11] = param_1;
    puVar1[0x12] = param_2;
    *(undefined1 **)(puVar1 + 0x54) = param_3;
    *(undefined4 *)(puVar1 + 200) = param_4;
    gnt4_memset(puVar1 + 0x144,0,0x14);
    if (param_3 != (undefined1 *)0x0) {
      puVar1[0x145] = *param_3;
    }
  }
  return puVar1;
}



// ==== 801b2080  zz_01b2080_ ====

void zz_01b2080_(undefined1 param_1,undefined1 param_2,undefined1 *param_3)

{
  zz_01b1fd8_(param_1,param_2,param_3,&DAT_803d4a24);
  return;
}



// ==== 801b20ac  zz_01b20ac_ ====

void zz_01b20ac_(int param_1)

{
  (*(code *)(&PTR_zz_01b20e8__80380a2c)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801b20e8  zz_01b20e8_ ====

void zz_01b20e8_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(undefined4 *)(param_1 + 0xcc) = DAT_803bb37c;
  return;
}



// ==== 801b2104  zz_01b2104_ ====

void zz_01b2104_(int param_1)

{
  (*(code *)(&PTR_zz_01b213c__804359dc)[*(char *)(param_1 + 0x11)])();
  return;
}



// ==== 801b213c  zz_01b213c_ ====

void zz_01b213c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  char cVar2;
  float fVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar4;
  bool bVar5;
  undefined8 uVar6;
  double dVar7;
  
  fVar3 = FLOAT_8043b8f0;
  fVar1 = FLOAT_8043b8e8;
  cVar2 = *(char *)(param_9 + 0x19);
  iVar4 = *(int *)(param_9 + 0xe0);
  if (cVar2 != '\x01') {
    if ('\0' < cVar2) {
      if ('\x02' < cVar2) {
        return;
      }
      dVar7 = (double)*(float *)(param_9 + 0xd4);
      fVar1 = (float)(dVar7 - (double)*(float *)(param_9 + 0xd8));
      *(float *)(param_9 + 0xd4) = fVar1;
      if (fVar1 <= fVar3) {
        *(float *)(param_9 + 0xd4) = fVar3;
        *(undefined1 *)(param_9 + 0x18) = 2;
        *(undefined1 *)(param_9 + 0x19) = 0;
        *(undefined1 *)(param_9 + 0x1a) = 0;
      }
      uVar6 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),dVar7,param_3,param_4,param_5,param_6,
                          param_7,param_8,*(int *)(param_9 + 0xcc),iVar4,param_11,param_12,param_13,
                          param_14,param_15,param_16);
      zz_0007c30_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,extraout_r4_00,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      return;
    }
    if (cVar2 < '\0') {
      return;
    }
    if (*(char *)(param_9 + 0x1a) == '\0') {
      *(undefined1 *)(param_9 + 0x1a) = 1;
      param_11 = (float *)0x0;
      *(float *)(param_9 + 0xd8) = fVar1;
      *(float *)(param_9 + 0xd4) = -*(float *)(param_9 + 0xd8);
      zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xcc),iVar4,0,param_12,param_13,param_14,param_15,param_16);
      *(undefined1 *)(param_9 + 0x82) = 0x15;
    }
    fVar3 = FLOAT_8043b8ec;
    dVar7 = (double)*(float *)(param_9 + 0xd4);
    fVar1 = (float)(dVar7 + (double)*(float *)(param_9 + 0xd8));
    bVar5 = FLOAT_8043b8ec < fVar1;
    *(float *)(param_9 + 0xd4) = fVar1;
    if (bVar5) {
      *(float *)(param_9 + 0xd4) = fVar3;
      *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
      *(undefined1 *)(param_9 + 0x1a) = 0;
    }
    uVar6 = zz_00086b8_((double)*(float *)(param_9 + 0xd4),dVar7,param_3,param_4,param_5,param_6,
                        param_7,param_8,*(int *)(param_9 + 0xcc),iVar4,param_11,param_12,param_13,
                        param_14,param_15,param_16);
    zz_0007c30_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,extraout_r4,
                param_11,param_12,param_13,param_14,param_15,param_16);
  }
  if (**(int **)(param_9 + 200) != 0) {
    *(undefined1 *)(param_9 + 0x19) = 2;
    *(undefined1 *)(param_9 + 0x1a) = 0;
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801b22a4  zz_01b22a4_ ====

void zz_01b22a4_(int param_1)

{
  if (((**(char **)(param_1 + 0x54) < '\0') ||
      (*(char *)(param_1 + 0x145) != **(char **)(param_1 + 0x54))) ||
     (**(int **)(param_1 + 200) != 0)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    (*(code *)(&PTR_zz_01b2324__804359e4)[*(char *)(param_1 + 0x19)])();
  }
  return;
}



// ==== 801b2324  zz_01b2324_ ====

void zz_01b2324_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  bool bVar3;
  float fVar4;
  float fVar5;
  short sVar6;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar7;
  undefined4 extraout_r4_01;
  float *pfVar8;
  uint *puVar9;
  int iVar10;
  bool bVar11;
  double dVar12;
  undefined8 uVar13;
  double dVar14;
  undefined4 uStack_38;
  float local_34;
  undefined4 uStack_2c;
  float local_28;
  undefined4 local_20;
  uint uStack_1c;
  
  cVar1 = *(char *)(param_9 + 0x1a);
  if (cVar1 == '\x01') {
    bVar3 = false;
    if (*(char *)(param_9 + 0x12) < '\0') {
      bVar3 = true;
    }
    else {
      sVar6 = *(short *)(param_9 + 0x1e) + -1;
      *(short *)(param_9 + 0x1e) = sVar6;
      if (sVar6 == 0) {
        *(undefined1 *)(*(int *)(param_9 + 0xe4) + 0x10) = 1;
      }
      if (*(char *)(*(int *)(param_9 + 0xe4) + 0x10) != '\0') {
        zz_0007bb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 0xe4),&uStack_2c,param_11,param_12,param_13,param_14,param_15
                    ,param_16);
        param_2 = (double)local_28;
        dVar12 = (double)FLOAT_8043b8ec;
        if ((param_2 < dVar12) &&
           (local_28 = (float)(param_2 + (double)*(float *)(param_9 + 0x58)),
           dVar12 <= (double)local_28)) {
          local_28 = FLOAT_8043b8ec;
          bVar3 = true;
        }
        zz_0007ae4_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 0xe4),&uStack_2c,(char *)param_11,param_12,param_13,param_14,
                    param_15,param_16);
      }
    }
    if ((*(short *)(param_9 + 0x146) != 0) &&
       (sVar6 = *(short *)(param_9 + 0x146) + -1, *(short *)(param_9 + 0x146) = sVar6, sVar6 < 1)) {
      *(undefined1 *)(param_9 + 0x144) = 1;
    }
    *(float *)(param_9 + 0xd8) = *(float *)(param_9 + 0xd8) + FLOAT_8043b908;
    fVar2 = *(float *)(param_9 + 0xd4);
    bVar11 = fVar2 < *(float *)(param_9 + 0xd8);
    if (bVar11) {
      *(float *)(param_9 + 0xd8) = fVar2;
    }
    if (((*(char *)(param_9 + 0x144) != '\0') && (bVar3)) && (bVar11)) {
      *(char *)(param_9 + 0x1a) = *(char *)(param_9 + 0x1a) + '\x01';
    }
    iVar10 = *(int *)(param_9 + 0xe0);
    dVar12 = (double)*(float *)(param_9 + 0xd8);
    zz_0008614_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xcc),iVar10,param_11,param_12,param_13,param_14,param_15,
                param_16);
    zz_0007c30_(dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),iVar10,param_11,param_12,param_13,param_14,param_15,
                param_16);
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(char *)(param_9 + 0x1a) = cVar1 + '\x01';
      puVar9 = (uint *)(param_9 + 0x14c);
      zz_009749c_(0,(int)*(char *)(param_9 + 0x145),(int *)(param_9 + 0x148),puVar9);
      *(undefined4 *)(param_9 + 0x150) = 100;
      *(int *)(param_9 + 0x154) = 0xe0 - (*(int *)(param_9 + 0x14c) * 0x18) / 2;
      fVar2 = FLOAT_8043b8f8;
      fVar5 = FLOAT_8043b8f4;
      fVar4 = FLOAT_8043b8f0;
      if (*(int *)(param_9 + 0x14c) < 4) {
        *(float *)(param_9 + 0xd4) = FLOAT_8043b8f4;
        *(float *)(param_9 + 0xd8) = fVar4;
        fVar2 = fVar5;
      }
      else {
        *(float *)(param_9 + 0xd4) = FLOAT_8043b8f8;
        *(float *)(param_9 + 0xd8) = fVar5;
      }
      iVar10 = *(int *)(param_9 + 0xe0);
      pfVar8 = (float *)0x1;
      zz_0006fb4_((double)fVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xcc),iVar10,1,puVar9,param_13,param_14,param_15,param_16);
      local_20 = 0x43300000;
      uStack_1c = (int)*(char *)(param_9 + 0x12) ^ 0x80000000;
      dVar12 = (double)(float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8043b910);
      if (dVar12 < (double)FLOAT_8043b8f0) {
        dVar12 = (double)FLOAT_8043b8f0;
      }
      dVar14 = DOUBLE_8043b910;
      uVar13 = zz_00086b8_(dVar12,DOUBLE_8043b910,param_3,param_4,param_5,param_6,param_7,param_8,
                           *(int *)(param_9 + 0xcc),iVar10,pfVar8,puVar9,param_13,param_14,param_15,
                           param_16);
      uVar13 = zz_0007c30_(uVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,
                           extraout_r4,pfVar8,puVar9,param_13,param_14,param_15,param_16);
      zz_0007d40_(uVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,
                  extraout_r4_00,pfVar8,puVar9,param_13,param_14,param_15,param_16);
      dVar12 = (double)*(float *)(param_9 + 0xd8);
      iVar7 = iVar10;
      zz_0008614_(dVar12,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + 0xcc),iVar10,pfVar8,puVar9,param_13,param_14,param_15,param_16)
      ;
      uVar13 = zz_0007c30_(dVar12,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,
                           iVar7,pfVar8,puVar9,param_13,param_14,param_15,param_16);
      uVar13 = zz_0007908_(uVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,
                           &uStack_38,pfVar8,puVar9,param_13,param_14,param_15,param_16);
      *(undefined2 *)(param_9 + 0x1e) = 6;
      iVar10 = *(int *)(param_9 + 0xe4);
      *(undefined1 *)(iVar10 + 0x10) = 0;
      if (-1 < *(char *)(param_9 + 0x12)) {
        pfVar8 = (float *)0x2;
        zz_0006fb4_(uVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(param_9 + 0xcc),iVar10,2,puVar9,param_13,param_14,param_15,param_16);
        local_20 = 0x43300000;
        uStack_1c = (int)*(char *)(param_9 + 0x12) ^ 0x80000000;
        uVar13 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,uStack_1c) -
                                            DOUBLE_8043b910),dVar14,param_3,param_4,param_5,param_6,
                             param_7,param_8,*(int *)(param_9 + 0xcc),iVar10,pfVar8,puVar9,param_13,
                             param_14,param_15,param_16);
        uVar13 = zz_0007c30_(uVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,
                             extraout_r4_01,pfVar8,puVar9,param_13,param_14,param_15,param_16);
        uVar13 = zz_0007bb4_(uVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,
                             &uStack_2c,pfVar8,puVar9,param_13,param_14,param_15,param_16);
        local_28 = FLOAT_8043b8f0;
        zz_0007ae4_(uVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,&uStack_2c,
                    (char *)pfVar8,puVar9,param_13,param_14,param_15,param_16);
        if (*(int *)(param_9 + 0x14c) < 4) {
          dVar12 = (double)FLOAT_8043b8fc;
          *(float *)(param_9 + 0x58) = (float)(dVar12 + (double)local_34);
        }
        else {
          dVar12 = (double)FLOAT_8043b900;
          *(float *)(param_9 + 0x58) = (float)(dVar12 + (double)local_34);
        }
        uVar13 = zz_0007908_(dVar12,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,
                             &uStack_38,pfVar8,puVar9,param_13,param_14,param_15,param_16);
        local_34 = *(float *)(param_9 + 0x58);
        zz_0007834_(uVar13,dVar14,param_3,param_4,param_5,param_6,param_7,param_8,iVar10,&uStack_38,
                    (char *)pfVar8,puVar9,param_13,param_14,param_15,param_16);
        fVar2 = FLOAT_8043b904;
        *(undefined1 *)(iVar10 + 0x10) = 0;
        *(float *)(param_9 + 0x58) = fVar2;
      }
      *(undefined2 *)(param_9 + 0x146) = 8;
      *(undefined1 *)(param_9 + 0x82) = 0x15;
    }
  }
  else if (cVar1 < '\x03') {
    *(char *)(param_9 + 0x19) = *(char *)(param_9 + 0x19) + '\x01';
    *(undefined1 *)(param_9 + 0x1a) = 0;
    *(undefined1 *)(param_9 + 0x144) = 1;
  }
  return;
}



// ==== 801b26bc  zz_01b26bc_ ====

void zz_01b26bc_(int param_1)

{
  *(undefined1 *)(param_1 + 0x144) = 1;
  return;
}



// ==== 801b26c8  zz_01b26c8_ ====

void zz_01b26c8_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801b26dc  zz_01b26dc_ ====

void zz_01b26dc_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801b26fc  zz_01b26fc_ ====

void zz_01b26fc_(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = 0;
  iVar2 = param_1;
  do {
    if (-1 < *(int *)(*(int *)(iVar2 + 0xe0) + 0x14)) {
      zz_0009958_(*(int *)(iVar2 + 0xe0),1);
    }
    iVar1 = iVar1 + 1;
    iVar2 = iVar2 + 4;
  } while (iVar1 < 2);
  if (*(char *)(param_1 + 0x144) != '\0') {
    zz_0096d0c_((double)FLOAT_8043b8ec);
    zz_0096d14_((double)FLOAT_8043b918);
    zz_00970b4_((short)*(undefined4 *)(param_1 + 0x150),(short)*(undefined4 *)(param_1 + 0x154),0x1b
                ,'\0',(short)*(char *)(param_1 + 0x145),-1);
  }
  return;
}



// ==== 801b27a0  zz_01b27a0_ ====

uint zz_01b27a0_(int param_1)

{
  return (uint)(-(int)*(char *)(param_1 + 0x144) | (int)*(char *)(param_1 + 0x144)) >> 0x1f;
}



// ==== 801b27b8  zz_01b27b8_ ====

void zz_01b27b8_(int param_1,undefined4 *param_2,undefined4 *param_3)

{
  if (param_2 != (undefined4 *)0x0) {
    *param_2 = *(undefined4 *)(param_1 + 0x154);
  }
  if (param_3 == (undefined4 *)0x0) {
    return;
  }
  *param_3 = *(undefined4 *)(param_1 + 0x14c);
  return;
}



// ==== 801b27dc  zz_01b27dc_ ====

void zz_01b27dc_(undefined1 *param_1)

{
  int iVar1;
  char *pcVar2;
  
  pcVar2 = param_1 + *(int *)(param_1 + 0x98) * 0x48 + 8;
  pcVar2[1] = *pcVar2;
  iVar1 = zz_008e340_(*(int *)(param_1 + 0x98));
  *pcVar2 = (char)iVar1;
  if (*pcVar2 != pcVar2[1]) {
    if (*pcVar2 != '\0') {
      iVar1 = zz_008e35c_(*(int *)(param_1 + 0x98));
      pcVar2[3] = (char)iVar1;
      *(int *)(pcVar2 + 0x40) = *(int *)(pcVar2 + 0x40) + 1;
    }
    if ((*(int *)(param_1 + 0xa8) == 0) && (*(int *)(param_1 + 0xa4) < 0)) {
      *param_1 = 0;
      param_1[1] = 0;
      param_1[2] = 0;
      param_1[3] = 0;
      param_1[0xcc] = 0xff;
    }
  }
  return;
}



// ==== 801b289c  zz_01b289c_ ====

void zz_01b289c_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_zz_01b29b8__80380a40;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_01b297c__80380a44;
  *(undefined **)(param_1 + 0x4bc) = PTR_zz_01b29a0__80380a48;
  *(undefined **)(param_1 + 0x4c0) = PTR_zz_01b29a4__80380a4c;
  *(undefined **)(param_1 + 0x4c4) = PTR_zz_01b29a8__80380a50;
  *(undefined **)(param_1 + 0x4c8) = PTR_zz_01b29ac__80380a54;
  *(undefined **)(param_1 + 0x4cc) = PTR_zz_01b29b0__80380a58;
  *(undefined **)(param_1 + 0x4d0) = PTR_zz_01b29b4__80380a5c;
  *(undefined4 *)(param_1 + 0x4d4) = DAT_80380a60;
  *(undefined4 *)(param_1 + 0x4d8) = DAT_80380a64;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_80380a68;
  *(undefined4 *)(param_1 + 0x4e0) = DAT_80380a6c;
  *(undefined4 *)(param_1 + 0x4e4) = DAT_80380a70;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_80380a74;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_80380a78;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_80380a7c;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_80380aa0;
  *(undefined4 *)(param_1 + 0x1d8c) = 0;
  *(undefined4 *)(param_1 + 0x1d88) = 0;
  *(undefined4 *)(param_1 + 0x1d84) = 0;
  *(undefined4 *)(param_1 + 0x1d80) = 0;
  *(undefined **)(param_1 + 0x27c) = &DAT_80380c90;
  return;
}



// ==== 801b297c  zz_01b297c_ ====

void zz_01b297c_(int param_1)

{
  zz_00c74ec_(param_1,0x42);
  return;
}



// ==== 801b29a0  zz_01b29a0_ ====

void zz_01b29a0_(void)

{
  return;
}



// ==== 801b29a4  zz_01b29a4_ ====

void zz_01b29a4_(void)

{
  return;
}



// ==== 801b29a8  zz_01b29a8_ ====

void zz_01b29a8_(void)

{
  return;
}



// ==== 801b29ac  zz_01b29ac_ ====

void zz_01b29ac_(void)

{
  return;
}



// ==== 801b29b0  zz_01b29b0_ ====

void zz_01b29b0_(void)

{
  return;
}



// ==== 801b29b4  zz_01b29b4_ ====

void zz_01b29b4_(void)

{
  return;
}



// ==== 801b29b8  zz_01b29b8_ ====

void zz_01b29b8_(int param_1)

{
  (**(code **)(&DAT_804359f0 + *(char *)(param_1 + 0x580) * 4))();
  return;
}



// ==== 801b29f0  zz_01b29f0_ ====

void zz_01b29f0_(int param_1)

{
  (*(code *)(&PTR_zz_01b2a2c__80380a80)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801b2a2c  zz_01b2a2c_ ====

void zz_01b2a2c_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043b920;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined2 *)(param_1 + 0x146) = 0;
  *(undefined2 *)(param_1 + 0x148) = 0;
  *(undefined2 *)(param_1 + 0x14a) = 0;
  return;
}



// ==== 801b2a54  zz_01b2a54_ ====

void zz_01b2a54_(int param_1)

{
  int iVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_8043b924;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = FUN_8006cc90(dVar2,param_1,2,1,(short *)&DAT_804359f4);
  if ((iVar1 == 0) && (FLOAT_8043b928 < *(float *)(param_1 + 0x558))) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 801b2ac8  zz_01b2ac8_ ====

void zz_01b2ac8_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_006dbe0_(param_1,0,1,1);
  if (iVar1 != 0) {
    zz_00c3be0_(param_1,0x3c);
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x548) = 0x28;
  return;
}



// ==== 801b2b28  zz_01b2b28_ ====

void zz_01b2b28_(int param_1)

{
  *(short *)(param_1 + 0x548) = *(short *)(param_1 + 0x548) + -1;
  if (*(short *)(param_1 + 0x548) < 1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 801b2b64  zz_01b2b64_ ====

void zz_01b2b64_(int param_1,byte param_2)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0x613) || (*(short *)(param_1 + 1000) == 0x627)) {
    puVar1 = zz_0088aa0_(param_1,3,8,0,2);
    if (puVar1 == (undefined1 *)0x0) {
      zz_01b3530_(0,param_1);
    }
    else {
      *puVar1 = 1;
      puVar1[0x10] = 0x5a;
      puVar1[0x11] = param_2;
      puVar1[0x13] = param_2 & 1;
      *(code **)(puVar1 + 0xc) = zz_01b2c8c_;
      *(code **)(puVar1 + 0x10c) = zz_01b3490_;
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



// ==== 801b2c8c  zz_01b2c8c_ ====

void zz_01b2c8c_(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_zz_01b2d24__80380e88)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801b2d24  zz_01b2d24_ ====

void zz_01b2d24_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  iVar5 = *(int *)(param_9 + 0x90);
  iVar2 = (uint)*(byte *)(param_9 + 0x11) * 0x28;
  iVar1 = zz_008ac80_(param_9,(int)(char)(&DAT_80380cab)[iVar2]);
  if (iVar1 == 0) {
    zz_01b3530_(param_9,iVar5);
  }
  else {
    uVar4 = 0x10;
    *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
    *(undefined1 *)(param_9 + 0x84) = 0x10;
    *(undefined1 *)(param_9 + 0x98) = 5;
    puVar3 = (undefined4 *)(uint)(byte)(&DAT_80380caa)[iVar2];
    *(undefined *)(param_9 + 0x89) = (&DAT_80380caa)[iVar2];
    *(code **)(param_9 + 0x100) = zz_0048288_;
    zz_0089100_(param_9,0,1);
    if (0 < *(short *)(&DAT_80380cca + iVar2)) {
      *(byte *)(param_9 + 0x2ac) = *(byte *)(param_9 + 0x2ac) | 1;
    }
    *(undefined2 *)(param_9 + 0x176) = 0;
    *(undefined2 *)(param_9 + 0x174) = 300;
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar5 + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4),
               (float *)(iVar2 + -0x7fc7f354),(float *)(param_9 + 0x20));
    *(undefined4 *)(param_9 + 0x2c) = *(undefined4 *)(param_9 + 0x20);
    *(undefined4 *)(param_9 + 0x30) = *(undefined4 *)(param_9 + 0x24);
    *(undefined4 *)(param_9 + 0x34) = *(undefined4 *)(param_9 + 0x28);
    *(undefined4 *)(param_9 + 0x9c) =
         *(undefined4 *)(iVar5 + ((byte)(&DAT_80380cc8)[iVar2] & 0x7f) * 4 + 0x8d4);
    *(undefined4 *)(param_9 + 0xa0) =
         *(undefined4 *)(iVar5 + ((byte)(&DAT_80380cc8)[iVar2] & 0x7f) * 4 + 0x8e4);
    *(undefined4 *)(param_9 + 0xa4) =
         *(undefined4 *)(iVar5 + ((byte)(&DAT_80380cc8)[iVar2] & 0x7f) * 4 + 0x8f4);
    if (((&DAT_80380cc8)[iVar2] & 0x80) != 0) {
      gnt4_PSQUATScale_bl((double)FLOAT_8043b930,(float *)(param_9 + 0x9c),(float *)(param_9 + 0x9c)
                         );
    }
    zz_0083d60_(param_9,iVar5,0);
    zz_006ebb4_((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x58) * *(float *)(&DAT_80380ccc + iVar2);
    *(float *)(param_9 + 0x5c) = *(float *)(param_9 + 0x5c) * *(float *)(&DAT_80380ccc + iVar2);
    *(float *)(param_9 + 0x60) = *(float *)(param_9 + 0x60) * *(float *)(&DAT_80380ccc + iVar2);
    *(float *)(param_9 + 0xb4) = *(float *)(param_9 + 0xb4) * *(float *)(&DAT_80380ccc + iVar2);
    uVar6 = zz_0048288_(param_9);
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_80380cb8 + iVar2);
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_80380cbc + iVar2);
    *(undefined2 *)(param_9 + 0x1e) = 10;
    *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_80380cbe + iVar2);
    if (0 < *(short *)(&DAT_80380cca + iVar2)) {
      puVar3 = (undefined4 *)(param_9 + 0x168);
      uVar4 = 1;
      *(undefined4 *)(param_9 + 0x168) = *(undefined4 *)(param_9 + 0x20);
      in_r8 = 0;
      *(undefined4 *)(param_9 + 0x16c) = *(undefined4 *)(param_9 + 0x24);
      *(undefined4 *)(param_9 + 0x170) = *(undefined4 *)(param_9 + 0x28);
      *(undefined4 *)(param_9 + 0x15c) = *(undefined4 *)(param_9 + 0x168);
      *(undefined4 *)(param_9 + 0x160) = *(undefined4 *)(param_9 + 0x16c);
      *(undefined4 *)(param_9 + 0x164) = *(undefined4 *)(param_9 + 0x170);
      uVar6 = zz_00a2bf8_(*(int *)(param_9 + 0x90),param_9,(undefined4 *)(param_9 + 0x15c),puVar3,1,
                          0);
    }
    iVar1 = zz_0006f98_(iVar5);
    uVar6 = zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xe0),
                        (uint)(byte)(&DAT_80380ca8)[iVar2],puVar3,uVar4,in_r8,in_r9,in_r10);
    zz_0006fb4_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xe4),(uint)(byte)(&DAT_80380ca9)[iVar2],
                puVar3,uVar4,in_r8,in_r9,in_r10);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    zz_01b2fb0_(param_9);
  }
  return;
}



// ==== 801b2fb0  zz_01b2fb0_ ====

void zz_01b2fb0_(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x174) + -1;
  *(short *)(param_1 + 0x174) = sVar1;
  if (sVar1 < 1) {
    zz_01b3530_(param_1,*(int *)(param_1 + 0x90));
  }
  else {
    (*(code *)(&PTR_zz_01b3094__80380e98)[*(char *)(param_1 + 0x19)])();
    if (*(short *)(param_1 + 0x176) < 1) {
      *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0xc00;
    }
    else {
      *(short *)(param_1 + 0x176) = *(short *)(param_1 + 0x176) + -1;
    }
    gnt4_PSMTXMultVec_bl
              ((float *)(*(int *)(param_1 + 0x90) + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
               (float *)((uint)*(byte *)(param_1 + 0x11) * 0x28 + -0x7fc7f354),
               (float *)(param_1 + 0x15c));
    *(undefined4 *)(param_1 + 0x168) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x16c) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x170) = *(undefined4 *)(param_1 + 0x28);
  }
  return;
}



// ==== 801b3094  zz_01b3094_ ====

void zz_01b3094_(int param_1)

{
  float fVar1;
  int iVar2;
  short sVar4;
  int iVar3;
  int iVar5;
  
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  iVar5 = *(int *)(param_1 + 0x90);
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x28;
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    sVar4 = *(short *)(param_1 + 0x1e) + -1;
    *(short *)(param_1 + 0x1e) = sVar4;
    if (sVar4 < 1) goto LAB_801b31a8;
    *(undefined2 *)(param_1 + 0x176) = 8;
  }
  if (*(short *)(param_1 + 0x176) < 1) {
    FUN_80083874((double)*(float *)(&DAT_80380cc4 + iVar2),param_1);
    FUN_80083ad4((double)*(float *)(&DAT_80380cc0 + iVar2),param_1,
                 (char)*(undefined2 *)(&DAT_80380cbe + iVar2));
  }
  if (*(short *)(&DAT_80380cca + iVar2) == 0) {
    zz_00833ec_(param_1);
    zz_0083524_(param_1);
  }
  else if (*(char *)(iVar5 + *(char *)(param_1 + 0x13) + 0x144) < '\0') goto LAB_801b31a8;
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
  iVar3 = zz_0083244_((float *)(param_1 + 0x20));
  if (((iVar3 == 0) && (iVar3 = zz_0084170_(param_1), iVar3 == 0)) &&
     (0 < *(short *)(param_1 + 0x1c))) {
    return;
  }
LAB_801b31a8:
  fVar1 = FLOAT_8043b934;
  if (*(short *)(&DAT_80380cca + iVar2) < 1) {
    zz_01b3530_(param_1,iVar5);
  }
  else {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(float *)(param_1 + 0x4c) = -*(float *)(param_1 + 0x44) * fVar1;
  }
  return;
}



// ==== 801b3200  zz_01b3200_ ====

void zz_01b3200_(int param_1)

{
  float fVar1;
  int iVar2;
  
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x28;
  FUN_80083874((double)*(float *)(&DAT_80380cc4 + iVar2),param_1);
  FUN_80083ad4((double)*(float *)(&DAT_80380cc0 + iVar2),param_1,
               (char)*(undefined2 *)(&DAT_80380cbe + iVar2));
  fVar1 = FLOAT_8043b938;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x4c);
  if (*(float *)(param_1 + 0x44) < fVar1) {
    *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined2 *)(param_1 + 0x1e) = 0x14;
    *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
    *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(param_1 + 0x9c);
    *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(param_1 + 0xa0);
    *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0xa4);
    zz_01b32d4_(param_1);
  }
  return;
}



// ==== 801b32d4  zz_01b32d4_ ====

/* WARNING: Removing unreachable block (ram,0x801b340c) */
/* WARNING: Removing unreachable block (ram,0x801b32e4) */

void zz_01b32d4_(int param_1)

{
  int iVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  float local_38;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 local_28;
  uint uStack_24;
  
  local_28 = 0x43300000;
  uStack_24 = (int)*(short *)(param_1 + 0x1e) ^ 0x80000000;
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x28;
  iVar4 = *(int *)(param_1 + 0x90);
  dVar5 = (double)((float)((double)CONCAT44(0x43300000,uStack_24) - DOUBLE_8043b940) /
                  FLOAT_8043b93c);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar4 + *(char *)(param_1 + 0x89) * 0x30 + 0x8d4),
             (float *)(iVar3 + -0x7fc7f354),&local_38);
  zz_0046588_(dVar5,(float *)(param_1 + 0x150),&local_38,(float *)(param_1 + 0x20));
  gnt4_PSVECSubtract_bl((float *)(param_1 + 0x150),&local_38,(float *)(param_1 + 0x38));
  iVar1 = iVar4 + *(char *)(param_1 + 0x89) * 0x30 + ((int)(char)(&DAT_80380cc9)[iVar3] & 0x7fU) * 4
  ;
  local_38 = *(float *)(iVar1 + 0x8d4);
  local_34 = *(undefined4 *)(iVar1 + 0x8e4);
  local_30 = *(undefined4 *)(iVar1 + 0x8f4);
  if (((int)(char)(&DAT_80380cc9)[iVar3] & 0x80U) != 0) {
    gnt4_PSQUATScale_bl((double)FLOAT_8043b930,&local_38,&local_38);
  }
  zz_0046588_(dVar5,(float *)(param_1 + 0x144),&local_38,(float *)(param_1 + 0x9c));
  sVar2 = *(short *)(param_1 + 0x1e) + -1;
  *(short *)(param_1 + 0x1e) = sVar2;
  if (sVar2 < 1) {
    zz_01b3530_(param_1,iVar4);
  }
  return;
}



// ==== 801b3434  zz_01b3434_ ====

void zz_01b3434_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801b3470  zz_01b3470_ ====

void zz_01b3470_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801b3490  zz_01b3490_ ====

/* WARNING: Removing unreachable block (ram,0x801b34ac) */

void zz_01b3490_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  float afStack_38 [12];
  
  iVar2 = *(int *)(param_9 + 0x90);
  gnt4_PSMTXRotRad_bl((double)(float)((double)FLOAT_8043b948 *
                                     (double)((longlong)(double)*(short *)(param_9 + 0x70) *
                                             0x3ff0000000000000)),afStack_38,0x78);
  pfVar1 = afStack_38;
  uVar4 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0)
              ,afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  uVar3 = 1;
  if (*(char *)(iVar2 + 0x3ec) == '\x04') {
    uVar3 = 0x44;
  }
  uVar4 = zz_00097b4_(*(int *)(param_9 + 0xe0),uVar3);
  zz_00076d0_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,afStack_38,(undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(param_9 + 0xe4),uVar3);
  return;
}



// ==== 801b3530  zz_01b3530_ ====

void zz_01b3530_(int param_1,int param_2)

{
  if (param_1 != 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  if (param_2 != 0) {
    *(undefined1 *)(param_2 + *(char *)(param_1 + 0x13) + 0x144) = 1;
  }
  return;
}



// ==== 801b3598  zz_01b3598_ ====

void zz_01b3598_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_zz_01b36f4__80380ea8;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_01b3688__80380eac;
  *(undefined **)(param_1 + 0x4bc) = PTR_zz_01b36ac__80380eb0;
  *(undefined **)(param_1 + 0x4c0) = PTR_zz_01b36b0__80380eb4;
  *(undefined **)(param_1 + 0x4c4) = PTR_zz_01b36e4__80380eb8;
  *(undefined **)(param_1 + 0x4c8) = PTR_zz_01b36e8__80380ebc;
  *(undefined **)(param_1 + 0x4cc) = PTR_zz_01b36ec__80380ec0;
  *(undefined **)(param_1 + 0x4d0) = PTR_zz_01b36f0__80380ec4;
  *(undefined4 *)(param_1 + 0x4d4) = DAT_80380ec8;
  *(undefined4 *)(param_1 + 0x4d8) = DAT_80380ecc;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_80380ed0;
  *(undefined4 *)(param_1 + 0x4e0) = DAT_80380ed4;
  *(undefined4 *)(param_1 + 0x4e4) = DAT_80380ed8;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_80380edc;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_80380ee0;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_80380ee4;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_80380f08;
  *(undefined **)(param_1 + 0x1d80) = &DAT_802bd54c;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bd65e;
  *(undefined4 *)(param_1 + 0x1d8c) = 0;
  *(undefined4 *)(param_1 + 0x1d88) = 0;
  *(undefined **)(param_1 + 0x27c) = &DAT_803810f8;
  return;
}



// ==== 801b3688  zz_01b3688_ ====

void zz_01b3688_(int param_1)

{
  zz_00c74ec_(param_1,0x43);
  return;
}



// ==== 801b36ac  zz_01b36ac_ ====

void zz_01b36ac_(void)

{
  return;
}



// ==== 801b36b0  zz_01b36b0_ ====

void zz_01b36b0_(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 0x10) != 0) {
    zz_00f0104_(param_1,0x14,6);
  }
  return;
}



// ==== 801b36e4  zz_01b36e4_ ====

void zz_01b36e4_(void)

{
  return;
}



// ==== 801b36e8  zz_01b36e8_ ====

void zz_01b36e8_(void)

{
  return;
}



// ==== 801b36ec  zz_01b36ec_ ====

void zz_01b36ec_(void)

{
  return;
}



// ==== 801b36f0  zz_01b36f0_ ====

void zz_01b36f0_(void)

{
  return;
}



// ==== 801b36f4  zz_01b36f4_ ====

void zz_01b36f4_(int param_1)

{
  (**(code **)(&DAT_80435a08 + *(char *)(param_1 + 0x580) * 4))();
  return;
}



// ==== 801b372c  zz_01b372c_ ====

void zz_01b372c_(int param_1)

{
  (*(code *)(&PTR_zz_01b3768__80380ee8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801b3768  zz_01b3768_ ====

void zz_01b3768_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043b954;
  fVar1 = FLOAT_8043b950;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(float *)(param_1 + 0x55c) = fVar2;
  *(undefined2 *)(param_1 + 0x146) = 0;
  *(undefined2 *)(param_1 + 0x148) = 0;
  *(undefined2 *)(param_1 + 0x14a) = 0;
  return;
}



// ==== 801b3798  zz_01b3798_ ====

void zz_01b3798_(int param_1)

{
  int iVar1;
  double dVar2;
  
  if ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x146) = 1;
  }
  dVar2 = (double)FLOAT_8043b958;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = FUN_8006cc90(dVar2,param_1,2,1,(short *)&DAT_80435a00);
  if ((iVar1 == 0) && (FLOAT_8043b954 < *(float *)(param_1 + 0x558))) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 801b3824  zz_01b3824_ ====

void zz_01b3824_(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  FUN_8006cc90((double)FLOAT_8043b958,param_1,2,1,(short *)&DAT_80435a00);
  if (*(short *)(param_1 + 1000) == 0xf01) {
    if ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) {
      *(undefined2 *)(param_1 + 0x146) = 1;
    }
    if (*(short *)(param_1 + 0x148) == 0) {
      *(undefined2 *)(param_1 + 0x148) = 0xc;
      *(short *)(param_1 + 0x14a) = *(short *)(param_1 + 0x14a) + 1;
      iVar3 = zz_006dbe0_(param_1,0,1,1);
      if (iVar3 != 0) {
        zz_0082824_(param_1,0x4a);
      }
      fVar1 = FLOAT_8043b95c;
      if (*(short *)(param_1 + 0x146) == 0) {
        if (0 < *(short *)(param_1 + 0x14a)) {
          *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
          *(float *)(param_1 + 0x558) = fVar1;
        }
      }
      else {
        *(undefined2 *)(param_1 + 0x146) = 0;
        fVar1 = FLOAT_8043b95c;
        if (4 < *(short *)(param_1 + 0x14a)) {
          *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
          *(float *)(param_1 + 0x558) = fVar1;
        }
      }
    }
    else {
      *(short *)(param_1 + 0x148) = *(short *)(param_1 + 0x148) + -1;
    }
  }
  else {
    iVar3 = zz_006dbe0_(param_1,0,1,1);
    if (iVar3 != 0) {
      if (*(short *)(param_1 + 1000) == 0xf02) {
        zz_00c3be0_(param_1,0x3d);
      }
      else {
        zz_016cc24_(param_1,0xb);
      }
    }
    fVar2 = FLOAT_8043b95c;
    fVar1 = FLOAT_8043b950;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x55c) = fVar1;
  }
  return;
}



// ==== 801b3990  zz_01b3990_ ====

void zz_01b3990_(int param_1)

{
  float fVar1;
  
  if (FLOAT_8043b954 < *(float *)(param_1 + 0x55c)) {
    FUN_8006cc90((double)FLOAT_8043b958,param_1,2,1,(short *)&DAT_80435a00);
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  fVar1 = FLOAT_8043b954;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  }
  return;
}



// ==== 801b3a24  zz_01b3a24_ ====

void zz_01b3a24_(void)

{
  int *piVar1;
  int iVar2;
  
  for (piVar1 = &DAT_80381140; -1 < *piVar1; piVar1 = piVar1 + 5) {
    iVar2 = zz_01a7538_(0xe,piVar1);
    if (iVar2 != 0) {
      *(code **)(iVar2 + 0xc) = zz_01b3aa4_;
      *(code **)(iVar2 + 0x10c) = zz_01b3c4c_;
    }
  }
  return;
}



// ==== 801b3aa4  zz_01b3aa4_ ====

void zz_01b3aa4_(int param_1)

{
  (*(code *)(&PTR_zz_01b3ae0__80381168)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801b3ae0  zz_01b3ae0_ ====

void zz_01b3ae0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  undefined8 uVar3;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  uVar2 = 1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar3 = zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043b960;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  uVar3 = zz_01a7688_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar2,
                      param_12,param_13,param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 6;
  zz_01b3b6c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
              uVar2,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801b3b6c  zz_01b3b6c_ ====

void zz_01b3b6c_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  float *pfVar1;
  double dVar2;
  undefined8 uVar3;
  
  dVar2 = zz_0045238_(*(short *)(param_9 + 0x7c));
  *(float *)(param_9 + 0x58) = (float)((double)FLOAT_8043b964 * dVar2 + (double)FLOAT_8043b960);
  dVar2 = zz_0045204_(*(short *)(param_9 + 0x7c));
  *(float *)(param_9 + 0x5c) = (float)((double)FLOAT_8043b964 * dVar2 + (double)FLOAT_8043b960);
  pfVar1 = (float *)(int)*(short *)(param_9 + 0x7c);
  *(short *)(param_9 + 0x7c) = *(short *)(param_9 + 0x7c) + 0x111;
  zz_01a7668_(param_9,0x78);
  dVar2 = DOUBLE_8043b970;
  uVar3 = zz_00086b8_((double)((float)((double)CONCAT44(0x43300000,
                                                        *(uint *)(param_9 + 0x170) ^ 0x80000000) -
                                      DOUBLE_8043b970) / FLOAT_8043b968),DOUBLE_8043b970,param_3,
                      param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x154),
                      *(int *)(param_9 + 0xe0),pfVar1,param_12,param_13,param_14,param_15,param_16);
  zz_0007c30_(uVar3,dVar2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe0),
              extraout_r4,pfVar1,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801b3c18  zz_01b3c18_ ====

void zz_01b3c18_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801b3c2c  zz_01b3c2c_ ====

void zz_01b3c2c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801b3c4c  zz_01b3c4c_ ====

void zz_01b3c4c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  zz_01a77e8_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801b3c6c  zz_01b3c6c_ ====

void zz_01b3c6c_(int param_1)

{
  *(undefined **)(param_1 + 0x4b4) = PTR_zz_01b4208__803814f0;
  *(undefined **)(param_1 + 0x4b8) = PTR_zz_01b4114__803814f4;
  *(undefined **)(param_1 + 0x4bc) = PTR_LAB_803814f8;
  *(undefined **)(param_1 + 0x4c0) = PTR_zz_01b4190__803814fc;
  *(undefined **)(param_1 + 0x4c4) = PTR_zz_01b41bc__80381500;
  *(undefined **)(param_1 + 0x4c8) = PTR_zz_01b41c0__80381504;
  *(undefined **)(param_1 + 0x4cc) = PTR_zz_01b41c4__80381508;
  *(undefined **)(param_1 + 0x4d0) = PTR_zz_01b41c8__8038150c;
  *(undefined **)(param_1 + 0x4d4) = PTR_zz_01b41e8__80381510;
  *(undefined4 *)(param_1 + 0x4d8) = DAT_80381514;
  *(undefined4 *)(param_1 + 0x4dc) = DAT_80381518;
  *(undefined **)(param_1 + 0x4e0) = PTR_zz_01b419c__8038151c;
  *(undefined **)(param_1 + 0x4e4) = PTR_FUN_80381520;
  *(undefined **)(param_1 + 0x4e8) = PTR_DAT_80381524;
  *(undefined **)(param_1 + 0x4ec) = PTR_PTR_80381528;
  *(undefined **)(param_1 + 0x4f0) = PTR_DAT_8038152c;
  *(undefined4 *)(param_1 + 0x4ac) = *(undefined4 *)(&DAT_803c4d94 + *(char *)(param_1 + 999) * 4);
  *(undefined **)(param_1 + 0x4b0) = &DAT_803811e0;
  *(undefined **)(param_1 + 0x1d80) = &DAT_80381b40;
  *(undefined **)(param_1 + 0x1d84) = &DAT_802bc080;
  *(undefined **)(param_1 + 0x1d88) = &DAT_803817c0;
  *(undefined **)(param_1 + 0x1d8c) = &DAT_802bae60;
  *(undefined **)(param_1 + 0x27c) = &DAT_80381448;
  return;
}



// ==== 801b3d68  zz_01b3d68_ ====

void zz_01b3d68_(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(300);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    FUN_800e4294(param_1,-0x7fc7ead0,2,puVar3 + 3,(float *)(puVar3 + 0x1b));
    FUN_800e4294(param_1,-0x7fc7ea70,2,puVar3 + 9,(float *)(puVar3 + 0x21));
    FUN_800e4294(param_1,-0x7fc7ea10,2,puVar3 + 0xf,(float *)(puVar3 + 0x27));
    FUN_800e4294(param_1,-0x7fc7e9b0,2,puVar3 + 0x15,(float *)(puVar3 + 0x2d));
  }
  return;
}



// ==== 801b3e3c  zz_01b3e3c_ ====

void zz_01b3e3c_(int param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  
  puVar2 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar2 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar2 = *(undefined4 *)(param_1 + 0x20);
    puVar2[1] = uVar1;
    puVar2[2] = *(undefined4 *)(param_1 + 0x28);
    if ((*(uint *)(param_1 + 0x5e0) & 0x20001000) == 0) {
      FUN_800e43e0(param_1,(float *)&DAT_80381530,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x1b),
                   (int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80381590,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x21),
                   (int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_803815f0,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x27)
                   ,(int *)0x0);
      FUN_800e43e0(param_1,(float *)&DAT_80381650,2,(float *)(puVar2 + 0x15),
                   (float *)(puVar2 + 0x2d),(int *)0x0);
    }
    else {
      FUN_800e4f9c(param_1,-0x7fc7ead0,2,(float *)(puVar2 + 3),(float *)(puVar2 + 0x33));
      FUN_800e4f9c(param_1,-0x7fc7ea70,2,(float *)(puVar2 + 9),(float *)(puVar2 + 0x39));
      FUN_800e4f9c(param_1,-0x7fc7ea10,2,(float *)(puVar2 + 0xf),(float *)(puVar2 + 0x3f));
      FUN_800e4f9c(param_1,-0x7fc7e9b0,2,(float *)(puVar2 + 0x15),(float *)(puVar2 + 0x45));
    }
  }
  return;
}



// ==== 801b3f94  zz_01b3f94_ ====

void zz_01b3f94_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 801b3fcc  zz_01b3fcc_ ====

void zz_01b3fcc_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fc7ead0,2,pfVar2 + 3,afStack_18);
    zz_00e4ec4_(param_1,-0x7fc7ea70,2,pfVar2 + 9,afStack_18);
    zz_00e4ec4_(param_1,-0x7fc7ea10,2,pfVar2 + 0xf,afStack_18);
    zz_00e4ec4_(param_1,-0x7fc7e9b0,2,pfVar2 + 0x15,afStack_18);
    zz_00e5184_(param_1,-0x7fc7ead0,2,pfVar2 + 3,pfVar2 + 0x33);
    zz_00e5184_(param_1,-0x7fc7ea70,2,pfVar2 + 9,pfVar2 + 0x39);
    zz_00e5184_(param_1,-0x7fc7ea10,2,pfVar2 + 0xf,pfVar2 + 0x3f);
    zz_00e5184_(param_1,-0x7fc7e9b0,2,pfVar2 + 0x15,pfVar2 + 0x45);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 801b4114  zz_01b4114_ ====

void zz_01b4114_(int param_1)

{
  short sVar1;
  
  zz_01b3d68_(param_1);
  sVar1 = *(short *)(param_1 + 1000);
  if (sVar1 == 0x90c) {
    zz_0162f78_(param_1,3);
  }
  else if ((sVar1 < 0x90c) && (sVar1 == 0x907)) {
    zz_0162f78_(param_1,1);
  }
  return;
}



// ==== 801b4190  zz_01b4190_ ====

void zz_01b4190_(int param_1)

{
  *(undefined1 *)(param_1 + 0x144) = *(undefined1 *)(param_1 + 0x6e8);
  return;
}



// ==== 801b419c  zz_01b419c_ ====

void zz_01b419c_(int param_1)

{
  zz_01b3e3c_(param_1);
  return;
}



// ==== 801b41bc  zz_01b41bc_ ====

void zz_01b41bc_(void)

{
  return;
}



// ==== 801b41c0  zz_01b41c0_ ====

void zz_01b41c0_(void)

{
  return;
}



// ==== 801b41c4  zz_01b41c4_ ====

void zz_01b41c4_(void)

{
  return;
}



// ==== 801b41c8  zz_01b41c8_ ====

void zz_01b41c8_(int param_1)

{
  zz_01b3f94_(param_1);
  return;
}



// ==== 801b41e8  zz_01b41e8_ ====

void zz_01b41e8_(int param_1)

{
  zz_01b3fcc_(param_1);
  return;
}



// ==== 801b4208  zz_01b4208_ ====

void zz_01b4208_(int param_1)

{
  (*(code *)(&PTR_zz_01b4244__803816b0)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801b4244  zz_01b4244_ ====

void zz_01b4244_(int param_1)

{
  (*(code *)(&PTR_zz_01b4280__803816bc)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801b4280  zz_01b4280_ ====

void zz_01b4280_(int param_1)

{
  *(short *)(param_1 + 0x1dfc) =
       (short)(int)(((double)CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x1dfc) ^ 0x80000000) -
                    DOUBLE_8043b980) * DOUBLE_8043b978);
  (*(code *)(&PTR_zz_01b42f4__803816d0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801b42f4  zz_01b42f4_ ====

void zz_01b42f4_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043b98c;
  fVar1 = FLOAT_8043b988;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  zz_006d0dc_(param_1,0xc1,0);
  return;
}



// ==== 801b433c  zz_01b433c_ ====

void zz_01b433c_(int param_1)

{
  int iVar1;
  double dVar2;
  
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = zz_006d0dc_(param_1,0xc1,0);
  if ((iVar1 != 1) && (FLOAT_8043b98c < *(float *)(param_1 + 0x558))) {
    return;
  }
  dVar2 = (double)FLOAT_8043b990;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,0xf,2,0,0xffffffff,0xffffffff);
  return;
}



// ==== 801b43c8  zz_01b43c8_ ====

void zz_01b43c8_(int param_1)

{
  short sVar1;
  int iVar2;
  
  zz_004cd24_(param_1,0xf);
  if ((*(char *)(param_1 + 0x1cef) == '\x01') && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x90c) {
        zz_0082824_(param_1,0x6d);
      }
      else if ((sVar1 < 0x90c) && (sVar1 == 0x907)) {
        zz_0082824_(param_1,0x6c);
      }
    }
  }
  return;
}



// ==== 801b4470  zz_01b4470_ ====

void zz_01b4470_(int param_1)

{
  int iVar1;
  
  iVar1 = zz_004cd24_(param_1,0xf);
  if (iVar1 == 1) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 801b44c4  zz_01b44c4_ ====

void zz_01b44c4_(int param_1)

{
  (*(code *)(&PTR_zz_01b4500__803816e0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801b4500  zz_01b4500_ ====

void zz_01b4500_(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043b994;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  zz_006dee8_(param_1,1);
  zz_004beb8_((double)FLOAT_8043b990,param_1,1,2,1,0xffffffff,0xffffffff);
  return;
}



// ==== 801b4564  zz_01b4564_ ====

void zz_01b4564_(int param_1)

{
  short sVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  iVar4 = zz_006dee8_(param_1,1);
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,1);
  }
  fVar3 = FLOAT_8043b98c;
  if (iVar4 < 0) {
    zz_006a3d0_(param_1,'\0',0,2);
  }
  else if ((((0 < iVar4) ||
            (fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
            *(float *)(param_1 + 0x558) = fVar2, fVar2 <= fVar3)) &&
           (*(char *)(param_1 + 0x1cef) == '\x01')) && (*(char *)(param_1 + 0x1cf0) == '\x01')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    iVar4 = zz_006dbe0_(param_1,0,1,1);
    if (iVar4 != 0) {
      sVar1 = *(short *)(param_1 + 1000);
      if (sVar1 == 0x90c) {
        zz_0082824_(param_1,0x6d);
      }
      else if ((sVar1 < 0x90c) && (sVar1 == 0x907)) {
        zz_0082824_(param_1,0x6c);
      }
    }
  }
  return;
}



// ==== 801b4674  zz_01b4674_ ====

void zz_01b4674_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  double dVar2;
  double dVar3;
  
  zz_004cd24_(param_9,1);
  dVar2 = DOUBLE_8043b980;
  if (*(char *)(param_9 + 0x1cee) != '\0') {
    dVar3 = (double)CONCAT44(0x43300000,(int)*(short *)(param_9 + 0x1dfc) ^ 0x80000000) -
            DOUBLE_8043b980;
    iVar1 = (int)(dVar3 * DOUBLE_8043b978);
    *(short *)(param_9 + 0x1dfc) = (short)iVar1;
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    zz_006a668_(dVar3,dVar2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x14,iVar1,
                param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



