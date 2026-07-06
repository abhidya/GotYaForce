// ==== 801ec11c  FUN_801ec11c ====

void FUN_801ec11c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801ec13c  FUN_801ec13c ====

void FUN_801ec13c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if ((*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') &&
     (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) != '\x04')) {
    iVar1 = 0;
    uVar2 = 1;
  }
  else {
    iVar1 = 1;
    uVar2 = 0x44;
  }
  iVar1 = *(int *)(param_9 + iVar1 * 4 + 0xe0);
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,
              (float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(iVar1,uVar2);
  return;
}



// ==== 801ec1bc  zz_01ec1bc_ ====

void zz_01ec1bc_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_801ec3bc;
    *(code **)(puVar1 + 0x10c) = FUN_801ec748;
    puVar1[0x11] = 0;
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
    FUN_800061a8(param_1,0xd);
    *(undefined4 *)(puVar1 + 0x54) = *(undefined4 *)(param_1 + 0x7f0);
    zz_00f036c_(param_1,0x1a);
  }
  return;
}



// ==== 801ec2cc  zz_01ec2cc_ ====

void zz_01ec2cc_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),2,0x18,1,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    *(code **)(puVar1 + 0xc) = FUN_801ec3bc;
    *(code **)(puVar1 + 0x10c) = FUN_801ec748;
    puVar1[0x11] = 1;
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
    puVar1[0x13] = *(undefined1 *)(param_1 + 0x13);
  }
  return;
}



// ==== 801ec3bc  FUN_801ec3bc ====

void FUN_801ec3bc(int param_1)

{
  (*(code *)(&PTR_FUN_803a1090)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801ec3f8  FUN_801ec3f8 ====

void FUN_801ec3f8(int param_1)

{
  uint uVar1;
  int iVar2;
  undefined *puVar3;
  uint uVar4;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int *piVar5;
  double dVar6;
  undefined8 uVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_38 [12];
  
  iVar2 = *(int *)(param_1 + 0x90);
  if (((*(char *)(iVar2 + 0x18) < '\x02') &&
      (*(short *)(iVar2 + 1000) == *(short *)(param_1 + 0x94))) && (*(short *)(iVar2 + 0x6ba) != 0))
  {
    *(undefined1 *)(param_1 + 0x18) = 1;
    if (*(char *)(param_1 + 0x11) == '\0') {
      iVar2 = zz_00df070_(*(int *)(param_1 + 0x90));
      *(char *)(param_1 + 0x13) = (char)iVar2;
      *(undefined2 *)(param_1 + 0x1c) = 2;
      return;
    }
    uVar1 = zz_00055fc_();
    uVar4 = *(uint *)(&DAT_80315f04 + *(char *)(param_1 + 0x13) * 8);
    puVar3 = (&PTR_DAT_80315f08)[*(char *)(param_1 + 0x13) * 2];
    piVar5 = (int *)(puVar3 + (uVar1 - (uVar1 / uVar4) * uVar4) * 0x14);
    gnt4_PSMTXCopy_bl((float *)(*(int *)(param_1 + 0x90) + *piVar5 * 0x30 + 0x8d4),
                      (float *)(param_1 + 0x114));
    gnt4_PSMTXTrans_bl((double)(float)piVar5[2],(double)(float)piVar5[3],(double)(float)piVar5[4],
                       afStack_38);
    gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
    *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x120);
    *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0x130);
    *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(param_1 + 0x140);
    *(float *)(param_1 + 0xb4) =
         *(float *)(*(int *)(param_1 + 0x90) + 0xb4) * *(float *)(*(int *)(param_1 + 0x90) + 0x7fc);
    dVar6 = (double)*(float *)(param_1 + 0xb4);
    dVar8 = dVar6;
    gnt4_PSMTXScale_bl(dVar6,dVar6,dVar6,afStack_38);
    uVar7 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),afStack_38,(float *)(param_1 + 0x114));
    zz_0006fb4_(uVar7,dVar6,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,DAT_803bb374,
                *(int *)(param_1 + 0xe0),4,puVar3,uVar4,in_r8,in_r9,in_r10);
    *(undefined2 *)(param_1 + 0x1c) = 0;
    zz_0018f88_((int *)(param_1 + 0x144),-0x7fc5efb8,(float *)(param_1 + 0x58));
    zz_0019338_((int *)(param_1 + 0x14c),-0x7fc5ef88,(float *)(param_1 + 0x44));
    zz_0007cac_((double)*(float *)(param_1 + 0x44),*(int *)(param_1 + 0xe0));
    *(undefined1 *)(param_1 + 0x82) = 1;
    return;
  }
  *(undefined1 *)(param_1 + 0x18) = 2;
  return;
}



// ==== 801ec5b8  FUN_801ec5b8 ====

void FUN_801ec5b8(int param_1)

{
  int iVar1;
  short sVar2;
  
  if (*(char *)(param_1 + 0x11) == '\0') {
    iVar1 = *(int *)(param_1 + 0x90);
    if (((*(char *)(iVar1 + 0x18) < '\x02') &&
        (*(short *)(iVar1 + 1000) == *(short *)(param_1 + 0x94))) &&
       (*(short *)(iVar1 + 0x6ba) != 0)) {
      if (*(int *)(iVar1 + 0x7f0) == 0) {
        FUN_800061a8(iVar1,0xd);
      }
      sVar2 = *(short *)(param_1 + 0x1c) + -1;
      *(short *)(param_1 + 0x1c) = sVar2;
      if (sVar2 < 1) {
        zz_01ec2cc_(param_1);
        *(undefined2 *)(param_1 + 0x1c) = 2;
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
    }
  }
  else {
    sVar2 = *(short *)(param_1 + 0x1c) + 1;
    *(short *)(param_1 + 0x1c) = sVar2;
    if (sVar2 < 0xf) {
      zz_0018fd8_((int *)(param_1 + 0x144),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x58)
                 );
      zz_0019370_((int *)(param_1 + 0x14c),(int)*(short *)(param_1 + 0x1c),(float *)(param_1 + 0x44)
                 );
      zz_0007cac_((double)*(float *)(param_1 + 0x44),*(int *)(param_1 + 0xe0));
      *(float *)(param_1 + 0x24) = *(float *)(param_1 + 0x24) + FLOAT_8043c3d0;
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
      *(undefined1 *)(param_1 + 0x82) = 0;
    }
  }
  return;
}



// ==== 801ec6d8  FUN_801ec6d8 ====

void FUN_801ec6d8(int param_1)

{
  if (*(char *)(param_1 + 0x11) == '\0') {
    FUN_800061a8(*(int *)(param_1 + 0x90),1);
  }
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801ec728  FUN_801ec728 ====

void FUN_801ec728(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801ec748  FUN_801ec748 ====

void FUN_801ec748(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  float *pfVar1;
  undefined8 uVar2;
  double dVar3;
  double dVar4;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_38 [13];
  
  *(undefined4 *)(param_1 + 0x120) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x130) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x140) = *(undefined4 *)(param_1 + 0x28);
  dVar3 = (double)*(float *)(param_1 + 0x5c);
  dVar4 = (double)*(float *)(param_1 + 0x60);
  gnt4_PSMTXScale_bl((double)*(float *)(param_1 + 0x58),dVar3,dVar4,afStack_38);
  pfVar1 = afStack_38;
  uVar2 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar1,pfVar1);
  zz_00076d0_(uVar2,dVar3,dVar4,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),afStack_38,
              (undefined *)pfVar1,param_4,param_5,param_6,param_7,param_8);
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x47);
  return;
}



// ==== 801ec7c4  FUN_801ec7c4 ====

void FUN_801ec7c4(void)

{
  byte bVar1;
  char cVar2;
  
  if ((char)PTR_DAT_80433930[1] < '\x01') {
    PTR_DAT_80433930[1] = PTR_DAT_80433930[1] + '\x01';
    zz_002a5f4_(0,0,0,0);
    DAT_804363a0 = &DAT_803d5fb8;
    gnt4_memset(&DAT_803d5fb8,0,0x690);
    cVar2 = '\0';
    bVar1 = PTR_DAT_80433930[2];
    if ((bVar1 & 1) == 0) {
      cVar2 = '\x01';
      if ((bVar1 & 2) == 0) {
        cVar2 = '\x02';
        if ((bVar1 & 4) == 0) {
          cVar2 = '\x03';
          if ((bVar1 & 8) == 0) {
            cVar2 = '\x04';
          }
        }
      }
    }
    if (cVar2 == '\x04') {
      cVar2 = '\0';
    }
    DAT_804363a0[0x68c] = cVar2;
  }
  *(undefined4 *)(DAT_804363a0 + 8) = (&DAT_803c71fc)[DAT_804363a0[0x68c] * 8];
  *(undefined4 *)(DAT_804363a0 + 0xc) = (&DAT_803c7204)[DAT_804363a0[0x68c] * 8];
  *(uint *)(DAT_804363a0 + 0x10) =
       *(uint *)(DAT_804363a0 + 0xc) | (&DAT_803c720c)[DAT_804363a0[0x68c] * 8];
  (*(code *)(&PTR_FUN_803a10a0)[*DAT_804363a0])();
  return;
}



// ==== 801ec910  FUN_801ec910 ====

void FUN_801ec910(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  char cVar1;
  byte bVar2;
  undefined1 *puVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 uVar5;
  undefined1 *in_r6;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  
  cVar1 = DAT_804363a0[1];
  if (cVar1 == '\x02') {
LAB_801eca08:
    iVar4 = zz_01b1c60_();
    in_r6 = DAT_804363a0;
    if (iVar4 == 1) goto LAB_801ecac8;
    if (iVar4 < 0) {
      *DAT_804363a0 = 3;
      DAT_804363a0[1] = 2;
      *(undefined2 *)(DAT_804363a0 + 4) = 0;
      goto LAB_801ecac8;
    }
    bVar2 = DAT_804363a0[1];
    DAT_804363a0[1] = bVar2 + 1;
    param_1 = zz_0044bec_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,0,
                          (uint)bVar2,in_r6,in_r7,in_r8,in_r9,in_r10);
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        DAT_804363a0[1] = 1;
        zz_0197854_(5);
        uVar5 = 0;
        zz_0088398_(DAT_80436238 + 0xfe800,0x100000,0);
        zz_00059b8_();
        uVar6 = zz_000bb70_();
        uVar6 = zz_0044848_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0x12);
        zz_007fd6c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_01ecfe4_,0,
                    uVar5,in_r6,in_r7,in_r8,in_r9,in_r10);
        uVar6 = set_global_menu_mode(6);
        uVar6 = zz_0041954_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,0);
        zz_004453c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,extraout_r4,
                    uVar5,in_r6,in_r7,in_r8,in_r9,in_r10);
        zz_0087718_(DAT_803c71e0);
        param_1 = zz_0027aac_(0xe0e0e000,0x20,0);
      }
      else if (cVar1 < '\0') goto LAB_801ecac8;
      iVar4 = zz_000a3c4_();
      if ((iVar4 != 0) || (iVar4 = zz_0027adc_(), iVar4 != 0)) goto LAB_801ecac8;
      DAT_804363a0[1] = DAT_804363a0[1] + '\x01';
      param_1 = zz_01b1ba4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
      goto LAB_801eca08;
    }
    if ('\x03' < cVar1) goto LAB_801ecac8;
  }
  iVar4 = zz_000a3c4_();
  if (iVar4 == 0) {
    *DAT_804363a0 = 1;
    puVar3 = DAT_804363a0;
    DAT_804363a0[1] = 0;
    zz_0008a94_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb384,puVar3,
                (undefined *)0x1,in_r6,in_r7,in_r8,in_r9,in_r10);
    uVar6 = zz_0027aac_(0,0x10,0);
    zz_00e99c8_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,0,DAT_8031a084,in_r6
                ,in_r7,in_r8,in_r9,in_r10);
    zz_01ecf40_();
    zz_01ed024_();
    FUN_801ed428();
  }
LAB_801ecac8:
  zz_01ecea0_();
  return;
}



// ==== 801ecadc  FUN_801ecadc ====

void FUN_801ecadc(void)

{
  char cVar1;
  short sVar2;
  int iVar3;
  uint uVar4;
  uint local_8;
  int local_4;
  
  local_4 = (int)*(short *)(DAT_804363a0 + 0x74);
  local_8 = (uint)*(short *)(DAT_804363a0 + 0x76);
  cVar1 = DAT_804363a0[0x68e];
  sVar2 = *(short *)(DAT_804363a0 + 0x78);
  DAT_804363a0[0x68e] = cVar1 + 1U;
  if (0x78 < (byte)(cVar1 + 1U)) {
    DAT_804363a0[0x68e] = 0;
  }
  cVar1 = DAT_804363a0[1];
  if (cVar1 == '\x01') {
    uVar4 = *(uint *)(DAT_804363a0 + 0xc);
    if ((uVar4 & 0x800) == 0) {
      if (((uVar4 & 0x400) == 0) && ((uVar4 & 0x100) == 0)) {
        if ((uVar4 & 0x200) == 0) {
          iVar3 = zz_017d3e0_(*(uint *)(DAT_804363a0 + 0x10),&local_4,&local_8,(int)sVar2,0xd);
          if (iVar3 != 0) {
            *(short *)(DAT_804363a0 + 0x74) = (short)local_4;
            *(short *)(DAT_804363a0 + 0x76) = (short)local_8;
            DAT_804363a0[0x68e] = 0;
            zz_01ed3f4_();
            zz_00f036c_(0,0x77);
          }
        }
        else {
          *DAT_804363a0 = 3;
          DAT_804363a0[1] = 0;
          zz_00f036c_(0,0x7b);
        }
      }
      else {
        iVar3 = ((int)*(short *)(DAT_804363a0 + 0x74) + (int)*(short *)(DAT_804363a0 + 0x76)) * 6;
        if (DAT_804363a0[iVar3 + 0x80] == '\0' && DAT_804363a0[iVar3 + 0x81] == '\0') {
          zz_00f036c_(0,0x7d);
        }
        else {
          DAT_804363a0[1] = DAT_804363a0[1] + '\x01';
          DAT_804363a0[0x68f] = 0;
          zz_0027aac_(0,8,1);
          zz_00f036c_(0,0x7a);
        }
      }
    }
    else {
      sVar2 = *(short *)(DAT_804363a0 + 0x7a);
      *(short *)(DAT_804363a0 + 0x7a) = sVar2 + 1;
      if (3 < (short)(sVar2 + 1)) {
        *(undefined2 *)(DAT_804363a0 + 0x7a) = 0;
      }
      zz_01ed0e4_();
      zz_00f036c_(0,0x77);
    }
  }
  else if (cVar1 < '\x01') {
    if ((-1 < cVar1) && (iVar3 = zz_0027adc_(), iVar3 == 0)) {
      DAT_804363a0[1] = DAT_804363a0[1] + '\x01';
    }
  }
  else if ((cVar1 < '\x03') && (iVar3 = zz_0027adc_(), iVar3 == 0)) {
    *DAT_804363a0 = 2;
    DAT_804363a0[1] = 0;
  }
  zz_01ecea0_();
  return;
}



// ==== 801eccf0  FUN_801eccf0 ====

void FUN_801eccf0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8)

{
  char cVar1;
  byte bVar2;
  
  cVar1 = DAT_804363a0[1];
  if (cVar1 == '\x01') {
    bVar2 = zz_01dc970_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8);
    if (bVar2 != 0) {
      DAT_804363a0[1] = DAT_804363a0[1] + '\x01';
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      DAT_804363a0[1] = cVar1 + '\x01';
      zz_01dc8e8_(0,DAT_804363a0[0x68c],(int)(char)DAT_804363a0[0x68f],
                  (undefined2 *)(DAT_804363a0 + 0x67c));
    }
  }
  else if (cVar1 < '\x03') {
    *DAT_804363a0 = 1;
    DAT_804363a0[1] = 0;
    zz_01ed3f4_();
    zz_0027aac_(0,8,0);
  }
  return;
}



// ==== 801ecdb0  FUN_801ecdb0 ====

void FUN_801ecdb0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                 undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                 undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  int iVar3;
  short sVar4;
  
  iVar2 = DAT_804363a0;
  cVar1 = *(char *)(DAT_804363a0 + 1);
  if (cVar1 == '\x01') {
    iVar2 = zz_0027adc_();
    if (iVar2 == 0) {
      *(char *)(DAT_804363a0 + 1) = *(char *)(DAT_804363a0 + 1) + '\x01';
      *(undefined2 *)(DAT_804363a0 + 4) = 4;
      *(undefined1 *)(DAT_804363a0 + 0x68d) = 0;
    }
  }
  else if (cVar1 < '\x01') {
    if (-1 < cVar1) {
      *(char *)(DAT_804363a0 + 1) = cVar1 + '\x01';
      zz_0027aac_(0,0x20,1);
      zz_00e9b60_((double)FLOAT_8043c3d8,2,0x20,2);
    }
  }
  else if (cVar1 < '\x03') {
    iVar3 = *(short *)(DAT_804363a0 + 4) + -1;
    sVar4 = (short)iVar3;
    *(short *)(DAT_804363a0 + 4) = sVar4;
    if (sVar4 < 1) {
      zz_01ecfe4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,iVar2,
                  param_11,param_12,param_13,param_14,param_15,param_16);
      zz_007fd5c_();
      *PTR_DAT_80433930 = 2;
      PTR_DAT_80433930[1] = 0;
      return;
    }
  }
  zz_01ecea0_();
  return;
}



