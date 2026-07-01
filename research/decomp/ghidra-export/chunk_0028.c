// ==== 800fc6a0  zz_00fc6a0_ ====

void zz_00fc6a0_(int param_1,undefined4 *param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  undefined4 uVar2;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,1,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 9;
    puVar1[0x11] = param_3;
    uVar2 = param_2[1];
    *(undefined4 *)(puVar1 + 0x20) = *param_2;
    *(undefined4 *)(puVar1 + 0x24) = uVar2;
    *(undefined4 *)(puVar1 + 0x28) = param_2[2];
    *(code **)(puVar1 + 0xc) = FUN_800fc7c0;
    *(code **)(puVar1 + 0x10c) = FUN_800fcaa0;
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



// ==== 800fc7c0  FUN_800fc7c0 ====

void FUN_800fc7c0(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_8031ed2c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800fc810  FUN_800fc810 ====

void FUN_800fc810(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  uint uVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  double dVar4;
  undefined8 uVar5;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar1 = (uint)*(byte *)(param_9 + 0x11) * 0x30;
  iVar2 = -((int)*(short *)(&DAT_8031eb60 + iVar1) >> 0x1f);
  if (iVar2 == 0) {
    iVar2 = zz_008ae3c_(*(int *)(param_9 + 0x90),param_9,(byte)*(short *)(&DAT_8031eb60 + iVar1));
  }
  if (iVar2 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined2 *)(param_9 + 0x1e) = DAT_8031ed12;
    *(float *)(param_9 + 0x16c) = *(float *)(&DAT_8031eb84 + iVar1) * *(float *)(param_9 + 0xb4);
    *(float *)(param_9 + 0x170) = *(float *)(&DAT_8031eb88 + iVar1) * *(float *)(param_9 + 0xb4);
    *(undefined2 *)(param_9 + 0x74) = 0;
    *(undefined2 *)(param_9 + 0x70) = 0;
    uVar3 = zz_00055fc_();
    dVar4 = (double)FLOAT_80439240;
    *(short *)(param_9 + 0x72) = (short)(uVar3 << 8);
    dVar4 = FUN_8003d964(dVar4,param_9,(float *)(param_9 + 0x20));
    *(float *)(param_9 + 0x24) = (float)dVar4;
    *(undefined1 *)(param_9 + 0x84) = 0x1e;
    *(code **)(param_9 + 0x100) = FUN_80047aa4;
    zz_0089100_(param_9,0,1);
    zz_0018f88_((int *)(param_9 + 0x144),(int)PTR_DAT_8031ed14,(float *)(param_9 + 0x58));
    *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x58) * *(float *)(param_9 + 0x170);
    *(float *)(param_9 + 0x5c) = *(float *)(param_9 + 0x5c) * *(float *)(param_9 + 0x16c);
    *(float *)(param_9 + 0x60) = *(float *)(param_9 + 0x60) * *(float *)(param_9 + 0x170);
    uVar5 = zz_0019338_((int *)(param_9 + 0x14c),(int)PTR_DAT_8031ed18,(float *)(param_9 + 0x174));
    zz_000726c_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(param_9 + 0xe0),(float *)(int)DAT_8031ed10,(int)*(char *)(param_9 + 0x88),
                in_r7,in_r8,in_r9,in_r10);
    zz_0007cac_((double)*(float *)(param_9 + 0x174),*(int *)(param_9 + 0xe0));
    *(undefined1 *)(param_9 + 0x82) = 1;
    zz_00f036c_(param_9,0x18);
  }
  return;
}



// ==== 800fc9b4  FUN_800fc9b4 ====

void FUN_800fc9b4(int param_1)

{
  short sVar1;
  
  sVar1 = *(short *)(param_1 + 0x1c) + 1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (*(short *)(param_1 + 0x1e) <= sVar1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x58));
  *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) * *(float *)(param_1 + 0x170);
  *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * *(float *)(param_1 + 0x16c);
  *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) * *(float *)(param_1 + 0x170);
  zz_0019370_((int *)(param_1 + 0x14c),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x174));
  zz_0007cac_((double)*(float *)(param_1 + 0x174),*(int *)(param_1 + 0xe0));
  return;
}



// ==== 800fca80  FUN_800fca80 ====

void FUN_800fca80(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800fcaa0  FUN_800fcaa0 ====

void FUN_800fcaa0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800fcae0  zz_00fcae0_ ====

void zz_00fcae0_(int param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  double dVar4;
  
  bVar1 = *(byte *)(param_1 + 0x11);
  iVar3 = *(int *)(param_1 + 200);
  gnt4_PSMTXIdentity_bl((float *)(param_1 + 0x114));
  zz_00457d4_('y',(float *)(param_1 + 0x114),(float *)(param_1 + 0x114),*(short *)(param_1 + 0x72));
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x11c);
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 300);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x13c);
  if ((iVar3 != 0) &&
     (((double)*(float *)(&DAT_8031eb8c + (uint)bVar1 * 0x30) < (double)FLOAT_80439244 ||
      (iVar2 = FUN_8006c334((double)*(float *)(&DAT_8031eb8c + (uint)bVar1 * 0x30),param_1,
                            (float *)(iVar3 + 100)), iVar2 != 0)))) {
    gnt4_PSVECSubtract_bl
              ((float *)(iVar3 + 100),(float *)(param_1 + 0x20),(float *)(param_1 + 0x38));
    *(float *)(param_1 + 0x3c) = FLOAT_80439244;
    dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if ((double)FLOAT_80439244 < dVar4) {
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    }
  }
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                      (float *)(param_1 + 0x38));
  return;
}



// ==== 800fcbd8  zz_00fcbd8_ ====

void zz_00fcbd8_(int param_1)

{
  bool bVar1;
  int iVar2;
  char cVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  bVar1 = false;
  iVar4 = *(int *)(param_1 + 200);
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x30;
  if (iVar4 != 0) {
    cVar3 = *(char *)(param_1 + 0x1cb) + -1;
    *(char *)(param_1 + 0x1cb) = cVar3;
    if (cVar3 < '\x01') {
      *(char *)(param_1 + 0x1cb) = (char)*(undefined2 *)(&DAT_8031eb62 + iVar2);
      local_24 = *(float *)(iVar4 + 100);
      local_1c = *(undefined4 *)(iVar4 + 0x6c);
      local_20 = *(undefined4 *)(param_1 + 0x24);
      dVar5 = gnt4_PSVECSquareDistance_bl(&local_24,(float *)(param_1 + 0x20));
      if ((double)FLOAT_80439244 < dVar5) {
        dVar6 = 1.0 / SQRT(dVar5);
        dVar6 = DOUBLE_80439248 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80439250);
        dVar6 = DOUBLE_80439248 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80439250);
        dVar5 = (double)(float)(dVar5 * DOUBLE_80439248 * dVar6 *
                                        -(dVar5 * dVar6 * dVar6 - DOUBLE_80439250));
      }
      if (dVar5 <= (double)*(float *)(&DAT_8031eb68 + iVar2)) {
        *(undefined4 *)(param_1 + 200) = 0;
      }
      else {
        FUN_8006c498((double)*(float *)(&DAT_8031eb64 + iVar2),param_1,&local_24);
        zz_00833a4_(param_1);
        bVar1 = true;
      }
    }
  }
  if (!bVar1) {
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  }
  dVar5 = FUN_8003d964((double)FLOAT_80439240,param_1,(float *)(param_1 + 0x20));
  *(float *)(param_1 + 0x24) = (float)dVar5;
  return;
}



// ==== 800fcd38  zz_00fcd38_ ====

bool zz_00fcd38_(int param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = param_3;
    puVar1[0x11] = param_2;
    puVar1[0x10] = 0x4c;
    *(code **)(puVar1 + 0xc) = FUN_800fce50;
    *(code **)(puVar1 + 0x10c) = FUN_800fd364;
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



// ==== 800fce50  FUN_800fce50 ====

void FUN_800fce50(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8031eed8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800fcee8  FUN_800fcee8 ====

void FUN_800fcee8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  undefined *puVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  undefined8 uVar9;
  
  uVar2 = 0x1e;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar8 = *(int *)(param_9 + 0x90);
  puVar5 = (&PTR_DAT_8031ee00)[(int)*(char *)(param_9 + 0x11) & 0x7f];
  iVar4 = *(char *)(param_9 + 0x13) * 0x18;
  iVar6 = ((int)*(char *)(param_9 + 0x11) & 0x7fU) * 0x20;
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(iVar8 + 0x70);
  psVar7 = (short *)(puVar5 + iVar4);
  uVar3 = (uint)*(ushort *)(iVar8 + 0x74);
  *(ushort *)(param_9 + 0x74) = *(ushort *)(iVar8 + 0x74);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar1 = iVar6;
  zz_0089100_(param_9,0,1);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar8 + psVar7[1] * 0x30 + 0x8d4),(float *)(psVar7 + 2),
             (float *)(param_9 + 0x20));
  zz_0083d60_(param_9,iVar8,(int)psVar7[1]);
  *(float *)(param_9 + 0x3c) = FLOAT_80439258;
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  uVar9 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8031ee28 + iVar6),(float *)(param_9 + 0x38),
                              (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8031ee28 + iVar6);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8031ee1a + iVar6);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8031ee1c + iVar6);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_8031ee1e + iVar6);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x3c) = *(undefined4 *)(&DAT_8031ee2c + iVar6);
  *(undefined4 *)(param_9 + 0x50) = *(undefined4 *)(&DAT_8031ee30 + iVar6);
  iVar8 = zz_0006f98_(iVar8);
  zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar8 + 0x600),
              *(int *)(param_9 + 0xe0),(int)*psVar7,uVar2,uVar3,iVar4,puVar5,iVar1);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar1 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8031ee18 + iVar6));
  if (iVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    zz_00f036c_(param_9,0xe7);
    zz_00f036c_(param_9,0xe9);
  }
  return;
}



// ==== 800fd09c  FUN_800fd09c ====

void FUN_800fd09c(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = (*(byte *)(param_1 + 0x11) & 0x7f) * 0x20;
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
        zz_00fd288_(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else if (*(short *)(param_1 + 0x1c) < 1) {
        zz_00fd288_(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else {
        FUN_80083874((double)*(float *)(&DAT_8031ee24 + iVar2),param_1);
        if (*(int *)(param_1 + 200) == 0) {
          gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),
                           (float *)(param_1 + 0x20));
        }
        else {
          *(char *)(param_1 + 0x1cb) = *(char *)(param_1 + 0x1cb) + -1;
          if (*(char *)(param_1 + 0x1cb) < '\x01') {
            *(char *)(param_1 + 0x1cb) = (char)*(undefined2 *)(&DAT_8031ee1c + iVar2);
            FUN_8006c498((double)*(float *)(&DAT_8031ee20 + iVar2),param_1,
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
            zz_00fd288_(param_1);
            zz_00fd2d0_(param_1);
          }
        }
        else {
          zz_00fd288_(param_1);
        }
      }
    }
    else {
      zz_00fd288_(param_1);
    }
  }
  else {
    zz_00fd288_(param_1);
    zz_00fd2d0_(param_1);
  }
  return;
}



// ==== 800fd288  zz_00fd288_ ====

void zz_00fd288_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  *(undefined1 *)(param_1 + 0x82) = 0;
  zz_008aff0_(param_1);
  zz_00f036c_(param_1,0xea);
  return;
}



// ==== 800fd2d0  zz_00fd2d0_ ====

void zz_00fd2d0_(int param_1)

{
  short sVar1;
  int iVar2;
  
  iVar2 = (*(byte *)(param_1 + 0x11) & 0x7f) * 0x20;
  sVar1 = *(short *)(&DAT_8031ee34 + iVar2);
  if (sVar1 == 1) {
    zz_00fc6a0_(param_1,(undefined4 *)(param_1 + 0x20),(char)*(undefined2 *)(&DAT_8031ee36 + iVar2))
    ;
  }
  else if ((sVar1 < 1) && (-1 < sVar1)) {
    zz_00fc208_(param_1,(undefined4 *)(param_1 + 0x20),(char)*(undefined2 *)(&DAT_8031ee36 + iVar2))
    ;
  }
  return;
}



// ==== 800fd338  FUN_800fd338 ====

void FUN_800fd338(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800fd344  FUN_800fd344 ====

void FUN_800fd344(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800fd364  FUN_800fd364 ====

void FUN_800fd364(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800fd3c0  zz_00fd3c0_ ====

bool zz_00fd3c0_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 == (undefined1 *)0x0) {
    *(undefined1 *)(param_1 + 0x14a) = 0;
  }
  else {
    *puVar1 = 1;
    puVar1[0x13] = 0;
    puVar1[0x11] = 0;
    puVar1[0x10] = 0x50;
    *(code **)(puVar1 + 0xc) = FUN_800fd4cc;
    *(code **)(puVar1 + 0x10c) = FUN_800fe60c;
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



// ==== 800fd4cc  FUN_800fd4cc ====

void FUN_800fd4cc(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8031ef28)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800fd564  FUN_800fd564 ====

void FUN_800fd564(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  int iVar7;
  undefined *puVar8;
  int iVar9;
  undefined8 uVar10;
  double dVar11;
  
  puVar8 = &DAT_8031ef0c;
  puVar6 = &DAT_8031eee8;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar9 = *(int *)(param_9 + 0x90);
  iVar7 = (int)*(char *)(param_9 + 0x13);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x1c;
  *(undefined1 *)(param_9 + 0x98) = 3;
  iVar3 = iVar7 * 0x24;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar2 = iVar3;
  iVar5 = iVar4;
  zz_0089100_(param_9,0,1);
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)(iVar9 + *(short *)(&DAT_8031eeea + iVar3) * 0x30 + 0x8dc);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar9 + *(short *)(&DAT_8031eeea + iVar3) * 0x30 + 0x8ec);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar9 + *(short *)(&DAT_8031eeea + iVar3) * 0x30 + 0x8fc);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar9 + *(short *)(&DAT_8031eeea + iVar3) * 0x30 + 0x8d4),
             (float *)(iVar3 + -0x7fce1114),(float *)(param_9 + 0x20));
  zz_0083d60_(param_9,iVar9,(int)*(short *)(&DAT_8031eeea + iVar3));
  gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  uVar10 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8031ef1c + iVar4),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8031ef1c + iVar4);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8031ef10 + iVar4);
  *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_8031ef12 + iVar4);
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x18c) = *(undefined4 *)(&DAT_8031ef20 + iVar4);
  iVar1 = zz_0006f98_(iVar9);
  zz_0006fb4_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar1 + 0x600)
              ,*(int *)(param_9 + 0xe0),(int)*(short *)(&DAT_8031eee8 + iVar3),iVar2,iVar5,puVar6,
              iVar7,puVar8);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar2 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8031ef0c + iVar4));
  if (iVar2 == 0) {
    *(undefined1 *)(iVar9 + 0x14a) = 0;
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar9 + *(short *)(&DAT_8031eeea + iVar3) * 0x30 + 0x8d4),
               (float *)(iVar3 + -0x7fce1108),(float *)(param_9 + 0x144));
    gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),(float *)(param_9 + 0x38),(float *)(param_9 + 0x150))
    ;
    zz_00a2bf8_(iVar9,param_9,(undefined4 *)(param_9 + 0x144),(float *)(param_9 + 0x150),1,0);
    *(undefined4 *)(param_9 + 0x180) = *(undefined4 *)(param_9 + 0x38);
    *(undefined4 *)(param_9 + 0x184) = *(undefined4 *)(param_9 + 0x3c);
    *(undefined4 *)(param_9 + 0x188) = *(undefined4 *)(param_9 + 0x40);
    dVar11 = gnt4_PSVECMag_bl((float *)(param_9 + 0x38));
    if ((double)FLOAT_80439260 < dVar11) {
      gnt4_PSQUATScale_bl((double)FLOAT_80439264,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38)
                         );
    }
    zz_00f036c_(param_9,0xdb);
  }
  return;
}



// ==== 800fd7ac  FUN_800fd7ac ====

void FUN_800fd7ac(int param_1)

