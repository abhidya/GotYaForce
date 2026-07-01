// ==== 8013e8d4  FUN_8013e8d4 ====

void FUN_8013e8d4(int param_1)

{
  int iVar1;
  double dVar2;
  
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043a13c,param_1);
  dVar2 = (double)FLOAT_8043a0fc;
  *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  FUN_80067310(dVar2,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if ((iVar1 != 0) && (*(char *)(param_1 + 0x1cef) < '\0')) {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a140 + *(float *)(param_1 + 0x1dc8);
    return;
  }
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
  }
  return;
}



// ==== 8013e9a4  FUN_8013e9a4 ====

void FUN_8013e9a4(int param_1)

{
  (*(code *)(&PTR_FUN_80339a90)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8013e9e0  FUN_8013e9e0 ====

void FUN_8013e9e0(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  *(short *)(param_1 + 0x18e0) = *(short *)(param_1 + 0x18e0) >> 1;
  (*(code *)(&PTR_FUN_80339aa4)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8013ea34  FUN_8013ea34 ====

void FUN_8013ea34(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  fVar3 = FLOAT_8043a148;
  fVar2 = FLOAT_8043a11c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  *(undefined1 *)(param_1 + 0x6f6) = 1;
  *(float *)(param_1 + 0x558) = fVar2;
  *(undefined2 *)(param_1 + 0x5ae) = *(undefined2 *)(param_1 + 0x72);
  *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) | 0x43;
  *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar3;
  *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar3;
  fVar2 = FLOAT_8043a110;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    *(float *)(param_1 + 0x48) = FLOAT_8043a120;
    *(float *)(param_1 + 0x50) = fVar2;
  }
  else {
    *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * fVar3;
    *(float *)(param_1 + 0x50) = *(float *)(param_1 + 0x50) * fVar3;
  }
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043a110;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8013eb04  FUN_8013eb04 ====

void FUN_8013eb04(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  FUN_80067310((double)FLOAT_8043a0fc,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a0f8;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  fVar3 = FLOAT_8043a0fc;
  if (fVar1 <= fVar2) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x4c) = fVar2;
    *(float *)(param_1 + 0x44) = fVar2;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x50) = fVar2;
    FUN_800061a8(param_1,4);
  }
  return;
}



// ==== 8013eba4  FUN_8013eba4 ====

void FUN_8013eba4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,char *param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  char cVar1;
  undefined4 extraout_r4;
  float *pfVar2;
  undefined8 uVar3;
  double dVar4;
  
  zz_004cd24_((int)param_9,0xf);
  FUN_80067310((double)FLOAT_8043a0fc,(int)param_9,*(short *)(param_9 + 0x5ae));
  zz_00677b0_((int)param_9);
  if (param_9[0x1cee] != '\0') {
    param_9[0x540] = param_9[0x540] + '\x01';
    param_9[0x6f6] = '\0';
    pfVar2 = (float *)(uint)(byte)param_9[0x3ec];
    zz_006a8c0_(param_9,0x803);
    uVar3 = FUN_8013cafc((int)param_9);
    FUN_8013c844(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,
                 extraout_r4,pfVar2,param_12,param_13,param_14,param_15,param_16);
    FUN_800562b8((int)param_9);
    FUN_80184250((int)param_9,0);
    cVar1 = param_9[0x6ea];
    dVar4 = (double)FLOAT_8043a110;
    param_9[0x6ea] = cVar1 + '\x01';
    zz_004beb8_(dVar4,(int)param_9,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  }
  return;
}



// ==== 8013ec6c  FUN_8013ec6c ====

void FUN_8013ec6c(int param_1)

{
  zz_004cd24_(param_1,0xf);
  FUN_80067310((double)FLOAT_8043a0fc,param_1,*(short *)(param_1 + 0x5ae));
  zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a5a4_(param_1);
    *(ushort *)(param_1 + 0x272) = *(ushort *)(param_1 + 0x272) & 0xffbc;
  }
  return;
}



// ==== 8013ecec  FUN_8013ecec ====

void FUN_8013ecec(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,char *param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined4 extraout_r4;
  float *pfVar1;
  undefined8 uVar2;
  
  pfVar1 = (float *)(uint)(byte)param_9[0x3ec];
  zz_006a8c0_(param_9,0x802);
  uVar2 = FUN_8013cafc((int)param_9);
  FUN_8013c844(uVar2,param_2,param_3,param_4,param_5,param_6,param_7,param_8,(int)param_9,
               extraout_r4,pfVar1,param_12,param_13,param_14,param_15,param_16);
  FUN_800562b8((int)param_9);
  FUN_800061a8((int)param_9,6);
  param_9[0x73f] = '\0';
  *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
  zz_006a5a4_((int)param_9);
  return;
}



// ==== 8013ed60  FUN_8013ed60 ====

void FUN_8013ed60(int param_1)

{
  (*(code *)(&PTR_FUN_80339ab4)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 8013ed9c  FUN_8013ed9c ====

void FUN_8013ed9c(int param_1)

{
  (*(code *)(&PTR_FUN_80339ac8)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 8013edd8  FUN_8013edd8 ====

void FUN_8013edd8(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  fVar2 = FLOAT_8043a14c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined2 *)(param_1 + 0x54a) = *(undefined2 *)(param_1 + 0x5ae);
  *(float *)(param_1 + 0x560) = fVar2;
  *(undefined2 *)(param_1 + 0x54e) = 10;
  *(undefined1 *)(param_1 + 0x6ea) = 2;
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) != 0) {
    *(undefined1 *)(param_1 + 0x6ea) = 5;
  }
  *(undefined1 *)(param_1 + 0x6f7) = 0;
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006e39c_(param_1,0xc1,2,0x2000,(float *)(param_1 + 0x524));
  }
  else {
    zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  }
  fVar3 = FLOAT_8043a114;
  fVar2 = FLOAT_8043a0f8;
  if (*(char *)(param_1 + 0x581) == '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_8043a0f8;
    *(float *)(param_1 + 0x44) = fVar2;
  }
  else {
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * FLOAT_8043a114;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar3;
  }
  fVar2 = FLOAT_8043a0f8;
  dVar4 = (double)FLOAT_8043a0fc;
  *(float *)(param_1 + 0x48) = *(float *)(param_1 + 0x48) * FLOAT_8043a114;
  *(float *)(param_1 + 0x50) = fVar2;
  FUN_80067310(dVar4,param_1,*(short *)(param_1 + 0x54a));
  zz_00679d0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar4 = (double)FLOAT_8043a110;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
  return;
}



// ==== 8013ef2c  FUN_8013ef2c ====

void FUN_8013ef2c(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  
  zz_004cd24_(param_1,0xf);
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006e39c_(param_1,0xc1,2,0x2000,(float *)(param_1 + 0x524));
  }
  else {
    zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  }
  zz_006ed8c_((double)FLOAT_8043a114,param_1);
  FUN_80067310((double)FLOAT_8043a0fc,param_1,*(short *)(param_1 + 0x54a));
  zz_00679d0_(param_1);
  fVar2 = FLOAT_8043a14c;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    dVar4 = (double)FLOAT_8043a110;
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(undefined1 *)(param_1 + 0x6f7) = 2;
    *(float *)(param_1 + 0x560) = fVar2;
    *(undefined2 *)(param_1 + 0x54e) = 10;
    cVar1 = *(char *)(param_1 + 0x6ea);
    *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
    zz_004beb8_(dVar4,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
    iVar3 = zz_006dbe0_(param_1,2,1,1);
    if (iVar3 != 0) {
      zz_00e19a8_(param_1,2,param_1 + 0x6f7);
    }
  }
  return;
}



// ==== 8013f060  FUN_8013f060 ====

void FUN_8013f060(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(undefined1 *)(param_1 + 0x6f7) = 2;
  uVar2 = zz_006de44_(param_1,0xf0f00);
  dVar3 = DOUBLE_8043a108;
  if (uVar2 != 0) {
    if ((int)*(short *)(param_1 + 0x54e) < (int)uVar2) {
      uVar2 = (int)*(short *)(param_1 + 0x54e);
    }
    *(short *)(param_1 + 0x54e) = *(short *)(param_1 + 0x54e) - (short)uVar2;
    *(float *)(param_1 + 0x560) =
         *(float *)(param_1 + 0x560) +
         (float)((double)CONCAT44(0x43300000,uVar2 ^ 0x80000000) - dVar3);
  }
  zz_006d1a8_(param_1,0xc1,(float *)(param_1 + 0x524));
  if ((*(uint *)(param_1 + 0x5e0) & 0x40) == 0) {
    zz_006e39c_(param_1,0xc1,2,0x2000,(float *)(param_1 + 0x524));
  }
  else {
    zz_006e39c_(param_1,0xc1,1,0x4000,(float *)(param_1 + 0x524));
  }
  if (*(char *)(param_1 + 0x1cef) < '\0') {
    *(undefined1 *)(param_1 + 0x1cef) = 0;
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(*(int *)(param_1 + 0x4ac) + 0x6c);
  }
  zz_006ed8c_((double)FLOAT_8043a114,param_1);
  FUN_80067310((double)FLOAT_8043a0fc,param_1,*(short *)(param_1 + 0x54a));
  zz_00679d0_(param_1);
  zz_004cd24_(param_1,0xf);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    if (*(float *)(param_1 + 0x560) <= FLOAT_8043a0f8) {
      dVar3 = (double)FLOAT_8043a110;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(undefined1 *)(param_1 + 0x6f7) = 0;
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar3,param_1,0xf,4,(int)cVar1,0xffffffff,0xffffffff);
    }
    else {
      *(float *)(param_1 + 0x560) = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
    }
  }
  return;
}



// ==== 8013f1f4  FUN_8013f1f4 ====

void FUN_8013f1f4(int param_1)

{
  float fVar1;
  double dVar2;
  int iVar3;
  double dVar4;
  
  fVar1 = FLOAT_8043a138;
  dVar2 = DOUBLE_8043a108;
  dVar4 = (double)FLOAT_8043a114;
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a108) * FLOAT_8043a138);
  *(short *)(param_1 + 0x18e0) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18e0) ^ 0x80000000) - dVar2
                           ) * fVar1);
  zz_006ed8c_(dVar4,param_1);
  FUN_80067310((double)FLOAT_8043a0fc,param_1,*(short *)(param_1 + 0x54a));
  iVar3 = zz_00677b0_(param_1);
  zz_004cd24_(param_1,0xf);
  fVar1 = FLOAT_8043a0f8;
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    *(float *)(param_1 + 0x4c) = fVar1;
    *(float *)(param_1 + 0x44) = fVar1;
    if (iVar3 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
  }
  return;
}



// ==== 8013f300  zz_013f300_ ====

void zz_013f300_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,2,0x18,0,4);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x1c;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 4;
    *(code **)(puVar1 + 0xc) = FUN_8013f408;
    *(code **)(puVar1 + 0x10c) = FUN_8013f790;
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



// ==== 8013f408  FUN_8013f408 ====

void FUN_8013f408(int param_1)

{
  (*(code *)(&PTR_FUN_8033abe0)[*(char *)(param_1 + 0x18)])();
  return;
}



// ==== 8013f444  FUN_8013f444 ====

void FUN_8013f444(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int *piVar2;
  undefined4 extraout_r4;
  undefined4 uVar3;
  double dVar4;
  undefined8 uVar5;
  double dVar6;
  
  uVar1 = *(char *)(param_9 + 0x13) * 0x3c;
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
    dVar4 = zz_0045204_(*(short *)(param_9 + 0x1e));
    dVar6 = (double)FLOAT_8043a154;
    *(float *)(param_9 + 0xd4) = (float)(dVar4 * (double)FLOAT_8043a150 + (double)FLOAT_8043a150);
    dVar4 = (double)*(float *)(param_9 + 0xd4);
    if ((dVar4 <= dVar6) && (dVar6 = dVar4, dVar4 < (double)FLOAT_8043a158)) {
      dVar6 = (double)FLOAT_8043a158;
    }
    *(float *)(param_9 + 0xd4) = (float)dVar6;
    *(code **)(param_9 + 0x100) = FUN_8013f698;
    uVar3 = 1;
    uVar5 = zz_0089100_(param_9,1,1);
    FUN_8013f84c(uVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
                 uVar3,param_12,param_13,param_14,param_15,param_16);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  return;
}



// ==== 8013f548  FUN_8013f548 ====