// ==== 801ecea0  zz_01ecea0_ ====

void zz_01ecea0_(void)

{
  zz_01ecec4_();
  zz_01ecef8_();
  return;
}



// ==== 801ecec4  zz_01ecec4_ ====

void zz_01ecec4_(void)

{
  zz_0089898_(0x28);
  zz_0089898_(0x38);
  zz_0089554_();
  zz_0089658_();
  return;
}



// ==== 801ecef8  zz_01ecef8_ ====

void zz_01ecef8_(void)

{
  zz_008a16c_();
  zz_0089c00_(0x28);
  zz_0089c00_(0x38);
  zz_008c0dc_(FUN_80089eb4);
  zz_008c104_(FUN_80089f28);
  return;
}



// ==== 801ecf40  zz_01ecf40_ ====

void zz_01ecf40_(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  float *pfVar5;
  
  iVar4 = 0;
  pfVar5 = (float *)&DAT_803a10bc;
  iVar3 = 0;
  iVar2 = 0;
  do {
    gnt4_C_MTXLookAt_bl((float *)(DAT_804363a0 + iVar4 + 0x14),(float *)&DAT_803a10b0,
                        (float *)&DAT_803a10d4,pfVar5);
    iVar1 = iVar2 + 0xc;
    *(int *)(PTR_DAT_80433930 + iVar3 + 0x14) = DAT_804363a0 + iVar4 + 0x14;
    iVar2 = iVar2 + 1;
    pfVar5 = pfVar5 + 3;
    iVar4 = iVar4 + 0x30;
    iVar3 = iVar3 + 4;
    PTR_DAT_80433930[iVar1] = 0xff;
  } while (iVar2 < 2);
  return;
}



// ==== 801ecfe4  zz_01ecfe4_ ====

void zz_01ecfe4_(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
                undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
                undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined8 uVar1;
  
  zz_0008b58_();
  uVar1 = zz_01978d0_();
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,extraout_r4,
                      param_11,param_12,param_13,param_14,param_15,param_16);
  uVar1 = zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1,extraout_r4_00
                      ,param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00e9ac0_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,2,extraout_r4_01,
              param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00f07c4_();
  return;
}



// ==== 801ed024  zz_01ed024_ ====

void zz_01ed024_(void)

{
  int iVar1;
  uint uVar2;
  short *psVar3;
  int iVar4;
  short sVar5;
  int iVar6;
  
  iVar1 = DAT_804363a0;
  iVar6 = 0;
  iVar4 = 0;
  *(undefined2 *)(DAT_804363a0 + 0x78) = 0;
  psVar3 = (short *)(iVar1 + 0x7c);
  do {
    sVar5 = (short)iVar4;
    *(char *)(psVar3 + 1) = (char)iVar6;
    uVar2 = zz_0066200_(iVar6);
    *psVar3 = (short)uVar2;
    if (*psVar3 < 0) break;
    *(undefined1 *)(psVar3 + 2) = (&DAT_803bfe78)[iVar6];
    *(undefined1 *)((int)psVar3 + 5) = (&DAT_803bff78)[iVar6];
    if (*(char *)(psVar3 + 2) != '\0' || *(char *)((int)psVar3 + 5) != '\0') {
      iVar4 = iVar6;
    }
    sVar5 = (short)iVar4;
    iVar6 = iVar6 + 1;
    psVar3 = psVar3 + 3;
  } while (iVar6 < 0xce);
  *(short *)(DAT_804363a0 + 0x78) = sVar5 + 1;
  zz_01ed0e4_();
  return;
}



// ==== 801ed0e4  zz_01ed0e4_ ====

void zz_01ed0e4_(void)

{
  char cVar1;
  short sVar2;
  bool bVar3;
  int iVar4;
  char *__s1;
  char *__s2;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined2 *__src;
  undefined2 *__src_00;
  int iVar11;
  undefined2 local_68 [2];
  undefined2 local_64 [2];
  undefined2 local_60 [2];
  undefined2 local_5c [2];
  undefined2 local_58 [2];
  undefined2 local_54 [2];
  undefined1 auStack_50 [8];
  char acStack_48 [8];
  char acStack_40 [16];
  
  iVar8 = 0;
  iVar11 = 0;
  iVar9 = (int)*(short *)(DAT_804363a0 + 0x76);
  iVar10 = (int)*(short *)(DAT_804363a0 + 0x78);
  cVar1 = *(char *)(DAT_804363a0 + (*(short *)(DAT_804363a0 + 0x74) + iVar9) * 6 + 0x7e);
  do {
    if (iVar10 + -1 <= iVar8) {
      iVar7 = 0;
      iVar11 = 0;
      iVar8 = iVar10;
      if (0 < iVar10) {
        do {
          if (cVar1 == *(char *)(DAT_804363a0 + iVar11 + 0x7e)) {
            iVar6 = iVar7 - iVar9;
            if (iVar6 < 0) {
              iVar9 = iVar9 + iVar6;
              iVar6 = 0;
            }
            else {
              iVar4 = iVar6 + 0xd;
              if (iVar10 < iVar4) {
                iVar6 = iVar10 + -0xd;
                iVar9 = iVar9 + (iVar4 - iVar10);
              }
            }
            *(short *)(DAT_804363a0 + 0x74) = (short)iVar6;
            *(short *)(DAT_804363a0 + 0x76) = (short)iVar9;
          }
          iVar11 = iVar11 + 6;
          iVar7 = iVar7 + 1;
          iVar8 = iVar8 + -1;
        } while (iVar8 != 0);
      }
      zz_01ed3f4_();
      return;
    }
    iVar7 = iVar8 + 1;
    iVar6 = iVar7 * 6;
    for (; iVar7 < iVar10; iVar7 = iVar7 + 1) {
      bVar3 = false;
      sVar2 = *(short *)(DAT_804363a0 + 0x7a);
      __src_00 = (undefined2 *)(DAT_804363a0 + iVar11 + 0x7c);
      __src = (undefined2 *)(DAT_804363a0 + iVar6 + 0x7c);
      if (sVar2 == 2) {
        if (*(char *)(__src_00 + 2) == '\0' && *(char *)((int)__src_00 + 5) == '\0') {
          iVar4 = 0x14;
        }
        else {
          local_5c[0] = *__src_00;
          iVar4 = zz_0066298_((char *)local_5c);
        }
        if (*(char *)(__src + 2) == '\0' && *(char *)((int)__src + 5) == '\0') {
          iVar5 = 0x14;
        }
        else {
          local_60[0] = *__src;
          iVar5 = zz_0066298_((char *)local_60);
        }
        if ((int)(iVar5 << 0x10 | (uint)*(byte *)(__src + 1)) <
            (int)(iVar4 << 0x10 | (uint)*(byte *)(__src_00 + 1))) {
          bVar3 = true;
        }
      }
      else if (sVar2 < 2) {
        if ((sVar2 == 0) || (sVar2 < 0)) {
LAB_801ed174:
          if (*(byte *)(__src + 1) < *(byte *)(__src_00 + 1)) {
            bVar3 = true;
          }
        }
        else {
          sprintf(acStack_40,&DAT_8043c3dc,(uint)*(byte *)(__src_00 + 1));
          sprintf(acStack_48,&DAT_8043c3dc,(uint)*(byte *)(__src + 1));
          if (*(char *)(__src_00 + 2) == '\0' && *(char *)((int)__src_00 + 5) == '\0') {
            __s1 = acStack_40;
          }
          else {
            local_54[0] = *__src_00;
            __s1 = (char *)zz_0066270_((char *)local_54);
          }
          if (*(char *)(__src + 2) == '\0' && *(char *)((int)__src + 5) == '\0') {
            __s2 = acStack_48;
          }
          else {
            local_58[0] = *__src;
            __s2 = (char *)zz_0066270_((char *)local_58);
          }
          iVar4 = gnt4_strcmp(__s1,__s2);
          if (0 < iVar4) {
            bVar3 = true;
          }
        }
      }
      else {
        if (3 < sVar2) goto LAB_801ed174;
        if (*(char *)(__src_00 + 2) == '\0' && *(char *)((int)__src_00 + 5) == '\0') {
          iVar4 = 5;
        }
        else {
          local_64[0] = *__src_00;
          iVar4 = zz_00662c0_((char *)local_64,0);
          iVar4 = 4 - iVar4;
        }
        if (*(char *)(__src + 2) == '\0' && *(char *)((int)__src + 5) == '\0') {
          iVar5 = 5;
        }
        else {
          local_68[0] = *__src;
          iVar5 = zz_00662c0_((char *)local_68,0);
          iVar5 = 4 - iVar5;
        }
        if ((int)(iVar5 << 0x10 | (uint)*(byte *)(__src + 1)) <
            (int)(iVar4 << 0x10 | (uint)*(byte *)(__src_00 + 1))) {
          bVar3 = true;
        }
      }
      if (bVar3) {
        gnt4_memcpy(auStack_50,__src_00,6);
        gnt4_memcpy(__src_00,__src,6);
        gnt4_memcpy(__src,auStack_50,6);
      }
      iVar6 = iVar6 + 6;
    }
    iVar11 = iVar11 + 6;
    iVar8 = iVar8 + 1;
  } while( true );
}



// ==== 801ed3f4  zz_01ed3f4_ ====

void zz_01ed3f4_(void)

{
  int iVar1;
  
  iVar1 = DAT_804363a0;
  *(undefined2 *)(DAT_804363a0 + 0x67c) =
       *(undefined2 *)
        (DAT_804363a0 +
        ((int)*(short *)(DAT_804363a0 + 0x74) + (int)*(short *)(DAT_804363a0 + 0x76)) * 6 + 0x7c);
  *(undefined1 *)(iVar1 + 0x67e) = 0;
  *(undefined1 *)(iVar1 + 0x67f) = 0;
  *(undefined4 *)(iVar1 + 0x684) = 0;
  return;
}



// ==== 801ed428  FUN_801ed428 ====

/* WARNING: Removing unreachable block (ram,0x801ed50c) */
/* WARNING: Removing unreachable block (ram,0x801ed504) */
/* WARNING: Removing unreachable block (ram,0x801ed4fc) */
/* WARNING: Removing unreachable block (ram,0x801ed448) */
/* WARNING: Removing unreachable block (ram,0x801ed440) */
/* WARNING: Removing unreachable block (ram,0x801ed438) */

void FUN_801ed428(void)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  for (piVar1 = &DAT_803a10e0; -1 < *piVar1; piVar1 = piVar1 + 5) {
    FUN_801ed534(piVar1);
  }
  dVar5 = (double)FLOAT_8043c3e8;
  uVar3 = 0;
  dVar6 = DOUBLE_8043c3f0;
  do {
    dVar4 = (double)(float)(dVar5 * (double)(float)((double)CONCAT44(0x43300000,uVar3 ^ 0x80000000)
                                                   - dVar6));
    for (piVar1 = &DAT_803a1248; -1 < *piVar1; piVar1 = piVar1 + 5) {
      iVar2 = FUN_801ed534(piVar1);
      *(char *)(iVar2 + 0x12) = (char)uVar3;
      *(float *)(iVar2 + 0x68) = (float)((double)*(float *)(iVar2 + 0x68) + dVar4);
    }
    uVar3 = uVar3 + 1;
  } while ((int)uVar3 < 0xd);
  *(undefined1 *)(DAT_804363a0 + 0x68d) = 1;
  return;
}



// ==== 801ed534  FUN_801ed534 ====

void FUN_801ed534(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined1 *puVar2;
  
  puVar2 = zz_008893c_(2,0x28,1,1);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x10] = 0;
    puVar2[0x11] = (char)param_1[1];
    *(code **)(puVar2 + 0xc) = FUN_801ed5e4;
    *(code **)(puVar2 + 0x10c) = FUN_801ee088;
    *(undefined4 *)(puVar2 + 0x144) = *param_1;
    uVar1 = param_1[2];
    *(undefined4 *)(puVar2 + 100) = uVar1;
    *(undefined4 *)(puVar2 + 0x148) = uVar1;
    uVar1 = param_1[3];
    *(undefined4 *)(puVar2 + 0x68) = uVar1;
    *(undefined4 *)(puVar2 + 0x14c) = uVar1;
    uVar1 = param_1[4];
    *(undefined4 *)(puVar2 + 0x6c) = uVar1;
    *(undefined4 *)(puVar2 + 0x150) = uVar1;
    *(undefined4 *)(puVar2 + 0x154) = DAT_803bb384;
  }
  return;
}



// ==== 801ed5e4  FUN_801ed5e4 ====

void FUN_801ed5e4(int param_1)