{
  char cVar1;
  double dVar2;
  
  *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x180);
  *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x184);
  *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x188);
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 == '\x01') {
    FUN_800fdc10(param_1);
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      zz_00fd868_(param_1);
    }
  }
  else if (cVar1 < '\x03') {
    zz_00fe300_(param_1);
  }
  *(undefined4 *)(param_1 + 0x180) = *(undefined4 *)(param_1 + 0x38);
  *(undefined4 *)(param_1 + 0x184) = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x188) = *(undefined4 *)(param_1 + 0x40);
  dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_80439260 < dVar2) {
    gnt4_PSQUATScale_bl((double)FLOAT_80439264,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  }
  return;
}



// ==== 800fd868  zz_00fd868_ ====

void zz_00fd868_(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float afStack_24 [4];
  
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  iVar4 = *(int *)(param_1 + 0x90);
  iVar2 = *(char *)(param_1 + 0x13) * 0x24;
  if (*(byte *)(param_1 + 0x1d9) == 0) {
    iVar1 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar1 == 0) {
      *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x11c);
      *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 300);
      *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x13c);
      if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x18c)) {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(&DAT_8031ef24 + iVar3);
      }
      else {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x18c);
      }
      gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                          (float *)(param_1 + 0x38));
      FUN_80083874((double)*(float *)(&DAT_8031ef18 + iVar3),param_1);
      FUN_80083ad4((double)*(float *)(&DAT_8031ef14 + iVar3),param_1,
                   (char)*(undefined2 *)(&DAT_8031ef10 + iVar3));
      zz_00833ec_(param_1);
      zz_0083610_(param_1,(float *)(param_1 + 0x18c));
      iVar3 = zz_0083714_(param_1);
      if (iVar3 == 0) {
        iVar3 = zz_0084170_(param_1);
        if (iVar3 == 0) {
          gnt4_PSMTXMultVec_bl
                    ((float *)(iVar4 + *(short *)(&DAT_8031eeea + iVar2) * 0x30 + 0x8d4),
                     (float *)(iVar2 + -0x7fce1108),(float *)(param_1 + 0x144));
          *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
          *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
          *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
          gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x144),afStack_24);
          dVar5 = gnt4_PSVECMag_bl(afStack_24);
          if ((double)FLOAT_80439278 <= dVar5) {
            gnt4_PSQUATScale_bl((double)(float)((double)FLOAT_80439278 / dVar5),afStack_24,
                                afStack_24);
            gnt4_PSVECAdd_bl((float *)(param_1 + 0x144),afStack_24,(float *)(param_1 + 0x20));
            *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
            *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
            *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
            zz_00fe4b8_(param_1);
          }
        }
        else {
          zz_00fe4b8_(param_1);
        }
      }
      else {
        zz_00fe4b8_(param_1);
      }
    }
    else {
      zz_00fe4b8_(param_1);
    }
  }
  else if ((*(byte *)(param_1 + 0x1d9) & 0x10) == 0) {
    zz_00fe4b8_(param_1);
  }
  else {
    *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x290);
    iVar3 = *(int *)(param_1 + 0x15c);
    if (*(char *)(iVar3 + 0x83) == '\0') {
      iVar4 = *(int *)(param_1 + 0x90);
      if ((((int)*(char *)(iVar4 + 0x71e) & 1 << (int)*(char *)(iVar3 + 0x3e4)) == 0) ||
         (((int)*(char *)(iVar3 + 0x71e) & 1 << (int)*(char *)(iVar4 + 0x3e4)) == 0)) {
        *(undefined1 *)(iVar3 + 0x719) = 1;
        *(int *)(iVar4 + 0x144) = iVar3;
        *(undefined1 *)(param_1 + 0x19) = 1;
        *(undefined2 *)(param_1 + 0x1c) = 600;
        zz_008aff0_(param_1);
        *(byte *)(iVar4 + 0x71e) =
             *(byte *)(iVar4 + 0x71e) | (byte)(1 << (int)*(char *)(iVar3 + 0x3e4));
        *(byte *)(iVar3 + 0x71e) =
             *(byte *)(iVar3 + 0x71e) | (byte)(1 << (int)*(char *)(iVar4 + 0x3e4));
        *(byte *)(iVar4 + 0x71f) =
             *(byte *)(iVar4 + 0x71f) & ~(byte)(1 << (int)*(char *)(iVar3 + 0x3e4));
        *(byte *)(iVar3 + 0x71f) =
             *(byte *)(iVar3 + 0x71f) & ~(byte)(1 << (int)*(char *)(iVar4 + 0x3e4));
        *(undefined1 *)(param_1 + 400) = *(undefined1 *)(iVar3 + 0x71a);
        zz_0066408_(iVar3,(int)*(char *)(param_1 + 400),(float *)(param_1 + 0x20),
                    (float *)(param_1 + 0x168));
        gnt4_PSMTXMultVec_bl
                  ((float *)(iVar4 + *(short *)(&DAT_8031eeea + iVar2) * 0x30 + 0x8d4),
                   (float *)(iVar2 + -0x7fce1108),(float *)(param_1 + 0x144));
        *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
        *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
        *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
        dVar5 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x144));
        if ((double)FLOAT_80439260 < dVar5) {
          dVar6 = 1.0 / SQRT(dVar5);
          dVar6 = DOUBLE_80439268 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80439270);
          dVar6 = DOUBLE_80439268 * dVar6 * -(dVar5 * dVar6 * dVar6 - DOUBLE_80439270);
          dVar5 = (double)(float)(dVar5 * DOUBLE_80439268 * dVar6 *
                                          -(dVar5 * dVar6 * dVar6 - DOUBLE_80439270));
        }
        *(float *)(param_1 + 0x164) = (float)dVar5;
      }
      else {
        zz_00fe4b8_(param_1);
      }
    }
    else {
      zz_00fe4b8_(param_1);
    }
  }
  return;
}



// ==== 800fdc10  FUN_800fdc10 ====

/* WARNING: Removing unreachable block (ram,0x800fe2e4) */
/* WARNING: Removing unreachable block (ram,0x800fe2dc) */
/* WARNING: Removing unreachable block (ram,0x800fe2d4) */
/* WARNING: Removing unreachable block (ram,0x800fe1b8) */
/* WARNING: Removing unreachable block (ram,0x800fdc30) */
/* WARNING: Removing unreachable block (ram,0x800fdc28) */
/* WARNING: Removing unreachable block (ram,0x800fdc20) */
/* WARNING: Removing unreachable block (ram,0x800fe01c) */

void FUN_800fdc10(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  byte bVar7;
  int iVar8;
  int iVar9;
  float *pfVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  float afStack_a4 [3];
  float afStack_98 [3];
  float local_8c;
  float local_88;
  float local_84;
  float local_80;
  undefined4 local_7c;
  undefined4 local_78;
  float local_74;
  undefined4 local_70;
  undefined4 local_6c;
  float afStack_68 [3];
  float afStack_5c [5];
  
  iVar8 = *(int *)(param_1 + 0x15c);
  iVar9 = *(int *)(param_1 + 0x90);
  iVar6 = *(char *)(param_1 + 0x13) * 0x24;
  *(byte *)(iVar9 + 0x71e) = *(byte *)(iVar9 + 0x71e) & ~(byte)(1 << (int)*(char *)(iVar8 + 0x3e4));
  *(byte *)(iVar8 + 0x71e) = *(byte *)(iVar8 + 0x71e) & ~(byte)(1 << (int)*(char *)(iVar9 + 0x3e4));
  *(byte *)(iVar9 + 0x71f) = *(byte *)(iVar9 + 0x71f) & ~(byte)(1 << (int)*(char *)(iVar8 + 0x3e4));
  *(byte *)(iVar8 + 0x71f) = *(byte *)(iVar8 + 0x71f) & ~(byte)(1 << (int)*(char *)(iVar9 + 0x3e4));
  if (((byte)PTR_DAT_80433934[0xd4] == 0) ||
     (((int)*(char *)(iVar8 + 0x3e5) & ~(uint)(byte)PTR_DAT_80433934[0xd4]) == 0)) {
    iVar5 = zz_0084434_(iVar9,1);
    if (iVar5 == 0) {
      iVar5 = zz_0084434_(iVar8,0);
      if (iVar5 == 0) {
        gnt4_PSMTXMultVec_bl
                  ((float *)(iVar9 + *(short *)(&DAT_8031eeea + iVar6) * 0x30 + 0x8d4),
                   (float *)(iVar6 + -0x7fce1108),(float *)(param_1 + 0x144));
        pfVar10 = (float *)(param_1 + 0x150);
        gnt4_PSMTXMultVec_bl
                  ((float *)(iVar8 + *(char *)(param_1 + 400) * 0x30 + 0x8d4),
                   (float *)(param_1 + 0x168),pfVar10);
        uVar2 = DAT_802b0cb4;
        *(float *)(param_1 + 0x20) = *pfVar10;
        uVar3 = DAT_802b0cb8;
        *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x154);
        uVar4 = DAT_802b0cbc;
        *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x158);
        *(undefined4 *)(param_1 + 0x9c) = uVar2;
        *(undefined4 *)(param_1 + 0xa0) = uVar3;
        *(undefined4 *)(param_1 + 0xa4) = uVar4;
        gnt4_PSVECSubtract_bl(pfVar10,(float *)(param_1 + 0x144),&local_8c);
        dVar11 = gnt4_PSVECSquareMag_bl(&local_8c);
        if ((double)FLOAT_80439260 < dVar11) {
          *(float *)(param_1 + 0x38) = local_8c;
          *(float *)(param_1 + 0x3c) = local_88;
          *(float *)(param_1 + 0x40) = local_84;
        }
        *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) - (*(char *)(iVar8 + 0x749) * 3 + 1)
        ;
        if (*(short *)(param_1 + 0x1c) < 1) {
          zz_00fe4b8_(param_1);
        }
        else {
          *(undefined1 *)(iVar8 + 0x719) = 1;
          zz_00f0104_(iVar8,0x1b,7);
          dVar11 = gnt4_PSVECSquareDistance_bl((float *)(param_1 + 0x144),pfVar10);
          if ((double)FLOAT_80439260 < dVar11) {
            dVar13 = 1.0 / SQRT(dVar11);
            dVar13 = DOUBLE_80439268 * dVar13 * -(dVar11 * dVar13 * dVar13 - DOUBLE_80439270);
            dVar13 = DOUBLE_80439268 * dVar13 * -(dVar11 * dVar13 * dVar13 - DOUBLE_80439270);
            dVar11 = (double)(float)(dVar11 * DOUBLE_80439268 * dVar13 *
                                              -(dVar11 * dVar13 * dVar13 - DOUBLE_80439270));
          }
          *(float *)(param_1 + 0x160) = (float)dVar11;
          if ((*(char *)(iVar9 + 0x6cb) == '\0') && (*(char *)(iVar8 + 0x6cb) == '\0')) {
            if ((*(char *)(iVar9 + 0x1dd) == '\0') || (*(char *)(iVar8 + 0x1dd) == '\0')) {
              if (*(float *)(param_1 + 0x164) <= FLOAT_8043927c) {
                *(float *)(param_1 + 0x164) = FLOAT_8043927c;
              }
              else {
                *(float *)(param_1 + 0x164) = *(float *)(param_1 + 0x164) - FLOAT_80439280;
              }
            }
            else {
              dVar11 = gnt4_PSQUATDotProduct_bl((float *)(iVar9 + 0x1cc),(float *)(iVar8 + 0x1cc));
              if (dVar11 < (double)FLOAT_80439260) {
                *(undefined4 *)(param_1 + 0x164) = *(undefined4 *)(param_1 + 0x160);
              }
            }
          }
          else if (*(float *)(param_1 + 0x164) <= *(float *)(param_1 + 0x160)) {
            *(float *)(param_1 + 0x164) = *(float *)(param_1 + 0x160);
          }
          if (*(float *)(param_1 + 0x164) < *(float *)(param_1 + 0x160)) {
            bVar7 = *(char *)(iVar9 + 0x87) != '\0';
            if (*(char *)(iVar8 + 0x87) != '\0') {
              bVar7 = bVar7 | 2;
            }
            local_80 = *(float *)(param_1 + 0x144);
            local_7c = *(undefined4 *)(param_1 + 0x148);
            local_78 = *(undefined4 *)(param_1 + 0x14c);
            local_74 = *pfVar10;
            local_70 = *(undefined4 *)(param_1 + 0x154);
            local_6c = *(undefined4 *)(param_1 + 0x158);
            gnt4_PSVECSubtract_bl((float *)(iVar9 + 0x20),(float *)(iVar9 + 0x5e8),&local_8c);
            dVar11 = gnt4_PSVECMag_bl(&local_8c);
            if ((double)FLOAT_80439288 <= dVar11) {
              fVar1 = (float)((double)(FLOAT_80439284 * *(float *)(iVar9 + 0x204)) * dVar11);
            }
            else {
              fVar1 = FLOAT_80439284 * *(float *)(iVar9 + 0x204);
            }
            dVar13 = (double)fVar1;
            gnt4_PSVECSubtract_bl((float *)(iVar8 + 0x20),(float *)(iVar8 + 0x5e8),&local_8c);
            dVar11 = gnt4_PSVECMag_bl(&local_8c);
            if ((double)FLOAT_80439288 <= dVar11) {
              fVar1 = (float)((double)*(float *)(iVar8 + 0x204) * dVar11);
            }
            else {
              fVar1 = *(float *)(iVar8 + 0x204);
            }
            dVar11 = (double)fVar1;
            if (bVar7 == 2) {
              dVar11 = (double)(float)(dVar11 * (double)FLOAT_8043928c);
            }
            else if (bVar7 < 2) {
              if (bVar7 != 0) {
                dVar13 = (double)(float)(dVar13 * (double)FLOAT_8043928c);
              }
            }
            else if (bVar7 < 4) {
              if (*(float *)(iVar9 + 0x24) <= *(float *)(iVar8 + 0x24)) {
                if (*(float *)(iVar9 + 0x24) < *(float *)(iVar8 + 0x24)) {
                  dVar11 = (double)(float)(dVar11 * (double)FLOAT_8043928c);
                }
              }
              else {
                dVar13 = (double)(float)(dVar13 * (double)FLOAT_8043928c);
              }
            }
            gnt4_PSVECSubtract_bl(&local_74,&local_80,&local_8c);
            dVar12 = gnt4_PSVECSquareMag_bl(&local_8c);
            if (dVar12 <= (double)FLOAT_80439260) {
              return;
            }
            gnt4_PSVECNormalize_bl(&local_8c,afStack_98);
            gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x164),afStack_98,&local_8c);
            gnt4_PSVECAdd_bl(&local_80,&local_8c,afStack_a4);
            gnt4_PSVECSubtract_bl(afStack_a4,&local_74,&local_8c);
            dVar12 = gnt4_PSVECMag_bl(&local_8c);
            if (dVar12 <= (double)FLOAT_80439260) {
              return;
            }
            if (*(float *)(iVar8 + 0x204) < FLOAT_80439290) {
              dVar11 = (double)(float)(dVar12 * (double)(float)(dVar11 / (double)(float)(dVar13 + 
                                                  dVar11)));
              gnt4_PSQUATScale_bl(dVar11,afStack_98,afStack_68);
              gnt4_PSQUATScale_bl(-(double)(float)(dVar12 - dVar11),afStack_98,afStack_5c);
              zz_0084498_(iVar9,afStack_68);
              zz_0084498_(iVar8,afStack_5c);
              gnt4_PSVECNormalize_bl(afStack_5c,afStack_98);
            }
            else {
              gnt4_PSQUATScale_bl(dVar12,afStack_98,afStack_68);
              zz_0084498_(iVar9,afStack_68);
              gnt4_PSQUATScale_bl((double)FLOAT_80439264,afStack_98,afStack_98);
            }
            local_8c = FLOAT_80439260;
            local_88 = FLOAT_80439264;
            local_84 = FLOAT_80439260;
            dVar11 = gnt4_PSQUATDotProduct_bl(afStack_98,&local_8c);
            if (bVar7 == 2) {
              if ((double)FLOAT_80439298 <= dVar11) {
                *(byte *)(iVar9 + 0x732) = *(byte *)(iVar9 + 0x732) | 1;
              }
            }
            else if (bVar7 < 2) {
              if ((bVar7 != 0) && (dVar11 <= (double)FLOAT_80439294)) {
                *(byte *)(iVar8 + 0x732) = *(byte *)(iVar8 + 0x732) | 1;
              }
            }
            else if (bVar7 < 4) {
              if (*(float *)(iVar9 + 0x24) <= *(float *)(iVar8 + 0x24)) {
                if ((*(float *)(iVar9 + 0x24) < *(float *)(iVar8 + 0x24)) &&
                   ((double)FLOAT_804392a0 <= dVar11)) {
                  *(float *)(iVar9 + 0x48) = FLOAT_80439260;
                  *(byte *)(iVar9 + 0x732) = *(byte *)(iVar9 + 0x732) | 1;
                }
              }
              else if (dVar11 <= (double)FLOAT_8043929c) {
                *(float *)(iVar8 + 0x48) = FLOAT_80439260;
                *(byte *)(iVar8 + 0x732) = *(byte *)(iVar8 + 0x732) | 1;
              }
            }
            *(byte *)(iVar9 + 0x71f) =
                 *(byte *)(iVar9 + 0x71f) | (byte)(1 << (int)*(char *)(iVar8 + 0x3e4));
            *(byte *)(iVar8 + 0x71f) =
                 *(byte *)(iVar8 + 0x71f) | (byte)(1 << (int)*(char *)(iVar9 + 0x3e4));
          }
          *(byte *)(iVar9 + 0x71e) =
               *(byte *)(iVar9 + 0x71e) | (byte)(1 << (int)*(char *)(iVar8 + 0x3e4));
          *(byte *)(iVar8 + 0x71e) =
               *(byte *)(iVar8 + 0x71e) | (byte)(1 << (int)*(char *)(iVar9 + 0x3e4));
        }
      }
      else {
        zz_00fe4b8_(param_1);
      }
    }
    else {
      zz_00fe4b8_(param_1);
    }
  }
  else {
    zz_00fe4b8_(param_1);
  }
  return;
}



