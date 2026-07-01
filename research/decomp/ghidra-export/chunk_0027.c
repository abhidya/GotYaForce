// ==== 800f5dd4  FUN_800f5dd4 ====

void FUN_800f5dd4(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8031cbf8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800f5e28  FUN_800f5e28 ====

void FUN_800f5e28(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  float *pfVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
  iVar6 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar3 = *(char *)(param_9 + 0x13) * 0x10;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar5 = iVar3;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_80439150;
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_8031cbc8 + iVar3);
  uVar2 = *(undefined4 *)(&DAT_8031cbd0 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8031cbcc + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8031cbd4 + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar3 = zz_0006f98_(iVar6);
  pfVar4 = *(float **)(*(char *)(param_9 + 0x11) * 8 + -0x7fce3418 + *(char *)(param_9 + 0x13) * 4);
  iVar6 = iVar3 + 0xc28;
  zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0x600),
              *(int *)(param_9 + 0xe0),(int)pfVar4,iVar6,iVar5,in_r8,in_r9,in_r10);
  uVar7 = zz_00086b8_((double)FLOAT_80439154,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                      ,*(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),pfVar4,iVar6,iVar5,in_r8,
                      in_r9,in_r10);
  uVar7 = zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),extraout_r4,pfVar4,iVar6,iVar5,in_r8,in_r9,in_r10);
  iVar6 = iVar3 + 0xc28;
  pfVar4 = *(float **)(*(char *)(param_9 + 0x11) * 8 + -0x7fce3418 + *(char *)(param_9 + 0x13) * 4);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),(int)pfVar4,iVar6,iVar5,in_r8
                      ,in_r9,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4_00,pfVar4,iVar6,iVar5,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80439158,*(int *)(param_9 + 0xe4));
  uVar7 = zz_00086b8_((double)FLOAT_80439154,param_2,param_3,param_4,param_5,param_6,param_7,param_8
                      ,*(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),pfVar4,iVar6,iVar5,in_r8,
                      in_r9,in_r10);
  uVar7 = zz_0007c30_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe4),extraout_r4_01,pfVar4,iVar6,iVar5,in_r8,in_r9,in_r10)
  ;
  *(byte *)(param_9 + 0x82) = *(byte *)(param_9 + 0x96) + 0x41;
  zz_00f5fb8_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
              (uint)*(byte *)(param_9 + 0x96),pfVar4,iVar6,iVar5,in_r8,in_r9,in_r10);
  return;
}



// ==== 800f5fb8  zz_00f5fb8_ ====

void zz_00f5fb8_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  uVar1 = zz_0007c30_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),param_10,param_11,param_12,param_13,param_14,param_15
                      ,param_16);
  zz_0007c30_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 800f6008  FUN_800f6008 ====

void FUN_800f6008(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800f6028  FUN_800f6028 ====

void FUN_800f6028(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') &&
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) != '\x04')) {
    iVar2 = *(int *)(param_9 + 0xe0);
    uVar1 = 1;
  }
  else {
    iVar2 = *(int *)(param_9 + 0xe4);
    uVar1 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar2,uVar1);
  return;
}



// ==== 800f60a0  zz_00f60a0_ ====

bool zz_00f60a0_(int param_1,undefined1 param_2)

{
  short sVar1;
  bool bVar3;
  undefined1 *puVar2;
  int iVar4;
  
  sVar1 = *(short *)(param_1 + 1000);
  if (((sVar1 == 0x701) || (sVar1 == 0x70c)) || (sVar1 == 0x70d)) {
    iVar4 = 0;
    do {
      puVar2 = zz_0088aa0_(param_1,2,0,0,4);
      bVar3 = puVar2 != (undefined1 *)0x0;
      if (bVar3) {
        *puVar2 = 1;
        puVar2[0x13] = (char)iVar4;
        puVar2[0x11] = param_2;
        *(code **)(puVar2 + 0xc) = FUN_800f61e4;
        *(code **)(puVar2 + 0x10c) = FUN_800f6530;
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
      iVar4 = iVar4 + 1;
    } while (iVar4 < 2);
  }
  else {
    bVar3 = false;
  }
  return bVar3;
}



// ==== 800f61e4  FUN_800f61e4 ====

void FUN_800f61e4(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8031cc20)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800f6238  FUN_800f6238 ====

void FUN_800f6238(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar1;
  int iVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  char *pcVar3;
  int iVar4;
  undefined8 uVar5;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar4 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar5 = zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  pcVar3 = (char *)(*(char *)(param_9 + 0x11) * 8 + -0x7fce33f8 + *(char *)(param_9 + 0x13) * 4);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(pcVar3 + 2);
  iVar4 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe0),(int)*pcVar3,iVar4 + 0xc28,
                      in_r7,in_r8,in_r9,in_r10);
  if (-1 < pcVar3[1]) {
    uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe4),(int)pcVar3[1],
                        iVar4 + 0xc28,in_r7,in_r8,in_r9,in_r10);
  }
  iVar2 = iVar4 + 0xc28;
  iVar1 = (int)*pcVar3;
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xe8),iVar1,iVar2,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe8)
              ,extraout_r4,iVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
  uVar5 = zz_0007cac_((double)FLOAT_80439160,*(int *)(param_9 + 0xe8));
  if (-1 < pcVar3[1]) {
    iVar1 = (int)pcVar3[1];
    iVar2 = iVar4 + 0xc28;
    uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                        *(int *)(iVar4 + 0x600),*(int *)(param_9 + 0xec),iVar1,iVar2,in_r7,in_r8,
                        in_r9,in_r10);
    zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xec),extraout_r4_00,iVar1,iVar2,in_r7,in_r8,in_r9,in_r10);
    zz_0007cac_((double)FLOAT_80439160,*(int *)(param_9 + 0xec));
  }
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x74) = 0;
  if (*(char *)(param_9 + 0x11) == '\0') {
    *(int *)(param_9 + 0x54) = param_9;
    zz_01a470c_(param_9,0);
  }
  zz_00f63b4_(param_9);
  return;
}



// ==== 800f63b4  zz_00f63b4_ ====

void zz_00f63b4_(int param_1)

{
  short sVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(param_1 + 0x90);
  iVar4 = iVar3 + *(char *)(param_1 + 0x13) * 0xc;
  uVar2 = *(undefined4 *)(iVar4 + 0x178);
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(iVar4 + 0x174);
  *(undefined4 *)(param_1 + 0x24) = uVar2;
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(iVar4 + 0x17c);
  *(undefined2 *)(param_1 + 0x72) = *(undefined2 *)(iVar3 + *(char *)(param_1 + 0x13) * 2 + 0x18c);
  uVar2 = *(undefined4 *)(iVar3 + 0xb4);
  *(undefined4 *)(param_1 + 0x60) = uVar2;
  *(undefined4 *)(param_1 + 0x5c) = uVar2;
  *(undefined4 *)(param_1 + 0x58) = uVar2;
  *(undefined4 *)(param_1 + 0xb8) = uVar2;
  *(undefined4 *)(param_1 + 0xb4) = uVar2;
  *(short *)(param_1 + 0x144) = *(short *)(param_1 + 0x144) + 0x400;
  *(ushort *)(param_1 + 0x144) = *(ushort *)(param_1 + 0x144) & 0x1fff;
  iVar4 = iVar3 + *(char *)(param_1 + 0x13);
  if (*(char *)(iVar4 + 0x158) == '\x01') {
    sVar1 = *(short *)(iVar3 + 1000);
    if (sVar1 == 0x701) {
      *(undefined1 *)(iVar4 + 0x158) = 2;
      zz_0159ad0_(iVar3,param_1,*(char *)(param_1 + 0x11) * 0x100 + (int)*(char *)(param_1 + 0x13));
    }
    else if (sVar1 == 0x70c) {
      *(undefined1 *)(iVar4 + 0x158) = 2;
      zz_0159ad0_(iVar3,param_1,*(char *)(param_1 + 0x11) * 0x100 + (int)*(char *)(param_1 + 0x13));
    }
    else if (sVar1 == 0x70d) {
      *(undefined1 *)(iVar4 + 0x158) = 0;
      *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(iVar3 + 0xcc);
      *(undefined4 *)(param_1 + 200) = *(undefined4 *)(iVar3 + 200);
      *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(iVar3 + 0xd0);
      zz_00c3be0_(param_1,0x62);
    }
  }
  return;
}



// ==== 800f6510  FUN_800f6510 ====

void FUN_800f6510(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800f6530  FUN_800f6530 ====

void FUN_800f6530(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  float *pfVar3;
  uint uVar4;
  undefined8 uVar5;
  double dVar6;
  float afStack_48 [12];
  undefined4 local_18;
  uint uStack_14;
  
  iVar2 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar2 + *(char *)(param_9 + 0x13) + 0x158) == '\0') {
    if (*(char *)(iVar2 + 0xae) == '\0') {
      iVar1 = 0;
      if (*(char *)(iVar2 + 0x3ec) == '\x04') {
        uVar4 = 0x44;
      }
      else {
        uVar4 = 0x45;
      }
    }
    else {
      iVar1 = 2;
      uVar4 = 0x44;
    }
    iVar2 = *(int *)(param_9 + iVar1 * 4 + 0xe0);
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar2,uVar4);
    if (*(char *)(param_9 + 0x11) == '\0') {
      local_18 = 0x43300000;
      uStack_14 = (int)*(short *)(param_9 + 0x144) ^ 0x80000000;
      dVar6 = (double)FLOAT_80439164;
      gnt4_PSMTXRotRad_bl((double)(float)(dVar6 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                   uStack_14) -
                                                                 DOUBLE_80439168)),afStack_48,0x78);
      pfVar3 = afStack_48;
      uVar5 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar3,pfVar3);
      iVar2 = *(int *)(param_9 + iVar1 * 4 + 0xe4);
      zz_00076d0_(uVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,afStack_48,
                  (undefined *)pfVar3,param_12,param_13,param_14,param_15,param_16);
      zz_00097b4_(iVar2,uVar4);
    }
  }
  return;
}



// ==== 800f6654  zz_00f6654_ ====

void zz_00f6654_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,8);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x12;
    puVar1[0x13] = 8;
    *(code **)(puVar1 + 0xc) = FUN_800f674c;
    *(code **)(puVar1 + 0x10c) = FUN_800f6970;
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
  return;
}



// ==== 800f674c  FUN_800f674c ====

void FUN_800f674c(int param_1)