{
  (*(code *)(&PTR_FUN_803a1324)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801ed620  FUN_801ed620 ====

void FUN_801ed620(int param_1)

{
  float fVar1;
  
  *(undefined1 *)(param_1 + 0x18) = 1;
  *(undefined1 *)(param_1 + 0x84) = 0x1f;
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0,1);
  fVar1 = FLOAT_8043c3f8;
  *(undefined2 *)(param_1 + 0x74) = 0;
  *(undefined2 *)(param_1 + 0x72) = 0;
  *(undefined2 *)(param_1 + 0x70) = 0;
  *(float *)(param_1 + 0x60) = fVar1;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  *(char *)(param_1 + 0x13) = (char)*(undefined4 *)(param_1 + 0x144);
  *(undefined4 *)(param_1 + 0x17c) = 0xffffffff;
  *(undefined4 *)(param_1 + 0x180) = 0xffffffff;
  FUN_801ed6ac(param_1);
  return;
}



// ==== 801ed6ac  FUN_801ed6ac ====

void FUN_801ed6ac(int param_1)

{
  (*(code *)(&PTR_FUN_803a1334)[*(char *)(param_1 + 0x11)])();
  if (*(char *)(DAT_804363a0 + 0x68d) == '\0') {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801ed714  FUN_801ed714 ====

void FUN_801ed714(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  if (*(char *)(param_9 + 0x19) == '\0') {
    *(undefined1 *)(param_9 + 0x19) = 1;
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 801ed764  FUN_801ed764 ====

void FUN_801ed764(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar3;
  int iVar2;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(char *)(param_9 + 0x13) = (char)*(undefined4 *)(param_9 + 0x144);
    param_1 = zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                          param_11,param_12,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  sVar3 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar3;
  if (0x3b < sVar3) {
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  iVar2 = (int)*(short *)(param_9 + 0x1c) / 0x1e + ((int)*(short *)(param_9 + 0x1c) >> 0x1f);
  iVar2 = iVar2 - (iVar2 >> 0x1f);
  if (*(int *)(param_9 + 0x180) != iVar2) {
    *(int *)(param_9 + 0x180) = iVar2;
    *(int *)(param_9 + 0x144) = *(char *)(param_9 + 0x13) + iVar2;
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,iVar2,
                param_12,param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801ed838  FUN_801ed838 ====

void FUN_801ed838(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  short sVar2;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 0;
    if (*(char *)(param_9 + 0x11) == '\x03') {
      *(undefined2 *)(param_9 + 0x74) = 0x8000;
    }
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
  }
  sVar2 = *(short *)(param_9 + 0x1c) + 1;
  *(short *)(param_9 + 0x1c) = sVar2;
  if (0x46 < sVar2) {
    *(undefined2 *)(param_9 + 0x1c) = 0;
  }
  if (*(short *)(param_9 + 0x1c) < 0x32) {
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  else {
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  return;
}



// ==== 801ed8f0  FUN_801ed8f0 ====

void FUN_801ed8f0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  double dVar2;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if ('\0' < cVar1) {
      return;
    }
    if (cVar1 < '\0') {
      return;
    }
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined2 *)(param_9 + 0x1c) = 0;
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
    *(undefined4 *)(param_9 + 0x174) = 1;
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  *(float *)(param_9 + 0x68) =
       FLOAT_8043c3e8 *
       (float)((double)CONCAT44(0x43300000,(int)*(short *)(DAT_804363a0 + 0x76) ^ 0x80000000) -
              DOUBLE_8043c3f0) + *(float *)(param_9 + 0x14c);
  dVar2 = zz_0045238_((short)(((uint)*(byte *)(DAT_804363a0 + 0x68e) << 0x10) / 0x78));
  *(float *)(param_9 + 0x178) = (float)((double)FLOAT_8043c400 * dVar2 + (double)FLOAT_8043c3fc);
  return;
}



// ==== 801ed9d0  FUN_801ed9d0 ====

void FUN_801ed9d0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  if (*(char *)(param_9 + 0x19) == '\0') {
    *(undefined1 *)(param_9 + 0x19) = 1;
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 801eda20  FUN_801eda20 ====

void FUN_801eda20(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  uint extraout_r4;
  
  uVar1 = (uint)*(byte *)(param_9 + 0x19);
  if (uVar1 == 0) {
    *(byte *)(param_9 + 0x19) = *(byte *)(param_9 + 0x19) + 1;
    param_1 = zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,
                          param_11,param_12,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
    uVar1 = extraout_r4;
  }
  FUN_801edad8(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar1,
               param_11,param_12,param_13,param_14,param_15,param_16);
  FUN_801eda80(param_9);
  return;
}



// ==== 801eda80  FUN_801eda80 ====

void FUN_801eda80(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  fVar3 = FLOAT_8043c408;
  fVar2 = FLOAT_8043c404;
  fVar1 = FLOAT_8043c3f8;
  if ((int)*(char *)(param_1 + 0x12) == (int)*(short *)(DAT_804363a0 + 0x76)) {
    *(float *)(param_1 + 0x60) = FLOAT_8043c404;
    *(float *)(param_1 + 0x5c) = fVar2;
    *(float *)(param_1 + 0x58) = fVar2;
    *(float *)(param_1 + 0x6c) = fVar3 + *(float *)(param_1 + 0x150);
    return;
  }
  *(float *)(param_1 + 0x60) = FLOAT_8043c3f8;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  *(undefined4 *)(param_1 + 0x6c) = *(undefined4 *)(param_1 + 0x150);
  return;
}



// ==== 801edad8  FUN_801edad8 ====

void FUN_801edad8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  double dVar2;
  uint uVar3;
  
  dVar2 = DOUBLE_8043c3f0;
  uVar3 = countLeadingZeros((int)*(short *)(DAT_804363a0 + 0x76) - (int)*(char *)(param_9 + 0x12));
  pfVar1 = (float *)(uVar3 >> 5);
  if (*(float **)(param_9 + 0x17c) != pfVar1) {
    *(float **)(param_9 + 0x17c) = pfVar1;
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,(uint)pfVar1 ^ 0x80000000) - dVar2),
                param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar1,param_12,
                param_13,param_14,param_15,param_16);
  }
  return;
}



// ==== 801edb44  FUN_801edb44 ====

void FUN_801edb44(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if (('\0' < cVar1) || (cVar1 < '\0')) goto LAB_801edbc4;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
  }
  if (*(char *)(DAT_804363a0 +
               ((int)*(short *)(DAT_804363a0 + 0x74) + (int)*(char *)(param_9 + 0x12)) * 6 + 0x7f)
      == '\0') {
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
LAB_801edbc4:
  FUN_801eda80(param_9);
  return;
}



// ==== 801edbe0  FUN_801edbe0 ====

void FUN_801edbe0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if (('\0' < cVar1) || (cVar1 < '\0')) goto LAB_801edc60;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,param_11,
                param_12,param_13,param_14,param_15,param_16);
  }
  if (*(char *)(DAT_804363a0 +
               ((int)*(short *)(DAT_804363a0 + 0x74) + (int)*(char *)(param_9 + 0x12)) * 6 + 0x80)
      == '\0') {
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
LAB_801edc60:
  FUN_801eda80(param_9);
  return;
}



// ==== 801edc7c  FUN_801edc7c ====

void FUN_801edc7c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  double dVar2;
  int iVar3;
  float *pfVar4;
  undefined2 *puVar5;
  undefined2 local_18 [4];
  undefined4 local_10;
  uint uStack_c;
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if (('\0' < cVar1) || (cVar1 < '\0')) goto LAB_801eddc4;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  puVar5 = (undefined2 *)
           (DAT_804363a0 +
           ((int)*(short *)(DAT_804363a0 + 0x74) + (int)*(char *)(param_9 + 0x12)) * 6 + 0x7c);
  local_18[0] = *puVar5;
  iVar3 = zz_0066298_((char *)local_18);
  if ((*(char *)(puVar5 + 2) == '\0') && (*(char *)((int)puVar5 + 5) == '\0')) {
    iVar3 = 0x14;
  }
  if (*(int *)(param_9 + 0x180) != iVar3) {
    *(int *)(param_9 + 0x180) = iVar3;
    *(undefined4 *)(param_9 + 0x17c) = 0xffffffff;
    *(int *)(param_9 + 0x144) = *(char *)(param_9 + 0x13) + iVar3;
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,iVar3,
                param_12,param_13,param_14,param_15,param_16);
  }
  dVar2 = DOUBLE_8043c3f0;
  if ((int)*(char *)(param_9 + 0x12) == (int)*(short *)(DAT_804363a0 + 0x76)) {
    pfVar4 = (float *)0x1;
  }
  else if ((*(char *)(puVar5 + 2) == '\0') && (*(char *)((int)puVar5 + 5) == '\0')) {
    pfVar4 = (float *)0x2;
  }
  else {
    pfVar4 = (float *)0x0;
  }
  if (*(float **)(param_9 + 0x17c) != pfVar4) {
    uStack_c = (uint)pfVar4 ^ 0x80000000;
    local_10 = 0x43300000;
    *(float **)(param_9 + 0x17c) = pfVar4;
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,uStack_c) - dVar2),param_2,param_3,
                param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar4,param_12,param_13,param_14,
                param_15,param_16);
  }
LAB_801eddc4:
  FUN_801eda80(param_9);
  return;
}



// ==== 801edde4  FUN_801edde4 ====

void FUN_801edde4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined2 *puVar5;
  undefined2 local_18 [8];
  
  cVar1 = *(char *)(param_9 + 0x19);
  if (cVar1 != '\x01') {
    if (('\0' < cVar1) || (cVar1 < '\0')) goto LAB_801edea8;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
  }
  iVar3 = ((int)*(short *)(DAT_804363a0 + 0x74) + (int)*(char *)(param_9 + 0x12)) * 6;
  puVar5 = (undefined2 *)(DAT_804363a0 + iVar3 + 0x7c);
  local_18[0] = *puVar5;
  iVar4 = DAT_804363a0;
  iVar2 = zz_00662c0_((char *)local_18,0);
  if (*(int *)(param_9 + 0x180) != iVar2) {
    *(int *)(param_9 + 0x180) = iVar2;
    *(int *)(param_9 + 0x144) = *(char *)(param_9 + 0x13) + iVar2;
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,iVar3,
                iVar4,in_r7,in_r8,in_r9,in_r10);
  }
  if (*(char *)(puVar5 + 2) == '\0' && *(char *)((int)puVar5 + 5) == '\0') {
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
LAB_801edea8:
  FUN_801eda80(param_9);
  return;
}



// ==== 801edec8  FUN_801edec8 ====

void FUN_801edec8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  double dVar2;
  float *pfVar3;
  uint uVar4;
  int iVar5;
  
  cVar1 = *(char *)(param_9 + 0x19);
  pfVar3 = (float *)(int)*(char *)(param_9 + 0x11);
  iVar5 = (int)pfVar3 + -0xb;
  if (cVar1 != '\x01') {
    if (('\0' < cVar1) || (cVar1 < '\0')) goto LAB_801ee034;
    *(char *)(param_9 + 0x19) = cVar1 + '\x01';
    zz_01a7688_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar3,
                param_12,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  dVar2 = DOUBLE_8043c3f0;
  uVar4 = *(byte *)(DAT_804363a0 +
                   ((int)*(short *)(DAT_804363a0 + 0x74) + (int)*(char *)(param_9 + 0x12)) * 6 +
                   0x7e) + 1;
  if (iVar5 == 1) {
    pfVar3 = (float *)0x66666667;
    uVar4 = (uVar4 / 10) % 10;
  }
  else if (iVar5 < 1) {
    if (-1 < iVar5) {
      uVar4 = uVar4 % 10;
    }
  }
  else if (iVar5 < 3) {
    uVar4 = uVar4 / 100;
  }
  if (*(uint *)(param_9 + 0x180) != uVar4) {
    *(uint *)(param_9 + 0x180) = uVar4;
    zz_01a76fc_((double)(float)((double)CONCAT44(0x43300000,uVar4 ^ 0x80000000) - dVar2),param_2,
                param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,pfVar3,uVar4,param_13,
                param_14,param_15,param_16);
  }
LAB_801ee034:
  FUN_801eda80(param_9);
  return;
}



// ==== 801ee068  FUN_801ee068 ====

void FUN_801ee068(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801ee088  FUN_801ee088 ====

void FUN_801ee088(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  undefined8 uVar1;
  
  FUN_801ee0c4(param_9);
  uVar1 = FUN_801ee144(param_9);
  zz_01a77e8_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
              param_11,param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 801ee0c4  FUN_801ee0c4 ====

void FUN_801ee0c4(int param_1)

{
  if (*(char *)(param_1 + 0x11) == '\x04') {
    zz_0096d0c_((double)FLOAT_8043c40c);
    zz_0096d14_((double)FLOAT_8043c410);
    zz_0097144_(0x1c0,0x30,0x18,PTR_DAT_803a1310);
    zz_0097144_(0x1f0,0x30,0x18,(&PTR_DAT_803a1314)[*(short *)(DAT_804363a0 + 0x7a)]);
  }
  return;
}



// ==== 801ee144  FUN_801ee144 ====

void FUN_801ee144(int param_1)

{
  short sVar1;
  char *__src;
  uint uVar2;
  short sVar3;
  undefined2 *puVar4;
  int iVar5;
  undefined2 local_68 [2];
  byte abStack_64 [68];
  undefined4 local_20;
  uint uStack_1c;
  undefined4 local_18;
  uint uStack_14;
  
  if (*(char *)(param_1 + 0x11) == '\t') {
    puVar4 = (undefined2 *)
             (DAT_804363a0 +
             ((int)*(short *)(DAT_804363a0 + 0x74) + (int)*(char *)(param_1 + 0x12)) * 6 + 0x7c);
    if (*(char *)(puVar4 + 2) == '\0' && *(char *)((int)puVar4 + 5) == '\0') {
      strcpy((char *)abStack_64,&DAT_802b3ce8);
    }
    else {
      local_68[0] = *puVar4;
      __src = (char *)zz_0066270_((char *)local_68);
      strcpy((char *)abStack_64,__src);
    }
    uVar2 = 0xf;
    sVar1 = *(char *)(param_1 + 0x12) * 0x17;
    sVar3 = sVar1 + 0x6a;
    if ((int)*(char *)(param_1 + 0x12) == (int)*(short *)(DAT_804363a0 + 0x76)) {
      uVar2 = 0x11;
      iVar5 = 0x1a;
      sVar3 = sVar1 + 0x69;
    }
    else if (*(char *)(puVar4 + 2) == '\0' && *(char *)((int)puVar4 + 5) == '\0') {
      iVar5 = 0x19;
    }
    else {
      iVar5 = 0x18;
    }
    uStack_1c = uVar2 ^ 0x80000000;
    local_20 = 0x43300000;
    zz_0096d0c_((double)((float)((double)CONCAT44(0x43300000,uStack_1c) - DOUBLE_8043c3f0) /
                        FLOAT_8043c414));
    uStack_14 = uVar2 ^ 0x80000000;
    local_18 = 0x43300000;
    zz_0096d14_((double)(float)((double)CONCAT44(0x43300000,uStack_14) - DOUBLE_8043c3f0));
    zz_0097144_(0x80,sVar3,iVar5,abStack_64);
  }
  return;
}



// ==== 801ee294  zz_01ee294_ ====

void zz_01ee294_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x203) || (*(short *)(param_1 + 1000) == 0x20c)) &&
     (puVar1 = zz_0088aa0_(param_1,3,0,0,4), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_801ee3a4;
    *(code **)(puVar1 + 0x10c) = FUN_801ee660;
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



// ==== 801ee3a4  FUN_801ee3a4 ====

void FUN_801ee3a4(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803a1388)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801ee3f8  FUN_801ee3f8 ====

void FUN_801ee3f8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  int iVar4;
  int iVar5;
  uint uVar6;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar7;
  undefined8 uVar8;
  
  uVar6 = (uint)*(byte *)(param_9 + 0x11);
  iVar7 = *(int *)(param_9 + 0x90);
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar3 = (char)*(byte *)(param_9 + 0x11) * 0x18;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar8 = zz_0089100_(param_9,(int)*(char *)(iVar7 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_8043c418;
  *(undefined1 *)(param_9 + 0x84) = 0x53;
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_803a1374 + iVar3);
  uVar2 = *(undefined4 *)(&DAT_803a1380 + iVar3);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803a137c + iVar3);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803a1384 + iVar3);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(&DAT_803a1376 + iVar3);
  *(undefined2 *)(param_9 + 0x74) = *(undefined2 *)(&DAT_803a137a + iVar3);
  *(float *)(param_9 + 0xb4) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x60) = fVar1;
  iVar7 = zz_0006f98_(iVar7);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe0),
                      (int)*(short *)(&DAT_803a1370 + iVar3),iVar7 + 0xc28,uVar6,in_r8,in_r9,in_r10)
  ;
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe8),
                      (int)*(short *)(&DAT_803a1372 + iVar3),iVar7 + 0xc28,uVar6,in_r8,in_r9,in_r10)
  ;
  iVar5 = iVar7 + 0xc28;
  iVar4 = (int)*(short *)(&DAT_803a1370 + iVar3);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xe4),iVar4,iVar5,uVar6,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar4,iVar5,uVar6,in_r8,in_r9,in_r10);
  uVar8 = zz_0007cac_((double)FLOAT_8043c41c,*(int *)(param_9 + 0xe4));
  iVar4 = iVar7 + 0xc28;
  iVar3 = (int)*(short *)(&DAT_803a1372 + iVar3);
  uVar8 = zz_0007030_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar7 + 0x600),*(int *)(param_9 + 0xec),iVar3,iVar4,uVar6,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xec)
              ,extraout_r4_00,iVar3,iVar4,uVar6,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043c41c,*(int *)(param_9 + 0xec));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  zz_01ee560_(param_9);
  return;
}



// ==== 801ee560  zz_01ee560_ ====

void zz_01ee560_(int param_1)

{
  float fVar1;
  double dVar2;
  
  dVar2 = DOUBLE_8043c438;
  fVar1 = FLOAT_8043c424;
  if ((*(byte *)(*(int *)(param_1 + 0x90) + 0x6e9) & 0x10) == 0) {
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) - FLOAT_8043c420;
  }
  else {
    *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + FLOAT_8043c420;
    *(short *)(param_1 + 0x70) =
         (short)(int)(fVar1 * *(float *)(*(int *)(param_1 + 0x90) + 0x1dc8) +
                     (float)((double)CONCAT44(0x43300000,
                                              (int)*(short *)(param_1 + 0x70) ^ 0x80000000) - dVar2)
                     );
  }
  if (DOUBLE_8043c428 < (double)*(float *)(param_1 + 0x58)) {
    *(float *)(param_1 + 0x58) = FLOAT_8043c430;
  }
  if (*(float *)(param_1 + 0x58) < FLOAT_8043c434) {
    *(float *)(param_1 + 0x58) = FLOAT_8043c434;
  }
  *(undefined4 *)(param_1 + 0x60) = *(undefined4 *)(param_1 + 0x58);
  *(undefined4 *)(param_1 + 0x5c) = *(undefined4 *)(param_1 + 0x58);
  return;
}



// ==== 801ee614  FUN_801ee614 ====

void FUN_801ee614(int param_1)

{
  *(char *)(param_1 + 0x18) = *(char *)(param_1 + 0x18) + '\x01';
  zz_008aff0_(param_1);
  return;
}



// ==== 801ee640  FUN_801ee640 ====

void FUN_801ee640(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801ee660  FUN_801ee660 ====

void FUN_801ee660(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined8 uVar5;
  float afStack_48 [14];
  
  if ((double)FLOAT_8043c434 < (double)*(float *)(param_9 + 0x58)) {
    if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
      iVar3 = *(int *)(param_9 + 0xe0);
      iVar2 = *(int *)(param_9 + 0xe8);
      if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
        uVar4 = 0x44;
      }
      else {
        uVar4 = 1;
      }
    }
    else {
      iVar3 = *(int *)(param_9 + 0xe4);
      uVar4 = 0x44;
      iVar2 = *(int *)(param_9 + 0xec);
    }
    zz_00076d0_((double)*(float *)(param_9 + 0x58),param_2,param_3,param_4,param_5,param_6,param_7,
                param_8,iVar3,(float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,
                param_15,param_16);
    zz_00097b4_(iVar3,uVar4);
    gnt4_PSMTXRotRad_bl((double)FLOAT_8043c440,afStack_48,0x79);
    pfVar1 = afStack_48;
    uVar5 = gnt4_PSMTXConcat_bl((float *)(param_9 + 0x114),pfVar1,pfVar1);
    zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,afStack_48,
                (undefined *)pfVar1,param_12,param_13,param_14,param_15,param_16);
    zz_00097b4_(iVar2,uVar4);
  }
  return;
}