void FUN_8013f548(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  int iVar2;
  double dVar3;
  double dVar4;
  double dVar5;
  
  iVar2 = *(int *)(param_9 + 0x8c);
  if (*(char *)(param_9 + 0x11) == '\0') {
    *(short *)(param_9 + 0x1e) = *(short *)(param_9 + 0x1e) + 0x222;
  }
  else {
    *(short *)(param_9 + 0x1e) = *(short *)(param_9 + 0x1e) + 0x444;
  }
  dVar4 = zz_0045204_(*(short *)(param_9 + 0x1e));
  dVar5 = (double)FLOAT_8043a154;
  *(float *)(param_9 + 0xd4) = (float)(dVar4 * (double)FLOAT_8043a150 + (double)FLOAT_8043a150);
  dVar3 = (double)*(float *)(param_9 + 0xd4);
  if ((dVar3 <= dVar5) && (dVar5 = dVar3, dVar3 < (double)FLOAT_8043a158)) {
    dVar5 = (double)FLOAT_8043a158;
  }
  *(float *)(param_9 + 0xd4) = (float)dVar5;
  zz_013fa70_(dVar4,dVar5,param_3,param_4,param_5,param_6,param_7,param_8,param_9,param_10,param_11,
              param_12,param_13,param_14,param_15,param_16);
  sVar1 = *(short *)(param_9 + 0x1c) + -1;
  *(short *)(param_9 + 0x1c) = sVar1;
  if (sVar1 < 1) {
    *(undefined2 *)(param_9 + 0x1c) = 0x18;
    zz_00f036c_(param_9,0x19);
  }
  if (*(char *)(param_9 + 0x11) == '\0') {
    sVar1 = *(short *)(iVar2 + 0x710);
  }
  else {
    sVar1 = *(short *)(iVar2 + 0x712);
  }
  if (sVar1 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  return;
}



// ==== 8013f650  FUN_8013f650 ====

void FUN_8013f650(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8013f698  FUN_8013f698 ====

void FUN_8013f698(int param_1)

{
  float fVar1;
  float *pfVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = *(int *)(param_1 + 0x8c);
  *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(iVar3 + 0x910);
  *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(iVar3 + 0x920);
  *(undefined4 *)(param_1 + 0x28) = *(undefined4 *)(iVar3 + 0x930);
  fVar1 = *(float *)(iVar3 + 0xb4) * *(float *)(iVar3 + 0x7fc);
  *(float *)(param_1 + 0x60) = fVar1;
  *(float *)(param_1 + 0x5c) = fVar1;
  *(float *)(param_1 + 0x58) = fVar1;
  for (iVar3 = 0; iVar3 < *(char *)(param_1 + 0x13); iVar3 = iVar3 + 1) {
    pfVar2 = (float *)(*(int *)(param_1 + 0x54) + iVar4);
    if (pfVar2[0xe] == 0.0) {
      gnt4_PSMTXTrans_bl((double)*(float *)(param_1 + 0x20),(double)*(float *)(param_1 + 0x24),
                         (double)*(float *)(param_1 + 0x28),pfVar2);
      zz_00457d4_('z',pfVar2,pfVar2,*(short *)((int)pfVar2 + 0x32));
      zz_00457d4_('x',pfVar2,pfVar2,*(short *)(pfVar2 + 0xc));
      zz_00456a0_(pfVar2,pfVar2,(float *)(param_1 + 0x58));
    }
    iVar4 = iVar4 + 0x3c;
  }
  return;
}



// ==== 8013f790  FUN_8013f790 ====

void FUN_8013f790(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 float *param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float *pfVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = 0;
  iVar3 = param_9;
  for (iVar2 = 0; iVar2 < *(char *)(param_9 + 0x13); iVar2 = iVar2 + 1) {
    pfVar1 = (float *)(*(int *)(param_9 + 0x54) + iVar4);
    if (pfVar1[0xe] != 0.0) {
      zz_00484e8_(pfVar1,(float *)(param_9 + 0x20),&DAT_802b0cb4,3);
      param_12 = (int)*(short *)(pfVar1 + 0xc);
      zz_00457d4_('z',pfVar1,pfVar1,*(short *)(pfVar1 + 0xc));
      param_11 = (float *)(param_9 + 0x58);
      param_1 = zz_00456a0_(pfVar1,pfVar1,param_11);
    }
    zz_00076d0_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                *(int *)(iVar3 + 0xe0),pfVar1,(undefined *)param_11,param_12,param_13,param_14,
                param_15,param_16);
    param_1 = zz_00097b4_(*(int *)(iVar3 + 0xe0),1);
    iVar4 = iVar4 + 0x3c;
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 8013f84c  FUN_8013f84c ====

/* WARNING: Removing unreachable block (ram,0x8013fa54) */
/* WARNING: Removing unreachable block (ram,0x8013fa4c) */
/* WARNING: Removing unreachable block (ram,0x8013f864) */
/* WARNING: Removing unreachable block (ram,0x8013f85c) */

void FUN_8013f84c(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  uint uVar2;
  uint uVar3;
  undefined4 extraout_r4;
  float *pfVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  double dVar8;
  double dVar9;
  undefined8 uVar10;
  double dVar11;
  double dVar12;
  double dVar13;
  
  uVar1 = countLeadingZeros((int)*(char *)(param_9 + 0x11));
  dVar11 = (double)*(float *)(param_9 + 0xd4);
  iVar7 = 0;
  dVar13 = (double)(float)(dVar11 + (double)(float)((double)CONCAT44(0x43300000,
                                                                     uVar1 >> 4 & 0xffffffe ^
                                                                     0x80000000) - DOUBLE_8043a168))
  ;
  iVar6 = param_9;
  dVar9 = DOUBLE_8043a168;
  for (uVar1 = 0; (int)uVar1 < (int)*(char *)(param_9 + 0x13); uVar1 = uVar1 + 1) {
    iVar5 = *(int *)(param_9 + 0x54) + iVar7;
    *(uint *)(iVar5 + 0x38) = uVar1 - 1 & ~-((uint)(uVar1 < 2) - ((int)uVar1 >> 0x1f));
    if (*(int *)(iVar5 + 0x38) == 0) {
      uVar2 = zz_00055fc_();
      dVar12 = (double)((float)((double)CONCAT44(0x43300000,uVar2 & 0x3f ^ 0x80000000) -
                               DOUBLE_8043a168) / FLOAT_8043a15c);
      uVar3 = zz_00055fc_();
      *(short *)(iVar5 + 0x30) = (short)(uVar3 << 8);
      uVar3 = zz_00055fc_();
      dVar8 = (double)FLOAT_8043a154;
      dVar11 = (double)FLOAT_8043a160;
      *(short *)(iVar5 + 0x32) = (short)(uVar3 << 8);
      dVar9 = (double)(longlong)(int)(dVar11 * dVar12);
      *(short *)(iVar5 + 0x34) = (short)(int)(dVar11 * dVar12);
      *(short *)(iVar5 + 0x36) = (short)(int)(dVar11 * (double)(float)(dVar8 - dVar12));
      if ((uVar2 & 0x80) != 0) {
        *(short *)(iVar5 + 0x34) = -*(short *)(iVar5 + 0x34);
      }
      if ((uVar2 & 0x40) != 0) {
        *(short *)(iVar5 + 0x36) = -*(short *)(iVar5 + 0x36);
      }
    }
    else {
      *(undefined2 *)(iVar5 + 0x36) = 0;
      *(undefined2 *)(iVar5 + 0x32) = 0;
      *(undefined2 *)(iVar5 + 0x30) = 0;
      if (*(int *)(iVar5 + 0x38) == 1) {
        *(undefined2 *)(iVar5 + 0x34) = 0xf778;
      }
      else {
        *(undefined2 *)(iVar5 + 0x34) = 0xff4a;
      }
    }
    if (*(char *)(param_9 + 0x11) == '\0') {
      *(short *)(iVar5 + 0x34) = *(short *)(iVar5 + 0x34) / 2;
      *(short *)(iVar5 + 0x36) = *(short *)(iVar5 + 0x36) / 2;
    }
    pfVar4 = (float *)(int)*(short *)(&DAT_80434670 + *(int *)(iVar5 + 0x38) * 2);
    zz_0006fb4_(dVar9,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                *(int *)(iVar6 + 0xe0),(int)pfVar4,param_12,param_13,param_14,param_15,param_16);
    uVar10 = zz_00086b8_(dVar13,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                         *(int *)(iVar6 + 0xe0),pfVar4,param_12,param_13,param_14,param_15,param_16)
    ;
    dVar9 = (double)zz_0007c30_(uVar10,dVar11,param_3,param_4,param_5,param_6,param_7,param_8,
                                *(int *)(iVar6 + 0xe0),extraout_r4,pfVar4,param_12,param_13,param_14
                                ,param_15,param_16);
    iVar7 = iVar7 + 0x3c;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 8013fa70  zz_013fa70_ ====

/* WARNING: Removing unreachable block (ram,0x8013fb34) */
/* WARNING: Removing unreachable block (ram,0x8013fa80) */

void zz_013fa70_(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                float *param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  uint uVar1;
  int iVar2;
  undefined4 extraout_r4;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  
  uVar1 = countLeadingZeros((int)*(char *)(param_9 + 0x11));
  dVar7 = (double)*(float *)(param_9 + 0xd4);
  iVar4 = 0;
  dVar8 = (double)(float)(dVar7 + (double)(float)((double)CONCAT44(0x43300000,
                                                                   uVar1 >> 4 & 0xffffffe ^
                                                                   0x80000000) - DOUBLE_8043a168));
  iVar5 = param_9;
  for (iVar3 = 0; iVar3 < *(char *)(param_9 + 0x13); iVar3 = iVar3 + 1) {
    iVar2 = *(int *)(param_9 + 0x54) + iVar4;
    *(short *)(iVar2 + 0x30) = *(short *)(iVar2 + 0x30) + *(short *)(iVar2 + 0x34);
    *(short *)(iVar2 + 0x32) = *(short *)(iVar2 + 0x32) + *(short *)(iVar2 + 0x36);
    uVar6 = zz_00086b8_(dVar8,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,DAT_803bb374,
                        *(int *)(iVar5 + 0xe0),param_11,param_12,param_13,param_14,param_15,param_16
                       );
    zz_0007c30_(uVar6,dVar7,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar5 + 0xe0),
                extraout_r4,param_11,param_12,param_13,param_14,param_15,param_16);
    iVar4 = iVar4 + 0x3c;
    iVar5 = iVar5 + 4;
  }
  return;
}



// ==== 8013fb50  zz_013fb50_ ====

void zz_013fb50_(int param_1,byte param_2)

{
  float fVar1;
  undefined1 *puVar2;
  
  puVar2 = zz_0088aa0_(param_1,3,8,0,2);
  if (puVar2 != (undefined1 *)0x0) {
    *puVar2 = 1;
    puVar2[0x10] = 0x51;
    puVar2[0x11] = param_2;
    *(code **)(puVar2 + 0xc) = FUN_8013fc98;
    *(code **)(puVar2 + 0x10c) = FUN_8014035c;
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
    gnt4_PSQUATScale_bl((double)*(float *)(puVar2 + 0xb4),
                        (float *)((uint)param_2 * 0x38 + -0x7fcc53f0),(float *)(puVar2 + 0x144));
    fVar1 = FLOAT_8043a170;
    *(float *)(puVar2 + 0x60) = FLOAT_8043a170;
    *(float *)(puVar2 + 0x5c) = fVar1;
    *(float *)(puVar2 + 0x58) = fVar1;
    zz_00f036c_(param_1,6);
  }
  return;
}



// ==== 8013fc98  FUN_8013fc98 ====

void FUN_8013fc98(int param_1)

{
  zz_0084000_(param_1);
  (*(code *)(&PTR_FUN_8033addc)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 8013fce8  FUN_8013fce8 ====

void FUN_8013fce8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  undefined8 uVar7;
  
  iVar6 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar5 = (uint)*(byte *)(param_9 + 0x11) * 0x38;
  *(code **)(param_9 + 0x100) = zz_0048288_;
  iVar4 = iVar5;
  zz_0089100_(param_9,0,1);
  *(undefined1 *)(param_9 + 0x84) = 0x10;
  *(undefined1 *)(param_9 + 0x98) = 5;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar6 + (char)(&DAT_8033abf2)[iVar5] * 0x30 + 0x8d4),
             (float *)(iVar5 + -0x7fcc540c),(float *)(param_9 + 0x20));
  *(undefined4 *)(param_9 + 0x38) =
       *(undefined4 *)
        (iVar6 + (char)(&DAT_8033abf2)[iVar5] * 0x30 + (char)(&DAT_8033ac1c)[iVar5] * 4 + 0x8d4);
  *(undefined4 *)(param_9 + 0x3c) =
       *(undefined4 *)
        (iVar6 + (char)(&DAT_8033abf2)[iVar5] * 0x30 + (char)(&DAT_8033ac1c)[iVar5] * 4 + 0x8e4);
  *(undefined4 *)(param_9 + 0x40) =
       *(undefined4 *)
        (iVar6 + (char)(&DAT_8033abf2)[iVar5] * 0x30 + (char)(&DAT_8033ac1c)[iVar5] * 4 + 0x8f4);
  if ((&DAT_8033ac1d)[iVar5] == '\x01') {
    gnt4_PSQUATScale_bl((double)FLOAT_8043a174,(float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  }
  if (*(int *)(iVar6 + 200) != 0) {
    zz_0083d60_(param_9,iVar6,(int)(char)(&DAT_8033abf2)[iVar5]);
  }
  uVar7 = zz_006ebb4_((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
  *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8033ac00 + iVar5);
  *(char *)(param_9 + 0x1cb) = (char)*(undefined4 *)(&DAT_8033ac04 + iVar5);
  *(undefined4 *)(param_9 + 0x9c) =
       *(undefined4 *)(iVar6 + (char)(&DAT_8033abf2)[iVar5] * 0x30 + 0x8d8);
  *(undefined4 *)(param_9 + 0xa0) =
       *(undefined4 *)(iVar6 + (char)(&DAT_8033abf2)[iVar5] * 0x30 + 0x8e8);
  *(undefined4 *)(param_9 + 0xa4) =
       *(undefined4 *)(iVar6 + (char)(&DAT_8033abf2)[iVar5] * 0x30 + 0x8f8);
  *(undefined2 *)(param_9 + 0x1c) = 300;
  iVar6 = zz_008ac80_(param_9,(int)(char)(&DAT_8033abf3)[iVar5]);
  if (iVar6 == 0) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    iVar6 = zz_0006f78_(param_9);
    uVar7 = zz_000726c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                        *(int *)(param_9 + 0xe0),(float *)(uint)(byte)(&DAT_8033abf0)[iVar5],
                        (int)*(char *)(param_9 + 0x88),iVar4,in_r8,in_r9,in_r10);
    *(undefined4 *)(param_9 + 0x158) = *(undefined4 *)(param_9 + 0x20);
    *(undefined4 *)(param_9 + 0x15c) = *(undefined4 *)(param_9 + 0x24);
    *(undefined4 *)(param_9 + 0x160) = *(undefined4 *)(param_9 + 0x28);
    *(undefined4 *)(param_9 + 0x164) = *(undefined4 *)(param_9 + 0x38);
    *(undefined4 *)(param_9 + 0x168) = *(undefined4 *)(param_9 + 0x3c);
    *(undefined4 *)(param_9 + 0x16c) = *(undefined4 *)(param_9 + 0x40);
    *(undefined4 *)(param_9 + 0x170) = *(undefined4 *)(param_9 + 0x9c);
    *(undefined4 *)(param_9 + 0x174) = *(undefined4 *)(param_9 + 0xa0);
    *(undefined4 *)(param_9 + 0x178) = *(undefined4 *)(param_9 + 0xa4);
    *(undefined4 *)(param_9 + 0x17c) = *(undefined4 *)(param_9 + 0xb4);
    iVar6 = zz_0006f78_(param_9);
    zz_000726c_(uVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar6,
                *(int *)(param_9 + 0xe4),(float *)(uint)(byte)(&DAT_8033abf1)[iVar5],
                (int)*(char *)(param_9 + 0x88),iVar4,in_r8,in_r9,in_r10);
    *(undefined1 *)(param_9 + 0x82) = 1;
  }
  *(float *)(param_9 + 0x180) = FLOAT_8043a178;
  *(undefined4 *)(param_9 + 0x184) = *(undefined4 *)(&DAT_8033ac24 + iVar5);
  uVar3 = zz_00055fc_();
  iVar4 = (uVar3 & 7) * 0xc;
  uVar2 = *(undefined4 *)(&DAT_8033ad80 + iVar4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(&DAT_8033ad7c + iVar4);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(&DAT_8033ad84 + iVar4);
  uVar3 = zz_00055fc_();
  *(short *)(param_9 + 0x74) = (short)(uVar3 << 0xb);
  fVar1 = FLOAT_8043a178;
  *(undefined **)(param_9 + 0x150) = &DAT_8033ad40;
  *(float *)(param_9 + 0x154) = fVar1;
  zz_014025c_(param_9);
  return;
}



// ==== 8013ffcc  FUN_8013ffcc ====

void FUN_8013ffcc(int param_1)

{
  float fVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 auStack_2c [3];
  float local_20;
  undefined4 local_1c;
  undefined4 local_18;
  
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  zz_014025c_(param_1);
  if (FLOAT_8043a178 < *(float *)(param_1 + 0x17c)) {
    *(float *)(param_1 + 0x17c) = *(float *)(param_1 + 0x17c) - FLOAT_8043a17c;
  }
  fVar1 = FLOAT_8043a170;
  *(float *)(param_1 + 0x180) = *(float *)(param_1 + 0x180) + FLOAT_8043a180;
  if (fVar1 < *(float *)(param_1 + 0x180)) {
    *(float *)(param_1 + 0x180) = fVar1;
  }
  if (*(short *)(param_1 + 0x1c) < 1) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
  }
  else {
    *(undefined4 *)(param_1 + 0x9c) = *(undefined4 *)(param_1 + 0x118);
    *(undefined4 *)(param_1 + 0xa0) = *(undefined4 *)(param_1 + 0x128);
    *(undefined4 *)(param_1 + 0xa4) = *(undefined4 *)(param_1 + 0x138);
    iVar3 = zz_0083244_((float *)(param_1 + 0x20));
    if (iVar3 == 0) {
      if (*(char *)(param_1 + 0x1d9) == '\0') {
        iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x38;
        FUN_80083874((double)*(float *)(&DAT_8033ac0c + iVar3),param_1);
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) + *(float *)(&DAT_8033ac20 + iVar3);
        if (*(float *)(param_1 + 0x184) < *(float *)(param_1 + 0x44)) {
          *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x184);
        }
        FUN_80083ad4((double)*(float *)(&DAT_8033ac08 + iVar3),param_1,
                     (char)*(undefined4 *)(&DAT_8033ac04 + iVar3));
        uVar5 = *(undefined4 *)(param_1 + 0x58);
        uVar4 = *(undefined4 *)(param_1 + 0x5c);
        uVar2 = *(undefined4 *)(param_1 + 0x60);
        zz_00833ec_(param_1);
        *(undefined4 *)(param_1 + 0x58) = uVar5;
        *(undefined4 *)(param_1 + 0x5c) = uVar4;
        *(undefined4 *)(param_1 + 0x60) = uVar2;
        gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(iVar3 + -0x7fcc53f0),
                            (float *)(param_1 + 0x144));
        zz_0083610_(param_1,(float *)(param_1 + 0x184));
        iVar3 = zz_0083714_(param_1);
        if (iVar3 == 0) {
          iVar3 = zz_003ecb8_((float *)(param_1 + 0x20),(float *)(param_1 + 0x2c),&local_20,
                              auStack_2c);
          if (iVar3 != 0) {
            *(float *)(param_1 + 0x20) = local_20;
            *(undefined4 *)(param_1 + 0x24) = local_1c;
            *(undefined4 *)(param_1 + 0x28) = local_18;
            FUN_8001b9ac((double)*(float *)(param_1 + 0xb4),&local_20,auStack_2c);
            zz_0019550_(param_1,&local_20,0);
            *(undefined1 *)(param_1 + 0x18) = 2;
          }
        }
        else {
          *(undefined1 *)(param_1 + 0x18) = 2;
          zz_008aff0_(param_1);
        }
      }
      else {
        *(undefined1 *)(param_1 + 0x18) = 2;
        zz_008aff0_(param_1);
      }
    }
    else {
      *(undefined1 *)(param_1 + 0x18) = 2;
      zz_008aff0_(param_1);
    }
  }
  return;
}



// ==== 80140200  FUN_80140200 ====

void FUN_80140200(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 8014023c  FUN_8014023c ====

void FUN_8014023c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8014025c  zz_014025c_ ====

void zz_014025c_(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  float *pfVar5;
  float *pfVar6;
  
  pfVar6 = *(float **)(param_1 + 0x150);
  if (pfVar6 == (float *)0x0) {
    return;
  }
LAB_801402bc:
  do {
    fVar1 = *pfVar6;
    pfVar5 = (float *)0x0;
    if (*(float *)(param_1 + 0x154) < fVar1) {
LAB_801402d0:
      fVar1 = FLOAT_8043a170;
      if (pfVar5 == (float *)0x0) {
        pfVar5 = pfVar6 + -5;
      }
      fVar2 = *pfVar6 - *pfVar5;
      fVar3 = *(float *)(param_1 + 0x154) - *pfVar5;
      *(float *)(param_1 + 0x58) = fVar3 * ((pfVar6[1] - pfVar5[1]) / fVar2) + pfVar5[1];
      *(float *)(param_1 + 0x5c) = fVar3 * ((pfVar6[2] - pfVar5[2]) / fVar2) + pfVar5[2];
      *(float *)(param_1 + 0x60) = fVar3 * ((pfVar6[3] - pfVar5[3]) / fVar2) + pfVar5[3];
      *(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x154) + fVar1;
      if (pfVar5 != pfVar6) {
        return;
      }
      *(undefined4 *)(param_1 + 0x150) = 0;
      return;
    }
    if (((uint)pfVar6[4] & 0xf0000000) != 0) {
      uVar4 = (uint)pfVar6[4] & 0xff;
      if (uVar4 == 0) {
        *(float *)(param_1 + 0x154) = fVar1;
        pfVar5 = pfVar6;
        goto LAB_801402d0;
      }
      pfVar6 = pfVar6 + uVar4 * -5;
      *(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x154) - fVar1;
      *(float *)(param_1 + 0x154) = *(float *)(param_1 + 0x154) + *pfVar6;
      goto LAB_801402bc;
    }
    pfVar6 = pfVar6 + 5;
  } while( true );
}



// ==== 8014035c  FUN_8014035c ====

void FUN_8014035c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  bool bVar1;
  float *pfVar2;
  int iVar3;
  undefined8 uVar4;
  double dVar5;
  double dVar6;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float local_78;
  float local_74;
  float local_70;
  float afStack_6c [12];
  float afStack_3c [3];
  undefined4 local_30;
  undefined4 local_20;
  undefined4 local_10;
  
  gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x180),(float *)(param_1 + 0x144),&local_78);
  dVar5 = (double)local_74;
  dVar6 = (double)local_70;
  gnt4_PSMTXScale_bl((double)local_78,dVar5,dVar6,afStack_3c);
  pfVar2 = afStack_3c;
  uVar4 = gnt4_PSMTXConcat_bl((float *)(param_1 + 0x114),pfVar2,pfVar2);
  zz_00076d0_(uVar4,dVar5,dVar6,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe0),afStack_3c,
              (undefined *)pfVar2,param_4,param_5,param_6,param_7,param_8);
  zz_00097b4_(*(int *)(param_1 + 0xe0),0x44);
  if (FLOAT_8043a178 < *(float *)(param_1 + 0x17c)) {
    iVar3 = param_1 + 0x170;
    bVar1 = zz_0045ef4_(afStack_3c,5,param_1 + 0x164,iVar3);
    if (!bVar1) {
      local_30 = *(undefined4 *)(param_1 + 0x158);
      local_20 = *(undefined4 *)(param_1 + 0x15c);
      local_10 = *(undefined4 *)(param_1 + 0x160);
      dVar6 = (double)*(float *)(param_1 + 0x17c);
      dVar5 = dVar6;
      gnt4_PSMTXScale_bl(dVar6,dVar6,dVar6,afStack_6c);
      pfVar2 = afStack_3c;
      uVar4 = gnt4_PSMTXConcat_bl(pfVar2,afStack_6c,pfVar2);
      zz_00076d0_(uVar4,dVar6,dVar5,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(param_1 + 0xe4),
                  afStack_3c,(undefined *)pfVar2,iVar3,param_5,param_6,param_7,param_8);
      zz_00097b4_(*(int *)(param_1 + 0xe4),0x44);
    }
  }
  return;
}