{
  (*(code *)(&PTR_FUN_8031cd24)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800f6788  FUN_800f6788 ====

void FUN_800f6788(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int *piVar2;
  undefined8 uVar3;
  
  uVar1 = *(char *)(param_9 + 0x13) * 0x60;
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
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined2 *)(param_9 + 0x1e) = 0;
    *(code **)(param_9 + 0x100) = FUN_800f69f4;
    uVar3 = zz_0089100_(param_9,1,1);
    zz_00f6b68_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 800f6850  FUN_800f6850 ====

void FUN_800f6850(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  short sVar3;
  int iVar4;
  double dVar5;
  
  dVar5 = (double)FLOAT_80439170;
  iVar4 = *(int *)(param_9 + 0x8c);
  fVar1 = *(float *)(iVar4 + 0xb4);
  *(float *)(param_9 + 0xb4) =
       (float)(dVar5 * (double)(float)((double)fVar1 * (double)*(float *)(iVar4 + 0x7fc)));
  uVar2 = *(undefined4 *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0x60) = uVar2;
  *(undefined4 *)(param_9 + 0x5c) = uVar2;
  *(undefined4 *)(param_9 + 0x58) = uVar2;
  sVar3 = *(short *)(param_9 + 0x1e);
  if (sVar3 == 0) {
    if ('\x01' < *(char *)(iVar4 + 0x18)) {
      *(undefined2 *)(param_9 + 0x1e) = 1;
    }
  }
  else if (sVar3 == 1) {
    if (*(char *)(iVar4 + 0x18) == '\x01') {
      *(undefined2 *)(param_9 + 0x1e) = 2;
    }
  }
  else if (sVar3 < 0x10) {
    *(short *)(param_9 + 0x1e) = sVar3 + 1;
  }
  iVar4 = zz_00f6cb4_((double)fVar1,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  if (iVar4 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 800f6928  FUN_800f6928 ====

void FUN_800f6928(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800f6970  FUN_800f6970 ====

void FUN_800f6970(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = 0;
  iVar3 = 0;
  iVar2 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar1) break;
    if (((int)*(short *)(param_9 + 0x1c) & 1 << iVar1) != 0) {
      zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar2 + 0xe0),(float *)(*(int *)(param_9 + 0x54) + iVar3),param_11,
                  param_12,param_13,param_14,param_15,param_16);
      param_1 = zz_00097b4_(*(int *)(iVar2 + 0xe0),0x44);
    }
    iVar3 = iVar3 + 0x60;
    iVar2 = iVar2 + 4;
    iVar1 = iVar1 + 1;
  }
  return;
}



// ==== 800f69f4  FUN_800f69f4 ====

void FUN_800f69f4(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  uint uVar4;
  float *pfVar5;
  int iVar6;
  int iVar7;
  float local_28;
  float local_24;
  float local_20;
  
  fVar1 = FLOAT_80439174;
  iVar7 = 0;
  iVar6 = 0;
  iVar3 = *(int *)(param_1 + 0x8c);
  uVar2 = *(undefined4 *)(iVar3 + 0x24);
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(iVar3 + 0x20);
  *(undefined4 *)(param_1 + 0x24) = uVar2;
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(iVar3 + 0x28);
  *(float *)(param_1 + 0x24) = fVar1 * *(float *)(param_1 + 0x5c) + *(float *)(param_1 + 0x24);
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar6) break;
    if (((int)*(short *)(param_1 + 0x1c) & 1 << iVar6) != 0) {
      pfVar5 = (float *)(*(int *)(param_1 + 0x54) + iVar7);
      gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                         (double)*(float *)(param_1 + 0x28),pfVar5);
      zz_00457d4_('z',pfVar5,pfVar5,*(short *)(pfVar5 + 0x15));
      zz_00457d4_('y',pfVar5,pfVar5,*(short *)((int)pfVar5 + 0x52));
      zz_00457d4_('x',pfVar5,pfVar5,*(short *)(pfVar5 + 0x14));
      uVar4 = countLeadingZeros(1 - (uint)*(ushort *)((int)pfVar5 + 0x56));
      gnt4_PSQUATScale_bl((double)*(float *)(&DAT_80434460 +
                                            (uVar4 >> 5 & *(short *)(pfVar5 + 0x16) + iVar6 & 1) * 4
                                            ),pfVar5 + 0x10,&local_28);
      local_28 = local_28 * *(float *)(param_1 + 0x58);
      local_24 = local_24 * *(float *)(param_1 + 0x5c);
      local_20 = local_20 * *(float *)(param_1 + 0x60);
      zz_00456a0_(pfVar5,pfVar5,&local_28);
    }
    iVar7 = iVar7 + 0x60;
    iVar6 = iVar6 + 1;
  }
  return;
}



// ==== 800f6b68  zz_00f6b68_ ====

void zz_00f6b68_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,ushort param_10)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  int iVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  
  iVar6 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar6) break;
    uVar3 = 1 << iVar6;
    if (((int)*(short *)(param_9 + 0x1c) & uVar3) == 0) {
      iVar4 = *(int *)(param_9 + 0x8c);
      uVar1 = (uint)param_10;
      iVar5 = *(int *)(param_9 + 0x54) + iVar6 * 0x60;
      *(ushort *)(iVar5 + 0x56) = param_10;
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)uVar3;
      *(undefined4 *)(iVar5 + 0x5c) = *(undefined4 *)(iVar4 + 0xb4);
      *(undefined2 *)(iVar5 + 0x58) = 0;
      *(undefined2 *)(iVar5 + 0x5a) = *(undefined2 *)(&DAT_8031cd02 + uVar1 * 0xc);
      if (*(short *)(iVar5 + 0x56) == 0) {
        *(undefined2 *)(iVar5 + 0x50) = 0;
        uVar2 = zz_00055fc_();
        *(short *)(iVar5 + 0x52) = (short)(uVar2 << 8);
        *(undefined2 *)(iVar5 + 0x54) = 0;
      }
      else {
        uVar2 = zz_00055fc_();
        *(short *)(iVar5 + 0x50) = (short)(uVar2 << 8);
        uVar2 = zz_00055fc_();
        *(short *)(iVar5 + 0x52) = (short)(uVar2 << 8);
        uVar2 = zz_00055fc_();
        *(short *)(iVar5 + 0x54) = (short)(uVar2 << 8);
      }
      zz_0018f88_((int *)(iVar5 + 0x30),(int)(&PTR_DAT_8031cd04)[uVar1 * 3],(float *)(iVar5 + 0x40))
      ;
      gnt4_PSQUATScale_bl((double)*(float *)(iVar5 + 0x5c),(float *)(iVar5 + 0x40),
                          (float *)(iVar5 + 0x40));
      uVar7 = zz_0019338_((int *)(iVar5 + 0x38),(int)(&PTR_DAT_8031cd08)[uVar1 * 3],
                          (float *)(iVar5 + 0x4c));
      zz_0006fb4_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                  *(int *)(param_9 + iVar6 * 4 + 0xe0),(int)*(short *)(&DAT_8031cd00 + uVar1 * 0xc),
                  uVar3,iVar4,in_r8,in_r9,in_r10);
      iVar6 = (int)*(char *)(param_9 + 0x13);
    }
    iVar6 = iVar6 + 1;
  }
  return;
}



// ==== 800f6cb4  zz_00f6cb4_ ====

int zz_00f6cb4_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9)

{
  ushort uVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  bool bVar7;
  
  iVar4 = 0;
  iVar6 = 0;
  iVar5 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar4) break;
    if (((int)*(short *)(param_9 + 0x1c) & 1 << iVar4) != 0) {
      iVar3 = *(int *)(param_9 + 0x54) + iVar6;
      sVar2 = *(short *)(iVar3 + 0x58) + 1;
      *(short *)(iVar3 + 0x58) = sVar2;
      uVar1 = (ushort)(1 << iVar4);
      if ((*(short *)(iVar3 + 0x5a) <= sVar2) && (*(short *)(iVar3 + 0x56) != 1)) {
        *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) & ~uVar1;
      }
      if (*(short *)(iVar3 + 0x56) == 0) {
        if (*(short *)(iVar3 + 0x58) == 5) {
          zz_00f6b68_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1);
        }
        *(short *)(iVar3 + 0x52) = *(short *)(iVar3 + 0x52) + 0xccc;
      }
      else if (*(short *)(iVar3 + 0x56) == 1) {
        if (*(short *)(param_9 + 0x1e) < 0x10) {
          if ((*(ushort *)(iVar3 + 0x58) & 1) == 0) {
            zz_00f6b68_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,2);
          }
        }
        else {
          param_2 = (double)*(float *)(iVar3 + 0x4c);
          bVar7 = (float)(param_2 - (double)FLOAT_80439178) < FLOAT_8043917c;
          *(float *)(iVar3 + 0x4c) = (float)(param_2 - (double)FLOAT_80439178);
          if (bVar7) {
            *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) & ~uVar1;
          }
        }
        *(short *)(iVar3 + 0x50) = *(short *)(iVar3 + 0x50) + 0x1111;
        *(short *)(iVar3 + 0x54) = *(short *)(iVar3 + 0x54) + 0x1111;
      }
      zz_0018fd8_((int *)(iVar3 + 0x30),(int)*(short *)(iVar3 + 0x58),(float *)(iVar3 + 0x40));
      gnt4_PSQUATScale_bl((double)*(float *)(iVar3 + 0x5c),(float *)(iVar3 + 0x40),
                          (float *)(iVar3 + 0x40));
      zz_0019370_((int *)(iVar3 + 0x38),(int)*(short *)(iVar3 + 0x58),(float *)(iVar3 + 0x4c));
      param_1 = zz_0007cac_((double)*(float *)(iVar3 + 0x4c),*(int *)(iVar5 + 0xe0));
    }
    iVar6 = iVar6 + 0x60;
    iVar5 = iVar5 + 4;
    iVar4 = iVar4 + 1;
  }
  return (int)*(short *)(param_9 + 0x1c);
}



// ==== 800f6e3c  zz_00f6e3c_ ====

void zz_00f6e3c_(undefined1 param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x3a,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x13;
    *(code **)(puVar1 + 0xc) = FUN_800f6eb8;
    *(undefined4 *)(puVar1 + 0x10c) = 0;
    puVar1[0x88] = param_1;
    puVar1[0x11] = param_2;
  }
  return;
}



// ==== 800f6eb8  FUN_800f6eb8 ====

void FUN_800f6eb8(int param_1)