// ==== 801ee744  zz_01ee744_ ====

void zz_01ee744_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if (((*(uint *)(param_1 + 0x8c4) & 8) == 0) &&
     (puVar1 = zz_0088aa0_(param_1,2,0x18,0,1), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x10] = 0x32;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_801ee848;
    *(code **)(puVar1 + 0x10c) = FUN_801eea4c;
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



// ==== 801ee848  FUN_801ee848 ====

void FUN_801ee848(int param_1)

{
  (*(code *)(&PTR_FUN_803a1398)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801ee884  FUN_801ee884 ====

void FUN_801ee884(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 uVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  
  fVar2 = FLOAT_8043c448;
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar4 = *(int *)(param_9 + 0x90);
  *(uint *)(iVar4 + 0x8c4) = *(uint *)(iVar4 + 0x8c4) | 8;
  *(float *)(param_9 + 0xb4) = fVar2 * *(float *)(iVar4 + 0x7fc);
  uVar1 = *(undefined4 *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0x60) = uVar1;
  *(undefined4 *)(param_9 + 0x5c) = uVar1;
  *(undefined4 *)(param_9 + 0x58) = uVar1;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,(int)*(char *)(iVar4 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x55;
  fVar2 = FLOAT_8043c44c;
  dVar5 = (double)FLOAT_8043c44c;
  *(undefined1 *)(param_9 + 0x89) = 1;
  fVar3 = FLOAT_8043c450;
  *(float *)(iVar4 + 100) = fVar2;
  *(float *)(iVar4 + 0x68) = fVar3;
  *(float *)(iVar4 + 0x6c) = fVar2;
  zz_0006fb4_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),
              (int)*(short *)(&DAT_80435b80 + *(char *)(param_9 + 0x11) * 2),param_12,param_13,
              param_14,param_15,param_16);
  *(undefined1 *)(param_9 + 0x82) = 1;
  zz_00f036c_(*(int *)(param_9 + 0x90),0x23);
  FUN_800061a8(iVar4,0xf);
  zz_01ee980_(param_9);
  return;
}



// ==== 801ee980  zz_01ee980_ ====

void zz_01ee980_(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x90);
  if ((((*(uint *)(iVar1 + 0x5e0) & 0x20000000) != 0) && ((*(uint *)(iVar1 + 0x8c4) & 8) != 0)) &&
     (*(char *)(iVar1 + 0x18) < '\x02')) {
    return;
  }
  *(uint *)(iVar1 + 0x8c4) = *(uint *)(iVar1 + 0x8c4) & 0xfffffff7;
  *(uint *)(iVar1 + 0x5e0) = *(uint *)(iVar1 + 0x5e0) & 0xdfffffff;
  *(undefined1 *)(param_1 + 0x18) = 2;
  return;
}



// ==== 801ee9d0  FUN_801ee9d0 ====

void FUN_801ee9d0(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_00b19b4_(param_1,2,0x10);
  zz_00f036c_(*(int *)(param_1 + 0x90),0x27);
  FUN_800061a8(*(int *)(param_1 + 0x90),0x12);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801eea2c  FUN_801eea2c ====

void FUN_801eea2c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801eea4c  FUN_801eea4c ====

void FUN_801eea4c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801eea8c  FUN_801eea8c ====

void FUN_801eea8c(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_801eeb74;
    *(code **)(puVar1 + 0x10c) = FUN_801eede8;
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



// ==== 801eeb74  FUN_801eeb74 ====

void FUN_801eeb74(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803a13a8)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801eebc8  FUN_801eebc8 ====

void FUN_801eebc8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar3;
  double dVar4;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar3 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,(int)*(char *)(iVar3 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x51;
  fVar1 = FLOAT_8043c458;
  *(undefined1 *)(param_9 + 0x89) = 7;
  fVar2 = FLOAT_8043c45c;
  dVar4 = (double)FLOAT_8043c45c;
  *(float *)(param_9 + 100) = fVar1;
  fVar1 = FLOAT_8043c460;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar1;
  iVar3 = zz_0006f98_(iVar3);
  zz_0007030_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar3 + 0x600),
              *(int *)(param_9 + 0xe0),9,iVar3 + 0xc28,in_r7,in_r8,in_r9,in_r10);
  *(undefined1 *)(param_9 + 0x19) = 0;
  *(undefined1 *)(param_9 + 0x82) = 0;
  zz_01eec84_(param_9);
  return;
}



// ==== 801eec84  zz_01eec84_ ====

void zz_01eec84_(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  float fVar3;
  float fVar4;
  
  fVar4 = FLOAT_8043c46c;
  fVar3 = FLOAT_8043c464;
  if (*(char *)(*(int *)(param_1 + 0x90) + 0x6f7) == '\0') {
    *(undefined1 *)(param_1 + 0x19) = 0;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  else {
    cVar1 = *(char *)(param_1 + 0x19);
    if (cVar1 == '\x01') {
      *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) + *(float *)(param_1 + 0x148);
      *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) + *(float *)(param_1 + 0x148);
      *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) + *(float *)(param_1 + 0x148);
      *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) + *(float *)(param_1 + 0x150);
      if (fVar4 < *(float *)(param_1 + 0x58)) {
        *(float *)(param_1 + 0x60) = fVar4;
        fVar3 = FLOAT_8043c470;
        *(float *)(param_1 + 0x5c) = fVar4;
        *(float *)(param_1 + 0x58) = fVar4;
        *(float *)(param_1 + 0x14c) = fVar3;
        *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
      }
      zz_0007cac_((double)*(float *)(param_1 + 0x14c),*(int *)(param_1 + 0xe0));
    }
    else if ((cVar1 < '\x01') && (-1 < cVar1)) {
      *(undefined1 *)(param_1 + 0x82) = 1;
      fVar4 = FLOAT_8043c468;
      *(float *)(param_1 + 0x148) = fVar3;
      uVar2 = *(undefined4 *)(param_1 + 0x148);
      *(undefined4 *)(param_1 + 0x60) = uVar2;
      *(undefined4 *)(param_1 + 0x5c) = uVar2;
      *(undefined4 *)(param_1 + 0x58) = uVar2;
      *(float *)(param_1 + 0x150) = fVar4;
      *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(param_1 + 0x150);
      zz_0007cac_((double)*(float *)(param_1 + 0x14c),*(int *)(param_1 + 0xe0));
      *(char *)(param_1 + 0x19) = *(char *)(param_1 + 0x19) + '\x01';
    }
  }
  return;
}



// ==== 801eedc8  FUN_801eedc8 ====

void FUN_801eedc8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801eede8  FUN_801eede8 ====

void FUN_801eede8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801eee28  zz_01eee28_ ====

void zz_01eee28_(void)

{
  short *psVar1;
  
  for (psVar1 = (short *)&DAT_80435b88; -1 < *psVar1; psVar1 = psVar1 + 2) {
    zz_01eee6c_(psVar1);
  }
  return;
}



// ==== 801eee6c  zz_01eee6c_ ====

void zz_01eee6c_(undefined2 *param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_008893c_(2,0x39,1,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 1;
    puVar1[0x11] = (char)*param_1;
    *(code **)(puVar1 + 0xc) = FUN_801eeef4;
    *(code **)(puVar1 + 0x10c) = FUN_801ef1c8;
    puVar1[0x13] = (char)param_1[1];
    *(undefined4 *)(puVar1 + 0x54) = DAT_803bb364;
  }
  return;
}



// ==== 801eeef4  FUN_801eeef4 ====

void FUN_801eeef4(int param_1)

{
  (*(code *)(&PTR_FUN_803a13b8)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801eef30  FUN_801eef30 ====

void FUN_801eef30(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  float *pfVar3;
  double dVar4;
  undefined8 uVar5;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0,1);
  fVar1 = FLOAT_8043c47c;
  *(float *)(param_9 + 100) = FLOAT_8043c478;
  fVar2 = FLOAT_8043c480;
  dVar4 = (double)FLOAT_8043c480;
  *(float *)(param_9 + 0x68) = fVar1;
  fVar1 = FLOAT_8043c484;
  *(float *)(param_9 + 0x6c) = fVar2;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  if (*(char *)(param_9 + 0x11) == '\0') {
    *(undefined1 *)(param_9 + 0x13) = *(undefined1 *)(DAT_80436398 + 0x1a);
  }
  pfVar3 = (float *)(int)*(char *)(param_9 + 0x13);
  uVar5 = zz_0006fb4_(dVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),(int)pfVar3,param_12,
                      param_13,param_14,param_15,param_16);
  if (*(char *)(param_9 + 0x11) == '\0') {
    zz_01ef0ac_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
                pfVar3,param_12,param_13,param_14,param_15,param_16);
  }
  zz_01ef000_(param_9);
  return;
}



// ==== 801ef000  zz_01ef000_ ====

void zz_01ef000_(int param_1)

{
  (**(code **)(&DAT_80435b90 + *(char *)(param_1 + 0x11) * 4))();
  if ((*(byte *)(DAT_80436398 + 0x17) & 1) != 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 801ef0ac  zz_01ef0ac_ ====

void zz_01ef0ac_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  int *piVar2;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined8 uVar3;
  
  uVar3 = zz_00086b8_((double)(float)((double)CONCAT44(0x43300000,
                                                       (int)*(char *)(DAT_80436398 + 0x1b) ^
                                                       0x80000000) - DOUBLE_8043c488),param_2,
                      param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x54),
                      *(int *)(param_9 + 0xe0),param_11,param_12,param_13,param_14,param_15,param_16
                     );
  uVar3 = zz_0007c30_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),extraout_r4,param_11,param_12,param_13,param_14,
                      param_15,param_16);
  iVar1 = *(int *)(*(int *)(param_9 + 0xe0) + 0xc);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = *(int *)(iVar1 + 0x10);
  }
  piVar2 = gnt4_HSD_JObjLoadJoint
                     (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      (int *)**(undefined4 **)(**(int **)(*(int *)(param_9 + 0x54) + 0x10) + 0x18),
                      extraout_r4_00,param_11,param_12,param_13,param_14,param_15,param_16);
  *(int **)(param_9 + 0x8c) = piVar2;
  if (piVar2 != (int *)0x0) {
    gnt4_HSD_JObjAddChild
              (uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar1,(int)piVar2,
               (char *)param_11,param_12,param_13,param_14,param_15,param_16);
    *(int *)(param_9 + 200) = iVar1;
  }
  return;
}



// ==== 801ef1a8  FUN_801ef1a8 ====

void FUN_801ef1a8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801ef1c8  FUN_801ef1c8 ====

/* WARNING: Removing unreachable block (ram,0x801ef254) */

void FUN_801ef1c8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  bool bVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  float afStack_38 [3];
  undefined4 local_2c;
  undefined4 local_1c;
  undefined4 local_c;
  
  uVar4 = zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13
                      ,param_14,param_15,param_16);
  iVar3 = *(int *)(param_9 + 0x8c);
  gnt4_PSMTXInverse_bl((float *)&DAT_803c1100,afStack_38);
  local_2c = *(undefined4 *)(param_9 + 0x20);
  local_1c = *(undefined4 *)(param_9 + 0x24);
  local_c = *(undefined4 *)(param_9 + 0x28);
  if (iVar3 == 0) {
    param_11 = &DAT_8043c498;
    gnt4___assert_bl(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,&DAT_8043c490,
                     0x495,&DAT_8043c498,param_12,param_13,param_14,param_15,param_16);
  }
  uVar4 = gnt4_PSMTXCopy_bl(afStack_38,(float *)(iVar3 + 0x44));
  *(uint *)(iVar3 + 0x14) = *(uint *)(iVar3 + 0x14) | 0x3800000;
  if (iVar3 != 0) {
    uVar2 = *(uint *)(iVar3 + 0x14);
    bVar1 = false;
    if (((uVar2 & 0x800000) == 0) && ((uVar2 & 0x40) != 0)) {
      bVar1 = true;
    }
    if (!bVar1) {
      gnt4_HSD_JObjSetMtxDirtySub_bl
                (uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,uVar2,param_11,
                 param_12,param_13,param_14,param_15,param_16);
    }
  }
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x47);
  return;
}



// ==== 801ef2b4  zz_01ef2b4_ ====

void zz_01ef2b4_(int param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,1);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x60;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 0;
    *(code **)(puVar1 + 0xc) = FUN_801ef3c4;
    *(code **)(puVar1 + 0x10c) = FUN_801ef6e4;
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
    puVar1[0x89] = param_3;
  }
  return;
}



// ==== 801ef3c4  FUN_801ef3c4 ====

void FUN_801ef3c4(int param_1)

{
  (*(code *)(&PTR_FUN_803a1480)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801ef400  FUN_801ef400 ====

void FUN_801ef400(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  float fVar2;
  uint uVar3;
  undefined4 uVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar5;
  int iVar6;
  double dVar7;
  undefined8 uVar8;
  double dVar9;
  
  dVar7 = DOUBLE_8043c4a8;
  fVar2 = FLOAT_8043c4a0;
  iVar6 = *(int *)(param_9 + 0x90);
  psVar5 = (short *)(&PTR_DAT_803a1460)[*(char *)(param_9 + 0x11)];
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(float *)(param_9 + 0xd4) = fVar2;
  *(float *)(param_9 + 0xd8) =
       (float)((double)CONCAT44(0x43300000,(int)psVar5[1] ^ 0x80000000) - dVar7);
  *(undefined1 *)(param_9 + 0x12) = 1;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  uVar3 = zz_00055fc_();
  *(short *)(param_9 + 0x72) = (short)(uVar3 << 8);
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar6 + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4),(float *)&DAT_803a1490,
             (float *)(param_9 + 0x20));
  dVar9 = (double)FLOAT_8043c4a4;
  *(float *)(param_9 + 0xb4) =
       (float)(dVar9 * (double)(*(float *)(iVar6 + 0xb4) * *(float *)(iVar6 + 0x7fc)));
  dVar7 = FUN_8003d6e4((double)*(float *)(iVar6 + 0x670),iVar6,(float *)(param_9 + 0x20));
  *(float *)(param_9 + 0x24) = (float)dVar7;
  uVar4 = 0x1e;
  uVar1 = *(undefined4 *)(param_9 + 0xb4);
  *(undefined4 *)(param_9 + 0x15c) = uVar1;
  *(undefined4 *)(param_9 + 0x158) = uVar1;
  *(undefined4 *)(param_9 + 0x154) = uVar1;
  *(undefined1 *)(param_9 + 0x84) = 0x1e;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,0,1);
  zz_008ac80_(param_9,(int)*(char *)(psVar5 + 2));
  zz_0018f88_((int *)(param_9 + 0x144),*(int *)(psVar5 + 4),(float *)(param_9 + 0x58));
  *(float *)(param_9 + 0x58) = *(float *)(param_9 + 0x58) * *(float *)(param_9 + 0x154);
  *(float *)(param_9 + 0x5c) = *(float *)(param_9 + 0x5c) * *(float *)(param_9 + 0x158);
  *(float *)(param_9 + 0x60) = *(float *)(param_9 + 0x60) * *(float *)(param_9 + 0x15c);
  uVar8 = zz_0019338_((int *)(param_9 + 0x14c),*(int *)(psVar5 + 6),(float *)(param_9 + 0x160));
  zz_0006fb4_(uVar8,dVar9,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
              *(int *)(param_9 + 0xe0),(int)*psVar5,uVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)*(float *)(param_9 + 0x160),*(int *)(param_9 + 0xe0));
  *(undefined1 *)(param_9 + 0x82) = 1;
  return;
}



// ==== 801ef5c0  FUN_801ef5c0 ====

void FUN_801ef5c0(int param_1)

{
  *(float *)(param_1 + 0xd4) =
       *(float *)(param_1 + 0xd4) + *(float *)(*(int *)(param_1 + 0x90) + 0x768);
  *(undefined2 *)(param_1 + 0x272) = 0xffff;
  zz_0019178_((double)*(float *)(param_1 + 0xd4),(int *)(param_1 + 0x144),(float *)(param_1 + 0x58))
  ;
  *(float *)(param_1 + 0x58) = *(float *)(param_1 + 0x58) * *(float *)(param_1 + 0x154);
  *(float *)(param_1 + 0x5c) = *(float *)(param_1 + 0x5c) * *(float *)(param_1 + 0x158);
  *(float *)(param_1 + 0x60) = *(float *)(param_1 + 0x60) * *(float *)(param_1 + 0x15c);
  zz_0019450_((double)*(float *)(param_1 + 0xd4),(int *)(param_1 + 0x14c),(float *)(param_1 + 0x160)
             );
  zz_0007cac_((double)*(float *)(param_1 + 0x160),*(int *)(param_1 + 0xe0));
  if (*(float *)(param_1 + 0xd8) <= *(float *)(param_1 + 0xd4)) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801ef688  FUN_801ef688 ====

void FUN_801ef688(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801ef6c4  FUN_801ef6c4 ====

void FUN_801ef6c4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801ef6e4  FUN_801ef6e4 ====

void FUN_801ef6e4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 801ef724  zz_01ef724_ ====

void zz_01ef724_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,8);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_801ef81c;
    *(code **)(puVar1 + 0x10c) = FUN_801f007c;
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



// ==== 801ef81c  FUN_801ef81c ====

void FUN_801ef81c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803a14fc)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801ef870  FUN_801ef870 ====