// ==== 80140450  zz_0140450_ ====

void zz_0140450_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,0x20,0,4);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x42;
    puVar1[0x11] = param_2;
    puVar1[0x13] = 4;
    puVar1[0x146] = 0x20;
    *(code **)(puVar1 + 0xc) = FUN_80140560;
    *(code **)(puVar1 + 0x10c) = FUN_80140da0;
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



// ==== 80140560  FUN_80140560 ====

void FUN_80140560(int param_1)

{
  zz_00840b8_(param_1);
  (*(code *)(&PTR_FUN_8033aef4)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801405b0  FUN_801405b0 ====

void FUN_801405b0(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,int param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  undefined4 extraout_r4;
  undefined4 uVar7;
  int iVar8;
  double dVar9;
  undefined8 uVar10;
  
  iVar6 = (uint)*(byte *)(param_9 + 0x11) * 0x14;
  iVar4 = -((int)*(short *)(&DAT_8033adf0 + iVar6) >> 0x1f);
  if (iVar4 == 0) {
    iVar4 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8033adf0 + iVar6));
  }
  *(short *)(param_9 + 0x144) = (*(char *)(param_9 + 0x13) + -1) * 0x34;
  uVar3 = (int)*(short *)(param_9 + 0x144) + *(char *)(param_9 + 0x146) * 0x18 + 0x1f;
  piVar5 = zz_0006dc8_((((int)uVar3 >> 5) + (uint)((int)uVar3 < 0 && (uVar3 & 0x1f) != 0)) * 0x20);
  *(int **)(param_9 + 0xdc) = piVar5;
  fVar1 = FLOAT_8043a188;
  if (iVar4 == 0 && -1 < (int)(-(int)piVar5 | (uint)piVar5)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
    zz_008aff0_(param_9);
    *(undefined1 *)(param_9 + 0x82) = 0;
  }
  else {
    iVar4 = *(int *)(param_9 + 0xcc);
    iVar8 = *(int *)(param_9 + 0x90);
    *(undefined1 *)(param_9 + 0x18) = 1;
    *(undefined2 *)(param_9 + 0x1e) = 0;
    *(undefined2 *)(param_9 + 0x1c4) = *(undefined2 *)(&DAT_8033adf2 + iVar6);
    *(short *)(param_9 + 0x1c) = (short)*(undefined4 *)(&DAT_8033adf4 + iVar6);
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8033adf8 + iVar6);
    *(undefined4 *)(param_9 + 0x48) = *(undefined4 *)(&DAT_8033adfc + iVar6);
    *(undefined4 *)(param_9 + 0x4c) = *(undefined4 *)(&DAT_8033ae00 + iVar6);
    *(float *)(param_9 + 0x204) = fVar1;
    *(undefined2 *)(param_9 + 0x1c8) = *(undefined2 *)(param_9 + 0x1c4);
    *(undefined2 *)(param_9 + 0x1c6) = *(undefined2 *)(param_9 + 0x1c4);
    fVar2 = FLOAT_8043a190;
    fVar1 = FLOAT_8043a18c;
    if ((iVar4 == 0) || ((*(byte *)(param_9 + 0xd0) & 4) == 0)) {
      *(float *)(param_9 + 0x20) = FLOAT_8043a18c;
      *(float *)(param_9 + 0x24) = fVar1;
      *(float *)(param_9 + 0x28) = fVar2;
      gnt4_PSMTXMultVec_bl
                ((float *)(iVar8 + 0x8d4),(float *)(param_9 + 0x20),(float *)(param_9 + 0x20));
      *(undefined4 *)(param_9 + 0x24) = *(undefined4 *)(iVar8 + 0x24);
    }
    else {
      uVar7 = *(undefined4 *)(iVar4 + 0x24);
      *(undefined4 *)(param_9 + 0x20) = *(undefined4 *)(iVar4 + 0x20);
      *(undefined4 *)(param_9 + 0x24) = uVar7;
      *(undefined4 *)(param_9 + 0x28) = *(undefined4 *)(iVar4 + 0x28);
    }
    *(undefined4 *)(param_9 + 0x2c) = *(undefined4 *)(param_9 + 0x20);
    *(undefined4 *)(param_9 + 0x30) = *(undefined4 *)(param_9 + 0x24);
    *(undefined4 *)(param_9 + 0x34) = *(undefined4 *)(param_9 + 0x28);
    dVar9 = FUN_8003d964((double)*(float *)(DAT_8043625c + 0x34),param_9,(float *)(param_9 + 0x20));
    *(float *)(param_9 + 0xd4) = (float)((double)FLOAT_8043a194 + dVar9);
    dVar9 = FUN_8003dd34((float *)(param_9 + 0x20));
    *(float *)(param_9 + 0xd8) = (float)dVar9;
    *(float *)(param_9 + 0x24) = (float)dVar9;
    uVar7 = 1;
    *(code **)(param_9 + 0x100) = FUN_80140b6c;
    uVar10 = zz_0089100_(param_9,1,1);
    zz_0140e34_(uVar10,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
                uVar7,param_12,param_13,param_14,param_15,param_16);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    zz_00f036c_(param_9,0xae);
  }
  return;
}



// ==== 801407b8  FUN_801407b8 ====

void FUN_801407b8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  short sVar1;
  undefined4 extraout_r4;
  undefined4 extraout_r4_00;
  undefined4 uVar2;
  undefined8 uVar3;
  
  uVar3 = (*(code *)(&PTR_FUN_8033af04)[*(char *)(param_9 + 0x19)])();
  sVar1 = *(short *)(param_9 + 0x1e) + -1;
  *(short *)(param_9 + 0x1e) = sVar1;
  uVar2 = extraout_r4;
  if (sVar1 < 1) {
    *(undefined2 *)(param_9 + 0x1e) = 10;
    uVar3 = zz_0141060_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
    uVar2 = extraout_r4_00;
  }
  zz_014118c_(uVar3,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,uVar2,param_11,
              param_12,param_13,param_14,param_15,param_16);
  return;
}



// ==== 8014082c  FUN_8014082c ====

void FUN_8014082c(int param_1)

{
  byte bVar1;
  float fVar2;
  bool bVar3;
  
  bVar3 = false;
  bVar1 = *(byte *)(param_1 + 0x1dc);
  if (bVar1 != 0) {
    if (((bVar1 & *(byte *)(DAT_803c4e84 + 0x3e5)) == 0) ||
       ((*(byte *)(DAT_803c4e84 + 0x274) & 2) == 0)) {
      if (((bVar1 & *(byte *)(DAT_803c4e84 + 0x21e5)) == 0) ||
         ((*(byte *)(DAT_803c4e84 + 0x2074) & 2) == 0)) {
        if (((bVar1 & *(byte *)(DAT_803c4e84 + 0x3fe5)) == 0) ||
           ((*(byte *)(DAT_803c4e84 + 0x3e74) & 2) == 0)) {
          if (((bVar1 & *(byte *)(DAT_803c4e84 + 0x5de5)) == 0) ||
             ((*(byte *)(DAT_803c4e84 + 0x5c74) & 2) == 0)) {
            if (((bVar1 & *(byte *)(DAT_803c4e84 + 0x7be5)) == 0) ||
               ((*(byte *)(DAT_803c4e84 + 0x7a74) & 2) == 0)) {
              if (((bVar1 & *(byte *)(DAT_803c4e84 + 0x99e5)) != 0) &&
                 ((*(byte *)(DAT_803c4e84 + 0x9874) & 2) != 0)) {
                bVar3 = true;
                *(undefined2 *)(param_1 + 0x1c) = 1;
              }
            }
            else {
              bVar3 = true;
              *(undefined2 *)(param_1 + 0x1c) = 1;
            }
          }
          else {
            bVar3 = true;
            *(undefined2 *)(param_1 + 0x1c) = 1;
          }
        }
        else {
          bVar3 = true;
          *(undefined2 *)(param_1 + 0x1c) = 1;
        }
      }
      else {
        bVar3 = true;
        *(undefined2 *)(param_1 + 0x1c) = 1;
      }
    }
    else {
      bVar3 = true;
      *(undefined2 *)(param_1 + 0x1c) = 1;
    }
  }
  if (!bVar3) {
    if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x48)) {
      fVar2 = *(float *)(param_1 + 0x44) + *(float *)(param_1 + 0x4c);
      *(float *)(param_1 + 0x44) = fVar2;
      if (*(float *)(param_1 + 0x48) < fVar2) {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x48);
      }
    }
    fVar2 = *(float *)(param_1 + 0x24) + *(float *)(param_1 + 0x44);
    *(float *)(param_1 + 0x24) = fVar2;
    if (*(float *)(param_1 + 0xd4) <= fVar2) {
      *(undefined1 *)(param_1 + 0x19) = 1;
      *(undefined4 *)(param_1 + 0x24) = *(undefined4 *)(param_1 + 0xd4);
    }
  }
  zz_01409d8_(param_1);
  return;
}



// ==== 801409d8  zz_01409d8_ ====

void zz_01409d8_(int param_1)

{
  *(short *)(param_1 + 0x1c) = *(short *)(param_1 + 0x1c) + -1;
  if (0 < *(short *)(param_1 + 0x1c)) {
    if (0 < *(short *)(param_1 + 0x1c6)) {
      if (*(char *)(param_1 + 0x1da) != '\0') {
        *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0xc0c0c0ff;
        return;
      }
      *(undefined4 *)(*(int *)(param_1 + 0xe0) + 0x18) = 0xff;
      return;
    }
  }
  *(undefined1 *)(param_1 + 0x19) = 2;
  *(undefined2 *)(param_1 + 0x1c) = 8;
  return;
}



// ==== 80140a40  FUN_80140a40 ====

void FUN_80140a40(int param_1)

{
  short sVar1;
  uint uVar2;
  
  uVar2 = *(byte *)(*(int *)(param_1 + 0xe0) + 0x18) + 0x20;
  if (0xff < uVar2) {
    uVar2 = 0xff;
  }
  *(char *)(*(int *)(param_1 + 0xe0) + 0x18) = (char)uVar2;
  uVar2 = *(byte *)(*(int *)(param_1 + 0xe0) + 0x19) + 0x20;
  if (0xff < uVar2) {
    uVar2 = 0xff;
  }
  *(char *)(*(int *)(param_1 + 0xe0) + 0x19) = (char)uVar2;
  uVar2 = *(byte *)(*(int *)(param_1 + 0xe0) + 0x1a) + 0x20;
  if (0xff < uVar2) {
    uVar2 = 0xff;
  }
  *(char *)(*(int *)(param_1 + 0xe0) + 0x1a) = (char)uVar2;
  uVar2 = *(byte *)(*(int *)(param_1 + 0xe0) + 0x1b) + 0x20;
  if (0xff < uVar2) {
    uVar2 = 0xff;
  }
  *(char *)(*(int *)(param_1 + 0xe0) + 0x1b) = (char)uVar2;
  sVar1 = *(short *)(param_1 + 0x1c) + -1;
  *(short *)(param_1 + 0x1c) = sVar1;
  if (sVar1 < 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    zz_01a55e0_(param_1,0);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  return;
}



// ==== 80140b24  FUN_80140b24 ====

void FUN_80140b24(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80140b6c  FUN_80140b6c ====

/* WARNING: Removing unreachable block (ram,0x80140d24) */

void FUN_80140b6c(int param_1)

{
  bool bVar1;
  int iVar2;
  uint uVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  float *pfVar6;
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
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [14];
  
  iVar7 = 0;
  iVar2 = param_1;
  for (iVar8 = 0; iVar8 < *(char *)(param_1 + 0x13) + -1; iVar8 = iVar8 + 1) {
    if (((int)*(char *)(param_1 + 0x147) & 1 << iVar8) != 0) {
      iVar5 = *(int *)(*(int *)(param_1 + 0xdc) + 0xc) + iVar7;
      gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0xb4),(float *)(iVar5 + 0x1c),&local_58);
      dVar10 = (double)*(float *)(iVar5 + 0x14);
      dVar11 = (double)*(float *)(iVar5 + 0x18);
      gnt4_PSMTXTrans_bl((double)*(float *)(iVar5 + 0x10),dVar10,dVar11,afStack_4c);
      iVar4 = (int)*(short *)(iVar5 + 0x30);
      zz_00457d4_('y',afStack_4c,afStack_4c,*(short *)(iVar5 + 0x30));
      pfVar6 = &local_58;
      uVar9 = zz_00456a0_(afStack_4c,afStack_4c,pfVar6);
      zz_00076d0_(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,*(int *)(iVar2 + 0xe0),
                  afStack_4c,(undefined *)pfVar6,iVar4,in_r7,in_r8,in_r9,in_r10);
      if (iVar8 == 0) {
        gnt4_PSMTXCopy_bl(afStack_4c,(float *)(param_1 + 0x114));
      }
    }
    iVar7 = iVar7 + 0x34;
    iVar2 = iVar2 + 4;
  }
  if (*(int *)(param_1 + 0x148) != 0) {
    iVar7 = 0;
    iVar2 = *(int *)(*(int *)(param_1 + *(char *)(param_1 + 0x13) * 4 + 0xdc) + 0xc);
    if (iVar2 == 0) {
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(iVar2 + 0x10);
    }
    iVar8 = 0;
    while (iVar7 < *(char *)(param_1 + 0x146)) {
      if ((*(uint *)(param_1 + 0x148) & 1 << iVar7) != 0) {
        local_58 = *(float *)(param_1 + 0xb4);
        pfVar6 = (float *)(*(int *)(*(int *)(param_1 + 0xdc) + 0xc) +
                          *(short *)(param_1 + 0x144) + iVar8);
        dVar10 = (double)pfVar6[1];
        dVar11 = (double)pfVar6[2];
        local_54 = local_58;
        local_50 = local_58;
        gnt4_PSMTXTrans_bl((double)*pfVar6,dVar10,dVar11,afStack_4c);
        iVar4 = (int)*(short *)(pfVar6 + 5);
        zz_00457d4_('y',afStack_4c,afStack_4c,*(short *)(pfVar6 + 5));
        pfVar6 = &local_58;
        uVar9 = zz_00456a0_(afStack_4c,afStack_4c,pfVar6);
        if (iVar2 == 0) {
          pfVar6 = (float *)&DAT_8043a1a0;
          gnt4___assert_bl(uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,&DAT_8043a198,0x495,
                           &DAT_8043a1a0,iVar4,in_r7,in_r8,in_r9,in_r10);
        }
        uVar9 = gnt4_PSMTXCopy_bl(afStack_4c,(float *)(iVar2 + 0x44));
        *(uint *)(iVar2 + 0x14) = *(uint *)(iVar2 + 0x14) | 0x3800000;
        if (iVar2 != 0) {
          uVar3 = *(uint *)(iVar2 + 0x14);
          bVar1 = false;
          if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
            bVar1 = true;
          }
          if (!bVar1) {
            gnt4_HSD_JObjSetMtxDirtySub_bl
                      (uVar9,dVar10,dVar11,in_f4,in_f5,in_f6,in_f7,in_f8,iVar2,uVar3,
                       (undefined *)pfVar6,iVar4,in_r7,in_r8,in_r9,in_r10);
          }
        }
      }
      iVar8 = iVar8 + 0x18;
      iVar7 = iVar7 + 1;
      if (iVar2 == 0) {
        iVar2 = 0;
      }
      else {
        iVar2 = *(int *)(iVar2 + 8);
      }
    }
  }
  return;
}



// ==== 80140da0  FUN_80140da0 ====

void FUN_80140da0(int param_1)

{
  uint uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = param_1;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    if (iVar2 == *(char *)(param_1 + 0x13) + -1) {
      uVar1 = *(uint *)(param_1 + 0x148);
    }
    else {
      uVar1 = (int)*(char *)(param_1 + 0x147) & 1 << iVar2;
    }
    if (uVar1 != 0) {
      zz_00097b4_(*(int *)(iVar3 + 0xe0),(int)*(char *)(param_1 + iVar2 + 0x14c));
    }
    iVar3 = iVar3 + 4;
  }
  return;
}



// ==== 80140e34  zz_0140e34_ ====

void zz_0140e34_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,int param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  undefined2 uVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  int iVar6;
  int *piVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  char *pcVar11;
  undefined8 uVar12;
  
  iVar10 = 0;
  pcVar11 = &DAT_8033aec4;
  *(undefined4 *)(param_9 + 0x148) = 0;
  *(undefined1 *)(param_9 + 0x147) = 0;
  iVar9 = param_9;
  for (iVar8 = 0; iVar8 < *(char *)(param_9 + 0x13); iVar8 = iVar8 + 1) {
    *(char *)(param_9 + iVar8 + 0x14c) = pcVar11[1];
    if (iVar8 == *(char *)(param_9 + 0x13) + -1) {
      iVar4 = zz_0006f78_(*(int *)(param_9 + 0x90));
      pcVar5 = (char *)(int)*pcVar11;
      param_12 = (int)*(char *)(param_9 + 0x146);
      param_1 = zz_0007198_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                            *(int *)(iVar9 + 0xe0),pcVar5,param_12,param_13,param_14,param_15,
                            param_16);
      iVar6 = 0;
      iVar4 = *(int *)(*(int *)(iVar9 + 0xe0) + 0xc);
      if (iVar4 == 0) {
        iVar4 = 0;
      }
      else {
        iVar4 = *(int *)(iVar4 + 0x10);
      }
      while (iVar6 < *(char *)(param_9 + 0x146)) {
        param_1 = gnt4_HSD_JObjSetFlagsAll
                            (param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                             0x10,pcVar5,param_12,param_13,param_14,param_15,param_16);
        iVar6 = iVar6 + 1;
        if (iVar4 == 0) {
          iVar4 = 0;
        }
        else {
          iVar4 = *(int *)(iVar4 + 8);
        }
      }
    }
    else {
      iVar4 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc);
      *(byte *)(param_9 + 0x147) = *(byte *)(param_9 + 0x147) | (byte)(1 << iVar8);
      piVar7 = (int *)(iVar4 + iVar10);
      iVar4 = *(int *)(param_9 + 0x24);
      piVar7[4] = *(int *)(param_9 + 0x20);
      piVar7[5] = iVar4;
      piVar7[6] = *(int *)(param_9 + 0x28);
      if (iVar8 == 0) {
        *(undefined2 *)((int)piVar7 + 0x32) = 0;
        fVar1 = FLOAT_8043a1a8;
        *(undefined2 *)(piVar7 + 0xc) = 0;
        *(undefined2 *)((int)piVar7 + 0x32) = 0x200;
        piVar7[7] = (int)fVar1;
        piVar7[8] = (int)fVar1;
        piVar7[9] = (int)fVar1;
        *(undefined4 *)(*(int *)(iVar9 + 0xe0) + 0x18) = 0;
        iVar4 = zz_0006f78_(*(int *)(param_9 + 0x90));
        param_12 = 0;
        param_1 = zz_0007030_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                              *(int *)(iVar9 + 0xe0),(int)*pcVar11,0,param_13,param_14,param_15,
                              param_16);
      }
      else {
        if (iVar8 == 2) {
          piVar7[5] = (int)((float)piVar7[5] - FLOAT_8043a1ac);
        }
        *(undefined2 *)(piVar7 + 0xb) = 0;
        *(undefined2 *)((int)piVar7 + 0x2e) = *(undefined2 *)(pcVar11 + 2);
        uVar3 = zz_00055fc_();
        *(short *)(piVar7 + 0xc) = (short)(uVar3 << 8);
        if (iVar8 == 1) {
          uVar2 = 0;
        }
        else {
          uVar2 = (undefined2)(0x10000 / (int)*(short *)((int)piVar7 + 0x2e));
        }
        *(undefined2 *)((int)piVar7 + 0x32) = uVar2;
        zz_0018f88_(piVar7,*(int *)(pcVar11 + 4),(float *)(piVar7 + 7));
        uVar12 = zz_0019338_(piVar7 + 2,*(int *)(pcVar11 + 8),(float *)(piVar7 + 10));
        iVar4 = zz_0006f78_(*(int *)(param_9 + 0x90));
        zz_0006fb4_(uVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar4,
                    *(int *)(iVar9 + 0xe0),(int)*pcVar11,param_12,param_13,param_14,param_15,
                    param_16);
        param_1 = zz_0007cac_((double)(float)piVar7[10],*(int *)(iVar9 + 0xe0));
      }
    }
    pcVar11 = pcVar11 + 0xc;
    iVar10 = iVar10 + 0x34;
    iVar9 = iVar9 + 4;
  }
  return;
}