{
  (*(code *)(&PTR_FUN_8031cd38)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 800f6ef4  FUN_800f6ef4 ====

void FUN_800f6ef4(int param_1)

{
  if (*(char *)(param_1 + 0x19) == '\0') {
    *(undefined1 *)(param_1 + 0x19) = 1;
    *(undefined2 *)(PTR_DAT_80433934 + 0xd6) = 2;
  }
  else {
    (**(code **)(&DAT_8031cd48 + *(char *)(param_1 + 0x11) * 4))();
    *(undefined1 *)(param_1 + 0x18) = 1;
  }
  return;
}



// ==== 800f6f68  FUN_800f6f68 ====

void FUN_800f6f68(int param_1)

{
  (**(code **)(&DAT_8031cd58 + *(char *)(param_1 + 0x11) * 4))();
  return;
}



// ==== 800f6fa4  FUN_800f6fa4 ====

void FUN_800f6fa4(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  zz_0040d64_(0,0);
  if ((PTR_DAT_80433934[*(char *)(param_1 + 0x88) * 0x3c + 0xf6] != '\0') &&
     ((PTR_DAT_80433934[0x51] == '\0' || (PTR_DAT_80433934[0x51] == '\x02')))) {
    zz_00dbda0_((int)*(char *)(param_1 + 0x88));
  }
  iVar4 = 0;
  for (iVar2 = 0; iVar2 < (char)(&DAT_80436264)[*(char *)(param_1 + 0x88)]; iVar2 = iVar2 + 1) {
    iVar3 = *(int *)((int)&DAT_803c6dec + iVar4 + *(char *)(param_1 + 0x88) * 0x18);
    if ((*(char *)(iVar3 + 0x18) == '\x01') &&
       ((PTR_DAT_80433934[0xda] & *(byte *)(iVar3 + 0x3e5)) != 0)) {
      zz_00b6510_(iVar3,0);
      iVar1 = *(char *)(*(int *)(iVar3 + 0x4b0) + 0xf) * 0x30;
      local_28 = *(undefined4 *)(iVar3 + iVar1 + 0x8e0);
      local_24 = *(undefined4 *)(iVar3 + iVar1 + 0x8f0);
      local_20 = *(undefined4 *)(iVar3 + iVar1 + 0x900);
      zz_00e7018_(iVar3,&local_28);
    }
    iVar4 = iVar4 + 4;
  }
  zz_00f70e0_(param_1);
  zz_00f0468_(0,0x79,0);
  return;
}



// ==== 800f70e0  zz_00f70e0_ ====

void zz_00f70e0_(int param_1)

{
  char cVar1;
  
  cVar1 = zz_008b290_();
  if (cVar1 == '\0') {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  else {
    *(undefined2 *)(PTR_DAT_80433934 + 0xd6) = 2;
  }
  return;
}



// ==== 800f712c  FUN_800f712c ====

void FUN_800f712c(int param_1)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 local_18;
  undefined4 local_14;
  undefined4 local_10;
  
  *(undefined2 *)(param_1 + 0x1c) = 0x96;
  zz_0040d64_(0,0);
  iVar3 = (int)(char)(&DAT_80436264)[*(char *)(param_1 + 0x88)];
  piVar2 = &DAT_803c6dec + *(char *)(param_1 + 0x88) * 6;
  if (0 < iVar3) {
    do {
      iVar1 = *piVar2;
      if ((*(char *)(iVar1 + 0x18) == '\x01') &&
         ((PTR_DAT_80433934[0xda] & *(byte *)(iVar1 + 0x3e5)) != 0)) {
        iVar3 = iVar1 + *(char *)(*(int *)(iVar1 + 0x4b0) + 0xf) * 0x30;
        local_18 = *(undefined4 *)(iVar3 + 0x8e0);
        local_14 = *(undefined4 *)(iVar3 + 0x8f0);
        local_10 = *(undefined4 *)(iVar3 + 0x900);
        zz_00e7018_(iVar1,&local_18);
        break;
      }
      piVar2 = piVar2 + 1;
      iVar3 = iVar3 + -1;
    } while (iVar3 != 0);
  }
  zz_00f70e0_(param_1);
  zz_00f0468_(0,0x79,0);
  return;
}



// ==== 800f7248  FUN_800f7248 ====

void FUN_800f7248(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  *(undefined2 *)(param_1 + 0x1c) = 0;
  if (PTR_DAT_80433930[0x32] == '\0') {
    if ((PTR_DAT_80433934[*(char *)(param_1 + 0x88) * 0x3c + 0xf6] != '\0') &&
       ((PTR_DAT_80433934[0x51] == '\0' || (PTR_DAT_80433934[0x51] == '\x02')))) {
      *(undefined2 *)(param_1 + 0x1c) = 0x3c;
      zz_00dbda0_((int)*(char *)(param_1 + 0x88));
    }
  }
  iVar4 = 0;
  for (iVar3 = 0; iVar3 < (char)(&DAT_80436264)[*(char *)(param_1 + 0x88)]; iVar3 = iVar3 + 1) {
    iVar1 = *(int *)((int)&DAT_803c6dec + iVar4 + *(char *)(param_1 + 0x88) * 0x18);
    if ((*(char *)(iVar1 + 0x18) == '\x01') &&
       ((PTR_DAT_80433934[0xda] & *(byte *)(iVar1 + 0x3e5)) != 0)) {
      iVar2 = *(char *)(*(int *)(iVar1 + 0x4b0) + 0xf) * 0x30;
      local_28 = *(undefined4 *)(iVar1 + iVar2 + 0x8e0);
      local_24 = *(undefined4 *)(iVar1 + iVar2 + 0x8f0);
      local_20 = *(undefined4 *)(iVar1 + iVar2 + 0x900);
      zz_00e7018_(iVar1,&local_28);
    }
    iVar4 = iVar4 + 4;
  }
  zz_00f73a8_(param_1);
  zz_00f0468_(0,0x79,0);
  return;
}



// ==== 800f73a8  zz_00f73a8_ ====

void zz_00f73a8_(int param_1)

{
  char cVar1;
  short sVar3;
  int iVar2;
  int iVar4;
  int iVar5;
  
  *(undefined2 *)(PTR_DAT_80433934 + 0xd6) = 2;
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      if ('\x02' < cVar1) {
        return;
      }
      goto LAB_800f7518;
    }
    if (cVar1 < '\0') {
      return;
    }
    sVar3 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar3;
    if (0 < sVar3) {
      return;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
    iVar4 = 0;
    *(undefined2 *)(param_1 + 0x1c) = 0x19;
    for (iVar5 = 0; iVar5 < (char)(&DAT_80436264)[*(char *)(param_1 + 0x88)]; iVar5 = iVar5 + 1) {
      iVar2 = *(int *)((int)&DAT_803c6dec + iVar4 + *(char *)(param_1 + 0x88) * 0x18);
      if ((PTR_DAT_80433934[0xda] & *(byte *)(iVar2 + 0x3e5)) != 0) {
        zz_00b6510_(iVar2,0);
        zz_00107a0_(iVar2,0xf);
      }
      iVar4 = iVar4 + 4;
    }
  }
  sVar3 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar3;
  if (0 < sVar3) {
    return;
  }
  iVar4 = 0;
  *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  *(undefined2 *)(param_1 + 0x1c) = 0x23;
  for (iVar5 = 0; iVar5 < (char)(&DAT_80436264)[*(char *)(param_1 + 0x88)]; iVar5 = iVar5 + 1) {
    iVar2 = *(int *)((int)&DAT_803c6dec + iVar4 + *(char *)(param_1 + 0x88) * 0x18);
    if ((PTR_DAT_80433934[0xda] & *(byte *)(iVar2 + 0x3e5)) != 0) {
      zz_00def38_(iVar2);
    }
    iVar4 = iVar4 + 4;
  }
LAB_800f7518:
  sVar3 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar3;
  if (sVar3 < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined2 *)(PTR_DAT_80433934 + 0xd6) = 1;
  }
  return;
}



// ==== 800f7560  FUN_800f7560 ====

void FUN_800f7560(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800f7740  FUN_800f7740 ====

void FUN_800f7740(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0xd00) {
    *(undefined1 *)(param_1 + 0x144) = 0;
    *(undefined1 *)(param_1 + 0x145) = 0;
    *(undefined1 *)(param_1 + 0x146) = 0;
    *(undefined1 *)(param_1 + 0x147) = 0;
    *(undefined1 *)(param_1 + 0x148) = 0;
    zz_00f902c_(param_1);
  }
  else if (*(short *)(param_1 + 1000) == 0xd04) {
    *(undefined1 *)(param_1 + 0x152) = 0;
    *(undefined1 *)(param_1 + 0x153) = 0;
    *(undefined1 *)(param_1 + 0x151) = 0;
    zz_00f846c_(param_1,1);
  }
  *(float *)(param_1 + 0x1dc0) = FLOAT_80439180;
  zz_00c74ec_(param_1,0x34);
  return;
}



// ==== 800f77c8  FUN_800f77c8 ====

void FUN_800f77c8(int param_1)

{
  if (*(short *)(param_1 + 0x79e) <= *(short *)(param_1 + 0x784)) {
    if (*(short *)(param_1 + 1000) == 0xd00) {
      *(undefined1 *)(param_1 + 0x144) = 0;
      *(undefined1 *)(param_1 + 0x145) = 0;
      *(undefined1 *)(param_1 + 0x146) = 0;
      *(undefined1 *)(param_1 + 0x147) = 0;
      *(undefined1 *)(param_1 + 0x148) = 0;
    }
    else if (*(short *)(param_1 + 1000) == 0xd04) {
      *(undefined1 *)(param_1 + 0x152) = 0;
      *(undefined1 *)(param_1 + 0x153) = 0;
      *(undefined1 *)(param_1 + 0x154) = 0;
      *(undefined1 *)(param_1 + 0x155) = 0;
      *(undefined1 *)(param_1 + 0x151) = 0;
    }
  }
  if ((*(byte *)(param_1 + 0x7d2) & 1) != 0) {
    if (((*(byte *)(param_1 + 0x7d2) & 2) == 0) && (*(char *)(param_1 + 0x150) == '\0')) {
      if (*(short *)(param_1 + 1000) == 0xd00) {
        zz_011a6d0_(param_1,0);
      }
      else if (*(short *)(param_1 + 1000) == 0xd04) {
        zz_011a6d0_(param_1,1);
      }
    }
  }
  return;
}



// ==== 800f789c  FUN_800f789c ====

void FUN_800f789c(int param_1)

{
  (*(code *)(&PTR_FUN_8031d120)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800f78d8  FUN_800f78d8 ====

void FUN_800f78d8(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  if ((*(short *)(param_1 + 1000) == 0xd00) || (*(short *)(param_1 + 1000) == 0xd04)) {
    (*(code *)(&PTR_LAB_8031d130)[*(char *)(param_1 + 0x540)])(param_1);
    dVar4 = DOUBLE_80439190;
    fVar3 = FLOAT_8043918c;
    fVar2 = FLOAT_80439188;
    fVar1 = FLOAT_80439184;
    *(short *)(param_1 + 0x1922) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1922) ^ 0x80000000) -
                             DOUBLE_80439190) *
                     (FLOAT_80439188 * (FLOAT_8043918c - *(float *)(param_1 + 0x1dc8)) +
                     FLOAT_80439184));
    *(short *)(param_1 + 0x1924) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1924) ^ 0x80000000) -
                             dVar4) * (fVar2 * (fVar3 - *(float *)(param_1 + 0x1dc8)) + fVar1));
  }
  else {
    zz_006a53c_(param_1,10);
  }
  return;
}



// ==== 800f79f4  FUN_800f79f4 ====

void FUN_800f79f4(int param_1)

{
  int iVar1;
  double dVar2;
  
  if ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x14a) = 1;
  }
  dVar2 = (double)FLOAT_8043919c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = FUN_8006cc90(dVar2,param_1,0xc,1,(short *)&DAT_80434468);
  if ((iVar1 == 0) && (FLOAT_804391a0 < *(float *)(param_1 + 0x558))) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 800f7a80  FUN_800f7a80 ====

void FUN_800f7a80(int param_1)

{
  float fVar1;
  int iVar2;
  
  if ((*(uint *)(param_1 + 0x5bc) & 0x200) != 0) {
    *(undefined2 *)(param_1 + 0x14a) = 1;
  }
  if (*(short *)(param_1 + 0x14c) == 0) {
    *(undefined2 *)(param_1 + 0x14c) = 10;
    *(short *)(param_1 + 0x14e) = *(short *)(param_1 + 0x14e) + 1;
    iVar2 = zz_006dbe0_(param_1,0,1,1);
    if (iVar2 != 0) {
      if (*(short *)(param_1 + 1000) == 0xd00) {
        zz_0082824_(param_1,(int)*(char *)(param_1 + 0x149) + 0xe);
      }
      else {
        zz_0082824_(param_1,(int)*(char *)(param_1 + 0x149) + 0x42);
      }
      *(char *)(param_1 + 0x149) = *(char *)(param_1 + 0x149) + '\x01';
      *(byte *)(param_1 + 0x149) = *(byte *)(param_1 + 0x149) & 1;
    }
    fVar1 = FLOAT_804391a4;
    if (*(short *)(param_1 + 0x14a) == 0) {
      if (0 < *(short *)(param_1 + 0x14e)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar1;
      }
    }
    else {
      *(undefined2 *)(param_1 + 0x14a) = 0;
      fVar1 = FLOAT_804391a4;
      if (9 < *(short *)(param_1 + 0x14e)) {
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
        *(float *)(param_1 + 0x558) = fVar1;
      }
    }
  }
  else {
    *(short *)(param_1 + 0x14c) = *(short *)(param_1 + 0x14c) + -1;
  }
  return;
}