// ==== 800fe300  zz_00fe300_ ====

void zz_00fe300_(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  double dVar6;
  double dVar7;
  float afStack_28 [7];
  
  iVar5 = *(int *)(param_1 + 0x90);
  iVar1 = *(char *)(param_1 + 0x13) * 0x24;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar5 + *(short *)(&DAT_8031eeea + iVar1) * 0x30 + 0x8d4),
             (float *)(iVar1 + -0x7fce1108),afStack_28);
  dVar6 = gnt4_PSVECSquareDistance_bl(afStack_28,(float *)(param_1 + 0x20));
  if ((double)FLOAT_80439260 < dVar6) {
    dVar7 = 1.0 / SQRT(dVar6);
    dVar7 = DOUBLE_80439268 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80439270);
    dVar7 = DOUBLE_80439268 * dVar7 * -(dVar6 * dVar7 * dVar7 - DOUBLE_80439270);
    dVar6 = (double)(float)(dVar6 * DOUBLE_80439268 * dVar7 *
                                    -(dVar6 * dVar7 * dVar7 - DOUBLE_80439270));
  }
  if ((double)FLOAT_80439280 < dVar6) {
    uVar4 = *(undefined4 *)(param_1 + 0x38);
    uVar3 = *(undefined4 *)(param_1 + 0x3c);
    uVar2 = *(undefined4 *)(param_1 + 0x40);
    dVar6 = (double)FLOAT_804392a4;
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x174);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x178);
    *(undefined4 *)(param_1 + 0x40) = *(undefined4 *)(param_1 + 0x17c);
    zz_006c440_(dVar6,param_1,afStack_28);
    *(undefined4 *)(param_1 + 0x174) = *(undefined4 *)(param_1 + 0x38);
    *(undefined4 *)(param_1 + 0x178) = *(undefined4 *)(param_1 + 0x3c);
    *(undefined4 *)(param_1 + 0x17c) = *(undefined4 *)(param_1 + 0x40);
    *(undefined4 *)(param_1 + 0x38) = uVar4;
    *(undefined4 *)(param_1 + 0x3c) = uVar3;
    *(undefined4 *)(param_1 + 0x40) = uVar2;
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar5 + *(short *)(&DAT_8031eeea + iVar1) * 0x30 + 0x8d4),
               (float *)(iVar1 + -0x7fce1108),(float *)(param_1 + 0x144));
    *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x20);
    *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x24);
    *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x28);
  }
  else {
    *(undefined1 *)(iVar5 + 0x14a) = 0;
    zz_00f036c_(iVar5,0xc3);
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 800fe4b8  zz_00fe4b8_ ====

void zz_00fe4b8_(int param_1)

{
  byte bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  float *pfVar5;
  double dVar6;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  float afStack_1c [5];
  
  bVar1 = *(byte *)(param_1 + 0x11);
  iVar4 = *(char *)(param_1 + 0x13) * 0x24;
  gnt4_PSMTXMultVec_bl
            ((float *)(*(int *)(param_1 + 0x90) + *(short *)(&DAT_8031eeea + iVar4) * 0x30 + 0x8d4),
             (float *)(iVar4 + -0x7fce1108),afStack_1c);
  gnt4_PSVECSubtract_bl(afStack_1c,(float *)(param_1 + 0x20),&local_28);
  dVar6 = gnt4_PSVECSquareMag_bl(&local_28);
  uVar2 = DAT_802b0cac;
  if (dVar6 <= (double)FLOAT_80439260) {
    *(undefined4 *)(param_1 + 0x174) = DAT_802b0ca8;
    uVar3 = DAT_802b0cb0;
    *(undefined4 *)(param_1 + 0x178) = uVar2;
    *(undefined4 *)(param_1 + 0x17c) = uVar3;
  }
  else {
    *(float *)(param_1 + 0x174) = local_28;
    *(undefined4 *)(param_1 + 0x178) = local_24;
    *(undefined4 *)(param_1 + 0x17c) = local_20;
  }
  if (*(float *)(&DAT_8031ef20 + (uint)bVar1 * 0x1c) <= *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = *(float *)(&DAT_8031ef20 + (uint)bVar1 * 0x1c);
  }
  pfVar5 = (float *)(param_1 + 0x174);
  gnt4_PSVECNormalize_bl(pfVar5,pfVar5);
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),pfVar5,pfVar5);
  *(undefined1 *)(param_1 + 0x19) = 2;
  zz_008aff0_(param_1);
  return;
}



// ==== 800fe5e0  FUN_800fe5e0 ====

void FUN_800fe5e0(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800fe5ec  FUN_800fe5ec ====

void FUN_800fe5ec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800fe60c  FUN_800fe60c ====

void FUN_800fe60c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800fe668  zz_00fe668_ ====

bool zz_00fe668_(int param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x13] = param_3;
    puVar1[0x10] = 0x21;
    *(code **)(puVar1 + 0xc) = FUN_800fe780;
    *(code **)(puVar1 + 0x10c) = FUN_800fed10;
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



// ==== 800fe780  FUN_800fe780 ====

void FUN_800fe780(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8031efe0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800fe818  FUN_800fe818 ====

void FUN_800fe818(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  undefined *puVar8;
  int iVar9;
  undefined *puVar10;
  int iVar11;
  undefined8 uVar12;
  float local_28;
  undefined4 local_24;
  undefined4 local_20;
  
  puVar10 = &DAT_8031ef80;
  puVar8 = &DAT_8031ef38;
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar11 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  iVar7 = *(char *)(param_9 + 0x13) * 0x18;
  iVar1 = (uint)*(byte *)(param_9 + 0x11) * 0x20;
  *(undefined1 *)(param_9 + 0x98) = 5;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar5 = iVar7;
  iVar9 = iVar1;
  zz_0089100_(param_9,0,1);
  uVar2 = DAT_802b0cb8;
  puVar6 = &DAT_802b0cb4;
  *(undefined4 *)(param_9 + 0x9c) = DAT_802b0cb4;
  uVar3 = DAT_802b0cbc;
  *(undefined4 *)(param_9 + 0xa0) = uVar2;
  *(undefined4 *)(param_9 + 0xa4) = uVar3;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar11 + (char)(&DAT_8031ef39)[iVar7] * 0x30 + 0x8d4),
             (float *)(iVar7 + -0x7fce10c4),(float *)(param_9 + 0x20));
  if ((char)(&DAT_8031ef3a)[iVar7] < '\0') {
    zz_0083d60_(param_9,iVar11,1);
  }
  else {
    *(undefined4 *)(param_9 + 0x38) =
         *(undefined4 *)(iVar11 + (char)(&DAT_8031ef39)[iVar7] * 0x30 + 0x8d4);
    *(undefined4 *)(param_9 + 0x3c) =
         *(undefined4 *)(iVar11 + (char)(&DAT_8031ef39)[iVar7] * 0x30 + 0x8e4);
    *(undefined4 *)(param_9 + 0x40) =
         *(undefined4 *)(iVar11 + (char)(&DAT_8031ef39)[iVar7] * 0x30 + 0x8f4);
    if ((char)(&DAT_8031ef3b)[iVar7] < '\0') {
      gnt4_PSQUATScale_bl((double)FLOAT_804392a8,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38)
                         );
    }
  }
  local_28 = *(float *)(param_9 + 0x38);
  local_24 = *(undefined4 *)(param_9 + 0x3c);
  local_20 = *(undefined4 *)(param_9 + 0x40);
  uVar12 = gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8031ef90 + iVar1),(float *)(param_9 + 0x38),
                               (float *)(param_9 + 0x38));
  if ('\0' < (char)(&DAT_8031ef9f)[iVar1]) {
    gnt4_PSQUATScale_bl((double)FLOAT_804392ac,&local_28,&local_28);
    uVar12 = gnt4_PSVECAdd_bl((float *)(param_9 + 0x20),&local_28,(float *)(param_9 + 0x20));
  }
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8031ef90 + iVar1);
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8031ef82 + iVar1);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8031ef84 + iVar1);
  *(short *)(param_9 + 0x1c4) = (short)(char)(&DAT_8031ef86)[iVar1];
  *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
  *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(&DAT_8031ef94 + iVar1);
  if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
    *(undefined4 *)(param_9 + 200) = 0;
  }
  iVar4 = zz_0006f98_(iVar11);
  zz_0006fb4_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar4 + 0x600)
              ,*(int *)(param_9 + 0xe0),(int)(char)(&DAT_8031ef38)[iVar7],puVar6,iVar5,puVar8,iVar9,
              puVar10);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  iVar5 = zz_008ac80_(param_9,(int)(char)(&DAT_8031ef80)[iVar1]);
  if (iVar5 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    if (-1 < (char)(&DAT_8031ef9e)[iVar1]) {
      *(undefined1 *)(param_9 + 0xa8) = 1;
      zz_00c74ec_(param_9,(int)(char)(&DAT_8031ef9e)[iVar1]);
    }
    if (-1 < *(short *)(&DAT_8031ef9c + iVar1)) {
      zz_00f036c_(iVar11,(int)*(short *)(&DAT_8031ef9c + iVar1));
    }
    if (-1 < (char)(&DAT_8031ef87)[iVar1]) {
      zz_0048288_(param_9);
      zz_00aedc0_(param_9,(float *)(param_9 + 0x114),(int)(char)(&DAT_8031ef87)[iVar1],
                  *(undefined1 *)(param_9 + 0x88));
    }
  }
  return;
}



// ==== 800feae8  FUN_800feae8 ====

void FUN_800feae8(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (uint)*(byte *)(param_1 + 0x11) * 0x20;
  if (*(char *)(param_1 + 0x1d9) == '\0') {
    iVar2 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar2 == 0) {
      if (*(short *)(param_1 + 0x1c6) < 1) {
        zz_00feca8_(param_1);
        FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
      }
      else {
        *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
        *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
        *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
        if (*(short *)(param_1 + 0x1c) < 1) {
          zz_00feca8_(param_1);
          FUN_8001bda8(param_1,(undefined4 *)(param_1 + 0x20),0);
        }
        else {
          if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x144)) {
            *(float *)(param_1 + 0x44) =
                 *(float *)(param_1 + 0x44) + *(float *)(&DAT_8031ef98 + iVar1);
          }
          else {
            *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x144);
          }
          gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
          gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                              (float *)(param_1 + 0x38));
          FUN_80083874((double)*(float *)(&DAT_8031ef8c + iVar1),param_1);
          FUN_80083ad4((double)*(float *)(&DAT_8031ef88 + iVar1),param_1,
                       (char)*(undefined2 *)(&DAT_8031ef84 + iVar1));
          *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
          zz_00833ec_(param_1);
          zz_0083610_(param_1,(float *)(param_1 + 0x144));
          iVar2 = zz_0083714_(param_1);
          if (iVar2 == 0) {
            iVar2 = zz_0084170_(param_1);
            if (iVar2 != 0) {
              zz_00feca8_(param_1);
              zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),(&DAT_8031ef81)[iVar1]);
            }
          }
          else {
            zz_00feca8_(param_1);
          }
        }
      }
    }
    else {
      zz_00feca8_(param_1);
    }
  }
  else {
    zz_00feca8_(param_1);
    zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x2a0),(&DAT_8031ef81)[iVar1]);
  }
  return;
}



// ==== 800feca8  zz_00feca8_ ====

void zz_00feca8_(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 800fece4  FUN_800fece4 ====

void FUN_800fece4(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 800fecf0  FUN_800fecf0 ====

void FUN_800fecf0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 800fed10  FUN_800fed10 ====

void FUN_800fed10(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 800fed6c  zz_00fed6c_ ====

void zz_00fed6c_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8031eff0)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800fedbc  FUN_800fedbc ====

void FUN_800fedbc(int param_1,undefined4 *param_2)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x746) = 0;
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_804392b4;
  *(float *)(param_1 + 0x558) = FLOAT_804392b0;
  *(float *)(param_1 + 0x50) = fVar2;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc0);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_804392b8;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_804392b4;
  return;
}



// ==== 800feec4  FUN_800feec4 ====

void FUN_800feec4(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_804392b4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    dVar3 = DOUBLE_804392c0;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,*(uint *)(param_2 + 8) ^ 0x80000000) - dVar3);
    zz_00ff1ec_(param_1,param_2);
    zz_00b2190_(param_1,0);
  }
  return;
}



// ==== 800fef88  FUN_800fef88 ====

void FUN_800fef88(int param_1,int param_2)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)*(float *)(param_2 + 0xc),param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if ((*(char *)(param_1 + 0x1cef) == '\0') || (*(char *)(param_1 + 0x1b03) != '\0')) {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_804392b4;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) ||
     (uVar3 = FUN_800668cc((double)*(float *)(param_2 + 4),param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  if (FLOAT_804392c8 < *(float *)(param_1 + 0x44)) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800ff058  FUN_800ff058 ====

void FUN_800ff058(int param_1,int param_2)

{
  char cVar1;
  double dVar2;
  double dVar3;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x746) = 1;
  }
  zz_004cd24_(param_1,0xf);
  dVar2 = DOUBLE_804392c0;
  if ((*(char *)(param_1 + 0x1cf0) < '\0') && (*(char *)(param_1 + 0x746) != '\0')) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
    dVar3 = (double)FLOAT_804392b8;
    *(undefined1 *)(param_1 + 0x746) = 0;
    *(float *)(param_1 + 0x558) =
         (float)((double)CONCAT44(0x43300000,*(uint *)(param_2 + 8) ^ 0x80000000) - dVar2);
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
    zz_00ff1ec_(param_1,param_2);
    zz_00b2190_(param_1,0);
    return;
  }
  if (*(char *)(param_1 + 0x1d10) != '\0') {
    zz_006d144_(param_1,0xc0);
  }
  if (*(char *)(param_1 + 0x1d0f) != '\0') {
    zz_00ff1ec_(param_1,param_2);
  }
  zz_006ed8c_((double)*(float *)(param_2 + 0x10),param_1);
  if (*(float *)(param_1 + 0x760) < *(float *)(param_2 + 4)) {
    zz_006ed8c_((double)*(float *)(param_2 + 0x14),param_1);
  }
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    if (FLOAT_804392c8 < *(float *)(param_1 + 0x44)) {
      zz_00b22f4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 800ff1ec  zz_00ff1ec_ ====

void zz_00ff1ec_(int param_1,int param_2)

{
  float fVar1;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
  }
  else {
    fVar1 = *(float *)(param_1 + 0x760) *
            (float)((double)CONCAT44(0x43300000,(int)*(char *)(param_1 + 0x1d0f) ^ 0x80000000) -
                   DOUBLE_804392c0) * FLOAT_804392cc;
  }
  if (*(uint *)(param_2 + 8) != 0) {
    *(float *)(param_1 + 0x44) =
         fVar1 / (float)((double)CONCAT44(0x43300000,*(uint *)(param_2 + 8) ^ 0x80000000) -
                        DOUBLE_804392c0);
  }
  fVar1 = *(float *)(*(int *)(param_1 + 0x4b0) + 0x54);
  if (fVar1 < *(float *)(param_1 + 0x44)) {
    *(float *)(param_1 + 0x44) = fVar1;
  }
  *(undefined1 *)(param_1 + 0x1d0f) = 0;
  return;
}