// ==== 80141060  zz_0141060_ ====

void zz_0141060_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  float fVar2;
  undefined4 uVar3;
  uint uVar4;
  int iVar5;
  undefined *puVar6;
  uint uVar7;
  uint uVar8;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar9;
  undefined4 *puVar10;
  int iVar11;
  double dVar12;
  
  iVar11 = 0;
  while( true ) {
    fVar1 = FLOAT_8043a18c;
    if (*(char *)(param_9 + 0x146) <= iVar11) break;
    uVar7 = *(uint *)(param_9 + 0x148);
    uVar8 = 1 << iVar11;
    if ((uVar7 & uVar8) == 0) {
      puVar6 = *(undefined **)(*(int *)(param_9 + 0xdc) + 0xc);
      dVar12 = (double)FLOAT_8043a18c;
      *(uint *)(param_9 + 0x148) = uVar7 | uVar8;
      fVar2 = FLOAT_8043a1b0;
      puVar10 = (undefined4 *)(puVar6 + (int)*(short *)(param_9 + 0x144) + iVar11 * 0x18);
      uVar3 = *(undefined4 *)(param_9 + 0x24);
      *puVar10 = *(undefined4 *)(param_9 + 0x20);
      puVar10[1] = uVar3;
      puVar10[2] = *(undefined4 *)(param_9 + 0x28);
      puVar10[3] = fVar1;
      puVar10[4] = fVar2;
      uVar4 = zz_00055fc_();
      iVar9 = 0;
      *(short *)(puVar10 + 5) = (short)(uVar4 << 8);
      iVar5 = *(int *)(*(int *)(param_9 + *(char *)(param_9 + 0x13) * 4 + 0xdc) + 0xc);
      if (iVar5 == 0) {
        iVar5 = 0;
      }
      else {
        iVar5 = *(int *)(iVar5 + 0x10);
      }
      while (iVar9 < iVar11) {
        dVar12 = (double)gnt4_HSD_JObjClearFlagsAll
                                   (dVar12,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                                    iVar5,0x10,puVar6,uVar7,uVar8,in_r8,in_r9,in_r10);
        iVar9 = iVar9 + 1;
        if (iVar5 == 0) {
          iVar5 = 0;
        }
        else {
          iVar5 = *(int *)(iVar5 + 8);
        }
      }
      iVar11 = (int)*(char *)(param_9 + 0x146);
    }
    iVar11 = iVar11 + 1;
  }
  return;
}



// ==== 8014118c  zz_014118c_ ====

uint zz_014118c_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  
  iVar7 = 0;
  iVar8 = 0;
  iVar3 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) + -1 <= iVar7) break;
    if (((int)*(char *)(param_9 + 0x147) & 1 << iVar7) != 0) {
      piVar6 = (int *)(*(int *)(*(int *)(param_9 + 0xdc) + 0xc) + iVar8);
      if (iVar7 == 0) {
        iVar4 = *(int *)(param_9 + 0x24);
        piVar6[4] = *(int *)(param_9 + 0x20);
        piVar6[5] = iVar4;
        piVar6[6] = *(int *)(param_9 + 0x28);
        *(short *)(piVar6 + 0xc) = *(short *)(piVar6 + 0xc) + *(short *)((int)piVar6 + 0x32);
      }
      else {
        sVar2 = *(short *)(piVar6 + 0xb);
        *(short *)(piVar6 + 0xb) = sVar2 + 1;
        if (*(short *)((int)piVar6 + 0x2e) <= (short)(sVar2 + 1)) {
          *(byte *)(param_9 + 0x147) = *(byte *)(param_9 + 0x147) & ~(byte)(1 << iVar7);
        }
        *(short *)(piVar6 + 0xc) = *(short *)(piVar6 + 0xc) + *(short *)((int)piVar6 + 0x32);
        zz_0018fd8_(piVar6,(int)*(short *)(piVar6 + 0xb),(float *)(piVar6 + 7));
        zz_0019370_(piVar6 + 2,(int)*(short *)(piVar6 + 0xb),(float *)(piVar6 + 10));
        zz_0007cac_((double)(float)piVar6[10],*(int *)(iVar3 + 0xe0));
      }
    }
    iVar8 = iVar8 + 0x34;
    iVar3 = iVar3 + 4;
    iVar7 = iVar7 + 1;
  }
  if (*(int *)(param_9 + 0x148) != 0) {
    iVar7 = 0;
    iVar3 = *(int *)(*(int *)(param_9 + *(char *)(param_9 + 0x13) * 4 + 0xdc) + 0xc);
    if (iVar3 == 0) {
      iVar3 = 0;
    }
    else {
      iVar3 = *(int *)(iVar3 + 0x10);
    }
    iVar8 = 0;
    while( true ) {
      if (*(char *)(param_9 + 0x146) <= iVar7) break;
      if ((*(uint *)(param_9 + 0x148) & 1 << iVar7) != 0) {
        iVar4 = *(int *)(*(int *)(param_9 + 0xdc) + 0xc) + *(short *)(param_9 + 0x144) + iVar8;
        *(float *)(iVar4 + 4) = *(float *)(iVar4 + 4) + *(float *)(iVar4 + 0xc);
        *(float *)(iVar4 + 0xc) = *(float *)(iVar4 + 0xc) + *(float *)(iVar4 + 0x10);
        fVar1 = *(float *)(iVar4 + 4);
        if ((double)fVar1 <= (double)*(float *)(param_9 + 0xd8)) {
          puVar5 = *(undefined **)(param_9 + 0x148);
          *(uint *)(param_9 + 0x148) = (uint)puVar5 & ~(1 << iVar7);
          gnt4_HSD_JObjSetFlagsAll
                    ((double)fVar1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                     0x10,puVar5,param_12,param_13,param_14,param_15,param_16);
        }
      }
      iVar8 = iVar8 + 0x18;
      iVar7 = iVar7 + 1;
      if (iVar3 == 0) {
        iVar3 = 0;
      }
      else {
        iVar3 = *(int *)(iVar3 + 8);
      }
    }
  }
  return (int)*(char *)(param_9 + 0x147) | *(uint *)(param_9 + 0x148);
}



// ==== 80141390  zz_0141390_ ====

bool zz_0141390_(int param_1)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,0);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x11] = 0;
    puVar1[0x10] = 0x44;
    *(code **)(puVar1 + 0xc) = FUN_80141490;
    *(undefined **)(puVar1 + 0x10c) = &DAT_80141a3c;
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



// ==== 80141490  FUN_80141490 ====

void FUN_80141490(int param_1)

{
  if ((*(char *)(param_1 + 0x18) < '\x02') &&
     (('\x01' < *(char *)(*(int *)(param_1 + 0x90) + 0x18) ||
      (*(short *)(*(int *)(param_1 + 0x90) + 1000) != *(short *)(param_1 + 0x94))))) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  (*(code *)(&PTR_FUN_8033af2c)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80141528  FUN_80141528 ====

void FUN_80141528(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x90);
  *(undefined1 *)(param_1 + 0x18) = 1;
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  *(undefined1 *)(param_1 + 0x84) = 0x1e;
  *(code **)(param_1 + 0x100) = FUN_80047aa4;
  zz_0089100_(param_1,0,1);
  fVar1 = FLOAT_8043a1b8;
  *(undefined1 *)(param_1 + 0x86) = 0;
  fVar2 = FLOAT_8043a1bc;
  *(float *)(param_1 + 0x144) = fVar1;
  *(float *)(param_1 + 0x148) = fVar2;
  *(float *)(param_1 + 0x14c) = fVar2;
  *(float *)(param_1 + 0x150) = fVar2;
  gnt4_PSMTXMultVec_bl
            ((float *)(iVar4 + (char)(&DAT_8033af12)[iVar3] * 0x30 + 0x8d4),
             (float *)(iVar3 + -0x7fcc50ec),(float *)(param_1 + 0x20));
  *(undefined4 *)(param_1 + 0x154) = *(undefined4 *)(param_1 + 0x20);
  *(undefined4 *)(param_1 + 0x158) = *(undefined4 *)(param_1 + 0x24);
  *(undefined4 *)(param_1 + 0x15c) = *(undefined4 *)(param_1 + 0x28);
  *(undefined1 *)(param_1 + 0x82) = 1;
  return;
}



// ==== 80141608  FUN_80141608 ====

void FUN_80141608(int param_1)

{
  char cVar1;
  float fVar2;
  int iVar3;
  int iVar4;
  float afStack_28 [7];
  
  fVar2 = FLOAT_8043a1b8;
  iVar4 = *(int *)(param_1 + 0x90);
  iVar3 = (uint)*(byte *)(param_1 + 0x11) * 0x1c;
  if ((*(uint *)(iVar4 + 0x5e0) & 0x2000000) == 0) {
    cVar1 = *(char *)(param_1 + 0x19);
    if (cVar1 == '\x01') {
      if ((*(char *)(iVar4 + 0x6cb) == '\0') && ('\0' < *(char *)(iVar4 + 0x6f2))) {
        *(char *)(iVar4 + 0x6f2) = *(char *)(iVar4 + 0x6f2) + -1;
      }
      else {
        *(undefined1 *)(param_1 + 0x19) = 2;
      }
    }
    else if (cVar1 < '\x01') {
      if (-1 < cVar1) {
        *(float *)(param_1 + 0x144) =
             *(float *)(param_1 + 0x144) + *(float *)(&DAT_8033af20 + iVar3);
        if (*(float *)(&DAT_8033af28 + iVar3) <= *(float *)(param_1 + 0x144)) {
          *(float *)(param_1 + 0x144) = *(float *)(&DAT_8033af28 + iVar3);
          *(undefined1 *)(param_1 + 0x19) = 1;
        }
        if (*(char *)(iVar4 + 0x6cb) != '\0') {
          *(undefined1 *)(param_1 + 0x19) = 2;
        }
      }
    }
    else if ((cVar1 < '\x03') &&
            (*(float *)(param_1 + 0x144) =
                  *(float *)(param_1 + 0x144) - *(float *)(&DAT_8033af24 + iVar3),
            *(float *)(param_1 + 0x144) <= fVar2)) {
      *(undefined1 *)(param_1 + 0x18) = 2;
      return;
    }
    *(undefined4 *)(param_1 + 0x150) = *(undefined4 *)(param_1 + 0x144);
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar4 + (char)(&DAT_8033af12)[iVar3] * 0x30 + 0x8d4),
               (float *)(iVar3 + -0x7fcc50ec),(float *)(param_1 + 0x20));
    gnt4_PSVECAdd_bl((float *)(iVar3 + -0x7fcc50ec),(float *)(param_1 + 0x148),afStack_28);
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar4 + (char)(&DAT_8033af12)[iVar3] * 0x30 + 0x8d4),afStack_28,
               (float *)(param_1 + 0x154));
    if (*(char *)(iVar4 + 0x6cb) == '\0') {
      zz_01417b0_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x18) = 2;
  }
  return;
}



// ==== 801417b0  zz_01417b0_ ====

void zz_01417b0_(int param_1)

{
  int iVar1;
  char *pcVar2;
  char *pcVar3;
  double dVar4;
  double dVar5;
  float local_24;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar1 = 0;
  pcVar3 = *(char **)(param_1 + 0x90);
  pcVar2 = DAT_803c4e84;
  do {
    if ((pcVar3 != pcVar2) && (*pcVar2 != '\0')) {
      if ((pcVar2[0x18] == '\x01') && (pcVar2[0x6cb] == '\0')) {
        if (*(float *)(pcVar2 + 0x720) <= FLOAT_8043a1bc) {
          if ((((*(ushort *)(pcVar2 + 0x272) & 2) == 0) && (pcVar2[0x743] != '\0')) &&
             (*(float *)(pcVar2 + 0x204) < FLOAT_8043a1c0)) {
            if (*(float *)(pcVar2 + 0x24) + *(float *)(pcVar2 + 0x668) <=
                *(float *)(DAT_8043625c + 0x34)) {
              local_24 = *(float *)(pcVar2 + 0x910);
              local_20 = *(undefined4 *)(pcVar2 + 0x920);
              local_1c = *(undefined4 *)(pcVar2 + 0x930);
              dVar4 = gnt4_PSVECSquareDistance_bl(&local_24,(float *)(param_1 + 0x154));
              if ((double)FLOAT_8043a1bc < dVar4) {
                dVar5 = 1.0 / SQRT(dVar4);
                dVar5 = DOUBLE_8043a1c8 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_8043a1d0);
                dVar5 = DOUBLE_8043a1c8 * dVar5 * -(dVar4 * dVar5 * dVar5 - DOUBLE_8043a1d0);
                dVar4 = (double)(float)(dVar4 * DOUBLE_8043a1c8 * dVar5 *
                                                -(dVar4 * dVar5 * dVar5 - DOUBLE_8043a1d0));
              }
              if (dVar4 <= (double)*(float *)(param_1 + 0x144)) {
                zz_014191c_((int)pcVar2,param_1);
              }
            }
          }
        }
      }
    }
    iVar1 = iVar1 + 1;
    pcVar2 = pcVar2 + 0x1e00;
  } while (iVar1 < 6);
  return;
}



// ==== 8014191c  zz_014191c_ ====

void zz_014191c_(int param_1,int param_2)

{
  float fVar1;
  double dVar2;
  float fStack_28;
  float local_24;
  float local_1c;
  undefined4 local_18;
  undefined4 local_14;
  
  local_1c = *(float *)(param_1 + 0x910);
  local_18 = *(undefined4 *)(param_1 + 0x920);
  local_14 = *(undefined4 *)(param_1 + 0x930);
  gnt4_PSVECSubtract_bl(&local_1c,(float *)(param_2 + 0x20),&fStack_28);
  dVar2 = gnt4_PSVECMag_bl(&fStack_28);
  if ((double)FLOAT_8043a1d8 < dVar2) {
    gnt4_PSVECNormalize_bl(&fStack_28,&fStack_28);
    fVar1 = FLOAT_8043a1bc;
    if (*(char *)(param_1 + 0x87) == '\0') {
      if (FLOAT_8043a1dc <= local_24) {
        *(float *)(param_1 + 0x48) = FLOAT_8043a1bc;
        *(byte *)(param_1 + 0x732) = *(byte *)(param_1 + 0x732) | 0x80;
      }
    }
    else if (FLOAT_8043a1bc < local_24) {
      *(byte *)(param_1 + 0x732) = *(byte *)(param_1 + 0x732) | 0x80;
      if (*(float *)(param_1 + 0x48) <= fVar1) {
        *(float *)(param_1 + 0x48) = fVar1;
      }
    }
    gnt4_PSQUATScale_bl((double)FLOAT_8043a1e0,&fStack_28,&fStack_28);
    zz_0084498_(param_1,&fStack_28);
  }
  return;
}



// ==== 80141a10  FUN_80141a10 ====

void FUN_80141a10(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  return;
}



// ==== 80141a1c  FUN_80141a1c ====

void FUN_80141a1c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80141a40  zz_0141a40_ ====

void zz_0141a40_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  if ((*(short *)(param_1 + 1000) == 3) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,6), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_80141b3c;
    *(code **)(puVar1 + 0x10c) = FUN_80141de4;
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



// ==== 80141b3c  FUN_80141b3c ====

void FUN_80141b3c(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8033af68)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80141b90  FUN_80141b90 ====

void FUN_80141b90(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  int iVar1;
  undefined4 extraout_r4;
  undefined4 uVar2;
  int iVar3;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar4;
  
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar1 = zz_0006f98_(*(int *)(param_9 + 0x90));
  uVar4 = zz_0007030_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xe0),0,iVar1 + 0xc28,in_r7,in_r8,
                      in_r9,in_r10);
  iVar3 = iVar1 + 0xc28;
  uVar2 = 0;
  uVar4 = zz_0007030_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar1 + 0x600),*(int *)(param_9 + 0xe4),0,iVar3,in_r7,in_r8,in_r9,
                      in_r10);
  zz_0007c54_(uVar4,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,uVar2,iVar3,in_r7,in_r8,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043a1e8,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  *(undefined1 *)(param_9 + 0x144) = 0xff;
  *(undefined1 *)(param_9 + 0x145) = 0xff;
  zz_0141c30_(param_9);
  return;
}



// ==== 80141c30  zz_0141c30_ ====

void zz_0141c30_(int param_1)