void FUN_801ef870(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  float fVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 extraout_r4_01;
  undefined4 extraout_r4_02;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  undefined8 uVar10;
  double local_28;
  double local_20;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar9 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar10 = zz_0089100_(param_9,(int)*(char *)(iVar9 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  *(undefined1 *)(param_9 + 0x89) = 1;
  fVar2 = FLOAT_8043c4b0;
  uVar1 = DAT_803a14d4;
  *(undefined4 *)(param_9 + 100) = DAT_803a14d0;
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = DAT_803a14d8;
  *(undefined4 *)(param_9 + 0x70) = DAT_803a14f4;
  *(undefined2 *)(param_9 + 0x74) = DAT_803a14f8;
  *(float *)(param_9 + 0xb4) = fVar2;
  *(float *)(param_9 + 0xb8) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x60) = fVar2;
  iVar3 = zz_0006f98_(iVar9);
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe0),
                       *(int *)(&DAT_80435b98 + *(char *)(param_9 + 0x13) * 4),iVar3 + 0xc28,in_r7,
                       in_r8,in_r9,in_r10);
  iVar8 = iVar3 + 0xc28;
  iVar5 = *(int *)(&DAT_80435b98 + *(char *)(param_9 + 0x13) * 4);
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe4),iVar5,iVar8,in_r7,in_r8,
                       in_r9,in_r10);
  zz_0007c54_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xe4),extraout_r4,iVar5,iVar8,in_r7,in_r8,in_r9,in_r10);
  uVar10 = zz_0007cac_((double)FLOAT_8043c4b4,*(int *)(param_9 + 0xe4));
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xe8),
                       *(int *)(&DAT_80435b98 + *(char *)(param_9 + 0x13) * 4),iVar3 + 0xc28,in_r7,
                       in_r8,in_r9,in_r10);
  iVar8 = iVar3 + 0xc28;
  iVar5 = *(int *)(&DAT_80435b98 + *(char *)(param_9 + 0x13) * 4);
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xec),iVar5,iVar8,in_r7,in_r8,
                       in_r9,in_r10);
  zz_0007c54_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xec),extraout_r4_00,iVar5,iVar8,in_r7,in_r8,in_r9,in_r10);
  uVar10 = zz_0007cac_((double)FLOAT_8043c4b4,*(int *)(param_9 + 0xec));
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xf0),
                       *(int *)(&DAT_80435b98 + *(char *)(param_9 + 0x13) * 4),iVar3 + 0xc28,in_r7,
                       in_r8,in_r9,in_r10);
  iVar8 = iVar3 + 0xc28;
  iVar5 = *(int *)(&DAT_80435b98 + *(char *)(param_9 + 0x13) * 4);
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xf4),iVar5,iVar8,in_r7,in_r8,
                       in_r9,in_r10);
  zz_0007c54_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xf4),extraout_r4_01,iVar5,iVar8,in_r7,in_r8,in_r9,in_r10);
  uVar10 = zz_0007cac_((double)FLOAT_8043c4b4,*(int *)(param_9 + 0xf4));
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xf8),
                       *(int *)(&DAT_80435b98 + *(char *)(param_9 + 0x13) * 4),iVar3 + 0xc28,in_r7,
                       in_r8,in_r9,in_r10);
  iVar8 = iVar3 + 0xc28;
  iVar5 = *(int *)(&DAT_80435b98 + *(char *)(param_9 + 0x13) * 4);
  uVar10 = zz_0007030_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                       *(int *)(iVar3 + 0x600),*(int *)(param_9 + 0xfc),iVar5,iVar8,in_r7,in_r8,
                       in_r9,in_r10);
  zz_0007c54_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
              *(int *)(param_9 + 0xfc),extraout_r4_02,iVar5,iVar8,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043c4b4,*(int *)(param_9 + 0xfc));
  puVar6 = (undefined4 *)(param_9 + 0x144);
  iVar3 = 0;
  puVar4 = (undefined4 *)&DAT_803a14dc;
  iVar5 = 4;
  puVar7 = puVar6;
  do {
    *puVar7 = *puVar4;
    *(undefined2 *)(puVar7 + 1) = *(undefined2 *)(puVar4 + 1);
    *(undefined2 *)(puVar6 + 6) = 0;
    if (*(char *)(iVar9 + 0x493) == '\x02') {
      *(undefined2 *)(puVar6 + 8) = 0x600;
    }
    else {
      *(undefined2 *)(puVar6 + 8) = 0xd00;
    }
    *(undefined2 *)(puVar6 + 10) = *(undefined2 *)puVar4;
    if (iVar3 == 0) {
      *(undefined2 *)((int)puVar7 + 2) = 0x1000;
      *(undefined1 *)(param_9 + 0x174) = 0;
    }
    else if (iVar3 == 1) {
      *(undefined2 *)((int)puVar7 + 2) = 0x9000;
      local_28 = (double)(CONCAT44(0x43300000,(int)*(short *)(puVar6 + 8)) ^ 0x80000000);
      *(short *)(puVar6 + 6) =
           (short)(int)(FLOAT_8043c4b8 *
                       (FLOAT_8043c4bc / (FLOAT_8043c4c0 / (float)(local_28 - DOUBLE_8043c4c8))));
      *(undefined2 *)(puVar6 + 10) = 0;
      *(undefined1 *)(param_9 + 0x175) = 1;
    }
    else if (iVar3 == 2) {
      *(undefined2 *)((int)puVar7 + 2) = 0x7000;
      local_20 = (double)(CONCAT44(0x43300000,(int)*(short *)(puVar6 + 8)) ^ 0x80000000);
      *(short *)(puVar6 + 6) =
           -(short)(int)(FLOAT_8043c4b8 *
                        (FLOAT_8043c4bc / (FLOAT_8043c4c0 / (float)(local_20 - DOUBLE_8043c4c8))));
      *(undefined2 *)(puVar6 + 10) = 0;
      *(short *)(puVar6 + 8) = -*(short *)(puVar6 + 8);
      *(undefined1 *)(param_9 + 0x176) = 1;
    }
    else if (iVar3 == 3) {
      *(undefined2 *)((int)puVar7 + 2) = 0xf000;
      *(short *)(puVar6 + 8) = -*(short *)(puVar6 + 8);
      *(undefined1 *)(param_9 + 0x177) = 0;
    }
    puVar4 = (undefined4 *)((int)puVar4 + 6);
    puVar7 = (undefined4 *)((int)puVar7 + 6);
    puVar6 = (undefined4 *)((int)puVar6 + 2);
    iVar3 = iVar3 + 1;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  *(undefined1 *)(param_9 + 0x82) = 1;
  zz_01efc6c_(param_9);
  return;
}



// ==== 801efc6c  zz_01efc6c_ ====

void zz_01efc6c_(int param_1)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  short *psVar4;
  short *psVar5;
  int iVar6;
  double dVar7;
  double local_48;
  double local_38;
  undefined8 local_30;
  double local_28;
  
  iVar2 = *(int *)(param_1 + 0x90);
  if (((*(uint *)(iVar2 + 0x5e0) & 0x50) != 0) || (*(char *)(iVar2 + 0x493) == '\x02')) {
    psVar3 = (short *)(param_1 + 0x144);
    psVar4 = &DAT_803a14dc;
    iVar1 = 0;
    psVar5 = psVar3;
    do {
      dVar7 = DOUBLE_8043c4c8;
      if ((iVar1 == 0) || (iVar1 == 2)) {
        iVar6 = param_1 + iVar1;
        local_48 = (double)(CONCAT44(0x43300000,(int)psVar3[0x10]) ^ 0x80000000);
        psVar5[1] = (short)(int)((float)(local_48 - DOUBLE_8043c4c8) * *(float *)(iVar2 + 0x5f4) +
                                (float)((double)CONCAT44(0x43300000,(int)psVar5[1] ^ 0x80000000) -
                                       DOUBLE_8043c4c8));
        if (*(char *)(iVar6 + 0x174) == '\x01') {
          local_38 = (double)(CONCAT44(0x43300000,(int)psVar3[0xc]) ^ 0x80000000);
          psVar3[0x14] = (short)(int)((float)(local_38 - dVar7) * *(float *)(iVar2 + 0x5f4) +
                                     (float)((double)CONCAT44(0x43300000,
                                                              (int)psVar3[0x14] ^ 0x80000000) -
                                            dVar7));
          dVar7 = zz_0045204_(psVar3[0x14]);
          local_30 = (double)(CONCAT44(0x43300000,(int)*psVar4) ^ 0x80000000);
          *psVar5 = (short)(int)((double)FLOAT_8043c4d0 * dVar7 +
                                (double)(float)(local_30 - DOUBLE_8043c4c8));
          if (*psVar4 < *psVar5) {
            *psVar5 = *psVar4;
          }
        }
        if (psVar5[1] < 0x7001) {
          if (psVar5[1] < 0x1000) {
            psVar5[1] = 0x1000;
            psVar3[0x10] = -psVar3[0x10];
            *psVar5 = *psVar4;
            *(undefined1 *)(iVar6 + 0x174) = 0;
          }
        }
        else {
          psVar5[1] = 0x7000;
          local_28 = (double)(CONCAT44(0x43300000,(int)psVar3[0x10]) ^ 0x80000000);
          psVar3[0xc] = -(short)(int)(FLOAT_8043c4b8 *
                                     (FLOAT_8043c4bc /
                                     (FLOAT_8043c4c0 / (float)(local_28 - DOUBLE_8043c4c8))));
          psVar3[0x14] = 0;
          psVar3[0x10] = -psVar3[0x10];
          *(undefined1 *)(iVar6 + 0x174) = 1;
        }
      }
      else if ((iVar1 == 1) || (iVar1 == 3)) {
        iVar6 = param_1 + iVar1;
        local_28 = (double)(CONCAT44(0x43300000,(int)psVar3[0x10]) ^ 0x80000000);
        local_30 = (double)CONCAT44(0x43300000,(int)psVar5[1] ^ 0x80000000);
        psVar5[1] = (short)(int)((float)(local_28 - DOUBLE_8043c4c8) * *(float *)(iVar2 + 0x5f4) +
                                (float)(local_30 - DOUBLE_8043c4c8));
        if (*(char *)(iVar6 + 0x174) == '\x01') {
          local_28 = (double)(CONCAT44(0x43300000,(int)psVar3[0xc]) ^ 0x80000000);
          local_30 = (double)CONCAT44(0x43300000,(int)psVar3[0x14] ^ 0x80000000);
          psVar3[0x14] = (short)(int)((float)(local_28 - dVar7) * *(float *)(iVar2 + 0x5f4) +
                                     (float)(local_30 - dVar7));
          dVar7 = zz_0045204_(psVar3[0x14]);
          *psVar5 = (short)(int)((double)FLOAT_8043c4d0 * dVar7 +
                                (double)(float)((double)CONCAT44(0x43300000,
                                                                 (int)*psVar4 ^ 0x80000000) -
                                               DOUBLE_8043c4c8));
          if (*psVar4 < *psVar5) {
            *psVar5 = *psVar4;
          }
        }
        if (psVar5[1] < -0x7000) {
          psVar5[1] = -0x7000;
          local_28 = (double)(CONCAT44(0x43300000,(int)psVar3[0x10]) ^ 0x80000000);
          psVar3[0xc] = (short)(int)(FLOAT_8043c4b8 *
                                    (FLOAT_8043c4bc /
                                    (FLOAT_8043c4c0 / (float)(local_28 - DOUBLE_8043c4c8))));
          psVar3[0x14] = 0;
          psVar3[0x10] = -psVar3[0x10];
          *(undefined1 *)(iVar6 + 0x174) = 1;
        }
        else if (-0x1000 < psVar5[1]) {
          psVar5[1] = -0x1000;
          psVar3[0x10] = -psVar3[0x10];
          *psVar5 = *psVar4;
          *(undefined1 *)(iVar6 + 0x174) = 0;
        }
      }
      iVar1 = iVar1 + 1;
      psVar5 = psVar5 + 3;
      psVar4 = psVar4 + 3;
      psVar3 = psVar3 + 1;
    } while (iVar1 < 4);
  }
  return;
}



// ==== 801f005c  FUN_801f005c ====

void FUN_801f005c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801f007c  FUN_801f007c ====

/* WARNING: Removing unreachable block (ram,0x801f01a8) */
/* WARNING: Removing unreachable block (ram,0x801f0120) */
/* WARNING: Removing unreachable block (ram,0x801f0144) */
/* WARNING: Removing unreachable block (ram,0x801f008c) */

void FUN_801f007c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  float *pfVar8;
  float *pfVar9;
  undefined8 uVar10;
  double dVar11;
  float afStack_128 [12];
  float afStack_f8 [49];
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar3 = 0;
    if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
      uVar4 = 0x44;
    }
    else {
      uVar4 = 1;
    }
  }
  else {
    iVar3 = 1;
    uVar4 = 0x44;
  }
  dVar11 = (double)FLOAT_8043c4d4;
  pfVar8 = (float *)&DAT_803a14a0;
  pfVar9 = afStack_f8;
  psVar7 = (short *)(param_9 + 0x144);
  iVar2 = 0;
  iVar6 = 0;
  do {
    gnt4_PSMTXCopy_bl((float *)(param_9 + 0x114),pfVar9);
    gnt4_PSMTXMultVec_bl(pfVar9,pfVar8,(float *)(param_9 + 0x20));
    pfVar9[3] = *(float *)(param_9 + 0x20);
    pfVar9[7] = *(float *)(param_9 + 0x24);
    pfVar9[0xb] = *(float *)(param_9 + 0x28);
    gnt4_PSMTXRotRad_bl((double)(float)(dVar11 * (double)((longlong)(double)psVar7[1] *
                                                         0x3ff0000000000000)),afStack_128,0x79);
    gnt4_PSMTXConcat_bl(pfVar9,afStack_128,pfVar9);
    gnt4_PSMTXRotRad_bl((double)(float)(dVar11 * (double)((longlong)(double)*psVar7 *
                                                         0x3ff0000000000000)),afStack_128,0x78);
    pfVar1 = pfVar9;
    uVar10 = gnt4_PSMTXConcat_bl(pfVar9,afStack_128,pfVar9);
    iVar5 = (iVar3 + iVar6) * 4 + 0xe0;
    zz_00076d0_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + iVar5),pfVar9,(undefined *)pfVar1,param_12,param_13,param_14,
                param_15,param_16);
    zz_00097b4_(*(int *)(param_9 + iVar5),uVar4);
    iVar2 = iVar2 + 1;
    pfVar8 = pfVar8 + 3;
    psVar7 = psVar7 + 3;
    iVar6 = iVar6 + 2;
    pfVar9 = pfVar9 + 0xc;
  } while (iVar2 < 4);
  return;
}



// ==== 801f01c4  FUN_801f01c4 ====

void FUN_801f01c4(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x13] = param_2;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_801f02bc;
    *(code **)(puVar1 + 0x10c) = FUN_801f0900;
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



// ==== 801f02bc  FUN_801f02bc ====

void FUN_801f02bc(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803a1528)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801f0310  FUN_801f0310 ====

void FUN_801f0310(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  undefined4 uVar1;
  undefined4 extraout_r4;
  int iVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
  uVar5 = (uint)*(byte *)(param_9 + 0x18);
  *(byte *)(param_9 + 0x18) = *(byte *)(param_9 + 0x18) + 1;
  *(undefined1 *)(param_9 + 0x19) = 0;
  *(undefined1 *)(param_9 + 0x1a) = 0;
  iVar6 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar7 = zz_0089100_(param_9,(int)*(char *)(iVar6 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x43;
  *(undefined1 *)(param_9 + 0x89) = 1;
  iVar2 = *(char *)(param_9 + 0x13) * 0xc;
  uVar1 = *(undefined4 *)(&DAT_803a1514 + iVar2);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_803a1510 + iVar2);
  *(undefined4 *)(param_9 + 0x68) = uVar1;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803a1518 + iVar2);
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  iVar2 = zz_0006f98_(iVar6);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar2 + 0x600),*(int *)(param_9 + 0xe0),
                      *(int *)(&DAT_80435ba0 + *(char *)(param_9 + 0x13) * 4),iVar2 + 0xc28,uVar5,
                      in_r8,in_r9,in_r10);
  iVar4 = iVar2 + 0xc28;
  iVar3 = *(int *)(&DAT_80435ba0 + *(char *)(param_9 + 0x13) * 4);
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar2 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,uVar5,in_r8,in_r9
                      ,in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,uVar5,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043c4d8,*(int *)(param_9 + 0xe4));
  *(undefined1 *)(param_9 + 0x82) = 1;
  *(undefined4 *)(param_9 + 0x144) = *(undefined4 *)(iVar6 + 0x8e0);
  *(undefined4 *)(param_9 + 0x148) = *(undefined4 *)(iVar6 + 0x8f0);
  *(undefined4 *)(param_9 + 0x14c) = *(undefined4 *)(iVar6 + 0x900);
  *(undefined4 *)(param_9 + 0x150) = *(undefined4 *)(param_9 + 0x144);
  *(undefined4 *)(param_9 + 0x154) = *(undefined4 *)(param_9 + 0x148);
  *(undefined4 *)(param_9 + 0x158) = *(undefined4 *)(param_9 + 0x14c);
  FUN_801f047c(param_9);
  return;
}