// ==== 800ff2bc  zz_00ff2bc_ ====

void zz_00ff2bc_(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_zz_00ff30c__8031f000)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 800ff30c  zz_00ff30c_ ====

void zz_00ff30c_(int param_1,undefined2 *param_2)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  zz_006d144_(param_1,0xc1);
  fVar2 = FLOAT_804392b4;
  *(float *)(param_1 + 0x50) = FLOAT_804392b4;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804392d0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  *(char *)(param_1 + 0x6ea) = (char)*param_2;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(char *)(param_1 + 0x6ea) = (char)param_2[1];
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_804392b8;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_804392b4;
  return;
}



// ==== 800ff418  zz_00ff418_ ====

void zz_00ff418_(int param_1,int param_2)

{
  double dVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  gnt4_PSQUATScale_bl((double)FLOAT_804392d0,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    if (*(code **)(param_2 + 4) != (code *)0x0) {
      (**(code **)(param_2 + 4))(param_1);
    }
  }
  dVar1 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_804392c8 < dVar1) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 800ff4d4  zz_00ff4d4_ ====

void zz_00ff4d4_(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_804392d4,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (((iVar1 != 0) && ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0)) &&
     (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804392d8 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (((*(char *)(param_1 + 0x1cef) < '\0') && ((*(ushort *)(param_1 + 0x5d8) & 0xf0) != 0)) ||
     (*(char *)(param_1 + 0x1cee) != '\0')) {
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
    *(float *)(param_1 + 0x694) = FLOAT_804392d8 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 800ff5f0  zz_00ff5f0_ ====

void zz_00ff5f0_(void)

{
  zz_01d0170_(PTR_DAT_80433934 + 0x1838);
  return;
}



// ==== 800ff618  zz_00ff618_ ====

undefined4 zz_00ff618_(void)

{
  (*(code *)(&PTR_zz_00ff664__8031f010)[(char)*PTR_DAT_80433934])(PTR_DAT_80433934 + 0x1838);
  return *(undefined4 *)(PTR_DAT_80433934 + 0x185c);
}



// ==== 800ff664  zz_00ff664_ ====

void zz_00ff664_(int param_1)

{
  *PTR_DAT_80433934 = *PTR_DAT_80433934 + '\x01';
  PTR_DAT_80433934[1] = 0;
  *(undefined4 *)(param_1 + 0x24) = 0;
  *(undefined4 *)(param_1 + 0x28) = 1;
  *(undefined1 *)(param_1 + 0x15) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 1;
  return;
}



// ==== 800ff698  zz_00ff698_ ====

void zz_00ff698_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                int param_9)

{
  char cVar1;
  byte bVar2;
  bool bVar3;
  uint uVar4;
  int iVar5;
  bool bVar6;
  byte *unaff_r29;
  uint uVar7;
  byte local_28 [20];
  
  uVar7 = 0xffffffff;
  bVar3 = false;
  cVar1 = PTR_DAT_80433934[1];
  if (cVar1 == '\x01') {
    cVar1 = *(char *)(param_9 + 0x15);
    if (cVar1 == '\t') {
      bVar6 = zz_00ffa1c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      uVar7 = (uint)bVar6;
    }
    else if ((cVar1 < '\t') && ('\a' < cVar1)) {
      uVar7 = zz_00ffabc_(param_9);
    }
    if (uVar7 == 0) {
      PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + -1;
      *(undefined2 *)(PTR_DAT_80433934 + 8) = 0;
    }
  }
  else if ((cVar1 < '\x01') && (-1 < cVar1)) {
    cVar1 = *(char *)(param_9 + 0x15);
    uVar4 = zz_008bab0_(0xf,3,0);
    iVar5 = zz_008ba58_(uVar4,(int)cVar1,9,0);
    *(char *)(param_9 + 0x15) = (char)iVar5;
    if (cVar1 != *(char *)(param_9 + 0x15)) {
      zz_00f03c0_(0,0x77);
    }
    switch((int)*(char *)(param_9 + 0x15)) {
    case 0:
      uVar7 = 1;
      unaff_r29 = PTR_DAT_8043394c + 0x2b;
      break;
    case 1:
      uVar7 = 4;
      unaff_r29 = PTR_DAT_8043394c + 0x2c;
      break;
    case 2:
      uVar7 = 4;
      unaff_r29 = PTR_DAT_8043394c + 0x2d;
      break;
    case 3:
      uVar7 = 4;
      unaff_r29 = PTR_DAT_8043394c + 0x2e;
      break;
    case 4:
    case 5:
    case 6:
    case 7:
      unaff_r29 = local_28;
      uVar7 = 1;
      uVar4 = countLeadingZeros((int)(char)PTR_DAT_8043394c[0x30] &
                                1 << *(char *)(param_9 + 0x15) + -4);
      local_28[0] = (byte)(uVar4 >> 5);
      break;
    case 8:
      uVar7 = 0xffffffff;
      break;
    case 9:
      uVar7 = 0xffffffff;
    }
    if (-1 < (int)uVar7) {
      bVar2 = *unaff_r29;
      uVar4 = zz_008bab0_(0xf,3,1);
      iVar5 = zz_008ba00_(uVar4,(int)(char)bVar2,uVar7,1);
      *unaff_r29 = (byte)iVar5;
      if (*unaff_r29 != bVar2) {
        zz_00f03c0_(0,0x77);
        cVar1 = *(char *)(param_9 + 0x15);
        if (cVar1 == '\0') {
          uVar4 = countLeadingZeros((int)(char)*unaff_r29);
          gnt4_OSSetSoundMode_bl((byte)(uVar4 >> 5));
          zz_00f0f38_((int)(char)PTR_DAT_8043394c[0x2b] ^ 1);
          zz_026e0e0_((int)(char)PTR_DAT_8043394c[0x2b]);
        }
        else {
          iVar5 = (int)cVar1;
          if ((iVar5 < 4) || (7 < iVar5)) {
            if (cVar1 == '\x01') {
              zz_00e9c78_((double)FLOAT_804392e0,param_2,param_3,param_4,param_5,param_6,param_7,
                          param_8,2);
            }
          }
          else {
            bVar2 = (byte)(1 << iVar5 + -4);
            if (*unaff_r29 == 0) {
              PTR_DAT_8043394c[0x30] = PTR_DAT_8043394c[0x30] | bVar2;
              zz_010d880_(*(char *)(param_9 + 0x15) + -4,5);
            }
            else {
              PTR_DAT_8043394c[0x30] = PTR_DAT_8043394c[0x30] & ~bVar2;
            }
            PTR_DAT_8043394c[*(char *)(param_9 + 0x15) * 8 + -0x19] = *unaff_r29 ^ 1;
          }
        }
      }
    }
    uVar4 = zz_008b980_(0xf);
    if (uVar4 == 0) {
      uVar4 = zz_008b810_(0xf);
      if ((uVar4 != 0) && (uVar7 == 0xffffffff)) {
        zz_00f0468_(0,0x7a,0);
        PTR_DAT_80433934[1] = PTR_DAT_80433934[1] + '\x01';
        PTR_DAT_80433934[2] = 0;
        *(undefined2 *)(PTR_DAT_80433934 + 8) = 0x3c;
      }
    }
    else {
      zz_00f0468_(0,0x7b,0);
      bVar3 = true;
    }
  }
  if (bVar3) {
    *PTR_DAT_80433934 = *PTR_DAT_80433934 + '\x01';
  }
  return;
}



// ==== 800ffa04  zz_00ffa04_ ====

void zz_00ffa04_(int param_1)

{
  *(undefined4 *)(param_1 + 0x24) = 1;
  *(undefined4 *)(param_1 + 0x28) = 0;
  *(undefined4 *)(param_1 + 0x2c) = 0;
  return;
}



// ==== 800ffa1c  zz_00ffa1c_ ====

bool zz_00ffa1c_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  short sVar1;
  
  if (PTR_DAT_80433934[2] == '\0') {
    PTR_DAT_80433934[2] = 1;
    zz_008bbd0_(0,1);
    zz_008bbd0_(0,2);
    zz_008bbd0_(1,2);
    zz_008bbd0_(2,2);
    zz_008bbd0_(3,2);
    zz_00e9c78_((double)FLOAT_804392e0,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2);
  }
  sVar1 = *(short *)(PTR_DAT_80433934 + 8);
  *(short *)(PTR_DAT_80433934 + 8) = sVar1 + -1;
  return 0 < (short)(sVar1 + -1);
}



// ==== 800ffabc  zz_00ffabc_ ====

int zz_00ffabc_(int param_1)

{
  char cVar1;
  short sVar2;
  int iVar3;
  
  iVar3 = 1;
  cVar1 = PTR_DAT_80433934[2];
  if (cVar1 == '\x01') {
    iVar3 = zz_01f1874_();
    if (iVar3 == 0) {
      *(undefined4 *)(param_1 + 0x2c) = 1;
      zz_00e9ce4_((double)FLOAT_804392e4,2,0x20,1,DAT_8031a0e8);
    }
  }
  else if (((cVar1 < '\x01') && (-1 < cVar1)) &&
          (sVar2 = *(short *)(PTR_DAT_80433934 + 8), *(short *)(PTR_DAT_80433934 + 8) = sVar2 + -1,
          (short)(sVar2 + -1) < 1)) {
    PTR_DAT_80433934[2] = PTR_DAT_80433934[2] + '\x01';
    *(undefined4 *)(param_1 + 0x2c) = 0;
    *(undefined2 *)(PTR_DAT_80433934 + 8) = 0;
    zz_01f17fc_();
    zz_00e9ce4_((double)FLOAT_804392e4,2,0x20,1,DAT_8031a0d4);
  }
  return iVar3;
}



// ==== 800ffba8  zz_00ffba8_ ====

void zz_00ffba8_(int param_1,undefined1 param_2)

{
  char cVar1;
  undefined1 *puVar2;
  int iVar3;
  
  puVar2 = zz_0088aa0_(param_1,3,8,0,6);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x83] = 0x10;
    puVar2[0x10] = 0x54;
    puVar2[0x11] = param_2;
    *(code **)(puVar2 + 0xc) = FUN_800ffe48;
    *(code **)(puVar2 + 0x10c) = FUN_8010044c;
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
    iVar3 = (uint)(byte)puVar2[0x11] * 0x30;
    gnt4_PSMTXMultVec_bl
              ((float *)(param_1 + (char)(&DAT_8031f04a)[iVar3] * 0x30 + 0x8d4),
               (float *)(iVar3 + -0x7fce0fb4),(float *)(puVar2 + 0x20));
    if (*(char *)(param_1 + 0x587) == '\x02') {
      cVar1 = (&DAT_8031f074)[iVar3];
      if (cVar1 == '\x01') {
        *(undefined4 *)(puVar2 + 0x38) =
             *(undefined4 *)(param_1 + (char)(&DAT_8031f04a)[iVar3] * 0x30 + 0x8d8);
        *(undefined4 *)(puVar2 + 0x3c) =
             *(undefined4 *)(param_1 + (char)(&DAT_8031f04a)[iVar3] * 0x30 + 0x8e8);
        *(undefined4 *)(puVar2 + 0x40) =
             *(undefined4 *)(param_1 + (char)(&DAT_8031f04a)[iVar3] * 0x30 + 0x8f8);
      }
      else if (cVar1 < '\x01') {
        if (-1 < cVar1) {
          *(undefined4 *)(puVar2 + 0x38) =
               *(undefined4 *)(param_1 + (char)(&DAT_8031f04a)[iVar3] * 0x30 + 0x8d4);
          *(undefined4 *)(puVar2 + 0x3c) =
               *(undefined4 *)(param_1 + (char)(&DAT_8031f04a)[iVar3] * 0x30 + 0x8e4);
          *(undefined4 *)(puVar2 + 0x40) =
               *(undefined4 *)(param_1 + (char)(&DAT_8031f04a)[iVar3] * 0x30 + 0x8f4);
        }
      }
      else if (cVar1 < '\x03') {
        *(undefined4 *)(puVar2 + 0x38) =
             *(undefined4 *)(param_1 + (char)(&DAT_8031f04a)[iVar3] * 0x30 + 0x8dc);
        *(undefined4 *)(puVar2 + 0x3c) =
             *(undefined4 *)(param_1 + (char)(&DAT_8031f04a)[iVar3] * 0x30 + 0x8ec);
        *(undefined4 *)(puVar2 + 0x40) =
             *(undefined4 *)(param_1 + (char)(&DAT_8031f04a)[iVar3] * 0x30 + 0x8fc);
      }
      if ((&DAT_8031f075)[iVar3] == '\x01') {
        gnt4_PSQUATScale_bl((double)FLOAT_804392e8,(float *)(puVar2 + 0x38),(float *)(puVar2 + 0x38)
                           );
      }
    }
    else {
      zz_0083d60_((int)puVar2,param_1,0);
    }
    gnt4_PSVECNormalize_bl((float *)(puVar2 + 0x38),(float *)(puVar2 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8031f058 + iVar3),(float *)(puVar2 + 0x38),
                        (float *)(puVar2 + 0x38));
  }
  return;
}



// ==== 800ffe48  FUN_800ffe48 ====

void FUN_800ffe48(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8031f138)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 800ffee0  FUN_800ffee0 ====

void FUN_800ffee0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  undefined8 uVar8;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x30;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar6 = iVar5;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  fVar1 = FLOAT_804392ec;
  *(undefined1 *)(param_9 + 0x98) = 5;
  fVar2 = FLOAT_804392f0;
  *(float *)(param_9 + 0xa0) = fVar1;
  *(float *)(param_9 + 0x9c) = fVar1;
  *(float *)(param_9 + 0xa4) = fVar2;
  uVar8 = zz_0048288_(param_9);
  *(undefined2 *)(param_9 + 0x1c) = 600;
  iVar3 = zz_008ac80_(param_9,(int)(char)(&DAT_8031f04b)[iVar5]);
  if (iVar3 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    iVar4 = zz_0006f78_(param_9);
    iVar7 = 0;
    iVar3 = param_9;
    do {
      uVar8 = zz_000726c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                          *(int *)(iVar3 + 0xe0),(float *)(uint)(byte)(&DAT_8031f048)[iVar5],
                          (int)*(char *)(param_9 + 0x88),iVar6,in_r8,in_r9,in_r10);
      iVar7 = iVar7 + 1;
      iVar3 = iVar3 + 4;
    } while (iVar7 < 5);
    zz_000726c_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                *(int *)(param_9 + 0xf4),(float *)(uint)(byte)(&DAT_8031f049)[iVar5],
                (int)*(char *)(param_9 + 0x88),iVar6,in_r8,in_r9,in_r10);
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8031f058 + iVar5),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    fVar1 = FLOAT_804392f0;
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8031f058 + iVar5);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined4 *)(&DAT_8031f05c + iVar5);
    *(undefined2 *)(param_9 + 0x74) = 0;
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    *(undefined1 *)(param_9 + 0x144) = 0;
    *(undefined1 *)(param_9 + 0x145) = 0;
    *(float *)(param_9 + 0x148) = fVar1;
    zz_00f036c_(param_9,199);
    FUN_80100050(param_9);
  }
  return;
}