{
  if (*(char *)(*(int *)(param_1 + 0x90) + 0x7c8) != '\0') {
    *(char *)(param_1 + 0x82) = *(char *)(param_1 + 0x96) + 'A';
    return;
  }
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80141c6c  FUN_80141c6c ====

void FUN_80141c6c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80141c8c  zz_0141c8c_ ====

/* WARNING: Removing unreachable block (ram,0x80141d4c) */

void zz_0141c8c_(int param_1,int param_2,undefined *param_3,int *param_4,undefined4 param_5,
                undefined4 param_6,undefined4 param_7,undefined4 param_8)

{
  char cVar1;
  bool bVar2;
  uint uVar3;
  undefined *puVar4;
  int iVar5;
  undefined8 uVar6;
  double dVar7;
  double dVar8;
  double in_f4;
  double in_f5;
  double in_f6;
  double in_f7;
  double in_f8;
  float afStack_48 [13];
  
  iVar5 = *param_4;
  cVar1 = param_3[iVar5];
  *param_4 = iVar5 + 1;
  dVar7 = (double)*(float *)(param_1 + 0x7b4);
  dVar8 = (double)*(float *)(param_1 + 0x7b8);
  puVar4 = param_3;
  uVar6 = zz_020b4ac_((double)*(float *)(param_1 + 0x7b0),dVar7,dVar8,
                      (float *)(param_1 + cVar1 * 0x30 + 0x8d4),afStack_48);
  if ((*(uint *)(param_1 + 0x76c) & 1 << (int)cVar1) == 0) {
    uVar6 = gnt4_HSD_JObjSetFlags
                      (uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,param_2,0x10,puVar4,iVar5,
                       param_5,param_6,param_7,param_8);
  }
  else {
    uVar6 = gnt4_HSD_JObjClearFlags
                      (uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,param_2,0x10,puVar4,iVar5,
                       param_5,param_6,param_7,param_8);
  }
  if (param_2 == 0) {
    puVar4 = &DAT_8043a1f4;
    gnt4___assert_bl(uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,&DAT_8043a1ec,0x495,
                     &DAT_8043a1f4,iVar5,param_5,param_6,param_7,param_8);
  }
  uVar6 = gnt4_PSMTXCopy_bl(afStack_48,(float *)(param_2 + 0x44));
  *(uint *)(param_2 + 0x14) = *(uint *)(param_2 + 0x14) | 0x3800000;
  if (param_2 != 0) {
    uVar3 = *(uint *)(param_2 + 0x14);
    bVar2 = false;
    if (((uVar3 & 0x800000) == 0) && ((uVar3 & 0x40) != 0)) {
      bVar2 = true;
    }
    if (!bVar2) {
      gnt4_HSD_JObjSetMtxDirtySub_bl
                (uVar6,dVar7,dVar8,in_f4,in_f5,in_f6,in_f7,in_f8,param_2,uVar3,puVar4,iVar5,param_5,
                 param_6,param_7,param_8);
    }
  }
  if (param_2 == 0) {
    iVar5 = 0;
  }
  else {
    iVar5 = *(int *)(param_2 + 0x10);
  }
  while (iVar5 != 0) {
    zz_0141c8c_(param_1,iVar5,param_3,param_4,param_5,param_6,param_7,param_8);
    if (iVar5 == 0) {
      iVar5 = 0;
    }
    else {
      iVar5 = *(int *)(iVar5 + 8);
    }
  }
  return;
}



// ==== 80141de4  FUN_80141de4 ====

void FUN_80141de4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  byte bVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined *puVar5;
  int in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  int local_58;
  float afStack_54 [16];
  
  iVar6 = *(int *)(param_9 + 0x90);
  iVar3 = zz_0006f98_(iVar6);
  if ((*(char *)(iVar6 + 0xae) == '\0') && (*(char *)(iVar6 + 0x7c8) != '\x02')) {
    cVar2 = '\0';
  }
  else {
    cVar2 = '\x01';
  }
  iVar8 = *(int *)(param_9 + cVar2 * 4 + 0xe0);
  local_58 = 0;
  zz_0141c8c_(iVar6,*(int *)(iVar8 + 0xc),
              (undefined *)(*(int *)(iVar3 + 0x604) + *(int *)(*(int *)(iVar3 + 0x604) + 8)),
              &local_58,in_r7,in_r8,in_r9,in_r10);
  uVar9 = zz_00097b4_(iVar8,0x45);
  for (local_58 = 0; local_58 < 2; local_58 = local_58 + 1) {
    iVar8 = param_9 + local_58;
    bVar1 = *(byte *)(iVar6 + local_58 + 0x1d94);
    puVar5 = (undefined *)(uint)bVar1;
    iVar7 = *(int *)(param_9 + (cVar2 + 2 + local_58 * 2) * 4 + 0xe0);
    if (bVar1 != *(byte *)(iVar8 + 0x144)) {
      *(byte *)(iVar8 + 0x144) = bVar1;
      in_r7 = local_58 * 0x14;
      uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar3 + 0x600),*(int *)(param_9 + local_58 * 8 + 0xe8),
                          *(int *)(in_r7 + -0x7fcc50c0 + *(char *)(iVar6 + local_58 + 0x1d94) * 4),
                          iVar3 + 0xc28,in_r7,in_r8,in_r9,in_r10);
      iVar8 = iVar3 + 0xc28;
      puVar5 = *(undefined **)
                (local_58 * 0x14 + -0x7fcc50c0 + *(char *)(iVar6 + local_58 + 0x1d94) * 4);
      uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar3 + 0x600),*(int *)(param_9 + local_58 * 8 + 0xec),
                          (int)puVar5,iVar8,in_r7,in_r8,in_r9,in_r10);
      zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                  *(int *)(param_9 + local_58 * 8 + 0xec),extraout_r4,puVar5,iVar8,in_r7,in_r8,in_r9
                  ,in_r10);
      zz_0007cac_((double)FLOAT_8043a1e8,*(int *)(param_9 + local_58 * 8 + 0xec));
    }
    iVar4 = 0xb;
    if (local_58 == 0) {
      iVar4 = 7;
    }
    param_2 = (double)*(float *)(iVar6 + 0x7b4);
    param_3 = (double)*(float *)(iVar6 + 0x7b8);
    uVar9 = zz_020b4ac_((double)*(float *)(iVar6 + 0x7b0),param_2,param_3,
                        (float *)(iVar6 + iVar4 * 0x30 + 0x8d4),afStack_54);
    zz_00076d0_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar7,afStack_54,
                puVar5,iVar8,in_r7,in_r8,in_r9,in_r10);
    uVar9 = zz_00097b4_(iVar7,0x45);
  }
  return;
}



// ==== 80141fdc  FUN_80141fdc ====

void FUN_80141fdc(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(0xd4);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    zz_00e48cc_(param_1,-0x7fcc4d90,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}



// ==== 80142054  FUN_80142054 ====

void FUN_80142054(int param_1)

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
      FUN_800e4a18((double)FLOAT_8043a200,param_1,(float *)&DAT_8033b270,5,(float *)(puVar2 + 3),
                   (float *)(puVar2 + 0x12),(float *)(puVar2 + 0x30));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcc4d90,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}



// ==== 801420e8  FUN_801420e8 ====

void FUN_801420e8(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 80142120  FUN_80142120 ====

void FUN_80142120(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcc4d90,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fcc4d90,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 801421c0  FUN_801421c0 ====

void FUN_801421c0(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(0xd4);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    zz_00e48cc_(param_1,-0x7fcc4ca0,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}



// ==== 80142238  FUN_80142238 ====

void FUN_80142238(int param_1)

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
      FUN_800e4a18((double)FLOAT_8043a204,param_1,(float *)&DAT_8033b360,5,(float *)(puVar2 + 3),
                   (float *)(puVar2 + 0x12),(float *)(puVar2 + 0x30));
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcc4ca0,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}



// ==== 801422cc  FUN_801422cc ====

void FUN_801422cc(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 80142304  FUN_80142304 ====

void FUN_80142304(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcc4ca0,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fcc4ca0,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 801423a4  FUN_801423a4 ====

/* WARNING: Removing unreachable block (ram,0x80142650) */
/* WARNING: Removing unreachable block (ram,0x801423b4) */

void FUN_801423a4(int param_1,short *param_2)

{
  float fVar1;
  short sVar2;
  int iVar3;
  short sVar5;
  int iVar4;
  double dVar6;
  double dVar7;
  float local_58;
  float local_54;
  undefined4 local_50;
  float local_4c;
  float local_48;
  undefined4 local_44;
  undefined4 local_40;
  uint uStack_3c;
  longlong local_38;
  undefined4 local_30;
  uint uStack_2c;
  longlong local_28;
  
  iVar3 = zz_0066580_(param_1);
  dVar6 = DOUBLE_8043a210;
  fVar1 = FLOAT_8043a208;
  uStack_3c = (int)*param_2 ^ 0x80000000;
  local_40 = 0x43300000;
  sVar5 = (short)iVar3 - *(short *)(param_1 + 0x72);
  local_30 = 0x43300000;
  iVar3 = (int)((float)((double)CONCAT44(0x43300000,uStack_3c) - DOUBLE_8043a210) * FLOAT_8043a208);
  local_38 = (longlong)iVar3;
  *param_2 = (short)iVar3;
  uStack_2c = (int)param_2[1] ^ 0x80000000;
  iVar3 = (int)((float)((double)CONCAT44(0x43300000,uStack_2c) - dVar6) * fVar1);
  local_28 = (longlong)iVar3;
  param_2[1] = (short)iVar3;
  if ((*(byte *)(param_1 + 0x6e9) & 1) != 0) {
    sVar2 = sVar5;
    if (0x4000 < sVar5) {
      sVar2 = 0;
    }
    if (sVar2 < -0x4000) {
      sVar2 = 0;
    }
    if (0x2000 < sVar2) {
      sVar2 = 0x2000;
    }
    if (sVar2 < -0x2000) {
      sVar2 = -0x2000;
    }
    sVar2 = sVar2 - *param_2;
    if (sVar2 < 1) {
      if (sVar2 < -0x200) {
        sVar2 = -0x200;
      }
    }
    else if (0x200 < sVar2) {
      sVar2 = 0x200;
    }
    *param_2 = *param_2 + sVar2;
  }
  if ((((*(byte *)(param_1 + 0x6e9) & 0xe) != 0) && (sVar5 < 0x4000)) && (-0x4000 < sVar5)) {
    local_4c = *(float *)(param_1 + 0xb18);
    dVar6 = (double)*(float *)(param_1 + 0xb28);
    local_44 = *(undefined4 *)(param_1 + 0xb38);
    local_48 = FLOAT_8043a20c;
    dVar7 = gnt4_PSVECMag_bl(&local_4c);
    iVar3 = FUN_800452a0(dVar6,dVar7);
    local_58 = *(float *)(param_1 + 0xb20);
    local_54 = *(float *)(param_1 + 0xb30);
    local_50 = *(undefined4 *)(param_1 + 0xb40);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x50c),&local_58,&local_58);
    dVar7 = (double)local_54;
    local_54 = FLOAT_8043a20c;
    dVar6 = gnt4_PSVECMag_bl(&local_58);
    iVar4 = FUN_800452a0(dVar7,dVar6);
    if ((*(byte *)(param_1 + 0x6e9) & 4) == 0) {
      if ((*(byte *)(param_1 + 0x6e9) & 8) == 0) {
        sVar5 = 0;
      }
      else {
        sVar5 = 0x1000;
      }
    }
    else {
      sVar5 = -0x1000;
    }
    sVar5 = sVar5 + ((short)iVar3 - (short)iVar4);
    if (sVar5 < 1) {
      if (sVar5 < -0x200) {
        sVar5 = -0x200;
      }
    }
    else if (0x200 < sVar5) {
      sVar5 = 0x200;
    }
    param_2[1] = param_2[1] + sVar5;
    if (0x4000 < param_2[1]) {
      param_2[1] = 0x4000;
    }
    if (param_2[1] < -0x4000) {
      param_2[1] = -0x4000;
    }
  }
  *(short *)(param_1 + 0x190a) = param_2[1] >> 2;
  *(short *)(param_1 + 0x1910) = param_2[1] >> 2;
  *(short *)(param_1 + 0x1916) = param_2[1] >> 2;
  *(short *)(param_1 + 0x191c) = param_2[1];
  *(short *)(param_1 + 0x1920) = -(*param_2 >> 1);
  *(short *)(param_1 + 0x190c) = *param_2 >> 3;
  *(short *)(param_1 + 0x1912) = *param_2 >> 3;
  *(short *)(param_1 + 0x1918) = *param_2 >> 3;
  return;
}



// ==== 80142794  FUN_80142794 ====

void FUN_80142794(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x502) {
    FUN_80141fdc(param_1);
    FUN_80143750(param_1,0,0);
    FUN_80143750(param_1,0,1);
    zz_00c74ec_(param_1,0x11);
  }
  else if (*(short *)(param_1 + 1000) == 0x50e) {
    FUN_801421c0(param_1);
    FUN_80143750(param_1,1,0);
    FUN_80143750(param_1,1,1);
    zz_00c74ec_(param_1,0x15);
  }
  *(float *)(param_1 + 0x14c) = FLOAT_8043a20c;
  *(undefined2 *)(param_1 + 0x150) = 0;
  return;
}



// ==== 8014285c  FUN_8014285c ====

void FUN_8014285c(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  double dVar4;
  
  zz_0046698_(param_1);
  FUN_801423a4(param_1,(short *)(param_1 + 0x144));
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x152) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x152) ^ 0x80000000) -
                             DOUBLE_8043a210) * FLOAT_8043a218);
    *(undefined1 *)(param_1 + 0x6f5) = 0;
    *(undefined1 *)(param_1 + 0x6f6) = 0;
  }
  cVar1 = *(char *)(param_1 + 0x6f3);
  if (cVar1 < '\x01') {
    if (cVar1 < '\0') {
      *(undefined1 *)(param_1 + 0x6f2) = 2;
    }
    else {
      *(undefined1 *)(param_1 + 0x6f2) = 0;
    }
  }
  else {
    *(char *)(param_1 + 0x6f3) = cVar1 + -1;
    *(undefined1 *)(param_1 + 0x6f2) = 1;
    FUN_800061a8(param_1,8);
  }
  *(float *)(param_1 + 0x1dc0) = FLOAT_8043a21c;
  fVar3 = FLOAT_8043a224;
  fVar2 = FLOAT_8043a20c;
  if ((*(char *)(param_1 + 0x18) == '\x01') && (*(char *)(param_1 + 0x19) == '\x02')) {
    if ((*(char *)(param_1 + 0x5db) == '\x01') || ((*(uint *)(param_1 + 0x5e0) & 0x10) != 0)) {
      *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) + FLOAT_8043a220;
      if (fVar3 < *(float *)(param_1 + 0x14c)) {
        *(float *)(param_1 + 0x14c) = fVar3;
      }
      *(short *)(param_1 + 0x150) = *(short *)(param_1 + 0x150) + 0x180;
    }
    else {
      *(float *)(param_1 + 0x14c) = *(float *)(param_1 + 0x14c) - FLOAT_8043a220;
      if (*(float *)(param_1 + 0x14c) < fVar2) {
        *(float *)(param_1 + 0x14c) = fVar2;
      }
    }
    dVar4 = zz_0045204_(*(short *)(param_1 + 0x150));
    *(float *)(param_1 + 0x1dc0) =
         (float)((double)*(float *)(param_1 + 0x14c) *
                 (double)(float)((double)FLOAT_8043a21c * dVar4) + (double)FLOAT_8043a21c);
  }
  return;
}



// ==== 801429d8  FUN_801429d8 ====

void FUN_801429d8(int param_1)

{
  FUN_801423a4(param_1,(short *)(param_1 + 0x144));
  if (*(short *)(param_1 + 1000) == 0x502) {
    FUN_80142054(param_1);
  }
  else if (*(short *)(param_1 + 1000) == 0x50e) {
    FUN_80142238(param_1);
  }
  return;
}



// ==== 80142a3c  FUN_80142a3c ====

void FUN_80142a3c(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x502) {
    FUN_801420e8(param_1);
  }
  else if (*(short *)(param_1 + 1000) == 0x50e) {
    FUN_801422cc(param_1);
  }
  return;
}



// ==== 80142a78  FUN_80142a78 ====

void FUN_80142a78(int param_1)

{
  if (*(short *)(param_1 + 1000) == 0x502) {
    FUN_80142120(param_1);
  }
  else if (*(short *)(param_1 + 1000) == 0x50e) {
    FUN_80142304(param_1);
  }
  return;
}



// ==== 80142ab4  FUN_80142ab4 ====

void FUN_80142ab4(undefined4 param_1,char param_2,char param_3)

{
  (**(code **)(&DAT_80434678 + param_2 * 4))(param_1,(int)param_3);
  return;
}



// ==== 80142af4  FUN_80142af4 ====

void FUN_80142af4(int param_1)