// ==== 801f047c  FUN_801f047c ====

void FUN_801f047c(int param_1)

{
  char cVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  bool bVar5;
  double dVar6;
  float afStack_38 [3];
  float local_2c;
  float local_28;
  float local_24;
  double local_20;
  double local_18;
  
  iVar4 = *(int *)(param_1 + 0x90);
  *(undefined4 *)(param_1 + 0x144) = *(undefined4 *)(iVar4 + 0x8e0);
  *(undefined4 *)(param_1 + 0x148) = *(undefined4 *)(iVar4 + 0x8f0);
  *(undefined4 *)(param_1 + 0x14c) = *(undefined4 *)(iVar4 + 0x900);
  cVar1 = *(char *)(param_1 + 0x19);
  if (cVar1 != '\x01') {
    if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        uVar3 = *(uint *)(iVar4 + 0x5e0);
        if ((uVar3 & 0x2000000) == 0) {
          if (*(char *)(iVar4 + 0x6cb) == '\0') {
            if (((*(char *)(iVar4 + 0x1db) != '\0') && ((uVar3 & 0x10) == 0)) &&
               ((uVar3 & 0x20) == 0)) {
              *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x144);
              *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x148);
              *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x14c);
              return;
            }
            if ((*(char *)(iVar4 + 0x1dd) == '\0') || (*(char *)(iVar4 + 0x1db) != '\0')) {
              gnt4_PSVECSubtract_bl((float *)(param_1 + 0x144),(float *)(param_1 + 0x150),&local_2c)
              ;
            }
            else {
              dVar6 = gnt4_PSVECSquareMag_bl((float *)(iVar4 + 0x1cc));
              if (dVar6 <= (double)FLOAT_8043c4dc) {
                local_2c = FLOAT_8043c4dc;
                local_28 = FLOAT_8043c4e4;
                local_24 = FLOAT_8043c4dc;
              }
              else {
                gnt4_PSQUATScale_bl((double)FLOAT_8043c4e0,(float *)(iVar4 + 0x1cc),&local_2c);
              }
              gnt4_PSVECSubtract_bl
                        ((float *)(param_1 + 0x144),(float *)(param_1 + 0x150),afStack_38);
              gnt4_PSVECAdd_bl(&local_2c,afStack_38,&local_2c);
            }
            dVar6 = gnt4_PSVECSquareMag_bl(&local_2c);
            if ((double)FLOAT_8043c4dc < dVar6) {
              zz_00451b8_((float *)(iVar4 + 0x8d4),&local_2c,&local_2c);
              if ((*(uint *)(iVar4 + 0x5e0) & 0x40) != 0) {
                if (local_24 < FLOAT_8043c4dc) {
                  local_24 = local_24 - FLOAT_8043c4e8;
                }
                else {
                  local_24 = local_24 + FLOAT_8043c4e8;
                }
              }
              local_24 = FLOAT_8043c4ec * local_24;
              fVar2 = FLOAT_8043c4f0;
              if ((local_24 < FLOAT_8043c4f0) && (fVar2 = local_24, local_24 <= FLOAT_8043c4f4)) {
                fVar2 = FLOAT_8043c4f4;
              }
              if ((*(uint *)(iVar4 + 0x5e0) & 0x40) != 0) {
                fVar2 = FLOAT_8043c4f8;
              }
              if ((*(uint *)(iVar4 + 0x5e0) & 0x20000000) == 0) {
                local_20 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x70)) ^
                                   0x80000000);
                *(short *)(param_1 + 0x70) =
                     (short)(int)(FLOAT_8043c4fc * fVar2 + (float)(local_20 - DOUBLE_8043c508));
              }
            }
          }
          else {
            *(undefined1 *)(param_1 + 0x19) = 2;
            *(undefined1 *)(param_1 + 0x1a) = 0;
          }
        }
        else {
          *(undefined1 *)(param_1 + 0x19) = 1;
          *(undefined1 *)(param_1 + 0x1a) = 0;
        }
      }
    }
    else if (cVar1 < '\x03') {
      if (*(char *)(iVar4 + 0x6cb) == '\0') {
        *(undefined1 *)(param_1 + 0x19) = 0;
      }
      else {
        cVar1 = *(char *)(param_1 + 0x1a);
        if (cVar1 == '\x02') {
          *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
          if (*(short *)(param_1 + 0x1c) < 1) {
            *(undefined1 *)(param_1 + 0x1a) = 3;
          }
          if ((*(uint *)(iVar4 + 0x5e0) & 0x20000000) == 0) {
            local_18 = (double)(CONCAT44(0x43300000,(int)*(short *)(param_1 + 0x70)) ^ 0x80000000);
            *(short *)(param_1 + 0x70) =
                 (short)(int)((float)(local_18 - DOUBLE_8043c508) + FLOAT_8043c504);
          }
        }
        else if (cVar1 < '\x02') {
          if (cVar1 == '\0') {
            if ((*(uint *)(iVar4 + 0x5e0) & 0x40) == 0) {
              *(undefined1 *)(param_1 + 0x1a) = 1;
              *(undefined2 *)(param_1 + 0x1c) = 0x1e;
            }
          }
          else if ((-1 < cVar1) &&
                  (*(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1,
                  *(short *)(param_1 + 0x1c) < 1)) {
            *(undefined1 *)(param_1 + 0x1a) = 2;
            *(undefined2 *)(param_1 + 0x1c) = 0x30;
          }
        }
      }
    }
    goto LAB_801f08a0;
  }
  uVar3 = *(uint *)(iVar4 + 0x5e0);
  if ((uVar3 & 0x1000000) == 0) {
    *(undefined1 *)(param_1 + 0x19) = 0;
    goto LAB_801f08a0;
  }
  cVar1 = *(char *)(param_1 + 0x1a);
  if (cVar1 == '\x02') {
LAB_801f0750:
    fVar2 = *(float *)(param_1 + 0xd4) - *(float *)(iVar4 + 0x768);
    bVar5 = FLOAT_8043c4dc < fVar2;
    *(float *)(param_1 + 0xd4) = fVar2;
    if (bVar5) {
      if ((*(uint *)(iVar4 + 0x5e0) & 0x20000000) == 0) {
        *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0x1b00;
      }
      goto LAB_801f08a0;
    }
    *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
  }
  else {
    if (cVar1 < '\x02') {
      if (cVar1 == '\0') {
        if ((uVar3 & 0x2000000) != 0) {
          if ((uVar3 & 0x20000000) == 0) {
            *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0x1b00;
          }
          goto LAB_801f08a0;
        }
        *(undefined1 *)(param_1 + 0x1a) = 1;
      }
      else if (cVar1 < '\0') goto LAB_801f08a0;
      if ((*(uint *)(iVar4 + 0x5e0) & 0x4000000) != 0) {
        *(float *)(param_1 + 0xd4) = FLOAT_8043c500;
      }
      *(char *)(param_1 + 0x1a) = *(char *)(param_1 + 0x1a) + '\x01';
      goto LAB_801f0750;
    }
    if ('\x03' < cVar1) goto LAB_801f08a0;
  }
  if ((*(uint *)(iVar4 + 0x5e0) & 0x20000000) == 0) {
    *(short *)(param_1 + 0x70) = *(short *)(param_1 + 0x70) + 0x1200;
  }
LAB_801f08a0:
  *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x144);
  *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x148);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x14c);
  return;
}



// ==== 801f08e0  FUN_801f08e0 ====

void FUN_801f08e0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801f0900  FUN_801f0900 ====

void FUN_801f0900(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar1 = 0;
    if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
      uVar2 = 0x44;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    iVar1 = 1;
    uVar2 = 0x44;
  }
  iVar1 = param_9 + iVar1 * 4;
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar1 + 0xe0)
              ,(float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(iVar1 + 0xe0),uVar2);
  return;
}



// ==== 801f0984  FUN_801f0984 ====

void FUN_801f0984(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_801f0a6c;
    *(code **)(puVar1 + 0x10c) = FUN_801f0be4;
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



// ==== 801f0a6c  FUN_801f0a6c ====

void FUN_801f0a6c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_803a1538)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801f0ac0  FUN_801f0ac0 ====

void FUN_801f0ac0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 extraout_r4;
  undefined4 uVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  double dVar6;
  undefined8 uVar7;
  
  *(char *)(param_9 + 0x18) = *(char *)(param_9 + 0x18) + '\x01';
  iVar5 = *(int *)(param_9 + 0x90);
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_9,(int)*(char *)(iVar5 + 0x3e4) + 0x10,1);
  *(undefined1 *)(param_9 + 0x84) = 0x41;
  fVar1 = FLOAT_8043c510;
  *(undefined1 *)(param_9 + 0x89) = 2;
  fVar2 = FLOAT_8043c514;
  dVar6 = (double)FLOAT_8043c514;
  *(float *)(param_9 + 100) = fVar1;
  fVar1 = FLOAT_8043c518;
  *(float *)(param_9 + 0x68) = fVar2;
  *(float *)(param_9 + 0x6c) = fVar1;
  *(undefined2 *)(param_9 + 0x74) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  iVar5 = zz_0006f98_(iVar5);
  uVar7 = zz_0007030_(dVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe0),3,iVar5 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar4 = iVar5 + 0xc28;
  uVar3 = 3;
  uVar7 = zz_0007030_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar5 + 0x600),*(int *)(param_9 + 0xe4),3,iVar4,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043c51c,*(int *)(param_9 + 0xe4));
  *(undefined1 *)(param_9 + 0x82) = 1;
  FUN_801f0bb0();
  return;
}



// ==== 801f0bb0  FUN_801f0bb0 ====

void FUN_801f0bb0(void)

{
  return;
}



// ==== 801f0bc4  FUN_801f0bc4 ====

void FUN_801f0bc4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801f0be4  FUN_801f0be4 ====

void FUN_801f0be4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  uint uVar2;
  
  if (*(char *)(*(int *)(param_9 + 0x90) + 0xae) == '\0') {
    iVar1 = 0;
    if (*(char *)(*(int *)(param_9 + 0x90) + 0x3ec) == '\x04') {
      uVar2 = 0x44;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    iVar1 = 1;
    uVar2 = 0x44;
  }
  iVar1 = param_9 + iVar1 * 4;
  zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar1 + 0xe0)
              ,(float *)(param_9 + 0x114),param_11,param_12,param_13,param_14,param_15,param_16);
  zz_00097b4_(*(int *)(iVar1 + 0xe0),uVar2);
  return;
}



// ==== 801f0d58  FUN_801f0d58 ====

void FUN_801f0d58(int param_1)

{
  zz_00c74ec_(param_1,0x44);
  FUN_801f01c4(param_1,0);
  FUN_801f01c4(param_1,1);
  FUN_801f0984(param_1);
  *(undefined2 *)(param_1 + 0x144) = 0;
  return;
}



// ==== 801f0dbc  FUN_801f0dbc ====

void FUN_801f0dbc(int param_1)

{
  short sVar1;
  
  zz_006d520_(param_1,(float *)&DAT_803a1588);
  if ((*(uint *)(param_1 + 0x5e0) & 0x10) != 0) {
    zz_00f0104_(param_1,0x1e,6);
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x1000000) == 0) {
    if (*(char *)(param_1 + 0x146) == '\0') {
      sVar1 = *(short *)(param_1 + 0x144);
      if (sVar1 < 0) {
        *(short *)(param_1 + 0x144) = sVar1 + 0xc0;
        if (-1 < *(short *)(param_1 + 0x144)) {
          *(undefined2 *)(param_1 + 0x144) = 0;
        }
      }
      else if ((0 < sVar1) &&
              (*(short *)(param_1 + 0x144) = sVar1 + -0xc0, *(short *)(param_1 + 0x144) < 1)) {
        *(undefined2 *)(param_1 + 0x144) = 0;
      }
    }
  }
  *(undefined2 *)(param_1 + 0x18e0) = *(undefined2 *)(param_1 + 0x144);
  return;
}



// ==== 801f0e8c  FUN_801f0e8c ====

void FUN_801f0e8c(int param_1)

{
  (*(code *)(&PTR_FUN_80435ba8)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 801f0ec4  FUN_801f0ec4 ====

void FUN_801f0ec4(int param_1)

{
  (*(code *)(&PTR_FUN_80435bac)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801f0efc  FUN_801f0efc ====

void FUN_801f0efc(int param_1)

{
  (*(code *)(&PTR_LAB_803a15b8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801f0f50  FUN_801f0f50 ====

void FUN_801f0f50(int param_1)

{
  short sVar1;
  int iVar2;
  short sVar3;
  byte bVar4;
  
  *(undefined1 *)(param_1 + 0x146) = 1;
  zz_006660c_(param_1);
  iVar2 = FUN_800669d0(param_1,0xc1);
  bVar4 = iVar2 != 0;
  iVar2 = zz_00853ec_(param_1,0x17);
  sVar3 = (short)iVar2;
  if (sVar3 < -0x3800) {
    sVar3 = -0x3800;
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
  if (*(short *)(param_1 + 0x144) == sVar3) {
    bVar4 = bVar4 | 2;
  }
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  if ((bVar4 == 3) || (*(float *)(param_1 + 0x558) <= FLOAT_8043c524)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x541) = 0;
  }
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 1;
    iVar2 = zz_00677b0_(param_1);
    if (iVar2 != 0) {
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffffbf;
      *(undefined1 *)(param_1 + 0x709) = 0;
    }
  }
  return;
}



// ==== 801f10b4  FUN_801f10b4 ====

void FUN_801f10b4(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  *(undefined1 *)(param_1 + 0x146) = 0;
  iVar4 = zz_006dbe0_(param_1,0,1,1);
  if (iVar4 == 0) {
    *(undefined1 *)(param_1 + 0x709) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  else {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    zz_0084600_(param_1,0x17);
    fVar2 = FLOAT_8043c52c;
    fVar1 = FLOAT_8043c528;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) | 0x40;
    fVar3 = FLOAT_8043c530;
    *(short *)(param_1 + 0x5ae) = *(short *)(param_1 + 0x72) + -0x8000;
    *(float *)(param_1 + 0x44) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x48) = fVar1;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
    *(byte *)(param_1 + 0x709) = *(byte *)(param_1 + 0x709) | 1;
    *(float *)(param_1 + 0x558) = fVar3;
  }
  return;
}



// ==== 801f1188  FUN_801f1188 ====

void FUN_801f1188(int param_1)

{
  float fVar1;
  int iVar2;
  
  zz_0067458_((double)FLOAT_8043c534,param_1,*(short *)(param_1 + 0x5ae));
  *(float *)(param_1 + 0x558) = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  iVar2 = zz_00677b0_(param_1);
  if (iVar2 == 0) {
    if (FLOAT_8043c524 < *(float *)(param_1 + 0x558)) {
      *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) + -0x1000;
    }
    else {
      *(undefined1 *)(param_1 + 0x709) = 0;
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x709) = 0;
    zz_00b2190_(param_1,2);
    zz_00f07e8_(param_1);
    fVar1 = FLOAT_8043c524;
    *(undefined2 *)(param_1 + 0x18da) = 0;
    *(float *)(param_1 + 0x50) = fVar1;
    *(float *)(param_1 + 0x48) = fVar1;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    *(undefined2 *)(param_1 + 0x80) = 0;
    *(undefined2 *)(param_1 + 0x7e) = 0;
    *(undefined2 *)(param_1 + 0x7c) = 0;
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a474_(param_1);
  }
  return;
}



// ==== 801f1280  zz_01f1280_ ====

void zz_01f1280_(void)

{
  *(undefined2 *)(PTR_DAT_80435a30 + 6) = 0;
  (*(code *)(&PTR_FUN_803a17e0)[*(short *)(PTR_DAT_80435a30 + 2)])();
  return;
}



// ==== 801f12c8  zz_01f12c8_ ====

void zz_01f12c8_(void)

{
  *(undefined2 *)(PTR_DAT_80435a30 + 6) = 1;
  (*(code *)(&PTR_FUN_803a17ec)[*(short *)(PTR_DAT_80435a30 + 2)])();
  return;
}



// ==== 801f1310  FUN_801f1310 ====

undefined4 FUN_801f1310(void)

{
  (*(code *)(&PTR_FUN_80435bb0)[*(short *)(PTR_DAT_80435a30 + 4)])();
  return 0;
}



// ==== 801f134c  FUN_801f134c ====

void FUN_801f134c(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  undefined8 uVar1;
  
  *(short *)(PTR_DAT_80435a30 + 4) = *(short *)(PTR_DAT_80435a30 + 4) + 1;
  uVar1 = zz_0197854_(0);
  zz_0088398_(DAT_80436238 + 0xfe800,0x100000,4);
  zz_00449e8_(uVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,1);
  return;
}



// ==== 801f13a0  FUN_801f13a0 ====

void FUN_801f13a0(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined *puVar4;
  undefined *puVar5;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  
  iVar1 = zz_000a3c4_();
  puVar5 = PTR_DAT_80435a30;
  if (iVar1 == 0) {
    uVar2 = 0;
    uVar3 = 0;
    *(short *)(PTR_DAT_80435a30 + 2) = *(short *)(PTR_DAT_80435a30 + 2) + 1;
    puVar4 = PTR_DAT_80435a30;
    *(undefined2 *)(PTR_DAT_80435a30 + 4) = 0;
    zz_002a5f4_(0,0,0,0);
    uVar6 = set_global_menu_mode(6);
    zz_007fd6c_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,zz_01ba78c_,0,uVar2,
                uVar3,puVar4,puVar5,in_r9,in_r10);
    zz_01f16bc_();
    if (*(short *)(PTR_DAT_80435a30 + 6) == 0) {
      zz_0027aac_(0xe0e0e000,0x3c,0);
    }
  }
  return;
}



// ==== 801f143c  FUN_801f143c ====

undefined4 FUN_801f143c(void)

{
  (*(code *)(&PTR_FUN_80435bb8)[*(short *)(PTR_DAT_80435a30 + 4)])();
  zz_01f16f0_();
  zz_01f1778_();
  return 0;
}



// ==== 801f1480  FUN_801f1480 ====

void FUN_801f1480(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar2;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    *(short *)(PTR_DAT_80435a30 + 4) = *(short *)(PTR_DAT_80435a30 + 4) + 1;
    uVar2 = zz_0027c1c_();
    zz_01b1960_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,
                (int)(char)PTR_DAT_80435a30[0x46],*(undefined4 *)(PTR_DAT_80435a30 + 0x2c),
                *(undefined4 *)(PTR_DAT_80435a30 + 0x28),*(undefined4 *)(PTR_DAT_80435a30 + 0x24),
                in_r8,in_r9,in_r10);
  }
  return;
}



// ==== 801f14dc  FUN_801f14dc ====

void FUN_801f14dc(void)

{
  int iVar1;
  
  iVar1 = zz_01b1a40_();
  if (iVar1 == 0) {
    *(short *)(PTR_DAT_80435a30 + 2) = *(short *)(PTR_DAT_80435a30 + 2) + 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 4) = 0;
  }
  else if ((iVar1 < 0) && (-2 < iVar1)) {
    *(short *)(PTR_DAT_80435a30 + 2) = *(short *)(PTR_DAT_80435a30 + 2) + 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 4) = 0;
  }
  return;
}