// ==== 800f7bac  FUN_800f7bac ====

void FUN_800f7bac(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804391a0;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 800f7bf4  FUN_800f7bf4 ====

void FUN_800f7bf4(int param_1)

{
  float fVar1;
  double dVar2;
  
  if (*(short *)(param_1 + 1000) == 0xd00) {
    (*(code *)(&PTR_LAB_8031d140)[*(char *)(param_1 + 0x540)])();
    dVar2 = DOUBLE_80439190;
    fVar1 = FLOAT_80439184;
    *(short *)(param_1 + 0x1922) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1922) ^ 0x80000000) -
                             DOUBLE_80439190) * FLOAT_80439184);
    *(short *)(param_1 + 0x1924) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x1924) ^ 0x80000000) -
                             dVar2) * fVar1);
  }
  else {
    zz_006a53c_(param_1,10);
  }
  return;
}



// ==== 800f7cd0  FUN_800f7cd0 ====

void FUN_800f7cd0(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_804391a4;
  if (*(short *)(param_1 + 1000) == 0xd00) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    iVar2 = zz_006dbe0_(param_1,2,1,1);
    if (iVar2 != 0) {
      *(undefined1 *)(param_1 + *(char *)(param_1 + 0x148) + 0x144) = 1;
      zz_00f9400_(param_1,*(undefined1 *)(param_1 + 0x148));
      *(char *)(param_1 + 0x148) = *(char *)(param_1 + 0x148) + '\x01';
      *(byte *)(param_1 + 0x148) = *(byte *)(param_1 + 0x148) & 3;
    }
  }
  else {
    zz_006a53c_(param_1,10);
  }
  return;
}



// ==== 800f7d78  FUN_800f7d78 ====

void FUN_800f7d78(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804391a0;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 800f7dc0  FUN_800f7dc0 ====

void FUN_800f7dc0(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  (*(code *)(&PTR_LAB_8031d14c)[*(char *)(param_1 + 0x540)])();
  dVar4 = DOUBLE_80439190;
  fVar3 = FLOAT_8043918c;
  fVar2 = FLOAT_80439188;
  fVar1 = FLOAT_80439184;
  *(short *)(param_1 + 0x1922) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1922) ^ 0x80000000) -
                           DOUBLE_80439190) *
                   (FLOAT_80439188 * (FLOAT_8043918c - *(float *)(param_1 + 0x1dc8)) +
                   FLOAT_80439184));
  *(short *)(param_1 + 0x1924) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1924) ^ 0x80000000) - dVar4
                           ) * (fVar2 * (fVar3 - *(float *)(param_1 + 0x1dc8)) + fVar1));
  return;
}



// ==== 800f7ea4  FUN_800f7ea4 ====

void FUN_800f7ea4(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_804391a4;
  if (*(short *)(param_1 + 1000) == 0xd04) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    iVar2 = zz_006dbe0_(param_1,2,1,1);
    if (iVar2 != 0) {
      *(undefined1 *)(param_1 + *(char *)(param_1 + 0x151) + 0x152) = 1;
      zz_00fcd38_(param_1,2,*(undefined1 *)(param_1 + 0x151));
      *(char *)(param_1 + 0x151) = *(char *)(param_1 + 0x151) + '\x01';
      *(byte *)(param_1 + 0x151) = *(byte *)(param_1 + 0x151) & 1;
    }
  }
  else {
    zz_006a53c_(param_1,10);
  }
  return;
}



// ==== 800f7f50  FUN_800f7f50 ====

void FUN_800f7f50(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804391a0;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 800f7f98  FUN_800f7f98 ====

void FUN_800f7f98(int param_1)

{
  if ((*(short *)(param_1 + 1000) == 0xd00) || (*(short *)(param_1 + 1000) == 0xd04)) {
    (*(code *)(&PTR_LAB_8031d158)[*(char *)(param_1 + 0x540)])();
  }
  else {
    zz_006a53c_(param_1,10);
  }
  return;
}



// ==== 800f800c  FUN_800f800c ====

void FUN_800f800c(int param_1)

{
  int iVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_8043919c;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar1 = FUN_8006cc90(dVar2,param_1,0xd,1,
                       (short *)(((0xd00U - (int)*(short *)(param_1 + 1000) |
                                  (int)*(short *)(param_1 + 1000) - 0xd00U) >> 0x1c & 8) +
                                0x8031d168));
  if ((iVar1 == 0) && (FLOAT_804391a0 < *(float *)(param_1 + 0x558))) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  return;
}



// ==== 800f809c  FUN_800f809c ====

void FUN_800f809c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804391a4;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  if (*(short *)(param_1 + 1000) == 0xd00) {
    zz_00c3be0_(param_1,0x14);
  }
  else {
    zz_00c3be0_(param_1,0x38);
  }
  return;
}



// ==== 800f80ec  FUN_800f80ec ====

void FUN_800f80ec(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_804391a0;
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    zz_006a53c_(param_1,0);
  }
  return;
}



// ==== 800f8134  zz_00f8134_ ====

bool zz_00f8134_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = 0;
    *(code **)(puVar1 + 0xc) = FUN_800f8230;
    *(code **)(puVar1 + 0x10c) = FUN_800f83e0;
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
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800f8230  FUN_800f8230 ====

void FUN_800f8230(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8031d190)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800f8284  FUN_800f8284 ====

void FUN_800f8284(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  fVar1 = FLOAT_804391a8;
  iVar3 = *(char *)(param_9 + 0x13) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_8031d180 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8031d17c + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8031d184 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_8031d188 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8031d18c + iVar3);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_8031d17a + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_8031d178 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_8031d178 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804391ac,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00f83b0_();
  return;
}



// ==== 800f83b0  zz_00f83b0_ ====

void zz_00f83b0_(void)

{
  return;
}



// ==== 800f83c0  FUN_800f83c0 ====

void FUN_800f83c0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800f83e0  FUN_800f83e0 ====

void FUN_800f83e0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + 0x14a) == '\0') {
    if (*(char *)(iVar1 + 0xae) == '\0') {
      iVar2 = *(int *)(param_9 + 0xe0);
      if (*(char *)(iVar1 + 0x3ec) == '\x04') {
        uVar3 = 0x44;
      }
      else {
        uVar3 = 1;
      }
    }
    else {
      iVar2 = *(int *)(param_9 + 0xe4);
      uVar3 = 0x44;
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar2,uVar3);
  }
  return;
}



// ==== 800f846c  zz_00f846c_ ====

bool zz_00f846c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    puVar1 = zz_0088aa0_(param_1,2,0,0,2);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x13] = (char)iVar2;
      puVar1[0x11] = param_2;
      *(code **)(puVar1 + 0xc) = FUN_800f858c;
      *(code **)(puVar1 + 0x10c) = FUN_800f881c;
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
    iVar2 = iVar2 + 1;
  } while (iVar2 < 2);
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800f858c  FUN_800f858c ====

void FUN_800f858c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8031d200)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800f85e0  FUN_800f85e0 ====

void FUN_800f85e0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  int iVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar5;
  int iVar6;
  undefined8 uVar7;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar6 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  fVar1 = FLOAT_804391b0;
  psVar5 = (short *)(*(char *)(param_9 + 0x11) * 0x30 + -0x7fce2e60 +
                    *(char *)(param_9 + 0x13) * 0x18);
  uVar2 = *(undefined4 *)(psVar5 + 4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(psVar5 + 2);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(psVar5 + 6);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(psVar5 + 8);
  *(short *)(param_9 + 0x74) = psVar5[10];
  *(char *)(param_9 + 0x89) = (char)psVar5[1];
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar6 = zz_0006f98_(iVar6);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe0),(int)*psVar5,iVar6 + 0xc28,
                      in_r7,in_r8,in_r9,in_r10);
  iVar4 = iVar6 + 0xc28;
  iVar3 = (int)*psVar5;
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar6 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804391b4,*(int *)(param_9 + 0xe4));
  zz_00f8710_(param_9);
  return;
}



// ==== 800f8710  zz_00f8710_ ====

void zz_00f8710_(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  
  fVar3 = FLOAT_804391b8;
  fVar2 = FLOAT_804391b0;
  cVar1 = *(char *)(param_1 + 0x11);
  if (cVar1 == '\x01') {
    uVar4 = countLeadingZeros((int)*(char *)(*(int *)(param_1 + 0x90) +
                                             (int)*(char *)(param_1 + 0x13) + 0x152));
    uVar4 = uVar4 >> 5;
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    uVar4 = countLeadingZeros((int)*(char *)(*(int *)(param_1 + 0x90) +
                                             (int)*(char *)(param_1 + 0x13) + 0x146));
    uVar4 = uVar4 >> 5;
  }
  else {
    uVar4 = 0;
  }
  if (uVar4 == 0) {
    *(float *)(param_1 + 0x58) = FLOAT_804391b8;
    *(float *)(param_1 + 0x5c) = fVar3;
    *(float *)(param_1 + 0x60) = fVar3;
    *(undefined1 *)(param_1 + 0x82) = 0;
    return;
  }
  if (FLOAT_804391b0 <= *(float *)(param_1 + 0x58)) {
    *(float *)(param_1 + 0x58) = FLOAT_804391b0;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x60) = fVar2;
  }
  else {
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + FLOAT_804391b8;
    *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + fVar3;
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + fVar3;
  }
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
  return;
}



// ==== 800f87fc  FUN_800f87fc ====

void FUN_800f87fc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800f881c  FUN_800f881c ====

void FUN_800f881c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar1 = *(int *)(param_9 + 0xe0);
    if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
      uVar2 = 0x44;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
    uVar2 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,uVar2);
  return;
}



// ==== 800f889c  zz_00f889c_ ====

bool zz_00f889c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_800f89ac;
    *(code **)(puVar1 + 0x10c) = FUN_800f8bd8;
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
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800f89ac  FUN_800f89ac ====

void FUN_800f89ac(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8031d240)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800f8a00  FUN_800f8a00 ====

void FUN_800f8a00(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  fVar1 = FLOAT_804391c0;
  iVar3 = *(char *)(param_9 + 0x11) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_8031d218 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8031d214 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8031d21c + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_8031d220 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8031d224 + iVar3);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_8031d212 + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_8031d210 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_8031d210 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804391c4,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00f8b2c_(param_9);
  return;
}



// ==== 800f8b2c  zz_00f8b2c_ ====

void zz_00f8b2c_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_804391c8;
  fVar1 = FLOAT_804391c0;
  if (*(char *)(*(int *)(param_1 + 0x90) + 0x145) == '\0') {
    if (FLOAT_804391c0 <= *(float *)(param_1 + 0x58)) {
      *(float *)(param_1 + 0x58) = FLOAT_804391c0;
      *(float *)(param_1 + 0x5c) = fVar1;
      *(float *)(param_1 + 0x60) = fVar1;
    }
    else {
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + FLOAT_804391c8;
      *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + fVar2;
      *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + fVar2;
    }
    *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
    return;
  }
  *(float *)(param_1 + 0x58) = FLOAT_804391c8;
  *(float *)(param_1 + 0x5c) = fVar2;
  *(float *)(param_1 + 0x60) = fVar2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800f8bb8  FUN_800f8bb8 ====

void FUN_800f8bb8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800f8bd8  FUN_800f8bd8 ====

void FUN_800f8bd8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar1 = *(int *)(param_9 + 0xe0);
    if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
      uVar2 = 0x44;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
    uVar2 = 0x44;
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,uVar2);
  return;
}



// ==== 800f8c58  zz_00f8c58_ ====