{
  (*(code *)(&PTR_FUN_8033b490)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80142b30  FUN_80142b30 ====

void FUN_80142b30(int param_1)

{
  (*(code *)(&PTR_FUN_8033b49c)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80142b6c  FUN_80142b6c ====

void FUN_80142b6c(int param_1)

{
  if ('\0' < *(char *)(param_1 + 0x6f6)) {
    FUN_80143094(param_1);
  }
  (*(code *)(&PTR_FUN_8033b4b0)[*(char *)(param_1 + 0x540)])(param_1);
  gnt4_PSQUATScale_bl((double)FLOAT_8043a228,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  return;
}



// ==== 80142bf0  FUN_80142bf0 ====

void FUN_80142bf0(int param_1)

{
  float fVar1;
  float fVar2;
  
  fVar2 = FLOAT_8043a22c;
  fVar1 = FLOAT_8043a20c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar2;
  *(undefined1 *)(param_1 + 0x6f6) = 1;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  zz_006d144_(param_1,0xc1);
  zz_004beb8_((double)FLOAT_8043a230,param_1,0xf,2,0,0xffffffff,0xffffffff);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  return;
}



// ==== 80142c9c  FUN_80142c9c ====

void FUN_80142c9c(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043a20c;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc1), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80142d00  FUN_80142d00 ====

void FUN_80142d00(double param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  int iVar1;
  
  zz_004cd24_(param_9,0xf);
  if ('\0' < *(char *)(param_9 + 0x1cef)) {
    *(undefined1 *)(param_9 + 0x1cef) = 0;
    param_11 = 1;
    param_12 = 1;
    iVar1 = zz_006dbe0_(param_9,0,1,1);
    if (iVar1 != 0) {
      *(undefined1 *)(param_9 + 0x6f6) = 0;
      *(undefined1 *)(param_9 + 0x6f5) = 3;
    }
  }
  if (*(char *)(param_9 + 0x1cee) != '\0') {
    *(undefined1 *)(param_9 + 0x73f) = 0;
    *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
    if ((*(uint *)(param_9 + 0x5e0) & 0x40) == 0) {
      zz_006a474_(param_9);
    }
    else if ((*(uint *)(param_9 + 0x5e0) & 0x80) == 0) {
      zz_006a5a4_(param_9);
    }
    else {
      zz_006a750_(param_9,0x21);
      zz_006a668_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x14,
                  param_11,param_12,param_13,param_14,param_15,param_16);
    }
  }
  return;
}



// ==== 80142dd4  FUN_80142dd4 ====

void FUN_80142dd4(int param_1)

{
  if ('\0' < *(char *)(param_1 + 0x6f6)) {
    FUN_80143094(param_1);
  }
  (*(code *)(&PTR_FUN_8033b4bc)[*(char *)(param_1 + 0x540)])(param_1);
  gnt4_PSQUATScale_bl((double)FLOAT_8043a228,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  return;
}



// ==== 80142e58  FUN_80142e58 ====

void FUN_80142e58(int param_1)

{
  float fVar1;
  
  fVar1 = FLOAT_8043a22c;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  *(undefined1 *)(param_1 + 0x6f6) = 1;
  zz_006d144_(param_1,0x81);
  zz_004beb8_((double)FLOAT_8043a230,param_1,0xf,2,1,0xffffffff,0xffffffff);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff7f;
  return;
}



// ==== 80142ee0  FUN_80142ee0 ====

void FUN_80142ee0(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  fVar2 = FLOAT_8043a20c;
  fVar1 = *(float *)(param_1 + 0x560) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x560) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0x81), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80142f44  FUN_80142f44 ====

void FUN_80142f44(undefined8 param_1,undefined8 param_2,double param_3,double param_4,double param_5
                 ,double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  float fVar1;
  float fVar2;
  int iVar3;
  double dVar4;
  double dVar5;
  double dVar6;
  
  fVar1 = FLOAT_8043a234;
  if (*(char *)(param_9 + 0x5db) == ')') {
    if (*(char *)(param_9 + 0x540) == '\0') {
      *(undefined1 *)(param_9 + 0x540) = 1;
      fVar2 = FLOAT_8043a238;
      *(float *)(param_9 + 0x558) = fVar1;
      *(float *)(param_9 + 0x55c) = fVar2;
      *(undefined1 *)(param_9 + 0x6f6) = 1;
      *(undefined4 *)(param_9 + 0x754) = 0;
    }
    zz_004cd24_(param_9,4);
    if ('\0' < *(char *)(param_9 + 0x6f6)) {
      FUN_80143094(param_9);
    }
    fVar2 = FLOAT_8043a20c;
    fVar1 = *(float *)(param_9 + 0x558) - *(float *)(param_9 + 0x1dc8);
    *(float *)(param_9 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      param_11 = 1;
      *(float *)(param_9 + 0x558) = FLOAT_8043a23c;
      param_12 = 1;
      iVar3 = zz_006dbe0_(param_9,0,1,1);
      if (iVar3 != 0) {
        *(undefined1 *)(param_9 + 0x6f6) = 0;
        *(undefined1 *)(param_9 + 0x6f5) = 3;
      }
    }
    dVar6 = (double)*(float *)(param_9 + 0x55c);
    dVar4 = (double)FLOAT_8043a20c;
    fVar1 = (float)(dVar6 - (double)*(float *)(param_9 + 0x1dc8));
    dVar5 = (double)fVar1;
    *(float *)(param_9 + 0x55c) = fVar1;
    if (dVar4 < dVar5) {
      zz_0048d54_(dVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,param_9,1,param_11,
                  param_12,param_13,param_14,param_15,param_16);
    }
    else {
      *(undefined1 *)(param_9 + 0x73f) = 0;
      *(uint *)(param_9 + 0x5e0) = *(uint *)(param_9 + 0x5e0) & 0xfffffffc;
      zz_006a668_(dVar5,dVar6,param_3,param_4,param_5,param_6,param_7,param_8,param_9,0x10,param_11,
                  param_12,param_13,param_14,param_15,param_16);
      *(float *)(param_9 + 0x694) = FLOAT_8043a238 + *(float *)(param_9 + 0x1dc8);
    }
  }
  else {
    zz_006a3d0_(param_9,'\0',3,0);
  }
  return;
}



// ==== 80143094  FUN_80143094 ====

/* WARNING: Removing unreachable block (ram,0x80143214) */
/* WARNING: Removing unreachable block (ram,0x801430a4) */

void FUN_80143094(int param_1)

{
  short sVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  float local_48;
  float local_44;
  undefined4 local_40;
  undefined8 local_30;
  double local_28;
  
  if (*(int *)(param_1 + 0xcc) == 0) {
    uVar2 = (int)*(short *)(param_1 + 0x152) ^ 0x80000000;
    local_30 = (double)CONCAT44(0x43300000,uVar2);
    *(short *)(param_1 + 0x152) =
         (short)(int)-(FLOAT_8043a240 *
                       (float)((double)CONCAT44(0x43300000,uVar2) - DOUBLE_8043a210) *
                       *(float *)(param_1 + 0x1dc8) - (float)(local_30 - DOUBLE_8043a210));
  }
  else {
    local_48 = *(float *)(param_1 + 0x938);
    dVar5 = (double)*(float *)(param_1 + 0x948);
    local_40 = *(undefined4 *)(param_1 + 0x958);
    local_44 = FLOAT_8043a20c;
    dVar6 = gnt4_PSVECMag_bl(&local_48);
    iVar3 = FUN_800452a0(dVar5,dVar6);
    local_48 = *(float *)(param_1 + 0x940);
    local_44 = *(float *)(param_1 + 0x950);
    local_40 = *(undefined4 *)(param_1 + 0x960);
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x518),&local_48,&local_48);
    dVar6 = (double)local_44;
    local_44 = FLOAT_8043a20c;
    dVar5 = gnt4_PSVECMag_bl(&local_48);
    iVar4 = FUN_800452a0(dVar6,dVar5);
    sVar1 = (short)iVar3 - (short)iVar4;
    if (0x4000 < sVar1) {
      sVar1 = 0x4000;
    }
    local_28 = (double)(CONCAT44(0x43300000,(int)sVar1 - (int)*(short *)(param_1 + 0x152)) ^
                       0x80000000);
    sVar1 = (short)(int)(*(float *)(param_1 + 0x1dc8) * (float)(local_28 - DOUBLE_8043a210));
    if (0x1000 < sVar1) {
      sVar1 = 0x1000;
    }
    if (sVar1 < -0x1000) {
      sVar1 = -0x1000;
    }
    *(short *)(param_1 + 0x152) = *(short *)(param_1 + 0x152) + sVar1;
  }
  return;
}



// ==== 80143234  FUN_80143234 ====

void FUN_80143234(int param_1)

{
  (*(code *)(&PTR_FUN_8033b4c8)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80143270  FUN_80143270 ====

void FUN_80143270(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033b4dc)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801432c0  FUN_801432c0 ====

void FUN_801432c0(int param_1)

{
  char cVar1;
  uint uVar2;
  double dVar3;
  
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(undefined1 *)(param_1 + 0x6ea) = 0;
  uVar2 = FUN_80066838((double)*(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc +
                                         0x868),param_1);
  if ((int)uVar2 < 1) {
    *(undefined1 *)(param_1 + 0x541) = 1;
    *(undefined4 *)(param_1 + 0xcc) = 0;
    if ((*(uint *)(param_1 + 0x5e0) & 0x80) == 0) {
      *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x72);
    }
    else {
      *(undefined2 *)(param_1 + 0x5ac) = *(undefined2 *)(param_1 + 0x5ae);
    }
  }
  *(float *)(param_1 + 0x558) = FLOAT_8043a244;
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  cVar1 = *(char *)(param_1 + 0x6ea);
  dVar3 = (double)FLOAT_8043a230;
  *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
  zz_004beb8_(dVar3,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a20c;
  zz_0092dcc_(param_1,0);
  return;
}



// ==== 801433f4  FUN_801433f4 ====

void FUN_801433f4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  zz_006e1ac_(param_1,0xc0,1);
  fVar2 = FLOAT_8043a20c;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar3 = zz_006d144_(param_1,0xc0), iVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80143498  FUN_80143498 ====

void FUN_80143498(int param_1)

{
  float fVar1;
  
  zz_004cd24_(param_1,0xf);
  zz_006d144_(param_1,0xc0);
  zz_006e1ac_(param_1,0xc0,1);
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00677b0_(param_1);
  fVar1 = FLOAT_8043a244;
  if (*(char *)(param_1 + 0x1cef) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(undefined1 *)(param_1 + 0x542) = 0;
    *(float *)(param_1 + 0x558) = fVar1;
    FUN_80155c10(param_1,0);
    *(undefined1 *)(param_1 + 0x6f3) = 2;
  }
  return;
}



// ==== 80143538  FUN_80143538 ====

void FUN_80143538(int param_1)

{
  char cVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  double dVar5;
  double dVar6;
  
  *(undefined1 *)(param_1 + 0x6f3) = 2;
  dVar5 = zz_0045238_(*(short *)(param_1 + 0x18da));
  *(float *)(param_1 + 0x44) = (float)((double)FLOAT_8043a248 * dVar5);
  dVar5 = zz_0045204_(*(short *)(param_1 + 0x18da));
  dVar6 = (double)FLOAT_8043a224;
  *(float *)(param_1 + 0x48) = (float)((double)FLOAT_8043a248 * -dVar5);
  FUN_80067310(dVar6,param_1,*(short *)(param_1 + 0x5ae));
  iVar4 = zz_00677b0_(param_1);
  if (iVar4 != 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a210) *
                     -(FLOAT_8043a24c * *(float *)(param_1 + 0x1dc8) - FLOAT_8043a224));
  }
  zz_004cd24_(param_1,0xf);
  fVar3 = FLOAT_8043a20c;
  fVar2 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar2;
  if (fVar2 <= fVar3) {
    *(float *)(param_1 + 0x558) = fVar3;
    fVar2 = FLOAT_8043a244;
    if (*(char *)(param_1 + 0x1b01) != '\0') {
      dVar5 = (double)FLOAT_8043a230;
      *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
      *(float *)(param_1 + 0x558) = fVar2;
      cVar1 = *(char *)(param_1 + 0x6ea);
      *(char *)(param_1 + 0x6ea) = cVar1 + '\x01';
      zz_004beb8_(dVar5,param_1,0xf,3,(int)cVar1,0xffffffff,0xffffffff);
      *(undefined1 *)(param_1 + 0x6f3) = 0xff;
    }
  }
  return;
}



// ==== 8014367c  FUN_8014367c ====

void FUN_8014367c(int param_1)

{
  int iVar1;
  
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a210) * FLOAT_8043a218);
  zz_004cd24_(param_1,0xf);
  zz_006ed8c_((double)FLOAT_8043a250,param_1);
  FUN_80067310((double)FLOAT_8043a224,param_1,*(short *)(param_1 + 0x5ae));
  iVar1 = zz_00677b0_(param_1);
  if (*(char *)(param_1 + 0x1cee) != '\0') {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    if (iVar1 == 0) {
      zz_006a5a4_(param_1);
    }
    else {
      zz_006a474_(param_1);
    }
  }
  zz_00b22f4_(param_1);
  return;
}



// ==== 80143750  FUN_80143750 ====

void FUN_80143750(int param_1,undefined1 param_2,undefined1 param_3)

{
  undefined1 *puVar1;
  
  if (((*(short *)(param_1 + 1000) == 0x502) || (*(short *)(param_1 + 1000) == 0x50e)) &&
     (puVar1 = zz_0088aa0_(param_1,2,0,0,2), puVar1 != (undefined1 *)0x0)) {
    *puVar1 = 1;
    puVar1[0x11] = param_2;
    puVar1[0x13] = param_3;
    puVar1[0x83] = 0x18;
    *(code **)(puVar1 + 0xc) = FUN_80143870;
    *(code **)(puVar1 + 0x10c) = FUN_80143b04;
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



// ==== 80143870  FUN_80143870 ====

void FUN_80143870(int param_1)

{
  zz_00660e8_(param_1,*(int *)(param_1 + 0x90));
  (*(code *)(&PTR_FUN_8033c2e0)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 801438c4  FUN_801438c4 ====

void FUN_801438c4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  float fVar1;
  undefined4 uVar2;
  undefined4 extraout_r4;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined2 *puVar7;
  int iVar8;
  undefined8 uVar9;
  
  iVar8 = *(int *)(param_9 + 0x90);
  *(undefined1 *)(param_9 + 0x18) = 1;
  iVar6 = *(char *)(param_9 + 0x11) * 0x48;
  *(code **)(param_9 + 0x100) = FUN_80047aa4;
  iVar5 = iVar6 + -0x7fcc3db0;
  puVar7 = (undefined2 *)(iVar5 + *(char *)(param_9 + 0x13) * 0x24);
  uVar9 = zz_0089100_(param_9,(int)*(char *)(iVar8 + 0x3e4) + 0x10,1);
  fVar1 = FLOAT_8043a258;
  *(undefined1 *)(param_9 + 0x84) = 0x4f;
  *(char *)(param_9 + 0x89) = (char)*puVar7;
  uVar2 = *(undefined4 *)(puVar7 + 4);
  *(undefined4 *)(param_9 + 100) = *(undefined4 *)(puVar7 + 2);
  *(undefined4 *)(param_9 + 0x68) = uVar2;
  *(undefined4 *)(param_9 + 0x6c) = *(undefined4 *)(puVar7 + 6);
  uVar2 = *(undefined4 *)(puVar7 + 10);
  *(undefined4 *)(param_9 + 0x58) = *(undefined4 *)(puVar7 + 8);
  *(undefined4 *)(param_9 + 0x5c) = uVar2;
  *(undefined4 *)(param_9 + 0x60) = *(undefined4 *)(puVar7 + 0xc);
  *(undefined4 *)(param_9 + 0x70) = *(undefined4 *)(puVar7 + 0xe);
  *(undefined2 *)(param_9 + 0x74) = puVar7[0x10];
  *(float *)(param_9 + 0x60) = fVar1;
  *(float *)(param_9 + 0x5c) = fVar1;
  *(float *)(param_9 + 0x58) = fVar1;
  *(float *)(param_9 + 0xb8) = fVar1;
  *(float *)(param_9 + 0xb4) = fVar1;
  iVar8 = zz_0006f98_(iVar8);
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xe0),
                      *(int *)(&DAT_80434688 + *(char *)(param_9 + 0x11) * 4),iVar8 + 0xc28,iVar5,
                      iVar6,in_r9,in_r10);
  iVar4 = iVar8 + 0xc28;
  iVar3 = *(int *)(&DAT_80434688 + *(char *)(param_9 + 0x11) * 4);
  uVar9 = zz_0007030_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                      *(int *)(iVar8 + 0x600),*(int *)(param_9 + 0xe4),iVar3,iVar4,iVar5,iVar6,in_r9
                      ,in_r10);
  zz_0007c54_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(param_9 + 0xe4)
              ,extraout_r4,iVar3,iVar4,iVar5,iVar6,in_r9,in_r10);
  zz_0007cac_((double)FLOAT_8043a25c,*(int *)(param_9 + 0xe4));
  *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + 'A';
  FUN_80143a34(param_9);
  return;
}



// ==== 80143a34  FUN_80143a34 ====

void FUN_80143a34(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  
  iVar3 = *(int *)(param_1 + 0x90);
  *(undefined2 *)(param_1 + 0x70) = *(undefined2 *)(iVar3 + 0x152);
  uVar2 = 1 << (int)*(char *)(param_1 + 0x13);
  if (((int)(char)*(byte *)(iVar3 + 0x6f5) & uVar2) != 0) {
    *(byte *)(iVar3 + 0x6f5) = *(byte *)(iVar3 + 0x6f5) & ~(byte)uVar2;
    *(undefined4 *)(param_1 + 0xcc) = *(undefined4 *)(iVar3 + 0xcc);
    *(undefined4 *)(param_1 + 200) = *(undefined4 *)(iVar3 + 200);
    *(undefined1 *)(param_1 + 0xd0) = *(undefined1 *)(iVar3 + 0xd0);
    uVar1 = *(undefined4 *)(iVar3 + 0xb4);
    *(undefined4 *)(param_1 + 0x60) = uVar1;
    *(undefined4 *)(param_1 + 0x5c) = uVar1;
    *(undefined4 *)(param_1 + 0x58) = uVar1;
    *(undefined4 *)(param_1 + 0xb8) = uVar1;
    *(undefined4 *)(param_1 + 0xb4) = uVar1;
    zz_00c3be0_(param_1,(char)*(undefined4 *)(&DAT_80434690 + *(char *)(param_1 + 0x11) * 4));
  }
  return;
}



// ==== 80143ae4  FUN_80143ae4 ====