// ==== 801f1550  FUN_801f1550 ====

undefined4 FUN_801f1550(void)

{
  (*(code *)(&PTR_FUN_80435bc0)[*(short *)(PTR_DAT_80435a30 + 4)])();
  zz_01f16f0_();
  zz_01f1778_();
  return 0;
}



// ==== 801f1594  FUN_801f1594 ====

void FUN_801f1594(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
                 undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8)

{
  int iVar1;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar2;
  
  iVar1 = zz_0027adc_();
  if (iVar1 == 0) {
    *(short *)(PTR_DAT_80435a30 + 4) = *(short *)(PTR_DAT_80435a30 + 4) + 1;
    uVar2 = zz_0027c1c_();
    zz_01b1aa4_(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,0,
                (int)(char)PTR_DAT_80435a30[0x46],*(undefined4 *)(PTR_DAT_80435a30 + 0x2c),
                *(undefined4 *)(PTR_DAT_80435a30 + 0x28),*(undefined4 *)(PTR_DAT_80435a30 + 0x24),
                in_r8,in_r9,in_r10);
    PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] | 0x80;
  }
  return;
}



// ==== 801f1600  FUN_801f1600 ====

void FUN_801f1600(void)

{
  int iVar1;
  
  iVar1 = zz_01b1b84_();
  if (iVar1 == 0) {
    *(short *)(PTR_DAT_80435a30 + 2) = *(short *)(PTR_DAT_80435a30 + 2) + 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 4) = 0;
    PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] & 0x7f;
  }
  else if ((iVar1 < 0) && (-2 < iVar1)) {
    *(short *)(PTR_DAT_80435a30 + 2) = *(short *)(PTR_DAT_80435a30 + 2) + 1;
    *(undefined2 *)(PTR_DAT_80435a30 + 4) = 0;
    PTR_DAT_80433930[0x2b] = PTR_DAT_80433930[0x2b] & 0x7f;
  }
  return;
}



// ==== 801f1694  FUN_801f1694 ====

undefined4
FUN_801f1694(undefined8 param_1,undefined8 param_2,undefined8 param_3,undefined8 param_4,
            undefined8 param_5,undefined8 param_6,undefined8 param_7,undefined8 param_8,
            undefined4 param_9,undefined4 param_10,undefined4 param_11,undefined4 param_12,
            undefined4 param_13,undefined4 param_14,undefined4 param_15,undefined4 param_16)

{
  zz_01ba78c_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,
              param_11,param_12,param_13,param_14,param_15,param_16);
  zz_007fd5c_();
  return 1;
}



// ==== 801f16bc  zz_01f16bc_ ====

void zz_01f16bc_(void)

{
  gnt4_memset(&DAT_803c73b0,0,0x3e4);
  zz_01f16f0_();
  return;
}



// ==== 801f16f0  zz_01f16f0_ ====

void zz_01f16f0_(void)

{
  DAT_803c7698 = FLOAT_8043c538;
  DAT_803c769c = FLOAT_8043c538;
  DAT_803c76a0 = FLOAT_8043c538;
  DAT_803c76b0 = FLOAT_8043c538;
  DAT_803c76b4 = FLOAT_8043c538;
  DAT_803c76b8 = FLOAT_8043c53c;
  DAT_803c76e0 = FLOAT_8043c538;
  DAT_803c76e4 = FLOAT_8043c540;
  DAT_803c76e8 = FLOAT_8043c538;
  gnt4_C_MTXLookAt_bl((float *)&DAT_803c7744,&DAT_803c7698,&DAT_803c76e0,&DAT_803c76b0);
  PTR_DAT_80433930[0xc] = 0;
  *(undefined **)(PTR_DAT_80433930 + 0x14) = &DAT_803c7744;
  return;
}



// ==== 801f1778  zz_01f1778_ ====

void zz_01f1778_(void)

{
  zz_01f179c_();
  zz_01f17c8_();
  return;
}



// ==== 801f179c  zz_01f179c_ ====

void zz_01f179c_(void)

{
  zz_0089898_(0x38);
  zz_0089554_();
  zz_0089658_();
  return;
}



// ==== 801f17c8  zz_01f17c8_ ====

void zz_01f17c8_(void)

{
  zz_008a16c_();
  zz_0089c00_(0x38);
  zz_008c104_(FUN_80089f28);
  return;
}



// ==== 801f17fc  zz_01f17fc_ ====

void zz_01f17fc_(void)

{
  float fVar1;
  float fVar2;
  
  DAT_804363a8 = &DAT_803d6648;
  gnt4_memset(&DAT_803d6648,0,0x2c);
  fVar1 = FLOAT_8043c5bc;
  DAT_804363a8[0x28] = 1;
  fVar2 = FLOAT_8043c5c0;
  DAT_804363a8[0x29] = 1;
  *(undefined4 *)(DAT_804363a8 + 0x14) = 0;
  *(float *)(DAT_804363a8 + 0x18) = fVar1;
  *(float *)(DAT_804363a8 + 0x1c) = fVar2;
  *(float *)(DAT_804363a8 + 0x20) = fVar2;
  zz_01f1928_();
  return;
}



// ==== 801f1874  zz_01f1874_ ====

int zz_01f1874_(void)

{
  float fVar1;
  uint uVar2;
  
  *(float *)(DAT_804363a8 + 0x1c) =
       *(float *)(DAT_804363a8 + 0x1c) + *(float *)(DAT_804363a8 + 0x18);
  if (*(char *)(DAT_804363a8 + 0x2a) == '\0') {
    if (*(float *)(DAT_804363a8 + 0x20) <= *(float *)(DAT_804363a8 + 0x1c)) {
      zz_01f1954_();
      fVar1 = FLOAT_8043c5c0;
      *(int *)(DAT_804363a8 + 0x14) = *(int *)(DAT_804363a8 + 0x14) + 1;
      *(float *)(DAT_804363a8 + 0x1c) = fVar1;
    }
  }
  if ((*(int *)(DAT_804363a8 + 0x24) == 1) || (uVar2 = zz_008b980_(0xf), uVar2 != 0)) {
    *(undefined1 *)(DAT_804363a8 + 0x28) = 0;
    *(undefined1 *)(DAT_804363a8 + 0x29) = 0;
  }
  return (int)*(char *)(DAT_804363a8 + 0x28);
}



// ==== 801f1928  zz_01f1928_ ====

void zz_01f1928_(void)

{
  zz_01f1a80_(0,0,0);
  return;
}



// ==== 801f1954  zz_01f1954_ ====

void zz_01f1954_(void)

{
  char cVar1;
  char cVar2;
  uint uVar3;
  size_t sVar4;
  int iVar5;
  uint uVar6;
  char *pcVar7;
  char *__s;
  
  pcVar7 = (&PTR_s_20PLANNING_803a17f8)[*(int *)(DAT_804363a8 + 0x14)];
  cVar1 = pcVar7[1];
  __s = pcVar7 + 2;
  iVar5 = *pcVar7 + -0x30;
  if (iVar5 != 4) {
    if (iVar5 < 4) {
      if (0 < iVar5) {
        sVar4 = strlen(__s);
        uVar6 = sVar4 * -2 + 0x32 >> 1;
        while( true ) {
          cVar2 = *__s;
          __s = __s + 1;
          uVar3 = (uint)cVar2;
          if (uVar3 == 0) break;
          if ((0x20 < uVar3) && (uVar3 < 0x80)) {
            zz_01f1a80_((char)iVar5,uVar6,
                        *(undefined1 *)((int)&PTR_s_12HITOMI_NISHIMOTO_803a19e4 + uVar3));
          }
          uVar6 = uVar6 + 2;
        }
      }
    }
    else {
      if (iVar5 == 9) {
        *(undefined1 *)(DAT_804363a8 + 0x2a) = 1;
        return;
      }
      if (iVar5 < 9) {
        zz_01f1a80_((char)iVar5,0,*(undefined1 *)(*pcVar7 + -0x7fbca465));
      }
    }
  }
  *(float *)(DAT_804363a8 + 0x20) =
       (float)((double)CONCAT44(0x43300000,(uint)(byte)(&DAT_80435b98)[cVar1]) - DOUBLE_8043c5c8);
  return;
}



// ==== 801f1a80  zz_01f1a80_ ====

void zz_01f1a80_(undefined1 param_1,uint param_2,undefined1 param_3)

{
  char cVar1;
  float fVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  double dVar6;
  undefined1 *puVar7;
  
  puVar7 = zz_008893c_(2,0x28,1,1);
  if (puVar7 != (undefined1 *)0x0) {
    *puVar7 = 1;
    puVar7[0x10] = 0;
    puVar7[0x11] = param_1;
    *(code **)(puVar7 + 0xc) = FUN_801f1bfc;
    *(code **)(puVar7 + 0x10c) = FUN_801f1e54;
    puVar7[0x13] = param_3;
    fVar2 = FLOAT_8043c5ec;
    fVar5 = FLOAT_8043c5e4;
    fVar4 = FLOAT_8043c5dc;
    fVar3 = FLOAT_8043c5d4;
    cVar1 = puVar7[0x11];
    if (cVar1 != '\x04') {
      if (cVar1 < '\x04') {
        if ('\0' < cVar1) {
          fVar2 = FLOAT_8043c5e0 *
                  (float)((double)CONCAT44(0x43300000,param_2 ^ 0x80000000) - DOUBLE_8043c5f0);
          *(float *)(puVar7 + 100) =
               FLOAT_8043c5d4 *
               FLOAT_8043c5d8 *
               (float)((double)CONCAT44(0x43300000,param_2 ^ 0x80000000) - DOUBLE_8043c5f0) +
               FLOAT_8043c5d0;
          *(float *)(puVar7 + 0x6c) = fVar3 * fVar2 + fVar4;
          *(float *)(puVar7 + 0x68) = fVar5;
        }
      }
      else if (cVar1 < '\t') {
        *(float *)(puVar7 + 100) = FLOAT_8043c5e8;
        dVar6 = DOUBLE_8043c5f0;
        *(float *)(puVar7 + 0x6c) = fVar2;
        *(float *)(puVar7 + 0x68) =
             FLOAT_8043c5e4 -
             (float)((double)CONCAT44(0x43300000,
                                      (int)*(char *)((char)puVar7[0x11] + -0x7fbca431) ^ 0x80000000)
                    - dVar6);
      }
    }
    *(int *)(DAT_804363a8 + 0x24) = *(int *)(DAT_804363a8 + 0x24) + 1;
  }
  return;
}



// ==== 801f1bfc  FUN_801f1bfc ====

void FUN_801f1bfc(int param_1)

{
  (*(code *)(&PTR_FUN_803a1a64)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801f1c38  FUN_801f1c38 ====

void FUN_801f1c38(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  float fVar2;
  undefined4 extraout_r4;
  float *pfVar3;
  undefined8 uVar4;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  *(undefined1 *)(param_9 + 0x84) = 0x1f;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  uVar4 = zz_0089100_(param_9,0,1);
  *(undefined2 *)(param_9 + 0x74) = 0;
  fVar2 = FLOAT_8043c5f8;
  *(undefined2 *)(param_9 + 0x72) = 0;
  *(undefined2 *)(param_9 + 0x70) = 0;
  *(undefined2 *)(param_9 + 0x72) = 0xe906;
  *(float *)(param_9 + 0x60) = fVar2;
  *(float *)(param_9 + 0x5c) = fVar2;
  *(float *)(param_9 + 0x58) = fVar2;
  *(undefined4 *)(param_9 + 0x54) = DAT_803bb36c;
  pfVar3 = (float *)(int)*(char *)(param_9 + 0x13);
  zz_0006fb4_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0x54)
              ,*(int *)(param_9 + 0xe0),(int)pfVar3,param_12,param_13,param_14,param_15,param_16);
  cVar1 = *(char *)(param_9 + 0x11);
  if ((cVar1 != '\0') && (cVar1 < 7)) {
    uVar4 = zz_00087d4_((double)(float)((double)CONCAT44(0x43300000,(int)cVar1 ^ 0x80000000) -
                                       DOUBLE_8043c5f0),param_2,param_3,param_4,param_5,param_6,
                        param_7,param_8,*(int *)(param_9 + 0x54),*(int *)(param_9 + 0xe0),pfVar3,
                        param_12,param_13,param_14,param_15,param_16);
    zz_0007c30_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),extraout_r4,pfVar3,param_12,param_13,param_14,param_15,
                param_16);
  }
  *(undefined1 *)(param_9 + 0x82) = 3;
  return;
}



// ==== 801f1e34  FUN_801f1e34 ====

void FUN_801f1e34(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801f1e54  FUN_801f1e54 ====

void FUN_801f1e54(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  if (*(char *)(param_9 + 0x11) != '\0') {
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(param_9 + 0xe0),(float *)(param_9 + 0x114),param_11,param_12,param_13,
                param_14,param_15,param_16);
  }
  zz_00097b4_(*(int *)(param_9 + 0xe0),0x47);
  return;
}



// ==== 801f1ea0  zz_01f1ea0_ ====

void zz_01f1ea0_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,2);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x33;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 2;
    *(code **)(puVar1 + 0xc) = FUN_801f1fa8;
    *(code **)(puVar1 + 0x10c) = FUN_801f232c;
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



// ==== 801f1fa8  FUN_801f1fa8 ====

void FUN_801f1fa8(int param_1)