// ==== 80100050  FUN_80100050 ====

/* WARNING: Removing unreachable block (ram,0x801002fc) */
/* WARNING: Removing unreachable block (ram,0x801002f4) */
/* WARNING: Removing unreachable block (ram,0x80100068) */
/* WARNING: Removing unreachable block (ram,0x80100060) */

void FUN_80100050(int param_1)

{
  float fVar1;
  char cVar2;
  float fVar3;
  int iVar4;
  uint uVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  
  *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x11c);
  *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 300);
  *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x13c);
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x74) = *(short *)(param_1 + 0x74) + 0xccc;
  if (*(char *)(param_1 + 0x145) != '\0') {
    dVar8 = (double)FLOAT_804392ec;
    dVar9 = (double)FLOAT_804392f4;
    iVar6 = *(char *)(param_1 + 0x144) + 4;
    iVar7 = iVar6 / 5 + (iVar6 >> 0x1f);
    iVar6 = iVar6 + (iVar7 - (iVar7 >> 0x1f)) * -5;
    for (iVar7 = 0; iVar7 < *(char *)(param_1 + 0x145); iVar7 = iVar7 + 1) {
      iVar4 = param_1 + iVar6 * 0x14;
      fVar1 = (float)((double)*(float *)(iVar4 + 0x158) + dVar8);
      *(float *)(iVar4 + 0x158) = fVar1;
      if ((double)fVar1 <= dVar9) {
        FUN_80100324((float *)(iVar4 + 0x14c));
      }
      else {
        *(char *)(param_1 + 0x145) = *(char *)(param_1 + 0x145) + -1;
      }
      iVar6 = iVar6 + 4;
      iVar4 = iVar6 / 5 + (iVar6 >> 0x1f);
      iVar6 = iVar6 + (iVar4 - (iVar4 >> 0x1f)) * -5;
    }
  }
  fVar3 = FLOAT_804392f0;
  fVar1 = *(float *)(param_1 + 0x148) - FLOAT_804392ec;
  *(float *)(param_1 + 0x148) = fVar1;
  if ((fVar1 <= fVar3) && (*(char *)(param_1 + 0x145) < '\x05')) {
    *(float *)(param_1 + 0x148) = FLOAT_804392f8;
    cVar2 = *(char *)(param_1 + 0x144);
    iVar7 = param_1 + cVar2 * 0x14;
    *(float *)(iVar7 + 0x158) = fVar3;
    uVar5 = zz_00055fc_();
    *(short *)(iVar7 + 0x15c) = (short)(uVar5 << 0xb);
    *(undefined1 *)(iVar7 + 0x15e) = 0;
    FUN_80100324((float *)(iVar7 + 0x14c));
    iVar6 = cVar2 + 1;
    iVar7 = iVar6 / 5 + (iVar6 >> 0x1f);
    *(char *)(param_1 + 0x144) = (char)iVar6 + ((char)iVar7 - (char)(iVar7 >> 0x1f)) * -5;
    *(char *)(param_1 + 0x145) = *(char *)(param_1 + 0x145) + '\x01';
  }
  iVar7 = (uint)*(byte *)(param_1 + 0x11) * 0x30;
  if ((0 < *(short *)(param_1 + 0x1c)) &&
     (iVar6 = zz_0083244_((float *)(param_1 + 0x20)), iVar6 == 0)) {
    if (*(char *)(param_1 + 0x1d9) == '\0') {
      FUN_80083874((double)*(float *)(&DAT_8031f064 + iVar7),param_1);
      FUN_80083ad4((double)*(float *)(&DAT_8031f060 + iVar7),param_1,
                   (char)*(undefined4 *)(&DAT_8031f05c + iVar7));
      zz_00833ec_(param_1);
      zz_0083524_(param_1);
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(iVar7 + -0x7fce0f98),
                          (float *)(param_1 + 0x58));
      iVar6 = zz_0083714_(param_1);
      if (iVar6 == 0) {
        iVar6 = zz_0084170_(param_1);
        if (iVar6 == 0) {
          return;
        }
        *(undefined1 *)(param_1 + 0x18) = 2;
        if ((&DAT_8031f076)[iVar7] == '\0') {
          return;
        }
        zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),0xc);
        return;
      }
    }
    else if ((&DAT_8031f076)[iVar7] != '\0') {
      zz_0085e00_(param_1,(undefined4 *)(param_1 + 0x20),0xc);
    }
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  zz_008aff0_(param_1);
  return;
}



// ==== 80100324  FUN_80100324 ====

void FUN_80100324(float *param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  
  fVar7 = FLOAT_804392fc;
  iVar5 = *(char *)((int)param_1 + 0x12) * 0x10;
  fVar4 = *(float *)(&DAT_8031f148 + iVar5);
  fVar1 = *(float *)(&DAT_8031f14c + iVar5);
  fVar2 = *(float *)(&DAT_8031f150 + iVar5);
  fVar3 = *(float *)(&DAT_8031f154 + iVar5);
  if ((param_1[3] == fVar4) || (FLOAT_804392fc == fVar4)) {
    *param_1 = fVar1;
    param_1[1] = fVar2;
    param_1[2] = fVar3;
    return;
  }
  fVar6 = param_1[3] - fVar4;
  iVar5 = (*(char *)((int)param_1 + 0x12) + 1) * 0x10;
  fVar4 = *(float *)(&DAT_8031f148 + iVar5) - fVar4;
  *param_1 = ((*(float *)(&DAT_8031f14c + iVar5) - fVar1) / fVar4) * fVar6 + fVar1;
  param_1[1] = ((*(float *)(&DAT_8031f150 + iVar5) - fVar2) / fVar4) * fVar6 + fVar2;
  param_1[2] = ((*(float *)(&DAT_8031f154 + iVar5) - fVar3) / fVar4) * fVar6 + fVar3;
  fVar1 = *(float *)(&DAT_8031f148 + iVar5);
  if ((param_1[3] <= fVar1) && (fVar7 != fVar1)) {
    return;
  }
  *(char *)((int)param_1 + 0x12) = *(char *)((int)param_1 + 0x12) + '\x01';
  return;
}



// ==== 801003f0  FUN_801003f0 ====

void FUN_801003f0(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8010042c  FUN_8010042c ====

void FUN_8010042c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8010044c  FUN_8010044c ====

/* WARNING: Removing unreachable block (ram,0x801005d0) */
/* WARNING: Removing unreachable block (ram,0x801005c8) */
/* WARNING: Removing unreachable block (ram,0x80100464) */
/* WARNING: Removing unreachable block (ram,0x8010045c) */

void FUN_8010044c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  double dVar9;
  float afStack_a8 [12];
  float afStack_78 [12];
  undefined4 local_48;
  uint uStack_44;
  
  dVar9 = (double)FLOAT_80439300;
  iVar1 = *(char *)(param_9 + 0x144) + 4;
  iVar5 = iVar1 / 5 + (iVar1 >> 0x1f);
  iVar1 = iVar1 + (iVar5 - (iVar5 >> 0x1f)) * -5;
  dVar8 = DOUBLE_80439308;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x145); iVar5 = iVar5 + 1) {
    local_48 = 0x43300000;
    iVar4 = param_9 + iVar1 * 0x14;
    iVar3 = *(int *)(param_9 + iVar1 * 4 + 0xe0);
    uStack_44 = (int)*(short *)(iVar4 + 0x15c) ^ 0x80000000;
    gnt4_PSMTXRotRad_bl((double)(float)(dVar9 * (double)(float)((double)CONCAT44(0x43300000,
                                                                                 uStack_44) - dVar8)
                                       ),afStack_78,0x7a);
    gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),afStack_78,afStack_78);
    dVar7 = (double)*(float *)(iVar4 + 0x150);
    param_3 = (double)*(float *)(iVar4 + 0x154);
    gnt4_PSMTXScale_bl((double)*(float *)(iVar4 + 0x14c),dVar7,param_3,afStack_a8);
    pfVar2 = afStack_78;
    uVar6 = gnt4_PSMTXConcat_bl(pfVar2,afStack_a8,pfVar2);
    zz_00076d0_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,afStack_78,
                (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar3,0x44);
    iVar1 = iVar1 + 4;
    iVar3 = iVar1 / 5 + (iVar1 >> 0x1f);
    iVar1 = iVar1 + (iVar3 - (iVar3 >> 0x1f)) * -5;
  }
  local_48 = 0x43300000;
  uStack_44 = (int)*(short *)(param_9 + 0x74) ^ 0x80000000;
  dVar8 = (double)FLOAT_80439300;
  iVar5 = *(int *)(param_9 + 0xf4);
  gnt4_PSMTXRotRad_bl((double)(float)(dVar8 * (double)(float)((double)CONCAT44(0x43300000,uStack_44)
                                                             - DOUBLE_80439308)),afStack_78,0x7a);
  pfVar2 = afStack_78;
  uVar6 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar2,pfVar2);
  zz_00076d0_(uVar6,dVar8,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,afStack_78,
              (undefined *)pfVar2,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar5,0x44);
  return;
}



// ==== 801005ec  zz_01005ec_ ====

void zz_01005ec_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x14;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 8;
    *(code **)(puVar1 + 0xc) = FUN_801006f4;
    *(code **)(puVar1 + 0x10c) = FUN_801009e4;
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



// ==== 801006f4  FUN_801006f4 ====

void FUN_801006f4(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8031f210)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 80100780  FUN_80100780 ====

void FUN_80100780(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
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
    *(undefined2 *)(param_9 + 0x1e) = 0;
    *(code **)(param_9 + 0x100) = FUN_80100b18;
    uVar7 = zz_0089100_(param_9,1,1);
    iVar3 = zz_0006f78_(*(int *)(param_9 + 0x90));
    iVar5 = (int)*(char *)(param_9 + 0x13);
    pcVar4 = (char *)(int)(char)(&DAT_8031f1e8)[*(char *)(param_9 + 0x11) * 0x14];
    uVar7 = zz_0007198_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                        *(int *)(param_9 + 0xe0),pcVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
    iVar6 = 0;
    iVar3 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *(int *)(iVar3 + 0x10);
    }
    for (; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
      uVar7 = gnt4_HSD_JObjSetFlagsAll
                        (uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,0x10,
                         pcVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(iVar3 + 8);
      }
    }
    zz_0100c08_(param_9,(short)*(char *)(param_9 + 0x11),pcVar4,iVar5,in_r7,in_r8,in_r9,in_r10);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  }
  return;
}



// ==== 801008e8  FUN_801008e8 ====

void FUN_801008e8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_9 + 0x8c);
  cVar1 = *(char *)(iVar4 + 0x6f7);
  *(short *)(param_9 + 0x7e) = (cVar1 + 2) * 0x100;
  zz_0100df0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,(int)cVar1,
              param_11,param_12,param_13,param_14,param_15,param_16);
  uVar3 = 2;
  zz_00f0104_(*(int *)(param_9 + 0x90),0x16,2);
  if (*(char *)(iVar4 + 0x6f7) != '\0') {
    sVar2 = *(short *)(param_9 + 0x1c) + -1;
    *(short *)(param_9 + 0x1c) = sVar2;
    if (sVar2 < 1) {
      zz_0100c08_(param_9,(short)*(char *)(param_9 + 0x11),uVar3,param_12,param_13,param_14,param_15
                  ,param_16);
    }
  }
  if (*(short *)(param_9 + 0x1e) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 80100988  FUN_80100988 ====

void FUN_80100988(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8010099c  FUN_8010099c ====

void FUN_8010099c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801009e4  FUN_801009e4 ====

/* WARNING: Removing unreachable block (ram,0x80100a90) */

void FUN_801009e4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  float *pfVar4;
  int iVar5;
  int iVar6;
  
  iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(iVar2 + 0x10);
  }
  iVar6 = 0;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    if (((int)*(short *)(param_9 + 0x1e) & 1 << iVar5) != 0) {
      pfVar4 = (float *)(*(int *)(param_9 + 0x54) + iVar6);
      if (iVar2 == 0) {
        param_11 = &DAT_80439318;
        param_1 = gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                   &DAT_80439310,0x495,&DAT_80439318,param_12,param_13,param_14,
                                   param_15,param_16);
      }
      if (pfVar4 == (float *)0x0) {
        param_11 = &DAT_80439320;
        gnt4___assert_bl(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                         &DAT_80439310,0x496,&DAT_80439320,param_12,param_13,param_14,param_15,
                         param_16);
      }
      param_1 = gnt4_PSMTXCopy_bl(pfVar4,(float *)(iVar2 + 0x44));
      *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
      if (iVar2 != 0) {
        uVar3 = *(uint *)(iVar2 + 0x14);
        bVar1 = false;
        if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
          bVar1 = true;
        }
        if (!bVar1) {
          param_1 = gnt4_HSD_JObjSetMtxDirtySub_bl
                              (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2
                               ,uVar3,param_11,param_12,param_13,param_14,param_15,param_16);
        }
      }
    }
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 8);
    }
    iVar6 = iVar6 + 0x60;
  }
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x44);
  return;
}



// ==== 80100b18  FUN_80100b18 ====

void FUN_80100b18(int param_1)

{
  int iVar1;
  float *pfVar2;
  int iVar3;
  float afStack_48 [14];
  
  iVar1 = *(char *)(param_1 + 0x11) * 0x14;
  zz_00455fc_((float *)(*(int *)(param_1 + 0x8c) + (char)(&DAT_8031f1e9)[iVar1] * 0x30 + 0x8d4),
              afStack_48,(float *)(iVar1 + -0x7fce0e10));
  iVar1 = 0;
  iVar3 = 0;
  while( true ) {
    if (*(char *)(param_1 + 0x13) <= iVar1) break;
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar1) != 0) {
      pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar3);
      zz_00457d4_('y',afStack_48,pfVar2,*(short *)((int)pfVar2 + 0x52));
      zz_00455fc_(pfVar2,pfVar2,pfVar2 + 0x11);
      zz_00456a0_(pfVar2,pfVar2,pfVar2 + 0xe);
    }
    iVar3 = iVar3 + 0x60;
    iVar1 = iVar1 + 1;
  }
  return;
}



// ==== 80100c08  zz_0100c08_ ====