void FUN_80143ae4(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80143b04  FUN_80143b04 ====

void FUN_80143b04(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
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



// ==== 80143c78  FUN_80143c78 ====

void FUN_80143c78(int param_1)

{
  *(undefined4 *)(param_1 + 0x144) = 0x1e;
  if (*(short *)(param_1 + 1000) == 0x702) {
    zz_01a40b0_(param_1,0);
    zz_01a40b0_(param_1,1);
  }
  else if (*(short *)(param_1 + 1000) == 0x70a) {
    zz_01a40b0_(param_1,2);
    zz_01a40b0_(param_1,3);
  }
  return;
}



// ==== 80143ce8  FUN_80143ce8 ====

void FUN_80143ce8(int param_1)

{
  if ((*(uint *)(param_1 + 0x5e0) & 3) == 0) {
    *(short *)(param_1 + 0x18da) =
         (short)(int)((float)((double)CONCAT44(0x43300000,
                                               (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                             DOUBLE_8043a268) * FLOAT_8043a260);
  }
  return;
}



// ==== 80143da8  FUN_80143da8 ====

void FUN_80143da8(undefined4 param_1,char param_2,char param_3)

{
  (*(code *)(&PTR_LAB_8033c330)[param_2])(param_1,(int)param_3);
  return;
}



// ==== 80143de8  FUN_80143de8 ====

void FUN_80143de8(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x702) {
    zz_001ab6c_(param_1,0x21);
  }
  else if (*(short *)(param_1 + 1000) == 0x70a) {
    zz_001ab6c_(param_1,0x52);
  }
  return;
}



// ==== 80143e34  FUN_80143e34 ====

void FUN_80143e34(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x702) {
    zz_001ab6c_(param_1,0x20);
  }
  else if (*(short *)(param_1 + 1000) == 0x70a) {
    zz_001ab6c_(param_1,0x51);
  }
  return;
}



// ==== 80143e80  FUN_80143e80 ====

void FUN_80143e80(int param_1)

{
  *(undefined1 *)(param_1 + 0xaf) = 1;
  if (*(short *)(param_1 + 1000) == 0x702) {
    zz_001ab6c_(param_1,0x21);
    zz_001ab6c_(param_1,0x20);
  }
  else if (*(short *)(param_1 + 1000) == 0x70a) {
    zz_001ab6c_(param_1,0x52);
    zz_001ab6c_(param_1,0x51);
  }
  return;
}



// ==== 80143efc  FUN_80143efc ====

uint FUN_80143efc(int param_1)

{
  uint uVar1;
  bool bVar2;
  
  uVar1 = zz_006dbe0_(param_1,0,1,1);
  if (uVar1 != 0) {
    if (*(short *)(param_1 + 1000) == 0x702) {
      bVar2 = zz_00fbc64_(param_1,1);
      uVar1 = (uint)bVar2;
    }
    else if (*(short *)(param_1 + 1000) == 0x70a) {
      bVar2 = zz_00fbc64_(param_1,6);
      uVar1 = (uint)bVar2;
    }
  }
  return uVar1;
}



// ==== 80143f70  FUN_80143f70 ====

void FUN_80143f70(int param_1)

{
  (*(code *)(&PTR_FUN_8033c34c)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80143fac  FUN_80143fac ====

void FUN_80143fac(int param_1)

{
  *(short *)(param_1 + 0x18da) =
       (short)(int)((float)((double)CONCAT44(0x43300000,
                                             (int)*(short *)(param_1 + 0x18da) ^ 0x80000000) -
                           DOUBLE_8043a268) * FLOAT_8043a260);
  (*(code *)(&PTR_FUN_8033c358)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80144020  FUN_80144020 ====

void FUN_80144020(int param_1)

{
  zz_0148d74_(param_1);
  return;
}



// ==== 80144048  FUN_80144048 ====

void FUN_80144048(int param_1)

{
  zz_0149178_(param_1);
  return;
}



// ==== 80144070  FUN_80144070 ====

void FUN_80144070(int param_1)

{
  zz_0148d74_(param_1);
  return;
}



// ==== 80144098  FUN_80144098 ====

void FUN_80144098(int param_1)

{
  if (*(char *)(param_1 + 0x541) != '\0') {
    *(undefined4 *)(param_1 + 0xcc) = 0;
  }
  (*(code *)(&PTR_FUN_8033c3ac)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801440e8  FUN_801440e8 ====

void FUN_801440e8(int param_1)

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
  *(float *)(param_1 + 0x558) = FLOAT_8043a270;
  zz_006d144_(param_1,0xc0);
  zz_004beb8_((double)FLOAT_8043a274,param_1,0xf,3,5,0xffffffff,0xffffffff);
  return;
}



// ==== 801441a4  FUN_801441a4 ====

void FUN_801441a4(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  
  if (*(char *)(param_1 + 0x1b03) != '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a278;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (iVar4 = zz_006d144_(param_1,0xc0), iVar4 != 0)) {
    fVar1 = FLOAT_8043a27c;
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    *(float *)(param_1 + 0x558) = fVar1;
    fVar3 = FLOAT_8043a280;
    fVar2 = FLOAT_8043a278;
    fVar1 = *(float *)(param_1 + ((int)*(char *)(param_1 + 0x584) % 3) * 0xc + 0x868);
    if ((*(int *)(param_1 + 0xcc) != 0) && (fVar1 < *(float *)(param_1 + 0x760))) {
      fVar1 = *(float *)(param_1 + 0x760);
    }
    *(float *)(param_1 + 0x44) = fVar1 / FLOAT_8043a27c;
    *(float *)(param_1 + 0x4c) = fVar2;
    if (fVar3 < *(float *)(param_1 + 0x760)) {
      zz_00b2190_(param_1,0);
    }
  }
  return;
}



// ==== 801442a4  FUN_801442a4 ====

void FUN_801442a4(int param_1)

{
  float fVar1;
  float fVar2;
  uint uVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043a284,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  if (*(char *)(param_1 + 0x1cef) == '\0') {
    zz_004cd24_(param_1,0xf);
  }
  fVar2 = FLOAT_8043a278;
  fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
  *(float *)(param_1 + 0x558) = fVar1;
  if ((fVar1 <= fVar2) || (uVar3 = FUN_80066838((double)FLOAT_8043a280,param_1), uVar3 != 0)) {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  }
  return;
}



// ==== 80144344  FUN_80144344 ====

void FUN_80144344(int param_1)

{
  float fVar1;
  float fVar2;
  float fVar3;
  
  zz_006d144_(param_1,0xc0);
  zz_006ed8c_((double)FLOAT_8043a284,param_1);
  zz_00670dc_(param_1,*(short *)(param_1 + 0x5ae));
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043a288;
  fVar1 = FLOAT_8043a270;
  if (*(char *)(param_1 + 0x1cf0) != '\0') {
    *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
    fVar3 = FLOAT_8043a28c;
    *(float *)(param_1 + 0x558) = fVar1;
    fVar1 = FLOAT_8043a274;
    *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x44) * fVar2;
    *(float *)(param_1 + 0x4c) = *(float *)(param_1 + 0x4c) * fVar2;
    *(float *)(param_1 + 0x48) = fVar3;
    *(float *)(param_1 + 0x50) = fVar1;
  }
  return;
}



// ==== 801443e4  FUN_801443e4 ====

void FUN_801443e4(int param_1)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  zz_004cd24_(param_1,0xf);
  fVar2 = FLOAT_8043a278;
  if (*(char *)(param_1 + 0x1d9) != '\0') {
    *(float *)(param_1 + 0x4c) = FLOAT_8043a278;
    *(float *)(param_1 + 0x44) = fVar2;
  }
  FUN_80067310((double)FLOAT_8043a290,param_1,*(short *)(param_1 + 0x5ae));
  iVar3 = zz_00677b0_(param_1);
  fVar2 = FLOAT_8043a278;
  if ((iVar3 == 0) || (*(char *)(param_1 + 0x1cee) == '\0')) {
    fVar1 = *(float *)(param_1 + 0x558) - *(float *)(param_1 + 0x1dc8);
    *(float *)(param_1 + 0x558) = fVar1;
    if (fVar1 <= fVar2) {
      *(undefined1 *)(param_1 + 0x73f) = 0;
      *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
      zz_006a5a4_(param_1);
    }
  }
  else {
    *(undefined1 *)(param_1 + 0x73f) = 0;
    *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xfffffffc;
    zz_006a750_(param_1,7);
    *(float *)(param_1 + 0x694) = FLOAT_8043a290 + *(float *)(param_1 + 0x1dc8);
  }
  return;
}



// ==== 801444c8  FUN_801444c8 ====

void FUN_801444c8(int param_1)

{
  (*(code *)(&PTR_FUN_8033c3c0)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 80144504  FUN_80144504 ====

void FUN_80144504(int param_1)

{
  zz_0149708_(param_1);
  return;
}



// ==== 8014452c  zz_014452c_ ====

void zz_014452c_(int param_1,undefined1 param_2)

{
  undefined1 *puVar1;
  
  puVar1 = zz_0088aa0_(param_1,3,8,0,4);
  if (puVar1 != (undefined1 *)0x0) {
    *puVar1 = 1;
    puVar1[0x10] = 0x3c;
    puVar1[0x11] = param_2;
    *(code **)(puVar1 + 0xc) = FUN_80144634;
    *(code **)(puVar1 + 0x10c) = FUN_80144b24;
    puVar1[0x13] = 4;
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



// ==== 80144634  FUN_80144634 ====

void FUN_80144634(int param_1)

{
  zz_00840b8_(param_1);
  (*(code *)(&PTR_FUN_8033d300)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80144684  FUN_80144684 ====

void FUN_80144684(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 uVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar6;
  longlong lVar7;
  undefined8 uVar8;
  
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x2c;
  iVar2 = -((int)*(short *)(&DAT_8033d252 + iVar4) >> 0x1f);
  if (iVar2 == 0) {
    iVar2 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8033d252 + iVar4));
  }
  uVar1 = (int)*(char *)(param_9 + 0x13) << 3;
  if (uVar1 < 0x81) {
    *(int *)(param_9 + 0x54) = param_9 + 0x144;
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar3 = zz_0006dc8_(uVar1);
    *(int **)(param_9 + 0xdc) = piVar3;
    if (piVar3 != (int *)0x0) {
      *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    }
  }
  if ((iVar2 == 0) || (*(int *)(param_9 + 0x54) == 0)) {
    *(undefined1 *)(param_9 + 0x18) = 2;
  }
  else {
    iVar6 = *(int *)(param_9 + 0x90);
    *(undefined1 *)(param_9 + 0x18) = 1;
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar6 + (char)(&DAT_8033d250)[iVar4] * 0x30 + 0x8d4),
               (float *)(iVar4 + -0x7fcc2da8),(float *)(param_9 + 0x20));
    zz_0083d60_(param_9,iVar6,1);
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8033d270 + iVar4);
    gnt4_PSVECNormalize_bl((float *)(param_9 + 0x38),(float *)(param_9 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8033d270 + iVar4),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    uVar5 = 1;
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8033d264 + iVar4);
    *(char *)(param_9 + 0x1cb) = (char)*(undefined2 *)(&DAT_8033d266 + iVar4);
    iVar2 = (int)*(short *)(&DAT_8033d254 + iVar4);
    *(char *)(param_9 + 0x12) = (char)*(short *)(&DAT_8033d254 + iVar4);
    *(undefined4 *)(param_9 + 0x48) = *(undefined4 *)(&DAT_8033d274 + iVar4);
    *(code **)(param_9 + 0x100) = zz_0144a00_;
    lVar7 = zz_0089100_(param_9,1,1);
    uVar8 = FUN_80144b8c(lVar7,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,
                         extraout_r4,uVar5,iVar2,in_r7,in_r8,in_r9,in_r10);
    if (-1 < *(short *)(&DAT_8033d256 + iVar4)) {
      zz_0144a00_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
      zz_00aedc0_(iVar6,(float *)(param_9 + 0x114),(int)*(short *)(&DAT_8033d256 + iVar4),
                  *(undefined1 *)(param_9 + 0x12));
    }
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    zz_00f036c_(param_9,0xf4);
  }
  return;
}



// ==== 80144834  FUN_80144834 ====

void FUN_80144834(int param_1)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  short sVar6;
  uint uVar7;
  
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x2c;
  uVar7 = (uint)*(char *)(param_1 + 0x1d9);
  if (uVar7 == 0) {
    if (*(float *)(param_1 + 0x44) < *(float *)(param_1 + 0x48)) {
      fVar1 = *(float *)(param_1 + 0x44) + *(float *)(&DAT_8033d278 + iVar2);
      *(float *)(param_1 + 0x44) = fVar1;
      if (*(float *)(param_1 + 0x48) < fVar1) {
        *(float *)(param_1 + 0x44) = *(float *)(param_1 + 0x48);
      }
    }
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                        (float *)(param_1 + 0x38));
    FUN_80083874((double)*(float *)(&DAT_8033d26c + iVar2),param_1);
    FUN_80083ad4((double)*(float *)(&DAT_8033d268 + iVar2),param_1,
                 (char)*(undefined2 *)(&DAT_8033d266 + iVar2));
    zz_00833ec_(param_1);
    zz_0083610_(param_1,(float *)(param_1 + 0x48));
    uVar3 = zz_0084170_(param_1);
    uVar4 = zz_0083714_(param_1);
    uVar5 = zz_0083244_((float *)(param_1 + 0x20));
    sVar6 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar6;
    uVar7 = countLeadingZeros((int)sVar6);
    uVar7 = uVar3 | uVar4 | uVar5 | (1 << (uVar7 & 0x1f) | 1U >> 0x20 - (uVar7 & 0x1f)) & 1;
  }
  if (uVar7 != 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  zz_0144d74_(param_1);
  return;
}



// ==== 8014497c  FUN_8014497c ====

void FUN_8014497c(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 801449b8  FUN_801449b8 ====

void FUN_801449b8(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 80144a00  zz_0144a00_ ====

void zz_0144a00_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9)

{
  short sVar1;
  bool bVar2;
  float *pfVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  short *psVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  float local_58;
  float local_54;
  float local_50;
  float afStack_4c [14];
  
  bVar2 = zz_0045ef4_((float *)(param_9 + 0x114),5,param_9 + 0x38,&DAT_802b0cb4);
  if (bVar2) {
    zz_0045ef4_((float *)(param_9 + 0x114),4,param_9 + 0x38,&DAT_802b0ca8);
  }
  *(undefined4 *)(param_9 + 0x120) = *(undefined4 *)(param_9 + 0x20);
  *(undefined4 *)(param_9 + 0x130) = *(undefined4 *)(param_9 + 0x24);
  *(undefined4 *)(param_9 + 0x140) = *(undefined4 *)(param_9 + 0x28);
  zz_00456a0_((float *)(param_9 + 0x114),(float *)(param_9 + 0x114),(float *)(param_9 + 0x58));
  iVar8 = 0;
  iVar7 = param_9;
  for (iVar6 = 0; iVar6 < *(char *)(param_9 + 0x13); iVar6 = iVar6 + 1) {
    psVar5 = (short *)(*(int *)(param_9 + 0x54) + iVar8);
    zz_00457d4_('y',(float *)(param_9 + 0x114),afStack_4c,psVar5[1]);
    pfVar3 = afStack_4c;
    sVar1 = *psVar5;
    iVar4 = (int)sVar1;
    uVar9 = zz_00457d4_('x',pfVar3,pfVar3,sVar1);
    if ((iVar6 == 1) && ((*(ushort *)(param_9 + 0x1c) & 1) != 0)) {
      pfVar3 = &local_58;
      local_50 = FLOAT_8043a298;
      local_54 = FLOAT_8043a298;
      local_58 = FLOAT_8043a298;
      uVar9 = zz_00456a0_(afStack_4c,afStack_4c,pfVar3);
    }
    zz_00076d0_(uVar9,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar7 + 0xe0)
                ,afStack_4c,(undefined *)pfVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
    iVar8 = iVar8 + 8;
    iVar7 = iVar7 + 4;
  }
  return;
}



// ==== 80144b24  FUN_80144b24 ====

void FUN_80144b24(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1;
  for (iVar1 = 0; iVar1 < *(char *)(param_1 + 0x13); iVar1 = iVar1 + 1) {
    zz_00097b4_(*(int *)(iVar2 + 0xe0),0x44);
    iVar2 = iVar2 + 4;
  }
  return;
}



// ==== 80144b8c  FUN_80144b8c ====

/* WARNING: Removing unreachable block (ram,0x80144d58) */
/* WARNING: Removing unreachable block (ram,0x80144d50) */
/* WARNING: Removing unreachable block (ram,0x80144ba4) */
/* WARNING: Removing unreachable block (ram,0x80144b9c) */

void FUN_80144b8c(longlong param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                 undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                 undefined4 param_15,undefined4 param_16)

{
  undefined2 uVar1;
  uint uVar2;
  uint uVar3;
  uint uVar4;
  int iVar5;
  undefined4 extraout_r4;
  float *pfVar6;
  undefined2 *puVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  double dVar13;
  undefined8 uVar14;
  double dVar15;
  double dVar16;
  double local_58;
  
  uVar2 = zz_00055fc_();
  uVar3 = zz_00055fc_();
  iVar12 = 0;
  iVar11 = 0;
  iVar10 = 1;
  iVar9 = param_9;
  dVar16 = DOUBLE_8043a2b0;
  for (iVar8 = 0; iVar8 < *(char *)(param_9 + 0x13); iVar8 = iVar8 + 1) {
    puVar7 = (undefined2 *)(*(int *)(param_9 + 0x54) + iVar12);
    if (iVar8 < 2) {
      puVar7[2] = 0;
      uVar1 = 0xeb00;
      *puVar7 = 0;
      puVar7[1] = (short)(uVar2 << 8);
      if ((uVar3 & 1) != 0) {
        uVar1 = 0x1500;
      }
      puVar7[3] = uVar1;
    }
    else {
      uVar4 = zz_00055fc_();
      dVar15 = (double)((float)((double)CONCAT44(0x43300000,uVar4 & 0xff) - DOUBLE_8043a2a8) /
                       FLOAT_8043a29c);
      uVar4 = zz_00055fc_();
      *puVar7 = (short)(uVar4 << 8);
      uVar4 = zz_00055fc_();
      dVar13 = (double)FLOAT_8043a2a4;
      param_2 = (double)FLOAT_8043a2a0;
      puVar7[1] = (short)(uVar4 << 8);
      param_1 = (longlong)(int)(param_2 * dVar15);
      puVar7[2] = (short)(int)(param_2 * dVar15);
      puVar7[3] = (short)(int)(param_2 * (double)(float)(dVar13 - dVar15));
      if ((uVar3 & 1 << iVar11) != 0) {
        puVar7[2] = -puVar7[2];
      }
      if ((uVar3 & 1 << iVar10) != 0) {
        puVar7[3] = -puVar7[3];
      }
    }
    iVar5 = zz_0006f78_(*(int *)(param_9 + 0x90));
    pfVar6 = (float *)(int)*(short *)(&DAT_8033d310 + iVar11 + *(char *)(param_9 + 0x11) * 8);
    zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar5,
                *(int *)(iVar9 + 0xe0),(int)pfVar6,param_12,param_13,param_14,param_15,param_16);
    iVar5 = zz_0006f78_(*(int *)(param_9 + 0x90));
    local_58 = (double)(CONCAT44(0x43300000,(int)*(char *)(param_9 + 0x12)) ^ 0x80000000);
    uVar14 = zz_00086b8_((double)(float)(local_58 - dVar16),param_2,param_3,param_4,param_5,param_6,
                         param_7,param_8,iVar5,*(int *)(iVar9 + 0xe0),pfVar6,param_12,param_13,
                         param_14,param_15,param_16);
    param_1 = zz_0007c30_(uVar14,param_2,param_3,param_4,param_5,param_6,param_7,param_8,
                          *(int *)(iVar9 + 0xe0),extraout_r4,pfVar6,param_12,param_13,param_14,
                          param_15,param_16);
    iVar12 = iVar12 + 8;
    iVar11 = iVar11 + 2;
    iVar10 = iVar10 + 2;
    iVar9 = iVar9 + 4;
  }
  return;
}



// ==== 80144d74  zz_0144d74_ ====

void zz_0144d74_(int param_1)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  
  iVar1 = 0;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    psVar3 = (short *)(*(int *)(param_1 + 0x54) + iVar1);
    iVar1 = iVar1 + 8;
    *psVar3 = *psVar3 + psVar3[2];
    psVar3[1] = psVar3[1] + psVar3[3];
  }
  return;
}



// ==== 80144dc4  zz_0144dc4_ ====

undefined1 * zz_0144dc4_(int param_1,byte param_2)

{
  undefined1 *puVar1;
  
  if (*(short *)(param_1 + 1000) == *(short *)(&DAT_8033d35c + (uint)param_2 * 0x30)) {
    puVar1 = zz_0088aa0_(param_1,3,8,0,2);
    if (puVar1 != (undefined1 *)0x0) {
      *puVar1 = 1;
      puVar1[0x10] = 0x41;
      puVar1[0x11] = param_2;
      *(code **)(puVar1 + 0xc) = FUN_80144ef8;
      *(code **)(puVar1 + 0x10c) = FUN_8014539c;
      puVar1[0x13] = 2;
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
  }
  else {
    puVar1 = (undefined1 *)0x0;
  }
  return puVar1;
}



// ==== 80144ef8  FUN_80144ef8 ====

void FUN_80144ef8(int param_1)

{
  zz_00840b8_(param_1);
  (*(code *)(&PTR_FUN_8033d390)[*(char *)(param_1 + 0x18)])(param_1);
  return;
}



// ==== 80144f48  FUN_80144f48 ====

void FUN_80144f48(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  uint uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 extraout_r4;
  undefined4 uVar5;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  undefined8 uVar6;
  
  iVar4 = (uint)*(byte *)(param_9 + 0x11) * 0x30;
  iVar2 = -((int)*(short *)(&DAT_8033d332 + iVar4) >> 0x1f);
  if (iVar2 == 0) {
    iVar2 = zz_008ac80_(param_9,(int)*(short *)(&DAT_8033d332 + iVar4));
  }
  uVar1 = (int)*(char *)(param_9 + 0x13) << 2;
  if (uVar1 < 0x81) {
    *(int *)(param_9 + 0x54) = param_9 + 0x144;
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  else {
    piVar3 = zz_0006dc8_(uVar1);
    *(int **)(param_9 + 0xdc) = piVar3;
    if (piVar3 != (int *)0x0) {
      *(undefined4 *)(param_9 + 0x54) = *(undefined4 *)(*(int *)(param_9 + 0xdc) + 0xc);
    }
  }
  if ((iVar2 != 0) && (*(int *)(param_9 + 0x54) != 0)) {
    iVar2 = *(int *)(param_9 + 0x90);
    *(undefined1 *)(param_9 + 0x18) = 1;
    if ((*(byte *)(param_9 + 0xd0) & 4) == 0) {
      *(undefined4 *)(param_9 + 200) = 0;
    }
    gnt4_PSMTXMultVec_bl
              ((float *)(iVar2 + (char)(&DAT_8033d330)[iVar4] * 0x30 + 0x8d4),
               (float *)(iVar4 + -0x7fcc2ccc),(float *)(param_9 + 0x20));
    zz_0083d60_(param_9,iVar2,0);
    gnt4_PSQUATScale_bl((double)*(float *)(&DAT_8033d34c + iVar4),(float *)(param_9 + 0x38),
                        (float *)(param_9 + 0x38));
    *(undefined4 *)(param_9 + 0x44) = *(undefined4 *)(&DAT_8033d34c + iVar4);
    uVar5 = 1;
    *(undefined2 *)(param_9 + 0x1c) = *(undefined2 *)(&DAT_8033d340 + iVar4);
    iVar2 = (int)*(short *)(&DAT_8033d342 + iVar4);
    *(char *)(param_9 + 0x1cb) = (char)*(short *)(&DAT_8033d342 + iVar4);
    *(code **)(param_9 + 0x100) = FUN_8014528c;
    uVar6 = zz_0089100_(param_9,1,1);
    zz_0145404_(uVar6,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9,extraout_r4,
                uVar5,iVar2,in_r7,in_r8,in_r9,in_r10);
    *(char *)(param_9 + 0x82) = *(char *)(param_9 + 0x96) + '1';
    zz_00f036c_(param_9,0xe5);
    return;
  }
  *(undefined1 *)(param_9 + 0x18) = 2;
  return;
}



// ==== 801450c4  FUN_801450c4 ====

void FUN_801450c4(int param_1)

{
  float fVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  uint uVar5;
  short sVar6;
  uint uVar7;
  
  iVar2 = (uint)*(byte *)(param_1 + 0x11) * 0x30;
  uVar7 = (uint)*(char *)(param_1 + 0x1d9);
  if (uVar7 == 0) {
    if (*(float *)(param_1 + 0x44) < *(float *)(&DAT_8033d350 + iVar2)) {
      fVar1 = *(float *)(param_1 + 0x44) + *(float *)(&DAT_8033d354 + iVar2);
      *(float *)(param_1 + 0x44) = fVar1;
      if (*(float *)(&DAT_8033d350 + iVar2) < fVar1) {
        *(float *)(param_1 + 0x44) = *(float *)(&DAT_8033d350 + iVar2);
      }
    }
    gnt4_PSVECNormalize_bl((float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
    gnt4_PSQUATScale_bl((double)*(float *)(param_1 + 0x44),(float *)(param_1 + 0x38),
                        (float *)(param_1 + 0x38));
    FUN_80083874((double)*(float *)(&DAT_8033d348 + iVar2),param_1);
    FUN_80083ba4((double)*(float *)(&DAT_8033d344 + iVar2),param_1,
                 (char)*(undefined2 *)(&DAT_8033d342 + iVar2));
    zz_00833ec_(param_1);
    zz_0083524_(param_1);
    uVar3 = zz_0084170_(param_1);
    uVar4 = zz_0083714_(param_1);
    uVar5 = zz_0083244_((float *)(param_1 + 0x20));
    sVar6 = *(short *)(param_1 + 0x1c) + -1;
    *(short *)(param_1 + 0x1c) = sVar6;
    uVar7 = countLeadingZeros((int)sVar6);
    uVar7 = uVar3 | uVar4 | uVar5 | (1 << (uVar7 & 0x1f) | 1U >> 0x20 - (uVar7 & 0x1f)) & 1;
  }
  if (uVar7 != 0) {
    *(undefined1 *)(param_1 + 0x18) = 2;
    zz_008aff0_(param_1);
    *(undefined1 *)(param_1 + 0x82) = 0;
  }
  zz_01454b0_(param_1);
  return;
}



// ==== 80145208  FUN_80145208 ====

void FUN_80145208(int param_1)

{
  *(undefined1 *)(param_1 + 0x18) = 3;
  zz_008aff0_(param_1);
  *(undefined1 *)(param_1 + 0x82) = 0;
  return;
}



// ==== 80145244  FUN_80145244 ====

void FUN_80145244(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,undefined1 *param_9)

{
  if (*(int **)(param_9 + 0xdc) != (int *)0x0) {
    param_1 = zz_0197ad8_(*(int **)(param_9 + 0xdc));
    *(undefined4 *)(param_9 + 0xdc) = 0;
  }
  zz_0088e50_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}



// ==== 8014528c  FUN_8014528c ====

void FUN_8014528c(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                 double param_6,double param_7,double param_8,int param_9)

{
  short sVar1;
  bool bVar2;
  float *pfVar3;
  int iVar4;
  undefined4 in_r7;
  undefined4 in_r8;
  undefined4 in_r9;
  undefined4 in_r10;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined8 uVar8;
  float afStack_48 [14];
  
  bVar2 = zz_0045ef4_((float *)(param_9 + 0x114),5,param_9 + 0x38,&DAT_802b0cb4);
  if (bVar2) {
    zz_0045ef4_((float *)(param_9 + 0x114),4,param_9 + 0x38,&DAT_802b0ca8);
  }
  *(undefined4 *)(param_9 + 0x120) = *(undefined4 *)(param_9 + 0x20);
  *(undefined4 *)(param_9 + 0x130) = *(undefined4 *)(param_9 + 0x24);
  *(undefined4 *)(param_9 + 0x140) = *(undefined4 *)(param_9 + 0x28);
  zz_00456a0_((float *)(param_9 + 0x114),(float *)(param_9 + 0x114),(float *)(param_9 + 0x58));
  iVar7 = 0;
  iVar6 = param_9;
  for (iVar5 = 0; iVar5 < *(char *)(param_9 + 0x13); iVar5 = iVar5 + 1) {
    if (iVar5 == 0) {
      sVar1 = *(short *)(*(int *)(param_9 + 0x54) + iVar7);
      iVar4 = (int)sVar1;
      pfVar3 = afStack_48;
      uVar8 = zz_00457d4_('z',(float *)(param_9 + 0x114),pfVar3,sVar1);
    }
    else {
      sVar1 = *(short *)(*(int *)(param_9 + 0x54) + iVar7);
      iVar4 = (int)sVar1;
      pfVar3 = afStack_48;
      uVar8 = zz_00457d4_('x',(float *)(param_9 + 0x114),pfVar3,sVar1);
    }
    zz_00076d0_(uVar8,param_2,param_3,param_4,param_5,param_6,param_7,param_8,*(int *)(iVar6 + 0xe0)
                ,afStack_48,(undefined *)pfVar3,iVar4,in_r7,in_r8,in_r9,in_r10);
    iVar7 = iVar7 + 4;
    iVar6 = iVar6 + 4;
  }
  return;
}



// ==== 8014539c  FUN_8014539c ====

void FUN_8014539c(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar2 = param_1;
  for (iVar1 = 0; iVar1 < *(char *)(param_1 + 0x13); iVar1 = iVar1 + 1) {
    zz_00097b4_(*(int *)(iVar2 + 0xe0),0x44);
    iVar2 = iVar2 + 4;
  }
  return;
}



// ==== 80145404  zz_0145404_ ====

void zz_0145404_(undefined8 param_1,double param_2,double param_3,double param_4,double param_5,
                double param_6,double param_7,double param_8,int param_9,undefined4 param_10,
                undefined4 param_11,undefined4 param_12,undefined4 param_13,undefined4 param_14,
                undefined4 param_15,undefined4 param_16)

{
  undefined2 uVar1;
  uint uVar2;
  int iVar3;
  undefined2 *puVar4;
  int iVar5;
  int iVar6;
  undefined *puVar7;
  int iVar8;
  
  iVar5 = 0;
  iVar8 = 0;
  puVar7 = &DAT_8033d330 + (uint)*(byte *)(param_9 + 0x11) * 0x30;
  iVar6 = param_9;
  while( true ) {
    if (*(char *)(param_9 + 0x13) <= iVar5) break;
    puVar4 = (undefined2 *)(*(int *)(param_9 + 0x54) + iVar8);
    uVar2 = zz_00055fc_();
    *puVar4 = (short)(uVar2 << 9);
    uVar1 = 0xf778;
    if ((uVar2 & 0x80) != 0) {
      uVar1 = 0x888;
    }
    puVar4[1] = uVar1;
    iVar3 = zz_0006f78_(*(int *)(param_9 + 0x90));
    param_1 = zz_0006fb4_(param_1,param_2,param_3,param_4,param_5,param_6,param_7,param_8,iVar3,
                          *(int *)(iVar6 + 0xe0),(int)*(short *)(puVar7 + 0x28),param_12,param_13,
                          param_14,param_15,param_16);
    iVar8 = iVar8 + 4;
    puVar7 = puVar7 + 2;
    iVar6 = iVar6 + 4;
    iVar5 = iVar5 + 1;
  }
  return;
}



// ==== 801454b0  zz_01454b0_ ====

void zz_01454b0_(int param_1)

{
  int iVar1;
  int iVar2;
  short *psVar3;
  
  iVar1 = 0;
  for (iVar2 = 0; iVar2 < *(char *)(param_1 + 0x13); iVar2 = iVar2 + 1) {
    psVar3 = (short *)(*(int *)(param_1 + 0x54) + iVar1);
    iVar1 = iVar1 + 4;
    *psVar3 = *psVar3 + psVar3[1];
  }
  return;
}



// ==== 801454f0  zz_01454f0_ ====

void zz_01454f0_(int param_1)

{
  undefined4 uVar1;
  int *piVar2;
  undefined4 *puVar3;
  
  piVar2 = zz_0006dc8_(0xc0);
  *(int **)(param_1 + 0xdc) = piVar2;
  puVar3 = *(undefined4 **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (puVar3 != (undefined4 *)0x0) {
    uVar1 = *(undefined4 *)(param_1 + 0x24);
    *puVar3 = *(undefined4 *)(param_1 + 0x20);
    puVar3[1] = uVar1;
    puVar3[2] = *(undefined4 *)(param_1 + 0x28);
    zz_00e3ca0_(param_1,-0x7fcc1c58,5,puVar3 + 3,(float *)(puVar3 + 0x12));
  }
  return;
}



// ==== 80145568  zz_0145568_ ====

void zz_0145568_(int param_1)

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
      FUN_800e3dec(param_1,(float *)&DAT_8033e3a8,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x12),
                   (int *)&DAT_8033e4a8);
    }
    else {
      FUN_800e4f9c(param_1,-0x7fcc1c58,5,(float *)(puVar2 + 3),(float *)(puVar2 + 0x21));
    }
  }
  return;
}



// ==== 801455fc  zz_01455fc_ ====

void zz_01455fc_(int param_1)

{
  zz_0197ad8_(*(int **)(param_1 + 0xdc));
  *(undefined4 *)(param_1 + 0xdc) = 0;
  return;
}



// ==== 80145634  zz_0145634_ ====

void zz_0145634_(int param_1)

{
  float fVar1;
  float *pfVar2;
  float afStack_18 [4];
  
  pfVar2 = *(float **)(*(int *)(param_1 + 0xdc) + 0xc);
  if (pfVar2 != (float *)0x0) {
    gnt4_PSVECSubtract_bl((float *)(param_1 + 0x20),pfVar2,afStack_18);
    zz_00e4ec4_(param_1,-0x7fcc1c58,5,pfVar2 + 3,afStack_18);
    zz_00e5184_(param_1,-0x7fcc1c58,5,pfVar2 + 3,pfVar2 + 0x21);
    fVar1 = *(float *)(param_1 + 0x24);
    *pfVar2 = *(float *)(param_1 + 0x20);
    pfVar2[1] = fVar1;
    pfVar2[2] = *(float *)(param_1 + 0x28);
  }
  return;
}



// ==== 801457f4  FUN_801457f4 ====

void FUN_801457f4(int param_1)

{
  *(float *)(param_1 + 0x144) = FLOAT_8043a2b8;
  zz_01454f0_(param_1);
  return;
}



// ==== 801458b8  FUN_801458b8 ====

void FUN_801458b8(int param_1)

{
  zz_0145568_(param_1);
  return;
}



// ==== 801458e4  FUN_801458e4 ====

void FUN_801458e4(int param_1)

{
  zz_01455fc_(param_1);
  return;
}



// ==== 80145904  FUN_80145904 ====

void FUN_80145904(int param_1)

{
  zz_0145634_(param_1);
  return;
}



// ==== 80145924  FUN_80145924 ====

void FUN_80145924(int param_1)

{
  (*(code *)(&PTR_FUN_8033e4f4)[*(char *)(param_1 + 0x580)])();
  return;
}



// ==== 80145960  FUN_80145960 ====

void FUN_80145960(int param_1)

{
  *(short *)(param_1 + 0x18da) = *(short *)(param_1 + 0x18da) >> 1;
  (*(code *)(&PTR_FUN_8033e504)[*(char *)(param_1 + 0x581)])();
  return;
}



// ==== 801459a8  FUN_801459a8 ====

void FUN_801459a8(int param_1)

{
  *(short *)(param_1 + 0x1dfc) = *(short *)(param_1 + 0x1dfc) >> 1;
  (*(code *)(&PTR_FUN_8033e518)[*(char *)(param_1 + 0x540)])();
  return;
}



// ==== 801459f0  FUN_801459f0 ====

void FUN_801459f0(int param_1)

{
  float fVar1;
  int iVar2;
  
  fVar1 = FLOAT_8043a2bc;
  *(char *)(param_1 + 0x540) = *(char *)(param_1 + 0x540) + '\x01';
  *(float *)(param_1 + 0x560) = fVar1;
  zz_006d0dc_(param_1,0xc1,0);
  if (*(short *)(param_1 + 0x5aa) < 1) {
    iVar2 = 0;
    *(undefined1 *)(param_1 + 0x6ed) = 0;
  }
  else {
    iVar2 = 2;
    *(undefined1 *)(param_1 + 0x6ed) = 1;
  }
  *(char *)(param_1 + 0x6ec) = (char)iVar2;
  zz_004beb8_((double)FLOAT_8043a2c0,param_1,0xf,2,iVar2 + *(char *)(param_1 + 0x6ee),0xffffffff,
              0xffffffff);
  fVar1 = FLOAT_8043a2b8;
  *(uint *)(param_1 + 0x5e0) = *(uint *)(param_1 + 0x5e0) & 0xffffff4f;
  *(float *)(param_1 + 0x50) = fVar1;
  *(float *)(param_1 + 0x48) = fVar1;
  *(float *)(param_1 + 0x4c) = fVar1;
  *(float *)(param_1 + 0x44) = fVar1;
  *(undefined2 *)(param_1 + 0x80) = 0;
  *(undefined2 *)(param_1 + 0x7e) = 0;
  *(undefined2 *)(param_1 + 0x7c) = 0;
  gnt4_PSVECSubtract_bl
            ((float *)(param_1 + 0x20),(float *)(param_1 + 0x5e8),(float *)(param_1 + 0x38));
  gnt4_PSQUATScale_bl((double)FLOAT_8043a2c4,(float *)(param_1 + 0x38),(float *)(param_1 + 0x38));
  gnt4_PSVECAdd_bl((float *)(param_1 + 0x20),(float *)(param_1 + 0x38),(float *)(param_1 + 0x20));
  zz_00679d0_(param_1);
  *(float *)(param_1 + 0x80c) = FLOAT_8043a2b8;
  return;
}