{
  (*(code *)(&PTR_FUN_803a1b18)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 801f1fe4  FUN_801f1fe4 ====

void FUN_801f1fe4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int *piVar4;
  int iVar5;
  int iVar6;
  short *psVar7;
  int iVar8;
  undefined8 uVar9;
  
  uVar1 = *(char *)(param_9 + 0x13) * 0x24;
  if (uVar1 < 0x81) {
    *(int *)(param_9 + 0x54) = param_9 + 0x144;
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar4 = zz_0006dc8_(uVar1);
    *(int **)(param_9 + 0xdc) = piVar4;
    if (piVar4 != (int *)0x0) {
      *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    }
  }
  if (*(int *)(param_9 + 0x54) == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    *(undefined1 *)(param_9 + 0x18) = 1;
    uVar3 = 3;
    *(undefined2 *)(param_9 + 0x1c) = 0;
    *(undefined1 *)(param_9 + 0x89) = 3;
    *(code **)(param_9 + 0x100) = FUN_801f2280;
    zz_0089100_(param_9,1,1);
    psVar7 = &DAT_803a1b00;
    iVar8 = 0;
    iVar6 = param_9;
    for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
      *(ushort *)(param_9 + 0x1c) = *(ushort *)(param_9 + 0x1c) | (ushort)(1 << iVar5);
      piVar4 = (int *)(*(int *)(param_9 + 0x54) + iVar8);
      *(undefined2 *)(piVar4 + 8) = 0;
      *(short *)((int)piVar4 + 0x22) = psVar7[1];
      zz_0018f88_(piVar4,*(int *)(psVar7 + 2),(float *)(piVar4 + 4));
      uVar9 = zz_0019338_(piVar4 + 2,*(int *)(psVar7 + 4),(float *)(piVar4 + 7));
      iVar2 = zz_0006f78_(*(int *)(param_9 + 0x90));
      zz_0006fb4_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar2,
                  *(int *)(iVar6 + 0xe0),(int)*psVar7,uVar3,in_r7,in_r8,in_r9,in_r10);
      zz_0007cac_((double)(float)piVar4[7],*(int *)(iVar6 + 0xe0));
      iVar8 = iVar8 + 0x24;
      psVar7 = psVar7 + 6;
      iVar6 = iVar6 + 4;
    }
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  }
  return;
}



// ==== 801f214c  FUN_801f214c ====

void FUN_801f214c(int param_1)

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
    iVar5 = iVar5 + 0x24;
    iVar4 = iVar4 + 4;
    iVar3 = iVar3 + 1;
  }
  if (*(short *)(param_1 + 0x1c) == 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801f2238  FUN_801f2238 ====

void FUN_801f2238(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801f2280  FUN_801f2280 ====

void FUN_801f2280(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  float afStack_48 [13];
  
  gnt4_PSMTXCopy_bl((float *)(*(int *)(param_9 + 0x8c) + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4),
                    (float *)(param_9 + 0x114));
  iVar2 = 0;
  iVar4 = 0;
  iVar3 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar2) break;
    if (((int)*(short *)(param_9 + 0x1c) & 1 << iVar2) != 0) {
      pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar4 + 0x10);
      uVar5 = zz_00456a0_((float *)(param_9 + 0x114),afStack_48,pfVar1);
      zz_00076d0_(uVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(iVar3 + 0xe0),afStack_48,(undefined *)pfVar1,param_12,param_13,param_14,
                  param_15,param_16);
    }
    iVar4 = iVar4 + 0x24;
    iVar3 = iVar3 + 4;
    iVar2 = iVar2 + 1;
  }
  return;
}



// ==== 801f232c  FUN_801f232c ====

void FUN_801f232c(int param_1)

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



// ==== 801f23b0  zz_01f23b0_ ====

void zz_01f23b0_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(*(int *)(param_1 + 0x90),3,8,0,4);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x61;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_801f24ac;
    *(code **)(puVar1 + 0x10c) = FUN_801f2858;
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



// ==== 801f24ac  FUN_801f24ac ====

void FUN_801f24ac(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    *(undefined1 *)(param_1 + 0x1b) = 0;
    *(undefined1 *)(param_1 + 0x1a) = 0;
    *(undefined1 *)(param_1 + 0x19) = 0;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_803a1db0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801f2554  FUN_801f2554 ====

void FUN_801f2554(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  int *piVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar8;
  
  fVar1 = FLOAT_8043c608;
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar6 = (uint)*(byte *)(param_9 + 0x11) * 0x18;
  *(undefined1 *)(param_9 + 0x13) = 0;
  *(float *)(param_9 + 0xd4) = fVar1;
  uVar4 = 1;
  *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_803a1d68 + iVar6);
  *(char *)(param_9 + 0x89) = (char)*(undefined2 *)(&DAT_803a1d6a + iVar6);
  uVar5 = *(undefined4 *)(&DAT_803a1d6c + iVar6);
  uVar3 = *(undefined4 *)(&DAT_803a1d70 + iVar6);
  *(undefined4 *)(param_9 + 100) = uVar5;
  *(undefined4 *)(param_9 + 0x68) = uVar3;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_803a1d74 + iVar6);
  *(undefined *)(param_9 + 0x14) = (&DAT_803a1d7e)[iVar6];
  *(undefined *)(param_9 + 0x15) = (&DAT_803a1d7f)[iVar6];
  *(code **)(param_9 + 0x100) = FUN_801f2774;
  iVar7 = iVar6;
  uVar8 = zz_0089100_(param_9,(int)*(char *)(*(int *)(param_9 + 0x90) + 0x3e4) + 0x10,1);
  piVar2 = zz_0006dc8_(0xa0);
  *(int **)(param_9 + 0xdc) = piVar2;
  uVar8 = zz_01f28e0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0,uVar4,
                      uVar5,iVar7,in_r8,in_r9,in_r10);
  zz_01f28e0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,uVar4,uVar5,
              iVar7,in_r8,in_r9,in_r10);
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
  if (-1 < *(short *)(&DAT_803a1d7c + iVar6)) {
    zz_00f061c_((double)FLOAT_8043c60c,*(int *)(param_9 + 0x90),
                (int)*(short *)(&DAT_803a1d7c + iVar6));
  }
  return;
}



// ==== 801f2658  FUN_801f2658 ====

void FUN_801f2658(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  int iVar2;
  undefined *puVar3;
  float *pfVar4;
  double dVar5;
  
  puVar3 = &DAT_803a1d68;
  dVar5 = (double)*(float *)(param_9 + 0xd4);
  pfVar4 = (float *)((uint)*(byte *)(param_9 + 0x11) * 0x18);
  *(float *)(param_9 + 0xd4) = (float)(dVar5 + (double)FLOAT_8043c610);
  cVar1 = *(char *)(param_9 + 0x19);
  if ((((cVar1 != '\x01') && (cVar1 < '\x01')) && (-1 < cVar1)) &&
     (dVar5 = (double)*(float *)(param_9 + 0xd4), (double)FLOAT_8043c614 <= dVar5)) {
    puVar3 = (undefined *)(int)*(short *)(pfVar4 + -0x1ff178a6);
    iVar2 = zz_008ac80_(param_9,(int)puVar3);
    if (iVar2 == 0) {
      *(undefined1 *)(param_9 + 0x19) = 1;
    }
  }
  zz_01f29e0_(dVar5,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,puVar3,pfVar4,
              param_12,param_13,param_14,param_15,param_16);
  if (*(char *)(param_9 + 0x13) == '\0') {
    *(undefined1 *)(param_9 + 0x18) = 2;
    *(undefined1 *)(param_9 + 0x82) = 0;
    zz_008aff0_(param_9);
  }
  return;
}



// ==== 801f2718  FUN_801f2718 ====

void FUN_801f2718(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801f272c  FUN_801f272c ====

void FUN_801f272c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 801f2774  FUN_801f2774 ====

void FUN_801f2774(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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
  float afStack_48 [13];
  
  zz_00455fc_((float *)(*(int *)(param_9 + 0x8c) + *(char *)(param_9 + 0x89) * 0x30 + 0x8d4),
              (float *)(param_9 + 0x114),(float *)(param_9 + 100));
  *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(param_9 + 0x120);
  *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(param_9 + 0x130);
  *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(param_9 + 0x140);
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar5 = 0;
    iVar7 = 0;
    iVar6 = param_9;
    do {
      if (((int)*(char *)(param_9 + 0x13) & 1 << iVar5) != 0) {
        iVar4 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar7;
        sVar1 = *(short *)(iVar4 + 0x20);
        iVar3 = (int)sVar1;
        zz_00457d4_('y',(float *)(param_9 + 0x114),afStack_48,sVar1);
        pfVar2 = (float *)(iVar4 + 0x10);
        uVar8 = zz_00456a0_(afStack_48,afStack_48,pfVar2);
        zz_00076d0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                    *(int *)(iVar6 + 0xe0),afStack_48,(undefined *)pfVar2,iVar3,in_r7,in_r8,in_r9,
                    in_r10);
      }
      iVar5 = iVar5 + 1;
      iVar6 = iVar6 + 4;
      iVar7 = iVar7 + 0x28;
    } while (iVar5 < 4);
  }
  return;
}



// ==== 801f2858  FUN_801f2858 ====

void FUN_801f2858(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0xdc) != 0) {
    iVar1 = 0;
    iVar2 = param_1;
    do {
      if (((int)*(char *)(param_1 + 0x13) & 1 << iVar1) != 0) {
        zz_00097b4_(*(int *)(iVar2 + 0xe0),0x44);
      }
      iVar1 = iVar1 + 1;
      iVar2 = iVar2 + 4;
    } while (iVar1 < 4);
  }
  return;
}



// ==== 801f28e0  zz_01f28e0_ ====

void zz_01f28e0_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,int param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  undefined *puVar2;
  int iVar3;
  short *psVar4;
  int *piVar5;
  int iVar6;
  undefined8 uVar7;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    iVar3 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc);
    puVar2 = (&PTR_DAT_803a1d78)[(uint)*(byte *)(param_9 + 0x11) * 6];
    *(byte *)(param_9 + 0x13) = *(byte *)(param_9 + 0x13) | (byte)(1 << param_10);
    piVar5 = (int *)(iVar3 + param_10 * 0x28);
    *(undefined2 *)((int)piVar5 + 0x22) = 0;
    psVar4 = (short *)(puVar2 + param_10 * 0xc);
    *(short *)(piVar5 + 9) = psVar4[1];
    uVar1 = zz_00055fc_();
    *(short *)(piVar5 + 8) = (short)(uVar1 << 8);
    zz_0018f88_(piVar5,*(int *)(psVar4 + 2),(float *)(piVar5 + 4));
    uVar7 = zz_0019338_(piVar5 + 2,*(int *)(psVar4 + 4),(float *)(piVar5 + 7));
    iVar3 = zz_0006f78_(*(int *)(param_9 + 0x90));
    iVar6 = param_9 + param_10 * 4;
    zz_000726c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                *(int *)(iVar6 + 0xe0),(float *)(int)*psVar4,(int)*(char *)(param_9 + 0x88),param_13
                ,param_14,param_15,param_16);
    zz_0007cac_((double)(float)piVar5[7],*(int *)(iVar6 + 0xe0));
  }
  return;
}



// ==== 801f29e0  zz_01f29e0_ ====

void zz_01f29e0_(double param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  double dVar1;
  short sVar3;
  int iVar2;
  int iVar4;
  int *piVar5;
  uint uVar6;
  int iVar7;
  int iVar8;
  
  if (*(int *)(param_9 + 0xdc) != 0) {
    uVar6 = 0;
    iVar8 = 0;
    iVar7 = param_9;
    do {
      if (((int)*(char *)(param_9 + 0x13) & 1 << uVar6) != 0) {
        piVar5 = (int *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar8);
        sVar3 = *(short *)((int)piVar5 + 0x22) + 1;
        *(short *)((int)piVar5 + 0x22) = sVar3;
        if (*(short *)(piVar5 + 9) <= sVar3) {
          *(byte *)(param_9 + 0x13) = *(byte *)(param_9 + 0x13) & ~(byte)(1 << uVar6);
        }
        if (((uVar6 & 0xfe) == 0) && (*(short *)((int)piVar5 + 0x22) == 0x3c)) {
          zz_01f28e0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                      uVar6 + 2,param_11,param_12,param_13,param_14,param_15,param_16);
        }
        zz_0018fd8_(piVar5,(int)*(short *)((int)piVar5 + 0x22),(float *)(piVar5 + 4));
        param_11 = (float *)(piVar5 + 7);
        zz_0019370_(piVar5 + 2,(int)*(short *)((int)piVar5 + 0x22),param_11);
        param_1 = (double)zz_0007cac_((double)(float)piVar5[7],*(int *)(iVar7 + 0xe0));
        dVar1 = DOUBLE_8043c620;
        if (uVar6 == 1) {
          iVar4 = ((int)*(short *)((int)piVar5 + 0x22) & 1U) * 0xc;
          iVar2 = *(int *)(&DAT_803a1dc4 + iVar4);
          piVar5[4] = *(int *)(&DAT_803a1dc0 + iVar4);
          piVar5[5] = iVar2;
          piVar5[6] = *(int *)(&DAT_803a1dc8 + iVar4);
        }
        else if (uVar6 == 2) {
          param_1 = (double)(float)((double)CONCAT44(0x43300000,
                                                     (int)*(short *)(piVar5 + 8) ^ 0x80000000) -
                                   DOUBLE_8043c620);
          *(short *)(piVar5 + 8) = (short)(int)(param_1 + (double)FLOAT_8043c618);
          param_2 = dVar1;
        }
        else if (uVar6 == 3) {
          piVar5[4] = (int)((float)piVar5[4] *
                           *(float *)(&DAT_803a1dc0 +
                                     ((int)*(short *)((int)piVar5 + 0x22) & 1U) * 0xc));
          piVar5[5] = (int)((float)piVar5[5] *
                           *(float *)(&DAT_803a1dc4 +
                                     ((int)*(short *)((int)piVar5 + 0x22) & 1U) * 0xc));
          param_1 = (double)(float)piVar5[6];
          piVar5[6] = (int)(float)(param_1 *
                                  (double)*(float *)(&DAT_803a1dc8 +
                                                    ((int)*(short *)((int)piVar5 + 0x22) & 1U) * 0xc
                                                    ));
          if ((int)*(short *)((int)piVar5 + 0x22) < *(short *)(piVar5 + 9) + -0x20) {
            param_11 = (float *)(int)(char)*(byte *)(param_9 + 0x15);
            if ((-1 < (char)*(byte *)(param_9 + 0x14)) && (-1 < (int)param_11)) {
              param_11 = (float *)(uint)*(byte *)(param_9 + 0x15);
              param_1 = (double)zz_00f0104_(*(int *)(param_9 + 0x90),(uint)*(byte *)(param_9 + 0x14)
                                            ,(uint)param_11);
            }
          }
        }
      }
      uVar6 = uVar6 + 1;
      iVar7 = iVar7 + 4;
      iVar8 = iVar8 + 0x28;
    } while ((int)uVar6 < 4);
  }
  return;
}



// ==== 801f2bf8  FUN_801f2bf8 ====

/* WARNING: Removing unreachable block (ram,0x801f2d1c) */
/* WARNING: Removing unreachable block (ram,0x801f2c08) */

void FUN_801f2bf8(double param_1,int param_2,undefined1 param_3,char param_4)

{
  undefined1 *puVar1;
  
  if ((((*(short *)(param_2 + 1000) == 0xe00) || (*(short *)(param_2 + 1000) == 0xe05)) &&
      (param_4 < '\x1e')) && (puVar1 = zz_0088aa0_(param_2,3,8,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x13] = param_4;
    puVar1[0x11] = param_3;
    puVar1[0x83] = 0x10;
    *(code **)(puVar1 + 0xc) = FUN_801f2d40;
    *(code **)(puVar1 + 0x10c) = FUN_801f3400;
    *(float *)(puVar1 + 0xd8) = (float)param_1;
    *(int *)(puVar1 + 0x8c) = param_2;
    *(undefined4 *)(puVar1 + 0x90) = *(undefined4 *)(param_2 + 0x90);
    *(undefined2 *)(puVar1 + 0x94) = *(undefined2 *)(param_2 + 0x94);
    puVar1[0x96] = *(undefined1 *)(param_2 + 0x96);
    puVar1[0x97] = *(undefined1 *)(param_2 + 0x97);
    puVar1[0x88] = *(undefined1 *)(param_2 + 0x88);
    *(undefined4 *)(puVar1 + 200) = *(undefined4 *)(param_2 + 200);
    *(undefined4 *)(puVar1 + 0xcc) = *(undefined4 *)(param_2 + 0xcc);
    *(undefined4 *)(puVar1 + 0xb8) = *(undefined4 *)(param_2 + 0xb8);
    *(undefined4 *)(puVar1 + 0xb4) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(puVar1 + 0x58) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(puVar1 + 0x5c) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(puVar1 + 0x60) = *(undefined4 *)(param_2 + 0xb4);
    *(undefined4 *)(puVar1 + 0xc0) = *(undefined4 *)(param_2 + 0xc0);
    *(undefined4 *)(puVar1 + 0xc4) = *(undefined4 *)(param_2 + 0xc4);
    puVar1[0xd0] = *(undefined1 *)(param_2 + 0xd0);
  }
  return;
}