void zz_0100c08_(int param_1,ushort param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
                ,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  short sVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  float *pfVar5;
  int iVar6;
  float *pfVar7;
  int iVar8;
  undefined8 uVar9;
  double dVar10;
  double dVar11;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  iVar8 = 0;
  while( true ) {
    fVar2 = FLOAT_80439324;
    if (*(char *)(param_1 + 0x13) <= iVar8) break;
    if (((int)*(short *)(param_1 + 0x1e) & 1 << iVar8) == 0) {
      pfVar7 = (float *)(*(int *)(param_1 + 0x54) + iVar8 * 0x60);
      *(ushort *)((int)pfVar7 + 0x56) = param_2;
      *(undefined2 *)(param_1 + 0x1c) = 3;
      *(ushort *)(param_1 + 0x1e) = *(ushort *)(param_1 + 0x1e) | (ushort)(1 << iVar8);
      pfVar7[0x17] = fVar2;
      *(undefined2 *)(pfVar7 + 0x16) = 0;
      *(undefined2 *)((int)pfVar7 + 0x5a) = *(undefined2 *)(&DAT_8031f1ea + (uint)param_2 * 0x14);
      *(undefined2 *)(pfVar7 + 0x14) = 0;
      uVar3 = zz_00055fc_();
      *(short *)((int)pfVar7 + 0x52) = (short)(uVar3 << 8);
      *(undefined2 *)(pfVar7 + 0x15) = 0;
      gnt4_PSMTXIdentity_bl(pfVar7);
      uVar3 = zz_00055fc_();
      sVar1 = (short)(uVar3 << 8);
      iVar6 = (int)sVar1;
      zz_00457d4_('y',pfVar7,pfVar7,sVar1);
      pfVar7[0x11] = pfVar7[2];
      pfVar7[0x12] = pfVar7[6];
      pfVar7[0x13] = pfVar7[10];
      uVar3 = zz_00055fc_();
      gnt4_PSQUATScale_bl((double)(pfVar7[0x17] *
                                  (FLOAT_80439324 +
                                  (float)((double)CONCAT44(0x43300000,uVar3 & 0xff) -
                                         DOUBLE_80439330) / FLOAT_80439328)),pfVar7 + 0x11,
                          pfVar7 + 0x11);
      uVar3 = zz_00055fc_();
      dVar11 = DOUBLE_80439330;
      pfVar5 = pfVar7 + 0xe;
      dVar10 = (double)(float)((double)CONCAT44(0x43300000,uVar3 & 0xff) - DOUBLE_80439330);
      pfVar7[0x12] = pfVar7[0x17] * (float)(dVar10 / (double)FLOAT_8043932c);
      zz_0018f88_((int *)(pfVar7 + 0xc),(int)(&PTR_DAT_8031f1ec)[(uint)param_2 * 5],pfVar5);
      uVar9 = gnt4_PSQUATScale_bl((double)pfVar7[0x17],pfVar7 + 0xe,pfVar7 + 0xe);
      iVar4 = *(int *)(*(int *)(param_1 + 0xe0) + 0xc);
      if (iVar4 == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = *(int *)(iVar4 + 0x10);
      }
      if (0 < iVar8) {
        do {
          if (iVar4 == 0) {
            iVar4 = 0;
          }
          else {
            iVar4 = *(int *)(iVar4 + 8);
          }
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      gnt4_HSD_JObjClearFlagsAll
                (uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,iVar4,0x10,(undefined *)pfVar5,
                 iVar6,param_5,param_6,param_7,param_8);
      iVar8 = (int)*(char *)(param_1 + 0x13);
    }
    iVar8 = iVar8 + 1;
  }
  return;
}



// ==== 80100df0  zz_0100df0_ ====

int zz_0100df0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
               double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
               undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
               undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  int iVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  iVar2 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = *(int *)(iVar2 + 0x10);
  }
  iVar5 = 0;
  iVar6 = 0;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar5) break;
    puVar3 = (undefined *)(1 << iVar5);
    if (((int)*(short *)(param_9 + 0x1e) & (uint)puVar3) != 0) {
      iVar4 = *(int *)(param_9 + 0x54) + iVar6;
      sVar1 = *(short *)(iVar4 + 0x58) + 1;
      *(short *)(iVar4 + 0x58) = sVar1;
      if (sVar1 < *(short *)(iVar4 + 0x5a)) {
        *(short *)(iVar4 + 0x52) = *(short *)(iVar4 + 0x52) + *(short *)(param_9 + 0x7e);
        zz_0018fd8_((int *)(iVar4 + 0x30),(int)*(short *)(iVar4 + 0x58),(float *)(iVar4 + 0x38));
        param_1 = gnt4_PSQUATScale_bl((double)*(float *)(iVar4 + 0x5c),(float *)(iVar4 + 0x38),
                                      (float *)(iVar4 + 0x38));
      }
      else {
        *(ushort *)(param_9 + 0x1e) = *(ushort *)(param_9 + 0x1e) & ~(ushort)puVar3;
        param_1 = gnt4_HSD_JObjSetFlagsAll
                            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                             0x10,puVar3,param_12,param_13,param_14,param_15,param_16);
      }
    }
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 8);
    }
    iVar6 = iVar6 + 0x60;
    iVar5 = iVar5 + 1;
  }
  return (int)*(short *)(param_9 + 0x1e);
}



// ==== 80100ff0  FUN_80100ff0 ====

void FUN_80100ff0(int param_1)

{
  *(undefined1 *)(param_1 + 0x6e8) = 0x80;
  *(byte *)(param_1 + 0x6e9) = *(byte *)(param_1 + 0x6e9) | 0x80;
  zz_00f59ac_(param_1);
  zz_00c74ec_(param_1,0x2b);
  zz_00c74ec_(param_1,0x2c);
  zz_00c74ec_(param_1,0x2d);
  *(undefined1 *)(param_1 + 0x707) = 0x18;
  return;
}



// ==== 80101060  FUN_80101060 ====

void FUN_80101060(int param_1)

{
  uint uVar1;
  
  uVar1 = *(uint *)(param_1 + 0x5e0);
  if ((((uVar1 & 0x800) != 0) || ((uVar1 & 0x40) == 0)) && ((uVar1 & 0x20) == 0)) {
    *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 0x18;
  }
  zz_01485e8_(param_1,(float *)(param_1 + 0x144));
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_80439340) * FLOAT_80439338);
  }
  return;
}



// ==== 80101110  FUN_80101110 ====

void FUN_80101110(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_803204e8)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80101154  FUN_80101154 ====

void FUN_80101154(int param_1)

{
  zz_0137540_(param_1,3);
  return;
}



// ==== 80101180  FUN_80101180 ====

void FUN_80101180(int param_1)

{
  (*(code *)(&PTR_FUN_803204fc)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801011bc  FUN_801011bc ====

void FUN_801011bc(int param_1)

{
  (*(code *)(&PTR_zz_0101540__80320508)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801011f8  FUN_801011f8 ====

void FUN_801011f8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8032051c)[*(char *)(param_1 + 0x544)])();
  return;
}



// ==== 80101240  FUN_80101240 ====

void FUN_80101240(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80439348;
  if ((*(char *)(param_1 + 0x7ce) == '\x0f') || (*(char *)(param_1 + 0x7ce) == '\x10')) {
    *(undefined4 *)(param_1 + 0x44) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x58);
    *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x5c);
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x70);
    zz_01014cc_(param_1);
    zz_01012cc_(param_1);
  }
  else {
    *(undefined1 *)(param_1 + 0x581) = 2;
    zz_0101540_(param_1);
  }
  return;
}



// ==== 801012cc  zz_01012cc_ ====

void zz_01012cc_(int param_1)

{
  *(undefined1 *)(param_1 + 0x544) = 1;
  zz_0101c00_(param_1);
  zz_004beb8_((double)FLOAT_8043934c,param_1,1,2,0xf,0xc,2);
  zz_004beb8_((double)FLOAT_8043934c,param_1,6,2,0x1b,0xc,2);
  return;
}



// ==== 80101340  FUN_80101340 ====

void FUN_80101340(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,7);
  zz_01014cc_(param_1);
  if ((*(char *)(param_1 + 0x1cee) == '\0') && (FLOAT_80439348 < *(float *)(param_1 + 0x558))) {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x6ec) < '\x01') {
    dVar1 = (double)FLOAT_8043934c;
    *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
    zz_004beb8_(dVar1,param_1,1,2,0x11,0xffffffff,0xffffffff);
  }
  else {
    zz_0101c1c_(param_1);
    zz_004beb8_((double)FLOAT_8043934c,param_1,1,2,0x10,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8010140c  FUN_8010140c ====

void FUN_8010140c(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,7);
  zz_01014cc_(param_1);
  if ((*(uint *)(param_1 + 0x5d4) & 0x20) == 0) {
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a6fc_(param_1,0x10);
      dVar1 = (double)FLOAT_80439350;
      *(undefined1 *)(param_1 + 0x540) = 1;
      zz_004beb8_(dVar1,param_1,1,0,0xb,0xffffffff,0xffffffff);
      zz_006a750_(param_1,0x10);
      *(undefined1 *)(param_1 + 0x544) = 2;
      *(undefined1 *)(param_1 + 0x588) = 1;
    }
  }
  else {
    zz_01012cc_(param_1);
  }
  return;
}



// ==== 801014cc  zz_01014cc_ ====

void zz_01014cc_(int param_1)

{
  float fVar1;
  
  zz_0066ac0_(param_1,0);
  zz_0066e40_(param_1,2);
  fVar1 = FLOAT_80439348;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  if (*(float *)(param_1 + 0x44) < fVar1) {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  FUN_80067310((double)FLOAT_80439354,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  return;
}



// ==== 80101540  zz_0101540_ ====

void zz_0101540_(int param_1)

{
  zz_0101b68_(param_1);
  (*(code *)(&PTR_FUN_80434498)[*(char *)(param_1 + 0x545)])(param_1);
  (*(code *)(&PTR_FUN_80434490)[*(char *)(param_1 + 0x544)])(param_1);
  (*(code *)(&PTR_FUN_80320528)[*(char *)(param_1 + 0x540)])(param_1);
  return;
}



// ==== 801015d0  FUN_801015d0 ====

void FUN_801015d0(int param_1)

{
  double dVar1;
  
  dVar1 = (double)FLOAT_8043934c;
  *(char *)(param_1 + 0x545) = *(char *)(param_1 + 0x545) + '\x01';
  zz_004beb8_(dVar1,param_1,4,2,0x1a,4,2);
  return;
}



// ==== 80101614  FUN_80101614 ====

void FUN_80101614(int param_1)

{
  zz_004cd24_(param_1,4);
  return;
}



// ==== 80101638  FUN_80101638 ====

void FUN_80101638(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80439358;
  *(undefined1 *)(param_1 + 0x540) = 1;
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  zz_0101c00_(param_1);
  zz_004beb8_((double)FLOAT_8043934c,param_1,1,2,(int)*(char *)(param_1 + 0x6ea),4,2);
  return;
}



// ==== 801016a0  FUN_801016a0 ====

void FUN_801016a0(int param_1)

{
  float fVar1;
  double dVar2;
  
  fVar1 = FLOAT_80439348;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  if ((*(float *)(param_1 + 0x560) < fVar1) ||
     ((*(char *)(param_1 + 0x1cee) != '\0' && (*(short *)(param_1 + 0x54a) != 0)))) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0101c1c_(param_1);
    dVar2 = (double)FLOAT_8043934c;
    *(undefined2 *)(param_1 + 0x54c) = 5;
    zz_004beb8_(dVar2,param_1,1,2,*(char *)(param_1 + 0x6ea) + 5,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8010173c  FUN_8010173c ====

void FUN_8010173c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if ((*(uint *)(param_1 + 0x5d4) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x745) = 1;
  }
  fVar1 = FLOAT_80439348;
  *(undefined2 *)(param_1 + 0x54c) = 5;
  fVar2 = FLOAT_8043935c;
  if (*(float *)(param_1 + 0x558) <= fVar1) {
    if (*(char *)(param_1 + 0x6ec) < '\x01') {
      dVar4 = (double)FLOAT_8043934c;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x55c) = fVar2;
      *(undefined2 *)(param_1 + 0x54c) = 10;
      zz_004beb8_(dVar4,param_1,7,2,*(char *)(param_1 + 0x6ea) + 10,4,2);
    }
    else {
      zz_006bf80_(param_1);
      zz_0101c1c_(param_1);
      zz_004beb8_((double)FLOAT_8043934c,param_1,1,2,*(char *)(param_1 + 0x6ea) + 5,0xffffffff,
                  0xffffffff);
    }
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if ((*(ushort *)(param_1 + 0x5d8) & 0xf0) != 0) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    iVar3 = zz_00677b0_(param_1);
    if (iVar3 == 0) {
      zz_006a4f4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
    *(float *)(param_1 + 0x694) = *(float *)(param_1 + 0x558) + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80101880  FUN_80101880 ====

void FUN_80101880(int param_1)

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
    zz_0101c00_(param_1);
    zz_006bf80_(param_1);
    zz_0101c1c_(param_1);
    zz_004beb8_((double)FLOAT_8043934c,param_1,1,2,*(char *)(param_1 + 0x6ea) + 5,0xffffffff,
                0xffffffff);
    return;
  }
  fVar2 = FLOAT_80439348;
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



// ==== 801019ac  FUN_801019ac ====

void FUN_801019ac(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_80439348;
  *(char *)(param_1 + 0x544) = *(char *)(param_1 + 0x544) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0xff;
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined2 *)(param_1 + 0x54a) = 0;
  *(undefined2 *)(param_1 + 0x54c) = 0;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
  }
  zz_004beb8_((double)FLOAT_8043934c,param_1,2,2,(int)*(char *)(param_1 + 0x6eb),0xc,2);
  zz_0101a3c_(param_1);
  return;
}



// ==== 80101a3c  zz_0101a3c_ ====

void zz_0101a3c_(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  
  cVar1 = *(char *)(param_1 + 0x6eb);
  iVar3 = (int)cVar1;
  if (iVar3 == 0) {
    zz_006ed8c_((double)FLOAT_80439360,param_1);
  }
  else {
    fVar2 = *(float *)(*(int *)(param_1 + 0x4ac) + 0x2c);
    if (*(float *)(param_1 + 0x44) < fVar2) {
      *(float *)(param_1 + 0x44) = fVar2;
    }
    *(float *)(param_1 + 0x4c) = FLOAT_80439348;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x5ac);
  }
  if ((*(uint *)(param_1 + 0x5b4) & 0x100) == 0) {
    *(float *)(param_1 + 0x48) = FLOAT_8043934c;
  }
  else {
    *(float *)(param_1 + 0x48) = FLOAT_80439348;
  }
  FUN_80067310((double)FLOAT_80439354,param_1,*(short *)(param_1 + 0x5ae));
  zz_0067a28_(param_1);
  if (*(char *)(param_1 + 0x6ea) == iVar3) {
    zz_004cd24_(param_1,3);
  }
  else {
    if (-1 < *(char *)(param_1 + 0x6ea)) {
      zz_004beb8_((double)*(float *)(param_1 + 0x1ae0),param_1,3,2,
                  *(short *)(param_1 + 0x54c) + iVar3,
                  (int)(FLOAT_80439364 +
                       (float)((double)(float)((double)CONCAT44(0x43300000,
                                                                (int)*(short *)(param_1 + 0x1af8) ^
                                                                0x80000000) - DOUBLE_80439340) -
                              (double)*(float *)(param_1 + 0x1ae0))),2);
    }
    *(char *)(param_1 + 0x6ea) = cVar1;
  }
  return;
}



// ==== 80101b68  zz_0101b68_ ====

void zz_0101b68_(int param_1)

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



// ==== 80101c00  zz_0101c00_ ====

void zz_0101c00_(int param_1)

{
  float fVar1;
  
  *(undefined1 *)(param_1 + 0x745) = 0;
  fVar1 = FLOAT_8043935c;
  *(undefined1 *)(param_1 + 0x6ec) = 5;
  *(float *)(param_1 + 0x558) = fVar1;
  return;
}



// ==== 80101c1c  zz_0101c1c_ ====

void zz_0101c1c_(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_80439368;
  *(char *)(param_1 + 0x6ec) = *(char *)(param_1 + 0x6ec) + -1;
  *(float *)(param_1 + 0x558) = fVar1;
  *(undefined1 *)(param_1 + 0x745) = 0;
  *(undefined1 *)(param_1 + 0x587) = 0;
  iVar2 = zz_006dbe0_(param_1,0,1,1);
  if (iVar2 != 0) {
    zz_0082824_(param_1,0x19);
  }
  return;
}



// ==== 80101c88  FUN_80101c88 ====

void FUN_80101c88(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80320538)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80101cd0  FUN_80101cd0 ====

void FUN_80101cd0(int param_1)

{
  zz_0147e34_(param_1);
  return;
}



// ==== 80101cf4  FUN_80101cf4 ====

void FUN_80101cf4(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032054c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80101d44  FUN_80101d44 ====

void FUN_80101d44(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043935c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x54a) = 0x14;
  *(undefined2 *)(param_1 + 0x54e) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 7;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
  }
  zz_006d144_(param_1,0xc0);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_80439360,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043934c;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_80439348;
  zz_0092dcc_(param_1,0);
  return;
}



// ==== 80101e70  FUN_80101e70 ====

void FUN_80101e70(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  gnt4_PSQUATScale_bl((double)FLOAT_80439360,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_80439348;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    fVar2 = FLOAT_80439358;
    fVar1 = FLOAT_80439348;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar2;
    *(float *)(param_1 + 0x50) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
    zz_0092dcc_(param_1,0);
  }
  return;
}



// ==== 80101f50  FUN_80101f50 ====

void FUN_80101f50(int param_1)