bool zz_00f8c58_(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    puVar1 = zz_0088aa0_(param_1,2,0,0,2);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x13] = (char)iVar2;
      puVar1[0x11] = 0;
      *(code **)(puVar1 + 0xc) = FUN_800f8d70;
      *(code **)(puVar1 + 0x10c) = FUN_800f8f94;
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
    iVar2 = iVar2 + 1;
  } while (iVar2 < 2);
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800f8d70  FUN_800f8d70 ====

void FUN_800f8d70(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8031d280)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800f8dc4  FUN_800f8dc4 ====

void FUN_800f8dc4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  fVar1 = FLOAT_804391d0;
  iVar3 = *(char *)(param_9 + 0x13) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_8031d258 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8031d254 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8031d25c + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_8031d260 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8031d264 + iVar3);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_8031d252 + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_8031d250 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_8031d250 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804391d4,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00f8ef0_(param_9);
  return;
}



// ==== 800f8ef0  zz_00f8ef0_ ====

void zz_00f8ef0_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_804391d8;
  fVar1 = FLOAT_804391d0;
  if (*(char *)(*(int *)(param_1 + 0x90) + (int)*(char *)(param_1 + 0x13) + 0x148) != '\0') {
    *(float *)(param_1 + 0x58) = FLOAT_804391d8;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x60) = fVar2;
    return;
  }
  if (*(float *)(param_1 + 0x58) < FLOAT_804391d0) {
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + FLOAT_804391d8;
    *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + fVar2;
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + fVar2;
    return;
  }
  *(float *)(param_1 + 0x58) = FLOAT_804391d0;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x60) = fVar1;
  return;
}



// ==== 800f8f74  FUN_800f8f74 ====

void FUN_800f8f74(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800f8f94  FUN_800f8f94 ====

void FUN_800f8f94(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined *param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + (char)param_9[0x13] + 0x148) == '\0') {
    if (*(char *)(iVar1 + 0xae) == '\0') {
      iVar2 = *(int *)(param_9 + 0xe0);
      if (*(char *)(iVar1 + 0x3ec) == '\x04') {
        uVar3 = 0x44;
      }
      else {
        uVar3 = 1;
      }
    }
    else {
      iVar2 = *(int *)(param_9 + 0xe4);
      uVar3 = 0x44;
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                (float *)(param_9 + 0x114),param_9,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar2,uVar3);
  }
  return;
}



// ==== 800f902c  zz_00f902c_ ====

bool zz_00f902c_(int param_1)

{
  undefined1 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  do {
    puVar1 = zz_0088aa0_(param_1,2,0,0,2);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x13] = (char)iVar2;
      puVar1[0x11] = 0;
      *(code **)(puVar1 + 0xc) = FUN_800f9144;
      *(code **)(puVar1 + 0x10c) = FUN_800f9368;
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
    iVar2 = iVar2 + 1;
  } while (iVar2 < 4);
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800f9144  FUN_800f9144 ====

void FUN_800f9144(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8031d2f0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800f9198  FUN_800f9198 ====

void FUN_800f9198(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  undefined8 uVar6;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar6 = zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x5f;
  fVar1 = FLOAT_804391e0;
  iVar3 = *(char *)(param_9 + 0x13) * 0x18;
  uVar2 = *(undefined4 *)(&DAT_8031d298 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8031d294 + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8031d29c + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_8031d2a0 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_8031d2a4 + iVar3);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_8031d292 + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar5 = zz_0006f98_(iVar5);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_8031d290 + iVar3),iVar5 + 0xc28,in_r7,in_r8,in_r9,in_r10)
  ;
  iVar4 = iVar5 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_8031d290 + iVar3);
  uVar6 = zz_0007030_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804391e4,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00f92c4_(param_9);
  return;
}



// ==== 800f92c4  zz_00f92c4_ ====

void zz_00f92c4_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_804391e8;
  fVar1 = FLOAT_804391e0;
  if (*(char *)(*(int *)(param_1 + 0x90) + (int)*(char *)(param_1 + 0x13) + 0x144) != '\0') {
    *(float *)(param_1 + 0x58) = FLOAT_804391e8;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x60) = fVar2;
    return;
  }
  if (*(float *)(param_1 + 0x58) < FLOAT_804391e0) {
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + FLOAT_804391e8;
    *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + fVar2;
    *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + fVar2;
    return;
  }
  *(float *)(param_1 + 0x58) = FLOAT_804391e0;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x60) = fVar1;
  return;
}



// ==== 800f9348  FUN_800f9348 ====

void FUN_800f9348(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800f9368  FUN_800f9368 ====

void FUN_800f9368(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined *param_9,undefined4 param_10
                 ,undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  
  iVar1 = *(int *)(param_9 + 0x90);
  if (*(char *)(iVar1 + (char)param_9[0x13] + 0x144) == '\0') {
    if (*(char *)(iVar1 + 0xae) == '\0') {
      iVar2 = *(int *)(param_9 + 0xe0);
      if (*(char *)(iVar1 + 0x3ec) == '\x04') {
        uVar3 = 0x44;
      }
      else {
        uVar3 = 1;
      }
    }
    else {
      iVar2 = *(int *)(param_9 + 0xe4);
      uVar3 = 0x44;
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                (float *)(param_9 + 0x114),param_9,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar2,uVar3);
  }
  return;
}



// ==== 800f9400  zz_00f9400_ ====

bool zz_00f9400_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x11] = 0;
    puVar1[0x10] = 0x4a;
    *(code **)(puVar1 + 0xc) = FUN_800f9518;
    *(code **)(puVar1 + 0x10c) = FUN_800f99cc;
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
    zz_00f036c_(param_1,7);
  }
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800f9518  FUN_800f9518 ====

void FUN_800f9518(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8031d37c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800f95b0  FUN_800f95b0 ====

void FUN_800f95b0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  undefined8 uVar9;
  
  puVar7 = &DAT_8031d360;
  puVar5 = &DAT_8031d300;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar8 = *(int *)(param_9 + 0x90);
  iVar6 = (int)*(char *)(param_9 + 0x13);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar3 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  *(undefined1 *)(param_9 + 0x98) = 5;
  iVar2 = iVar6 * 0x18;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar1 = iVar2;
  iVar4 = iVar3;
  zz_0089100_(param_9,0,1);
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_8031d302 + iVar2) * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_8031d302 + iVar2) * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_8031d302 + iVar2) * 0x30 + 0x8f8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar8 + *(short *)(&DAT_8031d302 + iVar2) * 0x30 + 0x8d4),
             (float *)(iVar2 + -0x7fce2cfc),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_8031d302 + iVar2) * 0x30 + 0x8dc);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_8031d302 + iVar2) * 0x30 + 0x8ec);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)(iVar8 + *(short *)(&DAT_8031d302 + iVar2) * 0x30 + 0x8fc);
  uVar9 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8031d370 + iVar3),(float *)(param_9 + 0x38),
                              (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8031d370 + iVar3);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8031d362 + iVar3);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8031d364 + iVar3);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_8031d366 + iVar3);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(&DAT_8031d374 + iVar3);
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  iVar2 = zz_0006f98_(iVar8);
  zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar2 + 0x600),
              *(int *)(param_9 + 0xe0),1,iVar1,iVar4,puVar5,iVar6,puVar7);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar1 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8031d360 + iVar3));
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0xa8) = 1;
    zz_00c74ec_(param_9,0x4f);
  }
  return;
}



// ==== 800f97ac  FUN_800f97ac ====

void FUN_800f97ac(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_00f9964_(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        if (*(short *)(param_1 + 0x1c) < 1) {
          zz_00f9964_(param_1);
          FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
        }
        else {
          if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x144)) {
            *(float *)(param_1 + 0x44) =
                 *(float *)(param_1 + 0x44) + *(float *)(&DAT_8031d378 + iVar1);
          }
          else {
            *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x144);
          }
          gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
          gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                              (float *)(param_1 + 0x38));
          FUN_80083874((double)*(float *)(&DAT_8031d36c + iVar1),param_1);
          FUN_80083ad4((double)*(float *)(&DAT_8031d368 + iVar1),param_1,
                       (char)*(undefined2 *)(&DAT_8031d364 + iVar1));
          *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
          zz_00833ec_(param_1);
          zz_0083610_(param_1,(float *)(param_1 + 0x144));
          iVar1 = zz_0083714_(param_1);
          if (iVar1 == 0) {
            iVar1 = zz_0084170_(param_1);
            if (iVar1 != 0) {
              zz_00f9964_(param_1);
              zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),6);
            }
          }
          else {
            zz_00f9964_(param_1);
          }
        }
      }
    }
    else {
      zz_00f9964_(param_1);
    }
  }
  else {
    zz_00f9964_(param_1);
    zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x2a0),6);
  }
  return;
}



// ==== 800f9964  zz_00f9964_ ====

void zz_00f9964_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800f99a0  FUN_800f99a0 ====

void FUN_800f99a0(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800f99ac  FUN_800f99ac ====

void FUN_800f99ac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800f99cc  FUN_800f99cc ====

void FUN_800f99cc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_9 + 0x90);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  uVar1 = 1;
  if (*(char *)(iVar2 + 0x3ec) == '\x04') {
    uVar1 = 0x44;
  }
  zz_00097b4_(*(int *)(param_9 + 0xe0),uVar1);
  return;
}



// ==== 800f9b24  FUN_800f9b24 ====

void FUN_800f9b24(int param_1)

{
  *(undefined1 *)(param_1 + 0x6e8) = 0x80;
  *(byte *)(param_1 + 0x6e9) = *(byte *)(param_1 + 0x6e9) | 0x80;
  if (*(short *)(param_1 + 1000) == 0xa03) {
    zz_00e8c48_(param_1,0);
  }
  else if (*(short *)(param_1 + 1000) == 0xa06) {
    zz_00e8c48_(param_1,1);
  }
  return;
}



// ==== 800f9b7c  FUN_800f9b7c ====

void FUN_800f9b7c(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_804391f8) * FLOAT_804391f0);
  }
  if ('\0' < *(char *)(param_1 + 0x6f7)) {
    *(char *)(param_1 + 0x6f7) = *(char *)(param_1 + 0x6f7) + -1;
  }
  return;
}



// ==== 800f9be0  FUN_800f9be0 ====

void FUN_800f9be0(int param_1)

{
  zz_0148718_(param_1,(byte *)(param_1 + 0x14c));
  zz_01485e8_(param_1,(float *)(param_1 + 0x144));
  return;
}



// ==== 800f9c2c  FUN_800f9c2c ====

void FUN_800f9c2c(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8031d3d0)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 800f9c70  FUN_800f9c70 ====

void FUN_800f9c70(int param_1)

{
  zz_0137540_(param_1,2);
  return;
}



// ==== 800f9c94  FUN_800f9c94 ====

void FUN_800f9c94(int param_1,int param_2)

{
  int iVar1;
  
  iVar1 = param_2 * 2;
  if (*(short *)(param_1 + 1000) != 0xa03) {
    iVar1 = iVar1 + 1;
  }
  *(undefined1 *)(param_1 + 0xaf) = 1;
  zz_001ab6c_(param_1,(char)*(undefined2 *)(&DAT_80434470 + iVar1 * 2));
  return;
}



// ==== 800f9ce8  FUN_800f9ce8 ====

void FUN_800f9ce8(int param_1)