{
  float fVar1;
  float fVar2;
  double dVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(short *)(param_1 + 0x54a) = *(short *)(param_1 + 0x54a) + -1;
  }
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_006d144_(param_1,0xc0);
    zz_006e514_(param_1,0xc0,(short *)(param_1 + 0x54e));
    dVar3 = zz_0045238_(*(short *)(param_1 + 0x54e));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043936c * dVar3);
    dVar3 = zz_0045204_(*(short *)(param_1 + 0x54e));
    dVar4 = (double)FLOAT_80439354;
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043936c * -dVar3);
    FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x5ae));
    zz_00677b0_(param_1);
    zz_004cd24_(param_1,0xf);
    fVar2 = FLOAT_80439348;
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if ((fVar1 <= fVar2) || (*(short *)(param_1 + 0x54a) < 1)) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    }
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80102048  FUN_80102048 ====

void FUN_80102048(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_004cd24_(param_1,0xf);
    if (*(char *)(param_1 + 0x544) == '\0') {
      if (*(char *)(param_1 + 0x1b01) != '\0') {
        dVar3 = (double)FLOAT_8043934c;
        *(undefined1 *)(param_1 + 0x544) = 1;
        zz_004beb8_(dVar3,param_1,0xf,3,(int)*(char *)(param_1 + 0x6ea),0xffffffff,0xffffffff);
      }
    }
    else {
      zz_006ed8c_((double)FLOAT_80439360,param_1);
    }
    FUN_80067310((double)FLOAT_80439354,param_1,*(short *)(param_1 + 0x5ae));
    fVar1 = FLOAT_80439348;
    if (*(float *)(param_1 + 0x44) < FLOAT_80439348) {
      *(float *)(param_1 + 0x44) = FLOAT_80439348;
      *(float *)(param_1 + 0x4c) = fVar1;
    }
    iVar2 = zz_00677b0_(param_1);
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      if (iVar2 == 0) {
        zz_006a5a4_(param_1);
      }
      else {
        zz_006a474_(param_1);
      }
    }
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 8010214c  FUN_8010214c ====

void FUN_8010214c(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8032055c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8010219c  FUN_8010219c ====

void FUN_8010219c(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043935c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined1 *)(param_1 + 0x6ea) = 4;
  uVar3 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x86c),param_1);
  if ((int)uVar3 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  dVar4 = (double)FLOAT_8043934c;
  *(undefined2 *)(param_1 + 0x54e) = *(undefined2 *)(param_1 + 0x5ae);
  cVar1 = *(char *)(param_1 + 0x6ea);
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  zz_0102274_(param_1);
  return;
}



// ==== 80102274  zz_0102274_ ====

void zz_0102274_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  int iVar5;
  double dVar6;
  float local_28;
  float local_24;
  undefined4 local_20;
  float local_1c;
  float local_18;
  undefined4 local_14;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006ed8c_((double)FLOAT_80439370,param_1);
  FUN_80067310((double)FLOAT_80439354,param_1,*(short *)(param_1 + 0x54e));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_80439348;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar5 = zz_006d144_(param_1,0xc0), iVar5 != 0)) {
    fVar1 = FLOAT_80439358;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    if (*(int *)(param_1 + 0xcc) == 0) {
      *(float *)(param_1 + 0x48) = FLOAT_80439378;
      *(float *)(param_1 + 0x44) =
           *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x86c) / fVar1;
    }
    else {
      iVar5 = param_1 + *(char *)(*(int *)(param_1 + 0x4b0) + 0x10) * 0x30;
      local_1c = *(float *)(iVar5 + 0x8e0);
      local_18 = *(float *)(iVar5 + 0x8f0);
      local_14 = *(undefined4 *)(iVar5 + 0x900);
      local_28 = *(float *)(param_1 + 0x518);
      local_20 = *(undefined4 *)(param_1 + 0x520);
      local_24 = FLOAT_80439374 * *(float *)(param_1 + 0xb4) + *(float *)(param_1 + 0x51c);
      gnt4_PSVECSubtract_bl(&local_28,&local_1c,&local_1c);
      fVar1 = FLOAT_80439348;
      *(float *)(param_1 + 0x48) = local_18 / FLOAT_80439358;
      local_18 = fVar1;
      dVar6 = gnt4_PSVECMag_bl(&local_1c);
      *(float *)(param_1 + 0x44) = (float)(dVar6 / (double)FLOAT_80439358);
    }
    fVar4 = FLOAT_80439388;
    fVar3 = FLOAT_80439364;
    fVar2 = FLOAT_80439358;
    fVar1 = FLOAT_80439348;
    *(float *)(param_1 + 0x44) = (float)((double)*(float *)(param_1 + 0x44) * DOUBLE_80439380);
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x50) = fVar3 * (-*(float *)(param_1 + 0x48) / fVar2);
    *(undefined4 *)(param_1 + 0x38) = *(undefined4 *)(param_1 + 0x44);
    *(undefined4 *)(param_1 + 0x3c) = *(undefined4 *)(param_1 + 0x50);
    if (fVar4 < *(float *)(param_1 + 0x764)) {
      zz_0092dcc_(param_1,0);
    }
  }
  return;
}



// ==== 80102464  FUN_80102464 ====

void FUN_80102464(int param_1)

{
  float fVar1;
  uint uVar2;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  zz_006d144_(param_1,0xc0);
  uVar2 = FUN_80066838((double)FLOAT_8043938c,param_1);
  if (0 < (int)uVar2) {
    zz_006eddc_((double)FLOAT_80439338,param_1,(float *)(param_1 + 0x44));
  }
  FUN_80067310((double)FLOAT_80439354,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar1 = FLOAT_80439348;
  if (*(float *)(param_1 + 0x48) < FLOAT_80439348) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x50) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
  }
  return;
}



// ==== 8010250c  FUN_8010250c ====

void FUN_8010250c(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  uVar3 = FUN_80066838((double)FLOAT_8043938c,param_1);
  if (uVar3 == 0) {
    zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  }
  fVar2 = FLOAT_80439390;
  fVar1 = FLOAT_80439348;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x48) = fVar2;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    zz_00677b0_(param_1);
  }
  return;
}



// ==== 801025a4  FUN_801025a4 ====

void FUN_801025a4(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  if (*(char *)(param_1 + 0x71c) == '\0') {
    zz_004cd24_(param_1,0xf);
    dVar4 = (double)FLOAT_80439360;
    *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + 0x1e00;
    zz_006eddc_(dVar4,param_1,(float *)(param_1 + 0x44));
    fVar2 = FLOAT_80439348;
    if (*(float *)(param_1 + 0x44) < FLOAT_80439348) {
      *(float *)(param_1 + 0x44) = FLOAT_80439348;
      *(float *)(param_1 + 0x4c) = fVar2;
    }
    FUN_80067310((double)FLOAT_80439354,param_1,*(short *)(param_1 + 0x5ae));
    iVar3 = zz_00677b0_(param_1);
    fVar2 = FLOAT_80439394;
    if (iVar3 != 0) {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x558) = fVar2;
      zz_0066530_(param_1,0x2c);
      cVar1 = *(char *)(param_1 + 0x6ea);
      dVar4 = (double)FLOAT_8043934c;
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
      zz_00b2190_(param_1,2);
    }
  }
  return;
}



// ==== 8010268c  FUN_8010268c ====

void FUN_8010268c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  zz_004cd24_(param_1,0xf);
  fVar4 = FLOAT_80439358;
  fVar2 = FLOAT_8043934c;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_80439350;
    *(float *)(param_1 + 0x44) = fVar4;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x50) = fVar2;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
    zz_00677b0_(param_1);
    zz_0066530_(param_1,0x2d);
    cVar1 = *(char *)(param_1 + 0x6ea);
    dVar5 = (double)FLOAT_8043934c;
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 80102740  FUN_80102740 ====

void FUN_80102740(int param_1)

{
  int iVar1;
  
  zz_004cd24_(param_1,0xf);
  if (*(float *)(param_1 + 0x44) < FLOAT_80439348) {
    *(float *)(param_1 + 0x44) = FLOAT_80439348;
  }
  FUN_80067310((double)FLOAT_80439354,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (iVar1 == 0) {
    if (*(char *)(param_1 + 0x1cee) != '\0') {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_80439354 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80102800  FUN_80102800 ====

void FUN_80102800(int param_1)

{
  zz_0148384_(param_1);
  return;
}



// ==== 80102920  FUN_80102920 ====

void FUN_80102920(int param_1)

{
  zz_0096570_(param_1);
  zz_00c74ec_(param_1,2);
  return;
}



// ==== 80102974  FUN_80102974 ====

void FUN_80102974(int param_1)

{
  double dVar1;
  
  if ('\0' < *(char *)(param_1 + 0x6f7)) {
    *(char *)(param_1 + 0x6f7) = *(char *)(param_1 + 0x6f7) + -1;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    dVar1 = DOUBLE_804393a0;
    *(undefined2 *)(param_1 + 0x1918) = 0;
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             dVar1) * FLOAT_80439398);
  }
  return;
}



// ==== 801029f4  FUN_801029f4 ====

void FUN_801029f4(int param_1)

{
  (*(code *)(&PTR_FUN_80321610)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80102a30  FUN_80102a30 ====

void FUN_80102a30(int param_1)

{
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_804393a0) * FLOAT_804393a8);
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_80321620)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80102ab0  FUN_80102ab0 ====

void FUN_80102ab0(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_80321634)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80102af8  FUN_80102af8 ====

void FUN_80102af8(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = (double)FLOAT_804393ac;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_004beb8_(dVar2,param_1,1,2,(int)*(char *)(param_1 + 0x6ee),0xffffffff,0xffffffff);
  zz_004beb8_((double)FLOAT_804393ac,param_1,2,0,0,0xffffffff,0xffffffff);
  zz_006d0dc_(param_1,0xc1,0);
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  zz_01033f8_(param_1);
  fVar1 = FLOAT_804393b0;
  *(float *)(param_1 + 0x50) = FLOAT_804393b0;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_804393b0;
  return;
}



// ==== 80102bf8  FUN_80102bf8 ====

/* WARNING: Removing unreachable block (ram,0x80102cdc) */
/* WARNING: Removing unreachable block (ram,0x80102c08) */

void FUN_80102bf8(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_804393b0;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  iVar3 = zz_006d0dc_(param_1,0xc1,0);
  fVar2 = FLOAT_804393b0;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_80103428(param_1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  dVar4 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_804393b8 < dVar4) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80102cf8  FUN_80102cf8 ====

void FUN_80102cf8(int param_1)

{
  int iVar1;
  double dVar2;
  
  if (*(float *)(param_1 + 0x55c) <= FLOAT_804393b0) {
    zz_004cd24_(param_1,0xf);
  }
  else {
    *(float *)(param_1 + 0x55c) = *(float *)(param_1 + 0x55c) - *(float *)(param_1 + 0x1dc8);
  }
  if (*(float *)(param_1 + 0x558) <= FLOAT_804393b0) {
    if ((*(uint *)(param_1 + 0x5d4) & 0x20) != 0) {
      iVar1 = zz_006dbe0_(param_1,0,1,0);
      if ((iVar1 != 0) && ('\0' < *(char *)(param_1 + 0x6ef))) {
        if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
          zz_006a3d0_(param_1,'\0',3,0);
          return;
        }
        zz_006bf80_(param_1);
        dVar2 = (double)FLOAT_804393ac;
        *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + -1;
        zz_004beb8_(dVar2,param_1,0xf,2,1,0xffffffff,0xffffffff);
        return;
      }
      goto LAB_80102e0c;
    }
    *(float *)(param_1 + 0x55c) = FLOAT_804393b0;
  }
  else {
    *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  }
  if ((((*(ushort *)(param_1 + 0x5d8) & 0xf0) == 0) && ((*(uint *)(param_1 + 0x5d4) & 1) == 0)) &&
     (*(char *)(param_1 + 0x1cee) == '\0')) {
    gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
    zz_00679d0_(param_1);
    dVar2 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
    if (dVar2 <= (double)FLOAT_804393b8) {
      return;
    }
    zz_00b22f4_(param_1);
    return;
  }
LAB_80102e0c:
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  zz_006a474_(param_1);
  return;
}



// ==== 80102e84  FUN_80102e84 ====

void FUN_80102e84(int param_1)

{
  (*(code *)(&PTR_FUN_80321640)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80102ec0  FUN_80102ec0 ====

void FUN_80102ec0(int param_1)

{
  uint uVar1;
  int iVar2;
  
  iVar2 = 6;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  uVar1 = *(uint *)(param_1 + 0x5e0);
  if ((uVar1 & 0x80) != 0) {
    iVar2 = 9;
  }
  if ((uVar1 & 0x10) != 0) {
    iVar2 = 3;
  }
  if ((uVar1 & 0x20) != 0) {
    iVar2 = 0;
  }
  zz_004beb8_((double)FLOAT_804393ac,param_1,1,2,iVar2 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  zz_01033f8_(param_1);
  return;
}



// ==== 80102f50  FUN_80102f50 ====

void FUN_80102f50(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  iVar3 = zz_006dee8_(param_1,1);
  zz_004cd24_(param_1,1);
  fVar2 = FLOAT_804393b0;
  if (iVar3 < 0) {
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a3d0_(param_1,'\0',0,2);
    }
    else {
      zz_006a3d0_(param_1,'\0',4,2);
    }
  }
  else {
    if ((iVar3 < 1) &&
       (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
       *(float *)(param_1 + 0x560) = fVar1, fVar2 < fVar1)) {
      return;
    }
    if (*(char *)(param_1 + 0x1cef) != '\0') {
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      FUN_80103428(param_1);
    }
  }
  return;
}



// ==== 80103024  FUN_80103024 ====

void FUN_80103024(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  double dVar3;
  
  if (*(float *)(param_9 + 0x55c) <= FLOAT_804393b0) {
    zz_004cd24_(param_9,1);
  }
  else {
    *(float *)(param_9 + 0x55c) = *(float *)(param_9 + 0x55c) - *(float *)(param_9 + 0x1dc8);
  }
  dVar3 = (double)*(float *)(param_9 + 0x558);
  if (dVar3 <= (double)FLOAT_804393b0) {
    if ((*(uint *)(param_9 + 0x5d4) & 0x20) != 0) {
      param_11 = 1;
      param_12 = 0;
      iVar1 = zz_006dbe0_(param_9,0,1,0);
      if ((iVar1 != 0) && ('\0' < *(char *)(param_9 + 0x6ef))) {
        zz_006bf80_(param_9);
        *(char *)(param_9 + 0x540) = *(char *)(param_9 + 0x540) + -1;
        uVar2 = *(uint *)(param_9 + 0x5e0);
        if (((uVar2 & 0x40) != 0) || (*(char *)(param_9 + 0x5e4) == '\x04')) {
          iVar1 = 7;
          *(undefined1 *)(param_9 + 0x581) = 3;
          if ((*(uint *)(param_9 + 0x5e0) & 0x80) != 0) {
            iVar1 = 10;
          }
          zz_004beb8_((double)FLOAT_804393ac,param_9,1,2,iVar1,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x10) != 0) {
          dVar3 = (double)FLOAT_804393ac;
          *(undefined1 *)(param_9 + 0x581) = 1;
          zz_004beb8_(dVar3,param_9,1,2,4,0xffffffff,0xffffffff);
          return;
        }
        if ((uVar2 & 0x20) != 0) {
          dVar3 = (double)FLOAT_804393ac;
          *(undefined1 *)(param_9 + 0x581) = 2;
          zz_004beb8_(dVar3,param_9,1,2,1,0xffffffff,0xffffffff);
          return;
        }
        zz_006a3d0_(param_9,'\0',0,2);
        return;
      }
      goto LAB_801031b8;
    }
    *(float *)(param_9 + 0x55c) = FLOAT_804393b0;
  }
  else {
    *(float *)(param_9 + 0x558) = (float)(dVar3 - (double)*(float *)(param_9 + 0x1dc8));
  }
  if (((*(ushort *)(param_9 + 0x5d8) & 0xf0) == 0) && (*(char *)(param_9 + 0x1cee) == '\0')) {
    return;
  }
LAB_801031b8:
  *(undefined1 *)(param_9 + 0x73f) = 0;
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a668_(dVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801031ec  FUN_801031ec ====

void FUN_801031ec(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8032164c)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80103234  FUN_80103234 ====

void FUN_80103234(int param_1)

{
  double dVar1;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  zz_006d0dc_(param_1,0x81,0);
  dVar1 = (double)FLOAT_804393bc;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  FUN_80067310(dVar1,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  zz_004beb8_((double)FLOAT_804393ac,param_1,1,2,*(char *)(param_1 + 0x6ee) + 6,0xffffffff,
              0xffffffff);
  if ((*(char *)(param_1 + 0x1d0c) != '\0') || (*(char *)(param_1 + 0x1d0d) != '\x16')) {
    zz_004beb8_((double)FLOAT_804393ac,param_1,2,0,0x16,0xffffffff,0xffffffff);
  }
  zz_01033f8_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_804393b0;
  return;
}



// ==== 80103308  FUN_80103308 ====

/* WARNING: Removing unreachable block (ram,0x801033dc) */
/* WARNING: Removing unreachable block (ram,0x80103318) */

void FUN_80103308(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  dVar4 = (double)*(float *)(param_1 + 0x1dc8);
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(float *)(param_1 + 0x1dc8) = FLOAT_804393b0;
  }
  zz_004cd24_(param_1,0xf);
  *(float *)(param_1 + 0x1dc8) = (float)dVar4;
  FUN_80067310((double)FLOAT_804393bc,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  iVar3 = zz_006d0dc_(param_1,0x81,0);
  fVar2 = FLOAT_804393b0;
  if (((iVar3 != 0) ||
      (fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8),
      *(float *)(param_1 + 0x560) = fVar1, fVar1 <= fVar2)) && (*(char *)(param_1 + 0x1cef) != '\0')
     ) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    FUN_80103428(param_1);
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffd;
    zz_006a5a4_(param_1);
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 801033f8  zz_01033f8_ ====

void zz_01033f8_(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_804393c4;
  *(float *)(param_1 + 0x560) = FLOAT_804393c0;
  fVar1 = FLOAT_804393b0;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  if (*(char *)(param_1 + 0x6ee) != '\0') {
    return;
  }
  *(undefined1 *)(param_1 + 0x6ef) = 100;
  return;
}



// ==== 80103428  FUN_80103428 ====

/* WARNING: Removing unreachable block (ram,0x8010358c) */
/* WARNING: Removing unreachable block (ram,0x80103438) */

void FUN_80103428(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_28;
  float local_24;
  undefined4 local_20;
  
  fVar2 = FLOAT_804393c4;
  *(float *)(param_1 + 0x560) = FLOAT_804393c0;
  fVar1 = FLOAT_804393b0;
  *(float *)(param_1 + 0x558) = fVar2;
  *(float *)(param_1 + 0x55c) = fVar1;
  *(undefined1 *)(param_1 + 0x6ee) = 1;
  if ('\0' < *(char *)(param_1 + 0x6ef)) {
    *(undefined2 *)(param_1 + 0x1900) = 0;
    zz_0046698_(param_1);
    if (*(int *)(param_1 + 0xcc) != 0) {
      local_28 = *(float *)(param_1 + 0xa24);
      dVar5 = (double)*(float *)(param_1 + 0xa34);
      local_20 = *(undefined4 *)(param_1 + 0xa44);
      local_24 = FLOAT_804393b0;
      dVar6 = gnt4_PSVECMag_bl(&local_28);
      iVar3 = FUN_800452a0(dVar5,dVar6);
      local_28 = *(float *)(param_1 + 0xa30);
      local_24 = *(float *)(param_1 + 0xa40);
      local_20 = *(undefined4 *)(param_1 + 0xa50);
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_28,&local_28);
      dVar6 = (double)local_24;
      local_24 = FLOAT_804393b0;
      dVar5 = gnt4_PSVECMag_bl(&local_28);
      iVar4 = FUN_800452a0(dVar6,dVar5);
      *(short *)(param_1 + 0x1900) = (short)iVar3 + (short)iVar4;
      zz_0046dd4_((float *)(param_1 + *(char *)(param_1 + 0x19b2) * 0x30 + 0x8d4),
                  (float *)(param_1 + 0xa24),(short *)(param_1 + 0x18fe),
                  (undefined4 *)(param_1 + 0x1328),(float *)(param_1 + 0xf44),
                  (float *)(param_1 + 0x1628));
    }
    iVar3 = zz_006dbe0_(param_1,0,1,1);
    if (iVar3 != 0) {
      zz_00c3be0_(param_1,0xb);
      *(char *)(param_1 + 0x6ef) = *(char *)(param_1 + 0x6ef) + -1;
    }
    if (*(short *)(param_1 + 0x774) < 1) {
      *(undefined1 *)(param_1 + 0x6ef) = 0;
    }
  }
  return;
}



// ==== 801035ac  FUN_801035ac ====

void FUN_801035ac(int param_1)

{
  (*(code *)(&PTR_FUN_80321658)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801035e8  FUN_801035e8 ====

void FUN_801035e8(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}



// ==== 80103618  FUN_80103618 ====

void FUN_80103618(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_01613fc_(param_1);
  return;
}



// ==== 80103648  FUN_80103648 ====

void FUN_80103648(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  zz_0161d7c_(param_1);
  return;
}



// ==== 80103678  FUN_80103678 ====

void FUN_80103678(int param_1)

{
  zz_01618ac_(param_1);
  return;
}



// ==== 8010369c  FUN_8010369c ====

void FUN_8010369c(int param_1)

{
  (*(code *)(&PTR_FUN_8032166c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801036d8  FUN_801036d8 ====

void FUN_801036d8(int param_1)

{
  (*(code *)(&PTR_FUN_80321680)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80103714  FUN_80103714 ====

void FUN_80103714(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  double dVar5;
  
  fVar4 = FLOAT_804393cc;
  fVar3 = FLOAT_804393c8;
  fVar2 = FLOAT_804393b0;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x541) = 0;
  *(float *)(param_1 + 0x560) = fVar3;
  *(undefined2 *)(param_1 + 0x54e) = 0x3c;
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(float *)(param_1 + 0x48) = fVar4;
  *(float *)(param_1 + 0x50) = fVar2;
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar5 = (double)FLOAT_804393ac;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar5,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 801037f8  FUN_801037f8 ====

void FUN_801037f8(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  if (*(short *)(param_1 + 0x784) < 1) {
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  else if (*(char *)(param_1 + 0x541) == '\0') {
    *(undefined1 *)(param_1 + 0x541) = 1;
    zz_00107a0_(param_1,10);
  }
  FUN_80067310((double)FLOAT_804393bc,param_1,*(short *)(param_1 + 0x5ae));
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if ((*(char *)(param_1 + 0x1cef) < '\x01') || (iVar3 = zz_006dbe0_(param_1,2,1,0), iVar3 != 0)) {
    if (*(char *)(param_1 + 0x1cee) == '\0') {
      return;
    }
    zz_00f036c_(param_1,0xc3);
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 != 0) {
      zz_00e19a8_(param_1,1,param_1 + 0x6f7);
      dVar4 = (double)FLOAT_804393ac;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x542) = 0;
      *(undefined1 *)(param_1 + 0x6f7) = 2;
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
      return;
    }
  }
  fVar2 = FLOAT_804393b0;
  *(undefined1 *)(param_1 + 0x73f) = 0;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  zz_006a5a4_(param_1);
  return;
}



// ==== 8010398c  FUN_8010398c ====

void FUN_8010398c(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  double dVar4;
  
  *(undefined1 *)(param_1 + 0x6f7) = 2;
  uVar3 = zz_006de44_(param_1,0xf0f00);
  dVar4 = DOUBLE_804393a0;
  if (uVar3 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar3) {
      uVar3 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar3;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000) - dVar4);
  }
  FUN_80067310((double)FLOAT_804393bc,param_1,*(short *)(param_1 + 0x5ae) + -0x8000);
  zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
    zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  }
  fVar2 = FLOAT_804393b0;
  if (*(float *)(param_1 + 0x560) <= FLOAT_804393b0) {
    dVar4 = (double)FLOAT_804393ac;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(undefined1 *)(param_1 + 0x6f7) = 0;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  else {
    *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 80103aec  FUN_80103aec ====

void FUN_80103aec(int param_1)

{
  float fVar1;
  int iVar2;
  
  FUN_80067310((double)FLOAT_804393bc,param_1,*(short *)(param_1 + 0x5ae));
  iVar2 = zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_804393b0;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    if (iVar2 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a750_(param_1,7);
      *(float *)(param_1 + 0x694) = FLOAT_804393bc + *(float *)(param_1 + 0x1dc8);
    }
  }
  return;
}



// ==== 80103b9c  FUN_80103b9c ====

void FUN_80103b9c(int param_1)

{
  *(short *)(param_1 + 0x1900) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x1900) ^ 0x80000000) -
                           DOUBLE_804393a0) * FLOAT_804393a8);
  (*(code *)(&PTR_FUN_80321690)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80103c10  FUN_80103c10 ====

void FUN_80103c10(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_803216a4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 80103c60  FUN_80103c60 ====

void FUN_80103c60(int param_1)

{
  char cVar1;
  float fVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  if (*(int *)(param_1 + 0xcc) == 0) {
    *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
  }
  fVar2 = FLOAT_804393b0;
  *(float *)(param_1 + 0x50) = FLOAT_804393b0;
  *(float *)(param_1 + 0x48) = fVar2;
  *(float *)(param_1 + 0x4c) = fVar2;
  *(float *)(param_1 + 0x44) = fVar2;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  *(undefined1 *)(param_1 + 0x6ea) = 0xd;
  *(undefined1 *)(param_1 + 0x542) = 1;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 0xc;
    *(undefined1 *)(param_1 + 0x542) = 0;
  }
  zz_006d144_(param_1,0xc1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_804393ac;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,2,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_804393b0;
  return;
}



// ==== 80103d88  FUN_80103d88 ====

void FUN_80103d88(int param_1)

{
  double dVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc1);
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    zz_006e1ac_(param_1,0xc1,1);
  }
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  if ('\0' < *(char *)(param_1 + 0x1cef)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_00c3be0_(param_1,0x1a);
    zz_00c3be0_(param_1,0x1b);
    dVar1 = zz_0045238_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x44) = (float)((double)FLOAT_804393d0 * dVar1);
    dVar1 = zz_0045204_(*(short *)(param_1 + 0x18da));
    *(float *)(param_1 + 0x48) = (float)((double)FLOAT_804393d0 * dVar1);
  }
  dVar1 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
  if ((double)FLOAT_804393b8 < dVar1) {
    zz_00b22f4_(param_1);
  }
  return;
}



// ==== 80103e7c  FUN_80103e7c ====

void FUN_80103e7c(int param_1)

{
  float fVar1;
  int iVar2;
  double dVar3;
  float afStack_28 [4];
  undefined4 local_18;
  uint uStack_14;
  longlong local_10;
  
  local_18 = 0x43300000;
  uStack_14 = (int)*(short *)(param_1 + 0x18da) ^ 0x80000000;
  iVar2 = (int)((float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_804393a0) * FLOAT_80439398);
  local_10 = (longlong)iVar2;
  *(short *)(param_1 + 0x18da) = (short)iVar2;
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1d0f) < '\0') {
    *(undefined1 *)(param_1 + 0x1d0f) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_804393b4,param_1);
  FUN_80067310((double)FLOAT_804393bc,param_1,*(short *)(param_1 + 0x72) + -0x8000);
  gnt4_PSQUATScale_bl((double)FLOAT_804393b4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  iVar2 = zz_00677b0_(param_1);
  if ((iVar2 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_804393c4 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (('\0' < *(char *)(param_1 + 0x542)) && (*(char *)(param_1 + 0x1cee) != '\0')) {
    *(undefined1 *)(param_1 + 0x542) = 0;
    if (iVar2 == 0) {
      *(char *)(param_1 + 0x6ea) = *(char *)(param_1 + 0x6ea) + '\x01';
    }
    zz_004beb8_((double)FLOAT_804393ac,param_1,0xf,2,(int)*(char *)(param_1 + 0x6ea),0xffffffff,
                0xffffffff);
  }
  if (*(char *)(param_1 + 0x1cee) == '\0') {
    if (*(char *)(param_1 + 0x542) < '\x01') {
      gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),afStack_28);
      dVar3 = gnt4_PSVECMag_bl(afStack_28);
      if ((double)FLOAT_804393d4 < dVar3) {
        zz_00b22f4_(param_1);
      }
    }
    else {
      zz_00b22f4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_1);
    }
    else {
      iVar2 = FUN_800452a0((double)*(float *)(param_1 + 0x38),(double)*(float *)(param_1 + 0x40));
      *(short *)(param_1 + 0x5ae) = (short)iVar2;
      fVar1 = FLOAT_804393b0;
      *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) + *(float *)(param_1 + 0x3c);
      *(float *)(param_1 + 0x3c) = fVar1;
      dVar3 = gnt4_PSVECMag_bl((float *)(param_1 + 0x38));
      *(float *)(param_1 + 0x44) = (float)dVar3;
      *(float *)(param_1 + 0x4c) = FLOAT_804393b0;
      *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
      zz_006a5a4_(param_1);
    }
  }
  return;
}



// ==== 801040c4  zz_01040c4_ ====

void zz_01040c4_(int param_1)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 0xb03) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_801041b0;
    *(code **)(puVar1 + 0x10c) = FUN_80104350;
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



// ==== 801041b0  FUN_801041b0 ====

void FUN_801041b0(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803216b0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80104204  FUN_80104204 ====

void FUN_80104204(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  undefined4 extraout_r4;
  undefined4 uVar5;
  int iVar6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  double dVar8;
  undefined8 uVar9;
  double dVar10;
  double dVar11;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  
  iVar7 = *(int *)(param_1 + 0x90);
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  *(code **)(param_1 + 0x100) = FUN_80047dcc;
  zz_0089100_(param_1,(int)*(char *)(iVar7 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_804393d8;
  dVar11 = (double)FLOAT_804393d8;
  *(undefined1 *)(param_1 + 0x84) = 0x47;
  fVar2 = FLOAT_804393dc;
  dVar10 = (double)FLOAT_804393dc;
  *(float *)(param_1 + 0xb4) = fVar1;
  fVar3 = FLOAT_804393e0;
  dVar8 = (double)FLOAT_804393e0;
  *(float *)(param_1 + 0xb8) = fVar1;
  fVar4 = FLOAT_804393e4;
  *(float *)(param_1 + 0x58) = fVar1;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x60) = fVar1;
  *(undefined1 *)(param_1 + 0x89) = 0xc;
  *(float *)(param_1 + 100) = fVar2;
  *(float *)(param_1 + 0x68) = fVar3;
  *(float *)(param_1 + 0x6c) = fVar4;
  *(undefined2 *)(param_1 + 0x70) = 0xee39;
  *(undefined2 *)(param_1 + 0x72) = 0;
  iVar7 = zz_0006f98_(iVar7);
  uVar9 = zz_0007030_(dVar8,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar7 + 0x600),
                      *(int *)(param_1 + 0xe0),10,iVar7 + 0xc28,in_r7,in_r8,in_r9,in_r10);
  iVar6 = iVar7 + 0xc28;
  uVar5 = 10;
  uVar9 = zz_0007030_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar7 + 0x600),
                      *(int *)(param_1 + 0xe4),10,iVar6,in_r7,in_r8,in_r9,in_r10);
  zz_0007c54_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe4),extraout_r4
              ,uVar5,iVar6,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_804393e8,*(int *)(param_1 + 0xe4));
  *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
  zz_0104310_(param_1);
  return;
}



// ==== 80104310  zz_0104310_ ====

void zz_0104310_(int param_1)

{
  *(short *)(param_1 + 0x72) = *(short *)(param_1 + 0x72) + -0x800;
  return;
}



// ==== 80104330  FUN_80104330 ====

void FUN_80104330(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80104350  FUN_80104350 ====

void FUN_80104350(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar1 = *(int *)(param_9 + 0xe0);
  }
  else {
    iVar1 = *(int *)(param_9 + 0xe4);
  }
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,0x45);
  return;
}