{
  (*(code *)(&PTR_FUN_8031d3e4)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 800f9d24  FUN_800f9d24 ====

void FUN_800f9d24(int param_1)

{
  (*(code *)(&PTR_zz_00fa084__8031d3f0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800f9d60  FUN_800f9d60 ====

void FUN_800f9d60(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8031d404)[*(char *)(param_1 + 0x544)])();
  return;
}



// ==== 800f9da8  FUN_800f9da8 ====

void FUN_800f9da8(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80439200;
  if ((*(char *)(param_1 + 0x7ce) == '\x0f') || (*(char *)(param_1 + 0x7ce) == '\x10')) {
    dVar2 = (double)FLOAT_80439204;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x58);
    *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x5c);
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x70);
    zz_004beb8_(dVar2,param_1,1,2,0xf,0xc,2);
    zz_004beb8_((double)FLOAT_80439204,param_1,6,2,0x1b,0xc,2);
    zz_00f9e7c_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x581) = 2;
    zz_00fa084_(param_1);
  }
  return;
}



// ==== 800f9e7c  zz_00f9e7c_ ====

void zz_00f9e7c_(int param_1)

{
  float fVar1;
  double dVar2;
  
  zz_004cd24_(param_1,7);
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,2);
  fVar1 = FLOAT_80439200;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  if (*(float *)(param_1 + 0x44) < fVar1) {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  FUN_80067310((double)FLOAT_80439208,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(float *)(param_1 + 0x558) <= FLOAT_80439200) {
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(float *)(param_1 + 0x558) = FLOAT_8043920c;
      if ((*(uint *)(param_1 + 0x5b4) & 0x200) == 0) {
        dVar2 = (double)FLOAT_80439204;
        *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
        zz_004beb8_(dVar2,param_1,1,2,0x11,0xffffffff,0xffffffff);
      }
      else {
        zz_00fa7a8_(param_1);
        zz_004beb8_((double)FLOAT_80439204,param_1,1,2,0x10,0xffffffff,0xffffffff);
      }
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800f9f94  FUN_800f9f94 ====

void FUN_800f9f94(int param_1)

{
  float fVar1;
  double dVar2;
  
  zz_004cd24_(param_1,7);
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,2);
  fVar1 = FLOAT_80439200;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  if (*(float *)(param_1 + 0x44) < fVar1) {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  FUN_80067310((double)FLOAT_80439208,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a6fc_(param_1,0x10);
    dVar2 = (double)FLOAT_80439204;
    *(undefined1 *)(param_1 + 0x540) = 1;
    zz_004beb8_(dVar2,param_1,1,0,0xb,0xffffffff,0xffffffff);
    zz_006a750_(param_1,0x10);
    *(undefined1 *)(param_1 + 0x544) = 2;
    *(undefined1 *)(param_1 + 0x588) = 1;
  }
  return;
}



// ==== 800fa084  zz_00fa084_ ====

void zz_00fa084_(int param_1)

{
  zz_00fa6f4_(param_1);
  (*(code *)(&PTR_FUN_80434480)[*(char *)(param_1 + 0x545)])(param_1);
  (*(code *)(&PTR_FUN_80434478)[*(char *)(param_1 + 0x544)])(param_1);
  (*(code *)(&PTR_FUN_8031d410)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 800fa114  FUN_800fa114 ====

void FUN_800fa114(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_80439204;
  *(char *)(param_1 + 0x545) = *(char *)(param_1 + 0x545) + '\x01';
  zz_004beb8_(dVar1,param_1,4,2,0x1a,4,2);
  return;
}



// ==== 800fa158  FUN_800fa158 ====

void FUN_800fa158(int param_1)

{
  zz_004cd24_(param_1,4);
  return;
}



// ==== 800fa17c  FUN_800fa17c ====

void FUN_800fa17c(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80439210;
  *(undefined1 *)(param_1 + 0x540) = 1;
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  zz_00fa78c_(param_1);
  zz_004beb8_((double)FLOAT_80439204,param_1,1,2,(int)*(char *)(param_1 + 0x6ea),4,2);
  return;
}



// ==== 800fa1e4  FUN_800fa1e4 ====

void FUN_800fa1e4(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80439200;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  if ((*(float *)(param_1 + 0x560) < fVar1) ||
     ((*(char *)(param_1 + 0x1cee) != '\0' && (*(short *)(param_1 + 0x54a) != 0)))) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_00fa7a8_(param_1);
    dVar2 = (double)FLOAT_80439204;
    *(undefined2 *)(param_1 + 0x54c) = 5;
    zz_004beb8_(dVar2,param_1,1,2,*(char *)(param_1 + 0x6ea) + 5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 800fa280  FUN_800fa280 ====

void FUN_800fa280(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  fVar1 = FLOAT_80439200;
  *(undefined2 *)(param_1 + 0x54c) = 5;
  if (fVar1 < *(float *)(param_1 + 0x558)) {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    if (*(char *)(param_1 + 0x745) != '\0') {
      iVar2 = zz_006dbe0_(param_1,0,1,0);
      if (iVar2 != 0) {
        zz_006bf80_(param_1);
        zz_00fa7a8_(param_1);
        zz_004beb8_((double)FLOAT_80439204,param_1,1,2,*(char *)(param_1 + 0x6ea) + 5,0xffffffff,
                    0xffffffff);
        goto LAB_800fa380;
      }
    }
    fVar1 = FLOAT_80439214;
    dVar3 = (double)FLOAT_80439204;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x55c) = fVar1;
    *(undefined2 *)(param_1 + 0x54c) = 10;
    zz_004beb8_(dVar3,param_1,7,2,*(char *)(param_1 + 0x6ea) + 10,4,2);
  }
LAB_800fa380:
  if ((*(ushort *)(param_1 + 0x5d8) & 0xf0) != 0) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 == 0) {
      zz_006a4f4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = *(float *)(param_1 + 0x558) + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800fa3e8  FUN_800fa3e8 ====

void FUN_800fa3e8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  *(undefined2 *)(param_1 + 0x54c) = 10;
  if ((*(char *)(param_1 + 0x745) != '\0') && (iVar3 = zz_006dbe0_(param_1,0,1,0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    zz_00fa78c_(param_1);
    zz_006bf80_(param_1);
    zz_00fa7a8_(param_1);
    zz_004beb8_((double)FLOAT_80439204,param_1,1,2,*(char *)(param_1 + 0x6ea) + 5,0xffffffff,
                0xffffffff);
    return;
  }
  fVar2 = FLOAT_80439200;
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) &&
      (fVar1 = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x55c) = fVar1, fVar2 < fVar1)) && (*(char *)(param_1 + 0x1cee) == '\0'))
  {
    return;
  }
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  iVar3 = zz_00677b0_(param_1);
  if (iVar3 == 0) {
    zz_006a4f4_(param_1);
  }
  else {
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800fa514  FUN_800fa514 ====

void FUN_800fa514(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80439200;
  *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0xff;
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = 0;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_004beb8_((double)FLOAT_80439204,param_1,2,2,*(char *)(param_1 + 0x6eb) + 0x15,0xc,2);
  zz_00fa5a8_(param_1);
  return;
}



// ==== 800fa5a8  zz_00fa5a8_ ====

void zz_00fa5a8_(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  
  cVar1 = *(char *)(param_1 + 0x6eb);
  iVar3 = (int)cVar1;
  if (iVar3 == 0) {
    zz_006ed8c_((double)FLOAT_80439218,param_1);
  }
  else {
    fVar2 = *(float *)(*(int *)(param_1 + 0x4ac) + 0x2c);
    if (*(float *)(param_1 + 0x44) < fVar2) {
      *(float *)(param_1 + 0x44) = fVar2;
    }
    *(float *)(param_1 + 0x4c) = FLOAT_80439200;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
  }
  if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
    *(float *)(param_1 + 0x48) = FLOAT_80439204;
  }
  else {
    *(float *)(param_1 + 0x48) = FLOAT_80439200;
  }
  FUN_80067310((double)FLOAT_80439208,param_1,*(short *)(param_1 + 0x5ae));
  zz_0067a28_(param_1);
  if (*(char *)(param_1 + 0x6ea) == iVar3) {
    zz_004cd24_(param_1,3);
  }
  else {
    if (-1 < *(char *)(param_1 + 0x6ea)) {
      zz_004beb8_((double)*(float *)(param_1 + 0x1ae0),param_1,1,2,
                  *(short *)(param_1 + 0x54c) + iVar3,
                  (int)(FLOAT_8043921c +
                       (float)((double)(float)((double)CONCAT44(0x43300000,
                                                                (int)*(short *)(param_1 + 0x1af8) ^
                                                                0x80000000) - DOUBLE_804391f8) -
                              (double)*(float *)(param_1 + 0x1ae0))),2);
      zz_004beb8_((double)FLOAT_80439204,param_1,2,2,iVar3 + 0x15,0xc,2);
    }
    *(char *)(param_1 + 0x6ea) = cVar1;
  }
  return;
}



// ==== 800fa6f4  zz_00fa6f4_ ====

void zz_00fa6f4_(int param_1)

{
  undefined2 uVar2;
  int iVar1;
  int iVar3;
  char cVar4;
  
  *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  uVar2 = zz_006d0dc_(param_1,0x81,0);
  *(undefined2 *)(param_1 + 0x54a) = uVar2;
  zz_006e1ac_(param_1,0xc1,1);
  iVar3 = 0;
  iVar1 = zz_0066ac0_(param_1,0);
  if (iVar1 != 0) {
    iVar3 = -1;
  }
  cVar4 = '\0';
  if (iVar3 != 0) {
    cVar4 = ((byte)((int)*(short *)(param_1 + 0x5aa) + 0x2000U >> 0xe) & 3) + 1;
  }
  *(char *)(param_1 + 0x6eb) = cVar4;
  return;
}



// ==== 800fa78c  zz_00fa78c_ ====

void zz_00fa78c_(int param_1)

{
  float fVar1;
  
  *(undefined1 *)(param_1 + 0x745) = 0;
  fVar1 = FLOAT_80439214;
  *(undefined1 *)(param_1 + 0x6ec) = 6;
  *(float *)(param_1 + 0x558) = fVar1;
  return;
}



// ==== 800fa7a8  zz_00fa7a8_ ====

void zz_00fa7a8_(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80439220;
  *(char *)(param_1 + 0x6ec) = *(char *)(param_1 + 0x6ec) + -1;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(undefined1 *)(param_1 + 0x587) = 0;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    if (*(short *)(param_1 + 1000) == 0xa03) {
      zz_00c3be0_(param_1,2);
      zz_00c3be0_(param_1,3);
    }
    else if (*(short *)(param_1 + 1000) == 0xa06) {
      zz_00c3be0_(param_1,2);
      zz_00c3be0_(param_1,3);
    }
  }
  return;
}



// ==== 800fa850  FUN_800fa850 ====

void FUN_800fa850(int param_1)

{
  (*(code *)(&PTR_FUN_8031d420)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 800fa88c  FUN_800fa88c ====

void FUN_800fa88c(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0147e34_(param_1);
  return;
}



// ==== 800fa8bc  FUN_800fa8bc ====

void FUN_800fa8bc(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8031d434)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800fa90c  FUN_800fa90c ====

void FUN_800fa90c(int param_1)

{
  float fVar1;
  uint uVar2;
  
  fVar1 = FLOAT_80439214;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar1;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804391f0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_80439204,param_1,0xf,3,6,0xffffffff,0xffffffff);
  return;
}



// ==== 800faa10  FUN_800faa10 ====

void FUN_800faa10(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_804391f0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_80439200;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 800faac4  FUN_800faac4 ====

void FUN_800faac4(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSQUATScale_bl((double)FLOAT_804391f0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439210;
  fVar1 = FLOAT_80439200;
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_80439224;
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x50) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
    if (fVar3 < *(float *)(param_1 + 0x760)) {
      zz_0092dcc_(param_1,0);
    }
  }
  return;
}



// ==== 800fab98  FUN_800fab98 ====

void FUN_800fab98(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  
  if (-1 < *(char *)(param_1 + 0x1cef)) {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  dVar4 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_80439228 * dVar4);
  dVar4 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar5 = (double)FLOAT_80439208;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_80439228 * -dVar4);
  FUN_80067310(dVar5,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439200;
  if (((*(char *)(param_1 + 0x1d9) == '\0') &&
      (fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x558) = fVar1, fVar2 < fVar1)) &&
     (uVar3 = FUN_800668cc((double)FLOAT_80439224,param_1), uVar3 == 0)) {
    return;
  }
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  return;
}



// ==== 800fac8c  FUN_800fac8c ====

void FUN_800fac8c(int param_1)

{
  int iVar1;
  
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_804391f8) * FLOAT_804391f0);
  }
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_80439218,param_1);
  FUN_80067310((double)FLOAT_80439208,param_1,*(short *)(param_1 + 0x5ac));
  iVar1 = zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar1 == 0) {
      zz_006a4f4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
  }
  return;
}



// ==== 800fad64  FUN_800fad64 ====

void FUN_800fad64(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0147e34_(param_1);
  return;
}



// ==== 800fad94  FUN_800fad94 ====

void FUN_800fad94(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0xa03) {
    zz_0148384_(param_1);
  }
  else {
    zz_00fadcc_(param_1);
  }
  return;
}



// ==== 800fadcc  zz_00fadcc_ ====

void zz_00fadcc_(int param_1)

{
  (*(code *)(&PTR_FUN_8031d448)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800fae08  FUN_800fae08 ====

void FUN_800fae08(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  fVar2 = FLOAT_80439200;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  *(float *)(param_1 + 0x560) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = 0x1e;
  *(undefined1 *)(param_1 + 0x6ea) = 1;
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  fVar2 = FLOAT_80439200;
  *(float *)(param_1 + 0x50) = FLOAT_80439200;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439218,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_0067a28_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_80439204;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 800faf28  FUN_800faf28 ====

void FUN_800faf28(int param_1)

{
  zz_004cd24_(param_1,0xf);
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  gnt4_PSQUATScale_bl((double)FLOAT_80439218,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_0067a28_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x6f7) = 2;
    zz_00e19a8_(param_1,10,param_1 + 0x6f7);
  }
  return;
}



// ==== 800fafe0  FUN_800fafe0 ====

void FUN_800fafe0(int param_1)

{
  double dVar1;
  uint uVar2;
  
  *(undefined1 *)(param_1 + 0x6f7) = 2;
  uVar2 = zz_006de44_(param_1,0xf0f00);
  dVar1 = DOUBLE_804391f8;
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
  gnt4_PSQUATScale_bl((double)FLOAT_80439218,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  FUN_80067310((double)FLOAT_80439208,param_1,*(short *)(param_1 + 0x5ae));
  zz_0067a28_(param_1);
  if (*(float *)(param_1 + 0x560) <= FLOAT_80439200) {
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



// ==== 800fb14c  FUN_800fb14c ====

void FUN_800fb14c(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  dVar3 = (double)FLOAT_80439208;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_804391f8) * FLOAT_804391f0);
  FUN_80067310(dVar3,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_80439200;
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



// ==== 800fb220  zz_00fb220_ ====

bool zz_00fb220_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = param_2;
    puVar1[0x10] = 0x4d;
    *(code **)(puVar1 + 0xc) = FUN_800fb330;
    *(code **)(puVar1 + 0x10c) = FUN_800fb7e0;
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
  return puVar1 != (undefined1 *)0x0;
}



// ==== 800fb330  FUN_800fb330 ====

void FUN_800fb330(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8031e930)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800fb3c8  FUN_800fb3c8 ====

void FUN_800fb3c8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined *puVar4;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  uint uVar8;
  int iVar9;
  undefined8 uVar10;
  
  uVar2 = 0x1e;
  puVar5 = &DAT_8031e8f8;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  puVar4 = &DAT_8031e8c8;
  iVar9 = *(int *)(param_9 + 0x90);
  uVar8 = *(byte *)(param_9 + 0x11) & 0x7f;
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(iVar9 + 0x70);
  iVar6 = uVar8 * 0x1c;
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(iVar9 + 0x74);
  iVar3 = uVar8 * 0x18;
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar1 = iVar3;
  iVar7 = iVar6;
  zz_0089100_(param_9,0,1);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar9 + *(short *)(&DAT_8031e8ca + iVar3) * 0x30 + 0x8d4),
             (float *)(iVar3 + -0x7fce1734),(float *)(param_9 + 0x20));
  zz_0083d60_(param_9,iVar9,(int)*(short *)(&DAT_8031e8ca + iVar3));
  *(float *)(param_9 + 0x3c) = FLOAT_80439230;
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  uVar10 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8031e908 + iVar6),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8031e908 + iVar6);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8031e8fa + iVar6);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8031e8fc + iVar6);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_8031e8fe + iVar6);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(&DAT_8031e90c + iVar6);
  *(undefined4 *)(param_9 + 0x50) = *(undefined4 *)(&DAT_8031e910 + iVar6);
  iVar9 = zz_0006f98_(iVar9);
  zz_0006fb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar9 + 0x600)
              ,*(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_8031e8c8 + iVar3),uVar2,iVar1,puVar4,
              puVar5,iVar7);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar1 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8031e8f8 + iVar6));
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    zz_00f036c_(param_9,0xe8);
    zz_00f036c_(param_9,0xe9);
  }
  return;
}



// ==== 800fb56c  FUN_800fb56c ====

void FUN_800fb56c(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (*(byte *)(param_1 + 0x11) & 0x7f) * 0x1c;
  if (*(short *)(param_1 + 0x70) < 0x4000) {
    *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0x128;
  }
  else {
    *(undefined2 *)(param_1 + 0x70) = 0x4000;
  }
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar1 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar1 == 0) {
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_00fb76c_(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else if (*(short *)(param_1 + 0x1c) < 1) {
        zz_00fb76c_(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else {
        FUN_80083874((double)*(float *)(&DAT_8031e904 + iVar2),param_1);
        if (*(int *)(param_1 + 200) == 0) {
          gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                           (float *)(param_1 + 0x20));
        }
        else {
          *(char *)(param_1 + 0x1cb) = *(char *)(param_1 + 0x1cb) + -1;
          if (*(char *)(param_1 + 0x1cb) < '\x01') {
            *(char *)(param_1 + 0x1cb) = (char)*(undefined2 *)(&DAT_8031e8fc + iVar2);
            FUN_8006c498((double)*(float *)(&DAT_8031e900 + iVar2),param_1,
                         (float *)(*(int *)(param_1 + 200) + 100));
            zz_00833a4_(param_1);
          }
          else {
            gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                             (float *)(param_1 + 0x20));
          }
        }
        *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x3c);
        *(float *)(param_1 + 0x3c) = *(float *)(param_1 + 0x3c) + *(float *)(param_1 + 0x50);
        *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
        zz_00833ec_(param_1);
        zz_0083610_(param_1,(float *)(param_1 + 0x3c));
        iVar2 = zz_0083714_(param_1);
        if (iVar2 == 0) {
          iVar2 = zz_0084170_(param_1);
          if (iVar2 != 0) {
            zz_00fb76c_(param_1);
            zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),7);
          }
        }
        else {
          zz_00fb76c_(param_1);
        }
      }
    }
    else {
      zz_00fb76c_(param_1);
    }
  }
  else {
    zz_00fb76c_(param_1);
    zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),7);
  }
  return;
}



// ==== 800fb76c  zz_00fb76c_ ====

void zz_00fb76c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_008aff0_(param_1);
  zz_00f036c_(param_1,0xea);
  return;
}



// ==== 800fb7b4  FUN_800fb7b4 ====

void FUN_800fb7b4(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800fb7c0  FUN_800fb7c0 ====

void FUN_800fb7c0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800fb7e0  FUN_800fb7e0 ====

void FUN_800fb7e0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = *(int *)(param_9 + 0x90);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
              param_14,param_15,param_16);
  uVar1 = 1;
  if (*(char *)(iVar2 + 0x3ec) == '\x04') {
    uVar1 = 0x44;
  }
  zz_00097b4_(*(int *)(param_9 + 0xe0),uVar1);
  return;
}



// ==== 800fb83c  FUN_800fb83c ====

void FUN_800fb83c(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x300) || (*(short *)(param_1 + 1000) == 0x30b)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,4), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_800fb94c;
    *(code **)(puVar1 + 0x10c) = FUN_800fbbcc;
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



// ==== 800fb94c  FUN_800fb94c ====

void FUN_800fb94c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8031e968)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800fb9a0  FUN_800fb9a0 ====

void FUN_800fb9a0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar4;
  undefined8 uVar5;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar4 = *(int *)(param_9 + 0x90);
  iVar1 = zz_0006f98_(iVar4);
  uVar5 = zz_0007030_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xe0),
                      *(int *)(&DAT_8031e958 + *(char *)(param_9 + 0x11) * 8),iVar1 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar1 + 0xc28;
  iVar2 = *(int *)(&DAT_8031e958 + *(char *)(param_9 + 0x11) * 8);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xe4),iVar2,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  uVar5 = zz_0007cac_((double)FLOAT_80439238,*(int *)(param_9 + 0xe4));
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xe8),
                      *(int *)(&DAT_8031e95c + *(char *)(param_9 + 0x11) * 8),iVar1 + 0xc28,in_r7,
                      in_r8,in_r9,in_r10);
  iVar3 = iVar1 + 0xc28;
  iVar2 = *(int *)(&DAT_8031e95c + *(char *)(param_9 + 0x11) * 8);
  uVar5 = zz_0007030_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xec),iVar2,iVar3,in_r7,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,iVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_80439238,*(int *)(param_9 + 0xec));
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_00fbaf8_(param_9);
  return;
}



// ==== 800fbaf8  zz_00fbaf8_ ====

void zz_00fbaf8_(int param_1)

{
  int iVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = (int)*(char *)(*(int *)(param_1 + 0x90) + 0x144);
  iVar1 = (int)(1U - iVar4 | iVar4 - 1U) >> 0x1f;
  if (iVar4 == 1) {
    *(undefined1 *)(param_1 + 0x84) = 0x41;
  }
  else {
    *(undefined1 *)(param_1 + 0x84) = 0x4d;
    *(undefined2 *)(param_1 + 0x70) = 0;
    *(undefined2 *)(param_1 + 0x72) = 0x98e3;
    *(undefined2 *)(param_1 + 0x74) = 0x4000;
  }
  fVar2 = FLOAT_8043923c;
  iVar4 = iVar1 * -0xc;
  *(undefined *)(param_1 + 0x89) = (&DAT_80434488)[-iVar1];
  uVar3 = *(undefined4 *)(&DAT_8031e944 + iVar4);
  *(undefined4 *)(param_1 + 100) = *(undefined4 *)(&DAT_8031e940 + iVar4);
  *(undefined4 *)(param_1 + 0x68) = uVar3;
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(&DAT_8031e948 + iVar4);
  *(float *)(param_1 + 0xb4) = fVar2;
  *(float *)(param_1 + 0xb8) = fVar2;
  *(float *)(param_1 + 0x58) = fVar2;
  *(float *)(param_1 + 0x5c) = fVar2;
  *(float *)(param_1 + 0x60) = fVar2;
  return;
}



// ==== 800fbbac  FUN_800fbbac ====

void FUN_800fbbac(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800fbbcc  FUN_800fbbcc ====

void FUN_800fbbcc(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  uint uVar4;
  int iVar5;
  
  uVar4 = 0x44;
  iVar3 = *(int *)(param_9 + 0x90);
  iVar2 = (int)*(char *)(iVar3 + 0x144);
  uVar1 = ~((int)~((uint)(iVar2 + -1) | 1U - iVar2) >> 0x1f) & 2;
  if (*(char *)(iVar3 + 0xae) != '\0') {
    uVar1 = uVar1 + 1;
  }
  if (*(char *)(iVar3 + 0xae) == '\0') {
    uVar4 = 0x45;
  }
  iVar5 = *(int *)(param_9 + uVar1 * 4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
              (float *)(param_9 + 0x114),(undefined *)(iVar2 + -1),iVar2,iVar3,in_r8,in_r9,in_r10);
  zz_00097b4_(iVar5,uVar4);
  return;
}



// ==== 800fbc64  zz_00fbc64_ ====

bool zz_00fbc64_(int param_1,undefined1 param_2)

{
  short sVar1;
  bool bVar3;
  undefined1 *puVar2;
  
  sVar1 = *(short *)(*(int *)(param_1 + 0x90) + 1000);
  if (((((sVar1 == 0x700) || (sVar1 == 0x702)) || (sVar1 == 0x703)) ||
      ((sVar1 == 0x704 || (sVar1 == 0x707)))) ||
     ((sVar1 == 0x709 || ((sVar1 == 0x70a || (sVar1 == 0x70b)))))) {
    puVar2 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,0,1);
    bVar3 = puVar2 != (undefined1 *)0x0;
    if (bVar3) {
      *puVar2 = 1;
      puVar2[0x13] = param_2;
      puVar2[0x11] = param_2;
      puVar2[0x10] = 0x36;
      *(code **)(puVar2 + 0xc) = FUN_800fbdc0;
      *(code **)(puVar2 + 0x10c) = FUN_800fc1c8;
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
  }
  else {
    bVar3 = false;
  }
  return bVar3;
}



// ==== 800fbdc0  FUN_800fbdc0 ====

void FUN_800fbdc0(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8031eb4c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800fbe58  FUN_800fbe58 ====

void FUN_800fbe58(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined *puVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  float *pfVar8;
  int iVar9;
  undefined8 uVar10;
  
  puVar6 = &DAT_8031ea50;
  puVar4 = &DAT_8031e978;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar9 = *(int *)(param_9 + 0x90);
  iVar5 = (int)*(char *)(param_9 + 0x13);
  iVar7 = *(int *)(param_9 + 0x8c);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar3 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  *(undefined1 *)(param_9 + 0x98) = 5;
  iVar2 = iVar5 * 0x18;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar1 = iVar3;
  zz_0089100_(param_9,0,1);
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  if (*(short *)(&DAT_8031e97a + iVar2) < 0) {
    pfVar8 = (float *)(iVar7 + 0x114);
  }
  else {
    pfVar8 = (float *)(iVar9 + *(short *)(&DAT_8031e97a + iVar2) * 0x30 + 0x8d4);
  }
  *(float *)(param_9 + 0x9c) = pfVar8[1];
  *(float *)(param_9 + 0xa0) = pfVar8[5];
  *(float *)(param_9 + 0xa4) = pfVar8[9];
  gnt4_PSMTXMultVec_bl(pfVar8,(float *)(iVar2 + -0x7fce1684),(float *)(param_9 + 0x20));
  *(float *)(param_9 + 0x38) = pfVar8[2];
  *(float *)(param_9 + 0x3c) = pfVar8[6];
  *(float *)(param_9 + 0x40) = pfVar8[10];
  uVar10 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8031ea60 + iVar3),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8031ea60 + iVar3);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8031ea52 + iVar3);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8031ea54 + iVar3);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_8031ea56 + iVar3);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(&DAT_8031ea64 + iVar3);
  iVar7 = zz_0006f98_(iVar9);
  zz_000726c_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar7 + 0x600)
              ,*(int *)(param_9 + 0xe0),(float *)(int)*(short *)(&DAT_8031e978 + iVar2),
              (int)*(char *)(param_9 + 0x88),iVar1,puVar4,iVar5,puVar6);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar1 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8031ea50 + iVar3));
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    zz_00f036c_(param_9,0xb8);
  }
  return;
}



// ==== 800fc00c  FUN_800fc00c ====

void FUN_800fc00c(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
      *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
      *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
      if (*(short *)(param_1 + 0x1c) < 1) {
        zz_00fc16c_(param_1);
      }
      else {
        if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x144)) {
          *(float *)(param_1 + 0x44) =
               *(float *)(param_1 + 0x44) + *(float *)(&DAT_8031ea68 + iVar1);
        }
        else {
          *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x144);
        }
        gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                            (float *)(param_1 + 0x38));
        FUN_80083874((double)*(float *)(&DAT_8031ea5c + iVar1),param_1);
        FUN_80083ad4((double)*(float *)(&DAT_8031ea58 + iVar1),param_1,
                     (char)*(undefined2 *)(&DAT_8031ea54 + iVar1));
        *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
        zz_00833ec_(param_1);
        zz_0083610_(param_1,(float *)(param_1 + 0x144));
        iVar1 = zz_0083714_(param_1);
        if (iVar1 == 0) {
          iVar1 = zz_0084170_(param_1);
          if (iVar1 != 0) {
            zz_00fc16c_(param_1);
          }
        }
        else {
          zz_00fc16c_(param_1);
        }
      }
    }
    else {
      zz_00fc16c_(param_1);
    }
  }
  else {
    zz_00fc16c_(param_1);
  }
  return;
}



// ==== 800fc16c  zz_00fc16c_ ====

void zz_00fc16c_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_008aff0_(param_1);
  return;
}



// ==== 800fc19c  FUN_800fc19c ====

void FUN_800fc19c(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800fc1a8  FUN_800fc1a8 ====

void FUN_800fc1a8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800fc1c8  FUN_800fc1c8 ====

void FUN_800fc1c8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800fc208  zz_00fc208_ ====

void zz_00fc208_(int param_1,undefined4 *param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 8;
    puVar1[0x11] = param_3;
    uVar2 = param_2[1];
    *(undefined4 *)(puVar1 + 0x20) = *param_2;
    *(undefined4 *)(puVar1 + 0x24) = uVar2;
    *(undefined4 *)(puVar1 + 0x28) = param_2[2];
    *(code **)(puVar1 + 0xc) = FUN_800fc32c;
    *(undefined4 *)(puVar1 + 0x10c) = 0;
    *(undefined2 *)(puVar1 + 0x72) = *(undefined2 *)(param_1 + 0x72);
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



// ==== 800fc32c  FUN_800fc32c ====

void FUN_800fc32c(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_8031ed1c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800fc37c  FUN_800fc37c ====

void FUN_800fc37c(int param_1)

{
  int iVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_80439240;
  *(undefined1 *)(param_1 + 0x18) = 1;
  iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x30;
  *(undefined2 *)(param_1 + 0x1c) = 600;
  *(char *)(param_1 + 0x1cb) = (char)*(undefined2 *)(&DAT_8031eb62 + iVar1);
  *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(&DAT_8031eb70 + iVar1);
  *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(&DAT_8031eb74 + iVar1);
  dVar2 = FUN_8003d964(dVar2,param_1,(float *)(param_1 + 0x20));
  *(float *)(param_1 + 0x24) = (float)dVar2;
  zz_00fcae0_(param_1);
  *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x28);
  *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x168) = *(undefined4 *)(param_1 + 0x28);
  zz_00fc6a0_(param_1,(undefined4 *)(param_1 + 0x20),*(undefined1 *)(param_1 + 0x11));
  return;
}



// ==== 800fc440  FUN_800fc440 ====

/* WARNING: Removing unreachable block (ram,0x800fc67c) */
/* WARNING: Removing unreachable block (ram,0x800fc450) */

void FUN_800fc440(int param_1)

{
  bool bVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  short sVar8;
  int iVar9;
  double dVar10;
  double dVar11;
  float afStack_30 [5];
  
  dVar11 = (double)*(float *)(param_1 + 0x24);
  iVar9 = (uint)*(byte *)(param_1 + 0x11) * 0x30;
  zz_00fcbd8_(param_1);
  fVar2 = (float)((double)*(float *)(param_1 + 0x24) - dVar11);
  if (fVar2 < FLOAT_80439244) {
    fVar2 = -fVar2;
  }
  bVar1 = fVar2 < FLOAT_80439240;
  iVar5 = zz_003f044_((float *)(param_1 + 0x2c),(float *)(param_1 + 0x20),afStack_30);
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x4c);
  if (*(float *)(&DAT_8031eb7c + iVar9) < *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = *(float *)(&DAT_8031eb7c + iVar9);
  }
  if (*(float *)(param_1 + 0x44) < *(float *)(&DAT_8031eb78 + iVar9)) {
    *(float *)(param_1 + 0x44) = *(float *)(&DAT_8031eb78 + iVar9);
  }
  FUN_80083874((double)FLOAT_80439244,param_1);
  dVar11 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x154));
  if ((double)FLOAT_80439244 < dVar11) {
    dVar10 = 1.0 / SQRT(dVar11);
    dVar10 = DOUBLE_80439248 * dVar10 * -(dVar11 * dVar10 * dVar10 - DOUBLE_80439250);
    dVar10 = DOUBLE_80439248 * dVar10 * -(dVar11 * dVar10 * dVar10 - DOUBLE_80439250);
    dVar11 = (double)(float)(dVar11 * DOUBLE_80439248 * dVar10 *
                                      -(dVar11 * dVar10 * dVar10 - DOUBLE_80439250));
  }
  fVar2 = *(float *)(&DAT_8031eb6c + iVar9);
  fVar3 = *(float *)(param_1 + 0xb4);
  iVar6 = zz_0083244_((float *)(param_1 + 0x20));
  iVar7 = zz_0083714_(param_1);
  sVar8 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar8;
  uVar4 = countLeadingZeros((int)sVar8);
  if (((((bVar1 && iVar5 == 0) && dVar11 < (double)(fVar2 * fVar3)) && iVar6 == 0) && iVar7 == 0) &&
      ((1 << (uVar4 & 0x1f) | 1U >> 0x20 - (uVar4 & 0x1f)) & 1) == 0) {
    dVar11 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x160));
    if ((double)FLOAT_80439244 < dVar11) {
      dVar10 = 1.0 / SQRT(dVar11);
      dVar10 = DOUBLE_80439248 * dVar10 * -(dVar11 * dVar10 * dVar10 - DOUBLE_80439250);
      dVar10 = DOUBLE_80439248 * dVar10 * -(dVar11 * dVar10 * dVar10 - DOUBLE_80439250);
      dVar11 = (double)(float)(dVar11 * DOUBLE_80439248 * dVar10 *
                                        -(dVar11 * dVar10 * dVar10 - DOUBLE_80439250));
    }
    if ((double)(*(float *)(&DAT_8031eb80 + iVar9) * *(float *)(param_1 + 0xb4)) <= dVar11) {
      *(undefined4 *)(param_1 + 0x160) = *(undefined4 *)(param_1 + 0x20);
      *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x24);
      *(undefined4 *)(param_1 + 0x168) = *(undefined4 *)(param_1 + 0x28);
      zz_00fc6a0_(param_1,(undefined4 *)(param_1 + 0x20),*(undefined1 *)(param_1 + 0x11));
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



